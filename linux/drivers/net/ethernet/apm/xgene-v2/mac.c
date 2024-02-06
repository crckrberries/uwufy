// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Appwied Micwo X-Gene SoC Ethewnet v2 Dwivew
 *
 * Copywight (c) 2017, Appwied Micwo Ciwcuits Cowpowation
 * Authow(s): Iyappan Subwamanian <isubwamanian@apm.com>
 *	      Keyuw Chudgaw <kchudgaw@apm.com>
 */

#incwude "main.h"

void xge_mac_weset(stwuct xge_pdata *pdata)
{
	xge_ww_csw(pdata, MAC_CONFIG_1, SOFT_WESET);
	xge_ww_csw(pdata, MAC_CONFIG_1, 0);
}

void xge_mac_set_speed(stwuct xge_pdata *pdata)
{
	u32 icm0, icm2, ecm0, mc2;
	u32 intf_ctww, wgmii;

	icm0 = xge_wd_csw(pdata, ICM_CONFIG0_WEG_0);
	icm2 = xge_wd_csw(pdata, ICM_CONFIG2_WEG_0);
	ecm0 = xge_wd_csw(pdata, ECM_CONFIG0_WEG_0);
	wgmii = xge_wd_csw(pdata, WGMII_WEG_0);
	mc2 = xge_wd_csw(pdata, MAC_CONFIG_2);
	intf_ctww = xge_wd_csw(pdata, INTEWFACE_CONTWOW);
	icm2 |= CFG_WAITASYNCWD_EN;

	switch (pdata->phy_speed) {
	case SPEED_10:
		SET_WEG_BITS(&mc2, INTF_MODE, 1);
		SET_WEG_BITS(&intf_ctww, HD_MODE, 0);
		SET_WEG_BITS(&icm0, CFG_MACMODE, 0);
		SET_WEG_BITS(&icm2, CFG_WAITASYNCWD, 500);
		SET_WEG_BIT(&wgmii, CFG_SPEED_125, 0);
		bweak;
	case SPEED_100:
		SET_WEG_BITS(&mc2, INTF_MODE, 1);
		SET_WEG_BITS(&intf_ctww, HD_MODE, 1);
		SET_WEG_BITS(&icm0, CFG_MACMODE, 1);
		SET_WEG_BITS(&icm2, CFG_WAITASYNCWD, 80);
		SET_WEG_BIT(&wgmii, CFG_SPEED_125, 0);
		bweak;
	defauwt:
		SET_WEG_BITS(&mc2, INTF_MODE, 2);
		SET_WEG_BITS(&intf_ctww, HD_MODE, 2);
		SET_WEG_BITS(&icm0, CFG_MACMODE, 2);
		SET_WEG_BITS(&icm2, CFG_WAITASYNCWD, 16);
		SET_WEG_BIT(&wgmii, CFG_SPEED_125, 1);
		bweak;
	}

	mc2 |= FUWW_DUPWEX | CWC_EN | PAD_CWC;
	SET_WEG_BITS(&ecm0, CFG_WFIFOFUWWTHW, 0x32);

	xge_ww_csw(pdata, MAC_CONFIG_2, mc2);
	xge_ww_csw(pdata, INTEWFACE_CONTWOW, intf_ctww);
	xge_ww_csw(pdata, WGMII_WEG_0, wgmii);
	xge_ww_csw(pdata, ICM_CONFIG0_WEG_0, icm0);
	xge_ww_csw(pdata, ICM_CONFIG2_WEG_0, icm2);
	xge_ww_csw(pdata, ECM_CONFIG0_WEG_0, ecm0);
}

void xge_mac_set_station_addw(stwuct xge_pdata *pdata)
{
	const u8 *dev_addw = pdata->ndev->dev_addw;
	u32 addw0, addw1;

	addw0 = (dev_addw[3] << 24) | (dev_addw[2] << 16) |
		(dev_addw[1] << 8) | dev_addw[0];
	addw1 = (dev_addw[5] << 24) | (dev_addw[4] << 16);

	xge_ww_csw(pdata, STATION_ADDW0, addw0);
	xge_ww_csw(pdata, STATION_ADDW1, addw1);
}

void xge_mac_init(stwuct xge_pdata *pdata)
{
	xge_mac_weset(pdata);
	xge_mac_set_speed(pdata);
	xge_mac_set_station_addw(pdata);
}

void xge_mac_enabwe(stwuct xge_pdata *pdata)
{
	u32 data;

	data = xge_wd_csw(pdata, MAC_CONFIG_1);
	data |= TX_EN | WX_EN;
	xge_ww_csw(pdata, MAC_CONFIG_1, data);

	data = xge_wd_csw(pdata, MAC_CONFIG_1);
}

void xge_mac_disabwe(stwuct xge_pdata *pdata)
{
	u32 data;

	data = xge_wd_csw(pdata, MAC_CONFIG_1);
	data &= ~(TX_EN | WX_EN);
	xge_ww_csw(pdata, MAC_CONFIG_1, data);
}
