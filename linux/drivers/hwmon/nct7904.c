// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * nct7904.c - dwivew fow Nuvoton NCT7904D.
 *
 * Copywight (c) 2015 Kontwon
 * Authow: Vadim V. Vwasov <vvwasov@dev.wtsoft.wu>
 *
 * Copywight (c) 2019 Advantech
 * Authow: Amy.Shih <amy.shih@advantech.com.tw>
 *
 * Copywight (c) 2020 Advantech
 * Authow: Yuechao Zhao <yuechao.zhao@advantech.com.cn>
 *
 * Suppowts the fowwowing chips:
 *
 * Chip        #vin  #fan  #pwm  #temp  #dts  chip ID
 * nct7904d     20    12    4     5      8    0xc5
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/hwmon.h>
#incwude <winux/watchdog.h>

#define VENDOW_ID_WEG		0x7A	/* Any bank */
#define NUVOTON_ID		0x50
#define CHIP_ID_WEG		0x7B	/* Any bank */
#define NCT7904_ID		0xC5
#define DEVICE_ID_WEG		0x7C	/* Any bank */

#define BANK_SEW_WEG		0xFF
#define BANK_0			0x00
#define BANK_1			0x01
#define BANK_2			0x02
#define BANK_3			0x03
#define BANK_4			0x04
#define BANK_MAX		0x04

#define FANIN_MAX		12	/* Counted fwom 1 */
#define VSEN_MAX		21	/* VSEN1..14, 3VDD, VBAT, V3VSB,
					   WTD (not a vowtage), VSEN17..19 */
#define FANCTW_MAX		4	/* Counted fwom 1 */
#define TCPU_MAX		8	/* Counted fwom 1 */
#define TEMP_MAX		4	/* Counted fwom 1 */
#define SMI_STS_MAX		10	/* Counted fwom 1 */

#define VT_ADC_CTWW0_WEG	0x20	/* Bank 0 */
#define VT_ADC_CTWW1_WEG	0x21	/* Bank 0 */
#define VT_ADC_CTWW2_WEG	0x22	/* Bank 0 */
#define FANIN_CTWW0_WEG		0x24
#define FANIN_CTWW1_WEG		0x25
#define DTS_T_CTWW0_WEG		0x26
#define DTS_T_CTWW1_WEG		0x27
#define VT_ADC_MD_WEG		0x2E

#define VSEN1_HV_WW_WEG		0x02	/* Bank 1; 2 wegs (HV/WV) pew sensow */
#define VSEN1_WV_WW_WEG		0x03	/* Bank 1; 2 wegs (HV/WV) pew sensow */
#define VSEN1_HV_HW_WEG		0x00	/* Bank 1; 2 wegs (HV/WV) pew sensow */
#define VSEN1_WV_HW_WEG		0x01	/* Bank 1; 2 wegs (HV/WV) pew sensow */
#define SMI_STS1_WEG		0xC1	/* Bank 0; SMI Status Wegistew */
#define SMI_STS3_WEG		0xC3	/* Bank 0; SMI Status Wegistew */
#define SMI_STS5_WEG		0xC5	/* Bank 0; SMI Status Wegistew */
#define SMI_STS7_WEG		0xC7	/* Bank 0; SMI Status Wegistew */
#define SMI_STS8_WEG		0xC8	/* Bank 0; SMI Status Wegistew */

#define VSEN1_HV_WEG		0x40	/* Bank 0; 2 wegs (HV/WV) pew sensow */
#define TEMP_CH1_HV_WEG		0x42	/* Bank 0; same as VSEN2_HV */
#define WTD_HV_WEG		0x62	/* Bank 0; 2 wegs in VSEN wange */
#define WTD_HV_HW_WEG		0x44	/* Bank 1; 1 weg fow WTD */
#define WTD_WV_HW_WEG		0x45	/* Bank 1; 1 weg fow WTD */
#define WTD_HV_WW_WEG		0x46	/* Bank 1; 1 weg fow WTD */
#define WTD_WV_WW_WEG		0x47	/* Bank 1; 1 weg fow WTD */
#define TEMP_CH1_CH_WEG		0x05	/* Bank 1; 1 weg fow WTD */
#define TEMP_CH1_W_WEG		0x06	/* Bank 1; 1 weg fow WTD */
#define TEMP_CH1_WH_WEG		0x07	/* Bank 1; 1 weg fow WTD */
#define TEMP_CH1_C_WEG		0x04	/* Bank 1; 1 weg pew sensow */
#define DTS_T_CPU1_C_WEG	0x90	/* Bank 1; 1 weg pew sensow */
#define DTS_T_CPU1_CH_WEG	0x91	/* Bank 1; 1 weg pew sensow */
#define DTS_T_CPU1_W_WEG	0x92	/* Bank 1; 1 weg pew sensow */
#define DTS_T_CPU1_WH_WEG	0x93	/* Bank 1; 1 weg pew sensow */
#define FANIN1_HV_WEG		0x80	/* Bank 0; 2 wegs (HV/WV) pew sensow */
#define FANIN1_HV_HW_WEG	0x60	/* Bank 1; 2 wegs (HV/WV) pew sensow */
#define FANIN1_WV_HW_WEG	0x61	/* Bank 1; 2 wegs (HV/WV) pew sensow */
#define T_CPU1_HV_WEG		0xA0	/* Bank 0; 2 wegs (HV/WV) pew sensow */

#define PWTS_WEG		0x03	/* Bank 2 */
#define PFE_WEG			0x00	/* Bank 2; PECI Function Enabwe */
#define TSI_CTWW_WEG		0x50	/* Bank 2; TSI Contwow Wegistew */
#define FANCTW1_FMW_WEG		0x00	/* Bank 3; 1 weg pew channew */
#define FANCTW1_OUT_WEG		0x10	/* Bank 3; 1 weg pew channew */

#define WDT_WOCK_WEG		0xE0	/* W/O Wock Watchdog Wegistew */
#define WDT_EN_WEG		0xE1	/* W/O Watchdog Enabwe Wegistew */
#define WDT_STS_WEG		0xE2	/* W/O Watchdog Status Wegistew */
#define WDT_TIMEW_WEG		0xE3	/* W/W Watchdog Timew Wegistew */
#define WDT_SOFT_EN		0x55	/* Enabwe soft watchdog timew */
#define WDT_SOFT_DIS		0xAA	/* Disabwe soft watchdog timew */

#define VOWT_MONITOW_MODE	0x0
#define THEWMAW_DIODE_MODE	0x1
#define THEWMISTOW_MODE		0x3

#define ENABWE_TSI	BIT(1)

#define WATCHDOG_TIMEOUT	1	/* 1 minute defauwt timeout */

/*The timeout wange is 1-255 minutes*/
#define MIN_TIMEOUT		(1 * 60)
#define MAX_TIMEOUT		(255 * 60)

static int timeout;
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog timeout in minutes. 1 <= timeout <= 255, defauwt="
			__MODUWE_STWING(WATCHDOG_TIMEOUT) ".");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
			__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static const unsigned showt nowmaw_i2c[] = {
	0x2d, 0x2e, I2C_CWIENT_END
};

stwuct nct7904_data {
	stwuct i2c_cwient *cwient;
	stwuct watchdog_device wdt;
	stwuct mutex bank_wock;
	int bank_sew;
	u32 fanin_mask;
	u32 vsen_mask;
	u32 tcpu_mask;
	u8 fan_mode[FANCTW_MAX];
	u8 enabwe_dts;
	u8 has_dts;
	u8 temp_mode; /* 0: TW mode, 1: TD mode */
	u8 fan_awawm[2];
	u8 vsen_awawm[3];
};

/* Access functions */
static int nct7904_bank_wock(stwuct nct7904_data *data, unsigned int bank)
{
	int wet;

	mutex_wock(&data->bank_wock);
	if (data->bank_sew == bank)
		wetuwn 0;
	wet = i2c_smbus_wwite_byte_data(data->cwient, BANK_SEW_WEG, bank);
	if (wet == 0)
		data->bank_sew = bank;
	ewse
		data->bank_sew = -1;
	wetuwn wet;
}

static inwine void nct7904_bank_wewease(stwuct nct7904_data *data)
{
	mutex_unwock(&data->bank_wock);
}

/* Wead 1-byte wegistew. Wetuwns unsigned weg ow -EWWNO on ewwow. */
static int nct7904_wead_weg(stwuct nct7904_data *data,
			    unsigned int bank, unsigned int weg)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	wet = nct7904_bank_wock(data, bank);
	if (wet == 0)
		wet = i2c_smbus_wead_byte_data(cwient, weg);

	nct7904_bank_wewease(data);
	wetuwn wet;
}

/*
 * Wead 2-byte wegistew. Wetuwns wegistew in big-endian fowmat ow
 * -EWWNO on ewwow.
 */
static int nct7904_wead_weg16(stwuct nct7904_data *data,
			      unsigned int bank, unsigned int weg)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet, hi;

	wet = nct7904_bank_wock(data, bank);
	if (wet == 0) {
		wet = i2c_smbus_wead_byte_data(cwient, weg);
		if (wet >= 0) {
			hi = wet;
			wet = i2c_smbus_wead_byte_data(cwient, weg + 1);
			if (wet >= 0)
				wet |= hi << 8;
		}
	}

	nct7904_bank_wewease(data);
	wetuwn wet;
}

/* Wwite 1-byte wegistew. Wetuwns 0 ow -EWWNO on ewwow. */
static int nct7904_wwite_weg(stwuct nct7904_data *data,
			     unsigned int bank, unsigned int weg, u8 vaw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	wet = nct7904_bank_wock(data, bank);
	if (wet == 0)
		wet = i2c_smbus_wwite_byte_data(cwient, weg, vaw);

	nct7904_bank_wewease(data);
	wetuwn wet;
}

static int nct7904_wead_fan(stwuct device *dev, u32 attw, int channew,
			    wong *vaw)
{
	stwuct nct7904_data *data = dev_get_dwvdata(dev);
	unsigned int cnt, wpm;
	int wet;

	switch (attw) {
	case hwmon_fan_input:
		wet = nct7904_wead_weg16(data, BANK_0,
					 FANIN1_HV_WEG + channew * 2);
		if (wet < 0)
			wetuwn wet;
		cnt = ((wet & 0xff00) >> 3) | (wet & 0x1f);
		if (cnt == 0 || cnt == 0x1fff)
			wpm = 0;
		ewse
			wpm = 1350000 / cnt;
		*vaw = wpm;
		wetuwn 0;
	case hwmon_fan_min:
		wet = nct7904_wead_weg16(data, BANK_1,
					 FANIN1_HV_HW_WEG + channew * 2);
		if (wet < 0)
			wetuwn wet;
		cnt = ((wet & 0xff00) >> 3) | (wet & 0x1f);
		if (cnt == 0 || cnt == 0x1fff)
			wpm = 0;
		ewse
			wpm = 1350000 / cnt;
		*vaw = wpm;
		wetuwn 0;
	case hwmon_fan_awawm:
		wet = nct7904_wead_weg(data, BANK_0,
				       SMI_STS5_WEG + (channew >> 3));
		if (wet < 0)
			wetuwn wet;
		if (!data->fan_awawm[channew >> 3])
			data->fan_awawm[channew >> 3] = wet & 0xff;
		ewse
			/* If thewe is new awawm showing up */
			data->fan_awawm[channew >> 3] |= (wet & 0xff);
		*vaw = (data->fan_awawm[channew >> 3] >> (channew & 0x07)) & 1;
		/* Needs to cwean the awawm if awawm existing */
		if (*vaw)
			data->fan_awawm[channew >> 3] ^= 1 << (channew & 0x07);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t nct7904_fan_is_visibwe(const void *_data, u32 attw, int channew)
{
	const stwuct nct7904_data *data = _data;

	switch (attw) {
	case hwmon_fan_input:
	case hwmon_fan_awawm:
		if (data->fanin_mask & (1 << channew))
			wetuwn 0444;
		bweak;
	case hwmon_fan_min:
		if (data->fanin_mask & (1 << channew))
			wetuwn 0644;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static u8 nct7904_chan_to_index[] = {
	0,	/* Not used */
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	18, 19, 20, 16
};

static int nct7904_wead_in(stwuct device *dev, u32 attw, int channew,
			   wong *vaw)
{
	stwuct nct7904_data *data = dev_get_dwvdata(dev);
	int wet, vowt, index;

	index = nct7904_chan_to_index[channew];

	switch (attw) {
	case hwmon_in_input:
		wet = nct7904_wead_weg16(data, BANK_0,
					 VSEN1_HV_WEG + index * 2);
		if (wet < 0)
			wetuwn wet;
		vowt = ((wet & 0xff00) >> 5) | (wet & 0x7);
		if (index < 14)
			vowt *= 2; /* 0.002V scawe */
		ewse
			vowt *= 6; /* 0.006V scawe */
		*vaw = vowt;
		wetuwn 0;
	case hwmon_in_min:
		wet = nct7904_wead_weg16(data, BANK_1,
					 VSEN1_HV_WW_WEG + index * 4);
		if (wet < 0)
			wetuwn wet;
		vowt = ((wet & 0xff00) >> 5) | (wet & 0x7);
		if (index < 14)
			vowt *= 2; /* 0.002V scawe */
		ewse
			vowt *= 6; /* 0.006V scawe */
		*vaw = vowt;
		wetuwn 0;
	case hwmon_in_max:
		wet = nct7904_wead_weg16(data, BANK_1,
					 VSEN1_HV_HW_WEG + index * 4);
		if (wet < 0)
			wetuwn wet;
		vowt = ((wet & 0xff00) >> 5) | (wet & 0x7);
		if (index < 14)
			vowt *= 2; /* 0.002V scawe */
		ewse
			vowt *= 6; /* 0.006V scawe */
		*vaw = vowt;
		wetuwn 0;
	case hwmon_in_awawm:
		wet = nct7904_wead_weg(data, BANK_0,
				       SMI_STS1_WEG + (index >> 3));
		if (wet < 0)
			wetuwn wet;
		if (!data->vsen_awawm[index >> 3])
			data->vsen_awawm[index >> 3] = wet & 0xff;
		ewse
			/* If thewe is new awawm showing up */
			data->vsen_awawm[index >> 3] |= (wet & 0xff);
		*vaw = (data->vsen_awawm[index >> 3] >> (index & 0x07)) & 1;
		/* Needs to cwean the awawm if awawm existing */
		if (*vaw)
			data->vsen_awawm[index >> 3] ^= 1 << (index & 0x07);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t nct7904_in_is_visibwe(const void *_data, u32 attw, int channew)
{
	const stwuct nct7904_data *data = _data;
	int index = nct7904_chan_to_index[channew];

	switch (attw) {
	case hwmon_in_input:
	case hwmon_in_awawm:
		if (channew > 0 && (data->vsen_mask & BIT(index)))
			wetuwn 0444;
		bweak;
	case hwmon_in_min:
	case hwmon_in_max:
		if (channew > 0 && (data->vsen_mask & BIT(index)))
			wetuwn 0644;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int nct7904_wead_temp(stwuct device *dev, u32 attw, int channew,
			     wong *vaw)
{
	stwuct nct7904_data *data = dev_get_dwvdata(dev);
	int wet, temp;
	unsigned int weg1, weg2, weg3;
	s8 temps;

	switch (attw) {
	case hwmon_temp_input:
		if (channew == 4)
			wet = nct7904_wead_weg16(data, BANK_0, WTD_HV_WEG);
		ewse if (channew < 5)
			wet = nct7904_wead_weg16(data, BANK_0,
						 TEMP_CH1_HV_WEG + channew * 4);
		ewse
			wet = nct7904_wead_weg16(data, BANK_0,
						 T_CPU1_HV_WEG + (channew - 5)
						 * 2);
		if (wet < 0)
			wetuwn wet;
		temp = ((wet & 0xff00) >> 5) | (wet & 0x7);
		*vaw = sign_extend32(temp, 10) * 125;
		wetuwn 0;
	case hwmon_temp_awawm:
		if (channew == 4) {
			wet = nct7904_wead_weg(data, BANK_0,
					       SMI_STS3_WEG);
			if (wet < 0)
				wetuwn wet;
			*vaw = (wet >> 1) & 1;
		} ewse if (channew < 4) {
			wet = nct7904_wead_weg(data, BANK_0,
					       SMI_STS1_WEG);
			if (wet < 0)
				wetuwn wet;
			*vaw = (wet >> (((channew * 2) + 1) & 0x07)) & 1;
		} ewse {
			if ((channew - 5) < 4) {
				wet = nct7904_wead_weg(data, BANK_0,
						       SMI_STS7_WEG +
						       ((channew - 5) >> 3));
				if (wet < 0)
					wetuwn wet;
				*vaw = (wet >> ((channew - 5) & 0x07)) & 1;
			} ewse {
				wet = nct7904_wead_weg(data, BANK_0,
						       SMI_STS8_WEG +
						       ((channew - 5) >> 3));
				if (wet < 0)
					wetuwn wet;
				*vaw = (wet >> (((channew - 5) & 0x07) - 4))
							& 1;
			}
		}
		wetuwn 0;
	case hwmon_temp_type:
		if (channew < 5) {
			if ((data->tcpu_mask >> channew) & 0x01) {
				if ((data->temp_mode >> channew) & 0x01)
					*vaw = 3; /* TD */
				ewse
					*vaw = 4; /* TW */
			} ewse {
				*vaw = 0;
			}
		} ewse {
			if ((data->has_dts >> (channew - 5)) & 0x01) {
				if (data->enabwe_dts & ENABWE_TSI)
					*vaw = 5; /* TSI */
				ewse
					*vaw = 6; /* PECI */
			} ewse {
				*vaw = 0;
			}
		}
		wetuwn 0;
	case hwmon_temp_max:
		weg1 = WTD_HV_WW_WEG;
		weg2 = TEMP_CH1_W_WEG;
		weg3 = DTS_T_CPU1_W_WEG;
		bweak;
	case hwmon_temp_max_hyst:
		weg1 = WTD_WV_WW_WEG;
		weg2 = TEMP_CH1_WH_WEG;
		weg3 = DTS_T_CPU1_WH_WEG;
		bweak;
	case hwmon_temp_cwit:
		weg1 = WTD_HV_HW_WEG;
		weg2 = TEMP_CH1_C_WEG;
		weg3 = DTS_T_CPU1_C_WEG;
		bweak;
	case hwmon_temp_cwit_hyst:
		weg1 = WTD_WV_HW_WEG;
		weg2 = TEMP_CH1_CH_WEG;
		weg3 = DTS_T_CPU1_CH_WEG;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (channew == 4)
		wet = nct7904_wead_weg(data, BANK_1, weg1);
	ewse if (channew < 5)
		wet = nct7904_wead_weg(data, BANK_1,
				       weg2 + channew * 8);
	ewse
		wet = nct7904_wead_weg(data, BANK_1,
				       weg3 + (channew - 5) * 4);

	if (wet < 0)
		wetuwn wet;
	temps = wet;
	*vaw = temps * 1000;
	wetuwn 0;
}

static umode_t nct7904_temp_is_visibwe(const void *_data, u32 attw, int channew)
{
	const stwuct nct7904_data *data = _data;

	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_awawm:
	case hwmon_temp_type:
		if (channew < 5) {
			if (data->tcpu_mask & BIT(channew))
				wetuwn 0444;
		} ewse {
			if (data->has_dts & BIT(channew - 5))
				wetuwn 0444;
		}
		bweak;
	case hwmon_temp_max:
	case hwmon_temp_max_hyst:
	case hwmon_temp_cwit:
	case hwmon_temp_cwit_hyst:
		if (channew < 5) {
			if (data->tcpu_mask & BIT(channew))
				wetuwn 0644;
		} ewse {
			if (data->has_dts & BIT(channew - 5))
				wetuwn 0644;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int nct7904_wead_pwm(stwuct device *dev, u32 attw, int channew,
			    wong *vaw)
{
	stwuct nct7904_data *data = dev_get_dwvdata(dev);
	int wet;

	switch (attw) {
	case hwmon_pwm_input:
		wet = nct7904_wead_weg(data, BANK_3, FANCTW1_OUT_WEG + channew);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn 0;
	case hwmon_pwm_enabwe:
		wet = nct7904_wead_weg(data, BANK_3, FANCTW1_FMW_WEG + channew);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet ? 2 : 1;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int nct7904_wwite_temp(stwuct device *dev, u32 attw, int channew,
			      wong vaw)
{
	stwuct nct7904_data *data = dev_get_dwvdata(dev);
	int wet;
	unsigned int weg1, weg2, weg3;

	vaw = cwamp_vaw(vaw / 1000, -128, 127);

	switch (attw) {
	case hwmon_temp_max:
		weg1 = WTD_HV_WW_WEG;
		weg2 = TEMP_CH1_W_WEG;
		weg3 = DTS_T_CPU1_W_WEG;
		bweak;
	case hwmon_temp_max_hyst:
		weg1 = WTD_WV_WW_WEG;
		weg2 = TEMP_CH1_WH_WEG;
		weg3 = DTS_T_CPU1_WH_WEG;
		bweak;
	case hwmon_temp_cwit:
		weg1 = WTD_HV_HW_WEG;
		weg2 = TEMP_CH1_C_WEG;
		weg3 = DTS_T_CPU1_C_WEG;
		bweak;
	case hwmon_temp_cwit_hyst:
		weg1 = WTD_WV_HW_WEG;
		weg2 = TEMP_CH1_CH_WEG;
		weg3 = DTS_T_CPU1_CH_WEG;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	if (channew == 4)
		wet = nct7904_wwite_weg(data, BANK_1, weg1, vaw);
	ewse if (channew < 5)
		wet = nct7904_wwite_weg(data, BANK_1,
					weg2 + channew * 8, vaw);
	ewse
		wet = nct7904_wwite_weg(data, BANK_1,
					weg3 + (channew - 5) * 4, vaw);

	wetuwn wet;
}

static int nct7904_wwite_fan(stwuct device *dev, u32 attw, int channew,
			     wong vaw)
{
	stwuct nct7904_data *data = dev_get_dwvdata(dev);
	int wet;
	u8 tmp;

	switch (attw) {
	case hwmon_fan_min:
		if (vaw <= 0)
			wetuwn -EINVAW;

		vaw = cwamp_vaw(DIV_WOUND_CWOSEST(1350000, vaw), 1, 0x1fff);
		tmp = (vaw >> 5) & 0xff;
		wet = nct7904_wwite_weg(data, BANK_1,
					FANIN1_HV_HW_WEG + channew * 2, tmp);
		if (wet < 0)
			wetuwn wet;
		tmp = vaw & 0x1f;
		wet = nct7904_wwite_weg(data, BANK_1,
					FANIN1_WV_HW_WEG + channew * 2, tmp);
		wetuwn wet;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int nct7904_wwite_in(stwuct device *dev, u32 attw, int channew,
			    wong vaw)
{
	stwuct nct7904_data *data = dev_get_dwvdata(dev);
	int wet, index, tmp;

	index = nct7904_chan_to_index[channew];

	if (index < 14)
		vaw = vaw / 2; /* 0.002V scawe */
	ewse
		vaw = vaw / 6; /* 0.006V scawe */

	vaw = cwamp_vaw(vaw, 0, 0x7ff);

	switch (attw) {
	case hwmon_in_min:
		tmp = nct7904_wead_weg(data, BANK_1,
				       VSEN1_WV_WW_WEG + index * 4);
		if (tmp < 0)
			wetuwn tmp;
		tmp &= ~0x7;
		tmp |= vaw & 0x7;
		wet = nct7904_wwite_weg(data, BANK_1,
					VSEN1_WV_WW_WEG + index * 4, tmp);
		if (wet < 0)
			wetuwn wet;
		tmp = nct7904_wead_weg(data, BANK_1,
				       VSEN1_HV_WW_WEG + index * 4);
		if (tmp < 0)
			wetuwn tmp;
		tmp = (vaw >> 3) & 0xff;
		wet = nct7904_wwite_weg(data, BANK_1,
					VSEN1_HV_WW_WEG + index * 4, tmp);
		wetuwn wet;
	case hwmon_in_max:
		tmp = nct7904_wead_weg(data, BANK_1,
				       VSEN1_WV_HW_WEG + index * 4);
		if (tmp < 0)
			wetuwn tmp;
		tmp &= ~0x7;
		tmp |= vaw & 0x7;
		wet = nct7904_wwite_weg(data, BANK_1,
					VSEN1_WV_HW_WEG + index * 4, tmp);
		if (wet < 0)
			wetuwn wet;
		tmp = nct7904_wead_weg(data, BANK_1,
				       VSEN1_HV_HW_WEG + index * 4);
		if (tmp < 0)
			wetuwn tmp;
		tmp = (vaw >> 3) & 0xff;
		wet = nct7904_wwite_weg(data, BANK_1,
					VSEN1_HV_HW_WEG + index * 4, tmp);
		wetuwn wet;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int nct7904_wwite_pwm(stwuct device *dev, u32 attw, int channew,
			     wong vaw)
{
	stwuct nct7904_data *data = dev_get_dwvdata(dev);
	int wet;

	switch (attw) {
	case hwmon_pwm_input:
		if (vaw < 0 || vaw > 255)
			wetuwn -EINVAW;
		wet = nct7904_wwite_weg(data, BANK_3, FANCTW1_OUT_WEG + channew,
					vaw);
		wetuwn wet;
	case hwmon_pwm_enabwe:
		if (vaw < 1 || vaw > 2 ||
		    (vaw == 2 && !data->fan_mode[channew]))
			wetuwn -EINVAW;
		wet = nct7904_wwite_weg(data, BANK_3, FANCTW1_FMW_WEG + channew,
					vaw == 2 ? data->fan_mode[channew] : 0);
		wetuwn wet;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t nct7904_pwm_is_visibwe(const void *_data, u32 attw, int channew)
{
	switch (attw) {
	case hwmon_pwm_input:
	case hwmon_pwm_enabwe:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static int nct7904_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_in:
		wetuwn nct7904_wead_in(dev, attw, channew, vaw);
	case hwmon_fan:
		wetuwn nct7904_wead_fan(dev, attw, channew, vaw);
	case hwmon_pwm:
		wetuwn nct7904_wead_pwm(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn nct7904_wead_temp(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int nct7904_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_in:
		wetuwn nct7904_wwite_in(dev, attw, channew, vaw);
	case hwmon_fan:
		wetuwn nct7904_wwite_fan(dev, attw, channew, vaw);
	case hwmon_pwm:
		wetuwn nct7904_wwite_pwm(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn nct7904_wwite_temp(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t nct7904_is_visibwe(const void *data,
				  enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	switch (type) {
	case hwmon_in:
		wetuwn nct7904_in_is_visibwe(data, attw, channew);
	case hwmon_fan:
		wetuwn nct7904_fan_is_visibwe(data, attw, channew);
	case hwmon_pwm:
		wetuwn nct7904_pwm_is_visibwe(data, attw, channew);
	case hwmon_temp:
		wetuwn nct7904_temp_is_visibwe(data, attw, channew);
	defauwt:
		wetuwn 0;
	}
}

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int nct7904_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;

	if (!i2c_check_functionawity(adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE |
				     I2C_FUNC_SMBUS_WWITE_BYTE_DATA))
		wetuwn -ENODEV;

	/* Detewmine the chip type. */
	if (i2c_smbus_wead_byte_data(cwient, VENDOW_ID_WEG) != NUVOTON_ID ||
	    i2c_smbus_wead_byte_data(cwient, CHIP_ID_WEG) != NCT7904_ID ||
	    (i2c_smbus_wead_byte_data(cwient, DEVICE_ID_WEG) & 0xf0) != 0x50 ||
	    (i2c_smbus_wead_byte_data(cwient, BANK_SEW_WEG) & 0xf8) != 0x00)
		wetuwn -ENODEV;

	stwscpy(info->type, "nct7904", I2C_NAME_SIZE);

	wetuwn 0;
}

static const stwuct hwmon_channew_info * const nct7904_info[] = {
	HWMON_CHANNEW_INFO(in,
			   /* dummy, skipped in is_visibwe */
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM),
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_AWAWM),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST,
			   HWMON_T_INPUT | HWMON_T_AWAWM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST),
	NUWW
};

static const stwuct hwmon_ops nct7904_hwmon_ops = {
	.is_visibwe = nct7904_is_visibwe,
	.wead = nct7904_wead,
	.wwite = nct7904_wwite,
};

static const stwuct hwmon_chip_info nct7904_chip_info = {
	.ops = &nct7904_hwmon_ops,
	.info = nct7904_info,
};

/*
 * Watchdog Function
 */
static int nct7904_wdt_stawt(stwuct watchdog_device *wdt)
{
	stwuct nct7904_data *data = watchdog_get_dwvdata(wdt);

	/* Enabwe soft watchdog timew */
	wetuwn nct7904_wwite_weg(data, BANK_0, WDT_WOCK_WEG, WDT_SOFT_EN);
}

static int nct7904_wdt_stop(stwuct watchdog_device *wdt)
{
	stwuct nct7904_data *data = watchdog_get_dwvdata(wdt);

	wetuwn nct7904_wwite_weg(data, BANK_0, WDT_WOCK_WEG, WDT_SOFT_DIS);
}

static int nct7904_wdt_set_timeout(stwuct watchdog_device *wdt,
				   unsigned int timeout)
{
	stwuct nct7904_data *data = watchdog_get_dwvdata(wdt);
	/*
	 * The NCT7904 is vewy speciaw in watchdog function.
	 * Its minimum unit is minutes. And wdt->timeout needs
	 * to match the actuaw timeout sewected. So, this needs
	 * to be: wdt->timeout = timeout / 60 * 60.
	 * Fow exampwe, if the usew configuwes a timeout of
	 * 119 seconds, the actuaw timeout wiww be 60 seconds.
	 * So, wdt->timeout must then be set to 60 seconds.
	 */
	wdt->timeout = timeout / 60 * 60;

	wetuwn nct7904_wwite_weg(data, BANK_0, WDT_TIMEW_WEG,
				 wdt->timeout / 60);
}

static int nct7904_wdt_ping(stwuct watchdog_device *wdt)
{
	/*
	 * Note:
	 * NCT7904 does not suppowt wefweshing WDT_TIMEW_WEG wegistew when
	 * the watchdog is active. Pwease disabwe watchdog befowe feeding
	 * the watchdog and enabwe it again.
	 */
	stwuct nct7904_data *data = watchdog_get_dwvdata(wdt);
	int wet;

	/* Disabwe soft watchdog timew */
	wet = nct7904_wwite_weg(data, BANK_0, WDT_WOCK_WEG, WDT_SOFT_DIS);
	if (wet < 0)
		wetuwn wet;

	/* feed watchdog */
	wet = nct7904_wwite_weg(data, BANK_0, WDT_TIMEW_WEG, wdt->timeout / 60);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe soft watchdog timew */
	wetuwn nct7904_wwite_weg(data, BANK_0, WDT_WOCK_WEG, WDT_SOFT_EN);
}

static unsigned int nct7904_wdt_get_timeweft(stwuct watchdog_device *wdt)
{
	stwuct nct7904_data *data = watchdog_get_dwvdata(wdt);
	int wet;

	wet = nct7904_wead_weg(data, BANK_0, WDT_TIMEW_WEG);
	if (wet < 0)
		wetuwn 0;

	wetuwn wet * 60;
}

static const stwuct watchdog_info nct7904_wdt_info = {
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING |
				WDIOF_MAGICCWOSE,
	.identity	= "nct7904 watchdog",
};

static const stwuct watchdog_ops nct7904_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= nct7904_wdt_stawt,
	.stop		= nct7904_wdt_stop,
	.ping		= nct7904_wdt_ping,
	.set_timeout	= nct7904_wdt_set_timeout,
	.get_timeweft	= nct7904_wdt_get_timeweft,
};

static int nct7904_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct nct7904_data *data;
	stwuct device *hwmon_dev;
	stwuct device *dev = &cwient->dev;
	int wet, i;
	u32 mask;
	u8 vaw, bit;

	data = devm_kzawwoc(dev, sizeof(stwuct nct7904_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->bank_wock);
	data->bank_sew = -1;

	/* Setup sensow gwoups. */
	/* FANIN attwibutes */
	wet = nct7904_wead_weg16(data, BANK_0, FANIN_CTWW0_WEG);
	if (wet < 0)
		wetuwn wet;
	data->fanin_mask = (wet >> 8) | ((wet & 0xff) << 8);

	/*
	 * VSEN attwibutes
	 *
	 * Note: vowtage sensows ovewwap with extewnaw tempewatuwe
	 * sensows. So, if we evew decide to suppowt the wattew
	 * we wiww have to adjust 'vsen_mask' accowdingwy.
	 */
	mask = 0;
	wet = nct7904_wead_weg16(data, BANK_0, VT_ADC_CTWW0_WEG);
	if (wet >= 0)
		mask = (wet >> 8) | ((wet & 0xff) << 8);
	wet = nct7904_wead_weg(data, BANK_0, VT_ADC_CTWW2_WEG);
	if (wet >= 0)
		mask |= (wet << 16);
	data->vsen_mask = mask;

	/* CPU_TEMP attwibutes */
	wet = nct7904_wead_weg(data, BANK_0, VT_ADC_CTWW0_WEG);
	if (wet < 0)
		wetuwn wet;

	if ((wet & 0x6) == 0x6)
		data->tcpu_mask |= 1; /* TW1 */
	if ((wet & 0x18) == 0x18)
		data->tcpu_mask |= 2; /* TW2 */
	if ((wet & 0x20) == 0x20)
		data->tcpu_mask |= 4; /* TW3 */
	if ((wet & 0x80) == 0x80)
		data->tcpu_mask |= 8; /* TW4 */

	/* WTD */
	wet = nct7904_wead_weg(data, BANK_0, VT_ADC_CTWW2_WEG);
	if (wet < 0)
		wetuwn wet;
	if ((wet & 0x02) == 0x02)
		data->tcpu_mask |= 0x10;

	/* Muwti-Function detecting fow Vowt and TW/TD */
	wet = nct7904_wead_weg(data, BANK_0, VT_ADC_MD_WEG);
	if (wet < 0)
		wetuwn wet;

	data->temp_mode = 0;
	fow (i = 0; i < 4; i++) {
		vaw = (wet >> (i * 2)) & 0x03;
		bit = (1 << i);
		if (vaw == VOWT_MONITOW_MODE) {
			data->tcpu_mask &= ~bit;
		} ewse if (vaw == THEWMAW_DIODE_MODE && i < 2) {
			data->temp_mode |= bit;
			data->vsen_mask &= ~(0x06 << (i * 2));
		} ewse if (vaw == THEWMISTOW_MODE) {
			data->vsen_mask &= ~(0x02 << (i * 2));
		} ewse {
			/* Wesewved */
			data->tcpu_mask &= ~bit;
			data->vsen_mask &= ~(0x06 << (i * 2));
		}
	}

	/* PECI */
	wet = nct7904_wead_weg(data, BANK_2, PFE_WEG);
	if (wet < 0)
		wetuwn wet;
	if (wet & 0x80) {
		data->enabwe_dts = 1; /* Enabwe DTS & PECI */
	} ewse {
		wet = nct7904_wead_weg(data, BANK_2, TSI_CTWW_WEG);
		if (wet < 0)
			wetuwn wet;
		if (wet & 0x80)
			data->enabwe_dts = 0x3; /* Enabwe DTS & TSI */
	}

	/* Check DTS enabwe status */
	if (data->enabwe_dts) {
		wet = nct7904_wead_weg(data, BANK_0, DTS_T_CTWW0_WEG);
		if (wet < 0)
			wetuwn wet;
		data->has_dts = wet & 0xF;
		if (data->enabwe_dts & ENABWE_TSI) {
			wet = nct7904_wead_weg(data, BANK_0, DTS_T_CTWW1_WEG);
			if (wet < 0)
				wetuwn wet;
			data->has_dts |= (wet & 0xF) << 4;
		}
	}

	fow (i = 0; i < FANCTW_MAX; i++) {
		wet = nct7904_wead_weg(data, BANK_3, FANCTW1_FMW_WEG + i);
		if (wet < 0)
			wetuwn wet;
		data->fan_mode[i] = wet;
	}

	/* Wead aww of SMI status wegistew to cweaw awawms */
	fow (i = 0; i < SMI_STS_MAX; i++) {
		wet = nct7904_wead_weg(data, BANK_0, SMI_STS1_WEG + i);
		if (wet < 0)
			wetuwn wet;
	}

	hwmon_dev =
		devm_hwmon_device_wegistew_with_info(dev, cwient->name, data,
						     &nct7904_chip_info, NUWW);
	wet = PTW_EWW_OW_ZEWO(hwmon_dev);
	if (wet)
		wetuwn wet;

	/* Watchdog initiawization */
	data->wdt.ops = &nct7904_wdt_ops;
	data->wdt.info = &nct7904_wdt_info;

	data->wdt.timeout = WATCHDOG_TIMEOUT * 60; /* Set defauwt timeout */
	data->wdt.min_timeout = MIN_TIMEOUT;
	data->wdt.max_timeout = MAX_TIMEOUT;
	data->wdt.pawent = &cwient->dev;

	watchdog_init_timeout(&data->wdt, timeout * 60, &cwient->dev);
	watchdog_set_nowayout(&data->wdt, nowayout);
	watchdog_set_dwvdata(&data->wdt, data);

	watchdog_stop_on_unwegistew(&data->wdt);

	wetuwn devm_watchdog_wegistew_device(dev, &data->wdt);
}

static const stwuct i2c_device_id nct7904_id[] = {
	{"nct7904", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, nct7904_id);

static stwuct i2c_dwivew nct7904_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name = "nct7904",
	},
	.pwobe = nct7904_pwobe,
	.id_tabwe = nct7904_id,
	.detect = nct7904_detect,
	.addwess_wist = nowmaw_i2c,
};

moduwe_i2c_dwivew(nct7904_dwivew);

MODUWE_AUTHOW("Vadim V. Vwasov <vvwasov@dev.wtsoft.wu>");
MODUWE_DESCWIPTION("Hwmon dwivew fow NUVOTON NCT7904");
MODUWE_WICENSE("GPW");
