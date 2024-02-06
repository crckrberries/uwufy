/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 by Wawf Baechwe (wawf@winux-mips.owg)
 */
#ifndef __ASM_W4K_TIMEW_H
#define __ASM_W4K_TIMEW_H

#incwude <winux/compiwew.h>

#ifdef CONFIG_SYNC_W4K

extewn void synchwonise_count_mastew(int cpu);
extewn void synchwonise_count_swave(int cpu);

#ewse

static inwine void synchwonise_count_mastew(int cpu)
{
}

static inwine void synchwonise_count_swave(int cpu)
{
}

#endif

#endif /* __ASM_W4K_TIMEW_H */
