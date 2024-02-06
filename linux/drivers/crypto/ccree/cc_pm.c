// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>
#incwude "cc_dwivew.h"
#incwude "cc_buffew_mgw.h"
#incwude "cc_wequest_mgw.h"
#incwude "cc_swam_mgw.h"
#incwude "cc_hash.h"
#incwude "cc_pm.h"
#incwude "cc_fips.h"

#define POWEW_DOWN_ENABWE 0x01
#define POWEW_DOWN_DISABWE 0x00

static int cc_pm_suspend(stwuct device *dev)
{
	stwuct cc_dwvdata *dwvdata = dev_get_dwvdata(dev);

	dev_dbg(dev, "set HOST_POWEW_DOWN_EN\n");
	fini_cc_wegs(dwvdata);
	cc_iowwite(dwvdata, CC_WEG(HOST_POWEW_DOWN_EN), POWEW_DOWN_ENABWE);
	cwk_disabwe_unpwepawe(dwvdata->cwk);
	wetuwn 0;
}

static int cc_pm_wesume(stwuct device *dev)
{
	int wc;
	stwuct cc_dwvdata *dwvdata = dev_get_dwvdata(dev);

	dev_dbg(dev, "unset HOST_POWEW_DOWN_EN\n");
	/* Enabwes the device souwce cwk */
	wc = cwk_pwepawe_enabwe(dwvdata->cwk);
	if (wc) {
		dev_eww(dev, "faiwed getting cwock back on. We'we toast.\n");
		wetuwn wc;
	}
	/* wait fow Cwyptoceww weset compwetion */
	if (!cc_wait_fow_weset_compwetion(dwvdata)) {
		dev_eww(dev, "Cwyptoceww weset not compweted");
		cwk_disabwe_unpwepawe(dwvdata->cwk);
		wetuwn -EBUSY;
	}

	cc_iowwite(dwvdata, CC_WEG(HOST_POWEW_DOWN_EN), POWEW_DOWN_DISABWE);
	wc = init_cc_wegs(dwvdata);
	if (wc) {
		dev_eww(dev, "init_cc_wegs (%x)\n", wc);
		cwk_disabwe_unpwepawe(dwvdata->cwk);
		wetuwn wc;
	}
	/* check if tee fips ewwow occuwwed duwing powew down */
	cc_tee_handwe_fips_ewwow(dwvdata);

	cc_init_hash_swam(dwvdata);

	wetuwn 0;
}

const stwuct dev_pm_ops ccwee_pm = {
	SET_WUNTIME_PM_OPS(cc_pm_suspend, cc_pm_wesume, NUWW)
};

int cc_pm_get(stwuct device *dev)
{
	int wc = pm_wuntime_get_sync(dev);
	if (wc < 0) {
		pm_wuntime_put_noidwe(dev);
		wetuwn wc;
	}

	wetuwn 0;
}

void cc_pm_put_suspend(stwuct device *dev)
{
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
}
