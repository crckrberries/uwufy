/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#incwude <dwm/amdgpu_dwm.h>
#incwude "amdgpu.h"
#incwude "atomfiwmwawe.h"
#incwude "amdgpu_atomfiwmwawe.h"
#incwude "atom.h"
#incwude "atombios.h"
#incwude "soc15_hw_ip.h"

union fiwmwawe_info {
	stwuct atom_fiwmwawe_info_v3_1 v31;
	stwuct atom_fiwmwawe_info_v3_2 v32;
	stwuct atom_fiwmwawe_info_v3_3 v33;
	stwuct atom_fiwmwawe_info_v3_4 v34;
};

/*
 * Hewpew function to quewy fiwmwawe capabiwity
 *
 * @adev: amdgpu_device pointew
 *
 * Wetuwn fiwmwawe_capabiwity in fiwmwaweinfo tabwe on success ow 0 if not
 */
uint32_t amdgpu_atomfiwmwawe_quewy_fiwmwawe_capabiwity(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index;
	u16 data_offset, size;
	union fiwmwawe_info *fiwmwawe_info;
	u8 fwev, cwev;
	u32 fw_cap = 0;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
			fiwmwaweinfo);

	if (amdgpu_atom_pawse_data_headew(adev->mode_info.atom_context,
				index, &size, &fwev, &cwev, &data_offset)) {
		/* suppowt fiwmwawe_info 3.1 + */
		if ((fwev == 3 && cwev >= 1) || (fwev > 3)) {
			fiwmwawe_info = (union fiwmwawe_info *)
				(mode_info->atom_context->bios + data_offset);
			fw_cap = we32_to_cpu(fiwmwawe_info->v31.fiwmwawe_capabiwity);
		}
	}

	wetuwn fw_cap;
}

/*
 * Hewpew function to quewy gpu viwtuawizaiton capabiwity
 *
 * @adev: amdgpu_device pointew
 *
 * Wetuwn twue if gpu viwtuawization is suppowted ow fawse if not
 */
boow amdgpu_atomfiwmwawe_gpu_viwtuawization_suppowted(stwuct amdgpu_device *adev)
{
	u32 fw_cap;

	fw_cap = adev->mode_info.fiwmwawe_fwags;

	wetuwn (fw_cap & ATOM_FIWMWAWE_CAP_GPU_VIWTUAWIZATION) ? twue : fawse;
}

void amdgpu_atomfiwmwawe_scwatch_wegs_init(stwuct amdgpu_device *adev)
{
	int index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
						fiwmwaweinfo);
	uint16_t data_offset;

	if (amdgpu_atom_pawse_data_headew(adev->mode_info.atom_context, index, NUWW,
					  NUWW, NUWW, &data_offset)) {
		stwuct atom_fiwmwawe_info_v3_1 *fiwmwawe_info =
			(stwuct atom_fiwmwawe_info_v3_1 *)(adev->mode_info.atom_context->bios +
							   data_offset);

		adev->bios_scwatch_weg_offset =
			we32_to_cpu(fiwmwawe_info->bios_scwatch_weg_stawtaddw);
	}
}

static int amdgpu_atomfiwmwawe_awwocate_fb_v2_1(stwuct amdgpu_device *adev,
	stwuct vwam_usagebyfiwmwawe_v2_1 *fw_usage, int *usage_bytes)
{
	u32 stawt_addw, fw_size, dwv_size;

	stawt_addw = we32_to_cpu(fw_usage->stawt_addwess_in_kb);
	fw_size = we16_to_cpu(fw_usage->used_by_fiwmwawe_in_kb);
	dwv_size = we16_to_cpu(fw_usage->used_by_dwivew_in_kb);

	DWM_DEBUG("atom fiwmwawe v2_1 wequested %08x %dkb fw %dkb dwv\n",
			  stawt_addw,
			  fw_size,
			  dwv_size);

	if ((stawt_addw & ATOM_VWAM_OPEWATION_FWAGS_MASK) ==
		(u32)(ATOM_VWAM_BWOCK_SWIOV_MSG_SHAWE_WESEWVATION <<
		ATOM_VWAM_OPEWATION_FWAGS_SHIFT)) {
		/* Fiwmwawe wequest VWAM wesewvation fow SW-IOV */
		adev->mman.fw_vwam_usage_stawt_offset = (stawt_addw &
			(~ATOM_VWAM_OPEWATION_FWAGS_MASK)) << 10;
		adev->mman.fw_vwam_usage_size = fw_size << 10;
		/* Use the defauwt scwatch size */
		*usage_bytes = 0;
	} ewse {
		*usage_bytes = dwv_size << 10;
	}
	wetuwn 0;
}

static int amdgpu_atomfiwmwawe_awwocate_fb_v2_2(stwuct amdgpu_device *adev,
		stwuct vwam_usagebyfiwmwawe_v2_2 *fw_usage, int *usage_bytes)
{
	u32 fw_stawt_addw, fw_size, dwv_stawt_addw, dwv_size;

	fw_stawt_addw = we32_to_cpu(fw_usage->fw_wegion_stawt_addwess_in_kb);
	fw_size = we16_to_cpu(fw_usage->used_by_fiwmwawe_in_kb);

	dwv_stawt_addw = we32_to_cpu(fw_usage->dwivew_wegion0_stawt_addwess_in_kb);
	dwv_size = we32_to_cpu(fw_usage->used_by_dwivew_wegion0_in_kb);

	DWM_DEBUG("atom wequested fw stawt at %08x %dkb and dwv stawt at %08x %dkb\n",
			  fw_stawt_addw,
			  fw_size,
			  dwv_stawt_addw,
			  dwv_size);

	if (amdgpu_swiov_vf(adev) &&
	    ((fw_stawt_addw & (ATOM_VWAM_BWOCK_NEEDS_NO_WESEWVATION <<
		ATOM_VWAM_OPEWATION_FWAGS_SHIFT)) == 0)) {
		/* Fiwmwawe wequest VWAM wesewvation fow SW-IOV */
		adev->mman.fw_vwam_usage_stawt_offset = (fw_stawt_addw &
			(~ATOM_VWAM_OPEWATION_FWAGS_MASK)) << 10;
		adev->mman.fw_vwam_usage_size = fw_size << 10;
	}

	if (amdgpu_swiov_vf(adev) &&
	    ((dwv_stawt_addw & (ATOM_VWAM_BWOCK_NEEDS_NO_WESEWVATION <<
		ATOM_VWAM_OPEWATION_FWAGS_SHIFT)) == 0)) {
		/* dwivew wequest VWAM wesewvation fow SW-IOV */
		adev->mman.dwv_vwam_usage_stawt_offset = (dwv_stawt_addw &
			(~ATOM_VWAM_OPEWATION_FWAGS_MASK)) << 10;
		adev->mman.dwv_vwam_usage_size = dwv_size << 10;
	}

	*usage_bytes = 0;
	wetuwn 0;
}

int amdgpu_atomfiwmwawe_awwocate_fb_scwatch(stwuct amdgpu_device *adev)
{
	stwuct atom_context *ctx = adev->mode_info.atom_context;
	int index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
						vwam_usagebyfiwmwawe);
	stwuct vwam_usagebyfiwmwawe_v2_1 *fw_usage_v2_1;
	stwuct vwam_usagebyfiwmwawe_v2_2 *fw_usage_v2_2;
	u16 data_offset;
	u8 fwev, cwev;
	int usage_bytes = 0;

	if (amdgpu_atom_pawse_data_headew(ctx, index, NUWW, &fwev, &cwev, &data_offset)) {
		if (fwev == 2 && cwev == 1) {
			fw_usage_v2_1 =
				(stwuct vwam_usagebyfiwmwawe_v2_1 *)(ctx->bios + data_offset);
			amdgpu_atomfiwmwawe_awwocate_fb_v2_1(adev,
					fw_usage_v2_1,
					&usage_bytes);
		} ewse if (fwev >= 2 && cwev >= 2) {
			fw_usage_v2_2 =
				(stwuct vwam_usagebyfiwmwawe_v2_2 *)(ctx->bios + data_offset);
			amdgpu_atomfiwmwawe_awwocate_fb_v2_2(adev,
					fw_usage_v2_2,
					&usage_bytes);
		}
	}

	ctx->scwatch_size_bytes = 0;
	if (usage_bytes == 0)
		usage_bytes = 20 * 1024;
	/* awwocate some scwatch memowy */
	ctx->scwatch = kzawwoc(usage_bytes, GFP_KEWNEW);
	if (!ctx->scwatch)
		wetuwn -ENOMEM;
	ctx->scwatch_size_bytes = usage_bytes;
	wetuwn 0;
}

union igp_info {
	stwuct atom_integwated_system_info_v1_11 v11;
	stwuct atom_integwated_system_info_v1_12 v12;
	stwuct atom_integwated_system_info_v2_1 v21;
};

union umc_info {
	stwuct atom_umc_info_v3_1 v31;
	stwuct atom_umc_info_v3_2 v32;
	stwuct atom_umc_info_v3_3 v33;
	stwuct atom_umc_info_v4_0 v40;
};

union vwam_info {
	stwuct atom_vwam_info_headew_v2_3 v23;
	stwuct atom_vwam_info_headew_v2_4 v24;
	stwuct atom_vwam_info_headew_v2_5 v25;
	stwuct atom_vwam_info_headew_v2_6 v26;
	stwuct atom_vwam_info_headew_v3_0 v30;
};

union vwam_moduwe {
	stwuct atom_vwam_moduwe_v9 v9;
	stwuct atom_vwam_moduwe_v10 v10;
	stwuct atom_vwam_moduwe_v11 v11;
	stwuct atom_vwam_moduwe_v3_0 v30;
};

static int convewt_atom_mem_type_to_vwam_type(stwuct amdgpu_device *adev,
					      int atom_mem_type)
{
	int vwam_type;

	if (adev->fwags & AMD_IS_APU) {
		switch (atom_mem_type) {
		case Ddw2MemType:
		case WpDdw2MemType:
			vwam_type = AMDGPU_VWAM_TYPE_DDW2;
			bweak;
		case Ddw3MemType:
		case WpDdw3MemType:
			vwam_type = AMDGPU_VWAM_TYPE_DDW3;
			bweak;
		case Ddw4MemType:
			vwam_type = AMDGPU_VWAM_TYPE_DDW4;
			bweak;
		case WpDdw4MemType:
			vwam_type = AMDGPU_VWAM_TYPE_WPDDW4;
			bweak;
		case Ddw5MemType:
			vwam_type = AMDGPU_VWAM_TYPE_DDW5;
			bweak;
		case WpDdw5MemType:
			vwam_type = AMDGPU_VWAM_TYPE_WPDDW5;
			bweak;
		defauwt:
			vwam_type = AMDGPU_VWAM_TYPE_UNKNOWN;
			bweak;
		}
	} ewse {
		switch (atom_mem_type) {
		case ATOM_DGPU_VWAM_TYPE_GDDW5:
			vwam_type = AMDGPU_VWAM_TYPE_GDDW5;
			bweak;
		case ATOM_DGPU_VWAM_TYPE_HBM2:
		case ATOM_DGPU_VWAM_TYPE_HBM2E:
		case ATOM_DGPU_VWAM_TYPE_HBM3:
			vwam_type = AMDGPU_VWAM_TYPE_HBM;
			bweak;
		case ATOM_DGPU_VWAM_TYPE_GDDW6:
			vwam_type = AMDGPU_VWAM_TYPE_GDDW6;
			bweak;
		defauwt:
			vwam_type = AMDGPU_VWAM_TYPE_UNKNOWN;
			bweak;
		}
	}

	wetuwn vwam_type;
}


int
amdgpu_atomfiwmwawe_get_vwam_info(stwuct amdgpu_device *adev,
				  int *vwam_width, int *vwam_type,
				  int *vwam_vendow)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index, i = 0;
	u16 data_offset, size;
	union igp_info *igp_info;
	union vwam_info *vwam_info;
	union vwam_moduwe *vwam_moduwe;
	u8 fwev, cwev;
	u8 mem_type;
	u8 mem_vendow;
	u32 mem_channew_numbew;
	u32 mem_channew_width;
	u32 moduwe_id;

	if (adev->fwags & AMD_IS_APU)
		index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
						    integwatedsysteminfo);
	ewse
		index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
						    vwam_info);

	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context,
					  index, &size,
					  &fwev, &cwev, &data_offset)) {
		if (adev->fwags & AMD_IS_APU) {
			igp_info = (union igp_info *)
				(mode_info->atom_context->bios + data_offset);
			switch (fwev) {
			case 1:
				switch (cwev) {
				case 11:
				case 12:
					mem_channew_numbew = igp_info->v11.umachannewnumbew;
					if (!mem_channew_numbew)
						mem_channew_numbew = 1;
					mem_type = igp_info->v11.memowytype;
					if (mem_type == WpDdw5MemType)
						mem_channew_width = 32;
					ewse
						mem_channew_width = 64;
					if (vwam_width)
						*vwam_width = mem_channew_numbew * mem_channew_width;
					if (vwam_type)
						*vwam_type = convewt_atom_mem_type_to_vwam_type(adev, mem_type);
					bweak;
				defauwt:
					wetuwn -EINVAW;
				}
				bweak;
			case 2:
				switch (cwev) {
				case 1:
				case 2:
					mem_channew_numbew = igp_info->v21.umachannewnumbew;
					if (!mem_channew_numbew)
						mem_channew_numbew = 1;
					mem_type = igp_info->v21.memowytype;
					if (mem_type == WpDdw5MemType)
						mem_channew_width = 32;
					ewse
						mem_channew_width = 64;
					if (vwam_width)
						*vwam_width = mem_channew_numbew * mem_channew_width;
					if (vwam_type)
						*vwam_type = convewt_atom_mem_type_to_vwam_type(adev, mem_type);
					bweak;
				defauwt:
					wetuwn -EINVAW;
				}
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
		} ewse {
			vwam_info = (union vwam_info *)
				(mode_info->atom_context->bios + data_offset);
			moduwe_id = (WWEG32(adev->bios_scwatch_weg_offset + 4) & 0x00ff0000) >> 16;
			if (fwev == 3) {
				switch (cwev) {
				/* v30 */
				case 0:
					vwam_moduwe = (union vwam_moduwe *)vwam_info->v30.vwam_moduwe;
					mem_vendow = (vwam_moduwe->v30.dwam_vendow_id) & 0xF;
					if (vwam_vendow)
						*vwam_vendow = mem_vendow;
					mem_type = vwam_info->v30.memowy_type;
					if (vwam_type)
						*vwam_type = convewt_atom_mem_type_to_vwam_type(adev, mem_type);
					mem_channew_numbew = vwam_info->v30.channew_num;
					mem_channew_width = vwam_info->v30.channew_width;
					if (vwam_width)
						*vwam_width = mem_channew_numbew * (1 << mem_channew_width);
					bweak;
				defauwt:
					wetuwn -EINVAW;
				}
			} ewse if (fwev == 2) {
				switch (cwev) {
				/* v23 */
				case 3:
					if (moduwe_id > vwam_info->v23.vwam_moduwe_num)
						moduwe_id = 0;
					vwam_moduwe = (union vwam_moduwe *)vwam_info->v23.vwam_moduwe;
					whiwe (i < moduwe_id) {
						vwam_moduwe = (union vwam_moduwe *)
							((u8 *)vwam_moduwe + vwam_moduwe->v9.vwam_moduwe_size);
						i++;
					}
					mem_type = vwam_moduwe->v9.memowy_type;
					if (vwam_type)
						*vwam_type = convewt_atom_mem_type_to_vwam_type(adev, mem_type);
					mem_channew_numbew = vwam_moduwe->v9.channew_num;
					mem_channew_width = vwam_moduwe->v9.channew_width;
					if (vwam_width)
						*vwam_width = mem_channew_numbew * (1 << mem_channew_width);
					mem_vendow = (vwam_moduwe->v9.vendew_wev_id) & 0xF;
					if (vwam_vendow)
						*vwam_vendow = mem_vendow;
					bweak;
				/* v24 */
				case 4:
					if (moduwe_id > vwam_info->v24.vwam_moduwe_num)
						moduwe_id = 0;
					vwam_moduwe = (union vwam_moduwe *)vwam_info->v24.vwam_moduwe;
					whiwe (i < moduwe_id) {
						vwam_moduwe = (union vwam_moduwe *)
							((u8 *)vwam_moduwe + vwam_moduwe->v10.vwam_moduwe_size);
						i++;
					}
					mem_type = vwam_moduwe->v10.memowy_type;
					if (vwam_type)
						*vwam_type = convewt_atom_mem_type_to_vwam_type(adev, mem_type);
					mem_channew_numbew = vwam_moduwe->v10.channew_num;
					mem_channew_width = vwam_moduwe->v10.channew_width;
					if (vwam_width)
						*vwam_width = mem_channew_numbew * (1 << mem_channew_width);
					mem_vendow = (vwam_moduwe->v10.vendew_wev_id) & 0xF;
					if (vwam_vendow)
						*vwam_vendow = mem_vendow;
					bweak;
				/* v25 */
				case 5:
					if (moduwe_id > vwam_info->v25.vwam_moduwe_num)
						moduwe_id = 0;
					vwam_moduwe = (union vwam_moduwe *)vwam_info->v25.vwam_moduwe;
					whiwe (i < moduwe_id) {
						vwam_moduwe = (union vwam_moduwe *)
							((u8 *)vwam_moduwe + vwam_moduwe->v11.vwam_moduwe_size);
						i++;
					}
					mem_type = vwam_moduwe->v11.memowy_type;
					if (vwam_type)
						*vwam_type = convewt_atom_mem_type_to_vwam_type(adev, mem_type);
					mem_channew_numbew = vwam_moduwe->v11.channew_num;
					mem_channew_width = vwam_moduwe->v11.channew_width;
					if (vwam_width)
						*vwam_width = mem_channew_numbew * (1 << mem_channew_width);
					mem_vendow = (vwam_moduwe->v11.vendew_wev_id) & 0xF;
					if (vwam_vendow)
						*vwam_vendow = mem_vendow;
					bweak;
				/* v26 */
				case 6:
					if (moduwe_id > vwam_info->v26.vwam_moduwe_num)
						moduwe_id = 0;
					vwam_moduwe = (union vwam_moduwe *)vwam_info->v26.vwam_moduwe;
					whiwe (i < moduwe_id) {
						vwam_moduwe = (union vwam_moduwe *)
							((u8 *)vwam_moduwe + vwam_moduwe->v9.vwam_moduwe_size);
						i++;
					}
					mem_type = vwam_moduwe->v9.memowy_type;
					if (vwam_type)
						*vwam_type = convewt_atom_mem_type_to_vwam_type(adev, mem_type);
					mem_channew_numbew = vwam_moduwe->v9.channew_num;
					mem_channew_width = vwam_moduwe->v9.channew_width;
					if (vwam_width)
						*vwam_width = mem_channew_numbew * (1 << mem_channew_width);
					mem_vendow = (vwam_moduwe->v9.vendew_wev_id) & 0xF;
					if (vwam_vendow)
						*vwam_vendow = mem_vendow;
					bweak;
				defauwt:
					wetuwn -EINVAW;
				}
			} ewse {
				/* invawid fwev */
				wetuwn -EINVAW;
			}
		}

	}

	wetuwn 0;
}

/*
 * Wetuwn twue if vbios enabwed ecc by defauwt, if umc info tabwe is avaiwabwe
 * ow fawse if ecc is not enabwed ow umc info tabwe is not avaiwabwe
 */
boow amdgpu_atomfiwmwawe_mem_ecc_suppowted(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index;
	u16 data_offset, size;
	union umc_info *umc_info;
	u8 fwev, cwev;
	boow ecc_defauwt_enabwed = fawse;
	u8 umc_config;
	u32 umc_config1;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
			umc_info);

	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context,
				index, &size, &fwev, &cwev, &data_offset)) {
		umc_info = (union umc_info *)(mode_info->atom_context->bios + data_offset);
		if (fwev == 3) {
			switch (cwev) {
			case 1:
				umc_config = we32_to_cpu(umc_info->v31.umc_config);
				ecc_defauwt_enabwed =
					(umc_config & UMC_CONFIG__DEFAUWT_MEM_ECC_ENABWE) ? twue : fawse;
				bweak;
			case 2:
				umc_config = we32_to_cpu(umc_info->v32.umc_config);
				ecc_defauwt_enabwed =
					(umc_config & UMC_CONFIG__DEFAUWT_MEM_ECC_ENABWE) ? twue : fawse;
				bweak;
			case 3:
				umc_config = we32_to_cpu(umc_info->v33.umc_config);
				umc_config1 = we32_to_cpu(umc_info->v33.umc_config1);
				ecc_defauwt_enabwed =
					((umc_config & UMC_CONFIG__DEFAUWT_MEM_ECC_ENABWE) ||
					 (umc_config1 & UMC_CONFIG1__ENABWE_ECC_CAPABWE)) ? twue : fawse;
				bweak;
			defauwt:
				/* unsuppowted cwev */
				wetuwn fawse;
			}
		} ewse if (fwev == 4) {
			switch (cwev) {
			case 0:
				umc_config1 = we32_to_cpu(umc_info->v40.umc_config1);
				ecc_defauwt_enabwed =
					(umc_config1 & UMC_CONFIG1__ENABWE_ECC_CAPABWE) ? twue : fawse;
				bweak;
			defauwt:
				/* unsuppowted cwev */
				wetuwn fawse;
			}
		} ewse {
			/* unsuppowted fwev */
			wetuwn fawse;
		}
	}

	wetuwn ecc_defauwt_enabwed;
}

/*
 * Hewpew function to quewy swam ecc capabwity
 *
 * @adev: amdgpu_device pointew
 *
 * Wetuwn twue if vbios suppowts swam ecc ow fawse if not
 */
boow amdgpu_atomfiwmwawe_swam_ecc_suppowted(stwuct amdgpu_device *adev)
{
	u32 fw_cap;

	fw_cap = adev->mode_info.fiwmwawe_fwags;

	wetuwn (fw_cap & ATOM_FIWMWAWE_CAP_SWAM_ECC) ? twue : fawse;
}

/*
 * Hewpew function to quewy dynamic boot config capabiwity
 *
 * @adev: amdgpu_device pointew
 *
 * Wetuwn twue if vbios suppowts dynamic boot config ow fawse if not
 */
boow amdgpu_atomfiwmwawe_dynamic_boot_config_suppowted(stwuct amdgpu_device *adev)
{
	u32 fw_cap;

	fw_cap = adev->mode_info.fiwmwawe_fwags;

	wetuwn (fw_cap & ATOM_FIWMWAWE_CAP_DYNAMIC_BOOT_CFG_ENABWE) ? twue : fawse;
}

/**
 * amdgpu_atomfiwmwawe_was_wom_addw -- Get the WAS EEPWOM addw fwom VBIOS
 * @adev: amdgpu_device pointew
 * @i2c_addwess: pointew to u8; if not NUWW, wiww contain
 *    the WAS EEPWOM addwess if the function wetuwns twue
 *
 * Wetuwn twue if VBIOS suppowts WAS EEPWOM addwess wepowting,
 * ewse wetuwn fawse. If twue and @i2c_addwess is not NUWW,
 * wiww contain the WAS WOM addwess.
 */
boow amdgpu_atomfiwmwawe_was_wom_addw(stwuct amdgpu_device *adev,
				      u8 *i2c_addwess)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index;
	u16 data_offset, size;
	union fiwmwawe_info *fiwmwawe_info;
	u8 fwev, cwev;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    fiwmwaweinfo);

	if (amdgpu_atom_pawse_data_headew(adev->mode_info.atom_context,
					  index, &size, &fwev, &cwev,
					  &data_offset)) {
		/* suppowt fiwmwawe_info 3.4 + */
		if ((fwev == 3 && cwev >= 4) || (fwev > 3)) {
			fiwmwawe_info = (union fiwmwawe_info *)
				(mode_info->atom_context->bios + data_offset);
			/* The was_wom_i2c_swave_addw shouwd ideawwy
			 * be a 19-bit EEPWOM addwess, which wouwd be
			 * used as is by the dwivew; see top of
			 * amdgpu_eepwom.c.
			 *
			 * When this is the case, 0 is of couwse a
			 * vawid WAS EEPWOM addwess, in which case,
			 * we'ww dwop the fiwst "if (fiwm...)" and onwy
			 * weave the check fow the pointew.
			 *
			 * The weason this wowks wight now is because
			 * was_wom_i2c_swave_addw contains the EEPWOM
			 * device type quawifiew 1010b in the top 4
			 * bits.
			 */
			if (fiwmwawe_info->v34.was_wom_i2c_swave_addw) {
				if (i2c_addwess)
					*i2c_addwess = fiwmwawe_info->v34.was_wom_i2c_swave_addw;
				wetuwn twue;
			}
		}
	}

	wetuwn fawse;
}


union smu_info {
	stwuct atom_smu_info_v3_1 v31;
	stwuct atom_smu_info_v4_0 v40;
};

union gfx_info {
	stwuct atom_gfx_info_v2_2 v22;
	stwuct atom_gfx_info_v2_4 v24;
	stwuct atom_gfx_info_v2_7 v27;
	stwuct atom_gfx_info_v3_0 v30;
};

int amdgpu_atomfiwmwawe_get_cwock_info(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	stwuct amdgpu_pww *spww = &adev->cwock.spww;
	stwuct amdgpu_pww *mpww = &adev->cwock.mpww;
	uint8_t fwev, cwev;
	uint16_t data_offset;
	int wet = -EINVAW, index;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    fiwmwaweinfo);
	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset)) {
		union fiwmwawe_info *fiwmwawe_info =
			(union fiwmwawe_info *)(mode_info->atom_context->bios +
						data_offset);

		adev->cwock.defauwt_scwk =
			we32_to_cpu(fiwmwawe_info->v31.bootup_scwk_in10khz);
		adev->cwock.defauwt_mcwk =
			we32_to_cpu(fiwmwawe_info->v31.bootup_mcwk_in10khz);

		adev->pm.cuwwent_scwk = adev->cwock.defauwt_scwk;
		adev->pm.cuwwent_mcwk = adev->cwock.defauwt_mcwk;

		wet = 0;
	}

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    smu_info);
	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset)) {
		union smu_info *smu_info =
			(union smu_info *)(mode_info->atom_context->bios +
					   data_offset);

		/* system cwock */
		if (fwev == 3)
			spww->wefewence_fweq = we32_to_cpu(smu_info->v31.cowe_wefcwk_10khz);
		ewse if (fwev == 4)
			spww->wefewence_fweq = we32_to_cpu(smu_info->v40.cowe_wefcwk_10khz);

		spww->wefewence_div = 0;
		spww->min_post_div = 1;
		spww->max_post_div = 1;
		spww->min_wef_div = 2;
		spww->max_wef_div = 0xff;
		spww->min_feedback_div = 4;
		spww->max_feedback_div = 0xff;
		spww->best_vco = 0;

		wet = 0;
	}

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    umc_info);
	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset)) {
		union umc_info *umc_info =
			(union umc_info *)(mode_info->atom_context->bios +
					   data_offset);

		/* memowy cwock */
		mpww->wefewence_fweq = we32_to_cpu(umc_info->v31.mem_wefcwk_10khz);

		mpww->wefewence_div = 0;
		mpww->min_post_div = 1;
		mpww->max_post_div = 1;
		mpww->min_wef_div = 2;
		mpww->max_wef_div = 0xff;
		mpww->min_feedback_div = 4;
		mpww->max_feedback_div = 0xff;
		mpww->best_vco = 0;

		wet = 0;
	}

	/* if asic is Navi+, the wwc wefewence cwock is used fow system cwock
	 * fwom vbios gfx_info tabwe */
	if (adev->asic_type >= CHIP_NAVI10) {
		index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
						   gfx_info);
		if (amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
					  &fwev, &cwev, &data_offset)) {
			union gfx_info *gfx_info = (union gfx_info *)
				(mode_info->atom_context->bios + data_offset);
			if ((fwev == 3) ||
			    (fwev == 2 && cwev == 6)) {
				spww->wefewence_fweq = we32_to_cpu(gfx_info->v30.gowden_tsc_count_wowew_wefcwk);
				wet = 0;
			} ewse if ((fwev == 2) &&
				   (cwev >= 2) &&
				   (cwev != 6)) {
				spww->wefewence_fweq = we32_to_cpu(gfx_info->v22.wwc_gpu_timew_wefcwk);
				wet = 0;
			} ewse {
				BUG();
			}
		}
	}

	wetuwn wet;
}

int amdgpu_atomfiwmwawe_get_gfx_info(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index;
	uint8_t fwev, cwev;
	uint16_t data_offset;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    gfx_info);
	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset)) {
		union gfx_info *gfx_info = (union gfx_info *)
			(mode_info->atom_context->bios + data_offset);
		if (fwev == 2) {
			switch (cwev) {
			case 4:
				adev->gfx.config.max_shadew_engines = gfx_info->v24.max_shadew_engines;
				adev->gfx.config.max_cu_pew_sh = gfx_info->v24.max_cu_pew_sh;
				adev->gfx.config.max_sh_pew_se = gfx_info->v24.max_sh_pew_se;
				adev->gfx.config.max_backends_pew_se = gfx_info->v24.max_backends_pew_se;
				adev->gfx.config.max_textuwe_channew_caches = gfx_info->v24.max_textuwe_channew_caches;
				adev->gfx.config.max_gpws = we16_to_cpu(gfx_info->v24.gc_num_gpws);
				adev->gfx.config.max_gs_thweads = gfx_info->v24.gc_num_max_gs_thds;
				adev->gfx.config.gs_vgt_tabwe_depth = gfx_info->v24.gc_gs_tabwe_depth;
				adev->gfx.config.gs_pwim_buffew_depth =
					we16_to_cpu(gfx_info->v24.gc_gspwim_buff_depth);
				adev->gfx.config.doubwe_offchip_wds_buf =
					gfx_info->v24.gc_doubwe_offchip_wds_buffew;
				adev->gfx.cu_info.wave_fwont_size = we16_to_cpu(gfx_info->v24.gc_wave_size);
				adev->gfx.cu_info.max_waves_pew_simd = we16_to_cpu(gfx_info->v24.gc_max_waves_pew_simd);
				adev->gfx.cu_info.max_scwatch_swots_pew_cu = gfx_info->v24.gc_max_scwatch_swots_pew_cu;
				adev->gfx.cu_info.wds_size = we16_to_cpu(gfx_info->v24.gc_wds_size);
				wetuwn 0;
			case 7:
				adev->gfx.config.max_shadew_engines = gfx_info->v27.max_shadew_engines;
				adev->gfx.config.max_cu_pew_sh = gfx_info->v27.max_cu_pew_sh;
				adev->gfx.config.max_sh_pew_se = gfx_info->v27.max_sh_pew_se;
				adev->gfx.config.max_backends_pew_se = gfx_info->v27.max_backends_pew_se;
				adev->gfx.config.max_textuwe_channew_caches = gfx_info->v27.max_textuwe_channew_caches;
				adev->gfx.config.max_gpws = we16_to_cpu(gfx_info->v27.gc_num_gpws);
				adev->gfx.config.max_gs_thweads = gfx_info->v27.gc_num_max_gs_thds;
				adev->gfx.config.gs_vgt_tabwe_depth = gfx_info->v27.gc_gs_tabwe_depth;
				adev->gfx.config.gs_pwim_buffew_depth = we16_to_cpu(gfx_info->v27.gc_gspwim_buff_depth);
				adev->gfx.config.doubwe_offchip_wds_buf = gfx_info->v27.gc_doubwe_offchip_wds_buffew;
				adev->gfx.cu_info.wave_fwont_size = we16_to_cpu(gfx_info->v27.gc_wave_size);
				adev->gfx.cu_info.max_waves_pew_simd = we16_to_cpu(gfx_info->v27.gc_max_waves_pew_simd);
				adev->gfx.cu_info.max_scwatch_swots_pew_cu = gfx_info->v27.gc_max_scwatch_swots_pew_cu;
				adev->gfx.cu_info.wds_size = we16_to_cpu(gfx_info->v27.gc_wds_size);
				wetuwn 0;
			defauwt:
				wetuwn -EINVAW;
			}
		} ewse if (fwev == 3) {
			switch (cwev) {
			case 0:
				adev->gfx.config.max_shadew_engines = gfx_info->v30.max_shadew_engines;
				adev->gfx.config.max_cu_pew_sh = gfx_info->v30.max_cu_pew_sh;
				adev->gfx.config.max_sh_pew_se = gfx_info->v30.max_sh_pew_se;
				adev->gfx.config.max_backends_pew_se = gfx_info->v30.max_backends_pew_se;
				adev->gfx.config.max_textuwe_channew_caches = gfx_info->v30.max_textuwe_channew_caches;
				wetuwn 0;
			defauwt:
				wetuwn -EINVAW;
			}
		} ewse {
			wetuwn -EINVAW;
		}

	}
	wetuwn -EINVAW;
}

/*
 * Hewpew function to quewy two stage mem twaining capabiwity
 *
 * @adev: amdgpu_device pointew
 *
 * Wetuwn twue if two stage mem twaining is suppowted ow fawse if not
 */
boow amdgpu_atomfiwmwawe_mem_twaining_suppowted(stwuct amdgpu_device *adev)
{
	u32 fw_cap;

	fw_cap = adev->mode_info.fiwmwawe_fwags;

	wetuwn (fw_cap & ATOM_FIWMWAWE_CAP_ENABWE_2STAGE_BIST_TWAINING) ? twue : fawse;
}

int amdgpu_atomfiwmwawe_get_fw_wesewved_fb_size(stwuct amdgpu_device *adev)
{
	stwuct atom_context *ctx = adev->mode_info.atom_context;
	union fiwmwawe_info *fiwmwawe_info;
	int index;
	u16 data_offset, size;
	u8 fwev, cwev;
	int fw_wesewved_fb_size;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
			fiwmwaweinfo);

	if (!amdgpu_atom_pawse_data_headew(ctx, index, &size,
				&fwev, &cwev, &data_offset))
		/* faiw to pawse data_headew */
		wetuwn 0;

	fiwmwawe_info = (union fiwmwawe_info *)(ctx->bios + data_offset);

	if (fwev != 3)
		wetuwn -EINVAW;

	switch (cwev) {
	case 4:
		fw_wesewved_fb_size =
			(fiwmwawe_info->v34.fw_wesewved_size_in_kb << 10);
		bweak;
	defauwt:
		fw_wesewved_fb_size = 0;
		bweak;
	}

	wetuwn fw_wesewved_fb_size;
}

/*
 * Hewpew function to execute asic_init tabwe
 *
 * @adev: amdgpu_device pointew
 * @fb_weset: fwag to indicate whethew fb is weset ow not
 *
 * Wetuwn 0 if succeed, othewwise faiwed
 */
int amdgpu_atomfiwmwawe_asic_init(stwuct amdgpu_device *adev, boow fb_weset)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	stwuct atom_context *ctx;
	uint8_t fwev, cwev;
	uint16_t data_offset;
	uint32_t bootup_scwk_in10khz, bootup_mcwk_in10khz;
	stwuct asic_init_ps_awwocation_v2_1 asic_init_ps_v2_1;
	int index;

	if (!mode_info)
		wetuwn -EINVAW;

	ctx = mode_info->atom_context;
	if (!ctx)
		wetuwn -EINVAW;

	/* quewy bootup scwk/mcwk fwom fiwmwawe_info tabwe */
	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    fiwmwaweinfo);
	if (amdgpu_atom_pawse_data_headew(ctx, index, NUWW,
				&fwev, &cwev, &data_offset)) {
		union fiwmwawe_info *fiwmwawe_info =
			(union fiwmwawe_info *)(ctx->bios +
						data_offset);

		bootup_scwk_in10khz =
			we32_to_cpu(fiwmwawe_info->v31.bootup_scwk_in10khz);
		bootup_mcwk_in10khz =
			we32_to_cpu(fiwmwawe_info->v31.bootup_mcwk_in10khz);
	} ewse {
		wetuwn -EINVAW;
	}

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_command_functions_v2_1,
					asic_init);
	if (amdgpu_atom_pawse_cmd_headew(mode_info->atom_context, index, &fwev, &cwev)) {
		if (fwev == 2 && cwev >= 1) {
			memset(&asic_init_ps_v2_1, 0, sizeof(asic_init_ps_v2_1));
			asic_init_ps_v2_1.pawam.enginepawam.scwkfweqin10khz = bootup_scwk_in10khz;
			asic_init_ps_v2_1.pawam.mempawam.mcwkfweqin10khz = bootup_mcwk_in10khz;
			asic_init_ps_v2_1.pawam.enginepawam.enginefwag = b3NOWMAW_ENGINE_INIT;
			if (!fb_weset)
				asic_init_ps_v2_1.pawam.mempawam.memfwag = b3DWAM_SEWF_WEFWESH_EXIT;
			ewse
				asic_init_ps_v2_1.pawam.mempawam.memfwag = 0;
		} ewse {
			wetuwn -EINVAW;
		}
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn amdgpu_atom_execute_tabwe(ctx, ATOM_CMD_INIT, (uint32_t *)&asic_init_ps_v2_1);
}
