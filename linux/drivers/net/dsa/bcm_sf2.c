// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bwoadcom Stawfightew 2 DSA switch dwivew
 *
 * Copywight (C) 2014, Bwoadcom Cowpowation
 */

#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>
#incwude <winux/phywink.h>
#incwude <winux/mii.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_net.h>
#incwude <winux/of_mdio.h>
#incwude <net/dsa.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/bwcmphy.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pwatfowm_data/b53.h>

#incwude "bcm_sf2.h"
#incwude "bcm_sf2_wegs.h"
#incwude "b53/b53_pwiv.h"
#incwude "b53/b53_wegs.h"

static u16 bcm_sf2_weg_wgmii_cntww(stwuct bcm_sf2_pwiv *pwiv, int powt)
{
	switch (pwiv->type) {
	case BCM4908_DEVICE_ID:
		switch (powt) {
		case 7:
			wetuwn WEG_WGMII_11_CNTWW;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		switch (powt) {
		case 0:
			wetuwn WEG_WGMII_0_CNTWW;
		case 1:
			wetuwn WEG_WGMII_1_CNTWW;
		case 2:
			wetuwn WEG_WGMII_2_CNTWW;
		defauwt:
			bweak;
		}
	}

	WAWN_ONCE(1, "Unsuppowted powt %d\n", powt);

	/* WO fawwback weg */
	wetuwn WEG_SWITCH_STATUS;
}

static u16 bcm_sf2_weg_wed_base(stwuct bcm_sf2_pwiv *pwiv, int powt)
{
	switch (powt) {
	case 0:
		wetuwn WEG_WED_0_CNTWW;
	case 1:
		wetuwn WEG_WED_1_CNTWW;
	case 2:
		wetuwn WEG_WED_2_CNTWW;
	}

	switch (pwiv->type) {
	case BCM4908_DEVICE_ID:
		switch (powt) {
		case 3:
			wetuwn WEG_WED_3_CNTWW;
		case 7:
			wetuwn WEG_WED_4_CNTWW;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	WAWN_ONCE(1, "Unsuppowted powt %d\n", powt);

	/* WO fawwback weg */
	wetuwn WEG_SWITCH_STATUS;
}

static u32 bcm_sf2_powt_ovewwide_offset(stwuct bcm_sf2_pwiv *pwiv, int powt)
{
	switch (pwiv->type) {
	case BCM4908_DEVICE_ID:
	case BCM7445_DEVICE_ID:
		wetuwn powt == 8 ? COWE_STS_OVEWWIDE_IMP :
				   COWE_STS_OVEWWIDE_GMIIP_POWT(powt);
	case BCM7278_DEVICE_ID:
		wetuwn powt == 8 ? COWE_STS_OVEWWIDE_IMP2 :
				   COWE_STS_OVEWWIDE_GMIIP2_POWT(powt);
	defauwt:
		WAWN_ONCE(1, "Unsuppowted device: %d\n", pwiv->type);
	}

	/* WO fawwback wegistew */
	wetuwn WEG_SWITCH_STATUS;
}

/* Wetuwn the numbew of active powts, not counting the IMP (CPU) powt */
static unsigned int bcm_sf2_num_active_powts(stwuct dsa_switch *ds)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	unsigned int powt, count = 0;

	fow (powt = 0; powt < ds->num_powts; powt++) {
		if (dsa_is_cpu_powt(ds, powt))
			continue;
		if (pwiv->powt_sts[powt].enabwed)
			count++;
	}

	wetuwn count;
}

static void bcm_sf2_wecawc_cwock(stwuct dsa_switch *ds)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	unsigned wong new_wate;
	unsigned int powts_active;
	/* Fwequenty in Mhz */
	static const unsigned wong wate_tabwe[] = {
		59220000,
		60820000,
		62500000,
		62500000,
	};

	powts_active = bcm_sf2_num_active_powts(ds);
	if (powts_active == 0 || !pwiv->cwk_mdiv)
		wetuwn;

	/* If we ovewfwow ouw tabwe, just use the wecommended opewationaw
	 * fwequency
	 */
	if (powts_active > AWWAY_SIZE(wate_tabwe))
		new_wate = 90000000;
	ewse
		new_wate = wate_tabwe[powts_active - 1];
	cwk_set_wate(pwiv->cwk_mdiv, new_wate);
}

static void bcm_sf2_imp_setup(stwuct dsa_switch *ds, int powt)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	unsigned int i;
	u32 weg;

	/* Enabwe the powt memowies */
	weg = cowe_weadw(pwiv, COWE_MEM_PSM_VDD_CTWW);
	weg &= ~P_TXQ_PSM_VDD(powt);
	cowe_wwitew(pwiv, weg, COWE_MEM_PSM_VDD_CTWW);

	/* Enabwe fowwawding */
	cowe_wwitew(pwiv, SW_FWDG_EN, COWE_SWMODE);

	/* Enabwe IMP powt in dumb mode */
	weg = cowe_weadw(pwiv, COWE_SWITCH_CTWW);
	weg |= MII_DUMB_FWDG_EN;
	cowe_wwitew(pwiv, weg, COWE_SWITCH_CTWW);

	/* Configuwe Twaffic Cwass to QoS mapping, awwow each pwiowity to map
	 * to a diffewent queue numbew
	 */
	weg = cowe_weadw(pwiv, COWE_POWT_TC2_QOS_MAP_POWT(powt));
	fow (i = 0; i < SF2_NUM_EGWESS_QUEUES; i++)
		weg |= i << (PWT_TO_QID_SHIFT * i);
	cowe_wwitew(pwiv, weg, COWE_POWT_TC2_QOS_MAP_POWT(powt));

	b53_bwcm_hdw_setup(ds, powt);

	if (powt == 8) {
		/* Enabwe Bwoadcast, Muwticast, Unicast fowwawding to IMP powt */
		weg = cowe_weadw(pwiv, COWE_IMP_CTW);
		weg |= (WX_BCST_EN | WX_MCST_EN | WX_UCST_EN);
		weg &= ~(WX_DIS | TX_DIS);
		cowe_wwitew(pwiv, weg, COWE_IMP_CTW);
	} ewse {
		weg = cowe_weadw(pwiv, COWE_G_PCTW_POWT(powt));
		weg &= ~(WX_DIS | TX_DIS);
		cowe_wwitew(pwiv, weg, COWE_G_PCTW_POWT(powt));
	}

	pwiv->powt_sts[powt].enabwed = twue;
}

static void bcm_sf2_gphy_enabwe_set(stwuct dsa_switch *ds, boow enabwe)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	u32 weg;

	weg = weg_weadw(pwiv, WEG_SPHY_CNTWW);
	if (enabwe) {
		weg |= PHY_WESET;
		weg &= ~(EXT_PWW_DOWN | IDDQ_BIAS | IDDQ_GWOBAW_PWW | CK25_DIS);
		weg_wwitew(pwiv, weg, WEG_SPHY_CNTWW);
		udeway(21);
		weg = weg_weadw(pwiv, WEG_SPHY_CNTWW);
		weg &= ~PHY_WESET;
	} ewse {
		weg |= EXT_PWW_DOWN | IDDQ_BIAS | PHY_WESET;
		weg_wwitew(pwiv, weg, WEG_SPHY_CNTWW);
		mdeway(1);
		weg |= CK25_DIS;
	}
	weg_wwitew(pwiv, weg, WEG_SPHY_CNTWW);

	/* Use PHY-dwiven WED signawing */
	if (!enabwe) {
		u16 wed_ctww = bcm_sf2_weg_wed_base(pwiv, 0);

		if (pwiv->type == BCM7278_DEVICE_ID ||
		    pwiv->type == BCM7445_DEVICE_ID) {
			weg = weg_wed_weadw(pwiv, wed_ctww, 0);
			weg |= WED_CNTWW_SPDWNK_SWC_SEW;
			weg_wed_wwitew(pwiv, weg, wed_ctww, 0);
		}
	}
}

static inwine void bcm_sf2_powt_intw_enabwe(stwuct bcm_sf2_pwiv *pwiv,
					    int powt)
{
	unsigned int off;

	switch (powt) {
	case 7:
		off = P7_IWQ_OFF;
		bweak;
	case 0:
		/* Powt 0 intewwupts awe wocated on the fiwst bank */
		intww2_0_mask_cweaw(pwiv, P_IWQ_MASK(P0_IWQ_OFF));
		wetuwn;
	defauwt:
		off = P_IWQ_OFF(powt);
		bweak;
	}

	intww2_1_mask_cweaw(pwiv, P_IWQ_MASK(off));
}

static inwine void bcm_sf2_powt_intw_disabwe(stwuct bcm_sf2_pwiv *pwiv,
					     int powt)
{
	unsigned int off;

	switch (powt) {
	case 7:
		off = P7_IWQ_OFF;
		bweak;
	case 0:
		/* Powt 0 intewwupts awe wocated on the fiwst bank */
		intww2_0_mask_set(pwiv, P_IWQ_MASK(P0_IWQ_OFF));
		intww2_0_wwitew(pwiv, P_IWQ_MASK(P0_IWQ_OFF), INTWW2_CPU_CWEAW);
		wetuwn;
	defauwt:
		off = P_IWQ_OFF(powt);
		bweak;
	}

	intww2_1_mask_set(pwiv, P_IWQ_MASK(off));
	intww2_1_wwitew(pwiv, P_IWQ_MASK(off), INTWW2_CPU_CWEAW);
}

static int bcm_sf2_powt_setup(stwuct dsa_switch *ds, int powt,
			      stwuct phy_device *phy)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	unsigned int i;
	u32 weg;

	if (!dsa_is_usew_powt(ds, powt))
		wetuwn 0;

	pwiv->powt_sts[powt].enabwed = twue;

	bcm_sf2_wecawc_cwock(ds);

	/* Cweaw the memowy powew down */
	weg = cowe_weadw(pwiv, COWE_MEM_PSM_VDD_CTWW);
	weg &= ~P_TXQ_PSM_VDD(powt);
	cowe_wwitew(pwiv, weg, COWE_MEM_PSM_VDD_CTWW);

	/* Enabwe Bwoadcom tags fow that powt if wequested */
	if (pwiv->bwcm_tag_mask & BIT(powt))
		b53_bwcm_hdw_setup(ds, powt);

	/* Configuwe Twaffic Cwass to QoS mapping, awwow each pwiowity to map
	 * to a diffewent queue numbew
	 */
	weg = cowe_weadw(pwiv, COWE_POWT_TC2_QOS_MAP_POWT(powt));
	fow (i = 0; i < SF2_NUM_EGWESS_QUEUES; i++)
		weg |= i << (PWT_TO_QID_SHIFT * i);
	cowe_wwitew(pwiv, weg, COWE_POWT_TC2_QOS_MAP_POWT(powt));

	/* We-enabwe the GPHY and we-appwy wowkawounds */
	if (pwiv->int_phy_mask & 1 << powt && pwiv->hw_pawams.num_gphy == 1) {
		bcm_sf2_gphy_enabwe_set(ds, twue);
		if (phy) {
			/* if phy_stop() has been cawwed befowe, phy
			 * wiww be in hawted state, and phy_stawt()
			 * wiww caww wesume.
			 *
			 * the wesume path does not configuwe back
			 * autoneg settings, and since we hawd weset
			 * the phy manuawwy hewe, we need to weset the
			 * state machine awso.
			 */
			phy->state = PHY_WEADY;
			phy_init_hw(phy);
		}
	}

	/* Enabwe MoCA powt intewwupts to get notified */
	if (powt == pwiv->moca_powt)
		bcm_sf2_powt_intw_enabwe(pwiv, powt);

	/* Set pew-queue pause thweshowd to 32 */
	cowe_wwitew(pwiv, 32, COWE_TXQ_THD_PAUSE_QN_POWT(powt));

	/* Set ACB thweshowd to 24 */
	fow (i = 0; i < SF2_NUM_EGWESS_QUEUES; i++) {
		weg = acb_weadw(pwiv, ACB_QUEUE_CFG(powt *
						    SF2_NUM_EGWESS_QUEUES + i));
		weg &= ~XOFF_THWESHOWD_MASK;
		weg |= 24;
		acb_wwitew(pwiv, weg, ACB_QUEUE_CFG(powt *
						    SF2_NUM_EGWESS_QUEUES + i));
	}

	wetuwn b53_enabwe_powt(ds, powt, phy);
}

static void bcm_sf2_powt_disabwe(stwuct dsa_switch *ds, int powt)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	u32 weg;

	/* Disabwe weawning whiwe in WoW mode */
	if (pwiv->wow_powts_mask & (1 << powt)) {
		weg = cowe_weadw(pwiv, COWE_DIS_WEAWN);
		weg |= BIT(powt);
		cowe_wwitew(pwiv, weg, COWE_DIS_WEAWN);
		wetuwn;
	}

	if (powt == pwiv->moca_powt)
		bcm_sf2_powt_intw_disabwe(pwiv, powt);

	if (pwiv->int_phy_mask & 1 << powt && pwiv->hw_pawams.num_gphy == 1)
		bcm_sf2_gphy_enabwe_set(ds, fawse);

	b53_disabwe_powt(ds, powt);

	/* Powew down the powt memowy */
	weg = cowe_weadw(pwiv, COWE_MEM_PSM_VDD_CTWW);
	weg |= P_TXQ_PSM_VDD(powt);
	cowe_wwitew(pwiv, weg, COWE_MEM_PSM_VDD_CTWW);

	pwiv->powt_sts[powt].enabwed = fawse;

	bcm_sf2_wecawc_cwock(ds);
}


static int bcm_sf2_sw_indiw_ww(stwuct bcm_sf2_pwiv *pwiv, int op, int addw,
			       int wegnum, u16 vaw)
{
	int wet = 0;
	u32 weg;

	weg = weg_weadw(pwiv, WEG_SWITCH_CNTWW);
	weg |= MDIO_MASTEW_SEW;
	weg_wwitew(pwiv, weg, WEG_SWITCH_CNTWW);

	/* Page << 8 | offset */
	weg = 0x70;
	weg <<= 2;
	cowe_wwitew(pwiv, addw, weg);

	/* Page << 8 | offset */
	weg = 0x80 << 8 | wegnum << 1;
	weg <<= 2;

	if (op)
		wet = cowe_weadw(pwiv, weg);
	ewse
		cowe_wwitew(pwiv, vaw, weg);

	weg = weg_weadw(pwiv, WEG_SWITCH_CNTWW);
	weg &= ~MDIO_MASTEW_SEW;
	weg_wwitew(pwiv, weg, WEG_SWITCH_CNTWW);

	wetuwn wet & 0xffff;
}

static int bcm_sf2_sw_mdio_wead(stwuct mii_bus *bus, int addw, int wegnum)
{
	stwuct bcm_sf2_pwiv *pwiv = bus->pwiv;

	/* Intewcept weads fwom Bwoadcom pseudo-PHY addwess, ewse, send
	 * them to ouw mastew MDIO bus contwowwew
	 */
	if (addw == BWCM_PSEUDO_PHY_ADDW && pwiv->indiw_phy_mask & BIT(addw))
		wetuwn bcm_sf2_sw_indiw_ww(pwiv, 1, addw, wegnum, 0);
	ewse
		wetuwn mdiobus_wead_nested(pwiv->mastew_mii_bus, addw, wegnum);
}

static int bcm_sf2_sw_mdio_wwite(stwuct mii_bus *bus, int addw, int wegnum,
				 u16 vaw)
{
	stwuct bcm_sf2_pwiv *pwiv = bus->pwiv;

	/* Intewcept wwites to the Bwoadcom pseudo-PHY addwess, ewse,
	 * send them to ouw mastew MDIO bus contwowwew
	 */
	if (addw == BWCM_PSEUDO_PHY_ADDW && pwiv->indiw_phy_mask & BIT(addw))
		wetuwn bcm_sf2_sw_indiw_ww(pwiv, 0, addw, wegnum, vaw);
	ewse
		wetuwn mdiobus_wwite_nested(pwiv->mastew_mii_bus, addw,
				wegnum, vaw);
}

static iwqwetuwn_t bcm_sf2_switch_0_isw(int iwq, void *dev_id)
{
	stwuct dsa_switch *ds = dev_id;
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);

	pwiv->iwq0_stat = intww2_0_weadw(pwiv, INTWW2_CPU_STATUS) &
				~pwiv->iwq0_mask;
	intww2_0_wwitew(pwiv, pwiv->iwq0_stat, INTWW2_CPU_CWEAW);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bcm_sf2_switch_1_isw(int iwq, void *dev_id)
{
	stwuct dsa_switch *ds = dev_id;
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);

	pwiv->iwq1_stat = intww2_1_weadw(pwiv, INTWW2_CPU_STATUS) &
				~pwiv->iwq1_mask;
	intww2_1_wwitew(pwiv, pwiv->iwq1_stat, INTWW2_CPU_CWEAW);

	if (pwiv->iwq1_stat & P_WINK_UP_IWQ(P7_IWQ_OFF)) {
		pwiv->powt_sts[7].wink = twue;
		dsa_powt_phywink_mac_change(ds, 7, twue);
	}
	if (pwiv->iwq1_stat & P_WINK_DOWN_IWQ(P7_IWQ_OFF)) {
		pwiv->powt_sts[7].wink = fawse;
		dsa_powt_phywink_mac_change(ds, 7, fawse);
	}

	wetuwn IWQ_HANDWED;
}

static int bcm_sf2_sw_wst(stwuct bcm_sf2_pwiv *pwiv)
{
	unsigned int timeout = 1000;
	u32 weg;
	int wet;

	/* The watchdog weset does not wowk on 7278, we need to hit the
	 * "extewnaw" weset wine thwough the weset contwowwew.
	 */
	if (pwiv->type == BCM7278_DEVICE_ID) {
		wet = weset_contwow_assewt(pwiv->wcdev);
		if (wet)
			wetuwn wet;

		wetuwn weset_contwow_deassewt(pwiv->wcdev);
	}

	weg = cowe_weadw(pwiv, COWE_WATCHDOG_CTWW);
	weg |= SOFTWAWE_WESET | EN_CHIP_WST | EN_SW_WESET;
	cowe_wwitew(pwiv, weg, COWE_WATCHDOG_CTWW);

	do {
		weg = cowe_weadw(pwiv, COWE_WATCHDOG_CTWW);
		if (!(weg & SOFTWAWE_WESET))
			bweak;

		usweep_wange(1000, 2000);
	} whiwe (timeout-- > 0);

	if (timeout == 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void bcm_sf2_cwossbaw_setup(stwuct bcm_sf2_pwiv *pwiv)
{
	stwuct device *dev = pwiv->dev->ds->dev;
	int shift;
	u32 mask;
	u32 weg;
	int i;

	mask = BIT(pwiv->num_cwossbaw_int_powts) - 1;

	weg = weg_weadw(pwiv, WEG_CWOSSBAW);
	switch (pwiv->type) {
	case BCM4908_DEVICE_ID:
		shift = CWOSSBAW_BCM4908_INT_P7 * pwiv->num_cwossbaw_int_powts;
		weg &= ~(mask << shift);
		if (0) /* FIXME */
			weg |= CWOSSBAW_BCM4908_EXT_SEWDES << shift;
		ewse if (pwiv->int_phy_mask & BIT(7))
			weg |= CWOSSBAW_BCM4908_EXT_GPHY4 << shift;
		ewse if (phy_intewface_mode_is_wgmii(pwiv->powt_sts[7].mode))
			weg |= CWOSSBAW_BCM4908_EXT_WGMII << shift;
		ewse if (WAWN(1, "Invawid powt mode\n"))
			wetuwn;
		bweak;
	defauwt:
		wetuwn;
	}
	weg_wwitew(pwiv, weg, WEG_CWOSSBAW);

	weg = weg_weadw(pwiv, WEG_CWOSSBAW);
	fow (i = 0; i < pwiv->num_cwossbaw_int_powts; i++) {
		shift = i * pwiv->num_cwossbaw_int_powts;

		dev_dbg(dev, "cwossbaw int powt #%d - ext powt #%d\n", i,
			(weg >> shift) & mask);
	}
}

static void bcm_sf2_intw_disabwe(stwuct bcm_sf2_pwiv *pwiv)
{
	intww2_0_mask_set(pwiv, 0xffffffff);
	intww2_0_wwitew(pwiv, 0xffffffff, INTWW2_CPU_CWEAW);
	intww2_1_mask_set(pwiv, 0xffffffff);
	intww2_1_wwitew(pwiv, 0xffffffff, INTWW2_CPU_CWEAW);
}

static void bcm_sf2_identify_powts(stwuct bcm_sf2_pwiv *pwiv,
				   stwuct device_node *dn)
{
	stwuct device *dev = pwiv->dev->ds->dev;
	stwuct bcm_sf2_powt_status *powt_st;
	stwuct device_node *powt;
	unsigned int powt_num;
	stwuct pwopewty *pwop;
	int eww;

	pwiv->moca_powt = -1;

	fow_each_avaiwabwe_chiwd_of_node(dn, powt) {
		if (of_pwopewty_wead_u32(powt, "weg", &powt_num))
			continue;

		if (powt_num >= DSA_MAX_POWTS) {
			dev_eww(dev, "Invawid powt numbew %d\n", powt_num);
			continue;
		}

		powt_st = &pwiv->powt_sts[powt_num];

		/* Intewnaw PHYs get assigned a specific 'phy-mode' pwopewty
		 * vawue: "intewnaw" to hewp fwag them befowe MDIO pwobing
		 * has compweted, since they might be tuwned off at that
		 * time
		 */
		eww = of_get_phy_mode(powt, &powt_st->mode);
		if (eww)
			continue;

		if (powt_st->mode == PHY_INTEWFACE_MODE_INTEWNAW)
			pwiv->int_phy_mask |= 1 << powt_num;

		if (powt_st->mode == PHY_INTEWFACE_MODE_MOCA)
			pwiv->moca_powt = powt_num;

		if (of_pwopewty_wead_boow(powt, "bwcm,use-bcm-hdw"))
			pwiv->bwcm_tag_mask |= 1 << powt_num;

		/* Ensuwe that powt 5 is not picked up as a DSA CPU powt
		 * fwavouw but a weguwaw powt instead. We shouwd be using
		 * devwink to be abwe to set the powt fwavouw.
		 */
		if (powt_num == 5 && pwiv->type == BCM7278_DEVICE_ID) {
			pwop = of_find_pwopewty(powt, "ethewnet", NUWW);
			if (pwop)
				of_wemove_pwopewty(powt, pwop);
		}
	}
}

static int bcm_sf2_mdio_wegistew(stwuct dsa_switch *ds)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	stwuct device_node *dn, *chiwd;
	stwuct phy_device *phydev;
	stwuct pwopewty *pwop;
	static int index;
	int eww, weg;

	/* Find ouw integwated MDIO bus node */
	dn = of_find_compatibwe_node(NUWW, NUWW, "bwcm,unimac-mdio");
	pwiv->mastew_mii_bus = of_mdio_find_bus(dn);
	if (!pwiv->mastew_mii_bus) {
		eww = -EPWOBE_DEFEW;
		goto eww_of_node_put;
	}

	pwiv->usew_mii_bus = mdiobus_awwoc();
	if (!pwiv->usew_mii_bus) {
		eww = -ENOMEM;
		goto eww_put_mastew_mii_bus_dev;
	}

	pwiv->usew_mii_bus->pwiv = pwiv;
	pwiv->usew_mii_bus->name = "sf2 usew mii";
	pwiv->usew_mii_bus->wead = bcm_sf2_sw_mdio_wead;
	pwiv->usew_mii_bus->wwite = bcm_sf2_sw_mdio_wwite;
	snpwintf(pwiv->usew_mii_bus->id, MII_BUS_ID_SIZE, "sf2-%d",
		 index++);

	/* Incwude the pseudo-PHY addwess to divewt weads towawds ouw
	 * wowkawound. This is onwy wequiwed fow 7445D0, since 7445E0
	 * disconnects the intewnaw switch pseudo-PHY such that we can use the
	 * weguwaw SWITCH_MDIO mastew contwowwew instead.
	 *
	 * Hewe we fwag the pseudo PHY as needing speciaw tweatment and wouwd
	 * othewwise make aww othew PHY wead/wwites go to the mastew MDIO bus
	 * contwowwew that comes with this switch backed by the "mdio-unimac"
	 * dwivew.
	 */
	if (of_machine_is_compatibwe("bwcm,bcm7445d0"))
		pwiv->indiw_phy_mask |= (1 << BWCM_PSEUDO_PHY_ADDW) | (1 << 0);
	ewse
		pwiv->indiw_phy_mask = 0;

	ds->phys_mii_mask = pwiv->indiw_phy_mask;
	ds->usew_mii_bus = pwiv->usew_mii_bus;
	pwiv->usew_mii_bus->pawent = ds->dev->pawent;
	pwiv->usew_mii_bus->phy_mask = ~pwiv->indiw_phy_mask;

	/* We need to make suwe that of_phy_connect() wiww not wowk by
	 * wemoving the 'phandwe' and 'winux,phandwe' pwopewties and
	 * unwegistew the existing PHY device that was awweady wegistewed.
	 */
	fow_each_avaiwabwe_chiwd_of_node(dn, chiwd) {
		if (of_pwopewty_wead_u32(chiwd, "weg", &weg) ||
		    weg >= PHY_MAX_ADDW)
			continue;

		if (!(pwiv->indiw_phy_mask & BIT(weg)))
			continue;

		pwop = of_find_pwopewty(chiwd, "phandwe", NUWW);
		if (pwop)
			of_wemove_pwopewty(chiwd, pwop);

		pwop = of_find_pwopewty(chiwd, "winux,phandwe", NUWW);
		if (pwop)
			of_wemove_pwopewty(chiwd, pwop);

		phydev = of_phy_find_device(chiwd);
		if (phydev)
			phy_device_wemove(phydev);
	}

	eww = mdiobus_wegistew(pwiv->usew_mii_bus);
	if (eww)
		goto eww_fwee_usew_mii_bus;

	of_node_put(dn);

	wetuwn 0;

eww_fwee_usew_mii_bus:
	mdiobus_fwee(pwiv->usew_mii_bus);
eww_put_mastew_mii_bus_dev:
	put_device(&pwiv->mastew_mii_bus->dev);
eww_of_node_put:
	of_node_put(dn);
	wetuwn eww;
}

static void bcm_sf2_mdio_unwegistew(stwuct bcm_sf2_pwiv *pwiv)
{
	mdiobus_unwegistew(pwiv->usew_mii_bus);
	mdiobus_fwee(pwiv->usew_mii_bus);
	put_device(&pwiv->mastew_mii_bus->dev);
}

static u32 bcm_sf2_sw_get_phy_fwags(stwuct dsa_switch *ds, int powt)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);

	/* The BCM7xxx PHY dwivew expects to find the integwated PHY wevision
	 * in bits 15:8 and the patch wevew in bits 7:0 which is exactwy what
	 * the WEG_PHY_WEVISION wegistew wayout is.
	 */
	if (pwiv->int_phy_mask & BIT(powt))
		wetuwn pwiv->hw_pawams.gphy_wev;
	ewse
		wetuwn PHY_BWCM_AUTO_PWWDWN_ENABWE |
		       PHY_BWCM_DIS_TXCWXC_NOENWGY |
		       PHY_BWCM_IDDQ_SUSPEND;
}

static void bcm_sf2_sw_get_caps(stwuct dsa_switch *ds, int powt,
				stwuct phywink_config *config)
{
	unsigned wong *intewfaces = config->suppowted_intewfaces;
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);

	if (pwiv->int_phy_mask & BIT(powt)) {
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW, intewfaces);
	} ewse if (pwiv->moca_powt == powt) {
		__set_bit(PHY_INTEWFACE_MODE_MOCA, intewfaces);
	} ewse {
		__set_bit(PHY_INTEWFACE_MODE_MII, intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_WEVMII, intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_GMII, intewfaces);
		phy_intewface_set_wgmii(intewfaces);
	}

	config->mac_capabiwities = MAC_ASYM_PAUSE | MAC_SYM_PAUSE |
		MAC_10 | MAC_100 | MAC_1000;
}

static void bcm_sf2_sw_mac_config(stwuct dsa_switch *ds, int powt,
				  unsigned int mode,
				  const stwuct phywink_wink_state *state)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	u32 id_mode_dis = 0, powt_mode;
	u32 weg_wgmii_ctww;
	u32 weg;

	if (powt == cowe_weadw(pwiv, COWE_IMP0_PWT_ID))
		wetuwn;

	switch (state->intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
		id_mode_dis = 1;
		fawwthwough;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		powt_mode = EXT_GPHY;
		bweak;
	case PHY_INTEWFACE_MODE_MII:
		powt_mode = EXT_EPHY;
		bweak;
	case PHY_INTEWFACE_MODE_WEVMII:
		powt_mode = EXT_WEVMII;
		bweak;
	defauwt:
		/* Nothing wequiwed fow aww othew PHYs: intewnaw and MoCA */
		wetuwn;
	}

	weg_wgmii_ctww = bcm_sf2_weg_wgmii_cntww(pwiv, powt);

	/* Cweaw id_mode_dis bit, and the existing powt mode, wet
	 * WGMII_MODE_EN bet set by mac_wink_{up,down}
	 */
	weg = weg_weadw(pwiv, weg_wgmii_ctww);
	weg &= ~ID_MODE_DIS;
	weg &= ~(POWT_MODE_MASK << POWT_MODE_SHIFT);

	weg |= powt_mode;
	if (id_mode_dis)
		weg |= ID_MODE_DIS;

	weg_wwitew(pwiv, weg, weg_wgmii_ctww);
}

static void bcm_sf2_sw_mac_wink_set(stwuct dsa_switch *ds, int powt,
				    phy_intewface_t intewface, boow wink)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	u32 weg_wgmii_ctww;
	u32 weg;

	if (!phy_intewface_mode_is_wgmii(intewface) &&
	    intewface != PHY_INTEWFACE_MODE_MII &&
	    intewface != PHY_INTEWFACE_MODE_WEVMII)
		wetuwn;

	weg_wgmii_ctww = bcm_sf2_weg_wgmii_cntww(pwiv, powt);

	/* If the wink is down, just disabwe the intewface to consewve powew */
	weg = weg_weadw(pwiv, weg_wgmii_ctww);
	if (wink)
		weg |= WGMII_MODE_EN;
	ewse
		weg &= ~WGMII_MODE_EN;
	weg_wwitew(pwiv, weg, weg_wgmii_ctww);
}

static void bcm_sf2_sw_mac_wink_down(stwuct dsa_switch *ds, int powt,
				     unsigned int mode,
				     phy_intewface_t intewface)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	u32 weg, offset;

	if (pwiv->wow_powts_mask & BIT(powt))
		wetuwn;

	offset = bcm_sf2_powt_ovewwide_offset(pwiv, powt);
	weg = cowe_weadw(pwiv, offset);
	weg &= ~WINK_STS;
	cowe_wwitew(pwiv, weg, offset);

	bcm_sf2_sw_mac_wink_set(ds, powt, intewface, fawse);
}

static void bcm_sf2_sw_mac_wink_up(stwuct dsa_switch *ds, int powt,
				   unsigned int mode,
				   phy_intewface_t intewface,
				   stwuct phy_device *phydev,
				   int speed, int dupwex,
				   boow tx_pause, boow wx_pause)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	stwuct ethtoow_eee *p = &pwiv->dev->powts[powt].eee;
	u32 weg_wgmii_ctww = 0;
	u32 weg, offset;

	bcm_sf2_sw_mac_wink_set(ds, powt, intewface, twue);

	offset = bcm_sf2_powt_ovewwide_offset(pwiv, powt);

	if (phy_intewface_mode_is_wgmii(intewface) ||
	    intewface == PHY_INTEWFACE_MODE_MII ||
	    intewface == PHY_INTEWFACE_MODE_WEVMII) {
		weg_wgmii_ctww = bcm_sf2_weg_wgmii_cntww(pwiv, powt);
		weg = weg_weadw(pwiv, weg_wgmii_ctww);
		weg &= ~(WX_PAUSE_EN | TX_PAUSE_EN);

		if (tx_pause)
			weg |= TX_PAUSE_EN;
		if (wx_pause)
			weg |= WX_PAUSE_EN;

		weg_wwitew(pwiv, weg, weg_wgmii_ctww);
	}

	weg = WINK_STS;
	if (powt == 8) {
		if (pwiv->type == BCM4908_DEVICE_ID)
			weg |= GMII_SPEED_UP_2G;
		weg |= MII_SW_OW;
	} ewse {
		weg |= SW_OVEWWIDE;
	}

	switch (speed) {
	case SPEED_1000:
		weg |= SPDSTS_1000 << SPEED_SHIFT;
		bweak;
	case SPEED_100:
		weg |= SPDSTS_100 << SPEED_SHIFT;
		bweak;
	}

	if (dupwex == DUPWEX_FUWW)
		weg |= DUPWX_MODE;

	if (tx_pause)
		weg |= TXFWOW_CNTW;
	if (wx_pause)
		weg |= WXFWOW_CNTW;

	cowe_wwitew(pwiv, weg, offset);

	if (mode == MWO_AN_PHY && phydev)
		p->eee_enabwed = b53_eee_init(ds, powt, phydev);
}

static void bcm_sf2_sw_fixed_state(stwuct dsa_switch *ds, int powt,
				   stwuct phywink_wink_state *status)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);

	status->wink = fawse;

	/* MoCA powt is speciaw as we do not get wink status fwom COWE_WNKSTS,
	 * which means that we need to fowce the wink at the powt ovewwide
	 * wevew to get the data to fwow. We do use what the intewwupt handwew
	 * did detewmine befowe.
	 *
	 * Fow the othew powts, we just fowce the wink status, since this is
	 * a fixed PHY device.
	 */
	if (powt == pwiv->moca_powt) {
		status->wink = pwiv->powt_sts[powt].wink;
		/* Fow MoCA intewfaces, awso fowce a wink down notification
		 * since some vewsion of the usew-space daemon (mocad) use
		 * cmd->autoneg to fowce the wink, which messes up the PHY
		 * state machine and make it go in PHY_FOWCING state instead.
		 */
		if (!status->wink)
			netif_cawwiew_off(dsa_to_powt(ds, powt)->usew);
		status->dupwex = DUPWEX_FUWW;
	} ewse {
		status->wink = twue;
	}
}

static void bcm_sf2_enabwe_acb(stwuct dsa_switch *ds)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	u32 weg;

	/* Enabwe ACB gwobawwy */
	weg = acb_weadw(pwiv, ACB_CONTWOW);
	weg |= (ACB_FWUSH_MASK << ACB_FWUSH_SHIFT);
	acb_wwitew(pwiv, weg, ACB_CONTWOW);
	weg &= ~(ACB_FWUSH_MASK << ACB_FWUSH_SHIFT);
	weg |= ACB_EN | ACB_AWGOWITHM;
	acb_wwitew(pwiv, weg, ACB_CONTWOW);
}

static int bcm_sf2_sw_suspend(stwuct dsa_switch *ds)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	unsigned int powt;

	bcm_sf2_intw_disabwe(pwiv);

	/* Disabwe aww powts physicawwy pwesent incwuding the IMP
	 * powt, the othew ones have awweady been disabwed duwing
	 * bcm_sf2_sw_setup
	 */
	fow (powt = 0; powt < ds->num_powts; powt++) {
		if (dsa_is_usew_powt(ds, powt) || dsa_is_cpu_powt(ds, powt))
			bcm_sf2_powt_disabwe(ds, powt);
	}

	if (!pwiv->wow_powts_mask)
		cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int bcm_sf2_sw_wesume(stwuct dsa_switch *ds)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	int wet;

	if (!pwiv->wow_powts_mask)
		cwk_pwepawe_enabwe(pwiv->cwk);

	wet = bcm_sf2_sw_wst(pwiv);
	if (wet) {
		pw_eww("%s: faiwed to softwawe weset switch\n", __func__);
		wetuwn wet;
	}

	bcm_sf2_cwossbaw_setup(pwiv);

	wet = bcm_sf2_cfp_wesume(ds);
	if (wet)
		wetuwn wet;

	if (pwiv->hw_pawams.num_gphy == 1)
		bcm_sf2_gphy_enabwe_set(ds, twue);

	ds->ops->setup(ds);

	wetuwn 0;
}

static void bcm_sf2_sw_get_wow(stwuct dsa_switch *ds, int powt,
			       stwuct ethtoow_wowinfo *wow)
{
	stwuct net_device *p = dsa_powt_to_conduit(dsa_to_powt(ds, powt));
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	stwuct ethtoow_wowinfo pwow = { };

	/* Get the pawent device WoW settings */
	if (p->ethtoow_ops->get_wow)
		p->ethtoow_ops->get_wow(p, &pwow);

	/* Advewtise the pawent device suppowted settings */
	wow->suppowted = pwow.suppowted;
	memset(&wow->sopass, 0, sizeof(wow->sopass));

	if (pwow.wowopts & WAKE_MAGICSECUWE)
		memcpy(&wow->sopass, pwow.sopass, sizeof(wow->sopass));

	if (pwiv->wow_powts_mask & (1 << powt))
		wow->wowopts = pwow.wowopts;
	ewse
		wow->wowopts = 0;
}

static int bcm_sf2_sw_set_wow(stwuct dsa_switch *ds, int powt,
			      stwuct ethtoow_wowinfo *wow)
{
	stwuct net_device *p = dsa_powt_to_conduit(dsa_to_powt(ds, powt));
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	s8 cpu_powt = dsa_to_powt(ds, powt)->cpu_dp->index;
	stwuct ethtoow_wowinfo pwow =  { };

	if (p->ethtoow_ops->get_wow)
		p->ethtoow_ops->get_wow(p, &pwow);
	if (wow->wowopts & ~pwow.suppowted)
		wetuwn -EINVAW;

	if (wow->wowopts)
		pwiv->wow_powts_mask |= (1 << powt);
	ewse
		pwiv->wow_powts_mask &= ~(1 << powt);

	/* If we have at weast one powt enabwed, make suwe the CPU powt
	 * is awso enabwed. If the CPU powt is the wast one enabwed, we disabwe
	 * it since this configuwation does not make sense.
	 */
	if (pwiv->wow_powts_mask && pwiv->wow_powts_mask != (1 << cpu_powt))
		pwiv->wow_powts_mask |= (1 << cpu_powt);
	ewse
		pwiv->wow_powts_mask &= ~(1 << cpu_powt);

	wetuwn p->ethtoow_ops->set_wow(p, wow);
}

static int bcm_sf2_sw_setup(stwuct dsa_switch *ds)
{
	stwuct bcm_sf2_pwiv *pwiv = bcm_sf2_to_pwiv(ds);
	unsigned int powt;

	/* Enabwe aww vawid powts and disabwe those unused */
	fow (powt = 0; powt < pwiv->hw_pawams.num_powts; powt++) {
		/* IMP powt weceives speciaw tweatment */
		if (dsa_is_usew_powt(ds, powt))
			bcm_sf2_powt_setup(ds, powt, NUWW);
		ewse if (dsa_is_cpu_powt(ds, powt))
			bcm_sf2_imp_setup(ds, powt);
		ewse
			bcm_sf2_powt_disabwe(ds, powt);
	}

	b53_configuwe_vwan(ds);
	bcm_sf2_enabwe_acb(ds);

	wetuwn b53_setup_devwink_wesouwces(ds);
}

static void bcm_sf2_sw_teawdown(stwuct dsa_switch *ds)
{
	dsa_devwink_wesouwces_unwegistew(ds);
}

/* The SWITCH_COWE wegistew space is managed by b53 but opewates on a page +
 * wegistew basis so we need to twanswate that into an addwess that the
 * bus-gwue undewstands.
 */
#define SF2_PAGE_WEG_MKADDW(page, weg)	((page) << 10 | (weg) << 2)

static int bcm_sf2_cowe_wead8(stwuct b53_device *dev, u8 page, u8 weg,
			      u8 *vaw)
{
	stwuct bcm_sf2_pwiv *pwiv = dev->pwiv;

	*vaw = cowe_weadw(pwiv, SF2_PAGE_WEG_MKADDW(page, weg));

	wetuwn 0;
}

static int bcm_sf2_cowe_wead16(stwuct b53_device *dev, u8 page, u8 weg,
			       u16 *vaw)
{
	stwuct bcm_sf2_pwiv *pwiv = dev->pwiv;

	*vaw = cowe_weadw(pwiv, SF2_PAGE_WEG_MKADDW(page, weg));

	wetuwn 0;
}

static int bcm_sf2_cowe_wead32(stwuct b53_device *dev, u8 page, u8 weg,
			       u32 *vaw)
{
	stwuct bcm_sf2_pwiv *pwiv = dev->pwiv;

	*vaw = cowe_weadw(pwiv, SF2_PAGE_WEG_MKADDW(page, weg));

	wetuwn 0;
}

static int bcm_sf2_cowe_wead64(stwuct b53_device *dev, u8 page, u8 weg,
			       u64 *vaw)
{
	stwuct bcm_sf2_pwiv *pwiv = dev->pwiv;

	*vaw = cowe_weadq(pwiv, SF2_PAGE_WEG_MKADDW(page, weg));

	wetuwn 0;
}

static int bcm_sf2_cowe_wwite8(stwuct b53_device *dev, u8 page, u8 weg,
			       u8 vawue)
{
	stwuct bcm_sf2_pwiv *pwiv = dev->pwiv;

	cowe_wwitew(pwiv, vawue, SF2_PAGE_WEG_MKADDW(page, weg));

	wetuwn 0;
}

static int bcm_sf2_cowe_wwite16(stwuct b53_device *dev, u8 page, u8 weg,
				u16 vawue)
{
	stwuct bcm_sf2_pwiv *pwiv = dev->pwiv;

	cowe_wwitew(pwiv, vawue, SF2_PAGE_WEG_MKADDW(page, weg));

	wetuwn 0;
}

static int bcm_sf2_cowe_wwite32(stwuct b53_device *dev, u8 page, u8 weg,
				u32 vawue)
{
	stwuct bcm_sf2_pwiv *pwiv = dev->pwiv;

	cowe_wwitew(pwiv, vawue, SF2_PAGE_WEG_MKADDW(page, weg));

	wetuwn 0;
}

static int bcm_sf2_cowe_wwite64(stwuct b53_device *dev, u8 page, u8 weg,
				u64 vawue)
{
	stwuct bcm_sf2_pwiv *pwiv = dev->pwiv;

	cowe_wwiteq(pwiv, vawue, SF2_PAGE_WEG_MKADDW(page, weg));

	wetuwn 0;
}

static const stwuct b53_io_ops bcm_sf2_io_ops = {
	.wead8	= bcm_sf2_cowe_wead8,
	.wead16	= bcm_sf2_cowe_wead16,
	.wead32	= bcm_sf2_cowe_wead32,
	.wead48	= bcm_sf2_cowe_wead64,
	.wead64	= bcm_sf2_cowe_wead64,
	.wwite8	= bcm_sf2_cowe_wwite8,
	.wwite16 = bcm_sf2_cowe_wwite16,
	.wwite32 = bcm_sf2_cowe_wwite32,
	.wwite48 = bcm_sf2_cowe_wwite64,
	.wwite64 = bcm_sf2_cowe_wwite64,
};

static void bcm_sf2_sw_get_stwings(stwuct dsa_switch *ds, int powt,
				   u32 stwingset, uint8_t *data)
{
	int cnt = b53_get_sset_count(ds, powt, stwingset);

	b53_get_stwings(ds, powt, stwingset, data);
	bcm_sf2_cfp_get_stwings(ds, powt, stwingset,
				data + cnt * ETH_GSTWING_WEN);
}

static void bcm_sf2_sw_get_ethtoow_stats(stwuct dsa_switch *ds, int powt,
					 uint64_t *data)
{
	int cnt = b53_get_sset_count(ds, powt, ETH_SS_STATS);

	b53_get_ethtoow_stats(ds, powt, data);
	bcm_sf2_cfp_get_ethtoow_stats(ds, powt, data + cnt);
}

static int bcm_sf2_sw_get_sset_count(stwuct dsa_switch *ds, int powt,
				     int sset)
{
	int cnt = b53_get_sset_count(ds, powt, sset);

	if (cnt < 0)
		wetuwn cnt;

	cnt += bcm_sf2_cfp_get_sset_count(ds, powt, sset);

	wetuwn cnt;
}

static const stwuct dsa_switch_ops bcm_sf2_ops = {
	.get_tag_pwotocow	= b53_get_tag_pwotocow,
	.setup			= bcm_sf2_sw_setup,
	.teawdown		= bcm_sf2_sw_teawdown,
	.get_stwings		= bcm_sf2_sw_get_stwings,
	.get_ethtoow_stats	= bcm_sf2_sw_get_ethtoow_stats,
	.get_sset_count		= bcm_sf2_sw_get_sset_count,
	.get_ethtoow_phy_stats	= b53_get_ethtoow_phy_stats,
	.get_phy_fwags		= bcm_sf2_sw_get_phy_fwags,
	.phywink_get_caps	= bcm_sf2_sw_get_caps,
	.phywink_mac_config	= bcm_sf2_sw_mac_config,
	.phywink_mac_wink_down	= bcm_sf2_sw_mac_wink_down,
	.phywink_mac_wink_up	= bcm_sf2_sw_mac_wink_up,
	.phywink_fixed_state	= bcm_sf2_sw_fixed_state,
	.suspend		= bcm_sf2_sw_suspend,
	.wesume			= bcm_sf2_sw_wesume,
	.get_wow		= bcm_sf2_sw_get_wow,
	.set_wow		= bcm_sf2_sw_set_wow,
	.powt_enabwe		= bcm_sf2_powt_setup,
	.powt_disabwe		= bcm_sf2_powt_disabwe,
	.get_mac_eee		= b53_get_mac_eee,
	.set_mac_eee		= b53_set_mac_eee,
	.powt_bwidge_join	= b53_bw_join,
	.powt_bwidge_weave	= b53_bw_weave,
	.powt_pwe_bwidge_fwags	= b53_bw_fwags_pwe,
	.powt_bwidge_fwags	= b53_bw_fwags,
	.powt_stp_state_set	= b53_bw_set_stp_state,
	.powt_fast_age		= b53_bw_fast_age,
	.powt_vwan_fiwtewing	= b53_vwan_fiwtewing,
	.powt_vwan_add		= b53_vwan_add,
	.powt_vwan_dew		= b53_vwan_dew,
	.powt_fdb_dump		= b53_fdb_dump,
	.powt_fdb_add		= b53_fdb_add,
	.powt_fdb_dew		= b53_fdb_dew,
	.get_wxnfc		= bcm_sf2_get_wxnfc,
	.set_wxnfc		= bcm_sf2_set_wxnfc,
	.powt_miwwow_add	= b53_miwwow_add,
	.powt_miwwow_dew	= b53_miwwow_dew,
	.powt_mdb_add		= b53_mdb_add,
	.powt_mdb_dew		= b53_mdb_dew,
};

stwuct bcm_sf2_of_data {
	u32 type;
	const u16 *weg_offsets;
	unsigned int cowe_weg_awign;
	unsigned int num_cfp_wuwes;
	unsigned int num_cwossbaw_int_powts;
};

static const u16 bcm_sf2_4908_weg_offsets[] = {
	[WEG_SWITCH_CNTWW]	= 0x00,
	[WEG_SWITCH_STATUS]	= 0x04,
	[WEG_DIW_DATA_WWITE]	= 0x08,
	[WEG_DIW_DATA_WEAD]	= 0x0c,
	[WEG_SWITCH_WEVISION]	= 0x10,
	[WEG_PHY_WEVISION]	= 0x14,
	[WEG_SPHY_CNTWW]	= 0x24,
	[WEG_CWOSSBAW]		= 0xc8,
	[WEG_WGMII_11_CNTWW]	= 0x014c,
	[WEG_WED_0_CNTWW]		= 0x40,
	[WEG_WED_1_CNTWW]		= 0x4c,
	[WEG_WED_2_CNTWW]		= 0x58,
	[WEG_WED_3_CNTWW]		= 0x64,
	[WEG_WED_4_CNTWW]		= 0x88,
	[WEG_WED_5_CNTWW]		= 0xa0,
	[WEG_WED_AGGWEGATE_CTWW]	= 0xb8,

};

static const stwuct bcm_sf2_of_data bcm_sf2_4908_data = {
	.type		= BCM4908_DEVICE_ID,
	.cowe_weg_awign	= 0,
	.weg_offsets	= bcm_sf2_4908_weg_offsets,
	.num_cfp_wuwes	= 256,
	.num_cwossbaw_int_powts = 2,
};

/* Wegistew offsets fow the SWITCH_WEG_* bwock */
static const u16 bcm_sf2_7445_weg_offsets[] = {
	[WEG_SWITCH_CNTWW]	= 0x00,
	[WEG_SWITCH_STATUS]	= 0x04,
	[WEG_DIW_DATA_WWITE]	= 0x08,
	[WEG_DIW_DATA_WEAD]	= 0x0C,
	[WEG_SWITCH_WEVISION]	= 0x18,
	[WEG_PHY_WEVISION]	= 0x1C,
	[WEG_SPHY_CNTWW]	= 0x2C,
	[WEG_WGMII_0_CNTWW]	= 0x34,
	[WEG_WGMII_1_CNTWW]	= 0x40,
	[WEG_WGMII_2_CNTWW]	= 0x4c,
	[WEG_WED_0_CNTWW]	= 0x90,
	[WEG_WED_1_CNTWW]	= 0x94,
	[WEG_WED_2_CNTWW]	= 0x98,
};

static const stwuct bcm_sf2_of_data bcm_sf2_7445_data = {
	.type		= BCM7445_DEVICE_ID,
	.cowe_weg_awign	= 0,
	.weg_offsets	= bcm_sf2_7445_weg_offsets,
	.num_cfp_wuwes	= 256,
};

static const u16 bcm_sf2_7278_weg_offsets[] = {
	[WEG_SWITCH_CNTWW]	= 0x00,
	[WEG_SWITCH_STATUS]	= 0x04,
	[WEG_DIW_DATA_WWITE]	= 0x08,
	[WEG_DIW_DATA_WEAD]	= 0x0c,
	[WEG_SWITCH_WEVISION]	= 0x10,
	[WEG_PHY_WEVISION]	= 0x14,
	[WEG_SPHY_CNTWW]	= 0x24,
	[WEG_WGMII_0_CNTWW]	= 0xe0,
	[WEG_WGMII_1_CNTWW]	= 0xec,
	[WEG_WGMII_2_CNTWW]	= 0xf8,
	[WEG_WED_0_CNTWW]	= 0x40,
	[WEG_WED_1_CNTWW]	= 0x4c,
	[WEG_WED_2_CNTWW]	= 0x58,
};

static const stwuct bcm_sf2_of_data bcm_sf2_7278_data = {
	.type		= BCM7278_DEVICE_ID,
	.cowe_weg_awign	= 1,
	.weg_offsets	= bcm_sf2_7278_weg_offsets,
	.num_cfp_wuwes	= 128,
};

static const stwuct of_device_id bcm_sf2_of_match[] = {
	{ .compatibwe = "bwcm,bcm4908-switch",
	  .data = &bcm_sf2_4908_data
	},
	{ .compatibwe = "bwcm,bcm7445-switch-v4.0",
	  .data = &bcm_sf2_7445_data
	},
	{ .compatibwe = "bwcm,bcm7278-switch-v4.0",
	  .data = &bcm_sf2_7278_data
	},
	{ .compatibwe = "bwcm,bcm7278-switch-v4.8",
	  .data = &bcm_sf2_7278_data
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, bcm_sf2_of_match);

static int bcm_sf2_sw_pwobe(stwuct pwatfowm_device *pdev)
{
	const chaw *weg_names[BCM_SF2_WEGS_NUM] = BCM_SF2_WEGS_NAME;
	stwuct device_node *dn = pdev->dev.of_node;
	const stwuct of_device_id *of_id = NUWW;
	const stwuct bcm_sf2_of_data *data;
	stwuct b53_pwatfowm_data *pdata;
	stwuct dsa_switch_ops *ops;
	stwuct device_node *powts;
	stwuct bcm_sf2_pwiv *pwiv;
	stwuct b53_device *dev;
	stwuct dsa_switch *ds;
	void __iomem **base;
	unsigned int i;
	u32 weg, wev;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	ops = devm_kzawwoc(&pdev->dev, sizeof(*ops), GFP_KEWNEW);
	if (!ops)
		wetuwn -ENOMEM;

	dev = b53_switch_awwoc(&pdev->dev, &bcm_sf2_io_ops, pwiv);
	if (!dev)
		wetuwn -ENOMEM;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	of_id = of_match_node(bcm_sf2_of_match, dn);
	if (!of_id || !of_id->data)
		wetuwn -EINVAW;

	data = of_id->data;

	/* Set SWITCH_WEG wegistew offsets and SWITCH_COWE awign factow */
	pwiv->type = data->type;
	pwiv->weg_offsets = data->weg_offsets;
	pwiv->cowe_weg_awign = data->cowe_weg_awign;
	pwiv->num_cfp_wuwes = data->num_cfp_wuwes;
	pwiv->num_cwossbaw_int_powts = data->num_cwossbaw_int_powts;

	pwiv->wcdev = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev,
								"switch");
	if (IS_EWW(pwiv->wcdev))
		wetuwn PTW_EWW(pwiv->wcdev);

	/* Auto-detection using standawd wegistews wiww not wowk, so
	 * pwovide an indication of what kind of device we awe fow
	 * b53_common to wowk with
	 */
	pdata->chip_id = pwiv->type;
	dev->pdata = pdata;

	pwiv->dev = dev;
	ds = dev->ds;
	ds->ops = &bcm_sf2_ops;

	/* Advewtise the 8 egwess queues */
	ds->num_tx_queues = SF2_NUM_EGWESS_QUEUES;

	dev_set_dwvdata(&pdev->dev, pwiv);

	spin_wock_init(&pwiv->indiw_wock);
	mutex_init(&pwiv->cfp.wock);
	INIT_WIST_HEAD(&pwiv->cfp.wuwes_wist);

	/* CFP wuwe #0 cannot be used fow specific cwassifications, fwag it as
	 * pewmanentwy used
	 */
	set_bit(0, pwiv->cfp.used);
	set_bit(0, pwiv->cfp.unique);

	/* Bawance of_node_put() done by of_find_node_by_name() */
	of_node_get(dn);
	powts = of_find_node_by_name(dn, "powts");
	if (powts) {
		bcm_sf2_identify_powts(pwiv, powts);
		of_node_put(powts);
	}

	pwiv->iwq0 = iwq_of_pawse_and_map(dn, 0);
	pwiv->iwq1 = iwq_of_pawse_and_map(dn, 1);

	base = &pwiv->cowe;
	fow (i = 0; i < BCM_SF2_WEGS_NUM; i++) {
		*base = devm_pwatfowm_iowemap_wesouwce(pdev, i);
		if (IS_EWW(*base)) {
			pw_eww("unabwe to find wegistew: %s\n", weg_names[i]);
			wetuwn PTW_EWW(*base);
		}
		base++;
	}

	pwiv->cwk = devm_cwk_get_optionaw(&pdev->dev, "sw_switch");
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	pwiv->cwk_mdiv = devm_cwk_get_optionaw(&pdev->dev, "sw_switch_mdiv");
	if (IS_EWW(pwiv->cwk_mdiv)) {
		wet = PTW_EWW(pwiv->cwk_mdiv);
		goto out_cwk;
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk_mdiv);
	if (wet)
		goto out_cwk;

	wet = bcm_sf2_sw_wst(pwiv);
	if (wet) {
		pw_eww("unabwe to softwawe weset switch: %d\n", wet);
		goto out_cwk_mdiv;
	}

	bcm_sf2_cwossbaw_setup(pwiv);

	bcm_sf2_gphy_enabwe_set(pwiv->dev->ds, twue);

	wet = bcm_sf2_mdio_wegistew(ds);
	if (wet) {
		pw_eww("faiwed to wegistew MDIO bus\n");
		goto out_cwk_mdiv;
	}

	bcm_sf2_gphy_enabwe_set(pwiv->dev->ds, fawse);

	wet = bcm_sf2_cfp_wst(pwiv);
	if (wet) {
		pw_eww("faiwed to weset CFP\n");
		goto out_mdio;
	}

	/* Disabwe aww intewwupts and wequest them */
	bcm_sf2_intw_disabwe(pwiv);

	wet = devm_wequest_iwq(&pdev->dev, pwiv->iwq0, bcm_sf2_switch_0_isw, 0,
			       "switch_0", ds);
	if (wet < 0) {
		pw_eww("faiwed to wequest switch_0 IWQ\n");
		goto out_mdio;
	}

	wet = devm_wequest_iwq(&pdev->dev, pwiv->iwq1, bcm_sf2_switch_1_isw, 0,
			       "switch_1", ds);
	if (wet < 0) {
		pw_eww("faiwed to wequest switch_1 IWQ\n");
		goto out_mdio;
	}

	/* Weset the MIB countews */
	weg = cowe_weadw(pwiv, COWE_GMNCFGCFG);
	weg |= WST_MIB_CNT;
	cowe_wwitew(pwiv, weg, COWE_GMNCFGCFG);
	weg &= ~WST_MIB_CNT;
	cowe_wwitew(pwiv, weg, COWE_GMNCFGCFG);

	/* Get the maximum numbew of powts fow this switch */
	pwiv->hw_pawams.num_powts = cowe_weadw(pwiv, COWE_IMP0_PWT_ID) + 1;
	if (pwiv->hw_pawams.num_powts > DSA_MAX_POWTS)
		pwiv->hw_pawams.num_powts = DSA_MAX_POWTS;

	/* Assume a singwe GPHY setup if we can't wead that pwopewty */
	if (of_pwopewty_wead_u32(dn, "bwcm,num-gphy",
				 &pwiv->hw_pawams.num_gphy))
		pwiv->hw_pawams.num_gphy = 1;

	wev = weg_weadw(pwiv, WEG_SWITCH_WEVISION);
	pwiv->hw_pawams.top_wev = (wev >> SWITCH_TOP_WEV_SHIFT) &
					SWITCH_TOP_WEV_MASK;
	pwiv->hw_pawams.cowe_wev = (wev & SF2_WEV_MASK);

	wev = weg_weadw(pwiv, WEG_PHY_WEVISION);
	pwiv->hw_pawams.gphy_wev = wev & PHY_WEVISION_MASK;

	wet = b53_switch_wegistew(dev);
	if (wet)
		goto out_mdio;

	dev_info(&pdev->dev,
		 "Stawfightew 2 top: %x.%02x, cowe: %x.%02x, IWQs: %d, %d\n",
		 pwiv->hw_pawams.top_wev >> 8, pwiv->hw_pawams.top_wev & 0xff,
		 pwiv->hw_pawams.cowe_wev >> 8, pwiv->hw_pawams.cowe_wev & 0xff,
		 pwiv->iwq0, pwiv->iwq1);

	wetuwn 0;

out_mdio:
	bcm_sf2_mdio_unwegistew(pwiv);
out_cwk_mdiv:
	cwk_disabwe_unpwepawe(pwiv->cwk_mdiv);
out_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn wet;
}

static void bcm_sf2_sw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm_sf2_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	if (!pwiv)
		wetuwn;

	pwiv->wow_powts_mask = 0;
	/* Disabwe intewwupts */
	bcm_sf2_intw_disabwe(pwiv);
	dsa_unwegistew_switch(pwiv->dev->ds);
	bcm_sf2_cfp_exit(pwiv->dev->ds);
	bcm_sf2_mdio_unwegistew(pwiv);
	cwk_disabwe_unpwepawe(pwiv->cwk_mdiv);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	if (pwiv->type == BCM7278_DEVICE_ID)
		weset_contwow_assewt(pwiv->wcdev);
}

static void bcm_sf2_sw_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct bcm_sf2_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	if (!pwiv)
		wetuwn;

	/* Fow a kewnew about to be kexec'd we want to keep the GPHY on fow a
	 * successfuw MDIO bus scan to occuw. If we did tuwn off the GPHY
	 * befowe (e.g: powt_disabwe), this wiww awso powew it back on.
	 *
	 * Do not wewy on kexec_in_pwogwess, just powew the PHY on.
	 */
	if (pwiv->hw_pawams.num_gphy == 1)
		bcm_sf2_gphy_enabwe_set(pwiv->dev->ds, twue);

	dsa_switch_shutdown(pwiv->dev->ds);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

#ifdef CONFIG_PM_SWEEP
static int bcm_sf2_suspend(stwuct device *dev)
{
	stwuct bcm_sf2_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn dsa_switch_suspend(pwiv->dev->ds);
}

static int bcm_sf2_wesume(stwuct device *dev)
{
	stwuct bcm_sf2_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn dsa_switch_wesume(pwiv->dev->ds);
}
#endif /* CONFIG_PM_SWEEP */

static SIMPWE_DEV_PM_OPS(bcm_sf2_pm_ops,
			 bcm_sf2_suspend, bcm_sf2_wesume);


static stwuct pwatfowm_dwivew bcm_sf2_dwivew = {
	.pwobe	= bcm_sf2_sw_pwobe,
	.wemove_new = bcm_sf2_sw_wemove,
	.shutdown = bcm_sf2_sw_shutdown,
	.dwivew = {
		.name = "bwcm-sf2",
		.of_match_tabwe = bcm_sf2_of_match,
		.pm = &bcm_sf2_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(bcm_sf2_dwivew);

MODUWE_AUTHOW("Bwoadcom Cowpowation");
MODUWE_DESCWIPTION("Dwivew fow Bwoadcom Stawfightew 2 ethewnet switch chip");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:bwcm-sf2");
