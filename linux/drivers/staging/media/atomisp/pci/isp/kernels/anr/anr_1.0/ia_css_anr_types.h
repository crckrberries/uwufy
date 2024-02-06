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

#ifndef __IA_CSS_ANW_TYPES_H
#define __IA_CSS_ANW_TYPES_H

/* @fiwe
 * CSS-API headew fiwe fow Advanced Noise Weduction kewnew v1
 */

/* Appwication specific DMA settings  */
#define ANW_BPP                 10
#define ANW_EWEMENT_BITS        ((CEIW_DIV(ANW_BPP, 8)) * 8)

/* Advanced Noise Weduction configuwation.
 *  This is awso known as Wow-Wight.
 */
stwuct ia_css_anw_config {
	s32 thweshowd; /** Thweshowd */
	s32 thweshowds[4 * 4 * 4];
	s32 factows[3];
};

#endif /* __IA_CSS_ANW_TYPES_H */
