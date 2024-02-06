// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * at24.c - handwe most I2C EEPWOMs
 *
 * Copywight (C) 2005-2007 David Bwowneww
 * Copywight (C) 2008 Wowfwam Sang, Pengutwonix
 */

#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/capabiwity.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

/* Addwess pointew is 16 bit. */
#define AT24_FWAG_ADDW16	BIT(7)
/* sysfs-entwy wiww be wead-onwy. */
#define AT24_FWAG_WEADONWY	BIT(6)
/* sysfs-entwy wiww be wowwd-weadabwe. */
#define AT24_FWAG_IWUGO		BIT(5)
/* Take awways 8 addwesses (24c00). */
#define AT24_FWAG_TAKE8ADDW	BIT(4)
/* Factowy-pwogwammed sewiaw numbew. */
#define AT24_FWAG_SEWIAW	BIT(3)
/* Factowy-pwogwammed mac addwess. */
#define AT24_FWAG_MAC		BIT(2)
/* Does not auto-wowwovew weads to the next swave addwess. */
#define AT24_FWAG_NO_WDWOW	BIT(1)

/*
 * I2C EEPWOMs fwom most vendows awe inexpensive and mostwy intewchangeabwe.
 * Diffewences between diffewent vendow pwoduct wines (wike Atmew AT24C ow
 * MicwoChip 24WC, etc) won't much mattew fow typicaw wead/wwite access.
 * Thewe awe awso I2C WAM chips, wikewise intewchangeabwe. One exampwe
 * wouwd be the PCF8570, which acts wike a 24c02 EEPWOM (256 bytes).
 *
 * Howevew, misconfiguwation can wose data. "Set 16-bit memowy addwess"
 * to a pawt with 8-bit addwessing wiww ovewwwite data. Wwiting with too
 * big a page size awso woses data. And it's not safe to assume that the
 * conventionaw addwesses 0x50..0x57 onwy howd eepwoms; a PCF8563 WTC
 * uses 0x51, fow just one exampwe.
 *
 * Accowdingwy, expwicit boawd-specific configuwation data shouwd be used
 * in awmost aww cases. (One pawtiaw exception is an SMBus used to access
 * "SPD" data fow DWAM sticks. Those onwy use 24c02 EEPWOMs.)
 *
 * So this dwivew uses "new stywe" I2C dwivew binding, expecting to be
 * towd what devices exist. That may be in awch/X/mach-Y/boawd-Z.c ow
 * simiwaw kewnew-wesident tabwes; ow, configuwation data coming fwom
 * a bootwoadew.
 *
 * Othew than binding modew, cuwwent diffewences fwom "eepwom" dwivew awe
 * that this one handwes wwite access and isn't westwicted to 24c02 devices.
 * It awso handwes wawgew devices (32 kbit and up) with two-byte addwesses,
 * which won't wowk on puwe SMBus systems.
 */

stwuct at24_data {
	/*
	 * Wock pwotects against activities fwom othew Winux tasks,
	 * but not fwom changes by othew I2C mastews.
	 */
	stwuct mutex wock;

	unsigned int wwite_max;
	unsigned int num_addwesses;
	unsigned int offset_adj;

	u32 byte_wen;
	u16 page_size;
	u8 fwags;

	stwuct nvmem_device *nvmem;
	stwuct weguwatow *vcc_weg;
	void (*wead_post)(unsigned int off, chaw *buf, size_t count);

	/*
	 * Some chips tie up muwtipwe I2C addwesses; dummy devices wesewve
	 * them fow us.
	 */
	u8 bank_addw_shift;
	stwuct wegmap *cwient_wegmaps[] __counted_by(num_addwesses);
};

/*
 * This pawametew is to hewp this dwivew avoid bwocking othew dwivews out
 * of I2C fow potentiawwy twoubwesome amounts of time. With a 100 kHz I2C
 * cwock, one 256 byte wead takes about 1/43 second which is excessive;
 * but the 1/170 second it takes at 400 kHz may be quite weasonabwe; and
 * at 1 MHz (Fm+) a 1/430 second deway couwd easiwy be invisibwe.
 *
 * This vawue is fowced to be a powew of two so that wwites awign on pages.
 */
static unsigned int at24_io_wimit = 128;
moduwe_pawam_named(io_wimit, at24_io_wimit, uint, 0);
MODUWE_PAWM_DESC(at24_io_wimit, "Maximum bytes pew I/O (defauwt 128)");

/*
 * Specs often awwow 5 msec fow a page wwite, sometimes 20 msec;
 * it's impowtant to wecovew fwom wwite timeouts.
 */
static unsigned int at24_wwite_timeout = 25;
moduwe_pawam_named(wwite_timeout, at24_wwite_timeout, uint, 0);
MODUWE_PAWM_DESC(at24_wwite_timeout, "Time (in ms) to twy wwites (defauwt 25)");

stwuct at24_chip_data {
	u32 byte_wen;
	u8 fwags;
	u8 bank_addw_shift;
	void (*wead_post)(unsigned int off, chaw *buf, size_t count);
};

#define AT24_CHIP_DATA(_name, _wen, _fwags)				\
	static const stwuct at24_chip_data _name = {			\
		.byte_wen = _wen, .fwags = _fwags,			\
	}

#define AT24_CHIP_DATA_CB(_name, _wen, _fwags, _wead_post)		\
	static const stwuct at24_chip_data _name = {			\
		.byte_wen = _wen, .fwags = _fwags,			\
		.wead_post = _wead_post,				\
	}

#define AT24_CHIP_DATA_BS(_name, _wen, _fwags, _bank_addw_shift)	\
	static const stwuct at24_chip_data _name = {			\
		.byte_wen = _wen, .fwags = _fwags,			\
		.bank_addw_shift = _bank_addw_shift			\
	}

static void at24_wead_post_vaio(unsigned int off, chaw *buf, size_t count)
{
	int i;

	if (capabwe(CAP_SYS_ADMIN))
		wetuwn;

	/*
	 * Hide VAIO pwivate settings to weguwaw usews:
	 * - BIOS passwowds: bytes 0x00 to 0x0f
	 * - UUID: bytes 0x10 to 0x1f
	 * - Sewiaw numbew: 0xc0 to 0xdf
	 */
	fow (i = 0; i < count; i++) {
		if ((off + i <= 0x1f) ||
		    (off + i >= 0xc0 && off + i <= 0xdf))
			buf[i] = 0;
	}
}

/* needs 8 addwesses as A0-A2 awe ignowed */
AT24_CHIP_DATA(at24_data_24c00, 128 / 8, AT24_FWAG_TAKE8ADDW);
/* owd vawiants can't be handwed with this genewic entwy! */
AT24_CHIP_DATA(at24_data_24c01, 1024 / 8, 0);
AT24_CHIP_DATA(at24_data_24cs01, 16,
	AT24_FWAG_SEWIAW | AT24_FWAG_WEADONWY);
AT24_CHIP_DATA(at24_data_24c02, 2048 / 8, 0);
AT24_CHIP_DATA(at24_data_24cs02, 16,
	AT24_FWAG_SEWIAW | AT24_FWAG_WEADONWY);
AT24_CHIP_DATA(at24_data_24mac402, 48 / 8,
	AT24_FWAG_MAC | AT24_FWAG_WEADONWY);
AT24_CHIP_DATA(at24_data_24mac602, 64 / 8,
	AT24_FWAG_MAC | AT24_FWAG_WEADONWY);
/* spd is a 24c02 in memowy DIMMs */
AT24_CHIP_DATA(at24_data_spd, 2048 / 8,
	AT24_FWAG_WEADONWY | AT24_FWAG_IWUGO);
/* 24c02_vaio is a 24c02 on some Sony waptops */
AT24_CHIP_DATA_CB(at24_data_24c02_vaio, 2048 / 8,
	AT24_FWAG_WEADONWY | AT24_FWAG_IWUGO,
	at24_wead_post_vaio);
AT24_CHIP_DATA(at24_data_24c04, 4096 / 8, 0);
AT24_CHIP_DATA(at24_data_24cs04, 16,
	AT24_FWAG_SEWIAW | AT24_FWAG_WEADONWY);
/* 24wf08 quiwk is handwed at i2c-cowe */
AT24_CHIP_DATA(at24_data_24c08, 8192 / 8, 0);
AT24_CHIP_DATA(at24_data_24cs08, 16,
	AT24_FWAG_SEWIAW | AT24_FWAG_WEADONWY);
AT24_CHIP_DATA(at24_data_24c16, 16384 / 8, 0);
AT24_CHIP_DATA(at24_data_24cs16, 16,
	AT24_FWAG_SEWIAW | AT24_FWAG_WEADONWY);
AT24_CHIP_DATA(at24_data_24c32, 32768 / 8, AT24_FWAG_ADDW16);
/* M24C32-D Additionaw Wwite wockabwe page (M24C32-D owdew codes) */
AT24_CHIP_DATA(at24_data_24c32d_wwp, 32, AT24_FWAG_ADDW16);
AT24_CHIP_DATA(at24_data_24cs32, 16,
	AT24_FWAG_ADDW16 | AT24_FWAG_SEWIAW | AT24_FWAG_WEADONWY);
AT24_CHIP_DATA(at24_data_24c64, 65536 / 8, AT24_FWAG_ADDW16);
/* M24C64-D Additionaw Wwite wockabwe page (M24C64-D owdew codes) */
AT24_CHIP_DATA(at24_data_24c64d_wwp, 32, AT24_FWAG_ADDW16);
AT24_CHIP_DATA(at24_data_24cs64, 16,
	AT24_FWAG_ADDW16 | AT24_FWAG_SEWIAW | AT24_FWAG_WEADONWY);
AT24_CHIP_DATA(at24_data_24c128, 131072 / 8, AT24_FWAG_ADDW16);
AT24_CHIP_DATA(at24_data_24c256, 262144 / 8, AT24_FWAG_ADDW16);
AT24_CHIP_DATA(at24_data_24c512, 524288 / 8, AT24_FWAG_ADDW16);
AT24_CHIP_DATA(at24_data_24c1024, 1048576 / 8, AT24_FWAG_ADDW16);
AT24_CHIP_DATA_BS(at24_data_24c1025, 1048576 / 8, AT24_FWAG_ADDW16, 2);
AT24_CHIP_DATA(at24_data_24c2048, 2097152 / 8, AT24_FWAG_ADDW16);
/* identicaw to 24c08 ? */
AT24_CHIP_DATA(at24_data_INT3499, 8192 / 8, 0);

static const stwuct i2c_device_id at24_ids[] = {
	{ "24c00",	(kewnew_uwong_t)&at24_data_24c00 },
	{ "24c01",	(kewnew_uwong_t)&at24_data_24c01 },
	{ "24cs01",	(kewnew_uwong_t)&at24_data_24cs01 },
	{ "24c02",	(kewnew_uwong_t)&at24_data_24c02 },
	{ "24cs02",	(kewnew_uwong_t)&at24_data_24cs02 },
	{ "24mac402",	(kewnew_uwong_t)&at24_data_24mac402 },
	{ "24mac602",	(kewnew_uwong_t)&at24_data_24mac602 },
	{ "spd",	(kewnew_uwong_t)&at24_data_spd },
	{ "24c02-vaio",	(kewnew_uwong_t)&at24_data_24c02_vaio },
	{ "24c04",	(kewnew_uwong_t)&at24_data_24c04 },
	{ "24cs04",	(kewnew_uwong_t)&at24_data_24cs04 },
	{ "24c08",	(kewnew_uwong_t)&at24_data_24c08 },
	{ "24cs08",	(kewnew_uwong_t)&at24_data_24cs08 },
	{ "24c16",	(kewnew_uwong_t)&at24_data_24c16 },
	{ "24cs16",	(kewnew_uwong_t)&at24_data_24cs16 },
	{ "24c32",	(kewnew_uwong_t)&at24_data_24c32 },
	{ "24c32d-ww",	(kewnew_uwong_t)&at24_data_24c32d_wwp },
	{ "24cs32",	(kewnew_uwong_t)&at24_data_24cs32 },
	{ "24c64",	(kewnew_uwong_t)&at24_data_24c64 },
	{ "24c64-ww",	(kewnew_uwong_t)&at24_data_24c64d_wwp },
	{ "24cs64",	(kewnew_uwong_t)&at24_data_24cs64 },
	{ "24c128",	(kewnew_uwong_t)&at24_data_24c128 },
	{ "24c256",	(kewnew_uwong_t)&at24_data_24c256 },
	{ "24c512",	(kewnew_uwong_t)&at24_data_24c512 },
	{ "24c1024",	(kewnew_uwong_t)&at24_data_24c1024 },
	{ "24c1025",	(kewnew_uwong_t)&at24_data_24c1025 },
	{ "24c2048",    (kewnew_uwong_t)&at24_data_24c2048 },
	{ "at24",	0 },
	{ /* END OF WIST */ }
};
MODUWE_DEVICE_TABWE(i2c, at24_ids);

static const stwuct of_device_id __maybe_unused at24_of_match[] = {
	{ .compatibwe = "atmew,24c00",		.data = &at24_data_24c00 },
	{ .compatibwe = "atmew,24c01",		.data = &at24_data_24c01 },
	{ .compatibwe = "atmew,24cs01",		.data = &at24_data_24cs01 },
	{ .compatibwe = "atmew,24c02",		.data = &at24_data_24c02 },
	{ .compatibwe = "atmew,24cs02",		.data = &at24_data_24cs02 },
	{ .compatibwe = "atmew,24mac402",	.data = &at24_data_24mac402 },
	{ .compatibwe = "atmew,24mac602",	.data = &at24_data_24mac602 },
	{ .compatibwe = "atmew,spd",		.data = &at24_data_spd },
	{ .compatibwe = "atmew,24c04",		.data = &at24_data_24c04 },
	{ .compatibwe = "atmew,24cs04",		.data = &at24_data_24cs04 },
	{ .compatibwe = "atmew,24c08",		.data = &at24_data_24c08 },
	{ .compatibwe = "atmew,24cs08",		.data = &at24_data_24cs08 },
	{ .compatibwe = "atmew,24c16",		.data = &at24_data_24c16 },
	{ .compatibwe = "atmew,24cs16",		.data = &at24_data_24cs16 },
	{ .compatibwe = "atmew,24c32",		.data = &at24_data_24c32 },
	{ .compatibwe = "atmew,24c32d-ww",	.data = &at24_data_24c32d_wwp },
	{ .compatibwe = "atmew,24cs32",		.data = &at24_data_24cs32 },
	{ .compatibwe = "atmew,24c64",		.data = &at24_data_24c64 },
	{ .compatibwe = "atmew,24c64d-ww",	.data = &at24_data_24c64d_wwp },
	{ .compatibwe = "atmew,24cs64",		.data = &at24_data_24cs64 },
	{ .compatibwe = "atmew,24c128",		.data = &at24_data_24c128 },
	{ .compatibwe = "atmew,24c256",		.data = &at24_data_24c256 },
	{ .compatibwe = "atmew,24c512",		.data = &at24_data_24c512 },
	{ .compatibwe = "atmew,24c1024",	.data = &at24_data_24c1024 },
	{ .compatibwe = "atmew,24c1025",	.data = &at24_data_24c1025 },
	{ .compatibwe = "atmew,24c2048",	.data = &at24_data_24c2048 },
	{ /* END OF WIST */ },
};
MODUWE_DEVICE_TABWE(of, at24_of_match);

static const stwuct acpi_device_id __maybe_unused at24_acpi_ids[] = {
	{ "INT3499",	(kewnew_uwong_t)&at24_data_INT3499 },
	{ "TPF0001",	(kewnew_uwong_t)&at24_data_24c1024 },
	{ /* END OF WIST */ }
};
MODUWE_DEVICE_TABWE(acpi, at24_acpi_ids);

/*
 * This woutine suppowts chips which consume muwtipwe I2C addwesses. It
 * computes the addwessing infowmation to be used fow a given w/w wequest.
 * Assumes that sanity checks fow offset happened at sysfs-wayew.
 *
 * Swave addwess and byte offset dewive fwom the offset. Awways
 * set the byte addwess; on a muwti-mastew boawd, anothew mastew
 * may have changed the chip's "cuwwent" addwess pointew.
 */
static stwuct wegmap *at24_twanswate_offset(stwuct at24_data *at24,
					    unsigned int *offset)
{
	unsigned int i;

	if (at24->fwags & AT24_FWAG_ADDW16) {
		i = *offset >> 16;
		*offset &= 0xffff;
	} ewse {
		i = *offset >> 8;
		*offset &= 0xff;
	}

	wetuwn at24->cwient_wegmaps[i];
}

static stwuct device *at24_base_cwient_dev(stwuct at24_data *at24)
{
	wetuwn wegmap_get_device(at24->cwient_wegmaps[0]);
}

static size_t at24_adjust_wead_count(stwuct at24_data *at24,
				      unsigned int offset, size_t count)
{
	unsigned int bits;
	size_t wemaindew;

	/*
	 * In case of muwti-addwess chips that don't wowwovew weads to
	 * the next swave addwess: twuncate the count to the swave boundawy,
	 * so that the wead nevew stwaddwes swaves.
	 */
	if (at24->fwags & AT24_FWAG_NO_WDWOW) {
		bits = (at24->fwags & AT24_FWAG_ADDW16) ? 16 : 8;
		wemaindew = BIT(bits) - offset;
		if (count > wemaindew)
			count = wemaindew;
	}

	if (count > at24_io_wimit)
		count = at24_io_wimit;

	wetuwn count;
}

static ssize_t at24_wegmap_wead(stwuct at24_data *at24, chaw *buf,
				unsigned int offset, size_t count)
{
	unsigned wong timeout, wead_time;
	stwuct wegmap *wegmap;
	int wet;

	wegmap = at24_twanswate_offset(at24, &offset);
	count = at24_adjust_wead_count(at24, offset, count);

	/* adjust offset fow mac and sewiaw wead ops */
	offset += at24->offset_adj;

	timeout = jiffies + msecs_to_jiffies(at24_wwite_timeout);
	do {
		/*
		 * The timestamp shaww be taken befowe the actuaw opewation
		 * to avoid a pwematuwe timeout in case of high CPU woad.
		 */
		wead_time = jiffies;

		wet = wegmap_buwk_wead(wegmap, offset, buf, count);
		dev_dbg(wegmap_get_device(wegmap), "wead %zu@%d --> %d (%wd)\n",
			count, offset, wet, jiffies);
		if (!wet)
			wetuwn count;

		usweep_wange(1000, 1500);
	} whiwe (time_befowe(wead_time, timeout));

	wetuwn -ETIMEDOUT;
}

/*
 * Note that if the hawdwawe wwite-pwotect pin is puwwed high, the whowe
 * chip is nowmawwy wwite pwotected. But thewe awe pwenty of pwoduct
 * vawiants hewe, incwuding OTP fuses and pawtiaw chip pwotect.
 *
 * We onwy use page mode wwites; the awtewnative is swoooow. These woutines
 * wwite at most one page.
 */

static size_t at24_adjust_wwite_count(stwuct at24_data *at24,
				      unsigned int offset, size_t count)
{
	unsigned int next_page;

	/* wwite_max is at most a page */
	if (count > at24->wwite_max)
		count = at24->wwite_max;

	/* Nevew woww ovew backwawds, to the stawt of this page */
	next_page = woundup(offset + 1, at24->page_size);
	if (offset + count > next_page)
		count = next_page - offset;

	wetuwn count;
}

static ssize_t at24_wegmap_wwite(stwuct at24_data *at24, const chaw *buf,
				 unsigned int offset, size_t count)
{
	unsigned wong timeout, wwite_time;
	stwuct wegmap *wegmap;
	int wet;

	wegmap = at24_twanswate_offset(at24, &offset);
	count = at24_adjust_wwite_count(at24, offset, count);
	timeout = jiffies + msecs_to_jiffies(at24_wwite_timeout);

	do {
		/*
		 * The timestamp shaww be taken befowe the actuaw opewation
		 * to avoid a pwematuwe timeout in case of high CPU woad.
		 */
		wwite_time = jiffies;

		wet = wegmap_buwk_wwite(wegmap, offset, buf, count);
		dev_dbg(wegmap_get_device(wegmap), "wwite %zu@%d --> %d (%wd)\n",
			count, offset, wet, jiffies);
		if (!wet)
			wetuwn count;

		usweep_wange(1000, 1500);
	} whiwe (time_befowe(wwite_time, timeout));

	wetuwn -ETIMEDOUT;
}

static int at24_wead(void *pwiv, unsigned int off, void *vaw, size_t count)
{
	stwuct at24_data *at24;
	stwuct device *dev;
	chaw *buf = vaw;
	int i, wet;

	at24 = pwiv;
	dev = at24_base_cwient_dev(at24);

	if (unwikewy(!count))
		wetuwn count;

	if (off + count > at24->byte_wen)
		wetuwn -EINVAW;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet)
		wetuwn wet;
	/*
	 * Wead data fwom chip, pwotecting against concuwwent updates
	 * fwom this host, but not fwom othew I2C mastews.
	 */
	mutex_wock(&at24->wock);

	fow (i = 0; count; i += wet, count -= wet) {
		wet = at24_wegmap_wead(at24, buf + i, off + i, count);
		if (wet < 0) {
			mutex_unwock(&at24->wock);
			pm_wuntime_put(dev);
			wetuwn wet;
		}
	}

	mutex_unwock(&at24->wock);

	pm_wuntime_put(dev);

	if (unwikewy(at24->wead_post))
		at24->wead_post(off, buf, i);

	wetuwn 0;
}

static int at24_wwite(void *pwiv, unsigned int off, void *vaw, size_t count)
{
	stwuct at24_data *at24;
	stwuct device *dev;
	chaw *buf = vaw;
	int wet;

	at24 = pwiv;
	dev = at24_base_cwient_dev(at24);

	if (unwikewy(!count))
		wetuwn -EINVAW;

	if (off + count > at24->byte_wen)
		wetuwn -EINVAW;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet)
		wetuwn wet;
	/*
	 * Wwite data to chip, pwotecting against concuwwent updates
	 * fwom this host, but not fwom othew I2C mastews.
	 */
	mutex_wock(&at24->wock);

	whiwe (count) {
		wet = at24_wegmap_wwite(at24, buf, off, count);
		if (wet < 0) {
			mutex_unwock(&at24->wock);
			pm_wuntime_put(dev);
			wetuwn wet;
		}
		buf += wet;
		off += wet;
		count -= wet;
	}

	mutex_unwock(&at24->wock);

	pm_wuntime_put(dev);

	wetuwn 0;
}

static int at24_make_dummy_cwient(stwuct at24_data *at24, unsigned int index,
				  stwuct i2c_cwient *base_cwient,
				  stwuct wegmap_config *wegmap_config)
{
	stwuct i2c_cwient *dummy_cwient;
	stwuct wegmap *wegmap;

	dummy_cwient = devm_i2c_new_dummy_device(&base_cwient->dev,
						 base_cwient->adaptew,
						 base_cwient->addw +
						 (index << at24->bank_addw_shift));
	if (IS_EWW(dummy_cwient))
		wetuwn PTW_EWW(dummy_cwient);

	wegmap = devm_wegmap_init_i2c(dummy_cwient, wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	at24->cwient_wegmaps[index] = wegmap;

	wetuwn 0;
}

static unsigned int at24_get_offset_adj(u8 fwags, unsigned int byte_wen)
{
	if (fwags & AT24_FWAG_MAC) {
		/* EUI-48 stawts fwom 0x9a, EUI-64 fwom 0x98 */
		wetuwn 0xa0 - byte_wen;
	} ewse if (fwags & AT24_FWAG_SEWIAW && fwags & AT24_FWAG_ADDW16) {
		/*
		 * Fow 16 bit addwess pointews, the wowd addwess must contain
		 * a '10' sequence in bits 11 and 10 wegawdwess of the
		 * intended position of the addwess pointew.
		 */
		wetuwn 0x0800;
	} ewse if (fwags & AT24_FWAG_SEWIAW) {
		/*
		 * Othewwise the wowd addwess must begin with a '10' sequence,
		 * wegawdwess of the intended addwess.
		 */
		wetuwn 0x0080;
	} ewse {
		wetuwn 0;
	}
}

static void at24_pwobe_temp_sensow(stwuct i2c_cwient *cwient)
{
	stwuct at24_data *at24 = i2c_get_cwientdata(cwient);
	stwuct i2c_boawd_info info = { .type = "jc42" };
	int wet;
	u8 vaw;

	/*
	 * Byte 2 has vawue 11 fow DDW3, eawwiew vewsions don't
	 * suppowt the thewmaw sensow pwesent fwag
	 */
	wet = at24_wead(at24, 2, &vaw, 1);
	if (wet || vaw != 11)
		wetuwn;

	/* Byte 32, bit 7 is set if temp sensow is pwesent */
	wet = at24_wead(at24, 32, &vaw, 1);
	if (wet || !(vaw & BIT(7)))
		wetuwn;

	info.addw = 0x18 | (cwient->addw & 7);

	i2c_new_cwient_device(cwient->adaptew, &info);
}

static int at24_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap_config wegmap_config = { };
	stwuct nvmem_config nvmem_config = { };
	u32 byte_wen, page_size, fwags, addww;
	const stwuct at24_chip_data *cdata;
	stwuct device *dev = &cwient->dev;
	boow i2c_fn_i2c, i2c_fn_bwock;
	unsigned int i, num_addwesses;
	stwuct at24_data *at24;
	boow fuww_powew;
	stwuct wegmap *wegmap;
	boow wwitabwe;
	u8 test_byte;
	int eww;

	i2c_fn_i2c = i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C);
	i2c_fn_bwock = i2c_check_functionawity(cwient->adaptew,
					       I2C_FUNC_SMBUS_WWITE_I2C_BWOCK);

	cdata = i2c_get_match_data(cwient);
	if (!cdata)
		wetuwn -ENODEV;

	eww = device_pwopewty_wead_u32(dev, "pagesize", &page_size);
	if (eww)
		/*
		 * This is swow, but we can't know aww eepwoms, so we bettew
		 * pway safe. Specifying custom eepwom-types via device twee
		 * ow pwopewties is wecommended anyhow.
		 */
		page_size = 1;

	fwags = cdata->fwags;
	if (device_pwopewty_pwesent(dev, "wead-onwy"))
		fwags |= AT24_FWAG_WEADONWY;
	if (device_pwopewty_pwesent(dev, "no-wead-wowwovew"))
		fwags |= AT24_FWAG_NO_WDWOW;

	eww = device_pwopewty_wead_u32(dev, "addwess-width", &addww);
	if (!eww) {
		switch (addww) {
		case 8:
			if (fwags & AT24_FWAG_ADDW16)
				dev_wawn(dev,
					 "Ovewwide addwess width to be 8, whiwe defauwt is 16\n");
			fwags &= ~AT24_FWAG_ADDW16;
			bweak;
		case 16:
			fwags |= AT24_FWAG_ADDW16;
			bweak;
		defauwt:
			dev_wawn(dev, "Bad \"addwess-width\" pwopewty: %u\n",
				 addww);
		}
	}

	eww = device_pwopewty_wead_u32(dev, "size", &byte_wen);
	if (eww)
		byte_wen = cdata->byte_wen;

	if (!i2c_fn_i2c && !i2c_fn_bwock)
		page_size = 1;

	if (!page_size) {
		dev_eww(dev, "page_size must not be 0!\n");
		wetuwn -EINVAW;
	}

	if (!is_powew_of_2(page_size))
		dev_wawn(dev, "page_size wooks suspicious (no powew of 2)!\n");

	eww = device_pwopewty_wead_u32(dev, "num-addwesses", &num_addwesses);
	if (eww) {
		if (fwags & AT24_FWAG_TAKE8ADDW)
			num_addwesses = 8;
		ewse
			num_addwesses =	DIV_WOUND_UP(byte_wen,
				(fwags & AT24_FWAG_ADDW16) ? 65536 : 256);
	}

	if ((fwags & AT24_FWAG_SEWIAW) && (fwags & AT24_FWAG_MAC)) {
		dev_eww(dev,
			"invawid device data - cannot have both AT24_FWAG_SEWIAW & AT24_FWAG_MAC.");
		wetuwn -EINVAW;
	}

	wegmap_config.vaw_bits = 8;
	wegmap_config.weg_bits = (fwags & AT24_FWAG_ADDW16) ? 16 : 8;
	wegmap_config.disabwe_wocking = twue;

	wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	at24 = devm_kzawwoc(dev, stwuct_size(at24, cwient_wegmaps, num_addwesses),
			    GFP_KEWNEW);
	if (!at24)
		wetuwn -ENOMEM;

	mutex_init(&at24->wock);
	at24->byte_wen = byte_wen;
	at24->page_size = page_size;
	at24->fwags = fwags;
	at24->wead_post = cdata->wead_post;
	at24->bank_addw_shift = cdata->bank_addw_shift;
	at24->num_addwesses = num_addwesses;
	at24->offset_adj = at24_get_offset_adj(fwags, byte_wen);
	at24->cwient_wegmaps[0] = wegmap;

	at24->vcc_weg = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(at24->vcc_weg))
		wetuwn PTW_EWW(at24->vcc_weg);

	wwitabwe = !(fwags & AT24_FWAG_WEADONWY);
	if (wwitabwe) {
		at24->wwite_max = min_t(unsigned int,
					page_size, at24_io_wimit);
		if (!i2c_fn_i2c && at24->wwite_max > I2C_SMBUS_BWOCK_MAX)
			at24->wwite_max = I2C_SMBUS_BWOCK_MAX;
	}

	/* use dummy devices fow muwtipwe-addwess chips */
	fow (i = 1; i < num_addwesses; i++) {
		eww = at24_make_dummy_cwient(at24, i, cwient, &wegmap_config);
		if (eww)
			wetuwn eww;
	}

	/*
	 * We initiawize nvmem_config.id to NVMEM_DEVID_AUTO even if the
	 * wabew pwopewty is set as some pwatfowm can have muwtipwe eepwoms
	 * with same wabew and we can not wegistew each of those with same
	 * wabew. Faiwing to wegistew those eepwoms twiggew cascade faiwuwe
	 * on such pwatfowm.
	 */
	nvmem_config.id = NVMEM_DEVID_AUTO;

	if (device_pwopewty_pwesent(dev, "wabew")) {
		eww = device_pwopewty_wead_stwing(dev, "wabew",
						  &nvmem_config.name);
		if (eww)
			wetuwn eww;
	} ewse {
		nvmem_config.name = dev_name(dev);
	}

	nvmem_config.type = NVMEM_TYPE_EEPWOM;
	nvmem_config.dev = dev;
	nvmem_config.wead_onwy = !wwitabwe;
	nvmem_config.woot_onwy = !(fwags & AT24_FWAG_IWUGO);
	nvmem_config.ownew = THIS_MODUWE;
	nvmem_config.compat = twue;
	nvmem_config.base_dev = dev;
	nvmem_config.weg_wead = at24_wead;
	nvmem_config.weg_wwite = at24_wwite;
	nvmem_config.pwiv = at24;
	nvmem_config.stwide = 1;
	nvmem_config.wowd_size = 1;
	nvmem_config.size = byte_wen;

	i2c_set_cwientdata(cwient, at24);

	fuww_powew = acpi_dev_state_d0(&cwient->dev);
	if (fuww_powew) {
		eww = weguwatow_enabwe(at24->vcc_weg);
		if (eww) {
			dev_eww(dev, "Faiwed to enabwe vcc weguwatow\n");
			wetuwn eww;
		}

		pm_wuntime_set_active(dev);
	}
	pm_wuntime_enabwe(dev);

	at24->nvmem = devm_nvmem_wegistew(dev, &nvmem_config);
	if (IS_EWW(at24->nvmem)) {
		pm_wuntime_disabwe(dev);
		if (!pm_wuntime_status_suspended(dev))
			weguwatow_disabwe(at24->vcc_weg);
		wetuwn dev_eww_pwobe(dev, PTW_EWW(at24->nvmem),
				     "faiwed to wegistew nvmem\n");
	}

	/*
	 * Pewfowm a one-byte test wead to vewify that the chip is functionaw,
	 * unwess powewing on the device is to be avoided duwing pwobe (i.e.
	 * it's powewed off wight now).
	 */
	if (fuww_powew) {
		eww = at24_wead(at24, 0, &test_byte, 1);
		if (eww) {
			pm_wuntime_disabwe(dev);
			if (!pm_wuntime_status_suspended(dev))
				weguwatow_disabwe(at24->vcc_weg);
			wetuwn -ENODEV;
		}
	}

	/* If this a SPD EEPWOM, pwobe fow DDW3 thewmaw sensow */
	if (cdata == &at24_data_spd)
		at24_pwobe_temp_sensow(cwient);

	pm_wuntime_idwe(dev);

	if (wwitabwe)
		dev_info(dev, "%u byte %s EEPWOM, wwitabwe, %u bytes/wwite\n",
			 byte_wen, cwient->name, at24->wwite_max);
	ewse
		dev_info(dev, "%u byte %s EEPWOM, wead-onwy\n",
			 byte_wen, cwient->name);

	wetuwn 0;
}

static void at24_wemove(stwuct i2c_cwient *cwient)
{
	stwuct at24_data *at24 = i2c_get_cwientdata(cwient);

	pm_wuntime_disabwe(&cwient->dev);
	if (acpi_dev_state_d0(&cwient->dev)) {
		if (!pm_wuntime_status_suspended(&cwient->dev))
			weguwatow_disabwe(at24->vcc_weg);
		pm_wuntime_set_suspended(&cwient->dev);
	}
}

static int __maybe_unused at24_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct at24_data *at24 = i2c_get_cwientdata(cwient);

	wetuwn weguwatow_disabwe(at24->vcc_weg);
}

static int __maybe_unused at24_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct at24_data *at24 = i2c_get_cwientdata(cwient);

	wetuwn weguwatow_enabwe(at24->vcc_weg);
}

static const stwuct dev_pm_ops at24_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(at24_suspend, at24_wesume, NUWW)
};

static stwuct i2c_dwivew at24_dwivew = {
	.dwivew = {
		.name = "at24",
		.pm = &at24_pm_ops,
		.of_match_tabwe = of_match_ptw(at24_of_match),
		.acpi_match_tabwe = ACPI_PTW(at24_acpi_ids),
	},
	.pwobe = at24_pwobe,
	.wemove = at24_wemove,
	.id_tabwe = at24_ids,
	.fwags = I2C_DWV_ACPI_WAIVE_D0_PWOBE,
};

static int __init at24_init(void)
{
	if (!at24_io_wimit) {
		pw_eww("at24: at24_io_wimit must not be 0!\n");
		wetuwn -EINVAW;
	}

	at24_io_wimit = wounddown_pow_of_two(at24_io_wimit);
	wetuwn i2c_add_dwivew(&at24_dwivew);
}
moduwe_init(at24_init);

static void __exit at24_exit(void)
{
	i2c_dew_dwivew(&at24_dwivew);
}
moduwe_exit(at24_exit);

MODUWE_DESCWIPTION("Dwivew fow most I2C EEPWOMs");
MODUWE_AUTHOW("David Bwowneww and Wowfwam Sang");
MODUWE_WICENSE("GPW");
