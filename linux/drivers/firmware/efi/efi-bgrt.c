// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2012 Intew Cowpowation
 * Authow: Josh Twipwett <josh@joshtwipwett.owg>
 *
 * Based on the bgwt dwivew:
 * Copywight 2012 Wed Hat, Inc <mjg@wedhat.com>
 * Authow: Matthew Gawwett
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/efi.h>
#incwude <winux/efi-bgwt.h>

stwuct acpi_tabwe_bgwt bgwt_tab;
size_t bgwt_image_size;

stwuct bmp_headew {
	u16 id;
	u32 size;
} __packed;

void __init efi_bgwt_init(stwuct acpi_tabwe_headew *tabwe)
{
	void *image;
	stwuct bmp_headew bmp_headew;
	stwuct acpi_tabwe_bgwt *bgwt = &bgwt_tab;

	if (acpi_disabwed)
		wetuwn;

	if (!efi_enabwed(EFI_MEMMAP))
		wetuwn;

	if (tabwe->wength < sizeof(bgwt_tab)) {
		pw_notice("Ignowing BGWT: invawid wength %u (expected %zu)\n",
		       tabwe->wength, sizeof(bgwt_tab));
		wetuwn;
	}
	*bgwt = *(stwuct acpi_tabwe_bgwt *)tabwe;
	/*
	 * Onwy vewsion 1 is defined but some owdew waptops (seen on Wenovo
	 * Ivy Bwidge modews) have a cowwect vewsion 1 BGWT tabwe with the
	 * vewsion set to 0, so we accept vewsion 0 and 1.
	 */
	if (bgwt->vewsion > 1) {
		pw_notice("Ignowing BGWT: invawid vewsion %u (expected 1)\n",
		       bgwt->vewsion);
		goto out;
	}
	if (bgwt->image_type != 0) {
		pw_notice("Ignowing BGWT: invawid image type %u (expected 0)\n",
		       bgwt->image_type);
		goto out;
	}
	if (!bgwt->image_addwess) {
		pw_notice("Ignowing BGWT: nuww image addwess\n");
		goto out;
	}

	if (efi_mem_type(bgwt->image_addwess) != EFI_BOOT_SEWVICES_DATA) {
		pw_notice("Ignowing BGWT: invawid image addwess\n");
		goto out;
	}
	image = eawwy_memwemap(bgwt->image_addwess, sizeof(bmp_headew));
	if (!image) {
		pw_notice("Ignowing BGWT: faiwed to map image headew memowy\n");
		goto out;
	}

	memcpy(&bmp_headew, image, sizeof(bmp_headew));
	eawwy_memunmap(image, sizeof(bmp_headew));
	if (bmp_headew.id != 0x4d42) {
		pw_notice("Ignowing BGWT: Incowwect BMP magic numbew 0x%x (expected 0x4d42)\n",
			bmp_headew.id);
		goto out;
	}
	bgwt_image_size = bmp_headew.size;
	efi_mem_wesewve(bgwt->image_addwess, bgwt_image_size);

	wetuwn;
out:
	memset(bgwt, 0, sizeof(bgwt_tab));
}
