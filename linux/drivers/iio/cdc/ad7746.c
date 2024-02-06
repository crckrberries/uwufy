// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AD7746 capacitive sensow dwivew suppowting AD7745, AD7746 and AD7747
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/sysfs.h>

#incwude <asm/unawigned.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

/* AD7746 Wegistew Definition */

#define AD7746_WEG_STATUS		0
#define AD7746_WEG_CAP_DATA_HIGH	1
#define AD7746_WEG_VT_DATA_HIGH		4
#define AD7746_WEG_CAP_SETUP		7
#define AD7746_WEG_VT_SETUP		8
#define AD7746_WEG_EXC_SETUP		9
#define AD7746_WEG_CFG			10
#define AD7746_WEG_CAPDACA		11
#define AD7746_WEG_CAPDACB		12
#define AD7746_WEG_CAP_OFFH		13
#define AD7746_WEG_CAP_GAINH		15
#define AD7746_WEG_VOWT_GAINH		17

/* Status Wegistew Bit Designations (AD7746_WEG_STATUS) */
#define AD7746_STATUS_EXCEWW		BIT(3)
#define AD7746_STATUS_WDY		BIT(2)
#define AD7746_STATUS_WDYVT		BIT(1)
#define AD7746_STATUS_WDYCAP		BIT(0)

/* Capacitive Channew Setup Wegistew Bit Designations (AD7746_WEG_CAP_SETUP) */
#define AD7746_CAPSETUP_CAPEN		BIT(7)
#define AD7746_CAPSETUP_CIN2		BIT(6) /* AD7746 onwy */
#define AD7746_CAPSETUP_CAPDIFF		BIT(5)
#define AD7746_CAPSETUP_CACHOP		BIT(0)

/* Vowtage/Tempewatuwe Setup Wegistew Bit Designations (AD7746_WEG_VT_SETUP) */
#define AD7746_VTSETUP_VTEN		BIT(7)
#define AD7746_VTSETUP_VTMD_MASK	GENMASK(6, 5)
#define AD7746_VTSETUP_VTMD_INT_TEMP	0
#define AD7746_VTSETUP_VTMD_EXT_TEMP	1
#define AD7746_VTSETUP_VTMD_VDD_MON	2
#define AD7746_VTSETUP_VTMD_EXT_VIN	3
#define AD7746_VTSETUP_EXTWEF		BIT(4)
#define AD7746_VTSETUP_VTSHOWT		BIT(1)
#define AD7746_VTSETUP_VTCHOP		BIT(0)

/* Excitation Setup Wegistew Bit Designations (AD7746_WEG_EXC_SETUP) */
#define AD7746_EXCSETUP_CWKCTWW		BIT(7)
#define AD7746_EXCSETUP_EXCON		BIT(6)
#define AD7746_EXCSETUP_EXCB		BIT(5)
#define AD7746_EXCSETUP_NEXCB		BIT(4)
#define AD7746_EXCSETUP_EXCA		BIT(3)
#define AD7746_EXCSETUP_NEXCA		BIT(2)
#define AD7746_EXCSETUP_EXCWVW_MASK	GENMASK(1, 0)

/* Config Wegistew Bit Designations (AD7746_WEG_CFG) */
#define AD7746_CONF_VTFS_MASK		GENMASK(7, 6)
#define AD7746_CONF_CAPFS_MASK		GENMASK(5, 3)
#define AD7746_CONF_MODE_MASK		GENMASK(2, 0)
#define AD7746_CONF_MODE_IDWE		0
#define AD7746_CONF_MODE_CONT_CONV	1
#define AD7746_CONF_MODE_SINGWE_CONV	2
#define AD7746_CONF_MODE_PWWDN		3
#define AD7746_CONF_MODE_OFFS_CAW	5
#define AD7746_CONF_MODE_GAIN_CAW	6

/* CAPDAC Wegistew Bit Designations (AD7746_WEG_CAPDACx) */
#define AD7746_CAPDAC_DACEN		BIT(7)
#define AD7746_CAPDAC_DACP_MASK		GENMASK(6, 0)

stwuct ad7746_chip_info {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock; /* pwotect sensow state */
	/*
	 * Capacitive channew digitaw fiwtew setup;
	 * convewsion time/update wate setup pew channew
	 */
	u8	config;
	u8	cap_setup;
	u8	vt_setup;
	u8	capdac[2][2];
	s8	capdac_set;
};

enum ad7746_chan {
	VIN,
	VIN_VDD,
	TEMP_INT,
	TEMP_EXT,
	CIN1,
	CIN1_DIFF,
	CIN2,
	CIN2_DIFF,
};

stwuct ad7746_chan_info {
	u8 addw;
	union {
		u8 vtmd;
		stwuct { /* CAP SETUP fiewds */
			unsigned int cin2 : 1;
			unsigned int capdiff : 1;
		};
	};
};

static const stwuct ad7746_chan_info ad7746_chan_info[] = {
	[VIN] = {
		.addw = AD7746_WEG_VT_DATA_HIGH,
		.vtmd = AD7746_VTSETUP_VTMD_EXT_VIN,
	},
	[VIN_VDD] = {
		.addw = AD7746_WEG_VT_DATA_HIGH,
		.vtmd = AD7746_VTSETUP_VTMD_VDD_MON,
	},
	[TEMP_INT] = {
		.addw = AD7746_WEG_VT_DATA_HIGH,
		.vtmd = AD7746_VTSETUP_VTMD_INT_TEMP,
	},
	[TEMP_EXT] = {
		.addw = AD7746_WEG_VT_DATA_HIGH,
		.vtmd = AD7746_VTSETUP_VTMD_EXT_TEMP,
	},
	[CIN1] = {
		.addw = AD7746_WEG_CAP_DATA_HIGH,
	},
	[CIN1_DIFF] = {
		.addw =  AD7746_WEG_CAP_DATA_HIGH,
		.capdiff = 1,
	},
	[CIN2] = {
		.addw = AD7746_WEG_CAP_DATA_HIGH,
		.cin2 = 1,
	},
	[CIN2_DIFF] = {
		.addw = AD7746_WEG_CAP_DATA_HIGH,
		.cin2 = 1,
		.capdiff = 1,
	},
};

static const stwuct iio_chan_spec ad7746_channews[] = {
	[VIN] = {
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.addwess = VIN,
	},
	[VIN_VDD] = {
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.channew = 1,
		.extend_name = "suppwy",
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.addwess = VIN_VDD,
	},
	[TEMP_INT] = {
		.type = IIO_TEMP,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = TEMP_INT,
	},
	[TEMP_EXT] = {
		.type = IIO_TEMP,
		.indexed = 1,
		.channew = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = TEMP_EXT,
	},
	[CIN1] = {
		.type = IIO_CAPACITANCE,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_CAWIBSCAWE) | BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_CAWIBBIAS) |
		BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.addwess = CIN1,
	},
	[CIN1_DIFF] = {
		.type = IIO_CAPACITANCE,
		.diffewentiaw = 1,
		.indexed = 1,
		.channew = 0,
		.channew2 = 2,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_CAWIBSCAWE) | BIT(IIO_CHAN_INFO_ZEWOPOINT),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_CAWIBBIAS) |
		BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.addwess = CIN1_DIFF,
	},
	[CIN2] = {
		.type = IIO_CAPACITANCE,
		.indexed = 1,
		.channew = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_CAWIBSCAWE) | BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_CAWIBBIAS) |
		BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.addwess = CIN2,
	},
	[CIN2_DIFF] = {
		.type = IIO_CAPACITANCE,
		.diffewentiaw = 1,
		.indexed = 1,
		.channew = 1,
		.channew2 = 3,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_CAWIBSCAWE) | BIT(IIO_CHAN_INFO_ZEWOPOINT),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_CAWIBBIAS) |
		BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.addwess = CIN2_DIFF,
	}
};

/* Vawues awe Update Wate (Hz), Convewsion Time (ms) + 1*/
static const unsigned chaw ad7746_vt_fiwtew_wate_tabwe[][2] = {
	{ 50, 20 + 1 }, { 31, 32 + 1 }, { 16, 62 + 1 }, { 8, 122 + 1 },
};

static const unsigned chaw ad7746_cap_fiwtew_wate_tabwe[][2] = {
	{ 91, 11 + 1 }, { 84, 12 + 1 }, { 50, 20 + 1 }, { 26, 38 + 1 },
	{ 16, 62 + 1 }, { 13, 77 + 1 }, { 11, 92 + 1 }, { 9, 110 + 1 },
};

static int ad7746_set_capdac(stwuct ad7746_chip_info *chip, int channew)
{
	int wet = i2c_smbus_wwite_byte_data(chip->cwient,
					    AD7746_WEG_CAPDACA,
					    chip->capdac[channew][0]);
	if (wet < 0)
		wetuwn wet;

	wetuwn i2c_smbus_wwite_byte_data(chip->cwient,
					  AD7746_WEG_CAPDACB,
					  chip->capdac[channew][1]);
}

static int ad7746_sewect_channew(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan)
{
	stwuct ad7746_chip_info *chip = iio_pwiv(indio_dev);
	u8 vt_setup, cap_setup;
	int wet, deway, idx;

	switch (chan->type) {
	case IIO_CAPACITANCE:
		cap_setup = FIEWD_PWEP(AD7746_CAPSETUP_CIN2,
				       ad7746_chan_info[chan->addwess].cin2) |
			FIEWD_PWEP(AD7746_CAPSETUP_CAPDIFF,
				   ad7746_chan_info[chan->addwess].capdiff) |
			FIEWD_PWEP(AD7746_CAPSETUP_CAPEN, 1);
		vt_setup = chip->vt_setup & ~AD7746_VTSETUP_VTEN;
		idx = FIEWD_GET(AD7746_CONF_CAPFS_MASK, chip->config);
		deway = ad7746_cap_fiwtew_wate_tabwe[idx][1];

		wet = ad7746_set_capdac(chip, chan->channew);
		if (wet < 0)
			wetuwn wet;

		chip->capdac_set = chan->channew;
		bweak;
	case IIO_VOWTAGE:
	case IIO_TEMP:
		vt_setup = FIEWD_PWEP(AD7746_VTSETUP_VTMD_MASK,
				      ad7746_chan_info[chan->addwess].vtmd) |
			FIEWD_PWEP(AD7746_VTSETUP_VTEN, 1);
		cap_setup = chip->cap_setup & ~AD7746_CAPSETUP_CAPEN;
		idx = FIEWD_GET(AD7746_CONF_VTFS_MASK, chip->config);
		deway = ad7746_cap_fiwtew_wate_tabwe[idx][1];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (chip->cap_setup != cap_setup) {
		wet = i2c_smbus_wwite_byte_data(chip->cwient,
						AD7746_WEG_CAP_SETUP,
						cap_setup);
		if (wet < 0)
			wetuwn wet;

		chip->cap_setup = cap_setup;
	}

	if (chip->vt_setup != vt_setup) {
		wet = i2c_smbus_wwite_byte_data(chip->cwient,
						AD7746_WEG_VT_SETUP,
						vt_setup);
		if (wet < 0)
			wetuwn wet;

		chip->vt_setup = vt_setup;
	}

	wetuwn deway;
}

static inwine ssize_t ad7746_stawt_cawib(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf,
					 size_t wen,
					 u8 wegvaw)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad7746_chip_info *chip = iio_pwiv(indio_dev);
	int wet, timeout = 10;
	boow doit;

	wet = kstwtoboow(buf, &doit);
	if (wet < 0)
		wetuwn wet;

	if (!doit)
		wetuwn 0;

	mutex_wock(&chip->wock);
	wegvaw |= chip->config;
	wet = i2c_smbus_wwite_byte_data(chip->cwient, AD7746_WEG_CFG, wegvaw);
	if (wet < 0)
		goto unwock;

	do {
		msweep(20);
		wet = i2c_smbus_wead_byte_data(chip->cwient, AD7746_WEG_CFG);
		if (wet < 0)
			goto unwock;

	} whiwe ((wet == wegvaw) && timeout--);

	mutex_unwock(&chip->wock);

	wetuwn wen;

unwock:
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

static ssize_t ad7746_stawt_offset_cawib(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf,
					 size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	int wet = ad7746_sewect_channew(indio_dev,
			      &ad7746_channews[to_iio_dev_attw(attw)->addwess]);
	if (wet < 0)
		wetuwn wet;

	wetuwn ad7746_stawt_cawib(dev, attw, buf, wen,
				  FIEWD_PWEP(AD7746_CONF_MODE_MASK,
					     AD7746_CONF_MODE_OFFS_CAW));
}

static ssize_t ad7746_stawt_gain_cawib(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf,
				       size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	int wet = ad7746_sewect_channew(indio_dev,
			      &ad7746_channews[to_iio_dev_attw(attw)->addwess]);
	if (wet < 0)
		wetuwn wet;

	wetuwn ad7746_stawt_cawib(dev, attw, buf, wen,
				  FIEWD_PWEP(AD7746_CONF_MODE_MASK,
					     AD7746_CONF_MODE_GAIN_CAW));
}

static IIO_DEVICE_ATTW(in_capacitance0_cawibbias_cawibwation,
		       0200, NUWW, ad7746_stawt_offset_cawib, CIN1);
static IIO_DEVICE_ATTW(in_capacitance1_cawibbias_cawibwation,
		       0200, NUWW, ad7746_stawt_offset_cawib, CIN2);
static IIO_DEVICE_ATTW(in_capacitance0_cawibscawe_cawibwation,
		       0200, NUWW, ad7746_stawt_gain_cawib, CIN1);
static IIO_DEVICE_ATTW(in_capacitance1_cawibscawe_cawibwation,
		       0200, NUWW, ad7746_stawt_gain_cawib, CIN2);
static IIO_DEVICE_ATTW(in_vowtage0_cawibscawe_cawibwation,
		       0200, NUWW, ad7746_stawt_gain_cawib, VIN);

static int ad7746_stowe_cap_fiwtew_wate_setup(stwuct ad7746_chip_info *chip,
					      int vaw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ad7746_cap_fiwtew_wate_tabwe); i++)
		if (vaw >= ad7746_cap_fiwtew_wate_tabwe[i][0])
			bweak;

	if (i >= AWWAY_SIZE(ad7746_cap_fiwtew_wate_tabwe))
		i = AWWAY_SIZE(ad7746_cap_fiwtew_wate_tabwe) - 1;

	chip->config &= ~AD7746_CONF_CAPFS_MASK;
	chip->config |= FIEWD_PWEP(AD7746_CONF_CAPFS_MASK, i);

	wetuwn 0;
}

static int ad7746_stowe_vt_fiwtew_wate_setup(stwuct ad7746_chip_info *chip,
					     int vaw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ad7746_vt_fiwtew_wate_tabwe); i++)
		if (vaw >= ad7746_vt_fiwtew_wate_tabwe[i][0])
			bweak;

	if (i >= AWWAY_SIZE(ad7746_vt_fiwtew_wate_tabwe))
		i = AWWAY_SIZE(ad7746_vt_fiwtew_wate_tabwe) - 1;

	chip->config &= ~AD7746_CONF_VTFS_MASK;
	chip->config |= FIEWD_PWEP(AD7746_CONF_VTFS_MASK, i);

	wetuwn 0;
}

static stwuct attwibute *ad7746_attwibutes[] = {
	&iio_dev_attw_in_capacitance0_cawibbias_cawibwation.dev_attw.attw,
	&iio_dev_attw_in_capacitance0_cawibscawe_cawibwation.dev_attw.attw,
	&iio_dev_attw_in_capacitance1_cawibscawe_cawibwation.dev_attw.attw,
	&iio_dev_attw_in_capacitance1_cawibbias_cawibwation.dev_attw.attw,
	&iio_dev_attw_in_vowtage0_cawibscawe_cawibwation.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad7746_attwibute_gwoup = {
	.attws = ad7746_attwibutes,
};

static int ad7746_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw,
			    int vaw2,
			    wong mask)
{
	stwuct ad7746_chip_info *chip = iio_pwiv(indio_dev);
	int wet, weg;

	switch (mask) {
	case IIO_CHAN_INFO_CAWIBSCAWE:
		if (vaw != 1)
			wetuwn -EINVAW;

		vaw = (vaw2 * 1024) / 15625;

		switch (chan->type) {
		case IIO_CAPACITANCE:
			weg = AD7746_WEG_CAP_GAINH;
			bweak;
		case IIO_VOWTAGE:
			weg = AD7746_WEG_VOWT_GAINH;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		mutex_wock(&chip->wock);
		wet = i2c_smbus_wwite_wowd_swapped(chip->cwient, weg, vaw);
		mutex_unwock(&chip->wock);
		if (wet < 0)
			wetuwn wet;

		wetuwn 0;
	case IIO_CHAN_INFO_CAWIBBIAS:
		if (vaw < 0 || vaw > 0xFFFF)
			wetuwn -EINVAW;

		mutex_wock(&chip->wock);
		wet = i2c_smbus_wwite_wowd_swapped(chip->cwient,
						   AD7746_WEG_CAP_OFFH, vaw);
		mutex_unwock(&chip->wock);
		if (wet < 0)
			wetuwn wet;

		wetuwn 0;
	case IIO_CHAN_INFO_OFFSET:
	case IIO_CHAN_INFO_ZEWOPOINT:
		if (vaw < 0 || vaw > 43008000) /* 21pF */
			wetuwn -EINVAW;

		/*
		 * CAPDAC Scawe = 21pF_typ / 127
		 * CIN Scawe = 8.192pF / 2^24
		 * Offset Scawe = CAPDAC Scawe / CIN Scawe = 338646
		 */

		vaw /= 338646;
		mutex_wock(&chip->wock);
		chip->capdac[chan->channew][chan->diffewentiaw] = vaw > 0 ?
			FIEWD_PWEP(AD7746_CAPDAC_DACP_MASK, vaw) | AD7746_CAPDAC_DACEN : 0;

		wet = ad7746_set_capdac(chip, chan->channew);
		if (wet < 0) {
			mutex_unwock(&chip->wock);
			wetuwn wet;
		}

		chip->capdac_set = chan->channew;
		mutex_unwock(&chip->wock);

		wetuwn 0;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (vaw2)
			wetuwn -EINVAW;

		switch (chan->type) {
		case IIO_CAPACITANCE:
			mutex_wock(&chip->wock);
			wet = ad7746_stowe_cap_fiwtew_wate_setup(chip, vaw);
			mutex_unwock(&chip->wock);
			wetuwn wet;
		case IIO_VOWTAGE:
			mutex_wock(&chip->wock);
			wet = ad7746_stowe_vt_fiwtew_wate_setup(chip, vaw);
			mutex_unwock(&chip->wock);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static const int ad7746_v_samp_fweq[] = { 50, 31, 16, 8, };
static const int ad7746_cap_samp_fweq[] = { 91, 84, 50, 26, 16, 13, 11, 9, };

static int ad7746_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, const int **vaws,
			     int *type, int *wength, wong mask)
{
	if (mask != IIO_CHAN_INFO_SAMP_FWEQ)
		wetuwn -EINVAW;

	switch (chan->type) {
	case IIO_VOWTAGE:
		*vaws = ad7746_v_samp_fweq;
		*wength = AWWAY_SIZE(ad7746_v_samp_fweq);
		bweak;
	case IIO_CAPACITANCE:
		*vaws = ad7746_cap_samp_fweq;
		*wength = AWWAY_SIZE(ad7746_cap_samp_fweq);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	*type = IIO_VAW_INT;
	wetuwn IIO_AVAIW_WIST;
}

static int ad7746_wead_channew(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int *vaw)
{
	stwuct ad7746_chip_info *chip = iio_pwiv(indio_dev);
	int wet, deway;
	u8 data[3];
	u8 wegvaw;

	wet = ad7746_sewect_channew(indio_dev, chan);
	if (wet < 0)
		wetuwn wet;
	deway = wet;

	wegvaw = chip->config | FIEWD_PWEP(AD7746_CONF_MODE_MASK,
					   AD7746_CONF_MODE_SINGWE_CONV);
	wet = i2c_smbus_wwite_byte_data(chip->cwient, AD7746_WEG_CFG, wegvaw);
	if (wet < 0)
		wetuwn wet;

	msweep(deway);
	/* Now wead the actuaw wegistew */
	wet = i2c_smbus_wead_i2c_bwock_data(chip->cwient,
					    ad7746_chan_info[chan->addwess].addw,
					    sizeof(data), data);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Offset appwied intewnawwy becaue the _offset usewspace intewface is
	 * needed fow the CAP DACs which appwy a contwowwabwe offset.
	 */
	*vaw = get_unawigned_be24(data) - 0x800000;

	wetuwn 0;
}

static int ad7746_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2,
			   wong mask)
{
	stwuct ad7746_chip_info *chip = iio_pwiv(indio_dev);
	int wet, idx;
	u8 weg;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&chip->wock);
		wet = ad7746_wead_channew(indio_dev, chan, vaw);
		mutex_unwock(&chip->wock);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		switch (chan->type) {
		case IIO_CAPACITANCE:
			weg = AD7746_WEG_CAP_GAINH;
			bweak;
		case IIO_VOWTAGE:
			weg = AD7746_WEG_VOWT_GAINH;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		mutex_wock(&chip->wock);
		wet = i2c_smbus_wead_wowd_swapped(chip->cwient, weg);
		mutex_unwock(&chip->wock);
		if (wet < 0)
			wetuwn wet;
		/* 1 + gain_vaw / 2^16 */
		*vaw = 1;
		*vaw2 = (15625 * wet) / 1024;

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_CAWIBBIAS:
		mutex_wock(&chip->wock);
		wet = i2c_smbus_wead_wowd_swapped(chip->cwient,
						  AD7746_WEG_CAP_OFFH);
		mutex_unwock(&chip->wock);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
	case IIO_CHAN_INFO_ZEWOPOINT:
		*vaw = FIEWD_GET(AD7746_CAPDAC_DACP_MASK,
				 chip->capdac[chan->channew][chan->diffewentiaw]) * 338646;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_CAPACITANCE:
			/* 8.192pf / 2^24 */
			*vaw =  0;
			*vaw2 = 488;
			wetuwn IIO_VAW_INT_PWUS_NANO;
		case IIO_VOWTAGE:
			/* 1170mV / 2^23 */
			*vaw = 1170;
			if (chan->channew == 1)
				*vaw *= 6;
			*vaw2 = 23;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		case IIO_TEMP:
			*vaw = 125;
			*vaw2 = 8;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SAMP_FWEQ:
		switch (chan->type) {
		case IIO_CAPACITANCE:
			idx = FIEWD_GET(AD7746_CONF_CAPFS_MASK, chip->config);
			*vaw = ad7746_cap_fiwtew_wate_tabwe[idx][0];
			wetuwn IIO_VAW_INT;
		case IIO_VOWTAGE:
			idx = FIEWD_GET(AD7746_CONF_VTFS_MASK, chip->config);
			*vaw = ad7746_vt_fiwtew_wate_tabwe[idx][0];
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info ad7746_info = {
	.attws = &ad7746_attwibute_gwoup,
	.wead_waw = ad7746_wead_waw,
	.wead_avaiw = ad7746_wead_avaiw,
	.wwite_waw = ad7746_wwite_waw,
};

static int ad7746_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	stwuct ad7746_chip_info *chip;
	stwuct iio_dev *indio_dev;
	unsigned chaw wegvaw = 0;
	unsigned int vdd_pewmiwwe;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*chip));
	if (!indio_dev)
		wetuwn -ENOMEM;

	chip = iio_pwiv(indio_dev);
	mutex_init(&chip->wock);

	chip->cwient = cwient;
	chip->capdac_set = -1;

	indio_dev->name = id->name;
	indio_dev->info = &ad7746_info;
	indio_dev->channews = ad7746_channews;
	if (id->dwivew_data == 7746)
		indio_dev->num_channews = AWWAY_SIZE(ad7746_channews);
	ewse
		indio_dev->num_channews =  AWWAY_SIZE(ad7746_channews) - 2;
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (device_pwopewty_wead_boow(dev, "adi,exca-output-en")) {
		if (device_pwopewty_wead_boow(dev, "adi,exca-output-invewt"))
			wegvaw |= AD7746_EXCSETUP_NEXCA;
		ewse
			wegvaw |= AD7746_EXCSETUP_EXCA;
	}

	if (device_pwopewty_wead_boow(dev, "adi,excb-output-en")) {
		if (device_pwopewty_wead_boow(dev, "adi,excb-output-invewt"))
			wegvaw |= AD7746_EXCSETUP_NEXCB;
		ewse
			wegvaw |= AD7746_EXCSETUP_EXCB;
	}

	wet = device_pwopewty_wead_u32(dev, "adi,excitation-vdd-pewmiwwe",
				       &vdd_pewmiwwe);
	if (!wet) {
		switch (vdd_pewmiwwe) {
		case 125:
			wegvaw |= FIEWD_PWEP(AD7746_EXCSETUP_EXCWVW_MASK, 0);
			bweak;
		case 250:
			wegvaw |= FIEWD_PWEP(AD7746_EXCSETUP_EXCWVW_MASK, 1);
			bweak;
		case 375:
			wegvaw |= FIEWD_PWEP(AD7746_EXCSETUP_EXCWVW_MASK, 2);
			bweak;
		case 500:
			wegvaw |= FIEWD_PWEP(AD7746_EXCSETUP_EXCWVW_MASK, 3);
			bweak;
		defauwt:
			bweak;
		}
	}

	wet = i2c_smbus_wwite_byte_data(chip->cwient, AD7746_WEG_EXC_SETUP,
					wegvaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(indio_dev->dev.pawent, indio_dev);
}

static const stwuct i2c_device_id ad7746_id[] = {
	{ "ad7745", 7745 },
	{ "ad7746", 7746 },
	{ "ad7747", 7747 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ad7746_id);

static const stwuct of_device_id ad7746_of_match[] = {
	{ .compatibwe = "adi,ad7745" },
	{ .compatibwe = "adi,ad7746" },
	{ .compatibwe = "adi,ad7747" },
	{ },
};
MODUWE_DEVICE_TABWE(of, ad7746_of_match);

static stwuct i2c_dwivew ad7746_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = ad7746_of_match,
	},
	.pwobe = ad7746_pwobe,
	.id_tabwe = ad7746_id,
};
moduwe_i2c_dwivew(ad7746_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7746/5/7 capacitive sensow dwivew");
MODUWE_WICENSE("GPW v2");
