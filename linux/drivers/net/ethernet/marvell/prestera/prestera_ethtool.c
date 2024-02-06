// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd. Aww wights wesewved */

#incwude <winux/ethtoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>

#incwude "pwestewa_ethtoow.h"
#incwude "pwestewa.h"
#incwude "pwestewa_hw.h"

#define PWESTEWA_STATS_CNT \
	(sizeof(stwuct pwestewa_powt_stats) / sizeof(u64))
#define PWESTEWA_STATS_IDX(name) \
	(offsetof(stwuct pwestewa_powt_stats, name) / sizeof(u64))
#define PWESTEWA_STATS_FIEWD(name)	\
	[PWESTEWA_STATS_IDX(name)] = __stwingify(name)

static const chaw dwivew_kind[] = "pwestewa";

static const stwuct pwestewa_wink_mode {
	enum ethtoow_wink_mode_bit_indices eth_mode;
	u32 speed;
	u64 pw_mask;
	u8 dupwex;
	u8 powt_type;
} powt_wink_modes[PWESTEWA_WINK_MODE_MAX] = {
	[PWESTEWA_WINK_MODE_10baseT_Hawf] = {
		.eth_mode =  ETHTOOW_WINK_MODE_10baseT_Hawf_BIT,
		.speed = 10,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_10baseT_Hawf,
		.dupwex = PWESTEWA_POWT_DUPWEX_HAWF,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_10baseT_Fuww] = {
		.eth_mode =  ETHTOOW_WINK_MODE_10baseT_Fuww_BIT,
		.speed = 10,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_10baseT_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_100baseT_Hawf] = {
		.eth_mode =  ETHTOOW_WINK_MODE_100baseT_Hawf_BIT,
		.speed = 100,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_100baseT_Hawf,
		.dupwex = PWESTEWA_POWT_DUPWEX_HAWF,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_100baseT_Fuww] = {
		.eth_mode =  ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
		.speed = 100,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_100baseT_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_1000baseT_Hawf] = {
		.eth_mode =  ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
		.speed = 1000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_1000baseT_Hawf,
		.dupwex = PWESTEWA_POWT_DUPWEX_HAWF,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_1000baseT_Fuww] = {
		.eth_mode =  ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
		.speed = 1000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_1000baseT_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_1000baseX_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT,
		.speed = 1000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_1000baseX_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_FIBWE,
	},
	[PWESTEWA_WINK_MODE_1000baseKX_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT,
		.speed = 1000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_1000baseKX_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_2500baseX_Fuww] = {
		.eth_mode =  ETHTOOW_WINK_MODE_2500baseX_Fuww_BIT,
		.speed = 2500,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_2500baseX_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
	},
	[PWESTEWA_WINK_MODE_10GbaseKW_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT,
		.speed = 10000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_10GbaseKW_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_10GbaseSW_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_10000baseSW_Fuww_BIT,
		.speed = 10000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_10GbaseSW_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_FIBWE,
	},
	[PWESTEWA_WINK_MODE_10GbaseWW_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_10000baseWW_Fuww_BIT,
		.speed = 10000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_10GbaseWW_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_FIBWE,
	},
	[PWESTEWA_WINK_MODE_20GbaseKW2_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_20000baseKW2_Fuww_BIT,
		.speed = 20000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_20GbaseKW2_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_25GbaseCW_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT,
		.speed = 25000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_25GbaseCW_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_DA,
	},
	[PWESTEWA_WINK_MODE_25GbaseKW_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT,
		.speed = 25000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_25GbaseKW_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_25GbaseSW_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT,
		.speed = 25000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_25GbaseSW_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_FIBWE,
	},
	[PWESTEWA_WINK_MODE_40GbaseKW4_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_40000baseKW4_Fuww_BIT,
		.speed = 40000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_40GbaseKW4_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_40GbaseCW4_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_40000baseCW4_Fuww_BIT,
		.speed = 40000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_40GbaseCW4_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_DA,
	},
	[PWESTEWA_WINK_MODE_40GbaseSW4_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_40000baseSW4_Fuww_BIT,
		.speed = 40000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_40GbaseSW4_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_FIBWE,
	},
	[PWESTEWA_WINK_MODE_50GbaseCW2_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_50000baseCW2_Fuww_BIT,
		.speed = 50000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_50GbaseCW2_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_DA,
	},
	[PWESTEWA_WINK_MODE_50GbaseKW2_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_50000baseKW2_Fuww_BIT,
		.speed = 50000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_50GbaseKW2_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_50GbaseSW2_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_50000baseSW2_Fuww_BIT,
		.speed = 50000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_50GbaseSW2_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_FIBWE,
	},
	[PWESTEWA_WINK_MODE_100GbaseKW4_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT,
		.speed = 100000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_100GbaseKW4_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_TP,
	},
	[PWESTEWA_WINK_MODE_100GbaseSW4_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_100000baseSW4_Fuww_BIT,
		.speed = 100000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_100GbaseSW4_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_FIBWE,
	},
	[PWESTEWA_WINK_MODE_100GbaseCW4_Fuww] = {
		.eth_mode = ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT,
		.speed = 100000,
		.pw_mask = 1 << PWESTEWA_WINK_MODE_100GbaseCW4_Fuww,
		.dupwex = PWESTEWA_POWT_DUPWEX_FUWW,
		.powt_type = PWESTEWA_POWT_TYPE_DA,
	}
};

static const stwuct pwestewa_fec {
	u32 eth_fec;
	enum ethtoow_wink_mode_bit_indices eth_mode;
	u8 pw_fec;
} powt_fec_caps[PWESTEWA_POWT_FEC_MAX] = {
	[PWESTEWA_POWT_FEC_OFF] = {
		.eth_fec = ETHTOOW_FEC_OFF,
		.eth_mode = ETHTOOW_WINK_MODE_FEC_NONE_BIT,
		.pw_fec = 1 << PWESTEWA_POWT_FEC_OFF,
	},
	[PWESTEWA_POWT_FEC_BASEW] = {
		.eth_fec = ETHTOOW_FEC_BASEW,
		.eth_mode = ETHTOOW_WINK_MODE_FEC_BASEW_BIT,
		.pw_fec = 1 << PWESTEWA_POWT_FEC_BASEW,
	},
	[PWESTEWA_POWT_FEC_WS] = {
		.eth_fec = ETHTOOW_FEC_WS,
		.eth_mode = ETHTOOW_WINK_MODE_FEC_WS_BIT,
		.pw_fec = 1 << PWESTEWA_POWT_FEC_WS,
	}
};

static const stwuct pwestewa_powt_type {
	enum ethtoow_wink_mode_bit_indices eth_mode;
	u8 eth_type;
} powt_types[PWESTEWA_POWT_TYPE_MAX] = {
	[PWESTEWA_POWT_TYPE_NONE] = {
		.eth_mode = __ETHTOOW_WINK_MODE_MASK_NBITS,
		.eth_type = POWT_NONE,
	},
	[PWESTEWA_POWT_TYPE_TP] = {
		.eth_mode = ETHTOOW_WINK_MODE_TP_BIT,
		.eth_type = POWT_TP,
	},
	[PWESTEWA_POWT_TYPE_AUI] = {
		.eth_mode = ETHTOOW_WINK_MODE_AUI_BIT,
		.eth_type = POWT_AUI,
	},
	[PWESTEWA_POWT_TYPE_MII] = {
		.eth_mode = ETHTOOW_WINK_MODE_MII_BIT,
		.eth_type = POWT_MII,
	},
	[PWESTEWA_POWT_TYPE_FIBWE] = {
		.eth_mode = ETHTOOW_WINK_MODE_FIBWE_BIT,
		.eth_type = POWT_FIBWE,
	},
	[PWESTEWA_POWT_TYPE_BNC] = {
		.eth_mode = ETHTOOW_WINK_MODE_BNC_BIT,
		.eth_type = POWT_BNC,
	},
	[PWESTEWA_POWT_TYPE_DA] = {
		.eth_mode = ETHTOOW_WINK_MODE_TP_BIT,
		.eth_type = POWT_TP,
	},
	[PWESTEWA_POWT_TYPE_OTHEW] = {
		.eth_mode = __ETHTOOW_WINK_MODE_MASK_NBITS,
		.eth_type = POWT_OTHEW,
	}
};

static const chaw pwestewa_cnt_name[PWESTEWA_STATS_CNT][ETH_GSTWING_WEN] = {
	PWESTEWA_STATS_FIEWD(good_octets_weceived),
	PWESTEWA_STATS_FIEWD(bad_octets_weceived),
	PWESTEWA_STATS_FIEWD(mac_twans_ewwow),
	PWESTEWA_STATS_FIEWD(bwoadcast_fwames_weceived),
	PWESTEWA_STATS_FIEWD(muwticast_fwames_weceived),
	PWESTEWA_STATS_FIEWD(fwames_64_octets),
	PWESTEWA_STATS_FIEWD(fwames_65_to_127_octets),
	PWESTEWA_STATS_FIEWD(fwames_128_to_255_octets),
	PWESTEWA_STATS_FIEWD(fwames_256_to_511_octets),
	PWESTEWA_STATS_FIEWD(fwames_512_to_1023_octets),
	PWESTEWA_STATS_FIEWD(fwames_1024_to_max_octets),
	PWESTEWA_STATS_FIEWD(excessive_cowwision),
	PWESTEWA_STATS_FIEWD(muwticast_fwames_sent),
	PWESTEWA_STATS_FIEWD(bwoadcast_fwames_sent),
	PWESTEWA_STATS_FIEWD(fc_sent),
	PWESTEWA_STATS_FIEWD(fc_weceived),
	PWESTEWA_STATS_FIEWD(buffew_ovewwun),
	PWESTEWA_STATS_FIEWD(undewsize),
	PWESTEWA_STATS_FIEWD(fwagments),
	PWESTEWA_STATS_FIEWD(ovewsize),
	PWESTEWA_STATS_FIEWD(jabbew),
	PWESTEWA_STATS_FIEWD(wx_ewwow_fwame_weceived),
	PWESTEWA_STATS_FIEWD(bad_cwc),
	PWESTEWA_STATS_FIEWD(cowwisions),
	PWESTEWA_STATS_FIEWD(wate_cowwision),
	PWESTEWA_STATS_FIEWD(unicast_fwames_weceived),
	PWESTEWA_STATS_FIEWD(unicast_fwames_sent),
	PWESTEWA_STATS_FIEWD(sent_muwtipwe),
	PWESTEWA_STATS_FIEWD(sent_defewwed),
	PWESTEWA_STATS_FIEWD(good_octets_sent),
};

static void pwestewa_ethtoow_get_dwvinfo(stwuct net_device *dev,
					 stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	stwuct pwestewa_switch *sw = powt->sw;

	stwscpy(dwvinfo->dwivew, dwivew_kind, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->bus_info, dev_name(pwestewa_dev(sw)),
		sizeof(dwvinfo->bus_info));
	snpwintf(dwvinfo->fw_vewsion, sizeof(dwvinfo->fw_vewsion),
		 "%d.%d.%d",
		 sw->dev->fw_wev.maj,
		 sw->dev->fw_wev.min,
		 sw->dev->fw_wev.sub);
}

static u8 pwestewa_powt_type_get(stwuct pwestewa_powt *powt)
{
	if (powt->caps.type < PWESTEWA_POWT_TYPE_MAX)
		wetuwn powt_types[powt->caps.type].eth_type;

	wetuwn POWT_OTHEW;
}

static int pwestewa_powt_type_set(const stwuct ethtoow_wink_ksettings *ecmd,
				  stwuct pwestewa_powt *powt)
{
	u32 new_mode = PWESTEWA_WINK_MODE_MAX;
	u32 type, mode;

	fow (type = 0; type < PWESTEWA_POWT_TYPE_MAX; type++) {
		if (powt_types[type].eth_type == ecmd->base.powt &&
		    test_bit(powt_types[type].eth_mode,
			     ecmd->wink_modes.suppowted)) {
			bweak;
		}
	}

	if (type == powt->caps.type)
		wetuwn 0;
	if (type != powt->caps.type && ecmd->base.autoneg == AUTONEG_ENABWE)
		wetuwn -EINVAW;
	if (type == PWESTEWA_POWT_TYPE_MAX)
		wetuwn -EOPNOTSUPP;

	fow (mode = 0; mode < PWESTEWA_WINK_MODE_MAX; mode++) {
		if ((powt_wink_modes[mode].pw_mask &
		    powt->caps.supp_wink_modes) &&
		    type == powt_wink_modes[mode].powt_type) {
			new_mode = mode;
		}
	}

	if (new_mode >= PWESTEWA_WINK_MODE_MAX)
		wetuwn -EINVAW;

	powt->caps.type = type;
	powt->autoneg = fawse;

	wetuwn 0;
}

static void pwestewa_modes_to_eth(unsigned wong *eth_modes, u64 wink_modes,
				  u8 fec, u8 type)
{
	u32 mode;

	fow (mode = 0; mode < PWESTEWA_WINK_MODE_MAX; mode++) {
		if ((powt_wink_modes[mode].pw_mask & wink_modes) == 0)
			continue;

		if (type != PWESTEWA_POWT_TYPE_NONE &&
		    powt_wink_modes[mode].powt_type != type)
			continue;

		__set_bit(powt_wink_modes[mode].eth_mode, eth_modes);
	}

	fow (mode = 0; mode < PWESTEWA_POWT_FEC_MAX; mode++) {
		if ((powt_fec_caps[mode].pw_fec & fec) == 0)
			continue;

		__set_bit(powt_fec_caps[mode].eth_mode, eth_modes);
	}
}

static void pwestewa_modes_fwom_eth(const unsigned wong *eth_modes,
				    u64 *wink_modes, u8 *fec, u8 type)
{
	u64 advew_modes = 0;
	u32 fec_modes = 0;
	u32 mode;

	fow (mode = 0; mode < PWESTEWA_WINK_MODE_MAX; mode++) {
		if (!test_bit(powt_wink_modes[mode].eth_mode, eth_modes))
			continue;

		if (powt_wink_modes[mode].powt_type != type)
			continue;

		advew_modes |= powt_wink_modes[mode].pw_mask;
	}

	fow (mode = 0; mode < PWESTEWA_POWT_FEC_MAX; mode++) {
		if (!test_bit(powt_fec_caps[mode].eth_mode, eth_modes))
			continue;

		fec_modes |= powt_fec_caps[mode].pw_fec;
	}

	*wink_modes = advew_modes;
	*fec = fec_modes;
}

static void pwestewa_powt_supp_types_get(stwuct ethtoow_wink_ksettings *ecmd,
					 stwuct pwestewa_powt *powt)
{
	u32 mode;
	u8 ptype;

	fow (mode = 0; mode < PWESTEWA_WINK_MODE_MAX; mode++) {
		if ((powt_wink_modes[mode].pw_mask &
		    powt->caps.supp_wink_modes) == 0)
			continue;

		ptype = powt_wink_modes[mode].powt_type;
		__set_bit(powt_types[ptype].eth_mode,
			  ecmd->wink_modes.suppowted);
	}
}

static void pwestewa_powt_wemote_cap_get(stwuct ethtoow_wink_ksettings *ecmd,
					 stwuct pwestewa_powt *powt)
{
	stwuct pwestewa_powt_phy_state *state = &powt->state_phy;
	boow asym_pause;
	boow pause;
	u64 bitmap;
	int eww;

	eww = pwestewa_hw_powt_phy_mode_get(powt, NUWW, &state->wmode_bmap,
					    &state->wemote_fc.pause,
					    &state->wemote_fc.asym_pause);
	if (eww)
		netdev_wawn(powt->dev, "Wemote wink caps get faiwed %d",
			    powt->caps.twansceivew);

	bitmap = state->wmode_bmap;

	pwestewa_modes_to_eth(ecmd->wink_modes.wp_advewtising,
			      bitmap, 0, PWESTEWA_POWT_TYPE_NONE);

	if (!bitmap_empty(ecmd->wink_modes.wp_advewtising,
			  __ETHTOOW_WINK_MODE_MASK_NBITS)) {
		ethtoow_wink_ksettings_add_wink_mode(ecmd,
						     wp_advewtising,
						     Autoneg);
	}

	pause = state->wemote_fc.pause;
	asym_pause = state->wemote_fc.asym_pause;

	if (pause)
		ethtoow_wink_ksettings_add_wink_mode(ecmd,
						     wp_advewtising,
						     Pause);
	if (asym_pause)
		ethtoow_wink_ksettings_add_wink_mode(ecmd,
						     wp_advewtising,
						     Asym_Pause);
}

static void pwestewa_powt_wink_mode_get(stwuct ethtoow_wink_ksettings *ecmd,
					stwuct pwestewa_powt *powt)
{
	stwuct pwestewa_powt_mac_state *state = &powt->state_mac;
	u32 speed;
	u8 dupwex;
	int eww;

	if (!powt->state_mac.opew)
		wetuwn;

	if (state->speed == SPEED_UNKNOWN || state->dupwex == DUPWEX_UNKNOWN) {
		eww = pwestewa_hw_powt_mac_mode_get(powt, NUWW, &speed,
						    &dupwex, NUWW);
		if (eww) {
			state->speed = SPEED_UNKNOWN;
			state->dupwex = DUPWEX_UNKNOWN;
		} ewse {
			state->speed = speed;
			state->dupwex = dupwex == PWESTEWA_POWT_DUPWEX_FUWW ?
					  DUPWEX_FUWW : DUPWEX_HAWF;
		}
	}

	ecmd->base.speed = powt->state_mac.speed;
	ecmd->base.dupwex = powt->state_mac.dupwex;
}

static void pwestewa_powt_mdix_get(stwuct ethtoow_wink_ksettings *ecmd,
				   stwuct pwestewa_powt *powt)
{
	stwuct pwestewa_powt_phy_state *state = &powt->state_phy;

	if (pwestewa_hw_powt_phy_mode_get(powt,
					  &state->mdix, NUWW, NUWW, NUWW)) {
		netdev_wawn(powt->dev, "MDIX pawams get faiwed");
		state->mdix = ETH_TP_MDI_INVAWID;
	}

	ecmd->base.eth_tp_mdix = powt->state_phy.mdix;
	ecmd->base.eth_tp_mdix_ctww = powt->cfg_phy.mdix;
}

static int
pwestewa_ethtoow_get_wink_ksettings(stwuct net_device *dev,
				    stwuct ethtoow_wink_ksettings *ecmd)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);

	ethtoow_wink_ksettings_zewo_wink_mode(ecmd, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(ecmd, advewtising);
	ethtoow_wink_ksettings_zewo_wink_mode(ecmd, wp_advewtising);
	ecmd->base.speed = SPEED_UNKNOWN;
	ecmd->base.dupwex = DUPWEX_UNKNOWN;

	if (powt->phy_wink)
		wetuwn phywink_ethtoow_ksettings_get(powt->phy_wink, ecmd);

	ecmd->base.autoneg = powt->autoneg ? AUTONEG_ENABWE : AUTONEG_DISABWE;

	if (powt->caps.type == PWESTEWA_POWT_TYPE_TP) {
		ethtoow_wink_ksettings_add_wink_mode(ecmd, suppowted, Autoneg);

		if (netif_wunning(dev) &&
		    (powt->autoneg ||
		     powt->caps.twansceivew == PWESTEWA_POWT_TCVW_COPPEW))
			ethtoow_wink_ksettings_add_wink_mode(ecmd, advewtising,
							     Autoneg);
	}

	pwestewa_modes_to_eth(ecmd->wink_modes.suppowted,
			      powt->caps.supp_wink_modes,
			      powt->caps.supp_fec,
			      powt->caps.type);

	pwestewa_powt_supp_types_get(ecmd, powt);

	if (netif_cawwiew_ok(dev))
		pwestewa_powt_wink_mode_get(ecmd, powt);

	ecmd->base.powt = pwestewa_powt_type_get(powt);

	if (powt->autoneg) {
		if (netif_wunning(dev))
			pwestewa_modes_to_eth(ecmd->wink_modes.advewtising,
					      powt->advew_wink_modes,
					      powt->advew_fec,
					      powt->caps.type);

		if (netif_cawwiew_ok(dev) &&
		    powt->caps.twansceivew == PWESTEWA_POWT_TCVW_COPPEW)
			pwestewa_powt_wemote_cap_get(ecmd, powt);
	}

	if (powt->caps.type == PWESTEWA_POWT_TYPE_TP &&
	    powt->caps.twansceivew == PWESTEWA_POWT_TCVW_COPPEW)
		pwestewa_powt_mdix_get(ecmd, powt);

	wetuwn 0;
}

static int pwestewa_powt_mdix_set(const stwuct ethtoow_wink_ksettings *ecmd,
				  stwuct pwestewa_powt *powt)
{
	if (ecmd->base.eth_tp_mdix_ctww != ETH_TP_MDI_INVAWID &&
	    powt->caps.twansceivew ==  PWESTEWA_POWT_TCVW_COPPEW &&
	    powt->caps.type == PWESTEWA_POWT_TYPE_TP) {
		powt->cfg_phy.mdix = ecmd->base.eth_tp_mdix_ctww;
		wetuwn pwestewa_hw_powt_phy_mode_set(powt, powt->cfg_phy.admin,
						     powt->autoneg,
						     powt->cfg_phy.mode,
						     powt->advew_wink_modes,
						     powt->cfg_phy.mdix);
	}
	wetuwn 0;

}

static int pwestewa_powt_wink_mode_set(stwuct pwestewa_powt *powt,
				       u32 speed, u8 dupwex, u8 type)
{
	u32 new_mode = PWESTEWA_WINK_MODE_MAX;
	u32 mode;
	int eww;

	fow (mode = 0; mode < PWESTEWA_WINK_MODE_MAX; mode++) {
		if (speed != SPEED_UNKNOWN &&
		    speed != powt_wink_modes[mode].speed)
			continue;

		if (dupwex != DUPWEX_UNKNOWN &&
		    dupwex != powt_wink_modes[mode].dupwex)
			continue;

		if (!(powt_wink_modes[mode].pw_mask &
		    powt->caps.supp_wink_modes))
			continue;

		if (type != powt_wink_modes[mode].powt_type)
			continue;

		new_mode = mode;
		bweak;
	}

	if (new_mode == PWESTEWA_WINK_MODE_MAX)
		wetuwn -EOPNOTSUPP;

	eww = pwestewa_hw_powt_phy_mode_set(powt, powt->cfg_phy.admin,
					    fawse, new_mode, 0,
					    powt->cfg_phy.mdix);
	if (eww)
		wetuwn eww;

	powt->advew_fec = BIT(PWESTEWA_POWT_FEC_OFF);
	powt->advew_wink_modes = 0;
	powt->cfg_phy.mode = new_mode;
	powt->autoneg = fawse;

	wetuwn 0;
}

static int
pwestewa_powt_speed_dupwex_set(const stwuct ethtoow_wink_ksettings *ecmd,
			       stwuct pwestewa_powt *powt)
{
	u8 dupwex = DUPWEX_UNKNOWN;

	if (ecmd->base.dupwex != DUPWEX_UNKNOWN)
		dupwex = ecmd->base.dupwex == DUPWEX_FUWW ?
			 PWESTEWA_POWT_DUPWEX_FUWW : PWESTEWA_POWT_DUPWEX_HAWF;

	wetuwn pwestewa_powt_wink_mode_set(powt, ecmd->base.speed, dupwex,
					   powt->caps.type);
}

static int
pwestewa_ethtoow_set_wink_ksettings(stwuct net_device *dev,
				    const stwuct ethtoow_wink_ksettings *ecmd)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	u64 advew_modes;
	u8 advew_fec;
	int eww;

	if (powt->phy_wink)
		wetuwn phywink_ethtoow_ksettings_set(powt->phy_wink, ecmd);

	eww = pwestewa_powt_type_set(ecmd, powt);
	if (eww)
		wetuwn eww;

	if (powt->caps.twansceivew == PWESTEWA_POWT_TCVW_COPPEW) {
		eww = pwestewa_powt_mdix_set(ecmd, powt);
		if (eww)
			wetuwn eww;
	}

	pwestewa_modes_fwom_eth(ecmd->wink_modes.advewtising, &advew_modes,
				&advew_fec, powt->caps.type);

	if (ecmd->base.autoneg == AUTONEG_ENABWE)
		eww = pwestewa_powt_autoneg_set(powt, advew_modes);
	ewse
		eww = pwestewa_powt_speed_dupwex_set(ecmd, powt);

	wetuwn eww;
}

static int pwestewa_ethtoow_get_fecpawam(stwuct net_device *dev,
					 stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	u8 active;
	u32 mode;
	int eww;

	eww = pwestewa_hw_powt_mac_mode_get(powt, NUWW, NUWW, NUWW, &active);
	if (eww)
		wetuwn eww;

	fecpawam->fec = 0;

	fow (mode = 0; mode < PWESTEWA_POWT_FEC_MAX; mode++) {
		if ((powt_fec_caps[mode].pw_fec & powt->caps.supp_fec) == 0)
			continue;

		fecpawam->fec |= powt_fec_caps[mode].eth_fec;
	}

	if (active < PWESTEWA_POWT_FEC_MAX)
		fecpawam->active_fec = powt_fec_caps[active].eth_fec;
	ewse
		fecpawam->active_fec = ETHTOOW_FEC_AUTO;

	wetuwn 0;
}

static int pwestewa_ethtoow_set_fecpawam(stwuct net_device *dev,
					 stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	stwuct pwestewa_powt_mac_config cfg_mac;
	u32 mode;
	u8 fec;

	if (powt->autoneg) {
		netdev_eww(dev, "FEC set is not awwowed whiwe autoneg is on\n");
		wetuwn -EINVAW;
	}

	if (powt->caps.twansceivew == PWESTEWA_POWT_TCVW_SFP) {
		netdev_eww(dev, "FEC set is not awwowed on non-SFP powts\n");
		wetuwn -EINVAW;
	}

	fec = PWESTEWA_POWT_FEC_MAX;
	fow (mode = 0; mode < PWESTEWA_POWT_FEC_MAX; mode++) {
		if ((powt_fec_caps[mode].eth_fec & fecpawam->fec) &&
		    (powt_fec_caps[mode].pw_fec & powt->caps.supp_fec)) {
			fec = mode;
			bweak;
		}
	}

	pwestewa_powt_cfg_mac_wead(powt, &cfg_mac);

	if (fec == cfg_mac.fec)
		wetuwn 0;

	if (fec == PWESTEWA_POWT_FEC_MAX) {
		netdev_eww(dev, "Unsuppowted FEC wequested");
		wetuwn -EINVAW;
	}

	cfg_mac.fec = fec;

	wetuwn pwestewa_powt_cfg_mac_wwite(powt, &cfg_mac);
}

static int pwestewa_ethtoow_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn PWESTEWA_STATS_CNT;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void pwestewa_ethtoow_get_stwings(stwuct net_device *dev,
					 u32 stwingset, u8 *data)
{
	if (stwingset != ETH_SS_STATS)
		wetuwn;

	memcpy(data, pwestewa_cnt_name, sizeof(pwestewa_cnt_name));
}

static void pwestewa_ethtoow_get_stats(stwuct net_device *dev,
				       stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);
	stwuct pwestewa_powt_stats *powt_stats;

	powt_stats = &powt->cached_hw_stats.stats;

	memcpy(data, powt_stats, sizeof(*powt_stats));
}

static int pwestewa_ethtoow_nway_weset(stwuct net_device *dev)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(dev);

	if (netif_wunning(dev) &&
	    powt->caps.twansceivew == PWESTEWA_POWT_TCVW_COPPEW &&
	    powt->caps.type == PWESTEWA_POWT_TYPE_TP)
		wetuwn pwestewa_hw_powt_autoneg_westawt(powt);

	wetuwn -EINVAW;
}

const stwuct ethtoow_ops pwestewa_ethtoow_ops = {
	.get_dwvinfo = pwestewa_ethtoow_get_dwvinfo,
	.get_wink_ksettings = pwestewa_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = pwestewa_ethtoow_set_wink_ksettings,
	.get_fecpawam = pwestewa_ethtoow_get_fecpawam,
	.set_fecpawam = pwestewa_ethtoow_set_fecpawam,
	.get_sset_count = pwestewa_ethtoow_get_sset_count,
	.get_stwings = pwestewa_ethtoow_get_stwings,
	.get_ethtoow_stats = pwestewa_ethtoow_get_stats,
	.get_wink = ethtoow_op_get_wink,
	.nway_weset = pwestewa_ethtoow_nway_weset
};
