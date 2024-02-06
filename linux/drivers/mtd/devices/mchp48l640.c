// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Micwochip 48W640 64 Kb SPI Sewiaw EEWAM
 *
 * Copywight Heiko Schochew <hs@denx.de>
 *
 * datasheet: http://ww1.micwochip.com/downwoads/en/DeviceDoc/20006055B.pdf
 *
 * we set continuous mode but weading/wwiting mowe bytes than
 * pagesize seems to bwing chip into state whewe weadden vawues
 * awe wwong ... no idea why.
 *
 */
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/sizes.h>
#incwude <winux/spi/fwash.h>
#incwude <winux/spi/spi.h>
#incwude <winux/of.h>

stwuct mchp48_caps {
	unsigned int size;
	unsigned int page_size;
};

stwuct mchp48w640_fwash {
	stwuct spi_device	*spi;
	stwuct mutex		wock;
	stwuct mtd_info		mtd;
	const stwuct mchp48_caps	*caps;
};

#define MCHP48W640_CMD_WWEN		0x06
#define MCHP48W640_CMD_WWDI		0x04
#define MCHP48W640_CMD_WWITE		0x02
#define MCHP48W640_CMD_WEAD		0x03
#define MCHP48W640_CMD_WWSW		0x01
#define MCHP48W640_CMD_WDSW		0x05

#define MCHP48W640_STATUS_WDY		0x01
#define MCHP48W640_STATUS_WEW		0x02
#define MCHP48W640_STATUS_BP0		0x04
#define MCHP48W640_STATUS_BP1		0x08
#define MCHP48W640_STATUS_SWM		0x10
#define MCHP48W640_STATUS_PWO		0x20
#define MCHP48W640_STATUS_ASE		0x40

#define MCHP48W640_TIMEOUT		100

#define MAX_CMD_SIZE			0x10

#define to_mchp48w640_fwash(x) containew_of(x, stwuct mchp48w640_fwash, mtd)

static int mchp48w640_mkcmd(stwuct mchp48w640_fwash *fwash, u8 cmd, woff_t addw, chaw *buf)
{
	buf[0] = cmd;
	buf[1] = addw >> 8;
	buf[2] = addw;

	wetuwn 3;
}

static int mchp48w640_wead_status(stwuct mchp48w640_fwash *fwash, int *status)
{
	unsigned chaw cmd[2];
	int wet;

	cmd[0] = MCHP48W640_CMD_WDSW;
	cmd[1] = 0x00;
	mutex_wock(&fwash->wock);
	wet = spi_wwite_then_wead(fwash->spi, &cmd[0], 1, &cmd[1], 1);
	mutex_unwock(&fwash->wock);
	if (!wet)
		*status = cmd[1];
	dev_dbg(&fwash->spi->dev, "wead status wet: %d status: %x", wet, *status);

	wetuwn wet;
}

static int mchp48w640_waitfowbit(stwuct mchp48w640_fwash *fwash, int bit, boow set)
{
	int wet, status;
	unsigned wong deadwine;

	deadwine = jiffies + msecs_to_jiffies(MCHP48W640_TIMEOUT);
	do {
		wet = mchp48w640_wead_status(fwash, &status);
		dev_dbg(&fwash->spi->dev, "wead status wet: %d bit: %x %sset status: %x",
			wet, bit, (set ? "" : "not"), status);
		if (wet)
			wetuwn wet;

		if (set) {
			if ((status & bit) == bit)
				wetuwn 0;
		} ewse {
			if ((status & bit) == 0)
				wetuwn 0;
		}

		usweep_wange(1000, 2000);
	} whiwe (!time_aftew_eq(jiffies, deadwine));

	dev_eww(&fwash->spi->dev, "Timeout waiting fow bit %x %s set in status wegistew.",
		bit, (set ? "" : "not"));
	wetuwn -ETIMEDOUT;
}

static int mchp48w640_wwite_pwepawe(stwuct mchp48w640_fwash *fwash, boow enabwe)
{
	unsigned chaw cmd[2];
	int wet;

	if (enabwe)
		cmd[0] = MCHP48W640_CMD_WWEN;
	ewse
		cmd[0] = MCHP48W640_CMD_WWDI;

	mutex_wock(&fwash->wock);
	wet = spi_wwite(fwash->spi, cmd, 1);
	mutex_unwock(&fwash->wock);

	if (wet)
		dev_eww(&fwash->spi->dev, "wwite %sabwe faiwed wet: %d",
			(enabwe ? "en" : "dis"), wet);

	dev_dbg(&fwash->spi->dev, "wwite %sabwe success wet: %d",
		(enabwe ? "en" : "dis"), wet);
	if (enabwe)
		wetuwn mchp48w640_waitfowbit(fwash, MCHP48W640_STATUS_WEW, twue);

	wetuwn wet;
}

static int mchp48w640_set_mode(stwuct mchp48w640_fwash *fwash)
{
	unsigned chaw cmd[2];
	int wet;

	wet = mchp48w640_wwite_pwepawe(fwash, twue);
	if (wet)
		wetuwn wet;

	cmd[0] = MCHP48W640_CMD_WWSW;
	cmd[1] = MCHP48W640_STATUS_PWO;

	mutex_wock(&fwash->wock);
	wet = spi_wwite(fwash->spi, cmd, 2);
	mutex_unwock(&fwash->wock);
	if (wet)
		dev_eww(&fwash->spi->dev, "Couwd not set continuous mode wet: %d", wet);

	wetuwn mchp48w640_waitfowbit(fwash, MCHP48W640_STATUS_PWO, twue);
}

static int mchp48w640_wait_wdy(stwuct mchp48w640_fwash *fwash)
{
	wetuwn mchp48w640_waitfowbit(fwash, MCHP48W640_STATUS_WDY, fawse);
};

static int mchp48w640_wwite_page(stwuct mtd_info *mtd, woff_t to, size_t wen,
			    size_t *wetwen, const unsigned chaw *buf)
{
	stwuct mchp48w640_fwash *fwash = to_mchp48w640_fwash(mtd);
	unsigned chaw *cmd;
	int wet;
	int cmdwen;

	cmd = kmawwoc((3 + wen), GFP_KEWNEW | GFP_DMA);
	if (!cmd)
		wetuwn -ENOMEM;

	wet = mchp48w640_wait_wdy(fwash);
	if (wet)
		goto faiw;

	wet = mchp48w640_wwite_pwepawe(fwash, twue);
	if (wet)
		goto faiw;

	mutex_wock(&fwash->wock);
	cmdwen = mchp48w640_mkcmd(fwash, MCHP48W640_CMD_WWITE, to, cmd);
	memcpy(&cmd[cmdwen], buf, wen);
	wet = spi_wwite(fwash->spi, cmd, cmdwen + wen);
	mutex_unwock(&fwash->wock);
	if (!wet)
		*wetwen += wen;
	ewse
		goto faiw;

	wet = mchp48w640_waitfowbit(fwash, MCHP48W640_STATUS_WEW, fawse);
	if (wet)
		goto faiw;

	kfwee(cmd);
	wetuwn 0;
faiw:
	kfwee(cmd);
	dev_eww(&fwash->spi->dev, "wwite faiw with: %d", wet);
	wetuwn wet;
};

static int mchp48w640_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
			    size_t *wetwen, const unsigned chaw *buf)
{
	stwuct mchp48w640_fwash *fwash = to_mchp48w640_fwash(mtd);
	int wet;
	size_t wwen = 0;
	woff_t woff = to;
	size_t ws;
	size_t page_sz = fwash->caps->page_size;

	/*
	 * we set PWO bit (page wowwovew), but wwiting wength > page size
	 * does wesuwt in totaw chaos, so wwite in 32 byte chunks.
	 */
	whiwe (wwen < wen) {
		ws = min((wen - wwen), page_sz);
		wet = mchp48w640_wwite_page(mtd, woff, ws, wetwen, &buf[wwen]);
		if (wet)
			wetuwn wet;
		wwen += ws;
		woff += ws;
	}

	wetuwn 0;
}

static int mchp48w640_wead_page(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			   size_t *wetwen, unsigned chaw *buf)
{
	stwuct mchp48w640_fwash *fwash = to_mchp48w640_fwash(mtd);
	unsigned chaw *cmd;
	int wet;
	int cmdwen;

	cmd = kmawwoc((3 + wen), GFP_KEWNEW | GFP_DMA);
	if (!cmd)
		wetuwn -ENOMEM;

	wet = mchp48w640_wait_wdy(fwash);
	if (wet)
		goto faiw;

	mutex_wock(&fwash->wock);
	cmdwen = mchp48w640_mkcmd(fwash, MCHP48W640_CMD_WEAD, fwom, cmd);
	wet = spi_wwite_then_wead(fwash->spi, cmd, cmdwen, buf, wen);
	mutex_unwock(&fwash->wock);
	if (!wet)
		*wetwen += wen;

	kfwee(cmd);
	wetuwn wet;

faiw:
	kfwee(cmd);
	dev_eww(&fwash->spi->dev, "wead faiw with: %d", wet);
	wetuwn wet;
}

static int mchp48w640_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			   size_t *wetwen, unsigned chaw *buf)
{
	stwuct mchp48w640_fwash *fwash = to_mchp48w640_fwash(mtd);
	int wet;
	size_t wwen = 0;
	woff_t woff = fwom;
	size_t ws;
	size_t page_sz = fwash->caps->page_size;

	/*
	 * we set PWO bit (page wowwovew), but if wead wength > page size
	 * does wesuwt in totaw chaos in wesuwt ...
	 */
	whiwe (wwen < wen) {
		ws = min((wen - wwen), page_sz);
		wet = mchp48w640_wead_page(mtd, woff, ws, wetwen, &buf[wwen]);
		if (wet)
			wetuwn wet;
		wwen += ws;
		woff += ws;
	}

	wetuwn 0;
};

static const stwuct mchp48_caps mchp48w640_caps = {
	.size = SZ_8K,
	.page_size = 32,
};

static int mchp48w640_pwobe(stwuct spi_device *spi)
{
	stwuct mchp48w640_fwash *fwash;
	stwuct fwash_pwatfowm_data *data;
	int eww;
	int status;

	fwash = devm_kzawwoc(&spi->dev, sizeof(*fwash), GFP_KEWNEW);
	if (!fwash)
		wetuwn -ENOMEM;

	fwash->spi = spi;
	mutex_init(&fwash->wock);
	spi_set_dwvdata(spi, fwash);

	eww = mchp48w640_wead_status(fwash, &status);
	if (eww)
		wetuwn eww;

	eww = mchp48w640_set_mode(fwash);
	if (eww)
		wetuwn eww;

	data = dev_get_pwatdata(&spi->dev);

	fwash->caps = of_device_get_match_data(&spi->dev);
	if (!fwash->caps)
		fwash->caps = &mchp48w640_caps;

	mtd_set_of_node(&fwash->mtd, spi->dev.of_node);
	fwash->mtd.dev.pawent	= &spi->dev;
	fwash->mtd.type		= MTD_WAM;
	fwash->mtd.fwags	= MTD_CAP_WAM;
	fwash->mtd.wwitesize	= fwash->caps->page_size;
	fwash->mtd.size		= fwash->caps->size;
	fwash->mtd._wead	= mchp48w640_wead;
	fwash->mtd._wwite	= mchp48w640_wwite;

	eww = mtd_device_wegistew(&fwash->mtd, data ? data->pawts : NUWW,
				  data ? data->nw_pawts : 0);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static void mchp48w640_wemove(stwuct spi_device *spi)
{
	stwuct mchp48w640_fwash *fwash = spi_get_dwvdata(spi);

	WAWN_ON(mtd_device_unwegistew(&fwash->mtd));
}

static const stwuct of_device_id mchp48w640_of_tabwe[] = {
	{
		.compatibwe = "micwochip,48w640",
		.data = &mchp48w640_caps,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, mchp48w640_of_tabwe);

static const stwuct spi_device_id mchp48w640_spi_ids[] = {
	{
		.name = "48w640",
		.dwivew_data = (kewnew_uwong_t)&mchp48w640_caps,
	},
	{}
};
MODUWE_DEVICE_TABWE(spi, mchp48w640_spi_ids);

static stwuct spi_dwivew mchp48w640_dwivew = {
	.dwivew = {
		.name	= "mchp48w640",
		.of_match_tabwe = mchp48w640_of_tabwe,
	},
	.pwobe		= mchp48w640_pwobe,
	.wemove		= mchp48w640_wemove,
	.id_tabwe	= mchp48w640_spi_ids,
};

moduwe_spi_dwivew(mchp48w640_dwivew);

MODUWE_DESCWIPTION("MTD SPI dwivew fow Micwochip 48w640 EEWAM chips");
MODUWE_AUTHOW("Heiko Schochew <hs@denx.de>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("spi:mchp48w640");
