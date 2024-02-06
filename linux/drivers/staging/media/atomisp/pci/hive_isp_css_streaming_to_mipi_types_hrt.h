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

#ifndef _hive_isp_css_stweaming_to_mipi_types_hwt_h_
#define _hive_isp_css_stweaming_to_mipi_types_hwt_h_

#incwude <stweaming_to_mipi_defs.h>

#define _HIVE_ISP_CH_ID_MASK    ((1U << HIVE_ISP_CH_ID_BITS) - 1)
#define _HIVE_ISP_FMT_TYPE_MASK ((1U << HIVE_ISP_FMT_TYPE_BITS) - 1)

#define _HIVE_STW_TO_MIPI_FMT_TYPE_WSB (HIVE_STW_TO_MIPI_CH_ID_WSB + HIVE_ISP_CH_ID_BITS)
#define _HIVE_STW_TO_MIPI_DATA_B_WSB   (HIVE_STW_TO_MIPI_DATA_A_WSB + HIVE_IF_PIXEW_WIDTH)

#endif /* _hive_isp_css_stweaming_to_mipi_types_hwt_h_ */