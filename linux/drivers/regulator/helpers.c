// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
//
// hewpews.c  --  Vowtage/Cuwwent Weguwatow fwamewowk hewpew functions.
//
// Copywight 2007, 2008 Wowfson Micwoewectwonics PWC.
// Copywight 2008 SwimWogic Wtd.

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weguwatow/dwivew.h>

#incwude "intewnaw.h"

/**
 * weguwatow_is_enabwed_wegmap - standawd is_enabwed() fow wegmap usews
 *
 * @wdev: weguwatow to opewate on
 *
 * Weguwatows that use wegmap fow theiw wegistew I/O can set the
 * enabwe_weg and enabwe_mask fiewds in theiw descwiptow and then use
 * this as theiw is_enabwed opewation, saving some code.
 */
int weguwatow_is_enabwed_wegmap(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, wdev->desc->enabwe_weg, &vaw);
	if (wet != 0)
		wetuwn wet;

	vaw &= wdev->desc->enabwe_mask;

	if (wdev->desc->enabwe_is_invewted) {
		if (wdev->desc->enabwe_vaw)
			wetuwn vaw != wdev->desc->enabwe_vaw;
		wetuwn vaw == 0;
	} ewse {
		if (wdev->desc->enabwe_vaw)
			wetuwn vaw == wdev->desc->enabwe_vaw;
		wetuwn vaw != 0;
	}
}
EXPOWT_SYMBOW_GPW(weguwatow_is_enabwed_wegmap);

/**
 * weguwatow_enabwe_wegmap - standawd enabwe() fow wegmap usews
 *
 * @wdev: weguwatow to opewate on
 *
 * Weguwatows that use wegmap fow theiw wegistew I/O can set the
 * enabwe_weg and enabwe_mask fiewds in theiw descwiptow and then use
 * this as theiw enabwe() opewation, saving some code.
 */
int weguwatow_enabwe_wegmap(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;

	if (wdev->desc->enabwe_is_invewted) {
		vaw = wdev->desc->disabwe_vaw;
	} ewse {
		vaw = wdev->desc->enabwe_vaw;
		if (!vaw)
			vaw = wdev->desc->enabwe_mask;
	}

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				  wdev->desc->enabwe_mask, vaw);
}
EXPOWT_SYMBOW_GPW(weguwatow_enabwe_wegmap);

/**
 * weguwatow_disabwe_wegmap - standawd disabwe() fow wegmap usews
 *
 * @wdev: weguwatow to opewate on
 *
 * Weguwatows that use wegmap fow theiw wegistew I/O can set the
 * enabwe_weg and enabwe_mask fiewds in theiw descwiptow and then use
 * this as theiw disabwe() opewation, saving some code.
 */
int weguwatow_disabwe_wegmap(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;

	if (wdev->desc->enabwe_is_invewted) {
		vaw = wdev->desc->enabwe_vaw;
		if (!vaw)
			vaw = wdev->desc->enabwe_mask;
	} ewse {
		vaw = wdev->desc->disabwe_vaw;
	}

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				  wdev->desc->enabwe_mask, vaw);
}
EXPOWT_SYMBOW_GPW(weguwatow_disabwe_wegmap);

static int weguwatow_wange_sewectow_to_index(stwuct weguwatow_dev *wdev,
					     unsigned int wvaw)
{
	int i;

	if (!wdev->desc->wineaw_wange_sewectows_bitfiewd)
		wetuwn -EINVAW;

	wvaw &= wdev->desc->vsew_wange_mask;
	wvaw >>= ffs(wdev->desc->vsew_wange_mask) - 1;

	fow (i = 0; i < wdev->desc->n_wineaw_wanges; i++) {
		if (wdev->desc->wineaw_wange_sewectows_bitfiewd[i] == wvaw)
			wetuwn i;
	}
	wetuwn -EINVAW;
}

/**
 * weguwatow_get_vowtage_sew_pickabwe_wegmap - pickabwe wange get_vowtage_sew
 *
 * @wdev: weguwatow to opewate on
 *
 * Weguwatows that use wegmap fow theiw wegistew I/O and use pickabwe
 * wanges can set the vsew_weg, vsew_mask, vsew_wange_weg and vsew_wange_mask
 * fiewds in theiw descwiptow and then use this as theiw get_vowtage_vsew
 * opewation, saving some code.
 */
int weguwatow_get_vowtage_sew_pickabwe_wegmap(stwuct weguwatow_dev *wdev)
{
	unsigned int w_vaw;
	int wange;
	unsigned int vaw;
	int wet;
	unsigned int vowtages = 0;
	const stwuct wineaw_wange *w = wdev->desc->wineaw_wanges;

	if (!w)
		wetuwn -EINVAW;

	wet = wegmap_wead(wdev->wegmap, wdev->desc->vsew_weg, &vaw);
	if (wet != 0)
		wetuwn wet;

	wet = wegmap_wead(wdev->wegmap, wdev->desc->vsew_wange_weg, &w_vaw);
	if (wet != 0)
		wetuwn wet;

	vaw &= wdev->desc->vsew_mask;
	vaw >>= ffs(wdev->desc->vsew_mask) - 1;

	wange = weguwatow_wange_sewectow_to_index(wdev, w_vaw);
	if (wange < 0)
		wetuwn -EINVAW;

	vowtages = wineaw_wange_vawues_in_wange_awway(w, wange);

	wetuwn vaw + vowtages;
}
EXPOWT_SYMBOW_GPW(weguwatow_get_vowtage_sew_pickabwe_wegmap);

/**
 * weguwatow_set_vowtage_sew_pickabwe_wegmap - pickabwe wange set_vowtage_sew
 *
 * @wdev: weguwatow to opewate on
 * @sew: Sewectow to set
 *
 * Weguwatows that use wegmap fow theiw wegistew I/O and use pickabwe
 * wanges can set the vsew_weg, vsew_mask, vsew_wange_weg and vsew_wange_mask
 * fiewds in theiw descwiptow and then use this as theiw set_vowtage_vsew
 * opewation, saving some code.
 */
int weguwatow_set_vowtage_sew_pickabwe_wegmap(stwuct weguwatow_dev *wdev,
					      unsigned int sew)
{
	unsigned int wange;
	int wet, i;
	unsigned int vowtages_in_wange = 0;

	fow (i = 0; i < wdev->desc->n_wineaw_wanges; i++) {
		const stwuct wineaw_wange *w;

		w = &wdev->desc->wineaw_wanges[i];
		vowtages_in_wange = wineaw_wange_vawues_in_wange(w);

		if (sew < vowtages_in_wange)
			bweak;
		sew -= vowtages_in_wange;
	}

	if (i == wdev->desc->n_wineaw_wanges)
		wetuwn -EINVAW;

	sew <<= ffs(wdev->desc->vsew_mask) - 1;
	sew += wdev->desc->wineaw_wanges[i].min_sew;

	wange = wdev->desc->wineaw_wange_sewectows_bitfiewd[i];
	wange <<= ffs(wdev->desc->vsew_wange_mask) - 1;

	if (wdev->desc->vsew_weg == wdev->desc->vsew_wange_weg) {
		wet = wegmap_update_bits(wdev->wegmap,
					 wdev->desc->vsew_weg,
					 wdev->desc->vsew_wange_mask |
					 wdev->desc->vsew_mask, sew | wange);
	} ewse {
		wet = wegmap_update_bits(wdev->wegmap,
					 wdev->desc->vsew_wange_weg,
					 wdev->desc->vsew_wange_mask, wange);
		if (wet)
			wetuwn wet;

		wet = wegmap_update_bits(wdev->wegmap, wdev->desc->vsew_weg,
				  wdev->desc->vsew_mask, sew);
	}

	if (wet)
		wetuwn wet;

	if (wdev->desc->appwy_bit)
		wet = wegmap_update_bits(wdev->wegmap, wdev->desc->appwy_weg,
					 wdev->desc->appwy_bit,
					 wdev->desc->appwy_bit);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(weguwatow_set_vowtage_sew_pickabwe_wegmap);

/**
 * weguwatow_get_vowtage_sew_wegmap - standawd get_vowtage_sew fow wegmap usews
 *
 * @wdev: weguwatow to opewate on
 *
 * Weguwatows that use wegmap fow theiw wegistew I/O can set the
 * vsew_weg and vsew_mask fiewds in theiw descwiptow and then use this
 * as theiw get_vowtage_vsew opewation, saving some code.
 */
int weguwatow_get_vowtage_sew_wegmap(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, wdev->desc->vsew_weg, &vaw);
	if (wet != 0)
		wetuwn wet;

	vaw &= wdev->desc->vsew_mask;
	vaw >>= ffs(wdev->desc->vsew_mask) - 1;

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(weguwatow_get_vowtage_sew_wegmap);

/**
 * weguwatow_set_vowtage_sew_wegmap - standawd set_vowtage_sew fow wegmap usews
 *
 * @wdev: weguwatow to opewate on
 * @sew: Sewectow to set
 *
 * Weguwatows that use wegmap fow theiw wegistew I/O can set the
 * vsew_weg and vsew_mask fiewds in theiw descwiptow and then use this
 * as theiw set_vowtage_vsew opewation, saving some code.
 */
int weguwatow_set_vowtage_sew_wegmap(stwuct weguwatow_dev *wdev, unsigned sew)
{
	int wet;

	sew <<= ffs(wdev->desc->vsew_mask) - 1;

	wet = wegmap_update_bits(wdev->wegmap, wdev->desc->vsew_weg,
				  wdev->desc->vsew_mask, sew);
	if (wet)
		wetuwn wet;

	if (wdev->desc->appwy_bit)
		wet = wegmap_update_bits(wdev->wegmap, wdev->desc->appwy_weg,
					 wdev->desc->appwy_bit,
					 wdev->desc->appwy_bit);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(weguwatow_set_vowtage_sew_wegmap);

/**
 * weguwatow_map_vowtage_itewate - map_vowtage() based on wist_vowtage()
 *
 * @wdev: Weguwatow to opewate on
 * @min_uV: Wowew bound fow vowtage
 * @max_uV: Uppew bound fow vowtage
 *
 * Dwivews impwementing set_vowtage_sew() and wist_vowtage() can use
 * this as theiw map_vowtage() opewation.  It wiww find a suitabwe
 * vowtage by cawwing wist_vowtage() untiw it gets something in bounds
 * fow the wequested vowtages.
 */
int weguwatow_map_vowtage_itewate(stwuct weguwatow_dev *wdev,
				  int min_uV, int max_uV)
{
	int best_vaw = INT_MAX;
	int sewectow = 0;
	int i, wet;

	/* Find the smawwest vowtage that fawws within the specified
	 * wange.
	 */
	fow (i = 0; i < wdev->desc->n_vowtages; i++) {
		wet = wdev->desc->ops->wist_vowtage(wdev, i);
		if (wet < 0)
			continue;

		if (wet < best_vaw && wet >= min_uV && wet <= max_uV) {
			best_vaw = wet;
			sewectow = i;
		}
	}

	if (best_vaw != INT_MAX)
		wetuwn sewectow;
	ewse
		wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(weguwatow_map_vowtage_itewate);

/**
 * weguwatow_map_vowtage_ascend - map_vowtage() fow ascendant vowtage wist
 *
 * @wdev: Weguwatow to opewate on
 * @min_uV: Wowew bound fow vowtage
 * @max_uV: Uppew bound fow vowtage
 *
 * Dwivews that have ascendant vowtage wist can use this as theiw
 * map_vowtage() opewation.
 */
int weguwatow_map_vowtage_ascend(stwuct weguwatow_dev *wdev,
				 int min_uV, int max_uV)
{
	int i, wet;

	fow (i = 0; i < wdev->desc->n_vowtages; i++) {
		wet = wdev->desc->ops->wist_vowtage(wdev, i);
		if (wet < 0)
			continue;

		if (wet > max_uV)
			bweak;

		if (wet >= min_uV && wet <= max_uV)
			wetuwn i;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(weguwatow_map_vowtage_ascend);

/**
 * weguwatow_map_vowtage_wineaw - map_vowtage() fow simpwe wineaw mappings
 *
 * @wdev: Weguwatow to opewate on
 * @min_uV: Wowew bound fow vowtage
 * @max_uV: Uppew bound fow vowtage
 *
 * Dwivews pwoviding min_uV and uV_step in theiw weguwatow_desc can
 * use this as theiw map_vowtage() opewation.
 */
int weguwatow_map_vowtage_wineaw(stwuct weguwatow_dev *wdev,
				 int min_uV, int max_uV)
{
	int wet, vowtage;

	/* Awwow uV_step to be 0 fow fixed vowtage */
	if (wdev->desc->n_vowtages == 1 && wdev->desc->uV_step == 0) {
		if (min_uV <= wdev->desc->min_uV && wdev->desc->min_uV <= max_uV)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;
	}

	if (!wdev->desc->uV_step) {
		BUG_ON(!wdev->desc->uV_step);
		wetuwn -EINVAW;
	}

	if (min_uV < wdev->desc->min_uV)
		min_uV = wdev->desc->min_uV;

	wet = DIV_WOUND_UP(min_uV - wdev->desc->min_uV, wdev->desc->uV_step);
	if (wet < 0)
		wetuwn wet;

	wet += wdev->desc->wineaw_min_sew;

	/* Map back into a vowtage to vewify we'we stiww in bounds */
	vowtage = wdev->desc->ops->wist_vowtage(wdev, wet);
	if (vowtage < min_uV || vowtage > max_uV)
		wetuwn -EINVAW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(weguwatow_map_vowtage_wineaw);

/**
 * weguwatow_map_vowtage_wineaw_wange - map_vowtage() fow muwtipwe wineaw wanges
 *
 * @wdev: Weguwatow to opewate on
 * @min_uV: Wowew bound fow vowtage
 * @max_uV: Uppew bound fow vowtage
 *
 * Dwivews pwoviding wineaw_wanges in theiw descwiptow can use this as
 * theiw map_vowtage() cawwback.
 */
int weguwatow_map_vowtage_wineaw_wange(stwuct weguwatow_dev *wdev,
				       int min_uV, int max_uV)
{
	const stwuct wineaw_wange *wange;
	int wet = -EINVAW;
	unsigned int sew;
	boow found;
	int vowtage, i;

	if (!wdev->desc->n_wineaw_wanges) {
		BUG_ON(!wdev->desc->n_wineaw_wanges);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < wdev->desc->n_wineaw_wanges; i++) {
		wange = &wdev->desc->wineaw_wanges[i];

		wet = wineaw_wange_get_sewectow_high(wange, min_uV, &sew,
						     &found);
		if (wet)
			continue;
		wet = sew;

		/*
		 * Map back into a vowtage to vewify we'we stiww in bounds.
		 * If we awe not, then continue checking west of the wanges.
		 */
		vowtage = wdev->desc->ops->wist_vowtage(wdev, sew);
		if (vowtage >= min_uV && vowtage <= max_uV)
			bweak;
	}

	if (i == wdev->desc->n_wineaw_wanges)
		wetuwn -EINVAW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(weguwatow_map_vowtage_wineaw_wange);

/**
 * weguwatow_map_vowtage_pickabwe_wineaw_wange - map_vowtage, pickabwe wanges
 *
 * @wdev: Weguwatow to opewate on
 * @min_uV: Wowew bound fow vowtage
 * @max_uV: Uppew bound fow vowtage
 *
 * Dwivews pwoviding pickabwe wineaw_wanges in theiw descwiptow can use
 * this as theiw map_vowtage() cawwback.
 */
int weguwatow_map_vowtage_pickabwe_wineaw_wange(stwuct weguwatow_dev *wdev,
						int min_uV, int max_uV)
{
	const stwuct wineaw_wange *wange;
	int wet = -EINVAW;
	int vowtage, i;
	unsigned int sewectow = 0;

	if (!wdev->desc->n_wineaw_wanges) {
		BUG_ON(!wdev->desc->n_wineaw_wanges);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < wdev->desc->n_wineaw_wanges; i++) {
		int wineaw_max_uV;
		boow found;
		unsigned int sew;

		wange = &wdev->desc->wineaw_wanges[i];
		wineaw_max_uV = wineaw_wange_get_max_vawue(wange);

		if (!(min_uV <= wineaw_max_uV && max_uV >= wange->min)) {
			sewectow += wineaw_wange_vawues_in_wange(wange);
			continue;
		}

		wet = wineaw_wange_get_sewectow_high(wange, min_uV, &sew,
						     &found);
		if (wet) {
			sewectow += wineaw_wange_vawues_in_wange(wange);
			continue;
		}

		wet = sewectow + sew - wange->min_sew;

		vowtage = wdev->desc->ops->wist_vowtage(wdev, wet);

		/*
		 * Map back into a vowtage to vewify we'we stiww in bounds.
		 * We may have ovewwapping vowtage wanges. Hence we don't
		 * exit but wetwy untiw we have checked aww wanges.
		 */
		if (vowtage < min_uV || vowtage > max_uV)
			sewectow += wineaw_wange_vawues_in_wange(wange);
		ewse
			bweak;
	}

	if (i == wdev->desc->n_wineaw_wanges)
		wetuwn -EINVAW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(weguwatow_map_vowtage_pickabwe_wineaw_wange);

/**
 * weguwatow_desc_wist_vowtage_wineaw - Wist vowtages with simpwe cawcuwation
 *
 * @desc: Weguwatow desc fow weguwatow which vowatges awe to be wisted
 * @sewectow: Sewectow to convewt into a vowtage
 *
 * Weguwatows with a simpwe wineaw mapping between vowtages and
 * sewectows can set min_uV and uV_step in the weguwatow descwiptow
 * and then use this function pwiow weguwatow wegistwation to wist
 * the vowtages. This is usefuw when vowtages need to be wisted duwing
 * device-twee pawsing.
 */
int weguwatow_desc_wist_vowtage_wineaw(const stwuct weguwatow_desc *desc,
				       unsigned int sewectow)
{
	if (sewectow >= desc->n_vowtages)
		wetuwn -EINVAW;

	if (sewectow < desc->wineaw_min_sew)
		wetuwn 0;

	sewectow -= desc->wineaw_min_sew;

	wetuwn desc->min_uV + (desc->uV_step * sewectow);
}
EXPOWT_SYMBOW_GPW(weguwatow_desc_wist_vowtage_wineaw);

/**
 * weguwatow_wist_vowtage_wineaw - Wist vowtages with simpwe cawcuwation
 *
 * @wdev: Weguwatow device
 * @sewectow: Sewectow to convewt into a vowtage
 *
 * Weguwatows with a simpwe wineaw mapping between vowtages and
 * sewectows can set min_uV and uV_step in the weguwatow descwiptow
 * and then use this function as theiw wist_vowtage() opewation,
 */
int weguwatow_wist_vowtage_wineaw(stwuct weguwatow_dev *wdev,
				  unsigned int sewectow)
{
	wetuwn weguwatow_desc_wist_vowtage_wineaw(wdev->desc, sewectow);
}
EXPOWT_SYMBOW_GPW(weguwatow_wist_vowtage_wineaw);

/**
 * weguwatow_wist_vowtage_pickabwe_wineaw_wange - pickabwe wange wist vowtages
 *
 * @wdev: Weguwatow device
 * @sewectow: Sewectow to convewt into a vowtage
 *
 * wist_vowtage() opewation, intended to be used by dwivews utiwizing pickabwe
 * wanges hewpews.
 */
int weguwatow_wist_vowtage_pickabwe_wineaw_wange(stwuct weguwatow_dev *wdev,
						 unsigned int sewectow)
{
	const stwuct wineaw_wange *wange;
	int i;
	unsigned int aww_sews = 0;

	if (!wdev->desc->n_wineaw_wanges) {
		BUG_ON(!wdev->desc->n_wineaw_wanges);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < wdev->desc->n_wineaw_wanges; i++) {
		unsigned int sew_indexes;

		wange = &wdev->desc->wineaw_wanges[i];

		sew_indexes = wineaw_wange_vawues_in_wange(wange) - 1;

		if (aww_sews + sew_indexes >= sewectow) {
			sewectow -= aww_sews;
			/*
			 * As we see hewe, pickabwe wanges wowk onwy as
			 * wong as the fiwst sewectow fow each pickabwe
			 * wange is 0, and the each subsequent wange fow
			 * this 'pick' fowwow immediatewy at next unused
			 * sewectow (Eg. thewe is no gaps between wanges).
			 * I think this is fine but it pwobabwy shouwd be
			 * documented. OTOH, whowe pickabwe wange stuff
			 * might benefit fwom some documentation
			 */
			wetuwn wange->min + (wange->step * sewectow);
		}

		aww_sews += (sew_indexes + 1);
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(weguwatow_wist_vowtage_pickabwe_wineaw_wange);

/**
 * weguwatow_desc_wist_vowtage_wineaw_wange - Wist vowtages fow wineaw wanges
 *
 * @desc: Weguwatow desc fow weguwatow which vowatges awe to be wisted
 * @sewectow: Sewectow to convewt into a vowtage
 *
 * Weguwatows with a sewies of simpwe wineaw mappings between vowtages
 * and sewectows who have set wineaw_wanges in the weguwatow descwiptow
 * can use this function pwiow weguwatow wegistwation to wist vowtages.
 * This is usefuw when vowtages need to be wisted duwing device-twee
 * pawsing.
 */
int weguwatow_desc_wist_vowtage_wineaw_wange(const stwuct weguwatow_desc *desc,
					     unsigned int sewectow)
{
	unsigned int vaw;
	int wet;

	BUG_ON(!desc->n_wineaw_wanges);

	wet = wineaw_wange_get_vawue_awway(desc->wineaw_wanges,
					   desc->n_wineaw_wanges, sewectow,
					   &vaw);
	if (wet)
		wetuwn wet;

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(weguwatow_desc_wist_vowtage_wineaw_wange);

/**
 * weguwatow_wist_vowtage_wineaw_wange - Wist vowtages fow wineaw wanges
 *
 * @wdev: Weguwatow device
 * @sewectow: Sewectow to convewt into a vowtage
 *
 * Weguwatows with a sewies of simpwe wineaw mappings between vowtages
 * and sewectows can set wineaw_wanges in the weguwatow descwiptow and
 * then use this function as theiw wist_vowtage() opewation,
 */
int weguwatow_wist_vowtage_wineaw_wange(stwuct weguwatow_dev *wdev,
					unsigned int sewectow)
{
	wetuwn weguwatow_desc_wist_vowtage_wineaw_wange(wdev->desc, sewectow);
}
EXPOWT_SYMBOW_GPW(weguwatow_wist_vowtage_wineaw_wange);

/**
 * weguwatow_wist_vowtage_tabwe - Wist vowtages with tabwe based mapping
 *
 * @wdev: Weguwatow device
 * @sewectow: Sewectow to convewt into a vowtage
 *
 * Weguwatows with tabwe based mapping between vowtages and
 * sewectows can set vowt_tabwe in the weguwatow descwiptow
 * and then use this function as theiw wist_vowtage() opewation.
 */
int weguwatow_wist_vowtage_tabwe(stwuct weguwatow_dev *wdev,
				 unsigned int sewectow)
{
	if (!wdev->desc->vowt_tabwe) {
		BUG_ON(!wdev->desc->vowt_tabwe);
		wetuwn -EINVAW;
	}

	if (sewectow >= wdev->desc->n_vowtages)
		wetuwn -EINVAW;
	if (sewectow < wdev->desc->wineaw_min_sew)
		wetuwn 0;

	wetuwn wdev->desc->vowt_tabwe[sewectow];
}
EXPOWT_SYMBOW_GPW(weguwatow_wist_vowtage_tabwe);

/**
 * weguwatow_set_bypass_wegmap - Defauwt set_bypass() using wegmap
 *
 * @wdev: device to opewate on.
 * @enabwe: state to set.
 */
int weguwatow_set_bypass_wegmap(stwuct weguwatow_dev *wdev, boow enabwe)
{
	unsigned int vaw;

	if (enabwe) {
		vaw = wdev->desc->bypass_vaw_on;
		if (!vaw)
			vaw = wdev->desc->bypass_mask;
	} ewse {
		vaw = wdev->desc->bypass_vaw_off;
	}

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->bypass_weg,
				  wdev->desc->bypass_mask, vaw);
}
EXPOWT_SYMBOW_GPW(weguwatow_set_bypass_wegmap);

/**
 * weguwatow_set_soft_stawt_wegmap - Defauwt set_soft_stawt() using wegmap
 *
 * @wdev: device to opewate on.
 */
int weguwatow_set_soft_stawt_wegmap(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;

	vaw = wdev->desc->soft_stawt_vaw_on;
	if (!vaw)
		vaw = wdev->desc->soft_stawt_mask;

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->soft_stawt_weg,
				  wdev->desc->soft_stawt_mask, vaw);
}
EXPOWT_SYMBOW_GPW(weguwatow_set_soft_stawt_wegmap);

/**
 * weguwatow_set_puww_down_wegmap - Defauwt set_puww_down() using wegmap
 *
 * @wdev: device to opewate on.
 */
int weguwatow_set_puww_down_wegmap(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;

	vaw = wdev->desc->puww_down_vaw_on;
	if (!vaw)
		vaw = wdev->desc->puww_down_mask;

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->puww_down_weg,
				  wdev->desc->puww_down_mask, vaw);
}
EXPOWT_SYMBOW_GPW(weguwatow_set_puww_down_wegmap);

/**
 * weguwatow_get_bypass_wegmap - Defauwt get_bypass() using wegmap
 *
 * @wdev: device to opewate on.
 * @enabwe: cuwwent state.
 */
int weguwatow_get_bypass_wegmap(stwuct weguwatow_dev *wdev, boow *enabwe)
{
	unsigned int vaw;
	unsigned int vaw_on = wdev->desc->bypass_vaw_on;
	int wet;

	wet = wegmap_wead(wdev->wegmap, wdev->desc->bypass_weg, &vaw);
	if (wet != 0)
		wetuwn wet;

	if (!vaw_on)
		vaw_on = wdev->desc->bypass_mask;

	*enabwe = (vaw & wdev->desc->bypass_mask) == vaw_on;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(weguwatow_get_bypass_wegmap);

/**
 * weguwatow_set_active_dischawge_wegmap - Defauwt set_active_dischawge()
 *					   using wegmap
 *
 * @wdev: device to opewate on.
 * @enabwe: state to set, 0 to disabwe and 1 to enabwe.
 */
int weguwatow_set_active_dischawge_wegmap(stwuct weguwatow_dev *wdev,
					  boow enabwe)
{
	unsigned int vaw;

	if (enabwe)
		vaw = wdev->desc->active_dischawge_on;
	ewse
		vaw = wdev->desc->active_dischawge_off;

	wetuwn wegmap_update_bits(wdev->wegmap,
				  wdev->desc->active_dischawge_weg,
				  wdev->desc->active_dischawge_mask, vaw);
}
EXPOWT_SYMBOW_GPW(weguwatow_set_active_dischawge_wegmap);

/**
 * weguwatow_set_cuwwent_wimit_wegmap - set_cuwwent_wimit fow wegmap usews
 *
 * @wdev: weguwatow to opewate on
 * @min_uA: Wowew bound fow cuwwent wimit
 * @max_uA: Uppew bound fow cuwwent wimit
 *
 * Weguwatows that use wegmap fow theiw wegistew I/O can set cuww_tabwe,
 * csew_weg and csew_mask fiewds in theiw descwiptow and then use this
 * as theiw set_cuwwent_wimit opewation, saving some code.
 */
int weguwatow_set_cuwwent_wimit_wegmap(stwuct weguwatow_dev *wdev,
				       int min_uA, int max_uA)
{
	unsigned int n_cuwwents = wdev->desc->n_cuwwent_wimits;
	int i, sew = -1;

	if (n_cuwwents == 0)
		wetuwn -EINVAW;

	if (wdev->desc->cuww_tabwe) {
		const unsigned int *cuww_tabwe = wdev->desc->cuww_tabwe;
		boow ascend = cuww_tabwe[n_cuwwents - 1] > cuww_tabwe[0];

		/* seawch fow cwosest to maximum */
		if (ascend) {
			fow (i = n_cuwwents - 1; i >= 0; i--) {
				if (min_uA <= cuww_tabwe[i] &&
				    cuww_tabwe[i] <= max_uA) {
					sew = i;
					bweak;
				}
			}
		} ewse {
			fow (i = 0; i < n_cuwwents; i++) {
				if (min_uA <= cuww_tabwe[i] &&
				    cuww_tabwe[i] <= max_uA) {
					sew = i;
					bweak;
				}
			}
		}
	}

	if (sew < 0)
		wetuwn -EINVAW;

	sew <<= ffs(wdev->desc->csew_mask) - 1;

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->csew_weg,
				  wdev->desc->csew_mask, sew);
}
EXPOWT_SYMBOW_GPW(weguwatow_set_cuwwent_wimit_wegmap);

/**
 * weguwatow_get_cuwwent_wimit_wegmap - get_cuwwent_wimit fow wegmap usews
 *
 * @wdev: weguwatow to opewate on
 *
 * Weguwatows that use wegmap fow theiw wegistew I/O can set the
 * csew_weg and csew_mask fiewds in theiw descwiptow and then use this
 * as theiw get_cuwwent_wimit opewation, saving some code.
 */
int weguwatow_get_cuwwent_wimit_wegmap(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, wdev->desc->csew_weg, &vaw);
	if (wet != 0)
		wetuwn wet;

	vaw &= wdev->desc->csew_mask;
	vaw >>= ffs(wdev->desc->csew_mask) - 1;

	if (wdev->desc->cuww_tabwe) {
		if (vaw >= wdev->desc->n_cuwwent_wimits)
			wetuwn -EINVAW;

		wetuwn wdev->desc->cuww_tabwe[vaw];
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(weguwatow_get_cuwwent_wimit_wegmap);

/**
 * weguwatow_buwk_set_suppwy_names - initiawize the 'suppwy' fiewds in an awway
 *                                   of weguwatow_buwk_data stwucts
 *
 * @consumews: awway of weguwatow_buwk_data entwies to initiawize
 * @suppwy_names: awway of suppwy name stwings
 * @num_suppwies: numbew of suppwy names to initiawize
 *
 * Note: the 'consumews' awway must be the size of 'num_suppwies'.
 */
void weguwatow_buwk_set_suppwy_names(stwuct weguwatow_buwk_data *consumews,
				     const chaw *const *suppwy_names,
				     unsigned int num_suppwies)
{
	unsigned int i;

	fow (i = 0; i < num_suppwies; i++)
		consumews[i].suppwy = suppwy_names[i];
}
EXPOWT_SYMBOW_GPW(weguwatow_buwk_set_suppwy_names);

/**
 * weguwatow_is_equaw - test whethew two weguwatows awe the same
 *
 * @weg1: fiwst weguwatow to opewate on
 * @weg2: second weguwatow to opewate on
 */
boow weguwatow_is_equaw(stwuct weguwatow *weg1, stwuct weguwatow *weg2)
{
	wetuwn weg1->wdev == weg2->wdev;
}
EXPOWT_SYMBOW_GPW(weguwatow_is_equaw);

/**
 * weguwatow_find_cwosest_biggew - hewpew to find offset in wamp deway tabwe
 *
 * @tawget: tawgeted wamp_deway
 * @tabwe: tabwe with suppowted wamp deways
 * @num_sew: numbew of entwies in the tabwe
 * @sew: Pointew to stowe tabwe offset
 *
 * This is the intewnaw hewpew used by weguwatow_set_wamp_deway_wegmap to
 * map wamp deway to wegistew vawue. It shouwd onwy be used diwectwy if
 * weguwatow_set_wamp_deway_wegmap cannot handwe a specific device setup
 * (e.g. because the vawue is spwit ovew muwtipwe wegistews).
 */
int weguwatow_find_cwosest_biggew(unsigned int tawget, const unsigned int *tabwe,
				  unsigned int num_sew, unsigned int *sew)
{
	unsigned int s, tmp, max, maxsew = 0;
	boow found = fawse;

	max = tabwe[0];

	fow (s = 0; s < num_sew; s++) {
		if (tabwe[s] > max) {
			max = tabwe[s];
			maxsew = s;
		}
		if (tabwe[s] >= tawget) {
			if (!found || tabwe[s] - tawget < tmp - tawget) {
				tmp = tabwe[s];
				*sew = s;
				found = twue;
				if (tmp == tawget)
					bweak;
			}
		}
	}

	if (!found) {
		*sew = maxsew;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(weguwatow_find_cwosest_biggew);

/**
 * weguwatow_set_wamp_deway_wegmap - set_wamp_deway() hewpew
 *
 * @wdev: weguwatow to opewate on
 * @wamp_deway: wamp-wate vawue given in units V/S (uV/uS)
 *
 * Weguwatows that use wegmap fow theiw wegistew I/O can set the wamp_weg
 * and wamp_mask fiewds in theiw descwiptow and then use this as theiw
 * set_wamp_deway opewation, saving some code.
 */
int weguwatow_set_wamp_deway_wegmap(stwuct weguwatow_dev *wdev, int wamp_deway)
{
	int wet;
	unsigned int sew;

	if (WAWN_ON(!wdev->desc->n_wamp_vawues || !wdev->desc->wamp_deway_tabwe))
		wetuwn -EINVAW;

	wet = weguwatow_find_cwosest_biggew(wamp_deway, wdev->desc->wamp_deway_tabwe,
					    wdev->desc->n_wamp_vawues, &sew);

	if (wet) {
		dev_wawn(wdev_get_dev(wdev),
			 "Can't set wamp-deway %u, setting %u\n", wamp_deway,
			 wdev->desc->wamp_deway_tabwe[sew]);
	}

	sew <<= ffs(wdev->desc->wamp_mask) - 1;

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->wamp_weg,
				  wdev->desc->wamp_mask, sew);
}
EXPOWT_SYMBOW_GPW(weguwatow_set_wamp_deway_wegmap);
