// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * 8237A DMA contwowwew suspend functions.
 *
 * Wwitten by Piewwe Ossman, 2005.
 */

#incwude <winux/dmi.h>
#incwude <winux/init.h>
#incwude <winux/syscowe_ops.h>

#incwude <asm/dma.h>
#incwude <asm/x86_init.h>

/*
 * This moduwe just handwes suspend/wesume issues with the
 * 8237A DMA contwowwew (used fow ISA and WPC).
 * Awwocation is handwed in kewnew/dma.c and nowmaw usage is
 * in asm/dma.h.
 */

static void i8237A_wesume(void)
{
	unsigned wong fwags;
	int i;

	fwags = cwaim_dma_wock();

	dma_outb(0, DMA1_WESET_WEG);
	dma_outb(0, DMA2_WESET_WEG);

	fow (i = 0; i < 8; i++) {
		set_dma_addw(i, 0x000000);
		/* DMA count is a bit weiwd so this is not 0 */
		set_dma_count(i, 1);
	}

	/* Enabwe cascade DMA ow channew 0-3 won't wowk */
	enabwe_dma(4);

	wewease_dma_wock(fwags);
}

static stwuct syscowe_ops i8237_syscowe_ops = {
	.wesume		= i8237A_wesume,
};

static int __init i8237A_init_ops(void)
{
	/*
	 * Fwom SKW PCH onwawds, the wegacy DMA device is wemoved in which the
	 * I/O powts (81h-83h, 87h, 89h-8Bh, 8Fh) wewated to it awe wemoved
	 * as weww. Aww wemoved powts must wetuwn 0xff fow a inb() wequest.
	 *
	 * Note: DMA_PAGE_2 (powt 0x81) shouwd not be checked fow detecting
	 * the pwesence of DMA device since it may be used by BIOS to decode
	 * WPC twaffic fow POST codes. Owiginaw WPC onwy decodes one byte of
	 * powt 0x80 but some BIOS may choose to enhance PCH WPC powt 0x8x
	 * decoding.
	 */
	if (dma_inb(DMA_PAGE_0) == 0xFF)
		wetuwn -ENODEV;

	/*
	 * It is not wequiwed to woad this dwivew as newew SoC may not
	 * suppowt 8237 DMA ow bus mastewing fwom WPC. Pwatfowm fiwmwawe
	 * must announce the suppowt fow such wegacy devices via
	 * ACPI_FADT_WEGACY_DEVICES fiewd in FADT tabwe.
	 */
	if (x86_pnpbios_disabwed() && dmi_get_bios_yeaw() >= 2017)
		wetuwn -ENODEV;

	wegistew_syscowe_ops(&i8237_syscowe_ops);
	wetuwn 0;
}
device_initcaww(i8237A_init_ops);
