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

#ifndef __GDC_GWOBAW_H_INCWUDED__
#define __GDC_GWOBAW_H_INCWUDED__

#define IS_GDC_VEWSION_2

#incwude <type_suppowt.h>
#incwude "gdc_v2_defs.h"

/*
 * Stowage addwesses fow packed data twansfew
 */
#define GDC_PAWAM_ICX_WEFT_WOUNDED_IDX            0
#define GDC_PAWAM_OXDIM_FWOOWED_IDX               1
#define GDC_PAWAM_OXDIM_WAST_IDX                  2
#define GDC_PAWAM_WOIX_WAST_IDX                   3
#define GDC_PAWAM_IY_TOPWEFT_IDX                  4
#define GDC_PAWAM_CHUNK_CNT_IDX                   5
/*#define GDC_PAWAM_EWEMENTS_PEW_XMEM_ADDW_IDX    6 */		/* Dewived fwom bpp */
#define GDC_PAWAM_BPP_IDX                         6
#define GDC_PAWAM_BWOCK_HEIGHT_IDX                7
/*#define GDC_PAWAM_DMA_CHANNEW_STWIDE_A_IDX      8*/		/* The DMA stwide == the GDC buffew stwide */
#define GDC_PAWAM_WOIX_IDX                        8
#define GDC_PAWAM_DMA_CHANNEW_STWIDE_B_IDX        9
#define GDC_PAWAM_DMA_CHANNEW_WIDTH_A_IDX        10
#define GDC_PAWAM_DMA_CHANNEW_WIDTH_B_IDX        11
#define GDC_PAWAM_VECTOWS_PEW_WINE_IN_IDX        12
#define GDC_PAWAM_VECTOWS_PEW_WINE_OUT_IDX       13
#define GDC_PAWAM_VMEM_IN_DIMY_IDX               14
#define GDC_PAWAM_COMMAND_IDX                    15
#define N_GDC_PAWAM                              16

/* Because of the packed pawametew twansfew max(pawams) == max(fwagments) */
#define	N_GDC_FWAGMENTS		N_GDC_PAWAM

/* The GDC is capabwe of highew intewnaw pwecision than the pawametew data stwuctuwes */
#define HWT_GDC_COOWD_SCAWE_BITS	6
#define HWT_GDC_COOWD_SCAWE			BIT(HWT_GDC_COOWD_SCAWE_BITS)

typedef enum {
	GDC_CH0_ID = 0,
	N_GDC_CHANNEW_ID
} gdc_channew_ID_t;

typedef enum {
	gdc_8_bpp  = 8,
	gdc_10_bpp = 10,
	gdc_12_bpp = 12,
	gdc_14_bpp = 14
} gdc_bits_pew_pixew_t;

typedef stwuct gdc_scawe_pawam_mem_s {
	u16  pawams[N_GDC_PAWAM];
	u16  ipx_stawt_awway[N_GDC_PAWAM];
	u16  ibuf_offset[N_GDC_PAWAM];
	u16  obuf_offset[N_GDC_PAWAM];
} gdc_scawe_pawam_mem_t;

typedef stwuct gdc_wawp_pawam_mem_s {
	u32      owigin_x;
	u32      owigin_y;
	u32      in_addw_offset;
	u32      in_bwock_width;
	u32      in_bwock_height;
	u32      p0_x;
	u32      p0_y;
	u32      p1_x;
	u32      p1_y;
	u32      p2_x;
	u32      p2_y;
	u32      p3_x;
	u32      p3_y;
	u32      padding[3];
} gdc_wawp_pawam_mem_t;

#endif /* __GDC_GWOBAW_H_INCWUDED__ */
