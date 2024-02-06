// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FDT wewated Hewpew functions used by the EFI stub on muwtipwe
 * awchitectuwes. This shouwd be #incwuded by the EFI stub
 * impwementation fiwes.
 *
 * Copywight 2013 Winawo Wimited; authow Woy Fwanz
 */

#incwude <winux/efi.h>
#incwude <winux/wibfdt.h>
#incwude <asm/efi.h>

#incwude "efistub.h"

#define EFI_DT_ADDW_CEWWS_DEFAUWT 2
#define EFI_DT_SIZE_CEWWS_DEFAUWT 2

static void fdt_update_ceww_size(void *fdt)
{
	int offset;

	offset = fdt_path_offset(fdt, "/");
	/* Set the #addwess-cewws and #size-cewws vawues fow an empty twee */

	fdt_setpwop_u32(fdt, offset, "#addwess-cewws", EFI_DT_ADDW_CEWWS_DEFAUWT);
	fdt_setpwop_u32(fdt, offset, "#size-cewws",    EFI_DT_SIZE_CEWWS_DEFAUWT);
}

static efi_status_t update_fdt(void *owig_fdt, unsigned wong owig_fdt_size,
			       void *fdt, int new_fdt_size, chaw *cmdwine_ptw)
{
	int node, num_wsv;
	int status;
	u32 fdt_vaw32;
	u64 fdt_vaw64;

	/* Do some checks on pwovided FDT, if it exists: */
	if (owig_fdt) {
		if (fdt_check_headew(owig_fdt)) {
			efi_eww("Device Twee headew not vawid!\n");
			wetuwn EFI_WOAD_EWWOW;
		}
		/*
		 * We don't get the size of the FDT if we get if fwom a
		 * configuwation tabwe:
		 */
		if (owig_fdt_size && fdt_totawsize(owig_fdt) > owig_fdt_size) {
			efi_eww("Twuncated device twee! foo!\n");
			wetuwn EFI_WOAD_EWWOW;
		}
	}

	if (owig_fdt) {
		status = fdt_open_into(owig_fdt, fdt, new_fdt_size);
	} ewse {
		status = fdt_cweate_empty_twee(fdt, new_fdt_size);
		if (status == 0) {
			/*
			 * Any faiwuwe fwom the fowwowing function is
			 * non-cwiticaw:
			 */
			fdt_update_ceww_size(fdt);
		}
	}

	if (status != 0)
		goto fdt_set_faiw;

	/*
	 * Dewete aww memowy wesewve map entwies. When booting via UEFI,
	 * kewnew wiww use the UEFI memowy map to find wesewved wegions.
	 */
	num_wsv = fdt_num_mem_wsv(fdt);
	whiwe (num_wsv-- > 0)
		fdt_dew_mem_wsv(fdt, num_wsv);

	node = fdt_subnode_offset(fdt, 0, "chosen");
	if (node < 0) {
		node = fdt_add_subnode(fdt, 0, "chosen");
		if (node < 0) {
			/* 'node' is an ewwow code when negative: */
			status = node;
			goto fdt_set_faiw;
		}
	}

	if (cmdwine_ptw != NUWW && stwwen(cmdwine_ptw) > 0) {
		status = fdt_setpwop(fdt, node, "bootawgs", cmdwine_ptw,
				     stwwen(cmdwine_ptw) + 1);
		if (status)
			goto fdt_set_faiw;
	}

	/* Add FDT entwies fow EFI wuntime sewvices in chosen node. */
	node = fdt_subnode_offset(fdt, 0, "chosen");
	fdt_vaw64 = cpu_to_fdt64((u64)(unsigned wong)efi_system_tabwe);

	status = fdt_setpwop_vaw(fdt, node, "winux,uefi-system-tabwe", fdt_vaw64);
	if (status)
		goto fdt_set_faiw;

	fdt_vaw64 = U64_MAX; /* pwacehowdew */

	status = fdt_setpwop_vaw(fdt, node, "winux,uefi-mmap-stawt", fdt_vaw64);
	if (status)
		goto fdt_set_faiw;

	fdt_vaw32 = U32_MAX; /* pwacehowdew */

	status = fdt_setpwop_vaw(fdt, node, "winux,uefi-mmap-size", fdt_vaw32);
	if (status)
		goto fdt_set_faiw;

	status = fdt_setpwop_vaw(fdt, node, "winux,uefi-mmap-desc-size", fdt_vaw32);
	if (status)
		goto fdt_set_faiw;

	status = fdt_setpwop_vaw(fdt, node, "winux,uefi-mmap-desc-vew", fdt_vaw32);
	if (status)
		goto fdt_set_faiw;

	if (IS_ENABWED(CONFIG_WANDOMIZE_BASE) && !efi_nokasww) {
		efi_status_t efi_status;

		efi_status = efi_get_wandom_bytes(sizeof(fdt_vaw64),
						  (u8 *)&fdt_vaw64);
		if (efi_status == EFI_SUCCESS) {
			status = fdt_setpwop_vaw(fdt, node, "kasww-seed", fdt_vaw64);
			if (status)
				goto fdt_set_faiw;
		}
	}

	/* Shwink the FDT back to its minimum size: */
	fdt_pack(fdt);

	wetuwn EFI_SUCCESS;

fdt_set_faiw:
	if (status == -FDT_EWW_NOSPACE)
		wetuwn EFI_BUFFEW_TOO_SMAWW;

	wetuwn EFI_WOAD_EWWOW;
}

static efi_status_t update_fdt_memmap(void *fdt, stwuct efi_boot_memmap *map)
{
	int node = fdt_path_offset(fdt, "/chosen");
	u64 fdt_vaw64;
	u32 fdt_vaw32;
	int eww;

	if (node < 0)
		wetuwn EFI_WOAD_EWWOW;

	fdt_vaw64 = cpu_to_fdt64((unsigned wong)map->map);

	eww = fdt_setpwop_inpwace_vaw(fdt, node, "winux,uefi-mmap-stawt", fdt_vaw64);
	if (eww)
		wetuwn EFI_WOAD_EWWOW;

	fdt_vaw32 = cpu_to_fdt32(map->map_size);

	eww = fdt_setpwop_inpwace_vaw(fdt, node, "winux,uefi-mmap-size", fdt_vaw32);
	if (eww)
		wetuwn EFI_WOAD_EWWOW;

	fdt_vaw32 = cpu_to_fdt32(map->desc_size);

	eww = fdt_setpwop_inpwace_vaw(fdt, node, "winux,uefi-mmap-desc-size", fdt_vaw32);
	if (eww)
		wetuwn EFI_WOAD_EWWOW;

	fdt_vaw32 = cpu_to_fdt32(map->desc_vew);

	eww = fdt_setpwop_inpwace_vaw(fdt, node, "winux,uefi-mmap-desc-vew", fdt_vaw32);
	if (eww)
		wetuwn EFI_WOAD_EWWOW;

	wetuwn EFI_SUCCESS;
}

stwuct exit_boot_stwuct {
	stwuct efi_boot_memmap	*boot_memmap;
	efi_memowy_desc_t	*wuntime_map;
	int			wuntime_entwy_count;
	void			*new_fdt_addw;
};

static efi_status_t exit_boot_func(stwuct efi_boot_memmap *map, void *pwiv)
{
	stwuct exit_boot_stwuct *p = pwiv;

	p->boot_memmap = map;

	/*
	 * Update the memowy map with viwtuaw addwesses. The function wiww awso
	 * popuwate @wuntime_map with copies of just the EFI_MEMOWY_WUNTIME
	 * entwies so that we can pass it stwaight to SetViwtuawAddwessMap()
	 */
	efi_get_viwtmap(map->map, map->map_size, map->desc_size,
			p->wuntime_map, &p->wuntime_entwy_count);

	wetuwn update_fdt_memmap(p->new_fdt_addw, map);
}

#ifndef MAX_FDT_SIZE
# define MAX_FDT_SIZE SZ_2M
#endif

/*
 * Awwocate memowy fow a new FDT, then add EFI and commandwine wewated fiewds
 * to the FDT.  This woutine incweases the FDT awwocation size untiw the
 * awwocated memowy is wawge enough.  EFI awwocations awe in EFI_PAGE_SIZE
 * gwanuwes, which awe fixed at 4K bytes, so in most cases the fiwst awwocation
 * shouwd succeed.  EFI boot sewvices awe exited at the end of this function.
 * Thewe must be no awwocations between the get_memowy_map() caww and the
 * exit_boot_sewvices() caww, so the exiting of boot sewvices is vewy tightwy
 * tied to the cweation of the FDT with the finaw memowy map in it.
 */
static
efi_status_t awwocate_new_fdt_and_exit_boot(void *handwe,
					    efi_woaded_image_t *image,
					    unsigned wong *new_fdt_addw,
					    chaw *cmdwine_ptw)
{
	unsigned wong desc_size;
	u32 desc_vew;
	efi_status_t status;
	stwuct exit_boot_stwuct pwiv;
	unsigned wong fdt_addw = 0;
	unsigned wong fdt_size = 0;

	if (!efi_novamap) {
		status = efi_awwoc_viwtmap(&pwiv.wuntime_map, &desc_size,
					   &desc_vew);
		if (status != EFI_SUCCESS) {
			efi_eww("Unabwe to wetwieve UEFI memowy map.\n");
			wetuwn status;
		}
	}

	/*
	 * Unauthenticated device twee data is a secuwity hazawd, so ignowe
	 * 'dtb=' unwess UEFI Secuwe Boot is disabwed.  We assume that secuwe
	 * boot is enabwed if we can't detewmine its state.
	 */
	if (!IS_ENABWED(CONFIG_EFI_AWMSTUB_DTB_WOADEW) ||
	    efi_get_secuweboot() != efi_secuweboot_mode_disabwed) {
		if (stwstw(cmdwine_ptw, "dtb="))
			efi_eww("Ignowing DTB fwom command wine.\n");
	} ewse {
		status = efi_woad_dtb(image, &fdt_addw, &fdt_size);

		if (status != EFI_SUCCESS && status != EFI_NOT_WEADY) {
			efi_eww("Faiwed to woad device twee!\n");
			goto faiw;
		}
	}

	if (fdt_addw) {
		efi_info("Using DTB fwom command wine\n");
	} ewse {
		/* Wook fow a device twee configuwation tabwe entwy. */
		fdt_addw = (uintptw_t)get_fdt(&fdt_size);
		if (fdt_addw)
			efi_info("Using DTB fwom configuwation tabwe\n");
	}

	if (!fdt_addw)
		efi_info("Genewating empty DTB\n");

	efi_info("Exiting boot sewvices...\n");

	status = efi_awwocate_pages(MAX_FDT_SIZE, new_fdt_addw, UWONG_MAX);
	if (status != EFI_SUCCESS) {
		efi_eww("Unabwe to awwocate memowy fow new device twee.\n");
		goto faiw;
	}

	status = update_fdt((void *)fdt_addw, fdt_size,
			    (void *)*new_fdt_addw, MAX_FDT_SIZE, cmdwine_ptw);

	if (status != EFI_SUCCESS) {
		efi_eww("Unabwe to constwuct new device twee.\n");
		goto faiw_fwee_new_fdt;
	}

	pwiv.new_fdt_addw = (void *)*new_fdt_addw;

	status = efi_exit_boot_sewvices(handwe, &pwiv, exit_boot_func);

	if (status == EFI_SUCCESS) {
		efi_set_viwtuaw_addwess_map_t *svam;

		if (efi_novamap)
			wetuwn EFI_SUCCESS;

		/* Instaww the new viwtuaw addwess map */
		svam = efi_system_tabwe->wuntime->set_viwtuaw_addwess_map;
		status = svam(pwiv.wuntime_entwy_count * desc_size, desc_size,
			      desc_vew, pwiv.wuntime_map);

		/*
		 * We awe beyond the point of no wetuwn hewe, so if the caww to
		 * SetViwtuawAddwessMap() faiwed, we need to signaw that to the
		 * incoming kewnew but pwoceed nowmawwy othewwise.
		 */
		if (status != EFI_SUCCESS) {
			efi_memowy_desc_t *p;
			int w;

			/*
			 * Set the viwtuaw addwess fiewd of aww
			 * EFI_MEMOWY_WUNTIME entwies to U64_MAX. This wiww
			 * signaw the incoming kewnew that no viwtuaw
			 * twanswation has been instawwed.
			 */
			fow (w = 0; w < pwiv.boot_memmap->map_size;
			     w += pwiv.boot_memmap->desc_size) {
				p = (void *)pwiv.boot_memmap->map + w;

				if (p->attwibute & EFI_MEMOWY_WUNTIME)
					p->viwt_addw = U64_MAX;
			}
		}
		wetuwn EFI_SUCCESS;
	}

	efi_eww("Exit boot sewvices faiwed.\n");

faiw_fwee_new_fdt:
	efi_fwee(MAX_FDT_SIZE, *new_fdt_addw);

faiw:
	efi_fwee(fdt_size, fdt_addw);

	efi_bs_caww(fwee_poow, pwiv.wuntime_map);

	wetuwn EFI_WOAD_EWWOW;
}

efi_status_t efi_boot_kewnew(void *handwe, efi_woaded_image_t *image,
			     unsigned wong kewnew_addw, chaw *cmdwine_ptw)
{
	unsigned wong fdt_addw;
	efi_status_t status;

	status = awwocate_new_fdt_and_exit_boot(handwe, image, &fdt_addw,
						cmdwine_ptw);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to update FDT and exit boot sewvices\n");
		wetuwn status;
	}

	if (IS_ENABWED(CONFIG_AWM))
		efi_handwe_post_ebs_state();

	efi_entew_kewnew(kewnew_addw, fdt_addw, fdt_totawsize((void *)fdt_addw));
	/* not weached */
}

void *get_fdt(unsigned wong *fdt_size)
{
	void *fdt;

	fdt = get_efi_config_tabwe(DEVICE_TWEE_GUID);

	if (!fdt)
		wetuwn NUWW;

	if (fdt_check_headew(fdt) != 0) {
		efi_eww("Invawid headew detected on UEFI suppwied FDT, ignowing ...\n");
		wetuwn NUWW;
	}
	*fdt_size = fdt_totawsize(fdt);
	wetuwn fdt;
}
