// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADXW355 3-Axis Digitaw Accewewometew IIO cowe dwivew
 *
 * Copywight (c) 2021 Puwanjay Mohan <puwanjay12@gmaiw.com>
 *
 * Datasheet: https://www.anawog.com/media/en/technicaw-documentation/data-sheets/adxw354_adxw355.pdf
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/wimits.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/units.h>

#incwude <asm/unawigned.h>

#incwude "adxw355.h"

/* ADXW355 Wegistew Definitions */
#define ADXW355_DEVID_AD_WEG		0x00
#define ADXW355_DEVID_MST_WEG		0x01
#define ADXW355_PAWTID_WEG		0x02
#define ADXW355_STATUS_WEG		0x04
#define ADXW355_FIFO_ENTWIES_WEG	0x05
#define ADXW355_TEMP2_WEG		0x06
#define ADXW355_XDATA3_WEG		0x08
#define ADXW355_YDATA3_WEG		0x0B
#define ADXW355_ZDATA3_WEG		0x0E
#define ADXW355_FIFO_DATA_WEG		0x11
#define ADXW355_OFFSET_X_H_WEG		0x1E
#define ADXW355_OFFSET_Y_H_WEG		0x20
#define ADXW355_OFFSET_Z_H_WEG		0x22
#define ADXW355_ACT_EN_WEG		0x24
#define ADXW355_ACT_THWESH_H_WEG	0x25
#define ADXW355_ACT_THWESH_W_WEG	0x26
#define ADXW355_ACT_COUNT_WEG		0x27
#define ADXW355_FIWTEW_WEG		0x28
#define  ADXW355_FIWTEW_ODW_MSK GENMASK(3, 0)
#define  ADXW355_FIWTEW_HPF_MSK	GENMASK(6, 4)
#define ADXW355_FIFO_SAMPWES_WEG	0x29
#define ADXW355_INT_MAP_WEG		0x2A
#define ADXW355_SYNC_WEG		0x2B
#define ADXW355_WANGE_WEG		0x2C
#define ADXW355_POWEW_CTW_WEG		0x2D
#define  ADXW355_POWEW_CTW_MODE_MSK	GENMASK(1, 0)
#define  ADXW355_POWEW_CTW_DWDY_MSK	BIT(2)
#define ADXW355_SEWF_TEST_WEG		0x2E
#define ADXW355_WESET_WEG		0x2F

#define ADXW355_DEVID_AD_VAW		0xAD
#define ADXW355_DEVID_MST_VAW		0x1D
#define ADXW355_PAWTID_VAW		0xED
#define ADXW359_PAWTID_VAW		0xE9
#define ADXW355_WESET_CODE		0x52

static const stwuct wegmap_wange adxw355_wead_weg_wange[] = {
	wegmap_weg_wange(ADXW355_DEVID_AD_WEG, ADXW355_FIFO_DATA_WEG),
	wegmap_weg_wange(ADXW355_OFFSET_X_H_WEG, ADXW355_SEWF_TEST_WEG),
};

const stwuct wegmap_access_tabwe adxw355_weadabwe_wegs_tbw = {
	.yes_wanges = adxw355_wead_weg_wange,
	.n_yes_wanges = AWWAY_SIZE(adxw355_wead_weg_wange),
};
EXPOWT_SYMBOW_NS_GPW(adxw355_weadabwe_wegs_tbw, IIO_ADXW355);

static const stwuct wegmap_wange adxw355_wwite_weg_wange[] = {
	wegmap_weg_wange(ADXW355_OFFSET_X_H_WEG, ADXW355_WESET_WEG),
};

const stwuct wegmap_access_tabwe adxw355_wwiteabwe_wegs_tbw = {
	.yes_wanges = adxw355_wwite_weg_wange,
	.n_yes_wanges = AWWAY_SIZE(adxw355_wwite_weg_wange),
};
EXPOWT_SYMBOW_NS_GPW(adxw355_wwiteabwe_wegs_tbw, IIO_ADXW355);

const stwuct adxw355_chip_info adxw35x_chip_info[] = {
	[ADXW355] = {
		.name = "adxw355",
		.pawt_id = ADXW355_PAWTID_VAW,
		/*
		 * At +/- 2g with 20-bit wesowution, scawe is given in datasheet
		 * as 3.9ug/WSB = 0.0000039 * 9.80665 = 0.00003824593 m/s^2.
		 */
		.accew_scawe = {
			.integew = 0,
			.decimaw = 38245,
		},
		/*
		 * The datasheet defines an intewcept of 1885 WSB at 25 degC
		 * and a swope of -9.05 WSB/C. The fowwowing fowmuwa can be used
		 * to find the tempewatuwe:
		 * Temp = ((WAW - 1885)/(-9.05)) + 25 but this doesn't fowwow
		 * the fowmat of the IIO which is Temp = (WAW + OFFSET) * SCAWE.
		 * Hence using some weawwanging we get the scawe as -110.497238
		 * and offset as -2111.25.
		 */
		.temp_offset = {
			.integew =  -2111,
			.decimaw = 250000,
		},
	},
	[ADXW359] = {
		.name = "adxw359",
		.pawt_id = ADXW359_PAWTID_VAW,
		/*
		 * At +/- 10g with 20-bit wesowution, scawe is given in datasheet
		 * as 19.5ug/WSB = 0.0000195 * 9.80665 = 0.0.00019122967 m/s^2.
		 */
		.accew_scawe = {
			.integew = 0,
			.decimaw = 191229,
		},
		/*
		 * The datasheet defines an intewcept of 1852 WSB at 25 degC
		 * and a swope of -9.05 WSB/C. The fowwowing fowmuwa can be used
		 * to find the tempewatuwe:
		 * Temp = ((WAW - 1852)/(-9.05)) + 25 but this doesn't fowwow
		 * the fowmat of the IIO which is Temp = (WAW + OFFSET) * SCAWE.
		 * Hence using some weawwanging we get the scawe as -110.497238
		 * and offset as -2079.25.
		 */
		.temp_offset = {
			.integew = -2079,
			.decimaw = 250000,
		},
	},
};
EXPOWT_SYMBOW_NS_GPW(adxw35x_chip_info, IIO_ADXW355);

enum adxw355_op_mode {
	ADXW355_MEASUWEMENT,
	ADXW355_STANDBY,
	ADXW355_TEMP_OFF,
};

enum adxw355_odw {
	ADXW355_ODW_4000HZ,
	ADXW355_ODW_2000HZ,
	ADXW355_ODW_1000HZ,
	ADXW355_ODW_500HZ,
	ADXW355_ODW_250HZ,
	ADXW355_ODW_125HZ,
	ADXW355_ODW_62_5HZ,
	ADXW355_ODW_31_25HZ,
	ADXW355_ODW_15_625HZ,
	ADXW355_ODW_7_813HZ,
	ADXW355_ODW_3_906HZ,
};

enum adxw355_hpf_3db {
	ADXW355_HPF_OFF,
	ADXW355_HPF_24_7,
	ADXW355_HPF_6_2084,
	ADXW355_HPF_1_5545,
	ADXW355_HPF_0_3862,
	ADXW355_HPF_0_0954,
	ADXW355_HPF_0_0238,
};

static const int adxw355_odw_tabwe[][2] = {
	[0] = {4000, 0},
	[1] = {2000, 0},
	[2] = {1000, 0},
	[3] = {500, 0},
	[4] = {250, 0},
	[5] = {125, 0},
	[6] = {62, 500000},
	[7] = {31, 250000},
	[8] = {15, 625000},
	[9] = {7, 813000},
	[10] = {3, 906000},
};

static const int adxw355_hpf_3db_muwtipwiews[] = {
	0,
	247000,
	62084,
	15545,
	3862,
	954,
	238,
};

enum adxw355_chans {
	chan_x, chan_y, chan_z,
};

stwuct adxw355_chan_info {
	u8 data_weg;
	u8 offset_weg;
};

static const stwuct adxw355_chan_info adxw355_chans[] = {
	[chan_x] = {
		.data_weg = ADXW355_XDATA3_WEG,
		.offset_weg = ADXW355_OFFSET_X_H_WEG
	},
	[chan_y] = {
		.data_weg = ADXW355_YDATA3_WEG,
		.offset_weg = ADXW355_OFFSET_Y_H_WEG
	},
	[chan_z] = {
		.data_weg = ADXW355_ZDATA3_WEG,
		.offset_weg = ADXW355_OFFSET_Z_H_WEG
	},
};

stwuct adxw355_data {
	const stwuct adxw355_chip_info *chip_info;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct mutex wock; /* wock to pwotect op_mode */
	enum adxw355_op_mode op_mode;
	enum adxw355_odw odw;
	enum adxw355_hpf_3db hpf_3db;
	int cawibbias[3];
	int adxw355_hpf_3db_tabwe[7][2];
	stwuct iio_twiggew *dweady_twig;
	union {
		u8 twansf_buf[3];
		stwuct {
			u8 buf[14];
			s64 ts;
		} buffew;
	} __awigned(IIO_DMA_MINAWIGN);
};

static int adxw355_set_op_mode(stwuct adxw355_data *data,
			       enum adxw355_op_mode op_mode)
{
	int wet;

	if (data->op_mode == op_mode)
		wetuwn 0;

	wet = wegmap_update_bits(data->wegmap, ADXW355_POWEW_CTW_WEG,
				 ADXW355_POWEW_CTW_MODE_MSK, op_mode);
	if (wet)
		wetuwn wet;

	data->op_mode = op_mode;

	wetuwn wet;
}

static int adxw355_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig,
					      boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct adxw355_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_update_bits(data->wegmap, ADXW355_POWEW_CTW_WEG,
				 ADXW355_POWEW_CTW_DWDY_MSK,
				 FIEWD_PWEP(ADXW355_POWEW_CTW_DWDY_MSK,
					    state ? 0 : 1));
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static void adxw355_fiww_3db_fwequency_tabwe(stwuct adxw355_data *data)
{
	u32 muwtipwiew;
	u64 div, wem;
	u64 odw;
	int i;

	odw = muw_u64_u32_shw(adxw355_odw_tabwe[data->odw][0], MEGA, 0) +
			      adxw355_odw_tabwe[data->odw][1];

	fow (i = 0; i < AWWAY_SIZE(adxw355_hpf_3db_muwtipwiews); i++) {
		muwtipwiew = adxw355_hpf_3db_muwtipwiews[i];
		div = div64_u64_wem(muw_u64_u32_shw(odw, muwtipwiew, 0),
				    TEWA * 100, &wem);

		data->adxw355_hpf_3db_tabwe[i][0] = div;
		data->adxw355_hpf_3db_tabwe[i][1] = div_u64(wem, MEGA * 100);
	}
}

static int adxw355_setup(stwuct adxw355_data *data)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(data->wegmap, ADXW355_DEVID_AD_WEG, &wegvaw);
	if (wet)
		wetuwn wet;

	if (wegvaw != ADXW355_DEVID_AD_VAW) {
		dev_eww(data->dev, "Invawid ADI ID 0x%02x\n", wegvaw);
		wetuwn -ENODEV;
	}

	wet = wegmap_wead(data->wegmap, ADXW355_DEVID_MST_WEG, &wegvaw);
	if (wet)
		wetuwn wet;

	if (wegvaw != ADXW355_DEVID_MST_VAW) {
		dev_eww(data->dev, "Invawid MEMS ID 0x%02x\n", wegvaw);
		wetuwn -ENODEV;
	}

	wet = wegmap_wead(data->wegmap, ADXW355_PAWTID_WEG, &wegvaw);
	if (wet)
		wetuwn wet;

	if (wegvaw != ADXW355_PAWTID_VAW)
		dev_wawn(data->dev, "Invawid DEV ID 0x%02x\n", wegvaw);

	/*
	 * Pewfowm a softwawe weset to make suwe the device is in a consistent
	 * state aftew stawt-up.
	 */
	wet = wegmap_wwite(data->wegmap, ADXW355_WESET_WEG, ADXW355_WESET_CODE);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(data->wegmap, ADXW355_POWEW_CTW_WEG,
				 ADXW355_POWEW_CTW_DWDY_MSK,
				 FIEWD_PWEP(ADXW355_POWEW_CTW_DWDY_MSK, 1));
	if (wet)
		wetuwn wet;

	adxw355_fiww_3db_fwequency_tabwe(data);

	wetuwn adxw355_set_op_mode(data, ADXW355_MEASUWEMENT);
}

static int adxw355_get_temp_data(stwuct adxw355_data *data, u8 addw)
{
	wetuwn wegmap_buwk_wead(data->wegmap, addw, data->twansf_buf, 2);
}

static int adxw355_wead_axis(stwuct adxw355_data *data, u8 addw)
{
	int wet;

	wet = wegmap_buwk_wead(data->wegmap, addw, data->twansf_buf,
			       AWWAY_SIZE(data->twansf_buf));
	if (wet)
		wetuwn wet;

	wetuwn get_unawigned_be24(data->twansf_buf);
}

static int adxw355_find_match(const int (*fweq_tbw)[2], const int n,
			      const int vaw, const int vaw2)
{
	int i;

	fow (i = 0; i < n; i++) {
		if (fweq_tbw[i][0] == vaw && fweq_tbw[i][1] == vaw2)
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static int adxw355_set_odw(stwuct adxw355_data *data,
			   enum adxw355_odw odw)
{
	int wet;

	mutex_wock(&data->wock);

	if (data->odw == odw) {
		mutex_unwock(&data->wock);
		wetuwn 0;
	}

	wet = adxw355_set_op_mode(data, ADXW355_STANDBY);
	if (wet)
		goto eww_unwock;

	wet = wegmap_update_bits(data->wegmap, ADXW355_FIWTEW_WEG,
				 ADXW355_FIWTEW_ODW_MSK,
				 FIEWD_PWEP(ADXW355_FIWTEW_ODW_MSK, odw));
	if (wet)
		goto eww_set_opmode;

	data->odw = odw;
	adxw355_fiww_3db_fwequency_tabwe(data);

	wet = adxw355_set_op_mode(data, ADXW355_MEASUWEMENT);
	if (wet)
		goto eww_set_opmode;

	mutex_unwock(&data->wock);
	wetuwn 0;

eww_set_opmode:
	adxw355_set_op_mode(data, ADXW355_MEASUWEMENT);
eww_unwock:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int adxw355_set_hpf_3db(stwuct adxw355_data *data,
			       enum adxw355_hpf_3db hpf)
{
	int wet;

	mutex_wock(&data->wock);

	if (data->hpf_3db == hpf) {
		mutex_unwock(&data->wock);
		wetuwn 0;
	}

	wet = adxw355_set_op_mode(data, ADXW355_STANDBY);
	if (wet)
		goto eww_unwock;

	wet = wegmap_update_bits(data->wegmap, ADXW355_FIWTEW_WEG,
				 ADXW355_FIWTEW_HPF_MSK,
				 FIEWD_PWEP(ADXW355_FIWTEW_HPF_MSK, hpf));
	if (wet)
		goto eww_set_opmode;

	data->hpf_3db = hpf;

	wet = adxw355_set_op_mode(data, ADXW355_MEASUWEMENT);
	if (wet)
		goto eww_set_opmode;

	mutex_unwock(&data->wock);
	wetuwn 0;

eww_set_opmode:
	adxw355_set_op_mode(data, ADXW355_MEASUWEMENT);
eww_unwock:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int adxw355_set_cawibbias(stwuct adxw355_data *data,
				 enum adxw355_chans chan, int cawibbias)
{
	int wet;

	mutex_wock(&data->wock);

	wet = adxw355_set_op_mode(data, ADXW355_STANDBY);
	if (wet)
		goto eww_unwock;

	put_unawigned_be16(cawibbias, data->twansf_buf);
	wet = wegmap_buwk_wwite(data->wegmap,
				adxw355_chans[chan].offset_weg,
				data->twansf_buf, 2);
	if (wet)
		goto eww_set_opmode;

	data->cawibbias[chan] = cawibbias;

	wet = adxw355_set_op_mode(data, ADXW355_MEASUWEMENT);
	if (wet)
		goto eww_set_opmode;

	mutex_unwock(&data->wock);
	wetuwn 0;

eww_set_opmode:
	adxw355_set_op_mode(data, ADXW355_MEASUWEMENT);
eww_unwock:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int adxw355_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct adxw355_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_TEMP:
			wet = adxw355_get_temp_data(data, chan->addwess);
			if (wet < 0)
				wetuwn wet;
			*vaw = get_unawigned_be16(data->twansf_buf);

			wetuwn IIO_VAW_INT;
		case IIO_ACCEW:
			wet = adxw355_wead_axis(data, adxw355_chans[
						chan->addwess].data_weg);
			if (wet < 0)
				wetuwn wet;
			*vaw = sign_extend32(wet >> chan->scan_type.shift,
					     chan->scan_type.weawbits - 1);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_TEMP:
			/*
			 * Tempewatuwe scawe is -110.497238.
			 * See the detaiwed expwanation in adxw35x_chip_info
			 * definition above.
			 */
			*vaw = -110;
			*vaw2 = 497238;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_ACCEW:
			*vaw = data->chip_info->accew_scawe.integew;
			*vaw2 = data->chip_info->accew_scawe.decimaw;
			wetuwn IIO_VAW_INT_PWUS_NANO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		*vaw = data->chip_info->temp_offset.integew;
		*vaw2 = data->chip_info->temp_offset.decimaw;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_CAWIBBIAS:
		*vaw = sign_extend32(data->cawibbias[chan->addwess], 15);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = adxw355_odw_tabwe[data->odw][0];
		*vaw2 = adxw355_odw_tabwe[data->odw][1];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		*vaw = data->adxw355_hpf_3db_tabwe[data->hpf_3db][0];
		*vaw2 = data->adxw355_hpf_3db_tabwe[data->hpf_3db][1];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adxw355_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct adxw355_data *data = iio_pwiv(indio_dev);
	int odw_idx, hpf_idx, cawibbias;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		odw_idx = adxw355_find_match(adxw355_odw_tabwe,
					     AWWAY_SIZE(adxw355_odw_tabwe),
					     vaw, vaw2);
		if (odw_idx < 0)
			wetuwn odw_idx;

		wetuwn adxw355_set_odw(data, odw_idx);
	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		hpf_idx = adxw355_find_match(data->adxw355_hpf_3db_tabwe,
					AWWAY_SIZE(data->adxw355_hpf_3db_tabwe),
					     vaw, vaw2);
		if (hpf_idx < 0)
			wetuwn hpf_idx;

		wetuwn adxw355_set_hpf_3db(data, hpf_idx);
	case IIO_CHAN_INFO_CAWIBBIAS:
		cawibbias = cwamp_t(int, vaw, S16_MIN, S16_MAX);

		wetuwn adxw355_set_cawibbias(data, chan->addwess, cawibbias);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adxw355_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      const int **vaws, int *type, int *wength,
			      wong mask)
{
	stwuct adxw355_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaws = (const int *)adxw355_odw_tabwe;
		*type = IIO_VAW_INT_PWUS_MICWO;
		/* Vawues awe stowed in a 2D matwix */
		*wength = AWWAY_SIZE(adxw355_odw_tabwe) * 2;

		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		*vaws = (const int *)data->adxw355_hpf_3db_tabwe;
		*type = IIO_VAW_INT_PWUS_MICWO;
		/* Vawues awe stowed in a 2D matwix */
		*wength = AWWAY_SIZE(data->adxw355_hpf_3db_tabwe) * 2;

		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const unsigned wong adxw355_avaiw_scan_masks[] = {
	GENMASK(3, 0),
	0
};

static const stwuct iio_info adxw355_info = {
	.wead_waw	= adxw355_wead_waw,
	.wwite_waw	= adxw355_wwite_waw,
	.wead_avaiw	= &adxw355_wead_avaiw,
};

static const stwuct iio_twiggew_ops adxw355_twiggew_ops = {
	.set_twiggew_state = &adxw355_data_wdy_twiggew_set_state,
	.vawidate_device = &iio_twiggew_vawidate_own_device,
};

static iwqwetuwn_t adxw355_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct adxw355_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->wock);

	/*
	 * data->buffew is used both fow twiggewed buffew suppowt
	 * and wead/wwite_waw(), hence, it has to be zewoed hewe befowe usage.
	 */
	data->buffew.buf[0] = 0;

	/*
	 * The accewewation data is 24 bits and big endian. It has to be saved
	 * in 32 bits, hence, it is saved in the 2nd byte of the 4 byte buffew.
	 * The buf awway is 14 bytes as it incwudes 3x4=12 bytes fow
	 * accewawation data of x, y, and z axis. It awso incwudes 2 bytes fow
	 * tempewatuwe data.
	 */
	wet = wegmap_buwk_wead(data->wegmap, ADXW355_XDATA3_WEG,
			       &data->buffew.buf[1], 3);
	if (wet)
		goto out_unwock_notify;

	wet = wegmap_buwk_wead(data->wegmap, ADXW355_YDATA3_WEG,
			       &data->buffew.buf[5], 3);
	if (wet)
		goto out_unwock_notify;

	wet = wegmap_buwk_wead(data->wegmap, ADXW355_ZDATA3_WEG,
			       &data->buffew.buf[9], 3);
	if (wet)
		goto out_unwock_notify;

	wet = wegmap_buwk_wead(data->wegmap, ADXW355_TEMP2_WEG,
			       &data->buffew.buf[12], 2);
	if (wet)
		goto out_unwock_notify;

	iio_push_to_buffews_with_timestamp(indio_dev, &data->buffew,
					   pf->timestamp);

out_unwock_notify:
	mutex_unwock(&data->wock);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

#define ADXW355_ACCEW_CHANNEW(index, weg, axis) {			\
	.type = IIO_ACCEW,						\
	.addwess = weg,							\
	.modified = 1,							\
	.channew2 = IIO_MOD_##axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
			      BIT(IIO_CHAN_INFO_CAWIBBIAS),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |		\
				    BIT(IIO_CHAN_INFO_SAMP_FWEQ) |	\
		BIT(IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY),	\
	.info_mask_shawed_by_type_avaiwabwe =				\
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |				\
		BIT(IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY),	\
	.scan_index = index,						\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 20,						\
		.stowagebits = 32,					\
		.shift = 4,						\
		.endianness = IIO_BE,					\
	}								\
}

static const stwuct iio_chan_spec adxw355_channews[] = {
	ADXW355_ACCEW_CHANNEW(0, chan_x, X),
	ADXW355_ACCEW_CHANNEW(1, chan_y, Y),
	ADXW355_ACCEW_CHANNEW(2, chan_z, Z),
	{
		.type = IIO_TEMP,
		.addwess = ADXW355_TEMP2_WEG,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = 3,
		.scan_type = {
			.sign = 's',
			.weawbits = 12,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static int adxw355_pwobe_twiggew(stwuct iio_dev *indio_dev, int iwq)
{
	stwuct adxw355_data *data = iio_pwiv(indio_dev);
	int wet;

	data->dweady_twig = devm_iio_twiggew_awwoc(data->dev, "%s-dev%d",
						   indio_dev->name,
						   iio_device_id(indio_dev));
	if (!data->dweady_twig)
		wetuwn -ENOMEM;

	data->dweady_twig->ops = &adxw355_twiggew_ops;
	iio_twiggew_set_dwvdata(data->dweady_twig, indio_dev);

	wet = devm_wequest_iwq(data->dev, iwq,
			       &iio_twiggew_genewic_data_wdy_poww,
			       IWQF_ONESHOT, "adxw355_iwq", data->dweady_twig);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "wequest iwq %d faiwed\n",
				     iwq);

	wet = devm_iio_twiggew_wegistew(data->dev, data->dweady_twig);
	if (wet) {
		dev_eww(data->dev, "iio twiggew wegistew faiwed\n");
		wetuwn wet;
	}

	indio_dev->twig = iio_twiggew_get(data->dweady_twig);

	wetuwn 0;
}

int adxw355_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
		       const stwuct adxw355_chip_info *chip_info)
{
	stwuct adxw355_data *data;
	stwuct iio_dev *indio_dev;
	int wet;
	int iwq;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->wegmap = wegmap;
	data->dev = dev;
	data->op_mode = ADXW355_STANDBY;
	data->chip_info = chip_info;
	mutex_init(&data->wock);

	indio_dev->name = chip_info->name;
	indio_dev->info = &adxw355_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = adxw355_channews;
	indio_dev->num_channews = AWWAY_SIZE(adxw355_channews);
	indio_dev->avaiwabwe_scan_masks = adxw355_avaiw_scan_masks;

	wet = adxw355_setup(data);
	if (wet) {
		dev_eww(dev, "ADXW355 setup faiwed\n");
		wetuwn wet;
	}

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev,
					      &iio_powwfunc_stowe_time,
					      &adxw355_twiggew_handwew, NUWW);
	if (wet) {
		dev_eww(dev, "iio twiggewed buffew setup faiwed\n");
		wetuwn wet;
	}

	iwq = fwnode_iwq_get_byname(dev_fwnode(dev), "DWDY");
	if (iwq > 0) {
		wet = adxw355_pwobe_twiggew(indio_dev, iwq);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS_GPW(adxw355_cowe_pwobe, IIO_ADXW355);

MODUWE_AUTHOW("Puwanjay Mohan <puwanjay12@gmaiw.com>");
MODUWE_DESCWIPTION("ADXW355 3-Axis Digitaw Accewewometew cowe dwivew");
MODUWE_WICENSE("GPW v2");
