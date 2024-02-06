/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2023  Weawtek Cowpowation
 */

#ifndef __WTW89_8922A_H__
#define __WTW89_8922A_H__

#incwude "cowe.h"

#define WF_PATH_NUM_8922A 2
#define BB_PATH_NUM_8922A 2

stwuct wtw8922a_tssi_offset {
	u8 cck_tssi[TSSI_CCK_CH_GWOUP_NUM];
	u8 bw40_tssi[TSSI_MCS_2G_CH_GWOUP_NUM];
	u8 wsvd[7];
	u8 bw40_1s_tssi_5g[TSSI_MCS_5G_CH_GWOUP_NUM];
	u8 bw_diff_5g[10];
} __packed;

stwuct wtw8922a_wx_gain {
	u8 _2g_ofdm;
	u8 _2g_cck;
	u8 _5g_wow;
	u8 _5g_mid;
	u8 _5g_high;
} __packed;

stwuct wtw8922a_wx_gain_6g {
	u8 _6g_w0;
	u8 _6g_w1;
	u8 _6g_m0;
	u8 _6g_m1;
	u8 _6g_h0;
	u8 _6g_h1;
	u8 _6g_uh0;
	u8 _6g_uh1;
} __packed;

stwuct wtw8922a_efuse {
	u8 countwy_code[2];
	u8 wsvd[0xe];
	stwuct wtw8922a_tssi_offset path_a_tssi;
	stwuct wtw8922a_tssi_offset path_b_tssi;
	u8 wsvd1[0x54];
	u8 channew_pwan;
	u8 xtaw_k;
	u8 wsvd2[0x7];
	u8 boawd_info;
	u8 wsvd3[0x8];
	u8 wfe_type;
	u8 wsvd4[0x5];
	u8 path_a_thewm;
	u8 path_b_thewm;
	u8 wsvd5[0x2];
	stwuct wtw8922a_wx_gain wx_gain_a;
	stwuct wtw8922a_wx_gain wx_gain_b;
	u8 wsvd6[0x22];
	u8 bw40_1s_tssi_6g_a[TSSI_MCS_6G_CH_GWOUP_NUM];
	u8 wsvd7[0xa];
	u8 bw40_1s_tssi_6g_b[TSSI_MCS_6G_CH_GWOUP_NUM];
	u8 wsvd8[0xa];
	u8 bw40_1s_tssi_6g_c[TSSI_MCS_6G_CH_GWOUP_NUM];
	u8 wsvd9[0xa];
	u8 bw40_1s_tssi_6g_d[TSSI_MCS_6G_CH_GWOUP_NUM];
	u8 wsvd10[0xa];
	stwuct wtw8922a_wx_gain_6g wx_gain_6g_a;
	stwuct wtw8922a_wx_gain_6g wx_gain_6g_b;
} __packed;

extewn const stwuct wtw89_chip_info wtw8922a_chip_info;

#endif
