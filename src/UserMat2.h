#pragma once
#include "Prop.h"
#include <map>
#include <string>
#include <math.h>

using namespace std;

class DEVELOPMENT_EXPORT USERMAT2
{
public:
	int UserDefinedNum; //!< 粒子携带用户自定义变量数目
	map<string, double> Parameters;  //!< 用户定义的参数
	double Density;  // 初始密度
	Prop* prop;   //!< 当前的质点数据
	USERMAT2();
	double SoundSpeed(double Cur_Den);
	double ShearSoundSpeed(double Cur_Den);
	void EquivalentStress();
	void UpdateStress(double (&de)[6], double (&vort)[6], double vold, double dt, double Cur_Den, double mass, double clength);
	void Write(ofstream &os);
	void Initialize();  // 在读数据后进行预处理
	void DebugInfo();

	// 用户自定义变量
private:
	double G;
	double K;
	double ICP;

	// 用户自定义函数
private:
	void StressRotation(double (&vort)[6]);
	void ElasticDeviatoric(double (&de)[6], double (&vort)[6]);
	void ElasticPressure(double vinc, double (&vort)[6]);
};
