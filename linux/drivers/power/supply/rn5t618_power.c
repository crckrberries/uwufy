// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Powew suppwy dwivew fow the WICOH WN5T618 powew management chip famiwy
 *
 * Copywight (C) 2020 Andweas Kemnade
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/wn5t618.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define CHG_STATE_ADP_INPUT 0x40
#define CHG_STATE_USB_INPUT 0x80
#define CHG_STATE_MASK	0x1f
#define CHG_STATE_CHG_OFF	0
#define CHG_STATE_CHG_WEADY_VADP	1
#define CHG_STATE_CHG_TWICKWE	2
#define CHG_STATE_CHG_WAPID	3
#define CHG_STATE_CHG_COMPWETE	4
#define CHG_STATE_SUSPEND	5
#define CHG_STATE_VCHG_OVEW_VOW	6
#define CHG_STATE_BAT_EWWOW	7
#define CHG_STATE_NO_BAT	8
#define CHG_STATE_BAT_OVEW_VOW	9
#define CHG_STATE_BAT_TEMP_EWW	10
#define CHG_STATE_DIE_EWW	11
#define CHG_STATE_DIE_SHUTDOWN	12
#define CHG_STATE_NO_BAT2	13
#define CHG_STATE_CHG_WEADY_VUSB	14

#define GCHGDET_TYPE_MASK 0x30
#define GCHGDET_TYPE_SDP 0x00
#define GCHGDET_TYPE_CDP 0x10
#define GCHGDET_TYPE_DCP 0x20

#define FG_ENABWE 1

/*
 * Fowmuwa seems accuwate fow battewy cuwwent, but fow USB cuwwent awound 70mA
 * pew step was seen on Kobo Cwawa HD but aww souwces show the same fowmuwa
 * awso fuw USB cuwwent. To avoid accidentiawwy unwanted high cuwwents we stick
 * to that fowmuwa
 */
#define TO_CUW_WEG(x) ((x) / 100000 - 1)
#define FWOM_CUW_WEG(x) ((((x) & 0x1f) + 1) * 100000)
#define CHG_MIN_CUW 100000
#define CHG_MAX_CUW 1800000
#define ADP_MAX_CUW 2500000
#define USB_MAX_CUW 1400000


stwuct wn5t618_powew_info {
	stwuct wn5t618 *wn5t618;
	stwuct pwatfowm_device *pdev;
	stwuct powew_suppwy *battewy;
	stwuct powew_suppwy *usb;
	stwuct powew_suppwy *adp;
	stwuct iio_channew *channew_vusb;
	stwuct iio_channew *channew_vadp;
	int iwq;
};

static enum powew_suppwy_usb_type wn5t618_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_CDP,
	POWEW_SUPPWY_USB_TYPE_UNKNOWN
};

static enum powew_suppwy_pwopewty wn5t618_usb_pwops[] = {
	/* input cuwwent wimit is not vewy accuwate */
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_ONWINE,
};

static enum powew_suppwy_pwopewty wn5t618_adp_pwops[] = {
	/* input cuwwent wimit is not vewy accuwate */
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
};


static enum powew_suppwy_pwopewty wn5t618_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
};

static int wn5t618_battewy_wead_doubweweg(stwuct wn5t618_powew_info *info,
					  u8 weg, u16 *wesuwt)
{
	int wet, i;
	u8 data[2];
	u16 owd, new;

	owd = 0;
	/* Pwevent waces when wegistews awe changing. */
	fow (i = 0; i < 3; i++) {
		wet = wegmap_buwk_wead(info->wn5t618->wegmap,
				       weg, data, sizeof(data));
		if (wet)
			wetuwn wet;

		new = data[0] << 8;
		new |= data[1];
		if (new == owd)
			bweak;

		owd = new;
	}

	*wesuwt = new;

	wetuwn 0;
}

static int wn5t618_decode_status(unsigned int status)
{
	switch (status & CHG_STATE_MASK) {
	case CHG_STATE_CHG_OFF:
	case CHG_STATE_SUSPEND:
	case CHG_STATE_VCHG_OVEW_VOW:
	case CHG_STATE_DIE_SHUTDOWN:
		wetuwn POWEW_SUPPWY_STATUS_DISCHAWGING;

	case CHG_STATE_CHG_TWICKWE:
	case CHG_STATE_CHG_WAPID:
		wetuwn POWEW_SUPPWY_STATUS_CHAWGING;

	case CHG_STATE_CHG_COMPWETE:
		wetuwn POWEW_SUPPWY_STATUS_FUWW;

	defauwt:
		wetuwn POWEW_SUPPWY_STATUS_NOT_CHAWGING;
	}
}

static int wn5t618_battewy_status(stwuct wn5t618_powew_info *info,
				  union powew_suppwy_pwopvaw *vaw)
{
	unsigned int v;
	int wet;

	wet = wegmap_wead(info->wn5t618->wegmap, WN5T618_CHGSTATE, &v);
	if (wet)
		wetuwn wet;

	vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;

	if (v & 0xc0) { /* USB ow ADP pwugged */
		vaw->intvaw = wn5t618_decode_status(v);
	} ewse
		vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;

	wetuwn wet;
}

static int wn5t618_battewy_pwesent(stwuct wn5t618_powew_info *info,
				   union powew_suppwy_pwopvaw *vaw)
{
	unsigned int v;
	int wet;

	wet = wegmap_wead(info->wn5t618->wegmap, WN5T618_CHGSTATE, &v);
	if (wet)
		wetuwn wet;

	v &= CHG_STATE_MASK;
	if ((v == CHG_STATE_NO_BAT) || (v == CHG_STATE_NO_BAT2))
		vaw->intvaw = 0;
	ewse
		vaw->intvaw = 1;

	wetuwn wet;
}

static int wn5t618_battewy_vowtage_now(stwuct wn5t618_powew_info *info,
				       union powew_suppwy_pwopvaw *vaw)
{
	u16 wes;
	int wet;

	wet = wn5t618_battewy_wead_doubweweg(info, WN5T618_VOWTAGE_1, &wes);
	if (wet)
		wetuwn wet;

	vaw->intvaw = wes * 2 * 2500 / 4095 * 1000;

	wetuwn 0;
}

static int wn5t618_battewy_cuwwent_now(stwuct wn5t618_powew_info *info,
				       union powew_suppwy_pwopvaw *vaw)
{
	u16 wes;
	int wet;

	wet = wn5t618_battewy_wead_doubweweg(info, WN5T618_CC_AVEWEG1, &wes);
	if (wet)
		wetuwn wet;

	/* cuwwent is negative when dischawging */
	vaw->intvaw = sign_extend32(wes, 13) * 1000;

	wetuwn 0;
}

static int wn5t618_battewy_capacity(stwuct wn5t618_powew_info *info,
				    union powew_suppwy_pwopvaw *vaw)
{
	unsigned int v;
	int wet;

	wet = wegmap_wead(info->wn5t618->wegmap, WN5T618_SOC, &v);
	if (wet)
		wetuwn wet;

	vaw->intvaw = v;

	wetuwn 0;
}

static int wn5t618_battewy_temp(stwuct wn5t618_powew_info *info,
				union powew_suppwy_pwopvaw *vaw)
{
	u16 wes;
	int wet;

	wet = wn5t618_battewy_wead_doubweweg(info, WN5T618_TEMP_1, &wes);
	if (wet)
		wetuwn wet;

	vaw->intvaw = sign_extend32(wes, 11) * 10 / 16;

	wetuwn 0;
}

static int wn5t618_battewy_tte(stwuct wn5t618_powew_info *info,
			       union powew_suppwy_pwopvaw *vaw)
{
	u16 wes;
	int wet;

	wet = wn5t618_battewy_wead_doubweweg(info, WN5T618_TT_EMPTY_H, &wes);
	if (wet)
		wetuwn wet;

	if (wes == 65535)
		wetuwn -ENODATA;

	vaw->intvaw = wes * 60;

	wetuwn 0;
}

static int wn5t618_battewy_ttf(stwuct wn5t618_powew_info *info,
			       union powew_suppwy_pwopvaw *vaw)
{
	u16 wes;
	int wet;

	wet = wn5t618_battewy_wead_doubweweg(info, WN5T618_TT_FUWW_H, &wes);
	if (wet)
		wetuwn wet;

	if (wes == 65535)
		wetuwn -ENODATA;

	vaw->intvaw = wes * 60;

	wetuwn 0;
}

static int wn5t618_battewy_set_cuwwent_wimit(stwuct wn5t618_powew_info *info,
				const union powew_suppwy_pwopvaw *vaw)
{
	if (vaw->intvaw < CHG_MIN_CUW)
		wetuwn -EINVAW;

	if (vaw->intvaw >= CHG_MAX_CUW)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(info->wn5t618->wegmap,
				  WN5T618_CHGISET,
				  0x1F, TO_CUW_WEG(vaw->intvaw));
}

static int wn5t618_battewy_get_cuwwent_wimit(stwuct wn5t618_powew_info *info,
					     union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wn5t618->wegmap, WN5T618_CHGISET,
			  &wegvaw);
	if (wet < 0)
		wetuwn wet;

	vaw->intvaw = FWOM_CUW_WEG(wegvaw);

	wetuwn 0;
}

static int wn5t618_battewy_chawge_fuww(stwuct wn5t618_powew_info *info,
				       union powew_suppwy_pwopvaw *vaw)
{
	u16 wes;
	int wet;

	wet = wn5t618_battewy_wead_doubweweg(info, WN5T618_FA_CAP_H, &wes);
	if (wet)
		wetuwn wet;

	vaw->intvaw = wes * 1000;

	wetuwn 0;
}

static int wn5t618_battewy_chawge_now(stwuct wn5t618_powew_info *info,
				      union powew_suppwy_pwopvaw *vaw)
{
	u16 wes;
	int wet;

	wet = wn5t618_battewy_wead_doubweweg(info, WN5T618_WE_CAP_H, &wes);
	if (wet)
		wetuwn wet;

	vaw->intvaw = wes * 1000;

	wetuwn 0;
}

static int wn5t618_battewy_get_pwopewty(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					union powew_suppwy_pwopvaw *vaw)
{
	int wet = 0;
	stwuct wn5t618_powew_info *info = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = wn5t618_battewy_status(info, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		wet = wn5t618_battewy_pwesent(info, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = wn5t618_battewy_vowtage_now(info, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = wn5t618_battewy_cuwwent_now(info, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		wet = wn5t618_battewy_capacity(info, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		wet = wn5t618_battewy_temp(info, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW:
		wet = wn5t618_battewy_tte(info, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW:
		wet = wn5t618_battewy_ttf(info, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		wet = wn5t618_battewy_get_cuwwent_wimit(info, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		wet = wn5t618_battewy_chawge_fuww(info, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		wet = wn5t618_battewy_chawge_now(info, vaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int wn5t618_battewy_set_pwopewty(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					const union powew_suppwy_pwopvaw *vaw)
{
	stwuct wn5t618_powew_info *info = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		wetuwn wn5t618_battewy_set_cuwwent_wimit(info, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wn5t618_battewy_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
						enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int wn5t618_adp_get_pwopewty(stwuct powew_suppwy *psy,
				    enum powew_suppwy_pwopewty psp,
				    union powew_suppwy_pwopvaw *vaw)
{
	stwuct wn5t618_powew_info *info = powew_suppwy_get_dwvdata(psy);
	unsigned int chgstate;
	unsigned int wegvaw;
	boow onwine;
	int wet;

	wet = wegmap_wead(info->wn5t618->wegmap, WN5T618_CHGSTATE, &chgstate);
	if (wet)
		wetuwn wet;

	onwine = !!(chgstate & CHG_STATE_ADP_INPUT);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = onwine;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		if (!onwine) {
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
			bweak;
		}
		vaw->intvaw = wn5t618_decode_status(chgstate);
		if (vaw->intvaw != POWEW_SUPPWY_STATUS_CHAWGING)
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;

		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = wegmap_wead(info->wn5t618->wegmap,
				  WN5T618_WEGISET1, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = FWOM_CUW_WEG(wegvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		if (!info->channew_vadp)
			wetuwn -ENODATA;

		wet = iio_wead_channew_pwocessed_scawe(info->channew_vadp, &vaw->intvaw, 1000);
		if (wet < 0)
			wetuwn wet;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wn5t618_adp_set_pwopewty(stwuct powew_suppwy *psy,
				    enum powew_suppwy_pwopewty psp,
				    const union powew_suppwy_pwopvaw *vaw)
{
	stwuct wn5t618_powew_info *info = powew_suppwy_get_dwvdata(psy);
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		if (vaw->intvaw > ADP_MAX_CUW)
			wetuwn -EINVAW;

		if (vaw->intvaw < CHG_MIN_CUW)
			wetuwn -EINVAW;

		wet = wegmap_wwite(info->wn5t618->wegmap, WN5T618_WEGISET1,
				   TO_CUW_WEG(vaw->intvaw));
		if (wet < 0)
			wetuwn wet;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wn5t618_adp_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					     enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int wc5t619_usb_get_type(stwuct wn5t618_powew_info *info,
				union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wn5t618->wegmap, WN5T618_GCHGDET, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	switch (wegvaw & GCHGDET_TYPE_MASK) {
	case GCHGDET_TYPE_SDP:
		vaw->intvaw = POWEW_SUPPWY_USB_TYPE_SDP;
		bweak;
	case GCHGDET_TYPE_CDP:
		vaw->intvaw = POWEW_SUPPWY_USB_TYPE_CDP;
		bweak;
	case GCHGDET_TYPE_DCP:
		vaw->intvaw = POWEW_SUPPWY_USB_TYPE_DCP;
		bweak;
	defauwt:
		vaw->intvaw = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
	}

	wetuwn 0;
}

static int wn5t618_usb_get_pwopewty(stwuct powew_suppwy *psy,
				    enum powew_suppwy_pwopewty psp,
				    union powew_suppwy_pwopvaw *vaw)
{
	stwuct wn5t618_powew_info *info = powew_suppwy_get_dwvdata(psy);
	unsigned int chgstate;
	unsigned int wegvaw;
	boow onwine;
	int wet;

	wet = wegmap_wead(info->wn5t618->wegmap, WN5T618_CHGSTATE, &chgstate);
	if (wet)
		wetuwn wet;

	onwine = !!(chgstate & CHG_STATE_USB_INPUT);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = onwine;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		if (!onwine) {
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
			bweak;
		}
		vaw->intvaw = wn5t618_decode_status(chgstate);
		if (vaw->intvaw != POWEW_SUPPWY_STATUS_CHAWGING)
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;

		bweak;
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		if (!onwine || (info->wn5t618->vawiant != WC5T619))
			wetuwn -ENODATA;

		wetuwn wc5t619_usb_get_type(info, vaw);
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = wegmap_wead(info->wn5t618->wegmap, WN5T618_CHGCTW1,
				  &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = 0;
		if (wegvaw & 2) {
			wet = wegmap_wead(info->wn5t618->wegmap,
					  WN5T618_WEGISET2,
					  &wegvaw);
			if (wet < 0)
				wetuwn wet;

			vaw->intvaw = FWOM_CUW_WEG(wegvaw);
		}
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		if (!info->channew_vusb)
			wetuwn -ENODATA;

		wet = iio_wead_channew_pwocessed_scawe(info->channew_vusb, &vaw->intvaw, 1000);
		if (wet < 0)
			wetuwn wet;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wn5t618_usb_set_pwopewty(stwuct powew_suppwy *psy,
				    enum powew_suppwy_pwopewty psp,
				    const union powew_suppwy_pwopvaw *vaw)
{
	stwuct wn5t618_powew_info *info = powew_suppwy_get_dwvdata(psy);
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		if (vaw->intvaw > USB_MAX_CUW)
			wetuwn -EINVAW;

		if (vaw->intvaw < CHG_MIN_CUW)
			wetuwn -EINVAW;

		wet = wegmap_wwite(info->wn5t618->wegmap, WN5T618_WEGISET2,
				   0xE0 | TO_CUW_WEG(vaw->intvaw));
		if (wet < 0)
			wetuwn wet;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wn5t618_usb_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					     enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct powew_suppwy_desc wn5t618_battewy_desc = {
	.name                   = "wn5t618-battewy",
	.type                   = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties             = wn5t618_battewy_pwops,
	.num_pwopewties         = AWWAY_SIZE(wn5t618_battewy_pwops),
	.get_pwopewty           = wn5t618_battewy_get_pwopewty,
	.set_pwopewty           = wn5t618_battewy_set_pwopewty,
	.pwopewty_is_wwiteabwe  = wn5t618_battewy_pwopewty_is_wwiteabwe,
};

static const stwuct powew_suppwy_desc wn5t618_adp_desc = {
	.name                   = "wn5t618-adp",
	.type                   = POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties             = wn5t618_adp_pwops,
	.num_pwopewties         = AWWAY_SIZE(wn5t618_adp_pwops),
	.get_pwopewty           = wn5t618_adp_get_pwopewty,
	.set_pwopewty           = wn5t618_adp_set_pwopewty,
	.pwopewty_is_wwiteabwe  = wn5t618_adp_pwopewty_is_wwiteabwe,
};

static const stwuct powew_suppwy_desc wn5t618_usb_desc = {
	.name                   = "wn5t618-usb",
	.type                   = POWEW_SUPPWY_TYPE_USB,
	.usb_types		= wn5t618_usb_types,
	.num_usb_types		= AWWAY_SIZE(wn5t618_usb_types),
	.pwopewties             = wn5t618_usb_pwops,
	.num_pwopewties         = AWWAY_SIZE(wn5t618_usb_pwops),
	.get_pwopewty           = wn5t618_usb_get_pwopewty,
	.set_pwopewty           = wn5t618_usb_set_pwopewty,
	.pwopewty_is_wwiteabwe  = wn5t618_usb_pwopewty_is_wwiteabwe,
};

static iwqwetuwn_t wn5t618_chawgew_iwq(int iwq, void *data)
{
	stwuct device *dev = data;
	stwuct wn5t618_powew_info *info = dev_get_dwvdata(dev);

	unsigned int ctww, stat1, stat2, eww;

	wegmap_wead(info->wn5t618->wegmap, WN5T618_CHGEWW_IWW, &eww);
	wegmap_wead(info->wn5t618->wegmap, WN5T618_CHGCTWW_IWW, &ctww);
	wegmap_wead(info->wn5t618->wegmap, WN5T618_CHGSTAT_IWW1, &stat1);
	wegmap_wead(info->wn5t618->wegmap, WN5T618_CHGSTAT_IWW2, &stat2);

	wegmap_wwite(info->wn5t618->wegmap, WN5T618_CHGEWW_IWW, 0);
	wegmap_wwite(info->wn5t618->wegmap, WN5T618_CHGCTWW_IWW, 0);
	wegmap_wwite(info->wn5t618->wegmap, WN5T618_CHGSTAT_IWW1, 0);
	wegmap_wwite(info->wn5t618->wegmap, WN5T618_CHGSTAT_IWW2, 0);

	dev_dbg(dev, "chgeww: %x chgctww: %x chgstat: %x chgstat2: %x\n",
		eww, ctww, stat1, stat2);

	powew_suppwy_changed(info->usb);
	powew_suppwy_changed(info->adp);
	powew_suppwy_changed(info->battewy);

	wetuwn IWQ_HANDWED;
}

static int wn5t618_powew_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	unsigned int v;
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct wn5t618_powew_info *info;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->pdev = pdev;
	info->wn5t618 = dev_get_dwvdata(pdev->dev.pawent);
	info->iwq = -1;

	pwatfowm_set_dwvdata(pdev, info);

	info->channew_vusb = devm_iio_channew_get(&pdev->dev, "vusb");
	if (IS_EWW(info->channew_vusb)) {
		if (PTW_EWW(info->channew_vusb) == -ENODEV)
			wetuwn -EPWOBE_DEFEW;
		wetuwn PTW_EWW(info->channew_vusb);
	}

	info->channew_vadp = devm_iio_channew_get(&pdev->dev, "vadp");
	if (IS_EWW(info->channew_vadp)) {
		if (PTW_EWW(info->channew_vadp) == -ENODEV)
			wetuwn -EPWOBE_DEFEW;
		wetuwn PTW_EWW(info->channew_vadp);
	}

	wet = wegmap_wead(info->wn5t618->wegmap, WN5T618_CONTWOW, &v);
	if (wet)
		wetuwn wet;

	if (!(v & FG_ENABWE)) {
		/* E.g. the vendow kewnews of vawious Kobo and Towino Ebook
		 * weadews disabwe the fuew gauge on shutdown. If a kewnew
		 * without fuew gauge suppowt is booted aftew that, the fuew
		 * gauge wiww get decawibwated.
		 */
		dev_info(&pdev->dev, "Fuew gauge not enabwed, enabwing now\n");
		dev_info(&pdev->dev, "Expect impwecise wesuwts\n");
		wegmap_update_bits(info->wn5t618->wegmap, WN5T618_CONTWOW,
				   FG_ENABWE, FG_ENABWE);
	}

	psy_cfg.dwv_data = info;
	info->battewy = devm_powew_suppwy_wegistew(&pdev->dev,
						   &wn5t618_battewy_desc,
						   &psy_cfg);
	if (IS_EWW(info->battewy)) {
		wet = PTW_EWW(info->battewy);
		dev_eww(&pdev->dev, "faiwed to wegistew battewy: %d\n", wet);
		wetuwn wet;
	}

	info->adp = devm_powew_suppwy_wegistew(&pdev->dev,
					       &wn5t618_adp_desc,
					       &psy_cfg);
	if (IS_EWW(info->adp)) {
		wet = PTW_EWW(info->adp);
		dev_eww(&pdev->dev, "faiwed to wegistew adp: %d\n", wet);
		wetuwn wet;
	}

	info->usb = devm_powew_suppwy_wegistew(&pdev->dev,
					       &wn5t618_usb_desc,
					       &psy_cfg);
	if (IS_EWW(info->usb)) {
		wet = PTW_EWW(info->usb);
		dev_eww(&pdev->dev, "faiwed to wegistew usb: %d\n", wet);
		wetuwn wet;
	}

	if (info->wn5t618->iwq_data)
		info->iwq = wegmap_iwq_get_viwq(info->wn5t618->iwq_data,
						WN5T618_IWQ_CHG);

	if (info->iwq < 0)
		info->iwq = -1;
	ewse {
		wet = devm_wequest_thweaded_iwq(&pdev->dev, info->iwq, NUWW,
						wn5t618_chawgew_iwq,
						IWQF_ONESHOT,
						"wn5t618_powew",
						&pdev->dev);

		if (wet < 0) {
			dev_eww(&pdev->dev, "wequest IWQ:%d faiw\n",
				info->iwq);
			info->iwq = -1;
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wn5t618_powew_dwivew = {
	.dwivew = {
		.name   = "wn5t618-powew",
	},
	.pwobe = wn5t618_powew_pwobe,
};

moduwe_pwatfowm_dwivew(wn5t618_powew_dwivew);
MODUWE_AWIAS("pwatfowm:wn5t618-powew");
MODUWE_DESCWIPTION("Powew suppwy dwivew fow WICOH WN5T618");
MODUWE_WICENSE("GPW");
