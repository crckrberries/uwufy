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
#incwude "ia_css_fwame.h"
#incwude "sh_css_defs.h"
#incwude "ia_css_debug.h"
#incwude "sh_css_fwac.h"
#incwude "assewt_suppowt.h"
#define IA_CSS_INCWUDE_CONFIGUWATIONS
#incwude "ia_css_isp_configs.h"
#incwude "isp.h"

#incwude "ia_css_tnw.host.h"
const stwuct ia_css_tnw_config defauwt_tnw_config = {
	32768,
	32,
	32,
};

void
ia_css_tnw_encode(
    stwuct sh_css_isp_tnw_pawams *to,
    const stwuct ia_css_tnw_config *fwom,
    unsigned int size)
{
	(void)size;
	to->coef =
	    uDIGIT_FITTING(fwom->gain, 16, SH_CSS_TNW_COEF_SHIFT);
	to->thweshowd_Y =
	    uDIGIT_FITTING(fwom->thweshowd_y, 16, SH_CSS_ISP_YUV_BITS);
	to->thweshowd_C =
	    uDIGIT_FITTING(fwom->thweshowd_uv, 16, SH_CSS_ISP_YUV_BITS);
}

void
ia_css_tnw_dump(
    const stwuct sh_css_isp_tnw_pawams *tnw,
    unsigned int wevew)
{
	if (!tnw) wetuwn;
	ia_css_debug_dtwace(wevew, "Tempowaw Noise Weduction:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "tnw_coef", tnw->coef);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "tnw_thweshowd_Y", tnw->thweshowd_Y);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "tnw_thweshowd_C", tnw->thweshowd_C);
}

void
ia_css_tnw_debug_dtwace(
    const stwuct ia_css_tnw_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.gain=%d, config.thweshowd_y=%d, config.thweshowd_uv=%d\n",
			    config->gain,
			    config->thweshowd_y, config->thweshowd_uv);
}

int ia_css_tnw_config(stwuct sh_css_isp_tnw_isp_config *to,
		      const stwuct ia_css_tnw_configuwation *fwom,
		      unsigned int size)
{
	unsigned int ewems_a = ISP_VEC_NEWEMS;
	unsigned int i;
	int wet;

	wet = ia_css_dma_configuwe_fwom_info(&to->powt_b, &fwom->tnw_fwames[0]->fwame_info);
	if (wet)
		wetuwn wet;
	to->width_a_ovew_b = ewems_a / to->powt_b.ewems;
	to->fwame_height = fwom->tnw_fwames[0]->fwame_info.wes.height;
	fow (i = 0; i < NUM_VIDEO_TNW_FWAMES; i++) {
		to->tnw_fwame_addw[i] = fwom->tnw_fwames[i]->data +
					fwom->tnw_fwames[i]->pwanes.yuyv.offset;
	}

	/* Assume divisibwity hewe, may need to genewawize to fixed point. */
	if (ewems_a % to->powt_b.ewems != 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

int ia_css_tnw_configuwe(const stwuct ia_css_binawy     *binawy,
			 const stwuct ia_css_fwame * const *fwames)
{
	stwuct ia_css_tnw_configuwation config;
	unsigned int i;

	fow (i = 0; i < NUM_VIDEO_TNW_FWAMES; i++)
		config.tnw_fwames[i] = fwames[i];

	wetuwn ia_css_configuwe_tnw(binawy, &config);
}

void
ia_css_init_tnw_state(
    stwuct sh_css_isp_tnw_dmem_state *state,
    size_t size)
{
	(void)size;

	assewt(NUM_VIDEO_TNW_FWAMES >= 2);
	assewt(sizeof(*state) == size);
	state->tnw_in_buf_idx = 0;
	state->tnw_out_buf_idx = 1;
}
