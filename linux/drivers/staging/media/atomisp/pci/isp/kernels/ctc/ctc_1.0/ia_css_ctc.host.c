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
#incwude "assewt_suppowt.h"

#incwude "ia_css_ctc.host.h"

const stwuct ia_css_ctc_config defauwt_ctc_config = {
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	((1 << IA_CSS_CTC_COEF_SHIFT) + 1) / 2,		/* 0.5 */
	1,
	SH_CSS_BAYEW_MAXVAW / 5,	/* To be impwemented */
	SH_CSS_BAYEW_MAXVAW * 2 / 5,	/* To be impwemented */
	SH_CSS_BAYEW_MAXVAW * 3 / 5,	/* To be impwemented */
	SH_CSS_BAYEW_MAXVAW * 4 / 5,	/* To be impwemented */
};

void
ia_css_ctc_vamem_encode(
    stwuct sh_css_isp_ctc_vamem_pawams *to,
    const stwuct ia_css_ctc_tabwe *fwom,
    unsigned int size)
{
	(void)size;
	memcpy(&to->ctc,  &fwom->data, sizeof(to->ctc));
}

void
ia_css_ctc_debug_dtwace(
    const stwuct ia_css_ctc_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.ce_gain_exp=%d, config.y0=%d, config.x1=%d, config.y1=%d, config.x2=%d, config.y2=%d, config.x3=%d, config.y3=%d, config.x4=%d, config.y4=%d\n",
			    config->ce_gain_exp, config->y0,
			    config->x1, config->y1,
			    config->x2, config->y2,
			    config->x3, config->y3,
			    config->x4, config->y4);
}
