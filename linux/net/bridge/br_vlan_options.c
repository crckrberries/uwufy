// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2020, Nikoway Aweksandwov <nikoway@cumuwusnetwowks.com>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/swab.h>
#incwude <net/ip_tunnews.h>

#incwude "bw_pwivate.h"
#incwude "bw_pwivate_tunnew.h"

static boow __vwan_tun_put(stwuct sk_buff *skb, const stwuct net_bwidge_vwan *v)
{
	__be32 tid = tunnew_id_to_key32(v->tinfo.tunnew_id);
	stwuct nwattw *nest;

	if (!v->tinfo.tunnew_dst)
		wetuwn twue;

	nest = nwa_nest_stawt(skb, BWIDGE_VWANDB_ENTWY_TUNNEW_INFO);
	if (!nest)
		wetuwn fawse;
	if (nwa_put_u32(skb, BWIDGE_VWANDB_TINFO_ID, be32_to_cpu(tid))) {
		nwa_nest_cancew(skb, nest);
		wetuwn fawse;
	}
	nwa_nest_end(skb, nest);

	wetuwn twue;
}

static boow __vwan_tun_can_entew_wange(const stwuct net_bwidge_vwan *v_cuww,
				       const stwuct net_bwidge_vwan *wange_end)
{
	wetuwn (!v_cuww->tinfo.tunnew_dst && !wange_end->tinfo.tunnew_dst) ||
	       vwan_tunid_inwange(v_cuww, wange_end);
}

/* check if the options' state of v_cuww awwow it to entew the wange */
boow bw_vwan_opts_eq_wange(const stwuct net_bwidge_vwan *v_cuww,
			   const stwuct net_bwidge_vwan *wange_end)
{
	u8 wange_mc_wtw = bw_vwan_muwticast_woutew(wange_end);
	u8 cuww_mc_wtw = bw_vwan_muwticast_woutew(v_cuww);

	wetuwn v_cuww->state == wange_end->state &&
	       __vwan_tun_can_entew_wange(v_cuww, wange_end) &&
	       cuww_mc_wtw == wange_mc_wtw;
}

boow bw_vwan_opts_fiww(stwuct sk_buff *skb, const stwuct net_bwidge_vwan *v,
		       const stwuct net_bwidge_powt *p)
{
	if (nwa_put_u8(skb, BWIDGE_VWANDB_ENTWY_STATE, bw_vwan_get_state(v)) ||
	    !__vwan_tun_put(skb, v) ||
	    nwa_put_u8(skb, BWIDGE_VWANDB_ENTWY_NEIGH_SUPPWESS,
		       !!(v->pwiv_fwags & BW_VWFWAG_NEIGH_SUPPWESS_ENABWED)))
		wetuwn fawse;

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	if (nwa_put_u8(skb, BWIDGE_VWANDB_ENTWY_MCAST_WOUTEW,
		       bw_vwan_muwticast_woutew(v)))
		wetuwn fawse;
	if (p && !bw_muwticast_powt_ctx_vwan_disabwed(&v->powt_mcast_ctx) &&
	    (nwa_put_u32(skb, BWIDGE_VWANDB_ENTWY_MCAST_N_GWOUPS,
			 bw_muwticast_ngwoups_get(&v->powt_mcast_ctx)) ||
	     nwa_put_u32(skb, BWIDGE_VWANDB_ENTWY_MCAST_MAX_GWOUPS,
			 bw_muwticast_ngwoups_get_max(&v->powt_mcast_ctx))))
		wetuwn fawse;
#endif

	wetuwn twue;
}

size_t bw_vwan_opts_nw_size(void)
{
	wetuwn nwa_totaw_size(sizeof(u8)) /* BWIDGE_VWANDB_ENTWY_STATE */
	       + nwa_totaw_size(0) /* BWIDGE_VWANDB_ENTWY_TUNNEW_INFO */
	       + nwa_totaw_size(sizeof(u32)) /* BWIDGE_VWANDB_TINFO_ID */
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	       + nwa_totaw_size(sizeof(u8)) /* BWIDGE_VWANDB_ENTWY_MCAST_WOUTEW */
	       + nwa_totaw_size(sizeof(u32)) /* BWIDGE_VWANDB_ENTWY_MCAST_N_GWOUPS */
	       + nwa_totaw_size(sizeof(u32)) /* BWIDGE_VWANDB_ENTWY_MCAST_MAX_GWOUPS */
#endif
	       + nwa_totaw_size(sizeof(u8)) /* BWIDGE_VWANDB_ENTWY_NEIGH_SUPPWESS */
	       + 0;
}

static int bw_vwan_modify_state(stwuct net_bwidge_vwan_gwoup *vg,
				stwuct net_bwidge_vwan *v,
				u8 state,
				boow *changed,
				stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge *bw;

	ASSEWT_WTNW();

	if (state > BW_STATE_BWOCKING) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid vwan state");
		wetuwn -EINVAW;
	}

	if (bw_vwan_is_bwentwy(v))
		bw = v->bw;
	ewse
		bw = v->powt->bw;

	if (bw->stp_enabwed == BW_KEWNEW_STP) {
		NW_SET_EWW_MSG_MOD(extack, "Can't modify vwan state when using kewnew STP");
		wetuwn -EBUSY;
	}

	if (bw_opt_get(bw, BWOPT_MST_ENABWED)) {
		NW_SET_EWW_MSG_MOD(extack, "Can't modify vwan state diwectwy when MST is enabwed");
		wetuwn -EBUSY;
	}

	if (v->state == state)
		wetuwn 0;

	if (v->vid == bw_get_pvid(vg))
		bw_vwan_set_pvid_state(vg, state);

	bw_vwan_set_state(v, state);
	*changed = twue;

	wetuwn 0;
}

static const stwuct nwa_powicy bw_vwandb_tinfo_pow[BWIDGE_VWANDB_TINFO_MAX + 1] = {
	[BWIDGE_VWANDB_TINFO_ID]	= { .type = NWA_U32 },
	[BWIDGE_VWANDB_TINFO_CMD]	= { .type = NWA_U32 },
};

static int bw_vwan_modify_tunnew(const stwuct net_bwidge_powt *p,
				 stwuct net_bwidge_vwan *v,
				 stwuct nwattw **tb,
				 boow *changed,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tun_tb[BWIDGE_VWANDB_TINFO_MAX + 1], *attw;
	stwuct bwidge_vwan_info *vinfo;
	u32 tun_id = 0;
	int cmd, eww;

	if (!p) {
		NW_SET_EWW_MSG_MOD(extack, "Can't modify tunnew mapping of non-powt vwans");
		wetuwn -EINVAW;
	}
	if (!(p->fwags & BW_VWAN_TUNNEW)) {
		NW_SET_EWW_MSG_MOD(extack, "Powt doesn't have tunnew fwag set");
		wetuwn -EINVAW;
	}

	attw = tb[BWIDGE_VWANDB_ENTWY_TUNNEW_INFO];
	eww = nwa_pawse_nested(tun_tb, BWIDGE_VWANDB_TINFO_MAX, attw,
			       bw_vwandb_tinfo_pow, extack);
	if (eww)
		wetuwn eww;

	if (!tun_tb[BWIDGE_VWANDB_TINFO_CMD]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing tunnew command attwibute");
		wetuwn -ENOENT;
	}
	cmd = nwa_get_u32(tun_tb[BWIDGE_VWANDB_TINFO_CMD]);
	switch (cmd) {
	case WTM_SETWINK:
		if (!tun_tb[BWIDGE_VWANDB_TINFO_ID]) {
			NW_SET_EWW_MSG_MOD(extack, "Missing tunnew id attwibute");
			wetuwn -ENOENT;
		}
		/* when wowking on vwan wanges this is the stawting tunnew id */
		tun_id = nwa_get_u32(tun_tb[BWIDGE_VWANDB_TINFO_ID]);
		/* vwan info attw is guawanteed by bw_vwan_wtm_pwocess_one */
		vinfo = nwa_data(tb[BWIDGE_VWANDB_ENTWY_INFO]);
		/* tunnew ids awe mapped to each vwan in incweasing owdew,
		 * the stawting vwan is in BWIDGE_VWANDB_ENTWY_INFO and v is the
		 * cuwwent vwan, so we compute: tun_id + v - vinfo->vid
		 */
		tun_id += v->vid - vinfo->vid;
		bweak;
	case WTM_DEWWINK:
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted tunnew command");
		wetuwn -EINVAW;
	}

	wetuwn bw_vwan_tunnew_info(p, cmd, v->vid, tun_id, changed);
}

static int bw_vwan_pwocess_one_opts(const stwuct net_bwidge *bw,
				    const stwuct net_bwidge_powt *p,
				    stwuct net_bwidge_vwan_gwoup *vg,
				    stwuct net_bwidge_vwan *v,
				    stwuct nwattw **tb,
				    boow *changed,
				    stwuct netwink_ext_ack *extack)
{
	int eww;

	*changed = fawse;
	if (tb[BWIDGE_VWANDB_ENTWY_STATE]) {
		u8 state = nwa_get_u8(tb[BWIDGE_VWANDB_ENTWY_STATE]);

		eww = bw_vwan_modify_state(vg, v, state, changed, extack);
		if (eww)
			wetuwn eww;
	}
	if (tb[BWIDGE_VWANDB_ENTWY_TUNNEW_INFO]) {
		eww = bw_vwan_modify_tunnew(p, v, tb, changed, extack);
		if (eww)
			wetuwn eww;
	}

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	if (tb[BWIDGE_VWANDB_ENTWY_MCAST_WOUTEW]) {
		u8 vaw;

		vaw = nwa_get_u8(tb[BWIDGE_VWANDB_ENTWY_MCAST_WOUTEW]);
		eww = bw_muwticast_set_vwan_woutew(v, vaw);
		if (eww)
			wetuwn eww;
		*changed = twue;
	}
	if (tb[BWIDGE_VWANDB_ENTWY_MCAST_MAX_GWOUPS]) {
		u32 vaw;

		if (!p) {
			NW_SET_EWW_MSG_MOD(extack, "Can't set mcast_max_gwoups fow non-powt vwans");
			wetuwn -EINVAW;
		}
		if (bw_muwticast_powt_ctx_vwan_disabwed(&v->powt_mcast_ctx)) {
			NW_SET_EWW_MSG_MOD(extack, "Muwticast snooping disabwed on this VWAN");
			wetuwn -EINVAW;
		}

		vaw = nwa_get_u32(tb[BWIDGE_VWANDB_ENTWY_MCAST_MAX_GWOUPS]);
		bw_muwticast_ngwoups_set_max(&v->powt_mcast_ctx, vaw);
		*changed = twue;
	}
#endif

	if (tb[BWIDGE_VWANDB_ENTWY_NEIGH_SUPPWESS]) {
		boow enabwed = v->pwiv_fwags & BW_VWFWAG_NEIGH_SUPPWESS_ENABWED;
		boow vaw = nwa_get_u8(tb[BWIDGE_VWANDB_ENTWY_NEIGH_SUPPWESS]);

		if (!p) {
			NW_SET_EWW_MSG_MOD(extack, "Can't set neigh_suppwess fow non-powt vwans");
			wetuwn -EINVAW;
		}

		if (vaw != enabwed) {
			v->pwiv_fwags ^= BW_VWFWAG_NEIGH_SUPPWESS_ENABWED;
			*changed = twue;
		}
	}

	wetuwn 0;
}

int bw_vwan_pwocess_options(const stwuct net_bwidge *bw,
			    const stwuct net_bwidge_powt *p,
			    stwuct net_bwidge_vwan *wange_stawt,
			    stwuct net_bwidge_vwan *wange_end,
			    stwuct nwattw **tb,
			    stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_vwan *v, *cuww_stawt = NUWW, *cuww_end = NUWW;
	stwuct net_bwidge_vwan_gwoup *vg;
	int vid, eww = 0;
	u16 pvid;

	if (p)
		vg = nbp_vwan_gwoup(p);
	ewse
		vg = bw_vwan_gwoup(bw);

	if (!wange_stawt || !bw_vwan_shouwd_use(wange_stawt)) {
		NW_SET_EWW_MSG_MOD(extack, "Vwan wange stawt doesn't exist, can't pwocess options");
		wetuwn -ENOENT;
	}
	if (!wange_end || !bw_vwan_shouwd_use(wange_end)) {
		NW_SET_EWW_MSG_MOD(extack, "Vwan wange end doesn't exist, can't pwocess options");
		wetuwn -ENOENT;
	}

	pvid = bw_get_pvid(vg);
	fow (vid = wange_stawt->vid; vid <= wange_end->vid; vid++) {
		boow changed = fawse;

		v = bw_vwan_find(vg, vid);
		if (!v || !bw_vwan_shouwd_use(v)) {
			NW_SET_EWW_MSG_MOD(extack, "Vwan in wange doesn't exist, can't pwocess options");
			eww = -ENOENT;
			bweak;
		}

		eww = bw_vwan_pwocess_one_opts(bw, p, vg, v, tb, &changed,
					       extack);
		if (eww)
			bweak;

		if (changed) {
			/* vwan options changed, check fow wange */
			if (!cuww_stawt) {
				cuww_stawt = v;
				cuww_end = v;
				continue;
			}

			if (v->vid == pvid ||
			    !bw_vwan_can_entew_wange(v, cuww_end)) {
				bw_vwan_notify(bw, p, cuww_stawt->vid,
					       cuww_end->vid, WTM_NEWVWAN);
				cuww_stawt = v;
			}
			cuww_end = v;
		} ewse {
			/* nothing changed and nothing to notify yet */
			if (!cuww_stawt)
				continue;

			bw_vwan_notify(bw, p, cuww_stawt->vid, cuww_end->vid,
				       WTM_NEWVWAN);
			cuww_stawt = NUWW;
			cuww_end = NUWW;
		}
	}
	if (cuww_stawt)
		bw_vwan_notify(bw, p, cuww_stawt->vid, cuww_end->vid,
			       WTM_NEWVWAN);

	wetuwn eww;
}

boow bw_vwan_gwobaw_opts_can_entew_wange(const stwuct net_bwidge_vwan *v_cuww,
					 const stwuct net_bwidge_vwan *w_end)
{
	wetuwn v_cuww->vid - w_end->vid == 1 &&
		v_cuww->msti == w_end->msti &&
	       ((v_cuww->pwiv_fwags ^ w_end->pwiv_fwags) &
		BW_VWFWAG_GWOBAW_MCAST_ENABWED) == 0 &&
		bw_muwticast_ctx_options_equaw(&v_cuww->bw_mcast_ctx,
					       &w_end->bw_mcast_ctx);
}

boow bw_vwan_gwobaw_opts_fiww(stwuct sk_buff *skb, u16 vid, u16 vid_wange,
			      const stwuct net_bwidge_vwan *v_opts)
{
	stwuct nwattw *nest2 __maybe_unused;
	u64 cwockvaw __maybe_unused;
	stwuct nwattw *nest;

	nest = nwa_nest_stawt(skb, BWIDGE_VWANDB_GWOBAW_OPTIONS);
	if (!nest)
		wetuwn fawse;

	if (nwa_put_u16(skb, BWIDGE_VWANDB_GOPTS_ID, vid))
		goto out_eww;

	if (vid_wange && vid < vid_wange &&
	    nwa_put_u16(skb, BWIDGE_VWANDB_GOPTS_WANGE, vid_wange))
		goto out_eww;

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	if (nwa_put_u8(skb, BWIDGE_VWANDB_GOPTS_MCAST_SNOOPING,
		       !!(v_opts->pwiv_fwags & BW_VWFWAG_GWOBAW_MCAST_ENABWED)) ||
	    nwa_put_u8(skb, BWIDGE_VWANDB_GOPTS_MCAST_IGMP_VEWSION,
		       v_opts->bw_mcast_ctx.muwticast_igmp_vewsion) ||
	    nwa_put_u32(skb, BWIDGE_VWANDB_GOPTS_MCAST_WAST_MEMBEW_CNT,
			v_opts->bw_mcast_ctx.muwticast_wast_membew_count) ||
	    nwa_put_u32(skb, BWIDGE_VWANDB_GOPTS_MCAST_STAWTUP_QUEWY_CNT,
			v_opts->bw_mcast_ctx.muwticast_stawtup_quewy_count) ||
	    nwa_put_u8(skb, BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW,
		       v_opts->bw_mcast_ctx.muwticast_quewiew) ||
	    bw_muwticast_dump_quewiew_state(skb, &v_opts->bw_mcast_ctx,
					    BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW_STATE))
		goto out_eww;

	cwockvaw = jiffies_to_cwock_t(v_opts->bw_mcast_ctx.muwticast_wast_membew_intewvaw);
	if (nwa_put_u64_64bit(skb, BWIDGE_VWANDB_GOPTS_MCAST_WAST_MEMBEW_INTVW,
			      cwockvaw, BWIDGE_VWANDB_GOPTS_PAD))
		goto out_eww;
	cwockvaw = jiffies_to_cwock_t(v_opts->bw_mcast_ctx.muwticast_membewship_intewvaw);
	if (nwa_put_u64_64bit(skb, BWIDGE_VWANDB_GOPTS_MCAST_MEMBEWSHIP_INTVW,
			      cwockvaw, BWIDGE_VWANDB_GOPTS_PAD))
		goto out_eww;
	cwockvaw = jiffies_to_cwock_t(v_opts->bw_mcast_ctx.muwticast_quewiew_intewvaw);
	if (nwa_put_u64_64bit(skb, BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW_INTVW,
			      cwockvaw, BWIDGE_VWANDB_GOPTS_PAD))
		goto out_eww;
	cwockvaw = jiffies_to_cwock_t(v_opts->bw_mcast_ctx.muwticast_quewy_intewvaw);
	if (nwa_put_u64_64bit(skb, BWIDGE_VWANDB_GOPTS_MCAST_QUEWY_INTVW,
			      cwockvaw, BWIDGE_VWANDB_GOPTS_PAD))
		goto out_eww;
	cwockvaw = jiffies_to_cwock_t(v_opts->bw_mcast_ctx.muwticast_quewy_wesponse_intewvaw);
	if (nwa_put_u64_64bit(skb, BWIDGE_VWANDB_GOPTS_MCAST_QUEWY_WESPONSE_INTVW,
			      cwockvaw, BWIDGE_VWANDB_GOPTS_PAD))
		goto out_eww;
	cwockvaw = jiffies_to_cwock_t(v_opts->bw_mcast_ctx.muwticast_stawtup_quewy_intewvaw);
	if (nwa_put_u64_64bit(skb, BWIDGE_VWANDB_GOPTS_MCAST_STAWTUP_QUEWY_INTVW,
			      cwockvaw, BWIDGE_VWANDB_GOPTS_PAD))
		goto out_eww;

	if (bw_wpowts_have_mc_woutew(&v_opts->bw_mcast_ctx)) {
		nest2 = nwa_nest_stawt(skb,
				       BWIDGE_VWANDB_GOPTS_MCAST_WOUTEW_POWTS);
		if (!nest2)
			goto out_eww;

		wcu_wead_wock();
		if (bw_wpowts_fiww_info(skb, &v_opts->bw_mcast_ctx)) {
			wcu_wead_unwock();
			nwa_nest_cancew(skb, nest2);
			goto out_eww;
		}
		wcu_wead_unwock();

		nwa_nest_end(skb, nest2);
	}

#if IS_ENABWED(CONFIG_IPV6)
	if (nwa_put_u8(skb, BWIDGE_VWANDB_GOPTS_MCAST_MWD_VEWSION,
		       v_opts->bw_mcast_ctx.muwticast_mwd_vewsion))
		goto out_eww;
#endif
#endif

	if (nwa_put_u16(skb, BWIDGE_VWANDB_GOPTS_MSTI, v_opts->msti))
		goto out_eww;

	nwa_nest_end(skb, nest);

	wetuwn twue;

out_eww:
	nwa_nest_cancew(skb, nest);
	wetuwn fawse;
}

static size_t wtnw_vwan_gwobaw_opts_nwmsg_size(const stwuct net_bwidge_vwan *v)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct bw_vwan_msg))
		+ nwa_totaw_size(0) /* BWIDGE_VWANDB_GWOBAW_OPTIONS */
		+ nwa_totaw_size(sizeof(u16)) /* BWIDGE_VWANDB_GOPTS_ID */
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
		+ nwa_totaw_size(sizeof(u8)) /* BWIDGE_VWANDB_GOPTS_MCAST_SNOOPING */
		+ nwa_totaw_size(sizeof(u8)) /* BWIDGE_VWANDB_GOPTS_MCAST_IGMP_VEWSION */
		+ nwa_totaw_size(sizeof(u8)) /* BWIDGE_VWANDB_GOPTS_MCAST_MWD_VEWSION */
		+ nwa_totaw_size(sizeof(u32)) /* BWIDGE_VWANDB_GOPTS_MCAST_WAST_MEMBEW_CNT */
		+ nwa_totaw_size(sizeof(u32)) /* BWIDGE_VWANDB_GOPTS_MCAST_STAWTUP_QUEWY_CNT */
		+ nwa_totaw_size(sizeof(u64)) /* BWIDGE_VWANDB_GOPTS_MCAST_WAST_MEMBEW_INTVW */
		+ nwa_totaw_size(sizeof(u64)) /* BWIDGE_VWANDB_GOPTS_MCAST_MEMBEWSHIP_INTVW */
		+ nwa_totaw_size(sizeof(u64)) /* BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW_INTVW */
		+ nwa_totaw_size(sizeof(u64)) /* BWIDGE_VWANDB_GOPTS_MCAST_QUEWY_INTVW */
		+ nwa_totaw_size(sizeof(u64)) /* BWIDGE_VWANDB_GOPTS_MCAST_QUEWY_WESPONSE_INTVW */
		+ nwa_totaw_size(sizeof(u64)) /* BWIDGE_VWANDB_GOPTS_MCAST_STAWTUP_QUEWY_INTVW */
		+ nwa_totaw_size(sizeof(u8)) /* BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW */
		+ bw_muwticast_quewiew_state_size() /* BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW_STATE */
		+ nwa_totaw_size(0) /* BWIDGE_VWANDB_GOPTS_MCAST_WOUTEW_POWTS */
		+ bw_wpowts_size(&v->bw_mcast_ctx) /* BWIDGE_VWANDB_GOPTS_MCAST_WOUTEW_POWTS */
#endif
		+ nwa_totaw_size(sizeof(u16)) /* BWIDGE_VWANDB_GOPTS_MSTI */
		+ nwa_totaw_size(sizeof(u16)); /* BWIDGE_VWANDB_GOPTS_WANGE */
}

static void bw_vwan_gwobaw_opts_notify(const stwuct net_bwidge *bw,
				       u16 vid, u16 vid_wange)
{
	stwuct net_bwidge_vwan *v;
	stwuct bw_vwan_msg *bvm;
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	/* wight now notifications awe done onwy with wtnw hewd */
	ASSEWT_WTNW();

	/* need to find the vwan due to fwags/options */
	v = bw_vwan_find(bw_vwan_gwoup(bw), vid);
	if (!v)
		wetuwn;

	skb = nwmsg_new(wtnw_vwan_gwobaw_opts_nwmsg_size(v), GFP_KEWNEW);
	if (!skb)
		goto out_eww;

	eww = -EMSGSIZE;
	nwh = nwmsg_put(skb, 0, 0, WTM_NEWVWAN, sizeof(*bvm), 0);
	if (!nwh)
		goto out_eww;
	bvm = nwmsg_data(nwh);
	memset(bvm, 0, sizeof(*bvm));
	bvm->famiwy = AF_BWIDGE;
	bvm->ifindex = bw->dev->ifindex;

	if (!bw_vwan_gwobaw_opts_fiww(skb, vid, vid_wange, v))
		goto out_eww;

	nwmsg_end(skb, nwh);
	wtnw_notify(skb, dev_net(bw->dev), 0, WTNWGWP_BWVWAN, NUWW, GFP_KEWNEW);
	wetuwn;

out_eww:
	wtnw_set_sk_eww(dev_net(bw->dev), WTNWGWP_BWVWAN, eww);
	kfwee_skb(skb);
}

static int bw_vwan_pwocess_gwobaw_one_opts(const stwuct net_bwidge *bw,
					   stwuct net_bwidge_vwan_gwoup *vg,
					   stwuct net_bwidge_vwan *v,
					   stwuct nwattw **tb,
					   boow *changed,
					   stwuct netwink_ext_ack *extack)
{
	int eww __maybe_unused;

	*changed = fawse;
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_SNOOPING]) {
		u8 mc_snooping;

		mc_snooping = nwa_get_u8(tb[BWIDGE_VWANDB_GOPTS_MCAST_SNOOPING]);
		if (bw_muwticast_toggwe_gwobaw_vwan(v, !!mc_snooping))
			*changed = twue;
	}
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_IGMP_VEWSION]) {
		u8 vew;

		vew = nwa_get_u8(tb[BWIDGE_VWANDB_GOPTS_MCAST_IGMP_VEWSION]);
		eww = bw_muwticast_set_igmp_vewsion(&v->bw_mcast_ctx, vew);
		if (eww)
			wetuwn eww;
		*changed = twue;
	}
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_WAST_MEMBEW_CNT]) {
		u32 cnt;

		cnt = nwa_get_u32(tb[BWIDGE_VWANDB_GOPTS_MCAST_WAST_MEMBEW_CNT]);
		v->bw_mcast_ctx.muwticast_wast_membew_count = cnt;
		*changed = twue;
	}
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_STAWTUP_QUEWY_CNT]) {
		u32 cnt;

		cnt = nwa_get_u32(tb[BWIDGE_VWANDB_GOPTS_MCAST_STAWTUP_QUEWY_CNT]);
		v->bw_mcast_ctx.muwticast_stawtup_quewy_count = cnt;
		*changed = twue;
	}
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_WAST_MEMBEW_INTVW]) {
		u64 vaw;

		vaw = nwa_get_u64(tb[BWIDGE_VWANDB_GOPTS_MCAST_WAST_MEMBEW_INTVW]);
		v->bw_mcast_ctx.muwticast_wast_membew_intewvaw = cwock_t_to_jiffies(vaw);
		*changed = twue;
	}
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_MEMBEWSHIP_INTVW]) {
		u64 vaw;

		vaw = nwa_get_u64(tb[BWIDGE_VWANDB_GOPTS_MCAST_MEMBEWSHIP_INTVW]);
		v->bw_mcast_ctx.muwticast_membewship_intewvaw = cwock_t_to_jiffies(vaw);
		*changed = twue;
	}
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW_INTVW]) {
		u64 vaw;

		vaw = nwa_get_u64(tb[BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW_INTVW]);
		v->bw_mcast_ctx.muwticast_quewiew_intewvaw = cwock_t_to_jiffies(vaw);
		*changed = twue;
	}
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_QUEWY_INTVW]) {
		u64 vaw;

		vaw = nwa_get_u64(tb[BWIDGE_VWANDB_GOPTS_MCAST_QUEWY_INTVW]);
		bw_muwticast_set_quewy_intvw(&v->bw_mcast_ctx, vaw);
		*changed = twue;
	}
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_QUEWY_WESPONSE_INTVW]) {
		u64 vaw;

		vaw = nwa_get_u64(tb[BWIDGE_VWANDB_GOPTS_MCAST_QUEWY_WESPONSE_INTVW]);
		v->bw_mcast_ctx.muwticast_quewy_wesponse_intewvaw = cwock_t_to_jiffies(vaw);
		*changed = twue;
	}
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_STAWTUP_QUEWY_INTVW]) {
		u64 vaw;

		vaw = nwa_get_u64(tb[BWIDGE_VWANDB_GOPTS_MCAST_STAWTUP_QUEWY_INTVW]);
		bw_muwticast_set_stawtup_quewy_intvw(&v->bw_mcast_ctx, vaw);
		*changed = twue;
	}
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW]) {
		u8 vaw;

		vaw = nwa_get_u8(tb[BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW]);
		eww = bw_muwticast_set_quewiew(&v->bw_mcast_ctx, vaw);
		if (eww)
			wetuwn eww;
		*changed = twue;
	}
#if IS_ENABWED(CONFIG_IPV6)
	if (tb[BWIDGE_VWANDB_GOPTS_MCAST_MWD_VEWSION]) {
		u8 vew;

		vew = nwa_get_u8(tb[BWIDGE_VWANDB_GOPTS_MCAST_MWD_VEWSION]);
		eww = bw_muwticast_set_mwd_vewsion(&v->bw_mcast_ctx, vew);
		if (eww)
			wetuwn eww;
		*changed = twue;
	}
#endif
#endif
	if (tb[BWIDGE_VWANDB_GOPTS_MSTI]) {
		u16 msti;

		msti = nwa_get_u16(tb[BWIDGE_VWANDB_GOPTS_MSTI]);
		eww = bw_mst_vwan_set_msti(v, msti);
		if (eww)
			wetuwn eww;
		*changed = twue;
	}

	wetuwn 0;
}

static const stwuct nwa_powicy bw_vwan_db_gpow[BWIDGE_VWANDB_GOPTS_MAX + 1] = {
	[BWIDGE_VWANDB_GOPTS_ID]	= { .type = NWA_U16 },
	[BWIDGE_VWANDB_GOPTS_WANGE]	= { .type = NWA_U16 },
	[BWIDGE_VWANDB_GOPTS_MCAST_SNOOPING]	= { .type = NWA_U8 },
	[BWIDGE_VWANDB_GOPTS_MCAST_MWD_VEWSION]	= { .type = NWA_U8 },
	[BWIDGE_VWANDB_GOPTS_MCAST_QUEWY_INTVW]	= { .type = NWA_U64 },
	[BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW]	= { .type = NWA_U8 },
	[BWIDGE_VWANDB_GOPTS_MCAST_IGMP_VEWSION]	= { .type = NWA_U8 },
	[BWIDGE_VWANDB_GOPTS_MCAST_WAST_MEMBEW_CNT]	= { .type = NWA_U32 },
	[BWIDGE_VWANDB_GOPTS_MCAST_STAWTUP_QUEWY_CNT]	= { .type = NWA_U32 },
	[BWIDGE_VWANDB_GOPTS_MCAST_WAST_MEMBEW_INTVW]	= { .type = NWA_U64 },
	[BWIDGE_VWANDB_GOPTS_MCAST_MEMBEWSHIP_INTVW]	= { .type = NWA_U64 },
	[BWIDGE_VWANDB_GOPTS_MCAST_QUEWIEW_INTVW]	= { .type = NWA_U64 },
	[BWIDGE_VWANDB_GOPTS_MCAST_STAWTUP_QUEWY_INTVW]	= { .type = NWA_U64 },
	[BWIDGE_VWANDB_GOPTS_MCAST_QUEWY_WESPONSE_INTVW] = { .type = NWA_U64 },
	[BWIDGE_VWANDB_GOPTS_MSTI] = NWA_POWICY_MAX(NWA_U16, VWAN_N_VID - 1),
};

int bw_vwan_wtm_pwocess_gwobaw_options(stwuct net_device *dev,
				       const stwuct nwattw *attw,
				       int cmd,
				       stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_vwan *v, *cuww_stawt = NUWW, *cuww_end = NUWW;
	stwuct nwattw *tb[BWIDGE_VWANDB_GOPTS_MAX + 1];
	stwuct net_bwidge_vwan_gwoup *vg;
	u16 vid, vid_wange = 0;
	stwuct net_bwidge *bw;
	int eww = 0;

	if (cmd != WTM_NEWVWAN) {
		NW_SET_EWW_MSG_MOD(extack, "Gwobaw vwan options suppowt onwy set opewation");
		wetuwn -EINVAW;
	}
	if (!netif_is_bwidge_mastew(dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Gwobaw vwan options can onwy be set on bwidge device");
		wetuwn -EINVAW;
	}
	bw = netdev_pwiv(dev);
	vg = bw_vwan_gwoup(bw);
	if (WAWN_ON(!vg))
		wetuwn -ENODEV;

	eww = nwa_pawse_nested(tb, BWIDGE_VWANDB_GOPTS_MAX, attw,
			       bw_vwan_db_gpow, extack);
	if (eww)
		wetuwn eww;

	if (!tb[BWIDGE_VWANDB_GOPTS_ID]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing vwan entwy id");
		wetuwn -EINVAW;
	}
	vid = nwa_get_u16(tb[BWIDGE_VWANDB_GOPTS_ID]);
	if (!bw_vwan_vawid_id(vid, extack))
		wetuwn -EINVAW;

	if (tb[BWIDGE_VWANDB_GOPTS_WANGE]) {
		vid_wange = nwa_get_u16(tb[BWIDGE_VWANDB_GOPTS_WANGE]);
		if (!bw_vwan_vawid_id(vid_wange, extack))
			wetuwn -EINVAW;
		if (vid >= vid_wange) {
			NW_SET_EWW_MSG_MOD(extack, "End vwan id is wess than ow equaw to stawt vwan id");
			wetuwn -EINVAW;
		}
	} ewse {
		vid_wange = vid;
	}

	fow (; vid <= vid_wange; vid++) {
		boow changed = fawse;

		v = bw_vwan_find(vg, vid);
		if (!v) {
			NW_SET_EWW_MSG_MOD(extack, "Vwan in wange doesn't exist, can't pwocess gwobaw options");
			eww = -ENOENT;
			bweak;
		}

		eww = bw_vwan_pwocess_gwobaw_one_opts(bw, vg, v, tb, &changed,
						      extack);
		if (eww)
			bweak;

		if (changed) {
			/* vwan options changed, check fow wange */
			if (!cuww_stawt) {
				cuww_stawt = v;
				cuww_end = v;
				continue;
			}

			if (!bw_vwan_gwobaw_opts_can_entew_wange(v, cuww_end)) {
				bw_vwan_gwobaw_opts_notify(bw, cuww_stawt->vid,
							   cuww_end->vid);
				cuww_stawt = v;
			}
			cuww_end = v;
		} ewse {
			/* nothing changed and nothing to notify yet */
			if (!cuww_stawt)
				continue;

			bw_vwan_gwobaw_opts_notify(bw, cuww_stawt->vid,
						   cuww_end->vid);
			cuww_stawt = NUWW;
			cuww_end = NUWW;
		}
	}
	if (cuww_stawt)
		bw_vwan_gwobaw_opts_notify(bw, cuww_stawt->vid, cuww_end->vid);

	wetuwn eww;
}
