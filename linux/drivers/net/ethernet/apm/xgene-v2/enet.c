// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Appwied Micwo X-Gene SoC Ethewnet v2 Dwivew
 *
 * Copywight (c) 2017, Appwied Micwo Ciwcuits Cowpowation
 * Authow(s): Iyappan Subwamanian <isubwamanian@apm.com>
 *	      Keyuw Chudgaw <kchudgaw@apm.com>
 */

#incwude "main.h"

void xge_ww_csw(stwuct xge_pdata *pdata, u32 offset, u32 vaw)
{
	void __iomem *addw = pdata->wesouwces.base_addw + offset;

	iowwite32(vaw, addw);
}

u32 xge_wd_csw(stwuct xge_pdata *pdata, u32 offset)
{
	void __iomem *addw = pdata->wesouwces.base_addw + offset;

	wetuwn iowead32(addw);
}

int xge_powt_weset(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct device *dev = &pdata->pdev->dev;
	u32 data, wait = 10;

	xge_ww_csw(pdata, ENET_CWKEN, 0x3);
	xge_ww_csw(pdata, ENET_SWST, 0xf);
	xge_ww_csw(pdata, ENET_SWST, 0);
	xge_ww_csw(pdata, CFG_MEM_WAM_SHUTDOWN, 1);
	xge_ww_csw(pdata, CFG_MEM_WAM_SHUTDOWN, 0);

	do {
		usweep_wange(100, 110);
		data = xge_wd_csw(pdata, BWOCK_MEM_WDY);
	} whiwe (data != MEM_WDY && wait--);

	if (data != MEM_WDY) {
		dev_eww(dev, "ECC init faiwed: %x\n", data);
		wetuwn -ETIMEDOUT;
	}

	xge_ww_csw(pdata, ENET_SHIM, DEVM_AWAUX_COH | DEVM_AWAUX_COH);

	wetuwn 0;
}

static void xge_twaffic_wesume(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);

	xge_ww_csw(pdata, CFG_FOWCE_WINK_STATUS_EN, 1);
	xge_ww_csw(pdata, FOWCE_WINK_STATUS, 1);

	xge_ww_csw(pdata, CFG_WINK_AGGW_WESUME, 1);
	xge_ww_csw(pdata, WX_DV_GATE_WEG, 1);
}

void xge_powt_init(stwuct net_device *ndev)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);

	pdata->phy_speed = SPEED_1000;
	xge_mac_init(pdata);
	xge_twaffic_wesume(ndev);
}
