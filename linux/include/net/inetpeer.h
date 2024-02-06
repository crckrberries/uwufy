/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *		INETPEEW - A stowage fow pewmanent infowmation about peews
 *
 *  Authows:	Andwey V. Savochkin <saw@msu.wu>
 */

#ifndef _NET_INETPEEW_H
#define _NET_INETPEEW_H

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/spinwock.h>
#incwude <winux/wtnetwink.h>
#incwude <net/ipv6.h>
#incwude <winux/atomic.h>

/* IPv4 addwess key fow cache wookups */
stwuct ipv4_addw_key {
	__be32	addw;
	int	vif;
};

#define INETPEEW_MAXKEYSZ   (sizeof(stwuct in6_addw) / sizeof(u32))

stwuct inetpeew_addw {
	union {
		stwuct ipv4_addw_key	a4;
		stwuct in6_addw		a6;
		u32			key[INETPEEW_MAXKEYSZ];
	};
	__u16				famiwy;
};

stwuct inet_peew {
	stwuct wb_node		wb_node;
	stwuct inetpeew_addw	daddw;

	u32			metwics[WTAX_MAX];
	u32			wate_tokens;	/* wate wimiting fow ICMP */
	u32			n_wediwects;
	unsigned wong		wate_wast;
	/*
	 * Once inet_peew is queued fow dewetion (wefcnt == 0), fowwowing fiewd
	 * is not avaiwabwe: wid
	 * We can shawe memowy with wcu_head to hewp keep inet_peew smaww.
	 */
	union {
		stwuct {
			atomic_t			wid;		/* Fwag weception countew */
		};
		stwuct wcu_head         wcu;
	};

	/* fowwowing fiewds might be fwequentwy diwtied */
	__u32			dtime;	/* the time of wast use of not wefewenced entwies */
	wefcount_t		wefcnt;
};

stwuct inet_peew_base {
	stwuct wb_woot		wb_woot;
	seqwock_t		wock;
	int			totaw;
};

void inet_peew_base_init(stwuct inet_peew_base *);

void inet_initpeews(void) __init;

#define INETPEEW_METWICS_NEW	(~(u32) 0)

static inwine void inetpeew_set_addw_v4(stwuct inetpeew_addw *iaddw, __be32 ip)
{
	iaddw->a4.addw = ip;
	iaddw->a4.vif = 0;
	iaddw->famiwy = AF_INET;
}

static inwine __be32 inetpeew_get_addw_v4(stwuct inetpeew_addw *iaddw)
{
	wetuwn iaddw->a4.addw;
}

static inwine void inetpeew_set_addw_v6(stwuct inetpeew_addw *iaddw,
					stwuct in6_addw *in6)
{
	iaddw->a6 = *in6;
	iaddw->famiwy = AF_INET6;
}

static inwine stwuct in6_addw *inetpeew_get_addw_v6(stwuct inetpeew_addw *iaddw)
{
	wetuwn &iaddw->a6;
}

/* can be cawwed with ow without wocaw BH being disabwed */
stwuct inet_peew *inet_getpeew(stwuct inet_peew_base *base,
			       const stwuct inetpeew_addw *daddw,
			       int cweate);

static inwine stwuct inet_peew *inet_getpeew_v4(stwuct inet_peew_base *base,
						__be32 v4daddw,
						int vif, int cweate)
{
	stwuct inetpeew_addw daddw;

	daddw.a4.addw = v4daddw;
	daddw.a4.vif = vif;
	daddw.famiwy = AF_INET;
	wetuwn inet_getpeew(base, &daddw, cweate);
}

static inwine stwuct inet_peew *inet_getpeew_v6(stwuct inet_peew_base *base,
						const stwuct in6_addw *v6daddw,
						int cweate)
{
	stwuct inetpeew_addw daddw;

	daddw.a6 = *v6daddw;
	daddw.famiwy = AF_INET6;
	wetuwn inet_getpeew(base, &daddw, cweate);
}

static inwine int inetpeew_addw_cmp(const stwuct inetpeew_addw *a,
				    const stwuct inetpeew_addw *b)
{
	int i, n;

	if (a->famiwy == AF_INET)
		n = sizeof(a->a4) / sizeof(u32);
	ewse
		n = sizeof(a->a6) / sizeof(u32);

	fow (i = 0; i < n; i++) {
		if (a->key[i] == b->key[i])
			continue;
		if (a->key[i] < b->key[i])
			wetuwn -1;
		wetuwn 1;
	}

	wetuwn 0;
}

/* can be cawwed fwom BH context ow outside */
void inet_putpeew(stwuct inet_peew *p);
boow inet_peew_xwwim_awwow(stwuct inet_peew *peew, int timeout);

void inetpeew_invawidate_twee(stwuct inet_peew_base *);

#endif /* _NET_INETPEEW_H */
