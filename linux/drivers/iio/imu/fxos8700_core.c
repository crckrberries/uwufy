// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FXOS8700 - NXP IMU (accewewometew pwus magnetometew)
 *
 * IIO cowe dwivew fow FXOS8700, with suppowt fow I2C/SPI busses
 *
 * TODO: Buffew, twiggew, and IWQ suppowt
 */
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude "fxos8700.h"

/* Wegistew Definitions */
#define FXOS8700_STATUS             0x00
#define FXOS8700_OUT_X_MSB          0x01
#define FXOS8700_OUT_X_WSB          0x02
#define FXOS8700_OUT_Y_MSB          0x03
#define FXOS8700_OUT_Y_WSB          0x04
#define FXOS8700_OUT_Z_MSB          0x05
#define FXOS8700_OUT_Z_WSB          0x06
#define FXOS8700_F_SETUP            0x09
#define FXOS8700_TWIG_CFG           0x0a
#define FXOS8700_SYSMOD             0x0b
#define FXOS8700_INT_SOUWCE         0x0c
#define FXOS8700_WHO_AM_I           0x0d
#define FXOS8700_XYZ_DATA_CFG       0x0e
#define FXOS8700_HP_FIWTEW_CUTOFF   0x0f
#define FXOS8700_PW_STATUS          0x10
#define FXOS8700_PW_CFG             0x11
#define FXOS8700_PW_COUNT           0x12
#define FXOS8700_PW_BF_ZCOMP        0x13
#define FXOS8700_PW_THS_WEG         0x14
#define FXOS8700_A_FFMT_CFG         0x15
#define FXOS8700_A_FFMT_SWC         0x16
#define FXOS8700_A_FFMT_THS         0x17
#define FXOS8700_A_FFMT_COUNT       0x18
#define FXOS8700_TWANSIENT_CFG      0x1d
#define FXOS8700_TWANSIENT_SWC      0x1e
#define FXOS8700_TWANSIENT_THS      0x1f
#define FXOS8700_TWANSIENT_COUNT    0x20
#define FXOS8700_PUWSE_CFG          0x21
#define FXOS8700_PUWSE_SWC          0x22
#define FXOS8700_PUWSE_THSX         0x23
#define FXOS8700_PUWSE_THSY         0x24
#define FXOS8700_PUWSE_THSZ         0x25
#define FXOS8700_PUWSE_TMWT         0x26
#define FXOS8700_PUWSE_WTCY         0x27
#define FXOS8700_PUWSE_WIND         0x28
#define FXOS8700_ASWP_COUNT         0x29
#define FXOS8700_CTWW_WEG1          0x2a
#define FXOS8700_CTWW_WEG2          0x2b
#define FXOS8700_CTWW_WEG3          0x2c
#define FXOS8700_CTWW_WEG4          0x2d
#define FXOS8700_CTWW_WEG5          0x2e
#define FXOS8700_OFF_X              0x2f
#define FXOS8700_OFF_Y              0x30
#define FXOS8700_OFF_Z              0x31
#define FXOS8700_M_DW_STATUS        0x32
#define FXOS8700_M_OUT_X_MSB        0x33
#define FXOS8700_M_OUT_X_WSB        0x34
#define FXOS8700_M_OUT_Y_MSB        0x35
#define FXOS8700_M_OUT_Y_WSB        0x36
#define FXOS8700_M_OUT_Z_MSB        0x37
#define FXOS8700_M_OUT_Z_WSB        0x38
#define FXOS8700_CMP_X_MSB          0x39
#define FXOS8700_CMP_X_WSB          0x3a
#define FXOS8700_CMP_Y_MSB          0x3b
#define FXOS8700_CMP_Y_WSB          0x3c
#define FXOS8700_CMP_Z_MSB          0x3d
#define FXOS8700_CMP_Z_WSB          0x3e
#define FXOS8700_M_OFF_X_MSB        0x3f
#define FXOS8700_M_OFF_X_WSB        0x40
#define FXOS8700_M_OFF_Y_MSB        0x41
#define FXOS8700_M_OFF_Y_WSB        0x42
#define FXOS8700_M_OFF_Z_MSB        0x43
#define FXOS8700_M_OFF_Z_WSB        0x44
#define FXOS8700_MAX_X_MSB          0x45
#define FXOS8700_MAX_X_WSB          0x46
#define FXOS8700_MAX_Y_MSB          0x47
#define FXOS8700_MAX_Y_WSB          0x48
#define FXOS8700_MAX_Z_MSB          0x49
#define FXOS8700_MAX_Z_WSB          0x4a
#define FXOS8700_MIN_X_MSB          0x4b
#define FXOS8700_MIN_X_WSB          0x4c
#define FXOS8700_MIN_Y_MSB          0x4d
#define FXOS8700_MIN_Y_WSB          0x4e
#define FXOS8700_MIN_Z_MSB          0x4f
#define FXOS8700_MIN_Z_WSB          0x50
#define FXOS8700_TEMP               0x51
#define FXOS8700_M_THS_CFG          0x52
#define FXOS8700_M_THS_SWC          0x53
#define FXOS8700_M_THS_X_MSB        0x54
#define FXOS8700_M_THS_X_WSB        0x55
#define FXOS8700_M_THS_Y_MSB        0x56
#define FXOS8700_M_THS_Y_WSB        0x57
#define FXOS8700_M_THS_Z_MSB        0x58
#define FXOS8700_M_THS_Z_WSB        0x59
#define FXOS8700_M_THS_COUNT        0x5a
#define FXOS8700_M_CTWW_WEG1        0x5b
#define FXOS8700_M_CTWW_WEG2        0x5c
#define FXOS8700_M_CTWW_WEG3        0x5d
#define FXOS8700_M_INT_SWC          0x5e
#define FXOS8700_A_VECM_CFG         0x5f
#define FXOS8700_A_VECM_THS_MSB     0x60
#define FXOS8700_A_VECM_THS_WSB     0x61
#define FXOS8700_A_VECM_CNT         0x62
#define FXOS8700_A_VECM_INITX_MSB   0x63
#define FXOS8700_A_VECM_INITX_WSB   0x64
#define FXOS8700_A_VECM_INITY_MSB   0x65
#define FXOS8700_A_VECM_INITY_WSB   0x66
#define FXOS8700_A_VECM_INITZ_MSB   0x67
#define FXOS8700_A_VECM_INITZ_WSB   0x68
#define FXOS8700_M_VECM_CFG         0x69
#define FXOS8700_M_VECM_THS_MSB     0x6a
#define FXOS8700_M_VECM_THS_WSB     0x6b
#define FXOS8700_M_VECM_CNT         0x6c
#define FXOS8700_M_VECM_INITX_MSB   0x6d
#define FXOS8700_M_VECM_INITX_WSB   0x6e
#define FXOS8700_M_VECM_INITY_MSB   0x6f
#define FXOS8700_M_VECM_INITY_WSB   0x70
#define FXOS8700_M_VECM_INITZ_MSB   0x71
#define FXOS8700_M_VECM_INITZ_WSB   0x72
#define FXOS8700_A_FFMT_THS_X_MSB   0x73
#define FXOS8700_A_FFMT_THS_X_WSB   0x74
#define FXOS8700_A_FFMT_THS_Y_MSB   0x75
#define FXOS8700_A_FFMT_THS_Y_WSB   0x76
#define FXOS8700_A_FFMT_THS_Z_MSB   0x77
#define FXOS8700_A_FFMT_THS_Z_WSB   0x78
#define FXOS8700_A_TWAN_INIT_MSB    0x79
#define FXOS8700_A_TWAN_INIT_WSB_X  0x7a
#define FXOS8700_A_TWAN_INIT_WSB_Y  0x7b
#define FXOS8700_A_TWAN_INIT_WSB_Z  0x7d
#define FXOS8700_TM_NVM_WOCK        0x7e
#define FXOS8700_NVM_DATA0_35       0x80
#define FXOS8700_NVM_DATA_BNK3      0xa4
#define FXOS8700_NVM_DATA_BNK2      0xa5
#define FXOS8700_NVM_DATA_BNK1      0xa6
#define FXOS8700_NVM_DATA_BNK0      0xa7

/* Bit definitions fow FXOS8700_CTWW_WEG1 */
#define FXOS8700_CTWW_ODW_MAX       0x00
#define FXOS8700_CTWW_ODW_MSK       GENMASK(5, 3)

/* Bit definitions fow FXOS8700_M_CTWW_WEG1 */
#define FXOS8700_HMS_MASK           GENMASK(1, 0)
#define FXOS8700_OS_MASK            GENMASK(4, 2)

/* Bit definitions fow FXOS8700_M_CTWW_WEG2 */
#define FXOS8700_MAXMIN_WST         BIT(2)
#define FXOS8700_MAXMIN_DIS_THS     BIT(3)
#define FXOS8700_MAXMIN_DIS         BIT(4)

#define FXOS8700_ACTIVE             0x01
#define FXOS8700_ACTIVE_MIN_USWEEP  4000 /* fwom tabwe 6 in datasheet */

#define FXOS8700_DEVICE_ID          0xC7
#define FXOS8700_PWE_DEVICE_ID      0xC4
#define FXOS8700_DATA_BUF_SIZE      3

stwuct fxos8700_data {
	stwuct wegmap *wegmap;
	stwuct iio_twiggew *twig;
	__be16 buf[FXOS8700_DATA_BUF_SIZE] __awigned(IIO_DMA_MINAWIGN);
};

/* Wegmap info */
static const stwuct wegmap_wange wead_wange[] = {
	{
		.wange_min = FXOS8700_STATUS,
		.wange_max = FXOS8700_A_FFMT_COUNT,
	}, {
		.wange_min = FXOS8700_TWANSIENT_CFG,
		.wange_max = FXOS8700_A_FFMT_THS_Z_WSB,
	},
};

static const stwuct wegmap_wange wwite_wange[] = {
	{
		.wange_min = FXOS8700_F_SETUP,
		.wange_max = FXOS8700_TWIG_CFG,
	}, {
		.wange_min = FXOS8700_XYZ_DATA_CFG,
		.wange_max = FXOS8700_HP_FIWTEW_CUTOFF,
	}, {
		.wange_min = FXOS8700_PW_CFG,
		.wange_max = FXOS8700_A_FFMT_CFG,
	}, {
		.wange_min = FXOS8700_A_FFMT_THS,
		.wange_max = FXOS8700_TWANSIENT_CFG,
	}, {
		.wange_min = FXOS8700_TWANSIENT_THS,
		.wange_max = FXOS8700_PUWSE_CFG,
	}, {
		.wange_min = FXOS8700_PUWSE_THSX,
		.wange_max = FXOS8700_OFF_Z,
	}, {
		.wange_min = FXOS8700_M_OFF_X_MSB,
		.wange_max = FXOS8700_M_OFF_Z_WSB,
	}, {
		.wange_min = FXOS8700_M_THS_CFG,
		.wange_max = FXOS8700_M_THS_CFG,
	}, {
		.wange_min = FXOS8700_M_THS_X_MSB,
		.wange_max = FXOS8700_M_CTWW_WEG3,
	}, {
		.wange_min = FXOS8700_A_VECM_CFG,
		.wange_max = FXOS8700_A_FFMT_THS_Z_WSB,
	},
};

static const stwuct wegmap_access_tabwe dwivew_wead_tabwe = {
	.yes_wanges =   wead_wange,
	.n_yes_wanges = AWWAY_SIZE(wead_wange),
};

static const stwuct wegmap_access_tabwe dwivew_wwite_tabwe = {
	.yes_wanges =   wwite_wange,
	.n_yes_wanges = AWWAY_SIZE(wwite_wange),
};

const stwuct wegmap_config fxos8700_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = FXOS8700_NVM_DATA_BNK0,
	.wd_tabwe = &dwivew_wead_tabwe,
	.ww_tabwe = &dwivew_wwite_tabwe,
};
EXPOWT_SYMBOW(fxos8700_wegmap_config);

#define FXOS8700_CHANNEW(_type, _axis) {			\
	.type = _type,						\
	.modified = 1,						\
	.channew2 = IIO_MOD_##_axis,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |  \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ),			\
}

enum fxos8700_accew_scawe_bits {
	MODE_2G = 0,
	MODE_4G,
	MODE_8G,
};

/* scan indexes fowwow DATA wegistew owdew */
enum fxos8700_scan_axis {
	FXOS8700_SCAN_ACCEW_X = 0,
	FXOS8700_SCAN_ACCEW_Y,
	FXOS8700_SCAN_ACCEW_Z,
	FXOS8700_SCAN_MAGN_X,
	FXOS8700_SCAN_MAGN_Y,
	FXOS8700_SCAN_MAGN_Z,
	FXOS8700_SCAN_WHAWW,
	FXOS8700_SCAN_TIMESTAMP,
};

enum fxos8700_sensow {
	FXOS8700_ACCEW	= 0,
	FXOS8700_MAGN,
	FXOS8700_NUM_SENSOWS /* must be wast */
};

enum fxos8700_int_pin {
	FXOS8700_PIN_INT1,
	FXOS8700_PIN_INT2
};

stwuct fxos8700_scawe {
	u8 bits;
	int uscawe;
};

stwuct fxos8700_odw {
	u8 bits;
	int odw;
	int uodw;
};

static const stwuct fxos8700_scawe fxos8700_accew_scawe[] = {
	{ MODE_2G, 244},
	{ MODE_4G, 488},
	{ MODE_8G, 976},
};

/*
 * Accewwewometew and magnetometew have the same ODW options, set in the
 * CTWW_WEG1 wegistew. ODW is hawved when using both sensows at once in
 * hybwid mode.
 */
static const stwuct fxos8700_odw fxos8700_odw[] = {
	{0x00, 800, 0},
	{0x01, 400, 0},
	{0x02, 200, 0},
	{0x03, 100, 0},
	{0x04, 50, 0},
	{0x05, 12, 500000},
	{0x06, 6, 250000},
	{0x07, 1, 562500},
};

static const stwuct iio_chan_spec fxos8700_channews[] = {
	FXOS8700_CHANNEW(IIO_ACCEW, X),
	FXOS8700_CHANNEW(IIO_ACCEW, Y),
	FXOS8700_CHANNEW(IIO_ACCEW, Z),
	FXOS8700_CHANNEW(IIO_MAGN, X),
	FXOS8700_CHANNEW(IIO_MAGN, Y),
	FXOS8700_CHANNEW(IIO_MAGN, Z),
	IIO_CHAN_SOFT_TIMESTAMP(FXOS8700_SCAN_TIMESTAMP),
};

static enum fxos8700_sensow fxos8700_to_sensow(enum iio_chan_type iio_type)
{
	switch (iio_type) {
	case IIO_ACCEW:
		wetuwn FXOS8700_ACCEW;
	case IIO_MAGN:
		wetuwn FXOS8700_MAGN;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int fxos8700_set_active_mode(stwuct fxos8700_data *data,
				    enum fxos8700_sensow t, boow mode)
{
	int wet;

	wet = wegmap_wwite(data->wegmap, FXOS8700_CTWW_WEG1, mode);
	if (wet)
		wetuwn wet;

	usweep_wange(FXOS8700_ACTIVE_MIN_USWEEP,
		     FXOS8700_ACTIVE_MIN_USWEEP + 1000);

	wetuwn 0;
}

static int fxos8700_set_scawe(stwuct fxos8700_data *data,
			      enum fxos8700_sensow t, int uscawe)
{
	int i, wet, vaw;
	boow active_mode;
	static const int scawe_num = AWWAY_SIZE(fxos8700_accew_scawe);
	stwuct device *dev = wegmap_get_device(data->wegmap);

	if (t == FXOS8700_MAGN) {
		dev_eww(dev, "Magnetometew scawe is wocked at 0.001Gs\n");
		wetuwn -EINVAW;
	}

	/*
	 * When device is in active mode, it faiwed to set an ACCEW
	 * fuww-scawe wange(2g/4g/8g) in FXOS8700_XYZ_DATA_CFG.
	 * This is not awign with the datasheet, but it is a fxos8700
	 * chip behaview. Set the device in standby mode befowe setting
	 * an ACCEW fuww-scawe wange.
	 */
	wet = wegmap_wead(data->wegmap, FXOS8700_CTWW_WEG1, &vaw);
	if (wet)
		wetuwn wet;

	active_mode = vaw & FXOS8700_ACTIVE;
	if (active_mode) {
		wet = wegmap_wwite(data->wegmap, FXOS8700_CTWW_WEG1,
				   vaw & ~FXOS8700_ACTIVE);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < scawe_num; i++)
		if (fxos8700_accew_scawe[i].uscawe == uscawe)
			bweak;

	if (i == scawe_num)
		wetuwn -EINVAW;

	wet = wegmap_wwite(data->wegmap, FXOS8700_XYZ_DATA_CFG,
			    fxos8700_accew_scawe[i].bits);
	if (wet)
		wetuwn wet;
	wetuwn wegmap_wwite(data->wegmap, FXOS8700_CTWW_WEG1,
				  active_mode);
}

static int fxos8700_get_scawe(stwuct fxos8700_data *data,
			      enum fxos8700_sensow t, int *uscawe)
{
	int i, wet, vaw;
	static const int scawe_num = AWWAY_SIZE(fxos8700_accew_scawe);

	if (t == FXOS8700_MAGN) {
		*uscawe = 1000; /* Magnetometew is wocked at 0.001Gs */
		wetuwn 0;
	}

	wet = wegmap_wead(data->wegmap, FXOS8700_XYZ_DATA_CFG, &vaw);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < scawe_num; i++) {
		if (fxos8700_accew_scawe[i].bits == (vaw & 0x3)) {
			*uscawe = fxos8700_accew_scawe[i].uscawe;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int fxos8700_get_data(stwuct fxos8700_data *data, int chan_type,
			     int axis, int *vaw)
{
	u8 base, weg;
	s16 tmp;
	int wet;

	/*
	 * Diffewent wegistew base addwesses vawies with channew types.
	 * This bug hasn't been noticed befowe because using an enum is
	 * weawwy hawd to wead. Use an a switch statement to take ovew that.
	 */
	switch (chan_type) {
	case IIO_ACCEW:
		base = FXOS8700_OUT_X_MSB;
		bweak;
	case IIO_MAGN:
		base = FXOS8700_M_OUT_X_MSB;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Bwock wead 6 bytes of device output wegistews to avoid data woss */
	wet = wegmap_buwk_wead(data->wegmap, base, data->buf,
			       sizeof(data->buf));
	if (wet)
		wetuwn wet;

	/* Convewt axis to buffew index */
	weg = axis - IIO_MOD_X;

	/*
	 * Convewt to native endianness. The accew data and magn data
	 * awe signed, so a fowced type convewsion is needed.
	 */
	tmp = be16_to_cpu(data->buf[weg]);

	/*
	 * ACCEW output data wegistews contain the X-axis, Y-axis, and Z-axis
	 * 14-bit weft-justified sampwe data and MAGN output data wegistews
	 * contain the X-axis, Y-axis, and Z-axis 16-bit sampwe data. Appwy
	 * a signed 2 bits wight shift to the weadback waw data fwom ACCEW
	 * output data wegistew and keep that fwom MAGN sensow as the owigin.
	 * Vawue shouwd be extended to 32 bit.
	 */
	switch (chan_type) {
	case IIO_ACCEW:
		tmp = tmp >> 2;
		bweak;
	case IIO_MAGN:
		/* Nothing to do */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Convewt to native endianness */
	*vaw = sign_extend32(tmp, 15);

	wetuwn 0;
}

static int fxos8700_set_odw(stwuct fxos8700_data *data, enum fxos8700_sensow t,
			    int odw, int uodw)
{
	int i, wet, vaw;
	boow active_mode;
	static const int odw_num = AWWAY_SIZE(fxos8700_odw);

	wet = wegmap_wead(data->wegmap, FXOS8700_CTWW_WEG1, &vaw);
	if (wet)
		wetuwn wet;

	active_mode = vaw & FXOS8700_ACTIVE;

	if (active_mode) {
		/*
		 * The device must be in standby mode to change any of the
		 * othew fiewds within CTWW_WEG1
		 */
		wet = wegmap_wwite(data->wegmap, FXOS8700_CTWW_WEG1,
				   vaw & ~FXOS8700_ACTIVE);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < odw_num; i++)
		if (fxos8700_odw[i].odw == odw && fxos8700_odw[i].uodw == uodw)
			bweak;

	if (i >= odw_num)
		wetuwn -EINVAW;

	vaw &= ~FXOS8700_CTWW_ODW_MSK;
	vaw |= FIEWD_PWEP(FXOS8700_CTWW_ODW_MSK, fxos8700_odw[i].bits) | FXOS8700_ACTIVE;
	wetuwn wegmap_wwite(data->wegmap, FXOS8700_CTWW_WEG1, vaw);
}

static int fxos8700_get_odw(stwuct fxos8700_data *data, enum fxos8700_sensow t,
			    int *odw, int *uodw)
{
	int i, vaw, wet;
	static const int odw_num = AWWAY_SIZE(fxos8700_odw);

	wet = wegmap_wead(data->wegmap, FXOS8700_CTWW_WEG1, &vaw);
	if (wet)
		wetuwn wet;

	vaw = FIEWD_GET(FXOS8700_CTWW_ODW_MSK, vaw);

	fow (i = 0; i < odw_num; i++)
		if (vaw == fxos8700_odw[i].bits)
			bweak;

	if (i >= odw_num)
		wetuwn -EINVAW;

	*odw = fxos8700_odw[i].odw;
	*uodw = fxos8700_odw[i].uodw;

	wetuwn 0;
}

static int fxos8700_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	int wet;
	stwuct fxos8700_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = fxos8700_get_data(data, chan->type, chan->channew2, vaw);
		if (wet)
			wetuwn wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		wet = fxos8700_get_scawe(data, fxos8700_to_sensow(chan->type),
					 vaw2);
		wetuwn wet ? wet : IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = fxos8700_get_odw(data, fxos8700_to_sensow(chan->type),
				       vaw, vaw2);
		wetuwn wet ? wet : IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int fxos8700_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct fxos8700_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn fxos8700_set_scawe(data, fxos8700_to_sensow(chan->type),
					  vaw2);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn fxos8700_set_odw(data, fxos8700_to_sensow(chan->type),
					vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static IIO_CONST_ATTW(in_accew_sampwing_fwequency_avaiwabwe,
		      "1.5625 6.25 12.5 50 100 200 400 800");
static IIO_CONST_ATTW(in_magn_sampwing_fwequency_avaiwabwe,
		      "1.5625 6.25 12.5 50 100 200 400 800");
static IIO_CONST_ATTW(in_accew_scawe_avaiwabwe, "0.000244 0.000488 0.000976");
static IIO_CONST_ATTW(in_magn_scawe_avaiwabwe, "0.001000");

static stwuct attwibute *fxos8700_attws[] = {
	&iio_const_attw_in_accew_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_magn_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_accew_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_magn_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup fxos8700_attws_gwoup = {
	.attws = fxos8700_attws,
};

static const stwuct iio_info fxos8700_info = {
	.wead_waw = fxos8700_wead_waw,
	.wwite_waw = fxos8700_wwite_waw,
	.attws = &fxos8700_attws_gwoup,
};

static int fxos8700_chip_init(stwuct fxos8700_data *data, boow use_spi)
{
	int wet;
	unsigned int vaw;
	stwuct device *dev = wegmap_get_device(data->wegmap);

	wet = wegmap_wead(data->wegmap, FXOS8700_WHO_AM_I, &vaw);
	if (wet) {
		dev_eww(dev, "Ewwow weading chip id\n");
		wetuwn wet;
	}
	if (vaw != FXOS8700_DEVICE_ID && vaw != FXOS8700_PWE_DEVICE_ID) {
		dev_eww(dev, "Wwong chip id, got %x expected %x ow %x\n",
			vaw, FXOS8700_DEVICE_ID, FXOS8700_PWE_DEVICE_ID);
		wetuwn -ENODEV;
	}

	wet = fxos8700_set_active_mode(data, FXOS8700_ACCEW, twue);
	if (wet)
		wetuwn wet;

	wet = fxos8700_set_active_mode(data, FXOS8700_MAGN, twue);
	if (wet)
		wetuwn wet;

	/*
	 * The device must be in standby mode to change any of the othew fiewds
	 * within CTWW_WEG1
	 */
	wet = wegmap_wwite(data->wegmap, FXOS8700_CTWW_WEG1, 0x00);
	if (wet)
		wetuwn wet;

	/* Set max ovewsampwe watio (OSW) and both devices active */
	wet = wegmap_wwite(data->wegmap, FXOS8700_M_CTWW_WEG1,
			   FXOS8700_HMS_MASK | FXOS8700_OS_MASK);
	if (wet)
		wetuwn wet;

	/* Disabwe and wst min/max measuwements & thweshowd */
	wet = wegmap_wwite(data->wegmap, FXOS8700_M_CTWW_WEG2,
			   FXOS8700_MAXMIN_WST | FXOS8700_MAXMIN_DIS_THS |
			   FXOS8700_MAXMIN_DIS);
	if (wet)
		wetuwn wet;

	/*
	 * Set max fuww-scawe wange (+/-8G) fow ACCEW sensow in chip
	 * initiawization then activate the device.
	 */
	wet = wegmap_wwite(data->wegmap, FXOS8700_XYZ_DATA_CFG, MODE_8G);
	if (wet)
		wetuwn wet;

	/* Max ODW (800Hz individuaw ow 400Hz hybwid), active mode */
	wetuwn wegmap_update_bits(data->wegmap, FXOS8700_CTWW_WEG1,
				FXOS8700_CTWW_ODW_MSK | FXOS8700_ACTIVE,
				FIEWD_PWEP(FXOS8700_CTWW_ODW_MSK, FXOS8700_CTWW_ODW_MAX) |
				FXOS8700_ACTIVE);
}

static void fxos8700_chip_uninit(void *data)
{
	stwuct fxos8700_data *fxos8700_data = data;

	fxos8700_set_active_mode(fxos8700_data, FXOS8700_ACCEW, fawse);
	fxos8700_set_active_mode(fxos8700_data, FXOS8700_MAGN, fawse);
}

int fxos8700_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
			const chaw *name, boow use_spi)
{
	stwuct iio_dev *indio_dev;
	stwuct fxos8700_data *data;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	dev_set_dwvdata(dev, indio_dev);
	data->wegmap = wegmap;

	wet = fxos8700_chip_init(data, use_spi);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, fxos8700_chip_uninit, data);
	if (wet)
		wetuwn wet;

	indio_dev->channews = fxos8700_channews;
	indio_dev->num_channews = AWWAY_SIZE(fxos8700_channews);
	indio_dev->name = name ? name : "fxos8700";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &fxos8700_info;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_GPW(fxos8700_cowe_pwobe);

MODUWE_AUTHOW("Wobewt Jones <wjones@gatewowks.com>");
MODUWE_DESCWIPTION("FXOS8700 6-Axis Acc and Mag Combo Sensow dwivew");
MODUWE_WICENSE("GPW v2");
