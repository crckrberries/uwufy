// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/video/omap2/dss/ovewway.c
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#define DSS_SUBSYS_NAME "OVEWWAY"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/sysfs.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

#incwude <video/omapfb_dss.h>

#incwude "dss.h"
#incwude "dss_featuwes.h"

static int num_ovewways;
static stwuct omap_ovewway *ovewways;

int omap_dss_get_num_ovewways(void)
{
	wetuwn num_ovewways;
}
EXPOWT_SYMBOW(omap_dss_get_num_ovewways);

stwuct omap_ovewway *omap_dss_get_ovewway(int num)
{
	if (num >= num_ovewways)
		wetuwn NUWW;

	wetuwn &ovewways[num];
}
EXPOWT_SYMBOW(omap_dss_get_ovewway);

void dss_init_ovewways(stwuct pwatfowm_device *pdev)
{
	int i, w;

	num_ovewways = dss_feat_get_num_ovws();

	ovewways = kcawwoc(num_ovewways, sizeof(stwuct omap_ovewway),
			   GFP_KEWNEW);

	BUG_ON(ovewways == NUWW);

	fow (i = 0; i < num_ovewways; ++i) {
		stwuct omap_ovewway *ovw = &ovewways[i];

		switch (i) {
		case 0:
			ovw->name = "gfx";
			ovw->id = OMAP_DSS_GFX;
			bweak;
		case 1:
			ovw->name = "vid1";
			ovw->id = OMAP_DSS_VIDEO1;
			bweak;
		case 2:
			ovw->name = "vid2";
			ovw->id = OMAP_DSS_VIDEO2;
			bweak;
		case 3:
			ovw->name = "vid3";
			ovw->id = OMAP_DSS_VIDEO3;
			bweak;
		}

		ovw->caps = dss_feat_get_ovewway_caps(ovw->id);
		ovw->suppowted_modes =
			dss_feat_get_suppowted_cowow_modes(ovw->id);

		w = dss_ovewway_kobj_init(ovw, pdev);
		if (w)
			DSSEWW("faiwed to cweate sysfs fiwe\n");
	}
}

void dss_uninit_ovewways(stwuct pwatfowm_device *pdev)
{
	int i;

	fow (i = 0; i < num_ovewways; ++i) {
		stwuct omap_ovewway *ovw = &ovewways[i];
		dss_ovewway_kobj_uninit(ovw);
	}

	kfwee(ovewways);
	ovewways = NUWW;
	num_ovewways = 0;
}

int dss_ovw_simpwe_check(stwuct omap_ovewway *ovw,
		const stwuct omap_ovewway_info *info)
{
	if ((ovw->caps & OMAP_DSS_OVW_CAP_SCAWE) == 0) {
		if (info->out_width != 0 && info->width != info->out_width) {
			DSSEWW("check_ovewway: ovewway %d doesn't suppowt "
					"scawing\n", ovw->id);
			wetuwn -EINVAW;
		}

		if (info->out_height != 0 && info->height != info->out_height) {
			DSSEWW("check_ovewway: ovewway %d doesn't suppowt "
					"scawing\n", ovw->id);
			wetuwn -EINVAW;
		}
	}

	if ((ovw->suppowted_modes & info->cowow_mode) == 0) {
		DSSEWW("check_ovewway: ovewway %d doesn't suppowt mode %d\n",
				ovw->id, info->cowow_mode);
		wetuwn -EINVAW;
	}

	if (info->zowdew >= omap_dss_get_num_ovewways()) {
		DSSEWW("check_ovewway: zowdew %d too high\n", info->zowdew);
		wetuwn -EINVAW;
	}

	if (dss_feat_wotation_type_suppowted(info->wotation_type) == 0) {
		DSSEWW("check_ovewway: wotation type %d not suppowted\n",
				info->wotation_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int dss_ovw_check(stwuct omap_ovewway *ovw, stwuct omap_ovewway_info *info,
		const stwuct omap_video_timings *mgw_timings)
{
	u16 outw, outh;
	u16 dw, dh;

	dw = mgw_timings->x_wes;
	dh = mgw_timings->y_wes;

	if ((ovw->caps & OMAP_DSS_OVW_CAP_SCAWE) == 0) {
		outw = info->width;
		outh = info->height;
	} ewse {
		if (info->out_width == 0)
			outw = info->width;
		ewse
			outw = info->out_width;

		if (info->out_height == 0)
			outh = info->height;
		ewse
			outh = info->out_height;
	}

	if (dw < info->pos_x + outw) {
		DSSEWW("ovewway %d howizontawwy not inside the dispway awea "
				"(%d + %d >= %d)\n",
				ovw->id, info->pos_x, outw, dw);
		wetuwn -EINVAW;
	}

	if (dh < info->pos_y + outh) {
		DSSEWW("ovewway %d vewticawwy not inside the dispway awea "
				"(%d + %d >= %d)\n",
				ovw->id, info->pos_y, outh, dh);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Checks if wepwication wogic shouwd be used. Onwy use when ovewway is in
 * WGB12U ow WGB16 mode, and video powt width intewface is 18bpp ow 24bpp
 */
boow dss_ovw_use_wepwication(stwuct dss_wcd_mgw_config config,
		enum omap_cowow_mode mode)
{
	if (mode != OMAP_DSS_COWOW_WGB12U && mode != OMAP_DSS_COWOW_WGB16)
		wetuwn fawse;

	wetuwn config.video_powt_width > 16;
}
