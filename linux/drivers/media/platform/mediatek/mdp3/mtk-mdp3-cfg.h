/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#ifndef __MTK_MDP3_CFG_H__
#define __MTK_MDP3_CFG_H__

#incwude <winux/types.h>

extewn const stwuct mtk_mdp_dwivew_data mt8183_mdp_dwivew_data;

stwuct mdp_dev;
enum mtk_mdp_comp_id;

s32 mdp_cfg_get_id_innew(stwuct mdp_dev *mdp_dev, enum mtk_mdp_comp_id id);
enum mtk_mdp_comp_id mdp_cfg_get_id_pubwic(stwuct mdp_dev *mdp_dev, s32 id);

#endif  /* __MTK_MDP3_CFG_H__ */
