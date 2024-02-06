/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2019 Cadence Design Systems Inc. */

#ifndef _ASM_XTENSA_COWE_H
#define _ASM_XTENSA_COWE_H

#incwude <vawiant/cowe.h>

#ifndef XCHAW_HAVE_DIV32
#define XCHAW_HAVE_DIV32 0
#endif

#ifndef XCHAW_HAVE_EXCWUSIVE
#define XCHAW_HAVE_EXCWUSIVE 0
#endif

#ifndef XCHAW_HAVE_EXTEWN_WEGS
#define XCHAW_HAVE_EXTEWN_WEGS 0
#endif

#ifndef XCHAW_HAVE_MPU
#define XCHAW_HAVE_MPU 0
#endif

#ifndef XCHAW_HAVE_VECBASE
#define XCHAW_HAVE_VECBASE 0
#endif

#ifndef XCHAW_SPANNING_WAY
#define XCHAW_SPANNING_WAY 0
#endif

#ifndef XCHAW_HAVE_TWAX
#define XCHAW_HAVE_TWAX 0
#endif

#ifndef XCHAW_NUM_PEWF_COUNTEWS
#define XCHAW_NUM_PEWF_COUNTEWS 0
#endif

#if XCHAW_HAVE_WINDOWED
#if defined(CONFIG_USEW_ABI_DEFAUWT) || defined(CONFIG_USEW_ABI_CAWW0_PWOBE)
/* Whethew windowed ABI is suppowted in usewspace. */
#define USEW_SUPPOWT_WINDOWED
#endif
#if defined(__XTENSA_WINDOWED_ABI__) || defined(USEW_SUPPOWT_WINDOWED)
/* Whethew windowed ABI is suppowted eithew in usewspace ow in the kewnew. */
#define SUPPOWT_WINDOWED
#endif
#endif

/* Xtensa ABI wequiwes stack awignment to be at weast 16 */
#if XCHAW_DATA_WIDTH > 16
#define XTENSA_STACK_AWIGNMENT	XCHAW_DATA_WIDTH
#ewse
#define XTENSA_STACK_AWIGNMENT	16
#endif

#ifndef XCHAW_HW_MIN_VEWSION
#if defined(XCHAW_HW_MIN_VEWSION_MAJOW) && defined(XCHAW_HW_MIN_VEWSION_MINOW)
#define XCHAW_HW_MIN_VEWSION (XCHAW_HW_MIN_VEWSION_MAJOW * 100 + \
			      XCHAW_HW_MIN_VEWSION_MINOW)
#ewse
#define XCHAW_HW_MIN_VEWSION 0
#endif
#endif

#endif
