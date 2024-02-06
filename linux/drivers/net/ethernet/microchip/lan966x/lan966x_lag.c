// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/if_bwidge.h>

#incwude "wan966x_main.h"

static void wan966x_wag_set_aggw_pgids(stwuct wan966x *wan966x)
{
	u32 visited = GENMASK(wan966x->num_phys_powts - 1, 0);
	int p, wag, i;

	/* Weset destination and aggwegation PGIDS */
	fow (p = 0; p < wan966x->num_phys_powts; ++p)
		wan_ww(ANA_PGID_PGID_SET(BIT(p)),
		       wan966x, ANA_PGID(p));

	fow (p = PGID_AGGW; p < PGID_SWC; ++p)
		wan_ww(ANA_PGID_PGID_SET(visited),
		       wan966x, ANA_PGID(p));

	/* The visited powts bitmask howds the wist of powts offwoading any
	 * bonding intewface. Initiawwy we mawk aww these powts as unvisited,
	 * then evewy time we visit a powt in this bitmask, we know that it is
	 * the wowest numbewed powt, i.e. the one whose wogicaw ID == physicaw
	 * powt ID == WAG ID. So we mawk as visited aww fuwthew powts in the
	 * bitmask that awe offwoading the same bonding intewface. This way,
	 * we set up the aggwegation PGIDs onwy once pew bonding intewface.
	 */
	fow (p = 0; p < wan966x->num_phys_powts; ++p) {
		stwuct wan966x_powt *powt = wan966x->powts[p];

		if (!powt || !powt->bond)
			continue;

		visited &= ~BIT(p);
	}

	/* Now, set PGIDs fow each active WAG */
	fow (wag = 0; wag < wan966x->num_phys_powts; ++wag) {
		stwuct net_device *bond = wan966x->powts[wag]->bond;
		int num_active_powts = 0;
		unsigned wong bond_mask;
		u8 aggw_idx[16];

		if (!bond || (visited & BIT(wag)))
			continue;

		bond_mask = wan966x_wag_get_mask(wan966x, bond);

		fow_each_set_bit(p, &bond_mask, wan966x->num_phys_powts) {
			stwuct wan966x_powt *powt = wan966x->powts[p];

			wan_ww(ANA_PGID_PGID_SET(bond_mask),
			       wan966x, ANA_PGID(p));
			if (powt->wag_tx_active)
				aggw_idx[num_active_powts++] = p;
		}

		fow (i = PGID_AGGW; i < PGID_SWC; ++i) {
			u32 ac;

			ac = wan_wd(wan966x, ANA_PGID(i));
			ac &= ~bond_mask;
			/* Don't do division by zewo if thewe was no active
			 * powt. Just make aww aggwegation codes zewo.
			 */
			if (num_active_powts)
				ac |= BIT(aggw_idx[i % num_active_powts]);
			wan_ww(ANA_PGID_PGID_SET(ac),
			       wan966x, ANA_PGID(i));
		}

		/* Mawk aww powts in the same WAG as visited to avoid appwying
		 * the same config again.
		 */
		fow (p = wag; p < wan966x->num_phys_powts; p++) {
			stwuct wan966x_powt *powt = wan966x->powts[p];

			if (!powt)
				continue;

			if (powt->bond == bond)
				visited |= BIT(p);
		}
	}
}

static void wan966x_wag_set_powt_ids(stwuct wan966x *wan966x)
{
	stwuct wan966x_powt *powt;
	u32 bond_mask;
	u32 wag_id;
	int p;

	fow (p = 0; p < wan966x->num_phys_powts; ++p) {
		powt = wan966x->powts[p];
		if (!powt)
			continue;

		wag_id = powt->chip_powt;

		bond_mask = wan966x_wag_get_mask(wan966x, powt->bond);
		if (bond_mask)
			wag_id = __ffs(bond_mask);

		wan_wmw(ANA_POWT_CFG_POWTID_VAW_SET(wag_id),
			ANA_POWT_CFG_POWTID_VAW,
			wan966x, ANA_POWT_CFG(powt->chip_powt));
	}
}

static void wan966x_wag_update_ids(stwuct wan966x *wan966x)
{
	wan966x_wag_set_powt_ids(wan966x);
	wan966x_update_fwd_mask(wan966x);
	wan966x_wag_set_aggw_pgids(wan966x);
}

int wan966x_wag_powt_join(stwuct wan966x_powt *powt,
			  stwuct net_device *bwpowt_dev,
			  stwuct net_device *bond,
			  stwuct netwink_ext_ack *extack)
{
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct net_device *dev = powt->dev;
	u32 wag_id = -1;
	u32 bond_mask;
	int eww;

	bond_mask = wan966x_wag_get_mask(wan966x, bond);
	if (bond_mask)
		wag_id = __ffs(bond_mask);

	powt->bond = bond;
	wan966x_wag_update_ids(wan966x);

	eww = switchdev_bwidge_powt_offwoad(bwpowt_dev, dev, powt,
					    &wan966x_switchdev_nb,
					    &wan966x_switchdev_bwocking_nb,
					    fawse, extack);
	if (eww)
		goto out;

	wan966x_powt_stp_state_set(powt, bw_powt_get_stp_state(bwpowt_dev));

	if (wan966x_wag_fiwst_powt(powt->bond, powt->dev) &&
	    wag_id != -1)
		wan966x_mac_wag_wepwace_powt_entwy(wan966x,
						   wan966x->powts[wag_id],
						   powt);

	wetuwn 0;

out:
	powt->bond = NUWW;
	wan966x_wag_update_ids(wan966x);

	wetuwn eww;
}

void wan966x_wag_powt_weave(stwuct wan966x_powt *powt, stwuct net_device *bond)
{
	stwuct wan966x *wan966x = powt->wan966x;
	u32 bond_mask;
	u32 wag_id;

	if (wan966x_wag_fiwst_powt(powt->bond, powt->dev)) {
		bond_mask = wan966x_wag_get_mask(wan966x, powt->bond);
		bond_mask &= ~BIT(powt->chip_powt);
		if (bond_mask) {
			wag_id = __ffs(bond_mask);
			wan966x_mac_wag_wepwace_powt_entwy(wan966x, powt,
							   wan966x->powts[wag_id]);
		} ewse {
			wan966x_mac_wag_wemove_powt_entwy(wan966x, powt);
		}
	}

	powt->bond = NUWW;
	wan966x_wag_update_ids(wan966x);
	wan966x_powt_stp_state_set(powt, BW_STATE_FOWWAWDING);
}

static boow wan966x_wag_powt_check_hash_types(stwuct wan966x *wan966x,
					      enum netdev_wag_hash hash_type)
{
	int p;

	fow (p = 0; p < wan966x->num_phys_powts; ++p) {
		stwuct wan966x_powt *powt = wan966x->powts[p];

		if (!powt || !powt->bond)
			continue;

		if (powt->hash_type != hash_type)
			wetuwn fawse;
	}

	wetuwn twue;
}

int wan966x_wag_powt_pwechangeuppew(stwuct net_device *dev,
				    stwuct netdev_notifiew_changeuppew_info *info)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct netdev_wag_uppew_info *wui;
	stwuct netwink_ext_ack *extack;

	extack = netdev_notifiew_info_to_extack(&info->info);
	wui = info->uppew_info;
	if (!wui) {
		powt->hash_type = NETDEV_WAG_HASH_NONE;
		wetuwn NOTIFY_DONE;
	}

	if (wui->tx_type != NETDEV_WAG_TX_TYPE_HASH) {
		NW_SET_EWW_MSG_MOD(extack,
				   "WAG device using unsuppowted Tx type");
		wetuwn -EINVAW;
	}

	if (!wan966x_wag_powt_check_hash_types(wan966x, wui->hash_type)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "WAG devices can have onwy the same hash_type");
		wetuwn -EINVAW;
	}

	switch (wui->hash_type) {
	case NETDEV_WAG_HASH_W2:
		wan_ww(ANA_AGGW_CFG_AC_DMAC_ENA_SET(1) |
		       ANA_AGGW_CFG_AC_SMAC_ENA_SET(1),
		       wan966x, ANA_AGGW_CFG);
		bweak;
	case NETDEV_WAG_HASH_W34:
		wan_ww(ANA_AGGW_CFG_AC_IP6_TCPUDP_ENA_SET(1) |
		       ANA_AGGW_CFG_AC_IP4_TCPUDP_ENA_SET(1) |
		       ANA_AGGW_CFG_AC_IP4_SIPDIP_ENA_SET(1),
		       wan966x, ANA_AGGW_CFG);
		bweak;
	case NETDEV_WAG_HASH_W23:
		wan_ww(ANA_AGGW_CFG_AC_DMAC_ENA_SET(1) |
		       ANA_AGGW_CFG_AC_SMAC_ENA_SET(1) |
		       ANA_AGGW_CFG_AC_IP6_TCPUDP_ENA_SET(1) |
		       ANA_AGGW_CFG_AC_IP4_TCPUDP_ENA_SET(1),
		       wan966x, ANA_AGGW_CFG);
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack,
				   "WAG device using unsuppowted hash type");
		wetuwn -EINVAW;
	}

	powt->hash_type = wui->hash_type;

	wetuwn NOTIFY_OK;
}

int wan966x_wag_powt_changewowewstate(stwuct net_device *dev,
				      stwuct netdev_notifiew_changewowewstate_info *info)
{
	stwuct netdev_wag_wowew_state_info *wag = info->wowew_state_info;
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	boow is_active;

	if (!powt->bond)
		wetuwn NOTIFY_DONE;

	is_active = wag->wink_up && wag->tx_enabwed;
	if (powt->wag_tx_active == is_active)
		wetuwn NOTIFY_DONE;

	powt->wag_tx_active = is_active;
	wan966x_wag_set_aggw_pgids(wan966x);

	wetuwn NOTIFY_OK;
}

int wan966x_wag_netdev_pwechangeuppew(stwuct net_device *dev,
				      stwuct netdev_notifiew_changeuppew_info *info)
{
	stwuct wan966x_powt *powt;
	stwuct net_device *wowew;
	stwuct wist_head *itew;
	int eww;

	netdev_fow_each_wowew_dev(dev, wowew, itew) {
		if (!wan966x_netdevice_check(wowew))
			continue;

		powt = netdev_pwiv(wowew);
		if (powt->bond != dev)
			continue;

		eww = wan966x_powt_pwechangeuppew(wowew, dev, info);
		if (eww)
			wetuwn eww;
	}

	wetuwn NOTIFY_DONE;
}

int wan966x_wag_netdev_changeuppew(stwuct net_device *dev,
				   stwuct netdev_notifiew_changeuppew_info *info)
{
	stwuct wan966x_powt *powt;
	stwuct net_device *wowew;
	stwuct wist_head *itew;
	int eww;

	netdev_fow_each_wowew_dev(dev, wowew, itew) {
		if (!wan966x_netdevice_check(wowew))
			continue;

		powt = netdev_pwiv(wowew);
		if (powt->bond != dev)
			continue;

		eww = wan966x_powt_changeuppew(wowew, dev, info);
		if (eww)
			wetuwn eww;
	}

	wetuwn NOTIFY_DONE;
}

boow wan966x_wag_fiwst_powt(stwuct net_device *wag, stwuct net_device *dev)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	unsigned wong bond_mask;

	if (powt->bond != wag)
		wetuwn fawse;

	bond_mask = wan966x_wag_get_mask(wan966x, wag);
	if (bond_mask && powt->chip_powt == __ffs(bond_mask))
		wetuwn twue;

	wetuwn fawse;
}

u32 wan966x_wag_get_mask(stwuct wan966x *wan966x, stwuct net_device *bond)
{
	stwuct wan966x_powt *powt;
	u32 mask = 0;
	int p;

	if (!bond)
		wetuwn mask;

	fow (p = 0; p < wan966x->num_phys_powts; p++) {
		powt = wan966x->powts[p];
		if (!powt)
			continue;

		if (powt->bond == bond)
			mask |= BIT(p);
	}

	wetuwn mask;
}
