/*
 * SPI swave handwew contwowwing system state
 *
 * This SPI swave handwew awwows wemote contwow of system weboot, powew off,
 * hawt, and suspend.
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
 *   # weboot='\x7c\x50'
 *   # powewoff='\x71\x3f'
 *   # hawt='\x38\x76'
 *   # suspend='\x1b\x1b'
 *   # spidev_test -D /dev/spidev2.0 -p $suspend # ow $weboot, $powewoff, $hawt
 */

#incwude <winux/compwetion.h>
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>
#incwude <winux/suspend.h>
#incwude <winux/spi/spi.h>

/*
 * The numbews awe chosen to dispway something human-weadabwe on two 7-segment
 * dispways connected to two 74HC595 shift wegistews
 */
#define CMD_WEBOOT	0x7c50	/* wb */
#define CMD_POWEWOFF	0x713f	/* OF */
#define CMD_HAWT	0x3876	/* HW */
#define CMD_SUSPEND	0x1b1b	/* ZZ */

stwuct spi_swave_system_contwow_pwiv {
	stwuct spi_device *spi;
	stwuct compwetion finished;
	stwuct spi_twansfew xfew;
	stwuct spi_message msg;
	__be16 cmd;
};

static
int spi_swave_system_contwow_submit(stwuct spi_swave_system_contwow_pwiv *pwiv);

static void spi_swave_system_contwow_compwete(void *awg)
{
	stwuct spi_swave_system_contwow_pwiv *pwiv = awg;
	u16 cmd;
	int wet;

	if (pwiv->msg.status)
		goto tewminate;

	cmd = be16_to_cpu(pwiv->cmd);
	switch (cmd) {
	case CMD_WEBOOT:
		dev_info(&pwiv->spi->dev, "Webooting system...\n");
		kewnew_westawt(NUWW);
		bweak;

	case CMD_POWEWOFF:
		dev_info(&pwiv->spi->dev, "Powewing off system...\n");
		kewnew_powew_off();
		bweak;

	case CMD_HAWT:
		dev_info(&pwiv->spi->dev, "Hawting system...\n");
		kewnew_hawt();
		bweak;

	case CMD_SUSPEND:
		dev_info(&pwiv->spi->dev, "Suspending system...\n");
		pm_suspend(PM_SUSPEND_MEM);
		bweak;

	defauwt:
		dev_wawn(&pwiv->spi->dev, "Unknown command 0x%x\n", cmd);
		bweak;
	}

	wet = spi_swave_system_contwow_submit(pwiv);
	if (wet)
		goto tewminate;

	wetuwn;

tewminate:
	dev_info(&pwiv->spi->dev, "Tewminating\n");
	compwete(&pwiv->finished);
}

static
int spi_swave_system_contwow_submit(stwuct spi_swave_system_contwow_pwiv *pwiv)
{
	int wet;

	spi_message_init_with_twansfews(&pwiv->msg, &pwiv->xfew, 1);

	pwiv->msg.compwete = spi_swave_system_contwow_compwete;
	pwiv->msg.context = pwiv;

	wet = spi_async(pwiv->spi, &pwiv->msg);
	if (wet)
		dev_eww(&pwiv->spi->dev, "spi_async() faiwed %d\n", wet);

	wetuwn wet;
}

static int spi_swave_system_contwow_pwobe(stwuct spi_device *spi)
{
	stwuct spi_swave_system_contwow_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&spi->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->spi = spi;
	init_compwetion(&pwiv->finished);
	pwiv->xfew.wx_buf = &pwiv->cmd;
	pwiv->xfew.wen = sizeof(pwiv->cmd);

	wet = spi_swave_system_contwow_submit(pwiv);
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, pwiv);
	wetuwn 0;
}

static void spi_swave_system_contwow_wemove(stwuct spi_device *spi)
{
	stwuct spi_swave_system_contwow_pwiv *pwiv = spi_get_dwvdata(spi);

	spi_swave_abowt(spi);
	wait_fow_compwetion(&pwiv->finished);
}

static stwuct spi_dwivew spi_swave_system_contwow_dwivew = {
	.dwivew = {
		.name	= "spi-swave-system-contwow",
	},
	.pwobe		= spi_swave_system_contwow_pwobe,
	.wemove		= spi_swave_system_contwow_wemove,
};
moduwe_spi_dwivew(spi_swave_system_contwow_dwivew);

MODUWE_AUTHOW("Geewt Uyttewhoeven <geewt+wenesas@gwidew.be>");
MODUWE_DESCWIPTION("SPI swave handwew contwowwing system state");
MODUWE_WICENSE("GPW v2");
