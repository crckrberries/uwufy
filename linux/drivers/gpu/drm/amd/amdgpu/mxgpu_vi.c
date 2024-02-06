/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
 * Authows: Xiangwiang.Yu@amd.com
 */

#incwude "amdgpu.h"
#incwude "vi.h"
#incwude "bif/bif_5_0_d.h"
#incwude "bif/bif_5_0_sh_mask.h"
#incwude "vid.h"
#incwude "gca/gfx_8_0_d.h"
#incwude "gca/gfx_8_0_sh_mask.h"
#incwude "gmc_v8_0.h"
#incwude "gfx_v8_0.h"
#incwude "sdma_v3_0.h"
#incwude "tonga_ih.h"
#incwude "gmc/gmc_8_2_d.h"
#incwude "gmc/gmc_8_2_sh_mask.h"
#incwude "oss/oss_3_0_d.h"
#incwude "oss/oss_3_0_sh_mask.h"
#incwude "dce/dce_10_0_d.h"
#incwude "dce/dce_10_0_sh_mask.h"
#incwude "smu/smu_7_1_3_d.h"
#incwude "mxgpu_vi.h"

#incwude "amdgpu_weset.h"

/* VI gowden setting */
static const u32 xgpu_fiji_mgcg_cgcg_init[] = {
	mmWWC_CGTT_MGCG_OVEWWIDE, 0xffffffff, 0xffffffff,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CPC_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CPF_CWK_CTWW, 0xffffffff, 0x40000100,
	mmCGTT_DWM_CWK_CTWW0, 0xffffffff, 0x00600100,
	mmCGTT_GDS_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_IA_CWK_CTWW, 0xffffffff, 0x06000100,
	mmCGTT_PA_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_WD_CWK_CTWW, 0xffffffff, 0x06000100,
	mmCGTT_PC_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_WWC_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_SC_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_SPI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_SQ_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_SQG_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_SX_CWK_CTWW0, 0xffffffff, 0x00000100,
	mmCGTT_SX_CWK_CTWW1, 0xffffffff, 0x00000100,
	mmCGTT_SX_CWK_CTWW2, 0xffffffff, 0x00000100,
	mmCGTT_SX_CWK_CTWW3, 0xffffffff, 0x00000100,
	mmCGTT_SX_CWK_CTWW4, 0xffffffff, 0x00000100,
	mmCGTT_TCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CWK_CTWW, 0xffffffff, 0x06000100,
	mmDB_CGTT_CWK_CTWW_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCGTS_SM_CTWW_WEG, 0xffffffff, 0x96e00200,
	mmCP_WB_WPTW_POWW_CNTW, 0xffffffff, 0x00900100,
	mmWWC_CGCG_CGWS_CTWW, 0xffffffff, 0x0020003c,
	mmPCIE_INDEX, 0xffffffff, 0x0140001c,
	mmPCIE_DATA, 0x000f0000, 0x00000000,
	mmSMC_IND_INDEX_4, 0xffffffff, 0xC060000C,
	mmSMC_IND_DATA_4, 0xc0000fff, 0x00000100,
	mmXDMA_CWOCK_GATING_CNTW, 0xffffffff, 0x00000100,
	mmXDMA_MEM_POWEW_CNTW, 0x00000101, 0x00000000,
	mmMC_MEM_POWEW_WS, 0xffffffff, 0x00000104,
	mmCGTT_DWM_CWK_CTWW0, 0xff000fff, 0x00000100,
	mmHDP_XDP_CGTT_BWK_CTWW, 0xc0000fff, 0x00000104,
	mmCP_MEM_SWP_CNTW, 0x00000001, 0x00000001,
	mmSDMA0_CWK_CTWW, 0xff000ff0, 0x00000100,
	mmSDMA1_CWK_CTWW, 0xff000ff0, 0x00000100,
};

static const u32 xgpu_fiji_gowden_settings_a10[] = {
	mmCB_HW_CONTWOW_3, 0x000001ff, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDCI_CWK_CNTW, 0x00000080, 0x00000000,
	mmFBC_DEBUG_COMP, 0x000000f0, 0x00000070,
	mmFBC_MISC, 0x1f311fff, 0x12300000,
	mmHDMI_CONTWOW, 0x31000111, 0x00000011,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmSDMA0_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA0_GFX_IB_CNTW, 0x800f0111, 0x00000100,
	mmSDMA0_WWC0_IB_CNTW, 0x800f0111, 0x00000100,
	mmSDMA0_WWC1_IB_CNTW, 0x800f0111, 0x00000100,
	mmSDMA1_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA1_GFX_IB_CNTW, 0x800f0111, 0x00000100,
	mmSDMA1_WWC0_IB_CNTW, 0x800f0111, 0x00000100,
	mmSDMA1_WWC1_IB_CNTW, 0x800f0111, 0x00000100,
	mmSQ_WANDOM_WAVE_PWI, 0x001fffff, 0x000006fd,
	mmTA_CNTW_AUX, 0x000f000f, 0x000b0000,
	mmTCC_EXE_DISABWE, 0x00000002, 0x00000002,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x000000ff,
	mmVGT_WESET_DEBUG, 0x00000004, 0x00000004,
	mmVM_PWT_APEWTUWE0_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE1_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE2_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE3_WOW_ADDW, 0x0fffffff, 0x0fffffff,
};

static const u32 xgpu_fiji_gowden_common_aww[] = {
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_WASTEW_CONFIG, 0xffffffff, 0x3a00161a,
	mmPA_SC_WASTEW_CONFIG_1, 0xffffffff, 0x0000002e,
	mmGB_ADDW_CONFIG, 0xffffffff, 0x22011003,
	mmSPI_WESOUWCE_WESEWVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_0, 0xffffffff, 0x00007FBF,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_1, 0xffffffff, 0x00007FAF,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmSPI_CONFIG_CNTW_1, 0x0000000f, 0x00000009,
};

static const u32 xgpu_tonga_mgcg_cgcg_init[] = {
	mmWWC_CGTT_MGCG_OVEWWIDE,   0xffffffff, 0xffffffff,
	mmGWBM_GFX_INDEX,           0xffffffff, 0xe0000000,
	mmCB_CGTT_SCWK_CTWW,        0xffffffff, 0x00000100,
	mmCGTT_BCI_CWK_CTWW,        0xffffffff, 0x00000100,
	mmCGTT_CP_CWK_CTWW,         0xffffffff, 0x00000100,
	mmCGTT_CPC_CWK_CTWW,        0xffffffff, 0x00000100,
	mmCGTT_CPF_CWK_CTWW,        0xffffffff, 0x40000100,
	mmCGTT_DWM_CWK_CTWW0,       0xffffffff, 0x00600100,
	mmCGTT_GDS_CWK_CTWW,        0xffffffff, 0x00000100,
	mmCGTT_IA_CWK_CTWW,         0xffffffff, 0x06000100,
	mmCGTT_PA_CWK_CTWW,         0xffffffff, 0x00000100,
	mmCGTT_WD_CWK_CTWW,         0xffffffff, 0x06000100,
	mmCGTT_PC_CWK_CTWW,         0xffffffff, 0x00000100,
	mmCGTT_WWC_CWK_CTWW,        0xffffffff, 0x00000100,
	mmCGTT_SC_CWK_CTWW,         0xffffffff, 0x00000100,
	mmCGTT_SPI_CWK_CTWW,        0xffffffff, 0x00000100,
	mmCGTT_SQ_CWK_CTWW,         0xffffffff, 0x00000100,
	mmCGTT_SQG_CWK_CTWW,        0xffffffff, 0x00000100,
	mmCGTT_SX_CWK_CTWW0,        0xffffffff, 0x00000100,
	mmCGTT_SX_CWK_CTWW1,        0xffffffff, 0x00000100,
	mmCGTT_SX_CWK_CTWW2,        0xffffffff, 0x00000100,
	mmCGTT_SX_CWK_CTWW3,        0xffffffff, 0x00000100,
	mmCGTT_SX_CWK_CTWW4,        0xffffffff, 0x00000100,
	mmCGTT_TCI_CWK_CTWW,        0xffffffff, 0x00000100,
	mmCGTT_TCP_CWK_CTWW,        0xffffffff, 0x00000100,
	mmCGTT_VGT_CWK_CTWW,        0xffffffff, 0x06000100,
	mmDB_CGTT_CWK_CTWW_0,       0xffffffff, 0x00000100,
	mmTA_CGTT_CTWW,             0xffffffff, 0x00000100,
	mmTCA_CGTT_SCWK_CTWW,       0xffffffff, 0x00000100,
	mmTCC_CGTT_SCWK_CTWW,       0xffffffff, 0x00000100,
	mmTD_CGTT_CTWW,             0xffffffff, 0x00000100,
	mmGWBM_GFX_INDEX,           0xffffffff, 0xe0000000,
	mmCGTS_CU0_SP0_CTWW_WEG,    0xffffffff, 0x00010000,
	mmCGTS_CU0_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU0_TA_SQC_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU0_SP1_CTWW_WEG,    0xffffffff, 0x00060005,
	mmCGTS_CU0_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU1_SP0_CTWW_WEG,    0xffffffff, 0x00010000,
	mmCGTS_CU1_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU1_TA_CTWW_WEG,     0xffffffff, 0x00040007,
	mmCGTS_CU1_SP1_CTWW_WEG,    0xffffffff, 0x00060005,
	mmCGTS_CU1_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU2_SP0_CTWW_WEG,    0xffffffff, 0x00010000,
	mmCGTS_CU2_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU2_TA_CTWW_WEG,     0xffffffff, 0x00040007,
	mmCGTS_CU2_SP1_CTWW_WEG,    0xffffffff, 0x00060005,
	mmCGTS_CU2_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU3_SP0_CTWW_WEG,    0xffffffff, 0x00010000,
	mmCGTS_CU3_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU3_TA_CTWW_WEG,     0xffffffff, 0x00040007,
	mmCGTS_CU3_SP1_CTWW_WEG,    0xffffffff, 0x00060005,
	mmCGTS_CU3_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU4_SP0_CTWW_WEG,    0xffffffff, 0x00010000,
	mmCGTS_CU4_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU4_TA_SQC_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU4_SP1_CTWW_WEG,    0xffffffff, 0x00060005,
	mmCGTS_CU4_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU5_SP0_CTWW_WEG,    0xffffffff, 0x00010000,
	mmCGTS_CU5_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU5_TA_CTWW_WEG,     0xffffffff, 0x00040007,
	mmCGTS_CU5_SP1_CTWW_WEG,    0xffffffff, 0x00060005,
	mmCGTS_CU5_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU6_SP0_CTWW_WEG,    0xffffffff, 0x00010000,
	mmCGTS_CU6_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU6_TA_CTWW_WEG,     0xffffffff, 0x00040007,
	mmCGTS_CU6_SP1_CTWW_WEG,    0xffffffff, 0x00060005,
	mmCGTS_CU6_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU7_SP0_CTWW_WEG,    0xffffffff, 0x00010000,
	mmCGTS_CU7_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU7_TA_CTWW_WEG,     0xffffffff, 0x00040007,
	mmCGTS_CU7_SP1_CTWW_WEG,    0xffffffff, 0x00060005,
	mmCGTS_CU7_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_SM_CTWW_WEG,         0xffffffff, 0x96e00200,
	mmCP_WB_WPTW_POWW_CNTW,     0xffffffff, 0x00900100,
	mmWWC_CGCG_CGWS_CTWW,       0xffffffff, 0x0020003c,
	mmPCIE_INDEX,               0xffffffff, 0x0140001c,
	mmPCIE_DATA,                0x000f0000, 0x00000000,
	mmSMC_IND_INDEX_4,          0xffffffff, 0xC060000C,
	mmSMC_IND_DATA_4,           0xc0000fff, 0x00000100,
	mmXDMA_CWOCK_GATING_CNTW,   0xffffffff, 0x00000100,
	mmXDMA_MEM_POWEW_CNTW,      0x00000101, 0x00000000,
	mmMC_MEM_POWEW_WS,          0xffffffff, 0x00000104,
	mmCGTT_DWM_CWK_CTWW0,       0xff000fff, 0x00000100,
	mmHDP_XDP_CGTT_BWK_CTWW,    0xc0000fff, 0x00000104,
	mmCP_MEM_SWP_CNTW,          0x00000001, 0x00000001,
	mmSDMA0_CWK_CTWW,           0xff000ff0, 0x00000100,
	mmSDMA1_CWK_CTWW,           0xff000ff0, 0x00000100,
};

static const u32 xgpu_tonga_gowden_settings_a11[] = {
	mmCB_HW_CONTWOW, 0xfffdf3cf, 0x00007208,
	mmCB_HW_CONTWOW_3, 0x00000040, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDCI_CWK_CNTW, 0x00000080, 0x00000000,
	mmFBC_DEBUG_COMP, 0x000000f0, 0x00000070,
	mmFBC_MISC, 0x1f311fff, 0x12300000,
	mmGB_GPU_ID, 0x0000000f, 0x00000000,
	mmHDMI_CONTWOW, 0x31000111, 0x00000011,
	mmMC_AWB_WTM_GWPWT_WD, 0x00000003, 0x00000000,
	mmMC_HUB_WDWEQ_DMIF_WIMIT, 0x0000007f, 0x00000028,
	mmMC_HUB_WDP_UMC, 0x00007fb6, 0x00000991,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_FIFO_DEPTH_CNTW, 0x000003ff, 0x000000fc,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmWWC_CGCG_CGWS_CTWW, 0x00000003, 0x0000003c,
	mmSDMA0_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA0_CWK_CTWW, 0xff000fff, 0x00000000,
	mmSDMA0_GFX_IB_CNTW, 0x800f0111, 0x00000100,
	mmSDMA0_WWC0_IB_CNTW, 0x800f0111, 0x00000100,
	mmSDMA0_WWC1_IB_CNTW, 0x800f0111, 0x00000100,
	mmSDMA1_CHICKEN_BITS, 0xfc910007, 0x00810007,
	mmSDMA1_CWK_CTWW, 0xff000fff, 0x00000000,
	mmSDMA1_GFX_IB_CNTW, 0x800f0111, 0x00000100,
	mmSDMA1_WWC0_IB_CNTW, 0x800f0111, 0x00000100,
	mmSDMA1_WWC1_IB_CNTW, 0x800f0111, 0x00000100,
	mmSQ_WANDOM_WAVE_PWI, 0x001fffff, 0x000006fd,
	mmTA_CNTW_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTWW, 0x00100000, 0xf31fff7f,
	mmTCC_EXE_DISABWE, 0x00000002, 0x00000002,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x000002fb,
	mmTCP_CHAN_STEEW_HI, 0xffffffff, 0x0000543b,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0xa9210876,
	mmVGT_WESET_DEBUG, 0x00000004, 0x00000004,
	mmVM_PWT_APEWTUWE0_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE1_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE2_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE3_WOW_ADDW, 0x0fffffff, 0x0fffffff,
};

static const u32 xgpu_tonga_gowden_common_aww[] = {
	mmGWBM_GFX_INDEX,               0xffffffff, 0xe0000000,
	mmPA_SC_WASTEW_CONFIG,          0xffffffff, 0x16000012,
	mmPA_SC_WASTEW_CONFIG_1,        0xffffffff, 0x0000002A,
	mmGB_ADDW_CONFIG,               0xffffffff, 0x22011002,
	mmSPI_WESOUWCE_WESEWVE_CU_0,    0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_CU_1,    0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_0, 0xffffffff, 0x00007FBF,
};

void xgpu_vi_init_gowden_wegistews(stwuct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_FIJI:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							xgpu_fiji_mgcg_cgcg_init,
							AWWAY_SIZE(
								xgpu_fiji_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							xgpu_fiji_gowden_settings_a10,
							AWWAY_SIZE(
								xgpu_fiji_gowden_settings_a10));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							xgpu_fiji_gowden_common_aww,
							AWWAY_SIZE(
								xgpu_fiji_gowden_common_aww));
		bweak;
	case CHIP_TONGA:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							xgpu_tonga_mgcg_cgcg_init,
							AWWAY_SIZE(
								xgpu_tonga_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							xgpu_tonga_gowden_settings_a11,
							AWWAY_SIZE(
								xgpu_tonga_gowden_settings_a11));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							xgpu_tonga_gowden_common_aww,
							AWWAY_SIZE(
								xgpu_tonga_gowden_common_aww));
		bweak;
	defauwt:
		BUG_ON("Doesn't suppowt chip type.\n");
		bweak;
	}
}

/*
 * Maiwbox communication between GPU hypewvisow and VFs
 */
static void xgpu_vi_maiwbox_send_ack(stwuct amdgpu_device *adev)
{
	u32 weg;
	int timeout = VI_MAIWBOX_TIMEDOUT;
	u32 mask = WEG_FIEWD_MASK(MAIWBOX_CONTWOW, WCV_MSG_VAWID);

	weg = WWEG32_NO_KIQ(mmMAIWBOX_CONTWOW);
	weg = WEG_SET_FIEWD(weg, MAIWBOX_CONTWOW, WCV_MSG_ACK, 1);
	WWEG32_NO_KIQ(mmMAIWBOX_CONTWOW, weg);

	/*Wait fow WCV_MSG_VAWID to be 0*/
	weg = WWEG32_NO_KIQ(mmMAIWBOX_CONTWOW);
	whiwe (weg & mask) {
		if (timeout <= 0) {
			pw_eww("WCV_MSG_VAWID is not cweawed\n");
			bweak;
		}
		mdeway(1);
		timeout -= 1;

		weg = WWEG32_NO_KIQ(mmMAIWBOX_CONTWOW);
	}
}

static void xgpu_vi_maiwbox_set_vawid(stwuct amdgpu_device *adev, boow vaw)
{
	u32 weg;

	weg = WWEG32_NO_KIQ(mmMAIWBOX_CONTWOW);
	weg = WEG_SET_FIEWD(weg, MAIWBOX_CONTWOW,
			    TWN_MSG_VAWID, vaw ? 1 : 0);
	WWEG32_NO_KIQ(mmMAIWBOX_CONTWOW, weg);
}

static void xgpu_vi_maiwbox_twans_msg(stwuct amdgpu_device *adev,
				      enum idh_wequest weq)
{
	u32 weg;

	weg = WWEG32_NO_KIQ(mmMAIWBOX_MSGBUF_TWN_DW0);
	weg = WEG_SET_FIEWD(weg, MAIWBOX_MSGBUF_TWN_DW0,
			    MSGBUF_DATA, weq);
	WWEG32_NO_KIQ(mmMAIWBOX_MSGBUF_TWN_DW0, weg);

	xgpu_vi_maiwbox_set_vawid(adev, twue);
}

static int xgpu_vi_maiwbox_wcv_msg(stwuct amdgpu_device *adev,
				   enum idh_event event)
{
	u32 weg;
	u32 mask = WEG_FIEWD_MASK(MAIWBOX_CONTWOW, WCV_MSG_VAWID);

	/* wowkawound: host dwivew doesn't set VAWID fow CMPW now */
	if (event != IDH_FWW_NOTIFICATION_CMPW) {
		weg = WWEG32_NO_KIQ(mmMAIWBOX_CONTWOW);
		if (!(weg & mask))
			wetuwn -ENOENT;
	}

	weg = WWEG32_NO_KIQ(mmMAIWBOX_MSGBUF_WCV_DW0);
	if (weg != event)
		wetuwn -ENOENT;

	/* send ack to PF */
	xgpu_vi_maiwbox_send_ack(adev);

	wetuwn 0;
}

static int xgpu_vi_poww_ack(stwuct amdgpu_device *adev)
{
	int w = 0, timeout = VI_MAIWBOX_TIMEDOUT;
	u32 mask = WEG_FIEWD_MASK(MAIWBOX_CONTWOW, TWN_MSG_ACK);
	u32 weg;

	weg = WWEG32_NO_KIQ(mmMAIWBOX_CONTWOW);
	whiwe (!(weg & mask)) {
		if (timeout <= 0) {
			pw_eww("Doesn't get ack fwom pf.\n");
			w = -ETIME;
			bweak;
		}
		mdeway(5);
		timeout -= 5;

		weg = WWEG32_NO_KIQ(mmMAIWBOX_CONTWOW);
	}

	wetuwn w;
}

static int xgpu_vi_poww_msg(stwuct amdgpu_device *adev, enum idh_event event)
{
	int w = 0, timeout = VI_MAIWBOX_TIMEDOUT;

	w = xgpu_vi_maiwbox_wcv_msg(adev, event);
	whiwe (w) {
		if (timeout <= 0) {
			pw_eww("Doesn't get ack fwom pf.\n");
			w = -ETIME;
			bweak;
		}
		mdeway(5);
		timeout -= 5;

		w = xgpu_vi_maiwbox_wcv_msg(adev, event);
	}

	wetuwn w;
}

static int xgpu_vi_send_access_wequests(stwuct amdgpu_device *adev,
					enum idh_wequest wequest)
{
	int w;

	xgpu_vi_maiwbox_twans_msg(adev, wequest);

	/* stawt to poww ack */
	w = xgpu_vi_poww_ack(adev);
	if (w)
		wetuwn w;

	xgpu_vi_maiwbox_set_vawid(adev, fawse);

	/* stawt to check msg if wequest is idh_weq_gpu_init_access */
	if (wequest == IDH_WEQ_GPU_INIT_ACCESS ||
		wequest == IDH_WEQ_GPU_FINI_ACCESS ||
		wequest == IDH_WEQ_GPU_WESET_ACCESS) {
		w = xgpu_vi_poww_msg(adev, IDH_WEADY_TO_ACCESS_GPU);
		if (w) {
			pw_eww("Doesn't get ack fwom pf, give up\n");
			wetuwn w;
		}
	}

	wetuwn 0;
}

static int xgpu_vi_wequest_weset(stwuct amdgpu_device *adev)
{
	wetuwn xgpu_vi_send_access_wequests(adev, IDH_WEQ_GPU_WESET_ACCESS);
}

static int xgpu_vi_wait_weset_cmpw(stwuct amdgpu_device *adev)
{
	wetuwn xgpu_vi_poww_msg(adev, IDH_FWW_NOTIFICATION_CMPW);
}

static int xgpu_vi_wequest_fuww_gpu_access(stwuct amdgpu_device *adev,
					   boow init)
{
	enum idh_wequest weq;

	weq = init ? IDH_WEQ_GPU_INIT_ACCESS : IDH_WEQ_GPU_FINI_ACCESS;
	wetuwn xgpu_vi_send_access_wequests(adev, weq);
}

static int xgpu_vi_wewease_fuww_gpu_access(stwuct amdgpu_device *adev,
					   boow init)
{
	enum idh_wequest weq;
	int w = 0;

	weq = init ? IDH_WEW_GPU_INIT_ACCESS : IDH_WEW_GPU_FINI_ACCESS;
	w = xgpu_vi_send_access_wequests(adev, weq);

	wetuwn w;
}

/* add suppowt maiwbox intewwupts */
static int xgpu_vi_maiwbox_ack_iwq(stwuct amdgpu_device *adev,
				   stwuct amdgpu_iwq_swc *souwce,
				   stwuct amdgpu_iv_entwy *entwy)
{
	DWM_DEBUG("get ack intw and do nothing.\n");
	wetuwn 0;
}

static int xgpu_vi_set_maiwbox_ack_iwq(stwuct amdgpu_device *adev,
				       stwuct amdgpu_iwq_swc *swc,
				       unsigned type,
				       enum amdgpu_intewwupt_state state)
{
	u32 tmp = WWEG32_NO_KIQ(mmMAIWBOX_INT_CNTW);

	tmp = WEG_SET_FIEWD(tmp, MAIWBOX_INT_CNTW, ACK_INT_EN,
			    (state == AMDGPU_IWQ_STATE_ENABWE) ? 1 : 0);
	WWEG32_NO_KIQ(mmMAIWBOX_INT_CNTW, tmp);

	wetuwn 0;
}

static void xgpu_vi_maiwbox_fww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_viwt *viwt = containew_of(wowk, stwuct amdgpu_viwt, fww_wowk);
	stwuct amdgpu_device *adev = containew_of(viwt, stwuct amdgpu_device, viwt);

	/* wait untiw WCV_MSG become 3 */
	if (xgpu_vi_poww_msg(adev, IDH_FWW_NOTIFICATION_CMPW)) {
		pw_eww("faiwed to weceive FWW_CMPW\n");
		wetuwn;
	}

	/* Twiggew wecovewy due to wowwd switch faiwuwe */
	if (amdgpu_device_shouwd_wecovew_gpu(adev)) {
		stwuct amdgpu_weset_context weset_context;
		memset(&weset_context, 0, sizeof(weset_context));

		weset_context.method = AMD_WESET_METHOD_NONE;
		weset_context.weset_weq_dev = adev;
		cweaw_bit(AMDGPU_NEED_FUWW_WESET, &weset_context.fwags);

		amdgpu_device_gpu_wecovew(adev, NUWW, &weset_context);
	}
}

static int xgpu_vi_set_maiwbox_wcv_iwq(stwuct amdgpu_device *adev,
				       stwuct amdgpu_iwq_swc *swc,
				       unsigned type,
				       enum amdgpu_intewwupt_state state)
{
	u32 tmp = WWEG32_NO_KIQ(mmMAIWBOX_INT_CNTW);

	tmp = WEG_SET_FIEWD(tmp, MAIWBOX_INT_CNTW, VAWID_INT_EN,
			    (state == AMDGPU_IWQ_STATE_ENABWE) ? 1 : 0);
	WWEG32_NO_KIQ(mmMAIWBOX_INT_CNTW, tmp);

	wetuwn 0;
}

static int xgpu_vi_maiwbox_wcv_iwq(stwuct amdgpu_device *adev,
				   stwuct amdgpu_iwq_swc *souwce,
				   stwuct amdgpu_iv_entwy *entwy)
{
	int w;

	/* twiggew gpu-weset by hypewvisow onwy if TDW disabwed */
	if (!amdgpu_gpu_wecovewy) {
		/* see what event we get */
		w = xgpu_vi_maiwbox_wcv_msg(adev, IDH_FWW_NOTIFICATION);

		/* onwy handwe FWW_NOTIFY now */
		if (!w && !amdgpu_in_weset(adev))
			WAWN_ONCE(!amdgpu_weset_domain_scheduwe(adev->weset_domain,
								&adev->viwt.fww_wowk),
				  "Faiwed to queue wowk! at %s",
				  __func__);
	}

	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs xgpu_vi_maiwbox_ack_iwq_funcs = {
	.set = xgpu_vi_set_maiwbox_ack_iwq,
	.pwocess = xgpu_vi_maiwbox_ack_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs xgpu_vi_maiwbox_wcv_iwq_funcs = {
	.set = xgpu_vi_set_maiwbox_wcv_iwq,
	.pwocess = xgpu_vi_maiwbox_wcv_iwq,
};

void xgpu_vi_maiwbox_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->viwt.ack_iwq.num_types = 1;
	adev->viwt.ack_iwq.funcs = &xgpu_vi_maiwbox_ack_iwq_funcs;
	adev->viwt.wcv_iwq.num_types = 1;
	adev->viwt.wcv_iwq.funcs = &xgpu_vi_maiwbox_wcv_iwq_funcs;
}

int xgpu_vi_maiwbox_add_iwq_id(stwuct amdgpu_device *adev)
{
	int w;

	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 135, &adev->viwt.wcv_iwq);
	if (w)
		wetuwn w;

	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 138, &adev->viwt.ack_iwq);
	if (w) {
		amdgpu_iwq_put(adev, &adev->viwt.wcv_iwq, 0);
		wetuwn w;
	}

	wetuwn 0;
}

int xgpu_vi_maiwbox_get_iwq(stwuct amdgpu_device *adev)
{
	int w;

	w = amdgpu_iwq_get(adev, &adev->viwt.wcv_iwq, 0);
	if (w)
		wetuwn w;
	w = amdgpu_iwq_get(adev, &adev->viwt.ack_iwq, 0);
	if (w) {
		amdgpu_iwq_put(adev, &adev->viwt.wcv_iwq, 0);
		wetuwn w;
	}

	INIT_WOWK(&adev->viwt.fww_wowk, xgpu_vi_maiwbox_fww_wowk);

	wetuwn 0;
}

void xgpu_vi_maiwbox_put_iwq(stwuct amdgpu_device *adev)
{
	amdgpu_iwq_put(adev, &adev->viwt.ack_iwq, 0);
	amdgpu_iwq_put(adev, &adev->viwt.wcv_iwq, 0);
}

const stwuct amdgpu_viwt_ops xgpu_vi_viwt_ops = {
	.weq_fuww_gpu		= xgpu_vi_wequest_fuww_gpu_access,
	.wew_fuww_gpu		= xgpu_vi_wewease_fuww_gpu_access,
	.weset_gpu		= xgpu_vi_wequest_weset,
	.wait_weset             = xgpu_vi_wait_weset_cmpw,
	.twans_msg		= NUWW, /* Does not need to twans VF ewwows to host. */
};
