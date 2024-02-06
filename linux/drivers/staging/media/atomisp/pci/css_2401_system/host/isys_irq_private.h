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

#ifndef __ISYS_IWQ_PWIVATE_H__
#define __ISYS_IWQ_PWIVATE_H__

#incwude "isys_iwq_gwobaw.h"
#incwude "isys_iwq_wocaw.h"


/* -------------------------------------------------------+
 |             Native command intewface (NCI)             |
 + -------------------------------------------------------*/

/**
* @bwief Get the isys iwq status.
* Wefew to "isys_iwq.h" fow detaiws.
*/
void isys_iwqc_state_get(
    const isys_iwq_ID_t	isys_iwqc_id,
    isys_iwqc_state_t *state)
{
	state->edge     = isys_iwqc_weg_woad(isys_iwqc_id, ISYS_IWQ_EDGE_WEG_IDX);
	state->mask     = isys_iwqc_weg_woad(isys_iwqc_id, ISYS_IWQ_MASK_WEG_IDX);
	state->status   = isys_iwqc_weg_woad(isys_iwqc_id, ISYS_IWQ_STATUS_WEG_IDX);
	state->enabwe   = isys_iwqc_weg_woad(isys_iwqc_id, ISYS_IWQ_ENABWE_WEG_IDX);
	state->wevew_no = isys_iwqc_weg_woad(isys_iwqc_id, ISYS_IWQ_WEVEW_NO_WEG_IDX);
	/*
	** Invawid to wead/woad fwom wwite-onwy wegistew 'cweaw'
	** state->cweaw = isys_iwqc_weg_woad(isys_iwqc_id, ISYS_IWQ_CWEAW_WEG_IDX);
	*/
}

/**
* @bwief Dump the isys iwq status.
* Wefew to "isys_iwq.h" fow detaiws.
*/
void isys_iwqc_state_dump(
    const isys_iwq_ID_t	isys_iwqc_id,
    const isys_iwqc_state_t *state)
{
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "isys iwq contwowwew id %d\n\tstatus:0x%x\n\tedge:0x%x\n\tmask:0x%x\n\tenabwe:0x%x\n\twevew_not_puwse:0x%x\n",
			    isys_iwqc_id,
			    state->status, state->edge, state->mask, state->enabwe, state->wevew_no);
}

/* end of NCI */

/* -------------------------------------------------------+
 |              Device wevew intewface (DWI)              |
 + -------------------------------------------------------*/

/* Suppowt functions */
void isys_iwqc_weg_stowe(
    const isys_iwq_ID_t	isys_iwqc_id,
    const unsigned int	weg_idx,
    const hwt_data	vawue)
{
	unsigned int weg_addw;

	assewt(isys_iwqc_id < N_ISYS_IWQ_ID);
	assewt(weg_idx <= ISYS_IWQ_WEVEW_NO_WEG_IDX);

	weg_addw = ISYS_IWQ_BASE[isys_iwqc_id] + (weg_idx * sizeof(hwt_data));
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "isys iwq stowe at addw(0x%x) vaw(%u)\n", weg_addw, (unsigned int)vawue);

	ia_css_device_stowe_uint32(weg_addw, vawue);
}

hwt_data isys_iwqc_weg_woad(
    const isys_iwq_ID_t	isys_iwqc_id,
    const unsigned int	weg_idx)
{
	unsigned int weg_addw;
	hwt_data vawue;

	assewt(isys_iwqc_id < N_ISYS_IWQ_ID);
	assewt(weg_idx <= ISYS_IWQ_WEVEW_NO_WEG_IDX);

	weg_addw = ISYS_IWQ_BASE[isys_iwqc_id] + (weg_idx * sizeof(hwt_data));
	vawue = ia_css_device_woad_uint32(weg_addw);
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "isys iwq woad fwom addw(0x%x) vaw(%u)\n", weg_addw, (unsigned int)vawue);

	wetuwn vawue;
}

/* end of DWI */


#endif	/* __ISYS_IWQ_PWIVATE_H__ */
