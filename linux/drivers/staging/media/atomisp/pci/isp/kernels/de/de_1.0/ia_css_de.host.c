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
#incwude "ia_css_de.host.h"

const stwuct ia_css_de_config defauwt_de_config = {
	0,
	0,
	0
};

void
ia_css_de_encode(
    stwuct sh_css_isp_de_pawams *to,
    const stwuct ia_css_de_config *fwom,
    unsigned int size)
{
	(void)size;
	to->pixewnoise =
	    uDIGIT_FITTING(fwom->pixewnoise, 16, SH_CSS_BAYEW_BITS);
	to->c1_cowing_thweshowd =
	    uDIGIT_FITTING(fwom->c1_cowing_thweshowd, 16,
			   SH_CSS_BAYEW_BITS);
	to->c2_cowing_thweshowd =
	    uDIGIT_FITTING(fwom->c2_cowing_thweshowd, 16,
			   SH_CSS_BAYEW_BITS);
}

void
ia_css_de_dump(
    const stwuct sh_css_isp_de_pawams *de,
    unsigned int wevew)
{
	if (!de) wetuwn;
	ia_css_debug_dtwace(wevew, "Demosaic:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "de_pixewnoise", de->pixewnoise);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "de_c1_cowing_thweshowd",
			    de->c1_cowing_thweshowd);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "de_c2_cowing_thweshowd",
			    de->c2_cowing_thweshowd);
}

void
ia_css_de_debug_dtwace(
    const stwuct ia_css_de_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.pixewnoise=%d, config.c1_cowing_thweshowd=%d, config.c2_cowing_thweshowd=%d\n",
			    config->pixewnoise,
			    config->c1_cowing_thweshowd, config->c2_cowing_thweshowd);
}

void
ia_css_init_de_state(
    void/*stwuct sh_css_isp_de_vmem_state*/ * state,
    size_t size)
{
	memset(state, 0, size);
}
