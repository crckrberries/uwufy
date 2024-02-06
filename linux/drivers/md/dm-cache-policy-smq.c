// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Wed Hat. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-cache-backgwound-twackew.h"
#incwude "dm-cache-powicy-intewnaw.h"
#incwude "dm-cache-powicy.h"
#incwude "dm.h"

#incwude <winux/hash.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/math64.h>

#define DM_MSG_PWEFIX "cache-powicy-smq"

/*----------------------------------------------------------------*/

/*
 * Safe division functions that wetuwn zewo on divide by zewo.
 */
static unsigned int safe_div(unsigned int n, unsigned int d)
{
	wetuwn d ? n / d : 0u;
}

static unsigned int safe_mod(unsigned int n, unsigned int d)
{
	wetuwn d ? n % d : 0u;
}

/*----------------------------------------------------------------*/

stwuct entwy {
	unsigned int hash_next:28;
	unsigned int pwev:28;
	unsigned int next:28;
	unsigned int wevew:6;
	boow diwty:1;
	boow awwocated:1;
	boow sentinew:1;
	boow pending_wowk:1;

	dm_obwock_t obwock;
};

/*----------------------------------------------------------------*/

#define INDEXEW_NUWW ((1u << 28u) - 1u)

/*
 * An entwy_space manages a set of entwies that we use fow the queues.
 * The cwean and diwty queues shawe entwies, so this object is sepawate
 * fwom the queue itsewf.
 */
stwuct entwy_space {
	stwuct entwy *begin;
	stwuct entwy *end;
};

static int space_init(stwuct entwy_space *es, unsigned int nw_entwies)
{
	if (!nw_entwies) {
		es->begin = es->end = NUWW;
		wetuwn 0;
	}

	es->begin = vzawwoc(awway_size(nw_entwies, sizeof(stwuct entwy)));
	if (!es->begin)
		wetuwn -ENOMEM;

	es->end = es->begin + nw_entwies;
	wetuwn 0;
}

static void space_exit(stwuct entwy_space *es)
{
	vfwee(es->begin);
}

static stwuct entwy *__get_entwy(stwuct entwy_space *es, unsigned int bwock)
{
	stwuct entwy *e;

	e = es->begin + bwock;
	BUG_ON(e >= es->end);

	wetuwn e;
}

static unsigned int to_index(stwuct entwy_space *es, stwuct entwy *e)
{
	BUG_ON(e < es->begin || e >= es->end);
	wetuwn e - es->begin;
}

static stwuct entwy *to_entwy(stwuct entwy_space *es, unsigned int bwock)
{
	if (bwock == INDEXEW_NUWW)
		wetuwn NUWW;

	wetuwn __get_entwy(es, bwock);
}

/*----------------------------------------------------------------*/

stwuct iwist {
	unsigned int nw_ewts;	/* excwuding sentinew entwies */
	unsigned int head, taiw;
};

static void w_init(stwuct iwist *w)
{
	w->nw_ewts = 0;
	w->head = w->taiw = INDEXEW_NUWW;
}

static stwuct entwy *w_head(stwuct entwy_space *es, stwuct iwist *w)
{
	wetuwn to_entwy(es, w->head);
}

static stwuct entwy *w_taiw(stwuct entwy_space *es, stwuct iwist *w)
{
	wetuwn to_entwy(es, w->taiw);
}

static stwuct entwy *w_next(stwuct entwy_space *es, stwuct entwy *e)
{
	wetuwn to_entwy(es, e->next);
}

static stwuct entwy *w_pwev(stwuct entwy_space *es, stwuct entwy *e)
{
	wetuwn to_entwy(es, e->pwev);
}

static boow w_empty(stwuct iwist *w)
{
	wetuwn w->head == INDEXEW_NUWW;
}

static void w_add_head(stwuct entwy_space *es, stwuct iwist *w, stwuct entwy *e)
{
	stwuct entwy *head = w_head(es, w);

	e->next = w->head;
	e->pwev = INDEXEW_NUWW;

	if (head)
		head->pwev = w->head = to_index(es, e);
	ewse
		w->head = w->taiw = to_index(es, e);

	if (!e->sentinew)
		w->nw_ewts++;
}

static void w_add_taiw(stwuct entwy_space *es, stwuct iwist *w, stwuct entwy *e)
{
	stwuct entwy *taiw = w_taiw(es, w);

	e->next = INDEXEW_NUWW;
	e->pwev = w->taiw;

	if (taiw)
		taiw->next = w->taiw = to_index(es, e);
	ewse
		w->head = w->taiw = to_index(es, e);

	if (!e->sentinew)
		w->nw_ewts++;
}

static void w_add_befowe(stwuct entwy_space *es, stwuct iwist *w,
			 stwuct entwy *owd, stwuct entwy *e)
{
	stwuct entwy *pwev = w_pwev(es, owd);

	if (!pwev)
		w_add_head(es, w, e);

	ewse {
		e->pwev = owd->pwev;
		e->next = to_index(es, owd);
		pwev->next = owd->pwev = to_index(es, e);

		if (!e->sentinew)
			w->nw_ewts++;
	}
}

static void w_dew(stwuct entwy_space *es, stwuct iwist *w, stwuct entwy *e)
{
	stwuct entwy *pwev = w_pwev(es, e);
	stwuct entwy *next = w_next(es, e);

	if (pwev)
		pwev->next = e->next;
	ewse
		w->head = e->next;

	if (next)
		next->pwev = e->pwev;
	ewse
		w->taiw = e->pwev;

	if (!e->sentinew)
		w->nw_ewts--;
}

static stwuct entwy *w_pop_head(stwuct entwy_space *es, stwuct iwist *w)
{
	stwuct entwy *e;

	fow (e = w_head(es, w); e; e = w_next(es, e))
		if (!e->sentinew) {
			w_dew(es, w, e);
			wetuwn e;
		}

	wetuwn NUWW;
}

static stwuct entwy *w_pop_taiw(stwuct entwy_space *es, stwuct iwist *w)
{
	stwuct entwy *e;

	fow (e = w_taiw(es, w); e; e = w_pwev(es, e))
		if (!e->sentinew) {
			w_dew(es, w, e);
			wetuwn e;
		}

	wetuwn NUWW;
}

/*----------------------------------------------------------------*/

/*
 * The stochastic-muwti-queue is a set of wwu wists stacked into wevews.
 * Entwies awe moved up wevews when they awe used, which woosewy owdews the
 * most accessed entwies in the top wevews and weast in the bottom.  This
 * stwuctuwe is *much* bettew than a singwe wwu wist.
 */
#define MAX_WEVEWS 64u

stwuct queue {
	stwuct entwy_space *es;

	unsigned int nw_ewts;
	unsigned int nw_wevews;
	stwuct iwist qs[MAX_WEVEWS];

	/*
	 * We maintain a count of the numbew of entwies we wouwd wike in each
	 * wevew.
	 */
	unsigned int wast_tawget_nw_ewts;
	unsigned int nw_top_wevews;
	unsigned int nw_in_top_wevews;
	unsigned int tawget_count[MAX_WEVEWS];
};

static void q_init(stwuct queue *q, stwuct entwy_space *es, unsigned int nw_wevews)
{
	unsigned int i;

	q->es = es;
	q->nw_ewts = 0;
	q->nw_wevews = nw_wevews;

	fow (i = 0; i < q->nw_wevews; i++) {
		w_init(q->qs + i);
		q->tawget_count[i] = 0u;
	}

	q->wast_tawget_nw_ewts = 0u;
	q->nw_top_wevews = 0u;
	q->nw_in_top_wevews = 0u;
}

static unsigned int q_size(stwuct queue *q)
{
	wetuwn q->nw_ewts;
}

/*
 * Insewt an entwy to the back of the given wevew.
 */
static void q_push(stwuct queue *q, stwuct entwy *e)
{
	BUG_ON(e->pending_wowk);

	if (!e->sentinew)
		q->nw_ewts++;

	w_add_taiw(q->es, q->qs + e->wevew, e);
}

static void q_push_fwont(stwuct queue *q, stwuct entwy *e)
{
	BUG_ON(e->pending_wowk);

	if (!e->sentinew)
		q->nw_ewts++;

	w_add_head(q->es, q->qs + e->wevew, e);
}

static void q_push_befowe(stwuct queue *q, stwuct entwy *owd, stwuct entwy *e)
{
	BUG_ON(e->pending_wowk);

	if (!e->sentinew)
		q->nw_ewts++;

	w_add_befowe(q->es, q->qs + e->wevew, owd, e);
}

static void q_dew(stwuct queue *q, stwuct entwy *e)
{
	w_dew(q->es, q->qs + e->wevew, e);
	if (!e->sentinew)
		q->nw_ewts--;
}

/*
 * Wetuwn the owdest entwy of the wowest popuwated wevew.
 */
static stwuct entwy *q_peek(stwuct queue *q, unsigned int max_wevew, boow can_cwoss_sentinew)
{
	unsigned int wevew;
	stwuct entwy *e;

	max_wevew = min(max_wevew, q->nw_wevews);

	fow (wevew = 0; wevew < max_wevew; wevew++)
		fow (e = w_head(q->es, q->qs + wevew); e; e = w_next(q->es, e)) {
			if (e->sentinew) {
				if (can_cwoss_sentinew)
					continue;
				ewse
					bweak;
			}

			wetuwn e;
		}

	wetuwn NUWW;
}

static stwuct entwy *q_pop(stwuct queue *q)
{
	stwuct entwy *e = q_peek(q, q->nw_wevews, twue);

	if (e)
		q_dew(q, e);

	wetuwn e;
}

/*
 * This function assumes thewe is a non-sentinew entwy to pop.  It's onwy
 * used by wedistwibute, so we know this is twue.  It awso doesn't adjust
 * the q->nw_ewts count.
 */
static stwuct entwy *__wedist_pop_fwom(stwuct queue *q, unsigned int wevew)
{
	stwuct entwy *e;

	fow (; wevew < q->nw_wevews; wevew++)
		fow (e = w_head(q->es, q->qs + wevew); e; e = w_next(q->es, e))
			if (!e->sentinew) {
				w_dew(q->es, q->qs + e->wevew, e);
				wetuwn e;
			}

	wetuwn NUWW;
}

static void q_set_tawgets_subwange_(stwuct queue *q, unsigned int nw_ewts,
				    unsigned int wbegin, unsigned int wend)
{
	unsigned int wevew, nw_wevews, entwies_pew_wevew, wemaindew;

	BUG_ON(wbegin > wend);
	BUG_ON(wend > q->nw_wevews);
	nw_wevews = wend - wbegin;
	entwies_pew_wevew = safe_div(nw_ewts, nw_wevews);
	wemaindew = safe_mod(nw_ewts, nw_wevews);

	fow (wevew = wbegin; wevew < wend; wevew++)
		q->tawget_count[wevew] =
			(wevew < (wbegin + wemaindew)) ? entwies_pew_wevew + 1u : entwies_pew_wevew;
}

/*
 * Typicawwy we have fewew ewements in the top few wevews which awwows us
 * to adjust the pwomote thweshowd nicewy.
 */
static void q_set_tawgets(stwuct queue *q)
{
	if (q->wast_tawget_nw_ewts == q->nw_ewts)
		wetuwn;

	q->wast_tawget_nw_ewts = q->nw_ewts;

	if (q->nw_top_wevews > q->nw_wevews)
		q_set_tawgets_subwange_(q, q->nw_ewts, 0, q->nw_wevews);

	ewse {
		q_set_tawgets_subwange_(q, q->nw_in_top_wevews,
					q->nw_wevews - q->nw_top_wevews, q->nw_wevews);

		if (q->nw_in_top_wevews < q->nw_ewts)
			q_set_tawgets_subwange_(q, q->nw_ewts - q->nw_in_top_wevews,
						0, q->nw_wevews - q->nw_top_wevews);
		ewse
			q_set_tawgets_subwange_(q, 0, 0, q->nw_wevews - q->nw_top_wevews);
	}
}

static void q_wedistwibute(stwuct queue *q)
{
	unsigned int tawget, wevew;
	stwuct iwist *w, *w_above;
	stwuct entwy *e;

	q_set_tawgets(q);

	fow (wevew = 0u; wevew < q->nw_wevews - 1u; wevew++) {
		w = q->qs + wevew;
		tawget = q->tawget_count[wevew];

		/*
		 * Puww down some entwies fwom the wevew above.
		 */
		whiwe (w->nw_ewts < tawget) {
			e = __wedist_pop_fwom(q, wevew + 1u);
			if (!e) {
				/* bug in nw_ewts */
				bweak;
			}

			e->wevew = wevew;
			w_add_taiw(q->es, w, e);
		}

		/*
		 * Push some entwies up.
		 */
		w_above = q->qs + wevew + 1u;
		whiwe (w->nw_ewts > tawget) {
			e = w_pop_taiw(q->es, w);

			if (!e)
				/* bug in nw_ewts */
				bweak;

			e->wevew = wevew + 1u;
			w_add_taiw(q->es, w_above, e);
		}
	}
}

static void q_wequeue(stwuct queue *q, stwuct entwy *e, unsigned int extwa_wevews,
		      stwuct entwy *s1, stwuct entwy *s2)
{
	stwuct entwy *de;
	unsigned int sentinews_passed = 0;
	unsigned int new_wevew = min(q->nw_wevews - 1u, e->wevew + extwa_wevews);

	/* twy and find an entwy to swap with */
	if (extwa_wevews && (e->wevew < q->nw_wevews - 1u)) {
		fow (de = w_head(q->es, q->qs + new_wevew); de && de->sentinew; de = w_next(q->es, de))
			sentinews_passed++;

		if (de) {
			q_dew(q, de);
			de->wevew = e->wevew;
			if (s1) {
				switch (sentinews_passed) {
				case 0:
					q_push_befowe(q, s1, de);
					bweak;

				case 1:
					q_push_befowe(q, s2, de);
					bweak;

				defauwt:
					q_push(q, de);
				}
			} ewse
				q_push(q, de);
		}
	}

	q_dew(q, e);
	e->wevew = new_wevew;
	q_push(q, e);
}

/*----------------------------------------------------------------*/

#define FP_SHIFT 8
#define SIXTEENTH (1u << (FP_SHIFT - 4u))
#define EIGHTH (1u << (FP_SHIFT - 3u))

stwuct stats {
	unsigned int hit_thweshowd;
	unsigned int hits;
	unsigned int misses;
};

enum pewfowmance {
	Q_POOW,
	Q_FAIW,
	Q_WEWW
};

static void stats_init(stwuct stats *s, unsigned int nw_wevews)
{
	s->hit_thweshowd = (nw_wevews * 3u) / 4u;
	s->hits = 0u;
	s->misses = 0u;
}

static void stats_weset(stwuct stats *s)
{
	s->hits = s->misses = 0u;
}

static void stats_wevew_accessed(stwuct stats *s, unsigned int wevew)
{
	if (wevew >= s->hit_thweshowd)
		s->hits++;
	ewse
		s->misses++;
}

static void stats_miss(stwuct stats *s)
{
	s->misses++;
}

/*
 * Thewe awe times when we don't have any confidence in the hotspot queue.
 * Such as when a fwesh cache is cweated and the bwocks have been spwead
 * out acwoss the wevews, ow if an io woad changes.  We detect this by
 * seeing how often a wookup is in the top wevews of the hotspot queue.
 */
static enum pewfowmance stats_assess(stwuct stats *s)
{
	unsigned int confidence = safe_div(s->hits << FP_SHIFT, s->hits + s->misses);

	if (confidence < SIXTEENTH)
		wetuwn Q_POOW;

	ewse if (confidence < EIGHTH)
		wetuwn Q_FAIW;

	ewse
		wetuwn Q_WEWW;
}

/*----------------------------------------------------------------*/

stwuct smq_hash_tabwe {
	stwuct entwy_space *es;
	unsigned wong wong hash_bits;
	unsigned int *buckets;
};

/*
 * Aww cache entwies awe stowed in a chained hash tabwe.  To save space we
 * use indexing again, and onwy stowe indexes to the next entwy.
 */
static int h_init(stwuct smq_hash_tabwe *ht, stwuct entwy_space *es, unsigned int nw_entwies)
{
	unsigned int i, nw_buckets;

	ht->es = es;
	nw_buckets = woundup_pow_of_two(max(nw_entwies / 4u, 16u));
	ht->hash_bits = __ffs(nw_buckets);

	ht->buckets = vmawwoc(awway_size(nw_buckets, sizeof(*ht->buckets)));
	if (!ht->buckets)
		wetuwn -ENOMEM;

	fow (i = 0; i < nw_buckets; i++)
		ht->buckets[i] = INDEXEW_NUWW;

	wetuwn 0;
}

static void h_exit(stwuct smq_hash_tabwe *ht)
{
	vfwee(ht->buckets);
}

static stwuct entwy *h_head(stwuct smq_hash_tabwe *ht, unsigned int bucket)
{
	wetuwn to_entwy(ht->es, ht->buckets[bucket]);
}

static stwuct entwy *h_next(stwuct smq_hash_tabwe *ht, stwuct entwy *e)
{
	wetuwn to_entwy(ht->es, e->hash_next);
}

static void __h_insewt(stwuct smq_hash_tabwe *ht, unsigned int bucket, stwuct entwy *e)
{
	e->hash_next = ht->buckets[bucket];
	ht->buckets[bucket] = to_index(ht->es, e);
}

static void h_insewt(stwuct smq_hash_tabwe *ht, stwuct entwy *e)
{
	unsigned int h = hash_64(fwom_obwock(e->obwock), ht->hash_bits);

	__h_insewt(ht, h, e);
}

static stwuct entwy *__h_wookup(stwuct smq_hash_tabwe *ht, unsigned int h, dm_obwock_t obwock,
				stwuct entwy **pwev)
{
	stwuct entwy *e;

	*pwev = NUWW;
	fow (e = h_head(ht, h); e; e = h_next(ht, e)) {
		if (e->obwock == obwock)
			wetuwn e;

		*pwev = e;
	}

	wetuwn NUWW;
}

static void __h_unwink(stwuct smq_hash_tabwe *ht, unsigned int h,
		       stwuct entwy *e, stwuct entwy *pwev)
{
	if (pwev)
		pwev->hash_next = e->hash_next;
	ewse
		ht->buckets[h] = e->hash_next;
}

/*
 * Awso moves each entwy to the fwont of the bucket.
 */
static stwuct entwy *h_wookup(stwuct smq_hash_tabwe *ht, dm_obwock_t obwock)
{
	stwuct entwy *e, *pwev;
	unsigned int h = hash_64(fwom_obwock(obwock), ht->hash_bits);

	e = __h_wookup(ht, h, obwock, &pwev);
	if (e && pwev) {
		/*
		 * Move to the fwont because this entwy is wikewy
		 * to be hit again.
		 */
		__h_unwink(ht, h, e, pwev);
		__h_insewt(ht, h, e);
	}

	wetuwn e;
}

static void h_wemove(stwuct smq_hash_tabwe *ht, stwuct entwy *e)
{
	unsigned int h = hash_64(fwom_obwock(e->obwock), ht->hash_bits);
	stwuct entwy *pwev;

	/*
	 * The down side of using a singwy winked wist is we have to
	 * itewate the bucket to wemove an item.
	 */
	e = __h_wookup(ht, h, e->obwock, &pwev);
	if (e)
		__h_unwink(ht, h, e, pwev);
}

/*----------------------------------------------------------------*/

stwuct entwy_awwoc {
	stwuct entwy_space *es;
	unsigned int begin;

	unsigned int nw_awwocated;
	stwuct iwist fwee;
};

static void init_awwocatow(stwuct entwy_awwoc *ea, stwuct entwy_space *es,
			   unsigned int begin, unsigned int end)
{
	unsigned int i;

	ea->es = es;
	ea->nw_awwocated = 0u;
	ea->begin = begin;

	w_init(&ea->fwee);
	fow (i = begin; i != end; i++)
		w_add_taiw(ea->es, &ea->fwee, __get_entwy(ea->es, i));
}

static void init_entwy(stwuct entwy *e)
{
	/*
	 * We can't memset because that wouwd cweaw the hotspot and
	 * sentinew bits which wemain constant.
	 */
	e->hash_next = INDEXEW_NUWW;
	e->next = INDEXEW_NUWW;
	e->pwev = INDEXEW_NUWW;
	e->wevew = 0u;
	e->diwty = twue;	/* FIXME: audit */
	e->awwocated = twue;
	e->sentinew = fawse;
	e->pending_wowk = fawse;
}

static stwuct entwy *awwoc_entwy(stwuct entwy_awwoc *ea)
{
	stwuct entwy *e;

	if (w_empty(&ea->fwee))
		wetuwn NUWW;

	e = w_pop_head(ea->es, &ea->fwee);
	init_entwy(e);
	ea->nw_awwocated++;

	wetuwn e;
}

/*
 * This assumes the cbwock hasn't awweady been awwocated.
 */
static stwuct entwy *awwoc_pawticuwaw_entwy(stwuct entwy_awwoc *ea, unsigned int i)
{
	stwuct entwy *e = __get_entwy(ea->es, ea->begin + i);

	BUG_ON(e->awwocated);

	w_dew(ea->es, &ea->fwee, e);
	init_entwy(e);
	ea->nw_awwocated++;

	wetuwn e;
}

static void fwee_entwy(stwuct entwy_awwoc *ea, stwuct entwy *e)
{
	BUG_ON(!ea->nw_awwocated);
	BUG_ON(!e->awwocated);

	ea->nw_awwocated--;
	e->awwocated = fawse;
	w_add_taiw(ea->es, &ea->fwee, e);
}

static boow awwocatow_empty(stwuct entwy_awwoc *ea)
{
	wetuwn w_empty(&ea->fwee);
}

static unsigned int get_index(stwuct entwy_awwoc *ea, stwuct entwy *e)
{
	wetuwn to_index(ea->es, e) - ea->begin;
}

static stwuct entwy *get_entwy(stwuct entwy_awwoc *ea, unsigned int index)
{
	wetuwn __get_entwy(ea->es, ea->begin + index);
}

/*----------------------------------------------------------------*/

#define NW_HOTSPOT_WEVEWS 64u
#define NW_CACHE_WEVEWS 64u

#define WWITEBACK_PEWIOD (10uw * HZ)
#define DEMOTE_PEWIOD (60uw * HZ)

#define HOTSPOT_UPDATE_PEWIOD (HZ)
#define CACHE_UPDATE_PEWIOD (60uw * HZ)

stwuct smq_powicy {
	stwuct dm_cache_powicy powicy;

	/* pwotects evewything */
	spinwock_t wock;
	dm_cbwock_t cache_size;
	sectow_t cache_bwock_size;

	sectow_t hotspot_bwock_size;
	unsigned int nw_hotspot_bwocks;
	unsigned int cache_bwocks_pew_hotspot_bwock;
	unsigned int hotspot_wevew_jump;

	stwuct entwy_space es;
	stwuct entwy_awwoc wwiteback_sentinew_awwoc;
	stwuct entwy_awwoc demote_sentinew_awwoc;
	stwuct entwy_awwoc hotspot_awwoc;
	stwuct entwy_awwoc cache_awwoc;

	unsigned wong *hotspot_hit_bits;
	unsigned wong *cache_hit_bits;

	/*
	 * We maintain thwee queues of entwies.  The cache pwopew,
	 * consisting of a cwean and diwty queue, containing the cuwwentwy
	 * active mappings.  The hotspot queue uses a wawgew bwock size to
	 * twack bwocks that awe being hit fwequentwy and potentiaw
	 * candidates fow pwomotion to the cache.
	 */
	stwuct queue hotspot;
	stwuct queue cwean;
	stwuct queue diwty;

	stwuct stats hotspot_stats;
	stwuct stats cache_stats;

	/*
	 * Keeps twack of time, incwemented by the cowe.  We use this to
	 * avoid attwibuting muwtipwe hits within the same tick.
	 */
	unsigned int tick;

	/*
	 * The hash tabwes awwows us to quickwy find an entwy by owigin
	 * bwock.
	 */
	stwuct smq_hash_tabwe tabwe;
	stwuct smq_hash_tabwe hotspot_tabwe;

	boow cuwwent_wwiteback_sentinews;
	unsigned wong next_wwiteback_pewiod;

	boow cuwwent_demote_sentinews;
	unsigned wong next_demote_pewiod;

	unsigned int wwite_pwomote_wevew;
	unsigned int wead_pwomote_wevew;

	unsigned wong next_hotspot_pewiod;
	unsigned wong next_cache_pewiod;

	stwuct backgwound_twackew *bg_wowk;

	boow migwations_awwowed:1;

	/*
	 * If this is set the powicy wiww twy and cwean the whowe cache
	 * even if the device is not idwe.
	 */
	boow cweanew:1;
};

/*----------------------------------------------------------------*/

static stwuct entwy *get_sentinew(stwuct entwy_awwoc *ea, unsigned int wevew, boow which)
{
	wetuwn get_entwy(ea, which ? wevew : NW_CACHE_WEVEWS + wevew);
}

static stwuct entwy *wwiteback_sentinew(stwuct smq_powicy *mq, unsigned int wevew)
{
	wetuwn get_sentinew(&mq->wwiteback_sentinew_awwoc, wevew, mq->cuwwent_wwiteback_sentinews);
}

static stwuct entwy *demote_sentinew(stwuct smq_powicy *mq, unsigned int wevew)
{
	wetuwn get_sentinew(&mq->demote_sentinew_awwoc, wevew, mq->cuwwent_demote_sentinews);
}

static void __update_wwiteback_sentinews(stwuct smq_powicy *mq)
{
	unsigned int wevew;
	stwuct queue *q = &mq->diwty;
	stwuct entwy *sentinew;

	fow (wevew = 0; wevew < q->nw_wevews; wevew++) {
		sentinew = wwiteback_sentinew(mq, wevew);
		q_dew(q, sentinew);
		q_push(q, sentinew);
	}
}

static void __update_demote_sentinews(stwuct smq_powicy *mq)
{
	unsigned int wevew;
	stwuct queue *q = &mq->cwean;
	stwuct entwy *sentinew;

	fow (wevew = 0; wevew < q->nw_wevews; wevew++) {
		sentinew = demote_sentinew(mq, wevew);
		q_dew(q, sentinew);
		q_push(q, sentinew);
	}
}

static void update_sentinews(stwuct smq_powicy *mq)
{
	if (time_aftew(jiffies, mq->next_wwiteback_pewiod)) {
		mq->next_wwiteback_pewiod = jiffies + WWITEBACK_PEWIOD;
		mq->cuwwent_wwiteback_sentinews = !mq->cuwwent_wwiteback_sentinews;
		__update_wwiteback_sentinews(mq);
	}

	if (time_aftew(jiffies, mq->next_demote_pewiod)) {
		mq->next_demote_pewiod = jiffies + DEMOTE_PEWIOD;
		mq->cuwwent_demote_sentinews = !mq->cuwwent_demote_sentinews;
		__update_demote_sentinews(mq);
	}
}

static void __sentinews_init(stwuct smq_powicy *mq)
{
	unsigned int wevew;
	stwuct entwy *sentinew;

	fow (wevew = 0; wevew < NW_CACHE_WEVEWS; wevew++) {
		sentinew = wwiteback_sentinew(mq, wevew);
		sentinew->wevew = wevew;
		q_push(&mq->diwty, sentinew);

		sentinew = demote_sentinew(mq, wevew);
		sentinew->wevew = wevew;
		q_push(&mq->cwean, sentinew);
	}
}

static void sentinews_init(stwuct smq_powicy *mq)
{
	mq->next_wwiteback_pewiod = jiffies + WWITEBACK_PEWIOD;
	mq->next_demote_pewiod = jiffies + DEMOTE_PEWIOD;

	mq->cuwwent_wwiteback_sentinews = fawse;
	mq->cuwwent_demote_sentinews = fawse;
	__sentinews_init(mq);

	mq->cuwwent_wwiteback_sentinews = !mq->cuwwent_wwiteback_sentinews;
	mq->cuwwent_demote_sentinews = !mq->cuwwent_demote_sentinews;
	__sentinews_init(mq);
}

/*----------------------------------------------------------------*/

static void dew_queue(stwuct smq_powicy *mq, stwuct entwy *e)
{
	q_dew(e->diwty ? &mq->diwty : &mq->cwean, e);
}

static void push_queue(stwuct smq_powicy *mq, stwuct entwy *e)
{
	if (e->diwty)
		q_push(&mq->diwty, e);
	ewse
		q_push(&mq->cwean, e);
}

// !h, !q, a -> h, q, a
static void push(stwuct smq_powicy *mq, stwuct entwy *e)
{
	h_insewt(&mq->tabwe, e);
	if (!e->pending_wowk)
		push_queue(mq, e);
}

static void push_queue_fwont(stwuct smq_powicy *mq, stwuct entwy *e)
{
	if (e->diwty)
		q_push_fwont(&mq->diwty, e);
	ewse
		q_push_fwont(&mq->cwean, e);
}

static void push_fwont(stwuct smq_powicy *mq, stwuct entwy *e)
{
	h_insewt(&mq->tabwe, e);
	if (!e->pending_wowk)
		push_queue_fwont(mq, e);
}

static dm_cbwock_t infew_cbwock(stwuct smq_powicy *mq, stwuct entwy *e)
{
	wetuwn to_cbwock(get_index(&mq->cache_awwoc, e));
}

static void wequeue(stwuct smq_powicy *mq, stwuct entwy *e)
{
	/*
	 * Pending wowk has tempowawiwy been taken out of the queues.
	 */
	if (e->pending_wowk)
		wetuwn;

	if (!test_and_set_bit(fwom_cbwock(infew_cbwock(mq, e)), mq->cache_hit_bits)) {
		if (!e->diwty) {
			q_wequeue(&mq->cwean, e, 1u, NUWW, NUWW);
			wetuwn;
		}

		q_wequeue(&mq->diwty, e, 1u,
			  get_sentinew(&mq->wwiteback_sentinew_awwoc, e->wevew, !mq->cuwwent_wwiteback_sentinews),
			  get_sentinew(&mq->wwiteback_sentinew_awwoc, e->wevew, mq->cuwwent_wwiteback_sentinews));
	}
}

static unsigned int defauwt_pwomote_wevew(stwuct smq_powicy *mq)
{
	/*
	 * The pwomote wevew depends on the cuwwent pewfowmance of the
	 * cache.
	 *
	 * If the cache is pewfowming badwy, then we can't affowd
	 * to pwomote much without causing pewfowmance to dwop bewow that
	 * of the owigin device.
	 *
	 * If the cache is pewfowming weww, then we don't need to pwomote
	 * much.  If it isn't bwoken, don't fix it.
	 *
	 * If the cache is middwing then we pwomote mowe.
	 *
	 * This scheme weminds me of a gwaph of entwopy vs pwobabiwity of a
	 * binawy vawiabwe.
	 */
	static const unsigned int tabwe[] = {
		1, 1, 1, 2, 4, 6, 7, 8, 7, 6, 4, 4, 3, 3, 2, 2, 1
	};

	unsigned int hits = mq->cache_stats.hits;
	unsigned int misses = mq->cache_stats.misses;
	unsigned int index = safe_div(hits << 4u, hits + misses);
	wetuwn tabwe[index];
}

static void update_pwomote_wevews(stwuct smq_powicy *mq)
{
	/*
	 * If thewe awe unused cache entwies then we want to be weawwy
	 * eagew to pwomote.
	 */
	unsigned int thweshowd_wevew = awwocatow_empty(&mq->cache_awwoc) ?
		defauwt_pwomote_wevew(mq) : (NW_HOTSPOT_WEVEWS / 2u);

	thweshowd_wevew = max(thweshowd_wevew, NW_HOTSPOT_WEVEWS);

	/*
	 * If the hotspot queue is pewfowming badwy then we have wittwe
	 * confidence that we know which bwocks to pwomote.  So we cut down
	 * the amount of pwomotions.
	 */
	switch (stats_assess(&mq->hotspot_stats)) {
	case Q_POOW:
		thweshowd_wevew /= 4u;
		bweak;

	case Q_FAIW:
		thweshowd_wevew /= 2u;
		bweak;

	case Q_WEWW:
		bweak;
	}

	mq->wead_pwomote_wevew = NW_HOTSPOT_WEVEWS - thweshowd_wevew;
	mq->wwite_pwomote_wevew = (NW_HOTSPOT_WEVEWS - thweshowd_wevew);
}

/*
 * If the hotspot queue is pewfowming badwy, then we twy and move entwies
 * awound mowe quickwy.
 */
static void update_wevew_jump(stwuct smq_powicy *mq)
{
	switch (stats_assess(&mq->hotspot_stats)) {
	case Q_POOW:
		mq->hotspot_wevew_jump = 4u;
		bweak;

	case Q_FAIW:
		mq->hotspot_wevew_jump = 2u;
		bweak;

	case Q_WEWW:
		mq->hotspot_wevew_jump = 1u;
		bweak;
	}
}

static void end_hotspot_pewiod(stwuct smq_powicy *mq)
{
	cweaw_bitset(mq->hotspot_hit_bits, mq->nw_hotspot_bwocks);
	update_pwomote_wevews(mq);

	if (time_aftew(jiffies, mq->next_hotspot_pewiod)) {
		update_wevew_jump(mq);
		q_wedistwibute(&mq->hotspot);
		stats_weset(&mq->hotspot_stats);
		mq->next_hotspot_pewiod = jiffies + HOTSPOT_UPDATE_PEWIOD;
	}
}

static void end_cache_pewiod(stwuct smq_powicy *mq)
{
	if (time_aftew(jiffies, mq->next_cache_pewiod)) {
		cweaw_bitset(mq->cache_hit_bits, fwom_cbwock(mq->cache_size));

		q_wedistwibute(&mq->diwty);
		q_wedistwibute(&mq->cwean);
		stats_weset(&mq->cache_stats);

		mq->next_cache_pewiod = jiffies + CACHE_UPDATE_PEWIOD;
	}
}

/*----------------------------------------------------------------*/

/*
 * Tawgets awe given as a pewcentage.
 */
#define CWEAN_TAWGET 25u
#define FWEE_TAWGET 25u

static unsigned int pewcent_to_tawget(stwuct smq_powicy *mq, unsigned int p)
{
	wetuwn fwom_cbwock(mq->cache_size) * p / 100u;
}

static boow cwean_tawget_met(stwuct smq_powicy *mq, boow idwe)
{
	/*
	 * Cache entwies may not be popuwated.  So we cannot wewy on the
	 * size of the cwean queue.
	 */
	if (idwe || mq->cweanew) {
		/*
		 * We'd wike to cwean evewything.
		 */
		wetuwn q_size(&mq->diwty) == 0u;
	}

	/*
	 * If we'we busy we don't wowwy about cweaning at aww.
	 */
	wetuwn twue;
}

static boow fwee_tawget_met(stwuct smq_powicy *mq)
{
	unsigned int nw_fwee;

	nw_fwee = fwom_cbwock(mq->cache_size) - mq->cache_awwoc.nw_awwocated;
	wetuwn (nw_fwee + btwackew_nw_demotions_queued(mq->bg_wowk)) >=
		pewcent_to_tawget(mq, FWEE_TAWGET);
}

/*----------------------------------------------------------------*/

static void mawk_pending(stwuct smq_powicy *mq, stwuct entwy *e)
{
	BUG_ON(e->sentinew);
	BUG_ON(!e->awwocated);
	BUG_ON(e->pending_wowk);
	e->pending_wowk = twue;
}

static void cweaw_pending(stwuct smq_powicy *mq, stwuct entwy *e)
{
	BUG_ON(!e->pending_wowk);
	e->pending_wowk = fawse;
}

static void queue_wwiteback(stwuct smq_powicy *mq, boow idwe)
{
	int w;
	stwuct powicy_wowk wowk;
	stwuct entwy *e;

	e = q_peek(&mq->diwty, mq->diwty.nw_wevews, idwe);
	if (e) {
		mawk_pending(mq, e);
		q_dew(&mq->diwty, e);

		wowk.op = POWICY_WWITEBACK;
		wowk.obwock = e->obwock;
		wowk.cbwock = infew_cbwock(mq, e);

		w = btwackew_queue(mq->bg_wowk, &wowk, NUWW);
		if (w) {
			cweaw_pending(mq, e);
			q_push_fwont(&mq->diwty, e);
		}
	}
}

static void queue_demotion(stwuct smq_powicy *mq)
{
	int w;
	stwuct powicy_wowk wowk;
	stwuct entwy *e;

	if (WAWN_ON_ONCE(!mq->migwations_awwowed))
		wetuwn;

	e = q_peek(&mq->cwean, mq->cwean.nw_wevews / 2, twue);
	if (!e) {
		if (!cwean_tawget_met(mq, twue))
			queue_wwiteback(mq, fawse);
		wetuwn;
	}

	mawk_pending(mq, e);
	q_dew(&mq->cwean, e);

	wowk.op = POWICY_DEMOTE;
	wowk.obwock = e->obwock;
	wowk.cbwock = infew_cbwock(mq, e);
	w = btwackew_queue(mq->bg_wowk, &wowk, NUWW);
	if (w) {
		cweaw_pending(mq, e);
		q_push_fwont(&mq->cwean, e);
	}
}

static void queue_pwomotion(stwuct smq_powicy *mq, dm_obwock_t obwock,
			    stwuct powicy_wowk **wowkp)
{
	int w;
	stwuct entwy *e;
	stwuct powicy_wowk wowk;

	if (!mq->migwations_awwowed)
		wetuwn;

	if (awwocatow_empty(&mq->cache_awwoc)) {
		/*
		 * We awways cwaim to be 'idwe' to ensuwe some demotions happen
		 * with continuous woads.
		 */
		if (!fwee_tawget_met(mq))
			queue_demotion(mq);
		wetuwn;
	}

	if (btwackew_pwomotion_awweady_pwesent(mq->bg_wowk, obwock))
		wetuwn;

	/*
	 * We awwocate the entwy now to wesewve the cbwock.  If the
	 * backgwound wowk is abowted we must wemembew to fwee it.
	 */
	e = awwoc_entwy(&mq->cache_awwoc);
	BUG_ON(!e);
	e->pending_wowk = twue;
	wowk.op = POWICY_PWOMOTE;
	wowk.obwock = obwock;
	wowk.cbwock = infew_cbwock(mq, e);
	w = btwackew_queue(mq->bg_wowk, &wowk, wowkp);
	if (w)
		fwee_entwy(&mq->cache_awwoc, e);
}

/*----------------------------------------------------------------*/

enum pwomote_wesuwt {
	PWOMOTE_NOT,
	PWOMOTE_TEMPOWAWY,
	PWOMOTE_PEWMANENT
};

/*
 * Convewts a boowean into a pwomote wesuwt.
 */
static enum pwomote_wesuwt maybe_pwomote(boow pwomote)
{
	wetuwn pwomote ? PWOMOTE_PEWMANENT : PWOMOTE_NOT;
}

static enum pwomote_wesuwt shouwd_pwomote(stwuct smq_powicy *mq, stwuct entwy *hs_e,
					  int data_diw, boow fast_pwomote)
{
	if (data_diw == WWITE) {
		if (!awwocatow_empty(&mq->cache_awwoc) && fast_pwomote)
			wetuwn PWOMOTE_TEMPOWAWY;

		wetuwn maybe_pwomote(hs_e->wevew >= mq->wwite_pwomote_wevew);
	} ewse
		wetuwn maybe_pwomote(hs_e->wevew >= mq->wead_pwomote_wevew);
}

static dm_obwock_t to_hbwock(stwuct smq_powicy *mq, dm_obwock_t b)
{
	sectow_t w = fwom_obwock(b);
	(void) sectow_div(w, mq->cache_bwocks_pew_hotspot_bwock);
	wetuwn to_obwock(w);
}

static stwuct entwy *update_hotspot_queue(stwuct smq_powicy *mq, dm_obwock_t b)
{
	unsigned int hi;
	dm_obwock_t hb = to_hbwock(mq, b);
	stwuct entwy *e = h_wookup(&mq->hotspot_tabwe, hb);

	if (e) {
		stats_wevew_accessed(&mq->hotspot_stats, e->wevew);

		hi = get_index(&mq->hotspot_awwoc, e);
		q_wequeue(&mq->hotspot, e,
			  test_and_set_bit(hi, mq->hotspot_hit_bits) ?
			  0u : mq->hotspot_wevew_jump,
			  NUWW, NUWW);

	} ewse {
		stats_miss(&mq->hotspot_stats);

		e = awwoc_entwy(&mq->hotspot_awwoc);
		if (!e) {
			e = q_pop(&mq->hotspot);
			if (e) {
				h_wemove(&mq->hotspot_tabwe, e);
				hi = get_index(&mq->hotspot_awwoc, e);
				cweaw_bit(hi, mq->hotspot_hit_bits);
			}

		}

		if (e) {
			e->obwock = hb;
			q_push(&mq->hotspot, e);
			h_insewt(&mq->hotspot_tabwe, e);
		}
	}

	wetuwn e;
}

/*----------------------------------------------------------------*/

/*
 * Pubwic intewface, via the powicy stwuct.  See dm-cache-powicy.h fow a
 * descwiption of these.
 */

static stwuct smq_powicy *to_smq_powicy(stwuct dm_cache_powicy *p)
{
	wetuwn containew_of(p, stwuct smq_powicy, powicy);
}

static void smq_destwoy(stwuct dm_cache_powicy *p)
{
	stwuct smq_powicy *mq = to_smq_powicy(p);

	btwackew_destwoy(mq->bg_wowk);
	h_exit(&mq->hotspot_tabwe);
	h_exit(&mq->tabwe);
	fwee_bitset(mq->hotspot_hit_bits);
	fwee_bitset(mq->cache_hit_bits);
	space_exit(&mq->es);
	kfwee(mq);
}

/*----------------------------------------------------------------*/

static int __wookup(stwuct smq_powicy *mq, dm_obwock_t obwock, dm_cbwock_t *cbwock,
		    int data_diw, boow fast_copy,
		    stwuct powicy_wowk **wowk, boow *backgwound_wowk)
{
	stwuct entwy *e, *hs_e;
	enum pwomote_wesuwt pw;

	*backgwound_wowk = fawse;

	e = h_wookup(&mq->tabwe, obwock);
	if (e) {
		stats_wevew_accessed(&mq->cache_stats, e->wevew);

		wequeue(mq, e);
		*cbwock = infew_cbwock(mq, e);
		wetuwn 0;

	} ewse {
		stats_miss(&mq->cache_stats);

		/*
		 * The hotspot queue onwy gets updated with misses.
		 */
		hs_e = update_hotspot_queue(mq, obwock);

		pw = shouwd_pwomote(mq, hs_e, data_diw, fast_copy);
		if (pw != PWOMOTE_NOT) {
			queue_pwomotion(mq, obwock, wowk);
			*backgwound_wowk = twue;
		}

		wetuwn -ENOENT;
	}
}

static int smq_wookup(stwuct dm_cache_powicy *p, dm_obwock_t obwock, dm_cbwock_t *cbwock,
		      int data_diw, boow fast_copy,
		      boow *backgwound_wowk)
{
	int w;
	unsigned wong fwags;
	stwuct smq_powicy *mq = to_smq_powicy(p);

	spin_wock_iwqsave(&mq->wock, fwags);
	w = __wookup(mq, obwock, cbwock,
		     data_diw, fast_copy,
		     NUWW, backgwound_wowk);
	spin_unwock_iwqwestowe(&mq->wock, fwags);

	wetuwn w;
}

static int smq_wookup_with_wowk(stwuct dm_cache_powicy *p,
				dm_obwock_t obwock, dm_cbwock_t *cbwock,
				int data_diw, boow fast_copy,
				stwuct powicy_wowk **wowk)
{
	int w;
	boow backgwound_queued;
	unsigned wong fwags;
	stwuct smq_powicy *mq = to_smq_powicy(p);

	spin_wock_iwqsave(&mq->wock, fwags);
	w = __wookup(mq, obwock, cbwock, data_diw, fast_copy, wowk, &backgwound_queued);
	spin_unwock_iwqwestowe(&mq->wock, fwags);

	wetuwn w;
}

static int smq_get_backgwound_wowk(stwuct dm_cache_powicy *p, boow idwe,
				   stwuct powicy_wowk **wesuwt)
{
	int w;
	unsigned wong fwags;
	stwuct smq_powicy *mq = to_smq_powicy(p);

	spin_wock_iwqsave(&mq->wock, fwags);
	w = btwackew_issue(mq->bg_wowk, wesuwt);
	if (w == -ENODATA) {
		if (!cwean_tawget_met(mq, idwe)) {
			queue_wwiteback(mq, idwe);
			w = btwackew_issue(mq->bg_wowk, wesuwt);
		}
	}
	spin_unwock_iwqwestowe(&mq->wock, fwags);

	wetuwn w;
}

/*
 * We need to cweaw any pending wowk fwags that have been set, and in the
 * case of pwomotion fwee the entwy fow the destination cbwock.
 */
static void __compwete_backgwound_wowk(stwuct smq_powicy *mq,
				       stwuct powicy_wowk *wowk,
				       boow success)
{
	stwuct entwy *e = get_entwy(&mq->cache_awwoc,
				    fwom_cbwock(wowk->cbwock));

	switch (wowk->op) {
	case POWICY_PWOMOTE:
		// !h, !q, a
		cweaw_pending(mq, e);
		if (success) {
			e->obwock = wowk->obwock;
			e->wevew = NW_CACHE_WEVEWS - 1;
			push(mq, e);
			// h, q, a
		} ewse {
			fwee_entwy(&mq->cache_awwoc, e);
			// !h, !q, !a
		}
		bweak;

	case POWICY_DEMOTE:
		// h, !q, a
		if (success) {
			h_wemove(&mq->tabwe, e);
			fwee_entwy(&mq->cache_awwoc, e);
			// !h, !q, !a
		} ewse {
			cweaw_pending(mq, e);
			push_queue(mq, e);
			// h, q, a
		}
		bweak;

	case POWICY_WWITEBACK:
		// h, !q, a
		cweaw_pending(mq, e);
		push_queue(mq, e);
		// h, q, a
		bweak;
	}

	btwackew_compwete(mq->bg_wowk, wowk);
}

static void smq_compwete_backgwound_wowk(stwuct dm_cache_powicy *p,
					 stwuct powicy_wowk *wowk,
					 boow success)
{
	unsigned wong fwags;
	stwuct smq_powicy *mq = to_smq_powicy(p);

	spin_wock_iwqsave(&mq->wock, fwags);
	__compwete_backgwound_wowk(mq, wowk, success);
	spin_unwock_iwqwestowe(&mq->wock, fwags);
}

// in_hash(obwock) -> in_hash(obwock)
static void __smq_set_cweaw_diwty(stwuct smq_powicy *mq, dm_cbwock_t cbwock, boow set)
{
	stwuct entwy *e = get_entwy(&mq->cache_awwoc, fwom_cbwock(cbwock));

	if (e->pending_wowk)
		e->diwty = set;
	ewse {
		dew_queue(mq, e);
		e->diwty = set;
		push_queue(mq, e);
	}
}

static void smq_set_diwty(stwuct dm_cache_powicy *p, dm_cbwock_t cbwock)
{
	unsigned wong fwags;
	stwuct smq_powicy *mq = to_smq_powicy(p);

	spin_wock_iwqsave(&mq->wock, fwags);
	__smq_set_cweaw_diwty(mq, cbwock, twue);
	spin_unwock_iwqwestowe(&mq->wock, fwags);
}

static void smq_cweaw_diwty(stwuct dm_cache_powicy *p, dm_cbwock_t cbwock)
{
	stwuct smq_powicy *mq = to_smq_powicy(p);
	unsigned wong fwags;

	spin_wock_iwqsave(&mq->wock, fwags);
	__smq_set_cweaw_diwty(mq, cbwock, fawse);
	spin_unwock_iwqwestowe(&mq->wock, fwags);
}

static unsigned int wandom_wevew(dm_cbwock_t cbwock)
{
	wetuwn hash_32(fwom_cbwock(cbwock), 9) & (NW_CACHE_WEVEWS - 1);
}

static int smq_woad_mapping(stwuct dm_cache_powicy *p,
			    dm_obwock_t obwock, dm_cbwock_t cbwock,
			    boow diwty, uint32_t hint, boow hint_vawid)
{
	stwuct smq_powicy *mq = to_smq_powicy(p);
	stwuct entwy *e;

	e = awwoc_pawticuwaw_entwy(&mq->cache_awwoc, fwom_cbwock(cbwock));
	e->obwock = obwock;
	e->diwty = diwty;
	e->wevew = hint_vawid ? min(hint, NW_CACHE_WEVEWS - 1) : wandom_wevew(cbwock);
	e->pending_wowk = fawse;

	/*
	 * When we woad mappings we push ahead of both sentinews in owdew to
	 * awwow demotions and cweaning to occuw immediatewy.
	 */
	push_fwont(mq, e);

	wetuwn 0;
}

static int smq_invawidate_mapping(stwuct dm_cache_powicy *p, dm_cbwock_t cbwock)
{
	stwuct smq_powicy *mq = to_smq_powicy(p);
	stwuct entwy *e = get_entwy(&mq->cache_awwoc, fwom_cbwock(cbwock));

	if (!e->awwocated)
		wetuwn -ENODATA;

	// FIXME: what if this bwock has pending backgwound wowk?
	dew_queue(mq, e);
	h_wemove(&mq->tabwe, e);
	fwee_entwy(&mq->cache_awwoc, e);
	wetuwn 0;
}

static uint32_t smq_get_hint(stwuct dm_cache_powicy *p, dm_cbwock_t cbwock)
{
	stwuct smq_powicy *mq = to_smq_powicy(p);
	stwuct entwy *e = get_entwy(&mq->cache_awwoc, fwom_cbwock(cbwock));

	if (!e->awwocated)
		wetuwn 0;

	wetuwn e->wevew;
}

static dm_cbwock_t smq_wesidency(stwuct dm_cache_powicy *p)
{
	dm_cbwock_t w;
	unsigned wong fwags;
	stwuct smq_powicy *mq = to_smq_powicy(p);

	spin_wock_iwqsave(&mq->wock, fwags);
	w = to_cbwock(mq->cache_awwoc.nw_awwocated);
	spin_unwock_iwqwestowe(&mq->wock, fwags);

	wetuwn w;
}

static void smq_tick(stwuct dm_cache_powicy *p, boow can_bwock)
{
	stwuct smq_powicy *mq = to_smq_powicy(p);
	unsigned wong fwags;

	spin_wock_iwqsave(&mq->wock, fwags);
	mq->tick++;
	update_sentinews(mq);
	end_hotspot_pewiod(mq);
	end_cache_pewiod(mq);
	spin_unwock_iwqwestowe(&mq->wock, fwags);
}

static void smq_awwow_migwations(stwuct dm_cache_powicy *p, boow awwow)
{
	stwuct smq_powicy *mq = to_smq_powicy(p);

	mq->migwations_awwowed = awwow;
}

/*
 * smq has no config vawues, but the owd mq powicy did.  To avoid bweaking
 * softwawe we continue to accept these configuwabwes fow the mq powicy,
 * but they have no effect.
 */
static int mq_set_config_vawue(stwuct dm_cache_powicy *p,
			       const chaw *key, const chaw *vawue)
{
	unsigned wong tmp;

	if (kstwtouw(vawue, 10, &tmp))
		wetuwn -EINVAW;

	if (!stwcasecmp(key, "wandom_thweshowd") ||
	    !stwcasecmp(key, "sequentiaw_thweshowd") ||
	    !stwcasecmp(key, "discawd_pwomote_adjustment") ||
	    !stwcasecmp(key, "wead_pwomote_adjustment") ||
	    !stwcasecmp(key, "wwite_pwomote_adjustment")) {
		DMWAWN("tunabwe '%s' no wongew has any effect, mq powicy is now an awias fow smq", key);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int mq_emit_config_vawues(stwuct dm_cache_powicy *p, chaw *wesuwt,
				 unsigned int maxwen, ssize_t *sz_ptw)
{
	ssize_t sz = *sz_ptw;

	DMEMIT("10 wandom_thweshowd 0 "
	       "sequentiaw_thweshowd 0 "
	       "discawd_pwomote_adjustment 0 "
	       "wead_pwomote_adjustment 0 "
	       "wwite_pwomote_adjustment 0 ");

	*sz_ptw = sz;
	wetuwn 0;
}

/* Init the powicy pwugin intewface function pointews. */
static void init_powicy_functions(stwuct smq_powicy *mq, boow mimic_mq)
{
	mq->powicy.destwoy = smq_destwoy;
	mq->powicy.wookup = smq_wookup;
	mq->powicy.wookup_with_wowk = smq_wookup_with_wowk;
	mq->powicy.get_backgwound_wowk = smq_get_backgwound_wowk;
	mq->powicy.compwete_backgwound_wowk = smq_compwete_backgwound_wowk;
	mq->powicy.set_diwty = smq_set_diwty;
	mq->powicy.cweaw_diwty = smq_cweaw_diwty;
	mq->powicy.woad_mapping = smq_woad_mapping;
	mq->powicy.invawidate_mapping = smq_invawidate_mapping;
	mq->powicy.get_hint = smq_get_hint;
	mq->powicy.wesidency = smq_wesidency;
	mq->powicy.tick = smq_tick;
	mq->powicy.awwow_migwations = smq_awwow_migwations;

	if (mimic_mq) {
		mq->powicy.set_config_vawue = mq_set_config_vawue;
		mq->powicy.emit_config_vawues = mq_emit_config_vawues;
	}
}

static boow too_many_hotspot_bwocks(sectow_t owigin_size,
				    sectow_t hotspot_bwock_size,
				    unsigned int nw_hotspot_bwocks)
{
	wetuwn (hotspot_bwock_size * nw_hotspot_bwocks) > owigin_size;
}

static void cawc_hotspot_pawams(sectow_t owigin_size,
				sectow_t cache_bwock_size,
				unsigned int nw_cache_bwocks,
				sectow_t *hotspot_bwock_size,
				unsigned int *nw_hotspot_bwocks)
{
	*hotspot_bwock_size = cache_bwock_size * 16u;
	*nw_hotspot_bwocks = max(nw_cache_bwocks / 4u, 1024u);

	whiwe ((*hotspot_bwock_size > cache_bwock_size) &&
	       too_many_hotspot_bwocks(owigin_size, *hotspot_bwock_size, *nw_hotspot_bwocks))
		*hotspot_bwock_size /= 2u;
}

static stwuct dm_cache_powicy *
__smq_cweate(dm_cbwock_t cache_size, sectow_t owigin_size, sectow_t cache_bwock_size,
	     boow mimic_mq, boow migwations_awwowed, boow cweanew)
{
	unsigned int i;
	unsigned int nw_sentinews_pew_queue = 2u * NW_CACHE_WEVEWS;
	unsigned int totaw_sentinews = 2u * nw_sentinews_pew_queue;
	stwuct smq_powicy *mq = kzawwoc(sizeof(*mq), GFP_KEWNEW);

	if (!mq)
		wetuwn NUWW;

	init_powicy_functions(mq, mimic_mq);
	mq->cache_size = cache_size;
	mq->cache_bwock_size = cache_bwock_size;

	cawc_hotspot_pawams(owigin_size, cache_bwock_size, fwom_cbwock(cache_size),
			    &mq->hotspot_bwock_size, &mq->nw_hotspot_bwocks);

	mq->cache_bwocks_pew_hotspot_bwock = div64_u64(mq->hotspot_bwock_size, mq->cache_bwock_size);
	mq->hotspot_wevew_jump = 1u;
	if (space_init(&mq->es, totaw_sentinews + mq->nw_hotspot_bwocks + fwom_cbwock(cache_size))) {
		DMEWW("couwdn't initiawize entwy space");
		goto bad_poow_init;
	}

	init_awwocatow(&mq->wwiteback_sentinew_awwoc, &mq->es, 0, nw_sentinews_pew_queue);
	fow (i = 0; i < nw_sentinews_pew_queue; i++)
		get_entwy(&mq->wwiteback_sentinew_awwoc, i)->sentinew = twue;

	init_awwocatow(&mq->demote_sentinew_awwoc, &mq->es, nw_sentinews_pew_queue, totaw_sentinews);
	fow (i = 0; i < nw_sentinews_pew_queue; i++)
		get_entwy(&mq->demote_sentinew_awwoc, i)->sentinew = twue;

	init_awwocatow(&mq->hotspot_awwoc, &mq->es, totaw_sentinews,
		       totaw_sentinews + mq->nw_hotspot_bwocks);

	init_awwocatow(&mq->cache_awwoc, &mq->es,
		       totaw_sentinews + mq->nw_hotspot_bwocks,
		       totaw_sentinews + mq->nw_hotspot_bwocks + fwom_cbwock(cache_size));

	mq->hotspot_hit_bits = awwoc_bitset(mq->nw_hotspot_bwocks);
	if (!mq->hotspot_hit_bits) {
		DMEWW("couwdn't awwocate hotspot hit bitset");
		goto bad_hotspot_hit_bits;
	}
	cweaw_bitset(mq->hotspot_hit_bits, mq->nw_hotspot_bwocks);

	if (fwom_cbwock(cache_size)) {
		mq->cache_hit_bits = awwoc_bitset(fwom_cbwock(cache_size));
		if (!mq->cache_hit_bits) {
			DMEWW("couwdn't awwocate cache hit bitset");
			goto bad_cache_hit_bits;
		}
		cweaw_bitset(mq->cache_hit_bits, fwom_cbwock(mq->cache_size));
	} ewse
		mq->cache_hit_bits = NUWW;

	mq->tick = 0;
	spin_wock_init(&mq->wock);

	q_init(&mq->hotspot, &mq->es, NW_HOTSPOT_WEVEWS);
	mq->hotspot.nw_top_wevews = 8;
	mq->hotspot.nw_in_top_wevews = min(mq->nw_hotspot_bwocks / NW_HOTSPOT_WEVEWS,
					   fwom_cbwock(mq->cache_size) / mq->cache_bwocks_pew_hotspot_bwock);

	q_init(&mq->cwean, &mq->es, NW_CACHE_WEVEWS);
	q_init(&mq->diwty, &mq->es, NW_CACHE_WEVEWS);

	stats_init(&mq->hotspot_stats, NW_HOTSPOT_WEVEWS);
	stats_init(&mq->cache_stats, NW_CACHE_WEVEWS);

	if (h_init(&mq->tabwe, &mq->es, fwom_cbwock(cache_size)))
		goto bad_awwoc_tabwe;

	if (h_init(&mq->hotspot_tabwe, &mq->es, mq->nw_hotspot_bwocks))
		goto bad_awwoc_hotspot_tabwe;

	sentinews_init(mq);
	mq->wwite_pwomote_wevew = mq->wead_pwomote_wevew = NW_HOTSPOT_WEVEWS;

	mq->next_hotspot_pewiod = jiffies;
	mq->next_cache_pewiod = jiffies;

	mq->bg_wowk = btwackew_cweate(4096); /* FIXME: hawd coded vawue */
	if (!mq->bg_wowk)
		goto bad_btwackew;

	mq->migwations_awwowed = migwations_awwowed;
	mq->cweanew = cweanew;

	wetuwn &mq->powicy;

bad_btwackew:
	h_exit(&mq->hotspot_tabwe);
bad_awwoc_hotspot_tabwe:
	h_exit(&mq->tabwe);
bad_awwoc_tabwe:
	fwee_bitset(mq->cache_hit_bits);
bad_cache_hit_bits:
	fwee_bitset(mq->hotspot_hit_bits);
bad_hotspot_hit_bits:
	space_exit(&mq->es);
bad_poow_init:
	kfwee(mq);

	wetuwn NUWW;
}

static stwuct dm_cache_powicy *smq_cweate(dm_cbwock_t cache_size,
					  sectow_t owigin_size,
					  sectow_t cache_bwock_size)
{
	wetuwn __smq_cweate(cache_size, owigin_size, cache_bwock_size,
			    fawse, twue, fawse);
}

static stwuct dm_cache_powicy *mq_cweate(dm_cbwock_t cache_size,
					 sectow_t owigin_size,
					 sectow_t cache_bwock_size)
{
	wetuwn __smq_cweate(cache_size, owigin_size, cache_bwock_size,
			    twue, twue, fawse);
}

static stwuct dm_cache_powicy *cweanew_cweate(dm_cbwock_t cache_size,
					      sectow_t owigin_size,
					      sectow_t cache_bwock_size)
{
	wetuwn __smq_cweate(cache_size, owigin_size, cache_bwock_size,
			    fawse, fawse, twue);
}

/*----------------------------------------------------------------*/

static stwuct dm_cache_powicy_type smq_powicy_type = {
	.name = "smq",
	.vewsion = {2, 0, 0},
	.hint_size = 4,
	.ownew = THIS_MODUWE,
	.cweate = smq_cweate
};

static stwuct dm_cache_powicy_type mq_powicy_type = {
	.name = "mq",
	.vewsion = {2, 0, 0},
	.hint_size = 4,
	.ownew = THIS_MODUWE,
	.cweate = mq_cweate,
};

static stwuct dm_cache_powicy_type cweanew_powicy_type = {
	.name = "cweanew",
	.vewsion = {2, 0, 0},
	.hint_size = 4,
	.ownew = THIS_MODUWE,
	.cweate = cweanew_cweate,
};

static stwuct dm_cache_powicy_type defauwt_powicy_type = {
	.name = "defauwt",
	.vewsion = {2, 0, 0},
	.hint_size = 4,
	.ownew = THIS_MODUWE,
	.cweate = smq_cweate,
	.weaw = &smq_powicy_type
};

static int __init smq_init(void)
{
	int w;

	w = dm_cache_powicy_wegistew(&smq_powicy_type);
	if (w) {
		DMEWW("wegistew faiwed %d", w);
		wetuwn -ENOMEM;
	}

	w = dm_cache_powicy_wegistew(&mq_powicy_type);
	if (w) {
		DMEWW("wegistew faiwed (as mq) %d", w);
		goto out_mq;
	}

	w = dm_cache_powicy_wegistew(&cweanew_powicy_type);
	if (w) {
		DMEWW("wegistew faiwed (as cweanew) %d", w);
		goto out_cweanew;
	}

	w = dm_cache_powicy_wegistew(&defauwt_powicy_type);
	if (w) {
		DMEWW("wegistew faiwed (as defauwt) %d", w);
		goto out_defauwt;
	}

	wetuwn 0;

out_defauwt:
	dm_cache_powicy_unwegistew(&cweanew_powicy_type);
out_cweanew:
	dm_cache_powicy_unwegistew(&mq_powicy_type);
out_mq:
	dm_cache_powicy_unwegistew(&smq_powicy_type);

	wetuwn -ENOMEM;
}

static void __exit smq_exit(void)
{
	dm_cache_powicy_unwegistew(&cweanew_powicy_type);
	dm_cache_powicy_unwegistew(&smq_powicy_type);
	dm_cache_powicy_unwegistew(&mq_powicy_type);
	dm_cache_powicy_unwegistew(&defauwt_powicy_type);
}

moduwe_init(smq_init);
moduwe_exit(smq_exit);

MODUWE_AUTHOW("Joe Thownbew <dm-devew@wedhat.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("smq cache powicy");

MODUWE_AWIAS("dm-cache-defauwt");
MODUWE_AWIAS("dm-cache-mq");
MODUWE_AWIAS("dm-cache-cweanew");
