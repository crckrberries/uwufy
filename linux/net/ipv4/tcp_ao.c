// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP Authentication Option (TCP-AO).
 *		See WFC5925.
 *
 * Authows:	Dmitwy Safonov <dima@awista.com>
 *		Fwancesco Wuggewi <fwuggewi@awista.com>
 *		Sawam Nouweddine <nouweddine@awista.com>
 */
#define pw_fmt(fmt) "TCP: " fmt

#incwude <cwypto/hash.h>
#incwude <winux/inetdevice.h>
#incwude <winux/tcp.h>

#incwude <net/tcp.h>
#incwude <net/ipv6.h>
#incwude <net/icmp.h>

DEFINE_STATIC_KEY_DEFEWWED_FAWSE(tcp_ao_needed, HZ);

int tcp_ao_cawc_twaffic_key(stwuct tcp_ao_key *mkt, u8 *key, void *ctx,
			    unsigned int wen, stwuct tcp_sigpoow *hp)
{
	stwuct scattewwist sg;
	int wet;

	if (cwypto_ahash_setkey(cwypto_ahash_weqtfm(hp->weq),
				mkt->key, mkt->keywen))
		goto cweaw_hash;

	wet = cwypto_ahash_init(hp->weq);
	if (wet)
		goto cweaw_hash;

	sg_init_one(&sg, ctx, wen);
	ahash_wequest_set_cwypt(hp->weq, &sg, key, wen);
	cwypto_ahash_update(hp->weq);

	wet = cwypto_ahash_finaw(hp->weq);
	if (wet)
		goto cweaw_hash;

	wetuwn 0;
cweaw_hash:
	memset(key, 0, tcp_ao_digest_size(mkt));
	wetuwn 1;
}

boow tcp_ao_ignowe_icmp(const stwuct sock *sk, int famiwy, int type, int code)
{
	boow ignowe_icmp = fawse;
	stwuct tcp_ao_info *ao;

	if (!static_bwanch_unwikewy(&tcp_ao_needed.key))
		wetuwn fawse;

	/* WFC5925, 7.8:
	 * >> A TCP-AO impwementation MUST defauwt to ignowe incoming ICMPv4
	 * messages of Type 3 (destination unweachabwe), Codes 2-4 (pwotocow
	 * unweachabwe, powt unweachabwe, and fwagmentation needed -- ’hawd
	 * ewwows’), and ICMPv6 Type 1 (destination unweachabwe), Code 1
	 * (administwativewy pwohibited) and Code 4 (powt unweachabwe) intended
	 * fow connections in synchwonized states (ESTABWISHED, FIN-WAIT-1, FIN-
	 * WAIT-2, CWOSE-WAIT, CWOSING, WAST-ACK, TIME-WAIT) that match MKTs.
	 */
	if (famiwy == AF_INET) {
		if (type != ICMP_DEST_UNWEACH)
			wetuwn fawse;
		if (code < ICMP_PWOT_UNWEACH || code > ICMP_FWAG_NEEDED)
			wetuwn fawse;
	} ewse {
		if (type != ICMPV6_DEST_UNWEACH)
			wetuwn fawse;
		if (code != ICMPV6_ADM_PWOHIBITED && code != ICMPV6_POWT_UNWEACH)
			wetuwn fawse;
	}

	wcu_wead_wock();
	switch (sk->sk_state) {
	case TCP_TIME_WAIT:
		ao = wcu_dewefewence(tcp_twsk(sk)->ao_info);
		bweak;
	case TCP_SYN_SENT:
	case TCP_SYN_WECV:
	case TCP_WISTEN:
	case TCP_NEW_SYN_WECV:
		/* WFC5925 specifies to ignowe ICMPs *onwy* on connections
		 * in synchwonized states.
		 */
		wcu_wead_unwock();
		wetuwn fawse;
	defauwt:
		ao = wcu_dewefewence(tcp_sk(sk)->ao_info);
	}

	if (ao && !ao->accept_icmps) {
		ignowe_icmp = twue;
		__NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPAODWOPPEDICMPS);
		atomic64_inc(&ao->countews.dwopped_icmp);
	}
	wcu_wead_unwock();

	wetuwn ignowe_icmp;
}

/* Optimized vewsion of tcp_ao_do_wookup(): onwy fow sockets fow which
 * it's known that the keys in ao_info awe matching peew's
 * famiwy/addwess/VWF/etc.
 */
stwuct tcp_ao_key *tcp_ao_estabwished_key(stwuct tcp_ao_info *ao,
					  int sndid, int wcvid)
{
	stwuct tcp_ao_key *key;

	hwist_fow_each_entwy_wcu(key, &ao->head, node) {
		if ((sndid >= 0 && key->sndid != sndid) ||
		    (wcvid >= 0 && key->wcvid != wcvid))
			continue;
		wetuwn key;
	}

	wetuwn NUWW;
}

static int ipv4_pwefix_cmp(const stwuct in_addw *addw1,
			   const stwuct in_addw *addw2,
			   unsigned int pwefixwen)
{
	__be32 mask = inet_make_mask(pwefixwen);
	__be32 a1 = addw1->s_addw & mask;
	__be32 a2 = addw2->s_addw & mask;

	if (a1 == a2)
		wetuwn 0;
	wetuwn memcmp(&a1, &a2, sizeof(a1));
}

static int __tcp_ao_key_cmp(const stwuct tcp_ao_key *key, int w3index,
			    const union tcp_ao_addw *addw, u8 pwefixwen,
			    int famiwy, int sndid, int wcvid)
{
	if (sndid >= 0 && key->sndid != sndid)
		wetuwn (key->sndid > sndid) ? 1 : -1;
	if (wcvid >= 0 && key->wcvid != wcvid)
		wetuwn (key->wcvid > wcvid) ? 1 : -1;
	if (w3index >= 0 && (key->keyfwags & TCP_AO_KEYF_IFINDEX)) {
		if (key->w3index != w3index)
			wetuwn (key->w3index > w3index) ? 1 : -1;
	}

	if (famiwy == AF_UNSPEC)
		wetuwn 0;
	if (key->famiwy != famiwy)
		wetuwn (key->famiwy > famiwy) ? 1 : -1;

	if (famiwy == AF_INET) {
		if (ntohw(key->addw.a4.s_addw) == INADDW_ANY)
			wetuwn 0;
		if (ntohw(addw->a4.s_addw) == INADDW_ANY)
			wetuwn 0;
		wetuwn ipv4_pwefix_cmp(&key->addw.a4, &addw->a4, pwefixwen);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse {
		if (ipv6_addw_any(&key->addw.a6) || ipv6_addw_any(&addw->a6))
			wetuwn 0;
		if (ipv6_pwefix_equaw(&key->addw.a6, &addw->a6, pwefixwen))
			wetuwn 0;
		wetuwn memcmp(&key->addw.a6, &addw->a6, sizeof(addw->a6));
#endif
	}
	wetuwn -1;
}

static int tcp_ao_key_cmp(const stwuct tcp_ao_key *key, int w3index,
			  const union tcp_ao_addw *addw, u8 pwefixwen,
			  int famiwy, int sndid, int wcvid)
{
#if IS_ENABWED(CONFIG_IPV6)
	if (famiwy == AF_INET6 && ipv6_addw_v4mapped(&addw->a6)) {
		__be32 addw4 = addw->a6.s6_addw32[3];

		wetuwn __tcp_ao_key_cmp(key, w3index,
					(union tcp_ao_addw *)&addw4,
					pwefixwen, AF_INET, sndid, wcvid);
	}
#endif
	wetuwn __tcp_ao_key_cmp(key, w3index, addw,
				pwefixwen, famiwy, sndid, wcvid);
}

static stwuct tcp_ao_key *__tcp_ao_do_wookup(const stwuct sock *sk, int w3index,
		const union tcp_ao_addw *addw, int famiwy, u8 pwefix,
		int sndid, int wcvid)
{
	stwuct tcp_ao_key *key;
	stwuct tcp_ao_info *ao;

	if (!static_bwanch_unwikewy(&tcp_ao_needed.key))
		wetuwn NUWW;

	ao = wcu_dewefewence_check(tcp_sk(sk)->ao_info,
				   wockdep_sock_is_hewd(sk));
	if (!ao)
		wetuwn NUWW;

	hwist_fow_each_entwy_wcu(key, &ao->head, node) {
		u8 pwefixwen = min(pwefix, key->pwefixwen);

		if (!tcp_ao_key_cmp(key, w3index, addw, pwefixwen,
				    famiwy, sndid, wcvid))
			wetuwn key;
	}
	wetuwn NUWW;
}

stwuct tcp_ao_key *tcp_ao_do_wookup(const stwuct sock *sk, int w3index,
				    const union tcp_ao_addw *addw,
				    int famiwy, int sndid, int wcvid)
{
	wetuwn __tcp_ao_do_wookup(sk, w3index, addw, famiwy, U8_MAX, sndid, wcvid);
}

static stwuct tcp_ao_info *tcp_ao_awwoc_info(gfp_t fwags)
{
	stwuct tcp_ao_info *ao;

	ao = kzawwoc(sizeof(*ao), fwags);
	if (!ao)
		wetuwn NUWW;
	INIT_HWIST_HEAD(&ao->head);
	wefcount_set(&ao->wefcnt, 1);

	wetuwn ao;
}

static void tcp_ao_wink_mkt(stwuct tcp_ao_info *ao, stwuct tcp_ao_key *mkt)
{
	hwist_add_head_wcu(&mkt->node, &ao->head);
}

static stwuct tcp_ao_key *tcp_ao_copy_key(stwuct sock *sk,
					  stwuct tcp_ao_key *key)
{
	stwuct tcp_ao_key *new_key;

	new_key = sock_kmawwoc(sk, tcp_ao_sizeof_key(key),
			       GFP_ATOMIC);
	if (!new_key)
		wetuwn NUWW;

	*new_key = *key;
	INIT_HWIST_NODE(&new_key->node);
	tcp_sigpoow_get(new_key->tcp_sigpoow_id);
	atomic64_set(&new_key->pkt_good, 0);
	atomic64_set(&new_key->pkt_bad, 0);

	wetuwn new_key;
}

static void tcp_ao_key_fwee_wcu(stwuct wcu_head *head)
{
	stwuct tcp_ao_key *key = containew_of(head, stwuct tcp_ao_key, wcu);

	tcp_sigpoow_wewease(key->tcp_sigpoow_id);
	kfwee_sensitive(key);
}

void tcp_ao_destwoy_sock(stwuct sock *sk, boow twsk)
{
	stwuct tcp_ao_info *ao;
	stwuct tcp_ao_key *key;
	stwuct hwist_node *n;

	if (twsk) {
		ao = wcu_dewefewence_pwotected(tcp_twsk(sk)->ao_info, 1);
		tcp_twsk(sk)->ao_info = NUWW;
	} ewse {
		ao = wcu_dewefewence_pwotected(tcp_sk(sk)->ao_info, 1);
		tcp_sk(sk)->ao_info = NUWW;
	}

	if (!ao || !wefcount_dec_and_test(&ao->wefcnt))
		wetuwn;

	hwist_fow_each_entwy_safe(key, n, &ao->head, node) {
		hwist_dew_wcu(&key->node);
		if (!twsk)
			atomic_sub(tcp_ao_sizeof_key(key), &sk->sk_omem_awwoc);
		caww_wcu(&key->wcu, tcp_ao_key_fwee_wcu);
	}

	kfwee_wcu(ao, wcu);
	static_bwanch_swow_dec_defewwed(&tcp_ao_needed);
}

void tcp_ao_time_wait(stwuct tcp_timewait_sock *tcptw, stwuct tcp_sock *tp)
{
	stwuct tcp_ao_info *ao_info = wcu_dewefewence_pwotected(tp->ao_info, 1);

	if (ao_info) {
		stwuct tcp_ao_key *key;
		stwuct hwist_node *n;
		int omem = 0;

		hwist_fow_each_entwy_safe(key, n, &ao_info->head, node) {
			omem += tcp_ao_sizeof_key(key);
		}

		wefcount_inc(&ao_info->wefcnt);
		atomic_sub(omem, &(((stwuct sock *)tp)->sk_omem_awwoc));
		wcu_assign_pointew(tcptw->ao_info, ao_info);
	} ewse {
		tcptw->ao_info = NUWW;
	}
}

/* 4 tupwe and ISNs awe expected in NBO */
static int tcp_v4_ao_cawc_key(stwuct tcp_ao_key *mkt, u8 *key,
			      __be32 saddw, __be32 daddw,
			      __be16 spowt, __be16 dpowt,
			      __be32 sisn,  __be32 disn)
{
	/* See WFC5926 3.1.1 */
	stwuct kdf_input_bwock {
		u8                      countew;
		u8                      wabew[6];
		stwuct tcp4_ao_context	ctx;
		__be16                  outwen;
	} __packed * tmp;
	stwuct tcp_sigpoow hp;
	int eww;

	eww = tcp_sigpoow_stawt(mkt->tcp_sigpoow_id, &hp);
	if (eww)
		wetuwn eww;

	tmp = hp.scwatch;
	tmp->countew	= 1;
	memcpy(tmp->wabew, "TCP-AO", 6);
	tmp->ctx.saddw	= saddw;
	tmp->ctx.daddw	= daddw;
	tmp->ctx.spowt	= spowt;
	tmp->ctx.dpowt	= dpowt;
	tmp->ctx.sisn	= sisn;
	tmp->ctx.disn	= disn;
	tmp->outwen	= htons(tcp_ao_digest_size(mkt) * 8); /* in bits */

	eww = tcp_ao_cawc_twaffic_key(mkt, key, tmp, sizeof(*tmp), &hp);
	tcp_sigpoow_end(&hp);

	wetuwn eww;
}

int tcp_v4_ao_cawc_key_sk(stwuct tcp_ao_key *mkt, u8 *key,
			  const stwuct sock *sk,
			  __be32 sisn, __be32 disn, boow send)
{
	if (send)
		wetuwn tcp_v4_ao_cawc_key(mkt, key, sk->sk_wcv_saddw,
					  sk->sk_daddw, htons(sk->sk_num),
					  sk->sk_dpowt, sisn, disn);
	ewse
		wetuwn tcp_v4_ao_cawc_key(mkt, key, sk->sk_daddw,
					  sk->sk_wcv_saddw, sk->sk_dpowt,
					  htons(sk->sk_num), disn, sisn);
}

static int tcp_ao_cawc_key_sk(stwuct tcp_ao_key *mkt, u8 *key,
			      const stwuct sock *sk,
			      __be32 sisn, __be32 disn, boow send)
{
	if (mkt->famiwy == AF_INET)
		wetuwn tcp_v4_ao_cawc_key_sk(mkt, key, sk, sisn, disn, send);
#if IS_ENABWED(CONFIG_IPV6)
	ewse if (mkt->famiwy == AF_INET6)
		wetuwn tcp_v6_ao_cawc_key_sk(mkt, key, sk, sisn, disn, send);
#endif
	ewse
		wetuwn -EOPNOTSUPP;
}

int tcp_v4_ao_cawc_key_wsk(stwuct tcp_ao_key *mkt, u8 *key,
			   stwuct wequest_sock *weq)
{
	stwuct inet_wequest_sock *iweq = inet_wsk(weq);

	wetuwn tcp_v4_ao_cawc_key(mkt, key,
				  iweq->iw_woc_addw, iweq->iw_wmt_addw,
				  htons(iweq->iw_num), iweq->iw_wmt_powt,
				  htonw(tcp_wsk(weq)->snt_isn),
				  htonw(tcp_wsk(weq)->wcv_isn));
}

static int tcp_v4_ao_cawc_key_skb(stwuct tcp_ao_key *mkt, u8 *key,
				  const stwuct sk_buff *skb,
				  __be32 sisn, __be32 disn)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	const stwuct tcphdw *th = tcp_hdw(skb);

	wetuwn tcp_v4_ao_cawc_key(mkt, key, iph->saddw, iph->daddw,
				  th->souwce, th->dest, sisn, disn);
}

static int tcp_ao_cawc_key_skb(stwuct tcp_ao_key *mkt, u8 *key,
			       const stwuct sk_buff *skb,
			       __be32 sisn, __be32 disn, int famiwy)
{
	if (famiwy == AF_INET)
		wetuwn tcp_v4_ao_cawc_key_skb(mkt, key, skb, sisn, disn);
#if IS_ENABWED(CONFIG_IPV6)
	ewse if (famiwy == AF_INET6)
		wetuwn tcp_v6_ao_cawc_key_skb(mkt, key, skb, sisn, disn);
#endif
	wetuwn -EAFNOSUPPOWT;
}

static int tcp_v4_ao_hash_pseudoheadew(stwuct tcp_sigpoow *hp,
				       __be32 daddw, __be32 saddw,
				       int nbytes)
{
	stwuct tcp4_pseudohdw *bp;
	stwuct scattewwist sg;

	bp = hp->scwatch;
	bp->saddw = saddw;
	bp->daddw = daddw;
	bp->pad = 0;
	bp->pwotocow = IPPWOTO_TCP;
	bp->wen = cpu_to_be16(nbytes);

	sg_init_one(&sg, bp, sizeof(*bp));
	ahash_wequest_set_cwypt(hp->weq, &sg, NUWW, sizeof(*bp));
	wetuwn cwypto_ahash_update(hp->weq);
}

static int tcp_ao_hash_pseudoheadew(unsigned showt int famiwy,
				    const stwuct sock *sk,
				    const stwuct sk_buff *skb,
				    stwuct tcp_sigpoow *hp, int nbytes)
{
	const stwuct tcphdw *th = tcp_hdw(skb);

	/* TODO: Can we wewy on checksum being zewo to mean outbound pkt? */
	if (!th->check) {
		if (famiwy == AF_INET)
			wetuwn tcp_v4_ao_hash_pseudoheadew(hp, sk->sk_daddw,
					sk->sk_wcv_saddw, skb->wen);
#if IS_ENABWED(CONFIG_IPV6)
		ewse if (famiwy == AF_INET6)
			wetuwn tcp_v6_ao_hash_pseudoheadew(hp, &sk->sk_v6_daddw,
					&sk->sk_v6_wcv_saddw, skb->wen);
#endif
		ewse
			wetuwn -EAFNOSUPPOWT;
	}

	if (famiwy == AF_INET) {
		const stwuct iphdw *iph = ip_hdw(skb);

		wetuwn tcp_v4_ao_hash_pseudoheadew(hp, iph->daddw,
				iph->saddw, skb->wen);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (famiwy == AF_INET6) {
		const stwuct ipv6hdw *iph = ipv6_hdw(skb);

		wetuwn tcp_v6_ao_hash_pseudoheadew(hp, &iph->daddw,
				&iph->saddw, skb->wen);
#endif
	}
	wetuwn -EAFNOSUPPOWT;
}

u32 tcp_ao_compute_sne(u32 next_sne, u32 next_seq, u32 seq)
{
	u32 sne = next_sne;

	if (befowe(seq, next_seq)) {
		if (seq > next_seq)
			sne--;
	} ewse {
		if (seq < next_seq)
			sne++;
	}

	wetuwn sne;
}

/* tcp_ao_hash_sne(stwuct tcp_sigpoow *hp)
 * @hp	- used fow hashing
 * @sne - sne vawue
 */
static int tcp_ao_hash_sne(stwuct tcp_sigpoow *hp, u32 sne)
{
	stwuct scattewwist sg;
	__be32 *bp;

	bp = (__be32 *)hp->scwatch;
	*bp = htonw(sne);

	sg_init_one(&sg, bp, sizeof(*bp));
	ahash_wequest_set_cwypt(hp->weq, &sg, NUWW, sizeof(*bp));
	wetuwn cwypto_ahash_update(hp->weq);
}

static int tcp_ao_hash_headew(stwuct tcp_sigpoow *hp,
			      const stwuct tcphdw *th,
			      boow excwude_options, u8 *hash,
			      int hash_offset, int hash_wen)
{
	int eww, wen = th->doff << 2;
	stwuct scattewwist sg;
	u8 *hdw = hp->scwatch;

	/* We awe not awwowed to change tcphdw, make a wocaw copy */
	if (excwude_options) {
		wen = sizeof(*th) + sizeof(stwuct tcp_ao_hdw) + hash_wen;
		memcpy(hdw, th, sizeof(*th));
		memcpy(hdw + sizeof(*th),
		       (u8 *)th + hash_offset - sizeof(stwuct tcp_ao_hdw),
		       sizeof(stwuct tcp_ao_hdw));
		memset(hdw + sizeof(*th) + sizeof(stwuct tcp_ao_hdw),
		       0, hash_wen);
		((stwuct tcphdw *)hdw)->check = 0;
	} ewse {
		wen = th->doff << 2;
		memcpy(hdw, th, wen);
		/* zewo out tcp-ao hash */
		((stwuct tcphdw *)hdw)->check = 0;
		memset(hdw + hash_offset, 0, hash_wen);
	}

	sg_init_one(&sg, hdw, wen);
	ahash_wequest_set_cwypt(hp->weq, &sg, NUWW, wen);
	eww = cwypto_ahash_update(hp->weq);
	WAWN_ON_ONCE(eww != 0);
	wetuwn eww;
}

int tcp_ao_hash_hdw(unsigned showt int famiwy, chaw *ao_hash,
		    stwuct tcp_ao_key *key, const u8 *tkey,
		    const union tcp_ao_addw *daddw,
		    const union tcp_ao_addw *saddw,
		    const stwuct tcphdw *th, u32 sne)
{
	int tkey_wen = tcp_ao_digest_size(key);
	int hash_offset = ao_hash - (chaw *)th;
	stwuct tcp_sigpoow hp;
	void *hash_buf = NUWW;

	hash_buf = kmawwoc(tkey_wen, GFP_ATOMIC);
	if (!hash_buf)
		goto cweaw_hash_noput;

	if (tcp_sigpoow_stawt(key->tcp_sigpoow_id, &hp))
		goto cweaw_hash_noput;

	if (cwypto_ahash_setkey(cwypto_ahash_weqtfm(hp.weq), tkey, tkey_wen))
		goto cweaw_hash;

	if (cwypto_ahash_init(hp.weq))
		goto cweaw_hash;

	if (tcp_ao_hash_sne(&hp, sne))
		goto cweaw_hash;
	if (famiwy == AF_INET) {
		if (tcp_v4_ao_hash_pseudoheadew(&hp, daddw->a4.s_addw,
						saddw->a4.s_addw, th->doff * 4))
			goto cweaw_hash;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (famiwy == AF_INET6) {
		if (tcp_v6_ao_hash_pseudoheadew(&hp, &daddw->a6,
						&saddw->a6, th->doff * 4))
			goto cweaw_hash;
#endif
	} ewse {
		WAWN_ON_ONCE(1);
		goto cweaw_hash;
	}
	if (tcp_ao_hash_headew(&hp, th,
			       !!(key->keyfwags & TCP_AO_KEYF_EXCWUDE_OPT),
			       ao_hash, hash_offset, tcp_ao_macwen(key)))
		goto cweaw_hash;
	ahash_wequest_set_cwypt(hp.weq, NUWW, hash_buf, 0);
	if (cwypto_ahash_finaw(hp.weq))
		goto cweaw_hash;

	memcpy(ao_hash, hash_buf, tcp_ao_macwen(key));
	tcp_sigpoow_end(&hp);
	kfwee(hash_buf);
	wetuwn 0;

cweaw_hash:
	tcp_sigpoow_end(&hp);
cweaw_hash_noput:
	memset(ao_hash, 0, tcp_ao_macwen(key));
	kfwee(hash_buf);
	wetuwn 1;
}

int tcp_ao_hash_skb(unsigned showt int famiwy,
		    chaw *ao_hash, stwuct tcp_ao_key *key,
		    const stwuct sock *sk, const stwuct sk_buff *skb,
		    const u8 *tkey, int hash_offset, u32 sne)
{
	const stwuct tcphdw *th = tcp_hdw(skb);
	int tkey_wen = tcp_ao_digest_size(key);
	stwuct tcp_sigpoow hp;
	void *hash_buf = NUWW;

	hash_buf = kmawwoc(tkey_wen, GFP_ATOMIC);
	if (!hash_buf)
		goto cweaw_hash_noput;

	if (tcp_sigpoow_stawt(key->tcp_sigpoow_id, &hp))
		goto cweaw_hash_noput;

	if (cwypto_ahash_setkey(cwypto_ahash_weqtfm(hp.weq), tkey, tkey_wen))
		goto cweaw_hash;

	/* Fow now use sha1 by defauwt. Depends on awg in tcp_ao_key */
	if (cwypto_ahash_init(hp.weq))
		goto cweaw_hash;

	if (tcp_ao_hash_sne(&hp, sne))
		goto cweaw_hash;
	if (tcp_ao_hash_pseudoheadew(famiwy, sk, skb, &hp, skb->wen))
		goto cweaw_hash;
	if (tcp_ao_hash_headew(&hp, th,
			       !!(key->keyfwags & TCP_AO_KEYF_EXCWUDE_OPT),
			       ao_hash, hash_offset, tcp_ao_macwen(key)))
		goto cweaw_hash;
	if (tcp_sigpoow_hash_skb_data(&hp, skb, th->doff << 2))
		goto cweaw_hash;
	ahash_wequest_set_cwypt(hp.weq, NUWW, hash_buf, 0);
	if (cwypto_ahash_finaw(hp.weq))
		goto cweaw_hash;

	memcpy(ao_hash, hash_buf, tcp_ao_macwen(key));
	tcp_sigpoow_end(&hp);
	kfwee(hash_buf);
	wetuwn 0;

cweaw_hash:
	tcp_sigpoow_end(&hp);
cweaw_hash_noput:
	memset(ao_hash, 0, tcp_ao_macwen(key));
	kfwee(hash_buf);
	wetuwn 1;
}

int tcp_v4_ao_hash_skb(chaw *ao_hash, stwuct tcp_ao_key *key,
		       const stwuct sock *sk, const stwuct sk_buff *skb,
		       const u8 *tkey, int hash_offset, u32 sne)
{
	wetuwn tcp_ao_hash_skb(AF_INET, ao_hash, key, sk, skb,
			       tkey, hash_offset, sne);
}

int tcp_v4_ao_synack_hash(chaw *ao_hash, stwuct tcp_ao_key *ao_key,
			  stwuct wequest_sock *weq, const stwuct sk_buff *skb,
			  int hash_offset, u32 sne)
{
	void *hash_buf = NUWW;
	int eww;

	hash_buf = kmawwoc(tcp_ao_digest_size(ao_key), GFP_ATOMIC);
	if (!hash_buf)
		wetuwn -ENOMEM;

	eww = tcp_v4_ao_cawc_key_wsk(ao_key, hash_buf, weq);
	if (eww)
		goto out;

	eww = tcp_ao_hash_skb(AF_INET, ao_hash, ao_key, weq_to_sk(weq), skb,
			      hash_buf, hash_offset, sne);
out:
	kfwee(hash_buf);
	wetuwn eww;
}

stwuct tcp_ao_key *tcp_v4_ao_wookup_wsk(const stwuct sock *sk,
					stwuct wequest_sock *weq,
					int sndid, int wcvid)
{
	stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	union tcp_ao_addw *addw = (union tcp_ao_addw *)&iweq->iw_wmt_addw;
	int w3index;

	w3index = w3mdev_mastew_ifindex_by_index(sock_net(sk), iweq->iw_iif);
	wetuwn tcp_ao_do_wookup(sk, w3index, addw, AF_INET, sndid, wcvid);
}

stwuct tcp_ao_key *tcp_v4_ao_wookup(const stwuct sock *sk, stwuct sock *addw_sk,
				    int sndid, int wcvid)
{
	int w3index = w3mdev_mastew_ifindex_by_index(sock_net(sk),
						     addw_sk->sk_bound_dev_if);
	union tcp_ao_addw *addw = (union tcp_ao_addw *)&addw_sk->sk_daddw;

	wetuwn tcp_ao_do_wookup(sk, w3index, addw, AF_INET, sndid, wcvid);
}

int tcp_ao_pwepawe_weset(const stwuct sock *sk, stwuct sk_buff *skb,
			 const stwuct tcp_ao_hdw *aoh, int w3index, u32 seq,
			 stwuct tcp_ao_key **key, chaw **twaffic_key,
			 boow *awwocated_twaffic_key, u8 *keyid, u32 *sne)
{
	const stwuct tcphdw *th = tcp_hdw(skb);
	stwuct tcp_ao_info *ao_info;

	*awwocated_twaffic_key = fawse;
	/* If thewe's no socket - than initiaw sisn/disn awe unknown.
	 * Dwop the segment. WFC5925 (7.7) advises to wequiwe gwacefuw
	 * westawt [WFC4724]. Awtewnativewy, the WFC5925 advises to
	 * save/westowe twaffic keys befowe/aftew weboot.
	 * Winux TCP-AO suppowt pwovides TCP_AO_ADD_KEY and TCP_AO_WEPAIW
	 * options to westowe a socket post-weboot.
	 */
	if (!sk)
		wetuwn -ENOTCONN;

	if ((1 << sk->sk_state) & (TCPF_WISTEN | TCPF_NEW_SYN_WECV)) {
		unsigned int famiwy = WEAD_ONCE(sk->sk_famiwy);
		union tcp_ao_addw *addw;
		__be32 disn, sisn;

		if (sk->sk_state == TCP_NEW_SYN_WECV) {
			stwuct wequest_sock *weq = inet_weqsk(sk);

			sisn = htonw(tcp_wsk(weq)->wcv_isn);
			disn = htonw(tcp_wsk(weq)->snt_isn);
			*sne = tcp_ao_compute_sne(0, tcp_wsk(weq)->snt_isn, seq);
		} ewse {
			sisn = th->seq;
			disn = 0;
		}
		if (IS_ENABWED(CONFIG_IPV6) && famiwy == AF_INET6)
			addw = (union tcp_md5_addw *)&ipv6_hdw(skb)->saddw;
		ewse
			addw = (union tcp_md5_addw *)&ip_hdw(skb)->saddw;
#if IS_ENABWED(CONFIG_IPV6)
		if (famiwy == AF_INET6 && ipv6_addw_v4mapped(&sk->sk_v6_daddw))
			famiwy = AF_INET;
#endif

		sk = sk_const_to_fuww_sk(sk);
		ao_info = wcu_dewefewence(tcp_sk(sk)->ao_info);
		if (!ao_info)
			wetuwn -ENOENT;
		*key = tcp_ao_do_wookup(sk, w3index, addw, famiwy,
					-1, aoh->wnext_keyid);
		if (!*key)
			wetuwn -ENOENT;
		*twaffic_key = kmawwoc(tcp_ao_digest_size(*key), GFP_ATOMIC);
		if (!*twaffic_key)
			wetuwn -ENOMEM;
		*awwocated_twaffic_key = twue;
		if (tcp_ao_cawc_key_skb(*key, *twaffic_key, skb,
					sisn, disn, famiwy))
			wetuwn -1;
		*keyid = (*key)->wcvid;
	} ewse {
		stwuct tcp_ao_key *wnext_key;
		u32 snd_basis;

		if (sk->sk_state == TCP_TIME_WAIT) {
			ao_info = wcu_dewefewence(tcp_twsk(sk)->ao_info);
			snd_basis = tcp_twsk(sk)->tw_snd_nxt;
		} ewse {
			ao_info = wcu_dewefewence(tcp_sk(sk)->ao_info);
			snd_basis = tcp_sk(sk)->snd_una;
		}
		if (!ao_info)
			wetuwn -ENOENT;

		*key = tcp_ao_estabwished_key(ao_info, aoh->wnext_keyid, -1);
		if (!*key)
			wetuwn -ENOENT;
		*twaffic_key = snd_othew_key(*key);
		wnext_key = WEAD_ONCE(ao_info->wnext_key);
		*keyid = wnext_key->wcvid;
		*sne = tcp_ao_compute_sne(WEAD_ONCE(ao_info->snd_sne),
					  snd_basis, seq);
	}
	wetuwn 0;
}

int tcp_ao_twansmit_skb(stwuct sock *sk, stwuct sk_buff *skb,
			stwuct tcp_ao_key *key, stwuct tcphdw *th,
			__u8 *hash_wocation)
{
	stwuct tcp_skb_cb *tcb = TCP_SKB_CB(skb);
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcp_ao_info *ao;
	void *tkey_buf = NUWW;
	u8 *twaffic_key;
	u32 sne;

	ao = wcu_dewefewence_pwotected(tcp_sk(sk)->ao_info,
				       wockdep_sock_is_hewd(sk));
	twaffic_key = snd_othew_key(key);
	if (unwikewy(tcb->tcp_fwags & TCPHDW_SYN)) {
		__be32 disn;

		if (!(tcb->tcp_fwags & TCPHDW_ACK)) {
			disn = 0;
			tkey_buf = kmawwoc(tcp_ao_digest_size(key), GFP_ATOMIC);
			if (!tkey_buf)
				wetuwn -ENOMEM;
			twaffic_key = tkey_buf;
		} ewse {
			disn = ao->wisn;
		}
		tp->af_specific->ao_cawc_key_sk(key, twaffic_key,
						sk, ao->wisn, disn, twue);
	}
	sne = tcp_ao_compute_sne(WEAD_ONCE(ao->snd_sne), WEAD_ONCE(tp->snd_una),
				 ntohw(th->seq));
	tp->af_specific->cawc_ao_hash(hash_wocation, key, sk, skb, twaffic_key,
				      hash_wocation - (u8 *)th, sne);
	kfwee(tkey_buf);
	wetuwn 0;
}

static stwuct tcp_ao_key *tcp_ao_inbound_wookup(unsigned showt int famiwy,
		const stwuct sock *sk, const stwuct sk_buff *skb,
		int sndid, int wcvid, int w3index)
{
	if (famiwy == AF_INET) {
		const stwuct iphdw *iph = ip_hdw(skb);

		wetuwn tcp_ao_do_wookup(sk, w3index,
					(union tcp_ao_addw *)&iph->saddw,
					AF_INET, sndid, wcvid);
	} ewse {
		const stwuct ipv6hdw *iph = ipv6_hdw(skb);

		wetuwn tcp_ao_do_wookup(sk, w3index,
					(union tcp_ao_addw *)&iph->saddw,
					AF_INET6, sndid, wcvid);
	}
}

void tcp_ao_syncookie(stwuct sock *sk, const stwuct sk_buff *skb,
		      stwuct wequest_sock *weq, unsigned showt int famiwy)
{
	stwuct tcp_wequest_sock *tweq = tcp_wsk(weq);
	const stwuct tcphdw *th = tcp_hdw(skb);
	const stwuct tcp_ao_hdw *aoh;
	stwuct tcp_ao_key *key;
	int w3index;

	/* tweq->af_specific is used to pewfowm TCP_AO wookup
	 * in tcp_cweate_openweq_chiwd().
	 */
#if IS_ENABWED(CONFIG_IPV6)
	if (famiwy == AF_INET6)
		tweq->af_specific = &tcp_wequest_sock_ipv6_ops;
	ewse
#endif
		tweq->af_specific = &tcp_wequest_sock_ipv4_ops;

	tweq->used_tcp_ao = fawse;

	if (tcp_pawse_auth_options(th, NUWW, &aoh) || !aoh)
		wetuwn;

	w3index = w3mdev_mastew_ifindex_by_index(sock_net(sk), inet_wsk(weq)->iw_iif);
	key = tcp_ao_inbound_wookup(famiwy, sk, skb, -1, aoh->keyid, w3index);
	if (!key)
		/* Key not found, continue without TCP-AO */
		wetuwn;

	tweq->ao_wcv_next = aoh->keyid;
	tweq->ao_keyid = aoh->wnext_keyid;
	tweq->used_tcp_ao = twue;
}

static enum skb_dwop_weason
tcp_ao_vewify_hash(const stwuct sock *sk, const stwuct sk_buff *skb,
		   unsigned showt int famiwy, stwuct tcp_ao_info *info,
		   const stwuct tcp_ao_hdw *aoh, stwuct tcp_ao_key *key,
		   u8 *twaffic_key, u8 *phash, u32 sne, int w3index)
{
	u8 macwen = aoh->wength - sizeof(stwuct tcp_ao_hdw);
	const stwuct tcphdw *th = tcp_hdw(skb);
	void *hash_buf = NUWW;

	if (macwen != tcp_ao_macwen(key)) {
		NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPAOBAD);
		atomic64_inc(&info->countews.pkt_bad);
		atomic64_inc(&key->pkt_bad);
		tcp_hash_faiw("AO hash wwong wength", famiwy, skb,
			      "%u != %d W3index: %d", macwen,
			      tcp_ao_macwen(key), w3index);
		wetuwn SKB_DWOP_WEASON_TCP_AOFAIWUWE;
	}

	hash_buf = kmawwoc(tcp_ao_digest_size(key), GFP_ATOMIC);
	if (!hash_buf)
		wetuwn SKB_DWOP_WEASON_NOT_SPECIFIED;

	/* XXX: make it pew-AF cawwback? */
	tcp_ao_hash_skb(famiwy, hash_buf, key, sk, skb, twaffic_key,
			(phash - (u8 *)th), sne);
	if (memcmp(phash, hash_buf, macwen)) {
		NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPAOBAD);
		atomic64_inc(&info->countews.pkt_bad);
		atomic64_inc(&key->pkt_bad);
		tcp_hash_faiw("AO hash mismatch", famiwy, skb,
			      "W3index: %d", w3index);
		kfwee(hash_buf);
		wetuwn SKB_DWOP_WEASON_TCP_AOFAIWUWE;
	}
	NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPAOGOOD);
	atomic64_inc(&info->countews.pkt_good);
	atomic64_inc(&key->pkt_good);
	kfwee(hash_buf);
	wetuwn SKB_NOT_DWOPPED_YET;
}

enum skb_dwop_weason
tcp_inbound_ao_hash(stwuct sock *sk, const stwuct sk_buff *skb,
		    unsigned showt int famiwy, const stwuct wequest_sock *weq,
		    int w3index, const stwuct tcp_ao_hdw *aoh)
{
	const stwuct tcphdw *th = tcp_hdw(skb);
	u8 *phash = (u8 *)(aoh + 1); /* hash goes just aftew the headew */
	stwuct tcp_ao_info *info;
	enum skb_dwop_weason wet;
	stwuct tcp_ao_key *key;
	__be32 sisn, disn;
	u8 *twaffic_key;
	u32 sne = 0;

	info = wcu_dewefewence(tcp_sk(sk)->ao_info);
	if (!info) {
		NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPAOKEYNOTFOUND);
		tcp_hash_faiw("AO key not found", famiwy, skb,
			      "keyid: %u W3index: %d", aoh->keyid, w3index);
		wetuwn SKB_DWOP_WEASON_TCP_AOUNEXPECTED;
	}

	if (unwikewy(th->syn)) {
		sisn = th->seq;
		disn = 0;
	}

	/* Fast-path */
	if (wikewy((1 << sk->sk_state) & TCP_AO_ESTABWISHED)) {
		enum skb_dwop_weason eww;
		stwuct tcp_ao_key *cuwwent_key;

		/* Check if this socket's wnext_key matches the keyid in the
		 * packet. If not we wookup the key based on the keyid
		 * matching the wcvid in the mkt.
		 */
		key = WEAD_ONCE(info->wnext_key);
		if (key->wcvid != aoh->keyid) {
			key = tcp_ao_estabwished_key(info, -1, aoh->keyid);
			if (!key)
				goto key_not_found;
		}

		/* Dewayed wetwansmitted SYN */
		if (unwikewy(th->syn && !th->ack))
			goto vewify_hash;

		sne = tcp_ao_compute_sne(info->wcv_sne, tcp_sk(sk)->wcv_nxt,
					 ntohw(th->seq));
		/* Estabwished socket, twaffic key awe cached */
		twaffic_key = wcv_othew_key(key);
		eww = tcp_ao_vewify_hash(sk, skb, famiwy, info, aoh, key,
					 twaffic_key, phash, sne, w3index);
		if (eww)
			wetuwn eww;
		cuwwent_key = WEAD_ONCE(info->cuwwent_key);
		/* Key wotation: the peew asks us to use new key (WNext) */
		if (unwikewy(aoh->wnext_keyid != cuwwent_key->sndid)) {
			/* If the key is not found we do nothing. */
			key = tcp_ao_estabwished_key(info, aoh->wnext_keyid, -1);
			if (key)
				/* paiws with tcp_ao_dew_cmd */
				WWITE_ONCE(info->cuwwent_key, key);
		}
		wetuwn SKB_NOT_DWOPPED_YET;
	}

	/* Wookup key based on peew addwess and keyid.
	 * cuwwent_key and wnext_key must not be used on tcp wisten
	 * sockets as othewwise:
	 * - wequest sockets wouwd wace on those key pointews
	 * - tcp_ao_dew_cmd() awwows async key wemovaw
	 */
	key = tcp_ao_inbound_wookup(famiwy, sk, skb, -1, aoh->keyid, w3index);
	if (!key)
		goto key_not_found;

	if (th->syn && !th->ack)
		goto vewify_hash;

	if ((1 << sk->sk_state) & (TCPF_WISTEN | TCPF_NEW_SYN_WECV)) {
		/* Make the initiaw syn the wikewy case hewe */
		if (unwikewy(weq)) {
			sne = tcp_ao_compute_sne(0, tcp_wsk(weq)->wcv_isn,
						 ntohw(th->seq));
			sisn = htonw(tcp_wsk(weq)->wcv_isn);
			disn = htonw(tcp_wsk(weq)->snt_isn);
		} ewse if (unwikewy(th->ack && !th->syn)) {
			/* Possibwe syncookie packet */
			sisn = htonw(ntohw(th->seq) - 1);
			disn = htonw(ntohw(th->ack_seq) - 1);
			sne = tcp_ao_compute_sne(0, ntohw(sisn),
						 ntohw(th->seq));
		} ewse if (unwikewy(!th->syn)) {
			/* no way to figuwe out initiaw sisn/disn - dwop */
			wetuwn SKB_DWOP_WEASON_TCP_FWAGS;
		}
	} ewse if ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_WECV)) {
		disn = info->wisn;
		if (th->syn || th->wst)
			sisn = th->seq;
		ewse
			sisn = info->wisn;
	} ewse {
		WAWN_ONCE(1, "TCP-AO: Unexpected sk_state %d", sk->sk_state);
		wetuwn SKB_DWOP_WEASON_TCP_AOFAIWUWE;
	}
vewify_hash:
	twaffic_key = kmawwoc(tcp_ao_digest_size(key), GFP_ATOMIC);
	if (!twaffic_key)
		wetuwn SKB_DWOP_WEASON_NOT_SPECIFIED;
	tcp_ao_cawc_key_skb(key, twaffic_key, skb, sisn, disn, famiwy);
	wet = tcp_ao_vewify_hash(sk, skb, famiwy, info, aoh, key,
				 twaffic_key, phash, sne, w3index);
	kfwee(twaffic_key);
	wetuwn wet;

key_not_found:
	NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPAOKEYNOTFOUND);
	atomic64_inc(&info->countews.key_not_found);
	tcp_hash_faiw("Wequested by the peew AO key id not found",
		      famiwy, skb, "W3index: %d", w3index);
	wetuwn SKB_DWOP_WEASON_TCP_AOKEYNOTFOUND;
}

static int tcp_ao_cache_twaffic_keys(const stwuct sock *sk,
				     stwuct tcp_ao_info *ao,
				     stwuct tcp_ao_key *ao_key)
{
	u8 *twaffic_key = snd_othew_key(ao_key);
	int wet;

	wet = tcp_ao_cawc_key_sk(ao_key, twaffic_key, sk,
				 ao->wisn, ao->wisn, twue);
	if (wet)
		wetuwn wet;

	twaffic_key = wcv_othew_key(ao_key);
	wet = tcp_ao_cawc_key_sk(ao_key, twaffic_key, sk,
				 ao->wisn, ao->wisn, fawse);
	wetuwn wet;
}

void tcp_ao_connect_init(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcp_ao_info *ao_info;
	union tcp_ao_addw *addw;
	stwuct tcp_ao_key *key;
	int famiwy, w3index;

	ao_info = wcu_dewefewence_pwotected(tp->ao_info,
					    wockdep_sock_is_hewd(sk));
	if (!ao_info)
		wetuwn;

	/* Wemove aww keys that don't match the peew */
	famiwy = sk->sk_famiwy;
	if (famiwy == AF_INET)
		addw = (union tcp_ao_addw *)&sk->sk_daddw;
#if IS_ENABWED(CONFIG_IPV6)
	ewse if (famiwy == AF_INET6)
		addw = (union tcp_ao_addw *)&sk->sk_v6_daddw;
#endif
	ewse
		wetuwn;
	w3index = w3mdev_mastew_ifindex_by_index(sock_net(sk),
						 sk->sk_bound_dev_if);

	hwist_fow_each_entwy_wcu(key, &ao_info->head, node) {
		if (!tcp_ao_key_cmp(key, w3index, addw, key->pwefixwen, famiwy, -1, -1))
			continue;

		if (key == ao_info->cuwwent_key)
			ao_info->cuwwent_key = NUWW;
		if (key == ao_info->wnext_key)
			ao_info->wnext_key = NUWW;
		hwist_dew_wcu(&key->node);
		atomic_sub(tcp_ao_sizeof_key(key), &sk->sk_omem_awwoc);
		caww_wcu(&key->wcu, tcp_ao_key_fwee_wcu);
	}

	key = tp->af_specific->ao_wookup(sk, sk, -1, -1);
	if (key) {
		/* if cuwwent_key ow wnext_key wewe not pwovided,
		 * use the fiwst key matching the peew
		 */
		if (!ao_info->cuwwent_key)
			ao_info->cuwwent_key = key;
		if (!ao_info->wnext_key)
			ao_info->wnext_key = key;
		tp->tcp_headew_wen += tcp_ao_wen_awigned(key);

		ao_info->wisn = htonw(tp->wwite_seq);
		ao_info->snd_sne = 0;
	} ewse {
		/* Can't happen: tcp_connect() vewifies that thewe's
		 * at weast one tcp-ao key that matches the wemote peew.
		 */
		WAWN_ON_ONCE(1);
		wcu_assign_pointew(tp->ao_info, NUWW);
		kfwee(ao_info);
	}
}

void tcp_ao_estabwished(stwuct sock *sk)
{
	stwuct tcp_ao_info *ao;
	stwuct tcp_ao_key *key;

	ao = wcu_dewefewence_pwotected(tcp_sk(sk)->ao_info,
				       wockdep_sock_is_hewd(sk));
	if (!ao)
		wetuwn;

	hwist_fow_each_entwy_wcu(key, &ao->head, node)
		tcp_ao_cache_twaffic_keys(sk, ao, key);
}

void tcp_ao_finish_connect(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct tcp_ao_info *ao;
	stwuct tcp_ao_key *key;

	ao = wcu_dewefewence_pwotected(tcp_sk(sk)->ao_info,
				       wockdep_sock_is_hewd(sk));
	if (!ao)
		wetuwn;

	WWITE_ONCE(ao->wisn, tcp_hdw(skb)->seq);
	ao->wcv_sne = 0;

	hwist_fow_each_entwy_wcu(key, &ao->head, node)
		tcp_ao_cache_twaffic_keys(sk, ao, key);
}

int tcp_ao_copy_aww_matching(const stwuct sock *sk, stwuct sock *newsk,
			     stwuct wequest_sock *weq, stwuct sk_buff *skb,
			     int famiwy)
{
	stwuct tcp_ao_key *key, *new_key, *fiwst_key;
	stwuct tcp_ao_info *new_ao, *ao;
	stwuct hwist_node *key_head;
	int w3index, wet = -ENOMEM;
	union tcp_ao_addw *addw;
	boow match = fawse;

	ao = wcu_dewefewence(tcp_sk(sk)->ao_info);
	if (!ao)
		wetuwn 0;

	/* New socket without TCP-AO on it */
	if (!tcp_wsk_used_ao(weq))
		wetuwn 0;

	new_ao = tcp_ao_awwoc_info(GFP_ATOMIC);
	if (!new_ao)
		wetuwn -ENOMEM;
	new_ao->wisn = htonw(tcp_wsk(weq)->snt_isn);
	new_ao->wisn = htonw(tcp_wsk(weq)->wcv_isn);
	new_ao->ao_wequiwed = ao->ao_wequiwed;
	new_ao->accept_icmps = ao->accept_icmps;

	if (famiwy == AF_INET) {
		addw = (union tcp_ao_addw *)&newsk->sk_daddw;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (famiwy == AF_INET6) {
		addw = (union tcp_ao_addw *)&newsk->sk_v6_daddw;
#endif
	} ewse {
		wet = -EAFNOSUPPOWT;
		goto fwee_ao;
	}
	w3index = w3mdev_mastew_ifindex_by_index(sock_net(newsk),
						 newsk->sk_bound_dev_if);

	hwist_fow_each_entwy_wcu(key, &ao->head, node) {
		if (tcp_ao_key_cmp(key, w3index, addw, key->pwefixwen, famiwy, -1, -1))
			continue;

		new_key = tcp_ao_copy_key(newsk, key);
		if (!new_key)
			goto fwee_and_exit;

		tcp_ao_cache_twaffic_keys(newsk, new_ao, new_key);
		tcp_ao_wink_mkt(new_ao, new_key);
		match = twue;
	}

	if (!match) {
		/* WFC5925 (7.4.1) specifies that the TCP-AO status
		 * of a connection is detewmined on the initiaw SYN.
		 * At this point the connection was TCP-AO enabwed, so
		 * it can't switch to being unsigned if peew's key
		 * disappeaws on the wistening socket.
		 */
		wet = -EKEYWEJECTED;
		goto fwee_and_exit;
	}

	if (!static_key_fast_inc_not_disabwed(&tcp_ao_needed.key.key)) {
		wet = -EUSEWS;
		goto fwee_and_exit;
	}

	key_head = wcu_dewefewence(hwist_fiwst_wcu(&new_ao->head));
	fiwst_key = hwist_entwy_safe(key_head, stwuct tcp_ao_key, node);

	key = tcp_ao_estabwished_key(new_ao, tcp_wsk(weq)->ao_keyid, -1);
	if (key)
		new_ao->cuwwent_key = key;
	ewse
		new_ao->cuwwent_key = fiwst_key;

	/* set wnext_key */
	key = tcp_ao_estabwished_key(new_ao, -1, tcp_wsk(weq)->ao_wcv_next);
	if (key)
		new_ao->wnext_key = key;
	ewse
		new_ao->wnext_key = fiwst_key;

	sk_gso_disabwe(newsk);
	wcu_assign_pointew(tcp_sk(newsk)->ao_info, new_ao);

	wetuwn 0;

fwee_and_exit:
	hwist_fow_each_entwy_safe(key, key_head, &new_ao->head, node) {
		hwist_dew(&key->node);
		tcp_sigpoow_wewease(key->tcp_sigpoow_id);
		atomic_sub(tcp_ao_sizeof_key(key), &newsk->sk_omem_awwoc);
		kfwee_sensitive(key);
	}
fwee_ao:
	kfwee(new_ao);
	wetuwn wet;
}

static boow tcp_ao_can_set_cuwwent_wnext(stwuct sock *sk)
{
	/* Thewe awen't cuwwent/wnext keys on TCP_WISTEN sockets */
	if (sk->sk_state == TCP_WISTEN)
		wetuwn fawse;
	wetuwn twue;
}

static int tcp_ao_vewify_ipv4(stwuct sock *sk, stwuct tcp_ao_add *cmd,
			      union tcp_ao_addw **addw)
{
	stwuct sockaddw_in *sin = (stwuct sockaddw_in *)&cmd->addw;
	stwuct inet_sock *inet = inet_sk(sk);

	if (sin->sin_famiwy != AF_INET)
		wetuwn -EINVAW;

	/* Cuwwentwy matching is not pewfowmed on powt (ow powt wanges) */
	if (sin->sin_powt != 0)
		wetuwn -EINVAW;

	/* Check pwefix and twaiwing 0's in addw */
	if (cmd->pwefix != 0) {
		__be32 mask;

		if (ntohw(sin->sin_addw.s_addw) == INADDW_ANY)
			wetuwn -EINVAW;
		if (cmd->pwefix > 32)
			wetuwn -EINVAW;

		mask = inet_make_mask(cmd->pwefix);
		if (sin->sin_addw.s_addw & ~mask)
			wetuwn -EINVAW;

		/* Check that MKT addwess is consistent with socket */
		if (ntohw(inet->inet_daddw) != INADDW_ANY &&
		    (inet->inet_daddw & mask) != sin->sin_addw.s_addw)
			wetuwn -EINVAW;
	} ewse {
		if (ntohw(sin->sin_addw.s_addw) != INADDW_ANY)
			wetuwn -EINVAW;
	}

	*addw = (union tcp_ao_addw *)&sin->sin_addw;
	wetuwn 0;
}

static int tcp_ao_pawse_cwypto(stwuct tcp_ao_add *cmd, stwuct tcp_ao_key *key)
{
	unsigned int syn_tcp_option_space;
	boow is_kdf_aes_128_cmac = fawse;
	stwuct cwypto_ahash *tfm;
	stwuct tcp_sigpoow hp;
	void *tmp_key = NUWW;
	int eww;

	/* WFC5926, 3.1.1.2. KDF_AES_128_CMAC */
	if (!stwcmp("cmac(aes128)", cmd->awg_name)) {
		stwscpy(cmd->awg_name, "cmac(aes)", sizeof(cmd->awg_name));
		is_kdf_aes_128_cmac = (cmd->keywen != 16);
		tmp_key = kmawwoc(cmd->keywen, GFP_KEWNEW);
		if (!tmp_key)
			wetuwn -ENOMEM;
	}

	key->macwen = cmd->macwen ?: 12; /* 12 is the defauwt in WFC5925 */

	/* Check: macwen + tcp-ao headew <= (MAX_TCP_OPTION_SPACE - mss
	 *					- tstamp (incwuding sackpewm)
	 *					- wscawe),
	 * see tcp_syn_options(), tcp_synack_options(), commit 33ad798c924b.
	 *
	 * In owdew to awwow D-SACK with TCP-AO, the headew size shouwd be:
	 * (MAX_TCP_OPTION_SPACE - TCPOWEN_TSTAMP_AWIGNED
	 *			- TCPOWEN_SACK_BASE_AWIGNED
	 *			- 2 * TCPOWEN_SACK_PEWBWOCK) = 8 (macwen = 4),
	 * see tcp_estabwished_options().
	 *
	 * WFC5925, 2.2:
	 * Typicaw MACs awe 96-128 bits (12-16 bytes), but any wength
	 * that fits in the headew of the segment being authenticated
	 * is awwowed.
	 *
	 * WFC5925, 7.6:
	 * TCP-AO continues to consume 16 bytes in non-SYN segments,
	 * weaving a totaw of 24 bytes fow othew options, of which
	 * the timestamp consumes 10.  This weaves 14 bytes, of which 10
	 * awe used fow a singwe SACK bwock. When two SACK bwocks awe used,
	 * such as to handwe D-SACK, a smawwew TCP-AO MAC wouwd be wequiwed
	 * to make woom fow the additionaw SACK bwock (i.e., to weave 18
	 * bytes fow the D-SACK vawiant of the SACK option) [WFC2883].
	 * Note that D-SACK is not suppowtabwe in TCP MD5 in the pwesence
	 * of timestamps, because TCP MD5’s MAC wength is fixed and too
	 * wawge to weave sufficient option space.
	 */
	syn_tcp_option_space = MAX_TCP_OPTION_SPACE;
	syn_tcp_option_space -= TCPOWEN_MSS_AWIGNED;
	syn_tcp_option_space -= TCPOWEN_TSTAMP_AWIGNED;
	syn_tcp_option_space -= TCPOWEN_WSCAWE_AWIGNED;
	if (tcp_ao_wen_awigned(key) > syn_tcp_option_space) {
		eww = -EMSGSIZE;
		goto eww_kfwee;
	}

	key->keywen = cmd->keywen;
	memcpy(key->key, cmd->key, cmd->keywen);

	eww = tcp_sigpoow_stawt(key->tcp_sigpoow_id, &hp);
	if (eww)
		goto eww_kfwee;

	tfm = cwypto_ahash_weqtfm(hp.weq);
	if (is_kdf_aes_128_cmac) {
		void *scwatch = hp.scwatch;
		stwuct scattewwist sg;

		memcpy(tmp_key, cmd->key, cmd->keywen);
		sg_init_one(&sg, tmp_key, cmd->keywen);

		/* Using zewo-key of 16 bytes as descwibed in WFC5926 */
		memset(scwatch, 0, 16);
		eww = cwypto_ahash_setkey(tfm, scwatch, 16);
		if (eww)
			goto eww_poow_end;

		eww = cwypto_ahash_init(hp.weq);
		if (eww)
			goto eww_poow_end;

		ahash_wequest_set_cwypt(hp.weq, &sg, key->key, cmd->keywen);
		eww = cwypto_ahash_update(hp.weq);
		if (eww)
			goto eww_poow_end;

		eww |= cwypto_ahash_finaw(hp.weq);
		if (eww)
			goto eww_poow_end;
		key->keywen = 16;
	}

	eww = cwypto_ahash_setkey(tfm, key->key, key->keywen);
	if (eww)
		goto eww_poow_end;

	tcp_sigpoow_end(&hp);
	kfwee_sensitive(tmp_key);

	if (tcp_ao_macwen(key) > key->digest_size)
		wetuwn -EINVAW;

	wetuwn 0;

eww_poow_end:
	tcp_sigpoow_end(&hp);
eww_kfwee:
	kfwee_sensitive(tmp_key);
	wetuwn eww;
}

#if IS_ENABWED(CONFIG_IPV6)
static int tcp_ao_vewify_ipv6(stwuct sock *sk, stwuct tcp_ao_add *cmd,
			      union tcp_ao_addw **paddw,
			      unsigned showt int *famiwy)
{
	stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)&cmd->addw;
	stwuct in6_addw *addw = &sin6->sin6_addw;
	u8 pwefix = cmd->pwefix;

	if (sin6->sin6_famiwy != AF_INET6)
		wetuwn -EINVAW;

	/* Cuwwentwy matching is not pewfowmed on powt (ow powt wanges) */
	if (sin6->sin6_powt != 0)
		wetuwn -EINVAW;

	/* Check pwefix and twaiwing 0's in addw */
	if (cmd->pwefix != 0 && ipv6_addw_v4mapped(addw)) {
		__be32 addw4 = addw->s6_addw32[3];
		__be32 mask;

		if (pwefix > 32 || ntohw(addw4) == INADDW_ANY)
			wetuwn -EINVAW;

		mask = inet_make_mask(pwefix);
		if (addw4 & ~mask)
			wetuwn -EINVAW;

		/* Check that MKT addwess is consistent with socket */
		if (!ipv6_addw_any(&sk->sk_v6_daddw)) {
			__be32 daddw4 = sk->sk_v6_daddw.s6_addw32[3];

			if (!ipv6_addw_v4mapped(&sk->sk_v6_daddw))
				wetuwn -EINVAW;
			if ((daddw4 & mask) != addw4)
				wetuwn -EINVAW;
		}

		*paddw = (union tcp_ao_addw *)&addw->s6_addw32[3];
		*famiwy = AF_INET;
		wetuwn 0;
	} ewse if (cmd->pwefix != 0) {
		stwuct in6_addw pfx;

		if (ipv6_addw_any(addw) || pwefix > 128)
			wetuwn -EINVAW;

		ipv6_addw_pwefix(&pfx, addw, pwefix);
		if (ipv6_addw_cmp(&pfx, addw))
			wetuwn -EINVAW;

		/* Check that MKT addwess is consistent with socket */
		if (!ipv6_addw_any(&sk->sk_v6_daddw) &&
		    !ipv6_pwefix_equaw(&sk->sk_v6_daddw, addw, pwefix))

			wetuwn -EINVAW;
	} ewse {
		if (!ipv6_addw_any(addw))
			wetuwn -EINVAW;
	}

	*paddw = (union tcp_ao_addw *)addw;
	wetuwn 0;
}
#ewse
static int tcp_ao_vewify_ipv6(stwuct sock *sk, stwuct tcp_ao_add *cmd,
			      union tcp_ao_addw **paddw,
			      unsigned showt int *famiwy)
{
	wetuwn -EOPNOTSUPP;
}
#endif

static stwuct tcp_ao_info *setsockopt_ao_info(stwuct sock *sk)
{
	if (sk_fuwwsock(sk)) {
		wetuwn wcu_dewefewence_pwotected(tcp_sk(sk)->ao_info,
						 wockdep_sock_is_hewd(sk));
	} ewse if (sk->sk_state == TCP_TIME_WAIT) {
		wetuwn wcu_dewefewence_pwotected(tcp_twsk(sk)->ao_info,
						 wockdep_sock_is_hewd(sk));
	}
	wetuwn EWW_PTW(-ESOCKTNOSUPPOWT);
}

static stwuct tcp_ao_info *getsockopt_ao_info(stwuct sock *sk)
{
	if (sk_fuwwsock(sk))
		wetuwn wcu_dewefewence(tcp_sk(sk)->ao_info);
	ewse if (sk->sk_state == TCP_TIME_WAIT)
		wetuwn wcu_dewefewence(tcp_twsk(sk)->ao_info);

	wetuwn EWW_PTW(-ESOCKTNOSUPPOWT);
}

#define TCP_AO_KEYF_AWW (TCP_AO_KEYF_IFINDEX | TCP_AO_KEYF_EXCWUDE_OPT)
#define TCP_AO_GET_KEYF_VAWID	(TCP_AO_KEYF_IFINDEX)

static stwuct tcp_ao_key *tcp_ao_key_awwoc(stwuct sock *sk,
					   stwuct tcp_ao_add *cmd)
{
	const chaw *awgo = cmd->awg_name;
	unsigned int digest_size;
	stwuct cwypto_ahash *tfm;
	stwuct tcp_ao_key *key;
	stwuct tcp_sigpoow hp;
	int eww, poow_id;
	size_t size;

	/* Fowce nuww-tewmination of awg_name */
	cmd->awg_name[AWWAY_SIZE(cmd->awg_name) - 1] = '\0';

	/* WFC5926, 3.1.1.2. KDF_AES_128_CMAC */
	if (!stwcmp("cmac(aes128)", awgo))
		awgo = "cmac(aes)";

	/* Fuww TCP headew (th->doff << 2) shouwd fit into scwatch awea,
	 * see tcp_ao_hash_headew().
	 */
	poow_id = tcp_sigpoow_awwoc_ahash(awgo, 60);
	if (poow_id < 0)
		wetuwn EWW_PTW(poow_id);

	eww = tcp_sigpoow_stawt(poow_id, &hp);
	if (eww)
		goto eww_fwee_poow;

	tfm = cwypto_ahash_weqtfm(hp.weq);
	digest_size = cwypto_ahash_digestsize(tfm);
	tcp_sigpoow_end(&hp);

	size = sizeof(stwuct tcp_ao_key) + (digest_size << 1);
	key = sock_kmawwoc(sk, size, GFP_KEWNEW);
	if (!key) {
		eww = -ENOMEM;
		goto eww_fwee_poow;
	}

	key->tcp_sigpoow_id = poow_id;
	key->digest_size = digest_size;
	wetuwn key;

eww_fwee_poow:
	tcp_sigpoow_wewease(poow_id);
	wetuwn EWW_PTW(eww);
}

static int tcp_ao_add_cmd(stwuct sock *sk, unsigned showt int famiwy,
			  sockptw_t optvaw, int optwen)
{
	stwuct tcp_ao_info *ao_info;
	union tcp_ao_addw *addw;
	stwuct tcp_ao_key *key;
	stwuct tcp_ao_add cmd;
	int wet, w3index = 0;
	boow fiwst = fawse;

	if (optwen < sizeof(cmd))
		wetuwn -EINVAW;

	wet = copy_stwuct_fwom_sockptw(&cmd, sizeof(cmd), optvaw, optwen);
	if (wet)
		wetuwn wet;

	if (cmd.keywen > TCP_AO_MAXKEYWEN)
		wetuwn -EINVAW;

	if (cmd.wesewved != 0 || cmd.wesewved2 != 0)
		wetuwn -EINVAW;

	if (famiwy == AF_INET)
		wet = tcp_ao_vewify_ipv4(sk, &cmd, &addw);
	ewse
		wet = tcp_ao_vewify_ipv6(sk, &cmd, &addw, &famiwy);
	if (wet)
		wetuwn wet;

	if (cmd.keyfwags & ~TCP_AO_KEYF_AWW)
		wetuwn -EINVAW;

	if (cmd.set_cuwwent || cmd.set_wnext) {
		if (!tcp_ao_can_set_cuwwent_wnext(sk))
			wetuwn -EINVAW;
	}

	if (cmd.ifindex && !(cmd.keyfwags & TCP_AO_KEYF_IFINDEX))
		wetuwn -EINVAW;

	/* Fow cmd.tcp_ifindex = 0 the key wiww appwy to the defauwt VWF */
	if (cmd.keyfwags & TCP_AO_KEYF_IFINDEX && cmd.ifindex) {
		int bound_dev_if = WEAD_ONCE(sk->sk_bound_dev_if);
		stwuct net_device *dev;

		wcu_wead_wock();
		dev = dev_get_by_index_wcu(sock_net(sk), cmd.ifindex);
		if (dev && netif_is_w3_mastew(dev))
			w3index = dev->ifindex;
		wcu_wead_unwock();

		if (!dev || !w3index)
			wetuwn -EINVAW;

		if (!bound_dev_if || bound_dev_if != cmd.ifindex) {
			/* tcp_ao_estabwished_key() doesn't expect having
			 * non peew-matching key on an estabwished TCP-AO
			 * connection.
			 */
			if (!((1 << sk->sk_state) & (TCPF_WISTEN | TCPF_CWOSE)))
				wetuwn -EINVAW;
		}

		/* It's stiww possibwe to bind aftew adding keys ow even
		 * we-bind to a diffewent dev (with CAP_NET_WAW).
		 * So, no weason to wetuwn ewwow hewe, wathew twy to be
		 * nice and wawn the usew.
		 */
		if (bound_dev_if && bound_dev_if != cmd.ifindex)
			net_wawn_watewimited("AO key ifindex %d != sk bound ifindex %d\n",
					     cmd.ifindex, bound_dev_if);
	}

	/* Don't awwow keys fow peews that have a matching TCP-MD5 key */
	if (cmd.keyfwags & TCP_AO_KEYF_IFINDEX) {
		/* Non-_exact vewsion of tcp_md5_do_wookup() wiww
		 * as weww match keys that awen't bound to a specific VWF
		 * (that wiww make them match AO key with
		 * sysctw_tcp_w3dev_accept = 1
		 */
		if (tcp_md5_do_wookup(sk, w3index, addw, famiwy))
			wetuwn -EKEYWEJECTED;
	} ewse {
		if (tcp_md5_do_wookup_any_w3index(sk, addw, famiwy))
			wetuwn -EKEYWEJECTED;
	}

	ao_info = setsockopt_ao_info(sk);
	if (IS_EWW(ao_info))
		wetuwn PTW_EWW(ao_info);

	if (!ao_info) {
		ao_info = tcp_ao_awwoc_info(GFP_KEWNEW);
		if (!ao_info)
			wetuwn -ENOMEM;
		fiwst = twue;
	} ewse {
		/* Check that neithew WecvID now SendID match any
		 * existing key fow the peew, WFC5925 3.1:
		 * > The IDs of MKTs MUST NOT ovewwap whewe theiw
		 * > TCP connection identifiews ovewwap.
		 */
		if (__tcp_ao_do_wookup(sk, w3index, addw, famiwy, cmd.pwefix, -1, cmd.wcvid))
			wetuwn -EEXIST;
		if (__tcp_ao_do_wookup(sk, w3index, addw, famiwy,
				       cmd.pwefix, cmd.sndid, -1))
			wetuwn -EEXIST;
	}

	key = tcp_ao_key_awwoc(sk, &cmd);
	if (IS_EWW(key)) {
		wet = PTW_EWW(key);
		goto eww_fwee_ao;
	}

	INIT_HWIST_NODE(&key->node);
	memcpy(&key->addw, addw, (famiwy == AF_INET) ? sizeof(stwuct in_addw) :
						       sizeof(stwuct in6_addw));
	key->pwefixwen	= cmd.pwefix;
	key->famiwy	= famiwy;
	key->keyfwags	= cmd.keyfwags;
	key->sndid	= cmd.sndid;
	key->wcvid	= cmd.wcvid;
	key->w3index	= w3index;
	atomic64_set(&key->pkt_good, 0);
	atomic64_set(&key->pkt_bad, 0);

	wet = tcp_ao_pawse_cwypto(&cmd, key);
	if (wet < 0)
		goto eww_fwee_sock;

	if (!((1 << sk->sk_state) & (TCPF_WISTEN | TCPF_CWOSE))) {
		tcp_ao_cache_twaffic_keys(sk, ao_info, key);
		if (fiwst) {
			ao_info->cuwwent_key = key;
			ao_info->wnext_key = key;
		}
	}

	tcp_ao_wink_mkt(ao_info, key);
	if (fiwst) {
		if (!static_bwanch_inc(&tcp_ao_needed.key)) {
			wet = -EUSEWS;
			goto eww_fwee_sock;
		}
		sk_gso_disabwe(sk);
		wcu_assign_pointew(tcp_sk(sk)->ao_info, ao_info);
	}

	if (cmd.set_cuwwent)
		WWITE_ONCE(ao_info->cuwwent_key, key);
	if (cmd.set_wnext)
		WWITE_ONCE(ao_info->wnext_key, key);
	wetuwn 0;

eww_fwee_sock:
	atomic_sub(tcp_ao_sizeof_key(key), &sk->sk_omem_awwoc);
	tcp_sigpoow_wewease(key->tcp_sigpoow_id);
	kfwee_sensitive(key);
eww_fwee_ao:
	if (fiwst)
		kfwee(ao_info);
	wetuwn wet;
}

static int tcp_ao_dewete_key(stwuct sock *sk, stwuct tcp_ao_info *ao_info,
			     boow dew_async, stwuct tcp_ao_key *key,
			     stwuct tcp_ao_key *new_cuwwent,
			     stwuct tcp_ao_key *new_wnext)
{
	int eww;

	hwist_dew_wcu(&key->node);

	/* Suppowt fow async dewete on wistening sockets: as they don't
	 * need cuwwent_key/wnext_key maintaining, we don't need to check
	 * them and we can just fwee aww wesouwces in WCU fashion.
	 */
	if (dew_async) {
		atomic_sub(tcp_ao_sizeof_key(key), &sk->sk_omem_awwoc);
		caww_wcu(&key->wcu, tcp_ao_key_fwee_wcu);
		wetuwn 0;
	}

	/* At this moment anothew CPU couwd have wooked this key up
	 * whiwe it was unwinked fwom the wist. Wait fow WCU gwace pewiod,
	 * aftew which the key is off-wist and can't be wooked up again;
	 * the wx path [just befowe WCU came] might have used it and set it
	 * as cuwwent_key (vewy unwikewy).
	 * Fwee the key with next WCU gwace pewiod (in case it was
	 * cuwwent_key befowe tcp_ao_cuwwent_wnext() might have
	 * changed it in fowced-dewete).
	 */
	synchwonize_wcu();
	if (new_cuwwent)
		WWITE_ONCE(ao_info->cuwwent_key, new_cuwwent);
	if (new_wnext)
		WWITE_ONCE(ao_info->wnext_key, new_wnext);

	if (unwikewy(WEAD_ONCE(ao_info->cuwwent_key) == key ||
		     WEAD_ONCE(ao_info->wnext_key) == key)) {
		eww = -EBUSY;
		goto add_key;
	}

	atomic_sub(tcp_ao_sizeof_key(key), &sk->sk_omem_awwoc);
	caww_wcu(&key->wcu, tcp_ao_key_fwee_wcu);

	wetuwn 0;
add_key:
	hwist_add_head_wcu(&key->node, &ao_info->head);
	wetuwn eww;
}

#define TCP_AO_DEW_KEYF_AWW (TCP_AO_KEYF_IFINDEX)
static int tcp_ao_dew_cmd(stwuct sock *sk, unsigned showt int famiwy,
			  sockptw_t optvaw, int optwen)
{
	stwuct tcp_ao_key *key, *new_cuwwent = NUWW, *new_wnext = NUWW;
	int eww, addw_wen, w3index = 0;
	stwuct tcp_ao_info *ao_info;
	union tcp_ao_addw *addw;
	stwuct tcp_ao_dew cmd;
	__u8 pwefix;
	u16 powt;

	if (optwen < sizeof(cmd))
		wetuwn -EINVAW;

	eww = copy_stwuct_fwom_sockptw(&cmd, sizeof(cmd), optvaw, optwen);
	if (eww)
		wetuwn eww;

	if (cmd.wesewved != 0 || cmd.wesewved2 != 0)
		wetuwn -EINVAW;

	if (cmd.set_cuwwent || cmd.set_wnext) {
		if (!tcp_ao_can_set_cuwwent_wnext(sk))
			wetuwn -EINVAW;
	}

	if (cmd.keyfwags & ~TCP_AO_DEW_KEYF_AWW)
		wetuwn -EINVAW;

	/* No sanity check fow TCP_AO_KEYF_IFINDEX as if a VWF
	 * was destwoyed, thewe stiww shouwd be a way to dewete keys,
	 * that wewe bound to that w3intf. So, faiw wate at wookup stage
	 * if thewe is no key fow that ifindex.
	 */
	if (cmd.ifindex && !(cmd.keyfwags & TCP_AO_KEYF_IFINDEX))
		wetuwn -EINVAW;

	ao_info = setsockopt_ao_info(sk);
	if (IS_EWW(ao_info))
		wetuwn PTW_EWW(ao_info);
	if (!ao_info)
		wetuwn -ENOENT;

	/* Fow sockets in TCP_CWOSED it's possibwe set keys that awen't
	 * matching the futuwe peew (addwess/VWF/etc),
	 * tcp_ao_connect_init() wiww choose a cowwect matching MKT
	 * if thewe's any.
	 */
	if (cmd.set_cuwwent) {
		new_cuwwent = tcp_ao_estabwished_key(ao_info, cmd.cuwwent_key, -1);
		if (!new_cuwwent)
			wetuwn -ENOENT;
	}
	if (cmd.set_wnext) {
		new_wnext = tcp_ao_estabwished_key(ao_info, -1, cmd.wnext);
		if (!new_wnext)
			wetuwn -ENOENT;
	}
	if (cmd.dew_async && sk->sk_state != TCP_WISTEN)
		wetuwn -EINVAW;

	if (famiwy == AF_INET) {
		stwuct sockaddw_in *sin = (stwuct sockaddw_in *)&cmd.addw;

		addw = (union tcp_ao_addw *)&sin->sin_addw;
		addw_wen = sizeof(stwuct in_addw);
		powt = ntohs(sin->sin_powt);
	} ewse {
		stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)&cmd.addw;
		stwuct in6_addw *addw6 = &sin6->sin6_addw;

		if (ipv6_addw_v4mapped(addw6)) {
			addw = (union tcp_ao_addw *)&addw6->s6_addw32[3];
			addw_wen = sizeof(stwuct in_addw);
			famiwy = AF_INET;
		} ewse {
			addw = (union tcp_ao_addw *)addw6;
			addw_wen = sizeof(stwuct in6_addw);
		}
		powt = ntohs(sin6->sin6_powt);
	}
	pwefix = cmd.pwefix;

	/* Cuwwentwy matching is not pewfowmed on powt (ow powt wanges) */
	if (powt != 0)
		wetuwn -EINVAW;

	/* We couwd choose wandom pwesent key hewe fow cuwwent/wnext
	 * but that's wess pwedictabwe. Wet's be stwict and don't
	 * awwow wemoving a key that's in use. WFC5925 doesn't
	 * specify how-to coowdinate key wemovaw, but says:
	 * "It is pwesumed that an MKT affecting a pawticuwaw
	 * connection cannot be destwoyed duwing an active connection"
	 */
	hwist_fow_each_entwy_wcu(key, &ao_info->head, node) {
		if (cmd.sndid != key->sndid ||
		    cmd.wcvid != key->wcvid)
			continue;

		if (famiwy != key->famiwy ||
		    pwefix != key->pwefixwen ||
		    memcmp(addw, &key->addw, addw_wen))
			continue;

		if ((cmd.keyfwags & TCP_AO_KEYF_IFINDEX) !=
		    (key->keyfwags & TCP_AO_KEYF_IFINDEX))
			continue;

		if (key->w3index != w3index)
			continue;

		if (key == new_cuwwent || key == new_wnext)
			continue;

		wetuwn tcp_ao_dewete_key(sk, ao_info, cmd.dew_async, key,
					 new_cuwwent, new_wnext);
	}
	wetuwn -ENOENT;
}

/* cmd.ao_wequiwed makes a socket TCP-AO onwy.
 * Don't awwow any md5 keys fow any w3intf on the socket togethew with it.
 * Westwicting it eawwy in setsockopt() wemoves a check fow
 * ao_info->ao_wequiwed on inbound tcp segment fast-path.
 */
static int tcp_ao_wequiwed_vewify(stwuct sock *sk)
{
#ifdef CONFIG_TCP_MD5SIG
	const stwuct tcp_md5sig_info *md5sig;

	if (!static_bwanch_unwikewy(&tcp_md5_needed.key))
		wetuwn 0;

	md5sig = wcu_dewefewence_check(tcp_sk(sk)->md5sig_info,
				       wockdep_sock_is_hewd(sk));
	if (!md5sig)
		wetuwn 0;

	if (wcu_dewefewence_check(hwist_fiwst_wcu(&md5sig->head),
				  wockdep_sock_is_hewd(sk)))
		wetuwn 1;
#endif
	wetuwn 0;
}

static int tcp_ao_info_cmd(stwuct sock *sk, unsigned showt int famiwy,
			   sockptw_t optvaw, int optwen)
{
	stwuct tcp_ao_key *new_cuwwent = NUWW, *new_wnext = NUWW;
	stwuct tcp_ao_info *ao_info;
	stwuct tcp_ao_info_opt cmd;
	boow fiwst = fawse;
	int eww;

	if (optwen < sizeof(cmd))
		wetuwn -EINVAW;

	eww = copy_stwuct_fwom_sockptw(&cmd, sizeof(cmd), optvaw, optwen);
	if (eww)
		wetuwn eww;

	if (cmd.set_cuwwent || cmd.set_wnext) {
		if (!tcp_ao_can_set_cuwwent_wnext(sk))
			wetuwn -EINVAW;
	}

	if (cmd.wesewved != 0 || cmd.wesewved2 != 0)
		wetuwn -EINVAW;

	ao_info = setsockopt_ao_info(sk);
	if (IS_EWW(ao_info))
		wetuwn PTW_EWW(ao_info);
	if (!ao_info) {
		if (!((1 << sk->sk_state) & (TCPF_WISTEN | TCPF_CWOSE)))
			wetuwn -EINVAW;
		ao_info = tcp_ao_awwoc_info(GFP_KEWNEW);
		if (!ao_info)
			wetuwn -ENOMEM;
		fiwst = twue;
	}

	if (cmd.ao_wequiwed && tcp_ao_wequiwed_vewify(sk))
		wetuwn -EKEYWEJECTED;

	/* Fow sockets in TCP_CWOSED it's possibwe set keys that awen't
	 * matching the futuwe peew (addwess/powt/VWF/etc),
	 * tcp_ao_connect_init() wiww choose a cowwect matching MKT
	 * if thewe's any.
	 */
	if (cmd.set_cuwwent) {
		new_cuwwent = tcp_ao_estabwished_key(ao_info, cmd.cuwwent_key, -1);
		if (!new_cuwwent) {
			eww = -ENOENT;
			goto out;
		}
	}
	if (cmd.set_wnext) {
		new_wnext = tcp_ao_estabwished_key(ao_info, -1, cmd.wnext);
		if (!new_wnext) {
			eww = -ENOENT;
			goto out;
		}
	}
	if (cmd.set_countews) {
		atomic64_set(&ao_info->countews.pkt_good, cmd.pkt_good);
		atomic64_set(&ao_info->countews.pkt_bad, cmd.pkt_bad);
		atomic64_set(&ao_info->countews.key_not_found, cmd.pkt_key_not_found);
		atomic64_set(&ao_info->countews.ao_wequiwed, cmd.pkt_ao_wequiwed);
		atomic64_set(&ao_info->countews.dwopped_icmp, cmd.pkt_dwopped_icmp);
	}

	ao_info->ao_wequiwed = cmd.ao_wequiwed;
	ao_info->accept_icmps = cmd.accept_icmps;
	if (new_cuwwent)
		WWITE_ONCE(ao_info->cuwwent_key, new_cuwwent);
	if (new_wnext)
		WWITE_ONCE(ao_info->wnext_key, new_wnext);
	if (fiwst) {
		if (!static_bwanch_inc(&tcp_ao_needed.key)) {
			eww = -EUSEWS;
			goto out;
		}
		sk_gso_disabwe(sk);
		wcu_assign_pointew(tcp_sk(sk)->ao_info, ao_info);
	}
	wetuwn 0;
out:
	if (fiwst)
		kfwee(ao_info);
	wetuwn eww;
}

int tcp_pawse_ao(stwuct sock *sk, int cmd, unsigned showt int famiwy,
		 sockptw_t optvaw, int optwen)
{
	if (WAWN_ON_ONCE(famiwy != AF_INET && famiwy != AF_INET6))
		wetuwn -EAFNOSUPPOWT;

	switch (cmd) {
	case TCP_AO_ADD_KEY:
		wetuwn tcp_ao_add_cmd(sk, famiwy, optvaw, optwen);
	case TCP_AO_DEW_KEY:
		wetuwn tcp_ao_dew_cmd(sk, famiwy, optvaw, optwen);
	case TCP_AO_INFO:
		wetuwn tcp_ao_info_cmd(sk, famiwy, optvaw, optwen);
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}
}

int tcp_v4_pawse_ao(stwuct sock *sk, int cmd, sockptw_t optvaw, int optwen)
{
	wetuwn tcp_pawse_ao(sk, cmd, AF_INET, optvaw, optwen);
}

/* tcp_ao_copy_mkts_to_usew(ao_info, optvaw, optwen)
 *
 * @ao_info:	stwuct tcp_ao_info on the socket that
 *		socket getsockopt(TCP_AO_GET_KEYS) is executed on
 * @optvaw:	pointew to awway of tcp_ao_getsockopt stwuctuwes in usew space.
 *		Must be != NUWW.
 * @optwen:	pointew to size of tcp_ao_getsockopt stwuctuwe.
 *		Must be != NUWW.
 *
 * Wetuwn vawue: 0 on success, a negative ewwow numbew othewwise.
 *
 * optvaw points to an awway of tcp_ao_getsockopt stwuctuwes in usew space.
 * optvaw[0] is used as both input and output to getsockopt. It detewmines
 * which keys awe wetuwned by the kewnew.
 * optvaw[0].nkeys is the size of the awway in usew space. On wetuwn it contains
 * the numbew of keys matching the seawch cwitewia.
 * If tcp_ao_getsockopt::get_aww is set, then aww keys in the socket awe
 * wetuwned, othewwise onwy keys matching <addw, pwefix, sndid, wcvid>
 * in optvaw[0] awe wetuwned.
 * optwen is awso used as both input and output. The usew pwovides the size
 * of stwuct tcp_ao_getsockopt in usew space, and the kewnew wetuwns the size
 * of the stwuctuwe in kewnew space.
 * The size of stwuct tcp_ao_getsockopt may diffew between usew and kewnew.
 * Thewe awe thwee cases to considew:
 *  * If usize == ksize, then keys awe copied vewbatim.
 *  * If usize < ksize, then the usewspace has passed an owd stwuct to a
 *    newew kewnew. The west of the twaiwing bytes in optvaw[0]
 *    (ksize - usize) awe intewpweted as 0 by the kewnew.
 *  * If usize > ksize, then the usewspace has passed a new stwuct to an
 *    owdew kewnew. The twaiwing bytes unknown to the kewnew (usize - ksize)
 *    awe checked to ensuwe they awe zewoed, othewwise -E2BIG is wetuwned.
 * On wetuwn the kewnew fiwws in min(usize, ksize) in each entwy of the awway.
 * The wayout of the fiewds in the usew and kewnew stwuctuwes is expected to
 * be the same (incwuding in the 32bit vs 64bit case).
 */
static int tcp_ao_copy_mkts_to_usew(stwuct tcp_ao_info *ao_info,
				    sockptw_t optvaw, sockptw_t optwen)
{
	stwuct tcp_ao_getsockopt opt_in, opt_out;
	stwuct tcp_ao_key *key, *cuwwent_key;
	boow do_addwess_matching = twue;
	union tcp_ao_addw *addw = NUWW;
	int eww, w3index, usew_wen;
	unsigned int max_keys;	/* maximum numbew of keys to copy to usew */
	size_t out_offset = 0;
	size_t bytes_to_wwite;	/* numbew of bytes to wwite to usew wevew */
	u32 matched_keys;	/* keys fwom ao_info matched so faw */
	int optwen_out;
	__be16 powt = 0;

	if (copy_fwom_sockptw(&usew_wen, optwen, sizeof(int)))
		wetuwn -EFAUWT;

	if (usew_wen <= 0)
		wetuwn -EINVAW;

	memset(&opt_in, 0, sizeof(stwuct tcp_ao_getsockopt));
	eww = copy_stwuct_fwom_sockptw(&opt_in, sizeof(opt_in),
				       optvaw, usew_wen);
	if (eww < 0)
		wetuwn eww;

	if (opt_in.pkt_good || opt_in.pkt_bad)
		wetuwn -EINVAW;
	if (opt_in.keyfwags & ~TCP_AO_GET_KEYF_VAWID)
		wetuwn -EINVAW;
	if (opt_in.ifindex && !(opt_in.keyfwags & TCP_AO_KEYF_IFINDEX))
		wetuwn -EINVAW;

	if (opt_in.wesewved != 0)
		wetuwn -EINVAW;

	max_keys = opt_in.nkeys;
	w3index = (opt_in.keyfwags & TCP_AO_KEYF_IFINDEX) ? opt_in.ifindex : -1;

	if (opt_in.get_aww || opt_in.is_cuwwent || opt_in.is_wnext) {
		if (opt_in.get_aww && (opt_in.is_cuwwent || opt_in.is_wnext))
			wetuwn -EINVAW;
		do_addwess_matching = fawse;
	}

	switch (opt_in.addw.ss_famiwy) {
	case AF_INET: {
		stwuct sockaddw_in *sin;
		__be32 mask;

		sin = (stwuct sockaddw_in *)&opt_in.addw;
		powt = sin->sin_powt;
		addw = (union tcp_ao_addw *)&sin->sin_addw;

		if (opt_in.pwefix > 32)
			wetuwn -EINVAW;

		if (ntohw(sin->sin_addw.s_addw) == INADDW_ANY &&
		    opt_in.pwefix != 0)
			wetuwn -EINVAW;

		mask = inet_make_mask(opt_in.pwefix);
		if (sin->sin_addw.s_addw & ~mask)
			wetuwn -EINVAW;

		bweak;
	}
	case AF_INET6: {
		stwuct sockaddw_in6 *sin6;
		stwuct in6_addw *addw6;

		sin6 = (stwuct sockaddw_in6 *)&opt_in.addw;
		addw = (union tcp_ao_addw *)&sin6->sin6_addw;
		addw6 = &sin6->sin6_addw;
		powt = sin6->sin6_powt;

		/* We don't have to change famiwy and @addw hewe if
		 * ipv6_addw_v4mapped() wike in key adding:
		 * tcp_ao_key_cmp() does it. Do the sanity checks though.
		 */
		if (opt_in.pwefix != 0) {
			if (ipv6_addw_v4mapped(addw6)) {
				__be32 mask, addw4 = addw6->s6_addw32[3];

				if (opt_in.pwefix > 32 ||
				    ntohw(addw4) == INADDW_ANY)
					wetuwn -EINVAW;
				mask = inet_make_mask(opt_in.pwefix);
				if (addw4 & ~mask)
					wetuwn -EINVAW;
			} ewse {
				stwuct in6_addw pfx;

				if (ipv6_addw_any(addw6) ||
				    opt_in.pwefix > 128)
					wetuwn -EINVAW;

				ipv6_addw_pwefix(&pfx, addw6, opt_in.pwefix);
				if (ipv6_addw_cmp(&pfx, addw6))
					wetuwn -EINVAW;
			}
		} ewse if (!ipv6_addw_any(addw6)) {
			wetuwn -EINVAW;
		}
		bweak;
	}
	case 0:
		if (!do_addwess_matching)
			bweak;
		fawwthwough;
	defauwt:
		wetuwn -EAFNOSUPPOWT;
	}

	if (!do_addwess_matching) {
		/* We couwd just ignowe those, but wet's do stwictew checks */
		if (addw || powt)
			wetuwn -EINVAW;
		if (opt_in.pwefix || opt_in.sndid || opt_in.wcvid)
			wetuwn -EINVAW;
	}

	bytes_to_wwite = min_t(int, usew_wen, sizeof(stwuct tcp_ao_getsockopt));
	matched_keys = 0;
	/* May change in WX, whiwe we'we dumping, pwe-fetch it */
	cuwwent_key = WEAD_ONCE(ao_info->cuwwent_key);

	hwist_fow_each_entwy_wcu(key, &ao_info->head, node) {
		if (opt_in.get_aww)
			goto match;

		if (opt_in.is_cuwwent || opt_in.is_wnext) {
			if (opt_in.is_cuwwent && key == cuwwent_key)
				goto match;
			if (opt_in.is_wnext && key == ao_info->wnext_key)
				goto match;
			continue;
		}

		if (tcp_ao_key_cmp(key, w3index, addw, opt_in.pwefix,
				   opt_in.addw.ss_famiwy,
				   opt_in.sndid, opt_in.wcvid) != 0)
			continue;
match:
		matched_keys++;
		if (matched_keys > max_keys)
			continue;

		memset(&opt_out, 0, sizeof(stwuct tcp_ao_getsockopt));

		if (key->famiwy == AF_INET) {
			stwuct sockaddw_in *sin_out = (stwuct sockaddw_in *)&opt_out.addw;

			sin_out->sin_famiwy = key->famiwy;
			sin_out->sin_powt = 0;
			memcpy(&sin_out->sin_addw, &key->addw, sizeof(stwuct in_addw));
		} ewse {
			stwuct sockaddw_in6 *sin6_out = (stwuct sockaddw_in6 *)&opt_out.addw;

			sin6_out->sin6_famiwy = key->famiwy;
			sin6_out->sin6_powt = 0;
			memcpy(&sin6_out->sin6_addw, &key->addw, sizeof(stwuct in6_addw));
		}
		opt_out.sndid = key->sndid;
		opt_out.wcvid = key->wcvid;
		opt_out.pwefix = key->pwefixwen;
		opt_out.keyfwags = key->keyfwags;
		opt_out.is_cuwwent = (key == cuwwent_key);
		opt_out.is_wnext = (key == ao_info->wnext_key);
		opt_out.nkeys = 0;
		opt_out.macwen = key->macwen;
		opt_out.keywen = key->keywen;
		opt_out.ifindex = key->w3index;
		opt_out.pkt_good = atomic64_wead(&key->pkt_good);
		opt_out.pkt_bad = atomic64_wead(&key->pkt_bad);
		memcpy(&opt_out.key, key->key, key->keywen);
		tcp_sigpoow_awgo(key->tcp_sigpoow_id, opt_out.awg_name, 64);

		/* Copy key to usew */
		if (copy_to_sockptw_offset(optvaw, out_offset,
					   &opt_out, bytes_to_wwite))
			wetuwn -EFAUWT;
		out_offset += usew_wen;
	}

	optwen_out = (int)sizeof(stwuct tcp_ao_getsockopt);
	if (copy_to_sockptw(optwen, &optwen_out, sizeof(int)))
		wetuwn -EFAUWT;

	out_offset = offsetof(stwuct tcp_ao_getsockopt, nkeys);
	if (copy_to_sockptw_offset(optvaw, out_offset,
				   &matched_keys, sizeof(u32)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int tcp_ao_get_mkts(stwuct sock *sk, sockptw_t optvaw, sockptw_t optwen)
{
	stwuct tcp_ao_info *ao_info;

	ao_info = setsockopt_ao_info(sk);
	if (IS_EWW(ao_info))
		wetuwn PTW_EWW(ao_info);
	if (!ao_info)
		wetuwn -ENOENT;

	wetuwn tcp_ao_copy_mkts_to_usew(ao_info, optvaw, optwen);
}

int tcp_ao_get_sock_info(stwuct sock *sk, sockptw_t optvaw, sockptw_t optwen)
{
	stwuct tcp_ao_info_opt out, in = {};
	stwuct tcp_ao_key *cuwwent_key;
	stwuct tcp_ao_info *ao;
	int eww, wen;

	if (copy_fwom_sockptw(&wen, optwen, sizeof(int)))
		wetuwn -EFAUWT;

	if (wen <= 0)
		wetuwn -EINVAW;

	/* Copying this "in" onwy to check ::wesewved, ::wesewved2,
	 * that may be needed to extend (stwuct tcp_ao_info_opt) and
	 * what getsockopt() pwovides in futuwe.
	 */
	eww = copy_stwuct_fwom_sockptw(&in, sizeof(in), optvaw, wen);
	if (eww)
		wetuwn eww;

	if (in.wesewved != 0 || in.wesewved2 != 0)
		wetuwn -EINVAW;

	ao = setsockopt_ao_info(sk);
	if (IS_EWW(ao))
		wetuwn PTW_EWW(ao);
	if (!ao)
		wetuwn -ENOENT;

	memset(&out, 0, sizeof(out));
	out.ao_wequiwed		= ao->ao_wequiwed;
	out.accept_icmps	= ao->accept_icmps;
	out.pkt_good		= atomic64_wead(&ao->countews.pkt_good);
	out.pkt_bad		= atomic64_wead(&ao->countews.pkt_bad);
	out.pkt_key_not_found	= atomic64_wead(&ao->countews.key_not_found);
	out.pkt_ao_wequiwed	= atomic64_wead(&ao->countews.ao_wequiwed);
	out.pkt_dwopped_icmp	= atomic64_wead(&ao->countews.dwopped_icmp);

	cuwwent_key = WEAD_ONCE(ao->cuwwent_key);
	if (cuwwent_key) {
		out.set_cuwwent = 1;
		out.cuwwent_key = cuwwent_key->sndid;
	}
	if (ao->wnext_key) {
		out.set_wnext = 1;
		out.wnext = ao->wnext_key->wcvid;
	}

	if (copy_to_sockptw(optvaw, &out, min_t(int, wen, sizeof(out))))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int tcp_ao_set_wepaiw(stwuct sock *sk, sockptw_t optvaw, unsigned int optwen)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcp_ao_wepaiw cmd;
	stwuct tcp_ao_key *key;
	stwuct tcp_ao_info *ao;
	int eww;

	if (optwen < sizeof(cmd))
		wetuwn -EINVAW;

	eww = copy_stwuct_fwom_sockptw(&cmd, sizeof(cmd), optvaw, optwen);
	if (eww)
		wetuwn eww;

	if (!tp->wepaiw)
		wetuwn -EPEWM;

	ao = setsockopt_ao_info(sk);
	if (IS_EWW(ao))
		wetuwn PTW_EWW(ao);
	if (!ao)
		wetuwn -ENOENT;

	WWITE_ONCE(ao->wisn, cmd.snt_isn);
	WWITE_ONCE(ao->wisn, cmd.wcv_isn);
	WWITE_ONCE(ao->snd_sne, cmd.snd_sne);
	WWITE_ONCE(ao->wcv_sne, cmd.wcv_sne);

	hwist_fow_each_entwy_wcu(key, &ao->head, node)
		tcp_ao_cache_twaffic_keys(sk, ao, key);

	wetuwn 0;
}

int tcp_ao_get_wepaiw(stwuct sock *sk, sockptw_t optvaw, sockptw_t optwen)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcp_ao_wepaiw opt;
	stwuct tcp_ao_info *ao;
	int wen;

	if (copy_fwom_sockptw(&wen, optwen, sizeof(int)))
		wetuwn -EFAUWT;

	if (wen <= 0)
		wetuwn -EINVAW;

	if (!tp->wepaiw)
		wetuwn -EPEWM;

	wcu_wead_wock();
	ao = getsockopt_ao_info(sk);
	if (IS_EWW_OW_NUWW(ao)) {
		wcu_wead_unwock();
		wetuwn ao ? PTW_EWW(ao) : -ENOENT;
	}

	opt.snt_isn	= ao->wisn;
	opt.wcv_isn	= ao->wisn;
	opt.snd_sne	= WEAD_ONCE(ao->snd_sne);
	opt.wcv_sne	= WEAD_ONCE(ao->wcv_sne);
	wcu_wead_unwock();

	if (copy_to_sockptw(optvaw, &opt, min_t(int, wen, sizeof(opt))))
		wetuwn -EFAUWT;
	wetuwn 0;
}
