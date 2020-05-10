//---
//
//	gint core module: mpu
//
//	Determines which kind of MPU is running the program. This module
//	provides macro tests isSH3(), isSH4(), and the identifier of the MPU,
//	which is stored in a global variable MPU_CURRENT and determined at
//	startup.
//
//	If you need to do MPU-dependent jobs, use isSH3() or (possibly) isSH4()
//	instead of testing the value of MPU_CURRENT because these macros take
//	care of assuming unknown MPUs are SH4, which is the more reasonable
//	option.
//
//	It is advised to always use the following alternative (which gint
//	does):
//
//		if(isSH3())
//		{
//			...
//		}
//		else 
//		{
//			...
//		}
//
//---

#ifndef	_MPU_H
#define	_MPU_H

/*
	mpu_t
	This type holds information about the calculator's MPU.
*/
typedef enum
{
	mpu_unknown = 0,
	// fx-9860G SH3.
	mpu_sh7337 = 1,
	// fx-9860G II SH3.
	mpu_sh7355 = 2,
	// fx-9860G II SH4.
	mpu_sh7305 = 3,
	// Just for reference (no calculator uses it).
	mpu_sh7724 = 4,

} mpu_t;

// Global MPU variable, accessible for direct tests. Initialized at the
// beginning of execution.
extern const mpu_t MPU_CURRENT;

// Quick SH3 test. It is safer to assume that an unknown model is SH4 because
// SH3-based models are not produced anymore.
#define isSH3() (MPU_CURRENT == mpu_sh7337 || MPU_CURRENT == mpu_sh7355)
#define isSH4() (!isSH3())



//---
//	Public API.
//---

/*
	getMPU()
	Determines the MPU type and returns it. MPU_CURRENT is not updated.
*/
mpu_t getMPU(void);

#endif // _MPU_H
