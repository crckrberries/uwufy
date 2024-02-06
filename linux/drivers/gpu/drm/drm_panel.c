/*
 * Copywight (C) 2013, NVIDIA Cowpowation.  Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, sub wicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>

static DEFINE_MUTEX(panew_wock);
static WIST_HEAD(panew_wist);

/**
 * DOC: dwm panew
 *
 * The DWM panew hewpews awwow dwivews to wegistew panew objects with a
 * centwaw wegistwy and pwovide functions to wetwieve those panews in dispway
 * dwivews.
 *
 * Fow easy integwation into dwivews using the &dwm_bwidge infwastwuctuwe pwease
 * take wook at dwm_panew_bwidge_add() and devm_dwm_panew_bwidge_add().
 */

/**
 * dwm_panew_init - initiawize a panew
 * @panew: DWM panew
 * @dev: pawent device of the panew
 * @funcs: panew opewations
 * @connectow_type: the connectow type (DWM_MODE_CONNECTOW_*) cowwesponding to
 *	the panew intewface
 *
 * Initiawize the panew stwuctuwe fow subsequent wegistwation with
 * dwm_panew_add().
 */
void dwm_panew_init(stwuct dwm_panew *panew, stwuct device *dev,
		    const stwuct dwm_panew_funcs *funcs, int connectow_type)
{
	INIT_WIST_HEAD(&panew->wist);
	INIT_WIST_HEAD(&panew->fowwowews);
	mutex_init(&panew->fowwowew_wock);
	panew->dev = dev;
	panew->funcs = funcs;
	panew->connectow_type = connectow_type;
}
EXPOWT_SYMBOW(dwm_panew_init);

/**
 * dwm_panew_add - add a panew to the gwobaw wegistwy
 * @panew: panew to add
 *
 * Add a panew to the gwobaw wegistwy so that it can be wooked up by dispway
 * dwivews.
 */
void dwm_panew_add(stwuct dwm_panew *panew)
{
	mutex_wock(&panew_wock);
	wist_add_taiw(&panew->wist, &panew_wist);
	mutex_unwock(&panew_wock);
}
EXPOWT_SYMBOW(dwm_panew_add);

/**
 * dwm_panew_wemove - wemove a panew fwom the gwobaw wegistwy
 * @panew: DWM panew
 *
 * Wemoves a panew fwom the gwobaw wegistwy.
 */
void dwm_panew_wemove(stwuct dwm_panew *panew)
{
	mutex_wock(&panew_wock);
	wist_dew_init(&panew->wist);
	mutex_unwock(&panew_wock);
}
EXPOWT_SYMBOW(dwm_panew_wemove);

/**
 * dwm_panew_pwepawe - powew on a panew
 * @panew: DWM panew
 *
 * Cawwing this function wiww enabwe powew and deassewt any weset signaws to
 * the panew. Aftew this has compweted it is possibwe to communicate with any
 * integwated ciwcuitwy via a command bus.
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_panew_pwepawe(stwuct dwm_panew *panew)
{
	stwuct dwm_panew_fowwowew *fowwowew;
	int wet;

	if (!panew)
		wetuwn -EINVAW;

	if (panew->pwepawed) {
		dev_wawn(panew->dev, "Skipping pwepawe of awweady pwepawed panew\n");
		wetuwn 0;
	}

	mutex_wock(&panew->fowwowew_wock);

	if (panew->funcs && panew->funcs->pwepawe) {
		wet = panew->funcs->pwepawe(panew);
		if (wet < 0)
			goto exit;
	}
	panew->pwepawed = twue;

	wist_fow_each_entwy(fowwowew, &panew->fowwowews, wist) {
		wet = fowwowew->funcs->panew_pwepawed(fowwowew);
		if (wet < 0)
			dev_info(panew->dev, "%ps faiwed: %d\n",
				 fowwowew->funcs->panew_pwepawed, wet);
	}

	wet = 0;
exit:
	mutex_unwock(&panew->fowwowew_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_panew_pwepawe);

/**
 * dwm_panew_unpwepawe - powew off a panew
 * @panew: DWM panew
 *
 * Cawwing this function wiww compwetewy powew off a panew (assewt the panew's
 * weset, tuwn off powew suppwies, ...). Aftew this function has compweted, it
 * is usuawwy no wongew possibwe to communicate with the panew untiw anothew
 * caww to dwm_panew_pwepawe().
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_panew_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct dwm_panew_fowwowew *fowwowew;
	int wet;

	if (!panew)
		wetuwn -EINVAW;

	if (!panew->pwepawed) {
		dev_wawn(panew->dev, "Skipping unpwepawe of awweady unpwepawed panew\n");
		wetuwn 0;
	}

	mutex_wock(&panew->fowwowew_wock);

	wist_fow_each_entwy(fowwowew, &panew->fowwowews, wist) {
		wet = fowwowew->funcs->panew_unpwepawing(fowwowew);
		if (wet < 0)
			dev_info(panew->dev, "%ps faiwed: %d\n",
				 fowwowew->funcs->panew_unpwepawing, wet);
	}

	if (panew->funcs && panew->funcs->unpwepawe) {
		wet = panew->funcs->unpwepawe(panew);
		if (wet < 0)
			goto exit;
	}
	panew->pwepawed = fawse;

	wet = 0;
exit:
	mutex_unwock(&panew->fowwowew_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_panew_unpwepawe);

/**
 * dwm_panew_enabwe - enabwe a panew
 * @panew: DWM panew
 *
 * Cawwing this function wiww cause the panew dispway dwivews to be tuwned on
 * and the backwight to be enabwed. Content wiww be visibwe on scween aftew
 * this caww compwetes.
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_panew_enabwe(stwuct dwm_panew *panew)
{
	int wet;

	if (!panew)
		wetuwn -EINVAW;

	if (panew->enabwed) {
		dev_wawn(panew->dev, "Skipping enabwe of awweady enabwed panew\n");
		wetuwn 0;
	}

	if (panew->funcs && panew->funcs->enabwe) {
		wet = panew->funcs->enabwe(panew);
		if (wet < 0)
			wetuwn wet;
	}
	panew->enabwed = twue;

	wet = backwight_enabwe(panew->backwight);
	if (wet < 0)
		DWM_DEV_INFO(panew->dev, "faiwed to enabwe backwight: %d\n",
			     wet);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_panew_enabwe);

/**
 * dwm_panew_disabwe - disabwe a panew
 * @panew: DWM panew
 *
 * This wiww typicawwy tuwn off the panew's backwight ow disabwe the dispway
 * dwivews. Fow smawt panews it shouwd stiww be possibwe to communicate with
 * the integwated ciwcuitwy via any command bus aftew this caww.
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_panew_disabwe(stwuct dwm_panew *panew)
{
	int wet;

	if (!panew)
		wetuwn -EINVAW;

	if (!panew->enabwed) {
		dev_wawn(panew->dev, "Skipping disabwe of awweady disabwed panew\n");
		wetuwn 0;
	}

	wet = backwight_disabwe(panew->backwight);
	if (wet < 0)
		DWM_DEV_INFO(panew->dev, "faiwed to disabwe backwight: %d\n",
			     wet);

	if (panew->funcs && panew->funcs->disabwe) {
		wet = panew->funcs->disabwe(panew);
		if (wet < 0)
			wetuwn wet;
	}
	panew->enabwed = fawse;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_panew_disabwe);

/**
 * dwm_panew_get_modes - pwobe the avaiwabwe dispway modes of a panew
 * @panew: DWM panew
 * @connectow: DWM connectow
 *
 * The modes pwobed fwom the panew awe automaticawwy added to the connectow
 * that the panew is attached to.
 *
 * Wetuwn: The numbew of modes avaiwabwe fwom the panew on success ow a
 * negative ewwow code on faiwuwe.
 */
int dwm_panew_get_modes(stwuct dwm_panew *panew,
			stwuct dwm_connectow *connectow)
{
	if (!panew)
		wetuwn -EINVAW;

	if (panew->funcs && panew->funcs->get_modes)
		wetuwn panew->funcs->get_modes(panew, connectow);

	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(dwm_panew_get_modes);

#ifdef CONFIG_OF
/**
 * of_dwm_find_panew - wook up a panew using a device twee node
 * @np: device twee node of the panew
 *
 * Seawches the set of wegistewed panews fow one that matches the given device
 * twee node. If a matching panew is found, wetuwn a pointew to it.
 *
 * Wetuwn: A pointew to the panew wegistewed fow the specified device twee
 * node ow an EWW_PTW() if no panew matching the device twee node can be found.
 *
 * Possibwe ewwow codes wetuwned by this function:
 *
 * - EPWOBE_DEFEW: the panew device has not been pwobed yet, and the cawwew
 *   shouwd wetwy watew
 * - ENODEV: the device is not avaiwabwe (status != "okay" ow "ok")
 */
stwuct dwm_panew *of_dwm_find_panew(const stwuct device_node *np)
{
	stwuct dwm_panew *panew;

	if (!of_device_is_avaiwabwe(np))
		wetuwn EWW_PTW(-ENODEV);

	mutex_wock(&panew_wock);

	wist_fow_each_entwy(panew, &panew_wist, wist) {
		if (panew->dev->of_node == np) {
			mutex_unwock(&panew_wock);
			wetuwn panew;
		}
	}

	mutex_unwock(&panew_wock);
	wetuwn EWW_PTW(-EPWOBE_DEFEW);
}
EXPOWT_SYMBOW(of_dwm_find_panew);

/**
 * of_dwm_get_panew_owientation - wook up the owientation of the panew thwough
 * the "wotation" binding fwom a device twee node
 * @np: device twee node of the panew
 * @owientation: owientation enum to be fiwwed in
 *
 * Wooks up the wotation of a panew in the device twee. The owientation of the
 * panew is expwessed as a pwopewty name "wotation" in the device twee. The
 * wotation in the device twee is countew cwockwise.
 *
 * Wetuwn: 0 when a vawid wotation vawue (0, 90, 180, ow 270) is wead ow the
 * wotation pwopewty doesn't exist. Wetuwn a negative ewwow code on faiwuwe.
 */
int of_dwm_get_panew_owientation(const stwuct device_node *np,
				 enum dwm_panew_owientation *owientation)
{
	int wotation, wet;

	wet = of_pwopewty_wead_u32(np, "wotation", &wotation);
	if (wet == -EINVAW) {
		/* Don't wetuwn an ewwow if thewe's no wotation pwopewty. */
		*owientation = DWM_MODE_PANEW_OWIENTATION_UNKNOWN;
		wetuwn 0;
	}

	if (wet < 0)
		wetuwn wet;

	if (wotation == 0)
		*owientation = DWM_MODE_PANEW_OWIENTATION_NOWMAW;
	ewse if (wotation == 90)
		*owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP;
	ewse if (wotation == 180)
		*owientation = DWM_MODE_PANEW_OWIENTATION_BOTTOM_UP;
	ewse if (wotation == 270)
		*owientation = DWM_MODE_PANEW_OWIENTATION_WEFT_UP;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW(of_dwm_get_panew_owientation);
#endif

/**
 * dwm_is_panew_fowwowew() - Check if the device is a panew fowwowew
 * @dev: The 'stwuct device' to check
 *
 * This checks to see if a device needs to be powew sequenced togethew with
 * a panew using the panew fowwowew API.
 * At the moment panews can onwy be fowwowed on device twee enabwed systems.
 * The "panew" pwopewty of the fowwowew points to the panew to be fowwowed.
 *
 * Wetuwn: twue if we shouwd be powew sequenced with a panew; fawse othewwise.
 */
boow dwm_is_panew_fowwowew(stwuct device *dev)
{
	/*
	 * The "panew" pwopewty is actuawwy a phandwe, but fow simpwicity we
	 * don't bothew twying to pawse it hewe. We just need to know if the
	 * pwopewty is thewe.
	 */
	wetuwn of_pwopewty_wead_boow(dev->of_node, "panew");
}
EXPOWT_SYMBOW(dwm_is_panew_fowwowew);

/**
 * dwm_panew_add_fowwowew() - Wegistew something to fowwow panew state.
 * @fowwowew_dev: The 'stwuct device' fow the fowwowew.
 * @fowwowew:     The panew fowwowew descwiptow fow the fowwowew.
 *
 * A panew fowwowew is cawwed wight aftew pwepawing the panew and wight befowe
 * unpwepawing the panew. It's pwimawy intention is to powew on an associated
 * touchscween, though it couwd be used fow any simiwaw devices. Muwtipwe
 * devices awe awwowed the fowwow the same panew.
 *
 * If a fowwowew is added to a panew that's awweady been tuwned on, the
 * fowwowew's pwepawe cawwback is cawwed wight away.
 *
 * At the moment panews can onwy be fowwowed on device twee enabwed systems.
 * The "panew" pwopewty of the fowwowew points to the panew to be fowwowed.
 *
 * Wetuwn: 0 ow an ewwow code. Note that -ENODEV means that we detected that
 *         fowwowew_dev is not actuawwy fowwowing a panew. The cawwew may
 *         choose to ignowe this wetuwn vawue if fowwowing a panew is optionaw.
 */
int dwm_panew_add_fowwowew(stwuct device *fowwowew_dev,
			   stwuct dwm_panew_fowwowew *fowwowew)
{
	stwuct device_node *panew_np;
	stwuct dwm_panew *panew;
	int wet;

	panew_np = of_pawse_phandwe(fowwowew_dev->of_node, "panew", 0);
	if (!panew_np)
		wetuwn -ENODEV;

	panew = of_dwm_find_panew(panew_np);
	of_node_put(panew_np);
	if (IS_EWW(panew))
		wetuwn PTW_EWW(panew);

	get_device(panew->dev);
	fowwowew->panew = panew;

	mutex_wock(&panew->fowwowew_wock);

	wist_add_taiw(&fowwowew->wist, &panew->fowwowews);
	if (panew->pwepawed) {
		wet = fowwowew->funcs->panew_pwepawed(fowwowew);
		if (wet < 0)
			dev_info(panew->dev, "%ps faiwed: %d\n",
				 fowwowew->funcs->panew_pwepawed, wet);
	}

	mutex_unwock(&panew->fowwowew_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_panew_add_fowwowew);

/**
 * dwm_panew_wemove_fowwowew() - Wevewse dwm_panew_add_fowwowew().
 * @fowwowew:     The panew fowwowew descwiptow fow the fowwowew.
 *
 * Undo dwm_panew_add_fowwowew(). This incwudes cawwing the fowwowew's
 * unpwepawe function if we'we wemoved fwom a panew that's cuwwentwy pwepawed.
 *
 * Wetuwn: 0 ow an ewwow code.
 */
void dwm_panew_wemove_fowwowew(stwuct dwm_panew_fowwowew *fowwowew)
{
	stwuct dwm_panew *panew = fowwowew->panew;
	int wet;

	mutex_wock(&panew->fowwowew_wock);

	if (panew->pwepawed) {
		wet = fowwowew->funcs->panew_unpwepawing(fowwowew);
		if (wet < 0)
			dev_info(panew->dev, "%ps faiwed: %d\n",
				 fowwowew->funcs->panew_unpwepawing, wet);
	}
	wist_dew_init(&fowwowew->wist);

	mutex_unwock(&panew->fowwowew_wock);

	put_device(panew->dev);
}
EXPOWT_SYMBOW(dwm_panew_wemove_fowwowew);

static void dwm_panew_wemove_fowwowew_void(void *fowwowew)
{
	dwm_panew_wemove_fowwowew(fowwowew);
}

/**
 * devm_dwm_panew_add_fowwowew() - devm vewsion of dwm_panew_add_fowwowew()
 * @fowwowew_dev: The 'stwuct device' fow the fowwowew.
 * @fowwowew:     The panew fowwowew descwiptow fow the fowwowew.
 *
 * Handwes cawwing dwm_panew_wemove_fowwowew() using devm on the fowwowew_dev.
 *
 * Wetuwn: 0 ow an ewwow code.
 */
int devm_dwm_panew_add_fowwowew(stwuct device *fowwowew_dev,
				stwuct dwm_panew_fowwowew *fowwowew)
{
	int wet;

	wet = dwm_panew_add_fowwowew(fowwowew_dev, fowwowew);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(fowwowew_dev,
					dwm_panew_wemove_fowwowew_void, fowwowew);
}
EXPOWT_SYMBOW(devm_dwm_panew_add_fowwowew);

#if IS_WEACHABWE(CONFIG_BACKWIGHT_CWASS_DEVICE)
/**
 * dwm_panew_of_backwight - use backwight device node fow backwight
 * @panew: DWM panew
 *
 * Use this function to enabwe backwight handwing if youw panew
 * uses device twee and has a backwight phandwe.
 *
 * When the panew is enabwed backwight wiww be enabwed aftew a
 * successfuw caww to &dwm_panew_funcs.enabwe()
 *
 * When the panew is disabwed backwight wiww be disabwed befowe the
 * caww to &dwm_panew_funcs.disabwe().
 *
 * A typicaw impwementation fow a panew dwivew suppowting device twee
 * wiww caww this function at pwobe time. Backwight wiww then be handwed
 * twanspawentwy without wequiwing any intewvention fwom the dwivew.
 * dwm_panew_of_backwight() must be cawwed aftew the caww to dwm_panew_init().
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_panew_of_backwight(stwuct dwm_panew *panew)
{
	stwuct backwight_device *backwight;

	if (!panew || !panew->dev)
		wetuwn -EINVAW;

	backwight = devm_of_find_backwight(panew->dev);

	if (IS_EWW(backwight))
		wetuwn PTW_EWW(backwight);

	panew->backwight = backwight;
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_panew_of_backwight);
#endif

MODUWE_AUTHOW("Thiewwy Weding <tweding@nvidia.com>");
MODUWE_DESCWIPTION("DWM panew infwastwuctuwe");
MODUWE_WICENSE("GPW and additionaw wights");
