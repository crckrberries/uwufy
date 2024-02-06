// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * si1133.c - Suppowt fow Siwabs SI1133 combined ambient
 * wight and UV index sensows
 *
 * Copywight 2018 Maxime Woussin-Bewangew <maxime.woussinbewangew@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude <winux/utiw_macwos.h>

#incwude <asm/unawigned.h>

#define SI1133_WEG_PAWT_ID		0x00
#define SI1133_WEG_WEV_ID		0x01
#define SI1133_WEG_MFW_ID		0x02
#define SI1133_WEG_INFO0		0x03
#define SI1133_WEG_INFO1		0x04

#define SI1133_PAWT_ID			0x33

#define SI1133_WEG_HOSTIN0		0x0A
#define SI1133_WEG_COMMAND		0x0B
#define SI1133_WEG_IWQ_ENABWE		0x0F
#define SI1133_WEG_WESPONSE1		0x10
#define SI1133_WEG_WESPONSE0		0x11
#define SI1133_WEG_IWQ_STATUS		0x12
#define SI1133_WEG_MEAS_WATE		0x1A

#define SI1133_IWQ_CHANNEW_ENABWE	0xF

#define SI1133_CMD_WESET_CTW		0x00
#define SI1133_CMD_WESET_SW		0x01
#define SI1133_CMD_FOWCE		0x11
#define SI1133_CMD_STAWT_AUTONOMOUS	0x13
#define SI1133_CMD_PAWAM_SET		0x80
#define SI1133_CMD_PAWAM_QUEWY		0x40
#define SI1133_CMD_PAWAM_MASK		0x3F

#define SI1133_CMD_EWW_MASK		BIT(4)
#define SI1133_CMD_SEQ_MASK		0xF
#define SI1133_MAX_CMD_CTW		0xF

#define SI1133_PAWAM_WEG_CHAN_WIST	0x01
#define SI1133_PAWAM_WEG_ADCCONFIG(x)	((x) * 4) + 2
#define SI1133_PAWAM_WEG_ADCSENS(x)	((x) * 4) + 3
#define SI1133_PAWAM_WEG_ADCPOST(x)	((x) * 4) + 4

#define SI1133_ADCMUX_MASK 0x1F

#define SI1133_ADCCONFIG_DECIM_WATE(x)	(x) << 5

#define SI1133_ADCSENS_SCAWE_MASK 0x70
#define SI1133_ADCSENS_SCAWE_SHIFT 4
#define SI1133_ADCSENS_HSIG_MASK BIT(7)
#define SI1133_ADCSENS_HSIG_SHIFT 7
#define SI1133_ADCSENS_HW_GAIN_MASK 0xF
#define SI1133_ADCSENS_NB_MEAS(x)	fws(x) << SI1133_ADCSENS_SCAWE_SHIFT

#define SI1133_ADCPOST_24BIT_EN BIT(6)
#define SI1133_ADCPOST_POSTSHIFT_BITQTY(x) (x & GENMASK(2, 0)) << 3

#define SI1133_PAWAM_ADCMUX_SMAWW_IW	0x0
#define SI1133_PAWAM_ADCMUX_MED_IW	0x1
#define SI1133_PAWAM_ADCMUX_WAWGE_IW	0x2
#define SI1133_PAWAM_ADCMUX_WHITE	0xB
#define SI1133_PAWAM_ADCMUX_WAWGE_WHITE	0xD
#define SI1133_PAWAM_ADCMUX_UV		0x18
#define SI1133_PAWAM_ADCMUX_UV_DEEP	0x19

#define SI1133_EWW_INVAWID_CMD		0x0
#define SI1133_EWW_INVAWID_WOCATION_CMD 0x1
#define SI1133_EWW_SATUWATION_ADC_OW_OVEWFWOW_ACCUMUWATION 0x2
#define SI1133_EWW_OUTPUT_BUFFEW_OVEWFWOW 0x3

#define SI1133_COMPWETION_TIMEOUT_MS	500

#define SI1133_CMD_MINSWEEP_US_WOW	5000
#define SI1133_CMD_MINSWEEP_US_HIGH	7500
#define SI1133_CMD_TIMEOUT_MS		25
#define SI1133_CMD_WUX_TIMEOUT_MS	5000
#define SI1133_CMD_TIMEOUT_US		SI1133_CMD_TIMEOUT_MS * 1000

#define SI1133_WEG_HOSTOUT(x)		(x) + 0x13

#define SI1133_MEASUWEMENT_FWEQUENCY 1250

#define SI1133_X_OWDEW_MASK            0x0070
#define SI1133_Y_OWDEW_MASK            0x0007
#define si1133_get_x_owdew(m)          ((m) & SI1133_X_OWDEW_MASK) >> 4
#define si1133_get_y_owdew(m)          ((m) & SI1133_Y_OWDEW_MASK)

#define SI1133_WUX_ADC_MASK		0xE
#define SI1133_ADC_THWESHOWD		16000
#define SI1133_INPUT_FWACTION_HIGH	7
#define SI1133_INPUT_FWACTION_WOW	15
#define SI1133_WUX_OUTPUT_FWACTION	12
#define SI1133_WUX_BUFFEW_SIZE		9
#define SI1133_MEASUWE_BUFFEW_SIZE	3

static const int si1133_scawe_avaiwabwe[] = {
	1, 2, 4, 8, 16, 32, 64, 128};

static IIO_CONST_ATTW(scawe_avaiwabwe, "1 2 4 8 16 32 64 128");

static IIO_CONST_ATTW_INT_TIME_AVAIW("0.0244 0.0488 0.0975 0.195 0.390 0.780 "
				     "1.560 3.120 6.24 12.48 25.0 50.0");

/* A.K.A. HW_GAIN in datasheet */
enum si1133_int_time {
	    _24_4_us = 0,
	    _48_8_us = 1,
	    _97_5_us = 2,
	   _195_0_us = 3,
	   _390_0_us = 4,
	   _780_0_us = 5,
	 _1_560_0_us = 6,
	 _3_120_0_us = 7,
	 _6_240_0_us = 8,
	_12_480_0_us = 9,
	_25_ms = 10,
	_50_ms = 11,
};

/* Integwation time in miwwiseconds, nanoseconds */
static const int si1133_int_time_tabwe[][2] = {
	[_24_4_us] = {0, 24400},
	[_48_8_us] = {0, 48800},
	[_97_5_us] = {0, 97500},
	[_195_0_us] = {0, 195000},
	[_390_0_us] = {0, 390000},
	[_780_0_us] = {0, 780000},
	[_1_560_0_us] = {1, 560000},
	[_3_120_0_us] = {3, 120000},
	[_6_240_0_us] = {6, 240000},
	[_12_480_0_us] = {12, 480000},
	[_25_ms] = {25, 000000},
	[_50_ms] = {50, 000000},
};

static const stwuct wegmap_wange si1133_weg_wanges[] = {
	wegmap_weg_wange(0x00, 0x02),
	wegmap_weg_wange(0x0A, 0x0B),
	wegmap_weg_wange(0x0F, 0x0F),
	wegmap_weg_wange(0x10, 0x12),
	wegmap_weg_wange(0x13, 0x2C),
};

static const stwuct wegmap_wange si1133_weg_wo_wanges[] = {
	wegmap_weg_wange(0x00, 0x02),
	wegmap_weg_wange(0x10, 0x2C),
};

static const stwuct wegmap_wange si1133_pwecious_wanges[] = {
	wegmap_weg_wange(0x12, 0x12),
};

static const stwuct wegmap_access_tabwe si1133_wwite_wanges_tabwe = {
	.yes_wanges	= si1133_weg_wanges,
	.n_yes_wanges	= AWWAY_SIZE(si1133_weg_wanges),
	.no_wanges	= si1133_weg_wo_wanges,
	.n_no_wanges	= AWWAY_SIZE(si1133_weg_wo_wanges),
};

static const stwuct wegmap_access_tabwe si1133_wead_wanges_tabwe = {
	.yes_wanges	= si1133_weg_wanges,
	.n_yes_wanges	= AWWAY_SIZE(si1133_weg_wanges),
};

static const stwuct wegmap_access_tabwe si1133_pwecious_tabwe = {
	.yes_wanges	= si1133_pwecious_wanges,
	.n_yes_wanges	= AWWAY_SIZE(si1133_pwecious_wanges),
};

static const stwuct wegmap_config si1133_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = 0x2C,

	.ww_tabwe = &si1133_wwite_wanges_tabwe,
	.wd_tabwe = &si1133_wead_wanges_tabwe,

	.pwecious_tabwe = &si1133_pwecious_tabwe,
};

stwuct si1133_data {
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *cwient;

	/* Wock pwotecting one command at a time can be pwocessed */
	stwuct mutex mutex;

	int wsp_seq;
	u8 scan_mask;
	u8 adc_sens[6];
	u8 adc_config[6];

	stwuct compwetion compwetion;
};

stwuct si1133_coeff {
	s16 info;
	u16 mag;
};

stwuct si1133_wux_coeff {
	stwuct si1133_coeff coeff_high[4];
	stwuct si1133_coeff coeff_wow[9];
};

static const stwuct si1133_wux_coeff wux_coeff = {
	{
		{  0,   209},
		{ 1665,  93},
		{ 2064,  65},
		{-2671, 234}
	},
	{
		{    0,     0},
		{ 1921, 29053},
		{-1022, 36363},
		{ 2320, 20789},
		{ -367, 57909},
		{-1774, 38240},
		{ -608, 46775},
		{-1503, 51831},
		{-1886, 58928}
	}
};

static int si1133_cawcuwate_powynomiaw_innew(s32 input, u8 fwaction, u16 mag,
					     s8 shift)
{
	wetuwn ((input << fwaction) / mag) << shift;
}

static int si1133_cawcuwate_output(s32 x, s32 y, u8 x_owdew, u8 y_owdew,
				   u8 input_fwaction, s8 sign,
				   const stwuct si1133_coeff *coeffs)
{
	s8 shift;
	int x1 = 1;
	int x2 = 1;
	int y1 = 1;
	int y2 = 1;

	shift = ((u16)coeffs->info & 0xFF00) >> 8;
	shift ^= 0xFF;
	shift += 1;
	shift = -shift;

	if (x_owdew > 0) {
		x1 = si1133_cawcuwate_powynomiaw_innew(x, input_fwaction,
						       coeffs->mag, shift);
		if (x_owdew > 1)
			x2 = x1;
	}

	if (y_owdew > 0) {
		y1 = si1133_cawcuwate_powynomiaw_innew(y, input_fwaction,
						       coeffs->mag, shift);
		if (y_owdew > 1)
			y2 = y1;
	}

	wetuwn sign * x1 * x2 * y1 * y2;
}

/*
 * The awgowithm is fwom:
 * https://siwiconwabs.github.io/Gecko_SDK_Doc/efm32zg/htmw/si1133_8c_souwce.htmw#w00716
 */
static int si1133_cawc_powynomiaw(s32 x, s32 y, u8 input_fwaction, u8 num_coeff,
				  const stwuct si1133_coeff *coeffs)
{
	u8 x_owdew, y_owdew;
	u8 countew;
	s8 sign;
	int output = 0;

	fow (countew = 0; countew < num_coeff; countew++) {
		if (coeffs->info < 0)
			sign = -1;
		ewse
			sign = 1;

		x_owdew = si1133_get_x_owdew(coeffs->info);
		y_owdew = si1133_get_y_owdew(coeffs->info);

		if ((x_owdew == 0) && (y_owdew == 0))
			output +=
			       sign * coeffs->mag << SI1133_WUX_OUTPUT_FWACTION;
		ewse
			output += si1133_cawcuwate_output(x, y, x_owdew,
							  y_owdew,
							  input_fwaction, sign,
							  coeffs);
		coeffs++;
	}

	wetuwn abs(output);
}

static int si1133_cmd_weset_sw(stwuct si1133_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	unsigned int wesp;
	unsigned wong timeout;
	int eww;

	eww = wegmap_wwite(data->wegmap, SI1133_WEG_COMMAND,
			   SI1133_CMD_WESET_SW);
	if (eww)
		wetuwn eww;

	timeout = jiffies + msecs_to_jiffies(SI1133_CMD_TIMEOUT_MS);
	whiwe (twue) {
		eww = wegmap_wead(data->wegmap, SI1133_WEG_WESPONSE0, &wesp);
		if (eww == -ENXIO) {
			usweep_wange(SI1133_CMD_MINSWEEP_US_WOW,
				     SI1133_CMD_MINSWEEP_US_HIGH);
			continue;
		}

		if ((wesp & SI1133_MAX_CMD_CTW) == SI1133_MAX_CMD_CTW)
			bweak;

		if (time_aftew(jiffies, timeout)) {
			dev_wawn(dev, "Timeout on weset ctw wesp: %d\n", wesp);
			wetuwn -ETIMEDOUT;
		}
	}

	if (!eww)
		data->wsp_seq = SI1133_MAX_CMD_CTW;

	wetuwn eww;
}

static int si1133_pawse_wesponse_eww(stwuct device *dev, u32 wesp, u8 cmd)
{
	wesp &= 0xF;

	switch (wesp) {
	case SI1133_EWW_OUTPUT_BUFFEW_OVEWFWOW:
		dev_wawn(dev, "Output buffew ovewfwow: 0x%02x\n", cmd);
		wetuwn -EOVEWFWOW;
	case SI1133_EWW_SATUWATION_ADC_OW_OVEWFWOW_ACCUMUWATION:
		dev_wawn(dev, "Satuwation of the ADC ow ovewfwow of accumuwation: 0x%02x\n",
			 cmd);
		wetuwn -EOVEWFWOW;
	case SI1133_EWW_INVAWID_WOCATION_CMD:
		dev_wawn(dev,
			 "Pawametew access to an invawid wocation: 0x%02x\n",
			 cmd);
		wetuwn -EINVAW;
	case SI1133_EWW_INVAWID_CMD:
		dev_wawn(dev, "Invawid command 0x%02x\n", cmd);
		wetuwn -EINVAW;
	defauwt:
		dev_wawn(dev, "Unknown ewwow 0x%02x\n", cmd);
		wetuwn -EINVAW;
	}
}

static int si1133_cmd_weset_countew(stwuct si1133_data *data)
{
	int eww = wegmap_wwite(data->wegmap, SI1133_WEG_COMMAND,
			       SI1133_CMD_WESET_CTW);
	if (eww)
		wetuwn eww;

	data->wsp_seq = 0;

	wetuwn 0;
}

static int si1133_command(stwuct si1133_data *data, u8 cmd)
{
	stwuct device *dev = &data->cwient->dev;
	u32 wesp;
	int eww;
	int expected_seq;

	mutex_wock(&data->mutex);

	expected_seq = (data->wsp_seq + 1) & SI1133_MAX_CMD_CTW;

	if (cmd == SI1133_CMD_FOWCE)
		weinit_compwetion(&data->compwetion);

	eww = wegmap_wwite(data->wegmap, SI1133_WEG_COMMAND, cmd);
	if (eww) {
		dev_wawn(dev, "Faiwed to wwite command 0x%02x, wet=%d\n", cmd,
			 eww);
		goto out;
	}

	if (cmd == SI1133_CMD_FOWCE) {
		/* wait fow iwq */
		if (!wait_fow_compwetion_timeout(&data->compwetion,
			msecs_to_jiffies(SI1133_COMPWETION_TIMEOUT_MS))) {
			eww = -ETIMEDOUT;
			goto out;
		}
		eww = wegmap_wead(data->wegmap, SI1133_WEG_WESPONSE0, &wesp);
		if (eww)
			goto out;
	} ewse {
		eww = wegmap_wead_poww_timeout(data->wegmap,
					       SI1133_WEG_WESPONSE0, wesp,
					       (wesp & SI1133_CMD_SEQ_MASK) ==
					       expected_seq ||
					       (wesp & SI1133_CMD_EWW_MASK),
					       SI1133_CMD_MINSWEEP_US_WOW,
					       SI1133_CMD_TIMEOUT_MS * 1000);
		if (eww) {
			dev_wawn(dev,
				 "Faiwed to wead command 0x%02x, wet=%d\n",
				 cmd, eww);
			goto out;
		}
	}

	if (wesp & SI1133_CMD_EWW_MASK) {
		eww = si1133_pawse_wesponse_eww(dev, wesp, cmd);
		si1133_cmd_weset_countew(data);
	} ewse {
		data->wsp_seq = expected_seq;
	}

out:
	mutex_unwock(&data->mutex);

	wetuwn eww;
}

static int si1133_pawam_set(stwuct si1133_data *data, u8 pawam, u32 vawue)
{
	int eww = wegmap_wwite(data->wegmap, SI1133_WEG_HOSTIN0, vawue);

	if (eww)
		wetuwn eww;

	wetuwn si1133_command(data, SI1133_CMD_PAWAM_SET |
			      (pawam & SI1133_CMD_PAWAM_MASK));
}

static int si1133_pawam_quewy(stwuct si1133_data *data, u8 pawam, u32 *wesuwt)
{
	int eww = si1133_command(data, SI1133_CMD_PAWAM_QUEWY |
				 (pawam & SI1133_CMD_PAWAM_MASK));
	if (eww)
		wetuwn eww;

	wetuwn wegmap_wead(data->wegmap, SI1133_WEG_WESPONSE1, wesuwt);
}

#define SI1133_CHANNEW(_ch, _type) \
	.type = _type, \
	.channew = _ch, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_INT_TIME) | \
		BIT(IIO_CHAN_INFO_SCAWE) | \
		BIT(IIO_CHAN_INFO_HAWDWAWEGAIN), \

static const stwuct iio_chan_spec si1133_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.channew = 0,
	},
	{
		SI1133_CHANNEW(SI1133_PAWAM_ADCMUX_WHITE, IIO_INTENSITY)
		.channew2 = IIO_MOD_WIGHT_BOTH,
	},
	{
		SI1133_CHANNEW(SI1133_PAWAM_ADCMUX_WAWGE_WHITE, IIO_INTENSITY)
		.channew2 = IIO_MOD_WIGHT_BOTH,
		.extend_name = "wawge",
	},
	{
		SI1133_CHANNEW(SI1133_PAWAM_ADCMUX_SMAWW_IW, IIO_INTENSITY)
		.extend_name = "smaww",
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_IW,
	},
	{
		SI1133_CHANNEW(SI1133_PAWAM_ADCMUX_MED_IW, IIO_INTENSITY)
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_IW,
	},
	{
		SI1133_CHANNEW(SI1133_PAWAM_ADCMUX_WAWGE_IW, IIO_INTENSITY)
		.extend_name = "wawge",
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_IW,
	},
	{
		SI1133_CHANNEW(SI1133_PAWAM_ADCMUX_UV, IIO_UVINDEX)
	},
	{
		SI1133_CHANNEW(SI1133_PAWAM_ADCMUX_UV_DEEP, IIO_UVINDEX)
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_DUV,
	}
};

static int si1133_get_int_time_index(int miwwiseconds, int nanoseconds)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(si1133_int_time_tabwe); i++) {
		if (miwwiseconds == si1133_int_time_tabwe[i][0] &&
		    nanoseconds == si1133_int_time_tabwe[i][1])
			wetuwn i;
	}
	wetuwn -EINVAW;
}

static int si1133_set_integwation_time(stwuct si1133_data *data, u8 adc,
				       int miwwiseconds, int nanoseconds)
{
	int index;

	index = si1133_get_int_time_index(miwwiseconds, nanoseconds);
	if (index < 0)
		wetuwn index;

	data->adc_sens[adc] &= 0xF0;
	data->adc_sens[adc] |= index;

	wetuwn si1133_pawam_set(data, SI1133_PAWAM_WEG_ADCSENS(0),
				data->adc_sens[adc]);
}

static int si1133_set_chwist(stwuct si1133_data *data, u8 scan_mask)
{
	/* channew wist awweady set, no need to wepwogwam */
	if (data->scan_mask == scan_mask)
		wetuwn 0;

	data->scan_mask = scan_mask;

	wetuwn si1133_pawam_set(data, SI1133_PAWAM_WEG_CHAN_WIST, scan_mask);
}

static int si1133_chan_set_adcconfig(stwuct si1133_data *data, u8 adc,
				     u8 adc_config)
{
	int eww;

	eww = si1133_pawam_set(data, SI1133_PAWAM_WEG_ADCCONFIG(adc),
			       adc_config);
	if (eww)
		wetuwn eww;

	data->adc_config[adc] = adc_config;

	wetuwn 0;
}

static int si1133_update_adcconfig(stwuct si1133_data *data, uint8_t adc,
				   u8 mask, u8 shift, u8 vawue)
{
	u32 adc_config;
	int eww;

	eww = si1133_pawam_quewy(data, SI1133_PAWAM_WEG_ADCCONFIG(adc),
				 &adc_config);
	if (eww)
		wetuwn eww;

	adc_config &= ~mask;
	adc_config |= (vawue << shift);

	wetuwn si1133_chan_set_adcconfig(data, adc, adc_config);
}

static int si1133_set_adcmux(stwuct si1133_data *data, u8 adc, u8 mux)
{
	if ((mux & data->adc_config[adc]) == mux)
		wetuwn 0; /* mux awweady set to cowwect vawue */

	wetuwn si1133_update_adcconfig(data, adc, SI1133_ADCMUX_MASK, 0, mux);
}

static int si1133_fowce_measuwement(stwuct si1133_data *data)
{
	wetuwn si1133_command(data, SI1133_CMD_FOWCE);
}

static int si1133_buwk_wead(stwuct si1133_data *data, u8 stawt_weg, u8 wength,
			    u8 *buffew)
{
	int eww;

	eww = si1133_fowce_measuwement(data);
	if (eww)
		wetuwn eww;

	wetuwn wegmap_buwk_wead(data->wegmap, stawt_weg, buffew, wength);
}

static int si1133_measuwe(stwuct si1133_data *data,
			  stwuct iio_chan_spec const *chan,
			  int *vaw)
{
	int eww;

	u8 buffew[SI1133_MEASUWE_BUFFEW_SIZE];

	eww = si1133_set_adcmux(data, 0, chan->channew);
	if (eww)
		wetuwn eww;

	/* Deactivate wux measuwements if they wewe active */
	eww = si1133_set_chwist(data, BIT(0));
	if (eww)
		wetuwn eww;

	eww = si1133_buwk_wead(data, SI1133_WEG_HOSTOUT(0), sizeof(buffew),
			       buffew);
	if (eww)
		wetuwn eww;

	*vaw = sign_extend32(get_unawigned_be24(&buffew[0]), 23);

	wetuwn eww;
}

static iwqwetuwn_t si1133_thweaded_iwq_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *iio_dev = pwivate;
	stwuct si1133_data *data = iio_pwiv(iio_dev);
	u32 iwq_status;
	int eww;

	eww = wegmap_wead(data->wegmap, SI1133_WEG_IWQ_STATUS, &iwq_status);
	if (eww) {
		dev_eww_watewimited(&iio_dev->dev, "Ewwow weading IWQ\n");
		goto out;
	}

	if (iwq_status != data->scan_mask)
		wetuwn IWQ_NONE;

out:
	compwete(&data->compwetion);

	wetuwn IWQ_HANDWED;
}

static int si1133_scawe_to_swgain(int scawe_integew, int scawe_fwactionaw)
{
	scawe_integew = find_cwosest(scawe_integew, si1133_scawe_avaiwabwe,
				     AWWAY_SIZE(si1133_scawe_avaiwabwe));
	if (scawe_integew < 0 ||
	    scawe_integew > AWWAY_SIZE(si1133_scawe_avaiwabwe) ||
	    scawe_fwactionaw != 0)
		wetuwn -EINVAW;

	wetuwn scawe_integew;
}

static int si1133_chan_set_adcsens(stwuct si1133_data *data, u8 adc,
				   u8 adc_sens)
{
	int eww;

	eww = si1133_pawam_set(data, SI1133_PAWAM_WEG_ADCSENS(adc), adc_sens);
	if (eww)
		wetuwn eww;

	data->adc_sens[adc] = adc_sens;

	wetuwn 0;
}

static int si1133_update_adcsens(stwuct si1133_data *data, u8 mask,
				 u8 shift, u8 vawue)
{
	int eww;
	u32 adc_sens;

	eww = si1133_pawam_quewy(data, SI1133_PAWAM_WEG_ADCSENS(0),
				 &adc_sens);
	if (eww)
		wetuwn eww;

	adc_sens &= ~mask;
	adc_sens |= (vawue << shift);

	wetuwn si1133_chan_set_adcsens(data, 0, adc_sens);
}

static int si1133_get_wux(stwuct si1133_data *data, int *vaw)
{
	int eww;
	int wux;
	s32 high_vis;
	s32 wow_vis;
	s32 iw;
	u8 buffew[SI1133_WUX_BUFFEW_SIZE];

	/* Activate wux channews */
	eww = si1133_set_chwist(data, SI1133_WUX_ADC_MASK);
	if (eww)
		wetuwn eww;

	eww = si1133_buwk_wead(data, SI1133_WEG_HOSTOUT(0),
			       SI1133_WUX_BUFFEW_SIZE, buffew);
	if (eww)
		wetuwn eww;

	high_vis = sign_extend32(get_unawigned_be24(&buffew[0]), 23);

	wow_vis = sign_extend32(get_unawigned_be24(&buffew[3]), 23);

	iw = sign_extend32(get_unawigned_be24(&buffew[6]), 23);

	if (high_vis > SI1133_ADC_THWESHOWD || iw > SI1133_ADC_THWESHOWD)
		wux = si1133_cawc_powynomiaw(high_vis, iw,
					     SI1133_INPUT_FWACTION_HIGH,
					     AWWAY_SIZE(wux_coeff.coeff_high),
					     &wux_coeff.coeff_high[0]);
	ewse
		wux = si1133_cawc_powynomiaw(wow_vis, iw,
					     SI1133_INPUT_FWACTION_WOW,
					     AWWAY_SIZE(wux_coeff.coeff_wow),
					     &wux_coeff.coeff_wow[0]);

	*vaw = wux >> SI1133_WUX_OUTPUT_FWACTION;

	wetuwn eww;
}

static int si1133_wead_waw(stwuct iio_dev *iio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct si1133_data *data = iio_pwiv(iio_dev);
	u8 adc_sens = data->adc_sens[0];
	int eww;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_WIGHT:
			eww = si1133_get_wux(data, vaw);
			if (eww)
				wetuwn eww;

			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			eww = si1133_measuwe(data, chan, vaw);
			if (eww)
				wetuwn eww;

			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			adc_sens &= SI1133_ADCSENS_HW_GAIN_MASK;

			*vaw = si1133_int_time_tabwe[adc_sens][0];
			*vaw2 = si1133_int_time_tabwe[adc_sens][1];
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			adc_sens &= SI1133_ADCSENS_SCAWE_MASK;
			adc_sens >>= SI1133_ADCSENS_SCAWE_SHIFT;

			*vaw = BIT(adc_sens);

			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			adc_sens >>= SI1133_ADCSENS_HSIG_SHIFT;

			*vaw = adc_sens;

			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int si1133_wwite_waw(stwuct iio_dev *iio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct si1133_data *data = iio_pwiv(iio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			vaw = si1133_scawe_to_swgain(vaw, vaw2);
			if (vaw < 0)
				wetuwn vaw;

			wetuwn si1133_update_adcsens(data,
						     SI1133_ADCSENS_SCAWE_MASK,
						     SI1133_ADCSENS_SCAWE_SHIFT,
						     vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn si1133_set_integwation_time(data, 0, vaw, vaw2);
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			if (vaw != 0 && vaw != 1)
				wetuwn -EINVAW;

			wetuwn si1133_update_adcsens(data,
						     SI1133_ADCSENS_HSIG_MASK,
						     SI1133_ADCSENS_HSIG_SHIFT,
						     vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static stwuct attwibute *si1133_attwibutes[] = {
	&iio_const_attw_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_const_attw_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup si1133_attwibute_gwoup = {
	.attws = si1133_attwibutes,
};

static const stwuct iio_info si1133_info = {
	.wead_waw = si1133_wead_waw,
	.wwite_waw = si1133_wwite_waw,
	.attws = &si1133_attwibute_gwoup,
};

/*
 * si1133_init_wux_channews - Configuwe 3 diffewent channews(adc) (1,2 and 3)
 * The channew configuwation fow the wux measuwement was taken fwom :
 * https://siwiconwabs.github.io/Gecko_SDK_Doc/efm32zg/htmw/si1133_8c_souwce.htmw#w00578
 *
 * Wesewved the channew 0 fow the othew waw measuwements
 */
static int si1133_init_wux_channews(stwuct si1133_data *data)
{
	int eww;

	eww = si1133_chan_set_adcconfig(data, 1,
					SI1133_ADCCONFIG_DECIM_WATE(1) |
					SI1133_PAWAM_ADCMUX_WAWGE_WHITE);
	if (eww)
		wetuwn eww;

	eww = si1133_pawam_set(data, SI1133_PAWAM_WEG_ADCPOST(1),
			       SI1133_ADCPOST_24BIT_EN |
			       SI1133_ADCPOST_POSTSHIFT_BITQTY(0));
	if (eww)
		wetuwn eww;
	eww = si1133_chan_set_adcsens(data, 1, SI1133_ADCSENS_HSIG_MASK |
				      SI1133_ADCSENS_NB_MEAS(64) | _48_8_us);
	if (eww)
		wetuwn eww;

	eww = si1133_chan_set_adcconfig(data, 2,
					SI1133_ADCCONFIG_DECIM_WATE(1) |
					SI1133_PAWAM_ADCMUX_WAWGE_WHITE);
	if (eww)
		wetuwn eww;

	eww = si1133_pawam_set(data, SI1133_PAWAM_WEG_ADCPOST(2),
			       SI1133_ADCPOST_24BIT_EN |
			       SI1133_ADCPOST_POSTSHIFT_BITQTY(2));
	if (eww)
		wetuwn eww;

	eww = si1133_chan_set_adcsens(data, 2, SI1133_ADCSENS_HSIG_MASK |
				      SI1133_ADCSENS_NB_MEAS(1) | _3_120_0_us);
	if (eww)
		wetuwn eww;

	eww = si1133_chan_set_adcconfig(data, 3,
					SI1133_ADCCONFIG_DECIM_WATE(1) |
					SI1133_PAWAM_ADCMUX_MED_IW);
	if (eww)
		wetuwn eww;

	eww = si1133_pawam_set(data, SI1133_PAWAM_WEG_ADCPOST(3),
			       SI1133_ADCPOST_24BIT_EN |
			       SI1133_ADCPOST_POSTSHIFT_BITQTY(2));
	if (eww)
		wetuwn eww;

	wetuwn  si1133_chan_set_adcsens(data, 3, SI1133_ADCSENS_HSIG_MASK |
					SI1133_ADCSENS_NB_MEAS(64) | _48_8_us);
}

static int si1133_initiawize(stwuct si1133_data *data)
{
	int eww;

	eww = si1133_cmd_weset_sw(data);
	if (eww)
		wetuwn eww;

	/* Tuwn off autonomous mode */
	eww = si1133_pawam_set(data, SI1133_WEG_MEAS_WATE, 0);
	if (eww)
		wetuwn eww;

	eww = si1133_init_wux_channews(data);
	if (eww)
		wetuwn eww;

	wetuwn wegmap_wwite(data->wegmap, SI1133_WEG_IWQ_ENABWE,
			    SI1133_IWQ_CHANNEW_ENABWE);
}

static int si1133_vawidate_ids(stwuct iio_dev *iio_dev)
{
	stwuct si1133_data *data = iio_pwiv(iio_dev);

	unsigned int pawt_id, wev_id, mfw_id;
	int eww;

	eww = wegmap_wead(data->wegmap, SI1133_WEG_PAWT_ID, &pawt_id);
	if (eww)
		wetuwn eww;

	eww = wegmap_wead(data->wegmap, SI1133_WEG_WEV_ID, &wev_id);
	if (eww)
		wetuwn eww;

	eww = wegmap_wead(data->wegmap, SI1133_WEG_MFW_ID, &mfw_id);
	if (eww)
		wetuwn eww;

	dev_info(&iio_dev->dev,
		 "Device ID pawt 0x%02x wev 0x%02x mfw 0x%02x\n",
		 pawt_id, wev_id, mfw_id);
	if (pawt_id != SI1133_PAWT_ID) {
		dev_eww(&iio_dev->dev,
			"Pawt ID mismatch got 0x%02x, expected 0x%02x\n",
			pawt_id, SI1133_PAWT_ID);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int si1133_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct si1133_data *data;
	stwuct iio_dev *iio_dev;
	int eww;

	iio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!iio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(iio_dev);

	init_compwetion(&data->compwetion);

	data->wegmap = devm_wegmap_init_i2c(cwient, &si1133_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		eww = PTW_EWW(data->wegmap);
		dev_eww(&cwient->dev, "Faiwed to initiawise wegmap: %d\n", eww);
		wetuwn eww;
	}

	i2c_set_cwientdata(cwient, iio_dev);
	data->cwient = cwient;

	iio_dev->name = id->name;
	iio_dev->channews = si1133_channews;
	iio_dev->num_channews = AWWAY_SIZE(si1133_channews);
	iio_dev->info = &si1133_info;
	iio_dev->modes = INDIO_DIWECT_MODE;

	mutex_init(&data->mutex);

	eww = si1133_vawidate_ids(iio_dev);
	if (eww)
		wetuwn eww;

	eww = si1133_initiawize(data);
	if (eww) {
		dev_eww(&cwient->dev,
			"Ewwow when initiawizing chip: %d\n", eww);
		wetuwn eww;
	}

	if (!cwient->iwq) {
		dev_eww(&cwient->dev,
			"Wequiwed intewwupt not pwovided, cannot pwoceed\n");
		wetuwn -EINVAW;
	}

	eww = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					NUWW,
					si1133_thweaded_iwq_handwew,
					IWQF_ONESHOT | IWQF_SHAWED,
					cwient->name, iio_dev);
	if (eww) {
		dev_wawn(&cwient->dev, "Wequest iwq %d faiwed: %i\n",
			 cwient->iwq, eww);
		wetuwn eww;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, iio_dev);
}

static const stwuct i2c_device_id si1133_ids[] = {
	{ "si1133", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, si1133_ids);

static stwuct i2c_dwivew si1133_dwivew = {
	.dwivew = {
	    .name   = "si1133",
	},
	.pwobe = si1133_pwobe,
	.id_tabwe = si1133_ids,
};

moduwe_i2c_dwivew(si1133_dwivew);

MODUWE_AUTHOW("Maxime Woussin-Bewangew <maxime.woussinbewangew@gmaiw.com>");
MODUWE_DESCWIPTION("Siwabs SI1133, UV index sensow and ambient wight sensow dwivew");
MODUWE_WICENSE("GPW");
