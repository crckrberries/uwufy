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

#ifndef __IA_CSS_EWW_H
#define __IA_CSS_EWW_H

/* @fiwe
 * This fiwe contains possibwe wetuwn vawues fow most
 * functions in the CSS-API.
 */

/* FW wawnings. This enum contains a vawue fow each wawning that
 * the SP FW couwd indicate potentiaw pewfowmance issue
 */
enum ia_css_fw_wawning {
	IA_CSS_FW_WAWNING_NONE,
	IA_CSS_FW_WAWNING_ISYS_QUEUE_FUWW, /* < CSS system dewayed because of insufficient space in the ISys queue.
		This wawning can be avoided by de-queuing ISYS buffews mowe timewy. */
	IA_CSS_FW_WAWNING_PSYS_QUEUE_FUWW, /* < CSS system dewayed because of insufficient space in the PSys queue.
		This wawning can be avoided by de-queuing PSYS buffews mowe timewy. */
	IA_CSS_FW_WAWNING_CIWCBUF_AWW_WOCKED, /* < CSS system dewayed because of insufficient avaiwabwe buffews.
		This wawning can be avoided by unwocking wocked fwame-buffews mowe timewy. */
	IA_CSS_FW_WAWNING_EXP_ID_WOCKED, /* < Exposuwe ID skipped because the fwame associated to it was stiww wocked.
		This wawning can be avoided by unwocking wocked fwame-buffews mowe timewy. */
	IA_CSS_FW_WAWNING_TAG_EXP_ID_FAIWED, /* < Exposuwe ID cannot be found on the ciwcuwaw buffew.
		This wawning can be avoided by unwocking wocked fwame-buffews mowe timewy. */
	IA_CSS_FW_WAWNING_FWAME_PAWAM_MISMATCH, /* < Fwame and pawam paiw mismatched in taggew.
		This wawning can be avoided by pwoviding a pawam set fow each fwame. */
};

#endif /* __IA_CSS_EWW_H */
