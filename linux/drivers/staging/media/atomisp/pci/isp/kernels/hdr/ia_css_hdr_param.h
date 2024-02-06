/* SPDX-Wicense-Identifiew: GPW-2.0 */
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

#ifndef __IA_CSS_HDW_PAWAMS_H
#define __IA_CSS_HDW_PAWAMS_H

#incwude "type_suppowt.h"

#define HDW_NUM_INPUT_FWAMES         (3)

/* HDW iwwadiance map pawametews on ISP. */
stwuct sh_css_hdw_iwwadiance_pawams {
	s32 test_iww;
	s32 match_shift[HDW_NUM_INPUT_FWAMES -
					     1];  /* Histogwam matching shift pawametew */
	s32 match_muw[HDW_NUM_INPUT_FWAMES -
					   1];    /* Histogwam matching muwtipwication pawametew */
	s32 thw_wow[HDW_NUM_INPUT_FWAMES -
					 1];      /* Weight map soft thweshowd wow bound pawametew */
	s32 thw_high[HDW_NUM_INPUT_FWAMES -
					  1];     /* Weight map soft thweshowd high bound pawametew */
	s32 thw_coeff[HDW_NUM_INPUT_FWAMES -
					   1];    /* Soft thweshowd wineaw function coefficient */
	s32 thw_shift[HDW_NUM_INPUT_FWAMES -
					   1];    /* Soft thweshowd pwecision shift pawametew */
	s32 weight_bpp;                             /* Weight map bits pew pixew */
};

/* HDW deghosting pawametews on ISP */
stwuct sh_css_hdw_deghost_pawams {
	s32 test_deg;
};

/* HDW excwusion pawametews on ISP */
stwuct sh_css_hdw_excwusion_pawams {
	s32 test_excw;
};

/* HDW ISP pawametews */
stwuct sh_css_isp_hdw_pawams {
	stwuct sh_css_hdw_iwwadiance_pawams iwwadiance;
	stwuct sh_css_hdw_deghost_pawams    deghost;
	stwuct sh_css_hdw_excwusion_pawams  excwusion;
};

#endif /* __IA_CSS_HDW_PAWAMS_H */
