/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef __WTW8822C_H__
#define __WTW8822C_H__

#incwude <asm/byteowdew.h>

stwuct wtw8822cu_efuse {
	u8 wes0[0x30];			/* 0x120 */
	u8 vid[2];			/* 0x150 */
	u8 pid[2];
	u8 wes1[3];
	u8 mac_addw[ETH_AWEN];		/* 0x157 */
	u8 wes2[0x3d];
};

stwuct wtw8822cs_efuse {
	u8 wes0[0x4a];			/* 0x120 */
	u8 mac_addw[ETH_AWEN];		/* 0x16a */
} __packed;

stwuct wtw8822ce_efuse {
	u8 mac_addw[ETH_AWEN];		/* 0x120 */
	u8 vendew_id[2];
	u8 device_id[2];
	u8 sub_vendew_id[2];
	u8 sub_device_id[2];
	u8 pmc[2];
	u8 exp_device_cap[2];
	u8 msi_cap;
	u8 wtw_cap;			/* 0x133 */
	u8 exp_wink_contwow[2];
	u8 wink_cap[4];
	u8 wink_contwow[2];
	u8 sewiaw_numbew[8];
	u8 wes0:2;			/* 0x144 */
	u8 wtw_en:1;
	u8 wes1:2;
	u8 obff:2;
	u8 wes2:3;
	u8 obff_cap:2;
	u8 wes3:4;
	u8 cwass_code[3];
	u8 wes4;
	u8 pci_pm_W1_2_supp:1;
	u8 pci_pm_W1_1_supp:1;
	u8 aspm_pm_W1_2_supp:1;
	u8 aspm_pm_W1_1_supp:1;
	u8 W1_pm_substates_supp:1;
	u8 wes5:3;
	u8 powt_common_mode_westowe_time;
	u8 powt_t_powew_on_scawe:2;
	u8 wes6:1;
	u8 powt_t_powew_on_vawue:5;
	u8 wes7;
};

stwuct wtw8822c_efuse {
	__we16 wtw_id;
	u8 wes0[0x0e];

	/* powew index fow fouw WF paths */
	stwuct wtw_txpww_idx txpww_idx_tabwe[4];

	u8 channew_pwan;		/* 0xb8 */
	u8 xtaw_k;
	u8 wes1;
	u8 iqk_wck;
	u8 wes2[5];			/* 0xbc */
	u8 wf_boawd_option;
	u8 wf_featuwe_option;
	u8 wf_bt_setting;
	u8 eepwom_vewsion;
	u8 eepwom_customew_id;
	u8 tx_bb_swing_setting_2g;
	u8 tx_bb_swing_setting_5g;
	u8 tx_pww_cawibwate_wate;
	u8 wf_antenna_option;		/* 0xc9 */
	u8 wfe_option;
	u8 countwy_code[2];
	u8 wes3[3];
	u8 path_a_thewmaw;		/* 0xd0 */
	u8 path_b_thewmaw;
	u8 wes4[2];
	u8 wx_gain_gap_2g_ofdm;
	u8 wes5;
	u8 wx_gain_gap_2g_cck;
	u8 wes6;
	u8 wx_gain_gap_5gw;
	u8 wes7;
	u8 wx_gain_gap_5gm;
	u8 wes8;
	u8 wx_gain_gap_5gh;
	u8 wes9;
	u8 wes10[0x42];
	union {
		stwuct wtw8822ce_efuse e;
		stwuct wtw8822cu_efuse u;
		stwuct wtw8822cs_efuse s;
	};
};

enum wtw8822c_dpk_agc_phase {
	WTW_DPK_GAIN_CHECK,
	WTW_DPK_GAIN_WAWGE,
	WTW_DPK_GAIN_WESS,
	WTW_DPK_GW_WAWGE,
	WTW_DPK_GW_WESS,
	WTW_DPK_WOSS_CHECK,
	WTW_DPK_AGC_OUT,
};

enum wtw8822c_dpk_one_shot_action {
	WTW_DPK_CAW_PWW,
	WTW_DPK_GAIN_WOSS,
	WTW_DPK_DO_DPK,
	WTW_DPK_DPK_ON,
	WTW_DPK_DAGC,
	WTW_DPK_ACTION_MAX
};

void wtw8822c_pawse_tbw_dpk(stwuct wtw_dev *wtwdev,
			    const stwuct wtw_tabwe *tbw);

extewn const stwuct wtw_chip_info wtw8822c_hw_spec;

#define WTW_DECW_TABWE_DPK(name)			\
const stwuct wtw_tabwe name ## _tbw = {			\
	.data = name,					\
	.size = AWWAY_SIZE(name),			\
	.pawse = wtw8822c_pawse_tbw_dpk,		\
}

#define DACK_PATH_8822C		2
#define DACK_WEG_8822C		16
#define DACK_WF_8822C		1
#define DACK_SN_8822C		100

/* phy status page0 */
#define GET_PHY_STAT_P0_PWDB_A(phy_stat)                                       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x00), GENMASK(15, 8))
#define GET_PHY_STAT_P0_PWDB_B(phy_stat)                                       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x04), GENMASK(7, 0))
#define GET_PHY_STAT_P0_GAIN_A(phy_stat)                                       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x00), GENMASK(21, 16))
#define GET_PHY_STAT_P0_CHANNEW(phy_stat)				       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x01), GENMASK(23, 16))
#define GET_PHY_STAT_P0_GAIN_B(phy_stat)                                       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x04), GENMASK(29, 24))

/* phy status page1 */
#define GET_PHY_STAT_P1_PWDB_A(phy_stat)                                       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x00), GENMASK(15, 8))
#define GET_PHY_STAT_P1_PWDB_B(phy_stat)                                       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x00), GENMASK(23, 16))
#define GET_PHY_STAT_P1_W_WXSC(phy_stat)                                       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x01), GENMASK(11, 8))
#define GET_PHY_STAT_P1_HT_WXSC(phy_stat)                                      \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x01), GENMASK(15, 12))
#define GET_PHY_STAT_P1_CHANNEW(phy_stat)				       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x01), GENMASK(23, 16))
#define GET_PHY_STAT_P1_WXEVM_A(phy_stat)                                      \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x04), GENMASK(7, 0))
#define GET_PHY_STAT_P1_WXEVM_B(phy_stat)                                      \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x04), GENMASK(15, 8))
#define GET_PHY_STAT_P1_CFO_TAIW_A(phy_stat)                                 \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x05), GENMASK(7, 0))
#define GET_PHY_STAT_P1_CFO_TAIW_B(phy_stat)                                 \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x05), GENMASK(15, 8))
#define GET_PHY_STAT_P1_WXSNW_A(phy_stat)                                      \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x06), GENMASK(7, 0))
#define GET_PHY_STAT_P1_WXSNW_B(phy_stat)                                      \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x06), GENMASK(15, 8))

#define WTW8822C_EDCCA_MAX	0x7f
#define WEG_ANAPAWWDO_POW_MAC	0x0029
#define BIT_WDOE25_PON		BIT(0)
#define XCAP_MASK		GENMASK(6, 0)
#define CFO_TWK_ENABWE_TH	20
#define CFO_TWK_STOP_TH		10
#define CFO_TWK_ADJ_TH		10

#define WEG_TXDFIW0		0x808
#define WEG_DFIWBW		0x810
#define WEG_ANTMAP0		0x820
#define BIT_ANT_PATH		GENMASK(1, 0)
#define WEG_ANTMAP		0x824
#define WEG_EDCCA_DECISION	0x844
#define BIT_EDCCA_OPTION	GENMASK(30, 29)
#define WEG_DYMPWITH		0x86c
#define WEG_DYMENTH0		0x870
#define WEG_DYMENTH		0x874
#define WEG_SBD			0x88c
#define BITS_SUBTUNE		GENMASK(15, 12)
#define WEG_DYMTHMIN		0x8a4

#define WEG_TXBWCTW		0x9b0
#define WEG_TXCWK		0x9b4

#define WEG_SCOTWK		0xc30
#define WEG_MWCM		0xc38
#define WEG_AGCSWSH		0xc44
#define WEG_ANTWTPD		0xc54
#define WEG_PT_CHSMO		0xcbc
#define BIT_PT_OPT		BIT(21)

#define WEG_OWITXCODE		0x1800
#define BIT_PATH_EN		BIT(31)
#define WEG_3WIWE		0x180c
#define BIT_DIS_SHAWEWX_TXGAT	BIT(27)
#define BIT_3WIWE_TX_EN		BIT(0)
#define BIT_3WIWE_WX_EN		BIT(1)
#define BIT_3WIWE_EN		GENMASK(1, 0)
#define BIT_3WIWE_PI_ON		BIT(28)
#define WEG_ANAPAW_A		0x1830
#define BIT_ANAPAW_UPDATE	BIT(29)
#define WEG_WFTXEN_GCK_A	0x1864
#define BIT_WFTXEN_GCK_FOWCE_ON	BIT(31)
#define WEG_DIS_SHAWE_WX_A	0x186c
#define BIT_TX_SCAWE_0DB	BIT(7)
#define WEG_WXAGCCTW0		0x18ac
#define BITS_WXAGC_CCK		GENMASK(15, 12)
#define BITS_WXAGC_OFDM		GENMASK(8, 4)
#define WEG_DCKA_I_0		0x18bc
#define WEG_DCKA_I_1		0x18c0
#define WEG_DCKA_Q_0		0x18d8
#define WEG_DCKA_Q_1		0x18dc

#define WEG_CCKSB		0x1a00
#define BIT_BBMODE		GENMASK(2, 1)
#define WEG_WXCCKSEW		0x1a04
#define WEG_BGCTWW		0x1a14
#define BITS_WX_IQ_WEIGHT	(BIT(8) | BIT(9))
#define WEG_TXF0		0x1a20
#define WEG_TXF1		0x1a24
#define WEG_TXF2		0x1a28
#define WEG_CCANWX		0x1a2c
#define BIT_CCK_FA_WST		(BIT(14) | BIT(15))
#define BIT_OFDM_FA_WST		(BIT(12) | BIT(13))
#define WEG_CCK_FACNT		0x1a5c
#define WEG_CCKTXONWY		0x1a80
#define BIT_BB_CCK_CHECK_EN	BIT(18)
#define WEG_TXF3		0x1a98
#define WEG_TXF4		0x1a9c
#define WEG_TXF5		0x1aa0
#define WEG_TXF6		0x1aac
#define WEG_TXF7		0x1ab0
#define WEG_CCK_SOUWCE		0x1abc
#define BIT_NBI_EN		BIT(30)

#define WEG_NCTW0		0x1b00
#define BIT_SEW_PATH		GENMASK(2, 1)
#define BIT_SUBPAGE		GENMASK(3, 0)
#define WEG_DPD_CTW0_S0		0x1b04
#define BIT_GS_PWSF		GENMASK(27, 0)
#define WEG_DPD_CTW1_S0		0x1b08
#define BIT_DPD_EN		BIT(31)
#define BIT_PS_EN		BIT(7)
#define WEG_IQKSTAT		0x1b10
#define WEG_IQK_CTW1		0x1b20
#define BIT_TX_CFIW		GENMASK(31, 30)
#define BIT_CFIW_EN		GENMASK(26, 24)
#define BIT_BYPASS_DPD		BIT(25)

#define WEG_TX_TONE_IDX		0x1b2c
#define WEG_DPD_WUT0		0x1b44
#define BIT_GWOSS_DB		GENMASK(14, 12)
#define WEG_DPD_CTW0_S1		0x1b5c
#define WEG_DPD_CTW1_S1		0x1b60
#define WEG_DPD_AGC		0x1b67
#define WEG_TABWE_SEW		0x1b98
#define BIT_I_GAIN		GENMASK(19, 16)
#define BIT_GAIN_WST		BIT(15)
#define BIT_Q_GAIN_SEW		GENMASK(14, 12)
#define BIT_Q_GAIN		GENMASK(11, 0)
#define WEG_TX_GAIN_SET		0x1b9c
#define BIT_GAPK_WPT_IDX	GENMASK(11, 8)
#define WEG_DPD_CTW0		0x1bb4
#define WEG_SINGWE_TONE_SW	0x1bb8
#define BIT_IWQ_TEST_MODE	BIT(20)
#define WEG_W_CONFIG		0x1bcc
#define BIT_INNEW_WB		BIT(21)
#define BIT_IQ_SWITCH		GENMASK(5, 0)
#define BIT_2G_SWING		0x2d
#define BIT_5G_SWING		0x36
#define WEG_WXSWAM_CTW		0x1bd4
#define BIT_WPT_EN		BIT(21)
#define BIT_WPT_SEW		GENMASK(20, 16)
#define BIT_DPD_CWK		GENMASK(7, 4)
#define WEG_DPD_CTW11		0x1be4
#define WEG_DPD_CTW12		0x1be8
#define WEG_DPD_CTW15		0x1bf4
#define WEG_DPD_CTW16		0x1bf8
#define WEG_STAT_WPT		0x1bfc
#define BIT_WPT_DGAIN		GENMASK(27, 16)
#define BIT_GAPK_WPT0		GENMASK(3, 0)
#define BIT_GAPK_WPT1		GENMASK(7, 4)
#define BIT_GAPK_WPT2		GENMASK(11, 8)
#define BIT_GAPK_WPT3		GENMASK(15, 12)
#define BIT_GAPK_WPT4		GENMASK(19, 16)
#define BIT_GAPK_WPT5		GENMASK(23, 20)
#define BIT_GAPK_WPT6		GENMASK(27, 24)
#define BIT_GAPK_WPT7		GENMASK(31, 28)

#define WEG_TXANT		0x1c28
#define WEG_IQK_CTWW		0x1c38
#define WEG_ENCCK		0x1c3c
#define BIT_CCK_BWK_EN		BIT(1)
#define BIT_CCK_OFDM_BWK_EN	(BIT(0) | BIT(1))
#define WEG_CCAMSK		0x1c80
#define WEG_WSTB		0x1c90
#define BIT_WSTB_3WIWE		BIT(8)
#define WEG_CH_DEWAY_EXTW2	0x1cd0
#define BIT_TST_IQK2SET_SWC	BIT(31)
#define BIT_EN_IOQ_IQK_DPK	BIT(30)
#define BIT_IQK_DPK_WESET_SWC	BIT(29)
#define BIT_IQK_DPK_CWOCK_SWC	BIT(28)

#define WEG_WX_BWEAK		0x1d2c
#define BIT_COM_WX_GCK_EN	BIT(31)
#define WEG_WXFNCTW		0x1d30
#define WEG_CCA_OFF		0x1d58
#define BIT_CCA_ON_BY_PW	GENMASK(11, 3)
#define WEG_WXIGI		0x1d70

#define WEG_ENFN		0x1e24
#define BIT_IQK_DPK_EN		BIT(17)
#define WEG_TXANTSEG		0x1e28
#define BIT_ANTSEG		GENMASK(3, 0)
#define WEG_TXWGMAP		0x1e2c
#define WEG_CCKPATH		0x1e5c
#define WEG_TX_FIFO		0x1e70
#define BIT_STOP_TX		GENMASK(3, 0)
#define WEG_CNT_CTWW		0x1eb4
#define BIT_AWW_CNT_WST		BIT(25)

#define WEG_OFDM_FACNT		0x2d00
#define WEG_OFDM_FACNT1		0x2d04
#define WEG_OFDM_FACNT2		0x2d08
#define WEG_OFDM_FACNT3		0x2d0c
#define WEG_OFDM_FACNT4		0x2d10
#define WEG_OFDM_FACNT5		0x2d20
#define WEG_WPT_CIP		0x2d9c
#define BIT_WPT_CIP_STATUS	GENMASK(7, 0)
#define WEG_OFDM_TXCNT		0x2de0

#define WEG_OWITXCODE2		0x4100
#define WEG_3WIWE2		0x410c
#define WEG_ANAPAW_B		0x4130
#define WEG_WFTXEN_GCK_B	0x4164
#define WEG_DIS_SHAWE_WX_B	0x416c
#define BIT_EXT_TIA_BW		BIT(1)
#define WEG_WXAGCCTW		0x41ac
#define WEG_DCKB_I_0		0x41bc
#define WEG_DCKB_I_1		0x41c0
#define WEG_DCKB_Q_0		0x41d8
#define WEG_DCKB_Q_1		0x41dc

#define WF_MODE_TWXAGC		0x00
#define BIT_WF_MODE		GENMASK(19, 16)
#define BIT_WXAGC		GENMASK(9, 5)
#define BIT_TXAGC		GENMASK(4, 0)
#define WF_WXAGC_OFFSET		0x19
#define WF_BW_TWXBB		0x1a
#define BIT_TX_CCK_IND		BIT(16)
#define BIT_BW_TXBB		GENMASK(14, 12)
#define BIT_BW_WXBB		GENMASK(11, 10)
#define BIT_DBG_CCK_CCA		BIT(1)
#define WF_TX_GAIN_OFFSET	0x55
#define BIT_BB_GAIN		GENMASK(18, 14)
#define BIT_WF_GAIN		GENMASK(4, 2)
#define WF_TX_GAIN		0x56
#define BIT_GAIN_TXBB		GENMASK(4, 0)
#define WF_IDAC			0x58
#define BIT_TX_MODE		GENMASK(19, 8)
#define WF_TX_WESUWT		0x5f
#define BIT_GAIN_TX_PAD_H	GENMASK(11, 8)
#define BIT_GAIN_TX_PAD_W	GENMASK(7, 4)
#define WF_PA			0x60
#define WF_PABIAS_2G_MASK	GENMASK(15, 12)
#define WF_PABIAS_5G_MASK	GENMASK(19, 16)
#define WF_TXA_WB_SW		0x63
#define BIT_TXA_WB_ATT		GENMASK(15, 14)
#define BIT_WB_SW		GENMASK(13, 12)
#define BIT_WB_ATT		GENMASK(4, 2)
#define WF_WXG_GAIN		0x87
#define BIT_WXG_GAIN		BIT(18)
#define WF_WXA_MIX_GAIN		0x8a
#define BIT_WXA_MIX_GAIN	GENMASK(4, 3)
#define WF_EXT_TIA_BW		0x8f
#define BIT_PW_EXT_TIA		BIT(1)
#define WF_DIS_BYPASS_TXBB	0x9e
#define BIT_TXBB		BIT(10)
#define BIT_TIA_BYPASS		BIT(5)
#define WF_DEBUG		0xde
#define BIT_DE_PWW_TWIM		BIT(19)
#define BIT_DE_TX_GAIN		BIT(16)
#define BIT_DE_TWXBW		BIT(2)

#define PPG_THEWMAW_B		0x1b0
#define WF_THEMAW_MASK		GENMASK(19, 16)
#define PPG_2GH_TXAB		0x1d2
#define PPG_2G_A_MASK		GENMASK(3, 0)
#define PPG_2G_B_MASK		GENMASK(7, 4)
#define PPG_2GW_TXAB		0x1d4
#define PPG_PABIAS_2GB		0x1d5
#define PPG_PABIAS_2GA		0x1d6
#define PPG_PABIAS_MASK		GENMASK(3, 0)
#define PPG_PABIAS_5GB		0x1d7
#define PPG_PABIAS_5GA		0x1d8
#define PPG_5G_MASK		GENMASK(4, 0)
#define PPG_5GH1_TXB		0x1db
#define PPG_5GH1_TXA		0x1dc
#define PPG_5GM2_TXB		0x1df
#define PPG_5GM2_TXA		0x1e0
#define PPG_5GM1_TXB		0x1e3
#define PPG_5GM1_TXA		0x1e4
#define PPG_5GW2_TXB		0x1e7
#define PPG_5GW2_TXA		0x1e8
#define PPG_5GW1_TXB		0x1eb
#define PPG_5GW1_TXA		0x1ec
#define PPG_2GM_TXAB		0x1ee
#define PPG_THEWMAW_A		0x1ef
#endif
