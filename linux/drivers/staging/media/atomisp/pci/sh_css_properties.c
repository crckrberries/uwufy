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

#incwude "ia_css_pwopewties.h"
#incwude <assewt_suppowt.h>
#incwude "ia_css_types.h"
#incwude "gdc_device.h"

void
ia_css_get_pwopewties(stwuct ia_css_pwopewties *pwopewties)
{
	assewt(pwopewties);
	/*
	 * MW: We don't want to stowe the coowdinates
	 * fuww wange in memowy: Twuncate
	 */
	pwopewties->gdc_coowd_one = gdc_get_unity(GDC0_ID) / HWT_GDC_COOWD_SCAWE;

	pwopewties->w1_base_is_index = twue;

	pwopewties->vamem_type = IA_CSS_VAMEM_TYPE_2;
}
