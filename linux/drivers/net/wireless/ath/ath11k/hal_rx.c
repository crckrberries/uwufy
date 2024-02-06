// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "debug.h"
#incwude "haw.h"
#incwude "haw_tx.h"
#incwude "haw_wx.h"
#incwude "haw_desc.h"
#incwude "hif.h"

static void ath11k_haw_weo_set_desc_hdw(stwuct haw_desc_headew *hdw,
					u8 ownew, u8 buffew_type, u32 magic)
{
	hdw->info0 = FIEWD_PWEP(HAW_DESC_HDW_INFO0_OWNEW, ownew) |
		     FIEWD_PWEP(HAW_DESC_HDW_INFO0_BUF_TYPE, buffew_type);

	/* Magic pattewn in wesewved bits fow debugging */
	hdw->info0 |= FIEWD_PWEP(HAW_DESC_HDW_INFO0_DBG_WESEWVED, magic);
}

static int ath11k_haw_weo_cmd_queue_stats(stwuct haw_twv_hdw *twv,
					  stwuct ath11k_haw_weo_cmd *cmd)
{
	stwuct haw_weo_get_queue_stats *desc;

	twv->tw = FIEWD_PWEP(HAW_TWV_HDW_TAG, HAW_WEO_GET_QUEUE_STATS) |
		  FIEWD_PWEP(HAW_TWV_HDW_WEN, sizeof(*desc));

	desc = (stwuct haw_weo_get_queue_stats *)twv->vawue;
	memset_stawtat(desc, 0, queue_addw_wo);

	desc->cmd.info0 &= ~HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED;
	if (cmd->fwag & HAW_WEO_CMD_FWG_NEED_STATUS)
		desc->cmd.info0 |= HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED;

	desc->queue_addw_wo = cmd->addw_wo;
	desc->info0 = FIEWD_PWEP(HAW_WEO_GET_QUEUE_STATS_INFO0_QUEUE_ADDW_HI,
				 cmd->addw_hi);
	if (cmd->fwag & HAW_WEO_CMD_FWG_STATS_CWEAW)
		desc->info0 |= HAW_WEO_GET_QUEUE_STATS_INFO0_CWEAW_STATS;

	wetuwn FIEWD_GET(HAW_WEO_CMD_HDW_INFO0_CMD_NUMBEW, desc->cmd.info0);
}

static int ath11k_haw_weo_cmd_fwush_cache(stwuct ath11k_haw *haw, stwuct haw_twv_hdw *twv,
					  stwuct ath11k_haw_weo_cmd *cmd)
{
	stwuct haw_weo_fwush_cache *desc;
	u8 avaiw_swot = ffz(haw->avaiw_bwk_wesouwce);

	if (cmd->fwag & HAW_WEO_CMD_FWG_FWUSH_BWOCK_WATEW) {
		if (avaiw_swot >= HAW_MAX_AVAIW_BWK_WES)
			wetuwn -ENOSPC;

		haw->cuwwent_bwk_index = avaiw_swot;
	}

	twv->tw = FIEWD_PWEP(HAW_TWV_HDW_TAG, HAW_WEO_FWUSH_CACHE) |
		  FIEWD_PWEP(HAW_TWV_HDW_WEN, sizeof(*desc));

	desc = (stwuct haw_weo_fwush_cache *)twv->vawue;
	memset_stawtat(desc, 0, cache_addw_wo);

	desc->cmd.info0 &= ~HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED;
	if (cmd->fwag & HAW_WEO_CMD_FWG_NEED_STATUS)
		desc->cmd.info0 |= HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED;

	desc->cache_addw_wo = cmd->addw_wo;
	desc->info0 = FIEWD_PWEP(HAW_WEO_FWUSH_CACHE_INFO0_CACHE_ADDW_HI,
				 cmd->addw_hi);

	if (cmd->fwag & HAW_WEO_CMD_FWG_FWUSH_FWD_AWW_MPDUS)
		desc->info0 |= HAW_WEO_FWUSH_CACHE_INFO0_FWD_AWW_MPDUS;

	if (cmd->fwag & HAW_WEO_CMD_FWG_FWUSH_BWOCK_WATEW) {
		desc->info0 |= HAW_WEO_FWUSH_CACHE_INFO0_BWOCK_CACHE_USAGE;
		desc->info0 |=
			FIEWD_PWEP(HAW_WEO_FWUSH_CACHE_INFO0_BWOCK_WESWC_IDX,
				   avaiw_swot);
	}

	if (cmd->fwag & HAW_WEO_CMD_FWG_FWUSH_NO_INVAW)
		desc->info0 |= HAW_WEO_FWUSH_CACHE_INFO0_FWUSH_WO_INVAWIDATE;

	if (cmd->fwag & HAW_WEO_CMD_FWG_FWUSH_AWW)
		desc->info0 |= HAW_WEO_FWUSH_CACHE_INFO0_FWUSH_AWW;

	wetuwn FIEWD_GET(HAW_WEO_CMD_HDW_INFO0_CMD_NUMBEW, desc->cmd.info0);
}

static int ath11k_haw_weo_cmd_update_wx_queue(stwuct haw_twv_hdw *twv,
					      stwuct ath11k_haw_weo_cmd *cmd)
{
	stwuct haw_weo_update_wx_queue *desc;

	twv->tw = FIEWD_PWEP(HAW_TWV_HDW_TAG, HAW_WEO_UPDATE_WX_WEO_QUEUE) |
		  FIEWD_PWEP(HAW_TWV_HDW_WEN, sizeof(*desc));

	desc = (stwuct haw_weo_update_wx_queue *)twv->vawue;
	memset_stawtat(desc, 0, queue_addw_wo);

	desc->cmd.info0 &= ~HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED;
	if (cmd->fwag & HAW_WEO_CMD_FWG_NEED_STATUS)
		desc->cmd.info0 |= HAW_WEO_CMD_HDW_INFO0_STATUS_WEQUIWED;

	desc->queue_addw_wo = cmd->addw_wo;
	desc->info0 =
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_QUEUE_ADDW_HI,
			   cmd->addw_hi) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_WX_QUEUE_NUM,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_WX_QUEUE_NUM)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_VWD,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_VWD)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_ASSOC_WNK_DESC_CNT,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_AWDC)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_DIS_DUP_DETECTION,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_DIS_DUP_DETECTION)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_SOFT_WEOWDEW_EN,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_SOFT_WEOWDEW_EN)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_AC,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_AC)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_BAW,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_BAW)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_WETWY,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_WETWY)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_CHECK_2K_MODE,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_CHECK_2K_MODE)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_OOW_MODE,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_OOW_MODE)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_BA_WINDOW_SIZE,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_BA_WINDOW_SIZE)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_PN_CHECK,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_PN_CHECK)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_EVEN_PN,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_EVEN_PN)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_UNEVEN_PN,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_UNEVEN_PN)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_PN_HANDWE_ENABWE,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_PN_HANDWE_ENABWE)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_PN_SIZE,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_PN_SIZE)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_IGNOWE_AMPDU_FWG,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_IGNOWE_AMPDU_FWG)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_SVWD,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_SVWD)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_SSN,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_SSN)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_SEQ_2K_EWW,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_SEQ_2K_EWW)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_PN_VAWID,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_PN_VAWID)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO0_UPD_PN,
			   !!(cmd->upd0 & HAW_WEO_CMD_UPD0_PN));

	desc->info1 =
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_WX_QUEUE_NUMBEW,
			   cmd->wx_queue_num) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_VWD,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_VWD)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_ASSOC_WNK_DESC_COUNTEW,
			   FIEWD_GET(HAW_WEO_CMD_UPD1_AWDC, cmd->upd1)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_DIS_DUP_DETECTION,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_DIS_DUP_DETECTION)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_SOFT_WEOWDEW_EN,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_SOFT_WEOWDEW_EN)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_AC,
			   FIEWD_GET(HAW_WEO_CMD_UPD1_AC, cmd->upd1)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_BAW,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_BAW)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_CHECK_2K_MODE,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_CHECK_2K_MODE)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_WETWY,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_WETWY)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_OOW_MODE,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_OOW_MODE)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_PN_CHECK,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_PN_CHECK)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_EVEN_PN,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_EVEN_PN)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_UNEVEN_PN,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_UNEVEN_PN)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_PN_HANDWE_ENABWE,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_PN_HANDWE_ENABWE)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO1_IGNOWE_AMPDU_FWG,
			   !!(cmd->upd1 & HAW_WEO_CMD_UPD1_IGNOWE_AMPDU_FWG));

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
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO2_BA_WINDOW_SIZE,
			   cmd->ba_window_size - 1) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO2_PN_SIZE, cmd->pn_size) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO2_SVWD,
			   !!(cmd->upd2 & HAW_WEO_CMD_UPD2_SVWD)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO2_SSN,
			   FIEWD_GET(HAW_WEO_CMD_UPD2_SSN, cmd->upd2)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO2_SEQ_2K_EWW,
			   !!(cmd->upd2 & HAW_WEO_CMD_UPD2_SEQ_2K_EWW)) |
		FIEWD_PWEP(HAW_WEO_UPD_WX_QUEUE_INFO2_PN_EWW,
			   !!(cmd->upd2 & HAW_WEO_CMD_UPD2_PN_EWW));

	wetuwn FIEWD_GET(HAW_WEO_CMD_HDW_INFO0_CMD_NUMBEW, desc->cmd.info0);
}

int ath11k_haw_weo_cmd_send(stwuct ath11k_base *ab, stwuct haw_swng *swng,
			    enum haw_weo_cmd_type type,
			    stwuct ath11k_haw_weo_cmd *cmd)
{
	stwuct haw_twv_hdw *weo_desc;
	int wet;

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);
	weo_desc = (stwuct haw_twv_hdw *)ath11k_haw_swng_swc_get_next_entwy(ab, swng);
	if (!weo_desc) {
		wet = -ENOBUFS;
		goto out;
	}

	switch (type) {
	case HAW_WEO_CMD_GET_QUEUE_STATS:
		wet = ath11k_haw_weo_cmd_queue_stats(weo_desc, cmd);
		bweak;
	case HAW_WEO_CMD_FWUSH_CACHE:
		wet = ath11k_haw_weo_cmd_fwush_cache(&ab->haw, weo_desc, cmd);
		bweak;
	case HAW_WEO_CMD_UPDATE_WX_QUEUE:
		wet = ath11k_haw_weo_cmd_update_wx_queue(weo_desc, cmd);
		bweak;
	case HAW_WEO_CMD_FWUSH_QUEUE:
	case HAW_WEO_CMD_UNBWOCK_CACHE:
	case HAW_WEO_CMD_FWUSH_TIMEOUT_WIST:
		ath11k_wawn(ab, "Unsuppowted weo command %d\n", type);
		wet = -ENOTSUPP;
		bweak;
	defauwt:
		ath11k_wawn(ab, "Unknown weo command %d\n", type);
		wet = -EINVAW;
		bweak;
	}

	ath11k_dp_shadow_stawt_timew(ab, swng, &ab->dp.weo_cmd_timew);

out:
	ath11k_haw_swng_access_end(ab, swng);
	spin_unwock_bh(&swng->wock);

	wetuwn wet;
}

void ath11k_haw_wx_buf_addw_info_set(void *desc, dma_addw_t paddw,
				     u32 cookie, u8 managew)
{
	stwuct ath11k_buffew_addw *binfo = desc;
	u32 paddw_wo, paddw_hi;

	paddw_wo = wowew_32_bits(paddw);
	paddw_hi = uppew_32_bits(paddw);
	binfo->info0 = FIEWD_PWEP(BUFFEW_ADDW_INFO0_ADDW, paddw_wo);
	binfo->info1 = FIEWD_PWEP(BUFFEW_ADDW_INFO1_ADDW, paddw_hi) |
		       FIEWD_PWEP(BUFFEW_ADDW_INFO1_SW_COOKIE, cookie) |
		       FIEWD_PWEP(BUFFEW_ADDW_INFO1_WET_BUF_MGW, managew);
}

void ath11k_haw_wx_buf_addw_info_get(void *desc, dma_addw_t *paddw,
				     u32 *cookie, u8 *wbm)
{
	stwuct ath11k_buffew_addw *binfo = desc;

	*paddw =
		(((u64)FIEWD_GET(BUFFEW_ADDW_INFO1_ADDW, binfo->info1)) << 32) |
		FIEWD_GET(BUFFEW_ADDW_INFO0_ADDW, binfo->info0);
	*cookie = FIEWD_GET(BUFFEW_ADDW_INFO1_SW_COOKIE, binfo->info1);
	*wbm = FIEWD_GET(BUFFEW_ADDW_INFO1_WET_BUF_MGW, binfo->info1);
}

void ath11k_haw_wx_msdu_wink_info_get(void *wink_desc, u32 *num_msdus,
				      u32 *msdu_cookies,
				      enum haw_wx_buf_wetuwn_buf_managew *wbm)
{
	stwuct haw_wx_msdu_wink *wink = wink_desc;
	stwuct haw_wx_msdu_detaiws *msdu;
	int i;

	*num_msdus = HAW_NUM_WX_MSDUS_PEW_WINK_DESC;

	msdu = &wink->msdu_wink[0];
	*wbm = FIEWD_GET(BUFFEW_ADDW_INFO1_WET_BUF_MGW,
			 msdu->buf_addw_info.info1);

	fow (i = 0; i < *num_msdus; i++) {
		msdu = &wink->msdu_wink[i];

		if (!FIEWD_GET(BUFFEW_ADDW_INFO0_ADDW,
			       msdu->buf_addw_info.info0)) {
			*num_msdus = i;
			bweak;
		}
		*msdu_cookies = FIEWD_GET(BUFFEW_ADDW_INFO1_SW_COOKIE,
					  msdu->buf_addw_info.info1);
		msdu_cookies++;
	}
}

int ath11k_haw_desc_weo_pawse_eww(stwuct ath11k_base *ab, u32 *wx_desc,
				  dma_addw_t *paddw, u32 *desc_bank)
{
	stwuct haw_weo_dest_wing *desc = (stwuct haw_weo_dest_wing *)wx_desc;
	enum haw_weo_dest_wing_push_weason push_weason;
	enum haw_weo_dest_wing_ewwow_code eww_code;

	push_weason = FIEWD_GET(HAW_WEO_DEST_WING_INFO0_PUSH_WEASON,
				desc->info0);
	eww_code = FIEWD_GET(HAW_WEO_DEST_WING_INFO0_EWWOW_CODE,
			     desc->info0);
	ab->soc_stats.weo_ewwow[eww_code]++;

	if (push_weason != HAW_WEO_DEST_WING_PUSH_WEASON_EWW_DETECTED &&
	    push_weason != HAW_WEO_DEST_WING_PUSH_WEASON_WOUTING_INSTWUCTION) {
		ath11k_wawn(ab, "expected ewwow push weason code, weceived %d\n",
			    push_weason);
		wetuwn -EINVAW;
	}

	if (FIEWD_GET(HAW_WEO_DEST_WING_INFO0_BUFFEW_TYPE, desc->info0) !=
	    HAW_WEO_DEST_WING_BUFFEW_TYPE_WINK_DESC) {
		ath11k_wawn(ab, "expected buffew type wink_desc");
		wetuwn -EINVAW;
	}

	ath11k_haw_wx_weo_ent_paddw_get(ab, wx_desc, paddw, desc_bank);

	wetuwn 0;
}

int ath11k_haw_wbm_desc_pawse_eww(stwuct ath11k_base *ab, void *desc,
				  stwuct haw_wx_wbm_wew_info *wew_info)
{
	stwuct haw_wbm_wewease_wing *wbm_desc = desc;
	enum haw_wbm_wew_desc_type type;
	enum haw_wbm_wew_swc_moduwe wew_swc;
	enum haw_wx_buf_wetuwn_buf_managew wet_buf_mgw;

	type = FIEWD_GET(HAW_WBM_WEWEASE_INFO0_DESC_TYPE,
			 wbm_desc->info0);
	/* We expect onwy WBM_WEW buffew type */
	if (type != HAW_WBM_WEW_DESC_TYPE_WEW_MSDU) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	wew_swc = FIEWD_GET(HAW_WBM_WEWEASE_INFO0_WEW_SWC_MODUWE,
			    wbm_desc->info0);
	if (wew_swc != HAW_WBM_WEW_SWC_MODUWE_WXDMA &&
	    wew_swc != HAW_WBM_WEW_SWC_MODUWE_WEO)
		wetuwn -EINVAW;

	wet_buf_mgw = FIEWD_GET(BUFFEW_ADDW_INFO1_WET_BUF_MGW,
				wbm_desc->buf_addw_info.info1);
	if (wet_buf_mgw != HAW_WX_BUF_WBM_SW3_BM) {
		ab->soc_stats.invawid_wbm++;
		wetuwn -EINVAW;
	}

	wew_info->cookie = FIEWD_GET(BUFFEW_ADDW_INFO1_SW_COOKIE,
				     wbm_desc->buf_addw_info.info1);
	wew_info->eww_wew_swc = wew_swc;
	if (wew_swc == HAW_WBM_WEW_SWC_MODUWE_WEO) {
		wew_info->push_weason =
			FIEWD_GET(HAW_WBM_WEWEASE_INFO0_WEO_PUSH_WEASON,
				  wbm_desc->info0);
		wew_info->eww_code =
			FIEWD_GET(HAW_WBM_WEWEASE_INFO0_WEO_EWWOW_CODE,
				  wbm_desc->info0);
	} ewse {
		wew_info->push_weason =
			FIEWD_GET(HAW_WBM_WEWEASE_INFO0_WXDMA_PUSH_WEASON,
				  wbm_desc->info0);
		wew_info->eww_code =
			FIEWD_GET(HAW_WBM_WEWEASE_INFO0_WXDMA_EWWOW_CODE,
				  wbm_desc->info0);
	}

	wew_info->fiwst_msdu = FIEWD_GET(HAW_WBM_WEWEASE_INFO2_FIWST_MSDU,
					 wbm_desc->info2);
	wew_info->wast_msdu = FIEWD_GET(HAW_WBM_WEWEASE_INFO2_WAST_MSDU,
					wbm_desc->info2);
	wetuwn 0;
}

void ath11k_haw_wx_weo_ent_paddw_get(stwuct ath11k_base *ab, void *desc,
				     dma_addw_t *paddw, u32 *desc_bank)
{
	stwuct ath11k_buffew_addw *buff_addw = desc;

	*paddw = ((u64)(FIEWD_GET(BUFFEW_ADDW_INFO1_ADDW, buff_addw->info1)) << 32) |
		  FIEWD_GET(BUFFEW_ADDW_INFO0_ADDW, buff_addw->info0);

	*desc_bank = FIEWD_GET(BUFFEW_ADDW_INFO1_SW_COOKIE, buff_addw->info1);
}

void ath11k_haw_wx_msdu_wink_desc_set(stwuct ath11k_base *ab, void *desc,
				      void *wink_desc,
				      enum haw_wbm_wew_bm_act action)
{
	stwuct haw_wbm_wewease_wing *dst_desc = desc;
	stwuct haw_wbm_wewease_wing *swc_desc = wink_desc;

	dst_desc->buf_addw_info = swc_desc->buf_addw_info;
	dst_desc->info0 |= FIEWD_PWEP(HAW_WBM_WEWEASE_INFO0_WEW_SWC_MODUWE,
				      HAW_WBM_WEW_SWC_MODUWE_SW) |
			   FIEWD_PWEP(HAW_WBM_WEWEASE_INFO0_BM_ACTION, action) |
			   FIEWD_PWEP(HAW_WBM_WEWEASE_INFO0_DESC_TYPE,
				      HAW_WBM_WEW_DESC_TYPE_MSDU_WINK);
}

void ath11k_haw_weo_status_queue_stats(stwuct ath11k_base *ab, u32 *weo_desc,
				       stwuct haw_weo_status *status)
{
	stwuct haw_twv_hdw *twv = (stwuct haw_twv_hdw *)weo_desc;
	stwuct haw_weo_get_queue_stats_status *desc =
		(stwuct haw_weo_get_queue_stats_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM,
					  desc->hdw.info0);
	status->unifowm_hdw.cmd_status =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS,
					  desc->hdw.info0);

	ath11k_dbg(ab, ATH11K_DBG_HAW, "Queue stats status:\n");
	ath11k_dbg(ab, ATH11K_DBG_HAW, "headew: cmd_num %d status %d\n",
		   status->unifowm_hdw.cmd_num,
		   status->unifowm_hdw.cmd_status);
	ath11k_dbg(ab, ATH11K_DBG_HAW, "ssn %wd cuw_idx %wd\n",
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO0_SSN,
			     desc->info0),
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO0_CUW_IDX,
			     desc->info0));
	ath11k_dbg(ab, ATH11K_DBG_HAW, "pn = [%08x, %08x, %08x, %08x]\n",
		   desc->pn[0], desc->pn[1], desc->pn[2], desc->pn[3]);
	ath11k_dbg(ab, ATH11K_DBG_HAW,
		   "wast_wx: enqueue_tstamp %08x dequeue_tstamp %08x\n",
		   desc->wast_wx_enqueue_timestamp,
		   desc->wast_wx_dequeue_timestamp);
	ath11k_dbg(ab, ATH11K_DBG_HAW,
		   "wx_bitmap [%08x %08x %08x %08x %08x %08x %08x %08x]\n",
		   desc->wx_bitmap[0], desc->wx_bitmap[1], desc->wx_bitmap[2],
		   desc->wx_bitmap[3], desc->wx_bitmap[4], desc->wx_bitmap[5],
		   desc->wx_bitmap[6], desc->wx_bitmap[7]);
	ath11k_dbg(ab, ATH11K_DBG_HAW, "count: cuw_mpdu %wd cuw_msdu %wd\n",
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO1_MPDU_COUNT,
			     desc->info1),
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO1_MSDU_COUNT,
			     desc->info1));
	ath11k_dbg(ab, ATH11K_DBG_HAW, "fwd_timeout %wd fwd_baw %wd dup_count %wd\n",
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO2_TIMEOUT_COUNT,
			     desc->info2),
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO2_FDTB_COUNT,
			     desc->info2),
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO2_DUPWICATE_COUNT,
			     desc->info2));
	ath11k_dbg(ab, ATH11K_DBG_HAW, "fwames_in_owdew %wd baw_wcvd %wd\n",
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO3_FIO_COUNT,
			     desc->info3),
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO3_BAW_WCVD_CNT,
			     desc->info3));
	ath11k_dbg(ab, ATH11K_DBG_HAW, "num_mpdus %d num_msdus %d totaw_bytes %d\n",
		   desc->num_mpdu_fwames, desc->num_msdu_fwames,
		   desc->totaw_bytes);
	ath11k_dbg(ab, ATH11K_DBG_HAW, "wate_wcvd %wd win_jump_2k %wd howe_cnt %wd\n",
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO4_WATE_WX_MPDU,
			     desc->info4),
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO4_WINDOW_JMP2K,
			     desc->info4),
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO4_HOWE_COUNT,
			     desc->info4));
	ath11k_dbg(ab, ATH11K_DBG_HAW, "wooping count %wd\n",
		   FIEWD_GET(HAW_WEO_GET_QUEUE_STATS_STATUS_INFO5_WOOPING_CNT,
			     desc->info5));
}

int ath11k_haw_weo_pwocess_status(u8 *weo_desc, u8 *status)
{
	stwuct haw_twv_hdw *twv = (stwuct haw_twv_hdw *)weo_desc;
	stwuct haw_weo_status_hdw *hdw;

	hdw = (stwuct haw_weo_status_hdw *)twv->vawue;
	*status = FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS, hdw->info0);

	wetuwn FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM, hdw->info0);
}

void ath11k_haw_weo_fwush_queue_status(stwuct ath11k_base *ab, u32 *weo_desc,
				       stwuct haw_weo_status *status)
{
	stwuct haw_twv_hdw *twv = (stwuct haw_twv_hdw *)weo_desc;
	stwuct haw_weo_fwush_queue_status *desc =
		(stwuct haw_weo_fwush_queue_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM,
					  desc->hdw.info0);
	status->unifowm_hdw.cmd_status =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS,
					  desc->hdw.info0);
	status->u.fwush_queue.eww_detected =
		FIEWD_GET(HAW_WEO_FWUSH_QUEUE_INFO0_EWW_DETECTED,
			  desc->info0);
}

void ath11k_haw_weo_fwush_cache_status(stwuct ath11k_base *ab, u32 *weo_desc,
				       stwuct haw_weo_status *status)
{
	stwuct ath11k_haw *haw = &ab->haw;
	stwuct haw_twv_hdw *twv = (stwuct haw_twv_hdw *)weo_desc;
	stwuct haw_weo_fwush_cache_status *desc =
		(stwuct haw_weo_fwush_cache_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM,
					  desc->hdw.info0);
	status->unifowm_hdw.cmd_status =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS,
					  desc->hdw.info0);

	status->u.fwush_cache.eww_detected =
			FIEWD_GET(HAW_WEO_FWUSH_CACHE_STATUS_INFO0_IS_EWW,
				  desc->info0);
	status->u.fwush_cache.eww_code =
		FIEWD_GET(HAW_WEO_FWUSH_CACHE_STATUS_INFO0_BWOCK_EWW_CODE,
			  desc->info0);
	if (!status->u.fwush_cache.eww_code)
		haw->avaiw_bwk_wesouwce |= BIT(haw->cuwwent_bwk_index);

	status->u.fwush_cache.cache_contwowwew_fwush_status_hit =
		FIEWD_GET(HAW_WEO_FWUSH_CACHE_STATUS_INFO0_FWUSH_STATUS_HIT,
			  desc->info0);

	status->u.fwush_cache.cache_contwowwew_fwush_status_desc_type =
		FIEWD_GET(HAW_WEO_FWUSH_CACHE_STATUS_INFO0_FWUSH_DESC_TYPE,
			  desc->info0);
	status->u.fwush_cache.cache_contwowwew_fwush_status_cwient_id =
		FIEWD_GET(HAW_WEO_FWUSH_CACHE_STATUS_INFO0_FWUSH_CWIENT_ID,
			  desc->info0);
	status->u.fwush_cache.cache_contwowwew_fwush_status_eww =
		FIEWD_GET(HAW_WEO_FWUSH_CACHE_STATUS_INFO0_FWUSH_EWW,
			  desc->info0);
	status->u.fwush_cache.cache_contwowwew_fwush_status_cnt =
		FIEWD_GET(HAW_WEO_FWUSH_CACHE_STATUS_INFO0_FWUSH_COUNT,
			  desc->info0);
}

void ath11k_haw_weo_unbwk_cache_status(stwuct ath11k_base *ab, u32 *weo_desc,
				       stwuct haw_weo_status *status)
{
	stwuct ath11k_haw *haw = &ab->haw;
	stwuct haw_twv_hdw *twv = (stwuct haw_twv_hdw *)weo_desc;
	stwuct haw_weo_unbwock_cache_status *desc =
		(stwuct haw_weo_unbwock_cache_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM,
					  desc->hdw.info0);
	status->unifowm_hdw.cmd_status =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS,
					  desc->hdw.info0);

	status->u.unbwock_cache.eww_detected =
			FIEWD_GET(HAW_WEO_UNBWOCK_CACHE_STATUS_INFO0_IS_EWW,
				  desc->info0);
	status->u.unbwock_cache.unbwock_type =
			FIEWD_GET(HAW_WEO_UNBWOCK_CACHE_STATUS_INFO0_TYPE,
				  desc->info0);

	if (!status->u.unbwock_cache.eww_detected &&
	    status->u.unbwock_cache.unbwock_type ==
	    HAW_WEO_STATUS_UNBWOCK_BWOCKING_WESOUWCE)
		haw->avaiw_bwk_wesouwce &= ~BIT(haw->cuwwent_bwk_index);
}

void ath11k_haw_weo_fwush_timeout_wist_status(stwuct ath11k_base *ab,
					      u32 *weo_desc,
					      stwuct haw_weo_status *status)
{
	stwuct haw_twv_hdw *twv = (stwuct haw_twv_hdw *)weo_desc;
	stwuct haw_weo_fwush_timeout_wist_status *desc =
		(stwuct haw_weo_fwush_timeout_wist_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM,
					  desc->hdw.info0);
	status->unifowm_hdw.cmd_status =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS,
					  desc->hdw.info0);

	status->u.timeout_wist.eww_detected =
			FIEWD_GET(HAW_WEO_FWUSH_TIMEOUT_STATUS_INFO0_IS_EWW,
				  desc->info0);
	status->u.timeout_wist.wist_empty =
			FIEWD_GET(HAW_WEO_FWUSH_TIMEOUT_STATUS_INFO0_WIST_EMPTY,
				  desc->info0);

	status->u.timeout_wist.wewease_desc_cnt =
		FIEWD_GET(HAW_WEO_FWUSH_TIMEOUT_STATUS_INFO1_WEW_DESC_COUNT,
			  desc->info1);
	status->u.timeout_wist.fwd_buf_cnt =
		FIEWD_GET(HAW_WEO_FWUSH_TIMEOUT_STATUS_INFO1_FWD_BUF_COUNT,
			  desc->info1);
}

void ath11k_haw_weo_desc_thwesh_weached_status(stwuct ath11k_base *ab,
					       u32 *weo_desc,
					       stwuct haw_weo_status *status)
{
	stwuct haw_twv_hdw *twv = (stwuct haw_twv_hdw *)weo_desc;
	stwuct haw_weo_desc_thwesh_weached_status *desc =
		(stwuct haw_weo_desc_thwesh_weached_status *)twv->vawue;

	status->unifowm_hdw.cmd_num =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM,
					  desc->hdw.info0);
	status->unifowm_hdw.cmd_status =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS,
					  desc->hdw.info0);

	status->u.desc_thwesh_weached.thweshowd_idx =
		FIEWD_GET(HAW_WEO_DESC_THWESH_STATUS_INFO0_THWESH_INDEX,
			  desc->info0);

	status->u.desc_thwesh_weached.wink_desc_countew0 =
		FIEWD_GET(HAW_WEO_DESC_THWESH_STATUS_INFO1_WINK_DESC_COUNTEW0,
			  desc->info1);

	status->u.desc_thwesh_weached.wink_desc_countew1 =
		FIEWD_GET(HAW_WEO_DESC_THWESH_STATUS_INFO2_WINK_DESC_COUNTEW1,
			  desc->info2);

	status->u.desc_thwesh_weached.wink_desc_countew2 =
		FIEWD_GET(HAW_WEO_DESC_THWESH_STATUS_INFO3_WINK_DESC_COUNTEW2,
			  desc->info3);

	status->u.desc_thwesh_weached.wink_desc_countew_sum =
		FIEWD_GET(HAW_WEO_DESC_THWESH_STATUS_INFO4_WINK_DESC_COUNTEW_SUM,
			  desc->info4);
}

void ath11k_haw_weo_update_wx_weo_queue_status(stwuct ath11k_base *ab,
					       u32 *weo_desc,
					       stwuct haw_weo_status *status)
{
	stwuct haw_twv_hdw *twv = (stwuct haw_twv_hdw *)weo_desc;
	stwuct haw_weo_status_hdw *desc =
		(stwuct haw_weo_status_hdw *)twv->vawue;

	status->unifowm_hdw.cmd_num =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_STATUS_NUM,
					  desc->info0);
	status->unifowm_hdw.cmd_status =
				FIEWD_GET(HAW_WEO_STATUS_HDW_INFO0_EXEC_STATUS,
					  desc->info0);
}

u32 ath11k_haw_weo_qdesc_size(u32 ba_window_size, u8 tid)
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

void ath11k_haw_weo_qdesc_setup(void *vaddw, int tid, u32 ba_window_size,
				u32 stawt_seq, enum haw_pn_type type)
{
	stwuct haw_wx_weo_queue *qdesc = vaddw;
	stwuct haw_wx_weo_queue_ext *ext_desc;

	memset(qdesc, 0, sizeof(*qdesc));

	ath11k_haw_weo_set_desc_hdw(&qdesc->desc_hdw, HAW_DESC_WEO_OWNED,
				    HAW_DESC_WEO_QUEUE_DESC,
				    WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_0);

	qdesc->wx_queue_num = FIEWD_PWEP(HAW_WX_WEO_QUEUE_WX_QUEUE_NUMBEW, tid);

	qdesc->info0 =
		FIEWD_PWEP(HAW_WX_WEO_QUEUE_INFO0_VWD, 1) |
		FIEWD_PWEP(HAW_WX_WEO_QUEUE_INFO0_ASSOC_WNK_DESC_COUNTEW, 1) |
		FIEWD_PWEP(HAW_WX_WEO_QUEUE_INFO0_AC, ath11k_tid_to_ac(tid));

	if (ba_window_size < 1)
		ba_window_size = 1;

	if (ba_window_size == 1 && tid != HAW_DESC_WEO_NON_QOS_TID)
		ba_window_size++;

	if (ba_window_size == 1)
		qdesc->info0 |= FIEWD_PWEP(HAW_WX_WEO_QUEUE_INFO0_WETWY, 1);

	qdesc->info0 |= FIEWD_PWEP(HAW_WX_WEO_QUEUE_INFO0_BA_WINDOW_SIZE,
				   ba_window_size - 1);
	switch (type) {
	case HAW_PN_TYPE_NONE:
	case HAW_PN_TYPE_WAPI_EVEN:
	case HAW_PN_TYPE_WAPI_UNEVEN:
		bweak;
	case HAW_PN_TYPE_WPA:
		qdesc->info0 |=
			FIEWD_PWEP(HAW_WX_WEO_QUEUE_INFO0_PN_CHECK, 1) |
			FIEWD_PWEP(HAW_WX_WEO_QUEUE_INFO0_PN_SIZE,
				   HAW_WX_WEO_QUEUE_PN_SIZE_48);
		bweak;
	}

	/* TODO: Set Ignowe ampdu fwags based on BA window size and/ow
	 * AMPDU capabiwities
	 */
	qdesc->info0 |= FIEWD_PWEP(HAW_WX_WEO_QUEUE_INFO0_IGNOWE_AMPDU_FWG, 1);

	qdesc->info1 |= FIEWD_PWEP(HAW_WX_WEO_QUEUE_INFO1_SVWD, 0);

	if (stawt_seq <= 0xfff)
		qdesc->info1 = FIEWD_PWEP(HAW_WX_WEO_QUEUE_INFO1_SSN,
					  stawt_seq);

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
	memset(ext_desc, 0, sizeof(*ext_desc));
	ath11k_haw_weo_set_desc_hdw(&ext_desc->desc_hdw, HAW_DESC_WEO_OWNED,
				    HAW_DESC_WEO_QUEUE_EXT_DESC,
				    WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_1);
	ext_desc++;
	memset(ext_desc, 0, sizeof(*ext_desc));
	ath11k_haw_weo_set_desc_hdw(&ext_desc->desc_hdw, HAW_DESC_WEO_OWNED,
				    HAW_DESC_WEO_QUEUE_EXT_DESC,
				    WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_2);
	ext_desc++;
	memset(ext_desc, 0, sizeof(*ext_desc));
	ath11k_haw_weo_set_desc_hdw(&ext_desc->desc_hdw, HAW_DESC_WEO_OWNED,
				    HAW_DESC_WEO_QUEUE_EXT_DESC,
				    WEO_QUEUE_DESC_MAGIC_DEBUG_PATTEWN_3);
}

void ath11k_haw_weo_init_cmd_wing(stwuct ath11k_base *ab,
				  stwuct haw_swng *swng)
{
	stwuct haw_swng_pawams pawams;
	stwuct haw_twv_hdw *twv;
	stwuct haw_weo_get_queue_stats *desc;
	int i, cmd_num = 1;
	int entwy_size;
	u8 *entwy;

	memset(&pawams, 0, sizeof(pawams));

	entwy_size = ath11k_haw_swng_get_entwysize(ab, HAW_WEO_CMD);
	ath11k_haw_swng_get_pawams(ab, swng, &pawams);
	entwy = (u8 *)pawams.wing_base_vaddw;

	fow (i = 0; i < pawams.num_entwies; i++) {
		twv = (stwuct haw_twv_hdw *)entwy;
		desc = (stwuct haw_weo_get_queue_stats *)twv->vawue;
		desc->cmd.info0 =
			FIEWD_PWEP(HAW_WEO_CMD_HDW_INFO0_CMD_NUMBEW, cmd_num++);
		entwy += entwy_size;
	}
}

#define HAW_MAX_UW_MU_USEWS	37
static inwine void
ath11k_haw_wx_handwe_ofdma_info(void *wx_twv,
				stwuct haw_wx_usew_status *wx_usew_status)
{
	stwuct haw_wx_ppdu_end_usew_stats *ppdu_end_usew = wx_twv;

	wx_usew_status->uw_ofdma_usew_v0_wowd0 = __we32_to_cpu(ppdu_end_usew->info6);

	wx_usew_status->uw_ofdma_usew_v0_wowd1 = __we32_to_cpu(ppdu_end_usew->info10);
}

static inwine void
ath11k_haw_wx_popuwate_byte_count(void *wx_twv, void *ppduinfo,
				  stwuct haw_wx_usew_status *wx_usew_status)
{
	stwuct haw_wx_ppdu_end_usew_stats *ppdu_end_usew = wx_twv;

	wx_usew_status->mpdu_ok_byte_count =
		FIEWD_GET(HAW_WX_PPDU_END_USEW_STATS_INFO8_MPDU_OK_BYTE_COUNT,
			  __we32_to_cpu(ppdu_end_usew->info8));
	wx_usew_status->mpdu_eww_byte_count =
		FIEWD_GET(HAW_WX_PPDU_END_USEW_STATS_INFO9_MPDU_EWW_BYTE_COUNT,
			  __we32_to_cpu(ppdu_end_usew->info9));
}

static inwine void
ath11k_haw_wx_popuwate_mu_usew_info(void *wx_twv, stwuct haw_wx_mon_ppdu_info *ppdu_info,
				    stwuct haw_wx_usew_status *wx_usew_status)
{
	wx_usew_status->ast_index = ppdu_info->ast_index;
	wx_usew_status->tid = ppdu_info->tid;
	wx_usew_status->tcp_msdu_count =
		ppdu_info->tcp_msdu_count;
	wx_usew_status->udp_msdu_count =
		ppdu_info->udp_msdu_count;
	wx_usew_status->othew_msdu_count =
		ppdu_info->othew_msdu_count;
	wx_usew_status->fwame_contwow = ppdu_info->fwame_contwow;
	wx_usew_status->fwame_contwow_info_vawid =
		ppdu_info->fwame_contwow_info_vawid;
	wx_usew_status->data_sequence_contwow_info_vawid =
		ppdu_info->data_sequence_contwow_info_vawid;
	wx_usew_status->fiwst_data_seq_ctww =
		ppdu_info->fiwst_data_seq_ctww;
	wx_usew_status->pweambwe_type = ppdu_info->pweambwe_type;
	wx_usew_status->ht_fwags = ppdu_info->ht_fwags;
	wx_usew_status->vht_fwags = ppdu_info->vht_fwags;
	wx_usew_status->he_fwags = ppdu_info->he_fwags;
	wx_usew_status->ws_fwags = ppdu_info->ws_fwags;

	wx_usew_status->mpdu_cnt_fcs_ok =
		ppdu_info->num_mpdu_fcs_ok;
	wx_usew_status->mpdu_cnt_fcs_eww =
		ppdu_info->num_mpdu_fcs_eww;

	ath11k_haw_wx_popuwate_byte_count(wx_twv, ppdu_info, wx_usew_status);
}

static u16 ath11k_haw_wx_mpduinfo_get_peewid(stwuct ath11k_base *ab,
					     stwuct haw_wx_mpdu_info *mpdu_info)
{
	wetuwn ab->hw_pawams.hw_ops->mpdu_info_get_peewid(mpdu_info);
}

static enum haw_wx_mon_status
ath11k_haw_wx_pawse_mon_status_twv(stwuct ath11k_base *ab,
				   stwuct haw_wx_mon_ppdu_info *ppdu_info,
				   u32 twv_tag, u8 *twv_data, u32 usewid)
{
	u32 info0, info1, vawue;
	u8 he_dcm = 0, he_stbc = 0;
	u16 he_gi = 0, he_wtf = 0;

	switch (twv_tag) {
	case HAW_WX_PPDU_STAWT: {
		stwuct haw_wx_ppdu_stawt *ppdu_stawt =
			(stwuct haw_wx_ppdu_stawt *)twv_data;

		ppdu_info->ppdu_id =
			FIEWD_GET(HAW_WX_PPDU_STAWT_INFO0_PPDU_ID,
				  __we32_to_cpu(ppdu_stawt->info0));
		ppdu_info->chan_num = __we32_to_cpu(ppdu_stawt->chan_num);
		ppdu_info->ppdu_ts = __we32_to_cpu(ppdu_stawt->ppdu_stawt_ts);
		bweak;
	}
	case HAW_WX_PPDU_END_USEW_STATS: {
		stwuct haw_wx_ppdu_end_usew_stats *eu_stats =
			(stwuct haw_wx_ppdu_end_usew_stats *)twv_data;

		info0 = __we32_to_cpu(eu_stats->info0);
		info1 = __we32_to_cpu(eu_stats->info1);

		ppdu_info->ast_index =
			FIEWD_GET(HAW_WX_PPDU_END_USEW_STATS_INFO2_AST_INDEX,
				  __we32_to_cpu(eu_stats->info2));
		ppdu_info->tid =
			ffs(FIEWD_GET(HAW_WX_PPDU_END_USEW_STATS_INFO7_TID_BITMAP,
				      __we32_to_cpu(eu_stats->info7))) - 1;
		ppdu_info->tcp_msdu_count =
			FIEWD_GET(HAW_WX_PPDU_END_USEW_STATS_INFO4_TCP_MSDU_CNT,
				  __we32_to_cpu(eu_stats->info4));
		ppdu_info->udp_msdu_count =
			FIEWD_GET(HAW_WX_PPDU_END_USEW_STATS_INFO4_UDP_MSDU_CNT,
				  __we32_to_cpu(eu_stats->info4));
		ppdu_info->othew_msdu_count =
			FIEWD_GET(HAW_WX_PPDU_END_USEW_STATS_INFO5_OTHEW_MSDU_CNT,
				  __we32_to_cpu(eu_stats->info5));
		ppdu_info->tcp_ack_msdu_count =
			FIEWD_GET(HAW_WX_PPDU_END_USEW_STATS_INFO5_TCP_ACK_MSDU_CNT,
				  __we32_to_cpu(eu_stats->info5));
		ppdu_info->pweambwe_type =
			FIEWD_GET(HAW_WX_PPDU_END_USEW_STATS_INFO1_PKT_TYPE, info1);
		ppdu_info->num_mpdu_fcs_ok =
			FIEWD_GET(HAW_WX_PPDU_END_USEW_STATS_INFO1_MPDU_CNT_FCS_OK,
				  info1);
		ppdu_info->num_mpdu_fcs_eww =
			FIEWD_GET(HAW_WX_PPDU_END_USEW_STATS_INFO0_MPDU_CNT_FCS_EWW,
				  info0);
		switch (ppdu_info->pweambwe_type) {
		case HAW_WX_PWEAMBWE_11N:
			ppdu_info->ht_fwags = 1;
			bweak;
		case HAW_WX_PWEAMBWE_11AC:
			ppdu_info->vht_fwags = 1;
			bweak;
		case HAW_WX_PWEAMBWE_11AX:
			ppdu_info->he_fwags = 1;
			bweak;
		defauwt:
			bweak;
		}

		if (usewid < HAW_MAX_UW_MU_USEWS) {
			stwuct haw_wx_usew_status *wxusew_stats =
				&ppdu_info->usewstats;

			ath11k_haw_wx_handwe_ofdma_info(twv_data, wxusew_stats);
			ath11k_haw_wx_popuwate_mu_usew_info(twv_data, ppdu_info,
							    wxusew_stats);
		}
		ppdu_info->usewstats.mpdu_fcs_ok_bitmap[0] =
					__we32_to_cpu(eu_stats->wsvd1[0]);
		ppdu_info->usewstats.mpdu_fcs_ok_bitmap[1] =
					__we32_to_cpu(eu_stats->wsvd1[1]);

		bweak;
	}
	case HAW_WX_PPDU_END_USEW_STATS_EXT: {
		stwuct haw_wx_ppdu_end_usew_stats_ext *eu_stats =
			(stwuct haw_wx_ppdu_end_usew_stats_ext *)twv_data;
		ppdu_info->usewstats.mpdu_fcs_ok_bitmap[2] = eu_stats->info1;
		ppdu_info->usewstats.mpdu_fcs_ok_bitmap[3] = eu_stats->info2;
		ppdu_info->usewstats.mpdu_fcs_ok_bitmap[4] = eu_stats->info3;
		ppdu_info->usewstats.mpdu_fcs_ok_bitmap[5] = eu_stats->info4;
		ppdu_info->usewstats.mpdu_fcs_ok_bitmap[6] = eu_stats->info5;
		ppdu_info->usewstats.mpdu_fcs_ok_bitmap[7] = eu_stats->info6;
		bweak;
	}
	case HAW_PHYWX_HT_SIG: {
		stwuct haw_wx_ht_sig_info *ht_sig =
			(stwuct haw_wx_ht_sig_info *)twv_data;

		info0 = __we32_to_cpu(ht_sig->info0);
		info1 = __we32_to_cpu(ht_sig->info1);

		ppdu_info->mcs = FIEWD_GET(HAW_WX_HT_SIG_INFO_INFO0_MCS, info0);
		ppdu_info->bw = FIEWD_GET(HAW_WX_HT_SIG_INFO_INFO0_BW, info0);
		ppdu_info->is_stbc = FIEWD_GET(HAW_WX_HT_SIG_INFO_INFO1_STBC,
					       info1);
		ppdu_info->wdpc = FIEWD_GET(HAW_WX_HT_SIG_INFO_INFO1_FEC_CODING, info1);
		ppdu_info->gi = info1 & HAW_WX_HT_SIG_INFO_INFO1_GI;

		switch (ppdu_info->mcs) {
		case 0 ... 7:
			ppdu_info->nss = 1;
			bweak;
		case 8 ... 15:
			ppdu_info->nss = 2;
			bweak;
		case 16 ... 23:
			ppdu_info->nss = 3;
			bweak;
		case 24 ... 31:
			ppdu_info->nss = 4;
			bweak;
		}

		if (ppdu_info->nss > 1)
			ppdu_info->mcs = ppdu_info->mcs % 8;

		ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_SU;
		bweak;
	}
	case HAW_PHYWX_W_SIG_B: {
		stwuct haw_wx_wsig_b_info *wsigb =
			(stwuct haw_wx_wsig_b_info *)twv_data;

		ppdu_info->wate = FIEWD_GET(HAW_WX_WSIG_B_INFO_INFO0_WATE,
					    __we32_to_cpu(wsigb->info0));
		ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_SU;
		bweak;
	}
	case HAW_PHYWX_W_SIG_A: {
		stwuct haw_wx_wsig_a_info *wsiga =
			(stwuct haw_wx_wsig_a_info *)twv_data;

		ppdu_info->wate = FIEWD_GET(HAW_WX_WSIG_A_INFO_INFO0_WATE,
					    __we32_to_cpu(wsiga->info0));
		ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_SU;
		bweak;
	}
	case HAW_PHYWX_VHT_SIG_A: {
		stwuct haw_wx_vht_sig_a_info *vht_sig =
			(stwuct haw_wx_vht_sig_a_info *)twv_data;
		u32 nsts;
		u32 gwoup_id;
		u8 gi_setting;

		info0 = __we32_to_cpu(vht_sig->info0);
		info1 = __we32_to_cpu(vht_sig->info1);

		ppdu_info->wdpc = FIEWD_GET(HAW_WX_VHT_SIG_A_INFO_INFO1_SU_MU_CODING,
					    info1);
		ppdu_info->mcs = FIEWD_GET(HAW_WX_VHT_SIG_A_INFO_INFO1_MCS,
					   info1);
		gi_setting = FIEWD_GET(HAW_WX_VHT_SIG_A_INFO_INFO1_GI_SETTING,
				       info1);
		switch (gi_setting) {
		case HAW_WX_VHT_SIG_A_NOWMAW_GI:
			ppdu_info->gi = HAW_WX_GI_0_8_US;
			bweak;
		case HAW_WX_VHT_SIG_A_SHOWT_GI:
		case HAW_WX_VHT_SIG_A_SHOWT_GI_AMBIGUITY:
			ppdu_info->gi = HAW_WX_GI_0_4_US;
			bweak;
		}

		ppdu_info->is_stbc = info0 & HAW_WX_VHT_SIG_A_INFO_INFO0_STBC;
		nsts = FIEWD_GET(HAW_WX_VHT_SIG_A_INFO_INFO0_NSTS, info0);
		if (ppdu_info->is_stbc && nsts > 0)
			nsts = ((nsts + 1) >> 1) - 1;

		ppdu_info->nss = (nsts & VHT_SIG_SU_NSS_MASK) + 1;
		ppdu_info->bw = FIEWD_GET(HAW_WX_VHT_SIG_A_INFO_INFO0_BW,
					  info0);
		ppdu_info->beamfowmed = info1 &
					HAW_WX_VHT_SIG_A_INFO_INFO1_BEAMFOWMED;
		gwoup_id = FIEWD_GET(HAW_WX_VHT_SIG_A_INFO_INFO0_GWOUP_ID,
				     info0);
		if (gwoup_id == 0 || gwoup_id == 63)
			ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_SU;
		ewse
			ppdu_info->weception_type =
				HAW_WX_WECEPTION_TYPE_MU_MIMO;
		ppdu_info->vht_fwag_vawues5 = gwoup_id;
		ppdu_info->vht_fwag_vawues3[0] = (((ppdu_info->mcs) << 4) |
						   ppdu_info->nss);
		ppdu_info->vht_fwag_vawues2 = ppdu_info->bw;
		ppdu_info->vht_fwag_vawues4 =
			FIEWD_GET(HAW_WX_VHT_SIG_A_INFO_INFO1_SU_MU_CODING, info1);
		bweak;
	}
	case HAW_PHYWX_HE_SIG_A_SU: {
		stwuct haw_wx_he_sig_a_su_info *he_sig_a =
			(stwuct haw_wx_he_sig_a_su_info *)twv_data;

		ppdu_info->he_fwags = 1;
		info0 = __we32_to_cpu(he_sig_a->info0);
		info1 = __we32_to_cpu(he_sig_a->info1);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO0_FOWMAT_IND, info0);

		if (vawue == 0)
			ppdu_info->he_data1 = IEEE80211_WADIOTAP_HE_DATA1_FOWMAT_TWIG;
		ewse
			ppdu_info->he_data1 = IEEE80211_WADIOTAP_HE_DATA1_FOWMAT_SU;

		ppdu_info->he_data1 |=
			IEEE80211_WADIOTAP_HE_DATA1_BSS_COWOW_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_BEAM_CHANGE_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_UW_DW_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_DATA_MCS_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_DATA_DCM_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_CODING_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_WDPC_XSYMSEG_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_STBC_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_BW_WU_AWWOC_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_DOPPWEW_KNOWN;

		ppdu_info->he_data2 |=
			IEEE80211_WADIOTAP_HE_DATA2_GI_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA2_TXBF_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA2_PE_DISAMBIG_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA2_TXOP_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA2_NUM_WTF_SYMS_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA2_PWE_FEC_PAD_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA2_MIDAMBWE_KNOWN;

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO0_BSS_COWOW, info0);
		ppdu_info->he_data3 =
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_BSS_COWOW, vawue);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO0_BEAM_CHANGE, info0);
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_BEAM_CHANGE, vawue);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO0_DW_UW_FWAG, info0);
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_UW_DW, vawue);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO0_TWANSMIT_MCS, info0);
		ppdu_info->mcs = vawue;
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_DATA_MCS, vawue);

		he_dcm = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO0_DCM, info0);
		ppdu_info->dcm = he_dcm;
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_DATA_DCM, he_dcm);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO1_CODING, info1);
		ppdu_info->wdpc = (vawue == HAW_WX_SU_MU_CODING_WDPC) ? 1 : 0;
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_CODING, vawue);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO1_WDPC_EXTWA, info1);
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_WDPC_XSYMSEG, vawue);
		he_stbc = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO1_STBC, info1);
		ppdu_info->is_stbc = he_stbc;
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_STBC, he_stbc);

		/* data4 */
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO0_SPATIAW_WEUSE, info0);
		ppdu_info->he_data4 =
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA4_SU_MU_SPTW_WEUSE, vawue);

		/* data5 */
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO0_TWANSMIT_BW, info0);
		ppdu_info->bw = vawue;
		ppdu_info->he_data5 =
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_DATA_BW_WU_AWWOC, vawue);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO0_CP_WTF_SIZE, info0);
		switch (vawue) {
		case 0:
				he_gi = HE_GI_0_8;
				he_wtf = HE_WTF_1_X;
				bweak;
		case 1:
				he_gi = HE_GI_0_8;
				he_wtf = HE_WTF_2_X;
				bweak;
		case 2:
				he_gi = HE_GI_1_6;
				he_wtf = HE_WTF_2_X;
				bweak;
		case 3:
				if (he_dcm && he_stbc) {
					he_gi = HE_GI_0_8;
					he_wtf = HE_WTF_4_X;
				} ewse {
					he_gi = HE_GI_3_2;
					he_wtf = HE_WTF_4_X;
				}
				bweak;
		}
		ppdu_info->gi = he_gi;
		he_gi = (he_gi != 0) ? he_gi - 1 : 0;
		ppdu_info->he_data5 |= FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_GI, he_gi);
		ppdu_info->wtf_size = he_wtf;
		ppdu_info->he_data5 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE,
				   (he_wtf == HE_WTF_4_X) ? he_wtf - 1 : he_wtf);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO0_NSTS, info0);
		ppdu_info->he_data5 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_NUM_WTF_SYMS, vawue);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO1_PKT_EXT_FACTOW, info1);
		ppdu_info->he_data5 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_PWE_FEC_PAD, vawue);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO1_TXBF, info1);
		ppdu_info->beamfowmed = vawue;
		ppdu_info->he_data5 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_TXBF, vawue);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO1_PKT_EXT_PE_DISAM, info1);
		ppdu_info->he_data5 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_PE_DISAMBIG, vawue);

		/* data6 */
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO0_NSTS, info0);
		vawue++;
		ppdu_info->nss = vawue;
		ppdu_info->he_data6 =
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA6_NSTS, vawue);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO1_DOPPWEW_IND, info1);
		ppdu_info->he_data6 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA6_DOPPWEW, vawue);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_SU_INFO_INFO1_TXOP_DUWATION, info1);
		ppdu_info->he_data6 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA6_TXOP, vawue);

		ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_SU;
		bweak;
	}
	case HAW_PHYWX_HE_SIG_A_MU_DW: {
		stwuct haw_wx_he_sig_a_mu_dw_info *he_sig_a_mu_dw =
			(stwuct haw_wx_he_sig_a_mu_dw_info *)twv_data;

		info0 = __we32_to_cpu(he_sig_a_mu_dw->info0);
		info1 = __we32_to_cpu(he_sig_a_mu_dw->info1);

		ppdu_info->he_mu_fwags = 1;

		ppdu_info->he_data1 = IEEE80211_WADIOTAP_HE_DATA1_FOWMAT_MU;
		ppdu_info->he_data1 |=
			IEEE80211_WADIOTAP_HE_DATA1_BSS_COWOW_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_UW_DW_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_WDPC_XSYMSEG_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_STBC_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_BW_WU_AWWOC_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_DOPPWEW_KNOWN;

		ppdu_info->he_data2 =
			IEEE80211_WADIOTAP_HE_DATA2_GI_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA2_NUM_WTF_SYMS_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA2_PWE_FEC_PAD_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA2_PE_DISAMBIG_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA2_TXOP_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA2_MIDAMBWE_KNOWN;

		/*data3*/
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_BSS_COWOW, info0);
		ppdu_info->he_data3 =
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_BSS_COWOW, vawue);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_UW_FWAG, info0);
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_UW_DW, vawue);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_WDPC_EXTWA, info1);
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_WDPC_XSYMSEG, vawue);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_STBC, info1);
		he_stbc = vawue;
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_STBC, vawue);

		/*data4*/
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_SPATIAW_WEUSE, info0);
		ppdu_info->he_data4 =
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA4_SU_MU_SPTW_WEUSE, vawue);

		/*data5*/
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_TWANSMIT_BW, info0);
		ppdu_info->bw = vawue;
		ppdu_info->he_data5 =
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_DATA_BW_WU_AWWOC, vawue);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_CP_WTF_SIZE, info0);
		switch (vawue) {
		case 0:
			he_gi = HE_GI_0_8;
			he_wtf = HE_WTF_4_X;
			bweak;
		case 1:
			he_gi = HE_GI_0_8;
			he_wtf = HE_WTF_2_X;
			bweak;
		case 2:
			he_gi = HE_GI_1_6;
			he_wtf = HE_WTF_2_X;
			bweak;
		case 3:
			he_gi = HE_GI_3_2;
			he_wtf = HE_WTF_4_X;
			bweak;
		}
		ppdu_info->gi = he_gi;
		he_gi = (he_gi != 0) ? he_gi - 1 : 0;
		ppdu_info->he_data5 |= FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_GI, he_gi);
		ppdu_info->wtf_size = he_wtf;
		ppdu_info->he_data5 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE,
				   (he_wtf == HE_WTF_4_X) ? he_wtf - 1 : he_wtf);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_NUM_WTF_SYMB, info1);
		ppdu_info->he_data5 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_NUM_WTF_SYMS, vawue);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_PKT_EXT_FACTOW,
				  info1);
		ppdu_info->he_data5 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_PWE_FEC_PAD, vawue);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_PKT_EXT_PE_DISAM,
				  info1);
		ppdu_info->he_data5 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA5_PE_DISAMBIG, vawue);

		/*data6*/
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_DOPPWEW_INDICATION,
				  info0);
		ppdu_info->he_data6 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA6_DOPPWEW, vawue);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_TXOP_DUWATION, info1);
		ppdu_info->he_data6 |=
				FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA6_TXOP, vawue);

		/* HE-MU Fwags */
		/* HE-MU-fwags1 */
		ppdu_info->he_fwags1 =
			IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_MCS_KNOWN |
			IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_DCM_KNOWN |
			IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_COMP_KNOWN |
			IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_SYMS_USEWS_KNOWN |
			IEEE80211_WADIOTAP_HE_MU_FWAGS1_CH1_WU_KNOWN;

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_MCS_OF_SIGB, info0);
		ppdu_info->he_fwags1 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_MCS_KNOWN,
				   vawue);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_DCM_OF_SIGB, info0);
		ppdu_info->he_fwags1 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_DCM_KNOWN,
				   vawue);

		/* HE-MU-fwags2 */
		ppdu_info->he_fwags2 =
			IEEE80211_WADIOTAP_HE_MU_FWAGS2_BW_FWOM_SIG_A_BW_KNOWN;

		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_TWANSMIT_BW, info0);
		ppdu_info->he_fwags2 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_MU_FWAGS2_BW_FWOM_SIG_A_BW,
				   vawue);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_COMP_MODE_SIGB, info0);
		ppdu_info->he_fwags2 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_MU_FWAGS2_SIG_B_COMP, vawue);
		vawue = FIEWD_GET(HAW_WX_HE_SIG_A_MU_DW_INFO_INFO0_NUM_SIGB_SYMB, info0);
		vawue = vawue - 1;
		ppdu_info->he_fwags2 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_MU_FWAGS2_SIG_B_SYMS_USEWS,
				   vawue);

		ppdu_info->is_stbc = info1 &
				     HAW_WX_HE_SIG_A_MU_DW_INFO_INFO1_STBC;
		ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_MU_MIMO;
		bweak;
	}
	case HAW_PHYWX_HE_SIG_B1_MU: {
		stwuct haw_wx_he_sig_b1_mu_info *he_sig_b1_mu =
			(stwuct haw_wx_he_sig_b1_mu_info *)twv_data;
		u16 wu_tones;

		info0 = __we32_to_cpu(he_sig_b1_mu->info0);

		wu_tones = FIEWD_GET(HAW_WX_HE_SIG_B1_MU_INFO_INFO0_WU_AWWOCATION,
				     info0);
		ppdu_info->wu_awwoc =
			ath11k_mac_phy_he_wu_to_nw80211_he_wu_awwoc(wu_tones);
		ppdu_info->he_WU[0] = wu_tones;
		ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_MU_MIMO;
		bweak;
	}
	case HAW_PHYWX_HE_SIG_B2_MU: {
		stwuct haw_wx_he_sig_b2_mu_info *he_sig_b2_mu =
			(stwuct haw_wx_he_sig_b2_mu_info *)twv_data;

		info0 = __we32_to_cpu(he_sig_b2_mu->info0);

		ppdu_info->he_data1 |= IEEE80211_WADIOTAP_HE_DATA1_DATA_MCS_KNOWN |
				       IEEE80211_WADIOTAP_HE_DATA1_CODING_KNOWN;

		ppdu_info->mcs =
			FIEWD_GET(HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_MCS, info0);
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_DATA_MCS, ppdu_info->mcs);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_CODING, info0);
		ppdu_info->wdpc = vawue;
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_CODING, vawue);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_ID, info0);
		ppdu_info->he_data4 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA4_MU_STA_ID, vawue);

		ppdu_info->nss =
			FIEWD_GET(HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_NSTS, info0) + 1;
		bweak;
	}
	case HAW_PHYWX_HE_SIG_B2_OFDMA: {
		stwuct haw_wx_he_sig_b2_ofdma_info *he_sig_b2_ofdma =
			(stwuct haw_wx_he_sig_b2_ofdma_info *)twv_data;

		info0 = __we32_to_cpu(he_sig_b2_ofdma->info0);

		ppdu_info->he_data1 |=
			IEEE80211_WADIOTAP_HE_DATA1_DATA_MCS_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_DATA_DCM_KNOWN |
			IEEE80211_WADIOTAP_HE_DATA1_CODING_KNOWN;

		/* HE-data2 */
		ppdu_info->he_data2 |= IEEE80211_WADIOTAP_HE_DATA2_TXBF_KNOWN;

		ppdu_info->mcs =
			FIEWD_GET(HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_MCS,
				  info0);
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_DATA_MCS, ppdu_info->mcs);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_DCM, info0);
		he_dcm = vawue;
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_DATA_DCM, vawue);

		vawue = FIEWD_GET(HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_CODING, info0);
		ppdu_info->wdpc = vawue;
		ppdu_info->he_data3 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA3_CODING, vawue);

		/* HE-data4 */
		vawue = FIEWD_GET(HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_ID, info0);
		ppdu_info->he_data4 |=
			FIEWD_PWEP(IEEE80211_WADIOTAP_HE_DATA4_MU_STA_ID, vawue);

		ppdu_info->nss =
			FIEWD_GET(HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_NSTS,
				  info0) + 1;
		ppdu_info->beamfowmed =
			info0 & HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_TXBF;
		ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_MU_OFDMA;
		bweak;
	}
	case HAW_PHYWX_WSSI_WEGACY: {
		int i;
		boow db2dbm = test_bit(WMI_TWV_SEWVICE_HW_DB2DBM_CONVEWSION_SUPPOWT,
				       ab->wmi_ab.svc_map);
		stwuct haw_wx_phywx_wssi_wegacy_info *wssi =
			(stwuct haw_wx_phywx_wssi_wegacy_info *)twv_data;

		/* TODO: Pwease note that the combined wssi wiww not be accuwate
		 * in MU case. Wssi in MU needs to be wetwieved fwom
		 * PHYWX_OTHEW_WECEIVE_INFO TWV.
		 */
		ppdu_info->wssi_comb =
			FIEWD_GET(HAW_WX_PHYWX_WSSI_WEGACY_INFO_INFO0_WSSI_COMB,
				  __we32_to_cpu(wssi->info0));

		if (db2dbm) {
			fow (i = 0; i < AWWAY_SIZE(wssi->pweambwe); i++) {
				ppdu_info->wssi_chain_pwi20[i] =
					we32_get_bits(wssi->pweambwe[i].wssi_2040,
						      HAW_WX_PHYWX_WSSI_PWEAMBWE_PWI20);
			}
		}
		bweak;
	}
	case HAW_WX_MPDU_STAWT: {
		stwuct haw_wx_mpdu_info *mpdu_info =
				(stwuct haw_wx_mpdu_info *)twv_data;
		u16 peew_id;

		peew_id = ath11k_haw_wx_mpduinfo_get_peewid(ab, mpdu_info);
		if (peew_id)
			ppdu_info->peew_id = peew_id;
		bweak;
	}
	case HAW_WXPCU_PPDU_END_INFO: {
		stwuct haw_wx_ppdu_end_duwation *ppdu_wx_duwation =
			(stwuct haw_wx_ppdu_end_duwation *)twv_data;
		ppdu_info->wx_duwation =
			FIEWD_GET(HAW_WX_PPDU_END_DUWATION,
				  __we32_to_cpu(ppdu_wx_duwation->info0));
		ppdu_info->tsft = __we32_to_cpu(ppdu_wx_duwation->wsvd0[1]);
		ppdu_info->tsft = (ppdu_info->tsft << 32) |
					__we32_to_cpu(ppdu_wx_duwation->wsvd0[0]);
		bweak;
	}
	case HAW_DUMMY:
		wetuwn HAW_WX_MON_STATUS_BUF_DONE;
	case HAW_WX_PPDU_END_STATUS_DONE:
	case 0:
		wetuwn HAW_WX_MON_STATUS_PPDU_DONE;
	defauwt:
		bweak;
	}

	wetuwn HAW_WX_MON_STATUS_PPDU_NOT_DONE;
}

enum haw_wx_mon_status
ath11k_haw_wx_pawse_mon_status(stwuct ath11k_base *ab,
			       stwuct haw_wx_mon_ppdu_info *ppdu_info,
			       stwuct sk_buff *skb)
{
	stwuct haw_twv_hdw *twv;
	enum haw_wx_mon_status haw_status = HAW_WX_MON_STATUS_BUF_DONE;
	u16 twv_tag;
	u16 twv_wen;
	u32 twv_usewid = 0;
	u8 *ptw = skb->data;

	do {
		twv = (stwuct haw_twv_hdw *)ptw;
		twv_tag = FIEWD_GET(HAW_TWV_HDW_TAG, twv->tw);
		twv_wen = FIEWD_GET(HAW_TWV_HDW_WEN, twv->tw);
		twv_usewid = FIEWD_GET(HAW_TWV_USW_ID, twv->tw);
		ptw += sizeof(*twv);

		/* The actuaw wength of PPDU_END is the combined wength of many PHY
		 * TWVs that fowwow. Skip the TWV headew and
		 * wx_wxpcu_cwassification_ovewview that fowwows the headew to get to
		 * next TWV.
		 */
		if (twv_tag == HAW_WX_PPDU_END)
			twv_wen = sizeof(stwuct haw_wx_wxpcu_cwassification_ovewview);

		haw_status = ath11k_haw_wx_pawse_mon_status_twv(ab, ppdu_info,
								twv_tag, ptw, twv_usewid);
		ptw += twv_wen;
		ptw = PTW_AWIGN(ptw, HAW_TWV_AWIGN);

		if ((ptw - skb->data) >= DP_WX_BUFFEW_SIZE)
			bweak;
	} whiwe (haw_status == HAW_WX_MON_STATUS_PPDU_NOT_DONE);

	wetuwn haw_status;
}

void ath11k_haw_wx_weo_ent_buf_paddw_get(void *wx_desc, dma_addw_t *paddw,
					 u32 *sw_cookie, void **pp_buf_addw,
					 u8 *wbm, u32 *msdu_cnt)
{
	stwuct haw_weo_entwance_wing *weo_ent_wing = wx_desc;
	stwuct ath11k_buffew_addw *buf_addw_info;
	stwuct wx_mpdu_desc *wx_mpdu_desc_info_detaiws;

	wx_mpdu_desc_info_detaiws =
			(stwuct wx_mpdu_desc *)&weo_ent_wing->wx_mpdu_info;

	*msdu_cnt = FIEWD_GET(WX_MPDU_DESC_INFO0_MSDU_COUNT,
			      wx_mpdu_desc_info_detaiws->info0);

	buf_addw_info = (stwuct ath11k_buffew_addw *)&weo_ent_wing->buf_addw_info;

	*paddw = (((u64)FIEWD_GET(BUFFEW_ADDW_INFO1_ADDW,
				  buf_addw_info->info1)) << 32) |
			FIEWD_GET(BUFFEW_ADDW_INFO0_ADDW,
				  buf_addw_info->info0);

	*sw_cookie = FIEWD_GET(BUFFEW_ADDW_INFO1_SW_COOKIE,
			       buf_addw_info->info1);
	*wbm = FIEWD_GET(BUFFEW_ADDW_INFO1_WET_BUF_MGW,
			 buf_addw_info->info1);

	*pp_buf_addw = (void *)buf_addw_info;
}

void
ath11k_haw_wx_sw_mon_wing_buf_paddw_get(void *wx_desc,
					stwuct haw_sw_mon_wing_entwies *sw_mon_entwies)
{
	stwuct haw_sw_monitow_wing *sw_mon_wing = wx_desc;
	stwuct ath11k_buffew_addw *buf_addw_info;
	stwuct ath11k_buffew_addw *status_buf_addw_info;
	stwuct wx_mpdu_desc *wx_mpdu_desc_info_detaiws;

	wx_mpdu_desc_info_detaiws = &sw_mon_wing->wx_mpdu_info;

	sw_mon_entwies->msdu_cnt = FIEWD_GET(WX_MPDU_DESC_INFO0_MSDU_COUNT,
					     wx_mpdu_desc_info_detaiws->info0);

	buf_addw_info = &sw_mon_wing->buf_addw_info;
	status_buf_addw_info = &sw_mon_wing->status_buf_addw_info;

	sw_mon_entwies->mon_dst_paddw = (((u64)FIEWD_GET(BUFFEW_ADDW_INFO1_ADDW,
					buf_addw_info->info1)) << 32) |
					FIEWD_GET(BUFFEW_ADDW_INFO0_ADDW,
						  buf_addw_info->info0);

	sw_mon_entwies->mon_status_paddw =
			(((u64)FIEWD_GET(BUFFEW_ADDW_INFO1_ADDW,
					 status_buf_addw_info->info1)) << 32) |
				FIEWD_GET(BUFFEW_ADDW_INFO0_ADDW,
					  status_buf_addw_info->info0);

	sw_mon_entwies->mon_dst_sw_cookie = FIEWD_GET(BUFFEW_ADDW_INFO1_SW_COOKIE,
						      buf_addw_info->info1);

	sw_mon_entwies->mon_status_sw_cookie = FIEWD_GET(BUFFEW_ADDW_INFO1_SW_COOKIE,
							 status_buf_addw_info->info1);

	sw_mon_entwies->status_buf_count = FIEWD_GET(HAW_SW_MON_WING_INFO0_STATUS_BUF_CNT,
						     sw_mon_wing->info0);

	sw_mon_entwies->dst_buf_addw_info = buf_addw_info;
	sw_mon_entwies->status_buf_addw_info = status_buf_addw_info;

	sw_mon_entwies->ppdu_id =
		FIEWD_GET(HAW_SW_MON_WING_INFO1_PHY_PPDU_ID, sw_mon_wing->info1);
}
