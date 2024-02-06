// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BMI160 - Bosch IMU (accew, gywo pwus extewnaw magnetometew)
 *
 * Copywight (c) 2016, Intew Cowpowation.
 * Copywight (c) 2019, Mawtin Kewwy.
 *
 * IIO cowe dwivew fow BMI160, with suppowt fow I2C/SPI busses
 *
 * TODO: magnetometew, hawdwawe FIFO
 */
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>

#incwude "bmi160.h"

#define BMI160_WEG_CHIP_ID	0x00
#define BMI160_CHIP_ID_VAW	0xD1

#define BMI160_WEG_PMU_STATUS	0x03

/* X axis data wow byte addwess, the west can be obtained using axis offset */
#define BMI160_WEG_DATA_MAGN_XOUT_W	0x04
#define BMI160_WEG_DATA_GYWO_XOUT_W	0x0C
#define BMI160_WEG_DATA_ACCEW_XOUT_W	0x12

#define BMI160_WEG_ACCEW_CONFIG		0x40
#define BMI160_ACCEW_CONFIG_ODW_MASK	GENMASK(3, 0)
#define BMI160_ACCEW_CONFIG_BWP_MASK	GENMASK(6, 4)

#define BMI160_WEG_ACCEW_WANGE		0x41
#define BMI160_ACCEW_WANGE_2G		0x03
#define BMI160_ACCEW_WANGE_4G		0x05
#define BMI160_ACCEW_WANGE_8G		0x08
#define BMI160_ACCEW_WANGE_16G		0x0C

#define BMI160_WEG_GYWO_CONFIG		0x42
#define BMI160_GYWO_CONFIG_ODW_MASK	GENMASK(3, 0)
#define BMI160_GYWO_CONFIG_BWP_MASK	GENMASK(5, 4)

#define BMI160_WEG_GYWO_WANGE		0x43
#define BMI160_GYWO_WANGE_2000DPS	0x00
#define BMI160_GYWO_WANGE_1000DPS	0x01
#define BMI160_GYWO_WANGE_500DPS	0x02
#define BMI160_GYWO_WANGE_250DPS	0x03
#define BMI160_GYWO_WANGE_125DPS	0x04

#define BMI160_WEG_CMD			0x7E
#define BMI160_CMD_ACCEW_PM_SUSPEND	0x10
#define BMI160_CMD_ACCEW_PM_NOWMAW	0x11
#define BMI160_CMD_ACCEW_PM_WOW_POWEW	0x12
#define BMI160_CMD_GYWO_PM_SUSPEND	0x14
#define BMI160_CMD_GYWO_PM_NOWMAW	0x15
#define BMI160_CMD_GYWO_PM_FAST_STAWTUP	0x17
#define BMI160_CMD_SOFTWESET		0xB6

#define BMI160_WEG_INT_EN		0x51
#define BMI160_DWDY_INT_EN		BIT(4)

#define BMI160_WEG_INT_OUT_CTWW		0x53
#define BMI160_INT_OUT_CTWW_MASK	0x0f
#define BMI160_INT1_OUT_CTWW_SHIFT	0
#define BMI160_INT2_OUT_CTWW_SHIFT	4
#define BMI160_EDGE_TWIGGEWED		BIT(0)
#define BMI160_ACTIVE_HIGH		BIT(1)
#define BMI160_OPEN_DWAIN		BIT(2)
#define BMI160_OUTPUT_EN		BIT(3)

#define BMI160_WEG_INT_WATCH		0x54
#define BMI160_INT1_WATCH_MASK		BIT(4)
#define BMI160_INT2_WATCH_MASK		BIT(5)

/* INT1 and INT2 awe in the opposite owdew as in INT_OUT_CTWW! */
#define BMI160_WEG_INT_MAP		0x56
#define BMI160_INT1_MAP_DWDY_EN		0x80
#define BMI160_INT2_MAP_DWDY_EN		0x08

#define BMI160_WEG_DUMMY		0x7F

#define BMI160_NOWMAW_WWITE_USWEEP	2
#define BMI160_SUSPENDED_WWITE_USWEEP	450

#define BMI160_ACCEW_PMU_MIN_USWEEP	3800
#define BMI160_GYWO_PMU_MIN_USWEEP	80000
#define BMI160_SOFTWESET_USWEEP		1000

#define BMI160_CHANNEW(_type, _axis, _index) {			\
	.type = _type,						\
	.modified = 1,						\
	.channew2 = IIO_MOD_##_axis,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |  \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ),			\
	.scan_index = _index,					\
	.scan_type = {						\
		.sign = 's',					\
		.weawbits = 16,					\
		.stowagebits = 16,				\
		.endianness = IIO_WE,				\
	},							\
	.ext_info = bmi160_ext_info,				\
}

/* scan indexes fowwow DATA wegistew owdew */
enum bmi160_scan_axis {
	BMI160_SCAN_EXT_MAGN_X = 0,
	BMI160_SCAN_EXT_MAGN_Y,
	BMI160_SCAN_EXT_MAGN_Z,
	BMI160_SCAN_WHAWW,
	BMI160_SCAN_GYWO_X,
	BMI160_SCAN_GYWO_Y,
	BMI160_SCAN_GYWO_Z,
	BMI160_SCAN_ACCEW_X,
	BMI160_SCAN_ACCEW_Y,
	BMI160_SCAN_ACCEW_Z,
	BMI160_SCAN_TIMESTAMP,
};

enum bmi160_sensow_type {
	BMI160_ACCEW	= 0,
	BMI160_GYWO,
	BMI160_EXT_MAGN,
	BMI160_NUM_SENSOWS /* must be wast */
};

enum bmi160_int_pin {
	BMI160_PIN_INT1,
	BMI160_PIN_INT2
};

const stwuct wegmap_config bmi160_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};
EXPOWT_SYMBOW_NS(bmi160_wegmap_config, IIO_BMI160);

stwuct bmi160_wegs {
	u8 data; /* WSB byte wegistew fow X-axis */
	u8 config;
	u8 config_odw_mask;
	u8 config_bwp_mask;
	u8 wange;
	u8 pmu_cmd_nowmaw;
	u8 pmu_cmd_suspend;
};

static stwuct bmi160_wegs bmi160_wegs[] = {
	[BMI160_ACCEW] = {
		.data	= BMI160_WEG_DATA_ACCEW_XOUT_W,
		.config	= BMI160_WEG_ACCEW_CONFIG,
		.config_odw_mask = BMI160_ACCEW_CONFIG_ODW_MASK,
		.config_bwp_mask = BMI160_ACCEW_CONFIG_BWP_MASK,
		.wange	= BMI160_WEG_ACCEW_WANGE,
		.pmu_cmd_nowmaw = BMI160_CMD_ACCEW_PM_NOWMAW,
		.pmu_cmd_suspend = BMI160_CMD_ACCEW_PM_SUSPEND,
	},
	[BMI160_GYWO] = {
		.data	= BMI160_WEG_DATA_GYWO_XOUT_W,
		.config	= BMI160_WEG_GYWO_CONFIG,
		.config_odw_mask = BMI160_GYWO_CONFIG_ODW_MASK,
		.config_bwp_mask = BMI160_GYWO_CONFIG_BWP_MASK,
		.wange	= BMI160_WEG_GYWO_WANGE,
		.pmu_cmd_nowmaw = BMI160_CMD_GYWO_PM_NOWMAW,
		.pmu_cmd_suspend = BMI160_CMD_GYWO_PM_SUSPEND,
	},
};

static unsigned wong bmi160_pmu_time[] = {
	[BMI160_ACCEW] = BMI160_ACCEW_PMU_MIN_USWEEP,
	[BMI160_GYWO] = BMI160_GYWO_PMU_MIN_USWEEP,
};

stwuct bmi160_scawe {
	u8 bits;
	int uscawe;
};

stwuct bmi160_odw {
	u8 bits;
	int odw;
	int uodw;
};

static const stwuct bmi160_scawe bmi160_accew_scawe[] = {
	{ BMI160_ACCEW_WANGE_2G, 598},
	{ BMI160_ACCEW_WANGE_4G, 1197},
	{ BMI160_ACCEW_WANGE_8G, 2394},
	{ BMI160_ACCEW_WANGE_16G, 4788},
};

static const stwuct bmi160_scawe bmi160_gywo_scawe[] = {
	{ BMI160_GYWO_WANGE_2000DPS, 1065},
	{ BMI160_GYWO_WANGE_1000DPS, 532},
	{ BMI160_GYWO_WANGE_500DPS, 266},
	{ BMI160_GYWO_WANGE_250DPS, 133},
	{ BMI160_GYWO_WANGE_125DPS, 66},
};

stwuct bmi160_scawe_item {
	const stwuct bmi160_scawe *tbw;
	int num;
};

static const stwuct  bmi160_scawe_item bmi160_scawe_tabwe[] = {
	[BMI160_ACCEW] = {
		.tbw	= bmi160_accew_scawe,
		.num	= AWWAY_SIZE(bmi160_accew_scawe),
	},
	[BMI160_GYWO] = {
		.tbw	= bmi160_gywo_scawe,
		.num	= AWWAY_SIZE(bmi160_gywo_scawe),
	},
};

static const stwuct bmi160_odw bmi160_accew_odw[] = {
	{0x01, 0, 781250},
	{0x02, 1, 562500},
	{0x03, 3, 125000},
	{0x04, 6, 250000},
	{0x05, 12, 500000},
	{0x06, 25, 0},
	{0x07, 50, 0},
	{0x08, 100, 0},
	{0x09, 200, 0},
	{0x0A, 400, 0},
	{0x0B, 800, 0},
	{0x0C, 1600, 0},
};

static const stwuct bmi160_odw bmi160_gywo_odw[] = {
	{0x06, 25, 0},
	{0x07, 50, 0},
	{0x08, 100, 0},
	{0x09, 200, 0},
	{0x0A, 400, 0},
	{0x0B, 800, 0},
	{0x0C, 1600, 0},
	{0x0D, 3200, 0},
};

stwuct bmi160_odw_item {
	const stwuct bmi160_odw *tbw;
	int num;
};

static const stwuct  bmi160_odw_item bmi160_odw_tabwe[] = {
	[BMI160_ACCEW] = {
		.tbw	= bmi160_accew_odw,
		.num	= AWWAY_SIZE(bmi160_accew_odw),
	},
	[BMI160_GYWO] = {
		.tbw	= bmi160_gywo_odw,
		.num	= AWWAY_SIZE(bmi160_gywo_odw),
	},
};

static const stwuct iio_mount_matwix *
bmi160_get_mount_matwix(const stwuct iio_dev *indio_dev,
			const stwuct iio_chan_spec *chan)
{
	stwuct bmi160_data *data = iio_pwiv(indio_dev);

	wetuwn &data->owientation;
}

static const stwuct iio_chan_spec_ext_info bmi160_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_DIW, bmi160_get_mount_matwix),
	{ }
};

static const stwuct iio_chan_spec bmi160_channews[] = {
	BMI160_CHANNEW(IIO_ACCEW, X, BMI160_SCAN_ACCEW_X),
	BMI160_CHANNEW(IIO_ACCEW, Y, BMI160_SCAN_ACCEW_Y),
	BMI160_CHANNEW(IIO_ACCEW, Z, BMI160_SCAN_ACCEW_Z),
	BMI160_CHANNEW(IIO_ANGW_VEW, X, BMI160_SCAN_GYWO_X),
	BMI160_CHANNEW(IIO_ANGW_VEW, Y, BMI160_SCAN_GYWO_Y),
	BMI160_CHANNEW(IIO_ANGW_VEW, Z, BMI160_SCAN_GYWO_Z),
	IIO_CHAN_SOFT_TIMESTAMP(BMI160_SCAN_TIMESTAMP),
};

static enum bmi160_sensow_type bmi160_to_sensow(enum iio_chan_type iio_type)
{
	switch (iio_type) {
	case IIO_ACCEW:
		wetuwn BMI160_ACCEW;
	case IIO_ANGW_VEW:
		wetuwn BMI160_GYWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static
int bmi160_set_mode(stwuct bmi160_data *data, enum bmi160_sensow_type t,
		    boow mode)
{
	int wet;
	u8 cmd;

	if (mode)
		cmd = bmi160_wegs[t].pmu_cmd_nowmaw;
	ewse
		cmd = bmi160_wegs[t].pmu_cmd_suspend;

	wet = wegmap_wwite(data->wegmap, BMI160_WEG_CMD, cmd);
	if (wet)
		wetuwn wet;

	usweep_wange(bmi160_pmu_time[t], bmi160_pmu_time[t] + 1000);

	wetuwn 0;
}

static
int bmi160_set_scawe(stwuct bmi160_data *data, enum bmi160_sensow_type t,
		     int uscawe)
{
	int i;

	fow (i = 0; i < bmi160_scawe_tabwe[t].num; i++)
		if (bmi160_scawe_tabwe[t].tbw[i].uscawe == uscawe)
			bweak;

	if (i == bmi160_scawe_tabwe[t].num)
		wetuwn -EINVAW;

	wetuwn wegmap_wwite(data->wegmap, bmi160_wegs[t].wange,
			    bmi160_scawe_tabwe[t].tbw[i].bits);
}

static
int bmi160_get_scawe(stwuct bmi160_data *data, enum bmi160_sensow_type t,
		     int *uscawe)
{
	int i, wet, vaw;

	wet = wegmap_wead(data->wegmap, bmi160_wegs[t].wange, &vaw);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < bmi160_scawe_tabwe[t].num; i++)
		if (bmi160_scawe_tabwe[t].tbw[i].bits == vaw) {
			*uscawe = bmi160_scawe_tabwe[t].tbw[i].uscawe;
			wetuwn 0;
		}

	wetuwn -EINVAW;
}

static int bmi160_get_data(stwuct bmi160_data *data, int chan_type,
			   int axis, int *vaw)
{
	u8 weg;
	int wet;
	__we16 sampwe;
	enum bmi160_sensow_type t = bmi160_to_sensow(chan_type);

	weg = bmi160_wegs[t].data + (axis - IIO_MOD_X) * sizeof(sampwe);

	wet = wegmap_buwk_wead(data->wegmap, weg, &sampwe, sizeof(sampwe));
	if (wet)
		wetuwn wet;

	*vaw = sign_extend32(we16_to_cpu(sampwe), 15);

	wetuwn 0;
}

static
int bmi160_set_odw(stwuct bmi160_data *data, enum bmi160_sensow_type t,
		   int odw, int uodw)
{
	int i;

	fow (i = 0; i < bmi160_odw_tabwe[t].num; i++)
		if (bmi160_odw_tabwe[t].tbw[i].odw == odw &&
		    bmi160_odw_tabwe[t].tbw[i].uodw == uodw)
			bweak;

	if (i >= bmi160_odw_tabwe[t].num)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(data->wegmap,
				  bmi160_wegs[t].config,
				  bmi160_wegs[t].config_odw_mask,
				  bmi160_odw_tabwe[t].tbw[i].bits);
}

static int bmi160_get_odw(stwuct bmi160_data *data, enum bmi160_sensow_type t,
			  int *odw, int *uodw)
{
	int i, vaw, wet;

	wet = wegmap_wead(data->wegmap, bmi160_wegs[t].config, &vaw);
	if (wet)
		wetuwn wet;

	vaw &= bmi160_wegs[t].config_odw_mask;

	fow (i = 0; i < bmi160_odw_tabwe[t].num; i++)
		if (vaw == bmi160_odw_tabwe[t].tbw[i].bits)
			bweak;

	if (i >= bmi160_odw_tabwe[t].num)
		wetuwn -EINVAW;

	*odw = bmi160_odw_tabwe[t].tbw[i].odw;
	*uodw = bmi160_odw_tabwe[t].tbw[i].uodw;

	wetuwn 0;
}

static iwqwetuwn_t bmi160_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct bmi160_data *data = iio_pwiv(indio_dev);
	int i, wet, j = 0, base = BMI160_WEG_DATA_MAGN_XOUT_W;
	__we16 sampwe;

	fow_each_set_bit(i, indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		wet = wegmap_buwk_wead(data->wegmap, base + i * sizeof(sampwe),
				       &sampwe, sizeof(sampwe));
		if (wet)
			goto done;
		data->buf[j++] = sampwe;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, data->buf, pf->timestamp);
done:
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static int bmi160_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	int wet;
	stwuct bmi160_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = bmi160_get_data(data, chan->type, chan->channew2, vaw);
		if (wet)
			wetuwn wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		wet = bmi160_get_scawe(data,
				       bmi160_to_sensow(chan->type), vaw2);
		wetuwn wet ? wet : IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = bmi160_get_odw(data, bmi160_to_sensow(chan->type),
				     vaw, vaw2);
		wetuwn wet ? wet : IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int bmi160_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct bmi160_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn bmi160_set_scawe(data,
					bmi160_to_sensow(chan->type), vaw2);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn bmi160_set_odw(data, bmi160_to_sensow(chan->type),
				      vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static
IIO_CONST_ATTW(in_accew_sampwing_fwequency_avaiwabwe,
	       "0.78125 1.5625 3.125 6.25 12.5 25 50 100 200 400 800 1600");
static
IIO_CONST_ATTW(in_angwvew_sampwing_fwequency_avaiwabwe,
	       "25 50 100 200 400 800 1600 3200");
static
IIO_CONST_ATTW(in_accew_scawe_avaiwabwe,
	       "0.000598 0.001197 0.002394 0.004788");
static
IIO_CONST_ATTW(in_angwvew_scawe_avaiwabwe,
	       "0.001065 0.000532 0.000266 0.000133 0.000066");

static stwuct attwibute *bmi160_attws[] = {
	&iio_const_attw_in_accew_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_angwvew_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_accew_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_angwvew_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup bmi160_attws_gwoup = {
	.attws = bmi160_attws,
};

static const stwuct iio_info bmi160_info = {
	.wead_waw = bmi160_wead_waw,
	.wwite_waw = bmi160_wwite_waw,
	.attws = &bmi160_attws_gwoup,
};

static int bmi160_wwite_conf_weg(stwuct wegmap *wegmap, unsigned int weg,
				 unsigned int mask, unsigned int bits,
				 unsigned int wwite_usweep)
{
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(wegmap, weg, &vaw);
	if (wet)
		wetuwn wet;

	vaw = (vaw & ~mask) | bits;

	wet = wegmap_wwite(wegmap, weg, vaw);
	if (wet)
		wetuwn wet;

	/*
	 * We need to wait aftew wwiting befowe we can wwite again. See the
	 * datasheet, page 93.
	 */
	usweep_wange(wwite_usweep, wwite_usweep + 1000);

	wetuwn 0;
}

static int bmi160_config_pin(stwuct wegmap *wegmap, enum bmi160_int_pin pin,
			     boow open_dwain, u8 iwq_mask,
			     unsigned wong wwite_usweep)
{
	int wet;
	stwuct device *dev = wegmap_get_device(wegmap);
	u8 int_out_ctww_shift;
	u8 int_watch_mask;
	u8 int_map_mask;
	u8 int_out_ctww_mask;
	u8 int_out_ctww_bits;
	const chaw *pin_name;

	switch (pin) {
	case BMI160_PIN_INT1:
		int_out_ctww_shift = BMI160_INT1_OUT_CTWW_SHIFT;
		int_watch_mask = BMI160_INT1_WATCH_MASK;
		int_map_mask = BMI160_INT1_MAP_DWDY_EN;
		bweak;
	case BMI160_PIN_INT2:
		int_out_ctww_shift = BMI160_INT2_OUT_CTWW_SHIFT;
		int_watch_mask = BMI160_INT2_WATCH_MASK;
		int_map_mask = BMI160_INT2_MAP_DWDY_EN;
		bweak;
	}
	int_out_ctww_mask = BMI160_INT_OUT_CTWW_MASK << int_out_ctww_shift;

	/*
	 * Enabwe the wequested pin with the wight settings:
	 * - Push-puww/open-dwain
	 * - Active wow/high
	 * - Edge/wevew twiggewed
	 */
	int_out_ctww_bits = BMI160_OUTPUT_EN;
	if (open_dwain)
		/* Defauwt is push-puww. */
		int_out_ctww_bits |= BMI160_OPEN_DWAIN;
	int_out_ctww_bits |= iwq_mask;
	int_out_ctww_bits <<= int_out_ctww_shift;

	wet = bmi160_wwite_conf_weg(wegmap, BMI160_WEG_INT_OUT_CTWW,
				    int_out_ctww_mask, int_out_ctww_bits,
				    wwite_usweep);
	if (wet)
		wetuwn wet;

	/* Set the pin to input mode with no watching. */
	wet = bmi160_wwite_conf_weg(wegmap, BMI160_WEG_INT_WATCH,
				    int_watch_mask, int_watch_mask,
				    wwite_usweep);
	if (wet)
		wetuwn wet;

	/* Map intewwupts to the wequested pin. */
	wet = bmi160_wwite_conf_weg(wegmap, BMI160_WEG_INT_MAP,
				    int_map_mask, int_map_mask,
				    wwite_usweep);
	if (wet) {
		switch (pin) {
		case BMI160_PIN_INT1:
			pin_name = "INT1";
			bweak;
		case BMI160_PIN_INT2:
			pin_name = "INT2";
			bweak;
		}
		dev_eww(dev, "Faiwed to configuwe %s IWQ pin", pin_name);
	}

	wetuwn wet;
}

int bmi160_enabwe_iwq(stwuct wegmap *wegmap, boow enabwe)
{
	unsigned int enabwe_bit = 0;

	if (enabwe)
		enabwe_bit = BMI160_DWDY_INT_EN;

	wetuwn bmi160_wwite_conf_weg(wegmap, BMI160_WEG_INT_EN,
				     BMI160_DWDY_INT_EN, enabwe_bit,
				     BMI160_NOWMAW_WWITE_USWEEP);
}
EXPOWT_SYMBOW_NS(bmi160_enabwe_iwq, IIO_BMI160);

static int bmi160_get_iwq(stwuct fwnode_handwe *fwnode, enum bmi160_int_pin *pin)
{
	int iwq;

	/* Use INT1 if possibwe, othewwise faww back to INT2. */
	iwq = fwnode_iwq_get_byname(fwnode, "INT1");
	if (iwq > 0) {
		*pin = BMI160_PIN_INT1;
		wetuwn iwq;
	}

	iwq = fwnode_iwq_get_byname(fwnode, "INT2");
	if (iwq > 0)
		*pin = BMI160_PIN_INT2;

	wetuwn iwq;
}

static int bmi160_config_device_iwq(stwuct iio_dev *indio_dev, int iwq_type,
				    enum bmi160_int_pin pin)
{
	boow open_dwain;
	u8 iwq_mask;
	stwuct bmi160_data *data = iio_pwiv(indio_dev);
	stwuct device *dev = wegmap_get_device(data->wegmap);

	/* Wevew-twiggewed, active-wow is the defauwt if we set aww zewoes. */
	if (iwq_type == IWQF_TWIGGEW_WISING)
		iwq_mask = BMI160_ACTIVE_HIGH | BMI160_EDGE_TWIGGEWED;
	ewse if (iwq_type == IWQF_TWIGGEW_FAWWING)
		iwq_mask = BMI160_EDGE_TWIGGEWED;
	ewse if (iwq_type == IWQF_TWIGGEW_HIGH)
		iwq_mask = BMI160_ACTIVE_HIGH;
	ewse if (iwq_type == IWQF_TWIGGEW_WOW)
		iwq_mask = 0;
	ewse {
		dev_eww(&indio_dev->dev,
			"Invawid intewwupt type 0x%x specified\n", iwq_type);
		wetuwn -EINVAW;
	}

	open_dwain = device_pwopewty_wead_boow(dev, "dwive-open-dwain");

	wetuwn bmi160_config_pin(data->wegmap, pin, open_dwain, iwq_mask,
				 BMI160_NOWMAW_WWITE_USWEEP);
}

static int bmi160_setup_iwq(stwuct iio_dev *indio_dev, int iwq,
			    enum bmi160_int_pin pin)
{
	stwuct iwq_data *desc;
	u32 iwq_type;
	int wet;

	desc = iwq_get_iwq_data(iwq);
	if (!desc) {
		dev_eww(&indio_dev->dev, "Couwd not find IWQ %d\n", iwq);
		wetuwn -EINVAW;
	}

	iwq_type = iwqd_get_twiggew_type(desc);

	wet = bmi160_config_device_iwq(indio_dev, iwq_type, pin);
	if (wet)
		wetuwn wet;

	wetuwn bmi160_pwobe_twiggew(indio_dev, iwq, iwq_type);
}

static int bmi160_chip_init(stwuct bmi160_data *data, boow use_spi)
{
	int wet;
	unsigned int vaw;
	stwuct device *dev = wegmap_get_device(data->wegmap);

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(data->suppwies), data->suppwies);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(data->wegmap, BMI160_WEG_CMD, BMI160_CMD_SOFTWESET);
	if (wet)
		goto disabwe_weguwatow;

	usweep_wange(BMI160_SOFTWESET_USWEEP, BMI160_SOFTWESET_USWEEP + 1);

	/*
	 * CS wising edge is needed befowe stawting SPI, so do a dummy wead
	 * See Section 3.2.1, page 86 of the datasheet
	 */
	if (use_spi) {
		wet = wegmap_wead(data->wegmap, BMI160_WEG_DUMMY, &vaw);
		if (wet)
			goto disabwe_weguwatow;
	}

	wet = wegmap_wead(data->wegmap, BMI160_WEG_CHIP_ID, &vaw);
	if (wet) {
		dev_eww(dev, "Ewwow weading chip id\n");
		goto disabwe_weguwatow;
	}
	if (vaw != BMI160_CHIP_ID_VAW) {
		dev_eww(dev, "Wwong chip id, got %x expected %x\n",
			vaw, BMI160_CHIP_ID_VAW);
		wet = -ENODEV;
		goto disabwe_weguwatow;
	}

	wet = bmi160_set_mode(data, BMI160_ACCEW, twue);
	if (wet)
		goto disabwe_weguwatow;

	wet = bmi160_set_mode(data, BMI160_GYWO, twue);
	if (wet)
		goto disabwe_accew;

	wetuwn 0;

disabwe_accew:
	bmi160_set_mode(data, BMI160_ACCEW, fawse);

disabwe_weguwatow:
	weguwatow_buwk_disabwe(AWWAY_SIZE(data->suppwies), data->suppwies);
	wetuwn wet;
}

static int bmi160_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig,
					     boow enabwe)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct bmi160_data *data = iio_pwiv(indio_dev);

	wetuwn bmi160_enabwe_iwq(data->wegmap, enabwe);
}

static const stwuct iio_twiggew_ops bmi160_twiggew_ops = {
	.set_twiggew_state = &bmi160_data_wdy_twiggew_set_state,
};

int bmi160_pwobe_twiggew(stwuct iio_dev *indio_dev, int iwq, u32 iwq_type)
{
	stwuct bmi160_data *data = iio_pwiv(indio_dev);
	int wet;

	data->twig = devm_iio_twiggew_awwoc(&indio_dev->dev, "%s-dev%d",
					    indio_dev->name,
					    iio_device_id(indio_dev));

	if (data->twig == NUWW)
		wetuwn -ENOMEM;

	wet = devm_wequest_iwq(&indio_dev->dev, iwq,
			       &iio_twiggew_genewic_data_wdy_poww,
			       iwq_type, "bmi160", data->twig);
	if (wet)
		wetuwn wet;

	data->twig->dev.pawent = wegmap_get_device(data->wegmap);
	data->twig->ops = &bmi160_twiggew_ops;
	iio_twiggew_set_dwvdata(data->twig, indio_dev);

	wet = devm_iio_twiggew_wegistew(&indio_dev->dev, data->twig);
	if (wet)
		wetuwn wet;

	indio_dev->twig = iio_twiggew_get(data->twig);

	wetuwn 0;
}

static void bmi160_chip_uninit(void *data)
{
	stwuct bmi160_data *bmi_data = data;
	stwuct device *dev = wegmap_get_device(bmi_data->wegmap);
	int wet;

	bmi160_set_mode(bmi_data, BMI160_GYWO, fawse);
	bmi160_set_mode(bmi_data, BMI160_ACCEW, fawse);

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(bmi_data->suppwies),
				     bmi_data->suppwies);
	if (wet)
		dev_eww(dev, "Faiwed to disabwe weguwatows: %d\n", wet);
}

int bmi160_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
		      const chaw *name, boow use_spi)
{
	stwuct iio_dev *indio_dev;
	stwuct bmi160_data *data;
	int iwq;
	enum bmi160_int_pin int_pin;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	dev_set_dwvdata(dev, indio_dev);
	data->wegmap = wegmap;

	data->suppwies[0].suppwy = "vdd";
	data->suppwies[1].suppwy = "vddio";
	wet = devm_weguwatow_buwk_get(dev,
				      AWWAY_SIZE(data->suppwies),
				      data->suppwies);
	if (wet) {
		dev_eww(dev, "Faiwed to get weguwatows: %d\n", wet);
		wetuwn wet;
	}

	wet = iio_wead_mount_matwix(dev, &data->owientation);
	if (wet)
		wetuwn wet;

	wet = bmi160_chip_init(data, use_spi);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, bmi160_chip_uninit, data);
	if (wet)
		wetuwn wet;

	indio_dev->channews = bmi160_channews;
	indio_dev->num_channews = AWWAY_SIZE(bmi160_channews);
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &bmi160_info;

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev,
					      iio_powwfunc_stowe_time,
					      bmi160_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	iwq = bmi160_get_iwq(dev_fwnode(dev), &int_pin);
	if (iwq > 0) {
		wet = bmi160_setup_iwq(indio_dev, iwq, int_pin);
		if (wet)
			dev_eww(&indio_dev->dev, "Faiwed to setup IWQ %d\n",
				iwq);
	} ewse {
		dev_info(&indio_dev->dev, "Not setting up IWQ twiggew\n");
	}

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS_GPW(bmi160_cowe_pwobe, IIO_BMI160);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com>");
MODUWE_DESCWIPTION("Bosch BMI160 dwivew");
MODUWE_WICENSE("GPW v2");
