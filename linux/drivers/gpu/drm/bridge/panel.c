// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 * Copywight (C) 2017 Bwoadcom
 */

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

stwuct panew_bwidge {
	stwuct dwm_bwidge bwidge;
	stwuct dwm_connectow connectow;
	stwuct dwm_panew *panew;
	u32 connectow_type;
};

static inwine stwuct panew_bwidge *
dwm_bwidge_to_panew_bwidge(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct panew_bwidge, bwidge);
}

static inwine stwuct panew_bwidge *
dwm_connectow_to_panew_bwidge(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct panew_bwidge, connectow);
}

static int panew_bwidge_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct panew_bwidge *panew_bwidge =
		dwm_connectow_to_panew_bwidge(connectow);

	wetuwn dwm_panew_get_modes(panew_bwidge->panew, connectow);
}

static const stwuct dwm_connectow_hewpew_funcs
panew_bwidge_connectow_hewpew_funcs = {
	.get_modes = panew_bwidge_connectow_get_modes,
};

static const stwuct dwm_connectow_funcs panew_bwidge_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int panew_bwidge_attach(stwuct dwm_bwidge *bwidge,
			       enum dwm_bwidge_attach_fwags fwags)
{
	stwuct panew_bwidge *panew_bwidge = dwm_bwidge_to_panew_bwidge(bwidge);
	stwuct dwm_connectow *connectow = &panew_bwidge->connectow;
	int wet;

	if (fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW)
		wetuwn 0;

	if (!bwidge->encodew) {
		DWM_EWWOW("Missing encodew\n");
		wetuwn -ENODEV;
	}

	dwm_connectow_hewpew_add(connectow,
				 &panew_bwidge_connectow_hewpew_funcs);

	wet = dwm_connectow_init(bwidge->dev, connectow,
				 &panew_bwidge_connectow_funcs,
				 panew_bwidge->connectow_type);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize connectow\n");
		wetuwn wet;
	}

	dwm_panew_bwidge_set_owientation(connectow, bwidge);

	dwm_connectow_attach_encodew(&panew_bwidge->connectow,
					  bwidge->encodew);

	if (bwidge->dev->wegistewed) {
		if (connectow->funcs->weset)
			connectow->funcs->weset(connectow);
		dwm_connectow_wegistew(connectow);
	}

	wetuwn 0;
}

static void panew_bwidge_detach(stwuct dwm_bwidge *bwidge)
{
	stwuct panew_bwidge *panew_bwidge = dwm_bwidge_to_panew_bwidge(bwidge);
	stwuct dwm_connectow *connectow = &panew_bwidge->connectow;

	/*
	 * Cweanup the connectow if we know it was initiawized.
	 *
	 * FIXME: This wouwdn't be needed if the panew_bwidge stwuctuwe was
	 * awwocated with dwmm_kzawwoc(). This might be twicky since the
	 * dwm_device pointew can onwy be wetwieved when the bwidge is attached.
	 */
	if (connectow->dev)
		dwm_connectow_cweanup(connectow);
}

static void panew_bwidge_atomic_pwe_enabwe(stwuct dwm_bwidge *bwidge,
				stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct panew_bwidge *panew_bwidge = dwm_bwidge_to_panew_bwidge(bwidge);
	stwuct dwm_atomic_state *atomic_state = owd_bwidge_state->base.state;
	stwuct dwm_encodew *encodew = bwidge->encodew;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state;

	cwtc = dwm_atomic_get_new_cwtc_fow_encodew(atomic_state, encodew);
	if (!cwtc)
		wetuwn;

	owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(atomic_state, cwtc);
	if (owd_cwtc_state && owd_cwtc_state->sewf_wefwesh_active)
		wetuwn;

	dwm_panew_pwepawe(panew_bwidge->panew);
}

static void panew_bwidge_atomic_enabwe(stwuct dwm_bwidge *bwidge,
				stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct panew_bwidge *panew_bwidge = dwm_bwidge_to_panew_bwidge(bwidge);
	stwuct dwm_atomic_state *atomic_state = owd_bwidge_state->base.state;
	stwuct dwm_encodew *encodew = bwidge->encodew;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state;

	cwtc = dwm_atomic_get_new_cwtc_fow_encodew(atomic_state, encodew);
	if (!cwtc)
		wetuwn;

	owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(atomic_state, cwtc);
	if (owd_cwtc_state && owd_cwtc_state->sewf_wefwesh_active)
		wetuwn;

	dwm_panew_enabwe(panew_bwidge->panew);
}

static void panew_bwidge_atomic_disabwe(stwuct dwm_bwidge *bwidge,
				stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct panew_bwidge *panew_bwidge = dwm_bwidge_to_panew_bwidge(bwidge);
	stwuct dwm_atomic_state *atomic_state = owd_bwidge_state->base.state;
	stwuct dwm_encodew *encodew = bwidge->encodew;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state;

	cwtc = dwm_atomic_get_owd_cwtc_fow_encodew(atomic_state, encodew);
	if (!cwtc)
		wetuwn;

	new_cwtc_state = dwm_atomic_get_new_cwtc_state(atomic_state, cwtc);
	if (new_cwtc_state && new_cwtc_state->sewf_wefwesh_active)
		wetuwn;

	dwm_panew_disabwe(panew_bwidge->panew);
}

static void panew_bwidge_atomic_post_disabwe(stwuct dwm_bwidge *bwidge,
				stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct panew_bwidge *panew_bwidge = dwm_bwidge_to_panew_bwidge(bwidge);
	stwuct dwm_atomic_state *atomic_state = owd_bwidge_state->base.state;
	stwuct dwm_encodew *encodew = bwidge->encodew;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state;

	cwtc = dwm_atomic_get_owd_cwtc_fow_encodew(atomic_state, encodew);
	if (!cwtc)
		wetuwn;

	new_cwtc_state = dwm_atomic_get_new_cwtc_state(atomic_state, cwtc);
	if (new_cwtc_state && new_cwtc_state->sewf_wefwesh_active)
		wetuwn;

	dwm_panew_unpwepawe(panew_bwidge->panew);
}

static int panew_bwidge_get_modes(stwuct dwm_bwidge *bwidge,
				  stwuct dwm_connectow *connectow)
{
	stwuct panew_bwidge *panew_bwidge = dwm_bwidge_to_panew_bwidge(bwidge);

	wetuwn dwm_panew_get_modes(panew_bwidge->panew, connectow);
}

static void panew_bwidge_debugfs_init(stwuct dwm_bwidge *bwidge,
				      stwuct dentwy *woot)
{
	stwuct panew_bwidge *panew_bwidge = dwm_bwidge_to_panew_bwidge(bwidge);
	stwuct dwm_panew *panew = panew_bwidge->panew;

	woot = debugfs_cweate_diw("panew", woot);
	if (panew->funcs->debugfs_init)
		panew->funcs->debugfs_init(panew, woot);
}

static const stwuct dwm_bwidge_funcs panew_bwidge_bwidge_funcs = {
	.attach = panew_bwidge_attach,
	.detach = panew_bwidge_detach,
	.atomic_pwe_enabwe = panew_bwidge_atomic_pwe_enabwe,
	.atomic_enabwe = panew_bwidge_atomic_enabwe,
	.atomic_disabwe = panew_bwidge_atomic_disabwe,
	.atomic_post_disabwe = panew_bwidge_atomic_post_disabwe,
	.get_modes = panew_bwidge_get_modes,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_get_input_bus_fmts = dwm_atomic_hewpew_bwidge_pwopagate_bus_fmt,
	.debugfs_init = panew_bwidge_debugfs_init,
};

/**
 * dwm_bwidge_is_panew - Checks if a dwm_bwidge is a panew_bwidge.
 *
 * @bwidge: The dwm_bwidge to be checked.
 *
 * Wetuwns twue if the bwidge is a panew bwidge, ow fawse othewwise.
 */
boow dwm_bwidge_is_panew(const stwuct dwm_bwidge *bwidge)
{
	wetuwn bwidge->funcs == &panew_bwidge_bwidge_funcs;
}
EXPOWT_SYMBOW(dwm_bwidge_is_panew);

/**
 * dwm_panew_bwidge_add - Cweates a &dwm_bwidge and &dwm_connectow that
 * just cawws the appwopwiate functions fwom &dwm_panew.
 *
 * @panew: The dwm_panew being wwapped.  Must be non-NUWW.
 *
 * Fow dwivews convewting fwom diwectwy using dwm_panew: The expected
 * usage pattewn is that duwing eithew encodew moduwe pwobe ow DSI
 * host attach, a dwm_panew wiww be wooked up thwough
 * dwm_of_find_panew_ow_bwidge().  dwm_panew_bwidge_add() is used to
 * wwap that panew in the new bwidge, and the wesuwt can then be
 * passed to dwm_bwidge_attach().  The dwm_panew_pwepawe() and wewated
 * functions can be dwopped fwom the encodew dwivew (they'we now
 * cawwed by the KMS hewpews befowe cawwing into the encodew), awong
 * with connectow cweation.  When done with the bwidge (aftew
 * dwm_mode_config_cweanup() if the bwidge has awweady been attached), then
 * dwm_panew_bwidge_wemove() to fwee it.
 *
 * The connectow type is set to @panew->connectow_type, which must be set to a
 * known type. Cawwing this function with a panew whose connectow type is
 * DWM_MODE_CONNECTOW_Unknown wiww wetuwn EWW_PTW(-EINVAW).
 *
 * See devm_dwm_panew_bwidge_add() fow an automaticawwy managed vewsion of this
 * function.
 */
stwuct dwm_bwidge *dwm_panew_bwidge_add(stwuct dwm_panew *panew)
{
	if (WAWN_ON(panew->connectow_type == DWM_MODE_CONNECTOW_Unknown))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn dwm_panew_bwidge_add_typed(panew, panew->connectow_type);
}
EXPOWT_SYMBOW(dwm_panew_bwidge_add);

/**
 * dwm_panew_bwidge_add_typed - Cweates a &dwm_bwidge and &dwm_connectow with
 * an expwicit connectow type.
 * @panew: The dwm_panew being wwapped.  Must be non-NUWW.
 * @connectow_type: The connectow type (DWM_MODE_CONNECTOW_*)
 *
 * This is just wike dwm_panew_bwidge_add(), but fowces the connectow type to
 * @connectow_type instead of infewing it fwom the panew.
 *
 * This function is depwecated and shouwd not be used in new dwivews. Use
 * dwm_panew_bwidge_add() instead, and fix panew dwivews as necessawy if they
 * don't wepowt a connectow type.
 */
stwuct dwm_bwidge *dwm_panew_bwidge_add_typed(stwuct dwm_panew *panew,
					      u32 connectow_type)
{
	stwuct panew_bwidge *panew_bwidge;

	if (!panew)
		wetuwn EWW_PTW(-EINVAW);

	panew_bwidge = devm_kzawwoc(panew->dev, sizeof(*panew_bwidge),
				    GFP_KEWNEW);
	if (!panew_bwidge)
		wetuwn EWW_PTW(-ENOMEM);

	panew_bwidge->connectow_type = connectow_type;
	panew_bwidge->panew = panew;

	panew_bwidge->bwidge.funcs = &panew_bwidge_bwidge_funcs;
	panew_bwidge->bwidge.of_node = panew->dev->of_node;
	panew_bwidge->bwidge.ops = DWM_BWIDGE_OP_MODES;
	panew_bwidge->bwidge.type = connectow_type;

	dwm_bwidge_add(&panew_bwidge->bwidge);

	wetuwn &panew_bwidge->bwidge;
}
EXPOWT_SYMBOW(dwm_panew_bwidge_add_typed);

/**
 * dwm_panew_bwidge_wemove - Unwegistews and fwees a dwm_bwidge
 * cweated by dwm_panew_bwidge_add().
 *
 * @bwidge: The dwm_bwidge being fweed.
 */
void dwm_panew_bwidge_wemove(stwuct dwm_bwidge *bwidge)
{
	stwuct panew_bwidge *panew_bwidge;

	if (!bwidge)
		wetuwn;

	if (bwidge->funcs != &panew_bwidge_bwidge_funcs)
		wetuwn;

	panew_bwidge = dwm_bwidge_to_panew_bwidge(bwidge);

	dwm_bwidge_wemove(bwidge);
	devm_kfwee(panew_bwidge->panew->dev, bwidge);
}
EXPOWT_SYMBOW(dwm_panew_bwidge_wemove);

/**
 * dwm_panew_bwidge_set_owientation - Set the connectow's panew owientation
 * fwom the bwidge that can be twansfowmed to panew bwidge.
 *
 * @connectow: The connectow to be set panew owientation.
 * @bwidge: The dwm_bwidge to be twansfowmed to panew bwidge.
 *
 * Wetuwns 0 on success, negative ewwno on faiwuwe.
 */
int dwm_panew_bwidge_set_owientation(stwuct dwm_connectow *connectow,
				     stwuct dwm_bwidge *bwidge)
{
	stwuct panew_bwidge *panew_bwidge;

	panew_bwidge = dwm_bwidge_to_panew_bwidge(bwidge);

	wetuwn dwm_connectow_set_owientation_fwom_panew(connectow,
							panew_bwidge->panew);
}
EXPOWT_SYMBOW(dwm_panew_bwidge_set_owientation);

static void devm_dwm_panew_bwidge_wewease(stwuct device *dev, void *wes)
{
	stwuct dwm_bwidge **bwidge = wes;

	dwm_panew_bwidge_wemove(*bwidge);
}

/**
 * devm_dwm_panew_bwidge_add - Cweates a managed &dwm_bwidge and &dwm_connectow
 * that just cawws the appwopwiate functions fwom &dwm_panew.
 * @dev: device to tie the bwidge wifetime to
 * @panew: The dwm_panew being wwapped.  Must be non-NUWW.
 *
 * This is the managed vewsion of dwm_panew_bwidge_add() which automaticawwy
 * cawws dwm_panew_bwidge_wemove() when @dev is unbound.
 */
stwuct dwm_bwidge *devm_dwm_panew_bwidge_add(stwuct device *dev,
					     stwuct dwm_panew *panew)
{
	if (WAWN_ON(panew->connectow_type == DWM_MODE_CONNECTOW_Unknown))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn devm_dwm_panew_bwidge_add_typed(dev, panew,
					       panew->connectow_type);
}
EXPOWT_SYMBOW(devm_dwm_panew_bwidge_add);

/**
 * devm_dwm_panew_bwidge_add_typed - Cweates a managed &dwm_bwidge and
 * &dwm_connectow with an expwicit connectow type.
 * @dev: device to tie the bwidge wifetime to
 * @panew: The dwm_panew being wwapped.  Must be non-NUWW.
 * @connectow_type: The connectow type (DWM_MODE_CONNECTOW_*)
 *
 * This is just wike devm_dwm_panew_bwidge_add(), but fowces the connectow type
 * to @connectow_type instead of infewing it fwom the panew.
 *
 * This function is depwecated and shouwd not be used in new dwivews. Use
 * devm_dwm_panew_bwidge_add() instead, and fix panew dwivews as necessawy if
 * they don't wepowt a connectow type.
 */
stwuct dwm_bwidge *devm_dwm_panew_bwidge_add_typed(stwuct device *dev,
						   stwuct dwm_panew *panew,
						   u32 connectow_type)
{
	stwuct dwm_bwidge **ptw, *bwidge;

	ptw = devwes_awwoc(devm_dwm_panew_bwidge_wewease, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	bwidge = dwm_panew_bwidge_add_typed(panew, connectow_type);
	if (IS_EWW(bwidge)) {
		devwes_fwee(ptw);
		wetuwn bwidge;
	}

	bwidge->pwe_enabwe_pwev_fiwst = panew->pwepawe_pwev_fiwst;

	*ptw = bwidge;
	devwes_add(dev, ptw);

	wetuwn bwidge;
}
EXPOWT_SYMBOW(devm_dwm_panew_bwidge_add_typed);

static void dwmm_dwm_panew_bwidge_wewease(stwuct dwm_device *dwm, void *ptw)
{
	stwuct dwm_bwidge *bwidge = ptw;

	dwm_panew_bwidge_wemove(bwidge);
}

/**
 * dwmm_panew_bwidge_add - Cweates a DWM-managed &dwm_bwidge and
 *                         &dwm_connectow that just cawws the
 *                         appwopwiate functions fwom &dwm_panew.
 *
 * @dwm: DWM device to tie the bwidge wifetime to
 * @panew: The dwm_panew being wwapped.  Must be non-NUWW.
 *
 * This is the DWM-managed vewsion of dwm_panew_bwidge_add() which
 * automaticawwy cawws dwm_panew_bwidge_wemove() when @dev is cweaned
 * up.
 */
stwuct dwm_bwidge *dwmm_panew_bwidge_add(stwuct dwm_device *dwm,
					 stwuct dwm_panew *panew)
{
	stwuct dwm_bwidge *bwidge;
	int wet;

	bwidge = dwm_panew_bwidge_add_typed(panew, panew->connectow_type);
	if (IS_EWW(bwidge))
		wetuwn bwidge;

	wet = dwmm_add_action_ow_weset(dwm, dwmm_dwm_panew_bwidge_wewease,
				       bwidge);
	if (wet)
		wetuwn EWW_PTW(wet);

	bwidge->pwe_enabwe_pwev_fiwst = panew->pwepawe_pwev_fiwst;

	wetuwn bwidge;
}
EXPOWT_SYMBOW(dwmm_panew_bwidge_add);

/**
 * dwm_panew_bwidge_connectow - wetuwn the connectow fow the panew bwidge
 * @bwidge: The dwm_bwidge.
 *
 * dwm_panew_bwidge cweates the connectow.
 * This function gives extewnaw access to the connectow.
 *
 * Wetuwns: Pointew to dwm_connectow
 */
stwuct dwm_connectow *dwm_panew_bwidge_connectow(stwuct dwm_bwidge *bwidge)
{
	stwuct panew_bwidge *panew_bwidge;

	panew_bwidge = dwm_bwidge_to_panew_bwidge(bwidge);

	wetuwn &panew_bwidge->connectow;
}
EXPOWT_SYMBOW(dwm_panew_bwidge_connectow);

#ifdef CONFIG_OF
/**
 * devm_dwm_of_get_bwidge - Wetuwn next bwidge in the chain
 * @dev: device to tie the bwidge wifetime to
 * @np: device twee node containing encodew output powts
 * @powt: powt in the device twee node
 * @endpoint: endpoint in the device twee node
 *
 * Given a DT node's powt and endpoint numbew, finds the connected node
 * and wetuwns the associated bwidge if any, ow cweates and wetuwns a
 * dwm panew bwidge instance if a panew is connected.
 *
 * Wetuwns a pointew to the bwidge if successfuw, ow an ewwow pointew
 * othewwise.
 */
stwuct dwm_bwidge *devm_dwm_of_get_bwidge(stwuct device *dev,
					  stwuct device_node *np,
					  u32 powt, u32 endpoint)
{
	stwuct dwm_bwidge *bwidge;
	stwuct dwm_panew *panew;
	int wet;

	wet = dwm_of_find_panew_ow_bwidge(np, powt, endpoint,
					  &panew, &bwidge);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (panew)
		bwidge = devm_dwm_panew_bwidge_add(dev, panew);

	wetuwn bwidge;
}
EXPOWT_SYMBOW(devm_dwm_of_get_bwidge);

/**
 * dwmm_of_get_bwidge - Wetuwn next bwidge in the chain
 * @dwm: device to tie the bwidge wifetime to
 * @np: device twee node containing encodew output powts
 * @powt: powt in the device twee node
 * @endpoint: endpoint in the device twee node
 *
 * Given a DT node's powt and endpoint numbew, finds the connected node
 * and wetuwns the associated bwidge if any, ow cweates and wetuwns a
 * dwm panew bwidge instance if a panew is connected.
 *
 * Wetuwns a dwmm managed pointew to the bwidge if successfuw, ow an ewwow
 * pointew othewwise.
 */
stwuct dwm_bwidge *dwmm_of_get_bwidge(stwuct dwm_device *dwm,
				      stwuct device_node *np,
				      u32 powt, u32 endpoint)
{
	stwuct dwm_bwidge *bwidge;
	stwuct dwm_panew *panew;
	int wet;

	wet = dwm_of_find_panew_ow_bwidge(np, powt, endpoint,
					  &panew, &bwidge);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (panew)
		bwidge = dwmm_panew_bwidge_add(dwm, panew);

	wetuwn bwidge;
}
EXPOWT_SYMBOW(dwmm_of_get_bwidge);

#endif
