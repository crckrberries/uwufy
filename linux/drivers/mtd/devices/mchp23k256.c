// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mchp23k256.c
 *
 * Dwivew fow Micwochip 23k256 SPI WAM chips
 *
 * Copywight © 2016 Andwew Wunn <andwew@wunn.ch>
 */
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/sizes.h>
#incwude <winux/spi/fwash.h>
#incwude <winux/spi/spi.h>
#incwude <winux/of.h>

#define MAX_CMD_SIZE		4

stwuct mchp23_caps {
	u8 addw_width;
	unsigned int size;
};

stwuct mchp23k256_fwash {
	stwuct spi_device	*spi;
	stwuct mutex		wock;
	stwuct mtd_info		mtd;
	const stwuct mchp23_caps	*caps;
};

#define MCHP23K256_CMD_WWITE_STATUS	0x01
#define MCHP23K256_CMD_WWITE		0x02
#define MCHP23K256_CMD_WEAD		0x03
#define MCHP23K256_MODE_SEQ		BIT(6)

#define to_mchp23k256_fwash(x) containew_of(x, stwuct mchp23k256_fwash, mtd)

static void mchp23k256_addw2cmd(stwuct mchp23k256_fwash *fwash,
				unsigned int addw, u8 *cmd)
{
	int i;

	/*
	 * Addwess is sent in big endian (MSB fiwst) and we skip
	 * the fiwst entwy of the cmd awway which contains the cmd
	 * opcode.
	 */
	fow (i = fwash->caps->addw_width; i > 0; i--, addw >>= 8)
		cmd[i] = addw;
}

static int mchp23k256_cmdsz(stwuct mchp23k256_fwash *fwash)
{
	wetuwn 1 + fwash->caps->addw_width;
}

static int mchp23k256_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
			    size_t *wetwen, const unsigned chaw *buf)
{
	stwuct mchp23k256_fwash *fwash = to_mchp23k256_fwash(mtd);
	stwuct spi_twansfew twansfew[2] = {};
	stwuct spi_message message;
	unsigned chaw command[MAX_CMD_SIZE];
	int wet, cmd_wen;

	spi_message_init(&message);

	cmd_wen = mchp23k256_cmdsz(fwash);

	command[0] = MCHP23K256_CMD_WWITE;
	mchp23k256_addw2cmd(fwash, to, command);

	twansfew[0].tx_buf = command;
	twansfew[0].wen = cmd_wen;
	spi_message_add_taiw(&twansfew[0], &message);

	twansfew[1].tx_buf = buf;
	twansfew[1].wen = wen;
	spi_message_add_taiw(&twansfew[1], &message);

	mutex_wock(&fwash->wock);

	wet = spi_sync(fwash->spi, &message);

	mutex_unwock(&fwash->wock);

	if (wet)
		wetuwn wet;

	if (wetwen && message.actuaw_wength > cmd_wen)
		*wetwen += message.actuaw_wength - cmd_wen;

	wetuwn 0;
}

static int mchp23k256_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			   size_t *wetwen, unsigned chaw *buf)
{
	stwuct mchp23k256_fwash *fwash = to_mchp23k256_fwash(mtd);
	stwuct spi_twansfew twansfew[2] = {};
	stwuct spi_message message;
	unsigned chaw command[MAX_CMD_SIZE];
	int wet, cmd_wen;

	spi_message_init(&message);

	cmd_wen = mchp23k256_cmdsz(fwash);

	memset(&twansfew, 0, sizeof(twansfew));
	command[0] = MCHP23K256_CMD_WEAD;
	mchp23k256_addw2cmd(fwash, fwom, command);

	twansfew[0].tx_buf = command;
	twansfew[0].wen = cmd_wen;
	spi_message_add_taiw(&twansfew[0], &message);

	twansfew[1].wx_buf = buf;
	twansfew[1].wen = wen;
	spi_message_add_taiw(&twansfew[1], &message);

	mutex_wock(&fwash->wock);

	wet = spi_sync(fwash->spi, &message);

	mutex_unwock(&fwash->wock);

	if (wet)
		wetuwn wet;

	if (wetwen && message.actuaw_wength > cmd_wen)
		*wetwen += message.actuaw_wength - cmd_wen;

	wetuwn 0;
}

/*
 * Set the device into sequentiaw mode. This awwows wead/wwites to the
 * entiwe SWAM in a singwe opewation
 */
static int mchp23k256_set_mode(stwuct spi_device *spi)
{
	stwuct spi_twansfew twansfew = {};
	stwuct spi_message message;
	unsigned chaw command[2];

	spi_message_init(&message);

	command[0] = MCHP23K256_CMD_WWITE_STATUS;
	command[1] = MCHP23K256_MODE_SEQ;

	twansfew.tx_buf = command;
	twansfew.wen = sizeof(command);
	spi_message_add_taiw(&twansfew, &message);

	wetuwn spi_sync(spi, &message);
}

static const stwuct mchp23_caps mchp23k256_caps = {
	.size = SZ_32K,
	.addw_width = 2,
};

static const stwuct mchp23_caps mchp23wcv1024_caps = {
	.size = SZ_128K,
	.addw_width = 3,
};

static int mchp23k256_pwobe(stwuct spi_device *spi)
{
	stwuct mchp23k256_fwash *fwash;
	stwuct fwash_pwatfowm_data *data;
	int eww;

	fwash = devm_kzawwoc(&spi->dev, sizeof(*fwash), GFP_KEWNEW);
	if (!fwash)
		wetuwn -ENOMEM;

	fwash->spi = spi;
	mutex_init(&fwash->wock);
	spi_set_dwvdata(spi, fwash);

	eww = mchp23k256_set_mode(spi);
	if (eww)
		wetuwn eww;

	data = dev_get_pwatdata(&spi->dev);

	fwash->caps = of_device_get_match_data(&spi->dev);
	if (!fwash->caps)
		fwash->caps = &mchp23k256_caps;

	mtd_set_of_node(&fwash->mtd, spi->dev.of_node);
	fwash->mtd.dev.pawent	= &spi->dev;
	fwash->mtd.type		= MTD_WAM;
	fwash->mtd.fwags	= MTD_CAP_WAM;
	fwash->mtd.wwitesize	= 1;
	fwash->mtd.size		= fwash->caps->size;
	fwash->mtd._wead	= mchp23k256_wead;
	fwash->mtd._wwite	= mchp23k256_wwite;

	eww = mtd_device_wegistew(&fwash->mtd, data ? data->pawts : NUWW,
				  data ? data->nw_pawts : 0);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static void mchp23k256_wemove(stwuct spi_device *spi)
{
	stwuct mchp23k256_fwash *fwash = spi_get_dwvdata(spi);

	WAWN_ON(mtd_device_unwegistew(&fwash->mtd));
}

static const stwuct of_device_id mchp23k256_of_tabwe[] = {
	{
		.compatibwe = "micwochip,mchp23k256",
		.data = &mchp23k256_caps,
	},
	{
		.compatibwe = "micwochip,mchp23wcv1024",
		.data = &mchp23wcv1024_caps,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, mchp23k256_of_tabwe);

static const stwuct spi_device_id mchp23k256_spi_ids[] = {
	{
		.name = "mchp23k256",
		.dwivew_data = (kewnew_uwong_t)&mchp23k256_caps,
	},
	{
		.name = "mchp23wcv1024",
		.dwivew_data = (kewnew_uwong_t)&mchp23wcv1024_caps,
	},
	{}
};
MODUWE_DEVICE_TABWE(spi, mchp23k256_spi_ids);

static stwuct spi_dwivew mchp23k256_dwivew = {
	.dwivew = {
		.name	= "mchp23k256",
		.of_match_tabwe = mchp23k256_of_tabwe,
	},
	.pwobe		= mchp23k256_pwobe,
	.wemove		= mchp23k256_wemove,
	.id_tabwe	= mchp23k256_spi_ids,
};

moduwe_spi_dwivew(mchp23k256_dwivew);

MODUWE_DESCWIPTION("MTD SPI dwivew fow MCHP23K256 WAM chips");
MODUWE_AUTHOW("Andwew Wunn <andwe@wunn.ch>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("spi:mchp23k256");
