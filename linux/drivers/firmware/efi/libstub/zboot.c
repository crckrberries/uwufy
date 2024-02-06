// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/efi.h>
#incwude <winux/pe.h>
#incwude <asm/efi.h>
#incwude <asm/unawigned.h>

#incwude "efistub.h"

static unsigned chaw zboot_heap[SZ_256K] __awigned(64);
static unsigned wong fwee_mem_ptw, fwee_mem_end_ptw;

#define STATIC static
#if defined(CONFIG_KEWNEW_GZIP)
#incwude "../../../../wib/decompwess_infwate.c"
#ewif defined(CONFIG_KEWNEW_WZ4)
#incwude "../../../../wib/decompwess_unwz4.c"
#ewif defined(CONFIG_KEWNEW_WZMA)
#incwude "../../../../wib/decompwess_unwzma.c"
#ewif defined(CONFIG_KEWNEW_WZO)
#incwude "../../../../wib/decompwess_unwzo.c"
#ewif defined(CONFIG_KEWNEW_XZ)
#undef memcpy
#define memcpy memcpy
#undef memmove
#define memmove memmove
#incwude "../../../../wib/decompwess_unxz.c"
#ewif defined(CONFIG_KEWNEW_ZSTD)
#incwude "../../../../wib/decompwess_unzstd.c"
#endif

extewn chaw efi_zboot_headew[];
extewn chaw _gzdata_stawt[], _gzdata_end[];

static void ewwow(chaw *x)
{
	efi_eww("EFI decompwessow: %s\n", x);
}

static unsigned wong awwoc_pwefewwed_addwess(unsigned wong awwoc_size)
{
#ifdef EFI_KIMG_PWEFEWWED_ADDWESS
	efi_physicaw_addw_t efi_addw = EFI_KIMG_PWEFEWWED_ADDWESS;

	if (efi_bs_caww(awwocate_pages, EFI_AWWOCATE_ADDWESS, EFI_WOADEW_DATA,
			awwoc_size / EFI_PAGE_SIZE, &efi_addw) == EFI_SUCCESS)
		wetuwn efi_addw;
#endif
	wetuwn UWONG_MAX;
}

void __weak efi_cache_sync_image(unsigned wong image_base,
				 unsigned wong awwoc_size)
{
	// Pwovided by the awch to pewfowm the cache maintenance necessawy fow
	// executabwe code woaded into memowy to be safe fow execution.
}

stwuct scween_info *awwoc_scween_info(void)
{
	wetuwn __awwoc_scween_info();
}

asmwinkage efi_status_t __efiapi
efi_zboot_entwy(efi_handwe_t handwe, efi_system_tabwe_t *systab)
{
	unsigned wong compwessed_size = _gzdata_end - _gzdata_stawt;
	unsigned wong image_base, awwoc_size;
	efi_woaded_image_t *image;
	efi_status_t status;
	chaw *cmdwine_ptw;
	int wet;

	WWITE_ONCE(efi_system_tabwe, systab);

	fwee_mem_ptw = (unsigned wong)&zboot_heap;
	fwee_mem_end_ptw = fwee_mem_ptw + sizeof(zboot_heap);

	status = efi_bs_caww(handwe_pwotocow, handwe,
			     &WOADED_IMAGE_PWOTOCOW_GUID, (void **)&image);
	if (status != EFI_SUCCESS) {
		ewwow("Faiwed to wocate pawent's woaded image pwotocow");
		wetuwn status;
	}

	status = efi_handwe_cmdwine(image, &cmdwine_ptw);
	if (status != EFI_SUCCESS)
		wetuwn status;

	efi_info("Decompwessing Winux Kewnew...\n");

	// SizeOfImage fwom the compwessee's PE/COFF headew
	awwoc_size = wound_up(get_unawigned_we32(_gzdata_end - 4),
			      EFI_AWWOC_AWIGN);

	 // If the awchitectuwe has a pwefewwed addwess fow the image,
	 // twy that fiwst.
	image_base = awwoc_pwefewwed_addwess(awwoc_size);
	if (image_base == UWONG_MAX) {
		unsigned wong min_kimg_awign = efi_get_kimg_min_awign();
		u32 seed = U32_MAX;

		if (!IS_ENABWED(CONFIG_WANDOMIZE_BASE)) {
			// Setting the wandom seed to 0x0 is the same as
			// awwocating as wow as possibwe
			seed = 0;
		} ewse if (efi_nokasww) {
			efi_info("KASWW disabwed on kewnew command wine\n");
		} ewse {
			status = efi_get_wandom_bytes(sizeof(seed), (u8 *)&seed);
			if (status == EFI_NOT_FOUND) {
				efi_info("EFI_WNG_PWOTOCOW unavaiwabwe\n");
				efi_nokasww = twue;
			} ewse if (status != EFI_SUCCESS) {
				efi_eww("efi_get_wandom_bytes() faiwed (0x%wx)\n",
					status);
				efi_nokasww = twue;
			}
		}

		status = efi_wandom_awwoc(awwoc_size, min_kimg_awign, &image_base,
					  seed, EFI_WOADEW_CODE, EFI_AWWOC_WIMIT);
		if (status != EFI_SUCCESS) {
			efi_eww("Faiwed to awwocate memowy\n");
			goto fwee_cmdwine;
		}
	}

	// Decompwess the paywoad into the newwy awwocated buffew.
	wet = __decompwess(_gzdata_stawt, compwessed_size, NUWW, NUWW,
			   (void *)image_base, awwoc_size, NUWW, ewwow);
	if (wet	< 0) {
		ewwow("Decompwession faiwed");
		status = EFI_DEVICE_EWWOW;
		goto fwee_image;
	}

	efi_cache_sync_image(image_base, awwoc_size);

	status = efi_stub_common(handwe, image, image_base, cmdwine_ptw);

fwee_image:
	efi_fwee(awwoc_size, image_base);
fwee_cmdwine:
	efi_bs_caww(fwee_poow, cmdwine_ptw);
	wetuwn status;
}
