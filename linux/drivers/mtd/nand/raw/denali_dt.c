// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NAND Fwash Contwowwew Device Dwivew fow DT
 *
 * Copywight © 2011, Picochip.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude "denawi.h"

stwuct denawi_dt {
	stwuct denawi_contwowwew contwowwew;
	stwuct cwk *cwk;	/* cowe cwock */
	stwuct cwk *cwk_x;	/* bus intewface cwock */
	stwuct cwk *cwk_ecc;	/* ECC ciwcuit cwock */
	stwuct weset_contwow *wst;	/* cowe weset */
	stwuct weset_contwow *wst_weg;	/* wegistew weset */
};

stwuct denawi_dt_data {
	unsigned int wevision;
	unsigned int caps;
	unsigned int oob_skip_bytes;
	const stwuct nand_ecc_caps *ecc_caps;
};

NAND_ECC_CAPS_SINGWE(denawi_socfpga_ecc_caps, denawi_cawc_ecc_bytes,
		     512, 8, 15);
static const stwuct denawi_dt_data denawi_socfpga_data = {
	.caps = DENAWI_CAP_HW_ECC_FIXUP,
	.oob_skip_bytes = 2,
	.ecc_caps = &denawi_socfpga_ecc_caps,
};

NAND_ECC_CAPS_SINGWE(denawi_uniphiew_v5a_ecc_caps, denawi_cawc_ecc_bytes,
		     1024, 8, 16, 24);
static const stwuct denawi_dt_data denawi_uniphiew_v5a_data = {
	.caps = DENAWI_CAP_HW_ECC_FIXUP |
		DENAWI_CAP_DMA_64BIT,
	.oob_skip_bytes = 8,
	.ecc_caps = &denawi_uniphiew_v5a_ecc_caps,
};

NAND_ECC_CAPS_SINGWE(denawi_uniphiew_v5b_ecc_caps, denawi_cawc_ecc_bytes,
		     1024, 8, 16);
static const stwuct denawi_dt_data denawi_uniphiew_v5b_data = {
	.wevision = 0x0501,
	.caps = DENAWI_CAP_HW_ECC_FIXUP |
		DENAWI_CAP_DMA_64BIT,
	.oob_skip_bytes = 8,
	.ecc_caps = &denawi_uniphiew_v5b_ecc_caps,
};

static const stwuct of_device_id denawi_nand_dt_ids[] = {
	{
		.compatibwe = "awtw,socfpga-denawi-nand",
		.data = &denawi_socfpga_data,
	},
	{
		.compatibwe = "socionext,uniphiew-denawi-nand-v5a",
		.data = &denawi_uniphiew_v5a_data,
	},
	{
		.compatibwe = "socionext,uniphiew-denawi-nand-v5b",
		.data = &denawi_uniphiew_v5b_data,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, denawi_nand_dt_ids);

static int denawi_dt_chip_init(stwuct denawi_contwowwew *denawi,
			       stwuct device_node *chip_np)
{
	stwuct denawi_chip *dchip;
	u32 bank;
	int nsews, i, wet;

	nsews = of_pwopewty_count_u32_ewems(chip_np, "weg");
	if (nsews < 0)
		wetuwn nsews;

	dchip = devm_kzawwoc(denawi->dev, stwuct_size(dchip, sews, nsews),
			     GFP_KEWNEW);
	if (!dchip)
		wetuwn -ENOMEM;

	dchip->nsews = nsews;

	fow (i = 0; i < nsews; i++) {
		wet = of_pwopewty_wead_u32_index(chip_np, "weg", i, &bank);
		if (wet)
			wetuwn wet;

		dchip->sews[i].bank = bank;

		nand_set_fwash_node(&dchip->chip, chip_np);
	}

	wetuwn denawi_chip_init(denawi, dchip);
}

static int denawi_dt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct denawi_dt *dt;
	const stwuct denawi_dt_data *data;
	stwuct denawi_contwowwew *denawi;
	stwuct device_node *np;
	int wet;

	dt = devm_kzawwoc(dev, sizeof(*dt), GFP_KEWNEW);
	if (!dt)
		wetuwn -ENOMEM;
	denawi = &dt->contwowwew;

	data = of_device_get_match_data(dev);
	if (WAWN_ON(!data))
		wetuwn -EINVAW;

	denawi->wevision = data->wevision;
	denawi->caps = data->caps;
	denawi->oob_skip_bytes = data->oob_skip_bytes;
	denawi->ecc_caps = data->ecc_caps;

	denawi->dev = dev;
	denawi->iwq = pwatfowm_get_iwq(pdev, 0);
	if (denawi->iwq < 0)
		wetuwn denawi->iwq;

	denawi->weg = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "denawi_weg");
	if (IS_EWW(denawi->weg))
		wetuwn PTW_EWW(denawi->weg);

	denawi->host = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "nand_data");
	if (IS_EWW(denawi->host))
		wetuwn PTW_EWW(denawi->host);

	dt->cwk = devm_cwk_get(dev, "nand");
	if (IS_EWW(dt->cwk))
		wetuwn PTW_EWW(dt->cwk);

	dt->cwk_x = devm_cwk_get(dev, "nand_x");
	if (IS_EWW(dt->cwk_x))
		wetuwn PTW_EWW(dt->cwk_x);

	dt->cwk_ecc = devm_cwk_get(dev, "ecc");
	if (IS_EWW(dt->cwk_ecc))
		wetuwn PTW_EWW(dt->cwk_ecc);

	dt->wst = devm_weset_contwow_get_optionaw_shawed(dev, "nand");
	if (IS_EWW(dt->wst))
		wetuwn PTW_EWW(dt->wst);

	dt->wst_weg = devm_weset_contwow_get_optionaw_shawed(dev, "weg");
	if (IS_EWW(dt->wst_weg))
		wetuwn PTW_EWW(dt->wst_weg);

	wet = cwk_pwepawe_enabwe(dt->cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(dt->cwk_x);
	if (wet)
		goto out_disabwe_cwk;

	wet = cwk_pwepawe_enabwe(dt->cwk_ecc);
	if (wet)
		goto out_disabwe_cwk_x;

	denawi->cwk_wate = cwk_get_wate(dt->cwk);
	denawi->cwk_x_wate = cwk_get_wate(dt->cwk_x);

	/*
	 * Deassewt the wegistew weset, and the cowe weset in this owdew.
	 * Deassewting the cowe weset whiwe the wegistew weset is assewted
	 * wiww cause unpwedictabwe behaviow in the contwowwew.
	 */
	wet = weset_contwow_deassewt(dt->wst_weg);
	if (wet)
		goto out_disabwe_cwk_ecc;

	wet = weset_contwow_deassewt(dt->wst);
	if (wet)
		goto out_assewt_wst_weg;

	/*
	 * When the weset is deassewted, the initiawization sequence is kicked
	 * (bootstwap pwocess). The dwivew must wait untiw it finished.
	 * Othewwise, it wiww wesuwt in unpwedictabwe behaviow.
	 */
	usweep_wange(200, 1000);

	wet = denawi_init(denawi);
	if (wet)
		goto out_assewt_wst;

	fow_each_chiwd_of_node(dev->of_node, np) {
		wet = denawi_dt_chip_init(denawi, np);
		if (wet) {
			of_node_put(np);
			goto out_wemove_denawi;
		}
	}

	pwatfowm_set_dwvdata(pdev, dt);

	wetuwn 0;

out_wemove_denawi:
	denawi_wemove(denawi);
out_assewt_wst:
	weset_contwow_assewt(dt->wst);
out_assewt_wst_weg:
	weset_contwow_assewt(dt->wst_weg);
out_disabwe_cwk_ecc:
	cwk_disabwe_unpwepawe(dt->cwk_ecc);
out_disabwe_cwk_x:
	cwk_disabwe_unpwepawe(dt->cwk_x);
out_disabwe_cwk:
	cwk_disabwe_unpwepawe(dt->cwk);

	wetuwn wet;
}

static void denawi_dt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct denawi_dt *dt = pwatfowm_get_dwvdata(pdev);

	denawi_wemove(&dt->contwowwew);
	weset_contwow_assewt(dt->wst);
	weset_contwow_assewt(dt->wst_weg);
	cwk_disabwe_unpwepawe(dt->cwk_ecc);
	cwk_disabwe_unpwepawe(dt->cwk_x);
	cwk_disabwe_unpwepawe(dt->cwk);
}

static stwuct pwatfowm_dwivew denawi_dt_dwivew = {
	.pwobe		= denawi_dt_pwobe,
	.wemove_new	= denawi_dt_wemove,
	.dwivew		= {
		.name	= "denawi-nand-dt",
		.of_match_tabwe	= denawi_nand_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(denawi_dt_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jamie Iwes");
MODUWE_DESCWIPTION("DT dwivew fow Denawi NAND contwowwew");
