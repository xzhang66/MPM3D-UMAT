#pragma once
#include "Prop.h"
#include <map>
#include <string>
#include <math.h>

using namespace std;

class DEVELOPMENT_EXPORT USERMAT2
{
public:
	int UserDefinedNum; //!< ����Я���û��Զ��������Ŀ
	map<string, double> Parameters;  //!< �û�����Ĳ���
	double Density;  // ��ʼ�ܶ�
	Prop* prop;   //!< ��ǰ���ʵ�����
	USERMAT2();
	double SoundSpeed(double Cur_Den);
	double ShearSoundSpeed(double Cur_Den);
	void EquivalentStress();
	void UpdateStress(double (&de)[6], double (&vort)[6], double vold, double dt, double Cur_Den, double mass, double clength);
	void Write(ofstream &os);
	void Initialize();  // �ڶ����ݺ����Ԥ����
	void DebugInfo();

	// �û��Զ������
private:
	double G;
	double K;
	double ICP;

	// �û��Զ��庯��
private:
	void StressRotation(double (&vort)[6]);
	void ElasticDeviatoric(double (&de)[6], double (&vort)[6]);
	void ElasticPressure(double vinc, double (&vort)[6]);
};
