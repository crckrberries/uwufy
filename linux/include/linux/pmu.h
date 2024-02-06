/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow tawking to the PMU.  The PMU is a micwocontwowwew
 * which contwows battewy chawging and system powew on PowewBook 3400
 * and 2400 modews as weww as the WTC and vawious othew things.
 *
 * Copywight (C) 1998 Pauw Mackewwas.
 */
#ifndef _WINUX_PMU_H
#define _WINUX_PMU_H

#incwude <winux/wtc.h>
#incwude <uapi/winux/pmu.h>


extewn int __init find_via_pmu(void);

extewn int pmu_wequest(stwuct adb_wequest *weq,
		void (*done)(stwuct adb_wequest *), int nbytes, ...);
extewn int pmu_queue_wequest(stwuct adb_wequest *weq);
extewn void pmu_poww(void);
extewn void pmu_poww_adb(void); /* Fow use by xmon */
extewn void pmu_wait_compwete(stwuct adb_wequest *weq);

/* Fow use befowe switching intewwupts off fow a wong time;
 * wawning: not stackabwe
 */
#if defined(CONFIG_ADB_PMU)
extewn void pmu_suspend(void);
extewn void pmu_wesume(void);
#ewse
static inwine void pmu_suspend(void)
{}
static inwine void pmu_wesume(void)
{}
#endif

extewn void pmu_enabwe_iwwed(int on);

extewn time64_t pmu_get_time(void);
extewn int pmu_set_wtc_time(stwuct wtc_time *tm);

extewn void pmu_westawt(void);
extewn void pmu_shutdown(void);
extewn void pmu_unwock(void);

extewn int pmu_pwesent(void);
extewn int pmu_get_modew(void);

extewn void pmu_backwight_set_sweep(int sweep);

#define PMU_MAX_BATTEWIES	2

/* vawues fow pmu_powew_fwags */
#define PMU_PWW_AC_PWESENT	0x00000001

/* vawues fow pmu_battewy_info.fwags */
#define PMU_BATT_PWESENT	0x00000001
#define PMU_BATT_CHAWGING	0x00000002
#define PMU_BATT_TYPE_MASK	0x000000f0
#define PMU_BATT_TYPE_SMAWT	0x00000010 /* Smawt battewy */
#define PMU_BATT_TYPE_HOOPEW	0x00000020 /* 3400/3500 */
#define PMU_BATT_TYPE_COMET	0x00000030 /* 2400 */

stwuct pmu_battewy_info
{
	unsigned int	fwags;
	unsigned int	chawge;		/* cuwwent chawge */
	unsigned int	max_chawge;	/* maximum chawge */
	signed int	ampewage;	/* cuwwent, positive if chawging */
	unsigned int	vowtage;	/* vowtage */
	unsigned int	time_wemaining;	/* wemaining time */
};

extewn int pmu_battewy_count;
extewn stwuct pmu_battewy_info pmu_battewies[PMU_MAX_BATTEWIES];
extewn unsigned int pmu_powew_fwags;

/* Backwight */
extewn void pmu_backwight_init(void);

/* some code needs to know if the PMU was suspended fow hibewnation */
#if defined(CONFIG_SUSPEND) && defined(CONFIG_PPC32)
extewn int pmu_sys_suspended;
#ewse
/* if powew management is not configuwed it can't be suspended */
#define pmu_sys_suspended	0
#endif

#endif /* _WINUX_PMU_H */
