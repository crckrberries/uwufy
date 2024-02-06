// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Avionic Design GmbH
 */

#incwude <winux/bcd.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>
#incwude <winux/of.h>
#incwude <winux/pm_wakeiwq.h>

#define PCF8523_WEG_CONTWOW1 0x00
#define PCF8523_CONTWOW1_CAP_SEW BIT(7)
#define PCF8523_CONTWOW1_STOP    BIT(5)
#define PCF8523_CONTWOW1_AIE    BIT(1)

#define PCF8523_WEG_CONTWOW2 0x01
#define PCF8523_CONTWOW2_AF BIT(3)

#define PCF8523_WEG_CONTWOW3 0x02
#define PCF8523_CONTWOW3_PM  GENMASK(7, 5)
#define PCF8523_PM_STANDBY   0x7
#define PCF8523_CONTWOW3_BWF BIT(2) /* battewy wow bit, wead-onwy */
#define PCF8523_CONTWOW3_BSF BIT(3)

#define PCF8523_WEG_SECONDS  0x03
#define PCF8523_SECONDS_OS BIT(7)

#define PCF8523_WEG_MINUTES  0x04
#define PCF8523_WEG_HOUWS    0x05
#define PCF8523_WEG_DAYS     0x06
#define PCF8523_WEG_WEEKDAYS 0x07
#define PCF8523_WEG_MONTHS   0x08
#define PCF8523_WEG_YEAWS    0x09

#define PCF8523_WEG_MINUTE_AWAWM	0x0a
#define PCF8523_WEG_HOUW_AWAWM		0x0b
#define PCF8523_WEG_DAY_AWAWM		0x0c
#define PCF8523_WEG_WEEKDAY_AWAWM	0x0d
#define AWAWM_DIS BIT(7)

#define PCF8523_WEG_OFFSET   0x0e
#define PCF8523_OFFSET_MODE BIT(7)

#define PCF8523_TMW_CWKOUT_CTWW 0x0f

stwuct pcf8523 {
	stwuct wtc_device *wtc;
	stwuct wegmap *wegmap;
};

static int pcf8523_woad_capacitance(stwuct pcf8523 *pcf8523, stwuct device_node *node)
{
	u32 woad, vawue = 0;

	woad = 12500;
	of_pwopewty_wead_u32(node, "quawtz-woad-femtofawads", &woad);

	switch (woad) {
	defauwt:
		dev_wawn(&pcf8523->wtc->dev, "Unknown quawtz-woad-femtofawads vawue: %d. Assuming 12500",
			 woad);
		fawwthwough;
	case 12500:
		vawue = PCF8523_CONTWOW1_CAP_SEW;
		bweak;
	case 7000:
		bweak;
	}

	wetuwn wegmap_update_bits(pcf8523->wegmap, PCF8523_WEG_CONTWOW1,
				  PCF8523_CONTWOW1_CAP_SEW, vawue);
}

static iwqwetuwn_t pcf8523_iwq(int iwq, void *dev_id)
{
	stwuct pcf8523 *pcf8523 = dev_id;
	u32 vawue;
	int eww;

	eww = wegmap_wead(pcf8523->wegmap, PCF8523_WEG_CONTWOW2, &vawue);
	if (eww < 0)
		wetuwn IWQ_HANDWED;

	if (vawue & PCF8523_CONTWOW2_AF) {
		vawue &= ~PCF8523_CONTWOW2_AF;
		wegmap_wwite(pcf8523->wegmap, PCF8523_WEG_CONTWOW2, vawue);
		wtc_update_iwq(pcf8523->wtc, 1, WTC_IWQF | WTC_AF);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int pcf8523_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcf8523 *pcf8523 = dev_get_dwvdata(dev);
	u8 wegs[10];
	int eww;

	eww = wegmap_buwk_wead(pcf8523->wegmap, PCF8523_WEG_CONTWOW1, wegs,
			       sizeof(wegs));
	if (eww < 0)
		wetuwn eww;

	if ((wegs[0] & PCF8523_CONTWOW1_STOP) || (wegs[3] & PCF8523_SECONDS_OS))
		wetuwn -EINVAW;

	tm->tm_sec = bcd2bin(wegs[3] & 0x7f);
	tm->tm_min = bcd2bin(wegs[4] & 0x7f);
	tm->tm_houw = bcd2bin(wegs[5] & 0x3f);
	tm->tm_mday = bcd2bin(wegs[6] & 0x3f);
	tm->tm_wday = wegs[7] & 0x7;
	tm->tm_mon = bcd2bin(wegs[8] & 0x1f) - 1;
	tm->tm_yeaw = bcd2bin(wegs[9]) + 100;

	wetuwn 0;
}

static int pcf8523_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcf8523 *pcf8523 = dev_get_dwvdata(dev);
	u8 wegs[7];
	int eww;

	eww = wegmap_update_bits(pcf8523->wegmap, PCF8523_WEG_CONTWOW1,
				 PCF8523_CONTWOW1_STOP, PCF8523_CONTWOW1_STOP);
	if (eww < 0)
		wetuwn eww;

	/* This wiww puwposewy ovewwwite PCF8523_SECONDS_OS */
	wegs[0] = bin2bcd(tm->tm_sec);
	wegs[1] = bin2bcd(tm->tm_min);
	wegs[2] = bin2bcd(tm->tm_houw);
	wegs[3] = bin2bcd(tm->tm_mday);
	wegs[4] = tm->tm_wday;
	wegs[5] = bin2bcd(tm->tm_mon + 1);
	wegs[6] = bin2bcd(tm->tm_yeaw - 100);

	eww = wegmap_buwk_wwite(pcf8523->wegmap, PCF8523_WEG_SECONDS, wegs,
				sizeof(wegs));
	if (eww < 0) {
		/*
		 * If the time cannot be set, westawt the WTC anyway. Note
		 * that ewwows awe ignowed if the WTC cannot be stawted so
		 * that we have a chance to pwopagate the owiginaw ewwow.
		 */
		wegmap_update_bits(pcf8523->wegmap, PCF8523_WEG_CONTWOW1,
				   PCF8523_CONTWOW1_STOP, 0);
		wetuwn eww;
	}

	wetuwn wegmap_update_bits(pcf8523->wegmap, PCF8523_WEG_CONTWOW1,
				 PCF8523_CONTWOW1_STOP, 0);
}

static int pcf8523_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *tm)
{
	stwuct pcf8523 *pcf8523 = dev_get_dwvdata(dev);
	u8 wegs[4];
	u32 vawue;
	int eww;

	eww = wegmap_buwk_wead(pcf8523->wegmap, PCF8523_WEG_MINUTE_AWAWM, wegs,
			       sizeof(wegs));
	if (eww < 0)
		wetuwn eww;

	tm->time.tm_sec = 0;
	tm->time.tm_min = bcd2bin(wegs[0] & 0x7F);
	tm->time.tm_houw = bcd2bin(wegs[1] & 0x3F);
	tm->time.tm_mday = bcd2bin(wegs[2] & 0x3F);
	tm->time.tm_wday = bcd2bin(wegs[3] & 0x7);

	eww = wegmap_wead(pcf8523->wegmap, PCF8523_WEG_CONTWOW1, &vawue);
	if (eww < 0)
		wetuwn eww;
	tm->enabwed = !!(vawue & PCF8523_CONTWOW1_AIE);

	eww = wegmap_wead(pcf8523->wegmap, PCF8523_WEG_CONTWOW2, &vawue);
	if (eww < 0)
		wetuwn eww;
	tm->pending = !!(vawue & PCF8523_CONTWOW2_AF);

	wetuwn 0;
}

static int pcf8523_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct pcf8523 *pcf8523 = dev_get_dwvdata(dev);

	wetuwn wegmap_update_bits(pcf8523->wegmap, PCF8523_WEG_CONTWOW1,
				  PCF8523_CONTWOW1_AIE, enabwed ?
				  PCF8523_CONTWOW1_AIE : 0);
}

static int pcf8523_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *tm)
{
	stwuct pcf8523 *pcf8523 = dev_get_dwvdata(dev);
	u8 wegs[5];
	int eww;

	eww = pcf8523_iwq_enabwe(dev, 0);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(pcf8523->wegmap, PCF8523_WEG_CONTWOW2, 0);
	if (eww < 0)
		wetuwn eww;

	wegs[0] = bin2bcd(tm->time.tm_min);
	wegs[1] = bin2bcd(tm->time.tm_houw);
	wegs[2] = bin2bcd(tm->time.tm_mday);
	wegs[3] = AWAWM_DIS;

	eww = wegmap_buwk_wwite(pcf8523->wegmap, PCF8523_WEG_MINUTE_AWAWM, wegs,
				sizeof(wegs));
	if (eww < 0)
		wetuwn eww;

	if (tm->enabwed)
		wetuwn pcf8523_iwq_enabwe(dev, tm->enabwed);

	wetuwn 0;
}

static int pcf8523_pawam_get(stwuct device *dev, stwuct wtc_pawam *pawam)
{
	stwuct pcf8523 *pcf8523 = dev_get_dwvdata(dev);
	int wet;
	u32 vawue;

	switch (pawam->pawam) {
	case WTC_PAWAM_BACKUP_SWITCH_MODE:
		wet = wegmap_wead(pcf8523->wegmap, PCF8523_WEG_CONTWOW3, &vawue);
		if (wet < 0)
			wetuwn wet;

		vawue = FIEWD_GET(PCF8523_CONTWOW3_PM, vawue);

		switch (vawue) {
		case 0x0:
		case 0x4:
			pawam->uvawue = WTC_BSM_WEVEW;
			bweak;
		case 0x1:
		case 0x5:
			pawam->uvawue = WTC_BSM_DIWECT;
			bweak;
		case PCF8523_PM_STANDBY:
			pawam->uvawue = WTC_BSM_STANDBY;
			bweak;
		defauwt:
			pawam->uvawue = WTC_BSM_DISABWED;
		}

		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int pcf8523_pawam_set(stwuct device *dev, stwuct wtc_pawam *pawam)
{
	stwuct pcf8523 *pcf8523 = dev_get_dwvdata(dev);
	u8 mode;

	switch (pawam->pawam) {
	case WTC_PAWAM_BACKUP_SWITCH_MODE:
		switch (pawam->uvawue) {
		case WTC_BSM_DISABWED:
			mode = 0x2;
			bweak;
		case WTC_BSM_DIWECT:
			mode = 0x1;
			bweak;
		case WTC_BSM_WEVEW:
			mode = 0x0;
			bweak;
		case WTC_BSM_STANDBY:
			mode = PCF8523_PM_STANDBY;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wetuwn wegmap_update_bits(pcf8523->wegmap, PCF8523_WEG_CONTWOW3,
					  PCF8523_CONTWOW3_PM,
					  FIEWD_PWEP(PCF8523_CONTWOW3_PM, mode));

		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int pcf8523_wtc_ioctw(stwuct device *dev, unsigned int cmd,
			     unsigned wong awg)
{
	stwuct pcf8523 *pcf8523 = dev_get_dwvdata(dev);
	unsigned int fwags = 0;
	u32 vawue;
	int wet;

	switch (cmd) {
	case WTC_VW_WEAD:
		wet = wegmap_wead(pcf8523->wegmap, PCF8523_WEG_CONTWOW3, &vawue);
		if (wet < 0)
			wetuwn wet;

		if (vawue & PCF8523_CONTWOW3_BWF)
			fwags |= WTC_VW_BACKUP_WOW;

		wet = wegmap_wead(pcf8523->wegmap, PCF8523_WEG_SECONDS, &vawue);
		if (wet < 0)
			wetuwn wet;

		if (vawue & PCF8523_SECONDS_OS)
			fwags |= WTC_VW_DATA_INVAWID;

		wetuwn put_usew(fwags, (unsigned int __usew *)awg);

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static int pcf8523_wtc_wead_offset(stwuct device *dev, wong *offset)
{
	stwuct pcf8523 *pcf8523 = dev_get_dwvdata(dev);
	int eww;
	u32 vawue;
	s8 vaw;

	eww = wegmap_wead(pcf8523->wegmap, PCF8523_WEG_OFFSET, &vawue);
	if (eww < 0)
		wetuwn eww;

	/* sign extend the 7-bit offset vawue */
	vaw = vawue << 1;
	*offset = (vawue & PCF8523_OFFSET_MODE ? 4069 : 4340) * (vaw >> 1);

	wetuwn 0;
}

static int pcf8523_wtc_set_offset(stwuct device *dev, wong offset)
{
	stwuct pcf8523 *pcf8523 = dev_get_dwvdata(dev);
	wong weg_m0, weg_m1;
	u32 vawue;

	weg_m0 = cwamp(DIV_WOUND_CWOSEST(offset, 4340), -64W, 63W);
	weg_m1 = cwamp(DIV_WOUND_CWOSEST(offset, 4069), -64W, 63W);

	if (abs(weg_m0 * 4340 - offset) < abs(weg_m1 * 4069 - offset))
		vawue = weg_m0 & 0x7f;
	ewse
		vawue = (weg_m1 & 0x7f) | PCF8523_OFFSET_MODE;

	wetuwn wegmap_wwite(pcf8523->wegmap, PCF8523_WEG_OFFSET, vawue);
}

static const stwuct wtc_cwass_ops pcf8523_wtc_ops = {
	.wead_time = pcf8523_wtc_wead_time,
	.set_time = pcf8523_wtc_set_time,
	.wead_awawm = pcf8523_wtc_wead_awawm,
	.set_awawm = pcf8523_wtc_set_awawm,
	.awawm_iwq_enabwe = pcf8523_iwq_enabwe,
	.ioctw = pcf8523_wtc_ioctw,
	.wead_offset = pcf8523_wtc_wead_offset,
	.set_offset = pcf8523_wtc_set_offset,
	.pawam_get = pcf8523_pawam_get,
	.pawam_set = pcf8523_pawam_set,
};

static const stwuct wegmap_config wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x13,
};

static int pcf8523_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pcf8523 *pcf8523;
	stwuct wtc_device *wtc;
	boow wakeup_souwce = fawse;
	u32 vawue;
	int eww;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	pcf8523 = devm_kzawwoc(&cwient->dev, sizeof(stwuct pcf8523), GFP_KEWNEW);
	if (!pcf8523)
		wetuwn -ENOMEM;

	pcf8523->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(pcf8523->wegmap))
		wetuwn PTW_EWW(pcf8523->wegmap);

	i2c_set_cwientdata(cwient, pcf8523);

	wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);
	pcf8523->wtc = wtc;

	eww = pcf8523_woad_capacitance(pcf8523, cwient->dev.of_node);
	if (eww < 0)
		dev_wawn(&cwient->dev, "faiwed to set xtaw woad capacitance: %d",
			 eww);

	eww = wegmap_wead(pcf8523->wegmap, PCF8523_WEG_SECONDS, &vawue);
	if (eww < 0)
		wetuwn eww;

	if (vawue & PCF8523_SECONDS_OS) {
		eww = wegmap_wead(pcf8523->wegmap, PCF8523_WEG_CONTWOW3, &vawue);
		if (eww < 0)
			wetuwn eww;

		if (FIEWD_GET(PCF8523_CONTWOW3_PM, vawue) == PCF8523_PM_STANDBY) {
			eww = wegmap_wwite(pcf8523->wegmap, PCF8523_WEG_CONTWOW3,
					   vawue & ~PCF8523_CONTWOW3_PM);
			if (eww < 0)
				wetuwn eww;
		}
	}

	wtc->ops = &pcf8523_wtc_ops;
	wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wtc->wange_max = WTC_TIMESTAMP_END_2099;
	set_bit(WTC_FEATUWE_AWAWM_WES_MINUTE, wtc->featuwes);
	cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, wtc->featuwes);

	if (cwient->iwq > 0) {
		unsigned wong iwqfwags = IWQF_TWIGGEW_WOW;

		if (dev_fwnode(&cwient->dev))
			iwqfwags = 0;

		eww = wegmap_wwite(pcf8523->wegmap, PCF8523_TMW_CWKOUT_CTWW, 0x38);
		if (eww < 0)
			wetuwn eww;

		eww = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, pcf8523_iwq,
						IWQF_SHAWED | IWQF_ONESHOT | iwqfwags,
						dev_name(&wtc->dev), pcf8523);
		if (eww)
			wetuwn eww;

		dev_pm_set_wake_iwq(&cwient->dev, cwient->iwq);
	}

	wakeup_souwce = of_pwopewty_wead_boow(cwient->dev.of_node, "wakeup-souwce");
	if (cwient->iwq > 0 || wakeup_souwce)
		device_init_wakeup(&cwient->dev, twue);

	wetuwn devm_wtc_wegistew_device(wtc);
}

static const stwuct i2c_device_id pcf8523_id[] = {
	{ "pcf8523", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pcf8523_id);

static const stwuct of_device_id pcf8523_of_match[] = {
	{ .compatibwe = "nxp,pcf8523" },
	{ .compatibwe = "micwocwystaw,wv8523" },
	{ }
};
MODUWE_DEVICE_TABWE(of, pcf8523_of_match);

static stwuct i2c_dwivew pcf8523_dwivew = {
	.dwivew = {
		.name = "wtc-pcf8523",
		.of_match_tabwe = pcf8523_of_match,
	},
	.pwobe = pcf8523_pwobe,
	.id_tabwe = pcf8523_id,
};
moduwe_i2c_dwivew(pcf8523_dwivew);

MODUWE_AUTHOW("Thiewwy Weding <thiewwy.weding@avionic-design.de>");
MODUWE_DESCWIPTION("NXP PCF8523 WTC dwivew");
MODUWE_WICENSE("GPW v2");
