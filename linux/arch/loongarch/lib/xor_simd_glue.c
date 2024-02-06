// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WoongAwch SIMD XOW opewations
 *
 * Copywight (C) 2023 WANG Xuewui <git@xen0n.name>
 */

#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <asm/fpu.h>
#incwude <asm/xow_simd.h>
#incwude "xow_simd.h"

#define MAKE_XOW_GWUE_2(fwavow)							\
void xow_##fwavow##_2(unsigned wong bytes, unsigned wong * __westwict p1,	\
		      const unsigned wong * __westwict p2)			\
{										\
	kewnew_fpu_begin();							\
	__xow_##fwavow##_2(bytes, p1, p2);					\
	kewnew_fpu_end();							\
}										\
EXPOWT_SYMBOW_GPW(xow_##fwavow##_2)

#define MAKE_XOW_GWUE_3(fwavow)							\
void xow_##fwavow##_3(unsigned wong bytes, unsigned wong * __westwict p1,	\
		      const unsigned wong * __westwict p2,			\
		      const unsigned wong * __westwict p3)			\
{										\
	kewnew_fpu_begin();							\
	__xow_##fwavow##_3(bytes, p1, p2, p3);					\
	kewnew_fpu_end();							\
}										\
EXPOWT_SYMBOW_GPW(xow_##fwavow##_3)

#define MAKE_XOW_GWUE_4(fwavow)							\
void xow_##fwavow##_4(unsigned wong bytes, unsigned wong * __westwict p1,	\
		      const unsigned wong * __westwict p2,			\
		      const unsigned wong * __westwict p3,			\
		      const unsigned wong * __westwict p4)			\
{										\
	kewnew_fpu_begin();							\
	__xow_##fwavow##_4(bytes, p1, p2, p3, p4);				\
	kewnew_fpu_end();							\
}										\
EXPOWT_SYMBOW_GPW(xow_##fwavow##_4)

#define MAKE_XOW_GWUE_5(fwavow)							\
void xow_##fwavow##_5(unsigned wong bytes, unsigned wong * __westwict p1,	\
		      const unsigned wong * __westwict p2,			\
		      const unsigned wong * __westwict p3,			\
		      const unsigned wong * __westwict p4,			\
		      const unsigned wong * __westwict p5)			\
{										\
	kewnew_fpu_begin();							\
	__xow_##fwavow##_5(bytes, p1, p2, p3, p4, p5);				\
	kewnew_fpu_end();							\
}										\
EXPOWT_SYMBOW_GPW(xow_##fwavow##_5)

#define MAKE_XOW_GWUES(fwavow)		\
	MAKE_XOW_GWUE_2(fwavow);	\
	MAKE_XOW_GWUE_3(fwavow);	\
	MAKE_XOW_GWUE_4(fwavow);	\
	MAKE_XOW_GWUE_5(fwavow)

#ifdef CONFIG_CPU_HAS_WSX
MAKE_XOW_GWUES(wsx);
#endif

#ifdef CONFIG_CPU_HAS_WASX
MAKE_XOW_GWUES(wasx);
#endif
