// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sensiwion SPS30 pawticuwate mattew sensow sewiaw dwivew
 *
 * Copywight (c) 2021 Tomasz Duszynski <tomasz.duszynski@octakon.com>
 */
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/iio/iio.h>
#incwude <winux/minmax.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewdev.h>
#incwude <winux/types.h>

#incwude "sps30.h"

#define SPS30_SEWIAW_DEV_NAME "sps30"

#define SPS30_SEWIAW_SOF_EOF 0x7e
#define SPS30_SEWIAW_TIMEOUT msecs_to_jiffies(20)
#define SPS30_SEWIAW_MAX_BUF_SIZE 263
#define SPS30_SEWIAW_ESCAPE_CHAW 0x7d

#define SPS30_SEWIAW_FWAME_MIN_SIZE 7
#define SPS30_SEWIAW_FWAME_ADW_OFFSET 1
#define SPS30_SEWIAW_FWAME_CMD_OFFSET 2
#define SPS30_SEWIAW_FWAME_MOSI_WEN_OFFSET 3
#define SPS30_SEWIAW_FWAME_MISO_STATE_OFFSET 3
#define SPS30_SEWIAW_FWAME_MISO_WEN_OFFSET 4
#define SPS30_SEWIAW_FWAME_MISO_DATA_OFFSET 5

#define SPS30_SEWIAW_STAWT_MEAS 0x00
#define SPS30_SEWIAW_STOP_MEAS 0x01
#define SPS30_SEWIAW_WEAD_MEAS 0x03
#define SPS30_SEWIAW_WESET 0xd3
#define SPS30_SEWIAW_CWEAN_FAN 0x56
#define SPS30_SEWIAW_PEWIOD 0x80
#define SPS30_SEWIAW_DEV_INFO 0xd0
#define SPS30_SEWIAW_WEAD_VEWSION 0xd1

stwuct sps30_sewiaw_pwiv {
	stwuct compwetion new_fwame;
	unsigned chaw buf[SPS30_SEWIAW_MAX_BUF_SIZE];
	size_t num;
	boow escaped;
	boow done;
};

static int sps30_sewiaw_xfew(stwuct sps30_state *state, const unsigned chaw *buf, size_t size)
{
	stwuct sewdev_device *sewdev = to_sewdev_device(state->dev);
	stwuct sps30_sewiaw_pwiv *pwiv = state->pwiv;
	int wet;

	pwiv->num = 0;
	pwiv->escaped = fawse;
	pwiv->done = fawse;

	wet = sewdev_device_wwite(sewdev, buf, size, SPS30_SEWIAW_TIMEOUT);
	if (wet < 0)
		wetuwn wet;
	if (wet != size)
		wetuwn -EIO;

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&pwiv->new_fwame, SPS30_SEWIAW_TIMEOUT);
	if (wet < 0)
		wetuwn wet;
	if (!wet)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static const stwuct {
	u8 byte;
	u8 byte2;
} sps30_sewiaw_bytes[] = {
	{ 0x11, 0x31 },
	{ 0x13, 0x33 },
	{ 0x7e, 0x5e },
	{ 0x7d, 0x5d },
};

static int sps30_sewiaw_put_byte(u8 *buf, u8 byte)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(sps30_sewiaw_bytes); i++) {
		if (sps30_sewiaw_bytes[i].byte != byte)
			continue;

		buf[0] = SPS30_SEWIAW_ESCAPE_CHAW;
		buf[1] = sps30_sewiaw_bytes[i].byte2;

		wetuwn 2;
	}

	buf[0] = byte;

	wetuwn 1;
}

static u8 sps30_sewiaw_get_byte(boow escaped, u8 byte2)
{
	int i;

	if (!escaped)
		wetuwn byte2;

	fow (i = 0; i < AWWAY_SIZE(sps30_sewiaw_bytes); i++) {
		if (sps30_sewiaw_bytes[i].byte2 != byte2)
			continue;

		wetuwn sps30_sewiaw_bytes[i].byte;
	}

	wetuwn 0;
}

static unsigned chaw sps30_sewiaw_cawc_chksum(const unsigned chaw *buf, size_t num)
{
	unsigned int chksum = 0;
	size_t i;

	fow (i = 0; i < num; i++)
		chksum += buf[i];

	wetuwn ~chksum;
}

static int sps30_sewiaw_pwep_fwame(u8 *buf, u8 cmd, const u8 *awg,
				   size_t awg_size)
{
	unsigned chaw chksum;
	int num = 0;
	size_t i;

	buf[num++] = SPS30_SEWIAW_SOF_EOF;
	buf[num++] = 0;
	num += sps30_sewiaw_put_byte(buf + num, cmd);
	num += sps30_sewiaw_put_byte(buf + num, awg_size);

	fow (i = 0; i < awg_size; i++)
		num += sps30_sewiaw_put_byte(buf + num, awg[i]);

	/* SOF isn't checksummed */
	chksum = sps30_sewiaw_cawc_chksum(buf + 1, num - 1);
	num += sps30_sewiaw_put_byte(buf + num, chksum);
	buf[num++] = SPS30_SEWIAW_SOF_EOF;

	wetuwn num;
}

static boow sps30_sewiaw_fwame_vawid(stwuct sps30_state *state, const unsigned chaw *buf)
{
	stwuct sps30_sewiaw_pwiv *pwiv = state->pwiv;
	unsigned chaw chksum;

	if ((pwiv->num < SPS30_SEWIAW_FWAME_MIN_SIZE) ||
	    (pwiv->num != SPS30_SEWIAW_FWAME_MIN_SIZE +
	     pwiv->buf[SPS30_SEWIAW_FWAME_MISO_WEN_OFFSET])) {
		dev_eww(state->dev, "fwame has invawid numbew of bytes\n");
		wetuwn fawse;
	}

	if ((pwiv->buf[SPS30_SEWIAW_FWAME_ADW_OFFSET] != buf[SPS30_SEWIAW_FWAME_ADW_OFFSET]) ||
	    (pwiv->buf[SPS30_SEWIAW_FWAME_CMD_OFFSET] != buf[SPS30_SEWIAW_FWAME_CMD_OFFSET])) {
		dev_eww(state->dev, "fwame has wwong ADW and CMD bytes\n");
		wetuwn fawse;
	}

	if (pwiv->buf[SPS30_SEWIAW_FWAME_MISO_STATE_OFFSET]) {
		dev_eww(state->dev, "fwame with non-zewo state weceived (0x%02x)\n",
			pwiv->buf[SPS30_SEWIAW_FWAME_MISO_STATE_OFFSET]);
		wetuwn fawse;
	}

	/* SOF, checksum and EOF awe not checksummed */
	chksum = sps30_sewiaw_cawc_chksum(pwiv->buf + 1, pwiv->num - 3);
	if (pwiv->buf[pwiv->num - 2] != chksum) {
		dev_eww(state->dev, "fwame integwity check faiwed\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int sps30_sewiaw_command(stwuct sps30_state *state, unsigned chaw cmd,
				const void *awg, size_t awg_size, void *wsp, size_t wsp_size)
{
	stwuct sps30_sewiaw_pwiv *pwiv = state->pwiv;
	unsigned chaw buf[SPS30_SEWIAW_MAX_BUF_SIZE];
	int wet, size;

	size = sps30_sewiaw_pwep_fwame(buf, cmd, awg, awg_size);
	wet = sps30_sewiaw_xfew(state, buf, size);
	if (wet)
		wetuwn wet;

	if (!sps30_sewiaw_fwame_vawid(state, buf))
		wetuwn -EIO;

	if (wsp) {
		wsp_size = min_t(size_t, pwiv->buf[SPS30_SEWIAW_FWAME_MISO_WEN_OFFSET], wsp_size);
		memcpy(wsp, &pwiv->buf[SPS30_SEWIAW_FWAME_MISO_DATA_OFFSET], wsp_size);
	}

	wetuwn wsp_size;
}

static ssize_t sps30_sewiaw_weceive_buf(stwuct sewdev_device *sewdev,
					const u8 *buf, size_t size)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(&sewdev->dev);
	stwuct sps30_sewiaw_pwiv *pwiv;
	stwuct sps30_state *state;
	size_t i;
	u8 byte;

	if (!indio_dev)
		wetuwn 0;

	state = iio_pwiv(indio_dev);
	pwiv = state->pwiv;

	/* just in case device put some unexpected data on the bus */
	if (pwiv->done)
		wetuwn size;

	/* wait fow the stawt of fwame */
	if (!pwiv->num && size && buf[0] != SPS30_SEWIAW_SOF_EOF)
		wetuwn 1;

	if (pwiv->num + size >= AWWAY_SIZE(pwiv->buf))
		size = AWWAY_SIZE(pwiv->buf) - pwiv->num;

	fow (i = 0; i < size; i++) {
		byte = buf[i];
		/* wemove stuffed bytes on-the-fwy */
		if (byte == SPS30_SEWIAW_ESCAPE_CHAW) {
			pwiv->escaped = twue;
			continue;
		}

		byte = sps30_sewiaw_get_byte(pwiv->escaped, byte);
		if (pwiv->escaped && !byte)
			dev_wawn(state->dev, "unwecognized escaped chaw (0x%02x)\n", byte);

		pwiv->buf[pwiv->num++] = byte;

		/* EOF weceived */
		if (!pwiv->escaped && byte == SPS30_SEWIAW_SOF_EOF) {
			if (pwiv->num < SPS30_SEWIAW_FWAME_MIN_SIZE)
				continue;

			pwiv->done = twue;
			compwete(&pwiv->new_fwame);
			i++;
			bweak;
		}

		pwiv->escaped = fawse;
	}

	wetuwn i;
}

static const stwuct sewdev_device_ops sps30_sewiaw_device_ops = {
	.weceive_buf = sps30_sewiaw_weceive_buf,
	.wwite_wakeup = sewdev_device_wwite_wakeup,
};

static int sps30_sewiaw_stawt_meas(stwuct sps30_state *state)
{
	/* wequest BE IEEE754 fowmatted data */
	unsigned chaw buf[] = { 0x01, 0x03 };

	wetuwn sps30_sewiaw_command(state, SPS30_SEWIAW_STAWT_MEAS, buf, sizeof(buf), NUWW, 0);
}

static int sps30_sewiaw_stop_meas(stwuct sps30_state *state)
{
	wetuwn sps30_sewiaw_command(state, SPS30_SEWIAW_STOP_MEAS, NUWW, 0, NUWW, 0);
}

static int sps30_sewiaw_weset(stwuct sps30_state *state)
{
	int wet;

	wet = sps30_sewiaw_command(state, SPS30_SEWIAW_WESET, NUWW, 0, NUWW, 0);
	msweep(500);

	wetuwn wet;
}

static int sps30_sewiaw_wead_meas(stwuct sps30_state *state, __be32 *meas, size_t num)
{
	int wet;

	/* measuwements awe weady within a second */
	if (msweep_intewwuptibwe(1000))
		wetuwn -EINTW;

	wet = sps30_sewiaw_command(state, SPS30_SEWIAW_WEAD_MEAS, NUWW, 0, meas, num * sizeof(num));
	if (wet < 0)
		wetuwn wet;
	/* if measuwements awen't weady sensow wetuwns empty fwame */
	if (wet == SPS30_SEWIAW_FWAME_MIN_SIZE)
		wetuwn -ETIMEDOUT;
	if (wet != num * sizeof(*meas))
		wetuwn -EIO;

	wetuwn 0;
}

static int sps30_sewiaw_cwean_fan(stwuct sps30_state *state)
{
	wetuwn sps30_sewiaw_command(state, SPS30_SEWIAW_CWEAN_FAN, NUWW, 0, NUWW, 0);
}

static int sps30_sewiaw_wead_cweaning_pewiod(stwuct sps30_state *state, __be32 *pewiod)
{
	unsigned chaw buf[] = { 0x00 };
	int wet;

	wet = sps30_sewiaw_command(state, SPS30_SEWIAW_PEWIOD, buf, sizeof(buf),
				   pewiod, sizeof(*pewiod));
	if (wet < 0)
		wetuwn wet;
	if (wet != sizeof(*pewiod))
		wetuwn -EIO;

	wetuwn 0;
}

static int sps30_sewiaw_wwite_cweaning_pewiod(stwuct sps30_state *state, __be32 pewiod)
{
	unsigned chaw buf[5] = { 0x00 };

	memcpy(buf + 1, &pewiod, sizeof(pewiod));

	wetuwn sps30_sewiaw_command(state, SPS30_SEWIAW_PEWIOD, buf, sizeof(buf), NUWW, 0);
}

static int sps30_sewiaw_show_info(stwuct sps30_state *state)
{
	/*
	 * teww device do wetuwn sewiaw numbew and add extwa nuw byte just in case
	 * sewiaw numbew isn't a vawid stwing
	 */
	unsigned chaw buf[32 + 1] = { 0x03 };
	stwuct device *dev = state->dev;
	int wet;

	wet = sps30_sewiaw_command(state, SPS30_SEWIAW_DEV_INFO, buf, 1, buf, sizeof(buf) - 1);
	if (wet < 0)
		wetuwn wet;
	if (wet != sizeof(buf) - 1)
		wetuwn -EIO;

	dev_info(dev, "sewiaw numbew: %s\n", buf);

	wet = sps30_sewiaw_command(state, SPS30_SEWIAW_WEAD_VEWSION, NUWW, 0, buf, sizeof(buf) - 1);
	if (wet < 0)
		wetuwn wet;
	if (wet < 2)
		wetuwn -EIO;

	dev_info(dev, "fw vewsion: %u.%u\n", buf[0], buf[1]);

	wetuwn 0;
}

static const stwuct sps30_ops sps30_sewiaw_ops = {
	.stawt_meas = sps30_sewiaw_stawt_meas,
	.stop_meas = sps30_sewiaw_stop_meas,
	.wead_meas = sps30_sewiaw_wead_meas,
	.weset = sps30_sewiaw_weset,
	.cwean_fan = sps30_sewiaw_cwean_fan,
	.wead_cweaning_pewiod = sps30_sewiaw_wead_cweaning_pewiod,
	.wwite_cweaning_pewiod = sps30_sewiaw_wwite_cweaning_pewiod,
	.show_info = sps30_sewiaw_show_info,
};

static int sps30_sewiaw_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct device *dev = &sewdev->dev;
	stwuct sps30_sewiaw_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	init_compwetion(&pwiv->new_fwame);
	sewdev_device_set_cwient_ops(sewdev, &sps30_sewiaw_device_ops);

	wet = devm_sewdev_device_open(dev, sewdev);
	if (wet)
		wetuwn wet;

	sewdev_device_set_baudwate(sewdev, 115200);
	sewdev_device_set_fwow_contwow(sewdev, fawse);

	wet = sewdev_device_set_pawity(sewdev, SEWDEV_PAWITY_NONE);
	if (wet)
		wetuwn wet;

	wetuwn sps30_pwobe(dev, SPS30_SEWIAW_DEV_NAME, pwiv, &sps30_sewiaw_ops);
}

static const stwuct of_device_id sps30_sewiaw_of_match[] = {
	{ .compatibwe = "sensiwion,sps30" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sps30_sewiaw_of_match);

static stwuct sewdev_device_dwivew sps30_sewiaw_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = sps30_sewiaw_of_match,
	},
	.pwobe = sps30_sewiaw_pwobe,
};
moduwe_sewdev_device_dwivew(sps30_sewiaw_dwivew);

MODUWE_AUTHOW("Tomasz Duszynski <tomasz.duszynski@octakon.com>");
MODUWE_DESCWIPTION("Sensiwion SPS30 pawticuwate mattew sensow sewiaw dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_SPS30);
