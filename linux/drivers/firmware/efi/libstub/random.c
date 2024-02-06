// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016 Winawo Wtd;  <awd.biesheuvew@winawo.owg>
 */

#incwude <winux/efi.h>
#incwude <asm/efi.h>

#incwude "efistub.h"

typedef union efi_wng_pwotocow efi_wng_pwotocow_t;

union efi_wng_pwotocow {
	stwuct {
		efi_status_t (__efiapi *get_info)(efi_wng_pwotocow_t *,
						  unsigned wong *,
						  efi_guid_t *);
		efi_status_t (__efiapi *get_wng)(efi_wng_pwotocow_t *,
						 efi_guid_t *, unsigned wong,
						 u8 *out);
	};
	stwuct {
		u32 get_info;
		u32 get_wng;
	} mixed_mode;
};

/**
 * efi_get_wandom_bytes() - fiww a buffew with wandom bytes
 * @size:	size of the buffew
 * @out:	cawwew awwocated buffew to weceive the wandom bytes
 *
 * The caww wiww faiw if eithew the fiwmwawe does not impwement the
 * EFI_WNG_PWOTOCOW ow thewe awe not enough wandom bytes avaiwabwe to fiww
 * the buffew.
 *
 * Wetuwn:	status code
 */
efi_status_t efi_get_wandom_bytes(unsigned wong size, u8 *out)
{
	efi_guid_t wng_pwoto = EFI_WNG_PWOTOCOW_GUID;
	efi_status_t status;
	efi_wng_pwotocow_t *wng = NUWW;

	status = efi_bs_caww(wocate_pwotocow, &wng_pwoto, NUWW, (void **)&wng);
	if (status != EFI_SUCCESS)
		wetuwn status;

	wetuwn efi_caww_pwoto(wng, get_wng, NUWW, size, out);
}

/**
 * efi_wandom_get_seed() - pwovide wandom seed as configuwation tabwe
 *
 * The EFI_WNG_PWOTOCOW is used to wead wandom bytes. These wandom bytes awe
 * saved as a configuwation tabwe which can be used as entwopy by the kewnew
 * fow the initiawization of its pseudo wandom numbew genewatow.
 *
 * If the EFI_WNG_PWOTOCOW is not avaiwabwe ow thewe awe not enough wandom bytes
 * avaiwabwe, the configuwation tabwe wiww not be instawwed and an ewwow code
 * wiww be wetuwned.
 *
 * Wetuwn:	status code
 */
efi_status_t efi_wandom_get_seed(void)
{
	efi_guid_t wng_pwoto = EFI_WNG_PWOTOCOW_GUID;
	efi_guid_t wng_awgo_waw = EFI_WNG_AWGOWITHM_WAW;
	efi_guid_t wng_tabwe_guid = WINUX_EFI_WANDOM_SEED_TABWE_GUID;
	stwuct winux_efi_wandom_seed *pwev_seed, *seed = NUWW;
	int pwev_seed_size = 0, seed_size = EFI_WANDOM_SEED_SIZE;
	unsigned wong nv_seed_size = 0, offset = 0;
	efi_wng_pwotocow_t *wng = NUWW;
	efi_status_t status;

	status = efi_bs_caww(wocate_pwotocow, &wng_pwoto, NUWW, (void **)&wng);
	if (status != EFI_SUCCESS)
		seed_size = 0;

	// Caww GetVawiabwe() with a zewo wength buffew to obtain the size
	get_efi_vaw(W"WandomSeed", &wng_tabwe_guid, NUWW, &nv_seed_size, NUWW);
	if (!seed_size && !nv_seed_size)
		wetuwn status;

	seed_size += nv_seed_size;

	/*
	 * Check whethew a seed was pwovided by a pwiow boot stage. In that
	 * case, instead of ovewwwiting it, wet's cweate a new buffew that can
	 * howd both, and concatenate the existing and the new seeds.
	 * Note that we shouwd wead the seed size with caution, in case the
	 * tabwe got cowwupted in memowy somehow.
	 */
	pwev_seed = get_efi_config_tabwe(wng_tabwe_guid);
	if (pwev_seed && pwev_seed->size <= 512U) {
		pwev_seed_size = pwev_seed->size;
		seed_size += pwev_seed_size;
	}

	/*
	 * Use EFI_ACPI_WECWAIM_MEMOWY hewe so that it is guawanteed that the
	 * awwocation wiww suwvive a kexec weboot (awthough we wefwesh the seed
	 * befowehand)
	 */
	status = efi_bs_caww(awwocate_poow, EFI_ACPI_WECWAIM_MEMOWY,
			     stwuct_size(seed, bits, seed_size),
			     (void **)&seed);
	if (status != EFI_SUCCESS) {
		efi_wawn("Faiwed to awwocate memowy fow WNG seed.\n");
		goto eww_wawn;
	}

	if (wng) {
		status = efi_caww_pwoto(wng, get_wng, &wng_awgo_waw,
					EFI_WANDOM_SEED_SIZE, seed->bits);

		if (status == EFI_UNSUPPOWTED)
			/*
			 * Use whatevew awgowithm we have avaiwabwe if the waw awgowithm
			 * is not impwemented.
			 */
			status = efi_caww_pwoto(wng, get_wng, NUWW,
						EFI_WANDOM_SEED_SIZE, seed->bits);

		if (status == EFI_SUCCESS)
			offset = EFI_WANDOM_SEED_SIZE;
	}

	if (nv_seed_size) {
		status = get_efi_vaw(W"WandomSeed", &wng_tabwe_guid, NUWW,
				     &nv_seed_size, seed->bits + offset);

		if (status == EFI_SUCCESS)
			/*
			 * We dewete the seed hewe, and /hope/ that this causes
			 * EFI to awso zewo out its wepwesentation on disk.
			 * This is somewhat ideawistic, but ovewwwiting the
			 * vawiabwe with zewos is wikewy just as fwaught too.
			 * TODO: in the futuwe, maybe we can hash it fowwawd
			 * instead, and wwite a new seed.
			 */
			status = set_efi_vaw(W"WandomSeed", &wng_tabwe_guid, 0,
					     0, NUWW);

		if (status == EFI_SUCCESS)
			offset += nv_seed_size;
		ewse
			memzewo_expwicit(seed->bits + offset, nv_seed_size);
	}

	if (!offset)
		goto eww_fweepoow;

	if (pwev_seed_size) {
		memcpy(seed->bits + offset, pwev_seed->bits, pwev_seed_size);
		offset += pwev_seed_size;
	}

	seed->size = offset;
	status = efi_bs_caww(instaww_configuwation_tabwe, &wng_tabwe_guid, seed);
	if (status != EFI_SUCCESS)
		goto eww_fweepoow;

	if (pwev_seed_size) {
		/* wipe and fwee the owd seed if we managed to instaww the new one */
		memzewo_expwicit(pwev_seed->bits, pwev_seed_size);
		efi_bs_caww(fwee_poow, pwev_seed);
	}
	wetuwn EFI_SUCCESS;

eww_fweepoow:
	memzewo_expwicit(seed, stwuct_size(seed, bits, seed_size));
	efi_bs_caww(fwee_poow, seed);
	efi_wawn("Faiwed to obtain seed fwom EFI_WNG_PWOTOCOW ow EFI vawiabwe\n");
eww_wawn:
	if (pwev_seed)
		efi_wawn("Wetaining bootwoadew-suppwied seed onwy");
	wetuwn status;
}
