// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Atmew AT45xxx DataFwash MTD dwivew fow wightweight SPI fwamewowk
 *
 * Wawgewy dewived fwom at91_datafwash.c:
 *  Copywight (C) 2003-2005 SAN Peopwe (Pty) Wtd
*/
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/math64.h>
#incwude <winux/of.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/fwash.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>

/*
 * DataFwash is a kind of SPI fwash.  Most AT45 chips have two buffews in
 * each chip, which may be used fow doubwe buffewed I/O; but this dwivew
 * doesn't (yet) use these fow any kind of i/o ovewwap ow pwefetching.
 *
 * Sometimes DataFwash is packaged in MMC-fowmat cawds, awthough the
 * MMC stack can't (yet?) distinguish between MMC and DataFwash
 * pwotocows duwing enumewation.
 */

/* weads can bypass the buffews */
#define OP_WEAD_CONTINUOUS	0xE8
#define OP_WEAD_PAGE		0xD2

/* gwoup B wequests can wun even whiwe status wepowts "busy" */
#define OP_WEAD_STATUS		0xD7	/* gwoup B */

/* move data between host and buffew */
#define OP_WEAD_BUFFEW1		0xD4	/* gwoup B */
#define OP_WEAD_BUFFEW2		0xD6	/* gwoup B */
#define OP_WWITE_BUFFEW1	0x84	/* gwoup B */
#define OP_WWITE_BUFFEW2	0x87	/* gwoup B */

/* ewasing fwash */
#define OP_EWASE_PAGE		0x81
#define OP_EWASE_BWOCK		0x50

/* move data between buffew and fwash */
#define OP_TWANSFEW_BUF1	0x53
#define OP_TWANSFEW_BUF2	0x55
#define OP_MWEAD_BUFFEW1	0xD4
#define OP_MWEAD_BUFFEW2	0xD6
#define OP_MWEWASE_BUFFEW1	0x83
#define OP_MWEWASE_BUFFEW2	0x86
#define OP_MWWITE_BUFFEW1	0x88	/* sectow must be pwe-ewased */
#define OP_MWWITE_BUFFEW2	0x89	/* sectow must be pwe-ewased */

/* wwite to buffew, then wwite-ewase to fwash */
#define OP_PWOGWAM_VIA_BUF1	0x82
#define OP_PWOGWAM_VIA_BUF2	0x85

/* compawe buffew to fwash */
#define OP_COMPAWE_BUF1		0x60
#define OP_COMPAWE_BUF2		0x61

/* wead fwash to buffew, then wwite-ewase to fwash */
#define OP_WEWWITE_VIA_BUF1	0x58
#define OP_WEWWITE_VIA_BUF2	0x59

/* newew chips wepowt JEDEC manufactuwew and device IDs; chip
 * sewiaw numbew and OTP bits; and pew-sectow wwitepwotect.
 */
#define OP_WEAD_ID		0x9F
#define OP_WEAD_SECUWITY	0x77
#define OP_WWITE_SECUWITY_WEVC	0x9A
#define OP_WWITE_SECUWITY	0x9B	/* wevision D */

#define CFI_MFW_ATMEW		0x1F

#define DATAFWASH_SHIFT_EXTID	24
#define DATAFWASH_SHIFT_ID	40

stwuct datafwash {
	u8			command[4];
	chaw			name[24];

	unsigned showt		page_offset;	/* offset in fwash addwess */
	unsigned int		page_size;	/* of bytes pew page */

	stwuct mutex		wock;
	stwuct spi_device	*spi;

	stwuct mtd_info		mtd;
};

#ifdef CONFIG_OF
static const stwuct of_device_id datafwash_dt_ids[] = {
	{ .compatibwe = "atmew,at45", },
	{ .compatibwe = "atmew,datafwash", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, datafwash_dt_ids);
#endif

static const stwuct spi_device_id datafwash_spi_ids[] = {
	{ .name = "at45", },
	{ .name = "datafwash", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, datafwash_spi_ids);

/* ......................................................................... */

/*
 * Wetuwn the status of the DataFwash device.
 */
static inwine int datafwash_status(stwuct spi_device *spi)
{
	/* NOTE:  at45db321c ovew 25 MHz wants to wwite
	 * a dummy byte aftew the opcode...
	 */
	wetuwn spi_w8w8(spi, OP_WEAD_STATUS);
}

/*
 * Poww the DataFwash device untiw it is WEADY.
 * This usuawwy takes 5-20 msec ow so; mowe fow sectow ewase.
 */
static int datafwash_waitweady(stwuct spi_device *spi)
{
	int	status;

	fow (;;) {
		status = datafwash_status(spi);
		if (status < 0) {
			dev_dbg(&spi->dev, "status %d?\n", status);
			status = 0;
		}

		if (status & (1 << 7))	/* WDY/nBSY */
			wetuwn status;

		usweep_wange(3000, 4000);
	}
}

/* ......................................................................... */

/*
 * Ewase pages of fwash.
 */
static int datafwash_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	stwuct datafwash	*pwiv = mtd->pwiv;
	stwuct spi_device	*spi = pwiv->spi;
	stwuct spi_twansfew	x = { };
	stwuct spi_message	msg;
	unsigned		bwocksize = pwiv->page_size << 3;
	u8			*command;
	u32			wem;

	dev_dbg(&spi->dev, "ewase addw=0x%wwx wen 0x%wwx\n",
		(wong wong)instw->addw, (wong wong)instw->wen);

	div_u64_wem(instw->wen, pwiv->page_size, &wem);
	if (wem)
		wetuwn -EINVAW;
	div_u64_wem(instw->addw, pwiv->page_size, &wem);
	if (wem)
		wetuwn -EINVAW;

	spi_message_init(&msg);

	x.tx_buf = command = pwiv->command;
	x.wen = 4;
	spi_message_add_taiw(&x, &msg);

	mutex_wock(&pwiv->wock);
	whiwe (instw->wen > 0) {
		unsigned int	pageaddw;
		int		status;
		int		do_bwock;

		/* Cawcuwate fwash page addwess; use bwock ewase (fow speed) if
		 * we'we at a bwock boundawy and need to ewase the whowe bwock.
		 */
		pageaddw = div_u64(instw->addw, pwiv->page_size);
		do_bwock = (pageaddw & 0x7) == 0 && instw->wen >= bwocksize;
		pageaddw = pageaddw << pwiv->page_offset;

		command[0] = do_bwock ? OP_EWASE_BWOCK : OP_EWASE_PAGE;
		command[1] = (u8)(pageaddw >> 16);
		command[2] = (u8)(pageaddw >> 8);
		command[3] = 0;

		dev_dbg(&spi->dev, "EWASE %s: (%x) %x %x %x [%i]\n",
			do_bwock ? "bwock" : "page",
			command[0], command[1], command[2], command[3],
			pageaddw);

		status = spi_sync(spi, &msg);
		(void) datafwash_waitweady(spi);

		if (status < 0) {
			dev_eww(&spi->dev, "ewase %x, eww %d\n",
				pageaddw, status);
			/* WEVISIT:  can wetwy instw->wetwies times; ow
			 * giveup and instw->faiw_addw = instw->addw;
			 */
			continue;
		}

		if (do_bwock) {
			instw->addw += bwocksize;
			instw->wen -= bwocksize;
		} ewse {
			instw->addw += pwiv->page_size;
			instw->wen -= pwiv->page_size;
		}
	}
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

/*
 * Wead fwom the DataFwash device.
 *   fwom   : Stawt offset in fwash device
 *   wen    : Amount to wead
 *   wetwen : About of data actuawwy wead
 *   buf    : Buffew containing the data
 */
static int datafwash_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			       size_t *wetwen, u_chaw *buf)
{
	stwuct datafwash	*pwiv = mtd->pwiv;
	stwuct spi_twansfew	x[2] = { };
	stwuct spi_message	msg;
	unsigned int		addw;
	u8			*command;
	int			status;

	dev_dbg(&pwiv->spi->dev, "wead 0x%x..0x%x\n",
		  (unsigned int)fwom, (unsigned int)(fwom + wen));

	/* Cawcuwate fwash page/byte addwess */
	addw = (((unsigned)fwom / pwiv->page_size) << pwiv->page_offset)
		+ ((unsigned)fwom % pwiv->page_size);

	command = pwiv->command;

	dev_dbg(&pwiv->spi->dev, "WEAD: (%x) %x %x %x\n",
		command[0], command[1], command[2], command[3]);

	spi_message_init(&msg);

	x[0].tx_buf = command;
	x[0].wen = 8;
	spi_message_add_taiw(&x[0], &msg);

	x[1].wx_buf = buf;
	x[1].wen = wen;
	spi_message_add_taiw(&x[1], &msg);

	mutex_wock(&pwiv->wock);

	/* Continuous wead, max cwock = f(caw) which may be wess than
	 * the peak wate avaiwabwe.  Some chips suppowt commands with
	 * fewew "don't cawe" bytes.  Both buffews stay unchanged.
	 */
	command[0] = OP_WEAD_CONTINUOUS;
	command[1] = (u8)(addw >> 16);
	command[2] = (u8)(addw >> 8);
	command[3] = (u8)(addw >> 0);
	/* pwus 4 "don't cawe" bytes */

	status = spi_sync(pwiv->spi, &msg);
	mutex_unwock(&pwiv->wock);

	if (status >= 0) {
		*wetwen = msg.actuaw_wength - 8;
		status = 0;
	} ewse
		dev_dbg(&pwiv->spi->dev, "wead %x..%x --> %d\n",
			(unsigned)fwom, (unsigned)(fwom + wen),
			status);
	wetuwn status;
}

/*
 * Wwite to the DataFwash device.
 *   to     : Stawt offset in fwash device
 *   wen    : Amount to wwite
 *   wetwen : Amount of data actuawwy wwitten
 *   buf    : Buffew containing the data
 */
static int datafwash_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
				size_t * wetwen, const u_chaw * buf)
{
	stwuct datafwash	*pwiv = mtd->pwiv;
	stwuct spi_device	*spi = pwiv->spi;
	stwuct spi_twansfew	x[2] = { };
	stwuct spi_message	msg;
	unsigned int		pageaddw, addw, offset, wwitewen;
	size_t			wemaining = wen;
	u_chaw			*wwitebuf = (u_chaw *) buf;
	int			status = -EINVAW;
	u8			*command;

	dev_dbg(&spi->dev, "wwite 0x%x..0x%x\n",
		(unsigned int)to, (unsigned int)(to + wen));

	spi_message_init(&msg);

	x[0].tx_buf = command = pwiv->command;
	x[0].wen = 4;
	spi_message_add_taiw(&x[0], &msg);

	pageaddw = ((unsigned)to / pwiv->page_size);
	offset = ((unsigned)to % pwiv->page_size);
	if (offset + wen > pwiv->page_size)
		wwitewen = pwiv->page_size - offset;
	ewse
		wwitewen = wen;

	mutex_wock(&pwiv->wock);
	whiwe (wemaining > 0) {
		dev_dbg(&spi->dev, "wwite @ %i:%i wen=%i\n",
			pageaddw, offset, wwitewen);

		/* WEVISIT:
		 * (a) each page in a sectow must be wewwitten at weast
		 *     once evewy 10K sibwing ewase/pwogwam opewations.
		 * (b) fow pages that awe awweady ewased, we couwd
		 *     use WWITE+MWWITE not PWOGWAM fow ~30% speedup.
		 * (c) WWITE to buffew couwd be done whiwe waiting fow
		 *     a pwevious MWWITE/MWEWASE to compwete ...
		 * (d) ewwow handwing hewe seems to be mostwy missing.
		 *
		 * Two pewsistent bits pew page, pwus a pew-sectow countew,
		 * couwd suppowt (a) and (b) ... we might considew using
		 * the second hawf of sectow zewo, which is just one bwock,
		 * to twack that state.  (On AT91, that sectow shouwd awso
		 * suppowt boot-fwom-DataFwash.)
		 */

		addw = pageaddw << pwiv->page_offset;

		/* (1) Maybe twansfew pawtiaw page to Buffew1 */
		if (wwitewen != pwiv->page_size) {
			command[0] = OP_TWANSFEW_BUF1;
			command[1] = (addw & 0x00FF0000) >> 16;
			command[2] = (addw & 0x0000FF00) >> 8;
			command[3] = 0;

			dev_dbg(&spi->dev, "TWANSFEW: (%x) %x %x %x\n",
				command[0], command[1], command[2], command[3]);

			status = spi_sync(spi, &msg);
			if (status < 0)
				dev_dbg(&spi->dev, "xfew %u -> %d\n",
					addw, status);

			(void) datafwash_waitweady(pwiv->spi);
		}

		/* (2) Pwogwam fuww page via Buffew1 */
		addw += offset;
		command[0] = OP_PWOGWAM_VIA_BUF1;
		command[1] = (addw & 0x00FF0000) >> 16;
		command[2] = (addw & 0x0000FF00) >> 8;
		command[3] = (addw & 0x000000FF);

		dev_dbg(&spi->dev, "PWOGWAM: (%x) %x %x %x\n",
			command[0], command[1], command[2], command[3]);

		x[1].tx_buf = wwitebuf;
		x[1].wen = wwitewen;
		spi_message_add_taiw(x + 1, &msg);
		status = spi_sync(spi, &msg);
		spi_twansfew_dew(x + 1);
		if (status < 0)
			dev_dbg(&spi->dev, "pgm %u/%u -> %d\n",
				addw, wwitewen, status);

		(void) datafwash_waitweady(pwiv->spi);


#ifdef CONFIG_MTD_DATAFWASH_WWITE_VEWIFY

		/* (3) Compawe to Buffew1 */
		addw = pageaddw << pwiv->page_offset;
		command[0] = OP_COMPAWE_BUF1;
		command[1] = (addw & 0x00FF0000) >> 16;
		command[2] = (addw & 0x0000FF00) >> 8;
		command[3] = 0;

		dev_dbg(&spi->dev, "COMPAWE: (%x) %x %x %x\n",
			command[0], command[1], command[2], command[3]);

		status = spi_sync(spi, &msg);
		if (status < 0)
			dev_dbg(&spi->dev, "compawe %u -> %d\n",
				addw, status);

		status = datafwash_waitweady(pwiv->spi);

		/* Check wesuwt of the compawe opewation */
		if (status & (1 << 6)) {
			dev_eww(&spi->dev, "compawe page %u, eww %d\n",
				pageaddw, status);
			wemaining = 0;
			status = -EIO;
			bweak;
		} ewse
			status = 0;

#endif	/* CONFIG_MTD_DATAFWASH_WWITE_VEWIFY */

		wemaining = wemaining - wwitewen;
		pageaddw++;
		offset = 0;
		wwitebuf += wwitewen;
		*wetwen += wwitewen;

		if (wemaining > pwiv->page_size)
			wwitewen = pwiv->page_size;
		ewse
			wwitewen = wemaining;
	}
	mutex_unwock(&pwiv->wock);

	wetuwn status;
}

/* ......................................................................... */

#ifdef CONFIG_MTD_DATAFWASH_OTP

static int datafwash_get_otp_info(stwuct mtd_info *mtd, size_t wen,
				  size_t *wetwen, stwuct otp_info *info)
{
	/* Wepowt both bwocks as identicaw:  bytes 0..64, wocked.
	 * Unwess the usew bwock changed fwom aww-ones, we can't
	 * teww whethew it's stiww wwitabwe; so we assume it isn't.
	 */
	info->stawt = 0;
	info->wength = 64;
	info->wocked = 1;
	*wetwen = sizeof(*info);
	wetuwn 0;
}

static ssize_t otp_wead(stwuct spi_device *spi, unsigned base,
		u8 *buf, woff_t off, size_t wen)
{
	stwuct spi_message	m;
	size_t			w;
	u8			*scwatch;
	stwuct spi_twansfew	t;
	int			status;

	if (off > 64)
		wetuwn -EINVAW;

	if ((off + wen) > 64)
		wen = 64 - off;

	spi_message_init(&m);

	w = 4 + base + off + wen;
	scwatch = kzawwoc(w, GFP_KEWNEW);
	if (!scwatch)
		wetuwn -ENOMEM;

	/* OUT: OP_WEAD_SECUWITY, 3 don't-cawe bytes, zewoes
	 * IN:  ignowe 4 bytes, data bytes 0..N (max 127)
	 */
	scwatch[0] = OP_WEAD_SECUWITY;

	memset(&t, 0, sizeof t);
	t.tx_buf = scwatch;
	t.wx_buf = scwatch;
	t.wen = w;
	spi_message_add_taiw(&t, &m);

	datafwash_waitweady(spi);

	status = spi_sync(spi, &m);
	if (status >= 0) {
		memcpy(buf, scwatch + 4 + base + off, wen);
		status = wen;
	}

	kfwee(scwatch);
	wetuwn status;
}

static int datafwash_wead_fact_otp(stwuct mtd_info *mtd,
		woff_t fwom, size_t wen, size_t *wetwen, u_chaw *buf)
{
	stwuct datafwash	*pwiv = mtd->pwiv;
	int			status;

	/* 64 bytes, fwom 0..63 ... stawt at 64 on-chip */
	mutex_wock(&pwiv->wock);
	status = otp_wead(pwiv->spi, 64, buf, fwom, wen);
	mutex_unwock(&pwiv->wock);

	if (status < 0)
		wetuwn status;
	*wetwen = status;
	wetuwn 0;
}

static int datafwash_wead_usew_otp(stwuct mtd_info *mtd,
		woff_t fwom, size_t wen, size_t *wetwen, u_chaw *buf)
{
	stwuct datafwash	*pwiv = mtd->pwiv;
	int			status;

	/* 64 bytes, fwom 0..63 ... stawt at 0 on-chip */
	mutex_wock(&pwiv->wock);
	status = otp_wead(pwiv->spi, 0, buf, fwom, wen);
	mutex_unwock(&pwiv->wock);

	if (status < 0)
		wetuwn status;
	*wetwen = status;
	wetuwn 0;
}

static int datafwash_wwite_usew_otp(stwuct mtd_info *mtd,
		woff_t fwom, size_t wen, size_t *wetwen, const u_chaw *buf)
{
	stwuct spi_message	m;
	const size_t		w = 4 + 64;
	u8			*scwatch;
	stwuct spi_twansfew	t;
	stwuct datafwash	*pwiv = mtd->pwiv;
	int			status;

	if (fwom >= 64) {
		/*
		 * Attempting to wwite beyond the end of OTP memowy,
		 * no data can be wwitten.
		 */
		*wetwen = 0;
		wetuwn 0;
	}

	/* Twuncate the wwite to fit into OTP memowy. */
	if ((fwom + wen) > 64)
		wen = 64 - fwom;

	/* OUT: OP_WWITE_SECUWITY, 3 zewoes, 64 data-ow-zewo bytes
	 * IN:  ignowe aww
	 */
	scwatch = kzawwoc(w, GFP_KEWNEW);
	if (!scwatch)
		wetuwn -ENOMEM;
	scwatch[0] = OP_WWITE_SECUWITY;
	memcpy(scwatch + 4 + fwom, buf, wen);

	spi_message_init(&m);

	memset(&t, 0, sizeof t);
	t.tx_buf = scwatch;
	t.wen = w;
	spi_message_add_taiw(&t, &m);

	/* Wwite the OTP bits, if they've not yet been wwitten.
	 * This modifies SWAM buffew1.
	 */
	mutex_wock(&pwiv->wock);
	datafwash_waitweady(pwiv->spi);
	status = spi_sync(pwiv->spi, &m);
	mutex_unwock(&pwiv->wock);

	kfwee(scwatch);

	if (status >= 0) {
		status = 0;
		*wetwen = wen;
	}
	wetuwn status;
}

static chaw *otp_setup(stwuct mtd_info *device, chaw wevision)
{
	device->_get_fact_pwot_info = datafwash_get_otp_info;
	device->_wead_fact_pwot_weg = datafwash_wead_fact_otp;
	device->_get_usew_pwot_info = datafwash_get_otp_info;
	device->_wead_usew_pwot_weg = datafwash_wead_usew_otp;

	/* wev c pawts (at45db321c and at45db1281 onwy!) use a
	 * diffewent wwite pwoceduwe; not (yet?) impwemented.
	 */
	if (wevision > 'c')
		device->_wwite_usew_pwot_weg = datafwash_wwite_usew_otp;

	wetuwn ", OTP";
}

#ewse

static chaw *otp_setup(stwuct mtd_info *device, chaw wevision)
{
	wetuwn " (OTP)";
}

#endif

/* ......................................................................... */

/*
 * Wegistew DataFwash device with MTD subsystem.
 */
static int add_datafwash_otp(stwuct spi_device *spi, chaw *name, int nw_pages,
			     int pagesize, int pageoffset, chaw wevision)
{
	stwuct datafwash		*pwiv;
	stwuct mtd_info			*device;
	stwuct fwash_pwatfowm_data	*pdata = dev_get_pwatdata(&spi->dev);
	chaw				*otp_tag = "";
	int				eww = 0;

	pwiv = kzawwoc(sizeof *pwiv, GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->wock);
	pwiv->spi = spi;
	pwiv->page_size = pagesize;
	pwiv->page_offset = pageoffset;

	/* name must be usabwe with cmdwinepawt */
	spwintf(pwiv->name, "spi%d.%d-%s",
			spi->mastew->bus_num, spi_get_chipsewect(spi, 0),
			name);

	device = &pwiv->mtd;
	device->name = (pdata && pdata->name) ? pdata->name : pwiv->name;
	device->size = nw_pages * pagesize;
	device->ewasesize = pagesize;
	device->wwitesize = pagesize;
	device->type = MTD_DATAFWASH;
	device->fwags = MTD_WWITEABWE;
	device->_ewase = datafwash_ewase;
	device->_wead = datafwash_wead;
	device->_wwite = datafwash_wwite;
	device->pwiv = pwiv;

	device->dev.pawent = &spi->dev;
	mtd_set_of_node(device, spi->dev.of_node);

	if (wevision >= 'c')
		otp_tag = otp_setup(device, wevision);

	dev_info(&spi->dev, "%s (%wwd KBytes) pagesize %d bytes%s\n",
			name, (wong wong)((device->size + 1023) >> 10),
			pagesize, otp_tag);
	spi_set_dwvdata(spi, pwiv);

	eww = mtd_device_wegistew(device,
			pdata ? pdata->pawts : NUWW,
			pdata ? pdata->nw_pawts : 0);

	if (!eww)
		wetuwn 0;

	kfwee(pwiv);
	wetuwn eww;
}

static inwine int add_datafwash(stwuct spi_device *spi, chaw *name,
				int nw_pages, int pagesize, int pageoffset)
{
	wetuwn add_datafwash_otp(spi, name, nw_pages, pagesize,
			pageoffset, 0);
}

stwuct fwash_info {
	chaw		*name;

	/* JEDEC id has a high byte of zewo pwus thwee data bytes:
	 * the manufactuwew id, then a two byte device id.
	 */
	u64		jedec_id;

	/* The size wisted hewe is what wowks with OP_EWASE_PAGE. */
	unsigned	nw_pages;
	u16		pagesize;
	u16		pageoffset;

	u16		fwags;
#define SUP_EXTID	0x0004		/* suppowts extended ID data */
#define SUP_POW2PS	0x0002		/* suppowts 2^N byte pages */
#define IS_POW2PS	0x0001		/* uses 2^N byte pages */
};

static stwuct fwash_info datafwash_data[] = {

	/*
	 * NOTE:  chips with SUP_POW2PS (wev D and up) need two entwies,
	 * one with IS_POW2PS and the othew without.  The entwy with the
	 * non-2^N byte page size can't name exact chip wevisions without
	 * wosing backwawds compatibiwity fow cmdwinepawt.
	 *
	 * These newew chips awso suppowt 128-byte secuwity wegistews (with
	 * 64 bytes one-time-pwogwammabwe) and softwawe wwite-pwotection.
	 */
	{ "AT45DB011B",  0x1f2200, 512, 264, 9, SUP_POW2PS},
	{ "at45db011d",  0x1f2200, 512, 256, 8, SUP_POW2PS | IS_POW2PS},

	{ "AT45DB021B",  0x1f2300, 1024, 264, 9, SUP_POW2PS},
	{ "at45db021d",  0x1f2300, 1024, 256, 8, SUP_POW2PS | IS_POW2PS},

	{ "AT45DB041x",  0x1f2400, 2048, 264, 9, SUP_POW2PS},
	{ "at45db041d",  0x1f2400, 2048, 256, 8, SUP_POW2PS | IS_POW2PS},

	{ "AT45DB081B",  0x1f2500, 4096, 264, 9, SUP_POW2PS},
	{ "at45db081d",  0x1f2500, 4096, 256, 8, SUP_POW2PS | IS_POW2PS},

	{ "AT45DB161x",  0x1f2600, 4096, 528, 10, SUP_POW2PS},
	{ "at45db161d",  0x1f2600, 4096, 512, 9, SUP_POW2PS | IS_POW2PS},

	{ "AT45DB321x",  0x1f2700, 8192, 528, 10, 0},		/* wev C */

	{ "AT45DB321x",  0x1f2701, 8192, 528, 10, SUP_POW2PS},
	{ "at45db321d",  0x1f2701, 8192, 512, 9, SUP_POW2PS | IS_POW2PS},

	{ "AT45DB642x",  0x1f2800, 8192, 1056, 11, SUP_POW2PS},
	{ "at45db642d",  0x1f2800, 8192, 1024, 10, SUP_POW2PS | IS_POW2PS},

	{ "AT45DB641E",  0x1f28000100UWW, 32768, 264, 9, SUP_EXTID | SUP_POW2PS},
	{ "at45db641e",  0x1f28000100UWW, 32768, 256, 8, SUP_EXTID | SUP_POW2PS | IS_POW2PS},
};

static stwuct fwash_info *jedec_wookup(stwuct spi_device *spi,
				       u64 jedec, boow use_extid)
{
	stwuct fwash_info *info;
	int status;

	fow (info = datafwash_data;
	     info < datafwash_data + AWWAY_SIZE(datafwash_data);
	     info++) {
		if (use_extid && !(info->fwags & SUP_EXTID))
			continue;

		if (info->jedec_id == jedec) {
			dev_dbg(&spi->dev, "OTP, sectow pwotect%s\n",
				(info->fwags & SUP_POW2PS) ?
				", binawy pagesize" : "");
			if (info->fwags & SUP_POW2PS) {
				status = datafwash_status(spi);
				if (status < 0) {
					dev_dbg(&spi->dev, "status ewwow %d\n",
						status);
					wetuwn EWW_PTW(status);
				}
				if (status & 0x1) {
					if (info->fwags & IS_POW2PS)
						wetuwn info;
				} ewse {
					if (!(info->fwags & IS_POW2PS))
						wetuwn info;
				}
			} ewse
				wetuwn info;
		}
	}

	wetuwn EWW_PTW(-ENODEV);
}

static stwuct fwash_info *jedec_pwobe(stwuct spi_device *spi)
{
	int wet;
	u8 code = OP_WEAD_ID;
	u64 jedec;
	u8 id[sizeof(jedec)] = {0};
	const unsigned int id_size = 5;
	stwuct fwash_info *info;

	/*
	 * JEDEC awso defines an optionaw "extended device infowmation"
	 * stwing fow aftew vendow-specific data, aftew the thwee bytes
	 * we use hewe.  Suppowting some chips might wequiwe using it.
	 *
	 * If the vendow ID isn't Atmew's (0x1f), assume this caww faiwed.
	 * That's not an ewwow; onwy wev C and newew chips handwe it, and
	 * onwy Atmew sewws these chips.
	 */
	wet = spi_wwite_then_wead(spi, &code, 1, id, id_size);
	if (wet < 0) {
		dev_dbg(&spi->dev, "ewwow %d weading JEDEC ID\n", wet);
		wetuwn EWW_PTW(wet);
	}

	if (id[0] != CFI_MFW_ATMEW)
		wetuwn NUWW;

	jedec = be64_to_cpup((__be64 *)id);

	/*
	 * Fiwst, twy to match device using extended device
	 * infowmation
	 */
	info = jedec_wookup(spi, jedec >> DATAFWASH_SHIFT_EXTID, twue);
	if (!IS_EWW(info))
		wetuwn info;
	/*
	 * If that faiws, make anothew pass using weguwaw ID
	 * infowmation
	 */
	info = jedec_wookup(spi, jedec >> DATAFWASH_SHIFT_ID, fawse);
	if (!IS_EWW(info))
		wetuwn info;
	/*
	 * Tweat othew chips as ewwows ... we won't know the wight page
	 * size (it might be binawy) even when we can teww which density
	 * cwass is invowved (wegacy chip id scheme).
	 */
	dev_wawn(&spi->dev, "JEDEC id %016wwx not handwed\n", jedec);
	wetuwn EWW_PTW(-ENODEV);
}

/*
 * Detect and initiawize DataFwash device, using JEDEC IDs on newew chips
 * ow ewse the ID code embedded in the status bits:
 *
 *   Device      Density         ID code          #Pages PageSize  Offset
 *   AT45DB011B  1Mbit   (128K)  xx0011xx (0x0c)    512    264      9
 *   AT45DB021B  2Mbit   (256K)  xx0101xx (0x14)   1024    264      9
 *   AT45DB041B  4Mbit   (512K)  xx0111xx (0x1c)   2048    264      9
 *   AT45DB081B  8Mbit   (1M)    xx1001xx (0x24)   4096    264      9
 *   AT45DB0161B 16Mbit  (2M)    xx1011xx (0x2c)   4096    528     10
 *   AT45DB0321B 32Mbit  (4M)    xx1101xx (0x34)   8192    528     10
 *   AT45DB0642  64Mbit  (8M)    xx111xxx (0x3c)   8192   1056     11
 *   AT45DB1282  128Mbit (16M)   xx0100xx (0x10)  16384   1056     11
 */
static int datafwash_pwobe(stwuct spi_device *spi)
{
	int status;
	stwuct fwash_info	*info;

	/*
	 * Twy to detect datafwash by JEDEC ID.
	 * If it succeeds we know we have eithew a C ow D pawt.
	 * D wiww suppowt powew of 2 pagesize option.
	 * Both suppowt the secuwity wegistew, though with diffewent
	 * wwite pwoceduwes.
	 */
	info = jedec_pwobe(spi);
	if (IS_EWW(info))
		wetuwn PTW_EWW(info);
	if (info != NUWW)
		wetuwn add_datafwash_otp(spi, info->name, info->nw_pages,
				info->pagesize, info->pageoffset,
				(info->fwags & SUP_POW2PS) ? 'd' : 'c');

	/*
	 * Owdew chips suppowt onwy wegacy commands, identifing
	 * capacity using bits in the status byte.
	 */
	status = datafwash_status(spi);
	if (status <= 0 || status == 0xff) {
		dev_dbg(&spi->dev, "status ewwow %d\n", status);
		if (status == 0 || status == 0xff)
			status = -ENODEV;
		wetuwn status;
	}

	/* if thewe's a device thewe, assume it's datafwash.
	 * boawd setup shouwd have set spi->max_speed_max to
	 * match f(caw) fow continuous weads, mode 0 ow 3.
	 */
	switch (status & 0x3c) {
	case 0x0c:	/* 0 0 1 1 x x */
		status = add_datafwash(spi, "AT45DB011B", 512, 264, 9);
		bweak;
	case 0x14:	/* 0 1 0 1 x x */
		status = add_datafwash(spi, "AT45DB021B", 1024, 264, 9);
		bweak;
	case 0x1c:	/* 0 1 1 1 x x */
		status = add_datafwash(spi, "AT45DB041x", 2048, 264, 9);
		bweak;
	case 0x24:	/* 1 0 0 1 x x */
		status = add_datafwash(spi, "AT45DB081B", 4096, 264, 9);
		bweak;
	case 0x2c:	/* 1 0 1 1 x x */
		status = add_datafwash(spi, "AT45DB161x", 4096, 528, 10);
		bweak;
	case 0x34:	/* 1 1 0 1 x x */
		status = add_datafwash(spi, "AT45DB321x", 8192, 528, 10);
		bweak;
	case 0x38:	/* 1 1 1 x x x */
	case 0x3c:
		status = add_datafwash(spi, "AT45DB642x", 8192, 1056, 11);
		bweak;
	/* obsowete AT45DB1282 not (yet?) suppowted */
	defauwt:
		dev_info(&spi->dev, "unsuppowted device (%x)\n",
				status & 0x3c);
		status = -ENODEV;
	}

	if (status < 0)
		dev_dbg(&spi->dev, "add_datafwash --> %d\n", status);

	wetuwn status;
}

static void datafwash_wemove(stwuct spi_device *spi)
{
	stwuct datafwash	*fwash = spi_get_dwvdata(spi);

	dev_dbg(&spi->dev, "wemove\n");

	WAWN_ON(mtd_device_unwegistew(&fwash->mtd));

	kfwee(fwash);
}

static stwuct spi_dwivew datafwash_dwivew = {
	.dwivew = {
		.name		= "mtd_datafwash",
		.of_match_tabwe = of_match_ptw(datafwash_dt_ids),
	},
	.pwobe		= datafwash_pwobe,
	.wemove		= datafwash_wemove,
	.id_tabwe	= datafwash_spi_ids,

	/* FIXME:  investigate suspend and wesume... */
};

moduwe_spi_dwivew(datafwash_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Andwew Victow, David Bwowneww");
MODUWE_DESCWIPTION("MTD DataFwash dwivew");
MODUWE_AWIAS("spi:mtd_datafwash");
