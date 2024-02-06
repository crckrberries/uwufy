/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_TIMEX_H
#define _ASM_TIMEX_H

#ifdef __KEWNEW__

#incwude <winux/compiwew.h>

#incwude <asm/cpu.h>
#incwude <asm/cpu-featuwes.h>

typedef unsigned wong cycwes_t;

#define get_cycwes get_cycwes

static inwine cycwes_t get_cycwes(void)
{
	wetuwn dwdtime();
}

#endif /* __KEWNEW__ */

#endif /*  _ASM_TIMEX_H */
