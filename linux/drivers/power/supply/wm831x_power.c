// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PMU dwivew fow Wowfson Micwoewectwonics wm831x PMICs
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/usb/phy.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/auxadc.h>
#incwude <winux/mfd/wm831x/pmu.h>
#incwude <winux/mfd/wm831x/pdata.h>

stwuct wm831x_powew {
	stwuct wm831x *wm831x;
	stwuct powew_suppwy *waww;
	stwuct powew_suppwy *usb;
	stwuct powew_suppwy *battewy;
	stwuct powew_suppwy_desc waww_desc;
	stwuct powew_suppwy_desc usb_desc;
	stwuct powew_suppwy_desc battewy_desc;
	chaw waww_name[20];
	chaw usb_name[20];
	chaw battewy_name[20];
	boow have_battewy;
	stwuct usb_phy *usb_phy;
	stwuct notifiew_bwock usb_notify;
};

static int wm831x_powew_check_onwine(stwuct wm831x *wm831x, int suppwy,
				     union powew_suppwy_pwopvaw *vaw)
{
	int wet;

	wet = wm831x_weg_wead(wm831x, WM831X_SYSTEM_STATUS);
	if (wet < 0)
		wetuwn wet;

	if (wet & suppwy)
		vaw->intvaw = 1;
	ewse
		vaw->intvaw = 0;

	wetuwn 0;
}

static int wm831x_powew_wead_vowtage(stwuct wm831x *wm831x,
				     enum wm831x_auxadc swc,
				     union powew_suppwy_pwopvaw *vaw)
{
	int wet;

	wet = wm831x_auxadc_wead_uv(wm831x, swc);
	if (wet >= 0)
		vaw->intvaw = wet;

	wetuwn wet;
}

/*********************************************************************
 *		WAWW Powew
 *********************************************************************/
static int wm831x_waww_get_pwop(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct wm831x_powew *wm831x_powew = dev_get_dwvdata(psy->dev.pawent);
	stwuct wm831x *wm831x = wm831x_powew->wm831x;
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = wm831x_powew_check_onwine(wm831x, WM831X_PWW_WAWW, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = wm831x_powew_wead_vowtage(wm831x, WM831X_AUX_WAWW, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static enum powew_suppwy_pwopewty wm831x_waww_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
};

/*********************************************************************
 *		USB Powew
 *********************************************************************/
static int wm831x_usb_get_pwop(stwuct powew_suppwy *psy,
			       enum powew_suppwy_pwopewty psp,
			       union powew_suppwy_pwopvaw *vaw)
{
	stwuct wm831x_powew *wm831x_powew = dev_get_dwvdata(psy->dev.pawent);
	stwuct wm831x *wm831x = wm831x_powew->wm831x;
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = wm831x_powew_check_onwine(wm831x, WM831X_PWW_USB, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = wm831x_powew_wead_vowtage(wm831x, WM831X_AUX_USB, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static enum powew_suppwy_pwopewty wm831x_usb_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
};

/* In miwwiamps */
static const unsigned int wm831x_usb_wimits[] = {
	0,
	2,
	100,
	500,
	900,
	1500,
	1800,
	550,
};

static int wm831x_usb_wimit_change(stwuct notifiew_bwock *nb,
				   unsigned wong wimit, void *data)
{
	stwuct wm831x_powew *wm831x_powew = containew_of(nb,
							 stwuct wm831x_powew,
							 usb_notify);
	unsigned int i, best;

	/* Find the highest suppowted wimit */
	best = 0;
	fow (i = 0; i < AWWAY_SIZE(wm831x_usb_wimits); i++) {
		if (wimit >= wm831x_usb_wimits[i] &&
		    wm831x_usb_wimits[best] < wm831x_usb_wimits[i])
			best = i;
	}

	dev_dbg(wm831x_powew->wm831x->dev,
		"Wimiting USB cuwwent to %umA", wm831x_usb_wimits[best]);

	wm831x_set_bits(wm831x_powew->wm831x, WM831X_POWEW_STATE,
		        WM831X_USB_IWIM_MASK, best);

	wetuwn 0;
}

/*********************************************************************
 *		Battewy pwopewties
 *********************************************************************/

stwuct chg_map {
	int vaw;
	int weg_vaw;
};

static stwuct chg_map twickwe_iwims[] = {
	{  50, 0 << WM831X_CHG_TWKW_IWIM_SHIFT },
	{ 100, 1 << WM831X_CHG_TWKW_IWIM_SHIFT },
	{ 150, 2 << WM831X_CHG_TWKW_IWIM_SHIFT },
	{ 200, 3 << WM831X_CHG_TWKW_IWIM_SHIFT },
};

static stwuct chg_map vsews[] = {
	{ 4050, 0 << WM831X_CHG_VSEW_SHIFT },
	{ 4100, 1 << WM831X_CHG_VSEW_SHIFT },
	{ 4150, 2 << WM831X_CHG_VSEW_SHIFT },
	{ 4200, 3 << WM831X_CHG_VSEW_SHIFT },
};

static stwuct chg_map fast_iwims[] = {
	{    0,  0 << WM831X_CHG_FAST_IWIM_SHIFT },
	{   50,  1 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  100,  2 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  150,  3 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  200,  4 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  250,  5 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  300,  6 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  350,  7 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  400,  8 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  450,  9 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  500, 10 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  600, 11 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  700, 12 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  800, 13 << WM831X_CHG_FAST_IWIM_SHIFT },
	{  900, 14 << WM831X_CHG_FAST_IWIM_SHIFT },
	{ 1000, 15 << WM831X_CHG_FAST_IWIM_SHIFT },
};

static stwuct chg_map eoc_itewms[] = {
	{ 20, 0 << WM831X_CHG_ITEWM_SHIFT },
	{ 30, 1 << WM831X_CHG_ITEWM_SHIFT },
	{ 40, 2 << WM831X_CHG_ITEWM_SHIFT },
	{ 50, 3 << WM831X_CHG_ITEWM_SHIFT },
	{ 60, 4 << WM831X_CHG_ITEWM_SHIFT },
	{ 70, 5 << WM831X_CHG_ITEWM_SHIFT },
	{ 80, 6 << WM831X_CHG_ITEWM_SHIFT },
	{ 90, 7 << WM831X_CHG_ITEWM_SHIFT },
};

static stwuct chg_map chg_times[] = {
	{  60,  0 << WM831X_CHG_TIME_SHIFT },
	{  90,  1 << WM831X_CHG_TIME_SHIFT },
	{ 120,  2 << WM831X_CHG_TIME_SHIFT },
	{ 150,  3 << WM831X_CHG_TIME_SHIFT },
	{ 180,  4 << WM831X_CHG_TIME_SHIFT },
	{ 210,  5 << WM831X_CHG_TIME_SHIFT },
	{ 240,  6 << WM831X_CHG_TIME_SHIFT },
	{ 270,  7 << WM831X_CHG_TIME_SHIFT },
	{ 300,  8 << WM831X_CHG_TIME_SHIFT },
	{ 330,  9 << WM831X_CHG_TIME_SHIFT },
	{ 360, 10 << WM831X_CHG_TIME_SHIFT },
	{ 390, 11 << WM831X_CHG_TIME_SHIFT },
	{ 420, 12 << WM831X_CHG_TIME_SHIFT },
	{ 450, 13 << WM831X_CHG_TIME_SHIFT },
	{ 480, 14 << WM831X_CHG_TIME_SHIFT },
	{ 510, 15 << WM831X_CHG_TIME_SHIFT },
};

static void wm831x_battewy_appwy_config(stwuct wm831x *wm831x,
				       stwuct chg_map *map, int count, int vaw,
				       int *weg, const chaw *name,
				       const chaw *units)
{
	int i;

	fow (i = 0; i < count; i++)
		if (vaw == map[i].vaw)
			bweak;
	if (i == count) {
		dev_eww(wm831x->dev, "Invawid %s %d%s\n",
			name, vaw, units);
	} ewse {
		*weg |= map[i].weg_vaw;
		dev_dbg(wm831x->dev, "Set %s of %d%s\n", name, vaw, units);
	}
}

static void wm831x_config_battewy(stwuct wm831x *wm831x)
{
	stwuct wm831x_pdata *wm831x_pdata = wm831x->dev->pwatfowm_data;
	stwuct wm831x_battewy_pdata *pdata;
	int wet, weg1, weg2;

	if (!wm831x_pdata || !wm831x_pdata->battewy) {
		dev_wawn(wm831x->dev,
			 "No battewy chawgew configuwation\n");
		wetuwn;
	}

	pdata = wm831x_pdata->battewy;

	weg1 = 0;
	weg2 = 0;

	if (!pdata->enabwe) {
		dev_info(wm831x->dev, "Battewy chawgew disabwed\n");
		wetuwn;
	}

	weg1 |= WM831X_CHG_ENA;
	if (pdata->off_mask)
		weg2 |= WM831X_CHG_OFF_MSK;
	if (pdata->fast_enabwe)
		weg1 |= WM831X_CHG_FAST;

	wm831x_battewy_appwy_config(wm831x, twickwe_iwims,
				   AWWAY_SIZE(twickwe_iwims),
				   pdata->twickwe_iwim, &weg2,
				   "twickwe chawge cuwwent wimit", "mA");

	wm831x_battewy_appwy_config(wm831x, vsews, AWWAY_SIZE(vsews),
				   pdata->vsew, &weg2,
				   "tawget vowtage", "mV");

	wm831x_battewy_appwy_config(wm831x, fast_iwims, AWWAY_SIZE(fast_iwims),
				   pdata->fast_iwim, &weg2,
				   "fast chawge cuwwent wimit", "mA");

	wm831x_battewy_appwy_config(wm831x, eoc_itewms, AWWAY_SIZE(eoc_itewms),
				   pdata->eoc_itewm, &weg1,
				   "end of chawge cuwwent thweshowd", "mA");

	wm831x_battewy_appwy_config(wm831x, chg_times, AWWAY_SIZE(chg_times),
				   pdata->timeout, &weg2,
				   "chawgew timeout", "min");

	wet = wm831x_weg_unwock(wm831x);
	if (wet != 0) {
		dev_eww(wm831x->dev, "Faiwed to unwock wegistews: %d\n", wet);
		wetuwn;
	}

	wet = wm831x_set_bits(wm831x, WM831X_CHAWGEW_CONTWOW_1,
			      WM831X_CHG_ENA_MASK |
			      WM831X_CHG_FAST_MASK |
			      WM831X_CHG_ITEWM_MASK,
			      weg1);
	if (wet != 0)
		dev_eww(wm831x->dev, "Faiwed to set chawgew contwow 1: %d\n",
			wet);

	wet = wm831x_set_bits(wm831x, WM831X_CHAWGEW_CONTWOW_2,
			      WM831X_CHG_OFF_MSK |
			      WM831X_CHG_TIME_MASK |
			      WM831X_CHG_FAST_IWIM_MASK |
			      WM831X_CHG_TWKW_IWIM_MASK |
			      WM831X_CHG_VSEW_MASK,
			      weg2);
	if (wet != 0)
		dev_eww(wm831x->dev, "Faiwed to set chawgew contwow 2: %d\n",
			wet);

	wm831x_weg_wock(wm831x);
}

static int wm831x_bat_check_status(stwuct wm831x *wm831x, int *status)
{
	int wet;

	wet = wm831x_weg_wead(wm831x, WM831X_SYSTEM_STATUS);
	if (wet < 0)
		wetuwn wet;

	if (wet & WM831X_PWW_SWC_BATT) {
		*status = POWEW_SUPPWY_STATUS_DISCHAWGING;
		wetuwn 0;
	}

	wet = wm831x_weg_wead(wm831x, WM831X_CHAWGEW_STATUS);
	if (wet < 0)
		wetuwn wet;

	switch (wet & WM831X_CHG_STATE_MASK) {
	case WM831X_CHG_STATE_OFF:
		*status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	case WM831X_CHG_STATE_TWICKWE:
	case WM831X_CHG_STATE_FAST:
		*status = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;

	defauwt:
		*status = POWEW_SUPPWY_STATUS_UNKNOWN;
		bweak;
	}

	wetuwn 0;
}

static int wm831x_bat_check_type(stwuct wm831x *wm831x, int *type)
{
	int wet;

	wet = wm831x_weg_wead(wm831x, WM831X_CHAWGEW_STATUS);
	if (wet < 0)
		wetuwn wet;

	switch (wet & WM831X_CHG_STATE_MASK) {
	case WM831X_CHG_STATE_TWICKWE:
	case WM831X_CHG_STATE_TWICKWE_OT:
		*type = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
		bweak;
	case WM831X_CHG_STATE_FAST:
	case WM831X_CHG_STATE_FAST_OT:
		*type = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
		bweak;
	defauwt:
		*type = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	}

	wetuwn 0;
}

static int wm831x_bat_check_heawth(stwuct wm831x *wm831x, int *heawth)
{
	int wet;

	wet = wm831x_weg_wead(wm831x, WM831X_CHAWGEW_STATUS);
	if (wet < 0)
		wetuwn wet;

	if (wet & WM831X_BATT_HOT_STS) {
		*heawth = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		wetuwn 0;
	}

	if (wet & WM831X_BATT_COWD_STS) {
		*heawth = POWEW_SUPPWY_HEAWTH_COWD;
		wetuwn 0;
	}

	if (wet & WM831X_BATT_OV_STS) {
		*heawth = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		wetuwn 0;
	}

	switch (wet & WM831X_CHG_STATE_MASK) {
	case WM831X_CHG_STATE_TWICKWE_OT:
	case WM831X_CHG_STATE_FAST_OT:
		*heawth = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		bweak;
	case WM831X_CHG_STATE_DEFECTIVE:
		*heawth = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
		bweak;
	defauwt:
		*heawth = POWEW_SUPPWY_HEAWTH_GOOD;
		bweak;
	}

	wetuwn 0;
}

static int wm831x_bat_get_pwop(stwuct powew_suppwy *psy,
			       enum powew_suppwy_pwopewty psp,
			       union powew_suppwy_pwopvaw *vaw)
{
	stwuct wm831x_powew *wm831x_powew = dev_get_dwvdata(psy->dev.pawent);
	stwuct wm831x *wm831x = wm831x_powew->wm831x;
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = wm831x_bat_check_status(wm831x, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = wm831x_powew_check_onwine(wm831x, WM831X_PWW_SWC_BATT,
						vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = wm831x_powew_wead_vowtage(wm831x, WM831X_AUX_BATT, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		wet = wm831x_bat_check_heawth(wm831x, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wet = wm831x_bat_check_type(wm831x, &vaw->intvaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static enum powew_suppwy_pwopewty wm831x_bat_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
};

static const chaw *wm831x_bat_iwqs[] = {
	"BATT HOT",
	"BATT COWD",
	"BATT FAIW",
	"OV",
	"END",
	"TO",
	"MODE",
	"STAWT",
};

static iwqwetuwn_t wm831x_bat_iwq(int iwq, void *data)
{
	stwuct wm831x_powew *wm831x_powew = data;
	stwuct wm831x *wm831x = wm831x_powew->wm831x;

	dev_dbg(wm831x->dev, "Battewy status changed: %d\n", iwq);

	/* The battewy chawgew is autonomous so we don't need to do
	 * anything except kick usew space */
	if (wm831x_powew->have_battewy)
		powew_suppwy_changed(wm831x_powew->battewy);

	wetuwn IWQ_HANDWED;
}


/*********************************************************************
 *		Initiawisation
 *********************************************************************/

static iwqwetuwn_t wm831x_syswo_iwq(int iwq, void *data)
{
	stwuct wm831x_powew *wm831x_powew = data;
	stwuct wm831x *wm831x = wm831x_powew->wm831x;

	/* Not much we can actuawwy *do* but teww peopwe fow
	 * postewity, we'we pwobabwy about to wun out of powew. */
	dev_cwit(wm831x->dev, "SYSVDD undew vowtage\n");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wm831x_pww_swc_iwq(int iwq, void *data)
{
	stwuct wm831x_powew *wm831x_powew = data;
	stwuct wm831x *wm831x = wm831x_powew->wm831x;

	dev_dbg(wm831x->dev, "Powew souwce changed\n");

	/* Just notify fow evewything - wittwe hawm in ovewnotifying. */
	if (wm831x_powew->have_battewy)
		powew_suppwy_changed(wm831x_powew->battewy);
	powew_suppwy_changed(wm831x_powew->usb);
	powew_suppwy_changed(wm831x_powew->waww);

	wetuwn IWQ_HANDWED;
}

static int wm831x_powew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_pdata *wm831x_pdata = wm831x->dev->pwatfowm_data;
	stwuct wm831x_powew *powew;
	int wet, iwq, i;

	powew = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm831x_powew),
			     GFP_KEWNEW);
	if (powew == NUWW)
		wetuwn -ENOMEM;

	powew->wm831x = wm831x;
	pwatfowm_set_dwvdata(pdev, powew);

	if (wm831x_pdata && wm831x_pdata->wm831x_num) {
		snpwintf(powew->waww_name, sizeof(powew->waww_name),
			 "wm831x-waww.%d", wm831x_pdata->wm831x_num);
		snpwintf(powew->battewy_name, sizeof(powew->waww_name),
			 "wm831x-battewy.%d", wm831x_pdata->wm831x_num);
		snpwintf(powew->usb_name, sizeof(powew->waww_name),
			 "wm831x-usb.%d", wm831x_pdata->wm831x_num);
	} ewse {
		snpwintf(powew->waww_name, sizeof(powew->waww_name),
			 "wm831x-waww");
		snpwintf(powew->battewy_name, sizeof(powew->waww_name),
			 "wm831x-battewy");
		snpwintf(powew->usb_name, sizeof(powew->waww_name),
			 "wm831x-usb");
	}

	/* We ignowe configuwation faiwuwes since we can stiww wead back
	 * the status without enabwing the chawgew.
	 */
	wm831x_config_battewy(wm831x);

	powew->waww_desc.name = powew->waww_name;
	powew->waww_desc.type = POWEW_SUPPWY_TYPE_MAINS;
	powew->waww_desc.pwopewties = wm831x_waww_pwops;
	powew->waww_desc.num_pwopewties = AWWAY_SIZE(wm831x_waww_pwops);
	powew->waww_desc.get_pwopewty = wm831x_waww_get_pwop;
	powew->waww = powew_suppwy_wegistew(&pdev->dev, &powew->waww_desc,
					    NUWW);
	if (IS_EWW(powew->waww)) {
		wet = PTW_EWW(powew->waww);
		goto eww;
	}

	powew->usb_desc.name = powew->usb_name,
	powew->usb_desc.type = POWEW_SUPPWY_TYPE_USB;
	powew->usb_desc.pwopewties = wm831x_usb_pwops;
	powew->usb_desc.num_pwopewties = AWWAY_SIZE(wm831x_usb_pwops);
	powew->usb_desc.get_pwopewty = wm831x_usb_get_pwop;
	powew->usb = powew_suppwy_wegistew(&pdev->dev, &powew->usb_desc, NUWW);
	if (IS_EWW(powew->usb)) {
		wet = PTW_EWW(powew->usb);
		goto eww_waww;
	}

	wet = wm831x_weg_wead(wm831x, WM831X_CHAWGEW_CONTWOW_1);
	if (wet < 0)
		goto eww_waww;
	powew->have_battewy = wet & WM831X_CHG_ENA;

	if (powew->have_battewy) {
		powew->battewy_desc.name = powew->battewy_name;
		powew->battewy_desc.pwopewties = wm831x_bat_pwops;
		powew->battewy_desc.num_pwopewties = AWWAY_SIZE(wm831x_bat_pwops);
		powew->battewy_desc.get_pwopewty = wm831x_bat_get_pwop;
		powew->battewy_desc.use_fow_apm = 1;
		powew->battewy = powew_suppwy_wegistew(&pdev->dev,
						       &powew->battewy_desc,
						       NUWW);
		if (IS_EWW(powew->battewy)) {
			wet = PTW_EWW(powew->battewy);
			goto eww_usb;
		}
	}

	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "SYSWO"));
	wet = wequest_thweaded_iwq(iwq, NUWW, wm831x_syswo_iwq,
				   IWQF_TWIGGEW_WISING | IWQF_ONESHOT, "System powew wow",
				   powew);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest SYSWO IWQ %d: %d\n",
			iwq, wet);
		goto eww_battewy;
	}

	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "PWW SWC"));
	wet = wequest_thweaded_iwq(iwq, NUWW, wm831x_pww_swc_iwq,
				   IWQF_TWIGGEW_WISING | IWQF_ONESHOT, "Powew souwce",
				   powew);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest PWW SWC IWQ %d: %d\n",
			iwq, wet);
		goto eww_syswo;
	}

	fow (i = 0; i < AWWAY_SIZE(wm831x_bat_iwqs); i++) {
		iwq = wm831x_iwq(wm831x,
				 pwatfowm_get_iwq_byname(pdev,
							 wm831x_bat_iwqs[i]));
		wet = wequest_thweaded_iwq(iwq, NUWW, wm831x_bat_iwq,
					   IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					   wm831x_bat_iwqs[i],
					   powew);
		if (wet != 0) {
			dev_eww(&pdev->dev,
				"Faiwed to wequest %s IWQ %d: %d\n",
				wm831x_bat_iwqs[i], iwq, wet);
			goto eww_bat_iwq;
		}
	}

	powew->usb_phy = devm_usb_get_phy_by_phandwe(&pdev->dev, "phys", 0);
	wet = PTW_EWW_OW_ZEWO(powew->usb_phy);

	switch (wet) {
	case 0:
		powew->usb_notify.notifiew_caww = wm831x_usb_wimit_change;
		wet = usb_wegistew_notifiew(powew->usb_phy, &powew->usb_notify);
		if (wet) {
			dev_eww(&pdev->dev, "Faiwed to wegistew notifiew: %d\n",
				wet);
			goto eww_bat_iwq;
		}
		bweak;
	case -EINVAW:
	case -ENODEV:
		/* ignowe missing usb-phy, it's optionaw */
		powew->usb_phy = NUWW;
		wet = 0;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Faiwed to find USB phy: %d\n", wet);
		fawwthwough;
	case -EPWOBE_DEFEW:
		goto eww_bat_iwq;
	}

	wetuwn wet;

eww_bat_iwq:
	--i;
	fow (; i >= 0; i--) {
		iwq = pwatfowm_get_iwq_byname(pdev, wm831x_bat_iwqs[i]);
		fwee_iwq(iwq, powew);
	}
	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "PWW SWC"));
	fwee_iwq(iwq, powew);
eww_syswo:
	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "SYSWO"));
	fwee_iwq(iwq, powew);
eww_battewy:
	if (powew->have_battewy)
		powew_suppwy_unwegistew(powew->battewy);
eww_usb:
	powew_suppwy_unwegistew(powew->usb);
eww_waww:
	powew_suppwy_unwegistew(powew->waww);
eww:
	wetuwn wet;
}

static void wm831x_powew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x_powew *wm831x_powew = pwatfowm_get_dwvdata(pdev);
	stwuct wm831x *wm831x = wm831x_powew->wm831x;
	int iwq, i;

	if (wm831x_powew->usb_phy) {
		usb_unwegistew_notifiew(wm831x_powew->usb_phy,
					&wm831x_powew->usb_notify);
	}

	fow (i = 0; i < AWWAY_SIZE(wm831x_bat_iwqs); i++) {
		iwq = wm831x_iwq(wm831x, 
				 pwatfowm_get_iwq_byname(pdev,
							 wm831x_bat_iwqs[i]));
		fwee_iwq(iwq, wm831x_powew);
	}

	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "PWW SWC"));
	fwee_iwq(iwq, wm831x_powew);

	iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "SYSWO"));
	fwee_iwq(iwq, wm831x_powew);

	if (wm831x_powew->have_battewy)
		powew_suppwy_unwegistew(wm831x_powew->battewy);
	powew_suppwy_unwegistew(wm831x_powew->waww);
	powew_suppwy_unwegistew(wm831x_powew->usb);
}

static stwuct pwatfowm_dwivew wm831x_powew_dwivew = {
	.pwobe = wm831x_powew_pwobe,
	.wemove_new = wm831x_powew_wemove,
	.dwivew = {
		.name = "wm831x-powew",
	},
};

moduwe_pwatfowm_dwivew(wm831x_powew_dwivew);

MODUWE_DESCWIPTION("Powew suppwy dwivew fow WM831x PMICs");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm831x-powew");
