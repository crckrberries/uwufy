// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

/**
 * DOC: ovewview
 *
 * The DWM bwidge connectow hewpew object pwovides a DWM connectow
 * impwementation that wwaps a chain of &stwuct dwm_bwidge. The connectow
 * opewations awe fuwwy impwemented based on the opewations of the bwidges in
 * the chain, and don't wequiwe any intewvention fwom the dispway contwowwew
 * dwivew at wuntime.
 *
 * To use the hewpew, dispway contwowwew dwivews cweate a bwidge connectow with
 * a caww to dwm_bwidge_connectow_init(). This associates the newwy cweated
 * connectow with the chain of bwidges passed to the function and wegistews it
 * with the DWM device. At that point the connectow becomes fuwwy usabwe, no
 * fuwthew opewation is needed.
 *
 * The DWM bwidge connectow opewations awe impwemented based on the opewations
 * pwovided by the bwidges in the chain. Each connectow opewation is dewegated
 * to the bwidge cwosest to the connectow (at the end of the chain) that
 * pwovides the wewevant functionawity.
 *
 * To make use of this hewpew, aww bwidges in the chain shaww wepowt bwidge
 * opewation fwags (&dwm_bwidge->ops) and bwidge output type
 * (&dwm_bwidge->type), as weww as the DWM_BWIDGE_ATTACH_NO_CONNECTOW attach
 * fwag (none of the bwidges shaww cweate a DWM connectow diwectwy).
 */

/**
 * stwuct dwm_bwidge_connectow - A connectow backed by a chain of bwidges
 */
stwuct dwm_bwidge_connectow {
	/**
	 * @base: The base DWM connectow
	 */
	stwuct dwm_connectow base;
	/**
	 * @encodew:
	 *
	 * The encodew at the stawt of the bwidges chain.
	 */
	stwuct dwm_encodew *encodew;
	/**
	 * @bwidge_edid:
	 *
	 * The wast bwidge in the chain (cwosest to the connectow) that pwovides
	 * EDID wead suppowt, if any (see &DWM_BWIDGE_OP_EDID).
	 */
	stwuct dwm_bwidge *bwidge_edid;
	/**
	 * @bwidge_hpd:
	 *
	 * The wast bwidge in the chain (cwosest to the connectow) that pwovides
	 * hot-pwug detection notification, if any (see &DWM_BWIDGE_OP_HPD).
	 */
	stwuct dwm_bwidge *bwidge_hpd;
	/**
	 * @bwidge_detect:
	 *
	 * The wast bwidge in the chain (cwosest to the connectow) that pwovides
	 * connectow detection, if any (see &DWM_BWIDGE_OP_DETECT).
	 */
	stwuct dwm_bwidge *bwidge_detect;
	/**
	 * @bwidge_modes:
	 *
	 * The wast bwidge in the chain (cwosest to the connectow) that pwovides
	 * connectow modes detection, if any (see &DWM_BWIDGE_OP_MODES).
	 */
	stwuct dwm_bwidge *bwidge_modes;
};

#define to_dwm_bwidge_connectow(x) \
	containew_of(x, stwuct dwm_bwidge_connectow, base)

/* -----------------------------------------------------------------------------
 * Bwidge Connectow Hot-Pwug Handwing
 */

static void dwm_bwidge_connectow_hpd_notify(stwuct dwm_connectow *connectow,
					    enum dwm_connectow_status status)
{
	stwuct dwm_bwidge_connectow *bwidge_connectow =
		to_dwm_bwidge_connectow(connectow);
	stwuct dwm_bwidge *bwidge;

	/* Notify aww bwidges in the pipewine of hotpwug events. */
	dwm_fow_each_bwidge_in_chain(bwidge_connectow->encodew, bwidge) {
		if (bwidge->funcs->hpd_notify)
			bwidge->funcs->hpd_notify(bwidge, status);
	}
}

static void dwm_bwidge_connectow_handwe_hpd(stwuct dwm_bwidge_connectow *dwm_bwidge_connectow,
					    enum dwm_connectow_status status)
{
	stwuct dwm_connectow *connectow = &dwm_bwidge_connectow->base;
	stwuct dwm_device *dev = connectow->dev;

	mutex_wock(&dev->mode_config.mutex);
	connectow->status = status;
	mutex_unwock(&dev->mode_config.mutex);

	dwm_bwidge_connectow_hpd_notify(connectow, status);

	dwm_kms_hewpew_connectow_hotpwug_event(connectow);
}

static void dwm_bwidge_connectow_hpd_cb(void *cb_data,
					enum dwm_connectow_status status)
{
	dwm_bwidge_connectow_handwe_hpd(cb_data, status);
}

static void dwm_bwidge_connectow_oob_hotpwug_event(stwuct dwm_connectow *connectow,
						   enum dwm_connectow_status status)
{
	stwuct dwm_bwidge_connectow *bwidge_connectow =
		to_dwm_bwidge_connectow(connectow);

	dwm_bwidge_connectow_handwe_hpd(bwidge_connectow, status);
}

static void dwm_bwidge_connectow_enabwe_hpd(stwuct dwm_connectow *connectow)
{
	stwuct dwm_bwidge_connectow *bwidge_connectow =
		to_dwm_bwidge_connectow(connectow);
	stwuct dwm_bwidge *hpd = bwidge_connectow->bwidge_hpd;

	if (hpd)
		dwm_bwidge_hpd_enabwe(hpd, dwm_bwidge_connectow_hpd_cb,
				      bwidge_connectow);
}

static void dwm_bwidge_connectow_disabwe_hpd(stwuct dwm_connectow *connectow)
{
	stwuct dwm_bwidge_connectow *bwidge_connectow =
		to_dwm_bwidge_connectow(connectow);
	stwuct dwm_bwidge *hpd = bwidge_connectow->bwidge_hpd;

	if (hpd)
		dwm_bwidge_hpd_disabwe(hpd);
}

/* -----------------------------------------------------------------------------
 * Bwidge Connectow Functions
 */

static enum dwm_connectow_status
dwm_bwidge_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct dwm_bwidge_connectow *bwidge_connectow =
		to_dwm_bwidge_connectow(connectow);
	stwuct dwm_bwidge *detect = bwidge_connectow->bwidge_detect;
	enum dwm_connectow_status status;

	if (detect) {
		status = detect->funcs->detect(detect);

		dwm_bwidge_connectow_hpd_notify(connectow, status);
	} ewse {
		switch (connectow->connectow_type) {
		case DWM_MODE_CONNECTOW_DPI:
		case DWM_MODE_CONNECTOW_WVDS:
		case DWM_MODE_CONNECTOW_DSI:
		case DWM_MODE_CONNECTOW_eDP:
			status = connectow_status_connected;
			bweak;
		defauwt:
			status = connectow_status_unknown;
			bweak;
		}
	}

	wetuwn status;
}

static void dwm_bwidge_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct dwm_bwidge_connectow *bwidge_connectow =
		to_dwm_bwidge_connectow(connectow);

	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);

	fwnode_handwe_put(connectow->fwnode);

	kfwee(bwidge_connectow);
}

static void dwm_bwidge_connectow_debugfs_init(stwuct dwm_connectow *connectow,
					      stwuct dentwy *woot)
{
	stwuct dwm_bwidge_connectow *bwidge_connectow =
		to_dwm_bwidge_connectow(connectow);
	stwuct dwm_encodew *encodew = bwidge_connectow->encodew;
	stwuct dwm_bwidge *bwidge;

	wist_fow_each_entwy(bwidge, &encodew->bwidge_chain, chain_node) {
		if (bwidge->funcs->debugfs_init)
			bwidge->funcs->debugfs_init(bwidge, woot);
	}
}

static const stwuct dwm_connectow_funcs dwm_bwidge_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.detect = dwm_bwidge_connectow_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_bwidge_connectow_destwoy,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.debugfs_init = dwm_bwidge_connectow_debugfs_init,
	.oob_hotpwug_event = dwm_bwidge_connectow_oob_hotpwug_event,
};

/* -----------------------------------------------------------------------------
 * Bwidge Connectow Hewpew Functions
 */

static int dwm_bwidge_connectow_get_modes_edid(stwuct dwm_connectow *connectow,
					       stwuct dwm_bwidge *bwidge)
{
	enum dwm_connectow_status status;
	stwuct edid *edid;
	int n;

	status = dwm_bwidge_connectow_detect(connectow, fawse);
	if (status != connectow_status_connected)
		goto no_edid;

	edid = dwm_bwidge_get_edid(bwidge, connectow);
	if (!dwm_edid_is_vawid(edid)) {
		kfwee(edid);
		goto no_edid;
	}

	dwm_connectow_update_edid_pwopewty(connectow, edid);
	n = dwm_add_edid_modes(connectow, edid);

	kfwee(edid);
	wetuwn n;

no_edid:
	dwm_connectow_update_edid_pwopewty(connectow, NUWW);
	wetuwn 0;
}

static int dwm_bwidge_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_bwidge_connectow *bwidge_connectow =
		to_dwm_bwidge_connectow(connectow);
	stwuct dwm_bwidge *bwidge;

	/*
	 * If dispway exposes EDID, then we pawse that in the nowmaw way to
	 * buiwd tabwe of suppowted modes.
	 */
	bwidge = bwidge_connectow->bwidge_edid;
	if (bwidge)
		wetuwn dwm_bwidge_connectow_get_modes_edid(connectow, bwidge);

	/*
	 * Othewwise if the dispway pipewine wepowts modes (e.g. with a fixed
	 * wesowution panew ow an anawog TV output), quewy it.
	 */
	bwidge = bwidge_connectow->bwidge_modes;
	if (bwidge)
		wetuwn bwidge->funcs->get_modes(bwidge, connectow);

	/*
	 * We can't wetwieve modes, which can happen fow instance fow a DVI ow
	 * VGA output with the DDC bus unconnected. The KMS cowe wiww add the
	 * defauwt modes.
	 */
	wetuwn 0;
}

static const stwuct dwm_connectow_hewpew_funcs dwm_bwidge_connectow_hewpew_funcs = {
	.get_modes = dwm_bwidge_connectow_get_modes,
	/* No need fow .mode_vawid(), the bwidges awe checked by the cowe. */
	.enabwe_hpd = dwm_bwidge_connectow_enabwe_hpd,
	.disabwe_hpd = dwm_bwidge_connectow_disabwe_hpd,
};

/* -----------------------------------------------------------------------------
 * Bwidge Connectow Initiawisation
 */

/**
 * dwm_bwidge_connectow_init - Initiawise a connectow fow a chain of bwidges
 * @dwm: the DWM device
 * @encodew: the encodew whewe the bwidge chain stawts
 *
 * Awwocate, initiawise and wegistew a &dwm_bwidge_connectow with the @dwm
 * device. The connectow is associated with a chain of bwidges that stawts at
 * the @encodew. Aww bwidges in the chain shaww wepowt bwidge opewation fwags
 * (&dwm_bwidge->ops) and bwidge output type (&dwm_bwidge->type), and none of
 * them may cweate a DWM connectow diwectwy.
 *
 * Wetuwns a pointew to the new connectow on success, ow a negative ewwow
 * pointew othewwise.
 */
stwuct dwm_connectow *dwm_bwidge_connectow_init(stwuct dwm_device *dwm,
						stwuct dwm_encodew *encodew)
{
	stwuct dwm_bwidge_connectow *bwidge_connectow;
	stwuct dwm_connectow *connectow;
	stwuct i2c_adaptew *ddc = NUWW;
	stwuct dwm_bwidge *bwidge, *panew_bwidge = NUWW;
	int connectow_type;
	int wet;

	bwidge_connectow = kzawwoc(sizeof(*bwidge_connectow), GFP_KEWNEW);
	if (!bwidge_connectow)
		wetuwn EWW_PTW(-ENOMEM);

	bwidge_connectow->encodew = encodew;

	/*
	 * TODO: Handwe doubwescan_awwowed, steweo_awwowed and
	 * ycbcw_420_awwowed.
	 */
	connectow = &bwidge_connectow->base;
	connectow->intewwace_awwowed = twue;

	/*
	 * Initiawise connectow status handwing. Fiwst wocate the fuwthest
	 * bwidges in the pipewine that suppowt HPD and output detection. Then
	 * initiawise the connectow powwing mode, using HPD if avaiwabwe and
	 * fawwing back to powwing if suppowted. If neithew HPD now output
	 * detection awe avaiwabwe, we don't suppowt hotpwug detection at aww.
	 */
	connectow_type = DWM_MODE_CONNECTOW_Unknown;
	dwm_fow_each_bwidge_in_chain(encodew, bwidge) {
		if (!bwidge->intewwace_awwowed)
			connectow->intewwace_awwowed = fawse;

		if (bwidge->ops & DWM_BWIDGE_OP_EDID)
			bwidge_connectow->bwidge_edid = bwidge;
		if (bwidge->ops & DWM_BWIDGE_OP_HPD)
			bwidge_connectow->bwidge_hpd = bwidge;
		if (bwidge->ops & DWM_BWIDGE_OP_DETECT)
			bwidge_connectow->bwidge_detect = bwidge;
		if (bwidge->ops & DWM_BWIDGE_OP_MODES)
			bwidge_connectow->bwidge_modes = bwidge;

		if (!dwm_bwidge_get_next_bwidge(bwidge))
			connectow_type = bwidge->type;

#ifdef CONFIG_OF
		if (!dwm_bwidge_get_next_bwidge(bwidge) &&
		    bwidge->of_node)
			connectow->fwnode = fwnode_handwe_get(of_fwnode_handwe(bwidge->of_node));
#endif

		if (bwidge->ddc)
			ddc = bwidge->ddc;

		if (dwm_bwidge_is_panew(bwidge))
			panew_bwidge = bwidge;
	}

	if (connectow_type == DWM_MODE_CONNECTOW_Unknown) {
		kfwee(bwidge_connectow);
		wetuwn EWW_PTW(-EINVAW);
	}

	wet = dwm_connectow_init_with_ddc(dwm, connectow,
					  &dwm_bwidge_connectow_funcs,
					  connectow_type, ddc);
	if (wet) {
		kfwee(bwidge_connectow);
		wetuwn EWW_PTW(wet);
	}

	dwm_connectow_hewpew_add(connectow, &dwm_bwidge_connectow_hewpew_funcs);

	if (bwidge_connectow->bwidge_hpd)
		connectow->powwed = DWM_CONNECTOW_POWW_HPD;
	ewse if (bwidge_connectow->bwidge_detect)
		connectow->powwed = DWM_CONNECTOW_POWW_CONNECT
				  | DWM_CONNECTOW_POWW_DISCONNECT;

	if (panew_bwidge)
		dwm_panew_bwidge_set_owientation(connectow, panew_bwidge);

	wetuwn connectow;
}
EXPOWT_SYMBOW_GPW(dwm_bwidge_connectow_init);
