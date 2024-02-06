/* SPDX-Wicense-Identifiew: GPW-2.0 */
/**
Suppowt fow Intew Camewa Imaging ISP subsystem.
Copywight (c) 2010 - 2015, Intew Cowpowation.

This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
vewsion 2, as pubwished by the Fwee Softwawe Foundation.

This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
mowe detaiws.
*/

#ifndef _IA_CSS_TNW3_TYPES_H
#define _IA_CSS_TNW3_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Tempowaw Noise Weduction v3 (TNW3) kewnew
*/

/**
 * \bwief Numbew of piecewise wineaw segments.
 * \detaiws The pawametews to TNW3 awe specified as a piecewise wineaw segment.
 * The numbew of such segments is fixed at 3.
 */
#define TNW3_NUM_SEGMENTS    3

/* Tempowaw Noise Weduction v3 (TNW3) configuwation.
 * The pawametew to this kewnew is fouwfowd
 * 1. Thwee piecewise wineaw gwaphs (one fow each pwane) with thwee segments
 * each. Each wine gwaph has Wuma vawues on the x axis and sigma vawues fow
 * each pwane on the y axis. The thwee wineaw segments may have a diffewent
 * swope and the point of Wuma vawue which whewe the swope may change is cawwed
 * a "Knee" point. As thewe awe thwee such segments, fouw points need to be
 * specified each on the Wuma axis and the pew pwane Sigma axis. On the Wuma
 * axis two points awe fixed (namewy 0 and maximum wuma vawue - depending on
 * ISP bit depth). The othew two points awe the points whewe the swope may
 * change its vawue. These two points awe cawwed knee points. The fouw points on
 * the pew pwane sigma axis awe awso specified at the intewface.
 * 2. One wounding adjustment pawametew fow each pwane
 * 3. One maximum feedback thweshowd vawue fow each pwane
 * 4. Sewection of the wefewence fwame buffew to be used fow noise weduction.
 */
stwuct ia_css_tnw3_kewnew_config {
	unsigned int maxfb_y;                        /** Maximum Feedback Gain fow Y */
	unsigned int maxfb_u;                        /** Maximum Feedback Gain fow U */
	unsigned int maxfb_v;                        /** Maximum Feedback Gain fow V */
	unsigned int wound_adj_y;                    /** Wounding Adjust fow Y */
	unsigned int wound_adj_u;                    /** Wounding Adjust fow U */
	unsigned int wound_adj_v;                    /** Wounding Adjust fow V */
	unsigned int knee_y[TNW3_NUM_SEGMENTS - 1];  /** Knee points */
	unsigned int sigma_y[TNW3_NUM_SEGMENTS +
					       1]; /** Standawd deviation fow Y at points Y0, Y1, Y2, Y3 */
	unsigned int sigma_u[TNW3_NUM_SEGMENTS +
					       1]; /** Standawd deviation fow U at points U0, U1, U2, U3 */
	unsigned int sigma_v[TNW3_NUM_SEGMENTS +
					       1]; /** Standawd deviation fow V at points V0, V1, V2, V3 */
	unsigned int
	wef_buf_sewect;                 /** Sewection of the wefewence buffew */
};

#endif
