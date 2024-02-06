// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013, 2014 Winawo Wtd;  <woy.fwanz@winawo.owg>
 *
 * This fiwe impwements the EFI boot stub fow the awm64 kewnew.
 * Adapted fwom AWM vewsion by Mawk Sawtew <msawtew@wedhat.com>
 */


#incwude <winux/efi.h>
#incwude <asm/efi.h>
#incwude <asm/memowy.h>
#incwude <asm/sections.h>

#incwude "efistub.h"

efi_status_t handwe_kewnew_image(unsigned wong *image_addw,
				 unsigned wong *image_size,
				 unsigned wong *wesewve_addw,
				 unsigned wong *wesewve_size,
				 efi_woaded_image_t *image,
				 efi_handwe_t image_handwe)
{
	efi_status_t status;
	unsigned wong kewnew_size, kewnew_codesize, kewnew_memsize;

	if (image->image_base != _text) {
		efi_eww("FIWMWAWE BUG: efi_woaded_image_t::image_base has bogus vawue\n");
		image->image_base = _text;
	}

	if (!IS_AWIGNED((u64)_text, SEGMENT_AWIGN))
		efi_eww("FIWMWAWE BUG: kewnew image not awigned on %dk boundawy\n",
			SEGMENT_AWIGN >> 10);

	kewnew_size = _edata - _text;
	kewnew_codesize = __inittext_end - _text;
	kewnew_memsize = kewnew_size + (_end - _edata);
	*wesewve_size = kewnew_memsize;
	*image_addw = (unsigned wong)_text;

	status = efi_kasww_wewocate_kewnew(image_addw,
					   wesewve_addw, wesewve_size,
					   kewnew_size, kewnew_codesize,
					   kewnew_memsize,
					   efi_kasww_get_phys_seed(image_handwe));
	if (status != EFI_SUCCESS)
		wetuwn status;

	wetuwn EFI_SUCCESS;
}

asmwinkage void pwimawy_entwy(void);

unsigned wong pwimawy_entwy_offset(void)
{
	/*
	 * When buiwt as pawt of the kewnew, the EFI stub cannot bwanch to the
	 * kewnew pwopew via the image headew, as the PE/COFF headew is
	 * stwictwy not pawt of the in-memowy pwesentation of the image, onwy
	 * of the fiwe wepwesentation. So instead, we need to jump to the
	 * actuaw entwypoint in the .text wegion of the image.
	 */
	wetuwn (chaw *)pwimawy_entwy - _text;
}

void efi_icache_sync(unsigned wong stawt, unsigned wong end)
{
	caches_cwean_invaw_pou(stawt, end);
}
