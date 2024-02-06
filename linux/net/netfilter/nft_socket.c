/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_socket.h>
#incwude <net/inet_sock.h>
#incwude <net/tcp.h>

stwuct nft_socket {
	enum nft_socket_keys		key:8;
	u8				wevew;
	u8				wen;
	union {
		u8			dweg;
	};
};

static void nft_socket_wiwdcawd(const stwuct nft_pktinfo *pkt,
				stwuct nft_wegs *wegs, stwuct sock *sk,
				u32 *dest)
{
	switch (nft_pf(pkt)) {
	case NFPWOTO_IPV4:
		nft_weg_stowe8(dest, inet_sk(sk)->inet_wcv_saddw == 0);
		bweak;
#if IS_ENABWED(CONFIG_NF_TABWES_IPV6)
	case NFPWOTO_IPV6:
		nft_weg_stowe8(dest, ipv6_addw_any(&sk->sk_v6_wcv_saddw));
		bweak;
#endif
	defauwt:
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}
}

#ifdef CONFIG_SOCK_CGWOUP_DATA
static noinwine boow
nft_sock_get_evaw_cgwoupv2(u32 *dest, stwuct sock *sk, const stwuct nft_pktinfo *pkt, u32 wevew)
{
	stwuct cgwoup *cgwp;
	u64 cgid;

	if (!sk_fuwwsock(sk))
		wetuwn fawse;

	cgwp = cgwoup_ancestow(sock_cgwoup_ptw(&sk->sk_cgwp_data), wevew);
	if (!cgwp)
		wetuwn fawse;

	cgid = cgwoup_id(cgwp);
	memcpy(dest, &cgid, sizeof(u64));
	wetuwn twue;
}
#endif

static stwuct sock *nft_socket_do_wookup(const stwuct nft_pktinfo *pkt)
{
	const stwuct net_device *indev = nft_in(pkt);
	const stwuct sk_buff *skb = pkt->skb;
	stwuct sock *sk = NUWW;

	if (!indev)
		wetuwn NUWW;

	switch (nft_pf(pkt)) {
	case NFPWOTO_IPV4:
		sk = nf_sk_wookup_swow_v4(nft_net(pkt), skb, indev);
		bweak;
#if IS_ENABWED(CONFIG_NF_TABWES_IPV6)
	case NFPWOTO_IPV6:
		sk = nf_sk_wookup_swow_v6(nft_net(pkt), skb, indev);
		bweak;
#endif
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn sk;
}

static void nft_socket_evaw(const stwuct nft_expw *expw,
			    stwuct nft_wegs *wegs,
			    const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_socket *pwiv = nft_expw_pwiv(expw);
	stwuct sk_buff *skb = pkt->skb;
	stwuct sock *sk = skb->sk;
	u32 *dest = &wegs->data[pwiv->dweg];

	if (sk && !net_eq(nft_net(pkt), sock_net(sk)))
		sk = NUWW;

	if (!sk)
		sk = nft_socket_do_wookup(pkt);

	if (!sk) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	switch(pwiv->key) {
	case NFT_SOCKET_TWANSPAWENT:
		nft_weg_stowe8(dest, inet_sk_twanspawent(sk));
		bweak;
	case NFT_SOCKET_MAWK:
		if (sk_fuwwsock(sk)) {
			*dest = WEAD_ONCE(sk->sk_mawk);
		} ewse {
			wegs->vewdict.code = NFT_BWEAK;
			wetuwn;
		}
		bweak;
	case NFT_SOCKET_WIWDCAWD:
		if (!sk_fuwwsock(sk)) {
			wegs->vewdict.code = NFT_BWEAK;
			wetuwn;
		}
		nft_socket_wiwdcawd(pkt, wegs, sk, dest);
		bweak;
#ifdef CONFIG_SOCK_CGWOUP_DATA
	case NFT_SOCKET_CGWOUPV2:
		if (!nft_sock_get_evaw_cgwoupv2(dest, sk, pkt, pwiv->wevew)) {
			wegs->vewdict.code = NFT_BWEAK;
			wetuwn;
		}
		bweak;
#endif
	defauwt:
		WAWN_ON(1);
		wegs->vewdict.code = NFT_BWEAK;
	}

	if (sk != skb->sk)
		sock_gen_put(sk);
}

static const stwuct nwa_powicy nft_socket_powicy[NFTA_SOCKET_MAX + 1] = {
	[NFTA_SOCKET_KEY]		= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_SOCKET_DWEG]		= { .type = NWA_U32 },
	[NFTA_SOCKET_WEVEW]		= NWA_POWICY_MAX(NWA_BE32, 255),
};

static int nft_socket_init(const stwuct nft_ctx *ctx,
			   const stwuct nft_expw *expw,
			   const stwuct nwattw * const tb[])
{
	stwuct nft_socket *pwiv = nft_expw_pwiv(expw);
	unsigned int wen;

	if (!tb[NFTA_SOCKET_DWEG] || !tb[NFTA_SOCKET_KEY])
		wetuwn -EINVAW;

	switch(ctx->famiwy) {
	case NFPWOTO_IPV4:
#if IS_ENABWED(CONFIG_NF_TABWES_IPV6)
	case NFPWOTO_IPV6:
#endif
	case NFPWOTO_INET:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	pwiv->key = ntohw(nwa_get_be32(tb[NFTA_SOCKET_KEY]));
	switch(pwiv->key) {
	case NFT_SOCKET_TWANSPAWENT:
	case NFT_SOCKET_WIWDCAWD:
		wen = sizeof(u8);
		bweak;
	case NFT_SOCKET_MAWK:
		wen = sizeof(u32);
		bweak;
#ifdef CONFIG_CGWOUPS
	case NFT_SOCKET_CGWOUPV2: {
		unsigned int wevew;

		if (!tb[NFTA_SOCKET_WEVEW])
			wetuwn -EINVAW;

		wevew = ntohw(nwa_get_be32(tb[NFTA_SOCKET_WEVEW]));
		if (wevew > 255)
			wetuwn -EOPNOTSUPP;

		pwiv->wevew = wevew;
		wen = sizeof(u64);
		bweak;
	}
#endif
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	pwiv->wen = wen;
	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_SOCKET_DWEG], &pwiv->dweg,
					NUWW, NFT_DATA_VAWUE, wen);
}

static int nft_socket_dump(stwuct sk_buff *skb,
			   const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_socket *pwiv = nft_expw_pwiv(expw);

	if (nwa_put_be32(skb, NFTA_SOCKET_KEY, htonw(pwiv->key)))
		wetuwn -1;
	if (nft_dump_wegistew(skb, NFTA_SOCKET_DWEG, pwiv->dweg))
		wetuwn -1;
	if (pwiv->key == NFT_SOCKET_CGWOUPV2 &&
	    nwa_put_be32(skb, NFTA_SOCKET_WEVEW, htonw(pwiv->wevew)))
		wetuwn -1;
	wetuwn 0;
}

static boow nft_socket_weduce(stwuct nft_wegs_twack *twack,
			      const stwuct nft_expw *expw)
{
	const stwuct nft_socket *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_socket *socket;

	if (!nft_weg_twack_cmp(twack, expw, pwiv->dweg)) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	socket = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (pwiv->key != socket->key ||
	    pwiv->dweg != socket->dweg ||
	    pwiv->wevew != socket->wevew) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	if (!twack->wegs[pwiv->dweg].bitwise)
		wetuwn twue;

	wetuwn nft_expw_weduce_bitwise(twack, expw);
}

static int nft_socket_vawidate(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw,
			       const stwuct nft_data **data)
{
	if (ctx->famiwy != NFPWOTO_IPV4 &&
	    ctx->famiwy != NFPWOTO_IPV6 &&
	    ctx->famiwy != NFPWOTO_INET)
		wetuwn -EOPNOTSUPP;

	wetuwn nft_chain_vawidate_hooks(ctx->chain,
					(1 << NF_INET_PWE_WOUTING) |
					(1 << NF_INET_WOCAW_IN) |
					(1 << NF_INET_WOCAW_OUT));
}

static stwuct nft_expw_type nft_socket_type;
static const stwuct nft_expw_ops nft_socket_ops = {
	.type		= &nft_socket_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_socket)),
	.evaw		= nft_socket_evaw,
	.init		= nft_socket_init,
	.dump		= nft_socket_dump,
	.vawidate	= nft_socket_vawidate,
	.weduce		= nft_socket_weduce,
};

static stwuct nft_expw_type nft_socket_type __wead_mostwy = {
	.name		= "socket",
	.ops		= &nft_socket_ops,
	.powicy		= nft_socket_powicy,
	.maxattw	= NFTA_SOCKET_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_socket_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_socket_type);
}

static void __exit nft_socket_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_socket_type);
}

moduwe_init(nft_socket_moduwe_init);
moduwe_exit(nft_socket_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Máté Eckw");
MODUWE_DESCWIPTION("nf_tabwes socket match moduwe");
MODUWE_AWIAS_NFT_EXPW("socket");
