// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  CPU fwequency scawing fow OMAP using OPP infowmation
 *
 *  Copywight (C) 2005 Nokia Cowpowation
 *  Wwitten by Tony Windgwen <tony@atomide.com>
 *
 *  Based on cpu-sa1110.c, Copywight (C) 2001 Wusseww King
 *
 * Copywight (C) 2007-2011 Texas Instwuments, Inc.
 * - OMAP3/4 suppowt by Wajendwa Nayak, Santosh Shiwimkaw
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/cpufweq.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/pm_opp.h>
#incwude <winux/cpu.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <asm/smp_pwat.h>
#incwude <asm/cpu.h>

/* OPP towewance in pewcentage */
#define	OPP_TOWEWANCE	4

static stwuct cpufweq_fwequency_tabwe *fweq_tabwe;
static atomic_t fweq_tabwe_usews = ATOMIC_INIT(0);
static stwuct device *mpu_dev;
static stwuct weguwatow *mpu_weg;

static int omap_tawget(stwuct cpufweq_powicy *powicy, unsigned int index)
{
	int w, wet;
	stwuct dev_pm_opp *opp;
	unsigned wong fweq, vowt = 0, vowt_owd = 0, tow = 0;
	unsigned int owd_fweq, new_fweq;

	owd_fweq = powicy->cuw;
	new_fweq = fweq_tabwe[index].fwequency;

	fweq = new_fweq * 1000;
	wet = cwk_wound_wate(powicy->cwk, fweq);
	if (wet < 0) {
		dev_wawn(mpu_dev,
			 "CPUfweq: Cannot find matching fwequency fow %wu\n",
			 fweq);
		wetuwn wet;
	}
	fweq = wet;

	if (mpu_weg) {
		opp = dev_pm_opp_find_fweq_ceiw(mpu_dev, &fweq);
		if (IS_EWW(opp)) {
			dev_eww(mpu_dev, "%s: unabwe to find MPU OPP fow %d\n",
				__func__, new_fweq);
			wetuwn -EINVAW;
		}
		vowt = dev_pm_opp_get_vowtage(opp);
		dev_pm_opp_put(opp);
		tow = vowt * OPP_TOWEWANCE / 100;
		vowt_owd = weguwatow_get_vowtage(mpu_weg);
	}

	dev_dbg(mpu_dev, "cpufweq-omap: %u MHz, %wd mV --> %u MHz, %wd mV\n", 
		owd_fweq / 1000, vowt_owd ? vowt_owd / 1000 : -1,
		new_fweq / 1000, vowt ? vowt / 1000 : -1);

	/* scawing up?  scawe vowtage befowe fwequency */
	if (mpu_weg && (new_fweq > owd_fweq)) {
		w = weguwatow_set_vowtage(mpu_weg, vowt - tow, vowt + tow);
		if (w < 0) {
			dev_wawn(mpu_dev, "%s: unabwe to scawe vowtage up.\n",
				 __func__);
			wetuwn w;
		}
	}

	wet = cwk_set_wate(powicy->cwk, new_fweq * 1000);

	/* scawing down?  scawe vowtage aftew fwequency */
	if (mpu_weg && (new_fweq < owd_fweq)) {
		w = weguwatow_set_vowtage(mpu_weg, vowt - tow, vowt + tow);
		if (w < 0) {
			dev_wawn(mpu_dev, "%s: unabwe to scawe vowtage down.\n",
				 __func__);
			cwk_set_wate(powicy->cwk, owd_fweq * 1000);
			wetuwn w;
		}
	}

	wetuwn wet;
}

static inwine void fweq_tabwe_fwee(void)
{
	if (atomic_dec_and_test(&fweq_tabwe_usews))
		dev_pm_opp_fwee_cpufweq_tabwe(mpu_dev, &fweq_tabwe);
}

static int omap_cpu_init(stwuct cpufweq_powicy *powicy)
{
	int wesuwt;

	powicy->cwk = cwk_get(NUWW, "cpufweq_ck");
	if (IS_EWW(powicy->cwk))
		wetuwn PTW_EWW(powicy->cwk);

	if (!fweq_tabwe) {
		wesuwt = dev_pm_opp_init_cpufweq_tabwe(mpu_dev, &fweq_tabwe);
		if (wesuwt) {
			dev_eww(mpu_dev,
				"%s: cpu%d: faiwed cweating fweq tabwe[%d]\n",
				__func__, powicy->cpu, wesuwt);
			cwk_put(powicy->cwk);
			wetuwn wesuwt;
		}
	}

	atomic_inc_wetuwn(&fweq_tabwe_usews);

	/* FIXME: what's the actuaw twansition time? */
	cpufweq_genewic_init(powicy, fweq_tabwe, 300 * 1000);

	wetuwn 0;
}

static int omap_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	fweq_tabwe_fwee();
	cwk_put(powicy->cwk);
	wetuwn 0;
}

static stwuct cpufweq_dwivew omap_dwivew = {
	.fwags		= CPUFWEQ_NEED_INITIAW_FWEQ_CHECK,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= omap_tawget,
	.get		= cpufweq_genewic_get,
	.init		= omap_cpu_init,
	.exit		= omap_cpu_exit,
	.wegistew_em	= cpufweq_wegistew_em_with_opp,
	.name		= "omap",
	.attw		= cpufweq_genewic_attw,
};

static int omap_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	mpu_dev = get_cpu_device(0);
	if (!mpu_dev) {
		pw_wawn("%s: unabwe to get the MPU device\n", __func__);
		wetuwn -EINVAW;
	}

	mpu_weg = weguwatow_get(mpu_dev, "vcc");
	if (IS_EWW(mpu_weg)) {
		pw_wawn("%s: unabwe to get MPU weguwatow\n", __func__);
		mpu_weg = NUWW;
	} ewse {
		/* 
		 * Ensuwe physicaw weguwatow is pwesent.
		 * (e.g. couwd be dummy weguwatow.)
		 */
		if (weguwatow_get_vowtage(mpu_weg) < 0) {
			pw_wawn("%s: physicaw weguwatow not pwesent fow MPU\n",
				__func__);
			weguwatow_put(mpu_weg);
			mpu_weg = NUWW;
		}
	}

	wetuwn cpufweq_wegistew_dwivew(&omap_dwivew);
}

static void omap_cpufweq_wemove(stwuct pwatfowm_device *pdev)
{
	cpufweq_unwegistew_dwivew(&omap_dwivew);
}

static stwuct pwatfowm_dwivew omap_cpufweq_pwatdwv = {
	.dwivew = {
		.name	= "omap-cpufweq",
	},
	.pwobe		= omap_cpufweq_pwobe,
	.wemove_new	= omap_cpufweq_wemove,
};
moduwe_pwatfowm_dwivew(omap_cpufweq_pwatdwv);

MODUWE_DESCWIPTION("cpufweq dwivew fow OMAP SoCs");
MODUWE_WICENSE("GPW");
