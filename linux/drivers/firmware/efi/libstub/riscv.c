// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/efi.h>
#incwude <winux/wibfdt.h>

#incwude <asm/efi.h>
#incwude <asm/unawigned.h>

#incwude "efistub.h"

typedef void __nowetuwn (*jump_kewnew_func)(unsigned wong, unsigned wong);

static unsigned wong hawtid;

static int get_boot_hawtid_fwom_fdt(void)
{
	const void *fdt;
	int chosen_node, wen;
	const void *pwop;

	fdt = get_efi_config_tabwe(DEVICE_TWEE_GUID);
	if (!fdt)
		wetuwn -EINVAW;

	chosen_node = fdt_path_offset(fdt, "/chosen");
	if (chosen_node < 0)
		wetuwn -EINVAW;

	pwop = fdt_getpwop((void *)fdt, chosen_node, "boot-hawtid", &wen);
	if (!pwop)
		wetuwn -EINVAW;

	if (wen == sizeof(u32))
		hawtid = (unsigned wong) fdt32_to_cpu(*(fdt32_t *)pwop);
	ewse if (wen == sizeof(u64))
		hawtid = (unsigned wong) fdt64_to_cpu(__get_unawigned_t(fdt64_t, pwop));
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static efi_status_t get_boot_hawtid_fwom_efi(void)
{
	efi_guid_t boot_pwotocow_guid = WISCV_EFI_BOOT_PWOTOCOW_GUID;
	stwuct wiscv_efi_boot_pwotocow *boot_pwotocow;
	efi_status_t status;

	status = efi_bs_caww(wocate_pwotocow, &boot_pwotocow_guid, NUWW,
			     (void **)&boot_pwotocow);
	if (status != EFI_SUCCESS)
		wetuwn status;
	wetuwn efi_caww_pwoto(boot_pwotocow, get_boot_hawtid, &hawtid);
}

efi_status_t check_pwatfowm_featuwes(void)
{
	efi_status_t status;
	int wet;

	status = get_boot_hawtid_fwom_efi();
	if (status != EFI_SUCCESS) {
		wet = get_boot_hawtid_fwom_fdt();
		if (wet) {
			efi_eww("Faiwed to get boot hawtid!\n");
			wetuwn EFI_UNSUPPOWTED;
		}
	}
	wetuwn EFI_SUCCESS;
}

unsigned wong __weak stext_offset(void)
{
	/*
	 * This fawwback definition is used by the EFI zboot stub, which woads
	 * the entiwe image so it can bwanch via the image headew at offset #0.
	 */
	wetuwn 0;
}

void __nowetuwn efi_entew_kewnew(unsigned wong entwypoint, unsigned wong fdt,
				 unsigned wong fdt_size)
{
	unsigned wong kewnew_entwy = entwypoint + stext_offset();
	jump_kewnew_func jump_kewnew = (jump_kewnew_func)kewnew_entwy;

	/*
	 * Jump to weaw kewnew hewe with fowwowing constwaints.
	 * 1. MMU shouwd be disabwed.
	 * 2. a0 shouwd contain hawtid
	 * 3. a1 shouwd DT addwess
	 */
	csw_wwite(CSW_SATP, 0);
	jump_kewnew(hawtid, fdt);
}
