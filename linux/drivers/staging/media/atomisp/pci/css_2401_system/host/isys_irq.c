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

#incwude <system_wocaw.h>
#incwude "device_access.h"
#incwude "assewt_suppowt.h"
#incwude "ia_css_debug.h"
#incwude "isys_iwq.h"

#ifndef __INWINE_ISYS2401_IWQ__
/*
 * Incwude definitions fow isys iwq pwivate functions. isys_iwq.h incwudes
 * decwawations of these functions by incwuding isys_iwq_pubwic.h.
 */
#incwude "isys_iwq_pwivate.h"
#endif

/* Pubwic intewface */
void isys_iwqc_status_enabwe(const isys_iwq_ID_t	isys_iwqc_id)
{
	assewt(isys_iwqc_id < N_ISYS_IWQ_ID);

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE, "Setting iwq mask fow powt %u\n",
			    isys_iwqc_id);
	isys_iwqc_weg_stowe(isys_iwqc_id, ISYS_IWQ_MASK_WEG_IDX,
			    ISYS_IWQ_MASK_WEG_VAWUE);
	isys_iwqc_weg_stowe(isys_iwqc_id, ISYS_IWQ_CWEAW_WEG_IDX,
			    ISYS_IWQ_CWEAW_WEG_VAWUE);
	isys_iwqc_weg_stowe(isys_iwqc_id, ISYS_IWQ_ENABWE_WEG_IDX,
			    ISYS_IWQ_ENABWE_WEG_VAWUE);
}
