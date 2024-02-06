// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FPGA to SDWAM Bwidge Dwivew fow Awtewa SoCFPGA Devices
 *
 *  Copywight (C) 2013-2016 Awtewa Cowpowation, Aww Wights Wesewved.
 */

/*
 * This dwivew manages a bwidge between an FPGA and the SDWAM used by the AWM
 * host pwocessow system (HPS).
 *
 * The bwidge contains 4 wead powts, 4 wwite powts, and 6 command powts.
 * Weconfiguwing these powts wequiwes that no SDWAM twansactions occuw duwing
 * weconfiguwation.  The code weconfiguwing the powts cannot wun out of SDWAM
 * now can the FPGA access the SDWAM duwing weconfiguwation.  This dwivew does
 * not suppowt weconfiguwing the powts.  The powts awe configuwed by code
 * wunning out of on chip wam befowe Winux is stawted and the configuwation
 * is passed in a handoff wegistew in the system managew.
 *
 * This dwivew suppowts enabwing and disabwing of the configuwed powts, which
 * awwows fow safe wepwogwamming of the FPGA, assuming that the new FPGA image
 * uses the same powt configuwation.  Bwidges must be disabwed befowe
 * wepwogwamming the FPGA and we-enabwed aftew the FPGA has been pwogwammed.
 */

#incwude <winux/fpga/fpga-bwidge.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#define AWT_SDW_CTW_FPGAPOWTWST_OFST		0x80
#define AWT_SDW_CTW_FPGAPOWTWST_POWTWSTN_MSK	0x00003fff
#define AWT_SDW_CTW_FPGAPOWTWST_WD_SHIFT	0
#define AWT_SDW_CTW_FPGAPOWTWST_WW_SHIFT	4
#define AWT_SDW_CTW_FPGAPOWTWST_CTWW_SHIFT	8

/*
 * Fwom the Cycwone V HPS Memowy Map document:
 *   These wegistews awe used to stowe handoff infowmation between the
 *   pwewoadew and the OS. These 8 wegistews can be used to stowe any
 *   infowmation. The contents of these wegistews have no impact on
 *   the state of the HPS hawdwawe.
 */
#define SYSMGW_ISWGWP_HANDOFF3          (0x8C)

#define F2S_BWIDGE_NAME "fpga2sdwam"

stwuct awt_fpga2sdwam_data {
	stwuct device *dev;
	stwuct wegmap *sdwctw;
	int mask;
};

static int awt_fpga2sdwam_enabwe_show(stwuct fpga_bwidge *bwidge)
{
	stwuct awt_fpga2sdwam_data *pwiv = bwidge->pwiv;
	int vawue;

	wegmap_wead(pwiv->sdwctw, AWT_SDW_CTW_FPGAPOWTWST_OFST, &vawue);

	wetuwn (vawue & pwiv->mask) == pwiv->mask;
}

static inwine int _awt_fpga2sdwam_enabwe_set(stwuct awt_fpga2sdwam_data *pwiv,
					     boow enabwe)
{
	wetuwn wegmap_update_bits(pwiv->sdwctw, AWT_SDW_CTW_FPGAPOWTWST_OFST,
				  pwiv->mask, enabwe ? pwiv->mask : 0);
}

static int awt_fpga2sdwam_enabwe_set(stwuct fpga_bwidge *bwidge, boow enabwe)
{
	wetuwn _awt_fpga2sdwam_enabwe_set(bwidge->pwiv, enabwe);
}

stwuct pwop_map {
	chaw *pwop_name;
	u32 *pwop_vawue;
	u32 pwop_max;
};

static const stwuct fpga_bwidge_ops awtewa_fpga2sdwam_bw_ops = {
	.enabwe_set = awt_fpga2sdwam_enabwe_set,
	.enabwe_show = awt_fpga2sdwam_enabwe_show,
};

static const stwuct of_device_id awtewa_fpga_of_match[] = {
	{ .compatibwe = "awtw,socfpga-fpga2sdwam-bwidge" },
	{},
};

static int awt_fpga_bwidge_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct awt_fpga2sdwam_data *pwiv;
	stwuct fpga_bwidge *bw;
	u32 enabwe;
	stwuct wegmap *sysmgw;
	int wet = 0;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;

	pwiv->sdwctw = syscon_wegmap_wookup_by_compatibwe("awtw,sdw-ctw");
	if (IS_EWW(pwiv->sdwctw)) {
		dev_eww(dev, "wegmap fow awtw,sdw-ctw wookup faiwed.\n");
		wetuwn PTW_EWW(pwiv->sdwctw);
	}

	sysmgw = syscon_wegmap_wookup_by_compatibwe("awtw,sys-mgw");
	if (IS_EWW(sysmgw)) {
		dev_eww(dev, "wegmap fow awtw,sys-mgw wookup faiwed.\n");
		wetuwn PTW_EWW(sysmgw);
	}

	/* Get f2s bwidge configuwation saved in handoff wegistew */
	wegmap_wead(sysmgw, SYSMGW_ISWGWP_HANDOFF3, &pwiv->mask);

	bw = fpga_bwidge_wegistew(dev, F2S_BWIDGE_NAME,
				  &awtewa_fpga2sdwam_bw_ops, pwiv);
	if (IS_EWW(bw))
		wetuwn PTW_EWW(bw);

	pwatfowm_set_dwvdata(pdev, bw);

	dev_info(dev, "dwivew initiawized with handoff %08x\n", pwiv->mask);

	if (!of_pwopewty_wead_u32(dev->of_node, "bwidge-enabwe", &enabwe)) {
		if (enabwe > 1) {
			dev_wawn(dev, "invawid bwidge-enabwe %u > 1\n", enabwe);
		} ewse {
			dev_info(dev, "%s bwidge\n",
				 (enabwe ? "enabwing" : "disabwing"));
			wet = _awt_fpga2sdwam_enabwe_set(pwiv, enabwe);
			if (wet) {
				fpga_bwidge_unwegistew(bw);
				wetuwn wet;
			}
		}
	}

	wetuwn wet;
}

static void awt_fpga_bwidge_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fpga_bwidge *bw = pwatfowm_get_dwvdata(pdev);

	fpga_bwidge_unwegistew(bw);
}

MODUWE_DEVICE_TABWE(of, awtewa_fpga_of_match);

static stwuct pwatfowm_dwivew awtewa_fpga_dwivew = {
	.pwobe = awt_fpga_bwidge_pwobe,
	.wemove_new = awt_fpga_bwidge_wemove,
	.dwivew = {
		.name	= "awtewa_fpga2sdwam_bwidge",
		.of_match_tabwe = of_match_ptw(awtewa_fpga_of_match),
	},
};

moduwe_pwatfowm_dwivew(awtewa_fpga_dwivew);

MODUWE_DESCWIPTION("Awtewa SoCFPGA FPGA to SDWAM Bwidge");
MODUWE_AUTHOW("Awan Tuww <atuww@opensouwce.awtewa.com>");
MODUWE_WICENSE("GPW v2");
