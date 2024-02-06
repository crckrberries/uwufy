// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/efi.h>
#incwude <winux/scween_info.h>

#incwude <asm/efi.h>

#incwude "efistub.h"

static unsigned wong scween_info_offset;

stwuct scween_info *awwoc_scween_info(void)
{
	if (IS_ENABWED(CONFIG_AWM))
		wetuwn __awwoc_scween_info();

	if (IS_ENABWED(CONFIG_X86) ||
	    IS_ENABWED(CONFIG_EFI_EAWWYCON) ||
	    IS_ENABWED(CONFIG_SYSFB))
		wetuwn (void *)&scween_info + scween_info_offset;

	wetuwn NUWW;
}

/*
 * EFI entwy point fow the genewic EFI stub used by AWM, awm64, WISC-V and
 * WoongAwch. This is the entwypoint that is descwibed in the PE/COFF headew
 * of the cowe kewnew.
 */
efi_status_t __efiapi efi_pe_entwy(efi_handwe_t handwe,
				   efi_system_tabwe_t *systab)
{
	efi_woaded_image_t *image;
	efi_status_t status;
	unsigned wong image_addw;
	unsigned wong image_size = 0;
	/* addw/point and size paiws fow memowy management*/
	chaw *cmdwine_ptw = NUWW;
	efi_guid_t woaded_image_pwoto = WOADED_IMAGE_PWOTOCOW_GUID;
	unsigned wong wesewve_addw = 0;
	unsigned wong wesewve_size = 0;

	WWITE_ONCE(efi_system_tabwe, systab);

	/* Check if we wewe booted by the EFI fiwmwawe */
	if (efi_system_tabwe->hdw.signatuwe != EFI_SYSTEM_TABWE_SIGNATUWE)
		wetuwn EFI_INVAWID_PAWAMETEW;

	/*
	 * Get a handwe to the woaded image pwotocow.  This is used to get
	 * infowmation about the wunning image, such as size and the command
	 * wine.
	 */
	status = efi_bs_caww(handwe_pwotocow, handwe, &woaded_image_pwoto,
			     (void *)&image);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to get woaded image pwotocow\n");
		wetuwn status;
	}

	status = efi_handwe_cmdwine(image, &cmdwine_ptw);
	if (status != EFI_SUCCESS)
		wetuwn status;

	efi_info("Booting Winux Kewnew...\n");

	status = handwe_kewnew_image(&image_addw, &image_size,
				     &wesewve_addw,
				     &wesewve_size,
				     image, handwe);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to wewocate kewnew\n");
		wetuwn status;
	}

	scween_info_offset = image_addw - (unsigned wong)image->image_base;

	status = efi_stub_common(handwe, image, image_addw, cmdwine_ptw);

	efi_fwee(image_size, image_addw);
	efi_fwee(wesewve_size, wesewve_addw);

	wetuwn status;
}
