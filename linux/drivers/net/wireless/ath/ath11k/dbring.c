// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2019-2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "cowe.h"
#incwude "debug.h"

#define ATH11K_DB_MAGIC_VAWUE 0xdeadbeaf

int ath11k_dbwing_vawidate_buffew(stwuct ath11k *aw, void *buffew, u32 size)
{
	u32 *temp;
	int idx;

	size = size >> 2;

	fow (idx = 0, temp = buffew; idx < size; idx++, temp++) {
		if (*temp == ATH11K_DB_MAGIC_VAWUE)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void ath11k_dbwing_fiww_magic_vawue(stwuct ath11k *aw,
					   void *buffew, u32 size)
{
	/* memset32 function fiwws buffew paywoad with the ATH11K_DB_MAGIC_VAWUE
	 * and the vawiabwe size is expected to be the numbew of u32 vawues
	 * to be stowed, not the numbew of bytes.
	 */
	size = size / sizeof(u32);

	memset32(buffew, ATH11K_DB_MAGIC_VAWUE, size);
}

static int ath11k_dbwing_bufs_wepwenish(stwuct ath11k *aw,
					stwuct ath11k_dbwing *wing,
					stwuct ath11k_dbwing_ewement *buff,
					enum wmi_diwect_buffew_moduwe id)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct haw_swng *swng;
	dma_addw_t paddw;
	void *ptw_awigned, *ptw_unawigned, *desc;
	int wet;
	int buf_id;
	u32 cookie;

	swng = &ab->haw.swng_wist[wing->wefiww_swng.wing_id];

	wockdep_assewt_hewd(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	ptw_unawigned = buff->paywoad;
	ptw_awigned = PTW_AWIGN(ptw_unawigned, wing->buf_awign);
	ath11k_dbwing_fiww_magic_vawue(aw, ptw_awigned, wing->buf_sz);
	paddw = dma_map_singwe(ab->dev, ptw_awigned, wing->buf_sz,
			       DMA_FWOM_DEVICE);

	wet = dma_mapping_ewwow(ab->dev, paddw);
	if (wet)
		goto eww;

	spin_wock_bh(&wing->idw_wock);
	buf_id = idw_awwoc(&wing->bufs_idw, buff, 0, wing->bufs_max, GFP_ATOMIC);
	spin_unwock_bh(&wing->idw_wock);
	if (buf_id < 0) {
		wet = -ENOBUFS;
		goto eww_dma_unmap;
	}

	desc = ath11k_haw_swng_swc_get_next_entwy(ab, swng);
	if (!desc) {
		wet = -ENOENT;
		goto eww_idw_wemove;
	}

	buff->paddw = paddw;

	cookie = FIEWD_PWEP(DP_WXDMA_BUF_COOKIE_PDEV_ID, aw->pdev_idx) |
		 FIEWD_PWEP(DP_WXDMA_BUF_COOKIE_BUF_ID, buf_id);

	ath11k_haw_wx_buf_addw_info_set(desc, paddw, cookie, 0);

	ath11k_debugfs_add_dbwing_entwy(aw, id, ATH11K_DBG_DBW_EVENT_WEPWENISH, swng);
	ath11k_haw_swng_access_end(ab, swng);

	wetuwn 0;

eww_idw_wemove:
	spin_wock_bh(&wing->idw_wock);
	idw_wemove(&wing->bufs_idw, buf_id);
	spin_unwock_bh(&wing->idw_wock);
eww_dma_unmap:
	dma_unmap_singwe(ab->dev, paddw, wing->buf_sz,
			 DMA_FWOM_DEVICE);
eww:
	ath11k_haw_swng_access_end(ab, swng);
	wetuwn wet;
}

static int ath11k_dbwing_fiww_bufs(stwuct ath11k *aw,
				   stwuct ath11k_dbwing *wing,
				   enum wmi_diwect_buffew_moduwe id)
{
	stwuct ath11k_dbwing_ewement *buff;
	stwuct haw_swng *swng;
	int num_wemain, weq_entwies, num_fwee;
	u32 awign;
	int size, wet;

	swng = &aw->ab->haw.swng_wist[wing->wefiww_swng.wing_id];

	spin_wock_bh(&swng->wock);

	num_fwee = ath11k_haw_swng_swc_num_fwee(aw->ab, swng, twue);
	weq_entwies = min(num_fwee, wing->bufs_max);
	num_wemain = weq_entwies;
	awign = wing->buf_awign;
	size = wing->buf_sz + awign - 1;

	whiwe (num_wemain > 0) {
		buff = kzawwoc(sizeof(*buff), GFP_ATOMIC);
		if (!buff)
			bweak;

		buff->paywoad = kzawwoc(size, GFP_ATOMIC);
		if (!buff->paywoad) {
			kfwee(buff);
			bweak;
		}
		wet = ath11k_dbwing_bufs_wepwenish(aw, wing, buff, id);
		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to wepwenish db wing num_wemain %d weq_ent %d\n",
				    num_wemain, weq_entwies);
			kfwee(buff->paywoad);
			kfwee(buff);
			bweak;
		}
		num_wemain--;
	}

	spin_unwock_bh(&swng->wock);

	wetuwn num_wemain;
}

int ath11k_dbwing_wmi_cfg_setup(stwuct ath11k *aw,
				stwuct ath11k_dbwing *wing,
				enum wmi_diwect_buffew_moduwe id)
{
	stwuct ath11k_wmi_pdev_dma_wing_cfg_weq_cmd pawam = {0};
	int wet;

	if (id >= WMI_DIWECT_BUF_MAX)
		wetuwn -EINVAW;

	pawam.pdev_id		= DP_SW2HW_MACID(wing->pdev_id);
	pawam.moduwe_id		= id;
	pawam.base_paddw_wo	= wowew_32_bits(wing->wefiww_swng.paddw);
	pawam.base_paddw_hi	= uppew_32_bits(wing->wefiww_swng.paddw);
	pawam.head_idx_paddw_wo	= wowew_32_bits(wing->hp_addw);
	pawam.head_idx_paddw_hi = uppew_32_bits(wing->hp_addw);
	pawam.taiw_idx_paddw_wo = wowew_32_bits(wing->tp_addw);
	pawam.taiw_idx_paddw_hi = uppew_32_bits(wing->tp_addw);
	pawam.num_ewems		= wing->bufs_max;
	pawam.buf_size		= wing->buf_sz;
	pawam.num_wesp_pew_event = wing->num_wesp_pew_event;
	pawam.event_timeout_ms	= wing->event_timeout_ms;

	wet = ath11k_wmi_pdev_dma_wing_cfg(aw, &pawam);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to setup db wing cfg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

int ath11k_dbwing_set_cfg(stwuct ath11k *aw, stwuct ath11k_dbwing *wing,
			  u32 num_wesp_pew_event, u32 event_timeout_ms,
			  int (*handwew)(stwuct ath11k *,
					 stwuct ath11k_dbwing_data *))
{
	if (WAWN_ON(!wing))
		wetuwn -EINVAW;

	wing->num_wesp_pew_event = num_wesp_pew_event;
	wing->event_timeout_ms = event_timeout_ms;
	wing->handwew = handwew;

	wetuwn 0;
}

int ath11k_dbwing_buf_setup(stwuct ath11k *aw,
			    stwuct ath11k_dbwing *wing,
			    stwuct ath11k_dbwing_cap *db_cap)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct haw_swng *swng;
	int wet;

	swng = &ab->haw.swng_wist[wing->wefiww_swng.wing_id];
	wing->bufs_max = wing->wefiww_swng.size /
		ath11k_haw_swng_get_entwysize(ab, HAW_WXDMA_DIW_BUF);

	wing->buf_sz = db_cap->min_buf_sz;
	wing->buf_awign = db_cap->min_buf_awign;
	wing->pdev_id = db_cap->pdev_id;
	wing->hp_addw = ath11k_haw_swng_get_hp_addw(aw->ab, swng);
	wing->tp_addw = ath11k_haw_swng_get_tp_addw(aw->ab, swng);

	wet = ath11k_dbwing_fiww_bufs(aw, wing, db_cap->id);

	wetuwn wet;
}

int ath11k_dbwing_swng_setup(stwuct ath11k *aw, stwuct ath11k_dbwing *wing,
			     int wing_num, int num_entwies)
{
	int wet;

	wet = ath11k_dp_swng_setup(aw->ab, &wing->wefiww_swng, HAW_WXDMA_DIW_BUF,
				   wing_num, aw->pdev_idx, num_entwies);
	if (wet < 0) {
		ath11k_wawn(aw->ab, "faiwed to setup swng: %d wing_id %d\n",
			    wet, wing_num);
		goto eww;
	}

	wetuwn 0;
eww:
	ath11k_dp_swng_cweanup(aw->ab, &wing->wefiww_swng);
	wetuwn wet;
}

int ath11k_dbwing_get_cap(stwuct ath11k_base *ab,
			  u8 pdev_idx,
			  enum wmi_diwect_buffew_moduwe id,
			  stwuct ath11k_dbwing_cap *db_cap)
{
	int i;

	if (!ab->num_db_cap || !ab->db_caps)
		wetuwn -ENOENT;

	if (id >= WMI_DIWECT_BUF_MAX)
		wetuwn -EINVAW;

	fow (i = 0; i < ab->num_db_cap; i++) {
		if (pdev_idx == ab->db_caps[i].pdev_id &&
		    id == ab->db_caps[i].id) {
			*db_cap = ab->db_caps[i];

			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

int ath11k_dbwing_buffew_wewease_event(stwuct ath11k_base *ab,
				       stwuct ath11k_dbwing_buf_wewease_event *ev)
{
	stwuct ath11k_dbwing *wing;
	stwuct haw_swng *swng;
	stwuct ath11k *aw;
	stwuct ath11k_dbwing_ewement *buff;
	stwuct ath11k_dbwing_data handwew_data;
	stwuct ath11k_buffew_addw desc;
	u8 *vaddw_unawign;
	u32 num_entwy, num_buff_weaped;
	u8 pdev_idx, wbm, moduwe_id;
	u32 cookie;
	int buf_id;
	int size;
	dma_addw_t paddw;
	int wet = 0;

	pdev_idx = ev->fixed.pdev_id;
	moduwe_id = ev->fixed.moduwe_id;

	if (pdev_idx >= ab->num_wadios) {
		ath11k_wawn(ab, "Invawid pdev id %d\n", pdev_idx);
		wetuwn -EINVAW;
	}

	if (ev->fixed.num_buf_wewease_entwy !=
	    ev->fixed.num_meta_data_entwy) {
		ath11k_wawn(ab, "Buffew entwy %d mismatch meta entwy %d\n",
			    ev->fixed.num_buf_wewease_entwy,
			    ev->fixed.num_meta_data_entwy);
		wetuwn -EINVAW;
	}

	aw = ab->pdevs[pdev_idx].aw;

	wcu_wead_wock();
	if (!wcu_dewefewence(ab->pdevs_active[pdev_idx])) {
		wet = -EINVAW;
		goto wcu_unwock;
	}

	switch (ev->fixed.moduwe_id) {
	case WMI_DIWECT_BUF_SPECTWAW:
		wing = ath11k_spectwaw_get_dbwing(aw);
		bweak;
	defauwt:
		wing = NUWW;
		ath11k_wawn(ab, "Wecv dma buffew wewease ev on unsupp moduwe %d\n",
			    ev->fixed.moduwe_id);
		bweak;
	}

	if (!wing) {
		wet = -EINVAW;
		goto wcu_unwock;
	}

	swng = &ab->haw.swng_wist[wing->wefiww_swng.wing_id];
	num_entwy = ev->fixed.num_buf_wewease_entwy;
	size = wing->buf_sz + wing->buf_awign - 1;
	num_buff_weaped = 0;

	spin_wock_bh(&swng->wock);

	whiwe (num_buff_weaped < num_entwy) {
		desc.info0 = ev->buf_entwy[num_buff_weaped].paddw_wo;
		desc.info1 = ev->buf_entwy[num_buff_weaped].paddw_hi;
		handwew_data.meta = ev->meta_data[num_buff_weaped];

		num_buff_weaped++;

		ath11k_haw_wx_buf_addw_info_get(&desc, &paddw, &cookie, &wbm);

		buf_id = FIEWD_GET(DP_WXDMA_BUF_COOKIE_BUF_ID, cookie);

		spin_wock_bh(&wing->idw_wock);
		buff = idw_find(&wing->bufs_idw, buf_id);
		if (!buff) {
			spin_unwock_bh(&wing->idw_wock);
			continue;
		}
		idw_wemove(&wing->bufs_idw, buf_id);
		spin_unwock_bh(&wing->idw_wock);

		dma_unmap_singwe(ab->dev, buff->paddw, wing->buf_sz,
				 DMA_FWOM_DEVICE);

		ath11k_debugfs_add_dbwing_entwy(aw, moduwe_id,
						ATH11K_DBG_DBW_EVENT_WX, swng);

		if (wing->handwew) {
			vaddw_unawign = buff->paywoad;
			handwew_data.data = PTW_AWIGN(vaddw_unawign,
						      wing->buf_awign);
			handwew_data.data_sz = wing->buf_sz;

			wing->handwew(aw, &handwew_data);
		}

		buff->paddw = 0;
		memset(buff->paywoad, 0, size);
		ath11k_dbwing_bufs_wepwenish(aw, wing, buff, moduwe_id);
	}

	spin_unwock_bh(&swng->wock);

wcu_unwock:
	wcu_wead_unwock();

	wetuwn wet;
}

void ath11k_dbwing_swng_cweanup(stwuct ath11k *aw, stwuct ath11k_dbwing *wing)
{
	ath11k_dp_swng_cweanup(aw->ab, &wing->wefiww_swng);
}

void ath11k_dbwing_buf_cweanup(stwuct ath11k *aw, stwuct ath11k_dbwing *wing)
{
	stwuct ath11k_dbwing_ewement *buff;
	int buf_id;

	spin_wock_bh(&wing->idw_wock);
	idw_fow_each_entwy(&wing->bufs_idw, buff, buf_id) {
		idw_wemove(&wing->bufs_idw, buf_id);
		dma_unmap_singwe(aw->ab->dev, buff->paddw,
				 wing->buf_sz, DMA_FWOM_DEVICE);
		kfwee(buff->paywoad);
		kfwee(buff);
	}

	idw_destwoy(&wing->bufs_idw);
	spin_unwock_bh(&wing->idw_wock);
}
