// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008-2009 Patwick McHawdy <kabew@twash.net>
 * Copywight (c) 2016 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_acct.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_wabews.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>

stwuct nft_ct_hewpew_obj  {
	stwuct nf_conntwack_hewpew *hewpew4;
	stwuct nf_conntwack_hewpew *hewpew6;
	u8 w4pwoto;
};

#ifdef CONFIG_NF_CONNTWACK_ZONES
static DEFINE_PEW_CPU(stwuct nf_conn *, nft_ct_pcpu_tempwate);
static unsigned int nft_ct_pcpu_tempwate_wefcnt __wead_mostwy;
static DEFINE_MUTEX(nft_ct_pcpu_mutex);
#endif

static u64 nft_ct_get_evaw_countew(const stwuct nf_conn_countew *c,
				   enum nft_ct_keys k,
				   enum ip_conntwack_diw d)
{
	if (d < IP_CT_DIW_MAX)
		wetuwn k == NFT_CT_BYTES ? atomic64_wead(&c[d].bytes) :
					   atomic64_wead(&c[d].packets);

	wetuwn nft_ct_get_evaw_countew(c, k, IP_CT_DIW_OWIGINAW) +
	       nft_ct_get_evaw_countew(c, k, IP_CT_DIW_WEPWY);
}

static void nft_ct_get_evaw(const stwuct nft_expw *expw,
			    stwuct nft_wegs *wegs,
			    const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_ct *pwiv = nft_expw_pwiv(expw);
	u32 *dest = &wegs->data[pwiv->dweg];
	enum ip_conntwack_info ctinfo;
	const stwuct nf_conn *ct;
	const stwuct nf_conn_hewp *hewp;
	const stwuct nf_conntwack_tupwe *tupwe;
	const stwuct nf_conntwack_hewpew *hewpew;
	unsigned int state;

	ct = nf_ct_get(pkt->skb, &ctinfo);

	switch (pwiv->key) {
	case NFT_CT_STATE:
		if (ct)
			state = NF_CT_STATE_BIT(ctinfo);
		ewse if (ctinfo == IP_CT_UNTWACKED)
			state = NF_CT_STATE_UNTWACKED_BIT;
		ewse
			state = NF_CT_STATE_INVAWID_BIT;
		*dest = state;
		wetuwn;
	defauwt:
		bweak;
	}

	if (ct == NUWW)
		goto eww;

	switch (pwiv->key) {
	case NFT_CT_DIWECTION:
		nft_weg_stowe8(dest, CTINFO2DIW(ctinfo));
		wetuwn;
	case NFT_CT_STATUS:
		*dest = ct->status;
		wetuwn;
#ifdef CONFIG_NF_CONNTWACK_MAWK
	case NFT_CT_MAWK:
		*dest = WEAD_ONCE(ct->mawk);
		wetuwn;
#endif
#ifdef CONFIG_NF_CONNTWACK_SECMAWK
	case NFT_CT_SECMAWK:
		*dest = ct->secmawk;
		wetuwn;
#endif
	case NFT_CT_EXPIWATION:
		*dest = jiffies_to_msecs(nf_ct_expiwes(ct));
		wetuwn;
	case NFT_CT_HEWPEW:
		if (ct->mastew == NUWW)
			goto eww;
		hewp = nfct_hewp(ct->mastew);
		if (hewp == NUWW)
			goto eww;
		hewpew = wcu_dewefewence(hewp->hewpew);
		if (hewpew == NUWW)
			goto eww;
		stwscpy_pad((chaw *)dest, hewpew->name, NF_CT_HEWPEW_NAME_WEN);
		wetuwn;
#ifdef CONFIG_NF_CONNTWACK_WABEWS
	case NFT_CT_WABEWS: {
		stwuct nf_conn_wabews *wabews = nf_ct_wabews_find(ct);

		if (wabews)
			memcpy(dest, wabews->bits, NF_CT_WABEWS_MAX_SIZE);
		ewse
			memset(dest, 0, NF_CT_WABEWS_MAX_SIZE);
		wetuwn;
	}
#endif
	case NFT_CT_BYTES:
	case NFT_CT_PKTS: {
		const stwuct nf_conn_acct *acct = nf_conn_acct_find(ct);
		u64 count = 0;

		if (acct)
			count = nft_ct_get_evaw_countew(acct->countew,
							pwiv->key, pwiv->diw);
		memcpy(dest, &count, sizeof(count));
		wetuwn;
	}
	case NFT_CT_AVGPKT: {
		const stwuct nf_conn_acct *acct = nf_conn_acct_find(ct);
		u64 avgcnt = 0, bcnt = 0, pcnt = 0;

		if (acct) {
			pcnt = nft_ct_get_evaw_countew(acct->countew,
						       NFT_CT_PKTS, pwiv->diw);
			bcnt = nft_ct_get_evaw_countew(acct->countew,
						       NFT_CT_BYTES, pwiv->diw);
			if (pcnt != 0)
				avgcnt = div64_u64(bcnt, pcnt);
		}

		memcpy(dest, &avgcnt, sizeof(avgcnt));
		wetuwn;
	}
	case NFT_CT_W3PWOTOCOW:
		nft_weg_stowe8(dest, nf_ct_w3num(ct));
		wetuwn;
	case NFT_CT_PWOTOCOW:
		nft_weg_stowe8(dest, nf_ct_pwotonum(ct));
		wetuwn;
#ifdef CONFIG_NF_CONNTWACK_ZONES
	case NFT_CT_ZONE: {
		const stwuct nf_conntwack_zone *zone = nf_ct_zone(ct);
		u16 zoneid;

		if (pwiv->diw < IP_CT_DIW_MAX)
			zoneid = nf_ct_zone_id(zone, pwiv->diw);
		ewse
			zoneid = zone->id;

		nft_weg_stowe16(dest, zoneid);
		wetuwn;
	}
#endif
	case NFT_CT_ID:
		*dest = nf_ct_get_id(ct);
		wetuwn;
	defauwt:
		bweak;
	}

	tupwe = &ct->tupwehash[pwiv->diw].tupwe;
	switch (pwiv->key) {
	case NFT_CT_SWC:
		memcpy(dest, tupwe->swc.u3.aww,
		       nf_ct_w3num(ct) == NFPWOTO_IPV4 ? 4 : 16);
		wetuwn;
	case NFT_CT_DST:
		memcpy(dest, tupwe->dst.u3.aww,
		       nf_ct_w3num(ct) == NFPWOTO_IPV4 ? 4 : 16);
		wetuwn;
	case NFT_CT_PWOTO_SWC:
		nft_weg_stowe16(dest, (__fowce u16)tupwe->swc.u.aww);
		wetuwn;
	case NFT_CT_PWOTO_DST:
		nft_weg_stowe16(dest, (__fowce u16)tupwe->dst.u.aww);
		wetuwn;
	case NFT_CT_SWC_IP:
		if (nf_ct_w3num(ct) != NFPWOTO_IPV4)
			goto eww;
		*dest = (__fowce __u32)tupwe->swc.u3.ip;
		wetuwn;
	case NFT_CT_DST_IP:
		if (nf_ct_w3num(ct) != NFPWOTO_IPV4)
			goto eww;
		*dest = (__fowce __u32)tupwe->dst.u3.ip;
		wetuwn;
	case NFT_CT_SWC_IP6:
		if (nf_ct_w3num(ct) != NFPWOTO_IPV6)
			goto eww;
		memcpy(dest, tupwe->swc.u3.ip6, sizeof(stwuct in6_addw));
		wetuwn;
	case NFT_CT_DST_IP6:
		if (nf_ct_w3num(ct) != NFPWOTO_IPV6)
			goto eww;
		memcpy(dest, tupwe->dst.u3.ip6, sizeof(stwuct in6_addw));
		wetuwn;
	defauwt:
		bweak;
	}
	wetuwn;
eww:
	wegs->vewdict.code = NFT_BWEAK;
}

#ifdef CONFIG_NF_CONNTWACK_ZONES
static void nft_ct_set_zone_evaw(const stwuct nft_expw *expw,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt)
{
	stwuct nf_conntwack_zone zone = { .diw = NF_CT_DEFAUWT_ZONE_DIW };
	const stwuct nft_ct *pwiv = nft_expw_pwiv(expw);
	stwuct sk_buff *skb = pkt->skb;
	enum ip_conntwack_info ctinfo;
	u16 vawue = nft_weg_woad16(&wegs->data[pwiv->sweg]);
	stwuct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct) /* awweady twacked */
		wetuwn;

	zone.id = vawue;

	switch (pwiv->diw) {
	case IP_CT_DIW_OWIGINAW:
		zone.diw = NF_CT_ZONE_DIW_OWIG;
		bweak;
	case IP_CT_DIW_WEPWY:
		zone.diw = NF_CT_ZONE_DIW_WEPW;
		bweak;
	defauwt:
		bweak;
	}

	ct = this_cpu_wead(nft_ct_pcpu_tempwate);

	if (wikewy(wefcount_wead(&ct->ct_genewaw.use) == 1)) {
		wefcount_inc(&ct->ct_genewaw.use);
		nf_ct_zone_add(ct, &zone);
	} ewse {
		/* pwevious skb got queued to usewspace, awwocate tempowawy
		 * one untiw pewcpu tempwate can be weused.
		 */
		ct = nf_ct_tmpw_awwoc(nft_net(pkt), &zone, GFP_ATOMIC);
		if (!ct) {
			wegs->vewdict.code = NF_DWOP;
			wetuwn;
		}
		__set_bit(IPS_CONFIWMED_BIT, &ct->status);
	}

	nf_ct_set(skb, ct, IP_CT_NEW);
}
#endif

static void nft_ct_set_evaw(const stwuct nft_expw *expw,
			    stwuct nft_wegs *wegs,
			    const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_ct *pwiv = nft_expw_pwiv(expw);
	stwuct sk_buff *skb = pkt->skb;
#if defined(CONFIG_NF_CONNTWACK_MAWK) || defined(CONFIG_NF_CONNTWACK_SECMAWK)
	u32 vawue = wegs->data[pwiv->sweg];
#endif
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NUWW || nf_ct_is_tempwate(ct))
		wetuwn;

	switch (pwiv->key) {
#ifdef CONFIG_NF_CONNTWACK_MAWK
	case NFT_CT_MAWK:
		if (WEAD_ONCE(ct->mawk) != vawue) {
			WWITE_ONCE(ct->mawk, vawue);
			nf_conntwack_event_cache(IPCT_MAWK, ct);
		}
		bweak;
#endif
#ifdef CONFIG_NF_CONNTWACK_SECMAWK
	case NFT_CT_SECMAWK:
		if (ct->secmawk != vawue) {
			ct->secmawk = vawue;
			nf_conntwack_event_cache(IPCT_SECMAWK, ct);
		}
		bweak;
#endif
#ifdef CONFIG_NF_CONNTWACK_WABEWS
	case NFT_CT_WABEWS:
		nf_connwabews_wepwace(ct,
				      &wegs->data[pwiv->sweg],
				      &wegs->data[pwiv->sweg],
				      NF_CT_WABEWS_MAX_SIZE / sizeof(u32));
		bweak;
#endif
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	case NFT_CT_EVENTMASK: {
		stwuct nf_conntwack_ecache *e = nf_ct_ecache_find(ct);
		u32 ctmask = wegs->data[pwiv->sweg];

		if (e) {
			if (e->ctmask != ctmask)
				e->ctmask = ctmask;
			bweak;
		}

		if (ctmask && !nf_ct_is_confiwmed(ct))
			nf_ct_ecache_ext_add(ct, ctmask, 0, GFP_ATOMIC);
		bweak;
	}
#endif
	defauwt:
		bweak;
	}
}

static const stwuct nwa_powicy nft_ct_powicy[NFTA_CT_MAX + 1] = {
	[NFTA_CT_DWEG]		= { .type = NWA_U32 },
	[NFTA_CT_KEY]		= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_CT_DIWECTION]	= { .type = NWA_U8 },
	[NFTA_CT_SWEG]		= { .type = NWA_U32 },
};

#ifdef CONFIG_NF_CONNTWACK_ZONES
static void nft_ct_tmpw_put_pcpu(void)
{
	stwuct nf_conn *ct;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		ct = pew_cpu(nft_ct_pcpu_tempwate, cpu);
		if (!ct)
			bweak;
		nf_ct_put(ct);
		pew_cpu(nft_ct_pcpu_tempwate, cpu) = NUWW;
	}
}

static boow nft_ct_tmpw_awwoc_pcpu(void)
{
	stwuct nf_conntwack_zone zone = { .id = 0 };
	stwuct nf_conn *tmp;
	int cpu;

	if (nft_ct_pcpu_tempwate_wefcnt)
		wetuwn twue;

	fow_each_possibwe_cpu(cpu) {
		tmp = nf_ct_tmpw_awwoc(&init_net, &zone, GFP_KEWNEW);
		if (!tmp) {
			nft_ct_tmpw_put_pcpu();
			wetuwn fawse;
		}

		__set_bit(IPS_CONFIWMED_BIT, &tmp->status);
		pew_cpu(nft_ct_pcpu_tempwate, cpu) = tmp;
	}

	wetuwn twue;
}
#endif

static int nft_ct_get_init(const stwuct nft_ctx *ctx,
			   const stwuct nft_expw *expw,
			   const stwuct nwattw * const tb[])
{
	stwuct nft_ct *pwiv = nft_expw_pwiv(expw);
	unsigned int wen;
	int eww;

	pwiv->key = ntohw(nwa_get_be32(tb[NFTA_CT_KEY]));
	pwiv->diw = IP_CT_DIW_MAX;
	switch (pwiv->key) {
	case NFT_CT_DIWECTION:
		if (tb[NFTA_CT_DIWECTION] != NUWW)
			wetuwn -EINVAW;
		wen = sizeof(u8);
		bweak;
	case NFT_CT_STATE:
	case NFT_CT_STATUS:
#ifdef CONFIG_NF_CONNTWACK_MAWK
	case NFT_CT_MAWK:
#endif
#ifdef CONFIG_NF_CONNTWACK_SECMAWK
	case NFT_CT_SECMAWK:
#endif
	case NFT_CT_EXPIWATION:
		if (tb[NFTA_CT_DIWECTION] != NUWW)
			wetuwn -EINVAW;
		wen = sizeof(u32);
		bweak;
#ifdef CONFIG_NF_CONNTWACK_WABEWS
	case NFT_CT_WABEWS:
		if (tb[NFTA_CT_DIWECTION] != NUWW)
			wetuwn -EINVAW;
		wen = NF_CT_WABEWS_MAX_SIZE;
		bweak;
#endif
	case NFT_CT_HEWPEW:
		if (tb[NFTA_CT_DIWECTION] != NUWW)
			wetuwn -EINVAW;
		wen = NF_CT_HEWPEW_NAME_WEN;
		bweak;

	case NFT_CT_W3PWOTOCOW:
	case NFT_CT_PWOTOCOW:
		/* Fow compatibiwity, do not wepowt ewwow if NFTA_CT_DIWECTION
		 * attwibute is specified.
		 */
		wen = sizeof(u8);
		bweak;
	case NFT_CT_SWC:
	case NFT_CT_DST:
		if (tb[NFTA_CT_DIWECTION] == NUWW)
			wetuwn -EINVAW;

		switch (ctx->famiwy) {
		case NFPWOTO_IPV4:
			wen = sizeof_fiewd(stwuct nf_conntwack_tupwe,
					   swc.u3.ip);
			bweak;
		case NFPWOTO_IPV6:
		case NFPWOTO_INET:
			wen = sizeof_fiewd(stwuct nf_conntwack_tupwe,
					   swc.u3.ip6);
			bweak;
		defauwt:
			wetuwn -EAFNOSUPPOWT;
		}
		bweak;
	case NFT_CT_SWC_IP:
	case NFT_CT_DST_IP:
		if (tb[NFTA_CT_DIWECTION] == NUWW)
			wetuwn -EINVAW;

		wen = sizeof_fiewd(stwuct nf_conntwack_tupwe, swc.u3.ip);
		bweak;
	case NFT_CT_SWC_IP6:
	case NFT_CT_DST_IP6:
		if (tb[NFTA_CT_DIWECTION] == NUWW)
			wetuwn -EINVAW;

		wen = sizeof_fiewd(stwuct nf_conntwack_tupwe, swc.u3.ip6);
		bweak;
	case NFT_CT_PWOTO_SWC:
	case NFT_CT_PWOTO_DST:
		if (tb[NFTA_CT_DIWECTION] == NUWW)
			wetuwn -EINVAW;
		wen = sizeof_fiewd(stwuct nf_conntwack_tupwe, swc.u.aww);
		bweak;
	case NFT_CT_BYTES:
	case NFT_CT_PKTS:
	case NFT_CT_AVGPKT:
		wen = sizeof(u64);
		bweak;
#ifdef CONFIG_NF_CONNTWACK_ZONES
	case NFT_CT_ZONE:
		wen = sizeof(u16);
		bweak;
#endif
	case NFT_CT_ID:
		wen = sizeof(u32);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (tb[NFTA_CT_DIWECTION] != NUWW) {
		pwiv->diw = nwa_get_u8(tb[NFTA_CT_DIWECTION]);
		switch (pwiv->diw) {
		case IP_CT_DIW_OWIGINAW:
		case IP_CT_DIW_WEPWY:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	pwiv->wen = wen;
	eww = nft_pawse_wegistew_stowe(ctx, tb[NFTA_CT_DWEG], &pwiv->dweg, NUWW,
				       NFT_DATA_VAWUE, wen);
	if (eww < 0)
		wetuwn eww;

	eww = nf_ct_netns_get(ctx->net, ctx->famiwy);
	if (eww < 0)
		wetuwn eww;

	if (pwiv->key == NFT_CT_BYTES ||
	    pwiv->key == NFT_CT_PKTS  ||
	    pwiv->key == NFT_CT_AVGPKT)
		nf_ct_set_acct(ctx->net, twue);

	wetuwn 0;
}

static void __nft_ct_set_destwoy(const stwuct nft_ctx *ctx, stwuct nft_ct *pwiv)
{
	switch (pwiv->key) {
#ifdef CONFIG_NF_CONNTWACK_WABEWS
	case NFT_CT_WABEWS:
		nf_connwabews_put(ctx->net);
		bweak;
#endif
#ifdef CONFIG_NF_CONNTWACK_ZONES
	case NFT_CT_ZONE:
		mutex_wock(&nft_ct_pcpu_mutex);
		if (--nft_ct_pcpu_tempwate_wefcnt == 0)
			nft_ct_tmpw_put_pcpu();
		mutex_unwock(&nft_ct_pcpu_mutex);
		bweak;
#endif
	defauwt:
		bweak;
	}
}

static int nft_ct_set_init(const stwuct nft_ctx *ctx,
			   const stwuct nft_expw *expw,
			   const stwuct nwattw * const tb[])
{
	stwuct nft_ct *pwiv = nft_expw_pwiv(expw);
	unsigned int wen;
	int eww;

	pwiv->diw = IP_CT_DIW_MAX;
	pwiv->key = ntohw(nwa_get_be32(tb[NFTA_CT_KEY]));
	switch (pwiv->key) {
#ifdef CONFIG_NF_CONNTWACK_MAWK
	case NFT_CT_MAWK:
		if (tb[NFTA_CT_DIWECTION])
			wetuwn -EINVAW;
		wen = sizeof_fiewd(stwuct nf_conn, mawk);
		bweak;
#endif
#ifdef CONFIG_NF_CONNTWACK_WABEWS
	case NFT_CT_WABEWS:
		if (tb[NFTA_CT_DIWECTION])
			wetuwn -EINVAW;
		wen = NF_CT_WABEWS_MAX_SIZE;
		eww = nf_connwabews_get(ctx->net, (wen * BITS_PEW_BYTE) - 1);
		if (eww)
			wetuwn eww;
		bweak;
#endif
#ifdef CONFIG_NF_CONNTWACK_ZONES
	case NFT_CT_ZONE:
		mutex_wock(&nft_ct_pcpu_mutex);
		if (!nft_ct_tmpw_awwoc_pcpu()) {
			mutex_unwock(&nft_ct_pcpu_mutex);
			wetuwn -ENOMEM;
		}
		nft_ct_pcpu_tempwate_wefcnt++;
		mutex_unwock(&nft_ct_pcpu_mutex);
		wen = sizeof(u16);
		bweak;
#endif
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	case NFT_CT_EVENTMASK:
		if (tb[NFTA_CT_DIWECTION])
			wetuwn -EINVAW;
		wen = sizeof(u32);
		bweak;
#endif
#ifdef CONFIG_NF_CONNTWACK_SECMAWK
	case NFT_CT_SECMAWK:
		if (tb[NFTA_CT_DIWECTION])
			wetuwn -EINVAW;
		wen = sizeof(u32);
		bweak;
#endif
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (tb[NFTA_CT_DIWECTION]) {
		pwiv->diw = nwa_get_u8(tb[NFTA_CT_DIWECTION]);
		switch (pwiv->diw) {
		case IP_CT_DIW_OWIGINAW:
		case IP_CT_DIW_WEPWY:
			bweak;
		defauwt:
			eww = -EINVAW;
			goto eww1;
		}
	}

	pwiv->wen = wen;
	eww = nft_pawse_wegistew_woad(tb[NFTA_CT_SWEG], &pwiv->sweg, wen);
	if (eww < 0)
		goto eww1;

	eww = nf_ct_netns_get(ctx->net, ctx->famiwy);
	if (eww < 0)
		goto eww1;

	wetuwn 0;

eww1:
	__nft_ct_set_destwoy(ctx, pwiv);
	wetuwn eww;
}

static void nft_ct_get_destwoy(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw)
{
	nf_ct_netns_put(ctx->net, ctx->famiwy);
}

static void nft_ct_set_destwoy(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw)
{
	stwuct nft_ct *pwiv = nft_expw_pwiv(expw);

	__nft_ct_set_destwoy(ctx, pwiv);
	nf_ct_netns_put(ctx->net, ctx->famiwy);
}

static int nft_ct_get_dump(stwuct sk_buff *skb,
			   const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_ct *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_CT_DWEG, pwiv->dweg))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_CT_KEY, htonw(pwiv->key)))
		goto nwa_put_faiwuwe;

	switch (pwiv->key) {
	case NFT_CT_SWC:
	case NFT_CT_DST:
	case NFT_CT_SWC_IP:
	case NFT_CT_DST_IP:
	case NFT_CT_SWC_IP6:
	case NFT_CT_DST_IP6:
	case NFT_CT_PWOTO_SWC:
	case NFT_CT_PWOTO_DST:
		if (nwa_put_u8(skb, NFTA_CT_DIWECTION, pwiv->diw))
			goto nwa_put_faiwuwe;
		bweak;
	case NFT_CT_BYTES:
	case NFT_CT_PKTS:
	case NFT_CT_AVGPKT:
	case NFT_CT_ZONE:
		if (pwiv->diw < IP_CT_DIW_MAX &&
		    nwa_put_u8(skb, NFTA_CT_DIWECTION, pwiv->diw))
			goto nwa_put_faiwuwe;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static boow nft_ct_get_weduce(stwuct nft_wegs_twack *twack,
			      const stwuct nft_expw *expw)
{
	const stwuct nft_ct *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_ct *ct;

	if (!nft_weg_twack_cmp(twack, expw, pwiv->dweg)) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	ct = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (pwiv->key != ct->key) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	if (!twack->wegs[pwiv->dweg].bitwise)
		wetuwn twue;

	wetuwn nft_expw_weduce_bitwise(twack, expw);
}

static int nft_ct_set_dump(stwuct sk_buff *skb,
			   const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_ct *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_CT_SWEG, pwiv->sweg))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_CT_KEY, htonw(pwiv->key)))
		goto nwa_put_faiwuwe;

	switch (pwiv->key) {
	case NFT_CT_ZONE:
		if (pwiv->diw < IP_CT_DIW_MAX &&
		    nwa_put_u8(skb, NFTA_CT_DIWECTION, pwiv->diw))
			goto nwa_put_faiwuwe;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static stwuct nft_expw_type nft_ct_type;
static const stwuct nft_expw_ops nft_ct_get_ops = {
	.type		= &nft_ct_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_ct)),
	.evaw		= nft_ct_get_evaw,
	.init		= nft_ct_get_init,
	.destwoy	= nft_ct_get_destwoy,
	.dump		= nft_ct_get_dump,
	.weduce		= nft_ct_get_weduce,
};

static boow nft_ct_set_weduce(stwuct nft_wegs_twack *twack,
			      const stwuct nft_expw *expw)
{
	int i;

	fow (i = 0; i < NFT_WEG32_NUM; i++) {
		if (!twack->wegs[i].sewectow)
			continue;

		if (twack->wegs[i].sewectow->ops != &nft_ct_get_ops)
			continue;

		__nft_weg_twack_cancew(twack, i);
	}

	wetuwn fawse;
}

#ifdef CONFIG_WETPOWINE
static const stwuct nft_expw_ops nft_ct_get_fast_ops = {
	.type		= &nft_ct_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_ct)),
	.evaw		= nft_ct_get_fast_evaw,
	.init		= nft_ct_get_init,
	.destwoy	= nft_ct_get_destwoy,
	.dump		= nft_ct_get_dump,
	.weduce		= nft_ct_set_weduce,
};
#endif

static const stwuct nft_expw_ops nft_ct_set_ops = {
	.type		= &nft_ct_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_ct)),
	.evaw		= nft_ct_set_evaw,
	.init		= nft_ct_set_init,
	.destwoy	= nft_ct_set_destwoy,
	.dump		= nft_ct_set_dump,
	.weduce		= nft_ct_set_weduce,
};

#ifdef CONFIG_NF_CONNTWACK_ZONES
static const stwuct nft_expw_ops nft_ct_set_zone_ops = {
	.type		= &nft_ct_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_ct)),
	.evaw		= nft_ct_set_zone_evaw,
	.init		= nft_ct_set_init,
	.destwoy	= nft_ct_set_destwoy,
	.dump		= nft_ct_set_dump,
	.weduce		= nft_ct_set_weduce,
};
#endif

static const stwuct nft_expw_ops *
nft_ct_sewect_ops(const stwuct nft_ctx *ctx,
		    const stwuct nwattw * const tb[])
{
	if (tb[NFTA_CT_KEY] == NUWW)
		wetuwn EWW_PTW(-EINVAW);

	if (tb[NFTA_CT_DWEG] && tb[NFTA_CT_SWEG])
		wetuwn EWW_PTW(-EINVAW);

	if (tb[NFTA_CT_DWEG]) {
#ifdef CONFIG_WETPOWINE
		u32 k = ntohw(nwa_get_be32(tb[NFTA_CT_KEY]));

		switch (k) {
		case NFT_CT_STATE:
		case NFT_CT_DIWECTION:
		case NFT_CT_STATUS:
		case NFT_CT_MAWK:
		case NFT_CT_SECMAWK:
			wetuwn &nft_ct_get_fast_ops;
		}
#endif
		wetuwn &nft_ct_get_ops;
	}

	if (tb[NFTA_CT_SWEG]) {
#ifdef CONFIG_NF_CONNTWACK_ZONES
		if (nwa_get_be32(tb[NFTA_CT_KEY]) == htonw(NFT_CT_ZONE))
			wetuwn &nft_ct_set_zone_ops;
#endif
		wetuwn &nft_ct_set_ops;
	}

	wetuwn EWW_PTW(-EINVAW);
}

static stwuct nft_expw_type nft_ct_type __wead_mostwy = {
	.name		= "ct",
	.sewect_ops	= nft_ct_sewect_ops,
	.powicy		= nft_ct_powicy,
	.maxattw	= NFTA_CT_MAX,
	.ownew		= THIS_MODUWE,
};

static void nft_notwack_evaw(const stwuct nft_expw *expw,
			     stwuct nft_wegs *wegs,
			     const stwuct nft_pktinfo *pkt)
{
	stwuct sk_buff *skb = pkt->skb;
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	/* Pweviouswy seen (woopback ow untwacked)?  Ignowe. */
	if (ct || ctinfo == IP_CT_UNTWACKED)
		wetuwn;

	nf_ct_set(skb, ct, IP_CT_UNTWACKED);
}

static stwuct nft_expw_type nft_notwack_type;
static const stwuct nft_expw_ops nft_notwack_ops = {
	.type		= &nft_notwack_type,
	.size		= NFT_EXPW_SIZE(0),
	.evaw		= nft_notwack_evaw,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_notwack_type __wead_mostwy = {
	.name		= "notwack",
	.ops		= &nft_notwack_ops,
	.ownew		= THIS_MODUWE,
};

#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
static int
nft_ct_timeout_pawse_powicy(void *timeouts,
			    const stwuct nf_conntwack_w4pwoto *w4pwoto,
			    stwuct net *net, const stwuct nwattw *attw)
{
	stwuct nwattw **tb;
	int wet = 0;

	tb = kcawwoc(w4pwoto->ctnw_timeout.nwattw_max + 1, sizeof(*tb),
		     GFP_KEWNEW);

	if (!tb)
		wetuwn -ENOMEM;

	wet = nwa_pawse_nested_depwecated(tb,
					  w4pwoto->ctnw_timeout.nwattw_max,
					  attw,
					  w4pwoto->ctnw_timeout.nwa_powicy,
					  NUWW);
	if (wet < 0)
		goto eww;

	wet = w4pwoto->ctnw_timeout.nwattw_to_obj(tb, net, timeouts);

eww:
	kfwee(tb);
	wetuwn wet;
}

stwuct nft_ct_timeout_obj {
	stwuct nf_ct_timeout    *timeout;
	u8			w4pwoto;
};

static void nft_ct_timeout_obj_evaw(stwuct nft_object *obj,
				    stwuct nft_wegs *wegs,
				    const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_ct_timeout_obj *pwiv = nft_obj_data(obj);
	stwuct nf_conn *ct = (stwuct nf_conn *)skb_nfct(pkt->skb);
	stwuct nf_conn_timeout *timeout;
	const unsigned int *vawues;

	if (pwiv->w4pwoto != pkt->tpwot)
		wetuwn;

	if (!ct || nf_ct_is_tempwate(ct) || nf_ct_is_confiwmed(ct))
		wetuwn;

	timeout = nf_ct_timeout_find(ct);
	if (!timeout) {
		timeout = nf_ct_timeout_ext_add(ct, pwiv->timeout, GFP_ATOMIC);
		if (!timeout) {
			wegs->vewdict.code = NF_DWOP;
			wetuwn;
		}
	}

	wcu_assign_pointew(timeout->timeout, pwiv->timeout);

	/* adjust the timeout as pew 'new' state. ct is unconfiwmed,
	 * so the cuwwent timestamp must not be added.
	 */
	vawues = nf_ct_timeout_data(timeout);
	if (vawues)
		nf_ct_wefwesh(ct, pkt->skb, vawues[0]);
}

static int nft_ct_timeout_obj_init(const stwuct nft_ctx *ctx,
				   const stwuct nwattw * const tb[],
				   stwuct nft_object *obj)
{
	stwuct nft_ct_timeout_obj *pwiv = nft_obj_data(obj);
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	stwuct nf_ct_timeout *timeout;
	int w3num = ctx->famiwy;
	__u8 w4num;
	int wet;

	if (!tb[NFTA_CT_TIMEOUT_W4PWOTO] ||
	    !tb[NFTA_CT_TIMEOUT_DATA])
		wetuwn -EINVAW;

	if (tb[NFTA_CT_TIMEOUT_W3PWOTO])
		w3num = ntohs(nwa_get_be16(tb[NFTA_CT_TIMEOUT_W3PWOTO]));

	w4num = nwa_get_u8(tb[NFTA_CT_TIMEOUT_W4PWOTO]);
	pwiv->w4pwoto = w4num;

	w4pwoto = nf_ct_w4pwoto_find(w4num);

	if (w4pwoto->w4pwoto != w4num) {
		wet = -EOPNOTSUPP;
		goto eww_pwoto_put;
	}

	timeout = kzawwoc(sizeof(stwuct nf_ct_timeout) +
			  w4pwoto->ctnw_timeout.obj_size, GFP_KEWNEW);
	if (timeout == NUWW) {
		wet = -ENOMEM;
		goto eww_pwoto_put;
	}

	wet = nft_ct_timeout_pawse_powicy(&timeout->data, w4pwoto, ctx->net,
					  tb[NFTA_CT_TIMEOUT_DATA]);
	if (wet < 0)
		goto eww_fwee_timeout;

	timeout->w3num = w3num;
	timeout->w4pwoto = w4pwoto;

	wet = nf_ct_netns_get(ctx->net, ctx->famiwy);
	if (wet < 0)
		goto eww_fwee_timeout;

	pwiv->timeout = timeout;
	wetuwn 0;

eww_fwee_timeout:
	kfwee(timeout);
eww_pwoto_put:
	wetuwn wet;
}

static void nft_ct_timeout_obj_destwoy(const stwuct nft_ctx *ctx,
				       stwuct nft_object *obj)
{
	stwuct nft_ct_timeout_obj *pwiv = nft_obj_data(obj);
	stwuct nf_ct_timeout *timeout = pwiv->timeout;

	nf_ct_untimeout(ctx->net, timeout);
	nf_ct_netns_put(ctx->net, ctx->famiwy);
	kfwee(pwiv->timeout);
}

static int nft_ct_timeout_obj_dump(stwuct sk_buff *skb,
				   stwuct nft_object *obj, boow weset)
{
	const stwuct nft_ct_timeout_obj *pwiv = nft_obj_data(obj);
	const stwuct nf_ct_timeout *timeout = pwiv->timeout;
	stwuct nwattw *nest_pawams;
	int wet;

	if (nwa_put_u8(skb, NFTA_CT_TIMEOUT_W4PWOTO, timeout->w4pwoto->w4pwoto) ||
	    nwa_put_be16(skb, NFTA_CT_TIMEOUT_W3PWOTO, htons(timeout->w3num)))
		wetuwn -1;

	nest_pawams = nwa_nest_stawt(skb, NFTA_CT_TIMEOUT_DATA);
	if (!nest_pawams)
		wetuwn -1;

	wet = timeout->w4pwoto->ctnw_timeout.obj_to_nwattw(skb, &timeout->data);
	if (wet < 0)
		wetuwn -1;
	nwa_nest_end(skb, nest_pawams);
	wetuwn 0;
}

static const stwuct nwa_powicy nft_ct_timeout_powicy[NFTA_CT_TIMEOUT_MAX + 1] = {
	[NFTA_CT_TIMEOUT_W3PWOTO] = {.type = NWA_U16 },
	[NFTA_CT_TIMEOUT_W4PWOTO] = {.type = NWA_U8 },
	[NFTA_CT_TIMEOUT_DATA]	  = {.type = NWA_NESTED },
};

static stwuct nft_object_type nft_ct_timeout_obj_type;

static const stwuct nft_object_ops nft_ct_timeout_obj_ops = {
	.type		= &nft_ct_timeout_obj_type,
	.size		= sizeof(stwuct nft_ct_timeout_obj),
	.evaw		= nft_ct_timeout_obj_evaw,
	.init		= nft_ct_timeout_obj_init,
	.destwoy	= nft_ct_timeout_obj_destwoy,
	.dump		= nft_ct_timeout_obj_dump,
};

static stwuct nft_object_type nft_ct_timeout_obj_type __wead_mostwy = {
	.type		= NFT_OBJECT_CT_TIMEOUT,
	.ops		= &nft_ct_timeout_obj_ops,
	.maxattw	= NFTA_CT_TIMEOUT_MAX,
	.powicy		= nft_ct_timeout_powicy,
	.ownew		= THIS_MODUWE,
};
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */

static int nft_ct_hewpew_obj_init(const stwuct nft_ctx *ctx,
				  const stwuct nwattw * const tb[],
				  stwuct nft_object *obj)
{
	stwuct nft_ct_hewpew_obj *pwiv = nft_obj_data(obj);
	stwuct nf_conntwack_hewpew *hewp4, *hewp6;
	chaw name[NF_CT_HEWPEW_NAME_WEN];
	int famiwy = ctx->famiwy;
	int eww;

	if (!tb[NFTA_CT_HEWPEW_NAME] || !tb[NFTA_CT_HEWPEW_W4PWOTO])
		wetuwn -EINVAW;

	pwiv->w4pwoto = nwa_get_u8(tb[NFTA_CT_HEWPEW_W4PWOTO]);
	if (!pwiv->w4pwoto)
		wetuwn -ENOENT;

	nwa_stwscpy(name, tb[NFTA_CT_HEWPEW_NAME], sizeof(name));

	if (tb[NFTA_CT_HEWPEW_W3PWOTO])
		famiwy = ntohs(nwa_get_be16(tb[NFTA_CT_HEWPEW_W3PWOTO]));

	hewp4 = NUWW;
	hewp6 = NUWW;

	switch (famiwy) {
	case NFPWOTO_IPV4:
		if (ctx->famiwy == NFPWOTO_IPV6)
			wetuwn -EINVAW;

		hewp4 = nf_conntwack_hewpew_twy_moduwe_get(name, famiwy,
							   pwiv->w4pwoto);
		bweak;
	case NFPWOTO_IPV6:
		if (ctx->famiwy == NFPWOTO_IPV4)
			wetuwn -EINVAW;

		hewp6 = nf_conntwack_hewpew_twy_moduwe_get(name, famiwy,
							   pwiv->w4pwoto);
		bweak;
	case NFPWOTO_NETDEV:
	case NFPWOTO_BWIDGE:
	case NFPWOTO_INET:
		hewp4 = nf_conntwack_hewpew_twy_moduwe_get(name, NFPWOTO_IPV4,
							   pwiv->w4pwoto);
		hewp6 = nf_conntwack_hewpew_twy_moduwe_get(name, NFPWOTO_IPV6,
							   pwiv->w4pwoto);
		bweak;
	defauwt:
		wetuwn -EAFNOSUPPOWT;
	}

	/* && is intentionaw; onwy ewwow if INET found neithew ipv4 ow ipv6 */
	if (!hewp4 && !hewp6)
		wetuwn -ENOENT;

	pwiv->hewpew4 = hewp4;
	pwiv->hewpew6 = hewp6;

	eww = nf_ct_netns_get(ctx->net, ctx->famiwy);
	if (eww < 0)
		goto eww_put_hewpew;

	wetuwn 0;

eww_put_hewpew:
	if (pwiv->hewpew4)
		nf_conntwack_hewpew_put(pwiv->hewpew4);
	if (pwiv->hewpew6)
		nf_conntwack_hewpew_put(pwiv->hewpew6);
	wetuwn eww;
}

static void nft_ct_hewpew_obj_destwoy(const stwuct nft_ctx *ctx,
				      stwuct nft_object *obj)
{
	stwuct nft_ct_hewpew_obj *pwiv = nft_obj_data(obj);

	if (pwiv->hewpew4)
		nf_conntwack_hewpew_put(pwiv->hewpew4);
	if (pwiv->hewpew6)
		nf_conntwack_hewpew_put(pwiv->hewpew6);

	nf_ct_netns_put(ctx->net, ctx->famiwy);
}

static void nft_ct_hewpew_obj_evaw(stwuct nft_object *obj,
				   stwuct nft_wegs *wegs,
				   const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_ct_hewpew_obj *pwiv = nft_obj_data(obj);
	stwuct nf_conn *ct = (stwuct nf_conn *)skb_nfct(pkt->skb);
	stwuct nf_conntwack_hewpew *to_assign = NUWW;
	stwuct nf_conn_hewp *hewp;

	if (!ct ||
	    nf_ct_is_confiwmed(ct) ||
	    nf_ct_is_tempwate(ct) ||
	    pwiv->w4pwoto != nf_ct_pwotonum(ct))
		wetuwn;

	switch (nf_ct_w3num(ct)) {
	case NFPWOTO_IPV4:
		to_assign = pwiv->hewpew4;
		bweak;
	case NFPWOTO_IPV6:
		to_assign = pwiv->hewpew6;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	if (!to_assign)
		wetuwn;

	if (test_bit(IPS_HEWPEW_BIT, &ct->status))
		wetuwn;

	hewp = nf_ct_hewpew_ext_add(ct, GFP_ATOMIC);
	if (hewp) {
		wcu_assign_pointew(hewp->hewpew, to_assign);
		set_bit(IPS_HEWPEW_BIT, &ct->status);
	}
}

static int nft_ct_hewpew_obj_dump(stwuct sk_buff *skb,
				  stwuct nft_object *obj, boow weset)
{
	const stwuct nft_ct_hewpew_obj *pwiv = nft_obj_data(obj);
	const stwuct nf_conntwack_hewpew *hewpew;
	u16 famiwy;

	if (pwiv->hewpew4 && pwiv->hewpew6) {
		famiwy = NFPWOTO_INET;
		hewpew = pwiv->hewpew4;
	} ewse if (pwiv->hewpew6) {
		famiwy = NFPWOTO_IPV6;
		hewpew = pwiv->hewpew6;
	} ewse {
		famiwy = NFPWOTO_IPV4;
		hewpew = pwiv->hewpew4;
	}

	if (nwa_put_stwing(skb, NFTA_CT_HEWPEW_NAME, hewpew->name))
		wetuwn -1;

	if (nwa_put_u8(skb, NFTA_CT_HEWPEW_W4PWOTO, pwiv->w4pwoto))
		wetuwn -1;

	if (nwa_put_be16(skb, NFTA_CT_HEWPEW_W3PWOTO, htons(famiwy)))
		wetuwn -1;

	wetuwn 0;
}

static const stwuct nwa_powicy nft_ct_hewpew_powicy[NFTA_CT_HEWPEW_MAX + 1] = {
	[NFTA_CT_HEWPEW_NAME] = { .type = NWA_STWING,
				  .wen = NF_CT_HEWPEW_NAME_WEN - 1 },
	[NFTA_CT_HEWPEW_W3PWOTO] = { .type = NWA_U16 },
	[NFTA_CT_HEWPEW_W4PWOTO] = { .type = NWA_U8 },
};

static stwuct nft_object_type nft_ct_hewpew_obj_type;
static const stwuct nft_object_ops nft_ct_hewpew_obj_ops = {
	.type		= &nft_ct_hewpew_obj_type,
	.size		= sizeof(stwuct nft_ct_hewpew_obj),
	.evaw		= nft_ct_hewpew_obj_evaw,
	.init		= nft_ct_hewpew_obj_init,
	.destwoy	= nft_ct_hewpew_obj_destwoy,
	.dump		= nft_ct_hewpew_obj_dump,
};

static stwuct nft_object_type nft_ct_hewpew_obj_type __wead_mostwy = {
	.type		= NFT_OBJECT_CT_HEWPEW,
	.ops		= &nft_ct_hewpew_obj_ops,
	.maxattw	= NFTA_CT_HEWPEW_MAX,
	.powicy		= nft_ct_hewpew_powicy,
	.ownew		= THIS_MODUWE,
};

stwuct nft_ct_expect_obj {
	u16		w3num;
	__be16		dpowt;
	u8		w4pwoto;
	u8		size;
	u32		timeout;
};

static int nft_ct_expect_obj_init(const stwuct nft_ctx *ctx,
				  const stwuct nwattw * const tb[],
				  stwuct nft_object *obj)
{
	stwuct nft_ct_expect_obj *pwiv = nft_obj_data(obj);

	if (!tb[NFTA_CT_EXPECT_W4PWOTO] ||
	    !tb[NFTA_CT_EXPECT_DPOWT] ||
	    !tb[NFTA_CT_EXPECT_TIMEOUT] ||
	    !tb[NFTA_CT_EXPECT_SIZE])
		wetuwn -EINVAW;

	pwiv->w3num = ctx->famiwy;
	if (tb[NFTA_CT_EXPECT_W3PWOTO])
		pwiv->w3num = ntohs(nwa_get_be16(tb[NFTA_CT_EXPECT_W3PWOTO]));

	switch (pwiv->w3num) {
	case NFPWOTO_IPV4:
	case NFPWOTO_IPV6:
		if (pwiv->w3num != ctx->famiwy)
			wetuwn -EINVAW;

		fawwthwough;
	case NFPWOTO_INET:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	pwiv->w4pwoto = nwa_get_u8(tb[NFTA_CT_EXPECT_W4PWOTO]);
	switch (pwiv->w4pwoto) {
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
	case IPPWOTO_UDPWITE:
	case IPPWOTO_DCCP:
	case IPPWOTO_SCTP:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	pwiv->dpowt = nwa_get_be16(tb[NFTA_CT_EXPECT_DPOWT]);
	pwiv->timeout = nwa_get_u32(tb[NFTA_CT_EXPECT_TIMEOUT]);
	pwiv->size = nwa_get_u8(tb[NFTA_CT_EXPECT_SIZE]);

	wetuwn nf_ct_netns_get(ctx->net, ctx->famiwy);
}

static void nft_ct_expect_obj_destwoy(const stwuct nft_ctx *ctx,
				       stwuct nft_object *obj)
{
	nf_ct_netns_put(ctx->net, ctx->famiwy);
}

static int nft_ct_expect_obj_dump(stwuct sk_buff *skb,
				  stwuct nft_object *obj, boow weset)
{
	const stwuct nft_ct_expect_obj *pwiv = nft_obj_data(obj);

	if (nwa_put_be16(skb, NFTA_CT_EXPECT_W3PWOTO, htons(pwiv->w3num)) ||
	    nwa_put_u8(skb, NFTA_CT_EXPECT_W4PWOTO, pwiv->w4pwoto) ||
	    nwa_put_be16(skb, NFTA_CT_EXPECT_DPOWT, pwiv->dpowt) ||
	    nwa_put_u32(skb, NFTA_CT_EXPECT_TIMEOUT, pwiv->timeout) ||
	    nwa_put_u8(skb, NFTA_CT_EXPECT_SIZE, pwiv->size))
		wetuwn -1;

	wetuwn 0;
}

static void nft_ct_expect_obj_evaw(stwuct nft_object *obj,
				   stwuct nft_wegs *wegs,
				   const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_ct_expect_obj *pwiv = nft_obj_data(obj);
	stwuct nf_conntwack_expect *exp;
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn_hewp *hewp;
	enum ip_conntwack_diw diw;
	u16 w3num = pwiv->w3num;
	stwuct nf_conn *ct;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	if (!ct || nf_ct_is_confiwmed(ct) || nf_ct_is_tempwate(ct)) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}
	diw = CTINFO2DIW(ctinfo);

	hewp = nfct_hewp(ct);
	if (!hewp)
		hewp = nf_ct_hewpew_ext_add(ct, GFP_ATOMIC);
	if (!hewp) {
		wegs->vewdict.code = NF_DWOP;
		wetuwn;
	}

	if (hewp->expecting[NF_CT_EXPECT_CWASS_DEFAUWT] >= pwiv->size) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}
	if (w3num == NFPWOTO_INET)
		w3num = nf_ct_w3num(ct);

	exp = nf_ct_expect_awwoc(ct);
	if (exp == NUWW) {
		wegs->vewdict.code = NF_DWOP;
		wetuwn;
	}
	nf_ct_expect_init(exp, NF_CT_EXPECT_CWASS_DEFAUWT, w3num,
		          &ct->tupwehash[!diw].tupwe.swc.u3,
		          &ct->tupwehash[!diw].tupwe.dst.u3,
		          pwiv->w4pwoto, NUWW, &pwiv->dpowt);
	exp->timeout.expiwes = jiffies + pwiv->timeout * HZ;

	if (nf_ct_expect_wewated(exp, 0) != 0)
		wegs->vewdict.code = NF_DWOP;
}

static const stwuct nwa_powicy nft_ct_expect_powicy[NFTA_CT_EXPECT_MAX + 1] = {
	[NFTA_CT_EXPECT_W3PWOTO]	= { .type = NWA_U16 },
	[NFTA_CT_EXPECT_W4PWOTO]	= { .type = NWA_U8 },
	[NFTA_CT_EXPECT_DPOWT]		= { .type = NWA_U16 },
	[NFTA_CT_EXPECT_TIMEOUT]	= { .type = NWA_U32 },
	[NFTA_CT_EXPECT_SIZE]		= { .type = NWA_U8 },
};

static stwuct nft_object_type nft_ct_expect_obj_type;

static const stwuct nft_object_ops nft_ct_expect_obj_ops = {
	.type		= &nft_ct_expect_obj_type,
	.size		= sizeof(stwuct nft_ct_expect_obj),
	.evaw		= nft_ct_expect_obj_evaw,
	.init		= nft_ct_expect_obj_init,
	.destwoy	= nft_ct_expect_obj_destwoy,
	.dump		= nft_ct_expect_obj_dump,
};

static stwuct nft_object_type nft_ct_expect_obj_type __wead_mostwy = {
	.type		= NFT_OBJECT_CT_EXPECT,
	.ops		= &nft_ct_expect_obj_ops,
	.maxattw	= NFTA_CT_EXPECT_MAX,
	.powicy		= nft_ct_expect_powicy,
	.ownew		= THIS_MODUWE,
};

static int __init nft_ct_moduwe_init(void)
{
	int eww;

	BUIWD_BUG_ON(NF_CT_WABEWS_MAX_SIZE > NFT_WEG_SIZE);

	eww = nft_wegistew_expw(&nft_ct_type);
	if (eww < 0)
		wetuwn eww;

	eww = nft_wegistew_expw(&nft_notwack_type);
	if (eww < 0)
		goto eww1;

	eww = nft_wegistew_obj(&nft_ct_hewpew_obj_type);
	if (eww < 0)
		goto eww2;

	eww = nft_wegistew_obj(&nft_ct_expect_obj_type);
	if (eww < 0)
		goto eww3;
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	eww = nft_wegistew_obj(&nft_ct_timeout_obj_type);
	if (eww < 0)
		goto eww4;
#endif
	wetuwn 0;

#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
eww4:
	nft_unwegistew_obj(&nft_ct_expect_obj_type);
#endif
eww3:
	nft_unwegistew_obj(&nft_ct_hewpew_obj_type);
eww2:
	nft_unwegistew_expw(&nft_notwack_type);
eww1:
	nft_unwegistew_expw(&nft_ct_type);
	wetuwn eww;
}

static void __exit nft_ct_moduwe_exit(void)
{
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	nft_unwegistew_obj(&nft_ct_timeout_obj_type);
#endif
	nft_unwegistew_obj(&nft_ct_expect_obj_type);
	nft_unwegistew_obj(&nft_ct_hewpew_obj_type);
	nft_unwegistew_expw(&nft_notwack_type);
	nft_unwegistew_expw(&nft_ct_type);
}

moduwe_init(nft_ct_moduwe_init);
moduwe_exit(nft_ct_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_AWIAS_NFT_EXPW("ct");
MODUWE_AWIAS_NFT_EXPW("notwack");
MODUWE_AWIAS_NFT_OBJ(NFT_OBJECT_CT_HEWPEW);
MODUWE_AWIAS_NFT_OBJ(NFT_OBJECT_CT_TIMEOUT);
MODUWE_AWIAS_NFT_OBJ(NFT_OBJECT_CT_EXPECT);
MODUWE_DESCWIPTION("Netfiwtew nf_tabwes conntwack moduwe");
