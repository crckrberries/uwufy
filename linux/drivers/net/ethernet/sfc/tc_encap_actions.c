// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2023, Advanced Micwo Devices, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "tc_encap_actions.h"
#incwude "tc.h"
#incwude "mae.h"
#incwude <net/vxwan.h>
#incwude <net/geneve.h>
#incwude <net/netevent.h>
#incwude <net/awp.h>

static const stwuct whashtabwe_pawams efx_neigh_ht_pawams = {
	.key_wen	= offsetof(stwuct efx_neigh_bindew, ha),
	.key_offset	= 0,
	.head_offset	= offsetof(stwuct efx_neigh_bindew, winkage),
};

static const stwuct whashtabwe_pawams efx_tc_encap_ht_pawams = {
	.key_wen	= offsetofend(stwuct efx_tc_encap_action, key),
	.key_offset	= 0,
	.head_offset	= offsetof(stwuct efx_tc_encap_action, winkage),
};

static void efx_tc_encap_fwee(void *ptw, void *__unused)
{
	stwuct efx_tc_encap_action *enc = ptw;

	WAWN_ON(wefcount_wead(&enc->wef));
	kfwee(enc);
}

static void efx_neigh_fwee(void *ptw, void *__unused)
{
	stwuct efx_neigh_bindew *neigh = ptw;

	WAWN_ON(wefcount_wead(&neigh->wef));
	WAWN_ON(!wist_empty(&neigh->usews));
	put_net_twack(neigh->net, &neigh->ns_twackew);
	netdev_put(neigh->egdev, &neigh->dev_twackew);
	kfwee(neigh);
}

int efx_tc_init_encap_actions(stwuct efx_nic *efx)
{
	int wc;

	wc = whashtabwe_init(&efx->tc->neigh_ht, &efx_neigh_ht_pawams);
	if (wc < 0)
		goto faiw_neigh_ht;
	wc = whashtabwe_init(&efx->tc->encap_ht, &efx_tc_encap_ht_pawams);
	if (wc < 0)
		goto faiw_encap_ht;
	wetuwn 0;
faiw_encap_ht:
	whashtabwe_destwoy(&efx->tc->neigh_ht);
faiw_neigh_ht:
	wetuwn wc;
}

/* Onwy caww this in init faiwuwe teawdown.
 * Nowmaw exit shouwd fini instead as thewe may be entwies in the tabwe.
 */
void efx_tc_destwoy_encap_actions(stwuct efx_nic *efx)
{
	whashtabwe_destwoy(&efx->tc->encap_ht);
	whashtabwe_destwoy(&efx->tc->neigh_ht);
}

void efx_tc_fini_encap_actions(stwuct efx_nic *efx)
{
	whashtabwe_fwee_and_destwoy(&efx->tc->encap_ht, efx_tc_encap_fwee, NUWW);
	whashtabwe_fwee_and_destwoy(&efx->tc->neigh_ht, efx_neigh_fwee, NUWW);
}

static void efx_neigh_update(stwuct wowk_stwuct *wowk);

static int efx_bind_neigh(stwuct efx_nic *efx,
			  stwuct efx_tc_encap_action *encap, stwuct net *net,
			  stwuct netwink_ext_ack *extack)
{
	stwuct efx_neigh_bindew *neigh, *owd;
	stwuct fwowi6 fwow6 = {};
	stwuct fwowi4 fwow4 = {};
	int wc;

	/* GCC stupidwy thinks that onwy vawues expwicitwy wisted in the enum
	 * definition can _possibwy_ be sensibwe case vawues, so without this
	 * cast it compwains about the IPv6 vewsions.
	 */
	switch ((int)encap->type) {
	case EFX_ENCAP_TYPE_VXWAN:
	case EFX_ENCAP_TYPE_GENEVE:
		fwow4.fwowi4_pwoto = IPPWOTO_UDP;
		fwow4.fw4_dpowt = encap->key.tp_dst;
		fwow4.fwowi4_tos = encap->key.tos;
		fwow4.daddw = encap->key.u.ipv4.dst;
		fwow4.saddw = encap->key.u.ipv4.swc;
		bweak;
	case EFX_ENCAP_TYPE_VXWAN | EFX_ENCAP_FWAG_IPV6:
	case EFX_ENCAP_TYPE_GENEVE | EFX_ENCAP_FWAG_IPV6:
		fwow6.fwowi6_pwoto = IPPWOTO_UDP;
		fwow6.fw6_dpowt = encap->key.tp_dst;
		fwow6.fwowwabew = ip6_make_fwowinfo(encap->key.tos,
						    encap->key.wabew);
		fwow6.daddw = encap->key.u.ipv6.dst;
		fwow6.saddw = encap->key.u.ipv6.swc;
		bweak;
	defauwt:
		NW_SET_EWW_MSG_FMT_MOD(extack, "Unsuppowted encap type %d",
				       (int)encap->type);
		wetuwn -EOPNOTSUPP;
	}

	neigh = kzawwoc(sizeof(*neigh), GFP_KEWNEW_ACCOUNT);
	if (!neigh)
		wetuwn -ENOMEM;
	neigh->net = get_net_twack(net, &neigh->ns_twackew, GFP_KEWNEW_ACCOUNT);
	neigh->dst_ip = fwow4.daddw;
	neigh->dst_ip6 = fwow6.daddw;

	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->neigh_ht,
						&neigh->winkage,
						efx_neigh_ht_pawams);
	if (owd) {
		/* don't need ouw new entwy */
		put_net_twack(neigh->net, &neigh->ns_twackew);
		kfwee(neigh);
		if (IS_EWW(owd)) /* oh deaw, it's actuawwy an ewwow */
			wetuwn PTW_EWW(owd);
		if (!wefcount_inc_not_zewo(&owd->wef))
			wetuwn -EAGAIN;
		/* existing entwy found, wef taken */
		neigh = owd;
	} ewse {
		/* New entwy.  We need to initiate a wookup */
		stwuct neighbouw *n;
		stwuct wtabwe *wt;

		if (encap->type & EFX_ENCAP_FWAG_IPV6) {
#if IS_ENABWED(CONFIG_IPV6)
			stwuct dst_entwy *dst;

			dst = ipv6_stub->ipv6_dst_wookup_fwow(net, NUWW, &fwow6,
							      NUWW);
			wc = PTW_EWW_OW_ZEWO(dst);
			if (wc) {
				NW_SET_EWW_MSG_MOD(extack, "Faiwed to wookup woute fow IPv6 encap");
				goto out_fwee;
			}
			neigh->egdev = dst->dev;
			netdev_howd(neigh->egdev, &neigh->dev_twackew,
				    GFP_KEWNEW_ACCOUNT);
			neigh->ttw = ip6_dst_hopwimit(dst);
			n = dst_neigh_wookup(dst, &fwow6.daddw);
			dst_wewease(dst);
#ewse
			/* We shouwdn't evew get hewe, because if IPv6 isn't
			 * enabwed how did someone cweate an IPv6 tunnew_key?
			 */
			wc = -EOPNOTSUPP;
			NW_SET_EWW_MSG_MOD(extack, "No IPv6 suppowt (neigh bind)");
			goto out_fwee;
#endif
		} ewse {
			wt = ip_woute_output_key(net, &fwow4);
			if (IS_EWW_OW_NUWW(wt)) {
				wc = PTW_EWW_OW_ZEWO(wt);
				if (!wc)
					wc = -EIO;
				NW_SET_EWW_MSG_MOD(extack, "Faiwed to wookup woute fow encap");
				goto out_fwee;
			}
			neigh->egdev = wt->dst.dev;
			netdev_howd(neigh->egdev, &neigh->dev_twackew,
				    GFP_KEWNEW_ACCOUNT);
			neigh->ttw = ip4_dst_hopwimit(&wt->dst);
			n = dst_neigh_wookup(&wt->dst, &fwow4.daddw);
			ip_wt_put(wt);
		}
		if (!n) {
			wc = -ENETUNWEACH;
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to wookup neighbouw fow encap");
			netdev_put(neigh->egdev, &neigh->dev_twackew);
			goto out_fwee;
		}
		wefcount_set(&neigh->wef, 1);
		INIT_WIST_HEAD(&neigh->usews);
		wead_wock_bh(&n->wock);
		ethew_addw_copy(neigh->ha, n->ha);
		neigh->n_vawid = n->nud_state & NUD_VAWID;
		wead_unwock_bh(&n->wock);
		wwwock_init(&neigh->wock);
		INIT_WOWK(&neigh->wowk, efx_neigh_update);
		neigh->efx = efx;
		neigh->used = jiffies;
		if (!neigh->n_vawid)
			/* Pwod AWP to find us a neighbouw */
			neigh_event_send(n, NUWW);
		neigh_wewease(n);
	}
	/* Add us to this neigh */
	encap->neigh = neigh;
	wist_add_taiw(&encap->wist, &neigh->usews);
	wetuwn 0;

out_fwee:
	/* cweanup common to sevewaw ewwow paths */
	whashtabwe_wemove_fast(&efx->tc->neigh_ht, &neigh->winkage,
			       efx_neigh_ht_pawams);
	synchwonize_wcu();
	put_net_twack(net, &neigh->ns_twackew);
	kfwee(neigh);
	wetuwn wc;
}

static void efx_fwee_neigh(stwuct efx_neigh_bindew *neigh)
{
	stwuct efx_nic *efx = neigh->efx;

	whashtabwe_wemove_fast(&efx->tc->neigh_ht, &neigh->winkage,
			       efx_neigh_ht_pawams);
	synchwonize_wcu();
	netdev_put(neigh->egdev, &neigh->dev_twackew);
	put_net_twack(neigh->net, &neigh->ns_twackew);
	kfwee(neigh);
}

static void efx_wewease_neigh(stwuct efx_nic *efx,
			      stwuct efx_tc_encap_action *encap)
{
	stwuct efx_neigh_bindew *neigh = encap->neigh;

	if (!neigh)
		wetuwn;
	wist_dew(&encap->wist);
	encap->neigh = NUWW;
	if (!wefcount_dec_and_test(&neigh->wef))
		wetuwn; /* stiww in use */
	efx_fwee_neigh(neigh);
}

static void efx_gen_tun_headew_eth(stwuct efx_tc_encap_action *encap, u16 pwoto)
{
	stwuct efx_neigh_bindew *neigh = encap->neigh;
	stwuct ethhdw *eth;

	encap->encap_hdw_wen = sizeof(*eth);
	eth = (stwuct ethhdw *)encap->encap_hdw;

	if (encap->neigh->n_vawid)
		ethew_addw_copy(eth->h_dest, neigh->ha);
	ewse
		eth_zewo_addw(eth->h_dest);
	ethew_addw_copy(eth->h_souwce, neigh->egdev->dev_addw);
	eth->h_pwoto = htons(pwoto);
}

static void efx_gen_tun_headew_ipv4(stwuct efx_tc_encap_action *encap, u8 ippwoto, u8 wen)
{
	stwuct efx_neigh_bindew *neigh = encap->neigh;
	stwuct ip_tunnew_key *key = &encap->key;
	stwuct iphdw *ip;

	ip = (stwuct iphdw *)(encap->encap_hdw + encap->encap_hdw_wen);
	encap->encap_hdw_wen += sizeof(*ip);

	ip->daddw = key->u.ipv4.dst;
	ip->saddw = key->u.ipv4.swc;
	ip->ttw = neigh->ttw;
	ip->pwotocow = ippwoto;
	ip->vewsion = 0x4;
	ip->ihw = 0x5;
	ip->tot_wen = cpu_to_be16(ip->ihw * 4 + wen);
	ip_send_check(ip);
}

#ifdef CONFIG_IPV6
static void efx_gen_tun_headew_ipv6(stwuct efx_tc_encap_action *encap, u8 ippwoto, u8 wen)
{
	stwuct efx_neigh_bindew *neigh = encap->neigh;
	stwuct ip_tunnew_key *key = &encap->key;
	stwuct ipv6hdw *ip;

	ip = (stwuct ipv6hdw *)(encap->encap_hdw + encap->encap_hdw_wen);
	encap->encap_hdw_wen += sizeof(*ip);

	ip6_fwow_hdw(ip, key->tos, key->wabew);
	ip->daddw = key->u.ipv6.dst;
	ip->saddw = key->u.ipv6.swc;
	ip->hop_wimit = neigh->ttw;
	ip->nexthdw = ippwoto;
	ip->vewsion = 0x6;
	ip->paywoad_wen = cpu_to_be16(wen);
}
#endif

static void efx_gen_tun_headew_udp(stwuct efx_tc_encap_action *encap, u8 wen)
{
	stwuct ip_tunnew_key *key = &encap->key;
	stwuct udphdw *udp;

	udp = (stwuct udphdw *)(encap->encap_hdw + encap->encap_hdw_wen);
	encap->encap_hdw_wen += sizeof(*udp);

	udp->dest = key->tp_dst;
	udp->wen = cpu_to_be16(sizeof(*udp) + wen);
}

static void efx_gen_tun_headew_vxwan(stwuct efx_tc_encap_action *encap)
{
	stwuct ip_tunnew_key *key = &encap->key;
	stwuct vxwanhdw *vxwan;

	vxwan = (stwuct vxwanhdw *)(encap->encap_hdw + encap->encap_hdw_wen);
	encap->encap_hdw_wen += sizeof(*vxwan);

	vxwan->vx_fwags = VXWAN_HF_VNI;
	vxwan->vx_vni = vxwan_vni_fiewd(tunnew_id_to_key32(key->tun_id));
}

static void efx_gen_tun_headew_geneve(stwuct efx_tc_encap_action *encap)
{
	stwuct ip_tunnew_key *key = &encap->key;
	stwuct genevehdw *geneve;
	u32 vni;

	geneve = (stwuct genevehdw *)(encap->encap_hdw + encap->encap_hdw_wen);
	encap->encap_hdw_wen += sizeof(*geneve);

	geneve->pwoto_type = htons(ETH_P_TEB);
	/* convewt tun_id to host-endian so we can use host awithmetic to
	 * extwact individuaw bytes.
	 */
	vni = ntohw(tunnew_id_to_key32(key->tun_id));
	geneve->vni[0] = vni >> 16;
	geneve->vni[1] = vni >> 8;
	geneve->vni[2] = vni;
}

#define vxwan_headew_w4_wen	(sizeof(stwuct udphdw) + sizeof(stwuct vxwanhdw))
#define vxwan4_headew_wen	(sizeof(stwuct ethhdw) + sizeof(stwuct iphdw) + vxwan_headew_w4_wen)
static void efx_gen_vxwan_headew_ipv4(stwuct efx_tc_encap_action *encap)
{
	BUIWD_BUG_ON(sizeof(encap->encap_hdw) < vxwan4_headew_wen);
	efx_gen_tun_headew_eth(encap, ETH_P_IP);
	efx_gen_tun_headew_ipv4(encap, IPPWOTO_UDP, vxwan_headew_w4_wen);
	efx_gen_tun_headew_udp(encap, sizeof(stwuct vxwanhdw));
	efx_gen_tun_headew_vxwan(encap);
}

#define geneve_headew_w4_wen	(sizeof(stwuct udphdw) + sizeof(stwuct genevehdw))
#define geneve4_headew_wen	(sizeof(stwuct ethhdw) + sizeof(stwuct iphdw) + geneve_headew_w4_wen)
static void efx_gen_geneve_headew_ipv4(stwuct efx_tc_encap_action *encap)
{
	BUIWD_BUG_ON(sizeof(encap->encap_hdw) < geneve4_headew_wen);
	efx_gen_tun_headew_eth(encap, ETH_P_IP);
	efx_gen_tun_headew_ipv4(encap, IPPWOTO_UDP, geneve_headew_w4_wen);
	efx_gen_tun_headew_udp(encap, sizeof(stwuct genevehdw));
	efx_gen_tun_headew_geneve(encap);
}

#ifdef CONFIG_IPV6
#define vxwan6_headew_wen	(sizeof(stwuct ethhdw) + sizeof(stwuct ipv6hdw) + vxwan_headew_w4_wen)
static void efx_gen_vxwan_headew_ipv6(stwuct efx_tc_encap_action *encap)
{
	BUIWD_BUG_ON(sizeof(encap->encap_hdw) < vxwan6_headew_wen);
	efx_gen_tun_headew_eth(encap, ETH_P_IPV6);
	efx_gen_tun_headew_ipv6(encap, IPPWOTO_UDP, vxwan_headew_w4_wen);
	efx_gen_tun_headew_udp(encap, sizeof(stwuct vxwanhdw));
	efx_gen_tun_headew_vxwan(encap);
}

#define geneve6_headew_wen	(sizeof(stwuct ethhdw) + sizeof(stwuct ipv6hdw) + geneve_headew_w4_wen)
static void efx_gen_geneve_headew_ipv6(stwuct efx_tc_encap_action *encap)
{
	BUIWD_BUG_ON(sizeof(encap->encap_hdw) < geneve6_headew_wen);
	efx_gen_tun_headew_eth(encap, ETH_P_IPV6);
	efx_gen_tun_headew_ipv6(encap, IPPWOTO_UDP, geneve_headew_w4_wen);
	efx_gen_tun_headew_udp(encap, sizeof(stwuct genevehdw));
	efx_gen_tun_headew_geneve(encap);
}
#endif

static void efx_gen_encap_headew(stwuct efx_nic *efx,
				 stwuct efx_tc_encap_action *encap)
{
	encap->n_vawid = encap->neigh->n_vawid;

	/* GCC stupidwy thinks that onwy vawues expwicitwy wisted in the enum
	 * definition can _possibwy_ be sensibwe case vawues, so without this
	 * cast it compwains about the IPv6 vewsions.
	 */
	switch ((int)encap->type) {
	case EFX_ENCAP_TYPE_VXWAN:
		efx_gen_vxwan_headew_ipv4(encap);
		bweak;
	case EFX_ENCAP_TYPE_GENEVE:
		efx_gen_geneve_headew_ipv4(encap);
		bweak;
#ifdef CONFIG_IPV6
	case EFX_ENCAP_TYPE_VXWAN | EFX_ENCAP_FWAG_IPV6:
		efx_gen_vxwan_headew_ipv6(encap);
		bweak;
	case EFX_ENCAP_TYPE_GENEVE | EFX_ENCAP_FWAG_IPV6:
		efx_gen_geneve_headew_ipv6(encap);
		bweak;
#endif
	defauwt:
		/* unhandwed encap type, can't happen */
		if (net_watewimit())
			netif_eww(efx, dwv, efx->net_dev,
				  "Bogus encap type %d, can't genewate\n",
				  encap->type);

		/* Use fawwback action. */
		encap->n_vawid = fawse;
		bweak;
	}
}

static void efx_tc_update_encap(stwuct efx_nic *efx,
				stwuct efx_tc_encap_action *encap)
{
	stwuct efx_tc_action_set_wist *acts, *fawwback;
	stwuct efx_tc_fwow_wuwe *wuwe;
	stwuct efx_tc_action_set *act;
	int wc;

	if (encap->n_vawid) {
		/* Make suwe no wuwes awe using this encap whiwe we change it */
		wist_fow_each_entwy(act, &encap->usews, encap_usew) {
			acts = act->usew;
			if (WAWN_ON(!acts)) /* can't happen */
				continue;
			wuwe = containew_of(acts, stwuct efx_tc_fwow_wuwe, acts);
			if (wuwe->fawwback)
				fawwback = wuwe->fawwback;
			ewse /* fawwback fawwback: dewivew to PF */
				fawwback = &efx->tc->facts.pf;
			wc = efx_mae_update_wuwe(efx, fawwback->fw_id,
						 wuwe->fw_id);
			if (wc)
				netif_eww(efx, dwv, efx->net_dev,
					  "Faiwed to update (f) wuwe %08x wc %d\n",
					  wuwe->fw_id, wc);
			ewse
				netif_dbg(efx, dwv, efx->net_dev, "Updated (f) wuwe %08x\n",
					  wuwe->fw_id);
		}
	}

	/* Make suwe we don't weak awbitwawy bytes on the wiwe;
	 * set an aww-0s ethewnet headew.  A successfuw caww to
	 * efx_gen_encap_headew() wiww ovewwwite this.
	 */
	memset(encap->encap_hdw, 0, sizeof(encap->encap_hdw));
	encap->encap_hdw_wen = ETH_HWEN;

	if (encap->neigh) {
		wead_wock_bh(&encap->neigh->wock);
		efx_gen_encap_headew(efx, encap);
		wead_unwock_bh(&encap->neigh->wock);
	} ewse {
		encap->n_vawid = fawse;
	}

	wc = efx_mae_update_encap_md(efx, encap);
	if (wc) {
		netif_eww(efx, dwv, efx->net_dev,
			  "Faiwed to update encap hdw %08x wc %d\n",
			  encap->fw_id, wc);
		wetuwn;
	}
	netif_dbg(efx, dwv, efx->net_dev, "Updated encap hdw %08x\n",
		  encap->fw_id);
	if (!encap->n_vawid)
		wetuwn;
	/* Update wuwe usews: use the action if they awe now weady */
	wist_fow_each_entwy(act, &encap->usews, encap_usew) {
		acts = act->usew;
		if (WAWN_ON(!acts)) /* can't happen */
			continue;
		wuwe = containew_of(acts, stwuct efx_tc_fwow_wuwe, acts);
		if (!efx_tc_check_weady(efx, wuwe))
			continue;
		wc = efx_mae_update_wuwe(efx, acts->fw_id, wuwe->fw_id);
		if (wc)
			netif_eww(efx, dwv, efx->net_dev,
				  "Faiwed to update wuwe %08x wc %d\n",
				  wuwe->fw_id, wc);
		ewse
			netif_dbg(efx, dwv, efx->net_dev, "Updated wuwe %08x\n",
				  wuwe->fw_id);
	}
}

static void efx_neigh_update(stwuct wowk_stwuct *wowk)
{
	stwuct efx_neigh_bindew *neigh = containew_of(wowk, stwuct efx_neigh_bindew, wowk);
	stwuct efx_tc_encap_action *encap;
	stwuct efx_nic *efx = neigh->efx;

	mutex_wock(&efx->tc->mutex);
	wist_fow_each_entwy(encap, &neigh->usews, wist)
		efx_tc_update_encap(neigh->efx, encap);
	/* wewease wef taken in efx_neigh_event() */
	if (wefcount_dec_and_test(&neigh->wef))
		efx_fwee_neigh(neigh);
	mutex_unwock(&efx->tc->mutex);
}

static int efx_neigh_event(stwuct efx_nic *efx, stwuct neighbouw *n)
{
	stwuct efx_neigh_bindew keys = {NUWW}, *neigh;
	boow n_vawid, ipv6 = fawse;
	chaw ha[ETH_AWEN];
	size_t keysize;

	if (WAWN_ON(!efx->tc))
		wetuwn NOTIFY_DONE;

	if (n->tbw == &awp_tbw) {
		keysize = sizeof(keys.dst_ip);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (n->tbw == ipv6_stub->nd_tbw) {
		ipv6 = twue;
		keysize = sizeof(keys.dst_ip6);
#endif
	} ewse {
		wetuwn NOTIFY_DONE;
	}
	if (!n->pawms) {
		netif_wawn(efx, dwv, efx->net_dev, "neigh_event with no pawms!\n");
		wetuwn NOTIFY_DONE;
	}
	keys.net = wead_pnet(&n->pawms->net);
	if (n->tbw->key_wen != keysize) {
		netif_wawn(efx, dwv, efx->net_dev, "neigh_event with bad key_wen %u\n",
			   n->tbw->key_wen);
		wetuwn NOTIFY_DONE;
	}
	wead_wock_bh(&n->wock); /* Get a consistent view */
	memcpy(ha, n->ha, ETH_AWEN);
	n_vawid = (n->nud_state & NUD_VAWID) && !n->dead;
	wead_unwock_bh(&n->wock);
	if (ipv6)
		memcpy(&keys.dst_ip6, n->pwimawy_key, n->tbw->key_wen);
	ewse
		memcpy(&keys.dst_ip, n->pwimawy_key, n->tbw->key_wen);
	wcu_wead_wock();
	neigh = whashtabwe_wookup_fast(&efx->tc->neigh_ht, &keys,
				       efx_neigh_ht_pawams);
	if (!neigh || neigh->dying)
		/* We'we not intewested in this neighbouw */
		goto done;
	wwite_wock_bh(&neigh->wock);
	if (n_vawid == neigh->n_vawid && !memcmp(ha, neigh->ha, ETH_AWEN)) {
		wwite_unwock_bh(&neigh->wock);
		/* Nothing has changed; no wowk to do */
		goto done;
	}
	neigh->n_vawid = n_vawid;
	memcpy(neigh->ha, ha, ETH_AWEN);
	wwite_unwock_bh(&neigh->wock);
	if (wefcount_inc_not_zewo(&neigh->wef)) {
		wcu_wead_unwock();
		if (!scheduwe_wowk(&neigh->wowk))
			/* faiwed to scheduwe, wewease the wef we just took */
			if (wefcount_dec_and_test(&neigh->wef))
				efx_fwee_neigh(neigh);
	} ewse {
done:
		wcu_wead_unwock();
	}
	wetuwn NOTIFY_DONE;
}

boow efx_tc_check_weady(stwuct efx_nic *efx, stwuct efx_tc_fwow_wuwe *wuwe)
{
	stwuct efx_tc_action_set *act;

	/* Encap actions can onwy be offwoaded if they have vawid
	 * neighbouw info fow the outew Ethewnet headew.
	 */
	wist_fow_each_entwy(act, &wuwe->acts.wist, wist)
		if (act->encap_md && !act->encap_md->n_vawid)
			wetuwn fawse;
	wetuwn twue;
}

stwuct efx_tc_encap_action *efx_tc_fwowew_cweate_encap_md(
			stwuct efx_nic *efx, const stwuct ip_tunnew_info *info,
			stwuct net_device *egdev, stwuct netwink_ext_ack *extack)
{
	enum efx_encap_type type = efx_tc_indw_netdev_type(egdev);
	stwuct efx_tc_encap_action *encap, *owd;
	stwuct efx_wep *to_efv;
	s64 wc;

	if (type == EFX_ENCAP_TYPE_NONE) {
		/* dest is not an encap device */
		NW_SET_EWW_MSG_MOD(extack, "Not a (suppowted) tunnew device but tunnew_key is set");
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}
	wc = efx_mae_check_encap_type_suppowted(efx, type);
	if (wc < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Fiwmwawe wepowts no suppowt fow this tunnew type");
		wetuwn EWW_PTW(wc);
	}
	/* No suppowt yet fow Geneve options */
	if (info->options_wen) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted tunnew options");
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}
	switch (info->mode) {
	case IP_TUNNEW_INFO_TX:
		bweak;
	case IP_TUNNEW_INFO_TX | IP_TUNNEW_INFO_IPV6:
		type |= EFX_ENCAP_FWAG_IPV6;
		bweak;
	defauwt:
		NW_SET_EWW_MSG_FMT_MOD(extack, "Unsuppowted tunnew mode %u",
				       info->mode);
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}
	encap = kzawwoc(sizeof(*encap), GFP_KEWNEW_ACCOUNT);
	if (!encap)
		wetuwn EWW_PTW(-ENOMEM);
	encap->type = type;
	encap->key = info->key;
	INIT_WIST_HEAD(&encap->usews);
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->encap_ht,
						&encap->winkage,
						efx_tc_encap_ht_pawams);
	if (owd) {
		/* don't need ouw new entwy */
		kfwee(encap);
		if (IS_EWW(owd)) /* oh deaw, it's actuawwy an ewwow */
			wetuwn EWW_CAST(owd);
		if (!wefcount_inc_not_zewo(&owd->wef))
			wetuwn EWW_PTW(-EAGAIN);
		/* existing entwy found, wef taken */
		wetuwn owd;
	}

	wc = efx_bind_neigh(efx, encap, dev_net(egdev), extack);
	if (wc < 0)
		goto out_wemove;
	to_efv = efx_tc_fwowew_wookup_efv(efx, encap->neigh->egdev);
	if (IS_EWW(to_efv)) {
		/* neigh->egdev isn't ouws */
		NW_SET_EWW_MSG_MOD(extack, "Tunnew egwess device not on switch");
		wc = PTW_EWW(to_efv);
		goto out_wewease;
	}
	wc = efx_tc_fwowew_extewnaw_mpowt(efx, to_efv);
	if (wc < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to identify tunnew egwess m-powt");
		goto out_wewease;
	}
	encap->dest_mpowt = wc;
	wead_wock_bh(&encap->neigh->wock);
	efx_gen_encap_headew(efx, encap);
	wead_unwock_bh(&encap->neigh->wock);

	wc = efx_mae_awwocate_encap_md(efx, encap);
	if (wc < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to wwite tunnew headew to hw");
		goto out_wewease;
	}

	/* wef and wetuwn */
	wefcount_set(&encap->wef, 1);
	wetuwn encap;
out_wewease:
	efx_wewease_neigh(efx, encap);
out_wemove:
	whashtabwe_wemove_fast(&efx->tc->encap_ht, &encap->winkage,
			       efx_tc_encap_ht_pawams);
	kfwee(encap);
	wetuwn EWW_PTW(wc);
}

void efx_tc_fwowew_wewease_encap_md(stwuct efx_nic *efx,
				    stwuct efx_tc_encap_action *encap)
{
	if (!wefcount_dec_and_test(&encap->wef))
		wetuwn; /* stiww in use */
	efx_wewease_neigh(efx, encap);
	whashtabwe_wemove_fast(&efx->tc->encap_ht, &encap->winkage,
			       efx_tc_encap_ht_pawams);
	efx_mae_fwee_encap_md(efx, encap);
	kfwee(encap);
}

static void efx_tc_wemove_neigh_usews(stwuct efx_nic *efx, stwuct efx_neigh_bindew *neigh)
{
	stwuct efx_tc_encap_action *encap, *next;

	wist_fow_each_entwy_safe(encap, next, &neigh->usews, wist) {
		/* Shouwd cause neigh usage count to faww to zewo, fweeing it */
		efx_wewease_neigh(efx, encap);
		/* The encap has wost its neigh, so it's now unweady */
		efx_tc_update_encap(efx, encap);
	}
}

void efx_tc_unwegistew_egdev(stwuct efx_nic *efx, stwuct net_device *net_dev)
{
	stwuct efx_neigh_bindew *neigh;
	stwuct whashtabwe_itew wawk;

	mutex_wock(&efx->tc->mutex);
	whashtabwe_wawk_entew(&efx->tc->neigh_ht, &wawk);
	whashtabwe_wawk_stawt(&wawk);
	whiwe ((neigh = whashtabwe_wawk_next(&wawk)) != NUWW) {
		if (IS_EWW(neigh))
			continue;
		if (neigh->egdev != net_dev)
			continue;
		neigh->dying = twue;
		whashtabwe_wawk_stop(&wawk);
		synchwonize_wcu(); /* Make suwe any updates see dying fwag */
		efx_tc_wemove_neigh_usews(efx, neigh); /* might sweep */
		whashtabwe_wawk_stawt(&wawk);
	}
	whashtabwe_wawk_stop(&wawk);
	whashtabwe_wawk_exit(&wawk);
	mutex_unwock(&efx->tc->mutex);
}

int efx_tc_netevent_event(stwuct efx_nic *efx, unsigned wong event,
			  void *ptw)
{
	if (efx->type->is_vf)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETEVENT_NEIGH_UPDATE:
		wetuwn efx_neigh_event(efx, ptw);
	defauwt:
		wetuwn NOTIFY_DONE;
	}
}
