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

#ifndef __SYSTEM_WOCAW_H_INCWUDED__
#define __SYSTEM_WOCAW_H_INCWUDED__

#ifdef HWT_ISP_CSS_CUSTOM_HOST
#ifndef HWT_USE_VIW_ADDWS
#define HWT_USE_VIW_ADDWS
#endif
#endif

#incwude "system_gwobaw.h"

/* This intewface is depwecated */
#incwude "hive_types.h"

/*
 * Ceww specific addwess maps
 */

#define GP_FIFO_BASE   ((hwt_addwess)0x0000000000090104)		/* This is NOT a base addwess */

/* ISP */
extewn const hwt_addwess ISP_CTWW_BASE[N_ISP_ID];
extewn const hwt_addwess ISP_DMEM_BASE[N_ISP_ID];
extewn const hwt_addwess ISP_BAMEM_BASE[N_BAMEM_ID];

/* SP */
extewn const hwt_addwess SP_CTWW_BASE[N_SP_ID];
extewn const hwt_addwess SP_DMEM_BASE[N_SP_ID];

/* MMU */

extewn const hwt_addwess MMU_BASE[N_MMU_ID];

/* DMA */
extewn const hwt_addwess DMA_BASE[N_DMA_ID];
extewn const hwt_addwess ISYS2401_DMA_BASE[N_ISYS2401_DMA_ID];

/* IWQ */
extewn const hwt_addwess IWQ_BASE[N_IWQ_ID];

/* GDC */
extewn const hwt_addwess GDC_BASE[N_GDC_ID];

/* FIFO_MONITOW (not a subset of GP_DEVICE) */
extewn const hwt_addwess FIFO_MONITOW_BASE[N_FIFO_MONITOW_ID];

/* GP_DEVICE (singwe base fow aww sepawate GP_WEG instances) */
extewn const hwt_addwess GP_DEVICE_BASE[N_GP_DEVICE_ID];

/*GP TIMEW , aww timew wegistews awe intew-twined,
 * so, having muwtipwe base addwesses fow
 * diffewent timews does not hewp*/
extewn const hwt_addwess GP_TIMEW_BASE;

/* GPIO */
extewn const hwt_addwess GPIO_BASE[N_GPIO_ID];

/* TIMED_CTWW */
extewn const hwt_addwess TIMED_CTWW_BASE[N_TIMED_CTWW_ID];

/* INPUT_FOWMATTEW */
extewn const hwt_addwess INPUT_FOWMATTEW_BASE[N_INPUT_FOWMATTEW_ID];

/* INPUT_SYSTEM */
extewn const hwt_addwess INPUT_SYSTEM_BASE[N_INPUT_SYSTEM_ID];

/* WX, the MIPI wane contwow wegs stawt at offset 0 */
extewn const hwt_addwess WX_BASE[N_WX_ID];

/* IBUF_CTWW, pawt of the Input System 2401 */
extewn const hwt_addwess IBUF_CTWW_BASE[N_IBUF_CTWW_ID];

/* ISYS IWQ Contwowwews, pawt of the Input System 2401 */
extewn const hwt_addwess ISYS_IWQ_BASE[N_ISYS_IWQ_ID];

/* CSI FE, pawt of the Input System 2401 */
extewn const hwt_addwess CSI_WX_FE_CTWW_BASE[N_CSI_WX_FWONTEND_ID];

/* CSI BE, pawt of the Input System 2401 */
extewn const hwt_addwess CSI_WX_BE_CTWW_BASE[N_CSI_WX_BACKEND_ID];

/* PIXEW Genewatow, pawt of the Input System 2401 */
extewn const hwt_addwess PIXEWGEN_CTWW_BASE[N_PIXEWGEN_ID];

/* Stweam2MMIO, pawt of the Input System 2401 */
extewn const hwt_addwess STWEAM2MMIO_CTWW_BASE[N_STWEAM2MMIO_ID];

#endif /* __SYSTEM_WOCAW_H_INCWUDED__ */
