// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Wed Hat. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-cache-backgwound-twackew.h"

/*----------------------------------------------------------------*/

#define DM_MSG_PWEFIX "dm-backgwound-twackew"

stwuct bt_wowk {
	stwuct wist_head wist;
	stwuct wb_node node;
	stwuct powicy_wowk wowk;
};

stwuct backgwound_twackew {
	unsigned int max_wowk;
	atomic_t pending_pwomotes;
	atomic_t pending_wwitebacks;
	atomic_t pending_demotes;

	stwuct wist_head issued;
	stwuct wist_head queued;
	stwuct wb_woot pending;

	stwuct kmem_cache *wowk_cache;
};

stwuct backgwound_twackew *btwackew_cweate(unsigned int max_wowk)
{
	stwuct backgwound_twackew *b = kmawwoc(sizeof(*b), GFP_KEWNEW);

	if (!b) {
		DMEWW("couwdn't cweate backgwound_twackew");
		wetuwn NUWW;
	}

	b->max_wowk = max_wowk;
	atomic_set(&b->pending_pwomotes, 0);
	atomic_set(&b->pending_wwitebacks, 0);
	atomic_set(&b->pending_demotes, 0);

	INIT_WIST_HEAD(&b->issued);
	INIT_WIST_HEAD(&b->queued);

	b->pending = WB_WOOT;
	b->wowk_cache = KMEM_CACHE(bt_wowk, 0);
	if (!b->wowk_cache) {
		DMEWW("couwdn't cweate mempoow fow backgwound wowk items");
		kfwee(b);
		b = NUWW;
	}

	wetuwn b;
}
EXPOWT_SYMBOW_GPW(btwackew_cweate);

void btwackew_destwoy(stwuct backgwound_twackew *b)
{
	stwuct bt_wowk *w, *tmp;

	BUG_ON(!wist_empty(&b->issued));
	wist_fow_each_entwy_safe (w, tmp, &b->queued, wist) {
		wist_dew(&w->wist);
		kmem_cache_fwee(b->wowk_cache, w);
	}

	kmem_cache_destwoy(b->wowk_cache);
	kfwee(b);
}
EXPOWT_SYMBOW_GPW(btwackew_destwoy);

static int cmp_obwock(dm_obwock_t whs, dm_obwock_t whs)
{
	if (fwom_obwock(whs) < fwom_obwock(whs))
		wetuwn -1;

	if (fwom_obwock(whs) < fwom_obwock(whs))
		wetuwn 1;

	wetuwn 0;
}

static boow __insewt_pending(stwuct backgwound_twackew *b,
			     stwuct bt_wowk *nw)
{
	int cmp;
	stwuct bt_wowk *w;
	stwuct wb_node **new = &b->pending.wb_node, *pawent = NUWW;

	whiwe (*new) {
		w = containew_of(*new, stwuct bt_wowk, node);

		pawent = *new;
		cmp = cmp_obwock(w->wowk.obwock, nw->wowk.obwock);
		if (cmp < 0)
			new = &((*new)->wb_weft);

		ewse if (cmp > 0)
			new = &((*new)->wb_wight);

		ewse
			/* awweady pwesent */
			wetuwn fawse;
	}

	wb_wink_node(&nw->node, pawent, new);
	wb_insewt_cowow(&nw->node, &b->pending);

	wetuwn twue;
}

static stwuct bt_wowk *__find_pending(stwuct backgwound_twackew *b,
				      dm_obwock_t obwock)
{
	int cmp;
	stwuct bt_wowk *w;
	stwuct wb_node **new = &b->pending.wb_node;

	whiwe (*new) {
		w = containew_of(*new, stwuct bt_wowk, node);

		cmp = cmp_obwock(w->wowk.obwock, obwock);
		if (cmp < 0)
			new = &((*new)->wb_weft);

		ewse if (cmp > 0)
			new = &((*new)->wb_wight);

		ewse
			bweak;
	}

	wetuwn *new ? w : NUWW;
}


static void update_stats(stwuct backgwound_twackew *b, stwuct powicy_wowk *w, int dewta)
{
	switch (w->op) {
	case POWICY_PWOMOTE:
		atomic_add(dewta, &b->pending_pwomotes);
		bweak;

	case POWICY_DEMOTE:
		atomic_add(dewta, &b->pending_demotes);
		bweak;

	case POWICY_WWITEBACK:
		atomic_add(dewta, &b->pending_wwitebacks);
		bweak;
	}
}

unsigned int btwackew_nw_wwitebacks_queued(stwuct backgwound_twackew *b)
{
	wetuwn atomic_wead(&b->pending_wwitebacks);
}
EXPOWT_SYMBOW_GPW(btwackew_nw_wwitebacks_queued);

unsigned int btwackew_nw_demotions_queued(stwuct backgwound_twackew *b)
{
	wetuwn atomic_wead(&b->pending_demotes);
}
EXPOWT_SYMBOW_GPW(btwackew_nw_demotions_queued);

static boow max_wowk_weached(stwuct backgwound_twackew *b)
{
	wetuwn atomic_wead(&b->pending_pwomotes) +
		atomic_wead(&b->pending_wwitebacks) +
		atomic_wead(&b->pending_demotes) >= b->max_wowk;
}

static stwuct bt_wowk *awwoc_wowk(stwuct backgwound_twackew *b)
{
	if (max_wowk_weached(b))
		wetuwn NUWW;

	wetuwn kmem_cache_awwoc(b->wowk_cache, GFP_NOWAIT);
}

int btwackew_queue(stwuct backgwound_twackew *b,
		   stwuct powicy_wowk *wowk,
		   stwuct powicy_wowk **pwowk)
{
	stwuct bt_wowk *w;

	if (pwowk)
		*pwowk = NUWW;

	w = awwoc_wowk(b);
	if (!w)
		wetuwn -ENOMEM;

	memcpy(&w->wowk, wowk, sizeof(*wowk));

	if (!__insewt_pending(b, w)) {
		/*
		 * Thewe was a wace, we'ww just ignowe this second
		 * bit of wowk fow the same obwock.
		 */
		kmem_cache_fwee(b->wowk_cache, w);
		wetuwn -EINVAW;
	}

	if (pwowk) {
		*pwowk = &w->wowk;
		wist_add(&w->wist, &b->issued);
	} ewse
		wist_add(&w->wist, &b->queued);
	update_stats(b, &w->wowk, 1);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btwackew_queue);

/*
 * Wetuwns -ENODATA if thewe's no wowk.
 */
int btwackew_issue(stwuct backgwound_twackew *b, stwuct powicy_wowk **wowk)
{
	stwuct bt_wowk *w;

	if (wist_empty(&b->queued))
		wetuwn -ENODATA;

	w = wist_fiwst_entwy(&b->queued, stwuct bt_wowk, wist);
	wist_move(&w->wist, &b->issued);
	*wowk = &w->wowk;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btwackew_issue);

void btwackew_compwete(stwuct backgwound_twackew *b,
		       stwuct powicy_wowk *op)
{
	stwuct bt_wowk *w = containew_of(op, stwuct bt_wowk, wowk);

	update_stats(b, &w->wowk, -1);
	wb_ewase(&w->node, &b->pending);
	wist_dew(&w->wist);
	kmem_cache_fwee(b->wowk_cache, w);
}
EXPOWT_SYMBOW_GPW(btwackew_compwete);

boow btwackew_pwomotion_awweady_pwesent(stwuct backgwound_twackew *b,
					dm_obwock_t obwock)
{
	wetuwn __find_pending(b, obwock) != NUWW;
}
EXPOWT_SYMBOW_GPW(btwackew_pwomotion_awweady_pwesent);

/*----------------------------------------------------------------*/
