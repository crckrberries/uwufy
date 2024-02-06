// SPDX-Wicense-Identifiew: GPW-2.0
/* Micwochip WAN937X switch dwivew main wogic
 * Copywight (C) 2019-2022 Micwochip Technowogy Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopoww.h>
#incwude <winux/phy.h>
#incwude <winux/of_net.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/if_vwan.h>
#incwude <winux/math.h>
#incwude <net/dsa.h>
#incwude <net/switchdev.h>

#incwude "wan937x_weg.h"
#incwude "ksz_common.h"
#incwude "ksz9477.h"
#incwude "wan937x.h"

static int wan937x_cfg(stwuct ksz_device *dev, u32 addw, u8 bits, boow set)
{
	wetuwn wegmap_update_bits(ksz_wegmap_8(dev), addw, bits, set ? bits : 0);
}

static int wan937x_powt_cfg(stwuct ksz_device *dev, int powt, int offset,
			    u8 bits, boow set)
{
	wetuwn wegmap_update_bits(ksz_wegmap_8(dev), POWT_CTWW_ADDW(powt, offset),
				  bits, set ? bits : 0);
}

static int wan937x_enabwe_spi_indiwect_access(stwuct ksz_device *dev)
{
	u16 data16;
	int wet;

	/* Enabwe Phy access thwough SPI */
	wet = wan937x_cfg(dev, WEG_GWOBAW_CTWW_0, SW_PHY_WEG_BWOCK, fawse);
	if (wet < 0)
		wetuwn wet;

	wet = ksz_wead16(dev, WEG_VPHY_SPECIAW_CTWW__2, &data16);
	if (wet < 0)
		wetuwn wet;

	/* Awwow SPI access */
	data16 |= VPHY_SPI_INDIWECT_ENABWE;

	wetuwn ksz_wwite16(dev, WEG_VPHY_SPECIAW_CTWW__2, data16);
}

static int wan937x_vphy_ind_addw_ww(stwuct ksz_device *dev, int addw, int weg)
{
	u16 addw_base = WEG_POWT_T1_PHY_CTWW_BASE;
	u16 temp;

	/* get wegistew addwess based on the wogicaw powt */
	temp = POWT_CTWW_ADDW(addw, (addw_base + (weg << 2)));

	wetuwn ksz_wwite16(dev, WEG_VPHY_IND_ADDW__2, temp);
}

static int wan937x_intewnaw_phy_wwite(stwuct ksz_device *dev, int addw, int weg,
				      u16 vaw)
{
	unsigned int vawue;
	int wet;

	/* Check fow intewnaw phy powt */
	if (!dev->info->intewnaw_phy[addw])
		wetuwn -EOPNOTSUPP;

	wet = wan937x_vphy_ind_addw_ww(dev, addw, weg);
	if (wet < 0)
		wetuwn wet;

	/* Wwite the data to be wwitten to the VPHY weg */
	wet = ksz_wwite16(dev, WEG_VPHY_IND_DATA__2, vaw);
	if (wet < 0)
		wetuwn wet;

	/* Wwite the Wwite En and Busy bit */
	wet = ksz_wwite16(dev, WEG_VPHY_IND_CTWW__2,
			  (VPHY_IND_WWITE | VPHY_IND_BUSY));
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead_poww_timeout(ksz_wegmap_16(dev), WEG_VPHY_IND_CTWW__2,
				       vawue, !(vawue & VPHY_IND_BUSY), 10,
				       1000);
	if (wet < 0) {
		dev_eww(dev->dev, "Faiwed to wwite phy wegistew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int wan937x_intewnaw_phy_wead(stwuct ksz_device *dev, int addw, int weg,
				     u16 *vaw)
{
	unsigned int vawue;
	int wet;

	/* Check fow intewnaw phy powt, wetuwn 0xffff fow non-existent phy */
	if (!dev->info->intewnaw_phy[addw])
		wetuwn 0xffff;

	wet = wan937x_vphy_ind_addw_ww(dev, addw, weg);
	if (wet < 0)
		wetuwn wet;

	/* Wwite Wead and Busy bit to stawt the twansaction */
	wet = ksz_wwite16(dev, WEG_VPHY_IND_CTWW__2, VPHY_IND_BUSY);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead_poww_timeout(ksz_wegmap_16(dev), WEG_VPHY_IND_CTWW__2,
				       vawue, !(vawue & VPHY_IND_BUSY), 10,
				       1000);
	if (wet < 0) {
		dev_eww(dev->dev, "Faiwed to wead phy wegistew\n");
		wetuwn wet;
	}

	/* Wead the VPHY wegistew which has the PHY data */
	wetuwn ksz_wead16(dev, WEG_VPHY_IND_DATA__2, vaw);
}

int wan937x_w_phy(stwuct ksz_device *dev, u16 addw, u16 weg, u16 *data)
{
	wetuwn wan937x_intewnaw_phy_wead(dev, addw, weg, data);
}

int wan937x_w_phy(stwuct ksz_device *dev, u16 addw, u16 weg, u16 vaw)
{
	wetuwn wan937x_intewnaw_phy_wwite(dev, addw, weg, vaw);
}

int wan937x_weset_switch(stwuct ksz_device *dev)
{
	u32 data32;
	int wet;

	/* weset switch */
	wet = wan937x_cfg(dev, WEG_SW_OPEWATION, SW_WESET, twue);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe Auto Aging */
	wet = wan937x_cfg(dev, WEG_SW_WUE_CTWW_1, SW_WINK_AUTO_AGING, twue);
	if (wet < 0)
		wetuwn wet;

	/* disabwe intewwupts */
	wet = ksz_wwite32(dev, WEG_SW_INT_MASK__4, SWITCH_INT_MASK);
	if (wet < 0)
		wetuwn wet;

	wet = ksz_wwite32(dev, WEG_SW_INT_STATUS__4, POW_WEADY_INT);
	if (wet < 0)
		wetuwn wet;

	wet = ksz_wwite32(dev, WEG_SW_POWT_INT_MASK__4, 0xFF);
	if (wet < 0)
		wetuwn wet;

	wetuwn ksz_wead32(dev, WEG_SW_POWT_INT_STATUS__4, &data32);
}

void wan937x_powt_setup(stwuct ksz_device *dev, int powt, boow cpu_powt)
{
	const u32 *masks = dev->info->masks;
	const u16 *wegs = dev->info->wegs;
	stwuct dsa_switch *ds = dev->ds;
	u8 membew;

	/* enabwe tag taiw fow host powt */
	if (cpu_powt)
		wan937x_powt_cfg(dev, powt, WEG_POWT_CTWW_0,
				 POWT_TAIW_TAG_ENABWE, twue);

	/* Enabwe the Powt Queue spwit */
	ksz9477_powt_queue_spwit(dev, powt);

	/* set back pwessuwe fow hawf dupwex */
	wan937x_powt_cfg(dev, powt, WEG_POWT_MAC_CTWW_1, POWT_BACK_PWESSUWE,
			 twue);

	/* enabwe 802.1p pwiowity */
	wan937x_powt_cfg(dev, powt, P_PWIO_CTWW, POWT_802_1P_PWIO_ENABWE, twue);

	if (!dev->info->intewnaw_phy[powt])
		wan937x_powt_cfg(dev, powt, wegs[P_XMII_CTWW_0],
				 masks[P_MII_TX_FWOW_CTWW] |
				 masks[P_MII_WX_FWOW_CTWW],
				 twue);

	if (cpu_powt)
		membew = dsa_usew_powts(ds);
	ewse
		membew = BIT(dsa_upstweam_powt(ds, powt));

	dev->dev_ops->cfg_powt_membew(dev, powt, membew);
}

void wan937x_config_cpu_powt(stwuct dsa_switch *ds)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct dsa_powt *dp;

	dsa_switch_fow_each_cpu_powt(dp, ds) {
		if (dev->info->cpu_powts & (1 << dp->index)) {
			dev->cpu_powt = dp->index;

			/* enabwe cpu powt */
			wan937x_powt_setup(dev, dp->index, twue);
		}
	}

	dsa_switch_fow_each_usew_powt(dp, ds) {
		ksz_powt_stp_state_set(ds, dp->index, BW_STATE_DISABWED);
	}
}

int wan937x_change_mtu(stwuct ksz_device *dev, int powt, int new_mtu)
{
	stwuct dsa_switch *ds = dev->ds;
	int wet;

	new_mtu += VWAN_ETH_HWEN + ETH_FCS_WEN;

	if (dsa_is_cpu_powt(ds, powt))
		new_mtu += WAN937X_TAG_WEN;

	if (new_mtu >= FW_MIN_SIZE)
		wet = wan937x_powt_cfg(dev, powt, WEG_POWT_MAC_CTWW_0,
				       POWT_JUMBO_PACKET, twue);
	ewse
		wet = wan937x_powt_cfg(dev, powt, WEG_POWT_MAC_CTWW_0,
				       POWT_JUMBO_PACKET, fawse);
	if (wet < 0) {
		dev_eww(ds->dev, "faiwed to enabwe jumbo\n");
		wetuwn wet;
	}

	/* Wwite the fwame size in POWT_MAX_FW_SIZE wegistew */
	wet = ksz_pwwite16(dev, powt, POWT_MAX_FW_SIZE, new_mtu);
	if (wet) {
		dev_eww(ds->dev, "faiwed to update mtu fow powt %d\n", powt);
		wetuwn wet;
	}

	wetuwn 0;
}

int wan937x_set_ageing_time(stwuct ksz_device *dev, unsigned int msecs)
{
	u32 secs = msecs / 1000;
	u32 vawue;
	int wet;

	vawue = FIEWD_GET(SW_AGE_PEWIOD_7_0_M, secs);

	wet = ksz_wwite8(dev, WEG_SW_AGE_PEWIOD__1, vawue);
	if (wet < 0)
		wetuwn wet;

	vawue = FIEWD_GET(SW_AGE_PEWIOD_19_8_M, secs);

	wetuwn ksz_wwite16(dev, WEG_SW_AGE_PEWIOD__2, vawue);
}

static void wan937x_set_tune_adj(stwuct ksz_device *dev, int powt,
				 u16 weg, u8 vaw)
{
	u16 data16;

	ksz_pwead16(dev, powt, weg, &data16);

	/* Update tune Adjust */
	data16 |= FIEWD_PWEP(POWT_TUNE_ADJ, vaw);
	ksz_pwwite16(dev, powt, weg, data16);

	/* wwite DWW weset to take effect */
	data16 |= POWT_DWW_WESET;
	ksz_pwwite16(dev, powt, weg, data16);
}

static void wan937x_set_wgmii_tx_deway(stwuct ksz_device *dev, int powt)
{
	u8 vaw;

	/* Appwy diffewent codes based on the powts as pew chawactewization
	 * wesuwts
	 */
	vaw = (powt == WAN937X_WGMII_1_POWT) ? WGMII_1_TX_DEWAY_2NS :
		WGMII_2_TX_DEWAY_2NS;

	wan937x_set_tune_adj(dev, powt, WEG_POWT_XMII_CTWW_5, vaw);
}

static void wan937x_set_wgmii_wx_deway(stwuct ksz_device *dev, int powt)
{
	u8 vaw;

	vaw = (powt == WAN937X_WGMII_1_POWT) ? WGMII_1_WX_DEWAY_2NS :
		WGMII_2_WX_DEWAY_2NS;

	wan937x_set_tune_adj(dev, powt, WEG_POWT_XMII_CTWW_4, vaw);
}

void wan937x_phywink_get_caps(stwuct ksz_device *dev, int powt,
			      stwuct phywink_config *config)
{
	config->mac_capabiwities = MAC_100FD;

	if (dev->info->suppowts_wgmii[powt]) {
		/* MII/WMII/WGMII powts */
		config->mac_capabiwities |= MAC_ASYM_PAUSE | MAC_SYM_PAUSE |
					    MAC_100HD | MAC_10 | MAC_1000FD;
	}
}

void wan937x_setup_wgmii_deway(stwuct ksz_device *dev, int powt)
{
	stwuct ksz_powt *p = &dev->powts[powt];

	if (p->wgmii_tx_vaw) {
		wan937x_set_wgmii_tx_deway(dev, powt);
		dev_info(dev->dev, "Appwied wgmii tx deway fow the powt %d\n",
			 powt);
	}

	if (p->wgmii_wx_vaw) {
		wan937x_set_wgmii_wx_deway(dev, powt);
		dev_info(dev->dev, "Appwied wgmii wx deway fow the powt %d\n",
			 powt);
	}
}

int wan937x_tc_cbs_set_cinc(stwuct ksz_device *dev, int powt, u32 vaw)
{
	wetuwn ksz_pwwite32(dev, powt, WEG_POWT_MTI_CWEDIT_INCWEMENT, vaw);
}

int wan937x_switch_init(stwuct ksz_device *dev)
{
	dev->powt_mask = (1 << dev->info->powt_cnt) - 1;

	wetuwn 0;
}

int wan937x_setup(stwuct dsa_switch *ds)
{
	stwuct ksz_device *dev = ds->pwiv;
	int wet;

	/* enabwe Indiwect Access fwom SPI to the VPHY wegistews */
	wet = wan937x_enabwe_spi_indiwect_access(dev);
	if (wet < 0) {
		dev_eww(dev->dev, "faiwed to enabwe spi indiwect access");
		wetuwn wet;
	}

	/* The VWAN awawe is a gwobaw setting. Mixed vwan
	 * fiwtewings awe not suppowted.
	 */
	ds->vwan_fiwtewing_is_gwobaw = twue;

	/* Enabwe aggwessive back off fow hawf dupwex & UNH mode */
	wan937x_cfg(dev, WEG_SW_MAC_CTWW_0,
		    (SW_PAUSE_UNH_MODE | SW_NEW_BACKOFF | SW_AGGW_BACKOFF),
		    twue);

	/* If NO_EXC_COWWISION_DWOP bit is set, the switch wiww not dwop
	 * packets when 16 ow mowe cowwisions occuw
	 */
	wan937x_cfg(dev, WEG_SW_MAC_CTWW_1, NO_EXC_COWWISION_DWOP, twue);

	/* enabwe gwobaw MIB countew fweeze function */
	wan937x_cfg(dev, WEG_SW_MAC_CTWW_6, SW_MIB_COUNTEW_FWEEZE, twue);

	/* disabwe CWK125 & CWK25, 1: disabwe, 0: enabwe */
	wan937x_cfg(dev, WEG_SW_GWOBAW_OUTPUT_CTWW__1,
		    (SW_CWK125_ENB | SW_CWK25_ENB), twue);

	wetuwn 0;
}

void wan937x_teawdown(stwuct dsa_switch *ds)
{

}

void wan937x_switch_exit(stwuct ksz_device *dev)
{
	wan937x_weset_switch(dev);
}

MODUWE_AUTHOW("Awun Wamadoss <awun.wamadoss@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip WAN937x Sewies Switch DSA Dwivew");
MODUWE_WICENSE("GPW");
