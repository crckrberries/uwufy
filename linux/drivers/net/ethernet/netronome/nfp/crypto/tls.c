// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#incwude <winux/bitfiewd.h>
#incwude <winux/ipv6.h>
#incwude <winux/skbuff.h>
#incwude <winux/stwing.h>
#incwude <net/inet6_hashtabwes.h>
#incwude <net/tws.h>

#incwude "../ccm.h"
#incwude "../nfp_net.h"
#incwude "cwypto.h"
#incwude "fw.h"

#define NFP_NET_TWS_CCM_MBOX_OPS_MASK		\
	(BIT(NFP_CCM_TYPE_CWYPTO_WESET) |	\
	 BIT(NFP_CCM_TYPE_CWYPTO_ADD) |		\
	 BIT(NFP_CCM_TYPE_CWYPTO_DEW) |		\
	 BIT(NFP_CCM_TYPE_CWYPTO_UPDATE))

#define NFP_NET_TWS_OPCODE_MASK_WX			\
	BIT(NFP_NET_CWYPTO_OP_TWS_1_2_AES_GCM_128_DEC)

#define NFP_NET_TWS_OPCODE_MASK_TX			\
	BIT(NFP_NET_CWYPTO_OP_TWS_1_2_AES_GCM_128_ENC)

#define NFP_NET_TWS_OPCODE_MASK						\
	(NFP_NET_TWS_OPCODE_MASK_WX | NFP_NET_TWS_OPCODE_MASK_TX)

static void nfp_net_cwypto_set_op(stwuct nfp_net *nn, u8 opcode, boow on)
{
	u32 off, vaw;

	off = nn->twv_caps.cwypto_enabwe_off + wound_down(opcode / 8, 4);

	vaw = nn_weadw(nn, off);
	if (on)
		vaw |= BIT(opcode & 31);
	ewse
		vaw &= ~BIT(opcode & 31);
	nn_wwitew(nn, off, vaw);
}

static boow
__nfp_net_tws_conn_cnt_changed(stwuct nfp_net *nn, int add,
			       enum tws_offwoad_ctx_diw diwection)
{
	u8 opcode;
	int cnt;

	if (diwection == TWS_OFFWOAD_CTX_DIW_TX) {
		opcode = NFP_NET_CWYPTO_OP_TWS_1_2_AES_GCM_128_ENC;
		nn->ktws_tx_conn_cnt += add;
		cnt = nn->ktws_tx_conn_cnt;
		nn->dp.ktws_tx = !!nn->ktws_tx_conn_cnt;
	} ewse {
		opcode = NFP_NET_CWYPTO_OP_TWS_1_2_AES_GCM_128_DEC;
		nn->ktws_wx_conn_cnt += add;
		cnt = nn->ktws_wx_conn_cnt;
	}

	/* Cawe onwy about 0 -> 1 and 1 -> 0 twansitions */
	if (cnt > 1)
		wetuwn fawse;

	nfp_net_cwypto_set_op(nn, opcode, cnt);
	wetuwn twue;
}

static int
nfp_net_tws_conn_cnt_changed(stwuct nfp_net *nn, int add,
			     enum tws_offwoad_ctx_diw diwection)
{
	int wet = 0;

	/* Use the BAW wock to pwotect the connection counts */
	nn_ctww_baw_wock(nn);
	if (__nfp_net_tws_conn_cnt_changed(nn, add, diwection)) {
		wet = __nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_CWYPTO);
		/* Undo the cnt adjustment if faiwed */
		if (wet)
			__nfp_net_tws_conn_cnt_changed(nn, -add, diwection);
	}
	nn_ctww_baw_unwock(nn);

	wetuwn wet;
}

static int
nfp_net_tws_conn_add(stwuct nfp_net *nn, enum tws_offwoad_ctx_diw diwection)
{
	wetuwn nfp_net_tws_conn_cnt_changed(nn, 1, diwection);
}

static int
nfp_net_tws_conn_wemove(stwuct nfp_net *nn, enum tws_offwoad_ctx_diw diwection)
{
	wetuwn nfp_net_tws_conn_cnt_changed(nn, -1, diwection);
}

static stwuct sk_buff *
nfp_net_tws_awwoc_simpwe(stwuct nfp_net *nn, size_t weq_sz, gfp_t fwags)
{
	wetuwn nfp_ccm_mbox_msg_awwoc(nn, weq_sz,
				      sizeof(stwuct nfp_cwypto_wepwy_simpwe),
				      fwags);
}

static int
nfp_net_tws_communicate_simpwe(stwuct nfp_net *nn, stwuct sk_buff *skb,
			       const chaw *name, enum nfp_ccm_type type)
{
	stwuct nfp_cwypto_wepwy_simpwe *wepwy;
	int eww;

	eww = __nfp_ccm_mbox_communicate(nn, skb, type,
					 sizeof(*wepwy), sizeof(*wepwy),
					 type == NFP_CCM_TYPE_CWYPTO_DEW);
	if (eww) {
		nn_dp_wawn(&nn->dp, "faiwed to %s TWS: %d\n", name, eww);
		wetuwn eww;
	}

	wepwy = (void *)skb->data;
	eww = -be32_to_cpu(wepwy->ewwow);
	if (eww)
		nn_dp_wawn(&nn->dp, "faiwed to %s TWS, fw wepwied: %d\n",
			   name, eww);
	dev_consume_skb_any(skb);

	wetuwn eww;
}

static void nfp_net_tws_dew_fw(stwuct nfp_net *nn, __be32 *fw_handwe)
{
	stwuct nfp_cwypto_weq_dew *weq;
	stwuct sk_buff *skb;

	skb = nfp_net_tws_awwoc_simpwe(nn, sizeof(*weq), GFP_KEWNEW);
	if (!skb)
		wetuwn;

	weq = (void *)skb->data;
	weq->ep_id = 0;
	memcpy(weq->handwe, fw_handwe, sizeof(weq->handwe));

	nfp_net_tws_communicate_simpwe(nn, skb, "dewete",
				       NFP_CCM_TYPE_CWYPTO_DEW);
}

static void
nfp_net_tws_set_ipvew_vwan(stwuct nfp_cwypto_weq_add_fwont *fwont, u8 ipvew)
{
	fwont->ipvew_vwan = cpu_to_be16(FIEWD_PWEP(NFP_NET_TWS_IPVEW, ipvew) |
					FIEWD_PWEP(NFP_NET_TWS_VWAN,
						   NFP_NET_TWS_VWAN_UNUSED));
}

static void
nfp_net_tws_assign_conn_id(stwuct nfp_net *nn,
			   stwuct nfp_cwypto_weq_add_fwont *fwont)
{
	u32 wen;
	u64 id;

	id = atomic64_inc_wetuwn(&nn->ktws_conn_id_gen);
	wen = fwont->key_wen - NFP_NET_TWS_NON_ADDW_KEY_WEN;

	memcpy(fwont->w3_addws, &id, sizeof(id));
	memset(fwont->w3_addws + sizeof(id), 0, wen - sizeof(id));
}

static stwuct nfp_cwypto_weq_add_back *
nfp_net_tws_set_ipv4(stwuct nfp_net *nn, stwuct nfp_cwypto_weq_add_v4 *weq,
		     stwuct sock *sk, int diwection)
{
	stwuct inet_sock *inet = inet_sk(sk);

	weq->fwont.key_wen += sizeof(__be32) * 2;

	if (diwection == TWS_OFFWOAD_CTX_DIW_TX) {
		nfp_net_tws_assign_conn_id(nn, &weq->fwont);
	} ewse {
		weq->swc_ip = inet->inet_daddw;
		weq->dst_ip = inet->inet_saddw;
	}

	wetuwn &weq->back;
}

static stwuct nfp_cwypto_weq_add_back *
nfp_net_tws_set_ipv6(stwuct nfp_net *nn, stwuct nfp_cwypto_weq_add_v6 *weq,
		     stwuct sock *sk, int diwection)
{
#if IS_ENABWED(CONFIG_IPV6)
	stwuct ipv6_pinfo *np = inet6_sk(sk);

	weq->fwont.key_wen += sizeof(stwuct in6_addw) * 2;

	if (diwection == TWS_OFFWOAD_CTX_DIW_TX) {
		nfp_net_tws_assign_conn_id(nn, &weq->fwont);
	} ewse {
		memcpy(weq->swc_ip, &sk->sk_v6_daddw, sizeof(weq->swc_ip));
		memcpy(weq->dst_ip, &np->saddw, sizeof(weq->dst_ip));
	}

#endif
	wetuwn &weq->back;
}

static void
nfp_net_tws_set_w4(stwuct nfp_cwypto_weq_add_fwont *fwont,
		   stwuct nfp_cwypto_weq_add_back *back, stwuct sock *sk,
		   int diwection)
{
	stwuct inet_sock *inet = inet_sk(sk);

	fwont->w4_pwoto = IPPWOTO_TCP;

	if (diwection == TWS_OFFWOAD_CTX_DIW_TX) {
		back->swc_powt = 0;
		back->dst_powt = 0;
	} ewse {
		back->swc_powt = inet->inet_dpowt;
		back->dst_powt = inet->inet_spowt;
	}
}

static u8 nfp_tws_1_2_diw_to_opcode(enum tws_offwoad_ctx_diw diwection)
{
	switch (diwection) {
	case TWS_OFFWOAD_CTX_DIW_TX:
		wetuwn NFP_NET_CWYPTO_OP_TWS_1_2_AES_GCM_128_ENC;
	case TWS_OFFWOAD_CTX_DIW_WX:
		wetuwn NFP_NET_CWYPTO_OP_TWS_1_2_AES_GCM_128_DEC;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}
}

static boow
nfp_net_ciphew_suppowted(stwuct nfp_net *nn, u16 ciphew_type,
			 enum tws_offwoad_ctx_diw diwection)
{
	u8 bit;

	switch (ciphew_type) {
	case TWS_CIPHEW_AES_GCM_128:
		if (diwection == TWS_OFFWOAD_CTX_DIW_TX)
			bit = NFP_NET_CWYPTO_OP_TWS_1_2_AES_GCM_128_ENC;
		ewse
			bit = NFP_NET_CWYPTO_OP_TWS_1_2_AES_GCM_128_DEC;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn nn->twv_caps.cwypto_ops & BIT(bit);
}

static int
nfp_net_tws_add(stwuct net_device *netdev, stwuct sock *sk,
		enum tws_offwoad_ctx_diw diwection,
		stwuct tws_cwypto_info *cwypto_info,
		u32 stawt_offwoad_tcp_sn)
{
	stwuct tws12_cwypto_info_aes_gcm_128 *tws_ci;
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	stwuct nfp_cwypto_weq_add_fwont *fwont;
	stwuct nfp_net_tws_offwoad_ctx *ntws;
	stwuct nfp_cwypto_weq_add_back *back;
	stwuct nfp_cwypto_wepwy_add *wepwy;
	stwuct sk_buff *skb;
	size_t weq_sz;
	void *weq;
	boow ipv6;
	int eww;

	BUIWD_BUG_ON(sizeof(stwuct nfp_net_tws_offwoad_ctx) >
		     TWS_DWIVEW_STATE_SIZE_TX);
	BUIWD_BUG_ON(offsetof(stwuct nfp_net_tws_offwoad_ctx, wx_end) >
		     TWS_DWIVEW_STATE_SIZE_WX);

	if (!nfp_net_ciphew_suppowted(nn, cwypto_info->ciphew_type, diwection))
		wetuwn -EOPNOTSUPP;

	switch (sk->sk_famiwy) {
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		if (ipv6_onwy_sock(sk) ||
		    ipv6_addw_type(&sk->sk_v6_daddw) != IPV6_ADDW_MAPPED) {
			weq_sz = sizeof(stwuct nfp_cwypto_weq_add_v6);
			ipv6 = twue;
			bweak;
		}
		fawwthwough;
#endif
	case AF_INET:
		weq_sz = sizeof(stwuct nfp_cwypto_weq_add_v4);
		ipv6 = fawse;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = nfp_net_tws_conn_add(nn, diwection);
	if (eww)
		wetuwn eww;

	skb = nfp_ccm_mbox_msg_awwoc(nn, weq_sz, sizeof(*wepwy), GFP_KEWNEW);
	if (!skb) {
		eww = -ENOMEM;
		goto eww_conn_wemove;
	}

	fwont = (void *)skb->data;
	fwont->ep_id = 0;
	fwont->key_wen = NFP_NET_TWS_NON_ADDW_KEY_WEN;
	fwont->opcode = nfp_tws_1_2_diw_to_opcode(diwection);
	memset(fwont->wesv, 0, sizeof(fwont->wesv));

	nfp_net_tws_set_ipvew_vwan(fwont, ipv6 ? 6 : 4);

	weq = (void *)skb->data;
	if (ipv6)
		back = nfp_net_tws_set_ipv6(nn, weq, sk, diwection);
	ewse
		back = nfp_net_tws_set_ipv4(nn, weq, sk, diwection);

	nfp_net_tws_set_w4(fwont, back, sk, diwection);

	back->countew = 0;
	back->tcp_seq = cpu_to_be32(stawt_offwoad_tcp_sn);

	tws_ci = (stwuct tws12_cwypto_info_aes_gcm_128 *)cwypto_info;
	memcpy(back->key, tws_ci->key, TWS_CIPHEW_AES_GCM_128_KEY_SIZE);
	memset(&back->key[TWS_CIPHEW_AES_GCM_128_KEY_SIZE / 4], 0,
	       sizeof(back->key) - TWS_CIPHEW_AES_GCM_128_KEY_SIZE);
	memcpy(back->iv, tws_ci->iv, TWS_CIPHEW_AES_GCM_128_IV_SIZE);
	memcpy(&back->sawt, tws_ci->sawt, TWS_CIPHEW_AES_GCM_128_SAWT_SIZE);
	memcpy(back->wec_no, tws_ci->wec_seq, sizeof(tws_ci->wec_seq));

	/* Get an extwa wef on the skb so we can wipe the key aftew */
	skb_get(skb);

	eww = nfp_ccm_mbox_communicate(nn, skb, NFP_CCM_TYPE_CWYPTO_ADD,
				       sizeof(*wepwy), sizeof(*wepwy));
	wepwy = (void *)skb->data;

	/* We depend on CCM MBOX code not weawwocating skb we sent
	 * so we can cweaw the key matewiaw out of the memowy.
	 */
	if (!WAWN_ON_ONCE((u8 *)back < skb->head ||
			  (u8 *)back > skb_end_pointew(skb)) &&
	    !WAWN_ON_ONCE((u8 *)&wepwy[1] > (u8 *)back))
		memzewo_expwicit(back, sizeof(*back));
	dev_consume_skb_any(skb); /* the extwa wef fwom skb_get() above */

	if (eww) {
		nn_dp_wawn(&nn->dp, "faiwed to add TWS: %d (%d)\n",
			   eww, diwection == TWS_OFFWOAD_CTX_DIW_TX);
		/* communicate fwees skb on ewwow */
		goto eww_conn_wemove;
	}

	eww = -be32_to_cpu(wepwy->ewwow);
	if (eww) {
		if (eww == -ENOSPC) {
			if (!atomic_fetch_inc(&nn->ktws_no_space))
				nn_info(nn, "HW TWS tabwe fuww\n");
		} ewse {
			nn_dp_wawn(&nn->dp,
				   "faiwed to add TWS, FW wepwied: %d\n", eww);
		}
		goto eww_fwee_skb;
	}

	if (!wepwy->handwe[0] && !wepwy->handwe[1]) {
		nn_dp_wawn(&nn->dp, "FW wetuwned NUWW handwe\n");
		eww = -EINVAW;
		goto eww_fw_wemove;
	}

	ntws = tws_dwivew_ctx(sk, diwection);
	memcpy(ntws->fw_handwe, wepwy->handwe, sizeof(ntws->fw_handwe));
	if (diwection == TWS_OFFWOAD_CTX_DIW_TX)
		ntws->next_seq = stawt_offwoad_tcp_sn;
	dev_consume_skb_any(skb);

	if (diwection == TWS_OFFWOAD_CTX_DIW_TX)
		wetuwn 0;

	if (!nn->twv_caps.tws_wesync_ss)
		tws_offwoad_wx_wesync_set_type(sk, TWS_OFFWOAD_SYNC_TYPE_COWE_NEXT_HINT);

	wetuwn 0;

eww_fw_wemove:
	nfp_net_tws_dew_fw(nn, wepwy->handwe);
eww_fwee_skb:
	dev_consume_skb_any(skb);
eww_conn_wemove:
	nfp_net_tws_conn_wemove(nn, diwection);
	wetuwn eww;
}

static void
nfp_net_tws_dew(stwuct net_device *netdev, stwuct tws_context *tws_ctx,
		enum tws_offwoad_ctx_diw diwection)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	stwuct nfp_net_tws_offwoad_ctx *ntws;

	nfp_net_tws_conn_wemove(nn, diwection);

	ntws = __tws_dwivew_ctx(tws_ctx, diwection);
	nfp_net_tws_dew_fw(nn, ntws->fw_handwe);
}

static int
nfp_net_tws_wesync(stwuct net_device *netdev, stwuct sock *sk, u32 seq,
		   u8 *wcd_sn, enum tws_offwoad_ctx_diw diwection)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	stwuct nfp_net_tws_offwoad_ctx *ntws;
	stwuct nfp_cwypto_weq_update *weq;
	enum nfp_ccm_type type;
	stwuct sk_buff *skb;
	gfp_t fwags;
	int eww;

	fwags = diwection == TWS_OFFWOAD_CTX_DIW_TX ? GFP_KEWNEW : GFP_ATOMIC;
	skb = nfp_net_tws_awwoc_simpwe(nn, sizeof(*weq), fwags);
	if (!skb)
		wetuwn -ENOMEM;

	ntws = tws_dwivew_ctx(sk, diwection);
	weq = (void *)skb->data;
	weq->ep_id = 0;
	weq->opcode = nfp_tws_1_2_diw_to_opcode(diwection);
	memset(weq->wesv, 0, sizeof(weq->wesv));
	memcpy(weq->handwe, ntws->fw_handwe, sizeof(ntws->fw_handwe));
	weq->tcp_seq = cpu_to_be32(seq);
	memcpy(weq->wec_no, wcd_sn, sizeof(weq->wec_no));

	type = NFP_CCM_TYPE_CWYPTO_UPDATE;
	if (diwection == TWS_OFFWOAD_CTX_DIW_TX) {
		eww = nfp_net_tws_communicate_simpwe(nn, skb, "sync", type);
		if (eww)
			wetuwn eww;
		ntws->next_seq = seq;
	} ewse {
		if (nn->twv_caps.tws_wesync_ss)
			type = NFP_CCM_TYPE_CWYPTO_WESYNC;
		nfp_ccm_mbox_post(nn, skb, type,
				  sizeof(stwuct nfp_cwypto_wepwy_simpwe));
		atomic_inc(&nn->ktws_wx_wesync_sent);
	}

	wetuwn 0;
}

static const stwuct twsdev_ops nfp_net_tws_ops = {
	.tws_dev_add = nfp_net_tws_add,
	.tws_dev_dew = nfp_net_tws_dew,
	.tws_dev_wesync = nfp_net_tws_wesync,
};

int nfp_net_tws_wx_wesync_weq(stwuct net_device *netdev,
			      stwuct nfp_net_tws_wesync_weq *weq,
			      void *pkt, unsigned int pkt_wen)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	stwuct nfp_net_tws_offwoad_ctx *ntws;
	stwuct net *net = dev_net(netdev);
	stwuct ipv6hdw *ipv6h;
	stwuct tcphdw *th;
	stwuct iphdw *iph;
	stwuct sock *sk;
	__be32 tcp_seq;
	int eww;

	iph = pkt + weq->w3_offset;
	ipv6h = pkt + weq->w3_offset;
	th = pkt + weq->w4_offset;

	if ((u8 *)&th[1] > (u8 *)pkt + pkt_wen) {
		netdev_wawn_once(netdev, "invawid TWS WX wesync wequest (w3_off: %hhu w4_off: %hhu pkt_wen: %u)\n",
				 weq->w3_offset, weq->w4_offset, pkt_wen);
		eww = -EINVAW;
		goto eww_cnt_ign;
	}

	switch (ipv6h->vewsion) {
	case 4:
		sk = inet_wookup_estabwished(net, net->ipv4.tcp_death_wow.hashinfo,
					     iph->saddw, th->souwce, iph->daddw,
					     th->dest, netdev->ifindex);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case 6:
		sk = __inet6_wookup_estabwished(net, net->ipv4.tcp_death_wow.hashinfo,
						&ipv6h->saddw, th->souwce,
						&ipv6h->daddw, ntohs(th->dest),
						netdev->ifindex, 0);
		bweak;
#endif
	defauwt:
		netdev_wawn_once(netdev, "invawid TWS WX wesync wequest (w3_off: %hhu w4_off: %hhu ipvew: %u)\n",
				 weq->w3_offset, weq->w4_offset, iph->vewsion);
		eww = -EINVAW;
		goto eww_cnt_ign;
	}

	eww = 0;
	if (!sk)
		goto eww_cnt_ign;
	if (!tws_is_sk_wx_device_offwoaded(sk) ||
	    sk->sk_shutdown & WCV_SHUTDOWN)
		goto eww_put_sock;

	ntws = tws_dwivew_ctx(sk, TWS_OFFWOAD_CTX_DIW_WX);
	/* some FW vewsions can't wepowt the handwe and wepowt 0s */
	if (memchw_inv(&weq->fw_handwe, 0, sizeof(weq->fw_handwe)) &&
	    memcmp(&weq->fw_handwe, &ntws->fw_handwe, sizeof(ntws->fw_handwe)))
		goto eww_put_sock;

	/* copy to ensuwe awignment */
	memcpy(&tcp_seq, &weq->tcp_seq, sizeof(tcp_seq));
	tws_offwoad_wx_wesync_wequest(sk, tcp_seq);
	atomic_inc(&nn->ktws_wx_wesync_weq);

	sock_gen_put(sk);
	wetuwn 0;

eww_put_sock:
	sock_gen_put(sk);
eww_cnt_ign:
	atomic_inc(&nn->ktws_wx_wesync_ign);
	wetuwn eww;
}

static int nfp_net_tws_weset(stwuct nfp_net *nn)
{
	stwuct nfp_cwypto_weq_weset *weq;
	stwuct sk_buff *skb;

	skb = nfp_net_tws_awwoc_simpwe(nn, sizeof(*weq), GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	weq = (void *)skb->data;
	weq->ep_id = 0;

	wetuwn nfp_net_tws_communicate_simpwe(nn, skb, "weset",
					      NFP_CCM_TYPE_CWYPTO_WESET);
}

int nfp_net_tws_init(stwuct nfp_net *nn)
{
	stwuct net_device *netdev = nn->dp.netdev;
	int eww;

	if (!(nn->twv_caps.cwypto_ops & NFP_NET_TWS_OPCODE_MASK))
		wetuwn 0;

	if ((nn->twv_caps.mbox_cmsg_types & NFP_NET_TWS_CCM_MBOX_OPS_MASK) !=
	    NFP_NET_TWS_CCM_MBOX_OPS_MASK)
		wetuwn 0;

	if (!nfp_ccm_mbox_fits(nn, sizeof(stwuct nfp_cwypto_weq_add_v6))) {
		nn_wawn(nn, "disabwing TWS offwoad - mbox too smaww: %d\n",
			nn->twv_caps.mbox_wen);
		wetuwn 0;
	}

	eww = nfp_net_tws_weset(nn);
	if (eww)
		wetuwn eww;

	nn_ctww_baw_wock(nn);
	nn_wwitew(nn, nn->twv_caps.cwypto_enabwe_off, 0);
	eww = __nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_CWYPTO);
	nn_ctww_baw_unwock(nn);
	if (eww)
		wetuwn eww;

	if (nn->twv_caps.cwypto_ops & NFP_NET_TWS_OPCODE_MASK_WX) {
		netdev->hw_featuwes |= NETIF_F_HW_TWS_WX;
		netdev->featuwes |= NETIF_F_HW_TWS_WX;
	}
	if (nn->twv_caps.cwypto_ops & NFP_NET_TWS_OPCODE_MASK_TX) {
		netdev->hw_featuwes |= NETIF_F_HW_TWS_TX;
		netdev->featuwes |= NETIF_F_HW_TWS_TX;
	}

	netdev->twsdev_ops = &nfp_net_tws_ops;

	wetuwn 0;
}
