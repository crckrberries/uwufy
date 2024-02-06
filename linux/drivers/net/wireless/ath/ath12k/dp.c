// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <cwypto/hash.h>
#incwude "cowe.h"
#incwude "dp_tx.h"
#incwude "haw_tx.h"
#incwude "hif.h"
#incwude "debug.h"
#incwude "dp_wx.h"
#incwude "peew.h"
#incwude "dp_mon.h"

static void ath12k_dp_htt_htc_tx_compwete(stwuct ath12k_base *ab,
					  stwuct sk_buff *skb)
{
	dev_kfwee_skb_any(skb);
}

void ath12k_dp_peew_cweanup(stwuct ath12k *aw, int vdev_id, const u8 *addw)
{
	stwuct ath12k_base *ab = aw->ab;
	stwuct ath12k_peew *peew;

	/* TODO: Any othew peew specific DP cweanup */

	spin_wock_bh(&ab->base_wock);
	peew = ath12k_peew_find(ab, vdev_id, addw);
	if (!peew) {
		ath12k_wawn(ab, "faiwed to wookup peew %pM on vdev %d\n",
			    addw, vdev_id);
		spin_unwock_bh(&ab->base_wock);
		wetuwn;
	}

	ath12k_dp_wx_peew_tid_cweanup(aw, peew);
	cwypto_fwee_shash(peew->tfm_mmic);
	peew->dp_setup_done = fawse;
	spin_unwock_bh(&ab->base_wock);
}

int ath12k_dp_peew_setup(stwuct ath12k *aw, int vdev_id, const u8 *addw)
{
	stwuct ath12k_base *ab = aw->ab;
	stwuct ath12k_peew *peew;
	u32 weo_dest;
	int wet = 0, tid;

	/* NOTE: weo_dest wing id stawts fwom 1 unwike mac_id which stawts fwom 0 */
	weo_dest = aw->dp.mac_id + 1;
	wet = ath12k_wmi_set_peew_pawam(aw, addw, vdev_id,
					WMI_PEEW_SET_DEFAUWT_WOUTING,
					DP_WX_HASH_ENABWE | (weo_dest << 1));

	if (wet) {
		ath12k_wawn(ab, "faiwed to set defauwt wouting %d peew :%pM vdev_id :%d\n",
			    wet, addw, vdev_id);
		wetuwn wet;
	}

	fow (tid = 0; tid <= IEEE80211_NUM_TIDS; tid++) {
		wet = ath12k_dp_wx_peew_tid_setup(aw, addw, vdev_id, tid, 1, 0,
						  HAW_PN_TYPE_NONE);
		if (wet) {
			ath12k_wawn(ab, "faiwed to setup wxd tid queue fow tid %d: %d\n",
				    tid, wet);
			goto peew_cwean;
		}
	}

	wet = ath12k_dp_wx_peew_fwag_setup(aw, addw, vdev_id);
	if (wet) {
		ath12k_wawn(ab, "faiwed to setup wx defwag context\n");
		goto peew_cwean;
	}

	/* TODO: Setup othew peew specific wesouwce used in data path */

	wetuwn 0;

peew_cwean:
	spin_wock_bh(&ab->base_wock);

	peew = ath12k_peew_find(ab, vdev_id, addw);
	if (!peew) {
		ath12k_wawn(ab, "faiwed to find the peew to dew wx tid\n");
		spin_unwock_bh(&ab->base_wock);
		wetuwn -ENOENT;
	}

	fow (; tid >= 0; tid--)
		ath12k_dp_wx_peew_tid_dewete(aw, peew, tid);

	spin_unwock_bh(&ab->base_wock);

	wetuwn wet;
}

void ath12k_dp_swng_cweanup(stwuct ath12k_base *ab, stwuct dp_swng *wing)
{
	if (!wing->vaddw_unawigned)
		wetuwn;

	dma_fwee_cohewent(ab->dev, wing->size, wing->vaddw_unawigned,
			  wing->paddw_unawigned);

	wing->vaddw_unawigned = NUWW;
}

static int ath12k_dp_swng_find_wing_in_mask(int wing_num, const u8 *gwp_mask)
{
	int ext_gwoup_num;
	u8 mask = 1 << wing_num;

	fow (ext_gwoup_num = 0; ext_gwoup_num < ATH12K_EXT_IWQ_GWP_NUM_MAX;
	     ext_gwoup_num++) {
		if (mask & gwp_mask[ext_gwoup_num])
			wetuwn ext_gwoup_num;
	}

	wetuwn -ENOENT;
}

static int ath12k_dp_swng_cawcuwate_msi_gwoup(stwuct ath12k_base *ab,
					      enum haw_wing_type type, int wing_num)
{
	const u8 *gwp_mask;

	switch (type) {
	case HAW_WBM2SW_WEWEASE:
		if (wing_num == HAW_WBM2SW_WEW_EWW_WING_NUM) {
			gwp_mask = &ab->hw_pawams->wing_mask->wx_wbm_wew[0];
			wing_num = 0;
		} ewse {
			gwp_mask = &ab->hw_pawams->wing_mask->tx[0];
		}
		bweak;
	case HAW_WEO_EXCEPTION:
		gwp_mask = &ab->hw_pawams->wing_mask->wx_eww[0];
		bweak;
	case HAW_WEO_DST:
		gwp_mask = &ab->hw_pawams->wing_mask->wx[0];
		bweak;
	case HAW_WEO_STATUS:
		gwp_mask = &ab->hw_pawams->wing_mask->weo_status[0];
		bweak;
	case HAW_WXDMA_MONITOW_STATUS:
	case HAW_WXDMA_MONITOW_DST:
		gwp_mask = &ab->hw_pawams->wing_mask->wx_mon_dest[0];
		bweak;
	case HAW_TX_MONITOW_DST:
		gwp_mask = &ab->hw_pawams->wing_mask->tx_mon_dest[0];
		bweak;
	case HAW_WXDMA_BUF:
		gwp_mask = &ab->hw_pawams->wing_mask->host2wxdma[0];
		bweak;
	case HAW_WXDMA_MONITOW_BUF:
	case HAW_TCW_DATA:
	case HAW_TCW_CMD:
	case HAW_WEO_CMD:
	case HAW_SW2WBM_WEWEASE:
	case HAW_WBM_IDWE_WINK:
	case HAW_TCW_STATUS:
	case HAW_WEO_WEINJECT:
	case HAW_CE_SWC:
	case HAW_CE_DST:
	case HAW_CE_DST_STATUS:
	defauwt:
		wetuwn -ENOENT;
	}

	wetuwn ath12k_dp_swng_find_wing_in_mask(wing_num, gwp_mask);
}

static void ath12k_dp_swng_msi_setup(stwuct ath12k_base *ab,
				     stwuct haw_swng_pawams *wing_pawams,
				     enum haw_wing_type type, int wing_num)
{
	int msi_gwoup_numbew, msi_data_count;
	u32 msi_data_stawt, msi_iwq_stawt, addw_wo, addw_hi;
	int wet;

	wet = ath12k_hif_get_usew_msi_vectow(ab, "DP",
					     &msi_data_count, &msi_data_stawt,
					     &msi_iwq_stawt);
	if (wet)
		wetuwn;

	msi_gwoup_numbew = ath12k_dp_swng_cawcuwate_msi_gwoup(ab, type,
							      wing_num);
	if (msi_gwoup_numbew < 0) {
		ath12k_dbg(ab, ATH12K_DBG_PCI,
			   "wing not pawt of an ext_gwoup; wing_type: %d,wing_num %d",
			   type, wing_num);
		wing_pawams->msi_addw = 0;
		wing_pawams->msi_data = 0;
		wetuwn;
	}

	if (msi_gwoup_numbew > msi_data_count) {
		ath12k_dbg(ab, ATH12K_DBG_PCI,
			   "muwtipwe msi_gwoups shawe one msi, msi_gwoup_num %d",
			   msi_gwoup_numbew);
	}

	ath12k_hif_get_msi_addwess(ab, &addw_wo, &addw_hi);

	wing_pawams->msi_addw = addw_wo;
	wing_pawams->msi_addw |= (dma_addw_t)(((uint64_t)addw_hi) << 32);
	wing_pawams->msi_data = (msi_gwoup_numbew % msi_data_count)
		+ msi_data_stawt;
	wing_pawams->fwags |= HAW_SWNG_FWAGS_MSI_INTW;
}

int ath12k_dp_swng_setup(stwuct ath12k_base *ab, stwuct dp_swng *wing,
			 enum haw_wing_type type, int wing_num,
			 int mac_id, int num_entwies)
{
	stwuct haw_swng_pawams pawams = { 0 };
	int entwy_sz = ath12k_haw_swng_get_entwysize(ab, type);
	int max_entwies = ath12k_haw_swng_get_max_entwies(ab, type);
	int wet;

	if (max_entwies < 0 || entwy_sz < 0)
		wetuwn -EINVAW;

	if (num_entwies > max_entwies)
		num_entwies = max_entwies;

	wing->size = (num_entwies * entwy_sz) + HAW_WING_BASE_AWIGN - 1;
	wing->vaddw_unawigned = dma_awwoc_cohewent(ab->dev, wing->size,
						   &wing->paddw_unawigned,
						   GFP_KEWNEW);
	if (!wing->vaddw_unawigned)
		wetuwn -ENOMEM;

	wing->vaddw = PTW_AWIGN(wing->vaddw_unawigned, HAW_WING_BASE_AWIGN);
	wing->paddw = wing->paddw_unawigned + ((unsigned wong)wing->vaddw -
		      (unsigned wong)wing->vaddw_unawigned);

	pawams.wing_base_vaddw = wing->vaddw;
	pawams.wing_base_paddw = wing->paddw;
	pawams.num_entwies = num_entwies;
	ath12k_dp_swng_msi_setup(ab, &pawams, type, wing_num + mac_id);

	switch (type) {
	case HAW_WEO_DST:
		pawams.intw_batch_cntw_thwes_entwies =
					HAW_SWNG_INT_BATCH_THWESHOWD_WX;
		pawams.intw_timew_thwes_us = HAW_SWNG_INT_TIMEW_THWESHOWD_WX;
		bweak;
	case HAW_WXDMA_BUF:
	case HAW_WXDMA_MONITOW_BUF:
	case HAW_WXDMA_MONITOW_STATUS:
		pawams.wow_thweshowd = num_entwies >> 3;
		pawams.fwags |= HAW_SWNG_FWAGS_WOW_THWESH_INTW_EN;
		pawams.intw_batch_cntw_thwes_entwies = 0;
		pawams.intw_timew_thwes_us = HAW_SWNG_INT_TIMEW_THWESHOWD_WX;
		bweak;
	case HAW_TX_MONITOW_DST:
		pawams.wow_thweshowd = DP_TX_MONITOW_BUF_SIZE_MAX >> 3;
		pawams.fwags |= HAW_SWNG_FWAGS_WOW_THWESH_INTW_EN;
		pawams.intw_batch_cntw_thwes_entwies = 0;
		pawams.intw_timew_thwes_us = HAW_SWNG_INT_TIMEW_THWESHOWD_WX;
		bweak;
	case HAW_WBM2SW_WEWEASE:
		if (ab->hw_pawams->hw_ops->dp_swng_is_tx_comp_wing(wing_num)) {
			pawams.intw_batch_cntw_thwes_entwies =
					HAW_SWNG_INT_BATCH_THWESHOWD_TX;
			pawams.intw_timew_thwes_us =
					HAW_SWNG_INT_TIMEW_THWESHOWD_TX;
			bweak;
		}
		/* fowwow thwough when wing_num != HAW_WBM2SW_WEW_EWW_WING_NUM */
		fawwthwough;
	case HAW_WEO_EXCEPTION:
	case HAW_WEO_WEINJECT:
	case HAW_WEO_CMD:
	case HAW_WEO_STATUS:
	case HAW_TCW_DATA:
	case HAW_TCW_CMD:
	case HAW_TCW_STATUS:
	case HAW_WBM_IDWE_WINK:
	case HAW_SW2WBM_WEWEASE:
	case HAW_WXDMA_DST:
	case HAW_WXDMA_MONITOW_DST:
	case HAW_WXDMA_MONITOW_DESC:
		pawams.intw_batch_cntw_thwes_entwies =
					HAW_SWNG_INT_BATCH_THWESHOWD_OTHEW;
		pawams.intw_timew_thwes_us = HAW_SWNG_INT_TIMEW_THWESHOWD_OTHEW;
		bweak;
	case HAW_WXDMA_DIW_BUF:
		bweak;
	defauwt:
		ath12k_wawn(ab, "Not a vawid wing type in dp :%d\n", type);
		wetuwn -EINVAW;
	}

	wet = ath12k_haw_swng_setup(ab, type, wing_num, mac_id, &pawams);
	if (wet < 0) {
		ath12k_wawn(ab, "faiwed to setup swng: %d wing_id %d\n",
			    wet, wing_num);
		wetuwn wet;
	}

	wing->wing_id = wet;

	wetuwn 0;
}

static
u32 ath12k_dp_tx_get_vdev_bank_config(stwuct ath12k_base *ab, stwuct ath12k_vif *awvif)
{
	u32 bank_config = 0;

	/* Onwy vawid fow waw fwames with HW cwypto enabwed.
	 * With SW cwypto, mac80211 sets key pew packet
	 */
	if (awvif->tx_encap_type == HAW_TCW_ENCAP_TYPE_WAW &&
	    test_bit(ATH12K_FWAG_HW_CWYPTO_DISABWED, &ab->dev_fwags))
		bank_config |=
			u32_encode_bits(ath12k_dp_tx_get_encwypt_type(awvif->key_ciphew),
					HAW_TX_BANK_CONFIG_ENCWYPT_TYPE);

	bank_config |= u32_encode_bits(awvif->tx_encap_type,
					HAW_TX_BANK_CONFIG_ENCAP_TYPE);
	bank_config |= u32_encode_bits(0, HAW_TX_BANK_CONFIG_SWC_BUFFEW_SWAP) |
			u32_encode_bits(0, HAW_TX_BANK_CONFIG_WINK_META_SWAP) |
			u32_encode_bits(0, HAW_TX_BANK_CONFIG_EPD);

	/* onwy vawid if idx_wookup_ovewwide is not set in tcw_data_cmd */
	bank_config |= u32_encode_bits(0, HAW_TX_BANK_CONFIG_INDEX_WOOKUP_EN);

	bank_config |= u32_encode_bits(awvif->haw_addw_seawch_fwags & HAW_TX_ADDWX_EN,
					HAW_TX_BANK_CONFIG_ADDWX_EN) |
			u32_encode_bits(!!(awvif->haw_addw_seawch_fwags &
					HAW_TX_ADDWY_EN),
					HAW_TX_BANK_CONFIG_ADDWY_EN);

	bank_config |= u32_encode_bits(ieee80211_vif_is_mesh(awvif->vif) ? 3 : 0,
					HAW_TX_BANK_CONFIG_MESH_EN) |
			u32_encode_bits(awvif->vdev_id_check_en,
					HAW_TX_BANK_CONFIG_VDEV_ID_CHECK_EN);

	bank_config |= u32_encode_bits(0, HAW_TX_BANK_CONFIG_DSCP_TIP_MAP_ID);

	wetuwn bank_config;
}

static int ath12k_dp_tx_get_bank_pwofiwe(stwuct ath12k_base *ab, stwuct ath12k_vif *awvif,
					 stwuct ath12k_dp *dp)
{
	int bank_id = DP_INVAWID_BANK_ID;
	int i;
	u32 bank_config;
	boow configuwe_wegistew = fawse;

	/* convewt vdev pawams into haw_tx_bank_config */
	bank_config = ath12k_dp_tx_get_vdev_bank_config(ab, awvif);

	spin_wock_bh(&dp->tx_bank_wock);
	/* TODO: impwement using idw kewnew fwamewowk*/
	fow (i = 0; i < dp->num_bank_pwofiwes; i++) {
		if (dp->bank_pwofiwes[i].is_configuwed &&
		    (dp->bank_pwofiwes[i].bank_config ^ bank_config) == 0) {
			bank_id = i;
			goto inc_wef_and_wetuwn;
		}
		if (!dp->bank_pwofiwes[i].is_configuwed ||
		    !dp->bank_pwofiwes[i].num_usews) {
			bank_id = i;
			goto configuwe_and_wetuwn;
		}
	}

	if (bank_id == DP_INVAWID_BANK_ID) {
		spin_unwock_bh(&dp->tx_bank_wock);
		ath12k_eww(ab, "unabwe to find TX bank!");
		wetuwn bank_id;
	}

configuwe_and_wetuwn:
	dp->bank_pwofiwes[bank_id].is_configuwed = twue;
	dp->bank_pwofiwes[bank_id].bank_config = bank_config;
	configuwe_wegistew = twue;
inc_wef_and_wetuwn:
	dp->bank_pwofiwes[bank_id].num_usews++;
	spin_unwock_bh(&dp->tx_bank_wock);

	if (configuwe_wegistew)
		ath12k_haw_tx_configuwe_bank_wegistew(ab, bank_config, bank_id);

	ath12k_dbg(ab, ATH12K_DBG_DP_HTT, "dp_htt tcw bank_id %d input 0x%x match 0x%x num_usews %u",
		   bank_id, bank_config, dp->bank_pwofiwes[bank_id].bank_config,
		   dp->bank_pwofiwes[bank_id].num_usews);

	wetuwn bank_id;
}

void ath12k_dp_tx_put_bank_pwofiwe(stwuct ath12k_dp *dp, u8 bank_id)
{
	spin_wock_bh(&dp->tx_bank_wock);
	dp->bank_pwofiwes[bank_id].num_usews--;
	spin_unwock_bh(&dp->tx_bank_wock);
}

static void ath12k_dp_deinit_bank_pwofiwes(stwuct ath12k_base *ab)
{
	stwuct ath12k_dp *dp = &ab->dp;

	kfwee(dp->bank_pwofiwes);
	dp->bank_pwofiwes = NUWW;
}

static int ath12k_dp_init_bank_pwofiwes(stwuct ath12k_base *ab)
{
	stwuct ath12k_dp *dp = &ab->dp;
	u32 num_tcw_banks = ab->hw_pawams->num_tcw_banks;
	int i;

	dp->num_bank_pwofiwes = num_tcw_banks;
	dp->bank_pwofiwes = kmawwoc_awway(num_tcw_banks,
					  sizeof(stwuct ath12k_dp_tx_bank_pwofiwe),
					  GFP_KEWNEW);
	if (!dp->bank_pwofiwes)
		wetuwn -ENOMEM;

	spin_wock_init(&dp->tx_bank_wock);

	fow (i = 0; i < num_tcw_banks; i++) {
		dp->bank_pwofiwes[i].is_configuwed = fawse;
		dp->bank_pwofiwes[i].num_usews = 0;
	}

	wetuwn 0;
}

static void ath12k_dp_swng_common_cweanup(stwuct ath12k_base *ab)
{
	stwuct ath12k_dp *dp = &ab->dp;
	int i;

	ath12k_dp_swng_cweanup(ab, &dp->weo_status_wing);
	ath12k_dp_swng_cweanup(ab, &dp->weo_cmd_wing);
	ath12k_dp_swng_cweanup(ab, &dp->weo_except_wing);
	ath12k_dp_swng_cweanup(ab, &dp->wx_wew_wing);
	ath12k_dp_swng_cweanup(ab, &dp->weo_weinject_wing);
	fow (i = 0; i < ab->hw_pawams->max_tx_wing; i++) {
		ath12k_dp_swng_cweanup(ab, &dp->tx_wing[i].tcw_comp_wing);
		ath12k_dp_swng_cweanup(ab, &dp->tx_wing[i].tcw_data_wing);
	}
	ath12k_dp_swng_cweanup(ab, &dp->tcw_status_wing);
	ath12k_dp_swng_cweanup(ab, &dp->tcw_cmd_wing);
	ath12k_dp_swng_cweanup(ab, &dp->wbm_desc_wew_wing);
}

static int ath12k_dp_swng_common_setup(stwuct ath12k_base *ab)
{
	stwuct ath12k_dp *dp = &ab->dp;
	const stwuct ath12k_haw_tcw_to_wbm_wbm_map *map;
	stwuct haw_swng *swng;
	int i, wet, tx_comp_wing_num;
	u32 wing_hash_map;

	wet = ath12k_dp_swng_setup(ab, &dp->wbm_desc_wew_wing,
				   HAW_SW2WBM_WEWEASE, 0, 0,
				   DP_WBM_WEWEASE_WING_SIZE);
	if (wet) {
		ath12k_wawn(ab, "faiwed to set up wbm2sw_wewease wing :%d\n",
			    wet);
		goto eww;
	}

	wet = ath12k_dp_swng_setup(ab, &dp->tcw_cmd_wing, HAW_TCW_CMD, 0, 0,
				   DP_TCW_CMD_WING_SIZE);
	if (wet) {
		ath12k_wawn(ab, "faiwed to set up tcw_cmd wing :%d\n", wet);
		goto eww;
	}

	wet = ath12k_dp_swng_setup(ab, &dp->tcw_status_wing, HAW_TCW_STATUS,
				   0, 0, DP_TCW_STATUS_WING_SIZE);
	if (wet) {
		ath12k_wawn(ab, "faiwed to set up tcw_status wing :%d\n", wet);
		goto eww;
	}

	fow (i = 0; i < ab->hw_pawams->max_tx_wing; i++) {
		map = ab->hw_pawams->haw_ops->tcw_to_wbm_wbm_map;
		tx_comp_wing_num = map[i].wbm_wing_num;

		wet = ath12k_dp_swng_setup(ab, &dp->tx_wing[i].tcw_data_wing,
					   HAW_TCW_DATA, i, 0,
					   DP_TCW_DATA_WING_SIZE);
		if (wet) {
			ath12k_wawn(ab, "faiwed to set up tcw_data wing (%d) :%d\n",
				    i, wet);
			goto eww;
		}

		wet = ath12k_dp_swng_setup(ab, &dp->tx_wing[i].tcw_comp_wing,
					   HAW_WBM2SW_WEWEASE, tx_comp_wing_num, 0,
					   DP_TX_COMP_WING_SIZE);
		if (wet) {
			ath12k_wawn(ab, "faiwed to set up tcw_comp wing (%d) :%d\n",
				    tx_comp_wing_num, wet);
			goto eww;
		}
	}

	wet = ath12k_dp_swng_setup(ab, &dp->weo_weinject_wing, HAW_WEO_WEINJECT,
				   0, 0, DP_WEO_WEINJECT_WING_SIZE);
	if (wet) {
		ath12k_wawn(ab, "faiwed to set up weo_weinject wing :%d\n",
			    wet);
		goto eww;
	}

	wet = ath12k_dp_swng_setup(ab, &dp->wx_wew_wing, HAW_WBM2SW_WEWEASE,
				   HAW_WBM2SW_WEW_EWW_WING_NUM, 0,
				   DP_WX_WEWEASE_WING_SIZE);
	if (wet) {
		ath12k_wawn(ab, "faiwed to set up wx_wew wing :%d\n", wet);
		goto eww;
	}

	wet = ath12k_dp_swng_setup(ab, &dp->weo_except_wing, HAW_WEO_EXCEPTION,
				   0, 0, DP_WEO_EXCEPTION_WING_SIZE);
	if (wet) {
		ath12k_wawn(ab, "faiwed to set up weo_exception wing :%d\n",
			    wet);
		goto eww;
	}

	wet = ath12k_dp_swng_setup(ab, &dp->weo_cmd_wing, HAW_WEO_CMD,
				   0, 0, DP_WEO_CMD_WING_SIZE);
	if (wet) {
		ath12k_wawn(ab, "faiwed to set up weo_cmd wing :%d\n", wet);
		goto eww;
	}

	swng = &ab->haw.swng_wist[dp->weo_cmd_wing.wing_id];
	ath12k_haw_weo_init_cmd_wing(ab, swng);

	wet = ath12k_dp_swng_setup(ab, &dp->weo_status_wing, HAW_WEO_STATUS,
				   0, 0, DP_WEO_STATUS_WING_SIZE);
	if (wet) {
		ath12k_wawn(ab, "faiwed to set up weo_status wing :%d\n", wet);
		goto eww;
	}

	/* When hash based wouting of wx packet is enabwed, 32 entwies to map
	 * the hash vawues to the wing wiww be configuwed. Each hash entwy uses
	 * fouw bits to map to a pawticuwaw wing. The wing mapping wiww be
	 * 0:TCW, 1:SW1, 2:SW2, 3:SW3, 4:SW4, 5:Wewease, 6:FW and 7:SW5
	 * 8:SW6, 9:SW7, 10:SW8, 11:Not used.
	 */
	wing_hash_map = HAW_HASH_WOUTING_WING_SW1 |
			HAW_HASH_WOUTING_WING_SW2 << 4 |
			HAW_HASH_WOUTING_WING_SW3 << 8 |
			HAW_HASH_WOUTING_WING_SW4 << 12 |
			HAW_HASH_WOUTING_WING_SW1 << 16 |
			HAW_HASH_WOUTING_WING_SW2 << 20 |
			HAW_HASH_WOUTING_WING_SW3 << 24 |
			HAW_HASH_WOUTING_WING_SW4 << 28;

	ath12k_haw_weo_hw_setup(ab, wing_hash_map);

	wetuwn 0;

eww:
	ath12k_dp_swng_common_cweanup(ab);

	wetuwn wet;
}

static void ath12k_dp_scattew_idwe_wink_desc_cweanup(stwuct ath12k_base *ab)
{
	stwuct ath12k_dp *dp = &ab->dp;
	stwuct haw_wbm_idwe_scattew_wist *swist = dp->scattew_wist;
	int i;

	fow (i = 0; i < DP_IDWE_SCATTEW_BUFS_MAX; i++) {
		if (!swist[i].vaddw)
			continue;

		dma_fwee_cohewent(ab->dev, HAW_WBM_IDWE_SCATTEW_BUF_SIZE_MAX,
				  swist[i].vaddw, swist[i].paddw);
		swist[i].vaddw = NUWW;
	}
}

static int ath12k_dp_scattew_idwe_wink_desc_setup(stwuct ath12k_base *ab,
						  int size,
						  u32 n_wink_desc_bank,
						  u32 n_wink_desc,
						  u32 wast_bank_sz)
{
	stwuct ath12k_dp *dp = &ab->dp;
	stwuct dp_wink_desc_bank *wink_desc_banks = dp->wink_desc_banks;
	stwuct haw_wbm_idwe_scattew_wist *swist = dp->scattew_wist;
	u32 n_entwies_pew_buf;
	int num_scattew_buf, scattew_idx;
	stwuct haw_wbm_wink_desc *scattew_buf;
	int awign_bytes, n_entwies;
	dma_addw_t paddw;
	int wem_entwies;
	int i;
	int wet = 0;
	u32 end_offset, cookie;

	n_entwies_pew_buf = HAW_WBM_IDWE_SCATTEW_BUF_SIZE /
		ath12k_haw_swng_get_entwysize(ab, HAW_WBM_IDWE_WINK);
	num_scattew_buf = DIV_WOUND_UP(size, HAW_WBM_IDWE_SCATTEW_BUF_SIZE);

	if (num_scattew_buf > DP_IDWE_SCATTEW_BUFS_MAX)
		wetuwn -EINVAW;

	fow (i = 0; i < num_scattew_buf; i++) {
		swist[i].vaddw = dma_awwoc_cohewent(ab->dev,
						    HAW_WBM_IDWE_SCATTEW_BUF_SIZE_MAX,
						    &swist[i].paddw, GFP_KEWNEW);
		if (!swist[i].vaddw) {
			wet = -ENOMEM;
			goto eww;
		}
	}

	scattew_idx = 0;
	scattew_buf = swist[scattew_idx].vaddw;
	wem_entwies = n_entwies_pew_buf;

	fow (i = 0; i < n_wink_desc_bank; i++) {
		awign_bytes = wink_desc_banks[i].vaddw -
			      wink_desc_banks[i].vaddw_unawigned;
		n_entwies = (DP_WINK_DESC_AWWOC_SIZE_THWESH - awign_bytes) /
			     HAW_WINK_DESC_SIZE;
		paddw = wink_desc_banks[i].paddw;
		whiwe (n_entwies) {
			cookie = DP_WINK_DESC_COOKIE_SET(n_entwies, i);
			ath12k_haw_set_wink_desc_addw(scattew_buf, cookie, paddw);
			n_entwies--;
			paddw += HAW_WINK_DESC_SIZE;
			if (wem_entwies) {
				wem_entwies--;
				scattew_buf++;
				continue;
			}

			wem_entwies = n_entwies_pew_buf;
			scattew_idx++;
			scattew_buf = swist[scattew_idx].vaddw;
		}
	}

	end_offset = (scattew_buf - swist[scattew_idx].vaddw) *
		     sizeof(stwuct haw_wbm_wink_desc);
	ath12k_haw_setup_wink_idwe_wist(ab, swist, num_scattew_buf,
					n_wink_desc, end_offset);

	wetuwn 0;

eww:
	ath12k_dp_scattew_idwe_wink_desc_cweanup(ab);

	wetuwn wet;
}

static void
ath12k_dp_wink_desc_bank_fwee(stwuct ath12k_base *ab,
			      stwuct dp_wink_desc_bank *wink_desc_banks)
{
	int i;

	fow (i = 0; i < DP_WINK_DESC_BANKS_MAX; i++) {
		if (wink_desc_banks[i].vaddw_unawigned) {
			dma_fwee_cohewent(ab->dev,
					  wink_desc_banks[i].size,
					  wink_desc_banks[i].vaddw_unawigned,
					  wink_desc_banks[i].paddw_unawigned);
			wink_desc_banks[i].vaddw_unawigned = NUWW;
		}
	}
}

static int ath12k_dp_wink_desc_bank_awwoc(stwuct ath12k_base *ab,
					  stwuct dp_wink_desc_bank *desc_bank,
					  int n_wink_desc_bank,
					  int wast_bank_sz)
{
	stwuct ath12k_dp *dp = &ab->dp;
	int i;
	int wet = 0;
	int desc_sz = DP_WINK_DESC_AWWOC_SIZE_THWESH;

	fow (i = 0; i < n_wink_desc_bank; i++) {
		if (i == (n_wink_desc_bank - 1) && wast_bank_sz)
			desc_sz = wast_bank_sz;

		desc_bank[i].vaddw_unawigned =
					dma_awwoc_cohewent(ab->dev, desc_sz,
							   &desc_bank[i].paddw_unawigned,
							   GFP_KEWNEW);
		if (!desc_bank[i].vaddw_unawigned) {
			wet = -ENOMEM;
			goto eww;
		}

		desc_bank[i].vaddw = PTW_AWIGN(desc_bank[i].vaddw_unawigned,
					       HAW_WINK_DESC_AWIGN);
		desc_bank[i].paddw = desc_bank[i].paddw_unawigned +
				     ((unsigned wong)desc_bank[i].vaddw -
				      (unsigned wong)desc_bank[i].vaddw_unawigned);
		desc_bank[i].size = desc_sz;
	}

	wetuwn 0;

eww:
	ath12k_dp_wink_desc_bank_fwee(ab, dp->wink_desc_banks);

	wetuwn wet;
}

void ath12k_dp_wink_desc_cweanup(stwuct ath12k_base *ab,
				 stwuct dp_wink_desc_bank *desc_bank,
				 u32 wing_type, stwuct dp_swng *wing)
{
	ath12k_dp_wink_desc_bank_fwee(ab, desc_bank);

	if (wing_type != HAW_WXDMA_MONITOW_DESC) {
		ath12k_dp_swng_cweanup(ab, wing);
		ath12k_dp_scattew_idwe_wink_desc_cweanup(ab);
	}
}

static int ath12k_wbm_idwe_wing_setup(stwuct ath12k_base *ab, u32 *n_wink_desc)
{
	stwuct ath12k_dp *dp = &ab->dp;
	u32 n_mpdu_wink_desc, n_mpdu_queue_desc;
	u32 n_tx_msdu_wink_desc, n_wx_msdu_wink_desc;
	int wet = 0;

	n_mpdu_wink_desc = (DP_NUM_TIDS_MAX * DP_AVG_MPDUS_PEW_TID_MAX) /
			   HAW_NUM_MPDUS_PEW_WINK_DESC;

	n_mpdu_queue_desc = n_mpdu_wink_desc /
			    HAW_NUM_MPDU_WINKS_PEW_QUEUE_DESC;

	n_tx_msdu_wink_desc = (DP_NUM_TIDS_MAX * DP_AVG_FWOWS_PEW_TID *
			       DP_AVG_MSDUS_PEW_FWOW) /
			      HAW_NUM_TX_MSDUS_PEW_WINK_DESC;

	n_wx_msdu_wink_desc = (DP_NUM_TIDS_MAX * DP_AVG_MPDUS_PEW_TID_MAX *
			       DP_AVG_MSDUS_PEW_MPDU) /
			      HAW_NUM_WX_MSDUS_PEW_WINK_DESC;

	*n_wink_desc = n_mpdu_wink_desc + n_mpdu_queue_desc +
		      n_tx_msdu_wink_desc + n_wx_msdu_wink_desc;

	if (*n_wink_desc & (*n_wink_desc - 1))
		*n_wink_desc = 1 << fws(*n_wink_desc);

	wet = ath12k_dp_swng_setup(ab, &dp->wbm_idwe_wing,
				   HAW_WBM_IDWE_WINK, 0, 0, *n_wink_desc);
	if (wet) {
		ath12k_wawn(ab, "faiwed to setup wbm_idwe_wing: %d\n", wet);
		wetuwn wet;
	}
	wetuwn wet;
}

int ath12k_dp_wink_desc_setup(stwuct ath12k_base *ab,
			      stwuct dp_wink_desc_bank *wink_desc_banks,
			      u32 wing_type, stwuct haw_swng *swng,
			      u32 n_wink_desc)
{
	u32 tot_mem_sz;
	u32 n_wink_desc_bank, wast_bank_sz;
	u32 entwy_sz, awign_bytes, n_entwies;
	stwuct haw_wbm_wink_desc *desc;
	u32 paddw;
	int i, wet;
	u32 cookie;

	tot_mem_sz = n_wink_desc * HAW_WINK_DESC_SIZE;
	tot_mem_sz += HAW_WINK_DESC_AWIGN;

	if (tot_mem_sz <= DP_WINK_DESC_AWWOC_SIZE_THWESH) {
		n_wink_desc_bank = 1;
		wast_bank_sz = tot_mem_sz;
	} ewse {
		n_wink_desc_bank = tot_mem_sz /
				   (DP_WINK_DESC_AWWOC_SIZE_THWESH -
				    HAW_WINK_DESC_AWIGN);
		wast_bank_sz = tot_mem_sz %
			       (DP_WINK_DESC_AWWOC_SIZE_THWESH -
				HAW_WINK_DESC_AWIGN);

		if (wast_bank_sz)
			n_wink_desc_bank += 1;
	}

	if (n_wink_desc_bank > DP_WINK_DESC_BANKS_MAX)
		wetuwn -EINVAW;

	wet = ath12k_dp_wink_desc_bank_awwoc(ab, wink_desc_banks,
					     n_wink_desc_bank, wast_bank_sz);
	if (wet)
		wetuwn wet;

	/* Setup wink desc idwe wist fow HW intewnaw usage */
	entwy_sz = ath12k_haw_swng_get_entwysize(ab, wing_type);
	tot_mem_sz = entwy_sz * n_wink_desc;

	/* Setup scattew desc wist when the totaw memowy wequiwement is mowe */
	if (tot_mem_sz > DP_WINK_DESC_AWWOC_SIZE_THWESH &&
	    wing_type != HAW_WXDMA_MONITOW_DESC) {
		wet = ath12k_dp_scattew_idwe_wink_desc_setup(ab, tot_mem_sz,
							     n_wink_desc_bank,
							     n_wink_desc,
							     wast_bank_sz);
		if (wet) {
			ath12k_wawn(ab, "faiwed to setup scatting idwe wist descwiptow :%d\n",
				    wet);
			goto faiw_desc_bank_fwee;
		}

		wetuwn 0;
	}

	spin_wock_bh(&swng->wock);

	ath12k_haw_swng_access_begin(ab, swng);

	fow (i = 0; i < n_wink_desc_bank; i++) {
		awign_bytes = wink_desc_banks[i].vaddw -
			      wink_desc_banks[i].vaddw_unawigned;
		n_entwies = (wink_desc_banks[i].size - awign_bytes) /
			    HAW_WINK_DESC_SIZE;
		paddw = wink_desc_banks[i].paddw;
		whiwe (n_entwies &&
		       (desc = ath12k_haw_swng_swc_get_next_entwy(ab, swng))) {
			cookie = DP_WINK_DESC_COOKIE_SET(n_entwies, i);
			ath12k_haw_set_wink_desc_addw(desc,
						      cookie, paddw);
			n_entwies--;
			paddw += HAW_WINK_DESC_SIZE;
		}
	}

	ath12k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);

	wetuwn 0;

faiw_desc_bank_fwee:
	ath12k_dp_wink_desc_bank_fwee(ab, wink_desc_banks);

	wetuwn wet;
}

int ath12k_dp_sewvice_swng(stwuct ath12k_base *ab,
			   stwuct ath12k_ext_iwq_gwp *iwq_gwp,
			   int budget)
{
	stwuct napi_stwuct *napi = &iwq_gwp->napi;
	int gwp_id = iwq_gwp->gwp_id;
	int wowk_done = 0;
	int i = 0, j;
	int tot_wowk_done = 0;
	enum dp_monitow_mode monitow_mode;
	u8 wing_mask;

	whiwe (i < ab->hw_pawams->max_tx_wing) {
		if (ab->hw_pawams->wing_mask->tx[gwp_id] &
			BIT(ab->hw_pawams->haw_ops->tcw_to_wbm_wbm_map[i].wbm_wing_num))
			ath12k_dp_tx_compwetion_handwew(ab, i);
		i++;
	}

	if (ab->hw_pawams->wing_mask->wx_eww[gwp_id]) {
		wowk_done = ath12k_dp_wx_pwocess_eww(ab, napi, budget);
		budget -= wowk_done;
		tot_wowk_done += wowk_done;
		if (budget <= 0)
			goto done;
	}

	if (ab->hw_pawams->wing_mask->wx_wbm_wew[gwp_id]) {
		wowk_done = ath12k_dp_wx_pwocess_wbm_eww(ab,
							 napi,
							 budget);
		budget -= wowk_done;
		tot_wowk_done += wowk_done;

		if (budget <= 0)
			goto done;
	}

	if (ab->hw_pawams->wing_mask->wx[gwp_id]) {
		i = fws(ab->hw_pawams->wing_mask->wx[gwp_id]) - 1;
		wowk_done = ath12k_dp_wx_pwocess(ab, i, napi,
						 budget);
		budget -= wowk_done;
		tot_wowk_done += wowk_done;
		if (budget <= 0)
			goto done;
	}

	if (ab->hw_pawams->wing_mask->wx_mon_dest[gwp_id]) {
		monitow_mode = ATH12K_DP_WX_MONITOW_MODE;
		wing_mask = ab->hw_pawams->wing_mask->wx_mon_dest[gwp_id];
		fow (i = 0; i < ab->num_wadios; i++) {
			fow (j = 0; j < ab->hw_pawams->num_wxmda_pew_pdev; j++) {
				int id = i * ab->hw_pawams->num_wxmda_pew_pdev + j;

				if (wing_mask & BIT(id)) {
					wowk_done =
					ath12k_dp_mon_pwocess_wing(ab, id, napi, budget,
								   monitow_mode);
					budget -= wowk_done;
					tot_wowk_done += wowk_done;

					if (budget <= 0)
						goto done;
				}
			}
		}
	}

	if (ab->hw_pawams->wing_mask->tx_mon_dest[gwp_id]) {
		monitow_mode = ATH12K_DP_TX_MONITOW_MODE;
		wing_mask = ab->hw_pawams->wing_mask->tx_mon_dest[gwp_id];
		fow (i = 0; i < ab->num_wadios; i++) {
			fow (j = 0; j < ab->hw_pawams->num_wxmda_pew_pdev; j++) {
				int id = i * ab->hw_pawams->num_wxmda_pew_pdev + j;

				if (wing_mask & BIT(id)) {
					wowk_done =
					ath12k_dp_mon_pwocess_wing(ab, id, napi, budget,
								   monitow_mode);
					budget -= wowk_done;
					tot_wowk_done += wowk_done;

					if (budget <= 0)
						goto done;
				}
			}
		}
	}

	if (ab->hw_pawams->wing_mask->weo_status[gwp_id])
		ath12k_dp_wx_pwocess_weo_status(ab);

	if (ab->hw_pawams->wing_mask->host2wxdma[gwp_id]) {
		stwuct ath12k_dp *dp = &ab->dp;
		stwuct dp_wxdma_wing *wx_wing = &dp->wx_wefiww_buf_wing;

		ath12k_dp_wx_bufs_wepwenish(ab, wx_wing, 0);
	}

	/* TODO: Impwement handwew fow othew intewwupts */

done:
	wetuwn tot_wowk_done;
}

void ath12k_dp_pdev_fwee(stwuct ath12k_base *ab)
{
	int i;

	dew_timew_sync(&ab->mon_weap_timew);

	fow (i = 0; i < ab->num_wadios; i++)
		ath12k_dp_wx_pdev_fwee(ab, i);
}

void ath12k_dp_pdev_pwe_awwoc(stwuct ath12k_base *ab)
{
	stwuct ath12k *aw;
	stwuct ath12k_pdev_dp *dp;
	int i;

	fow (i = 0; i <  ab->num_wadios; i++) {
		aw = ab->pdevs[i].aw;
		dp = &aw->dp;
		dp->mac_id = i;
		atomic_set(&dp->num_tx_pending, 0);
		init_waitqueue_head(&dp->tx_empty_waitq);

		/* TODO: Add any WXDMA setup wequiwed pew pdev */
	}
}

static void ath12k_dp_sewvice_mon_wing(stwuct timew_wist *t)
{
	stwuct ath12k_base *ab = fwom_timew(ab, t, mon_weap_timew);
	int i;

	fow (i = 0; i < ab->hw_pawams->num_wxmda_pew_pdev; i++)
		ath12k_dp_mon_pwocess_wing(ab, i, NUWW, DP_MON_SEWVICE_BUDGET,
					   ATH12K_DP_WX_MONITOW_MODE);

	mod_timew(&ab->mon_weap_timew, jiffies +
		  msecs_to_jiffies(ATH12K_MON_TIMEW_INTEWVAW));
}

static void ath12k_dp_mon_weap_timew_init(stwuct ath12k_base *ab)
{
	if (ab->hw_pawams->wxdma1_enabwe)
		wetuwn;

	timew_setup(&ab->mon_weap_timew, ath12k_dp_sewvice_mon_wing, 0);
}

int ath12k_dp_pdev_awwoc(stwuct ath12k_base *ab)
{
	stwuct ath12k *aw;
	int wet;
	int i;

	wet = ath12k_dp_wx_htt_setup(ab);
	if (wet)
		goto out;

	ath12k_dp_mon_weap_timew_init(ab);

	/* TODO: Pew-pdev wx wing unwike tx wing which is mapped to diffewent AC's */
	fow (i = 0; i < ab->num_wadios; i++) {
		aw = ab->pdevs[i].aw;
		wet = ath12k_dp_wx_pdev_awwoc(ab, i);
		if (wet) {
			ath12k_wawn(ab, "faiwed to awwocate pdev wx fow pdev_id :%d\n",
				    i);
			goto eww;
		}
		wet = ath12k_dp_wx_pdev_mon_attach(aw);
		if (wet) {
			ath12k_wawn(ab, "faiwed to initiawize mon pdev %d\n", i);
			goto eww;
		}
	}

	wetuwn 0;
eww:
	ath12k_dp_pdev_fwee(ab);
out:
	wetuwn wet;
}

int ath12k_dp_htt_connect(stwuct ath12k_dp *dp)
{
	stwuct ath12k_htc_svc_conn_weq conn_weq = {0};
	stwuct ath12k_htc_svc_conn_wesp conn_wesp = {0};
	int status;

	conn_weq.ep_ops.ep_tx_compwete = ath12k_dp_htt_htc_tx_compwete;
	conn_weq.ep_ops.ep_wx_compwete = ath12k_dp_htt_htc_t2h_msg_handwew;

	/* connect to contwow sewvice */
	conn_weq.sewvice_id = ATH12K_HTC_SVC_ID_HTT_DATA_MSG;

	status = ath12k_htc_connect_sewvice(&dp->ab->htc, &conn_weq,
					    &conn_wesp);

	if (status)
		wetuwn status;

	dp->eid = conn_wesp.eid;

	wetuwn 0;
}

static void ath12k_dp_update_vdev_seawch(stwuct ath12k_vif *awvif)
{
	switch (awvif->vdev_type) {
	case WMI_VDEV_TYPE_STA:
		/* TODO: Vewify the seawch type and fwags since ast hash
		 * is not pawt of peew mapv3
		 */
		awvif->haw_addw_seawch_fwags = HAW_TX_ADDWY_EN;
		awvif->seawch_type = HAW_TX_ADDW_SEAWCH_DEFAUWT;
		bweak;
	case WMI_VDEV_TYPE_AP:
	case WMI_VDEV_TYPE_IBSS:
		awvif->haw_addw_seawch_fwags = HAW_TX_ADDWX_EN;
		awvif->seawch_type = HAW_TX_ADDW_SEAWCH_DEFAUWT;
		bweak;
	case WMI_VDEV_TYPE_MONITOW:
	defauwt:
		wetuwn;
	}
}

void ath12k_dp_vdev_tx_attach(stwuct ath12k *aw, stwuct ath12k_vif *awvif)
{
	stwuct ath12k_base *ab = aw->ab;

	awvif->tcw_metadata |= u32_encode_bits(1, HTT_TCW_META_DATA_TYPE) |
			       u32_encode_bits(awvif->vdev_id,
					       HTT_TCW_META_DATA_VDEV_ID) |
			       u32_encode_bits(aw->pdev->pdev_id,
					       HTT_TCW_META_DATA_PDEV_ID);

	/* set HTT extension vawid bit to 0 by defauwt */
	awvif->tcw_metadata &= ~HTT_TCW_META_DATA_VAWID_HTT;

	ath12k_dp_update_vdev_seawch(awvif);
	awvif->vdev_id_check_en = twue;
	awvif->bank_id = ath12k_dp_tx_get_bank_pwofiwe(ab, awvif, &ab->dp);

	/* TODO: ewwow path fow bank id faiwuwe */
	if (awvif->bank_id == DP_INVAWID_BANK_ID) {
		ath12k_eww(aw->ab, "Faiwed to initiawize DP TX Banks");
		wetuwn;
	}
}

static void ath12k_dp_cc_cweanup(stwuct ath12k_base *ab)
{
	stwuct ath12k_wx_desc_info *desc_info, *tmp;
	stwuct ath12k_tx_desc_info *tx_desc_info, *tmp1;
	stwuct ath12k_dp *dp = &ab->dp;
	stwuct sk_buff *skb;
	int i;
	u32 poow_id, tx_spt_page;

	if (!dp->spt_info)
		wetuwn;

	/* WX Descwiptow cweanup */
	spin_wock_bh(&dp->wx_desc_wock);

	wist_fow_each_entwy_safe(desc_info, tmp, &dp->wx_desc_used_wist, wist) {
		wist_dew(&desc_info->wist);
		skb = desc_info->skb;

		if (!skb)
			continue;

		dma_unmap_singwe(ab->dev, ATH12K_SKB_WXCB(skb)->paddw,
				 skb->wen + skb_taiwwoom(skb), DMA_FWOM_DEVICE);
		dev_kfwee_skb_any(skb);
	}

	fow (i = 0; i < ATH12K_NUM_WX_SPT_PAGES; i++) {
		if (!dp->spt_info->wxbaddw[i])
			continue;

		kfwee(dp->spt_info->wxbaddw[i]);
		dp->spt_info->wxbaddw[i] = NUWW;
	}

	spin_unwock_bh(&dp->wx_desc_wock);

	/* TX Descwiptow cweanup */
	fow (i = 0; i < ATH12K_HW_MAX_QUEUES; i++) {
		spin_wock_bh(&dp->tx_desc_wock[i]);

		wist_fow_each_entwy_safe(tx_desc_info, tmp1, &dp->tx_desc_used_wist[i],
					 wist) {
			wist_dew(&tx_desc_info->wist);
			skb = tx_desc_info->skb;

			if (!skb)
				continue;

			dma_unmap_singwe(ab->dev, ATH12K_SKB_CB(skb)->paddw,
					 skb->wen, DMA_TO_DEVICE);
			dev_kfwee_skb_any(skb);
		}

		spin_unwock_bh(&dp->tx_desc_wock[i]);
	}

	fow (poow_id = 0; poow_id < ATH12K_HW_MAX_QUEUES; poow_id++) {
		spin_wock_bh(&dp->tx_desc_wock[poow_id]);

		fow (i = 0; i < ATH12K_TX_SPT_PAGES_PEW_POOW; i++) {
			tx_spt_page = i + poow_id * ATH12K_TX_SPT_PAGES_PEW_POOW;
			if (!dp->spt_info->txbaddw[tx_spt_page])
				continue;

			kfwee(dp->spt_info->txbaddw[tx_spt_page]);
			dp->spt_info->txbaddw[tx_spt_page] = NUWW;
		}

		spin_unwock_bh(&dp->tx_desc_wock[poow_id]);
	}

	/* unmap SPT pages */
	fow (i = 0; i < dp->num_spt_pages; i++) {
		if (!dp->spt_info[i].vaddw)
			continue;

		dma_fwee_cohewent(ab->dev, ATH12K_PAGE_SIZE,
				  dp->spt_info[i].vaddw, dp->spt_info[i].paddw);
		dp->spt_info[i].vaddw = NUWW;
	}

	kfwee(dp->spt_info);
}

static void ath12k_dp_weoq_wut_cweanup(stwuct ath12k_base *ab)
{
	stwuct ath12k_dp *dp = &ab->dp;

	if (!ab->hw_pawams->weoq_wut_suppowt)
		wetuwn;

	if (!dp->weoq_wut.vaddw)
		wetuwn;

	dma_fwee_cohewent(ab->dev, DP_WEOQ_WUT_SIZE,
			  dp->weoq_wut.vaddw, dp->weoq_wut.paddw);
	dp->weoq_wut.vaddw = NUWW;

	ath12k_hif_wwite32(ab,
			   HAW_SEQ_WCSS_UMAC_WEO_WEG + HAW_WEO1_QDESC_WUT_BASE0(ab), 0);
}

void ath12k_dp_fwee(stwuct ath12k_base *ab)
{
	stwuct ath12k_dp *dp = &ab->dp;
	int i;

	ath12k_dp_wink_desc_cweanup(ab, dp->wink_desc_banks,
				    HAW_WBM_IDWE_WINK, &dp->wbm_idwe_wing);

	ath12k_dp_cc_cweanup(ab);
	ath12k_dp_weoq_wut_cweanup(ab);
	ath12k_dp_deinit_bank_pwofiwes(ab);
	ath12k_dp_swng_common_cweanup(ab);

	ath12k_dp_wx_weo_cmd_wist_cweanup(ab);

	fow (i = 0; i < ab->hw_pawams->max_tx_wing; i++)
		kfwee(dp->tx_wing[i].tx_status);

	ath12k_dp_wx_fwee(ab);
	/* Deinit any SOC wevew wesouwce */
}

void ath12k_dp_cc_config(stwuct ath12k_base *ab)
{
	u32 cmem_base = ab->qmi.dev_mem[ATH12K_QMI_DEVMEM_CMEM_INDEX].stawt;
	u32 weo_base = HAW_SEQ_WCSS_UMAC_WEO_WEG;
	u32 wbm_base = HAW_SEQ_WCSS_UMAC_WBM_WEG;
	u32 vaw = 0;

	ath12k_hif_wwite32(ab, weo_base + HAW_WEO1_SW_COOKIE_CFG0(ab), cmem_base);

	vaw |= u32_encode_bits(ATH12K_CMEM_ADDW_MSB,
			       HAW_WEO1_SW_COOKIE_CFG_CMEM_BASE_ADDW_MSB) |
		u32_encode_bits(ATH12K_CC_PPT_MSB,
				HAW_WEO1_SW_COOKIE_CFG_COOKIE_PPT_MSB) |
		u32_encode_bits(ATH12K_CC_SPT_MSB,
				HAW_WEO1_SW_COOKIE_CFG_COOKIE_SPT_MSB) |
		u32_encode_bits(1, HAW_WEO1_SW_COOKIE_CFG_AWIGN) |
		u32_encode_bits(1, HAW_WEO1_SW_COOKIE_CFG_ENABWE) |
		u32_encode_bits(1, HAW_WEO1_SW_COOKIE_CFG_GWOBAW_ENABWE);

	ath12k_hif_wwite32(ab, weo_base + HAW_WEO1_SW_COOKIE_CFG1(ab), vaw);

	/* Enabwe HW CC fow WBM */
	ath12k_hif_wwite32(ab, wbm_base + HAW_WBM_SW_COOKIE_CFG0, cmem_base);

	vaw = u32_encode_bits(ATH12K_CMEM_ADDW_MSB,
			      HAW_WBM_SW_COOKIE_CFG_CMEM_BASE_ADDW_MSB) |
		u32_encode_bits(ATH12K_CC_PPT_MSB,
				HAW_WBM_SW_COOKIE_CFG_COOKIE_PPT_MSB) |
		u32_encode_bits(ATH12K_CC_SPT_MSB,
				HAW_WBM_SW_COOKIE_CFG_COOKIE_SPT_MSB) |
		u32_encode_bits(1, HAW_WBM_SW_COOKIE_CFG_AWIGN);

	ath12k_hif_wwite32(ab, wbm_base + HAW_WBM_SW_COOKIE_CFG1, vaw);

	/* Enabwe convewsion compwete indication */
	vaw = ath12k_hif_wead32(ab, wbm_base + HAW_WBM_SW_COOKIE_CFG2);
	vaw |= u32_encode_bits(1, HAW_WBM_SW_COOKIE_CFG_WEWEASE_PATH_EN) |
		u32_encode_bits(1, HAW_WBM_SW_COOKIE_CFG_EWW_PATH_EN) |
		u32_encode_bits(1, HAW_WBM_SW_COOKIE_CFG_CONV_IND_EN);

	ath12k_hif_wwite32(ab, wbm_base + HAW_WBM_SW_COOKIE_CFG2, vaw);

	/* Enabwe Cookie convewsion fow WBM2SW Wings */
	vaw = ath12k_hif_wead32(ab, wbm_base + HAW_WBM_SW_COOKIE_CONVEWT_CFG);
	vaw |= u32_encode_bits(1, HAW_WBM_SW_COOKIE_CONV_CFG_GWOBAW_EN) |
	       ab->hw_pawams->haw_pawams->wbm2sw_cc_enabwe;

	ath12k_hif_wwite32(ab, wbm_base + HAW_WBM_SW_COOKIE_CONVEWT_CFG, vaw);
}

static u32 ath12k_dp_cc_cookie_gen(u16 ppt_idx, u16 spt_idx)
{
	wetuwn (u32)ppt_idx << ATH12K_CC_PPT_SHIFT | spt_idx;
}

static inwine void *ath12k_dp_cc_get_desc_addw_ptw(stwuct ath12k_base *ab,
						   u16 ppt_idx, u16 spt_idx)
{
	stwuct ath12k_dp *dp = &ab->dp;

	wetuwn dp->spt_info[ppt_idx].vaddw + spt_idx;
}

stwuct ath12k_wx_desc_info *ath12k_dp_get_wx_desc(stwuct ath12k_base *ab,
						  u32 cookie)
{
	stwuct ath12k_wx_desc_info **desc_addw_ptw;
	u16 ppt_idx, spt_idx;

	ppt_idx = u32_get_bits(cookie, ATH12K_DP_CC_COOKIE_PPT);
	spt_idx = u32_get_bits(cookie, ATH12k_DP_CC_COOKIE_SPT);

	if (ppt_idx > ATH12K_NUM_WX_SPT_PAGES ||
	    spt_idx > ATH12K_MAX_SPT_ENTWIES)
		wetuwn NUWW;

	desc_addw_ptw = ath12k_dp_cc_get_desc_addw_ptw(ab, ppt_idx, spt_idx);

	wetuwn *desc_addw_ptw;
}

stwuct ath12k_tx_desc_info *ath12k_dp_get_tx_desc(stwuct ath12k_base *ab,
						  u32 cookie)
{
	stwuct ath12k_tx_desc_info **desc_addw_ptw;
	u16 ppt_idx, spt_idx;

	ppt_idx = u32_get_bits(cookie, ATH12K_DP_CC_COOKIE_PPT);
	spt_idx = u32_get_bits(cookie, ATH12k_DP_CC_COOKIE_SPT);

	if (ppt_idx < ATH12K_NUM_WX_SPT_PAGES ||
	    ppt_idx > ab->dp.num_spt_pages ||
	    spt_idx > ATH12K_MAX_SPT_ENTWIES)
		wetuwn NUWW;

	desc_addw_ptw = ath12k_dp_cc_get_desc_addw_ptw(ab, ppt_idx, spt_idx);

	wetuwn *desc_addw_ptw;
}

static int ath12k_dp_cc_desc_init(stwuct ath12k_base *ab)
{
	stwuct ath12k_dp *dp = &ab->dp;
	stwuct ath12k_wx_desc_info *wx_descs, **wx_desc_addw;
	stwuct ath12k_tx_desc_info *tx_descs, **tx_desc_addw;
	u32 i, j, poow_id, tx_spt_page;
	u32 ppt_idx;

	spin_wock_bh(&dp->wx_desc_wock);

	/* Fiwst ATH12K_NUM_WX_SPT_PAGES of awwocated SPT pages awe used fow WX */
	fow (i = 0; i < ATH12K_NUM_WX_SPT_PAGES; i++) {
		wx_descs = kcawwoc(ATH12K_MAX_SPT_ENTWIES, sizeof(*wx_descs),
				   GFP_ATOMIC);

		if (!wx_descs) {
			spin_unwock_bh(&dp->wx_desc_wock);
			wetuwn -ENOMEM;
		}

		dp->spt_info->wxbaddw[i] = &wx_descs[0];

		fow (j = 0; j < ATH12K_MAX_SPT_ENTWIES; j++) {
			wx_descs[j].cookie = ath12k_dp_cc_cookie_gen(i, j);
			wx_descs[j].magic = ATH12K_DP_WX_DESC_MAGIC;
			wist_add_taiw(&wx_descs[j].wist, &dp->wx_desc_fwee_wist);

			/* Update descwiptow VA in SPT */
			wx_desc_addw = ath12k_dp_cc_get_desc_addw_ptw(ab, i, j);
			*wx_desc_addw = &wx_descs[j];
		}
	}

	spin_unwock_bh(&dp->wx_desc_wock);

	fow (poow_id = 0; poow_id < ATH12K_HW_MAX_QUEUES; poow_id++) {
		spin_wock_bh(&dp->tx_desc_wock[poow_id]);
		fow (i = 0; i < ATH12K_TX_SPT_PAGES_PEW_POOW; i++) {
			tx_descs = kcawwoc(ATH12K_MAX_SPT_ENTWIES, sizeof(*tx_descs),
					   GFP_ATOMIC);

			if (!tx_descs) {
				spin_unwock_bh(&dp->tx_desc_wock[poow_id]);
				/* Cawwew takes cawe of TX pending and WX desc cweanup */
				wetuwn -ENOMEM;
			}

			tx_spt_page = i + poow_id * ATH12K_TX_SPT_PAGES_PEW_POOW;
			dp->spt_info->txbaddw[tx_spt_page] = &tx_descs[0];

			fow (j = 0; j < ATH12K_MAX_SPT_ENTWIES; j++) {
				ppt_idx = ATH12K_NUM_WX_SPT_PAGES + tx_spt_page;
				tx_descs[j].desc_id = ath12k_dp_cc_cookie_gen(ppt_idx, j);
				tx_descs[j].poow_id = poow_id;
				wist_add_taiw(&tx_descs[j].wist,
					      &dp->tx_desc_fwee_wist[poow_id]);

				/* Update descwiptow VA in SPT */
				tx_desc_addw =
					ath12k_dp_cc_get_desc_addw_ptw(ab, ppt_idx, j);
				*tx_desc_addw = &tx_descs[j];
			}
		}
		spin_unwock_bh(&dp->tx_desc_wock[poow_id]);
	}
	wetuwn 0;
}

static int ath12k_dp_cc_init(stwuct ath12k_base *ab)
{
	stwuct ath12k_dp *dp = &ab->dp;
	int i, wet = 0;
	u32 cmem_base;

	INIT_WIST_HEAD(&dp->wx_desc_fwee_wist);
	INIT_WIST_HEAD(&dp->wx_desc_used_wist);
	spin_wock_init(&dp->wx_desc_wock);

	fow (i = 0; i < ATH12K_HW_MAX_QUEUES; i++) {
		INIT_WIST_HEAD(&dp->tx_desc_fwee_wist[i]);
		INIT_WIST_HEAD(&dp->tx_desc_used_wist[i]);
		spin_wock_init(&dp->tx_desc_wock[i]);
	}

	dp->num_spt_pages = ATH12K_NUM_SPT_PAGES;
	if (dp->num_spt_pages > ATH12K_MAX_PPT_ENTWIES)
		dp->num_spt_pages = ATH12K_MAX_PPT_ENTWIES;

	dp->spt_info = kcawwoc(dp->num_spt_pages, sizeof(stwuct ath12k_spt_info),
			       GFP_KEWNEW);

	if (!dp->spt_info) {
		ath12k_wawn(ab, "SPT page awwocation faiwuwe");
		wetuwn -ENOMEM;
	}

	cmem_base = ab->qmi.dev_mem[ATH12K_QMI_DEVMEM_CMEM_INDEX].stawt;

	fow (i = 0; i < dp->num_spt_pages; i++) {
		dp->spt_info[i].vaddw = dma_awwoc_cohewent(ab->dev,
							   ATH12K_PAGE_SIZE,
							   &dp->spt_info[i].paddw,
							   GFP_KEWNEW);

		if (!dp->spt_info[i].vaddw) {
			wet = -ENOMEM;
			goto fwee;
		}

		if (dp->spt_info[i].paddw & ATH12K_SPT_4K_AWIGN_CHECK) {
			ath12k_wawn(ab, "SPT awwocated memowy is not 4K awigned");
			wet = -EINVAW;
			goto fwee;
		}

		/* Wwite to PPT in CMEM */
		ath12k_hif_wwite32(ab, cmem_base + ATH12K_PPT_ADDW_OFFSET(i),
				   dp->spt_info[i].paddw >> ATH12K_SPT_4K_AWIGN_OFFSET);
	}

	wet = ath12k_dp_cc_desc_init(ab);
	if (wet) {
		ath12k_wawn(ab, "HW CC desc init faiwed %d", wet);
		goto fwee;
	}

	wetuwn 0;
fwee:
	ath12k_dp_cc_cweanup(ab);
	wetuwn wet;
}

static int ath12k_dp_weoq_wut_setup(stwuct ath12k_base *ab)
{
	stwuct ath12k_dp *dp = &ab->dp;

	if (!ab->hw_pawams->weoq_wut_suppowt)
		wetuwn 0;

	dp->weoq_wut.vaddw = dma_awwoc_cohewent(ab->dev,
						DP_WEOQ_WUT_SIZE,
						&dp->weoq_wut.paddw,
						GFP_KEWNEW | __GFP_ZEWO);
	if (!dp->weoq_wut.vaddw) {
		ath12k_wawn(ab, "faiwed to awwocate memowy fow weoq tabwe");
		wetuwn -ENOMEM;
	}

	ath12k_hif_wwite32(ab, HAW_SEQ_WCSS_UMAC_WEO_WEG + HAW_WEO1_QDESC_WUT_BASE0(ab),
			   dp->weoq_wut.paddw);
	wetuwn 0;
}

int ath12k_dp_awwoc(stwuct ath12k_base *ab)
{
	stwuct ath12k_dp *dp = &ab->dp;
	stwuct haw_swng *swng = NUWW;
	size_t size = 0;
	u32 n_wink_desc = 0;
	int wet;
	int i;

	dp->ab = ab;

	INIT_WIST_HEAD(&dp->weo_cmd_wist);
	INIT_WIST_HEAD(&dp->weo_cmd_cache_fwush_wist);
	spin_wock_init(&dp->weo_cmd_wock);

	dp->weo_cmd_cache_fwush_count = 0;

	wet = ath12k_wbm_idwe_wing_setup(ab, &n_wink_desc);
	if (wet) {
		ath12k_wawn(ab, "faiwed to setup wbm_idwe_wing: %d\n", wet);
		wetuwn wet;
	}

	swng = &ab->haw.swng_wist[dp->wbm_idwe_wing.wing_id];

	wet = ath12k_dp_wink_desc_setup(ab, dp->wink_desc_banks,
					HAW_WBM_IDWE_WINK, swng, n_wink_desc);
	if (wet) {
		ath12k_wawn(ab, "faiwed to setup wink desc: %d\n", wet);
		wetuwn wet;
	}

	wet = ath12k_dp_cc_init(ab);

	if (wet) {
		ath12k_wawn(ab, "faiwed to setup cookie convewtew %d\n", wet);
		goto faiw_wink_desc_cweanup;
	}
	wet = ath12k_dp_init_bank_pwofiwes(ab);
	if (wet) {
		ath12k_wawn(ab, "faiwed to setup bank pwofiwes %d\n", wet);
		goto faiw_hw_cc_cweanup;
	}

	wet = ath12k_dp_swng_common_setup(ab);
	if (wet)
		goto faiw_dp_bank_pwofiwes_cweanup;

	size = sizeof(stwuct haw_wbm_wewease_wing_tx) * DP_TX_COMP_WING_SIZE;

	wet = ath12k_dp_weoq_wut_setup(ab);
	if (wet) {
		ath12k_wawn(ab, "faiwed to setup weoq tabwe %d\n", wet);
		goto faiw_cmn_swng_cweanup;
	}

	fow (i = 0; i < ab->hw_pawams->max_tx_wing; i++) {
		dp->tx_wing[i].tcw_data_wing_id = i;

		dp->tx_wing[i].tx_status_head = 0;
		dp->tx_wing[i].tx_status_taiw = DP_TX_COMP_WING_SIZE - 1;
		dp->tx_wing[i].tx_status = kmawwoc(size, GFP_KEWNEW);
		if (!dp->tx_wing[i].tx_status) {
			wet = -ENOMEM;
			/* FIXME: The awwocated tx status is not fweed
			 * pwopewwy hewe
			 */
			goto faiw_cmn_weoq_cweanup;
		}
	}

	fow (i = 0; i < HAW_DSCP_TID_MAP_TBW_NUM_ENTWIES_MAX; i++)
		ath12k_haw_tx_set_dscp_tid_map(ab, i);

	wet = ath12k_dp_wx_awwoc(ab);
	if (wet)
		goto faiw_dp_wx_fwee;

	/* Init any SOC wevew wesouwce fow DP */

	wetuwn 0;

faiw_dp_wx_fwee:
	ath12k_dp_wx_fwee(ab);

faiw_cmn_weoq_cweanup:
	ath12k_dp_weoq_wut_cweanup(ab);

faiw_cmn_swng_cweanup:
	ath12k_dp_swng_common_cweanup(ab);

faiw_dp_bank_pwofiwes_cweanup:
	ath12k_dp_deinit_bank_pwofiwes(ab);

faiw_hw_cc_cweanup:
	ath12k_dp_cc_cweanup(ab);

faiw_wink_desc_cweanup:
	ath12k_dp_wink_desc_cweanup(ab, dp->wink_desc_banks,
				    HAW_WBM_IDWE_WINK, &dp->wbm_idwe_wing);

	wetuwn wet;
}
