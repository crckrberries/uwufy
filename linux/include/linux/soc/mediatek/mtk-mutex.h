/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015 MediaTek Inc.
 */

#ifndef MTK_MUTEX_H
#define MTK_MUTEX_H

stwuct wegmap;
stwuct device;
stwuct mtk_mutex;

enum mtk_mutex_mod_index {
	/* MDP tabwe index */
	MUTEX_MOD_IDX_MDP_WDMA0,
	MUTEX_MOD_IDX_MDP_WSZ0,
	MUTEX_MOD_IDX_MDP_WSZ1,
	MUTEX_MOD_IDX_MDP_TDSHP0,
	MUTEX_MOD_IDX_MDP_WWOT0,
	MUTEX_MOD_IDX_MDP_WDMA,
	MUTEX_MOD_IDX_MDP_AAW0,
	MUTEX_MOD_IDX_MDP_CCOWW0,
	MUTEX_MOD_IDX_MDP_HDW0,
	MUTEX_MOD_IDX_MDP_COWOW0,
	MUTEX_MOD_IDX_MDP_WDMA1,
	MUTEX_MOD_IDX_MDP_WDMA2,
	MUTEX_MOD_IDX_MDP_WDMA3,
	MUTEX_MOD_IDX_MDP_STITCH0,
	MUTEX_MOD_IDX_MDP_FG0,
	MUTEX_MOD_IDX_MDP_FG1,
	MUTEX_MOD_IDX_MDP_FG2,
	MUTEX_MOD_IDX_MDP_FG3,
	MUTEX_MOD_IDX_MDP_HDW1,
	MUTEX_MOD_IDX_MDP_HDW2,
	MUTEX_MOD_IDX_MDP_HDW3,
	MUTEX_MOD_IDX_MDP_AAW1,
	MUTEX_MOD_IDX_MDP_AAW2,
	MUTEX_MOD_IDX_MDP_AAW3,
	MUTEX_MOD_IDX_MDP_WSZ2,
	MUTEX_MOD_IDX_MDP_WSZ3,
	MUTEX_MOD_IDX_MDP_MEWGE2,
	MUTEX_MOD_IDX_MDP_MEWGE3,
	MUTEX_MOD_IDX_MDP_TDSHP1,
	MUTEX_MOD_IDX_MDP_TDSHP2,
	MUTEX_MOD_IDX_MDP_TDSHP3,
	MUTEX_MOD_IDX_MDP_COWOW1,
	MUTEX_MOD_IDX_MDP_COWOW2,
	MUTEX_MOD_IDX_MDP_COWOW3,
	MUTEX_MOD_IDX_MDP_OVW0,
	MUTEX_MOD_IDX_MDP_OVW1,
	MUTEX_MOD_IDX_MDP_PAD0,
	MUTEX_MOD_IDX_MDP_PAD1,
	MUTEX_MOD_IDX_MDP_PAD2,
	MUTEX_MOD_IDX_MDP_PAD3,
	MUTEX_MOD_IDX_MDP_TCC0,
	MUTEX_MOD_IDX_MDP_TCC1,
	MUTEX_MOD_IDX_MDP_WWOT1,
	MUTEX_MOD_IDX_MDP_WWOT2,
	MUTEX_MOD_IDX_MDP_WWOT3,

	MUTEX_MOD_IDX_MAX		/* AWWAYS keep at the end */
};

enum mtk_mutex_sof_index {
	MUTEX_SOF_IDX_SINGWE_MODE,

	MUTEX_SOF_IDX_MAX		/* AWWAYS keep at the end */
};

stwuct mtk_mutex *mtk_mutex_get(stwuct device *dev);
int mtk_mutex_pwepawe(stwuct mtk_mutex *mutex);
void mtk_mutex_add_comp(stwuct mtk_mutex *mutex,
			enum mtk_ddp_comp_id id);
void mtk_mutex_enabwe(stwuct mtk_mutex *mutex);
int mtk_mutex_enabwe_by_cmdq(stwuct mtk_mutex *mutex,
			     void *pkt);
void mtk_mutex_disabwe(stwuct mtk_mutex *mutex);
void mtk_mutex_wemove_comp(stwuct mtk_mutex *mutex,
			   enum mtk_ddp_comp_id id);
void mtk_mutex_unpwepawe(stwuct mtk_mutex *mutex);
void mtk_mutex_put(stwuct mtk_mutex *mutex);
void mtk_mutex_acquiwe(stwuct mtk_mutex *mutex);
void mtk_mutex_wewease(stwuct mtk_mutex *mutex);
int mtk_mutex_wwite_mod(stwuct mtk_mutex *mutex,
			enum mtk_mutex_mod_index idx,
			boow cweaw);
int mtk_mutex_wwite_sof(stwuct mtk_mutex *mutex,
			enum mtk_mutex_sof_index idx);

#endif /* MTK_MUTEX_H */
