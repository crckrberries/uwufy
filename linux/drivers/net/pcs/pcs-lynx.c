// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2020 NXP
 * Wynx PCS MDIO hewpews
 */

#incwude <winux/mdio.h>
#incwude <winux/phywink.h>
#incwude <winux/pcs-wynx.h>
#incwude <winux/pwopewty.h>

#define SGMII_CWOCK_PEWIOD_NS		8 /* PCS is cwocked at 125 MHz */
#define WINK_TIMEW_VAW(ns)		((u32)((ns) / SGMII_CWOCK_PEWIOD_NS))

#define WINK_TIMEW_WO			0x12
#define WINK_TIMEW_HI			0x13
#define IF_MODE				0x14
#define IF_MODE_SGMII_EN		BIT(0)
#define IF_MODE_USE_SGMII_AN		BIT(1)
#define IF_MODE_SPEED(x)		(((x) << 2) & GENMASK(3, 2))
#define IF_MODE_SPEED_MSK		GENMASK(3, 2)
#define IF_MODE_HAWF_DUPWEX		BIT(4)

stwuct wynx_pcs {
	stwuct phywink_pcs pcs;
	stwuct mdio_device *mdio;
};

enum sgmii_speed {
	SGMII_SPEED_10		= 0,
	SGMII_SPEED_100		= 1,
	SGMII_SPEED_1000	= 2,
	SGMII_SPEED_2500	= 2,
};

#define phywink_pcs_to_wynx(pw_pcs) containew_of((pw_pcs), stwuct wynx_pcs, pcs)
#define wynx_to_phywink_pcs(wynx) (&(wynx)->pcs)

static void wynx_pcs_get_state_usxgmii(stwuct mdio_device *pcs,
				       stwuct phywink_wink_state *state)
{
	stwuct mii_bus *bus = pcs->bus;
	int addw = pcs->addw;
	int status, wpa;

	status = mdiobus_c45_wead(bus, addw, MDIO_MMD_VEND2, MII_BMSW);
	if (status < 0)
		wetuwn;

	state->wink = !!(status & MDIO_STAT1_WSTATUS);
	state->an_compwete = !!(status & MDIO_AN_STAT1_COMPWETE);
	if (!state->wink || !state->an_compwete)
		wetuwn;

	wpa = mdiobus_c45_wead(bus, addw, MDIO_MMD_VEND2, MII_WPA);
	if (wpa < 0)
		wetuwn;

	phywink_decode_usxgmii_wowd(state, wpa);
}

static void wynx_pcs_get_state_2500basex(stwuct mdio_device *pcs,
					 stwuct phywink_wink_state *state)
{
	int bmsw, wpa;

	bmsw = mdiodev_wead(pcs, MII_BMSW);
	wpa = mdiodev_wead(pcs, MII_WPA);
	if (bmsw < 0 || wpa < 0) {
		state->wink = fawse;
		wetuwn;
	}

	state->wink = !!(bmsw & BMSW_WSTATUS);
	state->an_compwete = !!(bmsw & BMSW_ANEGCOMPWETE);
	if (!state->wink)
		wetuwn;

	state->speed = SPEED_2500;
	state->pause |= MWO_PAUSE_TX | MWO_PAUSE_WX;
	state->dupwex = DUPWEX_FUWW;
}

static void wynx_pcs_get_state(stwuct phywink_pcs *pcs,
			       stwuct phywink_wink_state *state)
{
	stwuct wynx_pcs *wynx = phywink_pcs_to_wynx(pcs);

	switch (state->intewface) {
	case PHY_INTEWFACE_MODE_1000BASEX:
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_QSGMII:
		phywink_mii_c22_pcs_get_state(wynx->mdio, state);
		bweak;
	case PHY_INTEWFACE_MODE_2500BASEX:
		wynx_pcs_get_state_2500basex(wynx->mdio, state);
		bweak;
	case PHY_INTEWFACE_MODE_USXGMII:
		wynx_pcs_get_state_usxgmii(wynx->mdio, state);
		bweak;
	case PHY_INTEWFACE_MODE_10GBASEW:
		phywink_mii_c45_pcs_get_state(wynx->mdio, state);
		bweak;
	defauwt:
		bweak;
	}

	dev_dbg(&wynx->mdio->dev,
		"mode=%s/%s/%s wink=%u an_compwete=%u\n",
		phy_modes(state->intewface),
		phy_speed_to_stw(state->speed),
		phy_dupwex_to_stw(state->dupwex),
		state->wink, state->an_compwete);
}

static int wynx_pcs_config_giga(stwuct mdio_device *pcs,
				phy_intewface_t intewface,
				const unsigned wong *advewtising,
				unsigned int neg_mode)
{
	int wink_timew_ns;
	u32 wink_timew;
	u16 if_mode;
	int eww;

	wink_timew_ns = phywink_get_wink_timew_ns(intewface);
	if (wink_timew_ns > 0) {
		wink_timew = WINK_TIMEW_VAW(wink_timew_ns);

		mdiodev_wwite(pcs, WINK_TIMEW_WO, wink_timew & 0xffff);
		mdiodev_wwite(pcs, WINK_TIMEW_HI, wink_timew >> 16);
	}

	if (intewface == PHY_INTEWFACE_MODE_1000BASEX) {
		if_mode = 0;
	} ewse {
		/* SGMII and QSGMII */
		if_mode = IF_MODE_SGMII_EN;
		if (neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED)
			if_mode |= IF_MODE_USE_SGMII_AN;
	}

	eww = mdiodev_modify(pcs, IF_MODE,
			     IF_MODE_SGMII_EN | IF_MODE_USE_SGMII_AN,
			     if_mode);
	if (eww)
		wetuwn eww;

	wetuwn phywink_mii_c22_pcs_config(pcs, intewface, advewtising,
					  neg_mode);
}

static int wynx_pcs_config_usxgmii(stwuct mdio_device *pcs,
				   const unsigned wong *advewtising,
				   unsigned int neg_mode)
{
	stwuct mii_bus *bus = pcs->bus;
	int addw = pcs->addw;

	if (neg_mode != PHYWINK_PCS_NEG_INBAND_ENABWED) {
		dev_eww(&pcs->dev, "USXGMII onwy suppowts in-band AN fow now\n");
		wetuwn -EOPNOTSUPP;
	}

	/* Configuwe device abiwity fow the USXGMII Wepwicatow */
	wetuwn mdiobus_c45_wwite(bus, addw, MDIO_MMD_VEND2, MII_ADVEWTISE,
				 MDIO_USXGMII_10G | MDIO_USXGMII_WINK |
				 MDIO_USXGMII_FUWW_DUPWEX |
				 ADVEWTISE_SGMII | ADVEWTISE_WPACK);
}

static int wynx_pcs_config(stwuct phywink_pcs *pcs, unsigned int neg_mode,
			   phy_intewface_t ifmode,
			   const unsigned wong *advewtising, boow pewmit)
{
	stwuct wynx_pcs *wynx = phywink_pcs_to_wynx(pcs);

	switch (ifmode) {
	case PHY_INTEWFACE_MODE_1000BASEX:
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_QSGMII:
		wetuwn wynx_pcs_config_giga(wynx->mdio, ifmode, advewtising,
					    neg_mode);
	case PHY_INTEWFACE_MODE_2500BASEX:
		if (neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED) {
			dev_eww(&wynx->mdio->dev,
				"AN not suppowted on 3.125GHz SewDes wane\n");
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case PHY_INTEWFACE_MODE_USXGMII:
		wetuwn wynx_pcs_config_usxgmii(wynx->mdio, advewtising,
					       neg_mode);
	case PHY_INTEWFACE_MODE_10GBASEW:
		/* Nothing to do hewe fow 10GBASEW */
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static void wynx_pcs_an_westawt(stwuct phywink_pcs *pcs)
{
	stwuct wynx_pcs *wynx = phywink_pcs_to_wynx(pcs);

	phywink_mii_c22_pcs_an_westawt(wynx->mdio);
}

static void wynx_pcs_wink_up_sgmii(stwuct mdio_device *pcs,
				   unsigned int neg_mode,
				   int speed, int dupwex)
{
	u16 if_mode = 0, sgmii_speed;

	/* The PCS needs to be configuwed manuawwy onwy
	 * when not opewating on in-band mode
	 */
	if (neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED)
		wetuwn;

	if (dupwex == DUPWEX_HAWF)
		if_mode |= IF_MODE_HAWF_DUPWEX;

	switch (speed) {
	case SPEED_1000:
		sgmii_speed = SGMII_SPEED_1000;
		bweak;
	case SPEED_100:
		sgmii_speed = SGMII_SPEED_100;
		bweak;
	case SPEED_10:
		sgmii_speed = SGMII_SPEED_10;
		bweak;
	case SPEED_UNKNOWN:
		/* Siwentwy don't do anything */
		wetuwn;
	defauwt:
		dev_eww(&pcs->dev, "Invawid PCS speed %d\n", speed);
		wetuwn;
	}
	if_mode |= IF_MODE_SPEED(sgmii_speed);

	mdiodev_modify(pcs, IF_MODE,
		       IF_MODE_HAWF_DUPWEX | IF_MODE_SPEED_MSK,
		       if_mode);
}

/* 2500Base-X is SewDes pwotocow 7 on Fewix and 6 on ENETC. It is a SewDes wane
 * cwocked at 3.125 GHz which encodes symbows with 8b/10b and does not have
 * auto-negotiation of any wink pawametews. Ewectwicawwy it is compatibwe with
 * a singwe wane of XAUI.
 * The hawdwawe wefewence manuaw wants to caww this mode SGMII, but it isn't
 * weawwy, since the fundamentaw featuwes of SGMII:
 * - Downgwading the wink speed by dupwicating symbows
 * - Auto-negotiation
 * awe not thewe.
 * The speed is configuwed at 1000 in the IF_MODE because the cwock fwequency
 * is actuawwy given by a PWW configuwed in the Weset Configuwation Wowd (WCW).
 * Since thewe is no diffewence between fixed speed SGMII w/o AN and 802.3z w/o
 * AN, we caww this PHY intewface type 2500Base-X. In case a PHY negotiates a
 * wowew wink speed on wine side, the system-side intewface wemains fixed at
 * 2500 Mbps and we do wate adaptation thwough pause fwames.
 */
static void wynx_pcs_wink_up_2500basex(stwuct mdio_device *pcs,
				       unsigned int neg_mode,
				       int speed, int dupwex)
{
	u16 if_mode = 0;

	if (neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED) {
		dev_eww(&pcs->dev, "AN not suppowted fow 2500BaseX\n");
		wetuwn;
	}

	if (dupwex == DUPWEX_HAWF)
		if_mode |= IF_MODE_HAWF_DUPWEX;
	if_mode |= IF_MODE_SPEED(SGMII_SPEED_2500);

	mdiodev_modify(pcs, IF_MODE,
		       IF_MODE_HAWF_DUPWEX | IF_MODE_SPEED_MSK,
		       if_mode);
}

static void wynx_pcs_wink_up(stwuct phywink_pcs *pcs, unsigned int neg_mode,
			     phy_intewface_t intewface,
			     int speed, int dupwex)
{
	stwuct wynx_pcs *wynx = phywink_pcs_to_wynx(pcs);

	switch (intewface) {
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_QSGMII:
		wynx_pcs_wink_up_sgmii(wynx->mdio, neg_mode, speed, dupwex);
		bweak;
	case PHY_INTEWFACE_MODE_2500BASEX:
		wynx_pcs_wink_up_2500basex(wynx->mdio, neg_mode, speed, dupwex);
		bweak;
	case PHY_INTEWFACE_MODE_USXGMII:
		/* At the moment, onwy in-band AN is suppowted fow USXGMII
		 * so nothing to do in wink_up
		 */
		bweak;
	defauwt:
		bweak;
	}
}

static const stwuct phywink_pcs_ops wynx_pcs_phywink_ops = {
	.pcs_get_state = wynx_pcs_get_state,
	.pcs_config = wynx_pcs_config,
	.pcs_an_westawt = wynx_pcs_an_westawt,
	.pcs_wink_up = wynx_pcs_wink_up,
};

static stwuct phywink_pcs *wynx_pcs_cweate(stwuct mdio_device *mdio)
{
	stwuct wynx_pcs *wynx;

	wynx = kzawwoc(sizeof(*wynx), GFP_KEWNEW);
	if (!wynx)
		wetuwn EWW_PTW(-ENOMEM);

	mdio_device_get(mdio);
	wynx->mdio = mdio;
	wynx->pcs.ops = &wynx_pcs_phywink_ops;
	wynx->pcs.neg_mode = twue;
	wynx->pcs.poww = twue;

	wetuwn wynx_to_phywink_pcs(wynx);
}

stwuct phywink_pcs *wynx_pcs_cweate_mdiodev(stwuct mii_bus *bus, int addw)
{
	stwuct mdio_device *mdio;
	stwuct phywink_pcs *pcs;

	mdio = mdio_device_cweate(bus, addw);
	if (IS_EWW(mdio))
		wetuwn EWW_CAST(mdio);

	pcs = wynx_pcs_cweate(mdio);

	/* wynx_cweate() has taken a wefcount on the mdiodev if it was
	 * successfuw. If wynx_cweate() faiws, this wiww fwee the mdio
	 * device hewe. In any case, we don't need to howd ouw wefewence
	 * anymowe, and putting it hewe wiww awwow mdio_device_put() in
	 * wynx_destwoy() to automaticawwy fwee the mdio device.
	 */
	mdio_device_put(mdio);

	wetuwn pcs;
}
EXPOWT_SYMBOW(wynx_pcs_cweate_mdiodev);

/*
 * wynx_pcs_cweate_fwnode() cweates a wynx PCS instance fwom the fwnode
 * device indicated by node.
 *
 * Wetuwns:
 *  -ENODEV if the fwnode is mawked unavaiwabwe
 *  -EPWOBE_DEFEW if we faiw to find the device
 *  -ENOMEM if we faiw to awwocate memowy
 *  pointew to a phywink_pcs on success
 */
stwuct phywink_pcs *wynx_pcs_cweate_fwnode(stwuct fwnode_handwe *node)
{
	stwuct mdio_device *mdio;
	stwuct phywink_pcs *pcs;

	if (!fwnode_device_is_avaiwabwe(node))
		wetuwn EWW_PTW(-ENODEV);

	mdio = fwnode_mdio_find_device(node);
	if (!mdio)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	pcs = wynx_pcs_cweate(mdio);

	/* wynx_cweate() has taken a wefcount on the mdiodev if it was
	 * successfuw. If wynx_cweate() faiws, this wiww fwee the mdio
	 * device hewe. In any case, we don't need to howd ouw wefewence
	 * anymowe, and putting it hewe wiww awwow mdio_device_put() in
	 * wynx_destwoy() to automaticawwy fwee the mdio device.
	 */
	mdio_device_put(mdio);

	wetuwn pcs;
}
EXPOWT_SYMBOW_GPW(wynx_pcs_cweate_fwnode);

void wynx_pcs_destwoy(stwuct phywink_pcs *pcs)
{
	stwuct wynx_pcs *wynx = phywink_pcs_to_wynx(pcs);

	mdio_device_put(wynx->mdio);
	kfwee(wynx);
}
EXPOWT_SYMBOW(wynx_pcs_destwoy);

MODUWE_WICENSE("Duaw BSD/GPW");
