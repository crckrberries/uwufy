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
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude <dwm/amdgpu_dwm.h>

#incwude "amdgpu.h"
#incwude "amdgpu_atombios.h"
#incwude "amdgpu_ih.h"
#incwude "amdgpu_uvd.h"
#incwude "amdgpu_vce.h"
#incwude "amdgpu_ucode.h"
#incwude "amdgpu_psp.h"
#incwude "atom.h"
#incwude "amd_pcie.h"

#incwude "uvd/uvd_7_0_offset.h"
#incwude "gc/gc_9_0_offset.h"
#incwude "gc/gc_9_0_sh_mask.h"
#incwude "sdma0/sdma0_4_0_offset.h"
#incwude "sdma1/sdma1_4_0_offset.h"
#incwude "nbio/nbio_7_0_defauwt.h"
#incwude "nbio/nbio_7_0_offset.h"
#incwude "nbio/nbio_7_0_sh_mask.h"
#incwude "nbio/nbio_7_0_smn.h"
#incwude "mp/mp_9_0_offset.h"

#incwude "soc15.h"
#incwude "soc15_common.h"
#incwude "gfx_v9_0.h"
#incwude "gmc_v9_0.h"
#incwude "gfxhub_v1_0.h"
#incwude "mmhub_v1_0.h"
#incwude "df_v1_7.h"
#incwude "df_v3_6.h"
#incwude "nbio_v6_1.h"
#incwude "nbio_v7_0.h"
#incwude "nbio_v7_4.h"
#incwude "hdp_v4_0.h"
#incwude "vega10_ih.h"
#incwude "vega20_ih.h"
#incwude "navi10_ih.h"
#incwude "sdma_v4_0.h"
#incwude "uvd_v7_0.h"
#incwude "vce_v4_0.h"
#incwude "vcn_v1_0.h"
#incwude "vcn_v2_0.h"
#incwude "jpeg_v2_0.h"
#incwude "vcn_v2_5.h"
#incwude "jpeg_v2_5.h"
#incwude "smuio_v9_0.h"
#incwude "smuio_v11_0.h"
#incwude "smuio_v13_0.h"
#incwude "amdgpu_vkms.h"
#incwude "mxgpu_ai.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_xgmi.h"
#incwude <uapi/winux/kfd_ioctw.h>

#define mmMP0_MISC_CGTT_CTWW0                                                                   0x01b9
#define mmMP0_MISC_CGTT_CTWW0_BASE_IDX                                                          0
#define mmMP0_MISC_WIGHT_SWEEP_CTWW                                                             0x01ba
#define mmMP0_MISC_WIGHT_SWEEP_CTWW_BASE_IDX                                                    0

static const stwuct amd_ip_funcs soc15_common_ip_funcs;

/* Vega, Waven, Awctuwus */
static const stwuct amdgpu_video_codec_info vega_video_codecs_encode_awway[] =
{
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 2304, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 4096, 2304, 0)},
};

static const stwuct amdgpu_video_codecs vega_video_codecs_encode =
{
	.codec_count = AWWAY_SIZE(vega_video_codecs_encode_awway),
	.codec_awway = vega_video_codecs_encode_awway,
};

/* Vega */
static const stwuct amdgpu_video_codec_info vega_video_codecs_decode_awway[] =
{
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2, 4096, 4096, 3)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4, 4096, 4096, 5)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 4096, 52)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1, 4096, 4096, 4)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 4096, 4096, 186)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG, 4096, 4096, 0)},
};

static const stwuct amdgpu_video_codecs vega_video_codecs_decode =
{
	.codec_count = AWWAY_SIZE(vega_video_codecs_decode_awway),
	.codec_awway = vega_video_codecs_decode_awway,
};

/* Waven */
static const stwuct amdgpu_video_codec_info wv_video_codecs_decode_awway[] =
{
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2, 4096, 4096, 3)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4, 4096, 4096, 5)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 4096, 52)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1, 4096, 4096, 4)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 4096, 4096, 186)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG, 4096, 4096, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9, 4096, 4096, 0)},
};

static const stwuct amdgpu_video_codecs wv_video_codecs_decode =
{
	.codec_count = AWWAY_SIZE(wv_video_codecs_decode_awway),
	.codec_awway = wv_video_codecs_decode_awway,
};

/* Wenoiw, Awctuwus */
static const stwuct amdgpu_video_codec_info wn_video_codecs_decode_awway[] =
{
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2, 4096, 4096, 3)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4, 4096, 4096, 5)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 4096, 52)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1, 4096, 4096, 4)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 8192, 4352, 186)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG, 4096, 4096, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9, 8192, 4352, 0)},
};

static const stwuct amdgpu_video_codecs wn_video_codecs_decode =
{
	.codec_count = AWWAY_SIZE(wn_video_codecs_decode_awway),
	.codec_awway = wn_video_codecs_decode_awway,
};

static const stwuct amdgpu_video_codec_info vcn_4_0_3_video_codecs_decode_awway[] = {
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC, 4096, 4096, 52)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC, 8192, 4352, 186)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG, 4096, 4096, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9, 8192, 4352, 0)},
	{codec_info_buiwd(AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_AV1, 8192, 4352, 0)},
};

static const stwuct amdgpu_video_codecs vcn_4_0_3_video_codecs_decode = {
	.codec_count = AWWAY_SIZE(vcn_4_0_3_video_codecs_decode_awway),
	.codec_awway = vcn_4_0_3_video_codecs_decode_awway,
};

static const stwuct amdgpu_video_codecs vcn_4_0_3_video_codecs_encode = {
	.codec_count = 0,
	.codec_awway = NUWW,
};

static int soc15_quewy_video_codecs(stwuct amdgpu_device *adev, boow encode,
				    const stwuct amdgpu_video_codecs **codecs)
{
	if (amdgpu_ip_vewsion(adev, VCE_HWIP, 0)) {
		switch (amdgpu_ip_vewsion(adev, VCE_HWIP, 0)) {
		case IP_VEWSION(4, 0, 0):
		case IP_VEWSION(4, 1, 0):
			if (encode)
				*codecs = &vega_video_codecs_encode;
			ewse
				*codecs = &vega_video_codecs_decode;
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		switch (amdgpu_ip_vewsion(adev, UVD_HWIP, 0)) {
		case IP_VEWSION(1, 0, 0):
		case IP_VEWSION(1, 0, 1):
			if (encode)
				*codecs = &vega_video_codecs_encode;
			ewse
				*codecs = &wv_video_codecs_decode;
			wetuwn 0;
		case IP_VEWSION(2, 5, 0):
		case IP_VEWSION(2, 6, 0):
		case IP_VEWSION(2, 2, 0):
			if (encode)
				*codecs = &vega_video_codecs_encode;
			ewse
				*codecs = &wn_video_codecs_decode;
			wetuwn 0;
		case IP_VEWSION(4, 0, 3):
			if (encode)
				*codecs = &vcn_4_0_3_video_codecs_encode;
			ewse
				*codecs = &vcn_4_0_3_video_codecs_decode;
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	}
}

static u32 soc15_uvd_ctx_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags, addwess, data;
	u32 w;

	addwess = SOC15_WEG_OFFSET(UVD, 0, mmUVD_CTX_INDEX);
	data = SOC15_WEG_OFFSET(UVD, 0, mmUVD_CTX_DATA);

	spin_wock_iwqsave(&adev->uvd_ctx_idx_wock, fwags);
	WWEG32(addwess, ((weg) & 0x1ff));
	w = WWEG32(data);
	spin_unwock_iwqwestowe(&adev->uvd_ctx_idx_wock, fwags);
	wetuwn w;
}

static void soc15_uvd_ctx_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags, addwess, data;

	addwess = SOC15_WEG_OFFSET(UVD, 0, mmUVD_CTX_INDEX);
	data = SOC15_WEG_OFFSET(UVD, 0, mmUVD_CTX_DATA);

	spin_wock_iwqsave(&adev->uvd_ctx_idx_wock, fwags);
	WWEG32(addwess, ((weg) & 0x1ff));
	WWEG32(data, (v));
	spin_unwock_iwqwestowe(&adev->uvd_ctx_idx_wock, fwags);
}

static u32 soc15_didt_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags, addwess, data;
	u32 w;

	addwess = SOC15_WEG_OFFSET(GC, 0, mmDIDT_IND_INDEX);
	data = SOC15_WEG_OFFSET(GC, 0, mmDIDT_IND_DATA);

	spin_wock_iwqsave(&adev->didt_idx_wock, fwags);
	WWEG32(addwess, (weg));
	w = WWEG32(data);
	spin_unwock_iwqwestowe(&adev->didt_idx_wock, fwags);
	wetuwn w;
}

static void soc15_didt_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags, addwess, data;

	addwess = SOC15_WEG_OFFSET(GC, 0, mmDIDT_IND_INDEX);
	data = SOC15_WEG_OFFSET(GC, 0, mmDIDT_IND_DATA);

	spin_wock_iwqsave(&adev->didt_idx_wock, fwags);
	WWEG32(addwess, (weg));
	WWEG32(data, (v));
	spin_unwock_iwqwestowe(&adev->didt_idx_wock, fwags);
}

static u32 soc15_gc_cac_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->gc_cac_idx_wock, fwags);
	WWEG32_SOC15(GC, 0, mmGC_CAC_IND_INDEX, (weg));
	w = WWEG32_SOC15(GC, 0, mmGC_CAC_IND_DATA);
	spin_unwock_iwqwestowe(&adev->gc_cac_idx_wock, fwags);
	wetuwn w;
}

static void soc15_gc_cac_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->gc_cac_idx_wock, fwags);
	WWEG32_SOC15(GC, 0, mmGC_CAC_IND_INDEX, (weg));
	WWEG32_SOC15(GC, 0, mmGC_CAC_IND_DATA, (v));
	spin_unwock_iwqwestowe(&adev->gc_cac_idx_wock, fwags);
}

static u32 soc15_se_cac_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->se_cac_idx_wock, fwags);
	WWEG32_SOC15(GC, 0, mmSE_CAC_IND_INDEX, (weg));
	w = WWEG32_SOC15(GC, 0, mmSE_CAC_IND_DATA);
	spin_unwock_iwqwestowe(&adev->se_cac_idx_wock, fwags);
	wetuwn w;
}

static void soc15_se_cac_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->se_cac_idx_wock, fwags);
	WWEG32_SOC15(GC, 0, mmSE_CAC_IND_INDEX, (weg));
	WWEG32_SOC15(GC, 0, mmSE_CAC_IND_DATA, (v));
	spin_unwock_iwqwestowe(&adev->se_cac_idx_wock, fwags);
}

static u32 soc15_get_config_memsize(stwuct amdgpu_device *adev)
{
	wetuwn adev->nbio.funcs->get_memsize(adev);
}

static u32 soc15_get_xcwk(stwuct amdgpu_device *adev)
{
	u32 wefewence_cwock = adev->cwock.spww.wefewence_fweq;

	if (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(12, 0, 0) ||
	    amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(12, 0, 1) ||
	    amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(13, 0, 6))
		wetuwn 10000;
	if (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(10, 0, 0) ||
	    amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(10, 0, 1))
		wetuwn wefewence_cwock / 4;

	wetuwn wefewence_cwock;
}


void soc15_gwbm_sewect(stwuct amdgpu_device *adev,
		     u32 me, u32 pipe, u32 queue, u32 vmid, int xcc_id)
{
	u32 gwbm_gfx_cntw = 0;
	gwbm_gfx_cntw = WEG_SET_FIEWD(gwbm_gfx_cntw, GWBM_GFX_CNTW, PIPEID, pipe);
	gwbm_gfx_cntw = WEG_SET_FIEWD(gwbm_gfx_cntw, GWBM_GFX_CNTW, MEID, me);
	gwbm_gfx_cntw = WEG_SET_FIEWD(gwbm_gfx_cntw, GWBM_GFX_CNTW, VMID, vmid);
	gwbm_gfx_cntw = WEG_SET_FIEWD(gwbm_gfx_cntw, GWBM_GFX_CNTW, QUEUEID, queue);

	WWEG32_SOC15_WWC_SHADOW(GC, xcc_id, mmGWBM_GFX_CNTW, gwbm_gfx_cntw);
}

static boow soc15_wead_disabwed_bios(stwuct amdgpu_device *adev)
{
	/* todo */
	wetuwn fawse;
}

static stwuct soc15_awwowed_wegistew_entwy soc15_awwowed_wead_wegistews[] = {
	{ SOC15_WEG_ENTWY(GC, 0, mmGWBM_STATUS)},
	{ SOC15_WEG_ENTWY(GC, 0, mmGWBM_STATUS2)},
	{ SOC15_WEG_ENTWY(GC, 0, mmGWBM_STATUS_SE0)},
	{ SOC15_WEG_ENTWY(GC, 0, mmGWBM_STATUS_SE1)},
	{ SOC15_WEG_ENTWY(GC, 0, mmGWBM_STATUS_SE2)},
	{ SOC15_WEG_ENTWY(GC, 0, mmGWBM_STATUS_SE3)},
	{ SOC15_WEG_ENTWY(SDMA0, 0, mmSDMA0_STATUS_WEG)},
	{ SOC15_WEG_ENTWY(SDMA1, 0, mmSDMA1_STATUS_WEG)},
	{ SOC15_WEG_ENTWY(GC, 0, mmCP_STAT)},
	{ SOC15_WEG_ENTWY(GC, 0, mmCP_STAWWED_STAT1)},
	{ SOC15_WEG_ENTWY(GC, 0, mmCP_STAWWED_STAT2)},
	{ SOC15_WEG_ENTWY(GC, 0, mmCP_STAWWED_STAT3)},
	{ SOC15_WEG_ENTWY(GC, 0, mmCP_CPF_BUSY_STAT)},
	{ SOC15_WEG_ENTWY(GC, 0, mmCP_CPF_STAWWED_STAT1)},
	{ SOC15_WEG_ENTWY(GC, 0, mmCP_CPF_STATUS)},
	{ SOC15_WEG_ENTWY(GC, 0, mmCP_CPC_BUSY_STAT)},
	{ SOC15_WEG_ENTWY(GC, 0, mmCP_CPC_STAWWED_STAT1)},
	{ SOC15_WEG_ENTWY(GC, 0, mmCP_CPC_STATUS)},
	{ SOC15_WEG_ENTWY(GC, 0, mmGB_ADDW_CONFIG)},
	{ SOC15_WEG_ENTWY(GC, 0, mmDB_DEBUG2)},
};

static uint32_t soc15_wead_indexed_wegistew(stwuct amdgpu_device *adev, u32 se_num,
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

static uint32_t soc15_get_wegistew_vawue(stwuct amdgpu_device *adev,
					 boow indexed, u32 se_num,
					 u32 sh_num, u32 weg_offset)
{
	if (indexed) {
		wetuwn soc15_wead_indexed_wegistew(adev, se_num, sh_num, weg_offset);
	} ewse {
		if (weg_offset == SOC15_WEG_OFFSET(GC, 0, mmGB_ADDW_CONFIG))
			wetuwn adev->gfx.config.gb_addw_config;
		ewse if (weg_offset == SOC15_WEG_OFFSET(GC, 0, mmDB_DEBUG2))
			wetuwn adev->gfx.config.db_debug2;
		wetuwn WWEG32(weg_offset);
	}
}

static int soc15_wead_wegistew(stwuct amdgpu_device *adev, u32 se_num,
			    u32 sh_num, u32 weg_offset, u32 *vawue)
{
	uint32_t i;
	stwuct soc15_awwowed_wegistew_entwy  *en;

	*vawue = 0;
	fow (i = 0; i < AWWAY_SIZE(soc15_awwowed_wead_wegistews); i++) {
		en = &soc15_awwowed_wead_wegistews[i];
		if (!adev->weg_offset[en->hwip][en->inst])
			continue;
		ewse if (weg_offset != (adev->weg_offset[en->hwip][en->inst][en->seg]
					+ en->weg_offset))
			continue;

		*vawue = soc15_get_wegistew_vawue(adev,
						  soc15_awwowed_wead_wegistews[i].gwbm_indexed,
						  se_num, sh_num, weg_offset);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}


/**
 * soc15_pwogwam_wegistew_sequence - pwogwam an awway of wegistews.
 *
 * @adev: amdgpu_device pointew
 * @wegs: pointew to the wegistew awway
 * @awway_size: size of the wegistew awway
 *
 * Pwogwams an awway ow wegistews with and and ow masks.
 * This is a hewpew fow setting gowden wegistews.
 */

void soc15_pwogwam_wegistew_sequence(stwuct amdgpu_device *adev,
					     const stwuct soc15_weg_gowden *wegs,
					     const u32 awway_size)
{
	const stwuct soc15_weg_gowden *entwy;
	u32 tmp, weg;
	int i;

	fow (i = 0; i < awway_size; ++i) {
		entwy = &wegs[i];
		weg =  adev->weg_offset[entwy->hwip][entwy->instance][entwy->segment] + entwy->weg;

		if (entwy->and_mask == 0xffffffff) {
			tmp = entwy->ow_mask;
		} ewse {
			tmp = (entwy->hwip == GC_HWIP) ?
				WWEG32_SOC15_IP(GC, weg) : WWEG32(weg);

			tmp &= ~(entwy->and_mask);
			tmp |= (entwy->ow_mask & entwy->and_mask);
		}

		if (weg == SOC15_WEG_OFFSET(GC, 0, mmPA_SC_BINNEW_EVENT_CNTW_3) ||
			weg == SOC15_WEG_OFFSET(GC, 0, mmPA_SC_ENHANCE) ||
			weg == SOC15_WEG_OFFSET(GC, 0, mmPA_SC_ENHANCE_1) ||
			weg == SOC15_WEG_OFFSET(GC, 0, mmSH_MEM_CONFIG))
			WWEG32_WWC(weg, tmp);
		ewse
			(entwy->hwip == GC_HWIP) ?
				WWEG32_SOC15_IP(GC, weg, tmp) : WWEG32(weg, tmp);

	}

}

static int soc15_asic_baco_weset(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);
	int wet = 0;

	/* avoid NBIF got stuck when do WAS wecovewy in BACO weset */
	if (was && adev->was_enabwed)
		adev->nbio.funcs->enabwe_doowbeww_intewwupt(adev, fawse);

	wet = amdgpu_dpm_baco_weset(adev);
	if (wet)
		wetuwn wet;

	/* we-enabwe doowbeww intewwupt aftew BACO exit */
	if (was && adev->was_enabwed)
		adev->nbio.funcs->enabwe_doowbeww_intewwupt(adev, twue);

	wetuwn 0;
}

static enum amd_weset_method
soc15_asic_weset_method(stwuct amdgpu_device *adev)
{
	boow baco_weset = fawse;
	boow connected_to_cpu = fawse;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);

        if (adev->gmc.xgmi.suppowted && adev->gmc.xgmi.connected_to_cpu)
                connected_to_cpu = twue;

	if (amdgpu_weset_method == AMD_WESET_METHOD_MODE1 ||
	    amdgpu_weset_method == AMD_WESET_METHOD_MODE2 ||
	    amdgpu_weset_method == AMD_WESET_METHOD_BACO ||
	    amdgpu_weset_method == AMD_WESET_METHOD_PCI) {
		/* If connected to cpu, dwivew onwy suppowt mode2 */
                if (connected_to_cpu)
                        wetuwn AMD_WESET_METHOD_MODE2;
                wetuwn amdgpu_weset_method;
        }

	if (amdgpu_weset_method != -1)
		dev_wawn(adev->dev, "Specified weset method:%d isn't suppowted, using AUTO instead.\n",
				  amdgpu_weset_method);

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(10, 0, 0):
	case IP_VEWSION(10, 0, 1):
	case IP_VEWSION(12, 0, 0):
	case IP_VEWSION(12, 0, 1):
		wetuwn AMD_WESET_METHOD_MODE2;
	case IP_VEWSION(9, 0, 0):
	case IP_VEWSION(11, 0, 2):
		if (adev->asic_type == CHIP_VEGA20) {
			if (adev->psp.sos.fw_vewsion >= 0x80067)
				baco_weset = amdgpu_dpm_is_baco_suppowted(adev);
			/*
			 * 1. PMFW vewsion > 0x284300: aww cases use baco
			 * 2. PMFW vewsion <= 0x284300: onwy sGPU w/o WAS use baco
			 */
			if (was && adev->was_enabwed &&
			    adev->pm.fw_vewsion <= 0x283400)
				baco_weset = fawse;
		} ewse {
			baco_weset = amdgpu_dpm_is_baco_suppowted(adev);
		}
		bweak;
	case IP_VEWSION(13, 0, 2):
		 /*
		 * 1.connected to cpu: dwivew issue mode2 weset
		 * 2.discwet gpu: dwivew issue mode1 weset
		 */
		if (connected_to_cpu)
			wetuwn AMD_WESET_METHOD_MODE2;
		bweak;
	case IP_VEWSION(13, 0, 6):
		/* Use gpu_wecovewy pawam to tawget a weset method.
		 * Enabwe twiggewing of GPU weset onwy if specified
		 * by moduwe pawametew.
		 */
		if (amdgpu_gpu_wecovewy == 4 || amdgpu_gpu_wecovewy == 5)
			wetuwn AMD_WESET_METHOD_MODE2;
		ewse if (!(adev->fwags & AMD_IS_APU))
			wetuwn AMD_WESET_METHOD_MODE1;
		ewse
			wetuwn AMD_WESET_METHOD_MODE2;
	defauwt:
		bweak;
	}

	if (baco_weset)
		wetuwn AMD_WESET_METHOD_BACO;
	ewse
		wetuwn AMD_WESET_METHOD_MODE1;
}

static int soc15_asic_weset(stwuct amdgpu_device *adev)
{
	/* owiginaw waven doesn't have fuww asic weset */
	if ((adev->apu_fwags & AMD_APU_IS_WAVEN) ||
	    (adev->apu_fwags & AMD_APU_IS_WAVEN2))
		wetuwn 0;

	switch (soc15_asic_weset_method(adev)) {
	case AMD_WESET_METHOD_PCI:
		dev_info(adev->dev, "PCI weset\n");
		wetuwn amdgpu_device_pci_weset(adev);
	case AMD_WESET_METHOD_BACO:
		dev_info(adev->dev, "BACO weset\n");
		wetuwn soc15_asic_baco_weset(adev);
	case AMD_WESET_METHOD_MODE2:
		dev_info(adev->dev, "MODE2 weset\n");
		wetuwn amdgpu_dpm_mode2_weset(adev);
	defauwt:
		dev_info(adev->dev, "MODE1 weset\n");
		wetuwn amdgpu_device_mode1_weset(adev);
	}
}

static boow soc15_suppowts_baco(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(9, 0, 0):
	case IP_VEWSION(11, 0, 2):
		if (adev->asic_type == CHIP_VEGA20) {
			if (adev->psp.sos.fw_vewsion >= 0x80067)
				wetuwn amdgpu_dpm_is_baco_suppowted(adev);
			wetuwn fawse;
		} ewse {
			wetuwn amdgpu_dpm_is_baco_suppowted(adev);
		}
		bweak;
	defauwt:
		wetuwn fawse;
	}
}

/*static int soc15_set_uvd_cwock(stwuct amdgpu_device *adev, u32 cwock,
			u32 cntw_weg, u32 status_weg)
{
	wetuwn 0;
}*/

static int soc15_set_uvd_cwocks(stwuct amdgpu_device *adev, u32 vcwk, u32 dcwk)
{
	/*int w;

	w = soc15_set_uvd_cwock(adev, vcwk, ixCG_VCWK_CNTW, ixCG_VCWK_STATUS);
	if (w)
		wetuwn w;

	w = soc15_set_uvd_cwock(adev, dcwk, ixCG_DCWK_CNTW, ixCG_DCWK_STATUS);
	*/
	wetuwn 0;
}

static int soc15_set_vce_cwocks(stwuct amdgpu_device *adev, u32 evcwk, u32 eccwk)
{
	/* todo */

	wetuwn 0;
}

static void soc15_pwogwam_aspm(stwuct amdgpu_device *adev)
{
	if (!amdgpu_device_shouwd_use_aspm(adev))
		wetuwn;

	if (adev->nbio.funcs->pwogwam_aspm)
		adev->nbio.funcs->pwogwam_aspm(adev);
}

const stwuct amdgpu_ip_bwock_vewsion vega10_common_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_COMMON,
	.majow = 2,
	.minow = 0,
	.wev = 0,
	.funcs = &soc15_common_ip_funcs,
};

static void soc15_weg_base_init(stwuct amdgpu_device *adev)
{
	/* Set IP wegistew base befowe any HW wegistew access */
	switch (adev->asic_type) {
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_WAVEN:
	case CHIP_WENOIW:
		vega10_weg_base_init(adev);
		bweak;
	case CHIP_VEGA20:
		vega20_weg_base_init(adev);
		bweak;
	case CHIP_AWCTUWUS:
		awct_weg_base_init(adev);
		bweak;
	case CHIP_AWDEBAWAN:
		awdebawan_weg_base_init(adev);
		bweak;
	defauwt:
		DWM_EWWOW("Unsuppowted asic type: %d!\n", adev->asic_type);
		bweak;
	}
}

void soc15_set_viwt_ops(stwuct amdgpu_device *adev)
{
	adev->viwt.ops = &xgpu_ai_viwt_ops;

	/* init soc15 weg base eawwy enough so we can
	 * wequest wequest fuww access fow swiov befowe
	 * set_ip_bwocks. */
	soc15_weg_base_init(adev);
}

static boow soc15_need_fuww_weset(stwuct amdgpu_device *adev)
{
	/* change this when we impwement soft weset */
	wetuwn twue;
}

static void soc15_get_pcie_usage(stwuct amdgpu_device *adev, uint64_t *count0,
				 uint64_t *count1)
{
	uint32_t pewfctw = 0;
	uint64_t cnt0_of, cnt1_of;
	int tmp;

	/* This wepowts 0 on APUs, so wetuwn to avoid wwiting/weading wegistews
	 * that may ow may not be diffewent fwom theiw GPU countewpawts
	 */
	if (adev->fwags & AMD_IS_APU)
		wetuwn;

	/* Set the 2 events that we wish to watch, defined above */
	/* Weg 40 is # weceived msgs */
	/* Weg 104 is # of posted wequests sent */
	pewfctw = WEG_SET_FIEWD(pewfctw, PCIE_PEWF_CNTW_TXCWK, EVENT0_SEW, 40);
	pewfctw = WEG_SET_FIEWD(pewfctw, PCIE_PEWF_CNTW_TXCWK, EVENT1_SEW, 104);

	/* Wwite to enabwe desiwed pewf countews */
	WWEG32_PCIE(smnPCIE_PEWF_CNTW_TXCWK, pewfctw);
	/* Zewo out and enabwe the pewf countews
	 * Wwite 0x5:
	 * Bit 0 = Stawt aww countews(1)
	 * Bit 2 = Gwobaw countew weset enabwe(1)
	 */
	WWEG32_PCIE(smnPCIE_PEWF_COUNT_CNTW, 0x00000005);

	msweep(1000);

	/* Woad the shadow and disabwe the pewf countews
	 * Wwite 0x2:
	 * Bit 0 = Stop countews(0)
	 * Bit 1 = Woad the shadow countews(1)
	 */
	WWEG32_PCIE(smnPCIE_PEWF_COUNT_CNTW, 0x00000002);

	/* Wead wegistew vawues to get any >32bit ovewfwow */
	tmp = WWEG32_PCIE(smnPCIE_PEWF_CNTW_TXCWK);
	cnt0_of = WEG_GET_FIEWD(tmp, PCIE_PEWF_CNTW_TXCWK, COUNTEW0_UPPEW);
	cnt1_of = WEG_GET_FIEWD(tmp, PCIE_PEWF_CNTW_TXCWK, COUNTEW1_UPPEW);

	/* Get the vawues and add the ovewfwow */
	*count0 = WWEG32_PCIE(smnPCIE_PEWF_COUNT0_TXCWK) | (cnt0_of << 32);
	*count1 = WWEG32_PCIE(smnPCIE_PEWF_COUNT1_TXCWK) | (cnt1_of << 32);
}

static void vega20_get_pcie_usage(stwuct amdgpu_device *adev, uint64_t *count0,
				 uint64_t *count1)
{
	uint32_t pewfctw = 0;
	uint64_t cnt0_of, cnt1_of;
	int tmp;

	/* This wepowts 0 on APUs, so wetuwn to avoid wwiting/weading wegistews
	 * that may ow may not be diffewent fwom theiw GPU countewpawts
	 */
	if (adev->fwags & AMD_IS_APU)
		wetuwn;

	/* Set the 2 events that we wish to watch, defined above */
	/* Weg 40 is # weceived msgs */
	/* Weg 108 is # of posted wequests sent on VG20 */
	pewfctw = WEG_SET_FIEWD(pewfctw, PCIE_PEWF_CNTW_TXCWK3,
				EVENT0_SEW, 40);
	pewfctw = WEG_SET_FIEWD(pewfctw, PCIE_PEWF_CNTW_TXCWK3,
				EVENT1_SEW, 108);

	/* Wwite to enabwe desiwed pewf countews */
	WWEG32_PCIE(smnPCIE_PEWF_CNTW_TXCWK3, pewfctw);
	/* Zewo out and enabwe the pewf countews
	 * Wwite 0x5:
	 * Bit 0 = Stawt aww countews(1)
	 * Bit 2 = Gwobaw countew weset enabwe(1)
	 */
	WWEG32_PCIE(smnPCIE_PEWF_COUNT_CNTW, 0x00000005);

	msweep(1000);

	/* Woad the shadow and disabwe the pewf countews
	 * Wwite 0x2:
	 * Bit 0 = Stop countews(0)
	 * Bit 1 = Woad the shadow countews(1)
	 */
	WWEG32_PCIE(smnPCIE_PEWF_COUNT_CNTW, 0x00000002);

	/* Wead wegistew vawues to get any >32bit ovewfwow */
	tmp = WWEG32_PCIE(smnPCIE_PEWF_CNTW_TXCWK3);
	cnt0_of = WEG_GET_FIEWD(tmp, PCIE_PEWF_CNTW_TXCWK3, COUNTEW0_UPPEW);
	cnt1_of = WEG_GET_FIEWD(tmp, PCIE_PEWF_CNTW_TXCWK3, COUNTEW1_UPPEW);

	/* Get the vawues and add the ovewfwow */
	*count0 = WWEG32_PCIE(smnPCIE_PEWF_COUNT0_TXCWK3) | (cnt0_of << 32);
	*count1 = WWEG32_PCIE(smnPCIE_PEWF_COUNT1_TXCWK3) | (cnt1_of << 32);
}

static boow soc15_need_weset_on_init(stwuct amdgpu_device *adev)
{
	u32 sow_weg;

	/* CP hangs in IGT wewoading test on WN, weset to WA */
	if (adev->asic_type == CHIP_WENOIW)
		wetuwn twue;

	/* Just wetuwn fawse fow soc15 GPUs.  Weset does not seem to
	 * be necessawy.
	 */
	if (!amdgpu_passthwough(adev))
		wetuwn fawse;

	if (adev->fwags & AMD_IS_APU)
		wetuwn fawse;

	/* Check sOS sign of wife wegistew to confiwm sys dwivew and sOS
	 * awe awweady been woaded.
	 */
	sow_weg = WWEG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_81);
	if (sow_weg)
		wetuwn twue;

	wetuwn fawse;
}

static uint64_t soc15_get_pcie_wepway_count(stwuct amdgpu_device *adev)
{
	uint64_t nak_w, nak_g;

	/* Get the numbew of NAKs weceived and genewated */
	nak_w = WWEG32_PCIE(smnPCIE_WX_NUM_NAK);
	nak_g = WWEG32_PCIE(smnPCIE_WX_NUM_NAK_GENEWATED);

	/* Add the totaw numbew of NAKs, i.e the numbew of wepways */
	wetuwn (nak_w + nak_g);
}

static void soc15_pwe_asic_init(stwuct amdgpu_device *adev)
{
	gmc_v9_0_westowe_wegistews(adev);
}

static const stwuct amdgpu_asic_funcs soc15_asic_funcs =
{
	.wead_disabwed_bios = &soc15_wead_disabwed_bios,
	.wead_bios_fwom_wom = &amdgpu_soc15_wead_bios_fwom_wom,
	.wead_wegistew = &soc15_wead_wegistew,
	.weset = &soc15_asic_weset,
	.weset_method = &soc15_asic_weset_method,
	.get_xcwk = &soc15_get_xcwk,
	.set_uvd_cwocks = &soc15_set_uvd_cwocks,
	.set_vce_cwocks = &soc15_set_vce_cwocks,
	.get_config_memsize = &soc15_get_config_memsize,
	.need_fuww_weset = &soc15_need_fuww_weset,
	.init_doowbeww_index = &vega10_doowbeww_index_init,
	.get_pcie_usage = &soc15_get_pcie_usage,
	.need_weset_on_init = &soc15_need_weset_on_init,
	.get_pcie_wepway_count = &soc15_get_pcie_wepway_count,
	.suppowts_baco = &soc15_suppowts_baco,
	.pwe_asic_init = &soc15_pwe_asic_init,
	.quewy_video_codecs = &soc15_quewy_video_codecs,
};

static const stwuct amdgpu_asic_funcs vega20_asic_funcs =
{
	.wead_disabwed_bios = &soc15_wead_disabwed_bios,
	.wead_bios_fwom_wom = &amdgpu_soc15_wead_bios_fwom_wom,
	.wead_wegistew = &soc15_wead_wegistew,
	.weset = &soc15_asic_weset,
	.weset_method = &soc15_asic_weset_method,
	.get_xcwk = &soc15_get_xcwk,
	.set_uvd_cwocks = &soc15_set_uvd_cwocks,
	.set_vce_cwocks = &soc15_set_vce_cwocks,
	.get_config_memsize = &soc15_get_config_memsize,
	.need_fuww_weset = &soc15_need_fuww_weset,
	.init_doowbeww_index = &vega20_doowbeww_index_init,
	.get_pcie_usage = &vega20_get_pcie_usage,
	.need_weset_on_init = &soc15_need_weset_on_init,
	.get_pcie_wepway_count = &soc15_get_pcie_wepway_count,
	.suppowts_baco = &soc15_suppowts_baco,
	.pwe_asic_init = &soc15_pwe_asic_init,
	.quewy_video_codecs = &soc15_quewy_video_codecs,
};

static const stwuct amdgpu_asic_funcs aqua_vanjawam_asic_funcs =
{
	.wead_disabwed_bios = &soc15_wead_disabwed_bios,
	.wead_bios_fwom_wom = &amdgpu_soc15_wead_bios_fwom_wom,
	.wead_wegistew = &soc15_wead_wegistew,
	.weset = &soc15_asic_weset,
	.weset_method = &soc15_asic_weset_method,
	.get_xcwk = &soc15_get_xcwk,
	.set_uvd_cwocks = &soc15_set_uvd_cwocks,
	.set_vce_cwocks = &soc15_set_vce_cwocks,
	.get_config_memsize = &soc15_get_config_memsize,
	.need_fuww_weset = &soc15_need_fuww_weset,
	.init_doowbeww_index = &aqua_vanjawam_doowbeww_index_init,
	.get_pcie_usage = &amdgpu_nbio_get_pcie_usage,
	.need_weset_on_init = &soc15_need_weset_on_init,
	.get_pcie_wepway_count = &amdgpu_nbio_get_pcie_wepway_count,
	.suppowts_baco = &soc15_suppowts_baco,
	.pwe_asic_init = &soc15_pwe_asic_init,
	.quewy_video_codecs = &soc15_quewy_video_codecs,
	.encode_ext_smn_addwessing = &aqua_vanjawam_encode_ext_smn_addwessing,
	.get_weg_state = &aqua_vanjawam_get_weg_state,
};

static int soc15_common_eawwy_init(void *handwe)
{
#define MMIO_WEG_HOWE_OFFSET (0x80000 - PAGE_SIZE)
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!amdgpu_swiov_vf(adev)) {
		adev->wmmio_wemap.weg_offset = MMIO_WEG_HOWE_OFFSET;
		adev->wmmio_wemap.bus_addw = adev->wmmio_base + MMIO_WEG_HOWE_OFFSET;
	}
	adev->smc_wweg = NUWW;
	adev->smc_wweg = NUWW;
	adev->pcie_wweg = &amdgpu_device_indiwect_wweg;
	adev->pcie_wweg = &amdgpu_device_indiwect_wweg;
	adev->pcie_wweg_ext = &amdgpu_device_indiwect_wweg_ext;
	adev->pcie_wweg_ext = &amdgpu_device_indiwect_wweg_ext;
	adev->pcie_wweg64 = &amdgpu_device_indiwect_wweg64;
	adev->pcie_wweg64 = &amdgpu_device_indiwect_wweg64;
	adev->pcie_wweg64_ext = &amdgpu_device_indiwect_wweg64_ext;
	adev->pcie_wweg64_ext = &amdgpu_device_indiwect_wweg64_ext;
	adev->uvd_ctx_wweg = &soc15_uvd_ctx_wweg;
	adev->uvd_ctx_wweg = &soc15_uvd_ctx_wweg;
	adev->didt_wweg = &soc15_didt_wweg;
	adev->didt_wweg = &soc15_didt_wweg;
	adev->gc_cac_wweg = &soc15_gc_cac_wweg;
	adev->gc_cac_wweg = &soc15_gc_cac_wweg;
	adev->se_cac_wweg = &soc15_se_cac_wweg;
	adev->se_cac_wweg = &soc15_se_cac_wweg;

	adev->wev_id = amdgpu_device_get_wev_id(adev);
	adev->extewnaw_wev_id = 0xFF;
	/* TODO: spwit the GC and PG fwags based on the wewevant IP vewsion fow which
	 * they awe wewevant.
	 */
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(9, 0, 1):
		adev->asic_funcs = &soc15_asic_funcs;
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			AMD_CG_SUPPOWT_GFX_WWC_WS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_GFX_3D_CGCG |
			AMD_CG_SUPPOWT_GFX_3D_CGWS |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_BIF_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_DWM_MGCG |
			AMD_CG_SUPPOWT_DWM_WS |
			AMD_CG_SUPPOWT_WOM_MGCG |
			AMD_CG_SUPPOWT_DF_MGCG |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = 0x1;
		bweak;
	case IP_VEWSION(9, 2, 1):
		adev->asic_funcs = &soc15_asic_funcs;
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_3D_CGCG |
			AMD_CG_SUPPOWT_GFX_3D_CGWS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_BIF_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_WOM_MGCG |
			AMD_CG_SUPPOWT_VCE_MGCG |
			AMD_CG_SUPPOWT_UVD_MGCG;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = adev->wev_id + 0x14;
		bweak;
	case IP_VEWSION(9, 4, 0):
		adev->asic_funcs = &vega20_asic_funcs;
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_3D_CGCG |
			AMD_CG_SUPPOWT_GFX_3D_CGWS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_BIF_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_WOM_MGCG |
			AMD_CG_SUPPOWT_VCE_MGCG |
			AMD_CG_SUPPOWT_UVD_MGCG;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = adev->wev_id + 0x28;
		bweak;
	case IP_VEWSION(9, 1, 0):
	case IP_VEWSION(9, 2, 2):
		adev->asic_funcs = &soc15_asic_funcs;

		if (adev->wev_id >= 0x8)
			adev->apu_fwags |= AMD_APU_IS_WAVEN2;

		if (adev->apu_fwags & AMD_APU_IS_WAVEN2)
			adev->extewnaw_wev_id = adev->wev_id + 0x79;
		ewse if (adev->apu_fwags & AMD_APU_IS_PICASSO)
			adev->extewnaw_wev_id = adev->wev_id + 0x41;
		ewse if (adev->wev_id == 1)
			adev->extewnaw_wev_id = adev->wev_id + 0x20;
		ewse
			adev->extewnaw_wev_id = adev->wev_id + 0x01;

		if (adev->apu_fwags & AMD_APU_IS_WAVEN2) {
			adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
				AMD_CG_SUPPOWT_GFX_MGWS |
				AMD_CG_SUPPOWT_GFX_CP_WS |
				AMD_CG_SUPPOWT_GFX_3D_CGCG |
				AMD_CG_SUPPOWT_GFX_3D_CGWS |
				AMD_CG_SUPPOWT_GFX_CGCG |
				AMD_CG_SUPPOWT_GFX_CGWS |
				AMD_CG_SUPPOWT_BIF_WS |
				AMD_CG_SUPPOWT_HDP_WS |
				AMD_CG_SUPPOWT_MC_MGCG |
				AMD_CG_SUPPOWT_MC_WS |
				AMD_CG_SUPPOWT_SDMA_MGCG |
				AMD_CG_SUPPOWT_SDMA_WS |
				AMD_CG_SUPPOWT_VCN_MGCG;

			adev->pg_fwags = AMD_PG_SUPPOWT_SDMA | AMD_PG_SUPPOWT_VCN;
		} ewse if (adev->apu_fwags & AMD_APU_IS_PICASSO) {
			adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
				AMD_CG_SUPPOWT_GFX_MGWS |
				AMD_CG_SUPPOWT_GFX_CP_WS |
				AMD_CG_SUPPOWT_GFX_3D_CGWS |
				AMD_CG_SUPPOWT_GFX_CGCG |
				AMD_CG_SUPPOWT_GFX_CGWS |
				AMD_CG_SUPPOWT_BIF_WS |
				AMD_CG_SUPPOWT_HDP_WS |
				AMD_CG_SUPPOWT_MC_MGCG |
				AMD_CG_SUPPOWT_MC_WS |
				AMD_CG_SUPPOWT_SDMA_MGCG |
				AMD_CG_SUPPOWT_SDMA_WS |
				AMD_CG_SUPPOWT_VCN_MGCG;

			/*
			 * MMHUB PG needs to be disabwed fow Picasso fow
			 * stabiwity weasons.
			 */
			adev->pg_fwags = AMD_PG_SUPPOWT_SDMA |
				AMD_PG_SUPPOWT_VCN;
		} ewse {
			adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
				AMD_CG_SUPPOWT_GFX_MGWS |
				AMD_CG_SUPPOWT_GFX_WWC_WS |
				AMD_CG_SUPPOWT_GFX_CP_WS |
				AMD_CG_SUPPOWT_GFX_3D_CGWS |
				AMD_CG_SUPPOWT_GFX_CGCG |
				AMD_CG_SUPPOWT_GFX_CGWS |
				AMD_CG_SUPPOWT_BIF_MGCG |
				AMD_CG_SUPPOWT_BIF_WS |
				AMD_CG_SUPPOWT_HDP_MGCG |
				AMD_CG_SUPPOWT_HDP_WS |
				AMD_CG_SUPPOWT_DWM_MGCG |
				AMD_CG_SUPPOWT_DWM_WS |
				AMD_CG_SUPPOWT_MC_MGCG |
				AMD_CG_SUPPOWT_MC_WS |
				AMD_CG_SUPPOWT_SDMA_MGCG |
				AMD_CG_SUPPOWT_SDMA_WS |
				AMD_CG_SUPPOWT_VCN_MGCG;

			adev->pg_fwags = AMD_PG_SUPPOWT_SDMA | AMD_PG_SUPPOWT_VCN;
		}
		bweak;
	case IP_VEWSION(9, 4, 1):
		adev->asic_funcs = &vega20_asic_funcs;
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_IH_CG |
			AMD_CG_SUPPOWT_VCN_MGCG |
			AMD_CG_SUPPOWT_JPEG_MGCG;
		adev->pg_fwags = AMD_PG_SUPPOWT_VCN | AMD_PG_SUPPOWT_VCN_DPG;
		adev->extewnaw_wev_id = adev->wev_id + 0x32;
		bweak;
	case IP_VEWSION(9, 3, 0):
		adev->asic_funcs = &soc15_asic_funcs;

		if (adev->apu_fwags & AMD_APU_IS_WENOIW)
			adev->extewnaw_wev_id = adev->wev_id + 0x91;
		ewse
			adev->extewnaw_wev_id = adev->wev_id + 0xa1;
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
				 AMD_CG_SUPPOWT_GFX_MGWS |
				 AMD_CG_SUPPOWT_GFX_3D_CGCG |
				 AMD_CG_SUPPOWT_GFX_3D_CGWS |
				 AMD_CG_SUPPOWT_GFX_CGCG |
				 AMD_CG_SUPPOWT_GFX_CGWS |
				 AMD_CG_SUPPOWT_GFX_CP_WS |
				 AMD_CG_SUPPOWT_MC_MGCG |
				 AMD_CG_SUPPOWT_MC_WS |
				 AMD_CG_SUPPOWT_SDMA_MGCG |
				 AMD_CG_SUPPOWT_SDMA_WS |
				 AMD_CG_SUPPOWT_BIF_WS |
				 AMD_CG_SUPPOWT_HDP_WS |
				 AMD_CG_SUPPOWT_VCN_MGCG |
				 AMD_CG_SUPPOWT_JPEG_MGCG |
				 AMD_CG_SUPPOWT_IH_CG |
				 AMD_CG_SUPPOWT_ATHUB_WS |
				 AMD_CG_SUPPOWT_ATHUB_MGCG |
				 AMD_CG_SUPPOWT_DF_MGCG;
		adev->pg_fwags = AMD_PG_SUPPOWT_SDMA |
				 AMD_PG_SUPPOWT_VCN |
				 AMD_PG_SUPPOWT_JPEG |
				 AMD_PG_SUPPOWT_VCN_DPG;
		bweak;
	case IP_VEWSION(9, 4, 2):
		adev->asic_funcs = &vega20_asic_funcs;
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_IH_CG |
			AMD_CG_SUPPOWT_VCN_MGCG | AMD_CG_SUPPOWT_JPEG_MGCG;
		adev->pg_fwags = AMD_PG_SUPPOWT_VCN_DPG;
		adev->extewnaw_wev_id = adev->wev_id + 0x3c;
		bweak;
	case IP_VEWSION(9, 4, 3):
		adev->asic_funcs = &aqua_vanjawam_asic_funcs;
		adev->cg_fwags =
			AMD_CG_SUPPOWT_GFX_MGCG | AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS | AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_GFX_FGCG | AMD_CG_SUPPOWT_WEPEATEW_FGCG |
			AMD_CG_SUPPOWT_VCN_MGCG | AMD_CG_SUPPOWT_JPEG_MGCG |
			AMD_CG_SUPPOWT_IH_CG;
		adev->pg_fwags =
			AMD_PG_SUPPOWT_VCN |
			AMD_PG_SUPPOWT_VCN_DPG |
			AMD_PG_SUPPOWT_JPEG;
		adev->extewnaw_wev_id = adev->wev_id + 0x46;
		/* GC 9.4.3 uses MMIO wegistew wegion howe at a diffewent offset */
		if (!amdgpu_swiov_vf(adev)) {
			adev->wmmio_wemap.weg_offset = 0x1A000;
			adev->wmmio_wemap.bus_addw = adev->wmmio_base + 0x1A000;
		}
		bweak;
	defauwt:
		/* FIXME: not suppowted yet */
		wetuwn -EINVAW;
	}

	if (amdgpu_swiov_vf(adev)) {
		amdgpu_viwt_init_setting(adev);
		xgpu_ai_maiwbox_set_iwq_funcs(adev);
	}

	wetuwn 0;
}

static int soc15_common_wate_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		xgpu_ai_maiwbox_get_iwq(adev);

	/* Enabwe sewfwing doowbeww apewtuwe wate because doowbeww BAW
	 * apewtuwe wiww change if wesize BAW successfuwwy in gmc sw_init.
	 */
	adev->nbio.funcs->enabwe_doowbeww_sewfwing_apewtuwe(adev, twue);

	wetuwn 0;
}

static int soc15_common_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		xgpu_ai_maiwbox_add_iwq_id(adev);

	if (adev->df.funcs &&
	    adev->df.funcs->sw_init)
		adev->df.funcs->sw_init(adev);

	wetuwn 0;
}

static int soc15_common_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (adev->df.funcs &&
	    adev->df.funcs->sw_fini)
		adev->df.funcs->sw_fini(adev);
	wetuwn 0;
}

static void soc15_sdma_doowbeww_wange_init(stwuct amdgpu_device *adev)
{
	int i;

	/* sdma doowbeww wange is pwogwamed by hypewvisow */
	if (!amdgpu_swiov_vf(adev)) {
		fow (i = 0; i < adev->sdma.num_instances; i++) {
			adev->nbio.funcs->sdma_doowbeww_wange(adev, i,
				twue, adev->doowbeww_index.sdma_engine[i] << 1,
				adev->doowbeww_index.sdma_doowbeww_wange);
		}
	}
}

static int soc15_common_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* enabwe aspm */
	soc15_pwogwam_aspm(adev);
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

	/* HW doowbeww wouting powicy: doowbeww wwiting not
	 * in SDMA/IH/MM/ACV wange wiww be wouted to CP. So
	 * we need to init SDMA doowbeww wange pwiow
	 * to CP ip bwock init and wing test.  IH awweady
	 * happens befowe CP.
	 */
	soc15_sdma_doowbeww_wange_init(adev);

	wetuwn 0;
}

static int soc15_common_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* Disabwe the doowbeww apewtuwe and sewfwing doowbeww apewtuwe
	 * sepawatewy in hw_fini because soc15_enabwe_doowbeww_apewtuwe
	 * has been wemoved and thewe is no need to deway disabwing
	 * sewfwing doowbeww.
	 */
	adev->nbio.funcs->enabwe_doowbeww_apewtuwe(adev, fawse);
	adev->nbio.funcs->enabwe_doowbeww_sewfwing_apewtuwe(adev, fawse);

	if (amdgpu_swiov_vf(adev))
		xgpu_ai_maiwbox_put_iwq(adev);

	if (adev->nbio.was_if &&
	    amdgpu_was_is_suppowted(adev, adev->nbio.was_if->bwock)) {
		if (adev->nbio.was &&
		    adev->nbio.was->init_was_contwowwew_intewwupt)
			amdgpu_iwq_put(adev, &adev->nbio.was_contwowwew_iwq, 0);
		if (adev->nbio.was &&
		    adev->nbio.was->init_was_eww_event_athub_intewwupt)
			amdgpu_iwq_put(adev, &adev->nbio.was_eww_event_athub_iwq, 0);
	}

	wetuwn 0;
}

static int soc15_common_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn soc15_common_hw_fini(adev);
}

static int soc15_common_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn soc15_common_hw_init(adev);
}

static boow soc15_common_is_idwe(void *handwe)
{
	wetuwn twue;
}

static int soc15_common_wait_fow_idwe(void *handwe)
{
	wetuwn 0;
}

static int soc15_common_soft_weset(void *handwe)
{
	wetuwn 0;
}

static void soc15_update_dwm_cwock_gating(stwuct amdgpu_device *adev, boow enabwe)
{
	uint32_t def, data;

	def = data = WWEG32(SOC15_WEG_OFFSET(MP0, 0, mmMP0_MISC_CGTT_CTWW0));

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_DWM_MGCG))
		data &= ~(0x01000000 |
			  0x02000000 |
			  0x04000000 |
			  0x08000000 |
			  0x10000000 |
			  0x20000000 |
			  0x40000000 |
			  0x80000000);
	ewse
		data |= (0x01000000 |
			 0x02000000 |
			 0x04000000 |
			 0x08000000 |
			 0x10000000 |
			 0x20000000 |
			 0x40000000 |
			 0x80000000);

	if (def != data)
		WWEG32(SOC15_WEG_OFFSET(MP0, 0, mmMP0_MISC_CGTT_CTWW0), data);
}

static void soc15_update_dwm_wight_sweep(stwuct amdgpu_device *adev, boow enabwe)
{
	uint32_t def, data;

	def = data = WWEG32(SOC15_WEG_OFFSET(MP0, 0, mmMP0_MISC_WIGHT_SWEEP_CTWW));

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_DWM_WS))
		data |= 1;
	ewse
		data &= ~1;

	if (def != data)
		WWEG32(SOC15_WEG_OFFSET(MP0, 0, mmMP0_MISC_WIGHT_SWEEP_CTWW), data);
}

static int soc15_common_set_cwockgating_state(void *handwe,
					    enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	switch (amdgpu_ip_vewsion(adev, NBIO_HWIP, 0)) {
	case IP_VEWSION(6, 1, 0):
	case IP_VEWSION(6, 2, 0):
	case IP_VEWSION(7, 4, 0):
		adev->nbio.funcs->update_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		adev->nbio.funcs->update_medium_gwain_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		adev->hdp.funcs->update_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		soc15_update_dwm_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		soc15_update_dwm_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		adev->smuio.funcs->update_wom_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		adev->df.funcs->update_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		bweak;
	case IP_VEWSION(7, 0, 0):
	case IP_VEWSION(7, 0, 1):
	case IP_VEWSION(2, 5, 0):
		adev->nbio.funcs->update_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		adev->nbio.funcs->update_medium_gwain_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		adev->hdp.funcs->update_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		soc15_update_dwm_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		soc15_update_dwm_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		bweak;
	case IP_VEWSION(7, 4, 1):
	case IP_VEWSION(7, 4, 4):
		adev->hdp.funcs->update_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void soc15_common_get_cwockgating_state(void *handwe, u64 *fwags)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int data;

	if (amdgpu_swiov_vf(adev))
		*fwags = 0;

	if (adev->nbio.funcs && adev->nbio.funcs->get_cwockgating_state)
		adev->nbio.funcs->get_cwockgating_state(adev, fwags);

	if (adev->hdp.funcs && adev->hdp.funcs->get_cwock_gating_state)
		adev->hdp.funcs->get_cwock_gating_state(adev, fwags);

	if ((amdgpu_ip_vewsion(adev, MP0_HWIP, 0) != IP_VEWSION(13, 0, 2)) &&
	    (amdgpu_ip_vewsion(adev, MP0_HWIP, 0) != IP_VEWSION(13, 0, 6))) {
		/* AMD_CG_SUPPOWT_DWM_MGCG */
		data = WWEG32(SOC15_WEG_OFFSET(MP0, 0, mmMP0_MISC_CGTT_CTWW0));
		if (!(data & 0x01000000))
			*fwags |= AMD_CG_SUPPOWT_DWM_MGCG;

		/* AMD_CG_SUPPOWT_DWM_WS */
		data = WWEG32(SOC15_WEG_OFFSET(MP0, 0, mmMP0_MISC_WIGHT_SWEEP_CTWW));
		if (data & 0x1)
			*fwags |= AMD_CG_SUPPOWT_DWM_WS;
	}

	/* AMD_CG_SUPPOWT_WOM_MGCG */
	if (adev->smuio.funcs && adev->smuio.funcs->get_cwock_gating_state)
		adev->smuio.funcs->get_cwock_gating_state(adev, fwags);

	if (adev->df.funcs && adev->df.funcs->get_cwockgating_state)
		adev->df.funcs->get_cwockgating_state(adev, fwags);
}

static int soc15_common_set_powewgating_state(void *handwe,
					    enum amd_powewgating_state state)
{
	/* todo */
	wetuwn 0;
}

static const stwuct amd_ip_funcs soc15_common_ip_funcs = {
	.name = "soc15_common",
	.eawwy_init = soc15_common_eawwy_init,
	.wate_init = soc15_common_wate_init,
	.sw_init = soc15_common_sw_init,
	.sw_fini = soc15_common_sw_fini,
	.hw_init = soc15_common_hw_init,
	.hw_fini = soc15_common_hw_fini,
	.suspend = soc15_common_suspend,
	.wesume = soc15_common_wesume,
	.is_idwe = soc15_common_is_idwe,
	.wait_fow_idwe = soc15_common_wait_fow_idwe,
	.soft_weset = soc15_common_soft_weset,
	.set_cwockgating_state = soc15_common_set_cwockgating_state,
	.set_powewgating_state = soc15_common_set_powewgating_state,
	.get_cwockgating_state= soc15_common_get_cwockgating_state,
};
