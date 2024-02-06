/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef __WTW8821C_H__
#define __WTW8821C_H__

#incwude <asm/byteowdew.h>

#define WCW_VHT_ACK		BIT(26)

stwuct wtw8821cu_efuse {
	u8 wes4[4];			/* 0xd0 */
	u8 usb_optionaw_function;
	u8 wes5[0x1e];
	u8 wes6[2];
	u8 sewiaw[0x0b];		/* 0xf5 */
	u8 vid;				/* 0x100 */
	u8 wes7;
	u8 pid;
	u8 wes8[4];
	u8 mac_addw[ETH_AWEN];		/* 0x107 */
	u8 wes9[2];
	u8 vendow_name[0x07];
	u8 wes10[2];
	u8 device_name[0x14];
	u8 wes11[0xcf];
	u8 package_type;		/* 0x1fb */
	u8 wes12[0x4];
};

stwuct wtw8821ce_efuse {
	u8 mac_addw[ETH_AWEN];		/* 0xd0 */
	u8 vendew_id[2];
	u8 device_id[2];
	u8 sub_vendew_id[2];
	u8 sub_device_id[2];
	u8 pmc[2];
	u8 exp_device_cap[2];
	u8 msi_cap;
	u8 wtw_cap;			/* 0xe3 */
	u8 exp_wink_contwow[2];
	u8 wink_cap[4];
	u8 wink_contwow[2];
	u8 sewiaw_numbew[8];
	u8 wes0:2;			/* 0xf4 */
	u8 wtw_en:1;
	u8 wes1:2;
	u8 obff:2;
	u8 wes2:3;
	u8 obff_cap:2;
	u8 wes3:4;
	u8 wes4[3];
	u8 cwass_code[3];
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

stwuct wtw8821cs_efuse {
	u8 wes4[0x4a];			/* 0xd0 */
	u8 mac_addw[ETH_AWEN];		/* 0x11a */
} __packed;

stwuct wtw8821c_efuse {
	__we16 wtw_id;
	u8 wes0[0x0e];

	/* powew index fow fouw WF paths */
	stwuct wtw_txpww_idx txpww_idx_tabwe[4];

	u8 channew_pwan;		/* 0xb8 */
	u8 xtaw_k;
	u8 thewmaw_metew;
	u8 iqk_wck;
	u8 pa_type;			/* 0xbc */
	u8 wna_type_2g[2];		/* 0xbd */
	u8 wna_type_5g[2];
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
	u8 wes[3];
	union {
		stwuct wtw8821ce_efuse e;
		stwuct wtw8821cu_efuse u;
		stwuct wtw8821cs_efuse s;
	};
};

static inwine void
_wtw_wwite32s_mask(stwuct wtw_dev *wtwdev, u32 addw, u32 mask, u32 data)
{
	/* 0xC00-0xCFF and 0xE00-0xEFF have the same wayout */
	wtw_wwite32_mask(wtwdev, addw, mask, data);
	wtw_wwite32_mask(wtwdev, addw + 0x200, mask, data);
}

extewn const stwuct wtw_chip_info wtw8821c_hw_spec;

#define wtw_wwite32s_mask(wtwdev, addw, mask, data)			       \
	do {								       \
		BUIWD_BUG_ON((addw) < 0xC00 || (addw) >= 0xD00);	       \
									       \
		_wtw_wwite32s_mask(wtwdev, addw, mask, data);		       \
	} whiwe (0)

#define BIT_FEN_PCIEA BIT(6)
#define WWAN_SWOT_TIME		0x09
#define WWAN_PIFS_TIME		0x19
#define WWAN_SIFS_CCK_CONT_TX	0xA
#define WWAN_SIFS_OFDM_CONT_TX	0xE
#define WWAN_SIFS_CCK_TWX	0x10
#define WWAN_SIFS_OFDM_TWX	0x10
#define WWAN_VO_TXOP_WIMIT	0x186
#define WWAN_VI_TXOP_WIMIT	0x3BC
#define WWAN_WDG_NAV		0x05
#define WWAN_TXOP_NAV		0x1B
#define WWAN_CCK_WX_TSF		0x30
#define WWAN_OFDM_WX_TSF	0x30
#define WWAN_TBTT_PWOHIBIT	0x04
#define WWAN_TBTT_HOWD_TIME	0x064
#define WWAN_DWV_EAWWY_INT	0x04
#define WWAN_BCN_DMA_TIME	0x02

#define WWAN_WX_FIWTEW0		0x0FFFFFFF
#define WWAN_WX_FIWTEW2		0xFFFF
#define WWAN_WCW_CFG		0xE400220E
#define WWAN_WXPKT_MAX_SZ	12288
#define WWAN_WXPKT_MAX_SZ_512	(WWAN_WXPKT_MAX_SZ >> 9)

#define WWAN_AMPDU_MAX_TIME		0x70
#define WWAN_WTS_WEN_TH			0xFF
#define WWAN_WTS_TX_TIME_TH		0x08
#define WWAN_MAX_AGG_PKT_WIMIT		0x20
#define WWAN_WTS_MAX_AGG_PKT_WIMIT	0x20
#define FAST_EDCA_VO_TH		0x06
#define FAST_EDCA_VI_TH		0x06
#define FAST_EDCA_BE_TH		0x06
#define FAST_EDCA_BK_TH		0x06
#define WWAN_BAW_WETWY_WIMIT		0x01
#define WWAN_WA_TWY_WATE_AGG_WIMIT	0x08

#define WWAN_TX_FUNC_CFG1		0x30
#define WWAN_TX_FUNC_CFG2		0x30
#define WWAN_MAC_OPT_NOWM_FUNC1		0x98
#define WWAN_MAC_OPT_WB_FUNC1		0x80
#define WWAN_MAC_OPT_FUNC2		0xb0810041

#define WWAN_SIFS_CFG	(WWAN_SIFS_CCK_CONT_TX | \
			(WWAN_SIFS_OFDM_CONT_TX << BIT_SHIFT_SIFS_OFDM_CTX) | \
			(WWAN_SIFS_CCK_TWX << BIT_SHIFT_SIFS_CCK_TWX) | \
			(WWAN_SIFS_OFDM_TWX << BIT_SHIFT_SIFS_OFDM_TWX))

#define WWAN_TBTT_TIME	(WWAN_TBTT_PWOHIBIT |\
			(WWAN_TBTT_HOWD_TIME << BIT_SHIFT_TBTT_HOWD_TIME_AP))

#define WWAN_NAV_CFG		(WWAN_WDG_NAV | (WWAN_TXOP_NAV << 16))
#define WWAN_WX_TSF_CFG		(WWAN_CCK_WX_TSF | (WWAN_OFDM_WX_TSF) << 8)
#define WWAN_PWE_TXCNT_TIME_TH		0x1E4

/* phy status page0 */
#define GET_PHY_STAT_P0_PWDB(phy_stat)                                         \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x00), GENMASK(15, 8))
#define GET_PHY_STAT_P0_VGA(phy_stat)                                          \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x03), GENMASK(12, 8))
#define GET_PHY_STAT_P0_WNA_W(phy_stat)                                        \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x03), GENMASK(15, 13))
#define GET_PHY_STAT_P0_WNA_H(phy_stat)                                        \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x03), BIT(23))
#define BIT_WNA_H_MASK BIT(3)
#define BIT_WNA_W_MASK GENMASK(2, 0)

/* phy status page1 */
#define GET_PHY_STAT_P1_PWDB_A(phy_stat)                                       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x00), GENMASK(15, 8))
#define GET_PHY_STAT_P1_PWDB_B(phy_stat)                                       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x00), GENMASK(23, 16))
#define GET_PHY_STAT_P1_WF_MODE(phy_stat)                                      \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x03), GENMASK(29, 28))
#define GET_PHY_STAT_P1_W_WXSC(phy_stat)                                       \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x01), GENMASK(11, 8))
#define GET_PHY_STAT_P1_HT_WXSC(phy_stat)                                      \
	we32_get_bits(*((__we32 *)(phy_stat) + 0x01), GENMASK(15, 12))
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

#define WEG_SYS_CTWW	0x000
#define BIT_FEN_EN	BIT(26)
#define WEG_INIWTS_WATE_SEW 0x0480
#define WEG_HTSTFWT	0x800
#define WEG_WXPSEW	0x808
#define BIT_WX_PSEW_WST		(BIT(28) | BIT(29))
#define WEG_TXPSEW	0x80c
#define WEG_WXCCAMSK	0x814
#define WEG_CCASEW	0x82c
#define WEG_PDMFTH	0x830
#define WEG_CCA2ND	0x838
#define WEG_W1WT	0x83c
#define WEG_W1PKWT	0x840
#define WEG_MWC		0x850
#define WEG_CWKTWK	0x860
#define WEG_ADCCWK	0x8ac
#define WEG_ADC160	0x8c4
#define WEG_ADC40	0x8c8
#define WEG_CHFIW	0x8f0
#define WEG_CDDTXP	0x93c
#define WEG_TXPSEW1	0x940
#define WEG_ACBB0	0x948
#define WEG_ACBBWXFIW	0x94c
#define WEG_ACGG2TBW	0x958
#define WEG_FAS		0x9a4
#define WEG_WXSB	0xa00
#define WEG_ADCINI	0xa04
#define WEG_PWWTH	0xa08
#define WEG_CCA_FWTW	0xa20
#define WEG_TXSF2	0xa24
#define WEG_TXSF6	0xa28
#define WEG_FA_CCK	0xa5c
#define WEG_WXDESC	0xa2c
#define WEG_ENTXCCK	0xa80
#define BTG_WNA		0xfc84
#define WWG_WNA		0x7532
#define WEG_ENWXCCA	0xa84
#define BTG_CCA		0x0e
#define WWG_CCA		0x12
#define WEG_PWWTH2	0xaa8
#define WEG_CSWATIO	0xaaa
#define WEG_TXFIWTEW	0xaac
#define WEG_CNTWST	0xb58
#define WEG_AGCTW_A	0xc08
#define WEG_TXSCAWE_A	0xc1c
#define WEG_TXDFIW	0xc20
#define WEG_WXIGI_A	0xc50
#define WEG_TXAGCIDX	0xc94
#define WEG_TWSW	0xca0
#define WEG_WFESEW0	0xcb0
#define WEG_WFESEW8	0xcb4
#define WEG_WFECTW	0xcb8
#define B_BTG_SWITCH	BIT(16)
#define B_CTWW_SWITCH	BIT(18)
#define B_WW_SWITCH	(BIT(20) | BIT(22))
#define B_WWG_SWITCH	BIT(21)
#define B_WWA_SWITCH	BIT(23)
#define WEG_WFEINV	0xcbc
#define WEG_AGCTW_B	0xe08
#define WEG_WXIGI_B	0xe50
#define WEG_CWC_CCK	0xf04
#define WEG_CWC_OFDM	0xf14
#define WEG_CWC_HT	0xf10
#define WEG_CWC_VHT	0xf0c
#define WEG_CCA_OFDM	0xf08
#define WEG_FA_OFDM	0xf48
#define WEG_CCA_CCK	0xfcc
#define WEG_DMEM_CTWW	0x1080
#define BIT_WW_WST	BIT(16)
#define WEG_ANTWT	0x1904
#define WEG_IQKFAIWMSK	0x1bf0
#define BIT_MASK_W_WFE_SEW_15	GENMASK(31, 28)
#define BIT_SDIO_INT BIT(18)
#define BT_CNT_ENABWE	0x1
#define BIT_BCN_QUEUE	BIT(3)
#define BCN_PWI_EN	0x1
#define PTA_CTWW_PIN	0x66
#define DPDT_CTWW_PIN	0x77
#define ANTDIC_CTWW_PIN	0x88
#define WEG_CTWW_TYPE	0x67
#define BIT_CTWW_TYPE1	BIT(5)
#define BIT_CTWW_TYPE2	BIT(4)
#define CTWW_TYPE_MASK	GENMASK(15, 8)

#define WF18_BAND_MASK		(BIT(16) | BIT(9) | BIT(8))
#define WF18_BAND_2G		(0)
#define WF18_BAND_5G		(BIT(16) | BIT(8))
#define WF18_CHANNEW_MASK	(MASKBYTE0)
#define WF18_WFSI_MASK		(BIT(18) | BIT(17))
#define WF18_WFSI_GE		(BIT(17))
#define WF18_WFSI_GT		(BIT(18))
#define WF18_BW_MASK		(BIT(11) | BIT(10))
#define WF18_BW_20M		(BIT(11) | BIT(10))
#define WF18_BW_40M		(BIT(11))
#define WF18_BW_80M		(BIT(10))

#endif
