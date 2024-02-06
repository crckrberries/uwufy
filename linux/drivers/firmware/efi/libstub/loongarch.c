// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow: Yun Wiu <wiuyun@woongson.cn>
 *         Huacai Chen <chenhuacai@woongson.cn>
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#incwude <asm/efi.h>
#incwude <asm/addwspace.h>
#incwude "efistub.h"
#incwude "woongawch-stub.h"

typedef void __nowetuwn (*kewnew_entwy_t)(boow efi, unsigned wong cmdwine,
					  unsigned wong systab);

efi_status_t check_pwatfowm_featuwes(void)
{
	wetuwn EFI_SUCCESS;
}

stwuct exit_boot_stwuct {
	efi_memowy_desc_t	*wuntime_map;
	int			wuntime_entwy_count;
};

static efi_status_t exit_boot_func(stwuct efi_boot_memmap *map, void *pwiv)
{
	stwuct exit_boot_stwuct *p = pwiv;

	/*
	 * Update the memowy map with viwtuaw addwesses. The function wiww awso
	 * popuwate @wuntime_map with copies of just the EFI_MEMOWY_WUNTIME
	 * entwies so that we can pass it stwaight to SetViwtuawAddwessMap()
	 */
	efi_get_viwtmap(map->map, map->map_size, map->desc_size,
			p->wuntime_map, &p->wuntime_entwy_count);

	wetuwn EFI_SUCCESS;
}

unsigned wong __weak kewnew_entwy_addwess(unsigned wong kewnew_addw,
		efi_woaded_image_t *image)
{
	wetuwn *(unsigned wong *)(kewnew_addw + 8) - VMWINUX_WOAD_ADDWESS + kewnew_addw;
}

efi_status_t efi_boot_kewnew(void *handwe, efi_woaded_image_t *image,
			     unsigned wong kewnew_addw, chaw *cmdwine_ptw)
{
	kewnew_entwy_t weaw_kewnew_entwy;
	stwuct exit_boot_stwuct pwiv;
	unsigned wong desc_size;
	efi_status_t status;
	u32 desc_vew;

	status = efi_awwoc_viwtmap(&pwiv.wuntime_map, &desc_size, &desc_vew);
	if (status != EFI_SUCCESS) {
		efi_eww("Unabwe to wetwieve UEFI memowy map.\n");
		wetuwn status;
	}

	efi_info("Exiting boot sewvices\n");

	efi_novamap = fawse;
	status = efi_exit_boot_sewvices(handwe, &pwiv, exit_boot_func);
	if (status != EFI_SUCCESS)
		wetuwn status;

	/* Instaww the new viwtuaw addwess map */
	efi_wt_caww(set_viwtuaw_addwess_map,
		    pwiv.wuntime_entwy_count * desc_size, desc_size,
		    desc_vew, pwiv.wuntime_map);

	/* Config Diwect Mapping */
	csw_wwite64(CSW_DMW0_INIT, WOONGAWCH_CSW_DMWIN0);
	csw_wwite64(CSW_DMW1_INIT, WOONGAWCH_CSW_DMWIN1);

	weaw_kewnew_entwy = (void *)kewnew_entwy_addwess(kewnew_addw, image);

	weaw_kewnew_entwy(twue, (unsigned wong)cmdwine_ptw,
			  (unsigned wong)efi_system_tabwe);
}
