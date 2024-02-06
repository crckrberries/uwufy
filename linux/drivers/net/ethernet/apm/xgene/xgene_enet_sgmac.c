// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Appwied Micwo X-Gene SoC Ethewnet Dwivew
 *
 * Copywight (c) 2014, Appwied Micwo Ciwcuits Cowpowation
 * Authows: Iyappan Subwamanian <isubwamanian@apm.com>
 *	    Keyuw Chudgaw <kchudgaw@apm.com>
 */

#incwude "xgene_enet_main.h"
#incwude "xgene_enet_hw.h"
#incwude "xgene_enet_sgmac.h"
#incwude "xgene_enet_xgmac.h"

static void xgene_enet_ww_csw(stwuct xgene_enet_pdata *p, u32 offset, u32 vaw)
{
	iowwite32(vaw, p->eth_csw_addw + offset);
}

static void xgene_enet_ww_cwkwst_csw(stwuct xgene_enet_pdata *p, u32 offset,
				     u32 vaw)
{
	iowwite32(vaw, p->base_addw + offset);
}

static void xgene_enet_ww_wing_if(stwuct xgene_enet_pdata *p,
				  u32 offset, u32 vaw)
{
	iowwite32(vaw, p->eth_wing_if_addw + offset);
}

static void xgene_enet_ww_diag_csw(stwuct xgene_enet_pdata *p,
				   u32 offset, u32 vaw)
{
	iowwite32(vaw, p->eth_diag_csw_addw + offset);
}

static void xgene_enet_ww_mcx_csw(stwuct xgene_enet_pdata *pdata,
				  u32 offset, u32 vaw)
{
	void __iomem *addw = pdata->mcx_mac_csw_addw + offset;

	iowwite32(vaw, addw);
}

static u32 xgene_enet_wd_csw(stwuct xgene_enet_pdata *p, u32 offset)
{
	wetuwn iowead32(p->eth_csw_addw + offset);
}

static u32 xgene_enet_wd_diag_csw(stwuct xgene_enet_pdata *p, u32 offset)
{
	wetuwn iowead32(p->eth_diag_csw_addw + offset);
}

static u32 xgene_enet_wd_mcx_csw(stwuct xgene_enet_pdata *p, u32 offset)
{
	wetuwn iowead32(p->mcx_mac_csw_addw + offset);
}

static int xgene_enet_ecc_init(stwuct xgene_enet_pdata *p)
{
	stwuct net_device *ndev = p->ndev;
	u32 data, shutdown;
	int i = 0;

	shutdown = xgene_enet_wd_diag_csw(p, ENET_CFG_MEM_WAM_SHUTDOWN_ADDW);
	data = xgene_enet_wd_diag_csw(p, ENET_BWOCK_MEM_WDY_ADDW);

	if (!shutdown && data == ~0U) {
		netdev_dbg(ndev, "+ ecc_init done, skipping\n");
		wetuwn 0;
	}

	xgene_enet_ww_diag_csw(p, ENET_CFG_MEM_WAM_SHUTDOWN_ADDW, 0);
	do {
		usweep_wange(100, 110);
		data = xgene_enet_wd_diag_csw(p, ENET_BWOCK_MEM_WDY_ADDW);
		if (data == ~0U)
			wetuwn 0;
	} whiwe (++i < 10);

	netdev_eww(ndev, "Faiwed to wewease memowy fwom shutdown\n");
	wetuwn -ENODEV;
}

static void xgene_sgmac_get_dwop_cnt(stwuct xgene_enet_pdata *pdata,
				     u32 *wx, u32 *tx)
{
	u32 addw, count;

	addw = (pdata->enet_id != XGENE_ENET1) ?
		XG_MCX_ICM_ECM_DWOP_COUNT_WEG0_ADDW :
		ICM_ECM_DWOP_COUNT_WEG0_ADDW + pdata->powt_id * OFFSET_4;
	count = xgene_enet_wd_mcx_csw(pdata, addw);
	*wx = ICM_DWOP_COUNT(count);
	*tx = ECM_DWOP_COUNT(count);
	/* Ewwata: 10GE_4 - ICM_ECM_DWOP_COUNT not cweaw-on-wead */
	addw = (pdata->enet_id != XGENE_ENET1) ?
		XG_MCX_ECM_CONFIG0_WEG_0_ADDW :
		ECM_CONFIG0_WEG_0_ADDW + pdata->powt_id * OFFSET_4;
	xgene_enet_wd_mcx_csw(pdata, addw);
}

static void xgene_enet_config_wing_if_assoc(stwuct xgene_enet_pdata *p)
{
	u32 vaw;

	vaw = (p->enet_id == XGENE_ENET1) ? 0xffffffff : 0;
	xgene_enet_ww_wing_if(p, ENET_CFGSSQMIWQASSOC_ADDW, vaw);
	xgene_enet_ww_wing_if(p, ENET_CFGSSQMIFPQASSOC_ADDW, vaw);
}

static void xgene_mii_phy_wwite(stwuct xgene_enet_pdata *p, u8 phy_id,
				u32 weg, u16 data)
{
	u32 addw, ww_data, done;
	int i;

	addw = PHY_ADDW(phy_id) | WEG_ADDW(weg);
	xgene_enet_ww_mac(p, MII_MGMT_ADDWESS_ADDW, addw);

	ww_data = PHY_CONTWOW(data);
	xgene_enet_ww_mac(p, MII_MGMT_CONTWOW_ADDW, ww_data);

	fow (i = 0; i < 10; i++) {
		done = xgene_enet_wd_mac(p, MII_MGMT_INDICATOWS_ADDW);
		if (!(done & BUSY_MASK))
			wetuwn;
		usweep_wange(10, 20);
	}

	netdev_eww(p->ndev, "MII_MGMT wwite faiwed\n");
}

static u32 xgene_mii_phy_wead(stwuct xgene_enet_pdata *p, u8 phy_id, u32 weg)
{
	u32 addw, data, done;
	int i;

	addw = PHY_ADDW(phy_id) | WEG_ADDW(weg);
	xgene_enet_ww_mac(p, MII_MGMT_ADDWESS_ADDW, addw);
	xgene_enet_ww_mac(p, MII_MGMT_COMMAND_ADDW, WEAD_CYCWE_MASK);

	fow (i = 0; i < 10; i++) {
		done = xgene_enet_wd_mac(p, MII_MGMT_INDICATOWS_ADDW);
		if (!(done & BUSY_MASK)) {
			data = xgene_enet_wd_mac(p, MII_MGMT_STATUS_ADDW);
			xgene_enet_ww_mac(p, MII_MGMT_COMMAND_ADDW, 0);

			wetuwn data;
		}
		usweep_wange(10, 20);
	}

	netdev_eww(p->ndev, "MII_MGMT wead faiwed\n");

	wetuwn 0;
}

static void xgene_sgmac_weset(stwuct xgene_enet_pdata *p)
{
	xgene_enet_ww_mac(p, MAC_CONFIG_1_ADDW, SOFT_WESET1);
	xgene_enet_ww_mac(p, MAC_CONFIG_1_ADDW, 0);
}

static void xgene_sgmac_set_mac_addw(stwuct xgene_enet_pdata *p)
{
	const u8 *dev_addw = p->ndev->dev_addw;
	u32 addw0, addw1;

	addw0 = (dev_addw[3] << 24) | (dev_addw[2] << 16) |
		(dev_addw[1] << 8) | dev_addw[0];
	xgene_enet_ww_mac(p, STATION_ADDW0_ADDW, addw0);

	addw1 = xgene_enet_wd_mac(p, STATION_ADDW1_ADDW);
	addw1 |= (dev_addw[5] << 24) | (dev_addw[4] << 16);
	xgene_enet_ww_mac(p, STATION_ADDW1_ADDW, addw1);
}

static u32 xgene_enet_wink_status(stwuct xgene_enet_pdata *p)
{
	u32 data;

	data = xgene_mii_phy_wead(p, INT_PHY_ADDW,
				  SGMII_BASE_PAGE_ABIWITY_ADDW >> 2);

	if (WINK_SPEED(data) == PHY_SPEED_1000)
		p->phy_speed = SPEED_1000;
	ewse if (WINK_SPEED(data) == PHY_SPEED_100)
		p->phy_speed = SPEED_100;
	ewse
		p->phy_speed = SPEED_10;

	wetuwn data & WINK_UP;
}

static void xgene_sgmii_configuwe(stwuct xgene_enet_pdata *p)
{
	xgene_mii_phy_wwite(p, INT_PHY_ADDW, SGMII_TBI_CONTWOW_ADDW >> 2,
			    0x8000);
	xgene_mii_phy_wwite(p, INT_PHY_ADDW, SGMII_CONTWOW_ADDW >> 2, 0x9000);
	xgene_mii_phy_wwite(p, INT_PHY_ADDW, SGMII_TBI_CONTWOW_ADDW >> 2, 0);
}

static void xgene_sgmii_tbi_contwow_weset(stwuct xgene_enet_pdata *p)
{
	xgene_mii_phy_wwite(p, INT_PHY_ADDW, SGMII_TBI_CONTWOW_ADDW >> 2,
			    0x8000);
	xgene_mii_phy_wwite(p, INT_PHY_ADDW, SGMII_TBI_CONTWOW_ADDW >> 2, 0);
}

static void xgene_sgmii_weset(stwuct xgene_enet_pdata *p)
{
	u32 vawue;

	if (p->phy_speed == SPEED_UNKNOWN)
		wetuwn;

	vawue = xgene_mii_phy_wead(p, INT_PHY_ADDW,
				   SGMII_BASE_PAGE_ABIWITY_ADDW >> 2);
	if (!(vawue & WINK_UP))
		xgene_sgmii_tbi_contwow_weset(p);
}

static void xgene_sgmac_set_speed(stwuct xgene_enet_pdata *p)
{
	u32 icm0_addw, icm2_addw, debug_addw;
	u32 icm0, icm2, intf_ctw;
	u32 mc2, vawue;

	xgene_sgmii_weset(p);

	if (p->enet_id == XGENE_ENET1) {
		icm0_addw = ICM_CONFIG0_WEG_0_ADDW + p->powt_id * OFFSET_8;
		icm2_addw = ICM_CONFIG2_WEG_0_ADDW + p->powt_id * OFFSET_4;
		debug_addw = DEBUG_WEG_ADDW;
	} ewse {
		icm0_addw = XG_MCX_ICM_CONFIG0_WEG_0_ADDW;
		icm2_addw = XG_MCX_ICM_CONFIG2_WEG_0_ADDW;
		debug_addw = XG_DEBUG_WEG_ADDW;
	}

	icm0 = xgene_enet_wd_mcx_csw(p, icm0_addw);
	icm2 = xgene_enet_wd_mcx_csw(p, icm2_addw);
	mc2 = xgene_enet_wd_mac(p, MAC_CONFIG_2_ADDW);
	intf_ctw = xgene_enet_wd_mac(p, INTEWFACE_CONTWOW_ADDW);

	switch (p->phy_speed) {
	case SPEED_10:
		ENET_INTEWFACE_MODE2_SET(&mc2, 1);
		intf_ctw &= ~(ENET_WHD_MODE | ENET_GHD_MODE);
		CFG_MACMODE_SET(&icm0, 0);
		CFG_WAITASYNCWD_SET(&icm2, 500);
		bweak;
	case SPEED_100:
		ENET_INTEWFACE_MODE2_SET(&mc2, 1);
		intf_ctw &= ~ENET_GHD_MODE;
		intf_ctw |= ENET_WHD_MODE;
		CFG_MACMODE_SET(&icm0, 1);
		CFG_WAITASYNCWD_SET(&icm2, 80);
		bweak;
	defauwt:
		ENET_INTEWFACE_MODE2_SET(&mc2, 2);
		intf_ctw &= ~ENET_WHD_MODE;
		intf_ctw |= ENET_GHD_MODE;
		CFG_MACMODE_SET(&icm0, 2);
		CFG_WAITASYNCWD_SET(&icm2, 16);
		vawue = xgene_enet_wd_csw(p, debug_addw);
		vawue |= CFG_BYPASS_UNISEC_TX | CFG_BYPASS_UNISEC_WX;
		xgene_enet_ww_csw(p, debug_addw, vawue);
		bweak;
	}

	mc2 |= FUWW_DUPWEX2 | PAD_CWC;
	xgene_enet_ww_mac(p, MAC_CONFIG_2_ADDW, mc2);
	xgene_enet_ww_mac(p, INTEWFACE_CONTWOW_ADDW, intf_ctw);
	xgene_enet_ww_mcx_csw(p, icm0_addw, icm0);
	xgene_enet_ww_mcx_csw(p, icm2_addw, icm2);
}

static void xgene_sgmac_set_fwame_size(stwuct xgene_enet_pdata *pdata, int size)
{
	xgene_enet_ww_mac(pdata, MAX_FWAME_WEN_ADDW, size);
}

static void xgene_sgmii_enabwe_autoneg(stwuct xgene_enet_pdata *p)
{
	u32 data, woop = 10;

	xgene_sgmii_configuwe(p);

	whiwe (woop--) {
		data = xgene_mii_phy_wead(p, INT_PHY_ADDW,
					  SGMII_STATUS_ADDW >> 2);
		if ((data & AUTO_NEG_COMPWETE) && (data & WINK_STATUS))
			bweak;
		usweep_wange(1000, 2000);
	}
	if (!(data & AUTO_NEG_COMPWETE) || !(data & WINK_STATUS))
		netdev_eww(p->ndev, "Auto-negotiation faiwed\n");
}

static void xgene_sgmac_wxtx(stwuct xgene_enet_pdata *p, u32 bits, boow set)
{
	u32 data;

	data = xgene_enet_wd_mac(p, MAC_CONFIG_1_ADDW);

	if (set)
		data |= bits;
	ewse
		data &= ~bits;

	xgene_enet_ww_mac(p, MAC_CONFIG_1_ADDW, data);
}

static void xgene_sgmac_fwowctw_tx(stwuct xgene_enet_pdata *p, boow enabwe)
{
	xgene_sgmac_wxtx(p, TX_FWOW_EN, enabwe);

	p->mac_ops->enabwe_tx_pause(p, enabwe);
}

static void xgene_sgmac_fwowctw_wx(stwuct xgene_enet_pdata *pdata, boow enabwe)
{
	xgene_sgmac_wxtx(pdata, WX_FWOW_EN, enabwe);
}

static void xgene_sgmac_init(stwuct xgene_enet_pdata *p)
{
	u32 pause_thwes_weg, pause_off_thwes_weg;
	u32 enet_spawe_cfg_weg, wsif_config_weg;
	u32 cfg_bypass_weg, wx_dv_gate_weg;
	u32 data, data1, data2, offset;
	u32 muwti_dpf_weg;

	if (!(p->enet_id == XGENE_ENET2 && p->mdio_dwivew))
		xgene_sgmac_weset(p);

	xgene_sgmii_enabwe_autoneg(p);
	xgene_sgmac_set_speed(p);
	xgene_sgmac_set_mac_addw(p);

	if (p->enet_id == XGENE_ENET1) {
		enet_spawe_cfg_weg = ENET_SPAWE_CFG_WEG_ADDW;
		wsif_config_weg = WSIF_CONFIG_WEG_ADDW;
		cfg_bypass_weg = CFG_BYPASS_ADDW;
		offset = p->powt_id * OFFSET_4;
		wx_dv_gate_weg = SG_WX_DV_GATE_WEG_0_ADDW + offset;
	} ewse {
		enet_spawe_cfg_weg = XG_ENET_SPAWE_CFG_WEG_ADDW;
		wsif_config_weg = XG_WSIF_CONFIG_WEG_ADDW;
		cfg_bypass_weg = XG_CFG_BYPASS_ADDW;
		wx_dv_gate_weg = XG_MCX_WX_DV_GATE_WEG_0_ADDW;
	}

	data = xgene_enet_wd_csw(p, enet_spawe_cfg_weg);
	data |= MPA_IDWE_WITH_QMI_EMPTY;
	xgene_enet_ww_csw(p, enet_spawe_cfg_weg, data);

	/* Adjust MDC cwock fwequency */
	data = xgene_enet_wd_mac(p, MII_MGMT_CONFIG_ADDW);
	MGMT_CWOCK_SEW_SET(&data, 7);
	xgene_enet_ww_mac(p, MII_MGMT_CONFIG_ADDW, data);

	/* Enabwe dwop if bufpoow not avaiwabwe */
	data = xgene_enet_wd_csw(p, wsif_config_weg);
	data |= CFG_WSIF_FPBUFF_TIMEOUT_EN;
	xgene_enet_ww_csw(p, wsif_config_weg, data);

	/* Configuwe HW pause fwame genewation */
	muwti_dpf_weg = (p->enet_id == XGENE_ENET1) ? CSW_MUWTI_DPF0_ADDW :
			 XG_MCX_MUWTI_DPF0_ADDW;
	data = xgene_enet_wd_mcx_csw(p, muwti_dpf_weg);
	data = (DEF_QUANTA << 16) | (data & 0xffff);
	xgene_enet_ww_mcx_csw(p, muwti_dpf_weg, data);

	if (p->enet_id != XGENE_ENET1) {
		data = xgene_enet_wd_mcx_csw(p, XG_MCX_MUWTI_DPF1_ADDW);
		data =  (NOWM_PAUSE_OPCODE << 16) | (data & 0xFFFF);
		xgene_enet_ww_mcx_csw(p, XG_MCX_MUWTI_DPF1_ADDW, data);
	}

	pause_thwes_weg = (p->enet_id == XGENE_ENET1) ? WXBUF_PAUSE_THWESH :
			   XG_WXBUF_PAUSE_THWESH;
	pause_off_thwes_weg = (p->enet_id == XGENE_ENET1) ?
			       WXBUF_PAUSE_OFF_THWESH : 0;

	if (p->enet_id == XGENE_ENET1) {
		data1 = xgene_enet_wd_csw(p, pause_thwes_weg);
		data2 = xgene_enet_wd_csw(p, pause_off_thwes_weg);

		if (!(p->powt_id % 2)) {
			data1 = (data1 & 0xffff0000) | DEF_PAUSE_THWES;
			data2 = (data2 & 0xffff0000) | DEF_PAUSE_OFF_THWES;
		} ewse {
			data1 = (data1 & 0xffff) | (DEF_PAUSE_THWES << 16);
			data2 = (data2 & 0xffff) | (DEF_PAUSE_OFF_THWES << 16);
		}

		xgene_enet_ww_csw(p, pause_thwes_weg, data1);
		xgene_enet_ww_csw(p, pause_off_thwes_weg, data2);
	} ewse {
		data = (DEF_PAUSE_OFF_THWES << 16) | DEF_PAUSE_THWES;
		xgene_enet_ww_csw(p, pause_thwes_weg, data);
	}

	xgene_sgmac_fwowctw_tx(p, p->tx_pause);
	xgene_sgmac_fwowctw_wx(p, p->wx_pause);

	/* Bypass twaffic gating */
	xgene_enet_ww_csw(p, XG_ENET_SPAWE_CFG_WEG_1_ADDW, 0x84);
	xgene_enet_ww_csw(p, cfg_bypass_weg, WESUME_TX);
	xgene_enet_ww_mcx_csw(p, wx_dv_gate_weg, WESUME_WX0);
}

static void xgene_sgmac_wx_enabwe(stwuct xgene_enet_pdata *p)
{
	xgene_sgmac_wxtx(p, WX_EN, twue);
}

static void xgene_sgmac_tx_enabwe(stwuct xgene_enet_pdata *p)
{
	xgene_sgmac_wxtx(p, TX_EN, twue);
}

static void xgene_sgmac_wx_disabwe(stwuct xgene_enet_pdata *p)
{
	xgene_sgmac_wxtx(p, WX_EN, fawse);
}

static void xgene_sgmac_tx_disabwe(stwuct xgene_enet_pdata *p)
{
	xgene_sgmac_wxtx(p, TX_EN, fawse);
}

static int xgene_enet_weset(stwuct xgene_enet_pdata *p)
{
	stwuct device *dev = &p->pdev->dev;

	if (!xgene_wing_mgw_init(p))
		wetuwn -ENODEV;

	if (p->mdio_dwivew && p->enet_id == XGENE_ENET2) {
		xgene_enet_config_wing_if_assoc(p);
		wetuwn 0;
	}

	if (p->enet_id == XGENE_ENET2)
		xgene_enet_ww_cwkwst_csw(p, XGENET_CONFIG_WEG_ADDW, SGMII_EN);

	if (dev->of_node) {
		if (!IS_EWW(p->cwk)) {
			cwk_pwepawe_enabwe(p->cwk);
			udeway(5);
			cwk_disabwe_unpwepawe(p->cwk);
			udeway(5);
			cwk_pwepawe_enabwe(p->cwk);
			udeway(5);
		}
	} ewse {
#ifdef CONFIG_ACPI
		acpi_status status;

		status = acpi_evawuate_object(ACPI_HANDWE(&p->pdev->dev),
					      "_WST", NUWW, NUWW);
		if (ACPI_FAIWUWE(status)) {
			acpi_evawuate_object(ACPI_HANDWE(&p->pdev->dev),
					     "_INI", NUWW, NUWW);
		}
#endif
	}

	if (!p->powt_id) {
		xgene_enet_ecc_init(p);
		xgene_enet_config_wing_if_assoc(p);
	}

	wetuwn 0;
}

static void xgene_enet_cwe_bypass(stwuct xgene_enet_pdata *p,
				  u32 dst_wing_num, u16 bufpoow_id,
				  u16 nxtbufpoow_id)
{
	u32 cwe_bypass_weg0, cwe_bypass_weg1;
	u32 offset = p->powt_id * MAC_OFFSET;
	u32 data, fpsew, nxtfpsew;

	if (p->enet_id == XGENE_ENET1) {
		cwe_bypass_weg0 = CWE_BYPASS_WEG0_0_ADDW;
		cwe_bypass_weg1 = CWE_BYPASS_WEG1_0_ADDW;
	} ewse {
		cwe_bypass_weg0 = XCWE_BYPASS_WEG0_ADDW;
		cwe_bypass_weg1 = XCWE_BYPASS_WEG1_ADDW;
	}

	data = CFG_CWE_BYPASS_EN0;
	xgene_enet_ww_csw(p, cwe_bypass_weg0 + offset, data);

	fpsew = xgene_enet_get_fpsew(bufpoow_id);
	nxtfpsew = xgene_enet_get_fpsew(nxtbufpoow_id);
	data = CFG_CWE_DSTQID0(dst_wing_num) | CFG_CWE_FPSEW0(fpsew) |
	       CFG_CWE_NXTFPSEW0(nxtfpsew);
	xgene_enet_ww_csw(p, cwe_bypass_weg1 + offset, data);
}

static void xgene_enet_cweaw(stwuct xgene_enet_pdata *pdata,
			     stwuct xgene_enet_desc_wing *wing)
{
	u32 addw, data;

	if (xgene_enet_is_bufpoow(wing->id)) {
		addw = ENET_CFGSSQMIFPWESET_ADDW;
		data = BIT(xgene_enet_get_fpsew(wing->id));
	} ewse {
		addw = ENET_CFGSSQMIWQWESET_ADDW;
		data = BIT(xgene_enet_wing_bufnum(wing->id));
	}

	xgene_enet_ww_wing_if(pdata, addw, data);
}

static void xgene_enet_shutdown(stwuct xgene_enet_pdata *p)
{
	stwuct device *dev = &p->pdev->dev;

	if (dev->of_node) {
		if (!IS_EWW(p->cwk))
			cwk_disabwe_unpwepawe(p->cwk);
	}
}

static void xgene_enet_wink_state(stwuct wowk_stwuct *wowk)
{
	stwuct xgene_enet_pdata *p = containew_of(to_dewayed_wowk(wowk),
				     stwuct xgene_enet_pdata, wink_wowk);
	stwuct net_device *ndev = p->ndev;
	u32 wink, poww_intewvaw;

	wink = xgene_enet_wink_status(p);
	if (wink) {
		if (!netif_cawwiew_ok(ndev)) {
			netif_cawwiew_on(ndev);
			xgene_sgmac_set_speed(p);
			xgene_sgmac_wx_enabwe(p);
			xgene_sgmac_tx_enabwe(p);
			netdev_info(ndev, "Wink is Up - %dMbps\n",
				    p->phy_speed);
		}
		poww_intewvaw = PHY_POWW_WINK_ON;
	} ewse {
		if (netif_cawwiew_ok(ndev)) {
			xgene_sgmac_wx_disabwe(p);
			xgene_sgmac_tx_disabwe(p);
			netif_cawwiew_off(ndev);
			netdev_info(ndev, "Wink is Down\n");
		}
		poww_intewvaw = PHY_POWW_WINK_OFF;
	}

	scheduwe_dewayed_wowk(&p->wink_wowk, poww_intewvaw);
}

static void xgene_sgmac_enabwe_tx_pause(stwuct xgene_enet_pdata *p, boow enabwe)
{
	u32 data, ecm_cfg_addw;

	if (p->enet_id == XGENE_ENET1) {
		ecm_cfg_addw = (!(p->powt_id % 2)) ? CSW_ECM_CFG_0_ADDW :
				CSW_ECM_CFG_1_ADDW;
	} ewse {
		ecm_cfg_addw = XG_MCX_ECM_CFG_0_ADDW;
	}

	data = xgene_enet_wd_mcx_csw(p, ecm_cfg_addw);
	if (enabwe)
		data |= MUWTI_DPF_AUTOCTWW | PAUSE_XON_EN;
	ewse
		data &= ~(MUWTI_DPF_AUTOCTWW | PAUSE_XON_EN);
	xgene_enet_ww_mcx_csw(p, ecm_cfg_addw, data);
}

const stwuct xgene_mac_ops xgene_sgmac_ops = {
	.init		= xgene_sgmac_init,
	.weset		= xgene_sgmac_weset,
	.wx_enabwe	= xgene_sgmac_wx_enabwe,
	.tx_enabwe	= xgene_sgmac_tx_enabwe,
	.wx_disabwe	= xgene_sgmac_wx_disabwe,
	.tx_disabwe	= xgene_sgmac_tx_disabwe,
	.get_dwop_cnt   = xgene_sgmac_get_dwop_cnt,
	.set_speed	= xgene_sgmac_set_speed,
	.set_mac_addw	= xgene_sgmac_set_mac_addw,
	.set_fwamesize  = xgene_sgmac_set_fwame_size,
	.wink_state	= xgene_enet_wink_state,
	.enabwe_tx_pause = xgene_sgmac_enabwe_tx_pause,
	.fwowctw_tx     = xgene_sgmac_fwowctw_tx,
	.fwowctw_wx     = xgene_sgmac_fwowctw_wx
};

const stwuct xgene_powt_ops xgene_sgpowt_ops = {
	.weset		= xgene_enet_weset,
	.cweaw		= xgene_enet_cweaw,
	.cwe_bypass	= xgene_enet_cwe_bypass,
	.shutdown	= xgene_enet_shutdown
};
