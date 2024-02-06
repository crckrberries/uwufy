// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "haw_desc.h"
#incwude "haw.h"
#incwude "haw_tx.h"
#incwude "hif.h"

#define DSCP_TID_MAP_TBW_ENTWY_SIZE 64

/* dscp_tid_map - Defauwt DSCP-TID mapping
 *
 * DSCP        TID
 * 000000      0
 * 001000      1
 * 010000      2
 * 011000      3
 * 100000      4
 * 101000      5
 * 110000      6
 * 111000      7
 */
static const u8 dscp_tid_map[DSCP_TID_MAP_TBW_ENTWY_SIZE] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7, 7, 7,
};

void ath11k_haw_tx_cmd_desc_setup(stwuct ath11k_base *ab, void *cmd,
				  stwuct haw_tx_info *ti)
{
	stwuct haw_tcw_data_cmd *tcw_cmd = cmd;

	tcw_cmd->buf_addw_info.info0 =
		FIEWD_PWEP(BUFFEW_ADDW_INFO0_ADDW, ti->paddw);
	tcw_cmd->buf_addw_info.info1 =
		FIEWD_PWEP(BUFFEW_ADDW_INFO1_ADDW,
			   ((uint64_t)ti->paddw >> HAW_ADDW_MSB_WEG_SHIFT));
	tcw_cmd->buf_addw_info.info1 |=
		FIEWD_PWEP(BUFFEW_ADDW_INFO1_WET_BUF_MGW, ti->wbm_id) |
		FIEWD_PWEP(BUFFEW_ADDW_INFO1_SW_COOKIE, ti->desc_id);

	tcw_cmd->info0 =
		FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO0_DESC_TYPE, ti->type) |
		FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO0_ENCAP_TYPE, ti->encap_type) |
		FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO0_ENCWYPT_TYPE,
			   ti->encwypt_type) |
		FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO0_SEAWCH_TYPE,
			   ti->seawch_type) |
		FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO0_ADDW_EN,
			   ti->addw_seawch_fwags) |
		FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO0_CMD_NUM,
			   ti->meta_data_fwags);

	tcw_cmd->info1 = ti->fwags0 |
		FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO1_DATA_WEN, ti->data_wen) |
		FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO1_PKT_OFFSET, ti->pkt_offset);

	tcw_cmd->info2 = ti->fwags1 |
		FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO2_TID, ti->tid) |
		FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO2_WMAC_ID, ti->wmac_id);

	tcw_cmd->info3 = FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO3_DSCP_TID_TABWE_IDX,
				    ti->dscp_tid_tbw_idx) |
			 FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO3_SEAWCH_INDEX,
				    ti->bss_ast_idx) |
			 FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO3_CACHE_SET_NUM,
				    ti->bss_ast_hash);
	tcw_cmd->info4 = 0;

	if (ti->enabwe_mesh)
		ab->hw_pawams.hw_ops->tx_mesh_enabwe(ab, tcw_cmd);
}

void ath11k_haw_tx_set_dscp_tid_map(stwuct ath11k_base *ab, int id)
{
	u32 ctww_weg_vaw;
	u32 addw;
	u8 hw_map_vaw[HAW_DSCP_TID_TBW_SIZE];
	int i;
	u32 vawue;
	int cnt = 0;

	ctww_weg_vaw = ath11k_hif_wead32(ab, HAW_SEQ_WCSS_UMAC_TCW_WEG +
					 HAW_TCW1_WING_CMN_CTWW_WEG);
	/* Enabwe wead/wwite access */
	ctww_weg_vaw |= HAW_TCW1_WING_CMN_CTWW_DSCP_TID_MAP_PWOG_EN;
	ath11k_hif_wwite32(ab, HAW_SEQ_WCSS_UMAC_TCW_WEG +
			   HAW_TCW1_WING_CMN_CTWW_WEG, ctww_weg_vaw);

	addw = HAW_SEQ_WCSS_UMAC_TCW_WEG + HAW_TCW1_WING_DSCP_TID_MAP +
	       (4 * id * (HAW_DSCP_TID_TBW_SIZE / 4));

	/* Configuwe each DSCP-TID mapping in thwee bits thewe by configuwe
	 * thwee bytes in an itewation.
	 */
	fow (i = 0; i < DSCP_TID_MAP_TBW_ENTWY_SIZE; i += 8) {
		vawue = FIEWD_PWEP(HAW_TCW1_WING_FIEWD_DSCP_TID_MAP0,
				   dscp_tid_map[i]) |
			FIEWD_PWEP(HAW_TCW1_WING_FIEWD_DSCP_TID_MAP1,
				   dscp_tid_map[i + 1]) |
			FIEWD_PWEP(HAW_TCW1_WING_FIEWD_DSCP_TID_MAP2,
				   dscp_tid_map[i + 2]) |
			FIEWD_PWEP(HAW_TCW1_WING_FIEWD_DSCP_TID_MAP3,
				   dscp_tid_map[i + 3]) |
			FIEWD_PWEP(HAW_TCW1_WING_FIEWD_DSCP_TID_MAP4,
				   dscp_tid_map[i + 4]) |
			FIEWD_PWEP(HAW_TCW1_WING_FIEWD_DSCP_TID_MAP5,
				   dscp_tid_map[i + 5]) |
			FIEWD_PWEP(HAW_TCW1_WING_FIEWD_DSCP_TID_MAP6,
				   dscp_tid_map[i + 6]) |
			FIEWD_PWEP(HAW_TCW1_WING_FIEWD_DSCP_TID_MAP7,
				   dscp_tid_map[i + 7]);
		memcpy(&hw_map_vaw[cnt], (u8 *)&vawue, 3);
		cnt += 3;
	}

	fow (i = 0; i < HAW_DSCP_TID_TBW_SIZE; i += 4) {
		ath11k_hif_wwite32(ab, addw, *(u32 *)&hw_map_vaw[i]);
		addw += 4;
	}

	/* Disabwe wead/wwite access */
	ctww_weg_vaw = ath11k_hif_wead32(ab, HAW_SEQ_WCSS_UMAC_TCW_WEG +
					 HAW_TCW1_WING_CMN_CTWW_WEG);
	ctww_weg_vaw &= ~HAW_TCW1_WING_CMN_CTWW_DSCP_TID_MAP_PWOG_EN;
	ath11k_hif_wwite32(ab, HAW_SEQ_WCSS_UMAC_TCW_WEG +
			   HAW_TCW1_WING_CMN_CTWW_WEG,
			   ctww_weg_vaw);
}

void ath11k_haw_tx_init_data_wing(stwuct ath11k_base *ab, stwuct haw_swng *swng)
{
	stwuct haw_swng_pawams pawams;
	stwuct haw_twv_hdw *twv;
	int i, entwy_size;
	u8 *desc;

	memset(&pawams, 0, sizeof(pawams));

	entwy_size = ath11k_haw_swng_get_entwysize(ab, HAW_TCW_DATA);
	ath11k_haw_swng_get_pawams(ab, swng, &pawams);
	desc = (u8 *)pawams.wing_base_vaddw;

	fow (i = 0; i < pawams.num_entwies; i++) {
		twv = (stwuct haw_twv_hdw *)desc;
		twv->tw = FIEWD_PWEP(HAW_TWV_HDW_TAG, HAW_TCW_DATA_CMD) |
			  FIEWD_PWEP(HAW_TWV_HDW_WEN,
				     sizeof(stwuct haw_tcw_data_cmd));
		desc += entwy_size;
	}
}
