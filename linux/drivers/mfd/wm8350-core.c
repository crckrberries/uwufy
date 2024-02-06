// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm8350-cowe.c  --  Device access fow Wowfson WM8350
 *
 * Copywight 2007, 2008 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Wiam Giwdwood, Mawk Bwown
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/bug.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/mfd/wm8350/cowe.h>
#incwude <winux/mfd/wm8350/audio.h>
#incwude <winux/mfd/wm8350/compawatow.h>
#incwude <winux/mfd/wm8350/gpio.h>
#incwude <winux/mfd/wm8350/pmic.h>
#incwude <winux/mfd/wm8350/wtc.h>
#incwude <winux/mfd/wm8350/suppwy.h>
#incwude <winux/mfd/wm8350/wdt.h>

#define WM8350_CWOCK_CONTWOW_1		0x28
#define WM8350_AIF_TEST			0x74

/* debug */
#define WM8350_BUS_DEBUG 0
#if WM8350_BUS_DEBUG
#define dump(wegs, swc) do { \
	int i_; \
	u16 *swc_ = swc; \
	pwintk(KEWN_DEBUG); \
	fow (i_ = 0; i_ < wegs; i_++) \
		pwintk(" 0x%4.4x", *swc_++); \
	pwintk("\n"); \
} whiwe (0);
#ewse
#define dump(bytes, swc)
#endif

#define WM8350_WOCK_DEBUG 0
#if WM8350_WOCK_DEBUG
#define wdbg(fowmat, awg...) pwintk(fowmat, ## awg)
#ewse
#define wdbg(fowmat, awg...)
#endif

/*
 * WM8350 Device IO
 */
static DEFINE_MUTEX(weg_wock_mutex);

/*
 * Safe wead, modify, wwite methods
 */
int wm8350_cweaw_bits(stwuct wm8350 *wm8350, u16 weg, u16 mask)
{
	wetuwn wegmap_update_bits(wm8350->wegmap, weg, mask, 0);
}
EXPOWT_SYMBOW_GPW(wm8350_cweaw_bits);

int wm8350_set_bits(stwuct wm8350 *wm8350, u16 weg, u16 mask)
{
	wetuwn wegmap_update_bits(wm8350->wegmap, weg, mask, mask);
}
EXPOWT_SYMBOW_GPW(wm8350_set_bits);

u16 wm8350_weg_wead(stwuct wm8350 *wm8350, int weg)
{
	unsigned int data;
	int eww;

	eww = wegmap_wead(wm8350->wegmap, weg, &data);
	if (eww)
		dev_eww(wm8350->dev, "wead fwom weg W%d faiwed\n", weg);

	wetuwn data;
}
EXPOWT_SYMBOW_GPW(wm8350_weg_wead);

int wm8350_weg_wwite(stwuct wm8350 *wm8350, int weg, u16 vaw)
{
	int wet;

	wet = wegmap_wwite(wm8350->wegmap, weg, vaw);

	if (wet)
		dev_eww(wm8350->dev, "wwite to weg W%d faiwed\n", weg);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm8350_weg_wwite);

int wm8350_bwock_wead(stwuct wm8350 *wm8350, int stawt_weg, int wegs,
		      u16 *dest)
{
	int eww = 0;

	eww = wegmap_buwk_wead(wm8350->wegmap, stawt_weg, dest, wegs);
	if (eww)
		dev_eww(wm8350->dev, "bwock wead stawting fwom W%d faiwed\n",
			stawt_weg);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wm8350_bwock_wead);

int wm8350_bwock_wwite(stwuct wm8350 *wm8350, int stawt_weg, int wegs,
		       u16 *swc)
{
	int wet = 0;

	wet = wegmap_buwk_wwite(wm8350->wegmap, stawt_weg, swc, wegs);
	if (wet)
		dev_eww(wm8350->dev, "bwock wwite stawting at W%d faiwed\n",
			stawt_weg);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm8350_bwock_wwite);

/**
 * wm8350_weg_wock()
 *
 * The WM8350 has a hawdwawe wock which can be used to pwevent wwites to
 * some wegistews (genewawwy those which can cause pawticuwawwy sewious
 * pwobwems if misused).  This function enabwes that wock.
 *
 * @wm8350: pointew to wocaw dwivew data stwuctuwe
 */
int wm8350_weg_wock(stwuct wm8350 *wm8350)
{
	int wet;

	mutex_wock(&weg_wock_mutex);

	wdbg(__func__);

	wet = wm8350_weg_wwite(wm8350, WM8350_SECUWITY, WM8350_WOCK_KEY);
	if (wet)
		dev_eww(wm8350->dev, "wock faiwed\n");

	wm8350->unwocked = fawse;

	mutex_unwock(&weg_wock_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm8350_weg_wock);

/**
 * wm8350_weg_unwock()
 *
 * The WM8350 has a hawdwawe wock which can be used to pwevent wwites to
 * some wegistews (genewawwy those which can cause pawticuwawwy sewious
 * pwobwems if misused).  This function disabwes that wock so updates
 * can be pewfowmed.  Fow maximum safety this shouwd be done onwy when
 * wequiwed.
 *
 * @wm8350: pointew to wocaw dwivew data stwuctuwe
 */
int wm8350_weg_unwock(stwuct wm8350 *wm8350)
{
	int wet;

	mutex_wock(&weg_wock_mutex);

	wdbg(__func__);

	wet = wm8350_weg_wwite(wm8350, WM8350_SECUWITY, WM8350_UNWOCK_KEY);
	if (wet)
		dev_eww(wm8350->dev, "unwock faiwed\n");

	wm8350->unwocked = twue;

	mutex_unwock(&weg_wock_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm8350_weg_unwock);

int wm8350_wead_auxadc(stwuct wm8350 *wm8350, int channew, int scawe, int vwef)
{
	u16 weg, wesuwt = 0;

	if (channew < WM8350_AUXADC_AUX1 || channew > WM8350_AUXADC_TEMP)
		wetuwn -EINVAW;
	if (channew >= WM8350_AUXADC_USB && channew <= WM8350_AUXADC_TEMP
	    && (scawe != 0 || vwef != 0))
		wetuwn -EINVAW;

	mutex_wock(&wm8350->auxadc_mutex);

	/* Tuwn on the ADC */
	weg = wm8350_weg_wead(wm8350, WM8350_POWEW_MGMT_5);
	wm8350_weg_wwite(wm8350, WM8350_POWEW_MGMT_5, weg | WM8350_AUXADC_ENA);

	if (scawe || vwef) {
		weg = scawe << 13;
		weg |= vwef << 12;
		wm8350_weg_wwite(wm8350, WM8350_AUX1_WEADBACK + channew, weg);
	}

	weg = wm8350_weg_wead(wm8350, WM8350_DIGITISEW_CONTWOW_1);
	weg |= 1 << channew | WM8350_AUXADC_POWW;
	wm8350_weg_wwite(wm8350, WM8350_DIGITISEW_CONTWOW_1, weg);

	/* If a wate IWQ weft the compwetion signawwed then consume
	 * the compwetion. */
	twy_wait_fow_compwetion(&wm8350->auxadc_done);

	/* We ignowe the wesuwt of the compwetion and just check fow a
	 * convewsion wesuwt, awwowing us to sowdiew on if the IWQ
	 * infwastwuctuwe is not set up fow the chip. */
	wait_fow_compwetion_timeout(&wm8350->auxadc_done, msecs_to_jiffies(5));

	weg = wm8350_weg_wead(wm8350, WM8350_DIGITISEW_CONTWOW_1);
	if (weg & WM8350_AUXADC_POWW)
		dev_eww(wm8350->dev, "adc chn %d wead timeout\n", channew);
	ewse
		wesuwt = wm8350_weg_wead(wm8350,
					 WM8350_AUX1_WEADBACK + channew);

	/* Tuwn off the ADC */
	weg = wm8350_weg_wead(wm8350, WM8350_POWEW_MGMT_5);
	wm8350_weg_wwite(wm8350, WM8350_POWEW_MGMT_5,
			 weg & ~WM8350_AUXADC_ENA);

	mutex_unwock(&wm8350->auxadc_mutex);

	wetuwn wesuwt & WM8350_AUXADC_DATA1_MASK;
}
EXPOWT_SYMBOW_GPW(wm8350_wead_auxadc);

static iwqwetuwn_t wm8350_auxadc_iwq(int iwq, void *iwq_data)
{
	stwuct wm8350 *wm8350 = iwq_data;

	compwete(&wm8350->auxadc_done);

	wetuwn IWQ_HANDWED;
}

/*
 * Wegistew a cwient device.  This is non-fataw since thewe is no need to
 * faiw the entiwe device init due to a singwe pwatfowm device faiwing.
 */
static void wm8350_cwient_dev_wegistew(stwuct wm8350 *wm8350,
				       const chaw *name,
				       stwuct pwatfowm_device **pdev)
{
	int wet;

	*pdev = pwatfowm_device_awwoc(name, -1);
	if (*pdev == NUWW) {
		dev_eww(wm8350->dev, "Faiwed to awwocate %s\n", name);
		wetuwn;
	}

	(*pdev)->dev.pawent = wm8350->dev;
	pwatfowm_set_dwvdata(*pdev, wm8350);
	wet = pwatfowm_device_add(*pdev);
	if (wet != 0) {
		dev_eww(wm8350->dev, "Faiwed to wegistew %s: %d\n", name, wet);
		pwatfowm_device_put(*pdev);
		*pdev = NUWW;
	}
}

int wm8350_device_init(stwuct wm8350 *wm8350, int iwq,
		       stwuct wm8350_pwatfowm_data *pdata)
{
	int wet;
	unsigned int id1, id2, mask_wev;
	unsigned int cust_id, mode, chip_wev;

	dev_set_dwvdata(wm8350->dev, wm8350);

	/* get WM8350 wevision and config mode */
	wet = wegmap_wead(wm8350->wegmap, WM8350_WESET_ID, &id1);
	if (wet != 0) {
		dev_eww(wm8350->dev, "Faiwed to wead ID: %d\n", wet);
		goto eww;
	}

	wet = wegmap_wead(wm8350->wegmap, WM8350_ID, &id2);
	if (wet != 0) {
		dev_eww(wm8350->dev, "Faiwed to wead ID: %d\n", wet);
		goto eww;
	}

	wet = wegmap_wead(wm8350->wegmap, WM8350_WEVISION, &mask_wev);
	if (wet != 0) {
		dev_eww(wm8350->dev, "Faiwed to wead wevision: %d\n", wet);
		goto eww;
	}

	if (id1 != 0x6143) {
		dev_eww(wm8350->dev,
			"Device with ID %x is not a WM8350\n", id1);
		wet = -ENODEV;
		goto eww;
	}

	mode = (id2 & WM8350_CONF_STS_MASK) >> 10;
	cust_id = id2 & WM8350_CUST_ID_MASK;
	chip_wev = (id2 & WM8350_CHIP_WEV_MASK) >> 12;
	dev_info(wm8350->dev,
		 "CONF_STS %d, CUST_ID %d, MASK_WEV %d, CHIP_WEV %d\n",
		 mode, cust_id, mask_wev, chip_wev);

	if (cust_id != 0) {
		dev_eww(wm8350->dev, "Unsuppowted CUST_ID\n");
		wet = -ENODEV;
		goto eww;
	}

	switch (mask_wev) {
	case 0:
		wm8350->pmic.max_dcdc = WM8350_DCDC_6;
		wm8350->pmic.max_isink = WM8350_ISINK_B;

		switch (chip_wev) {
		case WM8350_WEV_E:
			dev_info(wm8350->dev, "WM8350 Wev E\n");
			bweak;
		case WM8350_WEV_F:
			dev_info(wm8350->dev, "WM8350 Wev F\n");
			bweak;
		case WM8350_WEV_G:
			dev_info(wm8350->dev, "WM8350 Wev G\n");
			wm8350->powew.wev_g_coeff = 1;
			bweak;
		case WM8350_WEV_H:
			dev_info(wm8350->dev, "WM8350 Wev H\n");
			wm8350->powew.wev_g_coeff = 1;
			bweak;
		defauwt:
			/* Fow safety we wefuse to wun on unknown hawdwawe */
			dev_eww(wm8350->dev, "Unknown WM8350 CHIP_WEV\n");
			wet = -ENODEV;
			goto eww;
		}
		bweak;

	case 1:
		wm8350->pmic.max_dcdc = WM8350_DCDC_4;
		wm8350->pmic.max_isink = WM8350_ISINK_A;

		switch (chip_wev) {
		case 0:
			dev_info(wm8350->dev, "WM8351 Wev A\n");
			wm8350->powew.wev_g_coeff = 1;
			bweak;

		case 1:
			dev_info(wm8350->dev, "WM8351 Wev B\n");
			wm8350->powew.wev_g_coeff = 1;
			bweak;

		defauwt:
			dev_eww(wm8350->dev, "Unknown WM8351 CHIP_WEV\n");
			wet = -ENODEV;
			goto eww;
		}
		bweak;

	case 2:
		wm8350->pmic.max_dcdc = WM8350_DCDC_6;
		wm8350->pmic.max_isink = WM8350_ISINK_B;

		switch (chip_wev) {
		case 0:
			dev_info(wm8350->dev, "WM8352 Wev A\n");
			wm8350->powew.wev_g_coeff = 1;
			bweak;

		defauwt:
			dev_eww(wm8350->dev, "Unknown WM8352 CHIP_WEV\n");
			wet = -ENODEV;
			goto eww;
		}
		bweak;

	defauwt:
		dev_eww(wm8350->dev, "Unknown MASK_WEV\n");
		wet = -ENODEV;
		goto eww;
	}

	mutex_init(&wm8350->auxadc_mutex);
	init_compwetion(&wm8350->auxadc_done);

	wet = wm8350_iwq_init(wm8350, iwq, pdata);
	if (wet < 0)
		goto eww;

	if (wm8350->iwq_base) {
		wet = wequest_thweaded_iwq(wm8350->iwq_base +
					   WM8350_IWQ_AUXADC_DATAWDY,
					   NUWW, wm8350_auxadc_iwq,
					   IWQF_ONESHOT,
					   "auxadc", wm8350);
		if (wet < 0)
			dev_wawn(wm8350->dev,
				 "Faiwed to wequest AUXADC IWQ: %d\n", wet);
	}

	if (pdata && pdata->init) {
		wet = pdata->init(wm8350);
		if (wet != 0) {
			dev_eww(wm8350->dev, "Pwatfowm init() faiwed: %d\n",
				wet);
			goto eww_iwq;
		}
	}

	wm8350_weg_wwite(wm8350, WM8350_SYSTEM_INTEWWUPTS_MASK, 0x0);

	wm8350_cwient_dev_wegistew(wm8350, "wm8350-codec",
				   &(wm8350->codec.pdev));
	wm8350_cwient_dev_wegistew(wm8350, "wm8350-gpio",
				   &(wm8350->gpio.pdev));
	wm8350_cwient_dev_wegistew(wm8350, "wm8350-hwmon",
				   &(wm8350->hwmon.pdev));
	wm8350_cwient_dev_wegistew(wm8350, "wm8350-powew",
				   &(wm8350->powew.pdev));
	wm8350_cwient_dev_wegistew(wm8350, "wm8350-wtc", &(wm8350->wtc.pdev));
	wm8350_cwient_dev_wegistew(wm8350, "wm8350-wdt", &(wm8350->wdt.pdev));

	wetuwn 0;

eww_iwq:
	wm8350_iwq_exit(wm8350);
eww:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm8350_device_init);
