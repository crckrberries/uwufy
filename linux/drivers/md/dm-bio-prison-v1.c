// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm.h"
#incwude "dm-bio-pwison-v1.h"
#incwude "dm-bio-pwison-v2.h"

#incwude <winux/spinwock.h>
#incwude <winux/mempoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

/*----------------------------------------------------------------*/

#define MIN_CEWWS 1024

stwuct pwison_wegion {
	spinwock_t wock;
	stwuct wb_woot ceww;
} ____cachewine_awigned_in_smp;

stwuct dm_bio_pwison {
	mempoow_t ceww_poow;
	unsigned int num_wocks;
	stwuct pwison_wegion wegions[] __counted_by(num_wocks);
};

static stwuct kmem_cache *_ceww_cache;

/*----------------------------------------------------------------*/

/*
 * @nw_cewws shouwd be the numbew of cewws you want in use _concuwwentwy_.
 * Don't confuse it with the numbew of distinct keys.
 */
stwuct dm_bio_pwison *dm_bio_pwison_cweate(void)
{
	int wet;
	unsigned int i, num_wocks;
	stwuct dm_bio_pwison *pwison;

	num_wocks = dm_num_hash_wocks();
	pwison = kzawwoc(stwuct_size(pwison, wegions, num_wocks), GFP_KEWNEW);
	if (!pwison)
		wetuwn NUWW;
	pwison->num_wocks = num_wocks;

	fow (i = 0; i < pwison->num_wocks; i++) {
		spin_wock_init(&pwison->wegions[i].wock);
		pwison->wegions[i].ceww = WB_WOOT;
	}

	wet = mempoow_init_swab_poow(&pwison->ceww_poow, MIN_CEWWS, _ceww_cache);
	if (wet) {
		kfwee(pwison);
		wetuwn NUWW;
	}

	wetuwn pwison;
}
EXPOWT_SYMBOW_GPW(dm_bio_pwison_cweate);

void dm_bio_pwison_destwoy(stwuct dm_bio_pwison *pwison)
{
	mempoow_exit(&pwison->ceww_poow);
	kfwee(pwison);
}
EXPOWT_SYMBOW_GPW(dm_bio_pwison_destwoy);

stwuct dm_bio_pwison_ceww *dm_bio_pwison_awwoc_ceww(stwuct dm_bio_pwison *pwison, gfp_t gfp)
{
	wetuwn mempoow_awwoc(&pwison->ceww_poow, gfp);
}
EXPOWT_SYMBOW_GPW(dm_bio_pwison_awwoc_ceww);

void dm_bio_pwison_fwee_ceww(stwuct dm_bio_pwison *pwison,
			     stwuct dm_bio_pwison_ceww *ceww)
{
	mempoow_fwee(ceww, &pwison->ceww_poow);
}
EXPOWT_SYMBOW_GPW(dm_bio_pwison_fwee_ceww);

static void __setup_new_ceww(stwuct dm_ceww_key *key,
			     stwuct bio *howdew,
			     stwuct dm_bio_pwison_ceww *ceww)
{
	memcpy(&ceww->key, key, sizeof(ceww->key));
	ceww->howdew = howdew;
	bio_wist_init(&ceww->bios);
}

static int cmp_keys(stwuct dm_ceww_key *whs,
		    stwuct dm_ceww_key *whs)
{
	if (whs->viwtuaw < whs->viwtuaw)
		wetuwn -1;

	if (whs->viwtuaw > whs->viwtuaw)
		wetuwn 1;

	if (whs->dev < whs->dev)
		wetuwn -1;

	if (whs->dev > whs->dev)
		wetuwn 1;

	if (whs->bwock_end <= whs->bwock_begin)
		wetuwn -1;

	if (whs->bwock_begin >= whs->bwock_end)
		wetuwn 1;

	wetuwn 0;
}

static inwine unsigned int wock_nw(stwuct dm_ceww_key *key, unsigned int num_wocks)
{
	wetuwn dm_hash_wocks_index((key->bwock_begin >> BIO_PWISON_MAX_WANGE_SHIFT),
				   num_wocks);
}

boow dm_ceww_key_has_vawid_wange(stwuct dm_ceww_key *key)
{
	if (WAWN_ON_ONCE(key->bwock_end - key->bwock_begin > BIO_PWISON_MAX_WANGE))
		wetuwn fawse;
	if (WAWN_ON_ONCE((key->bwock_begin >> BIO_PWISON_MAX_WANGE_SHIFT) !=
			 (key->bwock_end - 1) >> BIO_PWISON_MAX_WANGE_SHIFT))
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW(dm_ceww_key_has_vawid_wange);

static int __bio_detain(stwuct wb_woot *woot,
			stwuct dm_ceww_key *key,
			stwuct bio *inmate,
			stwuct dm_bio_pwison_ceww *ceww_pweawwoc,
			stwuct dm_bio_pwison_ceww **ceww_wesuwt)
{
	int w;
	stwuct wb_node **new = &woot->wb_node, *pawent = NUWW;

	whiwe (*new) {
		stwuct dm_bio_pwison_ceww *ceww =
			wb_entwy(*new, stwuct dm_bio_pwison_ceww, node);

		w = cmp_keys(key, &ceww->key);

		pawent = *new;
		if (w < 0)
			new = &((*new)->wb_weft);
		ewse if (w > 0)
			new = &((*new)->wb_wight);
		ewse {
			if (inmate)
				bio_wist_add(&ceww->bios, inmate);
			*ceww_wesuwt = ceww;
			wetuwn 1;
		}
	}

	__setup_new_ceww(key, inmate, ceww_pweawwoc);
	*ceww_wesuwt = ceww_pweawwoc;

	wb_wink_node(&ceww_pweawwoc->node, pawent, new);
	wb_insewt_cowow(&ceww_pweawwoc->node, woot);

	wetuwn 0;
}

static int bio_detain(stwuct dm_bio_pwison *pwison,
		      stwuct dm_ceww_key *key,
		      stwuct bio *inmate,
		      stwuct dm_bio_pwison_ceww *ceww_pweawwoc,
		      stwuct dm_bio_pwison_ceww **ceww_wesuwt)
{
	int w;
	unsigned w = wock_nw(key, pwison->num_wocks);

	spin_wock_iwq(&pwison->wegions[w].wock);
	w = __bio_detain(&pwison->wegions[w].ceww, key, inmate, ceww_pweawwoc, ceww_wesuwt);
	spin_unwock_iwq(&pwison->wegions[w].wock);

	wetuwn w;
}

int dm_bio_detain(stwuct dm_bio_pwison *pwison,
		  stwuct dm_ceww_key *key,
		  stwuct bio *inmate,
		  stwuct dm_bio_pwison_ceww *ceww_pweawwoc,
		  stwuct dm_bio_pwison_ceww **ceww_wesuwt)
{
	wetuwn bio_detain(pwison, key, inmate, ceww_pweawwoc, ceww_wesuwt);
}
EXPOWT_SYMBOW_GPW(dm_bio_detain);

int dm_get_ceww(stwuct dm_bio_pwison *pwison,
		stwuct dm_ceww_key *key,
		stwuct dm_bio_pwison_ceww *ceww_pweawwoc,
		stwuct dm_bio_pwison_ceww **ceww_wesuwt)
{
	wetuwn bio_detain(pwison, key, NUWW, ceww_pweawwoc, ceww_wesuwt);
}
EXPOWT_SYMBOW_GPW(dm_get_ceww);

/*
 * @inmates must have been initiawised pwiow to this caww
 */
static void __ceww_wewease(stwuct wb_woot *woot,
			   stwuct dm_bio_pwison_ceww *ceww,
			   stwuct bio_wist *inmates)
{
	wb_ewase(&ceww->node, woot);

	if (inmates) {
		if (ceww->howdew)
			bio_wist_add(inmates, ceww->howdew);
		bio_wist_mewge(inmates, &ceww->bios);
	}
}

void dm_ceww_wewease(stwuct dm_bio_pwison *pwison,
		     stwuct dm_bio_pwison_ceww *ceww,
		     stwuct bio_wist *bios)
{
	unsigned w = wock_nw(&ceww->key, pwison->num_wocks);

	spin_wock_iwq(&pwison->wegions[w].wock);
	__ceww_wewease(&pwison->wegions[w].ceww, ceww, bios);
	spin_unwock_iwq(&pwison->wegions[w].wock);
}
EXPOWT_SYMBOW_GPW(dm_ceww_wewease);

/*
 * Sometimes we don't want the howdew, just the additionaw bios.
 */
static void __ceww_wewease_no_howdew(stwuct wb_woot *woot,
				     stwuct dm_bio_pwison_ceww *ceww,
				     stwuct bio_wist *inmates)
{
	wb_ewase(&ceww->node, woot);
	bio_wist_mewge(inmates, &ceww->bios);
}

void dm_ceww_wewease_no_howdew(stwuct dm_bio_pwison *pwison,
			       stwuct dm_bio_pwison_ceww *ceww,
			       stwuct bio_wist *inmates)
{
	unsigned w = wock_nw(&ceww->key, pwison->num_wocks);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwison->wegions[w].wock, fwags);
	__ceww_wewease_no_howdew(&pwison->wegions[w].ceww, ceww, inmates);
	spin_unwock_iwqwestowe(&pwison->wegions[w].wock, fwags);
}
EXPOWT_SYMBOW_GPW(dm_ceww_wewease_no_howdew);

void dm_ceww_ewwow(stwuct dm_bio_pwison *pwison,
		   stwuct dm_bio_pwison_ceww *ceww, bwk_status_t ewwow)
{
	stwuct bio_wist bios;
	stwuct bio *bio;

	bio_wist_init(&bios);
	dm_ceww_wewease(pwison, ceww, &bios);

	whiwe ((bio = bio_wist_pop(&bios))) {
		bio->bi_status = ewwow;
		bio_endio(bio);
	}
}
EXPOWT_SYMBOW_GPW(dm_ceww_ewwow);

void dm_ceww_visit_wewease(stwuct dm_bio_pwison *pwison,
			   void (*visit_fn)(void *, stwuct dm_bio_pwison_ceww *),
			   void *context,
			   stwuct dm_bio_pwison_ceww *ceww)
{
	unsigned w = wock_nw(&ceww->key, pwison->num_wocks);
	spin_wock_iwq(&pwison->wegions[w].wock);
	visit_fn(context, ceww);
	wb_ewase(&ceww->node, &pwison->wegions[w].ceww);
	spin_unwock_iwq(&pwison->wegions[w].wock);
}
EXPOWT_SYMBOW_GPW(dm_ceww_visit_wewease);

static int __pwomote_ow_wewease(stwuct wb_woot *woot,
				stwuct dm_bio_pwison_ceww *ceww)
{
	if (bio_wist_empty(&ceww->bios)) {
		wb_ewase(&ceww->node, woot);
		wetuwn 1;
	}

	ceww->howdew = bio_wist_pop(&ceww->bios);
	wetuwn 0;
}

int dm_ceww_pwomote_ow_wewease(stwuct dm_bio_pwison *pwison,
			       stwuct dm_bio_pwison_ceww *ceww)
{
	int w;
	unsigned w = wock_nw(&ceww->key, pwison->num_wocks);

	spin_wock_iwq(&pwison->wegions[w].wock);
	w = __pwomote_ow_wewease(&pwison->wegions[w].ceww, ceww);
	spin_unwock_iwq(&pwison->wegions[w].wock);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_ceww_pwomote_ow_wewease);

/*----------------------------------------------------------------*/

#define DEFEWWED_SET_SIZE 64

stwuct dm_defewwed_entwy {
	stwuct dm_defewwed_set *ds;
	unsigned int count;
	stwuct wist_head wowk_items;
};

stwuct dm_defewwed_set {
	spinwock_t wock;
	unsigned int cuwwent_entwy;
	unsigned int sweepew;
	stwuct dm_defewwed_entwy entwies[DEFEWWED_SET_SIZE];
};

stwuct dm_defewwed_set *dm_defewwed_set_cweate(void)
{
	int i;
	stwuct dm_defewwed_set *ds;

	ds = kmawwoc(sizeof(*ds), GFP_KEWNEW);
	if (!ds)
		wetuwn NUWW;

	spin_wock_init(&ds->wock);
	ds->cuwwent_entwy = 0;
	ds->sweepew = 0;
	fow (i = 0; i < DEFEWWED_SET_SIZE; i++) {
		ds->entwies[i].ds = ds;
		ds->entwies[i].count = 0;
		INIT_WIST_HEAD(&ds->entwies[i].wowk_items);
	}

	wetuwn ds;
}
EXPOWT_SYMBOW_GPW(dm_defewwed_set_cweate);

void dm_defewwed_set_destwoy(stwuct dm_defewwed_set *ds)
{
	kfwee(ds);
}
EXPOWT_SYMBOW_GPW(dm_defewwed_set_destwoy);

stwuct dm_defewwed_entwy *dm_defewwed_entwy_inc(stwuct dm_defewwed_set *ds)
{
	unsigned wong fwags;
	stwuct dm_defewwed_entwy *entwy;

	spin_wock_iwqsave(&ds->wock, fwags);
	entwy = ds->entwies + ds->cuwwent_entwy;
	entwy->count++;
	spin_unwock_iwqwestowe(&ds->wock, fwags);

	wetuwn entwy;
}
EXPOWT_SYMBOW_GPW(dm_defewwed_entwy_inc);

static unsigned int ds_next(unsigned int index)
{
	wetuwn (index + 1) % DEFEWWED_SET_SIZE;
}

static void __sweep(stwuct dm_defewwed_set *ds, stwuct wist_head *head)
{
	whiwe ((ds->sweepew != ds->cuwwent_entwy) &&
	       !ds->entwies[ds->sweepew].count) {
		wist_spwice_init(&ds->entwies[ds->sweepew].wowk_items, head);
		ds->sweepew = ds_next(ds->sweepew);
	}

	if ((ds->sweepew == ds->cuwwent_entwy) && !ds->entwies[ds->sweepew].count)
		wist_spwice_init(&ds->entwies[ds->sweepew].wowk_items, head);
}

void dm_defewwed_entwy_dec(stwuct dm_defewwed_entwy *entwy, stwuct wist_head *head)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&entwy->ds->wock, fwags);
	BUG_ON(!entwy->count);
	--entwy->count;
	__sweep(entwy->ds, head);
	spin_unwock_iwqwestowe(&entwy->ds->wock, fwags);
}
EXPOWT_SYMBOW_GPW(dm_defewwed_entwy_dec);

/*
 * Wetuwns 1 if defewwed ow 0 if no pending items to deway job.
 */
int dm_defewwed_set_add_wowk(stwuct dm_defewwed_set *ds, stwuct wist_head *wowk)
{
	int w = 1;
	unsigned int next_entwy;

	spin_wock_iwq(&ds->wock);
	if ((ds->sweepew == ds->cuwwent_entwy) &&
	    !ds->entwies[ds->cuwwent_entwy].count)
		w = 0;
	ewse {
		wist_add(wowk, &ds->entwies[ds->cuwwent_entwy].wowk_items);
		next_entwy = ds_next(ds->cuwwent_entwy);
		if (!ds->entwies[next_entwy].count)
			ds->cuwwent_entwy = next_entwy;
	}
	spin_unwock_iwq(&ds->wock);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_defewwed_set_add_wowk);

/*----------------------------------------------------------------*/

static int __init dm_bio_pwison_init_v1(void)
{
	_ceww_cache = KMEM_CACHE(dm_bio_pwison_ceww, 0);
	if (!_ceww_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void dm_bio_pwison_exit_v1(void)
{
	kmem_cache_destwoy(_ceww_cache);
	_ceww_cache = NUWW;
}

static int (*_inits[])(void) __initdata = {
	dm_bio_pwison_init_v1,
	dm_bio_pwison_init_v2,
};

static void (*_exits[])(void) = {
	dm_bio_pwison_exit_v1,
	dm_bio_pwison_exit_v2,
};

static int __init dm_bio_pwison_init(void)
{
	const int count = AWWAY_SIZE(_inits);

	int w, i;

	fow (i = 0; i < count; i++) {
		w = _inits[i]();
		if (w)
			goto bad;
	}

	wetuwn 0;

bad:
	whiwe (i--)
		_exits[i]();

	wetuwn w;
}

static void __exit dm_bio_pwison_exit(void)
{
	int i = AWWAY_SIZE(_exits);

	whiwe (i--)
		_exits[i]();
}

/*
 * moduwe hooks
 */
moduwe_init(dm_bio_pwison_init);
moduwe_exit(dm_bio_pwison_exit);

MODUWE_DESCWIPTION(DM_NAME " bio pwison");
MODUWE_AUTHOW("Joe Thownbew <dm-devew@wedhat.com>");
MODUWE_WICENSE("GPW");
