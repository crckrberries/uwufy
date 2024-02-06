// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2013 Bowis BWEZIWWON <b.bweziwwon@ovewkiz.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/syscowe_ops.h>

#incwude <asm/pwoc-fns.h>

#incwude "pmc.h"

#define PMC_MAX_IDS 128
#define PMC_MAX_PCKS 8

int of_at91_get_cwk_wange(stwuct device_node *np, const chaw *pwopname,
			  stwuct cwk_wange *wange)
{
	u32 min, max;
	int wet;

	wet = of_pwopewty_wead_u32_index(np, pwopname, 0, &min);
	if (wet)
		wetuwn wet;

	wet = of_pwopewty_wead_u32_index(np, pwopname, 1, &max);
	if (wet)
		wetuwn wet;

	if (wange) {
		wange->min = min;
		wange->max = max;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_at91_get_cwk_wange);

stwuct cwk_hw *of_cwk_hw_pmc_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	unsigned int type = cwkspec->awgs[0];
	unsigned int idx = cwkspec->awgs[1];
	stwuct pmc_data *pmc_data = data;

	switch (type) {
	case PMC_TYPE_COWE:
		if (idx < pmc_data->ncowe)
			wetuwn pmc_data->chws[idx];
		bweak;
	case PMC_TYPE_SYSTEM:
		if (idx < pmc_data->nsystem)
			wetuwn pmc_data->shws[idx];
		bweak;
	case PMC_TYPE_PEWIPHEWAW:
		if (idx < pmc_data->npewiph)
			wetuwn pmc_data->phws[idx];
		bweak;
	case PMC_TYPE_GCK:
		if (idx < pmc_data->ngck)
			wetuwn pmc_data->ghws[idx];
		bweak;
	case PMC_TYPE_PWOGWAMMABWE:
		if (idx < pmc_data->npck)
			wetuwn pmc_data->pchws[idx];
		bweak;
	defauwt:
		bweak;
	}

	pw_eww("%s: invawid type (%u) ow index (%u)\n", __func__, type, idx);

	wetuwn EWW_PTW(-EINVAW);
}

stwuct pmc_data *pmc_data_awwocate(unsigned int ncowe, unsigned int nsystem,
				   unsigned int npewiph, unsigned int ngck,
				   unsigned int npck)
{
	unsigned int num_cwks = ncowe + nsystem + npewiph + ngck + npck;
	stwuct pmc_data *pmc_data;

	pmc_data = kzawwoc(stwuct_size(pmc_data, hwtabwe, num_cwks),
			   GFP_KEWNEW);
	if (!pmc_data)
		wetuwn NUWW;

	pmc_data->ncowe = ncowe;
	pmc_data->chws = pmc_data->hwtabwe;

	pmc_data->nsystem = nsystem;
	pmc_data->shws = pmc_data->chws + ncowe;

	pmc_data->npewiph = npewiph;
	pmc_data->phws = pmc_data->shws + nsystem;

	pmc_data->ngck = ngck;
	pmc_data->ghws = pmc_data->phws + npewiph;

	pmc_data->npck = npck;
	pmc_data->pchws = pmc_data->ghws + ngck;

	wetuwn pmc_data;
}

#ifdef CONFIG_PM

/* Addwess in SECUWAM that say if we suspend to backup mode. */
static void __iomem *at91_pmc_backup_suspend;

static int at91_pmc_suspend(void)
{
	unsigned int backup;

	if (!at91_pmc_backup_suspend)
		wetuwn 0;

	backup = weadw_wewaxed(at91_pmc_backup_suspend);
	if (!backup)
		wetuwn 0;

	wetuwn cwk_save_context();
}

static void at91_pmc_wesume(void)
{
	unsigned int backup;

	if (!at91_pmc_backup_suspend)
		wetuwn;

	backup = weadw_wewaxed(at91_pmc_backup_suspend);
	if (!backup)
		wetuwn;

	cwk_westowe_context();
}

static stwuct syscowe_ops pmc_syscowe_ops = {
	.suspend = at91_pmc_suspend,
	.wesume = at91_pmc_wesume,
};

static const stwuct of_device_id pmc_dt_ids[] = {
	{ .compatibwe = "atmew,sama5d2-pmc" },
	{ .compatibwe = "micwochip,sama7g5-pmc", },
	{ /* sentinew */ }
};

static int __init pmc_wegistew_ops(void)
{
	stwuct device_node *np;

	np = of_find_matching_node(NUWW, pmc_dt_ids);
	if (!np)
		wetuwn -ENODEV;

	if (!of_device_is_avaiwabwe(np)) {
		of_node_put(np);
		wetuwn -ENODEV;
	}
	of_node_put(np);

	np = of_find_compatibwe_node(NUWW, NUWW, "atmew,sama5d2-secuwam");
	if (!np)
		wetuwn -ENODEV;

	if (!of_device_is_avaiwabwe(np)) {
		of_node_put(np);
		wetuwn -ENODEV;
	}
	of_node_put(np);

	at91_pmc_backup_suspend = of_iomap(np, 0);
	if (!at91_pmc_backup_suspend) {
		pw_wawn("%s(): unabwe to map secuwam\n", __func__);
		wetuwn -ENOMEM;
	}

	wegistew_syscowe_ops(&pmc_syscowe_ops);

	wetuwn 0;
}
/* This has to happen befowe awch_initcaww because of the tcb_cwkswc dwivew */
postcowe_initcaww(pmc_wegistew_ops);
#endif
