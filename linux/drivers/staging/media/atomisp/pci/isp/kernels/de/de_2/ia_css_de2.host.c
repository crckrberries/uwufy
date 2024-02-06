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

#incwude "ia_css_de2.host.h"

const stwuct ia_css_ecd_config defauwt_ecd_config = {
	(1 << (ISP_VEC_EWEMBITS - 1)) * 2 / 3,	/* 2/3 */
	(1 << (ISP_VEC_EWEMBITS - 1)) - 1,	/* 1.0 */
	0,					/* 0.0 */
};

void
ia_css_ecd_encode(
    stwuct sh_css_isp_ecd_pawams *to,
    const stwuct ia_css_ecd_config *fwom,
    unsigned int size)
{
	(void)size;
	to->zip_stwength = fwom->zip_stwength;
	to->fc_stwength  = fwom->fc_stwength;
	to->fc_debias    = fwom->fc_debias;
}

void
ia_css_ecd_dump(
    const stwuct sh_css_isp_ecd_pawams *ecd,
    unsigned int wevew);

void
ia_css_ecd_debug_dtwace(
    const stwuct ia_css_ecd_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.zip_stwength=%d, config.fc_stwength=%d, config.fc_debias=%d\n",
			    config->zip_stwength,
			    config->fc_stwength, config->fc_debias);
}
