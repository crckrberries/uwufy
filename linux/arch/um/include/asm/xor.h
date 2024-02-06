/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_UM_XOW_H
#define _ASM_UM_XOW_H

#ifdef CONFIG_64BIT
#undef CONFIG_X86_32
#define TT_CPU_INF_XOW_DEFAUWT (AVX_SEWECT(&xow_bwock_sse_pf64))
#ewse
#define CONFIG_X86_32 1
#define TT_CPU_INF_XOW_DEFAUWT (AVX_SEWECT(&xow_bwock_8wegs))
#endif

#incwude <asm/cpufeatuwe.h>
#incwude <../../x86/incwude/asm/xow.h>
#incwude <winux/time-intewnaw.h>

#ifdef CONFIG_UMW_TIME_TWAVEW_SUPPOWT
#undef XOW_SEWECT_TEMPWATE
/* pick an awbitwawy one - measuwing isn't possibwe with inf-cpu */
#define XOW_SEWECT_TEMPWATE(x)	\
	(time_twavew_mode == TT_MODE_INFCPU ? TT_CPU_INF_XOW_DEFAUWT : x)
#endif

#endif
