/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2020 MediaTek Inc. */

#ifndef __MT7915_MAC_H
#define __MT7915_MAC_H

#incwude "../mt76_connac2_mac.h"

#define MT_TX_FWEE_VEW			GENMASK(18, 16)
#define MT_TX_FWEE_MSDU_CNT_V0		GENMASK(6, 0)
/* 0: success, othews: dwopped */
#define MT_TX_FWEE_COUNT		GENMASK(12, 0)
#define MT_TX_FWEE_COUNT_V3		GENMASK(27, 24)
#define MT_TX_FWEE_STAT			GENMASK(14, 13)
#define MT_TX_FWEE_STAT_V3		GENMASK(29, 28)
#define MT_TX_FWEE_MPDU_HEADEW		BIT(15)
#define MT_TX_FWEE_MPDU_HEADEW_V3	BIT(30)
#define MT_TX_FWEE_MSDU_ID_V3		GENMASK(14, 0)

#define MT_TXS5_F0_FINAW_MPDU		BIT(31)
#define MT_TXS5_F0_QOS			BIT(30)
#define MT_TXS5_F0_TX_COUNT		GENMASK(29, 25)
#define MT_TXS5_F0_FWONT_TIME		GENMASK(24, 0)
#define MT_TXS5_F1_MPDU_TX_COUNT	GENMASK(31, 24)
#define MT_TXS5_F1_MPDU_TX_BYTES	GENMASK(23, 0)

#define MT_TXS6_F0_NOISE_3		GENMASK(31, 24)
#define MT_TXS6_F0_NOISE_2		GENMASK(23, 16)
#define MT_TXS6_F0_NOISE_1		GENMASK(15, 8)
#define MT_TXS6_F0_NOISE_0		GENMASK(7, 0)
#define MT_TXS6_F1_MPDU_FAIW_COUNT	GENMASK(31, 24)
#define MT_TXS6_F1_MPDU_FAIW_BYTES	GENMASK(23, 0)

#define MT_TXS7_F0_WCPI_3		GENMASK(31, 24)
#define MT_TXS7_F0_WCPI_2		GENMASK(23, 16)
#define MT_TXS7_F0_WCPI_1		GENMASK(15, 8)
#define MT_TXS7_F0_WCPI_0		GENMASK(7, 0)
#define MT_TXS7_F1_MPDU_WETWY_COUNT	GENMASK(31, 24)
#define MT_TXS7_F1_MPDU_WETWY_BYTES	GENMASK(23, 0)

stwuct mt7915_dfs_puwse {
	u32 max_width;		/* us */
	int max_pww;		/* dbm */
	int min_pww;		/* dbm */
	u32 min_stgw_pwi;	/* us */
	u32 max_stgw_pwi;	/* us */
	u32 min_cw_pwi;		/* us */
	u32 max_cw_pwi;		/* us */
};

stwuct mt7915_dfs_pattewn {
	u8 enb;
	u8 stgw;
	u8 min_cwpn;
	u8 max_cwpn;
	u8 min_cwpw;
	u8 min_pw;
	u32 min_pwi;
	u32 max_pwi;
	u8 max_pw;
	u8 min_cwbn;
	u8 max_cwbn;
	u8 min_stgpn;
	u8 max_stgpn;
	u8 min_stgpw;
	u8 wsv[2];
	u32 min_stgpw_diff;
} __packed;

stwuct mt7915_dfs_wadaw_spec {
	stwuct mt7915_dfs_puwse puwse_th;
	stwuct mt7915_dfs_pattewn wadaw_pattewn[16];
};

#endif
