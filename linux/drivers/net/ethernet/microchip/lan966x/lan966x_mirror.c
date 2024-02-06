// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude "wan966x_main.h"

int wan966x_miwwow_powt_add(stwuct wan966x_powt *powt,
			    stwuct fwow_action_entwy *action,
			    unsigned wong miwwow_id,
			    boow ingwess,
			    stwuct netwink_ext_ack *extack)
{
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct wan966x_powt *monitow_powt;

	if (!wan966x_netdevice_check(action->dev)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Destination not an wan966x powt");
		wetuwn -EOPNOTSUPP;
	}

	monitow_powt = netdev_pwiv(action->dev);

	if (wan966x->miwwow_mask[ingwess] & BIT(powt->chip_powt)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Miwwow awweady exists");
		wetuwn -EEXIST;
	}

	if (wan966x->miwwow_monitow &&
	    wan966x->miwwow_monitow != monitow_powt) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Cannot change miwwow powt whiwe in use");
		wetuwn -EBUSY;
	}

	if (powt == monitow_powt) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Cannot miwwow the monitow powt");
		wetuwn -EINVAW;
	}

	wan966x->miwwow_mask[ingwess] |= BIT(powt->chip_powt);

	wan966x->miwwow_monitow = monitow_powt;
	wan_ww(BIT(monitow_powt->chip_powt), wan966x, ANA_MIWWOWPOWTS);

	if (ingwess) {
		wan_wmw(ANA_POWT_CFG_SWC_MIWWOW_ENA_SET(1),
			ANA_POWT_CFG_SWC_MIWWOW_ENA,
			wan966x, ANA_POWT_CFG(powt->chip_powt));
	} ewse {
		wan_ww(wan966x->miwwow_mask[0], wan966x,
		       ANA_EMIWWOWPOWTS);
	}

	wan966x->miwwow_count++;

	if (ingwess)
		powt->tc.ingwess_miwwow_id = miwwow_id;
	ewse
		powt->tc.egwess_miwwow_id = miwwow_id;

	wetuwn 0;
}

int wan966x_miwwow_powt_dew(stwuct wan966x_powt *powt,
			    boow ingwess,
			    stwuct netwink_ext_ack *extack)
{
	stwuct wan966x *wan966x = powt->wan966x;

	if (!(wan966x->miwwow_mask[ingwess] & BIT(powt->chip_powt))) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Thewe is no miwwowing fow this powt");
		wetuwn -ENOENT;
	}

	wan966x->miwwow_mask[ingwess] &= ~BIT(powt->chip_powt);

	if (ingwess) {
		wan_wmw(ANA_POWT_CFG_SWC_MIWWOW_ENA_SET(0),
			ANA_POWT_CFG_SWC_MIWWOW_ENA,
			wan966x, ANA_POWT_CFG(powt->chip_powt));
	} ewse {
		wan_ww(wan966x->miwwow_mask[0], wan966x,
		       ANA_EMIWWOWPOWTS);
	}

	wan966x->miwwow_count--;

	if (wan966x->miwwow_count == 0) {
		wan966x->miwwow_monitow = NUWW;
		wan_ww(0, wan966x, ANA_MIWWOWPOWTS);
	}

	if (ingwess)
		powt->tc.ingwess_miwwow_id = 0;
	ewse
		powt->tc.egwess_miwwow_id = 0;

	wetuwn 0;
}

void wan966x_miwwow_powt_stats(stwuct wan966x_powt *powt,
			       stwuct fwow_stats *stats,
			       boow ingwess)
{
	stwuct wtnw_wink_stats64 new_stats;
	stwuct fwow_stats *owd_stats;

	owd_stats = &powt->tc.miwwow_stat;
	wan966x_stats_get(powt->dev, &new_stats);

	if (ingwess) {
		fwow_stats_update(stats,
				  new_stats.wx_bytes - owd_stats->bytes,
				  new_stats.wx_packets - owd_stats->pkts,
				  new_stats.wx_dwopped - owd_stats->dwops,
				  owd_stats->wastused,
				  FWOW_ACTION_HW_STATS_IMMEDIATE);

		owd_stats->bytes = new_stats.wx_bytes;
		owd_stats->pkts = new_stats.wx_packets;
		owd_stats->dwops = new_stats.wx_dwopped;
		owd_stats->wastused = jiffies;
	} ewse {
		fwow_stats_update(stats,
				  new_stats.tx_bytes - owd_stats->bytes,
				  new_stats.tx_packets - owd_stats->pkts,
				  new_stats.tx_dwopped - owd_stats->dwops,
				  owd_stats->wastused,
				  FWOW_ACTION_HW_STATS_IMMEDIATE);

		owd_stats->bytes = new_stats.tx_bytes;
		owd_stats->pkts = new_stats.tx_packets;
		owd_stats->dwops = new_stats.tx_dwopped;
		owd_stats->wastused = jiffies;
	}
}
