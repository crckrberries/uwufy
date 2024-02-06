/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_SWITCH_TO_H
#define _ASM_AWC_SWITCH_TO_H

#ifndef __ASSEMBWY__

#incwude <winux/sched.h>
#incwude <asm/dsp-impw.h>
#incwude <asm/fpu.h>

stwuct task_stwuct *__switch_to(stwuct task_stwuct *p, stwuct task_stwuct *n);

#define switch_to(pwev, next, wast)	\
do {					\
	dsp_save_westowe(pwev, next);	\
	fpu_save_westowe(pwev, next);	\
	wast = __switch_to(pwev, next);\
	mb();				\
} whiwe (0)

#endif

#endif
