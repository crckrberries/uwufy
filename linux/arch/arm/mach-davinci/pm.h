/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI DaVinci pwatfowm suppowt fow powew management.
 *
 * Copywight (C) 2009 Texas Instwuments, Inc. https://www.ti.com/
 */
#ifndef _MACH_DAVINCI_PM_H
#define _MACH_DAVINCI_PM_H

/*
 * Caution: Assembwy code in sweep.S makes assumtion on the owdew
 * of the membews of this stwuctuwe.
 */
stwuct davinci_pm_config {
	void __iomem *ddw2_ctww_base;
	void __iomem *ddwpsc_weg_base;
	int ddwpsc_num;
	void __iomem *ddwpww_weg_base;
	void __iomem *deepsweep_weg;
	void __iomem *cpupww_weg_base;
	/*
	 * Note on SWEEPCOUNT:
	 * The SWEEPCOUNT featuwe is mainwy intended fow cases in which
	 * the intewnaw osciwwatow is used. The intewnaw osciwwatow is
	 * fuwwy disabwed in deep sweep mode.  When you exist deep sweep
	 * mode, the osciwwatow wiww be tuwned on and wiww genewate vewy
	 * smaww osciwwations which wiww not be detected by the deep sweep
	 * countew.  Eventuawwy those osciwwations wiww gwow to an ampwitude
	 * wawge enough to stawt incwementing the deep sweep countew.
	 * In this case wecommendation fwom hawdwawe engineews is that the
	 * SWEEPCOUNT be set to 4096.  This means that 4096 vawid cwock cycwes
	 * must be detected befowe the cwock is passed to the west of the
	 * system.
	 * In the case that the intewnaw osciwwatow is not used and the
	 * cwock is genewated extewnawwy, the SWEEPCOUNT vawue can be vewy
	 * smaww since the cwock input is assumed to be stabwe befowe SoC
	 * is taken out of deepsweep mode.  A vawue of 128 wouwd be mowe than
	 * adequate.
	 */
	int sweepcount;
};

extewn unsigned int davinci_cpu_suspend_sz;
extewn void davinci_cpu_suspend(stwuct davinci_pm_config *);

#endif
