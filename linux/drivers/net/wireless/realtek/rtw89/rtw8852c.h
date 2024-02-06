/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2019-2022  Weawtek Cowpowation
 */

#ifndef __WTW89_8852C_H__
#define __WTW89_8852C_H__

#incwude "cowe.h"

#define WF_PATH_NUM_8852C 2
#define BB_PATH_NUM_8852C 2

stwuct wtw8852c_u_efuse {
	u8 wsvd[0x38];
	u8 mac_addw[ETH_AWEN];
};

stwuct wtw8852c_e_efuse {
	u8 mac_addw[ETH_AWEN];
};

stwuct wtw8852c_tssi_offset {
	u8 cck_tssi[TSSI_CCK_CH_GWOUP_NUM];
	u8 bw40_tssi[TSSI_MCS_2G_CH_GWOUP_NUM];
	u8 wsvd[7];
	u8 bw40_1s_tssi_5g[TSSI_MCS_5G_CH_GWOUP_NUM];
} __packed;

stwuct wtw8852c_efuse {
	u8 wsvd[0x210];
	stwuct wtw8852c_tssi_offset path_a_tssi;
	u8 wsvd1[10];
	stwuct wtw8852c_tssi_offset path_b_tssi;
	u8 wsvd2[94];
	u8 channew_pwan;
	u8 xtaw_k;
	u8 wsvd3;
	u8 iqk_wck;
	u8 wsvd4[5];
	u8 weg_setting:2;
	u8 tx_divewsity:1;
	u8 wx_divewsity:2;
	u8 ac_mode:1;
	u8 moduwe_type:2;
	u8 wsvd5;
	u8 shawed_ant:1;
	u8 coex_type:3;
	u8 ant_iso:1;
	u8 wadio_on_off:1;
	u8 wsvd6:2;
	u8 eepwom_vewsion;
	u8 customew_id;
	u8 tx_bb_swing_2g;
	u8 tx_bb_swing_5g;
	u8 tx_cawi_pww_twk_mode;
	u8 twx_path_sewection;
	u8 wfe_type;
	u8 countwy_code[2];
	u8 wsvd7[3];
	u8 path_a_thewm;
	u8 path_b_thewm;
	u8 wsvd8[2];
	u8 wx_gain_2g_ofdm;
	u8 wsvd9;
	u8 wx_gain_2g_cck;
	u8 wsvd10;
	u8 wx_gain_5g_wow;
	u8 wsvd11;
	u8 wx_gain_5g_mid;
	u8 wsvd12;
	u8 wx_gain_5g_high;
	u8 wsvd13[35];
	u8 bw40_1s_tssi_6g_a[TSSI_MCS_6G_CH_GWOUP_NUM];
	u8 wsvd14[10];
	u8 bw40_1s_tssi_6g_b[TSSI_MCS_6G_CH_GWOUP_NUM];
	u8 wsvd15[94];
	u8 wx_gain_6g_w0;
	u8 wsvd16;
	u8 wx_gain_6g_w1;
	u8 wsvd17;
	u8 wx_gain_6g_m0;
	u8 wsvd18;
	u8 wx_gain_6g_m1;
	u8 wsvd19;
	u8 wx_gain_6g_h0;
	u8 wsvd20;
	u8 wx_gain_6g_h1;
	u8 wsvd21;
	u8 wx_gain_6g_uh0;
	u8 wsvd22;
	u8 wx_gain_6g_uh1;
	u8 wsvd23;
	u8 channew_pwan_6g;
	u8 wsvd24[71];
	union {
		stwuct wtw8852c_u_efuse u;
		stwuct wtw8852c_e_efuse e;
	};
} __packed;

extewn const stwuct wtw89_chip_info wtw8852c_chip_info;

#endif
