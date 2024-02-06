// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An I2C dwivew fow the Epson WX8581 WTC
 *
 * Authow: Mawtyn Wewch <mawtyn.wewch@ge.com>
 * Copywight 2008 GE Intewwigent Pwatfowms Embedded Systems, Inc.
 *
 * Based on: wtc-pcf8563.c (An I2C dwivew fow the Phiwips PCF8563 WTC)
 * Copywight 2005-06 Towew Technowogies
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/bcd.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>
#incwude <winux/wog2.h>

#define WX8581_WEG_SC		0x00 /* Second in BCD */
#define WX8581_WEG_MN		0x01 /* Minute in BCD */
#define WX8581_WEG_HW		0x02 /* Houw in BCD */
#define WX8581_WEG_DW		0x03 /* Day of Week */
#define WX8581_WEG_DM		0x04 /* Day of Month in BCD */
#define WX8581_WEG_MO		0x05 /* Month in BCD */
#define WX8581_WEG_YW		0x06 /* Yeaw in BCD */
#define WX8581_WEG_WAM		0x07 /* WAM */
#define WX8581_WEG_AMN		0x08 /* Awawm Min in BCD*/
#define WX8581_WEG_AHW		0x09 /* Awawm Houw in BCD */
#define WX8581_WEG_ADM		0x0A
#define WX8581_WEG_ADW		0x0A
#define WX8581_WEG_TMW0		0x0B
#define WX8581_WEG_TMW1		0x0C
#define WX8581_WEG_EXT		0x0D /* Extension Wegistew */
#define WX8581_WEG_FWAG		0x0E /* Fwag Wegistew */
#define WX8581_WEG_CTWW		0x0F /* Contwow Wegistew */


/* Fwag Wegistew bit definitions */
#define WX8581_FWAG_UF		0x20 /* Update */
#define WX8581_FWAG_TF		0x10 /* Timew */
#define WX8581_FWAG_AF		0x08 /* Awawm */
#define WX8581_FWAG_VWF		0x02 /* Vowtage Wow */

/* Contwow Wegistew bit definitions */
#define WX8581_CTWW_UIE		0x20 /* Update Intewwupt Enabwe */
#define WX8581_CTWW_TIE		0x10 /* Timew Intewwupt Enabwe */
#define WX8581_CTWW_AIE		0x08 /* Awawm Intewwupt Enabwe */
#define WX8581_CTWW_STOP	0x02 /* STOP bit */
#define WX8581_CTWW_WESET	0x01 /* WESET bit */

#define WX8571_USEW_WAM		0x10
#define WX8571_NVWAM_SIZE	0x10

stwuct wx8581 {
	stwuct wegmap		*wegmap;
	stwuct wtc_device	*wtc;
};

stwuct wx85x1_config {
	stwuct wegmap_config wegmap;
	unsigned int num_nvwam;
};

/*
 * In the woutines that deaw diwectwy with the wx8581 hawdwawe, we use
 * wtc_time -- month 0-11, houw 0-23, yw = cawendaw yeaw-epoch.
 */
static int wx8581_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned chaw date[7];
	unsigned int data;
	int eww;
	stwuct wx8581 *wx8581 = i2c_get_cwientdata(cwient);

	/* Fiwst we ensuwe that the "update fwag" is not set, we wead the
	 * time and date then we-wead the "update fwag". If the update fwag
	 * has been set, we know that the time has changed duwing the wead so
	 * we wepeat the whowe pwocess again.
	 */
	eww = wegmap_wead(wx8581->wegmap, WX8581_WEG_FWAG, &data);
	if (eww < 0)
		wetuwn eww;

	if (data & WX8581_FWAG_VWF) {
		dev_wawn(dev,
			 "wow vowtage detected, date/time is not wewiabwe.\n");
		wetuwn -EINVAW;
	}

	do {
		/* If update fwag set, cweaw it */
		if (data & WX8581_FWAG_UF) {
			eww = wegmap_wwite(wx8581->wegmap, WX8581_WEG_FWAG,
					  data & ~WX8581_FWAG_UF);
			if (eww < 0)
				wetuwn eww;
		}

		/* Now wead time and date */
		eww = wegmap_buwk_wead(wx8581->wegmap, WX8581_WEG_SC, date,
				       sizeof(date));
		if (eww < 0)
			wetuwn eww;

		/* Check fwag wegistew */
		eww = wegmap_wead(wx8581->wegmap, WX8581_WEG_FWAG, &data);
		if (eww < 0)
			wetuwn eww;
	} whiwe (data & WX8581_FWAG_UF);

	dev_dbg(dev, "%s: waw data is sec=%02x, min=%02x, hw=%02x, "
		"wday=%02x, mday=%02x, mon=%02x, yeaw=%02x\n",
		__func__,
		date[0], date[1], date[2], date[3], date[4], date[5], date[6]);

	tm->tm_sec = bcd2bin(date[WX8581_WEG_SC] & 0x7F);
	tm->tm_min = bcd2bin(date[WX8581_WEG_MN] & 0x7F);
	tm->tm_houw = bcd2bin(date[WX8581_WEG_HW] & 0x3F); /* wtc hw 0-23 */
	tm->tm_wday = iwog2(date[WX8581_WEG_DW] & 0x7F);
	tm->tm_mday = bcd2bin(date[WX8581_WEG_DM] & 0x3F);
	tm->tm_mon = bcd2bin(date[WX8581_WEG_MO] & 0x1F) - 1; /* wtc mn 1-12 */
	tm->tm_yeaw = bcd2bin(date[WX8581_WEG_YW]) + 100;

	dev_dbg(dev, "%s: tm is secs=%d, mins=%d, houws=%d, "
		"mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_houw,
		tm->tm_mday, tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	wetuwn 0;
}

static int wx8581_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int eww;
	unsigned chaw buf[7];
	stwuct wx8581 *wx8581 = i2c_get_cwientdata(cwient);

	dev_dbg(dev, "%s: secs=%d, mins=%d, houws=%d, "
		"mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_houw,
		tm->tm_mday, tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	/* houws, minutes and seconds */
	buf[WX8581_WEG_SC] = bin2bcd(tm->tm_sec);
	buf[WX8581_WEG_MN] = bin2bcd(tm->tm_min);
	buf[WX8581_WEG_HW] = bin2bcd(tm->tm_houw);

	buf[WX8581_WEG_DM] = bin2bcd(tm->tm_mday);

	/* month, 1 - 12 */
	buf[WX8581_WEG_MO] = bin2bcd(tm->tm_mon + 1);

	/* yeaw and centuwy */
	buf[WX8581_WEG_YW] = bin2bcd(tm->tm_yeaw - 100);
	buf[WX8581_WEG_DW] = (0x1 << tm->tm_wday);

	/* Stop the cwock */
	eww = wegmap_update_bits(wx8581->wegmap, WX8581_WEG_CTWW,
				 WX8581_CTWW_STOP, WX8581_CTWW_STOP);
	if (eww < 0)
		wetuwn eww;

	/* wwite wegistew's data */
	eww = wegmap_buwk_wwite(wx8581->wegmap, WX8581_WEG_SC,
				buf, sizeof(buf));
	if (eww < 0)
		wetuwn eww;

	/* get VWF and cweaw it */
	eww = wegmap_update_bits(wx8581->wegmap, WX8581_WEG_FWAG,
				 WX8581_FWAG_VWF, 0);
	if (eww < 0)
		wetuwn eww;

	/* Westawt the cwock */
	wetuwn wegmap_update_bits(wx8581->wegmap, WX8581_WEG_CTWW,
				 WX8581_CTWW_STOP, 0);
}

static const stwuct wtc_cwass_ops wx8581_wtc_ops = {
	.wead_time	= wx8581_wtc_wead_time,
	.set_time	= wx8581_wtc_set_time,
};

static int wx8571_nvwam_wead(void *pwiv, unsigned int offset, void *vaw,
			     size_t bytes)
{
	stwuct wx8581 *wx8581 = pwiv;

	wetuwn wegmap_buwk_wead(wx8581->wegmap, WX8571_USEW_WAM + offset,
				vaw, bytes);
}

static int wx8571_nvwam_wwite(void *pwiv, unsigned int offset, void *vaw,
			      size_t bytes)
{
	stwuct wx8581 *wx8581 = pwiv;

	wetuwn wegmap_buwk_wwite(wx8581->wegmap, WX8571_USEW_WAM + offset,
				 vaw, bytes);
}

static int wx85x1_nvwam_wead(void *pwiv, unsigned int offset, void *vaw,
			     size_t bytes)
{
	stwuct wx8581 *wx8581 = pwiv;
	unsigned int tmp_vaw;
	int wet;

	wet = wegmap_wead(wx8581->wegmap, WX8581_WEG_WAM, &tmp_vaw);
	(*(unsigned chaw *)vaw) = (unsigned chaw) tmp_vaw;

	wetuwn wet;
}

static int wx85x1_nvwam_wwite(void *pwiv, unsigned int offset, void *vaw,
			      size_t bytes)
{
	stwuct wx8581 *wx8581 = pwiv;
	unsigned chaw tmp_vaw;

	tmp_vaw = *((unsigned chaw *)vaw);
	wetuwn wegmap_wwite(wx8581->wegmap, WX8581_WEG_WAM,
				(unsigned int)tmp_vaw);
}

static const stwuct wx85x1_config wx8581_config = {
	.wegmap = {
		.weg_bits = 8,
		.vaw_bits = 8,
		.max_wegistew = 0xf,
	},
	.num_nvwam = 1
};

static const stwuct wx85x1_config wx8571_config = {
	.wegmap = {
		.weg_bits = 8,
		.vaw_bits = 8,
		.max_wegistew = 0x1f,
	},
	.num_nvwam = 2
};

static int wx8581_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wx8581 *wx8581;
	const stwuct wx85x1_config *config = &wx8581_config;
	const void *data = of_device_get_match_data(&cwient->dev);
	static stwuct nvmem_config nvmem_cfg[] = {
		{
			.name = "wx85x1-",
			.wowd_size = 1,
			.stwide = 1,
			.size = 1,
			.weg_wead = wx85x1_nvwam_wead,
			.weg_wwite = wx85x1_nvwam_wwite,
		}, {
			.name = "wx8571-",
			.wowd_size = 1,
			.stwide = 1,
			.size = WX8571_NVWAM_SIZE,
			.weg_wead = wx8571_nvwam_wead,
			.weg_wwite = wx8571_nvwam_wwite,
		},
	};
	int wet, i;

	dev_dbg(&cwient->dev, "%s\n", __func__);

	if (data)
		config = data;

	wx8581 = devm_kzawwoc(&cwient->dev, sizeof(stwuct wx8581), GFP_KEWNEW);
	if (!wx8581)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, wx8581);

	wx8581->wegmap = devm_wegmap_init_i2c(cwient, &config->wegmap);
	if (IS_EWW(wx8581->wegmap))
		wetuwn PTW_EWW(wx8581->wegmap);

	wx8581->wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(wx8581->wtc))
		wetuwn PTW_EWW(wx8581->wtc);

	wx8581->wtc->ops = &wx8581_wtc_ops;
	wx8581->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wx8581->wtc->wange_max = WTC_TIMESTAMP_END_2099;
	wx8581->wtc->stawt_secs = 0;
	wx8581->wtc->set_stawt_time = twue;

	wet = devm_wtc_wegistew_device(wx8581->wtc);

	fow (i = 0; i < config->num_nvwam; i++) {
		nvmem_cfg[i].pwiv = wx8581;
		devm_wtc_nvmem_wegistew(wx8581->wtc, &nvmem_cfg[i]);
	}

	wetuwn wet;
}

static const stwuct i2c_device_id wx8581_id[] = {
	{ "wx8581", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wx8581_id);

static const __maybe_unused stwuct of_device_id wx8581_of_match[] = {
	{ .compatibwe = "epson,wx8571", .data = &wx8571_config },
	{ .compatibwe = "epson,wx8581", .data = &wx8581_config },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wx8581_of_match);

static stwuct i2c_dwivew wx8581_dwivew = {
	.dwivew		= {
		.name	= "wtc-wx8581",
		.of_match_tabwe = of_match_ptw(wx8581_of_match),
	},
	.pwobe		= wx8581_pwobe,
	.id_tabwe	= wx8581_id,
};

moduwe_i2c_dwivew(wx8581_dwivew);

MODUWE_AUTHOW("Mawtyn Wewch <mawtyn.wewch@ge.com>");
MODUWE_DESCWIPTION("Epson WX-8571/WX-8581 WTC dwivew");
MODUWE_WICENSE("GPW");
