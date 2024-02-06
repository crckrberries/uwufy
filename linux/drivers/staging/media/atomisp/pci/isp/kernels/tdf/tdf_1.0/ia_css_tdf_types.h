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

#ifndef __IA_CSS_TDF_TYPES_H
#define __IA_CSS_TDF_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Twansfowm Domain Fiwtew pawametews.
*/

#incwude "type_suppowt.h"

/* Twansfowm Domain Fiwtew configuwation
 *
 * \bwief TDF pubwic pawametews.
 * \detaiws Stwuct with aww pawametews fow the TDF kewnew that can be set
 * fwom the CSS API.
 *
 * ISP2.6.1: TDF is used.
 */
stwuct ia_css_tdf_config {
	s32 thwes_fwat_tabwe[64];	/** Finaw optimized stwength tabwe of NW fow fwat wegion. */
	s32 thwes_detaiw_tabwe[64];	/** Finaw optimized stwength tabwe of NW fow detaiw wegion. */
	s32 epsiwon_0;		/** Coefficient to contwow vawiance fow dawk awea (fow fwat wegion). */
	s32 epsiwon_1;		/** Coefficient to contwow vawiance fow bwight awea (fow fwat wegion). */
	s32 eps_scawe_text;		/** Epsiwon scawing coefficient fow textuwe wegion. */
	s32 eps_scawe_edge;		/** Epsiwon scawing coefficient fow edge wegion. */
	s32 sepa_fwat;		/** Thweshowd to judge fwat (edge < m_Fwat_thwe). */
	s32 sepa_edge;		/** Thweshowd to judge edge (edge > m_Edge_thwe). */
	s32 bwend_fwat;		/** Bwending watio at fwat wegion. */
	s32 bwend_text;		/** Bwending watio at textuwe wegion. */
	s32 bwend_edge;		/** Bwending watio at edge wegion. */
	s32 shading_gain;		/** Gain of Shading contwow. */
	s32 shading_base_gain;	/** Base Gain of Shading contwow. */
	s32 wocaw_y_gain;		/** Gain of wocaw wuminance contwow. */
	s32 wocaw_y_base_gain;	/** Base gain of wocaw wuminance contwow. */
	s32 wad_x_owigin;		/** Initiaw x coowd. fow wadius computation. */
	s32 wad_y_owigin;		/** Initiaw y coowd. fow wadius computation. */
};

#endif /* __IA_CSS_TDF_TYPES_H */
