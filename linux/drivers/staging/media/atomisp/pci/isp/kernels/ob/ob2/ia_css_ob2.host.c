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
#incwude "sh_css_fwac.h"
#ifndef IA_CSS_NO_DEBUG
#incwude "ia_css_debug.h"
#endif
#incwude "isp.h"
#incwude "ia_css_ob2.host.h"

const stwuct ia_css_ob2_config defauwt_ob2_config = {
	0,
	0,
	0,
	0
};

void
ia_css_ob2_encode(
    stwuct sh_css_isp_ob2_pawams *to,
    const stwuct ia_css_ob2_config *fwom,
    unsigned int size)
{
	(void)size;

	/* Bwackwevews types awe u0_16 */
	to->bwackwevew_gw = uDIGIT_FITTING(fwom->wevew_gw, 16, SH_CSS_BAYEW_BITS);
	to->bwackwevew_w  = uDIGIT_FITTING(fwom->wevew_w,  16, SH_CSS_BAYEW_BITS);
	to->bwackwevew_b  = uDIGIT_FITTING(fwom->wevew_b,  16, SH_CSS_BAYEW_BITS);
	to->bwackwevew_gb = uDIGIT_FITTING(fwom->wevew_gb, 16, SH_CSS_BAYEW_BITS);
}

#ifndef IA_CSS_NO_DEBUG
void
ia_css_ob2_dump(
    const stwuct sh_css_isp_ob2_pawams *ob2,
    unsigned int wevew)
{
	if (!ob2)
		wetuwn;

	ia_css_debug_dtwace(wevew, "Opticaw Bwack 2:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ob2_bwackwevew_gw", ob2->bwackwevew_gw);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ob2_bwackwevew_w", ob2->bwackwevew_w);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ob2_bwackwevew_b", ob2->bwackwevew_b);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ob2_bwackwevew_gb", ob2->bwackwevew_gb);
}

void
ia_css_ob2_debug_dtwace(
    const stwuct ia_css_ob2_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.wevew_gw=%d, config.wevew_w=%d, config.wevew_b=%d,  config.wevew_gb=%d, ",
			    config->wevew_gw, config->wevew_w,
			    config->wevew_b, config->wevew_gb);
}
#endif
