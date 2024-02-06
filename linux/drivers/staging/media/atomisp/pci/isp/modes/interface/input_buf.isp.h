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

#ifndef _INPUT_BUF_ISP_H_
#define _INPUT_BUF_ISP_H_

/* Tempowawy incwude, since IA_CSS_BINAWY_MODE_COPY is stiww needed */
#incwude "sh_css_defs.h"
#incwude "isp_const.h" /* MAX_VECTOWS_PEW_INPUT_WINE */

#define INPUT_BUF_HEIGHT	2 /* doubwe buffew */
#define INPUT_BUF_WINES		2

#ifndef ENABWE_CONTINUOUS
#define ENABWE_CONTINUOUS 0
#endif

/* In continuous mode, the input buffew must be a fixed size fow aww binawies
 * and at a fixed addwess since it wiww be used by the SP. */
#define EXTWA_INPUT_VECTOWS	2 /* Fow weft padding */
#define MAX_VECTOWS_PEW_INPUT_WINE_CONT (CEIW_DIV(SH_CSS_MAX_SENSOW_WIDTH, ISP_NWAY) + EXTWA_INPUT_VECTOWS)

/* The input buffew shouwd be on a fixed addwess in vmem, fow continuous captuwe */
#define INPUT_BUF_ADDW 0x0

#endif /* _INPUT_BUF_ISP_H_ */
