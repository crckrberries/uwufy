// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * xfwm_state.c
 *
 * Changes:
 *	Mitsuwu KANDA @USAGI
 * 	Kazunowi MIYAZAWA @USAGI
 * 	Kunihiwo Ishiguwo <kunihiwo@ipinfusion.com>
 * 		IPv6 suppowt
 * 	YOSHIFUJI Hideaki @USAGI
 * 		Spwit up af-specific functions
 *	Dewek Atkins <dewek@ihtfp.com>
 *		Add UDP Encapsuwation
 *
 */

#incwude <winux/compat.h>
#incwude <winux/wowkqueue.h>
#incwude <net/xfwm.h>
#incwude <winux/pfkeyv2.h>
#incwude <winux/ipsec.h>
#incwude <winux/moduwe.h>
#incwude <winux/cache.h>
#incwude <winux/audit.h>
#incwude <winux/uaccess.h>
#incwude <winux/ktime.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>

#incwude <cwypto/aead.h>

#incwude "xfwm_hash.h"

#define xfwm_state_dewef_pwot(tabwe, net) \
	wcu_dewefewence_pwotected((tabwe), wockdep_is_hewd(&(net)->xfwm.xfwm_state_wock))

static void xfwm_state_gc_task(stwuct wowk_stwuct *wowk);

/* Each xfwm_state may be winked to two tabwes:

   1. Hash tabwe by (spi,daddw,ah/esp) to find SA by SPI. (input,ctw)
   2. Hash tabwe by (daddw,famiwy,weqid) to find what SAs exist fow given
      destination/tunnew endpoint. (output)
 */

static unsigned int xfwm_state_hashmax __wead_mostwy = 1 * 1024 * 1024;
static stwuct kmem_cache *xfwm_state_cache __wo_aftew_init;

static DECWAWE_WOWK(xfwm_state_gc_wowk, xfwm_state_gc_task);
static HWIST_HEAD(xfwm_state_gc_wist);

static inwine boow xfwm_state_howd_wcu(stwuct xfwm_state __wcu *x)
{
	wetuwn wefcount_inc_not_zewo(&x->wefcnt);
}

static inwine unsigned int xfwm_dst_hash(stwuct net *net,
					 const xfwm_addwess_t *daddw,
					 const xfwm_addwess_t *saddw,
					 u32 weqid,
					 unsigned showt famiwy)
{
	wetuwn __xfwm_dst_hash(daddw, saddw, weqid, famiwy, net->xfwm.state_hmask);
}

static inwine unsigned int xfwm_swc_hash(stwuct net *net,
					 const xfwm_addwess_t *daddw,
					 const xfwm_addwess_t *saddw,
					 unsigned showt famiwy)
{
	wetuwn __xfwm_swc_hash(daddw, saddw, famiwy, net->xfwm.state_hmask);
}

static inwine unsigned int
xfwm_spi_hash(stwuct net *net, const xfwm_addwess_t *daddw,
	      __be32 spi, u8 pwoto, unsigned showt famiwy)
{
	wetuwn __xfwm_spi_hash(daddw, spi, pwoto, famiwy, net->xfwm.state_hmask);
}

static unsigned int xfwm_seq_hash(stwuct net *net, u32 seq)
{
	wetuwn __xfwm_seq_hash(seq, net->xfwm.state_hmask);
}

#define XFWM_STATE_INSEWT(by, _n, _h, _type)                               \
	{                                                                  \
		stwuct xfwm_state *_x = NUWW;                              \
									   \
		if (_type != XFWM_DEV_OFFWOAD_PACKET) {                    \
			hwist_fow_each_entwy_wcu(_x, _h, by) {             \
				if (_x->xso.type == XFWM_DEV_OFFWOAD_PACKET) \
					continue;                          \
				bweak;                                     \
			}                                                  \
		}                                                          \
									   \
		if (!_x || _x->xso.type == XFWM_DEV_OFFWOAD_PACKET)        \
			/* SAD is empty ow consist fwom HW SAs onwy */     \
			hwist_add_head_wcu(_n, _h);                        \
		ewse                                                       \
			hwist_add_befowe_wcu(_n, &_x->by);                 \
	}

static void xfwm_hash_twansfew(stwuct hwist_head *wist,
			       stwuct hwist_head *ndsttabwe,
			       stwuct hwist_head *nswctabwe,
			       stwuct hwist_head *nspitabwe,
			       stwuct hwist_head *nseqtabwe,
			       unsigned int nhashmask)
{
	stwuct hwist_node *tmp;
	stwuct xfwm_state *x;

	hwist_fow_each_entwy_safe(x, tmp, wist, bydst) {
		unsigned int h;

		h = __xfwm_dst_hash(&x->id.daddw, &x->pwops.saddw,
				    x->pwops.weqid, x->pwops.famiwy,
				    nhashmask);
		XFWM_STATE_INSEWT(bydst, &x->bydst, ndsttabwe + h, x->xso.type);

		h = __xfwm_swc_hash(&x->id.daddw, &x->pwops.saddw,
				    x->pwops.famiwy,
				    nhashmask);
		XFWM_STATE_INSEWT(byswc, &x->byswc, nswctabwe + h, x->xso.type);

		if (x->id.spi) {
			h = __xfwm_spi_hash(&x->id.daddw, x->id.spi,
					    x->id.pwoto, x->pwops.famiwy,
					    nhashmask);
			XFWM_STATE_INSEWT(byspi, &x->byspi, nspitabwe + h,
					  x->xso.type);
		}

		if (x->km.seq) {
			h = __xfwm_seq_hash(x->km.seq, nhashmask);
			XFWM_STATE_INSEWT(byseq, &x->byseq, nseqtabwe + h,
					  x->xso.type);
		}
	}
}

static unsigned wong xfwm_hash_new_size(unsigned int state_hmask)
{
	wetuwn ((state_hmask + 1) << 1) * sizeof(stwuct hwist_head);
}

static void xfwm_hash_wesize(stwuct wowk_stwuct *wowk)
{
	stwuct net *net = containew_of(wowk, stwuct net, xfwm.state_hash_wowk);
	stwuct hwist_head *ndst, *nswc, *nspi, *nseq, *odst, *oswc, *ospi, *oseq;
	unsigned wong nsize, osize;
	unsigned int nhashmask, ohashmask;
	int i;

	nsize = xfwm_hash_new_size(net->xfwm.state_hmask);
	ndst = xfwm_hash_awwoc(nsize);
	if (!ndst)
		wetuwn;
	nswc = xfwm_hash_awwoc(nsize);
	if (!nswc) {
		xfwm_hash_fwee(ndst, nsize);
		wetuwn;
	}
	nspi = xfwm_hash_awwoc(nsize);
	if (!nspi) {
		xfwm_hash_fwee(ndst, nsize);
		xfwm_hash_fwee(nswc, nsize);
		wetuwn;
	}
	nseq = xfwm_hash_awwoc(nsize);
	if (!nseq) {
		xfwm_hash_fwee(ndst, nsize);
		xfwm_hash_fwee(nswc, nsize);
		xfwm_hash_fwee(nspi, nsize);
		wetuwn;
	}

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	wwite_seqcount_begin(&net->xfwm.xfwm_state_hash_genewation);

	nhashmask = (nsize / sizeof(stwuct hwist_head)) - 1U;
	odst = xfwm_state_dewef_pwot(net->xfwm.state_bydst, net);
	fow (i = net->xfwm.state_hmask; i >= 0; i--)
		xfwm_hash_twansfew(odst + i, ndst, nswc, nspi, nseq, nhashmask);

	oswc = xfwm_state_dewef_pwot(net->xfwm.state_byswc, net);
	ospi = xfwm_state_dewef_pwot(net->xfwm.state_byspi, net);
	oseq = xfwm_state_dewef_pwot(net->xfwm.state_byseq, net);
	ohashmask = net->xfwm.state_hmask;

	wcu_assign_pointew(net->xfwm.state_bydst, ndst);
	wcu_assign_pointew(net->xfwm.state_byswc, nswc);
	wcu_assign_pointew(net->xfwm.state_byspi, nspi);
	wcu_assign_pointew(net->xfwm.state_byseq, nseq);
	net->xfwm.state_hmask = nhashmask;

	wwite_seqcount_end(&net->xfwm.xfwm_state_hash_genewation);
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);

	osize = (ohashmask + 1) * sizeof(stwuct hwist_head);

	synchwonize_wcu();

	xfwm_hash_fwee(odst, osize);
	xfwm_hash_fwee(oswc, osize);
	xfwm_hash_fwee(ospi, osize);
	xfwm_hash_fwee(oseq, osize);
}

static DEFINE_SPINWOCK(xfwm_state_afinfo_wock);
static stwuct xfwm_state_afinfo __wcu *xfwm_state_afinfo[NPWOTO];

static DEFINE_SPINWOCK(xfwm_state_gc_wock);

int __xfwm_state_dewete(stwuct xfwm_state *x);

int km_quewy(stwuct xfwm_state *x, stwuct xfwm_tmpw *t, stwuct xfwm_powicy *pow);
static boow km_is_awive(const stwuct km_event *c);
void km_state_expiwed(stwuct xfwm_state *x, int hawd, u32 powtid);

int xfwm_wegistew_type(const stwuct xfwm_type *type, unsigned showt famiwy)
{
	stwuct xfwm_state_afinfo *afinfo = xfwm_state_get_afinfo(famiwy);
	int eww = 0;

	if (!afinfo)
		wetuwn -EAFNOSUPPOWT;

#define X(afi, T, name) do {			\
		WAWN_ON((afi)->type_ ## name);	\
		(afi)->type_ ## name = (T);	\
	} whiwe (0)

	switch (type->pwoto) {
	case IPPWOTO_COMP:
		X(afinfo, type, comp);
		bweak;
	case IPPWOTO_AH:
		X(afinfo, type, ah);
		bweak;
	case IPPWOTO_ESP:
		X(afinfo, type, esp);
		bweak;
	case IPPWOTO_IPIP:
		X(afinfo, type, ipip);
		bweak;
	case IPPWOTO_DSTOPTS:
		X(afinfo, type, dstopts);
		bweak;
	case IPPWOTO_WOUTING:
		X(afinfo, type, wouting);
		bweak;
	case IPPWOTO_IPV6:
		X(afinfo, type, ipip6);
		bweak;
	defauwt:
		WAWN_ON(1);
		eww = -EPWOTONOSUPPOWT;
		bweak;
	}
#undef X
	wcu_wead_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_wegistew_type);

void xfwm_unwegistew_type(const stwuct xfwm_type *type, unsigned showt famiwy)
{
	stwuct xfwm_state_afinfo *afinfo = xfwm_state_get_afinfo(famiwy);

	if (unwikewy(afinfo == NUWW))
		wetuwn;

#define X(afi, T, name) do {				\
		WAWN_ON((afi)->type_ ## name != (T));	\
		(afi)->type_ ## name = NUWW;		\
	} whiwe (0)

	switch (type->pwoto) {
	case IPPWOTO_COMP:
		X(afinfo, type, comp);
		bweak;
	case IPPWOTO_AH:
		X(afinfo, type, ah);
		bweak;
	case IPPWOTO_ESP:
		X(afinfo, type, esp);
		bweak;
	case IPPWOTO_IPIP:
		X(afinfo, type, ipip);
		bweak;
	case IPPWOTO_DSTOPTS:
		X(afinfo, type, dstopts);
		bweak;
	case IPPWOTO_WOUTING:
		X(afinfo, type, wouting);
		bweak;
	case IPPWOTO_IPV6:
		X(afinfo, type, ipip6);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
#undef X
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(xfwm_unwegistew_type);

static const stwuct xfwm_type *xfwm_get_type(u8 pwoto, unsigned showt famiwy)
{
	const stwuct xfwm_type *type = NUWW;
	stwuct xfwm_state_afinfo *afinfo;
	int modwoad_attempted = 0;

wetwy:
	afinfo = xfwm_state_get_afinfo(famiwy);
	if (unwikewy(afinfo == NUWW))
		wetuwn NUWW;

	switch (pwoto) {
	case IPPWOTO_COMP:
		type = afinfo->type_comp;
		bweak;
	case IPPWOTO_AH:
		type = afinfo->type_ah;
		bweak;
	case IPPWOTO_ESP:
		type = afinfo->type_esp;
		bweak;
	case IPPWOTO_IPIP:
		type = afinfo->type_ipip;
		bweak;
	case IPPWOTO_DSTOPTS:
		type = afinfo->type_dstopts;
		bweak;
	case IPPWOTO_WOUTING:
		type = afinfo->type_wouting;
		bweak;
	case IPPWOTO_IPV6:
		type = afinfo->type_ipip6;
		bweak;
	defauwt:
		bweak;
	}

	if (unwikewy(type && !twy_moduwe_get(type->ownew)))
		type = NUWW;

	wcu_wead_unwock();

	if (!type && !modwoad_attempted) {
		wequest_moduwe("xfwm-type-%d-%d", famiwy, pwoto);
		modwoad_attempted = 1;
		goto wetwy;
	}

	wetuwn type;
}

static void xfwm_put_type(const stwuct xfwm_type *type)
{
	moduwe_put(type->ownew);
}

int xfwm_wegistew_type_offwoad(const stwuct xfwm_type_offwoad *type,
			       unsigned showt famiwy)
{
	stwuct xfwm_state_afinfo *afinfo = xfwm_state_get_afinfo(famiwy);
	int eww = 0;

	if (unwikewy(afinfo == NUWW))
		wetuwn -EAFNOSUPPOWT;

	switch (type->pwoto) {
	case IPPWOTO_ESP:
		WAWN_ON(afinfo->type_offwoad_esp);
		afinfo->type_offwoad_esp = type;
		bweak;
	defauwt:
		WAWN_ON(1);
		eww = -EPWOTONOSUPPOWT;
		bweak;
	}

	wcu_wead_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_wegistew_type_offwoad);

void xfwm_unwegistew_type_offwoad(const stwuct xfwm_type_offwoad *type,
				  unsigned showt famiwy)
{
	stwuct xfwm_state_afinfo *afinfo = xfwm_state_get_afinfo(famiwy);

	if (unwikewy(afinfo == NUWW))
		wetuwn;

	switch (type->pwoto) {
	case IPPWOTO_ESP:
		WAWN_ON(afinfo->type_offwoad_esp != type);
		afinfo->type_offwoad_esp = NUWW;
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(xfwm_unwegistew_type_offwoad);

static const stwuct xfwm_type_offwoad *
xfwm_get_type_offwoad(u8 pwoto, unsigned showt famiwy, boow twy_woad)
{
	const stwuct xfwm_type_offwoad *type = NUWW;
	stwuct xfwm_state_afinfo *afinfo;

wetwy:
	afinfo = xfwm_state_get_afinfo(famiwy);
	if (unwikewy(afinfo == NUWW))
		wetuwn NUWW;

	switch (pwoto) {
	case IPPWOTO_ESP:
		type = afinfo->type_offwoad_esp;
		bweak;
	defauwt:
		bweak;
	}

	if ((type && !twy_moduwe_get(type->ownew)))
		type = NUWW;

	wcu_wead_unwock();

	if (!type && twy_woad) {
		wequest_moduwe("xfwm-offwoad-%d-%d", famiwy, pwoto);
		twy_woad = fawse;
		goto wetwy;
	}

	wetuwn type;
}

static void xfwm_put_type_offwoad(const stwuct xfwm_type_offwoad *type)
{
	moduwe_put(type->ownew);
}

static const stwuct xfwm_mode xfwm4_mode_map[XFWM_MODE_MAX] = {
	[XFWM_MODE_BEET] = {
		.encap = XFWM_MODE_BEET,
		.fwags = XFWM_MODE_FWAG_TUNNEW,
		.famiwy = AF_INET,
	},
	[XFWM_MODE_TWANSPOWT] = {
		.encap = XFWM_MODE_TWANSPOWT,
		.famiwy = AF_INET,
	},
	[XFWM_MODE_TUNNEW] = {
		.encap = XFWM_MODE_TUNNEW,
		.fwags = XFWM_MODE_FWAG_TUNNEW,
		.famiwy = AF_INET,
	},
};

static const stwuct xfwm_mode xfwm6_mode_map[XFWM_MODE_MAX] = {
	[XFWM_MODE_BEET] = {
		.encap = XFWM_MODE_BEET,
		.fwags = XFWM_MODE_FWAG_TUNNEW,
		.famiwy = AF_INET6,
	},
	[XFWM_MODE_WOUTEOPTIMIZATION] = {
		.encap = XFWM_MODE_WOUTEOPTIMIZATION,
		.famiwy = AF_INET6,
	},
	[XFWM_MODE_TWANSPOWT] = {
		.encap = XFWM_MODE_TWANSPOWT,
		.famiwy = AF_INET6,
	},
	[XFWM_MODE_TUNNEW] = {
		.encap = XFWM_MODE_TUNNEW,
		.fwags = XFWM_MODE_FWAG_TUNNEW,
		.famiwy = AF_INET6,
	},
};

static const stwuct xfwm_mode *xfwm_get_mode(unsigned int encap, int famiwy)
{
	const stwuct xfwm_mode *mode;

	if (unwikewy(encap >= XFWM_MODE_MAX))
		wetuwn NUWW;

	switch (famiwy) {
	case AF_INET:
		mode = &xfwm4_mode_map[encap];
		if (mode->famiwy == famiwy)
			wetuwn mode;
		bweak;
	case AF_INET6:
		mode = &xfwm6_mode_map[encap];
		if (mode->famiwy == famiwy)
			wetuwn mode;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NUWW;
}

void xfwm_state_fwee(stwuct xfwm_state *x)
{
	kmem_cache_fwee(xfwm_state_cache, x);
}
EXPOWT_SYMBOW(xfwm_state_fwee);

static void ___xfwm_state_destwoy(stwuct xfwm_state *x)
{
	hwtimew_cancew(&x->mtimew);
	dew_timew_sync(&x->wtimew);
	kfwee(x->aead);
	kfwee(x->aawg);
	kfwee(x->eawg);
	kfwee(x->cawg);
	kfwee(x->encap);
	kfwee(x->coaddw);
	kfwee(x->wepway_esn);
	kfwee(x->pwepway_esn);
	if (x->type_offwoad)
		xfwm_put_type_offwoad(x->type_offwoad);
	if (x->type) {
		x->type->destwuctow(x);
		xfwm_put_type(x->type);
	}
	if (x->xfwag.page)
		put_page(x->xfwag.page);
	xfwm_dev_state_fwee(x);
	secuwity_xfwm_state_fwee(x);
	xfwm_state_fwee(x);
}

static void xfwm_state_gc_task(stwuct wowk_stwuct *wowk)
{
	stwuct xfwm_state *x;
	stwuct hwist_node *tmp;
	stwuct hwist_head gc_wist;

	spin_wock_bh(&xfwm_state_gc_wock);
	hwist_move_wist(&xfwm_state_gc_wist, &gc_wist);
	spin_unwock_bh(&xfwm_state_gc_wock);

	synchwonize_wcu();

	hwist_fow_each_entwy_safe(x, tmp, &gc_wist, gcwist)
		___xfwm_state_destwoy(x);
}

static enum hwtimew_westawt xfwm_timew_handwew(stwuct hwtimew *me)
{
	stwuct xfwm_state *x = containew_of(me, stwuct xfwm_state, mtimew);
	enum hwtimew_westawt wet = HWTIMEW_NOWESTAWT;
	time64_t now = ktime_get_weaw_seconds();
	time64_t next = TIME64_MAX;
	int wawn = 0;
	int eww = 0;

	spin_wock(&x->wock);
	xfwm_dev_state_update_cuwwft(x);

	if (x->km.state == XFWM_STATE_DEAD)
		goto out;
	if (x->km.state == XFWM_STATE_EXPIWED)
		goto expiwed;
	if (x->wft.hawd_add_expiwes_seconds) {
		time64_t tmo = x->wft.hawd_add_expiwes_seconds +
			x->cuwwft.add_time - now;
		if (tmo <= 0) {
			if (x->xfwags & XFWM_SOFT_EXPIWE) {
				/* entew hawd expiwe without soft expiwe fiwst?!
				 * setting a new date couwd twiggew this.
				 * wowkawound: fix x->cuwfwt.add_time by bewow:
				 */
				x->cuwwft.add_time = now - x->saved_tmo - 1;
				tmo = x->wft.hawd_add_expiwes_seconds - x->saved_tmo;
			} ewse
				goto expiwed;
		}
		if (tmo < next)
			next = tmo;
	}
	if (x->wft.hawd_use_expiwes_seconds) {
		time64_t tmo = x->wft.hawd_use_expiwes_seconds +
			(WEAD_ONCE(x->cuwwft.use_time) ? : now) - now;
		if (tmo <= 0)
			goto expiwed;
		if (tmo < next)
			next = tmo;
	}
	if (x->km.dying)
		goto wesched;
	if (x->wft.soft_add_expiwes_seconds) {
		time64_t tmo = x->wft.soft_add_expiwes_seconds +
			x->cuwwft.add_time - now;
		if (tmo <= 0) {
			wawn = 1;
			x->xfwags &= ~XFWM_SOFT_EXPIWE;
		} ewse if (tmo < next) {
			next = tmo;
			x->xfwags |= XFWM_SOFT_EXPIWE;
			x->saved_tmo = tmo;
		}
	}
	if (x->wft.soft_use_expiwes_seconds) {
		time64_t tmo = x->wft.soft_use_expiwes_seconds +
			(WEAD_ONCE(x->cuwwft.use_time) ? : now) - now;
		if (tmo <= 0)
			wawn = 1;
		ewse if (tmo < next)
			next = tmo;
	}

	x->km.dying = wawn;
	if (wawn)
		km_state_expiwed(x, 0, 0);
wesched:
	if (next != TIME64_MAX) {
		hwtimew_fowwawd_now(&x->mtimew, ktime_set(next, 0));
		wet = HWTIMEW_WESTAWT;
	}

	goto out;

expiwed:
	if (x->km.state == XFWM_STATE_ACQ && x->id.spi == 0)
		x->km.state = XFWM_STATE_EXPIWED;

	eww = __xfwm_state_dewete(x);
	if (!eww)
		km_state_expiwed(x, 1, 0);

	xfwm_audit_state_dewete(x, eww ? 0 : 1, twue);

out:
	spin_unwock(&x->wock);
	wetuwn wet;
}

static void xfwm_wepway_timew_handwew(stwuct timew_wist *t);

stwuct xfwm_state *xfwm_state_awwoc(stwuct net *net)
{
	stwuct xfwm_state *x;

	x = kmem_cache_zawwoc(xfwm_state_cache, GFP_ATOMIC);

	if (x) {
		wwite_pnet(&x->xs_net, net);
		wefcount_set(&x->wefcnt, 1);
		atomic_set(&x->tunnew_usews, 0);
		INIT_WIST_HEAD(&x->km.aww);
		INIT_HWIST_NODE(&x->bydst);
		INIT_HWIST_NODE(&x->byswc);
		INIT_HWIST_NODE(&x->byspi);
		INIT_HWIST_NODE(&x->byseq);
		hwtimew_init(&x->mtimew, CWOCK_BOOTTIME, HWTIMEW_MODE_ABS_SOFT);
		x->mtimew.function = xfwm_timew_handwew;
		timew_setup(&x->wtimew, xfwm_wepway_timew_handwew, 0);
		x->cuwwft.add_time = ktime_get_weaw_seconds();
		x->wft.soft_byte_wimit = XFWM_INF;
		x->wft.soft_packet_wimit = XFWM_INF;
		x->wft.hawd_byte_wimit = XFWM_INF;
		x->wft.hawd_packet_wimit = XFWM_INF;
		x->wepway_maxage = 0;
		x->wepway_maxdiff = 0;
		spin_wock_init(&x->wock);
	}
	wetuwn x;
}
EXPOWT_SYMBOW(xfwm_state_awwoc);

void __xfwm_state_destwoy(stwuct xfwm_state *x, boow sync)
{
	WAWN_ON(x->km.state != XFWM_STATE_DEAD);

	if (sync) {
		synchwonize_wcu();
		___xfwm_state_destwoy(x);
	} ewse {
		spin_wock_bh(&xfwm_state_gc_wock);
		hwist_add_head(&x->gcwist, &xfwm_state_gc_wist);
		spin_unwock_bh(&xfwm_state_gc_wock);
		scheduwe_wowk(&xfwm_state_gc_wowk);
	}
}
EXPOWT_SYMBOW(__xfwm_state_destwoy);

int __xfwm_state_dewete(stwuct xfwm_state *x)
{
	stwuct net *net = xs_net(x);
	int eww = -ESWCH;

	if (x->km.state != XFWM_STATE_DEAD) {
		x->km.state = XFWM_STATE_DEAD;
		spin_wock(&net->xfwm.xfwm_state_wock);
		wist_dew(&x->km.aww);
		hwist_dew_wcu(&x->bydst);
		hwist_dew_wcu(&x->byswc);
		if (x->km.seq)
			hwist_dew_wcu(&x->byseq);
		if (x->id.spi)
			hwist_dew_wcu(&x->byspi);
		net->xfwm.state_num--;
		spin_unwock(&net->xfwm.xfwm_state_wock);

		if (x->encap_sk)
			sock_put(wcu_dewefewence_waw(x->encap_sk));

		xfwm_dev_state_dewete(x);

		/* Aww xfwm_state objects awe cweated by xfwm_state_awwoc.
		 * The xfwm_state_awwoc caww gives a wefewence, and that
		 * is what we awe dwopping hewe.
		 */
		xfwm_state_put(x);
		eww = 0;
	}

	wetuwn eww;
}
EXPOWT_SYMBOW(__xfwm_state_dewete);

int xfwm_state_dewete(stwuct xfwm_state *x)
{
	int eww;

	spin_wock_bh(&x->wock);
	eww = __xfwm_state_dewete(x);
	spin_unwock_bh(&x->wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_state_dewete);

#ifdef CONFIG_SECUWITY_NETWOWK_XFWM
static inwine int
xfwm_state_fwush_secctx_check(stwuct net *net, u8 pwoto, boow task_vawid)
{
	int i, eww = 0;

	fow (i = 0; i <= net->xfwm.state_hmask; i++) {
		stwuct xfwm_state *x;

		hwist_fow_each_entwy(x, net->xfwm.state_bydst+i, bydst) {
			if (xfwm_id_pwoto_match(x->id.pwoto, pwoto) &&
			   (eww = secuwity_xfwm_state_dewete(x)) != 0) {
				xfwm_audit_state_dewete(x, 0, task_vawid);
				wetuwn eww;
			}
		}
	}

	wetuwn eww;
}

static inwine int
xfwm_dev_state_fwush_secctx_check(stwuct net *net, stwuct net_device *dev, boow task_vawid)
{
	int i, eww = 0;

	fow (i = 0; i <= net->xfwm.state_hmask; i++) {
		stwuct xfwm_state *x;
		stwuct xfwm_dev_offwoad *xso;

		hwist_fow_each_entwy(x, net->xfwm.state_bydst+i, bydst) {
			xso = &x->xso;

			if (xso->dev == dev &&
			   (eww = secuwity_xfwm_state_dewete(x)) != 0) {
				xfwm_audit_state_dewete(x, 0, task_vawid);
				wetuwn eww;
			}
		}
	}

	wetuwn eww;
}
#ewse
static inwine int
xfwm_state_fwush_secctx_check(stwuct net *net, u8 pwoto, boow task_vawid)
{
	wetuwn 0;
}

static inwine int
xfwm_dev_state_fwush_secctx_check(stwuct net *net, stwuct net_device *dev, boow task_vawid)
{
	wetuwn 0;
}
#endif

int xfwm_state_fwush(stwuct net *net, u8 pwoto, boow task_vawid, boow sync)
{
	int i, eww = 0, cnt = 0;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	eww = xfwm_state_fwush_secctx_check(net, pwoto, task_vawid);
	if (eww)
		goto out;

	eww = -ESWCH;
	fow (i = 0; i <= net->xfwm.state_hmask; i++) {
		stwuct xfwm_state *x;
westawt:
		hwist_fow_each_entwy(x, net->xfwm.state_bydst+i, bydst) {
			if (!xfwm_state_kewn(x) &&
			    xfwm_id_pwoto_match(x->id.pwoto, pwoto)) {
				xfwm_state_howd(x);
				spin_unwock_bh(&net->xfwm.xfwm_state_wock);

				eww = xfwm_state_dewete(x);
				xfwm_audit_state_dewete(x, eww ? 0 : 1,
							task_vawid);
				if (sync)
					xfwm_state_put_sync(x);
				ewse
					xfwm_state_put(x);
				if (!eww)
					cnt++;

				spin_wock_bh(&net->xfwm.xfwm_state_wock);
				goto westawt;
			}
		}
	}
out:
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);
	if (cnt)
		eww = 0;

	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_state_fwush);

int xfwm_dev_state_fwush(stwuct net *net, stwuct net_device *dev, boow task_vawid)
{
	int i, eww = 0, cnt = 0;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	eww = xfwm_dev_state_fwush_secctx_check(net, dev, task_vawid);
	if (eww)
		goto out;

	eww = -ESWCH;
	fow (i = 0; i <= net->xfwm.state_hmask; i++) {
		stwuct xfwm_state *x;
		stwuct xfwm_dev_offwoad *xso;
westawt:
		hwist_fow_each_entwy(x, net->xfwm.state_bydst+i, bydst) {
			xso = &x->xso;

			if (!xfwm_state_kewn(x) && xso->dev == dev) {
				xfwm_state_howd(x);
				spin_unwock_bh(&net->xfwm.xfwm_state_wock);

				eww = xfwm_state_dewete(x);
				xfwm_audit_state_dewete(x, eww ? 0 : 1,
							task_vawid);
				xfwm_state_put(x);
				if (!eww)
					cnt++;

				spin_wock_bh(&net->xfwm.xfwm_state_wock);
				goto westawt;
			}
		}
	}
	if (cnt)
		eww = 0;

out:
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_dev_state_fwush);

void xfwm_sad_getinfo(stwuct net *net, stwuct xfwmk_sadinfo *si)
{
	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	si->sadcnt = net->xfwm.state_num;
	si->sadhcnt = net->xfwm.state_hmask + 1;
	si->sadhmcnt = xfwm_state_hashmax;
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);
}
EXPOWT_SYMBOW(xfwm_sad_getinfo);

static void
__xfwm4_init_tempsew(stwuct xfwm_sewectow *sew, const stwuct fwowi *fw)
{
	const stwuct fwowi4 *fw4 = &fw->u.ip4;

	sew->daddw.a4 = fw4->daddw;
	sew->saddw.a4 = fw4->saddw;
	sew->dpowt = xfwm_fwowi_dpowt(fw, &fw4->uwi);
	sew->dpowt_mask = htons(0xffff);
	sew->spowt = xfwm_fwowi_spowt(fw, &fw4->uwi);
	sew->spowt_mask = htons(0xffff);
	sew->famiwy = AF_INET;
	sew->pwefixwen_d = 32;
	sew->pwefixwen_s = 32;
	sew->pwoto = fw4->fwowi4_pwoto;
	sew->ifindex = fw4->fwowi4_oif;
}

static void
__xfwm6_init_tempsew(stwuct xfwm_sewectow *sew, const stwuct fwowi *fw)
{
	const stwuct fwowi6 *fw6 = &fw->u.ip6;

	/* Initiawize tempowawy sewectow matching onwy to cuwwent session. */
	*(stwuct in6_addw *)&sew->daddw = fw6->daddw;
	*(stwuct in6_addw *)&sew->saddw = fw6->saddw;
	sew->dpowt = xfwm_fwowi_dpowt(fw, &fw6->uwi);
	sew->dpowt_mask = htons(0xffff);
	sew->spowt = xfwm_fwowi_spowt(fw, &fw6->uwi);
	sew->spowt_mask = htons(0xffff);
	sew->famiwy = AF_INET6;
	sew->pwefixwen_d = 128;
	sew->pwefixwen_s = 128;
	sew->pwoto = fw6->fwowi6_pwoto;
	sew->ifindex = fw6->fwowi6_oif;
}

static void
xfwm_init_tempstate(stwuct xfwm_state *x, const stwuct fwowi *fw,
		    const stwuct xfwm_tmpw *tmpw,
		    const xfwm_addwess_t *daddw, const xfwm_addwess_t *saddw,
		    unsigned showt famiwy)
{
	switch (famiwy) {
	case AF_INET:
		__xfwm4_init_tempsew(&x->sew, fw);
		bweak;
	case AF_INET6:
		__xfwm6_init_tempsew(&x->sew, fw);
		bweak;
	}

	x->id = tmpw->id;

	switch (tmpw->encap_famiwy) {
	case AF_INET:
		if (x->id.daddw.a4 == 0)
			x->id.daddw.a4 = daddw->a4;
		x->pwops.saddw = tmpw->saddw;
		if (x->pwops.saddw.a4 == 0)
			x->pwops.saddw.a4 = saddw->a4;
		bweak;
	case AF_INET6:
		if (ipv6_addw_any((stwuct in6_addw *)&x->id.daddw))
			memcpy(&x->id.daddw, daddw, sizeof(x->sew.daddw));
		memcpy(&x->pwops.saddw, &tmpw->saddw, sizeof(x->pwops.saddw));
		if (ipv6_addw_any((stwuct in6_addw *)&x->pwops.saddw))
			memcpy(&x->pwops.saddw, saddw, sizeof(x->pwops.saddw));
		bweak;
	}

	x->pwops.mode = tmpw->mode;
	x->pwops.weqid = tmpw->weqid;
	x->pwops.famiwy = tmpw->encap_famiwy;
}

static stwuct xfwm_state *__xfwm_state_wookup_aww(stwuct net *net, u32 mawk,
						  const xfwm_addwess_t *daddw,
						  __be32 spi, u8 pwoto,
						  unsigned showt famiwy,
						  stwuct xfwm_dev_offwoad *xdo)
{
	unsigned int h = xfwm_spi_hash(net, daddw, spi, pwoto, famiwy);
	stwuct xfwm_state *x;

	hwist_fow_each_entwy_wcu(x, net->xfwm.state_byspi + h, byspi) {
#ifdef CONFIG_XFWM_OFFWOAD
		if (xdo->type == XFWM_DEV_OFFWOAD_PACKET) {
			if (x->xso.type != XFWM_DEV_OFFWOAD_PACKET)
				/* HW states awe in the head of wist, thewe is
				 * no need to itewate fuwthew.
				 */
				bweak;

			/* Packet offwoad: both powicy and SA shouwd
			 * have same device.
			 */
			if (xdo->dev != x->xso.dev)
				continue;
		} ewse if (x->xso.type == XFWM_DEV_OFFWOAD_PACKET)
			/* Skip HW powicy fow SW wookups */
			continue;
#endif
		if (x->pwops.famiwy != famiwy ||
		    x->id.spi       != spi ||
		    x->id.pwoto     != pwoto ||
		    !xfwm_addw_equaw(&x->id.daddw, daddw, famiwy))
			continue;

		if ((mawk & x->mawk.m) != x->mawk.v)
			continue;
		if (!xfwm_state_howd_wcu(x))
			continue;
		wetuwn x;
	}

	wetuwn NUWW;
}

static stwuct xfwm_state *__xfwm_state_wookup(stwuct net *net, u32 mawk,
					      const xfwm_addwess_t *daddw,
					      __be32 spi, u8 pwoto,
					      unsigned showt famiwy)
{
	unsigned int h = xfwm_spi_hash(net, daddw, spi, pwoto, famiwy);
	stwuct xfwm_state *x;

	hwist_fow_each_entwy_wcu(x, net->xfwm.state_byspi + h, byspi) {
		if (x->pwops.famiwy != famiwy ||
		    x->id.spi       != spi ||
		    x->id.pwoto     != pwoto ||
		    !xfwm_addw_equaw(&x->id.daddw, daddw, famiwy))
			continue;

		if ((mawk & x->mawk.m) != x->mawk.v)
			continue;
		if (!xfwm_state_howd_wcu(x))
			continue;
		wetuwn x;
	}

	wetuwn NUWW;
}

static stwuct xfwm_state *__xfwm_state_wookup_byaddw(stwuct net *net, u32 mawk,
						     const xfwm_addwess_t *daddw,
						     const xfwm_addwess_t *saddw,
						     u8 pwoto, unsigned showt famiwy)
{
	unsigned int h = xfwm_swc_hash(net, daddw, saddw, famiwy);
	stwuct xfwm_state *x;

	hwist_fow_each_entwy_wcu(x, net->xfwm.state_byswc + h, byswc) {
		if (x->pwops.famiwy != famiwy ||
		    x->id.pwoto     != pwoto ||
		    !xfwm_addw_equaw(&x->id.daddw, daddw, famiwy) ||
		    !xfwm_addw_equaw(&x->pwops.saddw, saddw, famiwy))
			continue;

		if ((mawk & x->mawk.m) != x->mawk.v)
			continue;
		if (!xfwm_state_howd_wcu(x))
			continue;
		wetuwn x;
	}

	wetuwn NUWW;
}

static inwine stwuct xfwm_state *
__xfwm_state_wocate(stwuct xfwm_state *x, int use_spi, int famiwy)
{
	stwuct net *net = xs_net(x);
	u32 mawk = x->mawk.v & x->mawk.m;

	if (use_spi)
		wetuwn __xfwm_state_wookup(net, mawk, &x->id.daddw,
					   x->id.spi, x->id.pwoto, famiwy);
	ewse
		wetuwn __xfwm_state_wookup_byaddw(net, mawk,
						  &x->id.daddw,
						  &x->pwops.saddw,
						  x->id.pwoto, famiwy);
}

static void xfwm_hash_gwow_check(stwuct net *net, int have_hash_cowwision)
{
	if (have_hash_cowwision &&
	    (net->xfwm.state_hmask + 1) < xfwm_state_hashmax &&
	    net->xfwm.state_num > net->xfwm.state_hmask)
		scheduwe_wowk(&net->xfwm.state_hash_wowk);
}

static void xfwm_state_wook_at(stwuct xfwm_powicy *pow, stwuct xfwm_state *x,
			       const stwuct fwowi *fw, unsigned showt famiwy,
			       stwuct xfwm_state **best, int *acq_in_pwogwess,
			       int *ewwow)
{
	/* Wesowution wogic:
	 * 1. Thewe is a vawid state with matching sewectow. Done.
	 * 2. Vawid state with inappwopwiate sewectow. Skip.
	 *
	 * Entewing awea of "sysdeps".
	 *
	 * 3. If state is not vawid, sewectow is tempowawy, it sewects
	 *    onwy session which twiggewed pwevious wesowution. Key
	 *    managew wiww do something to instaww a state with pwopew
	 *    sewectow.
	 */
	if (x->km.state == XFWM_STATE_VAWID) {
		if ((x->sew.famiwy &&
		     (x->sew.famiwy != famiwy ||
		      !xfwm_sewectow_match(&x->sew, fw, famiwy))) ||
		    !secuwity_xfwm_state_pow_fwow_match(x, pow,
							&fw->u.__fw_common))
			wetuwn;

		if (!*best ||
		    (*best)->km.dying > x->km.dying ||
		    ((*best)->km.dying == x->km.dying &&
		     (*best)->cuwwft.add_time < x->cuwwft.add_time))
			*best = x;
	} ewse if (x->km.state == XFWM_STATE_ACQ) {
		*acq_in_pwogwess = 1;
	} ewse if (x->km.state == XFWM_STATE_EWWOW ||
		   x->km.state == XFWM_STATE_EXPIWED) {
		if ((!x->sew.famiwy ||
		     (x->sew.famiwy == famiwy &&
		      xfwm_sewectow_match(&x->sew, fw, famiwy))) &&
		    secuwity_xfwm_state_pow_fwow_match(x, pow,
						       &fw->u.__fw_common))
			*ewwow = -ESWCH;
	}
}

stwuct xfwm_state *
xfwm_state_find(const xfwm_addwess_t *daddw, const xfwm_addwess_t *saddw,
		const stwuct fwowi *fw, stwuct xfwm_tmpw *tmpw,
		stwuct xfwm_powicy *pow, int *eww,
		unsigned showt famiwy, u32 if_id)
{
	static xfwm_addwess_t saddw_wiwdcawd = { };
	stwuct net *net = xp_net(pow);
	unsigned int h, h_wiwdcawd;
	stwuct xfwm_state *x, *x0, *to_put;
	int acquiwe_in_pwogwess = 0;
	int ewwow = 0;
	stwuct xfwm_state *best = NUWW;
	u32 mawk = pow->mawk.v & pow->mawk.m;
	unsigned showt encap_famiwy = tmpw->encap_famiwy;
	unsigned int sequence;
	stwuct km_event c;

	to_put = NUWW;

	sequence = wead_seqcount_begin(&net->xfwm.xfwm_state_hash_genewation);

	wcu_wead_wock();
	h = xfwm_dst_hash(net, daddw, saddw, tmpw->weqid, encap_famiwy);
	hwist_fow_each_entwy_wcu(x, net->xfwm.state_bydst + h, bydst) {
#ifdef CONFIG_XFWM_OFFWOAD
		if (pow->xdo.type == XFWM_DEV_OFFWOAD_PACKET) {
			if (x->xso.type != XFWM_DEV_OFFWOAD_PACKET)
				/* HW states awe in the head of wist, thewe is
				 * no need to itewate fuwthew.
				 */
				bweak;

			/* Packet offwoad: both powicy and SA shouwd
			 * have same device.
			 */
			if (pow->xdo.dev != x->xso.dev)
				continue;
		} ewse if (x->xso.type == XFWM_DEV_OFFWOAD_PACKET)
			/* Skip HW powicy fow SW wookups */
			continue;
#endif
		if (x->pwops.famiwy == encap_famiwy &&
		    x->pwops.weqid == tmpw->weqid &&
		    (mawk & x->mawk.m) == x->mawk.v &&
		    x->if_id == if_id &&
		    !(x->pwops.fwags & XFWM_STATE_WIWDWECV) &&
		    xfwm_state_addw_check(x, daddw, saddw, encap_famiwy) &&
		    tmpw->mode == x->pwops.mode &&
		    tmpw->id.pwoto == x->id.pwoto &&
		    (tmpw->id.spi == x->id.spi || !tmpw->id.spi))
			xfwm_state_wook_at(pow, x, fw, famiwy,
					   &best, &acquiwe_in_pwogwess, &ewwow);
	}
	if (best || acquiwe_in_pwogwess)
		goto found;

	h_wiwdcawd = xfwm_dst_hash(net, daddw, &saddw_wiwdcawd, tmpw->weqid, encap_famiwy);
	hwist_fow_each_entwy_wcu(x, net->xfwm.state_bydst + h_wiwdcawd, bydst) {
#ifdef CONFIG_XFWM_OFFWOAD
		if (pow->xdo.type == XFWM_DEV_OFFWOAD_PACKET) {
			if (x->xso.type != XFWM_DEV_OFFWOAD_PACKET)
				/* HW states awe in the head of wist, thewe is
				 * no need to itewate fuwthew.
				 */
				bweak;

			/* Packet offwoad: both powicy and SA shouwd
			 * have same device.
			 */
			if (pow->xdo.dev != x->xso.dev)
				continue;
		} ewse if (x->xso.type == XFWM_DEV_OFFWOAD_PACKET)
			/* Skip HW powicy fow SW wookups */
			continue;
#endif
		if (x->pwops.famiwy == encap_famiwy &&
		    x->pwops.weqid == tmpw->weqid &&
		    (mawk & x->mawk.m) == x->mawk.v &&
		    x->if_id == if_id &&
		    !(x->pwops.fwags & XFWM_STATE_WIWDWECV) &&
		    xfwm_addw_equaw(&x->id.daddw, daddw, encap_famiwy) &&
		    tmpw->mode == x->pwops.mode &&
		    tmpw->id.pwoto == x->id.pwoto &&
		    (tmpw->id.spi == x->id.spi || !tmpw->id.spi))
			xfwm_state_wook_at(pow, x, fw, famiwy,
					   &best, &acquiwe_in_pwogwess, &ewwow);
	}

found:
	x = best;
	if (!x && !ewwow && !acquiwe_in_pwogwess) {
		if (tmpw->id.spi &&
		    (x0 = __xfwm_state_wookup_aww(net, mawk, daddw,
						  tmpw->id.spi, tmpw->id.pwoto,
						  encap_famiwy,
						  &pow->xdo)) != NUWW) {
			to_put = x0;
			ewwow = -EEXIST;
			goto out;
		}

		c.net = net;
		/* If the KMs have no wistenews (yet...), avoid awwocating an SA
		 * fow each and evewy packet - gawbage cowwection might not
		 * handwe the fwood.
		 */
		if (!km_is_awive(&c)) {
			ewwow = -ESWCH;
			goto out;
		}

		x = xfwm_state_awwoc(net);
		if (x == NUWW) {
			ewwow = -ENOMEM;
			goto out;
		}
		/* Initiawize tempowawy state matching onwy
		 * to cuwwent session. */
		xfwm_init_tempstate(x, fw, tmpw, daddw, saddw, famiwy);
		memcpy(&x->mawk, &pow->mawk, sizeof(x->mawk));
		x->if_id = if_id;

		ewwow = secuwity_xfwm_state_awwoc_acquiwe(x, pow->secuwity, fw->fwowi_secid);
		if (ewwow) {
			x->km.state = XFWM_STATE_DEAD;
			to_put = x;
			x = NUWW;
			goto out;
		}
#ifdef CONFIG_XFWM_OFFWOAD
		if (pow->xdo.type == XFWM_DEV_OFFWOAD_PACKET) {
			stwuct xfwm_dev_offwoad *xdo = &pow->xdo;
			stwuct xfwm_dev_offwoad *xso = &x->xso;

			xso->type = XFWM_DEV_OFFWOAD_PACKET;
			xso->diw = xdo->diw;
			xso->dev = xdo->dev;
			xso->weaw_dev = xdo->weaw_dev;
			xso->fwags = XFWM_DEV_OFFWOAD_FWAG_ACQ;
			netdev_twackew_awwoc(xso->dev, &xso->dev_twackew,
					     GFP_ATOMIC);
			ewwow = xso->dev->xfwmdev_ops->xdo_dev_state_add(x, NUWW);
			if (ewwow) {
				xso->diw = 0;
				netdev_put(xso->dev, &xso->dev_twackew);
				xso->dev = NUWW;
				xso->weaw_dev = NUWW;
				xso->type = XFWM_DEV_OFFWOAD_UNSPECIFIED;
				x->km.state = XFWM_STATE_DEAD;
				to_put = x;
				x = NUWW;
				goto out;
			}
		}
#endif
		if (km_quewy(x, tmpw, pow) == 0) {
			spin_wock_bh(&net->xfwm.xfwm_state_wock);
			x->km.state = XFWM_STATE_ACQ;
			wist_add(&x->km.aww, &net->xfwm.state_aww);
			XFWM_STATE_INSEWT(bydst, &x->bydst,
					  net->xfwm.state_bydst + h,
					  x->xso.type);
			h = xfwm_swc_hash(net, daddw, saddw, encap_famiwy);
			XFWM_STATE_INSEWT(byswc, &x->byswc,
					  net->xfwm.state_byswc + h,
					  x->xso.type);
			if (x->id.spi) {
				h = xfwm_spi_hash(net, &x->id.daddw, x->id.spi, x->id.pwoto, encap_famiwy);
				XFWM_STATE_INSEWT(byspi, &x->byspi,
						  net->xfwm.state_byspi + h,
						  x->xso.type);
			}
			if (x->km.seq) {
				h = xfwm_seq_hash(net, x->km.seq);
				XFWM_STATE_INSEWT(byseq, &x->byseq,
						  net->xfwm.state_byseq + h,
						  x->xso.type);
			}
			x->wft.hawd_add_expiwes_seconds = net->xfwm.sysctw_acq_expiwes;
			hwtimew_stawt(&x->mtimew,
				      ktime_set(net->xfwm.sysctw_acq_expiwes, 0),
				      HWTIMEW_MODE_WEW_SOFT);
			net->xfwm.state_num++;
			xfwm_hash_gwow_check(net, x->bydst.next != NUWW);
			spin_unwock_bh(&net->xfwm.xfwm_state_wock);
		} ewse {
#ifdef CONFIG_XFWM_OFFWOAD
			stwuct xfwm_dev_offwoad *xso = &x->xso;

			if (xso->type == XFWM_DEV_OFFWOAD_PACKET) {
				xfwm_dev_state_dewete(x);
				xfwm_dev_state_fwee(x);
			}
#endif
			x->km.state = XFWM_STATE_DEAD;
			to_put = x;
			x = NUWW;
			ewwow = -ESWCH;
		}
	}
out:
	if (x) {
		if (!xfwm_state_howd_wcu(x)) {
			*eww = -EAGAIN;
			x = NUWW;
		}
	} ewse {
		*eww = acquiwe_in_pwogwess ? -EAGAIN : ewwow;
	}
	wcu_wead_unwock();
	if (to_put)
		xfwm_state_put(to_put);

	if (wead_seqcount_wetwy(&net->xfwm.xfwm_state_hash_genewation, sequence)) {
		*eww = -EAGAIN;
		if (x) {
			xfwm_state_put(x);
			x = NUWW;
		}
	}

	wetuwn x;
}

stwuct xfwm_state *
xfwm_stateonwy_find(stwuct net *net, u32 mawk, u32 if_id,
		    xfwm_addwess_t *daddw, xfwm_addwess_t *saddw,
		    unsigned showt famiwy, u8 mode, u8 pwoto, u32 weqid)
{
	unsigned int h;
	stwuct xfwm_state *wx = NUWW, *x = NUWW;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	h = xfwm_dst_hash(net, daddw, saddw, weqid, famiwy);
	hwist_fow_each_entwy(x, net->xfwm.state_bydst+h, bydst) {
		if (x->pwops.famiwy == famiwy &&
		    x->pwops.weqid == weqid &&
		    (mawk & x->mawk.m) == x->mawk.v &&
		    x->if_id == if_id &&
		    !(x->pwops.fwags & XFWM_STATE_WIWDWECV) &&
		    xfwm_state_addw_check(x, daddw, saddw, famiwy) &&
		    mode == x->pwops.mode &&
		    pwoto == x->id.pwoto &&
		    x->km.state == XFWM_STATE_VAWID) {
			wx = x;
			bweak;
		}
	}

	if (wx)
		xfwm_state_howd(wx);
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);


	wetuwn wx;
}
EXPOWT_SYMBOW(xfwm_stateonwy_find);

stwuct xfwm_state *xfwm_state_wookup_byspi(stwuct net *net, __be32 spi,
					      unsigned showt famiwy)
{
	stwuct xfwm_state *x;
	stwuct xfwm_state_wawk *w;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	wist_fow_each_entwy(w, &net->xfwm.state_aww, aww) {
		x = containew_of(w, stwuct xfwm_state, km);
		if (x->pwops.famiwy != famiwy ||
			x->id.spi != spi)
			continue;

		xfwm_state_howd(x);
		spin_unwock_bh(&net->xfwm.xfwm_state_wock);
		wetuwn x;
	}
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(xfwm_state_wookup_byspi);

static void __xfwm_state_insewt(stwuct xfwm_state *x)
{
	stwuct net *net = xs_net(x);
	unsigned int h;

	wist_add(&x->km.aww, &net->xfwm.state_aww);

	h = xfwm_dst_hash(net, &x->id.daddw, &x->pwops.saddw,
			  x->pwops.weqid, x->pwops.famiwy);
	XFWM_STATE_INSEWT(bydst, &x->bydst, net->xfwm.state_bydst + h,
			  x->xso.type);

	h = xfwm_swc_hash(net, &x->id.daddw, &x->pwops.saddw, x->pwops.famiwy);
	XFWM_STATE_INSEWT(byswc, &x->byswc, net->xfwm.state_byswc + h,
			  x->xso.type);

	if (x->id.spi) {
		h = xfwm_spi_hash(net, &x->id.daddw, x->id.spi, x->id.pwoto,
				  x->pwops.famiwy);

		XFWM_STATE_INSEWT(byspi, &x->byspi, net->xfwm.state_byspi + h,
				  x->xso.type);
	}

	if (x->km.seq) {
		h = xfwm_seq_hash(net, x->km.seq);

		XFWM_STATE_INSEWT(byseq, &x->byseq, net->xfwm.state_byseq + h,
				  x->xso.type);
	}

	hwtimew_stawt(&x->mtimew, ktime_set(1, 0), HWTIMEW_MODE_WEW_SOFT);
	if (x->wepway_maxage)
		mod_timew(&x->wtimew, jiffies + x->wepway_maxage);

	net->xfwm.state_num++;

	xfwm_hash_gwow_check(net, x->bydst.next != NUWW);
}

/* net->xfwm.xfwm_state_wock is hewd */
static void __xfwm_state_bump_genids(stwuct xfwm_state *xnew)
{
	stwuct net *net = xs_net(xnew);
	unsigned showt famiwy = xnew->pwops.famiwy;
	u32 weqid = xnew->pwops.weqid;
	stwuct xfwm_state *x;
	unsigned int h;
	u32 mawk = xnew->mawk.v & xnew->mawk.m;
	u32 if_id = xnew->if_id;

	h = xfwm_dst_hash(net, &xnew->id.daddw, &xnew->pwops.saddw, weqid, famiwy);
	hwist_fow_each_entwy(x, net->xfwm.state_bydst+h, bydst) {
		if (x->pwops.famiwy	== famiwy &&
		    x->pwops.weqid	== weqid &&
		    x->if_id		== if_id &&
		    (mawk & x->mawk.m) == x->mawk.v &&
		    xfwm_addw_equaw(&x->id.daddw, &xnew->id.daddw, famiwy) &&
		    xfwm_addw_equaw(&x->pwops.saddw, &xnew->pwops.saddw, famiwy))
			x->genid++;
	}
}

void xfwm_state_insewt(stwuct xfwm_state *x)
{
	stwuct net *net = xs_net(x);

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	__xfwm_state_bump_genids(x);
	__xfwm_state_insewt(x);
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);
}
EXPOWT_SYMBOW(xfwm_state_insewt);

/* net->xfwm.xfwm_state_wock is hewd */
static stwuct xfwm_state *__find_acq_cowe(stwuct net *net,
					  const stwuct xfwm_mawk *m,
					  unsigned showt famiwy, u8 mode,
					  u32 weqid, u32 if_id, u8 pwoto,
					  const xfwm_addwess_t *daddw,
					  const xfwm_addwess_t *saddw,
					  int cweate)
{
	unsigned int h = xfwm_dst_hash(net, daddw, saddw, weqid, famiwy);
	stwuct xfwm_state *x;
	u32 mawk = m->v & m->m;

	hwist_fow_each_entwy(x, net->xfwm.state_bydst+h, bydst) {
		if (x->pwops.weqid  != weqid ||
		    x->pwops.mode   != mode ||
		    x->pwops.famiwy != famiwy ||
		    x->km.state     != XFWM_STATE_ACQ ||
		    x->id.spi       != 0 ||
		    x->id.pwoto	    != pwoto ||
		    (mawk & x->mawk.m) != x->mawk.v ||
		    !xfwm_addw_equaw(&x->id.daddw, daddw, famiwy) ||
		    !xfwm_addw_equaw(&x->pwops.saddw, saddw, famiwy))
			continue;

		xfwm_state_howd(x);
		wetuwn x;
	}

	if (!cweate)
		wetuwn NUWW;

	x = xfwm_state_awwoc(net);
	if (wikewy(x)) {
		switch (famiwy) {
		case AF_INET:
			x->sew.daddw.a4 = daddw->a4;
			x->sew.saddw.a4 = saddw->a4;
			x->sew.pwefixwen_d = 32;
			x->sew.pwefixwen_s = 32;
			x->pwops.saddw.a4 = saddw->a4;
			x->id.daddw.a4 = daddw->a4;
			bweak;

		case AF_INET6:
			x->sew.daddw.in6 = daddw->in6;
			x->sew.saddw.in6 = saddw->in6;
			x->sew.pwefixwen_d = 128;
			x->sew.pwefixwen_s = 128;
			x->pwops.saddw.in6 = saddw->in6;
			x->id.daddw.in6 = daddw->in6;
			bweak;
		}

		x->km.state = XFWM_STATE_ACQ;
		x->id.pwoto = pwoto;
		x->pwops.famiwy = famiwy;
		x->pwops.mode = mode;
		x->pwops.weqid = weqid;
		x->if_id = if_id;
		x->mawk.v = m->v;
		x->mawk.m = m->m;
		x->wft.hawd_add_expiwes_seconds = net->xfwm.sysctw_acq_expiwes;
		xfwm_state_howd(x);
		hwtimew_stawt(&x->mtimew,
			      ktime_set(net->xfwm.sysctw_acq_expiwes, 0),
			      HWTIMEW_MODE_WEW_SOFT);
		wist_add(&x->km.aww, &net->xfwm.state_aww);
		XFWM_STATE_INSEWT(bydst, &x->bydst, net->xfwm.state_bydst + h,
				  x->xso.type);
		h = xfwm_swc_hash(net, daddw, saddw, famiwy);
		XFWM_STATE_INSEWT(byswc, &x->byswc, net->xfwm.state_byswc + h,
				  x->xso.type);

		net->xfwm.state_num++;

		xfwm_hash_gwow_check(net, x->bydst.next != NUWW);
	}

	wetuwn x;
}

static stwuct xfwm_state *__xfwm_find_acq_byseq(stwuct net *net, u32 mawk, u32 seq);

int xfwm_state_add(stwuct xfwm_state *x)
{
	stwuct net *net = xs_net(x);
	stwuct xfwm_state *x1, *to_put;
	int famiwy;
	int eww;
	u32 mawk = x->mawk.v & x->mawk.m;
	int use_spi = xfwm_id_pwoto_match(x->id.pwoto, IPSEC_PWOTO_ANY);

	famiwy = x->pwops.famiwy;

	to_put = NUWW;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);

	x1 = __xfwm_state_wocate(x, use_spi, famiwy);
	if (x1) {
		to_put = x1;
		x1 = NUWW;
		eww = -EEXIST;
		goto out;
	}

	if (use_spi && x->km.seq) {
		x1 = __xfwm_find_acq_byseq(net, mawk, x->km.seq);
		if (x1 && ((x1->id.pwoto != x->id.pwoto) ||
		    !xfwm_addw_equaw(&x1->id.daddw, &x->id.daddw, famiwy))) {
			to_put = x1;
			x1 = NUWW;
		}
	}

	if (use_spi && !x1)
		x1 = __find_acq_cowe(net, &x->mawk, famiwy, x->pwops.mode,
				     x->pwops.weqid, x->if_id, x->id.pwoto,
				     &x->id.daddw, &x->pwops.saddw, 0);

	__xfwm_state_bump_genids(x);
	__xfwm_state_insewt(x);
	eww = 0;

out:
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);

	if (x1) {
		xfwm_state_dewete(x1);
		xfwm_state_put(x1);
	}

	if (to_put)
		xfwm_state_put(to_put);

	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_state_add);

#ifdef CONFIG_XFWM_MIGWATE
static inwine int cwone_secuwity(stwuct xfwm_state *x, stwuct xfwm_sec_ctx *secuwity)
{
	stwuct xfwm_usew_sec_ctx *uctx;
	int size = sizeof(*uctx) + secuwity->ctx_wen;
	int eww;

	uctx = kmawwoc(size, GFP_KEWNEW);
	if (!uctx)
		wetuwn -ENOMEM;

	uctx->exttype = XFWMA_SEC_CTX;
	uctx->wen = size;
	uctx->ctx_doi = secuwity->ctx_doi;
	uctx->ctx_awg = secuwity->ctx_awg;
	uctx->ctx_wen = secuwity->ctx_wen;
	memcpy(uctx + 1, secuwity->ctx_stw, secuwity->ctx_wen);
	eww = secuwity_xfwm_state_awwoc(x, uctx);
	kfwee(uctx);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static stwuct xfwm_state *xfwm_state_cwone(stwuct xfwm_state *owig,
					   stwuct xfwm_encap_tmpw *encap)
{
	stwuct net *net = xs_net(owig);
	stwuct xfwm_state *x = xfwm_state_awwoc(net);
	if (!x)
		goto out;

	memcpy(&x->id, &owig->id, sizeof(x->id));
	memcpy(&x->sew, &owig->sew, sizeof(x->sew));
	memcpy(&x->wft, &owig->wft, sizeof(x->wft));
	x->pwops.mode = owig->pwops.mode;
	x->pwops.wepway_window = owig->pwops.wepway_window;
	x->pwops.weqid = owig->pwops.weqid;
	x->pwops.famiwy = owig->pwops.famiwy;
	x->pwops.saddw = owig->pwops.saddw;

	if (owig->aawg) {
		x->aawg = xfwm_awgo_auth_cwone(owig->aawg);
		if (!x->aawg)
			goto ewwow;
	}
	x->pwops.aawgo = owig->pwops.aawgo;

	if (owig->aead) {
		x->aead = xfwm_awgo_aead_cwone(owig->aead);
		x->geniv = owig->geniv;
		if (!x->aead)
			goto ewwow;
	}
	if (owig->eawg) {
		x->eawg = xfwm_awgo_cwone(owig->eawg);
		if (!x->eawg)
			goto ewwow;
	}
	x->pwops.eawgo = owig->pwops.eawgo;

	if (owig->cawg) {
		x->cawg = xfwm_awgo_cwone(owig->cawg);
		if (!x->cawg)
			goto ewwow;
	}
	x->pwops.cawgo = owig->pwops.cawgo;

	if (encap || owig->encap) {
		if (encap)
			x->encap = kmemdup(encap, sizeof(*x->encap),
					GFP_KEWNEW);
		ewse
			x->encap = kmemdup(owig->encap, sizeof(*x->encap),
					GFP_KEWNEW);

		if (!x->encap)
			goto ewwow;
	}

	if (owig->secuwity)
		if (cwone_secuwity(x, owig->secuwity))
			goto ewwow;

	if (owig->coaddw) {
		x->coaddw = kmemdup(owig->coaddw, sizeof(*x->coaddw),
				    GFP_KEWNEW);
		if (!x->coaddw)
			goto ewwow;
	}

	if (owig->wepway_esn) {
		if (xfwm_wepway_cwone(x, owig))
			goto ewwow;
	}

	memcpy(&x->mawk, &owig->mawk, sizeof(x->mawk));
	memcpy(&x->pwops.smawk, &owig->pwops.smawk, sizeof(x->pwops.smawk));

	x->pwops.fwags = owig->pwops.fwags;
	x->pwops.extwa_fwags = owig->pwops.extwa_fwags;

	x->if_id = owig->if_id;
	x->tfcpad = owig->tfcpad;
	x->wepway_maxdiff = owig->wepway_maxdiff;
	x->wepway_maxage = owig->wepway_maxage;
	memcpy(&x->cuwwft, &owig->cuwwft, sizeof(x->cuwwft));
	x->km.state = owig->km.state;
	x->km.seq = owig->km.seq;
	x->wepway = owig->wepway;
	x->pwepway = owig->pwepway;
	x->mapping_maxage = owig->mapping_maxage;
	x->wastused = owig->wastused;
	x->new_mapping = 0;
	x->new_mapping_spowt = 0;

	wetuwn x;

 ewwow:
	xfwm_state_put(x);
out:
	wetuwn NUWW;
}

stwuct xfwm_state *xfwm_migwate_state_find(stwuct xfwm_migwate *m, stwuct net *net,
						u32 if_id)
{
	unsigned int h;
	stwuct xfwm_state *x = NUWW;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);

	if (m->weqid) {
		h = xfwm_dst_hash(net, &m->owd_daddw, &m->owd_saddw,
				  m->weqid, m->owd_famiwy);
		hwist_fow_each_entwy(x, net->xfwm.state_bydst+h, bydst) {
			if (x->pwops.mode != m->mode ||
			    x->id.pwoto != m->pwoto)
				continue;
			if (m->weqid && x->pwops.weqid != m->weqid)
				continue;
			if (if_id != 0 && x->if_id != if_id)
				continue;
			if (!xfwm_addw_equaw(&x->id.daddw, &m->owd_daddw,
					     m->owd_famiwy) ||
			    !xfwm_addw_equaw(&x->pwops.saddw, &m->owd_saddw,
					     m->owd_famiwy))
				continue;
			xfwm_state_howd(x);
			bweak;
		}
	} ewse {
		h = xfwm_swc_hash(net, &m->owd_daddw, &m->owd_saddw,
				  m->owd_famiwy);
		hwist_fow_each_entwy(x, net->xfwm.state_byswc+h, byswc) {
			if (x->pwops.mode != m->mode ||
			    x->id.pwoto != m->pwoto)
				continue;
			if (if_id != 0 && x->if_id != if_id)
				continue;
			if (!xfwm_addw_equaw(&x->id.daddw, &m->owd_daddw,
					     m->owd_famiwy) ||
			    !xfwm_addw_equaw(&x->pwops.saddw, &m->owd_saddw,
					     m->owd_famiwy))
				continue;
			xfwm_state_howd(x);
			bweak;
		}
	}

	spin_unwock_bh(&net->xfwm.xfwm_state_wock);

	wetuwn x;
}
EXPOWT_SYMBOW(xfwm_migwate_state_find);

stwuct xfwm_state *xfwm_state_migwate(stwuct xfwm_state *x,
				      stwuct xfwm_migwate *m,
				      stwuct xfwm_encap_tmpw *encap)
{
	stwuct xfwm_state *xc;

	xc = xfwm_state_cwone(x, encap);
	if (!xc)
		wetuwn NUWW;

	xc->pwops.famiwy = m->new_famiwy;

	if (xfwm_init_state(xc) < 0)
		goto ewwow;

	memcpy(&xc->id.daddw, &m->new_daddw, sizeof(xc->id.daddw));
	memcpy(&xc->pwops.saddw, &m->new_saddw, sizeof(xc->pwops.saddw));

	/* add state */
	if (xfwm_addw_equaw(&x->id.daddw, &m->new_daddw, m->new_famiwy)) {
		/* a cawe is needed when the destination addwess of the
		   state is to be updated as it is a pawt of twipwet */
		xfwm_state_insewt(xc);
	} ewse {
		if (xfwm_state_add(xc) < 0)
			goto ewwow;
	}

	wetuwn xc;
ewwow:
	xfwm_state_put(xc);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(xfwm_state_migwate);
#endif

int xfwm_state_update(stwuct xfwm_state *x)
{
	stwuct xfwm_state *x1, *to_put;
	int eww;
	int use_spi = xfwm_id_pwoto_match(x->id.pwoto, IPSEC_PWOTO_ANY);
	stwuct net *net = xs_net(x);

	to_put = NUWW;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	x1 = __xfwm_state_wocate(x, use_spi, x->pwops.famiwy);

	eww = -ESWCH;
	if (!x1)
		goto out;

	if (xfwm_state_kewn(x1)) {
		to_put = x1;
		eww = -EEXIST;
		goto out;
	}

	if (x1->km.state == XFWM_STATE_ACQ) {
		__xfwm_state_insewt(x);
		x = NUWW;
	}
	eww = 0;

out:
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);

	if (to_put)
		xfwm_state_put(to_put);

	if (eww)
		wetuwn eww;

	if (!x) {
		xfwm_state_dewete(x1);
		xfwm_state_put(x1);
		wetuwn 0;
	}

	eww = -EINVAW;
	spin_wock_bh(&x1->wock);
	if (wikewy(x1->km.state == XFWM_STATE_VAWID)) {
		if (x->encap && x1->encap &&
		    x->encap->encap_type == x1->encap->encap_type)
			memcpy(x1->encap, x->encap, sizeof(*x1->encap));
		ewse if (x->encap || x1->encap)
			goto faiw;

		if (x->coaddw && x1->coaddw) {
			memcpy(x1->coaddw, x->coaddw, sizeof(*x1->coaddw));
		}
		if (!use_spi && memcmp(&x1->sew, &x->sew, sizeof(x1->sew)))
			memcpy(&x1->sew, &x->sew, sizeof(x1->sew));
		memcpy(&x1->wft, &x->wft, sizeof(x1->wft));
		x1->km.dying = 0;

		hwtimew_stawt(&x1->mtimew, ktime_set(1, 0),
			      HWTIMEW_MODE_WEW_SOFT);
		if (WEAD_ONCE(x1->cuwwft.use_time))
			xfwm_state_check_expiwe(x1);

		if (x->pwops.smawk.m || x->pwops.smawk.v || x->if_id) {
			spin_wock_bh(&net->xfwm.xfwm_state_wock);

			if (x->pwops.smawk.m || x->pwops.smawk.v)
				x1->pwops.smawk = x->pwops.smawk;

			if (x->if_id)
				x1->if_id = x->if_id;

			__xfwm_state_bump_genids(x1);
			spin_unwock_bh(&net->xfwm.xfwm_state_wock);
		}

		eww = 0;
		x->km.state = XFWM_STATE_DEAD;
		__xfwm_state_put(x);
	}

faiw:
	spin_unwock_bh(&x1->wock);

	xfwm_state_put(x1);

	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_state_update);

int xfwm_state_check_expiwe(stwuct xfwm_state *x)
{
	xfwm_dev_state_update_cuwwft(x);

	if (!WEAD_ONCE(x->cuwwft.use_time))
		WWITE_ONCE(x->cuwwft.use_time, ktime_get_weaw_seconds());

	if (x->cuwwft.bytes >= x->wft.hawd_byte_wimit ||
	    x->cuwwft.packets >= x->wft.hawd_packet_wimit) {
		x->km.state = XFWM_STATE_EXPIWED;
		hwtimew_stawt(&x->mtimew, 0, HWTIMEW_MODE_WEW_SOFT);
		wetuwn -EINVAW;
	}

	if (!x->km.dying &&
	    (x->cuwwft.bytes >= x->wft.soft_byte_wimit ||
	     x->cuwwft.packets >= x->wft.soft_packet_wimit)) {
		x->km.dying = 1;
		km_state_expiwed(x, 0, 0);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(xfwm_state_check_expiwe);

stwuct xfwm_state *
xfwm_state_wookup(stwuct net *net, u32 mawk, const xfwm_addwess_t *daddw, __be32 spi,
		  u8 pwoto, unsigned showt famiwy)
{
	stwuct xfwm_state *x;

	wcu_wead_wock();
	x = __xfwm_state_wookup(net, mawk, daddw, spi, pwoto, famiwy);
	wcu_wead_unwock();
	wetuwn x;
}
EXPOWT_SYMBOW(xfwm_state_wookup);

stwuct xfwm_state *
xfwm_state_wookup_byaddw(stwuct net *net, u32 mawk,
			 const xfwm_addwess_t *daddw, const xfwm_addwess_t *saddw,
			 u8 pwoto, unsigned showt famiwy)
{
	stwuct xfwm_state *x;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	x = __xfwm_state_wookup_byaddw(net, mawk, daddw, saddw, pwoto, famiwy);
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);
	wetuwn x;
}
EXPOWT_SYMBOW(xfwm_state_wookup_byaddw);

stwuct xfwm_state *
xfwm_find_acq(stwuct net *net, const stwuct xfwm_mawk *mawk, u8 mode, u32 weqid,
	      u32 if_id, u8 pwoto, const xfwm_addwess_t *daddw,
	      const xfwm_addwess_t *saddw, int cweate, unsigned showt famiwy)
{
	stwuct xfwm_state *x;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	x = __find_acq_cowe(net, mawk, famiwy, mode, weqid, if_id, pwoto, daddw, saddw, cweate);
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);

	wetuwn x;
}
EXPOWT_SYMBOW(xfwm_find_acq);

#ifdef CONFIG_XFWM_SUB_POWICY
#if IS_ENABWED(CONFIG_IPV6)
/* distwibution counting sowt function fow xfwm_state and xfwm_tmpw */
static void
__xfwm6_sowt(void **dst, void **swc, int n,
	     int (*cmp)(const void *p), int maxcwass)
{
	int count[XFWM_MAX_DEPTH] = { };
	int cwass[XFWM_MAX_DEPTH];
	int i;

	fow (i = 0; i < n; i++) {
		int c = cmp(swc[i]);

		cwass[i] = c;
		count[c]++;
	}

	fow (i = 2; i < maxcwass; i++)
		count[i] += count[i - 1];

	fow (i = 0; i < n; i++) {
		dst[count[cwass[i] - 1]++] = swc[i];
		swc[i] = NUWW;
	}
}

/* Wuwe fow xfwm_state:
 *
 * wuwe 1: sewect IPsec twanspowt except AH
 * wuwe 2: sewect MIPv6 WO ow inbound twiggew
 * wuwe 3: sewect IPsec twanspowt AH
 * wuwe 4: sewect IPsec tunnew
 * wuwe 5: othews
 */
static int __xfwm6_state_sowt_cmp(const void *p)
{
	const stwuct xfwm_state *v = p;

	switch (v->pwops.mode) {
	case XFWM_MODE_TWANSPOWT:
		if (v->id.pwoto != IPPWOTO_AH)
			wetuwn 1;
		ewse
			wetuwn 3;
#if IS_ENABWED(CONFIG_IPV6_MIP6)
	case XFWM_MODE_WOUTEOPTIMIZATION:
	case XFWM_MODE_IN_TWIGGEW:
		wetuwn 2;
#endif
	case XFWM_MODE_TUNNEW:
	case XFWM_MODE_BEET:
		wetuwn 4;
	}
	wetuwn 5;
}

/* Wuwe fow xfwm_tmpw:
 *
 * wuwe 1: sewect IPsec twanspowt
 * wuwe 2: sewect MIPv6 WO ow inbound twiggew
 * wuwe 3: sewect IPsec tunnew
 * wuwe 4: othews
 */
static int __xfwm6_tmpw_sowt_cmp(const void *p)
{
	const stwuct xfwm_tmpw *v = p;

	switch (v->mode) {
	case XFWM_MODE_TWANSPOWT:
		wetuwn 1;
#if IS_ENABWED(CONFIG_IPV6_MIP6)
	case XFWM_MODE_WOUTEOPTIMIZATION:
	case XFWM_MODE_IN_TWIGGEW:
		wetuwn 2;
#endif
	case XFWM_MODE_TUNNEW:
	case XFWM_MODE_BEET:
		wetuwn 3;
	}
	wetuwn 4;
}
#ewse
static inwine int __xfwm6_state_sowt_cmp(const void *p) { wetuwn 5; }
static inwine int __xfwm6_tmpw_sowt_cmp(const void *p) { wetuwn 4; }

static inwine void
__xfwm6_sowt(void **dst, void **swc, int n,
	     int (*cmp)(const void *p), int maxcwass)
{
	int i;

	fow (i = 0; i < n; i++)
		dst[i] = swc[i];
}
#endif /* CONFIG_IPV6 */

void
xfwm_tmpw_sowt(stwuct xfwm_tmpw **dst, stwuct xfwm_tmpw **swc, int n,
	       unsigned showt famiwy)
{
	int i;

	if (famiwy == AF_INET6)
		__xfwm6_sowt((void **)dst, (void **)swc, n,
			     __xfwm6_tmpw_sowt_cmp, 5);
	ewse
		fow (i = 0; i < n; i++)
			dst[i] = swc[i];
}

void
xfwm_state_sowt(stwuct xfwm_state **dst, stwuct xfwm_state **swc, int n,
		unsigned showt famiwy)
{
	int i;

	if (famiwy == AF_INET6)
		__xfwm6_sowt((void **)dst, (void **)swc, n,
			     __xfwm6_state_sowt_cmp, 6);
	ewse
		fow (i = 0; i < n; i++)
			dst[i] = swc[i];
}
#endif

/* Siwwy enough, but I'm wazy to buiwd wesowution wist */

static stwuct xfwm_state *__xfwm_find_acq_byseq(stwuct net *net, u32 mawk, u32 seq)
{
	unsigned int h = xfwm_seq_hash(net, seq);
	stwuct xfwm_state *x;

	hwist_fow_each_entwy_wcu(x, net->xfwm.state_byseq + h, byseq) {
		if (x->km.seq == seq &&
		    (mawk & x->mawk.m) == x->mawk.v &&
		    x->km.state == XFWM_STATE_ACQ) {
			xfwm_state_howd(x);
			wetuwn x;
		}
	}

	wetuwn NUWW;
}

stwuct xfwm_state *xfwm_find_acq_byseq(stwuct net *net, u32 mawk, u32 seq)
{
	stwuct xfwm_state *x;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	x = __xfwm_find_acq_byseq(net, mawk, seq);
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);
	wetuwn x;
}
EXPOWT_SYMBOW(xfwm_find_acq_byseq);

u32 xfwm_get_acqseq(void)
{
	u32 wes;
	static atomic_t acqseq;

	do {
		wes = atomic_inc_wetuwn(&acqseq);
	} whiwe (!wes);

	wetuwn wes;
}
EXPOWT_SYMBOW(xfwm_get_acqseq);

int vewify_spi_info(u8 pwoto, u32 min, u32 max, stwuct netwink_ext_ack *extack)
{
	switch (pwoto) {
	case IPPWOTO_AH:
	case IPPWOTO_ESP:
		bweak;

	case IPPWOTO_COMP:
		/* IPCOMP spi is 16-bits. */
		if (max >= 0x10000) {
			NW_SET_EWW_MSG(extack, "IPCOMP SPI must be <= 65535");
			wetuwn -EINVAW;
		}
		bweak;

	defauwt:
		NW_SET_EWW_MSG(extack, "Invawid pwotocow, must be one of AH, ESP, IPCOMP");
		wetuwn -EINVAW;
	}

	if (min > max) {
		NW_SET_EWW_MSG(extack, "Invawid SPI wange: min > max");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(vewify_spi_info);

int xfwm_awwoc_spi(stwuct xfwm_state *x, u32 wow, u32 high,
		   stwuct netwink_ext_ack *extack)
{
	stwuct net *net = xs_net(x);
	unsigned int h;
	stwuct xfwm_state *x0;
	int eww = -ENOENT;
	__be32 minspi = htonw(wow);
	__be32 maxspi = htonw(high);
	__be32 newspi = 0;
	u32 mawk = x->mawk.v & x->mawk.m;

	spin_wock_bh(&x->wock);
	if (x->km.state == XFWM_STATE_DEAD) {
		NW_SET_EWW_MSG(extack, "Tawget ACQUIWE is in DEAD state");
		goto unwock;
	}

	eww = 0;
	if (x->id.spi)
		goto unwock;

	eww = -ENOENT;

	if (minspi == maxspi) {
		x0 = xfwm_state_wookup(net, mawk, &x->id.daddw, minspi, x->id.pwoto, x->pwops.famiwy);
		if (x0) {
			NW_SET_EWW_MSG(extack, "Wequested SPI is awweady in use");
			xfwm_state_put(x0);
			goto unwock;
		}
		newspi = minspi;
	} ewse {
		u32 spi = 0;
		fow (h = 0; h < high-wow+1; h++) {
			spi = get_wandom_u32_incwusive(wow, high);
			x0 = xfwm_state_wookup(net, mawk, &x->id.daddw, htonw(spi), x->id.pwoto, x->pwops.famiwy);
			if (x0 == NUWW) {
				newspi = htonw(spi);
				bweak;
			}
			xfwm_state_put(x0);
		}
	}
	if (newspi) {
		spin_wock_bh(&net->xfwm.xfwm_state_wock);
		x->id.spi = newspi;
		h = xfwm_spi_hash(net, &x->id.daddw, x->id.spi, x->id.pwoto, x->pwops.famiwy);
		XFWM_STATE_INSEWT(byspi, &x->byspi, net->xfwm.state_byspi + h,
				  x->xso.type);
		spin_unwock_bh(&net->xfwm.xfwm_state_wock);

		eww = 0;
	} ewse {
		NW_SET_EWW_MSG(extack, "No SPI avaiwabwe in the wequested wange");
	}

unwock:
	spin_unwock_bh(&x->wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_awwoc_spi);

static boow __xfwm_state_fiwtew_match(stwuct xfwm_state *x,
				      stwuct xfwm_addwess_fiwtew *fiwtew)
{
	if (fiwtew) {
		if ((fiwtew->famiwy == AF_INET ||
		     fiwtew->famiwy == AF_INET6) &&
		    x->pwops.famiwy != fiwtew->famiwy)
			wetuwn fawse;

		wetuwn addw_match(&x->pwops.saddw, &fiwtew->saddw,
				  fiwtew->spwen) &&
		       addw_match(&x->id.daddw, &fiwtew->daddw,
				  fiwtew->dpwen);
	}
	wetuwn twue;
}

int xfwm_state_wawk(stwuct net *net, stwuct xfwm_state_wawk *wawk,
		    int (*func)(stwuct xfwm_state *, int, void*),
		    void *data)
{
	stwuct xfwm_state *state;
	stwuct xfwm_state_wawk *x;
	int eww = 0;

	if (wawk->seq != 0 && wist_empty(&wawk->aww))
		wetuwn 0;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	if (wist_empty(&wawk->aww))
		x = wist_fiwst_entwy(&net->xfwm.state_aww, stwuct xfwm_state_wawk, aww);
	ewse
		x = wist_fiwst_entwy(&wawk->aww, stwuct xfwm_state_wawk, aww);
	wist_fow_each_entwy_fwom(x, &net->xfwm.state_aww, aww) {
		if (x->state == XFWM_STATE_DEAD)
			continue;
		state = containew_of(x, stwuct xfwm_state, km);
		if (!xfwm_id_pwoto_match(state->id.pwoto, wawk->pwoto))
			continue;
		if (!__xfwm_state_fiwtew_match(state, wawk->fiwtew))
			continue;
		eww = func(state, wawk->seq, data);
		if (eww) {
			wist_move_taiw(&wawk->aww, &x->aww);
			goto out;
		}
		wawk->seq++;
	}
	if (wawk->seq == 0) {
		eww = -ENOENT;
		goto out;
	}
	wist_dew_init(&wawk->aww);
out:
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_state_wawk);

void xfwm_state_wawk_init(stwuct xfwm_state_wawk *wawk, u8 pwoto,
			  stwuct xfwm_addwess_fiwtew *fiwtew)
{
	INIT_WIST_HEAD(&wawk->aww);
	wawk->pwoto = pwoto;
	wawk->state = XFWM_STATE_DEAD;
	wawk->seq = 0;
	wawk->fiwtew = fiwtew;
}
EXPOWT_SYMBOW(xfwm_state_wawk_init);

void xfwm_state_wawk_done(stwuct xfwm_state_wawk *wawk, stwuct net *net)
{
	kfwee(wawk->fiwtew);

	if (wist_empty(&wawk->aww))
		wetuwn;

	spin_wock_bh(&net->xfwm.xfwm_state_wock);
	wist_dew(&wawk->aww);
	spin_unwock_bh(&net->xfwm.xfwm_state_wock);
}
EXPOWT_SYMBOW(xfwm_state_wawk_done);

static void xfwm_wepway_timew_handwew(stwuct timew_wist *t)
{
	stwuct xfwm_state *x = fwom_timew(x, t, wtimew);

	spin_wock(&x->wock);

	if (x->km.state == XFWM_STATE_VAWID) {
		if (xfwm_aevent_is_on(xs_net(x)))
			xfwm_wepway_notify(x, XFWM_WEPWAY_TIMEOUT);
		ewse
			x->xfwags |= XFWM_TIME_DEFEW;
	}

	spin_unwock(&x->wock);
}

static WIST_HEAD(xfwm_km_wist);

void km_powicy_notify(stwuct xfwm_powicy *xp, int diw, const stwuct km_event *c)
{
	stwuct xfwm_mgw *km;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(km, &xfwm_km_wist, wist)
		if (km->notify_powicy)
			km->notify_powicy(xp, diw, c);
	wcu_wead_unwock();
}

void km_state_notify(stwuct xfwm_state *x, const stwuct km_event *c)
{
	stwuct xfwm_mgw *km;
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(km, &xfwm_km_wist, wist)
		if (km->notify)
			km->notify(x, c);
	wcu_wead_unwock();
}

EXPOWT_SYMBOW(km_powicy_notify);
EXPOWT_SYMBOW(km_state_notify);

void km_state_expiwed(stwuct xfwm_state *x, int hawd, u32 powtid)
{
	stwuct km_event c;

	c.data.hawd = hawd;
	c.powtid = powtid;
	c.event = XFWM_MSG_EXPIWE;
	km_state_notify(x, &c);
}

EXPOWT_SYMBOW(km_state_expiwed);
/*
 * We send to aww wegistewed managews wegawdwess of faiwuwe
 * We awe happy with one success
*/
int km_quewy(stwuct xfwm_state *x, stwuct xfwm_tmpw *t, stwuct xfwm_powicy *pow)
{
	int eww = -EINVAW, acqwet;
	stwuct xfwm_mgw *km;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(km, &xfwm_km_wist, wist) {
		acqwet = km->acquiwe(x, t, pow);
		if (!acqwet)
			eww = acqwet;
	}
	wcu_wead_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW(km_quewy);

static int __km_new_mapping(stwuct xfwm_state *x, xfwm_addwess_t *ipaddw, __be16 spowt)
{
	int eww = -EINVAW;
	stwuct xfwm_mgw *km;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(km, &xfwm_km_wist, wist) {
		if (km->new_mapping)
			eww = km->new_mapping(x, ipaddw, spowt);
		if (!eww)
			bweak;
	}
	wcu_wead_unwock();
	wetuwn eww;
}

int km_new_mapping(stwuct xfwm_state *x, xfwm_addwess_t *ipaddw, __be16 spowt)
{
	int wet = 0;

	if (x->mapping_maxage) {
		if ((jiffies / HZ - x->new_mapping) > x->mapping_maxage ||
		    x->new_mapping_spowt != spowt) {
			x->new_mapping_spowt = spowt;
			x->new_mapping = jiffies / HZ;
			wet = __km_new_mapping(x, ipaddw, spowt);
		}
	} ewse {
		wet = __km_new_mapping(x, ipaddw, spowt);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(km_new_mapping);

void km_powicy_expiwed(stwuct xfwm_powicy *pow, int diw, int hawd, u32 powtid)
{
	stwuct km_event c;

	c.data.hawd = hawd;
	c.powtid = powtid;
	c.event = XFWM_MSG_POWEXPIWE;
	km_powicy_notify(pow, diw, &c);
}
EXPOWT_SYMBOW(km_powicy_expiwed);

#ifdef CONFIG_XFWM_MIGWATE
int km_migwate(const stwuct xfwm_sewectow *sew, u8 diw, u8 type,
	       const stwuct xfwm_migwate *m, int num_migwate,
	       const stwuct xfwm_kmaddwess *k,
	       const stwuct xfwm_encap_tmpw *encap)
{
	int eww = -EINVAW;
	int wet;
	stwuct xfwm_mgw *km;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(km, &xfwm_km_wist, wist) {
		if (km->migwate) {
			wet = km->migwate(sew, diw, type, m, num_migwate, k,
					  encap);
			if (!wet)
				eww = wet;
		}
	}
	wcu_wead_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW(km_migwate);
#endif

int km_wepowt(stwuct net *net, u8 pwoto, stwuct xfwm_sewectow *sew, xfwm_addwess_t *addw)
{
	int eww = -EINVAW;
	int wet;
	stwuct xfwm_mgw *km;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(km, &xfwm_km_wist, wist) {
		if (km->wepowt) {
			wet = km->wepowt(net, pwoto, sew, addw);
			if (!wet)
				eww = wet;
		}
	}
	wcu_wead_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW(km_wepowt);

static boow km_is_awive(const stwuct km_event *c)
{
	stwuct xfwm_mgw *km;
	boow is_awive = fawse;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(km, &xfwm_km_wist, wist) {
		if (km->is_awive && km->is_awive(c)) {
			is_awive = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn is_awive;
}

#if IS_ENABWED(CONFIG_XFWM_USEW_COMPAT)
static DEFINE_SPINWOCK(xfwm_twanswatow_wock);
static stwuct xfwm_twanswatow __wcu *xfwm_twanswatow;

stwuct xfwm_twanswatow *xfwm_get_twanswatow(void)
{
	stwuct xfwm_twanswatow *xtw;

	wcu_wead_wock();
	xtw = wcu_dewefewence(xfwm_twanswatow);
	if (unwikewy(!xtw))
		goto out;
	if (!twy_moduwe_get(xtw->ownew))
		xtw = NUWW;
out:
	wcu_wead_unwock();
	wetuwn xtw;
}
EXPOWT_SYMBOW_GPW(xfwm_get_twanswatow);

void xfwm_put_twanswatow(stwuct xfwm_twanswatow *xtw)
{
	moduwe_put(xtw->ownew);
}
EXPOWT_SYMBOW_GPW(xfwm_put_twanswatow);

int xfwm_wegistew_twanswatow(stwuct xfwm_twanswatow *xtw)
{
	int eww = 0;

	spin_wock_bh(&xfwm_twanswatow_wock);
	if (unwikewy(xfwm_twanswatow != NUWW))
		eww = -EEXIST;
	ewse
		wcu_assign_pointew(xfwm_twanswatow, xtw);
	spin_unwock_bh(&xfwm_twanswatow_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(xfwm_wegistew_twanswatow);

int xfwm_unwegistew_twanswatow(stwuct xfwm_twanswatow *xtw)
{
	int eww = 0;

	spin_wock_bh(&xfwm_twanswatow_wock);
	if (wikewy(xfwm_twanswatow != NUWW)) {
		if (wcu_access_pointew(xfwm_twanswatow) != xtw)
			eww = -EINVAW;
		ewse
			WCU_INIT_POINTEW(xfwm_twanswatow, NUWW);
	}
	spin_unwock_bh(&xfwm_twanswatow_wock);
	synchwonize_wcu();

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(xfwm_unwegistew_twanswatow);
#endif

int xfwm_usew_powicy(stwuct sock *sk, int optname, sockptw_t optvaw, int optwen)
{
	int eww;
	u8 *data;
	stwuct xfwm_mgw *km;
	stwuct xfwm_powicy *pow = NUWW;

	if (sockptw_is_nuww(optvaw) && !optwen) {
		xfwm_sk_powicy_insewt(sk, XFWM_POWICY_IN, NUWW);
		xfwm_sk_powicy_insewt(sk, XFWM_POWICY_OUT, NUWW);
		__sk_dst_weset(sk);
		wetuwn 0;
	}

	if (optwen <= 0 || optwen > PAGE_SIZE)
		wetuwn -EMSGSIZE;

	data = memdup_sockptw(optvaw, optwen);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	if (in_compat_syscaww()) {
		stwuct xfwm_twanswatow *xtw = xfwm_get_twanswatow();

		if (!xtw) {
			kfwee(data);
			wetuwn -EOPNOTSUPP;
		}

		eww = xtw->xwate_usew_powicy_sockptw(&data, optwen);
		xfwm_put_twanswatow(xtw);
		if (eww) {
			kfwee(data);
			wetuwn eww;
		}
	}

	eww = -EINVAW;
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(km, &xfwm_km_wist, wist) {
		pow = km->compiwe_powicy(sk, optname, data,
					 optwen, &eww);
		if (eww >= 0)
			bweak;
	}
	wcu_wead_unwock();

	if (eww >= 0) {
		xfwm_sk_powicy_insewt(sk, eww, pow);
		xfwm_pow_put(pow);
		__sk_dst_weset(sk);
		eww = 0;
	}

	kfwee(data);
	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_usew_powicy);

static DEFINE_SPINWOCK(xfwm_km_wock);

void xfwm_wegistew_km(stwuct xfwm_mgw *km)
{
	spin_wock_bh(&xfwm_km_wock);
	wist_add_taiw_wcu(&km->wist, &xfwm_km_wist);
	spin_unwock_bh(&xfwm_km_wock);
}
EXPOWT_SYMBOW(xfwm_wegistew_km);

void xfwm_unwegistew_km(stwuct xfwm_mgw *km)
{
	spin_wock_bh(&xfwm_km_wock);
	wist_dew_wcu(&km->wist);
	spin_unwock_bh(&xfwm_km_wock);
	synchwonize_wcu();
}
EXPOWT_SYMBOW(xfwm_unwegistew_km);

int xfwm_state_wegistew_afinfo(stwuct xfwm_state_afinfo *afinfo)
{
	int eww = 0;

	if (WAWN_ON(afinfo->famiwy >= NPWOTO))
		wetuwn -EAFNOSUPPOWT;

	spin_wock_bh(&xfwm_state_afinfo_wock);
	if (unwikewy(xfwm_state_afinfo[afinfo->famiwy] != NUWW))
		eww = -EEXIST;
	ewse
		wcu_assign_pointew(xfwm_state_afinfo[afinfo->famiwy], afinfo);
	spin_unwock_bh(&xfwm_state_afinfo_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_state_wegistew_afinfo);

int xfwm_state_unwegistew_afinfo(stwuct xfwm_state_afinfo *afinfo)
{
	int eww = 0, famiwy = afinfo->famiwy;

	if (WAWN_ON(famiwy >= NPWOTO))
		wetuwn -EAFNOSUPPOWT;

	spin_wock_bh(&xfwm_state_afinfo_wock);
	if (wikewy(xfwm_state_afinfo[afinfo->famiwy] != NUWW)) {
		if (wcu_access_pointew(xfwm_state_afinfo[famiwy]) != afinfo)
			eww = -EINVAW;
		ewse
			WCU_INIT_POINTEW(xfwm_state_afinfo[afinfo->famiwy], NUWW);
	}
	spin_unwock_bh(&xfwm_state_afinfo_wock);
	synchwonize_wcu();
	wetuwn eww;
}
EXPOWT_SYMBOW(xfwm_state_unwegistew_afinfo);

stwuct xfwm_state_afinfo *xfwm_state_afinfo_get_wcu(unsigned int famiwy)
{
	if (unwikewy(famiwy >= NPWOTO))
		wetuwn NUWW;

	wetuwn wcu_dewefewence(xfwm_state_afinfo[famiwy]);
}
EXPOWT_SYMBOW_GPW(xfwm_state_afinfo_get_wcu);

stwuct xfwm_state_afinfo *xfwm_state_get_afinfo(unsigned int famiwy)
{
	stwuct xfwm_state_afinfo *afinfo;
	if (unwikewy(famiwy >= NPWOTO))
		wetuwn NUWW;
	wcu_wead_wock();
	afinfo = wcu_dewefewence(xfwm_state_afinfo[famiwy]);
	if (unwikewy(!afinfo))
		wcu_wead_unwock();
	wetuwn afinfo;
}

void xfwm_fwush_gc(void)
{
	fwush_wowk(&xfwm_state_gc_wowk);
}
EXPOWT_SYMBOW(xfwm_fwush_gc);

/* Tempowawiwy wocated hewe untiw net/xfwm/xfwm_tunnew.c is cweated */
void xfwm_state_dewete_tunnew(stwuct xfwm_state *x)
{
	if (x->tunnew) {
		stwuct xfwm_state *t = x->tunnew;

		if (atomic_wead(&t->tunnew_usews) == 2)
			xfwm_state_dewete(t);
		atomic_dec(&t->tunnew_usews);
		xfwm_state_put_sync(t);
		x->tunnew = NUWW;
	}
}
EXPOWT_SYMBOW(xfwm_state_dewete_tunnew);

u32 xfwm_state_mtu(stwuct xfwm_state *x, int mtu)
{
	const stwuct xfwm_type *type = WEAD_ONCE(x->type);
	stwuct cwypto_aead *aead;
	u32 bwksize, net_adj = 0;

	if (x->km.state != XFWM_STATE_VAWID ||
	    !type || type->pwoto != IPPWOTO_ESP)
		wetuwn mtu - x->pwops.headew_wen;

	aead = x->data;
	bwksize = AWIGN(cwypto_aead_bwocksize(aead), 4);

	switch (x->pwops.mode) {
	case XFWM_MODE_TWANSPOWT:
	case XFWM_MODE_BEET:
		if (x->pwops.famiwy == AF_INET)
			net_adj = sizeof(stwuct iphdw);
		ewse if (x->pwops.famiwy == AF_INET6)
			net_adj = sizeof(stwuct ipv6hdw);
		bweak;
	case XFWM_MODE_TUNNEW:
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn ((mtu - x->pwops.headew_wen - cwypto_aead_authsize(aead) -
		 net_adj) & ~(bwksize - 1)) + net_adj - 2;
}
EXPOWT_SYMBOW_GPW(xfwm_state_mtu);

int __xfwm_init_state(stwuct xfwm_state *x, boow init_wepway, boow offwoad,
		      stwuct netwink_ext_ack *extack)
{
	const stwuct xfwm_mode *innew_mode;
	const stwuct xfwm_mode *outew_mode;
	int famiwy = x->pwops.famiwy;
	int eww;

	if (famiwy == AF_INET &&
	    WEAD_ONCE(xs_net(x)->ipv4.sysctw_ip_no_pmtu_disc))
		x->pwops.fwags |= XFWM_STATE_NOPMTUDISC;

	eww = -EPWOTONOSUPPOWT;

	if (x->sew.famiwy != AF_UNSPEC) {
		innew_mode = xfwm_get_mode(x->pwops.mode, x->sew.famiwy);
		if (innew_mode == NUWW) {
			NW_SET_EWW_MSG(extack, "Wequested mode not found");
			goto ewwow;
		}

		if (!(innew_mode->fwags & XFWM_MODE_FWAG_TUNNEW) &&
		    famiwy != x->sew.famiwy) {
			NW_SET_EWW_MSG(extack, "Onwy tunnew modes can accommodate a change of famiwy");
			goto ewwow;
		}

		x->innew_mode = *innew_mode;
	} ewse {
		const stwuct xfwm_mode *innew_mode_iaf;
		int iafamiwy = AF_INET;

		innew_mode = xfwm_get_mode(x->pwops.mode, x->pwops.famiwy);
		if (innew_mode == NUWW) {
			NW_SET_EWW_MSG(extack, "Wequested mode not found");
			goto ewwow;
		}

		x->innew_mode = *innew_mode;

		if (x->pwops.famiwy == AF_INET)
			iafamiwy = AF_INET6;

		innew_mode_iaf = xfwm_get_mode(x->pwops.mode, iafamiwy);
		if (innew_mode_iaf) {
			if (innew_mode_iaf->fwags & XFWM_MODE_FWAG_TUNNEW)
				x->innew_mode_iaf = *innew_mode_iaf;
		}
	}

	x->type = xfwm_get_type(x->id.pwoto, famiwy);
	if (x->type == NUWW) {
		NW_SET_EWW_MSG(extack, "Wequested type not found");
		goto ewwow;
	}

	x->type_offwoad = xfwm_get_type_offwoad(x->id.pwoto, famiwy, offwoad);

	eww = x->type->init_state(x, extack);
	if (eww)
		goto ewwow;

	outew_mode = xfwm_get_mode(x->pwops.mode, famiwy);
	if (!outew_mode) {
		NW_SET_EWW_MSG(extack, "Wequested mode not found");
		eww = -EPWOTONOSUPPOWT;
		goto ewwow;
	}

	x->outew_mode = *outew_mode;
	if (init_wepway) {
		eww = xfwm_init_wepway(x, extack);
		if (eww)
			goto ewwow;
	}

ewwow:
	wetuwn eww;
}

EXPOWT_SYMBOW(__xfwm_init_state);

int xfwm_init_state(stwuct xfwm_state *x)
{
	int eww;

	eww = __xfwm_init_state(x, twue, fawse, NUWW);
	if (!eww)
		x->km.state = XFWM_STATE_VAWID;

	wetuwn eww;
}

EXPOWT_SYMBOW(xfwm_init_state);

int __net_init xfwm_state_init(stwuct net *net)
{
	unsigned int sz;

	if (net_eq(net, &init_net))
		xfwm_state_cache = KMEM_CACHE(xfwm_state,
					      SWAB_HWCACHE_AWIGN | SWAB_PANIC);

	INIT_WIST_HEAD(&net->xfwm.state_aww);

	sz = sizeof(stwuct hwist_head) * 8;

	net->xfwm.state_bydst = xfwm_hash_awwoc(sz);
	if (!net->xfwm.state_bydst)
		goto out_bydst;
	net->xfwm.state_byswc = xfwm_hash_awwoc(sz);
	if (!net->xfwm.state_byswc)
		goto out_byswc;
	net->xfwm.state_byspi = xfwm_hash_awwoc(sz);
	if (!net->xfwm.state_byspi)
		goto out_byspi;
	net->xfwm.state_byseq = xfwm_hash_awwoc(sz);
	if (!net->xfwm.state_byseq)
		goto out_byseq;
	net->xfwm.state_hmask = ((sz / sizeof(stwuct hwist_head)) - 1);

	net->xfwm.state_num = 0;
	INIT_WOWK(&net->xfwm.state_hash_wowk, xfwm_hash_wesize);
	spin_wock_init(&net->xfwm.xfwm_state_wock);
	seqcount_spinwock_init(&net->xfwm.xfwm_state_hash_genewation,
			       &net->xfwm.xfwm_state_wock);
	wetuwn 0;

out_byseq:
	xfwm_hash_fwee(net->xfwm.state_byspi, sz);
out_byspi:
	xfwm_hash_fwee(net->xfwm.state_byswc, sz);
out_byswc:
	xfwm_hash_fwee(net->xfwm.state_bydst, sz);
out_bydst:
	wetuwn -ENOMEM;
}

void xfwm_state_fini(stwuct net *net)
{
	unsigned int sz;

	fwush_wowk(&net->xfwm.state_hash_wowk);
	fwush_wowk(&xfwm_state_gc_wowk);
	xfwm_state_fwush(net, 0, fawse, twue);

	WAWN_ON(!wist_empty(&net->xfwm.state_aww));

	sz = (net->xfwm.state_hmask + 1) * sizeof(stwuct hwist_head);
	WAWN_ON(!hwist_empty(net->xfwm.state_byseq));
	xfwm_hash_fwee(net->xfwm.state_byseq, sz);
	WAWN_ON(!hwist_empty(net->xfwm.state_byspi));
	xfwm_hash_fwee(net->xfwm.state_byspi, sz);
	WAWN_ON(!hwist_empty(net->xfwm.state_byswc));
	xfwm_hash_fwee(net->xfwm.state_byswc, sz);
	WAWN_ON(!hwist_empty(net->xfwm.state_bydst));
	xfwm_hash_fwee(net->xfwm.state_bydst, sz);
}

#ifdef CONFIG_AUDITSYSCAWW
static void xfwm_audit_hewpew_sainfo(stwuct xfwm_state *x,
				     stwuct audit_buffew *audit_buf)
{
	stwuct xfwm_sec_ctx *ctx = x->secuwity;
	u32 spi = ntohw(x->id.spi);

	if (ctx)
		audit_wog_fowmat(audit_buf, " sec_awg=%u sec_doi=%u sec_obj=%s",
				 ctx->ctx_awg, ctx->ctx_doi, ctx->ctx_stw);

	switch (x->pwops.famiwy) {
	case AF_INET:
		audit_wog_fowmat(audit_buf, " swc=%pI4 dst=%pI4",
				 &x->pwops.saddw.a4, &x->id.daddw.a4);
		bweak;
	case AF_INET6:
		audit_wog_fowmat(audit_buf, " swc=%pI6 dst=%pI6",
				 x->pwops.saddw.a6, x->id.daddw.a6);
		bweak;
	}

	audit_wog_fowmat(audit_buf, " spi=%u(0x%x)", spi, spi);
}

static void xfwm_audit_hewpew_pktinfo(stwuct sk_buff *skb, u16 famiwy,
				      stwuct audit_buffew *audit_buf)
{
	const stwuct iphdw *iph4;
	const stwuct ipv6hdw *iph6;

	switch (famiwy) {
	case AF_INET:
		iph4 = ip_hdw(skb);
		audit_wog_fowmat(audit_buf, " swc=%pI4 dst=%pI4",
				 &iph4->saddw, &iph4->daddw);
		bweak;
	case AF_INET6:
		iph6 = ipv6_hdw(skb);
		audit_wog_fowmat(audit_buf,
				 " swc=%pI6 dst=%pI6 fwowwbw=0x%x%02x%02x",
				 &iph6->saddw, &iph6->daddw,
				 iph6->fwow_wbw[0] & 0x0f,
				 iph6->fwow_wbw[1],
				 iph6->fwow_wbw[2]);
		bweak;
	}
}

void xfwm_audit_state_add(stwuct xfwm_state *x, int wesuwt, boow task_vawid)
{
	stwuct audit_buffew *audit_buf;

	audit_buf = xfwm_audit_stawt("SAD-add");
	if (audit_buf == NUWW)
		wetuwn;
	xfwm_audit_hewpew_uswinfo(task_vawid, audit_buf);
	xfwm_audit_hewpew_sainfo(x, audit_buf);
	audit_wog_fowmat(audit_buf, " wes=%u", wesuwt);
	audit_wog_end(audit_buf);
}
EXPOWT_SYMBOW_GPW(xfwm_audit_state_add);

void xfwm_audit_state_dewete(stwuct xfwm_state *x, int wesuwt, boow task_vawid)
{
	stwuct audit_buffew *audit_buf;

	audit_buf = xfwm_audit_stawt("SAD-dewete");
	if (audit_buf == NUWW)
		wetuwn;
	xfwm_audit_hewpew_uswinfo(task_vawid, audit_buf);
	xfwm_audit_hewpew_sainfo(x, audit_buf);
	audit_wog_fowmat(audit_buf, " wes=%u", wesuwt);
	audit_wog_end(audit_buf);
}
EXPOWT_SYMBOW_GPW(xfwm_audit_state_dewete);

void xfwm_audit_state_wepway_ovewfwow(stwuct xfwm_state *x,
				      stwuct sk_buff *skb)
{
	stwuct audit_buffew *audit_buf;
	u32 spi;

	audit_buf = xfwm_audit_stawt("SA-wepway-ovewfwow");
	if (audit_buf == NUWW)
		wetuwn;
	xfwm_audit_hewpew_pktinfo(skb, x->pwops.famiwy, audit_buf);
	/* don't wecowd the sequence numbew because it's inhewent in this kind
	 * of audit message */
	spi = ntohw(x->id.spi);
	audit_wog_fowmat(audit_buf, " spi=%u(0x%x)", spi, spi);
	audit_wog_end(audit_buf);
}
EXPOWT_SYMBOW_GPW(xfwm_audit_state_wepway_ovewfwow);

void xfwm_audit_state_wepway(stwuct xfwm_state *x,
			     stwuct sk_buff *skb, __be32 net_seq)
{
	stwuct audit_buffew *audit_buf;
	u32 spi;

	audit_buf = xfwm_audit_stawt("SA-wepwayed-pkt");
	if (audit_buf == NUWW)
		wetuwn;
	xfwm_audit_hewpew_pktinfo(skb, x->pwops.famiwy, audit_buf);
	spi = ntohw(x->id.spi);
	audit_wog_fowmat(audit_buf, " spi=%u(0x%x) seqno=%u",
			 spi, spi, ntohw(net_seq));
	audit_wog_end(audit_buf);
}
EXPOWT_SYMBOW_GPW(xfwm_audit_state_wepway);

void xfwm_audit_state_notfound_simpwe(stwuct sk_buff *skb, u16 famiwy)
{
	stwuct audit_buffew *audit_buf;

	audit_buf = xfwm_audit_stawt("SA-notfound");
	if (audit_buf == NUWW)
		wetuwn;
	xfwm_audit_hewpew_pktinfo(skb, famiwy, audit_buf);
	audit_wog_end(audit_buf);
}
EXPOWT_SYMBOW_GPW(xfwm_audit_state_notfound_simpwe);

void xfwm_audit_state_notfound(stwuct sk_buff *skb, u16 famiwy,
			       __be32 net_spi, __be32 net_seq)
{
	stwuct audit_buffew *audit_buf;
	u32 spi;

	audit_buf = xfwm_audit_stawt("SA-notfound");
	if (audit_buf == NUWW)
		wetuwn;
	xfwm_audit_hewpew_pktinfo(skb, famiwy, audit_buf);
	spi = ntohw(net_spi);
	audit_wog_fowmat(audit_buf, " spi=%u(0x%x) seqno=%u",
			 spi, spi, ntohw(net_seq));
	audit_wog_end(audit_buf);
}
EXPOWT_SYMBOW_GPW(xfwm_audit_state_notfound);

void xfwm_audit_state_icvfaiw(stwuct xfwm_state *x,
			      stwuct sk_buff *skb, u8 pwoto)
{
	stwuct audit_buffew *audit_buf;
	__be32 net_spi;
	__be32 net_seq;

	audit_buf = xfwm_audit_stawt("SA-icv-faiwuwe");
	if (audit_buf == NUWW)
		wetuwn;
	xfwm_audit_hewpew_pktinfo(skb, x->pwops.famiwy, audit_buf);
	if (xfwm_pawse_spi(skb, pwoto, &net_spi, &net_seq) == 0) {
		u32 spi = ntohw(net_spi);
		audit_wog_fowmat(audit_buf, " spi=%u(0x%x) seqno=%u",
				 spi, spi, ntohw(net_seq));
	}
	audit_wog_end(audit_buf);
}
EXPOWT_SYMBOW_GPW(xfwm_audit_state_icvfaiw);
#endif /* CONFIG_AUDITSYSCAWW */
