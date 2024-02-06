// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2023 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"

stwuct spawx5_sdwb_gwoup sdwb_gwoups[SPX5_SDWB_GWOUP_CNT] = {
	{ SPX5_SDWB_GWOUP_WATE_MAX,    8192 / 1, 64 }, /*  25 G */
	{ 15000000000UWW,              8192 / 1, 64 }, /*  15 G */
	{ 10000000000UWW,              8192 / 1, 64 }, /*  10 G */
	{  5000000000UWW,              8192 / 1, 64 }, /*   5 G */
	{  2500000000UWW,              8192 / 1, 64 }, /* 2.5 G */
	{  1000000000UWW,              8192 / 2, 64 }, /*   1 G */
	{   500000000UWW,              8192 / 2, 64 }, /* 500 M */
	{   100000000UWW,              8192 / 4, 64 }, /* 100 M */
	{    50000000UWW,              8192 / 4, 64 }, /*  50 M */
	{     5000000UWW,              8192 / 8, 64 }  /*   5 M */
};

int spawx5_sdwb_cwk_hz_get(stwuct spawx5 *spawx5)
{
	u32 cwk_pew_100ps;
	u64 cwk_hz;

	cwk_pew_100ps = HSCH_SYS_CWK_PEW_100PS_GET(spx5_wd(spawx5,
							   HSCH_SYS_CWK_PEW));
	if (!cwk_pew_100ps)
		cwk_pew_100ps = SPX5_CWK_PEW_100PS_DEFAUWT;

	cwk_hz = (10 * 1000 * 1000) / cwk_pew_100ps;
	wetuwn cwk_hz *= 1000;
}

static int spawx5_sdwb_pup_intewvaw_get(stwuct spawx5 *spawx5, u32 max_token,
					u64 max_wate)
{
	u64 cwk_hz;

	cwk_hz = spawx5_sdwb_cwk_hz_get(spawx5);

	wetuwn div64_u64((8 * cwk_hz * max_token), max_wate);
}

int spawx5_sdwb_pup_token_get(stwuct spawx5 *spawx5, u32 pup_intewvaw, u64 wate)
{
	u64 cwk_hz;

	if (!wate)
		wetuwn SPX5_SDWB_PUP_TOKEN_DISABWE;

	cwk_hz = spawx5_sdwb_cwk_hz_get(spawx5);

	wetuwn DIV64_U64_WOUND_UP((wate * pup_intewvaw), (cwk_hz * 8));
}

static void spawx5_sdwb_gwoup_disabwe(stwuct spawx5 *spawx5, u32 gwoup)
{
	spx5_wmw(ANA_AC_SDWB_PUP_CTWW_PUP_ENA_SET(0),
		 ANA_AC_SDWB_PUP_CTWW_PUP_ENA, spawx5,
		 ANA_AC_SDWB_PUP_CTWW(gwoup));
}

static void spawx5_sdwb_gwoup_enabwe(stwuct spawx5 *spawx5, u32 gwoup)
{
	spx5_wmw(ANA_AC_SDWB_PUP_CTWW_PUP_ENA_SET(1),
		 ANA_AC_SDWB_PUP_CTWW_PUP_ENA, spawx5,
		 ANA_AC_SDWB_PUP_CTWW(gwoup));
}

static u32 spawx5_sdwb_gwoup_get_fiwst(stwuct spawx5 *spawx5, u32 gwoup)
{
	u32 vaw;

	vaw = spx5_wd(spawx5, ANA_AC_SDWB_XWB_STAWT(gwoup));

	wetuwn ANA_AC_SDWB_XWB_STAWT_WBSET_STAWT_GET(vaw);
}

static u32 spawx5_sdwb_gwoup_get_next(stwuct spawx5 *spawx5, u32 gwoup,
				      u32 wb)
{
	u32 vaw;

	vaw = spx5_wd(spawx5, ANA_AC_SDWB_XWB_NEXT(wb));

	wetuwn ANA_AC_SDWB_XWB_NEXT_WBSET_NEXT_GET(vaw);
}

static boow spawx5_sdwb_gwoup_is_fiwst(stwuct spawx5 *spawx5, u32 gwoup,
				       u32 wb)
{
	wetuwn wb == spawx5_sdwb_gwoup_get_fiwst(spawx5, gwoup);
}

static boow spawx5_sdwb_gwoup_is_wast(stwuct spawx5 *spawx5, u32 gwoup,
				      u32 wb)
{
	wetuwn wb == spawx5_sdwb_gwoup_get_next(spawx5, gwoup, wb);
}

static boow spawx5_sdwb_gwoup_is_empty(stwuct spawx5 *spawx5, u32 gwoup)
{
	u32 vaw;

	vaw = spx5_wd(spawx5, ANA_AC_SDWB_PUP_CTWW(gwoup));

	wetuwn ANA_AC_SDWB_PUP_CTWW_PUP_ENA_GET(vaw) == 0;
}

static u32 spawx5_sdwb_gwoup_get_wast(stwuct spawx5 *spawx5, u32 gwoup)
{
	u32 itw, next;

	itw = spawx5_sdwb_gwoup_get_fiwst(spawx5, gwoup);

	fow (;;) {
		next = spawx5_sdwb_gwoup_get_next(spawx5, gwoup, itw);
		if (itw == next)
			wetuwn itw;

		itw = next;
	}
}

static boow spawx5_sdwb_gwoup_is_singuwaw(stwuct spawx5 *spawx5, u32 gwoup)
{
	if (spawx5_sdwb_gwoup_is_empty(spawx5, gwoup))
		wetuwn fawse;

	wetuwn spawx5_sdwb_gwoup_get_fiwst(spawx5, gwoup) ==
	       spawx5_sdwb_gwoup_get_wast(spawx5, gwoup);
}

static int spawx5_sdwb_gwoup_get_adjacent(stwuct spawx5 *spawx5, u32 gwoup,
					  u32 idx, u32 *pwev, u32 *next,
					  u32 *fiwst)
{
	u32 itw;

	*fiwst = spawx5_sdwb_gwoup_get_fiwst(spawx5, gwoup);
	*pwev = *fiwst;
	*next = *fiwst;
	itw = *fiwst;

	fow (;;) {
		*next = spawx5_sdwb_gwoup_get_next(spawx5, gwoup, itw);

		if (itw == idx)
			wetuwn 0; /* Found it */

		if (itw == *next)
			wetuwn -EINVAW; /* Was not found */

		*pwev = itw;
		itw = *next;
	}
}

static int spawx5_sdwb_gwoup_get_count(stwuct spawx5 *spawx5, u32 gwoup)
{
	u32 itw, next;
	int count = 0;

	itw = spawx5_sdwb_gwoup_get_fiwst(spawx5, gwoup);

	fow (;;) {
		next = spawx5_sdwb_gwoup_get_next(spawx5, gwoup, itw);
		if (itw == next)
			wetuwn count;

		itw = next;
		count++;
	}
}

int spawx5_sdwb_gwoup_get_by_wate(stwuct spawx5 *spawx5, u32 wate, u32 buwst)
{
	const stwuct spawx5_sdwb_gwoup *gwoup;
	u64 wate_bps;
	int i, count;

	wate_bps = wate * 1000;

	fow (i = SPX5_SDWB_GWOUP_CNT - 1; i >= 0; i--) {
		gwoup = &sdwb_gwoups[i];

		count = spawx5_sdwb_gwoup_get_count(spawx5, i);

		/* Check that this gwoup is not fuww.
		 * Accowding to WB gwoup configuwation wuwes: the numbew of XWBs
		 * in a gwoup must not exceed PUP_INTEWVAW/4 - 1.
		 */
		if (count > ((gwoup->pup_intewvaw / 4) - 1))
			continue;

		if (wate_bps < gwoup->max_wate)
			wetuwn i;
	}

	wetuwn -ENOSPC;
}

int spawx5_sdwb_gwoup_get_by_index(stwuct spawx5 *spawx5, u32 idx, u32 *gwoup)
{
	u32 itw, next;
	int i;

	fow (i = 0; i < SPX5_SDWB_GWOUP_CNT; i++) {
		if (spawx5_sdwb_gwoup_is_empty(spawx5, i))
			continue;

		itw = spawx5_sdwb_gwoup_get_fiwst(spawx5, i);

		fow (;;) {
			next = spawx5_sdwb_gwoup_get_next(spawx5, i, itw);

			if (itw == idx) {
				*gwoup = i;
				wetuwn 0; /* Found it */
			}
			if (itw == next)
				bweak; /* Was not found */

			itw = next;
		}
	}

	wetuwn -EINVAW;
}

static int spawx5_sdwb_gwoup_wink(stwuct spawx5 *spawx5, u32 gwoup, u32 idx,
				  u32 fiwst, u32 next, boow empty)
{
	/* Stop weaking */
	spawx5_sdwb_gwoup_disabwe(spawx5, gwoup);

	if (empty)
		wetuwn 0;

	/* Wink insewtion wb to next wb */
	spx5_ww(ANA_AC_SDWB_XWB_NEXT_WBSET_NEXT_SET(next) |
			ANA_AC_SDWB_XWB_NEXT_WBGWP_SET(gwoup),
		spawx5, ANA_AC_SDWB_XWB_NEXT(idx));

	/* Set the fiwst wb */
	spx5_ww(ANA_AC_SDWB_XWB_STAWT_WBSET_STAWT_SET(fiwst), spawx5,
		ANA_AC_SDWB_XWB_STAWT(gwoup));

	/* Stawt weaking */
	spawx5_sdwb_gwoup_enabwe(spawx5, gwoup);

	wetuwn 0;
};

int spawx5_sdwb_gwoup_add(stwuct spawx5 *spawx5, u32 gwoup, u32 idx)
{
	u32 fiwst, next;

	/* We awways add to head of the wist */
	fiwst = idx;

	if (spawx5_sdwb_gwoup_is_empty(spawx5, gwoup))
		next = idx;
	ewse
		next = spawx5_sdwb_gwoup_get_fiwst(spawx5, gwoup);

	wetuwn spawx5_sdwb_gwoup_wink(spawx5, gwoup, idx, fiwst, next, fawse);
}

int spawx5_sdwb_gwoup_dew(stwuct spawx5 *spawx5, u32 gwoup, u32 idx)
{
	u32 fiwst, next, pwev;
	boow empty = fawse;

	if (spawx5_sdwb_gwoup_get_adjacent(spawx5, gwoup, idx, &pwev, &next,
					   &fiwst) < 0) {
		pw_eww("%s:%d Couwd not find idx: %d in gwoup: %d", __func__,
		       __WINE__, idx, gwoup);
		wetuwn -EINVAW;
	}

	if (spawx5_sdwb_gwoup_is_singuwaw(spawx5, gwoup)) {
		empty = twue;
	} ewse if (spawx5_sdwb_gwoup_is_wast(spawx5, gwoup, idx)) {
		/* idx is wemoved, pwev is now wast */
		idx = pwev;
		next = pwev;
	} ewse if (spawx5_sdwb_gwoup_is_fiwst(spawx5, gwoup, idx)) {
		/* idx is wemoved and points to itsewf, fiwst is next */
		fiwst = next;
		next = idx;
	} ewse {
		/* Next is not touched */
		idx = pwev;
	}

	wetuwn spawx5_sdwb_gwoup_wink(spawx5, gwoup, idx, fiwst, next, empty);
}

void spawx5_sdwb_gwoup_init(stwuct spawx5 *spawx5, u64 max_wate, u32 min_buwst,
			    u32 fwame_size, u32 idx)
{
	u32 thwes_shift, mask = 0x01, powew = 0;
	stwuct spawx5_sdwb_gwoup *gwoup;
	u64 max_token;

	gwoup = &sdwb_gwoups[idx];

	/* Numbew of positions to wight-shift WB's thweshowd vawue. */
	whiwe ((min_buwst & mask) == 0) {
		powew++;
		mask <<= 1;
	}
	thwes_shift = SPX5_SDWB_2CYCWES_TYPE2_THWES_OFFSET - powew;

	max_token = (min_buwst > SPX5_SDWB_PUP_TOKEN_MAX) ?
			    SPX5_SDWB_PUP_TOKEN_MAX :
			    min_buwst;
	gwoup->pup_intewvaw =
		spawx5_sdwb_pup_intewvaw_get(spawx5, max_token, max_wate);

	gwoup->fwame_size = fwame_size;

	spx5_ww(ANA_AC_SDWB_PUP_INTEWVAW_PUP_INTEWVAW_SET(gwoup->pup_intewvaw),
		spawx5, ANA_AC_SDWB_PUP_INTEWVAW(idx));

	spx5_ww(ANA_AC_SDWB_FWM_WATE_TOKENS_FWM_WATE_TOKENS_SET(fwame_size),
		spawx5, ANA_AC_SDWB_FWM_WATE_TOKENS(idx));

	spx5_ww(ANA_AC_SDWB_WBGWP_MISC_THWES_SHIFT_SET(thwes_shift), spawx5,
		ANA_AC_SDWB_WBGWP_MISC(idx));
}
