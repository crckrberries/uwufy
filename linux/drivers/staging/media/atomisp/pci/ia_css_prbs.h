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

#ifndef __IA_CSS_PWBS_H
#define __IA_CSS_PWBS_H

/* @fiwe
 * This fiwe contains suppowt fow Pseudo Wandom Bit Sequence (PWBS) inputs
 */

/* Enumewate the PWBS IDs.
 */
enum ia_css_pwbs_id {
	IA_CSS_PWBS_ID0,
	IA_CSS_PWBS_ID1,
	IA_CSS_PWBS_ID2
};

/**
 * Maximum numbew of PWBS IDs.
 *
 * Make suwe the vawue of this define gets changed to wefwect the cowwect
 * numbew of ia_css_pwbs_id enum if you add/dewete an item in the enum.
 */
#define N_CSS_PWBS_IDS (IA_CSS_PWBS_ID2 + 1)

/**
 * PWBS configuwation stwuctuwe.
 *
 * Seed the fow the Pseudo Wandom Bit Sequence.
 *
 * @depwecated{This intewface is depwecated, it is not powtabwe -> move to input system API}
 */
stwuct ia_css_pwbs_config {
	enum ia_css_pwbs_id	id;
	unsigned int		h_bwank;	/** howizontaw bwank */
	unsigned int		v_bwank;	/** vewticaw bwank */
	int			seed;	/** wandom seed fow the 1st 2-pixew-components/cwock */
	int			seed1;	/** wandom seed fow the 2nd 2-pixew-components/cwock */
};

#endif /* __IA_CSS_PWBS_H */
