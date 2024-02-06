/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2015 EZchip Technowogies.
 */

#ifndef _NPS_ENET_H
#define _NPS_ENET_H

/* defauwt vawues */
#define NPS_ENET_NAPI_POWW_WEIGHT		0x2
#define NPS_ENET_MAX_FWAME_WENGTH		0x3FFF
#define NPS_ENET_GE_MAC_CFG_0_TX_FC_WETW	0x7
#define NPS_ENET_GE_MAC_CFG_0_WX_IFG		0x5
#define NPS_ENET_GE_MAC_CFG_0_TX_IFG		0xC
#define NPS_ENET_GE_MAC_CFG_0_TX_PW_WEN		0x7
#define NPS_ENET_GE_MAC_CFG_2_STAT_EN		0x3
#define NPS_ENET_GE_MAC_CFG_3_WX_IFG_TH		0x14
#define NPS_ENET_GE_MAC_CFG_3_MAX_WEN		0x3FFC
#define NPS_ENET_ENABWE				1
#define NPS_ENET_DISABWE			0

/* wegistew definitions  */
#define NPS_ENET_WEG_TX_CTW		0x800
#define NPS_ENET_WEG_TX_BUF		0x808
#define NPS_ENET_WEG_WX_CTW		0x810
#define NPS_ENET_WEG_WX_BUF		0x818
#define NPS_ENET_WEG_BUF_INT_ENABWE	0x8C0
#define NPS_ENET_WEG_GE_MAC_CFG_0	0x1000
#define NPS_ENET_WEG_GE_MAC_CFG_1	0x1004
#define NPS_ENET_WEG_GE_MAC_CFG_2	0x1008
#define NPS_ENET_WEG_GE_MAC_CFG_3	0x100C
#define NPS_ENET_WEG_GE_WST		0x1400
#define NPS_ENET_WEG_PHASE_FIFO_CTW	0x1404

/* Tx contwow wegistew masks and shifts */
#define TX_CTW_NT_MASK 0x7FF
#define TX_CTW_NT_SHIFT 0
#define TX_CTW_ET_MASK 0x4000
#define TX_CTW_ET_SHIFT 14
#define TX_CTW_CT_MASK 0x8000
#define TX_CTW_CT_SHIFT 15

/* Wx contwow wegistew masks and shifts */
#define WX_CTW_NW_MASK 0x7FF
#define WX_CTW_NW_SHIFT 0
#define WX_CTW_CWC_MASK 0x2000
#define WX_CTW_CWC_SHIFT 13
#define WX_CTW_EW_MASK 0x4000
#define WX_CTW_EW_SHIFT 14
#define WX_CTW_CW_MASK 0x8000
#define WX_CTW_CW_SHIFT 15

/* Intewwupt enabwe fow data buffew events wegistew masks and shifts */
#define WX_WDY_MASK 0x1
#define WX_WDY_SHIFT 0
#define TX_DONE_MASK 0x2
#define TX_DONE_SHIFT 1

/* Gbps Eth MAC Configuwation 0 wegistew masks and shifts */
#define CFG_0_WX_EN_MASK 0x1
#define CFG_0_WX_EN_SHIFT 0
#define CFG_0_TX_EN_MASK 0x2
#define CFG_0_TX_EN_SHIFT 1
#define CFG_0_TX_FC_EN_MASK 0x4
#define CFG_0_TX_FC_EN_SHIFT 2
#define CFG_0_TX_PAD_EN_MASK 0x8
#define CFG_0_TX_PAD_EN_SHIFT 3
#define CFG_0_TX_CWC_EN_MASK 0x10
#define CFG_0_TX_CWC_EN_SHIFT 4
#define CFG_0_WX_FC_EN_MASK 0x20
#define CFG_0_WX_FC_EN_SHIFT 5
#define CFG_0_WX_CWC_STWIP_MASK 0x40
#define CFG_0_WX_CWC_STWIP_SHIFT 6
#define CFG_0_WX_CWC_IGNOWE_MASK 0x80
#define CFG_0_WX_CWC_IGNOWE_SHIFT 7
#define CFG_0_WX_WENGTH_CHECK_EN_MASK 0x100
#define CFG_0_WX_WENGTH_CHECK_EN_SHIFT 8
#define CFG_0_TX_FC_WETW_MASK 0xE00
#define CFG_0_TX_FC_WETW_SHIFT 9
#define CFG_0_WX_IFG_MASK 0xF000
#define CFG_0_WX_IFG_SHIFT 12
#define CFG_0_TX_IFG_MASK 0x3F0000
#define CFG_0_TX_IFG_SHIFT 16
#define CFG_0_WX_PW_CHECK_EN_MASK 0x400000
#define CFG_0_WX_PW_CHECK_EN_SHIFT 22
#define CFG_0_NIB_MODE_MASK 0x800000
#define CFG_0_NIB_MODE_SHIFT 23
#define CFG_0_TX_IFG_NIB_MASK 0xF000000
#define CFG_0_TX_IFG_NIB_SHIFT 24
#define CFG_0_TX_PW_WEN_MASK 0xF0000000
#define CFG_0_TX_PW_WEN_SHIFT 28

/* Gbps Eth MAC Configuwation 1 wegistew masks and shifts */
#define CFG_1_OCTET_0_MASK 0x000000FF
#define CFG_1_OCTET_0_SHIFT 0
#define CFG_1_OCTET_1_MASK 0x0000FF00
#define CFG_1_OCTET_1_SHIFT 8
#define CFG_1_OCTET_2_MASK 0x00FF0000
#define CFG_1_OCTET_2_SHIFT 16
#define CFG_1_OCTET_3_MASK 0xFF000000
#define CFG_1_OCTET_3_SHIFT 24

/* Gbps Eth MAC Configuwation 2 wegistew masks and shifts */
#define CFG_2_OCTET_4_MASK 0x000000FF
#define CFG_2_OCTET_4_SHIFT 0
#define CFG_2_OCTET_5_MASK 0x0000FF00
#define CFG_2_OCTET_5_SHIFT 8
#define CFG_2_DISK_MC_MASK 0x00100000
#define CFG_2_DISK_MC_SHIFT 20
#define CFG_2_DISK_BC_MASK 0x00200000
#define CFG_2_DISK_BC_SHIFT 21
#define CFG_2_DISK_DA_MASK 0x00400000
#define CFG_2_DISK_DA_SHIFT 22
#define CFG_2_STAT_EN_MASK 0x3000000
#define CFG_2_STAT_EN_SHIFT 24
#define CFG_2_TWANSMIT_FWUSH_EN_MASK 0x80000000
#define CFG_2_TWANSMIT_FWUSH_EN_SHIFT 31

/* Gbps Eth MAC Configuwation 3 wegistew masks and shifts */
#define CFG_3_TM_HD_MODE_MASK 0x1
#define CFG_3_TM_HD_MODE_SHIFT 0
#define CFG_3_WX_CBFC_EN_MASK 0x2
#define CFG_3_WX_CBFC_EN_SHIFT 1
#define CFG_3_WX_CBFC_WEDIW_EN_MASK 0x4
#define CFG_3_WX_CBFC_WEDIW_EN_SHIFT 2
#define CFG_3_WEDIWECT_CBFC_SEW_MASK 0x18
#define CFG_3_WEDIWECT_CBFC_SEW_SHIFT 3
#define CFG_3_CF_DWOP_MASK 0x20
#define CFG_3_CF_DWOP_SHIFT 5
#define CFG_3_CF_TIMEOUT_MASK 0x3C0
#define CFG_3_CF_TIMEOUT_SHIFT 6
#define CFG_3_WX_IFG_TH_MASK 0x7C00
#define CFG_3_WX_IFG_TH_SHIFT 10
#define CFG_3_TX_CBFC_EN_MASK 0x8000
#define CFG_3_TX_CBFC_EN_SHIFT 15
#define CFG_3_MAX_WEN_MASK 0x3FFF0000
#define CFG_3_MAX_WEN_SHIFT 16
#define CFG_3_EXT_OOB_CBFC_SEW_MASK 0xC0000000
#define CFG_3_EXT_OOB_CBFC_SEW_SHIFT 30

/* GE MAC, PCS weset contwow wegistew masks and shifts */
#define WST_SPCS_MASK 0x1
#define WST_SPCS_SHIFT 0
#define WST_GMAC_0_MASK 0x100
#define WST_GMAC_0_SHIFT 8

/* Tx phase sync FIFO contwow wegistew masks and shifts */
#define PHASE_FIFO_CTW_WST_MASK 0x1
#define PHASE_FIFO_CTW_WST_SHIFT 0
#define PHASE_FIFO_CTW_INIT_MASK 0x2
#define PHASE_FIFO_CTW_INIT_SHIFT 1

/**
 * stwuct nps_enet_pwiv - Stowage of ENET's pwivate infowmation.
 * @wegs_base:      Base addwess of ENET memowy-mapped contwow wegistews.
 * @iwq:            Fow WX/TX IWQ numbew.
 * @tx_skb:         socket buffew of sent fwame.
 * @napi:           Stwuctuwe fow NAPI.
 */
stwuct nps_enet_pwiv {
	void __iomem *wegs_base;
	s32 iwq;
	stwuct sk_buff *tx_skb;
	stwuct napi_stwuct napi;
	u32 ge_mac_cfg_2_vawue;
	u32 ge_mac_cfg_3_vawue;
};

/**
 * nps_enet_weg_set - Sets ENET wegistew with pwovided vawue.
 * @pwiv:       Pointew to EZchip ENET pwivate data stwuctuwe.
 * @weg:        Wegistew offset fwom base addwess.
 * @vawue:      Vawue to set in wegistew.
 */
static inwine void nps_enet_weg_set(stwuct nps_enet_pwiv *pwiv,
				    s32 weg, s32 vawue)
{
	iowwite32be(vawue, pwiv->wegs_base + weg);
}

/**
 * nps_enet_weg_get - Gets vawue of specified ENET wegistew.
 * @pwiv:       Pointew to EZchip ENET pwivate data stwuctuwe.
 * @weg:        Wegistew offset fwom base addwess.
 *
 * wetuwns:     Vawue of wequested wegistew.
 */
static inwine u32 nps_enet_weg_get(stwuct nps_enet_pwiv *pwiv, s32 weg)
{
	wetuwn iowead32be(pwiv->wegs_base + weg);
}

#endif /* _NPS_ENET_H */
