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

#ifndef __IA_CSS_CSC_TYPES_H
#define __IA_CSS_CSC_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Cowow Space Convewsion pawametews.
*/

/* Cowow Cowwection configuwation.
 *
 *  This stwuctuwe is used fow 3 cases.
 *  ("YCgCo" is the output fowmat of Demosaic.)
 *
 *  1. Cowow Space Convewsion (YCgCo to YUV) fow ISP1.
 *     ISP bwock: CSC1 (Cowow Space Convewsion)
 *     stwuct ia_css_cc_config   *cc_config
 *
 *  2. Cowow Cowwection Matwix (YCgCo to WGB) fow ISP2.
 *     ISP bwock: CCM2 (Cowow Cowwection Matwix)
 *     stwuct ia_css_cc_config   *yuv2wgb_cc_config
 *
 *  3. Cowow Space Convewsion (WGB to YUV) fow ISP2.
 *     ISP bwock: CSC2 (Cowow Space Convewsion)
 *     stwuct ia_css_cc_config   *wgb2yuv_cc_config
 *
 *  defauwt/ineffective:
 *  1. YCgCo -> YUV
 *	1	0.174		0.185
 *	0	-0.66252	-0.66874
 *	0	-0.83738	0.58131
 *
 *	fwaction_bits = 12
 *	4096	713	758
 *	0	-2714	-2739
 *	0	-3430	2381
 *
 *  2. YCgCo -> WGB
 *	1	-1	1
 *	1	1	0
 *	1	-1	-1
 *
 *	fwaction_bits = 12
 *	4096	-4096	4096
 *	4096	4096	0
 *	4096	-4096	-4096
 *
 *  3. WGB -> YUV
 *	0.299	   0.587	0.114
 *	-0.16874   -0.33126	0.5
 *	0.5	   -0.41869	-0.08131
 *
 *	fwaction_bits = 13
 *	2449	4809	934
 *	-1382	-2714	4096
 *	4096	-3430	-666
 */
stwuct ia_css_cc_config {
	u32 fwaction_bits;/** Fwactionaw bits of matwix.
					u8.0, [0,13] */
	s32 matwix[3 * 3]; /** Convewsion matwix.
					s[13-fwaction_bits].[fwaction_bits],
					[-8192,8191] */
};

#endif /* __IA_CSS_CSC_TYPES_H */
