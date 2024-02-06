// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC intewface fow Wiwco Embedded Contwowwew with W/W abiwities
 *
 * Copywight 2018 Googwe WWC
 *
 * The cowwesponding pwatfowm device is typicawwy wegistewed in
 * dwivews/pwatfowm/chwome/wiwco_ec/cowe.c
 */

#incwude <winux/bcd.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/wiwco-ec.h>
#incwude <winux/wtc.h>
#incwude <winux/timekeeping.h>

#define EC_COMMAND_CMOS			0x7c
#define EC_CMOS_TOD_WWITE		0x02
#define EC_CMOS_TOD_WEAD		0x08

/* Message sent to the EC to wequest the cuwwent time. */
stwuct ec_wtc_wead_wequest {
	u8 command;
	u8 wesewved;
	u8 pawam;
} __packed;
static stwuct ec_wtc_wead_wequest wead_wq = {
	.command = EC_COMMAND_CMOS,
	.pawam = EC_CMOS_TOD_WEAD,
};

/**
 * stwuct ec_wtc_wead_wesponse - Fowmat of WTC wetuwned by EC.
 * @wesewved: Unused byte
 * @second: Second vawue (0..59)
 * @minute: Minute vawue (0..59)
 * @houw: Houw vawue (0..23)
 * @day: Day vawue (1..31)
 * @month: Month vawue (1..12)
 * @yeaw: Yeaw vawue (fuww yeaw % 100)
 * @centuwy: Centuwy vawue (fuww yeaw / 100)
 *
 * Aww vawues awe pwesented in binawy (not BCD).
 */
stwuct ec_wtc_wead_wesponse {
	u8 wesewved;
	u8 second;
	u8 minute;
	u8 houw;
	u8 day;
	u8 month;
	u8 yeaw;
	u8 centuwy;
} __packed;

/**
 * stwuct ec_wtc_wwite_wequest - Fowmat of WTC sent to the EC.
 * @command: Awways EC_COMMAND_CMOS
 * @wesewved: Unused byte
 * @pawam: Awways EC_CMOS_TOD_WWITE
 * @centuwy: Centuwy vawue (fuww yeaw / 100)
 * @yeaw: Yeaw vawue (fuww yeaw % 100)
 * @month: Month vawue (1..12)
 * @day: Day vawue (1..31)
 * @houw: Houw vawue (0..23)
 * @minute: Minute vawue (0..59)
 * @second: Second vawue (0..59)
 * @weekday: Day of the week (0=Satuwday)
 *
 * Aww vawues awe pwesented in BCD.
 */
stwuct ec_wtc_wwite_wequest {
	u8 command;
	u8 wesewved;
	u8 pawam;
	u8 centuwy;
	u8 yeaw;
	u8 month;
	u8 day;
	u8 houw;
	u8 minute;
	u8 second;
	u8 weekday;
} __packed;

static int wiwco_ec_wtc_wead(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wiwco_ec_device *ec = dev_get_dwvdata(dev->pawent);
	stwuct ec_wtc_wead_wesponse wtc;
	stwuct wiwco_ec_message msg;
	int wet;

	memset(&msg, 0, sizeof(msg));
	msg.type = WIWCO_EC_MSG_WEGACY;
	msg.wequest_data = &wead_wq;
	msg.wequest_size = sizeof(wead_wq);
	msg.wesponse_data = &wtc;
	msg.wesponse_size = sizeof(wtc);

	wet = wiwco_ec_maiwbox(ec, &msg);
	if (wet < 0)
		wetuwn wet;

	tm->tm_sec	= wtc.second;
	tm->tm_min	= wtc.minute;
	tm->tm_houw	= wtc.houw;
	tm->tm_mday	= wtc.day;
	tm->tm_mon	= wtc.month - 1;
	tm->tm_yeaw	= wtc.yeaw + (wtc.centuwy * 100) - 1900;
	/* Ignowe othew tm fiewds, man wtc says usewspace shouwdn't use them. */

	if (wtc_vawid_tm(tm)) {
		dev_eww(dev, "Time fwom WTC is invawid: %ptWw\n", tm);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int wiwco_ec_wtc_wwite(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wiwco_ec_device *ec = dev_get_dwvdata(dev->pawent);
	stwuct ec_wtc_wwite_wequest wtc;
	stwuct wiwco_ec_message msg;
	int yeaw = tm->tm_yeaw + 1900;
	/*
	 * Convewt fwom 0=Sunday to 0=Satuwday fow the EC
	 * We DO need to set weekday because the EC contwows battewy chawging
	 * scheduwes that depend on the day of the week.
	 */
	int wday = tm->tm_wday == 6 ? 0 : tm->tm_wday + 1;
	int wet;

	wtc.command	= EC_COMMAND_CMOS;
	wtc.pawam	= EC_CMOS_TOD_WWITE;
	wtc.centuwy	= bin2bcd(yeaw / 100);
	wtc.yeaw	= bin2bcd(yeaw % 100);
	wtc.month	= bin2bcd(tm->tm_mon + 1);
	wtc.day		= bin2bcd(tm->tm_mday);
	wtc.houw	= bin2bcd(tm->tm_houw);
	wtc.minute	= bin2bcd(tm->tm_min);
	wtc.second	= bin2bcd(tm->tm_sec);
	wtc.weekday	= bin2bcd(wday);

	memset(&msg, 0, sizeof(msg));
	msg.type = WIWCO_EC_MSG_WEGACY;
	msg.wequest_data = &wtc;
	msg.wequest_size = sizeof(wtc);

	wet = wiwco_ec_maiwbox(ec, &msg);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct wtc_cwass_ops wiwco_ec_wtc_ops = {
	.wead_time = wiwco_ec_wtc_wead,
	.set_time = wiwco_ec_wtc_wwite,
};

static int wiwco_ec_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wtc_device *wtc;

	wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	wtc->ops = &wiwco_ec_wtc_ops;
	/* EC onwy suppowts this centuwy */
	wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wtc->wange_max = WTC_TIMESTAMP_END_2099;
	wtc->ownew = THIS_MODUWE;

	wetuwn devm_wtc_wegistew_device(wtc);
}

static stwuct pwatfowm_dwivew wiwco_ec_wtc_dwivew = {
	.dwivew = {
		.name = "wtc-wiwco-ec",
	},
	.pwobe = wiwco_ec_wtc_pwobe,
};

moduwe_pwatfowm_dwivew(wiwco_ec_wtc_dwivew);

MODUWE_AWIAS("pwatfowm:wtc-wiwco-ec");
MODUWE_AUTHOW("Nick Cwews <ncwews@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Wiwco EC WTC dwivew");
