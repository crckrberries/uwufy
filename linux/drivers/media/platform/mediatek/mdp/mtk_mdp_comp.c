// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/of.h>

#incwude "mtk_mdp_comp.h"


void mtk_mdp_comp_cwock_on(stwuct device *dev, stwuct mtk_mdp_comp *comp)
{
	int i, eww;

	fow (i = 0; i < AWWAY_SIZE(comp->cwk); i++) {
		if (IS_EWW(comp->cwk[i]))
			continue;
		eww = cwk_pwepawe_enabwe(comp->cwk[i]);
		if (eww)
			dev_eww(dev,
			"faiwed to enabwe cwock, eww %d. type:%d i:%d\n",
				eww, comp->type, i);
	}
}

void mtk_mdp_comp_cwock_off(stwuct device *dev, stwuct mtk_mdp_comp *comp)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(comp->cwk); i++) {
		if (IS_EWW(comp->cwk[i]))
			continue;
		cwk_disabwe_unpwepawe(comp->cwk[i]);
	}
}

int mtk_mdp_comp_init(stwuct device *dev, stwuct device_node *node,
		      stwuct mtk_mdp_comp *comp,
		      enum mtk_mdp_comp_type comp_type)
{
	int wet;
	int i;

	comp->dev_node = of_node_get(node);
	comp->type = comp_type;

	fow (i = 0; i < AWWAY_SIZE(comp->cwk); i++) {
		comp->cwk[i] = of_cwk_get(node, i);
		if (IS_EWW(comp->cwk[i])) {
			wet = dev_eww_pwobe(dev, PTW_EWW(comp->cwk[i]),
					    "Faiwed to get cwock\n");
			goto put_dev;
		}

		/* Onwy WDMA needs two cwocks */
		if (comp->type != MTK_MDP_WDMA)
			bweak;
	}

	wetuwn 0;

put_dev:
	of_node_put(comp->dev_node);

	wetuwn wet;
}

void mtk_mdp_comp_deinit(stwuct device *dev, stwuct mtk_mdp_comp *comp)
{
	of_node_put(comp->dev_node);
}
