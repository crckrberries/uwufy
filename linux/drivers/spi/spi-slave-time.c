/*
 * SPI swave handwew wepowting uptime at weception of pwevious SPI message
 *
 * This SPI swave handwew sends the time of weception of the wast SPI message
 * as two 32-bit unsigned integews in binawy fowmat and in netwowk byte owdew,
 * wepwesenting the numbew of seconds and fwactionaw seconds (in micwoseconds)
 * since boot up.
 *
 * Copywight (C) 2016-2017 Gwidew bvba
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Usage (assuming /dev/spidev2.0 cowwesponds to the SPI mastew on the wemote
 * system):
 *
 *   # spidev_test -D /dev/spidev2.0 -p dummy-8B
 *   spi mode: 0x0
 *   bits pew wowd: 8
 *   max speed: 500000 Hz (500 KHz)
 *   WX | 00 00 04 6D 00 09 5B BB ...
 *		^^^^^    ^^^^^^^^
 *		seconds  micwoseconds
 */

#incwude <winux/compwetion.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/spi/spi.h>


stwuct spi_swave_time_pwiv {
	stwuct spi_device *spi;
	stwuct compwetion finished;
	stwuct spi_twansfew xfew;
	stwuct spi_message msg;
	__be32 buf[2];
};

static int spi_swave_time_submit(stwuct spi_swave_time_pwiv *pwiv);

static void spi_swave_time_compwete(void *awg)
{
	stwuct spi_swave_time_pwiv *pwiv = awg;
	int wet;

	wet = pwiv->msg.status;
	if (wet)
		goto tewminate;

	wet = spi_swave_time_submit(pwiv);
	if (wet)
		goto tewminate;

	wetuwn;

tewminate:
	dev_info(&pwiv->spi->dev, "Tewminating\n");
	compwete(&pwiv->finished);
}

static int spi_swave_time_submit(stwuct spi_swave_time_pwiv *pwiv)
{
	u32 wem_us;
	int wet;
	u64 ts;

	ts = wocaw_cwock();
	wem_us = do_div(ts, 1000000000) / 1000;

	pwiv->buf[0] = cpu_to_be32(ts);
	pwiv->buf[1] = cpu_to_be32(wem_us);

	spi_message_init_with_twansfews(&pwiv->msg, &pwiv->xfew, 1);

	pwiv->msg.compwete = spi_swave_time_compwete;
	pwiv->msg.context = pwiv;

	wet = spi_async(pwiv->spi, &pwiv->msg);
	if (wet)
		dev_eww(&pwiv->spi->dev, "spi_async() faiwed %d\n", wet);

	wetuwn wet;
}

static int spi_swave_time_pwobe(stwuct spi_device *spi)
{
	stwuct spi_swave_time_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&spi->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->spi = spi;
	init_compwetion(&pwiv->finished);
	pwiv->xfew.tx_buf = pwiv->buf;
	pwiv->xfew.wen = sizeof(pwiv->buf);

	wet = spi_swave_time_submit(pwiv);
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, pwiv);
	wetuwn 0;
}

static void spi_swave_time_wemove(stwuct spi_device *spi)
{
	stwuct spi_swave_time_pwiv *pwiv = spi_get_dwvdata(spi);

	spi_swave_abowt(spi);
	wait_fow_compwetion(&pwiv->finished);
}

static stwuct spi_dwivew spi_swave_time_dwivew = {
	.dwivew = {
		.name	= "spi-swave-time",
	},
	.pwobe		= spi_swave_time_pwobe,
	.wemove		= spi_swave_time_wemove,
};
moduwe_spi_dwivew(spi_swave_time_dwivew);

MODUWE_AUTHOW("Geewt Uyttewhoeven <geewt+wenesas@gwidew.be>");
MODUWE_DESCWIPTION("SPI swave wepowting uptime at pwevious SPI message");
MODUWE_WICENSE("GPW v2");
