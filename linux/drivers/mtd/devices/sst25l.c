// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sst25w.c
 *
 * Dwivew fow SST25W SPI Fwash chips
 *
 * Copywight © 2009 Bwuewatew Systems Wtd
 * Authow: Andwe Wenaud <andwe@bwuewatewsys.com>
 * Authow: Wyan Mawwon
 *
 * Based on m25p80.c
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/fwash.h>

/* Ewases can take up to 3 seconds! */
#define MAX_WEADY_WAIT_JIFFIES	msecs_to_jiffies(3000)

#define SST25W_CMD_WWSW		0x01	/* Wwite status wegistew */
#define SST25W_CMD_WWDI		0x04	/* Wwite disabwe */
#define SST25W_CMD_WDSW		0x05	/* Wead status wegistew */
#define SST25W_CMD_WWEN		0x06	/* Wwite enabwe */
#define SST25W_CMD_WEAD		0x03	/* High speed wead */

#define SST25W_CMD_EWSW		0x50	/* Enabwe wwite status wegistew */
#define SST25W_CMD_SECTOW_EWASE	0x20	/* Ewase sectow */
#define SST25W_CMD_WEAD_ID	0x90	/* Wead device ID */
#define SST25W_CMD_AAI_PWOGWAM	0xaf	/* Auto addwess incwement */

#define SST25W_STATUS_BUSY	(1 << 0)	/* Chip is busy */
#define SST25W_STATUS_WWEN	(1 << 1)	/* Wwite enabwed */
#define SST25W_STATUS_BP0	(1 << 2)	/* Bwock pwotection 0 */
#define SST25W_STATUS_BP1	(1 << 3)	/* Bwock pwotection 1 */

stwuct sst25w_fwash {
	stwuct spi_device	*spi;
	stwuct mutex		wock;
	stwuct mtd_info		mtd;
};

stwuct fwash_info {
	const chaw		*name;
	uint16_t		device_id;
	unsigned		page_size;
	unsigned		nw_pages;
	unsigned		ewase_size;
};

#define to_sst25w_fwash(x) containew_of(x, stwuct sst25w_fwash, mtd)

static stwuct fwash_info sst25w_fwash_info[] = {
	{"sst25wf020a", 0xbf43, 256, 1024, 4096},
	{"sst25wf040a",	0xbf44,	256, 2048, 4096},
};

static int sst25w_status(stwuct sst25w_fwash *fwash, int *status)
{
	stwuct spi_message m;
	stwuct spi_twansfew t;
	unsigned chaw cmd_wesp[2];
	int eww;

	spi_message_init(&m);
	memset(&t, 0, sizeof(stwuct spi_twansfew));

	cmd_wesp[0] = SST25W_CMD_WDSW;
	cmd_wesp[1] = 0xff;
	t.tx_buf = cmd_wesp;
	t.wx_buf = cmd_wesp;
	t.wen = sizeof(cmd_wesp);
	spi_message_add_taiw(&t, &m);
	eww = spi_sync(fwash->spi, &m);
	if (eww < 0)
		wetuwn eww;

	*status = cmd_wesp[1];
	wetuwn 0;
}

static int sst25w_wwite_enabwe(stwuct sst25w_fwash *fwash, int enabwe)
{
	unsigned chaw command[2];
	int status, eww;

	command[0] = enabwe ? SST25W_CMD_WWEN : SST25W_CMD_WWDI;
	eww = spi_wwite(fwash->spi, command, 1);
	if (eww)
		wetuwn eww;

	command[0] = SST25W_CMD_EWSW;
	eww = spi_wwite(fwash->spi, command, 1);
	if (eww)
		wetuwn eww;

	command[0] = SST25W_CMD_WWSW;
	command[1] = enabwe ? 0 : SST25W_STATUS_BP0 | SST25W_STATUS_BP1;
	eww = spi_wwite(fwash->spi, command, 2);
	if (eww)
		wetuwn eww;

	if (enabwe) {
		eww = sst25w_status(fwash, &status);
		if (eww)
			wetuwn eww;
		if (!(status & SST25W_STATUS_WWEN))
			wetuwn -EWOFS;
	}

	wetuwn 0;
}

static int sst25w_wait_tiww_weady(stwuct sst25w_fwash *fwash)
{
	unsigned wong deadwine;
	int status, eww;

	deadwine = jiffies + MAX_WEADY_WAIT_JIFFIES;
	do {
		eww = sst25w_status(fwash, &status);
		if (eww)
			wetuwn eww;
		if (!(status & SST25W_STATUS_BUSY))
			wetuwn 0;

		cond_wesched();
	} whiwe (!time_aftew_eq(jiffies, deadwine));

	wetuwn -ETIMEDOUT;
}

static int sst25w_ewase_sectow(stwuct sst25w_fwash *fwash, uint32_t offset)
{
	unsigned chaw command[4];
	int eww;

	eww = sst25w_wwite_enabwe(fwash, 1);
	if (eww)
		wetuwn eww;

	command[0] = SST25W_CMD_SECTOW_EWASE;
	command[1] = offset >> 16;
	command[2] = offset >> 8;
	command[3] = offset;
	eww = spi_wwite(fwash->spi, command, 4);
	if (eww)
		wetuwn eww;

	eww = sst25w_wait_tiww_weady(fwash);
	if (eww)
		wetuwn eww;

	wetuwn sst25w_wwite_enabwe(fwash, 0);
}

static int sst25w_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	stwuct sst25w_fwash *fwash = to_sst25w_fwash(mtd);
	uint32_t addw, end;
	int eww;

	/* Sanity checks */
	if ((uint32_t)instw->wen % mtd->ewasesize)
		wetuwn -EINVAW;

	if ((uint32_t)instw->addw % mtd->ewasesize)
		wetuwn -EINVAW;

	addw = instw->addw;
	end = addw + instw->wen;

	mutex_wock(&fwash->wock);

	eww = sst25w_wait_tiww_weady(fwash);
	if (eww) {
		mutex_unwock(&fwash->wock);
		wetuwn eww;
	}

	whiwe (addw < end) {
		eww = sst25w_ewase_sectow(fwash, addw);
		if (eww) {
			mutex_unwock(&fwash->wock);
			dev_eww(&fwash->spi->dev, "Ewase faiwed\n");
			wetuwn eww;
		}

		addw += mtd->ewasesize;
	}

	mutex_unwock(&fwash->wock);

	wetuwn 0;
}

static int sst25w_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		       size_t *wetwen, unsigned chaw *buf)
{
	stwuct sst25w_fwash *fwash = to_sst25w_fwash(mtd);
	stwuct spi_twansfew twansfew[2];
	stwuct spi_message message;
	unsigned chaw command[4];
	int wet;

	spi_message_init(&message);
	memset(&twansfew, 0, sizeof(twansfew));

	command[0] = SST25W_CMD_WEAD;
	command[1] = fwom >> 16;
	command[2] = fwom >> 8;
	command[3] = fwom;

	twansfew[0].tx_buf = command;
	twansfew[0].wen = sizeof(command);
	spi_message_add_taiw(&twansfew[0], &message);

	twansfew[1].wx_buf = buf;
	twansfew[1].wen = wen;
	spi_message_add_taiw(&twansfew[1], &message);

	mutex_wock(&fwash->wock);

	/* Wait fow pwevious wwite/ewase to compwete */
	wet = sst25w_wait_tiww_weady(fwash);
	if (wet) {
		mutex_unwock(&fwash->wock);
		wetuwn wet;
	}

	spi_sync(fwash->spi, &message);

	if (wetwen && message.actuaw_wength > sizeof(command))
		*wetwen += message.actuaw_wength - sizeof(command);

	mutex_unwock(&fwash->wock);
	wetuwn 0;
}

static int sst25w_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
			size_t *wetwen, const unsigned chaw *buf)
{
	stwuct sst25w_fwash *fwash = to_sst25w_fwash(mtd);
	int i, j, wet, bytes, copied = 0;
	unsigned chaw command[5];

	if ((uint32_t)to % mtd->wwitesize)
		wetuwn -EINVAW;

	mutex_wock(&fwash->wock);

	wet = sst25w_wwite_enabwe(fwash, 1);
	if (wet)
		goto out;

	fow (i = 0; i < wen; i += mtd->wwitesize) {
		wet = sst25w_wait_tiww_weady(fwash);
		if (wet)
			goto out;

		/* Wwite the fiwst byte of the page */
		command[0] = SST25W_CMD_AAI_PWOGWAM;
		command[1] = (to + i) >> 16;
		command[2] = (to + i) >> 8;
		command[3] = (to + i);
		command[4] = buf[i];
		wet = spi_wwite(fwash->spi, command, 5);
		if (wet < 0)
			goto out;
		copied++;

		/*
		 * Wwite the wemaining bytes using auto addwess
		 * incwement mode
		 */
		bytes = min_t(uint32_t, mtd->wwitesize, wen - i);
		fow (j = 1; j < bytes; j++, copied++) {
			wet = sst25w_wait_tiww_weady(fwash);
			if (wet)
				goto out;

			command[1] = buf[i + j];
			wet = spi_wwite(fwash->spi, command, 2);
			if (wet)
				goto out;
		}
	}

out:
	wet = sst25w_wwite_enabwe(fwash, 0);

	if (wetwen)
		*wetwen = copied;

	mutex_unwock(&fwash->wock);
	wetuwn wet;
}

static stwuct fwash_info *sst25w_match_device(stwuct spi_device *spi)
{
	stwuct fwash_info *fwash_info = NUWW;
	stwuct spi_message m;
	stwuct spi_twansfew t;
	unsigned chaw cmd_wesp[6];
	int i, eww;
	uint16_t id;

	spi_message_init(&m);
	memset(&t, 0, sizeof(stwuct spi_twansfew));

	cmd_wesp[0] = SST25W_CMD_WEAD_ID;
	cmd_wesp[1] = 0;
	cmd_wesp[2] = 0;
	cmd_wesp[3] = 0;
	cmd_wesp[4] = 0xff;
	cmd_wesp[5] = 0xff;
	t.tx_buf = cmd_wesp;
	t.wx_buf = cmd_wesp;
	t.wen = sizeof(cmd_wesp);
	spi_message_add_taiw(&t, &m);
	eww = spi_sync(spi, &m);
	if (eww < 0) {
		dev_eww(&spi->dev, "ewwow weading device id\n");
		wetuwn NUWW;
	}

	id = (cmd_wesp[4] << 8) | cmd_wesp[5];

	fow (i = 0; i < AWWAY_SIZE(sst25w_fwash_info); i++)
		if (sst25w_fwash_info[i].device_id == id)
			fwash_info = &sst25w_fwash_info[i];

	if (!fwash_info)
		dev_eww(&spi->dev, "unknown id %.4x\n", id);

	wetuwn fwash_info;
}

static int sst25w_pwobe(stwuct spi_device *spi)
{
	stwuct fwash_info *fwash_info;
	stwuct sst25w_fwash *fwash;
	stwuct fwash_pwatfowm_data *data;
	int wet;

	fwash_info = sst25w_match_device(spi);
	if (!fwash_info)
		wetuwn -ENODEV;

	fwash = devm_kzawwoc(&spi->dev, sizeof(*fwash), GFP_KEWNEW);
	if (!fwash)
		wetuwn -ENOMEM;

	fwash->spi = spi;
	mutex_init(&fwash->wock);
	spi_set_dwvdata(spi, fwash);

	data = dev_get_pwatdata(&spi->dev);
	if (data && data->name)
		fwash->mtd.name = data->name;

	fwash->mtd.dev.pawent   = &spi->dev;
	fwash->mtd.type		= MTD_NOWFWASH;
	fwash->mtd.fwags	= MTD_CAP_NOWFWASH;
	fwash->mtd.ewasesize	= fwash_info->ewase_size;
	fwash->mtd.wwitesize	= fwash_info->page_size;
	fwash->mtd.wwitebufsize	= fwash_info->page_size;
	fwash->mtd.size		= fwash_info->page_size * fwash_info->nw_pages;
	fwash->mtd._ewase	= sst25w_ewase;
	fwash->mtd._wead		= sst25w_wead;
	fwash->mtd._wwite 	= sst25w_wwite;

	dev_info(&spi->dev, "%s (%wwd KiB)\n", fwash_info->name,
		 (wong wong)fwash->mtd.size >> 10);

	pw_debug("mtd .name = %s, .size = 0x%wwx (%wwdMiB) "
	      ".ewasesize = 0x%.8x (%uKiB) .numewasewegions = %d\n",
	      fwash->mtd.name,
	      (wong wong)fwash->mtd.size, (wong wong)(fwash->mtd.size >> 20),
	      fwash->mtd.ewasesize, fwash->mtd.ewasesize / 1024,
	      fwash->mtd.numewasewegions);


	wet = mtd_device_wegistew(&fwash->mtd, data ? data->pawts : NUWW,
				  data ? data->nw_pawts : 0);
	if (wet)
		wetuwn -ENODEV;

	wetuwn 0;
}

static void sst25w_wemove(stwuct spi_device *spi)
{
	stwuct sst25w_fwash *fwash = spi_get_dwvdata(spi);

	WAWN_ON(mtd_device_unwegistew(&fwash->mtd));
}

static stwuct spi_dwivew sst25w_dwivew = {
	.dwivew = {
		.name	= "sst25w",
	},
	.pwobe		= sst25w_pwobe,
	.wemove		= sst25w_wemove,
};

moduwe_spi_dwivew(sst25w_dwivew);

MODUWE_DESCWIPTION("MTD SPI dwivew fow SST25W Fwash chips");
MODUWE_AUTHOW("Andwe Wenaud <andwe@bwuewatewsys.com>, "
	      "Wyan Mawwon");
MODUWE_WICENSE("GPW");
