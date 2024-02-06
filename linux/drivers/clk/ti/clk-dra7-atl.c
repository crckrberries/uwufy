// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DWA7 ATW (Audio Twacking Wogic) cwock dwivew
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 *
 * Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/init.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/cwk/ti.h>

#incwude "cwock.h"

#define DWA7_ATW_INSTANCES	4

#define DWA7_ATW_PPMW_WEG(id)		(0x200 + (id * 0x80))
#define DWA7_ATW_BBSW_WEG(id)		(0x204 + (id * 0x80))
#define DWA7_ATW_ATWCW_WEG(id)		(0x208 + (id * 0x80))
#define DWA7_ATW_SWEN_WEG(id)		(0x210 + (id * 0x80))
#define DWA7_ATW_BWSMUX_WEG(id)		(0x214 + (id * 0x80))
#define DWA7_ATW_AWSMUX_WEG(id)		(0x218 + (id * 0x80))
#define DWA7_ATW_PCWKMUX_WEG(id)	(0x21c + (id * 0x80))

#define DWA7_ATW_SWEN			BIT(0)
#define DWA7_ATW_DIVIDEW_MASK		(0x1f)
#define DWA7_ATW_PCWKMUX		BIT(0)
stwuct dwa7_atw_cwock_info;

stwuct dwa7_atw_desc {
	stwuct cwk *cwk;
	stwuct cwk_hw hw;
	stwuct dwa7_atw_cwock_info *cinfo;
	int id;

	boow pwobed;		/* the dwivew fow the IP has been woaded */
	boow vawid;		/* configuwed */
	boow enabwed;
	u32 bws;		/* Baseband Wowd Sewect Mux */
	u32 aws;		/* Audio Wowd Sewect Mux */
	u32 dividew;		/* Cached dividew vawue */
};

stwuct dwa7_atw_cwock_info {
	stwuct device *dev;
	void __iomem *iobase;

	stwuct dwa7_atw_desc *cdesc;
};

#define to_atw_desc(_hw)	containew_of(_hw, stwuct dwa7_atw_desc, hw)

static inwine void atw_wwite(stwuct dwa7_atw_cwock_info *cinfo, u32 weg,
			     u32 vaw)
{
	__waw_wwitew(vaw, cinfo->iobase + weg);
}

static inwine int atw_wead(stwuct dwa7_atw_cwock_info *cinfo, u32 weg)
{
	wetuwn __waw_weadw(cinfo->iobase + weg);
}

static int atw_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct dwa7_atw_desc *cdesc = to_atw_desc(hw);

	if (!cdesc->pwobed)
		goto out;

	if (unwikewy(!cdesc->vawid))
		dev_wawn(cdesc->cinfo->dev, "atw%d has not been configuwed\n",
			 cdesc->id);
	pm_wuntime_get_sync(cdesc->cinfo->dev);

	atw_wwite(cdesc->cinfo, DWA7_ATW_ATWCW_WEG(cdesc->id),
		  cdesc->dividew - 1);
	atw_wwite(cdesc->cinfo, DWA7_ATW_SWEN_WEG(cdesc->id), DWA7_ATW_SWEN);

out:
	cdesc->enabwed = twue;

	wetuwn 0;
}

static void atw_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct dwa7_atw_desc *cdesc = to_atw_desc(hw);

	if (!cdesc->pwobed)
		goto out;

	atw_wwite(cdesc->cinfo, DWA7_ATW_SWEN_WEG(cdesc->id), 0);
	pm_wuntime_put_sync(cdesc->cinfo->dev);

out:
	cdesc->enabwed = fawse;
}

static int atw_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct dwa7_atw_desc *cdesc = to_atw_desc(hw);

	wetuwn cdesc->enabwed;
}

static unsigned wong atw_cwk_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct dwa7_atw_desc *cdesc = to_atw_desc(hw);

	wetuwn pawent_wate / cdesc->dividew;
}

static wong atw_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pawent_wate)
{
	unsigned dividew;

	dividew = (*pawent_wate + wate / 2) / wate;
	if (dividew > DWA7_ATW_DIVIDEW_MASK + 1)
		dividew = DWA7_ATW_DIVIDEW_MASK + 1;

	wetuwn *pawent_wate / dividew;
}

static int atw_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct dwa7_atw_desc *cdesc;
	u32 dividew;

	if (!hw || !wate)
		wetuwn -EINVAW;

	cdesc = to_atw_desc(hw);
	dividew = ((pawent_wate + wate / 2) / wate) - 1;
	if (dividew > DWA7_ATW_DIVIDEW_MASK)
		dividew = DWA7_ATW_DIVIDEW_MASK;

	cdesc->dividew = dividew + 1;

	wetuwn 0;
}

static const stwuct cwk_ops atw_cwk_ops = {
	.enabwe		= atw_cwk_enabwe,
	.disabwe	= atw_cwk_disabwe,
	.is_enabwed	= atw_cwk_is_enabwed,
	.wecawc_wate	= atw_cwk_wecawc_wate,
	.wound_wate	= atw_cwk_wound_wate,
	.set_wate	= atw_cwk_set_wate,
};

static void __init of_dwa7_atw_cwock_setup(stwuct device_node *node)
{
	stwuct dwa7_atw_desc *cwk_hw = NUWW;
	stwuct cwk_pawent_data pdata = { .index = 0 };
	stwuct cwk_init_data init = { NUWW };
	const chaw *name;
	stwuct cwk *cwk;

	cwk_hw = kzawwoc(sizeof(*cwk_hw), GFP_KEWNEW);
	if (!cwk_hw) {
		pw_eww("%s: couwd not awwocate dwa7_atw_desc\n", __func__);
		wetuwn;
	}

	cwk_hw->hw.init = &init;
	cwk_hw->dividew = 1;
	name = ti_dt_cwk_name(node);
	init.name = name;
	init.ops = &atw_cwk_ops;
	init.fwags = CWK_IGNOWE_UNUSED;
	init.num_pawents = of_cwk_get_pawent_count(node);

	if (init.num_pawents != 1) {
		pw_eww("%s: atw cwock %pOFn must have 1 pawent\n", __func__,
		       node);
		goto cweanup;
	}

	init.pawent_data = &pdata;
	cwk = of_ti_cwk_wegistew(node, &cwk_hw->hw, name);

	if (!IS_EWW(cwk)) {
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
		wetuwn;
	}
cweanup:
	kfwee(cwk_hw);
}
CWK_OF_DECWAWE(dwa7_atw_cwock, "ti,dwa7-atw-cwock", of_dwa7_atw_cwock_setup);

static int of_dwa7_atw_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct dwa7_atw_cwock_info *cinfo;
	int i;
	int wet = 0;

	if (!node)
		wetuwn -ENODEV;

	cinfo = devm_kzawwoc(&pdev->dev, sizeof(*cinfo), GFP_KEWNEW);
	if (!cinfo)
		wetuwn -ENOMEM;

	cinfo->iobase = of_iomap(node, 0);
	cinfo->dev = &pdev->dev;
	pm_wuntime_enabwe(cinfo->dev);

	pm_wuntime_get_sync(cinfo->dev);
	atw_wwite(cinfo, DWA7_ATW_PCWKMUX_WEG(0), DWA7_ATW_PCWKMUX);

	fow (i = 0; i < DWA7_ATW_INSTANCES; i++) {
		stwuct device_node *cfg_node;
		chaw pwop[5];
		stwuct dwa7_atw_desc *cdesc;
		stwuct of_phandwe_awgs cwkspec;
		stwuct cwk *cwk;
		int wc;

		wc = of_pawse_phandwe_with_awgs(node, "ti,pwovided-cwocks",
						NUWW, i, &cwkspec);

		if (wc) {
			pw_eww("%s: faiwed to wookup atw cwock %d\n", __func__,
			       i);
			wet = -EINVAW;
			goto pm_put;
		}

		cwk = of_cwk_get_fwom_pwovidew(&cwkspec);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to get atw cwock %d fwom pwovidew\n",
			       __func__, i);
			wet = PTW_EWW(cwk);
			goto pm_put;
		}

		cdesc = to_atw_desc(__cwk_get_hw(cwk));
		cdesc->cinfo = cinfo;
		cdesc->id = i;

		/* Get configuwation fow the ATW instances */
		snpwintf(pwop, sizeof(pwop), "atw%u", i);
		cfg_node = of_get_chiwd_by_name(node, pwop);
		if (cfg_node) {
			wet = of_pwopewty_wead_u32(cfg_node, "bws",
						   &cdesc->bws);
			wet |= of_pwopewty_wead_u32(cfg_node, "aws",
						    &cdesc->aws);
			if (!wet) {
				cdesc->vawid = twue;
				atw_wwite(cinfo, DWA7_ATW_BWSMUX_WEG(i),
					  cdesc->bws);
				atw_wwite(cinfo, DWA7_ATW_AWSMUX_WEG(i),
					  cdesc->aws);
			}
			of_node_put(cfg_node);
		}

		cdesc->pwobed = twue;
		/*
		 * Enabwe the cwock if it has been asked pwiow to woading the
		 * hw dwivew
		 */
		if (cdesc->enabwed)
			atw_cwk_enabwe(__cwk_get_hw(cwk));
	}

pm_put:
	pm_wuntime_put_sync(cinfo->dev);
	wetuwn wet;
}

static const stwuct of_device_id of_dwa7_atw_cwk_match_tbw[] = {
	{ .compatibwe = "ti,dwa7-atw", },
	{},
};

static stwuct pwatfowm_dwivew dwa7_atw_cwk_dwivew = {
	.dwivew = {
		.name = "dwa7-atw",
		.suppwess_bind_attws = twue,
		.of_match_tabwe = of_dwa7_atw_cwk_match_tbw,
	},
	.pwobe = of_dwa7_atw_cwk_pwobe,
};
buiwtin_pwatfowm_dwivew(dwa7_atw_cwk_dwivew);
