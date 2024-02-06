/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * winux/awch/sh/kewnew/cpu/sh4/sh4_fpu.h
 *
 * Copywight (C) 2006 STMicwoewectwonics Wimited
 * Authow: Caww Shaw <caww.shaw@st.com>
 *
 * Definitions fow SH4 FPU opewations
 */

#ifndef __CPU_SH4_FPU_H
#define __CPU_SH4_FPU_H

#define FPSCW_ENABWE_MASK	0x00000f80UW

#define FPSCW_FMOV_DOUBWE	(1<<1)

#define FPSCW_CAUSE_INEXACT	(1<<12)
#define FPSCW_CAUSE_UNDEWFWOW	(1<<13)
#define FPSCW_CAUSE_OVEWFWOW	(1<<14)
#define FPSCW_CAUSE_DIVZEWO	(1<<15)
#define FPSCW_CAUSE_INVAWID	(1<<16)
#define FPSCW_CAUSE_EWWOW 	(1<<17)

#define FPSCW_DBW_PWECISION	(1<<19)
#define FPSCW_WOUNDING_MODE(x)	((x >> 20) & 3)
#define FPSCW_WM_NEAWEST	(0)
#define FPSCW_WM_ZEWO		(1)

#endif
