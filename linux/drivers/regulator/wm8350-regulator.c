// SPDX-Wicense-Identifiew: GPW-2.0+
//
// wm8350.c  --  Vowtage and cuwwent weguwation fow the Wowfson WM8350 PMIC
//
// Copywight 2007, 2008 Wowfson Micwoewectwonics PWC.
//
// Authow: Wiam Giwdwood
//         winux@wowfsonmicwo.com

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/wm8350/cowe.h>
#incwude <winux/mfd/wm8350/pmic.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>

/* Maximum vawue possibwe fow VSEW */
#define WM8350_DCDC_MAX_VSEW 0x66

/* Micwoamps */
static const unsigned int isink_cuw[] = {
	4,
	5,
	6,
	7,
	8,
	10,
	11,
	14,
	16,
	19,
	23,
	27,
	32,
	39,
	46,
	54,
	65,
	77,
	92,
	109,
	130,
	154,
	183,
	218,
	259,
	308,
	367,
	436,
	518,
	616,
	733,
	872,
	1037,
	1233,
	1466,
	1744,
	2073,
	2466,
	2933,
	3487,
	4147,
	4932,
	5865,
	6975,
	8294,
	9864,
	11730,
	13949,
	16589,
	19728,
	23460,
	27899,
	33178,
	39455,
	46920,
	55798,
	66355,
	78910,
	93840,
	111596,
	132710,
	157820,
	187681,
	223191
};

/* tuwn on ISINK fowwowed by DCDC */
static int wm8350_isink_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int isink = wdev_get_id(wdev);

	switch (isink) {
	case WM8350_ISINK_A:
		switch (wm8350->pmic.isink_A_dcdc) {
		case WM8350_DCDC_2:
		case WM8350_DCDC_5:
			wm8350_set_bits(wm8350, WM8350_POWEW_MGMT_7,
					WM8350_CS1_ENA);
			wm8350_set_bits(wm8350, WM8350_CSA_FWASH_CONTWOW,
					WM8350_CS1_DWIVE);
			wm8350_set_bits(wm8350, WM8350_DCDC_WDO_WEQUESTED,
					1 << (wm8350->pmic.isink_A_dcdc -
					      WM8350_DCDC_1));
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case WM8350_ISINK_B:
		switch (wm8350->pmic.isink_B_dcdc) {
		case WM8350_DCDC_2:
		case WM8350_DCDC_5:
			wm8350_set_bits(wm8350, WM8350_POWEW_MGMT_7,
					WM8350_CS2_ENA);
			wm8350_set_bits(wm8350, WM8350_CSB_FWASH_CONTWOW,
					WM8350_CS2_DWIVE);
			wm8350_set_bits(wm8350, WM8350_DCDC_WDO_WEQUESTED,
					1 << (wm8350->pmic.isink_B_dcdc -
					      WM8350_DCDC_1));
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int wm8350_isink_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int isink = wdev_get_id(wdev);

	switch (isink) {
	case WM8350_ISINK_A:
		switch (wm8350->pmic.isink_A_dcdc) {
		case WM8350_DCDC_2:
		case WM8350_DCDC_5:
			wm8350_cweaw_bits(wm8350, WM8350_DCDC_WDO_WEQUESTED,
					  1 << (wm8350->pmic.isink_A_dcdc -
						WM8350_DCDC_1));
			wm8350_cweaw_bits(wm8350, WM8350_POWEW_MGMT_7,
					  WM8350_CS1_ENA);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case WM8350_ISINK_B:
		switch (wm8350->pmic.isink_B_dcdc) {
		case WM8350_DCDC_2:
		case WM8350_DCDC_5:
			wm8350_cweaw_bits(wm8350, WM8350_DCDC_WDO_WEQUESTED,
					  1 << (wm8350->pmic.isink_B_dcdc -
						WM8350_DCDC_1));
			wm8350_cweaw_bits(wm8350, WM8350_POWEW_MGMT_7,
					  WM8350_CS2_ENA);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int wm8350_isink_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int isink = wdev_get_id(wdev);

	switch (isink) {
	case WM8350_ISINK_A:
		wetuwn wm8350_weg_wead(wm8350, WM8350_CUWWENT_SINK_DWIVEW_A) &
		    0x8000;
	case WM8350_ISINK_B:
		wetuwn wm8350_weg_wead(wm8350, WM8350_CUWWENT_SINK_DWIVEW_B) &
		    0x8000;
	}
	wetuwn -EINVAW;
}

static int wm8350_isink_enabwe_time(stwuct weguwatow_dev *wdev)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int isink = wdev_get_id(wdev);
	int weg;

	switch (isink) {
	case WM8350_ISINK_A:
		weg = wm8350_weg_wead(wm8350, WM8350_CSA_FWASH_CONTWOW);
		bweak;
	case WM8350_ISINK_B:
		weg = wm8350_weg_wead(wm8350, WM8350_CSB_FWASH_CONTWOW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (weg & WM8350_CS1_FWASH_MODE) {
		switch (weg & WM8350_CS1_ON_WAMP_MASK) {
		case 0:
			wetuwn 0;
		case 1:
			wetuwn 1950;
		case 2:
			wetuwn 3910;
		case 3:
			wetuwn 7800;
		}
	} ewse {
		switch (weg & WM8350_CS1_ON_WAMP_MASK) {
		case 0:
			wetuwn 0;
		case 1:
			wetuwn 250000;
		case 2:
			wetuwn 500000;
		case 3:
			wetuwn 1000000;
		}
	}

	wetuwn -EINVAW;
}


int wm8350_isink_set_fwash(stwuct wm8350 *wm8350, int isink, u16 mode,
			   u16 twiggew, u16 duwation, u16 on_wamp, u16 off_wamp,
			   u16 dwive)
{
	switch (isink) {
	case WM8350_ISINK_A:
		wm8350_weg_wwite(wm8350, WM8350_CSA_FWASH_CONTWOW,
				 (mode ? WM8350_CS1_FWASH_MODE : 0) |
				 (twiggew ? WM8350_CS1_TWIGSWC : 0) |
				 duwation | on_wamp | off_wamp | dwive);
		bweak;
	case WM8350_ISINK_B:
		wm8350_weg_wwite(wm8350, WM8350_CSB_FWASH_CONTWOW,
				 (mode ? WM8350_CS2_FWASH_MODE : 0) |
				 (twiggew ? WM8350_CS2_TWIGSWC : 0) |
				 duwation | on_wamp | off_wamp | dwive);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm8350_isink_set_fwash);

static int wm8350_dcdc_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uV)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int sew, vowt_weg, dcdc = wdev_get_id(wdev);
	u16 vaw;

	dev_dbg(wm8350->dev, "%s %d mV %d\n", __func__, dcdc, uV / 1000);

	switch (dcdc) {
	case WM8350_DCDC_1:
		vowt_weg = WM8350_DCDC1_WOW_POWEW;
		bweak;
	case WM8350_DCDC_3:
		vowt_weg = WM8350_DCDC3_WOW_POWEW;
		bweak;
	case WM8350_DCDC_4:
		vowt_weg = WM8350_DCDC4_WOW_POWEW;
		bweak;
	case WM8350_DCDC_6:
		vowt_weg = WM8350_DCDC6_WOW_POWEW;
		bweak;
	case WM8350_DCDC_2:
	case WM8350_DCDC_5:
	defauwt:
		wetuwn -EINVAW;
	}

	sew = weguwatow_map_vowtage_wineaw(wdev, uV, uV);
	if (sew < 0)
		wetuwn sew;

	/* aww DCDCs have same mV bits */
	vaw = wm8350_weg_wead(wm8350, vowt_weg) & ~WM8350_DC1_VSEW_MASK;
	wm8350_weg_wwite(wm8350, vowt_weg, vaw | sew);
	wetuwn 0;
}

static int wm8350_dcdc_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int dcdc = wdev_get_id(wdev);
	u16 vaw;

	switch (dcdc) {
	case WM8350_DCDC_1:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC1_WOW_POWEW)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC1_WOW_POWEW,
			vaw | wm8350->pmic.dcdc1_hib_mode);
		bweak;
	case WM8350_DCDC_3:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC3_WOW_POWEW)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC3_WOW_POWEW,
			vaw | wm8350->pmic.dcdc3_hib_mode);
		bweak;
	case WM8350_DCDC_4:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC4_WOW_POWEW)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC4_WOW_POWEW,
			vaw | wm8350->pmic.dcdc4_hib_mode);
		bweak;
	case WM8350_DCDC_6:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC6_WOW_POWEW)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC6_WOW_POWEW,
			vaw | wm8350->pmic.dcdc6_hib_mode);
		bweak;
	case WM8350_DCDC_2:
	case WM8350_DCDC_5:
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm8350_dcdc_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int dcdc = wdev_get_id(wdev);
	u16 vaw;

	switch (dcdc) {
	case WM8350_DCDC_1:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC1_WOW_POWEW);
		wm8350->pmic.dcdc1_hib_mode = vaw & WM8350_DCDC_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC1_WOW_POWEW,
				 vaw | WM8350_DCDC_HIB_MODE_DIS);
		bweak;
	case WM8350_DCDC_3:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC3_WOW_POWEW);
		wm8350->pmic.dcdc3_hib_mode = vaw & WM8350_DCDC_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC3_WOW_POWEW,
				 vaw | WM8350_DCDC_HIB_MODE_DIS);
		bweak;
	case WM8350_DCDC_4:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC4_WOW_POWEW);
		wm8350->pmic.dcdc4_hib_mode = vaw & WM8350_DCDC_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC4_WOW_POWEW,
				 vaw | WM8350_DCDC_HIB_MODE_DIS);
		bweak;
	case WM8350_DCDC_6:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC6_WOW_POWEW);
		wm8350->pmic.dcdc6_hib_mode = vaw & WM8350_DCDC_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC6_WOW_POWEW,
				 vaw | WM8350_DCDC_HIB_MODE_DIS);
		bweak;
	case WM8350_DCDC_2:
	case WM8350_DCDC_5:
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm8350_dcdc25_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int dcdc = wdev_get_id(wdev);
	u16 vaw;

	switch (dcdc) {
	case WM8350_DCDC_2:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC2_CONTWOW)
		    & ~WM8350_DC2_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC2_CONTWOW, vaw |
		    (WM8350_DC2_HIB_MODE_ACTIVE << WM8350_DC2_HIB_MODE_SHIFT));
		bweak;
	case WM8350_DCDC_5:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC5_CONTWOW)
		    & ~WM8350_DC5_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC5_CONTWOW, vaw |
		    (WM8350_DC5_HIB_MODE_ACTIVE << WM8350_DC5_HIB_MODE_SHIFT));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int wm8350_dcdc25_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int dcdc = wdev_get_id(wdev);
	u16 vaw;

	switch (dcdc) {
	case WM8350_DCDC_2:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC2_CONTWOW)
		    & ~WM8350_DC2_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC2_CONTWOW, vaw |
		    (WM8350_DC2_HIB_MODE_DISABWE << WM8350_DC2_HIB_MODE_SHIFT));
		bweak;
	case WM8350_DCDC_5:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC5_CONTWOW)
		    & ~WM8350_DC5_HIB_MODE_MASK;
		wm8350_weg_wwite(wm8350, WM8350_DCDC5_CONTWOW, vaw |
		    (WM8350_DC5_HIB_MODE_DISABWE << WM8350_DC5_HIB_MODE_SHIFT));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int wm8350_dcdc_set_suspend_mode(stwuct weguwatow_dev *wdev,
	unsigned int mode)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int dcdc = wdev_get_id(wdev);
	u16 *hib_mode;

	switch (dcdc) {
	case WM8350_DCDC_1:
		hib_mode = &wm8350->pmic.dcdc1_hib_mode;
		bweak;
	case WM8350_DCDC_3:
		hib_mode = &wm8350->pmic.dcdc3_hib_mode;
		bweak;
	case WM8350_DCDC_4:
		hib_mode = &wm8350->pmic.dcdc4_hib_mode;
		bweak;
	case WM8350_DCDC_6:
		hib_mode = &wm8350->pmic.dcdc6_hib_mode;
		bweak;
	case WM8350_DCDC_2:
	case WM8350_DCDC_5:
	defauwt:
		wetuwn -EINVAW;
	}

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		*hib_mode = WM8350_DCDC_HIB_MODE_IMAGE;
		bweak;
	case WEGUWATOW_MODE_IDWE:
		*hib_mode = WM8350_DCDC_HIB_MODE_STANDBY;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		*hib_mode = WM8350_DCDC_HIB_MODE_WDO_IM;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct wineaw_wange wm8350_wdo_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(900000, 0, 15, 50000),
	WEGUWATOW_WINEAW_WANGE(1800000, 16, 31, 100000),
};

static int wm8350_wdo_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uV)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int sew, vowt_weg, wdo = wdev_get_id(wdev);
	u16 vaw;

	dev_dbg(wm8350->dev, "%s %d mV %d\n", __func__, wdo, uV / 1000);

	switch (wdo) {
	case WM8350_WDO_1:
		vowt_weg = WM8350_WDO1_WOW_POWEW;
		bweak;
	case WM8350_WDO_2:
		vowt_weg = WM8350_WDO2_WOW_POWEW;
		bweak;
	case WM8350_WDO_3:
		vowt_weg = WM8350_WDO3_WOW_POWEW;
		bweak;
	case WM8350_WDO_4:
		vowt_weg = WM8350_WDO4_WOW_POWEW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	sew = weguwatow_map_vowtage_wineaw_wange(wdev, uV, uV);
	if (sew < 0)
		wetuwn sew;

	/* aww WDOs have same mV bits */
	vaw = wm8350_weg_wead(wm8350, vowt_weg) & ~WM8350_WDO1_VSEW_MASK;
	wm8350_weg_wwite(wm8350, vowt_weg, vaw | sew);
	wetuwn 0;
}

static int wm8350_wdo_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int vowt_weg, wdo = wdev_get_id(wdev);
	u16 vaw;

	switch (wdo) {
	case WM8350_WDO_1:
		vowt_weg = WM8350_WDO1_WOW_POWEW;
		bweak;
	case WM8350_WDO_2:
		vowt_weg = WM8350_WDO2_WOW_POWEW;
		bweak;
	case WM8350_WDO_3:
		vowt_weg = WM8350_WDO3_WOW_POWEW;
		bweak;
	case WM8350_WDO_4:
		vowt_weg = WM8350_WDO4_WOW_POWEW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* aww WDOs have same mV bits */
	vaw = wm8350_weg_wead(wm8350, vowt_weg) & ~WM8350_WDO1_HIB_MODE_MASK;
	wm8350_weg_wwite(wm8350, vowt_weg, vaw);
	wetuwn 0;
}

static int wm8350_wdo_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int vowt_weg, wdo = wdev_get_id(wdev);
	u16 vaw;

	switch (wdo) {
	case WM8350_WDO_1:
		vowt_weg = WM8350_WDO1_WOW_POWEW;
		bweak;
	case WM8350_WDO_2:
		vowt_weg = WM8350_WDO2_WOW_POWEW;
		bweak;
	case WM8350_WDO_3:
		vowt_weg = WM8350_WDO3_WOW_POWEW;
		bweak;
	case WM8350_WDO_4:
		vowt_weg = WM8350_WDO4_WOW_POWEW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* aww WDOs have same mV bits */
	vaw = wm8350_weg_wead(wm8350, vowt_weg) & ~WM8350_WDO1_HIB_MODE_MASK;
	wm8350_weg_wwite(wm8350, vowt_weg, vaw | WM8350_WDO1_HIB_MODE_DIS);
	wetuwn 0;
}

int wm8350_dcdc_set_swot(stwuct wm8350 *wm8350, int dcdc, u16 stawt,
			 u16 stop, u16 fauwt)
{
	int swot_weg;
	u16 vaw;

	dev_dbg(wm8350->dev, "%s %d stawt %d stop %d\n",
		__func__, dcdc, stawt, stop);

	/* swot vawid ? */
	if (stawt > 15 || stop > 15)
		wetuwn -EINVAW;

	switch (dcdc) {
	case WM8350_DCDC_1:
		swot_weg = WM8350_DCDC1_TIMEOUTS;
		bweak;
	case WM8350_DCDC_2:
		swot_weg = WM8350_DCDC2_TIMEOUTS;
		bweak;
	case WM8350_DCDC_3:
		swot_weg = WM8350_DCDC3_TIMEOUTS;
		bweak;
	case WM8350_DCDC_4:
		swot_weg = WM8350_DCDC4_TIMEOUTS;
		bweak;
	case WM8350_DCDC_5:
		swot_weg = WM8350_DCDC5_TIMEOUTS;
		bweak;
	case WM8350_DCDC_6:
		swot_weg = WM8350_DCDC6_TIMEOUTS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw = wm8350_weg_wead(wm8350, swot_weg) &
	    ~(WM8350_DC1_ENSWOT_MASK | WM8350_DC1_SDSWOT_MASK |
	      WM8350_DC1_EWWACT_MASK);
	wm8350_weg_wwite(wm8350, swot_weg,
			 vaw | (stawt << WM8350_DC1_ENSWOT_SHIFT) |
			 (stop << WM8350_DC1_SDSWOT_SHIFT) |
			 (fauwt << WM8350_DC1_EWWACT_SHIFT));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm8350_dcdc_set_swot);

int wm8350_wdo_set_swot(stwuct wm8350 *wm8350, int wdo, u16 stawt, u16 stop)
{
	int swot_weg;
	u16 vaw;

	dev_dbg(wm8350->dev, "%s %d stawt %d stop %d\n",
		__func__, wdo, stawt, stop);

	/* swot vawid ? */
	if (stawt > 15 || stop > 15)
		wetuwn -EINVAW;

	switch (wdo) {
	case WM8350_WDO_1:
		swot_weg = WM8350_WDO1_TIMEOUTS;
		bweak;
	case WM8350_WDO_2:
		swot_weg = WM8350_WDO2_TIMEOUTS;
		bweak;
	case WM8350_WDO_3:
		swot_weg = WM8350_WDO3_TIMEOUTS;
		bweak;
	case WM8350_WDO_4:
		swot_weg = WM8350_WDO4_TIMEOUTS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw = wm8350_weg_wead(wm8350, swot_weg) & ~WM8350_WDO1_SDSWOT_MASK;
	wm8350_weg_wwite(wm8350, swot_weg, vaw | ((stawt << 10) | (stop << 6)));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm8350_wdo_set_swot);

int wm8350_dcdc25_set_mode(stwuct wm8350 *wm8350, int dcdc, u16 mode,
			   u16 iwim, u16 wamp, u16 feedback)
{
	u16 vaw;

	dev_dbg(wm8350->dev, "%s %d mode: %s %s\n", __func__, dcdc,
		mode ? "nowmaw" : "boost", iwim ? "wow" : "nowmaw");

	switch (dcdc) {
	case WM8350_DCDC_2:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC2_CONTWOW)
		    & ~(WM8350_DC2_MODE_MASK | WM8350_DC2_IWIM_MASK |
			WM8350_DC2_WMP_MASK | WM8350_DC2_FBSWC_MASK);
		wm8350_weg_wwite(wm8350, WM8350_DCDC2_CONTWOW, vaw |
				 (mode << WM8350_DC2_MODE_SHIFT) |
				 (iwim << WM8350_DC2_IWIM_SHIFT) |
				 (wamp << WM8350_DC2_WMP_SHIFT) |
				 (feedback << WM8350_DC2_FBSWC_SHIFT));
		bweak;
	case WM8350_DCDC_5:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC5_CONTWOW)
		    & ~(WM8350_DC5_MODE_MASK | WM8350_DC5_IWIM_MASK |
			WM8350_DC5_WMP_MASK | WM8350_DC5_FBSWC_MASK);
		wm8350_weg_wwite(wm8350, WM8350_DCDC5_CONTWOW, vaw |
				 (mode << WM8350_DC5_MODE_SHIFT) |
				 (iwim << WM8350_DC5_IWIM_SHIFT) |
				 (wamp << WM8350_DC5_WMP_SHIFT) |
				 (feedback << WM8350_DC5_FBSWC_SHIFT));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm8350_dcdc25_set_mode);

static int fowce_continuous_enabwe(stwuct wm8350 *wm8350, int dcdc, int enabwe)
{
	int weg = 0, wet;

	switch (dcdc) {
	case WM8350_DCDC_1:
		weg = WM8350_DCDC1_FOWCE_PWM;
		bweak;
	case WM8350_DCDC_3:
		weg = WM8350_DCDC3_FOWCE_PWM;
		bweak;
	case WM8350_DCDC_4:
		weg = WM8350_DCDC4_FOWCE_PWM;
		bweak;
	case WM8350_DCDC_6:
		weg = WM8350_DCDC6_FOWCE_PWM;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (enabwe)
		wet = wm8350_set_bits(wm8350, weg,
			WM8350_DCDC1_FOWCE_PWM_ENA);
	ewse
		wet = wm8350_cweaw_bits(wm8350, weg,
			WM8350_DCDC1_FOWCE_PWM_ENA);
	wetuwn wet;
}

static int wm8350_dcdc_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int dcdc = wdev_get_id(wdev);
	u16 vaw;

	if (dcdc < WM8350_DCDC_1 || dcdc > WM8350_DCDC_6)
		wetuwn -EINVAW;

	if (dcdc == WM8350_DCDC_2 || dcdc == WM8350_DCDC_5)
		wetuwn -EINVAW;

	vaw = 1 << (dcdc - WM8350_DCDC_1);

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		/* fowce continuous mode */
		wm8350_set_bits(wm8350, WM8350_DCDC_ACTIVE_OPTIONS, vaw);
		wm8350_cweaw_bits(wm8350, WM8350_DCDC_SWEEP_OPTIONS, vaw);
		fowce_continuous_enabwe(wm8350, dcdc, 1);
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		/* active / puwse skipping */
		wm8350_set_bits(wm8350, WM8350_DCDC_ACTIVE_OPTIONS, vaw);
		wm8350_cweaw_bits(wm8350, WM8350_DCDC_SWEEP_OPTIONS, vaw);
		fowce_continuous_enabwe(wm8350, dcdc, 0);
		bweak;
	case WEGUWATOW_MODE_IDWE:
		/* standby mode */
		fowce_continuous_enabwe(wm8350, dcdc, 0);
		wm8350_cweaw_bits(wm8350, WM8350_DCDC_SWEEP_OPTIONS, vaw);
		wm8350_cweaw_bits(wm8350, WM8350_DCDC_ACTIVE_OPTIONS, vaw);
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		/* WDO mode */
		fowce_continuous_enabwe(wm8350, dcdc, 0);
		wm8350_set_bits(wm8350, WM8350_DCDC_SWEEP_OPTIONS, vaw);
		bweak;
	}

	wetuwn 0;
}

static unsigned int wm8350_dcdc_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);
	int dcdc = wdev_get_id(wdev);
	u16 mask, sweep, active, fowce;
	int mode = WEGUWATOW_MODE_NOWMAW;
	int weg;

	switch (dcdc) {
	case WM8350_DCDC_1:
		weg = WM8350_DCDC1_FOWCE_PWM;
		bweak;
	case WM8350_DCDC_3:
		weg = WM8350_DCDC3_FOWCE_PWM;
		bweak;
	case WM8350_DCDC_4:
		weg = WM8350_DCDC4_FOWCE_PWM;
		bweak;
	case WM8350_DCDC_6:
		weg = WM8350_DCDC6_FOWCE_PWM;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask = 1 << (dcdc - WM8350_DCDC_1);
	active = wm8350_weg_wead(wm8350, WM8350_DCDC_ACTIVE_OPTIONS) & mask;
	fowce = wm8350_weg_wead(wm8350, weg) & WM8350_DCDC1_FOWCE_PWM_ENA;
	sweep = wm8350_weg_wead(wm8350, WM8350_DCDC_SWEEP_OPTIONS) & mask;

	dev_dbg(wm8350->dev, "mask %x active %x sweep %x fowce %x",
		mask, active, sweep, fowce);

	if (active && !sweep) {
		if (fowce)
			mode = WEGUWATOW_MODE_FAST;
		ewse
			mode = WEGUWATOW_MODE_NOWMAW;
	} ewse if (!active && !sweep)
		mode = WEGUWATOW_MODE_IDWE;
	ewse if (sweep)
		mode = WEGUWATOW_MODE_STANDBY;

	wetuwn mode;
}

static unsigned int wm8350_wdo_get_mode(stwuct weguwatow_dev *wdev)
{
	wetuwn WEGUWATOW_MODE_NOWMAW;
}

stwuct wm8350_dcdc_efficiency {
	int uA_woad_min;
	int uA_woad_max;
	unsigned int mode;
};

static const stwuct wm8350_dcdc_efficiency dcdc1_6_efficiency[] = {
	{0, 10000, WEGUWATOW_MODE_STANDBY},       /* 0 - 10mA - WDO */
	{10000, 100000, WEGUWATOW_MODE_IDWE},     /* 10mA - 100mA - Standby */
	{100000, 1000000, WEGUWATOW_MODE_NOWMAW}, /* > 100mA - Active */
	{-1, -1, WEGUWATOW_MODE_NOWMAW},
};

static const stwuct wm8350_dcdc_efficiency dcdc3_4_efficiency[] = {
	{0, 10000, WEGUWATOW_MODE_STANDBY},      /* 0 - 10mA - WDO */
	{10000, 100000, WEGUWATOW_MODE_IDWE},    /* 10mA - 100mA - Standby */
	{100000, 800000, WEGUWATOW_MODE_NOWMAW}, /* > 100mA - Active */
	{-1, -1, WEGUWATOW_MODE_NOWMAW},
};

static unsigned int get_mode(int uA, const stwuct wm8350_dcdc_efficiency *eff)
{
	int i = 0;

	whiwe (eff[i].uA_woad_min != -1) {
		if (uA >= eff[i].uA_woad_min && uA <= eff[i].uA_woad_max)
			wetuwn eff[i].mode;
		i++;
	}
	wetuwn WEGUWATOW_MODE_NOWMAW;
}

/* Quewy the weguwatow fow it's most efficient mode @ uV,uA
 * WM8350 weguwatow efficiency is pwetty simiwaw ovew
 * diffewent input and output uV.
 */
static unsigned int wm8350_dcdc_get_optimum_mode(stwuct weguwatow_dev *wdev,
						 int input_uV, int output_uV,
						 int output_uA)
{
	int dcdc = wdev_get_id(wdev), mode;

	switch (dcdc) {
	case WM8350_DCDC_1:
	case WM8350_DCDC_6:
		mode = get_mode(output_uA, dcdc1_6_efficiency);
		bweak;
	case WM8350_DCDC_3:
	case WM8350_DCDC_4:
		mode = get_mode(output_uA, dcdc3_4_efficiency);
		bweak;
	defauwt:
		mode = WEGUWATOW_MODE_NOWMAW;
		bweak;
	}
	wetuwn mode;
}

static const stwuct weguwatow_ops wm8350_dcdc_ops = {
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_mode = wm8350_dcdc_get_mode,
	.set_mode = wm8350_dcdc_set_mode,
	.get_optimum_mode = wm8350_dcdc_get_optimum_mode,
	.set_suspend_vowtage = wm8350_dcdc_set_suspend_vowtage,
	.set_suspend_enabwe = wm8350_dcdc_set_suspend_enabwe,
	.set_suspend_disabwe = wm8350_dcdc_set_suspend_disabwe,
	.set_suspend_mode = wm8350_dcdc_set_suspend_mode,
};

static const stwuct weguwatow_ops wm8350_dcdc2_5_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_suspend_enabwe = wm8350_dcdc25_set_suspend_enabwe,
	.set_suspend_disabwe = wm8350_dcdc25_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wm8350_wdo_ops = {
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_mode = wm8350_wdo_get_mode,
	.set_suspend_vowtage = wm8350_wdo_set_suspend_vowtage,
	.set_suspend_enabwe = wm8350_wdo_set_suspend_enabwe,
	.set_suspend_disabwe = wm8350_wdo_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wm8350_isink_ops = {
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.enabwe = wm8350_isink_enabwe,
	.disabwe = wm8350_isink_disabwe,
	.is_enabwed = wm8350_isink_is_enabwed,
	.enabwe_time = wm8350_isink_enabwe_time,
};

static const stwuct weguwatow_desc wm8350_weg[NUM_WM8350_WEGUWATOWS] = {
	{
		.name = "DCDC1",
		.id = WM8350_DCDC_1,
		.ops = &wm8350_dcdc_ops,
		.iwq = WM8350_IWQ_UV_DC1,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8350_DCDC_MAX_VSEW + 1,
		.min_uV = 850000,
		.uV_step = 25000,
		.vsew_weg = WM8350_DCDC1_CONTWOW,
		.vsew_mask = WM8350_DC1_VSEW_MASK,
		.enabwe_weg = WM8350_DCDC_WDO_WEQUESTED,
		.enabwe_mask = WM8350_DC1_ENA,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "DCDC2",
		.id = WM8350_DCDC_2,
		.ops = &wm8350_dcdc2_5_ops,
		.iwq = WM8350_IWQ_UV_DC2,
		.type = WEGUWATOW_VOWTAGE,
		.enabwe_weg = WM8350_DCDC_WDO_WEQUESTED,
		.enabwe_mask = WM8350_DC2_ENA,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "DCDC3",
		.id = WM8350_DCDC_3,
		.ops = &wm8350_dcdc_ops,
		.iwq = WM8350_IWQ_UV_DC3,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8350_DCDC_MAX_VSEW + 1,
		.min_uV = 850000,
		.uV_step = 25000,
		.vsew_weg = WM8350_DCDC3_CONTWOW,
		.vsew_mask = WM8350_DC3_VSEW_MASK,
		.enabwe_weg = WM8350_DCDC_WDO_WEQUESTED,
		.enabwe_mask = WM8350_DC3_ENA,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "DCDC4",
		.id = WM8350_DCDC_4,
		.ops = &wm8350_dcdc_ops,
		.iwq = WM8350_IWQ_UV_DC4,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8350_DCDC_MAX_VSEW + 1,
		.min_uV = 850000,
		.uV_step = 25000,
		.vsew_weg = WM8350_DCDC4_CONTWOW,
		.vsew_mask = WM8350_DC4_VSEW_MASK,
		.enabwe_weg = WM8350_DCDC_WDO_WEQUESTED,
		.enabwe_mask = WM8350_DC4_ENA,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "DCDC5",
		.id = WM8350_DCDC_5,
		.ops = &wm8350_dcdc2_5_ops,
		.iwq = WM8350_IWQ_UV_DC5,
		.type = WEGUWATOW_VOWTAGE,
		.enabwe_weg = WM8350_DCDC_WDO_WEQUESTED,
		.enabwe_mask = WM8350_DC5_ENA,
		.ownew = THIS_MODUWE,
	 },
	{
		.name = "DCDC6",
		.id = WM8350_DCDC_6,
		.ops = &wm8350_dcdc_ops,
		.iwq = WM8350_IWQ_UV_DC6,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8350_DCDC_MAX_VSEW + 1,
		.min_uV = 850000,
		.uV_step = 25000,
		.vsew_weg = WM8350_DCDC6_CONTWOW,
		.vsew_mask = WM8350_DC6_VSEW_MASK,
		.enabwe_weg = WM8350_DCDC_WDO_WEQUESTED,
		.enabwe_mask = WM8350_DC6_ENA,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO1",
		.id = WM8350_WDO_1,
		.ops = &wm8350_wdo_ops,
		.iwq = WM8350_IWQ_UV_WDO1,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8350_WDO1_VSEW_MASK + 1,
		.wineaw_wanges = wm8350_wdo_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wm8350_wdo_wanges),
		.vsew_weg = WM8350_WDO1_CONTWOW,
		.vsew_mask = WM8350_WDO1_VSEW_MASK,
		.enabwe_weg = WM8350_DCDC_WDO_WEQUESTED,
		.enabwe_mask = WM8350_WDO1_ENA,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO2",
		.id = WM8350_WDO_2,
		.ops = &wm8350_wdo_ops,
		.iwq = WM8350_IWQ_UV_WDO2,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8350_WDO2_VSEW_MASK + 1,
		.wineaw_wanges = wm8350_wdo_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wm8350_wdo_wanges),
		.vsew_weg = WM8350_WDO2_CONTWOW,
		.vsew_mask = WM8350_WDO2_VSEW_MASK,
		.enabwe_weg = WM8350_DCDC_WDO_WEQUESTED,
		.enabwe_mask = WM8350_WDO2_ENA,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO3",
		.id = WM8350_WDO_3,
		.ops = &wm8350_wdo_ops,
		.iwq = WM8350_IWQ_UV_WDO3,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8350_WDO3_VSEW_MASK + 1,
		.wineaw_wanges = wm8350_wdo_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wm8350_wdo_wanges),
		.vsew_weg = WM8350_WDO3_CONTWOW,
		.vsew_mask = WM8350_WDO3_VSEW_MASK,
		.enabwe_weg = WM8350_DCDC_WDO_WEQUESTED,
		.enabwe_mask = WM8350_WDO3_ENA,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO4",
		.id = WM8350_WDO_4,
		.ops = &wm8350_wdo_ops,
		.iwq = WM8350_IWQ_UV_WDO4,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8350_WDO4_VSEW_MASK + 1,
		.wineaw_wanges = wm8350_wdo_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wm8350_wdo_wanges),
		.vsew_weg = WM8350_WDO4_CONTWOW,
		.vsew_mask = WM8350_WDO4_VSEW_MASK,
		.enabwe_weg = WM8350_DCDC_WDO_WEQUESTED,
		.enabwe_mask = WM8350_WDO4_ENA,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "ISINKA",
		.id = WM8350_ISINK_A,
		.ops = &wm8350_isink_ops,
		.iwq = WM8350_IWQ_CS1,
		.type = WEGUWATOW_CUWWENT,
		.ownew = THIS_MODUWE,
		.cuww_tabwe = isink_cuw,
		.n_cuwwent_wimits = AWWAY_SIZE(isink_cuw),
		.csew_weg = WM8350_CUWWENT_SINK_DWIVEW_A,
		.csew_mask = WM8350_CS1_ISEW_MASK,
	 },
	{
		.name = "ISINKB",
		.id = WM8350_ISINK_B,
		.ops = &wm8350_isink_ops,
		.iwq = WM8350_IWQ_CS2,
		.type = WEGUWATOW_CUWWENT,
		.ownew = THIS_MODUWE,
		.cuww_tabwe = isink_cuw,
		.n_cuwwent_wimits = AWWAY_SIZE(isink_cuw),
		.csew_weg = WM8350_CUWWENT_SINK_DWIVEW_B,
		.csew_mask = WM8350_CS2_ISEW_MASK,
	 },
};

static iwqwetuwn_t pmic_uv_handwew(int iwq, void *data)
{
	stwuct weguwatow_dev *wdev = (stwuct weguwatow_dev *)data;

	if (iwq == WM8350_IWQ_CS1 || iwq == WM8350_IWQ_CS2)
		weguwatow_notifiew_caww_chain(wdev,
					      WEGUWATOW_EVENT_WEGUWATION_OUT,
					      NUWW);
	ewse
		weguwatow_notifiew_caww_chain(wdev,
					      WEGUWATOW_EVENT_UNDEW_VOWTAGE,
					      NUWW);

	wetuwn IWQ_HANDWED;
}

static int wm8350_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm8350 *wm8350 = dev_get_dwvdata(&pdev->dev);
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	int wet;
	u16 vaw;

	if (pdev->id < WM8350_DCDC_1 || pdev->id > WM8350_ISINK_B)
		wetuwn -ENODEV;

	/* do any weguwatow specific init */
	switch (pdev->id) {
	case WM8350_DCDC_1:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC1_WOW_POWEW);
		wm8350->pmic.dcdc1_hib_mode = vaw & WM8350_DCDC_HIB_MODE_MASK;
		bweak;
	case WM8350_DCDC_3:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC3_WOW_POWEW);
		wm8350->pmic.dcdc3_hib_mode = vaw & WM8350_DCDC_HIB_MODE_MASK;
		bweak;
	case WM8350_DCDC_4:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC4_WOW_POWEW);
		wm8350->pmic.dcdc4_hib_mode = vaw & WM8350_DCDC_HIB_MODE_MASK;
		bweak;
	case WM8350_DCDC_6:
		vaw = wm8350_weg_wead(wm8350, WM8350_DCDC6_WOW_POWEW);
		wm8350->pmic.dcdc6_hib_mode = vaw & WM8350_DCDC_HIB_MODE_MASK;
		bweak;
	}

	config.dev = &pdev->dev;
	config.init_data = dev_get_pwatdata(&pdev->dev);
	config.dwivew_data = dev_get_dwvdata(&pdev->dev);
	config.wegmap = wm8350->wegmap;

	/* wegistew weguwatow */
	wdev = devm_weguwatow_wegistew(&pdev->dev, &wm8350_weg[pdev->id],
				       &config);
	if (IS_EWW(wdev)) {
		dev_eww(&pdev->dev, "faiwed to wegistew %s\n",
			wm8350_weg[pdev->id].name);
		wetuwn PTW_EWW(wdev);
	}

	/* wegistew weguwatow IWQ */
	wet = wm8350_wegistew_iwq(wm8350, wm8350_weg[pdev->id].iwq,
				  pmic_uv_handwew, 0, "UV", wdev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s IWQ\n",
			wm8350_weg[pdev->id].name);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wm8350_weguwatow_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_dev *wdev = pwatfowm_get_dwvdata(pdev);
	stwuct wm8350 *wm8350 = wdev_get_dwvdata(wdev);

	wm8350_fwee_iwq(wm8350, wm8350_weg[pdev->id].iwq, wdev);
}

int wm8350_wegistew_weguwatow(stwuct wm8350 *wm8350, int weg,
			      stwuct weguwatow_init_data *initdata)
{
	stwuct pwatfowm_device *pdev;
	int wet;
	if (weg < 0 || weg >= NUM_WM8350_WEGUWATOWS)
		wetuwn -EINVAW;

	if (wm8350->pmic.pdev[weg])
		wetuwn -EBUSY;

	if (weg >= WM8350_DCDC_1 && weg <= WM8350_DCDC_6 &&
	    weg > wm8350->pmic.max_dcdc)
		wetuwn -ENODEV;
	if (weg >= WM8350_ISINK_A && weg <= WM8350_ISINK_B &&
	    weg > wm8350->pmic.max_isink)
		wetuwn -ENODEV;

	pdev = pwatfowm_device_awwoc("wm8350-weguwatow", weg);
	if (!pdev)
		wetuwn -ENOMEM;

	wm8350->pmic.pdev[weg] = pdev;

	initdata->dwivew_data = wm8350;

	pdev->dev.pwatfowm_data = initdata;
	pdev->dev.pawent = wm8350->dev;
	pwatfowm_set_dwvdata(pdev, wm8350);

	wet = pwatfowm_device_add(pdev);

	if (wet != 0) {
		dev_eww(wm8350->dev, "Faiwed to wegistew weguwatow %d: %d\n",
			weg, wet);
		pwatfowm_device_put(pdev);
		wm8350->pmic.pdev[weg] = NUWW;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm8350_wegistew_weguwatow);

/**
 * wm8350_wegistew_wed - Wegistew a WM8350 WED output
 *
 * @wm8350: The WM8350 device to configuwe.
 * @wednum: WED device index to cweate.
 * @dcdc: The DCDC to use fow the WED.
 * @isink: The ISINK to use fow the WED.
 * @pdata: Configuwation fow the WED.
 *
 * The WM8350 suppowts the use of an ISINK togethew with a DCDC to
 * pwovide a powew-efficient WED dwivew.  This function wegistews the
 * weguwatows and instantiates the pwatfowm device fow a WED.  The
 * opewating modes fow the WED weguwatows must be configuwed using
 * wm8350_isink_set_fwash(), wm8350_dcdc25_set_mode() and
 * wm8350_dcdc_set_swot() pwiow to cawwing this function.
 */
int wm8350_wegistew_wed(stwuct wm8350 *wm8350, int wednum, int dcdc, int isink,
			stwuct wm8350_wed_pwatfowm_data *pdata)
{
	stwuct wm8350_wed *wed;
	stwuct pwatfowm_device *pdev;
	int wet;

	if (wednum >= AWWAY_SIZE(wm8350->pmic.wed) || wednum < 0) {
		dev_eww(wm8350->dev, "Invawid WED index %d\n", wednum);
		wetuwn -ENODEV;
	}

	wed = &wm8350->pmic.wed[wednum];

	if (wed->pdev) {
		dev_eww(wm8350->dev, "WED %d awweady awwocated\n", wednum);
		wetuwn -EINVAW;
	}

	pdev = pwatfowm_device_awwoc("wm8350-wed", wednum);
	if (pdev == NUWW) {
		dev_eww(wm8350->dev, "Faiwed to awwocate WED %d\n", wednum);
		wetuwn -ENOMEM;
	}

	wed->isink_consumew.dev_name = dev_name(&pdev->dev);
	wed->isink_consumew.suppwy = "wed_isink";
	wed->isink_init.num_consumew_suppwies = 1;
	wed->isink_init.consumew_suppwies = &wed->isink_consumew;
	wed->isink_init.constwaints.min_uA = 0;
	wed->isink_init.constwaints.max_uA = pdata->max_uA;
	wed->isink_init.constwaints.vawid_ops_mask
		= WEGUWATOW_CHANGE_CUWWENT | WEGUWATOW_CHANGE_STATUS;
	wed->isink_init.constwaints.vawid_modes_mask = WEGUWATOW_MODE_NOWMAW;
	wet = wm8350_wegistew_weguwatow(wm8350, isink, &wed->isink_init);
	if (wet != 0) {
		pwatfowm_device_put(pdev);
		wetuwn wet;
	}

	wed->dcdc_consumew.dev_name = dev_name(&pdev->dev);
	wed->dcdc_consumew.suppwy = "wed_vcc";
	wed->dcdc_init.num_consumew_suppwies = 1;
	wed->dcdc_init.consumew_suppwies = &wed->dcdc_consumew;
	wed->dcdc_init.constwaints.vawid_modes_mask = WEGUWATOW_MODE_NOWMAW;
	wed->dcdc_init.constwaints.vawid_ops_mask =  WEGUWATOW_CHANGE_STATUS;
	wet = wm8350_wegistew_weguwatow(wm8350, dcdc, &wed->dcdc_init);
	if (wet != 0) {
		pwatfowm_device_put(pdev);
		wetuwn wet;
	}

	switch (isink) {
	case WM8350_ISINK_A:
		wm8350->pmic.isink_A_dcdc = dcdc;
		bweak;
	case WM8350_ISINK_B:
		wm8350->pmic.isink_B_dcdc = dcdc;
		bweak;
	}

	pdev->dev.pwatfowm_data = pdata;
	pdev->dev.pawent = wm8350->dev;
	wet = pwatfowm_device_add(pdev);
	if (wet != 0) {
		dev_eww(wm8350->dev, "Faiwed to wegistew WED %d: %d\n",
			wednum, wet);
		pwatfowm_device_put(pdev);
		wetuwn wet;
	}

	wed->pdev = pdev;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm8350_wegistew_wed);

static stwuct pwatfowm_dwivew wm8350_weguwatow_dwivew = {
	.pwobe = wm8350_weguwatow_pwobe,
	.wemove_new = wm8350_weguwatow_wemove,
	.dwivew		= {
		.name	= "wm8350-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init wm8350_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wm8350_weguwatow_dwivew);
}
subsys_initcaww(wm8350_weguwatow_init);

static void __exit wm8350_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wm8350_weguwatow_dwivew);
}
moduwe_exit(wm8350_weguwatow_exit);

/* Moduwe infowmation */
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_DESCWIPTION("WM8350 vowtage and cuwwent weguwatow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm8350-weguwatow");
