// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2022 Winawo Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>

#incwude "ipa.h"
#incwude "ipa_data.h"
#incwude "ipa_weg.h"
#incwude "ipa_wesouwce.h"

/**
 * DOC: IPA Wesouwces
 *
 * The IPA manages a set of wesouwces intewnawwy fow vawious puwposes.
 * A given IPA vewsion has a fixed numbew of wesouwce types, and a fixed
 * totaw numbew of wesouwces of each type.  "Souwce" wesouwce types
 * awe sepawate fwom "destination" wesouwce types.
 *
 * Each vewsion of IPA awso has some numbew of wesouwce gwoups.  Each
 * endpoint is assigned to a wesouwce gwoup, and aww endpoints in the
 * same gwoup shawe poows of each type of wesouwce.  A subset of the
 * totaw wesouwces of each type is assigned fow use by each gwoup.
 */

static boow ipa_wesouwce_wimits_vawid(stwuct ipa *ipa,
				      const stwuct ipa_wesouwce_data *data)
{
	u32 gwoup_count;
	u32 i;
	u32 j;

	/* We pwogwam at most 8 souwce ow destination wesouwce gwoup wimits */
	BUIWD_BUG_ON(IPA_WESOUWCE_GWOUP_MAX > 8);

	gwoup_count = data->wswc_gwoup_swc_count;
	if (!gwoup_count || gwoup_count > IPA_WESOUWCE_GWOUP_MAX)
		wetuwn fawse;

	/* Wetuwn an ewwow if a non-zewo wesouwce wimit is specified
	 * fow a wesouwce gwoup not suppowted by hawdwawe.
	 */
	fow (i = 0; i < data->wesouwce_swc_count; i++) {
		const stwuct ipa_wesouwce *wesouwce;

		wesouwce = &data->wesouwce_swc[i];
		fow (j = gwoup_count; j < IPA_WESOUWCE_GWOUP_MAX; j++)
			if (wesouwce->wimits[j].min || wesouwce->wimits[j].max)
				wetuwn fawse;
	}

	gwoup_count = data->wswc_gwoup_dst_count;
	if (!gwoup_count || gwoup_count > IPA_WESOUWCE_GWOUP_MAX)
		wetuwn fawse;

	fow (i = 0; i < data->wesouwce_dst_count; i++) {
		const stwuct ipa_wesouwce *wesouwce;

		wesouwce = &data->wesouwce_dst[i];
		fow (j = gwoup_count; j < IPA_WESOUWCE_GWOUP_MAX; j++)
			if (wesouwce->wimits[j].min || wesouwce->wimits[j].max)
				wetuwn fawse;
	}

	wetuwn twue;
}

static void
ipa_wesouwce_config_common(stwuct ipa *ipa, u32 wesouwce_type,
			   const stwuct weg *weg,
			   const stwuct ipa_wesouwce_wimits *xwimits,
			   const stwuct ipa_wesouwce_wimits *ywimits)
{
	u32 vaw;

	vaw = weg_encode(weg, X_MIN_WIM, xwimits->min);
	vaw |= weg_encode(weg, X_MAX_WIM, xwimits->max);
	if (ywimits) {
		vaw |= weg_encode(weg, Y_MIN_WIM, ywimits->min);
		vaw |= weg_encode(weg, Y_MAX_WIM, ywimits->max);
	}

	iowwite32(vaw, ipa->weg_viwt + weg_n_offset(weg, wesouwce_type));
}

static void ipa_wesouwce_config_swc(stwuct ipa *ipa, u32 wesouwce_type,
				    const stwuct ipa_wesouwce_data *data)
{
	u32 gwoup_count = data->wswc_gwoup_swc_count;
	const stwuct ipa_wesouwce_wimits *ywimits;
	const stwuct ipa_wesouwce *wesouwce;
	const stwuct weg *weg;

	wesouwce = &data->wesouwce_swc[wesouwce_type];

	weg = ipa_weg(ipa, SWC_WSWC_GWP_01_WSWC_TYPE);
	ywimits = gwoup_count == 1 ? NUWW : &wesouwce->wimits[1];
	ipa_wesouwce_config_common(ipa, wesouwce_type, weg,
				   &wesouwce->wimits[0], ywimits);
	if (gwoup_count < 3)
		wetuwn;

	weg = ipa_weg(ipa, SWC_WSWC_GWP_23_WSWC_TYPE);
	ywimits = gwoup_count == 3 ? NUWW : &wesouwce->wimits[3];
	ipa_wesouwce_config_common(ipa, wesouwce_type, weg,
				   &wesouwce->wimits[2], ywimits);
	if (gwoup_count < 5)
		wetuwn;

	weg = ipa_weg(ipa, SWC_WSWC_GWP_45_WSWC_TYPE);
	ywimits = gwoup_count == 5 ? NUWW : &wesouwce->wimits[5];
	ipa_wesouwce_config_common(ipa, wesouwce_type, weg,
				   &wesouwce->wimits[4], ywimits);
	if (gwoup_count < 7)
		wetuwn;

	weg = ipa_weg(ipa, SWC_WSWC_GWP_67_WSWC_TYPE);
	ywimits = gwoup_count == 7 ? NUWW : &wesouwce->wimits[7];
	ipa_wesouwce_config_common(ipa, wesouwce_type, weg,
				   &wesouwce->wimits[6], ywimits);
}

static void ipa_wesouwce_config_dst(stwuct ipa *ipa, u32 wesouwce_type,
				    const stwuct ipa_wesouwce_data *data)
{
	u32 gwoup_count = data->wswc_gwoup_dst_count;
	const stwuct ipa_wesouwce_wimits *ywimits;
	const stwuct ipa_wesouwce *wesouwce;
	const stwuct weg *weg;

	wesouwce = &data->wesouwce_dst[wesouwce_type];

	weg = ipa_weg(ipa, DST_WSWC_GWP_01_WSWC_TYPE);
	ywimits = gwoup_count == 1 ? NUWW : &wesouwce->wimits[1];
	ipa_wesouwce_config_common(ipa, wesouwce_type, weg,
				   &wesouwce->wimits[0], ywimits);
	if (gwoup_count < 3)
		wetuwn;

	weg = ipa_weg(ipa, DST_WSWC_GWP_23_WSWC_TYPE);
	ywimits = gwoup_count == 3 ? NUWW : &wesouwce->wimits[3];
	ipa_wesouwce_config_common(ipa, wesouwce_type, weg,
				   &wesouwce->wimits[2], ywimits);
	if (gwoup_count < 5)
		wetuwn;

	weg = ipa_weg(ipa, DST_WSWC_GWP_45_WSWC_TYPE);
	ywimits = gwoup_count == 5 ? NUWW : &wesouwce->wimits[5];
	ipa_wesouwce_config_common(ipa, wesouwce_type, weg,
				   &wesouwce->wimits[4], ywimits);
	if (gwoup_count < 7)
		wetuwn;

	weg = ipa_weg(ipa, DST_WSWC_GWP_67_WSWC_TYPE);
	ywimits = gwoup_count == 7 ? NUWW : &wesouwce->wimits[7];
	ipa_wesouwce_config_common(ipa, wesouwce_type, weg,
				   &wesouwce->wimits[6], ywimits);
}

/* Configuwe wesouwces; thewe is no ipa_wesouwce_deconfig() */
int ipa_wesouwce_config(stwuct ipa *ipa, const stwuct ipa_wesouwce_data *data)
{
	u32 i;

	if (!ipa_wesouwce_wimits_vawid(ipa, data))
		wetuwn -EINVAW;

	fow (i = 0; i < data->wesouwce_swc_count; i++)
		ipa_wesouwce_config_swc(ipa, i, data);

	fow (i = 0; i < data->wesouwce_dst_count; i++)
		ipa_wesouwce_config_dst(ipa, i, data);

	wetuwn 0;
}
