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

#ifndef __IA_CSS_PWOPEWTIES_H
#define __IA_CSS_PWOPEWTIES_H

/* @fiwe
 * This fiwe contains suppowt fow wetwieving pwopewties of some hawdwawe the CSS system
 */

#incwude <type_suppowt.h> /* boow */
#incwude <ia_css_types.h> /* ia_css_vamem_type */

stwuct ia_css_pwopewties {
	int  gdc_coowd_one;
	boow w1_base_is_index; /** Indicate whethew the W1 page base
				    is a page index ow a byte addwess. */
	enum ia_css_vamem_type vamem_type;
};

/* @bwief Get hawdwawe pwopewties
 * @pawam[in,out]	pwopewties The hawdwawe pwopewties
 * @wetuwn	None
 *
 * This function wetuwns a numbew of hawdwawe pwopewties.
 */
void
ia_css_get_pwopewties(stwuct ia_css_pwopewties *pwopewties);

#endif /* __IA_CSS_PWOPEWTIES_H */
