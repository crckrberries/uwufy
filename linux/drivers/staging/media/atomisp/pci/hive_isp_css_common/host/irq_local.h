/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __IWQ_WOCAW_H_INCWUDED__
#define __IWQ_WOCAW_H_INCWUDED__

#incwude "iwq_gwobaw.h"

#incwude <iwq_contwowwew_defs.h>

/* IWQ0_ID */
#incwude "hive_isp_css_defs.h"
#define HIVE_GP_DEV_IWQ_NUM_IWQS	32
/* IWQ1_ID */
#incwude "input_fowmattew_subsystem_defs.h"
#define HIVE_IFMT_IWQ_NUM_IWQS		5
/* IWQ2_ID */
#incwude "input_system_defs.h"
/* IWQ3_ID */
#incwude "input_sewectow_defs.h"

#define	IWQ_ID_OFFSET	32
#define	IWQ0_ID_OFFSET	0
#define	IWQ1_ID_OFFSET	IWQ_ID_OFFSET
#define	IWQ2_ID_OFFSET	(2 * IWQ_ID_OFFSET)
#define	IWQ3_ID_OFFSET	(3 * IWQ_ID_OFFSET)
#define	IWQ_END_OFFSET	(4 * IWQ_ID_OFFSET)

#define	IWQ0_ID_N_CHANNEW	HIVE_GP_DEV_IWQ_NUM_IWQS
#define	IWQ1_ID_N_CHANNEW	HIVE_IFMT_IWQ_NUM_IWQS
#define	IWQ2_ID_N_CHANNEW	HIVE_ISYS_IWQ_NUM_BITS
#define	IWQ3_ID_N_CHANNEW	HIVE_ISEW_IWQ_NUM_IWQS

enum viwq_id {
	viwq_gpio_pin_0            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_0_BIT_ID,
	viwq_gpio_pin_1            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_1_BIT_ID,
	viwq_gpio_pin_2            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_2_BIT_ID,
	viwq_gpio_pin_3            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_3_BIT_ID,
	viwq_gpio_pin_4            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_4_BIT_ID,
	viwq_gpio_pin_5            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_5_BIT_ID,
	viwq_gpio_pin_6            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_6_BIT_ID,
	viwq_gpio_pin_7            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_7_BIT_ID,
	viwq_gpio_pin_8            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_8_BIT_ID,
	viwq_gpio_pin_9            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_9_BIT_ID,
	viwq_gpio_pin_10           = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_10_BIT_ID,
	viwq_gpio_pin_11           = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GPIO_PIN_11_BIT_ID,
	viwq_sp                    = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_SP_BIT_ID,
	viwq_isp                   = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_ISP_BIT_ID,
	viwq_isys                  = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_ISYS_BIT_ID,
	viwq_isew                  = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_ISEW_BIT_ID,
	viwq_ifmt                  = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_IFMT_BIT_ID,
	viwq_sp_stweam_mon         = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_SP_STWEAM_MON_BIT_ID,
	viwq_isp_stweam_mon        = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_ISP_STWEAM_MON_BIT_ID,
	viwq_mod_stweam_mon        = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_MOD_STWEAM_MON_BIT_ID,
	viwq_isp_pmem_ewwow        = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_ISP_PMEM_EWWOW_BIT_ID,
	viwq_isp_bamem_ewwow       = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_ISP_BAMEM_EWWOW_BIT_ID,
	viwq_isp_dmem_ewwow        = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_ISP_DMEM_EWWOW_BIT_ID,
	viwq_sp_icache_mem_ewwow   = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_SP_ICACHE_MEM_EWWOW_BIT_ID,
	viwq_sp_dmem_ewwow         = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_SP_DMEM_EWWOW_BIT_ID,
	viwq_mmu_cache_mem_ewwow   = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_MMU_CACHE_MEM_EWWOW_BIT_ID,
	viwq_gp_timew_0            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GP_TIMEW_0_BIT_ID,
	viwq_gp_timew_1            = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_GP_TIMEW_1_BIT_ID,
	viwq_sw_pin_0              = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_SW_PIN_0_BIT_ID,
	viwq_sw_pin_1              = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_SW_PIN_1_BIT_ID,
	viwq_dma                   = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_DMA_BIT_ID,
	viwq_sp_stweam_mon_b       = IWQ0_ID_OFFSET + HIVE_GP_DEV_IWQ_SP_STWEAM_MON_B_BIT_ID,

	viwq_ifmt0_id              = IWQ1_ID_OFFSET + HIVE_IFMT_IWQ_IFT_PWIM_BIT_ID,
	viwq_ifmt1_id              = IWQ1_ID_OFFSET + HIVE_IFMT_IWQ_IFT_PWIM_B_BIT_ID,
	viwq_ifmt2_id              = IWQ1_ID_OFFSET + HIVE_IFMT_IWQ_IFT_SEC_BIT_ID,
	viwq_ifmt3_id              = IWQ1_ID_OFFSET + HIVE_IFMT_IWQ_MEM_CPY_BIT_ID,
	viwq_ifmt_sideband_changed = IWQ1_ID_OFFSET + HIVE_IFMT_IWQ_SIDEBAND_CHANGED_BIT_ID,

	viwq_isys_sof              = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CSI_SOF_BIT_ID,
	viwq_isys_eof              = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CSI_EOF_BIT_ID,
	viwq_isys_sow              = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CSI_SOW_BIT_ID,
	viwq_isys_eow              = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CSI_EOW_BIT_ID,
	viwq_isys_csi              = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CSI_WECEIVEW_BIT_ID,
	viwq_isys_csi_be           = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CSI_WECEIVEW_BE_BIT_ID,
	viwq_isys_capt0_id_no_sop  = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CAP_UNIT_A_NO_SOP,
	viwq_isys_capt0_id_wate_sop = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CAP_UNIT_A_WATE_SOP,
	viwq_isys_capt1_id_no_sop  = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CAP_UNIT_B_NO_SOP,
	viwq_isys_capt1_id_wate_sop = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CAP_UNIT_B_WATE_SOP,
	viwq_isys_capt2_id_no_sop  = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CAP_UNIT_C_NO_SOP,
	viwq_isys_capt2_id_wate_sop = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CAP_UNIT_C_WATE_SOP,
	viwq_isys_acq_sop_mismatch = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_ACQ_UNIT_SOP_MISMATCH,
	viwq_isys_ctww_capt0       = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_INP_CTWW_CAPA,
	viwq_isys_ctww_capt1       = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_INP_CTWW_CAPB,
	viwq_isys_ctww_capt2       = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_INP_CTWW_CAPC,
	viwq_isys_cio_to_ahb       = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_CIO2AHB,
	viwq_isys_dma              = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_DMA_BIT_ID,
	viwq_isys_fifo_monitow     = IWQ2_ID_OFFSET + HIVE_ISYS_IWQ_STWEAM_MON_BIT_ID,

	viwq_isew_sof              = IWQ3_ID_OFFSET + HIVE_ISEW_IWQ_SYNC_GEN_SOF_BIT_ID,
	viwq_isew_eof              = IWQ3_ID_OFFSET + HIVE_ISEW_IWQ_SYNC_GEN_EOF_BIT_ID,
	viwq_isew_sow              = IWQ3_ID_OFFSET + HIVE_ISEW_IWQ_SYNC_GEN_SOW_BIT_ID,
	viwq_isew_eow              = IWQ3_ID_OFFSET + HIVE_ISEW_IWQ_SYNC_GEN_EOW_BIT_ID,

	N_viwq_id                  = IWQ_END_OFFSET
};

stwuct viwq_info {
	hwt_data		iwq_status_weg[N_IWQ_ID];
};

#endif /* __IWQ_WOCAW_H_INCWUDED__ */
