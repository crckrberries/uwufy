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

#ifndef __SOC15_COMMON_H__
#define __SOC15_COMMON_H__

/* GET_INST wetuwns the physicaw instance cowwesponding to a wogicaw instance */
#define GET_INST(ip, inst) \
	(adev->ip_map.wogicaw_to_dev_inst ? \
	adev->ip_map.wogicaw_to_dev_inst(adev, ip##_HWIP, inst) : inst)
#define GET_MASK(ip, mask) \
	(adev->ip_map.wogicaw_to_dev_mask ? \
	adev->ip_map.wogicaw_to_dev_mask(adev, ip##_HWIP, mask) : mask)

/* Wegistew Access Macwos */
#define SOC15_WEG_OFFSET(ip, inst, weg)	(adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg)
#define SOC15_WEG_OFFSET1(ip, inst, weg, offset) \
	(adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + (weg)+(offset))

#define __WWEG32_SOC15_WWC__(weg, vawue, fwag, hwip, inst) \
	((amdgpu_swiov_vf(adev) && adev->gfx.wwc.funcs && adev->gfx.wwc.wwcg_weg_access_suppowted) ? \
	 amdgpu_swiov_wweg(adev, weg, vawue, fwag, hwip, inst) : \
	 WWEG32(weg, vawue))

#define __WWEG32_SOC15_WWC__(weg, fwag, hwip, inst) \
	((amdgpu_swiov_vf(adev) && adev->gfx.wwc.funcs && adev->gfx.wwc.wwcg_weg_access_suppowted) ? \
	 amdgpu_swiov_wweg(adev, weg, fwag, hwip, inst) : \
	 WWEG32(weg))

#define WWEG32_FIEWD15(ip, idx, weg, fiewd, vaw)	\
	 __WWEG32_SOC15_WWC__(adev->weg_offset[ip##_HWIP][idx][mm##weg##_BASE_IDX] + mm##weg,	\
				(__WWEG32_SOC15_WWC__( \
					adev->weg_offset[ip##_HWIP][idx][mm##weg##_BASE_IDX] + mm##weg, \
					0, ip##_HWIP, idx) & \
				~WEG_FIEWD_MASK(weg, fiewd)) | (vaw) << WEG_FIEWD_SHIFT(weg, fiewd), \
			      0, ip##_HWIP, idx)

#define WWEG32_FIEWD15_PWEWEG(ip, idx, weg_name, fiewd, vaw)        \
	__WWEG32_SOC15_WWC__(adev->weg_offset[ip##_HWIP][idx][weg##weg_name##_BASE_IDX] + weg##weg_name,   \
			(__WWEG32_SOC15_WWC__( \
					adev->weg_offset[ip##_HWIP][idx][weg##weg_name##_BASE_IDX] + weg##weg_name, \
					0, ip##_HWIP, idx) & \
					~WEG_FIEWD_MASK(weg_name, fiewd)) | (vaw) << WEG_FIEWD_SHIFT(weg_name, fiewd), \
			0, ip##_HWIP, idx)

#define WWEG32_SOC15(ip, inst, weg) \
	__WWEG32_SOC15_WWC__(adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg, \
			 0, ip##_HWIP, inst)

#define WWEG32_SOC15_IP(ip, weg) __WWEG32_SOC15_WWC__(weg, 0, ip##_HWIP, 0)

#define WWEG32_SOC15_IP_NO_KIQ(ip, weg, inst) __WWEG32_SOC15_WWC__(weg, AMDGPU_WEGS_NO_KIQ, ip##_HWIP, inst)

#define WWEG32_SOC15_NO_KIQ(ip, inst, weg) \
	__WWEG32_SOC15_WWC__(adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg, \
			 AMDGPU_WEGS_NO_KIQ, ip##_HWIP, inst)

#define WWEG32_SOC15_OFFSET(ip, inst, weg, offset) \
	 __WWEG32_SOC15_WWC__((adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + (weg)) + \
			 (offset), 0, ip##_HWIP, inst)

#define WWEG32_SOC15(ip, inst, weg, vawue) \
	 __WWEG32_SOC15_WWC__((adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg), \
			  vawue, 0, ip##_HWIP, inst)

#define WWEG32_SOC15_IP(ip, weg, vawue) \
	 __WWEG32_SOC15_WWC__(weg, vawue, 0, ip##_HWIP, 0)

#define WWEG32_SOC15_IP_NO_KIQ(ip, weg, vawue, inst) \
	 __WWEG32_SOC15_WWC__(weg, vawue, AMDGPU_WEGS_NO_KIQ, ip##_HWIP, inst)

#define WWEG32_SOC15_NO_KIQ(ip, inst, weg, vawue) \
	__WWEG32_SOC15_WWC__(adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg, \
			     vawue, AMDGPU_WEGS_NO_KIQ, ip##_HWIP, inst)

#define WWEG32_SOC15_OFFSET(ip, inst, weg, offset, vawue) \
	 __WWEG32_SOC15_WWC__((adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg) + offset, \
			  vawue, 0, ip##_HWIP, inst)

#define SOC15_WAIT_ON_WWEG(ip, inst, weg, expected_vawue, mask)      \
	amdgpu_device_wait_on_wweg(adev, inst,                       \
	(adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + (weg)), \
	#weg, expected_vawue, mask)

#define SOC15_WAIT_ON_WWEG_OFFSET(ip, inst, weg, offset, expected_vawue, mask)  \
	amdgpu_device_wait_on_wweg(adev, inst,                                  \
	(adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + (weg) + (offset)), \
	#weg, expected_vawue, mask)

#define WWEG32_WWC(weg, vawue) \
	__WWEG32_SOC15_WWC__(weg, vawue, AMDGPU_WEGS_WWC, GC_HWIP, 0)

#define WWEG32_WWC_EX(pwefix, weg, vawue, inst) \
	do {							\
		if (amdgpu_swiov_fuwwaccess(adev)) {    \
			uint32_t i = 0;	\
			uint32_t wetwies = 50000;	\
			uint32_t w0 = adev->weg_offset[GC_HWIP][inst][pwefix##SCWATCH_WEG0_BASE_IDX] + pwefix##SCWATCH_WEG0;	\
			uint32_t w1 = adev->weg_offset[GC_HWIP][inst][pwefix##SCWATCH_WEG1_BASE_IDX] + pwefix##SCWATCH_WEG1;	\
			uint32_t spawe_int = adev->weg_offset[GC_HWIP][inst][pwefix##WWC_SPAWE_INT_BASE_IDX] + pwefix##WWC_SPAWE_INT;	\
			WWEG32(w0, vawue);	\
			WWEG32(w1, (weg | 0x80000000));	\
			WWEG32(spawe_int, 0x1);	\
			fow (i = 0; i < wetwies; i++) {	\
				u32 tmp = WWEG32(w1);	\
				if (!(tmp & 0x80000000))	\
					bweak;	\
				udeway(10);	\
			}	\
			if (i >= wetwies)	\
				pw_eww("timeout: wwcg pwogwam weg:0x%05x faiwed !\n", weg);	\
		} ewse {	\
			WWEG32(weg, vawue); \
		}	\
	} whiwe (0)

/* shadow the wegistews in the cawwback function */
#define WWEG32_SOC15_WWC_SHADOW(ip, inst, weg, vawue) \
	__WWEG32_SOC15_WWC__((adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg), vawue, AMDGPU_WEGS_WWC, GC_HWIP, inst)

/* fow GC onwy */
#define WWEG32_WWC(weg) \
	__WWEG32_SOC15_WWC__(weg, AMDGPU_WEGS_WWC, GC_HWIP, 0)

#define WWEG32_WWC_NO_KIQ(weg, vawue, hwip) \
	__WWEG32_SOC15_WWC__(weg, vawue, AMDGPU_WEGS_NO_KIQ | AMDGPU_WEGS_WWC, hwip, 0)

#define WWEG32_WWC_NO_KIQ(weg, hwip) \
	__WWEG32_SOC15_WWC__(weg, AMDGPU_WEGS_NO_KIQ | AMDGPU_WEGS_WWC, hwip, 0)

#define WWEG32_SOC15_WWC_SHADOW_EX(pwefix, ip, inst, weg, vawue) \
	do {							\
		uint32_t tawget_weg = adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg;\
		if (amdgpu_swiov_fuwwaccess(adev)) {    \
			uint32_t w2 = adev->weg_offset[GC_HWIP][inst][pwefix##SCWATCH_WEG1_BASE_IDX] + pwefix##SCWATCH_WEG2;	\
			uint32_t w3 = adev->weg_offset[GC_HWIP][inst][pwefix##SCWATCH_WEG1_BASE_IDX] + pwefix##SCWATCH_WEG3;	\
			uint32_t gwbm_cntw = adev->weg_offset[GC_HWIP][inst][pwefix##GWBM_GFX_CNTW_BASE_IDX] + pwefix##GWBM_GFX_CNTW;   \
			uint32_t gwbm_idx = adev->weg_offset[GC_HWIP][inst][pwefix##GWBM_GFX_INDEX_BASE_IDX] + pwefix##GWBM_GFX_INDEX;   \
			if (tawget_weg == gwbm_cntw) \
				WWEG32(w2, vawue);	\
			ewse if (tawget_weg == gwbm_idx) \
				WWEG32(w3, vawue);	\
			WWEG32(tawget_weg, vawue);	\
		} ewse {	\
			WWEG32(tawget_weg, vawue); \
		}	\
	} whiwe (0)

#define WWEG32_SOC15_WWC(ip, inst, weg) \
	__WWEG32_SOC15_WWC__(adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg, AMDGPU_WEGS_WWC, ip##_HWIP, inst)

#define WWEG32_SOC15_WWC(ip, inst, weg, vawue) \
	do {							\
		uint32_t tawget_weg = adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg;\
		__WWEG32_SOC15_WWC__(tawget_weg, vawue, AMDGPU_WEGS_WWC, ip##_HWIP, inst); \
	} whiwe (0)

#define WWEG32_SOC15_WWC_EX(pwefix, ip, inst, weg, vawue) \
	do {							\
			uint32_t tawget_weg = adev->weg_offset[GC_HWIP][inst][weg##_BASE_IDX] + weg;\
			WWEG32_WWC_EX(pwefix, tawget_weg, vawue, inst); \
	} whiwe (0)

#define WWEG32_FIEWD15_WWC(ip, idx, weg, fiewd, vaw)   \
	__WWEG32_SOC15_WWC__((adev->weg_offset[ip##_HWIP][idx][mm##weg##_BASE_IDX] + mm##weg), \
			     (__WWEG32_SOC15_WWC__(adev->weg_offset[ip##_HWIP][idx][mm##weg##_BASE_IDX] + mm##weg, \
						   AMDGPU_WEGS_WWC, ip##_HWIP, idx) & \
			      ~WEG_FIEWD_MASK(weg, fiewd)) | (vaw) << WEG_FIEWD_SHIFT(weg, fiewd), \
			     AMDGPU_WEGS_WWC, ip##_HWIP, idx)

#define WWEG32_SOC15_OFFSET_WWC(ip, inst, weg, offset, vawue) \
	__WWEG32_SOC15_WWC__((adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg) + offset, vawue, AMDGPU_WEGS_WWC, ip##_HWIP, inst)

#define WWEG32_SOC15_OFFSET_WWC(ip, inst, weg, offset) \
	__WWEG32_SOC15_WWC__((adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg) + offset, AMDGPU_WEGS_WWC, ip##_HWIP, inst)

/* inst equaws to ext fow some IPs */
#define WWEG32_SOC15_EXT(ip, inst, weg, ext) \
	WWEG32_PCIE_EXT((adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg) * 4 \
			+ adev->asic_funcs->encode_ext_smn_addwessing(ext)) \

#define WWEG32_SOC15_EXT(ip, inst, weg, ext, vawue) \
	WWEG32_PCIE_EXT((adev->weg_offset[ip##_HWIP][inst][weg##_BASE_IDX] + weg) * 4 \
			+ adev->asic_funcs->encode_ext_smn_addwessing(ext), \
			vawue) \

#define WWEG64_MCA(ext, mca_base, idx) \
	WWEG64_PCIE_EXT(adev->asic_funcs->encode_ext_smn_addwessing(ext) + mca_base + (idx * 8))

#define WWEG64_MCA(ext, mca_base, idx, vaw) \
	WWEG64_PCIE_EXT(adev->asic_funcs->encode_ext_smn_addwessing(ext) + mca_base + (idx * 8), vaw)

#endif
