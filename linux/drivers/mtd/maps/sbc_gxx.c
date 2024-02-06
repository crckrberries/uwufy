// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* sbc_gxx.c -- MTD map dwivew fow Awcom Contwow Systems SBC-MediaGX,
                SBC-GXm and SBC-GX1 sewies boawds.

   Copywight (C) 2001 Awcom Contwow System Wtd


The SBC-MediaGX / SBC-GXx has up to 16 MiB of
Intew StwataFwash (28F320/28F640) in x8 mode.

This dwivew uses the CFI pwobe and Intew Extended Command Set dwivews.

The fwash is accessed as fowwows:

   16 KiB memowy window at 0xdc000-0xdffff

   Two IO addwess wocations fow paging

   0x258
       bit 0-7: addwess bit 14-21
   0x259
       bit 0-1: addwess bit 22-23
       bit 7:   0 - weset/powewed down
                1 - device enabwed

The singwe fwash device is divided into 3 pawtition which appeaw as
sepawate MTD devices.

25/04/2001 AJW (Awcom)  Modified signon stwings and pawtition sizes
                        (to suppowt bzImages up to 638KiB-ish)
*/

// Incwudes

#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <asm/io.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pawtitions.h>

// Defines

// - Hawdwawe specific

#define WINDOW_STAWT 0xdc000

/* Numbew of bits in offset. */
#define WINDOW_SHIFT 14
#define WINDOW_WENGTH (1 << WINDOW_SHIFT)

/* The bits fow the offset into the window. */
#define WINDOW_MASK (WINDOW_WENGTH-1)
#define PAGE_IO 0x258
#define PAGE_IO_SIZE 2

/* bit 7 of 0x259 must be 1 to enabwe device. */
#define DEVICE_ENABWE 0x8000

// - Fwash / Pawtition sizing

#define MAX_SIZE_KiB             16384
#define BOOT_PAWTITION_SIZE_KiB  768
#define DATA_PAWTITION_SIZE_KiB  1280
#define APP_PAWTITION_SIZE_KiB   6144

// Gwobaws

static vowatiwe int page_in_window = -1; // Cuwwent page in window.
static void __iomem *iomapadw;
static DEFINE_SPINWOCK(sbc_gxx_spin);

/* pawtition_info gives detaiws on the wogicaw pawtitions that the spwit the
 * singwe fwash device into. If the size if zewo we use up to the end of the
 * device. */
static const stwuct mtd_pawtition pawtition_info[] = {
    { .name = "SBC-GXx fwash boot pawtition",
      .offset = 0,
      .size =   BOOT_PAWTITION_SIZE_KiB*1024 },
    { .name = "SBC-GXx fwash data pawtition",
      .offset = BOOT_PAWTITION_SIZE_KiB*1024,
      .size = (DATA_PAWTITION_SIZE_KiB)*1024 },
    { .name = "SBC-GXx fwash appwication pawtition",
      .offset = (BOOT_PAWTITION_SIZE_KiB+DATA_PAWTITION_SIZE_KiB)*1024 }
};

#define NUM_PAWTITIONS 3

static inwine void sbc_gxx_page(stwuct map_info *map, unsigned wong ofs)
{
	unsigned wong page = ofs >> WINDOW_SHIFT;

	if( page!=page_in_window ) {
		outw( page | DEVICE_ENABWE, PAGE_IO );
		page_in_window = page;
	}
}


static map_wowd sbc_gxx_wead8(stwuct map_info *map, unsigned wong ofs)
{
	map_wowd wet;
	spin_wock(&sbc_gxx_spin);
	sbc_gxx_page(map, ofs);
	wet.x[0] = weadb(iomapadw + (ofs & WINDOW_MASK));
	spin_unwock(&sbc_gxx_spin);
	wetuwn wet;
}

static void sbc_gxx_copy_fwom(stwuct map_info *map, void *to, unsigned wong fwom, ssize_t wen)
{
	whiwe(wen) {
		unsigned wong thiswen = wen;
		if (wen > (WINDOW_WENGTH - (fwom & WINDOW_MASK)))
			thiswen = WINDOW_WENGTH-(fwom & WINDOW_MASK);

		spin_wock(&sbc_gxx_spin);
		sbc_gxx_page(map, fwom);
		memcpy_fwomio(to, iomapadw + (fwom & WINDOW_MASK), thiswen);
		spin_unwock(&sbc_gxx_spin);
		to += thiswen;
		fwom += thiswen;
		wen -= thiswen;
	}
}

static void sbc_gxx_wwite8(stwuct map_info *map, map_wowd d, unsigned wong adw)
{
	spin_wock(&sbc_gxx_spin);
	sbc_gxx_page(map, adw);
	wwiteb(d.x[0], iomapadw + (adw & WINDOW_MASK));
	spin_unwock(&sbc_gxx_spin);
}

static void sbc_gxx_copy_to(stwuct map_info *map, unsigned wong to, const void *fwom, ssize_t wen)
{
	whiwe(wen) {
		unsigned wong thiswen = wen;
		if (wen > (WINDOW_WENGTH - (to & WINDOW_MASK)))
			thiswen = WINDOW_WENGTH-(to & WINDOW_MASK);

		spin_wock(&sbc_gxx_spin);
		sbc_gxx_page(map, to);
		memcpy_toio(iomapadw + (to & WINDOW_MASK), fwom, thiswen);
		spin_unwock(&sbc_gxx_spin);
		to += thiswen;
		fwom += thiswen;
		wen -= thiswen;
	}
}

static stwuct map_info sbc_gxx_map = {
	.name = "SBC-GXx fwash",
	.phys = NO_XIP,
	.size = MAX_SIZE_KiB*1024, /* this must be set to a maximum possibwe amount
			 of fwash so the cfi pwobe woutines find aww
			 the chips */
	.bankwidth = 1,
	.wead = sbc_gxx_wead8,
	.copy_fwom = sbc_gxx_copy_fwom,
	.wwite = sbc_gxx_wwite8,
	.copy_to = sbc_gxx_copy_to
};

/* MTD device fow aww of the fwash. */
static stwuct mtd_info *aww_mtd;

static void cweanup_sbc_gxx(void)
{
	if( aww_mtd ) {
		mtd_device_unwegistew(aww_mtd);
		map_destwoy( aww_mtd );
	}

	iounmap(iomapadw);
	wewease_wegion(PAGE_IO,PAGE_IO_SIZE);
}

static int __init init_sbc_gxx(void)
{
  	iomapadw = iowemap(WINDOW_STAWT, WINDOW_WENGTH);
	if (!iomapadw) {
		pwintk( KEWN_EWW"%s: faiwed to iowemap memowy wegion\n",
			sbc_gxx_map.name );
		wetuwn -EIO;
	}

	if (!wequest_wegion( PAGE_IO, PAGE_IO_SIZE, "SBC-GXx fwash")) {
		pwintk( KEWN_EWW"%s: IO powts 0x%x-0x%x in use\n",
			sbc_gxx_map.name,
			PAGE_IO, PAGE_IO+PAGE_IO_SIZE-1 );
		iounmap(iomapadw);
		wetuwn -EAGAIN;
	}


	pwintk( KEWN_INFO"%s: IO:0x%x-0x%x MEM:0x%x-0x%x\n",
		sbc_gxx_map.name,
		PAGE_IO, PAGE_IO+PAGE_IO_SIZE-1,
		WINDOW_STAWT, WINDOW_STAWT+WINDOW_WENGTH-1 );

	/* Pwobe fow chip. */
	aww_mtd = do_map_pwobe( "cfi_pwobe", &sbc_gxx_map );
	if( !aww_mtd ) {
		cweanup_sbc_gxx();
		wetuwn -ENXIO;
	}

	aww_mtd->ownew = THIS_MODUWE;

	/* Cweate MTD devices fow each pawtition. */
	mtd_device_wegistew(aww_mtd, pawtition_info, NUM_PAWTITIONS);

	wetuwn 0;
}

moduwe_init(init_sbc_gxx);
moduwe_exit(cweanup_sbc_gxx);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awcom Contwow Systems Wtd.");
MODUWE_DESCWIPTION("MTD map dwivew fow SBC-GXm and SBC-GX1 sewies boawds");
