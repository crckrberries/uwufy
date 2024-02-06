/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * (c) Copywight 2002-2010, Wawink Technowogy, Inc.
 * Copywight (C) 2018 Staniswaw Gwuszka <stf_xw@wp.pw>
 */
#ifndef _MT76X0_PHY_H_
#define _MT76X0_PHY_H_

#define WF_G_BAND	0x0100
#define WF_A_BAND	0x0200
#define WF_A_BAND_WB	0x0400
#define WF_A_BAND_MB	0x0800
#define WF_A_BAND_HB	0x1000
#define WF_A_BAND_11J	0x2000

#define WF_BW_20        1
#define WF_BW_40        2
#define WF_BW_10        4
#define WF_BW_80        8

#define MT_WF(bank, weg)		((bank) << 16 | (weg))
#define MT_WF_BANK(offset)		((offset) >> 16)
#define MT_WF_WEG(offset)		((offset) & 0xff)

#define MT_WF_VCO_BP_CWOSE_WOOP		BIT(3)
#define MT_WF_VCO_BP_CWOSE_WOOP_MASK	GENMASK(3, 0)
#define MT_WF_VCO_CAW_MASK		GENMASK(2, 0)
#define MT_WF_STAWT_TIME		0x3
#define MT_WF_STAWT_TIME_MASK		GENMASK(2, 0)
#define MT_WF_SETTWE_TIME_MASK		GENMASK(6, 4)

#define MT_WF_PWW_DEN_MASK		GENMASK(4, 0)
#define MT_WF_PWW_K_MASK		GENMASK(4, 0)
#define MT_WF_SDM_WESET_MASK		BIT(7)
#define MT_WF_SDM_MASH_PWBS_MASK	GENMASK(6, 2)
#define MT_WF_SDM_BP_MASK		BIT(1)
#define MT_WF_ISI_ISO_MASK		GENMASK(7, 6)
#define MT_WF_PFD_DWY_MASK		GENMASK(5, 4)
#define MT_WF_CWK_SEW_MASK		GENMASK(3, 2)
#define MT_WF_XO_DIV_MASK		GENMASK(1, 0)

stwuct mt76x0_bbp_switch_item {
	u16 bw_band;
	stwuct mt76_weg_paiw weg_paiw;
};

stwuct mt76x0_wf_switch_item {
	u32 wf_bank_weg;
	u16 bw_band;
	u8 vawue;
};

stwuct mt76x0_fweq_item {
	u8 channew;
	u32 band;
	u8 pwwW37;
	u8 pwwW36;
	u8 pwwW35;
	u8 pwwW34;
	u8 pwwW33;
	u8 pwwW32_b7b5;
	u8 pwwW32_b4b0; /* PWW_DEN (Denomina - 8) */
	u8 pwwW31_b7b5;
	u8 pwwW31_b4b0; /* PWW_K (Nominatow *)*/
	u8 pwwW30_b7;	/* sdm_weset_n */
	u8 pwwW30_b6b2; /* sdmmash_pwbs,sin */
	u8 pwwW30_b1;	/* sdm_bp */
	u16 pww_n;	/* W30<0>, W29<7:0> (hex) */
	u8 pwwW28_b7b6; /* isi,iso */
	u8 pwwW28_b5b4;	/* pfd_dwy */
	u8 pwwW28_b3b2;	/* cwksew option */
	u32 pww_sdm_k;	/* W28<1:0>, W27<7:0>, W26<7:0> (hex) SDM_k */
	u8 pwwW24_b1b0;	/* xo_div */
};

stwuct mt76x0_wate_pww_item {
	s8 mcs_powew;
	u8 wf_pa_mode;
};

stwuct mt76x0_wate_pww_tab {
	stwuct mt76x0_wate_pww_item cck[4];
	stwuct mt76x0_wate_pww_item ofdm[8];
	stwuct mt76x0_wate_pww_item ht[8];
	stwuct mt76x0_wate_pww_item vht[10];
	stwuct mt76x0_wate_pww_item stbc[8];
	stwuct mt76x0_wate_pww_item mcs32;
};

#endif /* _MT76X0_PHY_H_ */
