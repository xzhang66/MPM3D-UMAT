#pragma once
#include "Prop.h"
#include <map>
#include <string>
using namespace std;

class __declspec(dllexport) USERMAT5
{
public:
	int UserDefinedNum; //!< ����Я���û��Զ��������Ŀ
	map<string, double> Parameters;  //!< �û�����Ĳ���
	double Density;  // ��ʼ�ܶ�
	Prop* prop;   //!< ��ǰ���ʵ�����
	USERMAT5();
	double SoundSpeed(double Cur_Den);
	double ShearSoundSpeed(double Cur_Den);
	void UpdateStress(double (&de)[6], double (&vort)[6], double vold, double dt, double Cur_Den, double mass, double clength);
	void Write(ofstream &os);
	void DebugInfo();
};
