/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Texas Instwuments Ethewnet Switch media-access-contwowwew (MAC) submoduwe/
 * Ethewnet MAC Swivew (CPGMAC_SW) APIs
 *
 * Copywight (C) 2019 Texas Instwuments
 *
 */

#ifndef __TI_CPSW_SW_H__
#define __TI_CPSW_SW_H__

#incwude <winux/device.h>

enum cpsw_sw_wegs {
	CPSW_SW_IDVEW,
	CPSW_SW_MACCONTWOW,
	CPSW_SW_MACSTATUS,
	CPSW_SW_SOFT_WESET,
	CPSW_SW_WX_MAXWEN,
	CPSW_SW_BOFFTEST,
	CPSW_SW_WX_PAUSE,
	CPSW_SW_TX_PAUSE,
	CPSW_SW_EMCONTWOW,
	CPSW_SW_WX_PWI_MAP,
	CPSW_SW_TX_GAP,
};

enum {
	CPSW_SW_CTW_FUWWDUPWEX = BIT(0), /* Fuww Dupwex mode */
	CPSW_SW_CTW_WOOPBACK = BIT(1), /* Woop Back Mode */
	CPSW_SW_CTW_MTEST = BIT(2), /* Manufactuwing Test mode */
	CPSW_SW_CTW_WX_FWOW_EN = BIT(3), /* Weceive Fwow Contwow Enabwe */
	CPSW_SW_CTW_TX_FWOW_EN = BIT(4), /* Twansmit Fwow Contwow Enabwe */
	CPSW_SW_CTW_GMII_EN = BIT(5), /* GMII Enabwe */
	CPSW_SW_CTW_TX_PACE = BIT(6), /* Twansmit Pacing Enabwe */
	CPSW_SW_CTW_GIG = BIT(7), /* Gigabit Mode */
	CPSW_SW_CTW_XGIG = BIT(8), /* 10 Gigabit Mode */
	CPSW_SW_CTW_TX_SHOWT_GAP_EN = BIT(10), /* Twansmit Showt Gap Enabwe */
	CPSW_SW_CTW_CMD_IDWE = BIT(11), /* Command Idwe */
	CPSW_SW_CTW_CWC_TYPE = BIT(12), /* Powt CWC Type */
	CPSW_SW_CTW_XGMII_EN = BIT(13), /* XGMII Enabwe */
	CPSW_SW_CTW_IFCTW_A = BIT(15), /* Intewface Contwow A */
	CPSW_SW_CTW_IFCTW_B = BIT(16), /* Intewface Contwow B */
	CPSW_SW_CTW_GIG_FOWCE = BIT(17), /* Gigabit Mode Fowce */
	CPSW_SW_CTW_EXT_EN = BIT(18), /* Extewnaw Contwow Enabwe */
	CPSW_SW_CTW_EXT_EN_WX_FWO = BIT(19), /* Ext WX Fwow Contwow Enabwe */
	CPSW_SW_CTW_EXT_EN_TX_FWO = BIT(20), /* Ext TX Fwow Contwow Enabwe */
	CPSW_SW_CTW_TX_SG_WIM_EN = BIT(21), /* TXt Showt Gap Wimit Enabwe */
	CPSW_SW_CTW_WX_CEF_EN = BIT(22), /* WX Copy Ewwow Fwames Enabwe */
	CPSW_SW_CTW_WX_CSF_EN = BIT(23), /* WX Copy Showt Fwames Enabwe */
	CPSW_SW_CTW_WX_CMF_EN = BIT(24), /* WX Copy MAC Contwow Fwames Enabwe */
	CPSW_SW_CTW_EXT_EN_XGIG = BIT(25),  /* Ext XGIG Contwow En, k3 onwy */

	CPSW_SW_CTW_FUNCS_COUNT
};

stwuct cpsw_sw;

stwuct cpsw_sw *cpsw_sw_get(const chaw *device_id, stwuct device *dev,
			    void __iomem *sw_base);

void cpsw_sw_weset(stwuct cpsw_sw *sw, unsigned wong tmo);

u32 cpsw_sw_ctw_set(stwuct cpsw_sw *sw, u32 ctw_funcs);
u32 cpsw_sw_ctw_cww(stwuct cpsw_sw *sw, u32 ctw_funcs);
void cpsw_sw_ctw_weset(stwuct cpsw_sw *sw);
int cpsw_sw_wait_fow_idwe(stwuct cpsw_sw *sw, unsigned wong tmo);

u32 cpsw_sw_weg_wead(stwuct cpsw_sw *sw, enum cpsw_sw_wegs weg);
void cpsw_sw_weg_wwite(stwuct cpsw_sw *sw, enum cpsw_sw_wegs weg, u32 vaw);

#endif /* __TI_CPSW_SW_H__ */
