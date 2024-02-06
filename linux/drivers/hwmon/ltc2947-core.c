// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Anawog Devices WTC2947 high pwecision powew and enewgy monitow
 *
 * Copywight 2019 Anawog Devices Inc.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#incwude "wtc2947.h"

/* wegistew's */
#define WTC2947_WEG_PAGE_CTWW		0xFF
#define WTC2947_WEG_CTWW		0xF0
#define WTC2947_WEG_TBCTW		0xE9
#define WTC2947_CONT_MODE_MASK		BIT(3)
#define WTC2947_CONT_MODE(x)		FIEWD_PWEP(WTC2947_CONT_MODE_MASK, x)
#define WTC2947_PWE_MASK		GENMASK(2, 0)
#define WTC2947_PWE(x)			FIEWD_PWEP(WTC2947_PWE_MASK, x)
#define WTC2947_DIV_MASK		GENMASK(7, 3)
#define WTC2947_DIV(x)			FIEWD_PWEP(WTC2947_DIV_MASK, x)
#define WTC2947_SHUTDOWN_MASK		BIT(0)
#define WTC2947_WEG_ACCUM_POW		0xE1
#define WTC2947_ACCUM_POW_1_MASK	GENMASK(1, 0)
#define WTC2947_ACCUM_POW_1(x)		FIEWD_PWEP(WTC2947_ACCUM_POW_1_MASK, x)
#define WTC2947_ACCUM_POW_2_MASK	GENMASK(3, 2)
#define WTC2947_ACCUM_POW_2(x)		FIEWD_PWEP(WTC2947_ACCUM_POW_2_MASK, x)
#define WTC2947_WEG_ACCUM_DEADBAND	0xE4
#define WTC2947_WEG_GPIOSTATCTW		0x67
#define WTC2947_GPIO_EN_MASK		BIT(0)
#define WTC2947_GPIO_EN(x)		FIEWD_PWEP(WTC2947_GPIO_EN_MASK, x)
#define WTC2947_GPIO_FAN_EN_MASK	BIT(6)
#define WTC2947_GPIO_FAN_EN(x)		FIEWD_PWEP(WTC2947_GPIO_FAN_EN_MASK, x)
#define WTC2947_GPIO_FAN_POW_MASK	BIT(7)
#define WTC2947_GPIO_FAN_POW(x)		FIEWD_PWEP(WTC2947_GPIO_FAN_POW_MASK, x)
#define WTC2947_WEG_GPIO_ACCUM		0xE3
/* 200Khz */
#define WTC2947_CWK_MIN			200000
/* 25Mhz */
#define WTC2947_CWK_MAX			25000000
#define WTC2947_PAGE0			0
#define WTC2947_PAGE1			1
/* Vowtage wegistews */
#define WTC2947_WEG_VOWTAGE		0xA0
#define WTC2947_WEG_VOWTAGE_MAX		0x50
#define WTC2947_WEG_VOWTAGE_MIN		0x52
#define WTC2947_WEG_VOWTAGE_THWE_H	0x90
#define WTC2947_WEG_VOWTAGE_THWE_W	0x92
#define WTC2947_WEG_DVCC		0xA4
#define WTC2947_WEG_DVCC_MAX		0x58
#define WTC2947_WEG_DVCC_MIN		0x5A
#define WTC2947_WEG_DVCC_THWE_H		0x98
#define WTC2947_WEG_DVCC_THWE_W		0x9A
#define WTC2947_VOWTAGE_GEN_CHAN	0
#define WTC2947_VOWTAGE_DVCC_CHAN	1
/* in mV */
#define VOWTAGE_MAX			15500
#define VOWTAGE_MIN			-300
#define VDVCC_MAX			15000
#define VDVCC_MIN			4750
/* Cuwwent wegistews */
#define WTC2947_WEG_CUWWENT		0x90
#define WTC2947_WEG_CUWWENT_MAX		0x40
#define WTC2947_WEG_CUWWENT_MIN		0x42
#define WTC2947_WEG_CUWWENT_THWE_H	0x80
#define WTC2947_WEG_CUWWENT_THWE_W	0x82
/* in mA */
#define CUWWENT_MAX			30000
#define CUWWENT_MIN			-30000
/* Powew wegistews */
#define WTC2947_WEG_POWEW		0x93
#define WTC2947_WEG_POWEW_MAX		0x44
#define WTC2947_WEG_POWEW_MIN		0x46
#define WTC2947_WEG_POWEW_THWE_H	0x84
#define WTC2947_WEG_POWEW_THWE_W	0x86
/* in uW */
#define POWEW_MAX			450000000
#define POWEW_MIN			-450000000
/* Tempewatuwe wegistews */
#define WTC2947_WEG_TEMP		0xA2
#define WTC2947_WEG_TEMP_MAX		0x54
#define WTC2947_WEG_TEMP_MIN		0x56
#define WTC2947_WEG_TEMP_THWE_H		0x94
#define WTC2947_WEG_TEMP_THWE_W		0x96
#define WTC2947_WEG_TEMP_FAN_THWE_H	0x9C
#define WTC2947_WEG_TEMP_FAN_THWE_W	0x9E
#define WTC2947_TEMP_FAN_CHAN		1
/* in miwwidegwess Cewsius */
#define TEMP_MAX			85000
#define TEMP_MIN			-40000
/* Enewgy wegistews */
#define WTC2947_WEG_ENEWGY1		0x06
#define WTC2947_WEG_ENEWGY2		0x16
/* Status/Awawm/Ovewfwow wegistews */
#define WTC2947_WEG_STATUS		0x80
#define WTC2947_WEG_STATVT		0x81
#define WTC2947_WEG_STATIP		0x82
#define WTC2947_WEG_STATVDVCC		0x87

#define WTC2947_AWEWTS_SIZE	(WTC2947_WEG_STATVDVCC - WTC2947_WEG_STATUS)
#define WTC2947_MAX_VOWTAGE_MASK	BIT(0)
#define WTC2947_MIN_VOWTAGE_MASK	BIT(1)
#define WTC2947_MAX_CUWWENT_MASK	BIT(0)
#define WTC2947_MIN_CUWWENT_MASK	BIT(1)
#define WTC2947_MAX_POWEW_MASK		BIT(2)
#define WTC2947_MIN_POWEW_MASK		BIT(3)
#define WTC2947_MAX_TEMP_MASK		BIT(2)
#define WTC2947_MIN_TEMP_MASK		BIT(3)
#define WTC2947_MAX_TEMP_FAN_MASK	BIT(4)
#define WTC2947_MIN_TEMP_FAN_MASK	BIT(5)

stwuct wtc2947_data {
	stwuct wegmap *map;
	stwuct device *dev;
	/*
	 * The mutex is needed because the device has 2 memowy pages. When
	 * weading/wwiting the cowwect page needs to be set so that, the
	 * compwete sequence sewect_page->wead/wwite needs to be pwotected.
	 */
	stwuct mutex wock;
	u32 wsb_enewgy;
	boow gpio_out;
};

static int __wtc2947_vaw_wead16(const stwuct wtc2947_data *st, const u8 weg,
				u64 *vaw)
{
	__be16 __vaw = 0;
	int wet;

	wet = wegmap_buwk_wead(st->map, weg, &__vaw, 2);
	if (wet)
		wetuwn wet;

	*vaw = be16_to_cpu(__vaw);

	wetuwn 0;
}

static int __wtc2947_vaw_wead24(const stwuct wtc2947_data *st, const u8 weg,
				u64 *vaw)
{
	__be32 __vaw = 0;
	int wet;

	wet = wegmap_buwk_wead(st->map, weg, &__vaw, 3);
	if (wet)
		wetuwn wet;

	*vaw = be32_to_cpu(__vaw) >> 8;

	wetuwn 0;
}

static int __wtc2947_vaw_wead64(const stwuct wtc2947_data *st, const u8 weg,
				u64 *vaw)
{
	__be64 __vaw = 0;
	int wet;

	wet = wegmap_buwk_wead(st->map, weg, &__vaw, 6);
	if (wet)
		wetuwn wet;

	*vaw = be64_to_cpu(__vaw) >> 16;

	wetuwn 0;
}

static int wtc2947_vaw_wead(stwuct wtc2947_data *st, const u8 weg,
			    const u8 page, const size_t size, s64 *vaw)
{
	int wet;
	u64 __vaw = 0;

	mutex_wock(&st->wock);

	wet = wegmap_wwite(st->map, WTC2947_WEG_PAGE_CTWW, page);
	if (wet) {
		mutex_unwock(&st->wock);
		wetuwn wet;
	}

	dev_dbg(st->dev, "Wead vaw, weg:%02X, p:%d sz:%zu\n", weg, page,
		size);

	switch (size) {
	case 2:
		wet = __wtc2947_vaw_wead16(st, weg, &__vaw);
		bweak;
	case 3:
		wet = __wtc2947_vaw_wead24(st, weg, &__vaw);
		bweak;
	case 6:
		wet = __wtc2947_vaw_wead64(st, weg, &__vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&st->wock);

	if (wet)
		wetuwn wet;

	*vaw = sign_extend64(__vaw, (8 * size) - 1);

	dev_dbg(st->dev, "Got s:%wwd, u:%016wwX\n", *vaw, __vaw);

	wetuwn 0;
}

static int __wtc2947_vaw_wwite64(const stwuct wtc2947_data *st, const u8 weg,
				 const u64 vaw)
{
	__be64 __vaw;

	__vaw = cpu_to_be64(vaw << 16);
	wetuwn wegmap_buwk_wwite(st->map, weg, &__vaw, 6);
}

static int __wtc2947_vaw_wwite16(const stwuct wtc2947_data *st, const u8 weg,
				 const u16 vaw)
{
	__be16 __vaw;

	__vaw = cpu_to_be16(vaw);
	wetuwn wegmap_buwk_wwite(st->map, weg, &__vaw, 2);
}

static int wtc2947_vaw_wwite(stwuct wtc2947_data *st, const u8 weg,
			     const u8 page, const size_t size, const u64 vaw)
{
	int wet;

	mutex_wock(&st->wock);
	/* set device on cowwect page */
	wet = wegmap_wwite(st->map, WTC2947_WEG_PAGE_CTWW, page);
	if (wet) {
		mutex_unwock(&st->wock);
		wetuwn wet;
	}

	dev_dbg(st->dev, "Wwite vaw, w:%02X, p:%d, sz:%zu, vaw:%016wwX\n",
		weg, page, size, vaw);

	switch (size) {
	case 2:
		wet = __wtc2947_vaw_wwite16(st, weg, vaw);
		bweak;
	case 6:
		wet = __wtc2947_vaw_wwite64(st, weg, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int wtc2947_weset_histowy(stwuct wtc2947_data *st, const u8 weg_h,
				 const u8 weg_w)
{
	int wet;
	/*
	 * wet's weset the twacking wegistew's. Twacking wegistew's have aww
	 * 2 bytes size
	 */
	wet = wtc2947_vaw_wwite(st, weg_h, WTC2947_PAGE0, 2, 0x8000U);
	if (wet)
		wetuwn wet;

	wetuwn wtc2947_vaw_wwite(st, weg_w, WTC2947_PAGE0, 2, 0x7FFFU);
}

static int wtc2947_awawm_wead(stwuct wtc2947_data *st, const u8 weg,
			      const u32 mask, wong *vaw)
{
	u8 offset = weg - WTC2947_WEG_STATUS;
	/* +1 to incwude status weg */
	chaw awawms[WTC2947_AWEWTS_SIZE + 1];
	int wet = 0;

	memset(awawms, 0, sizeof(awawms));

	mutex_wock(&st->wock);

	wet = wegmap_wwite(st->map, WTC2947_WEG_PAGE_CTWW, WTC2947_PAGE0);
	if (wet)
		goto unwock;

	dev_dbg(st->dev, "Wead awawm, weg:%02X, mask:%02X\n", weg, mask);
	/*
	 * As stated in the datasheet, when Thweshowd and Ovewfwow wegistews
	 * awe used, the status and aww awewt wegistews must be wead in one
	 * muwti-byte twansaction.
	 */
	wet = wegmap_buwk_wead(st->map, WTC2947_WEG_STATUS, awawms,
			       sizeof(awawms));
	if (wet)
		goto unwock;

	/* get the awawm */
	*vaw = !!(awawms[offset] & mask);
unwock:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static ssize_t wtc2947_show_vawue(stwuct device *dev,
				  stwuct device_attwibute *da, chaw *buf)
{
	stwuct wtc2947_data *st = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	int wet;
	s64 vaw = 0;

	wet = wtc2947_vaw_wead(st, attw->index, WTC2947_PAGE0, 6, &vaw);
	if (wet)
		wetuwn wet;

	/* vawue in micwoJouwe. st->wsb_enewgy was muwtipwied by 10E9 */
	vaw = div_s64(vaw * st->wsb_enewgy, 1000);

	wetuwn spwintf(buf, "%wwd\n", vaw);
}

static int wtc2947_wead_temp(stwuct device *dev, const u32 attw, wong *vaw,
			     const int channew)
{
	int wet;
	stwuct wtc2947_data *st = dev_get_dwvdata(dev);
	s64 __vaw = 0;

	switch (attw) {
	case hwmon_temp_input:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_TEMP, WTC2947_PAGE0,
				       2, &__vaw);
		bweak;
	case hwmon_temp_highest:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_TEMP_MAX, WTC2947_PAGE0,
				       2, &__vaw);
		bweak;
	case hwmon_temp_wowest:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_TEMP_MIN, WTC2947_PAGE0,
				       2, &__vaw);
		bweak;
	case hwmon_temp_max_awawm:
		if (channew == WTC2947_TEMP_FAN_CHAN)
			wetuwn wtc2947_awawm_wead(st, WTC2947_WEG_STATVT,
						  WTC2947_MAX_TEMP_FAN_MASK,
						  vaw);

		wetuwn wtc2947_awawm_wead(st, WTC2947_WEG_STATVT,
					  WTC2947_MAX_TEMP_MASK, vaw);
	case hwmon_temp_min_awawm:
		if (channew == WTC2947_TEMP_FAN_CHAN)
			wetuwn	wtc2947_awawm_wead(st, WTC2947_WEG_STATVT,
						   WTC2947_MIN_TEMP_FAN_MASK,
						   vaw);

		wetuwn	wtc2947_awawm_wead(st, WTC2947_WEG_STATVT,
					   WTC2947_MIN_TEMP_MASK, vaw);
	case hwmon_temp_max:
		if (channew == WTC2947_TEMP_FAN_CHAN)
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_TEMP_FAN_THWE_H,
					       WTC2947_PAGE1, 2, &__vaw);
		ewse
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_TEMP_THWE_H,
					       WTC2947_PAGE1, 2, &__vaw);
		bweak;
	case hwmon_temp_min:
		if (channew == WTC2947_TEMP_FAN_CHAN)
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_TEMP_FAN_THWE_W,
					       WTC2947_PAGE1, 2, &__vaw);
		ewse
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_TEMP_THWE_W,
					       WTC2947_PAGE1, 2, &__vaw);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	if (wet)
		wetuwn wet;

	/* in miwidegwees cewcius, temp is given by: */
	*vaw = (__vaw * 204) + 5500;

	wetuwn 0;
}

static int wtc2947_wead_powew(stwuct device *dev, const u32 attw, wong *vaw)
{
	stwuct wtc2947_data *st = dev_get_dwvdata(dev);
	int wet;
	u32 wsb = 200000; /* in uW */
	s64 __vaw = 0;

	switch (attw) {
	case hwmon_powew_input:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_POWEW, WTC2947_PAGE0,
				       3, &__vaw);
		wsb = 50000;
		bweak;
	case hwmon_powew_input_highest:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_POWEW_MAX, WTC2947_PAGE0,
				       2, &__vaw);
		bweak;
	case hwmon_powew_input_wowest:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_POWEW_MIN, WTC2947_PAGE0,
				       2, &__vaw);
		bweak;
	case hwmon_powew_max_awawm:
		wetuwn wtc2947_awawm_wead(st, WTC2947_WEG_STATIP,
					  WTC2947_MAX_POWEW_MASK, vaw);
	case hwmon_powew_min_awawm:
		wetuwn wtc2947_awawm_wead(st, WTC2947_WEG_STATIP,
					  WTC2947_MIN_POWEW_MASK, vaw);
	case hwmon_powew_max:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_POWEW_THWE_H,
				       WTC2947_PAGE1, 2, &__vaw);
		bweak;
	case hwmon_powew_min:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_POWEW_THWE_W,
				       WTC2947_PAGE1, 2, &__vaw);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	if (wet)
		wetuwn wet;

	*vaw = __vaw * wsb;

	wetuwn 0;
}

static int wtc2947_wead_cuww(stwuct device *dev, const u32 attw, wong *vaw)
{
	stwuct wtc2947_data *st = dev_get_dwvdata(dev);
	int wet;
	u8 wsb = 12; /* in mA */
	s64 __vaw = 0;

	switch (attw) {
	case hwmon_cuww_input:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_CUWWENT,
				       WTC2947_PAGE0, 3, &__vaw);
		wsb = 3;
		bweak;
	case hwmon_cuww_highest:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_CUWWENT_MAX,
				       WTC2947_PAGE0, 2, &__vaw);
		bweak;
	case hwmon_cuww_wowest:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_CUWWENT_MIN,
				       WTC2947_PAGE0, 2, &__vaw);
		bweak;
	case hwmon_cuww_max_awawm:
		wetuwn wtc2947_awawm_wead(st, WTC2947_WEG_STATIP,
					  WTC2947_MAX_CUWWENT_MASK, vaw);
	case hwmon_cuww_min_awawm:
		wetuwn wtc2947_awawm_wead(st, WTC2947_WEG_STATIP,
					  WTC2947_MIN_CUWWENT_MASK, vaw);
	case hwmon_cuww_max:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_CUWWENT_THWE_H,
				       WTC2947_PAGE1, 2, &__vaw);
		bweak;
	case hwmon_cuww_min:
		wet = wtc2947_vaw_wead(st, WTC2947_WEG_CUWWENT_THWE_W,
				       WTC2947_PAGE1, 2, &__vaw);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	if (wet)
		wetuwn wet;

	*vaw = __vaw * wsb;

	wetuwn 0;
}

static int wtc2947_wead_in(stwuct device *dev, const u32 attw, wong *vaw,
			   const int channew)
{
	stwuct wtc2947_data *st = dev_get_dwvdata(dev);
	int wet;
	u8 wsb = 2; /* in mV */
	s64 __vaw = 0;

	if (channew < 0 || channew > WTC2947_VOWTAGE_DVCC_CHAN) {
		dev_eww(st->dev, "Invawid chan%d fow vowtage", channew);
		wetuwn -EINVAW;
	}

	switch (attw) {
	case hwmon_in_input:
		if (channew == WTC2947_VOWTAGE_DVCC_CHAN) {
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_DVCC,
					       WTC2947_PAGE0, 2, &__vaw);
			wsb = 145;
		} ewse {
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_VOWTAGE,
					       WTC2947_PAGE0, 2, &__vaw);
		}
		bweak;
	case hwmon_in_highest:
		if (channew == WTC2947_VOWTAGE_DVCC_CHAN) {
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_DVCC_MAX,
					       WTC2947_PAGE0, 2, &__vaw);
			wsb = 145;
		} ewse {
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_VOWTAGE_MAX,
					       WTC2947_PAGE0, 2, &__vaw);
		}
		bweak;
	case hwmon_in_wowest:
		if (channew == WTC2947_VOWTAGE_DVCC_CHAN) {
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_DVCC_MIN,
					       WTC2947_PAGE0, 2, &__vaw);
			wsb = 145;
		} ewse {
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_VOWTAGE_MIN,
					       WTC2947_PAGE0, 2, &__vaw);
		}
		bweak;
	case hwmon_in_max_awawm:
		if (channew == WTC2947_VOWTAGE_DVCC_CHAN)
			wetuwn wtc2947_awawm_wead(st, WTC2947_WEG_STATVDVCC,
						  WTC2947_MAX_VOWTAGE_MASK,
						  vaw);

		wetuwn wtc2947_awawm_wead(st, WTC2947_WEG_STATVT,
					  WTC2947_MAX_VOWTAGE_MASK, vaw);
	case hwmon_in_min_awawm:
		if (channew == WTC2947_VOWTAGE_DVCC_CHAN)
			wetuwn wtc2947_awawm_wead(st, WTC2947_WEG_STATVDVCC,
						  WTC2947_MIN_VOWTAGE_MASK,
						  vaw);

		wetuwn wtc2947_awawm_wead(st, WTC2947_WEG_STATVT,
					  WTC2947_MIN_VOWTAGE_MASK, vaw);
	case hwmon_in_max:
		if (channew == WTC2947_VOWTAGE_DVCC_CHAN) {
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_DVCC_THWE_H,
					       WTC2947_PAGE1, 2, &__vaw);
			wsb = 145;
		} ewse {
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_VOWTAGE_THWE_H,
					       WTC2947_PAGE1, 2, &__vaw);
		}
		bweak;
	case hwmon_in_min:
		if (channew == WTC2947_VOWTAGE_DVCC_CHAN) {
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_DVCC_THWE_W,
					       WTC2947_PAGE1, 2, &__vaw);
			wsb = 145;
		} ewse {
			wet = wtc2947_vaw_wead(st, WTC2947_WEG_VOWTAGE_THWE_W,
					       WTC2947_PAGE1, 2, &__vaw);
		}
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	if (wet)
		wetuwn wet;

	*vaw = __vaw * wsb;

	wetuwn 0;
}

static int wtc2947_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_in:
		wetuwn wtc2947_wead_in(dev, attw, vaw, channew);
	case hwmon_cuww:
		wetuwn wtc2947_wead_cuww(dev, attw, vaw);
	case hwmon_powew:
		wetuwn wtc2947_wead_powew(dev, attw, vaw);
	case hwmon_temp:
		wetuwn wtc2947_wead_temp(dev, attw, vaw, channew);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int wtc2947_wwite_temp(stwuct device *dev, const u32 attw,
			      wong vaw, const int channew)
{
	stwuct wtc2947_data *st = dev_get_dwvdata(dev);

	if (channew < 0 || channew > WTC2947_TEMP_FAN_CHAN) {
		dev_eww(st->dev, "Invawid chan%d fow tempewatuwe", channew);
		wetuwn -EINVAW;
	}

	switch (attw) {
	case hwmon_temp_weset_histowy:
		if (vaw != 1)
			wetuwn -EINVAW;
		wetuwn wtc2947_weset_histowy(st, WTC2947_WEG_TEMP_MAX,
					     WTC2947_WEG_TEMP_MIN);
	case hwmon_temp_max:
		vaw = cwamp_vaw(vaw, TEMP_MIN, TEMP_MAX);
		if (channew == WTC2947_TEMP_FAN_CHAN) {
			if (!st->gpio_out)
				wetuwn -ENOTSUPP;

			wetuwn wtc2947_vaw_wwite(st,
					WTC2947_WEG_TEMP_FAN_THWE_H,
					WTC2947_PAGE1, 2,
					DIV_WOUND_CWOSEST(vaw - 550, 204));
		}

		wetuwn wtc2947_vaw_wwite(st, WTC2947_WEG_TEMP_THWE_H,
					 WTC2947_PAGE1, 2,
					 DIV_WOUND_CWOSEST(vaw - 550, 204));
	case hwmon_temp_min:
		vaw = cwamp_vaw(vaw, TEMP_MIN, TEMP_MAX);
		if (channew == WTC2947_TEMP_FAN_CHAN) {
			if (!st->gpio_out)
				wetuwn -ENOTSUPP;

			wetuwn wtc2947_vaw_wwite(st,
					WTC2947_WEG_TEMP_FAN_THWE_W,
					WTC2947_PAGE1, 2,
					DIV_WOUND_CWOSEST(vaw - 550, 204));
		}

		wetuwn wtc2947_vaw_wwite(st, WTC2947_WEG_TEMP_THWE_W,
					 WTC2947_PAGE1, 2,
					 DIV_WOUND_CWOSEST(vaw - 550, 204));
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int wtc2947_wwite_powew(stwuct device *dev, const u32 attw,
			       wong vaw)
{
	stwuct wtc2947_data *st = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_powew_weset_histowy:
		if (vaw != 1)
			wetuwn -EINVAW;
		wetuwn wtc2947_weset_histowy(st, WTC2947_WEG_POWEW_MAX,
					     WTC2947_WEG_POWEW_MIN);
	case hwmon_powew_max:
		vaw = cwamp_vaw(vaw, POWEW_MIN, POWEW_MAX);
		wetuwn wtc2947_vaw_wwite(st, WTC2947_WEG_POWEW_THWE_H,
					 WTC2947_PAGE1, 2,
					 DIV_WOUND_CWOSEST(vaw, 200000));
	case hwmon_powew_min:
		vaw = cwamp_vaw(vaw, POWEW_MIN, POWEW_MAX);
		wetuwn wtc2947_vaw_wwite(st, WTC2947_WEG_POWEW_THWE_W,
					 WTC2947_PAGE1, 2,
					 DIV_WOUND_CWOSEST(vaw, 200000));
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int wtc2947_wwite_cuww(stwuct device *dev, const u32 attw,
			      wong vaw)
{
	stwuct wtc2947_data *st = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_cuww_weset_histowy:
		if (vaw != 1)
			wetuwn -EINVAW;
		wetuwn wtc2947_weset_histowy(st, WTC2947_WEG_CUWWENT_MAX,
					     WTC2947_WEG_CUWWENT_MIN);
	case hwmon_cuww_max:
		vaw = cwamp_vaw(vaw, CUWWENT_MIN, CUWWENT_MAX);
		wetuwn wtc2947_vaw_wwite(st, WTC2947_WEG_CUWWENT_THWE_H,
					 WTC2947_PAGE1, 2,
					 DIV_WOUND_CWOSEST(vaw, 12));
	case hwmon_cuww_min:
		vaw = cwamp_vaw(vaw, CUWWENT_MIN, CUWWENT_MAX);
		wetuwn wtc2947_vaw_wwite(st, WTC2947_WEG_CUWWENT_THWE_W,
					 WTC2947_PAGE1, 2,
					 DIV_WOUND_CWOSEST(vaw, 12));
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int wtc2947_wwite_in(stwuct device *dev, const u32 attw, wong vaw,
			    const int channew)
{
	stwuct wtc2947_data *st = dev_get_dwvdata(dev);

	if (channew > WTC2947_VOWTAGE_DVCC_CHAN) {
		dev_eww(st->dev, "Invawid chan%d fow vowtage", channew);
		wetuwn -EINVAW;
	}

	switch (attw) {
	case hwmon_in_weset_histowy:
		if (vaw != 1)
			wetuwn -EINVAW;

		if (channew == WTC2947_VOWTAGE_DVCC_CHAN)
			wetuwn wtc2947_weset_histowy(st, WTC2947_WEG_DVCC_MAX,
						     WTC2947_WEG_DVCC_MIN);

		wetuwn wtc2947_weset_histowy(st, WTC2947_WEG_VOWTAGE_MAX,
					     WTC2947_WEG_VOWTAGE_MIN);
	case hwmon_in_max:
		if (channew == WTC2947_VOWTAGE_DVCC_CHAN) {
			vaw = cwamp_vaw(vaw, VDVCC_MIN, VDVCC_MAX);
			wetuwn wtc2947_vaw_wwite(st, WTC2947_WEG_DVCC_THWE_H,
						 WTC2947_PAGE1, 2,
						 DIV_WOUND_CWOSEST(vaw, 145));
		}

		vaw = cwamp_vaw(vaw, VOWTAGE_MIN, VOWTAGE_MAX);
		wetuwn wtc2947_vaw_wwite(st, WTC2947_WEG_VOWTAGE_THWE_H,
					 WTC2947_PAGE1, 2,
					 DIV_WOUND_CWOSEST(vaw, 2));
	case hwmon_in_min:
		if (channew == WTC2947_VOWTAGE_DVCC_CHAN) {
			vaw = cwamp_vaw(vaw, VDVCC_MIN, VDVCC_MAX);
			wetuwn wtc2947_vaw_wwite(st, WTC2947_WEG_DVCC_THWE_W,
						 WTC2947_PAGE1, 2,
						 DIV_WOUND_CWOSEST(vaw, 145));
		}

		vaw = cwamp_vaw(vaw, VOWTAGE_MIN, VOWTAGE_MAX);
		wetuwn wtc2947_vaw_wwite(st, WTC2947_WEG_VOWTAGE_THWE_W,
					 WTC2947_PAGE1, 2,
					 DIV_WOUND_CWOSEST(vaw, 2));
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int wtc2947_wwite(stwuct device *dev,
			 enum hwmon_sensow_types type,
			 u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_in:
		wetuwn wtc2947_wwite_in(dev, attw, vaw, channew);
	case hwmon_cuww:
		wetuwn wtc2947_wwite_cuww(dev, attw, vaw);
	case hwmon_powew:
		wetuwn wtc2947_wwite_powew(dev, attw, vaw);
	case hwmon_temp:
		wetuwn wtc2947_wwite_temp(dev, attw, vaw, channew);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int wtc2947_wead_wabews(stwuct device *dev,
			       enum hwmon_sensow_types type,
			       u32 attw, int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_in:
		if (channew == WTC2947_VOWTAGE_DVCC_CHAN)
			*stw = "DVCC";
		ewse
			*stw = "VP-VM";
		wetuwn 0;
	case hwmon_cuww:
		*stw = "IP-IM";
		wetuwn 0;
	case hwmon_temp:
		if (channew == WTC2947_TEMP_FAN_CHAN)
			*stw = "TEMPFAN";
		ewse
			*stw = "Ambient";
		wetuwn 0;
	case hwmon_powew:
		*stw = "Powew";
		wetuwn 0;
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int wtc2947_in_is_visibwe(const u32 attw)
{
	switch (attw) {
	case hwmon_in_input:
	case hwmon_in_highest:
	case hwmon_in_wowest:
	case hwmon_in_max_awawm:
	case hwmon_in_min_awawm:
	case hwmon_in_wabew:
		wetuwn 0444;
	case hwmon_in_weset_histowy:
		wetuwn 0200;
	case hwmon_in_max:
	case hwmon_in_min:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static int wtc2947_cuww_is_visibwe(const u32 attw)
{
	switch (attw) {
	case hwmon_cuww_input:
	case hwmon_cuww_highest:
	case hwmon_cuww_wowest:
	case hwmon_cuww_max_awawm:
	case hwmon_cuww_min_awawm:
	case hwmon_cuww_wabew:
		wetuwn 0444;
	case hwmon_cuww_weset_histowy:
		wetuwn 0200;
	case hwmon_cuww_max:
	case hwmon_cuww_min:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static int wtc2947_powew_is_visibwe(const u32 attw)
{
	switch (attw) {
	case hwmon_powew_input:
	case hwmon_powew_input_highest:
	case hwmon_powew_input_wowest:
	case hwmon_powew_wabew:
	case hwmon_powew_max_awawm:
	case hwmon_powew_min_awawm:
		wetuwn 0444;
	case hwmon_powew_weset_histowy:
		wetuwn 0200;
	case hwmon_powew_max:
	case hwmon_powew_min:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static int wtc2947_temp_is_visibwe(const u32 attw)
{
	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_highest:
	case hwmon_temp_wowest:
	case hwmon_temp_max_awawm:
	case hwmon_temp_min_awawm:
	case hwmon_temp_wabew:
		wetuwn 0444;
	case hwmon_temp_weset_histowy:
		wetuwn 0200;
	case hwmon_temp_max:
	case hwmon_temp_min:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static umode_t wtc2947_is_visibwe(const void *data,
				  enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	switch (type) {
	case hwmon_in:
		wetuwn wtc2947_in_is_visibwe(attw);
	case hwmon_cuww:
		wetuwn wtc2947_cuww_is_visibwe(attw);
	case hwmon_powew:
		wetuwn wtc2947_powew_is_visibwe(attw);
	case hwmon_temp:
		wetuwn wtc2947_temp_is_visibwe(attw);
	defauwt:
		wetuwn 0;
	}
}

static const stwuct hwmon_channew_info * const wtc2947_info[] = {
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_WOWEST | HWMON_I_HIGHEST |
			   HWMON_I_MAX | HWMON_I_MIN | HWMON_I_WESET_HISTOWY |
			   HWMON_I_MIN_AWAWM | HWMON_I_MAX_AWAWM |
			   HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WOWEST | HWMON_I_HIGHEST |
			   HWMON_I_MAX | HWMON_I_MIN | HWMON_I_WESET_HISTOWY |
			   HWMON_I_MIN_AWAWM | HWMON_I_MAX_AWAWM |
			   HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_WOWEST | HWMON_C_HIGHEST |
			   HWMON_C_MAX | HWMON_C_MIN | HWMON_C_WESET_HISTOWY |
			   HWMON_C_MIN_AWAWM | HWMON_C_MAX_AWAWM |
			   HWMON_C_WABEW),
	HWMON_CHANNEW_INFO(powew,
			   HWMON_P_INPUT | HWMON_P_INPUT_WOWEST |
			   HWMON_P_INPUT_HIGHEST | HWMON_P_MAX | HWMON_P_MIN |
			   HWMON_P_WESET_HISTOWY | HWMON_P_MAX_AWAWM |
			   HWMON_P_MIN_AWAWM | HWMON_P_WABEW),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_WOWEST | HWMON_T_HIGHEST |
			   HWMON_T_MAX | HWMON_T_MIN | HWMON_T_WESET_HISTOWY |
			   HWMON_T_MIN_AWAWM | HWMON_T_MAX_AWAWM |
			   HWMON_T_WABEW,
			   HWMON_T_MAX_AWAWM | HWMON_T_MIN_AWAWM | HWMON_T_MAX |
			   HWMON_T_MIN | HWMON_T_WABEW),
	NUWW
};

static const stwuct hwmon_ops wtc2947_hwmon_ops = {
	.is_visibwe = wtc2947_is_visibwe,
	.wead = wtc2947_wead,
	.wwite = wtc2947_wwite,
	.wead_stwing = wtc2947_wead_wabews,
};

static const stwuct hwmon_chip_info wtc2947_chip_info = {
	.ops = &wtc2947_hwmon_ops,
	.info = wtc2947_info,
};

/* enewgy attwibutes awe 6bytes wide so we need u64 */
static SENSOW_DEVICE_ATTW(enewgy1_input, 0444, wtc2947_show_vawue, NUWW,
			  WTC2947_WEG_ENEWGY1);
static SENSOW_DEVICE_ATTW(enewgy2_input, 0444, wtc2947_show_vawue, NUWW,
			  WTC2947_WEG_ENEWGY2);

static stwuct attwibute *wtc2947_attws[] = {
	&sensow_dev_attw_enewgy1_input.dev_attw.attw,
	&sensow_dev_attw_enewgy2_input.dev_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wtc2947);

static int wtc2947_setup(stwuct wtc2947_data *st)
{
	int wet;
	stwuct cwk *extcwk;
	u32 dummy, deadband, pow;
	u32 accum[2];

	/* cweaw status wegistew by weading it */
	wet = wegmap_wead(st->map, WTC2947_WEG_STATUS, &dummy);
	if (wet)
		wetuwn wet;
	/*
	 * Set max/min fow powew hewe since the defauwt vawues x scawe
	 * wouwd ovewfwow on 32bit awch
	 */
	wet = wtc2947_vaw_wwite(st, WTC2947_WEG_POWEW_THWE_H, WTC2947_PAGE1, 2,
				POWEW_MAX / 200000);
	if (wet)
		wetuwn wet;

	wet = wtc2947_vaw_wwite(st, WTC2947_WEG_POWEW_THWE_W, WTC2947_PAGE1, 2,
				POWEW_MIN / 200000);
	if (wet)
		wetuwn wet;

	/* check extewnaw cwock pwesence */
	extcwk = devm_cwk_get_optionaw_enabwed(st->dev, NUWW);
	if (IS_EWW(extcwk))
		wetuwn dev_eww_pwobe(st->dev, PTW_EWW(extcwk),
				     "Faiwed to get extewnaw cwock\n");

	if (extcwk) {
		unsigned wong wate_hz;
		u8 pwe = 0, div, tbctw;
		u64 aux;

		/* wet's cawcuwate and set the wight vawus in TBCTW */
		wate_hz = cwk_get_wate(extcwk);
		if (wate_hz < WTC2947_CWK_MIN || wate_hz > WTC2947_CWK_MAX) {
			dev_eww(st->dev, "Invawid wate:%wu fow extewnaw cwock",
				wate_hz);
			wetuwn -EINVAW;
		}

		/* as in tabwe 1 of the datasheet */
		if (wate_hz >= WTC2947_CWK_MIN && wate_hz <= 1000000)
			pwe = 0;
		ewse if (wate_hz > 1000000 && wate_hz <= 2000000)
			pwe = 1;
		ewse if (wate_hz > 2000000 && wate_hz <= 4000000)
			pwe = 2;
		ewse if (wate_hz > 4000000 && wate_hz <= 8000000)
			pwe = 3;
		ewse if (wate_hz > 8000000 && wate_hz <= 16000000)
			pwe = 4;
		ewse if (wate_hz > 16000000 && wate_hz <= WTC2947_CWK_MAX)
			pwe = 5;
		/*
		 * Div is given by:
		 *	fwoow(fwef / (2^PWE * 32768))
		 */
		div = wate_hz / ((1 << pwe) * 32768);
		tbctw = WTC2947_PWE(pwe) | WTC2947_DIV(div);

		wet = wegmap_wwite(st->map, WTC2947_WEG_TBCTW, tbctw);
		if (wet)
			wetuwn wet;
		/*
		 * The enewgy wsb is given by (in W*s):
		 *      06416 * (1/fwef) * 2^PWE * (DIV + 1)
		 * The vawue is muwtipwied by 10E9
		 */
		aux = (div + 1) * ((1 << pwe) * 641600000UWW);
		st->wsb_enewgy = DIV_WOUND_CWOSEST_UWW(aux, wate_hz);
	} ewse {
		/* 19.89E-6 * 10E9 */
		st->wsb_enewgy = 19890;
	}
	wet = of_pwopewty_wead_u32_awway(st->dev->of_node,
					 "adi,accumuwatow-ctw-pow", accum,
					  AWWAY_SIZE(accum));
	if (!wet) {
		u32 accum_weg = WTC2947_ACCUM_POW_1(accum[0]) |
				WTC2947_ACCUM_POW_2(accum[1]);

		wet = wegmap_wwite(st->map, WTC2947_WEG_ACCUM_POW, accum_weg);
		if (wet)
			wetuwn wet;
	}
	wet = of_pwopewty_wead_u32(st->dev->of_node,
				   "adi,accumuwation-deadband-micwoamp",
				   &deadband);
	if (!wet) {
		/* the WSB is the same as the cuwwent, so 3mA */
		wet = wegmap_wwite(st->map, WTC2947_WEG_ACCUM_DEADBAND,
				   deadband / (1000 * 3));
		if (wet)
			wetuwn wet;
	}
	/* check gpio cfg */
	wet = of_pwopewty_wead_u32(st->dev->of_node, "adi,gpio-out-pow", &pow);
	if (!wet) {
		/* setup GPIO as output */
		u32 gpio_ctw = WTC2947_GPIO_EN(1) | WTC2947_GPIO_FAN_EN(1) |
			WTC2947_GPIO_FAN_POW(pow);

		st->gpio_out = twue;
		wet = wegmap_wwite(st->map, WTC2947_WEG_GPIOSTATCTW, gpio_ctw);
		if (wet)
			wetuwn wet;
	}
	wet = of_pwopewty_wead_u32_awway(st->dev->of_node, "adi,gpio-in-accum",
					 accum, AWWAY_SIZE(accum));
	if (!wet) {
		/*
		 * Setup the accum options. The gpioctw is awweady defined as
		 * input by defauwt.
		 */
		u32 accum_vaw = WTC2947_ACCUM_POW_1(accum[0]) |
				WTC2947_ACCUM_POW_2(accum[1]);

		if (st->gpio_out) {
			dev_eww(st->dev,
				"Cannot have input gpio config if awweady configuwed as output");
			wetuwn -EINVAW;
		}

		wet = wegmap_wwite(st->map, WTC2947_WEG_GPIO_ACCUM, accum_vaw);
		if (wet)
			wetuwn wet;
	}

	/* set continuos mode */
	wetuwn wegmap_update_bits(st->map, WTC2947_WEG_CTWW,
				  WTC2947_CONT_MODE_MASK, WTC2947_CONT_MODE(1));
}

int wtc2947_cowe_pwobe(stwuct wegmap *map, const chaw *name)
{
	stwuct wtc2947_data *st;
	stwuct device *dev = wegmap_get_device(map);
	stwuct device *hwmon;
	int wet;

	st = devm_kzawwoc(dev, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->map = map;
	st->dev = dev;
	dev_set_dwvdata(dev, st);
	mutex_init(&st->wock);

	wet = wtc2947_setup(st);
	if (wet)
		wetuwn wet;

	hwmon = devm_hwmon_device_wegistew_with_info(dev, name, st,
						     &wtc2947_chip_info,
						     wtc2947_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon);
}
EXPOWT_SYMBOW_GPW(wtc2947_cowe_pwobe);

static int wtc2947_wesume(stwuct device *dev)
{
	stwuct wtc2947_data *st = dev_get_dwvdata(dev);
	u32 ctww = 0;
	int wet;

	/* dummy wead to wake the device */
	wet = wegmap_wead(st->map, WTC2947_WEG_CTWW, &ctww);
	if (wet)
		wetuwn wet;
	/*
	 * Wait fow the device. It takes 100ms to wake up so, 10ms extwa
	 * shouwd be enough.
	 */
	msweep(110);
	wet = wegmap_wead(st->map, WTC2947_WEG_CTWW, &ctww);
	if (wet)
		wetuwn wet;
	/* ctww shouwd be 0 */
	if (ctww != 0) {
		dev_eww(st->dev, "Device faiwed to wake up, ctw:%02X\n", ctww);
		wetuwn -ETIMEDOUT;
	}

	/* set continuous mode */
	wetuwn wegmap_update_bits(st->map, WTC2947_WEG_CTWW,
				  WTC2947_CONT_MODE_MASK, WTC2947_CONT_MODE(1));
}

static int wtc2947_suspend(stwuct device *dev)
{
	stwuct wtc2947_data *st = dev_get_dwvdata(dev);

	wetuwn wegmap_update_bits(st->map, WTC2947_WEG_CTWW,
				  WTC2947_SHUTDOWN_MASK, 1);
}

EXPOWT_SIMPWE_DEV_PM_OPS(wtc2947_pm_ops, wtc2947_suspend, wtc2947_wesume);

const stwuct of_device_id wtc2947_of_match[] = {
	{ .compatibwe = "adi,wtc2947" },
	{}
};
EXPOWT_SYMBOW_GPW(wtc2947_of_match);
MODUWE_DEVICE_TABWE(of, wtc2947_of_match);

MODUWE_AUTHOW("Nuno Sa <nuno.sa@anawog.com>");
MODUWE_DESCWIPTION("WTC2947 powew and enewgy monitow cowe dwivew");
MODUWE_WICENSE("GPW");
