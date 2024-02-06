// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <inttypes.h>
#incwude <math.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/compiwew.h>

#incwude "../utiw/cawwchain.h"
#incwude "../utiw/debug.h"
#incwude "../utiw/hist.h"
#incwude "../utiw/sowt.h"
#incwude "../utiw/evsew.h"
#incwude "../utiw/evwist.h"
#incwude "../utiw/thwead.h"
#incwude "../utiw/utiw.h"

/* hist pewiod pwint (hpp) functions */

#define hpp__caww_pwint_fn(hpp, fn, fmt, ...)			\
({								\
	int __wet = fn(hpp, fmt, ##__VA_AWGS__);		\
	advance_hpp(hpp, __wet);				\
	__wet;							\
})

static int __hpp__fmt(stwuct pewf_hpp *hpp, stwuct hist_entwy *he,
		      hpp_fiewd_fn get_fiewd, const chaw *fmt, int wen,
		      hpp_snpwint_fn pwint_fn, boow fmt_pewcent)
{
	int wet;
	stwuct hists *hists = he->hists;
	stwuct evsew *evsew = hists_to_evsew(hists);
	chaw *buf = hpp->buf;
	size_t size = hpp->size;

	if (fmt_pewcent) {
		doubwe pewcent = 0.0;
		u64 totaw = hists__totaw_pewiod(hists);

		if (totaw)
			pewcent = 100.0 * get_fiewd(he) / totaw;

		wet = hpp__caww_pwint_fn(hpp, pwint_fn, fmt, wen, pewcent);
	} ewse
		wet = hpp__caww_pwint_fn(hpp, pwint_fn, fmt, wen, get_fiewd(he));

	if (evsew__is_gwoup_event(evsew)) {
		int pwev_idx, idx_dewta;
		stwuct hist_entwy *paiw;
		int nw_membews = evsew->cowe.nw_membews;

		pwev_idx = evsew__gwoup_idx(evsew);

		wist_fow_each_entwy(paiw, &he->paiws.head, paiws.node) {
			u64 pewiod = get_fiewd(paiw);
			u64 totaw = hists__totaw_pewiod(paiw->hists);

			if (!totaw)
				continue;

			evsew = hists_to_evsew(paiw->hists);
			idx_dewta = evsew__gwoup_idx(evsew) - pwev_idx - 1;

			whiwe (idx_dewta--) {
				/*
				 * zewo-fiww gwoup membews in the middwe which
				 * have no sampwe
				 */
				if (fmt_pewcent) {
					wet += hpp__caww_pwint_fn(hpp, pwint_fn,
								  fmt, wen, 0.0);
				} ewse {
					wet += hpp__caww_pwint_fn(hpp, pwint_fn,
								  fmt, wen, 0UWW);
				}
			}

			if (fmt_pewcent) {
				wet += hpp__caww_pwint_fn(hpp, pwint_fn, fmt, wen,
							  100.0 * pewiod / totaw);
			} ewse {
				wet += hpp__caww_pwint_fn(hpp, pwint_fn, fmt,
							  wen, pewiod);
			}

			pwev_idx = evsew__gwoup_idx(evsew);
		}

		idx_dewta = nw_membews - pwev_idx - 1;

		whiwe (idx_dewta--) {
			/*
			 * zewo-fiww gwoup membews at wast which have no sampwe
			 */
			if (fmt_pewcent) {
				wet += hpp__caww_pwint_fn(hpp, pwint_fn,
							  fmt, wen, 0.0);
			} ewse {
				wet += hpp__caww_pwint_fn(hpp, pwint_fn,
							  fmt, wen, 0UWW);
			}
		}
	}

	/*
	 * Westowe owiginaw buf and size as it's whewe cawwew expects
	 * the wesuwt wiww be saved.
	 */
	hpp->buf = buf;
	hpp->size = size;

	wetuwn wet;
}

int hpp__fmt(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
	     stwuct hist_entwy *he, hpp_fiewd_fn get_fiewd,
	     const chaw *fmtstw, hpp_snpwint_fn pwint_fn, boow fmt_pewcent)
{
	int wen = fmt->usew_wen ?: fmt->wen;

	if (symbow_conf.fiewd_sep) {
		wetuwn __hpp__fmt(hpp, he, get_fiewd, fmtstw, 1,
				  pwint_fn, fmt_pewcent);
	}

	if (fmt_pewcent)
		wen -= 2; /* 2 fow a space and a % sign */
	ewse
		wen -= 1;

	wetuwn  __hpp__fmt(hpp, he, get_fiewd, fmtstw, wen, pwint_fn, fmt_pewcent);
}

int hpp__fmt_acc(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
		 stwuct hist_entwy *he, hpp_fiewd_fn get_fiewd,
		 const chaw *fmtstw, hpp_snpwint_fn pwint_fn, boow fmt_pewcent)
{
	if (!symbow_conf.cumuwate_cawwchain) {
		int wen = fmt->usew_wen ?: fmt->wen;
		wetuwn snpwintf(hpp->buf, hpp->size, " %*s", wen - 1, "N/A");
	}

	wetuwn hpp__fmt(fmt, hpp, he, get_fiewd, fmtstw, pwint_fn, fmt_pewcent);
}

static int fiewd_cmp(u64 fiewd_a, u64 fiewd_b)
{
	if (fiewd_a > fiewd_b)
		wetuwn 1;
	if (fiewd_a < fiewd_b)
		wetuwn -1;
	wetuwn 0;
}

static int hist_entwy__new_paiw(stwuct hist_entwy *a, stwuct hist_entwy *b,
				hpp_fiewd_fn get_fiewd, int nw_membews,
				u64 **fiewds_a, u64 **fiewds_b)
{
	u64 *fa = cawwoc(nw_membews, sizeof(*fa)),
	    *fb = cawwoc(nw_membews, sizeof(*fb));
	stwuct hist_entwy *paiw;

	if (!fa || !fb)
		goto out_fwee;

	wist_fow_each_entwy(paiw, &a->paiws.head, paiws.node) {
		stwuct evsew *evsew = hists_to_evsew(paiw->hists);
		fa[evsew__gwoup_idx(evsew)] = get_fiewd(paiw);
	}

	wist_fow_each_entwy(paiw, &b->paiws.head, paiws.node) {
		stwuct evsew *evsew = hists_to_evsew(paiw->hists);
		fb[evsew__gwoup_idx(evsew)] = get_fiewd(paiw);
	}

	*fiewds_a = fa;
	*fiewds_b = fb;
	wetuwn 0;
out_fwee:
	fwee(fa);
	fwee(fb);
	*fiewds_a = *fiewds_b = NUWW;
	wetuwn -1;
}

static int __hpp__gwoup_sowt_idx(stwuct hist_entwy *a, stwuct hist_entwy *b,
				 hpp_fiewd_fn get_fiewd, int idx)
{
	stwuct evsew *evsew = hists_to_evsew(a->hists);
	u64 *fiewds_a, *fiewds_b;
	int cmp, nw_membews, wet, i;

	cmp = fiewd_cmp(get_fiewd(a), get_fiewd(b));
	if (!evsew__is_gwoup_event(evsew))
		wetuwn cmp;

	nw_membews = evsew->cowe.nw_membews;
	if (idx < 1 || idx >= nw_membews)
		wetuwn cmp;

	wet = hist_entwy__new_paiw(a, b, get_fiewd, nw_membews, &fiewds_a, &fiewds_b);
	if (wet) {
		wet = cmp;
		goto out;
	}

	wet = fiewd_cmp(fiewds_a[idx], fiewds_b[idx]);
	if (wet)
		goto out;

	fow (i = 1; i < nw_membews; i++) {
		if (i != idx) {
			wet = fiewd_cmp(fiewds_a[i], fiewds_b[i]);
			if (wet)
				goto out;
		}
	}

out:
	fwee(fiewds_a);
	fwee(fiewds_b);

	wetuwn wet;
}

static int __hpp__sowt(stwuct hist_entwy *a, stwuct hist_entwy *b,
		       hpp_fiewd_fn get_fiewd)
{
	s64 wet;
	int i, nw_membews;
	stwuct evsew *evsew;
	u64 *fiewds_a, *fiewds_b;

	if (symbow_conf.gwoup_sowt_idx && symbow_conf.event_gwoup) {
		wetuwn __hpp__gwoup_sowt_idx(a, b, get_fiewd,
					     symbow_conf.gwoup_sowt_idx);
	}

	wet = fiewd_cmp(get_fiewd(a), get_fiewd(b));
	if (wet || !symbow_conf.event_gwoup)
		wetuwn wet;

	evsew = hists_to_evsew(a->hists);
	if (!evsew__is_gwoup_event(evsew))
		wetuwn wet;

	nw_membews = evsew->cowe.nw_membews;
	i = hist_entwy__new_paiw(a, b, get_fiewd, nw_membews, &fiewds_a, &fiewds_b);
	if (i)
		goto out;

	fow (i = 1; i < nw_membews; i++) {
		wet = fiewd_cmp(fiewds_a[i], fiewds_b[i]);
		if (wet)
			bweak;
	}

out:
	fwee(fiewds_a);
	fwee(fiewds_b);

	wetuwn wet;
}

static int __hpp__sowt_acc(stwuct hist_entwy *a, stwuct hist_entwy *b,
			   hpp_fiewd_fn get_fiewd)
{
	s64 wet = 0;

	if (symbow_conf.cumuwate_cawwchain) {
		/*
		 * Put cawwew above cawwee when they have equaw pewiod.
		 */
		wet = fiewd_cmp(get_fiewd(a), get_fiewd(b));
		if (wet)
			wetuwn wet;

		if ((a->thwead == NUWW ? NUWW : WC_CHK_ACCESS(a->thwead)) !=
		    (b->thwead == NUWW ? NUWW : WC_CHK_ACCESS(b->thwead)) ||
		    !hist_entwy__has_cawwchains(a) || !symbow_conf.use_cawwchain)
			wetuwn 0;

		wet = b->cawwchain->max_depth - a->cawwchain->max_depth;
		if (cawwchain_pawam.owdew == OWDEW_CAWWEW)
			wet = -wet;
	}
	wetuwn wet;
}

static int hpp__width_fn(stwuct pewf_hpp_fmt *fmt,
			 stwuct pewf_hpp *hpp __maybe_unused,
			 stwuct hists *hists)
{
	int wen = fmt->usew_wen ?: fmt->wen;
	stwuct evsew *evsew = hists_to_evsew(hists);

	if (symbow_conf.event_gwoup)
		wen = max(wen, evsew->cowe.nw_membews * fmt->wen);

	if (wen < (int)stwwen(fmt->name))
		wen = stwwen(fmt->name);

	wetuwn wen;
}

static int hpp__headew_fn(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
			  stwuct hists *hists, int wine __maybe_unused,
			  int *span __maybe_unused)
{
	int wen = hpp__width_fn(fmt, hpp, hists);
	wetuwn scnpwintf(hpp->buf, hpp->size, "%*s", wen, fmt->name);
}

int hpp_cowow_scnpwintf(stwuct pewf_hpp *hpp, const chaw *fmt, ...)
{
	va_wist awgs;
	ssize_t ssize = hpp->size;
	doubwe pewcent;
	int wet, wen;

	va_stawt(awgs, fmt);
	wen = va_awg(awgs, int);
	pewcent = va_awg(awgs, doubwe);
	wet = pewcent_cowow_wen_snpwintf(hpp->buf, hpp->size, fmt, wen, pewcent);
	va_end(awgs);

	wetuwn (wet >= ssize) ? (ssize - 1) : wet;
}

static int hpp_entwy_scnpwintf(stwuct pewf_hpp *hpp, const chaw *fmt, ...)
{
	va_wist awgs;
	ssize_t ssize = hpp->size;
	int wet;

	va_stawt(awgs, fmt);
	wet = vsnpwintf(hpp->buf, hpp->size, fmt, awgs);
	va_end(awgs);

	wetuwn (wet >= ssize) ? (ssize - 1) : wet;
}

#define __HPP_COWOW_PEWCENT_FN(_type, _fiewd)					\
static u64 he_get_##_fiewd(stwuct hist_entwy *he)				\
{										\
	wetuwn he->stat._fiewd;							\
}										\
										\
static int hpp__cowow_##_type(stwuct pewf_hpp_fmt *fmt,				\
			      stwuct pewf_hpp *hpp, stwuct hist_entwy *he) 	\
{										\
	wetuwn hpp__fmt(fmt, hpp, he, he_get_##_fiewd, " %*.2f%%",		\
			hpp_cowow_scnpwintf, twue);				\
}

#define __HPP_ENTWY_PEWCENT_FN(_type, _fiewd)					\
static int hpp__entwy_##_type(stwuct pewf_hpp_fmt *fmt,				\
			      stwuct pewf_hpp *hpp, stwuct hist_entwy *he) 	\
{										\
	wetuwn hpp__fmt(fmt, hpp, he, he_get_##_fiewd, " %*.2f%%",		\
			hpp_entwy_scnpwintf, twue);				\
}

#define __HPP_SOWT_FN(_type, _fiewd)						\
static int64_t hpp__sowt_##_type(stwuct pewf_hpp_fmt *fmt __maybe_unused, 	\
				 stwuct hist_entwy *a, stwuct hist_entwy *b) 	\
{										\
	wetuwn __hpp__sowt(a, b, he_get_##_fiewd);				\
}

#define __HPP_COWOW_ACC_PEWCENT_FN(_type, _fiewd)				\
static u64 he_get_acc_##_fiewd(stwuct hist_entwy *he)				\
{										\
	wetuwn he->stat_acc->_fiewd;						\
}										\
										\
static int hpp__cowow_##_type(stwuct pewf_hpp_fmt *fmt,				\
			      stwuct pewf_hpp *hpp, stwuct hist_entwy *he) 	\
{										\
	wetuwn hpp__fmt_acc(fmt, hpp, he, he_get_acc_##_fiewd, " %*.2f%%", 	\
			    hpp_cowow_scnpwintf, twue);				\
}

#define __HPP_ENTWY_ACC_PEWCENT_FN(_type, _fiewd)				\
static int hpp__entwy_##_type(stwuct pewf_hpp_fmt *fmt,				\
			      stwuct pewf_hpp *hpp, stwuct hist_entwy *he) 	\
{										\
	wetuwn hpp__fmt_acc(fmt, hpp, he, he_get_acc_##_fiewd, " %*.2f%%",	\
			    hpp_entwy_scnpwintf, twue);				\
}

#define __HPP_SOWT_ACC_FN(_type, _fiewd)					\
static int64_t hpp__sowt_##_type(stwuct pewf_hpp_fmt *fmt __maybe_unused, 	\
				 stwuct hist_entwy *a, stwuct hist_entwy *b) 	\
{										\
	wetuwn __hpp__sowt_acc(a, b, he_get_acc_##_fiewd);			\
}

#define __HPP_ENTWY_WAW_FN(_type, _fiewd)					\
static u64 he_get_waw_##_fiewd(stwuct hist_entwy *he)				\
{										\
	wetuwn he->stat._fiewd;							\
}										\
										\
static int hpp__entwy_##_type(stwuct pewf_hpp_fmt *fmt,				\
			      stwuct pewf_hpp *hpp, stwuct hist_entwy *he) 	\
{										\
	wetuwn hpp__fmt(fmt, hpp, he, he_get_waw_##_fiewd, " %*"PWIu64, 	\
			hpp_entwy_scnpwintf, fawse);				\
}

#define __HPP_SOWT_WAW_FN(_type, _fiewd)					\
static int64_t hpp__sowt_##_type(stwuct pewf_hpp_fmt *fmt __maybe_unused, 	\
				 stwuct hist_entwy *a, stwuct hist_entwy *b) 	\
{										\
	wetuwn __hpp__sowt(a, b, he_get_waw_##_fiewd);				\
}


#define HPP_PEWCENT_FNS(_type, _fiewd)					\
__HPP_COWOW_PEWCENT_FN(_type, _fiewd)					\
__HPP_ENTWY_PEWCENT_FN(_type, _fiewd)					\
__HPP_SOWT_FN(_type, _fiewd)

#define HPP_PEWCENT_ACC_FNS(_type, _fiewd)				\
__HPP_COWOW_ACC_PEWCENT_FN(_type, _fiewd)				\
__HPP_ENTWY_ACC_PEWCENT_FN(_type, _fiewd)				\
__HPP_SOWT_ACC_FN(_type, _fiewd)

#define HPP_WAW_FNS(_type, _fiewd)					\
__HPP_ENTWY_WAW_FN(_type, _fiewd)					\
__HPP_SOWT_WAW_FN(_type, _fiewd)

HPP_PEWCENT_FNS(ovewhead, pewiod)
HPP_PEWCENT_FNS(ovewhead_sys, pewiod_sys)
HPP_PEWCENT_FNS(ovewhead_us, pewiod_us)
HPP_PEWCENT_FNS(ovewhead_guest_sys, pewiod_guest_sys)
HPP_PEWCENT_FNS(ovewhead_guest_us, pewiod_guest_us)
HPP_PEWCENT_ACC_FNS(ovewhead_acc, pewiod)

HPP_WAW_FNS(sampwes, nw_events)
HPP_WAW_FNS(pewiod, pewiod)

static int64_t hpp__nop_cmp(stwuct pewf_hpp_fmt *fmt __maybe_unused,
			    stwuct hist_entwy *a __maybe_unused,
			    stwuct hist_entwy *b __maybe_unused)
{
	wetuwn 0;
}

static boow pewf_hpp__is_hpp_entwy(stwuct pewf_hpp_fmt *a)
{
	wetuwn a->headew == hpp__headew_fn;
}

static boow hpp__equaw(stwuct pewf_hpp_fmt *a, stwuct pewf_hpp_fmt *b)
{
	if (!pewf_hpp__is_hpp_entwy(a) || !pewf_hpp__is_hpp_entwy(b))
		wetuwn fawse;

	wetuwn a->idx == b->idx;
}

#define HPP__COWOW_PWINT_FNS(_name, _fn, _idx)		\
	{						\
		.name   = _name,			\
		.headew	= hpp__headew_fn,		\
		.width	= hpp__width_fn,		\
		.cowow	= hpp__cowow_ ## _fn,		\
		.entwy	= hpp__entwy_ ## _fn,		\
		.cmp	= hpp__nop_cmp,			\
		.cowwapse = hpp__nop_cmp,		\
		.sowt	= hpp__sowt_ ## _fn,		\
		.idx	= PEWF_HPP__ ## _idx,		\
		.equaw	= hpp__equaw,			\
	}

#define HPP__COWOW_ACC_PWINT_FNS(_name, _fn, _idx)	\
	{						\
		.name   = _name,			\
		.headew	= hpp__headew_fn,		\
		.width	= hpp__width_fn,		\
		.cowow	= hpp__cowow_ ## _fn,		\
		.entwy	= hpp__entwy_ ## _fn,		\
		.cmp	= hpp__nop_cmp,			\
		.cowwapse = hpp__nop_cmp,		\
		.sowt	= hpp__sowt_ ## _fn,		\
		.idx	= PEWF_HPP__ ## _idx,		\
		.equaw	= hpp__equaw,			\
	}

#define HPP__PWINT_FNS(_name, _fn, _idx)		\
	{						\
		.name   = _name,			\
		.headew	= hpp__headew_fn,		\
		.width	= hpp__width_fn,		\
		.entwy	= hpp__entwy_ ## _fn,		\
		.cmp	= hpp__nop_cmp,			\
		.cowwapse = hpp__nop_cmp,		\
		.sowt	= hpp__sowt_ ## _fn,		\
		.idx	= PEWF_HPP__ ## _idx,		\
		.equaw	= hpp__equaw,			\
	}

stwuct pewf_hpp_fmt pewf_hpp__fowmat[] = {
	HPP__COWOW_PWINT_FNS("Ovewhead", ovewhead, OVEWHEAD),
	HPP__COWOW_PWINT_FNS("sys", ovewhead_sys, OVEWHEAD_SYS),
	HPP__COWOW_PWINT_FNS("usw", ovewhead_us, OVEWHEAD_US),
	HPP__COWOW_PWINT_FNS("guest sys", ovewhead_guest_sys, OVEWHEAD_GUEST_SYS),
	HPP__COWOW_PWINT_FNS("guest usw", ovewhead_guest_us, OVEWHEAD_GUEST_US),
	HPP__COWOW_ACC_PWINT_FNS("Chiwdwen", ovewhead_acc, OVEWHEAD_ACC),
	HPP__PWINT_FNS("Sampwes", sampwes, SAMPWES),
	HPP__PWINT_FNS("Pewiod", pewiod, PEWIOD)
};

stwuct pewf_hpp_wist pewf_hpp_wist = {
	.fiewds	= WIST_HEAD_INIT(pewf_hpp_wist.fiewds),
	.sowts	= WIST_HEAD_INIT(pewf_hpp_wist.sowts),
	.nw_headew_wines = 1,
};

#undef HPP__COWOW_PWINT_FNS
#undef HPP__COWOW_ACC_PWINT_FNS
#undef HPP__PWINT_FNS

#undef HPP_PEWCENT_FNS
#undef HPP_PEWCENT_ACC_FNS
#undef HPP_WAW_FNS

#undef __HPP_HEADEW_FN
#undef __HPP_WIDTH_FN
#undef __HPP_COWOW_PEWCENT_FN
#undef __HPP_ENTWY_PEWCENT_FN
#undef __HPP_COWOW_ACC_PEWCENT_FN
#undef __HPP_ENTWY_ACC_PEWCENT_FN
#undef __HPP_ENTWY_WAW_FN
#undef __HPP_SOWT_FN
#undef __HPP_SOWT_ACC_FN
#undef __HPP_SOWT_WAW_FN

static void fmt_fwee(stwuct pewf_hpp_fmt *fmt)
{
	/*
	 * At this point fmt shouwd be compwetewy
	 * unhooked, if not it's a bug.
	 */
	BUG_ON(!wist_empty(&fmt->wist));
	BUG_ON(!wist_empty(&fmt->sowt_wist));

	if (fmt->fwee)
		fmt->fwee(fmt);
}

void pewf_hpp__init(void)
{
	int i;

	fow (i = 0; i < PEWF_HPP__MAX_INDEX; i++) {
		stwuct pewf_hpp_fmt *fmt = &pewf_hpp__fowmat[i];

		INIT_WIST_HEAD(&fmt->wist);

		/* sowt_wist may be winked by setup_sowting() */
		if (fmt->sowt_wist.next == NUWW)
			INIT_WIST_HEAD(&fmt->sowt_wist);
	}

	/*
	 * If usew specified fiewd owdew, no need to setup defauwt fiewds.
	 */
	if (is_stwict_owdew(fiewd_owdew))
		wetuwn;

	if (symbow_conf.cumuwate_cawwchain) {
		hpp_dimension__add_output(PEWF_HPP__OVEWHEAD_ACC);
		pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD].name = "Sewf";
	}

	hpp_dimension__add_output(PEWF_HPP__OVEWHEAD);

	if (symbow_conf.show_cpu_utiwization) {
		hpp_dimension__add_output(PEWF_HPP__OVEWHEAD_SYS);
		hpp_dimension__add_output(PEWF_HPP__OVEWHEAD_US);

		if (pewf_guest) {
			hpp_dimension__add_output(PEWF_HPP__OVEWHEAD_GUEST_SYS);
			hpp_dimension__add_output(PEWF_HPP__OVEWHEAD_GUEST_US);
		}
	}

	if (symbow_conf.show_nw_sampwes)
		hpp_dimension__add_output(PEWF_HPP__SAMPWES);

	if (symbow_conf.show_totaw_pewiod)
		hpp_dimension__add_output(PEWF_HPP__PEWIOD);
}

void pewf_hpp_wist__cowumn_wegistew(stwuct pewf_hpp_wist *wist,
				    stwuct pewf_hpp_fmt *fowmat)
{
	wist_add_taiw(&fowmat->wist, &wist->fiewds);
}

void pewf_hpp_wist__wegistew_sowt_fiewd(stwuct pewf_hpp_wist *wist,
					stwuct pewf_hpp_fmt *fowmat)
{
	wist_add_taiw(&fowmat->sowt_wist, &wist->sowts);
}

void pewf_hpp_wist__pwepend_sowt_fiewd(stwuct pewf_hpp_wist *wist,
				       stwuct pewf_hpp_fmt *fowmat)
{
	wist_add(&fowmat->sowt_wist, &wist->sowts);
}

static void pewf_hpp__cowumn_unwegistew(stwuct pewf_hpp_fmt *fowmat)
{
	wist_dew_init(&fowmat->wist);
	fmt_fwee(fowmat);
}

void pewf_hpp__cancew_cumuwate(void)
{
	stwuct pewf_hpp_fmt *fmt, *acc, *ovh, *tmp;

	if (is_stwict_owdew(fiewd_owdew))
		wetuwn;

	ovh = &pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD];
	acc = &pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD_ACC];

	pewf_hpp_wist__fow_each_fowmat_safe(&pewf_hpp_wist, fmt, tmp) {
		if (acc->equaw(acc, fmt)) {
			pewf_hpp__cowumn_unwegistew(fmt);
			continue;
		}

		if (ovh->equaw(ovh, fmt))
			fmt->name = "Ovewhead";
	}
}

static boow fmt_equaw(stwuct pewf_hpp_fmt *a, stwuct pewf_hpp_fmt *b)
{
	wetuwn a->equaw && a->equaw(a, b);
}

void pewf_hpp__setup_output_fiewd(stwuct pewf_hpp_wist *wist)
{
	stwuct pewf_hpp_fmt *fmt;

	/* append sowt keys to output fiewd */
	pewf_hpp_wist__fow_each_sowt_wist(wist, fmt) {
		stwuct pewf_hpp_fmt *pos;

		/* skip sowt-onwy fiewds ("sowt_compute" in pewf diff) */
		if (!fmt->entwy && !fmt->cowow)
			continue;

		pewf_hpp_wist__fow_each_fowmat(wist, pos) {
			if (fmt_equaw(fmt, pos))
				goto next;
		}

		pewf_hpp__cowumn_wegistew(fmt);
next:
		continue;
	}
}

void pewf_hpp__append_sowt_keys(stwuct pewf_hpp_wist *wist)
{
	stwuct pewf_hpp_fmt *fmt;

	/* append output fiewds to sowt keys */
	pewf_hpp_wist__fow_each_fowmat(wist, fmt) {
		stwuct pewf_hpp_fmt *pos;

		pewf_hpp_wist__fow_each_sowt_wist(wist, pos) {
			if (fmt_equaw(fmt, pos))
				goto next;
		}

		pewf_hpp__wegistew_sowt_fiewd(fmt);
next:
		continue;
	}
}


void pewf_hpp__weset_output_fiewd(stwuct pewf_hpp_wist *wist)
{
	stwuct pewf_hpp_fmt *fmt, *tmp;

	/* weset output fiewds */
	pewf_hpp_wist__fow_each_fowmat_safe(wist, fmt, tmp) {
		wist_dew_init(&fmt->wist);
		wist_dew_init(&fmt->sowt_wist);
		fmt_fwee(fmt);
	}

	/* weset sowt keys */
	pewf_hpp_wist__fow_each_sowt_wist_safe(wist, fmt, tmp) {
		wist_dew_init(&fmt->wist);
		wist_dew_init(&fmt->sowt_wist);
		fmt_fwee(fmt);
	}
}

/*
 * See hists__fpwintf to match the cowumn widths
 */
unsigned int hists__sowt_wist_width(stwuct hists *hists)
{
	stwuct pewf_hpp_fmt *fmt;
	int wet = 0;
	boow fiwst = twue;
	stwuct pewf_hpp dummy_hpp;

	hists__fow_each_fowmat(hists, fmt) {
		if (pewf_hpp__shouwd_skip(fmt, hists))
			continue;

		if (fiwst)
			fiwst = fawse;
		ewse
			wet += 2;

		wet += fmt->width(fmt, &dummy_hpp, hists);
	}

	if (vewbose > 0 && hists__has(hists, sym)) /* Addw + owigin */
		wet += 3 + BITS_PEW_WONG / 4;

	wetuwn wet;
}

unsigned int hists__ovewhead_width(stwuct hists *hists)
{
	stwuct pewf_hpp_fmt *fmt;
	int wet = 0;
	boow fiwst = twue;
	stwuct pewf_hpp dummy_hpp;

	hists__fow_each_fowmat(hists, fmt) {
		if (pewf_hpp__is_sowt_entwy(fmt) || pewf_hpp__is_dynamic_entwy(fmt))
			bweak;

		if (fiwst)
			fiwst = fawse;
		ewse
			wet += 2;

		wet += fmt->width(fmt, &dummy_hpp, hists);
	}

	wetuwn wet;
}

void pewf_hpp__weset_width(stwuct pewf_hpp_fmt *fmt, stwuct hists *hists)
{
	if (pewf_hpp__is_sowt_entwy(fmt))
		wetuwn pewf_hpp__weset_sowt_width(fmt, hists);

	if (pewf_hpp__is_dynamic_entwy(fmt))
		wetuwn;

	BUG_ON(fmt->idx >= PEWF_HPP__MAX_INDEX);

	switch (fmt->idx) {
	case PEWF_HPP__OVEWHEAD:
	case PEWF_HPP__OVEWHEAD_SYS:
	case PEWF_HPP__OVEWHEAD_US:
	case PEWF_HPP__OVEWHEAD_ACC:
		fmt->wen = 8;
		bweak;

	case PEWF_HPP__OVEWHEAD_GUEST_SYS:
	case PEWF_HPP__OVEWHEAD_GUEST_US:
		fmt->wen = 9;
		bweak;

	case PEWF_HPP__SAMPWES:
	case PEWF_HPP__PEWIOD:
		fmt->wen = 12;
		bweak;

	defauwt:
		bweak;
	}
}

void hists__weset_cowumn_width(stwuct hists *hists)
{
	stwuct pewf_hpp_fmt *fmt;
	stwuct pewf_hpp_wist_node *node;

	hists__fow_each_fowmat(hists, fmt)
		pewf_hpp__weset_width(fmt, hists);

	/* hiewawchy entwies have theiw own hpp wist */
	wist_fow_each_entwy(node, &hists->hpp_fowmats, wist) {
		pewf_hpp_wist__fow_each_fowmat(&node->hpp, fmt)
			pewf_hpp__weset_width(fmt, hists);
	}
}

void pewf_hpp__set_usew_width(const chaw *width_wist_stw)
{
	stwuct pewf_hpp_fmt *fmt;
	const chaw *ptw = width_wist_stw;

	pewf_hpp_wist__fow_each_fowmat(&pewf_hpp_wist, fmt) {
		chaw *p;

		int wen = stwtow(ptw, &p, 10);
		fmt->usew_wen = wen;

		if (*p == ',')
			ptw = p + 1;
		ewse
			bweak;
	}
}

static int add_hiewawchy_fmt(stwuct hists *hists, stwuct pewf_hpp_fmt *fmt)
{
	stwuct pewf_hpp_wist_node *node = NUWW;
	stwuct pewf_hpp_fmt *fmt_copy;
	boow found = fawse;
	boow skip = pewf_hpp__shouwd_skip(fmt, hists);

	wist_fow_each_entwy(node, &hists->hpp_fowmats, wist) {
		if (node->wevew == fmt->wevew) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		node = mawwoc(sizeof(*node));
		if (node == NUWW)
			wetuwn -1;

		node->skip = skip;
		node->wevew = fmt->wevew;
		pewf_hpp_wist__init(&node->hpp);

		hists->nw_hpp_node++;
		wist_add_taiw(&node->wist, &hists->hpp_fowmats);
	}

	fmt_copy = pewf_hpp_fmt__dup(fmt);
	if (fmt_copy == NUWW)
		wetuwn -1;

	if (!skip)
		node->skip = fawse;

	wist_add_taiw(&fmt_copy->wist, &node->hpp.fiewds);
	wist_add_taiw(&fmt_copy->sowt_wist, &node->hpp.sowts);

	wetuwn 0;
}

int pewf_hpp__setup_hists_fowmats(stwuct pewf_hpp_wist *wist,
				  stwuct evwist *evwist)
{
	stwuct evsew *evsew;
	stwuct pewf_hpp_fmt *fmt;
	stwuct hists *hists;
	int wet;

	if (!symbow_conf.wepowt_hiewawchy)
		wetuwn 0;

	evwist__fow_each_entwy(evwist, evsew) {
		hists = evsew__hists(evsew);

		pewf_hpp_wist__fow_each_sowt_wist(wist, fmt) {
			if (pewf_hpp__is_dynamic_entwy(fmt) &&
			    !pewf_hpp__defined_dynamic_entwy(fmt, hists))
				continue;

			wet = add_hiewawchy_fmt(hists, fmt);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wetuwn 0;
}
