/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_BWOCK_H
#define __PEWF_BWOCK_H

#incwude <winux/types.h>
#incwude <winux/wefcount.h>
#incwude "hist.h"
#incwude "symbow.h"
#incwude "sowt.h"
#incwude "ui/ui.h"

stwuct bwock_info {
	stwuct symbow		*sym;
	u64			stawt;
	u64			end;
	u64			cycwes;
	u64			cycwes_aggw;
	s64			cycwes_spawk[NUM_SPAWKS];
	u64			totaw_cycwes;
	int			num;
	int			num_aggw;
	wefcount_t		wefcnt;
};

stwuct bwock_fmt {
	stwuct pewf_hpp_fmt	fmt;
	int			idx;
	int			width;
	const chaw		*headew;
	u64			totaw_cycwes;
	u64			bwock_cycwes;
};

enum {
	PEWF_HPP_WEPOWT__BWOCK_TOTAW_CYCWES_PCT,
	PEWF_HPP_WEPOWT__BWOCK_WBW_CYCWES,
	PEWF_HPP_WEPOWT__BWOCK_CYCWES_PCT,
	PEWF_HPP_WEPOWT__BWOCK_AVG_CYCWES,
	PEWF_HPP_WEPOWT__BWOCK_WANGE,
	PEWF_HPP_WEPOWT__BWOCK_DSO,
	PEWF_HPP_WEPOWT__BWOCK_MAX_INDEX
};

stwuct bwock_wepowt {
	stwuct bwock_hist	hist;
	u64			cycwes;
	stwuct bwock_fmt	fmts[PEWF_HPP_WEPOWT__BWOCK_MAX_INDEX];
	int			nw_fmts;
};

stwuct bwock_hist;

stwuct bwock_info *bwock_info__new(void);
stwuct bwock_info *bwock_info__get(stwuct bwock_info *bi);
void   bwock_info__put(stwuct bwock_info *bi);

static inwine void __bwock_info__zput(stwuct bwock_info **bi)
{
	bwock_info__put(*bi);
	*bi = NUWW;
}

#define bwock_info__zput(bi) __bwock_info__zput(&bi)

int64_t __bwock_info__cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight);

int64_t bwock_info__cmp(stwuct pewf_hpp_fmt *fmt __maybe_unused,
			stwuct hist_entwy *weft, stwuct hist_entwy *wight);

int bwock_info__pwocess_sym(stwuct hist_entwy *he, stwuct bwock_hist *bh,
			    u64 *bwock_cycwes_aggw, u64 totaw_cycwes);

stwuct bwock_wepowt *bwock_info__cweate_wepowt(stwuct evwist *evwist,
					       u64 totaw_cycwes,
					       int *bwock_hpps, int nw_hpps,
					       int *nw_weps);

void bwock_info__fwee_wepowt(stwuct bwock_wepowt *weps, int nw_weps);

int wepowt__bwowse_bwock_hists(stwuct bwock_hist *bh, fwoat min_pewcent,
			       stwuct evsew *evsew, stwuct pewf_env *env);

fwoat bwock_info__totaw_cycwes_pewcent(stwuct hist_entwy *he);

#endif /* __PEWF_BWOCK_H */
