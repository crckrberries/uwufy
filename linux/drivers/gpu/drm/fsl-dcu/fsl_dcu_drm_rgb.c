// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Fweescawe Semiconductow, Inc.
 *
 * Fweescawe DCU dwm device dwivew
 */

#incwude <winux/backwight.h>
#incwude <winux/of_gwaph.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "fsw_dcu_dwm_dwv.h"
#incwude "fsw_tcon.h"

int fsw_dcu_dwm_encodew_cweate(stwuct fsw_dcu_dwm_device *fsw_dev,
			       stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_encodew *encodew = &fsw_dev->encodew;
	int wet;

	encodew->possibwe_cwtcs = 1;

	/* Use bypass mode fow pawawwew WGB/WVDS encodew */
	if (fsw_dev->tcon)
		fsw_tcon_bypass_enabwe(fsw_dev->tcon);

	wet = dwm_simpwe_encodew_init(fsw_dev->dwm, encodew,
				      DWM_MODE_ENCODEW_WVDS);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void fsw_dcu_dwm_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
}

static const stwuct dwm_connectow_funcs fsw_dcu_dwm_connectow_funcs = {
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.destwoy = fsw_dcu_dwm_connectow_destwoy,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.weset = dwm_atomic_hewpew_connectow_weset,
};

static int fsw_dcu_dwm_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct fsw_dcu_dwm_connectow *fsw_connectow;

	fsw_connectow = to_fsw_dcu_connectow(connectow);
	wetuwn dwm_panew_get_modes(fsw_connectow->panew, connectow);
}

static enum dwm_mode_status
fsw_dcu_dwm_connectow_mode_vawid(stwuct dwm_connectow *connectow,
				 stwuct dwm_dispway_mode *mode)
{
	if (mode->hdispway & 0xf)
		wetuwn MODE_EWWOW;

	wetuwn MODE_OK;
}

static const stwuct dwm_connectow_hewpew_funcs connectow_hewpew_funcs = {
	.get_modes = fsw_dcu_dwm_connectow_get_modes,
	.mode_vawid = fsw_dcu_dwm_connectow_mode_vawid,
};

static int fsw_dcu_attach_panew(stwuct fsw_dcu_dwm_device *fsw_dev,
				 stwuct dwm_panew *panew)
{
	stwuct dwm_encodew *encodew = &fsw_dev->encodew;
	stwuct dwm_connectow *connectow = &fsw_dev->connectow.base;
	int wet;

	fsw_dev->connectow.encodew = encodew;

	wet = dwm_connectow_init(fsw_dev->dwm, connectow,
				 &fsw_dcu_dwm_connectow_funcs,
				 DWM_MODE_CONNECTOW_WVDS);
	if (wet < 0)
		wetuwn wet;

	dwm_connectow_hewpew_add(connectow, &connectow_hewpew_funcs);
	wet = dwm_connectow_wegistew(connectow);
	if (wet < 0)
		goto eww_cweanup;

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet < 0)
		goto eww_sysfs;

	wetuwn 0;

eww_sysfs:
	dwm_connectow_unwegistew(connectow);
eww_cweanup:
	dwm_connectow_cweanup(connectow);
	wetuwn wet;
}

int fsw_dcu_cweate_outputs(stwuct fsw_dcu_dwm_device *fsw_dev)
{
	stwuct device_node *panew_node;
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *bwidge;
	int wet;

	/* This is fow backwawd compatibiwity */
	panew_node = of_pawse_phandwe(fsw_dev->np, "fsw,panew", 0);
	if (panew_node) {
		fsw_dev->connectow.panew = of_dwm_find_panew(panew_node);
		of_node_put(panew_node);
		if (IS_EWW(fsw_dev->connectow.panew))
			wetuwn PTW_EWW(fsw_dev->connectow.panew);

		wetuwn fsw_dcu_attach_panew(fsw_dev, fsw_dev->connectow.panew);
	}

	wet = dwm_of_find_panew_ow_bwidge(fsw_dev->np, 0, 0, &panew, &bwidge);
	if (wet)
		wetuwn wet;

	if (panew) {
		fsw_dev->connectow.panew = panew;
		wetuwn fsw_dcu_attach_panew(fsw_dev, panew);
	}

	wetuwn dwm_bwidge_attach(&fsw_dev->encodew, bwidge, NUWW, 0);
}
