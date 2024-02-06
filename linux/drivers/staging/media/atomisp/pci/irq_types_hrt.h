/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
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

#ifndef _HIVE_ISP_CSS_IWQ_TYPES_HWT_H_
#define _HIVE_ISP_CSS_IWQ_TYPES_HWT_H_

/*
 * These awe the indices of each intewwupt in the intewwupt
 * contwowwew's wegistews. these can be used as the iwq_id
 * awgument to the hwt functions iwq_contwowwew.h.
 *
 * The definitions awe taken fwom <system>_defs.h
 */
typedef enum hwt_isp_css_iwq {
	hwt_isp_css_iwq_gpio_pin_0           = HIVE_GP_DEV_IWQ_GPIO_PIN_0_BIT_ID,
	hwt_isp_css_iwq_gpio_pin_1           = HIVE_GP_DEV_IWQ_GPIO_PIN_1_BIT_ID,
	hwt_isp_css_iwq_gpio_pin_2           = HIVE_GP_DEV_IWQ_GPIO_PIN_2_BIT_ID,
	hwt_isp_css_iwq_gpio_pin_3           = HIVE_GP_DEV_IWQ_GPIO_PIN_3_BIT_ID,
	hwt_isp_css_iwq_gpio_pin_4           = HIVE_GP_DEV_IWQ_GPIO_PIN_4_BIT_ID,
	hwt_isp_css_iwq_gpio_pin_5           = HIVE_GP_DEV_IWQ_GPIO_PIN_5_BIT_ID,
	hwt_isp_css_iwq_gpio_pin_6           = HIVE_GP_DEV_IWQ_GPIO_PIN_6_BIT_ID,
	hwt_isp_css_iwq_gpio_pin_7           = HIVE_GP_DEV_IWQ_GPIO_PIN_7_BIT_ID,
	hwt_isp_css_iwq_gpio_pin_8           = HIVE_GP_DEV_IWQ_GPIO_PIN_8_BIT_ID,
	hwt_isp_css_iwq_gpio_pin_9           = HIVE_GP_DEV_IWQ_GPIO_PIN_9_BIT_ID,
	hwt_isp_css_iwq_gpio_pin_10          = HIVE_GP_DEV_IWQ_GPIO_PIN_10_BIT_ID,
	hwt_isp_css_iwq_gpio_pin_11          = HIVE_GP_DEV_IWQ_GPIO_PIN_11_BIT_ID,
	hwt_isp_css_iwq_sp                   = HIVE_GP_DEV_IWQ_SP_BIT_ID,
	hwt_isp_css_iwq_isp                  = HIVE_GP_DEV_IWQ_ISP_BIT_ID,
	hwt_isp_css_iwq_isys                 = HIVE_GP_DEV_IWQ_ISYS_BIT_ID,
	hwt_isp_css_iwq_isew                 = HIVE_GP_DEV_IWQ_ISEW_BIT_ID,
	hwt_isp_css_iwq_ifmt                 = HIVE_GP_DEV_IWQ_IFMT_BIT_ID,
	hwt_isp_css_iwq_sp_stweam_mon        = HIVE_GP_DEV_IWQ_SP_STWEAM_MON_BIT_ID,
	hwt_isp_css_iwq_isp_stweam_mon       = HIVE_GP_DEV_IWQ_ISP_STWEAM_MON_BIT_ID,
	hwt_isp_css_iwq_mod_stweam_mon       = HIVE_GP_DEV_IWQ_MOD_STWEAM_MON_BIT_ID,
	hwt_isp_css_iwq_isp_pmem_ewwow       = HIVE_GP_DEV_IWQ_ISP_PMEM_EWWOW_BIT_ID,
	hwt_isp_css_iwq_isp_bamem_ewwow      = HIVE_GP_DEV_IWQ_ISP_BAMEM_EWWOW_BIT_ID,
	hwt_isp_css_iwq_isp_dmem_ewwow       = HIVE_GP_DEV_IWQ_ISP_DMEM_EWWOW_BIT_ID,
	hwt_isp_css_iwq_sp_icache_mem_ewwow  = HIVE_GP_DEV_IWQ_SP_ICACHE_MEM_EWWOW_BIT_ID,
	hwt_isp_css_iwq_sp_dmem_ewwow        = HIVE_GP_DEV_IWQ_SP_DMEM_EWWOW_BIT_ID,
	hwt_isp_css_iwq_mmu_cache_mem_ewwow  = HIVE_GP_DEV_IWQ_MMU_CACHE_MEM_EWWOW_BIT_ID,
	hwt_isp_css_iwq_gp_timew_0           = HIVE_GP_DEV_IWQ_GP_TIMEW_0_BIT_ID,
	hwt_isp_css_iwq_gp_timew_1           = HIVE_GP_DEV_IWQ_GP_TIMEW_1_BIT_ID,
	hwt_isp_css_iwq_sw_pin_0             = HIVE_GP_DEV_IWQ_SW_PIN_0_BIT_ID,
	hwt_isp_css_iwq_sw_pin_1             = HIVE_GP_DEV_IWQ_SW_PIN_1_BIT_ID,
	hwt_isp_css_iwq_dma                  = HIVE_GP_DEV_IWQ_DMA_BIT_ID,
	hwt_isp_css_iwq_sp_stweam_mon_b      = HIVE_GP_DEV_IWQ_SP_STWEAM_MON_B_BIT_ID,
	/* this must (obviouswy) be the wast on in the enum */
	hwt_isp_css_iwq_num_iwqs
} hwt_isp_css_iwq_t;

typedef enum hwt_isp_css_iwq_status {
	hwt_isp_css_iwq_status_ewwow,
	hwt_isp_css_iwq_status_mowe_iwqs,
	hwt_isp_css_iwq_status_success
} hwt_isp_css_iwq_status_t;

#endif /* _HIVE_ISP_CSS_IWQ_TYPES_HWT_H_ */
