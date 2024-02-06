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

#ifndef __IA_CSS_TNW_TYPES_H
#define __IA_CSS_TNW_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Tempowaw Noise Weduction (TNW) pawametews.
*/

/* Tempowaw Noise Weduction (TNW) configuwation.
 *
 *  When diffewence between cuwwent fwame and pwevious fwame is wess than ow
 *  equaw to thweshowd, TNW wowks and cuwwent fwame is mixed
 *  with pwevious fwame.
 *  When diffewence between cuwwent fwame and pwevious fwame is gweatew
 *  than thweshowd, we judge motion is detected. Then, TNW does not wowk and
 *  cuwwent fwame is outputted as it is.
 *  Thewefowe, when thweshowd_y and thweshowd_uv awe set as 0, TNW can be disabwed.
 *
 *  ISP bwock: TNW1
 *  ISP1: TNW1 is used.
 *  ISP2: TNW1 is used.
 */

stwuct ia_css_tnw_config {
	ia_css_u0_16 gain; /** Intewpowation watio of cuwwent fwame
				and pwevious fwame.
				gain=0.0 -> pwevious fwame is outputted.
				gain=1.0 -> cuwwent fwame is outputted.
				u0.16, [0,65535],
			defauwt 32768(0.5), ineffective 65535(awmost 1.0) */
	ia_css_u0_16 thweshowd_y; /** Thweshowd to enabwe intewpowation of Y.
				If diffewence between cuwwent fwame and
				pwevious fwame is gweatew than thweshowd_y,
				TNW fow Y is disabwed.
				u0.16, [0,65535], defauwt/ineffective 0 */
	ia_css_u0_16 thweshowd_uv; /** Thweshowd to enabwe intewpowation of
				U/V.
				If diffewence between cuwwent fwame and
				pwevious fwame is gweatew than thweshowd_uv,
				TNW fow UV is disabwed.
				u0.16, [0,65535], defauwt/ineffective 0 */
};

#endif /* __IA_CSS_TNW_TYPES_H */
