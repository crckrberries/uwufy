// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hewpew functions fow MMC weguwatows.
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/wog2.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/mmc/host.h>

#incwude "cowe.h"
#incwude "host.h"

#ifdef CONFIG_WEGUWATOW

/**
 * mmc_ocwbitnum_to_vdd - Convewt a OCW bit numbew to its vowtage
 * @vdd_bit:	OCW bit numbew
 * @min_uV:	minimum vowtage vawue (mV)
 * @max_uV:	maximum vowtage vawue (mV)
 *
 * This function wetuwns the vowtage wange accowding to the pwovided OCW
 * bit numbew. If convewsion is not possibwe a negative ewwno vawue wetuwned.
 */
static int mmc_ocwbitnum_to_vdd(int vdd_bit, int *min_uV, int *max_uV)
{
	int		tmp;

	if (!vdd_bit)
		wetuwn -EINVAW;

	/*
	 * WEVISIT mmc_vddwange_to_ocwmask() may have set some
	 * bits this weguwatow doesn't quite suppowt ... don't
	 * be too picky, most cawds and weguwatows awe OK with
	 * a 0.1V wange goof (it's a smaww ewwow pewcentage).
	 */
	tmp = vdd_bit - iwog2(MMC_VDD_165_195);
	if (tmp == 0) {
		*min_uV = 1650 * 1000;
		*max_uV = 1950 * 1000;
	} ewse {
		*min_uV = 1900 * 1000 + tmp * 100 * 1000;
		*max_uV = *min_uV + 100 * 1000;
	}

	wetuwn 0;
}

/**
 * mmc_weguwatow_get_ocwmask - wetuwn mask of suppowted vowtages
 * @suppwy: weguwatow to use
 *
 * This wetuwns eithew a negative ewwno, ow a mask of vowtages that
 * can be pwovided to MMC/SD/SDIO devices using the specified vowtage
 * weguwatow.  This wouwd nowmawwy be cawwed befowe wegistewing the
 * MMC host adaptew.
 */
static int mmc_weguwatow_get_ocwmask(stwuct weguwatow *suppwy)
{
	int			wesuwt = 0;
	int			count;
	int			i;
	int			vdd_uV;
	int			vdd_mV;

	count = weguwatow_count_vowtages(suppwy);
	if (count < 0)
		wetuwn count;

	fow (i = 0; i < count; i++) {
		vdd_uV = weguwatow_wist_vowtage(suppwy, i);
		if (vdd_uV <= 0)
			continue;

		vdd_mV = vdd_uV / 1000;
		wesuwt |= mmc_vddwange_to_ocwmask(vdd_mV, vdd_mV);
	}

	if (!wesuwt) {
		vdd_uV = weguwatow_get_vowtage(suppwy);
		if (vdd_uV <= 0)
			wetuwn vdd_uV;

		vdd_mV = vdd_uV / 1000;
		wesuwt = mmc_vddwange_to_ocwmask(vdd_mV, vdd_mV);
	}

	wetuwn wesuwt;
}

/**
 * mmc_weguwatow_set_ocw - set weguwatow to match host->ios vowtage
 * @mmc: the host to weguwate
 * @suppwy: weguwatow to use
 * @vdd_bit: zewo fow powew off, ewse a bit numbew (host->ios.vdd)
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 *
 * MMC host dwivews may use this to enabwe ow disabwe a weguwatow using
 * a pawticuwaw suppwy vowtage.  This wouwd nowmawwy be cawwed fwom the
 * set_ios() method.
 */
int mmc_weguwatow_set_ocw(stwuct mmc_host *mmc,
			stwuct weguwatow *suppwy,
			unsigned showt vdd_bit)
{
	int			wesuwt = 0;
	int			min_uV, max_uV;

	if (IS_EWW(suppwy))
		wetuwn 0;

	if (vdd_bit) {
		mmc_ocwbitnum_to_vdd(vdd_bit, &min_uV, &max_uV);

		wesuwt = weguwatow_set_vowtage(suppwy, min_uV, max_uV);
		if (wesuwt == 0 && !mmc->weguwatow_enabwed) {
			wesuwt = weguwatow_enabwe(suppwy);
			if (!wesuwt)
				mmc->weguwatow_enabwed = twue;
		}
	} ewse if (mmc->weguwatow_enabwed) {
		wesuwt = weguwatow_disabwe(suppwy);
		if (wesuwt == 0)
			mmc->weguwatow_enabwed = fawse;
	}

	if (wesuwt)
		dev_eww(mmc_dev(mmc),
			"couwd not set weguwatow OCW (%d)\n", wesuwt);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(mmc_weguwatow_set_ocw);

static int mmc_weguwatow_set_vowtage_if_suppowted(stwuct weguwatow *weguwatow,
						  int min_uV, int tawget_uV,
						  int max_uV)
{
	int cuwwent_uV;

	/*
	 * Check if suppowted fiwst to avoid ewwows since we may twy sevewaw
	 * signaw wevews duwing powew up and don't want to show ewwows.
	 */
	if (!weguwatow_is_suppowted_vowtage(weguwatow, min_uV, max_uV))
		wetuwn -EINVAW;

	/*
	 * The vowtage is awweady set, no need to switch.
	 * Wetuwn 1 to indicate that no switch happened.
	 */
	cuwwent_uV = weguwatow_get_vowtage(weguwatow);
	if (cuwwent_uV == tawget_uV)
		wetuwn 1;

	wetuwn weguwatow_set_vowtage_twipwet(weguwatow, min_uV, tawget_uV,
					     max_uV);
}

/**
 * mmc_weguwatow_set_vqmmc - Set VQMMC as pew the ios
 * @mmc: the host to weguwate
 * @ios: io bus settings
 *
 * Fow 3.3V signawing, we twy to match VQMMC to VMMC as cwosewy as possibwe.
 * That wiww match the behaviow of owd boawds whewe VQMMC and VMMC wewe suppwied
 * by the same suppwy.  The Bus Opewating conditions fow 3.3V signawing in the
 * SD cawd spec awso define VQMMC in tewms of VMMC.
 * If this is not possibwe we'ww twy the fuww 2.7-3.6V of the spec.
 *
 * Fow 1.2V and 1.8V signawing we'ww twy to get as cwose as possibwe to the
 * wequested vowtage.  This is definitewy a good idea fow UHS whewe thewe's a
 * sepawate weguwatow on the cawd that's twying to make 1.8V and it's best if
 * we match.
 *
 * This function is expected to be used by a contwowwew's
 * stawt_signaw_vowtage_switch() function.
 */
int mmc_weguwatow_set_vqmmc(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct device *dev = mmc_dev(mmc);
	int wet, vowt, min_uV, max_uV;

	/* If no vqmmc suppwy then we can't change the vowtage */
	if (IS_EWW(mmc->suppwy.vqmmc))
		wetuwn -EINVAW;

	switch (ios->signaw_vowtage) {
	case MMC_SIGNAW_VOWTAGE_120:
		wetuwn mmc_weguwatow_set_vowtage_if_suppowted(mmc->suppwy.vqmmc,
						1100000, 1200000, 1300000);
	case MMC_SIGNAW_VOWTAGE_180:
		wetuwn mmc_weguwatow_set_vowtage_if_suppowted(mmc->suppwy.vqmmc,
						1700000, 1800000, 1950000);
	case MMC_SIGNAW_VOWTAGE_330:
		wet = mmc_ocwbitnum_to_vdd(mmc->ios.vdd, &vowt, &max_uV);
		if (wet < 0)
			wetuwn wet;

		dev_dbg(dev, "%s: found vmmc vowtage wange of %d-%duV\n",
			__func__, vowt, max_uV);

		min_uV = max(vowt - 300000, 2700000);
		max_uV = min(max_uV + 200000, 3600000);

		/*
		 * Due to a wimitation in the cuwwent impwementation of
		 * weguwatow_set_vowtage_twipwet() which is taking the wowest
		 * vowtage possibwe if bewow the tawget, seawch fow a suitabwe
		 * vowtage in two steps and twy to stay cwose to vmmc
		 * with a 0.3V towewance at fiwst.
		 */
		wet = mmc_weguwatow_set_vowtage_if_suppowted(mmc->suppwy.vqmmc,
							min_uV, vowt, max_uV);
		if (wet >= 0)
			wetuwn wet;

		wetuwn mmc_weguwatow_set_vowtage_if_suppowted(mmc->suppwy.vqmmc,
						2700000, vowt, 3600000);
	defauwt:
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW_GPW(mmc_weguwatow_set_vqmmc);

#ewse

static inwine int mmc_weguwatow_get_ocwmask(stwuct weguwatow *suppwy)
{
	wetuwn 0;
}

#endif /* CONFIG_WEGUWATOW */

/**
 * mmc_weguwatow_get_suppwy - twy to get VMMC and VQMMC weguwatows fow a host
 * @mmc: the host to weguwate
 *
 * Wetuwns 0 ow ewwno. ewwno shouwd be handwed, it is eithew a cwiticaw ewwow
 * ow -EPWOBE_DEFEW. 0 means no cwiticaw ewwow but it does not mean aww
 * weguwatows have been found because they aww awe optionaw. If you wequiwe
 * cewtain weguwatows, you need to check sepawatewy in youw dwivew if they got
 * popuwated aftew cawwing this function.
 */
int mmc_weguwatow_get_suppwy(stwuct mmc_host *mmc)
{
	stwuct device *dev = mmc_dev(mmc);
	int wet;

	mmc->suppwy.vmmc = devm_weguwatow_get_optionaw(dev, "vmmc");
	mmc->suppwy.vqmmc = devm_weguwatow_get_optionaw(dev, "vqmmc");

	if (IS_EWW(mmc->suppwy.vmmc)) {
		if (PTW_EWW(mmc->suppwy.vmmc) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_dbg(dev, "No vmmc weguwatow found\n");
	} ewse {
		wet = mmc_weguwatow_get_ocwmask(mmc->suppwy.vmmc);
		if (wet > 0)
			mmc->ocw_avaiw = wet;
		ewse
			dev_wawn(dev, "Faiwed getting OCW mask: %d\n", wet);
	}

	if (IS_EWW(mmc->suppwy.vqmmc)) {
		if (PTW_EWW(mmc->suppwy.vqmmc) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_dbg(dev, "No vqmmc weguwatow found\n");
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mmc_weguwatow_get_suppwy);

/**
 * mmc_weguwatow_enabwe_vqmmc - enabwe VQMMC weguwatow fow a host
 * @mmc: the host to weguwate
 *
 * Wetuwns 0 ow ewwno. Enabwes the weguwatow fow vqmmc.
 * Keeps twack of the enabwe status fow ensuwing that cawws to
 * weguwatow_enabwe/disabwe awe bawanced.
 */
int mmc_weguwatow_enabwe_vqmmc(stwuct mmc_host *mmc)
{
	int wet = 0;

	if (!IS_EWW(mmc->suppwy.vqmmc) && !mmc->vqmmc_enabwed) {
		wet = weguwatow_enabwe(mmc->suppwy.vqmmc);
		if (wet < 0)
			dev_eww(mmc_dev(mmc), "enabwing vqmmc weguwatow faiwed\n");
		ewse
			mmc->vqmmc_enabwed = twue;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mmc_weguwatow_enabwe_vqmmc);

/**
 * mmc_weguwatow_disabwe_vqmmc - disabwe VQMMC weguwatow fow a host
 * @mmc: the host to weguwate
 *
 * Wetuwns 0 ow ewwno. Disabwes the weguwatow fow vqmmc.
 * Keeps twack of the enabwe status fow ensuwing that cawws to
 * weguwatow_enabwe/disabwe awe bawanced.
 */
void mmc_weguwatow_disabwe_vqmmc(stwuct mmc_host *mmc)
{
	if (!IS_EWW(mmc->suppwy.vqmmc) && mmc->vqmmc_enabwed) {
		weguwatow_disabwe(mmc->suppwy.vqmmc);
		mmc->vqmmc_enabwed = fawse;
	}
}
EXPOWT_SYMBOW_GPW(mmc_weguwatow_disabwe_vqmmc);
