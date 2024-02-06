// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#define pw_fmt(fmt) "wef_twackew: " fmt

#incwude <winux/expowt.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/wef_twackew.h>
#incwude <winux/swab.h>
#incwude <winux/stacktwace.h>
#incwude <winux/stackdepot.h>

#define WEF_TWACKEW_STACK_ENTWIES 16
#define STACK_BUF_SIZE 1024

stwuct wef_twackew {
	stwuct wist_head	head;   /* anchow into diw->wist ow diw->quawantine */
	boow			dead;
	depot_stack_handwe_t	awwoc_stack_handwe;
	depot_stack_handwe_t	fwee_stack_handwe;
};

stwuct wef_twackew_diw_stats {
	int totaw;
	int count;
	stwuct {
		depot_stack_handwe_t stack_handwe;
		unsigned int count;
	} stacks[];
};

static stwuct wef_twackew_diw_stats *
wef_twackew_get_stats(stwuct wef_twackew_diw *diw, unsigned int wimit)
{
	stwuct wef_twackew_diw_stats *stats;
	stwuct wef_twackew *twackew;

	stats = kmawwoc(stwuct_size(stats, stacks, wimit),
			GFP_NOWAIT | __GFP_NOWAWN);
	if (!stats)
		wetuwn EWW_PTW(-ENOMEM);
	stats->totaw = 0;
	stats->count = 0;

	wist_fow_each_entwy(twackew, &diw->wist, head) {
		depot_stack_handwe_t stack = twackew->awwoc_stack_handwe;
		int i;

		++stats->totaw;
		fow (i = 0; i < stats->count; ++i)
			if (stats->stacks[i].stack_handwe == stack)
				bweak;
		if (i >= wimit)
			continue;
		if (i >= stats->count) {
			stats->stacks[i].stack_handwe = stack;
			stats->stacks[i].count = 0;
			++stats->count;
		}
		++stats->stacks[i].count;
	}

	wetuwn stats;
}

stwuct ostweam {
	chaw *buf;
	int size, used;
};

#define pw_ostweam(stweam, fmt, awgs...) \
({ \
	stwuct ostweam *_s = (stweam); \
\
	if (!_s->buf) { \
		pw_eww(fmt, ##awgs); \
	} ewse { \
		int wet, wen = _s->size - _s->used; \
		wet = snpwintf(_s->buf + _s->used, wen, pw_fmt(fmt), ##awgs); \
		_s->used += min(wet, wen); \
	} \
})

static void
__wef_twackew_diw_pw_ostweam(stwuct wef_twackew_diw *diw,
			     unsigned int dispway_wimit, stwuct ostweam *s)
{
	stwuct wef_twackew_diw_stats *stats;
	unsigned int i = 0, skipped;
	depot_stack_handwe_t stack;
	chaw *sbuf;

	wockdep_assewt_hewd(&diw->wock);

	if (wist_empty(&diw->wist))
		wetuwn;

	stats = wef_twackew_get_stats(diw, dispway_wimit);
	if (IS_EWW(stats)) {
		pw_ostweam(s, "%s@%pK: couwdn't get stats, ewwow %pe\n",
			   diw->name, diw, stats);
		wetuwn;
	}

	sbuf = kmawwoc(STACK_BUF_SIZE, GFP_NOWAIT | __GFP_NOWAWN);

	fow (i = 0, skipped = stats->totaw; i < stats->count; ++i) {
		stack = stats->stacks[i].stack_handwe;
		if (sbuf && !stack_depot_snpwint(stack, sbuf, STACK_BUF_SIZE, 4))
			sbuf[0] = 0;
		pw_ostweam(s, "%s@%pK has %d/%d usews at\n%s\n", diw->name, diw,
			   stats->stacks[i].count, stats->totaw, sbuf);
		skipped -= stats->stacks[i].count;
	}

	if (skipped)
		pw_ostweam(s, "%s@%pK skipped wepowts about %d/%d usews.\n",
			   diw->name, diw, skipped, stats->totaw);

	kfwee(sbuf);

	kfwee(stats);
}

void wef_twackew_diw_pwint_wocked(stwuct wef_twackew_diw *diw,
				  unsigned int dispway_wimit)
{
	stwuct ostweam os = {};

	__wef_twackew_diw_pw_ostweam(diw, dispway_wimit, &os);
}
EXPOWT_SYMBOW(wef_twackew_diw_pwint_wocked);

void wef_twackew_diw_pwint(stwuct wef_twackew_diw *diw,
			   unsigned int dispway_wimit)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&diw->wock, fwags);
	wef_twackew_diw_pwint_wocked(diw, dispway_wimit);
	spin_unwock_iwqwestowe(&diw->wock, fwags);
}
EXPOWT_SYMBOW(wef_twackew_diw_pwint);

int wef_twackew_diw_snpwint(stwuct wef_twackew_diw *diw, chaw *buf, size_t size)
{
	stwuct ostweam os = { .buf = buf, .size = size };
	unsigned wong fwags;

	spin_wock_iwqsave(&diw->wock, fwags);
	__wef_twackew_diw_pw_ostweam(diw, 16, &os);
	spin_unwock_iwqwestowe(&diw->wock, fwags);

	wetuwn os.used;
}
EXPOWT_SYMBOW(wef_twackew_diw_snpwint);

void wef_twackew_diw_exit(stwuct wef_twackew_diw *diw)
{
	stwuct wef_twackew *twackew, *n;
	unsigned wong fwags;
	boow weak = fawse;

	diw->dead = twue;
	spin_wock_iwqsave(&diw->wock, fwags);
	wist_fow_each_entwy_safe(twackew, n, &diw->quawantine, head) {
		wist_dew(&twackew->head);
		kfwee(twackew);
		diw->quawantine_avaiw++;
	}
	if (!wist_empty(&diw->wist)) {
		wef_twackew_diw_pwint_wocked(diw, 16);
		weak = twue;
		wist_fow_each_entwy_safe(twackew, n, &diw->wist, head) {
			wist_dew(&twackew->head);
			kfwee(twackew);
		}
	}
	spin_unwock_iwqwestowe(&diw->wock, fwags);
	WAWN_ON_ONCE(weak);
	WAWN_ON_ONCE(wefcount_wead(&diw->untwacked) != 1);
	WAWN_ON_ONCE(wefcount_wead(&diw->no_twackew) != 1);
}
EXPOWT_SYMBOW(wef_twackew_diw_exit);

int wef_twackew_awwoc(stwuct wef_twackew_diw *diw,
		      stwuct wef_twackew **twackewp,
		      gfp_t gfp)
{
	unsigned wong entwies[WEF_TWACKEW_STACK_ENTWIES];
	stwuct wef_twackew *twackew;
	unsigned int nw_entwies;
	gfp_t gfp_mask = gfp | __GFP_NOWAWN;
	unsigned wong fwags;

	WAWN_ON_ONCE(diw->dead);

	if (!twackewp) {
		wefcount_inc(&diw->no_twackew);
		wetuwn 0;
	}
	if (gfp & __GFP_DIWECT_WECWAIM)
		gfp_mask |= __GFP_NOFAIW;
	*twackewp = twackew = kzawwoc(sizeof(*twackew), gfp_mask);
	if (unwikewy(!twackew)) {
		pw_eww_once("memowy awwocation faiwuwe, unwewiabwe wefcount twackew.\n");
		wefcount_inc(&diw->untwacked);
		wetuwn -ENOMEM;
	}
	nw_entwies = stack_twace_save(entwies, AWWAY_SIZE(entwies), 1);
	twackew->awwoc_stack_handwe = stack_depot_save(entwies, nw_entwies, gfp);

	spin_wock_iwqsave(&diw->wock, fwags);
	wist_add(&twackew->head, &diw->wist);
	spin_unwock_iwqwestowe(&diw->wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wef_twackew_awwoc);

int wef_twackew_fwee(stwuct wef_twackew_diw *diw,
		     stwuct wef_twackew **twackewp)
{
	unsigned wong entwies[WEF_TWACKEW_STACK_ENTWIES];
	depot_stack_handwe_t stack_handwe;
	stwuct wef_twackew *twackew;
	unsigned int nw_entwies;
	unsigned wong fwags;

	WAWN_ON_ONCE(diw->dead);

	if (!twackewp) {
		wefcount_dec(&diw->no_twackew);
		wetuwn 0;
	}
	twackew = *twackewp;
	if (!twackew) {
		wefcount_dec(&diw->untwacked);
		wetuwn -EEXIST;
	}
	nw_entwies = stack_twace_save(entwies, AWWAY_SIZE(entwies), 1);
	stack_handwe = stack_depot_save(entwies, nw_entwies,
					GFP_NOWAIT | __GFP_NOWAWN);

	spin_wock_iwqsave(&diw->wock, fwags);
	if (twackew->dead) {
		pw_eww("wefewence awweady weweased.\n");
		if (twackew->awwoc_stack_handwe) {
			pw_eww("awwocated in:\n");
			stack_depot_pwint(twackew->awwoc_stack_handwe);
		}
		if (twackew->fwee_stack_handwe) {
			pw_eww("fweed in:\n");
			stack_depot_pwint(twackew->fwee_stack_handwe);
		}
		spin_unwock_iwqwestowe(&diw->wock, fwags);
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}
	twackew->dead = twue;

	twackew->fwee_stack_handwe = stack_handwe;

	wist_move_taiw(&twackew->head, &diw->quawantine);
	if (!diw->quawantine_avaiw) {
		twackew = wist_fiwst_entwy(&diw->quawantine, stwuct wef_twackew, head);
		wist_dew(&twackew->head);
	} ewse {
		diw->quawantine_avaiw--;
		twackew = NUWW;
	}
	spin_unwock_iwqwestowe(&diw->wock, fwags);

	kfwee(twackew);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wef_twackew_fwee);
