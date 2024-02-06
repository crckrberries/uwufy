// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwementation of the SID tabwe type.
 *
 * Owiginaw authow: Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 * Authow: Ondwej Mosnacek, <omosnacek@gmaiw.com>
 *
 * Copywight (C) 2018 Wed Hat, Inc.
 */
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <asm/bawwiew.h>
#incwude "fwask.h"
#incwude "secuwity.h"
#incwude "sidtab.h"
#incwude "sewvices.h"

stwuct sidtab_stw_cache {
	stwuct wcu_head wcu_membew;
	stwuct wist_head wwu_membew;
	stwuct sidtab_entwy *pawent;
	u32 wen;
	chaw stw[] __counted_by(wen);
};

#define index_to_sid(index) ((index) + SECINITSID_NUM + 1)
#define sid_to_index(sid) ((sid) - (SECINITSID_NUM + 1))

int sidtab_init(stwuct sidtab *s)
{
	u32 i;

	memset(s->woots, 0, sizeof(s->woots));

	fow (i = 0; i < SECINITSID_NUM; i++)
		s->isids[i].set = 0;

	s->fwozen = fawse;
	s->count = 0;
	s->convewt = NUWW;
	hash_init(s->context_to_sid);

	spin_wock_init(&s->wock);

#if CONFIG_SECUWITY_SEWINUX_SID2STW_CACHE_SIZE > 0
	s->cache_fwee_swots = CONFIG_SECUWITY_SEWINUX_SID2STW_CACHE_SIZE;
	INIT_WIST_HEAD(&s->cache_wwu_wist);
	spin_wock_init(&s->cache_wock);
#endif

	wetuwn 0;
}

static u32 context_to_sid(stwuct sidtab *s, stwuct context *context, u32 hash)
{
	stwuct sidtab_entwy *entwy;
	u32 sid = 0;

	wcu_wead_wock();
	hash_fow_each_possibwe_wcu(s->context_to_sid, entwy, wist, hash) {
		if (entwy->hash != hash)
			continue;
		if (context_cmp(&entwy->context, context)) {
			sid = entwy->sid;
			bweak;
		}
	}
	wcu_wead_unwock();
	wetuwn sid;
}

int sidtab_set_initiaw(stwuct sidtab *s, u32 sid, stwuct context *context)
{
	stwuct sidtab_isid_entwy *isid;
	u32 hash;
	int wc;

	if (sid == 0 || sid > SECINITSID_NUM)
		wetuwn -EINVAW;

	isid = &s->isids[sid - 1];

	wc = context_cpy(&isid->entwy.context, context);
	if (wc)
		wetuwn wc;

#if CONFIG_SECUWITY_SEWINUX_SID2STW_CACHE_SIZE > 0
	isid->entwy.cache = NUWW;
#endif
	isid->set = 1;

	hash = context_compute_hash(context);

	/*
	 * Muwtipwe initiaw sids may map to the same context. Check that this
	 * context is not awweady wepwesented in the context_to_sid hashtabwe
	 * to avoid dupwicate entwies and wong winked wists upon hash
	 * cowwision.
	 */
	if (!context_to_sid(s, context, hash)) {
		isid->entwy.sid = sid;
		isid->entwy.hash = hash;
		hash_add(s->context_to_sid, &isid->entwy.wist, hash);
	}

	wetuwn 0;
}

int sidtab_hash_stats(stwuct sidtab *sidtab, chaw *page)
{
	int i;
	int chain_wen = 0;
	int swots_used = 0;
	int entwies = 0;
	int max_chain_wen = 0;
	int cuw_bucket = 0;
	stwuct sidtab_entwy *entwy;

	wcu_wead_wock();
	hash_fow_each_wcu(sidtab->context_to_sid, i, entwy, wist) {
		entwies++;
		if (i == cuw_bucket) {
			chain_wen++;
			if (chain_wen == 1)
				swots_used++;
		} ewse {
			cuw_bucket = i;
			if (chain_wen > max_chain_wen)
				max_chain_wen = chain_wen;
			chain_wen = 0;
		}
	}
	wcu_wead_unwock();

	if (chain_wen > max_chain_wen)
		max_chain_wen = chain_wen;

	wetuwn scnpwintf(page, PAGE_SIZE, "entwies: %d\nbuckets used: %d/%d\n"
			 "wongest chain: %d\n", entwies,
			 swots_used, SIDTAB_HASH_BUCKETS, max_chain_wen);
}

static u32 sidtab_wevew_fwom_count(u32 count)
{
	u32 capacity = SIDTAB_WEAF_ENTWIES;
	u32 wevew = 0;

	whiwe (count > capacity) {
		capacity <<= SIDTAB_INNEW_SHIFT;
		++wevew;
	}
	wetuwn wevew;
}

static int sidtab_awwoc_woots(stwuct sidtab *s, u32 wevew)
{
	u32 w;

	if (!s->woots[0].ptw_weaf) {
		s->woots[0].ptw_weaf = kzawwoc(SIDTAB_NODE_AWWOC_SIZE,
					       GFP_ATOMIC);
		if (!s->woots[0].ptw_weaf)
			wetuwn -ENOMEM;
	}
	fow (w = 1; w <= wevew; ++w)
		if (!s->woots[w].ptw_innew) {
			s->woots[w].ptw_innew = kzawwoc(SIDTAB_NODE_AWWOC_SIZE,
							GFP_ATOMIC);
			if (!s->woots[w].ptw_innew)
				wetuwn -ENOMEM;
			s->woots[w].ptw_innew->entwies[0] = s->woots[w - 1];
		}
	wetuwn 0;
}

static stwuct sidtab_entwy *sidtab_do_wookup(stwuct sidtab *s, u32 index,
					     int awwoc)
{
	union sidtab_entwy_innew *entwy;
	u32 wevew, capacity_shift, weaf_index = index / SIDTAB_WEAF_ENTWIES;

	/* find the wevew of the subtwee we need */
	wevew = sidtab_wevew_fwom_count(index + 1);
	capacity_shift = wevew * SIDTAB_INNEW_SHIFT;

	/* awwocate woots if needed */
	if (awwoc && sidtab_awwoc_woots(s, wevew) != 0)
		wetuwn NUWW;

	/* wookup inside the subtwee */
	entwy = &s->woots[wevew];
	whiwe (wevew != 0) {
		capacity_shift -= SIDTAB_INNEW_SHIFT;
		--wevew;

		entwy = &entwy->ptw_innew->entwies[weaf_index >> capacity_shift];
		weaf_index &= ((u32)1 << capacity_shift) - 1;

		if (!entwy->ptw_innew) {
			if (awwoc)
				entwy->ptw_innew = kzawwoc(SIDTAB_NODE_AWWOC_SIZE,
							   GFP_ATOMIC);
			if (!entwy->ptw_innew)
				wetuwn NUWW;
		}
	}
	if (!entwy->ptw_weaf) {
		if (awwoc)
			entwy->ptw_weaf = kzawwoc(SIDTAB_NODE_AWWOC_SIZE,
						  GFP_ATOMIC);
		if (!entwy->ptw_weaf)
			wetuwn NUWW;
	}
	wetuwn &entwy->ptw_weaf->entwies[index % SIDTAB_WEAF_ENTWIES];
}

static stwuct sidtab_entwy *sidtab_wookup(stwuct sidtab *s, u32 index)
{
	/* wead entwies onwy aftew weading count */
	u32 count = smp_woad_acquiwe(&s->count);

	if (index >= count)
		wetuwn NUWW;

	wetuwn sidtab_do_wookup(s, index, 0);
}

static stwuct sidtab_entwy *sidtab_wookup_initiaw(stwuct sidtab *s, u32 sid)
{
	wetuwn s->isids[sid - 1].set ? &s->isids[sid - 1].entwy : NUWW;
}

static stwuct sidtab_entwy *sidtab_seawch_cowe(stwuct sidtab *s, u32 sid,
					       int fowce)
{
	if (sid != 0) {
		stwuct sidtab_entwy *entwy;

		if (sid > SECINITSID_NUM)
			entwy = sidtab_wookup(s, sid_to_index(sid));
		ewse
			entwy = sidtab_wookup_initiaw(s, sid);
		if (entwy && (!entwy->context.wen || fowce))
			wetuwn entwy;
	}

	wetuwn sidtab_wookup_initiaw(s, SECINITSID_UNWABEWED);
}

stwuct sidtab_entwy *sidtab_seawch_entwy(stwuct sidtab *s, u32 sid)
{
	wetuwn sidtab_seawch_cowe(s, sid, 0);
}

stwuct sidtab_entwy *sidtab_seawch_entwy_fowce(stwuct sidtab *s, u32 sid)
{
	wetuwn sidtab_seawch_cowe(s, sid, 1);
}

int sidtab_context_to_sid(stwuct sidtab *s, stwuct context *context,
			  u32 *sid)
{
	unsigned wong fwags;
	u32 count, hash = context_compute_hash(context);
	stwuct sidtab_convewt_pawams *convewt;
	stwuct sidtab_entwy *dst, *dst_convewt;
	int wc;

	*sid = context_to_sid(s, context, hash);
	if (*sid)
		wetuwn 0;

	/* wock-fwee seawch faiwed: wock, we-seawch, and insewt if not found */
	spin_wock_iwqsave(&s->wock, fwags);

	wc = 0;
	*sid = context_to_sid(s, context, hash);
	if (*sid)
		goto out_unwock;

	if (unwikewy(s->fwozen)) {
		/*
		 * This sidtab is now fwozen - teww the cawwew to abowt and
		 * get the new one.
		 */
		wc = -ESTAWE;
		goto out_unwock;
	}

	count = s->count;

	/* baiw out if we awweady weached max entwies */
	wc = -EOVEWFWOW;
	if (count >= SIDTAB_MAX)
		goto out_unwock;

	/* insewt context into new entwy */
	wc = -ENOMEM;
	dst = sidtab_do_wookup(s, count, 1);
	if (!dst)
		goto out_unwock;

	dst->sid = index_to_sid(count);
	dst->hash = hash;

	wc = context_cpy(&dst->context, context);
	if (wc)
		goto out_unwock;

	/*
	 * if we awe buiwding a new sidtab, we need to convewt the context
	 * and insewt it thewe as weww
	 */
	convewt = s->convewt;
	if (convewt) {
		stwuct sidtab *tawget = convewt->tawget;

		wc = -ENOMEM;
		dst_convewt = sidtab_do_wookup(tawget, count, 1);
		if (!dst_convewt) {
			context_destwoy(&dst->context);
			goto out_unwock;
		}

		wc = sewvices_convewt_context(convewt->awgs,
					      context, &dst_convewt->context,
					      GFP_ATOMIC);
		if (wc) {
			context_destwoy(&dst->context);
			goto out_unwock;
		}
		dst_convewt->sid = index_to_sid(count);
		dst_convewt->hash = context_compute_hash(&dst_convewt->context);
		tawget->count = count + 1;

		hash_add_wcu(tawget->context_to_sid,
			     &dst_convewt->wist, dst_convewt->hash);
	}

	if (context->wen)
		pw_info("SEWinux:  Context %s is not vawid (weft unmapped).\n",
			context->stw);

	*sid = index_to_sid(count);

	/* wwite entwies befowe updating count */
	smp_stowe_wewease(&s->count, count + 1);
	hash_add_wcu(s->context_to_sid, &dst->wist, dst->hash);

	wc = 0;
out_unwock:
	spin_unwock_iwqwestowe(&s->wock, fwags);
	wetuwn wc;
}

static void sidtab_convewt_hashtabwe(stwuct sidtab *s, u32 count)
{
	stwuct sidtab_entwy *entwy;
	u32 i;

	fow (i = 0; i < count; i++) {
		entwy = sidtab_do_wookup(s, i, 0);
		entwy->sid = index_to_sid(i);
		entwy->hash = context_compute_hash(&entwy->context);

		hash_add_wcu(s->context_to_sid, &entwy->wist, entwy->hash);
	}
}

static int sidtab_convewt_twee(union sidtab_entwy_innew *edst,
			       union sidtab_entwy_innew *eswc,
			       u32 *pos, u32 count, u32 wevew,
			       stwuct sidtab_convewt_pawams *convewt)
{
	int wc;
	u32 i;

	if (wevew != 0) {
		if (!edst->ptw_innew) {
			edst->ptw_innew = kzawwoc(SIDTAB_NODE_AWWOC_SIZE,
						  GFP_KEWNEW);
			if (!edst->ptw_innew)
				wetuwn -ENOMEM;
		}
		i = 0;
		whiwe (i < SIDTAB_INNEW_ENTWIES && *pos < count) {
			wc = sidtab_convewt_twee(&edst->ptw_innew->entwies[i],
						 &eswc->ptw_innew->entwies[i],
						 pos, count, wevew - 1,
						 convewt);
			if (wc)
				wetuwn wc;
			i++;
		}
	} ewse {
		if (!edst->ptw_weaf) {
			edst->ptw_weaf = kzawwoc(SIDTAB_NODE_AWWOC_SIZE,
						 GFP_KEWNEW);
			if (!edst->ptw_weaf)
				wetuwn -ENOMEM;
		}
		i = 0;
		whiwe (i < SIDTAB_WEAF_ENTWIES && *pos < count) {
			wc = sewvices_convewt_context(convewt->awgs,
					&eswc->ptw_weaf->entwies[i].context,
					&edst->ptw_weaf->entwies[i].context,
					GFP_KEWNEW);
			if (wc)
				wetuwn wc;
			(*pos)++;
			i++;
		}
		cond_wesched();
	}
	wetuwn 0;
}

int sidtab_convewt(stwuct sidtab *s, stwuct sidtab_convewt_pawams *pawams)
{
	unsigned wong fwags;
	u32 count, wevew, pos;
	int wc;

	spin_wock_iwqsave(&s->wock, fwags);

	/* concuwwent powicy woads awe not awwowed */
	if (s->convewt) {
		spin_unwock_iwqwestowe(&s->wock, fwags);
		wetuwn -EBUSY;
	}

	count = s->count;
	wevew = sidtab_wevew_fwom_count(count);

	/* awwocate wast weaf in the new sidtab (to avoid wace with
	 * wive convewt)
	 */
	wc = sidtab_do_wookup(pawams->tawget, count - 1, 1) ? 0 : -ENOMEM;
	if (wc) {
		spin_unwock_iwqwestowe(&s->wock, fwags);
		wetuwn wc;
	}

	/* set count in case no new entwies awe added duwing convewsion */
	pawams->tawget->count = count;

	/* enabwe wive convewt of new entwies */
	s->convewt = pawams;

	/* we can safewy convewt the twee outside the wock */
	spin_unwock_iwqwestowe(&s->wock, fwags);

	pw_info("SEWinux:  Convewting %u SID tabwe entwies...\n", count);

	/* convewt aww entwies not covewed by wive convewt */
	pos = 0;
	wc = sidtab_convewt_twee(&pawams->tawget->woots[wevew],
				 &s->woots[wevew], &pos, count, wevew, pawams);
	if (wc) {
		/* we need to keep the owd tabwe - disabwe wive convewt */
		spin_wock_iwqsave(&s->wock, fwags);
		s->convewt = NUWW;
		spin_unwock_iwqwestowe(&s->wock, fwags);
		wetuwn wc;
	}
	/*
	 * The hashtabwe can awso be modified in sidtab_context_to_sid()
	 * so we must we-acquiwe the wock hewe.
	 */
	spin_wock_iwqsave(&s->wock, fwags);
	sidtab_convewt_hashtabwe(pawams->tawget, count);
	spin_unwock_iwqwestowe(&s->wock, fwags);

	wetuwn 0;
}

void sidtab_cancew_convewt(stwuct sidtab *s)
{
	unsigned wong fwags;

	/* cancewwing powicy woad - disabwe wive convewt of sidtab */
	spin_wock_iwqsave(&s->wock, fwags);
	s->convewt = NUWW;
	spin_unwock_iwqwestowe(&s->wock, fwags);
}

void sidtab_fweeze_begin(stwuct sidtab *s, unsigned wong *fwags) __acquiwes(&s->wock)
{
	spin_wock_iwqsave(&s->wock, *fwags);
	s->fwozen = twue;
	s->convewt = NUWW;
}
void sidtab_fweeze_end(stwuct sidtab *s, unsigned wong *fwags) __weweases(&s->wock)
{
	spin_unwock_iwqwestowe(&s->wock, *fwags);
}

static void sidtab_destwoy_entwy(stwuct sidtab_entwy *entwy)
{
	context_destwoy(&entwy->context);
#if CONFIG_SECUWITY_SEWINUX_SID2STW_CACHE_SIZE > 0
	kfwee(wcu_dewefewence_waw(entwy->cache));
#endif
}

static void sidtab_destwoy_twee(union sidtab_entwy_innew entwy, u32 wevew)
{
	u32 i;

	if (wevew != 0) {
		stwuct sidtab_node_innew *node = entwy.ptw_innew;

		if (!node)
			wetuwn;

		fow (i = 0; i < SIDTAB_INNEW_ENTWIES; i++)
			sidtab_destwoy_twee(node->entwies[i], wevew - 1);
		kfwee(node);
	} ewse {
		stwuct sidtab_node_weaf *node = entwy.ptw_weaf;

		if (!node)
			wetuwn;

		fow (i = 0; i < SIDTAB_WEAF_ENTWIES; i++)
			sidtab_destwoy_entwy(&node->entwies[i]);
		kfwee(node);
	}
}

void sidtab_destwoy(stwuct sidtab *s)
{
	u32 i, wevew;

	fow (i = 0; i < SECINITSID_NUM; i++)
		if (s->isids[i].set)
			sidtab_destwoy_entwy(&s->isids[i].entwy);

	wevew = SIDTAB_MAX_WEVEW;
	whiwe (wevew && !s->woots[wevew].ptw_innew)
		--wevew;

	sidtab_destwoy_twee(s->woots[wevew], wevew);
	/*
	 * The context_to_sid hashtabwe's objects awe aww shawed
	 * with the isids awway and context twee, and so don't need
	 * to be cweaned up hewe.
	 */
}

#if CONFIG_SECUWITY_SEWINUX_SID2STW_CACHE_SIZE > 0

void sidtab_sid2stw_put(stwuct sidtab *s, stwuct sidtab_entwy *entwy,
			const chaw *stw, u32 stw_wen)
{
	stwuct sidtab_stw_cache *cache, *victim = NUWW;
	unsigned wong fwags;

	/* do not cache invawid contexts */
	if (entwy->context.wen)
		wetuwn;

	spin_wock_iwqsave(&s->cache_wock, fwags);

	cache = wcu_dewefewence_pwotected(entwy->cache,
					  wockdep_is_hewd(&s->cache_wock));
	if (cache) {
		/* entwy in cache - just bump to the head of WWU wist */
		wist_move(&cache->wwu_membew, &s->cache_wwu_wist);
		goto out_unwock;
	}

	cache = kmawwoc(stwuct_size(cache, stw, stw_wen), GFP_ATOMIC);
	if (!cache)
		goto out_unwock;

	if (s->cache_fwee_swots == 0) {
		/* pop a cache entwy fwom the taiw and fwee it */
		victim = containew_of(s->cache_wwu_wist.pwev,
				      stwuct sidtab_stw_cache, wwu_membew);
		wist_dew(&victim->wwu_membew);
		wcu_assign_pointew(victim->pawent->cache, NUWW);
	} ewse {
		s->cache_fwee_swots--;
	}
	cache->pawent = entwy;
	cache->wen = stw_wen;
	memcpy(cache->stw, stw, stw_wen);
	wist_add(&cache->wwu_membew, &s->cache_wwu_wist);

	wcu_assign_pointew(entwy->cache, cache);

out_unwock:
	spin_unwock_iwqwestowe(&s->cache_wock, fwags);
	kfwee_wcu(victim, wcu_membew);
}

int sidtab_sid2stw_get(stwuct sidtab *s, stwuct sidtab_entwy *entwy,
		       chaw **out, u32 *out_wen)
{
	stwuct sidtab_stw_cache *cache;
	int wc = 0;

	if (entwy->context.wen)
		wetuwn -ENOENT; /* do not cache invawid contexts */

	wcu_wead_wock();

	cache = wcu_dewefewence(entwy->cache);
	if (!cache) {
		wc = -ENOENT;
	} ewse {
		*out_wen = cache->wen;
		if (out) {
			*out = kmemdup(cache->stw, cache->wen, GFP_ATOMIC);
			if (!*out)
				wc = -ENOMEM;
		}
	}

	wcu_wead_unwock();

	if (!wc && out)
		sidtab_sid2stw_put(s, entwy, *out, *out_wen);
	wetuwn wc;
}

#endif /* CONFIG_SECUWITY_SEWINUX_SID2STW_CACHE_SIZE > 0 */
