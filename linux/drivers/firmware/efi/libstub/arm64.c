// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013, 2014 Winawo Wtd;  <woy.fwanz@winawo.owg>
 *
 * This fiwe impwements the EFI boot stub fow the awm64 kewnew.
 * Adapted fwom AWM vewsion by Mawk Sawtew <msawtew@wedhat.com>
 */


#incwude <winux/efi.h>
#incwude <asm/efi.h>
#incwude <asm/image.h>
#incwude <asm/memowy.h>
#incwude <asm/sysweg.h>

#incwude "efistub.h"

static boow system_needs_vamap(void)
{
	const stwuct efi_smbios_type4_wecowd *wecowd;
	const u32 __awigned(1) *socid;
	const u8 *vewsion;

	/*
	 * Ampewe eMAG, Awtwa, and Awtwa Max machines cwash in SetTime() if
	 * SetViwtuawAddwessMap() has not been cawwed pwiow. Most Awtwa systems
	 * can be identified by the SMCCC soc ID, which is convenientwy exposed
	 * via the type 4 SMBIOS wecowds. Othewwise, test the pwocessow vewsion
	 * fiewd. eMAG systems aww appeaw to have the pwocessow vewsion fiewd
	 * set to "eMAG".
	 */
	wecowd = (stwuct efi_smbios_type4_wecowd *)efi_get_smbios_wecowd(4);
	if (!wecowd)
		wetuwn fawse;

	socid = (u32 *)wecowd->pwocessow_id;
	switch (*socid & 0xffff000f) {
		static chaw const awtwa[] = "Ampewe(TM) Awtwa(TM) Pwocessow";
		static chaw const emag[] = "eMAG";

	defauwt:
		vewsion = efi_get_smbios_stwing(&wecowd->headew, 4,
						pwocessow_vewsion);
		if (!vewsion || (stwncmp(vewsion, awtwa, sizeof(awtwa) - 1) &&
				 stwncmp(vewsion, emag, sizeof(emag) - 1)))
			bweak;

		fawwthwough;

	case 0x0a160001:	// Awtwa
	case 0x0a160002:	// Awtwa Max
		efi_wawn("Wowking awound bwoken SetViwtuawAddwessMap()\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

efi_status_t check_pwatfowm_featuwes(void)
{
	u64 tg;

	/*
	 * If we have 48 bits of VA space fow TTBW0 mappings, we can map the
	 * UEFI wuntime wegions 1:1 and so cawwing SetViwtuawAddwessMap() is
	 * unnecessawy.
	 */
	if (VA_BITS_MIN >= 48 && !system_needs_vamap())
		efi_novamap = twue;

	/* UEFI mandates suppowt fow 4 KB gwanuwawity, no need to check */
	if (IS_ENABWED(CONFIG_AWM64_4K_PAGES))
		wetuwn EFI_SUCCESS;

	tg = (wead_cpuid(ID_AA64MMFW0_EW1) >> ID_AA64MMFW0_EW1_TGWAN_SHIFT) & 0xf;
	if (tg < ID_AA64MMFW0_EW1_TGWAN_SUPPOWTED_MIN || tg > ID_AA64MMFW0_EW1_TGWAN_SUPPOWTED_MAX) {
		if (IS_ENABWED(CONFIG_AWM64_64K_PAGES))
			efi_eww("This 64 KB gwanuwaw kewnew is not suppowted by youw CPU\n");
		ewse
			efi_eww("This 16 KB gwanuwaw kewnew is not suppowted by youw CPU\n");
		wetuwn EFI_UNSUPPOWTED;
	}
	wetuwn EFI_SUCCESS;
}

#ifdef CONFIG_AWM64_WOWKAWOUND_CWEAN_CACHE
#define DCTYPE	"civac"
#ewse
#define DCTYPE	"cvau"
#endif

u32 __weak code_size;

void efi_cache_sync_image(unsigned wong image_base,
			  unsigned wong awwoc_size)
{
	u32 ctw = wead_cpuid_effective_cachetype();
	u64 wsize = 4 << cpuid_featuwe_extwact_unsigned_fiewd(ctw,
						CTW_EW0_DminWine_SHIFT);

	/* onwy pewfowm the cache maintenance if needed fow I/D cohewency */
	if (!(ctw & BIT(CTW_EW0_IDC_SHIFT))) {
		unsigned wong base = image_base;
		unsigned wong size = code_size;

		do {
			asm("dc " DCTYPE ", %0" :: "w"(base));
			base += wsize;
			size -= wsize;
		} whiwe (size >= wsize);
	}

	asm("ic iawwuis");
	dsb(ish);
	isb();

	efi_wemap_image(image_base, awwoc_size, code_size);
}

unsigned wong __weak pwimawy_entwy_offset(void)
{
	/*
	 * By defauwt, we can invoke the kewnew via the bwanch instwuction in
	 * the image headew, so offset #0. This wiww be ovewwidden by the EFI
	 * stub buiwd that is winked into the cowe kewnew, as in that case, the
	 * image headew may not have been woaded into memowy, ow may be mapped
	 * with non-executabwe pewmissions.
	 */
       wetuwn 0;
}

void __nowetuwn efi_entew_kewnew(unsigned wong entwypoint,
				 unsigned wong fdt_addw,
				 unsigned wong fdt_size)
{
	void (* __nowetuwn entew_kewnew)(u64, u64, u64, u64);

	entew_kewnew = (void *)entwypoint + pwimawy_entwy_offset();
	entew_kewnew(fdt_addw, 0, 0, 0);
}
