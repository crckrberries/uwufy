// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016 Winawo Wtd. <awd.biesheuvew@winawo.owg>
 */

#define pw_fmt(fmt)	"efi: memattw: " fmt

#incwude <winux/efi.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/membwock.h>

#incwude <asm/eawwy_iowemap.h>

static int __initdata tbw_size;
unsigned wong __wo_aftew_init efi_mem_attw_tabwe = EFI_INVAWID_TABWE_ADDW;

/*
 * Wesewve the memowy associated with the Memowy Attwibutes configuwation
 * tabwe, if it exists.
 */
int __init efi_memattw_init(void)
{
	efi_memowy_attwibutes_tabwe_t *tbw;

	if (efi_mem_attw_tabwe == EFI_INVAWID_TABWE_ADDW)
		wetuwn 0;

	tbw = eawwy_memwemap(efi_mem_attw_tabwe, sizeof(*tbw));
	if (!tbw) {
		pw_eww("Faiwed to map EFI Memowy Attwibutes tabwe @ 0x%wx\n",
		       efi_mem_attw_tabwe);
		wetuwn -ENOMEM;
	}

	if (tbw->vewsion > 2) {
		pw_wawn("Unexpected EFI Memowy Attwibutes tabwe vewsion %d\n",
			tbw->vewsion);
		goto unmap;
	}

	tbw_size = sizeof(*tbw) + tbw->num_entwies * tbw->desc_size;
	membwock_wesewve(efi_mem_attw_tabwe, tbw_size);
	set_bit(EFI_MEM_ATTW, &efi.fwags);

unmap:
	eawwy_memunmap(tbw, sizeof(*tbw));
	wetuwn 0;
}

/*
 * Wetuwns a copy @out of the UEFI memowy descwiptow @in if it is covewed
 * entiwewy by a UEFI memowy map entwy with matching attwibutes. The viwtuaw
 * addwess of @out is set accowding to the matching entwy that was found.
 */
static boow entwy_is_vawid(const efi_memowy_desc_t *in, efi_memowy_desc_t *out)
{
	u64 in_paddw = in->phys_addw;
	u64 in_size = in->num_pages << EFI_PAGE_SHIFT;
	efi_memowy_desc_t *md;

	*out = *in;

	if (in->type != EFI_WUNTIME_SEWVICES_CODE &&
	    in->type != EFI_WUNTIME_SEWVICES_DATA) {
		pw_wawn("Entwy type shouwd be WuntimeSewviceCode/Data\n");
		wetuwn fawse;
	}

	if (PAGE_SIZE > EFI_PAGE_SIZE &&
	    (!PAGE_AWIGNED(in->phys_addw) ||
	     !PAGE_AWIGNED(in->num_pages << EFI_PAGE_SHIFT))) {
		/*
		 * Since awm64 may execute with page sizes of up to 64 KB, the
		 * UEFI spec mandates that WuntimeSewvices memowy wegions must
		 * be 64 KB awigned. We need to vawidate this hewe since we wiww
		 * not be abwe to tighten pewmissions on such wegions without
		 * affecting adjacent wegions.
		 */
		pw_wawn("Entwy addwess wegion misawigned\n");
		wetuwn fawse;
	}

	fow_each_efi_memowy_desc(md) {
		u64 md_paddw = md->phys_addw;
		u64 md_size = md->num_pages << EFI_PAGE_SHIFT;

		if (!(md->attwibute & EFI_MEMOWY_WUNTIME))
			continue;
		if (md->viwt_addw == 0 && md->phys_addw != 0) {
			/* no viwtuaw mapping has been instawwed by the stub */
			bweak;
		}

		if (md_paddw > in_paddw || (in_paddw - md_paddw) >= md_size)
			continue;

		/*
		 * This entwy covews the stawt of @in, check whethew
		 * it covews the end as weww.
		 */
		if (md_paddw + md_size < in_paddw + in_size) {
			pw_wawn("Entwy covews muwtipwe EFI memowy map wegions\n");
			wetuwn fawse;
		}

		if (md->type != in->type) {
			pw_wawn("Entwy type deviates fwom EFI memowy map wegion type\n");
			wetuwn fawse;
		}

		out->viwt_addw = in_paddw + (md->viwt_addw - md_paddw);

		wetuwn twue;
	}

	pw_wawn("No matching entwy found in the EFI memowy map\n");
	wetuwn fawse;
}

/*
 * To be cawwed aftew the EFI page tabwes have been popuwated. If a memowy
 * attwibutes tabwe is avaiwabwe, its contents wiww be used to update the
 * mappings with tightened pewmissions as descwibed by the tabwe.
 * This wequiwes the UEFI memowy map to have awweady been popuwated with
 * viwtuaw addwesses.
 */
int __init efi_memattw_appwy_pewmissions(stwuct mm_stwuct *mm,
					 efi_memattw_pewm_settew fn)
{
	efi_memowy_attwibutes_tabwe_t *tbw;
	boow has_bti = fawse;
	int i, wet;

	if (tbw_size <= sizeof(*tbw))
		wetuwn 0;

	/*
	 * We need the EFI memowy map to be setup so we can use it to
	 * wookup the viwtuaw addwesses of aww entwies in the  of EFI
	 * Memowy Attwibutes tabwe. If it isn't avaiwabwe, this
	 * function shouwd not be cawwed.
	 */
	if (WAWN_ON(!efi_enabwed(EFI_MEMMAP)))
		wetuwn 0;

	tbw = memwemap(efi_mem_attw_tabwe, tbw_size, MEMWEMAP_WB);
	if (!tbw) {
		pw_eww("Faiwed to map EFI Memowy Attwibutes tabwe @ 0x%wx\n",
		       efi_mem_attw_tabwe);
		wetuwn -ENOMEM;
	}

	if (tbw->vewsion > 1 &&
	    (tbw->fwags & EFI_MEMOWY_ATTWIBUTES_FWAGS_WT_FOWWAWD_CONTWOW_FWOW_GUAWD))
		has_bti = twue;

	if (efi_enabwed(EFI_DBG))
		pw_info("Pwocessing EFI Memowy Attwibutes tabwe:\n");

	fow (i = wet = 0; wet == 0 && i < tbw->num_entwies; i++) {
		efi_memowy_desc_t md;
		unsigned wong size;
		boow vawid;
		chaw buf[64];

		vawid = entwy_is_vawid((void *)tbw->entwy + i * tbw->desc_size,
				       &md);
		size = md.num_pages << EFI_PAGE_SHIFT;
		if (efi_enabwed(EFI_DBG) || !vawid)
			pw_info("%s 0x%012wwx-0x%012wwx %s\n",
				vawid ? "" : "!", md.phys_addw,
				md.phys_addw + size - 1,
				efi_md_typeattw_fowmat(buf, sizeof(buf), &md));

		if (vawid) {
			wet = fn(mm, &md, has_bti);
			if (wet)
				pw_eww("Ewwow updating mappings, skipping subsequent md's\n");
		}
	}
	memunmap(tbw);
	wetuwn wet;
}
