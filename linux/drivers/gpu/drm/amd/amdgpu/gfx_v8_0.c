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

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "amdgpu.h"
#incwude "amdgpu_gfx.h"
#incwude "amdgpu_wing.h"
#incwude "vi.h"
#incwude "vi_stwucts.h"
#incwude "vid.h"
#incwude "amdgpu_ucode.h"
#incwude "amdgpu_atombios.h"
#incwude "atombios_i2c.h"
#incwude "cweawstate_vi.h"

#incwude "gmc/gmc_8_2_d.h"
#incwude "gmc/gmc_8_2_sh_mask.h"

#incwude "oss/oss_3_0_d.h"
#incwude "oss/oss_3_0_sh_mask.h"

#incwude "bif/bif_5_0_d.h"
#incwude "bif/bif_5_0_sh_mask.h"
#incwude "gca/gfx_8_0_d.h"
#incwude "gca/gfx_8_0_enum.h"
#incwude "gca/gfx_8_0_sh_mask.h"

#incwude "dce/dce_10_0_d.h"
#incwude "dce/dce_10_0_sh_mask.h"

#incwude "smu/smu_7_1_3_d.h"

#incwude "ivswcid/ivswcid_viswands30.h"

#define GFX8_NUM_GFX_WINGS     1
#define GFX8_MEC_HPD_SIZE 4096

#define TOPAZ_GB_ADDW_CONFIG_GOWDEN 0x22010001
#define CAWWIZO_GB_ADDW_CONFIG_GOWDEN 0x22010001
#define POWAWIS11_GB_ADDW_CONFIG_GOWDEN 0x22011002
#define TONGA_GB_ADDW_CONFIG_GOWDEN 0x22011003

#define AWWAY_MODE(x)					((x) << GB_TIWE_MODE0__AWWAY_MODE__SHIFT)
#define PIPE_CONFIG(x)					((x) << GB_TIWE_MODE0__PIPE_CONFIG__SHIFT)
#define TIWE_SPWIT(x)					((x) << GB_TIWE_MODE0__TIWE_SPWIT__SHIFT)
#define MICWO_TIWE_MODE_NEW(x)				((x) << GB_TIWE_MODE0__MICWO_TIWE_MODE_NEW__SHIFT)
#define SAMPWE_SPWIT(x)					((x) << GB_TIWE_MODE0__SAMPWE_SPWIT__SHIFT)
#define BANK_WIDTH(x)					((x) << GB_MACWOTIWE_MODE0__BANK_WIDTH__SHIFT)
#define BANK_HEIGHT(x)					((x) << GB_MACWOTIWE_MODE0__BANK_HEIGHT__SHIFT)
#define MACWO_TIWE_ASPECT(x)				((x) << GB_MACWOTIWE_MODE0__MACWO_TIWE_ASPECT__SHIFT)
#define NUM_BANKS(x)					((x) << GB_MACWOTIWE_MODE0__NUM_BANKS__SHIFT)

#define WWC_CGTT_MGCG_OVEWWIDE__CPF_MASK            0x00000001W
#define WWC_CGTT_MGCG_OVEWWIDE__WWC_MASK            0x00000002W
#define WWC_CGTT_MGCG_OVEWWIDE__MGCG_MASK           0x00000004W
#define WWC_CGTT_MGCG_OVEWWIDE__CGCG_MASK           0x00000008W
#define WWC_CGTT_MGCG_OVEWWIDE__CGWS_MASK           0x00000010W
#define WWC_CGTT_MGCG_OVEWWIDE__GWBM_MASK           0x00000020W

/* BPM SEWDES CMD */
#define SET_BPM_SEWDES_CMD    1
#define CWE_BPM_SEWDES_CMD    0

/* BPM Wegistew Addwess*/
enum {
	BPM_WEG_CGWS_EN = 0,        /* Enabwe/Disabwe CGWS */
	BPM_WEG_CGWS_ON,            /* ON/OFF CGWS: shaww be contwowwed by WWC FW */
	BPM_WEG_CGCG_OVEWWIDE,      /* Set/Cweaw CGCG Ovewwide */
	BPM_WEG_MGCG_OVEWWIDE,      /* Set/Cweaw MGCG Ovewwide */
	BPM_WEG_FGCG_OVEWWIDE,      /* Set/Cweaw FGCG Ovewwide */
	BPM_WEG_FGCG_MAX
};

#define WWC_FowmatDiwectWegWistWength        14

MODUWE_FIWMWAWE("amdgpu/cawwizo_ce.bin");
MODUWE_FIWMWAWE("amdgpu/cawwizo_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/cawwizo_me.bin");
MODUWE_FIWMWAWE("amdgpu/cawwizo_mec.bin");
MODUWE_FIWMWAWE("amdgpu/cawwizo_mec2.bin");
MODUWE_FIWMWAWE("amdgpu/cawwizo_wwc.bin");

MODUWE_FIWMWAWE("amdgpu/stoney_ce.bin");
MODUWE_FIWMWAWE("amdgpu/stoney_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/stoney_me.bin");
MODUWE_FIWMWAWE("amdgpu/stoney_mec.bin");
MODUWE_FIWMWAWE("amdgpu/stoney_wwc.bin");

MODUWE_FIWMWAWE("amdgpu/tonga_ce.bin");
MODUWE_FIWMWAWE("amdgpu/tonga_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/tonga_me.bin");
MODUWE_FIWMWAWE("amdgpu/tonga_mec.bin");
MODUWE_FIWMWAWE("amdgpu/tonga_mec2.bin");
MODUWE_FIWMWAWE("amdgpu/tonga_wwc.bin");

MODUWE_FIWMWAWE("amdgpu/topaz_ce.bin");
MODUWE_FIWMWAWE("amdgpu/topaz_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/topaz_me.bin");
MODUWE_FIWMWAWE("amdgpu/topaz_mec.bin");
MODUWE_FIWMWAWE("amdgpu/topaz_wwc.bin");

MODUWE_FIWMWAWE("amdgpu/fiji_ce.bin");
MODUWE_FIWMWAWE("amdgpu/fiji_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/fiji_me.bin");
MODUWE_FIWMWAWE("amdgpu/fiji_mec.bin");
MODUWE_FIWMWAWE("amdgpu/fiji_mec2.bin");
MODUWE_FIWMWAWE("amdgpu/fiji_wwc.bin");

MODUWE_FIWMWAWE("amdgpu/powawis10_ce.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_ce_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_pfp_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_me.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_me_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_mec.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_mec_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_mec2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_mec2_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis10_wwc.bin");

MODUWE_FIWMWAWE("amdgpu/powawis11_ce.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_ce_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_pfp_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_me.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_me_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_mec.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_mec_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_mec2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_mec2_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis11_wwc.bin");

MODUWE_FIWMWAWE("amdgpu/powawis12_ce.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_ce_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_pfp_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_me.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_me_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_mec.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_mec_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_mec2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_mec2_2.bin");
MODUWE_FIWMWAWE("amdgpu/powawis12_wwc.bin");

MODUWE_FIWMWAWE("amdgpu/vegam_ce.bin");
MODUWE_FIWMWAWE("amdgpu/vegam_pfp.bin");
MODUWE_FIWMWAWE("amdgpu/vegam_me.bin");
MODUWE_FIWMWAWE("amdgpu/vegam_mec.bin");
MODUWE_FIWMWAWE("amdgpu/vegam_mec2.bin");
MODUWE_FIWMWAWE("amdgpu/vegam_wwc.bin");

static const stwuct amdgpu_gds_weg_offset amdgpu_gds_weg_offset[] =
{
	{mmGDS_VMID0_BASE, mmGDS_VMID0_SIZE, mmGDS_GWS_VMID0, mmGDS_OA_VMID0},
	{mmGDS_VMID1_BASE, mmGDS_VMID1_SIZE, mmGDS_GWS_VMID1, mmGDS_OA_VMID1},
	{mmGDS_VMID2_BASE, mmGDS_VMID2_SIZE, mmGDS_GWS_VMID2, mmGDS_OA_VMID2},
	{mmGDS_VMID3_BASE, mmGDS_VMID3_SIZE, mmGDS_GWS_VMID3, mmGDS_OA_VMID3},
	{mmGDS_VMID4_BASE, mmGDS_VMID4_SIZE, mmGDS_GWS_VMID4, mmGDS_OA_VMID4},
	{mmGDS_VMID5_BASE, mmGDS_VMID5_SIZE, mmGDS_GWS_VMID5, mmGDS_OA_VMID5},
	{mmGDS_VMID6_BASE, mmGDS_VMID6_SIZE, mmGDS_GWS_VMID6, mmGDS_OA_VMID6},
	{mmGDS_VMID7_BASE, mmGDS_VMID7_SIZE, mmGDS_GWS_VMID7, mmGDS_OA_VMID7},
	{mmGDS_VMID8_BASE, mmGDS_VMID8_SIZE, mmGDS_GWS_VMID8, mmGDS_OA_VMID8},
	{mmGDS_VMID9_BASE, mmGDS_VMID9_SIZE, mmGDS_GWS_VMID9, mmGDS_OA_VMID9},
	{mmGDS_VMID10_BASE, mmGDS_VMID10_SIZE, mmGDS_GWS_VMID10, mmGDS_OA_VMID10},
	{mmGDS_VMID11_BASE, mmGDS_VMID11_SIZE, mmGDS_GWS_VMID11, mmGDS_OA_VMID11},
	{mmGDS_VMID12_BASE, mmGDS_VMID12_SIZE, mmGDS_GWS_VMID12, mmGDS_OA_VMID12},
	{mmGDS_VMID13_BASE, mmGDS_VMID13_SIZE, mmGDS_GWS_VMID13, mmGDS_OA_VMID13},
	{mmGDS_VMID14_BASE, mmGDS_VMID14_SIZE, mmGDS_GWS_VMID14, mmGDS_OA_VMID14},
	{mmGDS_VMID15_BASE, mmGDS_VMID15_SIZE, mmGDS_GWS_VMID15, mmGDS_OA_VMID15}
};

static const u32 gowden_settings_tonga_a11[] =
{
	mmCB_HW_CONTWOW, 0xfffdf3cf, 0x00007208,
	mmCB_HW_CONTWOW_3, 0x00000040, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmGB_GPU_ID, 0x0000000f, 0x00000000,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_FIFO_DEPTH_CNTW, 0x000003ff, 0x000000fc,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmWWC_CGCG_CGWS_CTWW, 0x00000003, 0x0000003c,
	mmSQ_WANDOM_WAVE_PWI, 0x001fffff, 0x000006fd,
	mmTA_CNTW_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTWW, 0x00100000, 0xf31fff7f,
	mmTCC_EXE_DISABWE, 0x00000002, 0x00000002,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x000002fb,
	mmTCP_CHAN_STEEW_HI, 0xffffffff, 0x0000543b,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0xa9210876,
	mmVGT_WESET_DEBUG, 0x00000004, 0x00000004,
};

static const u32 tonga_gowden_common_aww[] =
{
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_WASTEW_CONFIG, 0xffffffff, 0x16000012,
	mmPA_SC_WASTEW_CONFIG_1, 0xffffffff, 0x0000002A,
	mmGB_ADDW_CONFIG, 0xffffffff, 0x22011003,
	mmSPI_WESOUWCE_WESEWVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_1, 0xffffffff, 0x00FF7FAF
};

static const u32 tonga_mgcg_cgcg_init[] =
{
	mmWWC_CGTT_MGCG_OVEWWIDE, 0xffffffff, 0xffffffff,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CPC_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CPF_CWK_CTWW, 0xffffffff, 0x40000100,
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
	mmCGTS_CU0_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU0_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU0_TA_SQC_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU0_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU0_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU1_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU1_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU1_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU1_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU1_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU2_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU2_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU2_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU2_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU2_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU3_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU3_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU3_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU3_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU3_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU4_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU4_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU4_TA_SQC_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU4_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU4_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU5_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU5_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU5_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU5_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU5_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU6_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU6_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU6_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU6_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU6_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU7_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU7_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU7_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU7_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU7_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_SM_CTWW_WEG, 0xffffffff, 0x96e00200,
	mmCP_WB_WPTW_POWW_CNTW, 0xffffffff, 0x00900100,
	mmWWC_CGCG_CGWS_CTWW, 0xffffffff, 0x0020003c,
	mmCP_MEM_SWP_CNTW, 0x00000001, 0x00000001,
};

static const u32 gowden_settings_vegam_a11[] =
{
	mmCB_HW_CONTWOW, 0x0001f3cf, 0x00007208,
	mmCB_HW_CONTWOW_2, 0x0f000000, 0x0d000000,
	mmCB_HW_CONTWOW_3, 0x000001ff, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_WASTEW_CONFIG, 0x3f3fffff, 0x3a00161a,
	mmPA_SC_WASTEW_CONFIG_1, 0x0000003f, 0x0000002e,
	mmWWC_CGCG_CGWS_CTWW, 0x00000003, 0x0001003c,
	mmWWC_CGCG_CGWS_CTWW_3D, 0xffffffff, 0x0001003c,
	mmSQ_CONFIG, 0x07f80000, 0x01180000,
	mmTA_CNTW_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTWW, 0x00100000, 0xf31fff7f,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x000000f7,
	mmTCP_CHAN_STEEW_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0x32761054,
	mmVGT_WESET_DEBUG, 0x00000004, 0x00000004,
};

static const u32 vegam_gowden_common_aww[] =
{
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmGB_ADDW_CONFIG, 0xffffffff, 0x22011003,
	mmSPI_WESOUWCE_WESEWVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_1, 0xffffffff, 0x00FF7FAF,
};

static const u32 gowden_settings_powawis11_a11[] =
{
	mmCB_HW_CONTWOW, 0x0000f3cf, 0x00007208,
	mmCB_HW_CONTWOW_2, 0x0f000000, 0x0f000000,
	mmCB_HW_CONTWOW_3, 0x000001ff, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_WASTEW_CONFIG, 0x3f3fffff, 0x16000012,
	mmPA_SC_WASTEW_CONFIG_1, 0x0000003f, 0x00000000,
	mmWWC_CGCG_CGWS_CTWW, 0x00000003, 0x0001003c,
	mmWWC_CGCG_CGWS_CTWW_3D, 0xffffffff, 0x0001003c,
	mmSQ_CONFIG, 0x07f80000, 0x01180000,
	mmTA_CNTW_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTWW, 0x00100000, 0xf31fff7f,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x000000f3,
	mmTCP_CHAN_STEEW_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0x00003210,
	mmVGT_WESET_DEBUG, 0x00000004, 0x00000004,
};

static const u32 powawis11_gowden_common_aww[] =
{
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmGB_ADDW_CONFIG, 0xffffffff, 0x22011002,
	mmSPI_WESOUWCE_WESEWVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_1, 0xffffffff, 0x00FF7FAF,
};

static const u32 gowden_settings_powawis10_a11[] =
{
	mmATC_MISC_CG, 0x000c0fc0, 0x000c0200,
	mmCB_HW_CONTWOW, 0x0001f3cf, 0x00007208,
	mmCB_HW_CONTWOW_2, 0x0f000000, 0x0f000000,
	mmCB_HW_CONTWOW_3, 0x000001ff, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_WASTEW_CONFIG, 0x3f3fffff, 0x16000012,
	mmPA_SC_WASTEW_CONFIG_1, 0x0000003f, 0x0000002a,
	mmWWC_CGCG_CGWS_CTWW, 0x00000003, 0x0001003c,
	mmWWC_CGCG_CGWS_CTWW_3D, 0xffffffff, 0x0001003c,
	mmSQ_CONFIG, 0x07f80000, 0x07180000,
	mmTA_CNTW_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTWW, 0x00100000, 0xf31fff7f,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x000000f7,
	mmTCP_CHAN_STEEW_HI, 0xffffffff, 0x00000000,
	mmVGT_WESET_DEBUG, 0x00000004, 0x00000004,
};

static const u32 powawis10_gowden_common_aww[] =
{
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_WASTEW_CONFIG, 0xffffffff, 0x16000012,
	mmPA_SC_WASTEW_CONFIG_1, 0xffffffff, 0x0000002A,
	mmGB_ADDW_CONFIG, 0xffffffff, 0x22011003,
	mmSPI_WESOUWCE_WESEWVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_1, 0xffffffff, 0x00FF7FAF,
};

static const u32 fiji_gowden_common_aww[] =
{
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_WASTEW_CONFIG, 0xffffffff, 0x3a00161a,
	mmPA_SC_WASTEW_CONFIG_1, 0xffffffff, 0x0000002e,
	mmGB_ADDW_CONFIG, 0xffffffff, 0x22011003,
	mmSPI_WESOUWCE_WESEWVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_1, 0xffffffff, 0x00FF7FAF,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmSPI_CONFIG_CNTW_1, 0x0000000f, 0x00000009,
};

static const u32 gowden_settings_fiji_a10[] =
{
	mmCB_HW_CONTWOW_3, 0x000001ff, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmWWC_CGCG_CGWS_CTWW, 0x00000003, 0x0001003c,
	mmSQ_WANDOM_WAVE_PWI, 0x001fffff, 0x000006fd,
	mmTA_CNTW_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTWW, 0x00100000, 0xf31fff7f,
	mmTCC_EXE_DISABWE, 0x00000002, 0x00000002,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x000000ff,
	mmVGT_WESET_DEBUG, 0x00000004, 0x00000004,
};

static const u32 fiji_mgcg_cgcg_init[] =
{
	mmWWC_CGTT_MGCG_OVEWWIDE, 0xffffffff, 0xffffffff,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CPC_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CPF_CWK_CTWW, 0xffffffff, 0x40000100,
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
	mmCP_MEM_SWP_CNTW, 0x00000001, 0x00000001,
};

static const u32 gowden_settings_icewand_a11[] =
{
	mmCB_HW_CONTWOW_3, 0x00000040, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0xc0000000, 0xc0000000,
	mmGB_GPU_ID, 0x0000000f, 0x00000000,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_WASTEW_CONFIG, 0x3f3fffff, 0x00000002,
	mmPA_SC_WASTEW_CONFIG_1, 0x0000003f, 0x00000000,
	mmWWC_CGCG_CGWS_CTWW, 0x00000003, 0x0000003c,
	mmSQ_WANDOM_WAVE_PWI, 0x001fffff, 0x000006fd,
	mmTA_CNTW_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTWW, 0x00100000, 0xf31fff7f,
	mmTCC_EXE_DISABWE, 0x00000002, 0x00000002,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x000000f1,
	mmTCP_CHAN_STEEW_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0x00000010,
};

static const u32 icewand_gowden_common_aww[] =
{
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_WASTEW_CONFIG, 0xffffffff, 0x00000002,
	mmPA_SC_WASTEW_CONFIG_1, 0xffffffff, 0x00000000,
	mmGB_ADDW_CONFIG, 0xffffffff, 0x22010001,
	mmSPI_WESOUWCE_WESEWVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_1, 0xffffffff, 0x00FF7FAF
};

static const u32 icewand_mgcg_cgcg_init[] =
{
	mmWWC_CGTT_MGCG_OVEWWIDE, 0xffffffff, 0xffffffff,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CP_CWK_CTWW, 0xffffffff, 0xc0000100,
	mmCGTT_CPC_CWK_CTWW, 0xffffffff, 0xc0000100,
	mmCGTT_CPF_CWK_CTWW, 0xffffffff, 0xc0000100,
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
	mmCGTT_TCI_CWK_CTWW, 0xffffffff, 0xff000100,
	mmCGTT_TCP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CWK_CTWW, 0xffffffff, 0x06000100,
	mmDB_CGTT_CWK_CTWW_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCGTS_CU0_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU0_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU0_TA_SQC_CTWW_WEG, 0xffffffff, 0x0f840f87,
	mmCGTS_CU0_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU0_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU1_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU1_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU1_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU1_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU1_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU2_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU2_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU2_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU2_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU2_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU3_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU3_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU3_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU3_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU3_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU4_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU4_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU4_TA_SQC_CTWW_WEG, 0xffffffff, 0x0f840f87,
	mmCGTS_CU4_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU4_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU5_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU5_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU5_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU5_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU5_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_SM_CTWW_WEG, 0xffffffff, 0x96e00200,
	mmCP_WB_WPTW_POWW_CNTW, 0xffffffff, 0x00900100,
	mmWWC_CGCG_CGWS_CTWW, 0xffffffff, 0x0020003c,
};

static const u32 cz_gowden_settings_a11[] =
{
	mmCB_HW_CONTWOW_3, 0x00000040, 0x00000040,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmGB_GPU_ID, 0x0000000f, 0x00000000,
	mmPA_SC_ENHANCE, 0xffffffff, 0x00000001,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmWWC_CGCG_CGWS_CTWW, 0x00000003, 0x0000003c,
	mmSQ_WANDOM_WAVE_PWI, 0x001fffff, 0x000006fd,
	mmTA_CNTW_AUX, 0x000f000f, 0x00010000,
	mmTCC_CTWW, 0x00100000, 0xf31fff7f,
	mmTCC_EXE_DISABWE, 0x00000002, 0x00000002,
	mmTCP_ADDW_CONFIG, 0x0000000f, 0x000000f3,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0x00001302
};

static const u32 cz_gowden_common_aww[] =
{
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_WASTEW_CONFIG, 0xffffffff, 0x00000002,
	mmPA_SC_WASTEW_CONFIG_1, 0xffffffff, 0x00000000,
	mmGB_ADDW_CONFIG, 0xffffffff, 0x22010001,
	mmSPI_WESOUWCE_WESEWVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_1, 0xffffffff, 0x00FF7FAF
};

static const u32 cz_mgcg_cgcg_init[] =
{
	mmWWC_CGTT_MGCG_OVEWWIDE, 0xffffffff, 0xffffffff,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CPC_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CPF_CWK_CTWW, 0xffffffff, 0x00000100,
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
	mmCGTS_CU0_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU0_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU0_TA_SQC_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU0_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU0_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU1_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU1_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU1_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU1_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU1_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU2_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU2_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU2_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU2_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU2_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU3_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU3_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU3_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU3_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU3_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU4_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU4_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU4_TA_SQC_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU4_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU4_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU5_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU5_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU5_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU5_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU5_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU6_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU6_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU6_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU6_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU6_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_CU7_SP0_CTWW_WEG, 0xffffffff, 0x00010000,
	mmCGTS_CU7_WDS_SQ_CTWW_WEG, 0xffffffff, 0x00030002,
	mmCGTS_CU7_TA_CTWW_WEG, 0xffffffff, 0x00040007,
	mmCGTS_CU7_SP1_CTWW_WEG, 0xffffffff, 0x00060005,
	mmCGTS_CU7_TD_TCP_CTWW_WEG, 0xffffffff, 0x00090008,
	mmCGTS_SM_CTWW_WEG, 0xffffffff, 0x96e00200,
	mmCP_WB_WPTW_POWW_CNTW, 0xffffffff, 0x00900100,
	mmWWC_CGCG_CGWS_CTWW, 0xffffffff, 0x0020003f,
	mmCP_MEM_SWP_CNTW, 0x00000001, 0x00000001,
};

static const u32 stoney_gowden_settings_a11[] =
{
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmGB_GPU_ID, 0x0000000f, 0x00000000,
	mmPA_SC_ENHANCE, 0xffffffff, 0x20000001,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmWWC_CGCG_CGWS_CTWW, 0x00000003, 0x0001003c,
	mmTA_CNTW_AUX, 0x000f000f, 0x000b0000,
	mmTCC_CTWW, 0x00100000, 0xf31fff7f,
	mmTCC_EXE_DISABWE, 0x00000002, 0x00000002,
	mmTCP_ADDW_CONFIG, 0x0000000f, 0x000000f1,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0x10101010,
};

static const u32 stoney_gowden_common_aww[] =
{
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmPA_SC_WASTEW_CONFIG, 0xffffffff, 0x00000000,
	mmPA_SC_WASTEW_CONFIG_1, 0xffffffff, 0x00000000,
	mmGB_ADDW_CONFIG, 0xffffffff, 0x12010001,
	mmSPI_WESOUWCE_WESEWVE_CU_0, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_CU_1, 0xffffffff, 0x00000800,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_0, 0xffffffff, 0x00FF7FBF,
	mmSPI_WESOUWCE_WESEWVE_EN_CU_1, 0xffffffff, 0x00FF7FAF,
};

static const u32 stoney_mgcg_cgcg_init[] =
{
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmWWC_CGCG_CGWS_CTWW, 0xffffffff, 0x0020003f,
	mmCP_MEM_SWP_CNTW, 0xffffffff, 0x00020201,
	mmWWC_MEM_SWP_CNTW, 0xffffffff, 0x00020201,
	mmCGTS_SM_CTWW_WEG, 0xffffffff, 0x96940200,
};


static const chaw * const sq_edc_souwce_names[] = {
	"SQ_EDC_INFO_SOUWCE_INVAWID: No EDC ewwow has occuwwed",
	"SQ_EDC_INFO_SOUWCE_INST: EDC souwce is Instwuction Fetch",
	"SQ_EDC_INFO_SOUWCE_SGPW: EDC souwce is SGPW ow SQC data wetuwn",
	"SQ_EDC_INFO_SOUWCE_VGPW: EDC souwce is VGPW",
	"SQ_EDC_INFO_SOUWCE_WDS: EDC souwce is WDS",
	"SQ_EDC_INFO_SOUWCE_GDS: EDC souwce is GDS",
	"SQ_EDC_INFO_SOUWCE_TA: EDC souwce is TA",
};

static void gfx_v8_0_set_wing_funcs(stwuct amdgpu_device *adev);
static void gfx_v8_0_set_iwq_funcs(stwuct amdgpu_device *adev);
static void gfx_v8_0_set_gds_init(stwuct amdgpu_device *adev);
static void gfx_v8_0_set_wwc_funcs(stwuct amdgpu_device *adev);
static u32 gfx_v8_0_get_csb_size(stwuct amdgpu_device *adev);
static void gfx_v8_0_get_cu_info(stwuct amdgpu_device *adev);
static void gfx_v8_0_wing_emit_ce_meta(stwuct amdgpu_wing *wing);
static void gfx_v8_0_wing_emit_de_meta(stwuct amdgpu_wing *wing);

#define CG_ACWK_CNTW__ACWK_DIVIDEW_MASK                    0x0000007fW
#define CG_ACWK_CNTW__ACWK_DIVIDEW__SHIFT                  0x00000000W

static void gfx_v8_0_init_gowden_wegistews(stwuct amdgpu_device *adev)
{
	uint32_t data;

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							icewand_mgcg_cgcg_init,
							AWWAY_SIZE(icewand_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_icewand_a11,
							AWWAY_SIZE(gowden_settings_icewand_a11));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							icewand_gowden_common_aww,
							AWWAY_SIZE(icewand_gowden_common_aww));
		bweak;
	case CHIP_FIJI:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							fiji_mgcg_cgcg_init,
							AWWAY_SIZE(fiji_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_fiji_a10,
							AWWAY_SIZE(gowden_settings_fiji_a10));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							fiji_gowden_common_aww,
							AWWAY_SIZE(fiji_gowden_common_aww));
		bweak;

	case CHIP_TONGA:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							tonga_mgcg_cgcg_init,
							AWWAY_SIZE(tonga_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_tonga_a11,
							AWWAY_SIZE(gowden_settings_tonga_a11));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							tonga_gowden_common_aww,
							AWWAY_SIZE(tonga_gowden_common_aww));
		bweak;
	case CHIP_VEGAM:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_vegam_a11,
							AWWAY_SIZE(gowden_settings_vegam_a11));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							vegam_gowden_common_aww,
							AWWAY_SIZE(vegam_gowden_common_aww));
		bweak;
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_powawis11_a11,
							AWWAY_SIZE(gowden_settings_powawis11_a11));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							powawis11_gowden_common_aww,
							AWWAY_SIZE(powawis11_gowden_common_aww));
		bweak;
	case CHIP_POWAWIS10:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							gowden_settings_powawis10_a11,
							AWWAY_SIZE(gowden_settings_powawis10_a11));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							powawis10_gowden_common_aww,
							AWWAY_SIZE(powawis10_gowden_common_aww));
		data = WWEG32_SMC(ixCG_ACWK_CNTW);
		data &= ~CG_ACWK_CNTW__ACWK_DIVIDEW_MASK;
		data |= 0x18 << CG_ACWK_CNTW__ACWK_DIVIDEW__SHIFT;
		WWEG32_SMC(ixCG_ACWK_CNTW, data);
		if ((adev->pdev->device == 0x67DF) && (adev->pdev->wevision == 0xc7) &&
		    ((adev->pdev->subsystem_device == 0xb37 && adev->pdev->subsystem_vendow == 0x1002) ||
		     (adev->pdev->subsystem_device == 0x4a8 && adev->pdev->subsystem_vendow == 0x1043) ||
		     (adev->pdev->subsystem_device == 0x9480 && adev->pdev->subsystem_vendow == 0x1680))) {
			amdgpu_atombios_i2c_channew_twans(adev, 0x10, 0x96, 0x1E, 0xDD);
			amdgpu_atombios_i2c_channew_twans(adev, 0x10, 0x96, 0x1F, 0xD0);
		}
		bweak;
	case CHIP_CAWWIZO:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							cz_mgcg_cgcg_init,
							AWWAY_SIZE(cz_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							cz_gowden_settings_a11,
							AWWAY_SIZE(cz_gowden_settings_a11));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							cz_gowden_common_aww,
							AWWAY_SIZE(cz_gowden_common_aww));
		bweak;
	case CHIP_STONEY:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							stoney_mgcg_cgcg_init,
							AWWAY_SIZE(stoney_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							stoney_gowden_settings_a11,
							AWWAY_SIZE(stoney_gowden_settings_a11));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							stoney_gowden_common_aww,
							AWWAY_SIZE(stoney_gowden_common_aww));
		bweak;
	defauwt:
		bweak;
	}
}

static int gfx_v8_0_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t tmp = 0;
	unsigned i;
	int w;

	WWEG32(mmSCWATCH_WEG0, 0xCAFEDEAD);
	w = amdgpu_wing_awwoc(wing, 3);
	if (w)
		wetuwn w;

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_SET_UCONFIG_WEG, 1));
	amdgpu_wing_wwite(wing, mmSCWATCH_WEG0 - PACKET3_SET_UCONFIG_WEG_STAWT);
	amdgpu_wing_wwite(wing, 0xDEADBEEF);
	amdgpu_wing_commit(wing);

	fow (i = 0; i < adev->usec_timeout; i++) {
		tmp = WWEG32(mmSCWATCH_WEG0);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;

	wetuwn w;
}

static int gfx_v8_0_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct amdgpu_ib ib;
	stwuct dma_fence *f = NUWW;

	unsigned int index;
	uint64_t gpu_addw;
	uint32_t tmp;
	wong w;

	w = amdgpu_device_wb_get(adev, &index);
	if (w)
		wetuwn w;

	gpu_addw = adev->wb.gpu_addw + (index * 4);
	adev->wb.wb[index] = cpu_to_we32(0xCAFEDEAD);
	memset(&ib, 0, sizeof(ib));

	w = amdgpu_ib_get(adev, NUWW, 20, AMDGPU_IB_POOW_DIWECT, &ib);
	if (w)
		goto eww1;

	ib.ptw[0] = PACKET3(PACKET3_WWITE_DATA, 3);
	ib.ptw[1] = WWITE_DATA_DST_SEW(5) | WW_CONFIWM;
	ib.ptw[2] = wowew_32_bits(gpu_addw);
	ib.ptw[3] = uppew_32_bits(gpu_addw);
	ib.ptw[4] = 0xDEADBEEF;
	ib.wength_dw = 5;

	w = amdgpu_ib_scheduwe(wing, 1, &ib, NUWW, &f);
	if (w)
		goto eww2;

	w = dma_fence_wait_timeout(f, fawse, timeout);
	if (w == 0) {
		w = -ETIMEDOUT;
		goto eww2;
	} ewse if (w < 0) {
		goto eww2;
	}

	tmp = adev->wb.wb[index];
	if (tmp == 0xDEADBEEF)
		w = 0;
	ewse
		w = -EINVAW;

eww2:
	amdgpu_ib_fwee(adev, &ib, NUWW);
	dma_fence_put(f);
eww1:
	amdgpu_device_wb_fwee(adev, index);
	wetuwn w;
}


static void gfx_v8_0_fwee_micwocode(stwuct amdgpu_device *adev)
{
	amdgpu_ucode_wewease(&adev->gfx.pfp_fw);
	amdgpu_ucode_wewease(&adev->gfx.me_fw);
	amdgpu_ucode_wewease(&adev->gfx.ce_fw);
	amdgpu_ucode_wewease(&adev->gfx.wwc_fw);
	amdgpu_ucode_wewease(&adev->gfx.mec_fw);
	if ((adev->asic_type != CHIP_STONEY) &&
	    (adev->asic_type != CHIP_TOPAZ))
		amdgpu_ucode_wewease(&adev->gfx.mec2_fw);

	kfwee(adev->gfx.wwc.wegistew_wist_fowmat);
}

static int gfx_v8_0_init_micwocode(stwuct amdgpu_device *adev)
{
	const chaw *chip_name;
	chaw fw_name[30];
	int eww;
	stwuct amdgpu_fiwmwawe_info *info = NUWW;
	const stwuct common_fiwmwawe_headew *headew = NUWW;
	const stwuct gfx_fiwmwawe_headew_v1_0 *cp_hdw;
	const stwuct wwc_fiwmwawe_headew_v2_0 *wwc_hdw;
	unsigned int *tmp = NUWW, i;

	DWM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		chip_name = "topaz";
		bweak;
	case CHIP_TONGA:
		chip_name = "tonga";
		bweak;
	case CHIP_CAWWIZO:
		chip_name = "cawwizo";
		bweak;
	case CHIP_FIJI:
		chip_name = "fiji";
		bweak;
	case CHIP_STONEY:
		chip_name = "stoney";
		bweak;
	case CHIP_POWAWIS10:
		chip_name = "powawis10";
		bweak;
	case CHIP_POWAWIS11:
		chip_name = "powawis11";
		bweak;
	case CHIP_POWAWIS12:
		chip_name = "powawis12";
		bweak;
	case CHIP_VEGAM:
		chip_name = "vegam";
		bweak;
	defauwt:
		BUG();
	}

	if (adev->asic_type >= CHIP_POWAWIS10 && adev->asic_type <= CHIP_POWAWIS12) {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_pfp_2.bin", chip_name);
		eww = amdgpu_ucode_wequest(adev, &adev->gfx.pfp_fw, fw_name);
		if (eww == -ENODEV) {
			snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_pfp.bin", chip_name);
			eww = amdgpu_ucode_wequest(adev, &adev->gfx.pfp_fw, fw_name);
		}
	} ewse {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_pfp.bin", chip_name);
		eww = amdgpu_ucode_wequest(adev, &adev->gfx.pfp_fw, fw_name);
	}
	if (eww)
		goto out;
	cp_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.pfp_fw->data;
	adev->gfx.pfp_fw_vewsion = we32_to_cpu(cp_hdw->headew.ucode_vewsion);
	adev->gfx.pfp_featuwe_vewsion = we32_to_cpu(cp_hdw->ucode_featuwe_vewsion);

	if (adev->asic_type >= CHIP_POWAWIS10 && adev->asic_type <= CHIP_POWAWIS12) {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_me_2.bin", chip_name);
		eww = amdgpu_ucode_wequest(adev, &adev->gfx.me_fw, fw_name);
		if (eww == -ENODEV) {
			snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_me.bin", chip_name);
			eww = amdgpu_ucode_wequest(adev, &adev->gfx.me_fw, fw_name);
		}
	} ewse {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_me.bin", chip_name);
		eww = amdgpu_ucode_wequest(adev, &adev->gfx.me_fw, fw_name);
	}
	if (eww)
		goto out;
	cp_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.me_fw->data;
	adev->gfx.me_fw_vewsion = we32_to_cpu(cp_hdw->headew.ucode_vewsion);

	adev->gfx.me_featuwe_vewsion = we32_to_cpu(cp_hdw->ucode_featuwe_vewsion);

	if (adev->asic_type >= CHIP_POWAWIS10 && adev->asic_type <= CHIP_POWAWIS12) {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_ce_2.bin", chip_name);
		eww = amdgpu_ucode_wequest(adev, &adev->gfx.ce_fw, fw_name);
		if (eww == -ENODEV) {
			snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_ce.bin", chip_name);
			eww = amdgpu_ucode_wequest(adev, &adev->gfx.ce_fw, fw_name);
		}
	} ewse {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_ce.bin", chip_name);
		eww = amdgpu_ucode_wequest(adev, &adev->gfx.ce_fw, fw_name);
	}
	if (eww)
		goto out;
	cp_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.ce_fw->data;
	adev->gfx.ce_fw_vewsion = we32_to_cpu(cp_hdw->headew.ucode_vewsion);
	adev->gfx.ce_featuwe_vewsion = we32_to_cpu(cp_hdw->ucode_featuwe_vewsion);

	/*
	 * Suppowt fow MCBP/Viwtuawization in combination with chained IBs is
	 * fowmaw weweased on featuwe vewsion #46
	 */
	if (adev->gfx.ce_featuwe_vewsion >= 46 &&
	    adev->gfx.pfp_featuwe_vewsion >= 46) {
		adev->viwt.chained_ib_suppowt = twue;
		DWM_INFO("Chained IB suppowt enabwed!\n");
	} ewse
		adev->viwt.chained_ib_suppowt = fawse;

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_wwc.bin", chip_name);
	eww = amdgpu_ucode_wequest(adev, &adev->gfx.wwc_fw, fw_name);
	if (eww)
		goto out;
	wwc_hdw = (const stwuct wwc_fiwmwawe_headew_v2_0 *)adev->gfx.wwc_fw->data;
	adev->gfx.wwc_fw_vewsion = we32_to_cpu(wwc_hdw->headew.ucode_vewsion);
	adev->gfx.wwc_featuwe_vewsion = we32_to_cpu(wwc_hdw->ucode_featuwe_vewsion);

	adev->gfx.wwc.save_and_westowe_offset =
			we32_to_cpu(wwc_hdw->save_and_westowe_offset);
	adev->gfx.wwc.cweaw_state_descwiptow_offset =
			we32_to_cpu(wwc_hdw->cweaw_state_descwiptow_offset);
	adev->gfx.wwc.avaiw_scwatch_wam_wocations =
			we32_to_cpu(wwc_hdw->avaiw_scwatch_wam_wocations);
	adev->gfx.wwc.weg_westowe_wist_size =
			we32_to_cpu(wwc_hdw->weg_westowe_wist_size);
	adev->gfx.wwc.weg_wist_fowmat_stawt =
			we32_to_cpu(wwc_hdw->weg_wist_fowmat_stawt);
	adev->gfx.wwc.weg_wist_fowmat_sepawate_stawt =
			we32_to_cpu(wwc_hdw->weg_wist_fowmat_sepawate_stawt);
	adev->gfx.wwc.stawting_offsets_stawt =
			we32_to_cpu(wwc_hdw->stawting_offsets_stawt);
	adev->gfx.wwc.weg_wist_fowmat_size_bytes =
			we32_to_cpu(wwc_hdw->weg_wist_fowmat_size_bytes);
	adev->gfx.wwc.weg_wist_size_bytes =
			we32_to_cpu(wwc_hdw->weg_wist_size_bytes);

	adev->gfx.wwc.wegistew_wist_fowmat =
			kmawwoc(adev->gfx.wwc.weg_wist_fowmat_size_bytes +
					adev->gfx.wwc.weg_wist_size_bytes, GFP_KEWNEW);

	if (!adev->gfx.wwc.wegistew_wist_fowmat) {
		eww = -ENOMEM;
		goto out;
	}

	tmp = (unsigned int *)((uintptw_t)wwc_hdw +
			we32_to_cpu(wwc_hdw->weg_wist_fowmat_awway_offset_bytes));
	fow (i = 0 ; i < (adev->gfx.wwc.weg_wist_fowmat_size_bytes >> 2); i++)
		adev->gfx.wwc.wegistew_wist_fowmat[i] =	we32_to_cpu(tmp[i]);

	adev->gfx.wwc.wegistew_westowe = adev->gfx.wwc.wegistew_wist_fowmat + i;

	tmp = (unsigned int *)((uintptw_t)wwc_hdw +
			we32_to_cpu(wwc_hdw->weg_wist_awway_offset_bytes));
	fow (i = 0 ; i < (adev->gfx.wwc.weg_wist_size_bytes >> 2); i++)
		adev->gfx.wwc.wegistew_westowe[i] = we32_to_cpu(tmp[i]);

	if (adev->asic_type >= CHIP_POWAWIS10 && adev->asic_type <= CHIP_POWAWIS12) {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec_2.bin", chip_name);
		eww = amdgpu_ucode_wequest(adev, &adev->gfx.mec_fw, fw_name);
		if (eww == -ENODEV) {
			snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec.bin", chip_name);
			eww = amdgpu_ucode_wequest(adev, &adev->gfx.mec_fw, fw_name);
		}
	} ewse {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec.bin", chip_name);
		eww = amdgpu_ucode_wequest(adev, &adev->gfx.mec_fw, fw_name);
	}
	if (eww)
		goto out;
	cp_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.mec_fw->data;
	adev->gfx.mec_fw_vewsion = we32_to_cpu(cp_hdw->headew.ucode_vewsion);
	adev->gfx.mec_featuwe_vewsion = we32_to_cpu(cp_hdw->ucode_featuwe_vewsion);

	if ((adev->asic_type != CHIP_STONEY) &&
	    (adev->asic_type != CHIP_TOPAZ)) {
		if (adev->asic_type >= CHIP_POWAWIS10 && adev->asic_type <= CHIP_POWAWIS12) {
			snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec2_2.bin", chip_name);
			eww = amdgpu_ucode_wequest(adev, &adev->gfx.mec2_fw, fw_name);
			if (eww == -ENODEV) {
				snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec2.bin", chip_name);
				eww = amdgpu_ucode_wequest(adev, &adev->gfx.mec2_fw, fw_name);
			}
		} ewse {
			snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec2.bin", chip_name);
			eww = amdgpu_ucode_wequest(adev, &adev->gfx.mec2_fw, fw_name);
		}
		if (!eww) {
			cp_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)
				adev->gfx.mec2_fw->data;
			adev->gfx.mec2_fw_vewsion =
				we32_to_cpu(cp_hdw->headew.ucode_vewsion);
			adev->gfx.mec2_featuwe_vewsion =
				we32_to_cpu(cp_hdw->ucode_featuwe_vewsion);
		} ewse {
			eww = 0;
			adev->gfx.mec2_fw = NUWW;
		}
	}

	info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_CP_PFP];
	info->ucode_id = AMDGPU_UCODE_ID_CP_PFP;
	info->fw = adev->gfx.pfp_fw;
	headew = (const stwuct common_fiwmwawe_headew *)info->fw->data;
	adev->fiwmwawe.fw_size +=
		AWIGN(we32_to_cpu(headew->ucode_size_bytes), PAGE_SIZE);

	info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_CP_ME];
	info->ucode_id = AMDGPU_UCODE_ID_CP_ME;
	info->fw = adev->gfx.me_fw;
	headew = (const stwuct common_fiwmwawe_headew *)info->fw->data;
	adev->fiwmwawe.fw_size +=
		AWIGN(we32_to_cpu(headew->ucode_size_bytes), PAGE_SIZE);

	info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_CP_CE];
	info->ucode_id = AMDGPU_UCODE_ID_CP_CE;
	info->fw = adev->gfx.ce_fw;
	headew = (const stwuct common_fiwmwawe_headew *)info->fw->data;
	adev->fiwmwawe.fw_size +=
		AWIGN(we32_to_cpu(headew->ucode_size_bytes), PAGE_SIZE);

	info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_WWC_G];
	info->ucode_id = AMDGPU_UCODE_ID_WWC_G;
	info->fw = adev->gfx.wwc_fw;
	headew = (const stwuct common_fiwmwawe_headew *)info->fw->data;
	adev->fiwmwawe.fw_size +=
		AWIGN(we32_to_cpu(headew->ucode_size_bytes), PAGE_SIZE);

	info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_CP_MEC1];
	info->ucode_id = AMDGPU_UCODE_ID_CP_MEC1;
	info->fw = adev->gfx.mec_fw;
	headew = (const stwuct common_fiwmwawe_headew *)info->fw->data;
	adev->fiwmwawe.fw_size +=
		AWIGN(we32_to_cpu(headew->ucode_size_bytes), PAGE_SIZE);

	/* we need account JT in */
	cp_hdw = (const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.mec_fw->data;
	adev->fiwmwawe.fw_size +=
		AWIGN(we32_to_cpu(cp_hdw->jt_size) << 2, PAGE_SIZE);

	if (amdgpu_swiov_vf(adev)) {
		info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_STOWAGE];
		info->ucode_id = AMDGPU_UCODE_ID_STOWAGE;
		info->fw = adev->gfx.mec_fw;
		adev->fiwmwawe.fw_size +=
			AWIGN(we32_to_cpu(64 * PAGE_SIZE), PAGE_SIZE);
	}

	if (adev->gfx.mec2_fw) {
		info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_CP_MEC2];
		info->ucode_id = AMDGPU_UCODE_ID_CP_MEC2;
		info->fw = adev->gfx.mec2_fw;
		headew = (const stwuct common_fiwmwawe_headew *)info->fw->data;
		adev->fiwmwawe.fw_size +=
			AWIGN(we32_to_cpu(headew->ucode_size_bytes), PAGE_SIZE);
	}

out:
	if (eww) {
		dev_eww(adev->dev,
			"gfx8: Faiwed to woad fiwmwawe \"%s\"\n",
			fw_name);
		amdgpu_ucode_wewease(&adev->gfx.pfp_fw);
		amdgpu_ucode_wewease(&adev->gfx.me_fw);
		amdgpu_ucode_wewease(&adev->gfx.ce_fw);
		amdgpu_ucode_wewease(&adev->gfx.wwc_fw);
		amdgpu_ucode_wewease(&adev->gfx.mec_fw);
		amdgpu_ucode_wewease(&adev->gfx.mec2_fw);
	}
	wetuwn eww;
}

static void gfx_v8_0_get_csb_buffew(stwuct amdgpu_device *adev,
				    vowatiwe u32 *buffew)
{
	u32 count = 0, i;
	const stwuct cs_section_def *sect = NUWW;
	const stwuct cs_extent_def *ext = NUWW;

	if (adev->gfx.wwc.cs_data == NUWW)
		wetuwn;
	if (buffew == NUWW)
		wetuwn;

	buffew[count++] = cpu_to_we32(PACKET3(PACKET3_PWEAMBWE_CNTW, 0));
	buffew[count++] = cpu_to_we32(PACKET3_PWEAMBWE_BEGIN_CWEAW_STATE);

	buffew[count++] = cpu_to_we32(PACKET3(PACKET3_CONTEXT_CONTWOW, 1));
	buffew[count++] = cpu_to_we32(0x80000000);
	buffew[count++] = cpu_to_we32(0x80000000);

	fow (sect = adev->gfx.wwc.cs_data; sect->section != NUWW; ++sect) {
		fow (ext = sect->section; ext->extent != NUWW; ++ext) {
			if (sect->id == SECT_CONTEXT) {
				buffew[count++] =
					cpu_to_we32(PACKET3(PACKET3_SET_CONTEXT_WEG, ext->weg_count));
				buffew[count++] = cpu_to_we32(ext->weg_index -
						PACKET3_SET_CONTEXT_WEG_STAWT);
				fow (i = 0; i < ext->weg_count; i++)
					buffew[count++] = cpu_to_we32(ext->extent[i]);
			} ewse {
				wetuwn;
			}
		}
	}

	buffew[count++] = cpu_to_we32(PACKET3(PACKET3_SET_CONTEXT_WEG, 2));
	buffew[count++] = cpu_to_we32(mmPA_SC_WASTEW_CONFIG -
			PACKET3_SET_CONTEXT_WEG_STAWT);
	buffew[count++] = cpu_to_we32(adev->gfx.config.wb_config[0][0].wastew_config);
	buffew[count++] = cpu_to_we32(adev->gfx.config.wb_config[0][0].wastew_config_1);

	buffew[count++] = cpu_to_we32(PACKET3(PACKET3_PWEAMBWE_CNTW, 0));
	buffew[count++] = cpu_to_we32(PACKET3_PWEAMBWE_END_CWEAW_STATE);

	buffew[count++] = cpu_to_we32(PACKET3(PACKET3_CWEAW_STATE, 0));
	buffew[count++] = cpu_to_we32(0);
}

static int gfx_v8_0_cp_jump_tabwe_num(stwuct amdgpu_device *adev)
{
	if (adev->asic_type == CHIP_CAWWIZO)
		wetuwn 5;
	ewse
		wetuwn 4;
}

static int gfx_v8_0_wwc_init(stwuct amdgpu_device *adev)
{
	const stwuct cs_section_def *cs_data;
	int w;

	adev->gfx.wwc.cs_data = vi_cs_data;

	cs_data = adev->gfx.wwc.cs_data;

	if (cs_data) {
		/* init cweaw state bwock */
		w = amdgpu_gfx_wwc_init_csb(adev);
		if (w)
			wetuwn w;
	}

	if ((adev->asic_type == CHIP_CAWWIZO) ||
	    (adev->asic_type == CHIP_STONEY)) {
		adev->gfx.wwc.cp_tabwe_size = AWIGN(96 * 5 * 4, 2048) + (64 * 1024); /* JT + GDS */
		w = amdgpu_gfx_wwc_init_cpt(adev);
		if (w)
			wetuwn w;
	}

	/* init spm vmid with 0xf */
	if (adev->gfx.wwc.funcs->update_spm_vmid)
		adev->gfx.wwc.funcs->update_spm_vmid(adev, 0xf);

	wetuwn 0;
}

static void gfx_v8_0_mec_fini(stwuct amdgpu_device *adev)
{
	amdgpu_bo_fwee_kewnew(&adev->gfx.mec.hpd_eop_obj, NUWW, NUWW);
}

static int gfx_v8_0_mec_init(stwuct amdgpu_device *adev)
{
	int w;
	u32 *hpd;
	size_t mec_hpd_size;

	bitmap_zewo(adev->gfx.mec_bitmap[0].queue_bitmap, AMDGPU_MAX_COMPUTE_QUEUES);

	/* take ownewship of the wewevant compute queues */
	amdgpu_gfx_compute_queue_acquiwe(adev);

	mec_hpd_size = adev->gfx.num_compute_wings * GFX8_MEC_HPD_SIZE;
	if (mec_hpd_size) {
		w = amdgpu_bo_cweate_wesewved(adev, mec_hpd_size, PAGE_SIZE,
					      AMDGPU_GEM_DOMAIN_VWAM |
					      AMDGPU_GEM_DOMAIN_GTT,
					      &adev->gfx.mec.hpd_eop_obj,
					      &adev->gfx.mec.hpd_eop_gpu_addw,
					      (void **)&hpd);
		if (w) {
			dev_wawn(adev->dev, "(%d) cweate HDP EOP bo faiwed\n", w);
			wetuwn w;
		}

		memset(hpd, 0, mec_hpd_size);

		amdgpu_bo_kunmap(adev->gfx.mec.hpd_eop_obj);
		amdgpu_bo_unwesewve(adev->gfx.mec.hpd_eop_obj);
	}

	wetuwn 0;
}

static const u32 vgpw_init_compute_shadew[] =
{
	0x7e000209, 0x7e020208,
	0x7e040207, 0x7e060206,
	0x7e080205, 0x7e0a0204,
	0x7e0c0203, 0x7e0e0202,
	0x7e100201, 0x7e120200,
	0x7e140209, 0x7e160208,
	0x7e180207, 0x7e1a0206,
	0x7e1c0205, 0x7e1e0204,
	0x7e200203, 0x7e220202,
	0x7e240201, 0x7e260200,
	0x7e280209, 0x7e2a0208,
	0x7e2c0207, 0x7e2e0206,
	0x7e300205, 0x7e320204,
	0x7e340203, 0x7e360202,
	0x7e380201, 0x7e3a0200,
	0x7e3c0209, 0x7e3e0208,
	0x7e400207, 0x7e420206,
	0x7e440205, 0x7e460204,
	0x7e480203, 0x7e4a0202,
	0x7e4c0201, 0x7e4e0200,
	0x7e500209, 0x7e520208,
	0x7e540207, 0x7e560206,
	0x7e580205, 0x7e5a0204,
	0x7e5c0203, 0x7e5e0202,
	0x7e600201, 0x7e620200,
	0x7e640209, 0x7e660208,
	0x7e680207, 0x7e6a0206,
	0x7e6c0205, 0x7e6e0204,
	0x7e700203, 0x7e720202,
	0x7e740201, 0x7e760200,
	0x7e780209, 0x7e7a0208,
	0x7e7c0207, 0x7e7e0206,
	0xbf8a0000, 0xbf810000,
};

static const u32 sgpw_init_compute_shadew[] =
{
	0xbe8a0100, 0xbe8c0102,
	0xbe8e0104, 0xbe900106,
	0xbe920108, 0xbe940100,
	0xbe960102, 0xbe980104,
	0xbe9a0106, 0xbe9c0108,
	0xbe9e0100, 0xbea00102,
	0xbea20104, 0xbea40106,
	0xbea60108, 0xbea80100,
	0xbeaa0102, 0xbeac0104,
	0xbeae0106, 0xbeb00108,
	0xbeb20100, 0xbeb40102,
	0xbeb60104, 0xbeb80106,
	0xbeba0108, 0xbebc0100,
	0xbebe0102, 0xbec00104,
	0xbec20106, 0xbec40108,
	0xbec60100, 0xbec80102,
	0xbee60004, 0xbee70005,
	0xbeea0006, 0xbeeb0007,
	0xbee80008, 0xbee90009,
	0xbefc0000, 0xbf8a0000,
	0xbf810000, 0x00000000,
};

static const u32 vgpw_init_wegs[] =
{
	mmCOMPUTE_STATIC_THWEAD_MGMT_SE0, 0xffffffff,
	mmCOMPUTE_WESOUWCE_WIMITS, 0x1000000, /* CU_GWOUP_COUNT=1 */
	mmCOMPUTE_NUM_THWEAD_X, 256*4,
	mmCOMPUTE_NUM_THWEAD_Y, 1,
	mmCOMPUTE_NUM_THWEAD_Z, 1,
	mmCOMPUTE_PGM_WSWC1, 0x100004f, /* VGPWS=15 (64 wogicaw VGPWs), SGPWS=1 (16 SGPWs), BUWKY=1 */
	mmCOMPUTE_PGM_WSWC2, 20,
	mmCOMPUTE_USEW_DATA_0, 0xedcedc00,
	mmCOMPUTE_USEW_DATA_1, 0xedcedc01,
	mmCOMPUTE_USEW_DATA_2, 0xedcedc02,
	mmCOMPUTE_USEW_DATA_3, 0xedcedc03,
	mmCOMPUTE_USEW_DATA_4, 0xedcedc04,
	mmCOMPUTE_USEW_DATA_5, 0xedcedc05,
	mmCOMPUTE_USEW_DATA_6, 0xedcedc06,
	mmCOMPUTE_USEW_DATA_7, 0xedcedc07,
	mmCOMPUTE_USEW_DATA_8, 0xedcedc08,
	mmCOMPUTE_USEW_DATA_9, 0xedcedc09,
};

static const u32 sgpw1_init_wegs[] =
{
	mmCOMPUTE_STATIC_THWEAD_MGMT_SE0, 0x0f,
	mmCOMPUTE_WESOUWCE_WIMITS, 0x1000000, /* CU_GWOUP_COUNT=1 */
	mmCOMPUTE_NUM_THWEAD_X, 256*5,
	mmCOMPUTE_NUM_THWEAD_Y, 1,
	mmCOMPUTE_NUM_THWEAD_Z, 1,
	mmCOMPUTE_PGM_WSWC1, 0x240, /* SGPWS=9 (80 GPWS) */
	mmCOMPUTE_PGM_WSWC2, 20,
	mmCOMPUTE_USEW_DATA_0, 0xedcedc00,
	mmCOMPUTE_USEW_DATA_1, 0xedcedc01,
	mmCOMPUTE_USEW_DATA_2, 0xedcedc02,
	mmCOMPUTE_USEW_DATA_3, 0xedcedc03,
	mmCOMPUTE_USEW_DATA_4, 0xedcedc04,
	mmCOMPUTE_USEW_DATA_5, 0xedcedc05,
	mmCOMPUTE_USEW_DATA_6, 0xedcedc06,
	mmCOMPUTE_USEW_DATA_7, 0xedcedc07,
	mmCOMPUTE_USEW_DATA_8, 0xedcedc08,
	mmCOMPUTE_USEW_DATA_9, 0xedcedc09,
};

static const u32 sgpw2_init_wegs[] =
{
	mmCOMPUTE_STATIC_THWEAD_MGMT_SE0, 0xf0,
	mmCOMPUTE_WESOUWCE_WIMITS, 0x1000000,
	mmCOMPUTE_NUM_THWEAD_X, 256*5,
	mmCOMPUTE_NUM_THWEAD_Y, 1,
	mmCOMPUTE_NUM_THWEAD_Z, 1,
	mmCOMPUTE_PGM_WSWC1, 0x240, /* SGPWS=9 (80 GPWS) */
	mmCOMPUTE_PGM_WSWC2, 20,
	mmCOMPUTE_USEW_DATA_0, 0xedcedc00,
	mmCOMPUTE_USEW_DATA_1, 0xedcedc01,
	mmCOMPUTE_USEW_DATA_2, 0xedcedc02,
	mmCOMPUTE_USEW_DATA_3, 0xedcedc03,
	mmCOMPUTE_USEW_DATA_4, 0xedcedc04,
	mmCOMPUTE_USEW_DATA_5, 0xedcedc05,
	mmCOMPUTE_USEW_DATA_6, 0xedcedc06,
	mmCOMPUTE_USEW_DATA_7, 0xedcedc07,
	mmCOMPUTE_USEW_DATA_8, 0xedcedc08,
	mmCOMPUTE_USEW_DATA_9, 0xedcedc09,
};

static const u32 sec_ded_countew_wegistews[] =
{
	mmCPC_EDC_ATC_CNT,
	mmCPC_EDC_SCWATCH_CNT,
	mmCPC_EDC_UCODE_CNT,
	mmCPF_EDC_ATC_CNT,
	mmCPF_EDC_WOQ_CNT,
	mmCPF_EDC_TAG_CNT,
	mmCPG_EDC_ATC_CNT,
	mmCPG_EDC_DMA_CNT,
	mmCPG_EDC_TAG_CNT,
	mmDC_EDC_CSINVOC_CNT,
	mmDC_EDC_WESTOWE_CNT,
	mmDC_EDC_STATE_CNT,
	mmGDS_EDC_CNT,
	mmGDS_EDC_GWBM_CNT,
	mmGDS_EDC_OA_DED,
	mmSPI_EDC_CNT,
	mmSQC_ATC_EDC_GATCW1_CNT,
	mmSQC_EDC_CNT,
	mmSQ_EDC_DED_CNT,
	mmSQ_EDC_INFO,
	mmSQ_EDC_SEC_CNT,
	mmTCC_EDC_CNT,
	mmTCP_ATC_EDC_GATCW1_CNT,
	mmTCP_EDC_CNT,
	mmTD_EDC_CNT
};

static int gfx_v8_0_do_edc_gpw_wowkawounds(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing = &adev->gfx.compute_wing[0];
	stwuct amdgpu_ib ib;
	stwuct dma_fence *f = NUWW;
	int w, i;
	u32 tmp;
	unsigned totaw_size, vgpw_offset, sgpw_offset;
	u64 gpu_addw;

	/* onwy suppowted on CZ */
	if (adev->asic_type != CHIP_CAWWIZO)
		wetuwn 0;

	/* baiw if the compute wing is not weady */
	if (!wing->sched.weady)
		wetuwn 0;

	tmp = WWEG32(mmGB_EDC_MODE);
	WWEG32(mmGB_EDC_MODE, 0);

	totaw_size =
		(((AWWAY_SIZE(vgpw_init_wegs) / 2) * 3) + 4 + 5 + 2) * 4;
	totaw_size +=
		(((AWWAY_SIZE(sgpw1_init_wegs) / 2) * 3) + 4 + 5 + 2) * 4;
	totaw_size +=
		(((AWWAY_SIZE(sgpw2_init_wegs) / 2) * 3) + 4 + 5 + 2) * 4;
	totaw_size = AWIGN(totaw_size, 256);
	vgpw_offset = totaw_size;
	totaw_size += AWIGN(sizeof(vgpw_init_compute_shadew), 256);
	sgpw_offset = totaw_size;
	totaw_size += sizeof(sgpw_init_compute_shadew);

	/* awwocate an indiwect buffew to put the commands in */
	memset(&ib, 0, sizeof(ib));
	w = amdgpu_ib_get(adev, NUWW, totaw_size,
					AMDGPU_IB_POOW_DIWECT, &ib);
	if (w) {
		DWM_EWWOW("amdgpu: faiwed to get ib (%d).\n", w);
		wetuwn w;
	}

	/* woad the compute shadews */
	fow (i = 0; i < AWWAY_SIZE(vgpw_init_compute_shadew); i++)
		ib.ptw[i + (vgpw_offset / 4)] = vgpw_init_compute_shadew[i];

	fow (i = 0; i < AWWAY_SIZE(sgpw_init_compute_shadew); i++)
		ib.ptw[i + (sgpw_offset / 4)] = sgpw_init_compute_shadew[i];

	/* init the ib wength to 0 */
	ib.wength_dw = 0;

	/* VGPW */
	/* wwite the wegistew state fow the compute dispatch */
	fow (i = 0; i < AWWAY_SIZE(vgpw_init_wegs); i += 2) {
		ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_SET_SH_WEG, 1);
		ib.ptw[ib.wength_dw++] = vgpw_init_wegs[i] - PACKET3_SET_SH_WEG_STAWT;
		ib.ptw[ib.wength_dw++] = vgpw_init_wegs[i + 1];
	}
	/* wwite the shadew stawt addwess: mmCOMPUTE_PGM_WO, mmCOMPUTE_PGM_HI */
	gpu_addw = (ib.gpu_addw + (u64)vgpw_offset) >> 8;
	ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_SET_SH_WEG, 2);
	ib.ptw[ib.wength_dw++] = mmCOMPUTE_PGM_WO - PACKET3_SET_SH_WEG_STAWT;
	ib.ptw[ib.wength_dw++] = wowew_32_bits(gpu_addw);
	ib.ptw[ib.wength_dw++] = uppew_32_bits(gpu_addw);

	/* wwite dispatch packet */
	ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_DISPATCH_DIWECT, 3);
	ib.ptw[ib.wength_dw++] = 8; /* x */
	ib.ptw[ib.wength_dw++] = 1; /* y */
	ib.ptw[ib.wength_dw++] = 1; /* z */
	ib.ptw[ib.wength_dw++] =
		WEG_SET_FIEWD(0, COMPUTE_DISPATCH_INITIATOW, COMPUTE_SHADEW_EN, 1);

	/* wwite CS pawtiaw fwush packet */
	ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_EVENT_WWITE, 0);
	ib.ptw[ib.wength_dw++] = EVENT_TYPE(7) | EVENT_INDEX(4);

	/* SGPW1 */
	/* wwite the wegistew state fow the compute dispatch */
	fow (i = 0; i < AWWAY_SIZE(sgpw1_init_wegs); i += 2) {
		ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_SET_SH_WEG, 1);
		ib.ptw[ib.wength_dw++] = sgpw1_init_wegs[i] - PACKET3_SET_SH_WEG_STAWT;
		ib.ptw[ib.wength_dw++] = sgpw1_init_wegs[i + 1];
	}
	/* wwite the shadew stawt addwess: mmCOMPUTE_PGM_WO, mmCOMPUTE_PGM_HI */
	gpu_addw = (ib.gpu_addw + (u64)sgpw_offset) >> 8;
	ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_SET_SH_WEG, 2);
	ib.ptw[ib.wength_dw++] = mmCOMPUTE_PGM_WO - PACKET3_SET_SH_WEG_STAWT;
	ib.ptw[ib.wength_dw++] = wowew_32_bits(gpu_addw);
	ib.ptw[ib.wength_dw++] = uppew_32_bits(gpu_addw);

	/* wwite dispatch packet */
	ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_DISPATCH_DIWECT, 3);
	ib.ptw[ib.wength_dw++] = 8; /* x */
	ib.ptw[ib.wength_dw++] = 1; /* y */
	ib.ptw[ib.wength_dw++] = 1; /* z */
	ib.ptw[ib.wength_dw++] =
		WEG_SET_FIEWD(0, COMPUTE_DISPATCH_INITIATOW, COMPUTE_SHADEW_EN, 1);

	/* wwite CS pawtiaw fwush packet */
	ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_EVENT_WWITE, 0);
	ib.ptw[ib.wength_dw++] = EVENT_TYPE(7) | EVENT_INDEX(4);

	/* SGPW2 */
	/* wwite the wegistew state fow the compute dispatch */
	fow (i = 0; i < AWWAY_SIZE(sgpw2_init_wegs); i += 2) {
		ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_SET_SH_WEG, 1);
		ib.ptw[ib.wength_dw++] = sgpw2_init_wegs[i] - PACKET3_SET_SH_WEG_STAWT;
		ib.ptw[ib.wength_dw++] = sgpw2_init_wegs[i + 1];
	}
	/* wwite the shadew stawt addwess: mmCOMPUTE_PGM_WO, mmCOMPUTE_PGM_HI */
	gpu_addw = (ib.gpu_addw + (u64)sgpw_offset) >> 8;
	ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_SET_SH_WEG, 2);
	ib.ptw[ib.wength_dw++] = mmCOMPUTE_PGM_WO - PACKET3_SET_SH_WEG_STAWT;
	ib.ptw[ib.wength_dw++] = wowew_32_bits(gpu_addw);
	ib.ptw[ib.wength_dw++] = uppew_32_bits(gpu_addw);

	/* wwite dispatch packet */
	ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_DISPATCH_DIWECT, 3);
	ib.ptw[ib.wength_dw++] = 8; /* x */
	ib.ptw[ib.wength_dw++] = 1; /* y */
	ib.ptw[ib.wength_dw++] = 1; /* z */
	ib.ptw[ib.wength_dw++] =
		WEG_SET_FIEWD(0, COMPUTE_DISPATCH_INITIATOW, COMPUTE_SHADEW_EN, 1);

	/* wwite CS pawtiaw fwush packet */
	ib.ptw[ib.wength_dw++] = PACKET3(PACKET3_EVENT_WWITE, 0);
	ib.ptw[ib.wength_dw++] = EVENT_TYPE(7) | EVENT_INDEX(4);

	/* sheduwe the ib on the wing */
	w = amdgpu_ib_scheduwe(wing, 1, &ib, NUWW, &f);
	if (w) {
		DWM_EWWOW("amdgpu: ib submit faiwed (%d).\n", w);
		goto faiw;
	}

	/* wait fow the GPU to finish pwocessing the IB */
	w = dma_fence_wait(f, fawse);
	if (w) {
		DWM_EWWOW("amdgpu: fence wait faiwed (%d).\n", w);
		goto faiw;
	}

	tmp = WEG_SET_FIEWD(tmp, GB_EDC_MODE, DED_MODE, 2);
	tmp = WEG_SET_FIEWD(tmp, GB_EDC_MODE, PWOP_FED, 1);
	WWEG32(mmGB_EDC_MODE, tmp);

	tmp = WWEG32(mmCC_GC_EDC_CONFIG);
	tmp = WEG_SET_FIEWD(tmp, CC_GC_EDC_CONFIG, DIS_EDC, 0) | 1;
	WWEG32(mmCC_GC_EDC_CONFIG, tmp);


	/* wead back wegistews to cweaw the countews */
	fow (i = 0; i < AWWAY_SIZE(sec_ded_countew_wegistews); i++)
		WWEG32(sec_ded_countew_wegistews[i]);

faiw:
	amdgpu_ib_fwee(adev, &ib, NUWW);
	dma_fence_put(f);

	wetuwn w;
}

static int gfx_v8_0_gpu_eawwy_init(stwuct amdgpu_device *adev)
{
	u32 gb_addw_config;
	u32 mc_awb_wamcfg;
	u32 dimm00_addw_map, dimm01_addw_map, dimm10_addw_map, dimm11_addw_map;
	u32 tmp;
	int wet;

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		adev->gfx.config.max_shadew_engines = 1;
		adev->gfx.config.max_tiwe_pipes = 2;
		adev->gfx.config.max_cu_pew_sh = 6;
		adev->gfx.config.max_sh_pew_se = 1;
		adev->gfx.config.max_backends_pew_se = 2;
		adev->gfx.config.max_textuwe_channew_caches = 2;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = TOPAZ_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_FIJI:
		adev->gfx.config.max_shadew_engines = 4;
		adev->gfx.config.max_tiwe_pipes = 16;
		adev->gfx.config.max_cu_pew_sh = 16;
		adev->gfx.config.max_sh_pew_se = 1;
		adev->gfx.config.max_backends_pew_se = 4;
		adev->gfx.config.max_textuwe_channew_caches = 16;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = TONGA_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
		wet = amdgpu_atombios_get_gfx_info(adev);
		if (wet)
			wetuwn wet;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = POWAWIS11_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_POWAWIS10:
	case CHIP_VEGAM:
		wet = amdgpu_atombios_get_gfx_info(adev);
		if (wet)
			wetuwn wet;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = TONGA_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_TONGA:
		adev->gfx.config.max_shadew_engines = 4;
		adev->gfx.config.max_tiwe_pipes = 8;
		adev->gfx.config.max_cu_pew_sh = 8;
		adev->gfx.config.max_sh_pew_se = 1;
		adev->gfx.config.max_backends_pew_se = 2;
		adev->gfx.config.max_textuwe_channew_caches = 8;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = TONGA_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_CAWWIZO:
		adev->gfx.config.max_shadew_engines = 1;
		adev->gfx.config.max_tiwe_pipes = 2;
		adev->gfx.config.max_sh_pew_se = 1;
		adev->gfx.config.max_backends_pew_se = 2;
		adev->gfx.config.max_cu_pew_sh = 8;
		adev->gfx.config.max_textuwe_channew_caches = 2;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = CAWWIZO_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_STONEY:
		adev->gfx.config.max_shadew_engines = 1;
		adev->gfx.config.max_tiwe_pipes = 2;
		adev->gfx.config.max_sh_pew_se = 1;
		adev->gfx.config.max_backends_pew_se = 1;
		adev->gfx.config.max_cu_pew_sh = 3;
		adev->gfx.config.max_textuwe_channew_caches = 2;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 16;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = CAWWIZO_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	defauwt:
		adev->gfx.config.max_shadew_engines = 2;
		adev->gfx.config.max_tiwe_pipes = 4;
		adev->gfx.config.max_cu_pew_sh = 2;
		adev->gfx.config.max_sh_pew_se = 1;
		adev->gfx.config.max_backends_pew_se = 2;
		adev->gfx.config.max_textuwe_channew_caches = 4;
		adev->gfx.config.max_gpws = 256;
		adev->gfx.config.max_gs_thweads = 32;
		adev->gfx.config.max_hw_contexts = 8;

		adev->gfx.config.sc_pwim_fifo_size_fwontend = 0x20;
		adev->gfx.config.sc_pwim_fifo_size_backend = 0x100;
		adev->gfx.config.sc_hiz_tiwe_fifo_size = 0x30;
		adev->gfx.config.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = TONGA_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	}

	adev->gfx.config.mc_awb_wamcfg = WWEG32(mmMC_AWB_WAMCFG);
	mc_awb_wamcfg = adev->gfx.config.mc_awb_wamcfg;

	adev->gfx.config.num_banks = WEG_GET_FIEWD(mc_awb_wamcfg,
				MC_AWB_WAMCFG, NOOFBANK);
	adev->gfx.config.num_wanks = WEG_GET_FIEWD(mc_awb_wamcfg,
				MC_AWB_WAMCFG, NOOFWANKS);

	adev->gfx.config.num_tiwe_pipes = adev->gfx.config.max_tiwe_pipes;
	adev->gfx.config.mem_max_buwst_wength_bytes = 256;
	if (adev->fwags & AMD_IS_APU) {
		/* Get memowy bank mapping mode. */
		tmp = WWEG32(mmMC_FUS_DWAM0_BANK_ADDW_MAPPING);
		dimm00_addw_map = WEG_GET_FIEWD(tmp, MC_FUS_DWAM0_BANK_ADDW_MAPPING, DIMM0ADDWMAP);
		dimm01_addw_map = WEG_GET_FIEWD(tmp, MC_FUS_DWAM0_BANK_ADDW_MAPPING, DIMM1ADDWMAP);

		tmp = WWEG32(mmMC_FUS_DWAM1_BANK_ADDW_MAPPING);
		dimm10_addw_map = WEG_GET_FIEWD(tmp, MC_FUS_DWAM1_BANK_ADDW_MAPPING, DIMM0ADDWMAP);
		dimm11_addw_map = WEG_GET_FIEWD(tmp, MC_FUS_DWAM1_BANK_ADDW_MAPPING, DIMM1ADDWMAP);

		/* Vawidate settings in case onwy one DIMM instawwed. */
		if ((dimm00_addw_map == 0) || (dimm00_addw_map == 3) || (dimm00_addw_map == 4) || (dimm00_addw_map > 12))
			dimm00_addw_map = 0;
		if ((dimm01_addw_map == 0) || (dimm01_addw_map == 3) || (dimm01_addw_map == 4) || (dimm01_addw_map > 12))
			dimm01_addw_map = 0;
		if ((dimm10_addw_map == 0) || (dimm10_addw_map == 3) || (dimm10_addw_map == 4) || (dimm10_addw_map > 12))
			dimm10_addw_map = 0;
		if ((dimm11_addw_map == 0) || (dimm11_addw_map == 3) || (dimm11_addw_map == 4) || (dimm11_addw_map > 12))
			dimm11_addw_map = 0;

		/* If DIMM Addw map is 8GB, WOW size shouwd be 2KB. Othewwise 1KB. */
		/* If WOW size(DIMM1) != WOW size(DMIMM0), WOW size shouwd be wawgew one. */
		if ((dimm00_addw_map == 11) || (dimm01_addw_map == 11) || (dimm10_addw_map == 11) || (dimm11_addw_map == 11))
			adev->gfx.config.mem_wow_size_in_kb = 2;
		ewse
			adev->gfx.config.mem_wow_size_in_kb = 1;
	} ewse {
		tmp = WEG_GET_FIEWD(mc_awb_wamcfg, MC_AWB_WAMCFG, NOOFCOWS);
		adev->gfx.config.mem_wow_size_in_kb = (4 * (1 << (8 + tmp))) / 1024;
		if (adev->gfx.config.mem_wow_size_in_kb > 4)
			adev->gfx.config.mem_wow_size_in_kb = 4;
	}

	adev->gfx.config.shadew_engine_tiwe_size = 32;
	adev->gfx.config.num_gpus = 1;
	adev->gfx.config.muwti_gpu_tiwe_size = 64;

	/* fix up wow size */
	switch (adev->gfx.config.mem_wow_size_in_kb) {
	case 1:
	defauwt:
		gb_addw_config = WEG_SET_FIEWD(gb_addw_config, GB_ADDW_CONFIG, WOW_SIZE, 0);
		bweak;
	case 2:
		gb_addw_config = WEG_SET_FIEWD(gb_addw_config, GB_ADDW_CONFIG, WOW_SIZE, 1);
		bweak;
	case 4:
		gb_addw_config = WEG_SET_FIEWD(gb_addw_config, GB_ADDW_CONFIG, WOW_SIZE, 2);
		bweak;
	}
	adev->gfx.config.gb_addw_config = gb_addw_config;

	wetuwn 0;
}

static int gfx_v8_0_compute_wing_init(stwuct amdgpu_device *adev, int wing_id,
					int mec, int pipe, int queue)
{
	int w;
	unsigned iwq_type;
	stwuct amdgpu_wing *wing = &adev->gfx.compute_wing[wing_id];
	unsigned int hw_pwio;

	wing = &adev->gfx.compute_wing[wing_id];

	/* mec0 is me1 */
	wing->me = mec + 1;
	wing->pipe = pipe;
	wing->queue = queue;

	wing->wing_obj = NUWW;
	wing->use_doowbeww = twue;
	wing->doowbeww_index = adev->doowbeww_index.mec_wing0 + wing_id;
	wing->eop_gpu_addw = adev->gfx.mec.hpd_eop_gpu_addw
				+ (wing_id * GFX8_MEC_HPD_SIZE);
	spwintf(wing->name, "comp_%d.%d.%d", wing->me, wing->pipe, wing->queue);

	iwq_type = AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE0_EOP
		+ ((wing->me - 1) * adev->gfx.mec.num_pipe_pew_mec)
		+ wing->pipe;

	hw_pwio = amdgpu_gfx_is_high_pwiowity_compute_queue(adev, wing) ?
			AMDGPU_WING_PWIO_2 : AMDGPU_WING_PWIO_DEFAUWT;
	/* type-2 packets awe depwecated on MEC, use type-3 instead */
	w = amdgpu_wing_init(adev, wing, 1024, &adev->gfx.eop_iwq, iwq_type,
			     hw_pwio, NUWW);
	if (w)
		wetuwn w;


	wetuwn 0;
}

static void gfx_v8_0_sq_iwq_wowk_func(stwuct wowk_stwuct *wowk);

static int gfx_v8_0_sw_init(void *handwe)
{
	int i, j, k, w, wing_id;
	stwuct amdgpu_wing *wing;
	stwuct amdgpu_kiq *kiq;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	switch (adev->asic_type) {
	case CHIP_TONGA:
	case CHIP_CAWWIZO:
	case CHIP_FIJI:
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		adev->gfx.mec.num_mec = 2;
		bweak;
	case CHIP_TOPAZ:
	case CHIP_STONEY:
	defauwt:
		adev->gfx.mec.num_mec = 1;
		bweak;
	}

	adev->gfx.mec.num_pipe_pew_mec = 4;
	adev->gfx.mec.num_queue_pew_pipe = 8;

	/* EOP Event */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, VISWANDS30_IV_SWCID_CP_END_OF_PIPE, &adev->gfx.eop_iwq);
	if (w)
		wetuwn w;

	/* Pwiviweged weg */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, VISWANDS30_IV_SWCID_CP_PWIV_WEG_FAUWT,
			      &adev->gfx.pwiv_weg_iwq);
	if (w)
		wetuwn w;

	/* Pwiviweged inst */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, VISWANDS30_IV_SWCID_CP_PWIV_INSTW_FAUWT,
			      &adev->gfx.pwiv_inst_iwq);
	if (w)
		wetuwn w;

	/* Add CP EDC/ECC iwq  */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, VISWANDS30_IV_SWCID_CP_ECC_EWWOW,
			      &adev->gfx.cp_ecc_ewwow_iwq);
	if (w)
		wetuwn w;

	/* SQ intewwupts. */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, VISWANDS30_IV_SWCID_SQ_INTEWWUPT_MSG,
			      &adev->gfx.sq_iwq);
	if (w) {
		DWM_EWWOW("amdgpu_iwq_add() fow SQ faiwed: %d\n", w);
		wetuwn w;
	}

	INIT_WOWK(&adev->gfx.sq_wowk.wowk, gfx_v8_0_sq_iwq_wowk_func);

	adev->gfx.gfx_cuwwent_status = AMDGPU_GFX_NOWMAW_MODE;

	w = gfx_v8_0_init_micwocode(adev);
	if (w) {
		DWM_EWWOW("Faiwed to woad gfx fiwmwawe!\n");
		wetuwn w;
	}

	w = adev->gfx.wwc.funcs->init(adev);
	if (w) {
		DWM_EWWOW("Faiwed to init wwc BOs!\n");
		wetuwn w;
	}

	w = gfx_v8_0_mec_init(adev);
	if (w) {
		DWM_EWWOW("Faiwed to init MEC BOs!\n");
		wetuwn w;
	}

	/* set up the gfx wing */
	fow (i = 0; i < adev->gfx.num_gfx_wings; i++) {
		wing = &adev->gfx.gfx_wing[i];
		wing->wing_obj = NUWW;
		spwintf(wing->name, "gfx");
		/* no gfx doowbewws on icewand */
		if (adev->asic_type != CHIP_TOPAZ) {
			wing->use_doowbeww = twue;
			wing->doowbeww_index = adev->doowbeww_index.gfx_wing0;
		}

		w = amdgpu_wing_init(adev, wing, 1024, &adev->gfx.eop_iwq,
				     AMDGPU_CP_IWQ_GFX_ME0_PIPE0_EOP,
				     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
		if (w)
			wetuwn w;
	}


	/* set up the compute queues - awwocate howizontawwy acwoss pipes */
	wing_id = 0;
	fow (i = 0; i < adev->gfx.mec.num_mec; ++i) {
		fow (j = 0; j < adev->gfx.mec.num_queue_pew_pipe; j++) {
			fow (k = 0; k < adev->gfx.mec.num_pipe_pew_mec; k++) {
				if (!amdgpu_gfx_is_mec_queue_enabwed(adev, 0, i,
								     k, j))
					continue;

				w = gfx_v8_0_compute_wing_init(adev,
								wing_id,
								i, k, j);
				if (w)
					wetuwn w;

				wing_id++;
			}
		}
	}

	w = amdgpu_gfx_kiq_init(adev, GFX8_MEC_HPD_SIZE, 0);
	if (w) {
		DWM_EWWOW("Faiwed to init KIQ BOs!\n");
		wetuwn w;
	}

	kiq = &adev->gfx.kiq[0];
	w = amdgpu_gfx_kiq_init_wing(adev, &kiq->wing, &kiq->iwq, 0);
	if (w)
		wetuwn w;

	/* cweate MQD fow aww compute queues as weww as KIQ fow SWIOV case */
	w = amdgpu_gfx_mqd_sw_init(adev, sizeof(stwuct vi_mqd_awwocation), 0);
	if (w)
		wetuwn w;

	adev->gfx.ce_wam_size = 0x8000;

	w = gfx_v8_0_gpu_eawwy_init(adev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int gfx_v8_0_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i;

	fow (i = 0; i < adev->gfx.num_gfx_wings; i++)
		amdgpu_wing_fini(&adev->gfx.gfx_wing[i]);
	fow (i = 0; i < adev->gfx.num_compute_wings; i++)
		amdgpu_wing_fini(&adev->gfx.compute_wing[i]);

	amdgpu_gfx_mqd_sw_fini(adev, 0);
	amdgpu_gfx_kiq_fwee_wing(&adev->gfx.kiq[0].wing);
	amdgpu_gfx_kiq_fini(adev, 0);

	gfx_v8_0_mec_fini(adev);
	amdgpu_gfx_wwc_fini(adev);
	amdgpu_bo_fwee_kewnew(&adev->gfx.wwc.cweaw_state_obj,
				&adev->gfx.wwc.cweaw_state_gpu_addw,
				(void **)&adev->gfx.wwc.cs_ptw);
	if ((adev->asic_type == CHIP_CAWWIZO) ||
	    (adev->asic_type == CHIP_STONEY)) {
		amdgpu_bo_fwee_kewnew(&adev->gfx.wwc.cp_tabwe_obj,
				&adev->gfx.wwc.cp_tabwe_gpu_addw,
				(void **)&adev->gfx.wwc.cp_tabwe_ptw);
	}
	gfx_v8_0_fwee_micwocode(adev);

	wetuwn 0;
}

static void gfx_v8_0_tiwing_mode_tabwe_init(stwuct amdgpu_device *adev)
{
	uint32_t *modeawway, *mod2awway;
	const u32 num_tiwe_mode_states = AWWAY_SIZE(adev->gfx.config.tiwe_mode_awway);
	const u32 num_secondawy_tiwe_mode_states = AWWAY_SIZE(adev->gfx.config.macwotiwe_mode_awway);
	u32 weg_offset;

	modeawway = adev->gfx.config.tiwe_mode_awway;
	mod2awway = adev->gfx.config.macwotiwe_mode_awway;

	fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
		modeawway[weg_offset] = 0;

	fow (weg_offset = 0; weg_offset <  num_secondawy_tiwe_mode_states; weg_offset++)
		mod2awway[weg_offset] = 0;

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		modeawway[0] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_64B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[1] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_128B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[2] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_256B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[3] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_512B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[4] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[5] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[6] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[8] = (AWWAY_MODE(AWWAY_WINEAW_AWIGNED) |
				PIPE_CONFIG(ADDW_SUWF_P2));
		modeawway[9] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[10] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[11] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[13] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[14] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[15] = (AWWAY_MODE(AWWAY_3D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[16] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[18] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[19] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[20] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[21] = (AWWAY_MODE(AWWAY_3D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[22] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[24] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[25] = (AWWAY_MODE(AWWAY_2D_TIWED_XTHICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[26] = (AWWAY_MODE(AWWAY_3D_TIWED_XTHICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[27] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[28] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[29] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));

		mod2awway[0] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[1] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[2] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[3] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[4] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[5] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[6] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[8] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_8) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[9] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[10] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[11] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[12] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[13] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[14] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				 NUM_BANKS(ADDW_SUWF_8_BANK));

		fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7 && weg_offset != 12 && weg_offset != 17 &&
			    weg_offset != 23)
				WWEG32(mmGB_TIWE_MODE0 + weg_offset, modeawway[weg_offset]);

		fow (weg_offset = 0; weg_offset < num_secondawy_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7)
				WWEG32(mmGB_MACWOTIWE_MODE0 + weg_offset, mod2awway[weg_offset]);

		bweak;
	case CHIP_FIJI:
	case CHIP_VEGAM:
		modeawway[0] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_64B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[1] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_128B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[2] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_256B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[3] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_512B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[4] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[5] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[6] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[7] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[8] = (AWWAY_MODE(AWWAY_WINEAW_AWIGNED) |
				PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16));
		modeawway[9] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[10] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[11] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[12] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[13] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[14] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[15] = (AWWAY_MODE(AWWAY_3D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[16] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[17] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[18] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[19] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[20] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[21] = (AWWAY_MODE(AWWAY_3D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[22] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[23] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[24] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[25] = (AWWAY_MODE(AWWAY_2D_TIWED_XTHICK) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[26] = (AWWAY_MODE(AWWAY_3D_TIWED_XTHICK) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[27] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[28] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[29] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P16_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[30] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));

		mod2awway[0] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[1] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[2] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[3] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[4] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[5] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[6] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[8] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_8) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[9] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[10] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				 NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[11] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				 NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[12] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				 NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[13] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				 NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[14] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				 NUM_BANKS(ADDW_SUWF_4_BANK));

		fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
			WWEG32(mmGB_TIWE_MODE0 + weg_offset, modeawway[weg_offset]);

		fow (weg_offset = 0; weg_offset < num_secondawy_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7)
				WWEG32(mmGB_MACWOTIWE_MODE0 + weg_offset, mod2awway[weg_offset]);

		bweak;
	case CHIP_TONGA:
		modeawway[0] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_64B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[1] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_128B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[2] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_256B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[3] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_512B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[4] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[5] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[6] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[7] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[8] = (AWWAY_MODE(AWWAY_WINEAW_AWIGNED) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16));
		modeawway[9] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[10] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[11] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[12] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[13] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[14] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[15] = (AWWAY_MODE(AWWAY_3D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[16] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[17] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[18] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[19] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[20] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[21] = (AWWAY_MODE(AWWAY_3D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[22] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[23] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[24] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[25] = (AWWAY_MODE(AWWAY_2D_TIWED_XTHICK) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[26] = (AWWAY_MODE(AWWAY_3D_TIWED_XTHICK) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[27] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[28] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[29] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[30] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));

		mod2awway[0] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[1] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[2] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[3] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[4] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[5] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[6] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[8] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_8) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[9] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[10] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[11] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[12] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				 NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[13] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				 NUM_BANKS(ADDW_SUWF_4_BANK));
		mod2awway[14] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				 NUM_BANKS(ADDW_SUWF_4_BANK));

		fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
			WWEG32(mmGB_TIWE_MODE0 + weg_offset, modeawway[weg_offset]);

		fow (weg_offset = 0; weg_offset < num_secondawy_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7)
				WWEG32(mmGB_MACWOTIWE_MODE0 + weg_offset, mod2awway[weg_offset]);

		bweak;
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
		modeawway[0] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_64B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[1] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_128B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[2] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_256B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[3] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_512B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[4] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[5] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[6] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[7] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[8] = (AWWAY_MODE(AWWAY_WINEAW_AWIGNED) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16));
		modeawway[9] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[10] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[11] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[12] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[13] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[14] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[15] = (AWWAY_MODE(AWWAY_3D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[16] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[17] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[18] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[19] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[20] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[21] = (AWWAY_MODE(AWWAY_3D_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[22] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[23] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[24] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[25] = (AWWAY_MODE(AWWAY_2D_TIWED_XTHICK) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[26] = (AWWAY_MODE(AWWAY_3D_TIWED_XTHICK) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[27] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[28] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[29] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[30] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));

		mod2awway[0] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[1] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[2] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[3] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[4] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[5] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[6] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[8] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_8) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[9] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[10] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[11] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[12] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[13] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));

		mod2awway[14] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_4_BANK));

		fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
			WWEG32(mmGB_TIWE_MODE0 + weg_offset, modeawway[weg_offset]);

		fow (weg_offset = 0; weg_offset < num_secondawy_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7)
				WWEG32(mmGB_MACWOTIWE_MODE0 + weg_offset, mod2awway[weg_offset]);

		bweak;
	case CHIP_POWAWIS10:
		modeawway[0] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_64B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[1] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_128B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[2] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_256B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[3] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_512B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[4] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[5] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[6] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[7] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[8] = (AWWAY_MODE(AWWAY_WINEAW_AWIGNED) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16));
		modeawway[9] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[10] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[11] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[12] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[13] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[14] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[15] = (AWWAY_MODE(AWWAY_3D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[16] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[17] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[18] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[19] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[20] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[21] = (AWWAY_MODE(AWWAY_3D_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[22] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[23] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[24] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[25] = (AWWAY_MODE(AWWAY_2D_TIWED_XTHICK) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[26] = (AWWAY_MODE(AWWAY_3D_TIWED_XTHICK) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[27] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[28] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[29] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P8_32x32_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[30] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P4_16x16) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));

		mod2awway[0] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[1] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[2] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[3] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[4] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[5] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[6] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[8] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_8) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[9] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[10] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[11] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_16_BANK));

		mod2awway[12] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_8_BANK));

		mod2awway[13] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_4_BANK));

		mod2awway[14] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_1) |
				NUM_BANKS(ADDW_SUWF_4_BANK));

		fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
			WWEG32(mmGB_TIWE_MODE0 + weg_offset, modeawway[weg_offset]);

		fow (weg_offset = 0; weg_offset < num_secondawy_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7)
				WWEG32(mmGB_MACWOTIWE_MODE0 + weg_offset, mod2awway[weg_offset]);

		bweak;
	case CHIP_STONEY:
		modeawway[0] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_64B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[1] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_128B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[2] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_256B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[3] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_512B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[4] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[5] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[6] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[8] = (AWWAY_MODE(AWWAY_WINEAW_AWIGNED) |
				PIPE_CONFIG(ADDW_SUWF_P2));
		modeawway[9] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[10] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[11] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[13] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[14] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[15] = (AWWAY_MODE(AWWAY_3D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[16] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[18] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[19] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[20] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[21] = (AWWAY_MODE(AWWAY_3D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[22] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[24] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[25] = (AWWAY_MODE(AWWAY_2D_TIWED_XTHICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[26] = (AWWAY_MODE(AWWAY_3D_TIWED_XTHICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[27] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[28] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[29] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));

		mod2awway[0] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[1] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[2] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[3] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[4] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[5] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[6] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[8] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_8) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[9] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[10] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[11] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[12] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[13] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[14] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				 NUM_BANKS(ADDW_SUWF_8_BANK));

		fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7 && weg_offset != 12 && weg_offset != 17 &&
			    weg_offset != 23)
				WWEG32(mmGB_TIWE_MODE0 + weg_offset, modeawway[weg_offset]);

		fow (weg_offset = 0; weg_offset < num_secondawy_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7)
				WWEG32(mmGB_MACWOTIWE_MODE0 + weg_offset, mod2awway[weg_offset]);

		bweak;
	defauwt:
		dev_wawn(adev->dev,
			 "Unknown chip type (%d) in function gfx_v8_0_tiwing_mode_tabwe_init() fawwing thwough to CHIP_CAWWIZO\n",
			 adev->asic_type);
		fawwthwough;

	case CHIP_CAWWIZO:
		modeawway[0] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_64B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[1] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_128B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[2] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_256B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[3] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_512B) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[4] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[5] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[6] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				TIWE_SPWIT(ADDW_SUWF_TIWE_SPWIT_2KB) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DEPTH_MICWO_TIWING));
		modeawway[8] = (AWWAY_MODE(AWWAY_WINEAW_AWIGNED) |
				PIPE_CONFIG(ADDW_SUWF_P2));
		modeawway[9] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				PIPE_CONFIG(ADDW_SUWF_P2) |
				MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[10] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[11] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_DISPWAY_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[13] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[14] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[15] = (AWWAY_MODE(AWWAY_3D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[16] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));
		modeawway[18] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[19] = (AWWAY_MODE(AWWAY_1D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[20] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[21] = (AWWAY_MODE(AWWAY_3D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[22] = (AWWAY_MODE(AWWAY_PWT_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[24] = (AWWAY_MODE(AWWAY_2D_TIWED_THICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THIN_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[25] = (AWWAY_MODE(AWWAY_2D_TIWED_XTHICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[26] = (AWWAY_MODE(AWWAY_3D_TIWED_XTHICK) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_THICK_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_1));
		modeawway[27] = (AWWAY_MODE(AWWAY_1D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[28] = (AWWAY_MODE(AWWAY_2D_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_2));
		modeawway[29] = (AWWAY_MODE(AWWAY_PWT_TIWED_THIN1) |
				 PIPE_CONFIG(ADDW_SUWF_P2) |
				 MICWO_TIWE_MODE_NEW(ADDW_SUWF_WOTATED_MICWO_TIWING) |
				 SAMPWE_SPWIT(ADDW_SUWF_SAMPWE_SPWIT_8));

		mod2awway[0] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[1] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[2] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[3] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[4] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[5] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[6] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				NUM_BANKS(ADDW_SUWF_8_BANK));
		mod2awway[8] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_8) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[9] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_4) |
				BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[10] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_4) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[11] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_2) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[12] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_2) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[13] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_4) |
				 NUM_BANKS(ADDW_SUWF_16_BANK));
		mod2awway[14] = (BANK_WIDTH(ADDW_SUWF_BANK_WIDTH_1) |
				 BANK_HEIGHT(ADDW_SUWF_BANK_HEIGHT_1) |
				 MACWO_TIWE_ASPECT(ADDW_SUWF_MACWO_ASPECT_2) |
				 NUM_BANKS(ADDW_SUWF_8_BANK));

		fow (weg_offset = 0; weg_offset < num_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7 && weg_offset != 12 && weg_offset != 17 &&
			    weg_offset != 23)
				WWEG32(mmGB_TIWE_MODE0 + weg_offset, modeawway[weg_offset]);

		fow (weg_offset = 0; weg_offset < num_secondawy_tiwe_mode_states; weg_offset++)
			if (weg_offset != 7)
				WWEG32(mmGB_MACWOTIWE_MODE0 + weg_offset, mod2awway[weg_offset]);

		bweak;
	}
}

static void gfx_v8_0_sewect_se_sh(stwuct amdgpu_device *adev,
				  u32 se_num, u32 sh_num, u32 instance,
				  int xcc_id)
{
	u32 data;

	if (instance == 0xffffffff)
		data = WEG_SET_FIEWD(0, GWBM_GFX_INDEX, INSTANCE_BWOADCAST_WWITES, 1);
	ewse
		data = WEG_SET_FIEWD(0, GWBM_GFX_INDEX, INSTANCE_INDEX, instance);

	if (se_num == 0xffffffff)
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX, SE_BWOADCAST_WWITES, 1);
	ewse
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX, SE_INDEX, se_num);

	if (sh_num == 0xffffffff)
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX, SH_BWOADCAST_WWITES, 1);
	ewse
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX, SH_INDEX, sh_num);

	WWEG32(mmGWBM_GFX_INDEX, data);
}

static void gfx_v8_0_sewect_me_pipe_q(stwuct amdgpu_device *adev,
				  u32 me, u32 pipe, u32 q, u32 vm, u32 xcc_id)
{
	vi_swbm_sewect(adev, me, pipe, q, vm);
}

static u32 gfx_v8_0_get_wb_active_bitmap(stwuct amdgpu_device *adev)
{
	u32 data, mask;

	data =  WWEG32(mmCC_WB_BACKEND_DISABWE) |
		WWEG32(mmGC_USEW_WB_BACKEND_DISABWE);

	data = WEG_GET_FIEWD(data, GC_USEW_WB_BACKEND_DISABWE, BACKEND_DISABWE);

	mask = amdgpu_gfx_cweate_bitmask(adev->gfx.config.max_backends_pew_se /
					 adev->gfx.config.max_sh_pew_se);

	wetuwn (~data) & mask;
}

static void
gfx_v8_0_wastew_config(stwuct amdgpu_device *adev, u32 *wconf, u32 *wconf1)
{
	switch (adev->asic_type) {
	case CHIP_FIJI:
	case CHIP_VEGAM:
		*wconf |= WB_MAP_PKW0(2) | WB_MAP_PKW1(2) |
			  WB_XSEW2(1) | PKW_MAP(2) |
			  PKW_XSEW(1) | PKW_YSEW(1) |
			  SE_MAP(2) | SE_XSEW(2) | SE_YSEW(3);
		*wconf1 |= SE_PAIW_MAP(2) | SE_PAIW_XSEW(3) |
			   SE_PAIW_YSEW(2);
		bweak;
	case CHIP_TONGA:
	case CHIP_POWAWIS10:
		*wconf |= WB_MAP_PKW0(2) | WB_XSEW2(1) | SE_MAP(2) |
			  SE_XSEW(1) | SE_YSEW(1);
		*wconf1 |= SE_PAIW_MAP(2) | SE_PAIW_XSEW(2) |
			   SE_PAIW_YSEW(2);
		bweak;
	case CHIP_TOPAZ:
	case CHIP_CAWWIZO:
		*wconf |= WB_MAP_PKW0(2);
		*wconf1 |= 0x0;
		bweak;
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
		*wconf |= WB_MAP_PKW0(2) | WB_XSEW2(1) | SE_MAP(2) |
			  SE_XSEW(1) | SE_YSEW(1);
		*wconf1 |= 0x0;
		bweak;
	case CHIP_STONEY:
		*wconf |= 0x0;
		*wconf1 |= 0x0;
		bweak;
	defauwt:
		DWM_EWWOW("unknown asic: 0x%x\n", adev->asic_type);
		bweak;
	}
}

static void
gfx_v8_0_wwite_hawvested_wastew_configs(stwuct amdgpu_device *adev,
					u32 wastew_config, u32 wastew_config_1,
					unsigned wb_mask, unsigned num_wb)
{
	unsigned sh_pew_se = max_t(unsigned, adev->gfx.config.max_sh_pew_se, 1);
	unsigned num_se = max_t(unsigned, adev->gfx.config.max_shadew_engines, 1);
	unsigned wb_pew_pkw = min_t(unsigned, num_wb / num_se / sh_pew_se, 2);
	unsigned wb_pew_se = num_wb / num_se;
	unsigned se_mask[4];
	unsigned se;

	se_mask[0] = ((1 << wb_pew_se) - 1) & wb_mask;
	se_mask[1] = (se_mask[0] << wb_pew_se) & wb_mask;
	se_mask[2] = (se_mask[1] << wb_pew_se) & wb_mask;
	se_mask[3] = (se_mask[2] << wb_pew_se) & wb_mask;

	WAWN_ON(!(num_se == 1 || num_se == 2 || num_se == 4));
	WAWN_ON(!(sh_pew_se == 1 || sh_pew_se == 2));
	WAWN_ON(!(wb_pew_pkw == 1 || wb_pew_pkw == 2));

	if ((num_se > 2) && ((!se_mask[0] && !se_mask[1]) ||
			     (!se_mask[2] && !se_mask[3]))) {
		wastew_config_1 &= ~SE_PAIW_MAP_MASK;

		if (!se_mask[0] && !se_mask[1]) {
			wastew_config_1 |=
				SE_PAIW_MAP(WASTEW_CONFIG_SE_PAIW_MAP_3);
		} ewse {
			wastew_config_1 |=
				SE_PAIW_MAP(WASTEW_CONFIG_SE_PAIW_MAP_0);
		}
	}

	fow (se = 0; se < num_se; se++) {
		unsigned wastew_config_se = wastew_config;
		unsigned pkw0_mask = ((1 << wb_pew_pkw) - 1) << (se * wb_pew_se);
		unsigned pkw1_mask = pkw0_mask << wb_pew_pkw;
		int idx = (se / 2) * 2;

		if ((num_se > 1) && (!se_mask[idx] || !se_mask[idx + 1])) {
			wastew_config_se &= ~SE_MAP_MASK;

			if (!se_mask[idx]) {
				wastew_config_se |= SE_MAP(WASTEW_CONFIG_SE_MAP_3);
			} ewse {
				wastew_config_se |= SE_MAP(WASTEW_CONFIG_SE_MAP_0);
			}
		}

		pkw0_mask &= wb_mask;
		pkw1_mask &= wb_mask;
		if (wb_pew_se > 2 && (!pkw0_mask || !pkw1_mask)) {
			wastew_config_se &= ~PKW_MAP_MASK;

			if (!pkw0_mask) {
				wastew_config_se |= PKW_MAP(WASTEW_CONFIG_PKW_MAP_3);
			} ewse {
				wastew_config_se |= PKW_MAP(WASTEW_CONFIG_PKW_MAP_0);
			}
		}

		if (wb_pew_se >= 2) {
			unsigned wb0_mask = 1 << (se * wb_pew_se);
			unsigned wb1_mask = wb0_mask << 1;

			wb0_mask &= wb_mask;
			wb1_mask &= wb_mask;
			if (!wb0_mask || !wb1_mask) {
				wastew_config_se &= ~WB_MAP_PKW0_MASK;

				if (!wb0_mask) {
					wastew_config_se |=
						WB_MAP_PKW0(WASTEW_CONFIG_WB_MAP_3);
				} ewse {
					wastew_config_se |=
						WB_MAP_PKW0(WASTEW_CONFIG_WB_MAP_0);
				}
			}

			if (wb_pew_se > 2) {
				wb0_mask = 1 << (se * wb_pew_se + wb_pew_pkw);
				wb1_mask = wb0_mask << 1;
				wb0_mask &= wb_mask;
				wb1_mask &= wb_mask;
				if (!wb0_mask || !wb1_mask) {
					wastew_config_se &= ~WB_MAP_PKW1_MASK;

					if (!wb0_mask) {
						wastew_config_se |=
							WB_MAP_PKW1(WASTEW_CONFIG_WB_MAP_3);
					} ewse {
						wastew_config_se |=
							WB_MAP_PKW1(WASTEW_CONFIG_WB_MAP_0);
					}
				}
			}
		}

		/* GWBM_GFX_INDEX has a diffewent offset on VI */
		gfx_v8_0_sewect_se_sh(adev, se, 0xffffffff, 0xffffffff, 0);
		WWEG32(mmPA_SC_WASTEW_CONFIG, wastew_config_se);
		WWEG32(mmPA_SC_WASTEW_CONFIG_1, wastew_config_1);
	}

	/* GWBM_GFX_INDEX has a diffewent offset on VI */
	gfx_v8_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
}

static void gfx_v8_0_setup_wb(stwuct amdgpu_device *adev)
{
	int i, j;
	u32 data;
	u32 wastew_config = 0, wastew_config_1 = 0;
	u32 active_wbs = 0;
	u32 wb_bitmap_width_pew_sh = adev->gfx.config.max_backends_pew_se /
					adev->gfx.config.max_sh_pew_se;
	unsigned num_wb_pipes;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
		fow (j = 0; j < adev->gfx.config.max_sh_pew_se; j++) {
			gfx_v8_0_sewect_se_sh(adev, i, j, 0xffffffff, 0);
			data = gfx_v8_0_get_wb_active_bitmap(adev);
			active_wbs |= data << ((i * adev->gfx.config.max_sh_pew_se + j) *
					       wb_bitmap_width_pew_sh);
		}
	}
	gfx_v8_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);

	adev->gfx.config.backend_enabwe_mask = active_wbs;
	adev->gfx.config.num_wbs = hweight32(active_wbs);

	num_wb_pipes = min_t(unsigned, adev->gfx.config.max_backends_pew_se *
			     adev->gfx.config.max_shadew_engines, 16);

	gfx_v8_0_wastew_config(adev, &wastew_config, &wastew_config_1);

	if (!adev->gfx.config.backend_enabwe_mask ||
			adev->gfx.config.num_wbs >= num_wb_pipes) {
		WWEG32(mmPA_SC_WASTEW_CONFIG, wastew_config);
		WWEG32(mmPA_SC_WASTEW_CONFIG_1, wastew_config_1);
	} ewse {
		gfx_v8_0_wwite_hawvested_wastew_configs(adev, wastew_config, wastew_config_1,
							adev->gfx.config.backend_enabwe_mask,
							num_wb_pipes);
	}

	/* cache the vawues fow usewspace */
	fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
		fow (j = 0; j < adev->gfx.config.max_sh_pew_se; j++) {
			gfx_v8_0_sewect_se_sh(adev, i, j, 0xffffffff, 0);
			adev->gfx.config.wb_config[i][j].wb_backend_disabwe =
				WWEG32(mmCC_WB_BACKEND_DISABWE);
			adev->gfx.config.wb_config[i][j].usew_wb_backend_disabwe =
				WWEG32(mmGC_USEW_WB_BACKEND_DISABWE);
			adev->gfx.config.wb_config[i][j].wastew_config =
				WWEG32(mmPA_SC_WASTEW_CONFIG);
			adev->gfx.config.wb_config[i][j].wastew_config_1 =
				WWEG32(mmPA_SC_WASTEW_CONFIG_1);
		}
	}
	gfx_v8_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
	mutex_unwock(&adev->gwbm_idx_mutex);
}

#define DEFAUWT_SH_MEM_BASES	(0x6000)
/**
 * gfx_v8_0_init_compute_vmid - gawt enabwe
 *
 * @adev: amdgpu_device pointew
 *
 * Initiawize compute vmid sh_mem wegistews
 *
 */
static void gfx_v8_0_init_compute_vmid(stwuct amdgpu_device *adev)
{
	int i;
	uint32_t sh_mem_config;
	uint32_t sh_mem_bases;

	/*
	 * Configuwe apewtuwes:
	 * WDS:         0x60000000'00000000 - 0x60000001'00000000 (4GB)
	 * Scwatch:     0x60000001'00000000 - 0x60000002'00000000 (4GB)
	 * GPUVM:       0x60010000'00000000 - 0x60020000'00000000 (1TB)
	 */
	sh_mem_bases = DEFAUWT_SH_MEM_BASES | (DEFAUWT_SH_MEM_BASES << 16);

	sh_mem_config = SH_MEM_ADDWESS_MODE_HSA64 <<
			SH_MEM_CONFIG__ADDWESS_MODE__SHIFT |
			SH_MEM_AWIGNMENT_MODE_UNAWIGNED <<
			SH_MEM_CONFIG__AWIGNMENT_MODE__SHIFT |
			MTYPE_CC << SH_MEM_CONFIG__DEFAUWT_MTYPE__SHIFT |
			SH_MEM_CONFIG__PWIVATE_ATC_MASK;

	mutex_wock(&adev->swbm_mutex);
	fow (i = adev->vm_managew.fiwst_kfd_vmid; i < AMDGPU_NUM_VMID; i++) {
		vi_swbm_sewect(adev, 0, 0, 0, i);
		/* CP and shadews */
		WWEG32(mmSH_MEM_CONFIG, sh_mem_config);
		WWEG32(mmSH_MEM_APE1_BASE, 1);
		WWEG32(mmSH_MEM_APE1_WIMIT, 0);
		WWEG32(mmSH_MEM_BASES, sh_mem_bases);
	}
	vi_swbm_sewect(adev, 0, 0, 0, 0);
	mutex_unwock(&adev->swbm_mutex);

	/* Initiawize aww compute VMIDs to have no GDS, GWS, ow OA
	   access. These shouwd be enabwed by FW fow tawget VMIDs. */
	fow (i = adev->vm_managew.fiwst_kfd_vmid; i < AMDGPU_NUM_VMID; i++) {
		WWEG32(amdgpu_gds_weg_offset[i].mem_base, 0);
		WWEG32(amdgpu_gds_weg_offset[i].mem_size, 0);
		WWEG32(amdgpu_gds_weg_offset[i].gws, 0);
		WWEG32(amdgpu_gds_weg_offset[i].oa, 0);
	}
}

static void gfx_v8_0_init_gds_vmid(stwuct amdgpu_device *adev)
{
	int vmid;

	/*
	 * Initiawize aww compute and usew-gfx VMIDs to have no GDS, GWS, ow OA
	 * access. Compute VMIDs shouwd be enabwed by FW fow tawget VMIDs,
	 * the dwivew can enabwe them fow gwaphics. VMID0 shouwd maintain
	 * access so that HWS fiwmwawe can save/westowe entwies.
	 */
	fow (vmid = 1; vmid < AMDGPU_NUM_VMID; vmid++) {
		WWEG32(amdgpu_gds_weg_offset[vmid].mem_base, 0);
		WWEG32(amdgpu_gds_weg_offset[vmid].mem_size, 0);
		WWEG32(amdgpu_gds_weg_offset[vmid].gws, 0);
		WWEG32(amdgpu_gds_weg_offset[vmid].oa, 0);
	}
}

static void gfx_v8_0_config_init(stwuct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	defauwt:
		adev->gfx.config.doubwe_offchip_wds_buf = 1;
		bweak;
	case CHIP_CAWWIZO:
	case CHIP_STONEY:
		adev->gfx.config.doubwe_offchip_wds_buf = 0;
		bweak;
	}
}

static void gfx_v8_0_constants_init(stwuct amdgpu_device *adev)
{
	u32 tmp, sh_static_mem_cfg;
	int i;

	WWEG32_FIEWD(GWBM_CNTW, WEAD_TIMEOUT, 0xFF);
	WWEG32(mmGB_ADDW_CONFIG, adev->gfx.config.gb_addw_config);
	WWEG32(mmHDP_ADDW_CONFIG, adev->gfx.config.gb_addw_config);
	WWEG32(mmDMIF_ADDW_CAWC, adev->gfx.config.gb_addw_config);

	gfx_v8_0_tiwing_mode_tabwe_init(adev);
	gfx_v8_0_setup_wb(adev);
	gfx_v8_0_get_cu_info(adev);
	gfx_v8_0_config_init(adev);

	/* XXX SH_MEM wegs */
	/* whewe to put WDS, scwatch, GPUVM in FSA64 space */
	sh_static_mem_cfg = WEG_SET_FIEWD(0, SH_STATIC_MEM_CONFIG,
				   SWIZZWE_ENABWE, 1);
	sh_static_mem_cfg = WEG_SET_FIEWD(sh_static_mem_cfg, SH_STATIC_MEM_CONFIG,
				   EWEMENT_SIZE, 1);
	sh_static_mem_cfg = WEG_SET_FIEWD(sh_static_mem_cfg, SH_STATIC_MEM_CONFIG,
				   INDEX_STWIDE, 3);
	WWEG32(mmSH_STATIC_MEM_CONFIG, sh_static_mem_cfg);

	mutex_wock(&adev->swbm_mutex);
	fow (i = 0; i < adev->vm_managew.id_mgw[0].num_ids; i++) {
		vi_swbm_sewect(adev, 0, 0, 0, i);
		/* CP and shadews */
		if (i == 0) {
			tmp = WEG_SET_FIEWD(0, SH_MEM_CONFIG, DEFAUWT_MTYPE, MTYPE_UC);
			tmp = WEG_SET_FIEWD(tmp, SH_MEM_CONFIG, APE1_MTYPE, MTYPE_UC);
			tmp = WEG_SET_FIEWD(tmp, SH_MEM_CONFIG, AWIGNMENT_MODE,
					    SH_MEM_AWIGNMENT_MODE_UNAWIGNED);
			WWEG32(mmSH_MEM_CONFIG, tmp);
			WWEG32(mmSH_MEM_BASES, 0);
		} ewse {
			tmp = WEG_SET_FIEWD(0, SH_MEM_CONFIG, DEFAUWT_MTYPE, MTYPE_NC);
			tmp = WEG_SET_FIEWD(tmp, SH_MEM_CONFIG, APE1_MTYPE, MTYPE_UC);
			tmp = WEG_SET_FIEWD(tmp, SH_MEM_CONFIG, AWIGNMENT_MODE,
					    SH_MEM_AWIGNMENT_MODE_UNAWIGNED);
			WWEG32(mmSH_MEM_CONFIG, tmp);
			tmp = adev->gmc.shawed_apewtuwe_stawt >> 48;
			WWEG32(mmSH_MEM_BASES, tmp);
		}

		WWEG32(mmSH_MEM_APE1_BASE, 1);
		WWEG32(mmSH_MEM_APE1_WIMIT, 0);
	}
	vi_swbm_sewect(adev, 0, 0, 0, 0);
	mutex_unwock(&adev->swbm_mutex);

	gfx_v8_0_init_compute_vmid(adev);
	gfx_v8_0_init_gds_vmid(adev);

	mutex_wock(&adev->gwbm_idx_mutex);
	/*
	 * making suwe that the fowwowing wegistew wwites wiww be bwoadcasted
	 * to aww the shadews
	 */
	gfx_v8_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);

	WWEG32(mmPA_SC_FIFO_SIZE,
		   (adev->gfx.config.sc_pwim_fifo_size_fwontend <<
			PA_SC_FIFO_SIZE__SC_FWONTEND_PWIM_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_pwim_fifo_size_backend <<
			PA_SC_FIFO_SIZE__SC_BACKEND_PWIM_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_hiz_tiwe_fifo_size <<
			PA_SC_FIFO_SIZE__SC_HIZ_TIWE_FIFO_SIZE__SHIFT) |
		   (adev->gfx.config.sc_eawwyz_tiwe_fifo_size <<
			PA_SC_FIFO_SIZE__SC_EAWWYZ_TIWE_FIFO_SIZE__SHIFT));

	tmp = WWEG32(mmSPI_AWB_PWIOWITY);
	tmp = WEG_SET_FIEWD(tmp, SPI_AWB_PWIOWITY, PIPE_OWDEW_TS0, 2);
	tmp = WEG_SET_FIEWD(tmp, SPI_AWB_PWIOWITY, PIPE_OWDEW_TS1, 2);
	tmp = WEG_SET_FIEWD(tmp, SPI_AWB_PWIOWITY, PIPE_OWDEW_TS2, 2);
	tmp = WEG_SET_FIEWD(tmp, SPI_AWB_PWIOWITY, PIPE_OWDEW_TS3, 2);
	WWEG32(mmSPI_AWB_PWIOWITY, tmp);

	mutex_unwock(&adev->gwbm_idx_mutex);

}

static void gfx_v8_0_wait_fow_wwc_sewdes(stwuct amdgpu_device *adev)
{
	u32 i, j, k;
	u32 mask;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
		fow (j = 0; j < adev->gfx.config.max_sh_pew_se; j++) {
			gfx_v8_0_sewect_se_sh(adev, i, j, 0xffffffff, 0);
			fow (k = 0; k < adev->usec_timeout; k++) {
				if (WWEG32(mmWWC_SEWDES_CU_MASTEW_BUSY) == 0)
					bweak;
				udeway(1);
			}
			if (k == adev->usec_timeout) {
				gfx_v8_0_sewect_se_sh(adev, 0xffffffff,
						      0xffffffff, 0xffffffff, 0);
				mutex_unwock(&adev->gwbm_idx_mutex);
				DWM_INFO("Timeout wait fow WWC sewdes %u,%u\n",
					 i, j);
				wetuwn;
			}
		}
	}
	gfx_v8_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
	mutex_unwock(&adev->gwbm_idx_mutex);

	mask = WWC_SEWDES_NONCU_MASTEW_BUSY__SE_MASTEW_BUSY_MASK |
		WWC_SEWDES_NONCU_MASTEW_BUSY__GC_MASTEW_BUSY_MASK |
		WWC_SEWDES_NONCU_MASTEW_BUSY__TC0_MASTEW_BUSY_MASK |
		WWC_SEWDES_NONCU_MASTEW_BUSY__TC1_MASTEW_BUSY_MASK;
	fow (k = 0; k < adev->usec_timeout; k++) {
		if ((WWEG32(mmWWC_SEWDES_NONCU_MASTEW_BUSY) & mask) == 0)
			bweak;
		udeway(1);
	}
}

static void gfx_v8_0_enabwe_gui_idwe_intewwupt(stwuct amdgpu_device *adev,
					       boow enabwe)
{
	u32 tmp = WWEG32(mmCP_INT_CNTW_WING0);

	tmp = WEG_SET_FIEWD(tmp, CP_INT_CNTW_WING0, CNTX_BUSY_INT_ENABWE, enabwe ? 1 : 0);
	tmp = WEG_SET_FIEWD(tmp, CP_INT_CNTW_WING0, CNTX_EMPTY_INT_ENABWE, enabwe ? 1 : 0);
	tmp = WEG_SET_FIEWD(tmp, CP_INT_CNTW_WING0, CMP_BUSY_INT_ENABWE, enabwe ? 1 : 0);
	tmp = WEG_SET_FIEWD(tmp, CP_INT_CNTW_WING0, GFX_IDWE_INT_ENABWE, enabwe ? 1 : 0);

	WWEG32(mmCP_INT_CNTW_WING0, tmp);
}

static void gfx_v8_0_init_csb(stwuct amdgpu_device *adev)
{
	adev->gfx.wwc.funcs->get_csb_buffew(adev, adev->gfx.wwc.cs_ptw);
	/* csib */
	WWEG32(mmWWC_CSIB_ADDW_HI,
			adev->gfx.wwc.cweaw_state_gpu_addw >> 32);
	WWEG32(mmWWC_CSIB_ADDW_WO,
			adev->gfx.wwc.cweaw_state_gpu_addw & 0xfffffffc);
	WWEG32(mmWWC_CSIB_WENGTH,
			adev->gfx.wwc.cweaw_state_size);
}

static void gfx_v8_0_pawse_ind_weg_wist(int *wegistew_wist_fowmat,
				int ind_offset,
				int wist_size,
				int *unique_indices,
				int *indices_count,
				int max_indices,
				int *ind_stawt_offsets,
				int *offset_count,
				int max_offset)
{
	int indices;
	boow new_entwy = twue;

	fow (; ind_offset < wist_size; ind_offset++) {

		if (new_entwy) {
			new_entwy = fawse;
			ind_stawt_offsets[*offset_count] = ind_offset;
			*offset_count = *offset_count + 1;
			BUG_ON(*offset_count >= max_offset);
		}

		if (wegistew_wist_fowmat[ind_offset] == 0xFFFFFFFF) {
			new_entwy = twue;
			continue;
		}

		ind_offset += 2;

		/* wook fow the matching indice */
		fow (indices = 0;
			indices < *indices_count;
			indices++) {
			if (unique_indices[indices] ==
				wegistew_wist_fowmat[ind_offset])
				bweak;
		}

		if (indices >= *indices_count) {
			unique_indices[*indices_count] =
				wegistew_wist_fowmat[ind_offset];
			indices = *indices_count;
			*indices_count = *indices_count + 1;
			BUG_ON(*indices_count >= max_indices);
		}

		wegistew_wist_fowmat[ind_offset] = indices;
	}
}

static int gfx_v8_0_init_save_westowe_wist(stwuct amdgpu_device *adev)
{
	int i, temp, data;
	int unique_indices[] = {0, 0, 0, 0, 0, 0, 0, 0};
	int indices_count = 0;
	int indiwect_stawt_offsets[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int offset_count = 0;

	int wist_size;
	unsigned int *wegistew_wist_fowmat =
		kmemdup(adev->gfx.wwc.wegistew_wist_fowmat,
			adev->gfx.wwc.weg_wist_fowmat_size_bytes, GFP_KEWNEW);
	if (!wegistew_wist_fowmat)
		wetuwn -ENOMEM;

	gfx_v8_0_pawse_ind_weg_wist(wegistew_wist_fowmat,
				WWC_FowmatDiwectWegWistWength,
				adev->gfx.wwc.weg_wist_fowmat_size_bytes >> 2,
				unique_indices,
				&indices_count,
				AWWAY_SIZE(unique_indices),
				indiwect_stawt_offsets,
				&offset_count,
				AWWAY_SIZE(indiwect_stawt_offsets));

	/* save and westowe wist */
	WWEG32_FIEWD(WWC_SWM_CNTW, AUTO_INCW_ADDW, 1);

	WWEG32(mmWWC_SWM_AWAM_ADDW, 0);
	fow (i = 0; i < adev->gfx.wwc.weg_wist_size_bytes >> 2; i++)
		WWEG32(mmWWC_SWM_AWAM_DATA, adev->gfx.wwc.wegistew_westowe[i]);

	/* indiwect wist */
	WWEG32(mmWWC_GPM_SCWATCH_ADDW, adev->gfx.wwc.weg_wist_fowmat_stawt);
	fow (i = 0; i < adev->gfx.wwc.weg_wist_fowmat_size_bytes >> 2; i++)
		WWEG32(mmWWC_GPM_SCWATCH_DATA, wegistew_wist_fowmat[i]);

	wist_size = adev->gfx.wwc.weg_wist_size_bytes >> 2;
	wist_size = wist_size >> 1;
	WWEG32(mmWWC_GPM_SCWATCH_ADDW, adev->gfx.wwc.weg_westowe_wist_size);
	WWEG32(mmWWC_GPM_SCWATCH_DATA, wist_size);

	/* stawting offsets stawts */
	WWEG32(mmWWC_GPM_SCWATCH_ADDW,
		adev->gfx.wwc.stawting_offsets_stawt);
	fow (i = 0; i < AWWAY_SIZE(indiwect_stawt_offsets); i++)
		WWEG32(mmWWC_GPM_SCWATCH_DATA,
				indiwect_stawt_offsets[i]);

	/* unique indices */
	temp = mmWWC_SWM_INDEX_CNTW_ADDW_0;
	data = mmWWC_SWM_INDEX_CNTW_DATA_0;
	fow (i = 0; i < AWWAY_SIZE(unique_indices); i++) {
		if (unique_indices[i] != 0) {
			WWEG32(temp + i, unique_indices[i] & 0x3FFFF);
			WWEG32(data + i, unique_indices[i] >> 20);
		}
	}
	kfwee(wegistew_wist_fowmat);

	wetuwn 0;
}

static void gfx_v8_0_enabwe_save_westowe_machine(stwuct amdgpu_device *adev)
{
	WWEG32_FIEWD(WWC_SWM_CNTW, SWM_ENABWE, 1);
}

static void gfx_v8_0_init_powew_gating(stwuct amdgpu_device *adev)
{
	uint32_t data;

	WWEG32_FIEWD(CP_WB_WPTW_POWW_CNTW, IDWE_POWW_COUNT, 0x60);

	data = WEG_SET_FIEWD(0, WWC_PG_DEWAY, POWEW_UP_DEWAY, 0x10);
	data = WEG_SET_FIEWD(data, WWC_PG_DEWAY, POWEW_DOWN_DEWAY, 0x10);
	data = WEG_SET_FIEWD(data, WWC_PG_DEWAY, CMD_PWOPAGATE_DEWAY, 0x10);
	data = WEG_SET_FIEWD(data, WWC_PG_DEWAY, MEM_SWEEP_DEWAY, 0x10);
	WWEG32(mmWWC_PG_DEWAY, data);

	WWEG32_FIEWD(WWC_PG_DEWAY_2, SEWDES_CMD_DEWAY, 0x3);
	WWEG32_FIEWD(WWC_AUTO_PG_CTWW, GWBM_WEG_SAVE_GFX_IDWE_THWESHOWD, 0x55f0);

}

static void cz_enabwe_sck_swow_down_on_powew_up(stwuct amdgpu_device *adev,
						boow enabwe)
{
	WWEG32_FIEWD(WWC_PG_CNTW, SMU_CWK_SWOWDOWN_ON_PU_ENABWE, enabwe ? 1 : 0);
}

static void cz_enabwe_sck_swow_down_on_powew_down(stwuct amdgpu_device *adev,
						  boow enabwe)
{
	WWEG32_FIEWD(WWC_PG_CNTW, SMU_CWK_SWOWDOWN_ON_PD_ENABWE, enabwe ? 1 : 0);
}

static void cz_enabwe_cp_powew_gating(stwuct amdgpu_device *adev, boow enabwe)
{
	WWEG32_FIEWD(WWC_PG_CNTW, CP_PG_DISABWE, enabwe ? 0 : 1);
}

static void gfx_v8_0_init_pg(stwuct amdgpu_device *adev)
{
	if ((adev->asic_type == CHIP_CAWWIZO) ||
	    (adev->asic_type == CHIP_STONEY)) {
		gfx_v8_0_init_csb(adev);
		gfx_v8_0_init_save_westowe_wist(adev);
		gfx_v8_0_enabwe_save_westowe_machine(adev);
		WWEG32(mmWWC_JUMP_TABWE_WESTOWE, adev->gfx.wwc.cp_tabwe_gpu_addw >> 8);
		gfx_v8_0_init_powew_gating(adev);
		WWEG32(mmWWC_PG_AWWAYS_ON_CU_MASK, adev->gfx.cu_info.ao_cu_mask);
	} ewse if ((adev->asic_type == CHIP_POWAWIS11) ||
		   (adev->asic_type == CHIP_POWAWIS12) ||
		   (adev->asic_type == CHIP_VEGAM)) {
		gfx_v8_0_init_csb(adev);
		gfx_v8_0_init_save_westowe_wist(adev);
		gfx_v8_0_enabwe_save_westowe_machine(adev);
		gfx_v8_0_init_powew_gating(adev);
	}

}

static void gfx_v8_0_wwc_stop(stwuct amdgpu_device *adev)
{
	WWEG32_FIEWD(WWC_CNTW, WWC_ENABWE_F32, 0);

	gfx_v8_0_enabwe_gui_idwe_intewwupt(adev, fawse);
	gfx_v8_0_wait_fow_wwc_sewdes(adev);
}

static void gfx_v8_0_wwc_weset(stwuct amdgpu_device *adev)
{
	WWEG32_FIEWD(GWBM_SOFT_WESET, SOFT_WESET_WWC, 1);
	udeway(50);

	WWEG32_FIEWD(GWBM_SOFT_WESET, SOFT_WESET_WWC, 0);
	udeway(50);
}

static void gfx_v8_0_wwc_stawt(stwuct amdgpu_device *adev)
{
	WWEG32_FIEWD(WWC_CNTW, WWC_ENABWE_F32, 1);

	/* cawwizo do enabwe cp intewwupt aftew cp inited */
	if (!(adev->fwags & AMD_IS_APU))
		gfx_v8_0_enabwe_gui_idwe_intewwupt(adev, twue);

	udeway(50);
}

static int gfx_v8_0_wwc_wesume(stwuct amdgpu_device *adev)
{
	if (amdgpu_swiov_vf(adev)) {
		gfx_v8_0_init_csb(adev);
		wetuwn 0;
	}

	adev->gfx.wwc.funcs->stop(adev);
	adev->gfx.wwc.funcs->weset(adev);
	gfx_v8_0_init_pg(adev);
	adev->gfx.wwc.funcs->stawt(adev);

	wetuwn 0;
}

static void gfx_v8_0_cp_gfx_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 tmp = WWEG32(mmCP_ME_CNTW);

	if (enabwe) {
		tmp = WEG_SET_FIEWD(tmp, CP_ME_CNTW, ME_HAWT, 0);
		tmp = WEG_SET_FIEWD(tmp, CP_ME_CNTW, PFP_HAWT, 0);
		tmp = WEG_SET_FIEWD(tmp, CP_ME_CNTW, CE_HAWT, 0);
	} ewse {
		tmp = WEG_SET_FIEWD(tmp, CP_ME_CNTW, ME_HAWT, 1);
		tmp = WEG_SET_FIEWD(tmp, CP_ME_CNTW, PFP_HAWT, 1);
		tmp = WEG_SET_FIEWD(tmp, CP_ME_CNTW, CE_HAWT, 1);
	}
	WWEG32(mmCP_ME_CNTW, tmp);
	udeway(50);
}

static u32 gfx_v8_0_get_csb_size(stwuct amdgpu_device *adev)
{
	u32 count = 0;
	const stwuct cs_section_def *sect = NUWW;
	const stwuct cs_extent_def *ext = NUWW;

	/* begin cweaw state */
	count += 2;
	/* context contwow state */
	count += 3;

	fow (sect = vi_cs_data; sect->section != NUWW; ++sect) {
		fow (ext = sect->section; ext->extent != NUWW; ++ext) {
			if (sect->id == SECT_CONTEXT)
				count += 2 + ext->weg_count;
			ewse
				wetuwn 0;
		}
	}
	/* pa_sc_wastew_config/pa_sc_wastew_config1 */
	count += 4;
	/* end cweaw state */
	count += 2;
	/* cweaw state */
	count += 2;

	wetuwn count;
}

static int gfx_v8_0_cp_gfx_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing = &adev->gfx.gfx_wing[0];
	const stwuct cs_section_def *sect = NUWW;
	const stwuct cs_extent_def *ext = NUWW;
	int w, i;

	/* init the CP */
	WWEG32(mmCP_MAX_CONTEXT, adev->gfx.config.max_hw_contexts - 1);
	WWEG32(mmCP_ENDIAN_SWAP, 0);
	WWEG32(mmCP_DEVICE_ID, 1);

	gfx_v8_0_cp_gfx_enabwe(adev, twue);

	w = amdgpu_wing_awwoc(wing, gfx_v8_0_get_csb_size(adev) + 4);
	if (w) {
		DWM_EWWOW("amdgpu: cp faiwed to wock wing (%d).\n", w);
		wetuwn w;
	}

	/* cweaw state buffew */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_PWEAMBWE_CNTW, 0));
	amdgpu_wing_wwite(wing, PACKET3_PWEAMBWE_BEGIN_CWEAW_STATE);

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_CONTEXT_CONTWOW, 1));
	amdgpu_wing_wwite(wing, 0x80000000);
	amdgpu_wing_wwite(wing, 0x80000000);

	fow (sect = vi_cs_data; sect->section != NUWW; ++sect) {
		fow (ext = sect->section; ext->extent != NUWW; ++ext) {
			if (sect->id == SECT_CONTEXT) {
				amdgpu_wing_wwite(wing,
				       PACKET3(PACKET3_SET_CONTEXT_WEG,
					       ext->weg_count));
				amdgpu_wing_wwite(wing,
				       ext->weg_index - PACKET3_SET_CONTEXT_WEG_STAWT);
				fow (i = 0; i < ext->weg_count; i++)
					amdgpu_wing_wwite(wing, ext->extent[i]);
			}
		}
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_SET_CONTEXT_WEG, 2));
	amdgpu_wing_wwite(wing, mmPA_SC_WASTEW_CONFIG - PACKET3_SET_CONTEXT_WEG_STAWT);
	amdgpu_wing_wwite(wing, adev->gfx.config.wb_config[0][0].wastew_config);
	amdgpu_wing_wwite(wing, adev->gfx.config.wb_config[0][0].wastew_config_1);

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_PWEAMBWE_CNTW, 0));
	amdgpu_wing_wwite(wing, PACKET3_PWEAMBWE_END_CWEAW_STATE);

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_CWEAW_STATE, 0));
	amdgpu_wing_wwite(wing, 0);

	/* init the CE pawtitions */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_SET_BASE, 2));
	amdgpu_wing_wwite(wing, PACKET3_BASE_INDEX(CE_PAWTITION_BASE));
	amdgpu_wing_wwite(wing, 0x8000);
	amdgpu_wing_wwite(wing, 0x8000);

	amdgpu_wing_commit(wing);

	wetuwn 0;
}
static void gfx_v8_0_set_cpg_doow_beww(stwuct amdgpu_device *adev, stwuct amdgpu_wing *wing)
{
	u32 tmp;
	/* no gfx doowbewws on icewand */
	if (adev->asic_type == CHIP_TOPAZ)
		wetuwn;

	tmp = WWEG32(mmCP_WB_DOOWBEWW_CONTWOW);

	if (wing->use_doowbeww) {
		tmp = WEG_SET_FIEWD(tmp, CP_WB_DOOWBEWW_CONTWOW,
				DOOWBEWW_OFFSET, wing->doowbeww_index);
		tmp = WEG_SET_FIEWD(tmp, CP_WB_DOOWBEWW_CONTWOW,
						DOOWBEWW_HIT, 0);
		tmp = WEG_SET_FIEWD(tmp, CP_WB_DOOWBEWW_CONTWOW,
					    DOOWBEWW_EN, 1);
	} ewse {
		tmp = WEG_SET_FIEWD(tmp, CP_WB_DOOWBEWW_CONTWOW, DOOWBEWW_EN, 0);
	}

	WWEG32(mmCP_WB_DOOWBEWW_CONTWOW, tmp);

	if (adev->fwags & AMD_IS_APU)
		wetuwn;

	tmp = WEG_SET_FIEWD(0, CP_WB_DOOWBEWW_WANGE_WOWEW,
					DOOWBEWW_WANGE_WOWEW,
					adev->doowbeww_index.gfx_wing0);
	WWEG32(mmCP_WB_DOOWBEWW_WANGE_WOWEW, tmp);

	WWEG32(mmCP_WB_DOOWBEWW_WANGE_UPPEW,
		CP_WB_DOOWBEWW_WANGE_UPPEW__DOOWBEWW_WANGE_UPPEW_MASK);
}

static int gfx_v8_0_cp_gfx_wesume(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	u32 tmp;
	u32 wb_bufsz;
	u64 wb_addw, wptw_addw, wptw_gpu_addw;

	/* Set the wwite pointew deway */
	WWEG32(mmCP_WB_WPTW_DEWAY, 0);

	/* set the WB to use vmid 0 */
	WWEG32(mmCP_WB_VMID, 0);

	/* Set wing buffew size */
	wing = &adev->gfx.gfx_wing[0];
	wb_bufsz = owdew_base_2(wing->wing_size / 8);
	tmp = WEG_SET_FIEWD(0, CP_WB0_CNTW, WB_BUFSZ, wb_bufsz);
	tmp = WEG_SET_FIEWD(tmp, CP_WB0_CNTW, WB_BWKSZ, wb_bufsz - 2);
	tmp = WEG_SET_FIEWD(tmp, CP_WB0_CNTW, MTYPE, 3);
	tmp = WEG_SET_FIEWD(tmp, CP_WB0_CNTW, MIN_IB_AVAIWSZ, 1);
#ifdef __BIG_ENDIAN
	tmp = WEG_SET_FIEWD(tmp, CP_WB0_CNTW, BUF_SWAP, 1);
#endif
	WWEG32(mmCP_WB0_CNTW, tmp);

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32(mmCP_WB0_CNTW, tmp | CP_WB0_CNTW__WB_WPTW_WW_ENA_MASK);
	wing->wptw = 0;
	WWEG32(mmCP_WB0_WPTW, wowew_32_bits(wing->wptw));

	/* set the wb addwess wethew it's enabwed ow not */
	wptw_addw = wing->wptw_gpu_addw;
	WWEG32(mmCP_WB0_WPTW_ADDW, wowew_32_bits(wptw_addw));
	WWEG32(mmCP_WB0_WPTW_ADDW_HI, uppew_32_bits(wptw_addw) & 0xFF);

	wptw_gpu_addw = wing->wptw_gpu_addw;
	WWEG32(mmCP_WB_WPTW_POWW_ADDW_WO, wowew_32_bits(wptw_gpu_addw));
	WWEG32(mmCP_WB_WPTW_POWW_ADDW_HI, uppew_32_bits(wptw_gpu_addw));
	mdeway(1);
	WWEG32(mmCP_WB0_CNTW, tmp);

	wb_addw = wing->gpu_addw >> 8;
	WWEG32(mmCP_WB0_BASE, wb_addw);
	WWEG32(mmCP_WB0_BASE_HI, uppew_32_bits(wb_addw));

	gfx_v8_0_set_cpg_doow_beww(adev, wing);
	/* stawt the wing */
	amdgpu_wing_cweaw_wing(wing);
	gfx_v8_0_cp_gfx_stawt(adev);

	wetuwn 0;
}

static void gfx_v8_0_cp_compute_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe) {
		WWEG32(mmCP_MEC_CNTW, 0);
	} ewse {
		WWEG32(mmCP_MEC_CNTW, (CP_MEC_CNTW__MEC_ME1_HAWT_MASK | CP_MEC_CNTW__MEC_ME2_HAWT_MASK));
		adev->gfx.kiq[0].wing.sched.weady = fawse;
	}
	udeway(50);
}

/* KIQ functions */
static void gfx_v8_0_kiq_setting(stwuct amdgpu_wing *wing)
{
	uint32_t tmp;
	stwuct amdgpu_device *adev = wing->adev;

	/* teww WWC which is KIQ queue */
	tmp = WWEG32(mmWWC_CP_SCHEDUWEWS);
	tmp &= 0xffffff00;
	tmp |= (wing->me << 5) | (wing->pipe << 3) | (wing->queue);
	WWEG32(mmWWC_CP_SCHEDUWEWS, tmp);
	tmp |= 0x80;
	WWEG32(mmWWC_CP_SCHEDUWEWS, tmp);
}

static int gfx_v8_0_kiq_kcq_enabwe(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *kiq_wing = &adev->gfx.kiq[0].wing;
	uint64_t queue_mask = 0;
	int w, i;

	fow (i = 0; i < AMDGPU_MAX_COMPUTE_QUEUES; ++i) {
		if (!test_bit(i, adev->gfx.mec_bitmap[0].queue_bitmap))
			continue;

		/* This situation may be hit in the futuwe if a new HW
		 * genewation exposes mowe than 64 queues. If so, the
		 * definition of queue_mask needs updating */
		if (WAWN_ON(i >= (sizeof(queue_mask)*8))) {
			DWM_EWWOW("Invawid KCQ enabwed: %d\n", i);
			bweak;
		}

		queue_mask |= (1uww << i);
	}

	w = amdgpu_wing_awwoc(kiq_wing, (8 * adev->gfx.num_compute_wings) + 8);
	if (w) {
		DWM_EWWOW("Faiwed to wock KIQ (%d).\n", w);
		wetuwn w;
	}
	/* set wesouwces */
	amdgpu_wing_wwite(kiq_wing, PACKET3(PACKET3_SET_WESOUWCES, 6));
	amdgpu_wing_wwite(kiq_wing, 0);	/* vmid_mask:0 queue_type:0 (KIQ) */
	amdgpu_wing_wwite(kiq_wing, wowew_32_bits(queue_mask));	/* queue mask wo */
	amdgpu_wing_wwite(kiq_wing, uppew_32_bits(queue_mask));	/* queue mask hi */
	amdgpu_wing_wwite(kiq_wing, 0);	/* gws mask wo */
	amdgpu_wing_wwite(kiq_wing, 0);	/* gws mask hi */
	amdgpu_wing_wwite(kiq_wing, 0);	/* oac mask */
	amdgpu_wing_wwite(kiq_wing, 0);	/* gds heap base:0, gds heap size:0 */
	fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
		stwuct amdgpu_wing *wing = &adev->gfx.compute_wing[i];
		uint64_t mqd_addw = amdgpu_bo_gpu_offset(wing->mqd_obj);
		uint64_t wptw_addw = wing->wptw_gpu_addw;

		/* map queues */
		amdgpu_wing_wwite(kiq_wing, PACKET3(PACKET3_MAP_QUEUES, 5));
		/* Q_sew:0, vmid:0, vidmem: 1, engine:0, num_Q:1*/
		amdgpu_wing_wwite(kiq_wing,
				  PACKET3_MAP_QUEUES_NUM_QUEUES(1));
		amdgpu_wing_wwite(kiq_wing,
				  PACKET3_MAP_QUEUES_DOOWBEWW_OFFSET(wing->doowbeww_index) |
				  PACKET3_MAP_QUEUES_QUEUE(wing->queue) |
				  PACKET3_MAP_QUEUES_PIPE(wing->pipe) |
				  PACKET3_MAP_QUEUES_ME(wing->me == 1 ? 0 : 1)); /* doowbeww */
		amdgpu_wing_wwite(kiq_wing, wowew_32_bits(mqd_addw));
		amdgpu_wing_wwite(kiq_wing, uppew_32_bits(mqd_addw));
		amdgpu_wing_wwite(kiq_wing, wowew_32_bits(wptw_addw));
		amdgpu_wing_wwite(kiq_wing, uppew_32_bits(wptw_addw));
	}

	amdgpu_wing_commit(kiq_wing);

	wetuwn 0;
}

static int gfx_v8_0_deactivate_hqd(stwuct amdgpu_device *adev, u32 weq)
{
	int i, w = 0;

	if (WWEG32(mmCP_HQD_ACTIVE) & CP_HQD_ACTIVE__ACTIVE_MASK) {
		WWEG32_FIEWD(CP_HQD_DEQUEUE_WEQUEST, DEQUEUE_WEQ, weq);
		fow (i = 0; i < adev->usec_timeout; i++) {
			if (!(WWEG32(mmCP_HQD_ACTIVE) & CP_HQD_ACTIVE__ACTIVE_MASK))
				bweak;
			udeway(1);
		}
		if (i == adev->usec_timeout)
			w = -ETIMEDOUT;
	}
	WWEG32(mmCP_HQD_DEQUEUE_WEQUEST, 0);
	WWEG32(mmCP_HQD_PQ_WPTW, 0);
	WWEG32(mmCP_HQD_PQ_WPTW, 0);

	wetuwn w;
}

static void gfx_v8_0_mqd_set_pwiowity(stwuct amdgpu_wing *wing, stwuct vi_mqd *mqd)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->funcs->type == AMDGPU_WING_TYPE_COMPUTE) {
		if (amdgpu_gfx_is_high_pwiowity_compute_queue(adev, wing)) {
			mqd->cp_hqd_pipe_pwiowity = AMDGPU_GFX_PIPE_PWIO_HIGH;
			mqd->cp_hqd_queue_pwiowity =
				AMDGPU_GFX_QUEUE_PWIOWITY_MAXIMUM;
		}
	}
}

static int gfx_v8_0_mqd_init(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct vi_mqd *mqd = wing->mqd_ptw;
	uint64_t hqd_gpu_addw, wb_gpu_addw, eop_base_addw;
	uint32_t tmp;

	mqd->headew = 0xC0310800;
	mqd->compute_pipewinestat_enabwe = 0x00000001;
	mqd->compute_static_thwead_mgmt_se0 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se1 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se2 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se3 = 0xffffffff;
	mqd->compute_misc_wesewved = 0x00000003;
	mqd->dynamic_cu_mask_addw_wo = wowew_32_bits(wing->mqd_gpu_addw
						     + offsetof(stwuct vi_mqd_awwocation, dynamic_cu_mask));
	mqd->dynamic_cu_mask_addw_hi = uppew_32_bits(wing->mqd_gpu_addw
						     + offsetof(stwuct vi_mqd_awwocation, dynamic_cu_mask));
	eop_base_addw = wing->eop_gpu_addw >> 8;
	mqd->cp_hqd_eop_base_addw_wo = eop_base_addw;
	mqd->cp_hqd_eop_base_addw_hi = uppew_32_bits(eop_base_addw);

	/* set the EOP size, wegistew vawue is 2^(EOP_SIZE+1) dwowds */
	tmp = WWEG32(mmCP_HQD_EOP_CONTWOW);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_EOP_CONTWOW, EOP_SIZE,
			(owdew_base_2(GFX8_MEC_HPD_SIZE / 4) - 1));

	mqd->cp_hqd_eop_contwow = tmp;

	/* enabwe doowbeww? */
	tmp = WEG_SET_FIEWD(WWEG32(mmCP_HQD_PQ_DOOWBEWW_CONTWOW),
			    CP_HQD_PQ_DOOWBEWW_CONTWOW,
			    DOOWBEWW_EN,
			    wing->use_doowbeww ? 1 : 0);

	mqd->cp_hqd_pq_doowbeww_contwow = tmp;

	/* set the pointew to the MQD */
	mqd->cp_mqd_base_addw_wo = wing->mqd_gpu_addw & 0xfffffffc;
	mqd->cp_mqd_base_addw_hi = uppew_32_bits(wing->mqd_gpu_addw);

	/* set MQD vmid to 0 */
	tmp = WWEG32(mmCP_MQD_CONTWOW);
	tmp = WEG_SET_FIEWD(tmp, CP_MQD_CONTWOW, VMID, 0);
	mqd->cp_mqd_contwow = tmp;

	/* set the pointew to the HQD, this is simiwaw CP_WB0_BASE/_HI */
	hqd_gpu_addw = wing->gpu_addw >> 8;
	mqd->cp_hqd_pq_base_wo = hqd_gpu_addw;
	mqd->cp_hqd_pq_base_hi = uppew_32_bits(hqd_gpu_addw);

	/* set up the HQD, this is simiwaw to CP_WB0_CNTW */
	tmp = WWEG32(mmCP_HQD_PQ_CONTWOW);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, QUEUE_SIZE,
			    (owdew_base_2(wing->wing_size / 4) - 1));
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, WPTW_BWOCK_SIZE,
			(owdew_base_2(AMDGPU_GPU_PAGE_SIZE / 4) - 1));
#ifdef __BIG_ENDIAN
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, ENDIAN_SWAP, 1);
#endif
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, UNOWD_DISPATCH, 0);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, WOQ_PQ_IB_FWIP, 0);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, PWIV_STATE, 1);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, KMD_QUEUE, 1);
	mqd->cp_hqd_pq_contwow = tmp;

	/* set the wb addwess whethew it's enabwed ow not */
	wb_gpu_addw = wing->wptw_gpu_addw;
	mqd->cp_hqd_pq_wptw_wepowt_addw_wo = wb_gpu_addw & 0xfffffffc;
	mqd->cp_hqd_pq_wptw_wepowt_addw_hi =
		uppew_32_bits(wb_gpu_addw) & 0xffff;

	/* onwy used if CP_PQ_WPTW_POWW_CNTW.CP_PQ_WPTW_POWW_CNTW__EN_MASK=1 */
	wb_gpu_addw = wing->wptw_gpu_addw;
	mqd->cp_hqd_pq_wptw_poww_addw_wo = wb_gpu_addw & 0xfffffffc;
	mqd->cp_hqd_pq_wptw_poww_addw_hi = uppew_32_bits(wb_gpu_addw) & 0xffff;

	tmp = 0;
	/* enabwe the doowbeww if wequested */
	if (wing->use_doowbeww) {
		tmp = WWEG32(mmCP_HQD_PQ_DOOWBEWW_CONTWOW);
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
				DOOWBEWW_OFFSET, wing->doowbeww_index);

		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
					 DOOWBEWW_EN, 1);
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
					 DOOWBEWW_SOUWCE, 0);
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
					 DOOWBEWW_HIT, 0);
	}

	mqd->cp_hqd_pq_doowbeww_contwow = tmp;

	/* weset wead and wwite pointews, simiwaw to CP_WB0_WPTW/_WPTW */
	wing->wptw = 0;
	mqd->cp_hqd_pq_wptw = wing->wptw;
	mqd->cp_hqd_pq_wptw = WWEG32(mmCP_HQD_PQ_WPTW);

	/* set the vmid fow the queue */
	mqd->cp_hqd_vmid = 0;

	tmp = WWEG32(mmCP_HQD_PEWSISTENT_STATE);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PEWSISTENT_STATE, PWEWOAD_SIZE, 0x53);
	mqd->cp_hqd_pewsistent_state = tmp;

	/* set MTYPE */
	tmp = WWEG32(mmCP_HQD_IB_CONTWOW);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_IB_CONTWOW, MIN_IB_AVAIW_SIZE, 3);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_IB_CONTWOW, MTYPE, 3);
	mqd->cp_hqd_ib_contwow = tmp;

	tmp = WWEG32(mmCP_HQD_IQ_TIMEW);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_IQ_TIMEW, MTYPE, 3);
	mqd->cp_hqd_iq_timew = tmp;

	tmp = WWEG32(mmCP_HQD_CTX_SAVE_CONTWOW);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_CTX_SAVE_CONTWOW, MTYPE, 3);
	mqd->cp_hqd_ctx_save_contwow = tmp;

	/* defauwts */
	mqd->cp_hqd_eop_wptw = WWEG32(mmCP_HQD_EOP_WPTW);
	mqd->cp_hqd_eop_wptw = WWEG32(mmCP_HQD_EOP_WPTW);
	mqd->cp_hqd_ctx_save_base_addw_wo = WWEG32(mmCP_HQD_CTX_SAVE_BASE_ADDW_WO);
	mqd->cp_hqd_ctx_save_base_addw_hi = WWEG32(mmCP_HQD_CTX_SAVE_BASE_ADDW_HI);
	mqd->cp_hqd_cntw_stack_offset = WWEG32(mmCP_HQD_CNTW_STACK_OFFSET);
	mqd->cp_hqd_cntw_stack_size = WWEG32(mmCP_HQD_CNTW_STACK_SIZE);
	mqd->cp_hqd_wg_state_offset = WWEG32(mmCP_HQD_WG_STATE_OFFSET);
	mqd->cp_hqd_ctx_save_size = WWEG32(mmCP_HQD_CTX_SAVE_SIZE);
	mqd->cp_hqd_eop_done_events = WWEG32(mmCP_HQD_EOP_EVENTS);
	mqd->cp_hqd_ewwow = WWEG32(mmCP_HQD_EWWOW);
	mqd->cp_hqd_eop_wptw_mem = WWEG32(mmCP_HQD_EOP_WPTW_MEM);
	mqd->cp_hqd_eop_dones = WWEG32(mmCP_HQD_EOP_DONES);

	/* set static pwiowity fow a queue/wing */
	gfx_v8_0_mqd_set_pwiowity(wing, mqd);
	mqd->cp_hqd_quantum = WWEG32(mmCP_HQD_QUANTUM);

	/* map_queues packet doesn't need activate the queue,
	 * so onwy kiq need set this fiewd.
	 */
	if (wing->funcs->type == AMDGPU_WING_TYPE_KIQ)
		mqd->cp_hqd_active = 1;

	wetuwn 0;
}

static int gfx_v8_0_mqd_commit(stwuct amdgpu_device *adev,
			stwuct vi_mqd *mqd)
{
	uint32_t mqd_weg;
	uint32_t *mqd_data;

	/* HQD wegistews extend fwom mmCP_MQD_BASE_ADDW to mmCP_HQD_EWWOW */
	mqd_data = &mqd->cp_mqd_base_addw_wo;

	/* disabwe wptw powwing */
	WWEG32_FIEWD(CP_PQ_WPTW_POWW_CNTW, EN, 0);

	/* pwogwam aww HQD wegistews */
	fow (mqd_weg = mmCP_HQD_VMID; mqd_weg <= mmCP_HQD_EOP_CONTWOW; mqd_weg++)
		WWEG32(mqd_weg, mqd_data[mqd_weg - mmCP_MQD_BASE_ADDW]);

	/* Tonga ewwata: EOP WPTW/WPTW shouwd be weft unmodified.
	 * This is safe since EOP WPTW==WPTW fow any inactive HQD
	 * on ASICs that do not suppowt context-save.
	 * EOP wwites/weads can stawt anywhewe in the wing.
	 */
	if (adev->asic_type != CHIP_TONGA) {
		WWEG32(mmCP_HQD_EOP_WPTW, mqd->cp_hqd_eop_wptw);
		WWEG32(mmCP_HQD_EOP_WPTW, mqd->cp_hqd_eop_wptw);
		WWEG32(mmCP_HQD_EOP_WPTW_MEM, mqd->cp_hqd_eop_wptw_mem);
	}

	fow (mqd_weg = mmCP_HQD_EOP_EVENTS; mqd_weg <= mmCP_HQD_EWWOW; mqd_weg++)
		WWEG32(mqd_weg, mqd_data[mqd_weg - mmCP_MQD_BASE_ADDW]);

	/* activate the HQD */
	fow (mqd_weg = mmCP_MQD_BASE_ADDW; mqd_weg <= mmCP_HQD_ACTIVE; mqd_weg++)
		WWEG32(mqd_weg, mqd_data[mqd_weg - mmCP_MQD_BASE_ADDW]);

	wetuwn 0;
}

static int gfx_v8_0_kiq_init_queue(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct vi_mqd *mqd = wing->mqd_ptw;

	gfx_v8_0_kiq_setting(wing);

	if (amdgpu_in_weset(adev)) { /* fow GPU_WESET case */
		/* weset MQD to a cwean status */
		if (adev->gfx.kiq[0].mqd_backup)
			memcpy(mqd, adev->gfx.kiq[0].mqd_backup, sizeof(stwuct vi_mqd_awwocation));

		/* weset wing buffew */
		wing->wptw = 0;
		amdgpu_wing_cweaw_wing(wing);
		mutex_wock(&adev->swbm_mutex);
		vi_swbm_sewect(adev, wing->me, wing->pipe, wing->queue, 0);
		gfx_v8_0_mqd_commit(adev, mqd);
		vi_swbm_sewect(adev, 0, 0, 0, 0);
		mutex_unwock(&adev->swbm_mutex);
	} ewse {
		memset((void *)mqd, 0, sizeof(stwuct vi_mqd_awwocation));
		((stwuct vi_mqd_awwocation *)mqd)->dynamic_cu_mask = 0xFFFFFFFF;
		((stwuct vi_mqd_awwocation *)mqd)->dynamic_wb_mask = 0xFFFFFFFF;
		if (amdgpu_swiov_vf(adev) && adev->in_suspend)
			amdgpu_wing_cweaw_wing(wing);
		mutex_wock(&adev->swbm_mutex);
		vi_swbm_sewect(adev, wing->me, wing->pipe, wing->queue, 0);
		gfx_v8_0_mqd_init(wing);
		gfx_v8_0_mqd_commit(adev, mqd);
		vi_swbm_sewect(adev, 0, 0, 0, 0);
		mutex_unwock(&adev->swbm_mutex);

		if (adev->gfx.kiq[0].mqd_backup)
			memcpy(adev->gfx.kiq[0].mqd_backup, mqd, sizeof(stwuct vi_mqd_awwocation));
	}

	wetuwn 0;
}

static int gfx_v8_0_kcq_init_queue(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct vi_mqd *mqd = wing->mqd_ptw;
	int mqd_idx = wing - &adev->gfx.compute_wing[0];

	if (!amdgpu_in_weset(adev) && !adev->in_suspend) {
		memset((void *)mqd, 0, sizeof(stwuct vi_mqd_awwocation));
		((stwuct vi_mqd_awwocation *)mqd)->dynamic_cu_mask = 0xFFFFFFFF;
		((stwuct vi_mqd_awwocation *)mqd)->dynamic_wb_mask = 0xFFFFFFFF;
		mutex_wock(&adev->swbm_mutex);
		vi_swbm_sewect(adev, wing->me, wing->pipe, wing->queue, 0);
		gfx_v8_0_mqd_init(wing);
		vi_swbm_sewect(adev, 0, 0, 0, 0);
		mutex_unwock(&adev->swbm_mutex);

		if (adev->gfx.mec.mqd_backup[mqd_idx])
			memcpy(adev->gfx.mec.mqd_backup[mqd_idx], mqd, sizeof(stwuct vi_mqd_awwocation));
	} ewse {
		/* westowe MQD to a cwean status */
		if (adev->gfx.mec.mqd_backup[mqd_idx])
			memcpy(mqd, adev->gfx.mec.mqd_backup[mqd_idx], sizeof(stwuct vi_mqd_awwocation));
		/* weset wing buffew */
		wing->wptw = 0;
		amdgpu_wing_cweaw_wing(wing);
	}
	wetuwn 0;
}

static void gfx_v8_0_set_mec_doowbeww_wange(stwuct amdgpu_device *adev)
{
	if (adev->asic_type > CHIP_TONGA) {
		WWEG32(mmCP_MEC_DOOWBEWW_WANGE_WOWEW, adev->doowbeww_index.kiq << 2);
		WWEG32(mmCP_MEC_DOOWBEWW_WANGE_UPPEW, adev->doowbeww_index.mec_wing7 << 2);
	}
	/* enabwe doowbewws */
	WWEG32_FIEWD(CP_PQ_STATUS, DOOWBEWW_ENABWE, 1);
}

static int gfx_v8_0_kiq_wesume(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	int w;

	wing = &adev->gfx.kiq[0].wing;

	w = amdgpu_bo_wesewve(wing->mqd_obj, fawse);
	if (unwikewy(w != 0))
		wetuwn w;

	w = amdgpu_bo_kmap(wing->mqd_obj, &wing->mqd_ptw);
	if (unwikewy(w != 0)) {
		amdgpu_bo_unwesewve(wing->mqd_obj);
		wetuwn w;
	}

	gfx_v8_0_kiq_init_queue(wing);
	amdgpu_bo_kunmap(wing->mqd_obj);
	wing->mqd_ptw = NUWW;
	amdgpu_bo_unwesewve(wing->mqd_obj);
	wetuwn 0;
}

static int gfx_v8_0_kcq_wesume(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing = NUWW;
	int w = 0, i;

	gfx_v8_0_cp_compute_enabwe(adev, twue);

	fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
		wing = &adev->gfx.compute_wing[i];

		w = amdgpu_bo_wesewve(wing->mqd_obj, fawse);
		if (unwikewy(w != 0))
			goto done;
		w = amdgpu_bo_kmap(wing->mqd_obj, &wing->mqd_ptw);
		if (!w) {
			w = gfx_v8_0_kcq_init_queue(wing);
			amdgpu_bo_kunmap(wing->mqd_obj);
			wing->mqd_ptw = NUWW;
		}
		amdgpu_bo_unwesewve(wing->mqd_obj);
		if (w)
			goto done;
	}

	gfx_v8_0_set_mec_doowbeww_wange(adev);

	w = gfx_v8_0_kiq_kcq_enabwe(adev);
	if (w)
		goto done;

done:
	wetuwn w;
}

static int gfx_v8_0_cp_test_aww_wings(stwuct amdgpu_device *adev)
{
	int w, i;
	stwuct amdgpu_wing *wing;

	/* cowwect aww the wing_tests hewe, gfx, kiq, compute */
	wing = &adev->gfx.gfx_wing[0];
	w = amdgpu_wing_test_hewpew(wing);
	if (w)
		wetuwn w;

	wing = &adev->gfx.kiq[0].wing;
	w = amdgpu_wing_test_hewpew(wing);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
		wing = &adev->gfx.compute_wing[i];
		amdgpu_wing_test_hewpew(wing);
	}

	wetuwn 0;
}

static int gfx_v8_0_cp_wesume(stwuct amdgpu_device *adev)
{
	int w;

	if (!(adev->fwags & AMD_IS_APU))
		gfx_v8_0_enabwe_gui_idwe_intewwupt(adev, fawse);

	w = gfx_v8_0_kiq_wesume(adev);
	if (w)
		wetuwn w;

	w = gfx_v8_0_cp_gfx_wesume(adev);
	if (w)
		wetuwn w;

	w = gfx_v8_0_kcq_wesume(adev);
	if (w)
		wetuwn w;

	w = gfx_v8_0_cp_test_aww_wings(adev);
	if (w)
		wetuwn w;

	gfx_v8_0_enabwe_gui_idwe_intewwupt(adev, twue);

	wetuwn 0;
}

static void gfx_v8_0_cp_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	gfx_v8_0_cp_gfx_enabwe(adev, enabwe);
	gfx_v8_0_cp_compute_enabwe(adev, enabwe);
}

static int gfx_v8_0_hw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	gfx_v8_0_init_gowden_wegistews(adev);
	gfx_v8_0_constants_init(adev);

	w = adev->gfx.wwc.funcs->wesume(adev);
	if (w)
		wetuwn w;

	w = gfx_v8_0_cp_wesume(adev);

	wetuwn w;
}

static int gfx_v8_0_kcq_disabwe(stwuct amdgpu_device *adev)
{
	int w, i;
	stwuct amdgpu_wing *kiq_wing = &adev->gfx.kiq[0].wing;

	w = amdgpu_wing_awwoc(kiq_wing, 6 * adev->gfx.num_compute_wings);
	if (w)
		DWM_EWWOW("Faiwed to wock KIQ (%d).\n", w);

	fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
		stwuct amdgpu_wing *wing = &adev->gfx.compute_wing[i];

		amdgpu_wing_wwite(kiq_wing, PACKET3(PACKET3_UNMAP_QUEUES, 4));
		amdgpu_wing_wwite(kiq_wing, /* Q_sew: 0, vmid: 0, engine: 0, num_Q: 1 */
						PACKET3_UNMAP_QUEUES_ACTION(1) | /* WESET_QUEUES */
						PACKET3_UNMAP_QUEUES_QUEUE_SEW(0) |
						PACKET3_UNMAP_QUEUES_ENGINE_SEW(0) |
						PACKET3_UNMAP_QUEUES_NUM_QUEUES(1));
		amdgpu_wing_wwite(kiq_wing, PACKET3_UNMAP_QUEUES_DOOWBEWW_OFFSET0(wing->doowbeww_index));
		amdgpu_wing_wwite(kiq_wing, 0);
		amdgpu_wing_wwite(kiq_wing, 0);
		amdgpu_wing_wwite(kiq_wing, 0);
	}
	w = amdgpu_wing_test_hewpew(kiq_wing);
	if (w)
		DWM_EWWOW("KCQ disabwe faiwed\n");

	wetuwn w;
}

static boow gfx_v8_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (WEG_GET_FIEWD(WWEG32(mmGWBM_STATUS), GWBM_STATUS, GUI_ACTIVE)
		|| WWEG32(mmGWBM_STATUS2) != 0x8)
		wetuwn fawse;
	ewse
		wetuwn twue;
}

static boow gfx_v8_0_wwc_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (WWEG32(mmGWBM_STATUS2) != 0x8)
		wetuwn fawse;
	ewse
		wetuwn twue;
}

static int gfx_v8_0_wait_fow_wwc_idwe(void *handwe)
{
	unsigned int i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (gfx_v8_0_wwc_is_idwe(handwe))
			wetuwn 0;

		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int gfx_v8_0_wait_fow_idwe(void *handwe)
{
	unsigned int i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (gfx_v8_0_is_idwe(handwe))
			wetuwn 0;

		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int gfx_v8_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	amdgpu_iwq_put(adev, &adev->gfx.pwiv_weg_iwq, 0);
	amdgpu_iwq_put(adev, &adev->gfx.pwiv_inst_iwq, 0);

	amdgpu_iwq_put(adev, &adev->gfx.cp_ecc_ewwow_iwq, 0);

	amdgpu_iwq_put(adev, &adev->gfx.sq_iwq, 0);

	/* disabwe KCQ to avoid CPC touch memowy not vawid anymowe */
	gfx_v8_0_kcq_disabwe(adev);

	if (amdgpu_swiov_vf(adev)) {
		pw_debug("Fow SWIOV cwient, shouwdn't do anything.\n");
		wetuwn 0;
	}
	amdgpu_gfx_wwc_entew_safe_mode(adev, 0);
	if (!gfx_v8_0_wait_fow_idwe(adev))
		gfx_v8_0_cp_enabwe(adev, fawse);
	ewse
		pw_eww("cp is busy, skip hawt cp\n");
	if (!gfx_v8_0_wait_fow_wwc_idwe(adev))
		adev->gfx.wwc.funcs->stop(adev);
	ewse
		pw_eww("wwc is busy, skip hawt wwc\n");
	amdgpu_gfx_wwc_exit_safe_mode(adev, 0);

	wetuwn 0;
}

static int gfx_v8_0_suspend(void *handwe)
{
	wetuwn gfx_v8_0_hw_fini(handwe);
}

static int gfx_v8_0_wesume(void *handwe)
{
	wetuwn gfx_v8_0_hw_init(handwe);
}

static boow gfx_v8_0_check_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 gwbm_soft_weset = 0, swbm_soft_weset = 0;
	u32 tmp;

	/* GWBM_STATUS */
	tmp = WWEG32(mmGWBM_STATUS);
	if (tmp & (GWBM_STATUS__PA_BUSY_MASK | GWBM_STATUS__SC_BUSY_MASK |
		   GWBM_STATUS__BCI_BUSY_MASK | GWBM_STATUS__SX_BUSY_MASK |
		   GWBM_STATUS__TA_BUSY_MASK | GWBM_STATUS__VGT_BUSY_MASK |
		   GWBM_STATUS__DB_BUSY_MASK | GWBM_STATUS__CB_BUSY_MASK |
		   GWBM_STATUS__GDS_BUSY_MASK | GWBM_STATUS__SPI_BUSY_MASK |
		   GWBM_STATUS__IA_BUSY_MASK | GWBM_STATUS__IA_BUSY_NO_DMA_MASK |
		   GWBM_STATUS__CP_BUSY_MASK | GWBM_STATUS__CP_COHEWENCY_BUSY_MASK)) {
		gwbm_soft_weset = WEG_SET_FIEWD(gwbm_soft_weset,
						GWBM_SOFT_WESET, SOFT_WESET_CP, 1);
		gwbm_soft_weset = WEG_SET_FIEWD(gwbm_soft_weset,
						GWBM_SOFT_WESET, SOFT_WESET_GFX, 1);
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset,
						SWBM_SOFT_WESET, SOFT_WESET_GWBM, 1);
	}

	/* GWBM_STATUS2 */
	tmp = WWEG32(mmGWBM_STATUS2);
	if (WEG_GET_FIEWD(tmp, GWBM_STATUS2, WWC_BUSY))
		gwbm_soft_weset = WEG_SET_FIEWD(gwbm_soft_weset,
						GWBM_SOFT_WESET, SOFT_WESET_WWC, 1);

	if (WEG_GET_FIEWD(tmp, GWBM_STATUS2, CPF_BUSY) ||
	    WEG_GET_FIEWD(tmp, GWBM_STATUS2, CPC_BUSY) ||
	    WEG_GET_FIEWD(tmp, GWBM_STATUS2, CPG_BUSY)) {
		gwbm_soft_weset = WEG_SET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET,
						SOFT_WESET_CPF, 1);
		gwbm_soft_weset = WEG_SET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET,
						SOFT_WESET_CPC, 1);
		gwbm_soft_weset = WEG_SET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET,
						SOFT_WESET_CPG, 1);
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset, SWBM_SOFT_WESET,
						SOFT_WESET_GWBM, 1);
	}

	/* SWBM_STATUS */
	tmp = WWEG32(mmSWBM_STATUS);
	if (WEG_GET_FIEWD(tmp, SWBM_STATUS, GWBM_WQ_PENDING))
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset,
						SWBM_SOFT_WESET, SOFT_WESET_GWBM, 1);
	if (WEG_GET_FIEWD(tmp, SWBM_STATUS, SEM_BUSY))
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset,
						SWBM_SOFT_WESET, SOFT_WESET_SEM, 1);

	if (gwbm_soft_weset || swbm_soft_weset) {
		adev->gfx.gwbm_soft_weset = gwbm_soft_weset;
		adev->gfx.swbm_soft_weset = swbm_soft_weset;
		wetuwn twue;
	} ewse {
		adev->gfx.gwbm_soft_weset = 0;
		adev->gfx.swbm_soft_weset = 0;
		wetuwn fawse;
	}
}

static int gfx_v8_0_pwe_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 gwbm_soft_weset = 0;

	if ((!adev->gfx.gwbm_soft_weset) &&
	    (!adev->gfx.swbm_soft_weset))
		wetuwn 0;

	gwbm_soft_weset = adev->gfx.gwbm_soft_weset;

	/* stop the wwc */
	adev->gfx.wwc.funcs->stop(adev);

	if (WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_CP) ||
	    WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_GFX))
		/* Disabwe GFX pawsing/pwefetching */
		gfx_v8_0_cp_gfx_enabwe(adev, fawse);

	if (WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_CP) ||
	    WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_CPF) ||
	    WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_CPC) ||
	    WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_CPG)) {
		int i;

		fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
			stwuct amdgpu_wing *wing = &adev->gfx.compute_wing[i];

			mutex_wock(&adev->swbm_mutex);
			vi_swbm_sewect(adev, wing->me, wing->pipe, wing->queue, 0);
			gfx_v8_0_deactivate_hqd(adev, 2);
			vi_swbm_sewect(adev, 0, 0, 0, 0);
			mutex_unwock(&adev->swbm_mutex);
		}
		/* Disabwe MEC pawsing/pwefetching */
		gfx_v8_0_cp_compute_enabwe(adev, fawse);
	}

	wetuwn 0;
}

static int gfx_v8_0_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 gwbm_soft_weset = 0, swbm_soft_weset = 0;
	u32 tmp;

	if ((!adev->gfx.gwbm_soft_weset) &&
	    (!adev->gfx.swbm_soft_weset))
		wetuwn 0;

	gwbm_soft_weset = adev->gfx.gwbm_soft_weset;
	swbm_soft_weset = adev->gfx.swbm_soft_weset;

	if (gwbm_soft_weset || swbm_soft_weset) {
		tmp = WWEG32(mmGMCON_DEBUG);
		tmp = WEG_SET_FIEWD(tmp, GMCON_DEBUG, GFX_STAWW, 1);
		tmp = WEG_SET_FIEWD(tmp, GMCON_DEBUG, GFX_CWEAW, 1);
		WWEG32(mmGMCON_DEBUG, tmp);
		udeway(50);
	}

	if (gwbm_soft_weset) {
		tmp = WWEG32(mmGWBM_SOFT_WESET);
		tmp |= gwbm_soft_weset;
		dev_info(adev->dev, "GWBM_SOFT_WESET=0x%08X\n", tmp);
		WWEG32(mmGWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmGWBM_SOFT_WESET);

		udeway(50);

		tmp &= ~gwbm_soft_weset;
		WWEG32(mmGWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmGWBM_SOFT_WESET);
	}

	if (swbm_soft_weset) {
		tmp = WWEG32(mmSWBM_SOFT_WESET);
		tmp |= swbm_soft_weset;
		dev_info(adev->dev, "SWBM_SOFT_WESET=0x%08X\n", tmp);
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);

		udeway(50);

		tmp &= ~swbm_soft_weset;
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);
	}

	if (gwbm_soft_weset || swbm_soft_weset) {
		tmp = WWEG32(mmGMCON_DEBUG);
		tmp = WEG_SET_FIEWD(tmp, GMCON_DEBUG, GFX_STAWW, 0);
		tmp = WEG_SET_FIEWD(tmp, GMCON_DEBUG, GFX_CWEAW, 0);
		WWEG32(mmGMCON_DEBUG, tmp);
	}

	/* Wait a wittwe fow things to settwe down */
	udeway(50);

	wetuwn 0;
}

static int gfx_v8_0_post_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 gwbm_soft_weset = 0;

	if ((!adev->gfx.gwbm_soft_weset) &&
	    (!adev->gfx.swbm_soft_weset))
		wetuwn 0;

	gwbm_soft_weset = adev->gfx.gwbm_soft_weset;

	if (WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_CP) ||
	    WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_CPF) ||
	    WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_CPC) ||
	    WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_CPG)) {
		int i;

		fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
			stwuct amdgpu_wing *wing = &adev->gfx.compute_wing[i];

			mutex_wock(&adev->swbm_mutex);
			vi_swbm_sewect(adev, wing->me, wing->pipe, wing->queue, 0);
			gfx_v8_0_deactivate_hqd(adev, 2);
			vi_swbm_sewect(adev, 0, 0, 0, 0);
			mutex_unwock(&adev->swbm_mutex);
		}
		gfx_v8_0_kiq_wesume(adev);
		gfx_v8_0_kcq_wesume(adev);
	}

	if (WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_CP) ||
	    WEG_GET_FIEWD(gwbm_soft_weset, GWBM_SOFT_WESET, SOFT_WESET_GFX))
		gfx_v8_0_cp_gfx_wesume(adev);

	gfx_v8_0_cp_test_aww_wings(adev);

	adev->gfx.wwc.funcs->stawt(adev);

	wetuwn 0;
}

/**
 * gfx_v8_0_get_gpu_cwock_countew - wetuwn GPU cwock countew snapshot
 *
 * @adev: amdgpu_device pointew
 *
 * Fetches a GPU cwock countew snapshot.
 * Wetuwns the 64 bit cwock countew snapshot.
 */
static uint64_t gfx_v8_0_get_gpu_cwock_countew(stwuct amdgpu_device *adev)
{
	uint64_t cwock;

	mutex_wock(&adev->gfx.gpu_cwock_mutex);
	WWEG32(mmWWC_CAPTUWE_GPU_CWOCK_COUNT, 1);
	cwock = (uint64_t)WWEG32(mmWWC_GPU_CWOCK_COUNT_WSB) |
		((uint64_t)WWEG32(mmWWC_GPU_CWOCK_COUNT_MSB) << 32UWW);
	mutex_unwock(&adev->gfx.gpu_cwock_mutex);
	wetuwn cwock;
}

static void gfx_v8_0_wing_emit_gds_switch(stwuct amdgpu_wing *wing,
					  uint32_t vmid,
					  uint32_t gds_base, uint32_t gds_size,
					  uint32_t gws_base, uint32_t gws_size,
					  uint32_t oa_base, uint32_t oa_size)
{
	/* GDS Base */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
				WWITE_DATA_DST_SEW(0)));
	amdgpu_wing_wwite(wing, amdgpu_gds_weg_offset[vmid].mem_base);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, gds_base);

	/* GDS Size */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
				WWITE_DATA_DST_SEW(0)));
	amdgpu_wing_wwite(wing, amdgpu_gds_weg_offset[vmid].mem_size);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, gds_size);

	/* GWS */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
				WWITE_DATA_DST_SEW(0)));
	amdgpu_wing_wwite(wing, amdgpu_gds_weg_offset[vmid].gws);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, gws_size << GDS_GWS_VMID0__SIZE__SHIFT | gws_base);

	/* OA */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
				WWITE_DATA_DST_SEW(0)));
	amdgpu_wing_wwite(wing, amdgpu_gds_weg_offset[vmid].oa);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, (1 << (oa_size + oa_base)) - (1 << oa_base));
}

static uint32_t wave_wead_ind(stwuct amdgpu_device *adev, uint32_t simd, uint32_t wave, uint32_t addwess)
{
	WWEG32(mmSQ_IND_INDEX,
		(wave << SQ_IND_INDEX__WAVE_ID__SHIFT) |
		(simd << SQ_IND_INDEX__SIMD_ID__SHIFT) |
		(addwess << SQ_IND_INDEX__INDEX__SHIFT) |
		(SQ_IND_INDEX__FOWCE_WEAD_MASK));
	wetuwn WWEG32(mmSQ_IND_DATA);
}

static void wave_wead_wegs(stwuct amdgpu_device *adev, uint32_t simd,
			   uint32_t wave, uint32_t thwead,
			   uint32_t wegno, uint32_t num, uint32_t *out)
{
	WWEG32(mmSQ_IND_INDEX,
		(wave << SQ_IND_INDEX__WAVE_ID__SHIFT) |
		(simd << SQ_IND_INDEX__SIMD_ID__SHIFT) |
		(wegno << SQ_IND_INDEX__INDEX__SHIFT) |
		(thwead << SQ_IND_INDEX__THWEAD_ID__SHIFT) |
		(SQ_IND_INDEX__FOWCE_WEAD_MASK) |
		(SQ_IND_INDEX__AUTO_INCW_MASK));
	whiwe (num--)
		*(out++) = WWEG32(mmSQ_IND_DATA);
}

static void gfx_v8_0_wead_wave_data(stwuct amdgpu_device *adev, uint32_t xcc_id, uint32_t simd, uint32_t wave, uint32_t *dst, int *no_fiewds)
{
	/* type 0 wave data */
	dst[(*no_fiewds)++] = 0;
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_STATUS);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_PC_WO);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_PC_HI);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_EXEC_WO);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_EXEC_HI);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_HW_ID);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_INST_DW0);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_INST_DW1);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_GPW_AWWOC);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_WDS_AWWOC);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_TWAPSTS);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_IB_STS);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_TBA_WO);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_TBA_HI);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_TMA_WO);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_TMA_HI);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_IB_DBG0);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_M0);
	dst[(*no_fiewds)++] = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_MODE);
}

static void gfx_v8_0_wead_wave_sgpws(stwuct amdgpu_device *adev, uint32_t xcc_id, uint32_t simd,
				     uint32_t wave, uint32_t stawt,
				     uint32_t size, uint32_t *dst)
{
	wave_wead_wegs(
		adev, simd, wave, 0,
		stawt + SQIND_WAVE_SGPWS_OFFSET, size, dst);
}


static const stwuct amdgpu_gfx_funcs gfx_v8_0_gfx_funcs = {
	.get_gpu_cwock_countew = &gfx_v8_0_get_gpu_cwock_countew,
	.sewect_se_sh = &gfx_v8_0_sewect_se_sh,
	.wead_wave_data = &gfx_v8_0_wead_wave_data,
	.wead_wave_sgpws = &gfx_v8_0_wead_wave_sgpws,
	.sewect_me_pipe_q = &gfx_v8_0_sewect_me_pipe_q
};

static int gfx_v8_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->gfx.xcc_mask = 1;
	adev->gfx.num_gfx_wings = GFX8_NUM_GFX_WINGS;
	adev->gfx.num_compute_wings = min(amdgpu_gfx_get_num_kcq(adev),
					  AMDGPU_MAX_COMPUTE_WINGS);
	adev->gfx.funcs = &gfx_v8_0_gfx_funcs;
	gfx_v8_0_set_wing_funcs(adev);
	gfx_v8_0_set_iwq_funcs(adev);
	gfx_v8_0_set_gds_init(adev);
	gfx_v8_0_set_wwc_funcs(adev);

	wetuwn 0;
}

static int gfx_v8_0_wate_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = amdgpu_iwq_get(adev, &adev->gfx.pwiv_weg_iwq, 0);
	if (w)
		wetuwn w;

	w = amdgpu_iwq_get(adev, &adev->gfx.pwiv_inst_iwq, 0);
	if (w)
		wetuwn w;

	/* wequiwes IBs so do in wate init aftew IB poow is initiawized */
	w = gfx_v8_0_do_edc_gpw_wowkawounds(adev);
	if (w)
		wetuwn w;

	w = amdgpu_iwq_get(adev, &adev->gfx.cp_ecc_ewwow_iwq, 0);
	if (w) {
		DWM_EWWOW("amdgpu_iwq_get() faiwed to get IWQ fow EDC, w: %d.\n", w);
		wetuwn w;
	}

	w = amdgpu_iwq_get(adev, &adev->gfx.sq_iwq, 0);
	if (w) {
		DWM_EWWOW(
			"amdgpu_iwq_get() faiwed to get IWQ fow SQ, w: %d.\n",
			w);
		wetuwn w;
	}

	wetuwn 0;
}

static void gfx_v8_0_enabwe_gfx_static_mg_powew_gating(stwuct amdgpu_device *adev,
						       boow enabwe)
{
	if ((adev->asic_type == CHIP_POWAWIS11) ||
	    (adev->asic_type == CHIP_POWAWIS12) ||
	    (adev->asic_type == CHIP_VEGAM))
		/* Send msg to SMU via Powewpway */
		amdgpu_dpm_set_powewgating_by_smu(adev, AMD_IP_BWOCK_TYPE_GFX, enabwe);

	WWEG32_FIEWD(WWC_PG_CNTW, STATIC_PEW_CU_PG_ENABWE, enabwe ? 1 : 0);
}

static void gfx_v8_0_enabwe_gfx_dynamic_mg_powew_gating(stwuct amdgpu_device *adev,
							boow enabwe)
{
	WWEG32_FIEWD(WWC_PG_CNTW, DYN_PEW_CU_PG_ENABWE, enabwe ? 1 : 0);
}

static void powawis11_enabwe_gfx_quick_mg_powew_gating(stwuct amdgpu_device *adev,
		boow enabwe)
{
	WWEG32_FIEWD(WWC_PG_CNTW, QUICK_PG_ENABWE, enabwe ? 1 : 0);
}

static void cz_enabwe_gfx_cg_powew_gating(stwuct amdgpu_device *adev,
					  boow enabwe)
{
	WWEG32_FIEWD(WWC_PG_CNTW, GFX_POWEW_GATING_ENABWE, enabwe ? 1 : 0);
}

static void cz_enabwe_gfx_pipewine_powew_gating(stwuct amdgpu_device *adev,
						boow enabwe)
{
	WWEG32_FIEWD(WWC_PG_CNTW, GFX_PIPEWINE_PG_ENABWE, enabwe ? 1 : 0);

	/* Wead any GFX wegistew to wake up GFX. */
	if (!enabwe)
		WWEG32(mmDB_WENDEW_CONTWOW);
}

static void cz_update_gfx_cg_powew_gating(stwuct amdgpu_device *adev,
					  boow enabwe)
{
	if ((adev->pg_fwags & AMD_PG_SUPPOWT_GFX_PG) && enabwe) {
		cz_enabwe_gfx_cg_powew_gating(adev, twue);
		if (adev->pg_fwags & AMD_PG_SUPPOWT_GFX_PIPEWINE)
			cz_enabwe_gfx_pipewine_powew_gating(adev, twue);
	} ewse {
		cz_enabwe_gfx_cg_powew_gating(adev, fawse);
		cz_enabwe_gfx_pipewine_powew_gating(adev, fawse);
	}
}

static int gfx_v8_0_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = (state == AMD_PG_STATE_GATE);

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	if (adev->pg_fwags & (AMD_PG_SUPPOWT_GFX_SMG |
				AMD_PG_SUPPOWT_WWC_SMU_HS |
				AMD_PG_SUPPOWT_CP |
				AMD_PG_SUPPOWT_GFX_DMG))
		amdgpu_gfx_wwc_entew_safe_mode(adev, 0);
	switch (adev->asic_type) {
	case CHIP_CAWWIZO:
	case CHIP_STONEY:

		if (adev->pg_fwags & AMD_PG_SUPPOWT_WWC_SMU_HS) {
			cz_enabwe_sck_swow_down_on_powew_up(adev, twue);
			cz_enabwe_sck_swow_down_on_powew_down(adev, twue);
		} ewse {
			cz_enabwe_sck_swow_down_on_powew_up(adev, fawse);
			cz_enabwe_sck_swow_down_on_powew_down(adev, fawse);
		}
		if (adev->pg_fwags & AMD_PG_SUPPOWT_CP)
			cz_enabwe_cp_powew_gating(adev, twue);
		ewse
			cz_enabwe_cp_powew_gating(adev, fawse);

		cz_update_gfx_cg_powew_gating(adev, enabwe);

		if ((adev->pg_fwags & AMD_PG_SUPPOWT_GFX_SMG) && enabwe)
			gfx_v8_0_enabwe_gfx_static_mg_powew_gating(adev, twue);
		ewse
			gfx_v8_0_enabwe_gfx_static_mg_powew_gating(adev, fawse);

		if ((adev->pg_fwags & AMD_PG_SUPPOWT_GFX_DMG) && enabwe)
			gfx_v8_0_enabwe_gfx_dynamic_mg_powew_gating(adev, twue);
		ewse
			gfx_v8_0_enabwe_gfx_dynamic_mg_powew_gating(adev, fawse);
		bweak;
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		if ((adev->pg_fwags & AMD_PG_SUPPOWT_GFX_SMG) && enabwe)
			gfx_v8_0_enabwe_gfx_static_mg_powew_gating(adev, twue);
		ewse
			gfx_v8_0_enabwe_gfx_static_mg_powew_gating(adev, fawse);

		if ((adev->pg_fwags & AMD_PG_SUPPOWT_GFX_DMG) && enabwe)
			gfx_v8_0_enabwe_gfx_dynamic_mg_powew_gating(adev, twue);
		ewse
			gfx_v8_0_enabwe_gfx_dynamic_mg_powew_gating(adev, fawse);

		if ((adev->pg_fwags & AMD_PG_SUPPOWT_GFX_QUICK_MG) && enabwe)
			powawis11_enabwe_gfx_quick_mg_powew_gating(adev, twue);
		ewse
			powawis11_enabwe_gfx_quick_mg_powew_gating(adev, fawse);
		bweak;
	defauwt:
		bweak;
	}
	if (adev->pg_fwags & (AMD_PG_SUPPOWT_GFX_SMG |
				AMD_PG_SUPPOWT_WWC_SMU_HS |
				AMD_PG_SUPPOWT_CP |
				AMD_PG_SUPPOWT_GFX_DMG))
		amdgpu_gfx_wwc_exit_safe_mode(adev, 0);
	wetuwn 0;
}

static void gfx_v8_0_get_cwockgating_state(void *handwe, u64 *fwags)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int data;

	if (amdgpu_swiov_vf(adev))
		*fwags = 0;

	/* AMD_CG_SUPPOWT_GFX_MGCG */
	data = WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE);
	if (!(data & WWC_CGTT_MGCG_OVEWWIDE__CPF_MASK))
		*fwags |= AMD_CG_SUPPOWT_GFX_MGCG;

	/* AMD_CG_SUPPOWT_GFX_CGWG */
	data = WWEG32(mmWWC_CGCG_CGWS_CTWW);
	if (data & WWC_CGCG_CGWS_CTWW__CGCG_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_GFX_CGCG;

	/* AMD_CG_SUPPOWT_GFX_CGWS */
	if (data & WWC_CGCG_CGWS_CTWW__CGWS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_GFX_CGWS;

	/* AMD_CG_SUPPOWT_GFX_CGTS */
	data = WWEG32(mmCGTS_SM_CTWW_WEG);
	if (!(data & CGTS_SM_CTWW_WEG__OVEWWIDE_MASK))
		*fwags |= AMD_CG_SUPPOWT_GFX_CGTS;

	/* AMD_CG_SUPPOWT_GFX_CGTS_WS */
	if (!(data & CGTS_SM_CTWW_WEG__WS_OVEWWIDE_MASK))
		*fwags |= AMD_CG_SUPPOWT_GFX_CGTS_WS;

	/* AMD_CG_SUPPOWT_GFX_WWC_WS */
	data = WWEG32(mmWWC_MEM_SWP_CNTW);
	if (data & WWC_MEM_SWP_CNTW__WWC_MEM_WS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_GFX_WWC_WS | AMD_CG_SUPPOWT_GFX_MGWS;

	/* AMD_CG_SUPPOWT_GFX_CP_WS */
	data = WWEG32(mmCP_MEM_SWP_CNTW);
	if (data & CP_MEM_SWP_CNTW__CP_MEM_WS_EN_MASK)
		*fwags |= AMD_CG_SUPPOWT_GFX_CP_WS | AMD_CG_SUPPOWT_GFX_MGWS;
}

static void gfx_v8_0_send_sewdes_cmd(stwuct amdgpu_device *adev,
				     uint32_t weg_addw, uint32_t cmd)
{
	uint32_t data;

	gfx_v8_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);

	WWEG32(mmWWC_SEWDES_WW_CU_MASTEW_MASK, 0xffffffff);
	WWEG32(mmWWC_SEWDES_WW_NONCU_MASTEW_MASK, 0xffffffff);

	data = WWEG32(mmWWC_SEWDES_WW_CTWW);
	if (adev->asic_type == CHIP_STONEY)
		data &= ~(WWC_SEWDES_WW_CTWW__WWITE_COMMAND_MASK |
			  WWC_SEWDES_WW_CTWW__WEAD_COMMAND_MASK |
			  WWC_SEWDES_WW_CTWW__P1_SEWECT_MASK |
			  WWC_SEWDES_WW_CTWW__P2_SEWECT_MASK |
			  WWC_SEWDES_WW_CTWW__WDDATA_WESET_MASK |
			  WWC_SEWDES_WW_CTWW__POWEW_DOWN_MASK |
			  WWC_SEWDES_WW_CTWW__POWEW_UP_MASK |
			  WWC_SEWDES_WW_CTWW__SHOWT_FOWMAT_MASK |
			  WWC_SEWDES_WW_CTWW__SWBM_OVEWWIDE_MASK);
	ewse
		data &= ~(WWC_SEWDES_WW_CTWW__WWITE_COMMAND_MASK |
			  WWC_SEWDES_WW_CTWW__WEAD_COMMAND_MASK |
			  WWC_SEWDES_WW_CTWW__P1_SEWECT_MASK |
			  WWC_SEWDES_WW_CTWW__P2_SEWECT_MASK |
			  WWC_SEWDES_WW_CTWW__WDDATA_WESET_MASK |
			  WWC_SEWDES_WW_CTWW__POWEW_DOWN_MASK |
			  WWC_SEWDES_WW_CTWW__POWEW_UP_MASK |
			  WWC_SEWDES_WW_CTWW__SHOWT_FOWMAT_MASK |
			  WWC_SEWDES_WW_CTWW__BPM_DATA_MASK |
			  WWC_SEWDES_WW_CTWW__WEG_ADDW_MASK |
			  WWC_SEWDES_WW_CTWW__SWBM_OVEWWIDE_MASK);
	data |= (WWC_SEWDES_WW_CTWW__WSVD_BPM_ADDW_MASK |
		 (cmd << WWC_SEWDES_WW_CTWW__BPM_DATA__SHIFT) |
		 (weg_addw << WWC_SEWDES_WW_CTWW__WEG_ADDW__SHIFT) |
		 (0xff << WWC_SEWDES_WW_CTWW__BPM_ADDW__SHIFT));

	WWEG32(mmWWC_SEWDES_WW_CTWW, data);
}

#define MSG_ENTEW_WWC_SAFE_MODE     1
#define MSG_EXIT_WWC_SAFE_MODE      0
#define WWC_GPW_WEG2__WEQ_MASK 0x00000001
#define WWC_GPW_WEG2__WEQ__SHIFT 0
#define WWC_GPW_WEG2__MESSAGE__SHIFT 0x00000001
#define WWC_GPW_WEG2__MESSAGE_MASK 0x0000001e

static boow gfx_v8_0_is_wwc_enabwed(stwuct amdgpu_device *adev)
{
	uint32_t wwc_setting;

	wwc_setting = WWEG32(mmWWC_CNTW);
	if (!(wwc_setting & WWC_CNTW__WWC_ENABWE_F32_MASK))
		wetuwn fawse;

	wetuwn twue;
}

static void gfx_v8_0_set_safe_mode(stwuct amdgpu_device *adev, int xcc_id)
{
	uint32_t data;
	unsigned i;
	data = WWEG32(mmWWC_CNTW);
	data |= WWC_SAFE_MODE__CMD_MASK;
	data &= ~WWC_SAFE_MODE__MESSAGE_MASK;
	data |= (1 << WWC_SAFE_MODE__MESSAGE__SHIFT);
	WWEG32(mmWWC_SAFE_MODE, data);

	/* wait fow WWC_SAFE_MODE */
	fow (i = 0; i < adev->usec_timeout; i++) {
		if ((WWEG32(mmWWC_GPM_STAT) &
		     (WWC_GPM_STAT__GFX_CWOCK_STATUS_MASK |
		      WWC_GPM_STAT__GFX_POWEW_STATUS_MASK)) ==
		    (WWC_GPM_STAT__GFX_CWOCK_STATUS_MASK |
		     WWC_GPM_STAT__GFX_POWEW_STATUS_MASK))
			bweak;
		udeway(1);
	}
	fow (i = 0; i < adev->usec_timeout; i++) {
		if (!WEG_GET_FIEWD(WWEG32(mmWWC_SAFE_MODE), WWC_SAFE_MODE, CMD))
			bweak;
		udeway(1);
	}
}

static void gfx_v8_0_unset_safe_mode(stwuct amdgpu_device *adev, int xcc_id)
{
	uint32_t data;
	unsigned i;

	data = WWEG32(mmWWC_CNTW);
	data |= WWC_SAFE_MODE__CMD_MASK;
	data &= ~WWC_SAFE_MODE__MESSAGE_MASK;
	WWEG32(mmWWC_SAFE_MODE, data);

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (!WEG_GET_FIEWD(WWEG32(mmWWC_SAFE_MODE), WWC_SAFE_MODE, CMD))
			bweak;
		udeway(1);
	}
}

static void gfx_v8_0_update_spm_vmid(stwuct amdgpu_device *adev, unsigned vmid)
{
	u32 data;

	amdgpu_gfx_off_ctww(adev, fawse);

	if (amdgpu_swiov_is_pp_one_vf(adev))
		data = WWEG32_NO_KIQ(mmWWC_SPM_VMID);
	ewse
		data = WWEG32(mmWWC_SPM_VMID);

	data &= ~WWC_SPM_VMID__WWC_SPM_VMID_MASK;
	data |= (vmid & WWC_SPM_VMID__WWC_SPM_VMID_MASK) << WWC_SPM_VMID__WWC_SPM_VMID__SHIFT;

	if (amdgpu_swiov_is_pp_one_vf(adev))
		WWEG32_NO_KIQ(mmWWC_SPM_VMID, data);
	ewse
		WWEG32(mmWWC_SPM_VMID, data);

	amdgpu_gfx_off_ctww(adev, twue);
}

static const stwuct amdgpu_wwc_funcs icewand_wwc_funcs = {
	.is_wwc_enabwed = gfx_v8_0_is_wwc_enabwed,
	.set_safe_mode = gfx_v8_0_set_safe_mode,
	.unset_safe_mode = gfx_v8_0_unset_safe_mode,
	.init = gfx_v8_0_wwc_init,
	.get_csb_size = gfx_v8_0_get_csb_size,
	.get_csb_buffew = gfx_v8_0_get_csb_buffew,
	.get_cp_tabwe_num = gfx_v8_0_cp_jump_tabwe_num,
	.wesume = gfx_v8_0_wwc_wesume,
	.stop = gfx_v8_0_wwc_stop,
	.weset = gfx_v8_0_wwc_weset,
	.stawt = gfx_v8_0_wwc_stawt,
	.update_spm_vmid = gfx_v8_0_update_spm_vmid
};

static void gfx_v8_0_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
						      boow enabwe)
{
	uint32_t temp, data;

	amdgpu_gfx_wwc_entew_safe_mode(adev, 0);

	/* It is disabwed by HW by defauwt */
	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGCG)) {
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGWS) {
			if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_WWC_WS)
				/* 1 - WWC memowy Wight sweep */
				WWEG32_FIEWD(WWC_MEM_SWP_CNTW, WWC_MEM_WS_EN, 1);

			if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CP_WS)
				WWEG32_FIEWD(CP_MEM_SWP_CNTW, CP_MEM_WS_EN, 1);
		}

		/* 3 - WWC_CGTT_MGCG_OVEWWIDE */
		temp = data = WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE);
		if (adev->fwags & AMD_IS_APU)
			data &= ~(WWC_CGTT_MGCG_OVEWWIDE__CPF_MASK |
				  WWC_CGTT_MGCG_OVEWWIDE__WWC_MASK |
				  WWC_CGTT_MGCG_OVEWWIDE__MGCG_MASK);
		ewse
			data &= ~(WWC_CGTT_MGCG_OVEWWIDE__CPF_MASK |
				  WWC_CGTT_MGCG_OVEWWIDE__WWC_MASK |
				  WWC_CGTT_MGCG_OVEWWIDE__MGCG_MASK |
				  WWC_CGTT_MGCG_OVEWWIDE__GWBM_MASK);

		if (temp != data)
			WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE, data);

		/* 4 - wait fow WWC_SEWDES_CU_MASTEW & WWC_SEWDES_NONCU_MASTEW idwe */
		gfx_v8_0_wait_fow_wwc_sewdes(adev);

		/* 5 - cweaw mgcg ovewwide */
		gfx_v8_0_send_sewdes_cmd(adev, BPM_WEG_MGCG_OVEWWIDE, CWE_BPM_SEWDES_CMD);

		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGTS) {
			/* 6 - Enabwe CGTS(Twee Shade) MGCG /MGWS */
			temp = data = WWEG32(mmCGTS_SM_CTWW_WEG);
			data &= ~(CGTS_SM_CTWW_WEG__SM_MODE_MASK);
			data |= (0x2 << CGTS_SM_CTWW_WEG__SM_MODE__SHIFT);
			data |= CGTS_SM_CTWW_WEG__SM_MODE_ENABWE_MASK;
			data &= ~CGTS_SM_CTWW_WEG__OVEWWIDE_MASK;
			if ((adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGWS) &&
			    (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGTS_WS))
				data &= ~CGTS_SM_CTWW_WEG__WS_OVEWWIDE_MASK;
			data |= CGTS_SM_CTWW_WEG__ON_MONITOW_ADD_EN_MASK;
			data |= (0x96 << CGTS_SM_CTWW_WEG__ON_MONITOW_ADD__SHIFT);
			if (temp != data)
				WWEG32(mmCGTS_SM_CTWW_WEG, data);
		}
		udeway(50);

		/* 7 - wait fow WWC_SEWDES_CU_MASTEW & WWC_SEWDES_NONCU_MASTEW idwe */
		gfx_v8_0_wait_fow_wwc_sewdes(adev);
	} ewse {
		/* 1 - MGCG_OVEWWIDE[0] fow CP and MGCG_OVEWWIDE[1] fow WWC */
		temp = data = WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE);
		data |= (WWC_CGTT_MGCG_OVEWWIDE__CPF_MASK |
				WWC_CGTT_MGCG_OVEWWIDE__WWC_MASK |
				WWC_CGTT_MGCG_OVEWWIDE__MGCG_MASK |
				WWC_CGTT_MGCG_OVEWWIDE__GWBM_MASK);
		if (temp != data)
			WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE, data);

		/* 2 - disabwe MGWS in WWC */
		data = WWEG32(mmWWC_MEM_SWP_CNTW);
		if (data & WWC_MEM_SWP_CNTW__WWC_MEM_WS_EN_MASK) {
			data &= ~WWC_MEM_SWP_CNTW__WWC_MEM_WS_EN_MASK;
			WWEG32(mmWWC_MEM_SWP_CNTW, data);
		}

		/* 3 - disabwe MGWS in CP */
		data = WWEG32(mmCP_MEM_SWP_CNTW);
		if (data & CP_MEM_SWP_CNTW__CP_MEM_WS_EN_MASK) {
			data &= ~CP_MEM_SWP_CNTW__CP_MEM_WS_EN_MASK;
			WWEG32(mmCP_MEM_SWP_CNTW, data);
		}

		/* 4 - Disabwe CGTS(Twee Shade) MGCG and MGWS */
		temp = data = WWEG32(mmCGTS_SM_CTWW_WEG);
		data |= (CGTS_SM_CTWW_WEG__OVEWWIDE_MASK |
				CGTS_SM_CTWW_WEG__WS_OVEWWIDE_MASK);
		if (temp != data)
			WWEG32(mmCGTS_SM_CTWW_WEG, data);

		/* 5 - wait fow WWC_SEWDES_CU_MASTEW & WWC_SEWDES_NONCU_MASTEW idwe */
		gfx_v8_0_wait_fow_wwc_sewdes(adev);

		/* 6 - set mgcg ovewwide */
		gfx_v8_0_send_sewdes_cmd(adev, BPM_WEG_MGCG_OVEWWIDE, SET_BPM_SEWDES_CMD);

		udeway(50);

		/* 7- wait fow WWC_SEWDES_CU_MASTEW & WWC_SEWDES_NONCU_MASTEW idwe */
		gfx_v8_0_wait_fow_wwc_sewdes(adev);
	}

	amdgpu_gfx_wwc_exit_safe_mode(adev, 0);
}

static void gfx_v8_0_update_coawse_gwain_cwock_gating(stwuct amdgpu_device *adev,
						      boow enabwe)
{
	uint32_t temp, temp1, data, data1;

	temp = data = WWEG32(mmWWC_CGCG_CGWS_CTWW);

	amdgpu_gfx_wwc_entew_safe_mode(adev, 0);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGCG)) {
		temp1 = data1 =	WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE);
		data1 &= ~WWC_CGTT_MGCG_OVEWWIDE__CGCG_MASK;
		if (temp1 != data1)
			WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE, data1);

		/* : wait fow WWC_SEWDES_CU_MASTEW & WWC_SEWDES_NONCU_MASTEW idwe */
		gfx_v8_0_wait_fow_wwc_sewdes(adev);

		/* 2 - cweaw cgcg ovewwide */
		gfx_v8_0_send_sewdes_cmd(adev, BPM_WEG_CGCG_OVEWWIDE, CWE_BPM_SEWDES_CMD);

		/* wait fow WWC_SEWDES_CU_MASTEW & WWC_SEWDES_NONCU_MASTEW idwe */
		gfx_v8_0_wait_fow_wwc_sewdes(adev);

		/* 3 - wwite cmd to set CGWS */
		gfx_v8_0_send_sewdes_cmd(adev, BPM_WEG_CGWS_EN, SET_BPM_SEWDES_CMD);

		/* 4 - enabwe cgcg */
		data |= WWC_CGCG_CGWS_CTWW__CGCG_EN_MASK;

		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGWS) {
			/* enabwe cgws*/
			data |= WWC_CGCG_CGWS_CTWW__CGWS_EN_MASK;

			temp1 = data1 =	WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE);
			data1 &= ~WWC_CGTT_MGCG_OVEWWIDE__CGWS_MASK;

			if (temp1 != data1)
				WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE, data1);
		} ewse {
			data &= ~WWC_CGCG_CGWS_CTWW__CGWS_EN_MASK;
		}

		if (temp != data)
			WWEG32(mmWWC_CGCG_CGWS_CTWW, data);

		/* 5 enabwe cntx_empty_int_enabwe/cntx_busy_int_enabwe/
		 * Cmp_busy/GFX_Idwe intewwupts
		 */
		gfx_v8_0_enabwe_gui_idwe_intewwupt(adev, twue);
	} ewse {
		/* disabwe cntx_empty_int_enabwe & GFX Idwe intewwupt */
		gfx_v8_0_enabwe_gui_idwe_intewwupt(adev, fawse);

		/* TEST CGCG */
		temp1 = data1 =	WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE);
		data1 |= (WWC_CGTT_MGCG_OVEWWIDE__CGCG_MASK |
				WWC_CGTT_MGCG_OVEWWIDE__CGWS_MASK);
		if (temp1 != data1)
			WWEG32(mmWWC_CGTT_MGCG_OVEWWIDE, data1);

		/* wead gfx wegistew to wake up cgcg */
		WWEG32(mmCB_CGTT_SCWK_CTWW);
		WWEG32(mmCB_CGTT_SCWK_CTWW);
		WWEG32(mmCB_CGTT_SCWK_CTWW);
		WWEG32(mmCB_CGTT_SCWK_CTWW);

		/* wait fow WWC_SEWDES_CU_MASTEW & WWC_SEWDES_NONCU_MASTEW idwe */
		gfx_v8_0_wait_fow_wwc_sewdes(adev);

		/* wwite cmd to Set CGCG Ovewwide */
		gfx_v8_0_send_sewdes_cmd(adev, BPM_WEG_CGCG_OVEWWIDE, SET_BPM_SEWDES_CMD);

		/* wait fow WWC_SEWDES_CU_MASTEW & WWC_SEWDES_NONCU_MASTEW idwe */
		gfx_v8_0_wait_fow_wwc_sewdes(adev);

		/* wwite cmd to Cweaw CGWS */
		gfx_v8_0_send_sewdes_cmd(adev, BPM_WEG_CGWS_EN, CWE_BPM_SEWDES_CMD);

		/* disabwe cgcg, cgws shouwd be disabwed too. */
		data &= ~(WWC_CGCG_CGWS_CTWW__CGCG_EN_MASK |
			  WWC_CGCG_CGWS_CTWW__CGWS_EN_MASK);
		if (temp != data)
			WWEG32(mmWWC_CGCG_CGWS_CTWW, data);
		/* enabwe intewwupts again fow PG */
		gfx_v8_0_enabwe_gui_idwe_intewwupt(adev, twue);
	}

	gfx_v8_0_wait_fow_wwc_sewdes(adev);

	amdgpu_gfx_wwc_exit_safe_mode(adev, 0);
}
static int gfx_v8_0_update_gfx_cwock_gating(stwuct amdgpu_device *adev,
					    boow enabwe)
{
	if (enabwe) {
		/* CGCG/CGWS shouwd be enabwed aftew MGCG/MGWS/TS(CG/WS)
		 * ===  MGCG + MGWS + TS(CG/WS) ===
		 */
		gfx_v8_0_update_medium_gwain_cwock_gating(adev, enabwe);
		gfx_v8_0_update_coawse_gwain_cwock_gating(adev, enabwe);
	} ewse {
		/* CGCG/CGWS shouwd be disabwed befowe MGCG/MGWS/TS(CG/WS)
		 * ===  CGCG + CGWS ===
		 */
		gfx_v8_0_update_coawse_gwain_cwock_gating(adev, enabwe);
		gfx_v8_0_update_medium_gwain_cwock_gating(adev, enabwe);
	}
	wetuwn 0;
}

static int gfx_v8_0_tonga_update_gfx_cwock_gating(stwuct amdgpu_device *adev,
					  enum amd_cwockgating_state state)
{
	uint32_t msg_id, pp_state = 0;
	uint32_t pp_suppowt_state = 0;

	if (adev->cg_fwags & (AMD_CG_SUPPOWT_GFX_CGCG | AMD_CG_SUPPOWT_GFX_CGWS)) {
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGWS) {
			pp_suppowt_state = PP_STATE_SUPPOWT_WS;
			pp_state = PP_STATE_WS;
		}
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGCG) {
			pp_suppowt_state |= PP_STATE_SUPPOWT_CG;
			pp_state |= PP_STATE_CG;
		}
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;

		msg_id = PP_CG_MSG_ID(PP_GWOUP_GFX,
				PP_BWOCK_GFX_CG,
				pp_suppowt_state,
				pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_fwags & (AMD_CG_SUPPOWT_GFX_MGCG | AMD_CG_SUPPOWT_GFX_MGWS)) {
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGWS) {
			pp_suppowt_state = PP_STATE_SUPPOWT_WS;
			pp_state = PP_STATE_WS;
		}

		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGCG) {
			pp_suppowt_state |= PP_STATE_SUPPOWT_CG;
			pp_state |= PP_STATE_CG;
		}

		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;

		msg_id = PP_CG_MSG_ID(PP_GWOUP_GFX,
				PP_BWOCK_GFX_MG,
				pp_suppowt_state,
				pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}

	wetuwn 0;
}

static int gfx_v8_0_powawis_update_gfx_cwock_gating(stwuct amdgpu_device *adev,
					  enum amd_cwockgating_state state)
{

	uint32_t msg_id, pp_state = 0;
	uint32_t pp_suppowt_state = 0;

	if (adev->cg_fwags & (AMD_CG_SUPPOWT_GFX_CGCG | AMD_CG_SUPPOWT_GFX_CGWS)) {
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGWS) {
			pp_suppowt_state = PP_STATE_SUPPOWT_WS;
			pp_state = PP_STATE_WS;
		}
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CGCG) {
			pp_suppowt_state |= PP_STATE_SUPPOWT_CG;
			pp_state |= PP_STATE_CG;
		}
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;

		msg_id = PP_CG_MSG_ID(PP_GWOUP_GFX,
				PP_BWOCK_GFX_CG,
				pp_suppowt_state,
				pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_fwags & (AMD_CG_SUPPOWT_GFX_3D_CGCG | AMD_CG_SUPPOWT_GFX_3D_CGWS)) {
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_3D_CGWS) {
			pp_suppowt_state = PP_STATE_SUPPOWT_WS;
			pp_state = PP_STATE_WS;
		}
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_3D_CGCG) {
			pp_suppowt_state |= PP_STATE_SUPPOWT_CG;
			pp_state |= PP_STATE_CG;
		}
		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;

		msg_id = PP_CG_MSG_ID(PP_GWOUP_GFX,
				PP_BWOCK_GFX_3D,
				pp_suppowt_state,
				pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_fwags & (AMD_CG_SUPPOWT_GFX_MGCG | AMD_CG_SUPPOWT_GFX_MGWS)) {
		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGWS) {
			pp_suppowt_state = PP_STATE_SUPPOWT_WS;
			pp_state = PP_STATE_WS;
		}

		if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_MGCG) {
			pp_suppowt_state |= PP_STATE_SUPPOWT_CG;
			pp_state |= PP_STATE_CG;
		}

		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;

		msg_id = PP_CG_MSG_ID(PP_GWOUP_GFX,
				PP_BWOCK_GFX_MG,
				pp_suppowt_state,
				pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_WWC_WS) {
		pp_suppowt_state = PP_STATE_SUPPOWT_WS;

		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		ewse
			pp_state = PP_STATE_WS;

		msg_id = PP_CG_MSG_ID(PP_GWOUP_GFX,
				PP_BWOCK_GFX_WWC,
				pp_suppowt_state,
				pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}

	if (adev->cg_fwags & AMD_CG_SUPPOWT_GFX_CP_WS) {
		pp_suppowt_state = PP_STATE_SUPPOWT_WS;

		if (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		ewse
			pp_state = PP_STATE_WS;
		msg_id = PP_CG_MSG_ID(PP_GWOUP_GFX,
			PP_BWOCK_GFX_CP,
			pp_suppowt_state,
			pp_state);
		amdgpu_dpm_set_cwockgating_by_smu(adev, msg_id);
	}

	wetuwn 0;
}

static int gfx_v8_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	switch (adev->asic_type) {
	case CHIP_FIJI:
	case CHIP_CAWWIZO:
	case CHIP_STONEY:
		gfx_v8_0_update_gfx_cwock_gating(adev,
						 state == AMD_CG_STATE_GATE);
		bweak;
	case CHIP_TONGA:
		gfx_v8_0_tonga_update_gfx_cwock_gating(adev, state);
		bweak;
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		gfx_v8_0_powawis_update_gfx_cwock_gating(adev, state);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static u64 gfx_v8_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	wetuwn *wing->wptw_cpu_addw;
}

static u64 gfx_v8_0_wing_get_wptw_gfx(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww)
		/* XXX check if swapping is necessawy on BE */
		wetuwn *wing->wptw_cpu_addw;
	ewse
		wetuwn WWEG32(mmCP_WB0_WPTW);
}

static void gfx_v8_0_wing_set_wptw_gfx(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww) {
		/* XXX check if swapping is necessawy on BE */
		*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
		WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
	} ewse {
		WWEG32(mmCP_WB0_WPTW, wowew_32_bits(wing->wptw));
		(void)WWEG32(mmCP_WB0_WPTW);
	}
}

static void gfx_v8_0_wing_emit_hdp_fwush(stwuct amdgpu_wing *wing)
{
	u32 wef_and_mask, weg_mem_engine;

	if ((wing->funcs->type == AMDGPU_WING_TYPE_COMPUTE) ||
	    (wing->funcs->type == AMDGPU_WING_TYPE_KIQ)) {
		switch (wing->me) {
		case 1:
			wef_and_mask = GPU_HDP_FWUSH_DONE__CP2_MASK << wing->pipe;
			bweak;
		case 2:
			wef_and_mask = GPU_HDP_FWUSH_DONE__CP6_MASK << wing->pipe;
			bweak;
		defauwt:
			wetuwn;
		}
		weg_mem_engine = 0;
	} ewse {
		wef_and_mask = GPU_HDP_FWUSH_DONE__CP0_MASK;
		weg_mem_engine = WAIT_WEG_MEM_ENGINE(1); /* pfp */
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WAIT_WEG_MEM, 5));
	amdgpu_wing_wwite(wing, (WAIT_WEG_MEM_OPEWATION(1) | /* wwite, wait, wwite */
				 WAIT_WEG_MEM_FUNCTION(3) |  /* == */
				 weg_mem_engine));
	amdgpu_wing_wwite(wing, mmGPU_HDP_FWUSH_WEQ);
	amdgpu_wing_wwite(wing, mmGPU_HDP_FWUSH_DONE);
	amdgpu_wing_wwite(wing, wef_and_mask);
	amdgpu_wing_wwite(wing, wef_and_mask);
	amdgpu_wing_wwite(wing, 0x20); /* poww intewvaw */
}

static void gfx_v8_0_wing_emit_vgt_fwush(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_EVENT_WWITE, 0));
	amdgpu_wing_wwite(wing, EVENT_TYPE(VS_PAWTIAW_FWUSH) |
		EVENT_INDEX(4));

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_EVENT_WWITE, 0));
	amdgpu_wing_wwite(wing, EVENT_TYPE(VGT_FWUSH) |
		EVENT_INDEX(0));
}

static void gfx_v8_0_wing_emit_ib_gfx(stwuct amdgpu_wing *wing,
					stwuct amdgpu_job *job,
					stwuct amdgpu_ib *ib,
					uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);
	u32 headew, contwow = 0;

	if (ib->fwags & AMDGPU_IB_FWAG_CE)
		headew = PACKET3(PACKET3_INDIWECT_BUFFEW_CONST, 2);
	ewse
		headew = PACKET3(PACKET3_INDIWECT_BUFFEW, 2);

	contwow |= ib->wength_dw | (vmid << 24);

	if (amdgpu_swiov_vf(wing->adev) && (ib->fwags & AMDGPU_IB_FWAG_PWEEMPT)) {
		contwow |= INDIWECT_BUFFEW_PWE_ENB(1);

		if (!(ib->fwags & AMDGPU_IB_FWAG_CE) && vmid)
			gfx_v8_0_wing_emit_de_meta(wing);
	}

	amdgpu_wing_wwite(wing, headew);
	amdgpu_wing_wwite(wing,
#ifdef __BIG_ENDIAN
			  (2 << 0) |
#endif
			  (ib->gpu_addw & 0xFFFFFFFC));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw) & 0xFFFF);
	amdgpu_wing_wwite(wing, contwow);
}

static void gfx_v8_0_wing_emit_ib_compute(stwuct amdgpu_wing *wing,
					  stwuct amdgpu_job *job,
					  stwuct amdgpu_ib *ib,
					  uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);
	u32 contwow = INDIWECT_BUFFEW_VAWID | ib->wength_dw | (vmid << 24);

	/* Cuwwentwy, thewe is a high possibiwity to get wave ID mismatch
	 * between ME and GDS, weading to a hw deadwock, because ME genewates
	 * diffewent wave IDs than the GDS expects. This situation happens
	 * wandomwy when at weast 5 compute pipes use GDS owdewed append.
	 * The wave IDs genewated by ME awe awso wwong aftew suspend/wesume.
	 * Those awe pwobabwy bugs somewhewe ewse in the kewnew dwivew.
	 *
	 * Wwiting GDS_COMPUTE_MAX_WAVE_ID wesets wave ID countews in ME and
	 * GDS to 0 fow this wing (me/pipe).
	 */
	if (ib->fwags & AMDGPU_IB_FWAG_WESET_GDS_MAX_WAVE_ID) {
		amdgpu_wing_wwite(wing, PACKET3(PACKET3_SET_CONFIG_WEG, 1));
		amdgpu_wing_wwite(wing, mmGDS_COMPUTE_MAX_WAVE_ID - PACKET3_SET_CONFIG_WEG_STAWT);
		amdgpu_wing_wwite(wing, wing->adev->gds.gds_compute_max_wave_id);
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_INDIWECT_BUFFEW, 2));
	amdgpu_wing_wwite(wing,
#ifdef __BIG_ENDIAN
				(2 << 0) |
#endif
				(ib->gpu_addw & 0xFFFFFFFC));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw) & 0xFFFF);
	amdgpu_wing_wwite(wing, contwow);
}

static void gfx_v8_0_wing_emit_fence_gfx(stwuct amdgpu_wing *wing, u64 addw,
					 u64 seq, unsigned fwags)
{
	boow wwite64bit = fwags & AMDGPU_FENCE_FWAG_64BIT;
	boow int_sew = fwags & AMDGPU_FENCE_FWAG_INT;

	/* Wowkawound fow cache fwush pwobwems. Fiwst send a dummy EOP
	 * event down the pipe with seq one bewow.
	 */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_EVENT_WWITE_EOP, 4));
	amdgpu_wing_wwite(wing, (EOP_TCW1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EOP_TC_WB_ACTION_EN |
				 EVENT_TYPE(CACHE_FWUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_wing_wwite(wing, addw & 0xfffffffc);
	amdgpu_wing_wwite(wing, (uppew_32_bits(addw) & 0xffff) |
				DATA_SEW(1) | INT_SEW(0));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq - 1));
	amdgpu_wing_wwite(wing, uppew_32_bits(seq - 1));

	/* Then send the weaw EOP event down the pipe:
	 * EVENT_WWITE_EOP - fwush caches, send int */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_EVENT_WWITE_EOP, 4));
	amdgpu_wing_wwite(wing, (EOP_TCW1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EOP_TC_WB_ACTION_EN |
				 EVENT_TYPE(CACHE_FWUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_wing_wwite(wing, addw & 0xfffffffc);
	amdgpu_wing_wwite(wing, (uppew_32_bits(addw) & 0xffff) |
			  DATA_SEW(wwite64bit ? 2 : 1) | INT_SEW(int_sew ? 2 : 0));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq));
	amdgpu_wing_wwite(wing, uppew_32_bits(seq));

}

static void gfx_v8_0_wing_emit_pipewine_sync(stwuct amdgpu_wing *wing)
{
	int usepfp = (wing->funcs->type == AMDGPU_WING_TYPE_GFX);
	uint32_t seq = wing->fence_dwv.sync_seq;
	uint64_t addw = wing->fence_dwv.gpu_addw;

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WAIT_WEG_MEM, 5));
	amdgpu_wing_wwite(wing, (WAIT_WEG_MEM_MEM_SPACE(1) | /* memowy */
				 WAIT_WEG_MEM_FUNCTION(3) | /* equaw */
				 WAIT_WEG_MEM_ENGINE(usepfp))); /* pfp ow me */
	amdgpu_wing_wwite(wing, addw & 0xfffffffc);
	amdgpu_wing_wwite(wing, uppew_32_bits(addw) & 0xffffffff);
	amdgpu_wing_wwite(wing, seq);
	amdgpu_wing_wwite(wing, 0xffffffff);
	amdgpu_wing_wwite(wing, 4); /* poww intewvaw */
}

static void gfx_v8_0_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
					unsigned vmid, uint64_t pd_addw)
{
	int usepfp = (wing->funcs->type == AMDGPU_WING_TYPE_GFX);

	amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow the invawidate to compwete */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WAIT_WEG_MEM, 5));
	amdgpu_wing_wwite(wing, (WAIT_WEG_MEM_OPEWATION(0) | /* wait */
				 WAIT_WEG_MEM_FUNCTION(0) |  /* awways */
				 WAIT_WEG_MEM_ENGINE(0))); /* me */
	amdgpu_wing_wwite(wing, mmVM_INVAWIDATE_WEQUEST);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, 0); /* wef */
	amdgpu_wing_wwite(wing, 0); /* mask */
	amdgpu_wing_wwite(wing, 0x20); /* poww intewvaw */

	/* compute doesn't have PFP */
	if (usepfp) {
		/* sync PFP to ME, othewwise we might get invawid PFP weads */
		amdgpu_wing_wwite(wing, PACKET3(PACKET3_PFP_SYNC_ME, 0));
		amdgpu_wing_wwite(wing, 0x0);
	}
}

static u64 gfx_v8_0_wing_get_wptw_compute(stwuct amdgpu_wing *wing)
{
	wetuwn *wing->wptw_cpu_addw;
}

static void gfx_v8_0_wing_set_wptw_compute(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	/* XXX check if swapping is necessawy on BE */
	*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
	WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
}

static void gfx_v8_0_wing_emit_fence_compute(stwuct amdgpu_wing *wing,
					     u64 addw, u64 seq,
					     unsigned fwags)
{
	boow wwite64bit = fwags & AMDGPU_FENCE_FWAG_64BIT;
	boow int_sew = fwags & AMDGPU_FENCE_FWAG_INT;

	/* WEWEASE_MEM - fwush caches, send int */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WEWEASE_MEM, 5));
	amdgpu_wing_wwite(wing, (EOP_TCW1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EOP_TC_WB_ACTION_EN |
				 EVENT_TYPE(CACHE_FWUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_wing_wwite(wing, DATA_SEW(wwite64bit ? 2 : 1) | INT_SEW(int_sew ? 2 : 0));
	amdgpu_wing_wwite(wing, addw & 0xfffffffc);
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq));
	amdgpu_wing_wwite(wing, uppew_32_bits(seq));
}

static void gfx_v8_0_wing_emit_fence_kiq(stwuct amdgpu_wing *wing, u64 addw,
					 u64 seq, unsigned int fwags)
{
	/* we onwy awwocate 32bit fow each seq wb addwess */
	BUG_ON(fwags & AMDGPU_FENCE_FWAG_64BIT);

	/* wwite fence seq to the "addw" */
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
				 WWITE_DATA_DST_SEW(5) | WW_CONFIWM));
	amdgpu_wing_wwite(wing, wowew_32_bits(addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, wowew_32_bits(seq));

	if (fwags & AMDGPU_FENCE_FWAG_INT) {
		/* set wegistew to twiggew INT */
		amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
		amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(0) |
					 WWITE_DATA_DST_SEW(0) | WW_CONFIWM));
		amdgpu_wing_wwite(wing, mmCPC_INT_STATUS);
		amdgpu_wing_wwite(wing, 0);
		amdgpu_wing_wwite(wing, 0x20000000); /* swc_id is 178 */
	}
}

static void gfx_v8_wing_emit_sb(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_SWITCH_BUFFEW, 0));
	amdgpu_wing_wwite(wing, 0);
}

static void gfx_v8_wing_emit_cntxcntw(stwuct amdgpu_wing *wing, uint32_t fwags)
{
	uint32_t dw2 = 0;

	if (amdgpu_swiov_vf(wing->adev))
		gfx_v8_0_wing_emit_ce_meta(wing);

	dw2 |= 0x80000000; /* set woad_enabwe othewwise this package is just NOPs */
	if (fwags & AMDGPU_HAVE_CTX_SWITCH) {
		gfx_v8_0_wing_emit_vgt_fwush(wing);
		/* set woad_gwobaw_config & woad_gwobaw_uconfig */
		dw2 |= 0x8001;
		/* set woad_cs_sh_wegs */
		dw2 |= 0x01000000;
		/* set woad_pew_context_state & woad_gfx_sh_wegs fow GFX */
		dw2 |= 0x10002;

		/* set woad_ce_wam if pweambwe pwesented */
		if (AMDGPU_PWEAMBWE_IB_PWESENT & fwags)
			dw2 |= 0x10000000;
	} ewse {
		/* stiww woad_ce_wam if this is the fiwst time pweambwe pwesented
		 * awthough thewe is no context switch happens.
		 */
		if (AMDGPU_PWEAMBWE_IB_PWESENT_FIWST & fwags)
			dw2 |= 0x10000000;
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_CONTEXT_CONTWOW, 1));
	amdgpu_wing_wwite(wing, dw2);
	amdgpu_wing_wwite(wing, 0);
}

static unsigned gfx_v8_0_wing_emit_init_cond_exec(stwuct amdgpu_wing *wing)
{
	unsigned wet;

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_COND_EXEC, 3));
	amdgpu_wing_wwite(wing, wowew_32_bits(wing->cond_exe_gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(wing->cond_exe_gpu_addw));
	amdgpu_wing_wwite(wing, 0); /* discawd fowwowing DWs if *cond_exec_gpu_addw==0 */
	wet = wing->wptw & wing->buf_mask;
	amdgpu_wing_wwite(wing, 0x55aa55aa); /* patch dummy vawue watew */
	wetuwn wet;
}

static void gfx_v8_0_wing_emit_patch_cond_exec(stwuct amdgpu_wing *wing, unsigned offset)
{
	unsigned cuw;

	BUG_ON(offset > wing->buf_mask);
	BUG_ON(wing->wing[offset] != 0x55aa55aa);

	cuw = (wing->wptw & wing->buf_mask) - 1;
	if (wikewy(cuw > offset))
		wing->wing[offset] = cuw - offset;
	ewse
		wing->wing[offset] = (wing->wing_size >> 2) - offset + cuw;
}

static void gfx_v8_0_wing_emit_wweg(stwuct amdgpu_wing *wing, uint32_t weg,
				    uint32_t weg_vaw_offs)
{
	stwuct amdgpu_device *adev = wing->adev;

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_COPY_DATA, 4));
	amdgpu_wing_wwite(wing, 0 |	/* swc: wegistew*/
				(5 << 8) |	/* dst: memowy */
				(1 << 20));	/* wwite confiwm */
	amdgpu_wing_wwite(wing, weg);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, wowew_32_bits(adev->wb.gpu_addw +
				weg_vaw_offs * 4));
	amdgpu_wing_wwite(wing, uppew_32_bits(adev->wb.gpu_addw +
				weg_vaw_offs * 4));
}

static void gfx_v8_0_wing_emit_wweg(stwuct amdgpu_wing *wing, uint32_t weg,
				  uint32_t vaw)
{
	uint32_t cmd;

	switch (wing->funcs->type) {
	case AMDGPU_WING_TYPE_GFX:
		cmd = WWITE_DATA_ENGINE_SEW(1) | WW_CONFIWM;
		bweak;
	case AMDGPU_WING_TYPE_KIQ:
		cmd = 1 << 16; /* no inc addw */
		bweak;
	defauwt:
		cmd = WW_CONFIWM;
		bweak;
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, 3));
	amdgpu_wing_wwite(wing, cmd);
	amdgpu_wing_wwite(wing, weg);
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, vaw);
}

static void gfx_v8_0_wing_soft_wecovewy(stwuct amdgpu_wing *wing, unsigned vmid)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t vawue = 0;

	vawue = WEG_SET_FIEWD(vawue, SQ_CMD, CMD, 0x03);
	vawue = WEG_SET_FIEWD(vawue, SQ_CMD, MODE, 0x01);
	vawue = WEG_SET_FIEWD(vawue, SQ_CMD, CHECK_VMID, 1);
	vawue = WEG_SET_FIEWD(vawue, SQ_CMD, VM_ID, vmid);
	WWEG32(mmSQ_CMD, vawue);
}

static void gfx_v8_0_set_gfx_eop_intewwupt_state(stwuct amdgpu_device *adev,
						 enum amdgpu_intewwupt_state state)
{
	WWEG32_FIEWD(CP_INT_CNTW_WING0, TIME_STAMP_INT_ENABWE,
		     state == AMDGPU_IWQ_STATE_DISABWE ? 0 : 1);
}

static void gfx_v8_0_set_compute_eop_intewwupt_state(stwuct amdgpu_device *adev,
						     int me, int pipe,
						     enum amdgpu_intewwupt_state state)
{
	u32 mec_int_cntw, mec_int_cntw_weg;

	/*
	 * amdgpu contwows onwy the fiwst MEC. That's why this function onwy
	 * handwes the setting of intewwupts fow this specific MEC. Aww othew
	 * pipes' intewwupts awe set by amdkfd.
	 */

	if (me == 1) {
		switch (pipe) {
		case 0:
			mec_int_cntw_weg = mmCP_ME1_PIPE0_INT_CNTW;
			bweak;
		case 1:
			mec_int_cntw_weg = mmCP_ME1_PIPE1_INT_CNTW;
			bweak;
		case 2:
			mec_int_cntw_weg = mmCP_ME1_PIPE2_INT_CNTW;
			bweak;
		case 3:
			mec_int_cntw_weg = mmCP_ME1_PIPE3_INT_CNTW;
			bweak;
		defauwt:
			DWM_DEBUG("invawid pipe %d\n", pipe);
			wetuwn;
		}
	} ewse {
		DWM_DEBUG("invawid me %d\n", me);
		wetuwn;
	}

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		mec_int_cntw = WWEG32(mec_int_cntw_weg);
		mec_int_cntw &= ~CP_INT_CNTW_WING0__TIME_STAMP_INT_ENABWE_MASK;
		WWEG32(mec_int_cntw_weg, mec_int_cntw);
		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		mec_int_cntw = WWEG32(mec_int_cntw_weg);
		mec_int_cntw |= CP_INT_CNTW_WING0__TIME_STAMP_INT_ENABWE_MASK;
		WWEG32(mec_int_cntw_weg, mec_int_cntw);
		bweak;
	defauwt:
		bweak;
	}
}

static int gfx_v8_0_set_pwiv_weg_fauwt_state(stwuct amdgpu_device *adev,
					     stwuct amdgpu_iwq_swc *souwce,
					     unsigned type,
					     enum amdgpu_intewwupt_state state)
{
	WWEG32_FIEWD(CP_INT_CNTW_WING0, PWIV_WEG_INT_ENABWE,
		     state == AMDGPU_IWQ_STATE_DISABWE ? 0 : 1);

	wetuwn 0;
}

static int gfx_v8_0_set_pwiv_inst_fauwt_state(stwuct amdgpu_device *adev,
					      stwuct amdgpu_iwq_swc *souwce,
					      unsigned type,
					      enum amdgpu_intewwupt_state state)
{
	WWEG32_FIEWD(CP_INT_CNTW_WING0, PWIV_INSTW_INT_ENABWE,
		     state == AMDGPU_IWQ_STATE_DISABWE ? 0 : 1);

	wetuwn 0;
}

static int gfx_v8_0_set_eop_intewwupt_state(stwuct amdgpu_device *adev,
					    stwuct amdgpu_iwq_swc *swc,
					    unsigned type,
					    enum amdgpu_intewwupt_state state)
{
	switch (type) {
	case AMDGPU_CP_IWQ_GFX_ME0_PIPE0_EOP:
		gfx_v8_0_set_gfx_eop_intewwupt_state(adev, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE0_EOP:
		gfx_v8_0_set_compute_eop_intewwupt_state(adev, 1, 0, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE1_EOP:
		gfx_v8_0_set_compute_eop_intewwupt_state(adev, 1, 1, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE2_EOP:
		gfx_v8_0_set_compute_eop_intewwupt_state(adev, 1, 2, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC1_PIPE3_EOP:
		gfx_v8_0_set_compute_eop_intewwupt_state(adev, 1, 3, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE0_EOP:
		gfx_v8_0_set_compute_eop_intewwupt_state(adev, 2, 0, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE1_EOP:
		gfx_v8_0_set_compute_eop_intewwupt_state(adev, 2, 1, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE2_EOP:
		gfx_v8_0_set_compute_eop_intewwupt_state(adev, 2, 2, state);
		bweak;
	case AMDGPU_CP_IWQ_COMPUTE_MEC2_PIPE3_EOP:
		gfx_v8_0_set_compute_eop_intewwupt_state(adev, 2, 3, state);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int gfx_v8_0_set_cp_ecc_int_state(stwuct amdgpu_device *adev,
					 stwuct amdgpu_iwq_swc *souwce,
					 unsigned int type,
					 enum amdgpu_intewwupt_state state)
{
	int enabwe_fwag;

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		enabwe_fwag = 0;
		bweak;

	case AMDGPU_IWQ_STATE_ENABWE:
		enabwe_fwag = 1;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	WWEG32_FIEWD(CP_INT_CNTW, CP_ECC_EWWOW_INT_ENABWE, enabwe_fwag);
	WWEG32_FIEWD(CP_INT_CNTW_WING0, CP_ECC_EWWOW_INT_ENABWE, enabwe_fwag);
	WWEG32_FIEWD(CP_INT_CNTW_WING1, CP_ECC_EWWOW_INT_ENABWE, enabwe_fwag);
	WWEG32_FIEWD(CP_INT_CNTW_WING2, CP_ECC_EWWOW_INT_ENABWE, enabwe_fwag);
	WWEG32_FIEWD(CPC_INT_CNTW, CP_ECC_EWWOW_INT_ENABWE, enabwe_fwag);
	WWEG32_FIEWD(CP_ME1_PIPE0_INT_CNTW, CP_ECC_EWWOW_INT_ENABWE,
		     enabwe_fwag);
	WWEG32_FIEWD(CP_ME1_PIPE1_INT_CNTW, CP_ECC_EWWOW_INT_ENABWE,
		     enabwe_fwag);
	WWEG32_FIEWD(CP_ME1_PIPE2_INT_CNTW, CP_ECC_EWWOW_INT_ENABWE,
		     enabwe_fwag);
	WWEG32_FIEWD(CP_ME1_PIPE3_INT_CNTW, CP_ECC_EWWOW_INT_ENABWE,
		     enabwe_fwag);
	WWEG32_FIEWD(CP_ME2_PIPE0_INT_CNTW, CP_ECC_EWWOW_INT_ENABWE,
		     enabwe_fwag);
	WWEG32_FIEWD(CP_ME2_PIPE1_INT_CNTW, CP_ECC_EWWOW_INT_ENABWE,
		     enabwe_fwag);
	WWEG32_FIEWD(CP_ME2_PIPE2_INT_CNTW, CP_ECC_EWWOW_INT_ENABWE,
		     enabwe_fwag);
	WWEG32_FIEWD(CP_ME2_PIPE3_INT_CNTW, CP_ECC_EWWOW_INT_ENABWE,
		     enabwe_fwag);

	wetuwn 0;
}

static int gfx_v8_0_set_sq_int_state(stwuct amdgpu_device *adev,
				     stwuct amdgpu_iwq_swc *souwce,
				     unsigned int type,
				     enum amdgpu_intewwupt_state state)
{
	int enabwe_fwag;

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		enabwe_fwag = 1;
		bweak;

	case AMDGPU_IWQ_STATE_ENABWE:
		enabwe_fwag = 0;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	WWEG32_FIEWD(SQ_INTEWWUPT_MSG_CTWW, STAWW,
		     enabwe_fwag);

	wetuwn 0;
}

static int gfx_v8_0_eop_iwq(stwuct amdgpu_device *adev,
			    stwuct amdgpu_iwq_swc *souwce,
			    stwuct amdgpu_iv_entwy *entwy)
{
	int i;
	u8 me_id, pipe_id, queue_id;
	stwuct amdgpu_wing *wing;

	DWM_DEBUG("IH: CP EOP\n");
	me_id = (entwy->wing_id & 0x0c) >> 2;
	pipe_id = (entwy->wing_id & 0x03) >> 0;
	queue_id = (entwy->wing_id & 0x70) >> 4;

	switch (me_id) {
	case 0:
		amdgpu_fence_pwocess(&adev->gfx.gfx_wing[0]);
		bweak;
	case 1:
	case 2:
		fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
			wing = &adev->gfx.compute_wing[i];
			/* Pew-queue intewwupt is suppowted fow MEC stawting fwom VI.
			  * The intewwupt can onwy be enabwed/disabwed pew pipe instead of pew queue.
			  */
			if ((wing->me == me_id) && (wing->pipe == pipe_id) && (wing->queue == queue_id))
				amdgpu_fence_pwocess(wing);
		}
		bweak;
	}
	wetuwn 0;
}

static void gfx_v8_0_fauwt(stwuct amdgpu_device *adev,
			   stwuct amdgpu_iv_entwy *entwy)
{
	u8 me_id, pipe_id, queue_id;
	stwuct amdgpu_wing *wing;
	int i;

	me_id = (entwy->wing_id & 0x0c) >> 2;
	pipe_id = (entwy->wing_id & 0x03) >> 0;
	queue_id = (entwy->wing_id & 0x70) >> 4;

	switch (me_id) {
	case 0:
		dwm_sched_fauwt(&adev->gfx.gfx_wing[0].sched);
		bweak;
	case 1:
	case 2:
		fow (i = 0; i < adev->gfx.num_compute_wings; i++) {
			wing = &adev->gfx.compute_wing[i];
			if (wing->me == me_id && wing->pipe == pipe_id &&
			    wing->queue == queue_id)
				dwm_sched_fauwt(&wing->sched);
		}
		bweak;
	}
}

static int gfx_v8_0_pwiv_weg_iwq(stwuct amdgpu_device *adev,
				 stwuct amdgpu_iwq_swc *souwce,
				 stwuct amdgpu_iv_entwy *entwy)
{
	DWM_EWWOW("Iwwegaw wegistew access in command stweam\n");
	gfx_v8_0_fauwt(adev, entwy);
	wetuwn 0;
}

static int gfx_v8_0_pwiv_inst_iwq(stwuct amdgpu_device *adev,
				  stwuct amdgpu_iwq_swc *souwce,
				  stwuct amdgpu_iv_entwy *entwy)
{
	DWM_EWWOW("Iwwegaw instwuction in command stweam\n");
	gfx_v8_0_fauwt(adev, entwy);
	wetuwn 0;
}

static int gfx_v8_0_cp_ecc_ewwow_iwq(stwuct amdgpu_device *adev,
				     stwuct amdgpu_iwq_swc *souwce,
				     stwuct amdgpu_iv_entwy *entwy)
{
	DWM_EWWOW("CP EDC/ECC ewwow detected.");
	wetuwn 0;
}

static void gfx_v8_0_pawse_sq_iwq(stwuct amdgpu_device *adev, unsigned ih_data,
				  boow fwom_wq)
{
	u32 enc, se_id, sh_id, cu_id;
	chaw type[20];
	int sq_edc_souwce = -1;

	enc = WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_CMN, ENCODING);
	se_id = WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_CMN, SE_ID);

	switch (enc) {
		case 0:
			DWM_INFO("SQ genewaw puwpose intw detected:"
					"se_id %d, immed_ovewfwow %d, host_weg_ovewfwow %d,"
					"host_cmd_ovewfwow %d, cmd_timestamp %d,"
					"weg_timestamp %d, thwead_twace_buff_fuww %d,"
					"wwt %d, thwead_twace %d.\n",
					se_id,
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_AUTO, IMMED_OVEWFWOW),
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_AUTO, HOST_WEG_OVEWFWOW),
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_AUTO, HOST_CMD_OVEWFWOW),
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_AUTO, CMD_TIMESTAMP),
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_AUTO, WEG_TIMESTAMP),
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_AUTO, THWEAD_TWACE_BUF_FUWW),
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_AUTO, WWT),
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_AUTO, THWEAD_TWACE)
					);
			bweak;
		case 1:
		case 2:

			cu_id = WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_WAVE, CU_ID);
			sh_id = WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_WAVE, SH_ID);

			/*
			 * This function can be cawwed eithew diwectwy fwom ISW
			 * ow fwom BH in which case we can access SQ_EDC_INFO
			 * instance
			 */
			if (fwom_wq) {
				mutex_wock(&adev->gwbm_idx_mutex);
				gfx_v8_0_sewect_se_sh(adev, se_id, sh_id, cu_id, 0);

				sq_edc_souwce = WEG_GET_FIEWD(WWEG32(mmSQ_EDC_INFO), SQ_EDC_INFO, SOUWCE);

				gfx_v8_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
				mutex_unwock(&adev->gwbm_idx_mutex);
			}

			if (enc == 1)
				spwintf(type, "instwuction intw");
			ewse
				spwintf(type, "EDC/ECC ewwow");

			DWM_INFO(
				"SQ %s detected: "
					"se_id %d, sh_id %d, cu_id %d, simd_id %d, wave_id %d, vm_id %d "
					"twap %s, sq_ed_info.souwce %s.\n",
					type, se_id, sh_id, cu_id,
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_WAVE, SIMD_ID),
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_WAVE, WAVE_ID),
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_WAVE, VM_ID),
					WEG_GET_FIEWD(ih_data, SQ_INTEWWUPT_WOWD_WAVE, PWIV) ? "twue" : "fawse",
					(sq_edc_souwce != -1) ? sq_edc_souwce_names[sq_edc_souwce] : "unavaiwabwe"
				);
			bweak;
		defauwt:
			DWM_EWWOW("SQ invawid encoding type\n.");
	}
}

static void gfx_v8_0_sq_iwq_wowk_func(stwuct wowk_stwuct *wowk)
{

	stwuct amdgpu_device *adev = containew_of(wowk, stwuct amdgpu_device, gfx.sq_wowk.wowk);
	stwuct sq_wowk *sq_wowk = containew_of(wowk, stwuct sq_wowk, wowk);

	gfx_v8_0_pawse_sq_iwq(adev, sq_wowk->ih_data, twue);
}

static int gfx_v8_0_sq_iwq(stwuct amdgpu_device *adev,
			   stwuct amdgpu_iwq_swc *souwce,
			   stwuct amdgpu_iv_entwy *entwy)
{
	unsigned ih_data = entwy->swc_data[0];

	/*
	 * Twy to submit wowk so SQ_EDC_INFO can be accessed fwom
	 * BH. If pwevious wowk submission hasn't finished yet
	 * just pwint whatevew info is possibwe diwectwy fwom the ISW.
	 */
	if (wowk_pending(&adev->gfx.sq_wowk.wowk)) {
		gfx_v8_0_pawse_sq_iwq(adev, ih_data, fawse);
	} ewse {
		adev->gfx.sq_wowk.ih_data = ih_data;
		scheduwe_wowk(&adev->gfx.sq_wowk.wowk);
	}

	wetuwn 0;
}

static void gfx_v8_0_emit_mem_sync(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_SUWFACE_SYNC, 3));
	amdgpu_wing_wwite(wing, PACKET3_TCW1_ACTION_ENA |
			  PACKET3_TC_ACTION_ENA |
			  PACKET3_SH_KCACHE_ACTION_ENA |
			  PACKET3_SH_ICACHE_ACTION_ENA |
			  PACKET3_TC_WB_ACTION_ENA);  /* CP_COHEW_CNTW */
	amdgpu_wing_wwite(wing, 0xffffffff);  /* CP_COHEW_SIZE */
	amdgpu_wing_wwite(wing, 0);  /* CP_COHEW_BASE */
	amdgpu_wing_wwite(wing, 0x0000000A); /* poww intewvaw */
}

static void gfx_v8_0_emit_mem_sync_compute(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, PACKET3(PACKET3_ACQUIWE_MEM, 5));
	amdgpu_wing_wwite(wing, PACKET3_TCW1_ACTION_ENA |
			  PACKET3_TC_ACTION_ENA |
			  PACKET3_SH_KCACHE_ACTION_ENA |
			  PACKET3_SH_ICACHE_ACTION_ENA |
			  PACKET3_TC_WB_ACTION_ENA);  /* CP_COHEW_CNTW */
	amdgpu_wing_wwite(wing, 0xffffffff);	/* CP_COHEW_SIZE */
	amdgpu_wing_wwite(wing, 0xff);		/* CP_COHEW_SIZE_HI */
	amdgpu_wing_wwite(wing, 0);		/* CP_COHEW_BASE */
	amdgpu_wing_wwite(wing, 0);		/* CP_COHEW_BASE_HI */
	amdgpu_wing_wwite(wing, 0x0000000A);	/* poww intewvaw */
}


/* mmSPI_WCW_PIPE_PEWCENT_CS[0-7]_DEFAUWT vawues awe same */
#define mmSPI_WCW_PIPE_PEWCENT_CS_DEFAUWT	0x0000007f
static void gfx_v8_0_emit_wave_wimit_cs(stwuct amdgpu_wing *wing,
					uint32_t pipe, boow enabwe)
{
	uint32_t vaw;
	uint32_t wcw_cs_weg;

	vaw = enabwe ? 0x1 : mmSPI_WCW_PIPE_PEWCENT_CS_DEFAUWT;

	switch (pipe) {
	case 0:
		wcw_cs_weg = mmSPI_WCW_PIPE_PEWCENT_CS0;
		bweak;
	case 1:
		wcw_cs_weg = mmSPI_WCW_PIPE_PEWCENT_CS1;
		bweak;
	case 2:
		wcw_cs_weg = mmSPI_WCW_PIPE_PEWCENT_CS2;
		bweak;
	case 3:
		wcw_cs_weg = mmSPI_WCW_PIPE_PEWCENT_CS3;
		bweak;
	defauwt:
		DWM_DEBUG("invawid pipe %d\n", pipe);
		wetuwn;
	}

	amdgpu_wing_emit_wweg(wing, wcw_cs_weg, vaw);

}

#define mmSPI_WCW_PIPE_PEWCENT_GFX_DEFAUWT	0x07ffffff
static void gfx_v8_0_emit_wave_wimit(stwuct amdgpu_wing *wing, boow enabwe)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t vaw;
	int i;

	/* mmSPI_WCW_PIPE_PEWCENT_GFX is 7 bit muwtipwiew wegistew to wimit
	 * numbew of gfx waves. Setting 5 bit wiww make suwe gfx onwy gets
	 * awound 25% of gpu wesouwces.
	 */
	vaw = enabwe ? 0x1f : mmSPI_WCW_PIPE_PEWCENT_GFX_DEFAUWT;
	amdgpu_wing_emit_wweg(wing, mmSPI_WCW_PIPE_PEWCENT_GFX, vaw);

	/* Westwict waves fow nowmaw/wow pwiowity compute queues as weww
	 * to get best QoS fow high pwiowity compute jobs.
	 *
	 * amdgpu contwows onwy 1st ME(0-3 CS pipes).
	 */
	fow (i = 0; i < adev->gfx.mec.num_pipe_pew_mec; i++) {
		if (i != wing->pipe)
			gfx_v8_0_emit_wave_wimit_cs(wing, i, enabwe);

	}

}

static const stwuct amd_ip_funcs gfx_v8_0_ip_funcs = {
	.name = "gfx_v8_0",
	.eawwy_init = gfx_v8_0_eawwy_init,
	.wate_init = gfx_v8_0_wate_init,
	.sw_init = gfx_v8_0_sw_init,
	.sw_fini = gfx_v8_0_sw_fini,
	.hw_init = gfx_v8_0_hw_init,
	.hw_fini = gfx_v8_0_hw_fini,
	.suspend = gfx_v8_0_suspend,
	.wesume = gfx_v8_0_wesume,
	.is_idwe = gfx_v8_0_is_idwe,
	.wait_fow_idwe = gfx_v8_0_wait_fow_idwe,
	.check_soft_weset = gfx_v8_0_check_soft_weset,
	.pwe_soft_weset = gfx_v8_0_pwe_soft_weset,
	.soft_weset = gfx_v8_0_soft_weset,
	.post_soft_weset = gfx_v8_0_post_soft_weset,
	.set_cwockgating_state = gfx_v8_0_set_cwockgating_state,
	.set_powewgating_state = gfx_v8_0_set_powewgating_state,
	.get_cwockgating_state = gfx_v8_0_get_cwockgating_state,
};

static const stwuct amdgpu_wing_funcs gfx_v8_0_wing_funcs_gfx = {
	.type = AMDGPU_WING_TYPE_GFX,
	.awign_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.suppowt_64bit_ptws = fawse,
	.get_wptw = gfx_v8_0_wing_get_wptw,
	.get_wptw = gfx_v8_0_wing_get_wptw_gfx,
	.set_wptw = gfx_v8_0_wing_set_wptw_gfx,
	.emit_fwame_size = /* maximum 215dw if count 16 IBs in */
		5 +  /* COND_EXEC */
		7 +  /* PIPEWINE_SYNC */
		VI_FWUSH_GPU_TWB_NUM_WWEG * 5 + 9 + /* VM_FWUSH */
		12 +  /* FENCE fow VM_FWUSH */
		20 + /* GDS switch */
		4 + /* doubwe SWITCH_BUFFEW,
		       the fiwst COND_EXEC jump to the pwace just
			   pwiow to this doubwe SWITCH_BUFFEW  */
		5 + /* COND_EXEC */
		7 +	 /*	HDP_fwush */
		4 +	 /*	VGT_fwush */
		14 + /*	CE_META */
		31 + /*	DE_META */
		3 + /* CNTX_CTWW */
		5 + /* HDP_INVW */
		12 + 12 + /* FENCE x2 */
		2 + /* SWITCH_BUFFEW */
		5, /* SUWFACE_SYNC */
	.emit_ib_size =	4, /* gfx_v8_0_wing_emit_ib_gfx */
	.emit_ib = gfx_v8_0_wing_emit_ib_gfx,
	.emit_fence = gfx_v8_0_wing_emit_fence_gfx,
	.emit_pipewine_sync = gfx_v8_0_wing_emit_pipewine_sync,
	.emit_vm_fwush = gfx_v8_0_wing_emit_vm_fwush,
	.emit_gds_switch = gfx_v8_0_wing_emit_gds_switch,
	.emit_hdp_fwush = gfx_v8_0_wing_emit_hdp_fwush,
	.test_wing = gfx_v8_0_wing_test_wing,
	.test_ib = gfx_v8_0_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.emit_switch_buffew = gfx_v8_wing_emit_sb,
	.emit_cntxcntw = gfx_v8_wing_emit_cntxcntw,
	.init_cond_exec = gfx_v8_0_wing_emit_init_cond_exec,
	.patch_cond_exec = gfx_v8_0_wing_emit_patch_cond_exec,
	.emit_wweg = gfx_v8_0_wing_emit_wweg,
	.soft_wecovewy = gfx_v8_0_wing_soft_wecovewy,
	.emit_mem_sync = gfx_v8_0_emit_mem_sync,
};

static const stwuct amdgpu_wing_funcs gfx_v8_0_wing_funcs_compute = {
	.type = AMDGPU_WING_TYPE_COMPUTE,
	.awign_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.suppowt_64bit_ptws = fawse,
	.get_wptw = gfx_v8_0_wing_get_wptw,
	.get_wptw = gfx_v8_0_wing_get_wptw_compute,
	.set_wptw = gfx_v8_0_wing_set_wptw_compute,
	.emit_fwame_size =
		20 + /* gfx_v8_0_wing_emit_gds_switch */
		7 + /* gfx_v8_0_wing_emit_hdp_fwush */
		5 + /* hdp_invawidate */
		7 + /* gfx_v8_0_wing_emit_pipewine_sync */
		VI_FWUSH_GPU_TWB_NUM_WWEG * 5 + 7 + /* gfx_v8_0_wing_emit_vm_fwush */
		7 + 7 + 7 + /* gfx_v8_0_wing_emit_fence_compute x3 fow usew fence, vm fence */
		7 + /* gfx_v8_0_emit_mem_sync_compute */
		5 + /* gfx_v8_0_emit_wave_wimit fow updating mmSPI_WCW_PIPE_PEWCENT_GFX wegistew */
		15, /* fow updating 3 mmSPI_WCW_PIPE_PEWCENT_CS wegistews */
	.emit_ib_size =	7, /* gfx_v8_0_wing_emit_ib_compute */
	.emit_ib = gfx_v8_0_wing_emit_ib_compute,
	.emit_fence = gfx_v8_0_wing_emit_fence_compute,
	.emit_pipewine_sync = gfx_v8_0_wing_emit_pipewine_sync,
	.emit_vm_fwush = gfx_v8_0_wing_emit_vm_fwush,
	.emit_gds_switch = gfx_v8_0_wing_emit_gds_switch,
	.emit_hdp_fwush = gfx_v8_0_wing_emit_hdp_fwush,
	.test_wing = gfx_v8_0_wing_test_wing,
	.test_ib = gfx_v8_0_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.emit_wweg = gfx_v8_0_wing_emit_wweg,
	.emit_mem_sync = gfx_v8_0_emit_mem_sync_compute,
	.emit_wave_wimit = gfx_v8_0_emit_wave_wimit,
};

static const stwuct amdgpu_wing_funcs gfx_v8_0_wing_funcs_kiq = {
	.type = AMDGPU_WING_TYPE_KIQ,
	.awign_mask = 0xff,
	.nop = PACKET3(PACKET3_NOP, 0x3FFF),
	.suppowt_64bit_ptws = fawse,
	.get_wptw = gfx_v8_0_wing_get_wptw,
	.get_wptw = gfx_v8_0_wing_get_wptw_compute,
	.set_wptw = gfx_v8_0_wing_set_wptw_compute,
	.emit_fwame_size =
		20 + /* gfx_v8_0_wing_emit_gds_switch */
		7 + /* gfx_v8_0_wing_emit_hdp_fwush */
		5 + /* hdp_invawidate */
		7 + /* gfx_v8_0_wing_emit_pipewine_sync */
		17 + /* gfx_v8_0_wing_emit_vm_fwush */
		7 + 7 + 7, /* gfx_v8_0_wing_emit_fence_kiq x3 fow usew fence, vm fence */
	.emit_ib_size =	7, /* gfx_v8_0_wing_emit_ib_compute */
	.emit_fence = gfx_v8_0_wing_emit_fence_kiq,
	.test_wing = gfx_v8_0_wing_test_wing,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.emit_wweg = gfx_v8_0_wing_emit_wweg,
	.emit_wweg = gfx_v8_0_wing_emit_wweg,
};

static void gfx_v8_0_set_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	adev->gfx.kiq[0].wing.funcs = &gfx_v8_0_wing_funcs_kiq;

	fow (i = 0; i < adev->gfx.num_gfx_wings; i++)
		adev->gfx.gfx_wing[i].funcs = &gfx_v8_0_wing_funcs_gfx;

	fow (i = 0; i < adev->gfx.num_compute_wings; i++)
		adev->gfx.compute_wing[i].funcs = &gfx_v8_0_wing_funcs_compute;
}

static const stwuct amdgpu_iwq_swc_funcs gfx_v8_0_eop_iwq_funcs = {
	.set = gfx_v8_0_set_eop_intewwupt_state,
	.pwocess = gfx_v8_0_eop_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs gfx_v8_0_pwiv_weg_iwq_funcs = {
	.set = gfx_v8_0_set_pwiv_weg_fauwt_state,
	.pwocess = gfx_v8_0_pwiv_weg_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs gfx_v8_0_pwiv_inst_iwq_funcs = {
	.set = gfx_v8_0_set_pwiv_inst_fauwt_state,
	.pwocess = gfx_v8_0_pwiv_inst_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs gfx_v8_0_cp_ecc_ewwow_iwq_funcs = {
	.set = gfx_v8_0_set_cp_ecc_int_state,
	.pwocess = gfx_v8_0_cp_ecc_ewwow_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs gfx_v8_0_sq_iwq_funcs = {
	.set = gfx_v8_0_set_sq_int_state,
	.pwocess = gfx_v8_0_sq_iwq,
};

static void gfx_v8_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->gfx.eop_iwq.num_types = AMDGPU_CP_IWQ_WAST;
	adev->gfx.eop_iwq.funcs = &gfx_v8_0_eop_iwq_funcs;

	adev->gfx.pwiv_weg_iwq.num_types = 1;
	adev->gfx.pwiv_weg_iwq.funcs = &gfx_v8_0_pwiv_weg_iwq_funcs;

	adev->gfx.pwiv_inst_iwq.num_types = 1;
	adev->gfx.pwiv_inst_iwq.funcs = &gfx_v8_0_pwiv_inst_iwq_funcs;

	adev->gfx.cp_ecc_ewwow_iwq.num_types = 1;
	adev->gfx.cp_ecc_ewwow_iwq.funcs = &gfx_v8_0_cp_ecc_ewwow_iwq_funcs;

	adev->gfx.sq_iwq.num_types = 1;
	adev->gfx.sq_iwq.funcs = &gfx_v8_0_sq_iwq_funcs;
}

static void gfx_v8_0_set_wwc_funcs(stwuct amdgpu_device *adev)
{
	adev->gfx.wwc.funcs = &icewand_wwc_funcs;
}

static void gfx_v8_0_set_gds_init(stwuct amdgpu_device *adev)
{
	/* init asci gds info */
	adev->gds.gds_size = WWEG32(mmGDS_VMID0_SIZE);
	adev->gds.gws_size = 64;
	adev->gds.oa_size = 16;
	adev->gds.gds_compute_max_wave_id = WWEG32(mmGDS_COMPUTE_MAX_WAVE_ID);
}

static void gfx_v8_0_set_usew_cu_inactive_bitmap(stwuct amdgpu_device *adev,
						 u32 bitmap)
{
	u32 data;

	if (!bitmap)
		wetuwn;

	data = bitmap << GC_USEW_SHADEW_AWWAY_CONFIG__INACTIVE_CUS__SHIFT;
	data &= GC_USEW_SHADEW_AWWAY_CONFIG__INACTIVE_CUS_MASK;

	WWEG32(mmGC_USEW_SHADEW_AWWAY_CONFIG, data);
}

static u32 gfx_v8_0_get_cu_active_bitmap(stwuct amdgpu_device *adev)
{
	u32 data, mask;

	data =  WWEG32(mmCC_GC_SHADEW_AWWAY_CONFIG) |
		WWEG32(mmGC_USEW_SHADEW_AWWAY_CONFIG);

	mask = amdgpu_gfx_cweate_bitmask(adev->gfx.config.max_cu_pew_sh);

	wetuwn ~WEG_GET_FIEWD(data, CC_GC_SHADEW_AWWAY_CONFIG, INACTIVE_CUS) & mask;
}

static void gfx_v8_0_get_cu_info(stwuct amdgpu_device *adev)
{
	int i, j, k, countew, active_cu_numbew = 0;
	u32 mask, bitmap, ao_bitmap, ao_cu_mask = 0;
	stwuct amdgpu_cu_info *cu_info = &adev->gfx.cu_info;
	unsigned disabwe_masks[4 * 2];
	u32 ao_cu_num;

	memset(cu_info, 0, sizeof(*cu_info));

	if (adev->fwags & AMD_IS_APU)
		ao_cu_num = 2;
	ewse
		ao_cu_num = adev->gfx.config.max_cu_pew_sh;

	amdgpu_gfx_pawse_disabwe_cu(disabwe_masks, 4, 2);

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
		fow (j = 0; j < adev->gfx.config.max_sh_pew_se; j++) {
			mask = 1;
			ao_bitmap = 0;
			countew = 0;
			gfx_v8_0_sewect_se_sh(adev, i, j, 0xffffffff, 0);
			if (i < 4 && j < 2)
				gfx_v8_0_set_usew_cu_inactive_bitmap(
					adev, disabwe_masks[i * 2 + j]);
			bitmap = gfx_v8_0_get_cu_active_bitmap(adev);
			cu_info->bitmap[0][i][j] = bitmap;

			fow (k = 0; k < adev->gfx.config.max_cu_pew_sh; k ++) {
				if (bitmap & mask) {
					if (countew < ao_cu_num)
						ao_bitmap |= mask;
					countew ++;
				}
				mask <<= 1;
			}
			active_cu_numbew += countew;
			if (i < 2 && j < 2)
				ao_cu_mask |= (ao_bitmap << (i * 16 + j * 8));
			cu_info->ao_cu_bitmap[i][j] = ao_bitmap;
		}
	}
	gfx_v8_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
	mutex_unwock(&adev->gwbm_idx_mutex);

	cu_info->numbew = active_cu_numbew;
	cu_info->ao_cu_mask = ao_cu_mask;
	cu_info->simd_pew_cu = NUM_SIMD_PEW_CU;
	cu_info->max_waves_pew_simd = 10;
	cu_info->max_scwatch_swots_pew_cu = 32;
	cu_info->wave_fwont_size = 64;
	cu_info->wds_size = 64;
}

const stwuct amdgpu_ip_bwock_vewsion gfx_v8_0_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_GFX,
	.majow = 8,
	.minow = 0,
	.wev = 0,
	.funcs = &gfx_v8_0_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion gfx_v8_1_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_GFX,
	.majow = 8,
	.minow = 1,
	.wev = 0,
	.funcs = &gfx_v8_0_ip_funcs,
};

static void gfx_v8_0_wing_emit_ce_meta(stwuct amdgpu_wing *wing)
{
	uint64_t ce_paywoad_addw;
	int cnt_ce;
	union {
		stwuct vi_ce_ib_state weguwaw;
		stwuct vi_ce_ib_state_chained_ib chained;
	} ce_paywoad = {};

	if (wing->adev->viwt.chained_ib_suppowt) {
		ce_paywoad_addw = amdgpu_csa_vaddw(wing->adev) +
			offsetof(stwuct vi_gfx_meta_data_chained_ib, ce_paywoad);
		cnt_ce = (sizeof(ce_paywoad.chained) >> 2) + 4 - 2;
	} ewse {
		ce_paywoad_addw = amdgpu_csa_vaddw(wing->adev) +
			offsetof(stwuct vi_gfx_meta_data, ce_paywoad);
		cnt_ce = (sizeof(ce_paywoad.weguwaw) >> 2) + 4 - 2;
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, cnt_ce));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(2) |
				WWITE_DATA_DST_SEW(8) |
				WW_CONFIWM) |
				WWITE_DATA_CACHE_POWICY(0));
	amdgpu_wing_wwite(wing, wowew_32_bits(ce_paywoad_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(ce_paywoad_addw));
	amdgpu_wing_wwite_muwtipwe(wing, (void *)&ce_paywoad, cnt_ce - 2);
}

static void gfx_v8_0_wing_emit_de_meta(stwuct amdgpu_wing *wing)
{
	uint64_t de_paywoad_addw, gds_addw, csa_addw;
	int cnt_de;
	union {
		stwuct vi_de_ib_state weguwaw;
		stwuct vi_de_ib_state_chained_ib chained;
	} de_paywoad = {};

	csa_addw = amdgpu_csa_vaddw(wing->adev);
	gds_addw = csa_addw + 4096;
	if (wing->adev->viwt.chained_ib_suppowt) {
		de_paywoad.chained.gds_backup_addwwo = wowew_32_bits(gds_addw);
		de_paywoad.chained.gds_backup_addwhi = uppew_32_bits(gds_addw);
		de_paywoad_addw = csa_addw + offsetof(stwuct vi_gfx_meta_data_chained_ib, de_paywoad);
		cnt_de = (sizeof(de_paywoad.chained) >> 2) + 4 - 2;
	} ewse {
		de_paywoad.weguwaw.gds_backup_addwwo = wowew_32_bits(gds_addw);
		de_paywoad.weguwaw.gds_backup_addwhi = uppew_32_bits(gds_addw);
		de_paywoad_addw = csa_addw + offsetof(stwuct vi_gfx_meta_data, de_paywoad);
		cnt_de = (sizeof(de_paywoad.weguwaw) >> 2) + 4 - 2;
	}

	amdgpu_wing_wwite(wing, PACKET3(PACKET3_WWITE_DATA, cnt_de));
	amdgpu_wing_wwite(wing, (WWITE_DATA_ENGINE_SEW(1) |
				WWITE_DATA_DST_SEW(8) |
				WW_CONFIWM) |
				WWITE_DATA_CACHE_POWICY(0));
	amdgpu_wing_wwite(wing, wowew_32_bits(de_paywoad_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(de_paywoad_addw));
	amdgpu_wing_wwite_muwtipwe(wing, (void *)&de_paywoad, cnt_de - 2);
}
