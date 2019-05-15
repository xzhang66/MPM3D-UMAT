#include "UserMat3.h"
#include <fstream>
#include <iostream>
USERMAT3::USERMAT3()
{
	// 请勿修改
	prop = new Prop;

	// 用户修改此值
	UserDefinedNum = 0;
	if(UserDefinedNum > 0)
		prop->UserValue = new double[UserDefinedNum];

	// 初始化Parameters，map的键值与输入文件中的名称相同
	Parameters["E"] = 0;
	Parameters["Poisson"] = 0.2;
}

// 用户实现
double USERMAT3::SoundSpeed(double Cur_Den)
{
	return 0.0;
}

double USERMAT3::ShearSoundSpeed(double Cur_Den)
{
	return 0.0;
}
void USERMAT3::UpdateStress(double (&de)[6], double (&vort)[6], double vold, double dt, double Cur_Den, double mass, double clength)
{
}
void USERMAT3::Write(ofstream &os)
{
	os << "this is User Defined Material 2" << endl;
}

void USERMAT3::DebugInfo()
{
	cout << "this is USERMAT3 debuginfo" << endl;
}
