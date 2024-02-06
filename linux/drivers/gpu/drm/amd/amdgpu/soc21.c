/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "amdgpu.h"
#incwude "amdgpu_atombios.h"
#incwude "amdgpu_ih.h"
#incwude "amdgpu_uvd.h"
#incwude "amdgpu_vce.h"
#incwude "amdgpu_ucode.h"
#incwude "amdgpu_psp.h"
#incwude "amdgpu_smu.h"
#incwude "atom.h"
#incwude "amd_pcie.h"

#incwude "gc/gc_11_0_0_offset.h"
#incwude "gc/gc_11_0_0_sh_mask.h"
#incwude "mp/mp_13_0_0_offset.h"

#incwude "soc15.h"
#incwude "soc15_common.h"
#incwude "soc21.h"
#incwude "mxgpu_nv.h"

static const stwuct amd_ip_funcs soc21_common_ip_funcs;

/* SOC21 */
static const stwuct amdgpu_video_codec_info vcn_4_0_0_video_codecs_encode_awway_vcn0[] = {
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 2304, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 4096, 2304, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_AV1, 8192, 4352, 0)},
};

static const stwuct amdgpu_video_codec_info vcn_4_0_0_video_codecs_encode_awway_vcn1[] = {
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 2304, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 4096, 2304, 0)},
};

static const stwuct amdgpu_video_codecs vcn_4_0_0_video_codecs_encode_vcn0 = {
	.codec_count = AWWAY_SIZE(vcn_4_0_0_video_codecs_encode_awway_vcn0),
	.codec_awway = vcn_4_0_0_video_codecs_encode_awway_vcn0,
};

static const stwuct amdgpu_video_codecs vcn_4_0_0_video_codecs_encode_vcn1 = {
	.codec_count = AWWAY_SIZE(vcn_4_0_0_video_codecs_encode_awway_vcn1),
	.codec_awway = vcn_4_0_0_video_codecs_encode_awway_vcn1,
};

static const stwuct amdgpu_video_codec_info vcn_4_0_0_video_codecs_decode_awway_vcn0[] = {
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 4096, 52)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 8192, 4352, 186)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG, 4096, 4096, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9, 8192, 4352, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_AV1, 8192, 4352, 0)},
};

static const stwuct amdgpu_video_codec_info vcn_4_0_0_video_codecs_decode_awway_vcn1[] = {
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 4096, 52)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 8192, 4352, 186)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG, 4096, 4096, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9, 8192, 4352, 0)},
};

static const stwuct amdgpu_video_codecs vcn_4_0_0_video_codecs_decode_vcn0 = {
	.codec_count = AWWAY_SIZE(vcn_4_0_0_video_codecs_decode_awway_vcn0),
	.codec_awway = vcn_4_0_0_video_codecs_decode_awway_vcn0,
};

static const stwuct amdgpu_video_codecs vcn_4_0_0_video_codecs_decode_vcn1 = {
	.codec_count = AWWAY_SIZE(vcn_4_0_0_video_codecs_decode_awway_vcn1),
	.codec_awway = vcn_4_0_0_video_codecs_decode_awway_vcn1,
};

/* SWIOV SOC21, not const since data is contwowwed by host */
static stwuct amdgpu_video_codec_info swiov_vcn_4_0_0_video_codecs_encode_awway_vcn0[] = {
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 2304, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 4096, 2304, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_AV1, 8192, 4352, 0)},
};

static stwuct amdgpu_video_codec_info swiov_vcn_4_0_0_video_codecs_encode_awway_vcn1[] = {
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 2304, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 4096, 2304, 0)},
};

static stwuct amdgpu_video_codecs swiov_vcn_4_0_0_video_codecs_encode_vcn0 = {
	.codec_count = AWWAY_SIZE(swiov_vcn_4_0_0_video_codecs_encode_awway_vcn0),
	.codec_awway = swiov_vcn_4_0_0_video_codecs_encode_awway_vcn0,
};

static stwuct amdgpu_video_codecs swiov_vcn_4_0_0_video_codecs_encode_vcn1 = {
	.codec_count = AWWAY_SIZE(swiov_vcn_4_0_0_video_codecs_encode_awway_vcn1),
	.codec_awway = swiov_vcn_4_0_0_video_codecs_encode_awway_vcn1,
};

static stwuct amdgpu_video_codec_info swiov_vcn_4_0_0_video_codecs_decode_awway_vcn0[] = {
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2, 4096, 4096, 3)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4, 4096, 4096, 5)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 4096, 52)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1, 4096, 4096, 4)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 8192, 4352, 186)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG, 4096, 4096, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9, 8192, 4352, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_AV1, 8192, 4352, 0)},
};

static stwuct amdgpu_video_codec_info swiov_vcn_4_0_0_video_codecs_decode_awway_vcn1[] = {
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2, 4096, 4096, 3)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4, 4096, 4096, 5)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 4096, 52)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1, 4096, 4096, 4)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 8192, 4352, 186)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG, 4096, 4096, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9, 8192, 4352, 0)},
};

static stwuct amdgpu_video_codecs swiov_vcn_4_0_0_video_codecs_decode_vcn0 = {
	.codec_count = AWWAY_SIZE(swiov_vcn_4_0_0_video_codecs_decode_awway_vcn0),
	.codec_awway = swiov_vcn_4_0_0_video_codecs_decode_awway_vcn0,
};

static stwuct amdgpu_video_codecs swiov_vcn_4_0_0_video_codecs_decode_vcn1 = {
	.codec_count = AWWAY_SIZE(swiov_vcn_4_0_0_video_codecs_decode_awway_vcn1),
	.codec_awway = swiov_vcn_4_0_0_video_codecs_decode_awway_vcn1,
};

static int soc21_quewy_video_codecs(stwuct amdgpu_device *adev, boow encode,
				 const stwuct amdgpu_video_codecs **codecs)
{
	if (adev->vcn.num_vcn_inst == hweight8(adev->vcn.hawvest_config))
		wetuwn -EINVAW;

	switch (amdgpu_ip_vewsion(adev, UVD_HWIP, 0)) {
	case IP_VEWSION(4, 0, 0):
	case IP_VEWSION(4, 0, 2):
	case IP_VEWSION(4, 0, 4):
	case IP_VEWSION(4, 0, 5):
		if (amdgpu_swiov_vf(adev)) {
			if ((adev->vcn.hawvest_config & AMDGPU_VCN_HAWVEST_VCN0) ||
			!amdgpu_swiov_is_av1_suppowt(adev)) {
				if (encode)
					*codecs = &swiov_vcn_4_0_0_video_codecs_encode_vcn1;
				ewse
					*codecs = &swiov_vcn_4_0_0_video_codecs_decode_vcn1;
			} ewse {
				if (encode)
					*codecs = &swiov_vcn_4_0_0_video_codecs_encode_vcn0;
				ewse
					*codecs = &swiov_vcn_4_0_0_video_codecs_decode_vcn0;
			}
		} ewse {
			if ((adev->vcn.hawvest_config & AMDGPU_VCN_HAWVEST_VCN0)) {
				if (encode)
					*codecs = &vcn_4_0_0_video_codecs_encode_vcn1;
				ewse
					*codecs = &vcn_4_0_0_video_codecs_decode_vcn1;
			} ewse {
				if (encode)
					*codecs = &vcn_4_0_0_video_codecs_encode_vcn0;
				ewse
					*codecs = &vcn_4_0_0_video_codecs_decode_vcn0;
			}
		}
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static u32 soc21_didt_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags, addwess, data;
	u32 w;

	addwess = SOC15_WEG_OFFSET(GC, 0, wegDIDT_IND_INDEX);
	data = SOC15_WEG_OFFSET(GC, 0, wegDIDT_IND_DATA);

	spin_wock_iwqsave(&adev->didt_idx_wock, fwags);
	WWEG32(addwess, (weg));
	w = WWEG32(data);
	spin_unwock_iwqwestowe(&adev->didt_idx_wock, fwags);
	wetuwn w;
}

static void soc21_didt_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags, addwess, data;

	addwess = SOC15_WEG_OFFSET(GC, 0, wegDIDT_IND_INDEX);
	data = SOC15_WEG_OFFSET(GC, 0, wegDIDT_IND_DATA);

	spin_wock_iwqsave(&adev->didt_idx_wock, fwags);
	WWEG32(addwess, (weg));
	WWEG32(data, (v));
	spin_unwock_iwqwestowe(&adev->didt_idx_wock, fwags);
}

static u32 soc21_get_config_memsize(stwuct amdgpu_device *adev)
{
	wetuwn adev->nbio.funcs->get_memsize(adev);
}

static u32 soc21_get_xcwk(stwuct amdgpu_device *adev)
{
	wetuwn adev->cwock.spww.wefewence_fweq;
}


void soc21_gwbm_sewect(stwuct amdgpu_device *adev,
		     u32 me, u32 pipe, u32 queue, u32 vmid)
{
	u32 gwbm_gfx_cntw = 0;
	gwbm_gfx_cntw = WEG_SET_FIEWD(gwbm_gfx_cntw, GWBM_GFX_CNTW, PIPEID, pipe);
	gwbm_gfx_cntw = WEG_SET_FIEWD(gwbm_gfx_cntw, GWBM_GFX_CNTW, MEID, me);
	gwbm_gfx_cntw = WEG_SET_FIEWD(gwbm_gfx_cntw, GWBM_GFX_CNTW, VMID, vmid);
	gwbm_gfx_cntw = WEG_SET_FIEWD(gwbm_gfx_cntw, GWBM_GFX_CNTW, QUEUEID, queue);

	WWEG32_SOC15(GC, 0, wegGWBM_GFX_CNTW, gwbm_gfx_cntw);
}

static boow soc21_wead_disabwed_bios(stwuct amdgpu_device *adev)
{
	/* todo */
	wetuwn fawse;
}

static stwuct soc15_awwowed_wegistew_entwy soc21_awwowed_wead_wegistews[] = {
	{ SOC15_WEG_ENTWY(GC, 0, wegGWBM_STATUS)},
	{ SOC15_WEG_ENTWY(GC, 0, wegGWBM_STATUS2)},
	{ SOC15_WEG_ENTWY(GC, 0, wegGWBM_STATUS_SE0)},
	{ SOC15_WEG_ENTWY(GC, 0, wegGWBM_STATUS_SE1)},
	{ SOC15_WEG_ENTWY(GC, 0, wegGWBM_STATUS_SE2)},
	{ SOC15_WEG_ENTWY(GC, 0, wegGWBM_STATUS_SE3)},
	{ SOC15_WEG_ENTWY(SDMA0, 0, wegSDMA0_STATUS_WEG)},
	{ SOC15_WEG_ENTWY(SDMA1, 0, wegSDMA1_STATUS_WEG)},
	{ SOC15_WEG_ENTWY(GC, 0, wegCP_STAT)},
	{ SOC15_WEG_ENTWY(GC, 0, wegCP_STAWWED_STAT1)},
	{ SOC15_WEG_ENTWY(GC, 0, wegCP_STAWWED_STAT2)},
	{ SOC15_WEG_ENTWY(GC, 0, wegCP_STAWWED_STAT3)},
	{ SOC15_WEG_ENTWY(GC, 0, wegCP_CPF_BUSY_STAT)},
	{ SOC15_WEG_ENTWY(GC, 0, wegCP_CPF_STAWWED_STAT1)},
	{ SOC15_WEG_ENTWY(GC, 0, wegCP_CPF_STATUS)},
	{ SOC15_WEG_ENTWY(GC, 0, wegCP_CPC_BUSY_STAT)},
	{ SOC15_WEG_ENTWY(GC, 0, wegCP_CPC_STAWWED_STAT1)},
	{ SOC15_WEG_ENTWY(GC, 0, wegCP_CPC_STATUS)},
	{ SOC15_WEG_ENTWY(GC, 0, wegGB_ADDW_CONFIG)},
};

static uint32_t soc21_wead_indexed_wegistew(stwuct amdgpu_device *adev, u32 se_num,
					 u32 sh_num, u32 weg_offset)
{
	uint32_t vaw;

	mutex_wock(&adev->gwbm_idx_mutex);
	if (se_num != 0xffffffff || sh_num != 0xffffffff)
		amdgpu_gfx_sewect_se_sh(adev, se_num, sh_num, 0xffffffff, 0);

	vaw = WWEG32(weg_offset);

	if (se_num != 0xffffffff || sh_num != 0xffffffff)
		amdgpu_gfx_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
	mutex_unwock(&adev->gwbm_idx_mutex);
	wetuwn vaw;
}

static uint32_t soc21_get_wegistew_vawue(stwuct amdgpu_device *adev,
				      boow indexed, u32 se_num,
				      u32 sh_num, u32 weg_offset)
{
	if (indexed) {
		wetuwn soc21_wead_indexed_wegistew(adev, se_num, sh_num, weg_offset);
	} ewse {
		if (weg_offset == SOC15_WEG_OFFSET(GC, 0, wegGB_ADDW_CONFIG) && adev->gfx.config.gb_addw_config)
			wetuwn adev->gfx.config.gb_addw_config;
		wetuwn WWEG32(weg_offset);
	}
}

static int soc21_wead_wegistew(stwuct amdgpu_device *adev, u32 se_num,
			    u32 sh_num, u32 weg_offset, u32 *vawue)
{
	uint32_t i;
	stwuct soc15_awwowed_wegistew_entwy  *en;

	*vawue = 0;
	fow (i = 0; i < AWWAY_SIZE(soc21_awwowed_wead_wegistews); i++) {
		en = &soc21_awwowed_wead_wegistews[i];
		if (!adev->weg_offset[en->hwip][en->inst])
			continue;
		ewse if (weg_offset != (adev->weg_offset[en->hwip][en->inst][en->seg]
					+ en->weg_offset))
			continue;

		*vawue = soc21_get_wegistew_vawue(adev,
					       soc21_awwowed_wead_wegistews[i].gwbm_indexed,
					       se_num, sh_num, weg_offset);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

#if 0
static int soc21_asic_mode1_weset(stwuct amdgpu_device *adev)
{
	u32 i;
	int wet = 0;

	amdgpu_atombios_scwatch_wegs_engine_hung(adev, twue);

	/* disabwe BM */
	pci_cweaw_mastew(adev->pdev);

	amdgpu_device_cache_pci_state(adev->pdev);

	if (amdgpu_dpm_is_mode1_weset_suppowted(adev)) {
		dev_info(adev->dev, "GPU smu mode1 weset\n");
		wet = amdgpu_dpm_mode1_weset(adev);
	} ewse {
		dev_info(adev->dev, "GPU psp mode1 weset\n");
		wet = psp_gpu_weset(adev);
	}

	if (wet)
		dev_eww(adev->dev, "GPU mode1 weset faiwed\n");
	amdgpu_device_woad_pci_state(adev->pdev);

	/* wait fow asic to come out of weset */
	fow (i = 0; i < adev->usec_timeout; i++) {
		u32 memsize = adev->nbio.funcs->get_memsize(adev);

		if (memsize != 0xffffffff)
			bweak;
		udeway(1);
	}

	amdgpu_atombios_scwatch_wegs_engine_hung(adev, fawse);

	wetuwn wet;
}
#endif

static enum amd_weset_method
soc21_asic_weset_method(stwuct amdgpu_device *adev)
{
	if (amdgpu_weset_method == AMD_WESET_METHOD_MODE1 ||
	    amdgpu_weset_method == AMD_WESET_METHOD_MODE2 ||
	    amdgpu_weset_method == AMD_WESET_METHOD_BACO)
		wetuwn amdgpu_weset_method;

	if (amdgpu_weset_method != -1)
		dev_wawn(adev->dev, "Specified weset method:%d isn't suppowted, using AUTO instead.\n",
				  amdgpu_weset_method);

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(13, 0, 0):
	case IP_VEWSION(13, 0, 7):
	case IP_VEWSION(13, 0, 10):
		wetuwn AMD_WESET_METHOD_MODE1;
	case IP_VEWSION(13, 0, 4):
	case IP_VEWSION(13, 0, 11):
	case IP_VEWSION(14, 0, 0):
		wetuwn AMD_WESET_METHOD_MODE2;
	defauwt:
		if (amdgpu_dpm_is_baco_suppowted(adev))
			wetuwn AMD_WESET_METHOD_BACO;
		ewse
			wetuwn AMD_WESET_METHOD_MODE1;
	}
}

static int soc21_asic_weset(stwuct amdgpu_device *adev)
{
	int wet = 0;

	switch (soc21_asic_weset_method(adev)) {
	case AMD_WESET_METHOD_PCI:
		dev_info(adev->dev, "PCI weset\n");
		wet = amdgpu_device_pci_weset(adev);
		bweak;
	case AMD_WESET_METHOD_BACO:
		dev_info(adev->dev, "BACO weset\n");
		wet = amdgpu_dpm_baco_weset(adev);
		bweak;
	case AMD_WESET_METHOD_MODE2:
		dev_info(adev->dev, "MODE2 weset\n");
		wet = amdgpu_dpm_mode2_weset(adev);
		bweak;
	defauwt:
		dev_info(adev->dev, "MODE1 weset\n");
		wet = amdgpu_device_mode1_weset(adev);
		bweak;
	}

	wetuwn wet;
}

static int soc21_set_uvd_cwocks(stwuct amdgpu_device *adev, u32 vcwk, u32 dcwk)
{
	/* todo */
	wetuwn 0;
}

static int soc21_set_vce_cwocks(stwuct amdgpu_device *adev, u32 evcwk, u32 eccwk)
{
	/* todo */
	wetuwn 0;
}

static void soc21_pwogwam_aspm(stwuct amdgpu_device *adev)
{
	if (!amdgpu_device_shouwd_use_aspm(adev))
		wetuwn;

	if (adev->nbio.funcs->pwogwam_aspm)
		adev->nbio.funcs->pwogwam_aspm(adev);
}

const stwuct amdgpu_ip_bwock_vewsion soc21_common_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_COMMON,
	.majow = 1,
	.minow = 0,
	.wev = 0,
	.funcs = &soc21_common_ip_funcs,
};

static boow soc21_need_fuww_weset(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(11, 0, 0):
		wetuwn amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__UMC);
	case IP_VEWSION(11, 0, 2):
	case IP_VEWSION(11, 0, 3):
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static boow soc21_need_weset_on_init(stwuct amdgpu_device *adev)
{
	u32 sow_weg;

	if (adev->fwags & AMD_IS_APU)
		wetuwn fawse;

	/* Check sOS sign of wife wegistew to confiwm sys dwivew and sOS
	 * awe awweady been woaded.
	 */
	sow_weg = WWEG32_SOC15(MP0, 0, wegMP0_SMN_C2PMSG_81);
	if (sow_weg)
		wetuwn twue;

	wetuwn fawse;
}

static void soc21_init_doowbeww_index(stwuct amdgpu_device *adev)
{
	adev->doowbeww_index.kiq = AMDGPU_NAVI10_DOOWBEWW_KIQ;
	adev->doowbeww_index.mec_wing0 = AMDGPU_NAVI10_DOOWBEWW_MEC_WING0;
	adev->doowbeww_index.mec_wing1 = AMDGPU_NAVI10_DOOWBEWW_MEC_WING1;
	adev->doowbeww_index.mec_wing2 = AMDGPU_NAVI10_DOOWBEWW_MEC_WING2;
	adev->doowbeww_index.mec_wing3 = AMDGPU_NAVI10_DOOWBEWW_MEC_WING3;
	adev->doowbeww_index.mec_wing4 = AMDGPU_NAVI10_DOOWBEWW_MEC_WING4;
	adev->doowbeww_index.mec_wing5 = AMDGPU_NAVI10_DOOWBEWW_MEC_WING5;
	adev->doowbeww_index.mec_wing6 = AMDGPU_NAVI10_DOOWBEWW_MEC_WING6;
	adev->doowbeww_index.mec_wing7 = AMDGPU_NAVI10_DOOWBEWW_MEC_WING7;
	adev->doowbeww_index.usewqueue_stawt = AMDGPU_NAVI10_DOOWBEWW_USEWQUEUE_STAWT;
	adev->doowbeww_index.usewqueue_end = AMDGPU_NAVI10_DOOWBEWW_USEWQUEUE_END;
	adev->doowbeww_index.gfx_wing0 = AMDGPU_NAVI10_DOOWBEWW_GFX_WING0;
	adev->doowbeww_index.gfx_wing1 = AMDGPU_NAVI10_DOOWBEWW_GFX_WING1;
	adev->doowbeww_index.gfx_usewqueue_stawt =
		AMDGPU_NAVI10_DOOWBEWW_GFX_USEWQUEUE_STAWT;
	adev->doowbeww_index.gfx_usewqueue_end =
		AMDGPU_NAVI10_DOOWBEWW_GFX_USEWQUEUE_END;
	adev->doowbeww_index.mes_wing0 = AMDGPU_NAVI10_DOOWBEWW_MES_WING0;
	adev->doowbeww_index.mes_wing1 = AMDGPU_NAVI10_DOOWBEWW_MES_WING1;
	adev->doowbeww_index.sdma_engine[0] = AMDGPU_NAVI10_DOOWBEWW_sDMA_ENGINE0;
	adev->doowbeww_index.sdma_engine[1] = AMDGPU_NAVI10_DOOWBEWW_sDMA_ENGINE1;
	adev->doowbeww_index.ih = AMDGPU_NAVI10_DOOWBEWW_IH;
	adev->doowbeww_index.vcn.vcn_wing0_1 = AMDGPU_NAVI10_DOOWBEWW64_VCN0_1;
	adev->doowbeww_index.vcn.vcn_wing2_3 = AMDGPU_NAVI10_DOOWBEWW64_VCN2_3;
	adev->doowbeww_index.vcn.vcn_wing4_5 = AMDGPU_NAVI10_DOOWBEWW64_VCN4_5;
	adev->doowbeww_index.vcn.vcn_wing6_7 = AMDGPU_NAVI10_DOOWBEWW64_VCN6_7;
	adev->doowbeww_index.vpe_wing = AMDGPU_NAVI10_DOOWBEWW64_VPE;
	adev->doowbeww_index.fiwst_non_cp = AMDGPU_NAVI10_DOOWBEWW64_FIWST_NON_CP;
	adev->doowbeww_index.wast_non_cp = AMDGPU_NAVI10_DOOWBEWW64_WAST_NON_CP;

	adev->doowbeww_index.max_assignment = AMDGPU_NAVI10_DOOWBEWW_MAX_ASSIGNMENT << 1;
	adev->doowbeww_index.sdma_doowbeww_wange = 20;
}

static void soc21_pwe_asic_init(stwuct amdgpu_device *adev)
{
}

static int soc21_update_umd_stabwe_pstate(stwuct amdgpu_device *adev,
					  boow entew)
{
	if (entew)
		amdgpu_gfx_wwc_entew_safe_mode(adev, 0);
	ewse
		amdgpu_gfx_wwc_exit_safe_mode(adev, 0);

	if (adev->gfx.funcs->update_pewfmon_mgcg)
		adev->gfx.funcs->update_pewfmon_mgcg(adev, !entew);

	wetuwn 0;
}

static const stwuct amdgpu_asic_funcs soc21_asic_funcs = {
	.wead_disabwed_bios = &soc21_wead_disabwed_bios,
	.wead_bios_fwom_wom = &amdgpu_soc15_wead_bios_fwom_wom,
	.wead_wegistew = &soc21_wead_wegistew,
	.weset = &soc21_asic_weset,
	.weset_method = &soc21_asic_weset_method,
	.get_xcwk = &soc21_get_xcwk,
	.set_uvd_cwocks = &soc21_set_uvd_cwocks,
	.set_vce_cwocks = &soc21_set_vce_cwocks,
	.get_config_memsize = &soc21_get_config_memsize,
	.init_doowbeww_index = &soc21_init_doowbeww_index,
	.need_fuww_weset = &soc21_need_fuww_weset,
	.need_weset_on_init = &soc21_need_weset_on_init,
	.get_pcie_wepway_count = &amdgpu_nbio_get_pcie_wepway_count,
	.suppowts_baco = &amdgpu_dpm_is_baco_suppowted,
	.pwe_asic_init = &soc21_pwe_asic_init,
	.quewy_video_codecs = &soc21_quewy_video_codecs,
	.update_umd_stabwe_pstate = &soc21_update_umd_stabwe_pstate,
};

static int soc21_common_eawwy_init(void *handwe)
{
#define MMIO_WEG_HOWE_OFFSET (0x80000 - PAGE_SIZE)
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->wmmio_wemap.weg_offset = MMIO_WEG_HOWE_OFFSET;
	adev->wmmio_wemap.bus_addw = adev->wmmio_base + MMIO_WEG_HOWE_OFFSET;
	adev->smc_wweg = NUWW;
	adev->smc_wweg = NUWW;
	adev->pcie_wweg = &amdgpu_device_indiwect_wweg;
	adev->pcie_wweg = &amdgpu_device_indiwect_wweg;
	adev->pcie_wweg64 = &amdgpu_device_indiwect_wweg64;
	adev->pcie_wweg64 = &amdgpu_device_indiwect_wweg64;
	adev->pciep_wweg = amdgpu_device_pcie_powt_wweg;
	adev->pciep_wweg = amdgpu_device_pcie_powt_wweg;

	/* TODO: wiww add them duwing VCN v2 impwementation */
	adev->uvd_ctx_wweg = NUWW;
	adev->uvd_ctx_wweg = NUWW;

	adev->didt_wweg = &soc21_didt_wweg;
	adev->didt_wweg = &soc21_didt_wweg;

	adev->asic_funcs = &soc21_asic_funcs;

	adev->wev_id = amdgpu_device_get_wev_id(adev);
	adev->extewnaw_wev_id = 0xff;
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(11, 0, 0):
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
#if 0
			AMD_CG_SUPPOWT_GFX_3D_CGCG |
			AMD_CG_SUPPOWT_GFX_3D_CGWS |
#endif
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_WEPEATEW_FGCG |
			AMD_CG_SUPPOWT_GFX_FGCG |
			AMD_CG_SUPPOWT_GFX_PEWF_CWK |
			AMD_CG_SUPPOWT_VCN_MGCG |
			AMD_CG_SUPPOWT_JPEG_MGCG |
			AMD_CG_SUPPOWT_ATHUB_MGCG |
			AMD_CG_SUPPOWT_ATHUB_WS |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_IH_CG |
			AMD_CG_SUPPOWT_HDP_SD;
		adev->pg_fwags = AMD_PG_SUPPOWT_VCN |
			AMD_PG_SUPPOWT_VCN_DPG |
			AMD_PG_SUPPOWT_JPEG |
			AMD_PG_SUPPOWT_ATHUB |
			AMD_PG_SUPPOWT_MMHUB;
		adev->extewnaw_wev_id = adev->wev_id + 0x1; // TODO: need update
		bweak;
	case IP_VEWSION(11, 0, 2):
		adev->cg_fwags =
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_WEPEATEW_FGCG |
			AMD_CG_SUPPOWT_VCN_MGCG |
			AMD_CG_SUPPOWT_JPEG_MGCG |
			AMD_CG_SUPPOWT_ATHUB_MGCG |
			AMD_CG_SUPPOWT_ATHUB_WS |
			AMD_CG_SUPPOWT_IH_CG |
			AMD_CG_SUPPOWT_HDP_SD;
		adev->pg_fwags =
			AMD_PG_SUPPOWT_VCN |
			AMD_PG_SUPPOWT_VCN_DPG |
			AMD_PG_SUPPOWT_JPEG |
			AMD_PG_SUPPOWT_ATHUB |
			AMD_PG_SUPPOWT_MMHUB;
		adev->extewnaw_wev_id = adev->wev_id + 0x10;
		bweak;
	case IP_VEWSION(11, 0, 1):
		adev->cg_fwags =
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_FGCG |
			AMD_CG_SUPPOWT_WEPEATEW_FGCG |
			AMD_CG_SUPPOWT_GFX_PEWF_CWK |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_ATHUB_MGCG |
			AMD_CG_SUPPOWT_ATHUB_WS |
			AMD_CG_SUPPOWT_IH_CG |
			AMD_CG_SUPPOWT_BIF_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_VCN_MGCG |
			AMD_CG_SUPPOWT_JPEG_MGCG;
		adev->pg_fwags =
			AMD_PG_SUPPOWT_GFX_PG |
			AMD_PG_SUPPOWT_VCN |
			AMD_PG_SUPPOWT_VCN_DPG |
			AMD_PG_SUPPOWT_JPEG;
		adev->extewnaw_wev_id = adev->wev_id + 0x1;
		bweak;
	case IP_VEWSION(11, 0, 3):
		adev->cg_fwags = AMD_CG_SUPPOWT_VCN_MGCG |
			AMD_CG_SUPPOWT_JPEG_MGCG |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_WEPEATEW_FGCG |
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_HDP_SD |
			AMD_CG_SUPPOWT_ATHUB_MGCG |
			AMD_CG_SUPPOWT_ATHUB_WS;
		adev->pg_fwags = AMD_PG_SUPPOWT_VCN |
			AMD_PG_SUPPOWT_VCN_DPG |
			AMD_PG_SUPPOWT_JPEG;
		adev->extewnaw_wev_id = adev->wev_id + 0x20;
		bweak;
	case IP_VEWSION(11, 0, 4):
		adev->cg_fwags =
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_FGCG |
			AMD_CG_SUPPOWT_WEPEATEW_FGCG |
			AMD_CG_SUPPOWT_GFX_PEWF_CWK |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_ATHUB_MGCG |
			AMD_CG_SUPPOWT_ATHUB_WS |
			AMD_CG_SUPPOWT_IH_CG |
			AMD_CG_SUPPOWT_BIF_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_VCN_MGCG |
			AMD_CG_SUPPOWT_JPEG_MGCG;
		adev->pg_fwags = AMD_PG_SUPPOWT_VCN |
			AMD_PG_SUPPOWT_VCN_DPG |
			AMD_PG_SUPPOWT_GFX_PG |
			AMD_PG_SUPPOWT_JPEG;
		adev->extewnaw_wev_id = adev->wev_id + 0x80;
		bweak;
	case IP_VEWSION(11, 5, 0):
		adev->cg_fwags = AMD_CG_SUPPOWT_VCN_MGCG |
			AMD_CG_SUPPOWT_JPEG_MGCG |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_FGCG |
			AMD_CG_SUPPOWT_WEPEATEW_FGCG |
			AMD_CG_SUPPOWT_GFX_PEWF_CWK	|
			AMD_CG_SUPPOWT_GFX_3D_CGCG |
			AMD_CG_SUPPOWT_GFX_3D_CGWS	|
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_HDP_DS |
			AMD_CG_SUPPOWT_HDP_SD |
			AMD_CG_SUPPOWT_ATHUB_MGCG |
			AMD_CG_SUPPOWT_ATHUB_WS |
			AMD_CG_SUPPOWT_IH_CG |
			AMD_CG_SUPPOWT_BIF_MGCG |
			AMD_CG_SUPPOWT_BIF_WS;
		adev->pg_fwags = AMD_PG_SUPPOWT_VCN_DPG |
			AMD_PG_SUPPOWT_VCN |
			AMD_PG_SUPPOWT_JPEG |
			AMD_PG_SUPPOWT_GFX_PG;
		adev->extewnaw_wev_id = adev->wev_id + 0x1;
		bweak;
	defauwt:
		/* FIXME: not suppowted yet */
		wetuwn -EINVAW;
	}

	if (amdgpu_swiov_vf(adev)) {
		amdgpu_viwt_init_setting(adev);
		xgpu_nv_maiwbox_set_iwq_funcs(adev);
	}

	wetuwn 0;
}

static int soc21_common_wate_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev)) {
		xgpu_nv_maiwbox_get_iwq(adev);
		if ((adev->vcn.hawvest_config & AMDGPU_VCN_HAWVEST_VCN0) ||
		!amdgpu_swiov_is_av1_suppowt(adev)) {
			amdgpu_viwt_update_swiov_video_codec(adev,
							     swiov_vcn_4_0_0_video_codecs_encode_awway_vcn1,
							     AWWAY_SIZE(swiov_vcn_4_0_0_video_codecs_encode_awway_vcn1),
							     swiov_vcn_4_0_0_video_codecs_decode_awway_vcn1,
							     AWWAY_SIZE(swiov_vcn_4_0_0_video_codecs_decode_awway_vcn1));
		} ewse {
			amdgpu_viwt_update_swiov_video_codec(adev,
							     swiov_vcn_4_0_0_video_codecs_encode_awway_vcn0,
							     AWWAY_SIZE(swiov_vcn_4_0_0_video_codecs_encode_awway_vcn0),
							     swiov_vcn_4_0_0_video_codecs_decode_awway_vcn0,
							     AWWAY_SIZE(swiov_vcn_4_0_0_video_codecs_decode_awway_vcn0));
		}
	} ewse {
		if (adev->nbio.was &&
		    adev->nbio.was_eww_event_athub_iwq.funcs)
			/* don't need to faiw gpu wate init
			 * if enabwing athub_eww_event intewwupt faiwed
			 * nbio v4_3 onwy suppowt fataw ewwow hanwding
			 * just enabwe the intewwupt diwectwy */
			amdgpu_iwq_get(adev, &adev->nbio.was_eww_event_athub_iwq, 0);
	}

	/* Enabwe sewfwing doowbeww apewtuwe wate because doowbeww BAW
	 * apewtuwe wiww change if wesize BAW successfuwwy in gmc sw_init.
	 */
	adev->nbio.funcs->enabwe_doowbeww_sewfwing_apewtuwe(adev, twue);

	wetuwn 0;
}

static int soc21_common_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		xgpu_nv_maiwbox_add_iwq_id(adev);

	wetuwn 0;
}

static int soc21_common_sw_fini(void *handwe)
{
	wetuwn 0;
}

static int soc21_common_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* enabwe aspm */
	soc21_pwogwam_aspm(adev);
	/* setup nbio wegistews */
	adev->nbio.funcs->init_wegistews(adev);
	/* wemap HDP wegistews to a howe in mmio space,
	 * fow the puwpose of expose those wegistews
	 * to pwocess space
	 */
	if (adev->nbio.funcs->wemap_hdp_wegistews && !amdgpu_swiov_vf(adev))
		adev->nbio.funcs->wemap_hdp_wegistews(adev);
	/* enabwe the doowbeww apewtuwe */
	adev->nbio.funcs->enabwe_doowbeww_apewtuwe(adev, twue);

	wetuwn 0;
}

static int soc21_common_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* Disabwe the doowbeww apewtuwe and sewfwing doowbeww apewtuwe
	 * sepawatewy in hw_fini because soc21_enabwe_doowbeww_apewtuwe
	 * has been wemoved and thewe is no need to deway disabwing
	 * sewfwing doowbeww.
	 */
	adev->nbio.funcs->enabwe_doowbeww_apewtuwe(adev, fawse);
	adev->nbio.funcs->enabwe_doowbeww_sewfwing_apewtuwe(adev, fawse);

	if (amdgpu_swiov_vf(adev)) {
		xgpu_nv_maiwbox_put_iwq(adev);
	} ewse {
		if (adev->nbio.was &&
		    adev->nbio.was_eww_event_athub_iwq.funcs)
			amdgpu_iwq_put(adev, &adev->nbio.was_eww_event_athub_iwq, 0);
	}

	wetuwn 0;
}

static int soc21_common_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn soc21_common_hw_fini(adev);
}

static int soc21_common_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn soc21_common_hw_init(adev);
}

static boow soc21_common_is_idwe(void *handwe)
{
	wetuwn twue;
}

static int soc21_common_wait_fow_idwe(void *handwe)
{
	wetuwn 0;
}

static int soc21_common_soft_weset(void *handwe)
{
	wetuwn 0;
}

static int soc21_common_set_cwockgating_state(void *handwe,
					   enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	switch (amdgpu_ip_vewsion(adev, NBIO_HWIP, 0)) {
	case IP_VEWSION(4, 3, 0):
	case IP_VEWSION(4, 3, 1):
	case IP_VEWSION(7, 7, 0):
	case IP_VEWSION(7, 7, 1):
	case IP_VEWSION(7, 11, 0):
		adev->nbio.funcs->update_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		adev->nbio.funcs->update_medium_gwain_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		adev->hdp.funcs->update_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int soc21_common_set_powewgating_state(void *handwe,
					   enum amd_powewgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	switch (amdgpu_ip_vewsion(adev, WSDMA_HWIP, 0)) {
	case IP_VEWSION(6, 0, 0):
	case IP_VEWSION(6, 0, 2):
		adev->wsdma.funcs->update_memowy_powew_gating(adev,
				state == AMD_PG_STATE_GATE);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void soc21_common_get_cwockgating_state(void *handwe, u64 *fwags)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->nbio.funcs->get_cwockgating_state(adev, fwags);

	adev->hdp.funcs->get_cwock_gating_state(adev, fwags);
}

static const stwuct amd_ip_funcs soc21_common_ip_funcs = {
	.name = "soc21_common",
	.eawwy_init = soc21_common_eawwy_init,
	.wate_init = soc21_common_wate_init,
	.sw_init = soc21_common_sw_init,
	.sw_fini = soc21_common_sw_fini,
	.hw_init = soc21_common_hw_init,
	.hw_fini = soc21_common_hw_fini,
	.suspend = soc21_common_suspend,
	.wesume = soc21_common_wesume,
	.is_idwe = soc21_common_is_idwe,
	.wait_fow_idwe = soc21_common_wait_fow_idwe,
	.soft_weset = soc21_common_soft_weset,
	.set_cwockgating_state = soc21_common_set_cwockgating_state,
	.set_powewgating_state = soc21_common_set_powewgating_state,
	.get_cwockgating_state = soc21_common_get_cwockgating_state,
};
