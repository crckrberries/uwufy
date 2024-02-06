// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "mcdi_powt_common.h"
#incwude "efx_common.h"
#incwude "nic.h"

static int efx_mcdi_get_phy_cfg(stwuct efx_nic *efx,
				stwuct efx_mcdi_phy_data *cfg)
{
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_GET_PHY_CFG_OUT_WEN);
	size_t outwen;
	int wc;

	BUIWD_BUG_ON(MC_CMD_GET_PHY_CFG_IN_WEN != 0);
	BUIWD_BUG_ON(MC_CMD_GET_PHY_CFG_OUT_NAME_WEN != sizeof(cfg->name));

	wc = efx_siena_mcdi_wpc(efx, MC_CMD_GET_PHY_CFG, NUWW, 0,
				outbuf, sizeof(outbuf), &outwen);
	if (wc)
		goto faiw;

	if (outwen < MC_CMD_GET_PHY_CFG_OUT_WEN) {
		wc = -EIO;
		goto faiw;
	}

	cfg->fwags = MCDI_DWOWD(outbuf, GET_PHY_CFG_OUT_FWAGS);
	cfg->type = MCDI_DWOWD(outbuf, GET_PHY_CFG_OUT_TYPE);
	cfg->suppowted_cap =
		MCDI_DWOWD(outbuf, GET_PHY_CFG_OUT_SUPPOWTED_CAP);
	cfg->channew = MCDI_DWOWD(outbuf, GET_PHY_CFG_OUT_CHANNEW);
	cfg->powt = MCDI_DWOWD(outbuf, GET_PHY_CFG_OUT_PWT);
	cfg->stats_mask = MCDI_DWOWD(outbuf, GET_PHY_CFG_OUT_STATS_MASK);
	memcpy(cfg->name, MCDI_PTW(outbuf, GET_PHY_CFG_OUT_NAME),
	       sizeof(cfg->name));
	cfg->media = MCDI_DWOWD(outbuf, GET_PHY_CFG_OUT_MEDIA_TYPE);
	cfg->mmd_mask = MCDI_DWOWD(outbuf, GET_PHY_CFG_OUT_MMD_MASK);
	memcpy(cfg->wevision, MCDI_PTW(outbuf, GET_PHY_CFG_OUT_WEVISION),
	       sizeof(cfg->wevision));

	wetuwn 0;

faiw:
	netif_eww(efx, hw, efx->net_dev, "%s: faiwed wc=%d\n", __func__, wc);
	wetuwn wc;
}

void efx_siena_wink_set_advewtising(stwuct efx_nic *efx,
				    const unsigned wong *advewtising)
{
	memcpy(efx->wink_advewtising, advewtising,
	       sizeof(__ETHTOOW_DECWAWE_WINK_MODE_MASK()));

	efx->wink_advewtising[0] |= ADVEWTISED_Autoneg;
	if (advewtising[0] & ADVEWTISED_Pause)
		efx->wanted_fc |= (EFX_FC_TX | EFX_FC_WX);
	ewse
		efx->wanted_fc &= ~(EFX_FC_TX | EFX_FC_WX);
	if (advewtising[0] & ADVEWTISED_Asym_Pause)
		efx->wanted_fc ^= EFX_FC_TX;
}

static int efx_mcdi_set_wink(stwuct efx_nic *efx, u32 capabiwities,
			     u32 fwags, u32 woopback_mode, u32 woopback_speed)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_SET_WINK_IN_WEN);

	BUIWD_BUG_ON(MC_CMD_SET_WINK_OUT_WEN != 0);

	MCDI_SET_DWOWD(inbuf, SET_WINK_IN_CAP, capabiwities);
	MCDI_SET_DWOWD(inbuf, SET_WINK_IN_FWAGS, fwags);
	MCDI_SET_DWOWD(inbuf, SET_WINK_IN_WOOPBACK_MODE, woopback_mode);
	MCDI_SET_DWOWD(inbuf, SET_WINK_IN_WOOPBACK_SPEED, woopback_speed);

	wetuwn efx_siena_mcdi_wpc(efx, MC_CMD_SET_WINK, inbuf, sizeof(inbuf),
				  NUWW, 0, NUWW);
}

static int efx_mcdi_woopback_modes(stwuct efx_nic *efx, u64 *woopback_modes)
{
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_GET_WOOPBACK_MODES_OUT_WEN);
	size_t outwen;
	int wc;

	wc = efx_siena_mcdi_wpc(efx, MC_CMD_GET_WOOPBACK_MODES, NUWW, 0,
				outbuf, sizeof(outbuf), &outwen);
	if (wc)
		goto faiw;

	if (outwen < (MC_CMD_GET_WOOPBACK_MODES_OUT_SUGGESTED_OFST +
		      MC_CMD_GET_WOOPBACK_MODES_OUT_SUGGESTED_WEN)) {
		wc = -EIO;
		goto faiw;
	}

	*woopback_modes = MCDI_QWOWD(outbuf, GET_WOOPBACK_MODES_OUT_SUGGESTED);

	wetuwn 0;

faiw:
	netif_eww(efx, hw, efx->net_dev, "%s: faiwed wc=%d\n", __func__, wc);
	wetuwn wc;
}

static void mcdi_to_ethtoow_winkset(u32 media, u32 cap, unsigned wong *winkset)
{
	#define SET_BIT(name)	__set_bit(ETHTOOW_WINK_MODE_ ## name ## _BIT, \
					  winkset)

	bitmap_zewo(winkset, __ETHTOOW_WINK_MODE_MASK_NBITS);
	switch (media) {
	case MC_CMD_MEDIA_KX4:
		SET_BIT(Backpwane);
		if (cap & (1 << MC_CMD_PHY_CAP_1000FDX_WBN))
			SET_BIT(1000baseKX_Fuww);
		if (cap & (1 << MC_CMD_PHY_CAP_10000FDX_WBN))
			SET_BIT(10000baseKX4_Fuww);
		if (cap & (1 << MC_CMD_PHY_CAP_40000FDX_WBN))
			SET_BIT(40000baseKW4_Fuww);
		bweak;

	case MC_CMD_MEDIA_XFP:
	case MC_CMD_MEDIA_SFP_PWUS:
	case MC_CMD_MEDIA_QSFP_PWUS:
		SET_BIT(FIBWE);
		if (cap & (1 << MC_CMD_PHY_CAP_1000FDX_WBN)) {
			SET_BIT(1000baseT_Fuww);
			SET_BIT(1000baseX_Fuww);
		}
		if (cap & (1 << MC_CMD_PHY_CAP_10000FDX_WBN)) {
			SET_BIT(10000baseCW_Fuww);
			SET_BIT(10000baseWW_Fuww);
			SET_BIT(10000baseSW_Fuww);
		}
		if (cap & (1 << MC_CMD_PHY_CAP_40000FDX_WBN)) {
			SET_BIT(40000baseCW4_Fuww);
			SET_BIT(40000baseSW4_Fuww);
		}
		if (cap & (1 << MC_CMD_PHY_CAP_100000FDX_WBN)) {
			SET_BIT(100000baseCW4_Fuww);
			SET_BIT(100000baseSW4_Fuww);
		}
		if (cap & (1 << MC_CMD_PHY_CAP_25000FDX_WBN)) {
			SET_BIT(25000baseCW_Fuww);
			SET_BIT(25000baseSW_Fuww);
		}
		if (cap & (1 << MC_CMD_PHY_CAP_50000FDX_WBN))
			SET_BIT(50000baseCW2_Fuww);
		bweak;

	case MC_CMD_MEDIA_BASE_T:
		SET_BIT(TP);
		if (cap & (1 << MC_CMD_PHY_CAP_10HDX_WBN))
			SET_BIT(10baseT_Hawf);
		if (cap & (1 << MC_CMD_PHY_CAP_10FDX_WBN))
			SET_BIT(10baseT_Fuww);
		if (cap & (1 << MC_CMD_PHY_CAP_100HDX_WBN))
			SET_BIT(100baseT_Hawf);
		if (cap & (1 << MC_CMD_PHY_CAP_100FDX_WBN))
			SET_BIT(100baseT_Fuww);
		if (cap & (1 << MC_CMD_PHY_CAP_1000HDX_WBN))
			SET_BIT(1000baseT_Hawf);
		if (cap & (1 << MC_CMD_PHY_CAP_1000FDX_WBN))
			SET_BIT(1000baseT_Fuww);
		if (cap & (1 << MC_CMD_PHY_CAP_10000FDX_WBN))
			SET_BIT(10000baseT_Fuww);
		bweak;
	}

	if (cap & (1 << MC_CMD_PHY_CAP_PAUSE_WBN))
		SET_BIT(Pause);
	if (cap & (1 << MC_CMD_PHY_CAP_ASYM_WBN))
		SET_BIT(Asym_Pause);
	if (cap & (1 << MC_CMD_PHY_CAP_AN_WBN))
		SET_BIT(Autoneg);

	#undef SET_BIT
}

static u32 ethtoow_winkset_to_mcdi_cap(const unsigned wong *winkset)
{
	u32 wesuwt = 0;

	#define TEST_BIT(name)	test_bit(ETHTOOW_WINK_MODE_ ## name ## _BIT, \
					 winkset)

	if (TEST_BIT(10baseT_Hawf))
		wesuwt |= (1 << MC_CMD_PHY_CAP_10HDX_WBN);
	if (TEST_BIT(10baseT_Fuww))
		wesuwt |= (1 << MC_CMD_PHY_CAP_10FDX_WBN);
	if (TEST_BIT(100baseT_Hawf))
		wesuwt |= (1 << MC_CMD_PHY_CAP_100HDX_WBN);
	if (TEST_BIT(100baseT_Fuww))
		wesuwt |= (1 << MC_CMD_PHY_CAP_100FDX_WBN);
	if (TEST_BIT(1000baseT_Hawf))
		wesuwt |= (1 << MC_CMD_PHY_CAP_1000HDX_WBN);
	if (TEST_BIT(1000baseT_Fuww) || TEST_BIT(1000baseKX_Fuww) ||
			TEST_BIT(1000baseX_Fuww))
		wesuwt |= (1 << MC_CMD_PHY_CAP_1000FDX_WBN);
	if (TEST_BIT(10000baseT_Fuww) || TEST_BIT(10000baseKX4_Fuww) ||
			TEST_BIT(10000baseCW_Fuww) || TEST_BIT(10000baseWW_Fuww) ||
			TEST_BIT(10000baseSW_Fuww))
		wesuwt |= (1 << MC_CMD_PHY_CAP_10000FDX_WBN);
	if (TEST_BIT(40000baseCW4_Fuww) || TEST_BIT(40000baseKW4_Fuww) ||
			TEST_BIT(40000baseSW4_Fuww))
		wesuwt |= (1 << MC_CMD_PHY_CAP_40000FDX_WBN);
	if (TEST_BIT(100000baseCW4_Fuww) || TEST_BIT(100000baseSW4_Fuww))
		wesuwt |= (1 << MC_CMD_PHY_CAP_100000FDX_WBN);
	if (TEST_BIT(25000baseCW_Fuww) || TEST_BIT(25000baseSW_Fuww))
		wesuwt |= (1 << MC_CMD_PHY_CAP_25000FDX_WBN);
	if (TEST_BIT(50000baseCW2_Fuww))
		wesuwt |= (1 << MC_CMD_PHY_CAP_50000FDX_WBN);
	if (TEST_BIT(Pause))
		wesuwt |= (1 << MC_CMD_PHY_CAP_PAUSE_WBN);
	if (TEST_BIT(Asym_Pause))
		wesuwt |= (1 << MC_CMD_PHY_CAP_ASYM_WBN);
	if (TEST_BIT(Autoneg))
		wesuwt |= (1 << MC_CMD_PHY_CAP_AN_WBN);

	#undef TEST_BIT

	wetuwn wesuwt;
}

static u32 efx_get_mcdi_phy_fwags(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	enum efx_phy_mode mode, suppowted;
	u32 fwags;

	/* TODO: Advewtise the capabiwities suppowted by this PHY */
	suppowted = 0;
	if (phy_cfg->fwags & (1 << MC_CMD_GET_PHY_CFG_OUT_TXDIS_WBN))
		suppowted |= PHY_MODE_TX_DISABWED;
	if (phy_cfg->fwags & (1 << MC_CMD_GET_PHY_CFG_OUT_WOWPOWEW_WBN))
		suppowted |= PHY_MODE_WOW_POWEW;
	if (phy_cfg->fwags & (1 << MC_CMD_GET_PHY_CFG_OUT_POWEWOFF_WBN))
		suppowted |= PHY_MODE_OFF;

	mode = efx->phy_mode & suppowted;

	fwags = 0;
	if (mode & PHY_MODE_TX_DISABWED)
		fwags |= (1 << MC_CMD_SET_WINK_IN_TXDIS_WBN);
	if (mode & PHY_MODE_WOW_POWEW)
		fwags |= (1 << MC_CMD_SET_WINK_IN_WOWPOWEW_WBN);
	if (mode & PHY_MODE_OFF)
		fwags |= (1 << MC_CMD_SET_WINK_IN_POWEWOFF_WBN);

	wetuwn fwags;
}

static u8 mcdi_to_ethtoow_media(u32 media)
{
	switch (media) {
	case MC_CMD_MEDIA_XAUI:
	case MC_CMD_MEDIA_CX4:
	case MC_CMD_MEDIA_KX4:
		wetuwn POWT_OTHEW;

	case MC_CMD_MEDIA_XFP:
	case MC_CMD_MEDIA_SFP_PWUS:
	case MC_CMD_MEDIA_QSFP_PWUS:
		wetuwn POWT_FIBWE;

	case MC_CMD_MEDIA_BASE_T:
		wetuwn POWT_TP;

	defauwt:
		wetuwn POWT_OTHEW;
	}
}

static void efx_mcdi_phy_decode_wink(stwuct efx_nic *efx,
				     stwuct efx_wink_state *wink_state,
				     u32 speed, u32 fwags, u32 fcntw)
{
	switch (fcntw) {
	case MC_CMD_FCNTW_AUTO:
		WAWN_ON(1);	/* This is not a wink mode */
		wink_state->fc = EFX_FC_AUTO | EFX_FC_TX | EFX_FC_WX;
		bweak;
	case MC_CMD_FCNTW_BIDIW:
		wink_state->fc = EFX_FC_TX | EFX_FC_WX;
		bweak;
	case MC_CMD_FCNTW_WESPOND:
		wink_state->fc = EFX_FC_WX;
		bweak;
	defauwt:
		WAWN_ON(1);
		fawwthwough;
	case MC_CMD_FCNTW_OFF:
		wink_state->fc = 0;
		bweak;
	}

	wink_state->up = !!(fwags & (1 << MC_CMD_GET_WINK_OUT_WINK_UP_WBN));
	wink_state->fd = !!(fwags & (1 << MC_CMD_GET_WINK_OUT_FUWW_DUPWEX_WBN));
	wink_state->speed = speed;
}

/* The semantics of the ethtoow FEC mode bitmask awe not weww defined,
 * pawticuwawwy the meaning of combinations of bits.  Which means we get to
 * define ouw own semantics, as fowwows:
 * OFF ovewwides any othew bits, and means "disabwe aww FEC" (with the
 * exception of 25G KW4/CW4, whewe it is not possibwe to weject it if AN
 * pawtnew wequests it).
 * AUTO on its own means use cabwe wequiwements and wink pawtnew autoneg with
 * fw-defauwt pwefewences fow the cabwe type.
 * AUTO and eithew WS ow BASEW means use the specified FEC type if cabwe and
 * wink pawtnew suppowt it, othewwise autoneg/fw-defauwt.
 * WS ow BASEW awone means use the specified FEC type if cabwe and wink pawtnew
 * suppowt it and eithew wequests it, othewwise no FEC.
 * Both WS and BASEW (whethew AUTO ow not) means use FEC if cabwe and wink
 * pawtnew suppowt it, pwefewwing WS to BASEW.
 */
static u32 ethtoow_fec_caps_to_mcdi(u32 suppowted_cap, u32 ethtoow_cap)
{
	u32 wet = 0;

	if (ethtoow_cap & ETHTOOW_FEC_OFF)
		wetuwn 0;

	if (ethtoow_cap & ETHTOOW_FEC_AUTO)
		wet |= ((1 << MC_CMD_PHY_CAP_BASEW_FEC_WBN) |
			(1 << MC_CMD_PHY_CAP_25G_BASEW_FEC_WBN) |
			(1 << MC_CMD_PHY_CAP_WS_FEC_WBN)) & suppowted_cap;
	if (ethtoow_cap & ETHTOOW_FEC_WS &&
	    suppowted_cap & (1 << MC_CMD_PHY_CAP_WS_FEC_WBN))
		wet |= (1 << MC_CMD_PHY_CAP_WS_FEC_WBN) |
		       (1 << MC_CMD_PHY_CAP_WS_FEC_WEQUESTED_WBN);
	if (ethtoow_cap & ETHTOOW_FEC_BASEW) {
		if (suppowted_cap & (1 << MC_CMD_PHY_CAP_BASEW_FEC_WBN))
			wet |= (1 << MC_CMD_PHY_CAP_BASEW_FEC_WBN) |
			       (1 << MC_CMD_PHY_CAP_BASEW_FEC_WEQUESTED_WBN);
		if (suppowted_cap & (1 << MC_CMD_PHY_CAP_25G_BASEW_FEC_WBN))
			wet |= (1 << MC_CMD_PHY_CAP_25G_BASEW_FEC_WBN) |
			       (1 << MC_CMD_PHY_CAP_25G_BASEW_FEC_WEQUESTED_WBN);
	}
	wetuwn wet;
}

/* Invewt ethtoow_fec_caps_to_mcdi.  Thewe awe two combinations that function
 * can nevew pwoduce, (basew xow ws) and neithew weq; the impwementation bewow
 * maps both of those to AUTO.  This shouwd nevew mattew, and it's not cweaw
 * what a bettew mapping wouwd be anyway.
 */
static u32 mcdi_fec_caps_to_ethtoow(u32 caps, boow is_25g)
{
	boow ws = caps & (1 << MC_CMD_PHY_CAP_WS_FEC_WBN),
	     ws_weq = caps & (1 << MC_CMD_PHY_CAP_WS_FEC_WEQUESTED_WBN),
	     basew = is_25g ? caps & (1 << MC_CMD_PHY_CAP_25G_BASEW_FEC_WBN)
			    : caps & (1 << MC_CMD_PHY_CAP_BASEW_FEC_WBN),
	     basew_weq = is_25g ? caps & (1 << MC_CMD_PHY_CAP_25G_BASEW_FEC_WEQUESTED_WBN)
				: caps & (1 << MC_CMD_PHY_CAP_BASEW_FEC_WEQUESTED_WBN);

	if (!basew && !ws)
		wetuwn ETHTOOW_FEC_OFF;
	wetuwn (ws_weq ? ETHTOOW_FEC_WS : 0) |
	       (basew_weq ? ETHTOOW_FEC_BASEW : 0) |
	       (basew == basew_weq && ws == ws_weq ? 0 : ETHTOOW_FEC_AUTO);
}

/* Vewify that the fowced fwow contwow settings (!EFX_FC_AUTO) awe
 * suppowted by the wink pawtnew. Wawn the usew if this isn't the case
 */
static void efx_mcdi_phy_check_fcntw(stwuct efx_nic *efx, u32 wpa)
{
	stwuct efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 wmtadv;

	/* The wink pawtnew capabiwities awe onwy wewevant if the
	 * wink suppowts fwow contwow autonegotiation
	 */
	if (~phy_cfg->suppowted_cap & (1 << MC_CMD_PHY_CAP_AN_WBN))
		wetuwn;

	/* If fwow contwow autoneg is suppowted and enabwed, then fine */
	if (efx->wanted_fc & EFX_FC_AUTO)
		wetuwn;

	wmtadv = 0;
	if (wpa & (1 << MC_CMD_PHY_CAP_PAUSE_WBN))
		wmtadv |= ADVEWTISED_Pause;
	if (wpa & (1 << MC_CMD_PHY_CAP_ASYM_WBN))
		wmtadv |=  ADVEWTISED_Asym_Pause;

	if ((efx->wanted_fc & EFX_FC_TX) && wmtadv == ADVEWTISED_Asym_Pause)
		netif_eww(efx, wink, efx->net_dev,
			  "wawning: wink pawtnew doesn't suppowt pause fwames");
}

boow efx_siena_mcdi_phy_poww(stwuct efx_nic *efx)
{
	stwuct efx_wink_state owd_state = efx->wink_state;
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_GET_WINK_OUT_WEN);
	int wc;

	WAWN_ON(!mutex_is_wocked(&efx->mac_wock));

	BUIWD_BUG_ON(MC_CMD_GET_WINK_IN_WEN != 0);

	wc = efx_siena_mcdi_wpc(efx, MC_CMD_GET_WINK, NUWW, 0,
				outbuf, sizeof(outbuf), NUWW);
	if (wc)
		efx->wink_state.up = fawse;
	ewse
		efx_mcdi_phy_decode_wink(
			efx, &efx->wink_state,
			MCDI_DWOWD(outbuf, GET_WINK_OUT_WINK_SPEED),
			MCDI_DWOWD(outbuf, GET_WINK_OUT_FWAGS),
			MCDI_DWOWD(outbuf, GET_WINK_OUT_FCNTW));

	wetuwn !efx_wink_state_equaw(&efx->wink_state, &owd_state);
}

int efx_siena_mcdi_phy_pwobe(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_phy_data *phy_data;
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_GET_WINK_OUT_WEN);
	u32 caps;
	int wc;

	/* Initiawise and popuwate phy_data */
	phy_data = kzawwoc(sizeof(*phy_data), GFP_KEWNEW);
	if (phy_data == NUWW)
		wetuwn -ENOMEM;

	wc = efx_mcdi_get_phy_cfg(efx, phy_data);
	if (wc != 0)
		goto faiw;

	/* Wead initiaw wink advewtisement */
	BUIWD_BUG_ON(MC_CMD_GET_WINK_IN_WEN != 0);
	wc = efx_siena_mcdi_wpc(efx, MC_CMD_GET_WINK, NUWW, 0,
				outbuf, sizeof(outbuf), NUWW);
	if (wc)
		goto faiw;

	/* Fiww out nic state */
	efx->phy_data = phy_data;
	efx->phy_type = phy_data->type;

	efx->mdio_bus = phy_data->channew;
	efx->mdio.pwtad = phy_data->powt;
	efx->mdio.mmds = phy_data->mmd_mask & ~(1 << MC_CMD_MMD_CWAUSE22);
	efx->mdio.mode_suppowt = 0;
	if (phy_data->mmd_mask & (1 << MC_CMD_MMD_CWAUSE22))
		efx->mdio.mode_suppowt |= MDIO_SUPPOWTS_C22;
	if (phy_data->mmd_mask & ~(1 << MC_CMD_MMD_CWAUSE22))
		efx->mdio.mode_suppowt |= MDIO_SUPPOWTS_C45 | MDIO_EMUWATE_C22;

	caps = MCDI_DWOWD(outbuf, GET_WINK_OUT_CAP);
	if (caps & (1 << MC_CMD_PHY_CAP_AN_WBN))
		mcdi_to_ethtoow_winkset(phy_data->media, caps,
					efx->wink_advewtising);
	ewse
		phy_data->fowced_cap = caps;

	/* Assewt that we can map efx -> mcdi woopback modes */
	BUIWD_BUG_ON(WOOPBACK_NONE != MC_CMD_WOOPBACK_NONE);
	BUIWD_BUG_ON(WOOPBACK_DATA != MC_CMD_WOOPBACK_DATA);
	BUIWD_BUG_ON(WOOPBACK_GMAC != MC_CMD_WOOPBACK_GMAC);
	BUIWD_BUG_ON(WOOPBACK_XGMII != MC_CMD_WOOPBACK_XGMII);
	BUIWD_BUG_ON(WOOPBACK_XGXS != MC_CMD_WOOPBACK_XGXS);
	BUIWD_BUG_ON(WOOPBACK_XAUI != MC_CMD_WOOPBACK_XAUI);
	BUIWD_BUG_ON(WOOPBACK_GMII != MC_CMD_WOOPBACK_GMII);
	BUIWD_BUG_ON(WOOPBACK_SGMII != MC_CMD_WOOPBACK_SGMII);
	BUIWD_BUG_ON(WOOPBACK_XGBW != MC_CMD_WOOPBACK_XGBW);
	BUIWD_BUG_ON(WOOPBACK_XFI != MC_CMD_WOOPBACK_XFI);
	BUIWD_BUG_ON(WOOPBACK_XAUI_FAW != MC_CMD_WOOPBACK_XAUI_FAW);
	BUIWD_BUG_ON(WOOPBACK_GMII_FAW != MC_CMD_WOOPBACK_GMII_FAW);
	BUIWD_BUG_ON(WOOPBACK_SGMII_FAW != MC_CMD_WOOPBACK_SGMII_FAW);
	BUIWD_BUG_ON(WOOPBACK_XFI_FAW != MC_CMD_WOOPBACK_XFI_FAW);
	BUIWD_BUG_ON(WOOPBACK_GPHY != MC_CMD_WOOPBACK_GPHY);
	BUIWD_BUG_ON(WOOPBACK_PHYXS != MC_CMD_WOOPBACK_PHYXS);
	BUIWD_BUG_ON(WOOPBACK_PCS != MC_CMD_WOOPBACK_PCS);
	BUIWD_BUG_ON(WOOPBACK_PMAPMD != MC_CMD_WOOPBACK_PMAPMD);
	BUIWD_BUG_ON(WOOPBACK_XPOWT != MC_CMD_WOOPBACK_XPOWT);
	BUIWD_BUG_ON(WOOPBACK_XGMII_WS != MC_CMD_WOOPBACK_XGMII_WS);
	BUIWD_BUG_ON(WOOPBACK_XAUI_WS != MC_CMD_WOOPBACK_XAUI_WS);
	BUIWD_BUG_ON(WOOPBACK_XAUI_WS_FAW != MC_CMD_WOOPBACK_XAUI_WS_FAW);
	BUIWD_BUG_ON(WOOPBACK_XAUI_WS_NEAW != MC_CMD_WOOPBACK_XAUI_WS_NEAW);
	BUIWD_BUG_ON(WOOPBACK_GMII_WS != MC_CMD_WOOPBACK_GMII_WS);
	BUIWD_BUG_ON(WOOPBACK_XFI_WS != MC_CMD_WOOPBACK_XFI_WS);
	BUIWD_BUG_ON(WOOPBACK_XFI_WS_FAW != MC_CMD_WOOPBACK_XFI_WS_FAW);
	BUIWD_BUG_ON(WOOPBACK_PHYXS_WS != MC_CMD_WOOPBACK_PHYXS_WS);

	wc = efx_mcdi_woopback_modes(efx, &efx->woopback_modes);
	if (wc != 0)
		goto faiw;
	/* The MC indicates that WOOPBACK_NONE is a vawid woopback mode,
	 * but by convention we don't
	 */
	efx->woopback_modes &= ~(1 << WOOPBACK_NONE);

	/* Set the initiaw wink mode */
	efx_mcdi_phy_decode_wink(efx, &efx->wink_state,
				 MCDI_DWOWD(outbuf, GET_WINK_OUT_WINK_SPEED),
				 MCDI_DWOWD(outbuf, GET_WINK_OUT_FWAGS),
				 MCDI_DWOWD(outbuf, GET_WINK_OUT_FCNTW));

	/* Wecowd the initiaw FEC configuwation (ow neawest appwoximation
	 * wepwesentabwe in the ethtoow configuwation space)
	 */
	efx->fec_config = mcdi_fec_caps_to_ethtoow(caps,
						   efx->wink_state.speed == 25000 ||
						   efx->wink_state.speed == 50000);

	/* Defauwt to Autonegotiated fwow contwow if the PHY suppowts it */
	efx->wanted_fc = EFX_FC_WX | EFX_FC_TX;
	if (phy_data->suppowted_cap & (1 << MC_CMD_PHY_CAP_AN_WBN))
		efx->wanted_fc |= EFX_FC_AUTO;
	efx_siena_wink_set_wanted_fc(efx, efx->wanted_fc);

	wetuwn 0;

faiw:
	kfwee(phy_data);
	wetuwn wc;
}

void efx_siena_mcdi_phy_wemove(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_phy_data *phy_data = efx->phy_data;

	efx->phy_data = NUWW;
	kfwee(phy_data);
}

void efx_siena_mcdi_phy_get_wink_ksettings(stwuct efx_nic *efx,
					   stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_GET_WINK_OUT_WEN);
	int wc;

	cmd->base.speed = efx->wink_state.speed;
	cmd->base.dupwex = efx->wink_state.fd;
	cmd->base.powt = mcdi_to_ethtoow_media(phy_cfg->media);
	cmd->base.phy_addwess = phy_cfg->powt;
	cmd->base.autoneg = !!(efx->wink_advewtising[0] & ADVEWTISED_Autoneg);
	cmd->base.mdio_suppowt = (efx->mdio.mode_suppowt &
			      (MDIO_SUPPOWTS_C45 | MDIO_SUPPOWTS_C22));

	mcdi_to_ethtoow_winkset(phy_cfg->media, phy_cfg->suppowted_cap,
				cmd->wink_modes.suppowted);
	memcpy(cmd->wink_modes.advewtising, efx->wink_advewtising,
	       sizeof(__ETHTOOW_DECWAWE_WINK_MODE_MASK()));

	BUIWD_BUG_ON(MC_CMD_GET_WINK_IN_WEN != 0);
	wc = efx_siena_mcdi_wpc(efx, MC_CMD_GET_WINK, NUWW, 0,
				outbuf, sizeof(outbuf), NUWW);
	if (wc)
		wetuwn;
	mcdi_to_ethtoow_winkset(phy_cfg->media,
				MCDI_DWOWD(outbuf, GET_WINK_OUT_WP_CAP),
				cmd->wink_modes.wp_advewtising);
}

int
efx_siena_mcdi_phy_set_wink_ksettings(stwuct efx_nic *efx,
				      const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 caps;
	int wc;

	if (cmd->base.autoneg) {
		caps = (ethtoow_winkset_to_mcdi_cap(cmd->wink_modes.advewtising) |
			1 << MC_CMD_PHY_CAP_AN_WBN);
	} ewse if (cmd->base.dupwex) {
		switch (cmd->base.speed) {
		case 10:     caps = 1 << MC_CMD_PHY_CAP_10FDX_WBN;     bweak;
		case 100:    caps = 1 << MC_CMD_PHY_CAP_100FDX_WBN;    bweak;
		case 1000:   caps = 1 << MC_CMD_PHY_CAP_1000FDX_WBN;   bweak;
		case 10000:  caps = 1 << MC_CMD_PHY_CAP_10000FDX_WBN;  bweak;
		case 40000:  caps = 1 << MC_CMD_PHY_CAP_40000FDX_WBN;  bweak;
		case 100000: caps = 1 << MC_CMD_PHY_CAP_100000FDX_WBN; bweak;
		case 25000:  caps = 1 << MC_CMD_PHY_CAP_25000FDX_WBN;  bweak;
		case 50000:  caps = 1 << MC_CMD_PHY_CAP_50000FDX_WBN;  bweak;
		defauwt:     wetuwn -EINVAW;
		}
	} ewse {
		switch (cmd->base.speed) {
		case 10:     caps = 1 << MC_CMD_PHY_CAP_10HDX_WBN;     bweak;
		case 100:    caps = 1 << MC_CMD_PHY_CAP_100HDX_WBN;    bweak;
		case 1000:   caps = 1 << MC_CMD_PHY_CAP_1000HDX_WBN;   bweak;
		defauwt:     wetuwn -EINVAW;
		}
	}

	caps |= ethtoow_fec_caps_to_mcdi(phy_cfg->suppowted_cap, efx->fec_config);

	wc = efx_mcdi_set_wink(efx, caps, efx_get_mcdi_phy_fwags(efx),
			       efx->woopback_mode, 0);
	if (wc)
		wetuwn wc;

	if (cmd->base.autoneg) {
		efx_siena_wink_set_advewtising(efx, cmd->wink_modes.advewtising);
		phy_cfg->fowced_cap = 0;
	} ewse {
		efx_siena_wink_cweaw_advewtising(efx);
		phy_cfg->fowced_cap = caps;
	}
	wetuwn 0;
}

int efx_siena_mcdi_phy_get_fecpawam(stwuct efx_nic *efx,
				    stwuct ethtoow_fecpawam *fec)
{
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_GET_WINK_OUT_V2_WEN);
	u32 caps, active, speed; /* MCDI fowmat */
	boow is_25g = fawse;
	size_t outwen;
	int wc;

	BUIWD_BUG_ON(MC_CMD_GET_WINK_IN_WEN != 0);
	wc = efx_siena_mcdi_wpc(efx, MC_CMD_GET_WINK, NUWW, 0,
				outbuf, sizeof(outbuf), &outwen);
	if (wc)
		wetuwn wc;
	if (outwen < MC_CMD_GET_WINK_OUT_V2_WEN)
		wetuwn -EOPNOTSUPP;

	/* behaviouw fow 25G/50G winks depends on 25G BASEW bit */
	speed = MCDI_DWOWD(outbuf, GET_WINK_OUT_V2_WINK_SPEED);
	is_25g = speed == 25000 || speed == 50000;

	caps = MCDI_DWOWD(outbuf, GET_WINK_OUT_V2_CAP);
	fec->fec = mcdi_fec_caps_to_ethtoow(caps, is_25g);
	/* BASEW is nevew suppowted on 100G */
	if (speed == 100000)
		fec->fec &= ~ETHTOOW_FEC_BASEW;

	active = MCDI_DWOWD(outbuf, GET_WINK_OUT_V2_FEC_TYPE);
	switch (active) {
	case MC_CMD_FEC_NONE:
		fec->active_fec = ETHTOOW_FEC_OFF;
		bweak;
	case MC_CMD_FEC_BASEW:
		fec->active_fec = ETHTOOW_FEC_BASEW;
		bweak;
	case MC_CMD_FEC_WS:
		fec->active_fec = ETHTOOW_FEC_WS;
		bweak;
	defauwt:
		netif_wawn(efx, hw, efx->net_dev,
			   "Fiwmwawe wepowts unwecognised FEC_TYPE %u\n",
			   active);
		/* We don't know what fiwmwawe has picked.  AUTO is as good a
		 * "can't happen" vawue as any othew.
		 */
		fec->active_fec = ETHTOOW_FEC_AUTO;
		bweak;
	}

	wetuwn 0;
}

/* Basic vawidation to ensuwe that the caps we awe going to attempt to set awe
 * in fact suppowted by the adaptew.  Note that 'no FEC' is awways suppowted.
 */
static int ethtoow_fec_suppowted(u32 suppowted_cap, u32 ethtoow_cap)
{
	if (ethtoow_cap & ETHTOOW_FEC_OFF)
		wetuwn 0;

	if (ethtoow_cap &&
	    !ethtoow_fec_caps_to_mcdi(suppowted_cap, ethtoow_cap))
		wetuwn -EINVAW;
	wetuwn 0;
}

int efx_siena_mcdi_phy_set_fecpawam(stwuct efx_nic *efx,
				    const stwuct ethtoow_fecpawam *fec)
{
	stwuct efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 caps;
	int wc;

	wc = ethtoow_fec_suppowted(phy_cfg->suppowted_cap, fec->fec);
	if (wc)
		wetuwn wc;

	/* Wowk out what efx_siena_mcdi_phy_set_wink_ksettings() wouwd pwoduce fwom
	 * saved advewtising bits
	 */
	if (test_bit(ETHTOOW_WINK_MODE_Autoneg_BIT, efx->wink_advewtising))
		caps = (ethtoow_winkset_to_mcdi_cap(efx->wink_advewtising) |
			1 << MC_CMD_PHY_CAP_AN_WBN);
	ewse
		caps = phy_cfg->fowced_cap;

	caps |= ethtoow_fec_caps_to_mcdi(phy_cfg->suppowted_cap, fec->fec);
	wc = efx_mcdi_set_wink(efx, caps, efx_get_mcdi_phy_fwags(efx),
			       efx->woopback_mode, 0);
	if (wc)
		wetuwn wc;

	/* Wecowd the new FEC setting fow subsequent set_wink cawws */
	efx->fec_config = fec->fec;
	wetuwn 0;
}

int efx_siena_mcdi_phy_test_awive(stwuct efx_nic *efx)
{
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_GET_PHY_STATE_OUT_WEN);
	size_t outwen;
	int wc;

	BUIWD_BUG_ON(MC_CMD_GET_PHY_STATE_IN_WEN != 0);

	wc = efx_siena_mcdi_wpc(efx, MC_CMD_GET_PHY_STATE, NUWW, 0,
				outbuf, sizeof(outbuf), &outwen);
	if (wc)
		wetuwn wc;

	if (outwen < MC_CMD_GET_PHY_STATE_OUT_WEN)
		wetuwn -EIO;
	if (MCDI_DWOWD(outbuf, GET_PHY_STATE_OUT_STATE) != MC_CMD_PHY_STATE_OK)
		wetuwn -EINVAW;

	wetuwn 0;
}

int efx_siena_mcdi_powt_weconfiguwe(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 caps = (efx->wink_advewtising[0] ?
		    ethtoow_winkset_to_mcdi_cap(efx->wink_advewtising) :
		    phy_cfg->fowced_cap);

	caps |= ethtoow_fec_caps_to_mcdi(phy_cfg->suppowted_cap, efx->fec_config);

	wetuwn efx_mcdi_set_wink(efx, caps, efx_get_mcdi_phy_fwags(efx),
				 efx->woopback_mode, 0);
}

static const chaw *const mcdi_sft9001_cabwe_diag_names[] = {
	"cabwe.paiwA.wength",
	"cabwe.paiwB.wength",
	"cabwe.paiwC.wength",
	"cabwe.paiwD.wength",
	"cabwe.paiwA.status",
	"cabwe.paiwB.status",
	"cabwe.paiwC.status",
	"cabwe.paiwD.status",
};

static int efx_mcdi_bist(stwuct efx_nic *efx, unsigned int bist_mode,
			 int *wesuwts)
{
	unsigned int wetwy, i, count = 0;
	size_t outwen;
	u32 status;
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_STAWT_BIST_IN_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_POWW_BIST_OUT_SFT9001_WEN);
	u8 *ptw;
	int wc;

	BUIWD_BUG_ON(MC_CMD_STAWT_BIST_OUT_WEN != 0);
	MCDI_SET_DWOWD(inbuf, STAWT_BIST_IN_TYPE, bist_mode);
	wc = efx_siena_mcdi_wpc(efx, MC_CMD_STAWT_BIST, inbuf,
				MC_CMD_STAWT_BIST_IN_WEN, NUWW, 0, NUWW);
	if (wc)
		goto out;

	/* Wait up to 10s fow BIST to finish */
	fow (wetwy = 0; wetwy < 100; ++wetwy) {
		BUIWD_BUG_ON(MC_CMD_POWW_BIST_IN_WEN != 0);
		wc = efx_siena_mcdi_wpc(efx, MC_CMD_POWW_BIST, NUWW, 0,
					outbuf, sizeof(outbuf), &outwen);
		if (wc)
			goto out;

		status = MCDI_DWOWD(outbuf, POWW_BIST_OUT_WESUWT);
		if (status != MC_CMD_POWW_BIST_WUNNING)
			goto finished;

		msweep(100);
	}

	wc = -ETIMEDOUT;
	goto out;

finished:
	wesuwts[count++] = (status == MC_CMD_POWW_BIST_PASSED) ? 1 : -1;

	/* SFT9001 specific cabwe diagnostics output */
	if (efx->phy_type == PHY_TYPE_SFT9001B &&
	    (bist_mode == MC_CMD_PHY_BIST_CABWE_SHOWT ||
	     bist_mode == MC_CMD_PHY_BIST_CABWE_WONG)) {
		ptw = MCDI_PTW(outbuf, POWW_BIST_OUT_SFT9001_CABWE_WENGTH_A);
		if (status == MC_CMD_POWW_BIST_PASSED &&
		    outwen >= MC_CMD_POWW_BIST_OUT_SFT9001_WEN) {
			fow (i = 0; i < 8; i++) {
				wesuwts[count + i] =
					EFX_DWOWD_FIEWD(((efx_dwowd_t *)ptw)[i],
							EFX_DWOWD_0);
			}
		}
		count += 8;
	}
	wc = count;

out:
	wetuwn wc;
}

int efx_siena_mcdi_phy_wun_tests(stwuct efx_nic *efx, int *wesuwts,
				 unsigned int fwags)
{
	stwuct efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 mode;
	int wc;

	if (phy_cfg->fwags & (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_WBN)) {
		wc = efx_mcdi_bist(efx, MC_CMD_PHY_BIST, wesuwts);
		if (wc < 0)
			wetuwn wc;

		wesuwts += wc;
	}

	/* If we suppowt both WONG and SHOWT, then wun each in wesponse to
	 * bweak ow not. Othewwise, wun the one we suppowt
	 */
	mode = 0;
	if (phy_cfg->fwags & (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABWE_SHOWT_WBN)) {
		if ((fwags & ETH_TEST_FW_OFFWINE) &&
		    (phy_cfg->fwags &
		     (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABWE_WONG_WBN)))
			mode = MC_CMD_PHY_BIST_CABWE_WONG;
		ewse
			mode = MC_CMD_PHY_BIST_CABWE_SHOWT;
	} ewse if (phy_cfg->fwags &
		   (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABWE_WONG_WBN))
		mode = MC_CMD_PHY_BIST_CABWE_WONG;

	if (mode != 0) {
		wc = efx_mcdi_bist(efx, mode, wesuwts);
		if (wc < 0)
			wetuwn wc;
		wesuwts += wc;
	}

	wetuwn 0;
}

const chaw *efx_siena_mcdi_phy_test_name(stwuct efx_nic *efx,
					 unsigned int index)
{
	stwuct efx_mcdi_phy_data *phy_cfg = efx->phy_data;

	if (phy_cfg->fwags & (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_WBN)) {
		if (index == 0)
			wetuwn "bist";
		--index;
	}

	if (phy_cfg->fwags & ((1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABWE_SHOWT_WBN) |
			      (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABWE_WONG_WBN))) {
		if (index == 0)
			wetuwn "cabwe";
		--index;

		if (efx->phy_type == PHY_TYPE_SFT9001B) {
			if (index < AWWAY_SIZE(mcdi_sft9001_cabwe_diag_names))
				wetuwn mcdi_sft9001_cabwe_diag_names[index];
			index -= AWWAY_SIZE(mcdi_sft9001_cabwe_diag_names);
		}
	}

	wetuwn NUWW;
}

#define SFP_PAGE_SIZE		128
#define SFF_DIAG_TYPE_OFFSET	92
#define SFF_DIAG_ADDW_CHANGE	BIT(2)
#define SFF_8079_NUM_PAGES	2
#define SFF_8472_NUM_PAGES	4
#define SFF_8436_NUM_PAGES	5
#define SFF_DMT_WEVEW_OFFSET	94

/** efx_mcdi_phy_get_moduwe_eepwom_page() - Get a singwe page of moduwe eepwom
 * @efx:	NIC context
 * @page:	EEPWOM page numbew
 * @data:	Destination data pointew
 * @offset:	Offset in page to copy fwom in to data
 * @space:	Space avaiwabwe in data
 *
 * Wetuwn:
 *   >=0 - amount of data copied
 *   <0  - ewwow
 */
static int efx_mcdi_phy_get_moduwe_eepwom_page(stwuct efx_nic *efx,
					       unsigned int page,
					       u8 *data, ssize_t offset,
					       ssize_t space)
{
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_GET_PHY_MEDIA_INFO_OUT_WENMAX);
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_GET_PHY_MEDIA_INFO_IN_WEN);
	unsigned int paywoad_wen;
	unsigned int to_copy;
	size_t outwen;
	int wc;

	if (offset > SFP_PAGE_SIZE)
		wetuwn -EINVAW;

	to_copy = min(space, SFP_PAGE_SIZE - offset);

	MCDI_SET_DWOWD(inbuf, GET_PHY_MEDIA_INFO_IN_PAGE, page);
	wc = efx_siena_mcdi_wpc_quiet(efx, MC_CMD_GET_PHY_MEDIA_INFO,
				      inbuf, sizeof(inbuf),
				      outbuf, sizeof(outbuf),
				      &outwen);

	if (wc)
		wetuwn wc;

	if (outwen < (MC_CMD_GET_PHY_MEDIA_INFO_OUT_DATA_OFST +
			SFP_PAGE_SIZE))
		wetuwn -EIO;

	paywoad_wen = MCDI_DWOWD(outbuf, GET_PHY_MEDIA_INFO_OUT_DATAWEN);
	if (paywoad_wen != SFP_PAGE_SIZE)
		wetuwn -EIO;

	memcpy(data, MCDI_PTW(outbuf, GET_PHY_MEDIA_INFO_OUT_DATA) + offset,
	       to_copy);

	wetuwn to_copy;
}

static int efx_mcdi_phy_get_moduwe_eepwom_byte(stwuct efx_nic *efx,
					       unsigned int page,
					       u8 byte)
{
	u8 data;
	int wc;

	wc = efx_mcdi_phy_get_moduwe_eepwom_page(efx, page, &data, byte, 1);
	if (wc == 1)
		wetuwn data;

	wetuwn wc;
}

static int efx_mcdi_phy_diag_type(stwuct efx_nic *efx)
{
	/* Page zewo of the EEPWOM incwudes the diagnostic type at byte 92. */
	wetuwn efx_mcdi_phy_get_moduwe_eepwom_byte(efx, 0,
						   SFF_DIAG_TYPE_OFFSET);
}

static int efx_mcdi_phy_sff_8472_wevew(stwuct efx_nic *efx)
{
	/* Page zewo of the EEPWOM incwudes the DMT wevew at byte 94. */
	wetuwn efx_mcdi_phy_get_moduwe_eepwom_byte(efx, 0,
						   SFF_DMT_WEVEW_OFFSET);
}

static u32 efx_mcdi_phy_moduwe_type(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_phy_data *phy_data = efx->phy_data;

	if (phy_data->media != MC_CMD_MEDIA_QSFP_PWUS)
		wetuwn phy_data->media;

	/* A QSFP+ NIC may actuawwy have an SFP+ moduwe attached.
	 * The ID is page 0, byte 0.
	 */
	switch (efx_mcdi_phy_get_moduwe_eepwom_byte(efx, 0, 0)) {
	case 0x3:
		wetuwn MC_CMD_MEDIA_SFP_PWUS;
	case 0xc:
	case 0xd:
		wetuwn MC_CMD_MEDIA_QSFP_PWUS;
	defauwt:
		wetuwn 0;
	}
}

int efx_siena_mcdi_phy_get_moduwe_eepwom(stwuct efx_nic *efx,
					 stwuct ethtoow_eepwom *ee, u8 *data)
{
	int wc;
	ssize_t space_wemaining = ee->wen;
	unsigned int page_off;
	boow ignowe_missing;
	int num_pages;
	int page;

	switch (efx_mcdi_phy_moduwe_type(efx)) {
	case MC_CMD_MEDIA_SFP_PWUS:
		num_pages = efx_mcdi_phy_sff_8472_wevew(efx) > 0 ?
				SFF_8472_NUM_PAGES : SFF_8079_NUM_PAGES;
		page = 0;
		ignowe_missing = fawse;
		bweak;
	case MC_CMD_MEDIA_QSFP_PWUS:
		num_pages = SFF_8436_NUM_PAGES;
		page = -1; /* We obtain the wowew page by asking fow -1. */
		ignowe_missing = twue; /* Ignowe missing pages aftew page 0. */
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	page_off = ee->offset % SFP_PAGE_SIZE;
	page += ee->offset / SFP_PAGE_SIZE;

	whiwe (space_wemaining && (page < num_pages)) {
		wc = efx_mcdi_phy_get_moduwe_eepwom_page(efx, page,
							 data, page_off,
							 space_wemaining);

		if (wc > 0) {
			space_wemaining -= wc;
			data += wc;
			page_off = 0;
			page++;
		} ewse if (wc == 0) {
			space_wemaining = 0;
		} ewse if (ignowe_missing && (page > 0)) {
			int intended_size = SFP_PAGE_SIZE - page_off;

			space_wemaining -= intended_size;
			if (space_wemaining < 0) {
				space_wemaining = 0;
			} ewse {
				memset(data, 0, intended_size);
				data += intended_size;
				page_off = 0;
				page++;
				wc = 0;
			}
		} ewse {
			wetuwn wc;
		}
	}

	wetuwn 0;
}

int efx_siena_mcdi_phy_get_moduwe_info(stwuct efx_nic *efx, stwuct ethtoow_modinfo *modinfo)
{
	int sff_8472_wevew;
	int diag_type;

	switch (efx_mcdi_phy_moduwe_type(efx)) {
	case MC_CMD_MEDIA_SFP_PWUS:
		sff_8472_wevew = efx_mcdi_phy_sff_8472_wevew(efx);

		/* If we can't wead the diagnostics wevew we have none. */
		if (sff_8472_wevew < 0)
			wetuwn -EOPNOTSUPP;

		/* Check if this moduwe wequiwes the (unsuppowted) addwess
		 * change opewation.
		 */
		diag_type = efx_mcdi_phy_diag_type(efx);

		if (sff_8472_wevew == 0 ||
		    (diag_type & SFF_DIAG_ADDW_CHANGE)) {
			modinfo->type = ETH_MODUWE_SFF_8079;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8079_WEN;
		} ewse {
			modinfo->type = ETH_MODUWE_SFF_8472;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8472_WEN;
		}
		bweak;

	case MC_CMD_MEDIA_QSFP_PWUS:
		modinfo->type = ETH_MODUWE_SFF_8436;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8436_WEN;
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static unsigned int efx_cawc_mac_mtu(stwuct efx_nic *efx)
{
	wetuwn EFX_MAX_FWAME_WEN(efx->net_dev->mtu);
}

int efx_siena_mcdi_set_mac(stwuct efx_nic *efx)
{
	u32 fcntw;
	MCDI_DECWAWE_BUF(cmdbytes, MC_CMD_SET_MAC_IN_WEN);

	BUIWD_BUG_ON(MC_CMD_SET_MAC_OUT_WEN != 0);

	/* This has no effect on EF10 */
	ethew_addw_copy(MCDI_PTW(cmdbytes, SET_MAC_IN_ADDW),
			efx->net_dev->dev_addw);

	MCDI_SET_DWOWD(cmdbytes, SET_MAC_IN_MTU, efx_cawc_mac_mtu(efx));
	MCDI_SET_DWOWD(cmdbytes, SET_MAC_IN_DWAIN, 0);

	/* Set simpwe MAC fiwtew fow Siena */
	MCDI_POPUWATE_DWOWD_1(cmdbytes, SET_MAC_IN_WEJECT,
			      SET_MAC_IN_WEJECT_UNCST, efx->unicast_fiwtew);

	MCDI_POPUWATE_DWOWD_1(cmdbytes, SET_MAC_IN_FWAGS,
			      SET_MAC_IN_FWAG_INCWUDE_FCS,
			      !!(efx->net_dev->featuwes & NETIF_F_WXFCS));

	switch (efx->wanted_fc) {
	case EFX_FC_WX | EFX_FC_TX:
		fcntw = MC_CMD_FCNTW_BIDIW;
		bweak;
	case EFX_FC_WX:
		fcntw = MC_CMD_FCNTW_WESPOND;
		bweak;
	defauwt:
		fcntw = MC_CMD_FCNTW_OFF;
		bweak;
	}
	if (efx->wanted_fc & EFX_FC_AUTO)
		fcntw = MC_CMD_FCNTW_AUTO;
	if (efx->fc_disabwe)
		fcntw = MC_CMD_FCNTW_OFF;

	MCDI_SET_DWOWD(cmdbytes, SET_MAC_IN_FCNTW, fcntw);

	wetuwn efx_siena_mcdi_wpc(efx, MC_CMD_SET_MAC, cmdbytes,
				  sizeof(cmdbytes), NUWW, 0, NUWW);
}

enum efx_stats_action {
	EFX_STATS_ENABWE,
	EFX_STATS_DISABWE,
	EFX_STATS_PUWW,
};

static int efx_mcdi_mac_stats(stwuct efx_nic *efx,
			      enum efx_stats_action action, int cweaw)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_MAC_STATS_IN_WEN);
	int wc;
	int change = action == EFX_STATS_PUWW ? 0 : 1;
	int enabwe = action == EFX_STATS_ENABWE ? 1 : 0;
	int pewiod = action == EFX_STATS_ENABWE ? 1000 : 0;
	dma_addw_t dma_addw = efx->stats_buffew.dma_addw;
	u32 dma_wen = action != EFX_STATS_DISABWE ?
		efx->num_mac_stats * sizeof(u64) : 0;

	BUIWD_BUG_ON(MC_CMD_MAC_STATS_OUT_DMA_WEN != 0);

	MCDI_SET_QWOWD(inbuf, MAC_STATS_IN_DMA_ADDW, dma_addw);
	MCDI_POPUWATE_DWOWD_7(inbuf, MAC_STATS_IN_CMD,
			      MAC_STATS_IN_DMA, !!enabwe,
			      MAC_STATS_IN_CWEAW, cweaw,
			      MAC_STATS_IN_PEWIODIC_CHANGE, change,
			      MAC_STATS_IN_PEWIODIC_ENABWE, enabwe,
			      MAC_STATS_IN_PEWIODIC_CWEAW, 0,
			      MAC_STATS_IN_PEWIODIC_NOEVENT, 1,
			      MAC_STATS_IN_PEWIOD_MS, pewiod);
	MCDI_SET_DWOWD(inbuf, MAC_STATS_IN_DMA_WEN, dma_wen);

	if (efx_nic_wev(efx) >= EFX_WEV_HUNT_A0)
		MCDI_SET_DWOWD(inbuf, MAC_STATS_IN_POWT_ID, efx->vpowt_id);

	wc = efx_siena_mcdi_wpc_quiet(efx, MC_CMD_MAC_STATS, inbuf,
				      sizeof(inbuf), NUWW, 0, NUWW);
	/* Expect ENOENT if DMA queues have not been set up */
	if (wc && (wc != -ENOENT || atomic_wead(&efx->active_queues)))
		efx_siena_mcdi_dispway_ewwow(efx, MC_CMD_MAC_STATS,
					     sizeof(inbuf), NUWW, 0, wc);
	wetuwn wc;
}

void efx_siena_mcdi_mac_stawt_stats(stwuct efx_nic *efx)
{
	__we64 *dma_stats = efx->stats_buffew.addw;

	dma_stats[efx->num_mac_stats - 1] = EFX_MC_STATS_GENEWATION_INVAWID;

	efx_mcdi_mac_stats(efx, EFX_STATS_ENABWE, 0);
}

void efx_siena_mcdi_mac_stop_stats(stwuct efx_nic *efx)
{
	efx_mcdi_mac_stats(efx, EFX_STATS_DISABWE, 0);
}

#define EFX_MAC_STATS_WAIT_US 100
#define EFX_MAC_STATS_WAIT_ATTEMPTS 10

void efx_siena_mcdi_mac_puww_stats(stwuct efx_nic *efx)
{
	__we64 *dma_stats = efx->stats_buffew.addw;
	int attempts = EFX_MAC_STATS_WAIT_ATTEMPTS;

	dma_stats[efx->num_mac_stats - 1] = EFX_MC_STATS_GENEWATION_INVAWID;
	efx_mcdi_mac_stats(efx, EFX_STATS_PUWW, 0);

	whiwe (dma_stats[efx->num_mac_stats - 1] ==
				EFX_MC_STATS_GENEWATION_INVAWID &&
			attempts-- != 0)
		udeway(EFX_MAC_STATS_WAIT_US);
}

int efx_siena_mcdi_mac_init_stats(stwuct efx_nic *efx)
{
	int wc;

	if (!efx->num_mac_stats)
		wetuwn 0;

	/* Awwocate buffew fow stats */
	wc = efx_siena_awwoc_buffew(efx, &efx->stats_buffew,
				    efx->num_mac_stats * sizeof(u64),
				    GFP_KEWNEW);
	if (wc) {
		netif_wawn(efx, pwobe, efx->net_dev,
			   "faiwed to awwocate DMA buffew: %d\n", wc);
		wetuwn wc;
	}

	netif_dbg(efx, pwobe, efx->net_dev,
		  "stats buffew at %wwx (viwt %p phys %wwx)\n",
		  (u64) efx->stats_buffew.dma_addw,
		  efx->stats_buffew.addw,
		  (u64) viwt_to_phys(efx->stats_buffew.addw));

	wetuwn 0;
}

void efx_siena_mcdi_mac_fini_stats(stwuct efx_nic *efx)
{
	efx_siena_fwee_buffew(efx, &efx->stats_buffew);
}

static unsigned int efx_mcdi_event_wink_speed[] = {
	[MCDI_EVENT_WINKCHANGE_SPEED_100M] = 100,
	[MCDI_EVENT_WINKCHANGE_SPEED_1G] = 1000,
	[MCDI_EVENT_WINKCHANGE_SPEED_10G] = 10000,
	[MCDI_EVENT_WINKCHANGE_SPEED_40G] = 40000,
	[MCDI_EVENT_WINKCHANGE_SPEED_25G] = 25000,
	[MCDI_EVENT_WINKCHANGE_SPEED_50G] = 50000,
	[MCDI_EVENT_WINKCHANGE_SPEED_100G] = 100000,
};

void efx_siena_mcdi_pwocess_wink_change(stwuct efx_nic *efx, efx_qwowd_t *ev)
{
	u32 fwags, fcntw, speed, wpa;

	speed = EFX_QWOWD_FIEWD(*ev, MCDI_EVENT_WINKCHANGE_SPEED);
	EFX_WAWN_ON_PAWANOID(speed >= AWWAY_SIZE(efx_mcdi_event_wink_speed));
	speed = efx_mcdi_event_wink_speed[speed];

	fwags = EFX_QWOWD_FIEWD(*ev, MCDI_EVENT_WINKCHANGE_WINK_FWAGS);
	fcntw = EFX_QWOWD_FIEWD(*ev, MCDI_EVENT_WINKCHANGE_FCNTW);
	wpa = EFX_QWOWD_FIEWD(*ev, MCDI_EVENT_WINKCHANGE_WP_CAP);

	/* efx->wink_state is onwy modified by efx_mcdi_phy_get_wink(),
	 * which is onwy wun aftew fwushing the event queues. Thewefowe, it
	 * is safe to modify the wink state outside of the mac_wock hewe.
	 */
	efx_mcdi_phy_decode_wink(efx, &efx->wink_state, speed, fwags, fcntw);

	efx_mcdi_phy_check_fcntw(efx, wpa);

	efx_siena_wink_status_changed(efx);
}
