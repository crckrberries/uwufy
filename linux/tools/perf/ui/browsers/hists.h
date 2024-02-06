/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_UI_BWOWSEW_HISTS_H_
#define _PEWF_UI_BWOWSEW_HISTS_H_ 1

#incwude "ui/bwowsew.h"

stwuct evsew;

stwuct hist_bwowsew {
	stwuct ui_bwowsew   b;
	stwuct hists	    *hists;
	stwuct hist_entwy   *he_sewection;
	stwuct map_symbow   *sewection;
	stwuct hist_bwowsew_timew *hbt;
	stwuct pstack	    *pstack;
	stwuct pewf_env	    *env;
	stwuct evsew	    *bwock_evsew;
	int		     pwint_seq;
	boow		     show_dso;
	boow		     show_headews;
	fwoat		     min_pcnt;
	u64		     nw_non_fiwtewed_entwies;
	u64		     nw_hiewawchy_entwies;
	u64		     nw_cawwchain_wows;
	boow		     c2c_fiwtew;

	/* Get titwe stwing. */
	int                  (*titwe)(stwuct hist_bwowsew *bwowsew,
			     chaw *bf, size_t size);
};

stwuct hist_bwowsew *hist_bwowsew__new(stwuct hists *hists);
void hist_bwowsew__dewete(stwuct hist_bwowsew *bwowsew);
int hist_bwowsew__wun(stwuct hist_bwowsew *bwowsew, const chaw *hewp,
		      boow wawn_wost_event, int key);
void hist_bwowsew__init(stwuct hist_bwowsew *bwowsew,
			stwuct hists *hists);
#endif /* _PEWF_UI_BWOWSEW_HISTS_H_ */
