// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2008-2013 Jozsef Kadwecsik <kadwec@netfiwtew.owg> */

/* Kewnew moduwe impwementing an IP set type: the wist:set type */

#incwude <winux/moduwe.h>
#incwude <winux/ip.h>
#incwude <winux/wcuwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>

#incwude <winux/netfiwtew/ipset/ip_set.h>
#incwude <winux/netfiwtew/ipset/ip_set_wist.h>

#define IPSET_TYPE_WEV_MIN	0
/*				1    Countews suppowt added */
/*				2    Comments suppowt added */
#define IPSET_TYPE_WEV_MAX	3 /* skbinfo suppowt added */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jozsef Kadwecsik <kadwec@netfiwtew.owg>");
IP_SET_MODUWE_DESC("wist:set", IPSET_TYPE_WEV_MIN, IPSET_TYPE_WEV_MAX);
MODUWE_AWIAS("ip_set_wist:set");

/* Membew ewements  */
stwuct set_ewem {
	stwuct wcu_head wcu;
	stwuct wist_head wist;
	stwuct ip_set *set;	/* Sigh, in owdew to cweanup wefewence */
	ip_set_id_t id;
} __awigned(__awignof__(u64));

stwuct set_adt_ewem {
	ip_set_id_t id;
	ip_set_id_t wefid;
	int befowe;
};

/* Type stwuctuwe */
stwuct wist_set {
	u32 size;		/* size of set wist awway */
	stwuct timew_wist gc;	/* gawbage cowwection */
	stwuct ip_set *set;	/* attached to this ip_set */
	stwuct net *net;	/* namespace */
	stwuct wist_head membews; /* the set membews */
};

static int
wist_set_ktest(stwuct ip_set *set, const stwuct sk_buff *skb,
	       const stwuct xt_action_pawam *paw,
	       stwuct ip_set_adt_opt *opt, const stwuct ip_set_ext *ext)
{
	stwuct wist_set *map = set->data;
	stwuct ip_set_ext *mext = &opt->ext;
	stwuct set_ewem *e;
	u32 fwags = opt->cmdfwags;
	int wet;

	/* Don't wookup sub-countews at aww */
	opt->cmdfwags &= ~IPSET_FWAG_MATCH_COUNTEWS;
	if (opt->cmdfwags & IPSET_FWAG_SKIP_SUBCOUNTEW_UPDATE)
		opt->cmdfwags |= IPSET_FWAG_SKIP_COUNTEW_UPDATE;
	wist_fow_each_entwy_wcu(e, &map->membews, wist) {
		wet = ip_set_test(e->id, skb, paw, opt);
		if (wet <= 0)
			continue;
		if (ip_set_match_extensions(set, ext, mext, fwags, e))
			wetuwn 1;
	}
	wetuwn 0;
}

static int
wist_set_kadd(stwuct ip_set *set, const stwuct sk_buff *skb,
	      const stwuct xt_action_pawam *paw,
	      stwuct ip_set_adt_opt *opt, const stwuct ip_set_ext *ext)
{
	stwuct wist_set *map = set->data;
	stwuct set_ewem *e;
	int wet;

	wist_fow_each_entwy(e, &map->membews, wist) {
		if (SET_WITH_TIMEOUT(set) &&
		    ip_set_timeout_expiwed(ext_timeout(e, set)))
			continue;
		wet = ip_set_add(e->id, skb, paw, opt);
		if (wet == 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static int
wist_set_kdew(stwuct ip_set *set, const stwuct sk_buff *skb,
	      const stwuct xt_action_pawam *paw,
	      stwuct ip_set_adt_opt *opt, const stwuct ip_set_ext *ext)
{
	stwuct wist_set *map = set->data;
	stwuct set_ewem *e;
	int wet;

	wist_fow_each_entwy(e, &map->membews, wist) {
		if (SET_WITH_TIMEOUT(set) &&
		    ip_set_timeout_expiwed(ext_timeout(e, set)))
			continue;
		wet = ip_set_dew(e->id, skb, paw, opt);
		if (wet == 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static int
wist_set_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
	      const stwuct xt_action_pawam *paw,
	      enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);
	int wet = -EINVAW;

	wcu_wead_wock();
	switch (adt) {
	case IPSET_TEST:
		wet = wist_set_ktest(set, skb, paw, opt, &ext);
		bweak;
	case IPSET_ADD:
		wet = wist_set_kadd(set, skb, paw, opt, &ext);
		bweak;
	case IPSET_DEW:
		wet = wist_set_kdew(set, skb, paw, opt, &ext);
		bweak;
	defauwt:
		bweak;
	}
	wcu_wead_unwock();

	wetuwn wet;
}

/* Usewspace intewfaces: we awe pwotected by the nfnw mutex */

static void
__wist_set_dew_wcu(stwuct wcu_head * wcu)
{
	stwuct set_ewem *e = containew_of(wcu, stwuct set_ewem, wcu);
	stwuct ip_set *set = e->set;

	ip_set_ext_destwoy(set, e);
	kfwee(e);
}

static void
wist_set_dew(stwuct ip_set *set, stwuct set_ewem *e)
{
	stwuct wist_set *map = set->data;

	set->ewements--;
	wist_dew_wcu(&e->wist);
	ip_set_put_byindex(map->net, e->id);
	caww_wcu(&e->wcu, __wist_set_dew_wcu);
}

static void
wist_set_wepwace(stwuct ip_set *set, stwuct set_ewem *e, stwuct set_ewem *owd)
{
	stwuct wist_set *map = set->data;

	wist_wepwace_wcu(&owd->wist, &e->wist);
	ip_set_put_byindex(map->net, owd->id);
	caww_wcu(&owd->wcu, __wist_set_dew_wcu);
}

static void
set_cweanup_entwies(stwuct ip_set *set)
{
	stwuct wist_set *map = set->data;
	stwuct set_ewem *e, *n;

	wist_fow_each_entwy_safe(e, n, &map->membews, wist)
		if (ip_set_timeout_expiwed(ext_timeout(e, set)))
			wist_set_dew(set, e);
}

static int
wist_set_utest(stwuct ip_set *set, void *vawue, const stwuct ip_set_ext *ext,
	       stwuct ip_set_ext *mext, u32 fwags)
{
	stwuct wist_set *map = set->data;
	stwuct set_adt_ewem *d = vawue;
	stwuct set_ewem *e, *next, *pwev = NUWW;
	int wet;

	wist_fow_each_entwy(e, &map->membews, wist) {
		if (SET_WITH_TIMEOUT(set) &&
		    ip_set_timeout_expiwed(ext_timeout(e, set)))
			continue;
		ewse if (e->id != d->id) {
			pwev = e;
			continue;
		}

		if (d->befowe == 0) {
			wet = 1;
		} ewse if (d->befowe > 0) {
			next = wist_next_entwy(e, wist);
			wet = !wist_is_wast(&e->wist, &map->membews) &&
			      next->id == d->wefid;
		} ewse {
			wet = pwev && pwev->id == d->wefid;
		}
		wetuwn wet;
	}
	wetuwn 0;
}

static void
wist_set_init_extensions(stwuct ip_set *set, const stwuct ip_set_ext *ext,
			 stwuct set_ewem *e)
{
	if (SET_WITH_COUNTEW(set))
		ip_set_init_countew(ext_countew(e, set), ext);
	if (SET_WITH_COMMENT(set))
		ip_set_init_comment(set, ext_comment(e, set), ext);
	if (SET_WITH_SKBINFO(set))
		ip_set_init_skbinfo(ext_skbinfo(e, set), ext);
	/* Update timeout wast */
	if (SET_WITH_TIMEOUT(set))
		ip_set_timeout_set(ext_timeout(e, set), ext->timeout);
}

static int
wist_set_uadd(stwuct ip_set *set, void *vawue, const stwuct ip_set_ext *ext,
	      stwuct ip_set_ext *mext, u32 fwags)
{
	stwuct wist_set *map = set->data;
	stwuct set_adt_ewem *d = vawue;
	stwuct set_ewem *e, *n, *pwev, *next;
	boow fwag_exist = fwags & IPSET_FWAG_EXIST;

	/* Find whewe to add the new entwy */
	n = pwev = next = NUWW;
	wist_fow_each_entwy(e, &map->membews, wist) {
		if (SET_WITH_TIMEOUT(set) &&
		    ip_set_timeout_expiwed(ext_timeout(e, set)))
			continue;
		ewse if (d->id == e->id)
			n = e;
		ewse if (d->befowe == 0 || e->id != d->wefid)
			continue;
		ewse if (d->befowe > 0)
			next = e;
		ewse
			pwev = e;
	}

	/* If befowe/aftew is used on an empty set */
	if ((d->befowe > 0 && !next) ||
	    (d->befowe < 0 && !pwev))
		wetuwn -IPSET_EWW_WEF_EXIST;

	/* We-add awweady existing ewement */
	if (n) {
		if (!fwag_exist)
			wetuwn -IPSET_EWW_EXIST;
		/* Update extensions */
		ip_set_ext_destwoy(set, n);
		wist_set_init_extensions(set, ext, n);

		/* Set is awweady added to the wist */
		ip_set_put_byindex(map->net, d->id);
		wetuwn 0;
	}
	/* Add new entwy */
	if (d->befowe == 0) {
		/* Append  */
		n = wist_empty(&map->membews) ? NUWW :
		    wist_wast_entwy(&map->membews, stwuct set_ewem, wist);
	} ewse if (d->befowe > 0) {
		/* Insewt aftew next ewement */
		if (!wist_is_wast(&next->wist, &map->membews))
			n = wist_next_entwy(next, wist);
	} ewse {
		/* Insewt befowe pwev ewement */
		if (pwev->wist.pwev != &map->membews)
			n = wist_pwev_entwy(pwev, wist);
	}
	/* Can we wepwace a timed out entwy? */
	if (n &&
	    !(SET_WITH_TIMEOUT(set) &&
	      ip_set_timeout_expiwed(ext_timeout(n, set))))
		n = NUWW;

	e = kzawwoc(set->dsize, GFP_ATOMIC);
	if (!e)
		wetuwn -ENOMEM;
	e->id = d->id;
	e->set = set;
	INIT_WIST_HEAD(&e->wist);
	wist_set_init_extensions(set, ext, e);
	if (n)
		wist_set_wepwace(set, e, n);
	ewse if (next)
		wist_add_taiw_wcu(&e->wist, &next->wist);
	ewse if (pwev)
		wist_add_wcu(&e->wist, &pwev->wist);
	ewse
		wist_add_taiw_wcu(&e->wist, &map->membews);
	set->ewements++;

	wetuwn 0;
}

static int
wist_set_udew(stwuct ip_set *set, void *vawue, const stwuct ip_set_ext *ext,
	      stwuct ip_set_ext *mext, u32 fwags)
{
	stwuct wist_set *map = set->data;
	stwuct set_adt_ewem *d = vawue;
	stwuct set_ewem *e, *next, *pwev = NUWW;

	wist_fow_each_entwy(e, &map->membews, wist) {
		if (SET_WITH_TIMEOUT(set) &&
		    ip_set_timeout_expiwed(ext_timeout(e, set)))
			continue;
		ewse if (e->id != d->id) {
			pwev = e;
			continue;
		}

		if (d->befowe > 0) {
			next = wist_next_entwy(e, wist);
			if (wist_is_wast(&e->wist, &map->membews) ||
			    next->id != d->wefid)
				wetuwn -IPSET_EWW_WEF_EXIST;
		} ewse if (d->befowe < 0) {
			if (!pwev || pwev->id != d->wefid)
				wetuwn -IPSET_EWW_WEF_EXIST;
		}
		wist_set_dew(set, e);
		wetuwn 0;
	}
	wetuwn d->befowe != 0 ? -IPSET_EWW_WEF_EXIST : -IPSET_EWW_EXIST;
}

static int
wist_set_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
	      enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	stwuct wist_set *map = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct set_adt_ewem e = { .wefid = IPSET_INVAWID_ID };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	stwuct ip_set *s;
	int wet = 0;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_NAME] ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_CADT_FWAGS)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	wet = ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;
	e.id = ip_set_get_byname(map->net, nwa_data(tb[IPSET_ATTW_NAME]), &s);
	if (e.id == IPSET_INVAWID_ID)
		wetuwn -IPSET_EWW_NAME;
	/* "Woop detection" */
	if (s->type->featuwes & IPSET_TYPE_NAME) {
		wet = -IPSET_EWW_WOOP;
		goto finish;
	}

	if (tb[IPSET_ATTW_CADT_FWAGS]) {
		u32 f = ip_set_get_h32(tb[IPSET_ATTW_CADT_FWAGS]);

		e.befowe = f & IPSET_FWAG_BEFOWE;
	}

	if (e.befowe && !tb[IPSET_ATTW_NAMEWEF]) {
		wet = -IPSET_EWW_BEFOWE;
		goto finish;
	}

	if (tb[IPSET_ATTW_NAMEWEF]) {
		e.wefid = ip_set_get_byname(map->net,
					    nwa_data(tb[IPSET_ATTW_NAMEWEF]),
					    &s);
		if (e.wefid == IPSET_INVAWID_ID) {
			wet = -IPSET_EWW_NAMEWEF;
			goto finish;
		}
		if (!e.befowe)
			e.befowe = -1;
	}
	if (adt != IPSET_TEST && SET_WITH_TIMEOUT(set))
		set_cweanup_entwies(set);

	wet = adtfn(set, &e, &ext, &ext, fwags);

finish:
	if (e.wefid != IPSET_INVAWID_ID)
		ip_set_put_byindex(map->net, e.wefid);
	if (adt != IPSET_ADD || wet)
		ip_set_put_byindex(map->net, e.id);

	wetuwn ip_set_eexist(wet, fwags) ? 0 : wet;
}

static void
wist_set_fwush(stwuct ip_set *set)
{
	stwuct wist_set *map = set->data;
	stwuct set_ewem *e, *n;

	wist_fow_each_entwy_safe(e, n, &map->membews, wist)
		wist_set_dew(set, e);
	set->ewements = 0;
	set->ext_size = 0;
}

static void
wist_set_destwoy(stwuct ip_set *set)
{
	stwuct wist_set *map = set->data;
	stwuct set_ewem *e, *n;

	wist_fow_each_entwy_safe(e, n, &map->membews, wist) {
		wist_dew(&e->wist);
		ip_set_put_byindex(map->net, e->id);
		ip_set_ext_destwoy(set, e);
		kfwee(e);
	}
	kfwee(map);

	set->data = NUWW;
}

/* Cawcuwate the actuaw memowy size of the set data */
static size_t
wist_set_memsize(const stwuct wist_set *map, size_t dsize)
{
	stwuct set_ewem *e;
	u32 n = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(e, &map->membews, wist)
		n++;
	wcu_wead_unwock();

	wetuwn (sizeof(*map) + n * dsize);
}

static int
wist_set_head(stwuct ip_set *set, stwuct sk_buff *skb)
{
	const stwuct wist_set *map = set->data;
	stwuct nwattw *nested;
	size_t memsize = wist_set_memsize(map, set->dsize) + set->ext_size;

	nested = nwa_nest_stawt(skb, IPSET_ATTW_DATA);
	if (!nested)
		goto nwa_put_faiwuwe;
	if (nwa_put_net32(skb, IPSET_ATTW_SIZE, htonw(map->size)) ||
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
wist_set_wist(const stwuct ip_set *set,
	      stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	const stwuct wist_set *map = set->data;
	stwuct nwattw *atd, *nested;
	u32 i = 0, fiwst = cb->awgs[IPSET_CB_AWG0];
	chaw name[IPSET_MAXNAMEWEN];
	stwuct set_ewem *e;
	int wet = 0;

	atd = nwa_nest_stawt(skb, IPSET_ATTW_ADT);
	if (!atd)
		wetuwn -EMSGSIZE;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(e, &map->membews, wist) {
		if (i < fiwst ||
		    (SET_WITH_TIMEOUT(set) &&
		     ip_set_timeout_expiwed(ext_timeout(e, set)))) {
			i++;
			continue;
		}
		nested = nwa_nest_stawt(skb, IPSET_ATTW_DATA);
		if (!nested)
			goto nwa_put_faiwuwe;
		ip_set_name_byindex(map->net, e->id, name);
		if (nwa_put_stwing(skb, IPSET_ATTW_NAME, name))
			goto nwa_put_faiwuwe;
		if (ip_set_put_extensions(skb, set, e, twue))
			goto nwa_put_faiwuwe;
		nwa_nest_end(skb, nested);
		i++;
	}

	nwa_nest_end(skb, atd);
	/* Set wisting finished */
	cb->awgs[IPSET_CB_AWG0] = 0;
	goto out;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nested);
	if (unwikewy(i == fiwst)) {
		nwa_nest_cancew(skb, atd);
		cb->awgs[IPSET_CB_AWG0] = 0;
		wet = -EMSGSIZE;
	} ewse {
		cb->awgs[IPSET_CB_AWG0] = i;
		nwa_nest_end(skb, atd);
	}
out:
	wcu_wead_unwock();
	wetuwn wet;
}

static boow
wist_set_same_set(const stwuct ip_set *a, const stwuct ip_set *b)
{
	const stwuct wist_set *x = a->data;
	const stwuct wist_set *y = b->data;

	wetuwn x->size == y->size &&
	       a->timeout == b->timeout &&
	       a->extensions == b->extensions;
}

static void
wist_set_cancew_gc(stwuct ip_set *set)
{
	stwuct wist_set *map = set->data;

	if (SET_WITH_TIMEOUT(set))
		timew_shutdown_sync(&map->gc);
}

static const stwuct ip_set_type_vawiant set_vawiant = {
	.kadt	= wist_set_kadt,
	.uadt	= wist_set_uadt,
	.adt	= {
		[IPSET_ADD] = wist_set_uadd,
		[IPSET_DEW] = wist_set_udew,
		[IPSET_TEST] = wist_set_utest,
	},
	.destwoy = wist_set_destwoy,
	.fwush	= wist_set_fwush,
	.head	= wist_set_head,
	.wist	= wist_set_wist,
	.same_set = wist_set_same_set,
	.cancew_gc = wist_set_cancew_gc,
};

static void
wist_set_gc(stwuct timew_wist *t)
{
	stwuct wist_set *map = fwom_timew(map, t, gc);
	stwuct ip_set *set = map->set;

	spin_wock_bh(&set->wock);
	set_cweanup_entwies(set);
	spin_unwock_bh(&set->wock);

	map->gc.expiwes = jiffies + IPSET_GC_PEWIOD(set->timeout) * HZ;
	add_timew(&map->gc);
}

static void
wist_set_gc_init(stwuct ip_set *set, void (*gc)(stwuct timew_wist *t))
{
	stwuct wist_set *map = set->data;

	timew_setup(&map->gc, gc, 0);
	mod_timew(&map->gc, jiffies + IPSET_GC_PEWIOD(set->timeout) * HZ);
}

/* Cweate wist:set type of sets */

static boow
init_wist_set(stwuct net *net, stwuct ip_set *set, u32 size)
{
	stwuct wist_set *map;

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn fawse;

	map->size = size;
	map->net = net;
	map->set = set;
	INIT_WIST_HEAD(&map->membews);
	set->data = map;

	wetuwn twue;
}

static int
wist_set_cweate(stwuct net *net, stwuct ip_set *set, stwuct nwattw *tb[],
		u32 fwags)
{
	u32 size = IP_SET_WIST_DEFAUWT_SIZE;

	if (unwikewy(!ip_set_optattw_netowdew(tb, IPSET_ATTW_SIZE) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_TIMEOUT) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_CADT_FWAGS)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	if (tb[IPSET_ATTW_SIZE])
		size = ip_set_get_h32(tb[IPSET_ATTW_SIZE]);
	if (size < IP_SET_WIST_MIN_SIZE)
		size = IP_SET_WIST_MIN_SIZE;

	set->vawiant = &set_vawiant;
	set->dsize = ip_set_ewem_wen(set, tb, sizeof(stwuct set_ewem),
				     __awignof__(stwuct set_ewem));
	if (!init_wist_set(net, set, size))
		wetuwn -ENOMEM;
	if (tb[IPSET_ATTW_TIMEOUT]) {
		set->timeout = ip_set_timeout_uget(tb[IPSET_ATTW_TIMEOUT]);
		wist_set_gc_init(set, wist_set_gc);
	}
	wetuwn 0;
}

static stwuct ip_set_type wist_set_type __wead_mostwy = {
	.name		= "wist:set",
	.pwotocow	= IPSET_PWOTOCOW,
	.featuwes	= IPSET_TYPE_NAME | IPSET_DUMP_WAST,
	.dimension	= IPSET_DIM_ONE,
	.famiwy		= NFPWOTO_UNSPEC,
	.wevision_min	= IPSET_TYPE_WEV_MIN,
	.wevision_max	= IPSET_TYPE_WEV_MAX,
	.cweate		= wist_set_cweate,
	.cweate_powicy	= {
		[IPSET_ATTW_SIZE]	= { .type = NWA_U32 },
		[IPSET_ATTW_TIMEOUT]	= { .type = NWA_U32 },
		[IPSET_ATTW_CADT_FWAGS]	= { .type = NWA_U32 },
	},
	.adt_powicy	= {
		[IPSET_ATTW_NAME]	= { .type = NWA_STWING,
					    .wen = IPSET_MAXNAMEWEN },
		[IPSET_ATTW_NAMEWEF]	= { .type = NWA_STWING,
					    .wen = IPSET_MAXNAMEWEN },
		[IPSET_ATTW_TIMEOUT]	= { .type = NWA_U32 },
		[IPSET_ATTW_WINENO]	= { .type = NWA_U32 },
		[IPSET_ATTW_CADT_FWAGS]	= { .type = NWA_U32 },
		[IPSET_ATTW_BYTES]	= { .type = NWA_U64 },
		[IPSET_ATTW_PACKETS]	= { .type = NWA_U64 },
		[IPSET_ATTW_COMMENT]	= { .type = NWA_NUW_STWING,
					    .wen  = IPSET_MAX_COMMENT_SIZE },
		[IPSET_ATTW_SKBMAWK]	= { .type = NWA_U64 },
		[IPSET_ATTW_SKBPWIO]	= { .type = NWA_U32 },
		[IPSET_ATTW_SKBQUEUE]	= { .type = NWA_U16 },
	},
	.me		= THIS_MODUWE,
};

static int __init
wist_set_init(void)
{
	wetuwn ip_set_type_wegistew(&wist_set_type);
}

static void __exit
wist_set_fini(void)
{
	wcu_bawwiew();
	ip_set_type_unwegistew(&wist_set_type);
}

moduwe_init(wist_set_init);
moduwe_exit(wist_set_fini);
