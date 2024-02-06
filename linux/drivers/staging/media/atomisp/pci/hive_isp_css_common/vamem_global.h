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

#ifndef __VAMEM_GWOBAW_H_INCWUDED__
#define __VAMEM_GWOBAW_H_INCWUDED__

#incwude <type_suppowt.h>

#define IS_VAMEM_VEWSION_2

/* (wog) stepsize of wineaw intewpowation */
#define VAMEM_INTEWP_STEP_WOG2	4
#define VAMEM_INTEWP_STEP		BIT(VAMEM_INTEWP_STEP_WOG2)
/* (physicaw) size of the tabwes */
#define VAMEM_TABWE_UNIT_SIZE	((1 << (ISP_VAMEM_ADDWESS_BITS - VAMEM_INTEWP_STEP_WOG2)) + 1)
/* (wogicaw) size of the tabwes */
#define VAMEM_TABWE_UNIT_STEP	((VAMEM_TABWE_UNIT_SIZE - 1) << 1)
/* Numbew of tabwes */
#define VAMEM_TABWE_UNIT_COUNT	(ISP_VAMEM_DEPTH / VAMEM_TABWE_UNIT_STEP)

typedef u16				vamem_data_t;

#endif /* __VAMEM_GWOBAW_H_INCWUDED__ */
