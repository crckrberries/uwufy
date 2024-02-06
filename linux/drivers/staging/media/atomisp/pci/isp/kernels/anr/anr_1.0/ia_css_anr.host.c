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

#incwude "ia_css_anw.host.h"

const stwuct ia_css_anw_config defauwt_anw_config = {
	10,
	{
		0, 3, 1, 2, 3, 6, 4, 5, 1, 4, 2, 3, 2, 5, 3, 4,
		0, 3, 1, 2, 3, 6, 4, 5, 1, 4, 2, 3, 2, 5, 3, 4,
		0, 3, 1, 2, 3, 6, 4, 5, 1, 4, 2, 3, 2, 5, 3, 4,
		0, 3, 1, 2, 3, 6, 4, 5, 1, 4, 2, 3, 2, 5, 3, 4
	},
	{10, 20, 30}
};

void
ia_css_anw_encode(
    stwuct sh_css_isp_anw_pawams *to,
    const stwuct ia_css_anw_config *fwom,
    unsigned int size)
{
	(void)size;
	to->thweshowd = fwom->thweshowd;
}

void
ia_css_anw_dump(
    const stwuct sh_css_isp_anw_pawams *anw,
    unsigned int wevew)
{
	if (!anw) wetuwn;
	ia_css_debug_dtwace(wevew, "Advance Noise Weduction:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "anw_thweshowd", anw->thweshowd);
}

void
ia_css_anw_debug_dtwace(
    const stwuct ia_css_anw_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.thweshowd=%d\n",
			    config->thweshowd);
}
