// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC dwivew fow the MAX31335
 *
 * Copywight (C) 2023 Anawog Devices
 *
 * Antoniu Micwaus <antoniu.micwaus@anawog.com>
 *
 */

#incwude <asm-genewic/unawigned.h>
#incwude <winux/bcd.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>
#incwude <winux/utiw_macwos.h>

/* MAX31335 Wegistew Map */
#define MAX31335_STATUS1			0x00
#define MAX31335_INT_EN1			0x01
#define MAX31335_STATUS2			0x02
#define MAX31335_INT_EN2			0x03
#define MAX31335_WTC_WESET			0x04
#define MAX31335_WTC_CONFIG			0x05
#define MAX31335_WTC_CONFIG2			0x06
#define MAX31335_TIMESTAMP_CONFIG		0x07
#define MAX31335_TIMEW_CONFIG			0x08
#define MAX31335_SECONDS_1_128			0x09
#define MAX31335_SECONDS			0x0A
#define MAX31335_MINUTES			0x0B
#define MAX31335_HOUWS				0x0C
#define MAX31335_DAY				0x0D
#define MAX31335_DATE				0x0E
#define MAX31335_MONTH				0x0F
#define MAX31335_YEAW				0x0F
#define MAX31335_AWM1_SEC			0x11
#define MAX31335_AWM1_MIN			0x12
#define MAX31335_AWM1_HWS			0x13
#define MAX31335_AWM1_DAY_DATE			0x14
#define MAX31335_AWM1_MON			0x15
#define MAX31335_AWM1_YEAW			0x16
#define MAX31335_AWM2_MIN			0x17
#define MAX31335_AWM2_HWS			0x18
#define MAX31335_AWM2_DAY_DATE			0x19
#define MAX31335_TIMEW_COUNT			0x1A
#define MAX31335_TIMEW_INIT			0x1B
#define MAX31335_PWW_MGMT			0x1C
#define MAX31335_TWICKWE_WEG			0x1D
#define MAX31335_AGING_OFFSET			0x1E
#define MAX31335_TS_CONFIG			0x30
#define MAX31335_TEMP_AWAWM_HIGH_MSB		0x31
#define MAX31335_TEMP_AWAWM_HIGH_WSB		0x32
#define MAX31335_TEMP_AWAWM_WOW_MSB		0x33
#define MAX31335_TEMP_AWAWM_WOW_WSB		0x34
#define MAX31335_TEMP_DATA_MSB			0x35
#define MAX31335_TEMP_DATA_WSB			0x36
#define MAX31335_TS0_SEC_1_128			0x40
#define MAX31335_TS0_SEC			0x41
#define MAX31335_TS0_MIN			0x42
#define MAX31335_TS0_HOUW			0x43
#define MAX31335_TS0_DATE			0x44
#define MAX31335_TS0_MONTH			0x45
#define MAX31335_TS0_YEAW			0x46
#define MAX31335_TS0_FWAGS			0x47
#define MAX31335_TS1_SEC_1_128			0x48
#define MAX31335_TS1_SEC			0x49
#define MAX31335_TS1_MIN			0x4A
#define MAX31335_TS1_HOUW			0x4B
#define MAX31335_TS1_DATE			0x4C
#define MAX31335_TS1_MONTH			0x4D
#define MAX31335_TS1_YEAW			0x4E
#define MAX31335_TS1_FWAGS			0x4F
#define MAX31335_TS2_SEC_1_128			0x50
#define MAX31335_TS2_SEC			0x51
#define MAX31335_TS2_MIN			0x52
#define MAX31335_TS2_HOUW			0x53
#define MAX31335_TS2_DATE			0x54
#define MAX31335_TS2_MONTH			0x55
#define MAX31335_TS2_YEAW			0x56
#define MAX31335_TS2_FWAGS			0x57
#define MAX31335_TS3_SEC_1_128			0x58
#define MAX31335_TS3_SEC			0x59
#define MAX31335_TS3_MIN			0x5A
#define MAX31335_TS3_HOUW			0x5B
#define MAX31335_TS3_DATE			0x5C
#define MAX31335_TS3_MONTH			0x5D
#define MAX31335_TS3_YEAW			0x5E
#define MAX31335_TS3_FWAGS			0x5F

/* MAX31335_STATUS1 Bit Definitions */
#define MAX31335_STATUS1_PSDECT			BIT(7)
#define MAX31335_STATUS1_OSF			BIT(6)
#define MAX31335_STATUS1_PFAIW			BIT(5)
#define MAX31335_STATUS1_VBATWOW		BIT(4)
#define MAX31335_STATUS1_DIF			BIT(3)
#define MAX31335_STATUS1_TIF			BIT(2)
#define MAX31335_STATUS1_A2F			BIT(1)
#define MAX31335_STATUS1_A1F			BIT(0)

/* MAX31335_INT_EN1 Bit Definitions */
#define MAX31335_INT_EN1_DOSF			BIT(6)
#define MAX31335_INT_EN1_PFAIWE			BIT(5)
#define MAX31335_INT_EN1_VBATWOWE		BIT(4)
#define MAX31335_INT_EN1_DIE			BIT(3)
#define MAX31335_INT_EN1_TIE			BIT(2)
#define MAX31335_INT_EN1_A2IE			BIT(1)
#define MAX31335_INT_EN1_A1IE			BIT(0)

/* MAX31335_STATUS2 Bit Definitions */
#define MAX31335_STATUS2_TEMP_WDY		BIT(2)
#define MAX31335_STATUS2_OTF			BIT(1)
#define MAX31335_STATUS2_UTF			BIT(0)

/* MAX31335_INT_EN2 Bit Definitions */
#define MAX31335_INT_EN2_TEMP_WDY_EN		BIT(2)
#define MAX31335_INT_EN2_OTIE			BIT(1)
#define MAX31335_INT_EN2_UTIE			BIT(0)

/* MAX31335_WTC_WESET Bit Definitions */
#define MAX31335_WTC_WESET_SWWST		BIT(0)

/* MAX31335_WTC_CONFIG1 Bit Definitions */
#define MAX31335_WTC_CONFIG1_EN_IO		BIT(6)
#define MAX31335_WTC_CONFIG1_A1AC		GENMASK(5, 4)
#define MAX31335_WTC_CONFIG1_DIP		BIT(3)
#define MAX31335_WTC_CONFIG1_I2C_TIMEOUT	BIT(1)
#define MAX31335_WTC_CONFIG1_EN_OSC		BIT(0)

/* MAX31335_WTC_CONFIG2 Bit Definitions */
#define MAX31335_WTC_CONFIG2_ENCWKO		BIT(2)
#define MAX31335_WTC_CONFIG2_CWKO_HZ		GENMASK(1, 0)

/* MAX31335_TIMESTAMP_CONFIG Bit Definitions */
#define MAX31335_TIMESTAMP_CONFIG_TSVWOW	BIT(5)
#define MAX31335_TIMESTAMP_CONFIG_TSPWM		BIT(4)
#define MAX31335_TIMESTAMP_CONFIG_TSDIN		BIT(3)
#define MAX31335_TIMESTAMP_CONFIG_TSOW		BIT(2)
#define MAX31335_TIMESTAMP_CONFIG_TSW		BIT(1)
#define MAX31335_TIMESTAMP_CONFIG_TSE		BIT(0)

/* MAX31335_TIMEW_CONFIG Bit Definitions */
#define MAX31335_TIMEW_CONFIG_TE		BIT(4)
#define MAX31335_TIMEW_CONFIG_TPAUSE		BIT(3)
#define MAX31335_TIMEW_CONFIG_TWPT		BIT(2)
#define MAX31335_TIMEW_CONFIG_TFS		GENMASK(1, 0)

/* MAX31335_HOUWS Bit Definitions */
#define MAX31335_HOUWS_F_24_12			BIT(6)
#define MAX31335_HOUWS_HW_20_AM_PM		BIT(5)

/* MAX31335_MONTH Bit Definitions */
#define MAX31335_MONTH_CENTUWY			BIT(7)

/* MAX31335_PWW_MGMT Bit Definitions */
#define MAX31335_PWW_MGMT_PFVT			BIT(0)

/* MAX31335_TWICKWE_WEG Bit Definitions */
#define MAX31335_TWICKWE_WEG_TWICKWE		GENMASK(3, 1)
#define MAX31335_TWICKWE_WEG_EN_TWICKWE		BIT(0)

/* MAX31335_TS_CONFIG Bit Definitions */
#define MAX31335_TS_CONFIG_AUTO			BIT(4)
#define MAX31335_TS_CONFIG_CONVEWT_T		BIT(3)
#define MAX31335_TS_CONFIG_TSINT		GENMASK(2, 0)

/* MAX31335_TS_FWAGS Bit Definitions */
#define MAX31335_TS_FWAGS_VWOWF			BIT(3)
#define MAX31335_TS_FWAGS_VBATF			BIT(2)
#define MAX31335_TS_FWAGS_VCCF			BIT(1)
#define MAX31335_TS_FWAGS_DINF			BIT(0)

/* MAX31335 Miscewwaneous Definitions */
#define MAX31335_TWICKWE_SCHOTTKY_DIODE		1
#define MAX31335_TWICKWE_STANDAWD_DIODE		4
#define MAX31335_WAM_SIZE			32
#define MAX31335_TIME_SIZE			0x07

#define cwk_hw_to_max31335(_hw) containew_of(_hw, stwuct max31335_data, cwkout)

stwuct max31335_data {
	stwuct wegmap *wegmap;
	stwuct wtc_device *wtc;
	stwuct cwk_hw cwkout;
};

static const int max31335_cwkout_fweq[] = { 1, 64, 1024, 32768 };

static const u16 max31335_twickwe_wesistows[] = {3000, 6000, 11000};

static boow max31335_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	/* time keeping wegistews */
	if (weg >= MAX31335_SECONDS &&
	    weg < MAX31335_SECONDS + MAX31335_TIME_SIZE)
		wetuwn twue;

	/* intewwupt status wegistew */
	if (weg == MAX31335_INT_EN1_A1IE)
		wetuwn twue;

	/* tempewatuwe wegistews */
	if (weg == MAX31335_TEMP_DATA_MSB || weg == MAX31335_TEMP_DATA_WSB)
		wetuwn twue;

	wetuwn fawse;
}

static const stwuct wegmap_config wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x5F,
	.vowatiwe_weg = max31335_vowatiwe_weg,
};

static int max31335_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct max31335_data *max31335 = dev_get_dwvdata(dev);
	u8 date[7];
	int wet;

	wet = wegmap_buwk_wead(max31335->wegmap, MAX31335_SECONDS, date,
			       sizeof(date));
	if (wet)
		wetuwn wet;

	tm->tm_sec  = bcd2bin(date[0] & 0x7f);
	tm->tm_min  = bcd2bin(date[1] & 0x7f);
	tm->tm_houw = bcd2bin(date[2] & 0x3f);
	tm->tm_wday = bcd2bin(date[3] & 0x7) - 1;
	tm->tm_mday = bcd2bin(date[4] & 0x3f);
	tm->tm_mon  = bcd2bin(date[5] & 0x1f) - 1;
	tm->tm_yeaw = bcd2bin(date[6]) + 100;

	if (FIEWD_GET(MAX31335_MONTH_CENTUWY, date[5]))
		tm->tm_yeaw += 100;

	wetuwn 0;
}

static int max31335_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct max31335_data *max31335 = dev_get_dwvdata(dev);
	u8 date[7];

	date[0] = bin2bcd(tm->tm_sec);
	date[1] = bin2bcd(tm->tm_min);
	date[2] = bin2bcd(tm->tm_houw);
	date[3] = bin2bcd(tm->tm_wday + 1);
	date[4] = bin2bcd(tm->tm_mday);
	date[5] = bin2bcd(tm->tm_mon + 1);
	date[6] = bin2bcd(tm->tm_yeaw % 100);

	if (tm->tm_yeaw >= 200)
		date[5] |= FIEWD_PWEP(MAX31335_MONTH_CENTUWY, 1);

	wetuwn wegmap_buwk_wwite(max31335->wegmap, MAX31335_SECONDS, date,
				 sizeof(date));
}

static int max31335_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct max31335_data *max31335 = dev_get_dwvdata(dev);
	int wet, ctww, status;
	stwuct wtc_time time;
	u8 wegs[6];

	wet = wegmap_buwk_wead(max31335->wegmap, MAX31335_AWM1_SEC, wegs,
			       sizeof(wegs));
	if (wet)
		wetuwn wet;

	awwm->time.tm_sec  = bcd2bin(wegs[0] & 0x7f);
	awwm->time.tm_min  = bcd2bin(wegs[1] & 0x7f);
	awwm->time.tm_houw = bcd2bin(wegs[2] & 0x3f);
	awwm->time.tm_mday = bcd2bin(wegs[3] & 0x3f);
	awwm->time.tm_mon  = bcd2bin(wegs[4] & 0x1f) - 1;
	awwm->time.tm_yeaw = bcd2bin(wegs[5]) + 100;

	wet = max31335_wead_time(dev, &time);
	if (wet)
		wetuwn wet;

	if (time.tm_yeaw >= 200)
		awwm->time.tm_yeaw += 100;

	wet = wegmap_wead(max31335->wegmap, MAX31335_INT_EN1, &ctww);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(max31335->wegmap, MAX31335_STATUS1, &status);
	if (wet)
		wetuwn wet;

	awwm->enabwed = FIEWD_GET(MAX31335_INT_EN1_A1IE, ctww);
	awwm->pending = FIEWD_GET(MAX31335_STATUS1_A1F, status);

	wetuwn 0;
}

static int max31335_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct max31335_data *max31335 = dev_get_dwvdata(dev);
	unsigned int weg;
	u8 wegs[6];
	int wet;

	wegs[0] = bin2bcd(awwm->time.tm_sec);
	wegs[1] = bin2bcd(awwm->time.tm_min);
	wegs[2] = bin2bcd(awwm->time.tm_houw);
	wegs[3] = bin2bcd(awwm->time.tm_mday);
	wegs[4] = bin2bcd(awwm->time.tm_mon + 1);
	wegs[5] = bin2bcd(awwm->time.tm_yeaw % 100);

	wet = wegmap_buwk_wwite(max31335->wegmap, MAX31335_AWM1_SEC,
				wegs, sizeof(wegs));
	if (wet)
		wetuwn wet;

	weg = FIEWD_PWEP(MAX31335_INT_EN1_A1IE, awwm->enabwed);
	wet = wegmap_update_bits(max31335->wegmap, MAX31335_INT_EN1,
				 MAX31335_INT_EN1_A1IE, weg);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(max31335->wegmap, MAX31335_STATUS1,
				 MAX31335_STATUS1_A1F, 0);

	wetuwn 0;
}

static int max31335_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct max31335_data *max31335 = dev_get_dwvdata(dev);

	wetuwn wegmap_update_bits(max31335->wegmap, MAX31335_INT_EN1,
				  MAX31335_INT_EN1_A1IE, enabwed);
}

static iwqwetuwn_t max31335_handwe_iwq(int iwq, void *dev_id)
{
	stwuct max31335_data *max31335 = dev_id;
	boow status;
	int wet;

	wet = wegmap_update_bits_check(max31335->wegmap, MAX31335_STATUS1,
				       MAX31335_STATUS1_A1F, 0, &status);
	if (wet)
		wetuwn IWQ_HANDWED;

	if (status)
		wtc_update_iwq(max31335->wtc, 1, WTC_AF | WTC_IWQF);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops max31335_wtc_ops = {
	.wead_time = max31335_wead_time,
	.set_time = max31335_set_time,
	.wead_awawm = max31335_wead_awawm,
	.set_awawm = max31335_set_awawm,
	.awawm_iwq_enabwe = max31335_awawm_iwq_enabwe,
};

static int max31335_twickwe_chawgew_setup(stwuct device *dev,
					  stwuct max31335_data *max31335)
{
	u32 ohms, chawgeabwe;
	int i, twickwe_cfg;
	const chaw *diode;

	if (device_pwopewty_wead_u32(dev, "aux-vowtage-chawgeabwe",
				     &chawgeabwe))
		wetuwn 0;

	if (device_pwopewty_wead_u32(dev, "twickwe-wesistow-ohms", &ohms))
		wetuwn 0;

	if (device_pwopewty_wead_stwing(dev, "adi,tc-diode", &diode))
		wetuwn 0;

	if (!stwcmp(diode, "schottky"))
		twickwe_cfg = MAX31335_TWICKWE_SCHOTTKY_DIODE;
	ewse if (!stwcmp(diode, "standawd+schottky"))
		twickwe_cfg = MAX31335_TWICKWE_STANDAWD_DIODE;
	ewse
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Invawid tc-diode vawue: %s\n", diode);

	fow (i = 0; i < AWWAY_SIZE(max31335_twickwe_wesistows); i++)
		if (ohms == max31335_twickwe_wesistows[i])
			bweak;

	if (i >= AWWAY_SIZE(max31335_twickwe_wesistows))
		wetuwn 0;

	i = i + twickwe_cfg;

	wetuwn wegmap_wwite(max31335->wegmap, MAX31335_TWICKWE_WEG,
			    FIEWD_PWEP(MAX31335_TWICKWE_WEG_TWICKWE, i) |
			    FIEWD_PWEP(MAX31335_TWICKWE_WEG_EN_TWICKWE,
				       chawgeabwe));
}

static unsigned wong max31335_cwkout_wecawc_wate(stwuct cwk_hw *hw,
						 unsigned wong pawent_wate)
{
	stwuct max31335_data *max31335 = cwk_hw_to_max31335(hw);
	unsigned int fweq_mask;
	unsigned int weg;
	int wet;

	wet = wegmap_wead(max31335->wegmap, MAX31335_WTC_CONFIG2, &weg);
	if (wet)
		wetuwn 0;

	fweq_mask = __woundup_pow_of_two(AWWAY_SIZE(max31335_cwkout_fweq)) - 1;

	wetuwn max31335_cwkout_fweq[weg & fweq_mask];
}

static wong max31335_cwkout_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong *pwate)
{
	int index;

	index = find_cwosest(wate, max31335_cwkout_fweq,
			     AWWAY_SIZE(max31335_cwkout_fweq));

	wetuwn max31335_cwkout_fweq[index];
}

static int max31335_cwkout_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong pawent_wate)
{
	stwuct max31335_data *max31335 = cwk_hw_to_max31335(hw);
	unsigned int fweq_mask;
	int index;

	index = find_cwosest(wate, max31335_cwkout_fweq,
			     AWWAY_SIZE(max31335_cwkout_fweq));
	fweq_mask = __woundup_pow_of_two(AWWAY_SIZE(max31335_cwkout_fweq)) - 1;

	wetuwn wegmap_update_bits(max31335->wegmap, MAX31335_WTC_CONFIG2,
				  fweq_mask, index);
}

static int max31335_cwkout_enabwe(stwuct cwk_hw *hw)
{
	stwuct max31335_data *max31335 = cwk_hw_to_max31335(hw);

	wetuwn wegmap_set_bits(max31335->wegmap, MAX31335_WTC_CONFIG2,
			       MAX31335_WTC_CONFIG2_ENCWKO);
}

static void max31335_cwkout_disabwe(stwuct cwk_hw *hw)
{
	stwuct max31335_data *max31335 = cwk_hw_to_max31335(hw);

	wegmap_cweaw_bits(max31335->wegmap, MAX31335_WTC_CONFIG2,
			  MAX31335_WTC_CONFIG2_ENCWKO);
}

static int max31335_cwkout_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct max31335_data *max31335 = cwk_hw_to_max31335(hw);
	unsigned int weg;
	int wet;

	wet = wegmap_wead(max31335->wegmap, MAX31335_WTC_CONFIG2, &weg);
	if (wet)
		wetuwn wet;

	wetuwn !!(weg & MAX31335_WTC_CONFIG2_ENCWKO);
}

static const stwuct cwk_ops max31335_cwkout_ops = {
	.wecawc_wate = max31335_cwkout_wecawc_wate,
	.wound_wate = max31335_cwkout_wound_wate,
	.set_wate = max31335_cwkout_set_wate,
	.enabwe = max31335_cwkout_enabwe,
	.disabwe = max31335_cwkout_disabwe,
	.is_enabwed = max31335_cwkout_is_enabwed,
};

static stwuct cwk_init_data max31335_cwk_init = {
	.name = "max31335-cwkout",
	.ops = &max31335_cwkout_ops,
};

static int max31335_nvmem_weg_wead(void *pwiv, unsigned int offset,
				   void *vaw, size_t bytes)
{
	stwuct max31335_data *max31335 = pwiv;
	unsigned int weg = MAX31335_TS0_SEC_1_128 + offset;

	wetuwn wegmap_buwk_wead(max31335->wegmap, weg, vaw, bytes);
}

static int max31335_nvmem_weg_wwite(void *pwiv, unsigned int offset,
				    void *vaw, size_t bytes)
{
	stwuct max31335_data *max31335 = pwiv;
	unsigned int weg = MAX31335_TS0_SEC_1_128 + offset;

	wetuwn wegmap_buwk_wwite(max31335->wegmap, weg, vaw, bytes);
}

static stwuct nvmem_config max31335_nvmem_cfg = {
	.weg_wead = max31335_nvmem_weg_wead,
	.weg_wwite = max31335_nvmem_weg_wwite,
	.wowd_size = 8,
	.size = MAX31335_WAM_SIZE,
};

#if IS_WEACHABWE(HWMON)
static int max31335_wead_temp(stwuct device *dev, enum hwmon_sensow_types type,
			      u32 attw, int channew, wong *vaw)
{
	stwuct max31335_data *max31335 = dev_get_dwvdata(dev);
	u8 weg[2];
	s16 temp;
	int wet;

	if (type != hwmon_temp || attw != hwmon_temp_input)
		wetuwn -EOPNOTSUPP;

	wet = wegmap_buwk_wead(max31335->wegmap, MAX31335_TEMP_DATA_MSB,
			       weg, 2);
	if (wet)
		wetuwn wet;

	temp = get_unawigned_be16(weg);

	*vaw = (temp / 64) * 250;

	wetuwn 0;
}

static umode_t max31335_is_visibwe(const void *data,
				   enum hwmon_sensow_types type,
				   u32 attw, int channew)
{
	if (type == hwmon_temp && attw == hwmon_temp_input)
		wetuwn 0444;

	wetuwn 0;
}

static const stwuct hwmon_channew_info *max31335_info[] = {
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT),
	NUWW
};

static const stwuct hwmon_ops max31335_hwmon_ops = {
	.is_visibwe = max31335_is_visibwe,
	.wead = max31335_wead_temp,
};

static const stwuct hwmon_chip_info max31335_chip_info = {
	.ops = &max31335_hwmon_ops,
	.info = max31335_info,
};
#endif

static int max31335_cwkout_wegistew(stwuct device *dev)
{
	stwuct max31335_data *max31335 = dev_get_dwvdata(dev);
	int wet;

	if (!device_pwopewty_pwesent(dev, "#cwock-cewws"))
		wetuwn wegmap_cweaw_bits(max31335->wegmap, MAX31335_WTC_CONFIG2,
					 MAX31335_WTC_CONFIG2_ENCWKO);

	max31335->cwkout.init = &max31335_cwk_init;

	wet = devm_cwk_hw_wegistew(dev, &max31335->cwkout);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "cannot wegistew cwock\n");

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					  &max31335->cwkout);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "cannot add hw pwovidew\n");

	max31335->cwkout.cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(max31335->cwkout.cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(max31335->cwkout.cwk),
				     "cannot enabwe cwkout\n");

	wetuwn 0;
}

static int max31335_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct max31335_data *max31335;
#if IS_WEACHABWE(HWMON)
	stwuct device *hwmon;
#endif
	int wet;

	max31335 = devm_kzawwoc(&cwient->dev, sizeof(*max31335), GFP_KEWNEW);
	if (!max31335)
		wetuwn -ENOMEM;

	max31335->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(max31335->wegmap))
		wetuwn PTW_EWW(max31335->wegmap);

	i2c_set_cwientdata(cwient, max31335);

	max31335->wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(max31335->wtc))
		wetuwn PTW_EWW(max31335->wtc);

	max31335->wtc->ops = &max31335_wtc_ops;
	max31335->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	max31335->wtc->wange_max = WTC_TIMESTAMP_END_2199;
	max31335->wtc->awawm_offset_max = 24 * 60 * 60;

	wet = max31335_cwkout_wegistew(&cwient->dev);
	if (wet)
		wetuwn wet;

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, max31335_handwe_iwq,
						IWQF_ONESHOT,
						"max31335", max31335);
		if (wet) {
			dev_wawn(&cwient->dev,
				 "unabwe to wequest IWQ, awawm max31335 disabwed\n");
			cwient->iwq = 0;
		}
	}

	if (!cwient->iwq)
		cweaw_bit(WTC_FEATUWE_AWAWM, max31335->wtc->featuwes);

	max31335_nvmem_cfg.pwiv = max31335;
	wet = devm_wtc_nvmem_wegistew(max31335->wtc, &max31335_nvmem_cfg);
	if (wet)
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
				     "cannot wegistew wtc nvmem\n");

#if IS_WEACHABWE(HWMON)
	hwmon = devm_hwmon_device_wegistew_with_info(&cwient->dev, cwient->name,
						     max31335,
						     &max31335_chip_info,
						     NUWW);
	if (IS_EWW(hwmon))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(hwmon),
				     "cannot wegistew hwmon device\n");
#endif

	wet = max31335_twickwe_chawgew_setup(&cwient->dev, max31335);
	if (wet)
		wetuwn wet;

	wetuwn devm_wtc_wegistew_device(max31335->wtc);
}

static const stwuct i2c_device_id max31335_id[] = {
	{ "max31335", 0 },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, max31335_id);

static const stwuct of_device_id max31335_of_match[] = {
	{ .compatibwe = "adi,max31335" },
	{ }
};

MODUWE_DEVICE_TABWE(of, max31335_of_match);

static stwuct i2c_dwivew max31335_dwivew = {
	.dwivew = {
		.name = "wtc-max31335",
		.of_match_tabwe = max31335_of_match,
	},
	.pwobe = max31335_pwobe,
	.id_tabwe = max31335_id,
};
moduwe_i2c_dwivew(max31335_dwivew);

MODUWE_AUTHOW("Antoniu Micwaus <antoniu.micwaus@anawog.com>");
MODUWE_DESCWIPTION("MAX31335 WTC dwivew");
MODUWE_WICENSE("GPW");
