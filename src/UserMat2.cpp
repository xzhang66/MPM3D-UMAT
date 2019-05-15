#include "UserMat2.h"
#include <fstream>
#include <iostream>
USERMAT2::USERMAT2()
{
	// �����޸�
	prop = new Prop;

	// �û��޸Ĵ�ֵ
	UserDefinedNum = 0;
	if(UserDefinedNum > 0)
		prop->UserValue = new double[UserDefinedNum];

	// ��ʼ��Parameters��map�ļ�ֵ�������ļ��е�������ͬ
	Parameters["E"] = 0;
	Parameters["Poisson"] = 0.2;
}

// �û�ʵ��
double USERMAT2::SoundSpeed(double Cur_Den)
{
	return 0.0;
}

double USERMAT2::ShearSoundSpeed(double Cur_Den)
{
	return 0.0;
}
void USERMAT2::UpdateStress(double (&de)[6], double (&vort)[6], double vold, double dt, double Cur_Den, double mass, double clength)
{
}
void USERMAT2::Write(ofstream &os)
{
	os << "this is User Defined Material 2" << endl;
}

void USERMAT2::DebugInfo()
{
	cout << "this is USERMAT2 debuginfo" << endl;
}
