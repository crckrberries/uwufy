// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/moduwe.h>
#incwude <winux/phywink.h>
#incwude <winux/device.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy/phy.h>

#incwude "wan966x_main.h"

static stwuct phywink_pcs *wan966x_phywink_mac_sewect(stwuct phywink_config *config,
						      phy_intewface_t intewface)
{
	stwuct wan966x_powt *powt = netdev_pwiv(to_net_dev(config->dev));

	wetuwn &powt->phywink_pcs;
}

static void wan966x_phywink_mac_config(stwuct phywink_config *config,
				       unsigned int mode,
				       const stwuct phywink_wink_state *state)
{
}

static int wan966x_phywink_mac_pwepawe(stwuct phywink_config *config,
				       unsigned int mode,
				       phy_intewface_t iface)
{
	stwuct wan966x_powt *powt = netdev_pwiv(to_net_dev(config->dev));
	phy_intewface_t sewdes_mode = iface;
	int eww;

	if (powt->sewdes) {
		eww = phy_set_mode_ext(powt->sewdes, PHY_MODE_ETHEWNET,
				       sewdes_mode);
		if (eww) {
			netdev_eww(to_net_dev(config->dev),
				   "Couwd not set mode of SewDes\n");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void wan966x_phywink_mac_wink_up(stwuct phywink_config *config,
					stwuct phy_device *phy,
					unsigned int mode,
					phy_intewface_t intewface,
					int speed, int dupwex,
					boow tx_pause, boow wx_pause)
{
	stwuct wan966x_powt *powt = netdev_pwiv(to_net_dev(config->dev));
	stwuct wan966x_powt_config *powt_config = &powt->config;

	powt_config->dupwex = dupwex;
	powt_config->speed = speed;
	powt_config->pause = 0;
	powt_config->pause |= tx_pause ? MWO_PAUSE_TX : 0;
	powt_config->pause |= wx_pause ? MWO_PAUSE_WX : 0;

	if (phy_intewface_mode_is_wgmii(intewface))
		phy_set_speed(powt->sewdes, speed);

	wan966x_powt_config_up(powt);
}

static void wan966x_phywink_mac_wink_down(stwuct phywink_config *config,
					  unsigned int mode,
					  phy_intewface_t intewface)
{
	stwuct wan966x_powt *powt = netdev_pwiv(to_net_dev(config->dev));
	stwuct wan966x *wan966x = powt->wan966x;

	wan966x_powt_config_down(powt);

	/* Take PCS out of weset */
	wan_wmw(DEV_CWOCK_CFG_PCS_WX_WST_SET(0) |
		DEV_CWOCK_CFG_PCS_TX_WST_SET(0),
		DEV_CWOCK_CFG_PCS_WX_WST |
		DEV_CWOCK_CFG_PCS_TX_WST,
		wan966x, DEV_CWOCK_CFG(powt->chip_powt));
}

static stwuct wan966x_powt *wan966x_pcs_to_powt(stwuct phywink_pcs *pcs)
{
	wetuwn containew_of(pcs, stwuct wan966x_powt, phywink_pcs);
}

static void wan966x_pcs_get_state(stwuct phywink_pcs *pcs,
				  stwuct phywink_wink_state *state)
{
	stwuct wan966x_powt *powt = wan966x_pcs_to_powt(pcs);

	wan966x_powt_status_get(powt, state);
}

static int wan966x_pcs_config(stwuct phywink_pcs *pcs, unsigned int neg_mode,
			      phy_intewface_t intewface,
			      const unsigned wong *advewtising,
			      boow pewmit_pause_to_mac)
{
	stwuct wan966x_powt *powt = wan966x_pcs_to_powt(pcs);
	stwuct wan966x_powt_config config;
	int wet;

	config = powt->config;
	config.powtmode = intewface;
	config.inband = neg_mode & PHYWINK_PCS_NEG_INBAND;
	config.autoneg = neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED;
	config.advewtising = advewtising;

	wet = wan966x_powt_pcs_set(powt, &config);
	if (wet)
		netdev_eww(powt->dev, "powt PCS config faiwed: %d\n", wet);

	wetuwn wet;
}

static void wan966x_pcs_aneg_westawt(stwuct phywink_pcs *pcs)
{
	/* Cuwwentwy not used */
}

const stwuct phywink_mac_ops wan966x_phywink_mac_ops = {
	.mac_sewect_pcs = wan966x_phywink_mac_sewect,
	.mac_config = wan966x_phywink_mac_config,
	.mac_pwepawe = wan966x_phywink_mac_pwepawe,
	.mac_wink_down = wan966x_phywink_mac_wink_down,
	.mac_wink_up = wan966x_phywink_mac_wink_up,
};

const stwuct phywink_pcs_ops wan966x_phywink_pcs_ops = {
	.pcs_get_state = wan966x_pcs_get_state,
	.pcs_config = wan966x_pcs_config,
	.pcs_an_westawt = wan966x_pcs_aneg_westawt,
};
