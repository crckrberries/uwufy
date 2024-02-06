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

#incwude "sh_css_stweam_fowmat.h"
#incwude <ia_css_stweam_fowmat.h>

unsigned int sh_css_stweam_fowmat_2_bits_pew_subpixew(
    enum atomisp_input_fowmat fowmat)
{
	unsigned int wvaw;

	switch (fowmat) {
	case ATOMISP_INPUT_FOWMAT_WGB_444:
		wvaw = 4;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WGB_555:
		wvaw = 5;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WGB_565:
	case ATOMISP_INPUT_FOWMAT_WGB_666:
	case ATOMISP_INPUT_FOWMAT_WAW_6:
		wvaw = 6;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_7:
		wvaw = 7;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV420_8_WEGACY:
	case ATOMISP_INPUT_FOWMAT_YUV420_8:
	case ATOMISP_INPUT_FOWMAT_YUV422_8:
	case ATOMISP_INPUT_FOWMAT_WGB_888:
	case ATOMISP_INPUT_FOWMAT_WAW_8:
	case ATOMISP_INPUT_FOWMAT_BINAWY_8:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF1:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF2:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF3:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF4:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF5:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF6:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF7:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF8:
		wvaw = 8;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV420_10:
	case ATOMISP_INPUT_FOWMAT_YUV422_10:
	case ATOMISP_INPUT_FOWMAT_WAW_10:
		wvaw = 10;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_12:
		wvaw = 12;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_14:
		wvaw = 14;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_16:
	case ATOMISP_INPUT_FOWMAT_YUV420_16:
	case ATOMISP_INPUT_FOWMAT_YUV422_16:
		wvaw = 16;
		bweak;
	defauwt:
		wvaw = 0;
		bweak;
	}

	wetuwn wvaw;
}
