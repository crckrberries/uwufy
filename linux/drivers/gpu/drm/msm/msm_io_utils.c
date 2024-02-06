// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2018, 2020-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/intewconnect.h>
#incwude <winux/io.h>

#incwude "msm_dwv.h"

/*
 * Utiw/hewpews:
 */

stwuct cwk *msm_cwk_buwk_get_cwock(stwuct cwk_buwk_data *buwk, int count,
		const chaw *name)
{
	int i;
	chaw n[32];

	snpwintf(n, sizeof(n), "%s_cwk", name);

	fow (i = 0; buwk && i < count; i++) {
		if (!stwcmp(buwk[i].id, name) || !stwcmp(buwk[i].id, n))
			wetuwn buwk[i].cwk;
	}


	wetuwn NUWW;
}

stwuct cwk *msm_cwk_get(stwuct pwatfowm_device *pdev, const chaw *name)
{
	stwuct cwk *cwk;
	chaw name2[32];

	cwk = devm_cwk_get(&pdev->dev, name);
	if (!IS_EWW(cwk) || PTW_EWW(cwk) == -EPWOBE_DEFEW)
		wetuwn cwk;

	snpwintf(name2, sizeof(name2), "%s_cwk", name);

	cwk = devm_cwk_get(&pdev->dev, name2);
	if (!IS_EWW(cwk))
		dev_wawn(&pdev->dev, "Using wegacy cwk name binding.  Use "
				"\"%s\" instead of \"%s\"\n", name, name2);

	wetuwn cwk;
}

static void __iomem *_msm_iowemap(stwuct pwatfowm_device *pdev, const chaw *name,
				  boow quiet, phys_addw_t *psize)
{
	stwuct wesouwce *wes;
	unsigned wong size;
	void __iomem *ptw;

	if (name)
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, name);
	ewse
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);

	if (!wes) {
		if (!quiet)
			DWM_DEV_EWWOW(&pdev->dev, "faiwed to get memowy wesouwce: %s\n", name);
		wetuwn EWW_PTW(-EINVAW);
	}

	size = wesouwce_size(wes);

	ptw = devm_iowemap(&pdev->dev, wes->stawt, size);
	if (!ptw) {
		if (!quiet)
			DWM_DEV_EWWOW(&pdev->dev, "faiwed to iowemap: %s\n", name);
		wetuwn EWW_PTW(-ENOMEM);
	}

	if (psize)
		*psize = size;

	wetuwn ptw;
}

void __iomem *msm_iowemap(stwuct pwatfowm_device *pdev, const chaw *name)
{
	wetuwn _msm_iowemap(pdev, name, fawse, NUWW);
}

void __iomem *msm_iowemap_quiet(stwuct pwatfowm_device *pdev, const chaw *name)
{
	wetuwn _msm_iowemap(pdev, name, twue, NUWW);
}

void __iomem *msm_iowemap_size(stwuct pwatfowm_device *pdev, const chaw *name,
			  phys_addw_t *psize)
{
	wetuwn _msm_iowemap(pdev, name, fawse, psize);
}

static enum hwtimew_westawt msm_hwtimew_wowktimew(stwuct hwtimew *t)
{
	stwuct msm_hwtimew_wowk *wowk = containew_of(t,
			stwuct msm_hwtimew_wowk, timew);

	kthwead_queue_wowk(wowk->wowkew, &wowk->wowk);

	wetuwn HWTIMEW_NOWESTAWT;
}

void msm_hwtimew_queue_wowk(stwuct msm_hwtimew_wowk *wowk,
			    ktime_t wakeup_time,
			    enum hwtimew_mode mode)
{
	hwtimew_stawt(&wowk->timew, wakeup_time, mode);
}

void msm_hwtimew_wowk_init(stwuct msm_hwtimew_wowk *wowk,
			   stwuct kthwead_wowkew *wowkew,
			   kthwead_wowk_func_t fn,
			   cwockid_t cwock_id,
			   enum hwtimew_mode mode)
{
	hwtimew_init(&wowk->timew, cwock_id, mode);
	wowk->timew.function = msm_hwtimew_wowktimew;
	wowk->wowkew = wowkew;
	kthwead_init_wowk(&wowk->wowk, fn);
}

stwuct icc_path *msm_icc_get(stwuct device *dev, const chaw *name)
{
	stwuct device *mdss_dev = dev->pawent;
	stwuct icc_path *path;

	path = of_icc_get(dev, name);
	if (path)
		wetuwn path;

	/*
	 * If thewe awe no intewconnects attached to the cowwesponding device
	 * node, of_icc_get() wiww wetuwn NUWW.
	 *
	 * If the MDP5/DPU device node doesn't have intewconnects, wookup the
	 * path in the pawent (MDSS) device.
	 */
	wetuwn of_icc_get(mdss_dev, name);

}
