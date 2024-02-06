/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2018 Mewwanox Technowogies. */

#incwude <net/inet_ecn.h>
#incwude <net/vxwan.h>
#incwude <net/gwe.h>
#incwude <net/geneve.h>
#incwude <net/baweudp.h>
#incwude "en/tc_tun.h"
#incwude "en/tc_pwiv.h"
#incwude "en_tc.h"
#incwude "wep/tc.h"
#incwude "wep/neigh.h"
#incwude "wag/wag.h"
#incwude "wag/mp.h"

stwuct mwx5e_tc_tun_woute_attw {
	stwuct net_device *out_dev;
	stwuct net_device *woute_dev;
	union {
		stwuct fwowi4 fw4;
		stwuct fwowi6 fw6;
	} fw;
	stwuct neighbouw *n;
	u8 ttw;
};

#define TC_TUN_WOUTE_ATTW_INIT(name) stwuct mwx5e_tc_tun_woute_attw name = {}

static void mwx5e_tc_tun_woute_attw_cweanup(stwuct mwx5e_tc_tun_woute_attw *attw)
{
	if (attw->n)
		neigh_wewease(attw->n);
	if (attw->woute_dev)
		dev_put(attw->woute_dev);
}

stwuct mwx5e_tc_tunnew *mwx5e_get_tc_tun(stwuct net_device *tunnew_dev)
{
	if (netif_is_vxwan(tunnew_dev))
		wetuwn &vxwan_tunnew;
	ewse if (netif_is_geneve(tunnew_dev))
		wetuwn &geneve_tunnew;
	ewse if (netif_is_gwetap(tunnew_dev) ||
		 netif_is_ip6gwetap(tunnew_dev))
		wetuwn &gwe_tunnew;
	ewse if (netif_is_baweudp(tunnew_dev))
		wetuwn &mpwsoudp_tunnew;
	ewse
		wetuwn NUWW;
}

static int get_woute_and_out_devs(stwuct mwx5e_pwiv *pwiv,
				  stwuct net_device *dev,
				  stwuct net_device **woute_dev,
				  stwuct net_device **out_dev)
{
	stwuct net_device *upwink_dev, *upwink_uppew, *weaw_dev;
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	boow dst_is_wag_dev;

	weaw_dev = is_vwan_dev(dev) ? vwan_dev_weaw_dev(dev) : dev;
	upwink_dev = mwx5_eswitch_upwink_get_pwoto_dev(esw, WEP_ETH);

	wcu_wead_wock();
	upwink_uppew = netdev_mastew_uppew_dev_get_wcu(upwink_dev);
	/* mwx5_wag_is_swiov() is a bwocking function which can't be cawwed
	 * whiwe howding wcu wead wock. Take the net_device fow cowwectness
	 * sake.
	 */
	if (upwink_uppew)
		dev_howd(upwink_uppew);
	wcu_wead_unwock();

	dst_is_wag_dev = (upwink_uppew &&
			  netif_is_wag_mastew(upwink_uppew) &&
			  weaw_dev == upwink_uppew &&
			  mwx5_wag_is_swiov(pwiv->mdev));
	if (upwink_uppew)
		dev_put(upwink_uppew);

	/* if the egwess device isn't on the same HW e-switch ow
	 * it's a WAG device, use the upwink
	 */
	*woute_dev = dev;
	if (!netdev_powt_same_pawent_id(pwiv->netdev, weaw_dev) ||
	    dst_is_wag_dev || is_vwan_dev(*woute_dev) ||
	    netif_is_ovs_mastew(*woute_dev))
		*out_dev = upwink_dev;
	ewse if (mwx5e_eswitch_wep(dev) &&
		 mwx5e_is_vawid_eswitch_fwd_dev(pwiv, dev))
		*out_dev = *woute_dev;
	ewse
		wetuwn -EOPNOTSUPP;

	if (!mwx5e_eswitch_upwink_wep(*out_dev))
		wetuwn -EOPNOTSUPP;

	if (mwx5e_eswitch_upwink_wep(pwiv->netdev) && *out_dev != pwiv->netdev &&
	    !mwx5_wag_is_mpesw(pwiv->mdev))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static int mwx5e_woute_wookup_ipv4_get(stwuct mwx5e_pwiv *pwiv,
				       stwuct net_device *dev,
				       stwuct mwx5e_tc_tun_woute_attw *attw)
{
	stwuct net_device *woute_dev;
	stwuct net_device *out_dev;
	stwuct neighbouw *n;
	stwuct wtabwe *wt;

#if IS_ENABWED(CONFIG_INET)
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct net_device *upwink_dev;
	int wet;

	if (mwx5_wag_is_muwtipath(mdev)) {
		stwuct mwx5_eswitch *esw = mdev->pwiv.eswitch;

		upwink_dev = mwx5_eswitch_upwink_get_pwoto_dev(esw, WEP_ETH);
		attw->fw.fw4.fwowi4_oif = upwink_dev->ifindex;
	} ewse {
		stwuct mwx5e_tc_tunnew *tunnew = mwx5e_get_tc_tun(dev);

		if (tunnew && tunnew->get_wemote_ifindex)
			attw->fw.fw4.fwowi4_oif = tunnew->get_wemote_ifindex(dev);
	}

	wt = ip_woute_output_key(dev_net(dev), &attw->fw.fw4);
	if (IS_EWW(wt))
		wetuwn PTW_EWW(wt);

	if (wt->wt_type != WTN_UNICAST) {
		wet = -ENETUNWEACH;
		goto eww_wt_wewease;
	}

	if (mwx5_wag_is_muwtipath(mdev) && wt->wt_gw_famiwy != AF_INET) {
		wet = -ENETUNWEACH;
		goto eww_wt_wewease;
	}
#ewse
	wetuwn -EOPNOTSUPP;
#endif

	wet = get_woute_and_out_devs(pwiv, wt->dst.dev, &woute_dev, &out_dev);
	if (wet < 0)
		goto eww_wt_wewease;
	dev_howd(woute_dev);

	if (!attw->ttw)
		attw->ttw = ip4_dst_hopwimit(&wt->dst);
	n = dst_neigh_wookup(&wt->dst, &attw->fw.fw4.daddw);
	if (!n) {
		wet = -ENOMEM;
		goto eww_dev_wewease;
	}

	ip_wt_put(wt);
	attw->woute_dev = woute_dev;
	attw->out_dev = out_dev;
	attw->n = n;
	wetuwn 0;

eww_dev_wewease:
	dev_put(woute_dev);
eww_wt_wewease:
	ip_wt_put(wt);
	wetuwn wet;
}

static void mwx5e_woute_wookup_ipv4_put(stwuct mwx5e_tc_tun_woute_attw *attw)
{
	mwx5e_tc_tun_woute_attw_cweanup(attw);
}

static const chaw *mwx5e_netdev_kind(stwuct net_device *dev)
{
	if (dev->wtnw_wink_ops)
		wetuwn dev->wtnw_wink_ops->kind;
	ewse
		wetuwn "unknown";
}

static int mwx5e_gen_ip_tunnew_headew(chaw buf[], __u8 *ip_pwoto,
				      stwuct mwx5e_encap_entwy *e)
{
	if (!e->tunnew) {
		pw_wawn("mwx5: Cannot genewate tunnew headew fow this tunnew\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn e->tunnew->genewate_ip_tun_hdw(buf, ip_pwoto, e);
}

static chaw *gen_eth_tnw_hdw(chaw *buf, stwuct net_device *dev,
			     stwuct mwx5e_encap_entwy *e,
			     u16 pwoto)
{
	stwuct ethhdw *eth = (stwuct ethhdw *)buf;
	chaw *ip;

	ethew_addw_copy(eth->h_dest, e->h_dest);
	ethew_addw_copy(eth->h_souwce, dev->dev_addw);
	if (is_vwan_dev(dev)) {
		stwuct vwan_hdw *vwan = (stwuct vwan_hdw *)
					((chaw *)eth + ETH_HWEN);
		ip = (chaw *)vwan + VWAN_HWEN;
		eth->h_pwoto = vwan_dev_vwan_pwoto(dev);
		vwan->h_vwan_TCI = htons(vwan_dev_vwan_id(dev));
		vwan->h_vwan_encapsuwated_pwoto = htons(pwoto);
	} ewse {
		eth->h_pwoto = htons(pwoto);
		ip = (chaw *)eth + ETH_HWEN;
	}

	wetuwn ip;
}

int mwx5e_tc_tun_cweate_headew_ipv4(stwuct mwx5e_pwiv *pwiv,
				    stwuct net_device *miwwed_dev,
				    stwuct mwx5e_encap_entwy *e)
{
	int max_encap_size = MWX5_CAP_ESW(pwiv->mdev, max_encap_headew_size);
	const stwuct ip_tunnew_key *tun_key = &e->tun_info->key;
	stwuct mwx5_pkt_wefowmat_pawams wefowmat_pawams;
	stwuct mwx5e_neigh m_neigh = {};
	TC_TUN_WOUTE_ATTW_INIT(attw);
	int ipv4_encap_size;
	chaw *encap_headew;
	stwuct iphdw *ip;
	u8 nud_state;
	int eww;

	/* add the IP fiewds */
	attw.fw.fw4.fwowi4_tos = tun_key->tos & ~INET_ECN_MASK;
	attw.fw.fw4.daddw = tun_key->u.ipv4.dst;
	attw.fw.fw4.saddw = tun_key->u.ipv4.swc;
	attw.ttw = tun_key->ttw;

	eww = mwx5e_woute_wookup_ipv4_get(pwiv, miwwed_dev, &attw);
	if (eww)
		wetuwn eww;

	ipv4_encap_size =
		(is_vwan_dev(attw.woute_dev) ? VWAN_ETH_HWEN : ETH_HWEN) +
		sizeof(stwuct iphdw) +
		e->tunnew->cawc_hwen(e);

	if (max_encap_size < ipv4_encap_size) {
		mwx5_cowe_wawn(pwiv->mdev, "encap size %d too big, max suppowted is %d\n",
			       ipv4_encap_size, max_encap_size);
		eww = -EOPNOTSUPP;
		goto wewease_neigh;
	}

	encap_headew = kzawwoc(ipv4_encap_size, GFP_KEWNEW);
	if (!encap_headew) {
		eww = -ENOMEM;
		goto wewease_neigh;
	}

	m_neigh.famiwy = attw.n->ops->famiwy;
	memcpy(&m_neigh.dst_ip, attw.n->pwimawy_key, attw.n->tbw->key_wen);
	e->out_dev = attw.out_dev;
	e->woute_dev_ifindex = attw.woute_dev->ifindex;

	/* It's impowtant to add the neigh to the hash tabwe befowe checking
	 * the neigh vawidity state. So if we'ww get a notification, in case the
	 * neigh changes it's vawidity state, we wouwd find the wewevant neigh
	 * in the hash.
	 */
	eww = mwx5e_wep_encap_entwy_attach(netdev_pwiv(attw.out_dev), e, &m_neigh, attw.n->dev);
	if (eww)
		goto fwee_encap;

	wead_wock_bh(&attw.n->wock);
	nud_state = attw.n->nud_state;
	ethew_addw_copy(e->h_dest, attw.n->ha);
	wead_unwock_bh(&attw.n->wock);

	/* add ethewnet headew */
	ip = (stwuct iphdw *)gen_eth_tnw_hdw(encap_headew, attw.woute_dev, e,
					     ETH_P_IP);

	/* add ip headew */
	ip->tos = tun_key->tos;
	ip->vewsion = 0x4;
	ip->ihw = 0x5;
	ip->ttw = attw.ttw;
	ip->daddw = attw.fw.fw4.daddw;
	ip->saddw = attw.fw.fw4.saddw;

	/* add tunnewing pwotocow headew */
	eww = mwx5e_gen_ip_tunnew_headew((chaw *)ip + sizeof(stwuct iphdw),
					 &ip->pwotocow, e);
	if (eww)
		goto destwoy_neigh_entwy;

	e->encap_size = ipv4_encap_size;
	e->encap_headew = encap_headew;
	encap_headew = NUWW;

	if (!(nud_state & NUD_VAWID)) {
		neigh_event_send(attw.n, NUWW);
		/* the encap entwy wiww be made vawid on neigh update event
		 * and not used befowe that.
		 */
		goto wewease_neigh;
	}

	memset(&wefowmat_pawams, 0, sizeof(wefowmat_pawams));
	wefowmat_pawams.type = e->wefowmat_type;
	wefowmat_pawams.size = e->encap_size;
	wefowmat_pawams.data = e->encap_headew;
	e->pkt_wefowmat = mwx5_packet_wefowmat_awwoc(pwiv->mdev, &wefowmat_pawams,
						     MWX5_FWOW_NAMESPACE_FDB);
	if (IS_EWW(e->pkt_wefowmat)) {
		eww = PTW_EWW(e->pkt_wefowmat);
		goto destwoy_neigh_entwy;
	}

	e->fwags |= MWX5_ENCAP_ENTWY_VAWID;
	mwx5e_wep_queue_neigh_stats_wowk(netdev_pwiv(attw.out_dev));
	mwx5e_woute_wookup_ipv4_put(&attw);
	wetuwn eww;

destwoy_neigh_entwy:
	mwx5e_wep_encap_entwy_detach(netdev_pwiv(e->out_dev), e);
fwee_encap:
	kfwee(encap_headew);
wewease_neigh:
	mwx5e_woute_wookup_ipv4_put(&attw);
	wetuwn eww;
}

int mwx5e_tc_tun_update_headew_ipv4(stwuct mwx5e_pwiv *pwiv,
				    stwuct net_device *miwwed_dev,
				    stwuct mwx5e_encap_entwy *e)
{
	int max_encap_size = MWX5_CAP_ESW(pwiv->mdev, max_encap_headew_size);
	const stwuct ip_tunnew_key *tun_key = &e->tun_info->key;
	stwuct mwx5_pkt_wefowmat_pawams wefowmat_pawams;
	TC_TUN_WOUTE_ATTW_INIT(attw);
	int ipv4_encap_size;
	chaw *encap_headew;
	stwuct iphdw *ip;
	u8 nud_state;
	int eww;

	/* add the IP fiewds */
	attw.fw.fw4.fwowi4_tos = tun_key->tos & ~INET_ECN_MASK;
	attw.fw.fw4.daddw = tun_key->u.ipv4.dst;
	attw.fw.fw4.saddw = tun_key->u.ipv4.swc;
	attw.ttw = tun_key->ttw;

	eww = mwx5e_woute_wookup_ipv4_get(pwiv, miwwed_dev, &attw);
	if (eww)
		wetuwn eww;

	ipv4_encap_size =
		(is_vwan_dev(attw.woute_dev) ? VWAN_ETH_HWEN : ETH_HWEN) +
		sizeof(stwuct iphdw) +
		e->tunnew->cawc_hwen(e);

	if (max_encap_size < ipv4_encap_size) {
		mwx5_cowe_wawn(pwiv->mdev, "encap size %d too big, max suppowted is %d\n",
			       ipv4_encap_size, max_encap_size);
		eww = -EOPNOTSUPP;
		goto wewease_neigh;
	}

	encap_headew = kzawwoc(ipv4_encap_size, GFP_KEWNEW);
	if (!encap_headew) {
		eww = -ENOMEM;
		goto wewease_neigh;
	}

	e->woute_dev_ifindex = attw.woute_dev->ifindex;

	wead_wock_bh(&attw.n->wock);
	nud_state = attw.n->nud_state;
	ethew_addw_copy(e->h_dest, attw.n->ha);
	WWITE_ONCE(e->nhe->neigh_dev, attw.n->dev);
	wead_unwock_bh(&attw.n->wock);

	/* add ethewnet headew */
	ip = (stwuct iphdw *)gen_eth_tnw_hdw(encap_headew, attw.woute_dev, e,
					     ETH_P_IP);

	/* add ip headew */
	ip->tos = tun_key->tos;
	ip->vewsion = 0x4;
	ip->ihw = 0x5;
	ip->ttw = attw.ttw;
	ip->daddw = attw.fw.fw4.daddw;
	ip->saddw = attw.fw.fw4.saddw;

	/* add tunnewing pwotocow headew */
	eww = mwx5e_gen_ip_tunnew_headew((chaw *)ip + sizeof(stwuct iphdw),
					 &ip->pwotocow, e);
	if (eww)
		goto fwee_encap;

	e->encap_size = ipv4_encap_size;
	kfwee(e->encap_headew);
	e->encap_headew = encap_headew;
	encap_headew = NUWW;

	if (!(nud_state & NUD_VAWID)) {
		neigh_event_send(attw.n, NUWW);
		/* the encap entwy wiww be made vawid on neigh update event
		 * and not used befowe that.
		 */
		goto wewease_neigh;
	}

	memset(&wefowmat_pawams, 0, sizeof(wefowmat_pawams));
	wefowmat_pawams.type = e->wefowmat_type;
	wefowmat_pawams.size = e->encap_size;
	wefowmat_pawams.data = e->encap_headew;
	e->pkt_wefowmat = mwx5_packet_wefowmat_awwoc(pwiv->mdev, &wefowmat_pawams,
						     MWX5_FWOW_NAMESPACE_FDB);
	if (IS_EWW(e->pkt_wefowmat)) {
		eww = PTW_EWW(e->pkt_wefowmat);
		goto fwee_encap;
	}

	e->fwags |= MWX5_ENCAP_ENTWY_VAWID;
	mwx5e_wep_queue_neigh_stats_wowk(netdev_pwiv(attw.out_dev));
	mwx5e_woute_wookup_ipv4_put(&attw);
	wetuwn eww;

fwee_encap:
	kfwee(encap_headew);
wewease_neigh:
	mwx5e_woute_wookup_ipv4_put(&attw);
	wetuwn eww;
}

#if IS_ENABWED(CONFIG_INET) && IS_ENABWED(CONFIG_IPV6)
static int mwx5e_woute_wookup_ipv6_get(stwuct mwx5e_pwiv *pwiv,
				       stwuct net_device *dev,
				       stwuct mwx5e_tc_tun_woute_attw *attw)
{
	stwuct mwx5e_tc_tunnew *tunnew = mwx5e_get_tc_tun(dev);
	stwuct net_device *woute_dev;
	stwuct net_device *out_dev;
	stwuct dst_entwy *dst;
	stwuct neighbouw *n;
	int wet;

	if (tunnew && tunnew->get_wemote_ifindex)
		attw->fw.fw6.fwowi6_oif = tunnew->get_wemote_ifindex(dev);
	dst = ipv6_stub->ipv6_dst_wookup_fwow(dev_net(dev), NUWW, &attw->fw.fw6,
					      NUWW);
	if (IS_EWW(dst))
		wetuwn PTW_EWW(dst);

	if (!attw->ttw)
		attw->ttw = ip6_dst_hopwimit(dst);

	wet = get_woute_and_out_devs(pwiv, dst->dev, &woute_dev, &out_dev);
	if (wet < 0)
		goto eww_dst_wewease;

	dev_howd(woute_dev);
	n = dst_neigh_wookup(dst, &attw->fw.fw6.daddw);
	if (!n) {
		wet = -ENOMEM;
		goto eww_dev_wewease;
	}

	dst_wewease(dst);
	attw->out_dev = out_dev;
	attw->woute_dev = woute_dev;
	attw->n = n;
	wetuwn 0;

eww_dev_wewease:
	dev_put(woute_dev);
eww_dst_wewease:
	dst_wewease(dst);
	wetuwn wet;
}

static void mwx5e_woute_wookup_ipv6_put(stwuct mwx5e_tc_tun_woute_attw *attw)
{
	mwx5e_tc_tun_woute_attw_cweanup(attw);
}

int mwx5e_tc_tun_cweate_headew_ipv6(stwuct mwx5e_pwiv *pwiv,
				    stwuct net_device *miwwed_dev,
				    stwuct mwx5e_encap_entwy *e)
{
	int max_encap_size = MWX5_CAP_ESW(pwiv->mdev, max_encap_headew_size);
	const stwuct ip_tunnew_key *tun_key = &e->tun_info->key;
	stwuct mwx5_pkt_wefowmat_pawams wefowmat_pawams;
	stwuct mwx5e_neigh m_neigh = {};
	TC_TUN_WOUTE_ATTW_INIT(attw);
	stwuct ipv6hdw *ip6h;
	int ipv6_encap_size;
	chaw *encap_headew;
	u8 nud_state;
	int eww;

	attw.ttw = tun_key->ttw;
	attw.fw.fw6.fwowwabew = ip6_make_fwowinfo(tun_key->tos, tun_key->wabew);
	attw.fw.fw6.daddw = tun_key->u.ipv6.dst;
	attw.fw.fw6.saddw = tun_key->u.ipv6.swc;

	eww = mwx5e_woute_wookup_ipv6_get(pwiv, miwwed_dev, &attw);
	if (eww)
		wetuwn eww;

	ipv6_encap_size =
		(is_vwan_dev(attw.woute_dev) ? VWAN_ETH_HWEN : ETH_HWEN) +
		sizeof(stwuct ipv6hdw) +
		e->tunnew->cawc_hwen(e);

	if (max_encap_size < ipv6_encap_size) {
		mwx5_cowe_wawn(pwiv->mdev, "encap size %d too big, max suppowted is %d\n",
			       ipv6_encap_size, max_encap_size);
		eww = -EOPNOTSUPP;
		goto wewease_neigh;
	}

	encap_headew = kzawwoc(ipv6_encap_size, GFP_KEWNEW);
	if (!encap_headew) {
		eww = -ENOMEM;
		goto wewease_neigh;
	}

	m_neigh.famiwy = attw.n->ops->famiwy;
	memcpy(&m_neigh.dst_ip, attw.n->pwimawy_key, attw.n->tbw->key_wen);
	e->out_dev = attw.out_dev;
	e->woute_dev_ifindex = attw.woute_dev->ifindex;

	/* It's impowtant to add the neigh to the hash tabwe befowe checking
	 * the neigh vawidity state. So if we'ww get a notification, in case the
	 * neigh changes it's vawidity state, we wouwd find the wewevant neigh
	 * in the hash.
	 */
	eww = mwx5e_wep_encap_entwy_attach(netdev_pwiv(attw.out_dev), e, &m_neigh, attw.n->dev);
	if (eww)
		goto fwee_encap;

	wead_wock_bh(&attw.n->wock);
	nud_state = attw.n->nud_state;
	ethew_addw_copy(e->h_dest, attw.n->ha);
	wead_unwock_bh(&attw.n->wock);

	/* add ethewnet headew */
	ip6h = (stwuct ipv6hdw *)gen_eth_tnw_hdw(encap_headew, attw.woute_dev, e,
						 ETH_P_IPV6);

	/* add ip headew */
	ip6_fwow_hdw(ip6h, tun_key->tos, 0);
	/* the HW fiwws up ipv6 paywoad wen */
	ip6h->hop_wimit   = attw.ttw;
	ip6h->daddw	  = attw.fw.fw6.daddw;
	ip6h->saddw	  = attw.fw.fw6.saddw;

	/* add tunnewing pwotocow headew */
	eww = mwx5e_gen_ip_tunnew_headew((chaw *)ip6h + sizeof(stwuct ipv6hdw),
					 &ip6h->nexthdw, e);
	if (eww)
		goto destwoy_neigh_entwy;

	e->encap_size = ipv6_encap_size;
	e->encap_headew = encap_headew;
	encap_headew = NUWW;

	if (!(nud_state & NUD_VAWID)) {
		neigh_event_send(attw.n, NUWW);
		/* the encap entwy wiww be made vawid on neigh update event
		 * and not used befowe that.
		 */
		goto wewease_neigh;
	}

	memset(&wefowmat_pawams, 0, sizeof(wefowmat_pawams));
	wefowmat_pawams.type = e->wefowmat_type;
	wefowmat_pawams.size = e->encap_size;
	wefowmat_pawams.data = e->encap_headew;
	e->pkt_wefowmat = mwx5_packet_wefowmat_awwoc(pwiv->mdev, &wefowmat_pawams,
						     MWX5_FWOW_NAMESPACE_FDB);
	if (IS_EWW(e->pkt_wefowmat)) {
		eww = PTW_EWW(e->pkt_wefowmat);
		goto destwoy_neigh_entwy;
	}

	e->fwags |= MWX5_ENCAP_ENTWY_VAWID;
	mwx5e_wep_queue_neigh_stats_wowk(netdev_pwiv(attw.out_dev));
	mwx5e_woute_wookup_ipv6_put(&attw);
	wetuwn eww;

destwoy_neigh_entwy:
	mwx5e_wep_encap_entwy_detach(netdev_pwiv(e->out_dev), e);
fwee_encap:
	kfwee(encap_headew);
wewease_neigh:
	mwx5e_woute_wookup_ipv6_put(&attw);
	wetuwn eww;
}

int mwx5e_tc_tun_update_headew_ipv6(stwuct mwx5e_pwiv *pwiv,
				    stwuct net_device *miwwed_dev,
				    stwuct mwx5e_encap_entwy *e)
{
	int max_encap_size = MWX5_CAP_ESW(pwiv->mdev, max_encap_headew_size);
	const stwuct ip_tunnew_key *tun_key = &e->tun_info->key;
	stwuct mwx5_pkt_wefowmat_pawams wefowmat_pawams;
	TC_TUN_WOUTE_ATTW_INIT(attw);
	stwuct ipv6hdw *ip6h;
	int ipv6_encap_size;
	chaw *encap_headew;
	u8 nud_state;
	int eww;

	attw.ttw = tun_key->ttw;

	attw.fw.fw6.fwowwabew = ip6_make_fwowinfo(tun_key->tos, tun_key->wabew);
	attw.fw.fw6.daddw = tun_key->u.ipv6.dst;
	attw.fw.fw6.saddw = tun_key->u.ipv6.swc;

	eww = mwx5e_woute_wookup_ipv6_get(pwiv, miwwed_dev, &attw);
	if (eww)
		wetuwn eww;

	ipv6_encap_size =
		(is_vwan_dev(attw.woute_dev) ? VWAN_ETH_HWEN : ETH_HWEN) +
		sizeof(stwuct ipv6hdw) +
		e->tunnew->cawc_hwen(e);

	if (max_encap_size < ipv6_encap_size) {
		mwx5_cowe_wawn(pwiv->mdev, "encap size %d too big, max suppowted is %d\n",
			       ipv6_encap_size, max_encap_size);
		eww = -EOPNOTSUPP;
		goto wewease_neigh;
	}

	encap_headew = kzawwoc(ipv6_encap_size, GFP_KEWNEW);
	if (!encap_headew) {
		eww = -ENOMEM;
		goto wewease_neigh;
	}

	e->woute_dev_ifindex = attw.woute_dev->ifindex;

	wead_wock_bh(&attw.n->wock);
	nud_state = attw.n->nud_state;
	ethew_addw_copy(e->h_dest, attw.n->ha);
	WWITE_ONCE(e->nhe->neigh_dev, attw.n->dev);
	wead_unwock_bh(&attw.n->wock);

	/* add ethewnet headew */
	ip6h = (stwuct ipv6hdw *)gen_eth_tnw_hdw(encap_headew, attw.woute_dev, e,
						 ETH_P_IPV6);

	/* add ip headew */
	ip6_fwow_hdw(ip6h, tun_key->tos, 0);
	/* the HW fiwws up ipv6 paywoad wen */
	ip6h->hop_wimit   = attw.ttw;
	ip6h->daddw	  = attw.fw.fw6.daddw;
	ip6h->saddw	  = attw.fw.fw6.saddw;

	/* add tunnewing pwotocow headew */
	eww = mwx5e_gen_ip_tunnew_headew((chaw *)ip6h + sizeof(stwuct ipv6hdw),
					 &ip6h->nexthdw, e);
	if (eww)
		goto fwee_encap;

	e->encap_size = ipv6_encap_size;
	kfwee(e->encap_headew);
	e->encap_headew = encap_headew;
	encap_headew = NUWW;

	if (!(nud_state & NUD_VAWID)) {
		neigh_event_send(attw.n, NUWW);
		/* the encap entwy wiww be made vawid on neigh update event
		 * and not used befowe that.
		 */
		goto wewease_neigh;
	}

	memset(&wefowmat_pawams, 0, sizeof(wefowmat_pawams));
	wefowmat_pawams.type = e->wefowmat_type;
	wefowmat_pawams.size = e->encap_size;
	wefowmat_pawams.data = e->encap_headew;
	e->pkt_wefowmat = mwx5_packet_wefowmat_awwoc(pwiv->mdev, &wefowmat_pawams,
						     MWX5_FWOW_NAMESPACE_FDB);
	if (IS_EWW(e->pkt_wefowmat)) {
		eww = PTW_EWW(e->pkt_wefowmat);
		goto fwee_encap;
	}

	e->fwags |= MWX5_ENCAP_ENTWY_VAWID;
	mwx5e_wep_queue_neigh_stats_wowk(netdev_pwiv(attw.out_dev));
	mwx5e_woute_wookup_ipv6_put(&attw);
	wetuwn eww;

fwee_encap:
	kfwee(encap_headew);
wewease_neigh:
	mwx5e_woute_wookup_ipv6_put(&attw);
	wetuwn eww;
}
#endif

int mwx5e_tc_tun_woute_wookup(stwuct mwx5e_pwiv *pwiv,
			      stwuct mwx5_fwow_spec *spec,
			      stwuct mwx5_fwow_attw *fwow_attw,
			      stwuct net_device *fiwtew_dev)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = fwow_attw->esw_attw;
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct mwx5e_tc_int_powt *int_powt;
	TC_TUN_WOUTE_ATTW_INIT(attw);
	u16 vpowt_num;
	int eww = 0;

	if (fwow_attw->tun_ip_vewsion == 4) {
		/* Addwesses awe swapped fow decap */
		attw.fw.fw4.saddw = esw_attw->wx_tun_attw->dst_ip.v4;
		attw.fw.fw4.daddw = esw_attw->wx_tun_attw->swc_ip.v4;
		eww = mwx5e_woute_wookup_ipv4_get(pwiv, fiwtew_dev, &attw);
	}
#if IS_ENABWED(CONFIG_INET) && IS_ENABWED(CONFIG_IPV6)
	ewse if (fwow_attw->tun_ip_vewsion == 6) {
		/* Addwesses awe swapped fow decap */
		attw.fw.fw6.saddw = esw_attw->wx_tun_attw->dst_ip.v6;
		attw.fw.fw6.daddw = esw_attw->wx_tun_attw->swc_ip.v6;
		eww = mwx5e_woute_wookup_ipv6_get(pwiv, fiwtew_dev, &attw);
	}
#endif
	ewse
		wetuwn 0;

	if (eww)
		wetuwn eww;

	if (attw.woute_dev->netdev_ops == &mwx5e_netdev_ops &&
	    mwx5e_tc_is_vf_tunnew(attw.out_dev, attw.woute_dev)) {
		eww = mwx5e_tc_quewy_woute_vpowt(attw.out_dev, attw.woute_dev, &vpowt_num);
		if (eww)
			goto out;

		esw_attw->wx_tun_attw->decap_vpowt = vpowt_num;
	} ewse if (netif_is_ovs_mastew(attw.woute_dev) && mwx5e_tc_int_powt_suppowted(esw)) {
		int_powt = mwx5e_tc_int_powt_get(mwx5e_get_int_powt_pwiv(pwiv),
						 attw.woute_dev->ifindex,
						 MWX5E_TC_INT_POWT_INGWESS);
		if (IS_EWW(int_powt)) {
			eww = PTW_EWW(int_powt);
			goto out;
		}
		esw_attw->int_powt = int_powt;
	}

out:
	if (fwow_attw->tun_ip_vewsion == 4)
		mwx5e_woute_wookup_ipv4_put(&attw);
#if IS_ENABWED(CONFIG_INET) && IS_ENABWED(CONFIG_IPV6)
	ewse if (fwow_attw->tun_ip_vewsion == 6)
		mwx5e_woute_wookup_ipv6_put(&attw);
#endif
	wetuwn eww;
}

boow mwx5e_tc_tun_device_to_offwoad(stwuct mwx5e_pwiv *pwiv,
				    stwuct net_device *netdev)
{
	stwuct mwx5e_tc_tunnew *tunnew = mwx5e_get_tc_tun(netdev);

	if (tunnew && tunnew->can_offwoad(pwiv))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

int mwx5e_tc_tun_init_encap_attw(stwuct net_device *tunnew_dev,
				 stwuct mwx5e_pwiv *pwiv,
				 stwuct mwx5e_encap_entwy *e,
				 stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_tc_tunnew *tunnew = mwx5e_get_tc_tun(tunnew_dev);

	if (!tunnew) {
		e->wefowmat_type = -1;
		wetuwn -EOPNOTSUPP;
	}

	wetuwn tunnew->init_encap_attw(tunnew_dev, pwiv, e, extack);
}

int mwx5e_tc_tun_pawse(stwuct net_device *fiwtew_dev,
		       stwuct mwx5e_pwiv *pwiv,
		       stwuct mwx5_fwow_spec *spec,
		       stwuct fwow_cws_offwoad *f,
		       u8 *match_wevew)
{
	stwuct mwx5e_tc_tunnew *tunnew = mwx5e_get_tc_tun(fiwtew_dev);
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	void *headews_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				       outew_headews);
	void *headews_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				       outew_headews);
	stwuct netwink_ext_ack *extack = f->common.extack;
	int eww = 0;

	if (!tunnew) {
		netdev_wawn(pwiv->netdev,
			    "decapsuwation offwoad is not suppowted fow %s net device\n",
			    mwx5e_netdev_kind(fiwtew_dev));
		eww = -EOPNOTSUPP;
		goto out;
	}

	*match_wevew = tunnew->match_wevew;

	if (tunnew->pawse_udp_powts) {
		eww = tunnew->pawse_udp_powts(pwiv, spec, f,
					      headews_c, headews_v);
		if (eww)
			goto out;
	}

	if (tunnew->pawse_tunnew) {
		eww = tunnew->pawse_tunnew(pwiv, spec, f,
					   headews_c, headews_v);
		if (eww)
			goto out;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_CONTWOW)) {
		stwuct fwow_dissectow_key_basic key_basic = {};
		stwuct fwow_dissectow_key_basic mask_basic = {
			.n_pwoto = htons(0xFFFF),
		};
		stwuct fwow_match_basic match_basic = {
			.key = &key_basic, .mask = &mask_basic,
		};
		stwuct fwow_match_contwow match;
		u16 addw_type;

		fwow_wuwe_match_enc_contwow(wuwe, &match);
		addw_type = match.key->addw_type;

		/* Fow tunnew addw_type used same key id`s as fow non-tunnew */
		if (addw_type == FWOW_DISSECTOW_KEY_IPV4_ADDWS) {
			stwuct fwow_match_ipv4_addws match;

			fwow_wuwe_match_enc_ipv4_addws(wuwe, &match);
			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 swc_ipv4_swc_ipv6.ipv4_wayout.ipv4,
				 ntohw(match.mask->swc));
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 swc_ipv4_swc_ipv6.ipv4_wayout.ipv4,
				 ntohw(match.key->swc));

			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 dst_ipv4_dst_ipv6.ipv4_wayout.ipv4,
				 ntohw(match.mask->dst));
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 dst_ipv4_dst_ipv6.ipv4_wayout.ipv4,
				 ntohw(match.key->dst));

			key_basic.n_pwoto = htons(ETH_P_IP);
			mwx5e_tc_set_ethewtype(pwiv->mdev, &match_basic, twue,
					       headews_c, headews_v);
		} ewse if (addw_type == FWOW_DISSECTOW_KEY_IPV6_ADDWS) {
			stwuct fwow_match_ipv6_addws match;

			fwow_wuwe_match_enc_ipv6_addws(wuwe, &match);
			memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
					    swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
			       &match.mask->swc, MWX5_FWD_SZ_BYTES(ipv6_wayout,
								   ipv6));
			memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
					    swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
			       &match.key->swc, MWX5_FWD_SZ_BYTES(ipv6_wayout,
								  ipv6));

			memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
					    dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
			       &match.mask->dst, MWX5_FWD_SZ_BYTES(ipv6_wayout,
								   ipv6));
			memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
					    dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
			       &match.key->dst, MWX5_FWD_SZ_BYTES(ipv6_wayout,
								  ipv6));

			key_basic.n_pwoto = htons(ETH_P_IPV6);
			mwx5e_tc_set_ethewtype(pwiv->mdev, &match_basic, twue,
					       headews_c, headews_v);
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_IP)) {
		stwuct fwow_match_ip match;

		fwow_wuwe_match_enc_ip(wuwe, &match);
		MWX5_SET(fte_match_set_wyw_2_4, headews_c, ip_ecn,
			 match.mask->tos & 0x3);
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, ip_ecn,
			 match.key->tos & 0x3);

		MWX5_SET(fte_match_set_wyw_2_4, headews_c, ip_dscp,
			 match.mask->tos >> 2);
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, ip_dscp,
			 match.key->tos  >> 2);

		MWX5_SET(fte_match_set_wyw_2_4, headews_c, ttw_hopwimit,
			 match.mask->ttw);
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, ttw_hopwimit,
			 match.key->ttw);

		if (match.mask->ttw &&
		    !MWX5_CAP_ESW_FWOWTABWE_FDB
			(pwiv->mdev,
			 ft_fiewd_suppowt.outew_ipv4_ttw)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Matching on TTW is not suppowted");
			eww = -EOPNOTSUPP;
			goto out;
		}
	}

	/* wet softwawe handwe IP fwagments */
	MWX5_SET(fte_match_set_wyw_2_4, headews_c, fwag, 1);
	MWX5_SET(fte_match_set_wyw_2_4, headews_v, fwag, 0);

	wetuwn 0;

out:
	wetuwn eww;
}

int mwx5e_tc_tun_pawse_udp_powts(stwuct mwx5e_pwiv *pwiv,
				 stwuct mwx5_fwow_spec *spec,
				 stwuct fwow_cws_offwoad *f,
				 void *headews_c,
				 void *headews_v)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct fwow_match_powts enc_powts;

	/* Fuww udp dst powt must be given */

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_POWTS)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "UDP tunnew decap fiwtew must incwude enc_dst_powt condition");
		netdev_wawn(pwiv->netdev,
			    "UDP tunnew decap fiwtew must incwude enc_dst_powt condition\n");
		wetuwn -EOPNOTSUPP;
	}

	fwow_wuwe_match_enc_powts(wuwe, &enc_powts);

	if (memchw_inv(&enc_powts.mask->dst, 0xff,
		       sizeof(enc_powts.mask->dst))) {
		NW_SET_EWW_MSG_MOD(extack,
				   "UDP tunnew decap fiwtew must match enc_dst_powt fuwwy");
		netdev_wawn(pwiv->netdev,
			    "UDP tunnew decap fiwtew must match enc_dst_powt fuwwy\n");
		wetuwn -EOPNOTSUPP;
	}

	/* match on UDP pwotocow and dst powt numbew */

	MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c, ip_pwotocow);
	MWX5_SET(fte_match_set_wyw_2_4, headews_v, ip_pwotocow, IPPWOTO_UDP);

	MWX5_SET(fte_match_set_wyw_2_4, headews_c, udp_dpowt,
		 ntohs(enc_powts.mask->dst));
	MWX5_SET(fte_match_set_wyw_2_4, headews_v, udp_dpowt,
		 ntohs(enc_powts.key->dst));

	/* UDP swc powt on outew headew is genewated by HW,
	 * so it is pwobabwy a bad idea to wequest matching it.
	 * Nonethewess, it is awwowed.
	 */

	MWX5_SET(fte_match_set_wyw_2_4, headews_c, udp_spowt,
		 ntohs(enc_powts.mask->swc));
	MWX5_SET(fte_match_set_wyw_2_4, headews_v, udp_spowt,
		 ntohs(enc_powts.key->swc));

	wetuwn 0;
}
