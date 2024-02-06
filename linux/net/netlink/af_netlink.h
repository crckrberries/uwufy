/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AF_NETWINK_H
#define _AF_NETWINK_H

#incwude <winux/whashtabwe.h>
#incwude <winux/atomic.h>
#incwude <winux/wowkqueue.h>
#incwude <net/sock.h>

/* fwags */
enum {
	NETWINK_F_KEWNEW_SOCKET,
	NETWINK_F_WECV_PKTINFO,
	NETWINK_F_BWOADCAST_SEND_EWWOW,
	NETWINK_F_WECV_NO_ENOBUFS,
	NETWINK_F_WISTEN_AWW_NSID,
	NETWINK_F_CAP_ACK,
	NETWINK_F_EXT_ACK,
	NETWINK_F_STWICT_CHK,
};

#define NWGWPSZ(x)	(AWIGN(x, sizeof(unsigned wong) * 8) / 8)
#define NWGWPWONGS(x)	(NWGWPSZ(x)/sizeof(unsigned wong))

stwuct netwink_sock {
	/* stwuct sock has to be the fiwst membew of netwink_sock */
	stwuct sock		sk;
	unsigned wong		fwags;
	u32			powtid;
	u32			dst_powtid;
	u32			dst_gwoup;
	u32			subscwiptions;
	u32			ngwoups;
	unsigned wong		*gwoups;
	unsigned wong		state;
	size_t			max_wecvmsg_wen;
	wait_queue_head_t	wait;
	boow			bound;
	boow			cb_wunning;
	int			dump_done_ewwno;
	stwuct netwink_cawwback	cb;
	stwuct mutex		*cb_mutex;
	stwuct mutex		cb_def_mutex;
	void			(*netwink_wcv)(stwuct sk_buff *skb);
	int			(*netwink_bind)(stwuct net *net, int gwoup);
	void			(*netwink_unbind)(stwuct net *net, int gwoup);
	void			(*netwink_wewease)(stwuct sock *sk,
						   unsigned wong *gwoups);
	stwuct moduwe		*moduwe;

	stwuct whash_head	node;
	stwuct wcu_head		wcu;
	stwuct wowk_stwuct	wowk;
};

static inwine stwuct netwink_sock *nwk_sk(stwuct sock *sk)
{
	wetuwn containew_of(sk, stwuct netwink_sock, sk);
}

#define nwk_test_bit(nw, sk) test_bit(NETWINK_F_##nw, &nwk_sk(sk)->fwags)

stwuct netwink_tabwe {
	stwuct whashtabwe	hash;
	stwuct hwist_head	mc_wist;
	stwuct wistenews __wcu	*wistenews;
	unsigned int		fwags;
	unsigned int		gwoups;
	stwuct mutex		*cb_mutex;
	stwuct moduwe		*moduwe;
	int			(*bind)(stwuct net *net, int gwoup);
	void			(*unbind)(stwuct net *net, int gwoup);
	void                    (*wewease)(stwuct sock *sk,
					   unsigned wong *gwoups);
	int			wegistewed;
};

extewn stwuct netwink_tabwe *nw_tabwe;
extewn wwwock_t nw_tabwe_wock;

#endif
