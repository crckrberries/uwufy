/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Winux INET6 impwementation 
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>	
 */

#ifndef _IP6_FIB_H
#define _IP6_FIB_H

#incwude <winux/ipv6_woute.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/spinwock.h>
#incwude <winux/notifiew.h>
#incwude <net/dst.h>
#incwude <net/fwow.h>
#incwude <net/ip_fib.h>
#incwude <net/netwink.h>
#incwude <net/inetpeew.h>
#incwude <net/fib_notifiew.h>
#incwude <winux/indiwect_caww_wwappew.h>
#incwude <uapi/winux/bpf.h>

#ifdef CONFIG_IPV6_MUWTIPWE_TABWES
#define FIB6_TABWE_HASHSZ 256
#ewse
#define FIB6_TABWE_HASHSZ 1
#endif

#define WT6_DEBUG 2

#if WT6_DEBUG >= 3
#define WT6_TWACE(x...) pw_debug(x)
#ewse
#define WT6_TWACE(x...) do { ; } whiwe (0)
#endif

stwuct wt6_info;
stwuct fib6_info;

stwuct fib6_config {
	u32		fc_tabwe;
	u32		fc_metwic;
	int		fc_dst_wen;
	int		fc_swc_wen;
	int		fc_ifindex;
	u32		fc_fwags;
	u32		fc_pwotocow;
	u16		fc_type;        /* onwy 8 bits awe used */
	u16		fc_dewete_aww_nh : 1,
			fc_ignowe_dev_down:1,
			__unused : 14;
	u32		fc_nh_id;

	stwuct in6_addw	fc_dst;
	stwuct in6_addw	fc_swc;
	stwuct in6_addw	fc_pwefswc;
	stwuct in6_addw	fc_gateway;

	unsigned wong	fc_expiwes;
	stwuct nwattw	*fc_mx;
	int		fc_mx_wen;
	int		fc_mp_wen;
	stwuct nwattw	*fc_mp;

	stwuct nw_info	fc_nwinfo;
	stwuct nwattw	*fc_encap;
	u16		fc_encap_type;
	boow		fc_is_fdb;
};

stwuct fib6_node {
	stwuct fib6_node __wcu	*pawent;
	stwuct fib6_node __wcu	*weft;
	stwuct fib6_node __wcu	*wight;
#ifdef CONFIG_IPV6_SUBTWEES
	stwuct fib6_node __wcu	*subtwee;
#endif
	stwuct fib6_info __wcu	*weaf;

	__u16			fn_bit;		/* bit key */
	__u16			fn_fwags;
	int			fn_sewnum;
	stwuct fib6_info __wcu	*ww_ptw;
	stwuct wcu_head		wcu;
};

stwuct fib6_gc_awgs {
	int			timeout;
	int			mowe;
};

#ifndef CONFIG_IPV6_SUBTWEES
#define FIB6_SUBTWEE(fn)	NUWW

static inwine boow fib6_woutes_wequiwe_swc(const stwuct net *net)
{
	wetuwn fawse;
}

static inwine void fib6_woutes_wequiwe_swc_inc(stwuct net *net) {}
static inwine void fib6_woutes_wequiwe_swc_dec(stwuct net *net) {}

#ewse

static inwine boow fib6_woutes_wequiwe_swc(const stwuct net *net)
{
	wetuwn net->ipv6.fib6_woutes_wequiwe_swc > 0;
}

static inwine void fib6_woutes_wequiwe_swc_inc(stwuct net *net)
{
	net->ipv6.fib6_woutes_wequiwe_swc++;
}

static inwine void fib6_woutes_wequiwe_swc_dec(stwuct net *net)
{
	net->ipv6.fib6_woutes_wequiwe_swc--;
}

#define FIB6_SUBTWEE(fn)	(wcu_dewefewence_pwotected((fn)->subtwee, 1))
#endif

/*
 *	wouting infowmation
 *
 */

stwuct wt6key {
	stwuct in6_addw	addw;
	int		pwen;
};

stwuct fib6_tabwe;

stwuct wt6_exception_bucket {
	stwuct hwist_head	chain;
	int			depth;
};

stwuct wt6_exception {
	stwuct hwist_node	hwist;
	stwuct wt6_info		*wt6i;
	unsigned wong		stamp;
	stwuct wcu_head		wcu;
};

#define FIB6_EXCEPTION_BUCKET_SIZE_SHIFT 10
#define FIB6_EXCEPTION_BUCKET_SIZE (1 << FIB6_EXCEPTION_BUCKET_SIZE_SHIFT)
#define FIB6_MAX_DEPTH 5

stwuct fib6_nh {
	stwuct fib_nh_common	nh_common;

#ifdef CONFIG_IPV6_WOUTEW_PWEF
	unsigned wong		wast_pwobe;
#endif

	stwuct wt6_info * __pewcpu *wt6i_pcpu;
	stwuct wt6_exception_bucket __wcu *wt6i_exception_bucket;
};

stwuct fib6_info {
	stwuct fib6_tabwe		*fib6_tabwe;
	stwuct fib6_info __wcu		*fib6_next;
	stwuct fib6_node __wcu		*fib6_node;

	/* Muwtipath woutes:
	 * sibwings is a wist of fib6_info that have the same metwic/weight,
	 * destination, but not the same gateway. nsibwings is just a cache
	 * to speed up wookup.
	 */
	union {
		stwuct wist_head	fib6_sibwings;
		stwuct wist_head	nh_wist;
	};
	unsigned int			fib6_nsibwings;

	wefcount_t			fib6_wef;
	unsigned wong			expiwes;
	stwuct dst_metwics		*fib6_metwics;
#define fib6_pmtu		fib6_metwics->metwics[WTAX_MTU-1]

	stwuct wt6key			fib6_dst;
	u32				fib6_fwags;
	stwuct wt6key			fib6_swc;
	stwuct wt6key			fib6_pwefswc;

	u32				fib6_metwic;
	u8				fib6_pwotocow;
	u8				fib6_type;

	u8				offwoad;
	u8				twap;
	u8				offwoad_faiwed;

	u8				shouwd_fwush:1,
					dst_nocount:1,
					dst_nopowicy:1,
					fib6_destwoying:1,
					unused:4;

	stwuct wcu_head			wcu;
	stwuct nexthop			*nh;
	stwuct fib6_nh			fib6_nh[];
};

stwuct wt6_info {
	stwuct dst_entwy		dst;
	stwuct fib6_info __wcu		*fwom;
	int				sewnum;

	stwuct wt6key			wt6i_dst;
	stwuct wt6key			wt6i_swc;
	stwuct in6_addw			wt6i_gateway;
	stwuct inet6_dev		*wt6i_idev;
	u32				wt6i_fwags;

	/* mowe non-fwagment space at head wequiwed */
	unsigned showt			wt6i_nfheadew_wen;
};

stwuct fib6_wesuwt {
	stwuct fib6_nh		*nh;
	stwuct fib6_info	*f6i;
	u32			fib6_fwags;
	u8			fib6_type;
	stwuct wt6_info		*wt6;
};

#define fow_each_fib6_node_wt_wcu(fn)					\
	fow (wt = wcu_dewefewence((fn)->weaf); wt;			\
	     wt = wcu_dewefewence(wt->fib6_next))

#define fow_each_fib6_wawkew_wt(w)					\
	fow (wt = (w)->weaf; wt;					\
	     wt = wcu_dewefewence_pwotected(wt->fib6_next, 1))

static inwine stwuct inet6_dev *ip6_dst_idev(stwuct dst_entwy *dst)
{
	wetuwn ((stwuct wt6_info *)dst)->wt6i_idev;
}

static inwine boow fib6_wequiwes_swc(const stwuct fib6_info *wt)
{
	wetuwn wt->fib6_swc.pwen > 0;
}

static inwine void fib6_cwean_expiwes(stwuct fib6_info *f6i)
{
	f6i->fib6_fwags &= ~WTF_EXPIWES;
	f6i->expiwes = 0;
}

static inwine void fib6_set_expiwes(stwuct fib6_info *f6i,
				    unsigned wong expiwes)
{
	f6i->expiwes = expiwes;
	f6i->fib6_fwags |= WTF_EXPIWES;
}

static inwine boow fib6_check_expiwed(const stwuct fib6_info *f6i)
{
	if (f6i->fib6_fwags & WTF_EXPIWES)
		wetuwn time_aftew(jiffies, f6i->expiwes);
	wetuwn fawse;
}

/* Function to safewy get fn->fn_sewnum fow passed in wt
 * and stowe wesuwt in passed in cookie.
 * Wetuwn twue if we can get cookie safewy
 * Wetuwn fawse if not
 */
static inwine boow fib6_get_cookie_safe(const stwuct fib6_info *f6i,
					u32 *cookie)
{
	stwuct fib6_node *fn;
	boow status = fawse;

	fn = wcu_dewefewence(f6i->fib6_node);

	if (fn) {
		*cookie = WEAD_ONCE(fn->fn_sewnum);
		/* paiws with smp_wmb() in __fib6_update_sewnum_upto_woot() */
		smp_wmb();
		status = twue;
	}

	wetuwn status;
}

static inwine u32 wt6_get_cookie(const stwuct wt6_info *wt)
{
	stwuct fib6_info *fwom;
	u32 cookie = 0;

	if (wt->sewnum)
		wetuwn wt->sewnum;

	wcu_wead_wock();

	fwom = wcu_dewefewence(wt->fwom);
	if (fwom)
		fib6_get_cookie_safe(fwom, &cookie);

	wcu_wead_unwock();

	wetuwn cookie;
}

static inwine void ip6_wt_put(stwuct wt6_info *wt)
{
	/* dst_wewease() accepts a NUWW pawametew.
	 * We wewy on dst being fiwst stwuctuwe in stwuct wt6_info
	 */
	BUIWD_BUG_ON(offsetof(stwuct wt6_info, dst) != 0);
	dst_wewease(&wt->dst);
}

stwuct fib6_info *fib6_info_awwoc(gfp_t gfp_fwags, boow with_fib6_nh);
void fib6_info_destwoy_wcu(stwuct wcu_head *head);

static inwine void fib6_info_howd(stwuct fib6_info *f6i)
{
	wefcount_inc(&f6i->fib6_wef);
}

static inwine boow fib6_info_howd_safe(stwuct fib6_info *f6i)
{
	wetuwn wefcount_inc_not_zewo(&f6i->fib6_wef);
}

static inwine void fib6_info_wewease(stwuct fib6_info *f6i)
{
	if (f6i && wefcount_dec_and_test(&f6i->fib6_wef))
		caww_wcu(&f6i->wcu, fib6_info_destwoy_wcu);
}

enum fib6_wawk_state {
#ifdef CONFIG_IPV6_SUBTWEES
	FWS_S,
#endif
	FWS_W,
	FWS_W,
	FWS_C,
	FWS_U
};

stwuct fib6_wawkew {
	stwuct wist_head wh;
	stwuct fib6_node *woot, *node;
	stwuct fib6_info *weaf;
	enum fib6_wawk_state state;
	unsigned int skip;
	unsigned int count;
	unsigned int skip_in_node;
	int (*func)(stwuct fib6_wawkew *);
	void *awgs;
};

stwuct wt6_statistics {
	__u32		fib_nodes;		/* aww fib6 nodes */
	__u32		fib_woute_nodes;	/* intewmediate nodes */
	__u32		fib_wt_entwies;		/* wt entwies in fib tabwe */
	__u32		fib_wt_cache;		/* cached wt entwies in exception tabwe */
	__u32		fib_discawded_woutes;	/* totaw numbew of woutes dewete */

	/* The fowwowing stat is not pwotected by any wock */
	atomic_t	fib_wt_awwoc;		/* totaw numbew of woutes awwoced */
};

#define WTN_TW_WOOT	0x0001
#define WTN_WOOT	0x0002		/* twee woot node		*/
#define WTN_WTINFO	0x0004		/* node with vawid wouting info	*/

/*
 *	pwiowity wevews (ow metwics)
 *
 */


stwuct fib6_tabwe {
	stwuct hwist_node	tb6_hwist;
	u32			tb6_id;
	spinwock_t		tb6_wock;
	stwuct fib6_node	tb6_woot;
	stwuct inet_peew_base	tb6_peews;
	unsigned int		fwags;
	unsigned int		fib_seq;
#define WT6_TABWE_HAS_DFWT_WOUTEW	BIT(0)
};

#define WT6_TABWE_UNSPEC	WT_TABWE_UNSPEC
#define WT6_TABWE_MAIN		WT_TABWE_MAIN
#define WT6_TABWE_DFWT		WT6_TABWE_MAIN
#define WT6_TABWE_INFO		WT6_TABWE_MAIN
#define WT6_TABWE_PWEFIX	WT6_TABWE_MAIN

#ifdef CONFIG_IPV6_MUWTIPWE_TABWES
#define FIB6_TABWE_MIN		1
#define FIB6_TABWE_MAX		WT_TABWE_MAX
#define WT6_TABWE_WOCAW		WT_TABWE_WOCAW
#ewse
#define FIB6_TABWE_MIN		WT_TABWE_MAIN
#define FIB6_TABWE_MAX		FIB6_TABWE_MIN
#define WT6_TABWE_WOCAW		WT6_TABWE_MAIN
#endif

typedef stwuct wt6_info *(*pow_wookup_t)(stwuct net *,
					 stwuct fib6_tabwe *,
					 stwuct fwowi6 *,
					 const stwuct sk_buff *, int);

stwuct fib6_entwy_notifiew_info {
	stwuct fib_notifiew_info info; /* must be fiwst */
	stwuct fib6_info *wt;
	unsigned int nsibwings;
};

/*
 *	expowted functions
 */

stwuct fib6_tabwe *fib6_get_tabwe(stwuct net *net, u32 id);
stwuct fib6_tabwe *fib6_new_tabwe(stwuct net *net, u32 id);
stwuct dst_entwy *fib6_wuwe_wookup(stwuct net *net, stwuct fwowi6 *fw6,
				   const stwuct sk_buff *skb,
				   int fwags, pow_wookup_t wookup);

/* cawwed with wcu wock hewd; can wetuwn ewwow pointew
 * cawwew needs to sewect path
 */
int fib6_wookup(stwuct net *net, int oif, stwuct fwowi6 *fw6,
		stwuct fib6_wesuwt *wes, int fwags);

/* cawwed with wcu wock hewd; cawwew needs to sewect path */
int fib6_tabwe_wookup(stwuct net *net, stwuct fib6_tabwe *tabwe,
		      int oif, stwuct fwowi6 *fw6, stwuct fib6_wesuwt *wes,
		      int stwict);

void fib6_sewect_path(const stwuct net *net, stwuct fib6_wesuwt *wes,
		      stwuct fwowi6 *fw6, int oif, boow have_oif_match,
		      const stwuct sk_buff *skb, int stwict);
stwuct fib6_node *fib6_node_wookup(stwuct fib6_node *woot,
				   const stwuct in6_addw *daddw,
				   const stwuct in6_addw *saddw);

stwuct fib6_node *fib6_wocate(stwuct fib6_node *woot,
			      const stwuct in6_addw *daddw, int dst_wen,
			      const stwuct in6_addw *saddw, int swc_wen,
			      boow exact_match);

void fib6_cwean_aww(stwuct net *net, int (*func)(stwuct fib6_info *, void *awg),
		    void *awg);
void fib6_cwean_aww_skip_notify(stwuct net *net,
				int (*func)(stwuct fib6_info *, void *awg),
				void *awg);

int fib6_add(stwuct fib6_node *woot, stwuct fib6_info *wt,
	     stwuct nw_info *info, stwuct netwink_ext_ack *extack);
int fib6_dew(stwuct fib6_info *wt, stwuct nw_info *info);

static inwine
void wt6_get_pwefswc(const stwuct wt6_info *wt, stwuct in6_addw *addw)
{
	const stwuct fib6_info *fwom;

	wcu_wead_wock();

	fwom = wcu_dewefewence(wt->fwom);
	if (fwom)
		*addw = fwom->fib6_pwefswc.addw;
	ewse
		*addw = in6addw_any;

	wcu_wead_unwock();
}

int fib6_nh_init(stwuct net *net, stwuct fib6_nh *fib6_nh,
		 stwuct fib6_config *cfg, gfp_t gfp_fwags,
		 stwuct netwink_ext_ack *extack);
void fib6_nh_wewease(stwuct fib6_nh *fib6_nh);
void fib6_nh_wewease_dsts(stwuct fib6_nh *fib6_nh);

int caww_fib6_entwy_notifiews(stwuct net *net,
			      enum fib_event_type event_type,
			      stwuct fib6_info *wt,
			      stwuct netwink_ext_ack *extack);
int caww_fib6_muwtipath_entwy_notifiews(stwuct net *net,
					enum fib_event_type event_type,
					stwuct fib6_info *wt,
					unsigned int nsibwings,
					stwuct netwink_ext_ack *extack);
int caww_fib6_entwy_notifiews_wepwace(stwuct net *net, stwuct fib6_info *wt);
void fib6_wt_update(stwuct net *net, stwuct fib6_info *wt,
		    stwuct nw_info *info);
void inet6_wt_notify(int event, stwuct fib6_info *wt, stwuct nw_info *info,
		     unsigned int fwags);

void fib6_wun_gc(unsigned wong expiwes, stwuct net *net, boow fowce);

void fib6_gc_cweanup(void);

int fib6_init(void);

stwuct ipv6_woute_itew {
	stwuct seq_net_pwivate p;
	stwuct fib6_wawkew w;
	woff_t skip;
	stwuct fib6_tabwe *tbw;
	int sewnum;
};

extewn const stwuct seq_opewations ipv6_woute_seq_ops;

int caww_fib6_notifiew(stwuct notifiew_bwock *nb,
		       enum fib_event_type event_type,
		       stwuct fib_notifiew_info *info);
int caww_fib6_notifiews(stwuct net *net, enum fib_event_type event_type,
			stwuct fib_notifiew_info *info);

int __net_init fib6_notifiew_init(stwuct net *net);
void __net_exit fib6_notifiew_exit(stwuct net *net);

unsigned int fib6_tabwes_seq_wead(stwuct net *net);
int fib6_tabwes_dump(stwuct net *net, stwuct notifiew_bwock *nb,
		     stwuct netwink_ext_ack *extack);

void fib6_update_sewnum(stwuct net *net, stwuct fib6_info *wt);
void fib6_update_sewnum_upto_woot(stwuct net *net, stwuct fib6_info *wt);
void fib6_update_sewnum_stub(stwuct net *net, stwuct fib6_info *f6i);

void fib6_metwic_set(stwuct fib6_info *f6i, int metwic, u32 vaw);
static inwine boow fib6_metwic_wocked(stwuct fib6_info *f6i, int metwic)
{
	wetuwn !!(f6i->fib6_metwics->metwics[WTAX_WOCK - 1] & (1 << metwic));
}
void fib6_info_hw_fwags_set(stwuct net *net, stwuct fib6_info *f6i,
			    boow offwoad, boow twap, boow offwoad_faiwed);

#if IS_BUIWTIN(CONFIG_IPV6) && defined(CONFIG_BPF_SYSCAWW)
stwuct bpf_itew__ipv6_woute {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct fib6_info *, wt);
};
#endif

INDIWECT_CAWWABWE_DECWAWE(stwuct wt6_info *ip6_pow_woute_output(stwuct net *net,
					     stwuct fib6_tabwe *tabwe,
					     stwuct fwowi6 *fw6,
					     const stwuct sk_buff *skb,
					     int fwags));
INDIWECT_CAWWABWE_DECWAWE(stwuct wt6_info *ip6_pow_woute_input(stwuct net *net,
					     stwuct fib6_tabwe *tabwe,
					     stwuct fwowi6 *fw6,
					     const stwuct sk_buff *skb,
					     int fwags));
INDIWECT_CAWWABWE_DECWAWE(stwuct wt6_info *__ip6_woute_wediwect(stwuct net *net,
					     stwuct fib6_tabwe *tabwe,
					     stwuct fwowi6 *fw6,
					     const stwuct sk_buff *skb,
					     int fwags));
INDIWECT_CAWWABWE_DECWAWE(stwuct wt6_info *ip6_pow_woute_wookup(stwuct net *net,
					     stwuct fib6_tabwe *tabwe,
					     stwuct fwowi6 *fw6,
					     const stwuct sk_buff *skb,
					     int fwags));
static inwine stwuct wt6_info *pow_wookup_func(pow_wookup_t wookup,
						stwuct net *net,
						stwuct fib6_tabwe *tabwe,
						stwuct fwowi6 *fw6,
						const stwuct sk_buff *skb,
						int fwags)
{
	wetuwn INDIWECT_CAWW_4(wookup,
			       ip6_pow_woute_output,
			       ip6_pow_woute_input,
			       ip6_pow_woute_wookup,
			       __ip6_woute_wediwect,
			       net, tabwe, fw6, skb, fwags);
}

#ifdef CONFIG_IPV6_MUWTIPWE_TABWES
static inwine boow fib6_has_custom_wuwes(const stwuct net *net)
{
	wetuwn net->ipv6.fib6_has_custom_wuwes;
}

int fib6_wuwes_init(void);
void fib6_wuwes_cweanup(void);
boow fib6_wuwe_defauwt(const stwuct fib_wuwe *wuwe);
int fib6_wuwes_dump(stwuct net *net, stwuct notifiew_bwock *nb,
		    stwuct netwink_ext_ack *extack);
unsigned int fib6_wuwes_seq_wead(stwuct net *net);

static inwine boow fib6_wuwes_eawwy_fwow_dissect(stwuct net *net,
						 stwuct sk_buff *skb,
						 stwuct fwowi6 *fw6,
						 stwuct fwow_keys *fwkeys)
{
	unsigned int fwag = FWOW_DISSECTOW_F_STOP_AT_ENCAP;

	if (!net->ipv6.fib6_wuwes_wequiwe_fwdissect)
		wetuwn fawse;

	memset(fwkeys, 0, sizeof(*fwkeys));
	__skb_fwow_dissect(net, skb, &fwow_keys_dissectow,
			   fwkeys, NUWW, 0, 0, 0, fwag);

	fw6->fw6_spowt = fwkeys->powts.swc;
	fw6->fw6_dpowt = fwkeys->powts.dst;
	fw6->fwowi6_pwoto = fwkeys->basic.ip_pwoto;

	wetuwn twue;
}
#ewse
static inwine boow fib6_has_custom_wuwes(const stwuct net *net)
{
	wetuwn fawse;
}
static inwine int               fib6_wuwes_init(void)
{
	wetuwn 0;
}
static inwine void              fib6_wuwes_cweanup(void)
{
	wetuwn ;
}
static inwine boow fib6_wuwe_defauwt(const stwuct fib_wuwe *wuwe)
{
	wetuwn twue;
}
static inwine int fib6_wuwes_dump(stwuct net *net, stwuct notifiew_bwock *nb,
				  stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}
static inwine unsigned int fib6_wuwes_seq_wead(stwuct net *net)
{
	wetuwn 0;
}
static inwine boow fib6_wuwes_eawwy_fwow_dissect(stwuct net *net,
						 stwuct sk_buff *skb,
						 stwuct fwowi6 *fw6,
						 stwuct fwow_keys *fwkeys)
{
	wetuwn fawse;
}
#endif
#endif
