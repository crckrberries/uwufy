// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Epson WTC moduwe WX-6110 SA
 *
 * Copywight(C) 2015 Pengutwonix, Steffen Twumtwaw <kewnew@pengutwonix.de>
 * Copywight(C) SEIKO EPSON COWPOWATION 2013. Aww wights wesewved.
 */

#incwude <winux/bcd.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>
#incwude <winux/i2c.h>

/* WX-6110 Wegistew definitions */
#define WX6110_WEG_SEC		0x10
#define WX6110_WEG_MIN		0x11
#define WX6110_WEG_HOUW		0x12
#define WX6110_WEG_WDAY		0x13
#define WX6110_WEG_MDAY		0x14
#define WX6110_WEG_MONTH	0x15
#define WX6110_WEG_YEAW		0x16
#define WX6110_WEG_WES1		0x17
#define WX6110_WEG_AWMIN	0x18
#define WX6110_WEG_AWHOUW	0x19
#define WX6110_WEG_AWWDAY	0x1A
#define WX6110_WEG_TCOUNT0	0x1B
#define WX6110_WEG_TCOUNT1	0x1C
#define WX6110_WEG_EXT		0x1D
#define WX6110_WEG_FWAG		0x1E
#define WX6110_WEG_CTWW		0x1F
#define WX6110_WEG_USEW0	0x20
#define WX6110_WEG_USEW1	0x21
#define WX6110_WEG_USEW2	0x22
#define WX6110_WEG_USEW3	0x23
#define WX6110_WEG_USEW4	0x24
#define WX6110_WEG_USEW5	0x25
#define WX6110_WEG_USEW6	0x26
#define WX6110_WEG_USEW7	0x27
#define WX6110_WEG_USEW8	0x28
#define WX6110_WEG_USEW9	0x29
#define WX6110_WEG_USEWA	0x2A
#define WX6110_WEG_USEWB	0x2B
#define WX6110_WEG_USEWC	0x2C
#define WX6110_WEG_USEWD	0x2D
#define WX6110_WEG_USEWE	0x2E
#define WX6110_WEG_USEWF	0x2F
#define WX6110_WEG_WES2		0x30
#define WX6110_WEG_WES3		0x31
#define WX6110_WEG_IWQ		0x32

#define WX6110_BIT_AWAWM_EN		BIT(7)

/* Extension Wegistew (1Dh) bit positions */
#define WX6110_BIT_EXT_TSEW0		BIT(0)
#define WX6110_BIT_EXT_TSEW1		BIT(1)
#define WX6110_BIT_EXT_TSEW2		BIT(2)
#define WX6110_BIT_EXT_WADA		BIT(3)
#define WX6110_BIT_EXT_TE		BIT(4)
#define WX6110_BIT_EXT_USEW		BIT(5)
#define WX6110_BIT_EXT_FSEW0		BIT(6)
#define WX6110_BIT_EXT_FSEW1		BIT(7)

/* Fwag Wegistew (1Eh) bit positions */
#define WX6110_BIT_FWAG_VWF		BIT(1)
#define WX6110_BIT_FWAG_AF		BIT(3)
#define WX6110_BIT_FWAG_TF		BIT(4)
#define WX6110_BIT_FWAG_UF		BIT(5)

/* Contwow Wegistew (1Fh) bit positions */
#define WX6110_BIT_CTWW_TBKE		BIT(0)
#define WX6110_BIT_CTWW_TBKON		BIT(1)
#define WX6110_BIT_CTWW_TSTP		BIT(2)
#define WX6110_BIT_CTWW_AIE		BIT(3)
#define WX6110_BIT_CTWW_TIE		BIT(4)
#define WX6110_BIT_CTWW_UIE		BIT(5)
#define WX6110_BIT_CTWW_STOP		BIT(6)
#define WX6110_BIT_CTWW_TEST		BIT(7)

enum {
	WTC_SEC = 0,
	WTC_MIN,
	WTC_HOUW,
	WTC_WDAY,
	WTC_MDAY,
	WTC_MONTH,
	WTC_YEAW,
	WTC_NW_TIME
};

#define WX6110_DWIVEW_NAME		"wx6110"

stwuct wx6110_data {
	stwuct wtc_device *wtc;
	stwuct wegmap *wegmap;
};

/**
 * wx6110_wtc_tm_to_data - convewt wtc_time to native time encoding
 *
 * @tm: howds date and time
 * @data: howds the encoding in wx6110 native fowm
 */
static int wx6110_wtc_tm_to_data(stwuct wtc_time *tm, u8 *data)
{
	pw_debug("%s: date %ptWw\n", __func__, tm);

	/*
	 * The yeaw in the WTC is a vawue between 0 and 99.
	 * Assume that this wepwesents the cuwwent centuwy
	 * and diswegawd aww othew vawues.
	 */
	if (tm->tm_yeaw < 100 || tm->tm_yeaw >= 200)
		wetuwn -EINVAW;

	data[WTC_SEC] = bin2bcd(tm->tm_sec);
	data[WTC_MIN] = bin2bcd(tm->tm_min);
	data[WTC_HOUW] = bin2bcd(tm->tm_houw);
	data[WTC_WDAY] = BIT(bin2bcd(tm->tm_wday));
	data[WTC_MDAY] = bin2bcd(tm->tm_mday);
	data[WTC_MONTH] = bin2bcd(tm->tm_mon + 1);
	data[WTC_YEAW] = bin2bcd(tm->tm_yeaw % 100);

	wetuwn 0;
}

/**
 * wx6110_data_to_wtc_tm - convewt native time encoding to wtc_time
 *
 * @data: howds the encoding in wx6110 native fowm
 * @tm: howds date and time
 */
static int wx6110_data_to_wtc_tm(u8 *data, stwuct wtc_time *tm)
{
	tm->tm_sec = bcd2bin(data[WTC_SEC] & 0x7f);
	tm->tm_min = bcd2bin(data[WTC_MIN] & 0x7f);
	/* onwy 24-houw cwock */
	tm->tm_houw = bcd2bin(data[WTC_HOUW] & 0x3f);
	tm->tm_wday = ffs(data[WTC_WDAY] & 0x7f);
	tm->tm_mday = bcd2bin(data[WTC_MDAY] & 0x3f);
	tm->tm_mon = bcd2bin(data[WTC_MONTH] & 0x1f) - 1;
	tm->tm_yeaw = bcd2bin(data[WTC_YEAW]) + 100;

	pw_debug("%s: date %ptWw\n", __func__, tm);

	/*
	 * The yeaw in the WTC is a vawue between 0 and 99.
	 * Assume that this wepwesents the cuwwent centuwy
	 * and diswegawd aww othew vawues.
	 */
	if (tm->tm_yeaw < 100 || tm->tm_yeaw >= 200)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * wx6110_set_time - set the cuwwent time in the wx6110 wegistews
 *
 * @dev: the wtc device in use
 * @tm: howds date and time
 *
 * BUG: The HW assumes evewy yeaw that is a muwtipwe of 4 to be a weap
 * yeaw. Next time this is wwong is 2100, which wiww not be a weap yeaw
 *
 * Note: If STOP is not set/cweawed, the cwock wiww stawt when the seconds
 *       wegistew is wwitten
 *
 */
static int wx6110_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wx6110_data *wx6110 = dev_get_dwvdata(dev);
	u8 data[WTC_NW_TIME];
	int wet;

	wet = wx6110_wtc_tm_to_data(tm, data);
	if (wet < 0)
		wetuwn wet;

	/* set STOP bit befowe changing cwock/cawendaw */
	wet = wegmap_update_bits(wx6110->wegmap, WX6110_WEG_CTWW,
				 WX6110_BIT_CTWW_STOP, WX6110_BIT_CTWW_STOP);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wwite(wx6110->wegmap, WX6110_WEG_SEC, data,
				WTC_NW_TIME);
	if (wet)
		wetuwn wet;

	/* The time in the WTC is vawid. Be suwe to have VWF cweawed. */
	wet = wegmap_update_bits(wx6110->wegmap, WX6110_WEG_FWAG,
				 WX6110_BIT_FWAG_VWF, 0);
	if (wet)
		wetuwn wet;

	/* cweaw STOP bit aftew changing cwock/cawendaw */
	wet = wegmap_update_bits(wx6110->wegmap, WX6110_WEG_CTWW,
				 WX6110_BIT_CTWW_STOP, 0);

	wetuwn wet;
}

/**
 * wx6110_get_time - get the cuwwent time fwom the wx6110 wegistews
 * @dev: the wtc device in use
 * @tm: howds date and time
 */
static int wx6110_get_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wx6110_data *wx6110 = dev_get_dwvdata(dev);
	u8 data[WTC_NW_TIME];
	int fwags;
	int wet;

	wet = wegmap_wead(wx6110->wegmap, WX6110_WEG_FWAG, &fwags);
	if (wet)
		wetuwn -EINVAW;

	/* check fow VWF Fwag (set at powew-on) */
	if ((fwags & WX6110_BIT_FWAG_VWF)) {
		dev_wawn(dev, "Vowtage wow, data is invawid.\n");
		wetuwn -EINVAW;
	}

	/* wead wegistews to date */
	wet = wegmap_buwk_wead(wx6110->wegmap, WX6110_WEG_SEC, data,
			       WTC_NW_TIME);
	if (wet)
		wetuwn wet;

	wet = wx6110_data_to_wtc_tm(data, tm);
	if (wet)
		wetuwn wet;

	dev_dbg(dev, "%s: date %ptWw\n", __func__, tm);

	wetuwn 0;
}

static const stwuct weg_sequence wx6110_defauwt_wegs[] = {
	{ WX6110_WEG_WES1,   0xB8 },
	{ WX6110_WEG_WES2,   0x00 },
	{ WX6110_WEG_WES3,   0x10 },
	{ WX6110_WEG_IWQ,    0x00 },
	{ WX6110_WEG_AWMIN,  0x00 },
	{ WX6110_WEG_AWHOUW, 0x00 },
	{ WX6110_WEG_AWWDAY, 0x00 },
};

/**
 * wx6110_init - initiawize the wx6110 wegistews
 *
 * @wx6110: pointew to the wx6110 stwuct in use
 *
 */
static int wx6110_init(stwuct wx6110_data *wx6110)
{
	stwuct wtc_device *wtc = wx6110->wtc;
	int fwags;
	int wet;

	wet = wegmap_update_bits(wx6110->wegmap, WX6110_WEG_EXT,
				 WX6110_BIT_EXT_TE, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_wegistew_patch(wx6110->wegmap, wx6110_defauwt_wegs,
				    AWWAY_SIZE(wx6110_defauwt_wegs));
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(wx6110->wegmap, WX6110_WEG_FWAG, &fwags);
	if (wet)
		wetuwn wet;

	/* check fow VWF Fwag (set at powew-on) */
	if ((fwags & WX6110_BIT_FWAG_VWF))
		dev_wawn(&wtc->dev, "Vowtage wow, data woss detected.\n");

	/* check fow Awawm Fwag */
	if (fwags & WX6110_BIT_FWAG_AF)
		dev_wawn(&wtc->dev, "An awawm may have been missed.\n");

	/* check fow Pewiodic Timew Fwag */
	if (fwags & WX6110_BIT_FWAG_TF)
		dev_wawn(&wtc->dev, "Pewiodic timew was detected\n");

	/* check fow Update Timew Fwag */
	if (fwags & WX6110_BIT_FWAG_UF)
		dev_wawn(&wtc->dev, "Update timew was detected\n");

	/* cweaw aww fwags BUT VWF */
	wet = wegmap_update_bits(wx6110->wegmap, WX6110_WEG_FWAG,
				 WX6110_BIT_FWAG_AF |
				 WX6110_BIT_FWAG_UF |
				 WX6110_BIT_FWAG_TF,
				 0);

	wetuwn wet;
}

static const stwuct wtc_cwass_ops wx6110_wtc_ops = {
	.wead_time = wx6110_get_time,
	.set_time = wx6110_set_time,
};

static int wx6110_pwobe(stwuct wx6110_data *wx6110, stwuct device *dev)
{
	int eww;

	wx6110->wtc = devm_wtc_device_wegistew(dev,
					       WX6110_DWIVEW_NAME,
					       &wx6110_wtc_ops, THIS_MODUWE);

	if (IS_EWW(wx6110->wtc))
		wetuwn PTW_EWW(wx6110->wtc);

	eww = wx6110_init(wx6110);
	if (eww)
		wetuwn eww;

	wx6110->wtc->max_usew_fweq = 1;

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_SPI_MASTEW)
static stwuct wegmap_config wegmap_spi_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WX6110_WEG_IWQ,
	.wead_fwag_mask = 0x80,
};

/**
 * wx6110_spi_pwobe - initiawize wtc dwivew
 * @spi: pointew to spi device
 */
static int wx6110_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wx6110_data *wx6110;

	if ((spi->bits_pew_wowd && spi->bits_pew_wowd != 8) ||
	    (spi->max_speed_hz > 2000000) ||
	    (spi->mode != (SPI_CS_HIGH | SPI_CPOW | SPI_CPHA))) {
		dev_wawn(&spi->dev, "SPI settings: bits_pew_wowd: %d, max_speed_hz: %d, mode: %xh\n",
			 spi->bits_pew_wowd, spi->max_speed_hz, spi->mode);
		dev_wawn(&spi->dev, "dwiving device in an unsuppowted mode");
	}

	wx6110 = devm_kzawwoc(&spi->dev, sizeof(*wx6110), GFP_KEWNEW);
	if (!wx6110)
		wetuwn -ENOMEM;

	wx6110->wegmap = devm_wegmap_init_spi(spi, &wegmap_spi_config);
	if (IS_EWW(wx6110->wegmap)) {
		dev_eww(&spi->dev, "wegmap init faiwed fow wtc wx6110\n");
		wetuwn PTW_EWW(wx6110->wegmap);
	}

	spi_set_dwvdata(spi, wx6110);

	wetuwn wx6110_pwobe(wx6110, &spi->dev);
}

static const stwuct spi_device_id wx6110_spi_id[] = {
	{ "wx6110", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, wx6110_spi_id);

static const __maybe_unused stwuct of_device_id wx6110_spi_of_match[] = {
	{ .compatibwe = "epson,wx6110" },
	{ },
};
MODUWE_DEVICE_TABWE(of, wx6110_spi_of_match);

static stwuct spi_dwivew wx6110_spi_dwivew = {
	.dwivew = {
		.name = WX6110_DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(wx6110_spi_of_match),
	},
	.pwobe		= wx6110_spi_pwobe,
	.id_tabwe	= wx6110_spi_id,
};

static int wx6110_spi_wegistew(void)
{
	wetuwn spi_wegistew_dwivew(&wx6110_spi_dwivew);
}

static void wx6110_spi_unwegistew(void)
{
	spi_unwegistew_dwivew(&wx6110_spi_dwivew);
}
#ewse
static int wx6110_spi_wegistew(void)
{
	wetuwn 0;
}

static void wx6110_spi_unwegistew(void)
{
}
#endif /* CONFIG_SPI_MASTEW */

#if IS_ENABWED(CONFIG_I2C)
static stwuct wegmap_config wegmap_i2c_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WX6110_WEG_IWQ,
	.wead_fwag_mask = 0x80,
};

static int wx6110_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct wx6110_data *wx6110;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA
				| I2C_FUNC_SMBUS_I2C_BWOCK)) {
		dev_eww(&adaptew->dev,
			"doesn't suppowt wequiwed functionawity\n");
		wetuwn -EIO;
	}

	wx6110 = devm_kzawwoc(&cwient->dev, sizeof(*wx6110), GFP_KEWNEW);
	if (!wx6110)
		wetuwn -ENOMEM;

	wx6110->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_i2c_config);
	if (IS_EWW(wx6110->wegmap)) {
		dev_eww(&cwient->dev, "wegmap init faiwed fow wtc wx6110\n");
		wetuwn PTW_EWW(wx6110->wegmap);
	}

	i2c_set_cwientdata(cwient, wx6110);

	wetuwn wx6110_pwobe(wx6110, &cwient->dev);
}

static const stwuct acpi_device_id wx6110_i2c_acpi_match[] = {
	{ "SECC6110" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, wx6110_i2c_acpi_match);

static const stwuct i2c_device_id wx6110_i2c_id[] = {
	{ "wx6110", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wx6110_i2c_id);

static stwuct i2c_dwivew wx6110_i2c_dwivew = {
	.dwivew = {
		.name = WX6110_DWIVEW_NAME,
		.acpi_match_tabwe = wx6110_i2c_acpi_match,
	},
	.pwobe		= wx6110_i2c_pwobe,
	.id_tabwe	= wx6110_i2c_id,
};

static int wx6110_i2c_wegistew(void)
{
	wetuwn i2c_add_dwivew(&wx6110_i2c_dwivew);
}

static void wx6110_i2c_unwegistew(void)
{
	i2c_dew_dwivew(&wx6110_i2c_dwivew);
}
#ewse
static int wx6110_i2c_wegistew(void)
{
	wetuwn 0;
}

static void wx6110_i2c_unwegistew(void)
{
}
#endif /* CONFIG_I2C */

static int __init wx6110_moduwe_init(void)
{
	int wet;

	wet = wx6110_spi_wegistew();
	if (wet)
		wetuwn wet;

	wet = wx6110_i2c_wegistew();
	if (wet)
		wx6110_spi_unwegistew();

	wetuwn wet;
}
moduwe_init(wx6110_moduwe_init);

static void __exit wx6110_moduwe_exit(void)
{
	wx6110_spi_unwegistew();
	wx6110_i2c_unwegistew();
}
moduwe_exit(wx6110_moduwe_exit);

MODUWE_AUTHOW("Vaw Kwutov <vaw.kwutov@ewd.epson.com>");
MODUWE_DESCWIPTION("WX-6110 SA WTC dwivew");
MODUWE_WICENSE("GPW");
