#pragma once
// �û��Զ�����ʵ���Ϣ
class __declspec(dllexport) Prop
{
public:
	double VOL;			//!< Current volume
	double SM;			//!< mean stress
	double q;			//!< artificial bulk viscosity
	double ie;			//!< internal energy 2006-12
	double cp;			//!< sound speed
	double SD[6];       //!< ƫӦ��
	                    // SD[0] -> SDxx
	                    // SD[1] -> SDyy
	                    // SD[2] -> SDzz
	                    // SD[3] -> SDxy
	                    // SD[4] -> SDyz
	                    // SD[5] -> SDxz
	double* UserValue;  //!< �����û�����
	Prop(){UserValue = nullptr;}
};
