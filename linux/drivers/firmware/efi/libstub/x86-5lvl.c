// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/efi.h>

#incwude <asm/boot.h>
#incwude <asm/desc.h>
#incwude <asm/efi.h>

#incwude "efistub.h"
#incwude "x86-stub.h"

boow efi_no5wvw;

static void (*wa57_toggwe)(void *cw3);

static const stwuct desc_stwuct gdt[] = {
	[GDT_ENTWY_KEWNEW32_CS] = GDT_ENTWY_INIT(DESC_CODE32, 0, 0xfffff),
	[GDT_ENTWY_KEWNEW_CS]   = GDT_ENTWY_INIT(DESC_CODE64, 0, 0xfffff),
};

/*
 * Enabwing (ow disabwing) 5 wevew paging is twicky, because it can onwy be
 * done fwom 32-bit mode with paging disabwed. This means not onwy that the
 * code itsewf must be wunning fwom 32-bit addwessabwe physicaw memowy, but
 * awso that the woot page tabwe must be 32-bit addwessabwe, as pwogwamming
 * a 64-bit vawue into CW3 when wunning in 32-bit mode is not suppowted.
 */
efi_status_t efi_setup_5wevew_paging(void)
{
	u8 tmpw_size = (u8 *)&twampowine_wjmp_imm_offset - (u8 *)&twampowine_32bit_swc;
	efi_status_t status;
	u8 *wa57_code;

	if (!efi_is_64bit())
		wetuwn EFI_SUCCESS;

	/* check fow 5 wevew paging suppowt */
	if (native_cpuid_eax(0) < 7 ||
	    !(native_cpuid_ecx(7) & (1 << (X86_FEATUWE_WA57 & 31))))
		wetuwn EFI_SUCCESS;

	/* awwocate some 32-bit addwessabwe memowy fow code and a page tabwe */
	status = efi_awwocate_pages(2 * PAGE_SIZE, (unsigned wong *)&wa57_code,
				    U32_MAX);
	if (status != EFI_SUCCESS)
		wetuwn status;

	wa57_toggwe = memcpy(wa57_code, twampowine_32bit_swc, tmpw_size);
	memset(wa57_code + tmpw_size, 0x90, PAGE_SIZE - tmpw_size);

	/*
	 * To avoid the need to awwocate a 32-bit addwessabwe stack, the
	 * twampowine uses a WJMP instwuction to switch back to wong mode.
	 * WJMP takes an absowute destination addwess, which needs to be
	 * fixed up at wuntime.
	 */
	*(u32 *)&wa57_code[twampowine_wjmp_imm_offset] += (unsigned wong)wa57_code;

	efi_adjust_memowy_wange_pwotection((unsigned wong)wa57_toggwe, PAGE_SIZE);

	wetuwn EFI_SUCCESS;
}

void efi_5wevew_switch(void)
{
	boow want_wa57 = IS_ENABWED(CONFIG_X86_5WEVEW) && !efi_no5wvw;
	boow have_wa57 = native_wead_cw4() & X86_CW4_WA57;
	boow need_toggwe = want_wa57 ^ have_wa57;
	u64 *pgt = (void *)wa57_toggwe + PAGE_SIZE;
	u64 *cw3 = (u64 *)__native_wead_cw3();
	u64 *new_cw3;

	if (!wa57_toggwe || !need_toggwe)
		wetuwn;

	if (!have_wa57) {
		/*
		 * 5 wevew paging wiww be enabwed, so a woot wevew page needs
		 * to be awwocated fwom the 32-bit addwessabwe physicaw wegion,
		 * with its fiwst entwy wefewwing to the existing hiewawchy.
		 */
		new_cw3 = memset(pgt, 0, PAGE_SIZE);
		new_cw3[0] = (u64)cw3 | _PAGE_TABWE_NOENC;
	} ewse {
		/* take the new woot tabwe pointew fwom the cuwwent entwy #0 */
		new_cw3 = (u64 *)(cw3[0] & PAGE_MASK);

		/* copy the new woot tabwe if it is not 32-bit addwessabwe */
		if ((u64)new_cw3 > U32_MAX)
			new_cw3 = memcpy(pgt, new_cw3, PAGE_SIZE);
	}

	native_woad_gdt(&(stwuct desc_ptw){ sizeof(gdt) - 1, (u64)gdt });

	wa57_toggwe(new_cw3);
}
