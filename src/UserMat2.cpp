#include "UserMat2.h"
#include <fstream>
#include <iostream>
#define SIG_Y UserValue[0]
#define EPEFF UserValue[1]
#define YOUNG Parameters["E"]
#define POISSON Parameters["Poisson"]
#define YIELD0 Parameters["Yield0"]
#define PWC Parameters["PlasticWorkCoefficient"]
#define QPHI Parameters["qphi"]
#define KPHI Parameters["kphi"]
#define QPSI Parameters["qpsi"]
#define TEN_F Parameters["ten_f"]
#define min(a,b) (a<b?a:b)
USERMAT2::USERMAT2()
{
	// 请勿修改
	prop = new Prop;
	Density = 0.0;

	// 用户修改此值
	UserDefinedNum = 2;
	if(UserDefinedNum > 0)
		prop->UserValue = new double[UserDefinedNum];

	// 初始化Parameters，map的键值与输入文件中的名称相同
	Parameters["E"] = 0;
	Parameters["Poisson"] = 0.2;
	Parameters["Yield0"] = 0.0;
	Parameters["PlasticWorkCoefficient"] = 0.0;
	Parameters["qphi"] = 0.0;
	Parameters["kphi"] = 0.0;
	Parameters["qpsi"] = 0.0;
	Parameters["ten_f"] = 0.0;

	// 初始化用户自定义变量
	ICP = 0.0;
	K = 0.0;
	G = 0.0;
}

// 用户实现
void USERMAT2::Initialize()
{
	G = 0.5*YOUNG/(1.0 + POISSON);
	K = YOUNG/((1.0 - 2.0*POISSON)*3.0);
	ICP = 2*G*(1.0 - POISSON)/(1.0 - 2.0*POISSON);
}

double USERMAT2::SoundSpeed(double Cur_Den)
{
	return sqrt(ICP/Cur_Den); 
}

double USERMAT2::ShearSoundSpeed(double Cur_Den)
{
	return 0.0;
}

void USERMAT2::EquivalentStress()
{
	double J2;
	J2 = 0.5*(prop->Sxx*prop->Sxx + prop->Syy*prop->Syy + prop->Szz*prop->Szz)
		    + prop->Syz*prop->Syz + prop->Sxz*prop->Sxz + prop->Sxy*prop->Sxy;
	prop->seqv = sqrt(3.0*J2);
}

void USERMAT2::UpdateStress(double (&de)[6], double (&vort)[6], double vold, double dt, double Cur_Den, double mass, double clength)
{
	double sold[6], smold;
	sold[0] = prop->Sxx;
	sold[1] = prop->Syy;
	sold[2] = prop->Szz;
	sold[3] = prop->Syz;
	sold[4] = prop->Sxz;
	sold[5] = prop->Sxy;

	smold = prop->SM;

	double vsinc = de[0] + de[1] + de[2];
	double dvol2 = 0.5*(prop->VOL - vold);
	double V2 = (vold + prop->VOL);

	StressRotation(vort);

	double tenf, tenf_max;
	tenf = -1e10;
	if(QPHI == 0.0)
		tenf = 0.0;
	else
	{
		tenf_max = KPHI/QPHI;
		tenf = min(tenf, tenf_max);
	}

	// trial elastic stresses
	ElasticDeviatoric(de, vort);
	ElasticPressure(vsinc, vort);

	double dpFi, dpsig;
	double tau = 0.0;
	double newtau = 0.0;
	EquivalentStress();
	tau = prop->seqv/sqrt(3.0);
	
	dpFi = tau + QPHI*prop->SM - KPHI;
	dpsig = prop->SM - tenf;

	double depeff = 0.0;
	double depeffm = 0.0;
	double dlamd = 0.0;
	double ratio = 0.0;
	bool yield = false;

	if(dpsig < 0.0)
	{
		if(dpFi > 0.0)
		{
			yield = true;
			dlamd = dpFi/(G + K*QPHI*QPSI);
			depeffm = dlamd * QPSI;
			prop->SM = prop->SM - K*depeffm;
			newtau = KPHI - QPHI*prop->SM;
			ratio = newtau/tau;

			prop->Sxx *= ratio;
			prop->Syy *= ratio;
			prop->Szz *= ratio;
			prop->Syz *= ratio;
			prop->Sxz *= ratio;
			prop->Sxy *= ratio;
			prop->seqv *= ratio;

			depeff = dlamd*sqrt(1.0/3.0 +(2.0/9.0)*QPSI*QPSI);

			prop->EPEFF += depeff;
		}
	}
	else
	{
		double alphap = sqrt(1.0 + QPHI*QPHI) - QPHI;
		double Taup = KPHI - QPHI*tenf;
		double dp_hfai = tau - Taup - alphap*dpsig;
		if(dp_hfai > 0.0)
		{
			yield = true;
			dlamd = dpFi/(G + K*QPHI*QPSI);
			depeffm = dlamd*QPSI;
			prop->SM = prop->SM - K*depeffm;
			newtau = KPHI - QPHI*prop->SM;
			ratio = newtau/tau;

			prop->Sxx *= ratio;
			prop->Syy *= ratio;
			prop->Szz *= ratio;
			prop->Syz *= ratio;
			prop->Sxz *= ratio;
			prop->Sxy *= ratio;
			prop->seqv *= ratio;
			depeff = dlamd*sqrt(1.0/3.0 + (2.0/9.0)*QPHI*QPHI);
			prop->EPEFF += depeff;
		}
		else
		{
			yield =true;
			dlamd = (prop->SM - tenf)/K;
			prop->SM = tenf;
			depeff = dlamd*sqrt(2)/3.0;
			prop->EPEFF += depeff;
		}
	}
	
}

void USERMAT2::Write(ofstream &os)
{

}

void USERMAT2::DebugInfo()
{
	cout << "this is USERMAT debuginfo" << endl;
}

void USERMAT2::StressRotation(double (&vort)[6])
{
	double rot[6], sig[6], q[3];
	// Cauchy stress
	sig[0] = prop->Sxx + prop->SM;
	sig[1] = prop->Syy + prop->SM;
	sig[2] = prop->Szz + prop->SM;
	sig[3] = prop->Syz;
	sig[4] = prop->Sxz;
	sig[5] = prop->Sxy;

	q[0] = 2.0*sig[5]*vort[2];
	q[1] = 2.0*sig[4]*vort[1];
	q[2] = 2.0*sig[3]*vort[0];

	rot[0] = - q[0] + q[1];	
	rot[1] = + q[0] - q[2];
	rot[2] = - q[1] + q[2];
	rot[3] = vort[0]*(sig[1]-sig[2]) + vort[2]*sig[4] - vort[1]*sig[5];
	rot[4] = vort[1]*(sig[2]-sig[0]) + vort[0]*sig[5] - vort[2]*sig[3];
	rot[5] = vort[2]*(sig[0]-sig[1]) + vort[1]*sig[3] - vort[0]*sig[4];

	sig[0] += rot[0];
	sig[1] += rot[1];
	sig[2] += rot[2];
	sig[3] += rot[3];
	sig[4] += rot[4];
	sig[5] += rot[5];

	prop->SM = (sig[0] + sig[1] + sig[2])/3.0;

	prop->Sxx = sig[0] - prop->SM;
	prop->Syy = sig[1] - prop->SM;
	prop->Szz = sig[2] - prop->SM;
	prop->Syz = sig[3];
	prop->Sxz = sig[4];
	prop->Sxy = sig[5];
}

void USERMAT2::ElasticDeviatoric(double (&de)[6], double (&vort)[6])
{
	double dem;
	dem = (de[0] + de[1] + de[2]) / 3.0;
	prop->Sxx += 2.0*G*(de[0] - dem);
	prop->Syy += 2.0*G*(de[1] - dem);
	prop->Szz += 2.0*G*(de[2] - dem);
	prop->Syz += G*de[3];
	prop->Sxz += G*de[4];
	prop->Sxy += G*de[5];
}

void USERMAT2::ElasticPressure(double vinc, double (&vort)[6])
{
	prop->SM += K*vinc;
}