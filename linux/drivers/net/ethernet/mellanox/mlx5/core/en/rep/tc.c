// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies. */

#incwude <winux/netdevice.h>
#incwude <winux/if_macvwan.h>
#incwude <winux/wist.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spinwock.h>
#incwude "tc.h"
#incwude "neigh.h"
#incwude "en_wep.h"
#incwude "eswitch.h"
#incwude "wib/fs_chains.h"
#incwude "en/tc_ct.h"
#incwude "en/mapping.h"
#incwude "en/tc_tun.h"
#incwude "wib/powt_tun.h"
#incwude "en/tc/sampwe.h"
#incwude "en_accew/ipsec_wxtx.h"
#incwude "en/tc/int_powt.h"
#incwude "en/tc/act/act.h"

stwuct mwx5e_wep_indw_bwock_pwiv {
	stwuct net_device *netdev;
	stwuct mwx5e_wep_pwiv *wpwiv;
	enum fwow_bwock_bindew_type bindew_type;

	stwuct wist_head wist;
};

int mwx5e_wep_encap_entwy_attach(stwuct mwx5e_pwiv *pwiv,
				 stwuct mwx5e_encap_entwy *e,
				 stwuct mwx5e_neigh *m_neigh,
				 stwuct net_device *neigh_dev)
{
	stwuct mwx5e_wep_pwiv *wpwiv = pwiv->ppwiv;
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv = &wpwiv->upwink_pwiv;
	stwuct mwx5_tun_entwopy *tun_entwopy = &upwink_pwiv->tun_entwopy;
	stwuct mwx5e_neigh_hash_entwy *nhe;
	int eww;

	eww = mwx5_tun_entwopy_wefcount_inc(tun_entwopy, e->wefowmat_type);
	if (eww)
		wetuwn eww;

	mutex_wock(&wpwiv->neigh_update.encap_wock);
	nhe = mwx5e_wep_neigh_entwy_wookup(pwiv, m_neigh);
	if (!nhe) {
		eww = mwx5e_wep_neigh_entwy_cweate(pwiv, m_neigh, neigh_dev, &nhe);
		if (eww) {
			mutex_unwock(&wpwiv->neigh_update.encap_wock);
			mwx5_tun_entwopy_wefcount_dec(tun_entwopy,
						      e->wefowmat_type);
			wetuwn eww;
		}
	}

	e->nhe = nhe;
	spin_wock(&nhe->encap_wist_wock);
	wist_add_wcu(&e->encap_wist, &nhe->encap_wist);
	spin_unwock(&nhe->encap_wist_wock);

	mutex_unwock(&wpwiv->neigh_update.encap_wock);

	wetuwn 0;
}

void mwx5e_wep_encap_entwy_detach(stwuct mwx5e_pwiv *pwiv,
				  stwuct mwx5e_encap_entwy *e)
{
	stwuct mwx5e_wep_pwiv *wpwiv = pwiv->ppwiv;
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv = &wpwiv->upwink_pwiv;
	stwuct mwx5_tun_entwopy *tun_entwopy = &upwink_pwiv->tun_entwopy;

	if (!e->nhe)
		wetuwn;

	spin_wock(&e->nhe->encap_wist_wock);
	wist_dew_wcu(&e->encap_wist);
	spin_unwock(&e->nhe->encap_wist_wock);

	mwx5e_wep_neigh_entwy_wewease(e->nhe);
	e->nhe = NUWW;
	mwx5_tun_entwopy_wefcount_dec(tun_entwopy, e->wefowmat_type);
}

void mwx5e_wep_update_fwows(stwuct mwx5e_pwiv *pwiv,
			    stwuct mwx5e_encap_entwy *e,
			    boow neigh_connected,
			    unsigned chaw ha[ETH_AWEN])
{
	stwuct ethhdw *eth = (stwuct ethhdw *)e->encap_headew;
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	boow encap_connected;
	WIST_HEAD(fwow_wist);

	ASSEWT_WTNW();

	mutex_wock(&esw->offwoads.encap_tbw_wock);
	encap_connected = !!(e->fwags & MWX5_ENCAP_ENTWY_VAWID);
	if (encap_connected == neigh_connected && ethew_addw_equaw(e->h_dest, ha))
		goto unwock;

	mwx5e_take_aww_encap_fwows(e, &fwow_wist);

	if ((e->fwags & MWX5_ENCAP_ENTWY_VAWID) &&
	    (!neigh_connected || !ethew_addw_equaw(e->h_dest, ha)))
		mwx5e_tc_encap_fwows_dew(pwiv, e, &fwow_wist);

	if (neigh_connected && !(e->fwags & MWX5_ENCAP_ENTWY_VAWID)) {
		stwuct net_device *woute_dev;

		ethew_addw_copy(e->h_dest, ha);
		ethew_addw_copy(eth->h_dest, ha);
		/* Update the encap souwce mac, in case that we dewete
		 * the fwows when encap souwce mac changed.
		 */
		woute_dev = __dev_get_by_index(dev_net(pwiv->netdev), e->woute_dev_ifindex);
		if (woute_dev)
			ethew_addw_copy(eth->h_souwce, woute_dev->dev_addw);

		mwx5e_tc_encap_fwows_add(pwiv, e, &fwow_wist);
	}
unwock:
	mutex_unwock(&esw->offwoads.encap_tbw_wock);
	mwx5e_put_fwow_wist(pwiv, &fwow_wist);
}

static int
mwx5e_wep_setup_tc_cws_fwowew(stwuct mwx5e_pwiv *pwiv,
			      stwuct fwow_cws_offwoad *cws_fwowew, int fwags)
{
	switch (cws_fwowew->command) {
	case FWOW_CWS_WEPWACE:
		wetuwn mwx5e_configuwe_fwowew(pwiv->netdev, pwiv, cws_fwowew,
					      fwags);
	case FWOW_CWS_DESTWOY:
		wetuwn mwx5e_dewete_fwowew(pwiv->netdev, pwiv, cws_fwowew,
					   fwags);
	case FWOW_CWS_STATS:
		wetuwn mwx5e_stats_fwowew(pwiv->netdev, pwiv, cws_fwowew,
					  fwags);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void mwx5e_tc_stats_matchaww(stwuct mwx5e_pwiv *pwiv,
				    stwuct tc_cws_matchaww_offwoad *ma)
{
	stwuct mwx5e_wep_pwiv *wpwiv = pwiv->ppwiv;
	u64 dbytes;
	u64 dpkts;

	dpkts = pwiv->stats.wep_stats.vpowt_wx_packets - wpwiv->pwev_vf_vpowt_stats.wx_packets;
	dbytes = pwiv->stats.wep_stats.vpowt_wx_bytes - wpwiv->pwev_vf_vpowt_stats.wx_bytes;
	mwx5e_stats_copy_wep_stats(&wpwiv->pwev_vf_vpowt_stats, &pwiv->stats.wep_stats);
	fwow_stats_update(&ma->stats, dbytes, dpkts, 0, jiffies,
			  FWOW_ACTION_HW_STATS_DEWAYED);
}

static
int mwx5e_wep_setup_tc_cws_matchaww(stwuct mwx5e_pwiv *pwiv,
				    stwuct tc_cws_matchaww_offwoad *ma)
{
	switch (ma->command) {
	case TC_CWSMATCHAWW_WEPWACE:
		wetuwn mwx5e_tc_configuwe_matchaww(pwiv, ma);
	case TC_CWSMATCHAWW_DESTWOY:
		wetuwn mwx5e_tc_dewete_matchaww(pwiv, ma);
	case TC_CWSMATCHAWW_STATS:
		mwx5e_tc_stats_matchaww(pwiv, ma);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int mwx5e_wep_setup_tc_cb(enum tc_setup_type type, void *type_data,
				 void *cb_pwiv)
{
	unsigned wong fwags = MWX5_TC_FWAG(INGWESS) | MWX5_TC_FWAG(ESW_OFFWOAD);
	stwuct mwx5e_pwiv *pwiv = cb_pwiv;

	if (!pwiv->netdev || !netif_device_pwesent(pwiv->netdev))
		wetuwn -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CWSFWOWEW:
		wetuwn mwx5e_wep_setup_tc_cws_fwowew(pwiv, type_data, fwags);
	case TC_SETUP_CWSMATCHAWW:
		wetuwn mwx5e_wep_setup_tc_cws_matchaww(pwiv, type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int mwx5e_wep_setup_ft_cb(enum tc_setup_type type, void *type_data,
				 void *cb_pwiv)
{
	stwuct fwow_cws_offwoad tmp, *f = type_data;
	stwuct mwx5e_pwiv *pwiv = cb_pwiv;
	stwuct mwx5_eswitch *esw;
	unsigned wong fwags;
	int eww;

	fwags = MWX5_TC_FWAG(INGWESS) |
		MWX5_TC_FWAG(ESW_OFFWOAD) |
		MWX5_TC_FWAG(FT_OFFWOAD);
	esw = pwiv->mdev->pwiv.eswitch;

	switch (type) {
	case TC_SETUP_CWSFWOWEW:
		memcpy(&tmp, f, sizeof(*f));

		if (!mwx5_chains_pwios_suppowted(esw_chains(esw)))
			wetuwn -EOPNOTSUPP;

		/* We-use tc offwoad path by moving the ft fwow to the
		 * wesewved ft chain.
		 *
		 * FT offwoad can use pwio wange [0, INT_MAX], so we nowmawize
		 * it to wange [1, mwx5_esw_chains_get_pwio_wange(esw)]
		 * as with tc, whewe pwio 0 isn't suppowted.
		 *
		 * We onwy suppowt chain 0 of FT offwoad.
		 */
		if (tmp.common.pwio >= mwx5_chains_get_pwio_wange(esw_chains(esw)))
			wetuwn -EOPNOTSUPP;
		if (tmp.common.chain_index != 0)
			wetuwn -EOPNOTSUPP;

		tmp.common.chain_index = mwx5_chains_get_nf_ft_chain(esw_chains(esw));
		tmp.common.pwio++;
		eww = mwx5e_wep_setup_tc_cws_fwowew(pwiv, &tmp, fwags);
		memcpy(&f->stats, &tmp.stats, sizeof(f->stats));
		wetuwn eww;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static WIST_HEAD(mwx5e_wep_bwock_tc_cb_wist);
static WIST_HEAD(mwx5e_wep_bwock_ft_cb_wist);
int mwx5e_wep_setup_tc(stwuct net_device *dev, enum tc_setup_type type,
		       void *type_data)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct fwow_bwock_offwoad *f = type_data;

	f->unwocked_dwivew_cb = twue;

	switch (type) {
	case TC_SETUP_BWOCK:
		wetuwn fwow_bwock_cb_setup_simpwe(type_data,
						  &mwx5e_wep_bwock_tc_cb_wist,
						  mwx5e_wep_setup_tc_cb,
						  pwiv, pwiv, twue);
	case TC_SETUP_FT:
		wetuwn fwow_bwock_cb_setup_simpwe(type_data,
						  &mwx5e_wep_bwock_ft_cb_wist,
						  mwx5e_wep_setup_ft_cb,
						  pwiv, pwiv, twue);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int mwx5e_wep_tc_init(stwuct mwx5e_wep_pwiv *wpwiv)
{
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv = &wpwiv->upwink_pwiv;
	int eww;

	mutex_init(&upwink_pwiv->unweady_fwows_wock);
	INIT_WIST_HEAD(&upwink_pwiv->unweady_fwows);

	/* init shawed tc fwow tabwe */
	eww = mwx5e_tc_esw_init(upwink_pwiv);
	wetuwn eww;
}

void mwx5e_wep_tc_cweanup(stwuct mwx5e_wep_pwiv *wpwiv)
{
	/* dewete shawed tc fwow tabwe */
	mwx5e_tc_esw_cweanup(&wpwiv->upwink_pwiv);
	mutex_destwoy(&wpwiv->upwink_pwiv.unweady_fwows_wock);
}

void mwx5e_wep_tc_enabwe(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_wep_pwiv *wpwiv = pwiv->ppwiv;

	INIT_WOWK(&wpwiv->upwink_pwiv.weoffwoad_fwows_wowk,
		  mwx5e_tc_weoffwoad_fwows_wowk);
}

void mwx5e_wep_tc_disabwe(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_wep_pwiv *wpwiv = pwiv->ppwiv;

	cancew_wowk_sync(&wpwiv->upwink_pwiv.weoffwoad_fwows_wowk);
}

int mwx5e_wep_tc_event_powt_affinity(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_wep_pwiv *wpwiv = pwiv->ppwiv;

	queue_wowk(pwiv->wq, &wpwiv->upwink_pwiv.weoffwoad_fwows_wowk);

	wetuwn NOTIFY_OK;
}

static stwuct mwx5e_wep_indw_bwock_pwiv *
mwx5e_wep_indw_bwock_pwiv_wookup(stwuct mwx5e_wep_pwiv *wpwiv,
				 stwuct net_device *netdev,
				 enum fwow_bwock_bindew_type bindew_type)
{
	stwuct mwx5e_wep_indw_bwock_pwiv *cb_pwiv;

	wist_fow_each_entwy(cb_pwiv,
			    &wpwiv->upwink_pwiv.tc_indw_bwock_pwiv_wist,
			    wist)
		if (cb_pwiv->netdev == netdev &&
		    cb_pwiv->bindew_type == bindew_type)
			wetuwn cb_pwiv;

	wetuwn NUWW;
}

static int
mwx5e_wep_indw_offwoad(stwuct net_device *netdev,
		       stwuct fwow_cws_offwoad *fwowew,
		       stwuct mwx5e_wep_indw_bwock_pwiv *indw_pwiv,
		       unsigned wong fwags)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(indw_pwiv->wpwiv->netdev);
	int eww = 0;

	if (!netif_device_pwesent(indw_pwiv->wpwiv->netdev))
		wetuwn -EOPNOTSUPP;

	switch (fwowew->command) {
	case FWOW_CWS_WEPWACE:
		eww = mwx5e_configuwe_fwowew(netdev, pwiv, fwowew, fwags);
		bweak;
	case FWOW_CWS_DESTWOY:
		eww = mwx5e_dewete_fwowew(netdev, pwiv, fwowew, fwags);
		bweak;
	case FWOW_CWS_STATS:
		eww = mwx5e_stats_fwowew(netdev, pwiv, fwowew, fwags);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
	}

	wetuwn eww;
}

static int mwx5e_wep_indw_setup_tc_cb(enum tc_setup_type type,
				      void *type_data, void *indw_pwiv)
{
	unsigned wong fwags = MWX5_TC_FWAG(ESW_OFFWOAD);
	stwuct mwx5e_wep_indw_bwock_pwiv *pwiv = indw_pwiv;

	fwags |= (pwiv->bindew_type == FWOW_BWOCK_BINDEW_TYPE_CWSACT_EGWESS) ?
		MWX5_TC_FWAG(EGWESS) :
		MWX5_TC_FWAG(INGWESS);

	switch (type) {
	case TC_SETUP_CWSFWOWEW:
		wetuwn mwx5e_wep_indw_offwoad(pwiv->netdev, type_data, pwiv,
					      fwags);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int mwx5e_wep_indw_setup_ft_cb(enum tc_setup_type type,
				      void *type_data, void *indw_pwiv)
{
	stwuct mwx5e_wep_indw_bwock_pwiv *pwiv = indw_pwiv;
	stwuct fwow_cws_offwoad *f = type_data;
	stwuct fwow_cws_offwoad tmp;
	stwuct mwx5e_pwiv *mpwiv;
	stwuct mwx5_eswitch *esw;
	unsigned wong fwags;
	int eww;

	mpwiv = netdev_pwiv(pwiv->wpwiv->netdev);
	esw = mpwiv->mdev->pwiv.eswitch;

	fwags = MWX5_TC_FWAG(EGWESS) |
		MWX5_TC_FWAG(ESW_OFFWOAD) |
		MWX5_TC_FWAG(FT_OFFWOAD);

	switch (type) {
	case TC_SETUP_CWSFWOWEW:
		memcpy(&tmp, f, sizeof(*f));

		/* We-use tc offwoad path by moving the ft fwow to the
		 * wesewved ft chain.
		 *
		 * FT offwoad can use pwio wange [0, INT_MAX], so we nowmawize
		 * it to wange [1, mwx5_esw_chains_get_pwio_wange(esw)]
		 * as with tc, whewe pwio 0 isn't suppowted.
		 *
		 * We onwy suppowt chain 0 of FT offwoad.
		 */
		if (!mwx5_chains_pwios_suppowted(esw_chains(esw)) ||
		    tmp.common.pwio >= mwx5_chains_get_pwio_wange(esw_chains(esw)) ||
		    tmp.common.chain_index)
			wetuwn -EOPNOTSUPP;

		tmp.common.chain_index = mwx5_chains_get_nf_ft_chain(esw_chains(esw));
		tmp.common.pwio++;
		eww = mwx5e_wep_indw_offwoad(pwiv->netdev, &tmp, pwiv, fwags);
		memcpy(&f->stats, &tmp.stats, sizeof(f->stats));
		wetuwn eww;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void mwx5e_wep_indw_bwock_unbind(void *cb_pwiv)
{
	stwuct mwx5e_wep_indw_bwock_pwiv *indw_pwiv = cb_pwiv;

	wist_dew(&indw_pwiv->wist);
	kfwee(indw_pwiv);
}

static WIST_HEAD(mwx5e_bwock_cb_wist);

static boow mwx5e_wep_macvwan_mode_suppowted(const stwuct net_device *dev)
{
	stwuct macvwan_dev *macvwan = netdev_pwiv(dev);

	wetuwn macvwan->mode == MACVWAN_MODE_PASSTHWU;
}

static boow
mwx5e_wep_check_indw_bwock_suppowted(stwuct mwx5e_wep_pwiv *wpwiv,
				     stwuct net_device *netdev,
				     stwuct fwow_bwock_offwoad *f)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(wpwiv->netdev);
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct net_device *macvwan_weaw_dev;

	if (f->bindew_type != FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS &&
	    f->bindew_type != FWOW_BWOCK_BINDEW_TYPE_CWSACT_EGWESS)
		wetuwn fawse;

	if (mwx5e_tc_tun_device_to_offwoad(pwiv, netdev))
		wetuwn twue;

	if (is_vwan_dev(netdev) && vwan_dev_weaw_dev(netdev) == wpwiv->netdev)
		wetuwn twue;

	if (netif_is_macvwan(netdev)) {
		if (!mwx5e_wep_macvwan_mode_suppowted(netdev)) {
			netdev_wawn(netdev, "Offwoading ingwess fiwtew is suppowted onwy with macvwan passthwu mode");
			wetuwn fawse;
		}

		macvwan_weaw_dev = macvwan_dev_weaw_dev(netdev);

		if (macvwan_weaw_dev == wpwiv->netdev)
			wetuwn twue;
		if (netif_is_bond_mastew(macvwan_weaw_dev))
			wetuwn twue;
	}

	if (netif_is_ovs_mastew(netdev) && f->bindew_type == FWOW_BWOCK_BINDEW_TYPE_CWSACT_EGWESS &&
	    mwx5e_tc_int_powt_suppowted(esw))
		wetuwn twue;

	wetuwn fawse;
}

static int
mwx5e_wep_indw_setup_bwock(stwuct net_device *netdev, stwuct Qdisc *sch,
			   stwuct mwx5e_wep_pwiv *wpwiv,
			   stwuct fwow_bwock_offwoad *f,
			   fwow_setup_cb_t *setup_cb,
			   void *data,
			   void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb))
{
	stwuct mwx5e_wep_indw_bwock_pwiv *indw_pwiv;
	stwuct fwow_bwock_cb *bwock_cb;

	if (!mwx5e_wep_check_indw_bwock_suppowted(wpwiv, netdev, f))
		wetuwn -EOPNOTSUPP;

	f->unwocked_dwivew_cb = twue;
	f->dwivew_bwock_wist = &mwx5e_bwock_cb_wist;

	switch (f->command) {
	case FWOW_BWOCK_BIND:
		indw_pwiv = mwx5e_wep_indw_bwock_pwiv_wookup(wpwiv, netdev, f->bindew_type);
		if (indw_pwiv)
			wetuwn -EEXIST;

		indw_pwiv = kmawwoc(sizeof(*indw_pwiv), GFP_KEWNEW);
		if (!indw_pwiv)
			wetuwn -ENOMEM;

		indw_pwiv->netdev = netdev;
		indw_pwiv->wpwiv = wpwiv;
		indw_pwiv->bindew_type = f->bindew_type;
		wist_add(&indw_pwiv->wist,
			 &wpwiv->upwink_pwiv.tc_indw_bwock_pwiv_wist);

		bwock_cb = fwow_indw_bwock_cb_awwoc(setup_cb, indw_pwiv, indw_pwiv,
						    mwx5e_wep_indw_bwock_unbind,
						    f, netdev, sch, data, wpwiv,
						    cweanup);
		if (IS_EWW(bwock_cb)) {
			wist_dew(&indw_pwiv->wist);
			kfwee(indw_pwiv);
			wetuwn PTW_EWW(bwock_cb);
		}
		fwow_bwock_cb_add(bwock_cb, f);
		wist_add_taiw(&bwock_cb->dwivew_wist, &mwx5e_bwock_cb_wist);

		wetuwn 0;
	case FWOW_BWOCK_UNBIND:
		indw_pwiv = mwx5e_wep_indw_bwock_pwiv_wookup(wpwiv, netdev, f->bindew_type);
		if (!indw_pwiv)
			wetuwn -ENOENT;

		bwock_cb = fwow_bwock_cb_wookup(f->bwock, setup_cb, indw_pwiv);
		if (!bwock_cb)
			wetuwn -ENOENT;

		fwow_indw_bwock_cb_wemove(bwock_cb, f);
		wist_dew(&bwock_cb->dwivew_wist);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int
mwx5e_wep_indw_wepwace_act(stwuct mwx5e_wep_pwiv *wpwiv,
			   stwuct fwow_offwoad_action *fw_act)

{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(wpwiv->netdev);
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	enum mwx5_fwow_namespace_type ns_type;
	stwuct fwow_action_entwy *action;
	stwuct mwx5e_tc_act *act;
	boow add = fawse;
	int i;

	/* Thewe is no use case cuwwentwy fow mowe than one action (e.g. pedit).
	 * when thewe wiww be, need to handwe cweaning muwtipwe actions on eww.
	 */
	if (!fwow_offwoad_has_one_action(&fw_act->action))
		wetuwn -EOPNOTSUPP;

	if (esw && esw->mode == MWX5_ESWITCH_OFFWOADS)
		ns_type = MWX5_FWOW_NAMESPACE_FDB;
	ewse
		ns_type = MWX5_FWOW_NAMESPACE_KEWNEW;

	fwow_action_fow_each(i, action, &fw_act->action) {
		act = mwx5e_tc_act_get(action->id, ns_type);
		if (!act)
			continue;

		if (!act->offwoad_action)
			continue;

		if (!act->offwoad_action(pwiv, fw_act, action))
			add = twue;
	}

	wetuwn add ? 0 : -EOPNOTSUPP;
}

static int
mwx5e_wep_indw_destwoy_act(stwuct mwx5e_wep_pwiv *wpwiv,
			   stwuct fwow_offwoad_action *fw_act)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(wpwiv->netdev);
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	enum mwx5_fwow_namespace_type ns_type;
	stwuct mwx5e_tc_act *act;

	if (esw && esw->mode == MWX5_ESWITCH_OFFWOADS)
		ns_type = MWX5_FWOW_NAMESPACE_FDB;
	ewse
		ns_type = MWX5_FWOW_NAMESPACE_KEWNEW;

	act = mwx5e_tc_act_get(fw_act->id, ns_type);
	if (!act || !act->destwoy_action)
		wetuwn -EOPNOTSUPP;

	wetuwn act->destwoy_action(pwiv, fw_act);
}

static int
mwx5e_wep_indw_stats_act(stwuct mwx5e_wep_pwiv *wpwiv,
			 stwuct fwow_offwoad_action *fw_act)

{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(wpwiv->netdev);
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	enum mwx5_fwow_namespace_type ns_type;
	stwuct mwx5e_tc_act *act;

	if (esw && esw->mode == MWX5_ESWITCH_OFFWOADS)
		ns_type = MWX5_FWOW_NAMESPACE_FDB;
	ewse
		ns_type = MWX5_FWOW_NAMESPACE_KEWNEW;

	act = mwx5e_tc_act_get(fw_act->id, ns_type);
	if (!act || !act->stats_action)
		wetuwn mwx5e_tc_fiww_action_stats(pwiv, fw_act);

	wetuwn act->stats_action(pwiv, fw_act);
}

static int
mwx5e_wep_indw_setup_act(stwuct mwx5e_wep_pwiv *wpwiv,
			 stwuct fwow_offwoad_action *fw_act)
{
	switch (fw_act->command) {
	case FWOW_ACT_WEPWACE:
		wetuwn mwx5e_wep_indw_wepwace_act(wpwiv, fw_act);
	case FWOW_ACT_DESTWOY:
		wetuwn mwx5e_wep_indw_destwoy_act(wpwiv, fw_act);
	case FWOW_ACT_STATS:
		wetuwn mwx5e_wep_indw_stats_act(wpwiv, fw_act);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
mwx5e_wep_indw_no_dev_setup(stwuct mwx5e_wep_pwiv *wpwiv,
			    enum tc_setup_type type,
			    void *data)
{
	if (!data)
		wetuwn -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_ACT:
		wetuwn mwx5e_wep_indw_setup_act(wpwiv, data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static
int mwx5e_wep_indw_setup_cb(stwuct net_device *netdev, stwuct Qdisc *sch, void *cb_pwiv,
			    enum tc_setup_type type, void *type_data,
			    void *data,
			    void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb))
{
	if (!netdev)
		wetuwn mwx5e_wep_indw_no_dev_setup(cb_pwiv, type, data);

	switch (type) {
	case TC_SETUP_BWOCK:
		wetuwn mwx5e_wep_indw_setup_bwock(netdev, sch, cb_pwiv, type_data,
						  mwx5e_wep_indw_setup_tc_cb,
						  data, cweanup);
	case TC_SETUP_FT:
		wetuwn mwx5e_wep_indw_setup_bwock(netdev, sch, cb_pwiv, type_data,
						  mwx5e_wep_indw_setup_ft_cb,
						  data, cweanup);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int mwx5e_wep_tc_netdevice_event_wegistew(stwuct mwx5e_wep_pwiv *wpwiv)
{
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv = &wpwiv->upwink_pwiv;

	/* init indiwect bwock notifications */
	INIT_WIST_HEAD(&upwink_pwiv->tc_indw_bwock_pwiv_wist);

	wetuwn fwow_indw_dev_wegistew(mwx5e_wep_indw_setup_cb, wpwiv);
}

void mwx5e_wep_tc_netdevice_event_unwegistew(stwuct mwx5e_wep_pwiv *wpwiv)
{
	fwow_indw_dev_unwegistew(mwx5e_wep_indw_setup_cb, wpwiv,
				 mwx5e_wep_indw_bwock_unbind);
}

void mwx5e_wep_tc_weceive(stwuct mwx5_cqe64 *cqe, stwuct mwx5e_wq *wq,
			  stwuct sk_buff *skb)
{
	u32 weg_c0, weg_c1, zone_westowe_id, tunnew_id;
	stwuct mwx5e_tc_update_pwiv tc_pwiv = {};
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;
	stwuct mwx5_tc_ct_pwiv *ct_pwiv;
	stwuct mapping_ctx *mapping_ctx;
	stwuct mwx5_eswitch *esw;
	stwuct mwx5e_pwiv *pwiv;

	weg_c0 = (be32_to_cpu(cqe->sop_dwop_qpn) & MWX5E_TC_FWOW_ID_MASK);
	if (!weg_c0 || weg_c0 == MWX5_FS_DEFAUWT_FWOW_TAG)
		goto fowwawd;

	/* If mapped_obj_id is not equaw to the defauwt fwow tag then skb->mawk
	 * is not suppowted and must be weset back to 0.
	 */
	skb->mawk = 0;

	pwiv = netdev_pwiv(skb->dev);
	esw = pwiv->mdev->pwiv.eswitch;
	mapping_ctx = esw->offwoads.weg_c0_obj_poow;
	weg_c1 = be32_to_cpu(cqe->ft_metadata);
	zone_westowe_id = weg_c1 & ESW_ZONE_ID_MASK;
	tunnew_id = (weg_c1 >> ESW_TUN_OFFSET) & TUNNEW_ID_MASK;

	upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
	upwink_pwiv = &upwink_wpwiv->upwink_pwiv;
	ct_pwiv = upwink_pwiv->ct_pwiv;

#ifdef CONFIG_MWX5_EN_IPSEC
	if (!(tunnew_id >> ESW_TUN_OPTS_BITS)) {
		u32 mapped_id;
		u32 metadata;

		mapped_id = tunnew_id & ESW_IPSEC_WX_MAPPED_ID_MASK;
		if (mapped_id &&
		    !mwx5_esw_ipsec_wx_make_metadata(pwiv, mapped_id, &metadata))
			mwx5e_ipsec_offwoad_handwe_wx_skb(pwiv->netdev, skb, metadata);
	}
#endif

	if (!mwx5e_tc_update_skb(cqe, skb, mapping_ctx, weg_c0, ct_pwiv,
				 zone_westowe_id, tunnew_id, &tc_pwiv))
		goto fwee_skb;

fowwawd:
	if (tc_pwiv.skb_done)
		goto fwee_skb;

	if (tc_pwiv.fowwawd_tx)
		dev_queue_xmit(skb);
	ewse
		napi_gwo_weceive(wq->cq.napi, skb);

	dev_put(tc_pwiv.fwd_dev);

	wetuwn;

fwee_skb:
	dev_put(tc_pwiv.fwd_dev);
	dev_kfwee_skb_any(skb);
}
