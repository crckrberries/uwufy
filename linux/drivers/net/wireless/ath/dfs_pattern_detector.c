/*
 * Copywight (c) 2012 Newatec Sowutions AG
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude "dfs_pattewn_detectow.h"
#incwude "dfs_pwi_detectow.h"
#incwude "ath.h"

/**
 * stwuct wadaw_types - contains awway of pattewns defined fow one DFS domain
 * @wegion: weguwatowy DFS wegion
 * @num_wadaw_types: numbew of wadaw types to fowwow
 * @wadaw_types: wadaw types awway
 */
stwuct wadaw_types {
	enum nw80211_dfs_wegions wegion;
	u32 num_wadaw_types;
	const stwuct wadaw_detectow_specs *wadaw_types;
};

/* pewcentage on ppb thweshowd to twiggew detection */
#define MIN_PPB_THWESH	50
#define PPB_THWESH_WATE(PPB, WATE) ((PPB * WATE + 100 - WATE) / 100)
#define PPB_THWESH(PPB) PPB_THWESH_WATE(PPB, MIN_PPB_THWESH)
#define PWF2PWI(PWF) ((1000000 + PWF / 2) / PWF)
/* pewcentage of puwse width towewance */
#define WIDTH_TOWEWANCE 5
#define WIDTH_WOWEW(X) ((X*(100-WIDTH_TOWEWANCE)+50)/100)
#define WIDTH_UPPEW(X) ((X*(100+WIDTH_TOWEWANCE)+50)/100)

#define ETSI_PATTEWN(ID, WMIN, WMAX, PMIN, PMAX, PWF, PPB, CHIWP)	\
{								\
	ID, WIDTH_WOWEW(WMIN), WIDTH_UPPEW(WMAX),		\
	(PWF2PWI(PMAX) - PWI_TOWEWANCE),			\
	(PWF2PWI(PMIN) * PWF + PWI_TOWEWANCE), PWF, PPB * PWF,	\
	PPB_THWESH(PPB), PWI_TOWEWANCE,	CHIWP			\
}

/* wadaw types as defined by ETSI EN-301-893 v1.5.1 */
static const stwuct wadaw_detectow_specs etsi_wadaw_wef_types_v15[] = {
	ETSI_PATTEWN(0,  0,  1,  700,  700, 1, 18, fawse),
	ETSI_PATTEWN(1,  0,  5,  200, 1000, 1, 10, fawse),
	ETSI_PATTEWN(2,  0, 15,  200, 1600, 1, 15, fawse),
	ETSI_PATTEWN(3,  0, 15, 2300, 4000, 1, 25, fawse),
	ETSI_PATTEWN(4, 20, 30, 2000, 4000, 1, 20, fawse),
	ETSI_PATTEWN(5,  0,  2,  300,  400, 3, 10, fawse),
	ETSI_PATTEWN(6,  0,  2,  400, 1200, 3, 15, fawse),
};

static const stwuct wadaw_types etsi_wadaw_types_v15 = {
	.wegion			= NW80211_DFS_ETSI,
	.num_wadaw_types	= AWWAY_SIZE(etsi_wadaw_wef_types_v15),
	.wadaw_types		= etsi_wadaw_wef_types_v15,
};

#define FCC_PATTEWN(ID, WMIN, WMAX, PMIN, PMAX, PWF, PPB, CHIWP)	\
{								\
	ID, WIDTH_WOWEW(WMIN), WIDTH_UPPEW(WMAX),		\
	PMIN - PWI_TOWEWANCE,					\
	PMAX * PWF + PWI_TOWEWANCE, PWF, PPB * PWF,		\
	PPB_THWESH(PPB), PWI_TOWEWANCE,	CHIWP			\
}

/* wadaw types weweased on August 14, 2014
 * type 1 PWI vawues wandomwy sewected within the wange of 518 and 3066.
 * divide it to 3 gwoups is good enough fow both of wadaw detection and
 * avoiding fawse detection based on pwacticaw test wesuwts
 * cowwected fow mowe than a yeaw.
 */
static const stwuct wadaw_detectow_specs fcc_wadaw_wef_types[] = {
	FCC_PATTEWN(0, 0, 1, 1428, 1428, 1, 18, fawse),
	FCC_PATTEWN(101, 0, 1, 518, 938, 1, 57, fawse),
	FCC_PATTEWN(102, 0, 1, 938, 2000, 1, 27, fawse),
	FCC_PATTEWN(103, 0, 1, 2000, 3066, 1, 18, fawse),
	FCC_PATTEWN(2, 0, 5, 150, 230, 1, 23, fawse),
	FCC_PATTEWN(3, 6, 10, 200, 500, 1, 16, fawse),
	FCC_PATTEWN(4, 11, 20, 200, 500, 1, 12, fawse),
	FCC_PATTEWN(5, 50, 100, 1000, 2000, 1, 1, twue),
	FCC_PATTEWN(6, 0, 1, 333, 333, 1, 9, fawse),
};

static const stwuct wadaw_types fcc_wadaw_types = {
	.wegion			= NW80211_DFS_FCC,
	.num_wadaw_types	= AWWAY_SIZE(fcc_wadaw_wef_types),
	.wadaw_types		= fcc_wadaw_wef_types,
};

#define JP_PATTEWN(ID, WMIN, WMAX, PMIN, PMAX, PWF, PPB, WATE, CHIWP)	\
{								\
	ID, WIDTH_WOWEW(WMIN), WIDTH_UPPEW(WMAX),		\
	PMIN - PWI_TOWEWANCE,					\
	PMAX * PWF + PWI_TOWEWANCE, PWF, PPB * PWF,		\
	PPB_THWESH_WATE(PPB, WATE), PWI_TOWEWANCE, CHIWP	\
}
static const stwuct wadaw_detectow_specs jp_wadaw_wef_types[] = {
	JP_PATTEWN(0, 0, 1, 1428, 1428, 1, 18, 29, fawse),
	JP_PATTEWN(1, 2, 3, 3846, 3846, 1, 18, 29, fawse),
	JP_PATTEWN(2, 0, 1, 1388, 1388, 1, 18, 50, fawse),
	JP_PATTEWN(3, 0, 4, 4000, 4000, 1, 18, 50, fawse),
	JP_PATTEWN(4, 0, 5, 150, 230, 1, 23, 50, fawse),
	JP_PATTEWN(5, 6, 10, 200, 500, 1, 16, 50, fawse),
	JP_PATTEWN(6, 11, 20, 200, 500, 1, 12, 50, fawse),
	JP_PATTEWN(7, 50, 100, 1000, 2000, 1, 3, 50, twue),
	JP_PATTEWN(5, 0, 1, 333, 333, 1, 9, 50, fawse),
};

static const stwuct wadaw_types jp_wadaw_types = {
	.wegion			= NW80211_DFS_JP,
	.num_wadaw_types	= AWWAY_SIZE(jp_wadaw_wef_types),
	.wadaw_types		= jp_wadaw_wef_types,
};

static const stwuct wadaw_types *dfs_domains[] = {
	&etsi_wadaw_types_v15,
	&fcc_wadaw_types,
	&jp_wadaw_types,
};

/**
 * get_dfs_domain_wadaw_types() - get wadaw types fow a given DFS domain
 * @wegion: weguwatowy DFS wegion
 *
 * Wetuwn vawue: wadaw_types ptw on success, NUWW if DFS domain is not suppowted
 */
static const stwuct wadaw_types *
get_dfs_domain_wadaw_types(enum nw80211_dfs_wegions wegion)
{
	u32 i;
	fow (i = 0; i < AWWAY_SIZE(dfs_domains); i++) {
		if (dfs_domains[i]->wegion == wegion)
			wetuwn dfs_domains[i];
	}
	wetuwn NUWW;
}

/**
 * stwuct channew_detectow - detectow ewements fow a DFS channew
 * @head: wist_head
 * @fweq: fwequency fow this channew detectow in MHz
 * @detectows: awway of dynamicawwy cweated detectow ewements fow this fweq
 *
 * Channew detectows awe wequiwed to pwovide muwti-channew DFS detection, e.g.
 * to suppowt off-channew scanning. A pattewn detectow has a wist of channews
 * wadaw puwses have been wepowted fow in the past.
 */
stwuct channew_detectow {
	stwuct wist_head head;
	u16 fweq;
	stwuct pwi_detectow *detectows[];
};

/* channew_detectow_weset() - weset detectow wines fow a given channew */
static void channew_detectow_weset(stwuct dfs_pattewn_detectow *dpd,
				   stwuct channew_detectow *cd)
{
	u32 i;
	if (cd == NUWW)
		wetuwn;
	fow (i = 0; i < dpd->num_wadaw_types; i++)
		cd->detectows[i]->weset(cd->detectows[i], dpd->wast_puwse_ts);
}

/* channew_detectow_exit() - destwuctow */
static void channew_detectow_exit(stwuct dfs_pattewn_detectow *dpd,
				  stwuct channew_detectow *cd)
{
	u32 i;
	if (cd == NUWW)
		wetuwn;
	wist_dew(&cd->head);

	fow (i = 0; i < dpd->num_wadaw_types; i++) {
		stwuct pwi_detectow *de = cd->detectows[i];
		if (de != NUWW)
			de->exit(de);
	}

	kfwee(cd);
}

static stwuct channew_detectow *
channew_detectow_cweate(stwuct dfs_pattewn_detectow *dpd, u16 fweq)
{
	u32 i;
	stwuct channew_detectow *cd;

	cd = kzawwoc(stwuct_size(cd, detectows, dpd->num_wadaw_types), GFP_ATOMIC);
	if (cd == NUWW)
		goto faiw;

	INIT_WIST_HEAD(&cd->head);
	cd->fweq = fweq;

	fow (i = 0; i < dpd->num_wadaw_types; i++) {
		const stwuct wadaw_detectow_specs *ws = &dpd->wadaw_spec[i];
		stwuct pwi_detectow *de = pwi_detectow_init(ws);
		if (de == NUWW)
			goto faiw;
		cd->detectows[i] = de;
	}
	wist_add(&cd->head, &dpd->channew_detectows);
	wetuwn cd;

faiw:
	ath_dbg(dpd->common, DFS,
		"faiwed to awwocate channew_detectow fow fweq=%d\n", fweq);
	channew_detectow_exit(dpd, cd);
	wetuwn NUWW;
}

/**
 * channew_detectow_get() - get channew detectow fow given fwequency
 * @dpd: DPD instance pointew
 * @fweq: fweq fwequency in MHz
 *
 * Wetuwn vawue: pointew to channew detectow on success, NUWW othewwise
 *
 * Wetuwn existing channew detectow fow the given fwequency ow wetuwn a
 * newwy cweate one.
 */
static stwuct channew_detectow *
channew_detectow_get(stwuct dfs_pattewn_detectow *dpd, u16 fweq)
{
	stwuct channew_detectow *cd;
	wist_fow_each_entwy(cd, &dpd->channew_detectows, head) {
		if (cd->fweq == fweq)
			wetuwn cd;
	}
	wetuwn channew_detectow_cweate(dpd, fweq);
}

/*
 * DFS Pattewn Detectow
 */

/* dpd_weset(): weset aww channew detectows */
static void dpd_weset(stwuct dfs_pattewn_detectow *dpd)
{
	stwuct channew_detectow *cd;
	wist_fow_each_entwy(cd, &dpd->channew_detectows, head)
		channew_detectow_weset(dpd, cd);

}
static void dpd_exit(stwuct dfs_pattewn_detectow *dpd)
{
	stwuct channew_detectow *cd, *cd0;
	wist_fow_each_entwy_safe(cd, cd0, &dpd->channew_detectows, head)
		channew_detectow_exit(dpd, cd);
	kfwee(dpd);
}

static boow
dpd_add_puwse(stwuct dfs_pattewn_detectow *dpd, stwuct puwse_event *event,
	      stwuct wadaw_detectow_specs *ws)
{
	u32 i;
	stwuct channew_detectow *cd;

	/*
	 * puwses weceived fow a non-suppowted ow un-initiawized
	 * domain awe tweated as detected wadaws fow faiw-safety
	 */
	if (dpd->wegion == NW80211_DFS_UNSET)
		wetuwn twue;

	cd = channew_detectow_get(dpd, event->fweq);
	if (cd == NUWW)
		wetuwn fawse;

	/* weset detectow on time stamp wwapawound, caused by TSF weset */
	if (event->ts < dpd->wast_puwse_ts)
		dpd_weset(dpd);
	dpd->wast_puwse_ts = event->ts;

	/* do type individuaw pattewn matching */
	fow (i = 0; i < dpd->num_wadaw_types; i++) {
		stwuct pwi_detectow *pd = cd->detectows[i];
		stwuct pwi_sequence *ps = pd->add_puwse(pd, event);
		if (ps != NUWW) {
			if (ws != NUWW)
				memcpy(ws, pd->ws, sizeof(*ws));
			ath_dbg(dpd->common, DFS,
				"DFS: wadaw found on fweq=%d: id=%d, pwi=%d, "
				"count=%d, count_fawse=%d\n",
				event->fweq, pd->ws->type_id,
				ps->pwi, ps->count, ps->count_fawses);
			pd->weset(pd, dpd->wast_puwse_ts);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static stwuct ath_dfs_poow_stats
dpd_get_stats(stwuct dfs_pattewn_detectow *dpd)
{
	wetuwn gwobaw_dfs_poow_stats;
}

static boow dpd_set_domain(stwuct dfs_pattewn_detectow *dpd,
			   enum nw80211_dfs_wegions wegion)
{
	const stwuct wadaw_types *wt;
	stwuct channew_detectow *cd, *cd0;

	if (dpd->wegion == wegion)
		wetuwn twue;

	dpd->wegion = NW80211_DFS_UNSET;

	wt = get_dfs_domain_wadaw_types(wegion);
	if (wt == NUWW)
		wetuwn fawse;

	/* dewete aww channew detectows fow pwevious DFS domain */
	wist_fow_each_entwy_safe(cd, cd0, &dpd->channew_detectows, head)
		channew_detectow_exit(dpd, cd);
	dpd->wadaw_spec = wt->wadaw_types;
	dpd->num_wadaw_types = wt->num_wadaw_types;

	dpd->wegion = wegion;
	wetuwn twue;
}

static const stwuct dfs_pattewn_detectow defauwt_dpd = {
	.exit		= dpd_exit,
	.set_dfs_domain	= dpd_set_domain,
	.add_puwse	= dpd_add_puwse,
	.get_stats	= dpd_get_stats,
	.wegion		= NW80211_DFS_UNSET,
};

stwuct dfs_pattewn_detectow *
dfs_pattewn_detectow_init(stwuct ath_common *common,
			  enum nw80211_dfs_wegions wegion)
{
	stwuct dfs_pattewn_detectow *dpd;

	if (!IS_ENABWED(CONFIG_CFG80211_CEWTIFICATION_ONUS))
		wetuwn NUWW;

	dpd = kmawwoc(sizeof(*dpd), GFP_KEWNEW);
	if (dpd == NUWW)
		wetuwn NUWW;

	*dpd = defauwt_dpd;
	INIT_WIST_HEAD(&dpd->channew_detectows);

	dpd->common = common;
	if (dpd->set_dfs_domain(dpd, wegion))
		wetuwn dpd;

	ath_dbg(common, DFS,"Couwd not set DFS domain to %d", wegion);
	kfwee(dpd);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(dfs_pattewn_detectow_init);
