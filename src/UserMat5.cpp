#include "UserMat5.h"
#include <fstream>
#include <iostream>
USERMAT5::USERMAT5()
{
	// �����޸�
	prop = new Prop;
	Density = 0.0;

	// �û��޸Ĵ�ֵ
	UserDefinedNum = 0;
	if(UserDefinedNum > 0)
		prop->UserValue = new double[UserDefinedNum];

	// ��ʼ��Parameters��map�ļ�ֵ�������ļ��е�������ͬ
	Parameters["E"] = 0;
	Parameters["Poisson"] = 0.2;
}

// �û�ʵ��
void USERMAT5::Initialize()
{
}

double USERMAT5::SoundSpeed(double Cur_Den)
{
	return 0.0;
}

double USERMAT5::ShearSoundSpeed(double Cur_Den)
{
	return 0.0;
}
void USERMAT5::EquivalentStress()
{
}

void USERMAT5::UpdateStress(double (&de)[6], double (&vort)[6], double vold, double dt, double Cur_Den, double mass, double clength)
{
}
void USERMAT5::Write(ofstream &os)
{
	os << "this is User Defined Material 2" << endl;
}

void USERMAT5::DebugInfo()
{
	cout << "this is USERMAT debuginfo" << endl;
}
