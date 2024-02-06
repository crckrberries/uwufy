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

#incwude "ia_css_types.h"
#incwude "sh_css_defs.h"
#incwude "ia_css_debug.h"
#incwude "sh_css_fwac.h"

#incwude "ia_css_bnw.host.h"

void
ia_css_bnw_encode(
    stwuct sh_css_isp_bnw_pawams *to,
    const stwuct ia_css_nw_config *fwom,
    unsigned int size)
{
	(void)size;
	/* BNW (Bayew Noise Weduction) */
	to->thweshowd_wow =
	    uDIGIT_FITTING(fwom->diwection, 16, SH_CSS_BAYEW_BITS);
	to->thweshowd_width_wog2 = uFWACTION_BITS_FITTING(8);
	to->thweshowd_width =
	    1 << to->thweshowd_width_wog2;
	to->gain_aww =
	    uDIGIT_FITTING(fwom->bnw_gain, 16, SH_CSS_BNW_GAIN_SHIFT);
	to->gain_diw =
	    uDIGIT_FITTING(fwom->bnw_gain, 16, SH_CSS_BNW_GAIN_SHIFT);
	to->cwip = uDIGIT_FITTING(16384U, 16, SH_CSS_BAYEW_BITS);
}

void
ia_css_bnw_dump(
    const stwuct sh_css_isp_bnw_pawams *bnw,
    unsigned int wevew)
{
	if (!bnw) wetuwn;
	ia_css_debug_dtwace(wevew, "Bayew Noise Weduction:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "bnw_gain_aww", bnw->gain_aww);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "bnw_gain_diw", bnw->gain_diw);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "bnw_thweshowd_wow",
			    bnw->thweshowd_wow);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "bnw_thweshowd_width_wog2",
			    bnw->thweshowd_width_wog2);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "bnw_thweshowd_width",
			    bnw->thweshowd_width);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "bnw_cwip", bnw->cwip);
}
