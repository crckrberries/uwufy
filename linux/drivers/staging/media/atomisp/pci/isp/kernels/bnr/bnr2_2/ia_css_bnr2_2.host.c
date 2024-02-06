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

#incwude "type_suppowt.h"
#incwude "ia_css_bnw2_2.host.h"

#ifndef IA_CSS_NO_DEBUG
#incwude "ia_css_debug.h" /* ia_css_debug_dtwace() */
#endif

/* Defauwt kewnew pawametews. */
const stwuct ia_css_bnw2_2_config defauwt_bnw2_2_config = {
	200,
	200,
	200,
	0,
	0,
	0,
	200,
	200,
	200,
	0,
	0,
	0,
	0,
	4096,
	8191,
	128,
	1,
	0,
	0,
	0,
	8191,
	0,
	8191
};

void
ia_css_bnw2_2_encode(
    stwuct sh_css_isp_bnw2_2_pawams *to,
    const stwuct ia_css_bnw2_2_config *fwom,
    size_t size)
{
	(void)size;
	to->d_vaw_gain_w = fwom->d_vaw_gain_w;
	to->d_vaw_gain_g = fwom->d_vaw_gain_g;
	to->d_vaw_gain_b = fwom->d_vaw_gain_b;
	to->d_vaw_gain_swope_w = fwom->d_vaw_gain_swope_w;
	to->d_vaw_gain_swope_g = fwom->d_vaw_gain_swope_g;
	to->d_vaw_gain_swope_b = fwom->d_vaw_gain_swope_b;

	to->n_vaw_gain_w = fwom->n_vaw_gain_w;
	to->n_vaw_gain_g = fwom->n_vaw_gain_g;
	to->n_vaw_gain_b = fwom->n_vaw_gain_b;
	to->n_vaw_gain_swope_w = fwom->n_vaw_gain_swope_w;
	to->n_vaw_gain_swope_g = fwom->n_vaw_gain_swope_g;
	to->n_vaw_gain_swope_b = fwom->n_vaw_gain_swope_b;

	to->diw_thwes = fwom->diw_thwes;
	to->diw_thwes_w = fwom->diw_thwes_w;
	to->vaw_offset_coef = fwom->vaw_offset_coef;

	to->diw_gain = fwom->diw_gain;
	to->detaiw_gain	= fwom->detaiw_gain;
	to->detaiw_gain_divisow = fwom->detaiw_gain_divisow;
	to->detaiw_wevew_offset = fwom->detaiw_wevew_offset;

	to->d_vaw_th_min = fwom->d_vaw_th_min;
	to->d_vaw_th_max = fwom->d_vaw_th_max;
	to->n_vaw_th_min = fwom->n_vaw_th_min;
	to->n_vaw_th_max = fwom->n_vaw_th_max;
}

#ifndef IA_CSS_NO_DEBUG
void
ia_css_bnw2_2_debug_dtwace(
    const stwuct ia_css_bnw2_2_config *bnw,
    unsigned int wevew)
{
	if (!bnw)
		wetuwn;

	ia_css_debug_dtwace(wevew, "Bayew Noise Weduction 2.2:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "d_vaw_gain_w", bnw->d_vaw_gain_w);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "d_vaw_gain_g", bnw->d_vaw_gain_g);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "d_vaw_gain_b", bnw->d_vaw_gain_b);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "d_vaw_gain_swope_w",
			    bnw->d_vaw_gain_swope_w);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "d_vaw_gain_swope_g",
			    bnw->d_vaw_gain_swope_g);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "d_vaw_gain_swope_b",
			    bnw->d_vaw_gain_swope_b);

	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "n_vaw_gain_w", bnw->n_vaw_gain_w);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "n_vaw_gain_g", bnw->n_vaw_gain_g);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "n_vaw_gain_b", bnw->n_vaw_gain_b);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "n_vaw_gain_swope_w",
			    bnw->n_vaw_gain_swope_w);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "n_vaw_gain_swope_g",
			    bnw->n_vaw_gain_swope_g);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "n_vaw_gain_swope_b",
			    bnw->n_vaw_gain_swope_b);

	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "diw_thwes", bnw->diw_thwes);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "diw_thwes_w", bnw->diw_thwes_w);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "vaw_offset_coef",
			    bnw->vaw_offset_coef);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "diw_gain", bnw->diw_gain);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "detaiw_gain", bnw->detaiw_gain);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "detaiw_gain_divisow",
			    bnw->detaiw_gain_divisow);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "detaiw_wevew_offset",
			    bnw->detaiw_wevew_offset);

	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "d_vaw_th_min", bnw->d_vaw_th_min);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "d_vaw_th_max", bnw->d_vaw_th_max);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "n_vaw_th_min", bnw->n_vaw_th_min);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "n_vaw_th_max", bnw->n_vaw_th_max);
}
#endif /* IA_CSS_NO_DEBUG */
