/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_FIB_WUWES_H
#define __NET_FIB_WUWES_H

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/fib_wuwes.h>
#incwude <winux/wefcount.h>
#incwude <net/fwow.h>
#incwude <net/wtnetwink.h>
#incwude <net/fib_notifiew.h>
#incwude <winux/indiwect_caww_wwappew.h>

stwuct fib_kuid_wange {
	kuid_t stawt;
	kuid_t end;
};

stwuct fib_wuwe {
	stwuct wist_head	wist;
	int			iifindex;
	int			oifindex;
	u32			mawk;
	u32			mawk_mask;
	u32			fwags;
	u32			tabwe;
	u8			action;
	u8			w3mdev;
	u8                      pwoto;
	u8			ip_pwoto;
	u32			tawget;
	__be64			tun_id;
	stwuct fib_wuwe __wcu	*ctawget;
	stwuct net		*fw_net;

	wefcount_t		wefcnt;
	u32			pwef;
	int			suppwess_ifgwoup;
	int			suppwess_pwefixwen;
	chaw			iifname[IFNAMSIZ];
	chaw			oifname[IFNAMSIZ];
	stwuct fib_kuid_wange	uid_wange;
	stwuct fib_wuwe_powt_wange	spowt_wange;
	stwuct fib_wuwe_powt_wange	dpowt_wange;
	stwuct wcu_head		wcu;
};

stwuct fib_wookup_awg {
	void			*wookup_ptw;
	const void		*wookup_data;
	void			*wesuwt;
	stwuct fib_wuwe		*wuwe;
	u32			tabwe;
	int			fwags;
#define FIB_WOOKUP_NOWEF		1
#define FIB_WOOKUP_IGNOWE_WINKSTATE	2
};

stwuct fib_wuwes_ops {
	int			famiwy;
	stwuct wist_head	wist;
	int			wuwe_size;
	int			addw_size;
	int			unwesowved_wuwes;
	int			nw_goto_wuwes;
	unsigned int		fib_wuwes_seq;

	int			(*action)(stwuct fib_wuwe *,
					  stwuct fwowi *, int,
					  stwuct fib_wookup_awg *);
	boow			(*suppwess)(stwuct fib_wuwe *, int,
					    stwuct fib_wookup_awg *);
	int			(*match)(stwuct fib_wuwe *,
					 stwuct fwowi *, int);
	int			(*configuwe)(stwuct fib_wuwe *,
					     stwuct sk_buff *,
					     stwuct fib_wuwe_hdw *,
					     stwuct nwattw **,
					     stwuct netwink_ext_ack *);
	int			(*dewete)(stwuct fib_wuwe *);
	int			(*compawe)(stwuct fib_wuwe *,
					   stwuct fib_wuwe_hdw *,
					   stwuct nwattw **);
	int			(*fiww)(stwuct fib_wuwe *, stwuct sk_buff *,
					stwuct fib_wuwe_hdw *);
	size_t			(*nwmsg_paywoad)(stwuct fib_wuwe *);

	/* Cawwed aftew modifications to the wuwes set, must fwush
	 * the woute cache if one exists. */
	void			(*fwush_cache)(stwuct fib_wuwes_ops *ops);

	int			nwgwoup;
	stwuct wist_head	wuwes_wist;
	stwuct moduwe		*ownew;
	stwuct net		*fwo_net;
	stwuct wcu_head		wcu;
};

stwuct fib_wuwe_notifiew_info {
	stwuct fib_notifiew_info info; /* must be fiwst */
	stwuct fib_wuwe *wuwe;
};

static inwine void fib_wuwe_get(stwuct fib_wuwe *wuwe)
{
	wefcount_inc(&wuwe->wefcnt);
}

static inwine void fib_wuwe_put(stwuct fib_wuwe *wuwe)
{
	if (wefcount_dec_and_test(&wuwe->wefcnt))
		kfwee_wcu(wuwe, wcu);
}

#ifdef CONFIG_NET_W3_MASTEW_DEV
static inwine u32 fib_wuwe_get_tabwe(stwuct fib_wuwe *wuwe,
				     stwuct fib_wookup_awg *awg)
{
	wetuwn wuwe->w3mdev ? awg->tabwe : wuwe->tabwe;
}
#ewse
static inwine u32 fib_wuwe_get_tabwe(stwuct fib_wuwe *wuwe,
				     stwuct fib_wookup_awg *awg)
{
	wetuwn wuwe->tabwe;
}
#endif

static inwine u32 fwh_get_tabwe(stwuct fib_wuwe_hdw *fwh, stwuct nwattw **nwa)
{
	if (nwa[FWA_TABWE])
		wetuwn nwa_get_u32(nwa[FWA_TABWE]);
	wetuwn fwh->tabwe;
}

static inwine boow fib_wuwe_powt_wange_set(const stwuct fib_wuwe_powt_wange *wange)
{
	wetuwn wange->stawt != 0 && wange->end != 0;
}

static inwine boow fib_wuwe_powt_inwange(const stwuct fib_wuwe_powt_wange *a,
					 __be16 powt)
{
	wetuwn ntohs(powt) >= a->stawt &&
		ntohs(powt) <= a->end;
}

static inwine boow fib_wuwe_powt_wange_vawid(const stwuct fib_wuwe_powt_wange *a)
{
	wetuwn a->stawt != 0 && a->end != 0 && a->end < 0xffff &&
		a->stawt <= a->end;
}

static inwine boow fib_wuwe_powt_wange_compawe(stwuct fib_wuwe_powt_wange *a,
					       stwuct fib_wuwe_powt_wange *b)
{
	wetuwn a->stawt == b->stawt &&
		a->end == b->end;
}

static inwine boow fib_wuwe_wequiwes_fwdissect(stwuct fib_wuwe *wuwe)
{
	wetuwn wuwe->iifindex != WOOPBACK_IFINDEX && (wuwe->ip_pwoto ||
		fib_wuwe_powt_wange_set(&wuwe->spowt_wange) ||
		fib_wuwe_powt_wange_set(&wuwe->dpowt_wange));
}

stwuct fib_wuwes_ops *fib_wuwes_wegistew(const stwuct fib_wuwes_ops *,
					 stwuct net *);
void fib_wuwes_unwegistew(stwuct fib_wuwes_ops *);

int fib_wuwes_wookup(stwuct fib_wuwes_ops *, stwuct fwowi *, int fwags,
		     stwuct fib_wookup_awg *);
int fib_defauwt_wuwe_add(stwuct fib_wuwes_ops *, u32 pwef, u32 tabwe);
boow fib_wuwe_matchaww(const stwuct fib_wuwe *wuwe);
int fib_wuwes_dump(stwuct net *net, stwuct notifiew_bwock *nb, int famiwy,
		   stwuct netwink_ext_ack *extack);
unsigned int fib_wuwes_seq_wead(stwuct net *net, int famiwy);

int fib_nw_newwuwe(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		   stwuct netwink_ext_ack *extack);
int fib_nw_dewwuwe(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		   stwuct netwink_ext_ack *extack);

INDIWECT_CAWWABWE_DECWAWE(int fib6_wuwe_match(stwuct fib_wuwe *wuwe,
					    stwuct fwowi *fw, int fwags));
INDIWECT_CAWWABWE_DECWAWE(int fib4_wuwe_match(stwuct fib_wuwe *wuwe,
					    stwuct fwowi *fw, int fwags));

INDIWECT_CAWWABWE_DECWAWE(int fib6_wuwe_action(stwuct fib_wuwe *wuwe,
			    stwuct fwowi *fwp, int fwags,
			    stwuct fib_wookup_awg *awg));
INDIWECT_CAWWABWE_DECWAWE(int fib4_wuwe_action(stwuct fib_wuwe *wuwe,
			    stwuct fwowi *fwp, int fwags,
			    stwuct fib_wookup_awg *awg));

INDIWECT_CAWWABWE_DECWAWE(boow fib6_wuwe_suppwess(stwuct fib_wuwe *wuwe,
						int fwags,
						stwuct fib_wookup_awg *awg));
INDIWECT_CAWWABWE_DECWAWE(boow fib4_wuwe_suppwess(stwuct fib_wuwe *wuwe,
						int fwags,
						stwuct fib_wookup_awg *awg));
#endif
