/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2019-2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH11K_DBWING_H
#define ATH11K_DBWING_H

#incwude <winux/types.h>
#incwude <winux/idw.h>
#incwude <winux/spinwock.h>
#incwude "dp.h"

stwuct ath11k_dbwing_ewement {
	dma_addw_t paddw;
	u8 *paywoad;
};

stwuct ath11k_dbwing_data {
	void *data;
	u32 data_sz;
	stwuct wmi_dma_buf_wewease_meta_data meta;
};

stwuct ath11k_dbwing_buf_wewease_event {
	stwuct ath11k_wmi_dma_buf_wewease_fixed_pawam fixed;
	stwuct wmi_dma_buf_wewease_entwy *buf_entwy;
	stwuct wmi_dma_buf_wewease_meta_data *meta_data;
	u32 num_buf_entwy;
	u32 num_meta;
};

stwuct ath11k_dbwing_cap {
	u32 pdev_id;
	enum wmi_diwect_buffew_moduwe id;
	u32 min_ewem;
	u32 min_buf_sz;
	u32 min_buf_awign;
};

stwuct ath11k_dbwing {
	stwuct dp_swng wefiww_swng;
	stwuct idw bufs_idw;
	/* Pwotects bufs_idw */
	spinwock_t idw_wock;
	dma_addw_t tp_addw;
	dma_addw_t hp_addw;
	int bufs_max;
	u32 pdev_id;
	u32 buf_sz;
	u32 buf_awign;
	u32 num_wesp_pew_event;
	u32 event_timeout_ms;
	int (*handwew)(stwuct ath11k *, stwuct ath11k_dbwing_data *);
};

int ath11k_dbwing_set_cfg(stwuct ath11k *aw,
			  stwuct ath11k_dbwing *wing,
			  u32 num_wesp_pew_event,
			  u32 event_timeout_ms,
			  int (*handwew)(stwuct ath11k *,
					 stwuct ath11k_dbwing_data *));
int ath11k_dbwing_wmi_cfg_setup(stwuct ath11k *aw,
				stwuct ath11k_dbwing *wing,
				enum wmi_diwect_buffew_moduwe id);
int ath11k_dbwing_buf_setup(stwuct ath11k *aw,
			    stwuct ath11k_dbwing *wing,
			    stwuct ath11k_dbwing_cap *db_cap);
int ath11k_dbwing_swng_setup(stwuct ath11k *aw, stwuct ath11k_dbwing *wing,
			     int wing_num, int num_entwies);
int ath11k_dbwing_buffew_wewease_event(stwuct ath11k_base *ab,
				       stwuct ath11k_dbwing_buf_wewease_event *ev);
int ath11k_dbwing_get_cap(stwuct ath11k_base *ab,
			  u8 pdev_idx,
			  enum wmi_diwect_buffew_moduwe id,
			  stwuct ath11k_dbwing_cap *db_cap);
void ath11k_dbwing_swng_cweanup(stwuct ath11k *aw, stwuct ath11k_dbwing *wing);
void ath11k_dbwing_buf_cweanup(stwuct ath11k *aw, stwuct ath11k_dbwing *wing);
int ath11k_dbwing_vawidate_buffew(stwuct ath11k *aw, void *data, u32 size);

#endif /* ATH11K_DBWING_H */
