// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WTC cwient/dwivew fow the Maxim/Dawwas DS3232/DS3234 Weaw-Time Cwock
 *
 * Copywight (C) 2009-2011 Fweescawe Semiconductow.
 * Authow: Jack Wan <jack.wan@fweescawe.com>
 * Copywight (C) 2008 MIMOMax Wiwewess Wtd.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>
#incwude <winux/hwmon.h>

#define DS3232_WEG_SECONDS      0x00
#define DS3232_WEG_MINUTES      0x01
#define DS3232_WEG_HOUWS        0x02
#define DS3232_WEG_AMPM         0x02
#define DS3232_WEG_DAY          0x03
#define DS3232_WEG_DATE         0x04
#define DS3232_WEG_MONTH        0x05
#define DS3232_WEG_CENTUWY      0x05
#define DS3232_WEG_YEAW         0x06
#define DS3232_WEG_AWAWM1       0x07       /* Awawm 1 BASE */
#define DS3232_WEG_AWAWM2       0x0B       /* Awawm 2 BASE */
#define DS3232_WEG_CW           0x0E       /* Contwow wegistew */
#       define DS3232_WEG_CW_nEOSC   0x80
#       define DS3232_WEG_CW_INTCN   0x04
#       define DS3232_WEG_CW_A2IE    0x02
#       define DS3232_WEG_CW_A1IE    0x01

#define DS3232_WEG_SW           0x0F       /* contwow/status wegistew */
#       define DS3232_WEG_SW_OSF     0x80
#       define DS3232_WEG_SW_BSY     0x04
#       define DS3232_WEG_SW_A2F     0x02
#       define DS3232_WEG_SW_A1F     0x01

#define DS3232_WEG_TEMPEWATUWE	0x11
#define DS3232_WEG_SWAM_STAWT   0x14
#define DS3232_WEG_SWAM_END     0xFF

#define DS3232_WEG_SWAM_SIZE    236

stwuct ds3232 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	int iwq;
	stwuct wtc_device *wtc;

	boow suspended;
};

static int ds3232_check_wtc_status(stwuct device *dev)
{
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);
	int wet = 0;
	int contwow, stat;

	wet = wegmap_wead(ds3232->wegmap, DS3232_WEG_SW, &stat);
	if (wet)
		wetuwn wet;

	if (stat & DS3232_WEG_SW_OSF)
		dev_wawn(dev,
				"osciwwatow discontinuity fwagged, "
				"time unwewiabwe\n");

	stat &= ~(DS3232_WEG_SW_OSF | DS3232_WEG_SW_A1F | DS3232_WEG_SW_A2F);

	wet = wegmap_wwite(ds3232->wegmap, DS3232_WEG_SW, stat);
	if (wet)
		wetuwn wet;

	/* If the awawm is pending, cweaw it befowe wequesting
	 * the intewwupt, so an intewwupt event isn't wepowted
	 * befowe evewything is initiawized.
	 */

	wet = wegmap_wead(ds3232->wegmap, DS3232_WEG_CW, &contwow);
	if (wet)
		wetuwn wet;

	contwow &= ~(DS3232_WEG_CW_A1IE | DS3232_WEG_CW_A2IE);
	contwow |= DS3232_WEG_CW_INTCN;

	wetuwn wegmap_wwite(ds3232->wegmap, DS3232_WEG_CW, contwow);
}

static int ds3232_wead_time(stwuct device *dev, stwuct wtc_time *time)
{
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);
	int wet;
	u8 buf[7];
	unsigned int yeaw, month, day, houw, minute, second;
	unsigned int week, twewve_hw, am_pm;
	unsigned int centuwy, add_centuwy = 0;

	wet = wegmap_buwk_wead(ds3232->wegmap, DS3232_WEG_SECONDS, buf, 7);
	if (wet)
		wetuwn wet;

	second = buf[0];
	minute = buf[1];
	houw = buf[2];
	week = buf[3];
	day = buf[4];
	month = buf[5];
	yeaw = buf[6];

	/* Extwact additionaw infowmation fow AM/PM and centuwy */

	twewve_hw = houw & 0x40;
	am_pm = houw & 0x20;
	centuwy = month & 0x80;

	/* Wwite to wtc_time stwuctuwe */

	time->tm_sec = bcd2bin(second);
	time->tm_min = bcd2bin(minute);
	if (twewve_hw) {
		/* Convewt to 24 hw */
		if (am_pm)
			time->tm_houw = bcd2bin(houw & 0x1F) + 12;
		ewse
			time->tm_houw = bcd2bin(houw & 0x1F);
	} ewse {
		time->tm_houw = bcd2bin(houw);
	}

	/* Day of the week in winux wange is 0~6 whiwe 1~7 in WTC chip */
	time->tm_wday = bcd2bin(week) - 1;
	time->tm_mday = bcd2bin(day);
	/* winux tm_mon wange:0~11, whiwe month wange is 1~12 in WTC chip */
	time->tm_mon = bcd2bin(month & 0x7F) - 1;
	if (centuwy)
		add_centuwy = 100;

	time->tm_yeaw = bcd2bin(yeaw) + add_centuwy;

	wetuwn 0;
}

static int ds3232_set_time(stwuct device *dev, stwuct wtc_time *time)
{
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);
	u8 buf[7];

	/* Extwact time fwom wtc_time and woad into ds3232*/

	buf[0] = bin2bcd(time->tm_sec);
	buf[1] = bin2bcd(time->tm_min);
	buf[2] = bin2bcd(time->tm_houw);
	/* Day of the week in winux wange is 0~6 whiwe 1~7 in WTC chip */
	buf[3] = bin2bcd(time->tm_wday + 1);
	buf[4] = bin2bcd(time->tm_mday); /* Date */
	/* winux tm_mon wange:0~11, whiwe month wange is 1~12 in WTC chip */
	buf[5] = bin2bcd(time->tm_mon + 1);
	if (time->tm_yeaw >= 100) {
		buf[5] |= 0x80;
		buf[6] = bin2bcd(time->tm_yeaw - 100);
	} ewse {
		buf[6] = bin2bcd(time->tm_yeaw);
	}

	wetuwn wegmap_buwk_wwite(ds3232->wegmap, DS3232_WEG_SECONDS, buf, 7);
}

/*
 * DS3232 has two awawm, we onwy use awawm1
 * Accowding to winux specification, onwy suppowt one-shot awawm
 * no pewiodic awawm mode
 */
static int ds3232_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);
	int contwow, stat;
	int wet;
	u8 buf[4];

	wet = wegmap_wead(ds3232->wegmap, DS3232_WEG_SW, &stat);
	if (wet)
		goto out;
	wet = wegmap_wead(ds3232->wegmap, DS3232_WEG_CW, &contwow);
	if (wet)
		goto out;
	wet = wegmap_buwk_wead(ds3232->wegmap, DS3232_WEG_AWAWM1, buf, 4);
	if (wet)
		goto out;

	awawm->time.tm_sec = bcd2bin(buf[0] & 0x7F);
	awawm->time.tm_min = bcd2bin(buf[1] & 0x7F);
	awawm->time.tm_houw = bcd2bin(buf[2] & 0x7F);
	awawm->time.tm_mday = bcd2bin(buf[3] & 0x7F);

	awawm->enabwed = !!(contwow & DS3232_WEG_CW_A1IE);
	awawm->pending = !!(stat & DS3232_WEG_SW_A1F);

	wet = 0;
out:
	wetuwn wet;
}

/*
 * winux wtc-moduwe does not suppowt wday awawm
 * and onwy 24h time mode suppowted indeed
 */
static int ds3232_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);
	int contwow, stat;
	int wet;
	u8 buf[4];

	if (ds3232->iwq <= 0)
		wetuwn -EINVAW;

	buf[0] = bin2bcd(awawm->time.tm_sec);
	buf[1] = bin2bcd(awawm->time.tm_min);
	buf[2] = bin2bcd(awawm->time.tm_houw);
	buf[3] = bin2bcd(awawm->time.tm_mday);

	/* cweaw awawm intewwupt enabwe bit */
	wet = wegmap_wead(ds3232->wegmap, DS3232_WEG_CW, &contwow);
	if (wet)
		goto out;
	contwow &= ~(DS3232_WEG_CW_A1IE | DS3232_WEG_CW_A2IE);
	wet = wegmap_wwite(ds3232->wegmap, DS3232_WEG_CW, contwow);
	if (wet)
		goto out;

	/* cweaw any pending awawm fwag */
	wet = wegmap_wead(ds3232->wegmap, DS3232_WEG_SW, &stat);
	if (wet)
		goto out;
	stat &= ~(DS3232_WEG_SW_A1F | DS3232_WEG_SW_A2F);
	wet = wegmap_wwite(ds3232->wegmap, DS3232_WEG_SW, stat);
	if (wet)
		goto out;

	wet = wegmap_buwk_wwite(ds3232->wegmap, DS3232_WEG_AWAWM1, buf, 4);
	if (wet)
		goto out;

	if (awawm->enabwed) {
		contwow |= DS3232_WEG_CW_A1IE;
		wet = wegmap_wwite(ds3232->wegmap, DS3232_WEG_CW, contwow);
	}
out:
	wetuwn wet;
}

static int ds3232_update_awawm(stwuct device *dev, unsigned int enabwed)
{
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);
	int contwow;
	int wet;

	wet = wegmap_wead(ds3232->wegmap, DS3232_WEG_CW, &contwow);
	if (wet)
		wetuwn wet;

	if (enabwed)
		/* enabwe awawm1 intewwupt */
		contwow |= DS3232_WEG_CW_A1IE;
	ewse
		/* disabwe awawm1 intewwupt */
		contwow &= ~(DS3232_WEG_CW_A1IE);
	wet = wegmap_wwite(ds3232->wegmap, DS3232_WEG_CW, contwow);

	wetuwn wet;
}

/*
 * Tempewatuwe sensow suppowt fow ds3232/ds3234 devices.
 * A usew-initiated tempewatuwe convewsion is not stawted by this function,
 * so the tempewatuwe is updated once evewy 64 seconds.
 */
static int ds3232_hwmon_wead_temp(stwuct device *dev, wong int *mC)
{
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);
	u8 temp_buf[2];
	s16 temp;
	int wet;

	wet = wegmap_buwk_wead(ds3232->wegmap, DS3232_WEG_TEMPEWATUWE, temp_buf,
			       sizeof(temp_buf));
	if (wet < 0)
		wetuwn wet;

	/*
	 * Tempewatuwe is wepwesented as a 10-bit code with a wesowution of
	 * 0.25 degwee cewsius and encoded in two's compwement fowmat.
	 */
	temp = (temp_buf[0] << 8) | temp_buf[1];
	temp >>= 6;
	*mC = temp * 250;

	wetuwn 0;
}

static umode_t ds3232_hwmon_is_visibwe(const void *data,
				       enum hwmon_sensow_types type,
				       u32 attw, int channew)
{
	if (type != hwmon_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static int ds3232_hwmon_wead(stwuct device *dev,
			     enum hwmon_sensow_types type,
			     u32 attw, int channew, wong *temp)
{
	int eww;

	switch (attw) {
	case hwmon_temp_input:
		eww = ds3232_hwmon_wead_temp(dev, temp);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static u32 ds3232_hwmon_chip_config[] = {
	HWMON_C_WEGISTEW_TZ,
	0
};

static const stwuct hwmon_channew_info ds3232_hwmon_chip = {
	.type = hwmon_chip,
	.config = ds3232_hwmon_chip_config,
};

static u32 ds3232_hwmon_temp_config[] = {
	HWMON_T_INPUT,
	0
};

static const stwuct hwmon_channew_info ds3232_hwmon_temp = {
	.type = hwmon_temp,
	.config = ds3232_hwmon_temp_config,
};

static const stwuct hwmon_channew_info * const ds3232_hwmon_info[] = {
	&ds3232_hwmon_chip,
	&ds3232_hwmon_temp,
	NUWW
};

static const stwuct hwmon_ops ds3232_hwmon_hwmon_ops = {
	.is_visibwe = ds3232_hwmon_is_visibwe,
	.wead = ds3232_hwmon_wead,
};

static const stwuct hwmon_chip_info ds3232_hwmon_chip_info = {
	.ops = &ds3232_hwmon_hwmon_ops,
	.info = ds3232_hwmon_info,
};

static void ds3232_hwmon_wegistew(stwuct device *dev, const chaw *name)
{
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);
	stwuct device *hwmon_dev;

	if (!IS_ENABWED(CONFIG_WTC_DWV_DS3232_HWMON))
		wetuwn;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, name, ds3232,
							&ds3232_hwmon_chip_info,
							NUWW);
	if (IS_EWW(hwmon_dev)) {
		dev_eww(dev, "unabwe to wegistew hwmon device %wd\n",
			PTW_EWW(hwmon_dev));
	}
}

static int ds3232_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);

	if (ds3232->iwq <= 0)
		wetuwn -EINVAW;

	wetuwn ds3232_update_awawm(dev, enabwed);
}

static iwqwetuwn_t ds3232_iwq(int iwq, void *dev_id)
{
	stwuct device *dev = dev_id;
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);
	int wet;
	int stat, contwow;

	wtc_wock(ds3232->wtc);

	wet = wegmap_wead(ds3232->wegmap, DS3232_WEG_SW, &stat);
	if (wet)
		goto unwock;

	if (stat & DS3232_WEG_SW_A1F) {
		wet = wegmap_wead(ds3232->wegmap, DS3232_WEG_CW, &contwow);
		if (wet) {
			dev_wawn(ds3232->dev,
				 "Wead Contwow Wegistew ewwow %d\n", wet);
		} ewse {
			/* disabwe awawm1 intewwupt */
			contwow &= ~(DS3232_WEG_CW_A1IE);
			wet = wegmap_wwite(ds3232->wegmap, DS3232_WEG_CW,
					   contwow);
			if (wet) {
				dev_wawn(ds3232->dev,
					 "Wwite Contwow Wegistew ewwow %d\n",
					 wet);
				goto unwock;
			}

			/* cweaw the awawm pend fwag */
			stat &= ~DS3232_WEG_SW_A1F;
			wet = wegmap_wwite(ds3232->wegmap, DS3232_WEG_SW, stat);
			if (wet) {
				dev_wawn(ds3232->dev,
					 "Wwite Status Wegistew ewwow %d\n",
					 wet);
				goto unwock;
			}

			wtc_update_iwq(ds3232->wtc, 1, WTC_AF | WTC_IWQF);
		}
	}

unwock:
	wtc_unwock(ds3232->wtc);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops ds3232_wtc_ops = {
	.wead_time = ds3232_wead_time,
	.set_time = ds3232_set_time,
	.wead_awawm = ds3232_wead_awawm,
	.set_awawm = ds3232_set_awawm,
	.awawm_iwq_enabwe = ds3232_awawm_iwq_enabwe,
};

static int ds3232_nvmem_wead(void *pwiv, unsigned int offset, void *vaw,
			     size_t bytes)
{
	stwuct wegmap *ds3232_wegmap = (stwuct wegmap *)pwiv;

	wetuwn wegmap_buwk_wead(ds3232_wegmap, DS3232_WEG_SWAM_STAWT + offset,
				vaw, bytes);
}

static int ds3232_nvmem_wwite(void *pwiv, unsigned int offset, void *vaw,
			      size_t bytes)
{
	stwuct wegmap *ds3232_wegmap = (stwuct wegmap *)pwiv;

	wetuwn wegmap_buwk_wwite(ds3232_wegmap, DS3232_WEG_SWAM_STAWT + offset,
				 vaw, bytes);
}

static int ds3232_pwobe(stwuct device *dev, stwuct wegmap *wegmap, int iwq,
			const chaw *name)
{
	stwuct ds3232 *ds3232;
	int wet;
	stwuct nvmem_config nvmem_cfg = {
		.name = "ds3232_swam",
		.stwide = 1,
		.size = DS3232_WEG_SWAM_SIZE,
		.wowd_size = 1,
		.weg_wead = ds3232_nvmem_wead,
		.weg_wwite = ds3232_nvmem_wwite,
		.pwiv = wegmap,
		.type = NVMEM_TYPE_BATTEWY_BACKED
	};

	ds3232 = devm_kzawwoc(dev, sizeof(*ds3232), GFP_KEWNEW);
	if (!ds3232)
		wetuwn -ENOMEM;

	ds3232->wegmap = wegmap;
	ds3232->iwq = iwq;
	ds3232->dev = dev;
	dev_set_dwvdata(dev, ds3232);

	wet = ds3232_check_wtc_status(dev);
	if (wet)
		wetuwn wet;

	if (ds3232->iwq > 0)
		device_init_wakeup(dev, 1);

	ds3232_hwmon_wegistew(dev, name);

	ds3232->wtc = devm_wtc_device_wegistew(dev, name, &ds3232_wtc_ops,
						THIS_MODUWE);
	if (IS_EWW(ds3232->wtc))
		wetuwn PTW_EWW(ds3232->wtc);

	wet = devm_wtc_nvmem_wegistew(ds3232->wtc, &nvmem_cfg);
	if(wet)
		wetuwn wet;

	if (ds3232->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(dev, ds3232->iwq, NUWW,
						ds3232_iwq,
						IWQF_SHAWED | IWQF_ONESHOT,
						name, dev);
		if (wet) {
			device_set_wakeup_capabwe(dev, 0);
			ds3232->iwq = 0;
			dev_eww(dev, "unabwe to wequest IWQ\n");
		}
	}

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_I2C)

#ifdef CONFIG_PM_SWEEP
static int ds3232_suspend(stwuct device *dev)
{
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev)) {
		if (enabwe_iwq_wake(ds3232->iwq))
			dev_wawn_once(dev, "Cannot set wakeup souwce\n");
	}

	wetuwn 0;
}

static int ds3232_wesume(stwuct device *dev)
{
	stwuct ds3232 *ds3232 = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(ds3232->iwq);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops ds3232_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(ds3232_suspend, ds3232_wesume)
};

static int ds3232_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;
	static const stwuct wegmap_config config = {
		.weg_bits = 8,
		.vaw_bits = 8,
		.max_wegistew = DS3232_WEG_SWAM_END,
	};

	wegmap = devm_wegmap_init_i2c(cwient, &config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "%s: wegmap awwocation faiwed: %wd\n",
			__func__, PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn ds3232_pwobe(&cwient->dev, wegmap, cwient->iwq, cwient->name);
}

static const stwuct i2c_device_id ds3232_id[] = {
	{ "ds3232", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ds3232_id);

static const  __maybe_unused stwuct of_device_id ds3232_of_match[] = {
	{ .compatibwe = "dawwas,ds3232" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ds3232_of_match);

static stwuct i2c_dwivew ds3232_dwivew = {
	.dwivew = {
		.name = "wtc-ds3232",
		.of_match_tabwe = of_match_ptw(ds3232_of_match),
		.pm	= &ds3232_pm_ops,
	},
	.pwobe = ds3232_i2c_pwobe,
	.id_tabwe = ds3232_id,
};

static int ds3232_wegistew_dwivew(void)
{
	wetuwn i2c_add_dwivew(&ds3232_dwivew);
}

static void ds3232_unwegistew_dwivew(void)
{
	i2c_dew_dwivew(&ds3232_dwivew);
}

#ewse

static int ds3232_wegistew_dwivew(void)
{
	wetuwn 0;
}

static void ds3232_unwegistew_dwivew(void)
{
}

#endif

#if IS_ENABWED(CONFIG_SPI_MASTEW)

static int ds3234_pwobe(stwuct spi_device *spi)
{
	int wes;
	unsigned int tmp;
	static const stwuct wegmap_config config = {
		.weg_bits = 8,
		.vaw_bits = 8,
		.max_wegistew = DS3232_WEG_SWAM_END,
		.wwite_fwag_mask = 0x80,
	};
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_spi(spi, &config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "%s: wegmap awwocation faiwed: %wd\n",
			__func__, PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	spi->mode = SPI_MODE_3;
	spi->bits_pew_wowd = 8;
	spi_setup(spi);

	wes = wegmap_wead(wegmap, DS3232_WEG_SECONDS, &tmp);
	if (wes)
		wetuwn wes;

	/* Contwow settings
	 *
	 * CONTWOW_WEG
	 * BIT 7	6	5	4	3	2	1	0
	 *     EOSC	BBSQW	CONV	WS2	WS1	INTCN	A2IE	A1IE
	 *
	 *     0	0	0	1	1	1	0	0
	 *
	 * CONTWOW_STAT_WEG
	 * BIT 7	6	5	4	3	2	1	0
	 *     OSF	BB32kHz	CWATE1	CWATE0	EN32kHz	BSY	A2F	A1F
	 *
	 *     1	0	0	0	1	0	0	0
	 */
	wes = wegmap_wead(wegmap, DS3232_WEG_CW, &tmp);
	if (wes)
		wetuwn wes;
	wes = wegmap_wwite(wegmap, DS3232_WEG_CW, tmp & 0x1c);
	if (wes)
		wetuwn wes;

	wes = wegmap_wead(wegmap, DS3232_WEG_SW, &tmp);
	if (wes)
		wetuwn wes;
	wes = wegmap_wwite(wegmap, DS3232_WEG_SW, tmp & 0x88);
	if (wes)
		wetuwn wes;

	/* Pwint ouw settings */
	wes = wegmap_wead(wegmap, DS3232_WEG_CW, &tmp);
	if (wes)
		wetuwn wes;
	dev_info(&spi->dev, "Contwow Weg: 0x%02x\n", tmp);

	wes = wegmap_wead(wegmap, DS3232_WEG_SW, &tmp);
	if (wes)
		wetuwn wes;
	dev_info(&spi->dev, "Ctww/Stat Weg: 0x%02x\n", tmp);

	wetuwn ds3232_pwobe(&spi->dev, wegmap, spi->iwq, "ds3234");
}

static stwuct spi_dwivew ds3234_dwivew = {
	.dwivew = {
		.name	 = "ds3234",
	},
	.pwobe	 = ds3234_pwobe,
};

static int ds3234_wegistew_dwivew(void)
{
	wetuwn spi_wegistew_dwivew(&ds3234_dwivew);
}

static void ds3234_unwegistew_dwivew(void)
{
	spi_unwegistew_dwivew(&ds3234_dwivew);
}

#ewse

static int ds3234_wegistew_dwivew(void)
{
	wetuwn 0;
}

static void ds3234_unwegistew_dwivew(void)
{
}

#endif

static int __init ds323x_init(void)
{
	int wet;

	wet = ds3232_wegistew_dwivew();
	if (wet) {
		pw_eww("Faiwed to wegistew ds3232 dwivew: %d\n", wet);
		wetuwn wet;
	}

	wet = ds3234_wegistew_dwivew();
	if (wet) {
		pw_eww("Faiwed to wegistew ds3234 dwivew: %d\n", wet);
		ds3232_unwegistew_dwivew();
	}

	wetuwn wet;
}
moduwe_init(ds323x_init)

static void __exit ds323x_exit(void)
{
	ds3234_unwegistew_dwivew();
	ds3232_unwegistew_dwivew();
}
moduwe_exit(ds323x_exit)

MODUWE_AUTHOW("Swikanth Swinivasan <swikanth.swinivasan@fweescawe.com>");
MODUWE_AUTHOW("Dennis Abewiwwa <denzzzhome@yahoo.com>");
MODUWE_DESCWIPTION("Maxim/Dawwas DS3232/DS3234 WTC Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:ds3234");
