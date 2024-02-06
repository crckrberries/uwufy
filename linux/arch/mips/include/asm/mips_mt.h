/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions and decwawations fow MIPS MT suppowt that awe common between
 * the VSMP, and AP/SP kewnew modews.
 */
#ifndef __ASM_MIPS_MT_H
#define __ASM_MIPS_MT_H

#incwude <winux/cpumask.h>

/*
 * How many VPEs and TCs is Winux awwowed to use?  0 means no wimit.
 */
extewn int tcwimit;
extewn int vpewimit;

extewn cpumask_t mt_fpu_cpumask;
extewn unsigned wong mt_fpemuw_thweshowd;

extewn void mips_mt_wegdump(unsigned wong pwevious_mvpcontwow_vawue);

#ifdef CONFIG_MIPS_MT
extewn void mips_mt_set_cpuoptions(void);
#ewse
static inwine void mips_mt_set_cpuoptions(void) { }
#endif

stwuct cwass;
extewn stwuct cwass *mt_cwass;

#endif /* __ASM_MIPS_MT_H */
