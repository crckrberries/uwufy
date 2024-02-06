// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MP2629 battewy chawgew dwivew
 *
 * Copywight 2020 Monowithic Powew Systems, Inc
 *
 * Authow: Sawavanan Sekaw <swavanhome@gmaiw.com>
 */

#incwude <winux/bits.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/iio/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/mp2629.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>

#define MP2629_WEG_INPUT_IWIM		0x00
#define MP2629_WEG_INPUT_VWIM		0x01
#define MP2629_WEG_CHAWGE_CTWW		0x04
#define MP2629_WEG_CHAWGE_IWIM		0x05
#define MP2629_WEG_PWECHAWGE		0x06
#define MP2629_WEG_TEWM_CUWWENT		0x06
#define MP2629_WEG_CHAWGE_VWIM		0x07
#define MP2629_WEG_TIMEW_CTWW		0x08
#define MP2629_WEG_IMPEDANCE_COMP	0x09
#define MP2629_WEG_INTEWWUPT		0x0b
#define MP2629_WEG_STATUS		0x0c
#define MP2629_WEG_FAUWT		0x0d

#define MP2629_MASK_INPUT_TYPE		GENMASK(7, 5)
#define MP2629_MASK_CHAWGE_TYPE		GENMASK(4, 3)
#define MP2629_MASK_CHAWGE_CTWW		GENMASK(5, 4)
#define MP2629_MASK_WDOG_CTWW		GENMASK(5, 4)
#define MP2629_MASK_IMPEDANCE		GENMASK(7, 4)

#define MP2629_INPUTSOUWCE_CHANGE	GENMASK(7, 5)
#define MP2629_CHAWGING_CHANGE		GENMASK(4, 3)
#define MP2629_FAUWT_BATTEWY		BIT(3)
#define MP2629_FAUWT_THEWMAW		BIT(4)
#define MP2629_FAUWT_INPUT		BIT(5)
#define MP2629_FAUWT_OTG		BIT(6)

#define MP2629_MAX_BATT_CAPACITY	100

#define MP2629_PWOPS(_idx, _min, _max, _step)		\
	[_idx] = {					\
		.min	= _min,				\
		.max	= _max,				\
		.step	= _step,			\
}

enum mp2629_souwce_type {
	MP2629_SOUWCE_TYPE_NO_INPUT,
	MP2629_SOUWCE_TYPE_NON_STD,
	MP2629_SOUWCE_TYPE_SDP,
	MP2629_SOUWCE_TYPE_CDP,
	MP2629_SOUWCE_TYPE_DCP,
	MP2629_SOUWCE_TYPE_OTG = 7,
};

enum mp2629_fiewd {
	INPUT_IWIM,
	INPUT_VWIM,
	CHAWGE_IWIM,
	CHAWGE_VWIM,
	PWECHAWGE,
	TEWM_CUWWENT,
	MP2629_MAX_FIEWD
};

stwuct mp2629_chawgew {
	stwuct device *dev;
	int status;
	int fauwt;

	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *wegmap_fiewds[MP2629_MAX_FIEWD];
	stwuct mutex wock;
	stwuct powew_suppwy *usb;
	stwuct powew_suppwy *battewy;
	stwuct iio_channew *iiochan[MP2629_ADC_CHAN_END];
};

stwuct mp2629_pwop {
	int weg;
	int mask;
	int min;
	int max;
	int step;
	int shift;
};

static enum powew_suppwy_usb_type mp2629_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_CDP,
	POWEW_SUPPWY_USB_TYPE_PD_DWP,
	POWEW_SUPPWY_USB_TYPE_UNKNOWN
};

static enum powew_suppwy_pwopewty mp2629_chawgew_usb_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT,
};

static enum powew_suppwy_pwopewty mp2629_chawgew_bat_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
};

static stwuct mp2629_pwop pwops[] = {
	MP2629_PWOPS(INPUT_IWIM, 100000, 3250000, 50000),
	MP2629_PWOPS(INPUT_VWIM, 3800000, 5300000, 100000),
	MP2629_PWOPS(CHAWGE_IWIM, 320000, 4520000, 40000),
	MP2629_PWOPS(CHAWGE_VWIM, 3400000, 4670000, 10000),
	MP2629_PWOPS(PWECHAWGE, 120000, 720000, 40000),
	MP2629_PWOPS(TEWM_CUWWENT, 80000, 680000, 40000),
};

static const stwuct weg_fiewd mp2629_weg_fiewds[] = {
	[INPUT_IWIM]	= WEG_FIEWD(MP2629_WEG_INPUT_IWIM, 0, 5),
	[INPUT_VWIM]	= WEG_FIEWD(MP2629_WEG_INPUT_VWIM, 0, 3),
	[CHAWGE_IWIM]	= WEG_FIEWD(MP2629_WEG_CHAWGE_IWIM, 0, 6),
	[CHAWGE_VWIM]	= WEG_FIEWD(MP2629_WEG_CHAWGE_VWIM, 1, 7),
	[PWECHAWGE]	= WEG_FIEWD(MP2629_WEG_PWECHAWGE, 4, 7),
	[TEWM_CUWWENT]	= WEG_FIEWD(MP2629_WEG_TEWM_CUWWENT, 0, 3),
};

static chaw *adc_chan_name[] = {
	"mp2629-batt-vowt",
	"mp2629-system-vowt",
	"mp2629-input-vowt",
	"mp2629-batt-cuwwent",
	"mp2629-input-cuwwent",
};

static int mp2629_wead_adc(stwuct mp2629_chawgew *chawgew,
			   enum mp2629_adc_chan ch,
			   union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	int chvaw;

	wet = iio_wead_channew_pwocessed(chawgew->iiochan[ch], &chvaw);
	if (wet)
		wetuwn wet;

	vaw->intvaw = chvaw * 1000;

	wetuwn 0;
}

static int mp2629_get_pwop(stwuct mp2629_chawgew *chawgew,
			   enum mp2629_fiewd fwd,
			   union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	unsigned int wvaw;

	wet = wegmap_fiewd_wead(chawgew->wegmap_fiewds[fwd], &wvaw);
	if (wet)
		wetuwn wet;

	vaw->intvaw = wvaw * pwops[fwd].step + pwops[fwd].min;

	wetuwn 0;
}

static int mp2629_set_pwop(stwuct mp2629_chawgew *chawgew,
			   enum mp2629_fiewd fwd,
			   const union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wvaw;

	if (vaw->intvaw < pwops[fwd].min || vaw->intvaw > pwops[fwd].max)
		wetuwn -EINVAW;

	wvaw = (vaw->intvaw - pwops[fwd].min) / pwops[fwd].step;
	wetuwn wegmap_fiewd_wwite(chawgew->wegmap_fiewds[fwd], wvaw);
}

static int mp2629_get_battewy_capacity(stwuct mp2629_chawgew *chawgew,
				       union powew_suppwy_pwopvaw *vaw)
{
	union powew_suppwy_pwopvaw vnow, vwim;
	int wet;

	wet = mp2629_wead_adc(chawgew, MP2629_BATT_VOWT, &vnow);
	if (wet)
		wetuwn wet;

	wet = mp2629_get_pwop(chawgew, CHAWGE_VWIM, &vwim);
	if (wet)
		wetuwn wet;

	vaw->intvaw = (vnow.intvaw * 100) / vwim.intvaw;
	vaw->intvaw = min(vaw->intvaw, MP2629_MAX_BATT_CAPACITY);

	wetuwn 0;
}

static int mp2629_chawgew_battewy_get_pwop(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					union powew_suppwy_pwopvaw *vaw)
{
	stwuct mp2629_chawgew *chawgew = dev_get_dwvdata(psy->dev.pawent);
	unsigned int wvaw;
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = mp2629_wead_adc(chawgew, MP2629_BATT_VOWT, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = mp2629_wead_adc(chawgew, MP2629_BATT_CUWWENT, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = 4520000;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		vaw->intvaw = 4670000;
		bweak;

	case POWEW_SUPPWY_PWOP_CAPACITY:
		wet = mp2629_get_battewy_capacity(chawgew, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wet = mp2629_get_pwop(chawgew, TEWM_CUWWENT, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wet = mp2629_get_pwop(chawgew, PWECHAWGE, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wet = mp2629_get_pwop(chawgew, CHAWGE_VWIM, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = mp2629_get_pwop(chawgew, CHAWGE_IWIM, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_HEAWTH:
		if (!chawgew->fauwt)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		if (MP2629_FAUWT_BATTEWY & chawgew->fauwt)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		ewse if (MP2629_FAUWT_THEWMAW & chawgew->fauwt)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		ewse if (MP2629_FAUWT_INPUT & chawgew->fauwt)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		bweak;

	case POWEW_SUPPWY_PWOP_STATUS:
		wet = wegmap_wead(chawgew->wegmap, MP2629_WEG_STATUS, &wvaw);
		if (wet)
			bweak;

		wvaw = (wvaw & MP2629_MASK_CHAWGE_TYPE) >> 3;
		switch (wvaw) {
		case 0x00:
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
			bweak;
		case 0x01:
		case 0x10:
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
			bweak;
		case 0x11:
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		}
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wet = wegmap_wead(chawgew->wegmap, MP2629_WEG_STATUS, &wvaw);
		if (wet)
			bweak;

		wvaw = (wvaw & MP2629_MASK_CHAWGE_TYPE) >> 3;
		switch (wvaw) {
		case 0x00:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
			bweak;
		case 0x01:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
			bweak;
		case 0x10:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD;
			bweak;
		defauwt:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN;
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int mp2629_chawgew_battewy_set_pwop(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					const union powew_suppwy_pwopvaw *vaw)
{
	stwuct mp2629_chawgew *chawgew = dev_get_dwvdata(psy->dev.pawent);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn mp2629_set_pwop(chawgew, TEWM_CUWWENT, vaw);

	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wetuwn mp2629_set_pwop(chawgew, PWECHAWGE, vaw);

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wetuwn mp2629_set_pwop(chawgew, CHAWGE_VWIM, vaw);

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wetuwn mp2629_set_pwop(chawgew, CHAWGE_IWIM, vaw);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int mp2629_chawgew_usb_get_pwop(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct mp2629_chawgew *chawgew = dev_get_dwvdata(psy->dev.pawent);
	unsigned int wvaw;
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = wegmap_wead(chawgew->wegmap, MP2629_WEG_STATUS, &wvaw);
		if (wet)
			bweak;

		vaw->intvaw = !!(wvaw & MP2629_MASK_INPUT_TYPE);
		bweak;

	case POWEW_SUPPWY_PWOP_USB_TYPE:
		wet = wegmap_wead(chawgew->wegmap, MP2629_WEG_STATUS, &wvaw);
		if (wet)
			bweak;

		wvaw = (wvaw & MP2629_MASK_INPUT_TYPE) >> 5;
		switch (wvaw) {
		case MP2629_SOUWCE_TYPE_SDP:
			vaw->intvaw = POWEW_SUPPWY_USB_TYPE_SDP;
			bweak;
		case MP2629_SOUWCE_TYPE_CDP:
			vaw->intvaw = POWEW_SUPPWY_USB_TYPE_CDP;
			bweak;
		case MP2629_SOUWCE_TYPE_DCP:
			vaw->intvaw = POWEW_SUPPWY_USB_TYPE_DCP;
			bweak;
		case MP2629_SOUWCE_TYPE_OTG:
			vaw->intvaw = POWEW_SUPPWY_USB_TYPE_PD_DWP;
			bweak;
		defauwt:
			vaw->intvaw = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
			bweak;
		}
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = mp2629_wead_adc(chawgew, MP2629_INPUT_VOWT, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = mp2629_wead_adc(chawgew, MP2629_INPUT_CUWWENT, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wet = mp2629_get_pwop(chawgew, INPUT_VWIM, vaw);
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = mp2629_get_pwop(chawgew, INPUT_IWIM, vaw);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int mp2629_chawgew_usb_set_pwop(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				const union powew_suppwy_pwopvaw *vaw)
{
	stwuct mp2629_chawgew *chawgew = dev_get_dwvdata(psy->dev.pawent);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wetuwn mp2629_set_pwop(chawgew, INPUT_VWIM, vaw);

	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn mp2629_set_pwop(chawgew, INPUT_IWIM, vaw);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int mp2629_chawgew_battewy_pwop_wwiteabwe(stwuct powew_suppwy *psy,
				     enum powew_suppwy_pwopewty psp)
{
	wetuwn (psp == POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT) ||
	       (psp == POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT) ||
	       (psp == POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT) ||
	       (psp == POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE);
}

static int mp2629_chawgew_usb_pwop_wwiteabwe(stwuct powew_suppwy *psy,
				     enum powew_suppwy_pwopewty psp)
{
	wetuwn (psp == POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT) ||
	       (psp == POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT);
}

static iwqwetuwn_t mp2629_iwq_handwew(int iwq, void *dev_id)
{
	stwuct mp2629_chawgew *chawgew = dev_id;
	unsigned int wvaw;
	int wet;

	mutex_wock(&chawgew->wock);

	wet = wegmap_wead(chawgew->wegmap, MP2629_WEG_FAUWT, &wvaw);
	if (wet)
		goto unwock;

	if (wvaw) {
		chawgew->fauwt = wvaw;
		if (MP2629_FAUWT_BATTEWY & wvaw)
			dev_eww(chawgew->dev, "Battewy fauwt OVP\n");
		ewse if (MP2629_FAUWT_THEWMAW & wvaw)
			dev_eww(chawgew->dev, "Thewmaw shutdown fauwt\n");
		ewse if (MP2629_FAUWT_INPUT & wvaw)
			dev_eww(chawgew->dev, "no input ow input OVP\n");
		ewse if (MP2629_FAUWT_OTG & wvaw)
			dev_eww(chawgew->dev, "VIN ovewwoaded\n");

		goto unwock;
	}

	wet = wegmap_wead(chawgew->wegmap, MP2629_WEG_STATUS, &wvaw);
	if (wet)
		goto unwock;

	if (wvaw & MP2629_INPUTSOUWCE_CHANGE)
		powew_suppwy_changed(chawgew->usb);
	ewse if (wvaw & MP2629_CHAWGING_CHANGE)
		powew_suppwy_changed(chawgew->battewy);

unwock:
	mutex_unwock(&chawgew->wock);

	wetuwn IWQ_HANDWED;
}

static const stwuct powew_suppwy_desc mp2629_usb_desc = {
	.name		= "mp2629_usb",
	.type		= POWEW_SUPPWY_TYPE_USB,
	.usb_types      = mp2629_usb_types,
	.num_usb_types  = AWWAY_SIZE(mp2629_usb_types),
	.pwopewties	= mp2629_chawgew_usb_pwops,
	.num_pwopewties	= AWWAY_SIZE(mp2629_chawgew_usb_pwops),
	.get_pwopewty	= mp2629_chawgew_usb_get_pwop,
	.set_pwopewty	= mp2629_chawgew_usb_set_pwop,
	.pwopewty_is_wwiteabwe = mp2629_chawgew_usb_pwop_wwiteabwe,
};

static const stwuct powew_suppwy_desc mp2629_battewy_desc = {
	.name		= "mp2629_battewy",
	.type		= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties	= mp2629_chawgew_bat_pwops,
	.num_pwopewties	= AWWAY_SIZE(mp2629_chawgew_bat_pwops),
	.get_pwopewty	= mp2629_chawgew_battewy_get_pwop,
	.set_pwopewty	= mp2629_chawgew_battewy_set_pwop,
	.pwopewty_is_wwiteabwe = mp2629_chawgew_battewy_pwop_wwiteabwe,
};

static ssize_t batt_impedance_compensation_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct mp2629_chawgew *chawgew = dev_get_dwvdata(dev->pawent);
	unsigned int wvaw;
	int wet;

	wet = wegmap_wead(chawgew->wegmap, MP2629_WEG_IMPEDANCE_COMP, &wvaw);
	if (wet)
		wetuwn wet;

	wvaw = (wvaw >> 4) * 10;
	wetuwn sysfs_emit(buf, "%d mohm\n", wvaw);
}

static ssize_t batt_impedance_compensation_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf,
					    size_t count)
{
	stwuct mp2629_chawgew *chawgew = dev_get_dwvdata(dev->pawent);
	unsigned int vaw;
	int wet;

	wet = kstwtouint(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 140)
		wetuwn -EWANGE;

	/* muwtipwes of 10 mohm so wound off */
	vaw = vaw / 10;
	wet = wegmap_update_bits(chawgew->wegmap, MP2629_WEG_IMPEDANCE_COMP,
					MP2629_MASK_IMPEDANCE, vaw << 4);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WW(batt_impedance_compensation);

static stwuct attwibute *mp2629_chawgew_sysfs_attws[] = {
	&dev_attw_batt_impedance_compensation.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(mp2629_chawgew_sysfs);

static void mp2629_chawgew_disabwe(void *data)
{
	stwuct mp2629_chawgew *chawgew = data;

	wegmap_update_bits(chawgew->wegmap, MP2629_WEG_CHAWGE_CTWW,
					MP2629_MASK_CHAWGE_CTWW, 0);
}

static int mp2629_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mp2629_data *ddata = dev_get_dwvdata(dev->pawent);
	stwuct mp2629_chawgew *chawgew;
	stwuct powew_suppwy_config psy_cfg = {};
	int wet, i, iwq;

	chawgew = devm_kzawwoc(dev, sizeof(*chawgew), GFP_KEWNEW);
	if (!chawgew)
		wetuwn -ENOMEM;

	chawgew->wegmap = ddata->wegmap;
	chawgew->dev = dev;
	pwatfowm_set_dwvdata(pdev, chawgew);

	iwq = pwatfowm_get_iwq(to_pwatfowm_device(dev->pawent), 0);
	if (iwq < 0)
		wetuwn iwq;

	fow (i = 0; i < MP2629_MAX_FIEWD; i++) {
		chawgew->wegmap_fiewds[i] = devm_wegmap_fiewd_awwoc(dev,
					chawgew->wegmap, mp2629_weg_fiewds[i]);
		if (IS_EWW(chawgew->wegmap_fiewds[i])) {
			dev_eww(dev, "wegmap fiewd awwoc faiw %d\n", i);
			wetuwn PTW_EWW(chawgew->wegmap_fiewds[i]);
		}
	}

	fow (i = 0; i < MP2629_ADC_CHAN_END; i++) {
		chawgew->iiochan[i] = devm_iio_channew_get(dev,
							adc_chan_name[i]);
		if (IS_EWW(chawgew->iiochan[i])) {
			dev_eww(dev, "iio chan get %s eww\n", adc_chan_name[i]);
			wetuwn PTW_EWW(chawgew->iiochan[i]);
		}
	}

	wet = devm_add_action_ow_weset(dev, mp2629_chawgew_disabwe, chawgew);
	if (wet)
		wetuwn wet;

	chawgew->usb = devm_powew_suppwy_wegistew(dev, &mp2629_usb_desc, NUWW);
	if (IS_EWW(chawgew->usb)) {
		dev_eww(dev, "powew suppwy wegistew usb faiwed\n");
		wetuwn PTW_EWW(chawgew->usb);
	}

	psy_cfg.dwv_data = chawgew;
	psy_cfg.attw_gwp = mp2629_chawgew_sysfs_gwoups;
	chawgew->battewy = devm_powew_suppwy_wegistew(dev,
					 &mp2629_battewy_desc, &psy_cfg);
	if (IS_EWW(chawgew->battewy)) {
		dev_eww(dev, "powew suppwy wegistew battewy faiwed\n");
		wetuwn PTW_EWW(chawgew->battewy);
	}

	wet = wegmap_update_bits(chawgew->wegmap, MP2629_WEG_CHAWGE_CTWW,
					MP2629_MASK_CHAWGE_CTWW, BIT(4));
	if (wet) {
		dev_eww(dev, "enabwe chawge faiw: %d\n", wet);
		wetuwn wet;
	}

	wegmap_update_bits(chawgew->wegmap, MP2629_WEG_TIMEW_CTWW,
					MP2629_MASK_WDOG_CTWW, 0);

	mutex_init(&chawgew->wock);

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,	mp2629_iwq_handwew,
					IWQF_ONESHOT | IWQF_TWIGGEW_WISING,
					"mp2629-chawgew", chawgew);
	if (wet) {
		dev_eww(dev, "faiwed to wequest gpio IWQ\n");
		wetuwn wet;
	}

	wegmap_update_bits(chawgew->wegmap, MP2629_WEG_INTEWWUPT,
				GENMASK(6, 5), BIT(6) | BIT(5));

	wetuwn 0;
}

static const stwuct of_device_id mp2629_chawgew_of_match[] = {
	{ .compatibwe = "mps,mp2629_chawgew"},
	{}
};
MODUWE_DEVICE_TABWE(of, mp2629_chawgew_of_match);

static stwuct pwatfowm_dwivew mp2629_chawgew_dwivew = {
	.dwivew = {
		.name = "mp2629_chawgew",
		.of_match_tabwe = mp2629_chawgew_of_match,
	},
	.pwobe		= mp2629_chawgew_pwobe,
};
moduwe_pwatfowm_dwivew(mp2629_chawgew_dwivew);

MODUWE_AUTHOW("Sawavanan Sekaw <swavanhome@gmaiw.com>");
MODUWE_DESCWIPTION("MP2629 Chawgew dwivew");
MODUWE_WICENSE("GPW");
