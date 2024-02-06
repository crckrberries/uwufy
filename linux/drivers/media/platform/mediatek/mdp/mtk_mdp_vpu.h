/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015-2016 MediaTek Inc.
 * Authow: Houwong Wei <houwong.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#ifndef __MTK_MDP_VPU_H__
#define __MTK_MDP_VPU_H__

#incwude "mtk_mdp_ipi.h"


/**
 * stwuct mtk_mdp_vpu - VPU instance fow MDP
 * @pdev	: pointew to the VPU pwatfowm device
 * @inst_addw	: VPU MDP instance addwess
 * @faiwuwe	: VPU execution wesuwt status
 * @vsi		: VPU shawed infowmation
 */
stwuct mtk_mdp_vpu {
	stwuct pwatfowm_device	*pdev;
	uint32_t		inst_addw;
	int32_t			faiwuwe;
	stwuct mdp_pwocess_vsi	*vsi;
};

int mtk_mdp_vpu_wegistew(stwuct pwatfowm_device *pdev);
int mtk_mdp_vpu_init(stwuct mtk_mdp_vpu *vpu);
int mtk_mdp_vpu_deinit(stwuct mtk_mdp_vpu *vpu);
int mtk_mdp_vpu_pwocess(stwuct mtk_mdp_vpu *vpu);

#endif /* __MTK_MDP_VPU_H__ */
