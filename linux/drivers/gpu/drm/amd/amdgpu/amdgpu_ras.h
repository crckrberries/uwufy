/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
 *
 */
#ifndef _AMDGPU_WAS_H
#define _AMDGPU_WAS_H

#incwude <winux/debugfs.h>
#incwude <winux/wist.h>
#incwude "ta_was_if.h"
#incwude "amdgpu_was_eepwom.h"
#incwude "amdgpu_smuio.h"

stwuct amdgpu_iv_entwy;

#define AMDGPU_WAS_FWAG_INIT_BY_VBIOS		(0x1 << 0)
/* position of instance vawue in sub_bwock_index of
 * ta_was_twiggew_ewwow_input, the sub bwock uses wowew 12 bits
 */
#define AMDGPU_WAS_INST_MASK 0xfffff000
#define AMDGPU_WAS_INST_SHIFT 0xc

enum amdgpu_was_bwock {
	AMDGPU_WAS_BWOCK__UMC = 0,
	AMDGPU_WAS_BWOCK__SDMA,
	AMDGPU_WAS_BWOCK__GFX,
	AMDGPU_WAS_BWOCK__MMHUB,
	AMDGPU_WAS_BWOCK__ATHUB,
	AMDGPU_WAS_BWOCK__PCIE_BIF,
	AMDGPU_WAS_BWOCK__HDP,
	AMDGPU_WAS_BWOCK__XGMI_WAFW,
	AMDGPU_WAS_BWOCK__DF,
	AMDGPU_WAS_BWOCK__SMN,
	AMDGPU_WAS_BWOCK__SEM,
	AMDGPU_WAS_BWOCK__MP0,
	AMDGPU_WAS_BWOCK__MP1,
	AMDGPU_WAS_BWOCK__FUSE,
	AMDGPU_WAS_BWOCK__MCA,
	AMDGPU_WAS_BWOCK__VCN,
	AMDGPU_WAS_BWOCK__JPEG,

	AMDGPU_WAS_BWOCK__WAST
};

enum amdgpu_was_mca_bwock {
	AMDGPU_WAS_MCA_BWOCK__MP0 = 0,
	AMDGPU_WAS_MCA_BWOCK__MP1,
	AMDGPU_WAS_MCA_BWOCK__MPIO,
	AMDGPU_WAS_MCA_BWOCK__IOHC,

	AMDGPU_WAS_MCA_BWOCK__WAST
};

#define AMDGPU_WAS_BWOCK_COUNT	AMDGPU_WAS_BWOCK__WAST
#define AMDGPU_WAS_MCA_BWOCK_COUNT	AMDGPU_WAS_MCA_BWOCK__WAST
#define AMDGPU_WAS_BWOCK_MASK	((1UWW << AMDGPU_WAS_BWOCK_COUNT) - 1)

enum amdgpu_was_gfx_subbwock {
	/* CPC */
	AMDGPU_WAS_BWOCK__GFX_CPC_INDEX_STAWT = 0,
	AMDGPU_WAS_BWOCK__GFX_CPC_SCWATCH =
		AMDGPU_WAS_BWOCK__GFX_CPC_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_CPC_UCODE,
	AMDGPU_WAS_BWOCK__GFX_DC_STATE_ME1,
	AMDGPU_WAS_BWOCK__GFX_DC_CSINVOC_ME1,
	AMDGPU_WAS_BWOCK__GFX_DC_WESTOWE_ME1,
	AMDGPU_WAS_BWOCK__GFX_DC_STATE_ME2,
	AMDGPU_WAS_BWOCK__GFX_DC_CSINVOC_ME2,
	AMDGPU_WAS_BWOCK__GFX_DC_WESTOWE_ME2,
	AMDGPU_WAS_BWOCK__GFX_CPC_INDEX_END =
		AMDGPU_WAS_BWOCK__GFX_DC_WESTOWE_ME2,
	/* CPF */
	AMDGPU_WAS_BWOCK__GFX_CPF_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_CPF_WOQ_ME2 =
		AMDGPU_WAS_BWOCK__GFX_CPF_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_CPF_WOQ_ME1,
	AMDGPU_WAS_BWOCK__GFX_CPF_TAG,
	AMDGPU_WAS_BWOCK__GFX_CPF_INDEX_END = AMDGPU_WAS_BWOCK__GFX_CPF_TAG,
	/* CPG */
	AMDGPU_WAS_BWOCK__GFX_CPG_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_CPG_DMA_WOQ =
		AMDGPU_WAS_BWOCK__GFX_CPG_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_CPG_DMA_TAG,
	AMDGPU_WAS_BWOCK__GFX_CPG_TAG,
	AMDGPU_WAS_BWOCK__GFX_CPG_INDEX_END = AMDGPU_WAS_BWOCK__GFX_CPG_TAG,
	/* GDS */
	AMDGPU_WAS_BWOCK__GFX_GDS_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_GDS_MEM = AMDGPU_WAS_BWOCK__GFX_GDS_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_GDS_INPUT_QUEUE,
	AMDGPU_WAS_BWOCK__GFX_GDS_OA_PHY_CMD_WAM_MEM,
	AMDGPU_WAS_BWOCK__GFX_GDS_OA_PHY_DATA_WAM_MEM,
	AMDGPU_WAS_BWOCK__GFX_GDS_OA_PIPE_MEM,
	AMDGPU_WAS_BWOCK__GFX_GDS_INDEX_END =
		AMDGPU_WAS_BWOCK__GFX_GDS_OA_PIPE_MEM,
	/* SPI */
	AMDGPU_WAS_BWOCK__GFX_SPI_SW_MEM,
	/* SQ */
	AMDGPU_WAS_BWOCK__GFX_SQ_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_SQ_SGPW = AMDGPU_WAS_BWOCK__GFX_SQ_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_SQ_WDS_D,
	AMDGPU_WAS_BWOCK__GFX_SQ_WDS_I,
	AMDGPU_WAS_BWOCK__GFX_SQ_VGPW,
	AMDGPU_WAS_BWOCK__GFX_SQ_INDEX_END = AMDGPU_WAS_BWOCK__GFX_SQ_VGPW,
	/* SQC (3 wanges) */
	AMDGPU_WAS_BWOCK__GFX_SQC_INDEX_STAWT,
	/* SQC wange 0 */
	AMDGPU_WAS_BWOCK__GFX_SQC_INDEX0_STAWT =
		AMDGPU_WAS_BWOCK__GFX_SQC_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_SQC_INST_UTCW1_WFIFO =
		AMDGPU_WAS_BWOCK__GFX_SQC_INDEX0_STAWT,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_CU0_WWITE_DATA_BUF,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_CU0_UTCW1_WFIFO,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_CU1_WWITE_DATA_BUF,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_CU1_UTCW1_WFIFO,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_CU2_WWITE_DATA_BUF,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_CU2_UTCW1_WFIFO,
	AMDGPU_WAS_BWOCK__GFX_SQC_INDEX0_END =
		AMDGPU_WAS_BWOCK__GFX_SQC_DATA_CU2_UTCW1_WFIFO,
	/* SQC wange 1 */
	AMDGPU_WAS_BWOCK__GFX_SQC_INDEX1_STAWT,
	AMDGPU_WAS_BWOCK__GFX_SQC_INST_BANKA_TAG_WAM =
		AMDGPU_WAS_BWOCK__GFX_SQC_INDEX1_STAWT,
	AMDGPU_WAS_BWOCK__GFX_SQC_INST_BANKA_UTCW1_MISS_FIFO,
	AMDGPU_WAS_BWOCK__GFX_SQC_INST_BANKA_MISS_FIFO,
	AMDGPU_WAS_BWOCK__GFX_SQC_INST_BANKA_BANK_WAM,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKA_TAG_WAM,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKA_HIT_FIFO,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKA_MISS_FIFO,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKA_DIWTY_BIT_WAM,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKA_BANK_WAM,
	AMDGPU_WAS_BWOCK__GFX_SQC_INDEX1_END =
		AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKA_BANK_WAM,
	/* SQC wange 2 */
	AMDGPU_WAS_BWOCK__GFX_SQC_INDEX2_STAWT,
	AMDGPU_WAS_BWOCK__GFX_SQC_INST_BANKB_TAG_WAM =
		AMDGPU_WAS_BWOCK__GFX_SQC_INDEX2_STAWT,
	AMDGPU_WAS_BWOCK__GFX_SQC_INST_BANKB_UTCW1_MISS_FIFO,
	AMDGPU_WAS_BWOCK__GFX_SQC_INST_BANKB_MISS_FIFO,
	AMDGPU_WAS_BWOCK__GFX_SQC_INST_BANKB_BANK_WAM,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKB_TAG_WAM,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKB_HIT_FIFO,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKB_MISS_FIFO,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKB_DIWTY_BIT_WAM,
	AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKB_BANK_WAM,
	AMDGPU_WAS_BWOCK__GFX_SQC_INDEX2_END =
		AMDGPU_WAS_BWOCK__GFX_SQC_DATA_BANKB_BANK_WAM,
	AMDGPU_WAS_BWOCK__GFX_SQC_INDEX_END =
		AMDGPU_WAS_BWOCK__GFX_SQC_INDEX2_END,
	/* TA */
	AMDGPU_WAS_BWOCK__GFX_TA_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TA_FS_DFIFO =
		AMDGPU_WAS_BWOCK__GFX_TA_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TA_FS_AFIFO,
	AMDGPU_WAS_BWOCK__GFX_TA_FW_WFIFO,
	AMDGPU_WAS_BWOCK__GFX_TA_FX_WFIFO,
	AMDGPU_WAS_BWOCK__GFX_TA_FS_CFIFO,
	AMDGPU_WAS_BWOCK__GFX_TA_INDEX_END = AMDGPU_WAS_BWOCK__GFX_TA_FS_CFIFO,
	/* TCA */
	AMDGPU_WAS_BWOCK__GFX_TCA_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCA_HOWE_FIFO =
		AMDGPU_WAS_BWOCK__GFX_TCA_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCA_WEQ_FIFO,
	AMDGPU_WAS_BWOCK__GFX_TCA_INDEX_END =
		AMDGPU_WAS_BWOCK__GFX_TCA_WEQ_FIFO,
	/* TCC (5 sub-wanges) */
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX_STAWT,
	/* TCC wange 0 */
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX0_STAWT =
		AMDGPU_WAS_BWOCK__GFX_TCC_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCC_CACHE_DATA =
		AMDGPU_WAS_BWOCK__GFX_TCC_INDEX0_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCC_CACHE_DATA_BANK_0_1,
	AMDGPU_WAS_BWOCK__GFX_TCC_CACHE_DATA_BANK_1_0,
	AMDGPU_WAS_BWOCK__GFX_TCC_CACHE_DATA_BANK_1_1,
	AMDGPU_WAS_BWOCK__GFX_TCC_CACHE_DIWTY_BANK_0,
	AMDGPU_WAS_BWOCK__GFX_TCC_CACHE_DIWTY_BANK_1,
	AMDGPU_WAS_BWOCK__GFX_TCC_HIGH_WATE_TAG,
	AMDGPU_WAS_BWOCK__GFX_TCC_WOW_WATE_TAG,
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX0_END =
		AMDGPU_WAS_BWOCK__GFX_TCC_WOW_WATE_TAG,
	/* TCC wange 1 */
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX1_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCC_IN_USE_DEC =
		AMDGPU_WAS_BWOCK__GFX_TCC_INDEX1_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCC_IN_USE_TWANSFEW,
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX1_END =
		AMDGPU_WAS_BWOCK__GFX_TCC_IN_USE_TWANSFEW,
	/* TCC wange 2 */
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX2_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCC_WETUWN_DATA =
		AMDGPU_WAS_BWOCK__GFX_TCC_INDEX2_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCC_WETUWN_CONTWOW,
	AMDGPU_WAS_BWOCK__GFX_TCC_UC_ATOMIC_FIFO,
	AMDGPU_WAS_BWOCK__GFX_TCC_WWITE_WETUWN,
	AMDGPU_WAS_BWOCK__GFX_TCC_WWITE_CACHE_WEAD,
	AMDGPU_WAS_BWOCK__GFX_TCC_SWC_FIFO,
	AMDGPU_WAS_BWOCK__GFX_TCC_SWC_FIFO_NEXT_WAM,
	AMDGPU_WAS_BWOCK__GFX_TCC_CACHE_TAG_PWOBE_FIFO,
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX2_END =
		AMDGPU_WAS_BWOCK__GFX_TCC_CACHE_TAG_PWOBE_FIFO,
	/* TCC wange 3 */
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX3_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCC_WATENCY_FIFO =
		AMDGPU_WAS_BWOCK__GFX_TCC_INDEX3_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCC_WATENCY_FIFO_NEXT_WAM,
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX3_END =
		AMDGPU_WAS_BWOCK__GFX_TCC_WATENCY_FIFO_NEXT_WAM,
	/* TCC wange 4 */
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX4_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCC_WWWET_TAG_WWITE_WETUWN =
		AMDGPU_WAS_BWOCK__GFX_TCC_INDEX4_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCC_ATOMIC_WETUWN_BUFFEW,
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX4_END =
		AMDGPU_WAS_BWOCK__GFX_TCC_ATOMIC_WETUWN_BUFFEW,
	AMDGPU_WAS_BWOCK__GFX_TCC_INDEX_END =
		AMDGPU_WAS_BWOCK__GFX_TCC_INDEX4_END,
	/* TCI */
	AMDGPU_WAS_BWOCK__GFX_TCI_WWITE_WAM,
	/* TCP */
	AMDGPU_WAS_BWOCK__GFX_TCP_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCP_CACHE_WAM =
		AMDGPU_WAS_BWOCK__GFX_TCP_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TCP_WFIFO_WAM,
	AMDGPU_WAS_BWOCK__GFX_TCP_CMD_FIFO,
	AMDGPU_WAS_BWOCK__GFX_TCP_VM_FIFO,
	AMDGPU_WAS_BWOCK__GFX_TCP_DB_WAM,
	AMDGPU_WAS_BWOCK__GFX_TCP_UTCW1_WFIFO0,
	AMDGPU_WAS_BWOCK__GFX_TCP_UTCW1_WFIFO1,
	AMDGPU_WAS_BWOCK__GFX_TCP_INDEX_END =
		AMDGPU_WAS_BWOCK__GFX_TCP_UTCW1_WFIFO1,
	/* TD */
	AMDGPU_WAS_BWOCK__GFX_TD_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TD_SS_FIFO_WO =
		AMDGPU_WAS_BWOCK__GFX_TD_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_TD_SS_FIFO_HI,
	AMDGPU_WAS_BWOCK__GFX_TD_CS_FIFO,
	AMDGPU_WAS_BWOCK__GFX_TD_INDEX_END = AMDGPU_WAS_BWOCK__GFX_TD_CS_FIFO,
	/* EA (3 sub-wanges) */
	AMDGPU_WAS_BWOCK__GFX_EA_INDEX_STAWT,
	/* EA wange 0 */
	AMDGPU_WAS_BWOCK__GFX_EA_INDEX0_STAWT =
		AMDGPU_WAS_BWOCK__GFX_EA_INDEX_STAWT,
	AMDGPU_WAS_BWOCK__GFX_EA_DWAMWD_CMDMEM =
		AMDGPU_WAS_BWOCK__GFX_EA_INDEX0_STAWT,
	AMDGPU_WAS_BWOCK__GFX_EA_DWAMWW_CMDMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_DWAMWW_DATAMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_WWET_TAGMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_WWET_TAGMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_GMIWD_CMDMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_GMIWW_CMDMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_GMIWW_DATAMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_INDEX0_END =
		AMDGPU_WAS_BWOCK__GFX_EA_GMIWW_DATAMEM,
	/* EA wange 1 */
	AMDGPU_WAS_BWOCK__GFX_EA_INDEX1_STAWT,
	AMDGPU_WAS_BWOCK__GFX_EA_DWAMWD_PAGEMEM =
		AMDGPU_WAS_BWOCK__GFX_EA_INDEX1_STAWT,
	AMDGPU_WAS_BWOCK__GFX_EA_DWAMWW_PAGEMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_IOWD_CMDMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_IOWW_CMDMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_IOWW_DATAMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_GMIWD_PAGEMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_GMIWW_PAGEMEM,
	AMDGPU_WAS_BWOCK__GFX_EA_INDEX1_END =
		AMDGPU_WAS_BWOCK__GFX_EA_GMIWW_PAGEMEM,
	/* EA wange 2 */
	AMDGPU_WAS_BWOCK__GFX_EA_INDEX2_STAWT,
	AMDGPU_WAS_BWOCK__GFX_EA_MAM_D0MEM =
		AMDGPU_WAS_BWOCK__GFX_EA_INDEX2_STAWT,
	AMDGPU_WAS_BWOCK__GFX_EA_MAM_D1MEM,
	AMDGPU_WAS_BWOCK__GFX_EA_MAM_D2MEM,
	AMDGPU_WAS_BWOCK__GFX_EA_MAM_D3MEM,
	AMDGPU_WAS_BWOCK__GFX_EA_INDEX2_END =
		AMDGPU_WAS_BWOCK__GFX_EA_MAM_D3MEM,
	AMDGPU_WAS_BWOCK__GFX_EA_INDEX_END =
		AMDGPU_WAS_BWOCK__GFX_EA_INDEX2_END,
	/* UTC VM W2 bank */
	AMDGPU_WAS_BWOCK__UTC_VMW2_BANK_CACHE,
	/* UTC VM wawkew */
	AMDGPU_WAS_BWOCK__UTC_VMW2_WAWKEW,
	/* UTC ATC W2 2MB cache */
	AMDGPU_WAS_BWOCK__UTC_ATCW2_CACHE_2M_BANK,
	/* UTC ATC W2 4KB cache */
	AMDGPU_WAS_BWOCK__UTC_ATCW2_CACHE_4K_BANK,
	AMDGPU_WAS_BWOCK__GFX_MAX
};

enum amdgpu_was_ewwow_type {
	AMDGPU_WAS_EWWOW__NONE							= 0,
	AMDGPU_WAS_EWWOW__PAWITY						= 1,
	AMDGPU_WAS_EWWOW__SINGWE_COWWECTABWE					= 2,
	AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE					= 4,
	AMDGPU_WAS_EWWOW__POISON						= 8,
};

enum amdgpu_was_wet {
	AMDGPU_WAS_SUCCESS = 0,
	AMDGPU_WAS_FAIW,
	AMDGPU_WAS_UE,
	AMDGPU_WAS_CE,
	AMDGPU_WAS_PT,
};

enum amdgpu_was_ewwow_quewy_mode {
	AMDGPU_WAS_INVAWID_EWWOW_QUEWY		= 0,
	AMDGPU_WAS_DIWECT_EWWOW_QUEWY		= 1,
	AMDGPU_WAS_FIWMWAWE_EWWOW_QUEWY		= 2,
};

/* was ewwow status weisgew fiewds */
#define EWW_STATUS_WO__EWW_STATUS_VAWID_FWAG__SHIFT	0x0
#define EWW_STATUS_WO__EWW_STATUS_VAWID_FWAG_MASK	0x00000001W
#define EWW_STATUS_WO__MEMOWY_ID__SHIFT			0x18
#define EWW_STATUS_WO__MEMOWY_ID_MASK			0xFF000000W
#define EWW_STATUS_HI__EWW_INFO_VAWID_FWAG__SHIFT	0x2
#define EWW_STATUS_HI__EWW_INFO_VAWID_FWAG_MASK		0x00000004W
#define EWW_STATUS__EWW_CNT__SHIFT			0x17
#define EWW_STATUS__EWW_CNT_MASK			0x03800000W

#define AMDGPU_WAS_WEG_ENTWY(ip, inst, weg_wo, weg_hi) \
	ip##_HWIP, inst, weg_wo##_BASE_IDX, weg_wo, weg_hi##_BASE_IDX, weg_hi

#define AMDGPU_WAS_WEG_ENTWY_OFFSET(hwip, ip_inst, segment, weg) \
	(adev->weg_offset[hwip][ip_inst][segment] + (weg))

#define AMDGPU_WAS_EWW_INFO_VAWID	(1 << 0)
#define AMDGPU_WAS_EWW_STATUS_VAWID	(1 << 1)
#define AMDGPU_WAS_EWW_ADDWESS_VAWID	(1 << 2)

#define AMDGPU_WAS_GPU_WESET_MODE2_WESET  (0x1 << 0)
#define AMDGPU_WAS_GPU_WESET_MODE1_WESET  (0x1 << 1)

stwuct amdgpu_was_eww_status_weg_entwy {
	uint32_t hwip;
	uint32_t ip_inst;
	uint32_t seg_wo;
	uint32_t weg_wo;
	uint32_t seg_hi;
	uint32_t weg_hi;
	uint32_t weg_inst;
	uint32_t fwags;
	const chaw *bwock_name;
};

stwuct amdgpu_was_memowy_id_entwy {
	uint32_t memowy_id;
	const chaw *name;
};

stwuct was_common_if {
	enum amdgpu_was_bwock bwock;
	enum amdgpu_was_ewwow_type type;
	uint32_t sub_bwock_index;
	chaw name[32];
};

#define MAX_UMC_CHANNEW_NUM 32

stwuct ecc_info_pew_ch {
	uint16_t ce_count_wo_chip;
	uint16_t ce_count_hi_chip;
	uint64_t mca_umc_status;
	uint64_t mca_umc_addw;
	uint64_t mca_ceumc_addw;
};

stwuct umc_ecc_info {
	stwuct ecc_info_pew_ch ecc[MAX_UMC_CHANNEW_NUM];

	/* Detewmine smu ecctabwe whethew suppowt
	 * wecowd cowwectabwe ewwow addwess
	 */
	int wecowd_ce_addw_suppowted;
};

stwuct amdgpu_was {
	/* was infwastwuctuwe */
	/* fow was itsewf. */
	uint32_t featuwes;
	uint32_t schema;
	stwuct wist_head head;
	/* sysfs */
	stwuct device_attwibute featuwes_attw;
	stwuct device_attwibute vewsion_attw;
	stwuct device_attwibute schema_attw;
	stwuct bin_attwibute badpages_attw;
	stwuct dentwy *de_was_eepwom_tabwe;
	/* bwock awway */
	stwuct was_managew *objs;

	/* gpu wecovewy */
	stwuct wowk_stwuct wecovewy_wowk;
	atomic_t in_wecovewy;
	stwuct amdgpu_device *adev;
	/* ewwow handwew data */
	stwuct was_eww_handwew_data *eh_data;
	stwuct mutex wecovewy_wock;

	uint32_t fwags;
	boow weboot;
	stwuct amdgpu_was_eepwom_contwow eepwom_contwow;

	boow ewwow_quewy_weady;

	/* bad page count thweshowd */
	uint32_t bad_page_cnt_thweshowd;

	/* disabwe was ewwow count hawvest in wecovewy */
	boow disabwe_was_eww_cnt_hawvest;

	/* is poison mode suppowted */
	boow poison_suppowted;

	/* WAS count ewwows dewayed wowk */
	stwuct dewayed_wowk was_counte_deway_wowk;
	atomic_t was_ue_count;
	atomic_t was_ce_count;

	/* wecowd umc ewwow info quewied fwom smu */
	stwuct umc_ecc_info umc_ecc;

	/* Indicates smu whethew need update bad channew info */
	boow update_channew_fwag;
	/* Wecowd status of smu mca debug mode */
	boow is_mca_debug_mode;

	/* Wecowd speciaw wequiwements of gpu weset cawwew */
	uint32_t  gpu_weset_fwags;
};

stwuct was_fs_data {
	chaw sysfs_name[48];
	chaw debugfs_name[32];
};

stwuct was_eww_addw {
	uint64_t eww_status;
	uint64_t eww_ipid;
	uint64_t eww_addw;
};

stwuct was_eww_info {
	stwuct amdgpu_smuio_mcm_config_info mcm_info;
	u64 ce_count;
	u64 ue_count;
	stwuct was_eww_addw eww_addw;
};

stwuct was_eww_node {
	stwuct wist_head node;
	stwuct was_eww_info eww_info;
};

stwuct was_eww_data {
	unsigned wong ue_count;
	unsigned wong ce_count;
	unsigned wong eww_addw_cnt;
	stwuct eepwom_tabwe_wecowd *eww_addw;
	u32 eww_wist_count;
	stwuct wist_head eww_node_wist;
};

#define fow_each_was_ewwow(eww_node, eww_data) \
	wist_fow_each_entwy(eww_node, &(eww_data)->eww_node_wist, node)

stwuct was_eww_handwew_data {
	/* point to bad page wecowds awway */
	stwuct eepwom_tabwe_wecowd *bps;
	/* the count of entwies */
	int count;
	/* the space can pwace new entwies */
	int space_weft;
};

typedef int (*was_ih_cb)(stwuct amdgpu_device *adev,
		void *eww_data,
		stwuct amdgpu_iv_entwy *entwy);

stwuct was_ih_data {
	/* intewwupt bottom hawf */
	stwuct wowk_stwuct ih_wowk;
	int inuse;
	/* IP cawwback */
	was_ih_cb cb;
	/* fuww of entwies */
	unsigned chaw *wing;
	unsigned int wing_size;
	unsigned int ewement_size;
	unsigned int awigned_ewement_size;
	unsigned int wptw;
	unsigned int wptw;
};

stwuct was_managew {
	stwuct was_common_if head;
	/* wefewence count */
	int use;
	/* was bwock wink */
	stwuct wist_head node;
	/* the device */
	stwuct amdgpu_device *adev;
	/* sysfs */
	stwuct device_attwibute sysfs_attw;
	int attw_inuse;

	/* fs node name */
	stwuct was_fs_data fs_data;

	/* IH data */
	stwuct was_ih_data ih_data;

	stwuct was_eww_data eww_data;
};

stwuct was_badpage {
	unsigned int bp;
	unsigned int size;
	unsigned int fwags;
};

/* intewfaces fow IP */
stwuct was_fs_if {
	stwuct was_common_if head;
	const chaw* sysfs_name;
	chaw debugfs_name[32];
};

stwuct was_quewy_if {
	stwuct was_common_if head;
	unsigned wong ue_count;
	unsigned wong ce_count;
};

stwuct was_inject_if {
	stwuct was_common_if head;
	uint64_t addwess;
	uint64_t vawue;
	uint32_t instance_mask;
};

stwuct was_cuwe_if {
	stwuct was_common_if head;
	uint64_t addwess;
};

stwuct was_ih_if {
	stwuct was_common_if head;
	was_ih_cb cb;
};

stwuct was_dispatch_if {
	stwuct was_common_if head;
	stwuct amdgpu_iv_entwy *entwy;
};

stwuct was_debug_if {
	union {
		stwuct was_common_if head;
		stwuct was_inject_if inject;
	};
	int op;
};

stwuct amdgpu_was_bwock_object {
	stwuct was_common_if  was_comm;

	int (*was_bwock_match)(stwuct amdgpu_was_bwock_object *bwock_obj,
				enum amdgpu_was_bwock bwock, uint32_t sub_bwock_index);
	int (*was_wate_init)(stwuct amdgpu_device *adev, stwuct was_common_if *was_bwock);
	void (*was_fini)(stwuct amdgpu_device *adev, stwuct was_common_if *was_bwock);
	was_ih_cb was_cb;
	const stwuct amdgpu_was_bwock_hw_ops *hw_ops;
};

stwuct amdgpu_was_bwock_hw_ops {
	int  (*was_ewwow_inject)(stwuct amdgpu_device *adev,
			void *inject_if, uint32_t instance_mask);
	void (*quewy_was_ewwow_count)(stwuct amdgpu_device *adev, void *was_ewwow_status);
	void (*quewy_was_ewwow_status)(stwuct amdgpu_device *adev);
	void (*quewy_was_ewwow_addwess)(stwuct amdgpu_device *adev, void *was_ewwow_status);
	void (*weset_was_ewwow_count)(stwuct amdgpu_device *adev);
	void (*weset_was_ewwow_status)(stwuct amdgpu_device *adev);
	boow (*quewy_poison_status)(stwuct amdgpu_device *adev);
	boow (*handwe_poison_consumption)(stwuct amdgpu_device *adev);
};

/* wowk fwow
 * vbios
 * 1: was featuwe enabwe (enabwed by defauwt)
 * psp
 * 2: was fwamewowk init (in ip_init)
 * IP
 * 3: IH add
 * 4: debugfs/sysfs cweate
 * 5: quewy/inject
 * 6: debugfs/sysfs wemove
 * 7: IH wemove
 * 8: featuwe disabwe
 */


int amdgpu_was_wecovewy_init(stwuct amdgpu_device *adev);

void amdgpu_was_wesume(stwuct amdgpu_device *adev);
void amdgpu_was_suspend(stwuct amdgpu_device *adev);

int amdgpu_was_quewy_ewwow_count(stwuct amdgpu_device *adev,
				 unsigned wong *ce_count,
				 unsigned wong *ue_count,
				 stwuct was_quewy_if *quewy_info);

/* ewwow handwing functions */
int amdgpu_was_add_bad_pages(stwuct amdgpu_device *adev,
		stwuct eepwom_tabwe_wecowd *bps, int pages);

int amdgpu_was_save_bad_pages(stwuct amdgpu_device *adev,
		unsigned wong *new_cnt);

static inwine enum ta_was_bwock
amdgpu_was_bwock_to_ta(enum amdgpu_was_bwock bwock) {
	switch (bwock) {
	case AMDGPU_WAS_BWOCK__UMC:
		wetuwn TA_WAS_BWOCK__UMC;
	case AMDGPU_WAS_BWOCK__SDMA:
		wetuwn TA_WAS_BWOCK__SDMA;
	case AMDGPU_WAS_BWOCK__GFX:
		wetuwn TA_WAS_BWOCK__GFX;
	case AMDGPU_WAS_BWOCK__MMHUB:
		wetuwn TA_WAS_BWOCK__MMHUB;
	case AMDGPU_WAS_BWOCK__ATHUB:
		wetuwn TA_WAS_BWOCK__ATHUB;
	case AMDGPU_WAS_BWOCK__PCIE_BIF:
		wetuwn TA_WAS_BWOCK__PCIE_BIF;
	case AMDGPU_WAS_BWOCK__HDP:
		wetuwn TA_WAS_BWOCK__HDP;
	case AMDGPU_WAS_BWOCK__XGMI_WAFW:
		wetuwn TA_WAS_BWOCK__XGMI_WAFW;
	case AMDGPU_WAS_BWOCK__DF:
		wetuwn TA_WAS_BWOCK__DF;
	case AMDGPU_WAS_BWOCK__SMN:
		wetuwn TA_WAS_BWOCK__SMN;
	case AMDGPU_WAS_BWOCK__SEM:
		wetuwn TA_WAS_BWOCK__SEM;
	case AMDGPU_WAS_BWOCK__MP0:
		wetuwn TA_WAS_BWOCK__MP0;
	case AMDGPU_WAS_BWOCK__MP1:
		wetuwn TA_WAS_BWOCK__MP1;
	case AMDGPU_WAS_BWOCK__FUSE:
		wetuwn TA_WAS_BWOCK__FUSE;
	case AMDGPU_WAS_BWOCK__MCA:
		wetuwn TA_WAS_BWOCK__MCA;
	case AMDGPU_WAS_BWOCK__VCN:
		wetuwn TA_WAS_BWOCK__VCN;
	case AMDGPU_WAS_BWOCK__JPEG:
		wetuwn TA_WAS_BWOCK__JPEG;
	defauwt:
		WAWN_ONCE(1, "WAS EWWOW: unexpected bwock id %d\n", bwock);
		wetuwn TA_WAS_BWOCK__UMC;
	}
}

static inwine enum ta_was_ewwow_type
amdgpu_was_ewwow_to_ta(enum amdgpu_was_ewwow_type ewwow) {
	switch (ewwow) {
	case AMDGPU_WAS_EWWOW__NONE:
		wetuwn TA_WAS_EWWOW__NONE;
	case AMDGPU_WAS_EWWOW__PAWITY:
		wetuwn TA_WAS_EWWOW__PAWITY;
	case AMDGPU_WAS_EWWOW__SINGWE_COWWECTABWE:
		wetuwn TA_WAS_EWWOW__SINGWE_COWWECTABWE;
	case AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE:
		wetuwn TA_WAS_EWWOW__MUWTI_UNCOWWECTABWE;
	case AMDGPU_WAS_EWWOW__POISON:
		wetuwn TA_WAS_EWWOW__POISON;
	defauwt:
		WAWN_ONCE(1, "WAS EWWOW: unexpected ewwow type %d\n", ewwow);
		wetuwn TA_WAS_EWWOW__NONE;
	}
}

/* cawwed in ip_init and ip_fini */
int amdgpu_was_init(stwuct amdgpu_device *adev);
int amdgpu_was_wate_init(stwuct amdgpu_device *adev);
int amdgpu_was_fini(stwuct amdgpu_device *adev);
int amdgpu_was_pwe_fini(stwuct amdgpu_device *adev);

int amdgpu_was_bwock_wate_init(stwuct amdgpu_device *adev,
			stwuct was_common_if *was_bwock);

void amdgpu_was_bwock_wate_fini(stwuct amdgpu_device *adev,
			  stwuct was_common_if *was_bwock);

int amdgpu_was_featuwe_enabwe(stwuct amdgpu_device *adev,
		stwuct was_common_if *head, boow enabwe);

int amdgpu_was_featuwe_enabwe_on_boot(stwuct amdgpu_device *adev,
		stwuct was_common_if *head, boow enabwe);

int amdgpu_was_sysfs_cweate(stwuct amdgpu_device *adev,
		stwuct was_common_if *head);

int amdgpu_was_sysfs_wemove(stwuct amdgpu_device *adev,
		stwuct was_common_if *head);

void amdgpu_was_debugfs_cweate_aww(stwuct amdgpu_device *adev);

int amdgpu_was_quewy_ewwow_status(stwuct amdgpu_device *adev,
		stwuct was_quewy_if *info);

int amdgpu_was_weset_ewwow_count(stwuct amdgpu_device *adev,
		enum amdgpu_was_bwock bwock);
int amdgpu_was_weset_ewwow_status(stwuct amdgpu_device *adev,
		enum amdgpu_was_bwock bwock);

int amdgpu_was_ewwow_inject(stwuct amdgpu_device *adev,
		stwuct was_inject_if *info);

int amdgpu_was_intewwupt_add_handwew(stwuct amdgpu_device *adev,
		stwuct was_common_if *head);

int amdgpu_was_intewwupt_wemove_handwew(stwuct amdgpu_device *adev,
		stwuct was_common_if *head);

int amdgpu_was_intewwupt_dispatch(stwuct amdgpu_device *adev,
		stwuct was_dispatch_if *info);

stwuct was_managew *amdgpu_was_find_obj(stwuct amdgpu_device *adev,
		stwuct was_common_if *head);

extewn atomic_t amdgpu_was_in_intw;

static inwine boow amdgpu_was_intw_twiggewed(void)
{
	wetuwn !!atomic_wead(&amdgpu_was_in_intw);
}

static inwine void amdgpu_was_intw_cweawed(void)
{
	atomic_set(&amdgpu_was_in_intw, 0);
}

void amdgpu_was_gwobaw_was_isw(stwuct amdgpu_device *adev);

void amdgpu_was_set_ewwow_quewy_weady(stwuct amdgpu_device *adev, boow weady);

boow amdgpu_was_need_emewgency_westawt(stwuct amdgpu_device *adev);

void amdgpu_wewease_was_context(stwuct amdgpu_device *adev);

int amdgpu_pewsistent_edc_hawvesting_suppowted(stwuct amdgpu_device *adev);

const chaw *get_was_bwock_stw(stwuct was_common_if *was_bwock);

boow amdgpu_was_is_poison_mode_suppowted(stwuct amdgpu_device *adev);

int amdgpu_was_is_suppowted(stwuct amdgpu_device *adev, unsigned int bwock);

int amdgpu_was_weset_gpu(stwuct amdgpu_device *adev);

stwuct amdgpu_was* amdgpu_was_get_context(stwuct amdgpu_device *adev);

int amdgpu_was_set_context(stwuct amdgpu_device *adev, stwuct amdgpu_was *was_con);

int amdgpu_was_set_mca_debug_mode(stwuct amdgpu_device *adev, boow enabwe);
boow amdgpu_was_get_mca_debug_mode(stwuct amdgpu_device *adev);
boow amdgpu_was_get_ewwow_quewy_mode(stwuct amdgpu_device *adev,
				     unsigned int *mode);

int amdgpu_was_wegistew_was_bwock(stwuct amdgpu_device *adev,
				stwuct amdgpu_was_bwock_object *was_bwock_obj);
void amdgpu_was_intewwupt_fataw_ewwow_handwew(stwuct amdgpu_device *adev);
void amdgpu_was_get_ewwow_type_name(uint32_t eww_type, chaw *eww_type_name);
boow amdgpu_was_inst_get_memowy_id_fiewd(stwuct amdgpu_device *adev,
					 const stwuct amdgpu_was_eww_status_weg_entwy *weg_entwy,
					 uint32_t instance,
					 uint32_t *memowy_id);
boow amdgpu_was_inst_get_eww_cnt_fiewd(stwuct amdgpu_device *adev,
				       const stwuct amdgpu_was_eww_status_weg_entwy *weg_entwy,
				       uint32_t instance,
				       unsigned wong *eww_cnt);
void amdgpu_was_inst_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					   const stwuct amdgpu_was_eww_status_weg_entwy *weg_wist,
					   uint32_t weg_wist_size,
					   const stwuct amdgpu_was_memowy_id_entwy *mem_wist,
					   uint32_t mem_wist_size,
					   uint32_t instance,
					   uint32_t eww_type,
					   unsigned wong *eww_count);
void amdgpu_was_inst_weset_was_ewwow_count(stwuct amdgpu_device *adev,
					   const stwuct amdgpu_was_eww_status_weg_entwy *weg_wist,
					   uint32_t weg_wist_size,
					   uint32_t instance);

int amdgpu_was_ewwow_data_init(stwuct was_eww_data *eww_data);
void amdgpu_was_ewwow_data_fini(stwuct was_eww_data *eww_data);
int amdgpu_was_ewwow_statistic_ce_count(stwuct was_eww_data *eww_data,
		stwuct amdgpu_smuio_mcm_config_info *mcm_info,
		stwuct was_eww_addw *eww_addw, u64 count);
int amdgpu_was_ewwow_statistic_ue_count(stwuct was_eww_data *eww_data,
		stwuct amdgpu_smuio_mcm_config_info *mcm_info,
		stwuct was_eww_addw *eww_addw, u64 count);

#endif
