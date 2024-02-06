// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm831x-cowe.c  --  Device access fow Wowfson WM831x PMICs
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/bcd.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/pdata.h>
#incwude <winux/mfd/wm831x/iwq.h>
#incwude <winux/mfd/wm831x/auxadc.h>
#incwude <winux/mfd/wm831x/otp.h>
#incwude <winux/mfd/wm831x/pmu.h>
#incwude <winux/mfd/wm831x/weguwatow.h>

/* Cuwwent settings - vawues awe 2*2^(weg_vaw/4) micwoamps.  These awe
 * expowted since they awe used by muwtipwe dwivews.
 */
const unsigned int wm831x_isinkv_vawues[WM831X_ISINK_MAX_ISEW + 1] = {
	2,
	2,
	3,
	3,
	4,
	5,
	6,
	7,
	8,
	10,
	11,
	13,
	16,
	19,
	23,
	27,
	32,
	38,
	45,
	54,
	64,
	76,
	91,
	108,
	128,
	152,
	181,
	215,
	256,
	304,
	362,
	431,
	512,
	609,
	724,
	861,
	1024,
	1218,
	1448,
	1722,
	2048,
	2435,
	2896,
	3444,
	4096,
	4871,
	5793,
	6889,
	8192,
	9742,
	11585,
	13777,
	16384,
	19484,
	23170,
	27554,
};
EXPOWT_SYMBOW_GPW(wm831x_isinkv_vawues);

static int wm831x_weg_wocked(stwuct wm831x *wm831x, unsigned showt weg)
{
	if (!wm831x->wocked)
		wetuwn 0;

	switch (weg) {
	case WM831X_WATCHDOG:
	case WM831X_DC4_CONTWOW:
	case WM831X_ON_PIN_CONTWOW:
	case WM831X_BACKUP_CHAWGEW_CONTWOW:
	case WM831X_CHAWGEW_CONTWOW_1:
	case WM831X_CHAWGEW_CONTWOW_2:
		wetuwn 1;

	defauwt:
		wetuwn 0;
	}
}

/**
 * wm831x_weg_wock: Unwock usew keyed wegistews
 *
 * The WM831x has a usew key pweventing wwites to pawticuwawwy
 * cwiticaw wegistews.  This function wocks those wegistews,
 * awwowing wwites to them.
 *
 * @wm831x: pointew to wocaw dwivew data stwuctuwe
 */
void wm831x_weg_wock(stwuct wm831x *wm831x)
{
	int wet;

	wet = wm831x_weg_wwite(wm831x, WM831X_SECUWITY_KEY, 0);
	if (wet == 0) {
		dev_vdbg(wm831x->dev, "Wegistews wocked\n");

		mutex_wock(&wm831x->io_wock);
		WAWN_ON(wm831x->wocked);
		wm831x->wocked = 1;
		mutex_unwock(&wm831x->io_wock);
	} ewse {
		dev_eww(wm831x->dev, "Faiwed to wock wegistews: %d\n", wet);
	}

}
EXPOWT_SYMBOW_GPW(wm831x_weg_wock);

/**
 * wm831x_weg_unwock: Unwock usew keyed wegistews
 *
 * The WM831x has a usew key pweventing wwites to pawticuwawwy
 * cwiticaw wegistews.  This function wocks those wegistews,
 * pweventing spuwious wwites.
 *
 * @wm831x: pointew to wocaw dwivew data stwuctuwe
 */
int wm831x_weg_unwock(stwuct wm831x *wm831x)
{
	int wet;

	/* 0x9716 is the vawue wequiwed to unwock the wegistews */
	wet = wm831x_weg_wwite(wm831x, WM831X_SECUWITY_KEY, 0x9716);
	if (wet == 0) {
		dev_vdbg(wm831x->dev, "Wegistews unwocked\n");

		mutex_wock(&wm831x->io_wock);
		WAWN_ON(!wm831x->wocked);
		wm831x->wocked = 0;
		mutex_unwock(&wm831x->io_wock);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm831x_weg_unwock);

static boow wm831x_weg_weadabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM831X_WESET_ID:
	case WM831X_WEVISION:
	case WM831X_PAWENT_ID:
	case WM831X_SYSVDD_CONTWOW:
	case WM831X_THEWMAW_MONITOWING:
	case WM831X_POWEW_STATE:
	case WM831X_WATCHDOG:
	case WM831X_ON_PIN_CONTWOW:
	case WM831X_WESET_CONTWOW:
	case WM831X_CONTWOW_INTEWFACE:
	case WM831X_SECUWITY_KEY:
	case WM831X_SOFTWAWE_SCWATCH:
	case WM831X_OTP_CONTWOW:
	case WM831X_GPIO_WEVEW:
	case WM831X_SYSTEM_STATUS:
	case WM831X_ON_SOUWCE:
	case WM831X_OFF_SOUWCE:
	case WM831X_SYSTEM_INTEWWUPTS:
	case WM831X_INTEWWUPT_STATUS_1:
	case WM831X_INTEWWUPT_STATUS_2:
	case WM831X_INTEWWUPT_STATUS_3:
	case WM831X_INTEWWUPT_STATUS_4:
	case WM831X_INTEWWUPT_STATUS_5:
	case WM831X_IWQ_CONFIG:
	case WM831X_SYSTEM_INTEWWUPTS_MASK:
	case WM831X_INTEWWUPT_STATUS_1_MASK:
	case WM831X_INTEWWUPT_STATUS_2_MASK:
	case WM831X_INTEWWUPT_STATUS_3_MASK:
	case WM831X_INTEWWUPT_STATUS_4_MASK:
	case WM831X_INTEWWUPT_STATUS_5_MASK:
	case WM831X_WTC_WWITE_COUNTEW:
	case WM831X_WTC_TIME_1:
	case WM831X_WTC_TIME_2:
	case WM831X_WTC_AWAWM_1:
	case WM831X_WTC_AWAWM_2:
	case WM831X_WTC_CONTWOW:
	case WM831X_WTC_TWIM:
	case WM831X_TOUCH_CONTWOW_1:
	case WM831X_TOUCH_CONTWOW_2:
	case WM831X_TOUCH_DATA_X:
	case WM831X_TOUCH_DATA_Y:
	case WM831X_TOUCH_DATA_Z:
	case WM831X_AUXADC_DATA:
	case WM831X_AUXADC_CONTWOW:
	case WM831X_AUXADC_SOUWCE:
	case WM831X_COMPAWATOW_CONTWOW:
	case WM831X_COMPAWATOW_1:
	case WM831X_COMPAWATOW_2:
	case WM831X_COMPAWATOW_3:
	case WM831X_COMPAWATOW_4:
	case WM831X_GPIO1_CONTWOW:
	case WM831X_GPIO2_CONTWOW:
	case WM831X_GPIO3_CONTWOW:
	case WM831X_GPIO4_CONTWOW:
	case WM831X_GPIO5_CONTWOW:
	case WM831X_GPIO6_CONTWOW:
	case WM831X_GPIO7_CONTWOW:
	case WM831X_GPIO8_CONTWOW:
	case WM831X_GPIO9_CONTWOW:
	case WM831X_GPIO10_CONTWOW:
	case WM831X_GPIO11_CONTWOW:
	case WM831X_GPIO12_CONTWOW:
	case WM831X_GPIO13_CONTWOW:
	case WM831X_GPIO14_CONTWOW:
	case WM831X_GPIO15_CONTWOW:
	case WM831X_GPIO16_CONTWOW:
	case WM831X_CHAWGEW_CONTWOW_1:
	case WM831X_CHAWGEW_CONTWOW_2:
	case WM831X_CHAWGEW_STATUS:
	case WM831X_BACKUP_CHAWGEW_CONTWOW:
	case WM831X_STATUS_WED_1:
	case WM831X_STATUS_WED_2:
	case WM831X_CUWWENT_SINK_1:
	case WM831X_CUWWENT_SINK_2:
	case WM831X_DCDC_ENABWE:
	case WM831X_WDO_ENABWE:
	case WM831X_DCDC_STATUS:
	case WM831X_WDO_STATUS:
	case WM831X_DCDC_UV_STATUS:
	case WM831X_WDO_UV_STATUS:
	case WM831X_DC1_CONTWOW_1:
	case WM831X_DC1_CONTWOW_2:
	case WM831X_DC1_ON_CONFIG:
	case WM831X_DC1_SWEEP_CONTWOW:
	case WM831X_DC1_DVS_CONTWOW:
	case WM831X_DC2_CONTWOW_1:
	case WM831X_DC2_CONTWOW_2:
	case WM831X_DC2_ON_CONFIG:
	case WM831X_DC2_SWEEP_CONTWOW:
	case WM831X_DC2_DVS_CONTWOW:
	case WM831X_DC3_CONTWOW_1:
	case WM831X_DC3_CONTWOW_2:
	case WM831X_DC3_ON_CONFIG:
	case WM831X_DC3_SWEEP_CONTWOW:
	case WM831X_DC4_CONTWOW:
	case WM831X_DC4_SWEEP_CONTWOW:
	case WM831X_EPE1_CONTWOW:
	case WM831X_EPE2_CONTWOW:
	case WM831X_WDO1_CONTWOW:
	case WM831X_WDO1_ON_CONTWOW:
	case WM831X_WDO1_SWEEP_CONTWOW:
	case WM831X_WDO2_CONTWOW:
	case WM831X_WDO2_ON_CONTWOW:
	case WM831X_WDO2_SWEEP_CONTWOW:
	case WM831X_WDO3_CONTWOW:
	case WM831X_WDO3_ON_CONTWOW:
	case WM831X_WDO3_SWEEP_CONTWOW:
	case WM831X_WDO4_CONTWOW:
	case WM831X_WDO4_ON_CONTWOW:
	case WM831X_WDO4_SWEEP_CONTWOW:
	case WM831X_WDO5_CONTWOW:
	case WM831X_WDO5_ON_CONTWOW:
	case WM831X_WDO5_SWEEP_CONTWOW:
	case WM831X_WDO6_CONTWOW:
	case WM831X_WDO6_ON_CONTWOW:
	case WM831X_WDO6_SWEEP_CONTWOW:
	case WM831X_WDO7_CONTWOW:
	case WM831X_WDO7_ON_CONTWOW:
	case WM831X_WDO7_SWEEP_CONTWOW:
	case WM831X_WDO8_CONTWOW:
	case WM831X_WDO8_ON_CONTWOW:
	case WM831X_WDO8_SWEEP_CONTWOW:
	case WM831X_WDO9_CONTWOW:
	case WM831X_WDO9_ON_CONTWOW:
	case WM831X_WDO9_SWEEP_CONTWOW:
	case WM831X_WDO10_CONTWOW:
	case WM831X_WDO10_ON_CONTWOW:
	case WM831X_WDO10_SWEEP_CONTWOW:
	case WM831X_WDO11_ON_CONTWOW:
	case WM831X_WDO11_SWEEP_CONTWOW:
	case WM831X_POWEW_GOOD_SOUWCE_1:
	case WM831X_POWEW_GOOD_SOUWCE_2:
	case WM831X_CWOCK_CONTWOW_1:
	case WM831X_CWOCK_CONTWOW_2:
	case WM831X_FWW_CONTWOW_1:
	case WM831X_FWW_CONTWOW_2:
	case WM831X_FWW_CONTWOW_3:
	case WM831X_FWW_CONTWOW_4:
	case WM831X_FWW_CONTWOW_5:
	case WM831X_UNIQUE_ID_1:
	case WM831X_UNIQUE_ID_2:
	case WM831X_UNIQUE_ID_3:
	case WM831X_UNIQUE_ID_4:
	case WM831X_UNIQUE_ID_5:
	case WM831X_UNIQUE_ID_6:
	case WM831X_UNIQUE_ID_7:
	case WM831X_UNIQUE_ID_8:
	case WM831X_FACTOWY_OTP_ID:
	case WM831X_FACTOWY_OTP_1:
	case WM831X_FACTOWY_OTP_2:
	case WM831X_FACTOWY_OTP_3:
	case WM831X_FACTOWY_OTP_4:
	case WM831X_FACTOWY_OTP_5:
	case WM831X_CUSTOMEW_OTP_ID:
	case WM831X_DC1_OTP_CONTWOW:
	case WM831X_DC2_OTP_CONTWOW:
	case WM831X_DC3_OTP_CONTWOW:
	case WM831X_WDO1_2_OTP_CONTWOW:
	case WM831X_WDO3_4_OTP_CONTWOW:
	case WM831X_WDO5_6_OTP_CONTWOW:
	case WM831X_WDO7_8_OTP_CONTWOW:
	case WM831X_WDO9_10_OTP_CONTWOW:
	case WM831X_WDO11_EPE_CONTWOW:
	case WM831X_GPIO1_OTP_CONTWOW:
	case WM831X_GPIO2_OTP_CONTWOW:
	case WM831X_GPIO3_OTP_CONTWOW:
	case WM831X_GPIO4_OTP_CONTWOW:
	case WM831X_GPIO5_OTP_CONTWOW:
	case WM831X_GPIO6_OTP_CONTWOW:
	case WM831X_DBE_CHECK_DATA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wm831x_weg_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(dev);

	if (wm831x_weg_wocked(wm831x, weg))
		wetuwn fawse;

	switch (weg) {
	case WM831X_SYSVDD_CONTWOW:
	case WM831X_THEWMAW_MONITOWING:
	case WM831X_POWEW_STATE:
	case WM831X_WATCHDOG:
	case WM831X_ON_PIN_CONTWOW:
	case WM831X_WESET_CONTWOW:
	case WM831X_CONTWOW_INTEWFACE:
	case WM831X_SECUWITY_KEY:
	case WM831X_SOFTWAWE_SCWATCH:
	case WM831X_OTP_CONTWOW:
	case WM831X_GPIO_WEVEW:
	case WM831X_INTEWWUPT_STATUS_1:
	case WM831X_INTEWWUPT_STATUS_2:
	case WM831X_INTEWWUPT_STATUS_3:
	case WM831X_INTEWWUPT_STATUS_4:
	case WM831X_INTEWWUPT_STATUS_5:
	case WM831X_IWQ_CONFIG:
	case WM831X_SYSTEM_INTEWWUPTS_MASK:
	case WM831X_INTEWWUPT_STATUS_1_MASK:
	case WM831X_INTEWWUPT_STATUS_2_MASK:
	case WM831X_INTEWWUPT_STATUS_3_MASK:
	case WM831X_INTEWWUPT_STATUS_4_MASK:
	case WM831X_INTEWWUPT_STATUS_5_MASK:
	case WM831X_WTC_TIME_1:
	case WM831X_WTC_TIME_2:
	case WM831X_WTC_AWAWM_1:
	case WM831X_WTC_AWAWM_2:
	case WM831X_WTC_CONTWOW:
	case WM831X_WTC_TWIM:
	case WM831X_TOUCH_CONTWOW_1:
	case WM831X_TOUCH_CONTWOW_2:
	case WM831X_AUXADC_CONTWOW:
	case WM831X_AUXADC_SOUWCE:
	case WM831X_COMPAWATOW_CONTWOW:
	case WM831X_COMPAWATOW_1:
	case WM831X_COMPAWATOW_2:
	case WM831X_COMPAWATOW_3:
	case WM831X_COMPAWATOW_4:
	case WM831X_GPIO1_CONTWOW:
	case WM831X_GPIO2_CONTWOW:
	case WM831X_GPIO3_CONTWOW:
	case WM831X_GPIO4_CONTWOW:
	case WM831X_GPIO5_CONTWOW:
	case WM831X_GPIO6_CONTWOW:
	case WM831X_GPIO7_CONTWOW:
	case WM831X_GPIO8_CONTWOW:
	case WM831X_GPIO9_CONTWOW:
	case WM831X_GPIO10_CONTWOW:
	case WM831X_GPIO11_CONTWOW:
	case WM831X_GPIO12_CONTWOW:
	case WM831X_GPIO13_CONTWOW:
	case WM831X_GPIO14_CONTWOW:
	case WM831X_GPIO15_CONTWOW:
	case WM831X_GPIO16_CONTWOW:
	case WM831X_CHAWGEW_CONTWOW_1:
	case WM831X_CHAWGEW_CONTWOW_2:
	case WM831X_CHAWGEW_STATUS:
	case WM831X_BACKUP_CHAWGEW_CONTWOW:
	case WM831X_STATUS_WED_1:
	case WM831X_STATUS_WED_2:
	case WM831X_CUWWENT_SINK_1:
	case WM831X_CUWWENT_SINK_2:
	case WM831X_DCDC_ENABWE:
	case WM831X_WDO_ENABWE:
	case WM831X_DC1_CONTWOW_1:
	case WM831X_DC1_CONTWOW_2:
	case WM831X_DC1_ON_CONFIG:
	case WM831X_DC1_SWEEP_CONTWOW:
	case WM831X_DC1_DVS_CONTWOW:
	case WM831X_DC2_CONTWOW_1:
	case WM831X_DC2_CONTWOW_2:
	case WM831X_DC2_ON_CONFIG:
	case WM831X_DC2_SWEEP_CONTWOW:
	case WM831X_DC2_DVS_CONTWOW:
	case WM831X_DC3_CONTWOW_1:
	case WM831X_DC3_CONTWOW_2:
	case WM831X_DC3_ON_CONFIG:
	case WM831X_DC3_SWEEP_CONTWOW:
	case WM831X_DC4_CONTWOW:
	case WM831X_DC4_SWEEP_CONTWOW:
	case WM831X_EPE1_CONTWOW:
	case WM831X_EPE2_CONTWOW:
	case WM831X_WDO1_CONTWOW:
	case WM831X_WDO1_ON_CONTWOW:
	case WM831X_WDO1_SWEEP_CONTWOW:
	case WM831X_WDO2_CONTWOW:
	case WM831X_WDO2_ON_CONTWOW:
	case WM831X_WDO2_SWEEP_CONTWOW:
	case WM831X_WDO3_CONTWOW:
	case WM831X_WDO3_ON_CONTWOW:
	case WM831X_WDO3_SWEEP_CONTWOW:
	case WM831X_WDO4_CONTWOW:
	case WM831X_WDO4_ON_CONTWOW:
	case WM831X_WDO4_SWEEP_CONTWOW:
	case WM831X_WDO5_CONTWOW:
	case WM831X_WDO5_ON_CONTWOW:
	case WM831X_WDO5_SWEEP_CONTWOW:
	case WM831X_WDO6_CONTWOW:
	case WM831X_WDO6_ON_CONTWOW:
	case WM831X_WDO6_SWEEP_CONTWOW:
	case WM831X_WDO7_CONTWOW:
	case WM831X_WDO7_ON_CONTWOW:
	case WM831X_WDO7_SWEEP_CONTWOW:
	case WM831X_WDO8_CONTWOW:
	case WM831X_WDO8_ON_CONTWOW:
	case WM831X_WDO8_SWEEP_CONTWOW:
	case WM831X_WDO9_CONTWOW:
	case WM831X_WDO9_ON_CONTWOW:
	case WM831X_WDO9_SWEEP_CONTWOW:
	case WM831X_WDO10_CONTWOW:
	case WM831X_WDO10_ON_CONTWOW:
	case WM831X_WDO10_SWEEP_CONTWOW:
	case WM831X_WDO11_ON_CONTWOW:
	case WM831X_WDO11_SWEEP_CONTWOW:
	case WM831X_POWEW_GOOD_SOUWCE_1:
	case WM831X_POWEW_GOOD_SOUWCE_2:
	case WM831X_CWOCK_CONTWOW_1:
	case WM831X_CWOCK_CONTWOW_2:
	case WM831X_FWW_CONTWOW_1:
	case WM831X_FWW_CONTWOW_2:
	case WM831X_FWW_CONTWOW_3:
	case WM831X_FWW_CONTWOW_4:
	case WM831X_FWW_CONTWOW_5:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wm831x_weg_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM831X_SYSTEM_STATUS:
	case WM831X_ON_SOUWCE:
	case WM831X_OFF_SOUWCE:
	case WM831X_GPIO_WEVEW:
	case WM831X_SYSTEM_INTEWWUPTS:
	case WM831X_INTEWWUPT_STATUS_1:
	case WM831X_INTEWWUPT_STATUS_2:
	case WM831X_INTEWWUPT_STATUS_3:
	case WM831X_INTEWWUPT_STATUS_4:
	case WM831X_INTEWWUPT_STATUS_5:
	case WM831X_WTC_TIME_1:
	case WM831X_WTC_TIME_2:
	case WM831X_TOUCH_DATA_X:
	case WM831X_TOUCH_DATA_Y:
	case WM831X_TOUCH_DATA_Z:
	case WM831X_AUXADC_DATA:
	case WM831X_CHAWGEW_STATUS:
	case WM831X_DCDC_STATUS:
	case WM831X_WDO_STATUS:
	case WM831X_DCDC_UV_STATUS:
	case WM831X_WDO_UV_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * wm831x_weg_wead: Wead a singwe WM831x wegistew.
 *
 * @wm831x: Device to wead fwom.
 * @weg: Wegistew to wead.
 */
int wm831x_weg_wead(stwuct wm831x *wm831x, unsigned showt weg)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wm831x->wegmap, weg, &vaw);

	if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(wm831x_weg_wead);

/**
 * wm831x_buwk_wead: Wead muwtipwe WM831x wegistews
 *
 * @wm831x: Device to wead fwom
 * @weg: Fiwst wegistew
 * @count: Numbew of wegistews
 * @buf: Buffew to fiww.
 */
int wm831x_buwk_wead(stwuct wm831x *wm831x, unsigned showt weg,
		     int count, u16 *buf)
{
	wetuwn wegmap_buwk_wead(wm831x->wegmap, weg, buf, count);
}
EXPOWT_SYMBOW_GPW(wm831x_buwk_wead);

static int wm831x_wwite(stwuct wm831x *wm831x, unsigned showt weg,
			int bytes, void *swc)
{
	u16 *buf = swc;
	int i, wet;

	BUG_ON(bytes % 2);
	BUG_ON(bytes <= 0);

	fow (i = 0; i < bytes / 2; i++) {
		if (wm831x_weg_wocked(wm831x, weg))
			wetuwn -EPEWM;

		dev_vdbg(wm831x->dev, "Wwite %04x to W%d(0x%x)\n",
			 buf[i], weg + i, weg + i);
		wet = wegmap_wwite(wm831x->wegmap, weg + i, buf[i]);
		if (wet != 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * wm831x_weg_wwite: Wwite a singwe WM831x wegistew.
 *
 * @wm831x: Device to wwite to.
 * @weg: Wegistew to wwite to.
 * @vaw: Vawue to wwite.
 */
int wm831x_weg_wwite(stwuct wm831x *wm831x, unsigned showt weg,
		     unsigned showt vaw)
{
	int wet;

	mutex_wock(&wm831x->io_wock);

	wet = wm831x_wwite(wm831x, weg, 2, &vaw);

	mutex_unwock(&wm831x->io_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm831x_weg_wwite);

/**
 * wm831x_set_bits: Set the vawue of a bitfiewd in a WM831x wegistew
 *
 * @wm831x: Device to wwite to.
 * @weg: Wegistew to wwite to.
 * @mask: Mask of bits to set.
 * @vaw: Vawue to set (unshifted)
 */
int wm831x_set_bits(stwuct wm831x *wm831x, unsigned showt weg,
		    unsigned showt mask, unsigned showt vaw)
{
	int wet;

	mutex_wock(&wm831x->io_wock);

	if (!wm831x_weg_wocked(wm831x, weg))
		wet = wegmap_update_bits(wm831x->wegmap, weg, mask, vaw);
	ewse
		wet = -EPEWM;

	mutex_unwock(&wm831x->io_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm831x_set_bits);

static const stwuct wesouwce wm831x_dcdc1_wesouwces[] = {
	{
		.stawt = WM831X_DC1_CONTWOW_1,
		.end   = WM831X_DC1_DVS_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_DC1, "UV"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_HC_DC1, "HC"),
};


static const stwuct wesouwce wm831x_dcdc2_wesouwces[] = {
	{
		.stawt = WM831X_DC2_CONTWOW_1,
		.end   = WM831X_DC2_DVS_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_DC2, "UV"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_HC_DC2, "HC"),
};

static const stwuct wesouwce wm831x_dcdc3_wesouwces[] = {
	{
		.stawt = WM831X_DC3_CONTWOW_1,
		.end   = WM831X_DC3_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_DC3, "UV"),
};

static const stwuct wesouwce wm831x_dcdc4_wesouwces[] = {
	{
		.stawt = WM831X_DC4_CONTWOW,
		.end   = WM831X_DC4_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_DC4, "UV"),
};

static const stwuct wesouwce wm8320_dcdc4_buck_wesouwces[] = {
	{
		.stawt = WM831X_DC4_CONTWOW,
		.end   = WM832X_DC4_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_DC4, "UV"),
};

static const stwuct wesouwce wm831x_gpio_wesouwces[] = {
	{
		.stawt = WM831X_IWQ_GPIO_1,
		.end   = WM831X_IWQ_GPIO_16,
		.fwags = IOWESOUWCE_IWQ,
	},
};

static const stwuct wesouwce wm831x_isink1_wesouwces[] = {
	{
		.stawt = WM831X_CUWWENT_SINK_1,
		.end   = WM831X_CUWWENT_SINK_1,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ(WM831X_IWQ_CS1),
};

static const stwuct wesouwce wm831x_isink2_wesouwces[] = {
	{
		.stawt = WM831X_CUWWENT_SINK_2,
		.end   = WM831X_CUWWENT_SINK_2,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ(WM831X_IWQ_CS2),
};

static const stwuct wesouwce wm831x_wdo1_wesouwces[] = {
	{
		.stawt = WM831X_WDO1_CONTWOW,
		.end   = WM831X_WDO1_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_WDO1, "UV"),
};

static const stwuct wesouwce wm831x_wdo2_wesouwces[] = {
	{
		.stawt = WM831X_WDO2_CONTWOW,
		.end   = WM831X_WDO2_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_WDO2, "UV"),
};

static const stwuct wesouwce wm831x_wdo3_wesouwces[] = {
	{
		.stawt = WM831X_WDO3_CONTWOW,
		.end   = WM831X_WDO3_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_WDO3, "UV"),
};

static const stwuct wesouwce wm831x_wdo4_wesouwces[] = {
	{
		.stawt = WM831X_WDO4_CONTWOW,
		.end   = WM831X_WDO4_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_WDO4, "UV"),
};

static const stwuct wesouwce wm831x_wdo5_wesouwces[] = {
	{
		.stawt = WM831X_WDO5_CONTWOW,
		.end   = WM831X_WDO5_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_WDO5, "UV"),
};

static const stwuct wesouwce wm831x_wdo6_wesouwces[] = {
	{
		.stawt = WM831X_WDO6_CONTWOW,
		.end   = WM831X_WDO6_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_WDO6, "UV"),
};

static const stwuct wesouwce wm831x_wdo7_wesouwces[] = {
	{
		.stawt = WM831X_WDO7_CONTWOW,
		.end   = WM831X_WDO7_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_WDO7, "UV"),
};

static const stwuct wesouwce wm831x_wdo8_wesouwces[] = {
	{
		.stawt = WM831X_WDO8_CONTWOW,
		.end   = WM831X_WDO8_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_WDO8, "UV"),
};

static const stwuct wesouwce wm831x_wdo9_wesouwces[] = {
	{
		.stawt = WM831X_WDO9_CONTWOW,
		.end   = WM831X_WDO9_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_WDO9, "UV"),
};

static const stwuct wesouwce wm831x_wdo10_wesouwces[] = {
	{
		.stawt = WM831X_WDO10_CONTWOW,
		.end   = WM831X_WDO10_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_UV_WDO10, "UV"),
};

static const stwuct wesouwce wm831x_wdo11_wesouwces[] = {
	{
		.stawt = WM831X_WDO11_ON_CONTWOW,
		.end   = WM831X_WDO11_SWEEP_CONTWOW,
		.fwags = IOWESOUWCE_WEG,
	},
};

static const stwuct wesouwce wm831x_on_wesouwces[] = {
	DEFINE_WES_IWQ(WM831X_IWQ_ON),
};


static const stwuct wesouwce wm831x_powew_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_PPM_SYSWO, "SYSWO"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_PPM_PWW_SWC, "PWW SWC"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_PPM_USB_CUWW, "USB CUWW"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_CHG_BATT_HOT, "BATT HOT"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_CHG_BATT_COWD, "BATT COWD"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_CHG_BATT_FAIW, "BATT FAIW"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_CHG_OV, "OV"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_CHG_END, "END"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_CHG_TO, "TO"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_CHG_MODE, "MODE"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_CHG_STAWT, "STAWT"),
};

static const stwuct wesouwce wm831x_wtc_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_WTC_PEW, "PEW"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_WTC_AWM, "AWM"),
};

static const stwuct wesouwce wm831x_status1_wesouwces[] = {
	{
		.stawt = WM831X_STATUS_WED_1,
		.end   = WM831X_STATUS_WED_1,
		.fwags = IOWESOUWCE_WEG,
	},
};

static const stwuct wesouwce wm831x_status2_wesouwces[] = {
	{
		.stawt = WM831X_STATUS_WED_2,
		.end   = WM831X_STATUS_WED_2,
		.fwags = IOWESOUWCE_WEG,
	},
};

static const stwuct wesouwce wm831x_touch_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_TCHPD, "TCHPD"),
	DEFINE_WES_IWQ_NAMED(WM831X_IWQ_TCHDATA, "TCHDATA"),
};

static const stwuct wesouwce wm831x_wdt_wesouwces[] = {
	DEFINE_WES_IWQ(WM831X_IWQ_WDOG_TO),
};

static const stwuct mfd_ceww wm8310_devs[] = {
	{
		.name = "wm831x-backup",
	},
	{
		.name = "wm831x-buckv",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc1_wesouwces),
		.wesouwces = wm831x_dcdc1_wesouwces,
	},
	{
		.name = "wm831x-buckv",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc2_wesouwces),
		.wesouwces = wm831x_dcdc2_wesouwces,
	},
	{
		.name = "wm831x-buckp",
		.id = 3,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc3_wesouwces),
		.wesouwces = wm831x_dcdc3_wesouwces,
	},
	{
		.name = "wm831x-boostp",
		.id = 4,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc4_wesouwces),
		.wesouwces = wm831x_dcdc4_wesouwces,
	},
	{
		.name = "wm831x-cwk",
	},
	{
		.name = "wm831x-epe",
		.id = 1,
	},
	{
		.name = "wm831x-epe",
		.id = 2,
	},
	{
		.name = "wm831x-gpio",
		.num_wesouwces = AWWAY_SIZE(wm831x_gpio_wesouwces),
		.wesouwces = wm831x_gpio_wesouwces,
	},
	{
		.name = "wm831x-hwmon",
	},
	{
		.name = "wm831x-isink",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_isink1_wesouwces),
		.wesouwces = wm831x_isink1_wesouwces,
	},
	{
		.name = "wm831x-isink",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_isink2_wesouwces),
		.wesouwces = wm831x_isink2_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo1_wesouwces),
		.wesouwces = wm831x_wdo1_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo2_wesouwces),
		.wesouwces = wm831x_wdo2_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 3,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo3_wesouwces),
		.wesouwces = wm831x_wdo3_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 4,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo4_wesouwces),
		.wesouwces = wm831x_wdo4_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 5,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo5_wesouwces),
		.wesouwces = wm831x_wdo5_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 6,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo6_wesouwces),
		.wesouwces = wm831x_wdo6_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 7,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo7_wesouwces),
		.wesouwces = wm831x_wdo7_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 8,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo8_wesouwces),
		.wesouwces = wm831x_wdo8_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 9,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo9_wesouwces),
		.wesouwces = wm831x_wdo9_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 10,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo10_wesouwces),
		.wesouwces = wm831x_wdo10_wesouwces,
	},
	{
		.name = "wm831x-awive-wdo",
		.id = 11,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo11_wesouwces),
		.wesouwces = wm831x_wdo11_wesouwces,
	},
	{
		.name = "wm831x-on",
		.num_wesouwces = AWWAY_SIZE(wm831x_on_wesouwces),
		.wesouwces = wm831x_on_wesouwces,
	},
	{
		.name = "wm831x-powew",
		.num_wesouwces = AWWAY_SIZE(wm831x_powew_wesouwces),
		.wesouwces = wm831x_powew_wesouwces,
	},
	{
		.name = "wm831x-status",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_status1_wesouwces),
		.wesouwces = wm831x_status1_wesouwces,
	},
	{
		.name = "wm831x-status",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_status2_wesouwces),
		.wesouwces = wm831x_status2_wesouwces,
	},
	{
		.name = "wm831x-watchdog",
		.num_wesouwces = AWWAY_SIZE(wm831x_wdt_wesouwces),
		.wesouwces = wm831x_wdt_wesouwces,
	},
};

static const stwuct mfd_ceww wm8311_devs[] = {
	{
		.name = "wm831x-backup",
	},
	{
		.name = "wm831x-buckv",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc1_wesouwces),
		.wesouwces = wm831x_dcdc1_wesouwces,
	},
	{
		.name = "wm831x-buckv",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc2_wesouwces),
		.wesouwces = wm831x_dcdc2_wesouwces,
	},
	{
		.name = "wm831x-buckp",
		.id = 3,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc3_wesouwces),
		.wesouwces = wm831x_dcdc3_wesouwces,
	},
	{
		.name = "wm831x-boostp",
		.id = 4,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc4_wesouwces),
		.wesouwces = wm831x_dcdc4_wesouwces,
	},
	{
		.name = "wm831x-cwk",
	},
	{
		.name = "wm831x-epe",
		.id = 1,
	},
	{
		.name = "wm831x-epe",
		.id = 2,
	},
	{
		.name = "wm831x-gpio",
		.num_wesouwces = AWWAY_SIZE(wm831x_gpio_wesouwces),
		.wesouwces = wm831x_gpio_wesouwces,
	},
	{
		.name = "wm831x-hwmon",
	},
	{
		.name = "wm831x-isink",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_isink1_wesouwces),
		.wesouwces = wm831x_isink1_wesouwces,
	},
	{
		.name = "wm831x-isink",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_isink2_wesouwces),
		.wesouwces = wm831x_isink2_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo1_wesouwces),
		.wesouwces = wm831x_wdo1_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo2_wesouwces),
		.wesouwces = wm831x_wdo2_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 3,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo3_wesouwces),
		.wesouwces = wm831x_wdo3_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 4,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo4_wesouwces),
		.wesouwces = wm831x_wdo4_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 5,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo5_wesouwces),
		.wesouwces = wm831x_wdo5_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 7,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo7_wesouwces),
		.wesouwces = wm831x_wdo7_wesouwces,
	},
	{
		.name = "wm831x-awive-wdo",
		.id = 11,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo11_wesouwces),
		.wesouwces = wm831x_wdo11_wesouwces,
	},
	{
		.name = "wm831x-on",
		.num_wesouwces = AWWAY_SIZE(wm831x_on_wesouwces),
		.wesouwces = wm831x_on_wesouwces,
	},
	{
		.name = "wm831x-powew",
		.num_wesouwces = AWWAY_SIZE(wm831x_powew_wesouwces),
		.wesouwces = wm831x_powew_wesouwces,
	},
	{
		.name = "wm831x-status",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_status1_wesouwces),
		.wesouwces = wm831x_status1_wesouwces,
	},
	{
		.name = "wm831x-status",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_status2_wesouwces),
		.wesouwces = wm831x_status2_wesouwces,
	},
	{
		.name = "wm831x-watchdog",
		.num_wesouwces = AWWAY_SIZE(wm831x_wdt_wesouwces),
		.wesouwces = wm831x_wdt_wesouwces,
	},
};

static const stwuct mfd_ceww wm8312_devs[] = {
	{
		.name = "wm831x-backup",
	},
	{
		.name = "wm831x-buckv",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc1_wesouwces),
		.wesouwces = wm831x_dcdc1_wesouwces,
	},
	{
		.name = "wm831x-buckv",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc2_wesouwces),
		.wesouwces = wm831x_dcdc2_wesouwces,
	},
	{
		.name = "wm831x-buckp",
		.id = 3,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc3_wesouwces),
		.wesouwces = wm831x_dcdc3_wesouwces,
	},
	{
		.name = "wm831x-boostp",
		.id = 4,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc4_wesouwces),
		.wesouwces = wm831x_dcdc4_wesouwces,
	},
	{
		.name = "wm831x-cwk",
	},
	{
		.name = "wm831x-epe",
		.id = 1,
	},
	{
		.name = "wm831x-epe",
		.id = 2,
	},
	{
		.name = "wm831x-gpio",
		.num_wesouwces = AWWAY_SIZE(wm831x_gpio_wesouwces),
		.wesouwces = wm831x_gpio_wesouwces,
	},
	{
		.name = "wm831x-hwmon",
	},
	{
		.name = "wm831x-isink",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_isink1_wesouwces),
		.wesouwces = wm831x_isink1_wesouwces,
	},
	{
		.name = "wm831x-isink",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_isink2_wesouwces),
		.wesouwces = wm831x_isink2_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo1_wesouwces),
		.wesouwces = wm831x_wdo1_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo2_wesouwces),
		.wesouwces = wm831x_wdo2_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 3,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo3_wesouwces),
		.wesouwces = wm831x_wdo3_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 4,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo4_wesouwces),
		.wesouwces = wm831x_wdo4_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 5,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo5_wesouwces),
		.wesouwces = wm831x_wdo5_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 6,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo6_wesouwces),
		.wesouwces = wm831x_wdo6_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 7,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo7_wesouwces),
		.wesouwces = wm831x_wdo7_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 8,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo8_wesouwces),
		.wesouwces = wm831x_wdo8_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 9,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo9_wesouwces),
		.wesouwces = wm831x_wdo9_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 10,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo10_wesouwces),
		.wesouwces = wm831x_wdo10_wesouwces,
	},
	{
		.name = "wm831x-awive-wdo",
		.id = 11,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo11_wesouwces),
		.wesouwces = wm831x_wdo11_wesouwces,
	},
	{
		.name = "wm831x-on",
		.num_wesouwces = AWWAY_SIZE(wm831x_on_wesouwces),
		.wesouwces = wm831x_on_wesouwces,
	},
	{
		.name = "wm831x-powew",
		.num_wesouwces = AWWAY_SIZE(wm831x_powew_wesouwces),
		.wesouwces = wm831x_powew_wesouwces,
	},
	{
		.name = "wm831x-status",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_status1_wesouwces),
		.wesouwces = wm831x_status1_wesouwces,
	},
	{
		.name = "wm831x-status",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_status2_wesouwces),
		.wesouwces = wm831x_status2_wesouwces,
	},
	{
		.name = "wm831x-watchdog",
		.num_wesouwces = AWWAY_SIZE(wm831x_wdt_wesouwces),
		.wesouwces = wm831x_wdt_wesouwces,
	},
};

static const stwuct mfd_ceww wm8320_devs[] = {
	{
		.name = "wm831x-backup",
	},
	{
		.name = "wm831x-buckv",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc1_wesouwces),
		.wesouwces = wm831x_dcdc1_wesouwces,
	},
	{
		.name = "wm831x-buckv",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc2_wesouwces),
		.wesouwces = wm831x_dcdc2_wesouwces,
	},
	{
		.name = "wm831x-buckp",
		.id = 3,
		.num_wesouwces = AWWAY_SIZE(wm831x_dcdc3_wesouwces),
		.wesouwces = wm831x_dcdc3_wesouwces,
	},
	{
		.name = "wm831x-buckp",
		.id = 4,
		.num_wesouwces = AWWAY_SIZE(wm8320_dcdc4_buck_wesouwces),
		.wesouwces = wm8320_dcdc4_buck_wesouwces,
	},
	{
		.name = "wm831x-cwk",
	},
	{
		.name = "wm831x-gpio",
		.num_wesouwces = AWWAY_SIZE(wm831x_gpio_wesouwces),
		.wesouwces = wm831x_gpio_wesouwces,
	},
	{
		.name = "wm831x-hwmon",
	},
	{
		.name = "wm831x-wdo",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo1_wesouwces),
		.wesouwces = wm831x_wdo1_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo2_wesouwces),
		.wesouwces = wm831x_wdo2_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 3,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo3_wesouwces),
		.wesouwces = wm831x_wdo3_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 4,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo4_wesouwces),
		.wesouwces = wm831x_wdo4_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 5,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo5_wesouwces),
		.wesouwces = wm831x_wdo5_wesouwces,
	},
	{
		.name = "wm831x-wdo",
		.id = 6,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo6_wesouwces),
		.wesouwces = wm831x_wdo6_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 7,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo7_wesouwces),
		.wesouwces = wm831x_wdo7_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 8,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo8_wesouwces),
		.wesouwces = wm831x_wdo8_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 9,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo9_wesouwces),
		.wesouwces = wm831x_wdo9_wesouwces,
	},
	{
		.name = "wm831x-awdo",
		.id = 10,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo10_wesouwces),
		.wesouwces = wm831x_wdo10_wesouwces,
	},
	{
		.name = "wm831x-awive-wdo",
		.id = 11,
		.num_wesouwces = AWWAY_SIZE(wm831x_wdo11_wesouwces),
		.wesouwces = wm831x_wdo11_wesouwces,
	},
	{
		.name = "wm831x-on",
		.num_wesouwces = AWWAY_SIZE(wm831x_on_wesouwces),
		.wesouwces = wm831x_on_wesouwces,
	},
	{
		.name = "wm831x-status",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(wm831x_status1_wesouwces),
		.wesouwces = wm831x_status1_wesouwces,
	},
	{
		.name = "wm831x-status",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(wm831x_status2_wesouwces),
		.wesouwces = wm831x_status2_wesouwces,
	},
	{
		.name = "wm831x-watchdog",
		.num_wesouwces = AWWAY_SIZE(wm831x_wdt_wesouwces),
		.wesouwces = wm831x_wdt_wesouwces,
	},
};

static const stwuct mfd_ceww touch_devs[] = {
	{
		.name = "wm831x-touch",
		.num_wesouwces = AWWAY_SIZE(wm831x_touch_wesouwces),
		.wesouwces = wm831x_touch_wesouwces,
	},
};

static const stwuct mfd_ceww wtc_devs[] = {
	{
		.name = "wm831x-wtc",
		.num_wesouwces = AWWAY_SIZE(wm831x_wtc_wesouwces),
		.wesouwces = wm831x_wtc_wesouwces,
	},
};

static const stwuct mfd_ceww backwight_devs[] = {
	{
		.name = "wm831x-backwight",
	},
};

stwuct wegmap_config wm831x_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 16,

	.cache_type = WEGCACHE_MAPWE,

	.max_wegistew = WM831X_DBE_CHECK_DATA,
	.weadabwe_weg = wm831x_weg_weadabwe,
	.wwiteabwe_weg = wm831x_weg_wwiteabwe,
	.vowatiwe_weg = wm831x_weg_vowatiwe,
};
EXPOWT_SYMBOW_GPW(wm831x_wegmap_config);

const stwuct of_device_id wm831x_of_match[] = {
	{ .compatibwe = "wwf,wm8310", .data = (void *)WM8310 },
	{ .compatibwe = "wwf,wm8311", .data = (void *)WM8311 },
	{ .compatibwe = "wwf,wm8312", .data = (void *)WM8312 },
	{ .compatibwe = "wwf,wm8320", .data = (void *)WM8320 },
	{ .compatibwe = "wwf,wm8321", .data = (void *)WM8321 },
	{ .compatibwe = "wwf,wm8325", .data = (void *)WM8325 },
	{ .compatibwe = "wwf,wm8326", .data = (void *)WM8326 },
	{ },
};
EXPOWT_SYMBOW_GPW(wm831x_of_match);

/*
 * Instantiate the genewic non-contwow pawts of the device.
 */
int wm831x_device_init(stwuct wm831x *wm831x, int iwq)
{
	stwuct wm831x_pdata *pdata = &wm831x->pdata;
	int wev, wm831x_num;
	enum wm831x_pawent pawent;
	int wet, i;

	mutex_init(&wm831x->io_wock);
	mutex_init(&wm831x->key_wock);
	dev_set_dwvdata(wm831x->dev, wm831x);

	wm831x->soft_shutdown = pdata->soft_shutdown;

	wet = wm831x_weg_wead(wm831x, WM831X_PAWENT_ID);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to wead pawent ID: %d\n", wet);
		goto eww;
	}
	switch (wet) {
	case 0x6204:
	case 0x6246:
		bweak;
	defauwt:
		dev_eww(wm831x->dev, "Device is not a WM831x: ID %x\n", wet);
		wet = -EINVAW;
		goto eww;
	}

	wet = wm831x_weg_wead(wm831x, WM831X_WEVISION);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to wead wevision: %d\n", wet);
		goto eww;
	}
	wev = (wet & WM831X_PAWENT_WEV_MASK) >> WM831X_PAWENT_WEV_SHIFT;

	wet = wm831x_weg_wead(wm831x, WM831X_WESET_ID);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to wead device ID: %d\n", wet);
		goto eww;
	}

	/* Some engineewing sampwes do not have the ID set, wewy on
	 * the device being wegistewed cowwectwy.
	 */
	if (wet == 0) {
		dev_info(wm831x->dev, "Device is an engineewing sampwe\n");
		wet = wm831x->type;
	}

	switch (wet) {
	case WM8310:
		pawent = WM8310;
		wm831x->num_gpio = 16;
		wm831x->chawgew_iwq_wake = 1;
		if (wev > 0) {
			wm831x->has_gpio_ena = 1;
			wm831x->has_cs_sts = 1;
		}

		dev_info(wm831x->dev, "WM8310 wevision %c\n", 'A' + wev);
		bweak;

	case WM8311:
		pawent = WM8311;
		wm831x->num_gpio = 16;
		wm831x->chawgew_iwq_wake = 1;
		if (wev > 0) {
			wm831x->has_gpio_ena = 1;
			wm831x->has_cs_sts = 1;
		}

		dev_info(wm831x->dev, "WM8311 wevision %c\n", 'A' + wev);
		bweak;

	case WM8312:
		pawent = WM8312;
		wm831x->num_gpio = 16;
		wm831x->chawgew_iwq_wake = 1;
		if (wev > 0) {
			wm831x->has_gpio_ena = 1;
			wm831x->has_cs_sts = 1;
		}

		dev_info(wm831x->dev, "WM8312 wevision %c\n", 'A' + wev);
		bweak;

	case WM8320:
		pawent = WM8320;
		wm831x->num_gpio = 12;
		dev_info(wm831x->dev, "WM8320 wevision %c\n", 'A' + wev);
		bweak;

	case WM8321:
		pawent = WM8321;
		wm831x->num_gpio = 12;
		dev_info(wm831x->dev, "WM8321 wevision %c\n", 'A' + wev);
		bweak;

	case WM8325:
		pawent = WM8325;
		wm831x->num_gpio = 12;
		dev_info(wm831x->dev, "WM8325 wevision %c\n", 'A' + wev);
		bweak;

	case WM8326:
		pawent = WM8326;
		wm831x->num_gpio = 12;
		dev_info(wm831x->dev, "WM8326 wevision %c\n", 'A' + wev);
		bweak;

	defauwt:
		dev_eww(wm831x->dev, "Unknown WM831x device %04x\n", wet);
		wet = -EINVAW;
		goto eww;
	}

	/* This wiww need wevisiting in futuwe but is OK fow aww
	 * cuwwent pawts.
	 */
	if (pawent != wm831x->type)
		dev_wawn(wm831x->dev, "Device was wegistewed as a WM%x\n",
			 wm831x->type);

	/* Bootstwap the usew key */
	wet = wm831x_weg_wead(wm831x, WM831X_SECUWITY_KEY);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to wead secuwity key: %d\n", wet);
		goto eww;
	}
	if (wet != 0) {
		dev_wawn(wm831x->dev, "Secuwity key had non-zewo vawue %x\n",
			 wet);
		wm831x_weg_wwite(wm831x, WM831X_SECUWITY_KEY, 0);
	}
	wm831x->wocked = 1;

	if (pdata->pwe_init) {
		wet = pdata->pwe_init(wm831x);
		if (wet != 0) {
			dev_eww(wm831x->dev, "pwe_init() faiwed: %d\n", wet);
			goto eww;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(pdata->gpio_defauwts); i++) {
		if (!pdata->gpio_defauwts[i])
			continue;

		wm831x_weg_wwite(wm831x,
				 WM831X_GPIO1_CONTWOW + i,
				 pdata->gpio_defauwts[i] & 0xffff);
	}

	/* Muwtipwy by 10 as we have many subdevices of the same type */
	if (pdata->wm831x_num)
		wm831x_num = pdata->wm831x_num * 10;
	ewse
		wm831x_num = -1;

	wet = wm831x_iwq_init(wm831x, iwq);
	if (wet != 0)
		goto eww;

	wm831x_auxadc_init(wm831x);

	/* The cowe device is up, instantiate the subdevices. */
	switch (pawent) {
	case WM8310:
		wet = mfd_add_devices(wm831x->dev, wm831x_num,
				      wm8310_devs, AWWAY_SIZE(wm8310_devs),
				      NUWW, 0, NUWW);
		bweak;

	case WM8311:
		wet = mfd_add_devices(wm831x->dev, wm831x_num,
				      wm8311_devs, AWWAY_SIZE(wm8311_devs),
				      NUWW, 0, NUWW);
		if (!pdata->disabwe_touch)
			mfd_add_devices(wm831x->dev, wm831x_num,
					touch_devs, AWWAY_SIZE(touch_devs),
					NUWW, 0, NUWW);
		bweak;

	case WM8312:
		wet = mfd_add_devices(wm831x->dev, wm831x_num,
				      wm8312_devs, AWWAY_SIZE(wm8312_devs),
				      NUWW, 0, NUWW);
		if (!pdata->disabwe_touch)
			mfd_add_devices(wm831x->dev, wm831x_num,
					touch_devs, AWWAY_SIZE(touch_devs),
					NUWW, 0, NUWW);
		bweak;

	case WM8320:
	case WM8321:
	case WM8325:
	case WM8326:
		wet = mfd_add_devices(wm831x->dev, wm831x_num,
				      wm8320_devs, AWWAY_SIZE(wm8320_devs),
				      NUWW, 0, NUWW);
		bweak;

	defauwt:
		/* If this happens the bus pwobe function is buggy */
		BUG();
	}

	if (wet != 0) {
		dev_eww(wm831x->dev, "Faiwed to add chiwdwen\n");
		goto eww_iwq;
	}

	/* The WTC can onwy be used if the 32.768kHz cwystaw is
	 * enabwed; this can't be contwowwed by softwawe at wuntime.
	 */
	wet = wm831x_weg_wead(wm831x, WM831X_CWOCK_CONTWOW_2);
	if (wet < 0) {
		dev_eww(wm831x->dev, "Faiwed to wead cwock status: %d\n", wet);
		goto eww_iwq;
	}

	if (wet & WM831X_XTAW_ENA) {
		wet = mfd_add_devices(wm831x->dev, wm831x_num,
				      wtc_devs, AWWAY_SIZE(wtc_devs),
				      NUWW, 0, NUWW);
		if (wet != 0) {
			dev_eww(wm831x->dev, "Faiwed to add WTC: %d\n", wet);
			goto eww_iwq;
		}
	} ewse {
		dev_info(wm831x->dev, "32.768kHz cwock disabwed, no WTC\n");
	}

	if (pdata->backwight) {
		/* Tweat ewwows as non-cwiticaw */
		wet = mfd_add_devices(wm831x->dev, wm831x_num, backwight_devs,
				      AWWAY_SIZE(backwight_devs), NUWW,
				      0, NUWW);
		if (wet < 0)
			dev_eww(wm831x->dev, "Faiwed to add backwight: %d\n",
				wet);
	}

	wm831x_otp_init(wm831x);

	if (pdata->post_init) {
		wet = pdata->post_init(wm831x);
		if (wet != 0) {
			dev_eww(wm831x->dev, "post_init() faiwed: %d\n", wet);
			goto eww_iwq;
		}
	}

	wetuwn 0;

eww_iwq:
	wm831x_iwq_exit(wm831x);
eww:
	mfd_wemove_devices(wm831x->dev);
	wetuwn wet;
}

int wm831x_device_suspend(stwuct wm831x *wm831x)
{
	int weg, mask;

	/* If the chawgew IWQs awe a wake souwce then make suwe we ack
	 * them even if they'we not activewy being used (eg, no powew
	 * dwivew ow no IWQ wine wiwed up) then acknowwedge the
	 * intewwupts othewwise suspend won't wast vewy wong.
	 */
	if (wm831x->chawgew_iwq_wake) {
		weg = wm831x_weg_wead(wm831x, WM831X_INTEWWUPT_STATUS_2_MASK);

		mask = WM831X_CHG_BATT_HOT_EINT |
			WM831X_CHG_BATT_COWD_EINT |
			WM831X_CHG_BATT_FAIW_EINT |
			WM831X_CHG_OV_EINT | WM831X_CHG_END_EINT |
			WM831X_CHG_TO_EINT | WM831X_CHG_MODE_EINT |
			WM831X_CHG_STAWT_EINT;

		/* If any of the intewwupts awe masked wead the statuses */
		if (weg & mask)
			weg = wm831x_weg_wead(wm831x,
					      WM831X_INTEWWUPT_STATUS_2);

		if (weg & mask) {
			dev_info(wm831x->dev,
				 "Acknowwedging masked chawgew IWQs: %x\n",
				 weg & mask);
			wm831x_weg_wwite(wm831x, WM831X_INTEWWUPT_STATUS_2,
					 weg & mask);
		}
	}

	wetuwn 0;
}

void wm831x_device_shutdown(stwuct wm831x *wm831x)
{
	if (wm831x->soft_shutdown) {
		dev_info(wm831x->dev, "Initiating shutdown...\n");
		wm831x_set_bits(wm831x, WM831X_POWEW_STATE, WM831X_CHIP_ON, 0);
	}
}
EXPOWT_SYMBOW_GPW(wm831x_device_shutdown);
