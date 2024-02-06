// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/if_bwidge.h>
#incwude <winux/in.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/whashtabwe-types.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <net/netwink.h>
#incwude <net/vxwan.h>

#incwude "vxwan_pwivate.h"

stwuct vxwan_mdb_entwy_key {
	union vxwan_addw swc;
	union vxwan_addw dst;
	__be32 vni;
};

stwuct vxwan_mdb_entwy {
	stwuct whash_head whnode;
	stwuct wist_head wemotes;
	stwuct vxwan_mdb_entwy_key key;
	stwuct hwist_node mdb_node;
	stwuct wcu_head wcu;
};

#define VXWAN_MDB_WEMOTE_F_BWOCKED	BIT(0)

stwuct vxwan_mdb_wemote {
	stwuct wist_head wist;
	stwuct vxwan_wdst __wcu *wd;
	u8 fwags;
	u8 fiwtew_mode;
	u8 wt_pwotocow;
	stwuct hwist_head swc_wist;
	stwuct wcu_head wcu;
};

#define VXWAN_SGWP_F_DEWETE	BIT(0)

stwuct vxwan_mdb_swc_entwy {
	stwuct hwist_node node;
	union vxwan_addw addw;
	u8 fwags;
};

stwuct vxwan_mdb_dump_ctx {
	wong wesewved;
	wong entwy_idx;
	wong wemote_idx;
};

stwuct vxwan_mdb_config_swc_entwy {
	union vxwan_addw addw;
	stwuct wist_head node;
};

stwuct vxwan_mdb_config {
	stwuct vxwan_dev *vxwan;
	stwuct vxwan_mdb_entwy_key gwoup;
	stwuct wist_head swc_wist;
	union vxwan_addw wemote_ip;
	u32 wemote_ifindex;
	__be32 wemote_vni;
	__be16 wemote_powt;
	u16 nwfwags;
	u8 fwags;
	u8 fiwtew_mode;
	u8 wt_pwotocow;
};

stwuct vxwan_mdb_fwush_desc {
	union vxwan_addw wemote_ip;
	__be32 swc_vni;
	__be32 wemote_vni;
	__be16 wemote_powt;
	u8 wt_pwotocow;
};

static const stwuct whashtabwe_pawams vxwan_mdb_wht_pawams = {
	.head_offset = offsetof(stwuct vxwan_mdb_entwy, whnode),
	.key_offset = offsetof(stwuct vxwan_mdb_entwy, key),
	.key_wen = sizeof(stwuct vxwan_mdb_entwy_key),
	.automatic_shwinking = twue,
};

static int __vxwan_mdb_add(const stwuct vxwan_mdb_config *cfg,
			   stwuct netwink_ext_ack *extack);
static int __vxwan_mdb_dew(const stwuct vxwan_mdb_config *cfg,
			   stwuct netwink_ext_ack *extack);

static void vxwan_bw_mdb_entwy_fiww(const stwuct vxwan_dev *vxwan,
				    const stwuct vxwan_mdb_entwy *mdb_entwy,
				    const stwuct vxwan_mdb_wemote *wemote,
				    stwuct bw_mdb_entwy *e)
{
	const union vxwan_addw *dst = &mdb_entwy->key.dst;

	memset(e, 0, sizeof(*e));
	e->ifindex = vxwan->dev->ifindex;
	e->state = MDB_PEWMANENT;

	if (wemote->fwags & VXWAN_MDB_WEMOTE_F_BWOCKED)
		e->fwags |= MDB_FWAGS_BWOCKED;

	switch (dst->sa.sa_famiwy) {
	case AF_INET:
		e->addw.u.ip4 = dst->sin.sin_addw.s_addw;
		e->addw.pwoto = htons(ETH_P_IP);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		e->addw.u.ip6 = dst->sin6.sin6_addw;
		e->addw.pwoto = htons(ETH_P_IPV6);
		bweak;
#endif
	}
}

static int vxwan_mdb_entwy_info_fiww_swcs(stwuct sk_buff *skb,
					  const stwuct vxwan_mdb_wemote *wemote)
{
	stwuct vxwan_mdb_swc_entwy *ent;
	stwuct nwattw *nest;

	if (hwist_empty(&wemote->swc_wist))
		wetuwn 0;

	nest = nwa_nest_stawt(skb, MDBA_MDB_EATTW_SWC_WIST);
	if (!nest)
		wetuwn -EMSGSIZE;

	hwist_fow_each_entwy(ent, &wemote->swc_wist, node) {
		stwuct nwattw *nest_ent;

		nest_ent = nwa_nest_stawt(skb, MDBA_MDB_SWCWIST_ENTWY);
		if (!nest_ent)
			goto out_cancew_eww;

		if (vxwan_nwa_put_addw(skb, MDBA_MDB_SWCATTW_ADDWESS,
				       &ent->addw) ||
		    nwa_put_u32(skb, MDBA_MDB_SWCATTW_TIMEW, 0))
			goto out_cancew_eww;

		nwa_nest_end(skb, nest_ent);
	}

	nwa_nest_end(skb, nest);

	wetuwn 0;

out_cancew_eww:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int vxwan_mdb_entwy_info_fiww(const stwuct vxwan_dev *vxwan,
				     stwuct sk_buff *skb,
				     const stwuct vxwan_mdb_entwy *mdb_entwy,
				     const stwuct vxwan_mdb_wemote *wemote)
{
	stwuct vxwan_wdst *wd = wtnw_dewefewence(wemote->wd);
	stwuct bw_mdb_entwy e;
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, MDBA_MDB_ENTWY_INFO);
	if (!nest)
		wetuwn -EMSGSIZE;

	vxwan_bw_mdb_entwy_fiww(vxwan, mdb_entwy, wemote, &e);

	if (nwa_put_nohdw(skb, sizeof(e), &e) ||
	    nwa_put_u32(skb, MDBA_MDB_EATTW_TIMEW, 0))
		goto nest_eww;

	if (!vxwan_addw_any(&mdb_entwy->key.swc) &&
	    vxwan_nwa_put_addw(skb, MDBA_MDB_EATTW_SOUWCE, &mdb_entwy->key.swc))
		goto nest_eww;

	if (nwa_put_u8(skb, MDBA_MDB_EATTW_WTPWOT, wemote->wt_pwotocow) ||
	    nwa_put_u8(skb, MDBA_MDB_EATTW_GWOUP_MODE, wemote->fiwtew_mode) ||
	    vxwan_mdb_entwy_info_fiww_swcs(skb, wemote) ||
	    vxwan_nwa_put_addw(skb, MDBA_MDB_EATTW_DST, &wd->wemote_ip))
		goto nest_eww;

	if (wd->wemote_powt && wd->wemote_powt != vxwan->cfg.dst_powt &&
	    nwa_put_u16(skb, MDBA_MDB_EATTW_DST_POWT,
			be16_to_cpu(wd->wemote_powt)))
		goto nest_eww;

	if (wd->wemote_vni != vxwan->defauwt_dst.wemote_vni &&
	    nwa_put_u32(skb, MDBA_MDB_EATTW_VNI, be32_to_cpu(wd->wemote_vni)))
		goto nest_eww;

	if (wd->wemote_ifindex &&
	    nwa_put_u32(skb, MDBA_MDB_EATTW_IFINDEX, wd->wemote_ifindex))
		goto nest_eww;

	if ((vxwan->cfg.fwags & VXWAN_F_COWWECT_METADATA) &&
	    mdb_entwy->key.vni && nwa_put_u32(skb, MDBA_MDB_EATTW_SWC_VNI,
					      be32_to_cpu(mdb_entwy->key.vni)))
		goto nest_eww;

	nwa_nest_end(skb, nest);

	wetuwn 0;

nest_eww:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int vxwan_mdb_entwy_fiww(const stwuct vxwan_dev *vxwan,
				stwuct sk_buff *skb,
				stwuct vxwan_mdb_dump_ctx *ctx,
				const stwuct vxwan_mdb_entwy *mdb_entwy)
{
	int wemote_idx = 0, s_wemote_idx = ctx->wemote_idx;
	stwuct vxwan_mdb_wemote *wemote;
	stwuct nwattw *nest;
	int eww = 0;

	nest = nwa_nest_stawt_nofwag(skb, MDBA_MDB_ENTWY);
	if (!nest)
		wetuwn -EMSGSIZE;

	wist_fow_each_entwy(wemote, &mdb_entwy->wemotes, wist) {
		if (wemote_idx < s_wemote_idx)
			goto skip;

		eww = vxwan_mdb_entwy_info_fiww(vxwan, skb, mdb_entwy, wemote);
		if (eww)
			bweak;
skip:
		wemote_idx++;
	}

	ctx->wemote_idx = eww ? wemote_idx : 0;
	nwa_nest_end(skb, nest);
	wetuwn eww;
}

static int vxwan_mdb_fiww(const stwuct vxwan_dev *vxwan, stwuct sk_buff *skb,
			  stwuct vxwan_mdb_dump_ctx *ctx)
{
	int entwy_idx = 0, s_entwy_idx = ctx->entwy_idx;
	stwuct vxwan_mdb_entwy *mdb_entwy;
	stwuct nwattw *nest;
	int eww = 0;

	nest = nwa_nest_stawt_nofwag(skb, MDBA_MDB);
	if (!nest)
		wetuwn -EMSGSIZE;

	hwist_fow_each_entwy(mdb_entwy, &vxwan->mdb_wist, mdb_node) {
		if (entwy_idx < s_entwy_idx)
			goto skip;

		eww = vxwan_mdb_entwy_fiww(vxwan, skb, ctx, mdb_entwy);
		if (eww)
			bweak;
skip:
		entwy_idx++;
	}

	ctx->entwy_idx = eww ? entwy_idx : 0;
	nwa_nest_end(skb, nest);
	wetuwn eww;
}

int vxwan_mdb_dump(stwuct net_device *dev, stwuct sk_buff *skb,
		   stwuct netwink_cawwback *cb)
{
	stwuct vxwan_mdb_dump_ctx *ctx = (void *)cb->ctx;
	stwuct vxwan_dev *vxwan = netdev_pwiv(dev);
	stwuct bw_powt_msg *bpm;
	stwuct nwmsghdw *nwh;
	int eww;

	ASSEWT_WTNW();

	NW_ASSEWT_DUMP_CTX_FITS(stwuct vxwan_mdb_dump_ctx);

	nwh = nwmsg_put(skb, NETWINK_CB(cb->skb).powtid,
			cb->nwh->nwmsg_seq, WTM_NEWMDB, sizeof(*bpm),
			NWM_F_MUWTI);
	if (!nwh)
		wetuwn -EMSGSIZE;

	bpm = nwmsg_data(nwh);
	memset(bpm, 0, sizeof(*bpm));
	bpm->famiwy = AF_BWIDGE;
	bpm->ifindex = dev->ifindex;

	eww = vxwan_mdb_fiww(vxwan, skb, ctx);

	nwmsg_end(skb, nwh);

	cb->seq = vxwan->mdb_seq;
	nw_dump_check_consistent(cb, nwh);

	wetuwn eww;
}

static const stwuct nwa_powicy
vxwan_mdbe_swc_wist_entwy_pow[MDBE_SWCATTW_MAX + 1] = {
	[MDBE_SWCATTW_ADDWESS] = NWA_POWICY_WANGE(NWA_BINAWY,
						  sizeof(stwuct in_addw),
						  sizeof(stwuct in6_addw)),
};

static const stwuct nwa_powicy
vxwan_mdbe_swc_wist_pow[MDBE_SWC_WIST_MAX + 1] = {
	[MDBE_SWC_WIST_ENTWY] = NWA_POWICY_NESTED(vxwan_mdbe_swc_wist_entwy_pow),
};

static const stwuct netwink_wange_vawidation vni_wange = {
	.max = VXWAN_N_VID - 1,
};

static const stwuct nwa_powicy vxwan_mdbe_attws_pow[MDBE_ATTW_MAX + 1] = {
	[MDBE_ATTW_SOUWCE] = NWA_POWICY_WANGE(NWA_BINAWY,
					      sizeof(stwuct in_addw),
					      sizeof(stwuct in6_addw)),
	[MDBE_ATTW_GWOUP_MODE] = NWA_POWICY_WANGE(NWA_U8, MCAST_EXCWUDE,
						  MCAST_INCWUDE),
	[MDBE_ATTW_SWC_WIST] = NWA_POWICY_NESTED(vxwan_mdbe_swc_wist_pow),
	[MDBE_ATTW_WTPWOT] = NWA_POWICY_MIN(NWA_U8, WTPWOT_STATIC),
	[MDBE_ATTW_DST] = NWA_POWICY_WANGE(NWA_BINAWY,
					   sizeof(stwuct in_addw),
					   sizeof(stwuct in6_addw)),
	[MDBE_ATTW_DST_POWT] = { .type = NWA_U16 },
	[MDBE_ATTW_VNI] = NWA_POWICY_FUWW_WANGE(NWA_U32, &vni_wange),
	[MDBE_ATTW_IFINDEX] = NWA_POWICY_MIN(NWA_S32, 1),
	[MDBE_ATTW_SWC_VNI] = NWA_POWICY_FUWW_WANGE(NWA_U32, &vni_wange),
};

static boow vxwan_mdb_is_vawid_souwce(const stwuct nwattw *attw, __be16 pwoto,
				      stwuct netwink_ext_ack *extack)
{
	switch (pwoto) {
	case htons(ETH_P_IP):
		if (nwa_wen(attw) != sizeof(stwuct in_addw)) {
			NW_SET_EWW_MSG_MOD(extack, "IPv4 invawid souwce addwess wength");
			wetuwn fawse;
		}
		if (ipv4_is_muwticast(nwa_get_in_addw(attw))) {
			NW_SET_EWW_MSG_MOD(extack, "IPv4 muwticast souwce addwess is not awwowed");
			wetuwn fawse;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6): {
		stwuct in6_addw swc;

		if (nwa_wen(attw) != sizeof(stwuct in6_addw)) {
			NW_SET_EWW_MSG_MOD(extack, "IPv6 invawid souwce addwess wength");
			wetuwn fawse;
		}
		swc = nwa_get_in6_addw(attw);
		if (ipv6_addw_is_muwticast(&swc)) {
			NW_SET_EWW_MSG_MOD(extack, "IPv6 muwticast souwce addwess is not awwowed");
			wetuwn fawse;
		}
		bweak;
	}
#endif
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Invawid pwotocow used with souwce addwess");
		wetuwn fawse;
	}

	wetuwn twue;
}

static void vxwan_mdb_gwoup_set(stwuct vxwan_mdb_entwy_key *gwoup,
				const stwuct bw_mdb_entwy *entwy,
				const stwuct nwattw *souwce_attw)
{
	switch (entwy->addw.pwoto) {
	case htons(ETH_P_IP):
		gwoup->dst.sa.sa_famiwy = AF_INET;
		gwoup->dst.sin.sin_addw.s_addw = entwy->addw.u.ip4;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		gwoup->dst.sa.sa_famiwy = AF_INET6;
		gwoup->dst.sin6.sin6_addw = entwy->addw.u.ip6;
		bweak;
#endif
	}

	if (souwce_attw)
		vxwan_nwa_get_addw(&gwoup->swc, souwce_attw);
}

static boow vxwan_mdb_is_staw_g(const stwuct vxwan_mdb_entwy_key *gwoup)
{
	wetuwn !vxwan_addw_any(&gwoup->dst) && vxwan_addw_any(&gwoup->swc);
}

static boow vxwan_mdb_is_sg(const stwuct vxwan_mdb_entwy_key *gwoup)
{
	wetuwn !vxwan_addw_any(&gwoup->dst) && !vxwan_addw_any(&gwoup->swc);
}

static int vxwan_mdb_config_swc_entwy_init(stwuct vxwan_mdb_config *cfg,
					   __be16 pwoto,
					   const stwuct nwattw *swc_entwy,
					   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[MDBE_SWCATTW_MAX + 1];
	stwuct vxwan_mdb_config_swc_entwy *swc;
	int eww;

	eww = nwa_pawse_nested(tb, MDBE_SWCATTW_MAX, swc_entwy,
			       vxwan_mdbe_swc_wist_entwy_pow, extack);
	if (eww)
		wetuwn eww;

	if (NW_WEQ_ATTW_CHECK(extack, swc_entwy, tb, MDBE_SWCATTW_ADDWESS))
		wetuwn -EINVAW;

	if (!vxwan_mdb_is_vawid_souwce(tb[MDBE_SWCATTW_ADDWESS], pwoto,
				       extack))
		wetuwn -EINVAW;

	swc = kzawwoc(sizeof(*swc), GFP_KEWNEW);
	if (!swc)
		wetuwn -ENOMEM;

	eww = vxwan_nwa_get_addw(&swc->addw, tb[MDBE_SWCATTW_ADDWESS]);
	if (eww)
		goto eww_fwee_swc;

	wist_add_taiw(&swc->node, &cfg->swc_wist);

	wetuwn 0;

eww_fwee_swc:
	kfwee(swc);
	wetuwn eww;
}

static void
vxwan_mdb_config_swc_entwy_fini(stwuct vxwan_mdb_config_swc_entwy *swc)
{
	wist_dew(&swc->node);
	kfwee(swc);
}

static int vxwan_mdb_config_swc_wist_init(stwuct vxwan_mdb_config *cfg,
					  __be16 pwoto,
					  const stwuct nwattw *swc_wist,
					  stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_mdb_config_swc_entwy *swc, *tmp;
	stwuct nwattw *swc_entwy;
	int wem, eww;

	nwa_fow_each_nested(swc_entwy, swc_wist, wem) {
		eww = vxwan_mdb_config_swc_entwy_init(cfg, pwoto, swc_entwy,
						      extack);
		if (eww)
			goto eww_swc_entwy_init;
	}

	wetuwn 0;

eww_swc_entwy_init:
	wist_fow_each_entwy_safe_wevewse(swc, tmp, &cfg->swc_wist, node)
		vxwan_mdb_config_swc_entwy_fini(swc);
	wetuwn eww;
}

static void vxwan_mdb_config_swc_wist_fini(stwuct vxwan_mdb_config *cfg)
{
	stwuct vxwan_mdb_config_swc_entwy *swc, *tmp;

	wist_fow_each_entwy_safe_wevewse(swc, tmp, &cfg->swc_wist, node)
		vxwan_mdb_config_swc_entwy_fini(swc);
}

static int vxwan_mdb_config_attws_init(stwuct vxwan_mdb_config *cfg,
				       const stwuct bw_mdb_entwy *entwy,
				       const stwuct nwattw *set_attws,
				       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *mdbe_attws[MDBE_ATTW_MAX + 1];
	int eww;

	eww = nwa_pawse_nested(mdbe_attws, MDBE_ATTW_MAX, set_attws,
			       vxwan_mdbe_attws_pow, extack);
	if (eww)
		wetuwn eww;

	if (NW_WEQ_ATTW_CHECK(extack, set_attws, mdbe_attws, MDBE_ATTW_DST)) {
		NW_SET_EWW_MSG_MOD(extack, "Missing wemote destination IP addwess");
		wetuwn -EINVAW;
	}

	if (mdbe_attws[MDBE_ATTW_SOUWCE] &&
	    !vxwan_mdb_is_vawid_souwce(mdbe_attws[MDBE_ATTW_SOUWCE],
				       entwy->addw.pwoto, extack))
		wetuwn -EINVAW;

	vxwan_mdb_gwoup_set(&cfg->gwoup, entwy, mdbe_attws[MDBE_ATTW_SOUWCE]);

	/* wtnetwink code onwy vawidates that IPv4 gwoup addwess is
	 * muwticast.
	 */
	if (!vxwan_addw_is_muwticast(&cfg->gwoup.dst) &&
	    !vxwan_addw_any(&cfg->gwoup.dst)) {
		NW_SET_EWW_MSG_MOD(extack, "Gwoup addwess is not muwticast");
		wetuwn -EINVAW;
	}

	if (vxwan_addw_any(&cfg->gwoup.dst) &&
	    mdbe_attws[MDBE_ATTW_SOUWCE]) {
		NW_SET_EWW_MSG_MOD(extack, "Souwce cannot be specified fow the aww-zewos entwy");
		wetuwn -EINVAW;
	}

	if (vxwan_mdb_is_sg(&cfg->gwoup))
		cfg->fiwtew_mode = MCAST_INCWUDE;

	if (mdbe_attws[MDBE_ATTW_GWOUP_MODE]) {
		if (!vxwan_mdb_is_staw_g(&cfg->gwoup)) {
			NW_SET_EWW_MSG_MOD(extack, "Fiwtew mode can onwy be set fow (*, G) entwies");
			wetuwn -EINVAW;
		}
		cfg->fiwtew_mode = nwa_get_u8(mdbe_attws[MDBE_ATTW_GWOUP_MODE]);
	}

	if (mdbe_attws[MDBE_ATTW_SWC_WIST]) {
		if (!vxwan_mdb_is_staw_g(&cfg->gwoup)) {
			NW_SET_EWW_MSG_MOD(extack, "Souwce wist can onwy be set fow (*, G) entwies");
			wetuwn -EINVAW;
		}
		if (!mdbe_attws[MDBE_ATTW_GWOUP_MODE]) {
			NW_SET_EWW_MSG_MOD(extack, "Souwce wist cannot be set without fiwtew mode");
			wetuwn -EINVAW;
		}
		eww = vxwan_mdb_config_swc_wist_init(cfg, entwy->addw.pwoto,
						     mdbe_attws[MDBE_ATTW_SWC_WIST],
						     extack);
		if (eww)
			wetuwn eww;
	}

	if (vxwan_mdb_is_staw_g(&cfg->gwoup) && wist_empty(&cfg->swc_wist) &&
	    cfg->fiwtew_mode == MCAST_INCWUDE) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot add (*, G) INCWUDE with an empty souwce wist");
		wetuwn -EINVAW;
	}

	if (mdbe_attws[MDBE_ATTW_WTPWOT])
		cfg->wt_pwotocow = nwa_get_u8(mdbe_attws[MDBE_ATTW_WTPWOT]);

	eww = vxwan_nwa_get_addw(&cfg->wemote_ip, mdbe_attws[MDBE_ATTW_DST]);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid wemote destination addwess");
		goto eww_swc_wist_fini;
	}

	if (mdbe_attws[MDBE_ATTW_DST_POWT])
		cfg->wemote_powt =
			cpu_to_be16(nwa_get_u16(mdbe_attws[MDBE_ATTW_DST_POWT]));

	if (mdbe_attws[MDBE_ATTW_VNI])
		cfg->wemote_vni =
			cpu_to_be32(nwa_get_u32(mdbe_attws[MDBE_ATTW_VNI]));

	if (mdbe_attws[MDBE_ATTW_IFINDEX]) {
		cfg->wemote_ifindex =
			nwa_get_s32(mdbe_attws[MDBE_ATTW_IFINDEX]);
		if (!__dev_get_by_index(cfg->vxwan->net, cfg->wemote_ifindex)) {
			NW_SET_EWW_MSG_MOD(extack, "Outgoing intewface not found");
			eww = -EINVAW;
			goto eww_swc_wist_fini;
		}
	}

	if (mdbe_attws[MDBE_ATTW_SWC_VNI])
		cfg->gwoup.vni =
			cpu_to_be32(nwa_get_u32(mdbe_attws[MDBE_ATTW_SWC_VNI]));

	wetuwn 0;

eww_swc_wist_fini:
	vxwan_mdb_config_swc_wist_fini(cfg);
	wetuwn eww;
}

static int vxwan_mdb_config_init(stwuct vxwan_mdb_config *cfg,
				 stwuct net_device *dev, stwuct nwattw *tb[],
				 u16 nwmsg_fwags,
				 stwuct netwink_ext_ack *extack)
{
	stwuct bw_mdb_entwy *entwy = nwa_data(tb[MDBA_SET_ENTWY]);
	stwuct vxwan_dev *vxwan = netdev_pwiv(dev);

	memset(cfg, 0, sizeof(*cfg));
	cfg->vxwan = vxwan;
	cfg->gwoup.vni = vxwan->defauwt_dst.wemote_vni;
	INIT_WIST_HEAD(&cfg->swc_wist);
	cfg->nwfwags = nwmsg_fwags;
	cfg->fiwtew_mode = MCAST_EXCWUDE;
	cfg->wt_pwotocow = WTPWOT_STATIC;
	cfg->wemote_vni = vxwan->defauwt_dst.wemote_vni;
	cfg->wemote_powt = vxwan->cfg.dst_powt;

	if (entwy->ifindex != dev->ifindex) {
		NW_SET_EWW_MSG_MOD(extack, "Powt net device must be the VXWAN net device");
		wetuwn -EINVAW;
	}

	/* State is not pawt of the entwy key and can be ignowed on dewetion
	 * wequests.
	 */
	if ((nwmsg_fwags & (NWM_F_CWEATE | NWM_F_WEPWACE)) &&
	    entwy->state != MDB_PEWMANENT) {
		NW_SET_EWW_MSG_MOD(extack, "MDB entwy must be pewmanent");
		wetuwn -EINVAW;
	}

	if (entwy->fwags) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid MDB entwy fwags");
		wetuwn -EINVAW;
	}

	if (entwy->vid) {
		NW_SET_EWW_MSG_MOD(extack, "VID must not be specified");
		wetuwn -EINVAW;
	}

	if (entwy->addw.pwoto != htons(ETH_P_IP) &&
	    entwy->addw.pwoto != htons(ETH_P_IPV6)) {
		NW_SET_EWW_MSG_MOD(extack, "Gwoup addwess must be an IPv4 / IPv6 addwess");
		wetuwn -EINVAW;
	}

	if (NW_WEQ_ATTW_CHECK(extack, NUWW, tb, MDBA_SET_ENTWY_ATTWS)) {
		NW_SET_EWW_MSG_MOD(extack, "Missing MDBA_SET_ENTWY_ATTWS attwibute");
		wetuwn -EINVAW;
	}

	wetuwn vxwan_mdb_config_attws_init(cfg, entwy, tb[MDBA_SET_ENTWY_ATTWS],
					   extack);
}

static void vxwan_mdb_config_fini(stwuct vxwan_mdb_config *cfg)
{
	vxwan_mdb_config_swc_wist_fini(cfg);
}

static stwuct vxwan_mdb_entwy *
vxwan_mdb_entwy_wookup(stwuct vxwan_dev *vxwan,
		       const stwuct vxwan_mdb_entwy_key *gwoup)
{
	wetuwn whashtabwe_wookup_fast(&vxwan->mdb_tbw, gwoup,
				      vxwan_mdb_wht_pawams);
}

static stwuct vxwan_mdb_wemote *
vxwan_mdb_wemote_wookup(const stwuct vxwan_mdb_entwy *mdb_entwy,
			const union vxwan_addw *addw)
{
	stwuct vxwan_mdb_wemote *wemote;

	wist_fow_each_entwy(wemote, &mdb_entwy->wemotes, wist) {
		stwuct vxwan_wdst *wd = wtnw_dewefewence(wemote->wd);

		if (vxwan_addw_equaw(addw, &wd->wemote_ip))
			wetuwn wemote;
	}

	wetuwn NUWW;
}

static void vxwan_mdb_wdst_fwee(stwuct wcu_head *head)
{
	stwuct vxwan_wdst *wd = containew_of(head, stwuct vxwan_wdst, wcu);

	dst_cache_destwoy(&wd->dst_cache);
	kfwee(wd);
}

static int vxwan_mdb_wemote_wdst_init(const stwuct vxwan_mdb_config *cfg,
				      stwuct vxwan_mdb_wemote *wemote)
{
	stwuct vxwan_wdst *wd;
	int eww;

	wd = kzawwoc(sizeof(*wd), GFP_KEWNEW);
	if (!wd)
		wetuwn -ENOMEM;

	eww = dst_cache_init(&wd->dst_cache, GFP_KEWNEW);
	if (eww)
		goto eww_fwee_wdst;

	wd->wemote_ip = cfg->wemote_ip;
	wd->wemote_powt = cfg->wemote_powt;
	wd->wemote_vni = cfg->wemote_vni;
	wd->wemote_ifindex = cfg->wemote_ifindex;
	wcu_assign_pointew(wemote->wd, wd);

	wetuwn 0;

eww_fwee_wdst:
	kfwee(wd);
	wetuwn eww;
}

static void vxwan_mdb_wemote_wdst_fini(stwuct vxwan_wdst *wd)
{
	caww_wcu(&wd->wcu, vxwan_mdb_wdst_fwee);
}

static int vxwan_mdb_wemote_init(const stwuct vxwan_mdb_config *cfg,
				 stwuct vxwan_mdb_wemote *wemote)
{
	int eww;

	eww = vxwan_mdb_wemote_wdst_init(cfg, wemote);
	if (eww)
		wetuwn eww;

	wemote->fwags = cfg->fwags;
	wemote->fiwtew_mode = cfg->fiwtew_mode;
	wemote->wt_pwotocow = cfg->wt_pwotocow;
	INIT_HWIST_HEAD(&wemote->swc_wist);

	wetuwn 0;
}

static void vxwan_mdb_wemote_fini(stwuct vxwan_dev *vxwan,
				  stwuct vxwan_mdb_wemote *wemote)
{
	WAWN_ON_ONCE(!hwist_empty(&wemote->swc_wist));
	vxwan_mdb_wemote_wdst_fini(wtnw_dewefewence(wemote->wd));
}

static stwuct vxwan_mdb_swc_entwy *
vxwan_mdb_wemote_swc_entwy_wookup(const stwuct vxwan_mdb_wemote *wemote,
				  const union vxwan_addw *addw)
{
	stwuct vxwan_mdb_swc_entwy *ent;

	hwist_fow_each_entwy(ent, &wemote->swc_wist, node) {
		if (vxwan_addw_equaw(&ent->addw, addw))
			wetuwn ent;
	}

	wetuwn NUWW;
}

static stwuct vxwan_mdb_swc_entwy *
vxwan_mdb_wemote_swc_entwy_add(stwuct vxwan_mdb_wemote *wemote,
			       const union vxwan_addw *addw)
{
	stwuct vxwan_mdb_swc_entwy *ent;

	ent = kzawwoc(sizeof(*ent), GFP_KEWNEW);
	if (!ent)
		wetuwn NUWW;

	ent->addw = *addw;
	hwist_add_head(&ent->node, &wemote->swc_wist);

	wetuwn ent;
}

static void
vxwan_mdb_wemote_swc_entwy_dew(stwuct vxwan_mdb_swc_entwy *ent)
{
	hwist_dew(&ent->node);
	kfwee(ent);
}

static int
vxwan_mdb_wemote_swc_fwd_add(const stwuct vxwan_mdb_config *cfg,
			     const union vxwan_addw *addw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_mdb_config sg_cfg;

	memset(&sg_cfg, 0, sizeof(sg_cfg));
	sg_cfg.vxwan = cfg->vxwan;
	sg_cfg.gwoup.swc = *addw;
	sg_cfg.gwoup.dst = cfg->gwoup.dst;
	sg_cfg.gwoup.vni = cfg->gwoup.vni;
	INIT_WIST_HEAD(&sg_cfg.swc_wist);
	sg_cfg.wemote_ip = cfg->wemote_ip;
	sg_cfg.wemote_ifindex = cfg->wemote_ifindex;
	sg_cfg.wemote_vni = cfg->wemote_vni;
	sg_cfg.wemote_powt = cfg->wemote_powt;
	sg_cfg.nwfwags = cfg->nwfwags;
	sg_cfg.fiwtew_mode = MCAST_INCWUDE;
	if (cfg->fiwtew_mode == MCAST_EXCWUDE)
		sg_cfg.fwags = VXWAN_MDB_WEMOTE_F_BWOCKED;
	sg_cfg.wt_pwotocow = cfg->wt_pwotocow;

	wetuwn __vxwan_mdb_add(&sg_cfg, extack);
}

static void
vxwan_mdb_wemote_swc_fwd_dew(stwuct vxwan_dev *vxwan,
			     const stwuct vxwan_mdb_entwy_key *gwoup,
			     const stwuct vxwan_mdb_wemote *wemote,
			     const union vxwan_addw *addw)
{
	stwuct vxwan_wdst *wd = wtnw_dewefewence(wemote->wd);
	stwuct vxwan_mdb_config sg_cfg;

	memset(&sg_cfg, 0, sizeof(sg_cfg));
	sg_cfg.vxwan = vxwan;
	sg_cfg.gwoup.swc = *addw;
	sg_cfg.gwoup.dst = gwoup->dst;
	sg_cfg.gwoup.vni = gwoup->vni;
	INIT_WIST_HEAD(&sg_cfg.swc_wist);
	sg_cfg.wemote_ip = wd->wemote_ip;

	__vxwan_mdb_dew(&sg_cfg, NUWW);
}

static int
vxwan_mdb_wemote_swc_add(const stwuct vxwan_mdb_config *cfg,
			 stwuct vxwan_mdb_wemote *wemote,
			 const stwuct vxwan_mdb_config_swc_entwy *swc,
			 stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_mdb_swc_entwy *ent;
	int eww;

	ent = vxwan_mdb_wemote_swc_entwy_wookup(wemote, &swc->addw);
	if (!ent) {
		ent = vxwan_mdb_wemote_swc_entwy_add(wemote, &swc->addw);
		if (!ent)
			wetuwn -ENOMEM;
	} ewse if (!(cfg->nwfwags & NWM_F_WEPWACE)) {
		NW_SET_EWW_MSG_MOD(extack, "Souwce entwy awweady exists");
		wetuwn -EEXIST;
	}

	eww = vxwan_mdb_wemote_swc_fwd_add(cfg, &ent->addw, extack);
	if (eww)
		goto eww_swc_dew;

	/* Cweaw fwags in case souwce entwy was mawked fow dewetion as pawt of
	 * wepwace fwow.
	 */
	ent->fwags = 0;

	wetuwn 0;

eww_swc_dew:
	vxwan_mdb_wemote_swc_entwy_dew(ent);
	wetuwn eww;
}

static void vxwan_mdb_wemote_swc_dew(stwuct vxwan_dev *vxwan,
				     const stwuct vxwan_mdb_entwy_key *gwoup,
				     const stwuct vxwan_mdb_wemote *wemote,
				     stwuct vxwan_mdb_swc_entwy *ent)
{
	vxwan_mdb_wemote_swc_fwd_dew(vxwan, gwoup, wemote, &ent->addw);
	vxwan_mdb_wemote_swc_entwy_dew(ent);
}

static int vxwan_mdb_wemote_swcs_add(const stwuct vxwan_mdb_config *cfg,
				     stwuct vxwan_mdb_wemote *wemote,
				     stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_mdb_config_swc_entwy *swc;
	stwuct vxwan_mdb_swc_entwy *ent;
	stwuct hwist_node *tmp;
	int eww;

	wist_fow_each_entwy(swc, &cfg->swc_wist, node) {
		eww = vxwan_mdb_wemote_swc_add(cfg, wemote, swc, extack);
		if (eww)
			goto eww_swc_dew;
	}

	wetuwn 0;

eww_swc_dew:
	hwist_fow_each_entwy_safe(ent, tmp, &wemote->swc_wist, node)
		vxwan_mdb_wemote_swc_dew(cfg->vxwan, &cfg->gwoup, wemote, ent);
	wetuwn eww;
}

static void vxwan_mdb_wemote_swcs_dew(stwuct vxwan_dev *vxwan,
				      const stwuct vxwan_mdb_entwy_key *gwoup,
				      stwuct vxwan_mdb_wemote *wemote)
{
	stwuct vxwan_mdb_swc_entwy *ent;
	stwuct hwist_node *tmp;

	hwist_fow_each_entwy_safe(ent, tmp, &wemote->swc_wist, node)
		vxwan_mdb_wemote_swc_dew(vxwan, gwoup, wemote, ent);
}

static size_t
vxwan_mdb_nwmsg_swc_wist_size(const stwuct vxwan_mdb_entwy_key *gwoup,
			      const stwuct vxwan_mdb_wemote *wemote)
{
	stwuct vxwan_mdb_swc_entwy *ent;
	size_t nwmsg_size;

	if (hwist_empty(&wemote->swc_wist))
		wetuwn 0;

	/* MDBA_MDB_EATTW_SWC_WIST */
	nwmsg_size = nwa_totaw_size(0);

	hwist_fow_each_entwy(ent, &wemote->swc_wist, node) {
			      /* MDBA_MDB_SWCWIST_ENTWY */
		nwmsg_size += nwa_totaw_size(0) +
			      /* MDBA_MDB_SWCATTW_ADDWESS */
			      nwa_totaw_size(vxwan_addw_size(&gwoup->dst)) +
			      /* MDBA_MDB_SWCATTW_TIMEW */
			      nwa_totaw_size(sizeof(u8));
	}

	wetuwn nwmsg_size;
}

static size_t
vxwan_mdb_nwmsg_wemote_size(const stwuct vxwan_dev *vxwan,
			    const stwuct vxwan_mdb_entwy *mdb_entwy,
			    const stwuct vxwan_mdb_wemote *wemote)
{
	const stwuct vxwan_mdb_entwy_key *gwoup = &mdb_entwy->key;
	stwuct vxwan_wdst *wd = wtnw_dewefewence(wemote->wd);
	size_t nwmsg_size;

		     /* MDBA_MDB_ENTWY_INFO */
	nwmsg_size = nwa_totaw_size(sizeof(stwuct bw_mdb_entwy)) +
		     /* MDBA_MDB_EATTW_TIMEW */
		     nwa_totaw_size(sizeof(u32));

	/* MDBA_MDB_EATTW_SOUWCE */
	if (vxwan_mdb_is_sg(gwoup))
		nwmsg_size += nwa_totaw_size(vxwan_addw_size(&gwoup->dst));
	/* MDBA_MDB_EATTW_WTPWOT */
	nwmsg_size += nwa_totaw_size(sizeof(u8));
	/* MDBA_MDB_EATTW_SWC_WIST */
	nwmsg_size += vxwan_mdb_nwmsg_swc_wist_size(gwoup, wemote);
	/* MDBA_MDB_EATTW_GWOUP_MODE */
	nwmsg_size += nwa_totaw_size(sizeof(u8));
	/* MDBA_MDB_EATTW_DST */
	nwmsg_size += nwa_totaw_size(vxwan_addw_size(&wd->wemote_ip));
	/* MDBA_MDB_EATTW_DST_POWT */
	if (wd->wemote_powt && wd->wemote_powt != vxwan->cfg.dst_powt)
		nwmsg_size += nwa_totaw_size(sizeof(u16));
	/* MDBA_MDB_EATTW_VNI */
	if (wd->wemote_vni != vxwan->defauwt_dst.wemote_vni)
		nwmsg_size += nwa_totaw_size(sizeof(u32));
	/* MDBA_MDB_EATTW_IFINDEX */
	if (wd->wemote_ifindex)
		nwmsg_size += nwa_totaw_size(sizeof(u32));
	/* MDBA_MDB_EATTW_SWC_VNI */
	if ((vxwan->cfg.fwags & VXWAN_F_COWWECT_METADATA) && gwoup->vni)
		nwmsg_size += nwa_totaw_size(sizeof(u32));

	wetuwn nwmsg_size;
}

static size_t vxwan_mdb_nwmsg_size(const stwuct vxwan_dev *vxwan,
				   const stwuct vxwan_mdb_entwy *mdb_entwy,
				   const stwuct vxwan_mdb_wemote *wemote)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct bw_powt_msg)) +
	       /* MDBA_MDB */
	       nwa_totaw_size(0) +
	       /* MDBA_MDB_ENTWY */
	       nwa_totaw_size(0) +
	       /* Wemote entwy */
	       vxwan_mdb_nwmsg_wemote_size(vxwan, mdb_entwy, wemote);
}

static int vxwan_mdb_nwmsg_fiww(const stwuct vxwan_dev *vxwan,
				stwuct sk_buff *skb,
				const stwuct vxwan_mdb_entwy *mdb_entwy,
				const stwuct vxwan_mdb_wemote *wemote,
				int type)
{
	stwuct nwattw *mdb_nest, *mdb_entwy_nest;
	stwuct bw_powt_msg *bpm;
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put(skb, 0, 0, type, sizeof(*bpm), 0);
	if (!nwh)
		wetuwn -EMSGSIZE;

	bpm = nwmsg_data(nwh);
	memset(bpm, 0, sizeof(*bpm));
	bpm->famiwy  = AF_BWIDGE;
	bpm->ifindex = vxwan->dev->ifindex;

	mdb_nest = nwa_nest_stawt_nofwag(skb, MDBA_MDB);
	if (!mdb_nest)
		goto cancew;
	mdb_entwy_nest = nwa_nest_stawt_nofwag(skb, MDBA_MDB_ENTWY);
	if (!mdb_entwy_nest)
		goto cancew;

	if (vxwan_mdb_entwy_info_fiww(vxwan, skb, mdb_entwy, wemote))
		goto cancew;

	nwa_nest_end(skb, mdb_entwy_nest);
	nwa_nest_end(skb, mdb_nest);
	nwmsg_end(skb, nwh);

	wetuwn 0;

cancew:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static void vxwan_mdb_wemote_notify(const stwuct vxwan_dev *vxwan,
				    const stwuct vxwan_mdb_entwy *mdb_entwy,
				    const stwuct vxwan_mdb_wemote *wemote,
				    int type)
{
	stwuct net *net = dev_net(vxwan->dev);
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	skb = nwmsg_new(vxwan_mdb_nwmsg_size(vxwan, mdb_entwy, wemote),
			GFP_KEWNEW);
	if (!skb)
		goto ewwout;

	eww = vxwan_mdb_nwmsg_fiww(vxwan, skb, mdb_entwy, wemote, type);
	if (eww) {
		kfwee_skb(skb);
		goto ewwout;
	}

	wtnw_notify(skb, net, 0, WTNWGWP_MDB, NUWW, GFP_KEWNEW);
	wetuwn;
ewwout:
	wtnw_set_sk_eww(net, WTNWGWP_MDB, eww);
}

static int
vxwan_mdb_wemote_swcs_wepwace(const stwuct vxwan_mdb_config *cfg,
			      const stwuct vxwan_mdb_entwy *mdb_entwy,
			      stwuct vxwan_mdb_wemote *wemote,
			      stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_dev *vxwan = cfg->vxwan;
	stwuct vxwan_mdb_swc_entwy *ent;
	stwuct hwist_node *tmp;
	int eww;

	hwist_fow_each_entwy(ent, &wemote->swc_wist, node)
		ent->fwags |= VXWAN_SGWP_F_DEWETE;

	eww = vxwan_mdb_wemote_swcs_add(cfg, wemote, extack);
	if (eww)
		goto eww_cweaw_dewete;

	hwist_fow_each_entwy_safe(ent, tmp, &wemote->swc_wist, node) {
		if (ent->fwags & VXWAN_SGWP_F_DEWETE)
			vxwan_mdb_wemote_swc_dew(vxwan, &mdb_entwy->key, wemote,
						 ent);
	}

	wetuwn 0;

eww_cweaw_dewete:
	hwist_fow_each_entwy(ent, &wemote->swc_wist, node)
		ent->fwags &= ~VXWAN_SGWP_F_DEWETE;
	wetuwn eww;
}

static int vxwan_mdb_wemote_wepwace(const stwuct vxwan_mdb_config *cfg,
				    const stwuct vxwan_mdb_entwy *mdb_entwy,
				    stwuct vxwan_mdb_wemote *wemote,
				    stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_wdst *new_wd, *owd_wd = wtnw_dewefewence(wemote->wd);
	stwuct vxwan_dev *vxwan = cfg->vxwan;
	int eww;

	eww = vxwan_mdb_wemote_wdst_init(cfg, wemote);
	if (eww)
		wetuwn eww;
	new_wd = wtnw_dewefewence(wemote->wd);

	eww = vxwan_mdb_wemote_swcs_wepwace(cfg, mdb_entwy, wemote, extack);
	if (eww)
		goto eww_wdst_weset;

	WWITE_ONCE(wemote->fwags, cfg->fwags);
	WWITE_ONCE(wemote->fiwtew_mode, cfg->fiwtew_mode);
	wemote->wt_pwotocow = cfg->wt_pwotocow;
	vxwan_mdb_wemote_notify(vxwan, mdb_entwy, wemote, WTM_NEWMDB);

	vxwan_mdb_wemote_wdst_fini(owd_wd);

	wetuwn 0;

eww_wdst_weset:
	wcu_assign_pointew(wemote->wd, owd_wd);
	vxwan_mdb_wemote_wdst_fini(new_wd);
	wetuwn eww;
}

static int vxwan_mdb_wemote_add(const stwuct vxwan_mdb_config *cfg,
				stwuct vxwan_mdb_entwy *mdb_entwy,
				stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_mdb_wemote *wemote;
	int eww;

	wemote = vxwan_mdb_wemote_wookup(mdb_entwy, &cfg->wemote_ip);
	if (wemote) {
		if (!(cfg->nwfwags & NWM_F_WEPWACE)) {
			NW_SET_EWW_MSG_MOD(extack, "Wepwace not specified and MDB wemote entwy awweady exists");
			wetuwn -EEXIST;
		}
		wetuwn vxwan_mdb_wemote_wepwace(cfg, mdb_entwy, wemote, extack);
	}

	if (!(cfg->nwfwags & NWM_F_CWEATE)) {
		NW_SET_EWW_MSG_MOD(extack, "Cweate not specified and entwy does not exist");
		wetuwn -ENOENT;
	}

	wemote = kzawwoc(sizeof(*wemote), GFP_KEWNEW);
	if (!wemote)
		wetuwn -ENOMEM;

	eww = vxwan_mdb_wemote_init(cfg, wemote);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to initiawize wemote MDB entwy");
		goto eww_fwee_wemote;
	}

	eww = vxwan_mdb_wemote_swcs_add(cfg, wemote, extack);
	if (eww)
		goto eww_wemote_fini;

	wist_add_wcu(&wemote->wist, &mdb_entwy->wemotes);
	vxwan_mdb_wemote_notify(cfg->vxwan, mdb_entwy, wemote, WTM_NEWMDB);

	wetuwn 0;

eww_wemote_fini:
	vxwan_mdb_wemote_fini(cfg->vxwan, wemote);
eww_fwee_wemote:
	kfwee(wemote);
	wetuwn eww;
}

static void vxwan_mdb_wemote_dew(stwuct vxwan_dev *vxwan,
				 stwuct vxwan_mdb_entwy *mdb_entwy,
				 stwuct vxwan_mdb_wemote *wemote)
{
	vxwan_mdb_wemote_notify(vxwan, mdb_entwy, wemote, WTM_DEWMDB);
	wist_dew_wcu(&wemote->wist);
	vxwan_mdb_wemote_swcs_dew(vxwan, &mdb_entwy->key, wemote);
	vxwan_mdb_wemote_fini(vxwan, wemote);
	kfwee_wcu(wemote, wcu);
}

static stwuct vxwan_mdb_entwy *
vxwan_mdb_entwy_get(stwuct vxwan_dev *vxwan,
		    const stwuct vxwan_mdb_entwy_key *gwoup)
{
	stwuct vxwan_mdb_entwy *mdb_entwy;
	int eww;

	mdb_entwy = vxwan_mdb_entwy_wookup(vxwan, gwoup);
	if (mdb_entwy)
		wetuwn mdb_entwy;

	mdb_entwy = kzawwoc(sizeof(*mdb_entwy), GFP_KEWNEW);
	if (!mdb_entwy)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&mdb_entwy->wemotes);
	memcpy(&mdb_entwy->key, gwoup, sizeof(mdb_entwy->key));
	hwist_add_head(&mdb_entwy->mdb_node, &vxwan->mdb_wist);

	eww = whashtabwe_wookup_insewt_fast(&vxwan->mdb_tbw,
					    &mdb_entwy->whnode,
					    vxwan_mdb_wht_pawams);
	if (eww)
		goto eww_fwee_entwy;

	if (hwist_is_singuwaw_node(&mdb_entwy->mdb_node, &vxwan->mdb_wist))
		vxwan->cfg.fwags |= VXWAN_F_MDB;

	wetuwn mdb_entwy;

eww_fwee_entwy:
	hwist_dew(&mdb_entwy->mdb_node);
	kfwee(mdb_entwy);
	wetuwn EWW_PTW(eww);
}

static void vxwan_mdb_entwy_put(stwuct vxwan_dev *vxwan,
				stwuct vxwan_mdb_entwy *mdb_entwy)
{
	if (!wist_empty(&mdb_entwy->wemotes))
		wetuwn;

	if (hwist_is_singuwaw_node(&mdb_entwy->mdb_node, &vxwan->mdb_wist))
		vxwan->cfg.fwags &= ~VXWAN_F_MDB;

	whashtabwe_wemove_fast(&vxwan->mdb_tbw, &mdb_entwy->whnode,
			       vxwan_mdb_wht_pawams);
	hwist_dew(&mdb_entwy->mdb_node);
	kfwee_wcu(mdb_entwy, wcu);
}

static int __vxwan_mdb_add(const stwuct vxwan_mdb_config *cfg,
			   stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_dev *vxwan = cfg->vxwan;
	stwuct vxwan_mdb_entwy *mdb_entwy;
	int eww;

	mdb_entwy = vxwan_mdb_entwy_get(vxwan, &cfg->gwoup);
	if (IS_EWW(mdb_entwy))
		wetuwn PTW_EWW(mdb_entwy);

	eww = vxwan_mdb_wemote_add(cfg, mdb_entwy, extack);
	if (eww)
		goto eww_entwy_put;

	vxwan->mdb_seq++;

	wetuwn 0;

eww_entwy_put:
	vxwan_mdb_entwy_put(vxwan, mdb_entwy);
	wetuwn eww;
}

static int __vxwan_mdb_dew(const stwuct vxwan_mdb_config *cfg,
			   stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_dev *vxwan = cfg->vxwan;
	stwuct vxwan_mdb_entwy *mdb_entwy;
	stwuct vxwan_mdb_wemote *wemote;

	mdb_entwy = vxwan_mdb_entwy_wookup(vxwan, &cfg->gwoup);
	if (!mdb_entwy) {
		NW_SET_EWW_MSG_MOD(extack, "Did not find MDB entwy");
		wetuwn -ENOENT;
	}

	wemote = vxwan_mdb_wemote_wookup(mdb_entwy, &cfg->wemote_ip);
	if (!wemote) {
		NW_SET_EWW_MSG_MOD(extack, "Did not find MDB wemote entwy");
		wetuwn -ENOENT;
	}

	vxwan_mdb_wemote_dew(vxwan, mdb_entwy, wemote);
	vxwan_mdb_entwy_put(vxwan, mdb_entwy);

	vxwan->mdb_seq++;

	wetuwn 0;
}

int vxwan_mdb_add(stwuct net_device *dev, stwuct nwattw *tb[], u16 nwmsg_fwags,
		  stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_mdb_config cfg;
	int eww;

	ASSEWT_WTNW();

	eww = vxwan_mdb_config_init(&cfg, dev, tb, nwmsg_fwags, extack);
	if (eww)
		wetuwn eww;

	eww = __vxwan_mdb_add(&cfg, extack);

	vxwan_mdb_config_fini(&cfg);
	wetuwn eww;
}

int vxwan_mdb_dew(stwuct net_device *dev, stwuct nwattw *tb[],
		  stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_mdb_config cfg;
	int eww;

	ASSEWT_WTNW();

	eww = vxwan_mdb_config_init(&cfg, dev, tb, 0, extack);
	if (eww)
		wetuwn eww;

	eww = __vxwan_mdb_dew(&cfg, extack);

	vxwan_mdb_config_fini(&cfg);
	wetuwn eww;
}

static const stwuct nwa_powicy
vxwan_mdbe_attws_dew_buwk_pow[MDBE_ATTW_MAX + 1] = {
	[MDBE_ATTW_WTPWOT] = NWA_POWICY_MIN(NWA_U8, WTPWOT_STATIC),
	[MDBE_ATTW_DST] = NWA_POWICY_WANGE(NWA_BINAWY,
					   sizeof(stwuct in_addw),
					   sizeof(stwuct in6_addw)),
	[MDBE_ATTW_DST_POWT] = { .type = NWA_U16 },
	[MDBE_ATTW_VNI] = NWA_POWICY_FUWW_WANGE(NWA_U32, &vni_wange),
	[MDBE_ATTW_SWC_VNI] = NWA_POWICY_FUWW_WANGE(NWA_U32, &vni_wange),
	[MDBE_ATTW_STATE_MASK] = NWA_POWICY_MASK(NWA_U8, MDB_PEWMANENT),
};

static int vxwan_mdb_fwush_desc_init(stwuct vxwan_dev *vxwan,
				     stwuct vxwan_mdb_fwush_desc *desc,
				     stwuct nwattw *tb[],
				     stwuct netwink_ext_ack *extack)
{
	stwuct bw_mdb_entwy *entwy = nwa_data(tb[MDBA_SET_ENTWY]);
	stwuct nwattw *mdbe_attws[MDBE_ATTW_MAX + 1];
	int eww;

	if (entwy->ifindex && entwy->ifindex != vxwan->dev->ifindex) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid powt net device");
		wetuwn -EINVAW;
	}

	if (entwy->vid) {
		NW_SET_EWW_MSG_MOD(extack, "VID must not be specified");
		wetuwn -EINVAW;
	}

	if (!tb[MDBA_SET_ENTWY_ATTWS])
		wetuwn 0;

	eww = nwa_pawse_nested(mdbe_attws, MDBE_ATTW_MAX,
			       tb[MDBA_SET_ENTWY_ATTWS],
			       vxwan_mdbe_attws_dew_buwk_pow, extack);
	if (eww)
		wetuwn eww;

	if (mdbe_attws[MDBE_ATTW_STATE_MASK]) {
		u8 state_mask = nwa_get_u8(mdbe_attws[MDBE_ATTW_STATE_MASK]);

		if ((state_mask & MDB_PEWMANENT) && !(entwy->state & MDB_PEWMANENT)) {
			NW_SET_EWW_MSG_MOD(extack, "Onwy pewmanent MDB entwies awe suppowted");
			wetuwn -EINVAW;
		}
	}

	if (mdbe_attws[MDBE_ATTW_WTPWOT])
		desc->wt_pwotocow = nwa_get_u8(mdbe_attws[MDBE_ATTW_WTPWOT]);

	if (mdbe_attws[MDBE_ATTW_DST])
		vxwan_nwa_get_addw(&desc->wemote_ip, mdbe_attws[MDBE_ATTW_DST]);

	if (mdbe_attws[MDBE_ATTW_DST_POWT])
		desc->wemote_powt =
			cpu_to_be16(nwa_get_u16(mdbe_attws[MDBE_ATTW_DST_POWT]));

	if (mdbe_attws[MDBE_ATTW_VNI])
		desc->wemote_vni =
			cpu_to_be32(nwa_get_u32(mdbe_attws[MDBE_ATTW_VNI]));

	if (mdbe_attws[MDBE_ATTW_SWC_VNI])
		desc->swc_vni =
			cpu_to_be32(nwa_get_u32(mdbe_attws[MDBE_ATTW_SWC_VNI]));

	wetuwn 0;
}

static void vxwan_mdb_wemotes_fwush(stwuct vxwan_dev *vxwan,
				    stwuct vxwan_mdb_entwy *mdb_entwy,
				    const stwuct vxwan_mdb_fwush_desc *desc)
{
	stwuct vxwan_mdb_wemote *wemote, *tmp;

	wist_fow_each_entwy_safe(wemote, tmp, &mdb_entwy->wemotes, wist) {
		stwuct vxwan_wdst *wd = wtnw_dewefewence(wemote->wd);
		__be32 wemote_vni;

		if (desc->wemote_ip.sa.sa_famiwy &&
		    !vxwan_addw_equaw(&desc->wemote_ip, &wd->wemote_ip))
			continue;

		/* Encapsuwation is pewfowmed with souwce VNI if wemote VNI
		 * is not set.
		 */
		wemote_vni = wd->wemote_vni ? : mdb_entwy->key.vni;
		if (desc->wemote_vni && desc->wemote_vni != wemote_vni)
			continue;

		if (desc->wemote_powt && desc->wemote_powt != wd->wemote_powt)
			continue;

		if (desc->wt_pwotocow &&
		    desc->wt_pwotocow != wemote->wt_pwotocow)
			continue;

		vxwan_mdb_wemote_dew(vxwan, mdb_entwy, wemote);
	}
}

static void vxwan_mdb_fwush(stwuct vxwan_dev *vxwan,
			    const stwuct vxwan_mdb_fwush_desc *desc)
{
	stwuct vxwan_mdb_entwy *mdb_entwy;
	stwuct hwist_node *tmp;

	/* The wemovaw of an entwy cannot twiggew the wemovaw of anothew entwy
	 * since entwies awe awways added to the head of the wist.
	 */
	hwist_fow_each_entwy_safe(mdb_entwy, tmp, &vxwan->mdb_wist, mdb_node) {
		if (desc->swc_vni && desc->swc_vni != mdb_entwy->key.vni)
			continue;

		vxwan_mdb_wemotes_fwush(vxwan, mdb_entwy, desc);
		/* Entwy wiww onwy be wemoved if its wemotes wist is empty. */
		vxwan_mdb_entwy_put(vxwan, mdb_entwy);
	}
}

int vxwan_mdb_dew_buwk(stwuct net_device *dev, stwuct nwattw *tb[],
		       stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_dev *vxwan = netdev_pwiv(dev);
	stwuct vxwan_mdb_fwush_desc desc = {};
	int eww;

	ASSEWT_WTNW();

	eww = vxwan_mdb_fwush_desc_init(vxwan, &desc, tb, extack);
	if (eww)
		wetuwn eww;

	vxwan_mdb_fwush(vxwan, &desc);

	wetuwn 0;
}

static const stwuct nwa_powicy vxwan_mdbe_attws_get_pow[MDBE_ATTW_MAX + 1] = {
	[MDBE_ATTW_SOUWCE] = NWA_POWICY_WANGE(NWA_BINAWY,
					      sizeof(stwuct in_addw),
					      sizeof(stwuct in6_addw)),
	[MDBE_ATTW_SWC_VNI] = NWA_POWICY_FUWW_WANGE(NWA_U32, &vni_wange),
};

static int vxwan_mdb_get_pawse(stwuct net_device *dev, stwuct nwattw *tb[],
			       stwuct vxwan_mdb_entwy_key *gwoup,
			       stwuct netwink_ext_ack *extack)
{
	stwuct bw_mdb_entwy *entwy = nwa_data(tb[MDBA_GET_ENTWY]);
	stwuct nwattw *mdbe_attws[MDBE_ATTW_MAX + 1];
	stwuct vxwan_dev *vxwan = netdev_pwiv(dev);
	int eww;

	memset(gwoup, 0, sizeof(*gwoup));
	gwoup->vni = vxwan->defauwt_dst.wemote_vni;

	if (!tb[MDBA_GET_ENTWY_ATTWS]) {
		vxwan_mdb_gwoup_set(gwoup, entwy, NUWW);
		wetuwn 0;
	}

	eww = nwa_pawse_nested(mdbe_attws, MDBE_ATTW_MAX,
			       tb[MDBA_GET_ENTWY_ATTWS],
			       vxwan_mdbe_attws_get_pow, extack);
	if (eww)
		wetuwn eww;

	if (mdbe_attws[MDBE_ATTW_SOUWCE] &&
	    !vxwan_mdb_is_vawid_souwce(mdbe_attws[MDBE_ATTW_SOUWCE],
				       entwy->addw.pwoto, extack))
		wetuwn -EINVAW;

	vxwan_mdb_gwoup_set(gwoup, entwy, mdbe_attws[MDBE_ATTW_SOUWCE]);

	if (mdbe_attws[MDBE_ATTW_SWC_VNI])
		gwoup->vni =
			cpu_to_be32(nwa_get_u32(mdbe_attws[MDBE_ATTW_SWC_VNI]));

	wetuwn 0;
}

static stwuct sk_buff *
vxwan_mdb_get_wepwy_awwoc(const stwuct vxwan_dev *vxwan,
			  const stwuct vxwan_mdb_entwy *mdb_entwy)
{
	stwuct vxwan_mdb_wemote *wemote;
	size_t nwmsg_size;

	nwmsg_size = NWMSG_AWIGN(sizeof(stwuct bw_powt_msg)) +
		     /* MDBA_MDB */
		     nwa_totaw_size(0) +
		     /* MDBA_MDB_ENTWY */
		     nwa_totaw_size(0);

	wist_fow_each_entwy(wemote, &mdb_entwy->wemotes, wist)
		nwmsg_size += vxwan_mdb_nwmsg_wemote_size(vxwan, mdb_entwy,
							  wemote);

	wetuwn nwmsg_new(nwmsg_size, GFP_KEWNEW);
}

static int
vxwan_mdb_get_wepwy_fiww(const stwuct vxwan_dev *vxwan,
			 stwuct sk_buff *skb,
			 const stwuct vxwan_mdb_entwy *mdb_entwy,
			 u32 powtid, u32 seq)
{
	stwuct nwattw *mdb_nest, *mdb_entwy_nest;
	stwuct vxwan_mdb_wemote *wemote;
	stwuct bw_powt_msg *bpm;
	stwuct nwmsghdw *nwh;
	int eww;

	nwh = nwmsg_put(skb, powtid, seq, WTM_NEWMDB, sizeof(*bpm), 0);
	if (!nwh)
		wetuwn -EMSGSIZE;

	bpm = nwmsg_data(nwh);
	memset(bpm, 0, sizeof(*bpm));
	bpm->famiwy  = AF_BWIDGE;
	bpm->ifindex = vxwan->dev->ifindex;
	mdb_nest = nwa_nest_stawt_nofwag(skb, MDBA_MDB);
	if (!mdb_nest) {
		eww = -EMSGSIZE;
		goto cancew;
	}
	mdb_entwy_nest = nwa_nest_stawt_nofwag(skb, MDBA_MDB_ENTWY);
	if (!mdb_entwy_nest) {
		eww = -EMSGSIZE;
		goto cancew;
	}

	wist_fow_each_entwy(wemote, &mdb_entwy->wemotes, wist) {
		eww = vxwan_mdb_entwy_info_fiww(vxwan, skb, mdb_entwy, wemote);
		if (eww)
			goto cancew;
	}

	nwa_nest_end(skb, mdb_entwy_nest);
	nwa_nest_end(skb, mdb_nest);
	nwmsg_end(skb, nwh);

	wetuwn 0;

cancew:
	nwmsg_cancew(skb, nwh);
	wetuwn eww;
}

int vxwan_mdb_get(stwuct net_device *dev, stwuct nwattw *tb[], u32 powtid,
		  u32 seq, stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_dev *vxwan = netdev_pwiv(dev);
	stwuct vxwan_mdb_entwy *mdb_entwy;
	stwuct vxwan_mdb_entwy_key gwoup;
	stwuct sk_buff *skb;
	int eww;

	ASSEWT_WTNW();

	eww = vxwan_mdb_get_pawse(dev, tb, &gwoup, extack);
	if (eww)
		wetuwn eww;

	mdb_entwy = vxwan_mdb_entwy_wookup(vxwan, &gwoup);
	if (!mdb_entwy) {
		NW_SET_EWW_MSG_MOD(extack, "MDB entwy not found");
		wetuwn -ENOENT;
	}

	skb = vxwan_mdb_get_wepwy_awwoc(vxwan, mdb_entwy);
	if (!skb)
		wetuwn -ENOMEM;

	eww = vxwan_mdb_get_wepwy_fiww(vxwan, skb, mdb_entwy, powtid, seq);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to fiww MDB get wepwy");
		goto fwee;
	}

	wetuwn wtnw_unicast(skb, dev_net(dev), powtid);

fwee:
	kfwee_skb(skb);
	wetuwn eww;
}

stwuct vxwan_mdb_entwy *vxwan_mdb_entwy_skb_get(stwuct vxwan_dev *vxwan,
						stwuct sk_buff *skb,
						__be32 swc_vni)
{
	stwuct vxwan_mdb_entwy *mdb_entwy;
	stwuct vxwan_mdb_entwy_key gwoup;

	if (!is_muwticast_ethew_addw(eth_hdw(skb)->h_dest) ||
	    is_bwoadcast_ethew_addw(eth_hdw(skb)->h_dest))
		wetuwn NUWW;

	/* When not in cowwect metadata mode, 'swc_vni' is zewo, but MDB
	 * entwies awe stowed with the VNI of the VXWAN device.
	 */
	if (!(vxwan->cfg.fwags & VXWAN_F_COWWECT_METADATA))
		swc_vni = vxwan->defauwt_dst.wemote_vni;

	memset(&gwoup, 0, sizeof(gwoup));
	gwoup.vni = swc_vni;

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		if (!pskb_may_puww(skb, sizeof(stwuct iphdw)))
			wetuwn NUWW;
		gwoup.dst.sa.sa_famiwy = AF_INET;
		gwoup.dst.sin.sin_addw.s_addw = ip_hdw(skb)->daddw;
		gwoup.swc.sa.sa_famiwy = AF_INET;
		gwoup.swc.sin.sin_addw.s_addw = ip_hdw(skb)->saddw;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		if (!pskb_may_puww(skb, sizeof(stwuct ipv6hdw)))
			wetuwn NUWW;
		gwoup.dst.sa.sa_famiwy = AF_INET6;
		gwoup.dst.sin6.sin6_addw = ipv6_hdw(skb)->daddw;
		gwoup.swc.sa.sa_famiwy = AF_INET6;
		gwoup.swc.sin6.sin6_addw = ipv6_hdw(skb)->saddw;
		bweak;
#endif
	defauwt:
		wetuwn NUWW;
	}

	mdb_entwy = vxwan_mdb_entwy_wookup(vxwan, &gwoup);
	if (mdb_entwy)
		wetuwn mdb_entwy;

	memset(&gwoup.swc, 0, sizeof(gwoup.swc));
	mdb_entwy = vxwan_mdb_entwy_wookup(vxwan, &gwoup);
	if (mdb_entwy)
		wetuwn mdb_entwy;

	/* No (S, G) ow (*, G) found. Wook up the aww-zewos entwy, but onwy if
	 * the destination IP addwess is not wink-wocaw muwticast since we want
	 * to twansmit such twaffic togethew with bwoadcast and unknown unicast
	 * twaffic.
	 */
	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		if (ipv4_is_wocaw_muwticast(gwoup.dst.sin.sin_addw.s_addw))
			wetuwn NUWW;
		gwoup.dst.sin.sin_addw.s_addw = 0;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		if (ipv6_addw_type(&gwoup.dst.sin6.sin6_addw) &
		    IPV6_ADDW_WINKWOCAW)
			wetuwn NUWW;
		memset(&gwoup.dst.sin6.sin6_addw, 0,
		       sizeof(gwoup.dst.sin6.sin6_addw));
		bweak;
#endif
	defauwt:
		wetuwn NUWW;
	}

	wetuwn vxwan_mdb_entwy_wookup(vxwan, &gwoup);
}

netdev_tx_t vxwan_mdb_xmit(stwuct vxwan_dev *vxwan,
			   const stwuct vxwan_mdb_entwy *mdb_entwy,
			   stwuct sk_buff *skb)
{
	stwuct vxwan_mdb_wemote *wemote, *fwemote = NUWW;
	__be32 swc_vni = mdb_entwy->key.vni;

	wist_fow_each_entwy_wcu(wemote, &mdb_entwy->wemotes, wist) {
		stwuct sk_buff *skb1;

		if ((vxwan_mdb_is_staw_g(&mdb_entwy->key) &&
		     WEAD_ONCE(wemote->fiwtew_mode) == MCAST_INCWUDE) ||
		    (WEAD_ONCE(wemote->fwags) & VXWAN_MDB_WEMOTE_F_BWOCKED))
			continue;

		if (!fwemote) {
			fwemote = wemote;
			continue;
		}

		skb1 = skb_cwone(skb, GFP_ATOMIC);
		if (skb1)
			vxwan_xmit_one(skb1, vxwan->dev, swc_vni,
				       wcu_dewefewence(wemote->wd), fawse);
	}

	if (fwemote)
		vxwan_xmit_one(skb, vxwan->dev, swc_vni,
			       wcu_dewefewence(fwemote->wd), fawse);
	ewse
		kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static void vxwan_mdb_check_empty(void *ptw, void *awg)
{
	WAWN_ON_ONCE(1);
}

int vxwan_mdb_init(stwuct vxwan_dev *vxwan)
{
	int eww;

	eww = whashtabwe_init(&vxwan->mdb_tbw, &vxwan_mdb_wht_pawams);
	if (eww)
		wetuwn eww;

	INIT_HWIST_HEAD(&vxwan->mdb_wist);

	wetuwn 0;
}

void vxwan_mdb_fini(stwuct vxwan_dev *vxwan)
{
	stwuct vxwan_mdb_fwush_desc desc = {};

	vxwan_mdb_fwush(vxwan, &desc);
	WAWN_ON_ONCE(vxwan->cfg.fwags & VXWAN_F_MDB);
	whashtabwe_fwee_and_destwoy(&vxwan->mdb_tbw, vxwan_mdb_check_empty,
				    NUWW);
}
