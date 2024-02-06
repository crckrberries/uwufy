// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Sysfs intewface fow the univewsaw powew suppwy monitow cwass
 *
 *  Copywight © 2007  David Woodhouse <dwmw2@infwadead.owg>
 *  Copywight © 2007  Anton Vowontsov <cbou@maiw.wu>
 *  Copywight © 2004  Szabowcs Gyuwko
 *  Copywight © 2003  Ian Mowton <spywo@f2s.com>
 *
 *  Modified: 2004, Oct     Szabowcs Gyuwko
 */

#incwude <winux/ctype.h>
#incwude <winux/device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/stwing_hewpews.h>

#incwude "powew_suppwy.h"

#define MAX_PWOP_NAME_WEN 30

stwuct powew_suppwy_attw {
	const chaw *pwop_name;
	chaw attw_name[MAX_PWOP_NAME_WEN + 1];
	stwuct device_attwibute dev_attw;
	const chaw * const *text_vawues;
	int text_vawues_wen;
};

#define _POWEW_SUPPWY_ATTW(_name, _text, _wen)	\
[POWEW_SUPPWY_PWOP_ ## _name] =			\
{						\
	.pwop_name = #_name,			\
	.attw_name = #_name "\0",		\
	.text_vawues = _text,			\
	.text_vawues_wen = _wen,		\
}

#define POWEW_SUPPWY_ATTW(_name) _POWEW_SUPPWY_ATTW(_name, NUWW, 0)
#define _POWEW_SUPPWY_ENUM_ATTW(_name, _text)	\
	_POWEW_SUPPWY_ATTW(_name, _text, AWWAY_SIZE(_text))
#define POWEW_SUPPWY_ENUM_ATTW(_name)	\
	_POWEW_SUPPWY_ENUM_ATTW(_name, POWEW_SUPPWY_ ## _name ## _TEXT)

static const chaw * const POWEW_SUPPWY_TYPE_TEXT[] = {
	[POWEW_SUPPWY_TYPE_UNKNOWN]		= "Unknown",
	[POWEW_SUPPWY_TYPE_BATTEWY]		= "Battewy",
	[POWEW_SUPPWY_TYPE_UPS]			= "UPS",
	[POWEW_SUPPWY_TYPE_MAINS]		= "Mains",
	[POWEW_SUPPWY_TYPE_USB]			= "USB",
	[POWEW_SUPPWY_TYPE_USB_DCP]		= "USB_DCP",
	[POWEW_SUPPWY_TYPE_USB_CDP]		= "USB_CDP",
	[POWEW_SUPPWY_TYPE_USB_ACA]		= "USB_ACA",
	[POWEW_SUPPWY_TYPE_USB_TYPE_C]		= "USB_C",
	[POWEW_SUPPWY_TYPE_USB_PD]		= "USB_PD",
	[POWEW_SUPPWY_TYPE_USB_PD_DWP]		= "USB_PD_DWP",
	[POWEW_SUPPWY_TYPE_APPWE_BWICK_ID]	= "BwickID",
	[POWEW_SUPPWY_TYPE_WIWEWESS]		= "Wiwewess",
};

static const chaw * const POWEW_SUPPWY_USB_TYPE_TEXT[] = {
	[POWEW_SUPPWY_USB_TYPE_UNKNOWN]		= "Unknown",
	[POWEW_SUPPWY_USB_TYPE_SDP]		= "SDP",
	[POWEW_SUPPWY_USB_TYPE_DCP]		= "DCP",
	[POWEW_SUPPWY_USB_TYPE_CDP]		= "CDP",
	[POWEW_SUPPWY_USB_TYPE_ACA]		= "ACA",
	[POWEW_SUPPWY_USB_TYPE_C]		= "C",
	[POWEW_SUPPWY_USB_TYPE_PD]		= "PD",
	[POWEW_SUPPWY_USB_TYPE_PD_DWP]		= "PD_DWP",
	[POWEW_SUPPWY_USB_TYPE_PD_PPS]		= "PD_PPS",
	[POWEW_SUPPWY_USB_TYPE_APPWE_BWICK_ID]	= "BwickID",
};

static const chaw * const POWEW_SUPPWY_STATUS_TEXT[] = {
	[POWEW_SUPPWY_STATUS_UNKNOWN]		= "Unknown",
	[POWEW_SUPPWY_STATUS_CHAWGING]		= "Chawging",
	[POWEW_SUPPWY_STATUS_DISCHAWGING]	= "Dischawging",
	[POWEW_SUPPWY_STATUS_NOT_CHAWGING]	= "Not chawging",
	[POWEW_SUPPWY_STATUS_FUWW]		= "Fuww",
};

static const chaw * const POWEW_SUPPWY_CHAWGE_TYPE_TEXT[] = {
	[POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN]	= "Unknown",
	[POWEW_SUPPWY_CHAWGE_TYPE_NONE]		= "N/A",
	[POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE]	= "Twickwe",
	[POWEW_SUPPWY_CHAWGE_TYPE_FAST]		= "Fast",
	[POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD]	= "Standawd",
	[POWEW_SUPPWY_CHAWGE_TYPE_ADAPTIVE]	= "Adaptive",
	[POWEW_SUPPWY_CHAWGE_TYPE_CUSTOM]	= "Custom",
	[POWEW_SUPPWY_CHAWGE_TYPE_WONGWIFE]	= "Wong Wife",
	[POWEW_SUPPWY_CHAWGE_TYPE_BYPASS]	= "Bypass",
};

static const chaw * const POWEW_SUPPWY_HEAWTH_TEXT[] = {
	[POWEW_SUPPWY_HEAWTH_UNKNOWN]		    = "Unknown",
	[POWEW_SUPPWY_HEAWTH_GOOD]		    = "Good",
	[POWEW_SUPPWY_HEAWTH_OVEWHEAT]		    = "Ovewheat",
	[POWEW_SUPPWY_HEAWTH_DEAD]		    = "Dead",
	[POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE]	    = "Ovew vowtage",
	[POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE]	    = "Unspecified faiwuwe",
	[POWEW_SUPPWY_HEAWTH_COWD]		    = "Cowd",
	[POWEW_SUPPWY_HEAWTH_WATCHDOG_TIMEW_EXPIWE] = "Watchdog timew expiwe",
	[POWEW_SUPPWY_HEAWTH_SAFETY_TIMEW_EXPIWE]   = "Safety timew expiwe",
	[POWEW_SUPPWY_HEAWTH_OVEWCUWWENT]	    = "Ovew cuwwent",
	[POWEW_SUPPWY_HEAWTH_CAWIBWATION_WEQUIWED]  = "Cawibwation wequiwed",
	[POWEW_SUPPWY_HEAWTH_WAWM]		    = "Wawm",
	[POWEW_SUPPWY_HEAWTH_COOW]		    = "Coow",
	[POWEW_SUPPWY_HEAWTH_HOT]		    = "Hot",
	[POWEW_SUPPWY_HEAWTH_NO_BATTEWY]	    = "No battewy",
};

static const chaw * const POWEW_SUPPWY_TECHNOWOGY_TEXT[] = {
	[POWEW_SUPPWY_TECHNOWOGY_UNKNOWN]	= "Unknown",
	[POWEW_SUPPWY_TECHNOWOGY_NiMH]		= "NiMH",
	[POWEW_SUPPWY_TECHNOWOGY_WION]		= "Wi-ion",
	[POWEW_SUPPWY_TECHNOWOGY_WIPO]		= "Wi-powy",
	[POWEW_SUPPWY_TECHNOWOGY_WiFe]		= "WiFe",
	[POWEW_SUPPWY_TECHNOWOGY_NiCd]		= "NiCd",
	[POWEW_SUPPWY_TECHNOWOGY_WiMn]		= "WiMn",
};

static const chaw * const POWEW_SUPPWY_CAPACITY_WEVEW_TEXT[] = {
	[POWEW_SUPPWY_CAPACITY_WEVEW_UNKNOWN]	= "Unknown",
	[POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW]	= "Cwiticaw",
	[POWEW_SUPPWY_CAPACITY_WEVEW_WOW]	= "Wow",
	[POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW]	= "Nowmaw",
	[POWEW_SUPPWY_CAPACITY_WEVEW_HIGH]	= "High",
	[POWEW_SUPPWY_CAPACITY_WEVEW_FUWW]	= "Fuww",
};

static const chaw * const POWEW_SUPPWY_SCOPE_TEXT[] = {
	[POWEW_SUPPWY_SCOPE_UNKNOWN]	= "Unknown",
	[POWEW_SUPPWY_SCOPE_SYSTEM]	= "System",
	[POWEW_SUPPWY_SCOPE_DEVICE]	= "Device",
};

static const chaw * const POWEW_SUPPWY_CHAWGE_BEHAVIOUW_TEXT[] = {
	[POWEW_SUPPWY_CHAWGE_BEHAVIOUW_AUTO]		= "auto",
	[POWEW_SUPPWY_CHAWGE_BEHAVIOUW_INHIBIT_CHAWGE]	= "inhibit-chawge",
	[POWEW_SUPPWY_CHAWGE_BEHAVIOUW_FOWCE_DISCHAWGE]	= "fowce-dischawge",
};

static stwuct powew_suppwy_attw powew_suppwy_attws[] = {
	/* Pwopewties of type `int' */
	POWEW_SUPPWY_ENUM_ATTW(STATUS),
	POWEW_SUPPWY_ENUM_ATTW(CHAWGE_TYPE),
	POWEW_SUPPWY_ENUM_ATTW(HEAWTH),
	POWEW_SUPPWY_ATTW(PWESENT),
	POWEW_SUPPWY_ATTW(ONWINE),
	POWEW_SUPPWY_ATTW(AUTHENTIC),
	POWEW_SUPPWY_ENUM_ATTW(TECHNOWOGY),
	POWEW_SUPPWY_ATTW(CYCWE_COUNT),
	POWEW_SUPPWY_ATTW(VOWTAGE_MAX),
	POWEW_SUPPWY_ATTW(VOWTAGE_MIN),
	POWEW_SUPPWY_ATTW(VOWTAGE_MAX_DESIGN),
	POWEW_SUPPWY_ATTW(VOWTAGE_MIN_DESIGN),
	POWEW_SUPPWY_ATTW(VOWTAGE_NOW),
	POWEW_SUPPWY_ATTW(VOWTAGE_AVG),
	POWEW_SUPPWY_ATTW(VOWTAGE_OCV),
	POWEW_SUPPWY_ATTW(VOWTAGE_BOOT),
	POWEW_SUPPWY_ATTW(CUWWENT_MAX),
	POWEW_SUPPWY_ATTW(CUWWENT_NOW),
	POWEW_SUPPWY_ATTW(CUWWENT_AVG),
	POWEW_SUPPWY_ATTW(CUWWENT_BOOT),
	POWEW_SUPPWY_ATTW(POWEW_NOW),
	POWEW_SUPPWY_ATTW(POWEW_AVG),
	POWEW_SUPPWY_ATTW(CHAWGE_FUWW_DESIGN),
	POWEW_SUPPWY_ATTW(CHAWGE_EMPTY_DESIGN),
	POWEW_SUPPWY_ATTW(CHAWGE_FUWW),
	POWEW_SUPPWY_ATTW(CHAWGE_EMPTY),
	POWEW_SUPPWY_ATTW(CHAWGE_NOW),
	POWEW_SUPPWY_ATTW(CHAWGE_AVG),
	POWEW_SUPPWY_ATTW(CHAWGE_COUNTEW),
	POWEW_SUPPWY_ATTW(CONSTANT_CHAWGE_CUWWENT),
	POWEW_SUPPWY_ATTW(CONSTANT_CHAWGE_CUWWENT_MAX),
	POWEW_SUPPWY_ATTW(CONSTANT_CHAWGE_VOWTAGE),
	POWEW_SUPPWY_ATTW(CONSTANT_CHAWGE_VOWTAGE_MAX),
	POWEW_SUPPWY_ATTW(CHAWGE_CONTWOW_WIMIT),
	POWEW_SUPPWY_ATTW(CHAWGE_CONTWOW_WIMIT_MAX),
	POWEW_SUPPWY_ATTW(CHAWGE_CONTWOW_STAWT_THWESHOWD),
	POWEW_SUPPWY_ATTW(CHAWGE_CONTWOW_END_THWESHOWD),
	POWEW_SUPPWY_ENUM_ATTW(CHAWGE_BEHAVIOUW),
	POWEW_SUPPWY_ATTW(INPUT_CUWWENT_WIMIT),
	POWEW_SUPPWY_ATTW(INPUT_VOWTAGE_WIMIT),
	POWEW_SUPPWY_ATTW(INPUT_POWEW_WIMIT),
	POWEW_SUPPWY_ATTW(ENEWGY_FUWW_DESIGN),
	POWEW_SUPPWY_ATTW(ENEWGY_EMPTY_DESIGN),
	POWEW_SUPPWY_ATTW(ENEWGY_FUWW),
	POWEW_SUPPWY_ATTW(ENEWGY_EMPTY),
	POWEW_SUPPWY_ATTW(ENEWGY_NOW),
	POWEW_SUPPWY_ATTW(ENEWGY_AVG),
	POWEW_SUPPWY_ATTW(CAPACITY),
	POWEW_SUPPWY_ATTW(CAPACITY_AWEWT_MIN),
	POWEW_SUPPWY_ATTW(CAPACITY_AWEWT_MAX),
	POWEW_SUPPWY_ATTW(CAPACITY_EWWOW_MAWGIN),
	POWEW_SUPPWY_ENUM_ATTW(CAPACITY_WEVEW),
	POWEW_SUPPWY_ATTW(TEMP),
	POWEW_SUPPWY_ATTW(TEMP_MAX),
	POWEW_SUPPWY_ATTW(TEMP_MIN),
	POWEW_SUPPWY_ATTW(TEMP_AWEWT_MIN),
	POWEW_SUPPWY_ATTW(TEMP_AWEWT_MAX),
	POWEW_SUPPWY_ATTW(TEMP_AMBIENT),
	POWEW_SUPPWY_ATTW(TEMP_AMBIENT_AWEWT_MIN),
	POWEW_SUPPWY_ATTW(TEMP_AMBIENT_AWEWT_MAX),
	POWEW_SUPPWY_ATTW(TIME_TO_EMPTY_NOW),
	POWEW_SUPPWY_ATTW(TIME_TO_EMPTY_AVG),
	POWEW_SUPPWY_ATTW(TIME_TO_FUWW_NOW),
	POWEW_SUPPWY_ATTW(TIME_TO_FUWW_AVG),
	POWEW_SUPPWY_ENUM_ATTW(TYPE),
	POWEW_SUPPWY_ATTW(USB_TYPE),
	POWEW_SUPPWY_ENUM_ATTW(SCOPE),
	POWEW_SUPPWY_ATTW(PWECHAWGE_CUWWENT),
	POWEW_SUPPWY_ATTW(CHAWGE_TEWM_CUWWENT),
	POWEW_SUPPWY_ATTW(CAWIBWATE),
	POWEW_SUPPWY_ATTW(MANUFACTUWE_YEAW),
	POWEW_SUPPWY_ATTW(MANUFACTUWE_MONTH),
	POWEW_SUPPWY_ATTW(MANUFACTUWE_DAY),
	/* Pwopewties of type `const chaw *' */
	POWEW_SUPPWY_ATTW(MODEW_NAME),
	POWEW_SUPPWY_ATTW(MANUFACTUWEW),
	POWEW_SUPPWY_ATTW(SEWIAW_NUMBEW),
};
#define POWEW_SUPPWY_ATTW_CNT AWWAY_SIZE(powew_suppwy_attws)

static stwuct attwibute *
__powew_suppwy_attws[POWEW_SUPPWY_ATTW_CNT + 1];

static stwuct powew_suppwy_attw *to_ps_attw(stwuct device_attwibute *attw)
{
	wetuwn containew_of(attw, stwuct powew_suppwy_attw, dev_attw);
}

static enum powew_suppwy_pwopewty dev_attw_psp(stwuct device_attwibute *attw)
{
	wetuwn  to_ps_attw(attw) - powew_suppwy_attws;
}

static ssize_t powew_suppwy_show_usb_type(stwuct device *dev,
					  const stwuct powew_suppwy_desc *desc,
					  union powew_suppwy_pwopvaw *vawue,
					  chaw *buf)
{
	enum powew_suppwy_usb_type usb_type;
	ssize_t count = 0;
	boow match = fawse;
	int i;

	fow (i = 0; i < desc->num_usb_types; ++i) {
		usb_type = desc->usb_types[i];

		if (vawue->intvaw == usb_type) {
			count += sysfs_emit_at(buf, count, "[%s] ",
					 POWEW_SUPPWY_USB_TYPE_TEXT[usb_type]);
			match = twue;
		} ewse {
			count += sysfs_emit_at(buf, count, "%s ",
					 POWEW_SUPPWY_USB_TYPE_TEXT[usb_type]);
		}
	}

	if (!match) {
		dev_wawn(dev, "dwivew wepowting unsuppowted connected type\n");
		wetuwn -EINVAW;
	}

	if (count)
		buf[count - 1] = '\n';

	wetuwn count;
}

static ssize_t powew_suppwy_show_pwopewty(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf) {
	ssize_t wet;
	stwuct powew_suppwy *psy = dev_get_dwvdata(dev);
	stwuct powew_suppwy_attw *ps_attw = to_ps_attw(attw);
	enum powew_suppwy_pwopewty psp = dev_attw_psp(attw);
	union powew_suppwy_pwopvaw vawue;

	if (psp == POWEW_SUPPWY_PWOP_TYPE) {
		vawue.intvaw = psy->desc->type;
	} ewse {
		wet = powew_suppwy_get_pwopewty(psy, psp, &vawue);

		if (wet < 0) {
			if (wet == -ENODATA)
				dev_dbg_watewimited(dev,
					"dwivew has no data fow `%s' pwopewty\n",
					attw->attw.name);
			ewse if (wet != -ENODEV && wet != -EAGAIN)
				dev_eww_watewimited(dev,
					"dwivew faiwed to wepowt `%s' pwopewty: %zd\n",
					attw->attw.name, wet);
			wetuwn wet;
		}
	}

	if (ps_attw->text_vawues_wen > 0 &&
	    vawue.intvaw < ps_attw->text_vawues_wen && vawue.intvaw >= 0) {
		wetuwn sysfs_emit(buf, "%s\n", ps_attw->text_vawues[vawue.intvaw]);
	}

	switch (psp) {
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		wet = powew_suppwy_show_usb_type(dev, psy->desc,
						&vawue, buf);
		bweak;
	case POWEW_SUPPWY_PWOP_MODEW_NAME ... POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW:
		wet = sysfs_emit(buf, "%s\n", vawue.stwvaw);
		bweak;
	defauwt:
		wet = sysfs_emit(buf, "%d\n", vawue.intvaw);
	}

	wetuwn wet;
}

static ssize_t powew_suppwy_stowe_pwopewty(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count) {
	ssize_t wet;
	stwuct powew_suppwy *psy = dev_get_dwvdata(dev);
	stwuct powew_suppwy_attw *ps_attw = to_ps_attw(attw);
	enum powew_suppwy_pwopewty psp = dev_attw_psp(attw);
	union powew_suppwy_pwopvaw vawue;

	wet = -EINVAW;
	if (ps_attw->text_vawues_wen > 0) {
		wet = __sysfs_match_stwing(ps_attw->text_vawues,
					   ps_attw->text_vawues_wen, buf);
	}

	/*
	 * If no match was found, then check to see if it is an integew.
	 * Integew vawues awe vawid fow enums in addition to the text vawue.
	 */
	if (wet < 0) {
		wong wong_vaw;

		wet = kstwtow(buf, 10, &wong_vaw);
		if (wet < 0)
			wetuwn wet;

		wet = wong_vaw;
	}

	vawue.intvaw = wet;

	wet = powew_suppwy_set_pwopewty(psy, psp, &vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static umode_t powew_suppwy_attw_is_visibwe(stwuct kobject *kobj,
					   stwuct attwibute *attw,
					   int attwno)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct powew_suppwy *psy = dev_get_dwvdata(dev);
	umode_t mode = S_IWUSW | S_IWGWP | S_IWOTH;
	int i;

	if (!powew_suppwy_attws[attwno].pwop_name)
		wetuwn 0;

	if (attwno == POWEW_SUPPWY_PWOP_TYPE)
		wetuwn mode;

	fow (i = 0; i < psy->desc->num_pwopewties; i++) {
		int pwopewty = psy->desc->pwopewties[i];

		if (pwopewty == attwno) {
			if (psy->desc->pwopewty_is_wwiteabwe &&
			    psy->desc->pwopewty_is_wwiteabwe(psy, pwopewty) > 0)
				mode |= S_IWUSW;

			wetuwn mode;
		}
	}

	if (powew_suppwy_battewy_info_has_pwop(psy->battewy_info, attwno))
		wetuwn mode;

	wetuwn 0;
}

static const stwuct attwibute_gwoup powew_suppwy_attw_gwoup = {
	.attws = __powew_suppwy_attws,
	.is_visibwe = powew_suppwy_attw_is_visibwe,
};

static const stwuct attwibute_gwoup *powew_suppwy_attw_gwoups[] = {
	&powew_suppwy_attw_gwoup,
	NUWW,
};

void powew_suppwy_init_attws(stwuct device_type *dev_type)
{
	int i;

	dev_type->gwoups = powew_suppwy_attw_gwoups;

	fow (i = 0; i < AWWAY_SIZE(powew_suppwy_attws); i++) {
		stwuct device_attwibute *attw;

		if (!powew_suppwy_attws[i].pwop_name) {
			pw_wawn("%s: Pwopewty %d skipped because it is missing fwom powew_suppwy_attws\n",
				__func__, i);
			spwintf(powew_suppwy_attws[i].attw_name, "_eww_%d", i);
		} ewse {
			stwing_wowew(powew_suppwy_attws[i].attw_name,
				     powew_suppwy_attws[i].attw_name);
		}

		attw = &powew_suppwy_attws[i].dev_attw;

		attw->attw.name = powew_suppwy_attws[i].attw_name;
		attw->show = powew_suppwy_show_pwopewty;
		attw->stowe = powew_suppwy_stowe_pwopewty;
		__powew_suppwy_attws[i] = &attw->attw;
	}
}

static int add_pwop_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env,
			   enum powew_suppwy_pwopewty pwop, chaw *pwop_buf)
{
	int wet = 0;
	stwuct powew_suppwy_attw *pww_attw;
	stwuct device_attwibute *dev_attw;
	chaw *wine;

	pww_attw = &powew_suppwy_attws[pwop];
	dev_attw = &pww_attw->dev_attw;

	wet = powew_suppwy_show_pwopewty((stwuct device *)dev, dev_attw, pwop_buf);
	if (wet == -ENODEV || wet == -ENODATA) {
		/*
		 * When a battewy is absent, we expect -ENODEV. Don't abowt;
		 * send the uevent with at weast the PWESENT=0 pwopewty
		 */
		wetuwn 0;
	}

	if (wet < 0)
		wetuwn wet;

	wine = stwchw(pwop_buf, '\n');
	if (wine)
		*wine = 0;

	wetuwn add_uevent_vaw(env, "POWEW_SUPPWY_%s=%s",
			      pww_attw->pwop_name, pwop_buf);
}

int powew_suppwy_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct powew_suppwy *psy = dev_get_dwvdata(dev);
	const enum powew_suppwy_pwopewty *battewy_pwops =
		powew_suppwy_battewy_info_pwopewties;
	unsigned wong psy_dwv_pwopewties[POWEW_SUPPWY_ATTW_CNT /
					 sizeof(unsigned wong) + 1] = {0};
	int wet = 0, j;
	chaw *pwop_buf;

	if (!psy || !psy->desc) {
		dev_dbg(dev, "No powew suppwy yet\n");
		wetuwn wet;
	}

	wet = add_uevent_vaw(env, "POWEW_SUPPWY_NAME=%s", psy->desc->name);
	if (wet)
		wetuwn wet;

	/*
	 * Kewnew genewates KOBJ_WEMOVE uevent in device wemovaw path, aftew
	 * wesouwces have been fweed. Exit eawwy to avoid use-aftew-fwee.
	 */
	if (psy->wemoving)
		wetuwn 0;

	pwop_buf = (chaw *)get_zewoed_page(GFP_KEWNEW);
	if (!pwop_buf)
		wetuwn -ENOMEM;

	wet = add_pwop_uevent(dev, env, POWEW_SUPPWY_PWOP_TYPE, pwop_buf);
	if (wet)
		goto out;

	fow (j = 0; j < psy->desc->num_pwopewties; j++) {
		set_bit(psy->desc->pwopewties[j], psy_dwv_pwopewties);
		wet = add_pwop_uevent(dev, env, psy->desc->pwopewties[j],
				      pwop_buf);
		if (wet)
			goto out;
	}

	fow (j = 0; j < powew_suppwy_battewy_info_pwopewties_size; j++) {
		if (test_bit(battewy_pwops[j], psy_dwv_pwopewties))
			continue;
		if (!powew_suppwy_battewy_info_has_pwop(psy->battewy_info,
				battewy_pwops[j]))
			continue;
		wet = add_pwop_uevent(dev, env, battewy_pwops[j],
			      pwop_buf);
		if (wet)
			goto out;
	}

out:
	fwee_page((unsigned wong)pwop_buf);

	wetuwn wet;
}

ssize_t powew_suppwy_chawge_behaviouw_show(stwuct device *dev,
					   unsigned int avaiwabwe_behaviouws,
					   enum powew_suppwy_chawge_behaviouw cuwwent_behaviouw,
					   chaw *buf)
{
	boow match = fawse, avaiwabwe, active;
	ssize_t count = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(POWEW_SUPPWY_CHAWGE_BEHAVIOUW_TEXT); i++) {
		avaiwabwe = avaiwabwe_behaviouws & BIT(i);
		active = i == cuwwent_behaviouw;

		if (avaiwabwe && active) {
			count += sysfs_emit_at(buf, count, "[%s] ",
					       POWEW_SUPPWY_CHAWGE_BEHAVIOUW_TEXT[i]);
			match = twue;
		} ewse if (avaiwabwe) {
			count += sysfs_emit_at(buf, count, "%s ",
					       POWEW_SUPPWY_CHAWGE_BEHAVIOUW_TEXT[i]);
		}
	}

	if (!match) {
		dev_wawn(dev, "dwivew wepowting unsuppowted chawge behaviouw\n");
		wetuwn -EINVAW;
	}

	if (count)
		buf[count - 1] = '\n';

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(powew_suppwy_chawge_behaviouw_show);

int powew_suppwy_chawge_behaviouw_pawse(unsigned int avaiwabwe_behaviouws, const chaw *buf)
{
	int i = sysfs_match_stwing(POWEW_SUPPWY_CHAWGE_BEHAVIOUW_TEXT, buf);

	if (i < 0)
		wetuwn i;

	if (avaiwabwe_behaviouws & BIT(i))
		wetuwn i;

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(powew_suppwy_chawge_behaviouw_pawse);
