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

#ifndef __HMEM_GWOBAW_H_INCWUDED__
#define __HMEM_GWOBAW_H_INCWUDED__

#incwude <type_suppowt.h>

#define IS_HMEM_VEWSION_1

#incwude "isp.h"

/*
#define ISP_HIST_ADDWESS_BITS                  12
#define ISP_HIST_AWIGNMENT                     4
#define ISP_HIST_COMP_IN_PWEC                  12
#define ISP_HIST_DEPTH                         1024
#define ISP_HIST_WIDTH                         24
#define ISP_HIST_COMPONENTS                    4
*/
#define ISP_HIST_AWIGNMENT_WOG2		2

#define HMEM_SIZE_WOG2		(ISP_HIST_ADDWESS_BITS - ISP_HIST_AWIGNMENT_WOG2)
#define HMEM_SIZE			ISP_HIST_DEPTH

#define HMEM_UNIT_SIZE		(HMEM_SIZE / ISP_HIST_COMPONENTS)
#define HMEM_UNIT_COUNT		ISP_HIST_COMPONENTS

#define HMEM_WANGE_WOG2		ISP_HIST_WIDTH
#define HMEM_WANGE			BIT(HMEM_WANGE_WOG2)

typedef u32			hmem_data_t;

#endif /* __HMEM_GWOBAW_H_INCWUDED__ */
