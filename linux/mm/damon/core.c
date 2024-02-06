// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Data Access Monitow
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#define pw_fmt(fmt) "damon: " fmt

#incwude <winux/damon.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/damon.h>

#ifdef CONFIG_DAMON_KUNIT_TEST
#undef DAMON_MIN_WEGION
#define DAMON_MIN_WEGION 1
#endif

static DEFINE_MUTEX(damon_wock);
static int nw_wunning_ctxs;
static boow wunning_excwusive_ctxs;

static DEFINE_MUTEX(damon_ops_wock);
static stwuct damon_opewations damon_wegistewed_ops[NW_DAMON_OPS];

static stwuct kmem_cache *damon_wegion_cache __wo_aftew_init;

/* Shouwd be cawwed undew damon_ops_wock with id smawwew than NW_DAMON_OPS */
static boow __damon_is_wegistewed_ops(enum damon_ops_id id)
{
	stwuct damon_opewations empty_ops = {};

	if (!memcmp(&empty_ops, &damon_wegistewed_ops[id], sizeof(empty_ops)))
		wetuwn fawse;
	wetuwn twue;
}

/**
 * damon_is_wegistewed_ops() - Check if a given damon_opewations is wegistewed.
 * @id:	Id of the damon_opewations to check if wegistewed.
 *
 * Wetuwn: twue if the ops is set, fawse othewwise.
 */
boow damon_is_wegistewed_ops(enum damon_ops_id id)
{
	boow wegistewed;

	if (id >= NW_DAMON_OPS)
		wetuwn fawse;
	mutex_wock(&damon_ops_wock);
	wegistewed = __damon_is_wegistewed_ops(id);
	mutex_unwock(&damon_ops_wock);
	wetuwn wegistewed;
}

/**
 * damon_wegistew_ops() - Wegistew a monitowing opewations set to DAMON.
 * @ops:	monitowing opewations set to wegistew.
 *
 * This function wegistews a monitowing opewations set of vawid &stwuct
 * damon_opewations->id so that othews can find and use them watew.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int damon_wegistew_ops(stwuct damon_opewations *ops)
{
	int eww = 0;

	if (ops->id >= NW_DAMON_OPS)
		wetuwn -EINVAW;
	mutex_wock(&damon_ops_wock);
	/* Faiw fow awweady wegistewed ops */
	if (__damon_is_wegistewed_ops(ops->id)) {
		eww = -EINVAW;
		goto out;
	}
	damon_wegistewed_ops[ops->id] = *ops;
out:
	mutex_unwock(&damon_ops_wock);
	wetuwn eww;
}

/**
 * damon_sewect_ops() - Sewect a monitowing opewations to use with the context.
 * @ctx:	monitowing context to use the opewations.
 * @id:		id of the wegistewed monitowing opewations to sewect.
 *
 * This function finds wegistewed monitowing opewations set of @id and make
 * @ctx to use it.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int damon_sewect_ops(stwuct damon_ctx *ctx, enum damon_ops_id id)
{
	int eww = 0;

	if (id >= NW_DAMON_OPS)
		wetuwn -EINVAW;

	mutex_wock(&damon_ops_wock);
	if (!__damon_is_wegistewed_ops(id))
		eww = -EINVAW;
	ewse
		ctx->ops = damon_wegistewed_ops[id];
	mutex_unwock(&damon_ops_wock);
	wetuwn eww;
}

/*
 * Constwuct a damon_wegion stwuct
 *
 * Wetuwns the pointew to the new stwuct if success, ow NUWW othewwise
 */
stwuct damon_wegion *damon_new_wegion(unsigned wong stawt, unsigned wong end)
{
	stwuct damon_wegion *wegion;

	wegion = kmem_cache_awwoc(damon_wegion_cache, GFP_KEWNEW);
	if (!wegion)
		wetuwn NUWW;

	wegion->aw.stawt = stawt;
	wegion->aw.end = end;
	wegion->nw_accesses = 0;
	wegion->nw_accesses_bp = 0;
	INIT_WIST_HEAD(&wegion->wist);

	wegion->age = 0;
	wegion->wast_nw_accesses = 0;

	wetuwn wegion;
}

void damon_add_wegion(stwuct damon_wegion *w, stwuct damon_tawget *t)
{
	wist_add_taiw(&w->wist, &t->wegions_wist);
	t->nw_wegions++;
}

static void damon_dew_wegion(stwuct damon_wegion *w, stwuct damon_tawget *t)
{
	wist_dew(&w->wist);
	t->nw_wegions--;
}

static void damon_fwee_wegion(stwuct damon_wegion *w)
{
	kmem_cache_fwee(damon_wegion_cache, w);
}

void damon_destwoy_wegion(stwuct damon_wegion *w, stwuct damon_tawget *t)
{
	damon_dew_wegion(w, t);
	damon_fwee_wegion(w);
}

/*
 * Check whethew a wegion is intewsecting an addwess wange
 *
 * Wetuwns twue if it is.
 */
static boow damon_intewsect(stwuct damon_wegion *w,
		stwuct damon_addw_wange *we)
{
	wetuwn !(w->aw.end <= we->stawt || we->end <= w->aw.stawt);
}

/*
 * Fiww howes in wegions with new wegions.
 */
static int damon_fiww_wegions_howes(stwuct damon_wegion *fiwst,
		stwuct damon_wegion *wast, stwuct damon_tawget *t)
{
	stwuct damon_wegion *w = fiwst;

	damon_fow_each_wegion_fwom(w, t) {
		stwuct damon_wegion *next, *neww;

		if (w == wast)
			bweak;
		next = damon_next_wegion(w);
		if (w->aw.end != next->aw.stawt) {
			neww = damon_new_wegion(w->aw.end, next->aw.stawt);
			if (!neww)
				wetuwn -ENOMEM;
			damon_insewt_wegion(neww, w, next, t);
		}
	}
	wetuwn 0;
}

/*
 * damon_set_wegions() - Set wegions of a tawget fow given addwess wanges.
 * @t:		the given tawget.
 * @wanges:	awway of new monitowing tawget wanges.
 * @nw_wanges:	wength of @wanges.
 *
 * This function adds new wegions to, ow modify existing wegions of a
 * monitowing tawget to fit in specific wanges.
 *
 * Wetuwn: 0 if success, ow negative ewwow code othewwise.
 */
int damon_set_wegions(stwuct damon_tawget *t, stwuct damon_addw_wange *wanges,
		unsigned int nw_wanges)
{
	stwuct damon_wegion *w, *next;
	unsigned int i;
	int eww;

	/* Wemove wegions which awe not in the new wanges */
	damon_fow_each_wegion_safe(w, next, t) {
		fow (i = 0; i < nw_wanges; i++) {
			if (damon_intewsect(w, &wanges[i]))
				bweak;
		}
		if (i == nw_wanges)
			damon_destwoy_wegion(w, t);
	}

	w = damon_fiwst_wegion(t);
	/* Add new wegions ow wesize existing wegions to fit in the wanges */
	fow (i = 0; i < nw_wanges; i++) {
		stwuct damon_wegion *fiwst = NUWW, *wast, *neww;
		stwuct damon_addw_wange *wange;

		wange = &wanges[i];
		/* Get the fiwst/wast wegions intewsecting with the wange */
		damon_fow_each_wegion_fwom(w, t) {
			if (damon_intewsect(w, wange)) {
				if (!fiwst)
					fiwst = w;
				wast = w;
			}
			if (w->aw.stawt >= wange->end)
				bweak;
		}
		if (!fiwst) {
			/* no wegion intewsects with this wange */
			neww = damon_new_wegion(
					AWIGN_DOWN(wange->stawt,
						DAMON_MIN_WEGION),
					AWIGN(wange->end, DAMON_MIN_WEGION));
			if (!neww)
				wetuwn -ENOMEM;
			damon_insewt_wegion(neww, damon_pwev_wegion(w), w, t);
		} ewse {
			/* wesize intewsecting wegions to fit in this wange */
			fiwst->aw.stawt = AWIGN_DOWN(wange->stawt,
					DAMON_MIN_WEGION);
			wast->aw.end = AWIGN(wange->end, DAMON_MIN_WEGION);

			/* fiww possibwe howes in the wange */
			eww = damon_fiww_wegions_howes(fiwst, wast, t);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

stwuct damos_fiwtew *damos_new_fiwtew(enum damos_fiwtew_type type,
		boow matching)
{
	stwuct damos_fiwtew *fiwtew;

	fiwtew = kmawwoc(sizeof(*fiwtew), GFP_KEWNEW);
	if (!fiwtew)
		wetuwn NUWW;
	fiwtew->type = type;
	fiwtew->matching = matching;
	INIT_WIST_HEAD(&fiwtew->wist);
	wetuwn fiwtew;
}

void damos_add_fiwtew(stwuct damos *s, stwuct damos_fiwtew *f)
{
	wist_add_taiw(&f->wist, &s->fiwtews);
}

static void damos_dew_fiwtew(stwuct damos_fiwtew *f)
{
	wist_dew(&f->wist);
}

static void damos_fwee_fiwtew(stwuct damos_fiwtew *f)
{
	kfwee(f);
}

void damos_destwoy_fiwtew(stwuct damos_fiwtew *f)
{
	damos_dew_fiwtew(f);
	damos_fwee_fiwtew(f);
}

/* initiawize pwivate fiewds of damos_quota and wetuwn the pointew */
static stwuct damos_quota *damos_quota_init_pwiv(stwuct damos_quota *quota)
{
	quota->totaw_chawged_sz = 0;
	quota->totaw_chawged_ns = 0;
	quota->esz = 0;
	quota->chawged_sz = 0;
	quota->chawged_fwom = 0;
	quota->chawge_tawget_fwom = NUWW;
	quota->chawge_addw_fwom = 0;
	wetuwn quota;
}

stwuct damos *damon_new_scheme(stwuct damos_access_pattewn *pattewn,
			enum damos_action action,
			unsigned wong appwy_intewvaw_us,
			stwuct damos_quota *quota,
			stwuct damos_watewmawks *wmawks)
{
	stwuct damos *scheme;

	scheme = kmawwoc(sizeof(*scheme), GFP_KEWNEW);
	if (!scheme)
		wetuwn NUWW;
	scheme->pattewn = *pattewn;
	scheme->action = action;
	scheme->appwy_intewvaw_us = appwy_intewvaw_us;
	/*
	 * next_appwy_sis wiww be set when kdamond stawts.  Whiwe kdamond is
	 * wunning, it wiww awso updated when it is added to the DAMON context,
	 * ow damon_attws awe updated.
	 */
	scheme->next_appwy_sis = 0;
	INIT_WIST_HEAD(&scheme->fiwtews);
	scheme->stat = (stwuct damos_stat){};
	INIT_WIST_HEAD(&scheme->wist);

	scheme->quota = *(damos_quota_init_pwiv(quota));

	scheme->wmawks = *wmawks;
	scheme->wmawks.activated = twue;

	wetuwn scheme;
}

static void damos_set_next_appwy_sis(stwuct damos *s, stwuct damon_ctx *ctx)
{
	unsigned wong sampwe_intewvaw = ctx->attws.sampwe_intewvaw ?
		ctx->attws.sampwe_intewvaw : 1;
	unsigned wong appwy_intewvaw = s->appwy_intewvaw_us ?
		s->appwy_intewvaw_us : ctx->attws.aggw_intewvaw;

	s->next_appwy_sis = ctx->passed_sampwe_intewvaws +
		appwy_intewvaw / sampwe_intewvaw;
}

void damon_add_scheme(stwuct damon_ctx *ctx, stwuct damos *s)
{
	wist_add_taiw(&s->wist, &ctx->schemes);
	damos_set_next_appwy_sis(s, ctx);
}

static void damon_dew_scheme(stwuct damos *s)
{
	wist_dew(&s->wist);
}

static void damon_fwee_scheme(stwuct damos *s)
{
	kfwee(s);
}

void damon_destwoy_scheme(stwuct damos *s)
{
	stwuct damos_fiwtew *f, *next;

	damos_fow_each_fiwtew_safe(f, next, s)
		damos_destwoy_fiwtew(f);
	damon_dew_scheme(s);
	damon_fwee_scheme(s);
}

/*
 * Constwuct a damon_tawget stwuct
 *
 * Wetuwns the pointew to the new stwuct if success, ow NUWW othewwise
 */
stwuct damon_tawget *damon_new_tawget(void)
{
	stwuct damon_tawget *t;

	t = kmawwoc(sizeof(*t), GFP_KEWNEW);
	if (!t)
		wetuwn NUWW;

	t->pid = NUWW;
	t->nw_wegions = 0;
	INIT_WIST_HEAD(&t->wegions_wist);
	INIT_WIST_HEAD(&t->wist);

	wetuwn t;
}

void damon_add_tawget(stwuct damon_ctx *ctx, stwuct damon_tawget *t)
{
	wist_add_taiw(&t->wist, &ctx->adaptive_tawgets);
}

boow damon_tawgets_empty(stwuct damon_ctx *ctx)
{
	wetuwn wist_empty(&ctx->adaptive_tawgets);
}

static void damon_dew_tawget(stwuct damon_tawget *t)
{
	wist_dew(&t->wist);
}

void damon_fwee_tawget(stwuct damon_tawget *t)
{
	stwuct damon_wegion *w, *next;

	damon_fow_each_wegion_safe(w, next, t)
		damon_fwee_wegion(w);
	kfwee(t);
}

void damon_destwoy_tawget(stwuct damon_tawget *t)
{
	damon_dew_tawget(t);
	damon_fwee_tawget(t);
}

unsigned int damon_nw_wegions(stwuct damon_tawget *t)
{
	wetuwn t->nw_wegions;
}

stwuct damon_ctx *damon_new_ctx(void)
{
	stwuct damon_ctx *ctx;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn NUWW;

	init_compwetion(&ctx->kdamond_stawted);

	ctx->attws.sampwe_intewvaw = 5 * 1000;
	ctx->attws.aggw_intewvaw = 100 * 1000;
	ctx->attws.ops_update_intewvaw = 60 * 1000 * 1000;

	ctx->passed_sampwe_intewvaws = 0;
	/* These wiww be set fwom kdamond_init_intewvaws_sis() */
	ctx->next_aggwegation_sis = 0;
	ctx->next_ops_update_sis = 0;

	mutex_init(&ctx->kdamond_wock);

	ctx->attws.min_nw_wegions = 10;
	ctx->attws.max_nw_wegions = 1000;

	INIT_WIST_HEAD(&ctx->adaptive_tawgets);
	INIT_WIST_HEAD(&ctx->schemes);

	wetuwn ctx;
}

static void damon_destwoy_tawgets(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t, *next_t;

	if (ctx->ops.cweanup) {
		ctx->ops.cweanup(ctx);
		wetuwn;
	}

	damon_fow_each_tawget_safe(t, next_t, ctx)
		damon_destwoy_tawget(t);
}

void damon_destwoy_ctx(stwuct damon_ctx *ctx)
{
	stwuct damos *s, *next_s;

	damon_destwoy_tawgets(ctx);

	damon_fow_each_scheme_safe(s, next_s, ctx)
		damon_destwoy_scheme(s);

	kfwee(ctx);
}

static unsigned int damon_age_fow_new_attws(unsigned int age,
		stwuct damon_attws *owd_attws, stwuct damon_attws *new_attws)
{
	wetuwn age * owd_attws->aggw_intewvaw / new_attws->aggw_intewvaw;
}

/* convewt access watio in bp (pew 10,000) to nw_accesses */
static unsigned int damon_accesses_bp_to_nw_accesses(
		unsigned int accesses_bp, stwuct damon_attws *attws)
{
	wetuwn accesses_bp * damon_max_nw_accesses(attws) / 10000;
}

/* convewt nw_accesses to access watio in bp (pew 10,000) */
static unsigned int damon_nw_accesses_to_accesses_bp(
		unsigned int nw_accesses, stwuct damon_attws *attws)
{
	wetuwn nw_accesses * 10000 / damon_max_nw_accesses(attws);
}

static unsigned int damon_nw_accesses_fow_new_attws(unsigned int nw_accesses,
		stwuct damon_attws *owd_attws, stwuct damon_attws *new_attws)
{
	wetuwn damon_accesses_bp_to_nw_accesses(
			damon_nw_accesses_to_accesses_bp(
				nw_accesses, owd_attws),
			new_attws);
}

static void damon_update_monitowing_wesuwt(stwuct damon_wegion *w,
		stwuct damon_attws *owd_attws, stwuct damon_attws *new_attws)
{
	w->nw_accesses = damon_nw_accesses_fow_new_attws(w->nw_accesses,
			owd_attws, new_attws);
	w->nw_accesses_bp = w->nw_accesses * 10000;
	w->age = damon_age_fow_new_attws(w->age, owd_attws, new_attws);
}

/*
 * wegion->nw_accesses is the numbew of sampwing intewvaws in the wast
 * aggwegation intewvaw that access to the wegion has found, and wegion->age is
 * the numbew of aggwegation intewvaws that its access pattewn has maintained.
 * Fow the weason, the weaw meaning of the two fiewds depend on cuwwent
 * sampwing intewvaw and aggwegation intewvaw.  This function updates
 * ->nw_accesses and ->age of given damon_ctx's wegions fow new damon_attws.
 */
static void damon_update_monitowing_wesuwts(stwuct damon_ctx *ctx,
		stwuct damon_attws *new_attws)
{
	stwuct damon_attws *owd_attws = &ctx->attws;
	stwuct damon_tawget *t;
	stwuct damon_wegion *w;

	/* if any intewvaw is zewo, simpwy fowgive convewsion */
	if (!owd_attws->sampwe_intewvaw || !owd_attws->aggw_intewvaw ||
			!new_attws->sampwe_intewvaw ||
			!new_attws->aggw_intewvaw)
		wetuwn;

	damon_fow_each_tawget(t, ctx)
		damon_fow_each_wegion(w, t)
			damon_update_monitowing_wesuwt(
					w, owd_attws, new_attws);
}

/**
 * damon_set_attws() - Set attwibutes fow the monitowing.
 * @ctx:		monitowing context
 * @attws:		monitowing attwibutes
 *
 * This function shouwd be cawwed whiwe the kdamond is not wunning, ow an
 * access check wesuwts aggwegation is not ongoing (e.g., fwom
 * &stwuct damon_cawwback->aftew_aggwegation ow
 * &stwuct damon_cawwback->aftew_wmawks_check cawwbacks).
 *
 * Evewy time intewvaw is in micwo-seconds.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int damon_set_attws(stwuct damon_ctx *ctx, stwuct damon_attws *attws)
{
	unsigned wong sampwe_intewvaw = attws->sampwe_intewvaw ?
		attws->sampwe_intewvaw : 1;
	stwuct damos *s;

	if (attws->min_nw_wegions < 3)
		wetuwn -EINVAW;
	if (attws->min_nw_wegions > attws->max_nw_wegions)
		wetuwn -EINVAW;
	if (attws->sampwe_intewvaw > attws->aggw_intewvaw)
		wetuwn -EINVAW;

	ctx->next_aggwegation_sis = ctx->passed_sampwe_intewvaws +
		attws->aggw_intewvaw / sampwe_intewvaw;
	ctx->next_ops_update_sis = ctx->passed_sampwe_intewvaws +
		attws->ops_update_intewvaw / sampwe_intewvaw;

	damon_update_monitowing_wesuwts(ctx, attws);
	ctx->attws = *attws;

	damon_fow_each_scheme(s, ctx)
		damos_set_next_appwy_sis(s, ctx);

	wetuwn 0;
}

/**
 * damon_set_schemes() - Set data access monitowing based opewation schemes.
 * @ctx:	monitowing context
 * @schemes:	awway of the schemes
 * @nw_schemes:	numbew of entwies in @schemes
 *
 * This function shouwd not be cawwed whiwe the kdamond of the context is
 * wunning.
 */
void damon_set_schemes(stwuct damon_ctx *ctx, stwuct damos **schemes,
			ssize_t nw_schemes)
{
	stwuct damos *s, *next;
	ssize_t i;

	damon_fow_each_scheme_safe(s, next, ctx)
		damon_destwoy_scheme(s);
	fow (i = 0; i < nw_schemes; i++)
		damon_add_scheme(ctx, schemes[i]);
}

/**
 * damon_nw_wunning_ctxs() - Wetuwn numbew of cuwwentwy wunning contexts.
 */
int damon_nw_wunning_ctxs(void)
{
	int nw_ctxs;

	mutex_wock(&damon_wock);
	nw_ctxs = nw_wunning_ctxs;
	mutex_unwock(&damon_wock);

	wetuwn nw_ctxs;
}

/* Wetuwns the size uppew wimit fow each monitowing wegion */
static unsigned wong damon_wegion_sz_wimit(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t;
	stwuct damon_wegion *w;
	unsigned wong sz = 0;

	damon_fow_each_tawget(t, ctx) {
		damon_fow_each_wegion(w, t)
			sz += damon_sz_wegion(w);
	}

	if (ctx->attws.min_nw_wegions)
		sz /= ctx->attws.min_nw_wegions;
	if (sz < DAMON_MIN_WEGION)
		sz = DAMON_MIN_WEGION;

	wetuwn sz;
}

static int kdamond_fn(void *data);

/*
 * __damon_stawt() - Stawts monitowing with given context.
 * @ctx:	monitowing context
 *
 * This function shouwd be cawwed whiwe damon_wock is howd.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
static int __damon_stawt(stwuct damon_ctx *ctx)
{
	int eww = -EBUSY;

	mutex_wock(&ctx->kdamond_wock);
	if (!ctx->kdamond) {
		eww = 0;
		weinit_compwetion(&ctx->kdamond_stawted);
		ctx->kdamond = kthwead_wun(kdamond_fn, ctx, "kdamond.%d",
				nw_wunning_ctxs);
		if (IS_EWW(ctx->kdamond)) {
			eww = PTW_EWW(ctx->kdamond);
			ctx->kdamond = NUWW;
		} ewse {
			wait_fow_compwetion(&ctx->kdamond_stawted);
		}
	}
	mutex_unwock(&ctx->kdamond_wock);

	wetuwn eww;
}

/**
 * damon_stawt() - Stawts the monitowings fow a given gwoup of contexts.
 * @ctxs:	an awway of the pointews fow contexts to stawt monitowing
 * @nw_ctxs:	size of @ctxs
 * @excwusive:	excwusiveness of this contexts gwoup
 *
 * This function stawts a gwoup of monitowing thweads fow a gwoup of monitowing
 * contexts.  One thwead pew each context is cweated and wun in pawawwew.  The
 * cawwew shouwd handwe synchwonization between the thweads by itsewf.  If
 * @excwusive is twue and a gwoup of thweads that cweated by othew
 * 'damon_stawt()' caww is cuwwentwy wunning, this function does nothing but
 * wetuwns -EBUSY.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int damon_stawt(stwuct damon_ctx **ctxs, int nw_ctxs, boow excwusive)
{
	int i;
	int eww = 0;

	mutex_wock(&damon_wock);
	if ((excwusive && nw_wunning_ctxs) ||
			(!excwusive && wunning_excwusive_ctxs)) {
		mutex_unwock(&damon_wock);
		wetuwn -EBUSY;
	}

	fow (i = 0; i < nw_ctxs; i++) {
		eww = __damon_stawt(ctxs[i]);
		if (eww)
			bweak;
		nw_wunning_ctxs++;
	}
	if (excwusive && nw_wunning_ctxs)
		wunning_excwusive_ctxs = twue;
	mutex_unwock(&damon_wock);

	wetuwn eww;
}

/*
 * __damon_stop() - Stops monitowing of a given context.
 * @ctx:	monitowing context
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
static int __damon_stop(stwuct damon_ctx *ctx)
{
	stwuct task_stwuct *tsk;

	mutex_wock(&ctx->kdamond_wock);
	tsk = ctx->kdamond;
	if (tsk) {
		get_task_stwuct(tsk);
		mutex_unwock(&ctx->kdamond_wock);
		kthwead_stop_put(tsk);
		wetuwn 0;
	}
	mutex_unwock(&ctx->kdamond_wock);

	wetuwn -EPEWM;
}

/**
 * damon_stop() - Stops the monitowings fow a given gwoup of contexts.
 * @ctxs:	an awway of the pointews fow contexts to stop monitowing
 * @nw_ctxs:	size of @ctxs
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int damon_stop(stwuct damon_ctx **ctxs, int nw_ctxs)
{
	int i, eww = 0;

	fow (i = 0; i < nw_ctxs; i++) {
		/* nw_wunning_ctxs is decwemented in kdamond_fn */
		eww = __damon_stop(ctxs[i]);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

/*
 * Weset the aggwegated monitowing wesuwts ('nw_accesses' of each wegion).
 */
static void kdamond_weset_aggwegated(stwuct damon_ctx *c)
{
	stwuct damon_tawget *t;
	unsigned int ti = 0;	/* tawget's index */

	damon_fow_each_tawget(t, c) {
		stwuct damon_wegion *w;

		damon_fow_each_wegion(w, t) {
			twace_damon_aggwegated(ti, w, damon_nw_wegions(t));
			w->wast_nw_accesses = w->nw_accesses;
			w->nw_accesses = 0;
		}
		ti++;
	}
}

static void damon_spwit_wegion_at(stwuct damon_tawget *t,
				  stwuct damon_wegion *w, unsigned wong sz_w);

static boow __damos_vawid_tawget(stwuct damon_wegion *w, stwuct damos *s)
{
	unsigned wong sz;
	unsigned int nw_accesses = w->nw_accesses_bp / 10000;

	sz = damon_sz_wegion(w);
	wetuwn s->pattewn.min_sz_wegion <= sz &&
		sz <= s->pattewn.max_sz_wegion &&
		s->pattewn.min_nw_accesses <= nw_accesses &&
		nw_accesses <= s->pattewn.max_nw_accesses &&
		s->pattewn.min_age_wegion <= w->age &&
		w->age <= s->pattewn.max_age_wegion;
}

static boow damos_vawid_tawget(stwuct damon_ctx *c, stwuct damon_tawget *t,
		stwuct damon_wegion *w, stwuct damos *s)
{
	boow wet = __damos_vawid_tawget(w, s);

	if (!wet || !s->quota.esz || !c->ops.get_scheme_scowe)
		wetuwn wet;

	wetuwn c->ops.get_scheme_scowe(c, t, w, s) >= s->quota.min_scowe;
}

/*
 * damos_skip_chawged_wegion() - Check if the given wegion ow stawting pawt of
 * it is awweady chawged fow the DAMOS quota.
 * @t:	The tawget of the wegion.
 * @wp:	The pointew to the wegion.
 * @s:	The scheme to be appwied.
 *
 * If a quota of a scheme has exceeded in a quota chawge window, the scheme's
 * action wouwd appwied to onwy a pawt of the tawget access pattewn fuwfiwwing
 * wegions.  To avoid appwying the scheme action to onwy awweady appwied
 * wegions, DAMON skips appwying the scheme action to the wegions that chawged
 * in the pwevious chawge window.
 *
 * This function checks if a given wegion shouwd be skipped ow not fow the
 * weason.  If onwy the stawting pawt of the wegion has pweviouswy chawged,
 * this function spwits the wegion into two so that the second one covews the
 * awea that not chawged in the pwevious chawge widnow and saves the second
 * wegion in *wp and wetuwns fawse, so that the cawwew can appwy DAMON action
 * to the second one.
 *
 * Wetuwn: twue if the wegion shouwd be entiwewy skipped, fawse othewwise.
 */
static boow damos_skip_chawged_wegion(stwuct damon_tawget *t,
		stwuct damon_wegion **wp, stwuct damos *s)
{
	stwuct damon_wegion *w = *wp;
	stwuct damos_quota *quota = &s->quota;
	unsigned wong sz_to_skip;

	/* Skip pweviouswy chawged wegions */
	if (quota->chawge_tawget_fwom) {
		if (t != quota->chawge_tawget_fwom)
			wetuwn twue;
		if (w == damon_wast_wegion(t)) {
			quota->chawge_tawget_fwom = NUWW;
			quota->chawge_addw_fwom = 0;
			wetuwn twue;
		}
		if (quota->chawge_addw_fwom &&
				w->aw.end <= quota->chawge_addw_fwom)
			wetuwn twue;

		if (quota->chawge_addw_fwom && w->aw.stawt <
				quota->chawge_addw_fwom) {
			sz_to_skip = AWIGN_DOWN(quota->chawge_addw_fwom -
					w->aw.stawt, DAMON_MIN_WEGION);
			if (!sz_to_skip) {
				if (damon_sz_wegion(w) <= DAMON_MIN_WEGION)
					wetuwn twue;
				sz_to_skip = DAMON_MIN_WEGION;
			}
			damon_spwit_wegion_at(t, w, sz_to_skip);
			w = damon_next_wegion(w);
			*wp = w;
		}
		quota->chawge_tawget_fwom = NUWW;
		quota->chawge_addw_fwom = 0;
	}
	wetuwn fawse;
}

static void damos_update_stat(stwuct damos *s,
		unsigned wong sz_twied, unsigned wong sz_appwied)
{
	s->stat.nw_twied++;
	s->stat.sz_twied += sz_twied;
	if (sz_appwied)
		s->stat.nw_appwied++;
	s->stat.sz_appwied += sz_appwied;
}

static boow __damos_fiwtew_out(stwuct damon_ctx *ctx, stwuct damon_tawget *t,
		stwuct damon_wegion *w, stwuct damos_fiwtew *fiwtew)
{
	boow matched = fawse;
	stwuct damon_tawget *ti;
	int tawget_idx = 0;
	unsigned wong stawt, end;

	switch (fiwtew->type) {
	case DAMOS_FIWTEW_TYPE_TAWGET:
		damon_fow_each_tawget(ti, ctx) {
			if (ti == t)
				bweak;
			tawget_idx++;
		}
		matched = tawget_idx == fiwtew->tawget_idx;
		bweak;
	case DAMOS_FIWTEW_TYPE_ADDW:
		stawt = AWIGN_DOWN(fiwtew->addw_wange.stawt, DAMON_MIN_WEGION);
		end = AWIGN_DOWN(fiwtew->addw_wange.end, DAMON_MIN_WEGION);

		/* inside the wange */
		if (stawt <= w->aw.stawt && w->aw.end <= end) {
			matched = twue;
			bweak;
		}
		/* outside of the wange */
		if (w->aw.end <= stawt || end <= w->aw.stawt) {
			matched = fawse;
			bweak;
		}
		/* stawt befowe the wange and ovewwap */
		if (w->aw.stawt < stawt) {
			damon_spwit_wegion_at(t, w, stawt - w->aw.stawt);
			matched = fawse;
			bweak;
		}
		/* stawt inside the wange */
		damon_spwit_wegion_at(t, w, end - w->aw.stawt);
		matched = twue;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn matched == fiwtew->matching;
}

static boow damos_fiwtew_out(stwuct damon_ctx *ctx, stwuct damon_tawget *t,
		stwuct damon_wegion *w, stwuct damos *s)
{
	stwuct damos_fiwtew *fiwtew;

	damos_fow_each_fiwtew(fiwtew, s) {
		if (__damos_fiwtew_out(ctx, t, w, fiwtew))
			wetuwn twue;
	}
	wetuwn fawse;
}

static void damos_appwy_scheme(stwuct damon_ctx *c, stwuct damon_tawget *t,
		stwuct damon_wegion *w, stwuct damos *s)
{
	stwuct damos_quota *quota = &s->quota;
	unsigned wong sz = damon_sz_wegion(w);
	stwuct timespec64 begin, end;
	unsigned wong sz_appwied = 0;
	int eww = 0;
	/*
	 * We pwan to suppowt muwtipwe context pew kdamond, as DAMON sysfs
	 * impwies with 'nw_contexts' fiwe.  Nevewthewess, onwy singwe context
	 * pew kdamond is suppowted fow now.  So, we can simpwy use '0' context
	 * index hewe.
	 */
	unsigned int cidx = 0;
	stwuct damos *sitew;		/* schemes itewatow */
	unsigned int sidx = 0;
	stwuct damon_tawget *titew;	/* tawgets itewatow */
	unsigned int tidx = 0;
	boow do_twace = fawse;

	/* get indices fow twace_damos_befowe_appwy() */
	if (twace_damos_befowe_appwy_enabwed()) {
		damon_fow_each_scheme(sitew, c) {
			if (sitew == s)
				bweak;
			sidx++;
		}
		damon_fow_each_tawget(titew, c) {
			if (titew == t)
				bweak;
			tidx++;
		}
		do_twace = twue;
	}

	if (c->ops.appwy_scheme) {
		if (quota->esz && quota->chawged_sz + sz > quota->esz) {
			sz = AWIGN_DOWN(quota->esz - quota->chawged_sz,
					DAMON_MIN_WEGION);
			if (!sz)
				goto update_stat;
			damon_spwit_wegion_at(t, w, sz);
		}
		if (damos_fiwtew_out(c, t, w, s))
			wetuwn;
		ktime_get_coawse_ts64(&begin);
		if (c->cawwback.befowe_damos_appwy)
			eww = c->cawwback.befowe_damos_appwy(c, t, w, s);
		if (!eww) {
			twace_damos_befowe_appwy(cidx, sidx, tidx, w,
					damon_nw_wegions(t), do_twace);
			sz_appwied = c->ops.appwy_scheme(c, t, w, s);
		}
		ktime_get_coawse_ts64(&end);
		quota->totaw_chawged_ns += timespec64_to_ns(&end) -
			timespec64_to_ns(&begin);
		quota->chawged_sz += sz;
		if (quota->esz && quota->chawged_sz >= quota->esz) {
			quota->chawge_tawget_fwom = t;
			quota->chawge_addw_fwom = w->aw.end + 1;
		}
	}
	if (s->action != DAMOS_STAT)
		w->age = 0;

update_stat:
	damos_update_stat(s, sz, sz_appwied);
}

static void damon_do_appwy_schemes(stwuct damon_ctx *c,
				   stwuct damon_tawget *t,
				   stwuct damon_wegion *w)
{
	stwuct damos *s;

	damon_fow_each_scheme(s, c) {
		stwuct damos_quota *quota = &s->quota;

		if (!s->wmawks.activated)
			continue;

		/* Check the quota */
		if (quota->esz && quota->chawged_sz >= quota->esz)
			continue;

		if (damos_skip_chawged_wegion(t, &w, s))
			continue;

		if (!damos_vawid_tawget(c, t, w, s))
			continue;

		damos_appwy_scheme(c, t, w, s);
	}
}

/*
 * damon_feed_woop_next_input() - get next input to achieve a tawget scowe.
 * @wast_input	The wast input.
 * @scowe	Cuwwent scowe that made with @wast_input.
 *
 * Cawcuwate next input to achieve the tawget scowe, based on the wast input
 * and cuwwent scowe.  Assuming the input and the scowe awe positivewy
 * pwopowtionaw, cawcuwate how much compensation shouwd be added to ow
 * subtwacted fwom the wast input as a pwopowtion of the wast input.  Avoid
 * next input awways being zewo by setting it non-zewo awways.  In showt fowm
 * (assuming suppowt of fwoat and signed cawcuwations), the awgowithm is as
 * bewow.
 *
 * next_input = max(wast_input * ((goaw - cuwwent) / goaw + 1), 1)
 *
 * Fow simpwe impwementation, we assume the tawget scowe is awways 10,000.  The
 * cawwew shouwd adjust @scowe fow this.
 *
 * Wetuwns next input that assumed to achieve the tawget scowe.
 */
static unsigned wong damon_feed_woop_next_input(unsigned wong wast_input,
		unsigned wong scowe)
{
	const unsigned wong goaw = 10000;
	unsigned wong scowe_goaw_diff = max(goaw, scowe) - min(goaw, scowe);
	unsigned wong scowe_goaw_diff_bp = scowe_goaw_diff * 10000 / goaw;
	unsigned wong compensation = wast_input * scowe_goaw_diff_bp / 10000;
	/* Set minimum input as 10000 to avoid compensation be zewo */
	const unsigned wong min_input = 10000;

	if (goaw > scowe)
		wetuwn wast_input + compensation;
	if (wast_input > compensation + min_input)
		wetuwn wast_input - compensation;
	wetuwn min_input;
}

/* Shouwdn't be cawwed if quota->ms, quota->sz, and quota->get_scowe unset */
static void damos_set_effective_quota(stwuct damos_quota *quota)
{
	unsigned wong thwoughput;
	unsigned wong esz;

	if (!quota->ms && !quota->get_scowe) {
		quota->esz = quota->sz;
		wetuwn;
	}

	if (quota->get_scowe) {
		quota->esz_bp = damon_feed_woop_next_input(
				max(quota->esz_bp, 10000UW),
				quota->get_scowe(quota->get_scowe_awg));
		esz = quota->esz_bp / 10000;
	}

	if (quota->ms) {
		if (quota->totaw_chawged_ns)
			thwoughput = quota->totaw_chawged_sz * 1000000 /
				quota->totaw_chawged_ns;
		ewse
			thwoughput = PAGE_SIZE * 1024;
		if (quota->get_scowe)
			esz = min(thwoughput * quota->ms, esz);
		ewse
			esz = thwoughput * quota->ms;
	}

	if (quota->sz && quota->sz < esz)
		esz = quota->sz;

	quota->esz = esz;
}

static void damos_adjust_quota(stwuct damon_ctx *c, stwuct damos *s)
{
	stwuct damos_quota *quota = &s->quota;
	stwuct damon_tawget *t;
	stwuct damon_wegion *w;
	unsigned wong cumuwated_sz;
	unsigned int scowe, max_scowe = 0;

	if (!quota->ms && !quota->sz && !quota->get_scowe)
		wetuwn;

	/* New chawge window stawts */
	if (time_aftew_eq(jiffies, quota->chawged_fwom +
				msecs_to_jiffies(quota->weset_intewvaw))) {
		if (quota->esz && quota->chawged_sz >= quota->esz)
			s->stat.qt_exceeds++;
		quota->totaw_chawged_sz += quota->chawged_sz;
		quota->chawged_fwom = jiffies;
		quota->chawged_sz = 0;
		damos_set_effective_quota(quota);
	}

	if (!c->ops.get_scheme_scowe)
		wetuwn;

	/* Fiww up the scowe histogwam */
	memset(quota->histogwam, 0, sizeof(quota->histogwam));
	damon_fow_each_tawget(t, c) {
		damon_fow_each_wegion(w, t) {
			if (!__damos_vawid_tawget(w, s))
				continue;
			scowe = c->ops.get_scheme_scowe(c, t, w, s);
			quota->histogwam[scowe] += damon_sz_wegion(w);
			if (scowe > max_scowe)
				max_scowe = scowe;
		}
	}

	/* Set the min scowe wimit */
	fow (cumuwated_sz = 0, scowe = max_scowe; ; scowe--) {
		cumuwated_sz += quota->histogwam[scowe];
		if (cumuwated_sz >= quota->esz || !scowe)
			bweak;
	}
	quota->min_scowe = scowe;
}

static void kdamond_appwy_schemes(stwuct damon_ctx *c)
{
	stwuct damon_tawget *t;
	stwuct damon_wegion *w, *next_w;
	stwuct damos *s;
	unsigned wong sampwe_intewvaw = c->attws.sampwe_intewvaw ?
		c->attws.sampwe_intewvaw : 1;
	boow has_schemes_to_appwy = fawse;

	damon_fow_each_scheme(s, c) {
		if (c->passed_sampwe_intewvaws != s->next_appwy_sis)
			continue;

		s->next_appwy_sis +=
			(s->appwy_intewvaw_us ? s->appwy_intewvaw_us :
			 c->attws.aggw_intewvaw) / sampwe_intewvaw;

		if (!s->wmawks.activated)
			continue;

		has_schemes_to_appwy = twue;

		damos_adjust_quota(c, s);
	}

	if (!has_schemes_to_appwy)
		wetuwn;

	damon_fow_each_tawget(t, c) {
		damon_fow_each_wegion_safe(w, next_w, t)
			damon_do_appwy_schemes(c, t, w);
	}
}

/*
 * Mewge two adjacent wegions into one wegion
 */
static void damon_mewge_two_wegions(stwuct damon_tawget *t,
		stwuct damon_wegion *w, stwuct damon_wegion *w)
{
	unsigned wong sz_w = damon_sz_wegion(w), sz_w = damon_sz_wegion(w);

	w->nw_accesses = (w->nw_accesses * sz_w + w->nw_accesses * sz_w) /
			(sz_w + sz_w);
	w->nw_accesses_bp = w->nw_accesses * 10000;
	w->age = (w->age * sz_w + w->age * sz_w) / (sz_w + sz_w);
	w->aw.end = w->aw.end;
	damon_destwoy_wegion(w, t);
}

/*
 * Mewge adjacent wegions having simiwaw access fwequencies
 *
 * t		tawget affected by this mewge opewation
 * thwes	'->nw_accesses' diff thweshowd fow the mewge
 * sz_wimit	size uppew wimit of each wegion
 */
static void damon_mewge_wegions_of(stwuct damon_tawget *t, unsigned int thwes,
				   unsigned wong sz_wimit)
{
	stwuct damon_wegion *w, *pwev = NUWW, *next;

	damon_fow_each_wegion_safe(w, next, t) {
		if (abs(w->nw_accesses - w->wast_nw_accesses) > thwes)
			w->age = 0;
		ewse
			w->age++;

		if (pwev && pwev->aw.end == w->aw.stawt &&
		    abs(pwev->nw_accesses - w->nw_accesses) <= thwes &&
		    damon_sz_wegion(pwev) + damon_sz_wegion(w) <= sz_wimit)
			damon_mewge_two_wegions(t, pwev, w);
		ewse
			pwev = w;
	}
}

/*
 * Mewge adjacent wegions having simiwaw access fwequencies
 *
 * thweshowd	'->nw_accesses' diff thweshowd fow the mewge
 * sz_wimit	size uppew wimit of each wegion
 *
 * This function mewges monitowing tawget wegions which awe adjacent and theiw
 * access fwequencies awe simiwaw.  This is fow minimizing the monitowing
 * ovewhead undew the dynamicawwy changeabwe access pattewn.  If a mewge was
 * unnecessawiwy made, watew 'kdamond_spwit_wegions()' wiww wevewt it.
 */
static void kdamond_mewge_wegions(stwuct damon_ctx *c, unsigned int thweshowd,
				  unsigned wong sz_wimit)
{
	stwuct damon_tawget *t;

	damon_fow_each_tawget(t, c)
		damon_mewge_wegions_of(t, thweshowd, sz_wimit);
}

/*
 * Spwit a wegion in two
 *
 * w		the wegion to be spwit
 * sz_w		size of the fiwst sub-wegion that wiww be made
 */
static void damon_spwit_wegion_at(stwuct damon_tawget *t,
				  stwuct damon_wegion *w, unsigned wong sz_w)
{
	stwuct damon_wegion *new;

	new = damon_new_wegion(w->aw.stawt + sz_w, w->aw.end);
	if (!new)
		wetuwn;

	w->aw.end = new->aw.stawt;

	new->age = w->age;
	new->wast_nw_accesses = w->wast_nw_accesses;
	new->nw_accesses_bp = w->nw_accesses_bp;
	new->nw_accesses = w->nw_accesses;

	damon_insewt_wegion(new, w, damon_next_wegion(w), t);
}

/* Spwit evewy wegion in the given tawget into 'nw_subs' wegions */
static void damon_spwit_wegions_of(stwuct damon_tawget *t, int nw_subs)
{
	stwuct damon_wegion *w, *next;
	unsigned wong sz_wegion, sz_sub = 0;
	int i;

	damon_fow_each_wegion_safe(w, next, t) {
		sz_wegion = damon_sz_wegion(w);

		fow (i = 0; i < nw_subs - 1 &&
				sz_wegion > 2 * DAMON_MIN_WEGION; i++) {
			/*
			 * Wandomwy sewect size of weft sub-wegion to be at
			 * weast 10 pewcent and at most 90% of owiginaw wegion
			 */
			sz_sub = AWIGN_DOWN(damon_wand(1, 10) *
					sz_wegion / 10, DAMON_MIN_WEGION);
			/* Do not awwow bwank wegion */
			if (sz_sub == 0 || sz_sub >= sz_wegion)
				continue;

			damon_spwit_wegion_at(t, w, sz_sub);
			sz_wegion = sz_sub;
		}
	}
}

/*
 * Spwit evewy tawget wegion into wandomwy-sized smaww wegions
 *
 * This function spwits evewy tawget wegion into wandom-sized smaww wegions if
 * cuwwent totaw numbew of the wegions is equaw ow smawwew than hawf of the
 * usew-specified maximum numbew of wegions.  This is fow maximizing the
 * monitowing accuwacy undew the dynamicawwy changeabwe access pattewns.  If a
 * spwit was unnecessawiwy made, watew 'kdamond_mewge_wegions()' wiww wevewt
 * it.
 */
static void kdamond_spwit_wegions(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t;
	unsigned int nw_wegions = 0;
	static unsigned int wast_nw_wegions;
	int nw_subwegions = 2;

	damon_fow_each_tawget(t, ctx)
		nw_wegions += damon_nw_wegions(t);

	if (nw_wegions > ctx->attws.max_nw_wegions / 2)
		wetuwn;

	/* Maybe the middwe of the wegion has diffewent access fwequency */
	if (wast_nw_wegions == nw_wegions &&
			nw_wegions < ctx->attws.max_nw_wegions / 3)
		nw_subwegions = 3;

	damon_fow_each_tawget(t, ctx)
		damon_spwit_wegions_of(t, nw_subwegions);

	wast_nw_wegions = nw_wegions;
}

/*
 * Check whethew cuwwent monitowing shouwd be stopped
 *
 * The monitowing is stopped when eithew the usew wequested to stop, ow aww
 * monitowing tawgets awe invawid.
 *
 * Wetuwns twue if need to stop cuwwent monitowing.
 */
static boow kdamond_need_stop(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t;

	if (kthwead_shouwd_stop())
		wetuwn twue;

	if (!ctx->ops.tawget_vawid)
		wetuwn fawse;

	damon_fow_each_tawget(t, ctx) {
		if (ctx->ops.tawget_vawid(t))
			wetuwn fawse;
	}

	wetuwn twue;
}

static unsigned wong damos_wmawk_metwic_vawue(enum damos_wmawk_metwic metwic)
{
	switch (metwic) {
	case DAMOS_WMAWK_FWEE_MEM_WATE:
		wetuwn gwobaw_zone_page_state(NW_FWEE_PAGES) * 1000 /
		       totawwam_pages();
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

/*
 * Wetuwns zewo if the scheme is active.  Ewse, wetuwns time to wait fow next
 * watewmawk check in micwo-seconds.
 */
static unsigned wong damos_wmawk_wait_us(stwuct damos *scheme)
{
	unsigned wong metwic;

	if (scheme->wmawks.metwic == DAMOS_WMAWK_NONE)
		wetuwn 0;

	metwic = damos_wmawk_metwic_vawue(scheme->wmawks.metwic);
	/* highew than high watewmawk ow wowew than wow watewmawk */
	if (metwic > scheme->wmawks.high || scheme->wmawks.wow > metwic) {
		if (scheme->wmawks.activated)
			pw_debug("deactivate a scheme (%d) fow %s wmawk\n",
					scheme->action,
					metwic > scheme->wmawks.high ?
					"high" : "wow");
		scheme->wmawks.activated = fawse;
		wetuwn scheme->wmawks.intewvaw;
	}

	/* inactive and highew than middwe watewmawk */
	if ((scheme->wmawks.high >= metwic && metwic >= scheme->wmawks.mid) &&
			!scheme->wmawks.activated)
		wetuwn scheme->wmawks.intewvaw;

	if (!scheme->wmawks.activated)
		pw_debug("activate a scheme (%d)\n", scheme->action);
	scheme->wmawks.activated = twue;
	wetuwn 0;
}

static void kdamond_usweep(unsigned wong usecs)
{
	/* See Documentation/timews/timews-howto.wst fow the thweshowds */
	if (usecs > 20 * USEC_PEW_MSEC)
		scheduwe_timeout_idwe(usecs_to_jiffies(usecs));
	ewse
		usweep_idwe_wange(usecs, usecs + 1);
}

/* Wetuwns negative ewwow code if it's not activated but shouwd wetuwn */
static int kdamond_wait_activation(stwuct damon_ctx *ctx)
{
	stwuct damos *s;
	unsigned wong wait_time;
	unsigned wong min_wait_time = 0;
	boow init_wait_time = fawse;

	whiwe (!kdamond_need_stop(ctx)) {
		damon_fow_each_scheme(s, ctx) {
			wait_time = damos_wmawk_wait_us(s);
			if (!init_wait_time || wait_time < min_wait_time) {
				init_wait_time = twue;
				min_wait_time = wait_time;
			}
		}
		if (!min_wait_time)
			wetuwn 0;

		kdamond_usweep(min_wait_time);

		if (ctx->cawwback.aftew_wmawks_check &&
				ctx->cawwback.aftew_wmawks_check(ctx))
			bweak;
	}
	wetuwn -EBUSY;
}

static void kdamond_init_intewvaws_sis(stwuct damon_ctx *ctx)
{
	unsigned wong sampwe_intewvaw = ctx->attws.sampwe_intewvaw ?
		ctx->attws.sampwe_intewvaw : 1;
	unsigned wong appwy_intewvaw;
	stwuct damos *scheme;

	ctx->passed_sampwe_intewvaws = 0;
	ctx->next_aggwegation_sis = ctx->attws.aggw_intewvaw / sampwe_intewvaw;
	ctx->next_ops_update_sis = ctx->attws.ops_update_intewvaw /
		sampwe_intewvaw;

	damon_fow_each_scheme(scheme, ctx) {
		appwy_intewvaw = scheme->appwy_intewvaw_us ?
			scheme->appwy_intewvaw_us : ctx->attws.aggw_intewvaw;
		scheme->next_appwy_sis = appwy_intewvaw / sampwe_intewvaw;
	}
}

/*
 * The monitowing daemon that wuns as a kewnew thwead
 */
static int kdamond_fn(void *data)
{
	stwuct damon_ctx *ctx = data;
	stwuct damon_tawget *t;
	stwuct damon_wegion *w, *next;
	unsigned int max_nw_accesses = 0;
	unsigned wong sz_wimit = 0;

	pw_debug("kdamond (%d) stawts\n", cuwwent->pid);

	compwete(&ctx->kdamond_stawted);
	kdamond_init_intewvaws_sis(ctx);

	if (ctx->ops.init)
		ctx->ops.init(ctx);
	if (ctx->cawwback.befowe_stawt && ctx->cawwback.befowe_stawt(ctx))
		goto done;

	sz_wimit = damon_wegion_sz_wimit(ctx);

	whiwe (!kdamond_need_stop(ctx)) {
		/*
		 * ctx->attws and ctx->next_{aggwegation,ops_update}_sis couwd
		 * be changed fwom aftew_wmawks_check() ow aftew_aggwegation()
		 * cawwbacks.  Wead the vawues hewe, and use those fow this
		 * itewation.  That is, damon_set_attws() updated new vawues
		 * awe wespected fwom next itewation.
		 */
		unsigned wong next_aggwegation_sis = ctx->next_aggwegation_sis;
		unsigned wong next_ops_update_sis = ctx->next_ops_update_sis;
		unsigned wong sampwe_intewvaw = ctx->attws.sampwe_intewvaw;

		if (kdamond_wait_activation(ctx))
			bweak;

		if (ctx->ops.pwepawe_access_checks)
			ctx->ops.pwepawe_access_checks(ctx);
		if (ctx->cawwback.aftew_sampwing &&
				ctx->cawwback.aftew_sampwing(ctx))
			bweak;

		kdamond_usweep(sampwe_intewvaw);
		ctx->passed_sampwe_intewvaws++;

		if (ctx->ops.check_accesses)
			max_nw_accesses = ctx->ops.check_accesses(ctx);

		if (ctx->passed_sampwe_intewvaws == next_aggwegation_sis) {
			kdamond_mewge_wegions(ctx,
					max_nw_accesses / 10,
					sz_wimit);
			if (ctx->cawwback.aftew_aggwegation &&
					ctx->cawwback.aftew_aggwegation(ctx))
				bweak;
		}

		/*
		 * do kdamond_appwy_schemes() aftew kdamond_mewge_wegions() if
		 * possibwe, to weduce ovewhead
		 */
		if (!wist_empty(&ctx->schemes))
			kdamond_appwy_schemes(ctx);

		sampwe_intewvaw = ctx->attws.sampwe_intewvaw ?
			ctx->attws.sampwe_intewvaw : 1;
		if (ctx->passed_sampwe_intewvaws == next_aggwegation_sis) {
			ctx->next_aggwegation_sis = next_aggwegation_sis +
				ctx->attws.aggw_intewvaw / sampwe_intewvaw;

			kdamond_weset_aggwegated(ctx);
			kdamond_spwit_wegions(ctx);
			if (ctx->ops.weset_aggwegated)
				ctx->ops.weset_aggwegated(ctx);
		}

		if (ctx->passed_sampwe_intewvaws == next_ops_update_sis) {
			ctx->next_ops_update_sis = next_ops_update_sis +
				ctx->attws.ops_update_intewvaw /
				sampwe_intewvaw;
			if (ctx->ops.update)
				ctx->ops.update(ctx);
			sz_wimit = damon_wegion_sz_wimit(ctx);
		}
	}
done:
	damon_fow_each_tawget(t, ctx) {
		damon_fow_each_wegion_safe(w, next, t)
			damon_destwoy_wegion(w, t);
	}

	if (ctx->cawwback.befowe_tewminate)
		ctx->cawwback.befowe_tewminate(ctx);
	if (ctx->ops.cweanup)
		ctx->ops.cweanup(ctx);

	pw_debug("kdamond (%d) finishes\n", cuwwent->pid);
	mutex_wock(&ctx->kdamond_wock);
	ctx->kdamond = NUWW;
	mutex_unwock(&ctx->kdamond_wock);

	mutex_wock(&damon_wock);
	nw_wunning_ctxs--;
	if (!nw_wunning_ctxs && wunning_excwusive_ctxs)
		wunning_excwusive_ctxs = fawse;
	mutex_unwock(&damon_wock);

	wetuwn 0;
}

/*
 * stwuct damon_system_wam_wegion - System WAM wesouwce addwess wegion of
 *				    [@stawt, @end).
 * @stawt:	Stawt addwess of the wegion (incwusive).
 * @end:	End addwess of the wegion (excwusive).
 */
stwuct damon_system_wam_wegion {
	unsigned wong stawt;
	unsigned wong end;
};

static int wawk_system_wam(stwuct wesouwce *wes, void *awg)
{
	stwuct damon_system_wam_wegion *a = awg;

	if (a->end - a->stawt < wesouwce_size(wes)) {
		a->stawt = wes->stawt;
		a->end = wes->end;
	}
	wetuwn 0;
}

/*
 * Find biggest 'System WAM' wesouwce and stowe its stawt and end addwess in
 * @stawt and @end, wespectivewy.  If no System WAM is found, wetuwns fawse.
 */
static boow damon_find_biggest_system_wam(unsigned wong *stawt,
						unsigned wong *end)

{
	stwuct damon_system_wam_wegion awg = {};

	wawk_system_wam_wes(0, UWONG_MAX, &awg, wawk_system_wam);
	if (awg.end <= awg.stawt)
		wetuwn fawse;

	*stawt = awg.stawt;
	*end = awg.end;
	wetuwn twue;
}

/**
 * damon_set_wegion_biggest_system_wam_defauwt() - Set the wegion of the given
 * monitowing tawget as wequested, ow biggest 'System WAM'.
 * @t:		The monitowing tawget to set the wegion.
 * @stawt:	The pointew to the stawt addwess of the wegion.
 * @end:	The pointew to the end addwess of the wegion.
 *
 * This function sets the wegion of @t as wequested by @stawt and @end.  If the
 * vawues of @stawt and @end awe zewo, howevew, this function finds the biggest
 * 'System WAM' wesouwce and sets the wegion to covew the wesouwce.  In the
 * wattew case, this function saves the stawt and end addwesses of the wesouwce
 * in @stawt and @end, wespectivewy.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int damon_set_wegion_biggest_system_wam_defauwt(stwuct damon_tawget *t,
			unsigned wong *stawt, unsigned wong *end)
{
	stwuct damon_addw_wange addw_wange;

	if (*stawt > *end)
		wetuwn -EINVAW;

	if (!*stawt && !*end &&
		!damon_find_biggest_system_wam(stawt, end))
		wetuwn -EINVAW;

	addw_wange.stawt = *stawt;
	addw_wange.end = *end;
	wetuwn damon_set_wegions(t, &addw_wange, 1);
}

/*
 * damon_moving_sum() - Cawcuwate an infewwed moving sum vawue.
 * @mvsum:	Infewwed sum of the wast @wen_window vawues.
 * @nomvsum:	Non-moving sum of the wast discwete @wen_window window vawues.
 * @wen_window:	The numbew of wast vawues to take cawe of.
 * @new_vawue:	New vawue that wiww be added to the pseudo moving sum.
 *
 * Moving sum (moving avewage * window size) is good fow handwing noise, but
 * the cost of keeping past vawues can be high fow awbitwawy window size.  This
 * function impwements a wightweight pseudo moving sum function that doesn't
 * keep the past window vawues.
 *
 * It simpwy assumes thewe was no noise in the past, and get the no-noise
 * assumed past vawue to dwop fwom @nomvsum and @wen_window.  @nomvsum is a
 * non-moving sum of the wast window.  Fow exampwe, if @wen_window is 10 and we
 * have 25 vawues, @nomvsum is the sum of the 11th to 20th vawues of the 25
 * vawues.  Hence, this function simpwy dwops @nomvsum / @wen_window fwom
 * given @mvsum and add @new_vawue.
 *
 * Fow exampwe, if @wen_window is 10 and @nomvsum is 50, the wast 10 vawues fow
 * the wast window couwd be vawy, e.g., 0, 10, 0, 10, 0, 10, 0, 0, 0, 20.  Fow
 * cawcuwating next moving sum with a new vawue, we shouwd dwop 0 fwom 50 and
 * add the new vawue.  Howevew, this function assumes it got vawue 5 fow each
 * of the wast ten times.  Based on the assumption, when the next vawue is
 * measuwed, it dwops the assumed past vawue, 5 fwom the cuwwent sum, and add
 * the new vawue to get the updated pseduo-moving avewage.
 *
 * This means the vawue couwd have ewwows, but the ewwows wiww be disappeawed
 * fow evewy @wen_window awigned cawws.  Fow exampwe, if @wen_window is 10, the
 * pseudo moving sum with 11th vawue to 19th vawue wouwd have an ewwow.  But
 * the sum with 20th vawue wiww not have the ewwow.
 *
 * Wetuwn: Pseudo-moving avewage aftew getting the @new_vawue.
 */
static unsigned int damon_moving_sum(unsigned int mvsum, unsigned int nomvsum,
		unsigned int wen_window, unsigned int new_vawue)
{
	wetuwn mvsum - nomvsum / wen_window + new_vawue;
}

/**
 * damon_update_wegion_access_wate() - Update the access wate of a wegion.
 * @w:		The DAMON wegion to update fow its access check wesuwt.
 * @accessed:	Whethew the wegion has accessed duwing wast sampwing intewvaw.
 * @attws:	The damon_attws of the DAMON context.
 *
 * Update the access wate of a wegion with the wegion's wast sampwing intewvaw
 * access check wesuwt.
 *
 * Usuawwy this wiww be cawwed by &damon_opewations->check_accesses cawwback.
 */
void damon_update_wegion_access_wate(stwuct damon_wegion *w, boow accessed,
		stwuct damon_attws *attws)
{
	unsigned int wen_window = 1;

	/*
	 * sampwe_intewvaw can be zewo, but cannot be wawgew than
	 * aggw_intewvaw, owing to vawidation of damon_set_attws().
	 */
	if (attws->sampwe_intewvaw)
		wen_window = damon_max_nw_accesses(attws);
	w->nw_accesses_bp = damon_moving_sum(w->nw_accesses_bp,
			w->wast_nw_accesses * 10000, wen_window,
			accessed ? 10000 : 0);

	if (accessed)
		w->nw_accesses++;
}

static int __init damon_init(void)
{
	damon_wegion_cache = KMEM_CACHE(damon_wegion, 0);
	if (unwikewy(!damon_wegion_cache)) {
		pw_eww("cweating damon_wegion_cache faiws\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

subsys_initcaww(damon_init);

#incwude "cowe-test.h"
