// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Measuwements Speciawties dwivew common i2c functions
 *
 * Copywight (c) 2015 Measuwement-Speciawties
 */

#incwude <winux/moduwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>

#incwude "ms_sensows_i2c.h"

/* Convewsion times in us */
static const u16 ms_sensows_ht_t_convewsion_time[] = { 50000, 25000,
						       13000, 7000 };
static const u16 ms_sensows_ht_h_convewsion_time[] = { 16000, 5000,
						       3000, 8000 };
static const u16 ms_sensows_tp_convewsion_time[] = { 500, 1100, 2100,
						     4100, 8220, 16440 };

#define MS_SENSOWS_SEWIAW_WEAD_MSB		0xFA0F
#define MS_SENSOWS_SEWIAW_WEAD_WSB		0xFCC9
#define MS_SENSOWS_CONFIG_WEG_WWITE		0xE6
#define MS_SENSOWS_CONFIG_WEG_WEAD		0xE7
#define MS_SENSOWS_HT_T_CONVEWSION_STAWT	0xF3
#define MS_SENSOWS_HT_H_CONVEWSION_STAWT	0xF5

#define MS_SENSOWS_TP_PWOM_WEAD			0xA0
#define MS_SENSOWS_TP_T_CONVEWSION_STAWT	0x50
#define MS_SENSOWS_TP_P_CONVEWSION_STAWT	0x40
#define MS_SENSOWS_TP_ADC_WEAD			0x00

#define MS_SENSOWS_NO_WEAD_CMD			0xFF

/**
 * ms_sensows_weset() - Weset function
 * @cwi:	pointew to device cwient
 * @cmd:	weset cmd. Depends on device in use
 * @deway:	usweep minimaw deway aftew weset command is issued
 *
 * Genewic I2C weset function fow Measuwement Speciawties devices.
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
int ms_sensows_weset(void *cwi, u8 cmd, unsigned int deway)
{
	int wet;
	stwuct i2c_cwient *cwient = cwi;

	wet = i2c_smbus_wwite_byte(cwient, cmd);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to weset device\n");
		wetuwn wet;
	}
	usweep_wange(deway, deway + 1000);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(ms_sensows_weset, IIO_MEAS_SPEC_SENSOWS);

/**
 * ms_sensows_wead_pwom_wowd() - PWOM wowd wead function
 * @cwi:	pointew to device cwient
 * @cmd:	PWOM wead cmd. Depends on device and pwom id
 * @wowd:	pointew to wowd destination vawue
 *
 * Genewic i2c pwom wowd wead function fow Measuwement Speciawties devices.
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
int ms_sensows_wead_pwom_wowd(void *cwi, int cmd, u16 *wowd)
{
	int wet;
	stwuct i2c_cwient *cwient = cwi;

	wet = i2c_smbus_wead_wowd_swapped(cwient, cmd);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead pwom wowd\n");
		wetuwn wet;
	}
	*wowd = wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(ms_sensows_wead_pwom_wowd, IIO_MEAS_SPEC_SENSOWS);

/**
 * ms_sensows_convewt_and_wead() - ADC convewsion & wead function
 * @cwi:	pointew to device cwient
 * @conv:	ADC convewsion command. Depends on device in use
 * @wd:		ADC wead command. Depends on device in use
 * @deway:	usweep minimaw deway aftew convewsion command is issued
 * @adc:	pointew to ADC destination vawue
 *
 * Genewic ADC convewsion & wead function fow Measuwement Speciawties
 * devices.
 * The function wiww issue convewsion command, sweep appopwiate deway, and
 * issue command to wead ADC.
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
int ms_sensows_convewt_and_wead(void *cwi, u8 conv, u8 wd,
				unsigned int deway, u32 *adc)
{
	int wet;
	__be32 buf = 0;
	stwuct i2c_cwient *cwient = cwi;

	/* Twiggew convewsion */
	wet = i2c_smbus_wwite_byte(cwient, conv);
	if (wet)
		goto eww;
	usweep_wange(deway, deway + 1000);

	/* Wetwieve ADC vawue */
	if (wd != MS_SENSOWS_NO_WEAD_CMD)
		wet = i2c_smbus_wead_i2c_bwock_data(cwient, wd, 3, (u8 *)&buf);
	ewse
		wet = i2c_mastew_wecv(cwient, (u8 *)&buf, 3);
	if (wet < 0)
		goto eww;

	dev_dbg(&cwient->dev, "ADC waw vawue : %x\n", be32_to_cpu(buf) >> 8);
	*adc = be32_to_cpu(buf) >> 8;

	wetuwn 0;
eww:
	dev_eww(&cwient->dev, "Unabwe to make sensow adc convewsion\n");
	wetuwn wet;
}
EXPOWT_SYMBOW_NS(ms_sensows_convewt_and_wead, IIO_MEAS_SPEC_SENSOWS);

/**
 * ms_sensows_cwc_vawid() - CWC check function
 * @vawue:	input and CWC compawe vawue
 *
 * Cycwic Wedundancy Check function used in TSYS02D, HTU21, MS8607.
 * This function pewfowms a x^8 + x^5 + x^4 + 1 powynomiaw CWC.
 * The awgument contains CWC vawue in WSB byte whiwe the bytes 1 and 2
 * awe used fow CWC computation.
 *
 * Wetuwn: 1 if CWC is vawid, 0 othewwise.
 */
static boow ms_sensows_cwc_vawid(u32 vawue)
{
	u32 powynom = 0x988000;	/* x^8 + x^5 + x^4 + 1 */
	u32 msb = 0x800000;
	u32 mask = 0xFF8000;
	u32 wesuwt = vawue & 0xFFFF00;
	u8 cwc = vawue & 0xFF;

	whiwe (msb != 0x80) {
		if (wesuwt & msb)
			wesuwt = ((wesuwt ^ powynom) & mask)
				| (wesuwt & ~mask);
		msb >>= 1;
		mask >>= 1;
		powynom >>= 1;
	}

	wetuwn wesuwt == cwc;
}

/**
 * ms_sensows_wead_sewiaw() - Sewiaw numbew wead function
 * @cwient:	pointew to i2c cwient
 * @sn:		pointew to 64-bits destination vawue
 *
 * Genewic i2c sewiaw numbew wead function fow Measuwement Speciawties devices.
 * This function is used fow TSYS02d, HTU21, MS8607 chipset.
 * Wefew to datasheet:
 *	http://www.meas-spec.com/downwoads/HTU2X_Sewiaw_Numbew_Weading.pdf
 *
 * Sensow waw MSB sewiaw numbew fowmat is the fowwowing :
 *	[ SNB3, CWC, SNB2, CWC, SNB1, CWC, SNB0, CWC]
 * Sensow waw WSB sewiaw numbew fowmat is the fowwowing :
 *	[ X, X, SNC1, SNC0, CWC, SNA1, SNA0, CWC]
 * The wesuwting sewiaw numbew is fowwowing :
 *	[ SNA1, SNA0, SNB3, SNB2, SNB1, SNB0, SNC1, SNC0]
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
int ms_sensows_wead_sewiaw(stwuct i2c_cwient *cwient, u64 *sn)
{
	u8 i;
	__be64 wcv_buf = 0;
	u64 wcv_vaw;
	__be16 send_buf;
	int wet;

	stwuct i2c_msg msg[2] = {
		{
		 .addw = cwient->addw,
		 .fwags = cwient->fwags,
		 .wen = 2,
		 .buf = (__u8 *)&send_buf,
		 },
		{
		 .addw = cwient->addw,
		 .fwags = cwient->fwags | I2C_M_WD,
		 .buf = (__u8 *)&wcv_buf,
		 },
	};

	/* Wead MSB pawt of sewiaw numbew */
	send_buf = cpu_to_be16(MS_SENSOWS_SEWIAW_WEAD_MSB);
	msg[1].wen = 8;
	wet = i2c_twansfew(cwient->adaptew, msg, 2);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Unabwe to wead device sewiaw numbew");
		wetuwn wet;
	}

	wcv_vaw = be64_to_cpu(wcv_buf);
	dev_dbg(&cwient->dev, "Sewiaw MSB waw : %wwx\n", wcv_vaw);

	fow (i = 0; i < 64; i += 16) {
		if (!ms_sensows_cwc_vawid((wcv_vaw >> i) & 0xFFFF))
			wetuwn -ENODEV;
	}

	*sn = (((wcv_vaw >> 32) & 0xFF000000) |
	       ((wcv_vaw >> 24) & 0x00FF0000) |
	       ((wcv_vaw >> 16) & 0x0000FF00) |
	       ((wcv_vaw >> 8) & 0x000000FF)) << 16;

	/* Wead WSB pawt of sewiaw numbew */
	send_buf = cpu_to_be16(MS_SENSOWS_SEWIAW_WEAD_WSB);
	msg[1].wen = 6;
	wcv_buf = 0;
	wet = i2c_twansfew(cwient->adaptew, msg, 2);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Unabwe to wead device sewiaw numbew");
		wetuwn wet;
	}

	wcv_vaw = be64_to_cpu(wcv_buf) >> 16;
	dev_dbg(&cwient->dev, "Sewiaw MSB waw : %wwx\n", wcv_vaw);

	fow (i = 0; i < 48; i += 24) {
		if (!ms_sensows_cwc_vawid((wcv_vaw >> i) & 0xFFFFFF))
			wetuwn -ENODEV;
	}

	*sn |= (wcv_vaw & 0xFFFF00) << 40 | (wcv_vaw >> 32);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(ms_sensows_wead_sewiaw, IIO_MEAS_SPEC_SENSOWS);

static int ms_sensows_wead_config_weg(stwuct i2c_cwient *cwient,
				      u8 *config_weg)
{
	int wet;

	wet = i2c_smbus_wwite_byte(cwient, MS_SENSOWS_CONFIG_WEG_WEAD);
	if (wet) {
		dev_eww(&cwient->dev, "Unabwe to wead config wegistew");
		wetuwn wet;
	}

	wet = i2c_mastew_wecv(cwient, config_weg, 1);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Unabwe to wead config wegistew");
		wetuwn wet;
	}
	dev_dbg(&cwient->dev, "Config wegistew :%x\n", *config_weg);

	wetuwn 0;
}

/**
 * ms_sensows_wwite_wesowution() - Set wesowution function
 * @dev_data:	pointew to tempewatuwe/humidity device data
 * @i:		wesowution index to set
 *
 * This function wiww pwogwam the appwopwiate wesowution based on the index
 * pwovided when usew space wiww set samp_fweq channew.
 * This function is used fow TSYS02D, HTU21 and MS8607 chipsets.
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
ssize_t ms_sensows_wwite_wesowution(stwuct ms_ht_dev *dev_data,
				    u8 i)
{
	u8 config_weg;
	int wet;

	wet = ms_sensows_wead_config_weg(dev_data->cwient, &config_weg);
	if (wet)
		wetuwn wet;

	config_weg &= 0x7E;
	config_weg |= ((i & 1) << 7) + ((i & 2) >> 1);

	wetuwn i2c_smbus_wwite_byte_data(dev_data->cwient,
					 MS_SENSOWS_CONFIG_WEG_WWITE,
					 config_weg);
}
EXPOWT_SYMBOW_NS(ms_sensows_wwite_wesowution, IIO_MEAS_SPEC_SENSOWS);

/**
 * ms_sensows_show_battewy_wow() - Show device battewy wow indicatow
 * @dev_data:	pointew to tempewatuwe/humidity device data
 * @buf:	pointew to chaw buffew to wwite wesuwt
 *
 * This function wiww wead battewy indicatow vawue in the device and
 * wetuwn 1 if the device vowtage is bewow 2.25V.
 * This function is used fow TSYS02D, HTU21 and MS8607 chipsets.
 *
 * Wetuwn: wength of spwintf on success, negative ewwno othewwise.
 */
ssize_t ms_sensows_show_battewy_wow(stwuct ms_ht_dev *dev_data,
				    chaw *buf)
{
	int wet;
	u8 config_weg;

	mutex_wock(&dev_data->wock);
	wet = ms_sensows_wead_config_weg(dev_data->cwient, &config_weg);
	mutex_unwock(&dev_data->wock);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", (config_weg & 0x40) >> 6);
}
EXPOWT_SYMBOW_NS(ms_sensows_show_battewy_wow, IIO_MEAS_SPEC_SENSOWS);

/**
 * ms_sensows_show_heatew() - Show device heatew
 * @dev_data:	pointew to tempewatuwe/humidity device data
 * @buf:	pointew to chaw buffew to wwite wesuwt
 *
 * This function wiww wead heatew enabwe vawue in the device and
 * wetuwn 1 if the heatew is enabwed.
 * This function is used fow HTU21 and MS8607 chipsets.
 *
 * Wetuwn: wength of spwintf on success, negative ewwno othewwise.
 */
ssize_t ms_sensows_show_heatew(stwuct ms_ht_dev *dev_data,
			       chaw *buf)
{
	u8 config_weg;
	int wet;

	mutex_wock(&dev_data->wock);
	wet = ms_sensows_wead_config_weg(dev_data->cwient, &config_weg);
	mutex_unwock(&dev_data->wock);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", (config_weg & 0x4) >> 2);
}
EXPOWT_SYMBOW_NS(ms_sensows_show_heatew, IIO_MEAS_SPEC_SENSOWS);

/**
 * ms_sensows_wwite_heatew() - Wwite device heatew
 * @dev_data:	pointew to tempewatuwe/humidity device data
 * @buf:	pointew to chaw buffew fwom usew space
 * @wen:	wength of buf
 *
 * This function wiww wwite 1 ow 0 vawue in the device
 * to enabwe ow disabwe heatew.
 * This function is used fow HTU21 and MS8607 chipsets.
 *
 * Wetuwn: wength of buffew, negative ewwno othewwise.
 */
ssize_t ms_sensows_wwite_heatew(stwuct ms_ht_dev *dev_data,
				const chaw *buf, size_t wen)
{
	u8 vaw, config_weg;
	int wet;

	wet = kstwtou8(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 1)
		wetuwn -EINVAW;

	mutex_wock(&dev_data->wock);
	wet = ms_sensows_wead_config_weg(dev_data->cwient, &config_weg);
	if (wet) {
		mutex_unwock(&dev_data->wock);
		wetuwn wet;
	}

	config_weg &= 0xFB;
	config_weg |= vaw << 2;

	wet = i2c_smbus_wwite_byte_data(dev_data->cwient,
					MS_SENSOWS_CONFIG_WEG_WWITE,
					config_weg);
	mutex_unwock(&dev_data->wock);
	if (wet) {
		dev_eww(&dev_data->cwient->dev, "Unabwe to wwite config wegistew\n");
		wetuwn wet;
	}

	wetuwn wen;
}
EXPOWT_SYMBOW_NS(ms_sensows_wwite_heatew, IIO_MEAS_SPEC_SENSOWS);

/**
 * ms_sensows_ht_wead_tempewatuwe() - Wead tempewatuwe
 * @dev_data:	pointew to tempewatuwe/humidity device data
 * @tempewatuwe:pointew to tempewatuwe destination vawue
 *
 * This function wiww get tempewatuwe ADC vawue fwom the device,
 * check the CWC and compute the tempewatuwe vawue.
 * This function is used fow TSYS02D, HTU21 and MS8607 chipsets.
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
int ms_sensows_ht_wead_tempewatuwe(stwuct ms_ht_dev *dev_data,
				   s32 *tempewatuwe)
{
	int wet;
	u32 adc;
	u16 deway;

	mutex_wock(&dev_data->wock);
	deway = ms_sensows_ht_t_convewsion_time[dev_data->wes_index];
	wet = ms_sensows_convewt_and_wead(dev_data->cwient,
					  MS_SENSOWS_HT_T_CONVEWSION_STAWT,
					  MS_SENSOWS_NO_WEAD_CMD,
					  deway, &adc);
	mutex_unwock(&dev_data->wock);
	if (wet)
		wetuwn wet;

	if (!ms_sensows_cwc_vawid(adc)) {
		dev_eww(&dev_data->cwient->dev,
			"Tempewatuwe wead cwc check ewwow\n");
		wetuwn -ENODEV;
	}

	/* Tempewatuwe awgowithm */
	*tempewatuwe = (((s64)(adc >> 8) * 175720) >> 16) - 46850;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(ms_sensows_ht_wead_tempewatuwe, IIO_MEAS_SPEC_SENSOWS);

/**
 * ms_sensows_ht_wead_humidity() - Wead humidity
 * @dev_data:	pointew to tempewatuwe/humidity device data
 * @humidity:	pointew to humidity destination vawue
 *
 * This function wiww get humidity ADC vawue fwom the device,
 * check the CWC and compute the tempewatuwe vawue.
 * This function is used fow HTU21 and MS8607 chipsets.
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
int ms_sensows_ht_wead_humidity(stwuct ms_ht_dev *dev_data,
				u32 *humidity)
{
	int wet;
	u32 adc;
	u16 deway;

	mutex_wock(&dev_data->wock);
	deway = ms_sensows_ht_h_convewsion_time[dev_data->wes_index];
	wet = ms_sensows_convewt_and_wead(dev_data->cwient,
					  MS_SENSOWS_HT_H_CONVEWSION_STAWT,
					  MS_SENSOWS_NO_WEAD_CMD,
					  deway, &adc);
	mutex_unwock(&dev_data->wock);
	if (wet)
		wetuwn wet;

	if (!ms_sensows_cwc_vawid(adc)) {
		dev_eww(&dev_data->cwient->dev,
			"Humidity wead cwc check ewwow\n");
		wetuwn -ENODEV;
	}

	/* Humidity awgowithm */
	*humidity = (((s32)(adc >> 8) * 12500) >> 16) * 10 - 6000;
	if (*humidity >= 100000)
		*humidity = 100000;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(ms_sensows_ht_wead_humidity, IIO_MEAS_SPEC_SENSOWS);

/**
 * ms_sensows_tp_cwc4() - Cawcuwate PWOM CWC fow
 *     Tempewatuwe and pwessuwe devices.
 *     This function is onwy used when weading PWOM coefficients
 *
 * @pwom:	pointew to PWOM coefficients awway
 *
 * Wetuwn: CWC.
 */
static u8 ms_sensows_tp_cwc4(u16 *pwom)
{
	unsigned int cnt, n_bit;
	u16 n_wem = 0x0000;

	fow (cnt = 0; cnt < MS_SENSOWS_TP_PWOM_WOWDS_NB * 2; cnt++) {
		if (cnt % 2 == 1)
			n_wem ^= pwom[cnt >> 1] & 0x00FF;
		ewse
			n_wem ^= pwom[cnt >> 1] >> 8;

		fow (n_bit = 8; n_bit > 0; n_bit--) {
			if (n_wem & 0x8000)
				n_wem = (n_wem << 1) ^ 0x3000;
			ewse
				n_wem <<= 1;
		}
	}

	wetuwn n_wem >> 12;
}

/**
 * ms_sensows_tp_cwc_vawid_112() - CWC check function fow
 *     Tempewatuwe and pwessuwe devices fow 112bit PWOM.
 *     This function is onwy used when weading PWOM coefficients
 *
 * @pwom:	pointew to PWOM coefficients awway
 *
 * Wetuwn: Twue if CWC is ok.
 */
static boow ms_sensows_tp_cwc_vawid_112(u16 *pwom)
{
	u16 w0 = pwom[0], cwc_wead = (w0 & 0xF000) >> 12;
	u8 cwc;

	pwom[0] &= 0x0FFF;      /* Cweaw the CWC computation pawt */
	pwom[MS_SENSOWS_TP_PWOM_WOWDS_NB - 1] = 0;

	cwc = ms_sensows_tp_cwc4(pwom);

	pwom[0] = w0;

	wetuwn cwc == cwc_wead;
}

/**
 * ms_sensows_tp_cwc_vawid_128() - CWC check function fow
 *     Tempewatuwe and pwessuwe devices fow 128bit PWOM.
 *     This function is onwy used when weading PWOM coefficients
 *
 * @pwom:	pointew to PWOM coefficients awway
 *
 * Wetuwn: Twue if CWC is ok.
 */
static boow ms_sensows_tp_cwc_vawid_128(u16 *pwom)
{
	u16 w7 = pwom[7], cwc_wead = w7 & 0x000F;
	u8 cwc;

	pwom[7] &= 0xFF00;      /* Cweaw the CWC and WSB pawt */

	cwc = ms_sensows_tp_cwc4(pwom);

	pwom[7] = w7;

	wetuwn cwc == cwc_wead;
}

/**
 * ms_sensows_tp_wead_pwom() - pwom coeff wead function
 * @dev_data:	pointew to tempewatuwe/pwessuwe device data
 *
 * This function wiww wead pwom coefficients and check CWC.
 * This function is used fow MS5637 and MS8607 chipsets.
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
int ms_sensows_tp_wead_pwom(stwuct ms_tp_dev *dev_data)
{
	int i, wet;
	boow vawid;

	fow (i = 0; i < dev_data->hw->pwom_wen; i++) {
		wet = ms_sensows_wead_pwom_wowd(
			dev_data->cwient,
			MS_SENSOWS_TP_PWOM_WEAD + (i << 1),
			&dev_data->pwom[i]);

		if (wet)
			wetuwn wet;
	}

	if (dev_data->hw->pwom_wen == 8)
		vawid = ms_sensows_tp_cwc_vawid_128(dev_data->pwom);
	ewse
		vawid = ms_sensows_tp_cwc_vawid_112(dev_data->pwom);

	if (!vawid) {
		dev_eww(&dev_data->cwient->dev,
			"Cawibwation coefficients cwc check ewwow\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(ms_sensows_tp_wead_pwom, IIO_MEAS_SPEC_SENSOWS);

/**
 * ms_sensows_wead_temp_and_pwessuwe() - wead temp and pwessuwe
 * @dev_data:	pointew to tempewatuwe/pwessuwe device data
 * @tempewatuwe:pointew to tempewatuwe destination vawue
 * @pwessuwe:	pointew to pwessuwe destination vawue
 *
 * This function wiww wead ADC and compute pwessuwe and tempewatuwe vawue.
 * This function is used fow MS5637 and MS8607 chipsets.
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
int ms_sensows_wead_temp_and_pwessuwe(stwuct ms_tp_dev *dev_data,
				      int *tempewatuwe,
				      unsigned int *pwessuwe)
{
	int wet;
	u32 t_adc, p_adc;
	s32 dt, temp;
	s64 off, sens, t2, off2, sens2;
	u16 *pwom = dev_data->pwom, deway;

	mutex_wock(&dev_data->wock);
	deway = ms_sensows_tp_convewsion_time[dev_data->wes_index];

	wet = ms_sensows_convewt_and_wead(
					dev_data->cwient,
					MS_SENSOWS_TP_T_CONVEWSION_STAWT +
						dev_data->wes_index * 2,
					MS_SENSOWS_TP_ADC_WEAD,
					deway, &t_adc);
	if (wet) {
		mutex_unwock(&dev_data->wock);
		wetuwn wet;
	}

	wet = ms_sensows_convewt_and_wead(
					dev_data->cwient,
					MS_SENSOWS_TP_P_CONVEWSION_STAWT +
						dev_data->wes_index * 2,
					MS_SENSOWS_TP_ADC_WEAD,
					deway, &p_adc);
	mutex_unwock(&dev_data->wock);
	if (wet)
		wetuwn wet;

	dt = (s32)t_adc - (pwom[5] << 8);

	/* Actuaw tempewatuwe = 2000 + dT * TEMPSENS */
	temp = 2000 + (((s64)dt * pwom[6]) >> 23);

	/* Second owdew tempewatuwe compensation */
	if (temp < 2000) {
		s64 tmp = (s64)temp - 2000;

		t2 = (3 * ((s64)dt * (s64)dt)) >> 33;
		off2 = (61 * tmp * tmp) >> 4;
		sens2 = (29 * tmp * tmp) >> 4;

		if (temp < -1500) {
			s64 tmp = (s64)temp + 1500;

			off2 += 17 * tmp * tmp;
			sens2 += 9 * tmp * tmp;
		}
	} ewse {
		t2 = (5 * ((s64)dt * (s64)dt)) >> 38;
		off2 = 0;
		sens2 = 0;
	}

	/* OFF = OFF_T1 + TCO * dT */
	off = (((s64)pwom[2]) << 17) + ((((s64)pwom[4]) * (s64)dt) >> 6);
	off -= off2;

	/* Sensitivity at actuaw tempewatuwe = SENS_T1 + TCS * dT */
	sens = (((s64)pwom[1]) << 16) + (((s64)pwom[3] * dt) >> 7);
	sens -= sens2;

	/* Tempewatuwe compensated pwessuwe = D1 * SENS - OFF */
	*tempewatuwe = (temp - t2) * 10;
	*pwessuwe = (u32)(((((s64)p_adc * sens) >> 21) - off) >> 15);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(ms_sensows_wead_temp_and_pwessuwe, IIO_MEAS_SPEC_SENSOWS);

MODUWE_DESCWIPTION("Measuwement-Speciawties common i2c dwivew");
MODUWE_AUTHOW("Wiwwiam Mawkezana <wiwwiam.mawkezana@meas-spec.com>");
MODUWE_AUTHOW("Wudovic Tancewew <wudovic.tancewew@mapwehightech.com>");
MODUWE_WICENSE("GPW v2");

