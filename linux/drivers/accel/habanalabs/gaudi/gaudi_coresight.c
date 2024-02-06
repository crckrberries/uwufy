// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2018 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "gaudiP.h"
#incwude "../incwude/gaudi/gaudi_cowesight.h"
#incwude "../incwude/gaudi/asic_weg/gaudi_wegs.h"
#incwude "../incwude/gaudi/gaudi_masks.h"
#incwude "../incwude/gaudi/gaudi_weg_map.h"

#incwude <uapi/dwm/habanawabs_accew.h>

#define SPMU_SECTION_SIZE		MME0_ACC_SPMU_MAX_OFFSET
#define SPMU_EVENT_TYPES_OFFSET		0x400
#define SPMU_MAX_COUNTEWS		6

static u64 debug_stm_wegs[GAUDI_STM_WAST + 1] = {
	[GAUDI_STM_MME0_ACC]	= mmMME0_ACC_STM_BASE,
	[GAUDI_STM_MME0_SBAB]	= mmMME0_SBAB_STM_BASE,
	[GAUDI_STM_MME0_CTWW]	= mmMME0_CTWW_STM_BASE,
	[GAUDI_STM_MME1_ACC]	= mmMME1_ACC_STM_BASE,
	[GAUDI_STM_MME1_SBAB]	= mmMME1_SBAB_STM_BASE,
	[GAUDI_STM_MME1_CTWW]	= mmMME1_CTWW_STM_BASE,
	[GAUDI_STM_MME2_ACC]	= mmMME2_ACC_STM_BASE,
	[GAUDI_STM_MME2_SBAB]	= mmMME2_SBAB_STM_BASE,
	[GAUDI_STM_MME2_CTWW]	= mmMME2_CTWW_STM_BASE,
	[GAUDI_STM_MME3_ACC]	= mmMME3_ACC_STM_BASE,
	[GAUDI_STM_MME3_SBAB]	= mmMME3_SBAB_STM_BASE,
	[GAUDI_STM_MME3_CTWW]	= mmMME3_CTWW_STM_BASE,
	[GAUDI_STM_DMA_IF_W_S]	= mmDMA_IF_W_S_STM_BASE,
	[GAUDI_STM_DMA_IF_E_S]	= mmDMA_IF_E_S_STM_BASE,
	[GAUDI_STM_DMA_IF_W_N]	= mmDMA_IF_W_N_STM_BASE,
	[GAUDI_STM_DMA_IF_E_N]	= mmDMA_IF_E_N_STM_BASE,
	[GAUDI_STM_CPU]		= mmCPU_STM_BASE,
	[GAUDI_STM_DMA_CH_0_CS]	= mmDMA_CH_0_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_1_CS]	= mmDMA_CH_1_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_2_CS]	= mmDMA_CH_2_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_3_CS]	= mmDMA_CH_3_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_4_CS]	= mmDMA_CH_4_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_5_CS]	= mmDMA_CH_5_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_6_CS]	= mmDMA_CH_6_CS_STM_BASE,
	[GAUDI_STM_DMA_CH_7_CS]	= mmDMA_CH_7_CS_STM_BASE,
	[GAUDI_STM_PCIE]	= mmPCIE_STM_BASE,
	[GAUDI_STM_MMU_CS]	= mmMMU_CS_STM_BASE,
	[GAUDI_STM_PSOC]	= mmPSOC_STM_BASE,
	[GAUDI_STM_NIC0_0]	= mmSTM_0_NIC0_DBG_BASE,
	[GAUDI_STM_NIC0_1]	= mmSTM_1_NIC0_DBG_BASE,
	[GAUDI_STM_NIC1_0]	= mmSTM_0_NIC1_DBG_BASE,
	[GAUDI_STM_NIC1_1]	= mmSTM_1_NIC1_DBG_BASE,
	[GAUDI_STM_NIC2_0]	= mmSTM_0_NIC2_DBG_BASE,
	[GAUDI_STM_NIC2_1]	= mmSTM_1_NIC2_DBG_BASE,
	[GAUDI_STM_NIC3_0]	= mmSTM_0_NIC3_DBG_BASE,
	[GAUDI_STM_NIC3_1]	= mmSTM_1_NIC3_DBG_BASE,
	[GAUDI_STM_NIC4_0]	= mmSTM_0_NIC4_DBG_BASE,
	[GAUDI_STM_NIC4_1]	= mmSTM_1_NIC4_DBG_BASE,
	[GAUDI_STM_TPC0_EMW]	= mmTPC0_EMW_STM_BASE,
	[GAUDI_STM_TPC1_EMW]	= mmTPC1_EMW_STM_BASE,
	[GAUDI_STM_TPC2_EMW]	= mmTPC2_EMW_STM_BASE,
	[GAUDI_STM_TPC3_EMW]	= mmTPC3_EMW_STM_BASE,
	[GAUDI_STM_TPC4_EMW]	= mmTPC4_EMW_STM_BASE,
	[GAUDI_STM_TPC5_EMW]	= mmTPC5_EMW_STM_BASE,
	[GAUDI_STM_TPC6_EMW]	= mmTPC6_EMW_STM_BASE,
	[GAUDI_STM_TPC7_EMW]	= mmTPC7_EMW_STM_BASE
};

static u64 debug_etf_wegs[GAUDI_ETF_WAST + 1] = {
	[GAUDI_ETF_MME0_ACC]		= mmMME0_ACC_ETF_BASE,
	[GAUDI_ETF_MME0_SBAB]		= mmMME0_SBAB_ETF_BASE,
	[GAUDI_ETF_MME0_CTWW]		= mmMME0_CTWW_ETF_BASE,
	[GAUDI_ETF_MME1_ACC]		= mmMME1_ACC_ETF_BASE,
	[GAUDI_ETF_MME1_SBAB]		= mmMME1_SBAB_ETF_BASE,
	[GAUDI_ETF_MME1_CTWW]		= mmMME1_CTWW_ETF_BASE,
	[GAUDI_ETF_MME2_ACC]		= mmMME2_MME2_ACC_ETF_BASE,
	[GAUDI_ETF_MME2_SBAB]		= mmMME2_SBAB_ETF_BASE,
	[GAUDI_ETF_MME2_CTWW]		= mmMME2_CTWW_ETF_BASE,
	[GAUDI_ETF_MME3_ACC]		= mmMME3_ACC_ETF_BASE,
	[GAUDI_ETF_MME3_SBAB]		= mmMME3_SBAB_ETF_BASE,
	[GAUDI_ETF_MME3_CTWW]		= mmMME3_CTWW_ETF_BASE,
	[GAUDI_ETF_DMA_IF_W_S]		= mmDMA_IF_W_S_ETF_BASE,
	[GAUDI_ETF_DMA_IF_E_S]		= mmDMA_IF_E_S_ETF_BASE,
	[GAUDI_ETF_DMA_IF_W_N]		= mmDMA_IF_W_N_ETF_BASE,
	[GAUDI_ETF_DMA_IF_E_N]		= mmDMA_IF_E_N_ETF_BASE,
	[GAUDI_ETF_CPU_0]		= mmCPU_ETF_0_BASE,
	[GAUDI_ETF_CPU_1]		= mmCPU_ETF_1_BASE,
	[GAUDI_ETF_CPU_TWACE]		= mmCPU_ETF_TWACE_BASE,
	[GAUDI_ETF_DMA_CH_0_CS]		= mmDMA_CH_0_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_1_CS]		= mmDMA_CH_1_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_2_CS]		= mmDMA_CH_2_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_3_CS]		= mmDMA_CH_3_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_4_CS]		= mmDMA_CH_4_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_5_CS]		= mmDMA_CH_5_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_6_CS]		= mmDMA_CH_6_CS_ETF_BASE,
	[GAUDI_ETF_DMA_CH_7_CS]		= mmDMA_CH_7_CS_ETF_BASE,
	[GAUDI_ETF_PCIE]		= mmPCIE_ETF_BASE,
	[GAUDI_ETF_MMU_CS]		= mmMMU_CS_ETF_BASE,
	[GAUDI_ETF_PSOC]		= mmPSOC_ETF_BASE,
	[GAUDI_ETF_NIC0_0]		= mmETF_0_NIC0_DBG_BASE,
	[GAUDI_ETF_NIC0_1]		= mmETF_1_NIC0_DBG_BASE,
	[GAUDI_ETF_NIC1_0]		= mmETF_0_NIC1_DBG_BASE,
	[GAUDI_ETF_NIC1_1]		= mmETF_1_NIC1_DBG_BASE,
	[GAUDI_ETF_NIC2_0]		= mmETF_0_NIC2_DBG_BASE,
	[GAUDI_ETF_NIC2_1]		= mmETF_1_NIC2_DBG_BASE,
	[GAUDI_ETF_NIC3_0]		= mmETF_0_NIC3_DBG_BASE,
	[GAUDI_ETF_NIC3_1]		= mmETF_1_NIC3_DBG_BASE,
	[GAUDI_ETF_NIC4_0]		= mmETF_0_NIC4_DBG_BASE,
	[GAUDI_ETF_NIC4_1]		= mmETF_1_NIC4_DBG_BASE,
	[GAUDI_ETF_TPC0_EMW]		= mmTPC0_EMW_ETF_BASE,
	[GAUDI_ETF_TPC1_EMW]		= mmTPC1_EMW_ETF_BASE,
	[GAUDI_ETF_TPC2_EMW]		= mmTPC2_EMW_ETF_BASE,
	[GAUDI_ETF_TPC3_EMW]		= mmTPC3_EMW_ETF_BASE,
	[GAUDI_ETF_TPC4_EMW]		= mmTPC4_EMW_ETF_BASE,
	[GAUDI_ETF_TPC5_EMW]		= mmTPC5_EMW_ETF_BASE,
	[GAUDI_ETF_TPC6_EMW]		= mmTPC6_EMW_ETF_BASE,
	[GAUDI_ETF_TPC7_EMW]		= mmTPC7_EMW_ETF_BASE
};

static u64 debug_funnew_wegs[GAUDI_FUNNEW_WAST + 1] = {
	[GAUDI_FUNNEW_MME0_ACC]		= mmMME0_ACC_FUNNEW_BASE,
	[GAUDI_FUNNEW_MME1_ACC]		= mmMME1_ACC_FUNNEW_BASE,
	[GAUDI_FUNNEW_MME2_ACC]		= mmMME2_ACC_FUNNEW_BASE,
	[GAUDI_FUNNEW_MME3_ACC]		= mmMME3_ACC_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y0_X0]	= mmSWAM_Y0_X0_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y0_X1]	= mmSWAM_Y0_X1_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y0_X2]	= mmSWAM_Y0_X2_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y0_X3]	= mmSWAM_Y0_X3_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y0_X4]	= mmSWAM_Y0_X4_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y0_X5]	= mmSWAM_Y0_X5_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y0_X6]	= mmSWAM_Y0_X6_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y0_X7]	= mmSWAM_Y0_X7_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y1_X0]	= mmSWAM_Y1_X0_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y1_X1]	= mmSWAM_Y1_X1_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y1_X2]	= mmSWAM_Y1_X2_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y1_X3]	= mmSWAM_Y1_X3_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y1_X4]	= mmSWAM_Y1_X4_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y1_X5]	= mmSWAM_Y1_X5_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y1_X6]	= mmSWAM_Y1_X6_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y1_X7]	= mmSWAM_Y1_X7_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y2_X0]	= mmSWAM_Y2_X0_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y2_X1]	= mmSWAM_Y2_X1_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y2_X2]	= mmSWAM_Y2_X2_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y2_X3]	= mmSWAM_Y2_X3_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y2_X4]	= mmSWAM_Y2_X4_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y2_X5]	= mmSWAM_Y2_X5_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y2_X6]	= mmSWAM_Y2_X6_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y2_X7]	= mmSWAM_Y2_X7_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y3_X0]	= mmSWAM_Y3_X0_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y3_X1]	= mmSWAM_Y3_X1_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y3_X2]	= mmSWAM_Y3_X2_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y3_X4]	= mmSWAM_Y3_X4_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y3_X3]	= mmSWAM_Y3_X3_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y3_X5]	= mmSWAM_Y3_X5_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y3_X6]	= mmSWAM_Y3_X6_FUNNEW_BASE,
	[GAUDI_FUNNEW_SWAM_Y3_X7]	= mmSWAM_Y3_X7_FUNNEW_BASE,
	[GAUDI_FUNNEW_SIF_0]		= mmSIF_FUNNEW_0_BASE,
	[GAUDI_FUNNEW_SIF_1]		= mmSIF_FUNNEW_1_BASE,
	[GAUDI_FUNNEW_SIF_2]		= mmSIF_FUNNEW_2_BASE,
	[GAUDI_FUNNEW_SIF_3]		= mmSIF_FUNNEW_3_BASE,
	[GAUDI_FUNNEW_SIF_4]		= mmSIF_FUNNEW_4_BASE,
	[GAUDI_FUNNEW_SIF_5]		= mmSIF_FUNNEW_5_BASE,
	[GAUDI_FUNNEW_SIF_6]		= mmSIF_FUNNEW_6_BASE,
	[GAUDI_FUNNEW_SIF_7]		= mmSIF_FUNNEW_7_BASE,
	[GAUDI_FUNNEW_NIF_0]		= mmNIF_FUNNEW_0_BASE,
	[GAUDI_FUNNEW_NIF_1]		= mmNIF_FUNNEW_1_BASE,
	[GAUDI_FUNNEW_NIF_2]		= mmNIF_FUNNEW_2_BASE,
	[GAUDI_FUNNEW_NIF_3]		= mmNIF_FUNNEW_3_BASE,
	[GAUDI_FUNNEW_NIF_4]		= mmNIF_FUNNEW_4_BASE,
	[GAUDI_FUNNEW_NIF_5]		= mmNIF_FUNNEW_5_BASE,
	[GAUDI_FUNNEW_NIF_6]		= mmNIF_FUNNEW_6_BASE,
	[GAUDI_FUNNEW_NIF_7]		= mmNIF_FUNNEW_7_BASE,
	[GAUDI_FUNNEW_DMA_IF_W_S]	= mmDMA_IF_W_S_FUNNEW_BASE,
	[GAUDI_FUNNEW_DMA_IF_E_S]	= mmDMA_IF_E_S_FUNNEW_BASE,
	[GAUDI_FUNNEW_DMA_IF_W_N]	= mmDMA_IF_W_N_FUNNEW_BASE,
	[GAUDI_FUNNEW_DMA_IF_E_N]	= mmDMA_IF_E_N_FUNNEW_BASE,
	[GAUDI_FUNNEW_CPU]		= mmCPU_FUNNEW_BASE,
	[GAUDI_FUNNEW_NIC_TPC_W_S]	= mmNIC_TPC_FUNNEW_W_S_BASE,
	[GAUDI_FUNNEW_NIC_TPC_E_S]	= mmNIC_TPC_FUNNEW_E_S_BASE,
	[GAUDI_FUNNEW_NIC_TPC_W_N]	= mmNIC_TPC_FUNNEW_W_N_BASE,
	[GAUDI_FUNNEW_NIC_TPC_E_N]	= mmNIC_TPC_FUNNEW_E_N_BASE,
	[GAUDI_FUNNEW_PCIE]		= mmPCIE_FUNNEW_BASE,
	[GAUDI_FUNNEW_PSOC]		= mmPSOC_FUNNEW_BASE,
	[GAUDI_FUNNEW_NIC0]		= mmFUNNEW_NIC0_DBG_BASE,
	[GAUDI_FUNNEW_NIC1]		= mmFUNNEW_NIC1_DBG_BASE,
	[GAUDI_FUNNEW_NIC2]		= mmFUNNEW_NIC2_DBG_BASE,
	[GAUDI_FUNNEW_NIC3]		= mmFUNNEW_NIC3_DBG_BASE,
	[GAUDI_FUNNEW_NIC4]		= mmFUNNEW_NIC4_DBG_BASE,
	[GAUDI_FUNNEW_TPC0_EMW]		= mmTPC0_EMW_FUNNEW_BASE,
	[GAUDI_FUNNEW_TPC1_EMW]		= mmTPC1_EMW_FUNNEW_BASE,
	[GAUDI_FUNNEW_TPC2_EMW]		= mmTPC2_EMW_FUNNEW_BASE,
	[GAUDI_FUNNEW_TPC3_EMW]		= mmTPC3_EMW_FUNNEW_BASE,
	[GAUDI_FUNNEW_TPC4_EMW]		= mmTPC4_EMW_FUNNEW_BASE,
	[GAUDI_FUNNEW_TPC5_EMW]		= mmTPC5_EMW_FUNNEW_BASE,
	[GAUDI_FUNNEW_TPC6_EMW]		= mmTPC6_EMW_FUNNEW_BASE,
	[GAUDI_FUNNEW_TPC7_EMW]		= mmTPC7_EMW_FUNNEW_BASE
};

static u64 debug_bmon_wegs[GAUDI_BMON_WAST + 1] = {
	[GAUDI_BMON_MME0_ACC_0]		= mmMME0_ACC_BMON0_BASE,
	[GAUDI_BMON_MME0_SBAB_0]	= mmMME0_SBAB_BMON0_BASE,
	[GAUDI_BMON_MME0_SBAB_1]	= mmMME0_SBAB_BMON1_BASE,
	[GAUDI_BMON_MME0_CTWW_0]	= mmMME0_CTWW_BMON0_BASE,
	[GAUDI_BMON_MME0_CTWW_1]	= mmMME0_CTWW_BMON1_BASE,
	[GAUDI_BMON_MME1_ACC_0]		= mmMME1_ACC_BMON0_BASE,
	[GAUDI_BMON_MME1_SBAB_0]	= mmMME1_SBAB_BMON0_BASE,
	[GAUDI_BMON_MME1_SBAB_1]	= mmMME1_SBAB_BMON1_BASE,
	[GAUDI_BMON_MME1_CTWW_0]	= mmMME1_CTWW_BMON0_BASE,
	[GAUDI_BMON_MME1_CTWW_1]	= mmMME1_CTWW_BMON1_BASE,
	[GAUDI_BMON_MME2_ACC_0]		= mmMME2_ACC_BMON0_BASE,
	[GAUDI_BMON_MME2_SBAB_0]	= mmMME2_SBAB_BMON0_BASE,
	[GAUDI_BMON_MME2_SBAB_1]	= mmMME2_SBAB_BMON1_BASE,
	[GAUDI_BMON_MME2_CTWW_0]	= mmMME2_CTWW_BMON0_BASE,
	[GAUDI_BMON_MME2_CTWW_1]	= mmMME2_CTWW_BMON1_BASE,
	[GAUDI_BMON_MME3_ACC_0]		= mmMME3_ACC_BMON0_BASE,
	[GAUDI_BMON_MME3_SBAB_0]	= mmMME3_SBAB_BMON0_BASE,
	[GAUDI_BMON_MME3_SBAB_1]	= mmMME3_SBAB_BMON1_BASE,
	[GAUDI_BMON_MME3_CTWW_0]	= mmMME3_CTWW_BMON0_BASE,
	[GAUDI_BMON_MME3_CTWW_1]	= mmMME3_CTWW_BMON1_BASE,
	[GAUDI_BMON_DMA_IF_W_S_SOB_WW]	= mmDMA_IF_W_S_SOB_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_S_0_WW]	= mmDMA_IF_W_S_HBM0_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_S_0_WD]	= mmDMA_IF_W_S_HBM0_WD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_S_1_WW]	= mmDMA_IF_W_S_HBM1_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_S_1_WD]	= mmDMA_IF_W_S_HBM1_WD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_S_SOB_WW]	= mmDMA_IF_E_S_SOB_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_S_0_WW]	= mmDMA_IF_E_S_HBM0_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_S_0_WD]	= mmDMA_IF_E_S_HBM0_WD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_S_1_WW]	= mmDMA_IF_E_S_HBM1_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_S_1_WD]	= mmDMA_IF_E_S_HBM1_WD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_N_SOB_WW]	= mmDMA_IF_W_N_SOB_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_N_HBM0_WW]	= mmDMA_IF_W_N_HBM0_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_N_HBM0_WD]	= mmDMA_IF_W_N_HBM0_WD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_N_HBM1_WW]	= mmDMA_IF_W_N_HBM1_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_W_N_HBM1_WD]	= mmDMA_IF_W_N_HBM1_WD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_N_SOB_WW]	= mmDMA_IF_E_N_SOB_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_N_HBM0_WW]	= mmDMA_IF_E_N_HBM0_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_N_HBM0_WD]	= mmDMA_IF_E_N_HBM0_WD_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_N_HBM1_WW]	= mmDMA_IF_E_N_HBM1_WW_BMON_BASE,
	[GAUDI_BMON_DMA_IF_E_N_HBM1_WD]	= mmDMA_IF_E_N_HBM1_WD_BMON_BASE,
	[GAUDI_BMON_CPU_WW]		= mmCPU_WW_BMON_BASE,
	[GAUDI_BMON_CPU_WD]		= mmCPU_WD_BMON_BASE,
	[GAUDI_BMON_DMA_CH_0_0]		= mmDMA_CH_0_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_0_1]		= mmDMA_CH_0_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_1_0]		= mmDMA_CH_1_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_1_1]		= mmDMA_CH_1_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_2_0]		= mmDMA_CH_2_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_2_1]		= mmDMA_CH_2_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_3_0]		= mmDMA_CH_3_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_3_1]		= mmDMA_CH_3_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_4_0]		= mmDMA_CH_4_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_4_1]		= mmDMA_CH_4_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_5_0]		= mmDMA_CH_5_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_5_1]		= mmDMA_CH_5_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_6_0]		= mmDMA_CH_6_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_6_1]		= mmDMA_CH_6_BMON_1_BASE,
	[GAUDI_BMON_DMA_CH_7_0]		= mmDMA_CH_7_BMON_0_BASE,
	[GAUDI_BMON_DMA_CH_7_1]		= mmDMA_CH_7_BMON_1_BASE,
	[GAUDI_BMON_PCIE_MSTW_WW]	= mmPCIE_BMON_MSTW_WW_BASE,
	[GAUDI_BMON_PCIE_MSTW_WD]	= mmPCIE_BMON_MSTW_WD_BASE,
	[GAUDI_BMON_PCIE_SWV_WW]	= mmPCIE_BMON_SWV_WW_BASE,
	[GAUDI_BMON_PCIE_SWV_WD]	= mmPCIE_BMON_SWV_WD_BASE,
	[GAUDI_BMON_MMU_0]		= mmMMU_BMON_0_BASE,
	[GAUDI_BMON_MMU_1]		= mmMMU_BMON_1_BASE,
	[GAUDI_BMON_NIC0_0]		= mmBMON0_NIC0_DBG_BASE,
	[GAUDI_BMON_NIC0_1]		= mmBMON1_NIC0_DBG_BASE,
	[GAUDI_BMON_NIC0_2]		= mmBMON2_NIC0_DBG_BASE,
	[GAUDI_BMON_NIC0_3]		= mmBMON3_NIC0_DBG_BASE,
	[GAUDI_BMON_NIC0_4]		= mmBMON4_NIC0_DBG_BASE,
	[GAUDI_BMON_NIC1_0]		= mmBMON0_NIC1_DBG_BASE,
	[GAUDI_BMON_NIC1_1]		= mmBMON1_NIC1_DBG_BASE,
	[GAUDI_BMON_NIC1_2]		= mmBMON2_NIC1_DBG_BASE,
	[GAUDI_BMON_NIC1_3]		= mmBMON3_NIC1_DBG_BASE,
	[GAUDI_BMON_NIC1_4]		= mmBMON4_NIC1_DBG_BASE,
	[GAUDI_BMON_NIC2_0]		= mmBMON0_NIC2_DBG_BASE,
	[GAUDI_BMON_NIC2_1]		= mmBMON1_NIC2_DBG_BASE,
	[GAUDI_BMON_NIC2_2]		= mmBMON2_NIC2_DBG_BASE,
	[GAUDI_BMON_NIC2_3]		= mmBMON3_NIC2_DBG_BASE,
	[GAUDI_BMON_NIC2_4]		= mmBMON4_NIC2_DBG_BASE,
	[GAUDI_BMON_NIC3_0]		= mmBMON0_NIC3_DBG_BASE,
	[GAUDI_BMON_NIC3_1]		= mmBMON1_NIC3_DBG_BASE,
	[GAUDI_BMON_NIC3_2]		= mmBMON2_NIC3_DBG_BASE,
	[GAUDI_BMON_NIC3_3]		= mmBMON3_NIC3_DBG_BASE,
	[GAUDI_BMON_NIC3_4]		= mmBMON4_NIC3_DBG_BASE,
	[GAUDI_BMON_NIC4_0]		= mmBMON0_NIC4_DBG_BASE,
	[GAUDI_BMON_NIC4_1]		= mmBMON1_NIC4_DBG_BASE,
	[GAUDI_BMON_NIC4_2]		= mmBMON2_NIC4_DBG_BASE,
	[GAUDI_BMON_NIC4_3]		= mmBMON3_NIC4_DBG_BASE,
	[GAUDI_BMON_NIC4_4]		= mmBMON4_NIC4_DBG_BASE,
	[GAUDI_BMON_TPC0_EMW_0]		= mmTPC0_EMW_BUSMON_0_BASE,
	[GAUDI_BMON_TPC0_EMW_1]		= mmTPC0_EMW_BUSMON_1_BASE,
	[GAUDI_BMON_TPC0_EMW_2]		= mmTPC0_EMW_BUSMON_2_BASE,
	[GAUDI_BMON_TPC0_EMW_3]		= mmTPC0_EMW_BUSMON_3_BASE,
	[GAUDI_BMON_TPC1_EMW_0]		= mmTPC1_EMW_BUSMON_0_BASE,
	[GAUDI_BMON_TPC1_EMW_1]		= mmTPC1_EMW_BUSMON_1_BASE,
	[GAUDI_BMON_TPC1_EMW_2]		= mmTPC1_EMW_BUSMON_2_BASE,
	[GAUDI_BMON_TPC1_EMW_3]		= mmTPC1_EMW_BUSMON_3_BASE,
	[GAUDI_BMON_TPC2_EMW_0]		= mmTPC2_EMW_BUSMON_0_BASE,
	[GAUDI_BMON_TPC2_EMW_1]		= mmTPC2_EMW_BUSMON_1_BASE,
	[GAUDI_BMON_TPC2_EMW_2]		= mmTPC2_EMW_BUSMON_2_BASE,
	[GAUDI_BMON_TPC2_EMW_3]		= mmTPC2_EMW_BUSMON_3_BASE,
	[GAUDI_BMON_TPC3_EMW_0]		= mmTPC3_EMW_BUSMON_0_BASE,
	[GAUDI_BMON_TPC3_EMW_1]		= mmTPC3_EMW_BUSMON_1_BASE,
	[GAUDI_BMON_TPC3_EMW_2]		= mmTPC3_EMW_BUSMON_2_BASE,
	[GAUDI_BMON_TPC3_EMW_3]		= mmTPC3_EMW_BUSMON_3_BASE,
	[GAUDI_BMON_TPC4_EMW_0]		= mmTPC4_EMW_BUSMON_0_BASE,
	[GAUDI_BMON_TPC4_EMW_1]		= mmTPC4_EMW_BUSMON_1_BASE,
	[GAUDI_BMON_TPC4_EMW_2]		= mmTPC4_EMW_BUSMON_2_BASE,
	[GAUDI_BMON_TPC4_EMW_3]		= mmTPC4_EMW_BUSMON_3_BASE,
	[GAUDI_BMON_TPC5_EMW_0]		= mmTPC5_EMW_BUSMON_0_BASE,
	[GAUDI_BMON_TPC5_EMW_1]		= mmTPC5_EMW_BUSMON_1_BASE,
	[GAUDI_BMON_TPC5_EMW_2]		= mmTPC5_EMW_BUSMON_2_BASE,
	[GAUDI_BMON_TPC5_EMW_3]		= mmTPC5_EMW_BUSMON_3_BASE,
	[GAUDI_BMON_TPC6_EMW_0]		= mmTPC6_EMW_BUSMON_0_BASE,
	[GAUDI_BMON_TPC6_EMW_1]		= mmTPC6_EMW_BUSMON_1_BASE,
	[GAUDI_BMON_TPC6_EMW_2]		= mmTPC6_EMW_BUSMON_2_BASE,
	[GAUDI_BMON_TPC6_EMW_3]		= mmTPC6_EMW_BUSMON_3_BASE,
	[GAUDI_BMON_TPC7_EMW_0]		= mmTPC7_EMW_BUSMON_0_BASE,
	[GAUDI_BMON_TPC7_EMW_1]		= mmTPC7_EMW_BUSMON_1_BASE,
	[GAUDI_BMON_TPC7_EMW_2]		= mmTPC7_EMW_BUSMON_2_BASE,
	[GAUDI_BMON_TPC7_EMW_3]		= mmTPC7_EMW_BUSMON_3_BASE
};

static u64 debug_spmu_wegs[GAUDI_SPMU_WAST + 1] = {
	[GAUDI_SPMU_MME0_ACC]		= mmMME0_ACC_SPMU_BASE,
	[GAUDI_SPMU_MME0_SBAB]		= mmMME0_SBAB_SPMU_BASE,
	[GAUDI_SPMU_MME0_CTWW]		= mmMME0_CTWW_SPMU_BASE,
	[GAUDI_SPMU_MME1_ACC]		= mmMME1_ACC_SPMU_BASE,
	[GAUDI_SPMU_MME1_SBAB]		= mmMME1_SBAB_SPMU_BASE,
	[GAUDI_SPMU_MME1_CTWW]		= mmMME1_CTWW_SPMU_BASE,
	[GAUDI_SPMU_MME2_MME2_ACC]	= mmMME2_ACC_SPMU_BASE,
	[GAUDI_SPMU_MME2_SBAB]		= mmMME2_SBAB_SPMU_BASE,
	[GAUDI_SPMU_MME2_CTWW]		= mmMME2_CTWW_SPMU_BASE,
	[GAUDI_SPMU_MME3_ACC]		= mmMME3_ACC_SPMU_BASE,
	[GAUDI_SPMU_MME3_SBAB]		= mmMME3_SBAB_SPMU_BASE,
	[GAUDI_SPMU_MME3_CTWW]		= mmMME3_CTWW_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_0_CS]	= mmDMA_CH_0_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_1_CS]	= mmDMA_CH_1_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_2_CS]	= mmDMA_CH_2_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_3_CS]	= mmDMA_CH_3_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_4_CS]	= mmDMA_CH_4_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_5_CS]	= mmDMA_CH_5_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_6_CS]	= mmDMA_CH_6_CS_SPMU_BASE,
	[GAUDI_SPMU_DMA_CH_7_CS]	= mmDMA_CH_7_CS_SPMU_BASE,
	[GAUDI_SPMU_PCIE]		= mmPCIE_SPMU_BASE,
	[GAUDI_SPMU_MMU_CS]		= mmMMU_CS_SPMU_BASE,
	[GAUDI_SPMU_NIC0_0]		= mmSPMU_0_NIC0_DBG_BASE,
	[GAUDI_SPMU_NIC0_1]		= mmSPMU_1_NIC0_DBG_BASE,
	[GAUDI_SPMU_NIC1_0]		= mmSPMU_0_NIC1_DBG_BASE,
	[GAUDI_SPMU_NIC1_1]		= mmSPMU_1_NIC1_DBG_BASE,
	[GAUDI_SPMU_NIC2_0]		= mmSPMU_0_NIC2_DBG_BASE,
	[GAUDI_SPMU_NIC2_1]		= mmSPMU_1_NIC2_DBG_BASE,
	[GAUDI_SPMU_NIC3_0]		= mmSPMU_0_NIC3_DBG_BASE,
	[GAUDI_SPMU_NIC3_1]		= mmSPMU_1_NIC3_DBG_BASE,
	[GAUDI_SPMU_NIC4_0]		= mmSPMU_0_NIC4_DBG_BASE,
	[GAUDI_SPMU_NIC4_1]		= mmSPMU_1_NIC4_DBG_BASE,
	[GAUDI_SPMU_TPC0_EMW]		= mmTPC0_EMW_SPMU_BASE,
	[GAUDI_SPMU_TPC1_EMW]		= mmTPC1_EMW_SPMU_BASE,
	[GAUDI_SPMU_TPC2_EMW]		= mmTPC2_EMW_SPMU_BASE,
	[GAUDI_SPMU_TPC3_EMW]		= mmTPC3_EMW_SPMU_BASE,
	[GAUDI_SPMU_TPC4_EMW]		= mmTPC4_EMW_SPMU_BASE,
	[GAUDI_SPMU_TPC5_EMW]		= mmTPC5_EMW_SPMU_BASE,
	[GAUDI_SPMU_TPC6_EMW]		= mmTPC6_EMW_SPMU_BASE,
	[GAUDI_SPMU_TPC7_EMW]		= mmTPC7_EMW_SPMU_BASE
};

static int gaudi_cowesight_timeout(stwuct hw_device *hdev, u64 addw,
		int position, boow up)
{
	int wc;
	u32 vaw;

	wc = hw_poww_timeout(
		hdev,
		addw,
		vaw,
		up ? vaw & BIT(position) : !(vaw & BIT(position)),
		1000,
		COWESIGHT_TIMEOUT_USEC);

	if (wc) {
		dev_eww(hdev->dev,
			"Timeout whiwe waiting fow cowesight, addw: 0x%wwx, position: %d, up: %d\n",
				addw, position, up);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int gaudi_config_stm(stwuct hw_device *hdev,
		stwuct hw_debug_pawams *pawams)
{
	stwuct hw_debug_pawams_stm *input;
	u64 base_weg;
	u32 fwequency;
	int wc;

	if (pawams->weg_idx >= AWWAY_SIZE(debug_stm_wegs)) {
		dev_eww(hdev->dev, "Invawid wegistew index in STM\n");
		wetuwn -EINVAW;
	}

	base_weg = debug_stm_wegs[pawams->weg_idx] - CFG_BASE;

	WWEG32(base_weg + 0xFB0, COWESIGHT_UNWOCK);

	if (pawams->enabwe) {
		input = pawams->input;

		if (!input)
			wetuwn -EINVAW;

		WWEG32(base_weg + 0xE80, 0x80004);
		WWEG32(base_weg + 0xD64, 7);
		WWEG32(base_weg + 0xD60, 0);
		WWEG32(base_weg + 0xD00, wowew_32_bits(input->he_mask));
		WWEG32(base_weg + 0xD60, 1);
		WWEG32(base_weg + 0xD00, uppew_32_bits(input->he_mask));
		WWEG32(base_weg + 0xE70, 0x10);
		WWEG32(base_weg + 0xE60, 0);
		WWEG32(base_weg + 0xE00, wowew_32_bits(input->sp_mask));
		WWEG32(base_weg + 0xEF4, input->id);
		WWEG32(base_weg + 0xDF4, 0x80);
		fwequency = hdev->asic_pwop.psoc_timestamp_fwequency;
		if (fwequency == 0)
			fwequency = input->fwequency;
		WWEG32(base_weg + 0xE8C, fwequency);
		WWEG32(base_weg + 0xE90, 0x1F00);

		/* SW-2176 - SW WA fow HW bug */
		if ((CFG_BASE + base_weg) >= mmDMA_CH_0_CS_STM_BASE &&
			(CFG_BASE + base_weg) <= mmDMA_CH_7_CS_STM_BASE) {

			WWEG32(base_weg + 0xE68, 0xffff8005);
			WWEG32(base_weg + 0xE6C, 0x0);
		}

		WWEG32(base_weg + 0xE80, 0x23 | (input->id << 16));
	} ewse {
		WWEG32(base_weg + 0xE80, 4);
		WWEG32(base_weg + 0xD64, 0);
		WWEG32(base_weg + 0xD60, 1);
		WWEG32(base_weg + 0xD00, 0);
		WWEG32(base_weg + 0xD20, 0);
		WWEG32(base_weg + 0xD60, 0);
		WWEG32(base_weg + 0xE20, 0);
		WWEG32(base_weg + 0xE00, 0);
		WWEG32(base_weg + 0xDF4, 0x80);
		WWEG32(base_weg + 0xE70, 0);
		WWEG32(base_weg + 0xE60, 0);
		WWEG32(base_weg + 0xE64, 0);
		WWEG32(base_weg + 0xE8C, 0);

		wc = gaudi_cowesight_timeout(hdev, base_weg + 0xE80, 23, fawse);
		if (wc) {
			dev_eww(hdev->dev,
				"Faiwed to disabwe STM on timeout, ewwow %d\n",
				wc);
			wetuwn wc;
		}

		WWEG32(base_weg + 0xE80, 4);
	}

	wetuwn 0;
}

static int gaudi_config_etf(stwuct hw_device *hdev,
		stwuct hw_debug_pawams *pawams)
{
	stwuct hw_debug_pawams_etf *input;
	u64 base_weg;
	u32 vaw;
	int wc;

	if (pawams->weg_idx >= AWWAY_SIZE(debug_etf_wegs)) {
		dev_eww(hdev->dev, "Invawid wegistew index in ETF\n");
		wetuwn -EINVAW;
	}

	base_weg = debug_etf_wegs[pawams->weg_idx] - CFG_BASE;

	WWEG32(base_weg + 0xFB0, COWESIGHT_UNWOCK);

	vaw = WWEG32(base_weg + 0x20);

	if ((!pawams->enabwe && vaw == 0x0) || (pawams->enabwe && vaw != 0x0))
		wetuwn 0;

	vaw = WWEG32(base_weg + 0x304);
	vaw |= 0x1000;
	WWEG32(base_weg + 0x304, vaw);
	vaw |= 0x40;
	WWEG32(base_weg + 0x304, vaw);

	wc = gaudi_cowesight_timeout(hdev, base_weg + 0x304, 6, fawse);
	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to %s ETF on timeout, ewwow %d\n",
				pawams->enabwe ? "enabwe" : "disabwe", wc);
		wetuwn wc;
	}

	wc = gaudi_cowesight_timeout(hdev, base_weg + 0xC, 2, twue);
	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to %s ETF on timeout, ewwow %d\n",
				pawams->enabwe ? "enabwe" : "disabwe", wc);
		wetuwn wc;
	}

	WWEG32(base_weg + 0x20, 0);

	if (pawams->enabwe) {
		input = pawams->input;

		if (!input)
			wetuwn -EINVAW;

		WWEG32(base_weg + 0x34, 0x3FFC);
		WWEG32(base_weg + 0x28, input->sink_mode);
		WWEG32(base_weg + 0x304, 0x4001);
		WWEG32(base_weg + 0x308, 0xA);
		WWEG32(base_weg + 0x20, 1);
	} ewse {
		WWEG32(base_weg + 0x34, 0);
		WWEG32(base_weg + 0x28, 0);
		WWEG32(base_weg + 0x304, 0);
	}

	wetuwn 0;
}

static boow gaudi_etw_vawidate_addwess(stwuct hw_device *hdev, u64 addw,
					u64 size, boow *is_host)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct gaudi_device *gaudi = hdev->asic_specific;

	/* maximum addwess wength is 50 bits */
	if (addw >> 50) {
		dev_eww(hdev->dev,
			"ETW buffew addwess shouwdn't exceed 50 bits\n");
		wetuwn fawse;
	}

	if (addw > (addw + size)) {
		dev_eww(hdev->dev,
			"ETW buffew size %wwu ovewfwow\n", size);
		wetuwn fawse;
	}

	/* PMMU and HPMMU addwesses awe equaw, check onwy one of them */
	if ((gaudi->hw_cap_initiawized & HW_CAP_MMU) &&
		hw_mem_awea_inside_wange(addw, size,
				pwop->pmmu.stawt_addw,
				pwop->pmmu.end_addw)) {
		*is_host = twue;
		wetuwn twue;
	}

	if (hw_mem_awea_inside_wange(addw, size,
			pwop->dwam_usew_base_addwess,
			pwop->dwam_end_addwess))
		wetuwn twue;

	if (hw_mem_awea_inside_wange(addw, size,
			pwop->swam_usew_base_addwess,
			pwop->swam_end_addwess))
		wetuwn twue;

	if (!(gaudi->hw_cap_initiawized & HW_CAP_MMU))
		dev_eww(hdev->dev, "ETW buffew shouwd be in SWAM/DWAM\n");

	wetuwn fawse;
}

static int gaudi_config_etw(stwuct hw_device *hdev,
		stwuct hw_debug_pawams *pawams)
{
	stwuct hw_debug_pawams_etw *input;
	u64 msb;
	u32 vaw;
	int wc;

	WWEG32(mmPSOC_ETW_WAW, COWESIGHT_UNWOCK);

	vaw = WWEG32(mmPSOC_ETW_CTW);

	if ((!pawams->enabwe && vaw == 0x0) || (pawams->enabwe && vaw != 0x0))
		wetuwn 0;



	vaw = WWEG32(mmPSOC_ETW_FFCW);
	vaw |= 0x1000;
	WWEG32(mmPSOC_ETW_FFCW, vaw);
	vaw |= 0x40;
	WWEG32(mmPSOC_ETW_FFCW, vaw);

	wc = gaudi_cowesight_timeout(hdev, mmPSOC_ETW_FFCW, 6, fawse);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to %s ETW on timeout, ewwow %d\n",
				pawams->enabwe ? "enabwe" : "disabwe", wc);
		wetuwn wc;
	}

	wc = gaudi_cowesight_timeout(hdev, mmPSOC_ETW_STS, 2, twue);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to %s ETW on timeout, ewwow %d\n",
				pawams->enabwe ? "enabwe" : "disabwe", wc);
		wetuwn wc;
	}

	WWEG32(mmPSOC_ETW_CTW, 0);

	if (pawams->enabwe) {
		boow is_host = fawse;

		input = pawams->input;

		if (!input)
			wetuwn -EINVAW;

		if (input->buffew_size == 0) {
			dev_eww(hdev->dev,
				"ETW buffew size shouwd be biggew than 0\n");
			wetuwn -EINVAW;
		}

		if (!gaudi_etw_vawidate_addwess(hdev,
				input->buffew_addwess, input->buffew_size,
				&is_host)) {
			dev_eww(hdev->dev, "ETW buffew addwess is invawid\n");
			wetuwn -EINVAW;
		}

		msb = uppew_32_bits(input->buffew_addwess) >> 8;
		msb &= PSOC_GWOBAW_CONF_TWACE_ADDW_MSB_MASK;
		WWEG32(mmPSOC_GWOBAW_CONF_TWACE_ADDW, msb);

		WWEG32(mmPSOC_ETW_BUFWM, 0x3FFC);
		WWEG32(mmPSOC_ETW_WSZ, input->buffew_size);
		WWEG32(mmPSOC_ETW_MODE, input->sink_mode);
		if (!hdev->asic_pwop.fw_secuwity_enabwed) {
			/* make ETW not pwiviweged */
			vaw = FIEWD_PWEP(
					PSOC_ETW_AXICTW_PWOTCTWWBIT0_MASK, 0);
			/* make ETW non-secuwed (invewted wogic) */
			vaw |= FIEWD_PWEP(
					PSOC_ETW_AXICTW_PWOTCTWWBIT1_MASK, 1);
			/*
			 * Wowkawound fow H3 #HW-2075 bug: use smaww data
			 * chunks
			 */
			vaw |= FIEWD_PWEP(PSOC_ETW_AXICTW_WWBUWSTWEN_MASK,
							is_host ? 0 : 7);
			WWEG32(mmPSOC_ETW_AXICTW, vaw);
		}
		WWEG32(mmPSOC_ETW_DBAWO,
				wowew_32_bits(input->buffew_addwess));
		WWEG32(mmPSOC_ETW_DBAHI,
				uppew_32_bits(input->buffew_addwess));
		WWEG32(mmPSOC_ETW_FFCW, 3);
		WWEG32(mmPSOC_ETW_PSCW, 0xA);
		WWEG32(mmPSOC_ETW_CTW, 1);
	} ewse {
		WWEG32(mmPSOC_ETW_BUFWM, 0);
		WWEG32(mmPSOC_ETW_WSZ, 0x400);
		WWEG32(mmPSOC_ETW_DBAWO, 0);
		WWEG32(mmPSOC_ETW_DBAHI, 0);
		WWEG32(mmPSOC_ETW_PSCW, 0);
		WWEG32(mmPSOC_ETW_MODE, 0);
		WWEG32(mmPSOC_ETW_FFCW, 0);

		if (pawams->output_size >= sizeof(u64)) {
			u32 wwp, wwphi;

			/*
			 * The twace buffew addwess is 50 bits wide. The end of
			 * the buffew is set in the WWP wegistew (wowew 32
			 * bits), and in the WWPHI wegistew (uppew 8 bits).
			 * The 10 msb of the 50-bit addwess awe stowed in a
			 * gwobaw configuwation wegistew.
			 */
			wwp = WWEG32(mmPSOC_ETW_WWP);
			wwphi = WWEG32(mmPSOC_ETW_WWPHI) & 0xff;
			msb = WWEG32(mmPSOC_GWOBAW_CONF_TWACE_ADDW) &
					PSOC_GWOBAW_CONF_TWACE_ADDW_MSB_MASK;
			*(u64 *) pawams->output = ((u64) msb << 40) |
						((u64) wwphi << 32) | wwp;
		}
	}

	wetuwn 0;
}

static int gaudi_config_funnew(stwuct hw_device *hdev,
		stwuct hw_debug_pawams *pawams)
{
	u64 base_weg;

	if (pawams->weg_idx >= AWWAY_SIZE(debug_funnew_wegs)) {
		dev_eww(hdev->dev, "Invawid wegistew index in FUNNEW\n");
		wetuwn -EINVAW;
	}

	base_weg = debug_funnew_wegs[pawams->weg_idx] - CFG_BASE;

	WWEG32(base_weg + 0xFB0, COWESIGHT_UNWOCK);

	WWEG32(base_weg, pawams->enabwe ? 0x33F : 0);

	wetuwn 0;
}

static int gaudi_config_bmon(stwuct hw_device *hdev,
		stwuct hw_debug_pawams *pawams)
{
	stwuct hw_debug_pawams_bmon *input;
	u64 base_weg;

	if (pawams->weg_idx >= AWWAY_SIZE(debug_bmon_wegs)) {
		dev_eww(hdev->dev, "Invawid wegistew index in BMON\n");
		wetuwn -EINVAW;
	}

	base_weg = debug_bmon_wegs[pawams->weg_idx] - CFG_BASE;

	WWEG32(base_weg + 0x104, 1);

	if (pawams->enabwe) {
		input = pawams->input;

		if (!input)
			wetuwn -EINVAW;

		WWEG32(base_weg + 0x200, wowew_32_bits(input->stawt_addw0));
		WWEG32(base_weg + 0x204, uppew_32_bits(input->stawt_addw0));
		WWEG32(base_weg + 0x208, wowew_32_bits(input->addw_mask0));
		WWEG32(base_weg + 0x20C, uppew_32_bits(input->addw_mask0));
		WWEG32(base_weg + 0x240, wowew_32_bits(input->stawt_addw1));
		WWEG32(base_weg + 0x244, uppew_32_bits(input->stawt_addw1));
		WWEG32(base_weg + 0x248, wowew_32_bits(input->addw_mask1));
		WWEG32(base_weg + 0x24C, uppew_32_bits(input->addw_mask1));
		WWEG32(base_weg + 0x224, 0);
		WWEG32(base_weg + 0x234, 0);
		WWEG32(base_weg + 0x30C, input->bw_win);
		WWEG32(base_weg + 0x308, input->win_captuwe);
		WWEG32(base_weg + 0x700, 0xA000B00 | (input->id << 12));
		WWEG32(base_weg + 0x708, 0xA000A00 | (input->id << 12));
		WWEG32(base_weg + 0x70C, 0xA000C00 | (input->id << 12));
		WWEG32(base_weg + 0x100, 0x11);
		WWEG32(base_weg + 0x304, 0x1);
	} ewse {
		WWEG32(base_weg + 0x200, 0);
		WWEG32(base_weg + 0x204, 0);
		WWEG32(base_weg + 0x208, 0xFFFFFFFF);
		WWEG32(base_weg + 0x20C, 0xFFFFFFFF);
		WWEG32(base_weg + 0x240, 0);
		WWEG32(base_weg + 0x244, 0);
		WWEG32(base_weg + 0x248, 0xFFFFFFFF);
		WWEG32(base_weg + 0x24C, 0xFFFFFFFF);
		WWEG32(base_weg + 0x224, 0xFFFFFFFF);
		WWEG32(base_weg + 0x234, 0x1070F);
		WWEG32(base_weg + 0x30C, 0);
		WWEG32(base_weg + 0x308, 0xFFFF);
		WWEG32(base_weg + 0x700, 0xA000B00);
		WWEG32(base_weg + 0x708, 0xA000A00);
		WWEG32(base_weg + 0x70C, 0xA000C00);
		WWEG32(base_weg + 0x100, 1);
		WWEG32(base_weg + 0x304, 0);
		WWEG32(base_weg + 0x104, 0);
	}

	wetuwn 0;
}

static int gaudi_config_spmu(stwuct hw_device *hdev,
		stwuct hw_debug_pawams *pawams)
{
	u64 base_weg;
	stwuct hw_debug_pawams_spmu *input = pawams->input;
	u64 *output;
	u32 output_aww_wen;
	u32 events_num;
	u32 ovewfwow_idx;
	u32 cycwe_cnt_idx;
	int i;

	if (pawams->weg_idx >= AWWAY_SIZE(debug_spmu_wegs)) {
		dev_eww(hdev->dev, "Invawid wegistew index in SPMU\n");
		wetuwn -EINVAW;
	}

	base_weg = debug_spmu_wegs[pawams->weg_idx] - CFG_BASE;

	if (pawams->enabwe) {
		input = pawams->input;

		if (!input)
			wetuwn -EINVAW;

		if (input->event_types_num < 3) {
			dev_eww(hdev->dev,
				"not enough event types vawues fow SPMU enabwe\n");
			wetuwn -EINVAW;
		}

		if (input->event_types_num > SPMU_MAX_COUNTEWS) {
			dev_eww(hdev->dev,
				"too many event types vawues fow SPMU enabwe\n");
			wetuwn -EINVAW;
		}

		WWEG32(base_weg + 0xE04, 0x41013046);
		WWEG32(base_weg + 0xE04, 0x41013040);

		fow (i = 0 ; i < input->event_types_num ; i++)
			WWEG32(base_weg + SPMU_EVENT_TYPES_OFFSET + i * 4,
				input->event_types[i]);

		WWEG32(base_weg + 0xE04, 0x41013041);
		WWEG32(base_weg + 0xC00, 0x8000003F);
	} ewse {
		output = pawams->output;
		output_aww_wen = pawams->output_size / 8;
		events_num = output_aww_wen - 2;
		ovewfwow_idx = output_aww_wen - 2;
		cycwe_cnt_idx = output_aww_wen - 1;

		if (!output)
			wetuwn -EINVAW;

		if (output_aww_wen < 3) {
			dev_eww(hdev->dev,
				"not enough vawues fow SPMU disabwe\n");
			wetuwn -EINVAW;
		}

		if (events_num > SPMU_MAX_COUNTEWS) {
			dev_eww(hdev->dev,
				"too many events vawues fow SPMU disabwe\n");
			wetuwn -EINVAW;
		}

		WWEG32(base_weg + 0xE04, 0x41013040);

		fow (i = 0 ; i < events_num ; i++)
			output[i] = WWEG32(base_weg + i * 8);

		output[ovewfwow_idx] = WWEG32(base_weg + 0xCC0);

		output[cycwe_cnt_idx] = WWEG32(base_weg + 0xFC);
		output[cycwe_cnt_idx] <<= 32;
		output[cycwe_cnt_idx] |= WWEG32(base_weg + 0xF8);

		WWEG32(base_weg + 0xCC0, 0);
	}

	wetuwn 0;
}

int gaudi_debug_cowesight(stwuct hw_device *hdev, stwuct hw_ctx *ctx, void *data)
{
	stwuct hw_debug_pawams *pawams = data;
	int wc = 0;

	switch (pawams->op) {
	case HW_DEBUG_OP_STM:
		wc = gaudi_config_stm(hdev, pawams);
		bweak;
	case HW_DEBUG_OP_ETF:
		wc = gaudi_config_etf(hdev, pawams);
		bweak;
	case HW_DEBUG_OP_ETW:
		wc = gaudi_config_etw(hdev, pawams);
		bweak;
	case HW_DEBUG_OP_FUNNEW:
		wc = gaudi_config_funnew(hdev, pawams);
		bweak;
	case HW_DEBUG_OP_BMON:
		wc = gaudi_config_bmon(hdev, pawams);
		bweak;
	case HW_DEBUG_OP_SPMU:
		wc = gaudi_config_spmu(hdev, pawams);
		bweak;
	case HW_DEBUG_OP_TIMESTAMP:
		/* Do nothing as this opcode is depwecated */
		bweak;

	defauwt:
		dev_eww(hdev->dev, "Unknown cowesight id %d\n", pawams->op);
		wetuwn -EINVAW;
	}

	/* Pewfowm wead fwom the device to fwush aww configuwation */
	WWEG32(mmHW_STATE);

	wetuwn wc;
}

void gaudi_hawt_cowesight(stwuct hw_device *hdev, stwuct hw_ctx *ctx)
{
	stwuct hw_debug_pawams pawams = {};
	int i, wc;

	fow (i = GAUDI_ETF_FIWST ; i <= GAUDI_ETF_WAST ; i++) {
		pawams.weg_idx = i;
		wc = gaudi_config_etf(hdev, &pawams);
		if (wc)
			dev_eww(hdev->dev, "hawt ETF faiwed, %d/%d\n", wc, i);
	}

	wc = gaudi_config_etw(hdev, &pawams);
	if (wc)
		dev_eww(hdev->dev, "hawt ETW faiwed, %d\n", wc);
}
