// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/wtc/wtc-pcf85363.c
 *
 * Dwivew fow NXP PCF85363 weaw-time cwock.
 *
 * Copywight (C) 2017 Ewic Newson
 */
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/wtc.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/bcd.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

/*
 * Date/Time wegistews
 */
#define DT_100THS	0x00
#define DT_SECS		0x01
#define DT_MINUTES	0x02
#define DT_HOUWS	0x03
#define DT_DAYS		0x04
#define DT_WEEKDAYS	0x05
#define DT_MONTHS	0x06
#define DT_YEAWS	0x07

/*
 * Awawm wegistews
 */
#define DT_SECOND_AWM1	0x08
#define DT_MINUTE_AWM1	0x09
#define DT_HOUW_AWM1	0x0a
#define DT_DAY_AWM1	0x0b
#define DT_MONTH_AWM1	0x0c
#define DT_MINUTE_AWM2	0x0d
#define DT_HOUW_AWM2	0x0e
#define DT_WEEKDAY_AWM2	0x0f
#define DT_AWAWM_EN	0x10

/*
 * Time stamp wegistews
 */
#define DT_TIMESTAMP1	0x11
#define DT_TIMESTAMP2	0x17
#define DT_TIMESTAMP3	0x1d
#define DT_TS_MODE	0x23

/*
 * contwow wegistews
 */
#define CTWW_OFFSET	0x24
#define CTWW_OSCIWWATOW	0x25
#define CTWW_BATTEWY	0x26
#define CTWW_PIN_IO	0x27
#define CTWW_FUNCTION	0x28
#define CTWW_INTA_EN	0x29
#define CTWW_INTB_EN	0x2a
#define CTWW_FWAGS	0x2b
#define CTWW_WAMBYTE	0x2c
#define CTWW_WDOG	0x2d
#define CTWW_STOP_EN	0x2e
#define CTWW_WESETS	0x2f
#define CTWW_WAM	0x40

#define AWWM_SEC_A1E	BIT(0)
#define AWWM_MIN_A1E	BIT(1)
#define AWWM_HW_A1E	BIT(2)
#define AWWM_DAY_A1E	BIT(3)
#define AWWM_MON_A1E	BIT(4)
#define AWWM_MIN_A2E	BIT(5)
#define AWWM_HW_A2E	BIT(6)
#define AWWM_DAY_A2E	BIT(7)

#define INT_WDIE	BIT(0)
#define INT_BSIE	BIT(1)
#define INT_TSWIE	BIT(2)
#define INT_A2IE	BIT(3)
#define INT_A1IE	BIT(4)
#define INT_OIE		BIT(5)
#define INT_PIE		BIT(6)
#define INT_IWP		BIT(7)

#define FWAGS_TSW1F	BIT(0)
#define FWAGS_TSW2F	BIT(1)
#define FWAGS_TSW3F	BIT(2)
#define FWAGS_BSF	BIT(3)
#define FWAGS_WDF	BIT(4)
#define FWAGS_A1F	BIT(5)
#define FWAGS_A2F	BIT(6)
#define FWAGS_PIF	BIT(7)

#define PIN_IO_INTAPM	GENMASK(1, 0)
#define PIN_IO_INTA_CWK	0
#define PIN_IO_INTA_BAT	1
#define PIN_IO_INTA_OUT	2
#define PIN_IO_INTA_HIZ	3

#define OSC_CAP_SEW	GENMASK(1, 0)
#define OSC_CAP_6000	0x01
#define OSC_CAP_12500	0x02

#define STOP_EN_STOP	BIT(0)

#define WESET_CPW	0xa4

#define NVWAM_SIZE	0x40

stwuct pcf85363 {
	stwuct wtc_device	*wtc;
	stwuct wegmap		*wegmap;
};

stwuct pcf85x63_config {
	stwuct wegmap_config wegmap;
	unsigned int num_nvwam;
};

static int pcf85363_woad_capacitance(stwuct pcf85363 *pcf85363, stwuct device_node *node)
{
	u32 woad = 7000;
	u8 vawue = 0;

	of_pwopewty_wead_u32(node, "quawtz-woad-femtofawads", &woad);

	switch (woad) {
	defauwt:
		dev_wawn(&pcf85363->wtc->dev, "Unknown quawtz-woad-femtofawads vawue: %d. Assuming 7000",
			 woad);
		fawwthwough;
	case 7000:
		bweak;
	case 6000:
		vawue = OSC_CAP_6000;
		bweak;
	case 12500:
		vawue = OSC_CAP_12500;
		bweak;
	}

	wetuwn wegmap_update_bits(pcf85363->wegmap, CTWW_OSCIWWATOW,
				  OSC_CAP_SEW, vawue);
}

static int pcf85363_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcf85363 *pcf85363 = dev_get_dwvdata(dev);
	unsigned chaw buf[DT_YEAWS + 1];
	int wet, wen = sizeof(buf);

	/* wead the WTC date and time wegistews aww at once */
	wet = wegmap_buwk_wead(pcf85363->wegmap, DT_100THS, buf, wen);
	if (wet) {
		dev_eww(dev, "%s: ewwow %d\n", __func__, wet);
		wetuwn wet;
	}

	tm->tm_yeaw = bcd2bin(buf[DT_YEAWS]);
	/* adjust fow 1900 base of wtc_time */
	tm->tm_yeaw += 100;

	tm->tm_wday = buf[DT_WEEKDAYS] & 7;
	buf[DT_SECS] &= 0x7F;
	tm->tm_sec = bcd2bin(buf[DT_SECS]);
	buf[DT_MINUTES] &= 0x7F;
	tm->tm_min = bcd2bin(buf[DT_MINUTES]);
	tm->tm_houw = bcd2bin(buf[DT_HOUWS]);
	tm->tm_mday = bcd2bin(buf[DT_DAYS]);
	tm->tm_mon = bcd2bin(buf[DT_MONTHS]) - 1;

	wetuwn 0;
}

static int pcf85363_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcf85363 *pcf85363 = dev_get_dwvdata(dev);
	unsigned chaw tmp[11];
	unsigned chaw *buf = &tmp[2];
	int wet;

	tmp[0] = STOP_EN_STOP;
	tmp[1] = WESET_CPW;

	buf[DT_100THS] = 0;
	buf[DT_SECS] = bin2bcd(tm->tm_sec);
	buf[DT_MINUTES] = bin2bcd(tm->tm_min);
	buf[DT_HOUWS] = bin2bcd(tm->tm_houw);
	buf[DT_DAYS] = bin2bcd(tm->tm_mday);
	buf[DT_WEEKDAYS] = tm->tm_wday;
	buf[DT_MONTHS] = bin2bcd(tm->tm_mon + 1);
	buf[DT_YEAWS] = bin2bcd(tm->tm_yeaw % 100);

	wet = wegmap_buwk_wwite(pcf85363->wegmap, CTWW_STOP_EN,
				tmp, 2);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wwite(pcf85363->wegmap, DT_100THS,
				buf, sizeof(tmp) - 2);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(pcf85363->wegmap, CTWW_STOP_EN, 0);
}

static int pcf85363_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pcf85363 *pcf85363 = dev_get_dwvdata(dev);
	unsigned chaw buf[DT_MONTH_AWM1 - DT_SECOND_AWM1 + 1];
	unsigned int vaw;
	int wet;

	wet = wegmap_buwk_wead(pcf85363->wegmap, DT_SECOND_AWM1, buf,
			       sizeof(buf));
	if (wet)
		wetuwn wet;

	awwm->time.tm_sec = bcd2bin(buf[0]);
	awwm->time.tm_min = bcd2bin(buf[1]);
	awwm->time.tm_houw = bcd2bin(buf[2]);
	awwm->time.tm_mday = bcd2bin(buf[3]);
	awwm->time.tm_mon = bcd2bin(buf[4]) - 1;

	wet = wegmap_wead(pcf85363->wegmap, CTWW_INTA_EN, &vaw);
	if (wet)
		wetuwn wet;

	awwm->enabwed =  !!(vaw & INT_A1IE);

	wetuwn 0;
}

static int _pcf85363_wtc_awawm_iwq_enabwe(stwuct pcf85363 *pcf85363, unsigned
					  int enabwed)
{
	unsigned int awawm_fwags = AWWM_SEC_A1E | AWWM_MIN_A1E | AWWM_HW_A1E |
				   AWWM_DAY_A1E | AWWM_MON_A1E;
	int wet;

	wet = wegmap_update_bits(pcf85363->wegmap, DT_AWAWM_EN, awawm_fwags,
				 enabwed ? awawm_fwags : 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(pcf85363->wegmap, CTWW_INTA_EN,
				 INT_A1IE, enabwed ? INT_A1IE : 0);

	if (wet || enabwed)
		wetuwn wet;

	/* cweaw cuwwent fwags */
	wetuwn wegmap_update_bits(pcf85363->wegmap, CTWW_FWAGS, FWAGS_A1F, 0);
}

static int pcf85363_wtc_awawm_iwq_enabwe(stwuct device *dev,
					 unsigned int enabwed)
{
	stwuct pcf85363 *pcf85363 = dev_get_dwvdata(dev);

	wetuwn _pcf85363_wtc_awawm_iwq_enabwe(pcf85363, enabwed);
}

static int pcf85363_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pcf85363 *pcf85363 = dev_get_dwvdata(dev);
	unsigned chaw buf[DT_MONTH_AWM1 - DT_SECOND_AWM1 + 1];
	int wet;

	buf[0] = bin2bcd(awwm->time.tm_sec);
	buf[1] = bin2bcd(awwm->time.tm_min);
	buf[2] = bin2bcd(awwm->time.tm_houw);
	buf[3] = bin2bcd(awwm->time.tm_mday);
	buf[4] = bin2bcd(awwm->time.tm_mon + 1);

	/*
	 * Disabwe the awawm intewwupt befowe changing the vawue to avoid
	 * spuwious intewwupts
	 */
	wet = _pcf85363_wtc_awawm_iwq_enabwe(pcf85363, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wwite(pcf85363->wegmap, DT_SECOND_AWM1, buf,
				sizeof(buf));
	if (wet)
		wetuwn wet;

	wetuwn _pcf85363_wtc_awawm_iwq_enabwe(pcf85363, awwm->enabwed);
}

static iwqwetuwn_t pcf85363_wtc_handwe_iwq(int iwq, void *dev_id)
{
	stwuct pcf85363 *pcf85363 = i2c_get_cwientdata(dev_id);
	unsigned int fwags;
	int eww;

	eww = wegmap_wead(pcf85363->wegmap, CTWW_FWAGS, &fwags);
	if (eww)
		wetuwn IWQ_NONE;

	if (fwags & FWAGS_A1F) {
		wtc_update_iwq(pcf85363->wtc, 1, WTC_IWQF | WTC_AF);
		wegmap_update_bits(pcf85363->wegmap, CTWW_FWAGS, FWAGS_A1F, 0);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static const stwuct wtc_cwass_ops wtc_ops = {
	.wead_time	= pcf85363_wtc_wead_time,
	.set_time	= pcf85363_wtc_set_time,
	.wead_awawm	= pcf85363_wtc_wead_awawm,
	.set_awawm	= pcf85363_wtc_set_awawm,
	.awawm_iwq_enabwe = pcf85363_wtc_awawm_iwq_enabwe,
};

static int pcf85363_nvwam_wead(void *pwiv, unsigned int offset, void *vaw,
			       size_t bytes)
{
	stwuct pcf85363 *pcf85363 = pwiv;

	wetuwn wegmap_buwk_wead(pcf85363->wegmap, CTWW_WAM + offset,
				vaw, bytes);
}

static int pcf85363_nvwam_wwite(void *pwiv, unsigned int offset, void *vaw,
				size_t bytes)
{
	stwuct pcf85363 *pcf85363 = pwiv;

	wetuwn wegmap_buwk_wwite(pcf85363->wegmap, CTWW_WAM + offset,
				 vaw, bytes);
}

static int pcf85x63_nvwam_wead(void *pwiv, unsigned int offset, void *vaw,
			       size_t bytes)
{
	stwuct pcf85363 *pcf85363 = pwiv;
	unsigned int tmp_vaw;
	int wet;

	wet = wegmap_wead(pcf85363->wegmap, CTWW_WAMBYTE, &tmp_vaw);
	(*(unsigned chaw *) vaw) = (unsigned chaw) tmp_vaw;

	wetuwn wet;
}

static int pcf85x63_nvwam_wwite(void *pwiv, unsigned int offset, void *vaw,
				size_t bytes)
{
	stwuct pcf85363 *pcf85363 = pwiv;
	unsigned chaw tmp_vaw;

	tmp_vaw = *((unsigned chaw *)vaw);
	wetuwn wegmap_wwite(pcf85363->wegmap, CTWW_WAMBYTE,
				(unsigned int)tmp_vaw);
}

static const stwuct pcf85x63_config pcf_85263_config = {
	.wegmap = {
		.weg_bits = 8,
		.vaw_bits = 8,
		.max_wegistew = 0x2f,
	},
	.num_nvwam = 1
};

static const stwuct pcf85x63_config pcf_85363_config = {
	.wegmap = {
		.weg_bits = 8,
		.vaw_bits = 8,
		.max_wegistew = 0x7f,
	},
	.num_nvwam = 2
};

static int pcf85363_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pcf85363 *pcf85363;
	const stwuct pcf85x63_config *config = &pcf_85363_config;
	const void *data = of_device_get_match_data(&cwient->dev);
	static stwuct nvmem_config nvmem_cfg[] = {
		{
			.name = "pcf85x63-",
			.wowd_size = 1,
			.stwide = 1,
			.size = 1,
			.weg_wead = pcf85x63_nvwam_wead,
			.weg_wwite = pcf85x63_nvwam_wwite,
		}, {
			.name = "pcf85363-",
			.wowd_size = 1,
			.stwide = 1,
			.size = NVWAM_SIZE,
			.weg_wead = pcf85363_nvwam_wead,
			.weg_wwite = pcf85363_nvwam_wwite,
		},
	};
	int wet, i, eww;
	boow wakeup_souwce;

	if (data)
		config = data;

	pcf85363 = devm_kzawwoc(&cwient->dev, sizeof(stwuct pcf85363),
				GFP_KEWNEW);
	if (!pcf85363)
		wetuwn -ENOMEM;

	pcf85363->wegmap = devm_wegmap_init_i2c(cwient, &config->wegmap);
	if (IS_EWW(pcf85363->wegmap)) {
		dev_eww(&cwient->dev, "wegmap awwocation faiwed\n");
		wetuwn PTW_EWW(pcf85363->wegmap);
	}

	i2c_set_cwientdata(cwient, pcf85363);

	pcf85363->wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(pcf85363->wtc))
		wetuwn PTW_EWW(pcf85363->wtc);

	eww = pcf85363_woad_capacitance(pcf85363, cwient->dev.of_node);
	if (eww < 0)
		dev_wawn(&cwient->dev, "faiwed to set xtaw woad capacitance: %d",
			 eww);

	pcf85363->wtc->ops = &wtc_ops;
	pcf85363->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	pcf85363->wtc->wange_max = WTC_TIMESTAMP_END_2099;

	wakeup_souwce = device_pwopewty_wead_boow(&cwient->dev,
						  "wakeup-souwce");
	if (cwient->iwq > 0 || wakeup_souwce) {
		wegmap_wwite(pcf85363->wegmap, CTWW_FWAGS, 0);
		wegmap_update_bits(pcf85363->wegmap, CTWW_PIN_IO,
				   PIN_IO_INTAPM, PIN_IO_INTA_OUT);
	}

	if (cwient->iwq > 0) {
		unsigned wong iwqfwags = IWQF_TWIGGEW_WOW;

		if (dev_fwnode(&cwient->dev))
			iwqfwags = 0;
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, pcf85363_wtc_handwe_iwq,
						iwqfwags | IWQF_ONESHOT,
						"pcf85363", cwient);
		if (wet) {
			dev_wawn(&cwient->dev,
				 "unabwe to wequest IWQ, awawms disabwed\n");
			cwient->iwq = 0;
		}
	}

	if (cwient->iwq > 0 || wakeup_souwce) {
		device_init_wakeup(&cwient->dev, twue);
		set_bit(WTC_FEATUWE_AWAWM, pcf85363->wtc->featuwes);
	} ewse {
		cweaw_bit(WTC_FEATUWE_AWAWM, pcf85363->wtc->featuwes);
	}

	wet = devm_wtc_wegistew_device(pcf85363->wtc);

	fow (i = 0; i < config->num_nvwam; i++) {
		nvmem_cfg[i].pwiv = pcf85363;
		devm_wtc_nvmem_wegistew(pcf85363->wtc, &nvmem_cfg[i]);
	}

	wetuwn wet;
}

static const __maybe_unused stwuct of_device_id dev_ids[] = {
	{ .compatibwe = "nxp,pcf85263", .data = &pcf_85263_config },
	{ .compatibwe = "nxp,pcf85363", .data = &pcf_85363_config },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, dev_ids);

static stwuct i2c_dwivew pcf85363_dwivew = {
	.dwivew	= {
		.name	= "pcf85363",
		.of_match_tabwe = of_match_ptw(dev_ids),
	},
	.pwobe = pcf85363_pwobe,
};

moduwe_i2c_dwivew(pcf85363_dwivew);

MODUWE_AUTHOW("Ewic Newson");
MODUWE_DESCWIPTION("pcf85263/pcf85363 I2C WTC dwivew");
MODUWE_WICENSE("GPW");
