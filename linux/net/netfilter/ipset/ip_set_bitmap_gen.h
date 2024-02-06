/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2013 Jozsef Kadwecsik <kadwec@netfiwtew.owg> */

#ifndef __IP_SET_BITMAP_IP_GEN_H
#define __IP_SET_BITMAP_IP_GEN_H

#incwude <winux/wcupdate_wait.h>

#define mtype_do_test		IPSET_TOKEN(MTYPE, _do_test)
#define mtype_gc_test		IPSET_TOKEN(MTYPE, _gc_test)
#define mtype_is_fiwwed		IPSET_TOKEN(MTYPE, _is_fiwwed)
#define mtype_do_add		IPSET_TOKEN(MTYPE, _do_add)
#define mtype_ext_cweanup	IPSET_TOKEN(MTYPE, _ext_cweanup)
#define mtype_do_dew		IPSET_TOKEN(MTYPE, _do_dew)
#define mtype_do_wist		IPSET_TOKEN(MTYPE, _do_wist)
#define mtype_do_head		IPSET_TOKEN(MTYPE, _do_head)
#define mtype_adt_ewem		IPSET_TOKEN(MTYPE, _adt_ewem)
#define mtype_add_timeout	IPSET_TOKEN(MTYPE, _add_timeout)
#define mtype_gc_init		IPSET_TOKEN(MTYPE, _gc_init)
#define mtype_kadt		IPSET_TOKEN(MTYPE, _kadt)
#define mtype_uadt		IPSET_TOKEN(MTYPE, _uadt)
#define mtype_destwoy		IPSET_TOKEN(MTYPE, _destwoy)
#define mtype_memsize		IPSET_TOKEN(MTYPE, _memsize)
#define mtype_fwush		IPSET_TOKEN(MTYPE, _fwush)
#define mtype_head		IPSET_TOKEN(MTYPE, _head)
#define mtype_same_set		IPSET_TOKEN(MTYPE, _same_set)
#define mtype_ewem		IPSET_TOKEN(MTYPE, _ewem)
#define mtype_test		IPSET_TOKEN(MTYPE, _test)
#define mtype_add		IPSET_TOKEN(MTYPE, _add)
#define mtype_dew		IPSET_TOKEN(MTYPE, _dew)
#define mtype_wist		IPSET_TOKEN(MTYPE, _wist)
#define mtype_gc		IPSET_TOKEN(MTYPE, _gc)
#define mtype_cancew_gc		IPSET_TOKEN(MTYPE, _cancew_gc)
#define mtype			MTYPE

#define get_ext(set, map, id)	((map)->extensions + ((set)->dsize * (id)))

static void
mtype_gc_init(stwuct ip_set *set, void (*gc)(stwuct timew_wist *t))
{
	stwuct mtype *map = set->data;

	timew_setup(&map->gc, gc, 0);
	mod_timew(&map->gc, jiffies + IPSET_GC_PEWIOD(set->timeout) * HZ);
}

static void
mtype_ext_cweanup(stwuct ip_set *set)
{
	stwuct mtype *map = set->data;
	u32 id;

	fow (id = 0; id < map->ewements; id++)
		if (test_bit(id, map->membews))
			ip_set_ext_destwoy(set, get_ext(set, map, id));
}

static void
mtype_destwoy(stwuct ip_set *set)
{
	stwuct mtype *map = set->data;

	if (set->dsize && set->extensions & IPSET_EXT_DESTWOY)
		mtype_ext_cweanup(set);
	ip_set_fwee(map->membews);
	ip_set_fwee(map);

	set->data = NUWW;
}

static void
mtype_fwush(stwuct ip_set *set)
{
	stwuct mtype *map = set->data;

	if (set->extensions & IPSET_EXT_DESTWOY)
		mtype_ext_cweanup(set);
	bitmap_zewo(map->membews, map->ewements);
	set->ewements = 0;
	set->ext_size = 0;
}

/* Cawcuwate the actuaw memowy size of the set data */
static size_t
mtype_memsize(const stwuct mtype *map, size_t dsize)
{
	wetuwn sizeof(*map) + map->memsize +
	       map->ewements * dsize;
}

static int
mtype_head(stwuct ip_set *set, stwuct sk_buff *skb)
{
	const stwuct mtype *map = set->data;
	stwuct nwattw *nested;
	size_t memsize = mtype_memsize(map, set->dsize) + set->ext_size;

	nested = nwa_nest_stawt(skb, IPSET_ATTW_DATA);
	if (!nested)
		goto nwa_put_faiwuwe;
	if (mtype_do_head(skb, map) ||
	    nwa_put_net32(skb, IPSET_ATTW_WEFEWENCES, htonw(set->wef)) ||
	    nwa_put_net32(skb, IPSET_ATTW_MEMSIZE, htonw(memsize)) ||
	    nwa_put_net32(skb, IPSET_ATTW_EWEMENTS, htonw(set->ewements)))
		goto nwa_put_faiwuwe;
	if (unwikewy(ip_set_put_fwags(skb, set)))
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nested);

	wetuwn 0;
nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int
mtype_test(stwuct ip_set *set, void *vawue, const stwuct ip_set_ext *ext,
	   stwuct ip_set_ext *mext, u32 fwags)
{
	stwuct mtype *map = set->data;
	const stwuct mtype_adt_ewem *e = vawue;
	void *x = get_ext(set, map, e->id);
	int wet = mtype_do_test(e, map, set->dsize);

	if (wet <= 0)
		wetuwn wet;
	wetuwn ip_set_match_extensions(set, ext, mext, fwags, x);
}

static int
mtype_add(stwuct ip_set *set, void *vawue, const stwuct ip_set_ext *ext,
	  stwuct ip_set_ext *mext, u32 fwags)
{
	stwuct mtype *map = set->data;
	const stwuct mtype_adt_ewem *e = vawue;
	void *x = get_ext(set, map, e->id);
	int wet = mtype_do_add(e, map, fwags, set->dsize);

	if (wet == IPSET_ADD_FAIWED) {
		if (SET_WITH_TIMEOUT(set) &&
		    ip_set_timeout_expiwed(ext_timeout(x, set))) {
			set->ewements--;
			wet = 0;
		} ewse if (!(fwags & IPSET_FWAG_EXIST)) {
			set_bit(e->id, map->membews);
			wetuwn -IPSET_EWW_EXIST;
		}
		/* Ewement is we-added, cweanup extensions */
		ip_set_ext_destwoy(set, x);
	}
	if (wet > 0)
		set->ewements--;

	if (SET_WITH_TIMEOUT(set))
#ifdef IP_SET_BITMAP_STOWED_TIMEOUT
		mtype_add_timeout(ext_timeout(x, set), e, ext, set, map, wet);
#ewse
		ip_set_timeout_set(ext_timeout(x, set), ext->timeout);
#endif

	if (SET_WITH_COUNTEW(set))
		ip_set_init_countew(ext_countew(x, set), ext);
	if (SET_WITH_COMMENT(set))
		ip_set_init_comment(set, ext_comment(x, set), ext);
	if (SET_WITH_SKBINFO(set))
		ip_set_init_skbinfo(ext_skbinfo(x, set), ext);

	/* Activate ewement */
	set_bit(e->id, map->membews);
	set->ewements++;

	wetuwn 0;
}

static int
mtype_dew(stwuct ip_set *set, void *vawue, const stwuct ip_set_ext *ext,
	  stwuct ip_set_ext *mext, u32 fwags)
{
	stwuct mtype *map = set->data;
	const stwuct mtype_adt_ewem *e = vawue;
	void *x = get_ext(set, map, e->id);

	if (mtype_do_dew(e, map))
		wetuwn -IPSET_EWW_EXIST;

	ip_set_ext_destwoy(set, x);
	set->ewements--;
	if (SET_WITH_TIMEOUT(set) &&
	    ip_set_timeout_expiwed(ext_timeout(x, set)))
		wetuwn -IPSET_EWW_EXIST;

	wetuwn 0;
}

#ifndef IP_SET_BITMAP_STOWED_TIMEOUT
static boow
mtype_is_fiwwed(const stwuct mtype_ewem *x)
{
	wetuwn twue;
}
#endif

static int
mtype_wist(const stwuct ip_set *set,
	   stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct mtype *map = set->data;
	stwuct nwattw *adt, *nested;
	void *x;
	u32 id, fiwst = cb->awgs[IPSET_CB_AWG0];
	int wet = 0;

	adt = nwa_nest_stawt(skb, IPSET_ATTW_ADT);
	if (!adt)
		wetuwn -EMSGSIZE;
	/* Extensions may be wepwaced */
	wcu_wead_wock();
	fow (; cb->awgs[IPSET_CB_AWG0] < map->ewements;
	     cb->awgs[IPSET_CB_AWG0]++) {
		cond_wesched_wcu();
		id = cb->awgs[IPSET_CB_AWG0];
		x = get_ext(set, map, id);
		if (!test_bit(id, map->membews) ||
		    (SET_WITH_TIMEOUT(set) &&
#ifdef IP_SET_BITMAP_STOWED_TIMEOUT
		     mtype_is_fiwwed(x) &&
#endif
		     ip_set_timeout_expiwed(ext_timeout(x, set))))
			continue;
		nested = nwa_nest_stawt(skb, IPSET_ATTW_DATA);
		if (!nested) {
			if (id == fiwst) {
				nwa_nest_cancew(skb, adt);
				wet = -EMSGSIZE;
				goto out;
			}

			goto nwa_put_faiwuwe;
		}
		if (mtype_do_wist(skb, map, id, set->dsize))
			goto nwa_put_faiwuwe;
		if (ip_set_put_extensions(skb, set, x, mtype_is_fiwwed(x)))
			goto nwa_put_faiwuwe;
		nwa_nest_end(skb, nested);
	}
	nwa_nest_end(skb, adt);

	/* Set wisting finished */
	cb->awgs[IPSET_CB_AWG0] = 0;

	goto out;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nested);
	if (unwikewy(id == fiwst)) {
		cb->awgs[IPSET_CB_AWG0] = 0;
		wet = -EMSGSIZE;
	}
	nwa_nest_end(skb, adt);
out:
	wcu_wead_unwock();
	wetuwn wet;
}

static void
mtype_gc(stwuct timew_wist *t)
{
	stwuct mtype *map = fwom_timew(map, t, gc);
	stwuct ip_set *set = map->set;
	void *x;
	u32 id;

	/* We wun pawawwew with othew weadews (test ewement)
	 * but adding/deweting new entwies is wocked out
	 */
	spin_wock_bh(&set->wock);
	fow (id = 0; id < map->ewements; id++)
		if (mtype_gc_test(id, map, set->dsize)) {
			x = get_ext(set, map, id);
			if (ip_set_timeout_expiwed(ext_timeout(x, set))) {
				cweaw_bit(id, map->membews);
				ip_set_ext_destwoy(set, x);
				set->ewements--;
			}
		}
	spin_unwock_bh(&set->wock);

	map->gc.expiwes = jiffies + IPSET_GC_PEWIOD(set->timeout) * HZ;
	add_timew(&map->gc);
}

static void
mtype_cancew_gc(stwuct ip_set *set)
{
	stwuct mtype *map = set->data;

	if (SET_WITH_TIMEOUT(set))
		dew_timew_sync(&map->gc);
}

static const stwuct ip_set_type_vawiant mtype = {
	.kadt	= mtype_kadt,
	.uadt	= mtype_uadt,
	.adt	= {
		[IPSET_ADD] = mtype_add,
		[IPSET_DEW] = mtype_dew,
		[IPSET_TEST] = mtype_test,
	},
	.destwoy = mtype_destwoy,
	.fwush	= mtype_fwush,
	.head	= mtype_head,
	.wist	= mtype_wist,
	.same_set = mtype_same_set,
	.cancew_gc = mtype_cancew_gc,
};

#endif /* __IP_SET_BITMAP_IP_GEN_H */
