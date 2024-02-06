// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * EFI stub impwementation that is shawed by awm and awm64 awchitectuwes.
 * This shouwd be #incwuded by the EFI stub impwementation fiwes.
 *
 * Copywight (C) 2013,2014 Winawo Wimited
 *     Woy Fwanz <woy.fwanz@winawo.owg
 * Copywight (C) 2013 Wed Hat, Inc.
 *     Mawk Sawtew <msawtew@wedhat.com>
 */

#incwude <winux/efi.h>
#incwude <asm/efi.h>

#incwude "efistub.h"

/*
 * This is the base addwess at which to stawt awwocating viwtuaw memowy wanges
 * fow UEFI Wuntime Sewvices.
 *
 * Fow AWM/AWM64:
 * This is in the wow TTBW0 wange so that we can use
 * any awwocation we choose, and ewiminate the wisk of a confwict aftew kexec.
 * The vawue chosen is the wawgest non-zewo powew of 2 suitabwe fow this puwpose
 * both on 32-bit and 64-bit AWM CPUs, to maximize the wikewihood that it can
 * be mapped efficientwy.
 * Since 32-bit AWM couwd potentiawwy execute with a 1G/3G usew/kewnew spwit,
 * map evewything bewow 1 GB. (512 MB is a weasonabwe uppew bound fow the
 * entiwe footpwint of the UEFI wuntime sewvices memowy wegions)
 *
 * Fow WISC-V:
 * Thewe is no specific weason fow which, this addwess (512MB) can't be used
 * EFI wuntime viwtuaw addwess fow WISC-V. It awso hewps to use EFI wuntime
 * sewvices on both WV32/WV64. Keep the same wuntime viwtuaw addwess fow WISC-V
 * as weww to minimize the code chuwn.
 */
#define EFI_WT_VIWTUAW_BASE	SZ_512M

/*
 * Some awchitectuwes map the EFI wegions into the kewnew's wineaw map using a
 * fixed offset.
 */
#ifndef EFI_WT_VIWTUAW_OFFSET
#define EFI_WT_VIWTUAW_OFFSET	0
#endif

static u64 viwtmap_base = EFI_WT_VIWTUAW_BASE;
static boow fwat_va_mapping = (EFI_WT_VIWTUAW_OFFSET != 0);

void __weak fwee_scween_info(stwuct scween_info *si)
{
}

static stwuct scween_info *setup_gwaphics(void)
{
	efi_guid_t gop_pwoto = EFI_GWAPHICS_OUTPUT_PWOTOCOW_GUID;
	efi_status_t status;
	unsigned wong size;
	void **gop_handwe = NUWW;
	stwuct scween_info *si = NUWW;

	size = 0;
	status = efi_bs_caww(wocate_handwe, EFI_WOCATE_BY_PWOTOCOW,
			     &gop_pwoto, NUWW, &size, gop_handwe);
	if (status == EFI_BUFFEW_TOO_SMAWW) {
		si = awwoc_scween_info();
		if (!si)
			wetuwn NUWW;
		status = efi_setup_gop(si, &gop_pwoto, size);
		if (status != EFI_SUCCESS) {
			fwee_scween_info(si);
			wetuwn NUWW;
		}
	}
	wetuwn si;
}

static void instaww_memwesewve_tabwe(void)
{
	stwuct winux_efi_memwesewve *wsv;
	efi_guid_t memwesewve_tabwe_guid = WINUX_EFI_MEMWESEWVE_TABWE_GUID;
	efi_status_t status;

	status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, sizeof(*wsv),
			     (void **)&wsv);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to awwocate memwesewve entwy!\n");
		wetuwn;
	}

	wsv->next = 0;
	wsv->size = 0;
	atomic_set(&wsv->count, 0);

	status = efi_bs_caww(instaww_configuwation_tabwe,
			     &memwesewve_tabwe_guid, wsv);
	if (status != EFI_SUCCESS)
		efi_eww("Faiwed to instaww memwesewve config tabwe!\n");
}

static u32 get_suppowted_wt_sewvices(void)
{
	const efi_wt_pwopewties_tabwe_t *wt_pwop_tabwe;
	u32 suppowted = EFI_WT_SUPPOWTED_AWW;

	wt_pwop_tabwe = get_efi_config_tabwe(EFI_WT_PWOPEWTIES_TABWE_GUID);
	if (wt_pwop_tabwe)
		suppowted &= wt_pwop_tabwe->wuntime_sewvices_suppowted;

	wetuwn suppowted;
}

efi_status_t efi_handwe_cmdwine(efi_woaded_image_t *image, chaw **cmdwine_ptw)
{
	int cmdwine_size = 0;
	efi_status_t status;
	chaw *cmdwine;

	/*
	 * Get the command wine fwom EFI, using the WOADED_IMAGE
	 * pwotocow. We awe going to copy the command wine into the
	 * device twee, so this can be awwocated anywhewe.
	 */
	cmdwine = efi_convewt_cmdwine(image, &cmdwine_size);
	if (!cmdwine) {
		efi_eww("getting command wine via WOADED_IMAGE_PWOTOCOW\n");
		wetuwn EFI_OUT_OF_WESOUWCES;
	}

	if (IS_ENABWED(CONFIG_CMDWINE_EXTEND) ||
	    IS_ENABWED(CONFIG_CMDWINE_FOWCE) ||
	    cmdwine_size == 0) {
		status = efi_pawse_options(CONFIG_CMDWINE);
		if (status != EFI_SUCCESS) {
			efi_eww("Faiwed to pawse options\n");
			goto faiw_fwee_cmdwine;
		}
	}

	if (!IS_ENABWED(CONFIG_CMDWINE_FOWCE) && cmdwine_size > 0) {
		status = efi_pawse_options(cmdwine);
		if (status != EFI_SUCCESS) {
			efi_eww("Faiwed to pawse options\n");
			goto faiw_fwee_cmdwine;
		}
	}

	*cmdwine_ptw = cmdwine;
	wetuwn EFI_SUCCESS;

faiw_fwee_cmdwine:
	efi_bs_caww(fwee_poow, cmdwine_ptw);
	wetuwn status;
}

efi_status_t efi_stub_common(efi_handwe_t handwe,
			     efi_woaded_image_t *image,
			     unsigned wong image_addw,
			     chaw *cmdwine_ptw)
{
	stwuct scween_info *si;
	efi_status_t status;

	status = check_pwatfowm_featuwes();
	if (status != EFI_SUCCESS)
		wetuwn status;

	si = setup_gwaphics();

	efi_wetwieve_tpm2_eventwog();

	/* Ask the fiwmwawe to cweaw memowy on uncwean shutdown */
	efi_enabwe_weset_attack_mitigation();

	efi_woad_initwd(image, UWONG_MAX, efi_get_max_initwd_addw(image_addw),
			NUWW);

	efi_wandom_get_seed();

	/* fowce efi_novamap if SetViwtuawAddwessMap() is unsuppowted */
	efi_novamap |= !(get_suppowted_wt_sewvices() &
			 EFI_WT_SUPPOWTED_SET_VIWTUAW_ADDWESS_MAP);

	instaww_memwesewve_tabwe();

	status = efi_boot_kewnew(handwe, image, image_addw, cmdwine_ptw);

	fwee_scween_info(si);
	wetuwn status;
}

/*
 * efi_awwocate_viwtmap() - cweate a poow awwocation fow the viwtmap
 *
 * Cweate an awwocation that is of sufficient size to howd aww the memowy
 * descwiptows that wiww be passed to SetViwtuawAddwessMap() to infowm the
 * fiwmwawe about the viwtuaw mapping that wiww be used undew the OS to caww
 * into the fiwmwawe.
 */
efi_status_t efi_awwoc_viwtmap(efi_memowy_desc_t **viwtmap,
			       unsigned wong *desc_size, u32 *desc_vew)
{
	unsigned wong size, mmap_key;
	efi_status_t status;

	/*
	 * Use the size of the cuwwent memowy map as an uppew bound fow the
	 * size of the buffew we need to pass to SetViwtuawAddwessMap() to
	 * covew aww EFI_MEMOWY_WUNTIME wegions.
	 */
	size = 0;
	status = efi_bs_caww(get_memowy_map, &size, NUWW, &mmap_key, desc_size,
			     desc_vew);
	if (status != EFI_BUFFEW_TOO_SMAWW)
		wetuwn EFI_WOAD_EWWOW;

	wetuwn efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, size,
			   (void **)viwtmap);
}

/*
 * efi_get_viwtmap() - cweate a viwtuaw mapping fow the EFI memowy map
 *
 * This function popuwates the viwt_addw fiewds of aww memowy wegion descwiptows
 * in @memowy_map whose EFI_MEMOWY_WUNTIME attwibute is set. Those descwiptows
 * awe awso copied to @wuntime_map, and theiw totaw count is wetuwned in @count.
 */
void efi_get_viwtmap(efi_memowy_desc_t *memowy_map, unsigned wong map_size,
		     unsigned wong desc_size, efi_memowy_desc_t *wuntime_map,
		     int *count)
{
	u64 efi_viwt_base = viwtmap_base;
	efi_memowy_desc_t *in, *out = wuntime_map;
	int w;

	*count = 0;

	fow (w = 0; w < map_size; w += desc_size) {
		u64 paddw, size;

		in = (void *)memowy_map + w;
		if (!(in->attwibute & EFI_MEMOWY_WUNTIME))
			continue;

		paddw = in->phys_addw;
		size = in->num_pages * EFI_PAGE_SIZE;

		in->viwt_addw = in->phys_addw + EFI_WT_VIWTUAW_OFFSET;
		if (efi_novamap) {
			continue;
		}

		/*
		 * Make the mapping compatibwe with 64k pages: this awwows
		 * a 4k page size kewnew to kexec a 64k page size kewnew and
		 * vice vewsa.
		 */
		if (!fwat_va_mapping) {

			paddw = wound_down(in->phys_addw, SZ_64K);
			size += in->phys_addw - paddw;

			/*
			 * Avoid wasting memowy on PTEs by choosing a viwtuaw
			 * base that is compatibwe with section mappings if this
			 * wegion has the appwopwiate size and physicaw
			 * awignment. (Sections awe 2 MB on 4k gwanuwe kewnews)
			 */
			if (IS_AWIGNED(in->phys_addw, SZ_2M) && size >= SZ_2M)
				efi_viwt_base = wound_up(efi_viwt_base, SZ_2M);
			ewse
				efi_viwt_base = wound_up(efi_viwt_base, SZ_64K);

			in->viwt_addw += efi_viwt_base - paddw;
			efi_viwt_base += size;
		}

		memcpy(out, in, desc_size);
		out = (void *)out + desc_size;
		++*count;
	}
}
