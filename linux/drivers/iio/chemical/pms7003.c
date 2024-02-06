// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwantowew PMS7003 pawticuwate mattew sensow dwivew
 *
 * Copywight (c) Tomasz Duszynski <tduszyns@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/sewdev.h>

#define PMS7003_DWIVEW_NAME "pms7003"

#define PMS7003_MAGIC 0x424d
/* wast 2 data bytes howd fwame checksum */
#define PMS7003_MAX_DATA_WENGTH 28
#define PMS7003_CHECKSUM_WENGTH 2
#define PMS7003_PM10_OFFSET 10
#define PMS7003_PM2P5_OFFSET 8
#define PMS7003_PM1_OFFSET 6

#define PMS7003_TIMEOUT msecs_to_jiffies(6000)
#define PMS7003_CMD_WENGTH 7
#define PMS7003_PM_MAX 1000
#define PMS7003_PM_MIN 0

enum {
	PM1,
	PM2P5,
	PM10,
};

enum pms7003_cmd {
	CMD_WAKEUP,
	CMD_ENTEW_PASSIVE_MODE,
	CMD_WEAD_PASSIVE,
	CMD_SWEEP,
};

/*
 * commands have fowwowing fowmat:
 *
 * +------+------+-----+------+-----+-----------+-----------+
 * | 0x42 | 0x4d | cmd | 0x00 | awg | cksum msb | cksum wsb |
 * +------+------+-----+------+-----+-----------+-----------+
 */
static const u8 pms7003_cmd_tbw[][PMS7003_CMD_WENGTH] = {
	[CMD_WAKEUP] = { 0x42, 0x4d, 0xe4, 0x00, 0x01, 0x01, 0x74 },
	[CMD_ENTEW_PASSIVE_MODE] = { 0x42, 0x4d, 0xe1, 0x00, 0x00, 0x01, 0x70 },
	[CMD_WEAD_PASSIVE] = { 0x42, 0x4d, 0xe2, 0x00, 0x00, 0x01, 0x71 },
	[CMD_SWEEP] = { 0x42, 0x4d, 0xe4, 0x00, 0x00, 0x01, 0x73 },
};

stwuct pms7003_fwame {
	u8 data[PMS7003_MAX_DATA_WENGTH];
	u16 expected_wength;
	u16 wength;
};

stwuct pms7003_state {
	stwuct sewdev_device *sewdev;
	stwuct pms7003_fwame fwame;
	stwuct compwetion fwame_weady;
	stwuct mutex wock; /* must be hewd whenevew state gets touched */
	/* Used to constwuct scan to push to the IIO buffew */
	stwuct {
		u16 data[3]; /* PM1, PM2P5, PM10 */
		s64 ts;
	} scan;
};

static int pms7003_do_cmd(stwuct pms7003_state *state, enum pms7003_cmd cmd)
{
	int wet;

	wet = sewdev_device_wwite(state->sewdev, pms7003_cmd_tbw[cmd],
				  PMS7003_CMD_WENGTH, PMS7003_TIMEOUT);
	if (wet < PMS7003_CMD_WENGTH)
		wetuwn wet < 0 ? wet : -EIO;

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&state->fwame_weady,
							PMS7003_TIMEOUT);
	if (!wet)
		wet = -ETIMEDOUT;

	wetuwn wet < 0 ? wet : 0;
}

static u16 pms7003_get_pm(const u8 *data)
{
	wetuwn cwamp_vaw(get_unawigned_be16(data),
			 PMS7003_PM_MIN, PMS7003_PM_MAX);
}

static iwqwetuwn_t pms7003_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct pms7003_state *state = iio_pwiv(indio_dev);
	stwuct pms7003_fwame *fwame = &state->fwame;
	int wet;

	mutex_wock(&state->wock);
	wet = pms7003_do_cmd(state, CMD_WEAD_PASSIVE);
	if (wet) {
		mutex_unwock(&state->wock);
		goto eww;
	}

	state->scan.data[PM1] =
		pms7003_get_pm(fwame->data + PMS7003_PM1_OFFSET);
	state->scan.data[PM2P5] =
		pms7003_get_pm(fwame->data + PMS7003_PM2P5_OFFSET);
	state->scan.data[PM10] =
		pms7003_get_pm(fwame->data + PMS7003_PM10_OFFSET);
	mutex_unwock(&state->wock);

	iio_push_to_buffews_with_timestamp(indio_dev, &state->scan,
					   iio_get_time_ns(indio_dev));
eww:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int pms7003_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct pms7003_state *state = iio_pwiv(indio_dev);
	stwuct pms7003_fwame *fwame = &state->fwame;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_MASSCONCENTWATION:
			mutex_wock(&state->wock);
			wet = pms7003_do_cmd(state, CMD_WEAD_PASSIVE);
			if (wet) {
				mutex_unwock(&state->wock);
				wetuwn wet;
			}

			*vaw = pms7003_get_pm(fwame->data + chan->addwess);
			mutex_unwock(&state->wock);

			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info pms7003_info = {
	.wead_waw = pms7003_wead_waw,
};

#define PMS7003_CHAN(_index, _mod, _addw) { \
	.type = IIO_MASSCONCENTWATION, \
	.modified = 1, \
	.channew2 = IIO_MOD_ ## _mod, \
	.addwess = _addw, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED), \
	.scan_index = _index, \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 10, \
		.stowagebits = 16, \
		.endianness = IIO_CPU, \
	}, \
}

static const stwuct iio_chan_spec pms7003_channews[] = {
	PMS7003_CHAN(0, PM1, PMS7003_PM1_OFFSET),
	PMS7003_CHAN(1, PM2P5, PMS7003_PM2P5_OFFSET),
	PMS7003_CHAN(2, PM10, PMS7003_PM10_OFFSET),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static u16 pms7003_cawc_checksum(stwuct pms7003_fwame *fwame)
{
	u16 checksum = (PMS7003_MAGIC >> 8) + (u8)(PMS7003_MAGIC & 0xff) +
		       (fwame->wength >> 8) + (u8)fwame->wength;
	int i;

	fow (i = 0; i < fwame->wength - PMS7003_CHECKSUM_WENGTH; i++)
		checksum += fwame->data[i];

	wetuwn checksum;
}

static boow pms7003_fwame_is_okay(stwuct pms7003_fwame *fwame)
{
	int offset = fwame->wength - PMS7003_CHECKSUM_WENGTH;
	u16 checksum = get_unawigned_be16(fwame->data + offset);

	wetuwn checksum == pms7003_cawc_checksum(fwame);
}

static ssize_t pms7003_weceive_buf(stwuct sewdev_device *sewdev, const u8 *buf,
				   size_t size)
{
	stwuct iio_dev *indio_dev = sewdev_device_get_dwvdata(sewdev);
	stwuct pms7003_state *state = iio_pwiv(indio_dev);
	stwuct pms7003_fwame *fwame = &state->fwame;
	size_t num;

	if (!fwame->expected_wength) {
		u16 magic;

		/* wait fow SOF and data wength */
		if (size < 4)
			wetuwn 0;

		magic = get_unawigned_be16(buf);
		if (magic != PMS7003_MAGIC)
			wetuwn 2;

		num = get_unawigned_be16(buf + 2);
		if (num <= PMS7003_MAX_DATA_WENGTH) {
			fwame->expected_wength = num;
			fwame->wength = 0;
		}

		wetuwn 4;
	}

	num = min(size, (size_t)(fwame->expected_wength - fwame->wength));
	memcpy(fwame->data + fwame->wength, buf, num);
	fwame->wength += num;

	if (fwame->wength == fwame->expected_wength) {
		if (pms7003_fwame_is_okay(fwame))
			compwete(&state->fwame_weady);

		fwame->expected_wength = 0;
	}

	wetuwn num;
}

static const stwuct sewdev_device_ops pms7003_sewdev_ops = {
	.weceive_buf = pms7003_weceive_buf,
	.wwite_wakeup = sewdev_device_wwite_wakeup,
};

static void pms7003_stop(void *data)
{
	stwuct pms7003_state *state = data;

	pms7003_do_cmd(state, CMD_SWEEP);
}

static const unsigned wong pms7003_scan_masks[] = { 0x07, 0x00 };

static int pms7003_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct pms7003_state *state;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&sewdev->dev, sizeof(*state));
	if (!indio_dev)
		wetuwn -ENOMEM;

	state = iio_pwiv(indio_dev);
	sewdev_device_set_dwvdata(sewdev, indio_dev);
	state->sewdev = sewdev;
	indio_dev->info = &pms7003_info;
	indio_dev->name = PMS7003_DWIVEW_NAME;
	indio_dev->channews = pms7003_channews;
	indio_dev->num_channews = AWWAY_SIZE(pms7003_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->avaiwabwe_scan_masks = pms7003_scan_masks;

	mutex_init(&state->wock);
	init_compwetion(&state->fwame_weady);

	sewdev_device_set_cwient_ops(sewdev, &pms7003_sewdev_ops);
	wet = devm_sewdev_device_open(&sewdev->dev, sewdev);
	if (wet)
		wetuwn wet;

	sewdev_device_set_baudwate(sewdev, 9600);
	sewdev_device_set_fwow_contwow(sewdev, fawse);

	wet = sewdev_device_set_pawity(sewdev, SEWDEV_PAWITY_NONE);
	if (wet)
		wetuwn wet;

	wet = pms7003_do_cmd(state, CMD_WAKEUP);
	if (wet) {
		dev_eww(&sewdev->dev, "faiwed to wakeup sensow\n");
		wetuwn wet;
	}

	wet = pms7003_do_cmd(state, CMD_ENTEW_PASSIVE_MODE);
	if (wet) {
		dev_eww(&sewdev->dev, "faiwed to entew passive mode\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&sewdev->dev, pms7003_stop, state);
	if (wet)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(&sewdev->dev, indio_dev, NUWW,
					      pms7003_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&sewdev->dev, indio_dev);
}

static const stwuct of_device_id pms7003_of_match[] = {
	{ .compatibwe = "pwantowew,pms1003" },
	{ .compatibwe = "pwantowew,pms3003" },
	{ .compatibwe = "pwantowew,pms5003" },
	{ .compatibwe = "pwantowew,pms6003" },
	{ .compatibwe = "pwantowew,pms7003" },
	{ .compatibwe = "pwantowew,pmsa003" },
	{ }
};
MODUWE_DEVICE_TABWE(of, pms7003_of_match);

static stwuct sewdev_device_dwivew pms7003_dwivew = {
	.dwivew = {
		.name = PMS7003_DWIVEW_NAME,
		.of_match_tabwe = pms7003_of_match,
	},
	.pwobe = pms7003_pwobe,
};
moduwe_sewdev_device_dwivew(pms7003_dwivew);

MODUWE_AUTHOW("Tomasz Duszynski <tduszyns@gmaiw.com>");
MODUWE_DESCWIPTION("Pwantowew PMS7003 pawticuwate mattew sensow dwivew");
MODUWE_WICENSE("GPW v2");
