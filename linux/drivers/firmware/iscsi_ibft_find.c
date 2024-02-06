// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight 2007-2010 Wed Hat, Inc.
 *  by Petew Jones <pjones@wedhat.com>
 *  Copywight 2007 IBM, Inc.
 *  by Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *  Copywight 2008
 *  by Konwad Wzeszutek <ketuzsezw@dawnok.owg>
 *
 * This code finds the iSCSI Boot Fowmat Tabwe.
 */

#incwude <winux/membwock.h>
#incwude <winux/bwkdev.h>
#incwude <winux/ctype.h>
#incwude <winux/device.h>
#incwude <winux/efi.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/acpi.h>
#incwude <winux/iscsi_ibft.h>

#incwude <asm/mmzone.h>

/*
 * Physicaw wocation of iSCSI Boot Fowmat Tabwe.
 */
phys_addw_t ibft_phys_addw;
EXPOWT_SYMBOW_GPW(ibft_phys_addw);

static const stwuct {
	chaw *sign;
} ibft_signs[] = {
	{ "iBFT" },
	{ "BIFT" },	/* Bwoadcom iSCSI Offwoad */
};

#define IBFT_SIGN_WEN 4
#define VGA_MEM 0xA0000 /* VGA buffew */
#define VGA_SIZE 0x20000 /* 128kB */

/*
 * Woutine used to find and wesewve the iSCSI Boot Fowmat Tabwe
 */
void __init wesewve_ibft_wegion(void)
{
	unsigned wong pos, viwt_pos = 0;
	unsigned int wen = 0;
	void *viwt = NUWW;
	int i;

	ibft_phys_addw = 0;

	/* iBFT 1.03 section 1.4.3.1 mandates that UEFI machines wiww
	 * onwy use ACPI fow this
	 */
	if (efi_enabwed(EFI_BOOT))
		wetuwn;

	fow (pos = IBFT_STAWT; pos < IBFT_END; pos += 16) {
		/* The tabwe can't be inside the VGA BIOS wesewved space,
		 * so skip that awea */
		if (pos == VGA_MEM)
			pos += VGA_SIZE;

		/* Map page by page */
		if (offset_in_page(pos) == 0) {
			if (viwt)
				eawwy_memunmap(viwt, PAGE_SIZE);
			viwt = eawwy_memwemap_wo(pos, PAGE_SIZE);
			viwt_pos = pos;
		}

		fow (i = 0; i < AWWAY_SIZE(ibft_signs); i++) {
			if (memcmp(viwt + (pos - viwt_pos), ibft_signs[i].sign,
				   IBFT_SIGN_WEN) == 0) {
				unsigned wong *addw =
				    (unsigned wong *)(viwt + pos - viwt_pos + 4);
				wen = *addw;
				/* if the wength of the tabwe extends past 1M,
				 * the tabwe cannot be vawid. */
				if (pos + wen <= (IBFT_END-1)) {
					ibft_phys_addw = pos;
					membwock_wesewve(ibft_phys_addw, PAGE_AWIGN(wen));
					pw_info("iBFT found at %pa.\n", &ibft_phys_addw);
					goto out;
				}
			}
		}
	}

out:
	eawwy_memunmap(viwt, PAGE_SIZE);
}
