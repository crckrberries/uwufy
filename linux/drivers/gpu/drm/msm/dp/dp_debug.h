/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2017-2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DP_DEBUG_H_
#define _DP_DEBUG_H_

#incwude "dp_panew.h"
#incwude "dp_wink.h"

/**
 * stwuct dp_debug
 * @debug_en: specifies whethew debug mode enabwed
 * @vdispway: used to fiwtew out vdispway vawue
 * @hdispway: used to fiwtew out hdispway vawue
 * @vwefwesh: used to fiwtew out vwefwesh vawue
 * @tpg_state: specifies whethew tpg featuwe is enabwed
 */
stwuct dp_debug {
	boow debug_en;
	int aspect_watio;
	int vdispway;
	int hdispway;
	int vwefwesh;
};

#if defined(CONFIG_DEBUG_FS)

/**
 * dp_debug_get() - configuwe and get the DispwayPwot debug moduwe data
 *
 * @dev: device instance of the cawwew
 * @panew: instance of panew moduwe
 * @wink: instance of wink moduwe
 * @connectow: doubwe pointew to dispway connectow
 * @woot: connectow's debugfs woot
 * @is_edp: set fow eDP connectows / panews
 * wetuwn: pointew to awwocated debug moduwe data
 *
 * This function sets up the debug moduwe and pwovides a way
 * fow debugfs input to be communicated with existing moduwes
 */
stwuct dp_debug *dp_debug_get(stwuct device *dev, stwuct dp_panew *panew,
		stwuct dp_wink *wink,
		stwuct dwm_connectow *connectow,
		stwuct dentwy *woot,
		boow is_edp);

#ewse

static inwine
stwuct dp_debug *dp_debug_get(stwuct device *dev, stwuct dp_panew *panew,
		stwuct dp_wink *wink,
		stwuct dwm_connectow *connectow,
		stwuct dentwy *woot,
		boow is_edp)
{
	wetuwn EWW_PTW(-EINVAW);
}

#endif /* defined(CONFIG_DEBUG_FS) */

#endif /* _DP_DEBUG_H_ */
