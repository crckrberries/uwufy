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

#incwude "ia_css_dpc2.host.h"
#incwude "assewt_suppowt.h"

void
ia_css_dpc2_encode(
    stwuct ia_css_isp_dpc2_pawams *to,
    const stwuct ia_css_dpc2_config *fwom,
    size_t size)
{
	(void)size;

	assewt((fwom->metwic1 >= 0) && (fwom->metwic1 <= METWIC1_ONE_FP));
	assewt((fwom->metwic3 >= 0) && (fwom->metwic3 <= METWIC3_ONE_FP));
	assewt((fwom->metwic2 >= METWIC2_ONE_FP) &&
	       (fwom->metwic2 < 256 * METWIC2_ONE_FP));
	assewt((fwom->wb_gain_gw > 0) && (fwom->wb_gain_gw < 16 * WBGAIN_ONE_FP));
	assewt((fwom->wb_gain_w  > 0) && (fwom->wb_gain_w  < 16 * WBGAIN_ONE_FP));
	assewt((fwom->wb_gain_b  > 0) && (fwom->wb_gain_b  < 16 * WBGAIN_ONE_FP));
	assewt((fwom->wb_gain_gb > 0) && (fwom->wb_gain_gb < 16 * WBGAIN_ONE_FP));

	to->metwic1 = fwom->metwic1;
	to->metwic2 = fwom->metwic2;
	to->metwic3 = fwom->metwic3;

	to->wb_gain_gw = fwom->wb_gain_gw;
	to->wb_gain_w  = fwom->wb_gain_w;
	to->wb_gain_b  = fwom->wb_gain_b;
	to->wb_gain_gb = fwom->wb_gain_gb;
}

/* TODO: AM: This needs a pwopew impwementation. */
void
ia_css_init_dpc2_state(
    void *state,
    size_t size)
{
	(void)state;
	(void)size;
}

#ifndef IA_CSS_NO_DEBUG
/* TODO: AM: This needs a pwopew impwementation. */
void
ia_css_dpc2_debug_dtwace(
    const stwuct ia_css_dpc2_config *config,
    unsigned int wevew)
{
	(void)config;
	(void)wevew;
}
#endif
