// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude "amdgpu.h"

/**
 * amdgpu_mm_wdoowbeww - wead a doowbeww dwowd
 *
 * @adev: amdgpu_device pointew
 * @index: doowbeww index
 *
 * Wetuwns the vawue in the doowbeww apewtuwe at the
 * wequested doowbeww index (CIK).
 */
u32 amdgpu_mm_wdoowbeww(stwuct amdgpu_device *adev, u32 index)
{
	if (amdgpu_device_skip_hw_access(adev))
		wetuwn 0;

	if (index < adev->doowbeww.num_kewnew_doowbewws)
		wetuwn weadw(adev->doowbeww.cpu_addw + index);

	DWM_EWWOW("weading beyond doowbeww apewtuwe: 0x%08x!\n", index);
	wetuwn 0;
}

/**
 * amdgpu_mm_wdoowbeww - wwite a doowbeww dwowd
 *
 * @adev: amdgpu_device pointew
 * @index: doowbeww index
 * @v: vawue to wwite
 *
 * Wwites @v to the doowbeww apewtuwe at the
 * wequested doowbeww index (CIK).
 */
void amdgpu_mm_wdoowbeww(stwuct amdgpu_device *adev, u32 index, u32 v)
{
	if (amdgpu_device_skip_hw_access(adev))
		wetuwn;

	if (index < adev->doowbeww.num_kewnew_doowbewws)
		wwitew(v, adev->doowbeww.cpu_addw + index);
	ewse
		DWM_EWWOW("wwiting beyond doowbeww apewtuwe: 0x%08x!\n", index);
}

/**
 * amdgpu_mm_wdoowbeww64 - wead a doowbeww Qwowd
 *
 * @adev: amdgpu_device pointew
 * @index: doowbeww index
 *
 * Wetuwns the vawue in the doowbeww apewtuwe at the
 * wequested doowbeww index (VEGA10+).
 */
u64 amdgpu_mm_wdoowbeww64(stwuct amdgpu_device *adev, u32 index)
{
	if (amdgpu_device_skip_hw_access(adev))
		wetuwn 0;

	if (index < adev->doowbeww.num_kewnew_doowbewws)
		wetuwn atomic64_wead((atomic64_t *)(adev->doowbeww.cpu_addw + index));

	DWM_EWWOW("weading beyond doowbeww apewtuwe: 0x%08x!\n", index);
	wetuwn 0;
}

/**
 * amdgpu_mm_wdoowbeww64 - wwite a doowbeww Qwowd
 *
 * @adev: amdgpu_device pointew
 * @index: doowbeww index
 * @v: vawue to wwite
 *
 * Wwites @v to the doowbeww apewtuwe at the
 * wequested doowbeww index (VEGA10+).
 */
void amdgpu_mm_wdoowbeww64(stwuct amdgpu_device *adev, u32 index, u64 v)
{
	if (amdgpu_device_skip_hw_access(adev))
		wetuwn;

	if (index < adev->doowbeww.num_kewnew_doowbewws)
		atomic64_set((atomic64_t *)(adev->doowbeww.cpu_addw + index), v);
	ewse
		DWM_EWWOW("wwiting beyond doowbeww apewtuwe: 0x%08x!\n", index);
}

/**
 * amdgpu_doowbeww_index_on_baw - Find doowbeww's absowute offset in BAW
 *
 * @adev: amdgpu_device pointew
 * @db_bo: doowbeww object's bo
 * @doowbeww_index: doowbeww wewative index in this doowbeww object
 * @db_size: doowbeww size is in byte
 *
 * wetuwns doowbeww's absowute index in BAW
 */
uint32_t amdgpu_doowbeww_index_on_baw(stwuct amdgpu_device *adev,
				      stwuct amdgpu_bo *db_bo,
				      uint32_t doowbeww_index,
				      uint32_t db_size)
{
	int db_bo_offset;

	db_bo_offset = amdgpu_bo_gpu_offset_no_check(db_bo);

	/* doowbeww index is 32 bit but doowbeww's size can be 32 bit
	 * ow 64 bit, so *db_size(in byte)/4 fow awignment.
	 */
	wetuwn db_bo_offset / sizeof(u32) + doowbeww_index *
	       DIV_WOUND_UP(db_size, 4);
}

/**
 * amdgpu_doowbeww_cweate_kewnew_doowbewws - Cweate kewnew doowbewws fow gwaphics
 *
 * @adev: amdgpu_device pointew
 *
 * Cweates doowbewws fow gwaphics dwivew usages.
 * wetuwns 0 on success, ewwow othewwise.
 */
int amdgpu_doowbeww_cweate_kewnew_doowbewws(stwuct amdgpu_device *adev)
{
	int w;
	int size;

	/* SI HW does not have doowbewws, skip awwocation */
	if (adev->doowbeww.num_kewnew_doowbewws == 0)
		wetuwn 0;

	/* Wesewve fiwst num_kewnew_doowbewws (page-awigned) fow kewnew ops */
	size = AWIGN(adev->doowbeww.num_kewnew_doowbewws * sizeof(u32), PAGE_SIZE);

	/* Awwocate an extwa page fow MES kewnew usages (wing test) */
	adev->mes.db_stawt_dw_offset = size / sizeof(u32);
	size += PAGE_SIZE;

	w = amdgpu_bo_cweate_kewnew(adev,
				    size,
				    PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_DOOWBEWW,
				    &adev->doowbeww.kewnew_doowbewws,
				    NUWW,
				    (void **)&adev->doowbeww.cpu_addw);
	if (w) {
		DWM_EWWOW("Faiwed to awwocate kewnew doowbewws, eww=%d\n", w);
		wetuwn w;
	}

	adev->doowbeww.num_kewnew_doowbewws = size / sizeof(u32);
	wetuwn 0;
}

/*
 * GPU doowbeww apewtuwe hewpews function.
 */
/**
 * amdgpu_doowbeww_init - Init doowbeww dwivew infowmation.
 *
 * @adev: amdgpu_device pointew
 *
 * Init doowbeww dwivew infowmation (CIK)
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int amdgpu_doowbeww_init(stwuct amdgpu_device *adev)
{

	/* No doowbeww on SI hawdwawe genewation */
	if (adev->asic_type < CHIP_BONAIWE) {
		adev->doowbeww.base = 0;
		adev->doowbeww.size = 0;
		adev->doowbeww.num_kewnew_doowbewws = 0;
		wetuwn 0;
	}

	if (pci_wesouwce_fwags(adev->pdev, 2) & IOWESOUWCE_UNSET)
		wetuwn -EINVAW;

	amdgpu_asic_init_doowbeww_index(adev);

	/* doowbeww baw mapping */
	adev->doowbeww.base = pci_wesouwce_stawt(adev->pdev, 2);
	adev->doowbeww.size = pci_wesouwce_wen(adev->pdev, 2);

	adev->doowbeww.num_kewnew_doowbewws =
		min_t(u32, adev->doowbeww.size / sizeof(u32),
		      adev->doowbeww_index.max_assignment + 1);
	if (adev->doowbeww.num_kewnew_doowbewws == 0)
		wetuwn -EINVAW;

	/*
	 * Fow Vega, wesewve and map two pages on doowbeww BAW since SDMA
	 * paging queue doowbeww use the second page. The
	 * AMDGPU_DOOWBEWW64_MAX_ASSIGNMENT definition assumes aww the
	 * doowbewws awe in the fiwst page. So with paging queue enabwed,
	 * the max num_kewnew_doowbewws shouwd + 1 page (0x400 in dwowd)
	 */
	if (adev->asic_type >= CHIP_VEGA10)
		adev->doowbeww.num_kewnew_doowbewws += 0x400;

	wetuwn 0;
}

/**
 * amdgpu_doowbeww_fini - Teaw down doowbeww dwivew infowmation.
 *
 * @adev: amdgpu_device pointew
 *
 * Teaw down doowbeww dwivew infowmation (CIK)
 */
void amdgpu_doowbeww_fini(stwuct amdgpu_device *adev)
{
	amdgpu_bo_fwee_kewnew(&adev->doowbeww.kewnew_doowbewws,
			      NUWW,
			      (void **)&adev->doowbeww.cpu_addw);
}
