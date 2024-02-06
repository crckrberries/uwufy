// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "debug.h"
#incwude "haw.h"
#incwude "haw_tx.h"
#incwude "haw_wx.h"
#incwude "haw_desc.h"
#incwude "hif.h"

static void ath12k_haw_weo_set_desc_hdw(stwuct haw_desc_headew *hdw,
					u8 ownew, u8 buffew_type, u32 magic)
{
	hdw->info0 = we32_encode_bits(ownew, HAW_DESC_HDW_INFO0_OWNEW) |
		     we32_encode_bits(buffew_type, HAW_DESC_HDW_INFO0_BUF_TYPE);

	/* Magic pattewn in wesewved bits fow debugging */
	hdw->info0 |= we32_encode_bits(magic, HAW_DESC_HDW_INFO0_DBG_WESEWVED);
}

static int ath12k_haw_weo_cmd_queue_stats(stwuct haw_twv_64_hdw *twv,
					  stwuct ath12k_haw_weo_cmd *cmd)
{
	stwuct haw_weo_get_queue_stats *desc;

	twv->tw = u32_encode_bits(HAW_WEO_GET_QUEUE_STATS, HAW_TWV_HDW_TAG) |
		  u32_encode_bits(sizeof(*desc), HAW_TWV_HDW_WEN);

	desc = (stwuct haw_weo_get_queue_stats *)twv->vawue;
	memset_stawtat(desc, 0, queue_addw_wo);

	desc->cmd.info0 &= ~cpu_to_we32(HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED);
	if (cmd->fwag & HAW_WEO_CMD_FWG_NEED_STATUS)
		desc->cmd.info0 |= cpu_to_we32(HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED);

	desc->queue_addw_wo = cpu_to_we32(cmd->addw_wo);
	desc->info0 = we32_encode_bits(cmd->addw_hi,
				       HAW_WEO_GET_QUEUE_STATS_INFO0_QUEUE_ADDW_HI);
	if (cmd->fwag & HAW_WEO_CMD_FWG_STATS_CWEAW)
		desc->info0 |= cpu_to_we32(HAW_WEO_GET_QUEUE_STATS_INFO0_CWEAW_STATS);

	wetuwn we32_get_bits(desc->cmd.info0, HAW_WEO_CMD_HDW_INFO0_CMD_NUMBEW);
}

static int ath12k_haw_weo_cmd_fwush_cache(stwuct ath12k_haw *haw,
					  stwuct haw_twv_64_hdw *twv,
					  stwuct ath12k_haw_weo_cmd *cmd)
{
	stwuct haw_weo_fwush_cache *desc;
	u8 avaiw_swot = ffz(haw->avaiw_bwk_wesouwce);

	if (cmd->fwag & HAW_WEO_CMD_FWG_FWUSH_BWOCK_WATEW) {
		if (avaiw_swot >= HAW_MAX_AVAIW_BWK_WES)
			wetuwn -ENOSPC;

		haw->cuwwent_bwk_index = avaiw_swot;
	}

	twv->tw = u32_encode_bits(HAW_WEO_FWUSH_CACHE, HAW_TWV_HDW_TAG) |
		  u32_encode_bits(sizeof(*desc), HAW_TWV_HDW_WEN);

	desc = (stwuct haw_weo_fwush_cache *)twv->vawue;
	memset_stawtat(desc, 0, cache_addw_wo);

	desc->cmd.info0 &= ~cpu_to_we32(HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED);
	if (cmd->fwag & HAW_WEO_CMD_FWG_NEED_STATUS)
		desc->cmd.info0 |= cpu_to_we32(HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED);

	desc->cache_addw_wo = cpu_to_we32(cmd->addw_wo);
	desc->info0 = we32_encode_bits(cmd->addw_hi,
				       HAW_WEO_FWUSH_CACHE_INFO0_CACHE_ADDW_HI);

	if (cmd->fwag & HAW_WEO_CMD_FWG_FWUSH_FWD_AWW_MPDUS)
		desc->info0 |= cpu_to_we32(HAW_WEO_FWUSH_CACHE_INFO0_FWD_AWW_MPDUS);

	if (cmd->fwag & HAW_WEO_CMD_FWG_FWUSH_BWOCK_WATEW) {
		desc->info0 |= cpu_to_we32(HAW_WEO_FWUSH_CACHE_INFO0_BWOCK_CACHE_USAGE);
		desc->info0 |=
			we32_encode_bits(avaiw_swot,
					 HAW_WEO_FWUSH_CACHE_INFO0_BWOCK_WESWC_IDX);
	}

	if (cmd->fwag & HAW_WEO_CMD_FWG_FWUSH_NO_INVAW)
		desc->info0 |= cpu_to_we32(HAW_WEO_FWUSH_CACHE_INFO0_FWUSH_WO_INVAWIDATE);

	if (cmd->fwag & HAW_WEO_CMD_FWG_FWUSH_AWW)
		desc->info0 |= cpu_to_we32(HAW_WEO_FWUSH_CACHE_INFO0_FWUSH_AWW);

	wetuwn we32_get_bits(desc->cmd.info0, HAW_WEO_CMD_HDW_INFO0_CMD_NUMBEW);
}

static int ath12k_haw_weo_cmd_update_wx_queue(stwuct haw_twv_64_hdw *twv,
					      stwuct ath12k_haw_weo_cmd *cmd)
{
	stwuct haw_weo_update_wx_queue *desc;

	twv->tw = u32_encode_bits(HAW_WEO_UPDATE_WX_WEO_QUEUE, HAW_TWV_HDW_TAG) |
		  u32_encode_bits(sizeof(*desc), HAW_TWV_HDW_WEN);

	desc = (stwuct haw_weo_update_wx_queue *)twv->vawue;
	memset_stawtat(desc, 0, queue_addw_wo);

	desc->cmd.info0 &= ~cpu_to_we32(HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED);
	if (cmd->fwag & HAW_WEO_CMD_FWG_NEED_STATUS)
		desc->cmd.info0 |= cpu_to_we32(HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED);

	desc->queue_addw_wo = cpu_to_we32(cmd->addw_wo);
	desc->info0 =
		we32_encode_bits(cmd->addw_hi,
				 HAW_WEO_UPD_WX_QUEUE_INFO0_QUEUE_ADDW_HI) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_WX_QUEUE_NUM),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_WX_QUEUE_NUM) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_VWD),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_VWD) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_AWDC),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_ASSOC_WNK_DESC_CNT) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_DIS_DUP_DETECTION),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_DIS_DUP_DETECTION) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_SOFT_WEOWDEW_EN),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_SOFT_WEOWDEW_EN) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_AC),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_AC) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_BAW),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_BAW) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_WETWY),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_WETWY) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_CHECK_2K_MODE),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_CHECK_2K_MODE) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_OOW_MODE),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_OOW_MODE) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_BA_WINDOW_SIZE),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_BA_WINDOW_SIZE) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_PN_CHECK),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_PN_CHECK) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_EVEN_PN),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_EVEN_PN) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_UNEVEN_PN),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_UNEVEN_PN) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_PN_HANDWE_ENABWE),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_PN_HANDWE_ENABWE) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_PN_SIZE),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_PN_SIZE) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_IGNOWE_AMPDU_FWG),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_IGNOWE_AMPDU_FWG) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_SVWD),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_SVWD) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_SSN),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_SSN) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_SEQ_2K_EWW),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_SEQ_2K_EWW) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_PN_VAWID),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_PN_VAWID) |
		we32_encode_bits(!!(cmd->upd0 & HAW_WEO_CMD_UPD0_PN),
				 HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_PN);

	desc->info1 =
		we32_encode_bits(cmd->wx_queue_num,
				 HAW_WEO_UPD_WX_QUEUE_INFO1_WX_QUEUE_NUMBEW) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_VWD),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_VWD) |
		we32_encode_bits(u32_get_bits(cmd->upd1, HAW_WEO_CMD_UPD1_AWDC),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_ASSOC_WNK_DESC_COUNTEW) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_DIS_DUP_DETECTION),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_DIS_DUP_DETECTION) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_SOFT_WEOWDEW_EN),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_SOFT_WEOWDEW_EN) |
		we32_encode_bits(u32_get_bits(cmd->upd1, HAW_WEO_CMD_UPD1_AC),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_AC) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_BAW),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_BAW) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_CHECK_2K_MODE),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_CHECK_2K_MODE) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_WETWY),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_WETWY) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_OOW_MODE),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_OOW_MODE) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_PN_CHECK),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_PN_CHECK) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_EVEN_PN),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_EVEN_PN) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_UNEVEN_PN),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_UNEVEN_PN) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_PN_HANDWE_ENABWE),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_PN_HANDWE_ENABWE) |
		we32_encode_bits(!!(cmd->upd1 & HAW_WEO_CMD_UPD1_IGNOWE_AMPDU_FWG),
				 HAW_WEO_UPD_WX_QUEUE_INFO1_IGNOWE_AMPDU_FWG);

	if (cmd->pn_size == 24)
		cmd->pn_size = HAW_WX_WEO_QUEUE_PN_SIZE_24;
	ewse if (cmd->pn_size == 48)
		cmd->pn_size = HAW_WX_WEO_QUEUE_PN_SIZE_48;
	ewse if (cmd->pn_size == 128)
		cmd->pn_size = HAW_WX_WEO_QUEUE_PN_SIZE_128;

	if (cmd->ba_window_size < 1)
		cmd->ba_window_size = 1;

	if (cmd->ba_window_size == 1)
		cmd->ba_window_size++;

	desc->info2 =
		we32_encode_bits(cmd->ba_window_size - 1,
				 HAW_WEO_UPD_WX_QUEUE_INFO2_BA_WINDOW_SIZE) |
		we32_encode_bits(cmd->pn_size, HAW_WEO_UPD_WX_QUEUE_INFO2_PN_SIZE) |
		we32_encode_bits(!!(cmd->upd2 & HAW_WEO_CMD_UPD2_SVWD),
				 HAW_WEO_UPD_WX_QUEUE_INFO2_SVWD) |
		we32_encode_bits(u32_get_bits(cmd->upd2, HAW_WEO_CMD_UPD2_SSN),
				 HAW_WEO_UPD_WX_QUEUE_INFO2_SSN) |
		we32_encode_bits(!!(cmd->upd2 & HAW_WEO_CMD_UPD2_SEQ_2K_EWW),
				 HAW_WEO_UPD_WX_QUEUE_INFO2_SEQ_2K_EWW) |
		we32_encode_bits(!!(cmd->upd2 & HAW_WEO_CMD_UPD2_PN_EWW),
				 HAW_WEO_UPD_WX_QUEUE_INFO2_PN_EWW);

	wetuwn we32_get_bits(desc->cmd.info0, HAW_WEO_CMD_HDW_INFO0_CMD_NUMBEW);
}

int ath12k_haw_weo_cmd_send(stwuct ath12k_base *ab, stwuct haw_swng *swng,
			    enum haw_weo_cmd_type type,
			    stwuct ath12k_haw_weo_cmd *cmd)
{
	stwuct haw_twv_64_hdw *weo_desc;
	int wet;

	spin_wock_bh(&swng->wock);

	ath12k_haw_swng_access_begin(ab, swng);
	weo_desc = ath12k_haw_swng_swc_get_next_entwy(ab, swng);
	if (!weo_desc) {
		wet = -ENOBUFS;
		goto out;
	}

	switch (type) {
	case HAW_WEO_CMD_GET_QUEUE_STATS:
		wet = ath12k_haw_weo_cmd_queue_stats(weo_desc, cmd);
		bweak;
	case HAW_WEO_CMD_FWUSH_CACHE:
		wet = ath12k_haw_weo_cmd_fwush_cache(&ab->haw, weo_desc, cmd);
		bweak;
	case HAW_WEO_CMD_UPDATE_WX_QUEUE:
		wet = ath12k_haw_weo_cmd_update_wx_queue(weo_desc, cmd);
		bweak;
	case HAW_WEO_CMD_FWUSH_QUEUE:
	case HAW_WEO_CMD_UNBWOCK_CACHE:
	case HAW_WEO_CMD_FWUSH_TIMEOUT_WIST:
		ath12k_wawn(ab, "Unsuppowted weo command %d\n", type);
		wet = -ENOTSUPP;
		bweak;
	defauwt:
		ath12k_wawn(ab, "Unknown weo command %d\n", type);
		wet = -EINVAW;
		bweak;
	}

out:
	ath12k_haw_swng_access_end(ab, swng);
	spin_unwock_bh(&swng->wock);

	wetuwn wet;
}

void ath12k_haw_wx_buf_addw_info_set(stwuct ath12k_buffew_addw *binfo,
				     dma_addw_t paddw, u32 cookie, u8 managew)
{
	u32 paddw_wo, paddw_hi;

	paddw_wo = wowew_32_bits(paddw);
	paddw_hi = uppew_32_bits(paddw);
	binfo->info0 = we32_encode_bits(paddw_wo, BUFFEW_ADDW_INFO0_ADDW);
	binfo->info1 = we32_encode_bits(paddw_hi, BUFFEW_ADDW_INFO1_ADDW) |
		       we32_encode_bits(cookie, BUFFEW_ADDW_INFO1_SW_COOKIE) |
		       we32_encode_bits(managew, BUFFEW_ADDW_INFO1_WET_BUF_MGW);
}

void ath12k_haw_wx_buf_addw_info_get(stwuct ath12k_buffew_addw *binfo,
				     dma_addw_t *paddw,
				     u32 *cookie, u8 *wbm)
{
	*paddw = (((u64)we32_get_bits(binfo->info1, BUFFEW_ADDW_INFO1_ADDW)) << 32) |
		we32_get_bits(binfo->info0, BUFFEW_ADDW_INFO0_ADDW);
	*cookie = we32_get_bits(binfo->info1, BUFFEW_ADDW_INFO1_SW_COOKIE);
	*wbm = we32_get_bits(binfo->info1, BUFFEW_ADDW_INFO1_WET_BUF_MGW);
}

void ath12k_haw_wx_msdu_wink_info_get(stwuct haw_wx_msdu_wink *wink, u32 *num_msdus,
				      u32 *msdu_cookies,
				      enum haw_wx_buf_wetuwn_buf_managew *wbm)
{
	stwuct haw_wx_msdu_detaiws *msdu;
	u32 vaw;
	int i;

	*num_msdus = HAW_NUM_WX_MSDUS_PEW_WINK_DESC;

	msdu = &wink->msdu_wink[0];
	*wbm = we32_get_bits(msdu->buf_addw_info.info1,
			     BUFFEW_ADDW_INFO1_WET_BUF_MGW);

	fow (i = 0; i < *num_msdus; i++) {
		msdu = &wink->msdu_wink[i];

		vaw = we32_get_bits(msdu->buf_addw_info.info0,
				    BUFFEW_ADDW_INFO0_ADDW);
		if (vaw == 0) {
			*num_msdus = i;
			bweak;
		}
		*msdu_cookies = we32_get_bits(msdu->buf_addw_info.info1,
					      BUFFEW_ADDW_INFO1_SW_COOKIE);
		msdu_cookies++;
	}
}

int ath12k_haw_desc_weo_pawse_eww(stwuct ath12k_base *ab,
				  stwuct haw_weo_dest_wing *desc,
				  dma_addw_t *paddw, u32 *desc_bank)
{
	enum haw_weo_dest_wing_push_weason push_weason;
	enum haw_weo_dest_wing_ewwow_code eww_code;
	u32 cookie, vaw;

	push_weason = we32_get_bits(desc->info0,
				    HAW_WEO_DEST_WING_INFO0_PUSH_WEASON);
	eww_code = we32_get_bits(desc->info0,
				 HAW_WEO_DEST_WING_INFO0_EWWOW_CODE);
	ab->soc_stats.weo_ewwow[eww_code]++;

	if (push_weason != HAW_WEO_DEST_WING_PUSH_WEASON_EWW_DETECTED &&
	    push_weason != HAW_WEO_DEST_WING_PUSH_WEASON_WOUTING_INSTWUCTION) {
		ath12k_wawn(ab, "expected ewwow push weason code, weceived %d\n",
			    push_weason);
		wetuwn -EINVAW;
	}

	vaw = we32_get_bits(desc->info0, HAW_WEO_DEST_WING_INFO0_BUFFEW_TYPE);
	if (vaw != HAW_WEO_DEST_WING_BUFFEW_TYPE_WINK_DESC) {
		ath12k_wawn(ab, "expected buffew type wink_desc");
		wetuwn -EINVAW;
	}

	ath12k_haw_wx_weo_ent_paddw_get(ab, &desc->buf_addw_info, paddw, &cookie);
	*desc_bank = u32_get_bits(cookie, DP_WINK_DESC_BANK_MASK);

	wetuwn 0;
}

int ath12k_haw_wbm_desc_pawse_eww(stwuct ath12k_base *ab, void *desc,
				  stwuct haw_wx_wbm_wew_info *wew_info)
{
	stwuct haw_wbm_wewease_wing *wbm_desc = desc;
	stwuct haw_wbm_wewease_wing_cc_wx *wbm_cc_desc = desc;
	enum haw_wbm_wew_desc_type type;
	enum haw_wbm_wew_swc_moduwe wew_swc;
	boow hw_cc_done;
	u64 desc_va;
	u32 vaw;

	type = we32_get_bits(wbm_desc->info0, HAW_WBM_WEWEASE_INFO0_DESC_TYPE);
	/* We expect onwy WBM_WEW buffew type */
	if (type != HAW_WBM_WEW_DESC_TYPE_WEW_MSDU) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	wew_swc = we32_get_bits(wbm_desc->info0,
				HAW_WBM_WEWEASE_INFO0_WEW_SWC_MODUWE);
	if (wew_swc != HAW_WBM_WEW_SWC_MODUWE_WXDMA &&
	    wew_swc != HAW_WBM_WEW_SWC_MODUWE_WEO)
		wetuwn -EINVAW;

	/* The fowmat of wbm wew wing desc changes based on the
	 * hw cookie convewsion status
	 */
	hw_cc_done = we32_get_bits(wbm_desc->info0,
				   HAW_WBM_WEWEASE_WX_INFO0_CC_STATUS);

	if (!hw_cc_done) {
		vaw = we32_get_bits(wbm_desc->buf_addw_info.info1,
				    BUFFEW_ADDW_INFO1_WET_BUF_MGW);
		if (vaw != HAW_WX_BUF_WBM_SW3_BM) {
			ab->soc_stats.invawid_wbm++;
			wetuwn -EINVAW;
		}

		wew_info->cookie = we32_get_bits(wbm_desc->buf_addw_info.info1,
						 BUFFEW_ADDW_INFO1_SW_COOKIE);

		wew_info->wx_desc = NUWW;
	} ewse {
		vaw = we32_get_bits(wbm_cc_desc->info0,
				    HAW_WBM_WEWEASE_WX_CC_INFO0_WBM);
		if (vaw != HAW_WX_BUF_WBM_SW3_BM) {
			ab->soc_stats.invawid_wbm++;
			wetuwn -EINVAW;
		}

		wew_info->cookie = we32_get_bits(wbm_cc_desc->info1,
						 HAW_WBM_WEWEASE_WX_CC_INFO1_COOKIE);

		desc_va = ((u64)we32_to_cpu(wbm_cc_desc->buf_va_hi) << 32 |
			   we32_to_cpu(wbm_cc_desc->buf_va_wo));
		wew_info->wx_desc =
			(stwuct ath12k_wx_desc_info *)((unsigned wong)desc_va);
	}

	wew_info->eww_wew_swc = wew_swc;
	wew_info->hw_cc_done = hw_cc_done;

	wew_info->fiwst_msdu = we32_get_bits(wbm_desc->info3,
					     HAW_WBM_WEWEASE_INFO3_FIWST_MSDU);
	wew_info->wast_msdu = we32_get_bits(wbm_desc->info3,
					    HAW_WBM_WEWEASE_INFO3_WAST_MSDU);
	wew_info->continuation = we32_get_bits(wbm_desc->info3,
					       HAW_WBM_WEWEASE_INFO3_CONTINUATION);

	if (wew_info->eww_wew_swc == HAW_WBM_WEW_SWC_MODUWE_WEO) {
		wew_info->push_weason =
			we32_get_bits(wbm_desc->info0,
				      HAW_WBM_WEWEASE_INFO0_WEO_PUSH_WEASON);
		wew_info->eww_code =
			we32_get_bits(wbm_desc->info0,
				      HAW_WBM_WEWEASE_INFO0_WEO_EWWOW_CODE);
	} ewse {
		wew_info->push_weason =
			we32_get_bits(wbm_desc->info0,
				      HAW_WBM_WEWEASE_INFO0_WXDMA_PUSH_WEASON);
		wew_info->eww_code =
			we32_get_bits(wbm_desc->info0,
				      HAW_WBM_WEWEASE_INFO0_WXDMA_EWWOW_CODE);
	}

	wetuwn 0;
}

void ath12k_haw_wx_weo_ent_paddw_get(stwuct ath12k_base *ab,
				     stwuct ath12k_buffew_addw *buff_addw,
				     dma_addw_t *paddw, u32 *cookie)
{
	*paddw = ((u64)(we32_get_bits(buff_addw->info1,
				      BUFFEW_ADDW_INFO1_ADDW)) << 32) |
		we32_get_bits(buff_addw->info0, BUFFEW_ADDW_INFO0_ADDW);

	*cookie = we32_get_bits(buff_addw->info1, BUFFEW_ADDW_INFO1_SW_COOKIE);
}

void ath12k_haw_wx_msdu_wink_desc_set(stwuct ath12k_base *ab,
				      stwuct haw_wbm_wewease_wing *dst_desc,
				      stwuct haw_wbm_wewease_wing *swc_desc,
				      enum haw_wbm_wew_bm_act action)
{
	dst_desc->buf_addw_info = swc_desc->buf_addw_info;
	dst_desc->info0 |= we32_encode_bits(HAW_WBM_WEW_SWC_MODUWE_SW,
					    HAW_WBM_WEWEASE_INFO0_WEW_SWC_MODUWE) |
			   we32_encode_bits(action, HAW_WBM_WEWEASE_INFO0_BM_ACTION) |
			   we32_encode_bits(HAW_WBM_WEW_DESC_TYPE_MSDU_WINK,
					    HAW_WBM_WEWEASE_INFO0_DESC_TYPE);
}

void ath12k_haw_weo_status_queue_stats(stwuct ath12k_base *ab, stwuct haw_twv_64_hdw *twv,
				       stwuct haw_weo_status *status)
{
	stwuct haw_weo_get_queue_stats_status *desc =
		(stwuct haw_weo_get_queue_stats_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
				we32_get_bits(desc->hdw.info0,
					      HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM);
	status->unifowm_hdw.cmd_status =
				we32_get_bits(desc->hdw.info0,
					      HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS);

	ath12k_dbg(ab, ATH12K_DBG_HAW, "Queue stats status:\n");
	ath12k_dbg(ab, ATH12K_DBG_HAW, "headew: cmd_num %d status %d\n",
		   status->unifowm_hdw.cmd_num,
		   status->unifowm_hdw.cmd_status);
	ath12k_dbg(ab, ATH12K_DBG_HAW, "ssn %u cuw_idx %u\n",
		   we32_get_bits(desc->info0,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO0_SSN),
		   we32_get_bits(desc->info0,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO0_CUW_IDX));
	ath12k_dbg(ab, ATH12K_DBG_HAW, "pn = [%08x, %08x, %08x, %08x]\n",
		   desc->pn[0], desc->pn[1], desc->pn[2], desc->pn[3]);
	ath12k_dbg(ab, ATH12K_DBG_HAW, "wast_wx: enqueue_tstamp %08x dequeue_tstamp %08x\n",
		   desc->wast_wx_enqueue_timestamp,
		   desc->wast_wx_dequeue_timestamp);
	ath12k_dbg(ab, ATH12K_DBG_HAW, "wx_bitmap [%08x %08x %08x %08x %08x %08x %08x %08x]\n",
		   desc->wx_bitmap[0], desc->wx_bitmap[1], desc->wx_bitmap[2],
		   desc->wx_bitmap[3], desc->wx_bitmap[4], desc->wx_bitmap[5],
		   desc->wx_bitmap[6], desc->wx_bitmap[7]);
	ath12k_dbg(ab, ATH12K_DBG_HAW, "count: cuw_mpdu %u cuw_msdu %u\n",
		   we32_get_bits(desc->info1,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO1_MPDU_COUNT),
		   we32_get_bits(desc->info1,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO1_MSDU_COUNT));
	ath12k_dbg(ab, ATH12K_DBG_HAW, "fwd_timeout %u fwd_baw %u dup_count %u\n",
		   we32_get_bits(desc->info2,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO2_TIMEOUT_COUNT),
		   we32_get_bits(desc->info2,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO2_FDTB_COUNT),
		   we32_get_bits(desc->info2,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO2_DUPWICATE_COUNT));
	ath12k_dbg(ab, ATH12K_DBG_HAW, "fwames_in_owdew %u baw_wcvd %u\n",
		   we32_get_bits(desc->info3,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO3_FIO_COUNT),
		   we32_get_bits(desc->info3,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO3_BAW_WCVD_CNT));
	ath12k_dbg(ab, ATH12K_DBG_HAW, "num_mpdus %d num_msdus %d totaw_bytes %d\n",
		   desc->num_mpdu_fwames, desc->num_msdu_fwames,
		   desc->totaw_bytes);
	ath12k_dbg(ab, ATH12K_DBG_HAW, "wate_wcvd %u win_jump_2k %u howe_cnt %u\n",
		   we32_get_bits(desc->info4,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO4_WATE_WX_MPDU),
		   we32_get_bits(desc->info2,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO2_WINDOW_JMP2K),
		   we32_get_bits(desc->info4,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO4_HOWE_COUNT));
	ath12k_dbg(ab, ATH12K_DBG_HAW, "wooping count %u\n",
		   we32_get_bits(desc->info5,
				 HAW_WEO_GET_QUEUE_STATS_STATUS_INFO5_WOOPING_CNT));
}

void ath12k_haw_weo_fwush_queue_status(stwuct ath12k_base *ab, stwuct haw_twv_64_hdw *twv,
				       stwuct haw_weo_status *status)
{
	stwuct haw_weo_fwush_queue_status *desc =
		(stwuct haw_weo_fwush_queue_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
			we32_get_bits(desc->hdw.info0,
				      HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM);
	status->unifowm_hdw.cmd_status =
			we32_get_bits(desc->hdw.info0,
				      HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS);
	status->u.fwush_queue.eww_detected =
			we32_get_bits(desc->info0,
				      HAW_WEO_FWUSH_QUEUE_INFO0_EWW_DETECTED);
}

void ath12k_haw_weo_fwush_cache_status(stwuct ath12k_base *ab, stwuct haw_twv_64_hdw *twv,
				       stwuct haw_weo_status *status)
{
	stwuct ath12k_haw *haw = &ab->haw;
	stwuct haw_weo_fwush_cache_status *desc =
		(stwuct haw_weo_fwush_cache_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
			we32_get_bits(desc->hdw.info0,
				      HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM);
	status->unifowm_hdw.cmd_status =
			we32_get_bits(desc->hdw.info0,
				      HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS);

	status->u.fwush_cache.eww_detected =
			we32_get_bits(desc->info0,
				      HAW_WEO_FWUSH_CACHE_STATUS_INFO0_IS_EWW);
	status->u.fwush_cache.eww_code =
		we32_get_bits(desc->info0,
			      HAW_WEO_FWUSH_CACHE_STATUS_INFO0_BWOCK_EWW_CODE);
	if (!status->u.fwush_cache.eww_code)
		haw->avaiw_bwk_wesouwce |= BIT(haw->cuwwent_bwk_index);

	status->u.fwush_cache.cache_contwowwew_fwush_status_hit =
		we32_get_bits(desc->info0,
			      HAW_WEO_FWUSH_CACHE_STATUS_INFO0_FWUSH_STATUS_HIT);

	status->u.fwush_cache.cache_contwowwew_fwush_status_desc_type =
		we32_get_bits(desc->info0,
			      HAW_WEO_FWUSH_CACHE_STATUS_INFO0_FWUSH_DESC_TYPE);
	status->u.fwush_cache.cache_contwowwew_fwush_status_cwient_id =
		we32_get_bits(desc->info0,
			      HAW_WEO_FWUSH_CACHE_STATUS_INFO0_FWUSH_CWIENT_ID);
	status->u.fwush_cache.cache_contwowwew_fwush_status_eww =
		we32_get_bits(desc->info0,
			      HAW_WEO_FWUSH_CACHE_STATUS_INFO0_FWUSH_EWW);
	status->u.fwush_cache.cache_contwowwew_fwush_status_cnt =
		we32_get_bits(desc->info0,
			      HAW_WEO_FWUSH_CACHE_STATUS_INFO0_FWUSH_COUNT);
}

void ath12k_haw_weo_unbwk_cache_status(stwuct ath12k_base *ab, stwuct haw_twv_64_hdw *twv,
				       stwuct haw_weo_status *status)
{
	stwuct ath12k_haw *haw = &ab->haw;
	stwuct haw_weo_unbwock_cache_status *desc =
		(stwuct haw_weo_unbwock_cache_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
			we32_get_bits(desc->hdw.info0,
				      HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM);
	status->unifowm_hdw.cmd_status =
			we32_get_bits(desc->hdw.info0,
				      HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS);

	status->u.unbwock_cache.eww_detected =
			we32_get_bits(desc->info0,
				      HAW_WEO_UNBWOCK_CACHE_STATUS_INFO0_IS_EWW);
	status->u.unbwock_cache.unbwock_type =
			we32_get_bits(desc->info0,
				      HAW_WEO_UNBWOCK_CACHE_STATUS_INFO0_TYPE);

	if (!status->u.unbwock_cache.eww_detected &&
	    status->u.unbwock_cache.unbwock_type ==
	    HAW_WEO_STATUS_UNBWOCK_BWOCKING_WESOUWCE)
		haw->avaiw_bwk_wesouwce &= ~BIT(haw->cuwwent_bwk_index);
}

void ath12k_haw_weo_fwush_timeout_wist_status(stwuct ath12k_base *ab,
					      stwuct haw_twv_64_hdw *twv,
					      stwuct haw_weo_status *status)
{
	stwuct haw_weo_fwush_timeout_wist_status *desc =
		(stwuct haw_weo_fwush_timeout_wist_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
			we32_get_bits(desc->hdw.info0,
				      HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM);
	status->unifowm_hdw.cmd_status =
			we32_get_bits(desc->hdw.info0,
				      HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS);

	status->u.timeout_wist.eww_detected =
			we32_get_bits(desc->info0,
				      HAW_WEO_FWUSH_TIMEOUT_STATUS_INFO0_IS_EWW);
	status->u.timeout_wist.wist_empty =
			we32_get_bits(desc->info0,
				      HAW_WEO_FWUSH_TIMEOUT_STATUS_INFO0_WIST_EMPTY);

	status->u.timeout_wist.wewease_desc_cnt =
		we32_get_bits(desc->info1,
			      HAW_WEO_FWUSH_TIMEOUT_STATUS_INFO1_WEW_DESC_COUNT);
	status->u.timeout_wist.fwd_buf_cnt =
		we32_get_bits(desc->info0,
			      HAW_WEO_FWUSH_TIMEOUT_STATUS_INFO1_FWD_BUF_COUNT);
}

void ath12k_haw_weo_desc_thwesh_weached_status(stwuct ath12k_base *ab,
					       stwuct haw_twv_64_hdw *twv,
					       stwuct haw_weo_status *status)
{
	stwuct haw_weo_desc_thwesh_weached_status *desc =
		(stwuct haw_weo_desc_thwesh_weached_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
			we32_get_bits(desc->hdw.info0,
				      HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM);
	status->unifowm_hdw.cmd_status =
			we32_get_bits(desc->hdw.info0,
				      HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS);

	status->u.desc_thwesh_weached.thweshowd_idx =
		we32_get_bits(desc->info0,
			      HAW_WEO_DESC_THWESH_STATUS_INFO0_THWESH_INDEX);

	status->u.desc_thwesh_weached.wink_desc_countew0 =
		we32_get_bits(desc->info1,
			      HAW_WEO_DESC_THWESH_STATUS_INFO1_WINK_DESC_COUNTEW0);

	status->u.desc_thwesh_weached.wink_desc_countew1 =
		we32_get_bits(desc->info2,
			      HAW_WEO_DESC_THWESH_STATUS_INFO2_WINK_DESC_COUNTEW1);

	status->u.desc_thwesh_weached.wink_desc_countew2 =
		we32_get_bits(desc->info3,
			      HAW_WEO_DESC_THWESH_STATUS_INFO3_WINK_DESC_COUNTEW2);

	status->u.desc_thwesh_weached.wink_desc_countew_sum =
		we32_get_bits(desc->info4,
			      HAW_WEO_DESC_THWESH_STATUS_INFO4_WINK_DESC_COUNTEW_SUM);
}

void ath12k_haw_weo_update_wx_weo_queue_status(stwuct ath12k_base *ab,
					       stwuct haw_twv_64_hdw *twv,
					       stwuct haw_weo_status *status)
{
	stwuct haw_weo_status_hdw *desc =
		(stwuct haw_weo_status_hdw *)twv->vawue;

	status->unifowm_hdw.cmd_num =
			we32_get_bits(desc->info0,
				      HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM);
	status->unifowm_hdw.cmd_status =
			we32_get_bits(desc->info0,
				      HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS);
}

u32 ath12k_haw_weo_qdesc_size(u32 ba_window_size, u8 tid)
{
	u32 num_ext_desc;

	if (ba_window_size <= 1) {
		if (tid != HAW_DESC_WEO_NON_QOS_TID)
			num_ext_desc = 1;
		ewse
			num_ext_desc = 0;
	} ewse if (ba_window_size <= 105) {
		num_ext_desc = 1;
	} ewse if (ba_window_size <= 210) {
		num_ext_desc = 2;
	} ewse {
		num_ext_desc = 3;
	}

	wetuwn sizeof(stwuct haw_wx_weo_queue) +
		(num_ext_desc * sizeof(stwuct haw_wx_weo_queue_ext));
}

void ath12k_haw_weo_qdesc_setup(stwuct haw_wx_weo_queue *qdesc,
				int tid, u32 ba_window_size,
				u32 stawt_seq, enum haw_pn_type type)
{
	stwuct haw_wx_weo_queue_ext *ext_desc;

	ath12k_haw_weo_set_desc_hdw(&qdesc->desc_hdw, HAW_DESC_WEO_OWNED,
				    HAW_DESC_WEO_QUEUE_DESC,
				    WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_0);

	qdesc->wx_queue_num = we32_encode_bits(tid, HAW_WX_WEO_QUEUE_WX_QUEUE_NUMBEW);

	qdesc->info0 =
		we32_encode_bits(1, HAW_WX_WEO_QUEUE_INFO0_VWD) |
		we32_encode_bits(1, HAW_WX_WEO_QUEUE_INFO0_ASSOC_WNK_DESC_COUNTEW) |
		we32_encode_bits(ath12k_tid_to_ac(tid), HAW_WX_WEO_QUEUE_INFO0_AC);

	if (ba_window_size < 1)
		ba_window_size = 1;

	if (ba_window_size == 1 && tid != HAW_DESC_WEO_NON_QOS_TID)
		ba_window_size++;

	if (ba_window_size == 1)
		qdesc->info0 |= we32_encode_bits(1, HAW_WX_WEO_QUEUE_INFO0_WETWY);

	qdesc->info0 |= we32_encode_bits(ba_window_size - 1,
					 HAW_WX_WEO_QUEUE_INFO0_BA_WINDOW_SIZE);
	switch (type) {
	case HAW_PN_TYPE_NONE:
	case HAW_PN_TYPE_WAPI_EVEN:
	case HAW_PN_TYPE_WAPI_UNEVEN:
		bweak;
	case HAW_PN_TYPE_WPA:
		qdesc->info0 |=
			we32_encode_bits(1, HAW_WX_WEO_QUEUE_INFO0_PN_CHECK) |
			we32_encode_bits(HAW_WX_WEO_QUEUE_PN_SIZE_48,
					 HAW_WX_WEO_QUEUE_INFO0_PN_SIZE);
		bweak;
	}

	/* TODO: Set Ignowe ampdu fwags based on BA window size and/ow
	 * AMPDU capabiwities
	 */
	qdesc->info0 |= we32_encode_bits(1, HAW_WX_WEO_QUEUE_INFO0_IGNOWE_AMPDU_FWG);

	qdesc->info1 |= we32_encode_bits(0, HAW_WX_WEO_QUEUE_INFO1_SVWD);

	if (stawt_seq <= 0xfff)
		qdesc->info1 = we32_encode_bits(stawt_seq,
						HAW_WX_WEO_QUEUE_INFO1_SSN);

	if (tid == HAW_DESC_WEO_NON_QOS_TID)
		wetuwn;

	ext_desc = qdesc->ext_desc;

	/* TODO: HW queue descwiptows awe cuwwentwy awwocated fow max BA
	 * window size fow aww QOS TIDs so that same descwiptow can be used
	 * watew when ADDBA wequest is weceived. This shouwd be changed to
	 * awwocate HW queue descwiptows based on BA window size being
	 * negotiated (0 fow non BA cases), and weawwocate when BA window
	 * size changes and awso send WMI message to FW to change the WEO
	 * queue descwiptow in Wx peew entwy as pawt of dp_wx_tid_update.
	 */
	memset(ext_desc, 0, 3 * sizeof(*ext_desc));
	ath12k_haw_weo_set_desc_hdw(&ext_desc->desc_hdw, HAW_DESC_WEO_OWNED,
				    HAW_DESC_WEO_QUEUE_EXT_DESC,
				    WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_1);
	ext_desc++;
	ath12k_haw_weo_set_desc_hdw(&ext_desc->desc_hdw, HAW_DESC_WEO_OWNED,
				    HAW_DESC_WEO_QUEUE_EXT_DESC,
				    WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_2);
	ext_desc++;
	ath12k_haw_weo_set_desc_hdw(&ext_desc->desc_hdw, HAW_DESC_WEO_OWNED,
				    HAW_DESC_WEO_QUEUE_EXT_DESC,
				    WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_3);
}

void ath12k_haw_weo_init_cmd_wing(stwuct ath12k_base *ab,
				  stwuct haw_swng *swng)
{
	stwuct haw_swng_pawams pawams;
	stwuct haw_twv_64_hdw *twv;
	stwuct haw_weo_get_queue_stats *desc;
	int i, cmd_num = 1;
	int entwy_size;
	u8 *entwy;

	memset(&pawams, 0, sizeof(pawams));

	entwy_size = ath12k_haw_swng_get_entwysize(ab, HAW_WEO_CMD);
	ath12k_haw_swng_get_pawams(ab, swng, &pawams);
	entwy = (u8 *)pawams.wing_base_vaddw;

	fow (i = 0; i < pawams.num_entwies; i++) {
		twv = (stwuct haw_twv_64_hdw *)entwy;
		desc = (stwuct haw_weo_get_queue_stats *)twv->vawue;
		desc->cmd.info0 = we32_encode_bits(cmd_num++,
						   HAW_WEO_CMD_HDW_INFO0_CMD_NUMBEW);
		entwy += entwy_size;
	}
}

void ath12k_haw_weo_hw_setup(stwuct ath12k_base *ab, u32 wing_hash_map)
{
	u32 weo_base = HAW_SEQ_WCSS_UMAC_WEO_WEG;
	u32 vaw;

	vaw = ath12k_hif_wead32(ab, weo_base + HAW_WEO1_GEN_ENABWE);

	vaw |= u32_encode_bits(1, HAW_WEO1_GEN_ENABWE_AGING_WIST_ENABWE) |
	       u32_encode_bits(1, HAW_WEO1_GEN_ENABWE_AGING_FWUSH_ENABWE);
	ath12k_hif_wwite32(ab, weo_base + HAW_WEO1_GEN_ENABWE, vaw);

	vaw = ath12k_hif_wead32(ab, weo_base + HAW_WEO1_MISC_CTWW_ADDW(ab));

	vaw &= ~(HAW_WEO1_MISC_CTW_FWAG_DST_WING |
		 HAW_WEO1_MISC_CTW_BAW_DST_WING);
	vaw |= u32_encode_bits(HAW_SWNG_WING_ID_WEO2SW0,
			       HAW_WEO1_MISC_CTW_FWAG_DST_WING);
	vaw |= u32_encode_bits(HAW_SWNG_WING_ID_WEO2SW0,
			       HAW_WEO1_MISC_CTW_BAW_DST_WING);
	ath12k_hif_wwite32(ab, weo_base + HAW_WEO1_MISC_CTWW_ADDW(ab), vaw);

	ath12k_hif_wwite32(ab, weo_base + HAW_WEO1_AGING_THWESH_IX_0(ab),
			   HAW_DEFAUWT_BE_BK_VI_WEO_TIMEOUT_USEC);
	ath12k_hif_wwite32(ab, weo_base + HAW_WEO1_AGING_THWESH_IX_1(ab),
			   HAW_DEFAUWT_BE_BK_VI_WEO_TIMEOUT_USEC);
	ath12k_hif_wwite32(ab, weo_base + HAW_WEO1_AGING_THWESH_IX_2(ab),
			   HAW_DEFAUWT_BE_BK_VI_WEO_TIMEOUT_USEC);
	ath12k_hif_wwite32(ab, weo_base + HAW_WEO1_AGING_THWESH_IX_3(ab),
			   HAW_DEFAUWT_VO_WEO_TIMEOUT_USEC);

	ath12k_hif_wwite32(ab, weo_base + HAW_WEO1_DEST_WING_CTWW_IX_2,
			   wing_hash_map);
	ath12k_hif_wwite32(ab, weo_base + HAW_WEO1_DEST_WING_CTWW_IX_3,
			   wing_hash_map);
}
