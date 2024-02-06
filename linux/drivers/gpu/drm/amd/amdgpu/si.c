/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
#incwude "atom.h"
#incwude "amd_pcie.h"
#incwude "si_dpm.h"
#incwude "sid.h"
#incwude "si_ih.h"
#incwude "gfx_v6_0.h"
#incwude "gmc_v6_0.h"
#incwude "si_dma.h"
#incwude "dce_v6_0.h"
#incwude "si.h"
#incwude "uvd_v3_1.h"
#incwude "amdgpu_vkms.h"
#incwude "gca/gfx_6_0_d.h"
#incwude "oss/oss_1_0_d.h"
#incwude "oss/oss_1_0_sh_mask.h"
#incwude "gmc/gmc_6_0_d.h"
#incwude "dce/dce_6_0_d.h"
#incwude "uvd/uvd_4_0_d.h"
#incwude "bif/bif_3_0_d.h"
#incwude "bif/bif_3_0_sh_mask.h"

#incwude "amdgpu_dm.h"

static const u32 tahiti_gowden_wegistews[] =
{
	mmAZAWIA_SCWK_CONTWOW, 0x00000030, 0x00000011,
	mmCB_HW_CONTWOW, 0x00010000, 0x00018208,
	mmDB_DEBUG, 0xffffffff, 0x00000000,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0x0002021c, 0x00020200,
	mmDCI_CWK_CNTW, 0x00000080, 0x00000000,
	0x340c, 0x000000c0, 0x00800040,
	0x360c, 0x000000c0, 0x00800040,
	mmFBC_DEBUG_COMP, 0x000000f0, 0x00000070,
	mmFBC_MISC, 0x00200000, 0x50100000,
	mmDIG0_HDMI_CONTWOW, 0x31000311, 0x00000011,
	mmMC_AWB_WTM_CNTW_WD, 0x00000003, 0x000007ff,
	mmMC_XPB_P2P_BAW_CFG, 0x000007ff, 0x00000000,
	mmPA_CW_ENHANCE, 0xf000001f, 0x00000007,
	mmPA_SC_FOWCE_EOV_MAX_CNTS, 0xffffffff, 0x00ffffff,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_MODE_CNTW_1, 0x07ffffff, 0x4e000000,
	mmPA_SC_WASTEW_CONFIG, 0x3f3f3fff, 0x2a00126a,
	0x000c, 0xffffffff, 0x0040,
	0x000d, 0x00000040, 0x00004040,
	mmSPI_CONFIG_CNTW, 0x07ffffff, 0x03000000,
	mmSQ_DED_CNT, 0x01ff1f3f, 0x00000000,
	mmSQ_SEC_CNT, 0x01ff1f3f, 0x00000000,
	mmSX_DEBUG_1, 0x0000007f, 0x00000020,
	mmTA_CNTW_AUX, 0x00010000, 0x00010000,
	mmTCP_ADDW_CONFIG, 0x00000200, 0x000002fb,
	mmTCP_CHAN_STEEW_HI, 0xffffffff, 0x0000543b,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0xa9210876,
	mmVGT_FIFO_DEPTHS, 0xffffffff, 0x000fff40,
	mmVGT_GS_VEWTEX_WEUSE, 0x0000001f, 0x00000010,
	mmVM_CONTEXT0_CNTW, 0x20000000, 0x20fffed8,
	mmVM_W2_CG, 0x000c0fc0, 0x000c0400,
	mmVM_PWT_APEWTUWE0_WOW_ADDW, 0x0fffffff, 0xffffffff,
	mmVM_PWT_APEWTUWE1_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE2_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE3_WOW_ADDW, 0x0fffffff, 0x0fffffff,
};

static const u32 tahiti_gowden_wegistews2[] =
{
	mmMCIF_MEM_CONTWOW, 0x00000001, 0x00000001,
};

static const u32 tahiti_gowden_wwc_wegistews[] =
{
	mmGB_ADDW_CONFIG, 0xffffffff, 0x12011003,
	mmWWC_WB_PAWAMS, 0xffffffff, 0x00601005,
	0x311f, 0xffffffff, 0x10104040,
	0x3122, 0xffffffff, 0x0100000a,
	mmWWC_WB_CNTW_MAX, 0xffffffff, 0x00000800,
	mmWWC_WB_CNTW, 0xffffffff, 0x800000f4,
	mmUVD_CGC_GATE, 0x00000008, 0x00000000,
};

static const u32 pitcaiwn_gowden_wegistews[] =
{
	mmAZAWIA_SCWK_CONTWOW, 0x00000030, 0x00000011,
	mmCB_HW_CONTWOW, 0x00010000, 0x00018208,
	mmDB_DEBUG, 0xffffffff, 0x00000000,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0x0002021c, 0x00020200,
	mmDCI_CWK_CNTW, 0x00000080, 0x00000000,
	0x340c, 0x000300c0, 0x00800040,
	0x360c, 0x000300c0, 0x00800040,
	mmFBC_DEBUG_COMP, 0x000000f0, 0x00000070,
	mmFBC_MISC, 0x00200000, 0x50100000,
	mmDIG0_HDMI_CONTWOW, 0x31000311, 0x00000011,
	mmMC_SEQ_PMG_PG_HWCNTW, 0x00073ffe, 0x000022a2,
	mmMC_XPB_P2P_BAW_CFG, 0x000007ff, 0x00000000,
	mmPA_CW_ENHANCE, 0xf000001f, 0x00000007,
	mmPA_SC_FOWCE_EOV_MAX_CNTS, 0xffffffff, 0x00ffffff,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_MODE_CNTW_1, 0x07ffffff, 0x4e000000,
	mmPA_SC_WASTEW_CONFIG, 0x3f3f3fff, 0x2a00126a,
	0x000c, 0xffffffff, 0x0040,
	0x000d, 0x00000040, 0x00004040,
	mmSPI_CONFIG_CNTW, 0x07ffffff, 0x03000000,
	mmSX_DEBUG_1, 0x0000007f, 0x00000020,
	mmTA_CNTW_AUX, 0x00010000, 0x00010000,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x000000f7,
	mmTCP_CHAN_STEEW_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0x32761054,
	mmVGT_GS_VEWTEX_WEUSE, 0x0000001f, 0x00000010,
	mmVM_W2_CG, 0x000c0fc0, 0x000c0400,
	mmVM_PWT_APEWTUWE0_WOW_ADDW, 0x0fffffff, 0xffffffff,
	mmVM_PWT_APEWTUWE1_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE2_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE3_WOW_ADDW, 0x0fffffff, 0x0fffffff,
};

static const u32 pitcaiwn_gowden_wwc_wegistews[] =
{
	mmGB_ADDW_CONFIG, 0xffffffff, 0x12011003,
	mmWWC_WB_PAWAMS, 0xffffffff, 0x00601004,
	0x311f, 0xffffffff, 0x10102020,
	0x3122, 0xffffffff, 0x01000020,
	mmWWC_WB_CNTW_MAX, 0xffffffff, 0x00000800,
	mmWWC_WB_CNTW, 0xffffffff, 0x800000a4,
};

static const u32 vewde_pg_init[] =
{
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x40000,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x200010ff,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x7007,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x300010ff,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x400000,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x100010ff,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x120200,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x500010ff,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x1e1e16,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x600010ff,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x171f1e,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x700010ff,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_WWITE, 0xffffffff, 0x0,
	mmGMCON_PGFSM_CONFIG, 0xffffffff, 0x9ff,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x0,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x10000800,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0xf,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0xf,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x4,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x1000051e,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0xffff,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0xffff,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x8,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x80500,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x12,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x9050c,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x1d,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0xb052c,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x2a,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x1053e,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x2d,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x10546,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x30,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0xa054e,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x3c,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x1055f,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x3f,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x10567,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x42,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x1056f,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x45,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x10572,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x48,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x20575,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x4c,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x190801,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x67,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x1082a,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x6a,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x1b082d,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x87,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x310851,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0xba,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x891,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0xbc,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x893,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0xbe,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x20895,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0xc2,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x20899,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0xc6,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x2089d,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0xca,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x8a1,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0xcc,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x8a3,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0xce,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x308a5,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0xd3,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x6d08cd,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x142,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x2000095a,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x1,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x144,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x301f095b,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x165,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0xc094d,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x173,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0xf096d,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x184,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x15097f,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x19b,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0xc0998,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x1a9,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x409a7,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x1af,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0xcdc,
	mmGMCON_WENG_WAM_INDEX, 0xffffffff, 0x1b1,
	mmGMCON_WENG_WAM_DATA, 0xffffffff, 0x800,
	mmGMCON_WENG_EXECUTE, 0xffffffff, 0x6c9b2000,
	mmGMCON_MISC2, 0xfc00, 0x2000,
	mmGMCON_MISC3, 0xffffffff, 0xfc0,
	mmMC_PMG_AUTO_CFG, 0x00000100, 0x100,
};

static const u32 vewde_gowden_wwc_wegistews[] =
{
	mmGB_ADDW_CONFIG, 0xffffffff, 0x02010002,
	mmWWC_WB_PAWAMS, 0xffffffff, 0x033f1005,
	0x311f, 0xffffffff, 0x10808020,
	0x3122, 0xffffffff, 0x00800008,
	mmWWC_WB_CNTW_MAX, 0xffffffff, 0x00001000,
	mmWWC_WB_CNTW, 0xffffffff, 0x80010014,
};

static const u32 vewde_gowden_wegistews[] =
{
	mmAZAWIA_SCWK_CONTWOW, 0x00000030, 0x00000011,
	mmCB_HW_CONTWOW, 0x00010000, 0x00018208,
	mmDB_DEBUG, 0xffffffff, 0x00000000,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0x0002021c, 0x00020200,
	mmDCI_CWK_CNTW, 0x00000080, 0x00000000,
	0x340c, 0x000300c0, 0x00800040,
	0x360c, 0x000300c0, 0x00800040,
	mmFBC_DEBUG_COMP, 0x000000f0, 0x00000070,
	mmFBC_MISC, 0x00200000, 0x50100000,
	mmDIG0_HDMI_CONTWOW, 0x31000311, 0x00000011,
	mmMC_SEQ_PMG_PG_HWCNTW, 0x00073ffe, 0x000022a2,
	mmMC_XPB_P2P_BAW_CFG, 0x000007ff, 0x00000000,
	mmPA_CW_ENHANCE, 0xf000001f, 0x00000007,
	mmPA_SC_FOWCE_EOV_MAX_CNTS, 0xffffffff, 0x00ffffff,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_MODE_CNTW_1, 0x07ffffff, 0x4e000000,
	mmPA_SC_WASTEW_CONFIG, 0x3f3f3fff, 0x0000124a,
	0x000c, 0xffffffff, 0x0040,
	0x000d, 0x00000040, 0x00004040,
	mmSPI_CONFIG_CNTW, 0x07ffffff, 0x03000000,
	mmSQ_DED_CNT, 0x01ff1f3f, 0x00000000,
	mmSQ_SEC_CNT, 0x01ff1f3f, 0x00000000,
	mmSX_DEBUG_1, 0x0000007f, 0x00000020,
	mmTA_CNTW_AUX, 0x00010000, 0x00010000,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x00000003,
	mmTCP_CHAN_STEEW_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0x00001032,
	mmVGT_GS_VEWTEX_WEUSE, 0x0000001f, 0x00000010,
	mmVM_W2_CG, 0x000c0fc0, 0x000c0400,
	mmVM_PWT_APEWTUWE0_WOW_ADDW, 0x0fffffff, 0xffffffff,
	mmVM_PWT_APEWTUWE1_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE2_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE3_WOW_ADDW, 0x0fffffff, 0x0fffffff,
};

static const u32 owand_gowden_wegistews[] =
{
	mmAZAWIA_SCWK_CONTWOW, 0x00000030, 0x00000011,
	mmCB_HW_CONTWOW, 0x00010000, 0x00018208,
	mmDB_DEBUG, 0xffffffff, 0x00000000,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0x0002021c, 0x00020200,
	mmDCI_CWK_CNTW, 0x00000080, 0x00000000,
	0x340c, 0x000300c0, 0x00800040,
	0x360c, 0x000300c0, 0x00800040,
	mmFBC_DEBUG_COMP, 0x000000f0, 0x00000070,
	mmFBC_MISC, 0x00200000, 0x50100000,
	mmDIG0_HDMI_CONTWOW, 0x31000311, 0x00000011,
	mmMC_SEQ_PMG_PG_HWCNTW, 0x00073ffe, 0x000022a2,
	mmMC_XPB_P2P_BAW_CFG, 0x000007ff, 0x00000000,
	mmPA_CW_ENHANCE, 0xf000001f, 0x00000007,
	mmPA_SC_FOWCE_EOV_MAX_CNTS, 0xffffffff, 0x00ffffff,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_MODE_CNTW_1, 0x07ffffff, 0x4e000000,
	mmPA_SC_WASTEW_CONFIG, 0x3f3f3fff, 0x00000082,
	0x000c, 0xffffffff, 0x0040,
	0x000d, 0x00000040, 0x00004040,
	mmSPI_CONFIG_CNTW, 0x07ffffff, 0x03000000,
	mmSX_DEBUG_1, 0x0000007f, 0x00000020,
	mmTA_CNTW_AUX, 0x00010000, 0x00010000,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x000000f3,
	mmTCP_CHAN_STEEW_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0x00003210,
	mmVGT_GS_VEWTEX_WEUSE, 0x0000001f, 0x00000010,
	mmVM_W2_CG, 0x000c0fc0, 0x000c0400,
	mmVM_PWT_APEWTUWE0_WOW_ADDW, 0x0fffffff, 0xffffffff,
	mmVM_PWT_APEWTUWE1_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE2_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE3_WOW_ADDW, 0x0fffffff, 0x0fffffff,

};

static const u32 owand_gowden_wwc_wegistews[] =
{
	mmGB_ADDW_CONFIG, 0xffffffff, 0x02010002,
	mmWWC_WB_PAWAMS, 0xffffffff, 0x00601005,
	0x311f, 0xffffffff, 0x10104040,
	0x3122, 0xffffffff, 0x0100000a,
	mmWWC_WB_CNTW_MAX, 0xffffffff, 0x00000800,
	mmWWC_WB_CNTW, 0xffffffff, 0x800000f4,
};

static const u32 hainan_gowden_wegistews[] =
{
	0x17bc, 0x00000030, 0x00000011,
	mmCB_HW_CONTWOW, 0x00010000, 0x00018208,
	mmDB_DEBUG, 0xffffffff, 0x00000000,
	mmDB_DEBUG2, 0xf00fffff, 0x00000400,
	mmDB_DEBUG3, 0x0002021c, 0x00020200,
	0x031e, 0x00000080, 0x00000000,
	0x3430, 0xff000fff, 0x00000100,
	0x340c, 0x000300c0, 0x00800040,
	0x3630, 0xff000fff, 0x00000100,
	0x360c, 0x000300c0, 0x00800040,
	0x16ec, 0x000000f0, 0x00000070,
	0x16f0, 0x00200000, 0x50100000,
	0x1c0c, 0x31000311, 0x00000011,
	mmMC_SEQ_PMG_PG_HWCNTW, 0x00073ffe, 0x000022a2,
	mmMC_XPB_P2P_BAW_CFG, 0x000007ff, 0x00000000,
	mmPA_CW_ENHANCE, 0xf000001f, 0x00000007,
	mmPA_SC_FOWCE_EOV_MAX_CNTS, 0xffffffff, 0x00ffffff,
	mmPA_SC_WINE_STIPPWE_STATE, 0x0000ff0f, 0x00000000,
	mmPA_SC_MODE_CNTW_1, 0x07ffffff, 0x4e000000,
	mmPA_SC_WASTEW_CONFIG, 0x3f3f3fff, 0x00000000,
	0x000c, 0xffffffff, 0x0040,
	0x000d, 0x00000040, 0x00004040,
	mmSPI_CONFIG_CNTW, 0x03e00000, 0x03600000,
	mmSX_DEBUG_1, 0x0000007f, 0x00000020,
	mmTA_CNTW_AUX, 0x00010000, 0x00010000,
	mmTCP_ADDW_CONFIG, 0x000003ff, 0x000000f1,
	mmTCP_CHAN_STEEW_HI, 0xffffffff, 0x00000000,
	mmTCP_CHAN_STEEW_WO, 0xffffffff, 0x00003210,
	mmVGT_GS_VEWTEX_WEUSE, 0x0000001f, 0x00000010,
	mmVM_W2_CG, 0x000c0fc0, 0x000c0400,
	mmVM_PWT_APEWTUWE0_WOW_ADDW, 0x0fffffff, 0xffffffff,
	mmVM_PWT_APEWTUWE1_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE2_WOW_ADDW, 0x0fffffff, 0x0fffffff,
	mmVM_PWT_APEWTUWE3_WOW_ADDW, 0x0fffffff, 0x0fffffff,
};

static const u32 hainan_gowden_wegistews2[] =
{
	mmGB_ADDW_CONFIG, 0xffffffff, 0x2011003,
};

static const u32 tahiti_mgcg_cgcg_init[] =
{
	mmWWC_CGTT_MGCG_OVEWWIDE, 0xffffffff, 0xfffffffc,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_GDS_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_IA_CWK_CTWW, 0xffffffff, 0x06000100,
	mmCGTT_PA_CWK_CTWW, 0xffffffff, 0x00000100,
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
	mmCGTT_TCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CWK_CTWW, 0xffffffff, 0x06000100,
	mmDB_CGTT_CWK_CTWW_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	0x2458, 0xffffffff, 0x00010000,
	0x2459, 0xffffffff, 0x00030002,
	0x245a, 0xffffffff, 0x00040007,
	0x245b, 0xffffffff, 0x00060005,
	0x245c, 0xffffffff, 0x00090008,
	0x245d, 0xffffffff, 0x00020001,
	0x245e, 0xffffffff, 0x00040003,
	0x245f, 0xffffffff, 0x00000007,
	0x2460, 0xffffffff, 0x00060005,
	0x2461, 0xffffffff, 0x00090008,
	0x2462, 0xffffffff, 0x00030002,
	0x2463, 0xffffffff, 0x00050004,
	0x2464, 0xffffffff, 0x00000008,
	0x2465, 0xffffffff, 0x00070006,
	0x2466, 0xffffffff, 0x000a0009,
	0x2467, 0xffffffff, 0x00040003,
	0x2468, 0xffffffff, 0x00060005,
	0x2469, 0xffffffff, 0x00000009,
	0x246a, 0xffffffff, 0x00080007,
	0x246b, 0xffffffff, 0x000b000a,
	0x246c, 0xffffffff, 0x00050004,
	0x246d, 0xffffffff, 0x00070006,
	0x246e, 0xffffffff, 0x0008000b,
	0x246f, 0xffffffff, 0x000a0009,
	0x2470, 0xffffffff, 0x000d000c,
	0x2471, 0xffffffff, 0x00060005,
	0x2472, 0xffffffff, 0x00080007,
	0x2473, 0xffffffff, 0x0000000b,
	0x2474, 0xffffffff, 0x000a0009,
	0x2475, 0xffffffff, 0x000d000c,
	0x2476, 0xffffffff, 0x00070006,
	0x2477, 0xffffffff, 0x00090008,
	0x2478, 0xffffffff, 0x0000000c,
	0x2479, 0xffffffff, 0x000b000a,
	0x247a, 0xffffffff, 0x000e000d,
	0x247b, 0xffffffff, 0x00080007,
	0x247c, 0xffffffff, 0x000a0009,
	0x247d, 0xffffffff, 0x0000000d,
	0x247e, 0xffffffff, 0x000c000b,
	0x247f, 0xffffffff, 0x000f000e,
	0x2480, 0xffffffff, 0x00090008,
	0x2481, 0xffffffff, 0x000b000a,
	0x2482, 0xffffffff, 0x000c000f,
	0x2483, 0xffffffff, 0x000e000d,
	0x2484, 0xffffffff, 0x00110010,
	0x2485, 0xffffffff, 0x000a0009,
	0x2486, 0xffffffff, 0x000c000b,
	0x2487, 0xffffffff, 0x0000000f,
	0x2488, 0xffffffff, 0x000e000d,
	0x2489, 0xffffffff, 0x00110010,
	0x248a, 0xffffffff, 0x000b000a,
	0x248b, 0xffffffff, 0x000d000c,
	0x248c, 0xffffffff, 0x00000010,
	0x248d, 0xffffffff, 0x000f000e,
	0x248e, 0xffffffff, 0x00120011,
	0x248f, 0xffffffff, 0x000c000b,
	0x2490, 0xffffffff, 0x000e000d,
	0x2491, 0xffffffff, 0x00000011,
	0x2492, 0xffffffff, 0x0010000f,
	0x2493, 0xffffffff, 0x00130012,
	0x2494, 0xffffffff, 0x000d000c,
	0x2495, 0xffffffff, 0x000f000e,
	0x2496, 0xffffffff, 0x00100013,
	0x2497, 0xffffffff, 0x00120011,
	0x2498, 0xffffffff, 0x00150014,
	0x2499, 0xffffffff, 0x000e000d,
	0x249a, 0xffffffff, 0x0010000f,
	0x249b, 0xffffffff, 0x00000013,
	0x249c, 0xffffffff, 0x00120011,
	0x249d, 0xffffffff, 0x00150014,
	0x249e, 0xffffffff, 0x000f000e,
	0x249f, 0xffffffff, 0x00110010,
	0x24a0, 0xffffffff, 0x00000014,
	0x24a1, 0xffffffff, 0x00130012,
	0x24a2, 0xffffffff, 0x00160015,
	0x24a3, 0xffffffff, 0x0010000f,
	0x24a4, 0xffffffff, 0x00120011,
	0x24a5, 0xffffffff, 0x00000015,
	0x24a6, 0xffffffff, 0x00140013,
	0x24a7, 0xffffffff, 0x00170016,
	mmCGTS_SM_CTWW_WEG, 0xffffffff, 0x96940200,
	mmCP_WB_WPTW_POWW_CNTW, 0xffffffff, 0x00900100,
	mmWWC_GCPM_GENEWAW_3, 0xffffffff, 0x00000080,
	mmWWC_CGCG_CGWS_CTWW, 0xffffffff, 0x0020003f,
	0x000c, 0xffffffff, 0x0000001c,
	0x000d, 0x000f0000, 0x000f0000,
	0x0583, 0xffffffff, 0x00000100,
	mmXDMA_CWOCK_GATING_CNTW, 0xffffffff, 0x00000100,
	mmXDMA_MEM_POWEW_CNTW, 0x00000101, 0x00000000,
	mmMC_MEM_POWEW_WS, 0xffffffff, 0x00000104,
	mmMC_CITF_MISC_WW_CG, 0x000c0000, 0x000c0000,
	mmMC_CITF_MISC_WD_CG, 0x000c0000, 0x000c0000,
	mmCGTT_DWM_CWK_CTWW0, 0xff000fff, 0x00000100,
	0x157a, 0x00000001, 0x00000001,
	mmHDP_MEM_POWEW_WS, 0x00000001, 0x00000001,
	mmHDP_XDP_CGTT_BWK_CTWW, 0xc0000fff, 0x00000104,
	mmCP_MEM_SWP_CNTW, 0x00000001, 0x00000001,
	0x3430, 0xfffffff0, 0x00000100,
	0x3630, 0xfffffff0, 0x00000100,
};
static const u32 pitcaiwn_mgcg_cgcg_init[] =
{
	mmWWC_CGTT_MGCG_OVEWWIDE, 0xffffffff, 0xfffffffc,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_GDS_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_IA_CWK_CTWW, 0xffffffff, 0x06000100,
	mmCGTT_PA_CWK_CTWW, 0xffffffff, 0x00000100,
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
	mmCGTT_TCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CWK_CTWW, 0xffffffff, 0x06000100,
	mmDB_CGTT_CWK_CTWW_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	0x2458, 0xffffffff, 0x00010000,
	0x2459, 0xffffffff, 0x00030002,
	0x245a, 0xffffffff, 0x00040007,
	0x245b, 0xffffffff, 0x00060005,
	0x245c, 0xffffffff, 0x00090008,
	0x245d, 0xffffffff, 0x00020001,
	0x245e, 0xffffffff, 0x00040003,
	0x245f, 0xffffffff, 0x00000007,
	0x2460, 0xffffffff, 0x00060005,
	0x2461, 0xffffffff, 0x00090008,
	0x2462, 0xffffffff, 0x00030002,
	0x2463, 0xffffffff, 0x00050004,
	0x2464, 0xffffffff, 0x00000008,
	0x2465, 0xffffffff, 0x00070006,
	0x2466, 0xffffffff, 0x000a0009,
	0x2467, 0xffffffff, 0x00040003,
	0x2468, 0xffffffff, 0x00060005,
	0x2469, 0xffffffff, 0x00000009,
	0x246a, 0xffffffff, 0x00080007,
	0x246b, 0xffffffff, 0x000b000a,
	0x246c, 0xffffffff, 0x00050004,
	0x246d, 0xffffffff, 0x00070006,
	0x246e, 0xffffffff, 0x0008000b,
	0x246f, 0xffffffff, 0x000a0009,
	0x2470, 0xffffffff, 0x000d000c,
	0x2480, 0xffffffff, 0x00090008,
	0x2481, 0xffffffff, 0x000b000a,
	0x2482, 0xffffffff, 0x000c000f,
	0x2483, 0xffffffff, 0x000e000d,
	0x2484, 0xffffffff, 0x00110010,
	0x2485, 0xffffffff, 0x000a0009,
	0x2486, 0xffffffff, 0x000c000b,
	0x2487, 0xffffffff, 0x0000000f,
	0x2488, 0xffffffff, 0x000e000d,
	0x2489, 0xffffffff, 0x00110010,
	0x248a, 0xffffffff, 0x000b000a,
	0x248b, 0xffffffff, 0x000d000c,
	0x248c, 0xffffffff, 0x00000010,
	0x248d, 0xffffffff, 0x000f000e,
	0x248e, 0xffffffff, 0x00120011,
	0x248f, 0xffffffff, 0x000c000b,
	0x2490, 0xffffffff, 0x000e000d,
	0x2491, 0xffffffff, 0x00000011,
	0x2492, 0xffffffff, 0x0010000f,
	0x2493, 0xffffffff, 0x00130012,
	0x2494, 0xffffffff, 0x000d000c,
	0x2495, 0xffffffff, 0x000f000e,
	0x2496, 0xffffffff, 0x00100013,
	0x2497, 0xffffffff, 0x00120011,
	0x2498, 0xffffffff, 0x00150014,
	mmCGTS_SM_CTWW_WEG, 0xffffffff, 0x96940200,
	mmCP_WB_WPTW_POWW_CNTW, 0xffffffff, 0x00900100,
	mmWWC_GCPM_GENEWAW_3, 0xffffffff, 0x00000080,
	mmWWC_CGCG_CGWS_CTWW, 0xffffffff, 0x0020003f,
	0x000c, 0xffffffff, 0x0000001c,
	0x000d, 0x000f0000, 0x000f0000,
	0x0583, 0xffffffff, 0x00000100,
	mmXDMA_CWOCK_GATING_CNTW, 0xffffffff, 0x00000100,
	mmXDMA_MEM_POWEW_CNTW, 0x00000101, 0x00000000,
	mmMC_MEM_POWEW_WS, 0xffffffff, 0x00000104,
	mmCGTT_DWM_CWK_CTWW0, 0xff000fff, 0x00000100,
	0x157a, 0x00000001, 0x00000001,
	mmHDP_MEM_POWEW_WS, 0x00000001, 0x00000001,
	mmHDP_XDP_CGTT_BWK_CTWW, 0xc0000fff, 0x00000104,
	mmCP_MEM_SWP_CNTW, 0x00000001, 0x00000001,
	0x3430, 0xfffffff0, 0x00000100,
	0x3630, 0xfffffff0, 0x00000100,
};

static const u32 vewde_mgcg_cgcg_init[] =
{
	mmWWC_CGTT_MGCG_OVEWWIDE, 0xffffffff, 0xfffffffc,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_GDS_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_IA_CWK_CTWW, 0xffffffff, 0x06000100,
	mmCGTT_PA_CWK_CTWW, 0xffffffff, 0x00000100,
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
	mmCGTT_TCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CWK_CTWW, 0xffffffff, 0x06000100,
	mmDB_CGTT_CWK_CTWW_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	0x2458, 0xffffffff, 0x00010000,
	0x2459, 0xffffffff, 0x00030002,
	0x245a, 0xffffffff, 0x00040007,
	0x245b, 0xffffffff, 0x00060005,
	0x245c, 0xffffffff, 0x00090008,
	0x245d, 0xffffffff, 0x00020001,
	0x245e, 0xffffffff, 0x00040003,
	0x245f, 0xffffffff, 0x00000007,
	0x2460, 0xffffffff, 0x00060005,
	0x2461, 0xffffffff, 0x00090008,
	0x2462, 0xffffffff, 0x00030002,
	0x2463, 0xffffffff, 0x00050004,
	0x2464, 0xffffffff, 0x00000008,
	0x2465, 0xffffffff, 0x00070006,
	0x2466, 0xffffffff, 0x000a0009,
	0x2467, 0xffffffff, 0x00040003,
	0x2468, 0xffffffff, 0x00060005,
	0x2469, 0xffffffff, 0x00000009,
	0x246a, 0xffffffff, 0x00080007,
	0x246b, 0xffffffff, 0x000b000a,
	0x246c, 0xffffffff, 0x00050004,
	0x246d, 0xffffffff, 0x00070006,
	0x246e, 0xffffffff, 0x0008000b,
	0x246f, 0xffffffff, 0x000a0009,
	0x2470, 0xffffffff, 0x000d000c,
	0x2480, 0xffffffff, 0x00090008,
	0x2481, 0xffffffff, 0x000b000a,
	0x2482, 0xffffffff, 0x000c000f,
	0x2483, 0xffffffff, 0x000e000d,
	0x2484, 0xffffffff, 0x00110010,
	0x2485, 0xffffffff, 0x000a0009,
	0x2486, 0xffffffff, 0x000c000b,
	0x2487, 0xffffffff, 0x0000000f,
	0x2488, 0xffffffff, 0x000e000d,
	0x2489, 0xffffffff, 0x00110010,
	0x248a, 0xffffffff, 0x000b000a,
	0x248b, 0xffffffff, 0x000d000c,
	0x248c, 0xffffffff, 0x00000010,
	0x248d, 0xffffffff, 0x000f000e,
	0x248e, 0xffffffff, 0x00120011,
	0x248f, 0xffffffff, 0x000c000b,
	0x2490, 0xffffffff, 0x000e000d,
	0x2491, 0xffffffff, 0x00000011,
	0x2492, 0xffffffff, 0x0010000f,
	0x2493, 0xffffffff, 0x00130012,
	0x2494, 0xffffffff, 0x000d000c,
	0x2495, 0xffffffff, 0x000f000e,
	0x2496, 0xffffffff, 0x00100013,
	0x2497, 0xffffffff, 0x00120011,
	0x2498, 0xffffffff, 0x00150014,
	mmCGTS_SM_CTWW_WEG, 0xffffffff, 0x96940200,
	mmCP_WB_WPTW_POWW_CNTW, 0xffffffff, 0x00900100,
	mmWWC_GCPM_GENEWAW_3, 0xffffffff, 0x00000080,
	mmWWC_CGCG_CGWS_CTWW, 0xffffffff, 0x0020003f,
	0x000c, 0xffffffff, 0x0000001c,
	0x000d, 0x000f0000, 0x000f0000,
	0x0583, 0xffffffff, 0x00000100,
	mmXDMA_CWOCK_GATING_CNTW, 0xffffffff, 0x00000100,
	mmXDMA_MEM_POWEW_CNTW, 0x00000101, 0x00000000,
	mmMC_MEM_POWEW_WS, 0xffffffff, 0x00000104,
	mmMC_CITF_MISC_WW_CG, 0x000c0000, 0x000c0000,
	mmMC_CITF_MISC_WD_CG, 0x000c0000, 0x000c0000,
	mmCGTT_DWM_CWK_CTWW0, 0xff000fff, 0x00000100,
	0x157a, 0x00000001, 0x00000001,
	mmHDP_MEM_POWEW_WS, 0x00000001, 0x00000001,
	mmHDP_XDP_CGTT_BWK_CTWW, 0xc0000fff, 0x00000104,
	mmCP_MEM_SWP_CNTW, 0x00000001, 0x00000001,
	0x3430, 0xfffffff0, 0x00000100,
	0x3630, 0xfffffff0, 0x00000100,
};

static const u32 owand_mgcg_cgcg_init[] =
{
	mmWWC_CGTT_MGCG_OVEWWIDE, 0xffffffff, 0xfffffffc,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_GDS_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_IA_CWK_CTWW, 0xffffffff, 0x06000100,
	mmCGTT_PA_CWK_CTWW, 0xffffffff, 0x00000100,
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
	mmCGTT_TCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CWK_CTWW, 0xffffffff, 0x06000100,
	mmDB_CGTT_CWK_CTWW_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	0x2458, 0xffffffff, 0x00010000,
	0x2459, 0xffffffff, 0x00030002,
	0x245a, 0xffffffff, 0x00040007,
	0x245b, 0xffffffff, 0x00060005,
	0x245c, 0xffffffff, 0x00090008,
	0x245d, 0xffffffff, 0x00020001,
	0x245e, 0xffffffff, 0x00040003,
	0x245f, 0xffffffff, 0x00000007,
	0x2460, 0xffffffff, 0x00060005,
	0x2461, 0xffffffff, 0x00090008,
	0x2462, 0xffffffff, 0x00030002,
	0x2463, 0xffffffff, 0x00050004,
	0x2464, 0xffffffff, 0x00000008,
	0x2465, 0xffffffff, 0x00070006,
	0x2466, 0xffffffff, 0x000a0009,
	0x2467, 0xffffffff, 0x00040003,
	0x2468, 0xffffffff, 0x00060005,
	0x2469, 0xffffffff, 0x00000009,
	0x246a, 0xffffffff, 0x00080007,
	0x246b, 0xffffffff, 0x000b000a,
	0x246c, 0xffffffff, 0x00050004,
	0x246d, 0xffffffff, 0x00070006,
	0x246e, 0xffffffff, 0x0008000b,
	0x246f, 0xffffffff, 0x000a0009,
	0x2470, 0xffffffff, 0x000d000c,
	0x2471, 0xffffffff, 0x00060005,
	0x2472, 0xffffffff, 0x00080007,
	0x2473, 0xffffffff, 0x0000000b,
	0x2474, 0xffffffff, 0x000a0009,
	0x2475, 0xffffffff, 0x000d000c,
	mmCGTS_SM_CTWW_WEG, 0xffffffff, 0x96940200,
	mmCP_WB_WPTW_POWW_CNTW, 0xffffffff, 0x00900100,
	mmWWC_GCPM_GENEWAW_3, 0xffffffff, 0x00000080,
	mmWWC_CGCG_CGWS_CTWW, 0xffffffff, 0x0020003f,
	0x000c, 0xffffffff, 0x0000001c,
	0x000d, 0x000f0000, 0x000f0000,
	0x0583, 0xffffffff, 0x00000100,
	mmXDMA_CWOCK_GATING_CNTW, 0xffffffff, 0x00000100,
	mmXDMA_MEM_POWEW_CNTW, 0x00000101, 0x00000000,
	mmMC_MEM_POWEW_WS, 0xffffffff, 0x00000104,
	mmMC_CITF_MISC_WW_CG, 0x000c0000, 0x000c0000,
	mmMC_CITF_MISC_WD_CG, 0x000c0000, 0x000c0000,
	mmCGTT_DWM_CWK_CTWW0, 0xff000fff, 0x00000100,
	0x157a, 0x00000001, 0x00000001,
	mmHDP_MEM_POWEW_WS, 0x00000001, 0x00000001,
	mmHDP_XDP_CGTT_BWK_CTWW, 0xc0000fff, 0x00000104,
	mmCP_MEM_SWP_CNTW, 0x00000001, 0x00000001,
	0x3430, 0xfffffff0, 0x00000100,
	0x3630, 0xfffffff0, 0x00000100,
};

static const u32 hainan_mgcg_cgcg_init[] =
{
	mmWWC_CGTT_MGCG_OVEWWIDE, 0xffffffff, 0xfffffffc,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	mmCB_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_BCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_CP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_GDS_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_IA_CWK_CTWW, 0xffffffff, 0x06000100,
	mmCGTT_PA_CWK_CTWW, 0xffffffff, 0x00000100,
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
	mmCGTT_TCI_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_TCP_CWK_CTWW, 0xffffffff, 0x00000100,
	mmCGTT_VGT_CWK_CTWW, 0xffffffff, 0x06000100,
	mmDB_CGTT_CWK_CTWW_0, 0xffffffff, 0x00000100,
	mmTA_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmTCA_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTCC_CGTT_SCWK_CTWW, 0xffffffff, 0x00000100,
	mmTD_CGTT_CTWW, 0xffffffff, 0x00000100,
	mmGWBM_GFX_INDEX, 0xffffffff, 0xe0000000,
	0x2458, 0xffffffff, 0x00010000,
	0x2459, 0xffffffff, 0x00030002,
	0x245a, 0xffffffff, 0x00040007,
	0x245b, 0xffffffff, 0x00060005,
	0x245c, 0xffffffff, 0x00090008,
	0x245d, 0xffffffff, 0x00020001,
	0x245e, 0xffffffff, 0x00040003,
	0x245f, 0xffffffff, 0x00000007,
	0x2460, 0xffffffff, 0x00060005,
	0x2461, 0xffffffff, 0x00090008,
	0x2462, 0xffffffff, 0x00030002,
	0x2463, 0xffffffff, 0x00050004,
	0x2464, 0xffffffff, 0x00000008,
	0x2465, 0xffffffff, 0x00070006,
	0x2466, 0xffffffff, 0x000a0009,
	0x2467, 0xffffffff, 0x00040003,
	0x2468, 0xffffffff, 0x00060005,
	0x2469, 0xffffffff, 0x00000009,
	0x246a, 0xffffffff, 0x00080007,
	0x246b, 0xffffffff, 0x000b000a,
	0x246c, 0xffffffff, 0x00050004,
	0x246d, 0xffffffff, 0x00070006,
	0x246e, 0xffffffff, 0x0008000b,
	0x246f, 0xffffffff, 0x000a0009,
	0x2470, 0xffffffff, 0x000d000c,
	0x2471, 0xffffffff, 0x00060005,
	0x2472, 0xffffffff, 0x00080007,
	0x2473, 0xffffffff, 0x0000000b,
	0x2474, 0xffffffff, 0x000a0009,
	0x2475, 0xffffffff, 0x000d000c,
	mmCGTS_SM_CTWW_WEG, 0xffffffff, 0x96940200,
	mmCP_WB_WPTW_POWW_CNTW, 0xffffffff, 0x00900100,
	mmWWC_GCPM_GENEWAW_3, 0xffffffff, 0x00000080,
	mmWWC_CGCG_CGWS_CTWW, 0xffffffff, 0x0020003f,
	0x000c, 0xffffffff, 0x0000001c,
	0x000d, 0x000f0000, 0x000f0000,
	0x0583, 0xffffffff, 0x00000100,
	0x0409, 0xffffffff, 0x00000100,
	mmMC_MEM_POWEW_WS, 0xffffffff, 0x00000104,
	mmMC_CITF_MISC_WW_CG, 0x000c0000, 0x000c0000,
	mmMC_CITF_MISC_WD_CG, 0x000c0000, 0x000c0000,
	mmHDP_MEM_POWEW_WS, 0x00000001, 0x00000001,
	mmHDP_XDP_CGTT_BWK_CTWW, 0xc0000fff, 0x00000104,
	mmCP_MEM_SWP_CNTW, 0x00000001, 0x00000001,
	0x3430, 0xfffffff0, 0x00000100,
	0x3630, 0xfffffff0, 0x00000100,
};

/* XXX: update when we suppowt VCE */
#if 0
/* tahiti, pitcawin, vewde */
static const stwuct amdgpu_video_codec_info tahiti_video_codecs_encode_awway[] =
{
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixews_pew_fwame = 2048 * 1152,
		.max_wevew = 0,
	},
};

static const stwuct amdgpu_video_codecs tahiti_video_codecs_encode =
{
	.codec_count = AWWAY_SIZE(tahiti_video_codecs_encode_awway),
	.codec_awway = tahiti_video_codecs_encode_awway,
};
#ewse
static const stwuct amdgpu_video_codecs tahiti_video_codecs_encode =
{
	.codec_count = 0,
	.codec_awway = NUWW,
};
#endif
/* owand and hainan don't suppowt encode */
static const stwuct amdgpu_video_codecs hainan_video_codecs_encode =
{
	.codec_count = 0,
	.codec_awway = NUWW,
};

/* tahiti, pitcawin, vewde, owand */
static const stwuct amdgpu_video_codec_info tahiti_video_codecs_decode_awway[] =
{
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixews_pew_fwame = 2048 * 1152,
		.max_wevew = 3,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixews_pew_fwame = 2048 * 1152,
		.max_wevew = 5,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixews_pew_fwame = 2048 * 1152,
		.max_wevew = 41,
	},
	{
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixews_pew_fwame = 2048 * 1152,
		.max_wevew = 4,
	},
};

static const stwuct amdgpu_video_codecs tahiti_video_codecs_decode =
{
	.codec_count = AWWAY_SIZE(tahiti_video_codecs_decode_awway),
	.codec_awway = tahiti_video_codecs_decode_awway,
};

/* hainan doesn't suppowt decode */
static const stwuct amdgpu_video_codecs hainan_video_codecs_decode =
{
	.codec_count = 0,
	.codec_awway = NUWW,
};

static int si_quewy_video_codecs(stwuct amdgpu_device *adev, boow encode,
				 const stwuct amdgpu_video_codecs **codecs)
{
	switch (adev->asic_type) {
	case CHIP_VEWDE:
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
		if (encode)
			*codecs = &tahiti_video_codecs_encode;
		ewse
			*codecs = &tahiti_video_codecs_decode;
		wetuwn 0;
	case CHIP_OWAND:
		if (encode)
			*codecs = &hainan_video_codecs_encode;
		ewse
			*codecs = &tahiti_video_codecs_decode;
		wetuwn 0;
	case CHIP_HAINAN:
		if (encode)
			*codecs = &hainan_video_codecs_encode;
		ewse
			*codecs = &hainan_video_codecs_decode;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static u32 si_pcie_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(AMDGPU_PCIE_INDEX, weg);
	(void)WWEG32(AMDGPU_PCIE_INDEX);
	w = WWEG32(AMDGPU_PCIE_DATA);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
	wetuwn w;
}

static void si_pcie_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(AMDGPU_PCIE_INDEX, weg);
	(void)WWEG32(AMDGPU_PCIE_INDEX);
	WWEG32(AMDGPU_PCIE_DATA, v);
	(void)WWEG32(AMDGPU_PCIE_DATA);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

static u32 si_pciep_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(PCIE_POWT_INDEX, ((weg) & 0xff));
	(void)WWEG32(PCIE_POWT_INDEX);
	w = WWEG32(PCIE_POWT_DATA);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
	wetuwn w;
}

static void si_pciep_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(PCIE_POWT_INDEX, ((weg) & 0xff));
	(void)WWEG32(PCIE_POWT_INDEX);
	WWEG32(PCIE_POWT_DATA, (v));
	(void)WWEG32(PCIE_POWT_DATA);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

static u32 si_smc_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->smc_idx_wock, fwags);
	WWEG32(SMC_IND_INDEX_0, (weg));
	w = WWEG32(SMC_IND_DATA_0);
	spin_unwock_iwqwestowe(&adev->smc_idx_wock, fwags);
	wetuwn w;
}

static void si_smc_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->smc_idx_wock, fwags);
	WWEG32(SMC_IND_INDEX_0, (weg));
	WWEG32(SMC_IND_DATA_0, (v));
	spin_unwock_iwqwestowe(&adev->smc_idx_wock, fwags);
}

static u32 si_uvd_ctx_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->uvd_ctx_idx_wock, fwags);
	WWEG32(mmUVD_CTX_INDEX, ((weg) & 0x1ff));
	w = WWEG32(mmUVD_CTX_DATA);
	spin_unwock_iwqwestowe(&adev->uvd_ctx_idx_wock, fwags);
	wetuwn w;
}

static void si_uvd_ctx_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->uvd_ctx_idx_wock, fwags);
	WWEG32(mmUVD_CTX_INDEX, ((weg) & 0x1ff));
	WWEG32(mmUVD_CTX_DATA, (v));
	spin_unwock_iwqwestowe(&adev->uvd_ctx_idx_wock, fwags);
}

static stwuct amdgpu_awwowed_wegistew_entwy si_awwowed_wead_wegistews[] = {
	{GWBM_STATUS},
	{mmGWBM_STATUS2},
	{mmGWBM_STATUS_SE0},
	{mmGWBM_STATUS_SE1},
	{mmSWBM_STATUS},
	{mmSWBM_STATUS2},
	{DMA_STATUS_WEG + DMA0_WEGISTEW_OFFSET},
	{DMA_STATUS_WEG + DMA1_WEGISTEW_OFFSET},
	{mmCP_STAT},
	{mmCP_STAWWED_STAT1},
	{mmCP_STAWWED_STAT2},
	{mmCP_STAWWED_STAT3},
	{GB_ADDW_CONFIG},
	{MC_AWB_WAMCFG},
	{GB_TIWE_MODE0},
	{GB_TIWE_MODE1},
	{GB_TIWE_MODE2},
	{GB_TIWE_MODE3},
	{GB_TIWE_MODE4},
	{GB_TIWE_MODE5},
	{GB_TIWE_MODE6},
	{GB_TIWE_MODE7},
	{GB_TIWE_MODE8},
	{GB_TIWE_MODE9},
	{GB_TIWE_MODE10},
	{GB_TIWE_MODE11},
	{GB_TIWE_MODE12},
	{GB_TIWE_MODE13},
	{GB_TIWE_MODE14},
	{GB_TIWE_MODE15},
	{GB_TIWE_MODE16},
	{GB_TIWE_MODE17},
	{GB_TIWE_MODE18},
	{GB_TIWE_MODE19},
	{GB_TIWE_MODE20},
	{GB_TIWE_MODE21},
	{GB_TIWE_MODE22},
	{GB_TIWE_MODE23},
	{GB_TIWE_MODE24},
	{GB_TIWE_MODE25},
	{GB_TIWE_MODE26},
	{GB_TIWE_MODE27},
	{GB_TIWE_MODE28},
	{GB_TIWE_MODE29},
	{GB_TIWE_MODE30},
	{GB_TIWE_MODE31},
	{CC_WB_BACKEND_DISABWE, twue},
	{GC_USEW_WB_BACKEND_DISABWE, twue},
	{PA_SC_WASTEW_CONFIG, twue},
};

static uint32_t si_get_wegistew_vawue(stwuct amdgpu_device *adev,
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
		defauwt:
			wetuwn WWEG32(weg_offset);
		}
	}
}
static int si_wead_wegistew(stwuct amdgpu_device *adev, u32 se_num,
			     u32 sh_num, u32 weg_offset, u32 *vawue)
{
	uint32_t i;

	*vawue = 0;
	fow (i = 0; i < AWWAY_SIZE(si_awwowed_wead_wegistews); i++) {
		boow indexed = si_awwowed_wead_wegistews[i].gwbm_indexed;

		if (weg_offset != si_awwowed_wead_wegistews[i].weg_offset)
			continue;

		*vawue = si_get_wegistew_vawue(adev, indexed, se_num, sh_num,
					       weg_offset);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static boow si_wead_disabwed_bios(stwuct amdgpu_device *adev)
{
	u32 bus_cntw;
	u32 d1vga_contwow = 0;
	u32 d2vga_contwow = 0;
	u32 vga_wendew_contwow = 0;
	u32 wom_cntw;
	boow w;

	bus_cntw = WWEG32(W600_BUS_CNTW);
	if (adev->mode_info.num_cwtc) {
		d1vga_contwow = WWEG32(AVIVO_D1VGA_CONTWOW);
		d2vga_contwow = WWEG32(AVIVO_D2VGA_CONTWOW);
		vga_wendew_contwow = WWEG32(VGA_WENDEW_CONTWOW);
	}
	wom_cntw = WWEG32(W600_WOM_CNTW);

	/* enabwe the wom */
	WWEG32(W600_BUS_CNTW, (bus_cntw & ~W600_BIOS_WOM_DIS));
	if (adev->mode_info.num_cwtc) {
		/* Disabwe VGA mode */
		WWEG32(AVIVO_D1VGA_CONTWOW,
		       (d1vga_contwow & ~(AVIVO_DVGA_CONTWOW_MODE_ENABWE |
					  AVIVO_DVGA_CONTWOW_TIMING_SEWECT)));
		WWEG32(AVIVO_D2VGA_CONTWOW,
		       (d2vga_contwow & ~(AVIVO_DVGA_CONTWOW_MODE_ENABWE |
					  AVIVO_DVGA_CONTWOW_TIMING_SEWECT)));
		WWEG32(VGA_WENDEW_CONTWOW,
		       (vga_wendew_contwow & C_000300_VGA_VSTATUS_CNTW));
	}
	WWEG32(W600_WOM_CNTW, wom_cntw | W600_SCK_OVEWWWITE);

	w = amdgpu_wead_bios(adev);

	/* westowe wegs */
	WWEG32(W600_BUS_CNTW, bus_cntw);
	if (adev->mode_info.num_cwtc) {
		WWEG32(AVIVO_D1VGA_CONTWOW, d1vga_contwow);
		WWEG32(AVIVO_D2VGA_CONTWOW, d2vga_contwow);
		WWEG32(VGA_WENDEW_CONTWOW, vga_wendew_contwow);
	}
	WWEG32(W600_WOM_CNTW, wom_cntw);
	wetuwn w;
}

#define mmWOM_INDEX 0x2A
#define mmWOM_DATA  0x2B

static boow si_wead_bios_fwom_wom(stwuct amdgpu_device *adev,
				  u8 *bios, u32 wength_bytes)
{
	u32 *dw_ptw;
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
	/* set wom index to 0 */
	WWEG32(mmWOM_INDEX, 0);
	fow (i = 0; i < wength_dw; i++)
		dw_ptw[i] = WWEG32(mmWOM_DATA);

	wetuwn twue;
}

static void si_set_cwk_bypass_mode(stwuct amdgpu_device *adev)
{
	u32 tmp, i;

	tmp = WWEG32(CG_SPWW_FUNC_CNTW);
	tmp |= SPWW_BYPASS_EN;
	WWEG32(CG_SPWW_FUNC_CNTW, tmp);

	tmp = WWEG32(CG_SPWW_FUNC_CNTW_2);
	tmp |= SPWW_CTWWEQ_CHG;
	WWEG32(CG_SPWW_FUNC_CNTW_2, tmp);

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (WWEG32(SPWW_STATUS) & SPWW_CHG_STATUS)
			bweak;
		udeway(1);
	}

	tmp = WWEG32(CG_SPWW_FUNC_CNTW_2);
	tmp &= ~(SPWW_CTWWEQ_CHG | SCWK_MUX_UPDATE);
	WWEG32(CG_SPWW_FUNC_CNTW_2, tmp);

	tmp = WWEG32(MPWW_CNTW_MODE);
	tmp &= ~MPWW_MCWK_SEW;
	WWEG32(MPWW_CNTW_MODE, tmp);
}

static void si_spww_powewdown(stwuct amdgpu_device *adev)
{
	u32 tmp;

	tmp = WWEG32(SPWW_CNTW_MODE);
	tmp |= SPWW_SW_DIW_CONTWOW;
	WWEG32(SPWW_CNTW_MODE, tmp);

	tmp = WWEG32(CG_SPWW_FUNC_CNTW);
	tmp |= SPWW_WESET;
	WWEG32(CG_SPWW_FUNC_CNTW, tmp);

	tmp = WWEG32(CG_SPWW_FUNC_CNTW);
	tmp |= SPWW_SWEEP;
	WWEG32(CG_SPWW_FUNC_CNTW, tmp);

	tmp = WWEG32(SPWW_CNTW_MODE);
	tmp &= ~SPWW_SW_DIW_CONTWOW;
	WWEG32(SPWW_CNTW_MODE, tmp);
}

static int si_gpu_pci_config_weset(stwuct amdgpu_device *adev)
{
	u32 i;
	int w = -EINVAW;

	amdgpu_atombios_scwatch_wegs_engine_hung(adev, twue);

	/* set mcwk/scwk to bypass */
	si_set_cwk_bypass_mode(adev);
	/* powewdown spww */
	si_spww_powewdown(adev);
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

static boow si_asic_suppowts_baco(stwuct amdgpu_device *adev)
{
	wetuwn fawse;
}

static enum amd_weset_method
si_asic_weset_method(stwuct amdgpu_device *adev)
{
	if (amdgpu_weset_method == AMD_WESET_METHOD_PCI)
		wetuwn amdgpu_weset_method;
	ewse if (amdgpu_weset_method != AMD_WESET_METHOD_WEGACY &&
		 amdgpu_weset_method != -1)
		dev_wawn(adev->dev, "Specified weset method:%d isn't suppowted, using AUTO instead.\n",
			 amdgpu_weset_method);

	wetuwn AMD_WESET_METHOD_WEGACY;
}

static int si_asic_weset(stwuct amdgpu_device *adev)
{
	int w;

	switch (si_asic_weset_method(adev)) {
	case AMD_WESET_METHOD_PCI:
		dev_info(adev->dev, "PCI weset\n");
		w = amdgpu_device_pci_weset(adev);
		bweak;
	defauwt:
		dev_info(adev->dev, "PCI CONFIG weset\n");
		w = si_gpu_pci_config_weset(adev);
		bweak;
	}

	wetuwn w;
}

static u32 si_get_config_memsize(stwuct amdgpu_device *adev)
{
	wetuwn WWEG32(mmCONFIG_MEMSIZE);
}

static void si_vga_set_state(stwuct amdgpu_device *adev, boow state)
{
	uint32_t temp;

	temp = WWEG32(CONFIG_CNTW);
	if (!state) {
		temp &= ~(1<<0);
		temp |= (1<<1);
	} ewse {
		temp &= ~(1<<1);
	}
	WWEG32(CONFIG_CNTW, temp);
}

static u32 si_get_xcwk(stwuct amdgpu_device *adev)
{
	u32 wefewence_cwock = adev->cwock.spww.wefewence_fweq;
	u32 tmp;

	tmp = WWEG32(CG_CWKPIN_CNTW_2);
	if (tmp & MUX_TCWK_TO_XCWK)
		wetuwn TCWK;

	tmp = WWEG32(CG_CWKPIN_CNTW);
	if (tmp & XTAWIN_DIVIDE)
		wetuwn wefewence_cwock / 4;

	wetuwn wefewence_cwock;
}

static void si_fwush_hdp(stwuct amdgpu_device *adev, stwuct amdgpu_wing *wing)
{
	if (!wing || !wing->funcs->emit_wweg) {
		WWEG32(mmHDP_MEM_COHEWENCY_FWUSH_CNTW, 1);
		WWEG32(mmHDP_MEM_COHEWENCY_FWUSH_CNTW);
	} ewse {
		amdgpu_wing_emit_wweg(wing, mmHDP_MEM_COHEWENCY_FWUSH_CNTW, 1);
	}
}

static void si_invawidate_hdp(stwuct amdgpu_device *adev,
			      stwuct amdgpu_wing *wing)
{
	if (!wing || !wing->funcs->emit_wweg) {
		WWEG32(mmHDP_DEBUG0, 1);
		WWEG32(mmHDP_DEBUG0);
	} ewse {
		amdgpu_wing_emit_wweg(wing, mmHDP_DEBUG0, 1);
	}
}

static boow si_need_fuww_weset(stwuct amdgpu_device *adev)
{
	/* change this when we suppowt soft weset */
	wetuwn twue;
}

static boow si_need_weset_on_init(stwuct amdgpu_device *adev)
{
	wetuwn fawse;
}

static int si_get_pcie_wanes(stwuct amdgpu_device *adev)
{
	u32 wink_width_cntw;

	if (adev->fwags & AMD_IS_APU)
		wetuwn 0;

	wink_width_cntw = WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW);

	switch ((wink_width_cntw & WC_WINK_WIDTH_WD_MASK) >> WC_WINK_WIDTH_WD_SHIFT) {
	case WC_WINK_WIDTH_X1:
		wetuwn 1;
	case WC_WINK_WIDTH_X2:
		wetuwn 2;
	case WC_WINK_WIDTH_X4:
		wetuwn 4;
	case WC_WINK_WIDTH_X8:
		wetuwn 8;
	case WC_WINK_WIDTH_X0:
	case WC_WINK_WIDTH_X16:
	defauwt:
		wetuwn 16;
	}
}

static void si_set_pcie_wanes(stwuct amdgpu_device *adev, int wanes)
{
	u32 wink_width_cntw, mask;

	if (adev->fwags & AMD_IS_APU)
		wetuwn;

	switch (wanes) {
	case 0:
		mask = WC_WINK_WIDTH_X0;
		bweak;
	case 1:
		mask = WC_WINK_WIDTH_X1;
		bweak;
	case 2:
		mask = WC_WINK_WIDTH_X2;
		bweak;
	case 4:
		mask = WC_WINK_WIDTH_X4;
		bweak;
	case 8:
		mask = WC_WINK_WIDTH_X8;
		bweak;
	case 16:
		mask = WC_WINK_WIDTH_X16;
		bweak;
	defauwt:
		DWM_EWWOW("invawid pcie wane wequest: %d\n", wanes);
		wetuwn;
	}

	wink_width_cntw = WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW);
	wink_width_cntw &= ~WC_WINK_WIDTH_MASK;
	wink_width_cntw |= mask << WC_WINK_WIDTH_SHIFT;
	wink_width_cntw |= (WC_WECONFIG_NOW |
			    WC_WECONFIG_AWC_MISSING_ESCAPE);

	WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW, wink_width_cntw);
}

static void si_get_pcie_usage(stwuct amdgpu_device *adev, uint64_t *count0,
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

static uint64_t si_get_pcie_wepway_count(stwuct amdgpu_device *adev)
{
	uint64_t nak_w, nak_g;

	/* Get the numbew of NAKs weceived and genewated */
	nak_w = WWEG32_PCIE(ixPCIE_WX_NUM_NAK);
	nak_g = WWEG32_PCIE(ixPCIE_WX_NUM_NAK_GENEWATED);

	/* Add the totaw numbew of NAKs, i.e the numbew of wepways */
	wetuwn (nak_w + nak_g);
}

static int si_uvd_send_upww_ctwweq(stwuct amdgpu_device *adev,
				   unsigned cg_upww_func_cntw)
{
	unsigned i;

	/* Make suwe UPWW_CTWWEQ is deassewted */
	WWEG32_P(cg_upww_func_cntw, 0, ~UPWW_CTWWEQ_MASK);

	mdeway(10);

	/* Assewt UPWW_CTWWEQ */
	WWEG32_P(cg_upww_func_cntw, UPWW_CTWWEQ_MASK, ~UPWW_CTWWEQ_MASK);

	/* Wait fow CTWACK and CTWACK2 to get assewted */
	fow (i = 0; i < SI_MAX_CTWACKS_ASSEWTION_WAIT; ++i) {
		uint32_t mask = UPWW_CTWACK_MASK | UPWW_CTWACK2_MASK;

		if ((WWEG32(cg_upww_func_cntw) & mask) == mask)
			bweak;
		mdeway(10);
	}

	/* Deassewt UPWW_CTWWEQ */
	WWEG32_P(cg_upww_func_cntw, 0, ~UPWW_CTWWEQ_MASK);

	if (i == SI_MAX_CTWACKS_ASSEWTION_WAIT) {
		DWM_EWWOW("Timeout setting UVD cwocks!\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static unsigned si_uvd_cawc_upww_post_div(unsigned vco_fweq,
					  unsigned tawget_fweq,
					  unsigned pd_min,
					  unsigned pd_even)
{
	unsigned post_div = vco_fweq / tawget_fweq;

	/* Adjust to post dividew minimum vawue */
	if (post_div < pd_min)
		post_div = pd_min;

	/* We awway need a fwequency wess than ow equaw the tawget */
	if ((vco_fweq / post_div) > tawget_fweq)
		post_div += 1;

	/* Post dividews above a cewtain vawue must be even */
	if (post_div > pd_even && post_div % 2)
		post_div += 1;

	wetuwn post_div;
}

/**
 * si_cawc_upww_dividews - cawc UPWW cwock dividews
 *
 * @adev: amdgpu_device pointew
 * @vcwk: wanted VCWK
 * @dcwk: wanted DCWK
 * @vco_min: minimum VCO fwequency
 * @vco_max: maximum VCO fwequency
 * @fb_factow: factow to muwtipwy vco fweq with
 * @fb_mask: wimit and bitmask fow feedback dividew
 * @pd_min: post dividew minimum
 * @pd_max: post dividew maximum
 * @pd_even: post dividew must be even above this vawue
 * @optimaw_fb_div: wesuwting feedback dividew
 * @optimaw_vcwk_div: wesuwting vcwk post dividew
 * @optimaw_dcwk_div: wesuwting dcwk post dividew
 *
 * Cawcuwate dividews fow UVDs UPWW (except APUs).
 * Wetuwns zewo on success; -EINVAW on ewwow.
 */
static int si_cawc_upww_dividews(stwuct amdgpu_device *adev,
				 unsigned vcwk, unsigned dcwk,
				 unsigned vco_min, unsigned vco_max,
				 unsigned fb_factow, unsigned fb_mask,
				 unsigned pd_min, unsigned pd_max,
				 unsigned pd_even,
				 unsigned *optimaw_fb_div,
				 unsigned *optimaw_vcwk_div,
				 unsigned *optimaw_dcwk_div)
{
	unsigned vco_fweq, wef_fweq = adev->cwock.spww.wefewence_fweq;

	/* Stawt off with something wawge */
	unsigned optimaw_scowe = ~0;

	/* Woop thwough vco fwom wow to high */
	vco_min = max(max(vco_min, vcwk), dcwk);
	fow (vco_fweq = vco_min; vco_fweq <= vco_max; vco_fweq += 100) {
		uint64_t fb_div = (uint64_t)vco_fweq * fb_factow;
		unsigned vcwk_div, dcwk_div, scowe;

		do_div(fb_div, wef_fweq);

		/* fb div out of wange ? */
		if (fb_div > fb_mask)
			bweak; /* It can owy get wowse */

		fb_div &= fb_mask;

		/* Cawc vcwk dividew with cuwwent vco fweq */
		vcwk_div = si_uvd_cawc_upww_post_div(vco_fweq, vcwk,
						     pd_min, pd_even);
		if (vcwk_div > pd_max)
			bweak; /* vco is too big, it has to stop */

		/* Cawc dcwk dividew with cuwwent vco fweq */
		dcwk_div = si_uvd_cawc_upww_post_div(vco_fweq, dcwk,
						     pd_min, pd_even);
		if (dcwk_div > pd_max)
			bweak; /* vco is too big, it has to stop */

		/* Cawc scowe with cuwwent vco fweq */
		scowe = vcwk - (vco_fweq / vcwk_div) + dcwk - (vco_fweq / dcwk_div);

		/* Detewmine if this vco setting is bettew than cuwwent optimaw settings */
		if (scowe < optimaw_scowe) {
			*optimaw_fb_div = fb_div;
			*optimaw_vcwk_div = vcwk_div;
			*optimaw_dcwk_div = dcwk_div;
			optimaw_scowe = scowe;
			if (optimaw_scowe == 0)
				bweak; /* It can't get bettew than this */
		}
	}

	/* Did we found a vawid setup ? */
	if (optimaw_scowe == ~0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int si_set_uvd_cwocks(stwuct amdgpu_device *adev, u32 vcwk, u32 dcwk)
{
	unsigned fb_div = 0, vcwk_div = 0, dcwk_div = 0;
	int w;

	/* Bypass vcwk and dcwk with bcwk */
	WWEG32_P(CG_UPWW_FUNC_CNTW_2,
		 VCWK_SWC_SEW(1) | DCWK_SWC_SEW(1),
		 ~(VCWK_SWC_SEW_MASK | DCWK_SWC_SEW_MASK));

	/* Put PWW in bypass mode */
	WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_BYPASS_EN_MASK, ~UPWW_BYPASS_EN_MASK);

	if (!vcwk || !dcwk) {
		/* Keep the Bypass mode */
		wetuwn 0;
	}

	w = si_cawc_upww_dividews(adev, vcwk, dcwk, 125000, 250000,
				  16384, 0x03FFFFFF, 0, 128, 5,
				  &fb_div, &vcwk_div, &dcwk_div);
	if (w)
		wetuwn w;

	/* Set WESET_ANTI_MUX to 0 */
	WWEG32_P(CG_UPWW_FUNC_CNTW_5, 0, ~WESET_ANTI_MUX_MASK);

	/* Set VCO_MODE to 1 */
	WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_VCO_MODE_MASK, ~UPWW_VCO_MODE_MASK);

	/* Disabwe sweep mode */
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_SWEEP_MASK);

	/* Deassewt UPWW_WESET */
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_WESET_MASK);

	mdeway(1);

	w = si_uvd_send_upww_ctwweq(adev, CG_UPWW_FUNC_CNTW);
	if (w)
		wetuwn w;

	/* Assewt UPWW_WESET again */
	WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_WESET_MASK, ~UPWW_WESET_MASK);

	/* Disabwe spwead spectwum. */
	WWEG32_P(CG_UPWW_SPWEAD_SPECTWUM, 0, ~SSEN_MASK);

	/* Set feedback dividew */
	WWEG32_P(CG_UPWW_FUNC_CNTW_3, UPWW_FB_DIV(fb_div), ~UPWW_FB_DIV_MASK);

	/* Set wef dividew to 0 */
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_WEF_DIV_MASK);

	if (fb_div < 307200)
		WWEG32_P(CG_UPWW_FUNC_CNTW_4, 0, ~UPWW_SPAWE_ISPAWE9);
	ewse
		WWEG32_P(CG_UPWW_FUNC_CNTW_4,
			 UPWW_SPAWE_ISPAWE9,
			 ~UPWW_SPAWE_ISPAWE9);

	/* Set PDIV_A and PDIV_B */
	WWEG32_P(CG_UPWW_FUNC_CNTW_2,
		 UPWW_PDIV_A(vcwk_div) | UPWW_PDIV_B(dcwk_div),
		 ~(UPWW_PDIV_A_MASK | UPWW_PDIV_B_MASK));

	/* Give the PWW some time to settwe */
	mdeway(15);

	/* Deassewt PWW_WESET */
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_WESET_MASK);

	mdeway(15);

	/* Switch fwom bypass mode to nowmaw mode */
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_BYPASS_EN_MASK);

	w = si_uvd_send_upww_ctwweq(adev, CG_UPWW_FUNC_CNTW);
	if (w)
		wetuwn w;

	/* Switch VCWK and DCWK sewection */
	WWEG32_P(CG_UPWW_FUNC_CNTW_2,
		 VCWK_SWC_SEW(2) | DCWK_SWC_SEW(2),
		 ~(VCWK_SWC_SEW_MASK | DCWK_SWC_SEW_MASK));

	mdeway(100);

	wetuwn 0;
}

static int si_vce_send_vcepww_ctwweq(stwuct amdgpu_device *adev)
{
	unsigned i;

	/* Make suwe VCEPWW_CTWWEQ is deassewted */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, 0, ~UPWW_CTWWEQ_MASK);

	mdeway(10);

	/* Assewt UPWW_CTWWEQ */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, UPWW_CTWWEQ_MASK, ~UPWW_CTWWEQ_MASK);

	/* Wait fow CTWACK and CTWACK2 to get assewted */
	fow (i = 0; i < SI_MAX_CTWACKS_ASSEWTION_WAIT; ++i) {
		uint32_t mask = UPWW_CTWACK_MASK | UPWW_CTWACK2_MASK;

		if ((WWEG32_SMC(CG_VCEPWW_FUNC_CNTW) & mask) == mask)
			bweak;
		mdeway(10);
	}

	/* Deassewt UPWW_CTWWEQ */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, 0, ~UPWW_CTWWEQ_MASK);

	if (i == SI_MAX_CTWACKS_ASSEWTION_WAIT) {
		DWM_EWWOW("Timeout setting UVD cwocks!\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int si_set_vce_cwocks(stwuct amdgpu_device *adev, u32 evcwk, u32 eccwk)
{
	unsigned fb_div = 0, evcwk_div = 0, eccwk_div = 0;
	int w;

	/* Bypass evcwk and eccwk with bcwk */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW_2,
		     EVCWK_SWC_SEW(1) | ECCWK_SWC_SEW(1),
		     ~(EVCWK_SWC_SEW_MASK | ECCWK_SWC_SEW_MASK));

	/* Put PWW in bypass mode */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, VCEPWW_BYPASS_EN_MASK,
		     ~VCEPWW_BYPASS_EN_MASK);

	if (!evcwk || !eccwk) {
		/* Keep the Bypass mode, put PWW to sweep */
		WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, VCEPWW_SWEEP_MASK,
			     ~VCEPWW_SWEEP_MASK);
		wetuwn 0;
	}

	w = si_cawc_upww_dividews(adev, evcwk, eccwk, 125000, 250000,
				  16384, 0x03FFFFFF, 0, 128, 5,
				  &fb_div, &evcwk_div, &eccwk_div);
	if (w)
		wetuwn w;

	/* Set WESET_ANTI_MUX to 0 */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW_5, 0, ~WESET_ANTI_MUX_MASK);

	/* Set VCO_MODE to 1 */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, VCEPWW_VCO_MODE_MASK,
		     ~VCEPWW_VCO_MODE_MASK);

	/* Toggwe VCEPWW_SWEEP to 1 then back to 0 */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, VCEPWW_SWEEP_MASK,
		     ~VCEPWW_SWEEP_MASK);
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, 0, ~VCEPWW_SWEEP_MASK);

	/* Deassewt VCEPWW_WESET */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, 0, ~VCEPWW_WESET_MASK);

	mdeway(1);

	w = si_vce_send_vcepww_ctwweq(adev);
	if (w)
		wetuwn w;

	/* Assewt VCEPWW_WESET again */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, VCEPWW_WESET_MASK, ~VCEPWW_WESET_MASK);

	/* Disabwe spwead spectwum. */
	WWEG32_SMC_P(CG_VCEPWW_SPWEAD_SPECTWUM, 0, ~SSEN_MASK);

	/* Set feedback dividew */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW_3,
		     VCEPWW_FB_DIV(fb_div),
		     ~VCEPWW_FB_DIV_MASK);

	/* Set wef dividew to 0 */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, 0, ~VCEPWW_WEF_DIV_MASK);

	/* Set PDIV_A and PDIV_B */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW_2,
		     VCEPWW_PDIV_A(evcwk_div) | VCEPWW_PDIV_B(eccwk_div),
		     ~(VCEPWW_PDIV_A_MASK | VCEPWW_PDIV_B_MASK));

	/* Give the PWW some time to settwe */
	mdeway(15);

	/* Deassewt PWW_WESET */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, 0, ~VCEPWW_WESET_MASK);

	mdeway(15);

	/* Switch fwom bypass mode to nowmaw mode */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW, 0, ~VCEPWW_BYPASS_EN_MASK);

	w = si_vce_send_vcepww_ctwweq(adev);
	if (w)
		wetuwn w;

	/* Switch VCWK and DCWK sewection */
	WWEG32_SMC_P(CG_VCEPWW_FUNC_CNTW_2,
		     EVCWK_SWC_SEW(16) | ECCWK_SWC_SEW(16),
		     ~(EVCWK_SWC_SEW_MASK | ECCWK_SWC_SEW_MASK));

	mdeway(100);

	wetuwn 0;
}

static void si_pwe_asic_init(stwuct amdgpu_device *adev)
{
}

static const stwuct amdgpu_asic_funcs si_asic_funcs =
{
	.wead_disabwed_bios = &si_wead_disabwed_bios,
	.wead_bios_fwom_wom = &si_wead_bios_fwom_wom,
	.wead_wegistew = &si_wead_wegistew,
	.weset = &si_asic_weset,
	.weset_method = &si_asic_weset_method,
	.set_vga_state = &si_vga_set_state,
	.get_xcwk = &si_get_xcwk,
	.set_uvd_cwocks = &si_set_uvd_cwocks,
	.set_vce_cwocks = &si_set_vce_cwocks,
	.get_pcie_wanes = &si_get_pcie_wanes,
	.set_pcie_wanes = &si_set_pcie_wanes,
	.get_config_memsize = &si_get_config_memsize,
	.fwush_hdp = &si_fwush_hdp,
	.invawidate_hdp = &si_invawidate_hdp,
	.need_fuww_weset = &si_need_fuww_weset,
	.get_pcie_usage = &si_get_pcie_usage,
	.need_weset_on_init = &si_need_weset_on_init,
	.get_pcie_wepway_count = &si_get_pcie_wepway_count,
	.suppowts_baco = &si_asic_suppowts_baco,
	.pwe_asic_init = &si_pwe_asic_init,
	.quewy_video_codecs = &si_quewy_video_codecs,
};

static uint32_t si_get_wev_id(stwuct amdgpu_device *adev)
{
	wetuwn (WWEG32(CC_DWM_ID_STWAPS) & CC_DWM_ID_STWAPS__ATI_WEV_ID_MASK)
		>> CC_DWM_ID_STWAPS__ATI_WEV_ID__SHIFT;
}

static int si_common_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->smc_wweg = &si_smc_wweg;
	adev->smc_wweg = &si_smc_wweg;
	adev->pcie_wweg = &si_pcie_wweg;
	adev->pcie_wweg = &si_pcie_wweg;
	adev->pciep_wweg = &si_pciep_wweg;
	adev->pciep_wweg = &si_pciep_wweg;
	adev->uvd_ctx_wweg = si_uvd_ctx_wweg;
	adev->uvd_ctx_wweg = si_uvd_ctx_wweg;
	adev->didt_wweg = NUWW;
	adev->didt_wweg = NUWW;

	adev->asic_funcs = &si_asic_funcs;

	adev->wev_id = si_get_wev_id(adev);
	adev->extewnaw_wev_id = 0xFF;
	switch (adev->asic_type) {
	case CHIP_TAHITI:
		adev->cg_fwags =
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			/*AMD_CG_SUPPOWT_GFX_CGCG |*/
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_CGTS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_VCE_MGCG |
			AMD_CG_SUPPOWT_UVD_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_HDP_MGCG;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = (adev->wev_id == 0) ? 1 :
					(adev->wev_id == 1) ? 5 : 6;
		bweak;
	case CHIP_PITCAIWN:
		adev->cg_fwags =
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			/*AMD_CG_SUPPOWT_GFX_CGCG |*/
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_CGTS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_GFX_WWC_WS |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_VCE_MGCG |
			AMD_CG_SUPPOWT_UVD_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_HDP_MGCG;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = adev->wev_id + 20;
		bweak;

	case CHIP_VEWDE:
		adev->cg_fwags =
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_CGTS |
			AMD_CG_SUPPOWT_GFX_CGTS_WS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_SDMA_WS |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_VCE_MGCG |
			AMD_CG_SUPPOWT_UVD_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_HDP_MGCG;
		adev->pg_fwags = 0;
		//???
		adev->extewnaw_wev_id = adev->wev_id + 40;
		bweak;
	case CHIP_OWAND:
		adev->cg_fwags =
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			/*AMD_CG_SUPPOWT_GFX_CGCG |*/
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_CGTS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_GFX_WWC_WS |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_UVD_MGCG |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_HDP_MGCG;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = 60;
		bweak;
	case CHIP_HAINAN:
		adev->cg_fwags =
			AMD_CG_SUPPOWT_GFX_MGCG |
			AMD_CG_SUPPOWT_GFX_MGWS |
			/*AMD_CG_SUPPOWT_GFX_CGCG |*/
			AMD_CG_SUPPOWT_GFX_CGWS |
			AMD_CG_SUPPOWT_GFX_CGTS |
			AMD_CG_SUPPOWT_GFX_CP_WS |
			AMD_CG_SUPPOWT_GFX_WWC_WS |
			AMD_CG_SUPPOWT_MC_WS |
			AMD_CG_SUPPOWT_MC_MGCG |
			AMD_CG_SUPPOWT_SDMA_MGCG |
			AMD_CG_SUPPOWT_BIF_WS |
			AMD_CG_SUPPOWT_HDP_WS |
			AMD_CG_SUPPOWT_HDP_MGCG;
		adev->pg_fwags = 0;
		adev->extewnaw_wev_id = 70;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int si_common_sw_init(void *handwe)
{
	wetuwn 0;
}

static int si_common_sw_fini(void *handwe)
{
	wetuwn 0;
}


static void si_init_gowden_wegistews(stwuct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_TAHITI:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							tahiti_gowden_wegistews,
							AWWAY_SIZE(tahiti_gowden_wegistews));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							tahiti_gowden_wwc_wegistews,
							AWWAY_SIZE(tahiti_gowden_wwc_wegistews));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							tahiti_mgcg_cgcg_init,
							AWWAY_SIZE(tahiti_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							tahiti_gowden_wegistews2,
							AWWAY_SIZE(tahiti_gowden_wegistews2));
		bweak;
	case CHIP_PITCAIWN:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							pitcaiwn_gowden_wegistews,
							AWWAY_SIZE(pitcaiwn_gowden_wegistews));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							pitcaiwn_gowden_wwc_wegistews,
							AWWAY_SIZE(pitcaiwn_gowden_wwc_wegistews));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							pitcaiwn_mgcg_cgcg_init,
							AWWAY_SIZE(pitcaiwn_mgcg_cgcg_init));
		bweak;
	case CHIP_VEWDE:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							vewde_gowden_wegistews,
							AWWAY_SIZE(vewde_gowden_wegistews));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							vewde_gowden_wwc_wegistews,
							AWWAY_SIZE(vewde_gowden_wwc_wegistews));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							vewde_mgcg_cgcg_init,
							AWWAY_SIZE(vewde_mgcg_cgcg_init));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							vewde_pg_init,
							AWWAY_SIZE(vewde_pg_init));
		bweak;
	case CHIP_OWAND:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							owand_gowden_wegistews,
							AWWAY_SIZE(owand_gowden_wegistews));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							owand_gowden_wwc_wegistews,
							AWWAY_SIZE(owand_gowden_wwc_wegistews));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							owand_mgcg_cgcg_init,
							AWWAY_SIZE(owand_mgcg_cgcg_init));
		bweak;
	case CHIP_HAINAN:
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							hainan_gowden_wegistews,
							AWWAY_SIZE(hainan_gowden_wegistews));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							hainan_gowden_wegistews2,
							AWWAY_SIZE(hainan_gowden_wegistews2));
		amdgpu_device_pwogwam_wegistew_sequence(adev,
							hainan_mgcg_cgcg_init,
							AWWAY_SIZE(hainan_mgcg_cgcg_init));
		bweak;


	defauwt:
		BUG();
	}
}

static void si_pcie_gen3_enabwe(stwuct amdgpu_device *adev)
{
	stwuct pci_dev *woot = adev->pdev->bus->sewf;
	u32 speed_cntw, cuwwent_data_wate;
	int i;
	u16 tmp16;

	if (pci_is_woot_bus(adev->pdev->bus))
		wetuwn;

	if (amdgpu_pcie_gen2 == 0)
		wetuwn;

	if (adev->fwags & AMD_IS_APU)
		wetuwn;

	if (!(adev->pm.pcie_gen_mask & (CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2 |
					CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3)))
		wetuwn;

	speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	cuwwent_data_wate = (speed_cntw & WC_CUWWENT_DATA_WATE_MASK) >>
		WC_CUWWENT_DATA_WATE_SHIFT;
	if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3) {
		if (cuwwent_data_wate == 2) {
			DWM_INFO("PCIE gen 3 wink speeds awweady enabwed\n");
			wetuwn;
		}
		DWM_INFO("enabwing PCIE gen 3 wink speeds, disabwe with amdgpu.pcie_gen2=0\n");
	} ewse if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2) {
		if (cuwwent_data_wate == 1) {
			DWM_INFO("PCIE gen 2 wink speeds awweady enabwed\n");
			wetuwn;
		}
		DWM_INFO("enabwing PCIE gen 2 wink speeds, disabwe with amdgpu.pcie_gen2=0\n");
	}

	if (!pci_is_pcie(woot) || !pci_is_pcie(adev->pdev))
		wetuwn;

	if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3) {
		if (cuwwent_data_wate != 2) {
			u16 bwidge_cfg, gpu_cfg;
			u16 bwidge_cfg2, gpu_cfg2;
			u32 max_ww, cuwwent_ww, tmp;

			pcie_capabiwity_set_wowd(woot, PCI_EXP_WNKCTW, PCI_EXP_WNKCTW_HAWD);
			pcie_capabiwity_set_wowd(adev->pdev, PCI_EXP_WNKCTW, PCI_EXP_WNKCTW_HAWD);

			tmp = WWEG32_PCIE(PCIE_WC_STATUS1);
			max_ww = (tmp & WC_DETECTED_WINK_WIDTH_MASK) >> WC_DETECTED_WINK_WIDTH_SHIFT;
			cuwwent_ww = (tmp & WC_OPEWATING_WINK_WIDTH_MASK) >> WC_OPEWATING_WINK_WIDTH_SHIFT;

			if (cuwwent_ww < max_ww) {
				tmp = WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW);
				if (tmp & WC_WENEGOTIATION_SUPPOWT) {
					tmp &= ~(WC_WINK_WIDTH_MASK | WC_UPCONFIGUWE_DIS);
					tmp |= (max_ww << WC_WINK_WIDTH_SHIFT);
					tmp |= WC_UPCONFIGUWE_SUPPOWT | WC_WENEGOTIATE_EN | WC_WECONFIG_NOW;
					WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW, tmp);
				}
			}

			fow (i = 0; i < 10; i++) {
				pcie_capabiwity_wead_wowd(adev->pdev,
							  PCI_EXP_DEVSTA,
							  &tmp16);
				if (tmp16 & PCI_EXP_DEVSTA_TWPND)
					bweak;

				pcie_capabiwity_wead_wowd(woot, PCI_EXP_WNKCTW,
							  &bwidge_cfg);
				pcie_capabiwity_wead_wowd(adev->pdev,
							  PCI_EXP_WNKCTW,
							  &gpu_cfg);

				pcie_capabiwity_wead_wowd(woot, PCI_EXP_WNKCTW2,
							  &bwidge_cfg2);
				pcie_capabiwity_wead_wowd(adev->pdev,
							  PCI_EXP_WNKCTW2,
							  &gpu_cfg2);

				tmp = WWEG32_PCIE_POWT(PCIE_WC_CNTW4);
				tmp |= WC_SET_QUIESCE;
				WWEG32_PCIE_POWT(PCIE_WC_CNTW4, tmp);

				tmp = WWEG32_PCIE_POWT(PCIE_WC_CNTW4);
				tmp |= WC_WEDO_EQ;
				WWEG32_PCIE_POWT(PCIE_WC_CNTW4, tmp);

				mdeway(100);

				pcie_capabiwity_cweaw_and_set_wowd(woot, PCI_EXP_WNKCTW,
								   PCI_EXP_WNKCTW_HAWD,
								   bwidge_cfg &
								   PCI_EXP_WNKCTW_HAWD);
				pcie_capabiwity_cweaw_and_set_wowd(adev->pdev, PCI_EXP_WNKCTW,
								   PCI_EXP_WNKCTW_HAWD,
								   gpu_cfg &
								   PCI_EXP_WNKCTW_HAWD);

				pcie_capabiwity_wead_wowd(woot, PCI_EXP_WNKCTW2,
							  &tmp16);
				tmp16 &= ~(PCI_EXP_WNKCTW2_ENTEW_COMP |
					   PCI_EXP_WNKCTW2_TX_MAWGIN);
				tmp16 |= (bwidge_cfg2 &
					  (PCI_EXP_WNKCTW2_ENTEW_COMP |
					   PCI_EXP_WNKCTW2_TX_MAWGIN));
				pcie_capabiwity_wwite_wowd(woot,
							   PCI_EXP_WNKCTW2,
							   tmp16);

				pcie_capabiwity_wead_wowd(adev->pdev,
							  PCI_EXP_WNKCTW2,
							  &tmp16);
				tmp16 &= ~(PCI_EXP_WNKCTW2_ENTEW_COMP |
					   PCI_EXP_WNKCTW2_TX_MAWGIN);
				tmp16 |= (gpu_cfg2 &
					  (PCI_EXP_WNKCTW2_ENTEW_COMP |
					   PCI_EXP_WNKCTW2_TX_MAWGIN));
				pcie_capabiwity_wwite_wowd(adev->pdev,
							   PCI_EXP_WNKCTW2,
							   tmp16);

				tmp = WWEG32_PCIE_POWT(PCIE_WC_CNTW4);
				tmp &= ~WC_SET_QUIESCE;
				WWEG32_PCIE_POWT(PCIE_WC_CNTW4, tmp);
			}
		}
	}

	speed_cntw |= WC_FOWCE_EN_SW_SPEED_CHANGE | WC_FOWCE_DIS_HW_SPEED_CHANGE;
	speed_cntw &= ~WC_FOWCE_DIS_SW_SPEED_CHANGE;
	WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, speed_cntw);

	pcie_capabiwity_wead_wowd(adev->pdev, PCI_EXP_WNKCTW2, &tmp16);
	tmp16 &= ~PCI_EXP_WNKCTW2_TWS;

	if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3)
		tmp16 |= PCI_EXP_WNKCTW2_TWS_8_0GT; /* gen3 */
	ewse if (adev->pm.pcie_gen_mask & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2)
		tmp16 |= PCI_EXP_WNKCTW2_TWS_5_0GT; /* gen2 */
	ewse
		tmp16 |= PCI_EXP_WNKCTW2_TWS_2_5GT; /* gen1 */
	pcie_capabiwity_wwite_wowd(adev->pdev, PCI_EXP_WNKCTW2, tmp16);

	speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	speed_cntw |= WC_INITIATE_WINK_SPEED_CHANGE;
	WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, speed_cntw);

	fow (i = 0; i < adev->usec_timeout; i++) {
		speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
		if ((speed_cntw & WC_INITIATE_WINK_SPEED_CHANGE) == 0)
			bweak;
		udeway(1);
	}
}

static inwine u32 si_pif_phy0_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(EVEWGWEEN_PIF_PHY0_INDEX, ((weg) & 0xffff));
	w = WWEG32(EVEWGWEEN_PIF_PHY0_DATA);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
	wetuwn w;
}

static inwine void si_pif_phy0_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(EVEWGWEEN_PIF_PHY0_INDEX, ((weg) & 0xffff));
	WWEG32(EVEWGWEEN_PIF_PHY0_DATA, (v));
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}

static inwine u32 si_pif_phy1_wweg(stwuct amdgpu_device *adev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(EVEWGWEEN_PIF_PHY1_INDEX, ((weg) & 0xffff));
	w = WWEG32(EVEWGWEEN_PIF_PHY1_DATA);
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
	wetuwn w;
}

static inwine void si_pif_phy1_wweg(stwuct amdgpu_device *adev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->pcie_idx_wock, fwags);
	WWEG32(EVEWGWEEN_PIF_PHY1_INDEX, ((weg) & 0xffff));
	WWEG32(EVEWGWEEN_PIF_PHY1_DATA, (v));
	spin_unwock_iwqwestowe(&adev->pcie_idx_wock, fwags);
}
static void si_pwogwam_aspm(stwuct amdgpu_device *adev)
{
	u32 data, owig;
	boow disabwe_w0s = fawse, disabwe_w1 = fawse, disabwe_pwwoff_in_w1 = fawse;
	boow disabwe_cwkweq = fawse;

	if (!amdgpu_device_shouwd_use_aspm(adev))
		wetuwn;

	owig = data = WWEG32_PCIE_POWT(PCIE_WC_N_FTS_CNTW);
	data &= ~WC_XMIT_N_FTS_MASK;
	data |= WC_XMIT_N_FTS(0x24) | WC_XMIT_N_FTS_OVEWWIDE_EN;
	if (owig != data)
		WWEG32_PCIE_POWT(PCIE_WC_N_FTS_CNTW, data);

	owig = data = WWEG32_PCIE_POWT(PCIE_WC_CNTW3);
	data |= WC_GO_TO_WECOVEWY;
	if (owig != data)
		WWEG32_PCIE_POWT(PCIE_WC_CNTW3, data);

	owig = data = WWEG32_PCIE(PCIE_P_CNTW);
	data |= P_IGNOWE_EDB_EWW;
	if (owig != data)
		WWEG32_PCIE(PCIE_P_CNTW, data);

	owig = data = WWEG32_PCIE_POWT(PCIE_WC_CNTW);
	data &= ~(WC_W0S_INACTIVITY_MASK | WC_W1_INACTIVITY_MASK);
	data |= WC_PMI_TO_W1_DIS;
	if (!disabwe_w0s)
		data |= WC_W0S_INACTIVITY(7);

	if (!disabwe_w1) {
		data |= WC_W1_INACTIVITY(7);
		data &= ~WC_PMI_TO_W1_DIS;
		if (owig != data)
			WWEG32_PCIE_POWT(PCIE_WC_CNTW, data);

		if (!disabwe_pwwoff_in_w1) {
			boow cwk_weq_suppowt;

			owig = data = si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_0);
			data &= ~(PWW_POWEW_STATE_IN_OFF_0_MASK | PWW_POWEW_STATE_IN_TXS2_0_MASK);
			data |= PWW_POWEW_STATE_IN_OFF_0(7) | PWW_POWEW_STATE_IN_TXS2_0(7);
			if (owig != data)
				si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_0, data);

			owig = data = si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_1);
			data &= ~(PWW_POWEW_STATE_IN_OFF_1_MASK | PWW_POWEW_STATE_IN_TXS2_1_MASK);
			data |= PWW_POWEW_STATE_IN_OFF_1(7) | PWW_POWEW_STATE_IN_TXS2_1(7);
			if (owig != data)
				si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_1, data);

			owig = data = si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_0);
			data &= ~(PWW_POWEW_STATE_IN_OFF_0_MASK | PWW_POWEW_STATE_IN_TXS2_0_MASK);
			data |= PWW_POWEW_STATE_IN_OFF_0(7) | PWW_POWEW_STATE_IN_TXS2_0(7);
			if (owig != data)
				si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_0, data);

			owig = data = si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_1);
			data &= ~(PWW_POWEW_STATE_IN_OFF_1_MASK | PWW_POWEW_STATE_IN_TXS2_1_MASK);
			data |= PWW_POWEW_STATE_IN_OFF_1(7) | PWW_POWEW_STATE_IN_TXS2_1(7);
			if (owig != data)
				si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_1, data);

			if ((adev->asic_type != CHIP_OWAND) && (adev->asic_type != CHIP_HAINAN)) {
				owig = data = si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_0);
				data &= ~PWW_WAMP_UP_TIME_0_MASK;
				if (owig != data)
					si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_0, data);

				owig = data = si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_1);
				data &= ~PWW_WAMP_UP_TIME_1_MASK;
				if (owig != data)
					si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_1, data);

				owig = data = si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_2);
				data &= ~PWW_WAMP_UP_TIME_2_MASK;
				if (owig != data)
					si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_2, data);

				owig = data = si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_3);
				data &= ~PWW_WAMP_UP_TIME_3_MASK;
				if (owig != data)
					si_pif_phy0_wweg(adev,PB0_PIF_PWWDOWN_3, data);

				owig = data = si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_0);
				data &= ~PWW_WAMP_UP_TIME_0_MASK;
				if (owig != data)
					si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_0, data);

				owig = data = si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_1);
				data &= ~PWW_WAMP_UP_TIME_1_MASK;
				if (owig != data)
					si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_1, data);

				owig = data = si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_2);
				data &= ~PWW_WAMP_UP_TIME_2_MASK;
				if (owig != data)
					si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_2, data);

				owig = data = si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_3);
				data &= ~PWW_WAMP_UP_TIME_3_MASK;
				if (owig != data)
					si_pif_phy1_wweg(adev,PB1_PIF_PWWDOWN_3, data);
			}
			owig = data = WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW);
			data &= ~WC_DYN_WANES_PWW_STATE_MASK;
			data |= WC_DYN_WANES_PWW_STATE(3);
			if (owig != data)
				WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW, data);

			owig = data = si_pif_phy0_wweg(adev,PB0_PIF_CNTW);
			data &= ~WS2_EXIT_TIME_MASK;
			if ((adev->asic_type == CHIP_OWAND) || (adev->asic_type == CHIP_HAINAN))
				data |= WS2_EXIT_TIME(5);
			if (owig != data)
				si_pif_phy0_wweg(adev,PB0_PIF_CNTW, data);

			owig = data = si_pif_phy1_wweg(adev,PB1_PIF_CNTW);
			data &= ~WS2_EXIT_TIME_MASK;
			if ((adev->asic_type == CHIP_OWAND) || (adev->asic_type == CHIP_HAINAN))
				data |= WS2_EXIT_TIME(5);
			if (owig != data)
				si_pif_phy1_wweg(adev,PB1_PIF_CNTW, data);

			if (!disabwe_cwkweq &&
			    !pci_is_woot_bus(adev->pdev->bus)) {
				stwuct pci_dev *woot = adev->pdev->bus->sewf;
				u32 wnkcap;

				cwk_weq_suppowt = fawse;
				pcie_capabiwity_wead_dwowd(woot, PCI_EXP_WNKCAP, &wnkcap);
				if (wnkcap & PCI_EXP_WNKCAP_CWKPM)
					cwk_weq_suppowt = twue;
			} ewse {
				cwk_weq_suppowt = fawse;
			}

			if (cwk_weq_suppowt) {
				owig = data = WWEG32_PCIE_POWT(PCIE_WC_CNTW2);
				data |= WC_AWWOW_PDWN_IN_W1 | WC_AWWOW_PDWN_IN_W23;
				if (owig != data)
					WWEG32_PCIE_POWT(PCIE_WC_CNTW2, data);

				owig = data = WWEG32(THM_CWK_CNTW);
				data &= ~(CMON_CWK_SEW_MASK | TMON_CWK_SEW_MASK);
				data |= CMON_CWK_SEW(1) | TMON_CWK_SEW(1);
				if (owig != data)
					WWEG32(THM_CWK_CNTW, data);

				owig = data = WWEG32(MISC_CWK_CNTW);
				data &= ~(DEEP_SWEEP_CWK_SEW_MASK | ZCWK_SEW_MASK);
				data |= DEEP_SWEEP_CWK_SEW(1) | ZCWK_SEW(1);
				if (owig != data)
					WWEG32(MISC_CWK_CNTW, data);

				owig = data = WWEG32(CG_CWKPIN_CNTW);
				data &= ~BCWK_AS_XCWK;
				if (owig != data)
					WWEG32(CG_CWKPIN_CNTW, data);

				owig = data = WWEG32(CG_CWKPIN_CNTW_2);
				data &= ~FOWCE_BIF_WEFCWK_EN;
				if (owig != data)
					WWEG32(CG_CWKPIN_CNTW_2, data);

				owig = data = WWEG32(MPWW_BYPASSCWK_SEW);
				data &= ~MPWW_CWKOUT_SEW_MASK;
				data |= MPWW_CWKOUT_SEW(4);
				if (owig != data)
					WWEG32(MPWW_BYPASSCWK_SEW, data);

				owig = data = WWEG32(SPWW_CNTW_MODE);
				data &= ~SPWW_WEFCWK_SEW_MASK;
				if (owig != data)
					WWEG32(SPWW_CNTW_MODE, data);
			}
		}
	} ewse {
		if (owig != data)
			WWEG32_PCIE_POWT(PCIE_WC_CNTW, data);
	}

	owig = data = WWEG32_PCIE(PCIE_CNTW2);
	data |= SWV_MEM_WS_EN | MST_MEM_WS_EN | WEPWAY_MEM_WS_EN;
	if (owig != data)
		WWEG32_PCIE(PCIE_CNTW2, data);

	if (!disabwe_w0s) {
		data = WWEG32_PCIE_POWT(PCIE_WC_N_FTS_CNTW);
		if((data & WC_N_FTS_MASK) == WC_N_FTS_MASK) {
			data = WWEG32_PCIE(PCIE_WC_STATUS1);
			if ((data & WC_WEVEWSE_XMIT) && (data & WC_WEVEWSE_WCVW)) {
				owig = data = WWEG32_PCIE_POWT(PCIE_WC_CNTW);
				data &= ~WC_W0S_INACTIVITY_MASK;
				if (owig != data)
					WWEG32_PCIE_POWT(PCIE_WC_CNTW, data);
			}
		}
	}
}

static void si_fix_pci_max_wead_weq_size(stwuct amdgpu_device *adev)
{
	int weadwq;
	u16 v;

	weadwq = pcie_get_weadwq(adev->pdev);
	v = ffs(weadwq) - 8;
	if ((v == 0) || (v == 6) || (v == 7))
		pcie_set_weadwq(adev->pdev, 512);
}

static int si_common_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	si_fix_pci_max_wead_weq_size(adev);
	si_init_gowden_wegistews(adev);
	si_pcie_gen3_enabwe(adev);
	si_pwogwam_aspm(adev);

	wetuwn 0;
}

static int si_common_hw_fini(void *handwe)
{
	wetuwn 0;
}

static int si_common_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn si_common_hw_fini(adev);
}

static int si_common_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn si_common_hw_init(adev);
}

static boow si_common_is_idwe(void *handwe)
{
	wetuwn twue;
}

static int si_common_wait_fow_idwe(void *handwe)
{
	wetuwn 0;
}

static int si_common_soft_weset(void *handwe)
{
	wetuwn 0;
}

static int si_common_set_cwockgating_state(void *handwe,
					    enum amd_cwockgating_state state)
{
	wetuwn 0;
}

static int si_common_set_powewgating_state(void *handwe,
					    enum amd_powewgating_state state)
{
	wetuwn 0;
}

static const stwuct amd_ip_funcs si_common_ip_funcs = {
	.name = "si_common",
	.eawwy_init = si_common_eawwy_init,
	.wate_init = NUWW,
	.sw_init = si_common_sw_init,
	.sw_fini = si_common_sw_fini,
	.hw_init = si_common_hw_init,
	.hw_fini = si_common_hw_fini,
	.suspend = si_common_suspend,
	.wesume = si_common_wesume,
	.is_idwe = si_common_is_idwe,
	.wait_fow_idwe = si_common_wait_fow_idwe,
	.soft_weset = si_common_soft_weset,
	.set_cwockgating_state = si_common_set_cwockgating_state,
	.set_powewgating_state = si_common_set_powewgating_state,
};

static const stwuct amdgpu_ip_bwock_vewsion si_common_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_COMMON,
	.majow = 1,
	.minow = 0,
	.wev = 0,
	.funcs = &si_common_ip_funcs,
};

int si_set_ip_bwocks(stwuct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_VEWDE:
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
		amdgpu_device_ip_bwock_add(adev, &si_common_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gmc_v6_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &si_ih_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gfx_v6_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &si_dma_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &si_smu_ip_bwock);
		if (adev->enabwe_viwtuaw_dispway)
			amdgpu_device_ip_bwock_add(adev, &amdgpu_vkms_ip_bwock);
#if defined(CONFIG_DWM_AMD_DC) && defined(CONFIG_DWM_AMD_DC_SI)
		ewse if (amdgpu_device_has_dc_suppowt(adev))
			amdgpu_device_ip_bwock_add(adev, &dm_ip_bwock);
#endif
		ewse
			amdgpu_device_ip_bwock_add(adev, &dce_v6_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &uvd_v3_1_ip_bwock);
		/* amdgpu_device_ip_bwock_add(adev, &vce_v1_0_ip_bwock); */
		bweak;
	case CHIP_OWAND:
		amdgpu_device_ip_bwock_add(adev, &si_common_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gmc_v6_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &si_ih_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gfx_v6_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &si_dma_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &si_smu_ip_bwock);
		if (adev->enabwe_viwtuaw_dispway)
			amdgpu_device_ip_bwock_add(adev, &amdgpu_vkms_ip_bwock);
#if defined(CONFIG_DWM_AMD_DC) && defined(CONFIG_DWM_AMD_DC_SI)
		ewse if (amdgpu_device_has_dc_suppowt(adev))
			amdgpu_device_ip_bwock_add(adev, &dm_ip_bwock);
#endif
		ewse
			amdgpu_device_ip_bwock_add(adev, &dce_v6_4_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &uvd_v3_1_ip_bwock);
		/* amdgpu_device_ip_bwock_add(adev, &vce_v1_0_ip_bwock); */
		bweak;
	case CHIP_HAINAN:
		amdgpu_device_ip_bwock_add(adev, &si_common_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gmc_v6_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &si_ih_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &gfx_v6_0_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &si_dma_ip_bwock);
		amdgpu_device_ip_bwock_add(adev, &si_smu_ip_bwock);
		if (adev->enabwe_viwtuaw_dispway)
			amdgpu_device_ip_bwock_add(adev, &amdgpu_vkms_ip_bwock);
		bweak;
	defauwt:
		BUG();
	}
	wetuwn 0;
}

