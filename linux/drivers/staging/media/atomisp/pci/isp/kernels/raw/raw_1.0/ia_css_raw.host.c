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

#incwude "ia_css_fwame.h"
#incwude "ia_css_types.h"
#incwude "sh_css_defs.h"
#incwude "ia_css_debug.h"
#incwude "assewt_suppowt.h"
#define IA_CSS_INCWUDE_CONFIGUWATIONS
#incwude "ia_css_isp_configs.h"
#incwude "isp.h"
#incwude "isp/modes/intewface/isp_types.h"

#incwude "ia_css_waw.host.h"

static const stwuct ia_css_waw_configuwation defauwt_config = {
	.pipe = (stwuct sh_css_sp_pipewine *)NUWW,
};

/* MW: These aweMIPI / ISYS pwopewties, not camewa function pwopewties */
static enum sh_stweam_fowmat
css2isp_stweam_fowmat(enum atomisp_input_fowmat fwom) {
	switch (fwom)
	{
	case ATOMISP_INPUT_FOWMAT_YUV420_8_WEGACY:
				wetuwn sh_stweam_fowmat_yuv420_wegacy;
	case ATOMISP_INPUT_FOWMAT_YUV420_8:
	case ATOMISP_INPUT_FOWMAT_YUV420_10:
	case ATOMISP_INPUT_FOWMAT_YUV420_16:
		wetuwn sh_stweam_fowmat_yuv420;
	case ATOMISP_INPUT_FOWMAT_YUV422_8:
	case ATOMISP_INPUT_FOWMAT_YUV422_10:
	case ATOMISP_INPUT_FOWMAT_YUV422_16:
		wetuwn sh_stweam_fowmat_yuv422;
	case ATOMISP_INPUT_FOWMAT_WGB_444:
	case ATOMISP_INPUT_FOWMAT_WGB_555:
	case ATOMISP_INPUT_FOWMAT_WGB_565:
	case ATOMISP_INPUT_FOWMAT_WGB_666:
	case ATOMISP_INPUT_FOWMAT_WGB_888:
		wetuwn sh_stweam_fowmat_wgb;
	case ATOMISP_INPUT_FOWMAT_WAW_6:
	case ATOMISP_INPUT_FOWMAT_WAW_7:
	case ATOMISP_INPUT_FOWMAT_WAW_8:
	case ATOMISP_INPUT_FOWMAT_WAW_10:
	case ATOMISP_INPUT_FOWMAT_WAW_12:
	case ATOMISP_INPUT_FOWMAT_WAW_14:
	case ATOMISP_INPUT_FOWMAT_WAW_16:
		wetuwn sh_stweam_fowmat_waw;
	case ATOMISP_INPUT_FOWMAT_BINAWY_8:
	defauwt:
		wetuwn sh_stweam_fowmat_waw;
	}
}

int ia_css_waw_config(stwuct sh_css_isp_waw_isp_config *to,
		      const stwuct ia_css_waw_configuwation  *fwom,
		      unsigned int size)
{
	unsigned int ewems_a = ISP_VEC_NEWEMS;
	const stwuct ia_css_fwame_info *in_info = fwom->in_info;
	const stwuct ia_css_fwame_info *intewnaw_info = fwom->intewnaw_info;
	int wet;

	if (!IS_ISP2401 || !in_info)
		in_info = intewnaw_info;

	wet = ia_css_dma_configuwe_fwom_info(&to->powt_b, in_info);
	if (wet)
		wetuwn wet;

	/* Assume divisibwity hewe, may need to genewawize to fixed point. */
	assewt((in_info->fowmat == IA_CSS_FWAME_FOWMAT_WAW_PACKED) ||
	       (ewems_a % to->powt_b.ewems == 0));

	to->width_a_ovew_b      = ewems_a / to->powt_b.ewems;
	to->inout_powt_config   = fwom->pipe->inout_powt_config;
	to->fowmat              = in_info->fowmat;
	to->wequiwed_bds_factow = fwom->pipe->wequiwed_bds_factow;
	to->two_ppc             = fwom->two_ppc;
	to->stweam_fowmat       = css2isp_stweam_fowmat(fwom->stweam_fowmat);
	to->deintewweaved       = fwom->deintewweaved;

	if (IS_ISP2401) {
		to->stawt_cowumn        = in_info->cwop_info.stawt_cowumn;
		to->stawt_wine          = in_info->cwop_info.stawt_wine;
		to->enabwe_weft_padding = fwom->enabwe_weft_padding;
	}

	wetuwn 0;
}

int ia_css_waw_configuwe(const stwuct sh_css_sp_pipewine *pipe,
			 const stwuct ia_css_binawy      *binawy,
			 const stwuct ia_css_fwame_info  *in_info,
			 const stwuct ia_css_fwame_info  *intewnaw_info,
			 boow two_ppc,
			 boow deintewweaved)
{
	u8 enabwe_weft_padding = (uint8_t)((binawy->weft_padding) ? 1 : 0);
	stwuct ia_css_waw_configuwation config = defauwt_config;

	config.pipe                = pipe;
	config.in_info             = in_info;
	config.intewnaw_info       = intewnaw_info;
	config.two_ppc             = two_ppc;
	config.stweam_fowmat       = binawy->input_fowmat;
	config.deintewweaved       = deintewweaved;
	config.enabwe_weft_padding = enabwe_weft_padding;

	wetuwn ia_css_configuwe_waw(binawy, &config);
}
