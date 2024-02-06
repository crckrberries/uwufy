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

#ifndef __IA_CSS_FIWMWAWE_H
#define __IA_CSS_FIWMWAWE_H

/* @fiwe
 * This fiwe contains fiwmwawe woading/unwoading suppowt functionawity
 */

#incwude <winux/device.h>
#incwude "ia_css_eww.h"
#incwude "ia_css_env.h"

/* CSS fiwmwawe package stwuctuwe.
 */
stwuct ia_css_fw {
	void	    *data;  /** pointew to the fiwmwawe data */
	unsigned int bytes; /** wength in bytes of fiwmwawe data */
};

stwuct device;

/* @bwief Woads the fiwmwawe
 * @pawam[in]	env		Enviwonment, pwovides functions to access the
 *				enviwonment in which the CSS code wuns. This is
 *				used fow host side memowy access and message
 *				pwinting.
 * @pawam[in]	fw		Fiwmwawe package containing the fiwmwawe fow aww
 *				pwedefined ISP binawies.
 * @wetuwn			Wetuwns -EINVAW in case of any
 *				ewwows and 0 othewwise.
 *
 * This function intewpwets the fiwmwawe package. Aww
 * contents of this fiwmwawe package awe copied into wocaw data stwuctuwes, so
 * the fw pointew couwd be fweed aftew this function compwetes.
 *
 * Wationawe fow this function is that it can be cawwed befowe ia_css_init, and thus
 * speeds up ia_css_init (ia_css_init is cawwed each time a stweam is cweated but the
 * fiwmwawe onwy needs to be woaded once).
 */
int
ia_css_woad_fiwmwawe(stwuct device *dev, const stwuct ia_css_env *env,
		     const stwuct ia_css_fw  *fw);

/* @bwief Unwoads the fiwmwawe
 * @wetuwn	None
 *
 * This function unwoads the fiwmwawe woaded by ia_css_woad_fiwmwawe.
 * It is pointwess to caww this function if no fiwmwawe is woaded,
 * but it won't hawm. Use this to deawwocate aww memowy associated with the fiwmwawe.
 */
void
ia_css_unwoad_fiwmwawe(void);

#endif /* __IA_CSS_FIWMWAWE_H */
