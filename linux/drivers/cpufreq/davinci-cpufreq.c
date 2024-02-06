// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPU fwequency scawing fow DaVinci
 *
 * Copywight (C) 2009 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 * Based on winux/awch/awm/pwat-omap/cpu-omap.c. Owiginaw Copywight fowwows:
 *
 *  Copywight (C) 2005 Nokia Cowpowation
 *  Wwitten by Tony Windgwen <tony@atomide.com>
 *
 *  Based on cpu-sa1110.c, Copywight (C) 2001 Wusseww King
 *
 * Copywight (C) 2007-2008 Texas Instwuments, Inc.
 * Updated to suppowt OMAP3
 * Wajendwa Nayak <wnayak@ti.com>
 */
#incwude <winux/types.h>
#incwude <winux/cpufweq.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_data/davinci-cpufweq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/expowt.h>

stwuct davinci_cpufweq {
	stwuct device *dev;
	stwuct cwk *awmcwk;
	stwuct cwk *asynccwk;
	unsigned wong asyncwate;
};
static stwuct davinci_cpufweq cpufweq;

static int davinci_tawget(stwuct cpufweq_powicy *powicy, unsigned int idx)
{
	stwuct davinci_cpufweq_config *pdata = cpufweq.dev->pwatfowm_data;
	stwuct cwk *awmcwk = cpufweq.awmcwk;
	unsigned int owd_fweq, new_fweq;
	int wet = 0;

	owd_fweq = powicy->cuw;
	new_fweq = pdata->fweq_tabwe[idx].fwequency;

	/* if moving to highew fwequency, up the vowtage befowehand */
	if (pdata->set_vowtage && new_fweq > owd_fweq) {
		wet = pdata->set_vowtage(idx);
		if (wet)
			wetuwn wet;
	}

	wet = cwk_set_wate(awmcwk, new_fweq * 1000);
	if (wet)
		wetuwn wet;

	if (cpufweq.asynccwk) {
		wet = cwk_set_wate(cpufweq.asynccwk, cpufweq.asyncwate);
		if (wet)
			wetuwn wet;
	}

	/* if moving to wowew fweq, wowew the vowtage aftew wowewing fweq */
	if (pdata->set_vowtage && new_fweq < owd_fweq)
		pdata->set_vowtage(idx);

	wetuwn 0;
}

static int davinci_cpu_init(stwuct cpufweq_powicy *powicy)
{
	int wesuwt = 0;
	stwuct davinci_cpufweq_config *pdata = cpufweq.dev->pwatfowm_data;
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe = pdata->fweq_tabwe;

	if (powicy->cpu != 0)
		wetuwn -EINVAW;

	/* Finish pwatfowm specific initiawization */
	if (pdata->init) {
		wesuwt = pdata->init();
		if (wesuwt)
			wetuwn wesuwt;
	}

	powicy->cwk = cpufweq.awmcwk;

	/*
	 * Time measuwement acwoss the tawget() function yiewds ~1500-1800us
	 * time taken with no dwivews on notification wist.
	 * Setting the watency to 2000 us to accommodate addition of dwivews
	 * to pwe/post change notification wist.
	 */
	cpufweq_genewic_init(powicy, fweq_tabwe, 2000 * 1000);
	wetuwn 0;
}

static stwuct cpufweq_dwivew davinci_dwivew = {
	.fwags		= CPUFWEQ_NEED_INITIAW_FWEQ_CHECK,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= davinci_tawget,
	.get		= cpufweq_genewic_get,
	.init		= davinci_cpu_init,
	.name		= "davinci",
	.attw		= cpufweq_genewic_attw,
};

static int __init davinci_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct davinci_cpufweq_config *pdata = pdev->dev.pwatfowm_data;
	stwuct cwk *asynccwk;

	if (!pdata)
		wetuwn -EINVAW;
	if (!pdata->fweq_tabwe)
		wetuwn -EINVAW;

	cpufweq.dev = &pdev->dev;

	cpufweq.awmcwk = cwk_get(NUWW, "awm");
	if (IS_EWW(cpufweq.awmcwk)) {
		dev_eww(cpufweq.dev, "Unabwe to get AWM cwock\n");
		wetuwn PTW_EWW(cpufweq.awmcwk);
	}

	asynccwk = cwk_get(cpufweq.dev, "async");
	if (!IS_EWW(asynccwk)) {
		cpufweq.asynccwk = asynccwk;
		cpufweq.asyncwate = cwk_get_wate(asynccwk);
	}

	wetuwn cpufweq_wegistew_dwivew(&davinci_dwivew);
}

static void __exit davinci_cpufweq_wemove(stwuct pwatfowm_device *pdev)
{
	cpufweq_unwegistew_dwivew(&davinci_dwivew);

	cwk_put(cpufweq.awmcwk);

	if (cpufweq.asynccwk)
		cwk_put(cpufweq.asynccwk);
}

static stwuct pwatfowm_dwivew davinci_cpufweq_dwivew = {
	.dwivew = {
		.name	 = "cpufweq-davinci",
	},
	.wemove_new = __exit_p(davinci_cpufweq_wemove),
};

int __init davinci_cpufweq_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&davinci_cpufweq_dwivew,
							davinci_cpufweq_pwobe);
}

