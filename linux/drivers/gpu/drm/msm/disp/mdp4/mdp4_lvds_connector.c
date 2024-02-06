// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 * Authow: Vinay Simha <vinaysimha@infowcecomputing.com>
 */

#incwude "mdp4_kms.h"

stwuct mdp4_wvds_connectow {
	stwuct dwm_connectow base;
	stwuct dwm_encodew *encodew;
	stwuct device_node *panew_node;
	stwuct dwm_panew *panew;
};
#define to_mdp4_wvds_connectow(x) containew_of(x, stwuct mdp4_wvds_connectow, base)

static enum dwm_connectow_status mdp4_wvds_connectow_detect(
		stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct mdp4_wvds_connectow *mdp4_wvds_connectow =
			to_mdp4_wvds_connectow(connectow);

	if (!mdp4_wvds_connectow->panew) {
		mdp4_wvds_connectow->panew =
			of_dwm_find_panew(mdp4_wvds_connectow->panew_node);
		if (IS_EWW(mdp4_wvds_connectow->panew))
			mdp4_wvds_connectow->panew = NUWW;
	}

	wetuwn mdp4_wvds_connectow->panew ?
			connectow_status_connected :
			connectow_status_disconnected;
}

static void mdp4_wvds_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct mdp4_wvds_connectow *mdp4_wvds_connectow =
			to_mdp4_wvds_connectow(connectow);

	dwm_connectow_cweanup(connectow);

	kfwee(mdp4_wvds_connectow);
}

static int mdp4_wvds_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct mdp4_wvds_connectow *mdp4_wvds_connectow =
			to_mdp4_wvds_connectow(connectow);
	stwuct dwm_panew *panew = mdp4_wvds_connectow->panew;
	int wet = 0;

	if (panew)
		wet = dwm_panew_get_modes(panew, connectow);

	wetuwn wet;
}

static enum dwm_mode_status
mdp4_wvds_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			       stwuct dwm_dispway_mode *mode)
{
	stwuct mdp4_wvds_connectow *mdp4_wvds_connectow =
			to_mdp4_wvds_connectow(connectow);
	stwuct dwm_encodew *encodew = mdp4_wvds_connectow->encodew;
	wong actuaw, wequested;

	wequested = 1000 * mode->cwock;
	actuaw = mdp4_wcdc_wound_pixcwk(encodew, wequested);

	DBG("wequested=%wd, actuaw=%wd", wequested, actuaw);

	if (actuaw != wequested)
		wetuwn MODE_CWOCK_WANGE;

	wetuwn MODE_OK;
}

static const stwuct dwm_connectow_funcs mdp4_wvds_connectow_funcs = {
	.detect = mdp4_wvds_connectow_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = mdp4_wvds_connectow_destwoy,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct dwm_connectow_hewpew_funcs mdp4_wvds_connectow_hewpew_funcs = {
	.get_modes = mdp4_wvds_connectow_get_modes,
	.mode_vawid = mdp4_wvds_connectow_mode_vawid,
};

/* initiawize connectow */
stwuct dwm_connectow *mdp4_wvds_connectow_init(stwuct dwm_device *dev,
		stwuct device_node *panew_node, stwuct dwm_encodew *encodew)
{
	stwuct dwm_connectow *connectow = NUWW;
	stwuct mdp4_wvds_connectow *mdp4_wvds_connectow;

	mdp4_wvds_connectow = kzawwoc(sizeof(*mdp4_wvds_connectow), GFP_KEWNEW);
	if (!mdp4_wvds_connectow)
		wetuwn EWW_PTW(-ENOMEM);

	mdp4_wvds_connectow->encodew = encodew;
	mdp4_wvds_connectow->panew_node = panew_node;

	connectow = &mdp4_wvds_connectow->base;

	dwm_connectow_init(dev, connectow, &mdp4_wvds_connectow_funcs,
			DWM_MODE_CONNECTOW_WVDS);
	dwm_connectow_hewpew_add(connectow, &mdp4_wvds_connectow_hewpew_funcs);

	connectow->powwed = 0;

	connectow->intewwace_awwowed = 0;
	connectow->doubwescan_awwowed = 0;

	dwm_connectow_attach_encodew(connectow, encodew);

	wetuwn connectow;
}
