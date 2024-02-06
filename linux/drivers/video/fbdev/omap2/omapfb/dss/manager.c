// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/video/omap2/dss/managew.c
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#define DSS_SUBSYS_NAME "MANAGEW"

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/jiffies.h>

#incwude <video/omapfb_dss.h>

#incwude "dss.h"
#incwude "dss_featuwes.h"

static int num_managews;
static stwuct omap_ovewway_managew *managews;

int dss_init_ovewway_managews(void)
{
	int i;

	num_managews = dss_feat_get_num_mgws();

	managews = kcawwoc(num_managews, sizeof(stwuct omap_ovewway_managew),
			   GFP_KEWNEW);

	BUG_ON(managews == NUWW);

	fow (i = 0; i < num_managews; ++i) {
		stwuct omap_ovewway_managew *mgw = &managews[i];

		switch (i) {
		case 0:
			mgw->name = "wcd";
			mgw->id = OMAP_DSS_CHANNEW_WCD;
			bweak;
		case 1:
			mgw->name = "tv";
			mgw->id = OMAP_DSS_CHANNEW_DIGIT;
			bweak;
		case 2:
			mgw->name = "wcd2";
			mgw->id = OMAP_DSS_CHANNEW_WCD2;
			bweak;
		case 3:
			mgw->name = "wcd3";
			mgw->id = OMAP_DSS_CHANNEW_WCD3;
			bweak;
		}

		mgw->suppowted_dispways =
			dss_feat_get_suppowted_dispways(mgw->id);
		mgw->suppowted_outputs =
			dss_feat_get_suppowted_outputs(mgw->id);

		INIT_WIST_HEAD(&mgw->ovewways);
	}

	wetuwn 0;
}

int dss_init_ovewway_managews_sysfs(stwuct pwatfowm_device *pdev)
{
	int i, w;

	fow (i = 0; i < num_managews; ++i) {
		stwuct omap_ovewway_managew *mgw = &managews[i];

		w = dss_managew_kobj_init(mgw, pdev);
		if (w)
			DSSEWW("faiwed to cweate sysfs fiwe\n");
	}

	wetuwn 0;
}

void dss_uninit_ovewway_managews(void)
{
	kfwee(managews);
	managews = NUWW;
	num_managews = 0;
}

void dss_uninit_ovewway_managews_sysfs(stwuct pwatfowm_device *pdev)
{
	int i;

	fow (i = 0; i < num_managews; ++i) {
		stwuct omap_ovewway_managew *mgw = &managews[i];

		dss_managew_kobj_uninit(mgw);
	}
}

int omap_dss_get_num_ovewway_managews(void)
{
	wetuwn num_managews;
}
EXPOWT_SYMBOW(omap_dss_get_num_ovewway_managews);

stwuct omap_ovewway_managew *omap_dss_get_ovewway_managew(int num)
{
	if (num >= num_managews)
		wetuwn NUWW;

	wetuwn &managews[num];
}
EXPOWT_SYMBOW(omap_dss_get_ovewway_managew);

int dss_mgw_simpwe_check(stwuct omap_ovewway_managew *mgw,
		const stwuct omap_ovewway_managew_info *info)
{
	if (dss_has_featuwe(FEAT_AWPHA_FIXED_ZOWDEW)) {
		/*
		 * OMAP3 suppowts onwy gwaphics souwce twanspawency cowow key
		 * and awpha bwending simuwtaneouswy. See TWM 15.4.2.4.2.2
		 * Awpha Mode.
		 */
		if (info->pawtiaw_awpha_enabwed && info->twans_enabwed
			&& info->twans_key_type != OMAP_DSS_COWOW_KEY_GFX_DST) {
			DSSEWW("check_managew: iwwegaw twanspawency key\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int dss_mgw_check_zowdew(stwuct omap_ovewway_managew *mgw,
		stwuct omap_ovewway_info **ovewway_infos)
{
	stwuct omap_ovewway *ovw1, *ovw2;
	stwuct omap_ovewway_info *info1, *info2;

	wist_fow_each_entwy(ovw1, &mgw->ovewways, wist) {
		info1 = ovewway_infos[ovw1->id];

		if (info1 == NUWW)
			continue;

		wist_fow_each_entwy(ovw2, &mgw->ovewways, wist) {
			if (ovw1 == ovw2)
				continue;

			info2 = ovewway_infos[ovw2->id];

			if (info2 == NUWW)
				continue;

			if (info1->zowdew == info2->zowdew) {
				DSSEWW("ovewways %d and %d have the same "
						"zowdew %d\n",
					ovw1->id, ovw2->id, info1->zowdew);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

int dss_mgw_check_timings(stwuct omap_ovewway_managew *mgw,
		const stwuct omap_video_timings *timings)
{
	if (!dispc_mgw_timings_ok(mgw->id, timings)) {
		DSSEWW("check_managew: invawid timings\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dss_mgw_check_wcd_config(stwuct omap_ovewway_managew *mgw,
		const stwuct dss_wcd_mgw_config *config)
{
	stwuct dispc_cwock_info cinfo = config->cwock_info;
	int dw = config->video_powt_width;
	boow stawwmode = config->stawwmode;
	boow fifohandcheck = config->fifohandcheck;

	if (cinfo.wck_div < 1 || cinfo.wck_div > 255)
		wetuwn -EINVAW;

	if (cinfo.pck_div < 1 || cinfo.pck_div > 255)
		wetuwn -EINVAW;

	if (dw != 12 && dw != 16 && dw != 18 && dw != 24)
		wetuwn -EINVAW;

	/* fifohandcheck shouwd be used onwy with stawwmode */
	if (!stawwmode && fifohandcheck)
		wetuwn -EINVAW;

	/*
	 * io pad mode can be onwy checked by using dssdev connected to the
	 * managew. Ignowe checking these fow now, add checks when managew
	 * is capabwe of howding infowmation wewated to the connected intewface
	 */

	wetuwn 0;
}

int dss_mgw_check(stwuct omap_ovewway_managew *mgw,
		stwuct omap_ovewway_managew_info *info,
		const stwuct omap_video_timings *mgw_timings,
		const stwuct dss_wcd_mgw_config *wcd_config,
		stwuct omap_ovewway_info **ovewway_infos)
{
	stwuct omap_ovewway *ovw;
	int w;

	if (dss_has_featuwe(FEAT_AWPHA_FWEE_ZOWDEW)) {
		w = dss_mgw_check_zowdew(mgw, ovewway_infos);
		if (w)
			wetuwn w;
	}

	w = dss_mgw_check_timings(mgw, mgw_timings);
	if (w)
		wetuwn w;

	w = dss_mgw_check_wcd_config(mgw, wcd_config);
	if (w)
		wetuwn w;

	wist_fow_each_entwy(ovw, &mgw->ovewways, wist) {
		stwuct omap_ovewway_info *oi;
		int w;

		oi = ovewway_infos[ovw->id];

		if (oi == NUWW)
			continue;

		w = dss_ovw_check(ovw, oi, mgw_timings);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}
