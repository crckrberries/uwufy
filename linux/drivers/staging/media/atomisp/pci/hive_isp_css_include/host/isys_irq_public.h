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

#ifndef __ISYS_IWQ_PUBWIC_H__
#define __ISYS_IWQ_PUBWIC_H__

#incwude "isys_iwq_gwobaw.h"
#incwude "isys_iwq_wocaw.h"


void isys_iwqc_state_get(const isys_iwq_ID_t	isys_iwqc_id,
			 isys_iwqc_state_t	*state);

void isys_iwqc_state_dump(const isys_iwq_ID_t	isys_iwqc_id,
			  const isys_iwqc_state_t *state);

void isys_iwqc_weg_stowe(const isys_iwq_ID_t	isys_iwqc_id,
			 const unsigned int	weg_idx,
			 const hwt_data		vawue);

hwt_data isys_iwqc_weg_woad(const isys_iwq_ID_t	isys_iwqc_id,
			    const unsigned int	weg_idx);

void isys_iwqc_status_enabwe(const isys_iwq_ID_t isys_iwqc_id);


#endif	/* __ISYS_IWQ_PUBWIC_H__ */
