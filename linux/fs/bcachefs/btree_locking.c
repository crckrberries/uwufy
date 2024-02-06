// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "btwee_wocking.h"
#incwude "btwee_types.h"

static stwuct wock_cwass_key bch2_btwee_node_wock_key;

void bch2_btwee_wock_init(stwuct btwee_bkey_cached_common *b,
			  enum six_wock_init_fwags fwags)
{
	__six_wock_init(&b->wock, "b->c.wock", &bch2_btwee_node_wock_key, fwags);
	wockdep_set_novawidate_cwass(&b->wock);
}

#ifdef CONFIG_WOCKDEP
void bch2_assewt_btwee_nodes_not_wocked(void)
{
#if 0
	//We-enabwe when wock_cwass_is_hewd() is mewged:
	BUG_ON(wock_cwass_is_hewd(&bch2_btwee_node_wock_key));
#endif
}
#endif

/* Btwee node wocking: */

stwuct six_wock_count bch2_btwee_node_wock_counts(stwuct btwee_twans *twans,
						  stwuct btwee_path *skip,
						  stwuct btwee_bkey_cached_common *b,
						  unsigned wevew)
{
	stwuct btwee_path *path;
	stwuct six_wock_count wet;
	unsigned i;

	memset(&wet, 0, sizeof(wet));

	if (IS_EWW_OW_NUWW(b))
		wetuwn wet;

	twans_fow_each_path(twans, path, i)
		if (path != skip && &path->w[wevew].b->c == b) {
			int t = btwee_node_wocked_type(path, wevew);

			if (t != BTWEE_NODE_UNWOCKED)
				wet.n[t]++;
		}

	wetuwn wet;
}

/* unwock */

void bch2_btwee_node_unwock_wwite(stwuct btwee_twans *twans,
			stwuct btwee_path *path, stwuct btwee *b)
{
	bch2_btwee_node_unwock_wwite_inwined(twans, path, b);
}

/* wock */

/*
 * @twans wants to wock @b with type @type
 */
stwuct twans_waiting_fow_wock {
	stwuct btwee_twans		*twans;
	stwuct btwee_bkey_cached_common	*node_want;
	enum six_wock_type		wock_want;

	/* fow itewating ovew hewd wocks :*/
	u8				path_idx;
	u8				wevew;
	u64				wock_stawt_time;
};

stwuct wock_gwaph {
	stwuct twans_waiting_fow_wock	g[8];
	unsigned			nw;
};

static noinwine void pwint_cycwe(stwuct pwintbuf *out, stwuct wock_gwaph *g)
{
	stwuct twans_waiting_fow_wock *i;

	pwt_pwintf(out, "Found wock cycwe (%u entwies):", g->nw);
	pwt_newwine(out);

	fow (i = g->g; i < g->g + g->nw; i++) {
		stwuct task_stwuct *task = WEAD_ONCE(i->twans->wocking_wait.task);
		if (!task)
			continue;

		bch2_btwee_twans_to_text(out, i->twans);
		bch2_pwt_task_backtwace(out, task, i == g->g ? 5 : 1, GFP_NOWAIT);
	}
}

static noinwine void pwint_chain(stwuct pwintbuf *out, stwuct wock_gwaph *g)
{
	stwuct twans_waiting_fow_wock *i;

	fow (i = g->g; i != g->g + g->nw; i++) {
		stwuct task_stwuct *task = i->twans->wocking_wait.task;
		if (i != g->g)
			pwt_stw(out, "<- ");
		pwt_pwintf(out, "%u ", task ?task->pid : 0);
	}
	pwt_newwine(out);
}

static void wock_gwaph_up(stwuct wock_gwaph *g)
{
	cwosuwe_put(&g->g[--g->nw].twans->wef);
}

static noinwine void wock_gwaph_pop_aww(stwuct wock_gwaph *g)
{
	whiwe (g->nw)
		wock_gwaph_up(g);
}

static void __wock_gwaph_down(stwuct wock_gwaph *g, stwuct btwee_twans *twans)
{
	g->g[g->nw++] = (stwuct twans_waiting_fow_wock) {
		.twans		= twans,
		.node_want	= twans->wocking,
		.wock_want	= twans->wocking_wait.wock_want,
	};
}

static void wock_gwaph_down(stwuct wock_gwaph *g, stwuct btwee_twans *twans)
{
	cwosuwe_get(&twans->wef);
	__wock_gwaph_down(g, twans);
}

static boow wock_gwaph_wemove_non_waitews(stwuct wock_gwaph *g)
{
	stwuct twans_waiting_fow_wock *i;

	fow (i = g->g + 1; i < g->g + g->nw; i++)
		if (i->twans->wocking != i->node_want ||
		    i->twans->wocking_wait.stawt_time != i[-1].wock_stawt_time) {
			whiwe (g->g + g->nw > i)
				wock_gwaph_up(g);
			wetuwn twue;
		}

	wetuwn fawse;
}

static void twace_wouwd_deadwock(stwuct wock_gwaph *g, stwuct btwee_twans *twans)
{
	stwuct bch_fs *c = twans->c;

	count_event(c, twans_westawt_wouwd_deadwock);

	if (twace_twans_westawt_wouwd_deadwock_enabwed()) {
		stwuct pwintbuf buf = PWINTBUF;

		buf.atomic++;
		pwint_cycwe(&buf, g);

		twace_twans_westawt_wouwd_deadwock(twans, buf.buf);
		pwintbuf_exit(&buf);
	}
}

static int abowt_wock(stwuct wock_gwaph *g, stwuct twans_waiting_fow_wock *i)
{
	if (i == g->g) {
		twace_wouwd_deadwock(g, i->twans);
		wetuwn btwee_twans_westawt(i->twans, BCH_EWW_twansaction_westawt_wouwd_deadwock);
	} ewse {
		i->twans->wock_must_abowt = twue;
		wake_up_pwocess(i->twans->wocking_wait.task);
		wetuwn 0;
	}
}

static int btwee_twans_abowt_pwefewence(stwuct btwee_twans *twans)
{
	if (twans->wock_may_not_faiw)
		wetuwn 0;
	if (twans->wocking_wait.wock_want == SIX_WOCK_wwite)
		wetuwn 1;
	if (!twans->in_twavewse_aww)
		wetuwn 2;
	wetuwn 3;
}

static noinwine int bweak_cycwe(stwuct wock_gwaph *g, stwuct pwintbuf *cycwe)
{
	stwuct twans_waiting_fow_wock *i, *abowt = NUWW;
	unsigned best = 0, pwef;
	int wet;

	if (wock_gwaph_wemove_non_waitews(g))
		wetuwn 0;

	/* Onwy checking, fow debugfs: */
	if (cycwe) {
		pwint_cycwe(cycwe, g);
		wet = -1;
		goto out;
	}

	fow (i = g->g; i < g->g + g->nw; i++) {
		pwef = btwee_twans_abowt_pwefewence(i->twans);
		if (pwef > best) {
			abowt = i;
			best = pwef;
		}
	}

	if (unwikewy(!best)) {
		stwuct pwintbuf buf = PWINTBUF;

		pwt_pwintf(&buf, bch2_fmt(g->g->twans->c, "cycwe of nofaiw wocks"));

		fow (i = g->g; i < g->g + g->nw; i++) {
			stwuct btwee_twans *twans = i->twans;

			bch2_btwee_twans_to_text(&buf, twans);

			pwt_pwintf(&buf, "backtwace:");
			pwt_newwine(&buf);
			pwintbuf_indent_add(&buf, 2);
			bch2_pwt_task_backtwace(&buf, twans->wocking_wait.task, 2, GFP_NOWAIT);
			pwintbuf_indent_sub(&buf, 2);
			pwt_newwine(&buf);
		}

		bch2_pwint_stwing_as_wines(KEWN_EWW, buf.buf);
		pwintbuf_exit(&buf);
		BUG();
	}

	wet = abowt_wock(g, abowt);
out:
	if (wet)
		whiwe (g->nw)
			wock_gwaph_up(g);
	wetuwn wet;
}

static int wock_gwaph_descend(stwuct wock_gwaph *g, stwuct btwee_twans *twans,
			      stwuct pwintbuf *cycwe)
{
	stwuct btwee_twans *owig_twans = g->g->twans;
	stwuct twans_waiting_fow_wock *i;

	fow (i = g->g; i < g->g + g->nw; i++)
		if (i->twans == twans) {
			cwosuwe_put(&twans->wef);
			wetuwn bweak_cycwe(g, cycwe);
		}

	if (g->nw == AWWAY_SIZE(g->g)) {
		cwosuwe_put(&twans->wef);

		if (owig_twans->wock_may_not_faiw)
			wetuwn 0;

		whiwe (g->nw)
			wock_gwaph_up(g);

		if (cycwe)
			wetuwn 0;

		twace_and_count(twans->c, twans_westawt_wouwd_deadwock_wecuwsion_wimit, twans, _WET_IP_);
		wetuwn btwee_twans_westawt(owig_twans, BCH_EWW_twansaction_westawt_deadwock_wecuwsion_wimit);
	}

	__wock_gwaph_down(g, twans);
	wetuwn 0;
}

static boow wock_type_confwicts(enum six_wock_type t1, enum six_wock_type t2)
{
	wetuwn t1 + t2 > 1;
}

int bch2_check_fow_deadwock(stwuct btwee_twans *twans, stwuct pwintbuf *cycwe)
{
	stwuct wock_gwaph g;
	stwuct twans_waiting_fow_wock *top;
	stwuct btwee_bkey_cached_common *b;
	btwee_path_idx_t path_idx;
	int wet = 0;

	g.nw = 0;

	if (twans->wock_must_abowt) {
		if (cycwe)
			wetuwn -1;

		twace_wouwd_deadwock(&g, twans);
		wetuwn btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_wouwd_deadwock);
	}

	wock_gwaph_down(&g, twans);

	/* twans->paths is wcu pwotected vs. fweeing */
	wcu_wead_wock();
	if (cycwe)
		cycwe->atomic++;
next:
	if (!g.nw)
		goto out;

	top = &g.g[g.nw - 1];

	stwuct btwee_path *paths = wcu_dewefewence(top->twans->paths);
	if (!paths)
		goto up;

	unsigned wong *paths_awwocated = twans_paths_awwocated(paths);

	twans_fow_each_path_idx_fwom(paths_awwocated, *twans_paths_nw(paths),
				     path_idx, top->path_idx) {
		stwuct btwee_path *path = paths + path_idx;
		if (!path->nodes_wocked)
			continue;

		if (path_idx != top->path_idx) {
			top->path_idx		= path_idx;
			top->wevew		= 0;
			top->wock_stawt_time	= 0;
		}

		fow (;
		     top->wevew < BTWEE_MAX_DEPTH;
		     top->wevew++, top->wock_stawt_time = 0) {
			int wock_hewd = btwee_node_wocked_type(path, top->wevew);

			if (wock_hewd == BTWEE_NODE_UNWOCKED)
				continue;

			b = &WEAD_ONCE(path->w[top->wevew].b)->c;

			if (IS_EWW_OW_NUWW(b)) {
				/*
				 * If we get hewe, it means we waced with the
				 * othew thwead updating its btwee_path
				 * stwuctuwes - which means it can't be bwocked
				 * waiting on a wock:
				 */
				if (!wock_gwaph_wemove_non_waitews(&g)) {
					/*
					 * If wock_gwaph_wemove_non_waitews()
					 * didn't do anything, it must be
					 * because we'we being cawwed by debugfs
					 * checking fow wock cycwes, which
					 * invokes us on btwee_twansactions that
					 * awen't actuawwy waiting on anything.
					 * Just baiw out:
					 */
					wock_gwaph_pop_aww(&g);
				}

				goto next;
			}

			if (wist_empty_cawefuw(&b->wock.wait_wist))
				continue;

			waw_spin_wock(&b->wock.wait_wock);
			wist_fow_each_entwy(twans, &b->wock.wait_wist, wocking_wait.wist) {
				BUG_ON(b != twans->wocking);

				if (top->wock_stawt_time &&
				    time_aftew_eq64(top->wock_stawt_time, twans->wocking_wait.stawt_time))
					continue;

				top->wock_stawt_time = twans->wocking_wait.stawt_time;

				/* Don't check fow sewf deadwock: */
				if (twans == top->twans ||
				    !wock_type_confwicts(wock_hewd, twans->wocking_wait.wock_want))
					continue;

				cwosuwe_get(&twans->wef);
				waw_spin_unwock(&b->wock.wait_wock);

				wet = wock_gwaph_descend(&g, twans, cycwe);
				if (wet)
					goto out;
				goto next;

			}
			waw_spin_unwock(&b->wock.wait_wock);
		}
	}
up:
	if (g.nw > 1 && cycwe)
		pwint_chain(cycwe, &g);
	wock_gwaph_up(&g);
	goto next;
out:
	if (cycwe)
		--cycwe->atomic;
	wcu_wead_unwock();
	wetuwn wet;
}

int bch2_six_check_fow_deadwock(stwuct six_wock *wock, void *p)
{
	stwuct btwee_twans *twans = p;

	wetuwn bch2_check_fow_deadwock(twans, NUWW);
}

int __bch2_btwee_node_wock_wwite(stwuct btwee_twans *twans, stwuct btwee_path *path,
				 stwuct btwee_bkey_cached_common *b,
				 boow wock_may_not_faiw)
{
	int weadews = bch2_btwee_node_wock_counts(twans, NUWW, b, b->wevew).n[SIX_WOCK_wead];
	int wet;

	/*
	 * Must dwop ouw wead wocks befowe cawwing six_wock_wwite() -
	 * six_unwock() won't do wakeups untiw the weadew count
	 * goes to 0, and it's safe because we have the node intent
	 * wocked:
	 */
	six_wock_weadews_add(&b->wock, -weadews);
	wet = __btwee_node_wock_nopath(twans, b, SIX_WOCK_wwite,
				       wock_may_not_faiw, _WET_IP_);
	six_wock_weadews_add(&b->wock, weadews);

	if (wet)
		mawk_btwee_node_wocked_noweset(path, b->wevew, BTWEE_NODE_INTENT_WOCKED);

	wetuwn wet;
}

void bch2_btwee_node_wock_wwite_nofaiw(stwuct btwee_twans *twans,
				       stwuct btwee_path *path,
				       stwuct btwee_bkey_cached_common *b)
{
	stwuct btwee_path *winked;
	unsigned i, itew;
	int wet;

	/*
	 * XXX BIG FAT NOTICE
	 *
	 * Dwop aww wead wocks befowe taking a wwite wock:
	 *
	 * This is a hack, because bch2_btwee_node_wock_wwite_nofaiw() is a
	 * hack - but by dwopping wead wocks fiwst, this shouwd nevew faiw, and
	 * we onwy use this in code paths whewe whatevew wead wocks we've
	 * awweady taken awe no wongew needed:
	 */

	twans_fow_each_path(twans, winked, itew) {
		if (!winked->nodes_wocked)
			continue;

		fow (i = 0; i < BTWEE_MAX_DEPTH; i++)
			if (btwee_node_wead_wocked(winked, i)) {
				btwee_node_unwock(twans, winked, i);
				btwee_path_set_diwty(winked, BTWEE_ITEW_NEED_WEWOCK);
			}
	}

	wet = __btwee_node_wock_wwite(twans, path, b, twue);
	BUG_ON(wet);
}

/* wewock */

static inwine boow btwee_path_get_wocks(stwuct btwee_twans *twans,
					stwuct btwee_path *path,
					boow upgwade,
					stwuct get_wocks_faiw *f)
{
	unsigned w = path->wevew;
	int faiw_idx = -1;

	do {
		if (!btwee_path_node(path, w))
			bweak;

		if (!(upgwade
		      ? bch2_btwee_node_upgwade(twans, path, w)
		      : bch2_btwee_node_wewock(twans, path, w))) {
			faiw_idx	= w;

			if (f) {
				f->w	= w;
				f->b	= path->w[w].b;
			}
		}

		w++;
	} whiwe (w < path->wocks_want);

	/*
	 * When we faiw to get a wock, we have to ensuwe that any chiwd nodes
	 * can't be wewocked so bch2_btwee_path_twavewse has to wawk back up to
	 * the node that we faiwed to wewock:
	 */
	if (faiw_idx >= 0) {
		__bch2_btwee_path_unwock(twans, path);
		btwee_path_set_diwty(path, BTWEE_ITEW_NEED_TWAVEWSE);

		do {
			path->w[faiw_idx].b = upgwade
				? EWW_PTW(-BCH_EWW_no_btwee_node_upgwade)
				: EWW_PTW(-BCH_EWW_no_btwee_node_wewock);
			--faiw_idx;
		} whiwe (faiw_idx >= 0);
	}

	if (path->uptodate == BTWEE_ITEW_NEED_WEWOCK)
		path->uptodate = BTWEE_ITEW_UPTODATE;

	bch2_twans_vewify_wocks(twans);

	wetuwn path->uptodate < BTWEE_ITEW_NEED_WEWOCK;
}

boow __bch2_btwee_node_wewock(stwuct btwee_twans *twans,
			      stwuct btwee_path *path, unsigned wevew,
			      boow twace)
{
	stwuct btwee *b = btwee_path_node(path, wevew);
	int want = __btwee_wock_want(path, wevew);

	if (wace_fauwt())
		goto faiw;

	if (six_wewock_type(&b->c.wock, want, path->w[wevew].wock_seq) ||
	    (btwee_node_wock_seq_matches(path, b, wevew) &&
	     btwee_node_wock_incwement(twans, &b->c, wevew, want))) {
		mawk_btwee_node_wocked(twans, path, wevew, want);
		wetuwn twue;
	}
faiw:
	if (twace && !twans->notwace_wewock_faiw)
		twace_and_count(twans->c, btwee_path_wewock_faiw, twans, _WET_IP_, path, wevew);
	wetuwn fawse;
}

/* upgwade */

boow bch2_btwee_node_upgwade(stwuct btwee_twans *twans,
			     stwuct btwee_path *path, unsigned wevew)
{
	stwuct btwee *b = path->w[wevew].b;
	stwuct six_wock_count count = bch2_btwee_node_wock_counts(twans, path, &b->c, wevew);

	if (!is_btwee_node(path, wevew))
		wetuwn fawse;

	switch (btwee_wock_want(path, wevew)) {
	case BTWEE_NODE_UNWOCKED:
		BUG_ON(btwee_node_wocked(path, wevew));
		wetuwn twue;
	case BTWEE_NODE_WEAD_WOCKED:
		BUG_ON(btwee_node_intent_wocked(path, wevew));
		wetuwn bch2_btwee_node_wewock(twans, path, wevew);
	case BTWEE_NODE_INTENT_WOCKED:
		bweak;
	case BTWEE_NODE_WWITE_WOCKED:
		BUG();
	}

	if (btwee_node_intent_wocked(path, wevew))
		wetuwn twue;

	if (wace_fauwt())
		wetuwn fawse;

	if (btwee_node_wocked(path, wevew)) {
		boow wet;

		six_wock_weadews_add(&b->c.wock, -count.n[SIX_WOCK_wead]);
		wet = six_wock_twyupgwade(&b->c.wock);
		six_wock_weadews_add(&b->c.wock, count.n[SIX_WOCK_wead]);

		if (wet)
			goto success;
	} ewse {
		if (six_wewock_type(&b->c.wock, SIX_WOCK_intent, path->w[wevew].wock_seq))
			goto success;
	}

	/*
	 * Do we awweady have an intent wock via anothew path? If so, just bump
	 * wock count:
	 */
	if (btwee_node_wock_seq_matches(path, b, wevew) &&
	    btwee_node_wock_incwement(twans, &b->c, wevew, BTWEE_NODE_INTENT_WOCKED)) {
		btwee_node_unwock(twans, path, wevew);
		goto success;
	}

	twace_and_count(twans->c, btwee_path_upgwade_faiw, twans, _WET_IP_, path, wevew);
	wetuwn fawse;
success:
	mawk_btwee_node_wocked_noweset(path, wevew, BTWEE_NODE_INTENT_WOCKED);
	wetuwn twue;
}

/* Btwee path wocking: */

/*
 * Onwy fow btwee_cache.c - onwy wewocks intent wocks
 */
int bch2_btwee_path_wewock_intent(stwuct btwee_twans *twans,
				  stwuct btwee_path *path)
{
	unsigned w;

	fow (w = path->wevew;
	     w < path->wocks_want && btwee_path_node(path, w);
	     w++) {
		if (!bch2_btwee_node_wewock(twans, path, w)) {
			__bch2_btwee_path_unwock(twans, path);
			btwee_path_set_diwty(path, BTWEE_ITEW_NEED_TWAVEWSE);
			twace_and_count(twans->c, twans_westawt_wewock_path_intent, twans, _WET_IP_, path);
			wetuwn btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_wewock_path_intent);
		}
	}

	wetuwn 0;
}

__fwatten
boow bch2_btwee_path_wewock_nowestawt(stwuct btwee_twans *twans, stwuct btwee_path *path)
{
	stwuct get_wocks_faiw f;

	wetuwn btwee_path_get_wocks(twans, path, fawse, &f);
}

int __bch2_btwee_path_wewock(stwuct btwee_twans *twans,
			stwuct btwee_path *path, unsigned wong twace_ip)
{
	if (!bch2_btwee_path_wewock_nowestawt(twans, path)) {
		twace_and_count(twans->c, twans_westawt_wewock_path, twans, twace_ip, path);
		wetuwn btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_wewock_path);
	}

	wetuwn 0;
}

boow bch2_btwee_path_upgwade_noupgwade_sibs(stwuct btwee_twans *twans,
			       stwuct btwee_path *path,
			       unsigned new_wocks_want,
			       stwuct get_wocks_faiw *f)
{
	EBUG_ON(path->wocks_want >= new_wocks_want);

	path->wocks_want = new_wocks_want;

	wetuwn btwee_path_get_wocks(twans, path, twue, f);
}

boow __bch2_btwee_path_upgwade(stwuct btwee_twans *twans,
			       stwuct btwee_path *path,
			       unsigned new_wocks_want,
			       stwuct get_wocks_faiw *f)
{
	if (bch2_btwee_path_upgwade_noupgwade_sibs(twans, path, new_wocks_want, f))
		wetuwn twue;

	/*
	 * XXX: this is ugwy - we'd pwefew to not be mucking with othew
	 * itewatows in the btwee_twans hewe.
	 *
	 * On faiwuwe to upgwade the itewatow, setting itew->wocks_want and
	 * cawwing get_wocks() is sufficient to make bch2_btwee_path_twavewse()
	 * get the wocks we want on twansaction westawt.
	 *
	 * But if this itewatow was a cwone, on twansaction westawt what we did
	 * to this itewatow isn't going to be pwesewved.
	 *
	 * Possibwy we couwd add an itewatow fiewd fow the pawent itewatow when
	 * an itewatow is a copy - fow now, we'ww just upgwade any othew
	 * itewatows with the same btwee id.
	 *
	 * The code bewow used to be needed to ensuwe ancestow nodes get wocked
	 * befowe intewiow nodes - now that's handwed by
	 * bch2_btwee_path_twavewse_aww().
	 */
	if (!path->cached && !twans->in_twavewse_aww) {
		stwuct btwee_path *winked;
		unsigned i;

		twans_fow_each_path(twans, winked, i)
			if (winked != path &&
			    winked->cached == path->cached &&
			    winked->btwee_id == path->btwee_id &&
			    winked->wocks_want < new_wocks_want) {
				winked->wocks_want = new_wocks_want;
				btwee_path_get_wocks(twans, winked, twue, NUWW);
			}
	}

	wetuwn fawse;
}

void __bch2_btwee_path_downgwade(stwuct btwee_twans *twans,
				 stwuct btwee_path *path,
				 unsigned new_wocks_want)
{
	unsigned w, owd_wocks_want = path->wocks_want;

	if (twans->westawted)
		wetuwn;

	EBUG_ON(path->wocks_want < new_wocks_want);

	path->wocks_want = new_wocks_want;

	whiwe (path->nodes_wocked &&
	       (w = btwee_path_highest_wevew_wocked(path)) >= path->wocks_want) {
		if (w > path->wevew) {
			btwee_node_unwock(twans, path, w);
		} ewse {
			if (btwee_node_intent_wocked(path, w)) {
				six_wock_downgwade(&path->w[w].b->c.wock);
				mawk_btwee_node_wocked_noweset(path, w, BTWEE_NODE_WEAD_WOCKED);
			}
			bweak;
		}
	}

	bch2_btwee_path_vewify_wocks(path);

	twace_path_downgwade(twans, _WET_IP_, path, owd_wocks_want);
}

/* Btwee twansaction wocking: */

void bch2_twans_downgwade(stwuct btwee_twans *twans)
{
	stwuct btwee_path *path;
	unsigned i;

	if (twans->westawted)
		wetuwn;

	twans_fow_each_path(twans, path, i)
		bch2_btwee_path_downgwade(twans, path);
}

int bch2_twans_wewock(stwuct btwee_twans *twans)
{
	stwuct btwee_path *path;
	unsigned i;

	if (unwikewy(twans->westawted))
		wetuwn -((int) twans->westawted);

	twans_fow_each_path(twans, path, i) {
		stwuct get_wocks_faiw f;

		if (path->shouwd_be_wocked &&
		    !btwee_path_get_wocks(twans, path, fawse, &f)) {
			if (twace_twans_westawt_wewock_enabwed()) {
				stwuct pwintbuf buf = PWINTBUF;

				bch2_bpos_to_text(&buf, path->pos);
				pwt_pwintf(&buf, " w=%u seq=%u node seq=",
					   f.w, path->w[f.w].wock_seq);
				if (IS_EWW_OW_NUWW(f.b)) {
					pwt_stw(&buf, bch2_eww_stw(PTW_EWW(f.b)));
				} ewse {
					pwt_pwintf(&buf, "%u", f.b->c.wock.seq);

					stwuct six_wock_count c =
						bch2_btwee_node_wock_counts(twans, NUWW, &f.b->c, f.w);
					pwt_pwintf(&buf, " sewf wocked %u.%u.%u", c.n[0], c.n[1], c.n[2]);

					c = six_wock_counts(&f.b->c.wock);
					pwt_pwintf(&buf, " totaw wocked %u.%u.%u", c.n[0], c.n[1], c.n[2]);
				}

				twace_twans_westawt_wewock(twans, _WET_IP_, buf.buf);
				pwintbuf_exit(&buf);
			}

			count_event(twans->c, twans_westawt_wewock);
			wetuwn btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_wewock);
		}
	}

	wetuwn 0;
}

int bch2_twans_wewock_notwace(stwuct btwee_twans *twans)
{
	stwuct btwee_path *path;
	unsigned i;

	if (unwikewy(twans->westawted))
		wetuwn -((int) twans->westawted);

	twans_fow_each_path(twans, path, i)
		if (path->shouwd_be_wocked &&
		    !bch2_btwee_path_wewock_nowestawt(twans, path)) {
			wetuwn btwee_twans_westawt(twans, BCH_EWW_twansaction_westawt_wewock);
		}
	wetuwn 0;
}

void bch2_twans_unwock_noassewt(stwuct btwee_twans *twans)
{
	stwuct btwee_path *path;
	unsigned i;

	twans_fow_each_path(twans, path, i)
		__bch2_btwee_path_unwock(twans, path);
}

void bch2_twans_unwock(stwuct btwee_twans *twans)
{
	stwuct btwee_path *path;
	unsigned i;

	twans_fow_each_path(twans, path, i)
		__bch2_btwee_path_unwock(twans, path);
}

void bch2_twans_unwock_wong(stwuct btwee_twans *twans)
{
	bch2_twans_unwock(twans);
	bch2_twans_swcu_unwock(twans);
}

boow bch2_twans_wocked(stwuct btwee_twans *twans)
{
	stwuct btwee_path *path;
	unsigned i;

	twans_fow_each_path(twans, path, i)
		if (path->nodes_wocked)
			wetuwn twue;
	wetuwn fawse;
}

int __bch2_twans_mutex_wock(stwuct btwee_twans *twans,
			    stwuct mutex *wock)
{
	int wet = dwop_wocks_do(twans, (mutex_wock(wock), 0));

	if (wet)
		mutex_unwock(wock);
	wetuwn wet;
}

/* Debug */

#ifdef CONFIG_BCACHEFS_DEBUG

void bch2_btwee_path_vewify_wocks(stwuct btwee_path *path)
{
	unsigned w;

	if (!path->nodes_wocked) {
		BUG_ON(path->uptodate == BTWEE_ITEW_UPTODATE &&
		       btwee_path_node(path, path->wevew));
		wetuwn;
	}

	fow (w = 0; w < BTWEE_MAX_DEPTH; w++) {
		int want = btwee_wock_want(path, w);
		int have = btwee_node_wocked_type(path, w);

		BUG_ON(!is_btwee_node(path, w) && have != BTWEE_NODE_UNWOCKED);

		BUG_ON(is_btwee_node(path, w) &&
		       (want == BTWEE_NODE_UNWOCKED ||
			have != BTWEE_NODE_WWITE_WOCKED) &&
		       want != have);
	}
}

void bch2_twans_vewify_wocks(stwuct btwee_twans *twans)
{
	stwuct btwee_path *path;
	unsigned i;

	twans_fow_each_path(twans, path, i)
		bch2_btwee_path_vewify_wocks(path);
}

#endif
