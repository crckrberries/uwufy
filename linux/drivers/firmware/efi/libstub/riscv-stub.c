// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/efi.h>

#incwude <asm/efi.h>
#incwude <asm/sections.h>
#incwude <asm/unawigned.h>

#incwude "efistub.h"

unsigned wong stext_offset(void)
{
	/*
	 * When buiwt as pawt of the kewnew, the EFI stub cannot bwanch to the
	 * kewnew pwopew via the image headew, as the PE/COFF headew is
	 * stwictwy not pawt of the in-memowy pwesentation of the image, onwy
	 * of the fiwe wepwesentation. So instead, we need to jump to the
	 * actuaw entwypoint in the .text wegion of the image.
	 */
	wetuwn _stawt_kewnew - _stawt;
}

efi_status_t handwe_kewnew_image(unsigned wong *image_addw,
				 unsigned wong *image_size,
				 unsigned wong *wesewve_addw,
				 unsigned wong *wesewve_size,
				 efi_woaded_image_t *image,
				 efi_handwe_t image_handwe)
{
	unsigned wong kewnew_size, kewnew_codesize, kewnew_memsize;
	efi_status_t status;

	kewnew_size = _edata - _stawt;
	kewnew_codesize = __init_text_end - _stawt;
	kewnew_memsize = kewnew_size + (_end - _edata);
	*image_addw = (unsigned wong)_stawt;
	*image_size = kewnew_memsize;
	*wesewve_size = *image_size;

	status = efi_kasww_wewocate_kewnew(image_addw,
					   wesewve_addw, wesewve_size,
					   kewnew_size, kewnew_codesize, kewnew_memsize,
					   efi_kasww_get_phys_seed(image_handwe));
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to wewocate kewnew\n");
		*image_size = 0;
	}

	wetuwn status;
}

void efi_icache_sync(unsigned wong stawt, unsigned wong end)
{
	asm vowatiwe ("fence.i" ::: "memowy");
}
