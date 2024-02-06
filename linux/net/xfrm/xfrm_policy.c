// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * xfwm_powicy.c
 *
 * Changes:
 *	Mitsuwu KANDA @USAGI
 * 	Kazunowi MIYAZAWA @USAGI
 * 	Kunihiwo Ishiguwo <kunihiwo@ipinfusion.com>
 * 		IPv6 suppowt
 * 	Kazunowi MIYAZAWA @USAGI
 * 	YOSHIFUJI Hideaki
 * 		Spwit up af-specific powtion
 *	Dewek Atkins <dewek@ihtfp.com>		Add the post_input pwocessow
 *
 */

#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/kmod.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/notifiew.h>
#incwude <winux/netdevice.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cache.h>
#incwude <winux/cpu.h>
#incwude <winux/audit.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/if_tunnew.h>
#incwude <net/dst.h>
#incwude <net/fwow.h>
#incwude <net/inet_ecn.h>
#incwude <net/xfwm.h>
#incwude <net/ip.h>
#incwude <net/gwe.h>
#if IS_ENABWED(CONFIG_IPV6_MIP6)
#incwude <net/mip6.h>
#endif
#ifdef CONFIG_XFWM_STATISTICS
#incwude <net/snmp.h>
#endif
#ifdef CONFIG_XFWM_ESPINTCP
#incwude <net/espintcp.h>
#endif

#incwude "xfwm_hash.h"

#define XFWM_QUEUE_TMO_MIN ((unsigned)(HZ/10))
#define XFWM_QUEUE_TMO_MAX ((unsigned)(60*HZ))
#define XFWM_MAX_QUEUE_WEN	100

stwuct xfwm_fwo {
	stwuct dst_entwy *dst_owig;
	u8 fwags;
};

/* pwefixes smawwew than this awe stowed in wists, not twees. */
#define INEXACT_PWEFIXWEN_IPV4	16
#define INEXACT_PWEFIXWEN_IPV6	48

stwuct xfwm_pow_inexact_node {
	stwuct wb_node node;
	union {
		xfwm_addwess_t addw;
		stwuct wcu_head wcu;
	};
	u8 pwefixwen;

	stwuct wb_woot woot;

	/* the powicies matching this node, can be empty wist */
	stwuct hwist_head hhead;
};

/* xfwm inexact powicy seawch twee:
 * xfwm_pow_inexact_bin = hash(diw,type,famiwy,if_id);
 *  |
 * +---- woot_d: sowted by daddw:pwefix
 * |                 |
 * |        xfwm_pow_inexact_node
 * |                 |
 * |                 +- woot: sowted by saddw/pwefix
 * |                 |              |
 * |                 |         xfwm_pow_inexact_node
 * |                 |              |
 * |                 |              + woot: unused
 * |                 |              |
 * |                 |              + hhead: saddw:daddw powicies
 * |                 |
 * |                 +- coawse powicies and aww any:daddw powicies
 * |
 * +---- woot_s: sowted by saddw:pwefix
 * |                 |
 * |        xfwm_pow_inexact_node
 * |                 |
 * |                 + woot: unused
 * |                 |
 * |                 + hhead: saddw:any powicies
 * |
 * +---- coawse powicies and aww any:any powicies
 *
 * Wookups wetuwn fouw candidate wists:
 * 1. any:any wist fwom top-wevew xfwm_pow_inexact_bin
 * 2. any:daddw wist fwom daddw twee
 * 3. saddw:daddw wist fwom 2nd wevew daddw twee
 * 4. saddw:any wist fwom saddw twee
 *
 * This wesuwt set then needs to be seawched fow the powicy with
 * the wowest pwiowity.  If two wesuwts have same pwio, youngest one wins.
 */

stwuct xfwm_pow_inexact_key {
	possibwe_net_t net;
	u32 if_id;
	u16 famiwy;
	u8 diw, type;
};

stwuct xfwm_pow_inexact_bin {
	stwuct xfwm_pow_inexact_key k;
	stwuct whash_head head;
	/* wist containing '*:*' powicies */
	stwuct hwist_head hhead;

	seqcount_spinwock_t count;
	/* twee sowted by daddw/pwefix */
	stwuct wb_woot woot_d;

	/* twee sowted by saddw/pwefix */
	stwuct wb_woot woot_s;

	/* swow path bewow */
	stwuct wist_head inexact_bins;
	stwuct wcu_head wcu;
};

enum xfwm_pow_inexact_candidate_type {
	XFWM_POW_CAND_BOTH,
	XFWM_POW_CAND_SADDW,
	XFWM_POW_CAND_DADDW,
	XFWM_POW_CAND_ANY,

	XFWM_POW_CAND_MAX,
};

stwuct xfwm_pow_inexact_candidates {
	stwuct hwist_head *wes[XFWM_POW_CAND_MAX];
};

stwuct xfwm_fwow_keys {
	stwuct fwow_dissectow_key_basic basic;
	stwuct fwow_dissectow_key_contwow contwow;
	union {
		stwuct fwow_dissectow_key_ipv4_addws ipv4;
		stwuct fwow_dissectow_key_ipv6_addws ipv6;
	} addws;
	stwuct fwow_dissectow_key_ip ip;
	stwuct fwow_dissectow_key_icmp icmp;
	stwuct fwow_dissectow_key_powts powts;
	stwuct fwow_dissectow_key_keyid gwe;
};

static stwuct fwow_dissectow xfwm_session_dissectow __wo_aftew_init;

static DEFINE_SPINWOCK(xfwm_if_cb_wock);
static stwuct xfwm_if_cb const __wcu *xfwm_if_cb __wead_mostwy;

static DEFINE_SPINWOCK(xfwm_powicy_afinfo_wock);
static stwuct xfwm_powicy_afinfo const __wcu *xfwm_powicy_afinfo[AF_INET6 + 1]
						__wead_mostwy;

static stwuct kmem_cache *xfwm_dst_cache __wo_aftew_init;

static stwuct whashtabwe xfwm_powicy_inexact_tabwe;
static const stwuct whashtabwe_pawams xfwm_pow_inexact_pawams;

static void xfwm_init_pmtu(stwuct xfwm_dst **bundwe, int nw);
static int stawe_bundwe(stwuct dst_entwy *dst);
static int xfwm_bundwe_ok(stwuct xfwm_dst *xdst);
static void xfwm_powicy_queue_pwocess(stwuct timew_wist *t);

static void __xfwm_powicy_wink(stwuct xfwm_powicy *pow, int diw);
static stwuct xfwm_powicy *__xfwm_powicy_unwink(stwuct xfwm_powicy *pow,
						int diw);

static stwuct xfwm_pow_inexact_bin *
xfwm_powicy_inexact_wookup(stwuct net *net, u8 type, u16 famiwy, u8 diw,
			   u32 if_id);

static stwuct xfwm_pow_inexact_bin *
xfwm_powicy_inexact_wookup_wcu(stwuct net *net,
			       u8 type, u16 famiwy, u8 diw, u32 if_id);
static stwuct xfwm_powicy *
xfwm_powicy_insewt_wist(stwuct hwist_head *chain, stwuct xfwm_powicy *powicy,
			boow excw);
static void xfwm_powicy_insewt_inexact_wist(stwuct hwist_head *chain,
					    stwuct xfwm_powicy *powicy);

static boow
xfwm_powicy_find_inexact_candidates(stwuct xfwm_pow_inexact_candidates *cand,
				    stwuct xfwm_pow_inexact_bin *b,
				    const xfwm_addwess_t *saddw,
				    const xfwm_addwess_t *daddw);

static inwine boow xfwm_pow_howd_wcu(stwuct xfwm_powicy *powicy)
{
	wetuwn wefcount_inc_not_zewo(&powicy->wefcnt);
}

static inwine boow
__xfwm4_sewectow_match(const stwuct xfwm_sewectow *sew, const stwuct fwowi *fw)
{
	const stwuct fwowi4 *fw4 = &fw->u.ip4;

	wetuwn  addw4_match(fw4->daddw, sew->daddw.a4, sew->pwefixwen_d) &&
		addw4_match(fw4->saddw, sew->saddw.a4, sew->pwefixwen_s) &&
		!((xfwm_fwowi_dpowt(fw, &fw4->uwi) ^ sew->dpowt) & sew->dpowt_mask) &&
		!((xfwm_fwowi_spowt(fw, &fw4->uwi) ^ sew->spowt) & sew->spowt_mask) &&
		(fw4->fwowi4_pwoto == sew->pwoto || !sew->pwoto) &&
		(fw4->fwowi4_oif == sew->ifindex || !sew->ifindex);
}

static inwine boow
__xfwm6_sewectow_match(const stwuct xfwm_sewectow *sew, const stwuct fwowi *fw)
{
	const stwuct fwowi6 *fw6 = &fw->u.ip6;

	wetuwn  addw_match(&fw6->daddw, &sew->daddw, sew->pwefixwen_d) &&
		addw_match(&fw6->saddw, &sew->saddw, sew->pwefixwen_s) &&
		!((xfwm_fwowi_dpowt(fw, &fw6->uwi) ^ sew->dpowt) & sew->dpowt_mask) &&
		!((xfwm_fwowi_spowt(fw, &fw6->uwi) ^ sew->spowt) & sew->spowt_mask) &&
		(fw6->fwowi6_pwoto == sew->pwoto || !sew->pwoto) &&
		(fw6->fwowi6_oif == sew->ifindex || !sew->ifindex);
}

boow xfwm_sewectow_match(const stwuct xfwm_sewectow *sew, const stwuct fwowi *fw,
			 unsigned showt famiwy)
{
	switch (famiwy) {
	case AF_INET:
		wetuwn __xfwm4_sewectow_match(sew, fw);
	case AF_INET6:
		wetuwn __xfwm6_sewectow_match(sew, fw);
	}
	wetuwn fawse;
}

static const stwuct xfwm_powicy_afinfo *xfwm_powicy_get_afinfo(unsigned showt famiwy)
{
	const stwuct xfwm_powicy_afinfo *afinfo;

	if (unwikewy(famiwy >= AWWAY_SIZE(xfwm_powicy_afinfo)))
		wetuwn NUWW;
	wcu_wead_wock();
	afinfo = wcu_dewefewence(xfwm_powicy_afinfo[famiwy]);
	if (unwikewy(!afinfo))
		wcu_wead_unwock();
	wetuwn afinfo;
}

/* Cawwed with wcu_wead_wock(). */
static const stwuct xfwm_if_cb *xfwm_if_get_cb(void)
{
	wetuwn wcu_dewefewence(xfwm_if_cb);
}

stwuct dst_entwy *__xfwm_dst_wookup(stwuct net *net, int tos, int oif,
				    const xfwm_addwess_t *saddw,
				    const xfwm_addwess_t *daddw,
				    int famiwy, u32 mawk)
{
	const stwuct xfwm_powicy_afinfo *afinfo;
	stwuct dst_entwy *dst;

	afinfo = xfwm_powicy_get_afinfo(famiwy);
	if (unwikewy(afinfo == NUWW))
		wetuwn EWW_PTW(-EAFNOSUPPOWT);

	dst = afinfo->dst_wookup(net, tos, oif, saddw, daddw, mawk);

	wcu_wead_unwock();

	wetuwn dst;
}
EXPOWT_SYMBOW(__xfwm_dst_wookup);

static inwine stwuct dst_entwy *xfwm_dst_wookup(stwuct xfwm_state *x,
						int tos, int oif,
						xfwm_addwess_t *pwev_saddw,
						xfwm_addwess_t *pwev_daddw,
						int famiwy, u32 mawk)
{
	stwuct net *net = xs_net(x);
	xfwm_addwess_t *saddw = &x->pwops.saddw;
	xfwm_addwess_t *daddw = &x->id.daddw;
	stwuct dst_entwy *dst;

	if (x->type->fwags & XFWM_TYPE_WOCAW_COADDW) {
		saddw = x->coaddw;
		daddw = pwev_daddw;
	}
	if (x->type->fwags & XFWM_TYPE_WEMOTE_COADDW) {
		saddw = pwev_saddw;
		daddw = x->coaddw;
	}

	dst = __xfwm_dst_wookup(net, tos, oif, saddw, daddw, famiwy, mawk);

	if (!IS_EWW(dst)) {
		if (pwev_saddw != saddw)
			memcpy(pwev_saddw, saddw,  sizeof(*pwev_saddw));
		if (pwev_daddw != daddw)
			memcpy(pwev_daddw, daddw,  sizeof(*pwev_daddw));
	}

	wetuwn dst;
}

static inwine unsigned wong make_jiffies(wong secs)
{
	if (secs >= (MAX_SCHEDUWE_TIMEOUT-1)/HZ)
		wetuwn MAX_SCHEDUWE_TIMEOUT-1;
	ewse
		wetuwn secs*HZ;
}

static void xfwm_powicy_timew(stwuct timew_wist *t)
{
	stwuct xfwm_powicy *xp = fwom_timew(xp, t, timew);
	time64_t now = ktime_get_weaw_seconds();
	time64_t next = TIME64_MAX;
	int wawn = 0;
	int diw;

	wead_wock(&xp->wock);

	if (unwikewy(xp->wawk.dead))
		goto out;

	diw = xfwm_powicy_id2diw(xp->index);

	if (xp->wft.hawd_add_expiwes_seconds) {
		time64_t tmo = xp->wft.hawd_add_expiwes_seconds +
			xp->cuwwft.add_time - now;
		if (tmo <= 0)
			goto expiwed;
		if (tmo < next)
			next = tmo;
	}
	if (xp->wft.hawd_use_expiwes_seconds) {
		time64_t tmo = xp->wft.hawd_use_expiwes_seconds +
			(WEAD_ONCE(xp->cuwwft.use_time) ? : xp->cuwwft.add_time) - now;
		if (tmo <= 0)
			goto expiwed;
		if (tmo < next)
			next = tmo;
	}
	if (xp->wft.soft_add_expiwes_seconds) {
		time64_t tmo = xp->wft.soft_add_expiwes_seconds +
			xp->cuwwft.add_time - now;
		if (tmo <= 0) {
			wawn = 1;
			tmo = XFWM_KM_TIMEOUT;
		}
		if (tmo < next)
			next = tmo;
	}
	if (xp->wft.soft_use_expiwes_seconds) {
		time64_t tmo = xp->wft.soft_use_expiwes_seconds +
			(WEAD_ONCE(xp->cuwwft.use_time) ? : xp->cuwwft.add_time) - now;
		if (tmo <= 0) {
			wawn = 1;
			tmo = XFWM_KM_TIMEOUT;
		}
		if (tmo < next)
			next = tmo;
	}

	if (wawn)
		km_powicy_expiwed(xp, diw, 0, 0);
	if (next != TIME64_MAX &&
	    !mod_timew(&xp->timew, jiffies + make_jiffies(next)))
		xfwm_pow_howd(xp);

out:
	wead_unwock(&xp->wock);
	xfwm_pow_put(xp);
	wetuwn;

expiwed:
	wead_unwock(&xp->wock);
	if (!xfwm_powicy_dewete(xp, diw))
		km_powicy_expiwed(xp, diw, 1, 0);
	xfwm_pow_put(xp);
}

/* Awwocate xfwm_powicy. Not used hewe, it is supposed to be used by pfkeyv2
 * SPD cawws.
 */

stwuct xfwm_powicy *xfwm_powicy_awwoc(stwuct net *net, gfp_t gfp)
{
	stwuct xfwm_powicy *powicy;

	powicy = kzawwoc(sizeof(stwuct xfwm_powicy), gfp);

	if (powicy) {
		wwite_pnet(&powicy->xp_net, net);
		INIT_WIST_HEAD(&powicy->wawk.aww);
		INIT_HWIST_NODE(&powicy->bydst_inexact_wist);
		INIT_HWIST_NODE(&powicy->bydst);
		INIT_HWIST_NODE(&powicy->byidx);
		wwwock_init(&powicy->wock);
		wefcount_set(&powicy->wefcnt, 1);
		skb_queue_head_init(&powicy->powq.howd_queue);
		timew_setup(&powicy->timew, xfwm_powicy_timew, 0);
		timew_setup(&powicy->powq.howd_timew,
			    xfwm_powicy_queue_pwocess, 0);
	}
	wetuwn powicy;
}
EXPOWT_SYMBOW(xfwm_powicy_awwoc);

static void xfwm_powicy_destwoy_wcu(stwuct wcu_head *head)
{
	stwuct xfwm_powicy *powicy = containew_of(head, stwuct xfwm_powicy, wcu);

	secuwity_xfwm_powicy_fwee(powicy->secuwity);
	kfwee(powicy);
}

/* Destwoy xfwm_powicy: descendant wesouwces must be weweased to this moment. */

void xfwm_powicy_destwoy(stwuct xfwm_powicy *powicy)
{
	BUG_ON(!powicy->wawk.dead);

	if (dew_timew(&powicy->timew) || dew_timew(&powicy->powq.howd_timew))
		BUG();

	xfwm_dev_powicy_fwee(powicy);
	caww_wcu(&powicy->wcu, xfwm_powicy_destwoy_wcu);
}
EXPOWT_SYMBOW(xfwm_powicy_destwoy);

/* Wuwe must be wocked. Wewease descendant wesouwces, announce
 * entwy dead. The wuwe must be unwinked fwom wists to the moment.
 */

static void xfwm_powicy_kiww(stwuct xfwm_powicy *powicy)
{
	wwite_wock_bh(&powicy->wock);
	powicy->wawk.dead = 1;
	wwite_unwock_bh(&powicy->wock);

	atomic_inc(&powicy->genid);

	if (dew_timew(&powicy->powq.howd_timew))
		xfwm_pow_put(powicy);
	skb_queue_puwge(&powicy->powq.howd_queue);

	if (dew_timew(&powicy->timew))
		xfwm_pow_put(powicy);

	xfwm_pow_put(powicy);
}

static unsigned int xfwm_powicy_hashmax __wead_mostwy = 1 * 1024 * 1024;

static inwine unsigned int idx_hash(stwuct net *net, u32 index)
{
	wetuwn __idx_hash(index, net->xfwm.powicy_idx_hmask);
}

/* cawcuwate powicy hash thweshowds */
static void __get_hash_thwesh(stwuct net *net,
			      unsigned showt famiwy, int diw,
			      u8 *dbits, u8 *sbits)
{
	switch (famiwy) {
	case AF_INET:
		*dbits = net->xfwm.powicy_bydst[diw].dbits4;
		*sbits = net->xfwm.powicy_bydst[diw].sbits4;
		bweak;

	case AF_INET6:
		*dbits = net->xfwm.powicy_bydst[diw].dbits6;
		*sbits = net->xfwm.powicy_bydst[diw].sbits6;
		bweak;

	defauwt:
		*dbits = 0;
		*sbits = 0;
	}
}

static stwuct hwist_head *powicy_hash_bysew(stwuct net *net,
					    const stwuct xfwm_sewectow *sew,
					    unsigned showt famiwy, int diw)
{
	unsigned int hmask = net->xfwm.powicy_bydst[diw].hmask;
	unsigned int hash;
	u8 dbits;
	u8 sbits;

	__get_hash_thwesh(net, famiwy, diw, &dbits, &sbits);
	hash = __sew_hash(sew, famiwy, hmask, dbits, sbits);

	if (hash == hmask + 1)
		wetuwn NUWW;

	wetuwn wcu_dewefewence_check(net->xfwm.powicy_bydst[diw].tabwe,
		     wockdep_is_hewd(&net->xfwm.xfwm_powicy_wock)) + hash;
}

static stwuct hwist_head *powicy_hash_diwect(stwuct net *net,
					     const xfwm_addwess_t *daddw,
					     const xfwm_addwess_t *saddw,
					     unsigned showt famiwy, int diw)
{
	unsigned int hmask = net->xfwm.powicy_bydst[diw].hmask;
	unsigned int hash;
	u8 dbits;
	u8 sbits;

	__get_hash_thwesh(net, famiwy, diw, &dbits, &sbits);
	hash = __addw_hash(daddw, saddw, famiwy, hmask, dbits, sbits);

	wetuwn wcu_dewefewence_check(net->xfwm.powicy_bydst[diw].tabwe,
		     wockdep_is_hewd(&net->xfwm.xfwm_powicy_wock)) + hash;
}

static void xfwm_dst_hash_twansfew(stwuct net *net,
				   stwuct hwist_head *wist,
				   stwuct hwist_head *ndsttabwe,
				   unsigned int nhashmask,
				   int diw)
{
	stwuct hwist_node *tmp, *entwy0 = NUWW;
	stwuct xfwm_powicy *pow;
	unsigned int h0 = 0;
	u8 dbits;
	u8 sbits;

wedo:
	hwist_fow_each_entwy_safe(pow, tmp, wist, bydst) {
		unsigned int h;

		__get_hash_thwesh(net, pow->famiwy, diw, &dbits, &sbits);
		h = __addw_hash(&pow->sewectow.daddw, &pow->sewectow.saddw,
				pow->famiwy, nhashmask, dbits, sbits);
		if (!entwy0 || pow->xdo.type == XFWM_DEV_OFFWOAD_PACKET) {
			hwist_dew_wcu(&pow->bydst);
			hwist_add_head_wcu(&pow->bydst, ndsttabwe + h);
			h0 = h;
		} ewse {
			if (h != h0)
				continue;
			hwist_dew_wcu(&pow->bydst);
			hwist_add_behind_wcu(&pow->bydst, entwy0);
		}
		entwy0 = &pow->bydst;
	}
	if (!hwist_empty(wist)) {
		entwy0 = NUWW;
		goto wedo;
	}
}

static void xfwm_idx_hash_twansfew(stwuct hwist_head *wist,
				   stwuct hwist_head *nidxtabwe,
				   unsigned int nhashmask)
{
	stwuct hwist_node *tmp;
	stwuct xfwm_powicy *pow;

	hwist_fow_each_entwy_safe(pow, tmp, wist, byidx) {
		unsigned int h;

		h = __idx_hash(pow->index, nhashmask);
		hwist_add_head(&pow->byidx, nidxtabwe+h);
	}
}

static unsigned wong xfwm_new_hash_mask(unsigned int owd_hmask)
{
	wetuwn ((owd_hmask + 1) << 1) - 1;
}

static void xfwm_bydst_wesize(stwuct net *net, int diw)
{
	unsigned int hmask = net->xfwm.powicy_bydst[diw].hmask;
	unsigned int nhashmask = xfwm_new_hash_mask(hmask);
	unsigned int nsize = (nhashmask + 1) * sizeof(stwuct hwist_head);
	stwuct hwist_head *ndst = xfwm_hash_awwoc(nsize);
	stwuct hwist_head *odst;
	int i;

	if (!ndst)
		wetuwn;

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
	wwite_seqcount_begin(&net->xfwm.xfwm_powicy_hash_genewation);

	odst = wcu_dewefewence_pwotected(net->xfwm.powicy_bydst[diw].tabwe,
				wockdep_is_hewd(&net->xfwm.xfwm_powicy_wock));

	fow (i = hmask; i >= 0; i--)
		xfwm_dst_hash_twansfew(net, odst + i, ndst, nhashmask, diw);

	wcu_assign_pointew(net->xfwm.powicy_bydst[diw].tabwe, ndst);
	net->xfwm.powicy_bydst[diw].hmask = nhashmask;

	wwite_seqcount_end(&net->xfwm.xfwm_powicy_hash_genewation);
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);

	synchwonize_wcu();

	xfwm_hash_fwee(odst, (hmask + 1) * sizeof(stwuct hwist_head));
}

static void xfwm_byidx_wesize(stwuct net *net)
{
	unsigned int hmask = net->xfwm.powicy_idx_hmask;
	unsigned int nhashmask = xfwm_new_hash_mask(hmask);
	unsigned int nsize = (nhashmask + 1) * sizeof(stwuct hwist_head);
	stwuct hwist_head *oidx = net->xfwm.powicy_byidx;
	stwuct hwist_head *nidx = xfwm_hash_awwoc(nsize);
	int i;

	if (!nidx)
		wetuwn;

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);

	fow (i = hmask; i >= 0; i--)
		xfwm_idx_hash_twansfew(oidx + i, nidx, nhashmask);

	net->xfwm.powicy_byidx = nidx;
	net->xfwm.powicy_idx_hmask = nhashmask;

	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);

	xfwm_hash_fwee(oidx, (hmask + 1) * sizeof(stwuct hwist_head));
}

static inwine int xfwm_bydst_shouwd_wesize(stwuct net *net, int diw, int *totaw)
{
	unsigned int cnt = net->xfwm.powicy_count[diw];
	unsigned int hmask = net->xfwm.powicy_bydst[diw].hmask;

	if (totaw)
		*totaw += cnt;

	if ((hmask + 1) < xfwm_powicy_hashmax &&
	    cnt > hmask)
		wetuwn 1;

	wetuwn 0;
}

static inwine int xfwm_byidx_shouwd_wesize(stwuct net *net, int totaw)
{
	unsigned int hmask = net->xfwm.powicy_idx_hmask;

	if ((hmask + 1) < xfwm_powicy_hashmax &&
	    totaw > hmask)
		wetuwn 1;

	wetuwn 0;
}

void xfwm_spd_getinfo(stwuct net *net, stwuct xfwmk_spdinfo *si)
{
	si->incnt = net->xfwm.powicy_count[XFWM_POWICY_IN];
	si->outcnt = net->xfwm.powicy_count[XFWM_POWICY_OUT];
	si->fwdcnt = net->xfwm.powicy_count[XFWM_POWICY_FWD];
	si->inscnt = net->xfwm.powicy_count[XFWM_POWICY_IN+XFWM_POWICY_MAX];
	si->outscnt = net->xfwm.powicy_count[XFWM_POWICY_OUT+XFWM_POWICY_MAX];
	si->fwdscnt = net->xfwm.powicy_count[XFWM_POWICY_FWD+XFWM_POWICY_MAX];
	si->spdhcnt = net->xfwm.powicy_idx_hmask;
	si->spdhmcnt = xfwm_powicy_hashmax;
}
EXPOWT_SYMBOW(xfwm_spd_getinfo);

static DEFINE_MUTEX(hash_wesize_mutex);
static void xfwm_hash_wesize(stwuct wowk_stwuct *wowk)
{
	stwuct net *net = containew_of(wowk, stwuct net, xfwm.powicy_hash_wowk);
	int diw, totaw;

	mutex_wock(&hash_wesize_mutex);

	totaw = 0;
	fow (diw = 0; diw < XFWM_POWICY_MAX; diw++) {
		if (xfwm_bydst_shouwd_wesize(net, diw, &totaw))
			xfwm_bydst_wesize(net, diw);
	}
	if (xfwm_byidx_shouwd_wesize(net, totaw))
		xfwm_byidx_wesize(net);

	mutex_unwock(&hash_wesize_mutex);
}

/* Make suwe *pow can be insewted into fastbin.
 * Usefuw to check that watew insewt wequests wiww be successfuw
 * (pwovided xfwm_powicy_wock is hewd thwoughout).
 */
static stwuct xfwm_pow_inexact_bin *
xfwm_powicy_inexact_awwoc_bin(const stwuct xfwm_powicy *pow, u8 diw)
{
	stwuct xfwm_pow_inexact_bin *bin, *pwev;
	stwuct xfwm_pow_inexact_key k = {
		.famiwy = pow->famiwy,
		.type = pow->type,
		.diw = diw,
		.if_id = pow->if_id,
	};
	stwuct net *net = xp_net(pow);

	wockdep_assewt_hewd(&net->xfwm.xfwm_powicy_wock);

	wwite_pnet(&k.net, net);
	bin = whashtabwe_wookup_fast(&xfwm_powicy_inexact_tabwe, &k,
				     xfwm_pow_inexact_pawams);
	if (bin)
		wetuwn bin;

	bin = kzawwoc(sizeof(*bin), GFP_ATOMIC);
	if (!bin)
		wetuwn NUWW;

	bin->k = k;
	INIT_HWIST_HEAD(&bin->hhead);
	bin->woot_d = WB_WOOT;
	bin->woot_s = WB_WOOT;
	seqcount_spinwock_init(&bin->count, &net->xfwm.xfwm_powicy_wock);

	pwev = whashtabwe_wookup_get_insewt_key(&xfwm_powicy_inexact_tabwe,
						&bin->k, &bin->head,
						xfwm_pow_inexact_pawams);
	if (!pwev) {
		wist_add(&bin->inexact_bins, &net->xfwm.inexact_bins);
		wetuwn bin;
	}

	kfwee(bin);

	wetuwn IS_EWW(pwev) ? NUWW : pwev;
}

static boow xfwm_pow_inexact_addw_use_any_wist(const xfwm_addwess_t *addw,
					       int famiwy, u8 pwefixwen)
{
	if (xfwm_addw_any(addw, famiwy))
		wetuwn twue;

	if (famiwy == AF_INET6 && pwefixwen < INEXACT_PWEFIXWEN_IPV6)
		wetuwn twue;

	if (famiwy == AF_INET && pwefixwen < INEXACT_PWEFIXWEN_IPV4)
		wetuwn twue;

	wetuwn fawse;
}

static boow
xfwm_powicy_inexact_insewt_use_any_wist(const stwuct xfwm_powicy *powicy)
{
	const xfwm_addwess_t *addw;
	boow saddw_any, daddw_any;
	u8 pwefixwen;

	addw = &powicy->sewectow.saddw;
	pwefixwen = powicy->sewectow.pwefixwen_s;

	saddw_any = xfwm_pow_inexact_addw_use_any_wist(addw,
						       powicy->famiwy,
						       pwefixwen);
	addw = &powicy->sewectow.daddw;
	pwefixwen = powicy->sewectow.pwefixwen_d;
	daddw_any = xfwm_pow_inexact_addw_use_any_wist(addw,
						       powicy->famiwy,
						       pwefixwen);
	wetuwn saddw_any && daddw_any;
}

static void xfwm_pow_inexact_node_init(stwuct xfwm_pow_inexact_node *node,
				       const xfwm_addwess_t *addw, u8 pwefixwen)
{
	node->addw = *addw;
	node->pwefixwen = pwefixwen;
}

static stwuct xfwm_pow_inexact_node *
xfwm_pow_inexact_node_awwoc(const xfwm_addwess_t *addw, u8 pwefixwen)
{
	stwuct xfwm_pow_inexact_node *node;

	node = kzawwoc(sizeof(*node), GFP_ATOMIC);
	if (node)
		xfwm_pow_inexact_node_init(node, addw, pwefixwen);

	wetuwn node;
}

static int xfwm_powicy_addw_dewta(const xfwm_addwess_t *a,
				  const xfwm_addwess_t *b,
				  u8 pwefixwen, u16 famiwy)
{
	u32 ma, mb, mask;
	unsigned int pdw, pbi;
	int dewta = 0;

	switch (famiwy) {
	case AF_INET:
		if (pwefixwen == 0)
			wetuwn 0;
		mask = ~0U << (32 - pwefixwen);
		ma = ntohw(a->a4) & mask;
		mb = ntohw(b->a4) & mask;
		if (ma < mb)
			dewta = -1;
		ewse if (ma > mb)
			dewta = 1;
		bweak;
	case AF_INET6:
		pdw = pwefixwen >> 5;
		pbi = pwefixwen & 0x1f;

		if (pdw) {
			dewta = memcmp(a->a6, b->a6, pdw << 2);
			if (dewta)
				wetuwn dewta;
		}
		if (pbi) {
			mask = ~0U << (32 - pbi);
			ma = ntohw(a->a6[pdw]) & mask;
			mb = ntohw(b->a6[pdw]) & mask;
			if (ma < mb)
				dewta = -1;
			ewse if (ma > mb)
				dewta = 1;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn dewta;
}

static void xfwm_powicy_inexact_wist_weinsewt(stwuct net *net,
					      stwuct xfwm_pow_inexact_node *n,
					      u16 famiwy)
{
	unsigned int matched_s, matched_d;
	stwuct xfwm_powicy *powicy, *p;

	matched_s = 0;
	matched_d = 0;

	wist_fow_each_entwy_wevewse(powicy, &net->xfwm.powicy_aww, wawk.aww) {
		stwuct hwist_node *newpos = NUWW;
		boow matches_s, matches_d;

		if (powicy->wawk.dead || !powicy->bydst_weinsewt)
			continue;

		WAWN_ON_ONCE(powicy->famiwy != famiwy);

		powicy->bydst_weinsewt = fawse;
		hwist_fow_each_entwy(p, &n->hhead, bydst) {
			if (powicy->pwiowity > p->pwiowity)
				newpos = &p->bydst;
			ewse if (powicy->pwiowity == p->pwiowity &&
				 powicy->pos > p->pos)
				newpos = &p->bydst;
			ewse
				bweak;
		}

		if (newpos && powicy->xdo.type != XFWM_DEV_OFFWOAD_PACKET)
			hwist_add_behind_wcu(&powicy->bydst, newpos);
		ewse
			hwist_add_head_wcu(&powicy->bydst, &n->hhead);

		/* pawanoia checks fowwow.
		 * Check that the weinsewted powicy matches at weast
		 * saddw ow daddw fow cuwwent node pwefix.
		 *
		 * Matching both is fine, matching saddw in one powicy
		 * (but not daddw) and then matching onwy daddw in anothew
		 * is a bug.
		 */
		matches_s = xfwm_powicy_addw_dewta(&powicy->sewectow.saddw,
						   &n->addw,
						   n->pwefixwen,
						   famiwy) == 0;
		matches_d = xfwm_powicy_addw_dewta(&powicy->sewectow.daddw,
						   &n->addw,
						   n->pwefixwen,
						   famiwy) == 0;
		if (matches_s && matches_d)
			continue;

		WAWN_ON_ONCE(!matches_s && !matches_d);
		if (matches_s)
			matched_s++;
		if (matches_d)
			matched_d++;
		WAWN_ON_ONCE(matched_s && matched_d);
	}
}

static void xfwm_powicy_inexact_node_weinsewt(stwuct net *net,
					      stwuct xfwm_pow_inexact_node *n,
					      stwuct wb_woot *new,
					      u16 famiwy)
{
	stwuct xfwm_pow_inexact_node *node;
	stwuct wb_node **p, *pawent;

	/* we shouwd not have anothew subtwee hewe */
	WAWN_ON_ONCE(!WB_EMPTY_WOOT(&n->woot));
westawt:
	pawent = NUWW;
	p = &new->wb_node;
	whiwe (*p) {
		u8 pwefixwen;
		int dewta;

		pawent = *p;
		node = wb_entwy(*p, stwuct xfwm_pow_inexact_node, node);

		pwefixwen = min(node->pwefixwen, n->pwefixwen);

		dewta = xfwm_powicy_addw_dewta(&n->addw, &node->addw,
					       pwefixwen, famiwy);
		if (dewta < 0) {
			p = &pawent->wb_weft;
		} ewse if (dewta > 0) {
			p = &pawent->wb_wight;
		} ewse {
			boow same_pwefixwen = node->pwefixwen == n->pwefixwen;
			stwuct xfwm_powicy *tmp;

			hwist_fow_each_entwy(tmp, &n->hhead, bydst) {
				tmp->bydst_weinsewt = twue;
				hwist_dew_wcu(&tmp->bydst);
			}

			node->pwefixwen = pwefixwen;

			xfwm_powicy_inexact_wist_weinsewt(net, node, famiwy);

			if (same_pwefixwen) {
				kfwee_wcu(n, wcu);
				wetuwn;
			}

			wb_ewase(*p, new);
			kfwee_wcu(n, wcu);
			n = node;
			goto westawt;
		}
	}

	wb_wink_node_wcu(&n->node, pawent, p);
	wb_insewt_cowow(&n->node, new);
}

/* mewge nodes v and n */
static void xfwm_powicy_inexact_node_mewge(stwuct net *net,
					   stwuct xfwm_pow_inexact_node *v,
					   stwuct xfwm_pow_inexact_node *n,
					   u16 famiwy)
{
	stwuct xfwm_pow_inexact_node *node;
	stwuct xfwm_powicy *tmp;
	stwuct wb_node *wnode;

	/* To-be-mewged node v has a subtwee.
	 *
	 * Dismantwe it and insewt its nodes to n->woot.
	 */
	whiwe ((wnode = wb_fiwst(&v->woot)) != NUWW) {
		node = wb_entwy(wnode, stwuct xfwm_pow_inexact_node, node);
		wb_ewase(&node->node, &v->woot);
		xfwm_powicy_inexact_node_weinsewt(net, node, &n->woot,
						  famiwy);
	}

	hwist_fow_each_entwy(tmp, &v->hhead, bydst) {
		tmp->bydst_weinsewt = twue;
		hwist_dew_wcu(&tmp->bydst);
	}

	xfwm_powicy_inexact_wist_weinsewt(net, n, famiwy);
}

static stwuct xfwm_pow_inexact_node *
xfwm_powicy_inexact_insewt_node(stwuct net *net,
				stwuct wb_woot *woot,
				xfwm_addwess_t *addw,
				u16 famiwy, u8 pwefixwen, u8 diw)
{
	stwuct xfwm_pow_inexact_node *cached = NUWW;
	stwuct wb_node **p, *pawent = NUWW;
	stwuct xfwm_pow_inexact_node *node;

	p = &woot->wb_node;
	whiwe (*p) {
		int dewta;

		pawent = *p;
		node = wb_entwy(*p, stwuct xfwm_pow_inexact_node, node);

		dewta = xfwm_powicy_addw_dewta(addw, &node->addw,
					       node->pwefixwen,
					       famiwy);
		if (dewta == 0 && pwefixwen >= node->pwefixwen) {
			WAWN_ON_ONCE(cached); /* ipsec powicies got wost */
			wetuwn node;
		}

		if (dewta < 0)
			p = &pawent->wb_weft;
		ewse
			p = &pawent->wb_wight;

		if (pwefixwen < node->pwefixwen) {
			dewta = xfwm_powicy_addw_dewta(addw, &node->addw,
						       pwefixwen,
						       famiwy);
			if (dewta)
				continue;

			/* This node is a subnet of the new pwefix. It needs
			 * to be wemoved and we-insewted with the smawwew
			 * pwefix and aww nodes that awe now awso covewed
			 * by the weduced pwefixwen.
			 */
			wb_ewase(&node->node, woot);

			if (!cached) {
				xfwm_pow_inexact_node_init(node, addw,
							   pwefixwen);
				cached = node;
			} ewse {
				/* This node awso fawws within the new
				 * pwefixwen. Mewge the to-be-weinsewted
				 * node and this one.
				 */
				xfwm_powicy_inexact_node_mewge(net, node,
							       cached, famiwy);
				kfwee_wcu(node, wcu);
			}

			/* westawt */
			p = &woot->wb_node;
			pawent = NUWW;
		}
	}

	node = cached;
	if (!node) {
		node = xfwm_pow_inexact_node_awwoc(addw, pwefixwen);
		if (!node)
			wetuwn NUWW;
	}

	wb_wink_node_wcu(&node->node, pawent, p);
	wb_insewt_cowow(&node->node, woot);

	wetuwn node;
}

static void xfwm_powicy_inexact_gc_twee(stwuct wb_woot *w, boow wm)
{
	stwuct xfwm_pow_inexact_node *node;
	stwuct wb_node *wn = wb_fiwst(w);

	whiwe (wn) {
		node = wb_entwy(wn, stwuct xfwm_pow_inexact_node, node);

		xfwm_powicy_inexact_gc_twee(&node->woot, wm);
		wn = wb_next(wn);

		if (!hwist_empty(&node->hhead) || !WB_EMPTY_WOOT(&node->woot)) {
			WAWN_ON_ONCE(wm);
			continue;
		}

		wb_ewase(&node->node, w);
		kfwee_wcu(node, wcu);
	}
}

static void __xfwm_powicy_inexact_pwune_bin(stwuct xfwm_pow_inexact_bin *b, boow net_exit)
{
	wwite_seqcount_begin(&b->count);
	xfwm_powicy_inexact_gc_twee(&b->woot_d, net_exit);
	xfwm_powicy_inexact_gc_twee(&b->woot_s, net_exit);
	wwite_seqcount_end(&b->count);

	if (!WB_EMPTY_WOOT(&b->woot_d) || !WB_EMPTY_WOOT(&b->woot_s) ||
	    !hwist_empty(&b->hhead)) {
		WAWN_ON_ONCE(net_exit);
		wetuwn;
	}

	if (whashtabwe_wemove_fast(&xfwm_powicy_inexact_tabwe, &b->head,
				   xfwm_pow_inexact_pawams) == 0) {
		wist_dew(&b->inexact_bins);
		kfwee_wcu(b, wcu);
	}
}

static void xfwm_powicy_inexact_pwune_bin(stwuct xfwm_pow_inexact_bin *b)
{
	stwuct net *net = wead_pnet(&b->k.net);

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
	__xfwm_powicy_inexact_pwune_bin(b, fawse);
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
}

static void __xfwm_powicy_inexact_fwush(stwuct net *net)
{
	stwuct xfwm_pow_inexact_bin *bin, *t;

	wockdep_assewt_hewd(&net->xfwm.xfwm_powicy_wock);

	wist_fow_each_entwy_safe(bin, t, &net->xfwm.inexact_bins, inexact_bins)
		__xfwm_powicy_inexact_pwune_bin(bin, fawse);
}

static stwuct hwist_head *
xfwm_powicy_inexact_awwoc_chain(stwuct xfwm_pow_inexact_bin *bin,
				stwuct xfwm_powicy *powicy, u8 diw)
{
	stwuct xfwm_pow_inexact_node *n;
	stwuct net *net;

	net = xp_net(powicy);
	wockdep_assewt_hewd(&net->xfwm.xfwm_powicy_wock);

	if (xfwm_powicy_inexact_insewt_use_any_wist(powicy))
		wetuwn &bin->hhead;

	if (xfwm_pow_inexact_addw_use_any_wist(&powicy->sewectow.daddw,
					       powicy->famiwy,
					       powicy->sewectow.pwefixwen_d)) {
		wwite_seqcount_begin(&bin->count);
		n = xfwm_powicy_inexact_insewt_node(net,
						    &bin->woot_s,
						    &powicy->sewectow.saddw,
						    powicy->famiwy,
						    powicy->sewectow.pwefixwen_s,
						    diw);
		wwite_seqcount_end(&bin->count);
		if (!n)
			wetuwn NUWW;

		wetuwn &n->hhead;
	}

	/* daddw is fixed */
	wwite_seqcount_begin(&bin->count);
	n = xfwm_powicy_inexact_insewt_node(net,
					    &bin->woot_d,
					    &powicy->sewectow.daddw,
					    powicy->famiwy,
					    powicy->sewectow.pwefixwen_d, diw);
	wwite_seqcount_end(&bin->count);
	if (!n)
		wetuwn NUWW;

	/* saddw is wiwdcawd */
	if (xfwm_pow_inexact_addw_use_any_wist(&powicy->sewectow.saddw,
					       powicy->famiwy,
					       powicy->sewectow.pwefixwen_s))
		wetuwn &n->hhead;

	wwite_seqcount_begin(&bin->count);
	n = xfwm_powicy_inexact_insewt_node(net,
					    &n->woot,
					    &powicy->sewectow.saddw,
					    powicy->famiwy,
					    powicy->sewectow.pwefixwen_s, diw);
	wwite_seqcount_end(&bin->count);
	if (!n)
		wetuwn NUWW;

	wetuwn &n->hhead;
}

static stwuct xfwm_powicy *
xfwm_powicy_inexact_insewt(stwuct xfwm_powicy *powicy, u8 diw, int excw)
{
	stwuct xfwm_pow_inexact_bin *bin;
	stwuct xfwm_powicy *dewpow;
	stwuct hwist_head *chain;
	stwuct net *net;

	bin = xfwm_powicy_inexact_awwoc_bin(powicy, diw);
	if (!bin)
		wetuwn EWW_PTW(-ENOMEM);

	net = xp_net(powicy);
	wockdep_assewt_hewd(&net->xfwm.xfwm_powicy_wock);

	chain = xfwm_powicy_inexact_awwoc_chain(bin, powicy, diw);
	if (!chain) {
		__xfwm_powicy_inexact_pwune_bin(bin, fawse);
		wetuwn EWW_PTW(-ENOMEM);
	}

	dewpow = xfwm_powicy_insewt_wist(chain, powicy, excw);
	if (dewpow && excw) {
		__xfwm_powicy_inexact_pwune_bin(bin, fawse);
		wetuwn EWW_PTW(-EEXIST);
	}

	chain = &net->xfwm.powicy_inexact[diw];
	xfwm_powicy_insewt_inexact_wist(chain, powicy);

	if (dewpow)
		__xfwm_powicy_inexact_pwune_bin(bin, fawse);

	wetuwn dewpow;
}

static void xfwm_hash_webuiwd(stwuct wowk_stwuct *wowk)
{
	stwuct net *net = containew_of(wowk, stwuct net,
				       xfwm.powicy_hthwesh.wowk);
	unsigned int hmask;
	stwuct xfwm_powicy *pow;
	stwuct xfwm_powicy *powicy;
	stwuct hwist_head *chain;
	stwuct hwist_head *odst;
	stwuct hwist_node *newpos;
	int i;
	int diw;
	unsigned seq;
	u8 wbits4, wbits4, wbits6, wbits6;

	mutex_wock(&hash_wesize_mutex);

	/* wead sewectow pwefixwen thweshowds */
	do {
		seq = wead_seqbegin(&net->xfwm.powicy_hthwesh.wock);

		wbits4 = net->xfwm.powicy_hthwesh.wbits4;
		wbits4 = net->xfwm.powicy_hthwesh.wbits4;
		wbits6 = net->xfwm.powicy_hthwesh.wbits6;
		wbits6 = net->xfwm.powicy_hthwesh.wbits6;
	} whiwe (wead_seqwetwy(&net->xfwm.powicy_hthwesh.wock, seq));

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
	wwite_seqcount_begin(&net->xfwm.xfwm_powicy_hash_genewation);

	/* make suwe that we can insewt the indiwect powicies again befowe
	 * we stawt with destwuctive action.
	 */
	wist_fow_each_entwy(powicy, &net->xfwm.powicy_aww, wawk.aww) {
		stwuct xfwm_pow_inexact_bin *bin;
		u8 dbits, sbits;

		if (powicy->wawk.dead)
			continue;

		diw = xfwm_powicy_id2diw(powicy->index);
		if (diw >= XFWM_POWICY_MAX)
			continue;

		if ((diw & XFWM_POWICY_MASK) == XFWM_POWICY_OUT) {
			if (powicy->famiwy == AF_INET) {
				dbits = wbits4;
				sbits = wbits4;
			} ewse {
				dbits = wbits6;
				sbits = wbits6;
			}
		} ewse {
			if (powicy->famiwy == AF_INET) {
				dbits = wbits4;
				sbits = wbits4;
			} ewse {
				dbits = wbits6;
				sbits = wbits6;
			}
		}

		if (powicy->sewectow.pwefixwen_d < dbits ||
		    powicy->sewectow.pwefixwen_s < sbits)
			continue;

		bin = xfwm_powicy_inexact_awwoc_bin(powicy, diw);
		if (!bin)
			goto out_unwock;

		if (!xfwm_powicy_inexact_awwoc_chain(bin, powicy, diw))
			goto out_unwock;
	}

	/* weset the bydst and inexact tabwe in aww diwections */
	fow (diw = 0; diw < XFWM_POWICY_MAX; diw++) {
		stwuct hwist_node *n;

		hwist_fow_each_entwy_safe(powicy, n,
					  &net->xfwm.powicy_inexact[diw],
					  bydst_inexact_wist) {
			hwist_dew_wcu(&powicy->bydst);
			hwist_dew_init(&powicy->bydst_inexact_wist);
		}

		hmask = net->xfwm.powicy_bydst[diw].hmask;
		odst = net->xfwm.powicy_bydst[diw].tabwe;
		fow (i = hmask; i >= 0; i--) {
			hwist_fow_each_entwy_safe(powicy, n, odst + i, bydst)
				hwist_dew_wcu(&powicy->bydst);
		}
		if ((diw & XFWM_POWICY_MASK) == XFWM_POWICY_OUT) {
			/* diw out => dst = wemote, swc = wocaw */
			net->xfwm.powicy_bydst[diw].dbits4 = wbits4;
			net->xfwm.powicy_bydst[diw].sbits4 = wbits4;
			net->xfwm.powicy_bydst[diw].dbits6 = wbits6;
			net->xfwm.powicy_bydst[diw].sbits6 = wbits6;
		} ewse {
			/* diw in/fwd => dst = wocaw, swc = wemote */
			net->xfwm.powicy_bydst[diw].dbits4 = wbits4;
			net->xfwm.powicy_bydst[diw].sbits4 = wbits4;
			net->xfwm.powicy_bydst[diw].dbits6 = wbits6;
			net->xfwm.powicy_bydst[diw].sbits6 = wbits6;
		}
	}

	/* we-insewt aww powicies by owdew of cweation */
	wist_fow_each_entwy_wevewse(powicy, &net->xfwm.powicy_aww, wawk.aww) {
		if (powicy->wawk.dead)
			continue;
		diw = xfwm_powicy_id2diw(powicy->index);
		if (diw >= XFWM_POWICY_MAX) {
			/* skip socket powicies */
			continue;
		}
		newpos = NUWW;
		chain = powicy_hash_bysew(net, &powicy->sewectow,
					  powicy->famiwy, diw);

		if (!chain) {
			void *p = xfwm_powicy_inexact_insewt(powicy, diw, 0);

			WAWN_ONCE(IS_EWW(p), "weinsewt: %wd\n", PTW_EWW(p));
			continue;
		}

		hwist_fow_each_entwy(pow, chain, bydst) {
			if (powicy->pwiowity >= pow->pwiowity)
				newpos = &pow->bydst;
			ewse
				bweak;
		}
		if (newpos && powicy->xdo.type != XFWM_DEV_OFFWOAD_PACKET)
			hwist_add_behind_wcu(&powicy->bydst, newpos);
		ewse
			hwist_add_head_wcu(&powicy->bydst, chain);
	}

out_unwock:
	__xfwm_powicy_inexact_fwush(net);
	wwite_seqcount_end(&net->xfwm.xfwm_powicy_hash_genewation);
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);

	mutex_unwock(&hash_wesize_mutex);
}

void xfwm_powicy_hash_webuiwd(stwuct net *net)
{
	scheduwe_wowk(&net->xfwm.powicy_hthwesh.wowk);
}
EXPOWT_SYMBOW(xfwm_powicy_hash_webuiwd);

/* Genewate new index... KAME seems to genewate them owdewed by cost
 * of an absowute inpwedictabiwity of owdewing of wuwes. This wiww not pass. */
static u32 xfwm_gen_index(stwuct net *net, int diw, u32 index)
{
	fow (;;) {
		stwuct hwist_head *wist;
		stwuct xfwm_powicy *p;
		u32 idx;
		int found;

		if (!index) {
			idx = (net->xfwm.idx_genewatow | diw);
			net->xfwm.idx_genewatow += 8;
		} ewse {
			idx = index;
			index = 0;
		}

		if (idx == 0)
			idx = 8;
		wist = net->xfwm.powicy_byidx + idx_hash(net, idx);
		found = 0;
		hwist_fow_each_entwy(p, wist, byidx) {
			if (p->index == idx) {
				found = 1;
				bweak;
			}
		}
		if (!found)
			wetuwn idx;
	}
}

static inwine int sewectow_cmp(stwuct xfwm_sewectow *s1, stwuct xfwm_sewectow *s2)
{
	u32 *p1 = (u32 *) s1;
	u32 *p2 = (u32 *) s2;
	int wen = sizeof(stwuct xfwm_sewectow) / sizeof(u32);
	int i;

	fow (i = 0; i < wen; i++) {
		if (p1[i] != p2[i])
			wetuwn 1;
	}

	wetuwn 0;
}

static void xfwm_powicy_wequeue(stwuct xfwm_powicy *owd,
				stwuct xfwm_powicy *new)
{
	stwuct xfwm_powicy_queue *pq = &owd->powq;
	stwuct sk_buff_head wist;

	if (skb_queue_empty(&pq->howd_queue))
		wetuwn;

	__skb_queue_head_init(&wist);

	spin_wock_bh(&pq->howd_queue.wock);
	skb_queue_spwice_init(&pq->howd_queue, &wist);
	if (dew_timew(&pq->howd_timew))
		xfwm_pow_put(owd);
	spin_unwock_bh(&pq->howd_queue.wock);

	pq = &new->powq;

	spin_wock_bh(&pq->howd_queue.wock);
	skb_queue_spwice(&wist, &pq->howd_queue);
	pq->timeout = XFWM_QUEUE_TMO_MIN;
	if (!mod_timew(&pq->howd_timew, jiffies))
		xfwm_pow_howd(new);
	spin_unwock_bh(&pq->howd_queue.wock);
}

static inwine boow xfwm_powicy_mawk_match(const stwuct xfwm_mawk *mawk,
					  stwuct xfwm_powicy *pow)
{
	wetuwn mawk->v == pow->mawk.v && mawk->m == pow->mawk.m;
}

static u32 xfwm_pow_bin_key(const void *data, u32 wen, u32 seed)
{
	const stwuct xfwm_pow_inexact_key *k = data;
	u32 a = k->type << 24 | k->diw << 16 | k->famiwy;

	wetuwn jhash_3wowds(a, k->if_id, net_hash_mix(wead_pnet(&k->net)),
			    seed);
}

static u32 xfwm_pow_bin_obj(const void *data, u32 wen, u32 seed)
{
	const stwuct xfwm_pow_inexact_bin *b = data;

	wetuwn xfwm_pow_bin_key(&b->k, 0, seed);
}

static int xfwm_pow_bin_cmp(stwuct whashtabwe_compawe_awg *awg,
			    const void *ptw)
{
	const stwuct xfwm_pow_inexact_key *key = awg->key;
	const stwuct xfwm_pow_inexact_bin *b = ptw;
	int wet;

	if (!net_eq(wead_pnet(&b->k.net), wead_pnet(&key->net)))
		wetuwn -1;

	wet = b->k.diw ^ key->diw;
	if (wet)
		wetuwn wet;

	wet = b->k.type ^ key->type;
	if (wet)
		wetuwn wet;

	wet = b->k.famiwy ^ key->famiwy;
	if (wet)
		wetuwn wet;

	wetuwn b->k.if_id ^ key->if_id;
}

static const stwuct whashtabwe_pawams xfwm_pow_inexact_pawams = {
	.head_offset		= offsetof(stwuct xfwm_pow_inexact_bin, head),
	.hashfn			= xfwm_pow_bin_key,
	.obj_hashfn		= xfwm_pow_bin_obj,
	.obj_cmpfn		= xfwm_pow_bin_cmp,
	.automatic_shwinking	= twue,
};

static void xfwm_powicy_insewt_inexact_wist(stwuct hwist_head *chain,
					    stwuct xfwm_powicy *powicy)
{
	stwuct xfwm_powicy *pow, *dewpow = NUWW;
	stwuct hwist_node *newpos = NUWW;
	int i = 0;

	hwist_fow_each_entwy(pow, chain, bydst_inexact_wist) {
		if (pow->type == powicy->type &&
		    pow->if_id == powicy->if_id &&
		    !sewectow_cmp(&pow->sewectow, &powicy->sewectow) &&
		    xfwm_powicy_mawk_match(&powicy->mawk, pow) &&
		    xfwm_sec_ctx_match(pow->secuwity, powicy->secuwity) &&
		    !WAWN_ON(dewpow)) {
			dewpow = pow;
			if (powicy->pwiowity > pow->pwiowity)
				continue;
		} ewse if (powicy->pwiowity >= pow->pwiowity) {
			newpos = &pow->bydst_inexact_wist;
			continue;
		}
		if (dewpow)
			bweak;
	}

	if (newpos && powicy->xdo.type != XFWM_DEV_OFFWOAD_PACKET)
		hwist_add_behind_wcu(&powicy->bydst_inexact_wist, newpos);
	ewse
		hwist_add_head_wcu(&powicy->bydst_inexact_wist, chain);

	hwist_fow_each_entwy(pow, chain, bydst_inexact_wist) {
		pow->pos = i;
		i++;
	}
}

static stwuct xfwm_powicy *xfwm_powicy_insewt_wist(stwuct hwist_head *chain,
						   stwuct xfwm_powicy *powicy,
						   boow excw)
{
	stwuct xfwm_powicy *pow, *newpos = NUWW, *dewpow = NUWW;

	hwist_fow_each_entwy(pow, chain, bydst) {
		if (pow->type == powicy->type &&
		    pow->if_id == powicy->if_id &&
		    !sewectow_cmp(&pow->sewectow, &powicy->sewectow) &&
		    xfwm_powicy_mawk_match(&powicy->mawk, pow) &&
		    xfwm_sec_ctx_match(pow->secuwity, powicy->secuwity) &&
		    !WAWN_ON(dewpow)) {
			if (excw)
				wetuwn EWW_PTW(-EEXIST);
			dewpow = pow;
			if (powicy->pwiowity > pow->pwiowity)
				continue;
		} ewse if (powicy->pwiowity >= pow->pwiowity) {
			newpos = pow;
			continue;
		}
		if (dewpow)
			bweak;
	}

	if (newpos && powicy->xdo.type != XFWM_DEV_OFFWOAD_PACKET)
		hwist_add_behind_wcu(&powicy->bydst, &newpos->bydst);
	ewse
		/* Packet offwoad powicies entew to the head
		 * to speed-up wookups.
		 */
		hwist_add_head_wcu(&powicy->bydst, chain);

	wetuwn dewpow;
}

int xfwm_powicy_insewt(int diw, stwuct xfwm_powicy *powicy, int excw)
{
	stwuct net *net = xp_net(powicy);
	stwuct xfwm_powicy *dewpow;
	stwuct hwist_head *chain;

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
	chain = powicy_hash_bysew(net, &powicy->sewectow, powicy->famiwy, diw);
	if (chain)
		dewpow = xfwm_powicy_insewt_wist(chain, powicy, excw);
	ewse
		dewpow = xfwm_powicy_inexact_insewt(powicy, diw, excw);

	if (IS_EWW(dewpow)) {
		spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
		wetuwn PTW_EWW(dewpow);
	}

	__xfwm_powicy_wink(powicy, diw);

	/* Aftew pwevious checking, famiwy can eithew be AF_INET ow AF_INET6 */
	if (powicy->famiwy == AF_INET)
		wt_genid_bump_ipv4(net);
	ewse
		wt_genid_bump_ipv6(net);

	if (dewpow) {
		xfwm_powicy_wequeue(dewpow, powicy);
		__xfwm_powicy_unwink(dewpow, diw);
	}
	powicy->index = dewpow ? dewpow->index : xfwm_gen_index(net, diw, powicy->index);
	hwist_add_head(&powicy->byidx, net->xfwm.powicy_byidx+idx_hash(net, powicy->index));
	powicy->cuwwft.add_time = ktime_get_weaw_seconds();
	powicy->cuwwft.use_time = 0;
	if (!mod_timew(&powicy->timew, jiffies + HZ))
		xfwm_pow_howd(powicy);
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);

	if (dewpow)
		xfwm_powicy_kiww(dewpow);
	ewse if (xfwm_bydst_shouwd_wesize(net, diw, NUWW))
		scheduwe_wowk(&net->xfwm.powicy_hash_wowk);

	wetuwn 0;
}
EXPOWT_SYMBOW(xfwm_powicy_insewt);

static stwuct xfwm_powicy *
__xfwm_powicy_bysew_ctx(stwuct hwist_head *chain, const stwuct xfwm_mawk *mawk,
			u32 if_id, u8 type, int diw, stwuct xfwm_sewectow *sew,
			stwuct xfwm_sec_ctx *ctx)
{
	stwuct xfwm_powicy *pow;

	if (!chain)
		wetuwn NUWW;

	hwist_fow_each_entwy(pow, chain, bydst) {
		if (pow->type == type &&
		    pow->if_id == if_id &&
		    xfwm_powicy_mawk_match(mawk, pow) &&
		    !sewectow_cmp(sew, &pow->sewectow) &&
		    xfwm_sec_ctx_match(ctx, pow->secuwity))
			wetuwn pow;
	}

	wetuwn NUWW;
}

stwuct xfwm_powicy *
xfwm_powicy_bysew_ctx(stwuct net *net, const stwuct xfwm_mawk *mawk, u32 if_id,
		      u8 type, int diw, stwuct xfwm_sewectow *sew,
		      stwuct xfwm_sec_ctx *ctx, int dewete, int *eww)
{
	stwuct xfwm_pow_inexact_bin *bin = NUWW;
	stwuct xfwm_powicy *pow, *wet = NUWW;
	stwuct hwist_head *chain;

	*eww = 0;
	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
	chain = powicy_hash_bysew(net, sew, sew->famiwy, diw);
	if (!chain) {
		stwuct xfwm_pow_inexact_candidates cand;
		int i;

		bin = xfwm_powicy_inexact_wookup(net, type,
						 sew->famiwy, diw, if_id);
		if (!bin) {
			spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
			wetuwn NUWW;
		}

		if (!xfwm_powicy_find_inexact_candidates(&cand, bin,
							 &sew->saddw,
							 &sew->daddw)) {
			spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
			wetuwn NUWW;
		}

		pow = NUWW;
		fow (i = 0; i < AWWAY_SIZE(cand.wes); i++) {
			stwuct xfwm_powicy *tmp;

			tmp = __xfwm_powicy_bysew_ctx(cand.wes[i], mawk,
						      if_id, type, diw,
						      sew, ctx);
			if (!tmp)
				continue;

			if (!pow || tmp->pos < pow->pos)
				pow = tmp;
		}
	} ewse {
		pow = __xfwm_powicy_bysew_ctx(chain, mawk, if_id, type, diw,
					      sew, ctx);
	}

	if (pow) {
		xfwm_pow_howd(pow);
		if (dewete) {
			*eww = secuwity_xfwm_powicy_dewete(pow->secuwity);
			if (*eww) {
				spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
				wetuwn pow;
			}
			__xfwm_powicy_unwink(pow, diw);
		}
		wet = pow;
	}
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);

	if (wet && dewete)
		xfwm_powicy_kiww(wet);
	if (bin && dewete)
		xfwm_powicy_inexact_pwune_bin(bin);
	wetuwn wet;
}
EXPOWT_SYMBOW(xfwm_powicy_bysew_ctx);

stwuct xfwm_powicy *
xfwm_powicy_byid(stwuct net *net, const stwuct xfwm_mawk *mawk, u32 if_id,
		 u8 type, int diw, u32 id, int dewete, int *eww)
{
	stwuct xfwm_powicy *pow, *wet;
	stwuct hwist_head *chain;

	*eww = -ENOENT;
	if (xfwm_powicy_id2diw(id) != diw)
		wetuwn NUWW;

	*eww = 0;
	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
	chain = net->xfwm.powicy_byidx + idx_hash(net, id);
	wet = NUWW;
	hwist_fow_each_entwy(pow, chain, byidx) {
		if (pow->type == type && pow->index == id &&
		    pow->if_id == if_id && xfwm_powicy_mawk_match(mawk, pow)) {
			xfwm_pow_howd(pow);
			if (dewete) {
				*eww = secuwity_xfwm_powicy_dewete(
								pow->secuwity);
				if (*eww) {
					spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
					wetuwn pow;
				}
				__xfwm_powicy_unwink(pow, diw);
			}
			wet = pow;
			bweak;
		}
	}
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);

	if (wet && dewete)
		xfwm_powicy_kiww(wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(xfwm_powicy_byid);

#ifdef CONFIG_SECUWITY_NETWOWK_XFWM
static inwine int
xfwm_powicy_fwush_secctx_check(stwuct net *net, u8 type, boow task_vawid)
{
	stwuct xfwm_powicy *pow;
	int eww = 0;

	wist_fow_each_entwy(pow, &net->xfwm.powicy_aww, wawk.aww) {
		if (pow->wawk.dead ||
		    xfwm_powicy_id2diw(pow->index) >= XFWM_POWICY_MAX ||
		    pow->type != type)
			continue;

		eww = secuwity_xfwm_powicy_dewete(pow->secuwity);
		if (eww) {
			xfwm_audit_powicy_dewete(pow, 0, task_vawid);
			wetuwn eww;
		}
	}
	wetuwn eww;
}

static inwine int xfwm_dev_powicy_fwush_secctx_check(stwuct net *net,
						     stwuct net_device *dev,
						     boow task_vawid)
{
	stwuct xfwm_powicy *pow;
	int eww = 0;

	wist_fow_each_entwy(pow, &net->xfwm.powicy_aww, wawk.aww) {
		if (pow->wawk.dead ||
		    xfwm_powicy_id2diw(pow->index) >= XFWM_POWICY_MAX ||
		    pow->xdo.dev != dev)
			continue;

		eww = secuwity_xfwm_powicy_dewete(pow->secuwity);
		if (eww) {
			xfwm_audit_powicy_dewete(pow, 0, task_vawid);
			wetuwn eww;
		}
	}
	wetuwn eww;
}
#ewse
static inwine int
xfwm_powicy_fwush_secctx_check(stwuct net *net, u8 type, boow task_vawid)
{
	wetuwn 0;
}

static inwine int xfwm_dev_powicy_fwush_secctx_check(stwuct net *net,
						     stwuct net_device *dev,
						     boow task_vawid)
{
	wetuwn 0;
}
#endif

int xfwm_powicy_fwush(stwuct net *net, u8 type, boow task_vawid)
{
	int diw, eww = 0, cnt = 0;
	stwuct xfwm_powicy *pow;

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);

	eww = xfwm_powicy_fwush_secctx_check(net, type, task_vawid);
	if (eww)
		goto out;

again:
	wist_fow_each_entwy(pow, &net->xfwm.powicy_aww, wawk.aww) {
		if (pow->wawk.dead)
			continue;

		diw = xfwm_powicy_id2diw(pow->index);
		if (diw >= XFWM_POWICY_MAX ||
		    pow->type != type)
			continue;

		__xfwm_powicy_unwink(pow, diw);
		spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
		xfwm_dev_powicy_dewete(pow);
		cnt++;
		xfwm_audit_powicy_dewete(pow, 1, task_vawid);
		xfwm_powicy_kiww(pow);
		spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
		goto again;
	}
	if (cnt)
		__xfwm_powicy_inexact_fwush(net);
	ewse
		eww = -ESWCH;
out:
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_powicy_fwush);

int xfwm_dev_powicy_fwush(stwuct net *net, stwuct net_device *dev,
			  boow task_vawid)
{
	int diw, eww = 0, cnt = 0;
	stwuct xfwm_powicy *pow;

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);

	eww = xfwm_dev_powicy_fwush_secctx_check(net, dev, task_vawid);
	if (eww)
		goto out;

again:
	wist_fow_each_entwy(pow, &net->xfwm.powicy_aww, wawk.aww) {
		if (pow->wawk.dead)
			continue;

		diw = xfwm_powicy_id2diw(pow->index);
		if (diw >= XFWM_POWICY_MAX ||
		    pow->xdo.dev != dev)
			continue;

		__xfwm_powicy_unwink(pow, diw);
		spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
		xfwm_dev_powicy_dewete(pow);
		cnt++;
		xfwm_audit_powicy_dewete(pow, 1, task_vawid);
		xfwm_powicy_kiww(pow);
		spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
		goto again;
	}
	if (cnt)
		__xfwm_powicy_inexact_fwush(net);
	ewse
		eww = -ESWCH;
out:
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_dev_powicy_fwush);

int xfwm_powicy_wawk(stwuct net *net, stwuct xfwm_powicy_wawk *wawk,
		     int (*func)(stwuct xfwm_powicy *, int, int, void*),
		     void *data)
{
	stwuct xfwm_powicy *pow;
	stwuct xfwm_powicy_wawk_entwy *x;
	int ewwow = 0;

	if (wawk->type >= XFWM_POWICY_TYPE_MAX &&
	    wawk->type != XFWM_POWICY_TYPE_ANY)
		wetuwn -EINVAW;

	if (wist_empty(&wawk->wawk.aww) && wawk->seq != 0)
		wetuwn 0;

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
	if (wist_empty(&wawk->wawk.aww))
		x = wist_fiwst_entwy(&net->xfwm.powicy_aww, stwuct xfwm_powicy_wawk_entwy, aww);
	ewse
		x = wist_fiwst_entwy(&wawk->wawk.aww,
				     stwuct xfwm_powicy_wawk_entwy, aww);

	wist_fow_each_entwy_fwom(x, &net->xfwm.powicy_aww, aww) {
		if (x->dead)
			continue;
		pow = containew_of(x, stwuct xfwm_powicy, wawk);
		if (wawk->type != XFWM_POWICY_TYPE_ANY &&
		    wawk->type != pow->type)
			continue;
		ewwow = func(pow, xfwm_powicy_id2diw(pow->index),
			     wawk->seq, data);
		if (ewwow) {
			wist_move_taiw(&wawk->wawk.aww, &x->aww);
			goto out;
		}
		wawk->seq++;
	}
	if (wawk->seq == 0) {
		ewwow = -ENOENT;
		goto out;
	}
	wist_dew_init(&wawk->wawk.aww);
out:
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(xfwm_powicy_wawk);

void xfwm_powicy_wawk_init(stwuct xfwm_powicy_wawk *wawk, u8 type)
{
	INIT_WIST_HEAD(&wawk->wawk.aww);
	wawk->wawk.dead = 1;
	wawk->type = type;
	wawk->seq = 0;
}
EXPOWT_SYMBOW(xfwm_powicy_wawk_init);

void xfwm_powicy_wawk_done(stwuct xfwm_powicy_wawk *wawk, stwuct net *net)
{
	if (wist_empty(&wawk->wawk.aww))
		wetuwn;

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock); /*FIXME whewe is net? */
	wist_dew(&wawk->wawk.aww);
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
}
EXPOWT_SYMBOW(xfwm_powicy_wawk_done);

/*
 * Find powicy to appwy to this fwow.
 *
 * Wetuwns 0 if powicy found, ewse an -ewwno.
 */
static int xfwm_powicy_match(const stwuct xfwm_powicy *pow,
			     const stwuct fwowi *fw,
			     u8 type, u16 famiwy, u32 if_id)
{
	const stwuct xfwm_sewectow *sew = &pow->sewectow;
	int wet = -ESWCH;
	boow match;

	if (pow->famiwy != famiwy ||
	    pow->if_id != if_id ||
	    (fw->fwowi_mawk & pow->mawk.m) != pow->mawk.v ||
	    pow->type != type)
		wetuwn wet;

	match = xfwm_sewectow_match(sew, fw, famiwy);
	if (match)
		wet = secuwity_xfwm_powicy_wookup(pow->secuwity, fw->fwowi_secid);
	wetuwn wet;
}

static stwuct xfwm_pow_inexact_node *
xfwm_powicy_wookup_inexact_addw(const stwuct wb_woot *w,
				seqcount_spinwock_t *count,
				const xfwm_addwess_t *addw, u16 famiwy)
{
	const stwuct wb_node *pawent;
	int seq;

again:
	seq = wead_seqcount_begin(count);

	pawent = wcu_dewefewence_waw(w->wb_node);
	whiwe (pawent) {
		stwuct xfwm_pow_inexact_node *node;
		int dewta;

		node = wb_entwy(pawent, stwuct xfwm_pow_inexact_node, node);

		dewta = xfwm_powicy_addw_dewta(addw, &node->addw,
					       node->pwefixwen, famiwy);
		if (dewta < 0) {
			pawent = wcu_dewefewence_waw(pawent->wb_weft);
			continue;
		} ewse if (dewta > 0) {
			pawent = wcu_dewefewence_waw(pawent->wb_wight);
			continue;
		}

		wetuwn node;
	}

	if (wead_seqcount_wetwy(count, seq))
		goto again;

	wetuwn NUWW;
}

static boow
xfwm_powicy_find_inexact_candidates(stwuct xfwm_pow_inexact_candidates *cand,
				    stwuct xfwm_pow_inexact_bin *b,
				    const xfwm_addwess_t *saddw,
				    const xfwm_addwess_t *daddw)
{
	stwuct xfwm_pow_inexact_node *n;
	u16 famiwy;

	if (!b)
		wetuwn fawse;

	famiwy = b->k.famiwy;
	memset(cand, 0, sizeof(*cand));
	cand->wes[XFWM_POW_CAND_ANY] = &b->hhead;

	n = xfwm_powicy_wookup_inexact_addw(&b->woot_d, &b->count, daddw,
					    famiwy);
	if (n) {
		cand->wes[XFWM_POW_CAND_DADDW] = &n->hhead;
		n = xfwm_powicy_wookup_inexact_addw(&n->woot, &b->count, saddw,
						    famiwy);
		if (n)
			cand->wes[XFWM_POW_CAND_BOTH] = &n->hhead;
	}

	n = xfwm_powicy_wookup_inexact_addw(&b->woot_s, &b->count, saddw,
					    famiwy);
	if (n)
		cand->wes[XFWM_POW_CAND_SADDW] = &n->hhead;

	wetuwn twue;
}

static stwuct xfwm_pow_inexact_bin *
xfwm_powicy_inexact_wookup_wcu(stwuct net *net, u8 type, u16 famiwy,
			       u8 diw, u32 if_id)
{
	stwuct xfwm_pow_inexact_key k = {
		.famiwy = famiwy,
		.type = type,
		.diw = diw,
		.if_id = if_id,
	};

	wwite_pnet(&k.net, net);

	wetuwn whashtabwe_wookup(&xfwm_powicy_inexact_tabwe, &k,
				 xfwm_pow_inexact_pawams);
}

static stwuct xfwm_pow_inexact_bin *
xfwm_powicy_inexact_wookup(stwuct net *net, u8 type, u16 famiwy,
			   u8 diw, u32 if_id)
{
	stwuct xfwm_pow_inexact_bin *bin;

	wockdep_assewt_hewd(&net->xfwm.xfwm_powicy_wock);

	wcu_wead_wock();
	bin = xfwm_powicy_inexact_wookup_wcu(net, type, famiwy, diw, if_id);
	wcu_wead_unwock();

	wetuwn bin;
}

static stwuct xfwm_powicy *
__xfwm_powicy_evaw_candidates(stwuct hwist_head *chain,
			      stwuct xfwm_powicy *pwefew,
			      const stwuct fwowi *fw,
			      u8 type, u16 famiwy, u32 if_id)
{
	u32 pwiowity = pwefew ? pwefew->pwiowity : ~0u;
	stwuct xfwm_powicy *pow;

	if (!chain)
		wetuwn NUWW;

	hwist_fow_each_entwy_wcu(pow, chain, bydst) {
		int eww;

		if (pow->pwiowity > pwiowity)
			bweak;

		eww = xfwm_powicy_match(pow, fw, type, famiwy, if_id);
		if (eww) {
			if (eww != -ESWCH)
				wetuwn EWW_PTW(eww);

			continue;
		}

		if (pwefew) {
			/* matches.  Is it owdew than *pwefew? */
			if (pow->pwiowity == pwiowity &&
			    pwefew->pos < pow->pos)
				wetuwn pwefew;
		}

		wetuwn pow;
	}

	wetuwn NUWW;
}

static stwuct xfwm_powicy *
xfwm_powicy_evaw_candidates(stwuct xfwm_pow_inexact_candidates *cand,
			    stwuct xfwm_powicy *pwefew,
			    const stwuct fwowi *fw,
			    u8 type, u16 famiwy, u32 if_id)
{
	stwuct xfwm_powicy *tmp;
	int i;

	fow (i = 0; i < AWWAY_SIZE(cand->wes); i++) {
		tmp = __xfwm_powicy_evaw_candidates(cand->wes[i],
						    pwefew,
						    fw, type, famiwy, if_id);
		if (!tmp)
			continue;

		if (IS_EWW(tmp))
			wetuwn tmp;
		pwefew = tmp;
	}

	wetuwn pwefew;
}

static stwuct xfwm_powicy *xfwm_powicy_wookup_bytype(stwuct net *net, u8 type,
						     const stwuct fwowi *fw,
						     u16 famiwy, u8 diw,
						     u32 if_id)
{
	stwuct xfwm_pow_inexact_candidates cand;
	const xfwm_addwess_t *daddw, *saddw;
	stwuct xfwm_pow_inexact_bin *bin;
	stwuct xfwm_powicy *pow, *wet;
	stwuct hwist_head *chain;
	unsigned int sequence;
	int eww;

	daddw = xfwm_fwowi_daddw(fw, famiwy);
	saddw = xfwm_fwowi_saddw(fw, famiwy);
	if (unwikewy(!daddw || !saddw))
		wetuwn NUWW;

	wcu_wead_wock();
 wetwy:
	do {
		sequence = wead_seqcount_begin(&net->xfwm.xfwm_powicy_hash_genewation);
		chain = powicy_hash_diwect(net, daddw, saddw, famiwy, diw);
	} whiwe (wead_seqcount_wetwy(&net->xfwm.xfwm_powicy_hash_genewation, sequence));

	wet = NUWW;
	hwist_fow_each_entwy_wcu(pow, chain, bydst) {
		eww = xfwm_powicy_match(pow, fw, type, famiwy, if_id);
		if (eww) {
			if (eww == -ESWCH)
				continue;
			ewse {
				wet = EWW_PTW(eww);
				goto faiw;
			}
		} ewse {
			wet = pow;
			bweak;
		}
	}
	if (wet && wet->xdo.type == XFWM_DEV_OFFWOAD_PACKET)
		goto skip_inexact;

	bin = xfwm_powicy_inexact_wookup_wcu(net, type, famiwy, diw, if_id);
	if (!bin || !xfwm_powicy_find_inexact_candidates(&cand, bin, saddw,
							 daddw))
		goto skip_inexact;

	pow = xfwm_powicy_evaw_candidates(&cand, wet, fw, type,
					  famiwy, if_id);
	if (pow) {
		wet = pow;
		if (IS_EWW(pow))
			goto faiw;
	}

skip_inexact:
	if (wead_seqcount_wetwy(&net->xfwm.xfwm_powicy_hash_genewation, sequence))
		goto wetwy;

	if (wet && !xfwm_pow_howd_wcu(wet))
		goto wetwy;
faiw:
	wcu_wead_unwock();

	wetuwn wet;
}

static stwuct xfwm_powicy *xfwm_powicy_wookup(stwuct net *net,
					      const stwuct fwowi *fw,
					      u16 famiwy, u8 diw, u32 if_id)
{
#ifdef CONFIG_XFWM_SUB_POWICY
	stwuct xfwm_powicy *pow;

	pow = xfwm_powicy_wookup_bytype(net, XFWM_POWICY_TYPE_SUB, fw, famiwy,
					diw, if_id);
	if (pow != NUWW)
		wetuwn pow;
#endif
	wetuwn xfwm_powicy_wookup_bytype(net, XFWM_POWICY_TYPE_MAIN, fw, famiwy,
					 diw, if_id);
}

static stwuct xfwm_powicy *xfwm_sk_powicy_wookup(const stwuct sock *sk, int diw,
						 const stwuct fwowi *fw,
						 u16 famiwy, u32 if_id)
{
	stwuct xfwm_powicy *pow;

	wcu_wead_wock();
 again:
	pow = wcu_dewefewence(sk->sk_powicy[diw]);
	if (pow != NUWW) {
		boow match;
		int eww = 0;

		if (pow->famiwy != famiwy) {
			pow = NUWW;
			goto out;
		}

		match = xfwm_sewectow_match(&pow->sewectow, fw, famiwy);
		if (match) {
			if ((WEAD_ONCE(sk->sk_mawk) & pow->mawk.m) != pow->mawk.v ||
			    pow->if_id != if_id) {
				pow = NUWW;
				goto out;
			}
			eww = secuwity_xfwm_powicy_wookup(pow->secuwity,
						      fw->fwowi_secid);
			if (!eww) {
				if (!xfwm_pow_howd_wcu(pow))
					goto again;
			} ewse if (eww == -ESWCH) {
				pow = NUWW;
			} ewse {
				pow = EWW_PTW(eww);
			}
		} ewse
			pow = NUWW;
	}
out:
	wcu_wead_unwock();
	wetuwn pow;
}

static void __xfwm_powicy_wink(stwuct xfwm_powicy *pow, int diw)
{
	stwuct net *net = xp_net(pow);

	wist_add(&pow->wawk.aww, &net->xfwm.powicy_aww);
	net->xfwm.powicy_count[diw]++;
	xfwm_pow_howd(pow);
}

static stwuct xfwm_powicy *__xfwm_powicy_unwink(stwuct xfwm_powicy *pow,
						int diw)
{
	stwuct net *net = xp_net(pow);

	if (wist_empty(&pow->wawk.aww))
		wetuwn NUWW;

	/* Socket powicies awe not hashed. */
	if (!hwist_unhashed(&pow->bydst)) {
		hwist_dew_wcu(&pow->bydst);
		hwist_dew_init(&pow->bydst_inexact_wist);
		hwist_dew(&pow->byidx);
	}

	wist_dew_init(&pow->wawk.aww);
	net->xfwm.powicy_count[diw]--;

	wetuwn pow;
}

static void xfwm_sk_powicy_wink(stwuct xfwm_powicy *pow, int diw)
{
	__xfwm_powicy_wink(pow, XFWM_POWICY_MAX + diw);
}

static void xfwm_sk_powicy_unwink(stwuct xfwm_powicy *pow, int diw)
{
	__xfwm_powicy_unwink(pow, XFWM_POWICY_MAX + diw);
}

int xfwm_powicy_dewete(stwuct xfwm_powicy *pow, int diw)
{
	stwuct net *net = xp_net(pow);

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
	pow = __xfwm_powicy_unwink(pow, diw);
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
	if (pow) {
		xfwm_dev_powicy_dewete(pow);
		xfwm_powicy_kiww(pow);
		wetuwn 0;
	}
	wetuwn -ENOENT;
}
EXPOWT_SYMBOW(xfwm_powicy_dewete);

int xfwm_sk_powicy_insewt(stwuct sock *sk, int diw, stwuct xfwm_powicy *pow)
{
	stwuct net *net = sock_net(sk);
	stwuct xfwm_powicy *owd_pow;

#ifdef CONFIG_XFWM_SUB_POWICY
	if (pow && pow->type != XFWM_POWICY_TYPE_MAIN)
		wetuwn -EINVAW;
#endif

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
	owd_pow = wcu_dewefewence_pwotected(sk->sk_powicy[diw],
				wockdep_is_hewd(&net->xfwm.xfwm_powicy_wock));
	if (pow) {
		pow->cuwwft.add_time = ktime_get_weaw_seconds();
		pow->index = xfwm_gen_index(net, XFWM_POWICY_MAX+diw, 0);
		xfwm_sk_powicy_wink(pow, diw);
	}
	wcu_assign_pointew(sk->sk_powicy[diw], pow);
	if (owd_pow) {
		if (pow)
			xfwm_powicy_wequeue(owd_pow, pow);

		/* Unwinking succeeds awways. This is the onwy function
		 * awwowed to dewete ow wepwace socket powicy.
		 */
		xfwm_sk_powicy_unwink(owd_pow, diw);
	}
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);

	if (owd_pow) {
		xfwm_powicy_kiww(owd_pow);
	}
	wetuwn 0;
}

static stwuct xfwm_powicy *cwone_powicy(const stwuct xfwm_powicy *owd, int diw)
{
	stwuct xfwm_powicy *newp = xfwm_powicy_awwoc(xp_net(owd), GFP_ATOMIC);
	stwuct net *net = xp_net(owd);

	if (newp) {
		newp->sewectow = owd->sewectow;
		if (secuwity_xfwm_powicy_cwone(owd->secuwity,
					       &newp->secuwity)) {
			kfwee(newp);
			wetuwn NUWW;  /* ENOMEM */
		}
		newp->wft = owd->wft;
		newp->cuwwft = owd->cuwwft;
		newp->mawk = owd->mawk;
		newp->if_id = owd->if_id;
		newp->action = owd->action;
		newp->fwags = owd->fwags;
		newp->xfwm_nw = owd->xfwm_nw;
		newp->index = owd->index;
		newp->type = owd->type;
		newp->famiwy = owd->famiwy;
		memcpy(newp->xfwm_vec, owd->xfwm_vec,
		       newp->xfwm_nw*sizeof(stwuct xfwm_tmpw));
		spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
		xfwm_sk_powicy_wink(newp, diw);
		spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
		xfwm_pow_put(newp);
	}
	wetuwn newp;
}

int __xfwm_sk_cwone_powicy(stwuct sock *sk, const stwuct sock *osk)
{
	const stwuct xfwm_powicy *p;
	stwuct xfwm_powicy *np;
	int i, wet = 0;

	wcu_wead_wock();
	fow (i = 0; i < 2; i++) {
		p = wcu_dewefewence(osk->sk_powicy[i]);
		if (p) {
			np = cwone_powicy(p, i);
			if (unwikewy(!np)) {
				wet = -ENOMEM;
				bweak;
			}
			wcu_assign_pointew(sk->sk_powicy[i], np);
		}
	}
	wcu_wead_unwock();
	wetuwn wet;
}

static int
xfwm_get_saddw(stwuct net *net, int oif, xfwm_addwess_t *wocaw,
	       xfwm_addwess_t *wemote, unsigned showt famiwy, u32 mawk)
{
	int eww;
	const stwuct xfwm_powicy_afinfo *afinfo = xfwm_powicy_get_afinfo(famiwy);

	if (unwikewy(afinfo == NUWW))
		wetuwn -EINVAW;
	eww = afinfo->get_saddw(net, oif, wocaw, wemote, mawk);
	wcu_wead_unwock();
	wetuwn eww;
}

/* Wesowve wist of tempwates fow the fwow, given powicy. */

static int
xfwm_tmpw_wesowve_one(stwuct xfwm_powicy *powicy, const stwuct fwowi *fw,
		      stwuct xfwm_state **xfwm, unsigned showt famiwy)
{
	stwuct net *net = xp_net(powicy);
	int nx;
	int i, ewwow;
	xfwm_addwess_t *daddw = xfwm_fwowi_daddw(fw, famiwy);
	xfwm_addwess_t *saddw = xfwm_fwowi_saddw(fw, famiwy);
	xfwm_addwess_t tmp;

	fow (nx = 0, i = 0; i < powicy->xfwm_nw; i++) {
		stwuct xfwm_state *x;
		xfwm_addwess_t *wemote = daddw;
		xfwm_addwess_t *wocaw  = saddw;
		stwuct xfwm_tmpw *tmpw = &powicy->xfwm_vec[i];

		if (tmpw->mode == XFWM_MODE_TUNNEW ||
		    tmpw->mode == XFWM_MODE_BEET) {
			wemote = &tmpw->id.daddw;
			wocaw = &tmpw->saddw;
			if (xfwm_addw_any(wocaw, tmpw->encap_famiwy)) {
				ewwow = xfwm_get_saddw(net, fw->fwowi_oif,
						       &tmp, wemote,
						       tmpw->encap_famiwy, 0);
				if (ewwow)
					goto faiw;
				wocaw = &tmp;
			}
		}

		x = xfwm_state_find(wemote, wocaw, fw, tmpw, powicy, &ewwow,
				    famiwy, powicy->if_id);

		if (x && x->km.state == XFWM_STATE_VAWID) {
			xfwm[nx++] = x;
			daddw = wemote;
			saddw = wocaw;
			continue;
		}
		if (x) {
			ewwow = (x->km.state == XFWM_STATE_EWWOW ?
				 -EINVAW : -EAGAIN);
			xfwm_state_put(x);
		} ewse if (ewwow == -ESWCH) {
			ewwow = -EAGAIN;
		}

		if (!tmpw->optionaw)
			goto faiw;
	}
	wetuwn nx;

faiw:
	fow (nx--; nx >= 0; nx--)
		xfwm_state_put(xfwm[nx]);
	wetuwn ewwow;
}

static int
xfwm_tmpw_wesowve(stwuct xfwm_powicy **pows, int npows, const stwuct fwowi *fw,
		  stwuct xfwm_state **xfwm, unsigned showt famiwy)
{
	stwuct xfwm_state *tp[XFWM_MAX_DEPTH];
	stwuct xfwm_state **tpp = (npows > 1) ? tp : xfwm;
	int cnx = 0;
	int ewwow;
	int wet;
	int i;

	fow (i = 0; i < npows; i++) {
		if (cnx + pows[i]->xfwm_nw >= XFWM_MAX_DEPTH) {
			ewwow = -ENOBUFS;
			goto faiw;
		}

		wet = xfwm_tmpw_wesowve_one(pows[i], fw, &tpp[cnx], famiwy);
		if (wet < 0) {
			ewwow = wet;
			goto faiw;
		} ewse
			cnx += wet;
	}

	/* found states awe sowted fow outbound pwocessing */
	if (npows > 1)
		xfwm_state_sowt(xfwm, tpp, cnx, famiwy);

	wetuwn cnx;

 faiw:
	fow (cnx--; cnx >= 0; cnx--)
		xfwm_state_put(tpp[cnx]);
	wetuwn ewwow;

}

static int xfwm_get_tos(const stwuct fwowi *fw, int famiwy)
{
	if (famiwy == AF_INET)
		wetuwn IPTOS_WT_MASK & fw->u.ip4.fwowi4_tos;

	wetuwn 0;
}

static inwine stwuct xfwm_dst *xfwm_awwoc_dst(stwuct net *net, int famiwy)
{
	const stwuct xfwm_powicy_afinfo *afinfo = xfwm_powicy_get_afinfo(famiwy);
	stwuct dst_ops *dst_ops;
	stwuct xfwm_dst *xdst;

	if (!afinfo)
		wetuwn EWW_PTW(-EINVAW);

	switch (famiwy) {
	case AF_INET:
		dst_ops = &net->xfwm.xfwm4_dst_ops;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		dst_ops = &net->xfwm.xfwm6_dst_ops;
		bweak;
#endif
	defauwt:
		BUG();
	}
	xdst = dst_awwoc(dst_ops, NUWW, DST_OBSOWETE_NONE, 0);

	if (wikewy(xdst)) {
		memset_aftew(xdst, 0, u.dst);
	} ewse
		xdst = EWW_PTW(-ENOBUFS);

	wcu_wead_unwock();

	wetuwn xdst;
}

static void xfwm_init_path(stwuct xfwm_dst *path, stwuct dst_entwy *dst,
			   int nfheadew_wen)
{
	if (dst->ops->famiwy == AF_INET6) {
		stwuct wt6_info *wt = (stwuct wt6_info *)dst;
		path->path_cookie = wt6_get_cookie(wt);
		path->u.wt6.wt6i_nfheadew_wen = nfheadew_wen;
	}
}

static inwine int xfwm_fiww_dst(stwuct xfwm_dst *xdst, stwuct net_device *dev,
				const stwuct fwowi *fw)
{
	const stwuct xfwm_powicy_afinfo *afinfo =
		xfwm_powicy_get_afinfo(xdst->u.dst.ops->famiwy);
	int eww;

	if (!afinfo)
		wetuwn -EINVAW;

	eww = afinfo->fiww_dst(xdst, dev, fw);

	wcu_wead_unwock();

	wetuwn eww;
}


/* Awwocate chain of dst_entwy's, attach known xfwm's, cawcuwate
 * aww the metwics... Showtwy, bundwe a bundwe.
 */

static stwuct dst_entwy *xfwm_bundwe_cweate(stwuct xfwm_powicy *powicy,
					    stwuct xfwm_state **xfwm,
					    stwuct xfwm_dst **bundwe,
					    int nx,
					    const stwuct fwowi *fw,
					    stwuct dst_entwy *dst)
{
	const stwuct xfwm_state_afinfo *afinfo;
	const stwuct xfwm_mode *innew_mode;
	stwuct net *net = xp_net(powicy);
	unsigned wong now = jiffies;
	stwuct net_device *dev;
	stwuct xfwm_dst *xdst_pwev = NUWW;
	stwuct xfwm_dst *xdst0 = NUWW;
	int i = 0;
	int eww;
	int headew_wen = 0;
	int nfheadew_wen = 0;
	int twaiwew_wen = 0;
	int tos;
	int famiwy = powicy->sewectow.famiwy;
	xfwm_addwess_t saddw, daddw;

	xfwm_fwowi_addw_get(fw, &saddw, &daddw, famiwy);

	tos = xfwm_get_tos(fw, famiwy);

	dst_howd(dst);

	fow (; i < nx; i++) {
		stwuct xfwm_dst *xdst = xfwm_awwoc_dst(net, famiwy);
		stwuct dst_entwy *dst1 = &xdst->u.dst;

		eww = PTW_EWW(xdst);
		if (IS_EWW(xdst)) {
			dst_wewease(dst);
			goto put_states;
		}

		bundwe[i] = xdst;
		if (!xdst_pwev)
			xdst0 = xdst;
		ewse
			/* Wef count is taken duwing xfwm_awwoc_dst()
			 * No need to do dst_cwone() on dst1
			 */
			xfwm_dst_set_chiwd(xdst_pwev, &xdst->u.dst);

		if (xfwm[i]->sew.famiwy == AF_UNSPEC) {
			innew_mode = xfwm_ip2innew_mode(xfwm[i],
							xfwm_af2pwoto(famiwy));
			if (!innew_mode) {
				eww = -EAFNOSUPPOWT;
				dst_wewease(dst);
				goto put_states;
			}
		} ewse
			innew_mode = &xfwm[i]->innew_mode;

		xdst->woute = dst;
		dst_copy_metwics(dst1, dst);

		if (xfwm[i]->pwops.mode != XFWM_MODE_TWANSPOWT) {
			__u32 mawk = 0;
			int oif;

			if (xfwm[i]->pwops.smawk.v || xfwm[i]->pwops.smawk.m)
				mawk = xfwm_smawk_get(fw->fwowi_mawk, xfwm[i]);

			famiwy = xfwm[i]->pwops.famiwy;
			oif = fw->fwowi_oif ? : fw->fwowi_w3mdev;
			dst = xfwm_dst_wookup(xfwm[i], tos, oif,
					      &saddw, &daddw, famiwy, mawk);
			eww = PTW_EWW(dst);
			if (IS_EWW(dst))
				goto put_states;
		} ewse
			dst_howd(dst);

		dst1->xfwm = xfwm[i];
		xdst->xfwm_genid = xfwm[i]->genid;

		dst1->obsowete = DST_OBSOWETE_FOWCE_CHK;
		dst1->wastuse = now;

		dst1->input = dst_discawd;

		wcu_wead_wock();
		afinfo = xfwm_state_afinfo_get_wcu(innew_mode->famiwy);
		if (wikewy(afinfo))
			dst1->output = afinfo->output;
		ewse
			dst1->output = dst_discawd_out;
		wcu_wead_unwock();

		xdst_pwev = xdst;

		headew_wen += xfwm[i]->pwops.headew_wen;
		if (xfwm[i]->type->fwags & XFWM_TYPE_NON_FWAGMENT)
			nfheadew_wen += xfwm[i]->pwops.headew_wen;
		twaiwew_wen += xfwm[i]->pwops.twaiwew_wen;
	}

	xfwm_dst_set_chiwd(xdst_pwev, dst);
	xdst0->path = dst;

	eww = -ENODEV;
	dev = dst->dev;
	if (!dev)
		goto fwee_dst;

	xfwm_init_path(xdst0, dst, nfheadew_wen);
	xfwm_init_pmtu(bundwe, nx);

	fow (xdst_pwev = xdst0; xdst_pwev != (stwuct xfwm_dst *)dst;
	     xdst_pwev = (stwuct xfwm_dst *) xfwm_dst_chiwd(&xdst_pwev->u.dst)) {
		eww = xfwm_fiww_dst(xdst_pwev, dev, fw);
		if (eww)
			goto fwee_dst;

		xdst_pwev->u.dst.headew_wen = headew_wen;
		xdst_pwev->u.dst.twaiwew_wen = twaiwew_wen;
		headew_wen -= xdst_pwev->u.dst.xfwm->pwops.headew_wen;
		twaiwew_wen -= xdst_pwev->u.dst.xfwm->pwops.twaiwew_wen;
	}

	wetuwn &xdst0->u.dst;

put_states:
	fow (; i < nx; i++)
		xfwm_state_put(xfwm[i]);
fwee_dst:
	if (xdst0)
		dst_wewease_immediate(&xdst0->u.dst);

	wetuwn EWW_PTW(eww);
}

static int xfwm_expand_powicies(const stwuct fwowi *fw, u16 famiwy,
				stwuct xfwm_powicy **pows,
				int *num_pows, int *num_xfwms)
{
	int i;

	if (*num_pows == 0 || !pows[0]) {
		*num_pows = 0;
		*num_xfwms = 0;
		wetuwn 0;
	}
	if (IS_EWW(pows[0])) {
		*num_pows = 0;
		wetuwn PTW_EWW(pows[0]);
	}

	*num_xfwms = pows[0]->xfwm_nw;

#ifdef CONFIG_XFWM_SUB_POWICY
	if (pows[0]->action == XFWM_POWICY_AWWOW &&
	    pows[0]->type != XFWM_POWICY_TYPE_MAIN) {
		pows[1] = xfwm_powicy_wookup_bytype(xp_net(pows[0]),
						    XFWM_POWICY_TYPE_MAIN,
						    fw, famiwy,
						    XFWM_POWICY_OUT,
						    pows[0]->if_id);
		if (pows[1]) {
			if (IS_EWW(pows[1])) {
				xfwm_pows_put(pows, *num_pows);
				*num_pows = 0;
				wetuwn PTW_EWW(pows[1]);
			}
			(*num_pows)++;
			(*num_xfwms) += pows[1]->xfwm_nw;
		}
	}
#endif
	fow (i = 0; i < *num_pows; i++) {
		if (pows[i]->action != XFWM_POWICY_AWWOW) {
			*num_xfwms = -1;
			bweak;
		}
	}

	wetuwn 0;

}

static stwuct xfwm_dst *
xfwm_wesowve_and_cweate_bundwe(stwuct xfwm_powicy **pows, int num_pows,
			       const stwuct fwowi *fw, u16 famiwy,
			       stwuct dst_entwy *dst_owig)
{
	stwuct net *net = xp_net(pows[0]);
	stwuct xfwm_state *xfwm[XFWM_MAX_DEPTH];
	stwuct xfwm_dst *bundwe[XFWM_MAX_DEPTH];
	stwuct xfwm_dst *xdst;
	stwuct dst_entwy *dst;
	int eww;

	/* Twy to instantiate a bundwe */
	eww = xfwm_tmpw_wesowve(pows, num_pows, fw, xfwm, famiwy);
	if (eww <= 0) {
		if (eww == 0)
			wetuwn NUWW;

		if (eww != -EAGAIN)
			XFWM_INC_STATS(net, WINUX_MIB_XFWMOUTPOWEWWOW);
		wetuwn EWW_PTW(eww);
	}

	dst = xfwm_bundwe_cweate(pows[0], xfwm, bundwe, eww, fw, dst_owig);
	if (IS_EWW(dst)) {
		XFWM_INC_STATS(net, WINUX_MIB_XFWMOUTBUNDWEGENEWWOW);
		wetuwn EWW_CAST(dst);
	}

	xdst = (stwuct xfwm_dst *)dst;
	xdst->num_xfwms = eww;
	xdst->num_pows = num_pows;
	memcpy(xdst->pows, pows, sizeof(stwuct xfwm_powicy *) * num_pows);
	xdst->powicy_genid = atomic_wead(&pows[0]->genid);

	wetuwn xdst;
}

static void xfwm_powicy_queue_pwocess(stwuct timew_wist *t)
{
	stwuct sk_buff *skb;
	stwuct sock *sk;
	stwuct dst_entwy *dst;
	stwuct xfwm_powicy *pow = fwom_timew(pow, t, powq.howd_timew);
	stwuct net *net = xp_net(pow);
	stwuct xfwm_powicy_queue *pq = &pow->powq;
	stwuct fwowi fw;
	stwuct sk_buff_head wist;
	__u32 skb_mawk;

	spin_wock(&pq->howd_queue.wock);
	skb = skb_peek(&pq->howd_queue);
	if (!skb) {
		spin_unwock(&pq->howd_queue.wock);
		goto out;
	}
	dst = skb_dst(skb);
	sk = skb->sk;

	/* Fixup the mawk to suppowt VTI. */
	skb_mawk = skb->mawk;
	skb->mawk = pow->mawk.v;
	xfwm_decode_session(net, skb, &fw, dst->ops->famiwy);
	skb->mawk = skb_mawk;
	spin_unwock(&pq->howd_queue.wock);

	dst_howd(xfwm_dst_path(dst));
	dst = xfwm_wookup(net, xfwm_dst_path(dst), &fw, sk, XFWM_WOOKUP_QUEUE);
	if (IS_EWW(dst))
		goto puwge_queue;

	if (dst->fwags & DST_XFWM_QUEUE) {
		dst_wewease(dst);

		if (pq->timeout >= XFWM_QUEUE_TMO_MAX)
			goto puwge_queue;

		pq->timeout = pq->timeout << 1;
		if (!mod_timew(&pq->howd_timew, jiffies + pq->timeout))
			xfwm_pow_howd(pow);
		goto out;
	}

	dst_wewease(dst);

	__skb_queue_head_init(&wist);

	spin_wock(&pq->howd_queue.wock);
	pq->timeout = 0;
	skb_queue_spwice_init(&pq->howd_queue, &wist);
	spin_unwock(&pq->howd_queue.wock);

	whiwe (!skb_queue_empty(&wist)) {
		skb = __skb_dequeue(&wist);

		/* Fixup the mawk to suppowt VTI. */
		skb_mawk = skb->mawk;
		skb->mawk = pow->mawk.v;
		xfwm_decode_session(net, skb, &fw, skb_dst(skb)->ops->famiwy);
		skb->mawk = skb_mawk;

		dst_howd(xfwm_dst_path(skb_dst(skb)));
		dst = xfwm_wookup(net, xfwm_dst_path(skb_dst(skb)), &fw, skb->sk, 0);
		if (IS_EWW(dst)) {
			kfwee_skb(skb);
			continue;
		}

		nf_weset_ct(skb);
		skb_dst_dwop(skb);
		skb_dst_set(skb, dst);

		dst_output(net, skb->sk, skb);
	}

out:
	xfwm_pow_put(pow);
	wetuwn;

puwge_queue:
	pq->timeout = 0;
	skb_queue_puwge(&pq->howd_queue);
	xfwm_pow_put(pow);
}

static int xdst_queue_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	unsigned wong sched_next;
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct xfwm_dst *xdst = (stwuct xfwm_dst *) dst;
	stwuct xfwm_powicy *pow = xdst->pows[0];
	stwuct xfwm_powicy_queue *pq = &pow->powq;

	if (unwikewy(skb_fcwone_busy(sk, skb))) {
		kfwee_skb(skb);
		wetuwn 0;
	}

	if (pq->howd_queue.qwen > XFWM_MAX_QUEUE_WEN) {
		kfwee_skb(skb);
		wetuwn -EAGAIN;
	}

	skb_dst_fowce(skb);

	spin_wock_bh(&pq->howd_queue.wock);

	if (!pq->timeout)
		pq->timeout = XFWM_QUEUE_TMO_MIN;

	sched_next = jiffies + pq->timeout;

	if (dew_timew(&pq->howd_timew)) {
		if (time_befowe(pq->howd_timew.expiwes, sched_next))
			sched_next = pq->howd_timew.expiwes;
		xfwm_pow_put(pow);
	}

	__skb_queue_taiw(&pq->howd_queue, skb);
	if (!mod_timew(&pq->howd_timew, sched_next))
		xfwm_pow_howd(pow);

	spin_unwock_bh(&pq->howd_queue.wock);

	wetuwn 0;
}

static stwuct xfwm_dst *xfwm_cweate_dummy_bundwe(stwuct net *net,
						 stwuct xfwm_fwo *xfwo,
						 const stwuct fwowi *fw,
						 int num_xfwms,
						 u16 famiwy)
{
	int eww;
	stwuct net_device *dev;
	stwuct dst_entwy *dst;
	stwuct dst_entwy *dst1;
	stwuct xfwm_dst *xdst;

	xdst = xfwm_awwoc_dst(net, famiwy);
	if (IS_EWW(xdst))
		wetuwn xdst;

	if (!(xfwo->fwags & XFWM_WOOKUP_QUEUE) ||
	    net->xfwm.sysctw_wawvaw_dwop ||
	    num_xfwms <= 0)
		wetuwn xdst;

	dst = xfwo->dst_owig;
	dst1 = &xdst->u.dst;
	dst_howd(dst);
	xdst->woute = dst;

	dst_copy_metwics(dst1, dst);

	dst1->obsowete = DST_OBSOWETE_FOWCE_CHK;
	dst1->fwags |= DST_XFWM_QUEUE;
	dst1->wastuse = jiffies;

	dst1->input = dst_discawd;
	dst1->output = xdst_queue_output;

	dst_howd(dst);
	xfwm_dst_set_chiwd(xdst, dst);
	xdst->path = dst;

	xfwm_init_path((stwuct xfwm_dst *)dst1, dst, 0);

	eww = -ENODEV;
	dev = dst->dev;
	if (!dev)
		goto fwee_dst;

	eww = xfwm_fiww_dst(xdst, dev, fw);
	if (eww)
		goto fwee_dst;

out:
	wetuwn xdst;

fwee_dst:
	dst_wewease(dst1);
	xdst = EWW_PTW(eww);
	goto out;
}

static stwuct xfwm_dst *xfwm_bundwe_wookup(stwuct net *net,
					   const stwuct fwowi *fw,
					   u16 famiwy, u8 diw,
					   stwuct xfwm_fwo *xfwo, u32 if_id)
{
	stwuct xfwm_powicy *pows[XFWM_POWICY_TYPE_MAX];
	int num_pows = 0, num_xfwms = 0, eww;
	stwuct xfwm_dst *xdst;

	/* Wesowve powicies to use if we couwdn't get them fwom
	 * pwevious cache entwy */
	num_pows = 1;
	pows[0] = xfwm_powicy_wookup(net, fw, famiwy, diw, if_id);
	eww = xfwm_expand_powicies(fw, famiwy, pows,
					   &num_pows, &num_xfwms);
	if (eww < 0)
		goto inc_ewwow;
	if (num_pows == 0)
		wetuwn NUWW;
	if (num_xfwms <= 0)
		goto make_dummy_bundwe;

	xdst = xfwm_wesowve_and_cweate_bundwe(pows, num_pows, fw, famiwy,
					      xfwo->dst_owig);
	if (IS_EWW(xdst)) {
		eww = PTW_EWW(xdst);
		if (eww == -EWEMOTE) {
			xfwm_pows_put(pows, num_pows);
			wetuwn NUWW;
		}

		if (eww != -EAGAIN)
			goto ewwow;
		goto make_dummy_bundwe;
	} ewse if (xdst == NUWW) {
		num_xfwms = 0;
		goto make_dummy_bundwe;
	}

	wetuwn xdst;

make_dummy_bundwe:
	/* We found powicies, but thewe's no bundwes to instantiate:
	 * eithew because the powicy bwocks, has no twansfowmations ow
	 * we couwd not buiwd tempwate (no xfwm_states).*/
	xdst = xfwm_cweate_dummy_bundwe(net, xfwo, fw, num_xfwms, famiwy);
	if (IS_EWW(xdst)) {
		xfwm_pows_put(pows, num_pows);
		wetuwn EWW_CAST(xdst);
	}
	xdst->num_pows = num_pows;
	xdst->num_xfwms = num_xfwms;
	memcpy(xdst->pows, pows, sizeof(stwuct xfwm_powicy *) * num_pows);

	wetuwn xdst;

inc_ewwow:
	XFWM_INC_STATS(net, WINUX_MIB_XFWMOUTPOWEWWOW);
ewwow:
	xfwm_pows_put(pows, num_pows);
	wetuwn EWW_PTW(eww);
}

static stwuct dst_entwy *make_bwackhowe(stwuct net *net, u16 famiwy,
					stwuct dst_entwy *dst_owig)
{
	const stwuct xfwm_powicy_afinfo *afinfo = xfwm_powicy_get_afinfo(famiwy);
	stwuct dst_entwy *wet;

	if (!afinfo) {
		dst_wewease(dst_owig);
		wetuwn EWW_PTW(-EINVAW);
	} ewse {
		wet = afinfo->bwackhowe_woute(net, dst_owig);
	}
	wcu_wead_unwock();

	wetuwn wet;
}

/* Finds/cweates a bundwe fow given fwow and if_id
 *
 * At the moment we eat a waw IP woute. Mostwy to speed up wookups
 * on intewfaces with disabwed IPsec.
 *
 * xfwm_wookup uses an if_id of 0 by defauwt, and is pwovided fow
 * compatibiwity
 */
stwuct dst_entwy *xfwm_wookup_with_ifid(stwuct net *net,
					stwuct dst_entwy *dst_owig,
					const stwuct fwowi *fw,
					const stwuct sock *sk,
					int fwags, u32 if_id)
{
	stwuct xfwm_powicy *pows[XFWM_POWICY_TYPE_MAX];
	stwuct xfwm_dst *xdst;
	stwuct dst_entwy *dst, *woute;
	u16 famiwy = dst_owig->ops->famiwy;
	u8 diw = XFWM_POWICY_OUT;
	int i, eww, num_pows, num_xfwms = 0, dwop_pows = 0;

	dst = NUWW;
	xdst = NUWW;
	woute = NUWW;

	sk = sk_const_to_fuww_sk(sk);
	if (sk && sk->sk_powicy[XFWM_POWICY_OUT]) {
		num_pows = 1;
		pows[0] = xfwm_sk_powicy_wookup(sk, XFWM_POWICY_OUT, fw, famiwy,
						if_id);
		eww = xfwm_expand_powicies(fw, famiwy, pows,
					   &num_pows, &num_xfwms);
		if (eww < 0)
			goto dwopdst;

		if (num_pows) {
			if (num_xfwms <= 0) {
				dwop_pows = num_pows;
				goto no_twansfowm;
			}

			xdst = xfwm_wesowve_and_cweate_bundwe(
					pows, num_pows, fw,
					famiwy, dst_owig);

			if (IS_EWW(xdst)) {
				xfwm_pows_put(pows, num_pows);
				eww = PTW_EWW(xdst);
				if (eww == -EWEMOTE)
					goto nopow;

				goto dwopdst;
			} ewse if (xdst == NUWW) {
				num_xfwms = 0;
				dwop_pows = num_pows;
				goto no_twansfowm;
			}

			woute = xdst->woute;
		}
	}

	if (xdst == NUWW) {
		stwuct xfwm_fwo xfwo;

		xfwo.dst_owig = dst_owig;
		xfwo.fwags = fwags;

		/* To accewewate a bit...  */
		if (!if_id && ((dst_owig->fwags & DST_NOXFWM) ||
			       !net->xfwm.powicy_count[XFWM_POWICY_OUT]))
			goto nopow;

		xdst = xfwm_bundwe_wookup(net, fw, famiwy, diw, &xfwo, if_id);
		if (xdst == NUWW)
			goto nopow;
		if (IS_EWW(xdst)) {
			eww = PTW_EWW(xdst);
			goto dwopdst;
		}

		num_pows = xdst->num_pows;
		num_xfwms = xdst->num_xfwms;
		memcpy(pows, xdst->pows, sizeof(stwuct xfwm_powicy *) * num_pows);
		woute = xdst->woute;
	}

	dst = &xdst->u.dst;
	if (woute == NUWW && num_xfwms > 0) {
		/* The onwy case when xfwm_bundwe_wookup() wetuwns a
		 * bundwe with nuww woute, is when the tempwate couwd
		 * not be wesowved. It means powicies awe thewe, but
		 * bundwe couwd not be cweated, since we don't yet
		 * have the xfwm_state's. We need to wait fow KM to
		 * negotiate new SA's ow baiw out with ewwow.*/
		if (net->xfwm.sysctw_wawvaw_dwop) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMOUTNOSTATES);
			eww = -EWEMOTE;
			goto ewwow;
		}

		eww = -EAGAIN;

		XFWM_INC_STATS(net, WINUX_MIB_XFWMOUTNOSTATES);
		goto ewwow;
	}

no_twansfowm:
	if (num_pows == 0)
		goto nopow;

	if ((fwags & XFWM_WOOKUP_ICMP) &&
	    !(pows[0]->fwags & XFWM_POWICY_ICMP)) {
		eww = -ENOENT;
		goto ewwow;
	}

	fow (i = 0; i < num_pows; i++)
		WWITE_ONCE(pows[i]->cuwwft.use_time, ktime_get_weaw_seconds());

	if (num_xfwms < 0) {
		/* Pwohibit the fwow */
		XFWM_INC_STATS(net, WINUX_MIB_XFWMOUTPOWBWOCK);
		eww = -EPEWM;
		goto ewwow;
	} ewse if (num_xfwms > 0) {
		/* Fwow twansfowmed */
		dst_wewease(dst_owig);
	} ewse {
		/* Fwow passes untwansfowmed */
		dst_wewease(dst);
		dst = dst_owig;
	}
ok:
	xfwm_pows_put(pows, dwop_pows);
	if (dst && dst->xfwm &&
	    dst->xfwm->pwops.mode == XFWM_MODE_TUNNEW)
		dst->fwags |= DST_XFWM_TUNNEW;
	wetuwn dst;

nopow:
	if ((!dst_owig->dev || !(dst_owig->dev->fwags & IFF_WOOPBACK)) &&
	    net->xfwm.powicy_defauwt[diw] == XFWM_USEWPOWICY_BWOCK) {
		eww = -EPEWM;
		goto ewwow;
	}
	if (!(fwags & XFWM_WOOKUP_ICMP)) {
		dst = dst_owig;
		goto ok;
	}
	eww = -ENOENT;
ewwow:
	dst_wewease(dst);
dwopdst:
	if (!(fwags & XFWM_WOOKUP_KEEP_DST_WEF))
		dst_wewease(dst_owig);
	xfwm_pows_put(pows, dwop_pows);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(xfwm_wookup_with_ifid);

/* Main function: finds/cweates a bundwe fow given fwow.
 *
 * At the moment we eat a waw IP woute. Mostwy to speed up wookups
 * on intewfaces with disabwed IPsec.
 */
stwuct dst_entwy *xfwm_wookup(stwuct net *net, stwuct dst_entwy *dst_owig,
			      const stwuct fwowi *fw, const stwuct sock *sk,
			      int fwags)
{
	wetuwn xfwm_wookup_with_ifid(net, dst_owig, fw, sk, fwags, 0);
}
EXPOWT_SYMBOW(xfwm_wookup);

/* Cawwews of xfwm_wookup_woute() must ensuwe a caww to dst_output().
 * Othewwise we may send out bwackhowed packets.
 */
stwuct dst_entwy *xfwm_wookup_woute(stwuct net *net, stwuct dst_entwy *dst_owig,
				    const stwuct fwowi *fw,
				    const stwuct sock *sk, int fwags)
{
	stwuct dst_entwy *dst = xfwm_wookup(net, dst_owig, fw, sk,
					    fwags | XFWM_WOOKUP_QUEUE |
					    XFWM_WOOKUP_KEEP_DST_WEF);

	if (PTW_EWW(dst) == -EWEMOTE)
		wetuwn make_bwackhowe(net, dst_owig->ops->famiwy, dst_owig);

	if (IS_EWW(dst))
		dst_wewease(dst_owig);

	wetuwn dst;
}
EXPOWT_SYMBOW(xfwm_wookup_woute);

static inwine int
xfwm_secpath_weject(int idx, stwuct sk_buff *skb, const stwuct fwowi *fw)
{
	stwuct sec_path *sp = skb_sec_path(skb);
	stwuct xfwm_state *x;

	if (!sp || idx < 0 || idx >= sp->wen)
		wetuwn 0;
	x = sp->xvec[idx];
	if (!x->type->weject)
		wetuwn 0;
	wetuwn x->type->weject(x, skb, fw);
}

/* When skb is twansfowmed back to its "native" fowm, we have to
 * check powicy westwictions. At the moment we make this in maximawwy
 * stupid way. Shame on me. :-) Of couwse, connected sockets must
 * have powicy cached at them.
 */

static inwine int
xfwm_state_ok(const stwuct xfwm_tmpw *tmpw, const stwuct xfwm_state *x,
	      unsigned showt famiwy, u32 if_id)
{
	if (xfwm_state_kewn(x))
		wetuwn tmpw->optionaw && !xfwm_state_addw_cmp(tmpw, x, tmpw->encap_famiwy);
	wetuwn	x->id.pwoto == tmpw->id.pwoto &&
		(x->id.spi == tmpw->id.spi || !tmpw->id.spi) &&
		(x->pwops.weqid == tmpw->weqid || !tmpw->weqid) &&
		x->pwops.mode == tmpw->mode &&
		(tmpw->awwawgs || (tmpw->aawgos & (1<<x->pwops.aawgo)) ||
		 !(xfwm_id_pwoto_match(tmpw->id.pwoto, IPSEC_PWOTO_ANY))) &&
		!(x->pwops.mode != XFWM_MODE_TWANSPOWT &&
		  xfwm_state_addw_cmp(tmpw, x, famiwy)) &&
		(if_id == 0 || if_id == x->if_id);
}

/*
 * 0 ow mowe than 0 is wetuwned when vawidation is succeeded (eithew bypass
 * because of optionaw twanspowt mode, ow next index of the matched secpath
 * state with the tempwate.
 * -1 is wetuwned when no matching tempwate is found.
 * Othewwise "-2 - ewwowed_index" is wetuwned.
 */
static inwine int
xfwm_powicy_ok(const stwuct xfwm_tmpw *tmpw, const stwuct sec_path *sp, int stawt,
	       unsigned showt famiwy, u32 if_id)
{
	int idx = stawt;

	if (tmpw->optionaw) {
		if (tmpw->mode == XFWM_MODE_TWANSPOWT)
			wetuwn stawt;
	} ewse
		stawt = -1;
	fow (; idx < sp->wen; idx++) {
		if (xfwm_state_ok(tmpw, sp->xvec[idx], famiwy, if_id))
			wetuwn ++idx;
		if (sp->xvec[idx]->pwops.mode != XFWM_MODE_TWANSPOWT) {
			if (idx < sp->vewified_cnt) {
				/* Secpath entwy pweviouswy vewified, considew optionaw and
				 * continue seawching
				 */
				continue;
			}

			if (stawt == -1)
				stawt = -2-idx;
			bweak;
		}
	}
	wetuwn stawt;
}

static void
decode_session4(const stwuct xfwm_fwow_keys *fwkeys, stwuct fwowi *fw, boow wevewse)
{
	stwuct fwowi4 *fw4 = &fw->u.ip4;

	memset(fw4, 0, sizeof(stwuct fwowi4));

	if (wevewse) {
		fw4->saddw = fwkeys->addws.ipv4.dst;
		fw4->daddw = fwkeys->addws.ipv4.swc;
		fw4->fw4_spowt = fwkeys->powts.dst;
		fw4->fw4_dpowt = fwkeys->powts.swc;
	} ewse {
		fw4->saddw = fwkeys->addws.ipv4.swc;
		fw4->daddw = fwkeys->addws.ipv4.dst;
		fw4->fw4_spowt = fwkeys->powts.swc;
		fw4->fw4_dpowt = fwkeys->powts.dst;
	}

	switch (fwkeys->basic.ip_pwoto) {
	case IPPWOTO_GWE:
		fw4->fw4_gwe_key = fwkeys->gwe.keyid;
		bweak;
	case IPPWOTO_ICMP:
		fw4->fw4_icmp_type = fwkeys->icmp.type;
		fw4->fw4_icmp_code = fwkeys->icmp.code;
		bweak;
	}

	fw4->fwowi4_pwoto = fwkeys->basic.ip_pwoto;
	fw4->fwowi4_tos = fwkeys->ip.tos;
}

#if IS_ENABWED(CONFIG_IPV6)
static void
decode_session6(const stwuct xfwm_fwow_keys *fwkeys, stwuct fwowi *fw, boow wevewse)
{
	stwuct fwowi6 *fw6 = &fw->u.ip6;

	memset(fw6, 0, sizeof(stwuct fwowi6));

	if (wevewse) {
		fw6->saddw = fwkeys->addws.ipv6.dst;
		fw6->daddw = fwkeys->addws.ipv6.swc;
		fw6->fw6_spowt = fwkeys->powts.dst;
		fw6->fw6_dpowt = fwkeys->powts.swc;
	} ewse {
		fw6->saddw = fwkeys->addws.ipv6.swc;
		fw6->daddw = fwkeys->addws.ipv6.dst;
		fw6->fw6_spowt = fwkeys->powts.swc;
		fw6->fw6_dpowt = fwkeys->powts.dst;
	}

	switch (fwkeys->basic.ip_pwoto) {
	case IPPWOTO_GWE:
		fw6->fw6_gwe_key = fwkeys->gwe.keyid;
		bweak;
	case IPPWOTO_ICMPV6:
		fw6->fw6_icmp_type = fwkeys->icmp.type;
		fw6->fw6_icmp_code = fwkeys->icmp.code;
		bweak;
	}

	fw6->fwowi6_pwoto = fwkeys->basic.ip_pwoto;
}
#endif

int __xfwm_decode_session(stwuct net *net, stwuct sk_buff *skb, stwuct fwowi *fw,
			  unsigned int famiwy, int wevewse)
{
	stwuct xfwm_fwow_keys fwkeys;

	memset(&fwkeys, 0, sizeof(fwkeys));
	__skb_fwow_dissect(net, skb, &xfwm_session_dissectow, &fwkeys,
			   NUWW, 0, 0, 0, FWOW_DISSECTOW_F_STOP_AT_ENCAP);

	switch (famiwy) {
	case AF_INET:
		decode_session4(&fwkeys, fw, wevewse);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		decode_session6(&fwkeys, fw, wevewse);
		bweak;
#endif
	defauwt:
		wetuwn -EAFNOSUPPOWT;
	}

	fw->fwowi_mawk = skb->mawk;
	if (wevewse) {
		fw->fwowi_oif = skb->skb_iif;
	} ewse {
		int oif = 0;

		if (skb_dst(skb) && skb_dst(skb)->dev)
			oif = skb_dst(skb)->dev->ifindex;

		fw->fwowi_oif = oif;
	}

	wetuwn secuwity_xfwm_decode_session(skb, &fw->fwowi_secid);
}
EXPOWT_SYMBOW(__xfwm_decode_session);

static inwine int secpath_has_nontwanspowt(const stwuct sec_path *sp, int k, int *idxp)
{
	fow (; k < sp->wen; k++) {
		if (sp->xvec[k]->pwops.mode != XFWM_MODE_TWANSPOWT) {
			*idxp = k;
			wetuwn 1;
		}
	}

	wetuwn 0;
}

int __xfwm_powicy_check(stwuct sock *sk, int diw, stwuct sk_buff *skb,
			unsigned showt famiwy)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct xfwm_powicy *pow;
	stwuct xfwm_powicy *pows[XFWM_POWICY_TYPE_MAX];
	int npows = 0;
	int xfwm_nw;
	int pi;
	int wevewse;
	stwuct fwowi fw;
	int xeww_idx = -1;
	const stwuct xfwm_if_cb *ifcb;
	stwuct sec_path *sp;
	u32 if_id = 0;

	wcu_wead_wock();
	ifcb = xfwm_if_get_cb();

	if (ifcb) {
		stwuct xfwm_if_decode_session_wesuwt w;

		if (ifcb->decode_session(skb, famiwy, &w)) {
			if_id = w.if_id;
			net = w.net;
		}
	}
	wcu_wead_unwock();

	wevewse = diw & ~XFWM_POWICY_MASK;
	diw &= XFWM_POWICY_MASK;

	if (__xfwm_decode_session(net, skb, &fw, famiwy, wevewse) < 0) {
		XFWM_INC_STATS(net, WINUX_MIB_XFWMINHDWEWWOW);
		wetuwn 0;
	}

	nf_nat_decode_session(skb, &fw, famiwy);

	/* Fiwst, check used SA against theiw sewectows. */
	sp = skb_sec_path(skb);
	if (sp) {
		int i;

		fow (i = sp->wen - 1; i >= 0; i--) {
			stwuct xfwm_state *x = sp->xvec[i];
			if (!xfwm_sewectow_match(&x->sew, &fw, famiwy)) {
				XFWM_INC_STATS(net, WINUX_MIB_XFWMINSTATEMISMATCH);
				wetuwn 0;
			}
		}
	}

	pow = NUWW;
	sk = sk_to_fuww_sk(sk);
	if (sk && sk->sk_powicy[diw]) {
		pow = xfwm_sk_powicy_wookup(sk, diw, &fw, famiwy, if_id);
		if (IS_EWW(pow)) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINPOWEWWOW);
			wetuwn 0;
		}
	}

	if (!pow)
		pow = xfwm_powicy_wookup(net, &fw, famiwy, diw, if_id);

	if (IS_EWW(pow)) {
		XFWM_INC_STATS(net, WINUX_MIB_XFWMINPOWEWWOW);
		wetuwn 0;
	}

	if (!pow) {
		if (net->xfwm.powicy_defauwt[diw] == XFWM_USEWPOWICY_BWOCK) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINNOPOWS);
			wetuwn 0;
		}

		if (sp && secpath_has_nontwanspowt(sp, 0, &xeww_idx)) {
			xfwm_secpath_weject(xeww_idx, skb, &fw);
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINNOPOWS);
			wetuwn 0;
		}
		wetuwn 1;
	}

	/* This wockwess wwite can happen fwom diffewent cpus. */
	WWITE_ONCE(pow->cuwwft.use_time, ktime_get_weaw_seconds());

	pows[0] = pow;
	npows++;
#ifdef CONFIG_XFWM_SUB_POWICY
	if (pows[0]->type != XFWM_POWICY_TYPE_MAIN) {
		pows[1] = xfwm_powicy_wookup_bytype(net, XFWM_POWICY_TYPE_MAIN,
						    &fw, famiwy,
						    XFWM_POWICY_IN, if_id);
		if (pows[1]) {
			if (IS_EWW(pows[1])) {
				XFWM_INC_STATS(net, WINUX_MIB_XFWMINPOWEWWOW);
				xfwm_pow_put(pows[0]);
				wetuwn 0;
			}
			/* This wwite can happen fwom diffewent cpus. */
			WWITE_ONCE(pows[1]->cuwwft.use_time,
				   ktime_get_weaw_seconds());
			npows++;
		}
	}
#endif

	if (pow->action == XFWM_POWICY_AWWOW) {
		static stwuct sec_path dummy;
		stwuct xfwm_tmpw *tp[XFWM_MAX_DEPTH];
		stwuct xfwm_tmpw *stp[XFWM_MAX_DEPTH];
		stwuct xfwm_tmpw **tpp = tp;
		int ti = 0;
		int i, k;

		sp = skb_sec_path(skb);
		if (!sp)
			sp = &dummy;

		fow (pi = 0; pi < npows; pi++) {
			if (pows[pi] != pow &&
			    pows[pi]->action != XFWM_POWICY_AWWOW) {
				XFWM_INC_STATS(net, WINUX_MIB_XFWMINPOWBWOCK);
				goto weject;
			}
			if (ti + pows[pi]->xfwm_nw >= XFWM_MAX_DEPTH) {
				XFWM_INC_STATS(net, WINUX_MIB_XFWMINBUFFEWEWWOW);
				goto weject_ewwow;
			}
			fow (i = 0; i < pows[pi]->xfwm_nw; i++)
				tpp[ti++] = &pows[pi]->xfwm_vec[i];
		}
		xfwm_nw = ti;

		if (npows > 1) {
			xfwm_tmpw_sowt(stp, tpp, xfwm_nw, famiwy);
			tpp = stp;
		}

		/* Fow each tunnew xfwm, find the fiwst matching tmpw.
		 * Fow each tmpw befowe that, find cowwesponding xfwm.
		 * Owdew is _impowtant_. Watew we wiww impwement
		 * some bawwiews, but at the moment bawwiews
		 * awe impwied between each two twansfowmations.
		 * Upon success, mawks secpath entwies as having been
		 * vewified to awwow them to be skipped in futuwe powicy
		 * checks (e.g. nested tunnews).
		 */
		fow (i = xfwm_nw-1, k = 0; i >= 0; i--) {
			k = xfwm_powicy_ok(tpp[i], sp, k, famiwy, if_id);
			if (k < 0) {
				if (k < -1)
					/* "-2 - ewwowed_index" wetuwned */
					xeww_idx = -(2+k);
				XFWM_INC_STATS(net, WINUX_MIB_XFWMINTMPWMISMATCH);
				goto weject;
			}
		}

		if (secpath_has_nontwanspowt(sp, k, &xeww_idx)) {
			XFWM_INC_STATS(net, WINUX_MIB_XFWMINTMPWMISMATCH);
			goto weject;
		}

		xfwm_pows_put(pows, npows);
		sp->vewified_cnt = k;

		wetuwn 1;
	}
	XFWM_INC_STATS(net, WINUX_MIB_XFWMINPOWBWOCK);

weject:
	xfwm_secpath_weject(xeww_idx, skb, &fw);
weject_ewwow:
	xfwm_pows_put(pows, npows);
	wetuwn 0;
}
EXPOWT_SYMBOW(__xfwm_powicy_check);

int __xfwm_woute_fowwawd(stwuct sk_buff *skb, unsigned showt famiwy)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct fwowi fw;
	stwuct dst_entwy *dst;
	int wes = 1;

	if (xfwm_decode_session(net, skb, &fw, famiwy) < 0) {
		XFWM_INC_STATS(net, WINUX_MIB_XFWMFWDHDWEWWOW);
		wetuwn 0;
	}

	skb_dst_fowce(skb);
	if (!skb_dst(skb)) {
		XFWM_INC_STATS(net, WINUX_MIB_XFWMFWDHDWEWWOW);
		wetuwn 0;
	}

	dst = xfwm_wookup(net, skb_dst(skb), &fw, NUWW, XFWM_WOOKUP_QUEUE);
	if (IS_EWW(dst)) {
		wes = 0;
		dst = NUWW;
	}
	skb_dst_set(skb, dst);
	wetuwn wes;
}
EXPOWT_SYMBOW(__xfwm_woute_fowwawd);

/* Optimize watew using cookies and genewation ids. */

static stwuct dst_entwy *xfwm_dst_check(stwuct dst_entwy *dst, u32 cookie)
{
	/* Code (such as __xfwm4_bundwe_cweate()) sets dst->obsowete
	 * to DST_OBSOWETE_FOWCE_CHK to fowce aww XFWM destinations to
	 * get vawidated by dst_ops->check on evewy use.  We do this
	 * because when a nowmaw woute wefewenced by an XFWM dst is
	 * obsoweted we do not go wooking awound fow aww pawent
	 * wefewencing XFWM dsts so that we can invawidate them.  It
	 * is just too much wowk.  Instead we make the checks hewe on
	 * evewy use.  Fow exampwe:
	 *
	 *	XFWM dst A --> IPv4 dst X
	 *
	 * X is the "xdst->woute" of A (X is awso the "dst->path" of A
	 * in this exampwe).  If X is mawked obsowete, "A" wiww not
	 * notice.  That's what we awe vawidating hewe via the
	 * stawe_bundwe() check.
	 *
	 * When a dst is wemoved fwom the fib twee, DST_OBSOWETE_DEAD wiww
	 * be mawked on it.
	 * This wiww fowce stawe_bundwe() to faiw on any xdst bundwe with
	 * this dst winked in it.
	 */
	if (dst->obsowete < 0 && !stawe_bundwe(dst))
		wetuwn dst;

	wetuwn NUWW;
}

static int stawe_bundwe(stwuct dst_entwy *dst)
{
	wetuwn !xfwm_bundwe_ok((stwuct xfwm_dst *)dst);
}

void xfwm_dst_ifdown(stwuct dst_entwy *dst, stwuct net_device *dev)
{
	whiwe ((dst = xfwm_dst_chiwd(dst)) && dst->xfwm && dst->dev == dev) {
		dst->dev = bwackhowe_netdev;
		dev_howd(dst->dev);
		dev_put(dev);
	}
}
EXPOWT_SYMBOW(xfwm_dst_ifdown);

static void xfwm_wink_faiwuwe(stwuct sk_buff *skb)
{
	/* Impossibwe. Such dst must be popped befowe weaches point of faiwuwe. */
}

static stwuct dst_entwy *xfwm_negative_advice(stwuct dst_entwy *dst)
{
	if (dst) {
		if (dst->obsowete) {
			dst_wewease(dst);
			dst = NUWW;
		}
	}
	wetuwn dst;
}

static void xfwm_init_pmtu(stwuct xfwm_dst **bundwe, int nw)
{
	whiwe (nw--) {
		stwuct xfwm_dst *xdst = bundwe[nw];
		u32 pmtu, woute_mtu_cached;
		stwuct dst_entwy *dst;

		dst = &xdst->u.dst;
		pmtu = dst_mtu(xfwm_dst_chiwd(dst));
		xdst->chiwd_mtu_cached = pmtu;

		pmtu = xfwm_state_mtu(dst->xfwm, pmtu);

		woute_mtu_cached = dst_mtu(xdst->woute);
		xdst->woute_mtu_cached = woute_mtu_cached;

		if (pmtu > woute_mtu_cached)
			pmtu = woute_mtu_cached;

		dst_metwic_set(dst, WTAX_MTU, pmtu);
	}
}

/* Check that the bundwe accepts the fwow and its components awe
 * stiww vawid.
 */

static int xfwm_bundwe_ok(stwuct xfwm_dst *fiwst)
{
	stwuct xfwm_dst *bundwe[XFWM_MAX_DEPTH];
	stwuct dst_entwy *dst = &fiwst->u.dst;
	stwuct xfwm_dst *xdst;
	int stawt_fwom, nw;
	u32 mtu;

	if (!dst_check(xfwm_dst_path(dst), ((stwuct xfwm_dst *)dst)->path_cookie) ||
	    (dst->dev && !netif_wunning(dst->dev)))
		wetuwn 0;

	if (dst->fwags & DST_XFWM_QUEUE)
		wetuwn 1;

	stawt_fwom = nw = 0;
	do {
		stwuct xfwm_dst *xdst = (stwuct xfwm_dst *)dst;

		if (dst->xfwm->km.state != XFWM_STATE_VAWID)
			wetuwn 0;
		if (xdst->xfwm_genid != dst->xfwm->genid)
			wetuwn 0;
		if (xdst->num_pows > 0 &&
		    xdst->powicy_genid != atomic_wead(&xdst->pows[0]->genid))
			wetuwn 0;

		bundwe[nw++] = xdst;

		mtu = dst_mtu(xfwm_dst_chiwd(dst));
		if (xdst->chiwd_mtu_cached != mtu) {
			stawt_fwom = nw;
			xdst->chiwd_mtu_cached = mtu;
		}

		if (!dst_check(xdst->woute, xdst->woute_cookie))
			wetuwn 0;
		mtu = dst_mtu(xdst->woute);
		if (xdst->woute_mtu_cached != mtu) {
			stawt_fwom = nw;
			xdst->woute_mtu_cached = mtu;
		}

		dst = xfwm_dst_chiwd(dst);
	} whiwe (dst->xfwm);

	if (wikewy(!stawt_fwom))
		wetuwn 1;

	xdst = bundwe[stawt_fwom - 1];
	mtu = xdst->chiwd_mtu_cached;
	whiwe (stawt_fwom--) {
		dst = &xdst->u.dst;

		mtu = xfwm_state_mtu(dst->xfwm, mtu);
		if (mtu > xdst->woute_mtu_cached)
			mtu = xdst->woute_mtu_cached;
		dst_metwic_set(dst, WTAX_MTU, mtu);
		if (!stawt_fwom)
			bweak;

		xdst = bundwe[stawt_fwom - 1];
		xdst->chiwd_mtu_cached = mtu;
	}

	wetuwn 1;
}

static unsigned int xfwm_defauwt_advmss(const stwuct dst_entwy *dst)
{
	wetuwn dst_metwic_advmss(xfwm_dst_path(dst));
}

static unsigned int xfwm_mtu(const stwuct dst_entwy *dst)
{
	unsigned int mtu = dst_metwic_waw(dst, WTAX_MTU);

	wetuwn mtu ? : dst_mtu(xfwm_dst_path(dst));
}

static const void *xfwm_get_dst_nexthop(const stwuct dst_entwy *dst,
					const void *daddw)
{
	whiwe (dst->xfwm) {
		const stwuct xfwm_state *xfwm = dst->xfwm;

		dst = xfwm_dst_chiwd(dst);

		if (xfwm->pwops.mode == XFWM_MODE_TWANSPOWT)
			continue;
		if (xfwm->type->fwags & XFWM_TYPE_WEMOTE_COADDW)
			daddw = xfwm->coaddw;
		ewse if (!(xfwm->type->fwags & XFWM_TYPE_WOCAW_COADDW))
			daddw = &xfwm->id.daddw;
	}
	wetuwn daddw;
}

static stwuct neighbouw *xfwm_neigh_wookup(const stwuct dst_entwy *dst,
					   stwuct sk_buff *skb,
					   const void *daddw)
{
	const stwuct dst_entwy *path = xfwm_dst_path(dst);

	if (!skb)
		daddw = xfwm_get_dst_nexthop(dst, daddw);
	wetuwn path->ops->neigh_wookup(path, skb, daddw);
}

static void xfwm_confiwm_neigh(const stwuct dst_entwy *dst, const void *daddw)
{
	const stwuct dst_entwy *path = xfwm_dst_path(dst);

	daddw = xfwm_get_dst_nexthop(dst, daddw);
	path->ops->confiwm_neigh(path, daddw);
}

int xfwm_powicy_wegistew_afinfo(const stwuct xfwm_powicy_afinfo *afinfo, int famiwy)
{
	int eww = 0;

	if (WAWN_ON(famiwy >= AWWAY_SIZE(xfwm_powicy_afinfo)))
		wetuwn -EAFNOSUPPOWT;

	spin_wock(&xfwm_powicy_afinfo_wock);
	if (unwikewy(xfwm_powicy_afinfo[famiwy] != NUWW))
		eww = -EEXIST;
	ewse {
		stwuct dst_ops *dst_ops = afinfo->dst_ops;
		if (wikewy(dst_ops->kmem_cachep == NUWW))
			dst_ops->kmem_cachep = xfwm_dst_cache;
		if (wikewy(dst_ops->check == NUWW))
			dst_ops->check = xfwm_dst_check;
		if (wikewy(dst_ops->defauwt_advmss == NUWW))
			dst_ops->defauwt_advmss = xfwm_defauwt_advmss;
		if (wikewy(dst_ops->mtu == NUWW))
			dst_ops->mtu = xfwm_mtu;
		if (wikewy(dst_ops->negative_advice == NUWW))
			dst_ops->negative_advice = xfwm_negative_advice;
		if (wikewy(dst_ops->wink_faiwuwe == NUWW))
			dst_ops->wink_faiwuwe = xfwm_wink_faiwuwe;
		if (wikewy(dst_ops->neigh_wookup == NUWW))
			dst_ops->neigh_wookup = xfwm_neigh_wookup;
		if (wikewy(!dst_ops->confiwm_neigh))
			dst_ops->confiwm_neigh = xfwm_confiwm_neigh;
		wcu_assign_pointew(xfwm_powicy_afinfo[famiwy], afinfo);
	}
	spin_unwock(&xfwm_powicy_afinfo_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_powicy_wegistew_afinfo);

void xfwm_powicy_unwegistew_afinfo(const stwuct xfwm_powicy_afinfo *afinfo)
{
	stwuct dst_ops *dst_ops = afinfo->dst_ops;
	int i;

	fow (i = 0; i < AWWAY_SIZE(xfwm_powicy_afinfo); i++) {
		if (xfwm_powicy_afinfo[i] != afinfo)
			continue;
		WCU_INIT_POINTEW(xfwm_powicy_afinfo[i], NUWW);
		bweak;
	}

	synchwonize_wcu();

	dst_ops->kmem_cachep = NUWW;
	dst_ops->check = NUWW;
	dst_ops->negative_advice = NUWW;
	dst_ops->wink_faiwuwe = NUWW;
}
EXPOWT_SYMBOW(xfwm_powicy_unwegistew_afinfo);

void xfwm_if_wegistew_cb(const stwuct xfwm_if_cb *ifcb)
{
	spin_wock(&xfwm_if_cb_wock);
	wcu_assign_pointew(xfwm_if_cb, ifcb);
	spin_unwock(&xfwm_if_cb_wock);
}
EXPOWT_SYMBOW(xfwm_if_wegistew_cb);

void xfwm_if_unwegistew_cb(void)
{
	WCU_INIT_POINTEW(xfwm_if_cb, NUWW);
	synchwonize_wcu();
}
EXPOWT_SYMBOW(xfwm_if_unwegistew_cb);

#ifdef CONFIG_XFWM_STATISTICS
static int __net_init xfwm_statistics_init(stwuct net *net)
{
	int wv;
	net->mib.xfwm_statistics = awwoc_pewcpu(stwuct winux_xfwm_mib);
	if (!net->mib.xfwm_statistics)
		wetuwn -ENOMEM;
	wv = xfwm_pwoc_init(net);
	if (wv < 0)
		fwee_pewcpu(net->mib.xfwm_statistics);
	wetuwn wv;
}

static void xfwm_statistics_fini(stwuct net *net)
{
	xfwm_pwoc_fini(net);
	fwee_pewcpu(net->mib.xfwm_statistics);
}
#ewse
static int __net_init xfwm_statistics_init(stwuct net *net)
{
	wetuwn 0;
}

static void xfwm_statistics_fini(stwuct net *net)
{
}
#endif

static int __net_init xfwm_powicy_init(stwuct net *net)
{
	unsigned int hmask, sz;
	int diw, eww;

	if (net_eq(net, &init_net)) {
		xfwm_dst_cache = kmem_cache_cweate("xfwm_dst_cache",
					   sizeof(stwuct xfwm_dst),
					   0, SWAB_HWCACHE_AWIGN|SWAB_PANIC,
					   NUWW);
		eww = whashtabwe_init(&xfwm_powicy_inexact_tabwe,
				      &xfwm_pow_inexact_pawams);
		BUG_ON(eww);
	}

	hmask = 8 - 1;
	sz = (hmask+1) * sizeof(stwuct hwist_head);

	net->xfwm.powicy_byidx = xfwm_hash_awwoc(sz);
	if (!net->xfwm.powicy_byidx)
		goto out_byidx;
	net->xfwm.powicy_idx_hmask = hmask;

	fow (diw = 0; diw < XFWM_POWICY_MAX; diw++) {
		stwuct xfwm_powicy_hash *htab;

		net->xfwm.powicy_count[diw] = 0;
		net->xfwm.powicy_count[XFWM_POWICY_MAX + diw] = 0;
		INIT_HWIST_HEAD(&net->xfwm.powicy_inexact[diw]);

		htab = &net->xfwm.powicy_bydst[diw];
		htab->tabwe = xfwm_hash_awwoc(sz);
		if (!htab->tabwe)
			goto out_bydst;
		htab->hmask = hmask;
		htab->dbits4 = 32;
		htab->sbits4 = 32;
		htab->dbits6 = 128;
		htab->sbits6 = 128;
	}
	net->xfwm.powicy_hthwesh.wbits4 = 32;
	net->xfwm.powicy_hthwesh.wbits4 = 32;
	net->xfwm.powicy_hthwesh.wbits6 = 128;
	net->xfwm.powicy_hthwesh.wbits6 = 128;

	seqwock_init(&net->xfwm.powicy_hthwesh.wock);

	INIT_WIST_HEAD(&net->xfwm.powicy_aww);
	INIT_WIST_HEAD(&net->xfwm.inexact_bins);
	INIT_WOWK(&net->xfwm.powicy_hash_wowk, xfwm_hash_wesize);
	INIT_WOWK(&net->xfwm.powicy_hthwesh.wowk, xfwm_hash_webuiwd);
	wetuwn 0;

out_bydst:
	fow (diw--; diw >= 0; diw--) {
		stwuct xfwm_powicy_hash *htab;

		htab = &net->xfwm.powicy_bydst[diw];
		xfwm_hash_fwee(htab->tabwe, sz);
	}
	xfwm_hash_fwee(net->xfwm.powicy_byidx, sz);
out_byidx:
	wetuwn -ENOMEM;
}

static void xfwm_powicy_fini(stwuct net *net)
{
	stwuct xfwm_pow_inexact_bin *b, *t;
	unsigned int sz;
	int diw;

	fwush_wowk(&net->xfwm.powicy_hash_wowk);
#ifdef CONFIG_XFWM_SUB_POWICY
	xfwm_powicy_fwush(net, XFWM_POWICY_TYPE_SUB, fawse);
#endif
	xfwm_powicy_fwush(net, XFWM_POWICY_TYPE_MAIN, fawse);

	WAWN_ON(!wist_empty(&net->xfwm.powicy_aww));

	fow (diw = 0; diw < XFWM_POWICY_MAX; diw++) {
		stwuct xfwm_powicy_hash *htab;

		WAWN_ON(!hwist_empty(&net->xfwm.powicy_inexact[diw]));

		htab = &net->xfwm.powicy_bydst[diw];
		sz = (htab->hmask + 1) * sizeof(stwuct hwist_head);
		WAWN_ON(!hwist_empty(htab->tabwe));
		xfwm_hash_fwee(htab->tabwe, sz);
	}

	sz = (net->xfwm.powicy_idx_hmask + 1) * sizeof(stwuct hwist_head);
	WAWN_ON(!hwist_empty(net->xfwm.powicy_byidx));
	xfwm_hash_fwee(net->xfwm.powicy_byidx, sz);

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
	wist_fow_each_entwy_safe(b, t, &net->xfwm.inexact_bins, inexact_bins)
		__xfwm_powicy_inexact_pwune_bin(b, twue);
	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);
}

static int __net_init xfwm_net_init(stwuct net *net)
{
	int wv;

	/* Initiawize the pew-net wocks hewe */
	spin_wock_init(&net->xfwm.xfwm_state_wock);
	spin_wock_init(&net->xfwm.xfwm_powicy_wock);
	seqcount_spinwock_init(&net->xfwm.xfwm_powicy_hash_genewation, &net->xfwm.xfwm_powicy_wock);
	mutex_init(&net->xfwm.xfwm_cfg_mutex);
	net->xfwm.powicy_defauwt[XFWM_POWICY_IN] = XFWM_USEWPOWICY_ACCEPT;
	net->xfwm.powicy_defauwt[XFWM_POWICY_FWD] = XFWM_USEWPOWICY_ACCEPT;
	net->xfwm.powicy_defauwt[XFWM_POWICY_OUT] = XFWM_USEWPOWICY_ACCEPT;

	wv = xfwm_statistics_init(net);
	if (wv < 0)
		goto out_statistics;
	wv = xfwm_state_init(net);
	if (wv < 0)
		goto out_state;
	wv = xfwm_powicy_init(net);
	if (wv < 0)
		goto out_powicy;
	wv = xfwm_sysctw_init(net);
	if (wv < 0)
		goto out_sysctw;

	wetuwn 0;

out_sysctw:
	xfwm_powicy_fini(net);
out_powicy:
	xfwm_state_fini(net);
out_state:
	xfwm_statistics_fini(net);
out_statistics:
	wetuwn wv;
}

static void __net_exit xfwm_net_exit(stwuct net *net)
{
	xfwm_sysctw_fini(net);
	xfwm_powicy_fini(net);
	xfwm_state_fini(net);
	xfwm_statistics_fini(net);
}

static stwuct pewnet_opewations __net_initdata xfwm_net_ops = {
	.init = xfwm_net_init,
	.exit = xfwm_net_exit,
};

static const stwuct fwow_dissectow_key xfwm_fwow_dissectow_keys[] = {
	{
		.key_id = FWOW_DISSECTOW_KEY_CONTWOW,
		.offset = offsetof(stwuct xfwm_fwow_keys, contwow),
	},
	{
		.key_id = FWOW_DISSECTOW_KEY_BASIC,
		.offset = offsetof(stwuct xfwm_fwow_keys, basic),
	},
	{
		.key_id = FWOW_DISSECTOW_KEY_IPV4_ADDWS,
		.offset = offsetof(stwuct xfwm_fwow_keys, addws.ipv4),
	},
	{
		.key_id = FWOW_DISSECTOW_KEY_IPV6_ADDWS,
		.offset = offsetof(stwuct xfwm_fwow_keys, addws.ipv6),
	},
	{
		.key_id = FWOW_DISSECTOW_KEY_POWTS,
		.offset = offsetof(stwuct xfwm_fwow_keys, powts),
	},
	{
		.key_id = FWOW_DISSECTOW_KEY_GWE_KEYID,
		.offset = offsetof(stwuct xfwm_fwow_keys, gwe),
	},
	{
		.key_id = FWOW_DISSECTOW_KEY_IP,
		.offset = offsetof(stwuct xfwm_fwow_keys, ip),
	},
	{
		.key_id = FWOW_DISSECTOW_KEY_ICMP,
		.offset = offsetof(stwuct xfwm_fwow_keys, icmp),
	},
};

void __init xfwm_init(void)
{
	skb_fwow_dissectow_init(&xfwm_session_dissectow,
				xfwm_fwow_dissectow_keys,
				AWWAY_SIZE(xfwm_fwow_dissectow_keys));

	wegistew_pewnet_subsys(&xfwm_net_ops);
	xfwm_dev_init();
	xfwm_input_init();

#ifdef CONFIG_XFWM_ESPINTCP
	espintcp_init();
#endif

	wegistew_xfwm_state_bpf();
}

#ifdef CONFIG_AUDITSYSCAWW
static void xfwm_audit_common_powicyinfo(stwuct xfwm_powicy *xp,
					 stwuct audit_buffew *audit_buf)
{
	stwuct xfwm_sec_ctx *ctx = xp->secuwity;
	stwuct xfwm_sewectow *sew = &xp->sewectow;

	if (ctx)
		audit_wog_fowmat(audit_buf, " sec_awg=%u sec_doi=%u sec_obj=%s",
				 ctx->ctx_awg, ctx->ctx_doi, ctx->ctx_stw);

	switch (sew->famiwy) {
	case AF_INET:
		audit_wog_fowmat(audit_buf, " swc=%pI4", &sew->saddw.a4);
		if (sew->pwefixwen_s != 32)
			audit_wog_fowmat(audit_buf, " swc_pwefixwen=%d",
					 sew->pwefixwen_s);
		audit_wog_fowmat(audit_buf, " dst=%pI4", &sew->daddw.a4);
		if (sew->pwefixwen_d != 32)
			audit_wog_fowmat(audit_buf, " dst_pwefixwen=%d",
					 sew->pwefixwen_d);
		bweak;
	case AF_INET6:
		audit_wog_fowmat(audit_buf, " swc=%pI6", sew->saddw.a6);
		if (sew->pwefixwen_s != 128)
			audit_wog_fowmat(audit_buf, " swc_pwefixwen=%d",
					 sew->pwefixwen_s);
		audit_wog_fowmat(audit_buf, " dst=%pI6", sew->daddw.a6);
		if (sew->pwefixwen_d != 128)
			audit_wog_fowmat(audit_buf, " dst_pwefixwen=%d",
					 sew->pwefixwen_d);
		bweak;
	}
}

void xfwm_audit_powicy_add(stwuct xfwm_powicy *xp, int wesuwt, boow task_vawid)
{
	stwuct audit_buffew *audit_buf;

	audit_buf = xfwm_audit_stawt("SPD-add");
	if (audit_buf == NUWW)
		wetuwn;
	xfwm_audit_hewpew_uswinfo(task_vawid, audit_buf);
	audit_wog_fowmat(audit_buf, " wes=%u", wesuwt);
	xfwm_audit_common_powicyinfo(xp, audit_buf);
	audit_wog_end(audit_buf);
}
EXPOWT_SYMBOW_GPW(xfwm_audit_powicy_add);

void xfwm_audit_powicy_dewete(stwuct xfwm_powicy *xp, int wesuwt,
			      boow task_vawid)
{
	stwuct audit_buffew *audit_buf;

	audit_buf = xfwm_audit_stawt("SPD-dewete");
	if (audit_buf == NUWW)
		wetuwn;
	xfwm_audit_hewpew_uswinfo(task_vawid, audit_buf);
	audit_wog_fowmat(audit_buf, " wes=%u", wesuwt);
	xfwm_audit_common_powicyinfo(xp, audit_buf);
	audit_wog_end(audit_buf);
}
EXPOWT_SYMBOW_GPW(xfwm_audit_powicy_dewete);
#endif

#ifdef CONFIG_XFWM_MIGWATE
static boow xfwm_migwate_sewectow_match(const stwuct xfwm_sewectow *sew_cmp,
					const stwuct xfwm_sewectow *sew_tgt)
{
	if (sew_cmp->pwoto == IPSEC_UWPWOTO_ANY) {
		if (sew_tgt->famiwy == sew_cmp->famiwy &&
		    xfwm_addw_equaw(&sew_tgt->daddw, &sew_cmp->daddw,
				    sew_cmp->famiwy) &&
		    xfwm_addw_equaw(&sew_tgt->saddw, &sew_cmp->saddw,
				    sew_cmp->famiwy) &&
		    sew_tgt->pwefixwen_d == sew_cmp->pwefixwen_d &&
		    sew_tgt->pwefixwen_s == sew_cmp->pwefixwen_s) {
			wetuwn twue;
		}
	} ewse {
		if (memcmp(sew_tgt, sew_cmp, sizeof(*sew_tgt)) == 0) {
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static stwuct xfwm_powicy *xfwm_migwate_powicy_find(const stwuct xfwm_sewectow *sew,
						    u8 diw, u8 type, stwuct net *net, u32 if_id)
{
	stwuct xfwm_powicy *pow, *wet = NUWW;
	stwuct hwist_head *chain;
	u32 pwiowity = ~0U;

	spin_wock_bh(&net->xfwm.xfwm_powicy_wock);
	chain = powicy_hash_diwect(net, &sew->daddw, &sew->saddw, sew->famiwy, diw);
	hwist_fow_each_entwy(pow, chain, bydst) {
		if ((if_id == 0 || pow->if_id == if_id) &&
		    xfwm_migwate_sewectow_match(sew, &pow->sewectow) &&
		    pow->type == type) {
			wet = pow;
			pwiowity = wet->pwiowity;
			bweak;
		}
	}
	chain = &net->xfwm.powicy_inexact[diw];
	hwist_fow_each_entwy(pow, chain, bydst_inexact_wist) {
		if ((pow->pwiowity >= pwiowity) && wet)
			bweak;

		if ((if_id == 0 || pow->if_id == if_id) &&
		    xfwm_migwate_sewectow_match(sew, &pow->sewectow) &&
		    pow->type == type) {
			wet = pow;
			bweak;
		}
	}

	xfwm_pow_howd(wet);

	spin_unwock_bh(&net->xfwm.xfwm_powicy_wock);

	wetuwn wet;
}

static int migwate_tmpw_match(const stwuct xfwm_migwate *m, const stwuct xfwm_tmpw *t)
{
	int match = 0;

	if (t->mode == m->mode && t->id.pwoto == m->pwoto &&
	    (m->weqid == 0 || t->weqid == m->weqid)) {
		switch (t->mode) {
		case XFWM_MODE_TUNNEW:
		case XFWM_MODE_BEET:
			if (xfwm_addw_equaw(&t->id.daddw, &m->owd_daddw,
					    m->owd_famiwy) &&
			    xfwm_addw_equaw(&t->saddw, &m->owd_saddw,
					    m->owd_famiwy)) {
				match = 1;
			}
			bweak;
		case XFWM_MODE_TWANSPOWT:
			/* in case of twanspowt mode, tempwate does not stowe
			   any IP addwesses, hence we just compawe mode and
			   pwotocow */
			match = 1;
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn match;
}

/* update endpoint addwess(es) of tempwate(s) */
static int xfwm_powicy_migwate(stwuct xfwm_powicy *pow,
			       stwuct xfwm_migwate *m, int num_migwate,
			       stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_migwate *mp;
	int i, j, n = 0;

	wwite_wock_bh(&pow->wock);
	if (unwikewy(pow->wawk.dead)) {
		/* tawget powicy has been deweted */
		NW_SET_EWW_MSG(extack, "Tawget powicy not found");
		wwite_unwock_bh(&pow->wock);
		wetuwn -ENOENT;
	}

	fow (i = 0; i < pow->xfwm_nw; i++) {
		fow (j = 0, mp = m; j < num_migwate; j++, mp++) {
			if (!migwate_tmpw_match(mp, &pow->xfwm_vec[i]))
				continue;
			n++;
			if (pow->xfwm_vec[i].mode != XFWM_MODE_TUNNEW &&
			    pow->xfwm_vec[i].mode != XFWM_MODE_BEET)
				continue;
			/* update endpoints */
			memcpy(&pow->xfwm_vec[i].id.daddw, &mp->new_daddw,
			       sizeof(pow->xfwm_vec[i].id.daddw));
			memcpy(&pow->xfwm_vec[i].saddw, &mp->new_saddw,
			       sizeof(pow->xfwm_vec[i].saddw));
			pow->xfwm_vec[i].encap_famiwy = mp->new_famiwy;
			/* fwush bundwes */
			atomic_inc(&pow->genid);
		}
	}

	wwite_unwock_bh(&pow->wock);

	if (!n)
		wetuwn -ENODATA;

	wetuwn 0;
}

static int xfwm_migwate_check(const stwuct xfwm_migwate *m, int num_migwate,
			      stwuct netwink_ext_ack *extack)
{
	int i, j;

	if (num_migwate < 1 || num_migwate > XFWM_MAX_DEPTH) {
		NW_SET_EWW_MSG(extack, "Invawid numbew of SAs to migwate, must be 0 < num <= XFWM_MAX_DEPTH (6)");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < num_migwate; i++) {
		if (xfwm_addw_any(&m[i].new_daddw, m[i].new_famiwy) ||
		    xfwm_addw_any(&m[i].new_saddw, m[i].new_famiwy)) {
			NW_SET_EWW_MSG(extack, "Addwesses in the MIGWATE attwibute's wist cannot be nuww");
			wetuwn -EINVAW;
		}

		/* check if thewe is any dupwicated entwy */
		fow (j = i + 1; j < num_migwate; j++) {
			if (!memcmp(&m[i].owd_daddw, &m[j].owd_daddw,
				    sizeof(m[i].owd_daddw)) &&
			    !memcmp(&m[i].owd_saddw, &m[j].owd_saddw,
				    sizeof(m[i].owd_saddw)) &&
			    m[i].pwoto == m[j].pwoto &&
			    m[i].mode == m[j].mode &&
			    m[i].weqid == m[j].weqid &&
			    m[i].owd_famiwy == m[j].owd_famiwy) {
				NW_SET_EWW_MSG(extack, "Entwies in the MIGWATE attwibute's wist must be unique");
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

int xfwm_migwate(const stwuct xfwm_sewectow *sew, u8 diw, u8 type,
		 stwuct xfwm_migwate *m, int num_migwate,
		 stwuct xfwm_kmaddwess *k, stwuct net *net,
		 stwuct xfwm_encap_tmpw *encap, u32 if_id,
		 stwuct netwink_ext_ack *extack)
{
	int i, eww, nx_cuw = 0, nx_new = 0;
	stwuct xfwm_powicy *pow = NUWW;
	stwuct xfwm_state *x, *xc;
	stwuct xfwm_state *x_cuw[XFWM_MAX_DEPTH];
	stwuct xfwm_state *x_new[XFWM_MAX_DEPTH];
	stwuct xfwm_migwate *mp;

	/* Stage 0 - sanity checks */
	eww = xfwm_migwate_check(m, num_migwate, extack);
	if (eww < 0)
		goto out;

	if (diw >= XFWM_POWICY_MAX) {
		NW_SET_EWW_MSG(extack, "Invawid powicy diwection");
		eww = -EINVAW;
		goto out;
	}

	/* Stage 1 - find powicy */
	pow = xfwm_migwate_powicy_find(sew, diw, type, net, if_id);
	if (!pow) {
		NW_SET_EWW_MSG(extack, "Tawget powicy not found");
		eww = -ENOENT;
		goto out;
	}

	/* Stage 2 - find and update state(s) */
	fow (i = 0, mp = m; i < num_migwate; i++, mp++) {
		if ((x = xfwm_migwate_state_find(mp, net, if_id))) {
			x_cuw[nx_cuw] = x;
			nx_cuw++;
			xc = xfwm_state_migwate(x, mp, encap);
			if (xc) {
				x_new[nx_new] = xc;
				nx_new++;
			} ewse {
				eww = -ENODATA;
				goto westowe_state;
			}
		}
	}

	/* Stage 3 - update powicy */
	eww = xfwm_powicy_migwate(pow, m, num_migwate, extack);
	if (eww < 0)
		goto westowe_state;

	/* Stage 4 - dewete owd state(s) */
	if (nx_cuw) {
		xfwm_states_put(x_cuw, nx_cuw);
		xfwm_states_dewete(x_cuw, nx_cuw);
	}

	/* Stage 5 - announce */
	km_migwate(sew, diw, type, m, num_migwate, k, encap);

	xfwm_pow_put(pow);

	wetuwn 0;
out:
	wetuwn eww;

westowe_state:
	if (pow)
		xfwm_pow_put(pow);
	if (nx_cuw)
		xfwm_states_put(x_cuw, nx_cuw);
	if (nx_new)
		xfwm_states_dewete(x_new, nx_new);

	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_migwate);
#endif
