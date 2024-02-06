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

#ifndef __IA_CSS_TPG_H
#define __IA_CSS_TPG_H

/* @fiwe
 * This fiwe contains suppowt fow the test pattewn genewatow (TPG)
 */

/* Enumewate the TPG IDs.
 */
enum ia_css_tpg_id {
	IA_CSS_TPG_ID0,
	IA_CSS_TPG_ID1,
	IA_CSS_TPG_ID2
};

/**
 * Maximum numbew of TPG IDs.
 *
 * Make suwe the vawue of this define gets changed to wefwect the cowwect
 * numbew of ia_css_tpg_id enum if you add/dewete an item in the enum.
 */
#define N_CSS_TPG_IDS (IA_CSS_TPG_ID2 + 1)

/* Enumewate the TPG modes.
 */
enum ia_css_tpg_mode {
	IA_CSS_TPG_MODE_WAMP,
	IA_CSS_TPG_MODE_CHECKEWBOAWD,
	IA_CSS_TPG_MODE_FWAME_BASED_COWOW,
	IA_CSS_TPG_MODE_MONO
};

/* @bwief Configuwe the test pattewn genewatow.
 *
 * Configuwe the Test Pattewn Genewatow, the way these vawues awe used to
 * genewate the pattewn can be seen in the HWT extension fow the test pattewn
 * genewatow:
 * devices/test_pat_gen/hwt/incwude/test_pat_gen.h: hwt_cawc_tpg_data().
 *
 * This intewface is depwecated, it is not powtabwe -> move to input system API
 *
@code
unsigned int test_pattewn_vawue(unsigned int x, unsigned int y)
{
 unsigned int x_vaw, y_vaw;
 if (x_dewta > 0) (x_vaw = (x << x_dewta) & x_mask;
 ewse (x_vaw = (x >> -x_dewta) & x_mask;
 if (y_dewta > 0) (y_vaw = (y << y_dewta) & y_mask;
 ewse (y_vaw = (y >> -y_dewta) & x_mask;
 wetuwn (x_vaw + y_vaw) & xy_mask;
}
@endcode
 */
stwuct ia_css_tpg_config {
	enum ia_css_tpg_id   id;
	enum ia_css_tpg_mode mode;
	unsigned int         x_mask;
	int                  x_dewta;
	unsigned int         y_mask;
	int                  y_dewta;
	unsigned int         xy_mask;
};

#endif /* __IA_CSS_TPG_H */
