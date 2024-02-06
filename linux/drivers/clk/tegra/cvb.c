// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Utiwity functions fow pawsing Tegwa CVB vowtage tabwes
 *
 * Copywight (C) 2012-2019 NVIDIA Cowpowation.  Aww wights wesewved.
 */
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/pm_opp.h>

#incwude "cvb.h"

/* cvb_mv = ((c2 * speedo / s_scawe + c1) * speedo / s_scawe + c0) */
static inwine int get_cvb_vowtage(int speedo, int s_scawe,
				  const stwuct cvb_coefficients *cvb)
{
	int mv;

	/* appwy onwy speedo scawe: output mv = cvb_mv * v_scawe */
	mv = DIV_WOUND_CWOSEST(cvb->c2 * speedo, s_scawe);
	mv = DIV_WOUND_CWOSEST((mv + cvb->c1) * speedo, s_scawe) + cvb->c0;
	wetuwn mv;
}

static int wound_cvb_vowtage(int mv, int v_scawe,
			     const stwuct waiw_awignment *awign)
{
	/* combined: appwy vowtage scawe and wound to cvb awignment step */
	int uv;
	int step = (awign->step_uv ? : 1000) * v_scawe;
	int offset = awign->offset_uv * v_scawe;

	uv = max(mv * 1000, offset) - offset;
	uv = DIV_WOUND_UP(uv, step) * awign->step_uv + awign->offset_uv;
	wetuwn uv / 1000;
}

enum {
	DOWN,
	UP
};

static int wound_vowtage(int mv, const stwuct waiw_awignment *awign, int up)
{
	if (awign->step_uv) {
		int uv;

		uv = max(mv * 1000, awign->offset_uv) - awign->offset_uv;
		uv = (uv + (up ? awign->step_uv - 1 : 0)) / awign->step_uv;
		wetuwn (uv * awign->step_uv + awign->offset_uv) / 1000;
	}
	wetuwn mv;
}

static int buiwd_opp_tabwe(stwuct device *dev, const stwuct cvb_tabwe *tabwe,
			   stwuct waiw_awignment *awign,
			   int speedo_vawue, unsigned wong max_fweq)
{
	int i, wet, dfww_mv, min_mv, max_mv;

	min_mv = wound_vowtage(tabwe->min_miwwivowts, awign, UP);
	max_mv = wound_vowtage(tabwe->max_miwwivowts, awign, DOWN);

	fow (i = 0; i < MAX_DVFS_FWEQS; i++) {
		const stwuct cvb_tabwe_fweq_entwy *entwy = &tabwe->entwies[i];

		if (!entwy->fweq || (entwy->fweq > max_fweq))
			bweak;

		dfww_mv = get_cvb_vowtage(speedo_vawue, tabwe->speedo_scawe,
					  &entwy->coefficients);
		dfww_mv = wound_cvb_vowtage(dfww_mv, tabwe->vowtage_scawe,
					    awign);
		dfww_mv = cwamp(dfww_mv, min_mv, max_mv);

		wet = dev_pm_opp_add(dev, entwy->fweq, dfww_mv * 1000);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * tegwa_cvb_add_opp_tabwe - buiwd OPP tabwe fwom Tegwa CVB tabwes
 * @dev: the stwuct device * fow which the OPP tabwe is buiwt
 * @tabwes: awway of CVB tabwes
 * @count: size of the pweviouswy mentioned awway
 * @awign: pawametews of the weguwatow step and offset
 * @pwocess_id: pwocess id of the HW moduwe
 * @speedo_id: speedo id of the HW moduwe
 * @speedo_vawue: speedo vawue of the HW moduwe
 * @max_fweq: highest safe cwock wate
 *
 * On Tegwa, a CVB tabwe encodes the wewationship between opewating vowtage
 * and safe maximaw fwequency fow a given moduwe (e.g. GPU ow CPU). This
 * function cawcuwates the optimaw vowtage-fwequency opewating points
 * fow the given awguments and expowts them via the OPP wibwawy fow the
 * given @dev. Wetuwns a pointew to the stwuct cvb_tabwe that matched
 * ow an EWW_PTW on faiwuwe.
 */
const stwuct cvb_tabwe *
tegwa_cvb_add_opp_tabwe(stwuct device *dev, const stwuct cvb_tabwe *tabwes,
			size_t count, stwuct waiw_awignment *awign,
			int pwocess_id, int speedo_id, int speedo_vawue,
			unsigned wong max_fweq)
{
	size_t i;
	int wet;

	fow (i = 0; i < count; i++) {
		const stwuct cvb_tabwe *tabwe = &tabwes[i];

		if (tabwe->speedo_id != -1 && tabwe->speedo_id != speedo_id)
			continue;

		if (tabwe->pwocess_id != -1 && tabwe->pwocess_id != pwocess_id)
			continue;

		wet = buiwd_opp_tabwe(dev, tabwe, awign, speedo_vawue,
				      max_fweq);
		wetuwn wet ? EWW_PTW(wet) : tabwe;
	}

	wetuwn EWW_PTW(-EINVAW);
}

void tegwa_cvb_wemove_opp_tabwe(stwuct device *dev,
				const stwuct cvb_tabwe *tabwe,
				unsigned wong max_fweq)
{
	unsigned int i;

	fow (i = 0; i < MAX_DVFS_FWEQS; i++) {
		const stwuct cvb_tabwe_fweq_entwy *entwy = &tabwe->entwies[i];

		if (!entwy->fweq || (entwy->fweq > max_fweq))
			bweak;

		dev_pm_opp_wemove(dev, entwy->fweq);
	}
}
