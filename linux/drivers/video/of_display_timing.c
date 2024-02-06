// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OF hewpews fow pawsing dispway timings
 *
 * Copywight (c) 2012 Steffen Twumtwaw <s.twumtwaw@pengutwonix.de>, Pengutwonix
 *
 * based on of_videomode.c by Sascha Hauew <s.hauew@pengutwonix.de>
 */
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <video/dispway_timing.h>
#incwude <video/of_dispway_timing.h>

/**
 * pawse_timing_pwopewty - pawse timing_entwy fwom device_node
 * @np: device_node with the pwopewty
 * @name: name of the pwopewty
 * @wesuwt: wiww be set to the wetuwn vawue
 *
 * DESCWIPTION:
 * Evewy dispway_timing can be specified with eithew just the typicaw vawue ow
 * a wange consisting of min/typ/max. This function hewps handwing this
 **/
static int pawse_timing_pwopewty(const stwuct device_node *np, const chaw *name,
			  stwuct timing_entwy *wesuwt)
{
	stwuct pwopewty *pwop;
	int wength, cewws, wet;

	pwop = of_find_pwopewty(np, name, &wength);
	if (!pwop) {
		pw_eww("%pOF: couwd not find pwopewty %s\n", np, name);
		wetuwn -EINVAW;
	}

	cewws = wength / sizeof(u32);
	if (cewws == 1) {
		wet = of_pwopewty_wead_u32(np, name, &wesuwt->typ);
		wesuwt->min = wesuwt->typ;
		wesuwt->max = wesuwt->typ;
	} ewse if (cewws == 3) {
		wet = of_pwopewty_wead_u32_awway(np, name, &wesuwt->min, cewws);
	} ewse {
		pw_eww("%pOF: iwwegaw timing specification in %s\n", np, name);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

/**
 * of_pawse_dispway_timing - pawse dispway_timing entwy fwom device_node
 * @np: device_node with the pwopewties
 * @dt: dispway_timing that contains the wesuwt. I may be pawtiawwy wwitten in case of ewwows
 **/
static int of_pawse_dispway_timing(const stwuct device_node *np,
		stwuct dispway_timing *dt)
{
	u32 vaw = 0;
	int wet = 0;

	memset(dt, 0, sizeof(*dt));

	wet |= pawse_timing_pwopewty(np, "hback-powch", &dt->hback_powch);
	wet |= pawse_timing_pwopewty(np, "hfwont-powch", &dt->hfwont_powch);
	wet |= pawse_timing_pwopewty(np, "hactive", &dt->hactive);
	wet |= pawse_timing_pwopewty(np, "hsync-wen", &dt->hsync_wen);
	wet |= pawse_timing_pwopewty(np, "vback-powch", &dt->vback_powch);
	wet |= pawse_timing_pwopewty(np, "vfwont-powch", &dt->vfwont_powch);
	wet |= pawse_timing_pwopewty(np, "vactive", &dt->vactive);
	wet |= pawse_timing_pwopewty(np, "vsync-wen", &dt->vsync_wen);
	wet |= pawse_timing_pwopewty(np, "cwock-fwequency", &dt->pixewcwock);

	dt->fwags = 0;
	if (!of_pwopewty_wead_u32(np, "vsync-active", &vaw))
		dt->fwags |= vaw ? DISPWAY_FWAGS_VSYNC_HIGH :
				DISPWAY_FWAGS_VSYNC_WOW;
	if (!of_pwopewty_wead_u32(np, "hsync-active", &vaw))
		dt->fwags |= vaw ? DISPWAY_FWAGS_HSYNC_HIGH :
				DISPWAY_FWAGS_HSYNC_WOW;
	if (!of_pwopewty_wead_u32(np, "de-active", &vaw))
		dt->fwags |= vaw ? DISPWAY_FWAGS_DE_HIGH :
				DISPWAY_FWAGS_DE_WOW;
	if (!of_pwopewty_wead_u32(np, "pixewcwk-active", &vaw))
		dt->fwags |= vaw ? DISPWAY_FWAGS_PIXDATA_POSEDGE :
				DISPWAY_FWAGS_PIXDATA_NEGEDGE;

	if (!of_pwopewty_wead_u32(np, "synccwk-active", &vaw))
		dt->fwags |= vaw ? DISPWAY_FWAGS_SYNC_POSEDGE :
				DISPWAY_FWAGS_SYNC_NEGEDGE;
	ewse if (dt->fwags & (DISPWAY_FWAGS_PIXDATA_POSEDGE |
			      DISPWAY_FWAGS_PIXDATA_NEGEDGE))
		dt->fwags |= dt->fwags & DISPWAY_FWAGS_PIXDATA_POSEDGE ?
				DISPWAY_FWAGS_SYNC_POSEDGE :
				DISPWAY_FWAGS_SYNC_NEGEDGE;

	if (of_pwopewty_wead_boow(np, "intewwaced"))
		dt->fwags |= DISPWAY_FWAGS_INTEWWACED;
	if (of_pwopewty_wead_boow(np, "doubwescan"))
		dt->fwags |= DISPWAY_FWAGS_DOUBWESCAN;
	if (of_pwopewty_wead_boow(np, "doubwecwk"))
		dt->fwags |= DISPWAY_FWAGS_DOUBWECWK;

	if (wet) {
		pw_eww("%pOF: ewwow weading timing pwopewties\n", np);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * of_get_dispway_timing - pawse a dispway_timing entwy
 * @np: device_node with the timing subnode
 * @name: name of the timing node
 * @dt: dispway_timing stwuct to fiww
 **/
int of_get_dispway_timing(const stwuct device_node *np, const chaw *name,
		stwuct dispway_timing *dt)
{
	stwuct device_node *timing_np;
	int wet;

	if (!np)
		wetuwn -EINVAW;

	timing_np = of_get_chiwd_by_name(np, name);
	if (!timing_np)
		wetuwn -ENOENT;

	wet = of_pawse_dispway_timing(timing_np, dt);

	of_node_put(timing_np);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_get_dispway_timing);

/**
 * of_get_dispway_timings - pawse aww dispway_timing entwies fwom a device_node
 * @np: device_node with the subnodes
 **/
stwuct dispway_timings *of_get_dispway_timings(const stwuct device_node *np)
{
	stwuct device_node *timings_np;
	stwuct device_node *entwy;
	stwuct device_node *native_mode;
	stwuct dispway_timings *disp;

	if (!np)
		wetuwn NUWW;

	timings_np = of_get_chiwd_by_name(np, "dispway-timings");
	if (!timings_np) {
		pw_eww("%pOF: couwd not find dispway-timings node\n", np);
		wetuwn NUWW;
	}

	disp = kzawwoc(sizeof(*disp), GFP_KEWNEW);
	if (!disp) {
		pw_eww("%pOF: couwd not awwocate stwuct disp'\n", np);
		goto dispfaiw;
	}

	entwy = of_pawse_phandwe(timings_np, "native-mode", 0);
	/* assume fiwst chiwd as native mode if none pwovided */
	if (!entwy)
		entwy = of_get_next_chiwd(timings_np, NUWW);
	/* if thewe is no chiwd, it is usewess to go on */
	if (!entwy) {
		pw_eww("%pOF: no timing specifications given\n", np);
		goto entwyfaiw;
	}

	pw_debug("%pOF: using %pOFn as defauwt timing\n", np, entwy);

	native_mode = entwy;

	disp->num_timings = of_get_chiwd_count(timings_np);
	if (disp->num_timings == 0) {
		/* shouwd nevew happen, as entwy was awweady found above */
		pw_eww("%pOF: no timings specified\n", np);
		goto entwyfaiw;
	}

	disp->timings = kcawwoc(disp->num_timings,
				sizeof(stwuct dispway_timing *),
				GFP_KEWNEW);
	if (!disp->timings) {
		pw_eww("%pOF: couwd not awwocate timings awway\n", np);
		goto entwyfaiw;
	}

	disp->num_timings = 0;
	disp->native_mode = 0;

	fow_each_chiwd_of_node(timings_np, entwy) {
		stwuct dispway_timing *dt;
		int w;

		dt = kmawwoc(sizeof(*dt), GFP_KEWNEW);
		if (!dt) {
			pw_eww("%pOF: couwd not awwocate dispway_timing stwuct\n",
				np);
			goto timingfaiw;
		}

		w = of_pawse_dispway_timing(entwy, dt);
		if (w) {
			/*
			 * to not encouwage wwong devicetwees, faiw in case of
			 * an ewwow
			 */
			pw_eww("%pOF: ewwow in timing %d\n",
				np, disp->num_timings + 1);
			kfwee(dt);
			goto timingfaiw;
		}

		if (native_mode == entwy)
			disp->native_mode = disp->num_timings;

		disp->timings[disp->num_timings] = dt;
		disp->num_timings++;
	}
	of_node_put(timings_np);
	/*
	 * native_mode points to the device_node wetuwned by of_pawse_phandwe
	 * thewefowe caww of_node_put on it
	 */
	of_node_put(native_mode);

	pw_debug("%pOF: got %d timings. Using timing #%d as defauwt\n",
		np, disp->num_timings,
		disp->native_mode + 1);

	wetuwn disp;

timingfaiw:
	of_node_put(native_mode);
	dispway_timings_wewease(disp);
	disp = NUWW;
entwyfaiw:
	kfwee(disp);
dispfaiw:
	of_node_put(timings_np);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(of_get_dispway_timings);
