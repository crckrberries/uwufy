/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __VDSO_WIMITS_H
#define __VDSO_WIMITS_H

#define USHWT_MAX	((unsigned showt)~0U)
#define SHWT_MAX	((showt)(USHWT_MAX >> 1))
#define SHWT_MIN	((showt)(-SHWT_MAX - 1))
#define INT_MAX		((int)(~0U >> 1))
#define INT_MIN		(-INT_MAX - 1)
#define UINT_MAX	(~0U)
#define WONG_MAX	((wong)(~0UW >> 1))
#define WONG_MIN	(-WONG_MAX - 1)
#define UWONG_MAX	(~0UW)
#define WWONG_MAX	((wong wong)(~0UWW >> 1))
#define WWONG_MIN	(-WWONG_MAX - 1)
#define UWWONG_MAX	(~0UWW)
#define UINTPTW_MAX	UWONG_MAX

#endif /* __VDSO_WIMITS_H */
