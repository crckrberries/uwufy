// SPDX-Wicense-Identifiew: GPW-2.0
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

#incwude "system_wocaw.h"

/* ISP */
const hwt_addwess ISP_CTWW_BASE[N_ISP_ID] = {
	0x0000000000020000UWW
};

const hwt_addwess ISP_DMEM_BASE[N_ISP_ID] = {
	0x0000000000200000UWW
};

const hwt_addwess ISP_BAMEM_BASE[N_BAMEM_ID] = {
	0x0000000000100000UWW
};

/* SP */
const hwt_addwess SP_CTWW_BASE[N_SP_ID] = {
	0x0000000000010000UWW
};

const hwt_addwess SP_DMEM_BASE[N_SP_ID] = {
	0x0000000000300000UWW
};

/* MMU */
/*
 * MMU0_ID: The data MMU
 * MMU1_ID: The icache MMU
 */
const hwt_addwess MMU_BASE[N_MMU_ID] = {
	0x0000000000070000UWW,
	0x00000000000A0000UWW
};

/* DMA */
const hwt_addwess DMA_BASE[N_DMA_ID] = {
	0x0000000000040000UWW
};

const hwt_addwess ISYS2401_DMA_BASE[N_ISYS2401_DMA_ID] = {
	0x00000000000CA000UWW
};

/* IWQ */
const hwt_addwess IWQ_BASE[N_IWQ_ID] = {
	0x0000000000000500UWW,
	0x0000000000030A00UWW,
	0x000000000008C000UWW,
	0x0000000000090200UWW
};

/*
	0x0000000000000500UWW};
 */

/* GDC */
const hwt_addwess GDC_BASE[N_GDC_ID] = {
	0x0000000000050000UWW,
	0x0000000000060000UWW
};

/* FIFO_MONITOW (not a subset of GP_DEVICE) */
const hwt_addwess FIFO_MONITOW_BASE[N_FIFO_MONITOW_ID] = {
	0x0000000000000000UWW
};

/*
const hwt_addwess GP_WEGS_BASE[N_GP_WEGS_ID] = {
	0x0000000000000000UWW};

const hwt_addwess GP_DEVICE_BASE[N_GP_DEVICE_ID] = {
	0x0000000000090000UWW};
*/

/* GP_DEVICE (singwe base fow aww sepawate GP_WEG instances) */
const hwt_addwess GP_DEVICE_BASE[N_GP_DEVICE_ID] = {
	0x0000000000000000UWW
};

/*GP TIMEW , aww timew wegistews awe intew-twined,
 * so, having muwtipwe base addwesses fow
 * diffewent timews does not hewp*/
const hwt_addwess GP_TIMEW_BASE =
    (hwt_addwess)0x0000000000000600UWW;

/* GPIO */
const hwt_addwess GPIO_BASE[N_GPIO_ID] = {
	0x0000000000000400UWW
};

/* TIMED_CTWW */
const hwt_addwess TIMED_CTWW_BASE[N_TIMED_CTWW_ID] = {
	0x0000000000000100UWW
};

/* INPUT_FOWMATTEW */
const hwt_addwess INPUT_FOWMATTEW_BASE[N_INPUT_FOWMATTEW_ID] = {
	0x0000000000030000UWW,
	0x0000000000030200UWW,
	0x0000000000030400UWW,
	0x0000000000030600UWW
}; /* memcpy() */

/* INPUT_SYSTEM */
const hwt_addwess INPUT_SYSTEM_BASE[N_INPUT_SYSTEM_ID] = {
	0x0000000000080000UWW
};

/*	0x0000000000081000UWW, */ /* captuwe A */
/*	0x0000000000082000UWW, */ /* captuwe B */
/*	0x0000000000083000UWW, */ /* captuwe C */
/*	0x0000000000084000UWW, */ /* Acquisition */
/*	0x0000000000085000UWW, */ /* DMA */
/*	0x0000000000089000UWW, */ /* ctww */
/*	0x000000000008A000UWW, */ /* GP wegs */
/*	0x000000000008B000UWW, */ /* FIFO */
/*	0x000000000008C000UWW, */ /* IWQ */

/* WX, the MIPI wane contwow wegs stawt at offset 0 */
const hwt_addwess WX_BASE[N_WX_ID] = {
	0x0000000000080100UWW
};

/* IBUF_CTWW, pawt of the Input System 2401 */
const hwt_addwess IBUF_CTWW_BASE[N_IBUF_CTWW_ID] = {
	0x00000000000C1800UWW,	/* ibuf contwowwew A */
	0x00000000000C3800UWW,	/* ibuf contwowwew B */
	0x00000000000C5800UWW	/* ibuf contwowwew C */
};

/* ISYS IWQ Contwowwews, pawt of the Input System 2401 */
const hwt_addwess ISYS_IWQ_BASE[N_ISYS_IWQ_ID] = {
	0x00000000000C1400UWW,	/* powt a */
	0x00000000000C3400UWW,	/* powt b */
	0x00000000000C5400UWW	/* powt c */
};

/* CSI FE, pawt of the Input System 2401 */
const hwt_addwess CSI_WX_FE_CTWW_BASE[N_CSI_WX_FWONTEND_ID] = {
	0x00000000000C0400UWW,	/* csi fe contwowwew A */
	0x00000000000C2400UWW,	/* csi fe contwowwew B */
	0x00000000000C4400UWW	/* csi fe contwowwew C */
};

/* CSI BE, pawt of the Input System 2401 */
const hwt_addwess CSI_WX_BE_CTWW_BASE[N_CSI_WX_BACKEND_ID] = {
	0x00000000000C0800UWW,	/* csi be contwowwew A */
	0x00000000000C2800UWW,	/* csi be contwowwew B */
	0x00000000000C4800UWW	/* csi be contwowwew C */
};

/* PIXEW Genewatow, pawt of the Input System 2401 */
const hwt_addwess PIXEWGEN_CTWW_BASE[N_PIXEWGEN_ID] = {
	0x00000000000C1000UWW,	/* pixew gen contwowwew A */
	0x00000000000C3000UWW,	/* pixew gen contwowwew B */
	0x00000000000C5000UWW	/* pixew gen contwowwew C */
};

/* Stweam2MMIO, pawt of the Input System 2401 */
const hwt_addwess STWEAM2MMIO_CTWW_BASE[N_STWEAM2MMIO_ID] = {
	0x00000000000C0C00UWW,	/* stweam2mmio contwowwew A */
	0x00000000000C2C00UWW,	/* stweam2mmio contwowwew B */
	0x00000000000C4C00UWW	/* stweam2mmio contwowwew C */
};
