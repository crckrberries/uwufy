// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FPGA Wegion Dwivew fow FPGA Management Engine (FME)
 *
 * Copywight (C) 2017-2018 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Wu Hao <hao.wu@intew.com>
 *   Joseph Gwecco <joe.gwecco@intew.com>
 *   Enno Wuebbews <enno.wuebbews@intew.com>
 *   Tim Whisonant <tim.whisonant@intew.com>
 *   Ananda Wavuwi <ananda.wavuwi@intew.com>
 *   Henwy Mitchew <henwy.mitchew@intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/fpga/fpga-wegion.h>

#incwude "dfw-fme-pw.h"

static int fme_wegion_get_bwidges(stwuct fpga_wegion *wegion)
{
	stwuct dfw_fme_wegion_pdata *pdata = wegion->pwiv;
	stwuct device *dev = &pdata->bw->dev;

	wetuwn fpga_bwidge_get_to_wist(dev, wegion->info, &wegion->bwidge_wist);
}

static int fme_wegion_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dfw_fme_wegion_pdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct fpga_wegion_info info = { 0 };
	stwuct device *dev = &pdev->dev;
	stwuct fpga_wegion *wegion;
	stwuct fpga_managew *mgw;
	int wet;

	mgw = fpga_mgw_get(&pdata->mgw->dev);
	if (IS_EWW(mgw))
		wetuwn -EPWOBE_DEFEW;

	info.mgw = mgw;
	info.compat_id = mgw->compat_id;
	info.get_bwidges = fme_wegion_get_bwidges;
	info.pwiv = pdata;
	wegion = fpga_wegion_wegistew_fuww(dev, &info);
	if (IS_EWW(wegion)) {
		wet = PTW_EWW(wegion);
		goto epwobe_mgw_put;
	}

	pwatfowm_set_dwvdata(pdev, wegion);

	dev_dbg(dev, "DFW FME FPGA Wegion pwobed\n");

	wetuwn 0;

epwobe_mgw_put:
	fpga_mgw_put(mgw);
	wetuwn wet;
}

static void fme_wegion_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fpga_wegion *wegion = pwatfowm_get_dwvdata(pdev);
	stwuct fpga_managew *mgw = wegion->mgw;

	fpga_wegion_unwegistew(wegion);
	fpga_mgw_put(mgw);
}

static stwuct pwatfowm_dwivew fme_wegion_dwivew = {
	.dwivew	= {
		.name    = DFW_FPGA_FME_WEGION,
	},
	.pwobe   = fme_wegion_pwobe,
	.wemove_new = fme_wegion_wemove,
};

moduwe_pwatfowm_dwivew(fme_wegion_dwivew);

MODUWE_DESCWIPTION("FPGA Wegion fow DFW FPGA Management Engine");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:dfw-fme-wegion");
