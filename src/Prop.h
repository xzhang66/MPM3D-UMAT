#pragma once
// �й��ڲ���ϵͳ�ĺ궨��
#ifdef WIN32
#define DEVELOPMENT_EXPORT __declspec(dllexport)
#else
#define DEVELOPMENT_EXPORT
#endif

#include <cstddef>

// �û��Զ�����ʵ���Ϣ
#define Sxx SD[0]
#define Syy SD[1]
#define Szz SD[2]
#define Sxy SD[3]
#define Syz SD[4]
#define Sxz SD[5]
class DEVELOPMENT_EXPORT Prop
{
public:
	double VOL;			//!< Current volume
	double SM;			//!< mean stress
	double q;			//!< artificial bulk viscosity
	double ie;			//!< internal energy 2006-12
	double cp;			//!< sound speed
	double seqv;        //!< Equivalent stress
	double SD[6];       //!< ƫӦ��
	                    // SD[0] -> SDxx
	                    // SD[1] -> SDyy
	                    // SD[2] -> SDzz
	                    // SD[3] -> SDxy
	                    // SD[4] -> SDyz
	                    // SD[5] -> SDxz
	double* UserValue;  //!< �����û�����
	Prop()
	{
		SD[0] = 0.0;
		SD[1] = 0.0;
		SD[2] = 0.0;
		SD[3] = 0.0;
		SD[4] = 0.0;
		SD[5] = 0.0;
		VOL = 0.0;
		SM = 0.0;
		q = 0.0;
		ie = 0.0;
		cp = 0.0;
		seqv = 0.0;
		UserValue = nullptr;
	}
};
