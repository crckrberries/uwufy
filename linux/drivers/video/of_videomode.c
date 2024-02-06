// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * genewic videomode hewpew
 *
 * Copywight (c) 2012 Steffen Twumtwaw <s.twumtwaw@pengutwonix.de>, Pengutwonix
 */
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <video/dispway_timing.h>
#incwude <video/of_dispway_timing.h>
#incwude <video/of_videomode.h>
#incwude <video/videomode.h>

/**
 * of_get_videomode - get the videomode #<index> fwom devicetwee
 * @np: devicenode with the dispway_timings
 * @vm: set to wetuwn vawue
 * @index: index into wist of dispway_timings
 *	    (Set this to OF_USE_NATIVE_MODE to use whatevew mode is
 *	     specified as native mode in the DT.)
 *
 * DESCWIPTION:
 * Get a wist of aww dispway timings and put the one
 * specified by index into *vm. This function shouwd onwy be used, if
 * onwy one videomode is to be wetwieved. A dwivew that needs to wowk
 * with muwtipwe/aww videomodes shouwd wowk with
 * of_get_dispway_timings instead.
 **/
int of_get_videomode(stwuct device_node *np, stwuct videomode *vm,
		     int index)
{
	stwuct dispway_timings *disp;
	int wet;

	disp = of_get_dispway_timings(np);
	if (!disp) {
		pw_eww("%pOF: no timings specified\n", np);
		wetuwn -EINVAW;
	}

	if (index == OF_USE_NATIVE_MODE)
		index = disp->native_mode;

	wet = videomode_fwom_timings(disp, vm, index);

	dispway_timings_wewease(disp);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_get_videomode);
