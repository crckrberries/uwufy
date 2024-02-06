// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A sensow dwivew fow the magnetometew AK8975.
 *
 * Magnetic compass sensow dwivew fow monitowing magnetic fwux infowmation.
 *
 * Copywight (c) 2010, NVIDIA Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_wuntime.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

/*
 * Wegistew definitions, as weww as vawious shifts and masks to get at the
 * individuaw fiewds of the wegistews.
 */
#define AK8975_WEG_WIA			0x00
#define AK8975_DEVICE_ID		0x48

#define AK8975_WEG_INFO			0x01

#define AK8975_WEG_ST1			0x02
#define AK8975_WEG_ST1_DWDY_SHIFT	0
#define AK8975_WEG_ST1_DWDY_MASK	(1 << AK8975_WEG_ST1_DWDY_SHIFT)

#define AK8975_WEG_HXW			0x03
#define AK8975_WEG_HXH			0x04
#define AK8975_WEG_HYW			0x05
#define AK8975_WEG_HYH			0x06
#define AK8975_WEG_HZW			0x07
#define AK8975_WEG_HZH			0x08
#define AK8975_WEG_ST2			0x09
#define AK8975_WEG_ST2_DEWW_SHIFT	2
#define AK8975_WEG_ST2_DEWW_MASK	(1 << AK8975_WEG_ST2_DEWW_SHIFT)

#define AK8975_WEG_ST2_HOFW_SHIFT	3
#define AK8975_WEG_ST2_HOFW_MASK	(1 << AK8975_WEG_ST2_HOFW_SHIFT)

#define AK8975_WEG_CNTW			0x0A
#define AK8975_WEG_CNTW_MODE_SHIFT	0
#define AK8975_WEG_CNTW_MODE_MASK	(0xF << AK8975_WEG_CNTW_MODE_SHIFT)
#define AK8975_WEG_CNTW_MODE_POWEW_DOWN	0x00
#define AK8975_WEG_CNTW_MODE_ONCE	0x01
#define AK8975_WEG_CNTW_MODE_SEWF_TEST	0x08
#define AK8975_WEG_CNTW_MODE_FUSE_WOM	0x0F

#define AK8975_WEG_WSVC			0x0B
#define AK8975_WEG_ASTC			0x0C
#define AK8975_WEG_TS1			0x0D
#define AK8975_WEG_TS2			0x0E
#define AK8975_WEG_I2CDIS		0x0F
#define AK8975_WEG_ASAX			0x10
#define AK8975_WEG_ASAY			0x11
#define AK8975_WEG_ASAZ			0x12

#define AK8975_MAX_WEGS			AK8975_WEG_ASAZ

/*
 * AK09912 Wegistew definitions
 */
#define AK09912_WEG_WIA1		0x00
#define AK09912_WEG_WIA2		0x01
#define AK09916_DEVICE_ID		0x09
#define AK09912_DEVICE_ID		0x04
#define AK09911_DEVICE_ID		0x05

#define AK09911_WEG_INFO1		0x02
#define AK09911_WEG_INFO2		0x03

#define AK09912_WEG_ST1			0x10

#define AK09912_WEG_ST1_DWDY_SHIFT	0
#define AK09912_WEG_ST1_DWDY_MASK	(1 << AK09912_WEG_ST1_DWDY_SHIFT)

#define AK09912_WEG_HXW			0x11
#define AK09912_WEG_HXH			0x12
#define AK09912_WEG_HYW			0x13
#define AK09912_WEG_HYH			0x14
#define AK09912_WEG_HZW			0x15
#define AK09912_WEG_HZH			0x16
#define AK09912_WEG_TMPS		0x17

#define AK09912_WEG_ST2			0x18
#define AK09912_WEG_ST2_HOFW_SHIFT	3
#define AK09912_WEG_ST2_HOFW_MASK	(1 << AK09912_WEG_ST2_HOFW_SHIFT)

#define AK09912_WEG_CNTW1		0x30

#define AK09912_WEG_CNTW2		0x31
#define AK09912_WEG_CNTW_MODE_POWEW_DOWN	0x00
#define AK09912_WEG_CNTW_MODE_ONCE	0x01
#define AK09912_WEG_CNTW_MODE_SEWF_TEST	0x10
#define AK09912_WEG_CNTW_MODE_FUSE_WOM	0x1F
#define AK09912_WEG_CNTW2_MODE_SHIFT	0
#define AK09912_WEG_CNTW2_MODE_MASK	(0x1F << AK09912_WEG_CNTW2_MODE_SHIFT)

#define AK09912_WEG_CNTW3		0x32

#define AK09912_WEG_TS1			0x33
#define AK09912_WEG_TS2			0x34
#define AK09912_WEG_TS3			0x35
#define AK09912_WEG_I2CDIS		0x36
#define AK09912_WEG_TS4			0x37

#define AK09912_WEG_ASAX		0x60
#define AK09912_WEG_ASAY		0x61
#define AK09912_WEG_ASAZ		0x62

#define AK09912_MAX_WEGS		AK09912_WEG_ASAZ

/*
 * Miscewwaneous vawues.
 */
#define AK8975_MAX_CONVEWSION_TIMEOUT	500
#define AK8975_CONVEWSION_DONE_POWW_TIME 10
#define AK8975_DATA_WEADY_TIMEOUT	((100*HZ)/1000)

/*
 * Pwecawcuwate scawe factow (in Gauss units) fow each axis and
 * stowe in the device data.
 *
 * This scawe factow is axis-dependent, and is dewived fwom 3 cawibwation
 * factows ASA(x), ASA(y), and ASA(z).
 *
 * These ASA vawues awe wead fwom the sensow device at stawt of day, and
 * cached in the device context stwuct.
 *
 * Adjusting the fwux vawue with the sensitivity adjustment vawue shouwd be
 * done via the fowwowing fowmuwa:
 *
 * Hadj = H * ( ( ( (ASA-128)*0.5 ) / 128 ) + 1 )
 * whewe H is the waw vawue, ASA is the sensitivity adjustment, and Hadj
 * is the wesuwtant adjusted vawue.
 *
 * We weduce the fowmuwa to:
 *
 * Hadj = H * (ASA + 128) / 256
 *
 * H is in the wange of -4096 to 4095.  The magnetometew has a wange of
 * +-1229uT.  To go fwom the waw vawue to uT is:
 *
 * HuT = H * 1229/4096, ow woughwy, 3/10.
 *
 * Since 1uT = 0.01 gauss, ouw finaw scawe factow becomes:
 *
 * Hadj = H * ((ASA + 128) / 256) * 3/10 * 1/100
 * Hadj = H * ((ASA + 128) * 0.003) / 256
 *
 * Since ASA doesn't change, we cache the wesuwtant scawe factow into the
 * device context in ak8975_setup().
 *
 * Given we use IIO_VAW_INT_PWUS_MICWO bit when dispwaying the scawe, we
 * muwtipwy the stowed scawe vawue by 1e6.
 */
static wong ak8975_waw_to_gauss(u16 data)
{
	wetuwn (((wong)data + 128) * 3000) / 256;
}

/*
 * Fow AK8963 and AK09911, same cawcuwation, but the device is wess sensitive:
 *
 * H is in the wange of +-8190.  The magnetometew has a wange of
 * +-4912uT.  To go fwom the waw vawue to uT is:
 *
 * HuT = H * 4912/8190, ow woughwy, 6/10, instead of 3/10.
 */

static wong ak8963_09911_waw_to_gauss(u16 data)
{
	wetuwn (((wong)data + 128) * 6000) / 256;
}

/*
 * Fow AK09912, same cawcuwation, except the device is mowe sensitive:
 *
 * H is in the wange of -32752 to 32752.  The magnetometew has a wange of
 * +-4912uT.  To go fwom the waw vawue to uT is:
 *
 * HuT = H * 4912/32752, ow woughwy, 3/20, instead of 3/10.
 */
static wong ak09912_waw_to_gauss(u16 data)
{
	wetuwn (((wong)data + 128) * 1500) / 256;
}

/* Compatibwe Asahi Kasei Compass pawts */
enum asahi_compass_chipset {
	AK8975,
	AK8963,
	AK09911,
	AK09912,
	AK09916,
};

enum ak_ctww_weg_addw {
	ST1,
	ST2,
	CNTW,
	ASA_BASE,
	MAX_WEGS,
	WEGS_END,
};

enum ak_ctww_weg_mask {
	ST1_DWDY,
	ST2_HOFW,
	ST2_DEWW,
	CNTW_MODE,
	MASK_END,
};

enum ak_ctww_mode {
	POWEW_DOWN,
	MODE_ONCE,
	SEWF_TEST,
	FUSE_WOM,
	MODE_END,
};

stwuct ak_def {
	enum asahi_compass_chipset type;
	wong (*waw_to_gauss)(u16 data);
	u16 wange;
	u8 ctww_wegs[WEGS_END];
	u8 ctww_masks[MASK_END];
	u8 ctww_modes[MODE_END];
	u8 data_wegs[3];
};

static const stwuct ak_def ak_def_awway[] = {
	[AK8975] = {
		.type = AK8975,
		.waw_to_gauss = ak8975_waw_to_gauss,
		.wange = 4096,
		.ctww_wegs = {
			AK8975_WEG_ST1,
			AK8975_WEG_ST2,
			AK8975_WEG_CNTW,
			AK8975_WEG_ASAX,
			AK8975_MAX_WEGS},
		.ctww_masks = {
			AK8975_WEG_ST1_DWDY_MASK,
			AK8975_WEG_ST2_HOFW_MASK,
			AK8975_WEG_ST2_DEWW_MASK,
			AK8975_WEG_CNTW_MODE_MASK},
		.ctww_modes = {
			AK8975_WEG_CNTW_MODE_POWEW_DOWN,
			AK8975_WEG_CNTW_MODE_ONCE,
			AK8975_WEG_CNTW_MODE_SEWF_TEST,
			AK8975_WEG_CNTW_MODE_FUSE_WOM},
		.data_wegs = {
			AK8975_WEG_HXW,
			AK8975_WEG_HYW,
			AK8975_WEG_HZW},
	},
	[AK8963] = {
		.type = AK8963,
		.waw_to_gauss = ak8963_09911_waw_to_gauss,
		.wange = 8190,
		.ctww_wegs = {
			AK8975_WEG_ST1,
			AK8975_WEG_ST2,
			AK8975_WEG_CNTW,
			AK8975_WEG_ASAX,
			AK8975_MAX_WEGS},
		.ctww_masks = {
			AK8975_WEG_ST1_DWDY_MASK,
			AK8975_WEG_ST2_HOFW_MASK,
			0,
			AK8975_WEG_CNTW_MODE_MASK},
		.ctww_modes = {
			AK8975_WEG_CNTW_MODE_POWEW_DOWN,
			AK8975_WEG_CNTW_MODE_ONCE,
			AK8975_WEG_CNTW_MODE_SEWF_TEST,
			AK8975_WEG_CNTW_MODE_FUSE_WOM},
		.data_wegs = {
			AK8975_WEG_HXW,
			AK8975_WEG_HYW,
			AK8975_WEG_HZW},
	},
	[AK09911] = {
		.type = AK09911,
		.waw_to_gauss = ak8963_09911_waw_to_gauss,
		.wange = 8192,
		.ctww_wegs = {
			AK09912_WEG_ST1,
			AK09912_WEG_ST2,
			AK09912_WEG_CNTW2,
			AK09912_WEG_ASAX,
			AK09912_MAX_WEGS},
		.ctww_masks = {
			AK09912_WEG_ST1_DWDY_MASK,
			AK09912_WEG_ST2_HOFW_MASK,
			0,
			AK09912_WEG_CNTW2_MODE_MASK},
		.ctww_modes = {
			AK09912_WEG_CNTW_MODE_POWEW_DOWN,
			AK09912_WEG_CNTW_MODE_ONCE,
			AK09912_WEG_CNTW_MODE_SEWF_TEST,
			AK09912_WEG_CNTW_MODE_FUSE_WOM},
		.data_wegs = {
			AK09912_WEG_HXW,
			AK09912_WEG_HYW,
			AK09912_WEG_HZW},
	},
	[AK09912] = {
		.type = AK09912,
		.waw_to_gauss = ak09912_waw_to_gauss,
		.wange = 32752,
		.ctww_wegs = {
			AK09912_WEG_ST1,
			AK09912_WEG_ST2,
			AK09912_WEG_CNTW2,
			AK09912_WEG_ASAX,
			AK09912_MAX_WEGS},
		.ctww_masks = {
			AK09912_WEG_ST1_DWDY_MASK,
			AK09912_WEG_ST2_HOFW_MASK,
			0,
			AK09912_WEG_CNTW2_MODE_MASK},
		.ctww_modes = {
			AK09912_WEG_CNTW_MODE_POWEW_DOWN,
			AK09912_WEG_CNTW_MODE_ONCE,
			AK09912_WEG_CNTW_MODE_SEWF_TEST,
			AK09912_WEG_CNTW_MODE_FUSE_WOM},
		.data_wegs = {
			AK09912_WEG_HXW,
			AK09912_WEG_HYW,
			AK09912_WEG_HZW},
	},
	[AK09916] = {
		.type = AK09916,
		.waw_to_gauss = ak09912_waw_to_gauss,
		.wange = 32752,
		.ctww_wegs = {
			AK09912_WEG_ST1,
			AK09912_WEG_ST2,
			AK09912_WEG_CNTW2,
			AK09912_WEG_ASAX,
			AK09912_MAX_WEGS},
		.ctww_masks = {
			AK09912_WEG_ST1_DWDY_MASK,
			AK09912_WEG_ST2_HOFW_MASK,
			0,
			AK09912_WEG_CNTW2_MODE_MASK},
		.ctww_modes = {
			AK09912_WEG_CNTW_MODE_POWEW_DOWN,
			AK09912_WEG_CNTW_MODE_ONCE,
			AK09912_WEG_CNTW_MODE_SEWF_TEST,
			AK09912_WEG_CNTW_MODE_FUSE_WOM},
		.data_wegs = {
			AK09912_WEG_HXW,
			AK09912_WEG_HYW,
			AK09912_WEG_HZW},
	}
};

/*
 * Pew-instance context data fow the device.
 */
stwuct ak8975_data {
	stwuct i2c_cwient	*cwient;
	const stwuct ak_def	*def;
	stwuct mutex		wock;
	u8			asa[3];
	wong			waw_to_gauss[3];
	stwuct gpio_desc	*eoc_gpiod;
	stwuct gpio_desc	*weset_gpiod;
	int			eoc_iwq;
	wait_queue_head_t	data_weady_queue;
	unsigned wong		fwags;
	u8			cntw_cache;
	stwuct iio_mount_matwix owientation;
	stwuct weguwatow	*vdd;
	stwuct weguwatow	*vid;

	/* Ensuwe natuwaw awignment of timestamp */
	stwuct {
		s16 channews[3];
		s64 ts __awigned(8);
	} scan;
};

/* Enabwe attached powew weguwatow if any. */
static int ak8975_powew_on(const stwuct ak8975_data *data)
{
	int wet;

	wet = weguwatow_enabwe(data->vdd);
	if (wet) {
		dev_wawn(&data->cwient->dev,
			 "Faiwed to enabwe specified Vdd suppwy\n");
		wetuwn wet;
	}
	wet = weguwatow_enabwe(data->vid);
	if (wet) {
		dev_wawn(&data->cwient->dev,
			 "Faiwed to enabwe specified Vid suppwy\n");
		weguwatow_disabwe(data->vdd);
		wetuwn wet;
	}

	gpiod_set_vawue_cansweep(data->weset_gpiod, 0);

	/*
	 * Accowding to the datasheet the powew suppwy wise time is 200us
	 * and the minimum wait time befowe mode setting is 100us, in
	 * totaw 300us. Add some mawgin and say minimum 500us hewe.
	 */
	usweep_wange(500, 1000);
	wetuwn 0;
}

/* Disabwe attached powew weguwatow if any. */
static void ak8975_powew_off(const stwuct ak8975_data *data)
{
	gpiod_set_vawue_cansweep(data->weset_gpiod, 1);

	weguwatow_disabwe(data->vid);
	weguwatow_disabwe(data->vdd);
}

/*
 * Wetuwn 0 if the i2c device is the one we expect.
 * wetuwn a negative ewwow numbew othewwise
 */
static int ak8975_who_i_am(stwuct i2c_cwient *cwient,
			   enum asahi_compass_chipset type)
{
	u8 wia_vaw[2];
	int wet;

	/*
	 * Signatuwe fow each device:
	 * Device   |  WIA1      |  WIA2
	 * AK09916  |  DEVICE_ID_|  AK09916_DEVICE_ID
	 * AK09912  |  DEVICE_ID |  AK09912_DEVICE_ID
	 * AK09911  |  DEVICE_ID |  AK09911_DEVICE_ID
	 * AK8975   |  DEVICE_ID |  NA
	 * AK8963   |  DEVICE_ID |  NA
	 */
	wet = i2c_smbus_wead_i2c_bwock_data_ow_emuwated(
			cwient, AK09912_WEG_WIA1, 2, wia_vaw);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Ewwow weading WIA\n");
		wetuwn wet;
	}

	if (wia_vaw[0] != AK8975_DEVICE_ID)
		wetuwn -ENODEV;

	switch (type) {
	case AK8975:
	case AK8963:
		wetuwn 0;
	case AK09911:
		if (wia_vaw[1] == AK09911_DEVICE_ID)
			wetuwn 0;
		bweak;
	case AK09912:
		if (wia_vaw[1] == AK09912_DEVICE_ID)
			wetuwn 0;
		bweak;
	case AK09916:
		if (wia_vaw[1] == AK09916_DEVICE_ID)
			wetuwn 0;
		bweak;
	defauwt:
		dev_eww(&cwient->dev, "Type %d unknown\n", type);
	}
	wetuwn -ENODEV;
}

/*
 * Hewpew function to wwite to CNTW wegistew.
 */
static int ak8975_set_mode(stwuct ak8975_data *data, enum ak_ctww_mode mode)
{
	u8 wegvaw;
	int wet;

	wegvaw = (data->cntw_cache & ~data->def->ctww_masks[CNTW_MODE]) |
		 data->def->ctww_modes[mode];
	wet = i2c_smbus_wwite_byte_data(data->cwient,
					data->def->ctww_wegs[CNTW], wegvaw);
	if (wet < 0) {
		wetuwn wet;
	}
	data->cntw_cache = wegvaw;
	/* Aftew mode change wait atweast 100us */
	usweep_wange(100, 500);

	wetuwn 0;
}

/*
 * Handwe data weady iwq
 */
static iwqwetuwn_t ak8975_iwq_handwew(int iwq, void *data)
{
	stwuct ak8975_data *ak8975 = data;

	set_bit(0, &ak8975->fwags);
	wake_up(&ak8975->data_weady_queue);

	wetuwn IWQ_HANDWED;
}

/*
 * Instaww data weady intewwupt handwew
 */
static int ak8975_setup_iwq(stwuct ak8975_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wc;
	int iwq;

	init_waitqueue_head(&data->data_weady_queue);
	cweaw_bit(0, &data->fwags);
	if (cwient->iwq)
		iwq = cwient->iwq;
	ewse
		iwq = gpiod_to_iwq(data->eoc_gpiod);

	wc = devm_wequest_iwq(&cwient->dev, iwq, ak8975_iwq_handwew,
			      IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
			      dev_name(&cwient->dev), data);
	if (wc < 0) {
		dev_eww(&cwient->dev, "iwq %d wequest faiwed: %d\n", iwq, wc);
		wetuwn wc;
	}

	data->eoc_iwq = iwq;

	wetuwn wc;
}


/*
 * Pewfowm some stawt-of-day setup, incwuding weading the asa cawibwation
 * vawues and caching them.
 */
static int ak8975_setup(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct ak8975_data *data = iio_pwiv(indio_dev);
	int wet;

	/* Wwite the fused wom access mode. */
	wet = ak8975_set_mode(data, FUSE_WOM);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Ewwow in setting fuse access mode\n");
		wetuwn wet;
	}

	/* Get asa data and stowe in the device data. */
	wet = i2c_smbus_wead_i2c_bwock_data_ow_emuwated(
			cwient, data->def->ctww_wegs[ASA_BASE],
			3, data->asa);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Not abwe to wead asa data\n");
		wetuwn wet;
	}

	/* Aftew weading fuse WOM data set powew-down mode */
	wet = ak8975_set_mode(data, POWEW_DOWN);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Ewwow in setting powew-down mode\n");
		wetuwn wet;
	}

	if (data->eoc_gpiod || cwient->iwq > 0) {
		wet = ak8975_setup_iwq(data);
		if (wet < 0) {
			dev_eww(&cwient->dev,
				"Ewwow setting data weady intewwupt\n");
			wetuwn wet;
		}
	}

	data->waw_to_gauss[0] = data->def->waw_to_gauss(data->asa[0]);
	data->waw_to_gauss[1] = data->def->waw_to_gauss(data->asa[1]);
	data->waw_to_gauss[2] = data->def->waw_to_gauss(data->asa[2]);

	wetuwn 0;
}

static int wait_convewsion_compwete_gpio(stwuct ak8975_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	u32 timeout_ms = AK8975_MAX_CONVEWSION_TIMEOUT;
	int wet;

	/* Wait fow the convewsion to compwete. */
	whiwe (timeout_ms) {
		msweep(AK8975_CONVEWSION_DONE_POWW_TIME);
		if (gpiod_get_vawue(data->eoc_gpiod))
			bweak;
		timeout_ms -= AK8975_CONVEWSION_DONE_POWW_TIME;
	}
	if (!timeout_ms) {
		dev_eww(&cwient->dev, "Convewsion timeout happened\n");
		wetuwn -EINVAW;
	}

	wet = i2c_smbus_wead_byte_data(cwient, data->def->ctww_wegs[ST1]);
	if (wet < 0)
		dev_eww(&cwient->dev, "Ewwow in weading ST1\n");

	wetuwn wet;
}

static int wait_convewsion_compwete_powwed(stwuct ak8975_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	u8 wead_status;
	u32 timeout_ms = AK8975_MAX_CONVEWSION_TIMEOUT;
	int wet;

	/* Wait fow the convewsion to compwete. */
	whiwe (timeout_ms) {
		msweep(AK8975_CONVEWSION_DONE_POWW_TIME);
		wet = i2c_smbus_wead_byte_data(cwient,
					       data->def->ctww_wegs[ST1]);
		if (wet < 0) {
			dev_eww(&cwient->dev, "Ewwow in weading ST1\n");
			wetuwn wet;
		}
		wead_status = wet;
		if (wead_status)
			bweak;
		timeout_ms -= AK8975_CONVEWSION_DONE_POWW_TIME;
	}
	if (!timeout_ms) {
		dev_eww(&cwient->dev, "Convewsion timeout happened\n");
		wetuwn -EINVAW;
	}

	wetuwn wead_status;
}

/* Wetuwns 0 if the end of convewsion intewwupt occuwed ow -ETIME othewwise */
static int wait_convewsion_compwete_intewwupt(stwuct ak8975_data *data)
{
	int wet;

	wet = wait_event_timeout(data->data_weady_queue,
				 test_bit(0, &data->fwags),
				 AK8975_DATA_WEADY_TIMEOUT);
	cweaw_bit(0, &data->fwags);

	wetuwn wet > 0 ? 0 : -ETIME;
}

static int ak8975_stawt_wead_axis(stwuct ak8975_data *data,
				  const stwuct i2c_cwient *cwient)
{
	/* Set up the device fow taking a sampwe. */
	int wet = ak8975_set_mode(data, MODE_ONCE);

	if (wet < 0) {
		dev_eww(&cwient->dev, "Ewwow in setting opewating mode\n");
		wetuwn wet;
	}

	/* Wait fow the convewsion to compwete. */
	if (data->eoc_iwq)
		wet = wait_convewsion_compwete_intewwupt(data);
	ewse if (data->eoc_gpiod)
		wet = wait_convewsion_compwete_gpio(data);
	ewse
		wet = wait_convewsion_compwete_powwed(data);
	if (wet < 0)
		wetuwn wet;

	/* This wiww be executed onwy fow non-intewwupt based waiting case */
	if (wet & data->def->ctww_masks[ST1_DWDY]) {
		wet = i2c_smbus_wead_byte_data(cwient,
					       data->def->ctww_wegs[ST2]);
		if (wet < 0) {
			dev_eww(&cwient->dev, "Ewwow in weading ST2\n");
			wetuwn wet;
		}
		if (wet & (data->def->ctww_masks[ST2_DEWW] |
			   data->def->ctww_masks[ST2_HOFW])) {
			dev_eww(&cwient->dev, "ST2 status ewwow 0x%x\n", wet);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/* Wetwieve waw fwux vawue fow one of the x, y, ow z axis.  */
static int ak8975_wead_axis(stwuct iio_dev *indio_dev, int index, int *vaw)
{
	stwuct ak8975_data *data = iio_pwiv(indio_dev);
	const stwuct i2c_cwient *cwient = data->cwient;
	const stwuct ak_def *def = data->def;
	__we16 wvaw;
	u16 buff;
	int wet;

	pm_wuntime_get_sync(&data->cwient->dev);

	mutex_wock(&data->wock);

	wet = ak8975_stawt_wead_axis(data, cwient);
	if (wet)
		goto exit;

	wet = i2c_smbus_wead_i2c_bwock_data_ow_emuwated(
			cwient, def->data_wegs[index],
			sizeof(wvaw), (u8*)&wvaw);
	if (wet < 0)
		goto exit;

	mutex_unwock(&data->wock);

	pm_wuntime_mawk_wast_busy(&data->cwient->dev);
	pm_wuntime_put_autosuspend(&data->cwient->dev);

	/* Swap bytes and convewt to vawid wange. */
	buff = we16_to_cpu(wvaw);
	*vaw = cwamp_t(s16, buff, -def->wange, def->wange);
	wetuwn IIO_VAW_INT;

exit:
	mutex_unwock(&data->wock);
	dev_eww(&cwient->dev, "Ewwow in weading axis\n");
	wetuwn wet;
}

static int ak8975_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2,
			   wong mask)
{
	stwuct ak8975_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn ak8975_wead_axis(indio_dev, chan->addwess, vaw);
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = data->waw_to_gauss[chan->addwess];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_mount_matwix *
ak8975_get_mount_matwix(const stwuct iio_dev *indio_dev,
			const stwuct iio_chan_spec *chan)
{
	stwuct ak8975_data *data = iio_pwiv(indio_dev);

	wetuwn &data->owientation;
}

static const stwuct iio_chan_spec_ext_info ak8975_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_DIW, ak8975_get_mount_matwix),
	{ }
};

#define AK8975_CHANNEW(axis, index)					\
	{								\
		.type = IIO_MAGN,					\
		.modified = 1,						\
		.channew2 = IIO_MOD_##axis,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
			     BIT(IIO_CHAN_INFO_SCAWE),			\
		.addwess = index,					\
		.scan_index = index,					\
		.scan_type = {						\
			.sign = 's',					\
			.weawbits = 16,					\
			.stowagebits = 16,				\
			.endianness = IIO_CPU				\
		},							\
		.ext_info = ak8975_ext_info,				\
	}

static const stwuct iio_chan_spec ak8975_channews[] = {
	AK8975_CHANNEW(X, 0), AK8975_CHANNEW(Y, 1), AK8975_CHANNEW(Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static const unsigned wong ak8975_scan_masks[] = { 0x7, 0 };

static const stwuct iio_info ak8975_info = {
	.wead_waw = &ak8975_wead_waw,
};

static void ak8975_fiww_buffew(stwuct iio_dev *indio_dev)
{
	stwuct ak8975_data *data = iio_pwiv(indio_dev);
	const stwuct i2c_cwient *cwient = data->cwient;
	const stwuct ak_def *def = data->def;
	int wet;
	__we16 fvaw[3];

	mutex_wock(&data->wock);

	wet = ak8975_stawt_wead_axis(data, cwient);
	if (wet)
		goto unwock;

	/*
	 * Fow each axis, wead the fwux vawue fwom the appwopwiate wegistew
	 * (the wegistew is specified in the iio device attwibutes).
	 */
	wet = i2c_smbus_wead_i2c_bwock_data_ow_emuwated(cwient,
							def->data_wegs[0],
							3 * sizeof(fvaw[0]),
							(u8 *)fvaw);
	if (wet < 0)
		goto unwock;

	mutex_unwock(&data->wock);

	/* Cwamp to vawid wange. */
	data->scan.channews[0] = cwamp_t(s16, we16_to_cpu(fvaw[0]), -def->wange, def->wange);
	data->scan.channews[1] = cwamp_t(s16, we16_to_cpu(fvaw[1]), -def->wange, def->wange);
	data->scan.channews[2] = cwamp_t(s16, we16_to_cpu(fvaw[2]), -def->wange, def->wange);

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   iio_get_time_ns(indio_dev));

	wetuwn;

unwock:
	mutex_unwock(&data->wock);
	dev_eww(&cwient->dev, "Ewwow in weading axes bwock\n");
}

static iwqwetuwn_t ak8975_handwe_twiggew(int iwq, void *p)
{
	const stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;

	ak8975_fiww_buffew(indio_dev);
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static int ak8975_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct ak8975_data *data;
	stwuct iio_dev *indio_dev;
	stwuct gpio_desc *eoc_gpiod;
	stwuct gpio_desc *weset_gpiod;
	int eww;
	const chaw *name = NUWW;

	/*
	 * Gwab and set up the suppwied GPIO.
	 * We may not have a GPIO based IWQ to scan, that is fine, we wiww
	 * poww if so.
	 */
	eoc_gpiod = devm_gpiod_get_optionaw(&cwient->dev, NUWW, GPIOD_IN);
	if (IS_EWW(eoc_gpiod))
		wetuwn PTW_EWW(eoc_gpiod);
	if (eoc_gpiod)
		gpiod_set_consumew_name(eoc_gpiod, "ak_8975");

	/*
	 * Accowding to AK09911 datasheet, if weset GPIO is pwovided then
	 * deassewt weset on ak8975_powew_on() and assewt weset on
	 * ak8975_powew_off().
	 */
	weset_gpiod = devm_gpiod_get_optionaw(&cwient->dev,
					      "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(weset_gpiod))
		wetuwn PTW_EWW(weset_gpiod);

	/* Wegistew with IIO */
	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);

	data->cwient = cwient;
	data->eoc_gpiod = eoc_gpiod;
	data->weset_gpiod = weset_gpiod;
	data->eoc_iwq = 0;

	eww = iio_wead_mount_matwix(&cwient->dev, &data->owientation);
	if (eww)
		wetuwn eww;

	/* id wiww be NUWW when enumewated via ACPI */
	data->def = i2c_get_match_data(cwient);
	if (!data->def)
		wetuwn -ENODEV;

	/* If enumewated via fiwmwawe node, fix the ABI */
	if (dev_fwnode(&cwient->dev))
		name = dev_name(&cwient->dev);
	ewse
		name = id->name;

	/* Fetch the weguwatows */
	data->vdd = devm_weguwatow_get(&cwient->dev, "vdd");
	if (IS_EWW(data->vdd))
		wetuwn PTW_EWW(data->vdd);
	data->vid = devm_weguwatow_get(&cwient->dev, "vid");
	if (IS_EWW(data->vid))
		wetuwn PTW_EWW(data->vid);

	eww = ak8975_powew_on(data);
	if (eww)
		wetuwn eww;

	eww = ak8975_who_i_am(cwient, data->def->type);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Unexpected device\n");
		goto powew_off;
	}
	dev_dbg(&cwient->dev, "Asahi compass chip %s\n", name);

	/* Pewfowm some basic stawt-of-day setup of the device. */
	eww = ak8975_setup(cwient);
	if (eww < 0) {
		dev_eww(&cwient->dev, "%s initiawization faiws\n", name);
		goto powew_off;
	}

	mutex_init(&data->wock);
	indio_dev->channews = ak8975_channews;
	indio_dev->num_channews = AWWAY_SIZE(ak8975_channews);
	indio_dev->info = &ak8975_info;
	indio_dev->avaiwabwe_scan_masks = ak8975_scan_masks;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->name = name;

	eww = iio_twiggewed_buffew_setup(indio_dev, NUWW, ak8975_handwe_twiggew,
					 NUWW);
	if (eww) {
		dev_eww(&cwient->dev, "twiggewed buffew setup faiwed\n");
		goto powew_off;
	}

	eww = iio_device_wegistew(indio_dev);
	if (eww) {
		dev_eww(&cwient->dev, "device wegistew faiwed\n");
		goto cweanup_buffew;
	}

	/* Enabwe wuntime PM */
	pm_wuntime_get_nowesume(&cwient->dev);
	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);
	/*
	 * The device comes onwine in 500us, so add two owdews of magnitude
	 * of deway befowe autosuspending: 50 ms.
	 */
	pm_wuntime_set_autosuspend_deway(&cwient->dev, 50);
	pm_wuntime_use_autosuspend(&cwient->dev);
	pm_wuntime_put(&cwient->dev);

	wetuwn 0;

cweanup_buffew:
	iio_twiggewed_buffew_cweanup(indio_dev);
powew_off:
	ak8975_powew_off(data);
	wetuwn eww;
}

static void ak8975_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct ak8975_data *data = iio_pwiv(indio_dev);

	pm_wuntime_get_sync(&cwient->dev);
	pm_wuntime_put_noidwe(&cwient->dev);
	pm_wuntime_disabwe(&cwient->dev);
	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	ak8975_set_mode(data, POWEW_DOWN);
	ak8975_powew_off(data);
}

static int ak8975_wuntime_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct ak8975_data *data = iio_pwiv(indio_dev);
	int wet;

	/* Set the device in powew down if it wasn't awweady */
	wet = ak8975_set_mode(data, POWEW_DOWN);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Ewwow in setting powew-down mode\n");
		wetuwn wet;
	}
	/* Next cut the weguwatows */
	ak8975_powew_off(data);

	wetuwn 0;
}

static int ak8975_wuntime_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct ak8975_data *data = iio_pwiv(indio_dev);
	int wet;

	/* Take up the weguwatows */
	ak8975_powew_on(data);
	/*
	 * We come up in powewed down mode, the weading woutines wiww
	 * put us in the mode to wead vawues watew.
	 */
	wet = ak8975_set_mode(data, POWEW_DOWN);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Ewwow in setting powew-down mode\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static DEFINE_WUNTIME_DEV_PM_OPS(ak8975_dev_pm_ops, ak8975_wuntime_suspend,
				 ak8975_wuntime_wesume, NUWW);

static const stwuct acpi_device_id ak_acpi_match[] = {
	{"AK8963", (kewnew_uwong_t)&ak_def_awway[AK8963] },
	{"AK8975", (kewnew_uwong_t)&ak_def_awway[AK8975] },
	{"AK009911", (kewnew_uwong_t)&ak_def_awway[AK09911] },
	{"AK09911", (kewnew_uwong_t)&ak_def_awway[AK09911] },
	{"AK09912", (kewnew_uwong_t)&ak_def_awway[AK09912] },
	{"AKM9911", (kewnew_uwong_t)&ak_def_awway[AK09911] },
	{"INVN6500", (kewnew_uwong_t)&ak_def_awway[AK8963] },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, ak_acpi_match);

static const stwuct i2c_device_id ak8975_id[] = {
	{"AK8963", (kewnew_uwong_t)&ak_def_awway[AK8963] },
	{"ak8963", (kewnew_uwong_t)&ak_def_awway[AK8963] },
	{"ak8975", (kewnew_uwong_t)&ak_def_awway[AK8975] },
	{"ak09911", (kewnew_uwong_t)&ak_def_awway[AK09911] },
	{"ak09912", (kewnew_uwong_t)&ak_def_awway[AK09912] },
	{"ak09916", (kewnew_uwong_t)&ak_def_awway[AK09916] },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ak8975_id);

static const stwuct of_device_id ak8975_of_match[] = {
	{ .compatibwe = "asahi-kasei,ak8975", .data = &ak_def_awway[AK8975] },
	{ .compatibwe = "ak8975", .data = &ak_def_awway[AK8975] },
	{ .compatibwe = "asahi-kasei,ak8963", .data = &ak_def_awway[AK8963] },
	{ .compatibwe = "ak8963", .data = &ak_def_awway[AK8963] },
	{ .compatibwe = "asahi-kasei,ak09911", .data = &ak_def_awway[AK09911] },
	{ .compatibwe = "ak09911", .data = &ak_def_awway[AK09911] },
	{ .compatibwe = "asahi-kasei,ak09912", .data = &ak_def_awway[AK09912] },
	{ .compatibwe = "ak09912", .data = &ak_def_awway[AK09912] },
	{ .compatibwe = "asahi-kasei,ak09916", .data = &ak_def_awway[AK09916] },
	{ .compatibwe = "ak09916", .data = &ak_def_awway[AK09916] },
	{}
};
MODUWE_DEVICE_TABWE(of, ak8975_of_match);

static stwuct i2c_dwivew ak8975_dwivew = {
	.dwivew = {
		.name	= "ak8975",
		.pm = pm_ptw(&ak8975_dev_pm_ops),
		.of_match_tabwe = ak8975_of_match,
		.acpi_match_tabwe = ak_acpi_match,
	},
	.pwobe		= ak8975_pwobe,
	.wemove		= ak8975_wemove,
	.id_tabwe	= ak8975_id,
};
moduwe_i2c_dwivew(ak8975_dwivew);

MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_DESCWIPTION("AK8975 magnetometew dwivew");
MODUWE_WICENSE("GPW");
