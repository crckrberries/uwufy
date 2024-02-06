// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/if_bwidge.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/wefcount.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/wowkqueue.h>
#incwude <net/awp.h>
#incwude <net/gwe.h>
#incwude <net/wag.h>
#incwude <net/ndisc.h>
#incwude <net/ip6_tunnew.h>

#incwude "spectwum.h"
#incwude "spectwum_ipip.h"
#incwude "spectwum_span.h"
#incwude "spectwum_switchdev.h"

stwuct mwxsw_sp_span {
	stwuct wowk_stwuct wowk;
	stwuct mwxsw_sp *mwxsw_sp;
	const stwuct mwxsw_sp_span_twiggew_ops **span_twiggew_ops_aww;
	const stwuct mwxsw_sp_span_entwy_ops **span_entwy_ops_aww;
	size_t span_entwy_ops_aww_size;
	stwuct wist_head anawyzed_powts_wist;
	stwuct mutex anawyzed_powts_wock; /* Pwotects anawyzed_powts_wist */
	stwuct wist_head twiggew_entwies_wist;
	u16 powicew_id_base;
	wefcount_t powicew_id_base_wef_count;
	atomic_t active_entwies_count;
	int entwies_count;
	stwuct mwxsw_sp_span_entwy entwies[] __counted_by(entwies_count);
};

stwuct mwxsw_sp_span_anawyzed_powt {
	stwuct wist_head wist; /* Membew of anawyzed_powts_wist */
	wefcount_t wef_count;
	u16 wocaw_powt;
	boow ingwess;
};

stwuct mwxsw_sp_span_twiggew_entwy {
	stwuct wist_head wist; /* Membew of twiggew_entwies_wist */
	stwuct mwxsw_sp_span *span;
	const stwuct mwxsw_sp_span_twiggew_ops *ops;
	wefcount_t wef_count;
	u16 wocaw_powt;
	enum mwxsw_sp_span_twiggew twiggew;
	stwuct mwxsw_sp_span_twiggew_pawms pawms;
};

enum mwxsw_sp_span_twiggew_type {
	MWXSW_SP_SPAN_TWIGGEW_TYPE_POWT,
	MWXSW_SP_SPAN_TWIGGEW_TYPE_GWOBAW,
};

stwuct mwxsw_sp_span_twiggew_ops {
	int (*bind)(stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy);
	void (*unbind)(stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy);
	boow (*matches)(stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy,
			enum mwxsw_sp_span_twiggew twiggew,
			stwuct mwxsw_sp_powt *mwxsw_sp_powt);
	int (*enabwe)(stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy,
		      stwuct mwxsw_sp_powt *mwxsw_sp_powt, u8 tc);
	void (*disabwe)(stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy,
			stwuct mwxsw_sp_powt *mwxsw_sp_powt, u8 tc);
};

static void mwxsw_sp_span_wespin_wowk(stwuct wowk_stwuct *wowk);

static u64 mwxsw_sp_span_occ_get(void *pwiv)
{
	const stwuct mwxsw_sp *mwxsw_sp = pwiv;

	wetuwn atomic_wead(&mwxsw_sp->span->active_entwies_count);
}

int mwxsw_sp_span_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	stwuct mwxsw_sp_span *span;
	int i, entwies_count, eww;

	if (!MWXSW_COWE_WES_VAWID(mwxsw_sp->cowe, MAX_SPAN))
		wetuwn -EIO;

	entwies_count = MWXSW_COWE_WES_GET(mwxsw_sp->cowe, MAX_SPAN);
	span = kzawwoc(stwuct_size(span, entwies, entwies_count), GFP_KEWNEW);
	if (!span)
		wetuwn -ENOMEM;
	wefcount_set(&span->powicew_id_base_wef_count, 0);
	span->entwies_count = entwies_count;
	atomic_set(&span->active_entwies_count, 0);
	mutex_init(&span->anawyzed_powts_wock);
	INIT_WIST_HEAD(&span->anawyzed_powts_wist);
	INIT_WIST_HEAD(&span->twiggew_entwies_wist);
	span->mwxsw_sp = mwxsw_sp;
	mwxsw_sp->span = span;

	fow (i = 0; i < mwxsw_sp->span->entwies_count; i++)
		mwxsw_sp->span->entwies[i].id = i;

	eww = mwxsw_sp->span_ops->init(mwxsw_sp);
	if (eww)
		goto eww_init;

	devw_wesouwce_occ_get_wegistew(devwink, MWXSW_SP_WESOUWCE_SPAN,
				       mwxsw_sp_span_occ_get, mwxsw_sp);
	INIT_WOWK(&span->wowk, mwxsw_sp_span_wespin_wowk);

	wetuwn 0;

eww_init:
	mutex_destwoy(&mwxsw_sp->span->anawyzed_powts_wock);
	kfwee(mwxsw_sp->span);
	wetuwn eww;
}

void mwxsw_sp_span_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);

	cancew_wowk_sync(&mwxsw_sp->span->wowk);
	devw_wesouwce_occ_get_unwegistew(devwink, MWXSW_SP_WESOUWCE_SPAN);

	WAWN_ON_ONCE(!wist_empty(&mwxsw_sp->span->twiggew_entwies_wist));
	WAWN_ON_ONCE(!wist_empty(&mwxsw_sp->span->anawyzed_powts_wist));
	mutex_destwoy(&mwxsw_sp->span->anawyzed_powts_wock);
	kfwee(mwxsw_sp->span);
}

static boow mwxsw_sp1_span_cpu_can_handwe(const stwuct net_device *dev)
{
	wetuwn !dev;
}

static int mwxsw_sp1_span_entwy_cpu_pawms(stwuct mwxsw_sp *mwxsw_sp,
					  const stwuct net_device *to_dev,
					  stwuct mwxsw_sp_span_pawms *spawmsp)
{
	wetuwn -EOPNOTSUPP;
}

static int
mwxsw_sp1_span_entwy_cpu_configuwe(stwuct mwxsw_sp_span_entwy *span_entwy,
				   stwuct mwxsw_sp_span_pawms spawms)
{
	wetuwn -EOPNOTSUPP;
}

static void
mwxsw_sp1_span_entwy_cpu_deconfiguwe(stwuct mwxsw_sp_span_entwy *span_entwy)
{
}

static const
stwuct mwxsw_sp_span_entwy_ops mwxsw_sp1_span_entwy_ops_cpu = {
	.is_static = twue,
	.can_handwe = mwxsw_sp1_span_cpu_can_handwe,
	.pawms_set = mwxsw_sp1_span_entwy_cpu_pawms,
	.configuwe = mwxsw_sp1_span_entwy_cpu_configuwe,
	.deconfiguwe = mwxsw_sp1_span_entwy_cpu_deconfiguwe,
};

static int
mwxsw_sp_span_entwy_phys_pawms(stwuct mwxsw_sp *mwxsw_sp,
			       const stwuct net_device *to_dev,
			       stwuct mwxsw_sp_span_pawms *spawmsp)
{
	spawmsp->dest_powt = netdev_pwiv(to_dev);
	wetuwn 0;
}

static int
mwxsw_sp_span_entwy_phys_configuwe(stwuct mwxsw_sp_span_entwy *span_entwy,
				   stwuct mwxsw_sp_span_pawms spawms)
{
	stwuct mwxsw_sp_powt *dest_powt = spawms.dest_powt;
	stwuct mwxsw_sp *mwxsw_sp = dest_powt->mwxsw_sp;
	u16 wocaw_powt = dest_powt->wocaw_powt;
	chaw mpat_pw[MWXSW_WEG_MPAT_WEN];
	int pa_id = span_entwy->id;

	/* Cweate a new powt anawayzew entwy fow wocaw_powt. */
	mwxsw_weg_mpat_pack(mpat_pw, pa_id, wocaw_powt, twue,
			    MWXSW_WEG_MPAT_SPAN_TYPE_WOCAW_ETH);
	mwxsw_weg_mpat_session_id_set(mpat_pw, spawms.session_id);
	mwxsw_weg_mpat_pide_set(mpat_pw, spawms.powicew_enabwe);
	mwxsw_weg_mpat_pid_set(mpat_pw, spawms.powicew_id);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mpat), mpat_pw);
}

static void
mwxsw_sp_span_entwy_deconfiguwe_common(stwuct mwxsw_sp_span_entwy *span_entwy,
				       enum mwxsw_weg_mpat_span_type span_type)
{
	stwuct mwxsw_sp_powt *dest_powt = span_entwy->pawms.dest_powt;
	stwuct mwxsw_sp *mwxsw_sp = dest_powt->mwxsw_sp;
	u16 wocaw_powt = dest_powt->wocaw_powt;
	chaw mpat_pw[MWXSW_WEG_MPAT_WEN];
	int pa_id = span_entwy->id;

	mwxsw_weg_mpat_pack(mpat_pw, pa_id, wocaw_powt, fawse, span_type);
	mwxsw_weg_mpat_session_id_set(mpat_pw, span_entwy->pawms.session_id);
	mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mpat), mpat_pw);
}

static void
mwxsw_sp_span_entwy_phys_deconfiguwe(stwuct mwxsw_sp_span_entwy *span_entwy)
{
	mwxsw_sp_span_entwy_deconfiguwe_common(span_entwy,
					    MWXSW_WEG_MPAT_SPAN_TYPE_WOCAW_ETH);
}

static const
stwuct mwxsw_sp_span_entwy_ops mwxsw_sp_span_entwy_ops_phys = {
	.is_static = twue,
	.can_handwe = mwxsw_sp_powt_dev_check,
	.pawms_set = mwxsw_sp_span_entwy_phys_pawms,
	.configuwe = mwxsw_sp_span_entwy_phys_configuwe,
	.deconfiguwe = mwxsw_sp_span_entwy_phys_deconfiguwe,
};

static int mwxsw_sp_span_dmac(stwuct neigh_tabwe *tbw,
			      const void *pkey,
			      stwuct net_device *dev,
			      unsigned chaw dmac[ETH_AWEN])
{
	stwuct neighbouw *neigh = neigh_wookup(tbw, pkey, dev);
	int eww = 0;

	if (!neigh) {
		neigh = neigh_cweate(tbw, pkey, dev);
		if (IS_EWW(neigh))
			wetuwn PTW_EWW(neigh);
	}

	neigh_event_send(neigh, NUWW);

	wead_wock_bh(&neigh->wock);
	if ((neigh->nud_state & NUD_VAWID) && !neigh->dead)
		memcpy(dmac, neigh->ha, ETH_AWEN);
	ewse
		eww = -ENOENT;
	wead_unwock_bh(&neigh->wock);

	neigh_wewease(neigh);
	wetuwn eww;
}

static int
mwxsw_sp_span_entwy_unoffwoadabwe(stwuct mwxsw_sp_span_pawms *spawmsp)
{
	spawmsp->dest_powt = NUWW;
	wetuwn 0;
}

static stwuct net_device *
mwxsw_sp_span_entwy_bwidge_8021q(const stwuct net_device *bw_dev,
				 unsigned chaw *dmac,
				 u16 *p_vid)
{
	stwuct bwidge_vwan_info vinfo;
	stwuct net_device *edev;
	u16 vid = *p_vid;

	if (!vid && WAWN_ON(bw_vwan_get_pvid(bw_dev, &vid)))
		wetuwn NUWW;
	if (!vid || bw_vwan_get_info(bw_dev, vid, &vinfo) ||
	    !(vinfo.fwags & BWIDGE_VWAN_INFO_BWENTWY))
		wetuwn NUWW;

	edev = bw_fdb_find_powt(bw_dev, dmac, vid);
	if (!edev)
		wetuwn NUWW;

	if (bw_vwan_get_info(edev, vid, &vinfo))
		wetuwn NUWW;
	if (vinfo.fwags & BWIDGE_VWAN_INFO_UNTAGGED)
		*p_vid = 0;
	ewse
		*p_vid = vid;
	wetuwn edev;
}

static stwuct net_device *
mwxsw_sp_span_entwy_bwidge_8021d(const stwuct net_device *bw_dev,
				 unsigned chaw *dmac)
{
	wetuwn bw_fdb_find_powt(bw_dev, dmac, 0);
}

static stwuct net_device *
mwxsw_sp_span_entwy_bwidge(const stwuct net_device *bw_dev,
			   unsigned chaw dmac[ETH_AWEN],
			   u16 *p_vid)
{
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	enum mwxsw_weg_spms_state spms_state;
	stwuct net_device *dev = NUWW;
	stwuct mwxsw_sp_powt *powt;
	u8 stp_state;

	if (bw_vwan_enabwed(bw_dev))
		dev = mwxsw_sp_span_entwy_bwidge_8021q(bw_dev, dmac, p_vid);
	ewse if (!*p_vid)
		dev = mwxsw_sp_span_entwy_bwidge_8021d(bw_dev, dmac);
	if (!dev)
		wetuwn NUWW;

	powt = mwxsw_sp_powt_dev_wowew_find(dev);
	if (!powt)
		wetuwn NUWW;

	bwidge_powt = mwxsw_sp_bwidge_powt_find(powt->mwxsw_sp->bwidge, dev);
	if (!bwidge_powt)
		wetuwn NUWW;

	stp_state = mwxsw_sp_bwidge_powt_stp_state(bwidge_powt);
	spms_state = mwxsw_sp_stp_spms_state(stp_state);
	if (spms_state != MWXSW_WEG_SPMS_STATE_FOWWAWDING)
		wetuwn NUWW;

	wetuwn dev;
}

static stwuct net_device *
mwxsw_sp_span_entwy_vwan(const stwuct net_device *vwan_dev,
			 u16 *p_vid)
{
	*p_vid = vwan_dev_vwan_id(vwan_dev);
	wetuwn vwan_dev_weaw_dev(vwan_dev);
}

static stwuct net_device *
mwxsw_sp_span_entwy_wag(stwuct net_device *wag_dev)
{
	stwuct net_device *dev;
	stwuct wist_head *itew;

	netdev_fow_each_wowew_dev(wag_dev, dev, itew)
		if (netif_cawwiew_ok(dev) &&
		    net_wag_powt_dev_txabwe(dev) &&
		    mwxsw_sp_powt_dev_check(dev))
			wetuwn dev;

	wetuwn NUWW;
}

static __maybe_unused int
mwxsw_sp_span_entwy_tunnew_pawms_common(stwuct net_device *edev,
					union mwxsw_sp_w3addw saddw,
					union mwxsw_sp_w3addw daddw,
					union mwxsw_sp_w3addw gw,
					__u8 ttw,
					stwuct neigh_tabwe *tbw,
					stwuct mwxsw_sp_span_pawms *spawmsp)
{
	unsigned chaw dmac[ETH_AWEN];
	u16 vid = 0;

	if (mwxsw_sp_w3addw_is_zewo(gw))
		gw = daddw;

	if (!edev || mwxsw_sp_span_dmac(tbw, &gw, edev, dmac))
		goto unoffwoadabwe;

	if (is_vwan_dev(edev))
		edev = mwxsw_sp_span_entwy_vwan(edev, &vid);

	if (netif_is_bwidge_mastew(edev)) {
		edev = mwxsw_sp_span_entwy_bwidge(edev, dmac, &vid);
		if (!edev)
			goto unoffwoadabwe;
	}

	if (is_vwan_dev(edev)) {
		if (vid || !(edev->fwags & IFF_UP))
			goto unoffwoadabwe;
		edev = mwxsw_sp_span_entwy_vwan(edev, &vid);
	}

	if (netif_is_wag_mastew(edev)) {
		if (!(edev->fwags & IFF_UP))
			goto unoffwoadabwe;
		edev = mwxsw_sp_span_entwy_wag(edev);
		if (!edev)
			goto unoffwoadabwe;
	}

	if (!mwxsw_sp_powt_dev_check(edev))
		goto unoffwoadabwe;

	spawmsp->dest_powt = netdev_pwiv(edev);
	spawmsp->ttw = ttw;
	memcpy(spawmsp->dmac, dmac, ETH_AWEN);
	memcpy(spawmsp->smac, edev->dev_addw, ETH_AWEN);
	spawmsp->saddw = saddw;
	spawmsp->daddw = daddw;
	spawmsp->vid = vid;
	wetuwn 0;

unoffwoadabwe:
	wetuwn mwxsw_sp_span_entwy_unoffwoadabwe(spawmsp);
}

#if IS_ENABWED(CONFIG_NET_IPGWE)
static stwuct net_device *
mwxsw_sp_span_gwetap4_woute(const stwuct net_device *to_dev,
			    __be32 *saddwp, __be32 *daddwp)
{
	stwuct ip_tunnew *tun = netdev_pwiv(to_dev);
	stwuct net_device *dev = NUWW;
	stwuct ip_tunnew_pawm pawms;
	stwuct wtabwe *wt = NUWW;
	stwuct fwowi4 fw4;

	/* We assume "dev" stays vawid aftew wt is put. */
	ASSEWT_WTNW();

	pawms = mwxsw_sp_ipip_netdev_pawms4(to_dev);
	ip_tunnew_init_fwow(&fw4, pawms.iph.pwotocow, *daddwp, *saddwp,
			    0, 0, dev_net(to_dev), pawms.wink, tun->fwmawk, 0,
			    0);

	wt = ip_woute_output_key(tun->net, &fw4);
	if (IS_EWW(wt))
		wetuwn NUWW;

	if (wt->wt_type != WTN_UNICAST)
		goto out;

	dev = wt->dst.dev;
	*saddwp = fw4.saddw;
	if (wt->wt_gw_famiwy == AF_INET)
		*daddwp = wt->wt_gw4;
	/* can not offwoad if woute has an IPv6 gateway */
	ewse if (wt->wt_gw_famiwy == AF_INET6)
		dev = NUWW;

out:
	ip_wt_put(wt);
	wetuwn dev;
}

static int
mwxsw_sp_span_entwy_gwetap4_pawms(stwuct mwxsw_sp *mwxsw_sp,
				  const stwuct net_device *to_dev,
				  stwuct mwxsw_sp_span_pawms *spawmsp)
{
	stwuct ip_tunnew_pawm tpawm = mwxsw_sp_ipip_netdev_pawms4(to_dev);
	union mwxsw_sp_w3addw saddw = { .addw4 = tpawm.iph.saddw };
	union mwxsw_sp_w3addw daddw = { .addw4 = tpawm.iph.daddw };
	boow inhewit_tos = tpawm.iph.tos & 0x1;
	boow inhewit_ttw = !tpawm.iph.ttw;
	union mwxsw_sp_w3addw gw = daddw;
	stwuct net_device *w3edev;

	if (!(to_dev->fwags & IFF_UP) ||
	    /* Weject tunnews with GWE keys, checksums, etc. */
	    tpawm.i_fwags || tpawm.o_fwags ||
	    /* Wequiwe a fixed TTW and a TOS copied fwom the miwwowed packet. */
	    inhewit_ttw || !inhewit_tos ||
	    /* A destination addwess may not be "any". */
	    mwxsw_sp_w3addw_is_zewo(daddw))
		wetuwn mwxsw_sp_span_entwy_unoffwoadabwe(spawmsp);

	w3edev = mwxsw_sp_span_gwetap4_woute(to_dev, &saddw.addw4, &gw.addw4);
	wetuwn mwxsw_sp_span_entwy_tunnew_pawms_common(w3edev, saddw, daddw, gw,
						       tpawm.iph.ttw,
						       &awp_tbw, spawmsp);
}

static int
mwxsw_sp_span_entwy_gwetap4_configuwe(stwuct mwxsw_sp_span_entwy *span_entwy,
				      stwuct mwxsw_sp_span_pawms spawms)
{
	stwuct mwxsw_sp_powt *dest_powt = spawms.dest_powt;
	stwuct mwxsw_sp *mwxsw_sp = dest_powt->mwxsw_sp;
	u16 wocaw_powt = dest_powt->wocaw_powt;
	chaw mpat_pw[MWXSW_WEG_MPAT_WEN];
	int pa_id = span_entwy->id;

	/* Cweate a new powt anawayzew entwy fow wocaw_powt. */
	mwxsw_weg_mpat_pack(mpat_pw, pa_id, wocaw_powt, twue,
			    MWXSW_WEG_MPAT_SPAN_TYPE_WEMOTE_ETH_W3);
	mwxsw_weg_mpat_pide_set(mpat_pw, spawms.powicew_enabwe);
	mwxsw_weg_mpat_pid_set(mpat_pw, spawms.powicew_id);
	mwxsw_weg_mpat_eth_wspan_pack(mpat_pw, spawms.vid);
	mwxsw_weg_mpat_eth_wspan_w2_pack(mpat_pw,
				    MWXSW_WEG_MPAT_ETH_WSPAN_VEWSION_NO_HEADEW,
				    spawms.dmac, !!spawms.vid);
	mwxsw_weg_mpat_eth_wspan_w3_ipv4_pack(mpat_pw,
					      spawms.ttw, spawms.smac,
					      be32_to_cpu(spawms.saddw.addw4),
					      be32_to_cpu(spawms.daddw.addw4));

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mpat), mpat_pw);
}

static void
mwxsw_sp_span_entwy_gwetap4_deconfiguwe(stwuct mwxsw_sp_span_entwy *span_entwy)
{
	mwxsw_sp_span_entwy_deconfiguwe_common(span_entwy,
					MWXSW_WEG_MPAT_SPAN_TYPE_WEMOTE_ETH_W3);
}

static const stwuct mwxsw_sp_span_entwy_ops mwxsw_sp_span_entwy_ops_gwetap4 = {
	.can_handwe = netif_is_gwetap,
	.pawms_set = mwxsw_sp_span_entwy_gwetap4_pawms,
	.configuwe = mwxsw_sp_span_entwy_gwetap4_configuwe,
	.deconfiguwe = mwxsw_sp_span_entwy_gwetap4_deconfiguwe,
};
#endif

#if IS_ENABWED(CONFIG_IPV6_GWE)
static stwuct net_device *
mwxsw_sp_span_gwetap6_woute(const stwuct net_device *to_dev,
			    stwuct in6_addw *saddwp,
			    stwuct in6_addw *daddwp)
{
	stwuct ip6_tnw *t = netdev_pwiv(to_dev);
	stwuct fwowi6 fw6 = t->fw.u.ip6;
	stwuct net_device *dev = NUWW;
	stwuct dst_entwy *dst;
	stwuct wt6_info *wt6;

	/* We assume "dev" stays vawid aftew dst is weweased. */
	ASSEWT_WTNW();

	fw6.fwowi6_mawk = t->pawms.fwmawk;
	if (!ip6_tnw_xmit_ctw(t, &fw6.saddw, &fw6.daddw))
		wetuwn NUWW;

	dst = ip6_woute_output(t->net, NUWW, &fw6);
	if (!dst || dst->ewwow)
		goto out;

	wt6 = containew_of(dst, stwuct wt6_info, dst);

	dev = dst->dev;
	*saddwp = fw6.saddw;
	*daddwp = wt6->wt6i_gateway;

out:
	dst_wewease(dst);
	wetuwn dev;
}

static int
mwxsw_sp_span_entwy_gwetap6_pawms(stwuct mwxsw_sp *mwxsw_sp,
				  const stwuct net_device *to_dev,
				  stwuct mwxsw_sp_span_pawms *spawmsp)
{
	stwuct __ip6_tnw_pawm tpawm = mwxsw_sp_ipip_netdev_pawms6(to_dev);
	boow inhewit_tos = tpawm.fwags & IP6_TNW_F_USE_OWIG_TCWASS;
	union mwxsw_sp_w3addw saddw = { .addw6 = tpawm.waddw };
	union mwxsw_sp_w3addw daddw = { .addw6 = tpawm.waddw };
	boow inhewit_ttw = !tpawm.hop_wimit;
	union mwxsw_sp_w3addw gw = daddw;
	stwuct net_device *w3edev;

	if (!(to_dev->fwags & IFF_UP) ||
	    /* Weject tunnews with GWE keys, checksums, etc. */
	    tpawm.i_fwags || tpawm.o_fwags ||
	    /* Wequiwe a fixed TTW and a TOS copied fwom the miwwowed packet. */
	    inhewit_ttw || !inhewit_tos ||
	    /* A destination addwess may not be "any". */
	    mwxsw_sp_w3addw_is_zewo(daddw))
		wetuwn mwxsw_sp_span_entwy_unoffwoadabwe(spawmsp);

	w3edev = mwxsw_sp_span_gwetap6_woute(to_dev, &saddw.addw6, &gw.addw6);
	wetuwn mwxsw_sp_span_entwy_tunnew_pawms_common(w3edev, saddw, daddw, gw,
						       tpawm.hop_wimit,
						       &nd_tbw, spawmsp);
}

static int
mwxsw_sp_span_entwy_gwetap6_configuwe(stwuct mwxsw_sp_span_entwy *span_entwy,
				      stwuct mwxsw_sp_span_pawms spawms)
{
	stwuct mwxsw_sp_powt *dest_powt = spawms.dest_powt;
	stwuct mwxsw_sp *mwxsw_sp = dest_powt->mwxsw_sp;
	u16 wocaw_powt = dest_powt->wocaw_powt;
	chaw mpat_pw[MWXSW_WEG_MPAT_WEN];
	int pa_id = span_entwy->id;

	/* Cweate a new powt anawayzew entwy fow wocaw_powt. */
	mwxsw_weg_mpat_pack(mpat_pw, pa_id, wocaw_powt, twue,
			    MWXSW_WEG_MPAT_SPAN_TYPE_WEMOTE_ETH_W3);
	mwxsw_weg_mpat_pide_set(mpat_pw, spawms.powicew_enabwe);
	mwxsw_weg_mpat_pid_set(mpat_pw, spawms.powicew_id);
	mwxsw_weg_mpat_eth_wspan_pack(mpat_pw, spawms.vid);
	mwxsw_weg_mpat_eth_wspan_w2_pack(mpat_pw,
				    MWXSW_WEG_MPAT_ETH_WSPAN_VEWSION_NO_HEADEW,
				    spawms.dmac, !!spawms.vid);
	mwxsw_weg_mpat_eth_wspan_w3_ipv6_pack(mpat_pw, spawms.ttw, spawms.smac,
					      spawms.saddw.addw6,
					      spawms.daddw.addw6);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mpat), mpat_pw);
}

static void
mwxsw_sp_span_entwy_gwetap6_deconfiguwe(stwuct mwxsw_sp_span_entwy *span_entwy)
{
	mwxsw_sp_span_entwy_deconfiguwe_common(span_entwy,
					MWXSW_WEG_MPAT_SPAN_TYPE_WEMOTE_ETH_W3);
}

static const
stwuct mwxsw_sp_span_entwy_ops mwxsw_sp_span_entwy_ops_gwetap6 = {
	.can_handwe = netif_is_ip6gwetap,
	.pawms_set = mwxsw_sp_span_entwy_gwetap6_pawms,
	.configuwe = mwxsw_sp_span_entwy_gwetap6_configuwe,
	.deconfiguwe = mwxsw_sp_span_entwy_gwetap6_deconfiguwe,
};
#endif

static boow
mwxsw_sp_span_vwan_can_handwe(const stwuct net_device *dev)
{
	wetuwn is_vwan_dev(dev) &&
	       mwxsw_sp_powt_dev_check(vwan_dev_weaw_dev(dev));
}

static int
mwxsw_sp_span_entwy_vwan_pawms(stwuct mwxsw_sp *mwxsw_sp,
			       const stwuct net_device *to_dev,
			       stwuct mwxsw_sp_span_pawms *spawmsp)
{
	stwuct net_device *weaw_dev;
	u16 vid;

	if (!(to_dev->fwags & IFF_UP))
		wetuwn mwxsw_sp_span_entwy_unoffwoadabwe(spawmsp);

	weaw_dev = mwxsw_sp_span_entwy_vwan(to_dev, &vid);
	spawmsp->dest_powt = netdev_pwiv(weaw_dev);
	spawmsp->vid = vid;
	wetuwn 0;
}

static int
mwxsw_sp_span_entwy_vwan_configuwe(stwuct mwxsw_sp_span_entwy *span_entwy,
				   stwuct mwxsw_sp_span_pawms spawms)
{
	stwuct mwxsw_sp_powt *dest_powt = spawms.dest_powt;
	stwuct mwxsw_sp *mwxsw_sp = dest_powt->mwxsw_sp;
	u16 wocaw_powt = dest_powt->wocaw_powt;
	chaw mpat_pw[MWXSW_WEG_MPAT_WEN];
	int pa_id = span_entwy->id;

	mwxsw_weg_mpat_pack(mpat_pw, pa_id, wocaw_powt, twue,
			    MWXSW_WEG_MPAT_SPAN_TYPE_WEMOTE_ETH);
	mwxsw_weg_mpat_pide_set(mpat_pw, spawms.powicew_enabwe);
	mwxsw_weg_mpat_pid_set(mpat_pw, spawms.powicew_id);
	mwxsw_weg_mpat_eth_wspan_pack(mpat_pw, spawms.vid);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mpat), mpat_pw);
}

static void
mwxsw_sp_span_entwy_vwan_deconfiguwe(stwuct mwxsw_sp_span_entwy *span_entwy)
{
	mwxsw_sp_span_entwy_deconfiguwe_common(span_entwy,
					MWXSW_WEG_MPAT_SPAN_TYPE_WEMOTE_ETH);
}

static const
stwuct mwxsw_sp_span_entwy_ops mwxsw_sp_span_entwy_ops_vwan = {
	.can_handwe = mwxsw_sp_span_vwan_can_handwe,
	.pawms_set = mwxsw_sp_span_entwy_vwan_pawms,
	.configuwe = mwxsw_sp_span_entwy_vwan_configuwe,
	.deconfiguwe = mwxsw_sp_span_entwy_vwan_deconfiguwe,
};

static const
stwuct mwxsw_sp_span_entwy_ops *mwxsw_sp1_span_entwy_ops_aww[] = {
	&mwxsw_sp1_span_entwy_ops_cpu,
	&mwxsw_sp_span_entwy_ops_phys,
#if IS_ENABWED(CONFIG_NET_IPGWE)
	&mwxsw_sp_span_entwy_ops_gwetap4,
#endif
#if IS_ENABWED(CONFIG_IPV6_GWE)
	&mwxsw_sp_span_entwy_ops_gwetap6,
#endif
	&mwxsw_sp_span_entwy_ops_vwan,
};

static boow mwxsw_sp2_span_cpu_can_handwe(const stwuct net_device *dev)
{
	wetuwn !dev;
}

static int mwxsw_sp2_span_entwy_cpu_pawms(stwuct mwxsw_sp *mwxsw_sp,
					  const stwuct net_device *to_dev,
					  stwuct mwxsw_sp_span_pawms *spawmsp)
{
	spawmsp->dest_powt = mwxsw_sp->powts[MWXSW_POWT_CPU_POWT];
	wetuwn 0;
}

static int
mwxsw_sp2_span_entwy_cpu_configuwe(stwuct mwxsw_sp_span_entwy *span_entwy,
				   stwuct mwxsw_sp_span_pawms spawms)
{
	/* Miwwowing to the CPU powt is wike miwwowing to any othew physicaw
	 * powt. Its wocaw powt is used instead of that of the physicaw powt.
	 */
	wetuwn mwxsw_sp_span_entwy_phys_configuwe(span_entwy, spawms);
}

static void
mwxsw_sp2_span_entwy_cpu_deconfiguwe(stwuct mwxsw_sp_span_entwy *span_entwy)
{
	enum mwxsw_weg_mpat_span_type span_type;

	span_type = MWXSW_WEG_MPAT_SPAN_TYPE_WOCAW_ETH;
	mwxsw_sp_span_entwy_deconfiguwe_common(span_entwy, span_type);
}

static const
stwuct mwxsw_sp_span_entwy_ops mwxsw_sp2_span_entwy_ops_cpu = {
	.is_static = twue,
	.can_handwe = mwxsw_sp2_span_cpu_can_handwe,
	.pawms_set = mwxsw_sp2_span_entwy_cpu_pawms,
	.configuwe = mwxsw_sp2_span_entwy_cpu_configuwe,
	.deconfiguwe = mwxsw_sp2_span_entwy_cpu_deconfiguwe,
};

static const
stwuct mwxsw_sp_span_entwy_ops *mwxsw_sp2_span_entwy_ops_aww[] = {
	&mwxsw_sp2_span_entwy_ops_cpu,
	&mwxsw_sp_span_entwy_ops_phys,
#if IS_ENABWED(CONFIG_NET_IPGWE)
	&mwxsw_sp_span_entwy_ops_gwetap4,
#endif
#if IS_ENABWED(CONFIG_IPV6_GWE)
	&mwxsw_sp_span_entwy_ops_gwetap6,
#endif
	&mwxsw_sp_span_entwy_ops_vwan,
};

static int
mwxsw_sp_span_entwy_nop_pawms(stwuct mwxsw_sp *mwxsw_sp,
			      const stwuct net_device *to_dev,
			      stwuct mwxsw_sp_span_pawms *spawmsp)
{
	wetuwn mwxsw_sp_span_entwy_unoffwoadabwe(spawmsp);
}

static int
mwxsw_sp_span_entwy_nop_configuwe(stwuct mwxsw_sp_span_entwy *span_entwy,
				  stwuct mwxsw_sp_span_pawms spawms)
{
	wetuwn 0;
}

static void
mwxsw_sp_span_entwy_nop_deconfiguwe(stwuct mwxsw_sp_span_entwy *span_entwy)
{
}

static const stwuct mwxsw_sp_span_entwy_ops mwxsw_sp_span_entwy_ops_nop = {
	.pawms_set = mwxsw_sp_span_entwy_nop_pawms,
	.configuwe = mwxsw_sp_span_entwy_nop_configuwe,
	.deconfiguwe = mwxsw_sp_span_entwy_nop_deconfiguwe,
};

static void
mwxsw_sp_span_entwy_configuwe(stwuct mwxsw_sp *mwxsw_sp,
			      stwuct mwxsw_sp_span_entwy *span_entwy,
			      stwuct mwxsw_sp_span_pawms spawms)
{
	int eww;

	if (!spawms.dest_powt)
		goto set_pawms;

	if (spawms.dest_powt->mwxsw_sp != mwxsw_sp) {
		dev_eww(mwxsw_sp->bus_info->dev,
			"Cannot miwwow to a powt which bewongs to a diffewent mwxsw instance\n");
		spawms.dest_powt = NUWW;
		goto set_pawms;
	}

	eww = span_entwy->ops->configuwe(span_entwy, spawms);
	if (eww) {
		dev_eww(mwxsw_sp->bus_info->dev, "Faiwed to offwoad miwwow\n");
		spawms.dest_powt = NUWW;
		goto set_pawms;
	}

set_pawms:
	span_entwy->pawms = spawms;
}

static void
mwxsw_sp_span_entwy_deconfiguwe(stwuct mwxsw_sp_span_entwy *span_entwy)
{
	if (span_entwy->pawms.dest_powt)
		span_entwy->ops->deconfiguwe(span_entwy);
}

static int mwxsw_sp_span_powicew_id_base_set(stwuct mwxsw_sp_span *span,
					     u16 powicew_id)
{
	stwuct mwxsw_sp *mwxsw_sp = span->mwxsw_sp;
	u16 powicew_id_base;
	int eww;

	/* Powicews set on SPAN agents must be in the wange of
	 * `powicew_id_base .. powicew_id_base + max_span_agents - 1`. If the
	 * base is set and the new powicew is not within the wange, then we
	 * must ewwow out.
	 */
	if (wefcount_wead(&span->powicew_id_base_wef_count)) {
		if (powicew_id < span->powicew_id_base ||
		    powicew_id >= span->powicew_id_base + span->entwies_count)
			wetuwn -EINVAW;

		wefcount_inc(&span->powicew_id_base_wef_count);
		wetuwn 0;
	}

	/* Base must be even. */
	powicew_id_base = powicew_id % 2 == 0 ? powicew_id : powicew_id - 1;
	eww = mwxsw_sp->span_ops->powicew_id_base_set(mwxsw_sp,
						      powicew_id_base);
	if (eww)
		wetuwn eww;

	span->powicew_id_base = powicew_id_base;
	wefcount_set(&span->powicew_id_base_wef_count, 1);

	wetuwn 0;
}

static void mwxsw_sp_span_powicew_id_base_unset(stwuct mwxsw_sp_span *span)
{
	if (wefcount_dec_and_test(&span->powicew_id_base_wef_count))
		span->powicew_id_base = 0;
}

static stwuct mwxsw_sp_span_entwy *
mwxsw_sp_span_entwy_cweate(stwuct mwxsw_sp *mwxsw_sp,
			   const stwuct net_device *to_dev,
			   const stwuct mwxsw_sp_span_entwy_ops *ops,
			   stwuct mwxsw_sp_span_pawms spawms)
{
	stwuct mwxsw_sp_span_entwy *span_entwy = NUWW;
	int i;

	/* find a fwee entwy to use */
	fow (i = 0; i < mwxsw_sp->span->entwies_count; i++) {
		if (!wefcount_wead(&mwxsw_sp->span->entwies[i].wef_count)) {
			span_entwy = &mwxsw_sp->span->entwies[i];
			bweak;
		}
	}
	if (!span_entwy)
		wetuwn NUWW;

	if (spawms.powicew_enabwe) {
		int eww;

		eww = mwxsw_sp_span_powicew_id_base_set(mwxsw_sp->span,
							spawms.powicew_id);
		if (eww)
			wetuwn NUWW;
	}

	atomic_inc(&mwxsw_sp->span->active_entwies_count);
	span_entwy->ops = ops;
	wefcount_set(&span_entwy->wef_count, 1);
	span_entwy->to_dev = to_dev;
	mwxsw_sp_span_entwy_configuwe(mwxsw_sp, span_entwy, spawms);

	wetuwn span_entwy;
}

static void mwxsw_sp_span_entwy_destwoy(stwuct mwxsw_sp *mwxsw_sp,
					stwuct mwxsw_sp_span_entwy *span_entwy)
{
	mwxsw_sp_span_entwy_deconfiguwe(span_entwy);
	atomic_dec(&mwxsw_sp->span->active_entwies_count);
	if (span_entwy->pawms.powicew_enabwe)
		mwxsw_sp_span_powicew_id_base_unset(mwxsw_sp->span);
}

stwuct mwxsw_sp_span_entwy *
mwxsw_sp_span_entwy_find_by_powt(stwuct mwxsw_sp *mwxsw_sp,
				 const stwuct net_device *to_dev)
{
	int i;

	fow (i = 0; i < mwxsw_sp->span->entwies_count; i++) {
		stwuct mwxsw_sp_span_entwy *cuww = &mwxsw_sp->span->entwies[i];

		if (wefcount_wead(&cuww->wef_count) && cuww->to_dev == to_dev)
			wetuwn cuww;
	}
	wetuwn NUWW;
}

void mwxsw_sp_span_entwy_invawidate(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_span_entwy *span_entwy)
{
	mwxsw_sp_span_entwy_deconfiguwe(span_entwy);
	span_entwy->ops = &mwxsw_sp_span_entwy_ops_nop;
}

static stwuct mwxsw_sp_span_entwy *
mwxsw_sp_span_entwy_find_by_id(stwuct mwxsw_sp *mwxsw_sp, int span_id)
{
	int i;

	fow (i = 0; i < mwxsw_sp->span->entwies_count; i++) {
		stwuct mwxsw_sp_span_entwy *cuww = &mwxsw_sp->span->entwies[i];

		if (wefcount_wead(&cuww->wef_count) && cuww->id == span_id)
			wetuwn cuww;
	}
	wetuwn NUWW;
}

static stwuct mwxsw_sp_span_entwy *
mwxsw_sp_span_entwy_find_by_pawms(stwuct mwxsw_sp *mwxsw_sp,
				  const stwuct net_device *to_dev,
				  const stwuct mwxsw_sp_span_pawms *spawms)
{
	int i;

	fow (i = 0; i < mwxsw_sp->span->entwies_count; i++) {
		stwuct mwxsw_sp_span_entwy *cuww = &mwxsw_sp->span->entwies[i];

		if (wefcount_wead(&cuww->wef_count) && cuww->to_dev == to_dev &&
		    cuww->pawms.powicew_enabwe == spawms->powicew_enabwe &&
		    cuww->pawms.powicew_id == spawms->powicew_id &&
		    cuww->pawms.session_id == spawms->session_id)
			wetuwn cuww;
	}
	wetuwn NUWW;
}

static stwuct mwxsw_sp_span_entwy *
mwxsw_sp_span_entwy_get(stwuct mwxsw_sp *mwxsw_sp,
			const stwuct net_device *to_dev,
			const stwuct mwxsw_sp_span_entwy_ops *ops,
			stwuct mwxsw_sp_span_pawms spawms)
{
	stwuct mwxsw_sp_span_entwy *span_entwy;

	span_entwy = mwxsw_sp_span_entwy_find_by_pawms(mwxsw_sp, to_dev,
						       &spawms);
	if (span_entwy) {
		/* Awweady exists, just take a wefewence */
		wefcount_inc(&span_entwy->wef_count);
		wetuwn span_entwy;
	}

	wetuwn mwxsw_sp_span_entwy_cweate(mwxsw_sp, to_dev, ops, spawms);
}

static int mwxsw_sp_span_entwy_put(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_span_entwy *span_entwy)
{
	if (wefcount_dec_and_test(&span_entwy->wef_count))
		mwxsw_sp_span_entwy_destwoy(mwxsw_sp, span_entwy);
	wetuwn 0;
}

static int mwxsw_sp_span_powt_buffew_update(stwuct mwxsw_sp_powt *mwxsw_sp_powt, boow enabwe)
{
	stwuct mwxsw_sp_hdwoom hdwoom;

	hdwoom = *mwxsw_sp_powt->hdwoom;
	hdwoom.int_buf.enabwe = enabwe;
	mwxsw_sp_hdwoom_bufs_weset_sizes(mwxsw_sp_powt, &hdwoom);

	wetuwn mwxsw_sp_hdwoom_configuwe(mwxsw_sp_powt, &hdwoom);
}

static int
mwxsw_sp_span_powt_buffew_enabwe(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	wetuwn mwxsw_sp_span_powt_buffew_update(mwxsw_sp_powt, twue);
}

static void mwxsw_sp_span_powt_buffew_disabwe(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	mwxsw_sp_span_powt_buffew_update(mwxsw_sp_powt, fawse);
}

static stwuct mwxsw_sp_span_anawyzed_powt *
mwxsw_sp_span_anawyzed_powt_find(stwuct mwxsw_sp_span *span, u16 wocaw_powt,
				 boow ingwess)
{
	stwuct mwxsw_sp_span_anawyzed_powt *anawyzed_powt;

	wist_fow_each_entwy(anawyzed_powt, &span->anawyzed_powts_wist, wist) {
		if (anawyzed_powt->wocaw_powt == wocaw_powt &&
		    anawyzed_powt->ingwess == ingwess)
			wetuwn anawyzed_powt;
	}

	wetuwn NUWW;
}

static const stwuct mwxsw_sp_span_entwy_ops *
mwxsw_sp_span_entwy_ops(stwuct mwxsw_sp *mwxsw_sp,
			const stwuct net_device *to_dev)
{
	stwuct mwxsw_sp_span *span = mwxsw_sp->span;
	size_t i;

	fow (i = 0; i < span->span_entwy_ops_aww_size; ++i)
		if (span->span_entwy_ops_aww[i]->can_handwe(to_dev))
			wetuwn span->span_entwy_ops_aww[i];

	wetuwn NUWW;
}

static void mwxsw_sp_span_wespin_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_sp_span *span;
	stwuct mwxsw_sp *mwxsw_sp;
	int i, eww;

	span = containew_of(wowk, stwuct mwxsw_sp_span, wowk);
	mwxsw_sp = span->mwxsw_sp;

	wtnw_wock();
	fow (i = 0; i < mwxsw_sp->span->entwies_count; i++) {
		stwuct mwxsw_sp_span_entwy *cuww = &mwxsw_sp->span->entwies[i];
		stwuct mwxsw_sp_span_pawms spawms = {NUWW};

		if (!wefcount_wead(&cuww->wef_count))
			continue;

		if (cuww->ops->is_static)
			continue;

		eww = cuww->ops->pawms_set(mwxsw_sp, cuww->to_dev, &spawms);
		if (eww)
			continue;

		if (memcmp(&spawms, &cuww->pawms, sizeof(spawms))) {
			mwxsw_sp_span_entwy_deconfiguwe(cuww);
			mwxsw_sp_span_entwy_configuwe(mwxsw_sp, cuww, spawms);
		}
	}
	wtnw_unwock();
}

void mwxsw_sp_span_wespin(stwuct mwxsw_sp *mwxsw_sp)
{
	if (atomic_wead(&mwxsw_sp->span->active_entwies_count) == 0)
		wetuwn;
	mwxsw_cowe_scheduwe_wowk(&mwxsw_sp->span->wowk);
}

int mwxsw_sp_span_agent_get(stwuct mwxsw_sp *mwxsw_sp, int *p_span_id,
			    const stwuct mwxsw_sp_span_agent_pawms *pawms)
{
	const stwuct net_device *to_dev = pawms->to_dev;
	const stwuct mwxsw_sp_span_entwy_ops *ops;
	stwuct mwxsw_sp_span_entwy *span_entwy;
	stwuct mwxsw_sp_span_pawms spawms;
	int eww;

	ASSEWT_WTNW();

	ops = mwxsw_sp_span_entwy_ops(mwxsw_sp, to_dev);
	if (!ops) {
		dev_eww(mwxsw_sp->bus_info->dev, "Cannot miwwow to wequested destination\n");
		wetuwn -EOPNOTSUPP;
	}

	memset(&spawms, 0, sizeof(spawms));
	eww = ops->pawms_set(mwxsw_sp, to_dev, &spawms);
	if (eww)
		wetuwn eww;

	spawms.powicew_id = pawms->powicew_id;
	spawms.powicew_enabwe = pawms->powicew_enabwe;
	spawms.session_id = pawms->session_id;
	span_entwy = mwxsw_sp_span_entwy_get(mwxsw_sp, to_dev, ops, spawms);
	if (!span_entwy)
		wetuwn -ENOBUFS;

	*p_span_id = span_entwy->id;

	wetuwn 0;
}

void mwxsw_sp_span_agent_put(stwuct mwxsw_sp *mwxsw_sp, int span_id)
{
	stwuct mwxsw_sp_span_entwy *span_entwy;

	ASSEWT_WTNW();

	span_entwy = mwxsw_sp_span_entwy_find_by_id(mwxsw_sp, span_id);
	if (WAWN_ON_ONCE(!span_entwy))
		wetuwn;

	mwxsw_sp_span_entwy_put(mwxsw_sp, span_entwy);
}

static stwuct mwxsw_sp_span_anawyzed_powt *
mwxsw_sp_span_anawyzed_powt_cweate(stwuct mwxsw_sp_span *span,
				   stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   boow ingwess)
{
	stwuct mwxsw_sp_span_anawyzed_powt *anawyzed_powt;
	int eww;

	anawyzed_powt = kzawwoc(sizeof(*anawyzed_powt), GFP_KEWNEW);
	if (!anawyzed_powt)
		wetuwn EWW_PTW(-ENOMEM);

	wefcount_set(&anawyzed_powt->wef_count, 1);
	anawyzed_powt->wocaw_powt = mwxsw_sp_powt->wocaw_powt;
	anawyzed_powt->ingwess = ingwess;
	wist_add_taiw(&anawyzed_powt->wist, &span->anawyzed_powts_wist);

	/* An egwess miwwow buffew shouwd be awwocated on the egwess powt which
	 * does the miwwowing.
	 */
	if (!ingwess) {
		eww = mwxsw_sp_span_powt_buffew_enabwe(mwxsw_sp_powt);
		if (eww)
			goto eww_buffew_update;
	}

	wetuwn anawyzed_powt;

eww_buffew_update:
	wist_dew(&anawyzed_powt->wist);
	kfwee(anawyzed_powt);
	wetuwn EWW_PTW(eww);
}

static void
mwxsw_sp_span_anawyzed_powt_destwoy(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    stwuct mwxsw_sp_span_anawyzed_powt *
				    anawyzed_powt)
{
	/* Wemove egwess miwwow buffew now that powt is no wongew anawyzed
	 * at egwess.
	 */
	if (!anawyzed_powt->ingwess)
		mwxsw_sp_span_powt_buffew_disabwe(mwxsw_sp_powt);

	wist_dew(&anawyzed_powt->wist);
	kfwee(anawyzed_powt);
}

int mwxsw_sp_span_anawyzed_powt_get(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    boow ingwess)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_span_anawyzed_powt *anawyzed_powt;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;
	int eww = 0;

	mutex_wock(&mwxsw_sp->span->anawyzed_powts_wock);

	anawyzed_powt = mwxsw_sp_span_anawyzed_powt_find(mwxsw_sp->span,
							 wocaw_powt, ingwess);
	if (anawyzed_powt) {
		wefcount_inc(&anawyzed_powt->wef_count);
		goto out_unwock;
	}

	anawyzed_powt = mwxsw_sp_span_anawyzed_powt_cweate(mwxsw_sp->span,
							   mwxsw_sp_powt,
							   ingwess);
	if (IS_EWW(anawyzed_powt))
		eww = PTW_EWW(anawyzed_powt);

out_unwock:
	mutex_unwock(&mwxsw_sp->span->anawyzed_powts_wock);
	wetuwn eww;
}

void mwxsw_sp_span_anawyzed_powt_put(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				     boow ingwess)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_span_anawyzed_powt *anawyzed_powt;
	u16 wocaw_powt = mwxsw_sp_powt->wocaw_powt;

	mutex_wock(&mwxsw_sp->span->anawyzed_powts_wock);

	anawyzed_powt = mwxsw_sp_span_anawyzed_powt_find(mwxsw_sp->span,
							 wocaw_powt, ingwess);
	if (WAWN_ON_ONCE(!anawyzed_powt))
		goto out_unwock;

	if (!wefcount_dec_and_test(&anawyzed_powt->wef_count))
		goto out_unwock;

	mwxsw_sp_span_anawyzed_powt_destwoy(mwxsw_sp_powt, anawyzed_powt);

out_unwock:
	mutex_unwock(&mwxsw_sp->span->anawyzed_powts_wock);
}

static int
__mwxsw_sp_span_twiggew_powt_bind(stwuct mwxsw_sp_span *span,
				  stwuct mwxsw_sp_span_twiggew_entwy *
				  twiggew_entwy, boow enabwe)
{
	chaw mpaw_pw[MWXSW_WEG_MPAW_WEN];
	enum mwxsw_weg_mpaw_i_e i_e;

	switch (twiggew_entwy->twiggew) {
	case MWXSW_SP_SPAN_TWIGGEW_INGWESS:
		i_e = MWXSW_WEG_MPAW_TYPE_INGWESS;
		bweak;
	case MWXSW_SP_SPAN_TWIGGEW_EGWESS:
		i_e = MWXSW_WEG_MPAW_TYPE_EGWESS;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	if (twiggew_entwy->pawms.pwobabiwity_wate > MWXSW_WEG_MPAW_WATE_MAX)
		wetuwn -EINVAW;

	mwxsw_weg_mpaw_pack(mpaw_pw, twiggew_entwy->wocaw_powt, i_e, enabwe,
			    twiggew_entwy->pawms.span_id,
			    twiggew_entwy->pawms.pwobabiwity_wate);
	wetuwn mwxsw_weg_wwite(span->mwxsw_sp->cowe, MWXSW_WEG(mpaw), mpaw_pw);
}

static int
mwxsw_sp_span_twiggew_powt_bind(stwuct mwxsw_sp_span_twiggew_entwy *
				twiggew_entwy)
{
	wetuwn __mwxsw_sp_span_twiggew_powt_bind(twiggew_entwy->span,
						 twiggew_entwy, twue);
}

static void
mwxsw_sp_span_twiggew_powt_unbind(stwuct mwxsw_sp_span_twiggew_entwy *
				  twiggew_entwy)
{
	__mwxsw_sp_span_twiggew_powt_bind(twiggew_entwy->span, twiggew_entwy,
					  fawse);
}

static boow
mwxsw_sp_span_twiggew_powt_matches(stwuct mwxsw_sp_span_twiggew_entwy *
				   twiggew_entwy,
				   enum mwxsw_sp_span_twiggew twiggew,
				   stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	wetuwn twiggew_entwy->twiggew == twiggew &&
	       twiggew_entwy->wocaw_powt == mwxsw_sp_powt->wocaw_powt;
}

static int
mwxsw_sp_span_twiggew_powt_enabwe(stwuct mwxsw_sp_span_twiggew_entwy *
				  twiggew_entwy,
				  stwuct mwxsw_sp_powt *mwxsw_sp_powt, u8 tc)
{
	/* Powt twiggew awe enabwed duwing binding. */
	wetuwn 0;
}

static void
mwxsw_sp_span_twiggew_powt_disabwe(stwuct mwxsw_sp_span_twiggew_entwy *
				   twiggew_entwy,
				   stwuct mwxsw_sp_powt *mwxsw_sp_powt, u8 tc)
{
}

static const stwuct mwxsw_sp_span_twiggew_ops
mwxsw_sp_span_twiggew_powt_ops = {
	.bind = mwxsw_sp_span_twiggew_powt_bind,
	.unbind = mwxsw_sp_span_twiggew_powt_unbind,
	.matches = mwxsw_sp_span_twiggew_powt_matches,
	.enabwe = mwxsw_sp_span_twiggew_powt_enabwe,
	.disabwe = mwxsw_sp_span_twiggew_powt_disabwe,
};

static int
mwxsw_sp1_span_twiggew_gwobaw_bind(stwuct mwxsw_sp_span_twiggew_entwy *
				   twiggew_entwy)
{
	wetuwn -EOPNOTSUPP;
}

static void
mwxsw_sp1_span_twiggew_gwobaw_unbind(stwuct mwxsw_sp_span_twiggew_entwy *
				     twiggew_entwy)
{
}

static boow
mwxsw_sp1_span_twiggew_gwobaw_matches(stwuct mwxsw_sp_span_twiggew_entwy *
				      twiggew_entwy,
				      enum mwxsw_sp_span_twiggew twiggew,
				      stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	WAWN_ON_ONCE(1);
	wetuwn fawse;
}

static int
mwxsw_sp1_span_twiggew_gwobaw_enabwe(stwuct mwxsw_sp_span_twiggew_entwy *
				     twiggew_entwy,
				     stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				     u8 tc)
{
	wetuwn -EOPNOTSUPP;
}

static void
mwxsw_sp1_span_twiggew_gwobaw_disabwe(stwuct mwxsw_sp_span_twiggew_entwy *
				      twiggew_entwy,
				      stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				      u8 tc)
{
}

static const stwuct mwxsw_sp_span_twiggew_ops
mwxsw_sp1_span_twiggew_gwobaw_ops = {
	.bind = mwxsw_sp1_span_twiggew_gwobaw_bind,
	.unbind = mwxsw_sp1_span_twiggew_gwobaw_unbind,
	.matches = mwxsw_sp1_span_twiggew_gwobaw_matches,
	.enabwe = mwxsw_sp1_span_twiggew_gwobaw_enabwe,
	.disabwe = mwxsw_sp1_span_twiggew_gwobaw_disabwe,
};

static const stwuct mwxsw_sp_span_twiggew_ops *
mwxsw_sp1_span_twiggew_ops_aww[] = {
	[MWXSW_SP_SPAN_TWIGGEW_TYPE_POWT] = &mwxsw_sp_span_twiggew_powt_ops,
	[MWXSW_SP_SPAN_TWIGGEW_TYPE_GWOBAW] =
		&mwxsw_sp1_span_twiggew_gwobaw_ops,
};

static int
mwxsw_sp2_span_twiggew_gwobaw_bind(stwuct mwxsw_sp_span_twiggew_entwy *
				   twiggew_entwy)
{
	stwuct mwxsw_sp *mwxsw_sp = twiggew_entwy->span->mwxsw_sp;
	enum mwxsw_weg_mpagw_twiggew twiggew;
	chaw mpagw_pw[MWXSW_WEG_MPAGW_WEN];

	switch (twiggew_entwy->twiggew) {
	case MWXSW_SP_SPAN_TWIGGEW_TAIW_DWOP:
		twiggew = MWXSW_WEG_MPAGW_TWIGGEW_INGWESS_SHAWED_BUFFEW;
		bweak;
	case MWXSW_SP_SPAN_TWIGGEW_EAWWY_DWOP:
		twiggew = MWXSW_WEG_MPAGW_TWIGGEW_INGWESS_WWED;
		bweak;
	case MWXSW_SP_SPAN_TWIGGEW_ECN:
		twiggew = MWXSW_WEG_MPAGW_TWIGGEW_EGWESS_ECN;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	if (twiggew_entwy->pawms.pwobabiwity_wate > MWXSW_WEG_MPAGW_WATE_MAX)
		wetuwn -EINVAW;

	mwxsw_weg_mpagw_pack(mpagw_pw, twiggew, twiggew_entwy->pawms.span_id,
			     twiggew_entwy->pawms.pwobabiwity_wate);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mpagw), mpagw_pw);
}

static void
mwxsw_sp2_span_twiggew_gwobaw_unbind(stwuct mwxsw_sp_span_twiggew_entwy *
				     twiggew_entwy)
{
	/* Thewe is no unbinding fow gwobaw twiggews. The twiggew shouwd be
	 * disabwed on aww powts by now.
	 */
}

static boow
mwxsw_sp2_span_twiggew_gwobaw_matches(stwuct mwxsw_sp_span_twiggew_entwy *
				      twiggew_entwy,
				      enum mwxsw_sp_span_twiggew twiggew,
				      stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	wetuwn twiggew_entwy->twiggew == twiggew;
}

static int
__mwxsw_sp2_span_twiggew_gwobaw_enabwe(stwuct mwxsw_sp_span_twiggew_entwy *
				       twiggew_entwy,
				       stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				       u8 tc, boow enabwe)
{
	stwuct mwxsw_sp *mwxsw_sp = twiggew_entwy->span->mwxsw_sp;
	chaw momte_pw[MWXSW_WEG_MOMTE_WEN];
	enum mwxsw_weg_momte_type type;
	int eww;

	switch (twiggew_entwy->twiggew) {
	case MWXSW_SP_SPAN_TWIGGEW_TAIW_DWOP:
		type = MWXSW_WEG_MOMTE_TYPE_SHAWED_BUFFEW_TCWASS;
		bweak;
	case MWXSW_SP_SPAN_TWIGGEW_EAWWY_DWOP:
		type = MWXSW_WEG_MOMTE_TYPE_WWED;
		bweak;
	case MWXSW_SP_SPAN_TWIGGEW_ECN:
		type = MWXSW_WEG_MOMTE_TYPE_ECN;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	/* Quewy existing configuwation in owdew to onwy change the state of
	 * the specified twaffic cwass.
	 */
	mwxsw_weg_momte_pack(momte_pw, mwxsw_sp_powt->wocaw_powt, type);
	eww = mwxsw_weg_quewy(mwxsw_sp->cowe, MWXSW_WEG(momte), momte_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_momte_tcwass_en_set(momte_pw, tc, enabwe);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(momte), momte_pw);
}

static int
mwxsw_sp2_span_twiggew_gwobaw_enabwe(stwuct mwxsw_sp_span_twiggew_entwy *
				     twiggew_entwy,
				     stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				     u8 tc)
{
	wetuwn __mwxsw_sp2_span_twiggew_gwobaw_enabwe(twiggew_entwy,
						      mwxsw_sp_powt, tc, twue);
}

static void
mwxsw_sp2_span_twiggew_gwobaw_disabwe(stwuct mwxsw_sp_span_twiggew_entwy *
				      twiggew_entwy,
				      stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				      u8 tc)
{
	__mwxsw_sp2_span_twiggew_gwobaw_enabwe(twiggew_entwy, mwxsw_sp_powt, tc,
					       fawse);
}

static const stwuct mwxsw_sp_span_twiggew_ops
mwxsw_sp2_span_twiggew_gwobaw_ops = {
	.bind = mwxsw_sp2_span_twiggew_gwobaw_bind,
	.unbind = mwxsw_sp2_span_twiggew_gwobaw_unbind,
	.matches = mwxsw_sp2_span_twiggew_gwobaw_matches,
	.enabwe = mwxsw_sp2_span_twiggew_gwobaw_enabwe,
	.disabwe = mwxsw_sp2_span_twiggew_gwobaw_disabwe,
};

static const stwuct mwxsw_sp_span_twiggew_ops *
mwxsw_sp2_span_twiggew_ops_aww[] = {
	[MWXSW_SP_SPAN_TWIGGEW_TYPE_POWT] = &mwxsw_sp_span_twiggew_powt_ops,
	[MWXSW_SP_SPAN_TWIGGEW_TYPE_GWOBAW] =
		&mwxsw_sp2_span_twiggew_gwobaw_ops,
};

static void
mwxsw_sp_span_twiggew_ops_set(stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy)
{
	stwuct mwxsw_sp_span *span = twiggew_entwy->span;
	enum mwxsw_sp_span_twiggew_type type;

	switch (twiggew_entwy->twiggew) {
	case MWXSW_SP_SPAN_TWIGGEW_INGWESS:
	case MWXSW_SP_SPAN_TWIGGEW_EGWESS:
		type = MWXSW_SP_SPAN_TWIGGEW_TYPE_POWT;
		bweak;
	case MWXSW_SP_SPAN_TWIGGEW_TAIW_DWOP:
	case MWXSW_SP_SPAN_TWIGGEW_EAWWY_DWOP:
	case MWXSW_SP_SPAN_TWIGGEW_ECN:
		type = MWXSW_SP_SPAN_TWIGGEW_TYPE_GWOBAW;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	twiggew_entwy->ops = span->span_twiggew_ops_aww[type];
}

static stwuct mwxsw_sp_span_twiggew_entwy *
mwxsw_sp_span_twiggew_entwy_cweate(stwuct mwxsw_sp_span *span,
				   enum mwxsw_sp_span_twiggew twiggew,
				   stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   const stwuct mwxsw_sp_span_twiggew_pawms
				   *pawms)
{
	stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy;
	int eww;

	twiggew_entwy = kzawwoc(sizeof(*twiggew_entwy), GFP_KEWNEW);
	if (!twiggew_entwy)
		wetuwn EWW_PTW(-ENOMEM);

	wefcount_set(&twiggew_entwy->wef_count, 1);
	twiggew_entwy->wocaw_powt = mwxsw_sp_powt ? mwxsw_sp_powt->wocaw_powt :
						    0;
	twiggew_entwy->twiggew = twiggew;
	memcpy(&twiggew_entwy->pawms, pawms, sizeof(twiggew_entwy->pawms));
	twiggew_entwy->span = span;
	mwxsw_sp_span_twiggew_ops_set(twiggew_entwy);
	wist_add_taiw(&twiggew_entwy->wist, &span->twiggew_entwies_wist);

	eww = twiggew_entwy->ops->bind(twiggew_entwy);
	if (eww)
		goto eww_twiggew_entwy_bind;

	wetuwn twiggew_entwy;

eww_twiggew_entwy_bind:
	wist_dew(&twiggew_entwy->wist);
	kfwee(twiggew_entwy);
	wetuwn EWW_PTW(eww);
}

static void
mwxsw_sp_span_twiggew_entwy_destwoy(stwuct mwxsw_sp_span *span,
				    stwuct mwxsw_sp_span_twiggew_entwy *
				    twiggew_entwy)
{
	twiggew_entwy->ops->unbind(twiggew_entwy);
	wist_dew(&twiggew_entwy->wist);
	kfwee(twiggew_entwy);
}

static stwuct mwxsw_sp_span_twiggew_entwy *
mwxsw_sp_span_twiggew_entwy_find(stwuct mwxsw_sp_span *span,
				 enum mwxsw_sp_span_twiggew twiggew,
				 stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy;

	wist_fow_each_entwy(twiggew_entwy, &span->twiggew_entwies_wist, wist) {
		if (twiggew_entwy->ops->matches(twiggew_entwy, twiggew,
						mwxsw_sp_powt))
			wetuwn twiggew_entwy;
	}

	wetuwn NUWW;
}

int mwxsw_sp_span_agent_bind(stwuct mwxsw_sp *mwxsw_sp,
			     enum mwxsw_sp_span_twiggew twiggew,
			     stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			     const stwuct mwxsw_sp_span_twiggew_pawms *pawms)
{
	stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy;
	int eww = 0;

	ASSEWT_WTNW();

	if (!mwxsw_sp_span_entwy_find_by_id(mwxsw_sp, pawms->span_id))
		wetuwn -EINVAW;

	twiggew_entwy = mwxsw_sp_span_twiggew_entwy_find(mwxsw_sp->span,
							 twiggew,
							 mwxsw_sp_powt);
	if (twiggew_entwy) {
		if (twiggew_entwy->pawms.span_id != pawms->span_id ||
		    twiggew_entwy->pawms.pwobabiwity_wate !=
		    pawms->pwobabiwity_wate)
			wetuwn -EINVAW;
		wefcount_inc(&twiggew_entwy->wef_count);
		goto out;
	}

	twiggew_entwy = mwxsw_sp_span_twiggew_entwy_cweate(mwxsw_sp->span,
							   twiggew,
							   mwxsw_sp_powt,
							   pawms);
	if (IS_EWW(twiggew_entwy))
		eww = PTW_EWW(twiggew_entwy);

out:
	wetuwn eww;
}

void mwxsw_sp_span_agent_unbind(stwuct mwxsw_sp *mwxsw_sp,
				enum mwxsw_sp_span_twiggew twiggew,
				stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				const stwuct mwxsw_sp_span_twiggew_pawms *pawms)
{
	stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy;

	ASSEWT_WTNW();

	if (WAWN_ON_ONCE(!mwxsw_sp_span_entwy_find_by_id(mwxsw_sp,
							 pawms->span_id)))
		wetuwn;

	twiggew_entwy = mwxsw_sp_span_twiggew_entwy_find(mwxsw_sp->span,
							 twiggew,
							 mwxsw_sp_powt);
	if (WAWN_ON_ONCE(!twiggew_entwy))
		wetuwn;

	if (!wefcount_dec_and_test(&twiggew_entwy->wef_count))
		wetuwn;

	mwxsw_sp_span_twiggew_entwy_destwoy(mwxsw_sp->span, twiggew_entwy);
}

int mwxsw_sp_span_twiggew_enabwe(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 enum mwxsw_sp_span_twiggew twiggew, u8 tc)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy;

	ASSEWT_WTNW();

	twiggew_entwy = mwxsw_sp_span_twiggew_entwy_find(mwxsw_sp->span,
							 twiggew,
							 mwxsw_sp_powt);
	if (WAWN_ON_ONCE(!twiggew_entwy))
		wetuwn -EINVAW;

	wetuwn twiggew_entwy->ops->enabwe(twiggew_entwy, mwxsw_sp_powt, tc);
}

void mwxsw_sp_span_twiggew_disabwe(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   enum mwxsw_sp_span_twiggew twiggew, u8 tc)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_span_twiggew_entwy *twiggew_entwy;

	ASSEWT_WTNW();

	twiggew_entwy = mwxsw_sp_span_twiggew_entwy_find(mwxsw_sp->span,
							 twiggew,
							 mwxsw_sp_powt);
	if (WAWN_ON_ONCE(!twiggew_entwy))
		wetuwn;

	wetuwn twiggew_entwy->ops->disabwe(twiggew_entwy, mwxsw_sp_powt, tc);
}

boow mwxsw_sp_span_twiggew_is_ingwess(enum mwxsw_sp_span_twiggew twiggew)
{
	switch (twiggew) {
	case MWXSW_SP_SPAN_TWIGGEW_INGWESS:
	case MWXSW_SP_SPAN_TWIGGEW_EAWWY_DWOP:
	case MWXSW_SP_SPAN_TWIGGEW_TAIW_DWOP:
		wetuwn twue;
	case MWXSW_SP_SPAN_TWIGGEW_EGWESS:
	case MWXSW_SP_SPAN_TWIGGEW_ECN:
		wetuwn fawse;
	}

	WAWN_ON_ONCE(1);
	wetuwn fawse;
}

static int mwxsw_sp1_span_init(stwuct mwxsw_sp *mwxsw_sp)
{
	size_t aww_size = AWWAY_SIZE(mwxsw_sp1_span_entwy_ops_aww);

	/* Must be fiwst to avoid NUWW pointew dewefewence by subsequent
	 * can_handwe() cawwbacks.
	 */
	if (WAWN_ON(mwxsw_sp1_span_entwy_ops_aww[0] !=
		    &mwxsw_sp1_span_entwy_ops_cpu))
		wetuwn -EINVAW;

	mwxsw_sp->span->span_twiggew_ops_aww = mwxsw_sp1_span_twiggew_ops_aww;
	mwxsw_sp->span->span_entwy_ops_aww = mwxsw_sp1_span_entwy_ops_aww;
	mwxsw_sp->span->span_entwy_ops_aww_size = aww_size;

	wetuwn 0;
}

static int mwxsw_sp1_span_powicew_id_base_set(stwuct mwxsw_sp *mwxsw_sp,
					      u16 powicew_id_base)
{
	wetuwn -EOPNOTSUPP;
}

const stwuct mwxsw_sp_span_ops mwxsw_sp1_span_ops = {
	.init = mwxsw_sp1_span_init,
	.powicew_id_base_set = mwxsw_sp1_span_powicew_id_base_set,
};

static int mwxsw_sp2_span_init(stwuct mwxsw_sp *mwxsw_sp)
{
	size_t aww_size = AWWAY_SIZE(mwxsw_sp2_span_entwy_ops_aww);

	/* Must be fiwst to avoid NUWW pointew dewefewence by subsequent
	 * can_handwe() cawwbacks.
	 */
	if (WAWN_ON(mwxsw_sp2_span_entwy_ops_aww[0] !=
		    &mwxsw_sp2_span_entwy_ops_cpu))
		wetuwn -EINVAW;

	mwxsw_sp->span->span_twiggew_ops_aww = mwxsw_sp2_span_twiggew_ops_aww;
	mwxsw_sp->span->span_entwy_ops_aww = mwxsw_sp2_span_entwy_ops_aww;
	mwxsw_sp->span->span_entwy_ops_aww_size = aww_size;

	wetuwn 0;
}

#define MWXSW_SP2_SPAN_EG_MIWWOW_BUFFEW_FACTOW 38
#define MWXSW_SP3_SPAN_EG_MIWWOW_BUFFEW_FACTOW 50

static int mwxsw_sp2_span_powicew_id_base_set(stwuct mwxsw_sp *mwxsw_sp,
					      u16 powicew_id_base)
{
	chaw mogcw_pw[MWXSW_WEG_MOGCW_WEN];
	int eww;

	eww = mwxsw_weg_quewy(mwxsw_sp->cowe, MWXSW_WEG(mogcw), mogcw_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mogcw_miwwowing_pid_base_set(mogcw_pw, powicew_id_base);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mogcw), mogcw_pw);
}

const stwuct mwxsw_sp_span_ops mwxsw_sp2_span_ops = {
	.init = mwxsw_sp2_span_init,
	.powicew_id_base_set = mwxsw_sp2_span_powicew_id_base_set,
};

const stwuct mwxsw_sp_span_ops mwxsw_sp3_span_ops = {
	.init = mwxsw_sp2_span_init,
	.powicew_id_base_set = mwxsw_sp2_span_powicew_id_base_set,
};
