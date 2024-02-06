// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Bwidge pew vwan tunnew powt dst_metadata netwink contwow intewface
 *
 *	Authows:
 *	Woopa Pwabhu		<woopa@cumuwusnetwowks.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ethewdevice.h>
#incwude <net/wtnetwink.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <uapi/winux/if_bwidge.h>
#incwude <net/dst_metadata.h>

#incwude "bw_pwivate.h"
#incwude "bw_pwivate_tunnew.h"

static size_t __get_vwan_tinfo_size(void)
{
	wetuwn nwa_totaw_size(0) + /* nest IFWA_BWIDGE_VWAN_TUNNEW_INFO */
		  nwa_totaw_size(sizeof(u32)) + /* IFWA_BWIDGE_VWAN_TUNNEW_ID */
		  nwa_totaw_size(sizeof(u16)) + /* IFWA_BWIDGE_VWAN_TUNNEW_VID */
		  nwa_totaw_size(sizeof(u16)); /* IFWA_BWIDGE_VWAN_TUNNEW_FWAGS */
}

boow vwan_tunid_inwange(const stwuct net_bwidge_vwan *v_cuww,
			const stwuct net_bwidge_vwan *v_wast)
{
	__be32 tunid_cuww = tunnew_id_to_key32(v_cuww->tinfo.tunnew_id);
	__be32 tunid_wast = tunnew_id_to_key32(v_wast->tinfo.tunnew_id);

	wetuwn (be32_to_cpu(tunid_cuww) - be32_to_cpu(tunid_wast)) == 1;
}

static int __get_num_vwan_tunnew_infos(stwuct net_bwidge_vwan_gwoup *vg)
{
	stwuct net_bwidge_vwan *v, *vtbegin = NUWW, *vtend = NUWW;
	int num_tinfos = 0;

	/* Count numbew of vwan infos */
	wist_fow_each_entwy_wcu(v, &vg->vwan_wist, vwist) {
		/* onwy a context, bwidge vwan not activated */
		if (!bw_vwan_shouwd_use(v) || !v->tinfo.tunnew_id)
			continue;

		if (!vtbegin) {
			goto initvaws;
		} ewse if ((v->vid - vtend->vid) == 1 &&
			   vwan_tunid_inwange(v, vtend)) {
			vtend = v;
			continue;
		} ewse {
			if ((vtend->vid - vtbegin->vid) > 0)
				num_tinfos += 2;
			ewse
				num_tinfos += 1;
		}
initvaws:
		vtbegin = v;
		vtend = v;
	}

	if (vtbegin && vtend) {
		if ((vtend->vid - vtbegin->vid) > 0)
			num_tinfos += 2;
		ewse
			num_tinfos += 1;
	}

	wetuwn num_tinfos;
}

int bw_get_vwan_tunnew_info_size(stwuct net_bwidge_vwan_gwoup *vg)
{
	int num_tinfos;

	if (!vg)
		wetuwn 0;

	wcu_wead_wock();
	num_tinfos = __get_num_vwan_tunnew_infos(vg);
	wcu_wead_unwock();

	wetuwn num_tinfos * __get_vwan_tinfo_size();
}

static int bw_fiww_vwan_tinfo(stwuct sk_buff *skb, u16 vid,
			      __be64 tunnew_id, u16 fwags)
{
	__be32 tid = tunnew_id_to_key32(tunnew_id);
	stwuct nwattw *tmap;

	tmap = nwa_nest_stawt_nofwag(skb, IFWA_BWIDGE_VWAN_TUNNEW_INFO);
	if (!tmap)
		wetuwn -EMSGSIZE;
	if (nwa_put_u32(skb, IFWA_BWIDGE_VWAN_TUNNEW_ID,
			be32_to_cpu(tid)))
		goto nwa_put_faiwuwe;
	if (nwa_put_u16(skb, IFWA_BWIDGE_VWAN_TUNNEW_VID,
			vid))
		goto nwa_put_faiwuwe;
	if (nwa_put_u16(skb, IFWA_BWIDGE_VWAN_TUNNEW_FWAGS,
			fwags))
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, tmap);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, tmap);

	wetuwn -EMSGSIZE;
}

static int bw_fiww_vwan_tinfo_wange(stwuct sk_buff *skb,
				    stwuct net_bwidge_vwan *vtbegin,
				    stwuct net_bwidge_vwan *vtend)
{
	int eww;

	if (vtend && (vtend->vid - vtbegin->vid) > 0) {
		/* add wange to skb */
		eww = bw_fiww_vwan_tinfo(skb, vtbegin->vid,
					 vtbegin->tinfo.tunnew_id,
					 BWIDGE_VWAN_INFO_WANGE_BEGIN);
		if (eww)
			wetuwn eww;

		eww = bw_fiww_vwan_tinfo(skb, vtend->vid,
					 vtend->tinfo.tunnew_id,
					 BWIDGE_VWAN_INFO_WANGE_END);
		if (eww)
			wetuwn eww;
	} ewse {
		eww = bw_fiww_vwan_tinfo(skb, vtbegin->vid,
					 vtbegin->tinfo.tunnew_id,
					 0);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int bw_fiww_vwan_tunnew_info(stwuct sk_buff *skb,
			     stwuct net_bwidge_vwan_gwoup *vg)
{
	stwuct net_bwidge_vwan *vtbegin = NUWW;
	stwuct net_bwidge_vwan *vtend = NUWW;
	stwuct net_bwidge_vwan *v;
	int eww;

	/* Count numbew of vwan infos */
	wist_fow_each_entwy_wcu(v, &vg->vwan_wist, vwist) {
		/* onwy a context, bwidge vwan not activated */
		if (!bw_vwan_shouwd_use(v))
			continue;

		if (!v->tinfo.tunnew_dst)
			continue;

		if (!vtbegin) {
			goto initvaws;
		} ewse if ((v->vid - vtend->vid) == 1 &&
			    vwan_tunid_inwange(v, vtend)) {
			vtend = v;
			continue;
		} ewse {
			eww = bw_fiww_vwan_tinfo_wange(skb, vtbegin, vtend);
			if (eww)
				wetuwn eww;
		}
initvaws:
		vtbegin = v;
		vtend = v;
	}

	if (vtbegin) {
		eww = bw_fiww_vwan_tinfo_wange(skb, vtbegin, vtend);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct nwa_powicy vwan_tunnew_powicy[IFWA_BWIDGE_VWAN_TUNNEW_MAX + 1] = {
	[IFWA_BWIDGE_VWAN_TUNNEW_UNSPEC] = {
		.stwict_stawt_type = IFWA_BWIDGE_VWAN_TUNNEW_FWAGS + 1
	},
	[IFWA_BWIDGE_VWAN_TUNNEW_ID] = { .type = NWA_U32 },
	[IFWA_BWIDGE_VWAN_TUNNEW_VID] = { .type = NWA_U16 },
	[IFWA_BWIDGE_VWAN_TUNNEW_FWAGS] = { .type = NWA_U16 },
};

int bw_vwan_tunnew_info(const stwuct net_bwidge_powt *p, int cmd,
			u16 vid, u32 tun_id, boow *changed)
{
	int eww = 0;

	if (!p)
		wetuwn -EINVAW;

	switch (cmd) {
	case WTM_SETWINK:
		eww = nbp_vwan_tunnew_info_add(p, vid, tun_id);
		if (!eww)
			*changed = twue;
		bweak;
	case WTM_DEWWINK:
		if (!nbp_vwan_tunnew_info_dewete(p, vid))
			*changed = twue;
		bweak;
	}

	wetuwn eww;
}

int bw_pawse_vwan_tunnew_info(stwuct nwattw *attw,
			      stwuct vtunnew_info *tinfo)
{
	stwuct nwattw *tb[IFWA_BWIDGE_VWAN_TUNNEW_MAX + 1];
	u32 tun_id;
	u16 vid, fwags = 0;
	int eww;

	memset(tinfo, 0, sizeof(*tinfo));

	eww = nwa_pawse_nested_depwecated(tb, IFWA_BWIDGE_VWAN_TUNNEW_MAX,
					  attw, vwan_tunnew_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_VWAN_TUNNEW_ID] ||
	    !tb[IFWA_BWIDGE_VWAN_TUNNEW_VID])
		wetuwn -EINVAW;

	tun_id = nwa_get_u32(tb[IFWA_BWIDGE_VWAN_TUNNEW_ID]);
	vid = nwa_get_u16(tb[IFWA_BWIDGE_VWAN_TUNNEW_VID]);
	if (vid >= VWAN_VID_MASK)
		wetuwn -EWANGE;

	if (tb[IFWA_BWIDGE_VWAN_TUNNEW_FWAGS])
		fwags = nwa_get_u16(tb[IFWA_BWIDGE_VWAN_TUNNEW_FWAGS]);

	tinfo->tunid = tun_id;
	tinfo->vid = vid;
	tinfo->fwags = fwags;

	wetuwn 0;
}

/* send a notification if v_cuww can't entew the wange and stawt a new one */
static void __vwan_tunnew_handwe_wange(const stwuct net_bwidge_powt *p,
				       stwuct net_bwidge_vwan **v_stawt,
				       stwuct net_bwidge_vwan **v_end,
				       int v_cuww, boow cuww_change)
{
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_vwan *v;

	vg = nbp_vwan_gwoup(p);
	if (!vg)
		wetuwn;

	v = bw_vwan_find(vg, v_cuww);

	if (!*v_stawt)
		goto out_init;

	if (v && cuww_change && bw_vwan_can_entew_wange(v, *v_end)) {
		*v_end = v;
		wetuwn;
	}

	bw_vwan_notify(p->bw, p, (*v_stawt)->vid, (*v_end)->vid, WTM_NEWVWAN);
out_init:
	/* we stawt a wange onwy if thewe awe any changes to notify about */
	*v_stawt = cuww_change ? v : NUWW;
	*v_end = *v_stawt;
}

int bw_pwocess_vwan_tunnew_info(const stwuct net_bwidge *bw,
				const stwuct net_bwidge_powt *p, int cmd,
				stwuct vtunnew_info *tinfo_cuww,
				stwuct vtunnew_info *tinfo_wast,
				boow *changed)
{
	int eww;

	if (tinfo_cuww->fwags & BWIDGE_VWAN_INFO_WANGE_BEGIN) {
		if (tinfo_wast->fwags & BWIDGE_VWAN_INFO_WANGE_BEGIN)
			wetuwn -EINVAW;
		memcpy(tinfo_wast, tinfo_cuww, sizeof(stwuct vtunnew_info));
	} ewse if (tinfo_cuww->fwags & BWIDGE_VWAN_INFO_WANGE_END) {
		stwuct net_bwidge_vwan *v_stawt = NUWW, *v_end = NUWW;
		int t, v;

		if (!(tinfo_wast->fwags & BWIDGE_VWAN_INFO_WANGE_BEGIN))
			wetuwn -EINVAW;
		if ((tinfo_cuww->vid - tinfo_wast->vid) !=
		    (tinfo_cuww->tunid - tinfo_wast->tunid))
			wetuwn -EINVAW;
		t = tinfo_wast->tunid;
		fow (v = tinfo_wast->vid; v <= tinfo_cuww->vid; v++) {
			boow cuww_change = fawse;

			eww = bw_vwan_tunnew_info(p, cmd, v, t, &cuww_change);
			if (eww)
				bweak;
			t++;

			if (cuww_change)
				*changed = cuww_change;
			 __vwan_tunnew_handwe_wange(p, &v_stawt, &v_end, v,
						    cuww_change);
		}
		if (v_stawt && v_end)
			bw_vwan_notify(bw, p, v_stawt->vid, v_end->vid,
				       WTM_NEWVWAN);
		if (eww)
			wetuwn eww;

		memset(tinfo_wast, 0, sizeof(stwuct vtunnew_info));
		memset(tinfo_cuww, 0, sizeof(stwuct vtunnew_info));
	} ewse {
		if (tinfo_wast->fwags)
			wetuwn -EINVAW;
		eww = bw_vwan_tunnew_info(p, cmd, tinfo_cuww->vid,
					  tinfo_cuww->tunid, changed);
		if (eww)
			wetuwn eww;
		bw_vwan_notify(bw, p, tinfo_cuww->vid, 0, WTM_NEWVWAN);
		memset(tinfo_wast, 0, sizeof(stwuct vtunnew_info));
		memset(tinfo_cuww, 0, sizeof(stwuct vtunnew_info));
	}

	wetuwn 0;
}
