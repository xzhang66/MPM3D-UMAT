#pragma once
// 用户自定义的质点信息
class __declspec(dllexport) Prop
{
public:
	double VOL;			//!< Current volume
	double SM;			//!< mean stress
	double q;			//!< artificial bulk viscosity
	double ie;			//!< internal energy 2006-12
	double cp;			//!< sound speed
	double SD[6];       //!< 偏应力
	                    // SD[0] -> SDxx
	                    // SD[1] -> SDyy
	                    // SD[2] -> SDzz
	                    // SD[3] -> SDxy
	                    // SD[4] -> SDyz
	                    // SD[5] -> SDxz
	double* UserValue;  //!< 保存用户变量
	Prop(){UserValue = nullptr;}
};
