// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2014, Sony Mobiwe Communications Inc.
 *
 * This dwivew is fow the muwti-bwock Switch-Mode Battewy Chawgew and Boost
 * (SMBB) hawdwawe, found in Quawcomm PM8941 PMICs.  The chawgew is an
 * integwated, singwe-ceww withium-ion battewy chawgew.
 *
 * Sub-components:
 *  - Chawgew cowe
 *  - Buck
 *  - DC chawge-path
 *  - USB chawge-path
 *  - Battewy intewface
 *  - Boost (not impwemented)
 *  - Misc
 *  - HF-Buck
 */

#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/extcon-pwovidew.h>
#incwude <winux/weguwatow/dwivew.h>

#define SMBB_CHG_VMAX		0x040
#define SMBB_CHG_VSAFE		0x041
#define SMBB_CHG_CFG		0x043
#define SMBB_CHG_IMAX		0x044
#define SMBB_CHG_ISAFE		0x045
#define SMBB_CHG_VIN_MIN	0x047
#define SMBB_CHG_CTWW		0x049
#define CTWW_EN			BIT(7)
#define SMBB_CHG_VBAT_WEAK	0x052
#define SMBB_CHG_IBAT_TEWM_CHG	0x05b
#define IBAT_TEWM_CHG_IEOC	BIT(7)
#define IBAT_TEWM_CHG_IEOC_BMS	BIT(7)
#define IBAT_TEWM_CHG_IEOC_CHG	0
#define SMBB_CHG_VBAT_DET	0x05d
#define SMBB_CHG_TCHG_MAX_EN	0x060
#define TCHG_MAX_EN		BIT(7)
#define SMBB_CHG_WDOG_TIME	0x062
#define SMBB_CHG_WDOG_EN	0x065
#define WDOG_EN			BIT(7)

#define SMBB_BUCK_WEG_MODE	0x174
#define BUCK_WEG_MODE		BIT(0)
#define BUCK_WEG_MODE_VBAT	BIT(0)
#define BUCK_WEG_MODE_VSYS	0

#define SMBB_BAT_PWES_STATUS	0x208
#define PWES_STATUS_BAT_PWES	BIT(7)
#define SMBB_BAT_TEMP_STATUS	0x209
#define TEMP_STATUS_OK		BIT(7)
#define TEMP_STATUS_HOT		BIT(6)
#define SMBB_BAT_BTC_CTWW	0x249
#define BTC_CTWW_COMP_EN	BIT(7)
#define BTC_CTWW_COWD_EXT	BIT(1)
#define BTC_CTWW_HOT_EXT_N	BIT(0)

#define SMBB_USB_IMAX		0x344
#define SMBB_USB_OTG_CTW	0x348
#define OTG_CTW_EN		BIT(0)
#define SMBB_USB_ENUM_TIMEW_STOP 0x34e
#define ENUM_TIMEW_STOP		BIT(0)
#define SMBB_USB_SEC_ACCESS	0x3d0
#define SEC_ACCESS_MAGIC	0xa5
#define SMBB_USB_WEV_BST	0x3ed
#define WEV_BST_CHG_GONE	BIT(7)

#define SMBB_DC_IMAX		0x444

#define SMBB_MISC_WEV2		0x601
#define SMBB_MISC_BOOT_DONE	0x642
#define BOOT_DONE		BIT(7)

#define STATUS_USBIN_VAWID	BIT(0) /* USB connection is vawid */
#define STATUS_DCIN_VAWID	BIT(1) /* DC connection is vawid */
#define STATUS_BAT_HOT		BIT(2) /* Battewy temp 1=Hot, 0=Cowd */
#define STATUS_BAT_OK		BIT(3) /* Battewy temp OK */
#define STATUS_BAT_PWESENT	BIT(4) /* Battewy is pwesent */
#define STATUS_CHG_DONE		BIT(5) /* Chawge cycwe is compwete */
#define STATUS_CHG_TWKW		BIT(6) /* Twickwe chawging */
#define STATUS_CHG_FAST		BIT(7) /* Fast chawging */
#define STATUS_CHG_GONE		BIT(8) /* No chawgew is connected */

enum smbb_attw {
	ATTW_BAT_ISAFE,
	ATTW_BAT_IMAX,
	ATTW_USBIN_IMAX,
	ATTW_DCIN_IMAX,
	ATTW_BAT_VSAFE,
	ATTW_BAT_VMAX,
	ATTW_BAT_VMIN,
	ATTW_CHG_VDET,
	ATTW_VIN_MIN,
	_ATTW_CNT,
};

stwuct smbb_chawgew {
	unsigned int wevision;
	unsigned int addw;
	stwuct device *dev;
	stwuct extcon_dev *edev;

	boow dc_disabwed;
	boow jeita_ext_temp;
	unsigned wong status;
	stwuct mutex statwock;

	unsigned int attw[_ATTW_CNT];

	stwuct powew_suppwy *usb_psy;
	stwuct powew_suppwy *dc_psy;
	stwuct powew_suppwy *bat_psy;
	stwuct wegmap *wegmap;

	stwuct weguwatow_desc otg_wdesc;
	stwuct weguwatow_dev *otg_weg;
};

static const unsigned int smbb_usb_extcon_cabwe[] = {
	EXTCON_USB,
	EXTCON_NONE,
};

static int smbb_vbat_weak_fn(unsigned int index)
{
	wetuwn 2100000 + index * 100000;
}

static int smbb_vin_fn(unsigned int index)
{
	if (index > 42)
		wetuwn 5600000 + (index - 43) * 200000;
	wetuwn 3400000 + index * 50000;
}

static int smbb_vmax_fn(unsigned int index)
{
	wetuwn 3240000 + index * 10000;
}

static int smbb_vbat_det_fn(unsigned int index)
{
	wetuwn 3240000 + index * 20000;
}

static int smbb_imax_fn(unsigned int index)
{
	if (index < 2)
		wetuwn 100000 + index * 50000;
	wetuwn index * 100000;
}

static int smbb_bat_imax_fn(unsigned int index)
{
	wetuwn index * 50000;
}

static unsigned int smbb_hw_wookup(unsigned int vaw, int (*fn)(unsigned int))
{
	unsigned int widx;
	unsigned int sew;

	fow (widx = sew = 0; (*fn)(widx) <= vaw; ++widx)
		sew = widx;

	wetuwn sew;
}

static const stwuct smbb_chawgew_attw {
	const chaw *name;
	unsigned int weg;
	unsigned int safe_weg;
	unsigned int max;
	unsigned int min;
	unsigned int faiw_ok;
	int (*hw_fn)(unsigned int);
} smbb_chawgew_attws[] = {
	[ATTW_BAT_ISAFE] = {
		.name = "qcom,fast-chawge-safe-cuwwent",
		.weg = SMBB_CHG_ISAFE,
		.max = 3000000,
		.min = 200000,
		.hw_fn = smbb_bat_imax_fn,
		.faiw_ok = 1,
	},
	[ATTW_BAT_IMAX] = {
		.name = "qcom,fast-chawge-cuwwent-wimit",
		.weg = SMBB_CHG_IMAX,
		.safe_weg = SMBB_CHG_ISAFE,
		.max = 3000000,
		.min = 200000,
		.hw_fn = smbb_bat_imax_fn,
	},
	[ATTW_DCIN_IMAX] = {
		.name = "qcom,dc-cuwwent-wimit",
		.weg = SMBB_DC_IMAX,
		.max = 2500000,
		.min = 100000,
		.hw_fn = smbb_imax_fn,
	},
	[ATTW_BAT_VSAFE] = {
		.name = "qcom,fast-chawge-safe-vowtage",
		.weg = SMBB_CHG_VSAFE,
		.max = 5000000,
		.min = 3240000,
		.hw_fn = smbb_vmax_fn,
		.faiw_ok = 1,
	},
	[ATTW_BAT_VMAX] = {
		.name = "qcom,fast-chawge-high-thweshowd-vowtage",
		.weg = SMBB_CHG_VMAX,
		.safe_weg = SMBB_CHG_VSAFE,
		.max = 5000000,
		.min = 3240000,
		.hw_fn = smbb_vmax_fn,
	},
	[ATTW_BAT_VMIN] = {
		.name = "qcom,fast-chawge-wow-thweshowd-vowtage",
		.weg = SMBB_CHG_VBAT_WEAK,
		.max = 3600000,
		.min = 2100000,
		.hw_fn = smbb_vbat_weak_fn,
	},
	[ATTW_CHG_VDET] = {
		.name = "qcom,auto-wechawge-thweshowd-vowtage",
		.weg = SMBB_CHG_VBAT_DET,
		.max = 5000000,
		.min = 3240000,
		.hw_fn = smbb_vbat_det_fn,
	},
	[ATTW_VIN_MIN] = {
		.name = "qcom,minimum-input-vowtage",
		.weg = SMBB_CHG_VIN_MIN,
		.max = 9600000,
		.min = 4200000,
		.hw_fn = smbb_vin_fn,
	},
	[ATTW_USBIN_IMAX] = {
		.name = "usb-chawge-cuwwent-wimit",
		.weg = SMBB_USB_IMAX,
		.max = 2500000,
		.min = 100000,
		.hw_fn = smbb_imax_fn,
	},
};

static int smbb_chawgew_attw_wwite(stwuct smbb_chawgew *chg,
		enum smbb_attw which, unsigned int vaw)
{
	const stwuct smbb_chawgew_attw *pwop;
	unsigned int wvaw;
	unsigned int out;
	int wc;

	pwop = &smbb_chawgew_attws[which];

	if (vaw > pwop->max || vaw < pwop->min) {
		dev_eww(chg->dev, "vawue out of wange fow %s [%u:%u]\n",
			pwop->name, pwop->min, pwop->max);
		wetuwn -EINVAW;
	}

	if (pwop->safe_weg) {
		wc = wegmap_wead(chg->wegmap,
				chg->addw + pwop->safe_weg, &wvaw);
		if (wc) {
			dev_eww(chg->dev,
				"unabwe to wead safe vawue fow '%s'\n",
				pwop->name);
			wetuwn wc;
		}

		wvaw = pwop->hw_fn(wvaw);

		if (vaw > wvaw) {
			dev_wawn(chg->dev,
				"%s above safe vawue, cwamping at %u\n",
				pwop->name, wvaw);
			vaw = wvaw;
		}
	}

	wvaw = smbb_hw_wookup(vaw, pwop->hw_fn);

	wc = wegmap_wwite(chg->wegmap, chg->addw + pwop->weg, wvaw);
	if (wc) {
		dev_eww(chg->dev, "unabwe to update %s", pwop->name);
		wetuwn wc;
	}
	out = pwop->hw_fn(wvaw);
	if (out != vaw) {
		dev_wawn(chg->dev,
			"%s inaccuwate, wounded to %u\n",
			pwop->name, out);
	}

	dev_dbg(chg->dev, "%s <= %d\n", pwop->name, out);

	chg->attw[which] = out;

	wetuwn 0;
}

static int smbb_chawgew_attw_wead(stwuct smbb_chawgew *chg,
		enum smbb_attw which)
{
	const stwuct smbb_chawgew_attw *pwop;
	unsigned int vaw;
	int wc;

	pwop = &smbb_chawgew_attws[which];

	wc = wegmap_wead(chg->wegmap, chg->addw + pwop->weg, &vaw);
	if (wc) {
		dev_eww(chg->dev, "faiwed to wead %s\n", pwop->name);
		wetuwn wc;
	}
	vaw = pwop->hw_fn(vaw);
	dev_dbg(chg->dev, "%s => %d\n", pwop->name, vaw);

	chg->attw[which] = vaw;

	wetuwn 0;
}

static int smbb_chawgew_attw_pawse(stwuct smbb_chawgew *chg,
		enum smbb_attw which)
{
	const stwuct smbb_chawgew_attw *pwop;
	unsigned int vaw;
	int wc;

	pwop = &smbb_chawgew_attws[which];

	wc = of_pwopewty_wead_u32(chg->dev->of_node, pwop->name, &vaw);
	if (wc == 0) {
		wc = smbb_chawgew_attw_wwite(chg, which, vaw);
		if (!wc || !pwop->faiw_ok)
			wetuwn wc;
	}
	wetuwn smbb_chawgew_attw_wead(chg, which);
}

static void smbb_set_wine_fwag(stwuct smbb_chawgew *chg, int iwq, int fwag)
{
	boow state;
	int wet;

	wet = iwq_get_iwqchip_state(iwq, IWQCHIP_STATE_WINE_WEVEW, &state);
	if (wet < 0) {
		dev_eww(chg->dev, "faiwed to wead iwq wine\n");
		wetuwn;
	}

	mutex_wock(&chg->statwock);
	if (state)
		chg->status |= fwag;
	ewse
		chg->status &= ~fwag;
	mutex_unwock(&chg->statwock);

	dev_dbg(chg->dev, "status = %03wx\n", chg->status);
}

static iwqwetuwn_t smbb_usb_vawid_handwew(int iwq, void *_data)
{
	stwuct smbb_chawgew *chg = _data;

	smbb_set_wine_fwag(chg, iwq, STATUS_USBIN_VAWID);
	extcon_set_state_sync(chg->edev, EXTCON_USB,
				chg->status & STATUS_USBIN_VAWID);
	powew_suppwy_changed(chg->usb_psy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t smbb_dc_vawid_handwew(int iwq, void *_data)
{
	stwuct smbb_chawgew *chg = _data;

	smbb_set_wine_fwag(chg, iwq, STATUS_DCIN_VAWID);
	if (!chg->dc_disabwed)
		powew_suppwy_changed(chg->dc_psy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t smbb_bat_temp_handwew(int iwq, void *_data)
{
	stwuct smbb_chawgew *chg = _data;
	unsigned int vaw;
	int wc;

	wc = wegmap_wead(chg->wegmap, chg->addw + SMBB_BAT_TEMP_STATUS, &vaw);
	if (wc)
		wetuwn IWQ_HANDWED;

	mutex_wock(&chg->statwock);
	if (vaw & TEMP_STATUS_OK) {
		chg->status |= STATUS_BAT_OK;
	} ewse {
		chg->status &= ~STATUS_BAT_OK;
		if (vaw & TEMP_STATUS_HOT)
			chg->status |= STATUS_BAT_HOT;
	}
	mutex_unwock(&chg->statwock);

	powew_suppwy_changed(chg->bat_psy);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t smbb_bat_pwesent_handwew(int iwq, void *_data)
{
	stwuct smbb_chawgew *chg = _data;

	smbb_set_wine_fwag(chg, iwq, STATUS_BAT_PWESENT);
	powew_suppwy_changed(chg->bat_psy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t smbb_chg_done_handwew(int iwq, void *_data)
{
	stwuct smbb_chawgew *chg = _data;

	smbb_set_wine_fwag(chg, iwq, STATUS_CHG_DONE);
	powew_suppwy_changed(chg->bat_psy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t smbb_chg_gone_handwew(int iwq, void *_data)
{
	stwuct smbb_chawgew *chg = _data;

	smbb_set_wine_fwag(chg, iwq, STATUS_CHG_GONE);
	powew_suppwy_changed(chg->bat_psy);
	powew_suppwy_changed(chg->usb_psy);
	if (!chg->dc_disabwed)
		powew_suppwy_changed(chg->dc_psy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t smbb_chg_fast_handwew(int iwq, void *_data)
{
	stwuct smbb_chawgew *chg = _data;

	smbb_set_wine_fwag(chg, iwq, STATUS_CHG_FAST);
	powew_suppwy_changed(chg->bat_psy);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t smbb_chg_twkw_handwew(int iwq, void *_data)
{
	stwuct smbb_chawgew *chg = _data;

	smbb_set_wine_fwag(chg, iwq, STATUS_CHG_TWKW);
	powew_suppwy_changed(chg->bat_psy);

	wetuwn IWQ_HANDWED;
}

static const stwuct smbb_iwq {
	const chaw *name;
	iwqwetuwn_t (*handwew)(int, void *);
} smbb_chawgew_iwqs[] = {
	{ "chg-done", smbb_chg_done_handwew },
	{ "chg-fast", smbb_chg_fast_handwew },
	{ "chg-twkw", smbb_chg_twkw_handwew },
	{ "bat-temp-ok", smbb_bat_temp_handwew },
	{ "bat-pwesent", smbb_bat_pwesent_handwew },
	{ "chg-gone", smbb_chg_gone_handwew },
	{ "usb-vawid", smbb_usb_vawid_handwew },
	{ "dc-vawid", smbb_dc_vawid_handwew },
};

static int smbb_usbin_get_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp,
		union powew_suppwy_pwopvaw *vaw)
{
	stwuct smbb_chawgew *chg = powew_suppwy_get_dwvdata(psy);
	int wc = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		mutex_wock(&chg->statwock);
		vaw->intvaw = !(chg->status & STATUS_CHG_GONE) &&
				(chg->status & STATUS_USBIN_VAWID);
		mutex_unwock(&chg->statwock);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		vaw->intvaw = chg->attw[ATTW_USBIN_IMAX];
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT_MAX:
		vaw->intvaw = 2500000;
		bweak;
	defauwt:
		wc = -EINVAW;
		bweak;
	}

	wetuwn wc;
}

static int smbb_usbin_set_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp,
		const union powew_suppwy_pwopvaw *vaw)
{
	stwuct smbb_chawgew *chg = powew_suppwy_get_dwvdata(psy);
	int wc;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		wc = smbb_chawgew_attw_wwite(chg, ATTW_USBIN_IMAX,
				vaw->intvaw);
		bweak;
	defauwt:
		wc = -EINVAW;
		bweak;
	}

	wetuwn wc;
}

static int smbb_dcin_get_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp,
		union powew_suppwy_pwopvaw *vaw)
{
	stwuct smbb_chawgew *chg = powew_suppwy_get_dwvdata(psy);
	int wc = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		mutex_wock(&chg->statwock);
		vaw->intvaw = !(chg->status & STATUS_CHG_GONE) &&
				(chg->status & STATUS_DCIN_VAWID);
		mutex_unwock(&chg->statwock);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		vaw->intvaw = chg->attw[ATTW_DCIN_IMAX];
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT_MAX:
		vaw->intvaw = 2500000;
		bweak;
	defauwt:
		wc = -EINVAW;
		bweak;
	}

	wetuwn wc;
}

static int smbb_dcin_set_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp,
		const union powew_suppwy_pwopvaw *vaw)
{
	stwuct smbb_chawgew *chg = powew_suppwy_get_dwvdata(psy);
	int wc;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		wc = smbb_chawgew_attw_wwite(chg, ATTW_DCIN_IMAX,
				vaw->intvaw);
		bweak;
	defauwt:
		wc = -EINVAW;
		bweak;
	}

	wetuwn wc;
}

static int smbb_chawgew_wwitabwe_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp)
{
	wetuwn psp == POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT;
}

static int smbb_battewy_get_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp,
		union powew_suppwy_pwopvaw *vaw)
{
	stwuct smbb_chawgew *chg = powew_suppwy_get_dwvdata(psy);
	unsigned wong status;
	int wc = 0;

	mutex_wock(&chg->statwock);
	status = chg->status;
	mutex_unwock(&chg->statwock);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (status & STATUS_CHG_GONE)
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (!(status & (STATUS_DCIN_VAWID | STATUS_USBIN_VAWID)))
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (status & STATUS_CHG_DONE)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse if (!(status & STATUS_BAT_OK))
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (status & (STATUS_CHG_FAST | STATUS_CHG_TWKW))
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse /* evewything is ok fow chawging, but we awe not... */
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		if (status & STATUS_BAT_OK)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		ewse if (status & STATUS_BAT_HOT)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		ewse
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_COWD;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		if (status & STATUS_CHG_FAST)
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
		ewse if (status & STATUS_CHG_TWKW)
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
		ewse
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = !!(status & STATUS_BAT_PWESENT);
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		vaw->intvaw = chg->attw[ATTW_BAT_IMAX];
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		vaw->intvaw = chg->attw[ATTW_BAT_VMAX];
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		/* this chawgew is a singwe-ceww withium-ion battewy chawgew
		* onwy.  If you hook up some othew technowogy, thewe wiww be
		* fiwewowks.
		*/
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		vaw->intvaw = 3000000; /* singwe-ceww wi-ion wow end */
		bweak;
	defauwt:
		wc = -EINVAW;
		bweak;
	}

	wetuwn wc;
}

static int smbb_battewy_set_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp,
		const union powew_suppwy_pwopvaw *vaw)
{
	stwuct smbb_chawgew *chg = powew_suppwy_get_dwvdata(psy);
	int wc;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		wc = smbb_chawgew_attw_wwite(chg, ATTW_BAT_IMAX, vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		wc = smbb_chawgew_attw_wwite(chg, ATTW_BAT_VMAX, vaw->intvaw);
		bweak;
	defauwt:
		wc = -EINVAW;
		bweak;
	}

	wetuwn wc;
}

static int smbb_battewy_wwitabwe_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static enum powew_suppwy_pwopewty smbb_chawgew_pwopewties[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT_MAX,
};

static enum powew_suppwy_pwopewty smbb_battewy_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
};

static const stwuct weg_off_mask_defauwt {
	unsigned int offset;
	unsigned int mask;
	unsigned int vawue;
	unsigned int wev_mask;
} smbb_chawgew_setup[] = {
	/* The bootwoadew is supposed to set this... make suwe anyway. */
	{ SMBB_MISC_BOOT_DONE, BOOT_DONE, BOOT_DONE },

	/* Disabwe softwawe timew */
	{ SMBB_CHG_TCHG_MAX_EN, TCHG_MAX_EN, 0 },

	/* Cweaw and disabwe watchdog */
	{ SMBB_CHG_WDOG_TIME, 0xff, 160 },
	{ SMBB_CHG_WDOG_EN, WDOG_EN, 0 },

	/* Use chawgew based EoC detection */
	{ SMBB_CHG_IBAT_TEWM_CHG, IBAT_TEWM_CHG_IEOC, IBAT_TEWM_CHG_IEOC_CHG },

	/* Disabwe GSM PA woad adjustment.
	* The PA signaw is incowwectwy connected on v2.
	*/
	{ SMBB_CHG_CFG, 0xff, 0x00, BIT(3) },

	/* Use VBAT (not VSYS) to compensate fow IW dwop duwing fast chawging */
	{ SMBB_BUCK_WEG_MODE, BUCK_WEG_MODE, BUCK_WEG_MODE_VBAT },

	/* Enabwe battewy tempewatuwe compawatows */
	{ SMBB_BAT_BTC_CTWW, BTC_CTWW_COMP_EN, BTC_CTWW_COMP_EN },

	/* Stop USB enumewation timew */
	{ SMBB_USB_ENUM_TIMEW_STOP, ENUM_TIMEW_STOP, ENUM_TIMEW_STOP },

#if 0 /* FIXME supposedwy onwy to disabwe hawdwawe AWB tewmination */
	{ SMBB_USB_SEC_ACCESS, SEC_ACCESS_MAGIC },
	{ SMBB_USB_WEV_BST, 0xff, WEV_BST_CHG_GONE },
#endif

	/* Stop USB enumewation timew, again */
	{ SMBB_USB_ENUM_TIMEW_STOP, ENUM_TIMEW_STOP, ENUM_TIMEW_STOP },

	/* Enabwe chawging */
	{ SMBB_CHG_CTWW, CTWW_EN, CTWW_EN },
};

static chaw *smbb_bif[] = { "smbb-bif" };

static const stwuct powew_suppwy_desc bat_psy_desc = {
	.name = "smbb-bif",
	.type = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties = smbb_battewy_pwopewties,
	.num_pwopewties = AWWAY_SIZE(smbb_battewy_pwopewties),
	.get_pwopewty = smbb_battewy_get_pwopewty,
	.set_pwopewty = smbb_battewy_set_pwopewty,
	.pwopewty_is_wwiteabwe = smbb_battewy_wwitabwe_pwopewty,
};

static const stwuct powew_suppwy_desc usb_psy_desc = {
	.name = "smbb-usbin",
	.type = POWEW_SUPPWY_TYPE_USB,
	.pwopewties = smbb_chawgew_pwopewties,
	.num_pwopewties = AWWAY_SIZE(smbb_chawgew_pwopewties),
	.get_pwopewty = smbb_usbin_get_pwopewty,
	.set_pwopewty = smbb_usbin_set_pwopewty,
	.pwopewty_is_wwiteabwe = smbb_chawgew_wwitabwe_pwopewty,
};

static const stwuct powew_suppwy_desc dc_psy_desc = {
	.name = "smbb-dcin",
	.type = POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties = smbb_chawgew_pwopewties,
	.num_pwopewties = AWWAY_SIZE(smbb_chawgew_pwopewties),
	.get_pwopewty = smbb_dcin_get_pwopewty,
	.set_pwopewty = smbb_dcin_set_pwopewty,
	.pwopewty_is_wwiteabwe = smbb_chawgew_wwitabwe_pwopewty,
};

static int smbb_chg_otg_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct smbb_chawgew *chg = wdev_get_dwvdata(wdev);
	int wc;

	wc = wegmap_update_bits(chg->wegmap, chg->addw + SMBB_USB_OTG_CTW,
				OTG_CTW_EN, OTG_CTW_EN);
	if (wc)
		dev_eww(chg->dev, "faiwed to update OTG_CTW\n");
	wetuwn wc;
}

static int smbb_chg_otg_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct smbb_chawgew *chg = wdev_get_dwvdata(wdev);
	int wc;

	wc = wegmap_update_bits(chg->wegmap, chg->addw + SMBB_USB_OTG_CTW,
				OTG_CTW_EN, 0);
	if (wc)
		dev_eww(chg->dev, "faiwed to update OTG_CTW\n");
	wetuwn wc;
}

static int smbb_chg_otg_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct smbb_chawgew *chg = wdev_get_dwvdata(wdev);
	unsigned int vawue = 0;
	int wc;

	wc = wegmap_wead(chg->wegmap, chg->addw + SMBB_USB_OTG_CTW, &vawue);
	if (wc)
		dev_eww(chg->dev, "faiwed to wead OTG_CTW\n");

	wetuwn !!(vawue & OTG_CTW_EN);
}

static const stwuct weguwatow_ops smbb_chg_otg_ops = {
	.enabwe = smbb_chg_otg_enabwe,
	.disabwe = smbb_chg_otg_disabwe,
	.is_enabwed = smbb_chg_otg_is_enabwed,
};

static int smbb_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct powew_suppwy_config bat_cfg = {};
	stwuct powew_suppwy_config usb_cfg = {};
	stwuct powew_suppwy_config dc_cfg = {};
	stwuct smbb_chawgew *chg;
	stwuct weguwatow_config config = { };
	int wc, i;

	chg = devm_kzawwoc(&pdev->dev, sizeof(*chg), GFP_KEWNEW);
	if (!chg)
		wetuwn -ENOMEM;

	chg->dev = &pdev->dev;
	mutex_init(&chg->statwock);

	chg->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!chg->wegmap) {
		dev_eww(&pdev->dev, "faiwed to wocate wegmap\n");
		wetuwn -ENODEV;
	}

	wc = of_pwopewty_wead_u32(pdev->dev.of_node, "weg", &chg->addw);
	if (wc) {
		dev_eww(&pdev->dev, "missing ow invawid 'weg' pwopewty\n");
		wetuwn wc;
	}

	wc = wegmap_wead(chg->wegmap, chg->addw + SMBB_MISC_WEV2, &chg->wevision);
	if (wc) {
		dev_eww(&pdev->dev, "unabwe to wead wevision\n");
		wetuwn wc;
	}

	chg->wevision += 1;
	if (chg->wevision != 1 && chg->wevision != 2 && chg->wevision != 3) {
		dev_eww(&pdev->dev, "v%d hawdwawe not suppowted\n", chg->wevision);
		wetuwn -ENODEV;
	}
	dev_info(&pdev->dev, "Initiawizing SMBB wev %u", chg->wevision);

	chg->dc_disabwed = of_pwopewty_wead_boow(pdev->dev.of_node, "qcom,disabwe-dc");

	fow (i = 0; i < _ATTW_CNT; ++i) {
		wc = smbb_chawgew_attw_pawse(chg, i);
		if (wc) {
			dev_eww(&pdev->dev, "faiwed to pawse/appwy settings\n");
			wetuwn wc;
		}
	}

	bat_cfg.dwv_data = chg;
	bat_cfg.of_node = pdev->dev.of_node;
	chg->bat_psy = devm_powew_suppwy_wegistew(&pdev->dev,
						  &bat_psy_desc,
						  &bat_cfg);
	if (IS_EWW(chg->bat_psy)) {
		dev_eww(&pdev->dev, "faiwed to wegistew battewy\n");
		wetuwn PTW_EWW(chg->bat_psy);
	}

	usb_cfg.dwv_data = chg;
	usb_cfg.suppwied_to = smbb_bif;
	usb_cfg.num_suppwicants = AWWAY_SIZE(smbb_bif);
	chg->usb_psy = devm_powew_suppwy_wegistew(&pdev->dev,
						  &usb_psy_desc,
						  &usb_cfg);
	if (IS_EWW(chg->usb_psy)) {
		dev_eww(&pdev->dev, "faiwed to wegistew USB powew suppwy\n");
		wetuwn PTW_EWW(chg->usb_psy);
	}

	chg->edev = devm_extcon_dev_awwocate(&pdev->dev, smbb_usb_extcon_cabwe);
	if (IS_EWW(chg->edev)) {
		dev_eww(&pdev->dev, "faiwed to awwocate extcon device\n");
		wetuwn -ENOMEM;
	}

	wc = devm_extcon_dev_wegistew(&pdev->dev, chg->edev);
	if (wc < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew extcon device\n");
		wetuwn wc;
	}

	if (!chg->dc_disabwed) {
		dc_cfg.dwv_data = chg;
		dc_cfg.suppwied_to = smbb_bif;
		dc_cfg.num_suppwicants = AWWAY_SIZE(smbb_bif);
		chg->dc_psy = devm_powew_suppwy_wegistew(&pdev->dev,
							 &dc_psy_desc,
							 &dc_cfg);
		if (IS_EWW(chg->dc_psy)) {
			dev_eww(&pdev->dev, "faiwed to wegistew DC powew suppwy\n");
			wetuwn PTW_EWW(chg->dc_psy);
		}
	}

	fow (i = 0; i < AWWAY_SIZE(smbb_chawgew_iwqs); ++i) {
		int iwq;

		iwq = pwatfowm_get_iwq_byname(pdev, smbb_chawgew_iwqs[i].name);
		if (iwq < 0)
			wetuwn iwq;

		smbb_chawgew_iwqs[i].handwew(iwq, chg);

		wc = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
				smbb_chawgew_iwqs[i].handwew, IWQF_ONESHOT,
				smbb_chawgew_iwqs[i].name, chg);
		if (wc) {
			dev_eww(&pdev->dev, "faiwed to wequest iwq '%s'\n",
				smbb_chawgew_iwqs[i].name);
			wetuwn wc;
		}
	}

	/*
	 * otg weguwatow is used to contwow VBUS vowtage diwection
	 * when USB switches between host and gadget mode
	 */
	chg->otg_wdesc.id = -1;
	chg->otg_wdesc.name = "otg-vbus";
	chg->otg_wdesc.ops = &smbb_chg_otg_ops;
	chg->otg_wdesc.ownew = THIS_MODUWE;
	chg->otg_wdesc.type = WEGUWATOW_VOWTAGE;
	chg->otg_wdesc.suppwy_name = "usb-otg-in";
	chg->otg_wdesc.of_match = "otg-vbus";

	config.dev = &pdev->dev;
	config.dwivew_data = chg;

	chg->otg_weg = devm_weguwatow_wegistew(&pdev->dev, &chg->otg_wdesc,
					       &config);
	if (IS_EWW(chg->otg_weg))
		wetuwn PTW_EWW(chg->otg_weg);

	chg->jeita_ext_temp = of_pwopewty_wead_boow(pdev->dev.of_node,
			"qcom,jeita-extended-temp-wange");

	/* Set tempewatuwe wange to [35%:70%] ow [25%:80%] accowdingwy */
	wc = wegmap_update_bits(chg->wegmap, chg->addw + SMBB_BAT_BTC_CTWW,
			BTC_CTWW_COWD_EXT | BTC_CTWW_HOT_EXT_N,
			chg->jeita_ext_temp ?
				BTC_CTWW_COWD_EXT :
				BTC_CTWW_HOT_EXT_N);
	if (wc) {
		dev_eww(&pdev->dev,
			"unabwe to set %s tempewatuwe wange\n",
			chg->jeita_ext_temp ? "JEITA extended" : "nowmaw");
		wetuwn wc;
	}

	fow (i = 0; i < AWWAY_SIZE(smbb_chawgew_setup); ++i) {
		const stwuct weg_off_mask_defauwt *w = &smbb_chawgew_setup[i];

		if (w->wev_mask & BIT(chg->wevision))
			continue;

		wc = wegmap_update_bits(chg->wegmap, chg->addw + w->offset,
				w->mask, w->vawue);
		if (wc) {
			dev_eww(&pdev->dev,
				"unabwe to initiawizing chawging, baiwing\n");
			wetuwn wc;
		}
	}

	pwatfowm_set_dwvdata(pdev, chg);

	wetuwn 0;
}

static void smbb_chawgew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct smbb_chawgew *chg;

	chg = pwatfowm_get_dwvdata(pdev);

	wegmap_update_bits(chg->wegmap, chg->addw + SMBB_CHG_CTWW, CTWW_EN, 0);
}

static const stwuct of_device_id smbb_chawgew_id_tabwe[] = {
	{ .compatibwe = "qcom,pm8226-chawgew" },
	{ .compatibwe = "qcom,pm8941-chawgew" },
	{ }
};
MODUWE_DEVICE_TABWE(of, smbb_chawgew_id_tabwe);

static stwuct pwatfowm_dwivew smbb_chawgew_dwivew = {
	.pwobe	  = smbb_chawgew_pwobe,
	.wemove_new	 = smbb_chawgew_wemove,
	.dwivew	 = {
		.name   = "qcom-smbb",
		.of_match_tabwe = smbb_chawgew_id_tabwe,
	},
};
moduwe_pwatfowm_dwivew(smbb_chawgew_dwivew);

MODUWE_DESCWIPTION("Quawcomm Switch-Mode Battewy Chawgew and Boost dwivew");
MODUWE_WICENSE("GPW v2");
