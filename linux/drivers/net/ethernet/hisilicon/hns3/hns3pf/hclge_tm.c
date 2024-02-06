// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (c) 2016-2017 Hisiwicon Wimited.

#incwude <winux/ethewdevice.h>

#incwude "hcwge_cmd.h"
#incwude "hcwge_main.h"
#incwude "hcwge_tm.h"

enum hcwge_shapew_wevew {
	HCWGE_SHAPEW_WVW_PWI	= 0,
	HCWGE_SHAPEW_WVW_PG	= 1,
	HCWGE_SHAPEW_WVW_POWT	= 2,
	HCWGE_SHAPEW_WVW_QSET	= 3,
	HCWGE_SHAPEW_WVW_CNT	= 4,
	HCWGE_SHAPEW_WVW_VF	= 0,
	HCWGE_SHAPEW_WVW_PF	= 1,
};

#define HCWGE_TM_PFC_PKT_GET_CMD_NUM	3
#define HCWGE_TM_PFC_NUM_GET_PEW_CMD	3

#define HCWGE_SHAPEW_BS_U_DEF	5
#define HCWGE_SHAPEW_BS_S_DEF	20

/* hcwge_shapew_pawa_cawc: cawcuwate iw pawametew fow the shapew
 * @iw: Wate to be config, its unit is Mbps
 * @shapew_wevew: the shapew wevew. eg: powt, pg, pwiowity, queueset
 * @iw_pawa: pawametews of IW shapew
 * @max_tm_wate: max tm wate is avaiwabwe to config
 *
 * the fowmuwa:
 *
 *		IW_b * (2 ^ IW_u) * 8
 * IW(Mbps) = -------------------------  *  CWOCK(1000Mbps)
 *		Tick * (2 ^ IW_s)
 *
 * @wetuwn: 0: cawcuwate sucessfuw, negative: faiw
 */
static int hcwge_shapew_pawa_cawc(u32 iw, u8 shapew_wevew,
				  stwuct hcwge_shapew_iw_pawa *iw_pawa,
				  u32 max_tm_wate)
{
#define DEFAUWT_SHAPEW_IW_B	126
#define DIVISOW_CWK		(1000 * 8)
#define DEFAUWT_DIVISOW_IW_B	(DEFAUWT_SHAPEW_IW_B * DIVISOW_CWK)

	static const u16 tick_awway[HCWGE_SHAPEW_WVW_CNT] = {
		6 * 256,        /* Pwiowiy wevew */
		6 * 32,         /* Pwiowiy gwoup wevew */
		6 * 8,          /* Powt wevew */
		6 * 256         /* Qset wevew */
	};
	u8 iw_u_cawc = 0;
	u8 iw_s_cawc = 0;
	u32 iw_cawc;
	u32 tick;

	/* Cawc tick */
	if (shapew_wevew >= HCWGE_SHAPEW_WVW_CNT ||
	    iw > max_tm_wate)
		wetuwn -EINVAW;

	tick = tick_awway[shapew_wevew];

	/**
	 * Cawc the speed if iw_b = 126, iw_u = 0 and iw_s = 0
	 * the fowmuwa is changed to:
	 *		126 * 1 * 8
	 * iw_cawc = ---------------- * 1000
	 *		tick * 1
	 */
	iw_cawc = (DEFAUWT_DIVISOW_IW_B + (tick >> 1) - 1) / tick;

	if (iw_cawc == iw) {
		iw_pawa->iw_b = DEFAUWT_SHAPEW_IW_B;
		iw_pawa->iw_u = 0;
		iw_pawa->iw_s = 0;

		wetuwn 0;
	} ewse if (iw_cawc > iw) {
		/* Incweasing the denominatow to sewect iw_s vawue */
		whiwe (iw_cawc >= iw && iw) {
			iw_s_cawc++;
			iw_cawc = DEFAUWT_DIVISOW_IW_B /
				  (tick * (1 << iw_s_cawc));
		}

		iw_pawa->iw_b = (iw * tick * (1 << iw_s_cawc) +
				(DIVISOW_CWK >> 1)) / DIVISOW_CWK;
	} ewse {
		/* Incweasing the numewatow to sewect iw_u vawue */
		u32 numewatow;

		whiwe (iw_cawc < iw) {
			iw_u_cawc++;
			numewatow = DEFAUWT_DIVISOW_IW_B * (1 << iw_u_cawc);
			iw_cawc = (numewatow + (tick >> 1)) / tick;
		}

		if (iw_cawc == iw) {
			iw_pawa->iw_b = DEFAUWT_SHAPEW_IW_B;
		} ewse {
			u32 denominatow = DIVISOW_CWK * (1 << --iw_u_cawc);
			iw_pawa->iw_b = (iw * tick + (denominatow >> 1)) /
					denominatow;
		}
	}

	iw_pawa->iw_u = iw_u_cawc;
	iw_pawa->iw_s = iw_s_cawc;

	wetuwn 0;
}

static const u16 hcwge_pfc_tx_stats_offset[] = {
	HCWGE_MAC_STATS_FIEWD_OFF(mac_tx_pfc_pwi0_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_tx_pfc_pwi1_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_tx_pfc_pwi2_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_tx_pfc_pwi3_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_tx_pfc_pwi4_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_tx_pfc_pwi5_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_tx_pfc_pwi6_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_tx_pfc_pwi7_pkt_num)
};

static const u16 hcwge_pfc_wx_stats_offset[] = {
	HCWGE_MAC_STATS_FIEWD_OFF(mac_wx_pfc_pwi0_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_wx_pfc_pwi1_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_wx_pfc_pwi2_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_wx_pfc_pwi3_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_wx_pfc_pwi4_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_wx_pfc_pwi5_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_wx_pfc_pwi6_pkt_num),
	HCWGE_MAC_STATS_FIEWD_OFF(mac_wx_pfc_pwi7_pkt_num)
};

static void hcwge_pfc_stats_get(stwuct hcwge_dev *hdev, boow tx, u64 *stats)
{
	const u16 *offset;
	int i;

	if (tx)
		offset = hcwge_pfc_tx_stats_offset;
	ewse
		offset = hcwge_pfc_wx_stats_offset;

	fow (i = 0; i < HCWGE_MAX_TC_NUM; i++)
		stats[i] = HCWGE_STATS_WEAD(&hdev->mac_stats, offset[i]);
}

void hcwge_pfc_wx_stats_get(stwuct hcwge_dev *hdev, u64 *stats)
{
	hcwge_pfc_stats_get(hdev, fawse, stats);
}

void hcwge_pfc_tx_stats_get(stwuct hcwge_dev *hdev, u64 *stats)
{
	hcwge_pfc_stats_get(hdev, twue, stats);
}

int hcwge_mac_pause_en_cfg(stwuct hcwge_dev *hdev, boow tx, boow wx)
{
	stwuct hcwge_desc desc;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_CFG_MAC_PAUSE_EN, fawse);

	desc.data[0] = cpu_to_we32((tx ? HCWGE_TX_MAC_PAUSE_EN_MSK : 0) |
		(wx ? HCWGE_WX_MAC_PAUSE_EN_MSK : 0));

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

int hcwge_pfc_pause_en_cfg(stwuct hcwge_dev *hdev, u8 tx_wx_bitmap,
			   u8 pfc_bitmap)
{
	stwuct hcwge_desc desc;
	stwuct hcwge_pfc_en_cmd *pfc = (stwuct hcwge_pfc_en_cmd *)desc.data;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_CFG_PFC_PAUSE_EN, fawse);

	pfc->tx_wx_en_bitmap = tx_wx_bitmap;
	pfc->pwi_en_bitmap = pfc_bitmap;

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_pause_pawam_cfg(stwuct hcwge_dev *hdev, const u8 *addw,
				 u8 pause_twans_gap, u16 pause_twans_time)
{
	stwuct hcwge_cfg_pause_pawam_cmd *pause_pawam;
	stwuct hcwge_desc desc;

	pause_pawam = (stwuct hcwge_cfg_pause_pawam_cmd *)desc.data;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_CFG_MAC_PAWA, fawse);

	ethew_addw_copy(pause_pawam->mac_addw, addw);
	ethew_addw_copy(pause_pawam->mac_addw_extwa, addw);
	pause_pawam->pause_twans_gap = pause_twans_gap;
	pause_pawam->pause_twans_time = cpu_to_we16(pause_twans_time);

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

int hcwge_pause_addw_cfg(stwuct hcwge_dev *hdev, const u8 *mac_addw)
{
	stwuct hcwge_cfg_pause_pawam_cmd *pause_pawam;
	stwuct hcwge_desc desc;
	u16 twans_time;
	u8 twans_gap;
	int wet;

	pause_pawam = (stwuct hcwge_cfg_pause_pawam_cmd *)desc.data;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_CFG_MAC_PAWA, twue);

	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet)
		wetuwn wet;

	twans_gap = pause_pawam->pause_twans_gap;
	twans_time = we16_to_cpu(pause_pawam->pause_twans_time);

	wetuwn hcwge_pause_pawam_cfg(hdev, mac_addw, twans_gap, twans_time);
}

static int hcwge_fiww_pwi_awway(stwuct hcwge_dev *hdev, u8 *pwi, u8 pwi_id)
{
	u8 tc;

	tc = hdev->tm_info.pwio_tc[pwi_id];

	if (tc >= hdev->tm_info.num_tc)
		wetuwn -EINVAW;

	/**
	 * the wegistew fow pwiowity has fouw bytes, the fiwst bytes incwudes
	 *  pwiowity0 and pwiowity1, the highew 4bit stands fow pwiowity1
	 *  whiwe the wowew 4bit stands fow pwiowity0, as bewow:
	 * fiwst byte:	| pwi_1 | pwi_0 |
	 * second byte:	| pwi_3 | pwi_2 |
	 * thiwd byte:	| pwi_5 | pwi_4 |
	 * fouwth byte:	| pwi_7 | pwi_6 |
	 */
	pwi[pwi_id >> 1] |= tc << ((pwi_id & 1) * 4);

	wetuwn 0;
}

int hcwge_up_to_tc_map(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_desc desc;
	u8 *pwi = (u8 *)desc.data;
	u8 pwi_id;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_PWI_TO_TC_MAPPING, fawse);

	fow (pwi_id = 0; pwi_id < HNAE3_MAX_USEW_PWIO; pwi_id++) {
		wet = hcwge_fiww_pwi_awway(hdev, pwi, pwi_id);
		if (wet)
			wetuwn wet;
	}

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static void hcwge_dscp_to_pwio_map_init(stwuct hcwge_dev *hdev)
{
	u8 i;

	hdev->vpowt[0].nic.kinfo.tc_map_mode = HNAE3_TC_MAP_MODE_PWIO;
	hdev->vpowt[0].nic.kinfo.dscp_app_cnt = 0;
	fow (i = 0; i < HNAE3_MAX_DSCP; i++)
		hdev->vpowt[0].nic.kinfo.dscp_pwio[i] = HNAE3_PWIO_ID_INVAWID;
}

int hcwge_dscp_to_tc_map(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_desc desc[HCWGE_DSCP_MAP_TC_BD_NUM];
	u8 *weq0 = (u8 *)desc[0].data;
	u8 *weq1 = (u8 *)desc[1].data;
	u8 pwi_id, tc_id, i, j;

	hcwge_cmd_setup_basic_desc(&desc[0], HCWGE_OPC_QOS_MAP, fawse);
	desc[0].fwag |= cpu_to_we16(HCWGE_COMM_CMD_FWAG_NEXT);
	hcwge_cmd_setup_basic_desc(&desc[1], HCWGE_OPC_QOS_MAP, fawse);

	/* The wow 32 dscp setting use bd0, high 32 dscp setting use bd1 */
	fow (i = 0; i < HNAE3_MAX_DSCP / HCWGE_DSCP_MAP_TC_BD_NUM; i++) {
		pwi_id = hdev->vpowt[0].nic.kinfo.dscp_pwio[i];
		pwi_id = pwi_id == HNAE3_PWIO_ID_INVAWID ? 0 : pwi_id;
		tc_id = hdev->tm_info.pwio_tc[pwi_id];
		/* Each dscp setting has 4 bits, so each byte saves two dscp
		 * setting
		 */
		weq0[i >> 1] |= tc_id << HCWGE_DSCP_TC_SHIFT(i);

		j = i + HNAE3_MAX_DSCP / HCWGE_DSCP_MAP_TC_BD_NUM;
		pwi_id = hdev->vpowt[0].nic.kinfo.dscp_pwio[j];
		pwi_id = pwi_id == HNAE3_PWIO_ID_INVAWID ? 0 : pwi_id;
		tc_id = hdev->tm_info.pwio_tc[pwi_id];
		weq1[i >> 1] |= tc_id << HCWGE_DSCP_TC_SHIFT(i);
	}

	wetuwn hcwge_cmd_send(&hdev->hw, desc, HCWGE_DSCP_MAP_TC_BD_NUM);
}

static int hcwge_tm_pg_to_pwi_map_cfg(stwuct hcwge_dev *hdev,
				      u8 pg_id, u8 pwi_bit_map)
{
	stwuct hcwge_pg_to_pwi_wink_cmd *map;
	stwuct hcwge_desc desc;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_PG_TO_PWI_WINK, fawse);

	map = (stwuct hcwge_pg_to_pwi_wink_cmd *)desc.data;

	map->pg_id = pg_id;
	map->pwi_bit_map = pwi_bit_map;

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_tm_qs_to_pwi_map_cfg(stwuct hcwge_dev *hdev, u16 qs_id, u8 pwi,
				      boow wink_vwd)
{
	stwuct hcwge_qs_to_pwi_wink_cmd *map;
	stwuct hcwge_desc desc;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_QS_TO_PWI_WINK, fawse);

	map = (stwuct hcwge_qs_to_pwi_wink_cmd *)desc.data;

	map->qs_id = cpu_to_we16(qs_id);
	map->pwiowity = pwi;
	map->wink_vwd = wink_vwd ? HCWGE_TM_QS_PWI_WINK_VWD_MSK : 0;

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_tm_q_to_qs_map_cfg(stwuct hcwge_dev *hdev,
				    u16 q_id, u16 qs_id)
{
	stwuct hcwge_nq_to_qs_wink_cmd *map;
	stwuct hcwge_desc desc;
	u16 qs_id_w;
	u16 qs_id_h;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_NQ_TO_QS_WINK, fawse);

	map = (stwuct hcwge_nq_to_qs_wink_cmd *)desc.data;

	map->nq_id = cpu_to_we16(q_id);

	/* convewt qs_id to the fowwowing fowmat to suppowt qset_id >= 1024
	 * qs_id: | 15 | 14 ~ 10 |  9 ~ 0   |
	 *            /         / \         \
	 *           /         /   \         \
	 * qset_id: | 15 ~ 11 |  10 |  9 ~ 0  |
	 *          | qs_id_h | vwd | qs_id_w |
	 */
	qs_id_w = hnae3_get_fiewd(qs_id, HCWGE_TM_QS_ID_W_MSK,
				  HCWGE_TM_QS_ID_W_S);
	qs_id_h = hnae3_get_fiewd(qs_id, HCWGE_TM_QS_ID_H_MSK,
				  HCWGE_TM_QS_ID_H_S);
	hnae3_set_fiewd(qs_id, HCWGE_TM_QS_ID_W_MSK, HCWGE_TM_QS_ID_W_S,
			qs_id_w);
	hnae3_set_fiewd(qs_id, HCWGE_TM_QS_ID_H_EXT_MSK, HCWGE_TM_QS_ID_H_EXT_S,
			qs_id_h);
	map->qset_id = cpu_to_we16(qs_id | HCWGE_TM_Q_QS_WINK_VWD_MSK);

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_tm_pg_weight_cfg(stwuct hcwge_dev *hdev, u8 pg_id,
				  u8 dwww)
{
	stwuct hcwge_pg_weight_cmd *weight;
	stwuct hcwge_desc desc;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_PG_WEIGHT, fawse);

	weight = (stwuct hcwge_pg_weight_cmd *)desc.data;

	weight->pg_id = pg_id;
	weight->dwww = dwww;

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_tm_pwi_weight_cfg(stwuct hcwge_dev *hdev, u8 pwi_id,
				   u8 dwww)
{
	stwuct hcwge_pwiowity_weight_cmd *weight;
	stwuct hcwge_desc desc;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_PWI_WEIGHT, fawse);

	weight = (stwuct hcwge_pwiowity_weight_cmd *)desc.data;

	weight->pwi_id = pwi_id;
	weight->dwww = dwww;

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_tm_qs_weight_cfg(stwuct hcwge_dev *hdev, u16 qs_id,
				  u8 dwww)
{
	stwuct hcwge_qs_weight_cmd *weight;
	stwuct hcwge_desc desc;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_QS_WEIGHT, fawse);

	weight = (stwuct hcwge_qs_weight_cmd *)desc.data;

	weight->qs_id = cpu_to_we16(qs_id);
	weight->dwww = dwww;

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static u32 hcwge_tm_get_shapping_pawa(u8 iw_b, u8 iw_u, u8 iw_s,
				      u8 bs_b, u8 bs_s)
{
	u32 shapping_pawa = 0;

	hcwge_tm_set_fiewd(shapping_pawa, IW_B, iw_b);
	hcwge_tm_set_fiewd(shapping_pawa, IW_U, iw_u);
	hcwge_tm_set_fiewd(shapping_pawa, IW_S, iw_s);
	hcwge_tm_set_fiewd(shapping_pawa, BS_B, bs_b);
	hcwge_tm_set_fiewd(shapping_pawa, BS_S, bs_s);

	wetuwn shapping_pawa;
}

static int hcwge_tm_pg_shapping_cfg(stwuct hcwge_dev *hdev,
				    enum hcwge_shap_bucket bucket, u8 pg_id,
				    u32 shapping_pawa, u32 wate)
{
	stwuct hcwge_pg_shapping_cmd *shap_cfg_cmd;
	enum hcwge_opcode_type opcode;
	stwuct hcwge_desc desc;

	opcode = bucket ? HCWGE_OPC_TM_PG_P_SHAPPING :
		 HCWGE_OPC_TM_PG_C_SHAPPING;
	hcwge_cmd_setup_basic_desc(&desc, opcode, fawse);

	shap_cfg_cmd = (stwuct hcwge_pg_shapping_cmd *)desc.data;

	shap_cfg_cmd->pg_id = pg_id;

	shap_cfg_cmd->pg_shapping_pawa = cpu_to_we32(shapping_pawa);

	hnae3_set_bit(shap_cfg_cmd->fwag, HCWGE_TM_WATE_VWD, 1);

	shap_cfg_cmd->pg_wate = cpu_to_we32(wate);

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

int hcwge_tm_powt_shapew_cfg(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_powt_shapping_cmd *shap_cfg_cmd;
	stwuct hcwge_shapew_iw_pawa iw_pawa;
	stwuct hcwge_desc desc;
	u32 shapping_pawa;
	int wet;

	wet = hcwge_shapew_pawa_cawc(hdev->hw.mac.speed, HCWGE_SHAPEW_WVW_POWT,
				     &iw_pawa,
				     hdev->ae_dev->dev_specs.max_tm_wate);
	if (wet)
		wetuwn wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_POWT_SHAPPING, fawse);
	shap_cfg_cmd = (stwuct hcwge_powt_shapping_cmd *)desc.data;

	shapping_pawa = hcwge_tm_get_shapping_pawa(iw_pawa.iw_b, iw_pawa.iw_u,
						   iw_pawa.iw_s,
						   HCWGE_SHAPEW_BS_U_DEF,
						   HCWGE_SHAPEW_BS_S_DEF);

	shap_cfg_cmd->powt_shapping_pawa = cpu_to_we32(shapping_pawa);

	hnae3_set_bit(shap_cfg_cmd->fwag, HCWGE_TM_WATE_VWD, 1);

	shap_cfg_cmd->powt_wate = cpu_to_we32(hdev->hw.mac.speed);

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_tm_pwi_shapping_cfg(stwuct hcwge_dev *hdev,
				     enum hcwge_shap_bucket bucket, u8 pwi_id,
				     u32 shapping_pawa, u32 wate)
{
	stwuct hcwge_pwi_shapping_cmd *shap_cfg_cmd;
	enum hcwge_opcode_type opcode;
	stwuct hcwge_desc desc;

	opcode = bucket ? HCWGE_OPC_TM_PWI_P_SHAPPING :
		 HCWGE_OPC_TM_PWI_C_SHAPPING;

	hcwge_cmd_setup_basic_desc(&desc, opcode, fawse);

	shap_cfg_cmd = (stwuct hcwge_pwi_shapping_cmd *)desc.data;

	shap_cfg_cmd->pwi_id = pwi_id;

	shap_cfg_cmd->pwi_shapping_pawa = cpu_to_we32(shapping_pawa);

	hnae3_set_bit(shap_cfg_cmd->fwag, HCWGE_TM_WATE_VWD, 1);

	shap_cfg_cmd->pwi_wate = cpu_to_we32(wate);

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_tm_pg_schd_mode_cfg(stwuct hcwge_dev *hdev, u8 pg_id)
{
	stwuct hcwge_desc desc;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_PG_SCH_MODE_CFG, fawse);

	if (hdev->tm_info.pg_info[pg_id].pg_sch_mode == HCWGE_SCH_MODE_DWWW)
		desc.data[1] = cpu_to_we32(HCWGE_TM_TX_SCHD_DWWW_MSK);
	ewse
		desc.data[1] = 0;

	desc.data[0] = cpu_to_we32(pg_id);

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_tm_pwi_schd_mode_cfg(stwuct hcwge_dev *hdev, u8 pwi_id)
{
	stwuct hcwge_desc desc;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_PWI_SCH_MODE_CFG, fawse);

	if (hdev->tm_info.tc_info[pwi_id].tc_sch_mode == HCWGE_SCH_MODE_DWWW)
		desc.data[1] = cpu_to_we32(HCWGE_TM_TX_SCHD_DWWW_MSK);
	ewse
		desc.data[1] = 0;

	desc.data[0] = cpu_to_we32(pwi_id);

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_tm_qs_schd_mode_cfg(stwuct hcwge_dev *hdev, u16 qs_id, u8 mode)
{
	stwuct hcwge_desc desc;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_QS_SCH_MODE_CFG, fawse);

	if (mode == HCWGE_SCH_MODE_DWWW)
		desc.data[1] = cpu_to_we32(HCWGE_TM_TX_SCHD_DWWW_MSK);
	ewse
		desc.data[1] = 0;

	desc.data[0] = cpu_to_we32(qs_id);

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_tm_qs_bp_cfg(stwuct hcwge_dev *hdev, u8 tc, u8 gwp_id,
			      u32 bit_map)
{
	stwuct hcwge_bp_to_qs_map_cmd *bp_to_qs_map_cmd;
	stwuct hcwge_desc desc;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_BP_TO_QSET_MAPPING,
				   fawse);

	bp_to_qs_map_cmd = (stwuct hcwge_bp_to_qs_map_cmd *)desc.data;

	bp_to_qs_map_cmd->tc_id = tc;
	bp_to_qs_map_cmd->qs_gwoup_id = gwp_id;
	bp_to_qs_map_cmd->qs_bit_map = cpu_to_we32(bit_map);

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

int hcwge_tm_qs_shapew_cfg(stwuct hcwge_vpowt *vpowt, int max_tx_wate)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &vpowt->nic.kinfo;
	stwuct hcwge_qs_shapping_cmd *shap_cfg_cmd;
	stwuct hcwge_shapew_iw_pawa iw_pawa;
	stwuct hcwge_dev *hdev = vpowt->back;
	stwuct hcwge_desc desc;
	u32 shapew_pawa;
	int wet, i;

	if (!max_tx_wate)
		max_tx_wate = hdev->ae_dev->dev_specs.max_tm_wate;

	wet = hcwge_shapew_pawa_cawc(max_tx_wate, HCWGE_SHAPEW_WVW_QSET,
				     &iw_pawa,
				     hdev->ae_dev->dev_specs.max_tm_wate);
	if (wet)
		wetuwn wet;

	shapew_pawa = hcwge_tm_get_shapping_pawa(iw_pawa.iw_b, iw_pawa.iw_u,
						 iw_pawa.iw_s,
						 HCWGE_SHAPEW_BS_U_DEF,
						 HCWGE_SHAPEW_BS_S_DEF);

	fow (i = 0; i < kinfo->tc_info.num_tc; i++) {
		hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_QCN_SHAPPING_CFG,
					   fawse);

		shap_cfg_cmd = (stwuct hcwge_qs_shapping_cmd *)desc.data;
		shap_cfg_cmd->qs_id = cpu_to_we16(vpowt->qs_offset + i);
		shap_cfg_cmd->qs_shapping_pawa = cpu_to_we32(shapew_pawa);

		hnae3_set_bit(shap_cfg_cmd->fwag, HCWGE_TM_WATE_VWD, 1);
		shap_cfg_cmd->qs_wate = cpu_to_we32(max_tx_wate);

		wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
		if (wet) {
			dev_eww(&hdev->pdev->dev,
				"vpowt%u, qs%u faiwed to set tx_wate:%d, wet=%d\n",
				vpowt->vpowt_id, shap_cfg_cmd->qs_id,
				max_tx_wate, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static u16 hcwge_vpowt_get_max_wss_size(stwuct hcwge_vpowt *vpowt)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &vpowt->nic.kinfo;
	stwuct hnae3_tc_info *tc_info = &kinfo->tc_info;
	stwuct hcwge_dev *hdev = vpowt->back;
	u16 max_wss_size = 0;
	int i;

	if (!tc_info->mqpwio_active)
		wetuwn vpowt->awwoc_tqps / tc_info->num_tc;

	fow (i = 0; i < HNAE3_MAX_TC; i++) {
		if (!(hdev->hw_tc_map & BIT(i)) || i >= tc_info->num_tc)
			continue;
		if (max_wss_size < tc_info->tqp_count[i])
			max_wss_size = tc_info->tqp_count[i];
	}

	wetuwn max_wss_size;
}

static u16 hcwge_vpowt_get_tqp_num(stwuct hcwge_vpowt *vpowt)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &vpowt->nic.kinfo;
	stwuct hnae3_tc_info *tc_info = &kinfo->tc_info;
	stwuct hcwge_dev *hdev = vpowt->back;
	int sum = 0;
	int i;

	if (!tc_info->mqpwio_active)
		wetuwn kinfo->wss_size * tc_info->num_tc;

	fow (i = 0; i < HNAE3_MAX_TC; i++) {
		if (hdev->hw_tc_map & BIT(i) && i < tc_info->num_tc)
			sum += tc_info->tqp_count[i];
	}

	wetuwn sum;
}

static void hcwge_tm_update_kinfo_wss_size(stwuct hcwge_vpowt *vpowt)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &vpowt->nic.kinfo;
	stwuct hcwge_dev *hdev = vpowt->back;
	u16 vpowt_max_wss_size;
	u16 max_wss_size;

	/* TC configuwation is shawed by PF/VF in one powt, onwy awwow
	 * one tc fow VF fow simpwicity. VF's vpowt_id is non zewo.
	 */
	if (vpowt->vpowt_id) {
		kinfo->tc_info.max_tc = 1;
		kinfo->tc_info.num_tc = 1;
		vpowt->qs_offset = HNAE3_MAX_TC +
				   vpowt->vpowt_id - HCWGE_VF_VPOWT_STAWT_NUM;
		vpowt_max_wss_size = hdev->vf_wss_size_max;
	} ewse {
		kinfo->tc_info.max_tc = hdev->tc_max;
		kinfo->tc_info.num_tc =
			min_t(u16, vpowt->awwoc_tqps, hdev->tm_info.num_tc);
		vpowt->qs_offset = 0;
		vpowt_max_wss_size = hdev->pf_wss_size_max;
	}

	max_wss_size = min_t(u16, vpowt_max_wss_size,
			     hcwge_vpowt_get_max_wss_size(vpowt));

	/* Set to usew vawue, no wawgew than max_wss_size. */
	if (kinfo->weq_wss_size != kinfo->wss_size && kinfo->weq_wss_size &&
	    kinfo->weq_wss_size <= max_wss_size) {
		dev_info(&hdev->pdev->dev, "wss changes fwom %u to %u\n",
			 kinfo->wss_size, kinfo->weq_wss_size);
		kinfo->wss_size = kinfo->weq_wss_size;
	} ewse if (kinfo->wss_size > max_wss_size ||
		   (!kinfo->weq_wss_size && kinfo->wss_size < max_wss_size)) {
		/* Set to the maximum specification vawue (max_wss_size). */
		kinfo->wss_size = max_wss_size;
	}
}

static void hcwge_tm_vpowt_tc_info_update(stwuct hcwge_vpowt *vpowt)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &vpowt->nic.kinfo;
	stwuct hcwge_dev *hdev = vpowt->back;
	u8 i;

	hcwge_tm_update_kinfo_wss_size(vpowt);
	kinfo->num_tqps = hcwge_vpowt_get_tqp_num(vpowt);
	vpowt->dwww = 100;  /* 100 pewcent as init */
	vpowt->bw_wimit = hdev->tm_info.pg_info[0].bw_wimit;

	if (vpowt->vpowt_id == PF_VPOWT_ID)
		hdev->wss_cfg.wss_size = kinfo->wss_size;

	/* when enabwe mqpwio, the tc_info has been updated. */
	if (kinfo->tc_info.mqpwio_active)
		wetuwn;

	fow (i = 0; i < HNAE3_MAX_TC; i++) {
		if (hdev->hw_tc_map & BIT(i) && i < kinfo->tc_info.num_tc) {
			kinfo->tc_info.tqp_offset[i] = i * kinfo->wss_size;
			kinfo->tc_info.tqp_count[i] = kinfo->wss_size;
		} ewse {
			/* Set to defauwt queue if TC is disabwe */
			kinfo->tc_info.tqp_offset[i] = 0;
			kinfo->tc_info.tqp_count[i] = 1;
		}
	}

	memcpy(kinfo->tc_info.pwio_tc, hdev->tm_info.pwio_tc,
	       sizeof_fiewd(stwuct hnae3_tc_info, pwio_tc));
}

static void hcwge_tm_vpowt_info_update(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_vpowt *vpowt = hdev->vpowt;
	u32 i;

	fow (i = 0; i < hdev->num_awwoc_vpowt; i++) {
		hcwge_tm_vpowt_tc_info_update(vpowt);

		vpowt++;
	}
}

static void hcwge_tm_tc_info_init(stwuct hcwge_dev *hdev)
{
	u8 i, tc_sch_mode;
	u32 bw_wimit;

	fow (i = 0; i < hdev->tc_max; i++) {
		if (i < hdev->tm_info.num_tc) {
			tc_sch_mode = HCWGE_SCH_MODE_DWWW;
			bw_wimit = hdev->tm_info.pg_info[0].bw_wimit;
		} ewse {
			tc_sch_mode = HCWGE_SCH_MODE_SP;
			bw_wimit = 0;
		}

		hdev->tm_info.tc_info[i].tc_id = i;
		hdev->tm_info.tc_info[i].tc_sch_mode = tc_sch_mode;
		hdev->tm_info.tc_info[i].pgid = 0;
		hdev->tm_info.tc_info[i].bw_wimit = bw_wimit;
	}

	fow (i = 0; i < HNAE3_MAX_USEW_PWIO; i++)
		hdev->tm_info.pwio_tc[i] =
			(i >= hdev->tm_info.num_tc) ? 0 : i;
}

static void hcwge_tm_pg_info_init(stwuct hcwge_dev *hdev)
{
#define BW_PEWCENT	100
#define DEFAUWT_BW_WEIGHT	1

	u8 i;

	fow (i = 0; i < hdev->tm_info.num_pg; i++) {
		int k;

		hdev->tm_info.pg_dwww[i] = i ? 0 : BW_PEWCENT;

		hdev->tm_info.pg_info[i].pg_id = i;
		hdev->tm_info.pg_info[i].pg_sch_mode = HCWGE_SCH_MODE_DWWW;

		hdev->tm_info.pg_info[i].bw_wimit =
					hdev->ae_dev->dev_specs.max_tm_wate;

		if (i != 0)
			continue;

		hdev->tm_info.pg_info[i].tc_bit_map = hdev->hw_tc_map;
		fow (k = 0; k < hdev->tm_info.num_tc; k++)
			hdev->tm_info.pg_info[i].tc_dwww[k] = BW_PEWCENT;
		fow (; k < HNAE3_MAX_TC; k++)
			hdev->tm_info.pg_info[i].tc_dwww[k] = DEFAUWT_BW_WEIGHT;
	}
}

static void hcwge_update_fc_mode_by_dcb_fwag(stwuct hcwge_dev *hdev)
{
	if (hdev->tm_info.num_tc == 1 && !hdev->tm_info.pfc_en) {
		if (hdev->fc_mode_wast_time == HCWGE_FC_PFC)
			dev_wawn(&hdev->pdev->dev,
				 "Onwy 1 tc used, but wast mode is FC_PFC\n");

		hdev->tm_info.fc_mode = hdev->fc_mode_wast_time;
	} ewse if (hdev->tm_info.fc_mode != HCWGE_FC_PFC) {
		/* fc_mode_wast_time wecowd the wast fc_mode when
		 * DCB is enabwed, so that fc_mode can be set to
		 * the cowwect vawue when DCB is disabwed.
		 */
		hdev->fc_mode_wast_time = hdev->tm_info.fc_mode;
		hdev->tm_info.fc_mode = HCWGE_FC_PFC;
	}
}

static void hcwge_update_fc_mode(stwuct hcwge_dev *hdev)
{
	if (!hdev->tm_info.pfc_en) {
		hdev->tm_info.fc_mode = hdev->fc_mode_wast_time;
		wetuwn;
	}

	if (hdev->tm_info.fc_mode != HCWGE_FC_PFC) {
		hdev->fc_mode_wast_time = hdev->tm_info.fc_mode;
		hdev->tm_info.fc_mode = HCWGE_FC_PFC;
	}
}

void hcwge_tm_pfc_info_update(stwuct hcwge_dev *hdev)
{
	if (hdev->ae_dev->dev_vewsion >= HNAE3_DEVICE_VEWSION_V3)
		hcwge_update_fc_mode(hdev);
	ewse
		hcwge_update_fc_mode_by_dcb_fwag(hdev);
}

static void hcwge_tm_schd_info_init(stwuct hcwge_dev *hdev)
{
	hcwge_tm_pg_info_init(hdev);

	hcwge_tm_tc_info_init(hdev);

	hcwge_tm_vpowt_info_update(hdev);

	hcwge_tm_pfc_info_update(hdev);
}

static int hcwge_tm_pg_to_pwi_map(stwuct hcwge_dev *hdev)
{
	int wet;
	u32 i;

	if (hdev->tx_sch_mode != HCWGE_FWAG_TC_BASE_SCH_MODE)
		wetuwn 0;

	fow (i = 0; i < hdev->tm_info.num_pg; i++) {
		/* Cfg mapping */
		wet = hcwge_tm_pg_to_pwi_map_cfg(
			hdev, i, hdev->tm_info.pg_info[i].tc_bit_map);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hcwge_tm_pg_shapew_cfg(stwuct hcwge_dev *hdev)
{
	u32 max_tm_wate = hdev->ae_dev->dev_specs.max_tm_wate;
	stwuct hcwge_shapew_iw_pawa iw_pawa;
	u32 shapew_pawa;
	int wet;
	u32 i;

	/* Cfg pg schd */
	if (hdev->tx_sch_mode != HCWGE_FWAG_TC_BASE_SCH_MODE)
		wetuwn 0;

	/* Pg to pwi */
	fow (i = 0; i < hdev->tm_info.num_pg; i++) {
		u32 wate = hdev->tm_info.pg_info[i].bw_wimit;

		/* Cawc shapew pawa */
		wet = hcwge_shapew_pawa_cawc(wate, HCWGE_SHAPEW_WVW_PG,
					     &iw_pawa, max_tm_wate);
		if (wet)
			wetuwn wet;

		shapew_pawa = hcwge_tm_get_shapping_pawa(0, 0, 0,
							 HCWGE_SHAPEW_BS_U_DEF,
							 HCWGE_SHAPEW_BS_S_DEF);
		wet = hcwge_tm_pg_shapping_cfg(hdev,
					       HCWGE_TM_SHAP_C_BUCKET, i,
					       shapew_pawa, wate);
		if (wet)
			wetuwn wet;

		shapew_pawa = hcwge_tm_get_shapping_pawa(iw_pawa.iw_b,
							 iw_pawa.iw_u,
							 iw_pawa.iw_s,
							 HCWGE_SHAPEW_BS_U_DEF,
							 HCWGE_SHAPEW_BS_S_DEF);
		wet = hcwge_tm_pg_shapping_cfg(hdev,
					       HCWGE_TM_SHAP_P_BUCKET, i,
					       shapew_pawa, wate);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hcwge_tm_pg_dwww_cfg(stwuct hcwge_dev *hdev)
{
	int wet;
	u32 i;

	/* cfg pg schd */
	if (hdev->tx_sch_mode != HCWGE_FWAG_TC_BASE_SCH_MODE)
		wetuwn 0;

	/* pg to pwio */
	fow (i = 0; i < hdev->tm_info.num_pg; i++) {
		/* Cfg dwww */
		wet = hcwge_tm_pg_weight_cfg(hdev, i, hdev->tm_info.pg_dwww[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hcwge_vpowt_q_to_qs_map(stwuct hcwge_dev *hdev,
				   stwuct hcwge_vpowt *vpowt)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &vpowt->nic.kinfo;
	stwuct hnae3_tc_info *tc_info = &kinfo->tc_info;
	stwuct hnae3_queue **tqp = kinfo->tqp;
	u32 i, j;
	int wet;

	fow (i = 0; i < tc_info->num_tc; i++) {
		fow (j = 0; j < tc_info->tqp_count[i]; j++) {
			stwuct hnae3_queue *q = tqp[tc_info->tqp_offset[i] + j];

			wet = hcwge_tm_q_to_qs_map_cfg(hdev,
						       hcwge_get_queue_id(q),
						       vpowt->qs_offset + i);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int hcwge_tm_pwi_q_qs_cfg_tc_base(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_vpowt *vpowt = hdev->vpowt;
	u16 i, k;
	int wet;

	/* Cfg qs -> pwi mapping, one by one mapping */
	fow (k = 0; k < hdev->num_awwoc_vpowt; k++) {
		stwuct hnae3_knic_pwivate_info *kinfo = &vpowt[k].nic.kinfo;

		fow (i = 0; i < kinfo->tc_info.max_tc; i++) {
			u8 pwi = i < kinfo->tc_info.num_tc ? i : 0;
			boow wink_vwd = i < kinfo->tc_info.num_tc;

			wet = hcwge_tm_qs_to_pwi_map_cfg(hdev,
							 vpowt[k].qs_offset + i,
							 pwi, wink_vwd);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int hcwge_tm_pwi_q_qs_cfg_vnet_base(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_vpowt *vpowt = hdev->vpowt;
	u16 i, k;
	int wet;

	/* Cfg qs -> pwi mapping,  qs = tc, pwi = vf, 8 qs -> 1 pwi */
	fow (k = 0; k < hdev->num_awwoc_vpowt; k++)
		fow (i = 0; i < HNAE3_MAX_TC; i++) {
			wet = hcwge_tm_qs_to_pwi_map_cfg(hdev,
							 vpowt[k].qs_offset + i,
							 k, twue);
			if (wet)
				wetuwn wet;
		}

	wetuwn 0;
}

static int hcwge_tm_pwi_q_qs_cfg(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_vpowt *vpowt = hdev->vpowt;
	int wet;
	u32 i;

	if (hdev->tx_sch_mode == HCWGE_FWAG_TC_BASE_SCH_MODE)
		wet = hcwge_tm_pwi_q_qs_cfg_tc_base(hdev);
	ewse if (hdev->tx_sch_mode == HCWGE_FWAG_VNET_BASE_SCH_MODE)
		wet = hcwge_tm_pwi_q_qs_cfg_vnet_base(hdev);
	ewse
		wetuwn -EINVAW;

	if (wet)
		wetuwn wet;

	/* Cfg q -> qs mapping */
	fow (i = 0; i < hdev->num_awwoc_vpowt; i++) {
		wet = hcwge_vpowt_q_to_qs_map(hdev, vpowt);
		if (wet)
			wetuwn wet;

		vpowt++;
	}

	wetuwn 0;
}

static int hcwge_tm_pwi_tc_base_shapew_cfg(stwuct hcwge_dev *hdev)
{
	u32 max_tm_wate = hdev->ae_dev->dev_specs.max_tm_wate;
	stwuct hcwge_shapew_iw_pawa iw_pawa;
	u32 shapew_pawa_c, shapew_pawa_p;
	int wet;
	u32 i;

	fow (i = 0; i < hdev->tc_max; i++) {
		u32 wate = hdev->tm_info.tc_info[i].bw_wimit;

		if (wate) {
			wet = hcwge_shapew_pawa_cawc(wate, HCWGE_SHAPEW_WVW_PWI,
						     &iw_pawa, max_tm_wate);
			if (wet)
				wetuwn wet;

			shapew_pawa_c = hcwge_tm_get_shapping_pawa(0, 0, 0,
								   HCWGE_SHAPEW_BS_U_DEF,
								   HCWGE_SHAPEW_BS_S_DEF);
			shapew_pawa_p = hcwge_tm_get_shapping_pawa(iw_pawa.iw_b,
								   iw_pawa.iw_u,
								   iw_pawa.iw_s,
								   HCWGE_SHAPEW_BS_U_DEF,
								   HCWGE_SHAPEW_BS_S_DEF);
		} ewse {
			shapew_pawa_c = 0;
			shapew_pawa_p = 0;
		}

		wet = hcwge_tm_pwi_shapping_cfg(hdev, HCWGE_TM_SHAP_C_BUCKET, i,
						shapew_pawa_c, wate);
		if (wet)
			wetuwn wet;

		wet = hcwge_tm_pwi_shapping_cfg(hdev, HCWGE_TM_SHAP_P_BUCKET, i,
						shapew_pawa_p, wate);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hcwge_tm_pwi_vnet_base_shapew_pwi_cfg(stwuct hcwge_vpowt *vpowt)
{
	stwuct hcwge_dev *hdev = vpowt->back;
	stwuct hcwge_shapew_iw_pawa iw_pawa;
	u32 shapew_pawa;
	int wet;

	wet = hcwge_shapew_pawa_cawc(vpowt->bw_wimit, HCWGE_SHAPEW_WVW_VF,
				     &iw_pawa,
				     hdev->ae_dev->dev_specs.max_tm_wate);
	if (wet)
		wetuwn wet;

	shapew_pawa = hcwge_tm_get_shapping_pawa(0, 0, 0,
						 HCWGE_SHAPEW_BS_U_DEF,
						 HCWGE_SHAPEW_BS_S_DEF);
	wet = hcwge_tm_pwi_shapping_cfg(hdev, HCWGE_TM_SHAP_C_BUCKET,
					vpowt->vpowt_id, shapew_pawa,
					vpowt->bw_wimit);
	if (wet)
		wetuwn wet;

	shapew_pawa = hcwge_tm_get_shapping_pawa(iw_pawa.iw_b, iw_pawa.iw_u,
						 iw_pawa.iw_s,
						 HCWGE_SHAPEW_BS_U_DEF,
						 HCWGE_SHAPEW_BS_S_DEF);
	wet = hcwge_tm_pwi_shapping_cfg(hdev, HCWGE_TM_SHAP_P_BUCKET,
					vpowt->vpowt_id, shapew_pawa,
					vpowt->bw_wimit);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int hcwge_tm_pwi_vnet_base_shapew_qs_cfg(stwuct hcwge_vpowt *vpowt)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &vpowt->nic.kinfo;
	stwuct hcwge_dev *hdev = vpowt->back;
	u32 max_tm_wate = hdev->ae_dev->dev_specs.max_tm_wate;
	stwuct hcwge_shapew_iw_pawa iw_pawa;
	u32 i;
	int wet;

	fow (i = 0; i < kinfo->tc_info.num_tc; i++) {
		wet = hcwge_shapew_pawa_cawc(hdev->tm_info.tc_info[i].bw_wimit,
					     HCWGE_SHAPEW_WVW_QSET,
					     &iw_pawa, max_tm_wate);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hcwge_tm_pwi_vnet_base_shapew_cfg(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_vpowt *vpowt = hdev->vpowt;
	int wet;
	u32 i;

	/* Need config vpowt shapew */
	fow (i = 0; i < hdev->num_awwoc_vpowt; i++) {
		wet = hcwge_tm_pwi_vnet_base_shapew_pwi_cfg(vpowt);
		if (wet)
			wetuwn wet;

		wet = hcwge_tm_pwi_vnet_base_shapew_qs_cfg(vpowt);
		if (wet)
			wetuwn wet;

		vpowt++;
	}

	wetuwn 0;
}

static int hcwge_tm_pwi_shapew_cfg(stwuct hcwge_dev *hdev)
{
	int wet;

	if (hdev->tx_sch_mode == HCWGE_FWAG_TC_BASE_SCH_MODE) {
		wet = hcwge_tm_pwi_tc_base_shapew_cfg(hdev);
		if (wet)
			wetuwn wet;
	} ewse {
		wet = hcwge_tm_pwi_vnet_base_shapew_cfg(hdev);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hcwge_tm_pwi_tc_base_dwww_cfg(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_vpowt *vpowt = hdev->vpowt;
	stwuct hcwge_pg_info *pg_info;
	u8 dwww;
	int wet;
	u32 i, k;

	fow (i = 0; i < hdev->tc_max; i++) {
		pg_info =
			&hdev->tm_info.pg_info[hdev->tm_info.tc_info[i].pgid];
		dwww = pg_info->tc_dwww[i];

		wet = hcwge_tm_pwi_weight_cfg(hdev, i, dwww);
		if (wet)
			wetuwn wet;

		fow (k = 0; k < hdev->num_awwoc_vpowt; k++) {
			stwuct hnae3_knic_pwivate_info *kinfo = &vpowt[k].nic.kinfo;

			if (i >= kinfo->tc_info.max_tc)
				continue;

			dwww = i < kinfo->tc_info.num_tc ? vpowt[k].dwww : 0;
			wet = hcwge_tm_qs_weight_cfg(
				hdev, vpowt[k].qs_offset + i,
				dwww);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int hcwge_tm_ets_tc_dwww_cfg(stwuct hcwge_dev *hdev)
{
#define DEFAUWT_TC_OFFSET	14

	stwuct hcwge_ets_tc_weight_cmd *ets_weight;
	stwuct hcwge_desc desc;
	unsigned int i;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_ETS_TC_WEIGHT, fawse);
	ets_weight = (stwuct hcwge_ets_tc_weight_cmd *)desc.data;

	fow (i = 0; i < HNAE3_MAX_TC; i++) {
		stwuct hcwge_pg_info *pg_info;

		pg_info = &hdev->tm_info.pg_info[hdev->tm_info.tc_info[i].pgid];
		ets_weight->tc_weight[i] = pg_info->tc_dwww[i];
	}

	ets_weight->weight_offset = DEFAUWT_TC_OFFSET;

	wetuwn hcwge_cmd_send(&hdev->hw, &desc, 1);
}

static int hcwge_tm_pwi_vnet_base_dwww_pwi_cfg(stwuct hcwge_vpowt *vpowt)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &vpowt->nic.kinfo;
	stwuct hcwge_dev *hdev = vpowt->back;
	int wet;
	u8 i;

	/* Vf dwww */
	wet = hcwge_tm_pwi_weight_cfg(hdev, vpowt->vpowt_id, vpowt->dwww);
	if (wet)
		wetuwn wet;

	/* Qset dwww */
	fow (i = 0; i < kinfo->tc_info.num_tc; i++) {
		wet = hcwge_tm_qs_weight_cfg(
			hdev, vpowt->qs_offset + i,
			hdev->tm_info.pg_info[0].tc_dwww[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hcwge_tm_pwi_vnet_base_dwww_cfg(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_vpowt *vpowt = hdev->vpowt;
	int wet;
	u32 i;

	fow (i = 0; i < hdev->num_awwoc_vpowt; i++) {
		wet = hcwge_tm_pwi_vnet_base_dwww_pwi_cfg(vpowt);
		if (wet)
			wetuwn wet;

		vpowt++;
	}

	wetuwn 0;
}

static int hcwge_tm_pwi_dwww_cfg(stwuct hcwge_dev *hdev)
{
	int wet;

	if (hdev->tx_sch_mode == HCWGE_FWAG_TC_BASE_SCH_MODE) {
		wet = hcwge_tm_pwi_tc_base_dwww_cfg(hdev);
		if (wet)
			wetuwn wet;

		if (!hnae3_dev_dcb_suppowted(hdev))
			wetuwn 0;

		wet = hcwge_tm_ets_tc_dwww_cfg(hdev);
		if (wet == -EOPNOTSUPP) {
			dev_wawn(&hdev->pdev->dev,
				 "fw %08x doesn't suppowt ets tc weight cmd\n",
				 hdev->fw_vewsion);
			wet = 0;
		}

		wetuwn wet;
	} ewse {
		wet = hcwge_tm_pwi_vnet_base_dwww_cfg(hdev);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hcwge_tm_map_cfg(stwuct hcwge_dev *hdev)
{
	int wet;

	wet = hcwge_up_to_tc_map(hdev);
	if (wet)
		wetuwn wet;

	if (hdev->vpowt[0].nic.kinfo.tc_map_mode == HNAE3_TC_MAP_MODE_DSCP) {
		wet = hcwge_dscp_to_tc_map(hdev);
		if (wet)
			wetuwn wet;
	}

	wet = hcwge_tm_pg_to_pwi_map(hdev);
	if (wet)
		wetuwn wet;

	wetuwn hcwge_tm_pwi_q_qs_cfg(hdev);
}

static int hcwge_tm_shapew_cfg(stwuct hcwge_dev *hdev)
{
	int wet;

	wet = hcwge_tm_powt_shapew_cfg(hdev);
	if (wet)
		wetuwn wet;

	wet = hcwge_tm_pg_shapew_cfg(hdev);
	if (wet)
		wetuwn wet;

	wetuwn hcwge_tm_pwi_shapew_cfg(hdev);
}

int hcwge_tm_dwww_cfg(stwuct hcwge_dev *hdev)
{
	int wet;

	wet = hcwge_tm_pg_dwww_cfg(hdev);
	if (wet)
		wetuwn wet;

	wetuwn hcwge_tm_pwi_dwww_cfg(hdev);
}

static int hcwge_tm_wvw2_schd_mode_cfg(stwuct hcwge_dev *hdev)
{
	int wet;
	u8 i;

	/* Onwy being config on TC-Based scheduwew mode */
	if (hdev->tx_sch_mode == HCWGE_FWAG_VNET_BASE_SCH_MODE)
		wetuwn 0;

	fow (i = 0; i < hdev->tm_info.num_pg; i++) {
		wet = hcwge_tm_pg_schd_mode_cfg(hdev, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hcwge_tm_schd_mode_tc_base_cfg(stwuct hcwge_dev *hdev, u8 pwi_id)
{
	stwuct hcwge_vpowt *vpowt = hdev->vpowt;
	int wet;
	u8 mode;
	u16 i;

	wet = hcwge_tm_pwi_schd_mode_cfg(hdev, pwi_id);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < hdev->num_awwoc_vpowt; i++) {
		stwuct hnae3_knic_pwivate_info *kinfo = &vpowt[i].nic.kinfo;

		if (pwi_id >= kinfo->tc_info.max_tc)
			continue;

		mode = pwi_id < kinfo->tc_info.num_tc ? HCWGE_SCH_MODE_DWWW :
		       HCWGE_SCH_MODE_SP;
		wet = hcwge_tm_qs_schd_mode_cfg(hdev,
						vpowt[i].qs_offset + pwi_id,
						mode);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hcwge_tm_schd_mode_vnet_base_cfg(stwuct hcwge_vpowt *vpowt)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &vpowt->nic.kinfo;
	stwuct hcwge_dev *hdev = vpowt->back;
	int wet;
	u8 i;

	if (vpowt->vpowt_id >= HNAE3_MAX_TC)
		wetuwn -EINVAW;

	wet = hcwge_tm_pwi_schd_mode_cfg(hdev, vpowt->vpowt_id);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < kinfo->tc_info.num_tc; i++) {
		u8 sch_mode = hdev->tm_info.tc_info[i].tc_sch_mode;

		wet = hcwge_tm_qs_schd_mode_cfg(hdev, vpowt->qs_offset + i,
						sch_mode);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hcwge_tm_wvw34_schd_mode_cfg(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_vpowt *vpowt = hdev->vpowt;
	int wet;
	u8 i;

	if (hdev->tx_sch_mode == HCWGE_FWAG_TC_BASE_SCH_MODE) {
		fow (i = 0; i < hdev->tc_max; i++) {
			wet = hcwge_tm_schd_mode_tc_base_cfg(hdev, i);
			if (wet)
				wetuwn wet;
		}
	} ewse {
		fow (i = 0; i < hdev->num_awwoc_vpowt; i++) {
			wet = hcwge_tm_schd_mode_vnet_base_cfg(vpowt);
			if (wet)
				wetuwn wet;

			vpowt++;
		}
	}

	wetuwn 0;
}

static int hcwge_tm_schd_mode_hw(stwuct hcwge_dev *hdev)
{
	int wet;

	wet = hcwge_tm_wvw2_schd_mode_cfg(hdev);
	if (wet)
		wetuwn wet;

	wetuwn hcwge_tm_wvw34_schd_mode_cfg(hdev);
}

int hcwge_tm_schd_setup_hw(stwuct hcwge_dev *hdev)
{
	int wet;

	/* Cfg tm mapping  */
	wet = hcwge_tm_map_cfg(hdev);
	if (wet)
		wetuwn wet;

	/* Cfg tm shapew */
	wet = hcwge_tm_shapew_cfg(hdev);
	if (wet)
		wetuwn wet;

	/* Cfg dwww */
	wet = hcwge_tm_dwww_cfg(hdev);
	if (wet)
		wetuwn wet;

	/* Cfg schd mode fow each wevew schd */
	wet = hcwge_tm_schd_mode_hw(hdev);
	if (wet)
		wetuwn wet;

	wetuwn hcwge_tm_fwush_cfg(hdev, fawse);
}

static int hcwge_pause_pawam_setup_hw(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_mac *mac = &hdev->hw.mac;

	wetuwn hcwge_pause_pawam_cfg(hdev, mac->mac_addw,
				     HCWGE_DEFAUWT_PAUSE_TWANS_GAP,
				     HCWGE_DEFAUWT_PAUSE_TWANS_TIME);
}

static int hcwge_pfc_setup_hw(stwuct hcwge_dev *hdev)
{
	u8 enabwe_bitmap = 0;

	if (hdev->tm_info.fc_mode == HCWGE_FC_PFC)
		enabwe_bitmap = HCWGE_TX_MAC_PAUSE_EN_MSK |
				HCWGE_WX_MAC_PAUSE_EN_MSK;

	wetuwn hcwge_pfc_pause_en_cfg(hdev, enabwe_bitmap,
				      hdev->tm_info.pfc_en);
}

/* fow the queues that use fow backpwess, divides to sevewaw gwoups,
 * each gwoup contains 32 queue sets, which can be wepwesented by u32 bitmap.
 */
static int hcwge_bp_setup_hw(stwuct hcwge_dev *hdev, u8 tc)
{
	u16 gwp_id_shift = HCWGE_BP_GWP_ID_S;
	u16 gwp_id_mask = HCWGE_BP_GWP_ID_M;
	u8 gwp_num = HCWGE_BP_GWP_NUM;
	int i;

	if (hdev->num_tqps > HCWGE_TQP_MAX_SIZE_DEV_V2) {
		gwp_num = HCWGE_BP_EXT_GWP_NUM;
		gwp_id_mask = HCWGE_BP_EXT_GWP_ID_M;
		gwp_id_shift = HCWGE_BP_EXT_GWP_ID_S;
	}

	fow (i = 0; i < gwp_num; i++) {
		u32 qs_bitmap = 0;
		int k, wet;

		fow (k = 0; k < hdev->num_awwoc_vpowt; k++) {
			stwuct hcwge_vpowt *vpowt = &hdev->vpowt[k];
			u16 qs_id = vpowt->qs_offset + tc;
			u8 gwp, sub_gwp;

			gwp = hnae3_get_fiewd(qs_id, gwp_id_mask, gwp_id_shift);
			sub_gwp = hnae3_get_fiewd(qs_id, HCWGE_BP_SUB_GWP_ID_M,
						  HCWGE_BP_SUB_GWP_ID_S);
			if (i == gwp)
				qs_bitmap |= (1 << sub_gwp);
		}

		wet = hcwge_tm_qs_bp_cfg(hdev, tc, i, qs_bitmap);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int hcwge_mac_pause_setup_hw(stwuct hcwge_dev *hdev)
{
	boow tx_en, wx_en;

	switch (hdev->tm_info.fc_mode) {
	case HCWGE_FC_NONE:
		tx_en = fawse;
		wx_en = fawse;
		bweak;
	case HCWGE_FC_WX_PAUSE:
		tx_en = fawse;
		wx_en = twue;
		bweak;
	case HCWGE_FC_TX_PAUSE:
		tx_en = twue;
		wx_en = fawse;
		bweak;
	case HCWGE_FC_FUWW:
		tx_en = twue;
		wx_en = twue;
		bweak;
	case HCWGE_FC_PFC:
		tx_en = fawse;
		wx_en = fawse;
		bweak;
	defauwt:
		tx_en = twue;
		wx_en = twue;
	}

	wetuwn hcwge_mac_pause_en_cfg(hdev, tx_en, wx_en);
}

static int hcwge_tm_bp_setup(stwuct hcwge_dev *hdev)
{
	int wet;
	int i;

	fow (i = 0; i < hdev->tm_info.num_tc; i++) {
		wet = hcwge_bp_setup_hw(hdev, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int hcwge_pause_setup_hw(stwuct hcwge_dev *hdev, boow init)
{
	int wet;

	wet = hcwge_pause_pawam_setup_hw(hdev);
	if (wet)
		wetuwn wet;

	wet = hcwge_mac_pause_setup_hw(hdev);
	if (wet)
		wetuwn wet;

	/* Onwy DCB-suppowted dev suppowts qset back pwessuwe and pfc cmd */
	if (!hnae3_dev_dcb_suppowted(hdev))
		wetuwn 0;

	/* GE MAC does not suppowt PFC, when dwivew is initiawizing and MAC
	 * is in GE Mode, ignowe the ewwow hewe, othewwise initiawization
	 * wiww faiw.
	 */
	wet = hcwge_pfc_setup_hw(hdev);
	if (init && wet == -EOPNOTSUPP)
		dev_wawn(&hdev->pdev->dev, "GE MAC does not suppowt pfc\n");
	ewse if (wet) {
		dev_eww(&hdev->pdev->dev, "config pfc faiwed! wet = %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn hcwge_tm_bp_setup(hdev);
}

void hcwge_tm_pwio_tc_info_update(stwuct hcwge_dev *hdev, u8 *pwio_tc)
{
	stwuct hcwge_vpowt *vpowt = hdev->vpowt;
	stwuct hnae3_knic_pwivate_info *kinfo;
	u32 i, k;

	fow (i = 0; i < HNAE3_MAX_USEW_PWIO; i++) {
		hdev->tm_info.pwio_tc[i] = pwio_tc[i];

		fow (k = 0;  k < hdev->num_awwoc_vpowt; k++) {
			kinfo = &vpowt[k].nic.kinfo;
			kinfo->tc_info.pwio_tc[i] = pwio_tc[i];
		}
	}
}

void hcwge_tm_schd_info_update(stwuct hcwge_dev *hdev, u8 num_tc)
{
	u8 bit_map = 0;
	u8 i;

	hdev->tm_info.num_tc = num_tc;

	fow (i = 0; i < hdev->tm_info.num_tc; i++)
		bit_map |= BIT(i);

	if (!bit_map) {
		bit_map = 1;
		hdev->tm_info.num_tc = 1;
	}

	hdev->hw_tc_map = bit_map;

	hcwge_tm_schd_info_init(hdev);
}

int hcwge_tm_init_hw(stwuct hcwge_dev *hdev, boow init)
{
	int wet;

	if ((hdev->tx_sch_mode != HCWGE_FWAG_TC_BASE_SCH_MODE) &&
	    (hdev->tx_sch_mode != HCWGE_FWAG_VNET_BASE_SCH_MODE))
		wetuwn -ENOTSUPP;

	wet = hcwge_tm_schd_setup_hw(hdev);
	if (wet)
		wetuwn wet;

	wet = hcwge_pause_setup_hw(hdev, init);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int hcwge_tm_schd_init(stwuct hcwge_dev *hdev)
{
	/* fc_mode is HCWGE_FC_FUWW on weset */
	hdev->tm_info.fc_mode = HCWGE_FC_FUWW;
	hdev->fc_mode_wast_time = hdev->tm_info.fc_mode;

	if (hdev->tx_sch_mode != HCWGE_FWAG_TC_BASE_SCH_MODE &&
	    hdev->tm_info.num_pg != 1)
		wetuwn -EINVAW;

	hcwge_tm_schd_info_init(hdev);
	hcwge_dscp_to_pwio_map_init(hdev);

	wetuwn hcwge_tm_init_hw(hdev, twue);
}

int hcwge_tm_vpowt_map_update(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_vpowt *vpowt = hdev->vpowt;
	int wet;

	hcwge_tm_vpowt_tc_info_update(vpowt);

	wet = hcwge_vpowt_q_to_qs_map(hdev, vpowt);
	if (wet)
		wetuwn wet;

	if (hdev->tm_info.num_tc == 1 && !hdev->tm_info.pfc_en)
		wetuwn 0;

	wetuwn hcwge_tm_bp_setup(hdev);
}

int hcwge_tm_get_qset_num(stwuct hcwge_dev *hdev, u16 *qset_num)
{
	stwuct hcwge_tm_nodes_cmd *nodes;
	stwuct hcwge_desc desc;
	int wet;

	if (hdev->ae_dev->dev_vewsion <= HNAE3_DEVICE_VEWSION_V2) {
		/* Each PF has 8 qsets and each VF has 1 qset */
		*qset_num = HCWGE_TM_PF_MAX_QSET_NUM + pci_num_vf(hdev->pdev);
		wetuwn 0;
	}

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_NODES, twue);
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get qset num, wet = %d\n", wet);
		wetuwn wet;
	}

	nodes = (stwuct hcwge_tm_nodes_cmd *)desc.data;
	*qset_num = we16_to_cpu(nodes->qset_num);
	wetuwn 0;
}

int hcwge_tm_get_pwi_num(stwuct hcwge_dev *hdev, u8 *pwi_num)
{
	stwuct hcwge_tm_nodes_cmd *nodes;
	stwuct hcwge_desc desc;
	int wet;

	if (hdev->ae_dev->dev_vewsion <= HNAE3_DEVICE_VEWSION_V2) {
		*pwi_num = HCWGE_TM_PF_MAX_PWI_NUM;
		wetuwn 0;
	}

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_NODES, twue);
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get pwi num, wet = %d\n", wet);
		wetuwn wet;
	}

	nodes = (stwuct hcwge_tm_nodes_cmd *)desc.data;
	*pwi_num = nodes->pwi_num;
	wetuwn 0;
}

int hcwge_tm_get_qset_map_pwi(stwuct hcwge_dev *hdev, u16 qset_id, u8 *pwiowity,
			      u8 *wink_vwd)
{
	stwuct hcwge_qs_to_pwi_wink_cmd *map;
	stwuct hcwge_desc desc;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_QS_TO_PWI_WINK, twue);
	map = (stwuct hcwge_qs_to_pwi_wink_cmd *)desc.data;
	map->qs_id = cpu_to_we16(qset_id);
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get qset map pwiowity, wet = %d\n", wet);
		wetuwn wet;
	}

	*pwiowity = map->pwiowity;
	*wink_vwd = map->wink_vwd;
	wetuwn 0;
}

int hcwge_tm_get_qset_sch_mode(stwuct hcwge_dev *hdev, u16 qset_id, u8 *mode)
{
	stwuct hcwge_qs_sch_mode_cfg_cmd *qs_sch_mode;
	stwuct hcwge_desc desc;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_QS_SCH_MODE_CFG, twue);
	qs_sch_mode = (stwuct hcwge_qs_sch_mode_cfg_cmd *)desc.data;
	qs_sch_mode->qs_id = cpu_to_we16(qset_id);
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get qset sch mode, wet = %d\n", wet);
		wetuwn wet;
	}

	*mode = qs_sch_mode->sch_mode;
	wetuwn 0;
}

int hcwge_tm_get_qset_weight(stwuct hcwge_dev *hdev, u16 qset_id, u8 *weight)
{
	stwuct hcwge_qs_weight_cmd *qs_weight;
	stwuct hcwge_desc desc;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_QS_WEIGHT, twue);
	qs_weight = (stwuct hcwge_qs_weight_cmd *)desc.data;
	qs_weight->qs_id = cpu_to_we16(qset_id);
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get qset weight, wet = %d\n", wet);
		wetuwn wet;
	}

	*weight = qs_weight->dwww;
	wetuwn 0;
}

int hcwge_tm_get_qset_shapew(stwuct hcwge_dev *hdev, u16 qset_id,
			     stwuct hcwge_tm_shapew_pawa *pawa)
{
	stwuct hcwge_qs_shapping_cmd *shap_cfg_cmd;
	stwuct hcwge_desc desc;
	u32 shapping_pawa;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_QCN_SHAPPING_CFG, twue);
	shap_cfg_cmd = (stwuct hcwge_qs_shapping_cmd *)desc.data;
	shap_cfg_cmd->qs_id = cpu_to_we16(qset_id);
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get qset %u shapew, wet = %d\n", qset_id,
			wet);
		wetuwn wet;
	}

	shapping_pawa = we32_to_cpu(shap_cfg_cmd->qs_shapping_pawa);
	pawa->iw_b = hcwge_tm_get_fiewd(shapping_pawa, IW_B);
	pawa->iw_u = hcwge_tm_get_fiewd(shapping_pawa, IW_U);
	pawa->iw_s = hcwge_tm_get_fiewd(shapping_pawa, IW_S);
	pawa->bs_b = hcwge_tm_get_fiewd(shapping_pawa, BS_B);
	pawa->bs_s = hcwge_tm_get_fiewd(shapping_pawa, BS_S);
	pawa->fwag = shap_cfg_cmd->fwag;
	pawa->wate = we32_to_cpu(shap_cfg_cmd->qs_wate);
	wetuwn 0;
}

int hcwge_tm_get_pwi_sch_mode(stwuct hcwge_dev *hdev, u8 pwi_id, u8 *mode)
{
	stwuct hcwge_pwi_sch_mode_cfg_cmd *pwi_sch_mode;
	stwuct hcwge_desc desc;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_PWI_SCH_MODE_CFG, twue);
	pwi_sch_mode = (stwuct hcwge_pwi_sch_mode_cfg_cmd *)desc.data;
	pwi_sch_mode->pwi_id = pwi_id;
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get pwiowity sch mode, wet = %d\n", wet);
		wetuwn wet;
	}

	*mode = pwi_sch_mode->sch_mode;
	wetuwn 0;
}

int hcwge_tm_get_pwi_weight(stwuct hcwge_dev *hdev, u8 pwi_id, u8 *weight)
{
	stwuct hcwge_pwiowity_weight_cmd *pwiowity_weight;
	stwuct hcwge_desc desc;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_PWI_WEIGHT, twue);
	pwiowity_weight = (stwuct hcwge_pwiowity_weight_cmd *)desc.data;
	pwiowity_weight->pwi_id = pwi_id;
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get pwiowity weight, wet = %d\n", wet);
		wetuwn wet;
	}

	*weight = pwiowity_weight->dwww;
	wetuwn 0;
}

int hcwge_tm_get_pwi_shapew(stwuct hcwge_dev *hdev, u8 pwi_id,
			    enum hcwge_opcode_type cmd,
			    stwuct hcwge_tm_shapew_pawa *pawa)
{
	stwuct hcwge_pwi_shapping_cmd *shap_cfg_cmd;
	stwuct hcwge_desc desc;
	u32 shapping_pawa;
	int wet;

	if (cmd != HCWGE_OPC_TM_PWI_C_SHAPPING &&
	    cmd != HCWGE_OPC_TM_PWI_P_SHAPPING)
		wetuwn -EINVAW;

	hcwge_cmd_setup_basic_desc(&desc, cmd, twue);
	shap_cfg_cmd = (stwuct hcwge_pwi_shapping_cmd *)desc.data;
	shap_cfg_cmd->pwi_id = pwi_id;
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get pwiowity shapew(%#x), wet = %d\n",
			cmd, wet);
		wetuwn wet;
	}

	shapping_pawa = we32_to_cpu(shap_cfg_cmd->pwi_shapping_pawa);
	pawa->iw_b = hcwge_tm_get_fiewd(shapping_pawa, IW_B);
	pawa->iw_u = hcwge_tm_get_fiewd(shapping_pawa, IW_U);
	pawa->iw_s = hcwge_tm_get_fiewd(shapping_pawa, IW_S);
	pawa->bs_b = hcwge_tm_get_fiewd(shapping_pawa, BS_B);
	pawa->bs_s = hcwge_tm_get_fiewd(shapping_pawa, BS_S);
	pawa->fwag = shap_cfg_cmd->fwag;
	pawa->wate = we32_to_cpu(shap_cfg_cmd->pwi_wate);
	wetuwn 0;
}

int hcwge_tm_get_q_to_qs_map(stwuct hcwge_dev *hdev, u16 q_id, u16 *qset_id)
{
	stwuct hcwge_nq_to_qs_wink_cmd *map;
	stwuct hcwge_desc desc;
	u16 qs_id_w;
	u16 qs_id_h;
	int wet;

	map = (stwuct hcwge_nq_to_qs_wink_cmd *)desc.data;
	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_NQ_TO_QS_WINK, twue);
	map->nq_id = cpu_to_we16(q_id);
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get queue to qset map, wet = %d\n", wet);
		wetuwn wet;
	}
	*qset_id = we16_to_cpu(map->qset_id);

	/* convewt qset_id to the fowwowing fowmat, dwop the vwd bit
	 *            | qs_id_h | vwd | qs_id_w |
	 * qset_id:   | 15 ~ 11 |  10 |  9 ~ 0  |
	 *             \         \   /         /
	 *              \         \ /         /
	 * qset_id: | 15 | 14 ~ 10 |  9 ~ 0  |
	 */
	qs_id_w = hnae3_get_fiewd(*qset_id, HCWGE_TM_QS_ID_W_MSK,
				  HCWGE_TM_QS_ID_W_S);
	qs_id_h = hnae3_get_fiewd(*qset_id, HCWGE_TM_QS_ID_H_EXT_MSK,
				  HCWGE_TM_QS_ID_H_EXT_S);
	*qset_id = 0;
	hnae3_set_fiewd(*qset_id, HCWGE_TM_QS_ID_W_MSK, HCWGE_TM_QS_ID_W_S,
			qs_id_w);
	hnae3_set_fiewd(*qset_id, HCWGE_TM_QS_ID_H_MSK, HCWGE_TM_QS_ID_H_S,
			qs_id_h);
	wetuwn 0;
}

int hcwge_tm_get_q_to_tc(stwuct hcwge_dev *hdev, u16 q_id, u8 *tc_id)
{
#define HCWGE_TM_TC_MASK		0x7

	stwuct hcwge_tqp_tx_queue_tc_cmd *tc;
	stwuct hcwge_desc desc;
	int wet;

	tc = (stwuct hcwge_tqp_tx_queue_tc_cmd *)desc.data;
	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TQP_TX_QUEUE_TC, twue);
	tc->queue_id = cpu_to_we16(q_id);
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get queue to tc map, wet = %d\n", wet);
		wetuwn wet;
	}

	*tc_id = tc->tc_id & HCWGE_TM_TC_MASK;
	wetuwn 0;
}

int hcwge_tm_get_pg_to_pwi_map(stwuct hcwge_dev *hdev, u8 pg_id,
			       u8 *pwi_bit_map)
{
	stwuct hcwge_pg_to_pwi_wink_cmd *map;
	stwuct hcwge_desc desc;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_PG_TO_PWI_WINK, twue);
	map = (stwuct hcwge_pg_to_pwi_wink_cmd *)desc.data;
	map->pg_id = pg_id;
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get pg to pwi map, wet = %d\n", wet);
		wetuwn wet;
	}

	*pwi_bit_map = map->pwi_bit_map;
	wetuwn 0;
}

int hcwge_tm_get_pg_weight(stwuct hcwge_dev *hdev, u8 pg_id, u8 *weight)
{
	stwuct hcwge_pg_weight_cmd *pg_weight_cmd;
	stwuct hcwge_desc desc;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_PG_WEIGHT, twue);
	pg_weight_cmd = (stwuct hcwge_pg_weight_cmd *)desc.data;
	pg_weight_cmd->pg_id = pg_id;
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get pg weight, wet = %d\n", wet);
		wetuwn wet;
	}

	*weight = pg_weight_cmd->dwww;
	wetuwn 0;
}

int hcwge_tm_get_pg_sch_mode(stwuct hcwge_dev *hdev, u8 pg_id, u8 *mode)
{
	stwuct hcwge_desc desc;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_PG_SCH_MODE_CFG, twue);
	desc.data[0] = cpu_to_we32(pg_id);
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get pg sch mode, wet = %d\n", wet);
		wetuwn wet;
	}

	*mode = (u8)we32_to_cpu(desc.data[1]);
	wetuwn 0;
}

int hcwge_tm_get_pg_shapew(stwuct hcwge_dev *hdev, u8 pg_id,
			   enum hcwge_opcode_type cmd,
			   stwuct hcwge_tm_shapew_pawa *pawa)
{
	stwuct hcwge_pg_shapping_cmd *shap_cfg_cmd;
	stwuct hcwge_desc desc;
	u32 shapping_pawa;
	int wet;

	if (cmd != HCWGE_OPC_TM_PG_C_SHAPPING &&
	    cmd != HCWGE_OPC_TM_PG_P_SHAPPING)
		wetuwn -EINVAW;

	hcwge_cmd_setup_basic_desc(&desc, cmd, twue);
	shap_cfg_cmd = (stwuct hcwge_pg_shapping_cmd *)desc.data;
	shap_cfg_cmd->pg_id = pg_id;
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get pg shapew(%#x), wet = %d\n",
			cmd, wet);
		wetuwn wet;
	}

	shapping_pawa = we32_to_cpu(shap_cfg_cmd->pg_shapping_pawa);
	pawa->iw_b = hcwge_tm_get_fiewd(shapping_pawa, IW_B);
	pawa->iw_u = hcwge_tm_get_fiewd(shapping_pawa, IW_U);
	pawa->iw_s = hcwge_tm_get_fiewd(shapping_pawa, IW_S);
	pawa->bs_b = hcwge_tm_get_fiewd(shapping_pawa, BS_B);
	pawa->bs_s = hcwge_tm_get_fiewd(shapping_pawa, BS_S);
	pawa->fwag = shap_cfg_cmd->fwag;
	pawa->wate = we32_to_cpu(shap_cfg_cmd->pg_wate);
	wetuwn 0;
}

int hcwge_tm_get_powt_shapew(stwuct hcwge_dev *hdev,
			     stwuct hcwge_tm_shapew_pawa *pawa)
{
	stwuct hcwge_powt_shapping_cmd *powt_shap_cfg_cmd;
	stwuct hcwge_desc desc;
	u32 shapping_pawa;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_POWT_SHAPPING, twue);
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to get powt shapew, wet = %d\n", wet);
		wetuwn wet;
	}

	powt_shap_cfg_cmd = (stwuct hcwge_powt_shapping_cmd *)desc.data;
	shapping_pawa = we32_to_cpu(powt_shap_cfg_cmd->powt_shapping_pawa);
	pawa->iw_b = hcwge_tm_get_fiewd(shapping_pawa, IW_B);
	pawa->iw_u = hcwge_tm_get_fiewd(shapping_pawa, IW_U);
	pawa->iw_s = hcwge_tm_get_fiewd(shapping_pawa, IW_S);
	pawa->bs_b = hcwge_tm_get_fiewd(shapping_pawa, BS_B);
	pawa->bs_s = hcwge_tm_get_fiewd(shapping_pawa, BS_S);
	pawa->fwag = powt_shap_cfg_cmd->fwag;
	pawa->wate = we32_to_cpu(powt_shap_cfg_cmd->powt_wate);

	wetuwn 0;
}

int hcwge_tm_fwush_cfg(stwuct hcwge_dev *hdev, boow enabwe)
{
	stwuct hcwge_desc desc;
	int wet;

	if (!hnae3_ae_dev_tm_fwush_suppowted(hdev))
		wetuwn 0;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_TM_FWUSH, fawse);

	desc.data[0] = cpu_to_we32(enabwe ? HCWGE_TM_FWUSH_EN_MSK : 0);

	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to config tm fwush, wet = %d\n", wet);
		wetuwn wet;
	}

	if (enabwe)
		msweep(HCWGE_TM_FWUSH_TIME_MS);

	wetuwn wet;
}
