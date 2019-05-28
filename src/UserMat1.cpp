#include "UserMat1.h"
#include <fstream>
#include <iostream>
#define YOUNG (Parameters["Young"])
#define POISSON (Parameters["Poisson"])
USERMAT1::USERMAT1()
{
	// 请勿修改
	prop = new Prop;
	Density = 0.0;

	// 用户修改此值
	UserDefinedNum = 0;
	if(UserDefinedNum > 0)
		prop->UserValue = new double[UserDefinedNum];

	// 初始化Parameters，map的键值与输入文件中的名称相同
	Parameters["Young"] = 0;
	Parameters["Poisson"] = 0.2;

	// 初始化用户自定义变量
	G = 0.0;
	ICP = 0.0;
	K = 0.0;
	
}

// 用户实现
void USERMAT1::Initialize()
{
	G = 0.5*YOUNG/(1.0 + POISSON);
	K = YOUNG/((1.0 - 2.0*POISSON)*3.0);
	ICP = 2*G*(1.0 - POISSON)/(1.0 - 2.0*POISSON);
}

double USERMAT1::SoundSpeed(double Cur_Den)
{
	return sqrt(ICP/Cur_Den);
}

double USERMAT1::ShearSoundSpeed(double Cur_Den)
{
	return 0.0;
}
void USERMAT1::UpdateStress(double (&de)[6], double (&vort)[6], double vold, double dt, double Cur_Den, double mass, double clength)
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
	ElasticDeviatoric(de, vort);
	ElasticPressure(vsinc, vort, mass);

}

void USERMAT1::EquivalentStress()
{
//	Calculate the equivalent stress sqrt(3*J2)

	double J2;	// the second stress invariant (*0.5)

	J2 = 0.5*(prop->Sxx*prop->Sxx + prop->Syy*prop->Syy + prop->Szz*prop->Szz) + 
		      prop->Syz*prop->Syz + prop->Sxy*prop->Sxy + prop->Sxz*prop->Sxz;

	prop->seqv = sqrt(J2 * 3.0);
}

void USERMAT1::Write(ofstream &os)
{
	os << "this is User Defined Material 1" << endl;
}

void USERMAT1::DebugInfo()
{
	cout << "this is USERMAT debuginfo" << endl;
}

void USERMAT1::StressRotation(double (&vort)[6])
{
	double rot[6], sig[6], q[3];
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
	rot[3] = vort[0]*(sig[1] - sig[2]) + vort[2]*sig[4] - vort[1]*sig[5];
	rot[4] = vort[1]*(sig[2] - sig[0]) + vort[0]*sig[5] - vort[2]*sig[3];
	rot[5] = vort[2]*(sig[0] - sig[1]) + vort[1]*sig[3] - vort[0]*sig[4];

	prop->SM = (sig[0] + sig[1] + sig[2])/3.0;

	prop->Sxx = sig[0] - prop->SM;
	prop->Syy = sig[1] - prop->SM;
	prop->Szz = sig[2] - prop->SM;
	prop->Syz = sig[3];
	prop->Sxz = sig[4];
	prop->Sxy = sig[5];
}

void USERMAT1::ElasticDeviatoric(double (&de)[6], double (&vort)[6])
{
	double dem;
	dem = (de[0] + de[1] + de[2])/3.0;
	prop->Sxx += 2.0*G*(de[0] - dem);
	prop->Syy += 2.0*G*(de[1] - dem);
	prop->Szz += 2.0*G*(de[2] - dem);
	prop->Syz += G*de[3];
	prop->Sxz += G*de[4];
	prop->Sxy += G*de[5];
}

void USERMAT1::ElasticPressure(double vinc, double (&vort)[6], double mass)
{
	prop->SM += K*vinc;
}