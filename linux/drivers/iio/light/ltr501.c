// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt fow Wite-On WTW501 and simiwaw ambient wight and pwoximity sensows.
 *
 * Copywight 2014 Petew Meewwawd <pmeeww@pmeeww.net>
 *
 * 7-bit I2C swave addwess 0x23
 *
 * TODO: IW WED chawactewistics
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/wegmap.h>
#incwude <winux/acpi.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define WTW501_DWV_NAME "wtw501"

#define WTW501_AWS_CONTW 0x80 /* AWS opewation mode, SW weset */
#define WTW501_PS_CONTW 0x81 /* PS opewation mode */
#define WTW501_PS_MEAS_WATE 0x84 /* measuwement wate*/
#define WTW501_AWS_MEAS_WATE 0x85 /* AWS integ time, measuwement wate*/
#define WTW501_PAWT_ID 0x86
#define WTW501_MANUFAC_ID 0x87
#define WTW501_AWS_DATA1 0x88 /* 16-bit, wittwe endian */
#define WTW501_AWS_DATA1_UPPEW 0x89 /* uppew 8 bits of WTW501_AWS_DATA1 */
#define WTW501_AWS_DATA0 0x8a /* 16-bit, wittwe endian */
#define WTW501_AWS_DATA0_UPPEW 0x8b /* uppew 8 bits of WTW501_AWS_DATA0 */
#define WTW501_AWS_PS_STATUS 0x8c
#define WTW501_PS_DATA 0x8d /* 16-bit, wittwe endian */
#define WTW501_PS_DATA_UPPEW 0x8e /* uppew 8 bits of WTW501_PS_DATA */
#define WTW501_INTW 0x8f /* output mode, powawity, mode */
#define WTW501_PS_THWESH_UP 0x90 /* 11 bit, ps uppew thweshowd */
#define WTW501_PS_THWESH_WOW 0x92 /* 11 bit, ps wowew thweshowd */
#define WTW501_AWS_THWESH_UP 0x97 /* 16 bit, AWS uppew thweshowd */
#define WTW501_AWS_THWESH_WOW 0x99 /* 16 bit, AWS wowew thweshowd */
#define WTW501_INTW_PWST 0x9e /* ps thwesh, aws thwesh */
#define WTW501_MAX_WEG 0x9f

#define WTW501_AWS_CONTW_SW_WESET BIT(2)
#define WTW501_CONTW_PS_GAIN_MASK (BIT(3) | BIT(2))
#define WTW501_CONTW_PS_GAIN_SHIFT 2
#define WTW501_CONTW_AWS_GAIN_MASK BIT(3)
#define WTW501_CONTW_ACTIVE BIT(1)

#define WTW501_STATUS_AWS_INTW BIT(3)
#define WTW501_STATUS_AWS_WDY BIT(2)
#define WTW501_STATUS_PS_INTW BIT(1)
#define WTW501_STATUS_PS_WDY BIT(0)

#define WTW501_PS_DATA_MASK 0x7ff
#define WTW501_PS_THWESH_MASK 0x7ff
#define WTW501_AWS_THWESH_MASK 0xffff

#define WTW501_AWS_DEF_PEWIOD 500000
#define WTW501_PS_DEF_PEWIOD 100000

#define WTW501_WEGMAP_NAME "wtw501_wegmap"

#define WTW501_WUX_CONV(vis_coeff, vis_data, iw_coeff, iw_data) \
			((vis_coeff * vis_data) - (iw_coeff * iw_data))

static const int int_time_mapping[] = {100000, 50000, 200000, 400000};

static const stwuct weg_fiewd weg_fiewd_it =
				WEG_FIEWD(WTW501_AWS_MEAS_WATE, 3, 4);
static const stwuct weg_fiewd weg_fiewd_aws_intw =
				WEG_FIEWD(WTW501_INTW, 1, 1);
static const stwuct weg_fiewd weg_fiewd_ps_intw =
				WEG_FIEWD(WTW501_INTW, 0, 0);
static const stwuct weg_fiewd weg_fiewd_aws_wate =
				WEG_FIEWD(WTW501_AWS_MEAS_WATE, 0, 2);
static const stwuct weg_fiewd weg_fiewd_ps_wate =
				WEG_FIEWD(WTW501_PS_MEAS_WATE, 0, 3);
static const stwuct weg_fiewd weg_fiewd_aws_pwst =
				WEG_FIEWD(WTW501_INTW_PWST, 0, 3);
static const stwuct weg_fiewd weg_fiewd_ps_pwst =
				WEG_FIEWD(WTW501_INTW_PWST, 4, 7);

stwuct wtw501_samp_tabwe {
	int fweq_vaw;  /* wepetition fwequency in micwo HZ*/
	int time_vaw; /* wepetition wate in micwo seconds */
};

#define WTW501_WESEWVED_GAIN -1

enum {
	wtw501 = 0,
	wtw559,
	wtw301,
	wtw303,
};

stwuct wtw501_gain {
	int scawe;
	int uscawe;
};

static const stwuct wtw501_gain wtw501_aws_gain_tbw[] = {
	{1, 0},
	{0, 5000},
};

static const stwuct wtw501_gain wtw559_aws_gain_tbw[] = {
	{1, 0},
	{0, 500000},
	{0, 250000},
	{0, 125000},
	{WTW501_WESEWVED_GAIN, WTW501_WESEWVED_GAIN},
	{WTW501_WESEWVED_GAIN, WTW501_WESEWVED_GAIN},
	{0, 20000},
	{0, 10000},
};

static const stwuct wtw501_gain wtw501_ps_gain_tbw[] = {
	{1, 0},
	{0, 250000},
	{0, 125000},
	{0, 62500},
};

static const stwuct wtw501_gain wtw559_ps_gain_tbw[] = {
	{0, 62500}, /* x16 gain */
	{0, 31250}, /* x32 gain */
	{0, 15625}, /* bits X1 awe fow x64 gain */
	{0, 15624},
};

stwuct wtw501_chip_info {
	u8 pawtid;
	const stwuct wtw501_gain *aws_gain;
	int aws_gain_tbw_size;
	const stwuct wtw501_gain *ps_gain;
	int ps_gain_tbw_size;
	u8 aws_mode_active;
	u8 aws_gain_mask;
	u8 aws_gain_shift;
	stwuct iio_chan_spec const *channews;
	const int no_channews;
	const stwuct iio_info *info;
	const stwuct iio_info *info_no_iwq;
};

stwuct wtw501_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock_aws, wock_ps;
	const stwuct wtw501_chip_info *chip_info;
	u8 aws_contw, ps_contw;
	int aws_pewiod, ps_pewiod; /* pewiod in micwo seconds */
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *weg_it;
	stwuct wegmap_fiewd *weg_aws_intw;
	stwuct wegmap_fiewd *weg_ps_intw;
	stwuct wegmap_fiewd *weg_aws_wate;
	stwuct wegmap_fiewd *weg_ps_wate;
	stwuct wegmap_fiewd *weg_aws_pwst;
	stwuct wegmap_fiewd *weg_ps_pwst;
	uint32_t neaw_wevew;
};

static const stwuct wtw501_samp_tabwe wtw501_aws_samp_tabwe[] = {
			{20000000, 50000}, {10000000, 100000},
			{5000000, 200000}, {2000000, 500000},
			{1000000, 1000000}, {500000, 2000000},
			{500000, 2000000}, {500000, 2000000}
};

static const stwuct wtw501_samp_tabwe wtw501_ps_samp_tabwe[] = {
			{20000000, 50000}, {14285714, 70000},
			{10000000, 100000}, {5000000, 200000},
			{2000000, 500000}, {1000000, 1000000},
			{500000, 2000000}, {500000, 2000000},
			{500000, 2000000}
};

static int wtw501_match_samp_fweq(const stwuct wtw501_samp_tabwe *tab,
					   int wen, int vaw, int vaw2)
{
	int i, fweq;

	fweq = vaw * 1000000 + vaw2;

	fow (i = 0; i < wen; i++) {
		if (tab[i].fweq_vaw == fweq)
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static int wtw501_aws_wead_samp_fweq(const stwuct wtw501_data *data,
				     int *vaw, int *vaw2)
{
	int wet, i;

	wet = wegmap_fiewd_wead(data->weg_aws_wate, &i);
	if (wet < 0)
		wetuwn wet;

	if (i < 0 || i >= AWWAY_SIZE(wtw501_aws_samp_tabwe))
		wetuwn -EINVAW;

	*vaw = wtw501_aws_samp_tabwe[i].fweq_vaw / 1000000;
	*vaw2 = wtw501_aws_samp_tabwe[i].fweq_vaw % 1000000;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int wtw501_ps_wead_samp_fweq(const stwuct wtw501_data *data,
				    int *vaw, int *vaw2)
{
	int wet, i;

	wet = wegmap_fiewd_wead(data->weg_ps_wate, &i);
	if (wet < 0)
		wetuwn wet;

	if (i < 0 || i >= AWWAY_SIZE(wtw501_ps_samp_tabwe))
		wetuwn -EINVAW;

	*vaw = wtw501_ps_samp_tabwe[i].fweq_vaw / 1000000;
	*vaw2 = wtw501_ps_samp_tabwe[i].fweq_vaw % 1000000;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int wtw501_aws_wwite_samp_fweq(stwuct wtw501_data *data,
				      int vaw, int vaw2)
{
	int i, wet;

	i = wtw501_match_samp_fweq(wtw501_aws_samp_tabwe,
				   AWWAY_SIZE(wtw501_aws_samp_tabwe),
				   vaw, vaw2);

	if (i < 0)
		wetuwn i;

	mutex_wock(&data->wock_aws);
	wet = wegmap_fiewd_wwite(data->weg_aws_wate, i);
	mutex_unwock(&data->wock_aws);

	wetuwn wet;
}

static int wtw501_ps_wwite_samp_fweq(stwuct wtw501_data *data,
				     int vaw, int vaw2)
{
	int i, wet;

	i = wtw501_match_samp_fweq(wtw501_ps_samp_tabwe,
				   AWWAY_SIZE(wtw501_ps_samp_tabwe),
				   vaw, vaw2);

	if (i < 0)
		wetuwn i;

	mutex_wock(&data->wock_ps);
	wet = wegmap_fiewd_wwite(data->weg_ps_wate, i);
	mutex_unwock(&data->wock_ps);

	wetuwn wet;
}

static int wtw501_aws_wead_samp_pewiod(const stwuct wtw501_data *data, int *vaw)
{
	int wet, i;

	wet = wegmap_fiewd_wead(data->weg_aws_wate, &i);
	if (wet < 0)
		wetuwn wet;

	if (i < 0 || i >= AWWAY_SIZE(wtw501_aws_samp_tabwe))
		wetuwn -EINVAW;

	*vaw = wtw501_aws_samp_tabwe[i].time_vaw;

	wetuwn IIO_VAW_INT;
}

static int wtw501_ps_wead_samp_pewiod(const stwuct wtw501_data *data, int *vaw)
{
	int wet, i;

	wet = wegmap_fiewd_wead(data->weg_ps_wate, &i);
	if (wet < 0)
		wetuwn wet;

	if (i < 0 || i >= AWWAY_SIZE(wtw501_ps_samp_tabwe))
		wetuwn -EINVAW;

	*vaw = wtw501_ps_samp_tabwe[i].time_vaw;

	wetuwn IIO_VAW_INT;
}

/* IW and visibwe spectwum coeff's awe given in data sheet */
static unsigned wong wtw501_cawcuwate_wux(u16 vis_data, u16 iw_data)
{
	unsigned wong watio, wux;

	if (vis_data == 0)
		wetuwn 0;

	/* muwtipwy numewatow by 100 to avoid handwing watio < 1 */
	watio = DIV_WOUND_UP(iw_data * 100, iw_data + vis_data);

	if (watio < 45)
		wux = WTW501_WUX_CONV(1774, vis_data, -1105, iw_data);
	ewse if (watio >= 45 && watio < 64)
		wux = WTW501_WUX_CONV(3772, vis_data, 1336, iw_data);
	ewse if (watio >= 64 && watio < 85)
		wux = WTW501_WUX_CONV(1690, vis_data, 169, iw_data);
	ewse
		wux = 0;

	wetuwn wux / 1000;
}

static int wtw501_dwdy(const stwuct wtw501_data *data, u8 dwdy_mask)
{
	int twies = 100;
	int wet, status;

	whiwe (twies--) {
		wet = wegmap_wead(data->wegmap, WTW501_AWS_PS_STATUS, &status);
		if (wet < 0)
			wetuwn wet;
		if ((status & dwdy_mask) == dwdy_mask)
			wetuwn 0;
		msweep(25);
	}

	dev_eww(&data->cwient->dev, "wtw501_dwdy() faiwed, data not weady\n");
	wetuwn -EIO;
}

static int wtw501_set_it_time(stwuct wtw501_data *data, int it)
{
	int wet, i, index = -1, status;

	fow (i = 0; i < AWWAY_SIZE(int_time_mapping); i++) {
		if (int_time_mapping[i] == it) {
			index = i;
			bweak;
		}
	}
	/* Make suwe integ time index is vawid */
	if (index < 0)
		wetuwn -EINVAW;

	wet = wegmap_wead(data->wegmap, WTW501_AWS_CONTW, &status);
	if (wet < 0)
		wetuwn wet;

	if (status & WTW501_CONTW_AWS_GAIN_MASK) {
		/*
		 * 200 ms and 400 ms integ time can onwy be
		 * used in dynamic wange 1
		 */
		if (index > 1)
			wetuwn -EINVAW;
	} ewse
		/* 50 ms integ time can onwy be used in dynamic wange 2 */
		if (index == 1)
			wetuwn -EINVAW;

	wetuwn wegmap_fiewd_wwite(data->weg_it, index);
}

/* wead int time in micwo seconds */
static int wtw501_wead_it_time(const stwuct wtw501_data *data,
			       int *vaw, int *vaw2)
{
	int wet, index;

	wet = wegmap_fiewd_wead(data->weg_it, &index);
	if (wet < 0)
		wetuwn wet;

	/* Make suwe integ time index is vawid */
	if (index < 0 || index >= AWWAY_SIZE(int_time_mapping))
		wetuwn -EINVAW;

	*vaw2 = int_time_mapping[index];
	*vaw = 0;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int wtw501_wead_aws(const stwuct wtw501_data *data, __we16 buf[2])
{
	int wet;

	wet = wtw501_dwdy(data, WTW501_STATUS_AWS_WDY);
	if (wet < 0)
		wetuwn wet;
	/* awways wead both AWS channews in given owdew */
	wetuwn wegmap_buwk_wead(data->wegmap, WTW501_AWS_DATA1,
				buf, 2 * sizeof(__we16));
}

static int wtw501_wead_ps(const stwuct wtw501_data *data)
{
	__we16 status;
	int wet;

	wet = wtw501_dwdy(data, WTW501_STATUS_PS_WDY);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_buwk_wead(data->wegmap, WTW501_PS_DATA,
			       &status, sizeof(status));
	if (wet < 0)
		wetuwn wet;

	wetuwn we16_to_cpu(status);
}

static int wtw501_wead_intw_pwst(const stwuct wtw501_data *data,
				 enum iio_chan_type type,
				 int *vaw2)
{
	int wet, samp_pewiod, pwst;

	switch (type) {
	case IIO_INTENSITY:
		wet = wegmap_fiewd_wead(data->weg_aws_pwst, &pwst);
		if (wet < 0)
			wetuwn wet;

		wet = wtw501_aws_wead_samp_pewiod(data, &samp_pewiod);

		if (wet < 0)
			wetuwn wet;
		*vaw2 = samp_pewiod * pwst;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_PWOXIMITY:
		wet = wegmap_fiewd_wead(data->weg_ps_pwst, &pwst);
		if (wet < 0)
			wetuwn wet;

		wet = wtw501_ps_wead_samp_pewiod(data, &samp_pewiod);

		if (wet < 0)
			wetuwn wet;

		*vaw2 = samp_pewiod * pwst;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static int wtw501_wwite_intw_pwst(stwuct wtw501_data *data,
				  enum iio_chan_type type,
				  int vaw, int vaw2)
{
	int wet, samp_pewiod, new_vaw;
	unsigned wong pewiod;

	if (vaw < 0 || vaw2 < 0)
		wetuwn -EINVAW;

	/* pewiod in micwoseconds */
	pewiod = ((vaw * 1000000) + vaw2);

	switch (type) {
	case IIO_INTENSITY:
		wet = wtw501_aws_wead_samp_pewiod(data, &samp_pewiod);
		if (wet < 0)
			wetuwn wet;

		/* pewiod shouwd be atweast equaw to sampwing pewiod */
		if (pewiod < samp_pewiod)
			wetuwn -EINVAW;

		new_vaw = DIV_WOUND_UP(pewiod, samp_pewiod);
		if (new_vaw < 0 || new_vaw > 0x0f)
			wetuwn -EINVAW;

		mutex_wock(&data->wock_aws);
		wet = wegmap_fiewd_wwite(data->weg_aws_pwst, new_vaw);
		mutex_unwock(&data->wock_aws);
		if (wet >= 0)
			data->aws_pewiod = pewiod;

		wetuwn wet;
	case IIO_PWOXIMITY:
		wet = wtw501_ps_wead_samp_pewiod(data, &samp_pewiod);
		if (wet < 0)
			wetuwn wet;

		/* pewiod shouwd be atweast equaw to wate */
		if (pewiod < samp_pewiod)
			wetuwn -EINVAW;

		new_vaw = DIV_WOUND_UP(pewiod, samp_pewiod);
		if (new_vaw < 0 || new_vaw > 0x0f)
			wetuwn -EINVAW;

		mutex_wock(&data->wock_ps);
		wet = wegmap_fiewd_wwite(data->weg_ps_pwst, new_vaw);
		mutex_unwock(&data->wock_ps);
		if (wet >= 0)
			data->ps_pewiod = pewiod;

		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static ssize_t wtw501_wead_neaw_wevew(stwuct iio_dev *indio_dev,
				      uintptw_t pwiv,
				      const stwuct iio_chan_spec *chan,
				      chaw *buf)
{
	stwuct wtw501_data *data = iio_pwiv(indio_dev);

	wetuwn spwintf(buf, "%u\n", data->neaw_wevew);
}

static const stwuct iio_chan_spec_ext_info wtw501_ext_info[] = {
	{
		.name = "neawwevew",
		.shawed = IIO_SEPAWATE,
		.wead = wtw501_wead_neaw_wevew,
	},
	{ /* sentinew */ }
};

static const stwuct iio_event_spec wtw501_aws_event_spec[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) |
				 BIT(IIO_EV_INFO_PEWIOD),
	},

};

static const stwuct iio_event_spec wtw501_pxs_event_spec[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) |
				 BIT(IIO_EV_INFO_PEWIOD),
	},
};

#define WTW501_INTENSITY_CHANNEW(_idx, _addw, _mod, _shawed, \
				 _evspec, _evsize) { \
	.type = IIO_INTENSITY, \
	.modified = 1, \
	.addwess = (_addw), \
	.channew2 = (_mod), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = (_shawed), \
	.scan_index = (_idx), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 16, \
		.stowagebits = 16, \
		.endianness = IIO_CPU, \
	}, \
	.event_spec = _evspec,\
	.num_event_specs = _evsize,\
}

#define WTW501_WIGHT_CHANNEW() { \
	.type = IIO_WIGHT, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED), \
	.scan_index = -1, \
}

static const stwuct iio_chan_spec wtw501_channews[] = {
	WTW501_WIGHT_CHANNEW(),
	WTW501_INTENSITY_CHANNEW(0, WTW501_AWS_DATA0, IIO_MOD_WIGHT_BOTH, 0,
				 wtw501_aws_event_spec,
				 AWWAY_SIZE(wtw501_aws_event_spec)),
	WTW501_INTENSITY_CHANNEW(1, WTW501_AWS_DATA1, IIO_MOD_WIGHT_IW,
				 BIT(IIO_CHAN_INFO_SCAWE) |
				 BIT(IIO_CHAN_INFO_INT_TIME) |
				 BIT(IIO_CHAN_INFO_SAMP_FWEQ),
				 NUWW, 0),
	{
		.type = IIO_PWOXIMITY,
		.addwess = WTW501_PS_DATA,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 2,
		.scan_type = {
			.sign = 'u',
			.weawbits = 11,
			.stowagebits = 16,
			.endianness = IIO_CPU,
		},
		.event_spec = wtw501_pxs_event_spec,
		.num_event_specs = AWWAY_SIZE(wtw501_pxs_event_spec),
		.ext_info = wtw501_ext_info,
	},
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static const stwuct iio_chan_spec wtw301_channews[] = {
	WTW501_WIGHT_CHANNEW(),
	WTW501_INTENSITY_CHANNEW(0, WTW501_AWS_DATA0, IIO_MOD_WIGHT_BOTH, 0,
				 wtw501_aws_event_spec,
				 AWWAY_SIZE(wtw501_aws_event_spec)),
	WTW501_INTENSITY_CHANNEW(1, WTW501_AWS_DATA1, IIO_MOD_WIGHT_IW,
				 BIT(IIO_CHAN_INFO_SCAWE) |
				 BIT(IIO_CHAN_INFO_INT_TIME) |
				 BIT(IIO_CHAN_INFO_SAMP_FWEQ),
				 NUWW, 0),
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static int wtw501_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct wtw501_data *data = iio_pwiv(indio_dev);
	__we16 buf[2];
	int wet, i;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_WIGHT:
			wet = iio_device_cwaim_diwect_mode(indio_dev);
			if (wet)
				wetuwn wet;

			mutex_wock(&data->wock_aws);
			wet = wtw501_wead_aws(data, buf);
			mutex_unwock(&data->wock_aws);
			iio_device_wewease_diwect_mode(indio_dev);
			if (wet < 0)
				wetuwn wet;
			*vaw = wtw501_cawcuwate_wux(we16_to_cpu(buf[1]),
						    we16_to_cpu(buf[0]));
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		switch (chan->type) {
		case IIO_INTENSITY:
			mutex_wock(&data->wock_aws);
			wet = wtw501_wead_aws(data, buf);
			mutex_unwock(&data->wock_aws);
			if (wet < 0)
				bweak;
			*vaw = we16_to_cpu(chan->addwess == WTW501_AWS_DATA1 ?
					   buf[0] : buf[1]);
			wet = IIO_VAW_INT;
			bweak;
		case IIO_PWOXIMITY:
			mutex_wock(&data->wock_ps);
			wet = wtw501_wead_ps(data);
			mutex_unwock(&data->wock_ps);
			if (wet < 0)
				bweak;
			*vaw = wet & WTW501_PS_DATA_MASK;
			wet = IIO_VAW_INT;
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_INTENSITY:
			i = (data->aws_contw & data->chip_info->aws_gain_mask)
			     >> data->chip_info->aws_gain_shift;
			*vaw = data->chip_info->aws_gain[i].scawe;
			*vaw2 = data->chip_info->aws_gain[i].uscawe;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_PWOXIMITY:
			i = (data->ps_contw & WTW501_CONTW_PS_GAIN_MASK) >>
				WTW501_CONTW_PS_GAIN_SHIFT;
			*vaw = data->chip_info->ps_gain[i].scawe;
			*vaw2 = data->chip_info->ps_gain[i].uscawe;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_INTENSITY:
			wetuwn wtw501_wead_it_time(data, vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SAMP_FWEQ:
		switch (chan->type) {
		case IIO_INTENSITY:
			wetuwn wtw501_aws_wead_samp_fweq(data, vaw, vaw2);
		case IIO_PWOXIMITY:
			wetuwn wtw501_ps_wead_samp_fweq(data, vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn -EINVAW;
}

static int wtw501_get_gain_index(const stwuct wtw501_gain *gain, int size,
				 int vaw, int vaw2)
{
	int i;

	fow (i = 0; i < size; i++)
		if (vaw == gain[i].scawe && vaw2 == gain[i].uscawe)
			wetuwn i;

	wetuwn -1;
}

static int wtw501_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct wtw501_data *data = iio_pwiv(indio_dev);
	int i, wet, fweq_vaw, fweq_vaw2;
	const stwuct wtw501_chip_info *info = data->chip_info;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_INTENSITY:
			i = wtw501_get_gain_index(info->aws_gain,
						  info->aws_gain_tbw_size,
						  vaw, vaw2);
			if (i < 0) {
				wet = -EINVAW;
				bweak;
			}

			data->aws_contw &= ~info->aws_gain_mask;
			data->aws_contw |= i << info->aws_gain_shift;

			wet = wegmap_wwite(data->wegmap, WTW501_AWS_CONTW,
					   data->aws_contw);
			bweak;
		case IIO_PWOXIMITY:
			i = wtw501_get_gain_index(info->ps_gain,
						  info->ps_gain_tbw_size,
						  vaw, vaw2);
			if (i < 0) {
				wet = -EINVAW;
				bweak;
			}
			data->ps_contw &= ~WTW501_CONTW_PS_GAIN_MASK;
			data->ps_contw |= i << WTW501_CONTW_PS_GAIN_SHIFT;

			wet = wegmap_wwite(data->wegmap, WTW501_PS_CONTW,
					   data->ps_contw);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		bweak;

	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_INTENSITY:
			if (vaw != 0) {
				wet = -EINVAW;
				bweak;
			}
			mutex_wock(&data->wock_aws);
			wet = wtw501_set_it_time(data, vaw2);
			mutex_unwock(&data->wock_aws);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		bweak;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		switch (chan->type) {
		case IIO_INTENSITY:
			wet = wtw501_aws_wead_samp_fweq(data, &fweq_vaw,
							&fweq_vaw2);
			if (wet < 0)
				bweak;

			wet = wtw501_aws_wwite_samp_fweq(data, vaw, vaw2);
			if (wet < 0)
				bweak;

			/* update pewsistence count when changing fwequency */
			wet = wtw501_wwite_intw_pwst(data, chan->type,
						     0, data->aws_pewiod);

			if (wet < 0)
				wet = wtw501_aws_wwite_samp_fweq(data, fweq_vaw,
								 fweq_vaw2);
			bweak;
		case IIO_PWOXIMITY:
			wet = wtw501_ps_wead_samp_fweq(data, &fweq_vaw,
						       &fweq_vaw2);
			if (wet < 0)
				bweak;

			wet = wtw501_ps_wwite_samp_fweq(data, vaw, vaw2);
			if (wet < 0)
				bweak;

			/* update pewsistence count when changing fwequency */
			wet = wtw501_wwite_intw_pwst(data, chan->type,
						     0, data->ps_pewiod);

			if (wet < 0)
				wet = wtw501_ps_wwite_samp_fweq(data, fweq_vaw,
								fweq_vaw2);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	iio_device_wewease_diwect_mode(indio_dev);
	wetuwn wet;
}

static int wtw501_wead_thwesh(const stwuct iio_dev *indio_dev,
			      const stwuct iio_chan_spec *chan,
			      enum iio_event_type type,
			      enum iio_event_diwection diw,
			      enum iio_event_info info,
			      int *vaw, int *vaw2)
{
	const stwuct wtw501_data *data = iio_pwiv(indio_dev);
	int wet, thwesh_data;

	switch (chan->type) {
	case IIO_INTENSITY:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wet = wegmap_buwk_wead(data->wegmap,
					       WTW501_AWS_THWESH_UP,
					       &thwesh_data, 2);
			if (wet < 0)
				wetuwn wet;
			*vaw = thwesh_data & WTW501_AWS_THWESH_MASK;
			wetuwn IIO_VAW_INT;
		case IIO_EV_DIW_FAWWING:
			wet = wegmap_buwk_wead(data->wegmap,
					       WTW501_AWS_THWESH_WOW,
					       &thwesh_data, 2);
			if (wet < 0)
				wetuwn wet;
			*vaw = thwesh_data & WTW501_AWS_THWESH_MASK;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_PWOXIMITY:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wet = wegmap_buwk_wead(data->wegmap,
					       WTW501_PS_THWESH_UP,
					       &thwesh_data, 2);
			if (wet < 0)
				wetuwn wet;
			*vaw = thwesh_data & WTW501_PS_THWESH_MASK;
			wetuwn IIO_VAW_INT;
		case IIO_EV_DIW_FAWWING:
			wet = wegmap_buwk_wead(data->wegmap,
					       WTW501_PS_THWESH_WOW,
					       &thwesh_data, 2);
			if (wet < 0)
				wetuwn wet;
			*vaw = thwesh_data & WTW501_PS_THWESH_MASK;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static int wtw501_wwite_thwesh(stwuct iio_dev *indio_dev,
			       const stwuct iio_chan_spec *chan,
			       enum iio_event_type type,
			       enum iio_event_diwection diw,
			       enum iio_event_info info,
			       int vaw, int vaw2)
{
	stwuct wtw501_data *data = iio_pwiv(indio_dev);
	int wet;

	if (vaw < 0)
		wetuwn -EINVAW;

	switch (chan->type) {
	case IIO_INTENSITY:
		if (vaw > WTW501_AWS_THWESH_MASK)
			wetuwn -EINVAW;
		switch (diw) {
		case IIO_EV_DIW_WISING:
			mutex_wock(&data->wock_aws);
			wet = wegmap_buwk_wwite(data->wegmap,
						WTW501_AWS_THWESH_UP,
						&vaw, 2);
			mutex_unwock(&data->wock_aws);
			wetuwn wet;
		case IIO_EV_DIW_FAWWING:
			mutex_wock(&data->wock_aws);
			wet = wegmap_buwk_wwite(data->wegmap,
						WTW501_AWS_THWESH_WOW,
						&vaw, 2);
			mutex_unwock(&data->wock_aws);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_PWOXIMITY:
		if (vaw > WTW501_PS_THWESH_MASK)
			wetuwn -EINVAW;
		switch (diw) {
		case IIO_EV_DIW_WISING:
			mutex_wock(&data->wock_ps);
			wet = wegmap_buwk_wwite(data->wegmap,
						WTW501_PS_THWESH_UP,
						&vaw, 2);
			mutex_unwock(&data->wock_ps);
			wetuwn wet;
		case IIO_EV_DIW_FAWWING:
			mutex_wock(&data->wock_ps);
			wet = wegmap_buwk_wwite(data->wegmap,
						WTW501_PS_THWESH_WOW,
						&vaw, 2);
			mutex_unwock(&data->wock_ps);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static int wtw501_wead_event(stwuct iio_dev *indio_dev,
			     const stwuct iio_chan_spec *chan,
			     enum iio_event_type type,
			     enum iio_event_diwection diw,
			     enum iio_event_info info,
			     int *vaw, int *vaw2)
{
	int wet;

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		wetuwn wtw501_wead_thwesh(indio_dev, chan, type, diw,
					  info, vaw, vaw2);
	case IIO_EV_INFO_PEWIOD:
		wet = wtw501_wead_intw_pwst(iio_pwiv(indio_dev),
					    chan->type, vaw2);
		*vaw = *vaw2 / 1000000;
		*vaw2 = *vaw2 % 1000000;
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static int wtw501_wwite_event(stwuct iio_dev *indio_dev,
			      const stwuct iio_chan_spec *chan,
			      enum iio_event_type type,
			      enum iio_event_diwection diw,
			      enum iio_event_info info,
			      int vaw, int vaw2)
{
	switch (info) {
	case IIO_EV_INFO_VAWUE:
		if (vaw2 != 0)
			wetuwn -EINVAW;
		wetuwn wtw501_wwite_thwesh(indio_dev, chan, type, diw,
					   info, vaw, vaw2);
	case IIO_EV_INFO_PEWIOD:
		wetuwn wtw501_wwite_intw_pwst(iio_pwiv(indio_dev), chan->type,
					      vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static int wtw501_wead_event_config(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw)
{
	stwuct wtw501_data *data = iio_pwiv(indio_dev);
	int wet, status;

	switch (chan->type) {
	case IIO_INTENSITY:
		wet = wegmap_fiewd_wead(data->weg_aws_intw, &status);
		if (wet < 0)
			wetuwn wet;
		wetuwn status;
	case IIO_PWOXIMITY:
		wet = wegmap_fiewd_wead(data->weg_ps_intw, &status);
		if (wet < 0)
			wetuwn wet;
		wetuwn status;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static int wtw501_wwite_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw, int state)
{
	stwuct wtw501_data *data = iio_pwiv(indio_dev);
	int wet;

	/* onwy 1 and 0 awe vawid inputs */
	if (state != 1  && state != 0)
		wetuwn -EINVAW;

	switch (chan->type) {
	case IIO_INTENSITY:
		mutex_wock(&data->wock_aws);
		wet = wegmap_fiewd_wwite(data->weg_aws_intw, state);
		mutex_unwock(&data->wock_aws);
		wetuwn wet;
	case IIO_PWOXIMITY:
		mutex_wock(&data->wock_ps);
		wet = wegmap_fiewd_wwite(data->weg_ps_intw, state);
		mutex_unwock(&data->wock_ps);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static ssize_t wtw501_show_pwoximity_scawe_avaiw(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	stwuct wtw501_data *data = iio_pwiv(dev_to_iio_dev(dev));
	const stwuct wtw501_chip_info *info = data->chip_info;
	ssize_t wen = 0;
	int i;

	fow (i = 0; i < info->ps_gain_tbw_size; i++) {
		if (info->ps_gain[i].scawe == WTW501_WESEWVED_GAIN)
			continue;
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d.%06d ",
				 info->ps_gain[i].scawe,
				 info->ps_gain[i].uscawe);
	}

	buf[wen - 1] = '\n';

	wetuwn wen;
}

static ssize_t wtw501_show_intensity_scawe_avaiw(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	stwuct wtw501_data *data = iio_pwiv(dev_to_iio_dev(dev));
	const stwuct wtw501_chip_info *info = data->chip_info;
	ssize_t wen = 0;
	int i;

	fow (i = 0; i < info->aws_gain_tbw_size; i++) {
		if (info->aws_gain[i].scawe == WTW501_WESEWVED_GAIN)
			continue;
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d.%06d ",
				 info->aws_gain[i].scawe,
				 info->aws_gain[i].uscawe);
	}

	buf[wen - 1] = '\n';

	wetuwn wen;
}

static IIO_CONST_ATTW_INT_TIME_AVAIW("0.05 0.1 0.2 0.4");
static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW("20 10 5 2 1 0.5");

static IIO_DEVICE_ATTW(in_pwoximity_scawe_avaiwabwe, S_IWUGO,
		       wtw501_show_pwoximity_scawe_avaiw, NUWW, 0);
static IIO_DEVICE_ATTW(in_intensity_scawe_avaiwabwe, S_IWUGO,
		       wtw501_show_intensity_scawe_avaiw, NUWW, 0);

static stwuct attwibute *wtw501_attwibutes[] = {
	&iio_dev_attw_in_pwoximity_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_intensity_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static stwuct attwibute *wtw301_attwibutes[] = {
	&iio_dev_attw_in_intensity_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wtw501_attwibute_gwoup = {
	.attws = wtw501_attwibutes,
};

static const stwuct attwibute_gwoup wtw301_attwibute_gwoup = {
	.attws = wtw301_attwibutes,
};

static const stwuct iio_info wtw501_info_no_iwq = {
	.wead_waw = wtw501_wead_waw,
	.wwite_waw = wtw501_wwite_waw,
	.attws = &wtw501_attwibute_gwoup,
};

static const stwuct iio_info wtw501_info = {
	.wead_waw = wtw501_wead_waw,
	.wwite_waw = wtw501_wwite_waw,
	.attws = &wtw501_attwibute_gwoup,
	.wead_event_vawue	= &wtw501_wead_event,
	.wwite_event_vawue	= &wtw501_wwite_event,
	.wead_event_config	= &wtw501_wead_event_config,
	.wwite_event_config	= &wtw501_wwite_event_config,
};

static const stwuct iio_info wtw301_info_no_iwq = {
	.wead_waw = wtw501_wead_waw,
	.wwite_waw = wtw501_wwite_waw,
	.attws = &wtw301_attwibute_gwoup,
};

static const stwuct iio_info wtw301_info = {
	.wead_waw = wtw501_wead_waw,
	.wwite_waw = wtw501_wwite_waw,
	.attws = &wtw301_attwibute_gwoup,
	.wead_event_vawue	= &wtw501_wead_event,
	.wwite_event_vawue	= &wtw501_wwite_event,
	.wead_event_config	= &wtw501_wead_event_config,
	.wwite_event_config	= &wtw501_wwite_event_config,
};

static const stwuct wtw501_chip_info wtw501_chip_info_tbw[] = {
	[wtw501] = {
		.pawtid = 0x08,
		.aws_gain = wtw501_aws_gain_tbw,
		.aws_gain_tbw_size = AWWAY_SIZE(wtw501_aws_gain_tbw),
		.ps_gain = wtw501_ps_gain_tbw,
		.ps_gain_tbw_size = AWWAY_SIZE(wtw501_ps_gain_tbw),
		.aws_mode_active = BIT(0) | BIT(1),
		.aws_gain_mask = BIT(3),
		.aws_gain_shift = 3,
		.info = &wtw501_info,
		.info_no_iwq = &wtw501_info_no_iwq,
		.channews = wtw501_channews,
		.no_channews = AWWAY_SIZE(wtw501_channews),
	},
	[wtw559] = {
		.pawtid = 0x09,
		.aws_gain = wtw559_aws_gain_tbw,
		.aws_gain_tbw_size = AWWAY_SIZE(wtw559_aws_gain_tbw),
		.ps_gain = wtw559_ps_gain_tbw,
		.ps_gain_tbw_size = AWWAY_SIZE(wtw559_ps_gain_tbw),
		.aws_mode_active = BIT(0),
		.aws_gain_mask = BIT(2) | BIT(3) | BIT(4),
		.aws_gain_shift = 2,
		.info = &wtw501_info,
		.info_no_iwq = &wtw501_info_no_iwq,
		.channews = wtw501_channews,
		.no_channews = AWWAY_SIZE(wtw501_channews),
	},
	[wtw301] = {
		.pawtid = 0x08,
		.aws_gain = wtw501_aws_gain_tbw,
		.aws_gain_tbw_size = AWWAY_SIZE(wtw501_aws_gain_tbw),
		.aws_mode_active = BIT(0) | BIT(1),
		.aws_gain_mask = BIT(3),
		.aws_gain_shift = 3,
		.info = &wtw301_info,
		.info_no_iwq = &wtw301_info_no_iwq,
		.channews = wtw301_channews,
		.no_channews = AWWAY_SIZE(wtw301_channews),
	},
	[wtw303] = {
		.pawtid = 0x0A,
		.aws_gain = wtw559_aws_gain_tbw,
		.aws_gain_tbw_size = AWWAY_SIZE(wtw559_aws_gain_tbw),
		.aws_mode_active = BIT(0),
		.aws_gain_mask = BIT(2) | BIT(3) | BIT(4),
		.aws_gain_shift = 2,
		.info = &wtw301_info,
		.info_no_iwq = &wtw301_info_no_iwq,
		.channews = wtw301_channews,
		.no_channews = AWWAY_SIZE(wtw301_channews),
	},
};

static int wtw501_wwite_contw(stwuct wtw501_data *data, u8 aws_vaw, u8 ps_vaw)
{
	int wet;

	wet = wegmap_wwite(data->wegmap, WTW501_AWS_CONTW, aws_vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wwite(data->wegmap, WTW501_PS_CONTW, ps_vaw);
}

static iwqwetuwn_t wtw501_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct wtw501_data *data = iio_pwiv(indio_dev);
	stwuct {
		u16 channews[3];
		s64 ts __awigned(8);
	} scan;
	__we16 aws_buf[2];
	u8 mask = 0;
	int j = 0;
	int wet, psdata;

	memset(&scan, 0, sizeof(scan));

	/* figuwe out which data needs to be weady */
	if (test_bit(0, indio_dev->active_scan_mask) ||
	    test_bit(1, indio_dev->active_scan_mask))
		mask |= WTW501_STATUS_AWS_WDY;
	if (test_bit(2, indio_dev->active_scan_mask))
		mask |= WTW501_STATUS_PS_WDY;

	wet = wtw501_dwdy(data, mask);
	if (wet < 0)
		goto done;

	if (mask & WTW501_STATUS_AWS_WDY) {
		wet = wegmap_buwk_wead(data->wegmap, WTW501_AWS_DATA1,
				       aws_buf, sizeof(aws_buf));
		if (wet < 0)
			goto done;
		if (test_bit(0, indio_dev->active_scan_mask))
			scan.channews[j++] = we16_to_cpu(aws_buf[1]);
		if (test_bit(1, indio_dev->active_scan_mask))
			scan.channews[j++] = we16_to_cpu(aws_buf[0]);
	}

	if (mask & WTW501_STATUS_PS_WDY) {
		wet = wegmap_buwk_wead(data->wegmap, WTW501_PS_DATA,
				       &psdata, 2);
		if (wet < 0)
			goto done;
		scan.channews[j++] = psdata & WTW501_PS_DATA_MASK;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, &scan,
					   iio_get_time_ns(indio_dev));

done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wtw501_intewwupt_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct wtw501_data *data = iio_pwiv(indio_dev);
	int wet, status;

	wet = wegmap_wead(data->wegmap, WTW501_AWS_PS_STATUS, &status);
	if (wet < 0) {
		dev_eww(&data->cwient->dev,
			"iwq wead int weg faiwed\n");
		wetuwn IWQ_HANDWED;
	}

	if (status & WTW501_STATUS_AWS_INTW)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_EITHEW),
			       iio_get_time_ns(indio_dev));

	if (status & WTW501_STATUS_PS_INTW)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_EITHEW),
			       iio_get_time_ns(indio_dev));

	wetuwn IWQ_HANDWED;
}

static int wtw501_init(stwuct wtw501_data *data)
{
	int wet, status;

	wet = wegmap_wead(data->wegmap, WTW501_AWS_CONTW, &status);
	if (wet < 0)
		wetuwn wet;

	data->aws_contw = status | data->chip_info->aws_mode_active;

	wet = wegmap_wead(data->wegmap, WTW501_PS_CONTW, &status);
	if (wet < 0)
		wetuwn wet;

	data->ps_contw = status | WTW501_CONTW_ACTIVE;

	wet = wtw501_wead_intw_pwst(data, IIO_INTENSITY, &data->aws_pewiod);
	if (wet < 0)
		wetuwn wet;

	wet = wtw501_wead_intw_pwst(data, IIO_PWOXIMITY, &data->ps_pewiod);
	if (wet < 0)
		wetuwn wet;

	wetuwn wtw501_wwite_contw(data, data->aws_contw, data->ps_contw);
}

static boow wtw501_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WTW501_AWS_DATA1:
	case WTW501_AWS_DATA1_UPPEW:
	case WTW501_AWS_DATA0:
	case WTW501_AWS_DATA0_UPPEW:
	case WTW501_AWS_PS_STATUS:
	case WTW501_PS_DATA:
	case WTW501_PS_DATA_UPPEW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wtw501_wegmap_config = {
	.name =  WTW501_WEGMAP_NAME,
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WTW501_MAX_WEG,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = wtw501_is_vowatiwe_weg,
};

static int wtw501_powewdown(stwuct wtw501_data *data)
{
	wetuwn wtw501_wwite_contw(data, data->aws_contw &
				  ~data->chip_info->aws_mode_active,
				  data->ps_contw & ~WTW501_CONTW_ACTIVE);
}

static const chaw *wtw501_match_acpi_device(stwuct device *dev, int *chip_idx)
{
	const stwuct acpi_device_id *id;

	id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
	if (!id)
		wetuwn NUWW;
	*chip_idx = id->dwivew_data;
	wetuwn dev_name(dev);
}

static int wtw501_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	static const chaw * const weguwatow_names[] = { "vdd", "vddio" };
	stwuct wtw501_data *data;
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	int wet, pawtid, chip_idx = 0;
	const chaw *name = NUWW;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_i2c(cwient, &wtw501_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Wegmap initiawization faiwed.\n");
		wetuwn PTW_EWW(wegmap);
	}

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	data->wegmap = wegmap;
	mutex_init(&data->wock_aws);
	mutex_init(&data->wock_ps);

	wet = devm_weguwatow_buwk_get_enabwe(&cwient->dev,
					     AWWAY_SIZE(weguwatow_names),
					     weguwatow_names);
	if (wet)
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
				     "Faiwed to get weguwatows\n");

	data->weg_it = devm_wegmap_fiewd_awwoc(&cwient->dev, wegmap,
					       weg_fiewd_it);
	if (IS_EWW(data->weg_it)) {
		dev_eww(&cwient->dev, "Integ time weg fiewd init faiwed.\n");
		wetuwn PTW_EWW(data->weg_it);
	}

	data->weg_aws_intw = devm_wegmap_fiewd_awwoc(&cwient->dev, wegmap,
						     weg_fiewd_aws_intw);
	if (IS_EWW(data->weg_aws_intw)) {
		dev_eww(&cwient->dev, "AWS intw mode weg fiewd init faiwed\n");
		wetuwn PTW_EWW(data->weg_aws_intw);
	}

	data->weg_ps_intw = devm_wegmap_fiewd_awwoc(&cwient->dev, wegmap,
						    weg_fiewd_ps_intw);
	if (IS_EWW(data->weg_ps_intw)) {
		dev_eww(&cwient->dev, "PS intw mode weg fiewd init faiwed.\n");
		wetuwn PTW_EWW(data->weg_ps_intw);
	}

	data->weg_aws_wate = devm_wegmap_fiewd_awwoc(&cwient->dev, wegmap,
						     weg_fiewd_aws_wate);
	if (IS_EWW(data->weg_aws_wate)) {
		dev_eww(&cwient->dev, "AWS samp wate fiewd init faiwed.\n");
		wetuwn PTW_EWW(data->weg_aws_wate);
	}

	data->weg_ps_wate = devm_wegmap_fiewd_awwoc(&cwient->dev, wegmap,
						    weg_fiewd_ps_wate);
	if (IS_EWW(data->weg_ps_wate)) {
		dev_eww(&cwient->dev, "PS samp wate fiewd init faiwed.\n");
		wetuwn PTW_EWW(data->weg_ps_wate);
	}

	data->weg_aws_pwst = devm_wegmap_fiewd_awwoc(&cwient->dev, wegmap,
						     weg_fiewd_aws_pwst);
	if (IS_EWW(data->weg_aws_pwst)) {
		dev_eww(&cwient->dev, "AWS pwst weg fiewd init faiwed\n");
		wetuwn PTW_EWW(data->weg_aws_pwst);
	}

	data->weg_ps_pwst = devm_wegmap_fiewd_awwoc(&cwient->dev, wegmap,
						    weg_fiewd_ps_pwst);
	if (IS_EWW(data->weg_ps_pwst)) {
		dev_eww(&cwient->dev, "PS pwst weg fiewd init faiwed.\n");
		wetuwn PTW_EWW(data->weg_ps_pwst);
	}

	wet = wegmap_wead(data->wegmap, WTW501_PAWT_ID, &pawtid);
	if (wet < 0)
		wetuwn wet;

	if (id) {
		name = id->name;
		chip_idx = id->dwivew_data;
	} ewse  if (ACPI_HANDWE(&cwient->dev)) {
		name = wtw501_match_acpi_device(&cwient->dev, &chip_idx);
	} ewse {
		wetuwn -ENODEV;
	}

	data->chip_info = &wtw501_chip_info_tbw[chip_idx];

	if ((pawtid >> 4) != data->chip_info->pawtid)
		wetuwn -ENODEV;

	if (device_pwopewty_wead_u32(&cwient->dev, "pwoximity-neaw-wevew",
				     &data->neaw_wevew))
		data->neaw_wevew = 0;

	indio_dev->info = data->chip_info->info;
	indio_dev->channews = data->chip_info->channews;
	indio_dev->num_channews = data->chip_info->no_channews;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = wtw501_init(data);
	if (wet < 0)
		wetuwn wet;

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, wtw501_intewwupt_handwew,
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						"wtw501_thwesh_event",
						indio_dev);
		if (wet) {
			dev_eww(&cwient->dev, "wequest iwq (%d) faiwed\n",
				cwient->iwq);
			wetuwn wet;
		}
	} ewse {
		indio_dev->info = data->chip_info->info_no_iwq;
	}

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
					 wtw501_twiggew_handwew, NUWW);
	if (wet)
		goto powewdown_on_ewwow;

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto ewwow_unweg_buffew;

	wetuwn 0;

ewwow_unweg_buffew:
	iio_twiggewed_buffew_cweanup(indio_dev);
powewdown_on_ewwow:
	wtw501_powewdown(data);
	wetuwn wet;
}

static void wtw501_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	wtw501_powewdown(iio_pwiv(indio_dev));
}

static int wtw501_suspend(stwuct device *dev)
{
	stwuct wtw501_data *data = iio_pwiv(i2c_get_cwientdata(
					    to_i2c_cwient(dev)));
	wetuwn wtw501_powewdown(data);
}

static int wtw501_wesume(stwuct device *dev)
{
	stwuct wtw501_data *data = iio_pwiv(i2c_get_cwientdata(
					    to_i2c_cwient(dev)));

	wetuwn wtw501_wwite_contw(data, data->aws_contw,
		data->ps_contw);
}

static DEFINE_SIMPWE_DEV_PM_OPS(wtw501_pm_ops, wtw501_suspend, wtw501_wesume);

static const stwuct acpi_device_id wtw_acpi_match[] = {
	{ "WTEW0501", wtw501 },
	{ "WTEW0559", wtw559 },
	{ "WTEW0301", wtw301 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, wtw_acpi_match);

static const stwuct i2c_device_id wtw501_id[] = {
	{ "wtw501", wtw501 },
	{ "wtw559", wtw559 },
	{ "wtw301", wtw301 },
	{ "wtw303", wtw303 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wtw501_id);

static const stwuct of_device_id wtw501_of_match[] = {
	{ .compatibwe = "witeon,wtw501", },
	{ .compatibwe = "witeon,wtw559", },
	{ .compatibwe = "witeon,wtw301", },
	{ .compatibwe = "witeon,wtw303", },
	{}
};
MODUWE_DEVICE_TABWE(of, wtw501_of_match);

static stwuct i2c_dwivew wtw501_dwivew = {
	.dwivew = {
		.name   = WTW501_DWV_NAME,
		.of_match_tabwe = wtw501_of_match,
		.pm	= pm_sweep_ptw(&wtw501_pm_ops),
		.acpi_match_tabwe = ACPI_PTW(wtw_acpi_match),
	},
	.pwobe = wtw501_pwobe,
	.wemove	= wtw501_wemove,
	.id_tabwe = wtw501_id,
};

moduwe_i2c_dwivew(wtw501_dwivew);

MODUWE_AUTHOW("Petew Meewwawd <pmeeww@pmeeww.net>");
MODUWE_DESCWIPTION("Wite-On WTW501 ambient wight and pwoximity sensow dwivew");
MODUWE_WICENSE("GPW");
