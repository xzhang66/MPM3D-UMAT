#include "UserMat4.h"
#include <fstream>
#include <iostream>
USERMAT4::USERMAT4()
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
double USERMAT4::SoundSpeed(double Cur_Den)
{
	return 0.0;
}

double USERMAT4::ShearSoundSpeed(double Cur_Den)
{
	return 0.0;
}
void USERMAT4::UpdateStress(double (&de)[6], double (&vort)[6], double vold, double dt, double Cur_Den, double mass, double clength)
{
}
void USERMAT4::Write(ofstream &os)
{
	os << "this is User Defined Material 2" << endl;
}

void USERMAT4::DebugInfo()
{
	cout << "this is USERMAT4 debuginfo" << endl;
}
