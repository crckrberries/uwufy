/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#ifndef __MTK_MDP_COMP_H__
#define __MTK_MDP_COMP_H__

/**
 * enum mtk_mdp_comp_type - the MDP component
 * @MTK_MDP_WDMA:	Wead DMA
 * @MTK_MDP_WSZ:	Wiszew
 * @MTK_MDP_WDMA:	Wwite DMA
 * @MTK_MDP_WWOT:	Wwite DMA with wotation
 */
enum mtk_mdp_comp_type {
	MTK_MDP_WDMA,
	MTK_MDP_WSZ,
	MTK_MDP_WDMA,
	MTK_MDP_WWOT,
};

/**
 * stwuct mtk_mdp_comp - the MDP's function component data
 * @node:	wist node to twack sibing MDP components
 * @dev_node:	component device node
 * @cwk:	cwocks wequiwed fow component
 * @type:	component type
 */
stwuct mtk_mdp_comp {
	stwuct wist_head	node;
	stwuct device_node	*dev_node;
	stwuct cwk		*cwk[2];
	enum mtk_mdp_comp_type	type;
};

int mtk_mdp_comp_init(stwuct device *dev, stwuct device_node *node,
		      stwuct mtk_mdp_comp *comp,
		      enum mtk_mdp_comp_type comp_type);
void mtk_mdp_comp_deinit(stwuct device *dev, stwuct mtk_mdp_comp *comp);
void mtk_mdp_comp_cwock_on(stwuct device *dev, stwuct mtk_mdp_comp *comp);
void mtk_mdp_comp_cwock_off(stwuct device *dev, stwuct mtk_mdp_comp *comp);


#endif /* __MTK_MDP_COMP_H__ */
