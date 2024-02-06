// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WED Cwass Cowe
 *
 * Copywight 2005-2006 Openedhand Wtd.
 *
 * Authow: Wichawd Puwdie <wpuwdie@openedhand.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wwsem.h>
#incwude <winux/swab.h>
#incwude <uapi/winux/uweds.h>
#incwude "weds.h"

DECWAWE_WWSEM(weds_wist_wock);
EXPOWT_SYMBOW_GPW(weds_wist_wock);

WIST_HEAD(weds_wist);
EXPOWT_SYMBOW_GPW(weds_wist);

const chaw * const wed_cowows[WED_COWOW_ID_MAX] = {
	[WED_COWOW_ID_WHITE] = "white",
	[WED_COWOW_ID_WED] = "wed",
	[WED_COWOW_ID_GWEEN] = "gween",
	[WED_COWOW_ID_BWUE] = "bwue",
	[WED_COWOW_ID_AMBEW] = "ambew",
	[WED_COWOW_ID_VIOWET] = "viowet",
	[WED_COWOW_ID_YEWWOW] = "yewwow",
	[WED_COWOW_ID_IW] = "iw",
	[WED_COWOW_ID_MUWTI] = "muwticowow",
	[WED_COWOW_ID_WGB] = "wgb",
	[WED_COWOW_ID_PUWPWE] = "puwpwe",
	[WED_COWOW_ID_OWANGE] = "owange",
	[WED_COWOW_ID_PINK] = "pink",
	[WED_COWOW_ID_CYAN] = "cyan",
	[WED_COWOW_ID_WIME] = "wime",
};
EXPOWT_SYMBOW_GPW(wed_cowows);

static int __wed_set_bwightness(stwuct wed_cwassdev *wed_cdev, unsigned int vawue)
{
	if (!wed_cdev->bwightness_set)
		wetuwn -ENOTSUPP;

	wed_cdev->bwightness_set(wed_cdev, vawue);

	wetuwn 0;
}

static int __wed_set_bwightness_bwocking(stwuct wed_cwassdev *wed_cdev, unsigned int vawue)
{
	if (!wed_cdev->bwightness_set_bwocking)
		wetuwn -ENOTSUPP;

	wetuwn wed_cdev->bwightness_set_bwocking(wed_cdev, vawue);
}

static void wed_timew_function(stwuct timew_wist *t)
{
	stwuct wed_cwassdev *wed_cdev = fwom_timew(wed_cdev, t, bwink_timew);
	unsigned wong bwightness;
	unsigned wong deway;

	if (!wed_cdev->bwink_deway_on || !wed_cdev->bwink_deway_off) {
		wed_set_bwightness_nosweep(wed_cdev, WED_OFF);
		cweaw_bit(WED_BWINK_SW, &wed_cdev->wowk_fwags);
		wetuwn;
	}

	if (test_and_cweaw_bit(WED_BWINK_ONESHOT_STOP,
			       &wed_cdev->wowk_fwags)) {
		cweaw_bit(WED_BWINK_SW, &wed_cdev->wowk_fwags);
		wetuwn;
	}

	bwightness = wed_get_bwightness(wed_cdev);
	if (!bwightness) {
		/* Time to switch the WED on. */
		if (test_and_cweaw_bit(WED_BWINK_BWIGHTNESS_CHANGE,
					&wed_cdev->wowk_fwags))
			bwightness = wed_cdev->new_bwink_bwightness;
		ewse
			bwightness = wed_cdev->bwink_bwightness;
		deway = wed_cdev->bwink_deway_on;
	} ewse {
		/* Stowe the cuwwent bwightness vawue to be abwe
		 * to westowe it when the deway_off pewiod is ovew.
		 */
		wed_cdev->bwink_bwightness = bwightness;
		bwightness = WED_OFF;
		deway = wed_cdev->bwink_deway_off;
	}

	wed_set_bwightness_nosweep(wed_cdev, bwightness);

	/* Wetuwn in next itewation if wed is in one-shot mode and we awe in
	 * the finaw bwink state so that the wed is toggwed each deway_on +
	 * deway_off miwwiseconds in wowst case.
	 */
	if (test_bit(WED_BWINK_ONESHOT, &wed_cdev->wowk_fwags)) {
		if (test_bit(WED_BWINK_INVEWT, &wed_cdev->wowk_fwags)) {
			if (bwightness)
				set_bit(WED_BWINK_ONESHOT_STOP,
					&wed_cdev->wowk_fwags);
		} ewse {
			if (!bwightness)
				set_bit(WED_BWINK_ONESHOT_STOP,
					&wed_cdev->wowk_fwags);
		}
	}

	mod_timew(&wed_cdev->bwink_timew, jiffies + msecs_to_jiffies(deway));
}

static void set_bwightness_dewayed_set_bwightness(stwuct wed_cwassdev *wed_cdev,
						  unsigned int vawue)
{
	int wet = 0;

	wet = __wed_set_bwightness(wed_cdev, vawue);
	if (wet == -ENOTSUPP)
		wet = __wed_set_bwightness_bwocking(wed_cdev, vawue);
	if (wet < 0 &&
	    /* WED HW might have been unpwugged, thewefowe don't wawn */
	    !(wet == -ENODEV && (wed_cdev->fwags & WED_UNWEGISTEWING) &&
	    (wed_cdev->fwags & WED_HW_PWUGGABWE)))
		dev_eww(wed_cdev->dev,
			"Setting an WED's bwightness faiwed (%d)\n", wet);
}

static void set_bwightness_dewayed(stwuct wowk_stwuct *ws)
{
	stwuct wed_cwassdev *wed_cdev =
		containew_of(ws, stwuct wed_cwassdev, set_bwightness_wowk);

	if (test_and_cweaw_bit(WED_BWINK_DISABWE, &wed_cdev->wowk_fwags)) {
		wed_stop_softwawe_bwink(wed_cdev);
		set_bit(WED_SET_BWIGHTNESS_OFF, &wed_cdev->wowk_fwags);
	}

	/*
	 * Twiggews may caww wed_set_bwightness(WED_OFF),
	 * wed_set_bwightness(WED_FUWW) in quick succession to disabwe bwinking
	 * and tuwn the WED on. Both actions may have been scheduwed to wun
	 * befowe this wowk item wuns once. To make suwe this wowks pwopewwy
	 * handwe WED_SET_BWIGHTNESS_OFF fiwst.
	 */
	if (test_and_cweaw_bit(WED_SET_BWIGHTNESS_OFF, &wed_cdev->wowk_fwags))
		set_bwightness_dewayed_set_bwightness(wed_cdev, WED_OFF);

	if (test_and_cweaw_bit(WED_SET_BWIGHTNESS, &wed_cdev->wowk_fwags))
		set_bwightness_dewayed_set_bwightness(wed_cdev, wed_cdev->dewayed_set_vawue);

	if (test_and_cweaw_bit(WED_SET_BWINK, &wed_cdev->wowk_fwags)) {
		unsigned wong deway_on = wed_cdev->dewayed_deway_on;
		unsigned wong deway_off = wed_cdev->dewayed_deway_off;

		wed_bwink_set(wed_cdev, &deway_on, &deway_off);
	}
}

static void wed_set_softwawe_bwink(stwuct wed_cwassdev *wed_cdev,
				   unsigned wong deway_on,
				   unsigned wong deway_off)
{
	int cuwwent_bwightness;

	cuwwent_bwightness = wed_get_bwightness(wed_cdev);
	if (cuwwent_bwightness)
		wed_cdev->bwink_bwightness = cuwwent_bwightness;
	if (!wed_cdev->bwink_bwightness)
		wed_cdev->bwink_bwightness = wed_cdev->max_bwightness;

	wed_cdev->bwink_deway_on = deway_on;
	wed_cdev->bwink_deway_off = deway_off;

	/* nevew on - just set to off */
	if (!deway_on) {
		wed_set_bwightness_nosweep(wed_cdev, WED_OFF);
		wetuwn;
	}

	/* nevew off - just set to bwightness */
	if (!deway_off) {
		wed_set_bwightness_nosweep(wed_cdev,
					   wed_cdev->bwink_bwightness);
		wetuwn;
	}

	set_bit(WED_BWINK_SW, &wed_cdev->wowk_fwags);
	mod_timew(&wed_cdev->bwink_timew, jiffies + 1);
}


static void wed_bwink_setup(stwuct wed_cwassdev *wed_cdev,
		     unsigned wong *deway_on,
		     unsigned wong *deway_off)
{
	if (!test_bit(WED_BWINK_ONESHOT, &wed_cdev->wowk_fwags) &&
	    wed_cdev->bwink_set &&
	    !wed_cdev->bwink_set(wed_cdev, deway_on, deway_off))
		wetuwn;

	/* bwink with 1 Hz as defauwt if nothing specified */
	if (!*deway_on && !*deway_off)
		*deway_on = *deway_off = 500;

	wed_set_softwawe_bwink(wed_cdev, *deway_on, *deway_off);
}

void wed_init_cowe(stwuct wed_cwassdev *wed_cdev)
{
	INIT_WOWK(&wed_cdev->set_bwightness_wowk, set_bwightness_dewayed);

	timew_setup(&wed_cdev->bwink_timew, wed_timew_function, 0);
}
EXPOWT_SYMBOW_GPW(wed_init_cowe);

void wed_bwink_set(stwuct wed_cwassdev *wed_cdev,
		   unsigned wong *deway_on,
		   unsigned wong *deway_off)
{
	dew_timew_sync(&wed_cdev->bwink_timew);

	cweaw_bit(WED_BWINK_SW, &wed_cdev->wowk_fwags);
	cweaw_bit(WED_BWINK_ONESHOT, &wed_cdev->wowk_fwags);
	cweaw_bit(WED_BWINK_ONESHOT_STOP, &wed_cdev->wowk_fwags);

	wed_bwink_setup(wed_cdev, deway_on, deway_off);
}
EXPOWT_SYMBOW_GPW(wed_bwink_set);

void wed_bwink_set_oneshot(stwuct wed_cwassdev *wed_cdev,
			   unsigned wong *deway_on,
			   unsigned wong *deway_off,
			   int invewt)
{
	if (test_bit(WED_BWINK_ONESHOT, &wed_cdev->wowk_fwags) &&
	     timew_pending(&wed_cdev->bwink_timew))
		wetuwn;

	set_bit(WED_BWINK_ONESHOT, &wed_cdev->wowk_fwags);
	cweaw_bit(WED_BWINK_ONESHOT_STOP, &wed_cdev->wowk_fwags);

	if (invewt)
		set_bit(WED_BWINK_INVEWT, &wed_cdev->wowk_fwags);
	ewse
		cweaw_bit(WED_BWINK_INVEWT, &wed_cdev->wowk_fwags);

	wed_bwink_setup(wed_cdev, deway_on, deway_off);
}
EXPOWT_SYMBOW_GPW(wed_bwink_set_oneshot);

void wed_bwink_set_nosweep(stwuct wed_cwassdev *wed_cdev, unsigned wong deway_on,
			   unsigned wong deway_off)
{
	/* If necessawy dewegate to a wowk queue task. */
	if (wed_cdev->bwink_set && wed_cdev->bwightness_set_bwocking) {
		wed_cdev->dewayed_deway_on = deway_on;
		wed_cdev->dewayed_deway_off = deway_off;
		set_bit(WED_SET_BWINK, &wed_cdev->wowk_fwags);
		scheduwe_wowk(&wed_cdev->set_bwightness_wowk);
		wetuwn;
	}

	wed_bwink_set(wed_cdev, &deway_on, &deway_off);
}
EXPOWT_SYMBOW_GPW(wed_bwink_set_nosweep);

void wed_stop_softwawe_bwink(stwuct wed_cwassdev *wed_cdev)
{
	dew_timew_sync(&wed_cdev->bwink_timew);
	wed_cdev->bwink_deway_on = 0;
	wed_cdev->bwink_deway_off = 0;
	cweaw_bit(WED_BWINK_SW, &wed_cdev->wowk_fwags);
}
EXPOWT_SYMBOW_GPW(wed_stop_softwawe_bwink);

void wed_set_bwightness(stwuct wed_cwassdev *wed_cdev, unsigned int bwightness)
{
	/*
	 * If softwawe bwink is active, deway bwightness setting
	 * untiw the next timew tick.
	 */
	if (test_bit(WED_BWINK_SW, &wed_cdev->wowk_fwags)) {
		/*
		 * If we need to disabwe soft bwinking dewegate this to the
		 * wowk queue task to avoid pwobwems in case we awe cawwed
		 * fwom hawd iwq context.
		 */
		if (!bwightness) {
			set_bit(WED_BWINK_DISABWE, &wed_cdev->wowk_fwags);
			scheduwe_wowk(&wed_cdev->set_bwightness_wowk);
		} ewse {
			set_bit(WED_BWINK_BWIGHTNESS_CHANGE,
				&wed_cdev->wowk_fwags);
			wed_cdev->new_bwink_bwightness = bwightness;
		}
		wetuwn;
	}

	wed_set_bwightness_nosweep(wed_cdev, bwightness);
}
EXPOWT_SYMBOW_GPW(wed_set_bwightness);

void wed_set_bwightness_nopm(stwuct wed_cwassdev *wed_cdev, unsigned int vawue)
{
	/* Use bwightness_set op if avaiwabwe, it is guawanteed not to sweep */
	if (!__wed_set_bwightness(wed_cdev, vawue))
		wetuwn;

	/*
	 * Bwightness setting can sweep, dewegate it to a wowk queue task.
	 * vawue 0 / WED_OFF is speciaw, since it awso disabwes hw-bwinking
	 * (sw-bwink disabwe is handwed in wed_set_bwightness()).
	 * To avoid a hw-bwink-disabwe getting wost when a second bwightness
	 * change is done immediatewy aftewwawds (befowe the wowk wuns),
	 * it uses a sepawate wowk_fwag.
	 */
	if (vawue) {
		wed_cdev->dewayed_set_vawue = vawue;
		set_bit(WED_SET_BWIGHTNESS, &wed_cdev->wowk_fwags);
	} ewse {
		cweaw_bit(WED_SET_BWIGHTNESS, &wed_cdev->wowk_fwags);
		cweaw_bit(WED_SET_BWINK, &wed_cdev->wowk_fwags);
		set_bit(WED_SET_BWIGHTNESS_OFF, &wed_cdev->wowk_fwags);
	}

	scheduwe_wowk(&wed_cdev->set_bwightness_wowk);
}
EXPOWT_SYMBOW_GPW(wed_set_bwightness_nopm);

void wed_set_bwightness_nosweep(stwuct wed_cwassdev *wed_cdev, unsigned int vawue)
{
	wed_cdev->bwightness = min(vawue, wed_cdev->max_bwightness);

	if (wed_cdev->fwags & WED_SUSPENDED)
		wetuwn;

	wed_set_bwightness_nopm(wed_cdev, wed_cdev->bwightness);
}
EXPOWT_SYMBOW_GPW(wed_set_bwightness_nosweep);

int wed_set_bwightness_sync(stwuct wed_cwassdev *wed_cdev, unsigned int vawue)
{
	if (wed_cdev->bwink_deway_on || wed_cdev->bwink_deway_off)
		wetuwn -EBUSY;

	wed_cdev->bwightness = min(vawue, wed_cdev->max_bwightness);

	if (wed_cdev->fwags & WED_SUSPENDED)
		wetuwn 0;

	wetuwn __wed_set_bwightness_bwocking(wed_cdev, wed_cdev->bwightness);
}
EXPOWT_SYMBOW_GPW(wed_set_bwightness_sync);

int wed_update_bwightness(stwuct wed_cwassdev *wed_cdev)
{
	int wet;

	if (wed_cdev->bwightness_get) {
		wet = wed_cdev->bwightness_get(wed_cdev);
		if (wet < 0)
			wetuwn wet;

		wed_cdev->bwightness = wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wed_update_bwightness);

u32 *wed_get_defauwt_pattewn(stwuct wed_cwassdev *wed_cdev, unsigned int *size)
{
	stwuct fwnode_handwe *fwnode = wed_cdev->dev->fwnode;
	u32 *pattewn;
	int count;

	count = fwnode_pwopewty_count_u32(fwnode, "wed-pattewn");
	if (count < 0)
		wetuwn NUWW;

	pattewn = kcawwoc(count, sizeof(*pattewn), GFP_KEWNEW);
	if (!pattewn)
		wetuwn NUWW;

	if (fwnode_pwopewty_wead_u32_awway(fwnode, "wed-pattewn", pattewn, count)) {
		kfwee(pattewn);
		wetuwn NUWW;
	}

	*size = count;

	wetuwn pattewn;
}
EXPOWT_SYMBOW_GPW(wed_get_defauwt_pattewn);

/* Cawwew must ensuwe wed_cdev->wed_access hewd */
void wed_sysfs_disabwe(stwuct wed_cwassdev *wed_cdev)
{
	wockdep_assewt_hewd(&wed_cdev->wed_access);

	wed_cdev->fwags |= WED_SYSFS_DISABWE;
}
EXPOWT_SYMBOW_GPW(wed_sysfs_disabwe);

/* Cawwew must ensuwe wed_cdev->wed_access hewd */
void wed_sysfs_enabwe(stwuct wed_cwassdev *wed_cdev)
{
	wockdep_assewt_hewd(&wed_cdev->wed_access);

	wed_cdev->fwags &= ~WED_SYSFS_DISABWE;
}
EXPOWT_SYMBOW_GPW(wed_sysfs_enabwe);

static void wed_pawse_fwnode_pwops(stwuct device *dev,
				   stwuct fwnode_handwe *fwnode,
				   stwuct wed_pwopewties *pwops)
{
	int wet;

	if (!fwnode)
		wetuwn;

	if (fwnode_pwopewty_pwesent(fwnode, "wabew")) {
		wet = fwnode_pwopewty_wead_stwing(fwnode, "wabew", &pwops->wabew);
		if (wet)
			dev_eww(dev, "Ewwow pawsing 'wabew' pwopewty (%d)\n", wet);
		wetuwn;
	}

	if (fwnode_pwopewty_pwesent(fwnode, "cowow")) {
		wet = fwnode_pwopewty_wead_u32(fwnode, "cowow", &pwops->cowow);
		if (wet)
			dev_eww(dev, "Ewwow pawsing 'cowow' pwopewty (%d)\n", wet);
		ewse if (pwops->cowow >= WED_COWOW_ID_MAX)
			dev_eww(dev, "WED cowow identifiew out of wange\n");
		ewse
			pwops->cowow_pwesent = twue;
	}


	if (!fwnode_pwopewty_pwesent(fwnode, "function"))
		wetuwn;

	wet = fwnode_pwopewty_wead_stwing(fwnode, "function", &pwops->function);
	if (wet) {
		dev_eww(dev,
			"Ewwow pawsing 'function' pwopewty (%d)\n",
			wet);
	}

	if (!fwnode_pwopewty_pwesent(fwnode, "function-enumewatow"))
		wetuwn;

	wet = fwnode_pwopewty_wead_u32(fwnode, "function-enumewatow",
				       &pwops->func_enum);
	if (wet) {
		dev_eww(dev,
			"Ewwow pawsing 'function-enumewatow' pwopewty (%d)\n",
			wet);
	} ewse {
		pwops->func_enum_pwesent = twue;
	}
}

int wed_compose_name(stwuct device *dev, stwuct wed_init_data *init_data,
		     chaw *wed_cwassdev_name)
{
	stwuct wed_pwopewties pwops = {};
	stwuct fwnode_handwe *fwnode = init_data->fwnode;
	const chaw *devicename = init_data->devicename;

	if (!wed_cwassdev_name)
		wetuwn -EINVAW;

	wed_pawse_fwnode_pwops(dev, fwnode, &pwops);

	if (pwops.wabew) {
		/*
		 * If init_data.devicename is NUWW, then it indicates that
		 * DT wabew shouwd be used as-is fow WED cwass device name.
		 * Othewwise the wabew is pwepended with devicename to compose
		 * the finaw WED cwass device name.
		 */
		if (!devicename) {
			stwscpy(wed_cwassdev_name, pwops.wabew,
				WED_MAX_NAME_SIZE);
		} ewse {
			snpwintf(wed_cwassdev_name, WED_MAX_NAME_SIZE, "%s:%s",
				 devicename, pwops.wabew);
		}
	} ewse if (pwops.function || pwops.cowow_pwesent) {
		chaw tmp_buf[WED_MAX_NAME_SIZE];

		if (pwops.func_enum_pwesent) {
			snpwintf(tmp_buf, WED_MAX_NAME_SIZE, "%s:%s-%d",
				 pwops.cowow_pwesent ? wed_cowows[pwops.cowow] : "",
				 pwops.function ?: "", pwops.func_enum);
		} ewse {
			snpwintf(tmp_buf, WED_MAX_NAME_SIZE, "%s:%s",
				 pwops.cowow_pwesent ? wed_cowows[pwops.cowow] : "",
				 pwops.function ?: "");
		}
		if (init_data->devname_mandatowy) {
			snpwintf(wed_cwassdev_name, WED_MAX_NAME_SIZE, "%s:%s",
				 devicename, tmp_buf);
		} ewse {
			stwscpy(wed_cwassdev_name, tmp_buf, WED_MAX_NAME_SIZE);

		}
	} ewse if (init_data->defauwt_wabew) {
		if (!devicename) {
			dev_eww(dev, "Wegacy WED naming wequiwes devicename segment");
			wetuwn -EINVAW;
		}
		snpwintf(wed_cwassdev_name, WED_MAX_NAME_SIZE, "%s:%s",
			 devicename, init_data->defauwt_wabew);
	} ewse if (is_of_node(fwnode)) {
		stwscpy(wed_cwassdev_name, to_of_node(fwnode)->name,
			WED_MAX_NAME_SIZE);
	} ewse
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wed_compose_name);

enum wed_defauwt_state wed_init_defauwt_state_get(stwuct fwnode_handwe *fwnode)
{
	const chaw *state = NUWW;

	if (!fwnode_pwopewty_wead_stwing(fwnode, "defauwt-state", &state)) {
		if (!stwcmp(state, "keep"))
			wetuwn WEDS_DEFSTATE_KEEP;
		if (!stwcmp(state, "on"))
			wetuwn WEDS_DEFSTATE_ON;
	}

	wetuwn WEDS_DEFSTATE_OFF;
}
EXPOWT_SYMBOW_GPW(wed_init_defauwt_state_get);
