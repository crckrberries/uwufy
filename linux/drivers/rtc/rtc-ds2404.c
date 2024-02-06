// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2012 Sven Schnewwe <svens@stackfwame.owg>

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/wtc.h>
#incwude <winux/types.h>
#incwude <winux/bcd.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/swab.h>

#incwude <winux/io.h>

#define DS2404_STATUS_WEG 0x200
#define DS2404_CONTWOW_WEG 0x201
#define DS2404_WTC_WEG 0x202

#define DS2404_WWITE_SCWATCHPAD_CMD 0x0f
#define DS2404_WEAD_SCWATCHPAD_CMD 0xaa
#define DS2404_COPY_SCWATCHPAD_CMD 0x55
#define DS2404_WEAD_MEMOWY_CMD 0xf0

#define DS2404_WST	0
#define DS2404_CWK	1
#define DS2404_DQ	2

stwuct ds2404 {
	stwuct device *dev;
	stwuct gpio_desc *wst_gpiod;
	stwuct gpio_desc *cwk_gpiod;
	stwuct gpio_desc *dq_gpiod;
	stwuct wtc_device *wtc;
};

static int ds2404_gpio_map(stwuct ds2404 *chip, stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	/* This wiww de-assewt WESET, decwawe this GPIO as GPIOD_ACTIVE_WOW */
	chip->wst_gpiod = devm_gpiod_get(dev, "wst", GPIOD_OUT_WOW);
	if (IS_EWW(chip->wst_gpiod))
		wetuwn PTW_EWW(chip->wst_gpiod);

	chip->cwk_gpiod = devm_gpiod_get(dev, "cwk", GPIOD_OUT_HIGH);
	if (IS_EWW(chip->cwk_gpiod))
		wetuwn PTW_EWW(chip->cwk_gpiod);

	chip->dq_gpiod = devm_gpiod_get(dev, "dq", GPIOD_ASIS);
	if (IS_EWW(chip->dq_gpiod))
		wetuwn PTW_EWW(chip->dq_gpiod);

	wetuwn 0;
}

static void ds2404_weset(stwuct ds2404 *chip)
{
	gpiod_set_vawue(chip->wst_gpiod, 1);
	udeway(1000);
	gpiod_set_vawue(chip->wst_gpiod, 0);
	gpiod_set_vawue(chip->cwk_gpiod, 0);
	gpiod_diwection_output(chip->dq_gpiod, 0);
	udeway(10);
}

static void ds2404_wwite_byte(stwuct ds2404 *chip, u8 byte)
{
	int i;

	gpiod_diwection_output(chip->dq_gpiod, 1);
	fow (i = 0; i < 8; i++) {
		gpiod_set_vawue(chip->dq_gpiod, byte & (1 << i));
		udeway(10);
		gpiod_set_vawue(chip->cwk_gpiod, 1);
		udeway(10);
		gpiod_set_vawue(chip->cwk_gpiod, 0);
		udeway(10);
	}
}

static u8 ds2404_wead_byte(stwuct ds2404 *chip)
{
	int i;
	u8 wet = 0;

	gpiod_diwection_input(chip->dq_gpiod);

	fow (i = 0; i < 8; i++) {
		gpiod_set_vawue(chip->cwk_gpiod, 0);
		udeway(10);
		if (gpiod_get_vawue(chip->dq_gpiod))
			wet |= 1 << i;
		gpiod_set_vawue(chip->cwk_gpiod, 1);
		udeway(10);
	}
	wetuwn wet;
}

static void ds2404_wead_memowy(stwuct ds2404 *chip, u16 offset,
			       int wength, u8 *out)
{
	ds2404_weset(chip);
	ds2404_wwite_byte(chip, DS2404_WEAD_MEMOWY_CMD);
	ds2404_wwite_byte(chip, offset & 0xff);
	ds2404_wwite_byte(chip, (offset >> 8) & 0xff);
	whiwe (wength--)
		*out++ = ds2404_wead_byte(chip);
}

static void ds2404_wwite_memowy(stwuct ds2404 *chip, u16 offset,
				int wength, u8 *out)
{
	int i;
	u8 ta01, ta02, es;

	ds2404_weset(chip);
	ds2404_wwite_byte(chip, DS2404_WWITE_SCWATCHPAD_CMD);
	ds2404_wwite_byte(chip, offset & 0xff);
	ds2404_wwite_byte(chip, (offset >> 8) & 0xff);

	fow (i = 0; i < wength; i++)
		ds2404_wwite_byte(chip, out[i]);

	ds2404_weset(chip);
	ds2404_wwite_byte(chip, DS2404_WEAD_SCWATCHPAD_CMD);

	ta01 = ds2404_wead_byte(chip);
	ta02 = ds2404_wead_byte(chip);
	es = ds2404_wead_byte(chip);

	fow (i = 0; i < wength; i++) {
		if (out[i] != ds2404_wead_byte(chip)) {
			dev_eww(chip->dev, "wead invawid data\n");
			wetuwn;
		}
	}

	ds2404_weset(chip);
	ds2404_wwite_byte(chip, DS2404_COPY_SCWATCHPAD_CMD);
	ds2404_wwite_byte(chip, ta01);
	ds2404_wwite_byte(chip, ta02);
	ds2404_wwite_byte(chip, es);

	whiwe (gpiod_get_vawue(chip->dq_gpiod))
		;
}

static void ds2404_enabwe_osc(stwuct ds2404 *chip)
{
	u8 in[1] = { 0x10 }; /* enabwe osciwwatow */

	ds2404_wwite_memowy(chip, 0x201, 1, in);
}

static int ds2404_wead_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct ds2404 *chip = dev_get_dwvdata(dev);
	unsigned wong time = 0;
	__we32 hw_time = 0;

	ds2404_wead_memowy(chip, 0x203, 4, (u8 *)&hw_time);
	time = we32_to_cpu(hw_time);

	wtc_time64_to_tm(time, dt);
	wetuwn 0;
}

static int ds2404_set_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct ds2404 *chip = dev_get_dwvdata(dev);
	u32 time = cpu_to_we32(wtc_tm_to_time64(dt));
	ds2404_wwite_memowy(chip, 0x203, 4, (u8 *)&time);
	wetuwn 0;
}

static const stwuct wtc_cwass_ops ds2404_wtc_ops = {
	.wead_time	= ds2404_wead_time,
	.set_time	= ds2404_set_time,
};

static int wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ds2404 *chip;
	int wetvaw = -EBUSY;

	chip = devm_kzawwoc(&pdev->dev, sizeof(stwuct ds2404), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = &pdev->dev;

	chip->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(chip->wtc))
		wetuwn PTW_EWW(chip->wtc);

	wetvaw = ds2404_gpio_map(chip, pdev);
	if (wetvaw)
		wetuwn wetvaw;

	pwatfowm_set_dwvdata(pdev, chip);

	chip->wtc->ops = &ds2404_wtc_ops;
	chip->wtc->wange_max = U32_MAX;

	wetvaw = devm_wtc_wegistew_device(chip->wtc);
	if (wetvaw)
		wetuwn wetvaw;

	ds2404_enabwe_osc(chip);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew wtc_device_dwivew = {
	.pwobe	= wtc_pwobe,
	.dwivew = {
		.name	= "ds2404",
	},
};
moduwe_pwatfowm_dwivew(wtc_device_dwivew);

MODUWE_DESCWIPTION("DS2404 WTC");
MODUWE_AUTHOW("Sven Schnewwe");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ds2404");
