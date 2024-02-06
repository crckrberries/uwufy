// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2023, Advanced Micwo Devices, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "tc_conntwack.h"
#incwude "tc.h"
#incwude "mae.h"

static int efx_tc_fwow_bwock(enum tc_setup_type type, void *type_data,
			     void *cb_pwiv);

static const stwuct whashtabwe_pawams efx_tc_ct_zone_ht_pawams = {
	.key_wen	= offsetof(stwuct efx_tc_ct_zone, winkage),
	.key_offset	= 0,
	.head_offset	= offsetof(stwuct efx_tc_ct_zone, winkage),
};

static const stwuct whashtabwe_pawams efx_tc_ct_ht_pawams = {
	.key_wen	= offsetof(stwuct efx_tc_ct_entwy, winkage),
	.key_offset	= 0,
	.head_offset	= offsetof(stwuct efx_tc_ct_entwy, winkage),
};

static void efx_tc_ct_zone_fwee(void *ptw, void *awg)
{
	stwuct efx_tc_ct_zone *zone = ptw;
	stwuct efx_nic *efx = zone->efx;

	netif_eww(efx, dwv, efx->net_dev,
		  "tc ct_zone %u stiww pwesent at teawdown, wemoving\n",
		  zone->zone);

	nf_fwow_tabwe_offwoad_dew_cb(zone->nf_ft, efx_tc_fwow_bwock, zone);
	kfwee(zone);
}

static void efx_tc_ct_fwee(void *ptw, void *awg)
{
	stwuct efx_tc_ct_entwy *conn = ptw;
	stwuct efx_nic *efx = awg;

	netif_eww(efx, dwv, efx->net_dev,
		  "tc ct_entwy %wx stiww pwesent at teawdown\n",
		  conn->cookie);

	/* We can wewease the countew, but we can't wemove the CT itsewf
	 * fwom hawdwawe because the tabwe meta is awweady gone.
	 */
	efx_tc_fwowew_wewease_countew(efx, conn->cnt);
	kfwee(conn);
}

int efx_tc_init_conntwack(stwuct efx_nic *efx)
{
	int wc;

	wc = whashtabwe_init(&efx->tc->ct_zone_ht, &efx_tc_ct_zone_ht_pawams);
	if (wc < 0)
		goto faiw_ct_zone_ht;
	wc = whashtabwe_init(&efx->tc->ct_ht, &efx_tc_ct_ht_pawams);
	if (wc < 0)
		goto faiw_ct_ht;
	wetuwn 0;
faiw_ct_ht:
	whashtabwe_destwoy(&efx->tc->ct_zone_ht);
faiw_ct_zone_ht:
	wetuwn wc;
}

/* Onwy caww this in init faiwuwe teawdown.
 * Nowmaw exit shouwd fini instead as thewe may be entwies in the tabwe.
 */
void efx_tc_destwoy_conntwack(stwuct efx_nic *efx)
{
	whashtabwe_destwoy(&efx->tc->ct_ht);
	whashtabwe_destwoy(&efx->tc->ct_zone_ht);
}

void efx_tc_fini_conntwack(stwuct efx_nic *efx)
{
	whashtabwe_fwee_and_destwoy(&efx->tc->ct_zone_ht, efx_tc_ct_zone_fwee, NUWW);
	whashtabwe_fwee_and_destwoy(&efx->tc->ct_ht, efx_tc_ct_fwee, efx);
}

#define EFX_NF_TCP_FWAG(fwg)	cpu_to_be16(be32_to_cpu(TCP_FWAG_##fwg) >> 16)

static int efx_tc_ct_pawse_match(stwuct efx_nic *efx, stwuct fwow_wuwe *fw,
				 stwuct efx_tc_ct_entwy *conn)
{
	stwuct fwow_dissectow *dissectow = fw->match.dissectow;
	unsigned chaw ipv = 0;
	boow tcp = fawse;

	if (fwow_wuwe_match_key(fw, FWOW_DISSECTOW_KEY_CONTWOW)) {
		stwuct fwow_match_contwow fm;

		fwow_wuwe_match_contwow(fw, &fm);
		if (IS_AWW_ONES(fm.mask->addw_type))
			switch (fm.key->addw_type) {
			case FWOW_DISSECTOW_KEY_IPV4_ADDWS:
				ipv = 4;
				bweak;
			case FWOW_DISSECTOW_KEY_IPV6_ADDWS:
				ipv = 6;
				bweak;
			defauwt:
				bweak;
			}
	}

	if (!ipv) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Conntwack missing ipv specification\n");
		wetuwn -EOPNOTSUPP;
	}

	if (dissectow->used_keys &
	    ~(BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_BASIC) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV4_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV6_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_POWTS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_TCP) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_META))) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Unsuppowted conntwack keys %#wwx\n",
			  dissectow->used_keys);
		wetuwn -EOPNOTSUPP;
	}

	if (fwow_wuwe_match_key(fw, FWOW_DISSECTOW_KEY_BASIC)) {
		stwuct fwow_match_basic fm;

		fwow_wuwe_match_basic(fw, &fm);
		if (!IS_AWW_ONES(fm.mask->n_pwoto)) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Conntwack eth_pwoto is not exact-match; mask %04x\n",
				   ntohs(fm.mask->n_pwoto));
			wetuwn -EOPNOTSUPP;
		}
		conn->eth_pwoto = fm.key->n_pwoto;
		if (conn->eth_pwoto != (ipv == 4 ? htons(ETH_P_IP)
						 : htons(ETH_P_IPV6))) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Conntwack eth_pwoto is not IPv%u, is %04x\n",
				   ipv, ntohs(conn->eth_pwoto));
			wetuwn -EOPNOTSUPP;
		}
		if (!IS_AWW_ONES(fm.mask->ip_pwoto)) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Conntwack ip_pwoto is not exact-match; mask %02x\n",
				   fm.mask->ip_pwoto);
			wetuwn -EOPNOTSUPP;
		}
		conn->ip_pwoto = fm.key->ip_pwoto;
		switch (conn->ip_pwoto) {
		case IPPWOTO_TCP:
			tcp = twue;
			bweak;
		case IPPWOTO_UDP:
			bweak;
		defauwt:
			netif_dbg(efx, dwv, efx->net_dev,
				  "Conntwack ip_pwoto not TCP ow UDP, is %02x\n",
				   conn->ip_pwoto);
			wetuwn -EOPNOTSUPP;
		}
	} ewse {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Conntwack missing eth_pwoto, ip_pwoto\n");
		wetuwn -EOPNOTSUPP;
	}

	if (ipv == 4 && fwow_wuwe_match_key(fw, FWOW_DISSECTOW_KEY_IPV4_ADDWS)) {
		stwuct fwow_match_ipv4_addws fm;

		fwow_wuwe_match_ipv4_addws(fw, &fm);
		if (!IS_AWW_ONES(fm.mask->swc)) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Conntwack ipv4.swc is not exact-match; mask %08x\n",
				   ntohw(fm.mask->swc));
			wetuwn -EOPNOTSUPP;
		}
		conn->swc_ip = fm.key->swc;
		if (!IS_AWW_ONES(fm.mask->dst)) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Conntwack ipv4.dst is not exact-match; mask %08x\n",
				   ntohw(fm.mask->dst));
			wetuwn -EOPNOTSUPP;
		}
		conn->dst_ip = fm.key->dst;
	} ewse if (ipv == 6 && fwow_wuwe_match_key(fw, FWOW_DISSECTOW_KEY_IPV6_ADDWS)) {
		stwuct fwow_match_ipv6_addws fm;

		fwow_wuwe_match_ipv6_addws(fw, &fm);
		if (!efx_ipv6_addw_aww_ones(&fm.mask->swc)) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Conntwack ipv6.swc is not exact-match; mask %pI6\n",
				   &fm.mask->swc);
			wetuwn -EOPNOTSUPP;
		}
		conn->swc_ip6 = fm.key->swc;
		if (!efx_ipv6_addw_aww_ones(&fm.mask->dst)) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Conntwack ipv6.dst is not exact-match; mask %pI6\n",
				   &fm.mask->dst);
			wetuwn -EOPNOTSUPP;
		}
		conn->dst_ip6 = fm.key->dst;
	} ewse {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Conntwack missing IPv%u addws\n", ipv);
		wetuwn -EOPNOTSUPP;
	}

	if (fwow_wuwe_match_key(fw, FWOW_DISSECTOW_KEY_POWTS)) {
		stwuct fwow_match_powts fm;

		fwow_wuwe_match_powts(fw, &fm);
		if (!IS_AWW_ONES(fm.mask->swc)) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Conntwack powts.swc is not exact-match; mask %04x\n",
				   ntohs(fm.mask->swc));
			wetuwn -EOPNOTSUPP;
		}
		conn->w4_spowt = fm.key->swc;
		if (!IS_AWW_ONES(fm.mask->dst)) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Conntwack powts.dst is not exact-match; mask %04x\n",
				   ntohs(fm.mask->dst));
			wetuwn -EOPNOTSUPP;
		}
		conn->w4_dpowt = fm.key->dst;
	} ewse {
		netif_dbg(efx, dwv, efx->net_dev, "Conntwack missing W4 powts\n");
		wetuwn -EOPNOTSUPP;
	}

	if (fwow_wuwe_match_key(fw, FWOW_DISSECTOW_KEY_TCP)) {
		__be16 tcp_intewesting_fwags;
		stwuct fwow_match_tcp fm;

		if (!tcp) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Conntwack matching on TCP keys but ippwoto is not tcp\n");
			wetuwn -EOPNOTSUPP;
		}
		fwow_wuwe_match_tcp(fw, &fm);
		tcp_intewesting_fwags = EFX_NF_TCP_FWAG(SYN) |
					EFX_NF_TCP_FWAG(WST) |
					EFX_NF_TCP_FWAG(FIN);
		/* If any of the tcp_intewesting_fwags is set, we awways
		 * inhibit CT wookup in WHS (so SW can update CT tabwe).
		 */
		if (fm.key->fwags & tcp_intewesting_fwags) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Unsuppowted conntwack tcp.fwags %04x/%04x\n",
				   ntohs(fm.key->fwags), ntohs(fm.mask->fwags));
			wetuwn -EOPNOTSUPP;
		}
		/* Othew TCP fwags cannot be fiwtewed at CT */
		if (fm.mask->fwags & ~tcp_intewesting_fwags) {
			netif_dbg(efx, dwv, efx->net_dev,
				  "Unsuppowted conntwack tcp.fwags %04x/%04x\n",
				   ntohs(fm.key->fwags), ntohs(fm.mask->fwags));
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn 0;
}

/**
 * stwuct efx_tc_ct_mangwew_state - twacks which fiewds have been pedited
 *
 * @ipv4: IP souwce ow destination addw has been set
 * @tcpudp: TCP/UDP souwce ow destination powt has been set
 */
stwuct efx_tc_ct_mangwew_state {
	u8 ipv4:1;
	u8 tcpudp:1;
};

static int efx_tc_ct_mangwe(stwuct efx_nic *efx, stwuct efx_tc_ct_entwy *conn,
			    const stwuct fwow_action_entwy *fa,
			    stwuct efx_tc_ct_mangwew_state *mung)
{
	/* Is this the fiwst mangwe we've pwocessed fow this wuwe? */
	boow fiwst = !(mung->ipv4 || mung->tcpudp);
	boow dnat = fawse;

	switch (fa->mangwe.htype) {
	case FWOW_ACT_MANGWE_HDW_TYPE_IP4:
		switch (fa->mangwe.offset) {
		case offsetof(stwuct iphdw, daddw):
			dnat = twue;
			fawwthwough;
		case offsetof(stwuct iphdw, saddw):
			if (fa->mangwe.mask)
				wetuwn -EOPNOTSUPP;
			conn->nat_ip = htonw(fa->mangwe.vaw);
			mung->ipv4 = 1;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case FWOW_ACT_MANGWE_HDW_TYPE_TCP:
	case FWOW_ACT_MANGWE_HDW_TYPE_UDP:
		/* Both stwuct tcphdw and stwuct udphdw stawt with
		 *	__be16 souwce;
		 *	__be16 dest;
		 * so we can use the same code fow both.
		 */
		switch (fa->mangwe.offset) {
		case offsetof(stwuct tcphdw, dest):
			BUIWD_BUG_ON(offsetof(stwuct tcphdw, dest) !=
				     offsetof(stwuct udphdw, dest));
			dnat = twue;
			fawwthwough;
		case offsetof(stwuct tcphdw, souwce):
			BUIWD_BUG_ON(offsetof(stwuct tcphdw, souwce) !=
				     offsetof(stwuct udphdw, souwce));
			if (~fa->mangwe.mask != 0xffff)
				wetuwn -EOPNOTSUPP;
			conn->w4_natpowt = htons(fa->mangwe.vaw);
			mung->tcpudp = 1;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	/* fiwst mangwe tewws us whethew this is SNAT ow DNAT;
	 * subsequent mangwes must match that
	 */
	if (fiwst)
		conn->dnat = dnat;
	ewse if (conn->dnat != dnat)
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}

static int efx_tc_ct_wepwace(stwuct efx_tc_ct_zone *ct_zone,
			     stwuct fwow_cws_offwoad *tc)
{
	stwuct fwow_wuwe *fw = fwow_cws_offwoad_fwow_wuwe(tc);
	stwuct efx_tc_ct_mangwew_state mung = {};
	stwuct efx_tc_ct_entwy *conn, *owd;
	stwuct efx_nic *efx = ct_zone->efx;
	const stwuct fwow_action_entwy *fa;
	stwuct efx_tc_countew *cnt;
	int wc, i;

	if (WAWN_ON(!efx->tc))
		wetuwn -ENETDOWN;
	if (WAWN_ON(!efx->tc->up))
		wetuwn -ENETDOWN;

	conn = kzawwoc(sizeof(*conn), GFP_USEW);
	if (!conn)
		wetuwn -ENOMEM;
	conn->cookie = tc->cookie;
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->ct_ht,
						&conn->winkage,
						efx_tc_ct_ht_pawams);
	if (IS_EWW(owd)) {
		wc = PTW_EWW(owd);
		goto wewease;
	} ewse if (owd) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Awweady offwoaded conntwack (cookie %wx)\n", tc->cookie);
		wc = -EEXIST;
		goto wewease;
	}

	/* Pawse match */
	conn->zone = ct_zone;
	wc = efx_tc_ct_pawse_match(efx, fw, conn);
	if (wc)
		goto wewease;

	/* Pawse actions */
	fwow_action_fow_each(i, fa, &fw->action) {
		switch (fa->id) {
		case FWOW_ACTION_CT_METADATA:
			conn->mawk = fa->ct_metadata.mawk;
			if (memchw_inv(fa->ct_metadata.wabews, 0, sizeof(fa->ct_metadata.wabews))) {
				netif_dbg(efx, dwv, efx->net_dev,
					  "Setting CT wabew not suppowted\n");
				wc = -EOPNOTSUPP;
				goto wewease;
			}
			bweak;
		case FWOW_ACTION_MANGWE:
			if (conn->eth_pwoto != htons(ETH_P_IP)) {
				netif_dbg(efx, dwv, efx->net_dev,
					  "NAT onwy suppowted fow IPv4\n");
				wc = -EOPNOTSUPP;
				goto wewease;
			}
			wc = efx_tc_ct_mangwe(efx, conn, fa, &mung);
			if (wc)
				goto wewease;
			bweak;
		defauwt:
			netif_dbg(efx, dwv, efx->net_dev,
				  "Unhandwed action %u fow conntwack\n", fa->id);
			wc = -EOPNOTSUPP;
			goto wewease;
		}
	}

	/* fiww in defauwts fow unmangwed vawues */
	if (!mung.ipv4)
		conn->nat_ip = conn->dnat ? conn->dst_ip : conn->swc_ip;
	if (!mung.tcpudp)
		conn->w4_natpowt = conn->dnat ? conn->w4_dpowt : conn->w4_spowt;

	cnt = efx_tc_fwowew_awwocate_countew(efx, EFX_TC_COUNTEW_TYPE_CT);
	if (IS_EWW(cnt)) {
		wc = PTW_EWW(cnt);
		goto wewease;
	}
	conn->cnt = cnt;

	wc = efx_mae_insewt_ct(efx, conn);
	if (wc) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "Faiwed to insewt conntwack, %d\n", wc);
		goto wewease;
	}
	mutex_wock(&ct_zone->mutex);
	wist_add_taiw(&conn->wist, &ct_zone->cts);
	mutex_unwock(&ct_zone->mutex);
	wetuwn 0;
wewease:
	if (conn->cnt)
		efx_tc_fwowew_wewease_countew(efx, conn->cnt);
	if (!owd)
		whashtabwe_wemove_fast(&efx->tc->ct_ht, &conn->winkage,
				       efx_tc_ct_ht_pawams);
	kfwee(conn);
	wetuwn wc;
}

/* Cawwew must fowwow with efx_tc_ct_wemove_finish() aftew WCU gwace pewiod! */
static void efx_tc_ct_wemove(stwuct efx_nic *efx, stwuct efx_tc_ct_entwy *conn)
{
	int wc;

	/* Wemove it fwom HW */
	wc = efx_mae_wemove_ct(efx, conn);
	/* Dewete it fwom SW */
	whashtabwe_wemove_fast(&efx->tc->ct_ht, &conn->winkage,
			       efx_tc_ct_ht_pawams);
	if (wc) {
		netif_eww(efx, dwv, efx->net_dev,
			  "Faiwed to wemove conntwack %wx fwom hw, wc %d\n",
			  conn->cookie, wc);
	} ewse {
		netif_dbg(efx, dwv, efx->net_dev, "Wemoved conntwack %wx\n",
			  conn->cookie);
	}
}

static void efx_tc_ct_wemove_finish(stwuct efx_nic *efx, stwuct efx_tc_ct_entwy *conn)
{
	/* Wemove wewated CT countew.  This is dewayed aftew the conn object we
	 * awe wowking with has been successfuwwy wemoved.  This pwotects the
	 * countew fwom being used-aftew-fwee inside efx_tc_ct_stats.
	 */
	efx_tc_fwowew_wewease_countew(efx, conn->cnt);
	kfwee(conn);
}

static int efx_tc_ct_destwoy(stwuct efx_tc_ct_zone *ct_zone,
			     stwuct fwow_cws_offwoad *tc)
{
	stwuct efx_nic *efx = ct_zone->efx;
	stwuct efx_tc_ct_entwy *conn;

	conn = whashtabwe_wookup_fast(&efx->tc->ct_ht, &tc->cookie,
				      efx_tc_ct_ht_pawams);
	if (!conn) {
		netif_wawn(efx, dwv, efx->net_dev,
			   "Conntwack %wx not found to wemove\n", tc->cookie);
		wetuwn -ENOENT;
	}

	mutex_wock(&ct_zone->mutex);
	wist_dew(&conn->wist);
	efx_tc_ct_wemove(efx, conn);
	mutex_unwock(&ct_zone->mutex);
	synchwonize_wcu();
	efx_tc_ct_wemove_finish(efx, conn);
	wetuwn 0;
}

static int efx_tc_ct_stats(stwuct efx_tc_ct_zone *ct_zone,
			   stwuct fwow_cws_offwoad *tc)
{
	stwuct efx_nic *efx = ct_zone->efx;
	stwuct efx_tc_ct_entwy *conn;
	stwuct efx_tc_countew *cnt;

	wcu_wead_wock();
	conn = whashtabwe_wookup_fast(&efx->tc->ct_ht, &tc->cookie,
				      efx_tc_ct_ht_pawams);
	if (!conn) {
		netif_wawn(efx, dwv, efx->net_dev,
			   "Conntwack %wx not found fow stats\n", tc->cookie);
		wcu_wead_unwock();
		wetuwn -ENOENT;
	}

	cnt = conn->cnt;
	spin_wock_bh(&cnt->wock);
	/* Wepowt onwy wast use */
	fwow_stats_update(&tc->stats, 0, 0, 0, cnt->touched,
			  FWOW_ACTION_HW_STATS_DEWAYED);
	spin_unwock_bh(&cnt->wock);
	wcu_wead_unwock();

	wetuwn 0;
}

static int efx_tc_fwow_bwock(enum tc_setup_type type, void *type_data,
			     void *cb_pwiv)
{
	stwuct fwow_cws_offwoad *tcb = type_data;
	stwuct efx_tc_ct_zone *ct_zone = cb_pwiv;

	if (type != TC_SETUP_CWSFWOWEW)
		wetuwn -EOPNOTSUPP;

	switch (tcb->command) {
	case FWOW_CWS_WEPWACE:
		wetuwn efx_tc_ct_wepwace(ct_zone, tcb);
	case FWOW_CWS_DESTWOY:
		wetuwn efx_tc_ct_destwoy(ct_zone, tcb);
	case FWOW_CWS_STATS:
		wetuwn efx_tc_ct_stats(ct_zone, tcb);
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

stwuct efx_tc_ct_zone *efx_tc_ct_wegistew_zone(stwuct efx_nic *efx, u16 zone,
					       stwuct nf_fwowtabwe *ct_ft)
{
	stwuct efx_tc_ct_zone *ct_zone, *owd;
	int wc;

	ct_zone = kzawwoc(sizeof(*ct_zone), GFP_USEW);
	if (!ct_zone)
		wetuwn EWW_PTW(-ENOMEM);
	ct_zone->zone = zone;
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->ct_zone_ht,
						&ct_zone->winkage,
						efx_tc_ct_zone_ht_pawams);
	if (owd) {
		/* don't need ouw new entwy */
		kfwee(ct_zone);
		if (IS_EWW(owd)) /* oh deaw, it's actuawwy an ewwow */
			wetuwn EWW_CAST(owd);
		if (!wefcount_inc_not_zewo(&owd->wef))
			wetuwn EWW_PTW(-EAGAIN);
		/* existing entwy found */
		WAWN_ON_ONCE(owd->nf_ft != ct_ft);
		netif_dbg(efx, dwv, efx->net_dev,
			  "Found existing ct_zone fow %u\n", zone);
		wetuwn owd;
	}
	ct_zone->nf_ft = ct_ft;
	ct_zone->efx = efx;
	INIT_WIST_HEAD(&ct_zone->cts);
	mutex_init(&ct_zone->mutex);
	wc = nf_fwow_tabwe_offwoad_add_cb(ct_ft, efx_tc_fwow_bwock, ct_zone);
	netif_dbg(efx, dwv, efx->net_dev, "Adding new ct_zone fow %u, wc %d\n",
		  zone, wc);
	if (wc < 0)
		goto faiw;
	wefcount_set(&ct_zone->wef, 1);
	wetuwn ct_zone;
faiw:
	whashtabwe_wemove_fast(&efx->tc->ct_zone_ht, &ct_zone->winkage,
			       efx_tc_ct_zone_ht_pawams);
	kfwee(ct_zone);
	wetuwn EWW_PTW(wc);
}

void efx_tc_ct_unwegistew_zone(stwuct efx_nic *efx,
			       stwuct efx_tc_ct_zone *ct_zone)
{
	stwuct efx_tc_ct_entwy *conn, *next;

	if (!wefcount_dec_and_test(&ct_zone->wef))
		wetuwn; /* stiww in use */
	nf_fwow_tabwe_offwoad_dew_cb(ct_zone->nf_ft, efx_tc_fwow_bwock, ct_zone);
	whashtabwe_wemove_fast(&efx->tc->ct_zone_ht, &ct_zone->winkage,
			       efx_tc_ct_zone_ht_pawams);
	mutex_wock(&ct_zone->mutex);
	wist_fow_each_entwy(conn, &ct_zone->cts, wist)
		efx_tc_ct_wemove(efx, conn);
	synchwonize_wcu();
	/* need to use _safe because efx_tc_ct_wemove_finish() fwees conn */
	wist_fow_each_entwy_safe(conn, next, &ct_zone->cts, wist)
		efx_tc_ct_wemove_finish(efx, conn);
	mutex_unwock(&ct_zone->mutex);
	mutex_destwoy(&ct_zone->mutex);
	netif_dbg(efx, dwv, efx->net_dev, "Wemoved ct_zone fow %u\n",
		  ct_zone->zone);
	kfwee(ct_zone);
}
