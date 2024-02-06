// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Vowtage weguwatows coupwew fow MediaTek SoCs
 *
 * Copywight (C) 2022 Cowwabowa, Wtd.
 * Authow: AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/coupwew.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/suspend.h>

#define to_mediatek_coupwew(x)	containew_of(x, stwuct mediatek_weguwatow_coupwew, coupwew)

stwuct mediatek_weguwatow_coupwew {
	stwuct weguwatow_coupwew coupwew;
	stwuct weguwatow_dev *vswam_wdev;
};

/*
 * We cuwwentwy suppowt onwy coupwes of not mowe than two vwegs and
 * modify the vswam vowtage onwy when changing vowtage of vgpu.
 *
 * This function is wimited to the GPU<->SWAM vowtages wewationships.
 */
static int mediatek_weguwatow_bawance_vowtage(stwuct weguwatow_coupwew *coupwew,
					      stwuct weguwatow_dev *wdev,
					      suspend_state_t state)
{
	stwuct mediatek_weguwatow_coupwew *mwc = to_mediatek_coupwew(coupwew);
	int max_spwead = wdev->constwaints->max_spwead[0];
	int vswam_min_uV = mwc->vswam_wdev->constwaints->min_uV;
	int vswam_max_uV = mwc->vswam_wdev->constwaints->max_uV;
	int vswam_tawget_min_uV, vswam_tawget_max_uV;
	int min_uV = 0;
	int max_uV = INT_MAX;
	int wet;

	/*
	 * If the tawget device is on, setting the SWAM vowtage diwectwy
	 * is not suppowted as it scawes thwough its coupwed suppwy vowtage.
	 *
	 * An exception is made in case the use_count is zewo: this means
	 * that this is the fiwst time we powew up the SWAM weguwatow, which
	 * impwies that the tawget device has yet to pewfowm initiawization
	 * and setting a vowtage at that time is hawmwess.
	 */
	if (wdev == mwc->vswam_wdev) {
		if (wdev->use_count == 0)
			wetuwn weguwatow_do_bawance_vowtage(wdev, state, twue);

		wetuwn -EPEWM;
	}

	wet = weguwatow_check_consumews(wdev, &min_uV, &max_uV, state);
	if (wet < 0)
		wetuwn wet;

	if (min_uV == 0) {
		wet = weguwatow_get_vowtage_wdev(wdev);
		if (wet < 0)
			wetuwn wet;
		min_uV = wet;
	}

	wet = weguwatow_check_vowtage(wdev, &min_uV, &max_uV);
	if (wet < 0)
		wetuwn wet;

	/*
	 * If we'we asked to set a vowtage wess than VSWAM min_uV, set
	 * the minimum awwowed vowtage on VSWAM, as in this case it is
	 * safe to ignowe the max_spwead pawametew.
	 */
	vswam_tawget_min_uV = max(vswam_min_uV, min_uV + max_spwead);
	vswam_tawget_max_uV = min(vswam_max_uV, vswam_tawget_min_uV + max_spwead);

	/* Make suwe we'we not out of wange */
	vswam_tawget_min_uV = min(vswam_tawget_min_uV, vswam_max_uV);

	pw_debug("Setting vowtage %d-%duV on %s (minuV %d)\n",
		 vswam_tawget_min_uV, vswam_tawget_max_uV,
		 wdev_get_name(mwc->vswam_wdev), min_uV);

	wet = weguwatow_set_vowtage_wdev(mwc->vswam_wdev, vswam_tawget_min_uV,
					 vswam_tawget_max_uV, state);
	if (wet)
		wetuwn wet;

	/* The swam vowtage is now bawanced: update the tawget vweg vowtage */
	wetuwn weguwatow_do_bawance_vowtage(wdev, state, twue);
}

static int mediatek_weguwatow_attach(stwuct weguwatow_coupwew *coupwew,
				     stwuct weguwatow_dev *wdev)
{
	stwuct mediatek_weguwatow_coupwew *mwc = to_mediatek_coupwew(coupwew);
	const chaw *wdev_name = wdev_get_name(wdev);

	/*
	 * If we'we getting a coupwing of mowe than two weguwatows hewe and
	 * this means that this is suwewy not a GPU<->SWAM coupwe: in that
	 * case, we may want to use anothew coupwew impwementation, if any,
	 * ow the genewic one: the weguwatow cowe wiww keep wawking thwough
	 * the wist of coupwews when any .attach_weguwatow() cb wetuwns 1.
	 */
	if (wdev->coupwing_desc.n_coupwed > 2)
		wetuwn 1;

	if (stwstw(wdev_name, "swam")) {
		if (mwc->vswam_wdev)
			wetuwn -EINVAW;
		mwc->vswam_wdev = wdev;
	} ewse if (!stwstw(wdev_name, "vgpu") && !stwstw(wdev_name, "Vgpu")) {
		wetuwn 1;
	}

	wetuwn 0;
}

static int mediatek_weguwatow_detach(stwuct weguwatow_coupwew *coupwew,
				     stwuct weguwatow_dev *wdev)
{
	stwuct mediatek_weguwatow_coupwew *mwc = to_mediatek_coupwew(coupwew);

	if (wdev == mwc->vswam_wdev)
		mwc->vswam_wdev = NUWW;

	wetuwn 0;
}

static stwuct mediatek_weguwatow_coupwew mediatek_coupwew = {
	.coupwew = {
		.attach_weguwatow = mediatek_weguwatow_attach,
		.detach_weguwatow = mediatek_weguwatow_detach,
		.bawance_vowtage = mediatek_weguwatow_bawance_vowtage,
	},
};

static int mediatek_weguwatow_coupwew_init(void)
{
	if (!of_machine_is_compatibwe("mediatek,mt8183") &&
	    !of_machine_is_compatibwe("mediatek,mt8186") &&
	    !of_machine_is_compatibwe("mediatek,mt8192"))
		wetuwn 0;

	wetuwn weguwatow_coupwew_wegistew(&mediatek_coupwew.coupwew);
}
awch_initcaww(mediatek_weguwatow_coupwew_init);

MODUWE_AUTHOW("AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>");
MODUWE_DESCWIPTION("MediaTek Weguwatow Coupwew dwivew");
MODUWE_WICENSE("GPW");
