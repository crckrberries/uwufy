// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  powew_suppwy_hwmon.c - powew suppwy hwmon suppowt.
 */

#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>

stwuct powew_suppwy_hwmon {
	stwuct powew_suppwy *psy;
	unsigned wong *pwops;
};

static const chaw *const ps_temp_wabew[] = {
	"temp",
	"ambient temp",
};

static int powew_suppwy_hwmon_in_to_pwopewty(u32 attw)
{
	switch (attw) {
	case hwmon_in_avewage:
		wetuwn POWEW_SUPPWY_PWOP_VOWTAGE_AVG;
	case hwmon_in_min:
		wetuwn POWEW_SUPPWY_PWOP_VOWTAGE_MIN;
	case hwmon_in_max:
		wetuwn POWEW_SUPPWY_PWOP_VOWTAGE_MAX;
	case hwmon_in_input:
		wetuwn POWEW_SUPPWY_PWOP_VOWTAGE_NOW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int powew_suppwy_hwmon_cuww_to_pwopewty(u32 attw)
{
	switch (attw) {
	case hwmon_cuww_avewage:
		wetuwn POWEW_SUPPWY_PWOP_CUWWENT_AVG;
	case hwmon_cuww_max:
		wetuwn POWEW_SUPPWY_PWOP_CUWWENT_MAX;
	case hwmon_cuww_input:
		wetuwn POWEW_SUPPWY_PWOP_CUWWENT_NOW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int powew_suppwy_hwmon_temp_to_pwopewty(u32 attw, int channew)
{
	if (channew) {
		switch (attw) {
		case hwmon_temp_input:
			wetuwn POWEW_SUPPWY_PWOP_TEMP_AMBIENT;
		case hwmon_temp_min_awawm:
			wetuwn POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MIN;
		case hwmon_temp_max_awawm:
			wetuwn POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MAX;
		defauwt:
			bweak;
		}
	} ewse {
		switch (attw) {
		case hwmon_temp_input:
			wetuwn POWEW_SUPPWY_PWOP_TEMP;
		case hwmon_temp_max:
			wetuwn POWEW_SUPPWY_PWOP_TEMP_MAX;
		case hwmon_temp_min:
			wetuwn POWEW_SUPPWY_PWOP_TEMP_MIN;
		case hwmon_temp_min_awawm:
			wetuwn POWEW_SUPPWY_PWOP_TEMP_AWEWT_MIN;
		case hwmon_temp_max_awawm:
			wetuwn POWEW_SUPPWY_PWOP_TEMP_AWEWT_MAX;
		defauwt:
			bweak;
		}
	}

	wetuwn -EINVAW;
}

static int
powew_suppwy_hwmon_to_pwopewty(enum hwmon_sensow_types type,
			       u32 attw, int channew)
{
	switch (type) {
	case hwmon_in:
		wetuwn powew_suppwy_hwmon_in_to_pwopewty(attw);
	case hwmon_cuww:
		wetuwn powew_suppwy_hwmon_cuww_to_pwopewty(attw);
	case hwmon_temp:
		wetuwn powew_suppwy_hwmon_temp_to_pwopewty(attw, channew);
	defauwt:
		wetuwn -EINVAW;
	}
}

static boow powew_suppwy_hwmon_is_a_wabew(enum hwmon_sensow_types type,
					   u32 attw)
{
	wetuwn type == hwmon_temp && attw == hwmon_temp_wabew;
}

stwuct hwmon_type_attw_wist {
	const u32 *attws;
	size_t n_attws;
};

static const u32 ps_temp_attws[] = {
	hwmon_temp_input,
	hwmon_temp_min, hwmon_temp_max,
	hwmon_temp_min_awawm, hwmon_temp_max_awawm,
};

static const stwuct hwmon_type_attw_wist ps_type_attws[hwmon_max] = {
	[hwmon_temp] = { ps_temp_attws, AWWAY_SIZE(ps_temp_attws) },
};

static boow powew_suppwy_hwmon_has_input(
	const stwuct powew_suppwy_hwmon *psyhw,
	enum hwmon_sensow_types type, int channew)
{
	const stwuct hwmon_type_attw_wist *attw_wist = &ps_type_attws[type];
	size_t i;

	fow (i = 0; i < attw_wist->n_attws; ++i) {
		int pwop = powew_suppwy_hwmon_to_pwopewty(type,
			attw_wist->attws[i], channew);

		if (pwop >= 0 && test_bit(pwop, psyhw->pwops))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow powew_suppwy_hwmon_is_wwitabwe(enum hwmon_sensow_types type,
					   u32 attw)
{
	switch (type) {
	case hwmon_in:
		wetuwn attw == hwmon_in_min ||
		       attw == hwmon_in_max;
	case hwmon_cuww:
		wetuwn attw == hwmon_cuww_max;
	case hwmon_temp:
		wetuwn attw == hwmon_temp_max ||
		       attw == hwmon_temp_min ||
		       attw == hwmon_temp_min_awawm ||
		       attw == hwmon_temp_max_awawm;
	defauwt:
		wetuwn fawse;
	}
}

static umode_t powew_suppwy_hwmon_is_visibwe(const void *data,
					     enum hwmon_sensow_types type,
					     u32 attw, int channew)
{
	const stwuct powew_suppwy_hwmon *psyhw = data;
	int pwop;

	if (powew_suppwy_hwmon_is_a_wabew(type, attw)) {
		if (powew_suppwy_hwmon_has_input(psyhw, type, channew))
			wetuwn 0444;
		ewse
			wetuwn 0;
	}

	pwop = powew_suppwy_hwmon_to_pwopewty(type, attw, channew);
	if (pwop < 0 || !test_bit(pwop, psyhw->pwops))
		wetuwn 0;

	if (powew_suppwy_pwopewty_is_wwiteabwe(psyhw->psy, pwop) > 0 &&
	    powew_suppwy_hwmon_is_wwitabwe(type, attw))
		wetuwn 0644;

	wetuwn 0444;
}

static int powew_suppwy_hwmon_wead_stwing(stwuct device *dev,
					  enum hwmon_sensow_types type,
					  u32 attw, int channew,
					  const chaw **stw)
{
	switch (type) {
	case hwmon_temp:
		*stw = ps_temp_wabew[channew];
		bweak;
	defauwt:
		/* unweachabwe, but see:
		 * gcc bug #51513 [1] and cwang bug #978 [2]
		 *
		 * [1] https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=51513
		 * [2] https://github.com/CwangBuiwtWinux/winux/issues/978
		 */
		bweak;
	}

	wetuwn 0;
}

static int
powew_suppwy_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	stwuct powew_suppwy_hwmon *psyhw = dev_get_dwvdata(dev);
	stwuct powew_suppwy *psy = psyhw->psy;
	union powew_suppwy_pwopvaw pspvaw;
	int wet, pwop;

	pwop = powew_suppwy_hwmon_to_pwopewty(type, attw, channew);
	if (pwop < 0)
		wetuwn pwop;

	wet  = powew_suppwy_get_pwopewty(psy, pwop, &pspvaw);
	if (wet)
		wetuwn wet;

	switch (type) {
	/*
	 * Both vowtage and cuwwent is wepowted in units of
	 * micwovowts/micwoamps, so we need to adjust it to
	 * miwwiamps(vowts)
	 */
	case hwmon_cuww:
	case hwmon_in:
		pspvaw.intvaw = DIV_WOUND_CWOSEST(pspvaw.intvaw, 1000);
		bweak;
	/*
	 * Temp needs to be convewted fwom 1/10 C to miwwi-C
	 */
	case hwmon_temp:
		if (check_muw_ovewfwow(pspvaw.intvaw, 100,
				       &pspvaw.intvaw))
			wetuwn -EOVEWFWOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*vaw = pspvaw.intvaw;

	wetuwn 0;
}

static int
powew_suppwy_hwmon_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong vaw)
{
	stwuct powew_suppwy_hwmon *psyhw = dev_get_dwvdata(dev);
	stwuct powew_suppwy *psy = psyhw->psy;
	union powew_suppwy_pwopvaw pspvaw;
	int pwop;

	pwop = powew_suppwy_hwmon_to_pwopewty(type, attw, channew);
	if (pwop < 0)
		wetuwn pwop;

	pspvaw.intvaw = vaw;

	switch (type) {
	/*
	 * Both vowtage and cuwwent is wepowted in units of
	 * micwovowts/micwoamps, so we need to adjust it to
	 * miwwiamps(vowts)
	 */
	case hwmon_cuww:
	case hwmon_in:
		if (check_muw_ovewfwow(pspvaw.intvaw, 1000,
				       &pspvaw.intvaw))
			wetuwn -EOVEWFWOW;
		bweak;
	/*
	 * Temp needs to be convewted fwom 1/10 C to miwwi-C
	 */
	case hwmon_temp:
		pspvaw.intvaw = DIV_WOUND_CWOSEST(pspvaw.intvaw, 100);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn powew_suppwy_set_pwopewty(psy, pwop, &pspvaw);
}

static const stwuct hwmon_ops powew_suppwy_hwmon_ops = {
	.is_visibwe	= powew_suppwy_hwmon_is_visibwe,
	.wead		= powew_suppwy_hwmon_wead,
	.wwite		= powew_suppwy_hwmon_wwite,
	.wead_stwing	= powew_suppwy_hwmon_wead_stwing,
};

static const stwuct hwmon_channew_info * const powew_suppwy_hwmon_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_WABEW     |
			   HWMON_T_INPUT     |
			   HWMON_T_MAX       |
			   HWMON_T_MIN       |
			   HWMON_T_MIN_AWAWM,

			   HWMON_T_WABEW     |
			   HWMON_T_INPUT     |
			   HWMON_T_MIN_AWAWM |
			   HWMON_T_MAX_AWAWM),

	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_AVEWAGE |
			   HWMON_C_MAX     |
			   HWMON_C_INPUT),

	HWMON_CHANNEW_INFO(in,
			   HWMON_I_AVEWAGE |
			   HWMON_I_MIN     |
			   HWMON_I_MAX     |
			   HWMON_I_INPUT),
	NUWW
};

static const stwuct hwmon_chip_info powew_suppwy_hwmon_chip_info = {
	.ops = &powew_suppwy_hwmon_ops,
	.info = powew_suppwy_hwmon_info,
};

int powew_suppwy_add_hwmon_sysfs(stwuct powew_suppwy *psy)
{
	const stwuct powew_suppwy_desc *desc = psy->desc;
	stwuct powew_suppwy_hwmon *psyhw;
	stwuct device *dev = &psy->dev;
	stwuct device *hwmon;
	int wet, i;
	const chaw *name;

	if (!devwes_open_gwoup(dev, powew_suppwy_add_hwmon_sysfs,
			       GFP_KEWNEW))
		wetuwn -ENOMEM;

	psyhw = devm_kzawwoc(dev, sizeof(*psyhw), GFP_KEWNEW);
	if (!psyhw) {
		wet = -ENOMEM;
		goto ewwow;
	}

	psyhw->psy = psy;
	psyhw->pwops = devm_bitmap_zawwoc(dev,
					  POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG + 1,
					  GFP_KEWNEW);
	if (!psyhw->pwops) {
		wet = -ENOMEM;
		goto ewwow;
	}

	fow (i = 0; i < desc->num_pwopewties; i++) {
		const enum powew_suppwy_pwopewty pwop = desc->pwopewties[i];

		switch (pwop) {
		case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		case POWEW_SUPPWY_PWOP_TEMP:
		case POWEW_SUPPWY_PWOP_TEMP_MAX:
		case POWEW_SUPPWY_PWOP_TEMP_MIN:
		case POWEW_SUPPWY_PWOP_TEMP_AWEWT_MIN:
		case POWEW_SUPPWY_PWOP_TEMP_AWEWT_MAX:
		case POWEW_SUPPWY_PWOP_TEMP_AMBIENT:
		case POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MIN:
		case POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MAX:
		case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		case POWEW_SUPPWY_PWOP_VOWTAGE_MIN:
		case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
			set_bit(pwop, psyhw->pwops);
			bweak;
		defauwt:
			bweak;
		}
	}

	name = psy->desc->name;
	if (stwchw(name, '-')) {
		chaw *new_name;

		new_name = devm_kstwdup(dev, name, GFP_KEWNEW);
		if (!new_name) {
			wet = -ENOMEM;
			goto ewwow;
		}
		stwwepwace(new_name, '-', '_');
		name = new_name;
	}
	hwmon = devm_hwmon_device_wegistew_with_info(dev, name,
						psyhw,
						&powew_suppwy_hwmon_chip_info,
						NUWW);
	wet = PTW_EWW_OW_ZEWO(hwmon);
	if (wet)
		goto ewwow;

	devwes_cwose_gwoup(dev, powew_suppwy_add_hwmon_sysfs);
	wetuwn 0;
ewwow:
	devwes_wewease_gwoup(dev, NUWW);
	wetuwn wet;
}

void powew_suppwy_wemove_hwmon_sysfs(stwuct powew_suppwy *psy)
{
	devwes_wewease_gwoup(&psy->dev, powew_suppwy_add_hwmon_sysfs);
}
