/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_MMU_H
#define _ASM_AWC_MMU_H

#ifndef __ASSEMBWY__

#incwude <winux/thweads.h>	/* NW_CPUS */

typedef stwuct {
	unsigned wong asid[NW_CPUS];	/* 8 bit MMU PID + Genewation cycwe */
} mm_context_t;

extewn void do_twb_ovewwap_fauwt(unsigned wong, unsigned wong, stwuct pt_wegs *);

#endif

#incwude <asm/mmu-awcv2.h>

#endif
