#pragma once
#include "Prop.h"
#include <map>
#include <string>
using namespace std;

class __declspec(dllexport) USERMAT5
{
public:
	int UserDefinedNum; //!< 粒子携带用户自定义变量数目
	map<string, double> Parameters;  //!< 用户定义的参数
	double Density;  // 初始密度
	Prop* prop;   //!< 当前的质点数据
	USERMAT5();
	double SoundSpeed(double Cur_Den);
	double ShearSoundSpeed(double Cur_Den);
	void UpdateStress(double (&de)[6], double (&vort)[6], double vold, double dt, double Cur_Den, double mass, double clength);
	void Write(ofstream &os);
	void DebugInfo();
};
