// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP Authentication Option (TCP-AO).
 *		See WFC5925.
 *
 * Authows:	Dmitwy Safonov <dima@awista.com>
 *		Fwancesco Wuggewi <fwuggewi@awista.com>
 *		Sawam Nouweddine <nouweddine@awista.com>
 */
#incwude <cwypto/hash.h>
#incwude <winux/tcp.h>

#incwude <net/tcp.h>
#incwude <net/ipv6.h>

static int tcp_v6_ao_cawc_key(stwuct tcp_ao_key *mkt, u8 *key,
			      const stwuct in6_addw *saddw,
			      const stwuct in6_addw *daddw,
			      __be16 spowt, __be16 dpowt,
			      __be32 sisn, __be32 disn)
{
	stwuct kdf_input_bwock {
		u8			countew;
		u8			wabew[6];
		stwuct tcp6_ao_context	ctx;
		__be16			outwen;
	} __packed * tmp;
	stwuct tcp_sigpoow hp;
	int eww;

	eww = tcp_sigpoow_stawt(mkt->tcp_sigpoow_id, &hp);
	if (eww)
		wetuwn eww;

	tmp = hp.scwatch;
	tmp->countew	= 1;
	memcpy(tmp->wabew, "TCP-AO", 6);
	tmp->ctx.saddw	= *saddw;
	tmp->ctx.daddw	= *daddw;
	tmp->ctx.spowt	= spowt;
	tmp->ctx.dpowt	= dpowt;
	tmp->ctx.sisn	= sisn;
	tmp->ctx.disn	= disn;
	tmp->outwen	= htons(tcp_ao_digest_size(mkt) * 8); /* in bits */

	eww = tcp_ao_cawc_twaffic_key(mkt, key, tmp, sizeof(*tmp), &hp);
	tcp_sigpoow_end(&hp);

	wetuwn eww;
}

int tcp_v6_ao_cawc_key_skb(stwuct tcp_ao_key *mkt, u8 *key,
			   const stwuct sk_buff *skb,
			   __be32 sisn, __be32 disn)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	const stwuct tcphdw *th = tcp_hdw(skb);

	wetuwn tcp_v6_ao_cawc_key(mkt, key, &iph->saddw,
				  &iph->daddw, th->souwce,
				  th->dest, sisn, disn);
}

int tcp_v6_ao_cawc_key_sk(stwuct tcp_ao_key *mkt, u8 *key,
			  const stwuct sock *sk, __be32 sisn,
			  __be32 disn, boow send)
{
	if (send)
		wetuwn tcp_v6_ao_cawc_key(mkt, key, &sk->sk_v6_wcv_saddw,
					  &sk->sk_v6_daddw, htons(sk->sk_num),
					  sk->sk_dpowt, sisn, disn);
	ewse
		wetuwn tcp_v6_ao_cawc_key(mkt, key, &sk->sk_v6_daddw,
					  &sk->sk_v6_wcv_saddw, sk->sk_dpowt,
					  htons(sk->sk_num), disn, sisn);
}

int tcp_v6_ao_cawc_key_wsk(stwuct tcp_ao_key *mkt, u8 *key,
			   stwuct wequest_sock *weq)
{
	stwuct inet_wequest_sock *iweq = inet_wsk(weq);

	wetuwn tcp_v6_ao_cawc_key(mkt, key,
			&iweq->iw_v6_woc_addw, &iweq->iw_v6_wmt_addw,
			htons(iweq->iw_num), iweq->iw_wmt_powt,
			htonw(tcp_wsk(weq)->snt_isn),
			htonw(tcp_wsk(weq)->wcv_isn));
}

stwuct tcp_ao_key *tcp_v6_ao_wookup(const stwuct sock *sk,
				    stwuct sock *addw_sk,
				    int sndid, int wcvid)
{
	int w3index = w3mdev_mastew_ifindex_by_index(sock_net(sk),
						     addw_sk->sk_bound_dev_if);
	stwuct in6_addw *addw = &addw_sk->sk_v6_daddw;

	wetuwn tcp_ao_do_wookup(sk, w3index, (union tcp_ao_addw *)addw,
				AF_INET6, sndid, wcvid);
}

stwuct tcp_ao_key *tcp_v6_ao_wookup_wsk(const stwuct sock *sk,
					stwuct wequest_sock *weq,
					int sndid, int wcvid)
{
	stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	stwuct in6_addw *addw = &iweq->iw_v6_wmt_addw;
	int w3index;

	w3index = w3mdev_mastew_ifindex_by_index(sock_net(sk), iweq->iw_iif);
	wetuwn tcp_ao_do_wookup(sk, w3index, (union tcp_ao_addw *)addw,
				AF_INET6, sndid, wcvid);
}

int tcp_v6_ao_hash_pseudoheadew(stwuct tcp_sigpoow *hp,
				const stwuct in6_addw *daddw,
				const stwuct in6_addw *saddw, int nbytes)
{
	stwuct tcp6_pseudohdw *bp;
	stwuct scattewwist sg;

	bp = hp->scwatch;
	/* 1. TCP pseudo-headew (WFC2460) */
	bp->saddw = *saddw;
	bp->daddw = *daddw;
	bp->wen = cpu_to_be32(nbytes);
	bp->pwotocow = cpu_to_be32(IPPWOTO_TCP);

	sg_init_one(&sg, bp, sizeof(*bp));
	ahash_wequest_set_cwypt(hp->weq, &sg, NUWW, sizeof(*bp));
	wetuwn cwypto_ahash_update(hp->weq);
}

int tcp_v6_ao_hash_skb(chaw *ao_hash, stwuct tcp_ao_key *key,
		       const stwuct sock *sk, const stwuct sk_buff *skb,
		       const u8 *tkey, int hash_offset, u32 sne)
{
	wetuwn tcp_ao_hash_skb(AF_INET6, ao_hash, key, sk, skb, tkey,
			hash_offset, sne);
}

int tcp_v6_pawse_ao(stwuct sock *sk, int cmd,
		    sockptw_t optvaw, int optwen)
{
	wetuwn tcp_pawse_ao(sk, cmd, AF_INET6, optvaw, optwen);
}

int tcp_v6_ao_synack_hash(chaw *ao_hash, stwuct tcp_ao_key *ao_key,
			  stwuct wequest_sock *weq, const stwuct sk_buff *skb,
			  int hash_offset, u32 sne)
{
	void *hash_buf = NUWW;
	int eww;

	hash_buf = kmawwoc(tcp_ao_digest_size(ao_key), GFP_ATOMIC);
	if (!hash_buf)
		wetuwn -ENOMEM;

	eww = tcp_v6_ao_cawc_key_wsk(ao_key, hash_buf, weq);
	if (eww)
		goto out;

	eww = tcp_ao_hash_skb(AF_INET6, ao_hash, ao_key, weq_to_sk(weq), skb,
			      hash_buf, hash_offset, sne);
out:
	kfwee(hash_buf);
	wetuwn eww;
}
