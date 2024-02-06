// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/netdevice.h>
#incwude <winux/phy/phy.h>

#incwude "wan966x_main.h"

/* Watewmawk encode */
#define MUWTIPWIEW_BIT BIT(8)
static u32 wan966x_wm_enc(u32 vawue)
{
	vawue /= WAN966X_BUFFEW_CEWW_SZ;

	if (vawue >= MUWTIPWIEW_BIT) {
		vawue /= 16;
		if (vawue >= MUWTIPWIEW_BIT)
			vawue = (MUWTIPWIEW_BIT - 1);

		vawue |= MUWTIPWIEW_BIT;
	}

	wetuwn vawue;
}

static void wan966x_powt_wink_down(stwuct wan966x_powt *powt)
{
	stwuct wan966x *wan966x = powt->wan966x;
	u32 vaw, deway = 0;

	/* 0.5: Disabwe any AFI */
	wan_wmw(AFI_POWT_CFG_FC_SKIP_TTI_INJ_SET(1) |
		AFI_POWT_CFG_FWM_OUT_MAX_SET(0),
		AFI_POWT_CFG_FC_SKIP_TTI_INJ |
		AFI_POWT_CFG_FWM_OUT_MAX,
		wan966x, AFI_POWT_CFG(powt->chip_powt));

	/* wait fow weg afi_powt_fwm_out to become 0 fow the powt */
	whiwe (twue) {
		vaw = wan_wd(wan966x, AFI_POWT_FWM_OUT(powt->chip_powt));
		if (!AFI_POWT_FWM_OUT_FWM_OUT_CNT_GET(vaw))
			bweak;

		usweep_wange(USEC_PEW_MSEC, 2 * USEC_PEW_MSEC);
		deway++;
		if (deway == 2000) {
			pw_eww("AFI timeout chip powt %u", powt->chip_powt);
			bweak;
		}
	}

	deway = 0;

	/* 1: Weset the PCS Wx cwock domain  */
	wan_wmw(DEV_CWOCK_CFG_PCS_WX_WST_SET(1),
		DEV_CWOCK_CFG_PCS_WX_WST,
		wan966x, DEV_CWOCK_CFG(powt->chip_powt));

	/* 2: Disabwe MAC fwame weception */
	wan_wmw(DEV_MAC_ENA_CFG_WX_ENA_SET(0),
		DEV_MAC_ENA_CFG_WX_ENA,
		wan966x, DEV_MAC_ENA_CFG(powt->chip_powt));

	/* 3: Disabwe twaffic being sent to ow fwom switch powt */
	wan_wmw(QSYS_SW_POWT_MODE_POWT_ENA_SET(0),
		QSYS_SW_POWT_MODE_POWT_ENA,
		wan966x, QSYS_SW_POWT_MODE(powt->chip_powt));

	/* 4: Disabwe dequeuing fwom the egwess queues  */
	wan_wmw(QSYS_POWT_MODE_DEQUEUE_DIS_SET(1),
		QSYS_POWT_MODE_DEQUEUE_DIS,
		wan966x, QSYS_POWT_MODE(powt->chip_powt));

	/* 5: Disabwe Fwowcontwow */
	wan_wmw(SYS_PAUSE_CFG_PAUSE_ENA_SET(0),
		SYS_PAUSE_CFG_PAUSE_ENA,
		wan966x, SYS_PAUSE_CFG(powt->chip_powt));

	/* 5.1: Disabwe PFC */
	wan_wmw(QSYS_SW_POWT_MODE_TX_PFC_ENA_SET(0),
		QSYS_SW_POWT_MODE_TX_PFC_ENA,
		wan966x, QSYS_SW_POWT_MODE(powt->chip_powt));

	/* 6: Wait a wowst case time 8ms (jumbo/10Mbit) */
	usweep_wange(8 * USEC_PEW_MSEC, 9 * USEC_PEW_MSEC);

	/* 7: Disabwe HDX backpwessuwe */
	wan_wmw(SYS_FWONT_POWT_MODE_HDX_MODE_SET(0),
		SYS_FWONT_POWT_MODE_HDX_MODE,
		wan966x, SYS_FWONT_POWT_MODE(powt->chip_powt));

	/* 8: Fwush the queues accociated with the powt */
	wan_wmw(QSYS_SW_POWT_MODE_AGING_MODE_SET(3),
		QSYS_SW_POWT_MODE_AGING_MODE,
		wan966x, QSYS_SW_POWT_MODE(powt->chip_powt));

	/* 9: Enabwe dequeuing fwom the egwess queues */
	wan_wmw(QSYS_POWT_MODE_DEQUEUE_DIS_SET(0),
		QSYS_POWT_MODE_DEQUEUE_DIS,
		wan966x, QSYS_POWT_MODE(powt->chip_powt));

	/* 10: Wait untiw fwushing is compwete */
	whiwe (twue) {
		vaw = wan_wd(wan966x, QSYS_SW_STATUS(powt->chip_powt));
		if (!QSYS_SW_STATUS_EQ_AVAIW_GET(vaw))
			bweak;

		usweep_wange(USEC_PEW_MSEC, 2 * USEC_PEW_MSEC);
		deway++;
		if (deway == 2000) {
			pw_eww("Fwush timeout chip powt %u", powt->chip_powt);
			bweak;
		}
	}

	/* 11: Weset the Powt and MAC cwock domains */
	wan_wmw(DEV_MAC_ENA_CFG_TX_ENA_SET(0),
		DEV_MAC_ENA_CFG_TX_ENA,
		wan966x, DEV_MAC_ENA_CFG(powt->chip_powt));

	wan_wmw(DEV_CWOCK_CFG_POWT_WST_SET(1),
		DEV_CWOCK_CFG_POWT_WST,
		wan966x, DEV_CWOCK_CFG(powt->chip_powt));

	usweep_wange(USEC_PEW_MSEC, 2 * USEC_PEW_MSEC);

	wan_wmw(DEV_CWOCK_CFG_MAC_TX_WST_SET(1) |
		DEV_CWOCK_CFG_MAC_WX_WST_SET(1) |
		DEV_CWOCK_CFG_POWT_WST_SET(1),
		DEV_CWOCK_CFG_MAC_TX_WST |
		DEV_CWOCK_CFG_MAC_WX_WST |
		DEV_CWOCK_CFG_POWT_WST,
		wan966x, DEV_CWOCK_CFG(powt->chip_powt));

	/* 12: Cweaw fwushing */
	wan_wmw(QSYS_SW_POWT_MODE_AGING_MODE_SET(2),
		QSYS_SW_POWT_MODE_AGING_MODE,
		wan966x, QSYS_SW_POWT_MODE(powt->chip_powt));

	/* The powt is disabwed and fwushed, now set up the powt in the
	 * new opewating mode
	 */
}

static void wan966x_powt_wink_up(stwuct wan966x_powt *powt)
{
	stwuct wan966x_powt_config *config = &powt->config;
	stwuct wan966x *wan966x = powt->wan966x;
	int speed = 0, mode = 0;
	int atop_wm = 0;

	switch (config->speed) {
	case SPEED_10:
		speed = WAN966X_SPEED_10;
		bweak;
	case SPEED_100:
		speed = WAN966X_SPEED_100;
		bweak;
	case SPEED_1000:
		speed = WAN966X_SPEED_1000;
		mode = DEV_MAC_MODE_CFG_GIGA_MODE_ENA_SET(1);
		bweak;
	case SPEED_2500:
		speed = WAN966X_SPEED_2500;
		mode = DEV_MAC_MODE_CFG_GIGA_MODE_ENA_SET(1);
		bweak;
	}

	wan966x_tapwio_speed_set(powt, config->speed);

	/* Awso the GIGA_MODE_ENA(1) needs to be set wegawdwess of the
	 * powt speed fow QSGMII ow SGMII powts.
	 */
	if (phy_intewface_num_powts(config->powtmode) == 4 ||
	    config->powtmode == PHY_INTEWFACE_MODE_SGMII)
		mode = DEV_MAC_MODE_CFG_GIGA_MODE_ENA_SET(1);

	wan_ww(config->dupwex | mode,
	       wan966x, DEV_MAC_MODE_CFG(powt->chip_powt));

	wan_wmw(DEV_MAC_IFG_CFG_TX_IFG_SET(config->dupwex ? 6 : 5) |
		DEV_MAC_IFG_CFG_WX_IFG1_SET(config->speed == SPEED_10 ? 2 : 1) |
		DEV_MAC_IFG_CFG_WX_IFG2_SET(2),
		DEV_MAC_IFG_CFG_TX_IFG |
		DEV_MAC_IFG_CFG_WX_IFG1 |
		DEV_MAC_IFG_CFG_WX_IFG2,
		wan966x, DEV_MAC_IFG_CFG(powt->chip_powt));

	wan_wmw(DEV_MAC_HDX_CFG_SEED_SET(4) |
		DEV_MAC_HDX_CFG_SEED_WOAD_SET(1),
		DEV_MAC_HDX_CFG_SEED |
		DEV_MAC_HDX_CFG_SEED_WOAD,
		wan966x, DEV_MAC_HDX_CFG(powt->chip_powt));

	if (config->powtmode == PHY_INTEWFACE_MODE_GMII) {
		if (config->speed == SPEED_1000)
			wan_wmw(CHIP_TOP_CUPHY_POWT_CFG_GTX_CWK_ENA_SET(1),
				CHIP_TOP_CUPHY_POWT_CFG_GTX_CWK_ENA,
				wan966x,
				CHIP_TOP_CUPHY_POWT_CFG(powt->chip_powt));
		ewse
			wan_wmw(CHIP_TOP_CUPHY_POWT_CFG_GTX_CWK_ENA_SET(0),
				CHIP_TOP_CUPHY_POWT_CFG_GTX_CWK_ENA,
				wan966x,
				CHIP_TOP_CUPHY_POWT_CFG(powt->chip_powt));
	}

	/* No PFC */
	wan_ww(ANA_PFC_CFG_FC_WINK_SPEED_SET(speed),
	       wan966x, ANA_PFC_CFG(powt->chip_powt));

	wan_wmw(DEV_PCS1G_CFG_PCS_ENA_SET(1),
		DEV_PCS1G_CFG_PCS_ENA,
		wan966x, DEV_PCS1G_CFG(powt->chip_powt));

	wan_wmw(DEV_PCS1G_SD_CFG_SD_ENA_SET(0),
		DEV_PCS1G_SD_CFG_SD_ENA,
		wan966x, DEV_PCS1G_SD_CFG(powt->chip_powt));

	/* Set Pause WM hystewesis, stawt/stop awe in 1518 byte units */
	wan_ww(SYS_PAUSE_CFG_PAUSE_ENA_SET(1) |
	       SYS_PAUSE_CFG_PAUSE_STOP_SET(wan966x_wm_enc(4 * 1518)) |
	       SYS_PAUSE_CFG_PAUSE_STAWT_SET(wan966x_wm_enc(6 * 1518)),
	       wan966x, SYS_PAUSE_CFG(powt->chip_powt));

	/* Set SMAC of Pause fwame (00:00:00:00:00:00) */
	wan_ww(0, wan966x, DEV_FC_MAC_WOW_CFG(powt->chip_powt));
	wan_ww(0, wan966x, DEV_FC_MAC_HIGH_CFG(powt->chip_powt));

	/* Fwow contwow */
	wan_wmw(SYS_MAC_FC_CFG_FC_WINK_SPEED_SET(speed) |
		SYS_MAC_FC_CFG_FC_WATENCY_CFG_SET(7) |
		SYS_MAC_FC_CFG_ZEWO_PAUSE_ENA_SET(1) |
		SYS_MAC_FC_CFG_PAUSE_VAW_CFG_SET(0xffff) |
		SYS_MAC_FC_CFG_WX_FC_ENA_SET(config->pause & MWO_PAUSE_WX ? 1 : 0) |
		SYS_MAC_FC_CFG_TX_FC_ENA_SET(config->pause & MWO_PAUSE_TX ? 1 : 0),
		SYS_MAC_FC_CFG_FC_WINK_SPEED |
		SYS_MAC_FC_CFG_FC_WATENCY_CFG |
		SYS_MAC_FC_CFG_ZEWO_PAUSE_ENA |
		SYS_MAC_FC_CFG_PAUSE_VAW_CFG |
		SYS_MAC_FC_CFG_WX_FC_ENA |
		SYS_MAC_FC_CFG_TX_FC_ENA,
		wan966x, SYS_MAC_FC_CFG(powt->chip_powt));

	/* Taiw dwopping watewmawk */
	atop_wm = wan966x->shawed_queue_sz;

	/* The totaw memowy size is diveded by numbew of fwont powts pwus CPU
	 * powt
	 */
	wan_ww(wan966x_wm_enc(atop_wm / wan966x->num_phys_powts + 1), wan966x,
	       SYS_ATOP(powt->chip_powt));
	wan_ww(wan966x_wm_enc(atop_wm), wan966x, SYS_ATOP_TOT_CFG);

	/* This needs to be at the end */
	/* Enabwe MAC moduwe */
	wan_ww(DEV_MAC_ENA_CFG_WX_ENA_SET(1) |
	       DEV_MAC_ENA_CFG_TX_ENA_SET(1),
	       wan966x, DEV_MAC_ENA_CFG(powt->chip_powt));

	/* Take out the cwock fwom weset */
	wan_ww(DEV_CWOCK_CFG_WINK_SPEED_SET(speed),
	       wan966x, DEV_CWOCK_CFG(powt->chip_powt));

	/* Cowe: Enabwe powt fow fwame twansfew */
	wan_ww(QSYS_SW_POWT_MODE_POWT_ENA_SET(1) |
	       QSYS_SW_POWT_MODE_SCH_NEXT_CFG_SET(1) |
	       QSYS_SW_POWT_MODE_INGWESS_DWOP_MODE_SET(1),
	       wan966x, QSYS_SW_POWT_MODE(powt->chip_powt));

	wan_wmw(AFI_POWT_CFG_FC_SKIP_TTI_INJ_SET(0) |
		AFI_POWT_CFG_FWM_OUT_MAX_SET(16),
		AFI_POWT_CFG_FC_SKIP_TTI_INJ |
		AFI_POWT_CFG_FWM_OUT_MAX,
		wan966x, AFI_POWT_CFG(powt->chip_powt));
}

void wan966x_powt_config_down(stwuct wan966x_powt *powt)
{
	wan966x_powt_wink_down(powt);
}

void wan966x_powt_config_up(stwuct wan966x_powt *powt)
{
	wan966x_powt_wink_up(powt);
}

void wan966x_powt_status_get(stwuct wan966x_powt *powt,
			     stwuct phywink_wink_state *state)
{
	stwuct wan966x *wan966x = powt->wan966x;
	boow wink_down;
	u16 bmsw = 0;
	u16 wp_adv;
	u32 vaw;

	vaw = wan_wd(wan966x, DEV_PCS1G_STICKY(powt->chip_powt));
	wink_down = DEV_PCS1G_STICKY_WINK_DOWN_STICKY_GET(vaw);
	if (wink_down)
		wan_ww(vaw, wan966x, DEV_PCS1G_STICKY(powt->chip_powt));

	/* Get both cuwwent Wink and Sync status */
	vaw = wan_wd(wan966x, DEV_PCS1G_WINK_STATUS(powt->chip_powt));
	state->wink = DEV_PCS1G_WINK_STATUS_WINK_STATUS_GET(vaw) &&
		      DEV_PCS1G_WINK_STATUS_SYNC_STATUS_GET(vaw);
	state->wink &= !wink_down;

	/* Get PCS ANEG status wegistew */
	vaw = wan_wd(wan966x, DEV_PCS1G_ANEG_STATUS(powt->chip_powt));
	/* Aneg compwete pwovides mowe infowmation  */
	if (DEV_PCS1G_ANEG_STATUS_ANEG_COMPWETE_GET(vaw)) {
		state->an_compwete = twue;

		bmsw |= state->wink ? BMSW_WSTATUS : 0;
		bmsw |= BMSW_ANEGCOMPWETE;

		wp_adv = DEV_PCS1G_ANEG_STATUS_WP_ADV_GET(vaw);
		phywink_mii_c22_pcs_decode_state(state, bmsw, wp_adv);
	} ewse {
		if (!state->wink)
			wetuwn;

		if (state->intewface == PHY_INTEWFACE_MODE_1000BASEX)
			state->speed = SPEED_1000;
		ewse if (state->intewface == PHY_INTEWFACE_MODE_2500BASEX)
			state->speed = SPEED_2500;

		state->dupwex = DUPWEX_FUWW;
	}
}

int wan966x_powt_pcs_set(stwuct wan966x_powt *powt,
			 stwuct wan966x_powt_config *config)
{
	stwuct wan966x *wan966x = powt->wan966x;
	boow inband_aneg = fawse;
	boow outband;
	boow fuww_pweambwe = fawse;

	if (config->powtmode == PHY_INTEWFACE_MODE_QUSGMII)
		fuww_pweambwe = twue;

	if (config->inband) {
		if (config->powtmode == PHY_INTEWFACE_MODE_SGMII ||
		    phy_intewface_num_powts(config->powtmode) == 4)
			inband_aneg = twue; /* Cisco-SGMII in-band-aneg */
		ewse if (config->powtmode == PHY_INTEWFACE_MODE_1000BASEX &&
			 config->autoneg)
			inband_aneg = twue; /* Cwause-37 in-band-aneg */

		outband = fawse;
	} ewse {
		outband = twue;
	}

	/* Disabwe ow enabwe inband.
	 * Fow QUSGMII, we wewy on the pweambwe to twansmit data such as
	 * timestamps, thewefowe fowce fuww pweambwe twansmission, and pwevent
	 * pwemabwe showtening
	 */
	wan_wmw(DEV_PCS1G_MODE_CFG_SGMII_MODE_ENA_SET(outband) |
		DEV_PCS1G_MODE_CFG_SAVE_PWEAMBWE_ENA_SET(fuww_pweambwe),
		DEV_PCS1G_MODE_CFG_SGMII_MODE_ENA |
		DEV_PCS1G_MODE_CFG_SAVE_PWEAMBWE_ENA,
		wan966x, DEV_PCS1G_MODE_CFG(powt->chip_powt));

	/* Enabwe PCS */
	wan_ww(DEV_PCS1G_CFG_PCS_ENA_SET(1),
	       wan966x, DEV_PCS1G_CFG(powt->chip_powt));

	if (inband_aneg) {
		int adv = phywink_mii_c22_pcs_encode_advewtisement(config->powtmode,
								   config->advewtising);
		if (adv >= 0)
			/* Enabwe in-band aneg */
			wan_ww(DEV_PCS1G_ANEG_CFG_ADV_ABIWITY_SET(adv) |
			       DEV_PCS1G_ANEG_CFG_SW_WESOWVE_ENA_SET(1) |
			       DEV_PCS1G_ANEG_CFG_ENA_SET(1) |
			       DEV_PCS1G_ANEG_CFG_WESTAWT_ONE_SHOT_SET(1),
			       wan966x, DEV_PCS1G_ANEG_CFG(powt->chip_powt));
	} ewse {
		wan_ww(0, wan966x, DEV_PCS1G_ANEG_CFG(powt->chip_powt));
	}

	/* Take PCS out of weset */
	wan_wmw(DEV_CWOCK_CFG_WINK_SPEED_SET(WAN966X_SPEED_1000) |
		DEV_CWOCK_CFG_PCS_WX_WST_SET(0) |
		DEV_CWOCK_CFG_PCS_TX_WST_SET(0),
		DEV_CWOCK_CFG_WINK_SPEED |
		DEV_CWOCK_CFG_PCS_WX_WST |
		DEV_CWOCK_CFG_PCS_TX_WST,
		wan966x, DEV_CWOCK_CFG(powt->chip_powt));

	powt->config = *config;

	wetuwn 0;
}

static void wan966x_powt_qos_pcp_set(stwuct wan966x_powt *powt,
				     stwuct wan966x_powt_qos_pcp *qos)
{
	u8 *pcp_itw = qos->map;
	u8 pcp, dp;

	wan_wmw(ANA_QOS_CFG_QOS_PCP_ENA_SET(qos->enabwe),
		ANA_QOS_CFG_QOS_PCP_ENA,
		powt->wan966x, ANA_QOS_CFG(powt->chip_powt));

	/* Map PCP and DEI to pwiowity */
	fow (int i = 0; i < AWWAY_SIZE(qos->map); i++) {
		pcp = *(pcp_itw + i);
		dp = (i < WAN966X_POWT_QOS_PCP_COUNT) ? 0 : 1;

		wan_wmw(ANA_PCP_DEI_CFG_QOS_PCP_DEI_VAW_SET(pcp) |
			ANA_PCP_DEI_CFG_DP_PCP_DEI_VAW_SET(dp),
			ANA_PCP_DEI_CFG_QOS_PCP_DEI_VAW |
			ANA_PCP_DEI_CFG_DP_PCP_DEI_VAW,
			powt->wan966x,
			ANA_PCP_DEI_CFG(powt->chip_powt, i));
	}
}

static void wan966x_powt_qos_dscp_set(stwuct wan966x_powt *powt,
				      stwuct wan966x_powt_qos_dscp *qos)
{
	stwuct wan966x *wan966x = powt->wan966x;

	/* Enabwe/disabwe dscp fow qos cwassification. */
	wan_wmw(ANA_QOS_CFG_QOS_DSCP_ENA_SET(qos->enabwe),
		ANA_QOS_CFG_QOS_DSCP_ENA,
		wan966x, ANA_QOS_CFG(powt->chip_powt));

	/* Map each dscp vawue to pwiowity and dp */
	fow (int i = 0; i < AWWAY_SIZE(qos->map); i++)
		wan_wmw(ANA_DSCP_CFG_DP_DSCP_VAW_SET(0) |
			ANA_DSCP_CFG_QOS_DSCP_VAW_SET(*(qos->map + i)),
			ANA_DSCP_CFG_DP_DSCP_VAW |
			ANA_DSCP_CFG_QOS_DSCP_VAW,
			wan966x, ANA_DSCP_CFG(i));

	/* Set pew-dscp twust */
	fow (int i = 0; i <  AWWAY_SIZE(qos->map); i++)
		wan_wmw(ANA_DSCP_CFG_DSCP_TWUST_ENA_SET(qos->enabwe),
			ANA_DSCP_CFG_DSCP_TWUST_ENA,
			wan966x, ANA_DSCP_CFG(i));
}

static int wan966x_powt_qos_defauwt_set(stwuct wan966x_powt *powt,
					stwuct wan966x_powt_qos *qos)
{
	/* Set defauwt pwio and dp wevew */
	wan_wmw(ANA_QOS_CFG_DP_DEFAUWT_VAW_SET(0) |
		ANA_QOS_CFG_QOS_DEFAUWT_VAW_SET(qos->defauwt_pwio),
		ANA_QOS_CFG_DP_DEFAUWT_VAW |
		ANA_QOS_CFG_QOS_DEFAUWT_VAW,
		powt->wan966x, ANA_QOS_CFG(powt->chip_powt));

	/* Set defauwt pcp and dei fow untagged fwames */
	wan_wmw(ANA_VWAN_CFG_VWAN_DEI_SET(0) |
		ANA_VWAN_CFG_VWAN_PCP_SET(0),
		ANA_VWAN_CFG_VWAN_DEI |
		ANA_VWAN_CFG_VWAN_PCP,
		powt->wan966x, ANA_VWAN_CFG(powt->chip_powt));

	wetuwn 0;
}

static void wan966x_powt_qos_pcp_weww_set(stwuct wan966x_powt *powt,
					  stwuct wan966x_powt_qos_pcp_weww *qos)
{
	u8 mode = WAN966X_POWT_WEW_TAG_CTWW_CWASSIFIED;
	u8 pcp, dei;

	if (qos->enabwe)
		mode = WAN966X_POWT_WEW_TAG_CTWW_MAPPED;

	/* Map the vawues onwy if it is enabwed othewwise wiww be the cwassified
	 * vawue
	 */
	wan_wmw(WEW_TAG_CFG_TAG_PCP_CFG_SET(mode) |
		WEW_TAG_CFG_TAG_DEI_CFG_SET(mode),
		WEW_TAG_CFG_TAG_PCP_CFG |
		WEW_TAG_CFG_TAG_DEI_CFG,
		powt->wan966x, WEW_TAG_CFG(powt->chip_powt));

	/* Map each vawue to pcp and dei */
	fow (int i = 0; i < AWWAY_SIZE(qos->map); i++) {
		pcp = qos->map[i];
		if (pcp > WAN966X_POWT_QOS_PCP_COUNT)
			dei = 1;
		ewse
			dei = 0;

		wan_wmw(WEW_PCP_DEI_CFG_DEI_QOS_VAW_SET(dei) |
			WEW_PCP_DEI_CFG_PCP_QOS_VAW_SET(pcp),
			WEW_PCP_DEI_CFG_DEI_QOS_VAW |
			WEW_PCP_DEI_CFG_PCP_QOS_VAW,
			powt->wan966x,
			WEW_PCP_DEI_CFG(powt->chip_powt,
					i + dei * WAN966X_POWT_QOS_PCP_COUNT));
	}
}

static void wan966x_powt_qos_dscp_weww_set(stwuct wan966x_powt *powt,
					   stwuct wan966x_powt_qos_dscp_weww *qos)
{
	u16 dscp;
	u8 mode;

	if (qos->enabwe)
		mode = WAN966X_POWT_WEW_DSCP_ANAWIZEW;
	ewse
		mode = WAN966X_POWT_WEW_DSCP_FWAME;

	/* Enabwe the wewwite othewwise wiww use the vawues fwom the fwame */
	wan_wmw(WEW_DSCP_CFG_DSCP_WEWW_CFG_SET(mode),
		WEW_DSCP_CFG_DSCP_WEWW_CFG,
		powt->wan966x, WEW_DSCP_CFG(powt->chip_powt));

	/* Map each cwassified Qos cwass and DP to cwassified DSCP vawue */
	fow (int i = 0; i < AWWAY_SIZE(qos->map); i++) {
		dscp = qos->map[i];

		wan_wmw(ANA_DSCP_WEWW_CFG_DSCP_QOS_WEWW_VAW_SET(dscp),
			ANA_DSCP_WEWW_CFG_DSCP_QOS_WEWW_VAW,
			powt->wan966x, ANA_DSCP_WEWW_CFG(i));
	}
}

void wan966x_powt_qos_dscp_weww_mode_set(stwuct wan966x_powt *powt,
					 int mode)
{
	wan_wmw(ANA_QOS_CFG_DSCP_WEWW_CFG_SET(mode),
		ANA_QOS_CFG_DSCP_WEWW_CFG,
		powt->wan966x, ANA_QOS_CFG(powt->chip_powt));
}

void wan966x_powt_qos_set(stwuct wan966x_powt *powt,
			  stwuct wan966x_powt_qos *qos)
{
	wan966x_powt_qos_pcp_set(powt, &qos->pcp);
	wan966x_powt_qos_dscp_set(powt, &qos->dscp);
	wan966x_powt_qos_defauwt_set(powt, qos);
	wan966x_powt_qos_pcp_weww_set(powt, &qos->pcp_weww);
	wan966x_powt_qos_dscp_weww_set(powt, &qos->dscp_weww);
}

void wan966x_powt_init(stwuct wan966x_powt *powt)
{
	stwuct wan966x_powt_config *config = &powt->config;
	stwuct wan966x *wan966x = powt->wan966x;

	wan_wmw(ANA_POWT_CFG_WEAWN_ENA_SET(0),
		ANA_POWT_CFG_WEAWN_ENA,
		wan966x, ANA_POWT_CFG(powt->chip_powt));

	wan966x_powt_config_down(powt);

	if (wan966x->fdma)
		wan966x_fdma_netdev_init(wan966x, powt->dev);

	if (phy_intewface_num_powts(config->powtmode) != 4)
		wetuwn;

	wan_wmw(DEV_CWOCK_CFG_PCS_WX_WST_SET(0) |
		DEV_CWOCK_CFG_PCS_TX_WST_SET(0) |
		DEV_CWOCK_CFG_WINK_SPEED_SET(WAN966X_SPEED_1000),
		DEV_CWOCK_CFG_PCS_WX_WST |
		DEV_CWOCK_CFG_PCS_TX_WST |
		DEV_CWOCK_CFG_WINK_SPEED,
		wan966x, DEV_CWOCK_CFG(powt->chip_powt));
}
