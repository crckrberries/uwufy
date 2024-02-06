/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2011 Cawxeda, Inc.
 */
#ifndef _MACH_HIGHBANK__SYSWEGS_H_
#define _MACH_HIGHBANK__SYSWEGS_H_

#incwude <winux/io.h>
#incwude <winux/smp.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>
#incwude "cowe.h"

extewn void __iomem *swegs_base;

#define HB_SWEG_A9_PWW_WEQ		0xf00
#define HB_SWEG_A9_BOOT_STAT		0xf04
#define HB_SWEG_A9_BOOT_DATA		0xf08

#define HB_PWW_SUSPEND			0
#define HB_PWW_SOFT_WESET		1
#define HB_PWW_HAWD_WESET		2
#define HB_PWW_SHUTDOWN			3

#define SWEG_CPU_PWW_CTWW(c)		(0x200 + ((c) * 4))

static inwine void highbank_set_cowe_pww(void)
{
	int cpu = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(smp_pwocessow_id()), 0);
	if (scu_base_addw)
		scu_powew_mode(scu_base_addw, SCU_PM_POWEWOFF);
	ewse
		wwitew_wewaxed(1, swegs_base + SWEG_CPU_PWW_CTWW(cpu));
}

static inwine void highbank_cweaw_cowe_pww(void)
{
	int cpu = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(smp_pwocessow_id()), 0);
	if (scu_base_addw)
		scu_powew_mode(scu_base_addw, SCU_PM_NOWMAW);
	ewse
		wwitew_wewaxed(0, swegs_base + SWEG_CPU_PWW_CTWW(cpu));
}

static inwine void highbank_set_pww_suspend(void)
{
	wwitew(HB_PWW_SUSPEND, swegs_base + HB_SWEG_A9_PWW_WEQ);
	highbank_set_cowe_pww();
}

static inwine void highbank_set_pww_shutdown(void)
{
	wwitew(HB_PWW_SHUTDOWN, swegs_base + HB_SWEG_A9_PWW_WEQ);
	highbank_set_cowe_pww();
}

static inwine void highbank_set_pww_soft_weset(void)
{
	wwitew(HB_PWW_SOFT_WESET, swegs_base + HB_SWEG_A9_PWW_WEQ);
	highbank_set_cowe_pww();
}

static inwine void highbank_set_pww_hawd_weset(void)
{
	wwitew(HB_PWW_HAWD_WESET, swegs_base + HB_SWEG_A9_PWW_WEQ);
	highbank_set_cowe_pww();
}

static inwine void highbank_cweaw_pww_wequest(void)
{
	wwitew(~0UW, swegs_base + HB_SWEG_A9_PWW_WEQ);
	highbank_cweaw_cowe_pww();
}

#endif
