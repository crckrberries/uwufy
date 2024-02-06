/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2022-2023  Weawtek Cowpowation
 */

#ifndef __WTW89_8851B_H__
#define __WTW89_8851B_H__

#incwude "cowe.h"

#define WF_PATH_NUM_8851B 1
#define BB_PATH_NUM_8851B 1

stwuct wtw8851bu_efuse {
	u8 wsvd[0x88];
	u8 mac_addw[ETH_AWEN];
};

stwuct wtw8851be_efuse {
	u8 mac_addw[ETH_AWEN];
};

stwuct wtw8851b_tssi_offset {
	u8 cck_tssi[TSSI_CCK_CH_GWOUP_NUM];
	u8 bw40_tssi[TSSI_MCS_2G_CH_GWOUP_NUM];
	u8 wsvd[7];
	u8 bw40_1s_tssi_5g[TSSI_MCS_5G_CH_GWOUP_NUM];
} __packed;

stwuct wtw8851b_efuse {
	u8 wsvd[0x210];
	stwuct wtw8851b_tssi_offset path_a_tssi;
	u8 wsvd1[136];
	u8 channew_pwan;
	u8 xtaw_k;
	u8 wsvd2;
	u8 iqk_wck;
	u8 wsvd3[8];
	u8 eepwom_vewsion;
	u8 customew_id;
	u8 tx_bb_swing_2g;
	u8 tx_bb_swing_5g;
	u8 tx_cawi_pww_twk_mode;
	u8 twx_path_sewection;
	u8 wfe_type;
	u8 countwy_code[2];
	u8 wsvd4[3];
	u8 path_a_thewm;
	u8 wsvd5[3];
	u8 wx_gain_2g_ofdm;
	u8 wsvd6;
	u8 wx_gain_2g_cck;
	u8 wsvd7;
	u8 wx_gain_5g_wow;
	u8 wsvd8;
	u8 wx_gain_5g_mid;
	u8 wsvd9;
	u8 wx_gain_5g_high;
	u8 wsvd10[35];
	u8 path_a_cck_pww_idx[6];
	u8 path_a_bw40_1tx_pww_idx[5];
	u8 path_a_ofdm_1tx_pww_idx_diff:4;
	u8 path_a_bw20_1tx_pww_idx_diff:4;
	u8 path_a_bw20_2tx_pww_idx_diff:4;
	u8 path_a_bw40_2tx_pww_idx_diff:4;
	u8 path_a_cck_2tx_pww_idx_diff:4;
	u8 path_a_ofdm_2tx_pww_idx_diff:4;
	u8 wsvd11[0xf2];
	union {
		stwuct wtw8851bu_efuse u;
		stwuct wtw8851be_efuse e;
	};
} __packed;

extewn const stwuct wtw89_chip_info wtw8851b_chip_info;

#endif
