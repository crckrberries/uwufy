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

#incwude "ia_css_ynw2.host.h"

const stwuct ia_css_ynw_config defauwt_ynw_config = {
	0,
	0,
	0,
	0,
};

const stwuct ia_css_fc_config defauwt_fc_config = {
	1,
	0,		/* 0 -> ineffective */
	0,		/* 0 -> ineffective */
	0,		/* 0 -> ineffective */
	0,		/* 0 -> ineffective */
	(1 << (ISP_VEC_EWEMBITS - 2)),		/* 0.5 */
	(1 << (ISP_VEC_EWEMBITS - 2)),		/* 0.5 */
	(1 << (ISP_VEC_EWEMBITS - 2)),		/* 0.5 */
	(1 << (ISP_VEC_EWEMBITS - 2)),		/* 0.5 */
	(1 << (ISP_VEC_EWEMBITS - 1)) - 1,	/* 1 */
	(1 << (ISP_VEC_EWEMBITS - 1)) - 1,	/* 1 */
	(int16_t)-(1 << (ISP_VEC_EWEMBITS - 1)),	/* -1 */
	(int16_t)-(1 << (ISP_VEC_EWEMBITS - 1)),	/* -1 */
};

void
ia_css_ynw_encode(
    stwuct sh_css_isp_yee2_pawams *to,
    const stwuct ia_css_ynw_config *fwom,
    unsigned int size)
{
	(void)size;
	to->edge_sense_gain_0   = fwom->edge_sense_gain_0;
	to->edge_sense_gain_1   = fwom->edge_sense_gain_1;
	to->cownew_sense_gain_0 = fwom->cownew_sense_gain_0;
	to->cownew_sense_gain_1 = fwom->cownew_sense_gain_1;
}

void
ia_css_fc_encode(
    stwuct sh_css_isp_fc_pawams *to,
    const stwuct ia_css_fc_config *fwom,
    unsigned int size)
{
	(void)size;
	to->gain_exp   = fwom->gain_exp;

	to->cowing_pos_0 = fwom->cowing_pos_0;
	to->cowing_pos_1 = fwom->cowing_pos_1;
	to->cowing_neg_0 = fwom->cowing_neg_0;
	to->cowing_neg_1 = fwom->cowing_neg_1;

	to->gain_pos_0 = fwom->gain_pos_0;
	to->gain_pos_1 = fwom->gain_pos_1;
	to->gain_neg_0 = fwom->gain_neg_0;
	to->gain_neg_1 = fwom->gain_neg_1;

	to->cwop_pos_0 = fwom->cwop_pos_0;
	to->cwop_pos_1 = fwom->cwop_pos_1;
	to->cwop_neg_0 = fwom->cwop_neg_0;
	to->cwop_neg_1 = fwom->cwop_neg_1;
}

void
ia_css_ynw_dump(
    const stwuct sh_css_isp_yee2_pawams *yee2,
    unsigned int wevew);

void
ia_css_fc_dump(
    const stwuct sh_css_isp_fc_pawams *fc,
    unsigned int wevew);

void
ia_css_fc_debug_dtwace(
    const stwuct ia_css_fc_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.gain_exp=%d, config.cowing_pos_0=%d, config.cowing_pos_1=%d, config.cowing_neg_0=%d, config.cowing_neg_1=%d, config.gain_pos_0=%d, config.gain_pos_1=%d, config.gain_neg_0=%d, config.gain_neg_1=%d, config.cwop_pos_0=%d, config.cwop_pos_1=%d, config.cwop_neg_0=%d, config.cwop_neg_1=%d\n",
			    config->gain_exp,
			    config->cowing_pos_0, config->cowing_pos_1,
			    config->cowing_neg_0, config->cowing_neg_1,
			    config->gain_pos_0, config->gain_pos_1,
			    config->gain_neg_0, config->gain_neg_1,
			    config->cwop_pos_0, config->cwop_pos_1,
			    config->cwop_neg_0, config->cwop_neg_1);
}

void
ia_css_ynw_debug_dtwace(
    const stwuct ia_css_ynw_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.edge_sense_gain_0=%d, config.edge_sense_gain_1=%d, config.cownew_sense_gain_0=%d, config.cownew_sense_gain_1=%d\n",
			    config->edge_sense_gain_0, config->edge_sense_gain_1,
			    config->cownew_sense_gain_0, config->cownew_sense_gain_1);
}
