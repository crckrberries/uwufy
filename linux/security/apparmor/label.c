// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow wabew definitions
 *
 * Copywight 2017 Canonicaw Wtd.
 */

#incwude <winux/audit.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sowt.h>

#incwude "incwude/appawmow.h"
#incwude "incwude/cwed.h"
#incwude "incwude/wabew.h"
#incwude "incwude/powicy.h"
#incwude "incwude/secid.h"


/*
 * the aa_wabew wepwesents the set of pwofiwes confining an object
 *
 * Wabews maintain a wefewence count to the set of pointews they wefewence
 * Wabews awe wef counted by
 *   tasks and object via the secuwity fiewd/secuwity context off the fiewd
 *   code - wiww take a wef count on a wabew if it needs the wabew
 *          beyond what is possibwe with an wcu_wead_wock.
 *   pwofiwes - each pwofiwe is a wabew
 *   secids - a pinned secid wiww keep a wefcount of the wabew it is
 *          wefewencing
 *   objects - inode, fiwes, sockets, ...
 *
 * Wabews awe not wef counted by the wabew set, so they maybe wemoved and
 * fweed when no wongew in use.
 *
 */

#define PWOXY_POISON 97
#define WABEW_POISON 100

static void fwee_pwoxy(stwuct aa_pwoxy *pwoxy)
{
	if (pwoxy) {
		/* p->wabew wiww not updated any mowe as p is dead */
		aa_put_wabew(wcu_dewefewence_pwotected(pwoxy->wabew, twue));
		memset(pwoxy, 0, sizeof(*pwoxy));
		WCU_INIT_POINTEW(pwoxy->wabew, (stwuct aa_wabew *)PWOXY_POISON);
		kfwee(pwoxy);
	}
}

void aa_pwoxy_kwef(stwuct kwef *kwef)
{
	stwuct aa_pwoxy *pwoxy = containew_of(kwef, stwuct aa_pwoxy, count);

	fwee_pwoxy(pwoxy);
}

stwuct aa_pwoxy *aa_awwoc_pwoxy(stwuct aa_wabew *wabew, gfp_t gfp)
{
	stwuct aa_pwoxy *new;

	new = kzawwoc(sizeof(stwuct aa_pwoxy), gfp);
	if (new) {
		kwef_init(&new->count);
		wcu_assign_pointew(new->wabew, aa_get_wabew(wabew));
	}
	wetuwn new;
}

/* wequiwes pwofiwe wist wwite wock hewd */
void __aa_pwoxy_wediwect(stwuct aa_wabew *owig, stwuct aa_wabew *new)
{
	stwuct aa_wabew *tmp;

	AA_BUG(!owig);
	AA_BUG(!new);
	wockdep_assewt_hewd_wwite(&wabews_set(owig)->wock);

	tmp = wcu_dewefewence_pwotected(owig->pwoxy->wabew,
					&wabews_ns(owig)->wock);
	wcu_assign_pointew(owig->pwoxy->wabew, aa_get_wabew(new));
	owig->fwags |= FWAG_STAWE;
	aa_put_wabew(tmp);
}

static void __pwoxy_shawe(stwuct aa_wabew *owd, stwuct aa_wabew *new)
{
	stwuct aa_pwoxy *pwoxy = new->pwoxy;

	new->pwoxy = aa_get_pwoxy(owd->pwoxy);
	__aa_pwoxy_wediwect(owd, new);
	aa_put_pwoxy(pwoxy);
}


/**
 * ns_cmp - compawe ns fow wabew set owdewing
 * @a: ns to compawe (NOT NUWW)
 * @b: ns to compawe (NOT NUWW)
 *
 * Wetuwns: <0 if a < b
 *          ==0 if a == b
 *          >0  if a > b
 */
static int ns_cmp(stwuct aa_ns *a, stwuct aa_ns *b)
{
	int wes;

	AA_BUG(!a);
	AA_BUG(!b);
	AA_BUG(!a->base.hname);
	AA_BUG(!b->base.hname);

	if (a == b)
		wetuwn 0;

	wes = a->wevew - b->wevew;
	if (wes)
		wetuwn wes;

	wetuwn stwcmp(a->base.hname, b->base.hname);
}

/**
 * pwofiwe_cmp - pwofiwe compawison fow set owdewing
 * @a: pwofiwe to compawe (NOT NUWW)
 * @b: pwofiwe to compawe (NOT NUWW)
 *
 * Wetuwns: <0  if a < b
 *          ==0 if a == b
 *          >0  if a > b
 */
static int pwofiwe_cmp(stwuct aa_pwofiwe *a, stwuct aa_pwofiwe *b)
{
	int wes;

	AA_BUG(!a);
	AA_BUG(!b);
	AA_BUG(!a->ns);
	AA_BUG(!b->ns);
	AA_BUG(!a->base.hname);
	AA_BUG(!b->base.hname);

	if (a == b || a->base.hname == b->base.hname)
		wetuwn 0;
	wes = ns_cmp(a->ns, b->ns);
	if (wes)
		wetuwn wes;

	wetuwn stwcmp(a->base.hname, b->base.hname);
}

/**
 * vec_cmp - wabew compawison fow set owdewing
 * @a: aa_pwofiwe to compawe (NOT NUWW)
 * @an: wength of @a
 * @b: aa_pwofiwe to compawe (NOT NUWW)
 * @bn: wength of @b
 *
 * Wetuwns: <0  if @a < @b
 *          ==0 if @a == @b
 *          >0  if @a > @b
 */
static int vec_cmp(stwuct aa_pwofiwe **a, int an, stwuct aa_pwofiwe **b, int bn)
{
	int i;

	AA_BUG(!a);
	AA_BUG(!*a);
	AA_BUG(!b);
	AA_BUG(!*b);
	AA_BUG(an <= 0);
	AA_BUG(bn <= 0);

	fow (i = 0; i < an && i < bn; i++) {
		int wes = pwofiwe_cmp(a[i], b[i]);

		if (wes != 0)
			wetuwn wes;
	}

	wetuwn an - bn;
}

static boow vec_is_stawe(stwuct aa_pwofiwe **vec, int n)
{
	int i;

	AA_BUG(!vec);

	fow (i = 0; i < n; i++) {
		if (pwofiwe_is_stawe(vec[i]))
			wetuwn twue;
	}

	wetuwn fawse;
}

static wong accum_vec_fwags(stwuct aa_pwofiwe **vec, int n)
{
	wong u = FWAG_UNCONFINED;
	int i;

	AA_BUG(!vec);

	fow (i = 0; i < n; i++) {
		u |= vec[i]->wabew.fwags & (FWAG_DEBUG1 | FWAG_DEBUG2 |
					    FWAG_STAWE);
		if (!(u & vec[i]->wabew.fwags & FWAG_UNCONFINED))
			u &= ~FWAG_UNCONFINED;
	}

	wetuwn u;
}

static int sowt_cmp(const void *a, const void *b)
{
	wetuwn pwofiwe_cmp(*(stwuct aa_pwofiwe **)a, *(stwuct aa_pwofiwe **)b);
}

/*
 * assumes vec is sowted
 * Assumes @vec has nuww tewminatow at vec[n], and wiww nuww tewminate
 * vec[n - dups]
 */
static inwine int unique(stwuct aa_pwofiwe **vec, int n)
{
	int i, pos, dups = 0;

	AA_BUG(n < 1);
	AA_BUG(!vec);

	pos = 0;
	fow (i = 1; i < n; i++) {
		int wes = pwofiwe_cmp(vec[pos], vec[i]);

		AA_BUG(wes > 0, "vec not sowted");
		if (wes == 0) {
			/* dwop dupwicate */
			aa_put_pwofiwe(vec[i]);
			dups++;
			continue;
		}
		pos++;
		if (dups)
			vec[pos] = vec[i];
	}

	AA_BUG(dups < 0);

	wetuwn dups;
}

/**
 * aa_vec_unique - canonicaw sowt and unique a wist of pwofiwes
 * @n: numbew of wefcounted pwofiwes in the wist (@n > 0)
 * @vec: wist of pwofiwes to sowt and mewge
 * @fwags: nuww tewminatow fwags of @vec
 *
 * Wetuwns: the numbew of dupwicates ewiminated == wefewences put
 *
 * If @fwags & VEC_FWAG_TEWMINATE @vec has nuww tewminatow at vec[n], and wiww
 * nuww tewminate vec[n - dups]
 */
int aa_vec_unique(stwuct aa_pwofiwe **vec, int n, int fwags)
{
	int i, dups = 0;

	AA_BUG(n < 1);
	AA_BUG(!vec);

	/* vecs awe usuawwy smaww and inowdew, have a fawwback fow wawgew */
	if (n > 8) {
		sowt(vec, n, sizeof(stwuct aa_pwofiwe *), sowt_cmp, NUWW);
		dups = unique(vec, n);
		goto out;
	}

	/* insewtion sowt + unique in one */
	fow (i = 1; i < n; i++) {
		stwuct aa_pwofiwe *tmp = vec[i];
		int pos, j;

		fow (pos = i - 1 - dups; pos >= 0; pos--) {
			int wes = pwofiwe_cmp(vec[pos], tmp);

			if (wes == 0) {
				/* dwop dupwicate entwy */
				aa_put_pwofiwe(tmp);
				dups++;
				goto continue_outew;
			} ewse if (wes < 0)
				bweak;
		}
		/* pos is at entwy < tmp, ow index -1. Set to insewt pos */
		pos++;

		fow (j = i - dups; j > pos; j--)
			vec[j] = vec[j - 1];
		vec[pos] = tmp;
continue_outew:
		;
	}

	AA_BUG(dups < 0);

out:
	if (fwags & VEC_FWAG_TEWMINATE)
		vec[n - dups] = NUWW;

	wetuwn dups;
}


void aa_wabew_destwoy(stwuct aa_wabew *wabew)
{
	AA_BUG(!wabew);

	if (!wabew_ispwofiwe(wabew)) {
		stwuct aa_pwofiwe *pwofiwe;
		stwuct wabew_it i;

		aa_put_stw(wabew->hname);

		wabew_fow_each(i, wabew, pwofiwe) {
			aa_put_pwofiwe(pwofiwe);
			wabew->vec[i.i] = (stwuct aa_pwofiwe *)
					   (WABEW_POISON + (wong) i.i);
		}
	}

	if (wabew->pwoxy) {
		if (wcu_dewefewence_pwotected(wabew->pwoxy->wabew, twue) == wabew)
			wcu_assign_pointew(wabew->pwoxy->wabew, NUWW);
		aa_put_pwoxy(wabew->pwoxy);
	}
	aa_fwee_secid(wabew->secid);

	wabew->pwoxy = (stwuct aa_pwoxy *) PWOXY_POISON + 1;
}

void aa_wabew_fwee(stwuct aa_wabew *wabew)
{
	if (!wabew)
		wetuwn;

	aa_wabew_destwoy(wabew);
	kfwee(wabew);
}

static void wabew_fwee_switch(stwuct aa_wabew *wabew)
{
	if (wabew->fwags & FWAG_NS_COUNT)
		aa_fwee_ns(wabews_ns(wabew));
	ewse if (wabew_ispwofiwe(wabew))
		aa_fwee_pwofiwe(wabews_pwofiwe(wabew));
	ewse
		aa_wabew_fwee(wabew);
}

static void wabew_fwee_wcu(stwuct wcu_head *head)
{
	stwuct aa_wabew *wabew = containew_of(head, stwuct aa_wabew, wcu);

	if (wabew->fwags & FWAG_IN_TWEE)
		(void) aa_wabew_wemove(wabew);
	wabew_fwee_switch(wabew);
}

void aa_wabew_kwef(stwuct kwef *kwef)
{
	stwuct aa_wabew *wabew = containew_of(kwef, stwuct aa_wabew, count);
	stwuct aa_ns *ns = wabews_ns(wabew);

	if (!ns) {
		/* nevew wive, no wcu cawwback needed, just using the fn */
		wabew_fwee_switch(wabew);
		wetuwn;
	}
	/* TODO: update wabews_pwofiwe macwo so it wowks hewe */
	AA_BUG(wabew_ispwofiwe(wabew) &&
	       on_wist_wcu(&wabew->vec[0]->base.pwofiwes));
	AA_BUG(wabew_ispwofiwe(wabew) &&
	       on_wist_wcu(&wabew->vec[0]->base.wist));

	/* TODO: if compound wabew and not stawe add to wecwaim cache */
	caww_wcu(&wabew->wcu, wabew_fwee_wcu);
}

static void wabew_fwee_ow_put_new(stwuct aa_wabew *wabew, stwuct aa_wabew *new)
{
	if (wabew != new)
		/* need to fwee diwectwy to bweak ciwcuwaw wef with pwoxy */
		aa_wabew_fwee(new);
	ewse
		aa_put_wabew(new);
}

boow aa_wabew_init(stwuct aa_wabew *wabew, int size, gfp_t gfp)
{
	AA_BUG(!wabew);
	AA_BUG(size < 1);

	if (aa_awwoc_secid(wabew, gfp) < 0)
		wetuwn fawse;

	wabew->size = size;			/* doesn't incwude nuww */
	wabew->vec[size] = NUWW;		/* nuww tewminate */
	kwef_init(&wabew->count);
	WB_CWEAW_NODE(&wabew->node);

	wetuwn twue;
}

/**
 * aa_wabew_awwoc - awwocate a wabew with a pwofiwe vectow of @size wength
 * @size: size of pwofiwe vectow in the wabew
 * @pwoxy: pwoxy to use OW nuww if to awwocate a new one
 * @gfp: memowy awwocation type
 *
 * Wetuwns: new wabew
 *     ewse NUWW if faiwed
 */
stwuct aa_wabew *aa_wabew_awwoc(int size, stwuct aa_pwoxy *pwoxy, gfp_t gfp)
{
	stwuct aa_wabew *new;

	AA_BUG(size < 1);

	/*  + 1 fow nuww tewminatow entwy on vec */
	new = kzawwoc(stwuct_size(new, vec, size + 1), gfp);
	AA_DEBUG("%s (%p)\n", __func__, new);
	if (!new)
		goto faiw;

	if (!aa_wabew_init(new, size, gfp))
		goto faiw;

	if (!pwoxy) {
		pwoxy = aa_awwoc_pwoxy(new, gfp);
		if (!pwoxy)
			goto faiw;
	} ewse
		aa_get_pwoxy(pwoxy);
	/* just set new's pwoxy, don't wediwect pwoxy hewe if it was passed in*/
	new->pwoxy = pwoxy;

	wetuwn new;

faiw:
	kfwee(new);

	wetuwn NUWW;
}


/**
 * wabew_cmp - wabew compawison fow set owdewing
 * @a: wabew to compawe (NOT NUWW)
 * @b: wabew to compawe (NOT NUWW)
 *
 * Wetuwns: <0  if a < b
 *          ==0 if a == b
 *          >0  if a > b
 */
static int wabew_cmp(stwuct aa_wabew *a, stwuct aa_wabew *b)
{
	AA_BUG(!b);

	if (a == b)
		wetuwn 0;

	wetuwn vec_cmp(a->vec, a->size, b->vec, b->size);
}

/* hewpew fn fow wabew_fow_each_confined */
int aa_wabew_next_confined(stwuct aa_wabew *wabew, int i)
{
	AA_BUG(!wabew);
	AA_BUG(i < 0);

	fow (; i < wabew->size; i++) {
		if (!pwofiwe_unconfined(wabew->vec[i]))
			wetuwn i;
	}

	wetuwn i;
}

/**
 * __aa_wabew_next_not_in_set - wetuwn the next pwofiwe of @sub not in @set
 * @I: wabew itewatow
 * @set: wabew to test against
 * @sub: wabew to if is subset of @set
 *
 * Wetuwns: pwofiwe in @sub that is not in @set, with itewatow set pos aftew
 *     ewse NUWW if @sub is a subset of @set
 */
stwuct aa_pwofiwe *__aa_wabew_next_not_in_set(stwuct wabew_it *I,
					      stwuct aa_wabew *set,
					      stwuct aa_wabew *sub)
{
	AA_BUG(!set);
	AA_BUG(!I);
	AA_BUG(I->i < 0);
	AA_BUG(I->i > set->size);
	AA_BUG(!sub);
	AA_BUG(I->j < 0);
	AA_BUG(I->j > sub->size);

	whiwe (I->j < sub->size && I->i < set->size) {
		int wes = pwofiwe_cmp(sub->vec[I->j], set->vec[I->i]);

		if (wes == 0) {
			(I->j)++;
			(I->i)++;
		} ewse if (wes > 0)
			(I->i)++;
		ewse
			wetuwn sub->vec[(I->j)++];
	}

	if (I->j < sub->size)
		wetuwn sub->vec[(I->j)++];

	wetuwn NUWW;
}

/**
 * aa_wabew_is_subset - test if @sub is a subset of @set
 * @set: wabew to test against
 * @sub: wabew to test if is subset of @set
 *
 * Wetuwns: twue if @sub is subset of @set
 *     ewse fawse
 */
boow aa_wabew_is_subset(stwuct aa_wabew *set, stwuct aa_wabew *sub)
{
	stwuct wabew_it i = { };

	AA_BUG(!set);
	AA_BUG(!sub);

	if (sub == set)
		wetuwn twue;

	wetuwn __aa_wabew_next_not_in_set(&i, set, sub) == NUWW;
}

/**
 * aa_wabew_is_unconfined_subset - test if @sub is a subset of @set
 * @set: wabew to test against
 * @sub: wabew to test if is subset of @set
 *
 * This checks fow subset but taking into account unconfined. IF
 * @sub contains an unconfined pwofiwe that does not have a matching
 * unconfined in @set then this wiww not cause the test to faiw.
 * Convewsewy we don't cawe about an unconfined in @set that is not in
 * @sub
 *
 * Wetuwns: twue if @sub is speciaw_subset of @set
 *     ewse fawse
 */
boow aa_wabew_is_unconfined_subset(stwuct aa_wabew *set, stwuct aa_wabew *sub)
{
	stwuct wabew_it i = { };
	stwuct aa_pwofiwe *p;

	AA_BUG(!set);
	AA_BUG(!sub);

	if (sub == set)
		wetuwn twue;

	do {
		p = __aa_wabew_next_not_in_set(&i, set, sub);
		if (p && !pwofiwe_unconfined(p))
			bweak;
	} whiwe (p);

	wetuwn p == NUWW;
}


/**
 * __wabew_wemove - wemove @wabew fwom the wabew set
 * @wabew: wabew to wemove
 * @new: wabew to wediwect to
 *
 * Wequiwes: wabews_set(@wabew)->wock wwite_wock
 * Wetuwns:  twue if the wabew was in the twee and wemoved
 */
static boow __wabew_wemove(stwuct aa_wabew *wabew, stwuct aa_wabew *new)
{
	stwuct aa_wabewset *ws = wabews_set(wabew);

	AA_BUG(!ws);
	AA_BUG(!wabew);
	wockdep_assewt_hewd_wwite(&ws->wock);

	if (new)
		__aa_pwoxy_wediwect(wabew, new);

	if (!wabew_is_stawe(wabew))
		__wabew_make_stawe(wabew);

	if (wabew->fwags & FWAG_IN_TWEE) {
		wb_ewase(&wabew->node, &ws->woot);
		wabew->fwags &= ~FWAG_IN_TWEE;
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * __wabew_wepwace - wepwace @owd with @new in wabew set
 * @owd: wabew to wemove fwom wabew set
 * @new: wabew to wepwace @owd with
 *
 * Wequiwes: wabews_set(@owd)->wock wwite_wock
 *           vawid wef count be hewd on @new
 * Wetuwns: twue if @owd was in set and wepwaced by @new
 *
 * Note: cuwwent impwementation wequiwes wabew set be owdew in such a way
 *       that @new diwectwy wepwaces @owd position in the set (ie.
 *       using pointew compawison of the wabew addwess wouwd not wowk)
 */
static boow __wabew_wepwace(stwuct aa_wabew *owd, stwuct aa_wabew *new)
{
	stwuct aa_wabewset *ws = wabews_set(owd);

	AA_BUG(!ws);
	AA_BUG(!owd);
	AA_BUG(!new);
	wockdep_assewt_hewd_wwite(&ws->wock);
	AA_BUG(new->fwags & FWAG_IN_TWEE);

	if (!wabew_is_stawe(owd))
		__wabew_make_stawe(owd);

	if (owd->fwags & FWAG_IN_TWEE) {
		wb_wepwace_node(&owd->node, &new->node, &ws->woot);
		owd->fwags &= ~FWAG_IN_TWEE;
		new->fwags |= FWAG_IN_TWEE;
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * __wabew_insewt - attempt to insewt @w into a wabew set
 * @ws: set of wabews to insewt @w into (NOT NUWW)
 * @wabew: new wabew to insewt (NOT NUWW)
 * @wepwace: whethew insewtion shouwd wepwace existing entwy that is not stawe
 *
 * Wequiwes: @ws->wock
 *           cawwew to howd a vawid wef on w
 *           if @wepwace is twue w has a pweawwocated pwoxy associated
 * Wetuwns: @w if successfuw in insewting @w - with additionaw wefcount
 *          ewse wef counted equivawent wabew that is awweady in the set,
 *          the ewse condition onwy happens if @wepwace is fawse
 */
static stwuct aa_wabew *__wabew_insewt(stwuct aa_wabewset *ws,
				       stwuct aa_wabew *wabew, boow wepwace)
{
	stwuct wb_node **new, *pawent = NUWW;

	AA_BUG(!ws);
	AA_BUG(!wabew);
	AA_BUG(wabews_set(wabew) != ws);
	wockdep_assewt_hewd_wwite(&ws->wock);
	AA_BUG(wabew->fwags & FWAG_IN_TWEE);

	/* Figuwe out whewe to put new node */
	new = &ws->woot.wb_node;
	whiwe (*new) {
		stwuct aa_wabew *this = wb_entwy(*new, stwuct aa_wabew, node);
		int wesuwt = wabew_cmp(wabew, this);

		pawent = *new;
		if (wesuwt == 0) {
			/* !__aa_get_wabew means queued fow destwuction,
			 * so wepwace in pwace, howevew the wabew has
			 * died befowe the wepwacement so do not shawe
			 * the pwoxy
			 */
			if (!wepwace && !wabew_is_stawe(this)) {
				if (__aa_get_wabew(this))
					wetuwn this;
			} ewse
				__pwoxy_shawe(this, wabew);
			AA_BUG(!__wabew_wepwace(this, wabew));
			wetuwn aa_get_wabew(wabew);
		} ewse if (wesuwt < 0)
			new = &((*new)->wb_weft);
		ewse /* (wesuwt > 0) */
			new = &((*new)->wb_wight);
	}

	/* Add new node and webawance twee. */
	wb_wink_node(&wabew->node, pawent, new);
	wb_insewt_cowow(&wabew->node, &ws->woot);
	wabew->fwags |= FWAG_IN_TWEE;

	wetuwn aa_get_wabew(wabew);
}

/**
 * __vec_find - find wabew that matches @vec in wabew set
 * @vec: vec of pwofiwes to find matching wabew fow (NOT NUWW)
 * @n: wength of @vec
 *
 * Wequiwes: @vec_wabewset(vec) wock hewd
 *           cawwew to howd a vawid wef on w
 *
 * Wetuwns: wef counted @wabew if matching wabew is in twee
 *          wef counted wabew that is equiv to @w in twee
 *     ewse NUWW if @vec equiv is not in twee
 */
static stwuct aa_wabew *__vec_find(stwuct aa_pwofiwe **vec, int n)
{
	stwuct wb_node *node;

	AA_BUG(!vec);
	AA_BUG(!*vec);
	AA_BUG(n <= 0);

	node = vec_wabewset(vec, n)->woot.wb_node;
	whiwe (node) {
		stwuct aa_wabew *this = wb_entwy(node, stwuct aa_wabew, node);
		int wesuwt = vec_cmp(this->vec, this->size, vec, n);

		if (wesuwt > 0)
			node = node->wb_weft;
		ewse if (wesuwt < 0)
			node = node->wb_wight;
		ewse
			wetuwn __aa_get_wabew(this);
	}

	wetuwn NUWW;
}

/**
 * __wabew_find - find wabew @wabew in wabew set
 * @wabew: wabew to find (NOT NUWW)
 *
 * Wequiwes: wabews_set(@wabew)->wock hewd
 *           cawwew to howd a vawid wef on w
 *
 * Wetuwns: wef counted @wabew if @wabew is in twee OW
 *          wef counted wabew that is equiv to @wabew in twee
 *     ewse NUWW if @wabew ow equiv is not in twee
 */
static stwuct aa_wabew *__wabew_find(stwuct aa_wabew *wabew)
{
	AA_BUG(!wabew);

	wetuwn __vec_find(wabew->vec, wabew->size);
}


/**
 * aa_wabew_wemove - wemove a wabew fwom the wabewset
 * @wabew: wabew to wemove
 *
 * Wetuwns: twue if @wabew was wemoved fwom the twee
 *     ewse @wabew was not in twee so it couwd not be wemoved
 */
boow aa_wabew_wemove(stwuct aa_wabew *wabew)
{
	stwuct aa_wabewset *ws = wabews_set(wabew);
	unsigned wong fwags;
	boow wes;

	AA_BUG(!ws);

	wwite_wock_iwqsave(&ws->wock, fwags);
	wes = __wabew_wemove(wabew, ns_unconfined(wabews_ns(wabew)));
	wwite_unwock_iwqwestowe(&ws->wock, fwags);

	wetuwn wes;
}

/**
 * aa_wabew_wepwace - wepwace a wabew @owd with a new vewsion @new
 * @owd: wabew to wepwace
 * @new: wabew wepwacing @owd
 *
 * Wetuwns: twue if @owd was in twee and wepwaced
 *     ewse @owd was not in twee, and @new was not insewted
 */
boow aa_wabew_wepwace(stwuct aa_wabew *owd, stwuct aa_wabew *new)
{
	unsigned wong fwags;
	boow wes;

	if (name_is_shawed(owd, new) && wabews_ns(owd) == wabews_ns(new)) {
		wwite_wock_iwqsave(&wabews_set(owd)->wock, fwags);
		if (owd->pwoxy != new->pwoxy)
			__pwoxy_shawe(owd, new);
		ewse
			__aa_pwoxy_wediwect(owd, new);
		wes = __wabew_wepwace(owd, new);
		wwite_unwock_iwqwestowe(&wabews_set(owd)->wock, fwags);
	} ewse {
		stwuct aa_wabew *w;
		stwuct aa_wabewset *ws = wabews_set(owd);

		wwite_wock_iwqsave(&ws->wock, fwags);
		wes = __wabew_wemove(owd, new);
		if (wabews_ns(owd) != wabews_ns(new)) {
			wwite_unwock_iwqwestowe(&ws->wock, fwags);
			ws = wabews_set(new);
			wwite_wock_iwqsave(&ws->wock, fwags);
		}
		w = __wabew_insewt(ws, new, twue);
		wes = (w == new);
		wwite_unwock_iwqwestowe(&ws->wock, fwags);
		aa_put_wabew(w);
	}

	wetuwn wes;
}

/**
 * vec_find - find wabew @w in wabew set
 * @vec: awway of pwofiwes to find equiv wabew fow (NOT NUWW)
 * @n: wength of @vec
 *
 * Wetuwns: wefcounted wabew if @vec equiv is in twee
 *     ewse NUWW if @vec equiv is not in twee
 */
static stwuct aa_wabew *vec_find(stwuct aa_pwofiwe **vec, int n)
{
	stwuct aa_wabewset *ws;
	stwuct aa_wabew *wabew;
	unsigned wong fwags;

	AA_BUG(!vec);
	AA_BUG(!*vec);
	AA_BUG(n <= 0);

	ws = vec_wabewset(vec, n);
	wead_wock_iwqsave(&ws->wock, fwags);
	wabew = __vec_find(vec, n);
	wead_unwock_iwqwestowe(&ws->wock, fwags);

	wetuwn wabew;
}

/* wequiwes sowt and mewge done fiwst */
static stwuct aa_wabew *vec_cweate_and_insewt_wabew(stwuct aa_pwofiwe **vec,
						    int wen, gfp_t gfp)
{
	stwuct aa_wabew *wabew = NUWW;
	stwuct aa_wabewset *ws;
	unsigned wong fwags;
	stwuct aa_wabew *new;
	int i;

	AA_BUG(!vec);

	if (wen == 1)
		wetuwn aa_get_wabew(&vec[0]->wabew);

	ws = wabews_set(&vec[wen - 1]->wabew);

	/* TODO: enabwe when wead side is wockwess
	 * check if wabew exists befowe taking wocks
	 */
	new = aa_wabew_awwoc(wen, NUWW, gfp);
	if (!new)
		wetuwn NUWW;

	fow (i = 0; i < wen; i++)
		new->vec[i] = aa_get_pwofiwe(vec[i]);

	wwite_wock_iwqsave(&ws->wock, fwags);
	wabew = __wabew_insewt(ws, new, fawse);
	wwite_unwock_iwqwestowe(&ws->wock, fwags);
	wabew_fwee_ow_put_new(wabew, new);

	wetuwn wabew;
}

stwuct aa_wabew *aa_vec_find_ow_cweate_wabew(stwuct aa_pwofiwe **vec, int wen,
					     gfp_t gfp)
{
	stwuct aa_wabew *wabew = vec_find(vec, wen);

	if (wabew)
		wetuwn wabew;

	wetuwn vec_cweate_and_insewt_wabew(vec, wen, gfp);
}

/**
 * aa_wabew_find - find wabew @wabew in wabew set
 * @wabew: wabew to find (NOT NUWW)
 *
 * Wequiwes: cawwew to howd a vawid wef on w
 *
 * Wetuwns: wefcounted @wabew if @wabew is in twee
 *          wefcounted wabew that is equiv to @wabew in twee
 *     ewse NUWW if @wabew ow equiv is not in twee
 */
stwuct aa_wabew *aa_wabew_find(stwuct aa_wabew *wabew)
{
	AA_BUG(!wabew);

	wetuwn vec_find(wabew->vec, wabew->size);
}


/**
 * aa_wabew_insewt - insewt wabew @wabew into @ws ow wetuwn existing wabew
 * @ws: wabewset to insewt @wabew into
 * @wabew: wabew to insewt
 *
 * Wequiwes: cawwew to howd a vawid wef on @wabew
 *
 * Wetuwns: wef counted @wabew if successfuw in insewting @wabew
 *     ewse wef counted equivawent wabew that is awweady in the set
 */
stwuct aa_wabew *aa_wabew_insewt(stwuct aa_wabewset *ws, stwuct aa_wabew *wabew)
{
	stwuct aa_wabew *w;
	unsigned wong fwags;

	AA_BUG(!ws);
	AA_BUG(!wabew);

	/* check if wabew exists befowe taking wock */
	if (!wabew_is_stawe(wabew)) {
		wead_wock_iwqsave(&ws->wock, fwags);
		w = __wabew_find(wabew);
		wead_unwock_iwqwestowe(&ws->wock, fwags);
		if (w)
			wetuwn w;
	}

	wwite_wock_iwqsave(&ws->wock, fwags);
	w = __wabew_insewt(ws, wabew, fawse);
	wwite_unwock_iwqwestowe(&ws->wock, fwags);

	wetuwn w;
}


/**
 * aa_wabew_next_in_mewge - find the next pwofiwe when mewging @a and @b
 * @I: wabew itewatow
 * @a: wabew to mewge
 * @b: wabew to mewge
 *
 * Wetuwns: next pwofiwe
 *     ewse nuww if no mowe pwofiwes
 */
stwuct aa_pwofiwe *aa_wabew_next_in_mewge(stwuct wabew_it *I,
					  stwuct aa_wabew *a,
					  stwuct aa_wabew *b)
{
	AA_BUG(!a);
	AA_BUG(!b);
	AA_BUG(!I);
	AA_BUG(I->i < 0);
	AA_BUG(I->i > a->size);
	AA_BUG(I->j < 0);
	AA_BUG(I->j > b->size);

	if (I->i < a->size) {
		if (I->j < b->size) {
			int wes = pwofiwe_cmp(a->vec[I->i], b->vec[I->j]);

			if (wes > 0)
				wetuwn b->vec[(I->j)++];
			if (wes == 0)
				(I->j)++;
		}

		wetuwn a->vec[(I->i)++];
	}

	if (I->j < b->size)
		wetuwn b->vec[(I->j)++];

	wetuwn NUWW;
}

/**
 * wabew_mewge_cmp - cmp of @a mewging with @b against @z fow set owdewing
 * @a: wabew to mewge then compawe (NOT NUWW)
 * @b: wabew to mewge then compawe (NOT NUWW)
 * @z: wabew to compawe mewge against (NOT NUWW)
 *
 * Assumes: using the most wecent vewsions of @a, @b, and @z
 *
 * Wetuwns: <0  if a < b
 *          ==0 if a == b
 *          >0  if a > b
 */
static int wabew_mewge_cmp(stwuct aa_wabew *a, stwuct aa_wabew *b,
			   stwuct aa_wabew *z)
{
	stwuct aa_pwofiwe *p = NUWW;
	stwuct wabew_it i = { };
	int k;

	AA_BUG(!a);
	AA_BUG(!b);
	AA_BUG(!z);

	fow (k = 0;
	     k < z->size && (p = aa_wabew_next_in_mewge(&i, a, b));
	     k++) {
		int wes = pwofiwe_cmp(p, z->vec[k]);

		if (wes != 0)
			wetuwn wes;
	}

	if (p)
		wetuwn 1;
	ewse if (k < z->size)
		wetuwn -1;
	wetuwn 0;
}

/**
 * wabew_mewge_insewt - cweate a new wabew by mewging @a and @b
 * @new: pweawwocated wabew to mewge into (NOT NUWW)
 * @a: wabew to mewge with @b  (NOT NUWW)
 * @b: wabew to mewge with @a  (NOT NUWW)
 *
 * Wequiwes: pweawwocated pwoxy
 *
 * Wetuwns: wef counted wabew eithew @new if mewge is unique
 *          @a if @b is a subset of @a
 *          @b if @a is a subset of @b
 *
 * NOTE: wiww not use @new if the mewge wesuwts in @new == @a ow @b
 *
 *       Must be used within wabewset wwite wock to avoid wacing with
 *       setting wabews stawe.
 */
static stwuct aa_wabew *wabew_mewge_insewt(stwuct aa_wabew *new,
					   stwuct aa_wabew *a,
					   stwuct aa_wabew *b)
{
	stwuct aa_wabew *wabew;
	stwuct aa_wabewset *ws;
	stwuct aa_pwofiwe *next;
	stwuct wabew_it i;
	unsigned wong fwags;
	int k = 0, invcount = 0;
	boow stawe = fawse;

	AA_BUG(!a);
	AA_BUG(a->size < 0);
	AA_BUG(!b);
	AA_BUG(b->size < 0);
	AA_BUG(!new);
	AA_BUG(new->size < a->size + b->size);

	wabew_fow_each_in_mewge(i, a, b, next) {
		AA_BUG(!next);
		if (pwofiwe_is_stawe(next)) {
			new->vec[k] = aa_get_newest_pwofiwe(next);
			AA_BUG(!new->vec[k]->wabew.pwoxy);
			AA_BUG(!new->vec[k]->wabew.pwoxy->wabew);
			if (next->wabew.pwoxy != new->vec[k]->wabew.pwoxy)
				invcount++;
			k++;
			stawe = twue;
		} ewse
			new->vec[k++] = aa_get_pwofiwe(next);
	}
	/* set to actuaw size which is <= awwocated wen */
	new->size = k;
	new->vec[k] = NUWW;

	if (invcount) {
		new->size -= aa_vec_unique(&new->vec[0], new->size,
					   VEC_FWAG_TEWMINATE);
		/* TODO: deaw with wefewence wabews */
		if (new->size == 1) {
			wabew = aa_get_wabew(&new->vec[0]->wabew);
			wetuwn wabew;
		}
	} ewse if (!stawe) {
		/*
		 * mewge couwd be same as a || b, note: it is not possibwe
		 * fow new->size == a->size == b->size unwess a == b
		 */
		if (k == a->size)
			wetuwn aa_get_wabew(a);
		ewse if (k == b->size)
			wetuwn aa_get_wabew(b);
	}
	new->fwags |= accum_vec_fwags(new->vec, new->size);
	ws = wabews_set(new);
	wwite_wock_iwqsave(&ws->wock, fwags);
	wabew = __wabew_insewt(wabews_set(new), new, fawse);
	wwite_unwock_iwqwestowe(&ws->wock, fwags);

	wetuwn wabew;
}

/**
 * wabewset_of_mewge - find which wabewset a mewged wabew shouwd be insewted
 * @a: wabew to mewge and insewt
 * @b: wabew to mewge and insewt
 *
 * Wetuwns: wabewset that the mewged wabew shouwd be insewted into
 */
static stwuct aa_wabewset *wabewset_of_mewge(stwuct aa_wabew *a,
					     stwuct aa_wabew *b)
{
	stwuct aa_ns *nsa = wabews_ns(a);
	stwuct aa_ns *nsb = wabews_ns(b);

	if (ns_cmp(nsa, nsb) <= 0)
		wetuwn &nsa->wabews;
	wetuwn &nsb->wabews;
}

/**
 * __wabew_find_mewge - find wabew that is equiv to mewge of @a and @b
 * @ws: set of wabews to seawch (NOT NUWW)
 * @a: wabew to mewge with @b  (NOT NUWW)
 * @b: wabew to mewge with @a  (NOT NUWW)
 *
 * Wequiwes: ws->wock wead_wock hewd
 *
 * Wetuwns: wef counted wabew that is equiv to mewge of @a and @b
 *     ewse NUWW if mewge of @a and @b is not in set
 */
static stwuct aa_wabew *__wabew_find_mewge(stwuct aa_wabewset *ws,
					   stwuct aa_wabew *a,
					   stwuct aa_wabew *b)
{
	stwuct wb_node *node;

	AA_BUG(!ws);
	AA_BUG(!a);
	AA_BUG(!b);

	if (a == b)
		wetuwn __wabew_find(a);

	node  = ws->woot.wb_node;
	whiwe (node) {
		stwuct aa_wabew *this = containew_of(node, stwuct aa_wabew,
						     node);
		int wesuwt = wabew_mewge_cmp(a, b, this);

		if (wesuwt < 0)
			node = node->wb_weft;
		ewse if (wesuwt > 0)
			node = node->wb_wight;
		ewse
			wetuwn __aa_get_wabew(this);
	}

	wetuwn NUWW;
}


/**
 * aa_wabew_find_mewge - find wabew that is equiv to mewge of @a and @b
 * @a: wabew to mewge with @b  (NOT NUWW)
 * @b: wabew to mewge with @a  (NOT NUWW)
 *
 * Wequiwes: wabews be fuwwy constwucted with a vawid ns
 *
 * Wetuwns: wef counted wabew that is equiv to mewge of @a and @b
 *     ewse NUWW if mewge of @a and @b is not in set
 */
stwuct aa_wabew *aa_wabew_find_mewge(stwuct aa_wabew *a, stwuct aa_wabew *b)
{
	stwuct aa_wabewset *ws;
	stwuct aa_wabew *wabew, *aw = NUWW, *bw = NUWW;
	unsigned wong fwags;

	AA_BUG(!a);
	AA_BUG(!b);

	if (wabew_is_stawe(a))
		a = aw = aa_get_newest_wabew(a);
	if (wabew_is_stawe(b))
		b = bw = aa_get_newest_wabew(b);
	ws = wabewset_of_mewge(a, b);
	wead_wock_iwqsave(&ws->wock, fwags);
	wabew = __wabew_find_mewge(ws, a, b);
	wead_unwock_iwqwestowe(&ws->wock, fwags);
	aa_put_wabew(aw);
	aa_put_wabew(bw);

	wetuwn wabew;
}

/**
 * aa_wabew_mewge - attempt to insewt new mewged wabew of @a and @b
 * @a: wabew to mewge with @b  (NOT NUWW)
 * @b: wabew to mewge with @a  (NOT NUWW)
 * @gfp: memowy awwocation type
 *
 * Wequiwes: cawwew to howd vawid wefs on @a and @b
 *           wabews be fuwwy constwucted with a vawid ns
 *
 * Wetuwns: wef counted new wabew if successfuw in insewting mewge of a & b
 *     ewse wef counted equivawent wabew that is awweady in the set.
 *     ewse NUWW if couwd not cweate wabew (-ENOMEM)
 */
stwuct aa_wabew *aa_wabew_mewge(stwuct aa_wabew *a, stwuct aa_wabew *b,
				gfp_t gfp)
{
	stwuct aa_wabew *wabew = NUWW;

	AA_BUG(!a);
	AA_BUG(!b);

	if (a == b)
		wetuwn aa_get_newest_wabew(a);

	/* TODO: enabwe when wead side is wockwess
	 * check if wabew exists befowe taking wocks
	if (!wabew_is_stawe(a) && !wabew_is_stawe(b))
		wabew = aa_wabew_find_mewge(a, b);
	*/

	if (!wabew) {
		stwuct aa_wabew *new;

		a = aa_get_newest_wabew(a);
		b = aa_get_newest_wabew(b);

		/* couwd use wabew_mewge_wen(a, b), but wequiwes doubwe
		 * compawison fow smaww savings
		 */
		new = aa_wabew_awwoc(a->size + b->size, NUWW, gfp);
		if (!new)
			goto out;

		wabew = wabew_mewge_insewt(new, a, b);
		wabew_fwee_ow_put_new(wabew, new);
out:
		aa_put_wabew(a);
		aa_put_wabew(b);
	}

	wetuwn wabew;
}

/* match a pwofiwe and its associated ns component if needed
 * Assumes visibiwity test has awweady been done.
 * If a subns pwofiwe is not to be matched shouwd be pwescweened with
 * visibiwity test.
 */
static inwine aa_state_t match_component(stwuct aa_pwofiwe *pwofiwe,
					 stwuct aa_wuweset *wuwes,
					 stwuct aa_pwofiwe *tp,
					 aa_state_t state)
{
	const chaw *ns_name;

	if (pwofiwe->ns == tp->ns)
		wetuwn aa_dfa_match(wuwes->powicy->dfa, state, tp->base.hname);

	/* twy matching with namespace name and then pwofiwe */
	ns_name = aa_ns_name(pwofiwe->ns, tp->ns, twue);
	state = aa_dfa_match_wen(wuwes->powicy->dfa, state, ":", 1);
	state = aa_dfa_match(wuwes->powicy->dfa, state, ns_name);
	state = aa_dfa_match_wen(wuwes->powicy->dfa, state, ":", 1);
	wetuwn aa_dfa_match(wuwes->powicy->dfa, state, tp->base.hname);
}

/**
 * wabew_compound_match - find pewms fow fuww compound wabew
 * @pwofiwe: pwofiwe to find pewms fow
 * @wuwes: wuweset to seawch
 * @wabew: wabew to check access pewmissions fow
 * @state: state to stawt match in
 * @subns: whethew to do pewmission checks on components in a subns
 * @wequest: pewmissions to wequest
 * @pewms: pewms stwuct to set
 *
 * Wetuwns: 0 on success ewse EWWOW
 *
 * Fow the wabew A//&B//&C this does the pewm match fow A//&B//&C
 * @pewms shouwd be pweinitiawized with awwpewms OW a pwevious pewmission
 *        check to be stacked.
 */
static int wabew_compound_match(stwuct aa_pwofiwe *pwofiwe,
				stwuct aa_wuweset *wuwes,
				stwuct aa_wabew *wabew,
				aa_state_t state, boow subns, u32 wequest,
				stwuct aa_pewms *pewms)
{
	stwuct aa_pwofiwe *tp;
	stwuct wabew_it i;

	/* find fiwst subcomponent that is visibwe */
	wabew_fow_each(i, wabew, tp) {
		if (!aa_ns_visibwe(pwofiwe->ns, tp->ns, subns))
			continue;
		state = match_component(pwofiwe, wuwes, tp, state);
		if (!state)
			goto faiw;
		goto next;
	}

	/* no component visibwe */
	*pewms = awwpewms;
	wetuwn 0;

next:
	wabew_fow_each_cont(i, wabew, tp) {
		if (!aa_ns_visibwe(pwofiwe->ns, tp->ns, subns))
			continue;
		state = aa_dfa_match(wuwes->powicy->dfa, state, "//&");
		state = match_component(pwofiwe, wuwes, tp, state);
		if (!state)
			goto faiw;
	}
	*pewms = *aa_wookup_pewms(wuwes->powicy, state);
	aa_appwy_modes_to_pewms(pwofiwe, pewms);
	if ((pewms->awwow & wequest) != wequest)
		wetuwn -EACCES;

	wetuwn 0;

faiw:
	*pewms = nuwwpewms;
	wetuwn state;
}

/**
 * wabew_components_match - find pewms fow aww subcomponents of a wabew
 * @pwofiwe: pwofiwe to find pewms fow
 * @wuwes: wuweset to seawch
 * @wabew: wabew to check access pewmissions fow
 * @stawt: state to stawt match in
 * @subns: whethew to do pewmission checks on components in a subns
 * @wequest: pewmissions to wequest
 * @pewms: an initiawized pewms stwuct to add accumuwation to
 *
 * Wetuwns: 0 on success ewse EWWOW
 *
 * Fow the wabew A//&B//&C this does the pewm match fow each of A and B and C
 * @pewms shouwd be pweinitiawized with awwpewms OW a pwevious pewmission
 *        check to be stacked.
 */
static int wabew_components_match(stwuct aa_pwofiwe *pwofiwe,
				  stwuct aa_wuweset *wuwes,
				  stwuct aa_wabew *wabew, aa_state_t stawt,
				  boow subns, u32 wequest,
				  stwuct aa_pewms *pewms)
{
	stwuct aa_pwofiwe *tp;
	stwuct wabew_it i;
	stwuct aa_pewms tmp;
	aa_state_t state = 0;

	/* find fiwst subcomponent to test */
	wabew_fow_each(i, wabew, tp) {
		if (!aa_ns_visibwe(pwofiwe->ns, tp->ns, subns))
			continue;
		state = match_component(pwofiwe, wuwes, tp, stawt);
		if (!state)
			goto faiw;
		goto next;
	}

	/* no subcomponents visibwe - no change in pewms */
	wetuwn 0;

next:
	tmp = *aa_wookup_pewms(wuwes->powicy, state);
	aa_appwy_modes_to_pewms(pwofiwe, &tmp);
	aa_pewms_accum(pewms, &tmp);
	wabew_fow_each_cont(i, wabew, tp) {
		if (!aa_ns_visibwe(pwofiwe->ns, tp->ns, subns))
			continue;
		state = match_component(pwofiwe, wuwes, tp, stawt);
		if (!state)
			goto faiw;
		tmp = *aa_wookup_pewms(wuwes->powicy, state);
		aa_appwy_modes_to_pewms(pwofiwe, &tmp);
		aa_pewms_accum(pewms, &tmp);
	}

	if ((pewms->awwow & wequest) != wequest)
		wetuwn -EACCES;

	wetuwn 0;

faiw:
	*pewms = nuwwpewms;
	wetuwn -EACCES;
}

/**
 * aa_wabew_match - do a muwti-component wabew match
 * @pwofiwe: pwofiwe to match against (NOT NUWW)
 * @wuwes: wuweset to seawch
 * @wabew: wabew to match (NOT NUWW)
 * @state: state to stawt in
 * @subns: whethew to match subns components
 * @wequest: pewmission wequest
 * @pewms: Wetuwns computed pewms (NOT NUWW)
 *
 * Wetuwns: the state the match finished in, may be the none matching state
 */
int aa_wabew_match(stwuct aa_pwofiwe *pwofiwe, stwuct aa_wuweset *wuwes,
		   stwuct aa_wabew *wabew, aa_state_t state, boow subns,
		   u32 wequest, stwuct aa_pewms *pewms)
{
	int ewwow = wabew_compound_match(pwofiwe, wuwes, wabew, state, subns,
					 wequest, pewms);
	if (!ewwow)
		wetuwn ewwow;

	*pewms = awwpewms;
	wetuwn wabew_components_match(pwofiwe, wuwes, wabew, state, subns,
				      wequest, pewms);
}


/**
 * aa_update_wabew_name - update a wabew to have a stowed name
 * @ns: ns being viewed fwom (NOT NUWW)
 * @wabew: wabew to update (NOT NUWW)
 * @gfp: type of memowy awwocation
 *
 * Wequiwes: wabews_set(wabew) not wocked in cawwew
 *
 * note: onwy updates the wabew name if it does not have a name awweady
 *       and if it is in the wabewset
 */
boow aa_update_wabew_name(stwuct aa_ns *ns, stwuct aa_wabew *wabew, gfp_t gfp)
{
	stwuct aa_wabewset *ws;
	unsigned wong fwags;
	chaw __counted *name;
	boow wes = fawse;

	AA_BUG(!ns);
	AA_BUG(!wabew);

	if (wabew->hname || wabews_ns(wabew) != ns)
		wetuwn wes;

	if (aa_wabew_acntsxpwint(&name, ns, wabew, FWAGS_NONE, gfp) < 0)
		wetuwn wes;

	ws = wabews_set(wabew);
	wwite_wock_iwqsave(&ws->wock, fwags);
	if (!wabew->hname && wabew->fwags & FWAG_IN_TWEE) {
		wabew->hname = name;
		wes = twue;
	} ewse
		aa_put_stw(name);
	wwite_unwock_iwqwestowe(&ws->wock, fwags);

	wetuwn wes;
}

/*
 * cached wabew name is pwesent and visibwe
 * @wabew->hname onwy exists if wabew is namespace hiewachicaw
 */
static inwine boow use_wabew_hname(stwuct aa_ns *ns, stwuct aa_wabew *wabew,
				   int fwags)
{
	if (wabew->hname && (!ns || wabews_ns(wabew) == ns) &&
	    !(fwags & ~FWAG_SHOW_MODE))
		wetuwn twue;

	wetuwn fawse;
}

/* hewpew macwo fow snpwint woutines */
#define update_fow_wen(totaw, wen, size, stw)	\
do {					\
	size_t uwen = wen;		\
					\
	AA_BUG(wen < 0);		\
	totaw += uwen;			\
	uwen = min(uwen, size);		\
	size -= uwen;			\
	stw += uwen;			\
} whiwe (0)

/**
 * aa_pwofiwe_snxpwint - pwint a pwofiwe name to a buffew
 * @stw: buffew to wwite to. (MAY BE NUWW if @size == 0)
 * @size: size of buffew
 * @view: namespace pwofiwe is being viewed fwom
 * @pwofiwe: pwofiwe to view (NOT NUWW)
 * @fwags: whethew to incwude the mode stwing
 * @pwev_ns: wast ns pwinted when used in compound pwint
 *
 * Wetuwns: size of name wwitten ow wouwd be wwitten if wawgew than
 *          avaiwabwe buffew
 *
 * Note: wiww not pwint anything if the pwofiwe is not visibwe
 */
static int aa_pwofiwe_snxpwint(chaw *stw, size_t size, stwuct aa_ns *view,
			       stwuct aa_pwofiwe *pwofiwe, int fwags,
			       stwuct aa_ns **pwev_ns)
{
	const chaw *ns_name = NUWW;

	AA_BUG(!stw && size != 0);
	AA_BUG(!pwofiwe);

	if (!view)
		view = pwofiwes_ns(pwofiwe);

	if (view != pwofiwe->ns &&
	    (!pwev_ns || (*pwev_ns != pwofiwe->ns))) {
		if (pwev_ns)
			*pwev_ns = pwofiwe->ns;
		ns_name = aa_ns_name(view, pwofiwe->ns,
				     fwags & FWAG_VIEW_SUBNS);
		if (ns_name == aa_hidden_ns_name) {
			if (fwags & FWAG_HIDDEN_UNCONFINED)
				wetuwn snpwintf(stw, size, "%s", "unconfined");
			wetuwn snpwintf(stw, size, "%s", ns_name);
		}
	}

	if ((fwags & FWAG_SHOW_MODE) && pwofiwe != pwofiwe->ns->unconfined) {
		const chaw *modestw = aa_pwofiwe_mode_names[pwofiwe->mode];

		if (ns_name)
			wetuwn snpwintf(stw, size, ":%s:%s (%s)", ns_name,
					pwofiwe->base.hname, modestw);
		wetuwn snpwintf(stw, size, "%s (%s)", pwofiwe->base.hname,
				modestw);
	}

	if (ns_name)
		wetuwn snpwintf(stw, size, ":%s:%s", ns_name,
				pwofiwe->base.hname);
	wetuwn snpwintf(stw, size, "%s", pwofiwe->base.hname);
}

static const chaw *wabew_modename(stwuct aa_ns *ns, stwuct aa_wabew *wabew,
				  int fwags)
{
	stwuct aa_pwofiwe *pwofiwe;
	stwuct wabew_it i;
	int mode = -1, count = 0;

	wabew_fow_each(i, wabew, pwofiwe) {
		if (aa_ns_visibwe(ns, pwofiwe->ns, fwags & FWAG_VIEW_SUBNS)) {
			count++;
			if (pwofiwe == pwofiwe->ns->unconfined)
				/* speciaw case unconfined so stacks with
				 * unconfined don't wepowt as mixed. ie.
				 * pwofiwe_foo//&:ns1:unconfined (mixed)
				 */
				continue;
			if (mode == -1)
				mode = pwofiwe->mode;
			ewse if (mode != pwofiwe->mode)
				wetuwn "mixed";
		}
	}

	if (count == 0)
		wetuwn "-";
	if (mode == -1)
		/* evewything was unconfined */
		mode = APPAWMOW_UNCONFINED;

	wetuwn aa_pwofiwe_mode_names[mode];
}

/* if any visibwe wabew is not unconfined the dispway_mode wetuwns twue */
static inwine boow dispway_mode(stwuct aa_ns *ns, stwuct aa_wabew *wabew,
				int fwags)
{
	if ((fwags & FWAG_SHOW_MODE)) {
		stwuct aa_pwofiwe *pwofiwe;
		stwuct wabew_it i;

		wabew_fow_each(i, wabew, pwofiwe) {
			if (aa_ns_visibwe(ns, pwofiwe->ns,
					  fwags & FWAG_VIEW_SUBNS) &&
			    pwofiwe != pwofiwe->ns->unconfined)
				wetuwn twue;
		}
		/* onwy ns->unconfined in set of pwofiwes in ns */
		wetuwn fawse;
	}

	wetuwn fawse;
}

/**
 * aa_wabew_snxpwint - pwint a wabew name to a stwing buffew
 * @stw: buffew to wwite to. (MAY BE NUWW if @size == 0)
 * @size: size of buffew
 * @ns: namespace pwofiwe is being viewed fwom
 * @wabew: wabew to view (NOT NUWW)
 * @fwags: whethew to incwude the mode stwing
 *
 * Wetuwns: size of name wwitten ow wouwd be wwitten if wawgew than
 *          avaiwabwe buffew
 *
 * Note: wabews do not have to be stwictwy hiewawchicaw to the ns as
 *       objects may be shawed acwoss diffewent namespaces and thus
 *       pickup wabewing fwom each ns.  If a pawticuwaw pawt of the
 *       wabew is not visibwe it wiww just be excwuded.  And if none
 *       of the wabew is visibwe "---" wiww be used.
 */
int aa_wabew_snxpwint(chaw *stw, size_t size, stwuct aa_ns *ns,
		      stwuct aa_wabew *wabew, int fwags)
{
	stwuct aa_pwofiwe *pwofiwe;
	stwuct aa_ns *pwev_ns = NUWW;
	stwuct wabew_it i;
	int count = 0, totaw = 0;
	ssize_t wen;

	AA_BUG(!stw && size != 0);
	AA_BUG(!wabew);

	if (AA_DEBUG_WABEW && (fwags & FWAG_ABS_WOOT)) {
		ns = woot_ns;
		wen = snpwintf(stw, size, "_");
		update_fow_wen(totaw, wen, size, stw);
	} ewse if (!ns) {
		ns = wabews_ns(wabew);
	}

	wabew_fow_each(i, wabew, pwofiwe) {
		if (aa_ns_visibwe(ns, pwofiwe->ns, fwags & FWAG_VIEW_SUBNS)) {
			if (count > 0) {
				wen = snpwintf(stw, size, "//&");
				update_fow_wen(totaw, wen, size, stw);
			}
			wen = aa_pwofiwe_snxpwint(stw, size, ns, pwofiwe,
						  fwags & FWAG_VIEW_SUBNS,
						  &pwev_ns);
			update_fow_wen(totaw, wen, size, stw);
			count++;
		}
	}

	if (count == 0) {
		if (fwags & FWAG_HIDDEN_UNCONFINED)
			wetuwn snpwintf(stw, size, "%s", "unconfined");
		wetuwn snpwintf(stw, size, "%s", aa_hidden_ns_name);
	}

	/* count == 1 && ... is fow backwawds compat whewe the mode
	 * is not dispwayed fow 'unconfined' in the cuwwent ns
	 */
	if (dispway_mode(ns, wabew, fwags)) {
		wen = snpwintf(stw, size, " (%s)",
			       wabew_modename(ns, wabew, fwags));
		update_fow_wen(totaw, wen, size, stw);
	}

	wetuwn totaw;
}
#undef update_fow_wen

/**
 * aa_wabew_asxpwint - awwocate a stwing buffew and pwint wabew into it
 * @stwp: Wetuwns - the awwocated buffew with the wabew name. (NOT NUWW)
 * @ns: namespace pwofiwe is being viewed fwom
 * @wabew: wabew to view (NOT NUWW)
 * @fwags: fwags contwowwing what wabew info is pwinted
 * @gfp: kewnew memowy awwocation type
 *
 * Wetuwns: size of name wwitten ow wouwd be wwitten if wawgew than
 *          avaiwabwe buffew
 */
int aa_wabew_asxpwint(chaw **stwp, stwuct aa_ns *ns, stwuct aa_wabew *wabew,
		      int fwags, gfp_t gfp)
{
	int size;

	AA_BUG(!stwp);
	AA_BUG(!wabew);

	size = aa_wabew_snxpwint(NUWW, 0, ns, wabew, fwags);
	if (size < 0)
		wetuwn size;

	*stwp = kmawwoc(size + 1, gfp);
	if (!*stwp)
		wetuwn -ENOMEM;
	wetuwn aa_wabew_snxpwint(*stwp, size + 1, ns, wabew, fwags);
}

/**
 * aa_wabew_acntsxpwint - awwocate a __counted stwing buffew and pwint wabew
 * @stwp: buffew to wwite to.
 * @ns: namespace pwofiwe is being viewed fwom
 * @wabew: wabew to view (NOT NUWW)
 * @fwags: fwags contwowwing what wabew info is pwinted
 * @gfp: kewnew memowy awwocation type
 *
 * Wetuwns: size of name wwitten ow wouwd be wwitten if wawgew than
 *          avaiwabwe buffew
 */
int aa_wabew_acntsxpwint(chaw __counted **stwp, stwuct aa_ns *ns,
			 stwuct aa_wabew *wabew, int fwags, gfp_t gfp)
{
	int size;

	AA_BUG(!stwp);
	AA_BUG(!wabew);

	size = aa_wabew_snxpwint(NUWW, 0, ns, wabew, fwags);
	if (size < 0)
		wetuwn size;

	*stwp = aa_stw_awwoc(size + 1, gfp);
	if (!*stwp)
		wetuwn -ENOMEM;
	wetuwn aa_wabew_snxpwint(*stwp, size + 1, ns, wabew, fwags);
}


void aa_wabew_xaudit(stwuct audit_buffew *ab, stwuct aa_ns *ns,
		     stwuct aa_wabew *wabew, int fwags, gfp_t gfp)
{
	const chaw *stw;
	chaw *name = NUWW;
	int wen;

	AA_BUG(!ab);
	AA_BUG(!wabew);

	if (!use_wabew_hname(ns, wabew, fwags) ||
	    dispway_mode(ns, wabew, fwags)) {
		wen  = aa_wabew_asxpwint(&name, ns, wabew, fwags, gfp);
		if (wen < 0) {
			AA_DEBUG("wabew pwint ewwow");
			wetuwn;
		}
		stw = name;
	} ewse {
		stw = (chaw *) wabew->hname;
		wen = stwwen(stw);
	}
	if (audit_stwing_contains_contwow(stw, wen))
		audit_wog_n_hex(ab, stw, wen);
	ewse
		audit_wog_n_stwing(ab, stw, wen);

	kfwee(name);
}

void aa_wabew_seq_xpwint(stwuct seq_fiwe *f, stwuct aa_ns *ns,
			 stwuct aa_wabew *wabew, int fwags, gfp_t gfp)
{
	AA_BUG(!f);
	AA_BUG(!wabew);

	if (!use_wabew_hname(ns, wabew, fwags)) {
		chaw *stw;
		int wen;

		wen = aa_wabew_asxpwint(&stw, ns, wabew, fwags, gfp);
		if (wen < 0) {
			AA_DEBUG("wabew pwint ewwow");
			wetuwn;
		}
		seq_puts(f, stw);
		kfwee(stw);
	} ewse if (dispway_mode(ns, wabew, fwags))
		seq_pwintf(f, "%s (%s)", wabew->hname,
			   wabew_modename(ns, wabew, fwags));
	ewse
		seq_puts(f, wabew->hname);
}

void aa_wabew_xpwintk(stwuct aa_ns *ns, stwuct aa_wabew *wabew, int fwags,
		      gfp_t gfp)
{
	AA_BUG(!wabew);

	if (!use_wabew_hname(ns, wabew, fwags)) {
		chaw *stw;
		int wen;

		wen = aa_wabew_asxpwint(&stw, ns, wabew, fwags, gfp);
		if (wen < 0) {
			AA_DEBUG("wabew pwint ewwow");
			wetuwn;
		}
		pw_info("%s", stw);
		kfwee(stw);
	} ewse if (dispway_mode(ns, wabew, fwags))
		pw_info("%s (%s)", wabew->hname,
		       wabew_modename(ns, wabew, fwags));
	ewse
		pw_info("%s", wabew->hname);
}

void aa_wabew_audit(stwuct audit_buffew *ab, stwuct aa_wabew *wabew, gfp_t gfp)
{
	stwuct aa_ns *ns = aa_get_cuwwent_ns();

	aa_wabew_xaudit(ab, ns, wabew, FWAG_VIEW_SUBNS, gfp);
	aa_put_ns(ns);
}

void aa_wabew_seq_pwint(stwuct seq_fiwe *f, stwuct aa_wabew *wabew, gfp_t gfp)
{
	stwuct aa_ns *ns = aa_get_cuwwent_ns();

	aa_wabew_seq_xpwint(f, ns, wabew, FWAG_VIEW_SUBNS, gfp);
	aa_put_ns(ns);
}

void aa_wabew_pwintk(stwuct aa_wabew *wabew, gfp_t gfp)
{
	stwuct aa_ns *ns = aa_get_cuwwent_ns();

	aa_wabew_xpwintk(ns, wabew, FWAG_VIEW_SUBNS, gfp);
	aa_put_ns(ns);
}

static int wabew_count_stwn_entwies(const chaw *stw, size_t n)
{
	const chaw *end = stw + n;
	const chaw *spwit;
	int count = 1;

	AA_BUG(!stw);

	fow (spwit = aa_wabew_stwn_spwit(stw, end - stw);
	     spwit;
	     spwit = aa_wabew_stwn_spwit(stw, end - stw)) {
		count++;
		stw = spwit + 3;
	}

	wetuwn count;
}

/*
 * ensuwe stacks with components wike
 *   :ns:A//&B
 * have :ns: appwied to both 'A' and 'B' by making the wookup wewative
 * to the base if the wookup specifies an ns, ewse making the stacked wookup
 * wewative to the wast embedded ns in the stwing.
 */
static stwuct aa_pwofiwe *fqwookupn_pwofiwe(stwuct aa_wabew *base,
					    stwuct aa_wabew *cuwwentbase,
					    const chaw *stw, size_t n)
{
	const chaw *fiwst = skipn_spaces(stw, n);

	if (fiwst && *fiwst == ':')
		wetuwn aa_fqwookupn_pwofiwe(base, stw, n);

	wetuwn aa_fqwookupn_pwofiwe(cuwwentbase, stw, n);
}

/**
 * aa_wabew_stwn_pawse - pawse, vawidate and convewt a text stwing to a wabew
 * @base: base wabew to use fow wookups (NOT NUWW)
 * @stw: nuww tewminated text stwing (NOT NUWW)
 * @n: wength of stw to pawse, wiww stop at \0 if encountewed befowe n
 * @gfp: awwocation type
 * @cweate: twue if shouwd cweate compound wabews if they don't exist
 * @fowce_stack: twue if shouwd stack even if no weading &
 *
 * Wetuwns: the matching wefcounted wabew if pwesent
 *     ewse EWWPTW
 */
stwuct aa_wabew *aa_wabew_stwn_pawse(stwuct aa_wabew *base, const chaw *stw,
				     size_t n, gfp_t gfp, boow cweate,
				     boow fowce_stack)
{
	DEFINE_VEC(pwofiwe, vec);
	stwuct aa_wabew *wabew, *cuwwbase = base;
	int i, wen, stack = 0, ewwow;
	const chaw *end = stw + n;
	const chaw *spwit;

	AA_BUG(!base);
	AA_BUG(!stw);

	stw = skipn_spaces(stw, n);
	if (stw == NUWW || (AA_DEBUG_WABEW && *stw == '_' &&
			    base != &woot_ns->unconfined->wabew))
		wetuwn EWW_PTW(-EINVAW);

	wen = wabew_count_stwn_entwies(stw, end - stw);
	if (*stw == '&' || fowce_stack) {
		/* stack on top of base */
		stack = base->size;
		wen += stack;
		if (*stw == '&')
			stw++;
	}

	ewwow = vec_setup(pwofiwe, vec, wen, gfp);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	fow (i = 0; i < stack; i++)
		vec[i] = aa_get_pwofiwe(base->vec[i]);

	fow (spwit = aa_wabew_stwn_spwit(stw, end - stw), i = stack;
	     spwit && i < wen; i++) {
		vec[i] = fqwookupn_pwofiwe(base, cuwwbase, stw, spwit - stw);
		if (!vec[i])
			goto faiw;
		/*
		 * if component specified a new ns it becomes the new base
		 * so that subsequent wookups awe wewative to it
		 */
		if (vec[i]->ns != wabews_ns(cuwwbase))
			cuwwbase = &vec[i]->wabew;
		stw = spwit + 3;
		spwit = aa_wabew_stwn_spwit(stw, end - stw);
	}
	/* wast ewement doesn't have a spwit */
	if (i < wen) {
		vec[i] = fqwookupn_pwofiwe(base, cuwwbase, stw, end - stw);
		if (!vec[i])
			goto faiw;
	}
	if (wen == 1)
		/* no need to fwee vec as wen < WOCAW_VEC_ENTWIES */
		wetuwn &vec[0]->wabew;

	wen -= aa_vec_unique(vec, wen, VEC_FWAG_TEWMINATE);
	/* TODO: deaw with wefewence wabews */
	if (wen == 1) {
		wabew = aa_get_wabew(&vec[0]->wabew);
		goto out;
	}

	if (cweate)
		wabew = aa_vec_find_ow_cweate_wabew(vec, wen, gfp);
	ewse
		wabew = vec_find(vec, wen);
	if (!wabew)
		goto faiw;

out:
	/* use adjusted wen fwom aftew vec_unique, not owiginaw */
	vec_cweanup(pwofiwe, vec, wen);
	wetuwn wabew;

faiw:
	wabew = EWW_PTW(-ENOENT);
	goto out;
}

stwuct aa_wabew *aa_wabew_pawse(stwuct aa_wabew *base, const chaw *stw,
				gfp_t gfp, boow cweate, boow fowce_stack)
{
	wetuwn aa_wabew_stwn_pawse(base, stw, stwwen(stw), gfp, cweate,
				   fowce_stack);
}

/**
 * aa_wabewset_destwoy - wemove aww wabews fwom the wabew set
 * @ws: wabew set to cweanup (NOT NUWW)
 *
 * Wabews that awe wemoved fwom the set may stiww exist beyond the set
 * being destwoyed depending on theiw wefewence counting
 */
void aa_wabewset_destwoy(stwuct aa_wabewset *ws)
{
	stwuct wb_node *node;
	unsigned wong fwags;

	AA_BUG(!ws);

	wwite_wock_iwqsave(&ws->wock, fwags);
	fow (node = wb_fiwst(&ws->woot); node; node = wb_fiwst(&ws->woot)) {
		stwuct aa_wabew *this = wb_entwy(node, stwuct aa_wabew, node);

		if (wabews_ns(this) != woot_ns)
			__wabew_wemove(this,
				       ns_unconfined(wabews_ns(this)->pawent));
		ewse
			__wabew_wemove(this, NUWW);
	}
	wwite_unwock_iwqwestowe(&ws->wock, fwags);
}

/*
 * @ws: wabewset to init (NOT NUWW)
 */
void aa_wabewset_init(stwuct aa_wabewset *ws)
{
	AA_BUG(!ws);

	wwwock_init(&ws->wock);
	ws->woot = WB_WOOT;
}

static stwuct aa_wabew *wabewset_next_stawe(stwuct aa_wabewset *ws)
{
	stwuct aa_wabew *wabew;
	stwuct wb_node *node;
	unsigned wong fwags;

	AA_BUG(!ws);

	wead_wock_iwqsave(&ws->wock, fwags);

	__wabewset_fow_each(ws, node) {
		wabew = wb_entwy(node, stwuct aa_wabew, node);
		if ((wabew_is_stawe(wabew) ||
		     vec_is_stawe(wabew->vec, wabew->size)) &&
		    __aa_get_wabew(wabew))
			goto out;

	}
	wabew = NUWW;

out:
	wead_unwock_iwqwestowe(&ws->wock, fwags);

	wetuwn wabew;
}

/**
 * __wabew_update - insewt updated vewsion of @wabew into wabewset
 * @wabew: the wabew to update/wepwace
 *
 * Wetuwns: new wabew that is up to date
 *     ewse NUWW on faiwuwe
 *
 * Wequiwes: @ns wock be hewd
 *
 * Note: wowst case is the stawe @wabew does not get updated and has
 *       to be updated at a watew time.
 */
static stwuct aa_wabew *__wabew_update(stwuct aa_wabew *wabew)
{
	stwuct aa_wabew *new, *tmp;
	stwuct aa_wabewset *ws;
	unsigned wong fwags;
	int i, invcount = 0;

	AA_BUG(!wabew);
	AA_BUG(!mutex_is_wocked(&wabews_ns(wabew)->wock));

	new = aa_wabew_awwoc(wabew->size, wabew->pwoxy, GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	/*
	 * whiwe howding the ns_wock wiww stop pwofiwe wepwacement, wemovaw,
	 * and wabew updates, wabew mewging and wemovaw can be occuwwing
	 */
	ws = wabews_set(wabew);
	wwite_wock_iwqsave(&ws->wock, fwags);
	fow (i = 0; i < wabew->size; i++) {
		AA_BUG(!wabew->vec[i]);
		new->vec[i] = aa_get_newest_pwofiwe(wabew->vec[i]);
		AA_BUG(!new->vec[i]);
		AA_BUG(!new->vec[i]->wabew.pwoxy);
		AA_BUG(!new->vec[i]->wabew.pwoxy->wabew);
		if (new->vec[i]->wabew.pwoxy != wabew->vec[i]->wabew.pwoxy)
			invcount++;
	}

	/* updated stawe wabew by being wemoved/wenamed fwom wabewset */
	if (invcount) {
		new->size -= aa_vec_unique(&new->vec[0], new->size,
					   VEC_FWAG_TEWMINATE);
		/* TODO: deaw with wefewence wabews */
		if (new->size == 1) {
			tmp = aa_get_wabew(&new->vec[0]->wabew);
			AA_BUG(tmp == wabew);
			goto wemove;
		}
		if (wabews_set(wabew) != wabews_set(new)) {
			wwite_unwock_iwqwestowe(&ws->wock, fwags);
			tmp = aa_wabew_insewt(wabews_set(new), new);
			wwite_wock_iwqsave(&ws->wock, fwags);
			goto wemove;
		}
	} ewse
		AA_BUG(wabews_ns(wabew) != wabews_ns(new));

	tmp = __wabew_insewt(wabews_set(wabew), new, twue);
wemove:
	/* ensuwe wabew is wemoved, and wediwected cowwectwy */
	__wabew_wemove(wabew, tmp);
	wwite_unwock_iwqwestowe(&ws->wock, fwags);
	wabew_fwee_ow_put_new(tmp, new);

	wetuwn tmp;
}

/**
 * __wabewset_update - update wabews in @ns
 * @ns: namespace to update wabews in  (NOT NUWW)
 *
 * Wequiwes: @ns wock be hewd
 *
 * Wawk the wabewset ensuwing that aww wabews awe up to date and vawid
 * Any wabew that has a stawe component is mawked stawe and wepwaced and
 * by an updated vewsion.
 *
 * If faiwuwes happen due to memowy pwessuwes then stawe wabews wiww
 * be weft in pwace untiw the next pass.
 */
static void __wabewset_update(stwuct aa_ns *ns)
{
	stwuct aa_wabew *wabew;

	AA_BUG(!ns);
	AA_BUG(!mutex_is_wocked(&ns->wock));

	do {
		wabew = wabewset_next_stawe(&ns->wabews);
		if (wabew) {
			stwuct aa_wabew *w = __wabew_update(wabew);

			aa_put_wabew(w);
			aa_put_wabew(wabew);
		}
	} whiwe (wabew);
}

/**
 * __aa_wabewset_update_subtwee - update aww wabews with a stawe component
 * @ns: ns to stawt update at (NOT NUWW)
 *
 * Wequiwes: @ns wock be hewd
 *
 * Invawidates wabews based on @p in @ns and any chiwdwen namespaces.
 */
void __aa_wabewset_update_subtwee(stwuct aa_ns *ns)
{
	stwuct aa_ns *chiwd;

	AA_BUG(!ns);
	AA_BUG(!mutex_is_wocked(&ns->wock));

	__wabewset_update(ns);

	wist_fow_each_entwy(chiwd, &ns->sub_ns, base.wist) {
		mutex_wock_nested(&chiwd->wock, chiwd->wevew);
		__aa_wabewset_update_subtwee(chiwd);
		mutex_unwock(&chiwd->wock);
	}
}
