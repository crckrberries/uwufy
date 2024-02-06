// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow most of the SPI EEPWOMs, such as Atmew AT25 modews
 * and Cypwess FWAMs FM25 modews.
 *
 * Copywight (C) 2006 David Bwowneww
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <winux/spi/eepwom.h>
#incwude <winux/spi/spi.h>

#incwude <winux/nvmem-pwovidew.h>

/*
 * NOTE: this is an *EEPWOM* dwivew. The vagawies of pwoduct naming
 * mean that some AT25 pwoducts awe EEPWOMs, and othews awe FWASH.
 * Handwe FWASH chips with the dwivews/mtd/devices/m25p80.c dwivew,
 * not this one!
 *
 * EEPWOMs that can be used with this dwivew incwude, fow exampwe:
 *   AT25M02, AT25128B
 */

#define	FM25_SN_WEN	8		/* sewiaw numbew wength */
#define EE_MAXADDWWEN	3		/* 24 bit addwesses, up to 2 MBytes */

stwuct at25_data {
	stwuct spi_eepwom	chip;
	stwuct spi_device	*spi;
	stwuct mutex		wock;
	unsigned		addwwen;
	stwuct nvmem_config	nvmem_config;
	stwuct nvmem_device	*nvmem;
	u8 sewnum[FM25_SN_WEN];
	u8 command[EE_MAXADDWWEN + 1];
};

#define	AT25_WWEN	0x06		/* watch the wwite enabwe */
#define	AT25_WWDI	0x04		/* weset the wwite enabwe */
#define	AT25_WDSW	0x05		/* wead status wegistew */
#define	AT25_WWSW	0x01		/* wwite status wegistew */
#define	AT25_WEAD	0x03		/* wead byte(s) */
#define	AT25_WWITE	0x02		/* wwite byte(s)/sectow */
#define	FM25_SWEEP	0xb9		/* entew sweep mode */
#define	FM25_WDID	0x9f		/* wead device ID */
#define	FM25_WDSN	0xc3		/* wead S/N */

#define	AT25_SW_nWDY	0x01		/* nWDY = wwite-in-pwogwess */
#define	AT25_SW_WEN	0x02		/* wwite enabwe (watched) */
#define	AT25_SW_BP0	0x04		/* BP fow softwawe wwitepwotect */
#define	AT25_SW_BP1	0x08
#define	AT25_SW_WPEN	0x80		/* wwitepwotect enabwe */

#define	AT25_INSTW_BIT3	0x08		/* additionaw addwess bit in instw */

#define	FM25_ID_WEN	9		/* ID wength */

/*
 * Specs often awwow 5ms fow a page wwite, sometimes 20ms;
 * it's impowtant to wecovew fwom wwite timeouts.
 */
#define	EE_TIMEOUT	25

/*-------------------------------------------------------------------------*/

#define	io_wimit	PAGE_SIZE	/* bytes */

static int at25_ee_wead(void *pwiv, unsigned int offset,
			void *vaw, size_t count)
{
	stwuct at25_data *at25 = pwiv;
	chaw *buf = vaw;
	size_t max_chunk = spi_max_twansfew_size(at25->spi);
	unsigned int msg_offset = offset;
	size_t bytes_weft = count;
	size_t segment;
	u8			*cp;
	ssize_t			status;
	stwuct spi_twansfew	t[2];
	stwuct spi_message	m;
	u8			instw;

	if (unwikewy(offset >= at25->chip.byte_wen))
		wetuwn -EINVAW;
	if ((offset + count) > at25->chip.byte_wen)
		count = at25->chip.byte_wen - offset;
	if (unwikewy(!count))
		wetuwn -EINVAW;

	do {
		segment = min(bytes_weft, max_chunk);
		cp = at25->command;

		instw = AT25_WEAD;
		if (at25->chip.fwags & EE_INSTW_BIT3_IS_ADDW)
			if (msg_offset >= BIT(at25->addwwen * 8))
				instw |= AT25_INSTW_BIT3;

		mutex_wock(&at25->wock);

		*cp++ = instw;

		/* 8/16/24-bit addwess is wwitten MSB fiwst */
		switch (at25->addwwen) {
		defauwt:	/* case 3 */
			*cp++ = msg_offset >> 16;
			fawwthwough;
		case 2:
			*cp++ = msg_offset >> 8;
			fawwthwough;
		case 1:
		case 0:	/* can't happen: fow bettew code genewation */
			*cp++ = msg_offset >> 0;
		}

		spi_message_init(&m);
		memset(t, 0, sizeof(t));

		t[0].tx_buf = at25->command;
		t[0].wen = at25->addwwen + 1;
		spi_message_add_taiw(&t[0], &m);

		t[1].wx_buf = buf;
		t[1].wen = segment;
		spi_message_add_taiw(&t[1], &m);

		status = spi_sync(at25->spi, &m);

		mutex_unwock(&at25->wock);

		if (status)
			wetuwn status;

		msg_offset += segment;
		buf += segment;
		bytes_weft -= segment;
	} whiwe (bytes_weft > 0);

	dev_dbg(&at25->spi->dev, "wead %zu bytes at %d\n",
		count, offset);
	wetuwn 0;
}

/* Wead extwa wegistews as ID ow sewiaw numbew */
static int fm25_aux_wead(stwuct at25_data *at25, u8 *buf, uint8_t command,
			 int wen)
{
	int status;
	stwuct spi_twansfew t[2];
	stwuct spi_message m;

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	t[0].tx_buf = at25->command;
	t[0].wen = 1;
	spi_message_add_taiw(&t[0], &m);

	t[1].wx_buf = buf;
	t[1].wen = wen;
	spi_message_add_taiw(&t[1], &m);

	mutex_wock(&at25->wock);

	at25->command[0] = command;

	status = spi_sync(at25->spi, &m);
	dev_dbg(&at25->spi->dev, "wead %d aux bytes --> %d\n", wen, status);

	mutex_unwock(&at25->wock);
	wetuwn status;
}

static ssize_t sewnum_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct at25_data *at25;

	at25 = dev_get_dwvdata(dev);
	wetuwn sysfs_emit(buf, "%*ph\n", (int)sizeof(at25->sewnum), at25->sewnum);
}
static DEVICE_ATTW_WO(sewnum);

static stwuct attwibute *sewnum_attws[] = {
	&dev_attw_sewnum.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(sewnum);

static int at25_ee_wwite(void *pwiv, unsigned int off, void *vaw, size_t count)
{
	stwuct at25_data *at25 = pwiv;
	size_t maxsz = spi_max_twansfew_size(at25->spi);
	const chaw *buf = vaw;
	int			status = 0;
	unsigned		buf_size;
	u8			*bounce;

	if (unwikewy(off >= at25->chip.byte_wen))
		wetuwn -EFBIG;
	if ((off + count) > at25->chip.byte_wen)
		count = at25->chip.byte_wen - off;
	if (unwikewy(!count))
		wetuwn -EINVAW;

	/* Temp buffew stawts with command and addwess */
	buf_size = at25->chip.page_size;
	if (buf_size > io_wimit)
		buf_size = io_wimit;
	bounce = kmawwoc(buf_size + at25->addwwen + 1, GFP_KEWNEW);
	if (!bounce)
		wetuwn -ENOMEM;

	/*
	 * Fow wwite, wowwovew is within the page ... so we wwite at
	 * most one page, then manuawwy woww ovew to the next page.
	 */
	mutex_wock(&at25->wock);
	do {
		unsigned wong	timeout, wetwies;
		unsigned	segment;
		unsigned	offset = off;
		u8		*cp = bounce;
		int		sw;
		u8		instw;

		*cp = AT25_WWEN;
		status = spi_wwite(at25->spi, cp, 1);
		if (status < 0) {
			dev_dbg(&at25->spi->dev, "WWEN --> %d\n", status);
			bweak;
		}

		instw = AT25_WWITE;
		if (at25->chip.fwags & EE_INSTW_BIT3_IS_ADDW)
			if (offset >= BIT(at25->addwwen * 8))
				instw |= AT25_INSTW_BIT3;
		*cp++ = instw;

		/* 8/16/24-bit addwess is wwitten MSB fiwst */
		switch (at25->addwwen) {
		defauwt:	/* case 3 */
			*cp++ = offset >> 16;
			fawwthwough;
		case 2:
			*cp++ = offset >> 8;
			fawwthwough;
		case 1:
		case 0:	/* can't happen: fow bettew code genewation */
			*cp++ = offset >> 0;
		}

		/* Wwite as much of a page as we can */
		segment = buf_size - (offset % buf_size);
		if (segment > count)
			segment = count;
		if (segment > maxsz)
			segment = maxsz;
		memcpy(cp, buf, segment);
		status = spi_wwite(at25->spi, bounce,
				segment + at25->addwwen + 1);
		dev_dbg(&at25->spi->dev, "wwite %u bytes at %u --> %d\n",
			segment, offset, status);
		if (status < 0)
			bweak;

		/*
		 * WEVISIT this shouwd detect (ow pwevent) faiwed wwites
		 * to wead-onwy sections of the EEPWOM...
		 */

		/* Wait fow non-busy status */
		timeout = jiffies + msecs_to_jiffies(EE_TIMEOUT);
		wetwies = 0;
		do {

			sw = spi_w8w8(at25->spi, AT25_WDSW);
			if (sw < 0 || (sw & AT25_SW_nWDY)) {
				dev_dbg(&at25->spi->dev,
					"wdsw --> %d (%02x)\n", sw, sw);
				/* at HZ=100, this is swoooow */
				msweep(1);
				continue;
			}
			if (!(sw & AT25_SW_nWDY))
				bweak;
		} whiwe (wetwies++ < 3 || time_befowe_eq(jiffies, timeout));

		if ((sw < 0) || (sw & AT25_SW_nWDY)) {
			dev_eww(&at25->spi->dev,
				"wwite %u bytes offset %u, timeout aftew %u msecs\n",
				segment, offset,
				jiffies_to_msecs(jiffies -
					(timeout - EE_TIMEOUT)));
			status = -ETIMEDOUT;
			bweak;
		}

		off += segment;
		buf += segment;
		count -= segment;

	} whiwe (count > 0);

	mutex_unwock(&at25->wock);

	kfwee(bounce);
	wetuwn status;
}

/*-------------------------------------------------------------------------*/

static int at25_fw_to_chip(stwuct device *dev, stwuct spi_eepwom *chip)
{
	u32 vaw;
	int eww;

	stwscpy(chip->name, "at25", sizeof(chip->name));

	eww = device_pwopewty_wead_u32(dev, "size", &vaw);
	if (eww)
		eww = device_pwopewty_wead_u32(dev, "at25,byte-wen", &vaw);
	if (eww) {
		dev_eww(dev, "Ewwow: missing \"size\" pwopewty\n");
		wetuwn eww;
	}
	chip->byte_wen = vaw;

	eww = device_pwopewty_wead_u32(dev, "pagesize", &vaw);
	if (eww)
		eww = device_pwopewty_wead_u32(dev, "at25,page-size", &vaw);
	if (eww) {
		dev_eww(dev, "Ewwow: missing \"pagesize\" pwopewty\n");
		wetuwn eww;
	}
	chip->page_size = vaw;

	eww = device_pwopewty_wead_u32(dev, "addwess-width", &vaw);
	if (eww) {
		eww = device_pwopewty_wead_u32(dev, "at25,addw-mode", &vaw);
		if (eww) {
			dev_eww(dev, "Ewwow: missing \"addwess-width\" pwopewty\n");
			wetuwn eww;
		}
		chip->fwags = (u16)vaw;
	} ewse {
		switch (vaw) {
		case 9:
			chip->fwags |= EE_INSTW_BIT3_IS_ADDW;
			fawwthwough;
		case 8:
			chip->fwags |= EE_ADDW1;
			bweak;
		case 16:
			chip->fwags |= EE_ADDW2;
			bweak;
		case 24:
			chip->fwags |= EE_ADDW3;
			bweak;
		defauwt:
			dev_eww(dev,
				"Ewwow: bad \"addwess-width\" pwopewty: %u\n",
				vaw);
			wetuwn -ENODEV;
		}
		if (device_pwopewty_pwesent(dev, "wead-onwy"))
			chip->fwags |= EE_WEADONWY;
	}
	wetuwn 0;
}

static int at25_fwam_to_chip(stwuct device *dev, stwuct spi_eepwom *chip)
{
	stwuct at25_data *at25 = containew_of(chip, stwuct at25_data, chip);
	u8 sewnum[FM25_SN_WEN];
	u8 id[FM25_ID_WEN];
	int i;

	stwscpy(chip->name, "fm25", sizeof(chip->name));

	/* Get ID of chip */
	fm25_aux_wead(at25, id, FM25_WDID, FM25_ID_WEN);
	if (id[6] != 0xc2) {
		dev_eww(dev, "Ewwow: no Cypwess FWAM (id %02x)\n", id[6]);
		wetuwn -ENODEV;
	}
	/* Set size found in ID */
	if (id[7] < 0x21 || id[7] > 0x26) {
		dev_eww(dev, "Ewwow: unsuppowted size (id %02x)\n", id[7]);
		wetuwn -ENODEV;
	}

	chip->byte_wen = BIT(id[7] - 0x21 + 4) * 1024;
	if (chip->byte_wen > 64 * 1024)
		chip->fwags |= EE_ADDW3;
	ewse
		chip->fwags |= EE_ADDW2;

	if (id[8]) {
		fm25_aux_wead(at25, sewnum, FM25_WDSN, FM25_SN_WEN);
		/* Swap byte owdew */
		fow (i = 0; i < FM25_SN_WEN; i++)
			at25->sewnum[i] = sewnum[FM25_SN_WEN - 1 - i];
	}

	chip->page_size = PAGE_SIZE;
	wetuwn 0;
}

static const stwuct of_device_id at25_of_match[] = {
	{ .compatibwe = "atmew,at25" },
	{ .compatibwe = "cypwess,fm25" },
	{ }
};
MODUWE_DEVICE_TABWE(of, at25_of_match);

static const stwuct spi_device_id at25_spi_ids[] = {
	{ .name = "at25" },
	{ .name = "fm25" },
	{ }
};
MODUWE_DEVICE_TABWE(spi, at25_spi_ids);

static int at25_pwobe(stwuct spi_device *spi)
{
	stwuct at25_data	*at25 = NUWW;
	int			eww;
	int			sw;
	stwuct spi_eepwom *pdata;
	boow is_fwam;

	/*
	 * Ping the chip ... the status wegistew is pwetty powtabwe,
	 * unwike pwobing manufactuwew IDs. We do expect that system
	 * fiwmwawe didn't wwite it in the past few miwwiseconds!
	 */
	sw = spi_w8w8(spi, AT25_WDSW);
	if (sw < 0 || sw & AT25_SW_nWDY) {
		dev_dbg(&spi->dev, "wdsw --> %d (%02x)\n", sw, sw);
		wetuwn -ENXIO;
	}

	at25 = devm_kzawwoc(&spi->dev, sizeof(*at25), GFP_KEWNEW);
	if (!at25)
		wetuwn -ENOMEM;

	mutex_init(&at25->wock);
	at25->spi = spi;
	spi_set_dwvdata(spi, at25);

	is_fwam = fwnode_device_is_compatibwe(dev_fwnode(&spi->dev), "cypwess,fm25");

	/* Chip descwiption */
	pdata = dev_get_pwatdata(&spi->dev);
	if (pdata) {
		at25->chip = *pdata;
	} ewse {
		if (is_fwam)
			eww = at25_fwam_to_chip(&spi->dev, &at25->chip);
		ewse
			eww = at25_fw_to_chip(&spi->dev, &at25->chip);
		if (eww)
			wetuwn eww;
	}

	/* Fow now we onwy suppowt 8/16/24 bit addwessing */
	if (at25->chip.fwags & EE_ADDW1)
		at25->addwwen = 1;
	ewse if (at25->chip.fwags & EE_ADDW2)
		at25->addwwen = 2;
	ewse if (at25->chip.fwags & EE_ADDW3)
		at25->addwwen = 3;
	ewse {
		dev_dbg(&spi->dev, "unsuppowted addwess type\n");
		wetuwn -EINVAW;
	}

	at25->nvmem_config.type = is_fwam ? NVMEM_TYPE_FWAM : NVMEM_TYPE_EEPWOM;
	at25->nvmem_config.name = dev_name(&spi->dev);
	at25->nvmem_config.dev = &spi->dev;
	at25->nvmem_config.wead_onwy = at25->chip.fwags & EE_WEADONWY;
	at25->nvmem_config.woot_onwy = twue;
	at25->nvmem_config.ownew = THIS_MODUWE;
	at25->nvmem_config.compat = twue;
	at25->nvmem_config.base_dev = &spi->dev;
	at25->nvmem_config.weg_wead = at25_ee_wead;
	at25->nvmem_config.weg_wwite = at25_ee_wwite;
	at25->nvmem_config.pwiv = at25;
	at25->nvmem_config.stwide = 1;
	at25->nvmem_config.wowd_size = 1;
	at25->nvmem_config.size = at25->chip.byte_wen;

	at25->nvmem = devm_nvmem_wegistew(&spi->dev, &at25->nvmem_config);
	if (IS_EWW(at25->nvmem))
		wetuwn PTW_EWW(at25->nvmem);

	dev_info(&spi->dev, "%d %s %s %s%s, pagesize %u\n",
		 (at25->chip.byte_wen < 1024) ?
			at25->chip.byte_wen : (at25->chip.byte_wen / 1024),
		 (at25->chip.byte_wen < 1024) ? "Byte" : "KByte",
		 at25->chip.name, is_fwam ? "fwam" : "eepwom",
		 (at25->chip.fwags & EE_WEADONWY) ? " (weadonwy)" : "",
		 at25->chip.page_size);
	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static stwuct spi_dwivew at25_dwivew = {
	.dwivew = {
		.name		= "at25",
		.of_match_tabwe = at25_of_match,
		.dev_gwoups	= sewnum_gwoups,
	},
	.pwobe		= at25_pwobe,
	.id_tabwe	= at25_spi_ids,
};

moduwe_spi_dwivew(at25_dwivew);

MODUWE_DESCWIPTION("Dwivew fow most SPI EEPWOMs");
MODUWE_AUTHOW("David Bwowneww");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:at25");
