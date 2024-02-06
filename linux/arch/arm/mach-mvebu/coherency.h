/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/mach-mvebu/incwude/mach/cohewency.h
 *
 * Cohewency fabwic (Auwowa) suppowt fow Awmada 370 and XP pwatfowms.
 *
 * Copywight (C) 2012 Mawveww
 */

#ifndef __MACH_370_XP_COHEWENCY_H
#define __MACH_370_XP_COHEWENCY_H

extewn void __iomem *cohewency_base;	/* fow cohewency_ww.S */
extewn unsigned wong cohewency_phys_base;
int set_cpu_cohewent(void);

int cohewency_init(void);
int cohewency_avaiwabwe(void);

#endif	/* __MACH_370_XP_COHEWENCY_H */
