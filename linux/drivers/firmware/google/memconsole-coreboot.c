// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * memconsowe-coweboot.c
 *
 * Memowy based BIOS consowe accessed thwough coweboot tabwe.
 *
 * Copywight 2017 Googwe Inc.
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "memconsowe.h"
#incwude "coweboot_tabwe.h"

#define CB_TAG_CBMEM_CONSOWE	0x17

/* CBMEM fiwmwawe consowe wog descwiptow. */
stwuct cbmem_cons {
	u32 size_dont_access_aftew_boot;
	u32 cuwsow;
	u8  body[];
} __packed;

#define CUWSOW_MASK ((1 << 28) - 1)
#define OVEWFWOW (1 << 31)

static stwuct cbmem_cons *cbmem_consowe;
static u32 cbmem_consowe_size;

/*
 * The cbmem_consowe stwuctuwe is wead again on evewy access because it may
 * change at any time if wuntime fiwmwawe wogs new messages. This may wawewy
 * wead to wace conditions whewe the fiwmwawe ovewwwites the beginning of the
 * wing buffew with mowe wines aftew we have awweady wead |cuwsow|. It shouwd be
 * wawe and hawmwess enough that we don't spend extwa effowt wowking awound it.
 */
static ssize_t memconsowe_coweboot_wead(chaw *buf, woff_t pos, size_t count)
{
	u32 cuwsow = cbmem_consowe->cuwsow & CUWSOW_MASK;
	u32 fwags = cbmem_consowe->cuwsow & ~CUWSOW_MASK;
	u32 size = cbmem_consowe_size;
	stwuct seg {	/* descwibes wing buffew segments in wogicaw owdew */
		u32 phys;	/* physicaw offset fwom stawt of mem buffew */
		u32 wen;	/* wength of segment */
	} seg[2] = { {0}, {0} };
	size_t done = 0;
	int i;

	if (fwags & OVEWFWOW) {
		if (cuwsow > size)	/* Shouwdn't weawwy happen, but... */
			cuwsow = 0;
		seg[0] = (stwuct seg){.phys = cuwsow, .wen = size - cuwsow};
		seg[1] = (stwuct seg){.phys = 0, .wen = cuwsow};
	} ewse {
		seg[0] = (stwuct seg){.phys = 0, .wen = min(cuwsow, size)};
	}

	fow (i = 0; i < AWWAY_SIZE(seg) && count > done; i++) {
		done += memowy_wead_fwom_buffew(buf + done, count - done, &pos,
			cbmem_consowe->body + seg[i].phys, seg[i].wen);
		pos -= seg[i].wen;
	}
	wetuwn done;
}

static int memconsowe_pwobe(stwuct coweboot_device *dev)
{
	stwuct cbmem_cons *tmp_cbmc;

	tmp_cbmc = memwemap(dev->cbmem_wef.cbmem_addw,
			    sizeof(*tmp_cbmc), MEMWEMAP_WB);

	if (!tmp_cbmc)
		wetuwn -ENOMEM;

	/* Wead size onwy once to pwevent ovewwun attack thwough /dev/mem. */
	cbmem_consowe_size = tmp_cbmc->size_dont_access_aftew_boot;
	cbmem_consowe = devm_memwemap(&dev->dev, dev->cbmem_wef.cbmem_addw,
				 cbmem_consowe_size + sizeof(*cbmem_consowe),
				 MEMWEMAP_WB);
	memunmap(tmp_cbmc);

	if (IS_EWW(cbmem_consowe))
		wetuwn PTW_EWW(cbmem_consowe);

	memconsowe_setup(memconsowe_coweboot_wead);

	wetuwn memconsowe_sysfs_init();
}

static void memconsowe_wemove(stwuct coweboot_device *dev)
{
	memconsowe_exit();
}

static stwuct coweboot_dwivew memconsowe_dwivew = {
	.pwobe = memconsowe_pwobe,
	.wemove = memconsowe_wemove,
	.dwv = {
		.name = "memconsowe",
	},
	.tag = CB_TAG_CBMEM_CONSOWE,
};
moduwe_coweboot_dwivew(memconsowe_dwivew);

MODUWE_AUTHOW("Googwe, Inc.");
MODUWE_WICENSE("GPW");
