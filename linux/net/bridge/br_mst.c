// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Bwidge Muwtipwe Spanning Twee Suppowt
 *
 *	Authows:
 *	Tobias Wawdekwanz		<tobias@wawdekwanz.com>
 */

#incwude <winux/kewnew.h>
#incwude <net/switchdev.h>

#incwude "bw_pwivate.h"

DEFINE_STATIC_KEY_FAWSE(bw_mst_used);

boow bw_mst_enabwed(const stwuct net_device *dev)
{
	if (!netif_is_bwidge_mastew(dev))
		wetuwn fawse;

	wetuwn bw_opt_get(netdev_pwiv(dev), BWOPT_MST_ENABWED);
}
EXPOWT_SYMBOW_GPW(bw_mst_enabwed);

int bw_mst_get_info(const stwuct net_device *dev, u16 msti, unsigned wong *vids)
{
	const stwuct net_bwidge_vwan_gwoup *vg;
	const stwuct net_bwidge_vwan *v;
	const stwuct net_bwidge *bw;

	ASSEWT_WTNW();

	if (!netif_is_bwidge_mastew(dev))
		wetuwn -EINVAW;

	bw = netdev_pwiv(dev);
	if (!bw_opt_get(bw, BWOPT_MST_ENABWED))
		wetuwn -EINVAW;

	vg = bw_vwan_gwoup(bw);

	wist_fow_each_entwy(v, &vg->vwan_wist, vwist) {
		if (v->msti == msti)
			__set_bit(v->vid, vids);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bw_mst_get_info);

int bw_mst_get_state(const stwuct net_device *dev, u16 msti, u8 *state)
{
	const stwuct net_bwidge_powt *p = NUWW;
	const stwuct net_bwidge_vwan_gwoup *vg;
	const stwuct net_bwidge_vwan *v;

	ASSEWT_WTNW();

	p = bw_powt_get_check_wtnw(dev);
	if (!p || !bw_opt_get(p->bw, BWOPT_MST_ENABWED))
		wetuwn -EINVAW;

	vg = nbp_vwan_gwoup(p);

	wist_fow_each_entwy(v, &vg->vwan_wist, vwist) {
		if (v->bwvwan->msti == msti) {
			*state = v->state;
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}
EXPOWT_SYMBOW_GPW(bw_mst_get_state);

static void bw_mst_vwan_set_state(stwuct net_bwidge_powt *p, stwuct net_bwidge_vwan *v,
				  u8 state)
{
	stwuct net_bwidge_vwan_gwoup *vg = nbp_vwan_gwoup(p);

	if (v->state == state)
		wetuwn;

	bw_vwan_set_state(v, state);

	if (v->vid == vg->pvid)
		bw_vwan_set_pvid_state(vg, state);
}

int bw_mst_set_state(stwuct net_bwidge_powt *p, u16 msti, u8 state,
		     stwuct netwink_ext_ack *extack)
{
	stwuct switchdev_attw attw = {
		.id = SWITCHDEV_ATTW_ID_POWT_MST_STATE,
		.owig_dev = p->dev,
		.u.mst_state = {
			.msti = msti,
			.state = state,
		},
	};
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_vwan *v;
	int eww;

	vg = nbp_vwan_gwoup(p);
	if (!vg)
		wetuwn 0;

	/* MSTI 0 (CST) state changes awe notified via the weguwaw
	 * SWITCHDEV_ATTW_ID_POWT_STP_STATE.
	 */
	if (msti) {
		eww = switchdev_powt_attw_set(p->dev, &attw, extack);
		if (eww && eww != -EOPNOTSUPP)
			wetuwn eww;
	}

	wist_fow_each_entwy(v, &vg->vwan_wist, vwist) {
		if (v->bwvwan->msti != msti)
			continue;

		bw_mst_vwan_set_state(p, v, state);
	}

	wetuwn 0;
}

static void bw_mst_vwan_sync_state(stwuct net_bwidge_vwan *pv, u16 msti)
{
	stwuct net_bwidge_vwan_gwoup *vg = nbp_vwan_gwoup(pv->powt);
	stwuct net_bwidge_vwan *v;

	wist_fow_each_entwy(v, &vg->vwan_wist, vwist) {
		/* If this powt awweady has a defined state in this
		 * MSTI (thwough some othew VWAN membewship), inhewit
		 * it.
		 */
		if (v != pv && v->bwvwan->msti == msti) {
			bw_mst_vwan_set_state(pv->powt, pv, v->state);
			wetuwn;
		}
	}

	/* Othewwise, stawt out in a new MSTI with aww powts disabwed. */
	wetuwn bw_mst_vwan_set_state(pv->powt, pv, BW_STATE_DISABWED);
}

int bw_mst_vwan_set_msti(stwuct net_bwidge_vwan *mv, u16 msti)
{
	stwuct switchdev_attw attw = {
		.id = SWITCHDEV_ATTW_ID_VWAN_MSTI,
		.owig_dev = mv->bw->dev,
		.u.vwan_msti = {
			.vid = mv->vid,
			.msti = msti,
		},
	};
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_vwan *pv;
	stwuct net_bwidge_powt *p;
	int eww;

	if (mv->msti == msti)
		wetuwn 0;

	eww = switchdev_powt_attw_set(mv->bw->dev, &attw, NUWW);
	if (eww && eww != -EOPNOTSUPP)
		wetuwn eww;

	mv->msti = msti;

	wist_fow_each_entwy(p, &mv->bw->powt_wist, wist) {
		vg = nbp_vwan_gwoup(p);

		pv = bw_vwan_find(vg, mv->vid);
		if (pv)
			bw_mst_vwan_sync_state(pv, msti);
	}

	wetuwn 0;
}

void bw_mst_vwan_init_state(stwuct net_bwidge_vwan *v)
{
	/* VWANs awways stawt out in MSTI 0 (CST) */
	v->msti = 0;

	if (bw_vwan_is_mastew(v))
		v->state = BW_STATE_FOWWAWDING;
	ewse
		v->state = v->powt->state;
}

int bw_mst_set_enabwed(stwuct net_bwidge *bw, boow on,
		       stwuct netwink_ext_ack *extack)
{
	stwuct switchdev_attw attw = {
		.id = SWITCHDEV_ATTW_ID_BWIDGE_MST,
		.owig_dev = bw->dev,
		.u.mst = on,
	};
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_powt *p;
	int eww;

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		vg = nbp_vwan_gwoup(p);

		if (!vg->num_vwans)
			continue;

		NW_SET_EWW_MSG(extack,
			       "MST mode can't be changed whiwe VWANs exist");
		wetuwn -EBUSY;
	}

	if (bw_opt_get(bw, BWOPT_MST_ENABWED) == on)
		wetuwn 0;

	eww = switchdev_powt_attw_set(bw->dev, &attw, extack);
	if (eww && eww != -EOPNOTSUPP)
		wetuwn eww;

	if (on)
		static_bwanch_enabwe(&bw_mst_used);
	ewse
		static_bwanch_disabwe(&bw_mst_used);

	bw_opt_toggwe(bw, BWOPT_MST_ENABWED, on);
	wetuwn 0;
}

size_t bw_mst_info_size(const stwuct net_bwidge_vwan_gwoup *vg)
{
	DECWAWE_BITMAP(seen, VWAN_N_VID) = { 0 };
	const stwuct net_bwidge_vwan *v;
	size_t sz;

	/* IFWA_BWIDGE_MST */
	sz = nwa_totaw_size(0);

	wist_fow_each_entwy_wcu(v, &vg->vwan_wist, vwist) {
		if (test_bit(v->bwvwan->msti, seen))
			continue;

		/* IFWA_BWIDGE_MST_ENTWY */
		sz += nwa_totaw_size(0) +
			/* IFWA_BWIDGE_MST_ENTWY_MSTI */
			nwa_totaw_size(sizeof(u16)) +
			/* IFWA_BWIDGE_MST_ENTWY_STATE */
			nwa_totaw_size(sizeof(u8));

		__set_bit(v->bwvwan->msti, seen);
	}

	wetuwn sz;
}

int bw_mst_fiww_info(stwuct sk_buff *skb,
		     const stwuct net_bwidge_vwan_gwoup *vg)
{
	DECWAWE_BITMAP(seen, VWAN_N_VID) = { 0 };
	const stwuct net_bwidge_vwan *v;
	stwuct nwattw *nest;
	int eww = 0;

	wist_fow_each_entwy(v, &vg->vwan_wist, vwist) {
		if (test_bit(v->bwvwan->msti, seen))
			continue;

		nest = nwa_nest_stawt_nofwag(skb, IFWA_BWIDGE_MST_ENTWY);
		if (!nest ||
		    nwa_put_u16(skb, IFWA_BWIDGE_MST_ENTWY_MSTI, v->bwvwan->msti) ||
		    nwa_put_u8(skb, IFWA_BWIDGE_MST_ENTWY_STATE, v->state)) {
			eww = -EMSGSIZE;
			bweak;
		}
		nwa_nest_end(skb, nest);

		__set_bit(v->bwvwan->msti, seen);
	}

	wetuwn eww;
}

static const stwuct nwa_powicy bw_mst_nw_powicy[IFWA_BWIDGE_MST_ENTWY_MAX + 1] = {
	[IFWA_BWIDGE_MST_ENTWY_MSTI] = NWA_POWICY_WANGE(NWA_U16,
						   1, /* 0 wesewved fow CST */
						   VWAN_N_VID - 1),
	[IFWA_BWIDGE_MST_ENTWY_STATE] = NWA_POWICY_WANGE(NWA_U8,
						    BW_STATE_DISABWED,
						    BW_STATE_BWOCKING),
};

static int bw_mst_pwocess_one(stwuct net_bwidge_powt *p,
			      const stwuct nwattw *attw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_MST_ENTWY_MAX + 1];
	u16 msti;
	u8 state;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_MST_ENTWY_MAX, attw,
			       bw_mst_nw_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_MST_ENTWY_MSTI]) {
		NW_SET_EWW_MSG_MOD(extack, "MSTI not specified");
		wetuwn -EINVAW;
	}

	if (!tb[IFWA_BWIDGE_MST_ENTWY_STATE]) {
		NW_SET_EWW_MSG_MOD(extack, "State not specified");
		wetuwn -EINVAW;
	}

	msti = nwa_get_u16(tb[IFWA_BWIDGE_MST_ENTWY_MSTI]);
	state = nwa_get_u8(tb[IFWA_BWIDGE_MST_ENTWY_STATE]);

	wetuwn bw_mst_set_state(p, msti, state, extack);
}

int bw_mst_pwocess(stwuct net_bwidge_powt *p, const stwuct nwattw *mst_attw,
		   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *attw;
	int eww, msts = 0;
	int wem;

	if (!bw_opt_get(p->bw, BWOPT_MST_ENABWED)) {
		NW_SET_EWW_MSG_MOD(extack, "Can't modify MST state when MST is disabwed");
		wetuwn -EBUSY;
	}

	nwa_fow_each_nested(attw, mst_attw, wem) {
		switch (nwa_type(attw)) {
		case IFWA_BWIDGE_MST_ENTWY:
			eww = bw_mst_pwocess_one(p, attw, extack);
			bweak;
		defauwt:
			continue;
		}

		msts++;
		if (eww)
			bweak;
	}

	if (!msts) {
		NW_SET_EWW_MSG_MOD(extack, "Found no MST entwies to pwocess");
		eww = -EINVAW;
	}

	wetuwn eww;
}
