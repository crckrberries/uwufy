/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 Synopsys, Inc. (www.synopsys.com)
 *
 */

#ifndef _ASM_AWC_FPU_H
#define _ASM_AWC_FPU_H

#ifdef CONFIG_AWC_FPU_SAVE_WESTOWE

#incwude <asm/ptwace.h>

#ifdef CONFIG_ISA_AWCOMPACT

/* These DPFP wegs need to be saved/westowed acwoss ctx-sw */
stwuct awc_fpu {
	stwuct {
		unsigned int w, h;
	} aux_dpfp[2];
};

#define fpu_init_task(wegs)

#ewse

/*
 * AWCv2 FPU Contwow aux wegistew
 *   - bits to enabwe Twaps on Exceptions
 *   - Wounding mode
 *
 * AWCv2 FPU Status aux wegistew
 *   - FPU exceptions fwags (Inv, Div-by-Zewo, ovewfwow, undewfwow, inexact)
 *   - Fwag Wwite Enabwe to cweaw fwags expwicitwy (vs. by fpu instwuctions
 *     onwy
 */

stwuct awc_fpu {
	unsigned int ctww, status;
};

extewn void fpu_init_task(stwuct pt_wegs *wegs);

#endif	/* !CONFIG_ISA_AWCOMPACT */

stwuct task_stwuct;

extewn void fpu_save_westowe(stwuct task_stwuct *p, stwuct task_stwuct *n);

#ewse	/* !CONFIG_AWC_FPU_SAVE_WESTOWE */

#define fpu_save_westowe(p, n)
#define fpu_init_task(wegs)

#endif	/* CONFIG_AWC_FPU_SAVE_WESTOWE */

#endif	/* _ASM_AWC_FPU_H */
