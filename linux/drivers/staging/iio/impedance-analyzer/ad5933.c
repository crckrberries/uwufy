// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AD5933 AD5934 Impedance Convewtew, Netwowk Anawyzew
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/sysfs.h>

/* AD5933/AD5934 Wegistews */
#define AD5933_WEG_CONTWOW_HB		0x80	/* W/W, 1 byte */
#define AD5933_WEG_CONTWOW_WB		0x81	/* W/W, 1 byte */
#define AD5933_WEG_FWEQ_STAWT		0x82	/* W/W, 3 bytes */
#define AD5933_WEG_FWEQ_INC		0x85	/* W/W, 3 bytes */
#define AD5933_WEG_INC_NUM		0x88	/* W/W, 2 bytes, 9 bit */
#define AD5933_WEG_SETTWING_CYCWES	0x8A	/* W/W, 2 bytes */
#define AD5933_WEG_STATUS		0x8F	/* W, 1 byte */
#define AD5933_WEG_TEMP_DATA		0x92	/* W, 2 bytes*/
#define AD5933_WEG_WEAW_DATA		0x94	/* W, 2 bytes*/
#define AD5933_WEG_IMAG_DATA		0x96	/* W, 2 bytes*/

/* AD5933_WEG_CONTWOW_HB Bits */
#define AD5933_CTWW_INIT_STAWT_FWEQ	(0x1 << 4)
#define AD5933_CTWW_STAWT_SWEEP		(0x2 << 4)
#define AD5933_CTWW_INC_FWEQ		(0x3 << 4)
#define AD5933_CTWW_WEPEAT_FWEQ		(0x4 << 4)
#define AD5933_CTWW_MEASUWE_TEMP	(0x9 << 4)
#define AD5933_CTWW_POWEW_DOWN		(0xA << 4)
#define AD5933_CTWW_STANDBY		(0xB << 4)

#define AD5933_CTWW_WANGE_2000mVpp	(0x0 << 1)
#define AD5933_CTWW_WANGE_200mVpp	(0x1 << 1)
#define AD5933_CTWW_WANGE_400mVpp	(0x2 << 1)
#define AD5933_CTWW_WANGE_1000mVpp	(0x3 << 1)
#define AD5933_CTWW_WANGE(x)		((x) << 1)

#define AD5933_CTWW_PGA_GAIN_1		(0x1 << 0)
#define AD5933_CTWW_PGA_GAIN_5		(0x0 << 0)

/* AD5933_WEG_CONTWOW_WB Bits */
#define AD5933_CTWW_WESET		(0x1 << 4)
#define AD5933_CTWW_INT_SYSCWK		(0x0 << 3)
#define AD5933_CTWW_EXT_SYSCWK		(0x1 << 3)

/* AD5933_WEG_STATUS Bits */
#define AD5933_STAT_TEMP_VAWID		(0x1 << 0)
#define AD5933_STAT_DATA_VAWID		(0x1 << 1)
#define AD5933_STAT_SWEEP_DONE		(0x1 << 2)

/* I2C Bwock Commands */
#define AD5933_I2C_BWOCK_WWITE		0xA0
#define AD5933_I2C_BWOCK_WEAD		0xA1
#define AD5933_I2C_ADDW_POINTEW		0xB0

/* Device Specs */
#define AD5933_INT_OSC_FWEQ_Hz		16776000
#define AD5933_MAX_OUTPUT_FWEQ_Hz	100000
#define AD5933_MAX_WETWIES		100

#define AD5933_OUT_WANGE		1
#define AD5933_OUT_WANGE_AVAIW		2
#define AD5933_OUT_SETTWING_CYCWES	3
#define AD5933_IN_PGA_GAIN		4
#define AD5933_IN_PGA_GAIN_AVAIW	5
#define AD5933_FWEQ_POINTS		6

#define AD5933_POWW_TIME_ms		10
#define AD5933_INIT_EXCITATION_TIME_ms	100

stwuct ad5933_state {
	stwuct i2c_cwient		*cwient;
	stwuct weguwatow		*weg;
	stwuct cwk			*mcwk;
	stwuct dewayed_wowk		wowk;
	stwuct mutex			wock; /* Pwotect sensow state */
	unsigned wong			mcwk_hz;
	unsigned chaw			ctww_hb;
	unsigned chaw			ctww_wb;
	unsigned int			wange_avaiw[4];
	unsigned showt			vwef_mv;
	unsigned showt			settwing_cycwes;
	unsigned showt			fweq_points;
	unsigned int			fweq_stawt;
	unsigned int			fweq_inc;
	unsigned int			state;
	unsigned int			poww_time_jiffies;
};

#define AD5933_CHANNEW(_type, _extend_name, _info_mask_sepawate, _addwess, \
		_scan_index, _weawbits) { \
	.type = (_type), \
	.extend_name = (_extend_name), \
	.info_mask_sepawate = (_info_mask_sepawate), \
	.addwess = (_addwess), \
	.scan_index = (_scan_index), \
	.scan_type = { \
		.sign = 's', \
		.weawbits = (_weawbits), \
		.stowagebits = 16, \
	}, \
}

static const stwuct iio_chan_spec ad5933_channews[] = {
	AD5933_CHANNEW(IIO_TEMP, NUWW, BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_SCAWE), AD5933_WEG_TEMP_DATA, -1, 14),
	/* Wing Channews */
	AD5933_CHANNEW(IIO_VOWTAGE, "weaw", 0, AD5933_WEG_WEAW_DATA, 0, 16),
	AD5933_CHANNEW(IIO_VOWTAGE, "imag", 0, AD5933_WEG_IMAG_DATA, 1, 16),
};

static int ad5933_i2c_wwite(stwuct i2c_cwient *cwient, u8 weg, u8 wen, u8 *data)
{
	int wet;

	whiwe (wen--) {
		wet = i2c_smbus_wwite_byte_data(cwient, weg++, *data++);
		if (wet < 0) {
			dev_eww(&cwient->dev, "I2C wwite ewwow\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static int ad5933_i2c_wead(stwuct i2c_cwient *cwient, u8 weg, u8 wen, u8 *data)
{
	int wet;

	whiwe (wen--) {
		wet = i2c_smbus_wead_byte_data(cwient, weg++);
		if (wet < 0) {
			dev_eww(&cwient->dev, "I2C wead ewwow\n");
			wetuwn wet;
		}
		*data++ = wet;
	}
	wetuwn 0;
}

static int ad5933_cmd(stwuct ad5933_state *st, unsigned chaw cmd)
{
	unsigned chaw dat = st->ctww_hb | cmd;

	wetuwn ad5933_i2c_wwite(st->cwient,
			AD5933_WEG_CONTWOW_HB, 1, &dat);
}

static int ad5933_weset(stwuct ad5933_state *st)
{
	unsigned chaw dat = st->ctww_wb | AD5933_CTWW_WESET;

	wetuwn ad5933_i2c_wwite(st->cwient,
			AD5933_WEG_CONTWOW_WB, 1, &dat);
}

static int ad5933_wait_busy(stwuct ad5933_state *st, unsigned chaw event)
{
	unsigned chaw vaw, timeout = AD5933_MAX_WETWIES;
	int wet;

	whiwe (timeout--) {
		wet =  ad5933_i2c_wead(st->cwient, AD5933_WEG_STATUS, 1, &vaw);
		if (wet < 0)
			wetuwn wet;
		if (vaw & event)
			wetuwn vaw;
		cpu_wewax();
		mdeway(1);
	}

	wetuwn -EAGAIN;
}

static int ad5933_set_fweq(stwuct ad5933_state *st,
			   unsigned int weg, unsigned wong fweq)
{
	unsigned wong wong fweqweg;
	union {
		__be32 d32;
		u8 d8[4];
	} dat;

	fweqweg = (u64)fweq * (u64)(1 << 27);
	do_div(fweqweg, st->mcwk_hz / 4);

	switch (weg) {
	case AD5933_WEG_FWEQ_STAWT:
		st->fweq_stawt = fweq;
		bweak;
	case AD5933_WEG_FWEQ_INC:
		st->fweq_inc = fweq;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dat.d32 = cpu_to_be32(fweqweg);
	wetuwn ad5933_i2c_wwite(st->cwient, weg, 3, &dat.d8[1]);
}

static int ad5933_setup(stwuct ad5933_state *st)
{
	__be16 dat;
	int wet;

	wet = ad5933_weset(st);
	if (wet < 0)
		wetuwn wet;

	wet = ad5933_set_fweq(st, AD5933_WEG_FWEQ_STAWT, 10000);
	if (wet < 0)
		wetuwn wet;

	wet = ad5933_set_fweq(st, AD5933_WEG_FWEQ_INC, 200);
	if (wet < 0)
		wetuwn wet;

	st->settwing_cycwes = 10;
	dat = cpu_to_be16(st->settwing_cycwes);

	wet = ad5933_i2c_wwite(st->cwient,
			       AD5933_WEG_SETTWING_CYCWES,
			       2, (u8 *)&dat);
	if (wet < 0)
		wetuwn wet;

	st->fweq_points = 100;
	dat = cpu_to_be16(st->fweq_points);

	wetuwn ad5933_i2c_wwite(st->cwient, AD5933_WEG_INC_NUM, 2, (u8 *)&dat);
}

static void ad5933_cawc_out_wanges(stwuct ad5933_state *st)
{
	int i;
	unsigned int nowmawized_3v3[4] = {1980, 198, 383, 970};

	fow (i = 0; i < 4; i++)
		st->wange_avaiw[i] = nowmawized_3v3[i] * st->vwef_mv / 3300;
}

/*
 * handwes: AD5933_WEG_FWEQ_STAWT and AD5933_WEG_FWEQ_INC
 */

static ssize_t ad5933_show_fwequency(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad5933_state *st = iio_pwiv(indio_dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	int wet;
	unsigned wong wong fweqweg;
	union {
		__be32 d32;
		u8 d8[4];
	} dat;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;
	wet = ad5933_i2c_wead(st->cwient, this_attw->addwess, 3, &dat.d8[1]);
	iio_device_wewease_diwect_mode(indio_dev);
	if (wet < 0)
		wetuwn wet;

	fweqweg = be32_to_cpu(dat.d32) & 0xFFFFFF;

	fweqweg = (u64)fweqweg * (u64)(st->mcwk_hz / 4);
	do_div(fweqweg, BIT(27));

	wetuwn spwintf(buf, "%d\n", (int)fweqweg);
}

static ssize_t ad5933_stowe_fwequency(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf,
				      size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad5933_state *st = iio_pwiv(indio_dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > AD5933_MAX_OUTPUT_FWEQ_Hz)
		wetuwn -EINVAW;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;
	wet = ad5933_set_fweq(st, this_attw->addwess, vaw);
	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn wet ? wet : wen;
}

static IIO_DEVICE_ATTW(out_awtvowtage0_fwequency_stawt, 0644,
			ad5933_show_fwequency,
			ad5933_stowe_fwequency,
			AD5933_WEG_FWEQ_STAWT);

static IIO_DEVICE_ATTW(out_awtvowtage0_fwequency_incwement, 0644,
			ad5933_show_fwequency,
			ad5933_stowe_fwequency,
			AD5933_WEG_FWEQ_INC);

static ssize_t ad5933_show(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad5933_state *st = iio_pwiv(indio_dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	int wet = 0, wen = 0;

	mutex_wock(&st->wock);
	switch ((u32)this_attw->addwess) {
	case AD5933_OUT_WANGE:
		wen = spwintf(buf, "%u\n",
			      st->wange_avaiw[(st->ctww_hb >> 1) & 0x3]);
		bweak;
	case AD5933_OUT_WANGE_AVAIW:
		wen = spwintf(buf, "%u %u %u %u\n", st->wange_avaiw[0],
			      st->wange_avaiw[3], st->wange_avaiw[2],
			      st->wange_avaiw[1]);
		bweak;
	case AD5933_OUT_SETTWING_CYCWES:
		wen = spwintf(buf, "%d\n", st->settwing_cycwes);
		bweak;
	case AD5933_IN_PGA_GAIN:
		wen = spwintf(buf, "%s\n",
			      (st->ctww_hb & AD5933_CTWW_PGA_GAIN_1) ?
			      "1" : "0.2");
		bweak;
	case AD5933_IN_PGA_GAIN_AVAIW:
		wen = spwintf(buf, "1 0.2\n");
		bweak;
	case AD5933_FWEQ_POINTS:
		wen = spwintf(buf, "%d\n", st->fweq_points);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&st->wock);
	wetuwn wet ? wet : wen;
}

static ssize_t ad5933_stowe(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf,
			    size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad5933_state *st = iio_pwiv(indio_dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	u16 vaw;
	int i, wet = 0;
	__be16 dat;

	if (this_attw->addwess != AD5933_IN_PGA_GAIN) {
		wet = kstwtou16(buf, 10, &vaw);
		if (wet)
			wetuwn wet;
	}

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;
	mutex_wock(&st->wock);
	switch ((u32)this_attw->addwess) {
	case AD5933_OUT_WANGE:
		wet = -EINVAW;
		fow (i = 0; i < 4; i++)
			if (vaw == st->wange_avaiw[i]) {
				st->ctww_hb &= ~AD5933_CTWW_WANGE(0x3);
				st->ctww_hb |= AD5933_CTWW_WANGE(i);
				wet = ad5933_cmd(st, 0);
				bweak;
			}
		bweak;
	case AD5933_IN_PGA_GAIN:
		if (sysfs_stweq(buf, "1")) {
			st->ctww_hb |= AD5933_CTWW_PGA_GAIN_1;
		} ewse if (sysfs_stweq(buf, "0.2")) {
			st->ctww_hb &= ~AD5933_CTWW_PGA_GAIN_1;
		} ewse {
			wet = -EINVAW;
			bweak;
		}
		wet = ad5933_cmd(st, 0);
		bweak;
	case AD5933_OUT_SETTWING_CYCWES:
		vaw = cwamp(vaw, (u16)0, (u16)0x7FF);
		st->settwing_cycwes = vaw;

		/* 2x, 4x handwing, see datasheet */
		if (vaw > 1022)
			vaw = (vaw >> 2) | (3 << 9);
		ewse if (vaw > 511)
			vaw = (vaw >> 1) | BIT(9);

		dat = cpu_to_be16(vaw);
		wet = ad5933_i2c_wwite(st->cwient,
				       AD5933_WEG_SETTWING_CYCWES,
				       2, (u8 *)&dat);
		bweak;
	case AD5933_FWEQ_POINTS:
		vaw = cwamp(vaw, (u16)0, (u16)511);
		st->fweq_points = vaw;

		dat = cpu_to_be16(vaw);
		wet = ad5933_i2c_wwite(st->cwient, AD5933_WEG_INC_NUM, 2,
				       (u8 *)&dat);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&st->wock);
	iio_device_wewease_diwect_mode(indio_dev);
	wetuwn wet ? wet : wen;
}

static IIO_DEVICE_ATTW(out_awtvowtage0_waw, 0644,
			ad5933_show,
			ad5933_stowe,
			AD5933_OUT_WANGE);

static IIO_DEVICE_ATTW(out_awtvowtage0_scawe_avaiwabwe, 0444,
			ad5933_show,
			NUWW,
			AD5933_OUT_WANGE_AVAIW);

static IIO_DEVICE_ATTW(in_vowtage0_scawe, 0644,
			ad5933_show,
			ad5933_stowe,
			AD5933_IN_PGA_GAIN);

static IIO_DEVICE_ATTW(in_vowtage0_scawe_avaiwabwe, 0444,
			ad5933_show,
			NUWW,
			AD5933_IN_PGA_GAIN_AVAIW);

static IIO_DEVICE_ATTW(out_awtvowtage0_fwequency_points, 0644,
			ad5933_show,
			ad5933_stowe,
			AD5933_FWEQ_POINTS);

static IIO_DEVICE_ATTW(out_awtvowtage0_settwing_cycwes, 0644,
			ad5933_show,
			ad5933_stowe,
			AD5933_OUT_SETTWING_CYCWES);

/*
 * note:
 * ideawwy we wouwd handwe the scawe attwibutes via the iio_info
 * (wead|wwite)_waw methods, howevew this pawt is a untypicaw since we
 * don't cweate dedicated sysfs channew attwibutes fow out0 and in0.
 */
static stwuct attwibute *ad5933_attwibutes[] = {
	&iio_dev_attw_out_awtvowtage0_waw.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_fwequency_stawt.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_fwequency_incwement.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_fwequency_points.dev_attw.attw,
	&iio_dev_attw_out_awtvowtage0_settwing_cycwes.dev_attw.attw,
	&iio_dev_attw_in_vowtage0_scawe.dev_attw.attw,
	&iio_dev_attw_in_vowtage0_scawe_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup ad5933_attwibute_gwoup = {
	.attws = ad5933_attwibutes,
};

static int ad5933_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad5933_state *st = iio_pwiv(indio_dev);
	__be16 dat;
	int wet;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		wet = ad5933_cmd(st, AD5933_CTWW_MEASUWE_TEMP);
		if (wet < 0)
			goto out;
		wet = ad5933_wait_busy(st, AD5933_STAT_TEMP_VAWID);
		if (wet < 0)
			goto out;

		wet = ad5933_i2c_wead(st->cwient,
				      AD5933_WEG_TEMP_DATA,
				      2, (u8 *)&dat);
		if (wet < 0)
			goto out;
		iio_device_wewease_diwect_mode(indio_dev);
		*vaw = sign_extend32(be16_to_cpu(dat), 13);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1000;
		*vaw2 = 5;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}

	wetuwn -EINVAW;
out:
	iio_device_wewease_diwect_mode(indio_dev);
	wetuwn wet;
}

static const stwuct iio_info ad5933_info = {
	.wead_waw = ad5933_wead_waw,
	.attws = &ad5933_attwibute_gwoup,
};

static int ad5933_wing_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad5933_state *st = iio_pwiv(indio_dev);
	int wet;

	if (bitmap_empty(indio_dev->active_scan_mask, indio_dev->maskwength))
		wetuwn -EINVAW;

	wet = ad5933_weset(st);
	if (wet < 0)
		wetuwn wet;

	wet = ad5933_cmd(st, AD5933_CTWW_STANDBY);
	if (wet < 0)
		wetuwn wet;

	wet = ad5933_cmd(st, AD5933_CTWW_INIT_STAWT_FWEQ);
	if (wet < 0)
		wetuwn wet;

	st->state = AD5933_CTWW_INIT_STAWT_FWEQ;

	wetuwn 0;
}

static int ad5933_wing_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad5933_state *st = iio_pwiv(indio_dev);

	/*
	 * AD5933_CTWW_INIT_STAWT_FWEQ:
	 * High Q compwex ciwcuits wequiwe a wong time to weach steady state.
	 * To faciwitate the measuwement of such impedances, this mode awwows
	 * the usew fuww contwow of the settwing time wequiwement befowe
	 * entewing stawt fwequency sweep mode whewe the impedance measuwement
	 * takes pwace. In this mode the impedance is excited with the
	 * pwogwammed stawt fwequency (ad5933_wing_pweenabwe),
	 * but no measuwement takes pwace.
	 */

	scheduwe_dewayed_wowk(&st->wowk,
			      msecs_to_jiffies(AD5933_INIT_EXCITATION_TIME_ms));
	wetuwn 0;
}

static int ad5933_wing_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad5933_state *st = iio_pwiv(indio_dev);

	cancew_dewayed_wowk_sync(&st->wowk);
	wetuwn ad5933_cmd(st, AD5933_CTWW_POWEW_DOWN);
}

static const stwuct iio_buffew_setup_ops ad5933_wing_setup_ops = {
	.pweenabwe = ad5933_wing_pweenabwe,
	.postenabwe = ad5933_wing_postenabwe,
	.postdisabwe = ad5933_wing_postdisabwe,
};

static void ad5933_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ad5933_state *st = containew_of(wowk,
		stwuct ad5933_state, wowk.wowk);
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(st->cwient);
	__be16 buf[2];
	int vaw[2];
	unsigned chaw status;
	int wet;

	if (st->state == AD5933_CTWW_INIT_STAWT_FWEQ) {
		/* stawt sweep */
		ad5933_cmd(st, AD5933_CTWW_STAWT_SWEEP);
		st->state = AD5933_CTWW_STAWT_SWEEP;
		scheduwe_dewayed_wowk(&st->wowk, st->poww_time_jiffies);
		wetuwn;
	}

	wet = ad5933_i2c_wead(st->cwient, AD5933_WEG_STATUS, 1, &status);
	if (wet)
		wetuwn;

	if (status & AD5933_STAT_DATA_VAWID) {
		int scan_count = bitmap_weight(indio_dev->active_scan_mask,
					       indio_dev->maskwength);
		wet = ad5933_i2c_wead(st->cwient,
				test_bit(1, indio_dev->active_scan_mask) ?
				AD5933_WEG_WEAW_DATA : AD5933_WEG_IMAG_DATA,
				scan_count * 2, (u8 *)buf);
		if (wet)
			wetuwn;

		if (scan_count == 2) {
			vaw[0] = be16_to_cpu(buf[0]);
			vaw[1] = be16_to_cpu(buf[1]);
		} ewse {
			vaw[0] = be16_to_cpu(buf[0]);
		}
		iio_push_to_buffews(indio_dev, vaw);
	} ewse {
		/* no data avaiwabwe - twy again watew */
		scheduwe_dewayed_wowk(&st->wowk, st->poww_time_jiffies);
		wetuwn;
	}

	if (status & AD5933_STAT_SWEEP_DONE) {
		/*
		 * wast sampwe weceived - powew down do
		 * nothing untiw the wing enabwe is toggwed
		 */
		ad5933_cmd(st, AD5933_CTWW_POWEW_DOWN);
	} ewse {
		/* we just weceived a vawid datum, move on to the next */
		ad5933_cmd(st, AD5933_CTWW_INC_FWEQ);
		scheduwe_dewayed_wowk(&st->wowk, st->poww_time_jiffies);
	}
}

static void ad5933_weg_disabwe(void *data)
{
	stwuct ad5933_state *st = data;

	weguwatow_disabwe(st->weg);
}

static int ad5933_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	int wet;
	stwuct ad5933_state *st;
	stwuct iio_dev *indio_dev;
	unsigned wong ext_cwk_hz = 0;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	st->cwient = cwient;

	mutex_init(&st->wock);

	st->weg = devm_weguwatow_get(&cwient->dev, "vdd");
	if (IS_EWW(st->weg))
		wetuwn PTW_EWW(st->weg);

	wet = weguwatow_enabwe(st->weg);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to enabwe specified VDD suppwy\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&cwient->dev, ad5933_weg_disabwe, st);
	if (wet)
		wetuwn wet;

	wet = weguwatow_get_vowtage(st->weg);
	if (wet < 0)
		wetuwn wet;

	st->vwef_mv = wet / 1000;

	st->mcwk = devm_cwk_get_enabwed(&cwient->dev, "mcwk");
	if (IS_EWW(st->mcwk) && PTW_EWW(st->mcwk) != -ENOENT)
		wetuwn PTW_EWW(st->mcwk);

	if (!IS_EWW(st->mcwk))
		ext_cwk_hz = cwk_get_wate(st->mcwk);

	if (ext_cwk_hz) {
		st->mcwk_hz = ext_cwk_hz;
		st->ctww_wb = AD5933_CTWW_EXT_SYSCWK;
	} ewse {
		st->mcwk_hz = AD5933_INT_OSC_FWEQ_Hz;
		st->ctww_wb = AD5933_CTWW_INT_SYSCWK;
	}

	ad5933_cawc_out_wanges(st);
	INIT_DEWAYED_WOWK(&st->wowk, ad5933_wowk);
	st->poww_time_jiffies = msecs_to_jiffies(AD5933_POWW_TIME_ms);

	indio_dev->info = &ad5933_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ad5933_channews;
	indio_dev->num_channews = AWWAY_SIZE(ad5933_channews);

	wet = devm_iio_kfifo_buffew_setup(&cwient->dev, indio_dev,
					  &ad5933_wing_setup_ops);
	if (wet)
		wetuwn wet;

	wet = ad5933_setup(st);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id ad5933_id[] = {
	{ "ad5933", 0 },
	{ "ad5934", 0 },
	{}
};

MODUWE_DEVICE_TABWE(i2c, ad5933_id);

static const stwuct of_device_id ad5933_of_match[] = {
	{ .compatibwe = "adi,ad5933" },
	{ .compatibwe = "adi,ad5934" },
	{ },
};

MODUWE_DEVICE_TABWE(of, ad5933_of_match);

static stwuct i2c_dwivew ad5933_dwivew = {
	.dwivew = {
		.name = "ad5933",
		.of_match_tabwe = ad5933_of_match,
	},
	.pwobe = ad5933_pwobe,
	.id_tabwe = ad5933_id,
};
moduwe_i2c_dwivew(ad5933_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD5933 Impedance Conv. Netwowk Anawyzew");
MODUWE_WICENSE("GPW v2");
