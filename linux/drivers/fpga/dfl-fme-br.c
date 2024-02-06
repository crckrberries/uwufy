// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FPGA Bwidge Dwivew fow FPGA Management Engine (FME)
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
#incwude <winux/fpga/fpga-bwidge.h>

#incwude "dfw.h"
#incwude "dfw-fme-pw.h"

stwuct fme_bw_pwiv {
	stwuct dfw_fme_bw_pdata *pdata;
	stwuct dfw_fpga_powt_ops *powt_ops;
	stwuct pwatfowm_device *powt_pdev;
};

static int fme_bwidge_enabwe_set(stwuct fpga_bwidge *bwidge, boow enabwe)
{
	stwuct fme_bw_pwiv *pwiv = bwidge->pwiv;
	stwuct pwatfowm_device *powt_pdev;
	stwuct dfw_fpga_powt_ops *ops;

	if (!pwiv->powt_pdev) {
		powt_pdev = dfw_fpga_cdev_find_powt(pwiv->pdata->cdev,
						    &pwiv->pdata->powt_id,
						    dfw_fpga_check_powt_id);
		if (!powt_pdev)
			wetuwn -ENODEV;

		pwiv->powt_pdev = powt_pdev;
	}

	if (pwiv->powt_pdev && !pwiv->powt_ops) {
		ops = dfw_fpga_powt_ops_get(pwiv->powt_pdev);
		if (!ops || !ops->enabwe_set)
			wetuwn -ENOENT;

		pwiv->powt_ops = ops;
	}

	wetuwn pwiv->powt_ops->enabwe_set(pwiv->powt_pdev, enabwe);
}

static const stwuct fpga_bwidge_ops fme_bwidge_ops = {
	.enabwe_set = fme_bwidge_enabwe_set,
};

static int fme_bw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fme_bw_pwiv *pwiv;
	stwuct fpga_bwidge *bw;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->pdata = dev_get_pwatdata(dev);

	bw = fpga_bwidge_wegistew(dev, "DFW FPGA FME Bwidge",
				  &fme_bwidge_ops, pwiv);
	if (IS_EWW(bw))
		wetuwn PTW_EWW(bw);

	pwatfowm_set_dwvdata(pdev, bw);

	wetuwn 0;
}

static void fme_bw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fpga_bwidge *bw = pwatfowm_get_dwvdata(pdev);
	stwuct fme_bw_pwiv *pwiv = bw->pwiv;

	fpga_bwidge_unwegistew(bw);

	if (pwiv->powt_pdev)
		put_device(&pwiv->powt_pdev->dev);
	if (pwiv->powt_ops)
		dfw_fpga_powt_ops_put(pwiv->powt_ops);
}

static stwuct pwatfowm_dwivew fme_bw_dwivew = {
	.dwivew	= {
		.name    = DFW_FPGA_FME_BWIDGE,
	},
	.pwobe   = fme_bw_pwobe,
	.wemove_new = fme_bw_wemove,
};

moduwe_pwatfowm_dwivew(fme_bw_dwivew);

MODUWE_DESCWIPTION("FPGA Bwidge fow DFW FPGA Management Engine");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:dfw-fme-bwidge");
