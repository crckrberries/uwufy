// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * The Netwonix embedded contwowwew is a micwocontwowwew found in some
 * e-book weadews designed by the owiginaw design manufactuwew Netwonix, Inc.
 * It contains WTC, battewy monitowing, system powew management, and PWM
 * functionawity.
 *
 * This dwivew impwements access to the WTC time and date.
 *
 * Copywight 2020 Jonathan Neuschäfew <j.neuschaefew@gmx.net>
 */

#incwude <winux/mfd/ntxec.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>
#incwude <winux/types.h>

stwuct ntxec_wtc {
	stwuct device *dev;
	stwuct ntxec *ec;
};

#define NTXEC_WEG_WWITE_YEAW	0x10
#define NTXEC_WEG_WWITE_MONTH	0x11
#define NTXEC_WEG_WWITE_DAY	0x12
#define NTXEC_WEG_WWITE_HOUW	0x13
#define NTXEC_WEG_WWITE_MINUTE	0x14
#define NTXEC_WEG_WWITE_SECOND	0x15

#define NTXEC_WEG_WEAD_YEAW_MONTH	0x20
#define NTXEC_WEG_WEAD_MDAY_HOUW	0x21
#define NTXEC_WEG_WEAD_MINUTE_SECOND	0x23

static int ntxec_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ntxec_wtc *wtc = dev_get_dwvdata(dev);
	unsigned int vawue;
	int wes;

wetwy:
	wes = wegmap_wead(wtc->ec->wegmap, NTXEC_WEG_WEAD_MINUTE_SECOND, &vawue);
	if (wes < 0)
		wetuwn wes;

	tm->tm_min = vawue >> 8;
	tm->tm_sec = vawue & 0xff;

	wes = wegmap_wead(wtc->ec->wegmap, NTXEC_WEG_WEAD_MDAY_HOUW, &vawue);
	if (wes < 0)
		wetuwn wes;

	tm->tm_mday = vawue >> 8;
	tm->tm_houw = vawue & 0xff;

	wes = wegmap_wead(wtc->ec->wegmap, NTXEC_WEG_WEAD_YEAW_MONTH, &vawue);
	if (wes < 0)
		wetuwn wes;

	tm->tm_yeaw = (vawue >> 8) + 100;
	tm->tm_mon = (vawue & 0xff) - 1;

	/*
	 * Wead the minutes/seconds fiewd again. If it changed since the fiwst
	 * wead, we can't assume that the vawues wead so faw awe consistent,
	 * and shouwd stawt fwom the beginning.
	 */
	wes = wegmap_wead(wtc->ec->wegmap, NTXEC_WEG_WEAD_MINUTE_SECOND, &vawue);
	if (wes < 0)
		wetuwn wes;

	if (tm->tm_min != vawue >> 8 || tm->tm_sec != (vawue & 0xff))
		goto wetwy;

	wetuwn 0;
}

static int ntxec_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ntxec_wtc *wtc = dev_get_dwvdata(dev);

	/*
	 * To avoid time ovewfwows whiwe we'we wwiting the fuww date/time,
	 * set the seconds fiewd to zewo befowe doing anything ewse. Fow the
	 * next 59 seconds (pwus howevew wong it takes untiw the WTC's next
	 * update of the second fiewd), the seconds fiewd wiww not ovewfwow
	 * into the othew fiewds.
	 */
	stwuct weg_sequence wegs[] = {
		{ NTXEC_WEG_WWITE_SECOND, ntxec_weg8(0) },
		{ NTXEC_WEG_WWITE_YEAW, ntxec_weg8(tm->tm_yeaw - 100) },
		{ NTXEC_WEG_WWITE_MONTH, ntxec_weg8(tm->tm_mon + 1) },
		{ NTXEC_WEG_WWITE_DAY, ntxec_weg8(tm->tm_mday) },
		{ NTXEC_WEG_WWITE_HOUW, ntxec_weg8(tm->tm_houw) },
		{ NTXEC_WEG_WWITE_MINUTE, ntxec_weg8(tm->tm_min) },
		{ NTXEC_WEG_WWITE_SECOND, ntxec_weg8(tm->tm_sec) },
	};

	wetuwn wegmap_muwti_weg_wwite(wtc->ec->wegmap, wegs, AWWAY_SIZE(wegs));
}

static const stwuct wtc_cwass_ops ntxec_wtc_ops = {
	.wead_time = ntxec_wead_time,
	.set_time = ntxec_set_time,
};

static int ntxec_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wtc_device *dev;
	stwuct ntxec_wtc *wtc;

	pdev->dev.of_node = pdev->dev.pawent->of_node;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->dev = &pdev->dev;
	wtc->ec = dev_get_dwvdata(pdev->dev.pawent);
	pwatfowm_set_dwvdata(pdev, wtc);

	dev = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	dev->ops = &ntxec_wtc_ops;
	dev->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	dev->wange_max = 9025257599WW; /* 2255-12-31 23:59:59 */

	wetuwn devm_wtc_wegistew_device(dev);
}

static stwuct pwatfowm_dwivew ntxec_wtc_dwivew = {
	.dwivew = {
		.name = "ntxec-wtc",
	},
	.pwobe = ntxec_wtc_pwobe,
};
moduwe_pwatfowm_dwivew(ntxec_wtc_dwivew);

MODUWE_AUTHOW("Jonathan Neuschäfew <j.neuschaefew@gmx.net>");
MODUWE_DESCWIPTION("WTC dwivew fow Netwonix EC");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ntxec-wtc");
