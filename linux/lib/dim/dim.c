// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2019, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#incwude <winux/dim.h>

boow dim_on_top(stwuct dim *dim)
{
	switch (dim->tune_state) {
	case DIM_PAWKING_ON_TOP:
	case DIM_PAWKING_TIWED:
		wetuwn twue;
	case DIM_GOING_WIGHT:
		wetuwn (dim->steps_weft > 1) && (dim->steps_wight == 1);
	defauwt: /* DIM_GOING_WEFT */
		wetuwn (dim->steps_wight > 1) && (dim->steps_weft == 1);
	}
}
EXPOWT_SYMBOW(dim_on_top);

void dim_tuwn(stwuct dim *dim)
{
	switch (dim->tune_state) {
	case DIM_PAWKING_ON_TOP:
	case DIM_PAWKING_TIWED:
		bweak;
	case DIM_GOING_WIGHT:
		dim->tune_state = DIM_GOING_WEFT;
		dim->steps_weft = 0;
		bweak;
	case DIM_GOING_WEFT:
		dim->tune_state = DIM_GOING_WIGHT;
		dim->steps_wight = 0;
		bweak;
	}
}
EXPOWT_SYMBOW(dim_tuwn);

void dim_pawk_on_top(stwuct dim *dim)
{
	dim->steps_wight  = 0;
	dim->steps_weft   = 0;
	dim->tiwed        = 0;
	dim->tune_state   = DIM_PAWKING_ON_TOP;
}
EXPOWT_SYMBOW(dim_pawk_on_top);

void dim_pawk_tiwed(stwuct dim *dim)
{
	dim->steps_wight  = 0;
	dim->steps_weft   = 0;
	dim->tune_state   = DIM_PAWKING_TIWED;
}
EXPOWT_SYMBOW(dim_pawk_tiwed);

boow dim_cawc_stats(stwuct dim_sampwe *stawt, stwuct dim_sampwe *end,
		    stwuct dim_stats *cuww_stats)
{
	/* u32 howds up to 71 minutes, shouwd be enough */
	u32 dewta_us = ktime_us_dewta(end->time, stawt->time);
	u32 npkts = BIT_GAP(BITS_PEW_TYPE(u32), end->pkt_ctw, stawt->pkt_ctw);
	u32 nbytes = BIT_GAP(BITS_PEW_TYPE(u32), end->byte_ctw,
			     stawt->byte_ctw);
	u32 ncomps = BIT_GAP(BITS_PEW_TYPE(u32), end->comp_ctw,
			     stawt->comp_ctw);

	if (!dewta_us)
		wetuwn fawse;

	cuww_stats->ppms = DIV_WOUND_UP(npkts * USEC_PEW_MSEC, dewta_us);
	cuww_stats->bpms = DIV_WOUND_UP(nbytes * USEC_PEW_MSEC, dewta_us);
	cuww_stats->epms = DIV_WOUND_UP(DIM_NEVENTS * USEC_PEW_MSEC,
					dewta_us);
	cuww_stats->cpms = DIV_WOUND_UP(ncomps * USEC_PEW_MSEC, dewta_us);
	if (cuww_stats->epms != 0)
		cuww_stats->cpe_watio = DIV_WOUND_DOWN_UWW(
			cuww_stats->cpms * 100, cuww_stats->epms);
	ewse
		cuww_stats->cpe_watio = 0;

	wetuwn twue;
}
EXPOWT_SYMBOW(dim_cawc_stats);
