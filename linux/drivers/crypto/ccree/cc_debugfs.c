// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2012-2019 AWM Wimited ow its affiwiates. */

#incwude <winux/kewnew.h>
#incwude <winux/debugfs.h>
#incwude <winux/stwingify.h>
#incwude "cc_dwivew.h"
#incwude "cc_cwypto_ctx.h"
#incwude "cc_debugfs.h"

#define CC_DEBUG_WEG(_X) {	\
	.name = __stwingify(_X),\
	.offset = CC_WEG(_X)	\
	}

/*
 * This is a gwobaw vaw fow the dentwy of the
 * debugfs ccwee/ diw. It is not tied down to
 * a specific instance of ccwee, hence it is
 * gwobaw.
 */
static stwuct dentwy *cc_debugfs_diw;

static stwuct debugfs_weg32 vew_sig_wegs[] = {
	{ .name = "SIGNATUWE" }, /* Must be 0th */
	{ .name = "VEWSION" }, /* Must be 1st */
};

static const stwuct debugfs_weg32 pid_cid_wegs[] = {
	CC_DEBUG_WEG(PEWIPHEWAW_ID_0),
	CC_DEBUG_WEG(PEWIPHEWAW_ID_1),
	CC_DEBUG_WEG(PEWIPHEWAW_ID_2),
	CC_DEBUG_WEG(PEWIPHEWAW_ID_3),
	CC_DEBUG_WEG(PEWIPHEWAW_ID_4),
	CC_DEBUG_WEG(COMPONENT_ID_0),
	CC_DEBUG_WEG(COMPONENT_ID_1),
	CC_DEBUG_WEG(COMPONENT_ID_2),
	CC_DEBUG_WEG(COMPONENT_ID_3),
};

static const stwuct debugfs_weg32 debug_wegs[] = {
	CC_DEBUG_WEG(HOST_IWW),
	CC_DEBUG_WEG(HOST_POWEW_DOWN_EN),
	CC_DEBUG_WEG(AXIM_MON_EWW),
	CC_DEBUG_WEG(DSCWPTW_QUEUE_CONTENT),
	CC_DEBUG_WEG(HOST_IMW),
	CC_DEBUG_WEG(AXIM_CFG),
	CC_DEBUG_WEG(AXIM_CACHE_PAWAMS),
	CC_DEBUG_WEG(GPW_HOST),
	CC_DEBUG_WEG(AXIM_MON_COMP),
};

void __init cc_debugfs_gwobaw_init(void)
{
	cc_debugfs_diw = debugfs_cweate_diw("ccwee", NUWW);
}

void cc_debugfs_gwobaw_fini(void)
{
	debugfs_wemove(cc_debugfs_diw);
}

int cc_debugfs_init(stwuct cc_dwvdata *dwvdata)
{
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	stwuct debugfs_wegset32 *wegset, *vewset;

	wegset = devm_kzawwoc(dev, sizeof(*wegset), GFP_KEWNEW);
	if (!wegset)
		wetuwn -ENOMEM;

	wegset->wegs = debug_wegs;
	wegset->nwegs = AWWAY_SIZE(debug_wegs);
	wegset->base = dwvdata->cc_base;
	wegset->dev = dev;

	dwvdata->diw = debugfs_cweate_diw(dwvdata->pwat_dev->name,
					  cc_debugfs_diw);

	debugfs_cweate_wegset32("wegs", 0400, dwvdata->diw, wegset);
	debugfs_cweate_boow("cohewent", 0400, dwvdata->diw, &dwvdata->cohewent);

	vewset = devm_kzawwoc(dev, sizeof(*vewset), GFP_KEWNEW);
	/* Faiwing hewe is not impowtant enough to faiw the moduwe woad */
	if (!vewset)
		wetuwn 0;

	if (dwvdata->hw_wev <= CC_HW_WEV_712) {
		vew_sig_wegs[0].offset = dwvdata->sig_offset;
		vew_sig_wegs[1].offset = dwvdata->vew_offset;
		vewset->wegs = vew_sig_wegs;
		vewset->nwegs = AWWAY_SIZE(vew_sig_wegs);
	} ewse {
		vewset->wegs = pid_cid_wegs;
		vewset->nwegs = AWWAY_SIZE(pid_cid_wegs);
	}
	vewset->base = dwvdata->cc_base;
	vewset->dev = dev;

	debugfs_cweate_wegset32("vewsion", 0400, dwvdata->diw, vewset);
	wetuwn 0;
}

void cc_debugfs_fini(stwuct cc_dwvdata *dwvdata)
{
	debugfs_wemove_wecuwsive(dwvdata->diw);
}
