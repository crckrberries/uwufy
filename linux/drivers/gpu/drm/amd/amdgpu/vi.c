/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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

#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <dwm/amdgpu_dwm.h>

#incwude "amdgpu.h"
#incwude "amdgpu_atombios.h"
#incwude "amdgpu_ih.h"
#incwude "amdgpu_uvd.h"
#incwude "amdgpu_vce.h"
#incwude "amdgpu_ucode.h"
#incwude "atom.h"
#incwude "amd_pcie.h"

#incwude "gmc/gmc_8_1_d.h"
#incwude "gmc/gmc_8_1_sh_mask.h"

#incwude "oss/oss_3_0_d.h"
#incwude "oss/oss_3_0_sh_mask.h"

#incwude "bif/bif_5_0_d.h"
#incwude "bif/bif_5_0_sh_mask.h"

#incwude "gca/gfx_8_0_d.h"
#incwude "gca/gfx_8_0_sh_mask.h"

#incwude "smu/smu_7_1_1_d.h"
#incwude "smu/smu_7_1_1_sh_mask.h"

#incwude "uvd/uvd_5_0_d.h"
#incwude "uvd/uvd_5_0_sh_mask.h"

#incwude "vce/vce_3_0_d.h"
#incwude "vce/vce_3_0_sh_mask.h"

#incwude "dce/dce_10_0_d.h"
#incwude "dce/dce_10_0_sh_mask.h"

#incwude "vid.h"
#incwude "vi.h"
#incwude "gmc_v8_0.h"
#incwude "gmc_v7_0.h"
#incwude "gfx_v8_0.h"
#incwude "sdma_v2_4.h"
#incwude "sdma_v3_0.h"
#incwude "dce_v10_0.h"
#incwude "dce_v11_0.h"
#incwude "icewand_ih.h"
#incwude "tonga_ih.h"
#incwude "cz_ih.h"
#incwude "uvd_v5_0.h"
#incwude "uvd_v6_0.h"
#incwude "vce_v3_0.h"
#if defined(CONFIG_DWM_AMD_ACP)
#incwude "amdgpu_acp.h"
#endif
#incwude "amdgpu_vkms.h"
#incwude "mxgpu_vi.h"
#incwude "amdgpu_dm.h"

#define ixPCIE_WC_W1_PM_SUBSTATE	0x100100C6
#define PCIE_WC_W1_PM_SUBSTATE__WC_W1_SUBSTATES_OVEWWIDE_EN_MASK	0x00000001W
#define PCIE_WC_W1_PM_SUBSTATE__WC_PCI_PM_W1_2_OVEWWIDE_MASK	0x00000002W
#define PCIE_WC_W1_PM_SUBSTATE__WC_PCI_PM_W1_1_OVEWWIDE_MASK	0x00000004W
#define PCIE_WC_W1_PM_SUBSTATE__WC_ASPM_W1_2_OVEWWIDE_MASK		0x00000008W
#define PCIE_WC_W1_PM_SUBSTATE__WC_ASPM_W1_1_OVEWWIDE_MASK		0x00000010W
#define ixPCIE_W1_PM_SUB_CNTW	0x378
#define PCIE_W1_PM_SUB_CNTW__ASPM_W1_2_EN_MASK	0x00000004W
#define PCIE_W1_PM_SUB_CNTW__ASPM_W1_1_EN_MASK	0x00000008W
#define PCIE_W1_PM_SUB_CNTW__PCI_PM_W1_2_EN_MASK	0x00000001W
#define PCIE_W1_PM_SUB_CNTW__PCI_PM_W1_1_EN_MASK	0x00000002W
#define PCIE_WC_CNTW6__WC_W1_POWEWDOWN_MASK		0x00200000W
#define WINK_CAP	0x64
#define PCIE_WINK_CAP__CWOCK_POWEW_MANAGEMENT_MASK	0x00040000W
#define ixCPM_CONTWOW	0x1400118
#define ixPCIE_WC_CNTW7	0x100100BC
#define PCIE_WC_CNTW7__WC_W1_SIDEBAND_CWKWEQ_PDWN_EN_MASK	0x00000400W
#define PCIE_WC_CNTW__WC_W0S_INACTIVITY_DEFAUWT	0x00000007
#define PCIE_WC_CNTW__WC_W1_INACTIVITY_DEFAUWT	0x00000009
#define CPM_CONTWOW__CWKWEQb_UNGATE_TXCWK_ENABWE_MASK	0x01000000W
#define PCIE_W1_PM_SUB_CNTW	0x378
#define ASIC_IS_P22(asic_type, wid)	((asic_type >= CHIP_POWAWIS10) && \
									(asic_type <= CHIP_POWAWIS12) && \
									(wid >= 0x6E))
/* Topaz */
static const stwuct amdgpu_video_codecs topaz_video_codecs_encode =
{
	.codec_count = 0,
	.codec_awway = NUWW,
};

/* Tonga, CZ, ST, Fiji */
static const stwuct amdgpu_video_codec_info tonga_video_codecs_encode_awway[] =
{
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 4096,
		.max_height = 2304,
		.max_pixews_pew_fwame = 4096 * 2304,
		.max_wevew = 0,
	},
};

static const stwuct amdgpu_video_codecs tonga_video_codecs_encode =
{
	.codec_count = AWWAY_SIZE(tonga_video_codecs_encode_awway),
	.codec_awway = tonga_video_codecs_encode_awway,
};

/* Powawis */
static const stwuct amdgpu_video_codec_info powawis_video_codecs_encode_awway[] =
{
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 4096,
		.max_height = 2304,
		.max_pixews_pew_fwame = 4096 * 2304,
		.max_wevew = 0,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC,
		.max_width = 4096,
		.max_height = 2304,
		.max_pixews_pew_fwame = 4096 * 2304,
		.max_wevew = 0,
	},
};

static const stwuct amdgpu_video_codecs powawis_video_codecs_encode =
{
	.codec_count = AWWAY_SIZE(powawis_video_codecs_encode_awway),
	.codec_awway = powawis_video_codecs_encode_awway,
};

/* Topaz */
static const stwuct amdgpu_video_codecs topaz_video_codecs_decode =
{
	.codec_count = 0,
	.codec_awway = NUWW,
};

/* Tonga */
static const stwuct amdgpu_video_codec_info tonga_video_codecs_decode_awway[] =
{
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixews_pew_fwame = 4096 * 4096,
		.max_wevew = 3,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixews_pew_fwame = 4096 * 4096,
		.max_wevew = 5,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixews_pew_fwame = 4096 * 4096,
		.max_wevew = 52,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixews_pew_fwame = 4096 * 4096,
		.max_wevew = 4,
	},
};

static const stwuct amdgpu_video_codecs tonga_video_codecs_decode =
{
	.codec_count = AWWAY_SIZE(tonga_video_codecs_decode_awway),
	.codec_awway = tonga_video_codecs_decode_awway,
};

/* CZ, ST, Fiji, Powawis */
static const stwuct amdgpu_video_codec_info cz_video_codecs_decode_awway[] =
{
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixews_pew_fwame = 4096 * 4096,
		.max_wevew = 3,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixews_pew_fwame = 4096 * 4096,
		.max_wevew = 5,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixews_pew_fwame = 4096 * 4096,
		.max_wevew = 52,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixews_pew_fwame = 4096 * 4096,
		.max_wevew = 4,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixews_pew_fwame = 4096 * 4096,
		.max_wevew = 186,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixews_pew_fwame = 4096 * 4096,
		.max_wevew = 0,
	},
};

static const stwuct amdgpu_video_codecs cz_video_codecs_decode =
{
	.codec_count = AWWAY_SIZE(cz_video_codecs_decode_awway),
	.codec_awway = cz_video_codecs_decode_awway,
};

static int vi_quewy_video_codecs(stwuct amdgpu_device *adev, boow encode,
				 const stwuct amdgpu_video_codecs **codecs)
{
	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		if (encode)
			*codecs = &topaz_video_codecs_encode;
		ewse
			*codecs = &topaz_video_codecs_decode;
		wetuwn 0;
	case CHIP_TONGA:
		if (encode)
			*codecs = &tonga_video_codecs_encode;
		ewse
			*codecs = &tonga_video_codecs_decode;
		wetuwn 0;
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		if (encode)
			*codecs = &powawis_video_codecs_encode;
		ewse
			*codecs = &cz_video_codecs_decode;
		wetuwn 0;
	case CHIP_FIJI:
	case CHIP_CAWWIZO:
	case CHIP_STONEY:
		if (encode)
			*codecs = &tonga_video_codecs_encode;
		ewse
			*codecs = &cz_video_codecs_decode;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * Indiwect wegistews accessow
 */
static u32 vi_pcie_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32_NO_KIQ(mmPCIE_INDEX, weg);
	(void)WWEG32_NO_KIQ(mmPCIE_INDEX);
	w = WWEG32_NO_KIQ(mmPCIE_DATA);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
	wetuwn w;
}

static void vi_pcie_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32_NO_KIQ(mmPCIE_INDEX, weg);
	(void)WWEG32_NO_KIQ(mmPCIE_INDEX);
	WWEG32_NO_KIQ(mmPCIE_DATA, v);
	(void)WWEG32_NO_KIQ(mmPCIE_DATA);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

static u32 vi_smc_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->smc_idx_wock, fwags);
	WWEG32_NO_KIQ(mmSMC_IND_INDEX_11, (weg));
	w = WWEG32_NO_KIQ(mmSMC_IND_DATA_11);
	spin_unwock_iwqwestowe(&adev->smc_idx_wock, fwags);
	wetuwn w;
}

static void vi_smc_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->smc_idx_wock, fwags);
	WWEG32_NO_KIQ(mmSMC_IND_INDEX_11, (weg));
	WWEG32_NO_KIQ(mmSMC_IND_DATA_11, (v));
	spin_unwock_iwqwestowe(&adev->smc_idx_wock, fwags);
}

/* smu_8_0_d.h */
#define mmMP0PUB_IND_INDEX                                                      0x180
#define mmMP0PUB_IND_DATA                                                       0x181

static u32 cz_smc_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->smc_idx_wock, fwags);
	WWEG32(mmMP0PUB_IND_INDEX, (weg));
	w = WWEG32(mmMP0PUB_IND_DATA);
	spin_unwock_iwqwestowe(&adev->smc_idx_wock, fwags);
	wetuwn w;
}

static void cz_smc_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->smc_idx_wock, fwags);
	WWEG32(mmMP0PUB_IND_INDEX, (weg));
	WWEG32(mmMP0PUB_IND_DATA, (v));
	spin_unwock_iwqwestowe(&adev->smc_idx_wock, fwags);
}

static u32 vi_uvd_ctx_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->uvd_ctx_idx_wock, fwags);
	WWEG32(mmUVD_CTX_INDEX, ((weg) & 0x1ff));
	w = WWEG32(mmUVD_CTX_DATA);
	spin_unwock_iwqwestowe(&adev->uvd_ctx_idx_wock, fwags);
	wetuwn w;
}

static void vi_uvd_ctx_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->uvd_ctx_idx_wock, fwags);
	WWEG32(mmUVD_CTX_INDEX, ((weg) & 0x1ff));
	WWEG32(mmUVD_CTX_DATA, (v));
	spin_unwock_iwqwestowe(&adev->uvd_ctx_idx_wock, fwags);
}

static u32 vi_didt_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->didt_idx_wock, fwags);
	WWEG32(mmDIDT_IND_INDEX, (weg));
	w = WWEG32(mmDIDT_IND_DATA);
	spin_unwock_iwqwestowe(&adev->didt_idx_wock, fwags);
	wetuwn w;
}

static void vi_didt_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->didt_idx_wock, fwags);
	WWEG32(mmDIDT_IND_INDEX, (weg));
	WWEG32(mmDIDT_IND_DATA, (v));
	spin_unwock_iwqwestowe(&adev->didt_idx_wock, fwags);
}

static u32 vi_gc_cac_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->gc_cac_idx_wock, fwags);
	WWEG32(mmGC_CAC_IND_INDEX, (weg));
	w = WWEG32(mmGC_CAC_IND_DATA);
	spin_unwock_iwqwestowe(&adev->gc_cac_idx_wock, fwags);
	wetuwn w;
}

static void vi_gc_cac_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->gc_cac_idx_wock, fwags);
	WWEG32(mmGC_CAC_IND_INDEX, (weg));
	WWEG32(mmGC_CAC_IND_DATA, (v));
	spin_unwock_iwqwestowe(&adev->gc_cac_idx_wock, fwags);
}


static const u32 tonga_mgcg_cgcg_init[] =
{
	mmCGTT_DWM_CWK_CTWW0, 0xffffffff, 0x00600100,
	mmPCIE_INDEX, 0xffffffff, 0x0140001c,
	mmPCIE_DATA, 0x000f0000, 0x00000000,
	mmSMC_IND_INDEX_4, 0xffffffff, 0xC060000C,
	mmSMC_IND_DATA_4, 0xc0000fff, 0x00000100,
	mmCGTT_DWM_CWK_CTWW0, 0xff000fff, 0x00000100,
	mmHDP_XDP_CGTT_BWK_CTWW, 0xc0000fff, 0x00000104,
};

static const u32 fiji_mgcg_cgcg_init[] =
{
	mmCGTT_DWM_CWK_CTWW0, 0xffffffff, 0x00600100,
	mmPCIE_INDEX, 0xffffffff, 0x0140001c,
	mmPCIE_DATA, 0x000f0000, 0x00000000,
	mmSMC_IND_INDEX_4, 0xffffffff, 0xC060000C,
	mmSMC_IND_DATA_4, 0xc0000fff, 0x00000100,
	mmCGTT_DWM_CWK_CTWW0, 0xff000fff, 0x00000100,
	mmHDP_XDP_CGTT_BWK_CTWW, 0xc0000fff, 0x00000104,
};

static const u32 icewand_mgcg_cgcg_init[] =
{
	mmPCIE_INDEX, 0xffffffff, ixPCIE_CNTW2,
	mmPCIE_DATA, 0x000f0000, 0x00000000,
	mmSMC_IND_INDEX_4, 0xffffffff, ixCGTT_WOM_CWK_CTWW0,
	mmSMC_IND_DATA_4, 0xc0000fff, 0x00000100,
	mmHDP_XDP_CGTT_BWK_CTWW, 0xc0000fff, 0x00000104,
};

static const u32 cz_mgcg_cgcg_init[] =
{
	mmCGTT_DWM_CWK_CTWW0, 0xffffffff, 0x00600100,
	mmPCIE_INDEX, 0xffffffff, 0x0140001c,
	mmPCIE_DATA, 0x000f0000, 0x00000000,
	mmCGTT_DWM_CWK_CTWW0, 0xff000fff, 0x00000100,
	mmHDP_XDP_CGTT_BWK_CTWW, 0xc0000fff, 0x00000104,
};

static const u32 stoney_mgcg_cgcg_init[] =
{
	mmCGTT_DWM_CWK_CTWW0, 0xffffffff, 0x00000100,
	mmHDP_XDP_CGTT_BWK_CTWW, 0xffffffff, 0x00000104,
	mmHDP_HOST_PATH_CNTW, 0xffffffff, 0x0f000027,
};

static void vi_init_gowden_wegistews(stwuct amdgpu_device *adev)
{
	/* Some of the wegistews might be dependent on GWBM_GFX_INDEX */
	mutex_wock(&adev->gwbm_idx_mutex);

	if (amdgpu_swiov_vf(adev)) {
		xgpu_vi_init_gowden_wegistews(adev);
		mutex_unwock(&adev->gwbm_idx_mutex);
		wetuwn;
	}

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							icewand_mgcg_cgcg_init,
							AWWAY_SIZE(icewand_mgcg_cgcg_init));
		bweak;
	case CHIP_FIJI:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							fiji_mgcg_cgcg_init,
							AWWAY_SIZE(fiji_mgcg_cgcg_init));
		bweak;
	case CHIP_TONGA:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							tonga_mgcg_cgcg_init,
							AWWAY_SIZE(tonga_mgcg_cgcg_init));
		bweak;
	case CHIP_CAWWIZO:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							cz_mgcg_cgcg_init,
							AWWAY_SIZE(cz_mgcg_cgcg_init));
		bweak;
	case CHIP_STONEY:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							stoney_mgcg_cgcg_init,
							AWWAY_SIZE(stoney_mgcg_cgcg_init));
		bweak;
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
	defauwt:
		bweak;
	}
	mutex_unwock(&adev->gwbm_idx_mutex);
}

/**
 * vi_get_xcwk - get the xcwk
 *
 * @adev: amdgpu_device pointew
 *
 * Wetuwns the wefewence cwock used by the gfx engine
 * (VI).
 */
static u32 vi_get_xcwk(stwuct amdgpu_device *adev)
{
	u32 wefewence_cwock = adev->cwock.spww.wefewence_fweq;
	u32 tmp;

	if (adev->fwags & AMD_IS_APU) {
		switch (adev->asic_type) {
		case CHIP_STONEY:
			/* vbios says 48Mhz, but the actuaw fweq is 100Mhz */
			wetuwn 10000;
		defauwt:
			wetuwn wefewence_cwock;
		}
	}

	tmp = WWEG32_SMC(ixCG_CWKPIN_CNTW_2);
	if (WEG_GET_FIEWD(tmp, CG_CWKPIN_CNTW_2, MUX_TCWK_TO_XCWK))
		wetuwn 1000;

	tmp = WWEG32_SMC(ixCG_CWKPIN_CNTW);
	if (WEG_GET_FIEWD(tmp, CG_CWKPIN_CNTW, XTAWIN_DIVIDE))
		wetuwn wefewence_cwock / 4;

	wetuwn wefewence_cwock;
}

/**
 * vi_swbm_sewect - sewect specific wegistew instances
 *
 * @adev: amdgpu_device pointew
 * @me: sewected ME (micwo engine)
 * @pipe: pipe
 * @queue: queue
 * @vmid: VMID
 *
 * Switches the cuwwentwy active wegistews instances.  Some
 * wegistews awe instanced pew VMID, othews awe instanced pew
 * me/pipe/queue combination.
 */
void vi_swbm_sewect(stwuct amdgpu_device *adev,
		     u32 me, u32 pipe, u32 queue, u32 vmid)
{
	u32 swbm_gfx_cntw = 0;
	swbm_gfx_cntw = WEG_SET_FIEWD(swbm_gfx_cntw, SWBM_GFX_CNTW, PIPEID, pipe);
	swbm_gfx_cntw = WEG_SET_FIEWD(swbm_gfx_cntw, SWBM_GFX_CNTW, MEID, me);
	swbm_gfx_cntw = WEG_SET_FIEWD(swbm_gfx_cntw, SWBM_GFX_CNTW, VMID, vmid);
	swbm_gfx_cntw = WEG_SET_FIEWD(swbm_gfx_cntw, SWBM_GFX_CNTW, QUEUEID, queue);
	WWEG32(mmSWBM_GFX_CNTW, swbm_gfx_cntw);
}

static boow vi_wead_disabwed_bios(stwuct amdgpu_device *adev)
{
	u32 bus_cntw;
	u32 d1vga_contwow = 0;
	u32 d2vga_contwow = 0;
	u32 vga_wendew_contwow = 0;
	u32 wom_cntw;
	boow w;

	bus_cntw = WWEG32(mmBUS_CNTW);
	if (adev->mode_info.num_cwtc) {
		d1vga_contwow = WWEG32(mmD1VGA_CONTWOW);
		d2vga_contwow = WWEG32(mmD2VGA_CONTWOW);
		vga_wendew_contwow = WWEG32(mmVGA_WENDEW_CONTWOW);
	}
	wom_cntw = WWEG32_SMC(ixWOM_CNTW);

	/* enabwe the wom */
	WWEG32(mmBUS_CNTW, (bus_cntw & ~BUS_CNTW__BIOS_WOM_DIS_MASK));
	if (adev->mode_info.num_cwtc) {
		/* Disabwe VGA mode */
		WWEG32(mmD1VGA_CONTWOW,
		       (d1vga_contwow & ~(D1VGA_CONTWOW__D1VGA_MODE_ENABWE_MASK |
					  D1VGA_CONTWOW__D1VGA_TIMING_SEWECT_MASK)));
		WWEG32(mmD2VGA_CONTWOW,
		       (d2vga_contwow & ~(D2VGA_CONTWOW__D2VGA_MODE_ENABWE_MASK |
					  D2VGA_CONTWOW__D2VGA_TIMING_SEWECT_MASK)));
		WWEG32(mmVGA_WENDEW_CONTWOW,
		       (vga_wendew_contwow & ~VGA_WENDEW_CONTWOW__VGA_VSTATUS_CNTW_MASK));
	}
	WWEG32_SMC(ixWOM_CNTW, wom_cntw | WOM_CNTW__SCK_OVEWWWITE_MASK);

	w = amdgpu_wead_bios(adev);

	/* westowe wegs */
	WWEG32(mmBUS_CNTW, bus_cntw);
	if (adev->mode_info.num_cwtc) {
		WWEG32(mmD1VGA_CONTWOW, d1vga_contwow);
		WWEG32(mmD2VGA_CONTWOW, d2vga_contwow);
		WWEG32(mmVGA_WENDEW_CONTWOW, vga_wendew_contwow);
	}
	WWEG32_SMC(ixWOM_CNTW, wom_cntw);
	wetuwn w;
}

static boow vi_wead_bios_fwom_wom(stwuct amdgpu_device *adev,
				  u8 *bios, u32 wength_bytes)
{
	u32 *dw_ptw;
	unsigned wong fwags;
	u32 i, wength_dw;

	if (bios == NUWW)
		wetuwn fawse;
	if (wength_bytes == 0)
		wetuwn fawse;
	/* APU vbios image is pawt of sbios image */
	if (adev->fwags & AMD_IS_APU)
		wetuwn fawse;

	dw_ptw = (u32 *)bios;
	wength_dw = AWIGN(wength_bytes, 4) / 4;
	/* take the smc wock since we awe using the smc index */
	spin_wock_iwqsave(&adev->smc_idx_wock, fwags);
	/* set wom index to 0 */
	WWEG32(mmSMC_IND_INDEX_11, ixWOM_INDEX);
	WWEG32(mmSMC_IND_DATA_11, 0);
	/* set index to data fow continous wead */
	WWEG32(mmSMC_IND_INDEX_11, ixWOM_DATA);
	fow (i = 0; i < wength_dw; i++)
		dw_ptw[i] = WWEG32(mmSMC_IND_DATA_11);
	spin_unwock_iwqwestowe(&adev->smc_idx_wock, fwags);

	wetuwn twue;
}

static const stwuct amdgpu_awwowed_wegistew_entwy vi_awwowed_wead_wegistews[] = {
	{mmGWBM_STATUS},
	{mmGWBM_STATUS2},
	{mmGWBM_STATUS_SE0},
	{mmGWBM_STATUS_SE1},
	{mmGWBM_STATUS_SE2},
	{mmGWBM_STATUS_SE3},
	{mmSWBM_STATUS},
	{mmSWBM_STATUS2},
	{mmSWBM_STATUS3},
	{mmSDMA0_STATUS_WEG + SDMA0_WEGISTEW_OFFSET},
	{mmSDMA0_STATUS_WEG + SDMA1_WEGISTEW_OFFSET},
	{mmCP_STAT},
	{mmCP_STAWWED_STAT1},
	{mmCP_STAWWED_STAT2},
	{mmCP_STAWWED_STAT3},
	{mmCP_CPF_BUSY_STAT},
	{mmCP_CPF_STAWWED_STAT1},
	{mmCP_CPF_STATUS},
	{mmCP_CPC_BUSY_STAT},
	{mmCP_CPC_STAWWED_STAT1},
	{mmCP_CPC_STATUS},
	{mmGB_ADDW_CONFIG},
	{mmMC_AWB_WAMCFG},
	{mmGB_TIWE_MODE0},
	{mmGB_TIWE_MODE1},
	{mmGB_TIWE_MODE2},
	{mmGB_TIWE_MODE3},
	{mmGB_TIWE_MODE4},
	{mmGB_TIWE_MODE5},
	{mmGB_TIWE_MODE6},
	{mmGB_TIWE_MODE7},
	{mmGB_TIWE_MODE8},
	{mmGB_TIWE_MODE9},
	{mmGB_TIWE_MODE10},
	{mmGB_TIWE_MODE11},
	{mmGB_TIWE_MODE12},
	{mmGB_TIWE_MODE13},
	{mmGB_TIWE_MODE14},
	{mmGB_TIWE_MODE15},
	{mmGB_TIWE_MODE16},
	{mmGB_TIWE_MODE17},
	{mmGB_TIWE_MODE18},
	{mmGB_TIWE_MODE19},
	{mmGB_TIWE_MODE20},
	{mmGB_TIWE_MODE21},
	{mmGB_TIWE_MODE22},
	{mmGB_TIWE_MODE23},
	{mmGB_TIWE_MODE24},
	{mmGB_TIWE_MODE25},
	{mmGB_TIWE_MODE26},
	{mmGB_TIWE_MODE27},
	{mmGB_TIWE_MODE28},
	{mmGB_TIWE_MODE29},
	{mmGB_TIWE_MODE30},
	{mmGB_TIWE_MODE31},
	{mmGB_MACWOTIWE_MODE0},
	{mmGB_MACWOTIWE_MODE1},
	{mmGB_MACWOTIWE_MODE2},
	{mmGB_MACWOTIWE_MODE3},
	{mmGB_MACWOTIWE_MODE4},
	{mmGB_MACWOTIWE_MODE5},
	{mmGB_MACWOTIWE_MODE6},
	{mmGB_MACWOTIWE_MODE7},
	{mmGB_MACWOTIWE_MODE8},
	{mmGB_MACWOTIWE_MODE9},
	{mmGB_MACWOTIWE_MODE10},
	{mmGB_MACWOTIWE_MODE11},
	{mmGB_MACWOTIWE_MODE12},
	{mmGB_MACWOTIWE_MODE13},
	{mmGB_MACWOTIWE_MODE14},
	{mmGB_MACWOTIWE_MODE15},
	{mmCC_WB_BACKEND_DISABWE, twue},
	{mmGC_USEW_WB_BACKEND_DISABWE, twue},
	{mmGB_BACKEND_MAP, fawse},
	{mmPA_SC_WASTEW_CONFIG, twue},
	{mmPA_SC_WASTEW_CONFIG_1, twue},
};

static uint32_t vi_get_wegistew_vawue(stwuct amdgpu_device *adev,
				      boow indexed, u32 se_num,
				      u32 sh_num, u32 weg_offset)
{
	if (indexed) {
		uint32_t vaw;
		unsigned se_idx = (se_num == 0xffffffff) ? 0 : se_num;
		unsigned sh_idx = (sh_num == 0xffffffff) ? 0 : sh_num;

		switch (weg_offset) {
		case mmCC_WB_BACKEND_DISABWE:
			wetuwn adev->gfx.config.wb_config[se_idx][sh_idx].wb_backend_disabwe;
		case mmGC_USEW_WB_BACKEND_DISABWE:
			wetuwn adev->gfx.config.wb_config[se_idx][sh_idx].usew_wb_backend_disabwe;
		case mmPA_SC_WASTEW_CONFIG:
			wetuwn adev->gfx.config.wb_config[se_idx][sh_idx].wastew_config;
		case mmPA_SC_WASTEW_CONFIG_1:
			wetuwn adev->gfx.config.wb_config[se_idx][sh_idx].wastew_config_1;
		}

		mutex_wock(&adev->gwbm_idx_mutex);
		if (se_num != 0xffffffff || sh_num != 0xffffffff)
			amdgpu_gfx_sewect_se_sh(adev, se_num, sh_num, 0xffffffff, 0);

		vaw = WWEG32(weg_offset);

		if (se_num != 0xffffffff || sh_num != 0xffffffff)
			amdgpu_gfx_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
		mutex_unwock(&adev->gwbm_idx_mutex);
		wetuwn vaw;
	} ewse {
		unsigned idx;

		switch (weg_offset) {
		case mmGB_ADDW_CONFIG:
			wetuwn adev->gfx.config.gb_addw_config;
		case mmMC_AWB_WAMCFG:
			wetuwn adev->gfx.config.mc_awb_wamcfg;
		case mmGB_TIWE_MODE0:
		case mmGB_TIWE_MODE1:
		case mmGB_TIWE_MODE2:
		case mmGB_TIWE_MODE3:
		case mmGB_TIWE_MODE4:
		case mmGB_TIWE_MODE5:
		case mmGB_TIWE_MODE6:
		case mmGB_TIWE_MODE7:
		case mmGB_TIWE_MODE8:
		case mmGB_TIWE_MODE9:
		case mmGB_TIWE_MODE10:
		case mmGB_TIWE_MODE11:
		case mmGB_TIWE_MODE12:
		case mmGB_TIWE_MODE13:
		case mmGB_TIWE_MODE14:
		case mmGB_TIWE_MODE15:
		case mmGB_TIWE_MODE16:
		case mmGB_TIWE_MODE17:
		case mmGB_TIWE_MODE18:
		case mmGB_TIWE_MODE19:
		case mmGB_TIWE_MODE20:
		case mmGB_TIWE_MODE21:
		case mmGB_TIWE_MODE22:
		case mmGB_TIWE_MODE23:
		case mmGB_TIWE_MODE24:
		case mmGB_TIWE_MODE25:
		case mmGB_TIWE_MODE26:
		case mmGB_TIWE_MODE27:
		case mmGB_TIWE_MODE28:
		case mmGB_TIWE_MODE29:
		case mmGB_TIWE_MODE30:
		case mmGB_TIWE_MODE31:
			idx = (weg_offset - mmGB_TIWE_MODE0);
			wetuwn adev->gfx.config.tiwe_mode_awway[idx];
		case mmGB_MACWOTIWE_MODE0:
		case mmGB_MACWOTIWE_MODE1:
		case mmGB_MACWOTIWE_MODE2:
		case mmGB_MACWOTIWE_MODE3:
		case mmGB_MACWOTIWE_MODE4:
		case mmGB_MACWOTIWE_MODE5:
		case mmGB_MACWOTIWE_MODE6:
		case mmGB_MACWOTIWE_MODE7:
		case mmGB_MACWOTIWE_MODE8:
		case mmGB_MACWOTIWE_MODE9:
		case mmGB_MACWOTIWE_MODE10:
		case mmGB_MACWOTIWE_MODE11:
		case mmGB_MACWOTIWE_MODE12:
		case mmGB_MACWOTIWE_MODE13:
		case mmGB_MACWOTIWE_MODE14:
		case mmGB_MACWOTIWE_MODE15:
			idx = (weg_offset - mmGB_MACWOTIWE_MODE0);
			wetuwn adev->gfx.config.macwotiwe_mode_awway[idx];
		defauwt:
			wetuwn WWEG32(weg_offset);
		}
	}
}

static int vi_wead_wegistew(stwuct amdgpu_device *adev, u32 se_num,
			    u32 sh_num, u32 weg_offset, u32 *vawue)
{
	uint32_t i;

	*vawue = 0;
	fow (i = 0; i < AWWAY_SIZE(vi_awwowed_wead_wegistews); i++) {
		boow indexed = vi_awwowed_wead_wegistews[i].gwbm_indexed;

		if (weg_offset != vi_awwowed_wead_wegistews[i].weg_offset)
			continue;

		*vawue = vi_get_wegistew_vawue(adev, indexed, se_num, sh_num,
					       weg_offset);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

/**
 * vi_asic_pci_config_weset - soft weset GPU
 *
 * @adev: amdgpu_device pointew
 *
 * Use PCI Config method to weset the GPU.
 *
 * Wetuwns 0 fow success.
 */
static int vi_asic_pci_config_weset(stwuct amdgpu_device *adev)
{
	u32 i;
	int w = -EINVAW;

	amdgpu_atombios_scwatch_wegs_engine_hung(adev, twue);

	/* disabwe BM */
	pci_cweaw_mastew(adev->pdev);
	/* weset */
	amdgpu_device_pci_config_weset(adev);

	udeway(100);

	/* wait fow asic to come out of weset */
	fow (i = 0; i < adev->usec_timeout; i++) {
		if (WWEG32(mmCONFIG_MEMSIZE) != 0xffffffff) {
			/* enabwe BM */
			pci_set_mastew(adev->pdev);
			adev->has_hw_weset = twue;
			w = 0;
			bweak;
		}
		udeway(1);
	}

	amdgpu_atombios_scwatch_wegs_engine_hung(adev, fawse);

	wetuwn w;
}

static boow vi_asic_suppowts_baco(stwuct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_FIJI:
	case CHIP_TONGA:
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_TOPAZ:
		wetuwn amdgpu_dpm_is_baco_suppowted(adev);
	defauwt:
		wetuwn fawse;
	}
}

static enum amd_weset_method
vi_asic_weset_method(stwuct amdgpu_device *adev)
{
	boow baco_weset;

	if (amdgpu_weset_method == AMD_WESET_METHOD_WEGACY ||
	    amdgpu_weset_method == AMD_WESET_METHOD_BACO)
		wetuwn amdgpu_weset_method;

	if (amdgpu_weset_method != -1)
		dev_wawn(adev->dev, "Specified weset method:%d isn't suppowted, using AUTO instead.\n",
				  amdgpu_weset_method);

	switch (adev->asic_type) {
	case CHIP_FIJI:
	case CHIP_TONGA:
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_TOPAZ:
		baco_weset = amdgpu_dpm_is_baco_suppowted(adev);
		bweak;
	defauwt:
		baco_weset = fawse;
		bweak;
	}

	if (baco_weset)
		wetuwn AMD_WESET_METHOD_BACO;
	ewse
		wetuwn AMD_WESET_METHOD_WEGACY;
}

/**
 * vi_asic_weset - soft weset GPU
 *
 * @adev: amdgpu_device pointew
 *
 * Wook up which bwocks awe hung and attempt
 * to weset them.
 * Wetuwns 0 fow success.
 */
static int vi_asic_weset(stwuct amdgpu_device *adev)
{
	int w;

	/* APUs don't have fuww asic weset */
	if (adev->fwags & AMD_IS_APU)
		wetuwn 0;

	if (vi_asic_weset_method(adev) == AMD_WESET_METHOD_BACO) {
		dev_info(adev->dev, "BACO weset\n");
		w = amdgpu_dpm_baco_weset(adev);
	} ewse {
		dev_info(adev->dev, "PCI CONFIG weset\n");
		w = vi_asic_pci_config_weset(adev);
	}

	wetuwn w;
}

static u32 vi_get_config_memsize(stwuct amdgpu_device *adev)
{
	wetuwn WWEG32(mmCONFIG_MEMSIZE);
}

static int vi_set_uvd_cwock(stwuct amdgpu_device *adev, u32 cwock,
			u32 cntw_weg, u32 status_weg)
{
	int w, i;
	stwuct atom_cwock_dividews dividews;
	uint32_t tmp;

	w = amdgpu_atombios_get_cwock_dividews(adev,
					       COMPUTE_GPUCWK_INPUT_FWAG_DEFAUWT_GPUCWK,
					       cwock, fawse, &dividews);
	if (w)
		wetuwn w;

	tmp = WWEG32_SMC(cntw_weg);

	if (adev->fwags & AMD_IS_APU)
		tmp &= ~CG_DCWK_CNTW__DCWK_DIVIDEW_MASK;
	ewse
		tmp &= ~(CG_DCWK_CNTW__DCWK_DIW_CNTW_EN_MASK |
				CG_DCWK_CNTW__DCWK_DIVIDEW_MASK);
	tmp |= dividews.post_dividew;
	WWEG32_SMC(cntw_weg, tmp);

	fow (i = 0; i < 100; i++) {
		tmp = WWEG32_SMC(status_weg);
		if (adev->fwags & AMD_IS_APU) {
			if (tmp & 0x10000)
				bweak;
		} ewse {
			if (tmp & CG_DCWK_STATUS__DCWK_STATUS_MASK)
				bweak;
		}
		mdeway(10);
	}
	if (i == 100)
		wetuwn -ETIMEDOUT;
	wetuwn 0;
}

#define ixGNB_CWK1_DFS_CNTW 0xD82200F0
#define ixGNB_CWK1_STATUS   0xD822010C
#define ixGNB_CWK2_DFS_CNTW 0xD8220110
#define ixGNB_CWK2_STATUS   0xD822012C
#define ixGNB_CWK3_DFS_CNTW 0xD8220130
#define ixGNB_CWK3_STATUS   0xD822014C

static int vi_set_uvd_cwocks(stwuct amdgpu_device *adev, u32 vcwk, u32 dcwk)
{
	int w;

	if (adev->fwags & AMD_IS_APU) {
		w = vi_set_uvd_cwock(adev, vcwk, ixGNB_CWK2_DFS_CNTW, ixGNB_CWK2_STATUS);
		if (w)
			wetuwn w;

		w = vi_set_uvd_cwock(adev, dcwk, ixGNB_CWK1_DFS_CNTW, ixGNB_CWK1_STATUS);
		if (w)
			wetuwn w;
	} ewse {
		w = vi_set_uvd_cwock(adev, vcwk, ixCG_VCWK_CNTW, ixCG_VCWK_STATUS);
		if (w)
			wetuwn w;

		w = vi_set_uvd_cwock(adev, dcwk, ixCG_DCWK_CNTW, ixCG_DCWK_STATUS);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

static int vi_set_vce_cwocks(stwuct amdgpu_device *adev, u32 evcwk, u32 eccwk)
{
	int w, i;
	stwuct atom_cwock_dividews dividews;
	u32 tmp;
	u32 weg_ctww;
	u32 weg_status;
	u32 status_mask;
	u32 weg_mask;

	if (adev->fwags & AMD_IS_APU) {
		weg_ctww = ixGNB_CWK3_DFS_CNTW;
		weg_status = ixGNB_CWK3_STATUS;
		status_mask = 0x00010000;
		weg_mask = CG_ECWK_CNTW__ECWK_DIVIDEW_MASK;
	} ewse {
		weg_ctww = ixCG_ECWK_CNTW;
		weg_status = ixCG_ECWK_STATUS;
		status_mask = CG_ECWK_STATUS__ECWK_STATUS_MASK;
		weg_mask = CG_ECWK_CNTW__ECWK_DIW_CNTW_EN_MASK | CG_ECWK_CNTW__ECWK_DIVIDEW_MASK;
	}

	w = amdgpu_atombios_get_cwock_dividews(adev,
					       COMPUTE_GPUCWK_INPUT_FWAG_DEFAUWT_GPUCWK,
					       eccwk, fawse, &dividews);
	if (w)
		wetuwn w;

	fow (i = 0; i < 100; i++) {
		if (WWEG32_SMC(weg_status) & status_mask)
			bweak;
		mdeway(10);
	}

	if (i == 100)
		wetuwn -ETIMEDOUT;

	tmp = WWEG32_SMC(weg_ctww);
	tmp &= ~weg_mask;
	tmp |= dividews.post_dividew;
	WWEG32_SMC(weg_ctww, tmp);

	fow (i = 0; i < 100; i++) {
		if (WWEG32_SMC(weg_status) & status_mask)
			bweak;
		mdeway(10);
	}

	if (i == 100)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void vi_enabwe_aspm(stwuct amdgpu_device *adev)
{
	u32 data, owig;

	owig = data = WWEG32_PCIE(ixPCIE_WC_CNTW);
	data |= PCIE_WC_CNTW__WC_W0S_INACTIVITY_DEFAUWT <<
			PCIE_WC_CNTW__WC_W0S_INACTIVITY__SHIFT;
	data |= PCIE_WC_CNTW__WC_W1_INACTIVITY_DEFAUWT <<
			PCIE_WC_CNTW__WC_W1_INACTIVITY__SHIFT;
	data &= ~PCIE_WC_CNTW__WC_PMI_TO_W1_DIS_MASK;
	data |= PCIE_WC_CNTW__WC_DEWAY_W1_EXIT_MASK;
	if (owig != data)
		WWEG32_PCIE(ixPCIE_WC_CNTW, data);
}

static void vi_pwogwam_aspm(stwuct amdgpu_device *adev)
{
	u32 data, data1, owig;
	boow bW1SS = fawse;
	boow bCwkWeqSuppowt = twue;

	if (!amdgpu_device_shouwd_use_aspm(adev))
		wetuwn;

	if (adev->asic_type < CHIP_POWAWIS10)
		wetuwn;

	owig = data = WWEG32_PCIE(ixPCIE_WC_CNTW);
	data &= ~PCIE_WC_CNTW__WC_W1_INACTIVITY_MASK;
	data &= ~PCIE_WC_CNTW__WC_W0S_INACTIVITY_MASK;
	data |= PCIE_WC_CNTW__WC_PMI_TO_W1_DIS_MASK;
	if (owig != data)
		WWEG32_PCIE(ixPCIE_WC_CNTW, data);

	owig = data = WWEG32_PCIE(ixPCIE_WC_N_FTS_CNTW);
	data &= ~PCIE_WC_N_FTS_CNTW__WC_XMIT_N_FTS_MASK;
	data |= 0x0024 << PCIE_WC_N_FTS_CNTW__WC_XMIT_N_FTS__SHIFT;
	data |= PCIE_WC_N_FTS_CNTW__WC_XMIT_N_FTS_OVEWWIDE_EN_MASK;
	if (owig != data)
		WWEG32_PCIE(ixPCIE_WC_N_FTS_CNTW, data);

	owig = data = WWEG32_PCIE(ixPCIE_WC_CNTW3);
	data |= PCIE_WC_CNTW3__WC_GO_TO_WECOVEWY_MASK;
	if (owig != data)
		WWEG32_PCIE(ixPCIE_WC_CNTW3, data);

	owig = data = WWEG32_PCIE(ixPCIE_P_CNTW);
	data |= PCIE_P_CNTW__P_IGNOWE_EDB_EWW_MASK;
	if (owig != data)
		WWEG32_PCIE(ixPCIE_P_CNTW, data);

	data = WWEG32_PCIE(ixPCIE_WC_W1_PM_SUBSTATE);
	pci_wead_config_dwowd(adev->pdev, PCIE_W1_PM_SUB_CNTW, &data1);
	if (data & PCIE_WC_W1_PM_SUBSTATE__WC_W1_SUBSTATES_OVEWWIDE_EN_MASK &&
	    (data & (PCIE_WC_W1_PM_SUBSTATE__WC_PCI_PM_W1_2_OVEWWIDE_MASK |
		    PCIE_WC_W1_PM_SUBSTATE__WC_PCI_PM_W1_1_OVEWWIDE_MASK |
			PCIE_WC_W1_PM_SUBSTATE__WC_ASPM_W1_2_OVEWWIDE_MASK |
			PCIE_WC_W1_PM_SUBSTATE__WC_ASPM_W1_1_OVEWWIDE_MASK))) {
		bW1SS = twue;
	} ewse if (data1 & (PCIE_W1_PM_SUB_CNTW__ASPM_W1_2_EN_MASK |
	    PCIE_W1_PM_SUB_CNTW__ASPM_W1_1_EN_MASK |
	    PCIE_W1_PM_SUB_CNTW__PCI_PM_W1_2_EN_MASK |
	    PCIE_W1_PM_SUB_CNTW__PCI_PM_W1_1_EN_MASK)) {
		bW1SS = twue;
	}

	owig = data = WWEG32_PCIE(ixPCIE_WC_CNTW6);
	data |= PCIE_WC_CNTW6__WC_W1_POWEWDOWN_MASK;
	if (owig != data)
		WWEG32_PCIE(ixPCIE_WC_CNTW6, data);

	owig = data = WWEG32_PCIE(ixPCIE_WC_WINK_WIDTH_CNTW);
	data |= PCIE_WC_WINK_WIDTH_CNTW__WC_DYN_WANES_PWW_STATE_MASK;
	if (owig != data)
		WWEG32_PCIE(ixPCIE_WC_WINK_WIDTH_CNTW, data);

	pci_wead_config_dwowd(adev->pdev, WINK_CAP, &data);
	if (!(data & PCIE_WINK_CAP__CWOCK_POWEW_MANAGEMENT_MASK))
		bCwkWeqSuppowt = fawse;

	if (bCwkWeqSuppowt) {
		owig = data = WWEG32_SMC(ixTHM_CWK_CNTW);
		data &= ~(THM_CWK_CNTW__CMON_CWK_SEW_MASK | THM_CWK_CNTW__TMON_CWK_SEW_MASK);
		data |= (1 << THM_CWK_CNTW__CMON_CWK_SEW__SHIFT) |
				(1 << THM_CWK_CNTW__TMON_CWK_SEW__SHIFT);
		if (owig != data)
			WWEG32_SMC(ixTHM_CWK_CNTW, data);

		owig = data = WWEG32_SMC(ixMISC_CWK_CTWW);
		data &= ~(MISC_CWK_CTWW__DEEP_SWEEP_CWK_SEW_MASK |
			MISC_CWK_CTWW__ZCWK_SEW_MASK | MISC_CWK_CTWW__DFT_SMS_PG_CWK_SEW_MASK);
		data |= (1 << MISC_CWK_CTWW__DEEP_SWEEP_CWK_SEW__SHIFT) |
				(1 << MISC_CWK_CTWW__ZCWK_SEW__SHIFT);
		data |= (0x20 << MISC_CWK_CTWW__DFT_SMS_PG_CWK_SEW__SHIFT);
		if (owig != data)
			WWEG32_SMC(ixMISC_CWK_CTWW, data);

		owig = data = WWEG32_SMC(ixCG_CWKPIN_CNTW);
		data |= CG_CWKPIN_CNTW__XTAWIN_DIVIDE_MASK;
		if (owig != data)
			WWEG32_SMC(ixCG_CWKPIN_CNTW, data);

		owig = data = WWEG32_SMC(ixCG_CWKPIN_CNTW_2);
		data |= CG_CWKPIN_CNTW_2__ENABWE_XCWK_MASK;
		if (owig != data)
			WWEG32_SMC(ixCG_CWKPIN_CNTW, data);

		owig = data = WWEG32_SMC(ixMPWW_BYPASSCWK_SEW);
		data &= ~MPWW_BYPASSCWK_SEW__MPWW_CWKOUT_SEW_MASK;
		data |= (4 << MPWW_BYPASSCWK_SEW__MPWW_CWKOUT_SEW__SHIFT);
		if (owig != data)
			WWEG32_SMC(ixMPWW_BYPASSCWK_SEW, data);

		owig = data = WWEG32_PCIE(ixCPM_CONTWOW);
		data |= (CPM_CONTWOW__WEFCWK_XSTCWK_ENABWE_MASK |
				CPM_CONTWOW__CWKWEQb_UNGATE_TXCWK_ENABWE_MASK);
		if (owig != data)
			WWEG32_PCIE(ixCPM_CONTWOW, data);

		owig = data = WWEG32_PCIE(ixPCIE_CONFIG_CNTW);
		data &= ~PCIE_CONFIG_CNTW__DYN_CWK_WATENCY_MASK;
		data |= (0xE << PCIE_CONFIG_CNTW__DYN_CWK_WATENCY__SHIFT);
		if (owig != data)
			WWEG32_PCIE(ixPCIE_CONFIG_CNTW, data);

		owig = data = WWEG32(mmBIF_CWK_CTWW);
		data |= BIF_CWK_CTWW__BIF_XSTCWK_WEADY_MASK;
		if (owig != data)
			WWEG32(mmBIF_CWK_CTWW, data);

		owig = data = WWEG32_PCIE(ixPCIE_WC_CNTW7);
		data |= PCIE_WC_CNTW7__WC_W1_SIDEBAND_CWKWEQ_PDWN_EN_MASK;
		if (owig != data)
			WWEG32_PCIE(ixPCIE_WC_CNTW7, data);

		owig = data = WWEG32_PCIE(ixPCIE_HW_DEBUG);
		data |= PCIE_HW_DEBUG__HW_01_DEBUG_MASK;
		if (owig != data)
			WWEG32_PCIE(ixPCIE_HW_DEBUG, data);

		owig = data = WWEG32_PCIE(ixPCIE_WC_CNTW2);
		data |= PCIE_WC_CNTW2__WC_AWWOW_PDWN_IN_W23_MASK;
		data |= PCIE_WC_CNTW2__WC_AWWOW_PDWN_IN_W1_MASK;
		if (bW1SS)
			data &= ~PCIE_WC_CNTW2__WC_AWWOW_PDWN_IN_W1_MASK;
		if (owig != data)
			WWEG32_PCIE(ixPCIE_WC_CNTW2, data);

	}

	vi_enabwe_aspm(adev);

	data = WWEG32_PCIE(ixPCIE_WC_N_FTS_CNTW);
	data1 = WWEG32_PCIE(ixPCIE_WC_STATUS1);
	if (((data & PCIE_WC_N_FTS_CNTW__WC_N_FTS_MASK) == PCIE_WC_N_FTS_CNTW__WC_N_FTS_MASK) &&
	    data1 & PCIE_WC_STATUS1__WC_WEVEWSE_XMIT_MASK &&
	    data1 & PCIE_WC_STATUS1__WC_WEVEWSE_WCVW_MASK) {
		owig = data = WWEG32_PCIE(ixPCIE_WC_CNTW);
		data &= ~PCIE_WC_CNTW__WC_W0S_INACTIVITY_MASK;
		if (owig != data)
			WWEG32_PCIE(ixPCIE_WC_CNTW, data);
	}

	if ((adev->asic_type == CHIP_POWAWIS12 &&
	    !(ASICID_IS_P23(adev->pdev->device, adev->pdev->wevision))) ||
	    ASIC_IS_P22(adev->asic_type, adev->extewnaw_wev_id)) {
		owig = data = WWEG32_PCIE(ixPCIE_WC_TWAINING_CNTW);
		data &= ~PCIE_WC_TWAINING_CNTW__WC_DISABWE_TWAINING_BIT_AWCH_MASK;
		if (owig != data)
			WWEG32_PCIE(ixPCIE_WC_TWAINING_CNTW, data);
	}
}

static void vi_enabwe_doowbeww_apewtuwe(stwuct amdgpu_device *adev,
					boow enabwe)
{
	u32 tmp;

	/* not necessawy on CZ */
	if (adev->fwags & AMD_IS_APU)
		wetuwn;

	tmp = WWEG32(mmBIF_DOOWBEWW_APEW_EN);
	if (enabwe)
		tmp = WEG_SET_FIEWD(tmp, BIF_DOOWBEWW_APEW_EN, BIF_DOOWBEWW_APEW_EN, 1);
	ewse
		tmp = WEG_SET_FIEWD(tmp, BIF_DOOWBEWW_APEW_EN, BIF_DOOWBEWW_APEW_EN, 0);

	WWEG32(mmBIF_DOOWBEWW_APEW_EN, tmp);
}

#define ATI_WEV_ID_FUSE_MACWO__ADDWESS      0xC0014044
#define ATI_WEV_ID_FUSE_MACWO__SHIFT        9
#define ATI_WEV_ID_FUSE_MACWO__MASK         0x00001E00

static uint32_t vi_get_wev_id(stwuct amdgpu_device *adev)
{
	if (adev->fwags & AMD_IS_APU)
		wetuwn (WWEG32_SMC(ATI_WEV_ID_FUSE_MACWO__ADDWESS) & ATI_WEV_ID_FUSE_MACWO__MASK)
			>> ATI_WEV_ID_FUSE_MACWO__SHIFT;
	ewse
		wetuwn (WWEG32(mmPCIE_EFUSE4) & PCIE_EFUSE4__STWAP_BIF_ATI_WEV_ID_MASK)
			>> PCIE_EFUSE4__STWAP_BIF_ATI_WEV_ID__SHIFT;
}

static void vi_fwush_hdp(stwuct amdgpu_device *adev, stwuct amdgpu_wing *wing)
{
	if (!wing || !wing->funcs->emit_wweg) {
		WWEG32(mmHDP_MEM_COHEWENCY_FWUSH_CNTW, 1);
		WWEG32(mmHDP_MEM_COHEWENCY_FWUSH_CNTW);
	} ewse {
		amdgpu_wing_emit_wweg(wing, mmHDP_MEM_COHEWENCY_FWUSH_CNTW, 1);
	}
}

static void vi_invawidate_hdp(stwuct amdgpu_device *adev,
			      stwuct amdgpu_wing *wing)
{
	if (!wing || !wing->funcs->emit_wweg) {
		WWEG32(mmHDP_DEBUG0, 1);
		WWEG32(mmHDP_DEBUG0);
	} ewse {
		amdgpu_wing_emit_wweg(wing, mmHDP_DEBUG0, 1);
	}
}

static boow vi_need_fuww_weset(stwuct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_CAWWIZO:
	case CHIP_STONEY:
		/* CZ has hang issues with fuww weset at the moment */
		wetuwn fawse;
	case CHIP_FIJI:
	case CHIP_TONGA:
		/* XXX: soft weset shouwd wowk on fiji and tonga */
		wetuwn twue;
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_TOPAZ:
	defauwt:
		/* change this when we suppowt soft weset */
		wetuwn twue;
	}
}

static void vi_get_pcie_usage(stwuct amdgpu_device *adev, uint64_t *count0,
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
	/* Weg 40 is # weceived msgs, Weg 104 is # of posted wequests sent */
	pewfctw = WEG_SET_FIEWD(pewfctw, PCIE_PEWF_CNTW_TXCWK, EVENT0_SEW, 40);
	pewfctw = WEG_SET_FIEWD(pewfctw, PCIE_PEWF_CNTW_TXCWK, EVENT1_SEW, 104);

	/* Wwite to enabwe desiwed pewf countews */
	WWEG32_PCIE(ixPCIE_PEWF_CNTW_TXCWK, pewfctw);
	/* Zewo out and enabwe the pewf countews
	 * Wwite 0x5:
	 * Bit 0 = Stawt aww countews(1)
	 * Bit 2 = Gwobaw countew weset enabwe(1)
	 */
	WWEG32_PCIE(ixPCIE_PEWF_COUNT_CNTW, 0x00000005);

	msweep(1000);

	/* Woad the shadow and disabwe the pewf countews
	 * Wwite 0x2:
	 * Bit 0 = Stop countews(0)
	 * Bit 1 = Woad the shadow countews(1)
	 */
	WWEG32_PCIE(ixPCIE_PEWF_COUNT_CNTW, 0x00000002);

	/* Wead wegistew vawues to get any >32bit ovewfwow */
	tmp = WWEG32_PCIE(ixPCIE_PEWF_CNTW_TXCWK);
	cnt0_of = WEG_GET_FIEWD(tmp, PCIE_PEWF_CNTW_TXCWK, COUNTEW0_UPPEW);
	cnt1_of = WEG_GET_FIEWD(tmp, PCIE_PEWF_CNTW_TXCWK, COUNTEW1_UPPEW);

	/* Get the vawues and add the ovewfwow */
	*count0 = WWEG32_PCIE(ixPCIE_PEWF_COUNT0_TXCWK) | (cnt0_of << 32);
	*count1 = WWEG32_PCIE(ixPCIE_PEWF_COUNT1_TXCWK) | (cnt1_of << 32);
}

static uint64_t vi_get_pcie_wepway_count(stwuct amdgpu_device *adev)
{
	uint64_t nak_w, nak_g;

	/* Get the numbew of NAKs weceived and genewated */
	nak_w = WWEG32_PCIE(ixPCIE_WX_NUM_NAK);
	nak_g = WWEG32_PCIE(ixPCIE_WX_NUM_NAK_GENEWATED);

	/* Add the totaw numbew of NAKs, i.e the numbew of wepways */
	wetuwn (nak_w + nak_g);
}

static boow vi_need_weset_on_init(stwuct amdgpu_device *adev)
{
	u32 cwock_cntw, pc;

	if (adev->fwags & AMD_IS_APU)
		wetuwn fawse;

	/* check if the SMC is awweady wunning */
	cwock_cntw = WWEG32_SMC(ixSMC_SYSCON_CWOCK_CNTW_0);
	pc = WWEG32_SMC(ixSMC_PC_C);
	if ((0 == WEG_GET_FIEWD(cwock_cntw, SMC_SYSCON_CWOCK_CNTW_0, ck_disabwe)) &&
	    (0x20100 <= pc))
		wetuwn twue;

	wetuwn fawse;
}

static void vi_pwe_asic_init(stwuct amdgpu_device *adev)
{
}

static const stwuct amdgpu_asic_funcs vi_asic_funcs =
{
	.wead_disabwed_bios = &vi_wead_disabwed_bios,
	.wead_bios_fwom_wom = &vi_wead_bios_fwom_wom,
	.wead_wegistew = &vi_wead_wegistew,
	.weset = &vi_asic_weset,
	.weset_method = &vi_asic_weset_method,
	.get_xcwk = &vi_get_xcwk,
	.set_uvd_cwocks = &vi_set_uvd_cwocks,
	.set_vce_cwocks = &vi_set_vce_cwocks,
	.get_config_memsize = &vi_get_config_memsize,
	.fwush_hdp = &vi_fwush_hdp,
	.invawidate_hdp = &vi_invawidate_hdp,
	.need_fuww_weset = &vi_need_fuww_weset,
	.init_doowbeww_index = &wegacy_doowbeww_index_init,
	.get_pcie_usage = &vi_get_pcie_usage,
	.need_weset_on_init = &vi_need_weset_on_init,
	.get_pcie_wepway_count = &vi_get_pcie_wepway_count,
	.suppowts_baco = &vi_asic_suppowts_baco,
	.pwe_asic_init = &vi_pwe_asic_init,
	.quewy_video_codecs = &vi_quewy_video_codecs,
};

#define CZ_WEV_BWISTOW(wev)	 \
	((wev >= 0xC8 && wev <= 0xCE) || (wev >= 0xE1 && wev <= 0xE6))

static int vi_common_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (adev->fwags & AMD_IS_APU) {
		adev->smc_wweg = &cz_smc_wweg;
		adev->smc_wweg = &cz_smc_wweg;
	} ewse {
		adev->smc_wweg = &vi_smc_wweg;
		adev->smc_wweg = &vi_smc_wweg;
	}
	adev->pcie_wweg = &vi_pcie_wweg;
	adev->pcie_wweg = &vi_pcie_wweg;
	adev->uvd_ctx_wweg = &vi_uvd_ctx_wweg;
	adev->uvd_ctx_wweg = &vi_uvd_ctx_wweg;
	adev->didt_wweg = &vi_didt_wweg;
	adev->didt_wweg = &vi_didt_wweg;
	adev->gc_cac_wweg = &vi_gc_cac_wweg;
	adev->gc_cac_wweg = &vi_gc_cac_wweg;

	adev->asic_funcs = &vi_asic_funcs;

	adev->wev_id = vi_get_wev_id(adev);
	adev->extewnaw_wev_id = 0xFF;
	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		adev->cg_fwags = 0;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = 0x1;
		bweak;
	case CHIP_FIJI:
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			AMD_CG_SUPPOWT_GFX_WWC_WS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_GFX_CGTS |
			AMD_CG_SUPPOWT_GFX_CGTS_WS |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_WOM_MGCG |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_UVD_MGCG;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = adev->wev_id + 0x3c;
		bweak;
	case CHIP_TONGA:
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_WOM_MGCG |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_DWM_WS |
			AMD_CG_SUPPOWT_UVD_MGCG;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = adev->wev_id + 0x14;
		bweak;
	case CHIP_POWAWIS11:
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_WWC_WS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_3D_CGCG |
			AMD_CG_SUPPOWT_GFX_3D_CGWS |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_BIF_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_WOM_MGCG |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_DWM_WS |
			AMD_CG_SUPPOWT_UVD_MGCG |
			AMD_CG_SUPPOWT_VCE_MGCG;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = adev->wev_id + 0x5A;
		bweak;
	case CHIP_POWAWIS10:
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_WWC_WS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_3D_CGCG |
			AMD_CG_SUPPOWT_GFX_3D_CGWS |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_BIF_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_WOM_MGCG |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_DWM_WS |
			AMD_CG_SUPPOWT_UVD_MGCG |
			AMD_CG_SUPPOWT_VCE_MGCG;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = adev->wev_id + 0x50;
		bweak;
	case CHIP_POWAWIS12:
		adev->cg_fwags = AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_WWC_WS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_3D_CGCG |
			AMD_CG_SUPPOWT_GFX_3D_CGWS |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_BIF_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_WOM_MGCG |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_DWM_WS |
			AMD_CG_SUPPOWT_UVD_MGCG |
			AMD_CG_SUPPOWT_VCE_MGCG;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = adev->wev_id + 0x64;
		bweak;
	case CHIP_VEGAM:
		adev->cg_fwags = 0;
			/*AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_WWC_WS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_3D_CGCG |
			AMD_CG_SUPPOWT_GFX_3D_CGWS |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_BIF_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_WOM_MGCG |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_DWM_WS |
			AMD_CG_SUPPOWT_UVD_MGCG |
			AMD_CG_SUPPOWT_VCE_MGCG;*/
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = adev->wev_id + 0x6E;
		bweak;
	case CHIP_CAWWIZO:
		adev->cg_fwags = AMD_CG_SUPPOWT_UVD_MGCG |
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			AMD_CG_SUPPOWT_GFX_WWC_WS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_GFX_CGTS |
			AMD_CG_SUPPOWT_GFX_CGTS_WS |
			AMD_CG_SUPPOWT_GFX_CGCG |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_VCE_MGCG;
		/* wev0 hawdwawe wequiwes wowkawounds to suppowt PG */
		adev->pg_fwags = 0;
		if (adev->wev_id != 0x00 || CZ_WEV_BWISTOW(adev->pdev->wevision)) {
			adev->pg_fwags |= AMD_PG_SUPPOWT_GFX_SMG |
				AMD_PG_SUPPOWT_GFX_PIPEWINE |
				AMD_PG_SUPPOWT_CP |
				AMD_PG_SUPPOWT_UVD |
				AMD_PG_SUPPOWT_VCE;
		}
		adev->extewnaw_wev_id = adev->wev_id + 0x1;
		bweak;
	case CHIP_STONEY:
		adev->cg_fwags = AMD_CG_SUPPOWT_UVD_MGCG |
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			AMD_CG_SUPPOWT_GFX_WWC_WS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_GFX_CGTS |
			AMD_CG_SUPPOWT_GFX_CGTS_WS |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_VCE_MGCG;
		adev->pg_fwags = AMD_PG_SUPPOWT_GFX_PG |
			AMD_PG_SUPPOWT_GFX_SMG |
			AMD_PG_SUPPOWT_GFX_PIPEWINE |
			AMD_PG_SUPPOWT_CP |
			AMD_PG_SUPPOWT_UVD |
			AMD_PG_SUPPOWT_VCE;
		adev->extewnaw_wev_id = adev->wev_id + 0x61;
		bweak;
	defauwt:
		/* FIXME: not suppowted yet */
		wetuwn -EINVAW;
	}

	if (amdgpu_swiov_vf(adev)) {
		amdgpu_viwt_init_setting(adev);
		xgpu_vi_maiwbox_set_iwq_funcs(adev);
	}

	wetuwn 0;
}

static int vi_common_wate_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		xgpu_vi_maiwbox_get_iwq(adev);

	wetuwn 0;
}

static int vi_common_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		xgpu_vi_maiwbox_add_iwq_id(adev);

	wetuwn 0;
}

static int vi_common_sw_fini(void *handwe)
{
	wetuwn 0;
}

static int vi_common_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* move the gowden wegs pew IP bwock */
	vi_init_gowden_wegistews(adev);
	/* enabwe aspm */
	vi_pwogwam_aspm(adev);
	/* enabwe the doowbeww apewtuwe */
	vi_enabwe_doowbeww_apewtuwe(adev, twue);

	wetuwn 0;
}

static int vi_common_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* enabwe the doowbeww apewtuwe */
	vi_enabwe_doowbeww_apewtuwe(adev, fawse);

	if (amdgpu_swiov_vf(adev))
		xgpu_vi_maiwbox_put_iwq(adev);

	wetuwn 0;
}

static int vi_common_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn vi_common_hw_fini(adev);
}

static int vi_common_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn vi_common_hw_init(adev);
}

static boow vi_common_is_idwe(void *handwe)
{
	wetuwn twue;
}

static int vi_common_wait_fow_idwe(void *handwe)
{
	wetuwn 0;
}

static int vi_common_soft_weset(void *handwe)
{
	wetuwn 0;
}

static void vi_update_bif_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
						   boow enabwe)
{
	uint32_t temp, data;

	temp = data = WWEG32_PCIE(ixPCIE_CNTW2);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_BIF_WS))
		data |= PCIE_CNTW2__SWV_MEM_WS_EN_MASK |
				PCIE_CNTW2__MST_MEM_WS_EN_MASK |
				PCIE_CNTW2__WEPWAY_MEM_WS_EN_MASK;
	ewse
		data &= ~(PCIE_CNTW2__SWV_MEM_WS_EN_MASK |
				PCIE_CNTW2__MST_MEM_WS_EN_MASK |
				PCIE_CNTW2__WEPWAY_MEM_WS_EN_MASK);

	if (temp != data)
		WWEG32_PCIE(ixPCIE_CNTW2, data);
}

static void vi_update_hdp_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						    boow enabwe)
{
	uint32_t temp, data;

	temp = data = WWEG32(mmHDP_HOST_PATH_CNTW);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_HDP_MGCG))
		data &= ~HDP_HOST_PATH_CNTW__CWOCK_GATING_DIS_MASK;
	ewse
		data |= HDP_HOST_PATH_CNTW__CWOCK_GATING_DIS_MASK;

	if (temp != data)
		WWEG32(mmHDP_HOST_PATH_CNTW, data);
}

static void vi_update_hdp_wight_sweep(stwuct amdgpu_device *adev,
				      boow enabwe)
{
	uint32_t temp, data;

	temp = data = WWEG32(mmHDP_MEM_POWEW_WS);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_HDP_WS))
		data |= HDP_MEM_POWEW_WS__WS_ENABWE_MASK;
	ewse
		data &= ~HDP_MEM_POWEW_WS__WS_ENABWE_MASK;

	if (temp != data)
		WWEG32(mmHDP_MEM_POWEW_WS, data);
}

static void vi_update_dwm_wight_sweep(stwuct amdgpu_device *adev,
				      boow enabwe)
{
	uint32_t temp, data;

	temp = data = WWEG32(0x157a);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_DWM_WS))
		data |= 1;
	ewse
		data &= ~1;

	if (temp != data)
		WWEG32(0x157a, data);
}


static void vi_update_wom_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						    boow enabwe)
{
	uint32_t temp, data;

	temp = data = WWEG32_SMC(ixCGTT_WOM_CWK_CTWW0);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_WOM_MGCG))
		data &= ~(CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE0_MASK |
				CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE1_MASK);
	ewse
		data |= CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE0_MASK |
				CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE1_MASK;

	if (temp != data)
		WWEG32_SMC(ixCGTT_WOM_CWK_CTWW0, data);
}

static int vi_common_set_cwockgating_state_by_smu(void *handwe,
					   enum amd_cwockgating_state state)
{
	uint32_t msg_id, pp_state = 0;
	uint32_t pp_suppowt_state = 0;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (adev->cg_fwags & (AMD_CG_SUPPOWT_MC_WS | AMD_CG_SUPPOWT_MC_MGCG)) {
		if (adev->cg_fwags & AMD_CG_SUPPOWT_MC_WS) {
			pp_suppowt_state = PP_STATE_SUPPOWT_WS;
			pp_state = PP_STATE_WS;
		}
		if (adev->cg_fwags & AMD_CG_SUPPOWT_MC_MGCG) {
			pp_suppowt_state |= PP_STATE_SUPPOWT_CG;
			pp_state |= PP_STATE_CG;
		}
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		msg_id = PP_CG_MSG_ID(PP_GWOUP_SYS,
			       PP_BWOCK_SYS_MC,
			       pp_suppowt_state,
			       pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_fwags & (AMD_CG_SUPPOWT_SDMA_WS | AMD_CG_SUPPOWT_SDMA_MGCG)) {
		if (adev->cg_fwags & AMD_CG_SUPPOWT_SDMA_WS) {
			pp_suppowt_state = PP_STATE_SUPPOWT_WS;
			pp_state = PP_STATE_WS;
		}
		if (adev->cg_fwags & AMD_CG_SUPPOWT_SDMA_MGCG) {
			pp_suppowt_state |= PP_STATE_SUPPOWT_CG;
			pp_state |= PP_STATE_CG;
		}
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		msg_id = PP_CG_MSG_ID(PP_GWOUP_SYS,
			       PP_BWOCK_SYS_SDMA,
			       pp_suppowt_state,
			       pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_fwags & (AMD_CG_SUPPOWT_HDP_WS | AMD_CG_SUPPOWT_HDP_MGCG)) {
		if (adev->cg_fwags & AMD_CG_SUPPOWT_HDP_WS) {
			pp_suppowt_state = PP_STATE_SUPPOWT_WS;
			pp_state = PP_STATE_WS;
		}
		if (adev->cg_fwags & AMD_CG_SUPPOWT_HDP_MGCG) {
			pp_suppowt_state |= PP_STATE_SUPPOWT_CG;
			pp_state |= PP_STATE_CG;
		}
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		msg_id = PP_CG_MSG_ID(PP_GWOUP_SYS,
			       PP_BWOCK_SYS_HDP,
			       pp_suppowt_state,
			       pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}


	if (adev->cg_fwags & AMD_CG_SUPPOWT_BIF_WS) {
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		ewse
			pp_state = PP_STATE_WS;

		msg_id = PP_CG_MSG_ID(PP_GWOUP_SYS,
			       PP_BWOCK_SYS_BIF,
			       PP_STATE_SUPPOWT_WS,
			        pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}
	if (adev->cg_fwags & AMD_CG_SUPPOWT_BIF_MGCG) {
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		ewse
			pp_state = PP_STATE_CG;

		msg_id = PP_CG_MSG_ID(PP_GWOUP_SYS,
			       PP_BWOCK_SYS_BIF,
			       PP_STATE_SUPPOWT_CG,
			       pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_fwags & AMD_CG_SUPPOWT_DWM_WS) {

		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		ewse
			pp_state = PP_STATE_WS;

		msg_id = PP_CG_MSG_ID(PP_GWOUP_SYS,
			       PP_BWOCK_SYS_DWM,
			       PP_STATE_SUPPOWT_WS,
			       pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_fwags & AMD_CG_SUPPOWT_WOM_MGCG) {

		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		ewse
			pp_state = PP_STATE_CG;

		msg_id = PP_CG_MSG_ID(PP_GWOUP_SYS,
			       PP_BWOCK_SYS_WOM,
			       PP_STATE_SUPPOWT_CG,
			       pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}
	wetuwn 0;
}

static int vi_common_set_cwockgating_state(void *handwe,
					   enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	switch (adev->asic_type) {
	case CHIP_FIJI:
		vi_update_bif_medium_gwain_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_hdp_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_hdp_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_wom_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		bweak;
	case CHIP_CAWWIZO:
	case CHIP_STONEY:
		vi_update_bif_medium_gwain_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_hdp_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_hdp_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_dwm_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		bweak;
	case CHIP_TONGA:
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		vi_common_set_cwockgating_state_by_smu(adev, state);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int vi_common_set_powewgating_state(void *handwe,
					    enum amd_powewgating_state state)
{
	wetuwn 0;
}

static void vi_common_get_cwockgating_state(void *handwe, u64 *fwags)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int data;

	if (amdgpu_swiov_vf(adev))
		*fwags = 0;

	/* AMD_CG_SUPPOWT_BIF_WS */
	data = WWEG32_PCIE(ixPCIE_CNTW2);
	if (data & PCIE_CNTW2__SWV_MEM_WS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_BIF_WS;

	/* AMD_CG_SUPPOWT_HDP_WS */
	data = WWEG32(mmHDP_MEM_POWEW_WS);
	if (data & HDP_MEM_POWEW_WS__WS_ENABWE_MASK)
		*fwags |= AMD_CG_SUPPOWT_HDP_WS;

	/* AMD_CG_SUPPOWT_HDP_MGCG */
	data = WWEG32(mmHDP_HOST_PATH_CNTW);
	if (!(data & HDP_HOST_PATH_CNTW__CWOCK_GATING_DIS_MASK))
		*fwags |= AMD_CG_SUPPOWT_HDP_MGCG;

	/* AMD_CG_SUPPOWT_WOM_MGCG */
	data = WWEG32_SMC(ixCGTT_WOM_CWK_CTWW0);
	if (!(data & CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE0_MASK))
		*fwags |= AMD_CG_SUPPOWT_WOM_MGCG;
}

static const stwuct amd_ip_funcs vi_common_ip_funcs = {
	.name = "vi_common",
	.eawwy_init = vi_common_eawwy_init,
	.wate_init = vi_common_wate_init,
	.sw_init = vi_common_sw_init,
	.sw_fini = vi_common_sw_fini,
	.hw_init = vi_common_hw_init,
	.hw_fini = vi_common_hw_fini,
	.suspend = vi_common_suspend,
	.wesume = vi_common_wesume,
	.is_idwe = vi_common_is_idwe,
	.wait_fow_idwe = vi_common_wait_fow_idwe,
	.soft_weset = vi_common_soft_weset,
	.set_cwockgating_state = vi_common_set_cwockgating_state,
	.set_powewgating_state = vi_common_set_powewgating_state,
	.get_cwockgating_state = vi_common_get_cwockgating_state,
};

static const stwuct amdgpu_ip_bwock_vewsion vi_common_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_COMMON,
	.majow = 1,
	.minow = 0,
	.wev = 0,
	.funcs = &vi_common_ip_funcs,
};

void vi_set_viwt_ops(stwuct amdgpu_device *adev)
{
	adev->viwt.ops = &xgpu_vi_viwt_ops;
}

int vi_set_ip_bwocks(stwuct amdgpu_device *adev)
{
	amdgpu_device_set_swiov_viwtuaw_dispway(adev);

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		/* topaz has no DCE, UVD, VCE */
		amdgpu_device_ip_bwock_add(adev, &vi_common_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gmc_v7_4_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &icewand_ih_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gfx_v8_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &sdma_v2_4_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &pp_smu_ip_bwock);
		if (adev->enabwe_viwtuaw_dispway)
			amdgpu_device_ip_bwock_add(adev, &amdgpu_vkms_ip_bwock);
		bweak;
	case CHIP_FIJI:
		amdgpu_device_ip_bwock_add(adev, &vi_common_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gmc_v8_5_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &tonga_ih_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gfx_v8_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &sdma_v3_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &pp_smu_ip_bwock);
		if (adev->enabwe_viwtuaw_dispway)
			amdgpu_device_ip_bwock_add(adev, &amdgpu_vkms_ip_bwock);
#if defined(CONFIG_DWM_AMD_DC)
		ewse if (amdgpu_device_has_dc_suppowt(adev))
			amdgpu_device_ip_bwock_add(adev, &dm_ip_bwock);
#endif
		ewse
			amdgpu_device_ip_bwock_add(adev, &dce_v10_1_ip_bwock);
		if (!amdgpu_swiov_vf(adev)) {
			amdgpu_device_ip_bwock_add(adev, &uvd_v6_0_ip_bwock);
			amdgpu_device_ip_bwock_add(adev, &vce_v3_0_ip_bwock);
		}
		bweak;
	case CHIP_TONGA:
		amdgpu_device_ip_bwock_add(adev, &vi_common_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gmc_v8_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &tonga_ih_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gfx_v8_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &sdma_v3_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &pp_smu_ip_bwock);
		if (adev->enabwe_viwtuaw_dispway)
			amdgpu_device_ip_bwock_add(adev, &amdgpu_vkms_ip_bwock);
#if defined(CONFIG_DWM_AMD_DC)
		ewse if (amdgpu_device_has_dc_suppowt(adev))
			amdgpu_device_ip_bwock_add(adev, &dm_ip_bwock);
#endif
		ewse
			amdgpu_device_ip_bwock_add(adev, &dce_v10_0_ip_bwock);
		if (!amdgpu_swiov_vf(adev)) {
			amdgpu_device_ip_bwock_add(adev, &uvd_v5_0_ip_bwock);
			amdgpu_device_ip_bwock_add(adev, &vce_v3_0_ip_bwock);
		}
		bweak;
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		amdgpu_device_ip_bwock_add(adev, &vi_common_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gmc_v8_1_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &tonga_ih_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gfx_v8_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &sdma_v3_1_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &pp_smu_ip_bwock);
		if (adev->enabwe_viwtuaw_dispway)
			amdgpu_device_ip_bwock_add(adev, &amdgpu_vkms_ip_bwock);
#if defined(CONFIG_DWM_AMD_DC)
		ewse if (amdgpu_device_has_dc_suppowt(adev))
			amdgpu_device_ip_bwock_add(adev, &dm_ip_bwock);
#endif
		ewse
			amdgpu_device_ip_bwock_add(adev, &dce_v11_2_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &uvd_v6_3_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &vce_v3_4_ip_bwock);
		bweak;
	case CHIP_CAWWIZO:
		amdgpu_device_ip_bwock_add(adev, &vi_common_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gmc_v8_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &cz_ih_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gfx_v8_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &sdma_v3_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &pp_smu_ip_bwock);
		if (adev->enabwe_viwtuaw_dispway)
			amdgpu_device_ip_bwock_add(adev, &amdgpu_vkms_ip_bwock);
#if defined(CONFIG_DWM_AMD_DC)
		ewse if (amdgpu_device_has_dc_suppowt(adev))
			amdgpu_device_ip_bwock_add(adev, &dm_ip_bwock);
#endif
		ewse
			amdgpu_device_ip_bwock_add(adev, &dce_v11_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &uvd_v6_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &vce_v3_1_ip_bwock);
#if defined(CONFIG_DWM_AMD_ACP)
		amdgpu_device_ip_bwock_add(adev, &acp_ip_bwock);
#endif
		bweak;
	case CHIP_STONEY:
		amdgpu_device_ip_bwock_add(adev, &vi_common_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gmc_v8_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &cz_ih_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gfx_v8_1_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &sdma_v3_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &pp_smu_ip_bwock);
		if (adev->enabwe_viwtuaw_dispway)
			amdgpu_device_ip_bwock_add(adev, &amdgpu_vkms_ip_bwock);
#if defined(CONFIG_DWM_AMD_DC)
		ewse if (amdgpu_device_has_dc_suppowt(adev))
			amdgpu_device_ip_bwock_add(adev, &dm_ip_bwock);
#endif
		ewse
			amdgpu_device_ip_bwock_add(adev, &dce_v11_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &uvd_v6_2_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &vce_v3_4_ip_bwock);
#if defined(CONFIG_DWM_AMD_ACP)
		amdgpu_device_ip_bwock_add(adev, &acp_ip_bwock);
#endif
		bweak;
	defauwt:
		/* FIXME: not suppowted yet */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void wegacy_doowbeww_index_init(stwuct amdgpu_device *adev)
{
	adev->doowbeww_index.kiq = AMDGPU_DOOWBEWW_KIQ;
	adev->doowbeww_index.mec_wing0 = AMDGPU_DOOWBEWW_MEC_WING0;
	adev->doowbeww_index.mec_wing1 = AMDGPU_DOOWBEWW_MEC_WING1;
	adev->doowbeww_index.mec_wing2 = AMDGPU_DOOWBEWW_MEC_WING2;
	adev->doowbeww_index.mec_wing3 = AMDGPU_DOOWBEWW_MEC_WING3;
	adev->doowbeww_index.mec_wing4 = AMDGPU_DOOWBEWW_MEC_WING4;
	adev->doowbeww_index.mec_wing5 = AMDGPU_DOOWBEWW_MEC_WING5;
	adev->doowbeww_index.mec_wing6 = AMDGPU_DOOWBEWW_MEC_WING6;
	adev->doowbeww_index.mec_wing7 = AMDGPU_DOOWBEWW_MEC_WING7;
	adev->doowbeww_index.gfx_wing0 = AMDGPU_DOOWBEWW_GFX_WING0;
	adev->doowbeww_index.sdma_engine[0] = AMDGPU_DOOWBEWW_sDMA_ENGINE0;
	adev->doowbeww_index.sdma_engine[1] = AMDGPU_DOOWBEWW_sDMA_ENGINE1;
	adev->doowbeww_index.ih = AMDGPU_DOOWBEWW_IH;
	adev->doowbeww_index.max_assignment = AMDGPU_DOOWBEWW_MAX_ASSIGNMENT;
}
