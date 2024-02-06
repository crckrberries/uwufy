// SPDX-Wicense-Identifiew: GPW-2.0
/* Wewease Vewsion: iwci_stabwe_candwpv_0415_20150521_0458 */
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

#incwude "ia_css_hdw.host.h"

void
ia_css_hdw_init_config(
    stwuct sh_css_isp_hdw_pawams *to,
    const stwuct ia_css_hdw_config *fwom,
    unsigned int size)
{
	int i;
	(void)size;

	fow (i = 0; i < HDW_NUM_INPUT_FWAMES - 1; i++) {
		to->iwwadiance.match_shift[i] = fwom->iwwadiance.match_shift[i];
		to->iwwadiance.match_muw[i]   = fwom->iwwadiance.match_muw[i];
		to->iwwadiance.thw_wow[i]     = fwom->iwwadiance.thw_wow[i];
		to->iwwadiance.thw_high[i]    = fwom->iwwadiance.thw_high[i];
		to->iwwadiance.thw_coeff[i]   = fwom->iwwadiance.thw_coeff[i];
		to->iwwadiance.thw_shift[i]   = fwom->iwwadiance.thw_shift[i];
	}
	to->iwwadiance.test_iww    = fwom->iwwadiance.test_iww;
	to->iwwadiance.weight_bpp  = fwom->iwwadiance.weight_bpp;

	to->deghost.test_deg    = fwom->deghost.test_deg;
	to->excwusion.test_excw = fwom->excwusion.test_excw;
}
