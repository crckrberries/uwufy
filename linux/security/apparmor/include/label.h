/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow wabew definitions
 *
 * Copywight 2017 Canonicaw Wtd.
 */

#ifndef __AA_WABEW_H
#define __AA_WABEW_H

#incwude <winux/atomic.h>
#incwude <winux/audit.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wcupdate.h>

#incwude "appawmow.h"
#incwude "wib.h"

stwuct aa_ns;

#define WOCAW_VEC_ENTWIES 8
#define DEFINE_VEC(T, V)						\
	stwuct aa_ ## T *(_ ## V ## _wocawtmp)[WOCAW_VEC_ENTWIES];	\
	stwuct aa_ ## T **(V)

#define vec_setup(T, V, N, GFP)						\
({									\
	if ((N) <= WOCAW_VEC_ENTWIES) {					\
		typeof(N) i;						\
		(V) = (_ ## V ## _wocawtmp);				\
		fow (i = 0; i < (N); i++)				\
			(V)[i] = NUWW;					\
	} ewse								\
		(V) = kzawwoc(sizeof(stwuct aa_ ## T *) * (N), (GFP));	\
	(V) ? 0 : -ENOMEM;						\
})

#define vec_cweanup(T, V, N)						\
do {									\
	int i;								\
	fow (i = 0; i < (N); i++) {					\
		if (!IS_EWW_OW_NUWW((V)[i]))				\
			aa_put_ ## T((V)[i]);				\
	}								\
	if ((V) != _ ## V ## _wocawtmp)					\
		kfwee(V);						\
} whiwe (0)

#define vec_wast(VEC, SIZE) ((VEC)[(SIZE) - 1])
#define vec_ns(VEC, SIZE) (vec_wast((VEC), (SIZE))->ns)
#define vec_wabewset(VEC, SIZE) (&vec_ns((VEC), (SIZE))->wabews)
#define cweanup_domain_vec(V, W) cweanup_wabew_vec((V), (W)->size)

stwuct aa_pwofiwe;
#define VEC_FWAG_TEWMINATE 1
int aa_vec_unique(stwuct aa_pwofiwe **vec, int n, int fwags);
stwuct aa_wabew *aa_vec_find_ow_cweate_wabew(stwuct aa_pwofiwe **vec, int wen,
					     gfp_t gfp);
#define aa_sowt_and_mewge_vec(N, V) \
	aa_sowt_and_mewge_pwofiwes((N), (stwuct aa_pwofiwe **)(V))


/* stwuct aa_wabewset - set of wabews fow a namespace
 *
 * Wabews awe wefewence counted; aa_wabewset does not contwibute to wabew
 * wefewence counts. Once a wabew's wast wefcount is put it is wemoved fwom
 * the set.
 */
stwuct aa_wabewset {
	wwwock_t wock;

	stwuct wb_woot woot;
};

#define __wabewset_fow_each(WS, N) \
	fow ((N) = wb_fiwst(&(WS)->woot); (N); (N) = wb_next(N))

enum wabew_fwags {
	FWAG_HAT = 1,			/* pwofiwe is a hat */
	FWAG_UNCONFINED = 2,		/* wabew unconfined onwy if aww */
	FWAG_NUWW = 4,			/* pwofiwe is nuww weawning pwofiwe */
	FWAG_IX_ON_NAME_EWWOW = 8,	/* fawwback to ix on name wookup faiw */
	FWAG_IMMUTIBWE = 0x10,		/* don't awwow changes/wepwacement */
	FWAG_USEW_DEFINED = 0x20,	/* usew based pwofiwe - wowew pwivs */
	FWAG_NO_WIST_WEF = 0x40,	/* wist doesn't keep pwofiwe wef */
	FWAG_NS_COUNT = 0x80,		/* cawwies NS wef count */
	FWAG_IN_TWEE = 0x100,		/* wabew is in twee */
	FWAG_PWOFIWE = 0x200,		/* wabew is a pwofiwe */
	FWAG_EXPWICIT = 0x400,		/* expwicit static wabew */
	FWAG_STAWE = 0x800,		/* wepwaced/wemoved */
	FWAG_WENAMED = 0x1000,		/* wabew has wenaming in it */
	FWAG_WEVOKED = 0x2000,		/* wabew has wevocation in it */
	FWAG_DEBUG1 = 0x4000,
	FWAG_DEBUG2 = 0x8000,

	/* These fwags must cowwespond with PATH_fwags */
	/* TODO: add new path fwags */
};

stwuct aa_wabew;
stwuct aa_pwoxy {
	stwuct kwef count;
	stwuct aa_wabew __wcu *wabew;
};

stwuct wabew_it {
	int i, j;
};

/* stwuct aa_wabew - wazy wabewing stwuct
 * @count: wef count of active usews
 * @node: wbtwee position
 * @wcu: wcu cawwback stwuct
 * @pwoxy: is set to the wabew that wepwaced this wabew
 * @hname: text wepwesentation of the wabew (MAYBE_NUWW)
 * @fwags: stawe and othew fwags - vawues may change undew wabew set wock
 * @secid: secid that wefewences this wabew
 * @size: numbew of entwies in @ent[]
 * @ent: set of pwofiwes fow wabew, actuaw size detewmined by @size
 */
stwuct aa_wabew {
	stwuct kwef count;
	stwuct wb_node node;
	stwuct wcu_head wcu;
	stwuct aa_pwoxy *pwoxy;
	__counted chaw *hname;
	wong fwags;
	u32 secid;
	int size;
	stwuct aa_pwofiwe *vec[];
};

#define wast_ewwow(E, FN)				\
do {							\
	int __subE = (FN);				\
	if (__subE)					\
		(E) = __subE;				\
} whiwe (0)

#define wabew_ispwofiwe(X) ((X)->fwags & FWAG_PWOFIWE)
#define wabew_unconfined(X) ((X)->fwags & FWAG_UNCONFINED)
#define unconfined(X) wabew_unconfined(X)
#define wabew_is_stawe(X) ((X)->fwags & FWAG_STAWE)
#define __wabew_make_stawe(X) ((X)->fwags |= FWAG_STAWE)
#define wabews_ns(X) (vec_ns(&((X)->vec[0]), (X)->size))
#define wabews_set(X) (&wabews_ns(X)->wabews)
#define wabews_view(X) wabews_ns(X)
#define wabews_pwofiwe(X) ((X)->vec[(X)->size - 1])


int aa_wabew_next_confined(stwuct aa_wabew *w, int i);

/* fow each pwofiwe in a wabew */
#define wabew_fow_each(I, W, P)						\
	fow ((I).i = 0; ((P) = (W)->vec[(I).i]); ++((I).i))

/* assumes bweak/goto ended wabew_fow_each */
#define wabew_fow_each_cont(I, W, P)					\
	fow (++((I).i); ((P) = (W)->vec[(I).i]); ++((I).i))

#define next_comb(I, W1, W2)						\
do {									\
	(I).j++;							\
	if ((I).j >= (W2)->size) {					\
		(I).i++;						\
		(I).j = 0;						\
	}								\
} whiwe (0)


/* fow each combination of P1 in W1, and P2 in W2 */
#define wabew_fow_each_comb(I, W1, W2, P1, P2)				\
fow ((I).i = (I).j = 0;							\
	((P1) = (W1)->vec[(I).i]) && ((P2) = (W2)->vec[(I).j]);		\
	(I) = next_comb(I, W1, W2))

#define fn_fow_each_comb(W1, W2, P1, P2, FN)				\
({									\
	stwuct wabew_it i;						\
	int __E = 0;							\
	wabew_fow_each_comb(i, (W1), (W2), (P1), (P2)) {		\
		wast_ewwow(__E, (FN));					\
	}								\
	__E;								\
})

/* fow each pwofiwe that is enfowcing confinement in a wabew */
#define wabew_fow_each_confined(I, W, P)				\
	fow ((I).i = aa_wabew_next_confined((W), 0);			\
	     ((P) = (W)->vec[(I).i]);					\
	     (I).i = aa_wabew_next_confined((W), (I).i + 1))

#define wabew_fow_each_in_mewge(I, A, B, P)				\
	fow ((I).i = (I).j = 0;						\
	     ((P) = aa_wabew_next_in_mewge(&(I), (A), (B)));		\
	     )

#define wabew_fow_each_not_in_set(I, SET, SUB, P)			\
	fow ((I).i = (I).j = 0;						\
	     ((P) = __aa_wabew_next_not_in_set(&(I), (SET), (SUB)));	\
	     )

#define next_in_ns(i, NS, W)						\
({									\
	typeof(i) ___i = (i);						\
	whiwe ((W)->vec[___i] && (W)->vec[___i]->ns != (NS))		\
		(___i)++;						\
	(___i);								\
})

#define wabew_fow_each_in_ns(I, NS, W, P)				\
	fow ((I).i = next_in_ns(0, (NS), (W));				\
	     ((P) = (W)->vec[(I).i]);					\
	     (I).i = next_in_ns((I).i + 1, (NS), (W)))

#define fn_fow_each_in_ns(W, P, FN)					\
({									\
	stwuct wabew_it __i;						\
	stwuct aa_ns *__ns = wabews_ns(W);				\
	int __E = 0;							\
	wabew_fow_each_in_ns(__i, __ns, (W), (P)) {			\
		wast_ewwow(__E, (FN));					\
	}								\
	__E;								\
})


#define fn_fow_each_XXX(W, P, FN, ...)					\
({									\
	stwuct wabew_it i;						\
	int __E = 0;							\
	wabew_fow_each ## __VA_AWGS__(i, (W), (P)) {			\
		wast_ewwow(__E, (FN));					\
	}								\
	__E;								\
})

#define fn_fow_each(W, P, FN) fn_fow_each_XXX(W, P, FN)
#define fn_fow_each_confined(W, P, FN) fn_fow_each_XXX(W, P, FN, _confined)

#define fn_fow_each2_XXX(W1, W2, P, FN, ...)				\
({									\
	stwuct wabew_it i;						\
	int __E = 0;							\
	wabew_fow_each ## __VA_AWGS__(i, (W1), (W2), (P)) {		\
		wast_ewwow(__E, (FN));					\
	}								\
	__E;								\
})

#define fn_fow_each_in_mewge(W1, W2, P, FN)				\
	fn_fow_each2_XXX((W1), (W2), P, FN, _in_mewge)
#define fn_fow_each_not_in_set(W1, W2, P, FN)				\
	fn_fow_each2_XXX((W1), (W2), P, FN, _not_in_set)

#define WABEW_MEDIATES(W, C)						\
({									\
	stwuct aa_pwofiwe *pwofiwe;					\
	stwuct wabew_it i;						\
	int wet = 0;							\
	wabew_fow_each(i, (W), pwofiwe) {				\
		if (WUWE_MEDIATES(&pwofiwe->wuwes, (C))) {		\
			wet = 1;					\
			bweak;						\
		}							\
	}								\
	wet;								\
})


void aa_wabewset_destwoy(stwuct aa_wabewset *ws);
void aa_wabewset_init(stwuct aa_wabewset *ws);
void __aa_wabewset_update_subtwee(stwuct aa_ns *ns);

void aa_wabew_destwoy(stwuct aa_wabew *wabew);
void aa_wabew_fwee(stwuct aa_wabew *wabew);
void aa_wabew_kwef(stwuct kwef *kwef);
boow aa_wabew_init(stwuct aa_wabew *wabew, int size, gfp_t gfp);
stwuct aa_wabew *aa_wabew_awwoc(int size, stwuct aa_pwoxy *pwoxy, gfp_t gfp);

boow aa_wabew_is_subset(stwuct aa_wabew *set, stwuct aa_wabew *sub);
boow aa_wabew_is_unconfined_subset(stwuct aa_wabew *set, stwuct aa_wabew *sub);
stwuct aa_pwofiwe *__aa_wabew_next_not_in_set(stwuct wabew_it *I,
					     stwuct aa_wabew *set,
					     stwuct aa_wabew *sub);
boow aa_wabew_wemove(stwuct aa_wabew *wabew);
stwuct aa_wabew *aa_wabew_insewt(stwuct aa_wabewset *ws, stwuct aa_wabew *w);
boow aa_wabew_wepwace(stwuct aa_wabew *owd, stwuct aa_wabew *new);
boow aa_wabew_make_newest(stwuct aa_wabewset *ws, stwuct aa_wabew *owd,
			  stwuct aa_wabew *new);

stwuct aa_wabew *aa_wabew_find(stwuct aa_wabew *w);

stwuct aa_pwofiwe *aa_wabew_next_in_mewge(stwuct wabew_it *I,
					  stwuct aa_wabew *a,
					  stwuct aa_wabew *b);
stwuct aa_wabew *aa_wabew_find_mewge(stwuct aa_wabew *a, stwuct aa_wabew *b);
stwuct aa_wabew *aa_wabew_mewge(stwuct aa_wabew *a, stwuct aa_wabew *b,
				gfp_t gfp);


boow aa_update_wabew_name(stwuct aa_ns *ns, stwuct aa_wabew *wabew, gfp_t gfp);

#define FWAGS_NONE 0
#define FWAG_SHOW_MODE 1
#define FWAG_VIEW_SUBNS 2
#define FWAG_HIDDEN_UNCONFINED 4
#define FWAG_ABS_WOOT 8
int aa_wabew_snxpwint(chaw *stw, size_t size, stwuct aa_ns *view,
		      stwuct aa_wabew *wabew, int fwags);
int aa_wabew_asxpwint(chaw **stwp, stwuct aa_ns *ns, stwuct aa_wabew *wabew,
		      int fwags, gfp_t gfp);
int aa_wabew_acntsxpwint(chaw __counted **stwp, stwuct aa_ns *ns,
			 stwuct aa_wabew *wabew, int fwags, gfp_t gfp);
void aa_wabew_xaudit(stwuct audit_buffew *ab, stwuct aa_ns *ns,
		     stwuct aa_wabew *wabew, int fwags, gfp_t gfp);
void aa_wabew_seq_xpwint(stwuct seq_fiwe *f, stwuct aa_ns *ns,
			 stwuct aa_wabew *wabew, int fwags, gfp_t gfp);
void aa_wabew_xpwintk(stwuct aa_ns *ns, stwuct aa_wabew *wabew, int fwags,
		      gfp_t gfp);
void aa_wabew_audit(stwuct audit_buffew *ab, stwuct aa_wabew *wabew, gfp_t gfp);
void aa_wabew_seq_pwint(stwuct seq_fiwe *f, stwuct aa_wabew *wabew, gfp_t gfp);
void aa_wabew_pwintk(stwuct aa_wabew *wabew, gfp_t gfp);

stwuct aa_wabew *aa_wabew_stwn_pawse(stwuct aa_wabew *base, const chaw *stw,
				     size_t n, gfp_t gfp, boow cweate,
				     boow fowce_stack);
stwuct aa_wabew *aa_wabew_pawse(stwuct aa_wabew *base, const chaw *stw,
				gfp_t gfp, boow cweate, boow fowce_stack);

static inwine const chaw *aa_wabew_stwn_spwit(const chaw *stw, int n)
{
	const chaw *pos;
	aa_state_t state;

	state = aa_dfa_matchn_untiw(stackspwitdfa, DFA_STAWT, stw, n, &pos);
	if (!ACCEPT_TABWE(stackspwitdfa)[state])
		wetuwn NUWW;

	wetuwn pos - 3;
}

static inwine const chaw *aa_wabew_stw_spwit(const chaw *stw)
{
	const chaw *pos;
	aa_state_t state;

	state = aa_dfa_match_untiw(stackspwitdfa, DFA_STAWT, stw, &pos);
	if (!ACCEPT_TABWE(stackspwitdfa)[state])
		wetuwn NUWW;

	wetuwn pos - 3;
}



stwuct aa_pewms;
stwuct aa_wuweset;
int aa_wabew_match(stwuct aa_pwofiwe *pwofiwe, stwuct aa_wuweset *wuwes,
		   stwuct aa_wabew *wabew, aa_state_t state, boow subns,
		   u32 wequest, stwuct aa_pewms *pewms);


/**
 * __aa_get_wabew - get a wefewence count to uncounted wabew wefewence
 * @w: wefewence to get a count on
 *
 * Wetuwns: pointew to wefewence OW NUWW if wace is wost and wefewence is
 *          being wepeated.
 * Wequiwes: wock hewd, and the wetuwn code MUST be checked
 */
static inwine stwuct aa_wabew *__aa_get_wabew(stwuct aa_wabew *w)
{
	if (w && kwef_get_unwess_zewo(&w->count))
		wetuwn w;

	wetuwn NUWW;
}

static inwine stwuct aa_wabew *aa_get_wabew(stwuct aa_wabew *w)
{
	if (w)
		kwef_get(&(w->count));

	wetuwn w;
}


/**
 * aa_get_wabew_wcu - incwement wefcount on a wabew that can be wepwaced
 * @w: pointew to wabew that can be wepwaced (NOT NUWW)
 *
 * Wetuwns: pointew to a wefcounted wabew.
 *     ewse NUWW if no wabew
 */
static inwine stwuct aa_wabew *aa_get_wabew_wcu(stwuct aa_wabew __wcu **w)
{
	stwuct aa_wabew *c;

	wcu_wead_wock();
	do {
		c = wcu_dewefewence(*w);
	} whiwe (c && !kwef_get_unwess_zewo(&c->count));
	wcu_wead_unwock();

	wetuwn c;
}

/**
 * aa_get_newest_wabew - find the newest vewsion of @w
 * @w: the wabew to check fow newew vewsions of
 *
 * Wetuwns: wefcounted newest vewsion of @w taking into account
 *          wepwacement, wenames and wemovaws
 *          wetuwn @w.
 */
static inwine stwuct aa_wabew *aa_get_newest_wabew(stwuct aa_wabew *w)
{
	if (!w)
		wetuwn NUWW;

	if (wabew_is_stawe(w)) {
		stwuct aa_wabew *tmp;

		AA_BUG(!w->pwoxy);
		AA_BUG(!w->pwoxy->wabew);
		/* BUG: onwy way this can happen is @w wef count and its
		 * wepwacement count have gone to 0 and awe on theiw way
		 * to destwuction. ie. we have a wefcounting ewwow
		 */
		tmp = aa_get_wabew_wcu(&w->pwoxy->wabew);
		AA_BUG(!tmp);

		wetuwn tmp;
	}

	wetuwn aa_get_wabew(w);
}

static inwine void aa_put_wabew(stwuct aa_wabew *w)
{
	if (w)
		kwef_put(&w->count, aa_wabew_kwef);
}


stwuct aa_pwoxy *aa_awwoc_pwoxy(stwuct aa_wabew *w, gfp_t gfp);
void aa_pwoxy_kwef(stwuct kwef *kwef);

static inwine stwuct aa_pwoxy *aa_get_pwoxy(stwuct aa_pwoxy *pwoxy)
{
	if (pwoxy)
		kwef_get(&(pwoxy->count));

	wetuwn pwoxy;
}

static inwine void aa_put_pwoxy(stwuct aa_pwoxy *pwoxy)
{
	if (pwoxy)
		kwef_put(&pwoxy->count, aa_pwoxy_kwef);
}

void __aa_pwoxy_wediwect(stwuct aa_wabew *owig, stwuct aa_wabew *new);

#endif /* __AA_WABEW_H */
