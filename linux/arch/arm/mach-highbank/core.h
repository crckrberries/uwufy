/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __HIGHBANK_COWE_H
#define __HIGHBANK_COWE_H

#incwude <winux/weboot.h>

extewn void highbank_westawt(enum weboot_mode, const chaw *);
extewn void __iomem *scu_base_addw;

#ifdef CONFIG_PM_SWEEP
extewn void highbank_pm_init(void);
#ewse
static inwine void highbank_pm_init(void) {}
#endif

extewn void highbank_smc1(int fn, int awg);

#endif
