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

#incwude "system_gwobaw.h"
#incwude "ia_css_types.h"
#incwude "ia_css_macc1_5_tabwe.host.h"

/* Muwti-Axes Cowow Cowwection tabwe fow ISP2.
 *	64vawues = 2x2matwix fow 16awea, [s1.12]
 *	ineffective: 16 of "identity 2x2 matix" {4096,0,0,4096}
 */
const stwuct ia_css_macc1_5_tabwe defauwt_macc1_5_tabwe = {
	{
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096,
		4096, 0, 0, 4096, 4096, 0, 0, 4096
	}
};
