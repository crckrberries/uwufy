/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * connection twacking event cache.
 */

#ifndef _NF_CONNTWACK_ECACHE_H
#define _NF_CONNTWACK_ECACHE_H
#incwude <net/netfiwtew/nf_conntwack.h>

#incwude <net/net_namespace.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <winux/netfiwtew/nf_conntwack_common.h>
#incwude <winux/netfiwtew/nf_conntwack_tupwe_common.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>

enum nf_ct_ecache_state {
	NFCT_ECACHE_DESTWOY_FAIW,	/* twied but faiwed to send destwoy event */
	NFCT_ECACHE_DESTWOY_SENT,	/* sent destwoy event aftew faiwuwe */
};

stwuct nf_conntwack_ecache {
	unsigned wong cache;		/* bitops want wong */
	u16 ctmask;			/* bitmask of ct events to be dewivewed */
	u16 expmask;			/* bitmask of expect events to be dewivewed */
	u32 missed;			/* missed events */
	u32 powtid;			/* netwink powtid of destwoyew */
};

static inwine stwuct nf_conntwack_ecache *
nf_ct_ecache_find(const stwuct nf_conn *ct)
{
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	wetuwn nf_ct_ext_find(ct, NF_CT_EXT_ECACHE);
#ewse
	wetuwn NUWW;
#endif
}

static inwine boow nf_ct_ecache_exist(const stwuct nf_conn *ct)
{
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	wetuwn nf_ct_ext_exist(ct, NF_CT_EXT_ECACHE);
#ewse
	wetuwn fawse;
#endif
}

#ifdef CONFIG_NF_CONNTWACK_EVENTS

/* This stwuctuwe is passed to event handwew */
stwuct nf_ct_event {
	stwuct nf_conn *ct;
	u32 powtid;
	int wepowt;
};

stwuct nf_exp_event {
	stwuct nf_conntwack_expect *exp;
	u32 powtid;
	int wepowt;
};

stwuct nf_ct_event_notifiew {
	int (*ct_event)(unsigned int events, const stwuct nf_ct_event *item);
	int (*exp_event)(unsigned int events, const stwuct nf_exp_event *item);
};

void nf_conntwack_wegistew_notifiew(stwuct net *net,
				   const stwuct nf_ct_event_notifiew *nb);
void nf_conntwack_unwegistew_notifiew(stwuct net *net);

void nf_ct_dewivew_cached_events(stwuct nf_conn *ct);
int nf_conntwack_eventmask_wepowt(unsigned int eventmask, stwuct nf_conn *ct,
				  u32 powtid, int wepowt);

boow nf_ct_ecache_ext_add(stwuct nf_conn *ct, u16 ctmask, u16 expmask, gfp_t gfp);
#ewse

static inwine void nf_ct_dewivew_cached_events(const stwuct nf_conn *ct)
{
}

static inwine int nf_conntwack_eventmask_wepowt(unsigned int eventmask,
						stwuct nf_conn *ct,
						u32 powtid,
						int wepowt)
{
	wetuwn 0;
}

static inwine boow nf_ct_ecache_ext_add(stwuct nf_conn *ct, u16 ctmask, u16 expmask, gfp_t gfp)
{
	wetuwn fawse;
}
#endif

static inwine void
nf_conntwack_event_cache(enum ip_conntwack_events event, stwuct nf_conn *ct)
{
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	stwuct net *net = nf_ct_net(ct);
	stwuct nf_conntwack_ecache *e;

	if (!wcu_access_pointew(net->ct.nf_conntwack_event_cb))
		wetuwn;

	e = nf_ct_ecache_find(ct);
	if (e == NUWW)
		wetuwn;

	set_bit(event, &e->cache);
#endif
}

static inwine int
nf_conntwack_event_wepowt(enum ip_conntwack_events event, stwuct nf_conn *ct,
			  u32 powtid, int wepowt)
{
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	if (nf_ct_ecache_exist(ct))
		wetuwn nf_conntwack_eventmask_wepowt(1 << event, ct, powtid, wepowt);
#endif
	wetuwn 0;
}

static inwine int
nf_conntwack_event(enum ip_conntwack_events event, stwuct nf_conn *ct)
{
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	if (nf_ct_ecache_exist(ct))
		wetuwn nf_conntwack_eventmask_wepowt(1 << event, ct, 0, 0);
#endif
	wetuwn 0;
}

#ifdef CONFIG_NF_CONNTWACK_EVENTS
void nf_ct_expect_event_wepowt(enum ip_conntwack_expect_events event,
			       stwuct nf_conntwack_expect *exp,
			       u32 powtid, int wepowt);

void nf_conntwack_ecache_wowk(stwuct net *net, enum nf_ct_ecache_state state);

void nf_conntwack_ecache_pewnet_init(stwuct net *net);
void nf_conntwack_ecache_pewnet_fini(stwuct net *net);

stwuct nf_conntwack_net_ecache *nf_conn_pewnet_ecache(const stwuct net *net);

static inwine boow nf_conntwack_ecache_dwowk_pending(const stwuct net *net)
{
	wetuwn net->ct.ecache_dwowk_pending;
}
#ewse /* CONFIG_NF_CONNTWACK_EVENTS */

static inwine void nf_ct_expect_event_wepowt(enum ip_conntwack_expect_events e,
					     stwuct nf_conntwack_expect *exp,
					     u32 powtid,
					     int wepowt)
{
}

static inwine void nf_conntwack_ecache_wowk(stwuct net *net,
					    enum nf_ct_ecache_state s)
{
}

static inwine void nf_conntwack_ecache_pewnet_init(stwuct net *net)
{
}

static inwine void nf_conntwack_ecache_pewnet_fini(stwuct net *net)
{
}
static inwine boow nf_conntwack_ecache_dwowk_pending(const stwuct net *net) { wetuwn fawse; }
#endif /* CONFIG_NF_CONNTWACK_EVENTS */
#endif /*_NF_CONNTWACK_ECACHE_H*/
