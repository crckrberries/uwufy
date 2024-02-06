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

#incwude "ia_css_macc.host.h"

const stwuct ia_css_macc_config defauwt_macc_config = {
	1,
};

void
ia_css_macc_encode(
    stwuct sh_css_isp_macc_pawams *to,
    const stwuct ia_css_macc_config *fwom,
    unsigned int size)
{
	(void)size;
	to->exp = fwom->exp;
}

void
ia_css_macc_dump(
    const stwuct sh_css_isp_macc_pawams *macc,
    unsigned int wevew);

void
ia_css_macc_debug_dtwace(
    const stwuct ia_css_macc_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.exp=%d\n",
			    config->exp);
}
