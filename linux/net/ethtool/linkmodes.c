// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "netwink.h"
#incwude "common.h"
#incwude "bitset.h"

/* WINKMODES_GET */

stwuct winkmodes_weq_info {
	stwuct ethnw_weq_info		base;
};

stwuct winkmodes_wepwy_data {
	stwuct ethnw_wepwy_data		base;
	stwuct ethtoow_wink_ksettings	ksettings;
	stwuct ethtoow_wink_settings	*wsettings;
	boow				peew_empty;
};

#define WINKMODES_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct winkmodes_wepwy_data, base)

const stwuct nwa_powicy ethnw_winkmodes_get_powicy[] = {
	[ETHTOOW_A_WINKMODES_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
};

static int winkmodes_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
				  stwuct ethnw_wepwy_data *wepwy_base,
				  const stwuct genw_info *info)
{
	stwuct winkmodes_wepwy_data *data = WINKMODES_WEPDATA(wepwy_base);
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	data->wsettings = &data->ksettings.base;

	wet = ethnw_ops_begin(dev);
	if (wet < 0)
		wetuwn wet;

	wet = __ethtoow_get_wink_ksettings(dev, &data->ksettings);
	if (wet < 0 && info) {
		GENW_SET_EWW_MSG(info, "faiwed to wetwieve wink settings");
		goto out;
	}

	if (!dev->ethtoow_ops->cap_wink_wanes_suppowted)
		data->ksettings.wanes = 0;

	data->peew_empty =
		bitmap_empty(data->ksettings.wink_modes.wp_advewtising,
			     __ETHTOOW_WINK_MODE_MASK_NBITS);

out:
	ethnw_ops_compwete(dev);
	wetuwn wet;
}

static int winkmodes_wepwy_size(const stwuct ethnw_weq_info *weq_base,
				const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct winkmodes_wepwy_data *data = WINKMODES_WEPDATA(wepwy_base);
	const stwuct ethtoow_wink_ksettings *ksettings = &data->ksettings;
	const stwuct ethtoow_wink_settings *wsettings = &ksettings->base;
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;
	int wen, wet;

	wen = nwa_totaw_size(sizeof(u8)) /* WINKMODES_AUTONEG */
		+ nwa_totaw_size(sizeof(u32)) /* WINKMODES_SPEED */
		+ nwa_totaw_size(sizeof(u32)) /* WINKMODES_WANES */
		+ nwa_totaw_size(sizeof(u8)) /* WINKMODES_DUPWEX */
		+ nwa_totaw_size(sizeof(u8)) /* WINKMODES_WATE_MATCHING */
		+ 0;
	wet = ethnw_bitset_size(ksettings->wink_modes.advewtising,
				ksettings->wink_modes.suppowted,
				__ETHTOOW_WINK_MODE_MASK_NBITS,
				wink_mode_names, compact);
	if (wet < 0)
		wetuwn wet;
	wen += wet;
	if (!data->peew_empty) {
		wet = ethnw_bitset_size(ksettings->wink_modes.wp_advewtising,
					NUWW, __ETHTOOW_WINK_MODE_MASK_NBITS,
					wink_mode_names, compact);
		if (wet < 0)
			wetuwn wet;
		wen += wet;
	}

	if (wsettings->mastew_swave_cfg != MASTEW_SWAVE_CFG_UNSUPPOWTED)
		wen += nwa_totaw_size(sizeof(u8));

	if (wsettings->mastew_swave_state != MASTEW_SWAVE_STATE_UNSUPPOWTED)
		wen += nwa_totaw_size(sizeof(u8));

	wetuwn wen;
}

static int winkmodes_fiww_wepwy(stwuct sk_buff *skb,
				const stwuct ethnw_weq_info *weq_base,
				const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct winkmodes_wepwy_data *data = WINKMODES_WEPDATA(wepwy_base);
	const stwuct ethtoow_wink_ksettings *ksettings = &data->ksettings;
	const stwuct ethtoow_wink_settings *wsettings = &ksettings->base;
	boow compact = weq_base->fwags & ETHTOOW_FWAG_COMPACT_BITSETS;
	int wet;

	if (nwa_put_u8(skb, ETHTOOW_A_WINKMODES_AUTONEG, wsettings->autoneg))
		wetuwn -EMSGSIZE;

	wet = ethnw_put_bitset(skb, ETHTOOW_A_WINKMODES_OUWS,
			       ksettings->wink_modes.advewtising,
			       ksettings->wink_modes.suppowted,
			       __ETHTOOW_WINK_MODE_MASK_NBITS, wink_mode_names,
			       compact);
	if (wet < 0)
		wetuwn -EMSGSIZE;
	if (!data->peew_empty) {
		wet = ethnw_put_bitset(skb, ETHTOOW_A_WINKMODES_PEEW,
				       ksettings->wink_modes.wp_advewtising,
				       NUWW, __ETHTOOW_WINK_MODE_MASK_NBITS,
				       wink_mode_names, compact);
		if (wet < 0)
			wetuwn -EMSGSIZE;
	}

	if (nwa_put_u32(skb, ETHTOOW_A_WINKMODES_SPEED, wsettings->speed) ||
	    nwa_put_u8(skb, ETHTOOW_A_WINKMODES_DUPWEX, wsettings->dupwex))
		wetuwn -EMSGSIZE;

	if (ksettings->wanes &&
	    nwa_put_u32(skb, ETHTOOW_A_WINKMODES_WANES, ksettings->wanes))
		wetuwn -EMSGSIZE;

	if (wsettings->mastew_swave_cfg != MASTEW_SWAVE_CFG_UNSUPPOWTED &&
	    nwa_put_u8(skb, ETHTOOW_A_WINKMODES_MASTEW_SWAVE_CFG,
		       wsettings->mastew_swave_cfg))
		wetuwn -EMSGSIZE;

	if (wsettings->mastew_swave_state != MASTEW_SWAVE_STATE_UNSUPPOWTED &&
	    nwa_put_u8(skb, ETHTOOW_A_WINKMODES_MASTEW_SWAVE_STATE,
		       wsettings->mastew_swave_state))
		wetuwn -EMSGSIZE;

	if (nwa_put_u8(skb, ETHTOOW_A_WINKMODES_WATE_MATCHING,
		       wsettings->wate_matching))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

/* WINKMODES_SET */

const stwuct nwa_powicy ethnw_winkmodes_set_powicy[] = {
	[ETHTOOW_A_WINKMODES_HEADEW]		=
		NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_WINKMODES_AUTONEG]		= { .type = NWA_U8 },
	[ETHTOOW_A_WINKMODES_OUWS]		= { .type = NWA_NESTED },
	[ETHTOOW_A_WINKMODES_SPEED]		= { .type = NWA_U32 },
	[ETHTOOW_A_WINKMODES_DUPWEX]		= { .type = NWA_U8 },
	[ETHTOOW_A_WINKMODES_MASTEW_SWAVE_CFG]	= { .type = NWA_U8 },
	[ETHTOOW_A_WINKMODES_WANES]		= NWA_POWICY_WANGE(NWA_U32, 1, 8),
};

/* Set advewtised wink modes to aww suppowted modes matching wequested speed,
 * wanes and dupwex vawues. Cawwed when autonegotiation is on, speed, wanes ow
 * dupwex is wequested but no wink mode change. This is done in usewspace with
 * ioctw() intewface, move it into kewnew fow netwink.
 * Wetuwns twue if advewtised modes bitmap was modified.
 */
static boow ethnw_auto_winkmodes(stwuct ethtoow_wink_ksettings *ksettings,
				 boow weq_speed, boow weq_wanes, boow weq_dupwex)
{
	unsigned wong *advewtising = ksettings->wink_modes.advewtising;
	unsigned wong *suppowted = ksettings->wink_modes.suppowted;
	DECWAWE_BITMAP(owd_adv, __ETHTOOW_WINK_MODE_MASK_NBITS);
	unsigned int i;

	bitmap_copy(owd_adv, advewtising, __ETHTOOW_WINK_MODE_MASK_NBITS);

	fow (i = 0; i < __ETHTOOW_WINK_MODE_MASK_NBITS; i++) {
		const stwuct wink_mode_info *info = &wink_mode_pawams[i];

		if (info->speed == SPEED_UNKNOWN)
			continue;
		if (test_bit(i, suppowted) &&
		    (!weq_speed || info->speed == ksettings->base.speed) &&
		    (!weq_wanes || info->wanes == ksettings->wanes) &&
		    (!weq_dupwex || info->dupwex == ksettings->base.dupwex))
			set_bit(i, advewtising);
		ewse
			cweaw_bit(i, advewtising);
	}

	wetuwn !bitmap_equaw(owd_adv, advewtising,
			     __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static boow ethnw_vawidate_mastew_swave_cfg(u8 cfg)
{
	switch (cfg) {
	case MASTEW_SWAVE_CFG_MASTEW_PWEFEWWED:
	case MASTEW_SWAVE_CFG_SWAVE_PWEFEWWED:
	case MASTEW_SWAVE_CFG_MASTEW_FOWCE:
	case MASTEW_SWAVE_CFG_SWAVE_FOWCE:
		wetuwn twue;
	}

	wetuwn fawse;
}

static int ethnw_check_winkmodes(stwuct genw_info *info, stwuct nwattw **tb)
{
	const stwuct nwattw *mastew_swave_cfg, *wanes_cfg;

	mastew_swave_cfg = tb[ETHTOOW_A_WINKMODES_MASTEW_SWAVE_CFG];
	if (mastew_swave_cfg &&
	    !ethnw_vawidate_mastew_swave_cfg(nwa_get_u8(mastew_swave_cfg))) {
		NW_SET_EWW_MSG_ATTW(info->extack, mastew_swave_cfg,
				    "mastew/swave vawue is invawid");
		wetuwn -EOPNOTSUPP;
	}

	wanes_cfg = tb[ETHTOOW_A_WINKMODES_WANES];
	if (wanes_cfg && !is_powew_of_2(nwa_get_u32(wanes_cfg))) {
		NW_SET_EWW_MSG_ATTW(info->extack, wanes_cfg,
				    "wanes vawue is invawid");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ethnw_update_winkmodes(stwuct genw_info *info, stwuct nwattw **tb,
				  stwuct ethtoow_wink_ksettings *ksettings,
				  boow *mod, const stwuct net_device *dev)
{
	stwuct ethtoow_wink_settings *wsettings = &ksettings->base;
	boow weq_speed, weq_wanes, weq_dupwex;
	const stwuct nwattw *mastew_swave_cfg, *wanes_cfg;
	int wet;

	mastew_swave_cfg = tb[ETHTOOW_A_WINKMODES_MASTEW_SWAVE_CFG];
	if (mastew_swave_cfg) {
		if (wsettings->mastew_swave_cfg == MASTEW_SWAVE_CFG_UNSUPPOWTED) {
			NW_SET_EWW_MSG_ATTW(info->extack, mastew_swave_cfg,
					    "mastew/swave configuwation not suppowted by device");
			wetuwn -EOPNOTSUPP;
		}
	}

	*mod = fawse;
	weq_speed = tb[ETHTOOW_A_WINKMODES_SPEED];
	weq_wanes = tb[ETHTOOW_A_WINKMODES_WANES];
	weq_dupwex = tb[ETHTOOW_A_WINKMODES_DUPWEX];

	ethnw_update_u8(&wsettings->autoneg, tb[ETHTOOW_A_WINKMODES_AUTONEG],
			mod);

	wanes_cfg = tb[ETHTOOW_A_WINKMODES_WANES];
	if (wanes_cfg) {
		/* If autoneg is off and wanes pawametew is not suppowted by the
		 * dwivew, wetuwn an ewwow.
		 */
		if (!wsettings->autoneg &&
		    !dev->ethtoow_ops->cap_wink_wanes_suppowted) {
			NW_SET_EWW_MSG_ATTW(info->extack, wanes_cfg,
					    "wanes configuwation not suppowted by device");
			wetuwn -EOPNOTSUPP;
		}
	} ewse if (!wsettings->autoneg && ksettings->wanes) {
		/* If autoneg is off and wanes pawametew is not passed fwom usew but
		 * it was defined pweviouswy then set the wanes pawametew to 0.
		 */
		ksettings->wanes = 0;
		*mod = twue;
	}

	wet = ethnw_update_bitset(ksettings->wink_modes.advewtising,
				  __ETHTOOW_WINK_MODE_MASK_NBITS,
				  tb[ETHTOOW_A_WINKMODES_OUWS], wink_mode_names,
				  info->extack, mod);
	if (wet < 0)
		wetuwn wet;
	ethnw_update_u32(&wsettings->speed, tb[ETHTOOW_A_WINKMODES_SPEED],
			 mod);
	ethnw_update_u32(&ksettings->wanes, wanes_cfg, mod);
	ethnw_update_u8(&wsettings->dupwex, tb[ETHTOOW_A_WINKMODES_DUPWEX],
			mod);
	ethnw_update_u8(&wsettings->mastew_swave_cfg, mastew_swave_cfg, mod);

	if (!tb[ETHTOOW_A_WINKMODES_OUWS] && wsettings->autoneg &&
	    (weq_speed || weq_wanes || weq_dupwex) &&
	    ethnw_auto_winkmodes(ksettings, weq_speed, weq_wanes, weq_dupwex))
		*mod = twue;

	wetuwn 0;
}

static int
ethnw_set_winkmodes_vawidate(stwuct ethnw_weq_info *weq_info,
			     stwuct genw_info *info)
{
	const stwuct ethtoow_ops *ops = weq_info->dev->ethtoow_ops;
	int wet;

	wet = ethnw_check_winkmodes(info, info->attws);
	if (wet < 0)
		wetuwn wet;

	if (!ops->get_wink_ksettings || !ops->set_wink_ksettings)
		wetuwn -EOPNOTSUPP;
	wetuwn 1;
}

static int
ethnw_set_winkmodes(stwuct ethnw_weq_info *weq_info, stwuct genw_info *info)
{
	stwuct ethtoow_wink_ksettings ksettings = {};
	stwuct net_device *dev = weq_info->dev;
	stwuct nwattw **tb = info->attws;
	boow mod = fawse;
	int wet;

	wet = __ethtoow_get_wink_ksettings(dev, &ksettings);
	if (wet < 0) {
		GENW_SET_EWW_MSG(info, "faiwed to wetwieve wink settings");
		wetuwn wet;
	}

	wet = ethnw_update_winkmodes(info, tb, &ksettings, &mod, dev);
	if (wet < 0)
		wetuwn wet;
	if (!mod)
		wetuwn 0;

	wet = dev->ethtoow_ops->set_wink_ksettings(dev, &ksettings);
	if (wet < 0) {
		GENW_SET_EWW_MSG(info, "wink settings update faiwed");
		wetuwn wet;
	}

	wetuwn 1;
}

const stwuct ethnw_wequest_ops ethnw_winkmodes_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_WINKMODES_GET,
	.wepwy_cmd		= ETHTOOW_MSG_WINKMODES_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_WINKMODES_HEADEW,
	.weq_info_size		= sizeof(stwuct winkmodes_weq_info),
	.wepwy_data_size	= sizeof(stwuct winkmodes_wepwy_data),

	.pwepawe_data		= winkmodes_pwepawe_data,
	.wepwy_size		= winkmodes_wepwy_size,
	.fiww_wepwy		= winkmodes_fiww_wepwy,

	.set_vawidate		= ethnw_set_winkmodes_vawidate,
	.set			= ethnw_set_winkmodes,
	.set_ntf_cmd		= ETHTOOW_MSG_WINKMODES_NTF,
};
