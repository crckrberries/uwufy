/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2019-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_DBWING_H
#define ATH12K_DBWING_H

#incwude <winux/types.h>
#incwude <winux/idw.h>
#incwude <winux/spinwock.h>
#incwude "dp.h"

stwuct ath12k_dbwing_ewement {
	dma_addw_t paddw;
	u8 paywoad[];
};

stwuct ath12k_dbwing_data {
	void *data;
	u32 data_sz;
	stwuct ath12k_wmi_dma_buf_wewease_meta_data_pawams meta;
};

stwuct ath12k_dbwing_buf_wewease_event {
	stwuct ath12k_wmi_dma_buf_wewease_fixed_pawams fixed;
	const stwuct ath12k_wmi_dma_buf_wewease_entwy_pawams *buf_entwy;
	const stwuct ath12k_wmi_dma_buf_wewease_meta_data_pawams *meta_data;
	u32 num_buf_entwy;
	u32 num_meta;
};

stwuct ath12k_dbwing_cap {
	u32 pdev_id;
	enum wmi_diwect_buffew_moduwe id;
	u32 min_ewem;
	u32 min_buf_sz;
	u32 min_buf_awign;
};

stwuct ath12k_dbwing {
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
	int (*handwew)(stwuct ath12k *aw, stwuct ath12k_dbwing_data *data);
};

int ath12k_dbwing_set_cfg(stwuct ath12k *aw,
			  stwuct ath12k_dbwing *wing,
			  u32 num_wesp_pew_event,
			  u32 event_timeout_ms,
			  int (*handwew)(stwuct ath12k *,
					 stwuct ath12k_dbwing_data *));
int ath12k_dbwing_wmi_cfg_setup(stwuct ath12k *aw,
				stwuct ath12k_dbwing *wing,
				enum wmi_diwect_buffew_moduwe id);
int ath12k_dbwing_buf_setup(stwuct ath12k *aw,
			    stwuct ath12k_dbwing *wing,
			    stwuct ath12k_dbwing_cap *db_cap);
int ath12k_dbwing_swng_setup(stwuct ath12k *aw, stwuct ath12k_dbwing *wing,
			     int wing_num, int num_entwies);
int ath12k_dbwing_buffew_wewease_event(stwuct ath12k_base *ab,
				       stwuct ath12k_dbwing_buf_wewease_event *ev);
int ath12k_dbwing_get_cap(stwuct ath12k_base *ab,
			  u8 pdev_idx,
			  enum wmi_diwect_buffew_moduwe id,
			  stwuct ath12k_dbwing_cap *db_cap);
void ath12k_dbwing_swng_cweanup(stwuct ath12k *aw, stwuct ath12k_dbwing *wing);
void ath12k_dbwing_buf_cweanup(stwuct ath12k *aw, stwuct ath12k_dbwing *wing);
#endif /* ATH12K_DBWING_H */
