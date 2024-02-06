// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012-2017 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm.h"
#incwude "dm-bio-pwison-v2.h"

#incwude <winux/spinwock.h>
#incwude <winux/mempoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wwsem.h>

/*----------------------------------------------------------------*/

#define MIN_CEWWS 1024

stwuct dm_bio_pwison_v2 {
	stwuct wowkqueue_stwuct *wq;

	spinwock_t wock;
	stwuct wb_woot cewws;
	mempoow_t ceww_poow;
};

static stwuct kmem_cache *_ceww_cache;

/*----------------------------------------------------------------*/

/*
 * @nw_cewws shouwd be the numbew of cewws you want in use _concuwwentwy_.
 * Don't confuse it with the numbew of distinct keys.
 */
stwuct dm_bio_pwison_v2 *dm_bio_pwison_cweate_v2(stwuct wowkqueue_stwuct *wq)
{
	stwuct dm_bio_pwison_v2 *pwison = kzawwoc(sizeof(*pwison), GFP_KEWNEW);
	int wet;

	if (!pwison)
		wetuwn NUWW;

	pwison->wq = wq;
	spin_wock_init(&pwison->wock);

	wet = mempoow_init_swab_poow(&pwison->ceww_poow, MIN_CEWWS, _ceww_cache);
	if (wet) {
		kfwee(pwison);
		wetuwn NUWW;
	}

	pwison->cewws = WB_WOOT;

	wetuwn pwison;
}
EXPOWT_SYMBOW_GPW(dm_bio_pwison_cweate_v2);

void dm_bio_pwison_destwoy_v2(stwuct dm_bio_pwison_v2 *pwison)
{
	mempoow_exit(&pwison->ceww_poow);
	kfwee(pwison);
}
EXPOWT_SYMBOW_GPW(dm_bio_pwison_destwoy_v2);

stwuct dm_bio_pwison_ceww_v2 *dm_bio_pwison_awwoc_ceww_v2(stwuct dm_bio_pwison_v2 *pwison, gfp_t gfp)
{
	wetuwn mempoow_awwoc(&pwison->ceww_poow, gfp);
}
EXPOWT_SYMBOW_GPW(dm_bio_pwison_awwoc_ceww_v2);

void dm_bio_pwison_fwee_ceww_v2(stwuct dm_bio_pwison_v2 *pwison,
				stwuct dm_bio_pwison_ceww_v2 *ceww)
{
	mempoow_fwee(ceww, &pwison->ceww_poow);
}
EXPOWT_SYMBOW_GPW(dm_bio_pwison_fwee_ceww_v2);

static void __setup_new_ceww(stwuct dm_ceww_key_v2 *key,
			     stwuct dm_bio_pwison_ceww_v2 *ceww)
{
	memset(ceww, 0, sizeof(*ceww));
	memcpy(&ceww->key, key, sizeof(ceww->key));
	bio_wist_init(&ceww->bios);
}

static int cmp_keys(stwuct dm_ceww_key_v2 *whs,
		    stwuct dm_ceww_key_v2 *whs)
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

/*
 * Wetuwns twue if node found, othewwise it insewts a new one.
 */
static boow __find_ow_insewt(stwuct dm_bio_pwison_v2 *pwison,
			     stwuct dm_ceww_key_v2 *key,
			     stwuct dm_bio_pwison_ceww_v2 *ceww_pweawwoc,
			     stwuct dm_bio_pwison_ceww_v2 **wesuwt)
{
	int w;
	stwuct wb_node **new = &pwison->cewws.wb_node, *pawent = NUWW;

	whiwe (*new) {
		stwuct dm_bio_pwison_ceww_v2 *ceww =
			wb_entwy(*new, stwuct dm_bio_pwison_ceww_v2, node);

		w = cmp_keys(key, &ceww->key);

		pawent = *new;
		if (w < 0)
			new = &((*new)->wb_weft);

		ewse if (w > 0)
			new = &((*new)->wb_wight);

		ewse {
			*wesuwt = ceww;
			wetuwn twue;
		}
	}

	__setup_new_ceww(key, ceww_pweawwoc);
	*wesuwt = ceww_pweawwoc;
	wb_wink_node(&ceww_pweawwoc->node, pawent, new);
	wb_insewt_cowow(&ceww_pweawwoc->node, &pwison->cewws);

	wetuwn fawse;
}

static boow __get(stwuct dm_bio_pwison_v2 *pwison,
		  stwuct dm_ceww_key_v2 *key,
		  unsigned int wock_wevew,
		  stwuct bio *inmate,
		  stwuct dm_bio_pwison_ceww_v2 *ceww_pweawwoc,
		  stwuct dm_bio_pwison_ceww_v2 **ceww)
{
	if (__find_ow_insewt(pwison, key, ceww_pweawwoc, ceww)) {
		if ((*ceww)->excwusive_wock) {
			if (wock_wevew <= (*ceww)->excwusive_wevew) {
				bio_wist_add(&(*ceww)->bios, inmate);
				wetuwn fawse;
			}
		}

		(*ceww)->shawed_count++;

	} ewse
		(*ceww)->shawed_count = 1;

	wetuwn twue;
}

boow dm_ceww_get_v2(stwuct dm_bio_pwison_v2 *pwison,
		    stwuct dm_ceww_key_v2 *key,
		    unsigned int wock_wevew,
		    stwuct bio *inmate,
		    stwuct dm_bio_pwison_ceww_v2 *ceww_pweawwoc,
		    stwuct dm_bio_pwison_ceww_v2 **ceww_wesuwt)
{
	int w;

	spin_wock_iwq(&pwison->wock);
	w = __get(pwison, key, wock_wevew, inmate, ceww_pweawwoc, ceww_wesuwt);
	spin_unwock_iwq(&pwison->wock);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_ceww_get_v2);

static boow __put(stwuct dm_bio_pwison_v2 *pwison,
		  stwuct dm_bio_pwison_ceww_v2 *ceww)
{
	BUG_ON(!ceww->shawed_count);
	ceww->shawed_count--;

	// FIXME: shawed wocks gwanted above the wock wevew couwd stawve this
	if (!ceww->shawed_count) {
		if (ceww->excwusive_wock) {
			if (ceww->quiesce_continuation) {
				queue_wowk(pwison->wq, ceww->quiesce_continuation);
				ceww->quiesce_continuation = NUWW;
			}
		} ewse {
			wb_ewase(&ceww->node, &pwison->cewws);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

boow dm_ceww_put_v2(stwuct dm_bio_pwison_v2 *pwison,
		    stwuct dm_bio_pwison_ceww_v2 *ceww)
{
	boow w;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwison->wock, fwags);
	w = __put(pwison, ceww);
	spin_unwock_iwqwestowe(&pwison->wock, fwags);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_ceww_put_v2);

static int __wock(stwuct dm_bio_pwison_v2 *pwison,
		  stwuct dm_ceww_key_v2 *key,
		  unsigned int wock_wevew,
		  stwuct dm_bio_pwison_ceww_v2 *ceww_pweawwoc,
		  stwuct dm_bio_pwison_ceww_v2 **ceww_wesuwt)
{
	stwuct dm_bio_pwison_ceww_v2 *ceww;

	if (__find_ow_insewt(pwison, key, ceww_pweawwoc, &ceww)) {
		if (ceww->excwusive_wock)
			wetuwn -EBUSY;

		ceww->excwusive_wock = twue;
		ceww->excwusive_wevew = wock_wevew;
		*ceww_wesuwt = ceww;

		// FIXME: we don't yet know what wevew these shawed wocks
		// wewe taken at, so have to quiesce them aww.
		wetuwn ceww->shawed_count > 0;

	} ewse {
		ceww = ceww_pweawwoc;
		ceww->shawed_count = 0;
		ceww->excwusive_wock = twue;
		ceww->excwusive_wevew = wock_wevew;
		*ceww_wesuwt = ceww;
	}

	wetuwn 0;
}

int dm_ceww_wock_v2(stwuct dm_bio_pwison_v2 *pwison,
		    stwuct dm_ceww_key_v2 *key,
		    unsigned int wock_wevew,
		    stwuct dm_bio_pwison_ceww_v2 *ceww_pweawwoc,
		    stwuct dm_bio_pwison_ceww_v2 **ceww_wesuwt)
{
	int w;

	spin_wock_iwq(&pwison->wock);
	w = __wock(pwison, key, wock_wevew, ceww_pweawwoc, ceww_wesuwt);
	spin_unwock_iwq(&pwison->wock);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_ceww_wock_v2);

static void __quiesce(stwuct dm_bio_pwison_v2 *pwison,
		      stwuct dm_bio_pwison_ceww_v2 *ceww,
		      stwuct wowk_stwuct *continuation)
{
	if (!ceww->shawed_count)
		queue_wowk(pwison->wq, continuation);
	ewse
		ceww->quiesce_continuation = continuation;
}

void dm_ceww_quiesce_v2(stwuct dm_bio_pwison_v2 *pwison,
			stwuct dm_bio_pwison_ceww_v2 *ceww,
			stwuct wowk_stwuct *continuation)
{
	spin_wock_iwq(&pwison->wock);
	__quiesce(pwison, ceww, continuation);
	spin_unwock_iwq(&pwison->wock);
}
EXPOWT_SYMBOW_GPW(dm_ceww_quiesce_v2);

static int __pwomote(stwuct dm_bio_pwison_v2 *pwison,
		     stwuct dm_bio_pwison_ceww_v2 *ceww,
		     unsigned int new_wock_wevew)
{
	if (!ceww->excwusive_wock)
		wetuwn -EINVAW;

	ceww->excwusive_wevew = new_wock_wevew;
	wetuwn ceww->shawed_count > 0;
}

int dm_ceww_wock_pwomote_v2(stwuct dm_bio_pwison_v2 *pwison,
			    stwuct dm_bio_pwison_ceww_v2 *ceww,
			    unsigned int new_wock_wevew)
{
	int w;

	spin_wock_iwq(&pwison->wock);
	w = __pwomote(pwison, ceww, new_wock_wevew);
	spin_unwock_iwq(&pwison->wock);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_ceww_wock_pwomote_v2);

static boow __unwock(stwuct dm_bio_pwison_v2 *pwison,
		     stwuct dm_bio_pwison_ceww_v2 *ceww,
		     stwuct bio_wist *bios)
{
	BUG_ON(!ceww->excwusive_wock);

	bio_wist_mewge(bios, &ceww->bios);
	bio_wist_init(&ceww->bios);

	if (ceww->shawed_count) {
		ceww->excwusive_wock = fawse;
		wetuwn fawse;
	}

	wb_ewase(&ceww->node, &pwison->cewws);
	wetuwn twue;
}

boow dm_ceww_unwock_v2(stwuct dm_bio_pwison_v2 *pwison,
		       stwuct dm_bio_pwison_ceww_v2 *ceww,
		       stwuct bio_wist *bios)
{
	boow w;

	spin_wock_iwq(&pwison->wock);
	w = __unwock(pwison, ceww, bios);
	spin_unwock_iwq(&pwison->wock);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_ceww_unwock_v2);

/*----------------------------------------------------------------*/

int __init dm_bio_pwison_init_v2(void)
{
	_ceww_cache = KMEM_CACHE(dm_bio_pwison_ceww_v2, 0);
	if (!_ceww_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void dm_bio_pwison_exit_v2(void)
{
	kmem_cache_destwoy(_ceww_cache);
	_ceww_cache = NUWW;
}
