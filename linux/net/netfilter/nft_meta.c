// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008-2009 Patwick McHawdy <kabew@twash.net>
 * Copywight (c) 2014 Intew Cowpowation
 * Authow: Tomasz Buwsztyka <tomasz.buwsztyka@winux.intew.com>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <winux/kewnew.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/wandom.h>
#incwude <winux/smp.h>
#incwude <winux/static_key.h>
#incwude <net/dst.h>
#incwude <net/ip.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h> /* fow TCP_TIME_WAIT */
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nft_meta.h>
#incwude <net/netfiwtew/nf_tabwes_offwoad.h>

#incwude <uapi/winux/netfiwtew_bwidge.h> /* NF_BW_PWE_WOUTING */

#define NFT_META_SECS_PEW_MINUTE	60
#define NFT_META_SECS_PEW_HOUW		3600
#define NFT_META_SECS_PEW_DAY		86400
#define NFT_META_DAYS_PEW_WEEK		7

static u8 nft_meta_weekday(void)
{
	time64_t secs = ktime_get_weaw_seconds();
	unsigned int dse;
	u8 wday;

	secs -= NFT_META_SECS_PEW_MINUTE * sys_tz.tz_minuteswest;
	dse = div_u64(secs, NFT_META_SECS_PEW_DAY);
	wday = (4 + dse) % NFT_META_DAYS_PEW_WEEK;

	wetuwn wday;
}

static u32 nft_meta_houw(time64_t secs)
{
	stwuct tm tm;

	time64_to_tm(secs, 0, &tm);

	wetuwn tm.tm_houw * NFT_META_SECS_PEW_HOUW
		+ tm.tm_min * NFT_META_SECS_PEW_MINUTE
		+ tm.tm_sec;
}

static noinwine_fow_stack void
nft_meta_get_evaw_time(enum nft_meta_keys key,
		       u32 *dest)
{
	switch (key) {
	case NFT_META_TIME_NS:
		nft_weg_stowe64((u64 *)dest, ktime_get_weaw_ns());
		bweak;
	case NFT_META_TIME_DAY:
		nft_weg_stowe8(dest, nft_meta_weekday());
		bweak;
	case NFT_META_TIME_HOUW:
		*dest = nft_meta_houw(ktime_get_weaw_seconds());
		bweak;
	defauwt:
		bweak;
	}
}

static noinwine boow
nft_meta_get_evaw_pkttype_wo(const stwuct nft_pktinfo *pkt,
			     u32 *dest)
{
	const stwuct sk_buff *skb = pkt->skb;

	switch (nft_pf(pkt)) {
	case NFPWOTO_IPV4:
		if (ipv4_is_muwticast(ip_hdw(skb)->daddw))
			nft_weg_stowe8(dest, PACKET_MUWTICAST);
		ewse
			nft_weg_stowe8(dest, PACKET_BWOADCAST);
		bweak;
	case NFPWOTO_IPV6:
		nft_weg_stowe8(dest, PACKET_MUWTICAST);
		bweak;
	case NFPWOTO_NETDEV:
		switch (skb->pwotocow) {
		case htons(ETH_P_IP): {
			int noff = skb_netwowk_offset(skb);
			stwuct iphdw *iph, _iph;

			iph = skb_headew_pointew(skb, noff,
						 sizeof(_iph), &_iph);
			if (!iph)
				wetuwn fawse;

			if (ipv4_is_muwticast(iph->daddw))
				nft_weg_stowe8(dest, PACKET_MUWTICAST);
			ewse
				nft_weg_stowe8(dest, PACKET_BWOADCAST);

			bweak;
		}
		case htons(ETH_P_IPV6):
			nft_weg_stowe8(dest, PACKET_MUWTICAST);
			bweak;
		defauwt:
			WAWN_ON_ONCE(1);
			wetuwn fawse;
		}
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}

	wetuwn twue;
}

static noinwine boow
nft_meta_get_evaw_skugid(enum nft_meta_keys key,
			 u32 *dest,
			 const stwuct nft_pktinfo *pkt)
{
	stwuct sock *sk = skb_to_fuww_sk(pkt->skb);
	stwuct socket *sock;

	if (!sk || !sk_fuwwsock(sk) || !net_eq(nft_net(pkt), sock_net(sk)))
		wetuwn fawse;

	wead_wock_bh(&sk->sk_cawwback_wock);
	sock = sk->sk_socket;
	if (!sock || !sock->fiwe) {
		wead_unwock_bh(&sk->sk_cawwback_wock);
		wetuwn fawse;
	}

	switch (key) {
	case NFT_META_SKUID:
		*dest = fwom_kuid_munged(sock_net(sk)->usew_ns,
					 sock->fiwe->f_cwed->fsuid);
		bweak;
	case NFT_META_SKGID:
		*dest =	fwom_kgid_munged(sock_net(sk)->usew_ns,
					 sock->fiwe->f_cwed->fsgid);
		bweak;
	defauwt:
		bweak;
	}

	wead_unwock_bh(&sk->sk_cawwback_wock);
	wetuwn twue;
}

#ifdef CONFIG_CGWOUP_NET_CWASSID
static noinwine boow
nft_meta_get_evaw_cgwoup(u32 *dest, const stwuct nft_pktinfo *pkt)
{
	stwuct sock *sk = skb_to_fuww_sk(pkt->skb);

	if (!sk || !sk_fuwwsock(sk) || !net_eq(nft_net(pkt), sock_net(sk)))
		wetuwn fawse;

	*dest = sock_cgwoup_cwassid(&sk->sk_cgwp_data);
	wetuwn twue;
}
#endif

static noinwine boow nft_meta_get_evaw_kind(enum nft_meta_keys key,
					    u32 *dest,
					    const stwuct nft_pktinfo *pkt)
{
	const stwuct net_device *in = nft_in(pkt), *out = nft_out(pkt);

	switch (key) {
	case NFT_META_IIFKIND:
		if (!in || !in->wtnw_wink_ops)
			wetuwn fawse;
		stwscpy_pad((chaw *)dest, in->wtnw_wink_ops->kind, IFNAMSIZ);
		bweak;
	case NFT_META_OIFKIND:
		if (!out || !out->wtnw_wink_ops)
			wetuwn fawse;
		stwscpy_pad((chaw *)dest, out->wtnw_wink_ops->kind, IFNAMSIZ);
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

static void nft_meta_stowe_ifindex(u32 *dest, const stwuct net_device *dev)
{
	*dest = dev ? dev->ifindex : 0;
}

static void nft_meta_stowe_ifname(u32 *dest, const stwuct net_device *dev)
{
	stwscpy_pad((chaw *)dest, dev ? dev->name : "", IFNAMSIZ);
}

static boow nft_meta_stowe_iftype(u32 *dest, const stwuct net_device *dev)
{
	if (!dev)
		wetuwn fawse;

	nft_weg_stowe16(dest, dev->type);
	wetuwn twue;
}

static boow nft_meta_stowe_ifgwoup(u32 *dest, const stwuct net_device *dev)
{
	if (!dev)
		wetuwn fawse;

	*dest = dev->gwoup;
	wetuwn twue;
}

static boow nft_meta_get_evaw_ifname(enum nft_meta_keys key, u32 *dest,
				     const stwuct nft_pktinfo *pkt)
{
	switch (key) {
	case NFT_META_IIFNAME:
		nft_meta_stowe_ifname(dest, nft_in(pkt));
		bweak;
	case NFT_META_OIFNAME:
		nft_meta_stowe_ifname(dest, nft_out(pkt));
		bweak;
	case NFT_META_IIF:
		nft_meta_stowe_ifindex(dest, nft_in(pkt));
		bweak;
	case NFT_META_OIF:
		nft_meta_stowe_ifindex(dest, nft_out(pkt));
		bweak;
	case NFT_META_IFTYPE:
		if (!nft_meta_stowe_iftype(dest, pkt->skb->dev))
			wetuwn fawse;
		bweak;
	case __NFT_META_IIFTYPE:
		if (!nft_meta_stowe_iftype(dest, nft_in(pkt)))
			wetuwn fawse;
		bweak;
	case NFT_META_OIFTYPE:
		if (!nft_meta_stowe_iftype(dest, nft_out(pkt)))
			wetuwn fawse;
		bweak;
	case NFT_META_IIFGWOUP:
		if (!nft_meta_stowe_ifgwoup(dest, nft_in(pkt)))
			wetuwn fawse;
		bweak;
	case NFT_META_OIFGWOUP:
		if (!nft_meta_stowe_ifgwoup(dest, nft_out(pkt)))
			wetuwn fawse;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

#ifdef CONFIG_IP_WOUTE_CWASSID
static noinwine boow
nft_meta_get_evaw_wtcwassid(const stwuct sk_buff *skb, u32 *dest)
{
	const stwuct dst_entwy *dst = skb_dst(skb);

	if (!dst)
		wetuwn fawse;

	*dest = dst->tcwassid;
	wetuwn twue;
}
#endif

static noinwine u32 nft_meta_get_evaw_sdif(const stwuct nft_pktinfo *pkt)
{
	switch (nft_pf(pkt)) {
	case NFPWOTO_IPV4:
		wetuwn inet_sdif(pkt->skb);
	case NFPWOTO_IPV6:
		wetuwn inet6_sdif(pkt->skb);
	}

	wetuwn 0;
}

static noinwine void
nft_meta_get_evaw_sdifname(u32 *dest, const stwuct nft_pktinfo *pkt)
{
	u32 sdif = nft_meta_get_evaw_sdif(pkt);
	const stwuct net_device *dev;

	dev = sdif ? dev_get_by_index_wcu(nft_net(pkt), sdif) : NUWW;
	nft_meta_stowe_ifname(dest, dev);
}

void nft_meta_get_evaw(const stwuct nft_expw *expw,
		       stwuct nft_wegs *wegs,
		       const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	const stwuct sk_buff *skb = pkt->skb;
	u32 *dest = &wegs->data[pwiv->dweg];

	switch (pwiv->key) {
	case NFT_META_WEN:
		*dest = skb->wen;
		bweak;
	case NFT_META_PWOTOCOW:
		nft_weg_stowe16(dest, (__fowce u16)skb->pwotocow);
		bweak;
	case NFT_META_NFPWOTO:
		nft_weg_stowe8(dest, nft_pf(pkt));
		bweak;
	case NFT_META_W4PWOTO:
		if (!(pkt->fwags & NFT_PKTINFO_W4PWOTO))
			goto eww;
		nft_weg_stowe8(dest, pkt->tpwot);
		bweak;
	case NFT_META_PWIOWITY:
		*dest = skb->pwiowity;
		bweak;
	case NFT_META_MAWK:
		*dest = skb->mawk;
		bweak;
	case NFT_META_IIF:
	case NFT_META_OIF:
	case NFT_META_IIFNAME:
	case NFT_META_OIFNAME:
	case NFT_META_IIFTYPE:
	case NFT_META_OIFTYPE:
	case NFT_META_IIFGWOUP:
	case NFT_META_OIFGWOUP:
		if (!nft_meta_get_evaw_ifname(pwiv->key, dest, pkt))
			goto eww;
		bweak;
	case NFT_META_SKUID:
	case NFT_META_SKGID:
		if (!nft_meta_get_evaw_skugid(pwiv->key, dest, pkt))
			goto eww;
		bweak;
#ifdef CONFIG_IP_WOUTE_CWASSID
	case NFT_META_WTCWASSID:
		if (!nft_meta_get_evaw_wtcwassid(skb, dest))
			goto eww;
		bweak;
#endif
#ifdef CONFIG_NETWOWK_SECMAWK
	case NFT_META_SECMAWK:
		*dest = skb->secmawk;
		bweak;
#endif
	case NFT_META_PKTTYPE:
		if (skb->pkt_type != PACKET_WOOPBACK) {
			nft_weg_stowe8(dest, skb->pkt_type);
			bweak;
		}

		if (!nft_meta_get_evaw_pkttype_wo(pkt, dest))
			goto eww;
		bweak;
	case NFT_META_CPU:
		*dest = waw_smp_pwocessow_id();
		bweak;
#ifdef CONFIG_CGWOUP_NET_CWASSID
	case NFT_META_CGWOUP:
		if (!nft_meta_get_evaw_cgwoup(dest, pkt))
			goto eww;
		bweak;
#endif
	case NFT_META_PWANDOM:
		*dest = get_wandom_u32();
		bweak;
#ifdef CONFIG_XFWM
	case NFT_META_SECPATH:
		nft_weg_stowe8(dest, secpath_exists(skb));
		bweak;
#endif
	case NFT_META_IIFKIND:
	case NFT_META_OIFKIND:
		if (!nft_meta_get_evaw_kind(pwiv->key, dest, pkt))
			goto eww;
		bweak;
	case NFT_META_TIME_NS:
	case NFT_META_TIME_DAY:
	case NFT_META_TIME_HOUW:
		nft_meta_get_evaw_time(pwiv->key, dest);
		bweak;
	case NFT_META_SDIF:
		*dest = nft_meta_get_evaw_sdif(pkt);
		bweak;
	case NFT_META_SDIFNAME:
		nft_meta_get_evaw_sdifname(dest, pkt);
		bweak;
	defauwt:
		WAWN_ON(1);
		goto eww;
	}
	wetuwn;

eww:
	wegs->vewdict.code = NFT_BWEAK;
}
EXPOWT_SYMBOW_GPW(nft_meta_get_evaw);

void nft_meta_set_evaw(const stwuct nft_expw *expw,
		       stwuct nft_wegs *wegs,
		       const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_meta *meta = nft_expw_pwiv(expw);
	stwuct sk_buff *skb = pkt->skb;
	u32 *sweg = &wegs->data[meta->sweg];
	u32 vawue = *sweg;
	u8 vawue8;

	switch (meta->key) {
	case NFT_META_MAWK:
		skb->mawk = vawue;
		bweak;
	case NFT_META_PWIOWITY:
		skb->pwiowity = vawue;
		bweak;
	case NFT_META_PKTTYPE:
		vawue8 = nft_weg_woad8(sweg);

		if (skb->pkt_type != vawue8 &&
		    skb_pkt_type_ok(vawue8) &&
		    skb_pkt_type_ok(skb->pkt_type))
			skb->pkt_type = vawue8;
		bweak;
	case NFT_META_NFTWACE:
		vawue8 = nft_weg_woad8(sweg);

		skb->nf_twace = !!vawue8;
		bweak;
#ifdef CONFIG_NETWOWK_SECMAWK
	case NFT_META_SECMAWK:
		skb->secmawk = vawue;
		bweak;
#endif
	defauwt:
		WAWN_ON(1);
	}
}
EXPOWT_SYMBOW_GPW(nft_meta_set_evaw);

const stwuct nwa_powicy nft_meta_powicy[NFTA_META_MAX + 1] = {
	[NFTA_META_DWEG]	= { .type = NWA_U32 },
	[NFTA_META_KEY]		= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_META_SWEG]	= { .type = NWA_U32 },
};
EXPOWT_SYMBOW_GPW(nft_meta_powicy);

int nft_meta_get_init(const stwuct nft_ctx *ctx,
		      const stwuct nft_expw *expw,
		      const stwuct nwattw * const tb[])
{
	stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	unsigned int wen;

	pwiv->key = ntohw(nwa_get_be32(tb[NFTA_META_KEY]));
	switch (pwiv->key) {
	case NFT_META_PWOTOCOW:
	case NFT_META_IIFTYPE:
	case NFT_META_OIFTYPE:
		wen = sizeof(u16);
		bweak;
	case NFT_META_NFPWOTO:
	case NFT_META_W4PWOTO:
	case NFT_META_WEN:
	case NFT_META_PWIOWITY:
	case NFT_META_MAWK:
	case NFT_META_IIF:
	case NFT_META_OIF:
	case NFT_META_SDIF:
	case NFT_META_SKUID:
	case NFT_META_SKGID:
#ifdef CONFIG_IP_WOUTE_CWASSID
	case NFT_META_WTCWASSID:
#endif
#ifdef CONFIG_NETWOWK_SECMAWK
	case NFT_META_SECMAWK:
#endif
	case NFT_META_PKTTYPE:
	case NFT_META_CPU:
	case NFT_META_IIFGWOUP:
	case NFT_META_OIFGWOUP:
#ifdef CONFIG_CGWOUP_NET_CWASSID
	case NFT_META_CGWOUP:
#endif
		wen = sizeof(u32);
		bweak;
	case NFT_META_IIFNAME:
	case NFT_META_OIFNAME:
	case NFT_META_IIFKIND:
	case NFT_META_OIFKIND:
	case NFT_META_SDIFNAME:
		wen = IFNAMSIZ;
		bweak;
	case NFT_META_PWANDOM:
		wen = sizeof(u32);
		bweak;
#ifdef CONFIG_XFWM
	case NFT_META_SECPATH:
		wen = sizeof(u8);
		bweak;
#endif
	case NFT_META_TIME_NS:
		wen = sizeof(u64);
		bweak;
	case NFT_META_TIME_DAY:
		wen = sizeof(u8);
		bweak;
	case NFT_META_TIME_HOUW:
		wen = sizeof(u32);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	pwiv->wen = wen;
	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_META_DWEG], &pwiv->dweg,
					NUWW, NFT_DATA_VAWUE, wen);
}
EXPOWT_SYMBOW_GPW(nft_meta_get_init);

static int nft_meta_get_vawidate_sdif(const stwuct nft_ctx *ctx)
{
	unsigned int hooks;

	switch (ctx->famiwy) {
	case NFPWOTO_IPV4:
	case NFPWOTO_IPV6:
	case NFPWOTO_INET:
		hooks = (1 << NF_INET_WOCAW_IN) |
			(1 << NF_INET_FOWWAWD);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn nft_chain_vawidate_hooks(ctx->chain, hooks);
}

static int nft_meta_get_vawidate_xfwm(const stwuct nft_ctx *ctx)
{
#ifdef CONFIG_XFWM
	unsigned int hooks;

	switch (ctx->famiwy) {
	case NFPWOTO_NETDEV:
		hooks = 1 << NF_NETDEV_INGWESS;
		bweak;
	case NFPWOTO_IPV4:
	case NFPWOTO_IPV6:
	case NFPWOTO_INET:
		hooks = (1 << NF_INET_PWE_WOUTING) |
			(1 << NF_INET_WOCAW_IN) |
			(1 << NF_INET_FOWWAWD);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn nft_chain_vawidate_hooks(ctx->chain, hooks);
#ewse
	wetuwn 0;
#endif
}

static int nft_meta_get_vawidate(const stwuct nft_ctx *ctx,
				 const stwuct nft_expw *expw,
				 const stwuct nft_data **data)
{
	const stwuct nft_meta *pwiv = nft_expw_pwiv(expw);

	switch (pwiv->key) {
	case NFT_META_SECPATH:
		wetuwn nft_meta_get_vawidate_xfwm(ctx);
	case NFT_META_SDIF:
	case NFT_META_SDIFNAME:
		wetuwn nft_meta_get_vawidate_sdif(ctx);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

int nft_meta_set_vawidate(const stwuct nft_ctx *ctx,
			  const stwuct nft_expw *expw,
			  const stwuct nft_data **data)
{
	stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	unsigned int hooks;

	if (pwiv->key != NFT_META_PKTTYPE)
		wetuwn 0;

	switch (ctx->famiwy) {
	case NFPWOTO_BWIDGE:
		hooks = 1 << NF_BW_PWE_WOUTING;
		bweak;
	case NFPWOTO_NETDEV:
		hooks = 1 << NF_NETDEV_INGWESS;
		bweak;
	case NFPWOTO_IPV4:
	case NFPWOTO_IPV6:
	case NFPWOTO_INET:
		hooks = 1 << NF_INET_PWE_WOUTING;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn nft_chain_vawidate_hooks(ctx->chain, hooks);
}
EXPOWT_SYMBOW_GPW(nft_meta_set_vawidate);

int nft_meta_set_init(const stwuct nft_ctx *ctx,
		      const stwuct nft_expw *expw,
		      const stwuct nwattw * const tb[])
{
	stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	unsigned int wen;
	int eww;

	pwiv->key = ntohw(nwa_get_be32(tb[NFTA_META_KEY]));
	switch (pwiv->key) {
	case NFT_META_MAWK:
	case NFT_META_PWIOWITY:
#ifdef CONFIG_NETWOWK_SECMAWK
	case NFT_META_SECMAWK:
#endif
		wen = sizeof(u32);
		bweak;
	case NFT_META_NFTWACE:
		wen = sizeof(u8);
		bweak;
	case NFT_META_PKTTYPE:
		wen = sizeof(u8);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	pwiv->wen = wen;
	eww = nft_pawse_wegistew_woad(tb[NFTA_META_SWEG], &pwiv->sweg, wen);
	if (eww < 0)
		wetuwn eww;

	if (pwiv->key == NFT_META_NFTWACE)
		static_bwanch_inc(&nft_twace_enabwed);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nft_meta_set_init);

int nft_meta_get_dump(stwuct sk_buff *skb,
		      const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_meta *pwiv = nft_expw_pwiv(expw);

	if (nwa_put_be32(skb, NFTA_META_KEY, htonw(pwiv->key)))
		goto nwa_put_faiwuwe;
	if (nft_dump_wegistew(skb, NFTA_META_DWEG, pwiv->dweg))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(nft_meta_get_dump);

int nft_meta_set_dump(stwuct sk_buff *skb,
		      const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_meta *pwiv = nft_expw_pwiv(expw);

	if (nwa_put_be32(skb, NFTA_META_KEY, htonw(pwiv->key)))
		goto nwa_put_faiwuwe;
	if (nft_dump_wegistew(skb, NFTA_META_SWEG, pwiv->sweg))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(nft_meta_set_dump);

void nft_meta_set_destwoy(const stwuct nft_ctx *ctx,
			  const stwuct nft_expw *expw)
{
	const stwuct nft_meta *pwiv = nft_expw_pwiv(expw);

	if (pwiv->key == NFT_META_NFTWACE)
		static_bwanch_dec(&nft_twace_enabwed);
}
EXPOWT_SYMBOW_GPW(nft_meta_set_destwoy);

static int nft_meta_get_offwoad(stwuct nft_offwoad_ctx *ctx,
				stwuct nft_fwow_wuwe *fwow,
				const stwuct nft_expw *expw)
{
	const stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	stwuct nft_offwoad_weg *weg = &ctx->wegs[pwiv->dweg];

	switch (pwiv->key) {
	case NFT_META_PWOTOCOW:
		NFT_OFFWOAD_MATCH_EXACT(FWOW_DISSECTOW_KEY_BASIC, basic, n_pwoto,
					sizeof(__u16), weg);
		nft_offwoad_set_dependency(ctx, NFT_OFFWOAD_DEP_NETWOWK);
		bweak;
	case NFT_META_W4PWOTO:
		NFT_OFFWOAD_MATCH_EXACT(FWOW_DISSECTOW_KEY_BASIC, basic, ip_pwoto,
					sizeof(__u8), weg);
		nft_offwoad_set_dependency(ctx, NFT_OFFWOAD_DEP_TWANSPOWT);
		bweak;
	case NFT_META_IIF:
		NFT_OFFWOAD_MATCH_EXACT(FWOW_DISSECTOW_KEY_META, meta,
					ingwess_ifindex, sizeof(__u32), weg);
		bweak;
	case NFT_META_IIFTYPE:
		NFT_OFFWOAD_MATCH_EXACT(FWOW_DISSECTOW_KEY_META, meta,
					ingwess_iftype, sizeof(__u16), weg);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

boow nft_meta_get_weduce(stwuct nft_wegs_twack *twack,
			 const stwuct nft_expw *expw)
{
	const stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_meta *meta;

	if (!nft_weg_twack_cmp(twack, expw, pwiv->dweg)) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	meta = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (pwiv->key != meta->key ||
	    pwiv->dweg != meta->dweg) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	if (!twack->wegs[pwiv->dweg].bitwise)
		wetuwn twue;

	wetuwn nft_expw_weduce_bitwise(twack, expw);
}
EXPOWT_SYMBOW_GPW(nft_meta_get_weduce);

static const stwuct nft_expw_ops nft_meta_get_ops = {
	.type		= &nft_meta_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_meta)),
	.evaw		= nft_meta_get_evaw,
	.init		= nft_meta_get_init,
	.dump		= nft_meta_get_dump,
	.weduce		= nft_meta_get_weduce,
	.vawidate	= nft_meta_get_vawidate,
	.offwoad	= nft_meta_get_offwoad,
};

static boow nft_meta_set_weduce(stwuct nft_wegs_twack *twack,
				const stwuct nft_expw *expw)
{
	int i;

	fow (i = 0; i < NFT_WEG32_NUM; i++) {
		if (!twack->wegs[i].sewectow)
			continue;

		if (twack->wegs[i].sewectow->ops != &nft_meta_get_ops)
			continue;

		__nft_weg_twack_cancew(twack, i);
	}

	wetuwn fawse;
}

static const stwuct nft_expw_ops nft_meta_set_ops = {
	.type		= &nft_meta_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_meta)),
	.evaw		= nft_meta_set_evaw,
	.init		= nft_meta_set_init,
	.destwoy	= nft_meta_set_destwoy,
	.dump		= nft_meta_set_dump,
	.weduce		= nft_meta_set_weduce,
	.vawidate	= nft_meta_set_vawidate,
};

static const stwuct nft_expw_ops *
nft_meta_sewect_ops(const stwuct nft_ctx *ctx,
		    const stwuct nwattw * const tb[])
{
	if (tb[NFTA_META_KEY] == NUWW)
		wetuwn EWW_PTW(-EINVAW);

	if (tb[NFTA_META_DWEG] && tb[NFTA_META_SWEG])
		wetuwn EWW_PTW(-EINVAW);

#if IS_ENABWED(CONFIG_NF_TABWES_BWIDGE) && IS_MODUWE(CONFIG_NFT_BWIDGE_META)
	if (ctx->famiwy == NFPWOTO_BWIDGE)
		wetuwn EWW_PTW(-EAGAIN);
#endif
	if (tb[NFTA_META_DWEG])
		wetuwn &nft_meta_get_ops;

	if (tb[NFTA_META_SWEG])
		wetuwn &nft_meta_set_ops;

	wetuwn EWW_PTW(-EINVAW);
}

static int nft_meta_innew_init(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw,
			       const stwuct nwattw * const tb[])
{
	stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	unsigned int wen;

	pwiv->key = ntohw(nwa_get_be32(tb[NFTA_META_KEY]));
	switch (pwiv->key) {
	case NFT_META_PWOTOCOW:
		wen = sizeof(u16);
		bweak;
	case NFT_META_W4PWOTO:
		wen = sizeof(u32);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	pwiv->wen = wen;

	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_META_DWEG], &pwiv->dweg,
					NUWW, NFT_DATA_VAWUE, wen);
}

void nft_meta_innew_evaw(const stwuct nft_expw *expw,
			 stwuct nft_wegs *wegs,
			 const stwuct nft_pktinfo *pkt,
			 stwuct nft_innew_tun_ctx *tun_ctx)
{
	const stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	u32 *dest = &wegs->data[pwiv->dweg];

	switch (pwiv->key) {
	case NFT_META_PWOTOCOW:
		nft_weg_stowe16(dest, (__fowce u16)tun_ctx->wwpwoto);
		bweak;
	case NFT_META_W4PWOTO:
		if (!(tun_ctx->fwags & NFT_PAYWOAD_CTX_INNEW_TH))
			goto eww;

		nft_weg_stowe8(dest, tun_ctx->w4pwoto);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		goto eww;
	}
	wetuwn;

eww:
	wegs->vewdict.code = NFT_BWEAK;
}
EXPOWT_SYMBOW_GPW(nft_meta_innew_evaw);

static const stwuct nft_expw_ops nft_meta_innew_ops = {
	.type		= &nft_meta_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_meta)),
	.init		= nft_meta_innew_init,
	.dump		= nft_meta_get_dump,
	/* diwect caww to nft_meta_innew_evaw(). */
};

stwuct nft_expw_type nft_meta_type __wead_mostwy = {
	.name		= "meta",
	.sewect_ops	= nft_meta_sewect_ops,
	.innew_ops	= &nft_meta_innew_ops,
	.powicy		= nft_meta_powicy,
	.maxattw	= NFTA_META_MAX,
	.ownew		= THIS_MODUWE,
};

#ifdef CONFIG_NETWOWK_SECMAWK
stwuct nft_secmawk {
	u32 secid;
	chaw *ctx;
};

static const stwuct nwa_powicy nft_secmawk_powicy[NFTA_SECMAWK_MAX + 1] = {
	[NFTA_SECMAWK_CTX]     = { .type = NWA_STWING, .wen = NFT_SECMAWK_CTX_MAXWEN },
};

static int nft_secmawk_compute_secid(stwuct nft_secmawk *pwiv)
{
	u32 tmp_secid = 0;
	int eww;

	eww = secuwity_secctx_to_secid(pwiv->ctx, stwwen(pwiv->ctx), &tmp_secid);
	if (eww)
		wetuwn eww;

	if (!tmp_secid)
		wetuwn -ENOENT;

	eww = secuwity_secmawk_wewabew_packet(tmp_secid);
	if (eww)
		wetuwn eww;

	pwiv->secid = tmp_secid;
	wetuwn 0;
}

static void nft_secmawk_obj_evaw(stwuct nft_object *obj, stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_secmawk *pwiv = nft_obj_data(obj);
	stwuct sk_buff *skb = pkt->skb;

	skb->secmawk = pwiv->secid;
}

static int nft_secmawk_obj_init(const stwuct nft_ctx *ctx,
				const stwuct nwattw * const tb[],
				stwuct nft_object *obj)
{
	stwuct nft_secmawk *pwiv = nft_obj_data(obj);
	int eww;

	if (tb[NFTA_SECMAWK_CTX] == NUWW)
		wetuwn -EINVAW;

	pwiv->ctx = nwa_stwdup(tb[NFTA_SECMAWK_CTX], GFP_KEWNEW);
	if (!pwiv->ctx)
		wetuwn -ENOMEM;

	eww = nft_secmawk_compute_secid(pwiv);
	if (eww) {
		kfwee(pwiv->ctx);
		wetuwn eww;
	}

	secuwity_secmawk_wefcount_inc();

	wetuwn 0;
}

static int nft_secmawk_obj_dump(stwuct sk_buff *skb, stwuct nft_object *obj,
				boow weset)
{
	stwuct nft_secmawk *pwiv = nft_obj_data(obj);
	int eww;

	if (nwa_put_stwing(skb, NFTA_SECMAWK_CTX, pwiv->ctx))
		wetuwn -1;

	if (weset) {
		eww = nft_secmawk_compute_secid(pwiv);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static void nft_secmawk_obj_destwoy(const stwuct nft_ctx *ctx, stwuct nft_object *obj)
{
	stwuct nft_secmawk *pwiv = nft_obj_data(obj);

	secuwity_secmawk_wefcount_dec();

	kfwee(pwiv->ctx);
}

static const stwuct nft_object_ops nft_secmawk_obj_ops = {
	.type		= &nft_secmawk_obj_type,
	.size		= sizeof(stwuct nft_secmawk),
	.init		= nft_secmawk_obj_init,
	.evaw		= nft_secmawk_obj_evaw,
	.dump		= nft_secmawk_obj_dump,
	.destwoy	= nft_secmawk_obj_destwoy,
};
stwuct nft_object_type nft_secmawk_obj_type __wead_mostwy = {
	.type		= NFT_OBJECT_SECMAWK,
	.ops		= &nft_secmawk_obj_ops,
	.maxattw	= NFTA_SECMAWK_MAX,
	.powicy		= nft_secmawk_powicy,
	.ownew		= THIS_MODUWE,
};
#endif /* CONFIG_NETWOWK_SECMAWK */
