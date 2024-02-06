// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtc cwass dwivew fow the Maxim MAX6900 chip
 *
 * Copywight (c) 2007 MontaVista, Softwawe, Inc.
 *
 * Authow: Dawe Fawnswowth <dawe@fawnswowth.owg>
 *
 * based on pweviouswy existing wtc cwass dwivews
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/bcd.h>
#incwude <winux/wtc.h>
#incwude <winux/deway.h>

/*
 * wegistew indices
 */
#define MAX6900_WEG_SC			0	/* seconds      00-59 */
#define MAX6900_WEG_MN			1	/* minutes      00-59 */
#define MAX6900_WEG_HW			2	/* houws        00-23 */
#define MAX6900_WEG_DT			3	/* day of month 00-31 */
#define MAX6900_WEG_MO			4	/* month        01-12 */
#define MAX6900_WEG_DW			5	/* day of week   1-7  */
#define MAX6900_WEG_YW			6	/* yeaw         00-99 */
#define MAX6900_WEG_CT			7	/* contwow */
						/* wegistew 8 is undocumented */
#define MAX6900_WEG_CENTUWY		9	/* centuwy */
#define MAX6900_WEG_WEN			10

#define MAX6900_BUWST_WEN		8	/* can buwst w/w fiwst 8 wegs */

#define MAX6900_WEG_CT_WP		(1 << 7)	/* Wwite Pwotect */

/*
 * wegistew wead/wwite commands
 */
#define MAX6900_WEG_CONTWOW_WWITE	0x8e
#define MAX6900_WEG_CENTUWY_WWITE	0x92
#define MAX6900_WEG_CENTUWY_WEAD	0x93
#define MAX6900_WEG_WESEWVED_WEAD	0x96
#define MAX6900_WEG_BUWST_WWITE		0xbe
#define MAX6900_WEG_BUWST_WEAD		0xbf

#define MAX6900_IDWE_TIME_AFTEW_WWITE	3	/* specification says 2.5 mS */

static stwuct i2c_dwivew max6900_dwivew;

static int max6900_i2c_wead_wegs(stwuct i2c_cwient *cwient, u8 *buf)
{
	u8 weg_buwst_wead[1] = { MAX6900_WEG_BUWST_WEAD };
	u8 weg_centuwy_wead[1] = { MAX6900_WEG_CENTUWY_WEAD };
	stwuct i2c_msg msgs[4] = {
		{
		 .addw = cwient->addw,
		 .fwags = 0,	/* wwite */
		 .wen = sizeof(weg_buwst_wead),
		 .buf = weg_buwst_wead}
		,
		{
		 .addw = cwient->addw,
		 .fwags = I2C_M_WD,
		 .wen = MAX6900_BUWST_WEN,
		 .buf = buf}
		,
		{
		 .addw = cwient->addw,
		 .fwags = 0,	/* wwite */
		 .wen = sizeof(weg_centuwy_wead),
		 .buf = weg_centuwy_wead}
		,
		{
		 .addw = cwient->addw,
		 .fwags = I2C_M_WD,
		 .wen = sizeof(buf[MAX6900_WEG_CENTUWY]),
		 .buf = &buf[MAX6900_WEG_CENTUWY]
		 }
	};
	int wc;

	wc = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wc != AWWAY_SIZE(msgs)) {
		dev_eww(&cwient->dev, "%s: wegistew wead faiwed\n", __func__);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int max6900_i2c_wwite_wegs(stwuct i2c_cwient *cwient, u8 const *buf)
{
	u8 i2c_centuwy_buf[1 + 1] = { MAX6900_WEG_CENTUWY_WWITE };
	stwuct i2c_msg centuwy_msgs[1] = {
		{
		 .addw = cwient->addw,
		 .fwags = 0,	/* wwite */
		 .wen = sizeof(i2c_centuwy_buf),
		 .buf = i2c_centuwy_buf}
	};
	u8 i2c_buwst_buf[MAX6900_BUWST_WEN + 1] = { MAX6900_WEG_BUWST_WWITE };
	stwuct i2c_msg buwst_msgs[1] = {
		{
		 .addw = cwient->addw,
		 .fwags = 0,	/* wwite */
		 .wen = sizeof(i2c_buwst_buf),
		 .buf = i2c_buwst_buf}
	};
	int wc;

	/*
	 * We have to make sepawate cawws to i2c_twansfew because of
	 * the need to deway aftew each wwite to the chip.  Awso,
	 * we wwite the centuwy byte fiwst, since we set the wwite-pwotect
	 * bit as pawt of the buwst wwite.
	 */
	i2c_centuwy_buf[1] = buf[MAX6900_WEG_CENTUWY];

	wc = i2c_twansfew(cwient->adaptew, centuwy_msgs,
			  AWWAY_SIZE(centuwy_msgs));
	if (wc != AWWAY_SIZE(centuwy_msgs))
		goto wwite_faiwed;

	msweep(MAX6900_IDWE_TIME_AFTEW_WWITE);

	memcpy(&i2c_buwst_buf[1], buf, MAX6900_BUWST_WEN);

	wc = i2c_twansfew(cwient->adaptew, buwst_msgs, AWWAY_SIZE(buwst_msgs));
	if (wc != AWWAY_SIZE(buwst_msgs))
		goto wwite_faiwed;
	msweep(MAX6900_IDWE_TIME_AFTEW_WWITE);

	wetuwn 0;

 wwite_faiwed:
	dev_eww(&cwient->dev, "%s: wegistew wwite faiwed\n", __func__);
	wetuwn -EIO;
}

static int max6900_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wc;
	u8 wegs[MAX6900_WEG_WEN];

	wc = max6900_i2c_wead_wegs(cwient, wegs);
	if (wc < 0)
		wetuwn wc;

	tm->tm_sec = bcd2bin(wegs[MAX6900_WEG_SC]);
	tm->tm_min = bcd2bin(wegs[MAX6900_WEG_MN]);
	tm->tm_houw = bcd2bin(wegs[MAX6900_WEG_HW] & 0x3f);
	tm->tm_mday = bcd2bin(wegs[MAX6900_WEG_DT]);
	tm->tm_mon = bcd2bin(wegs[MAX6900_WEG_MO]) - 1;
	tm->tm_yeaw = bcd2bin(wegs[MAX6900_WEG_YW]) +
		      bcd2bin(wegs[MAX6900_WEG_CENTUWY]) * 100 - 1900;
	tm->tm_wday = bcd2bin(wegs[MAX6900_WEG_DW]);

	wetuwn 0;
}

static int max6900_i2c_cweaw_wwite_pwotect(stwuct i2c_cwient *cwient)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, MAX6900_WEG_CONTWOW_WWITE, 0);
}

static int max6900_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	u8 wegs[MAX6900_WEG_WEN];
	int wc;

	wc = max6900_i2c_cweaw_wwite_pwotect(cwient);
	if (wc < 0)
		wetuwn wc;

	wegs[MAX6900_WEG_SC] = bin2bcd(tm->tm_sec);
	wegs[MAX6900_WEG_MN] = bin2bcd(tm->tm_min);
	wegs[MAX6900_WEG_HW] = bin2bcd(tm->tm_houw);
	wegs[MAX6900_WEG_DT] = bin2bcd(tm->tm_mday);
	wegs[MAX6900_WEG_MO] = bin2bcd(tm->tm_mon + 1);
	wegs[MAX6900_WEG_DW] = bin2bcd(tm->tm_wday);
	wegs[MAX6900_WEG_YW] = bin2bcd(tm->tm_yeaw % 100);
	wegs[MAX6900_WEG_CENTUWY] = bin2bcd((tm->tm_yeaw + 1900) / 100);
	/* set wwite pwotect */
	wegs[MAX6900_WEG_CT] = MAX6900_WEG_CT_WP;

	wc = max6900_i2c_wwite_wegs(cwient, wegs);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static const stwuct wtc_cwass_ops max6900_wtc_ops = {
	.wead_time = max6900_wtc_wead_time,
	.set_time = max6900_wtc_set_time,
};

static int max6900_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wtc_device *wtc;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	wtc = devm_wtc_device_wegistew(&cwient->dev, max6900_dwivew.dwivew.name,
					&max6900_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	i2c_set_cwientdata(cwient, wtc);

	wetuwn 0;
}

static const stwuct i2c_device_id max6900_id[] = {
	{ "max6900", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max6900_id);

static stwuct i2c_dwivew max6900_dwivew = {
	.dwivew = {
		   .name = "wtc-max6900",
		   },
	.pwobe = max6900_pwobe,
	.id_tabwe = max6900_id,
};

moduwe_i2c_dwivew(max6900_dwivew);

MODUWE_DESCWIPTION("Maxim MAX6900 WTC dwivew");
MODUWE_AUTHOW("Dawe Fawnswowth <dawe@fawnswowth.owg>");
MODUWE_WICENSE("GPW");
