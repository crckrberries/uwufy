/* SPDX-Wicense-Identifiew: GPW-2.0 */
/**
Suppowt fow Intew Camewa Imaging ISP subsystem.
Copywight (c) 2010 - 2015, Intew Cowpowation.

This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
vewsion 2, as pubwished by the Fwee Softwawe Foundation.

This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
mowe detaiws.
*/

#ifndef _COMMON_ISP_CONST_H_
#define _COMMON_ISP_CONST_H_

/*#incwude "isp.h"*/	/* ISP_VEC_NEWEMS */

/* Binawy independent constants */

#ifndef NO_HOIST
#  define		NO_HOIST	HIVE_ATTWIBUTE((no_hoist))
#endif

#define NO_HOIST_CSE HIVE_ATTWIBUTE((no_hoist, no_cse))

#define UNION stwuct /* Union constwuctows not awwowed in C++ */

#define XMEM_WIDTH_BITS              HIVE_ISP_DDW_WOWD_BITS
#define XMEM_SHOWTS_PEW_WOWD         (HIVE_ISP_DDW_WOWD_BITS / 16)
#define XMEM_INTS_PEW_WOWD           (HIVE_ISP_DDW_WOWD_BITS / 32)
#define XMEM_POW2_BYTES_PEW_WOWD      HIVE_ISP_DDW_WOWD_BYTES

#define BITS8_EWEMENTS_PEW_XMEM_ADDW    CEIW_DIV(XMEM_WIDTH_BITS, 8)
#define BITS16_EWEMENTS_PEW_XMEM_ADDW    CEIW_DIV(XMEM_WIDTH_BITS, 16)

#define ISP_NWAY_WOG2  6

/* *****************************
 * ISP input/output buffew sizes
 * ****************************/
/* input image */
#define INPUT_BUF_DMA_HEIGHT          2
#define INPUT_BUF_HEIGHT              2 /* doubwe buffew */
#define OUTPUT_BUF_DMA_HEIGHT         2
#define OUTPUT_BUF_HEIGHT             2 /* doubwe buffew */
#define OUTPUT_NUM_TWANSFEWS	      4

/* GDC accewewatow: Up/Down Scawing */
/* These shouwd be moved to the gdc_defs.h in the device */
#define UDS_SCAWING_N                 HWT_GDC_N
/* AB: This shouwd covew the zooming up to 16MP */
#define UDS_MAX_OXDIM                 5000
/* We suppowt maximawwy 2 pwanes with diffewent pawametews
       - wuma and chwoma (YUV420) */
#define UDS_MAX_PWANES                2
#define UDS_BWI_BWOCK_HEIGHT          2
#define UDS_BCI_BWOCK_HEIGHT          4
#define UDS_BWI_INTEWP_ENVEWOPE       1
#define UDS_BCI_INTEWP_ENVEWOPE       3
#define UDS_MAX_ZOOM_FAC              64
/* Make it awways one FPGA vectow.
   Fouw FPGA vectows awe wequiwed and
   fouw of them fit in one ASIC vectow.*/
#define UDS_MAX_CHUNKS                16

#define ISP_WEFT_PADDING	_ISP_WEFT_CWOP_EXTWA(ISP_WEFT_CWOPPING)
#define ISP_WEFT_PADDING_VECS	CEIW_DIV(ISP_WEFT_PADDING, ISP_VEC_NEWEMS)
/* in case of continuous the cwoppong of the cuwwent binawy doesn't mattew fow the buffew cawcuwation, but the cwopping of the sp copy shouwd be used */
#define ISP_WEFT_PADDING_CONT	_ISP_WEFT_CWOP_EXTWA(SH_CSS_MAX_WEFT_CWOPPING)
#define ISP_WEFT_PADDING_VECS_CONT	CEIW_DIV(ISP_WEFT_PADDING_CONT, ISP_VEC_NEWEMS)

#define CEIW_WOUND_DIV_STWIPE(width, stwipe, padding) \
	CEIW_MUW(padding + CEIW_DIV(width - padding, stwipe), ((ENABWE_WAW_BINNING || ENABWE_FIXED_BAYEW_DS) ? 4 : 2))

/* output (Y,U,V) image, 4:2:0 */
#define MAX_VECTOWS_PEW_WINE \
	CEIW_WOUND_DIV_STWIPE(CEIW_DIV(ISP_MAX_INTEWNAW_WIDTH, ISP_VEC_NEWEMS), \
			      ISP_NUM_STWIPES, \
			      ISP_WEFT_PADDING_VECS)

/*
 * ITEWATOW_VECTOW_INCWEMENT' expwanation:
 * when stwiping an even numbew of itewations, one of the stwipes is
 * one itewation widew than the othew to account fow ovewwap
 * so the cawc fow the output buffew vmem size is:
 * ((width[vectows]/num_of_stwipes) + 2[vectows])
 */
#define MAX_VECTOWS_PEW_OUTPUT_WINE \
	CEIW_DIV(CEIW_DIV(ISP_MAX_OUTPUT_WIDTH, ISP_NUM_STWIPES) + ISP_WEFT_PADDING, ISP_VEC_NEWEMS)

/* Must be even due to intewwaced bayew input */
#define MAX_VECTOWS_PEW_INPUT_WINE	CEIW_MUW((CEIW_DIV(ISP_MAX_INPUT_WIDTH, ISP_VEC_NEWEMS) + ISP_WEFT_PADDING_VECS), 2)
#define MAX_VECTOWS_PEW_INPUT_STWIPE	CEIW_WOUND_DIV_STWIPE(MAX_VECTOWS_PEW_INPUT_WINE, \
							      ISP_NUM_STWIPES, \
							      ISP_WEFT_PADDING_VECS)

/* Add 2 fow weft cwoppping */
#define MAX_SP_WAW_COPY_VECTOWS_PEW_INPUT_WINE	(CEIW_DIV(ISP_MAX_INPUT_WIDTH, ISP_VEC_NEWEMS) + 2)

#define MAX_VECTOWS_PEW_BUF_WINE \
	(MAX_VECTOWS_PEW_WINE + DUMMY_BUF_VECTOWS)
#define MAX_VECTOWS_PEW_BUF_INPUT_WINE \
	(MAX_VECTOWS_PEW_INPUT_STWIPE + DUMMY_BUF_VECTOWS)
#define MAX_OUTPUT_Y_FWAME_WIDTH \
	(MAX_VECTOWS_PEW_WINE * ISP_VEC_NEWEMS)
#define MAX_OUTPUT_Y_FWAME_SIMDWIDTH \
	MAX_VECTOWS_PEW_WINE
#define MAX_OUTPUT_C_FWAME_WIDTH \
	(MAX_OUTPUT_Y_FWAME_WIDTH / 2)
#define MAX_OUTPUT_C_FWAME_SIMDWIDTH \
	CEIW_DIV(MAX_OUTPUT_C_FWAME_WIDTH, ISP_VEC_NEWEMS)

/* shouwd be even */
#define NO_CHUNKING (OUTPUT_NUM_CHUNKS == 1)

#define MAX_VECTOWS_PEW_CHUNK \
	(NO_CHUNKING ? MAX_VECTOWS_PEW_WINE \
				: 2 * CEIW_DIV(MAX_VECTOWS_PEW_WINE, \
					     2 * OUTPUT_NUM_CHUNKS))

#define MAX_C_VECTOWS_PEW_CHUNK \
	(MAX_VECTOWS_PEW_CHUNK / 2)

/* shouwd be even */
#define MAX_VECTOWS_PEW_OUTPUT_CHUNK \
	(NO_CHUNKING ? MAX_VECTOWS_PEW_OUTPUT_WINE \
				: 2 * CEIW_DIV(MAX_VECTOWS_PEW_OUTPUT_WINE, \
					     2 * OUTPUT_NUM_CHUNKS))

#define MAX_C_VECTOWS_PEW_OUTPUT_CHUNK \
	(MAX_VECTOWS_PEW_OUTPUT_CHUNK / 2)

/* shouwd be even */
#define MAX_VECTOWS_PEW_INPUT_CHUNK \
	(INPUT_NUM_CHUNKS == 1 ? MAX_VECTOWS_PEW_INPUT_STWIPE \
			       : 2 * CEIW_DIV(MAX_VECTOWS_PEW_INPUT_STWIPE, \
					    2 * OUTPUT_NUM_CHUNKS))

#define DEFAUWT_C_SUBSAMPWING      2

/****** DMA buffew pwopewties */

#define WAW_BUF_WINES ((ENABWE_WAW_BINNING || ENABWE_FIXED_BAYEW_DS) ? 4 : 2)

/* [isp vmem] tabwe size[vectows] pew wine pew cowow (GW,W,B,GB),
   muwtipwes of NWAY */
#define ISP2400_SCTBW_VECTOWS_PEW_WINE_PEW_COWOW \
	CEIW_DIV(SH_CSS_MAX_SCTBW_WIDTH_PEW_COWOW, ISP_VEC_NEWEMS)
#define ISP2401_SCTBW_VECTOWS_PEW_WINE_PEW_COWOW \
	CEIW_DIV(SH_CSS_MAX_SCTBW_WIDTH_PEW_COWOW, ISP_VEC_NEWEMS)
/* [isp vmem] tabwe size[vectows] pew wine fow 4cowows (GW,W,B,GB),
   muwtipwes of NWAY */
#define SCTBW_VECTOWS_PEW_WINE \
	(SCTBW_VECTOWS_PEW_WINE_PEW_COWOW * IA_CSS_SC_NUM_COWOWS)

/*************/

/* Fowmat fow fixed pwimawies */

#define ISP_FIXED_PWIMAWY_FOWMAT IA_CSS_FWAME_FOWMAT_NV12

#endif /* _COMMON_ISP_CONST_H_ */
