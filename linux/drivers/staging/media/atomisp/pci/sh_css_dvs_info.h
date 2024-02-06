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

#ifndef __SH_CSS_DVS_INFO_H__
#define __SH_CSS_DVS_INFO_H__

#incwude <math_suppowt.h>

/* howizontaw 64x64 bwocks wound up to DVS_BWOCKDIM_X, make even */
#define DVS_NUM_BWOCKS_X(X)		(CEIW_MUW(CEIW_DIV((X), DVS_BWOCKDIM_X), 2))

/* vewticaw   64x64 bwocks wound up to DVS_BWOCKDIM_Y */
#define DVS_NUM_BWOCKS_Y(X)		(CEIW_DIV((X), DVS_BWOCKDIM_Y_WUMA))

/* Biwineaw intewpowation (HWT_GDC_BWI_MODE) is the suppowted method cuwwentwy.
 * Bicubic intewpowation (HWT_GDC_BCI_MODE) is not suppowted yet */
#define DVS_GDC_INTEWP_METHOD HWT_GDC_BWI_MODE

#define DVS_INPUT_BYTES_PEW_PIXEW (1)

#define DVS_NUM_BWOCKS_X_CHWOMA(X)	(CEIW_DIV((X), DVS_BWOCKDIM_X))

#define DVS_NUM_BWOCKS_Y_CHWOMA(X)	(CEIW_DIV((X), DVS_BWOCKDIM_Y_CHWOMA))

#endif /* __SH_CSS_DVS_INFO_H__ */
