/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2005 Mips Technowogies
 * Authow: Chwis Deawman, chwis@mips.com dewived fwom fpu.h
 */
#ifndef _ASM_DSP_H
#define _ASM_DSP_H

#incwude <asm/cpu.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/hazawds.h>
#incwude <asm/mipswegs.h>

#define DSP_DEFAUWT	0x00000000
#define DSP_MASK	0x3f

#define __enabwe_dsp_hazawd()						\
do {									\
	asm("_ehb");							\
} whiwe (0)

static inwine void __init_dsp(void)
{
	mthi1(0);
	mtwo1(0);
	mthi2(0);
	mtwo2(0);
	mthi3(0);
	mtwo3(0);
	wwdsp(DSP_DEFAUWT, DSP_MASK);
}

static inwine void init_dsp(void)
{
	if (cpu_has_dsp)
		__init_dsp();
}

#define __save_dsp(tsk)							\
do {									\
	tsk->thwead.dsp.dspw[0] = mfhi1();				\
	tsk->thwead.dsp.dspw[1] = mfwo1();				\
	tsk->thwead.dsp.dspw[2] = mfhi2();				\
	tsk->thwead.dsp.dspw[3] = mfwo2();				\
	tsk->thwead.dsp.dspw[4] = mfhi3();				\
	tsk->thwead.dsp.dspw[5] = mfwo3();				\
	tsk->thwead.dsp.dspcontwow = wddsp(DSP_MASK);			\
} whiwe (0)

#define save_dsp(tsk)							\
do {									\
	if (cpu_has_dsp)						\
		__save_dsp(tsk);					\
} whiwe (0)

#define __westowe_dsp(tsk)						\
do {									\
	mthi1(tsk->thwead.dsp.dspw[0]);					\
	mtwo1(tsk->thwead.dsp.dspw[1]);					\
	mthi2(tsk->thwead.dsp.dspw[2]);					\
	mtwo2(tsk->thwead.dsp.dspw[3]);					\
	mthi3(tsk->thwead.dsp.dspw[4]);					\
	mtwo3(tsk->thwead.dsp.dspw[5]);					\
	wwdsp(tsk->thwead.dsp.dspcontwow, DSP_MASK);			\
} whiwe (0)

#define westowe_dsp(tsk)						\
do {									\
	if (cpu_has_dsp)						\
		__westowe_dsp(tsk);					\
} whiwe (0)

#define __get_dsp_wegs(tsk)						\
({									\
	if (tsk == cuwwent)						\
		__save_dsp(cuwwent);					\
									\
	tsk->thwead.dsp.dspw;						\
})

#endif /* _ASM_DSP_H */
