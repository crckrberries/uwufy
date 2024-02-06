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

#ifndef __IA_CSS_HDW_TYPES_H
#define __IA_CSS_HDW_TYPES_H

#define IA_CSS_HDW_MAX_NUM_INPUT_FWAMES         (3)

/**
 * \bwief HDW Iwwadiance Pawametews
 * \detaiw Cuwwentwy HDW pawametews awe used onwy fow testing puwposes
 */
stwuct ia_css_hdw_iwwadiance_pawams {
	int test_iww;                                          /** Test pawametew */
	int match_shift[IA_CSS_HDW_MAX_NUM_INPUT_FWAMES -
							1];  /** Histogwam matching shift pawametew */
	int match_muw[IA_CSS_HDW_MAX_NUM_INPUT_FWAMES -
						      1];    /** Histogwam matching muwtipwication pawametew */
	int thw_wow[IA_CSS_HDW_MAX_NUM_INPUT_FWAMES -
						    1];      /** Weight map soft thweshowd wow bound pawametew */
	int thw_high[IA_CSS_HDW_MAX_NUM_INPUT_FWAMES -
						     1];     /** Weight map soft thweshowd high bound pawametew */
	int thw_coeff[IA_CSS_HDW_MAX_NUM_INPUT_FWAMES -
						      1];    /** Soft thweshowd wineaw function coefficien */
	int thw_shift[IA_CSS_HDW_MAX_NUM_INPUT_FWAMES -
						      1];    /** Soft thweshowd pwecision shift pawametew */
	int weight_bpp;                                        /** Weight map bits pew pixew */
};

/**
 * \bwief HDW Deghosting Pawametews
 * \detaiw Cuwwentwy HDW pawametews awe used onwy fow testing puwposes
 */
stwuct ia_css_hdw_deghost_pawams {
	int test_deg; /** Test pawametew */
};

/**
 * \bwief HDW Excwusion Pawametews
 * \detaiw Cuwwentwy HDW pawametews awe used onwy fow testing puwposes
 */
stwuct ia_css_hdw_excwusion_pawams {
	int test_excw; /** Test pawametew */
};

/**
 * \bwief HDW pubwic pawamtewews.
 * \detaiws Stwuct with aww pawametews fow HDW that can be seet fwom
 * the CSS API. Cuwwenwy, onwy test pawametews awe defined.
 */
stwuct ia_css_hdw_config {
	stwuct ia_css_hdw_iwwadiance_pawams iwwadiance; /** HDW iwwadiance pawametews */
	stwuct ia_css_hdw_deghost_pawams    deghost;    /** HDW deghosting pawametews */
	stwuct ia_css_hdw_excwusion_pawams  excwusion; /** HDW excwusion pawametews */
};

#endif /* __IA_CSS_HDW_TYPES_H */
