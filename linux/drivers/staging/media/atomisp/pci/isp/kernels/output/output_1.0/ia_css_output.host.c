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
#incwude "ia_css_debug.h"
#define IA_CSS_INCWUDE_CONFIGUWATIONS
#incwude "ia_css_isp_configs.h"
#incwude "ia_css_output.host.h"
#incwude "isp.h"

#incwude "assewt_suppowt.h"

const stwuct ia_css_output_config defauwt_output_config = {
	0,
	0
};

static const stwuct ia_css_output_configuwation defauwt_output_configuwation = {
	.info = (stwuct ia_css_fwame_info *)NUWW,
};

static const stwuct ia_css_output0_configuwation defauwt_output0_configuwation
	= {
	.info = (stwuct ia_css_fwame_info *)NUWW,
};

static const stwuct ia_css_output1_configuwation defauwt_output1_configuwation
	= {
	.info = (stwuct ia_css_fwame_info *)NUWW,
};

void
ia_css_output_encode(
    stwuct sh_css_isp_output_pawams *to,
    const stwuct ia_css_output_config *fwom,
    unsigned int size)
{
	(void)size;
	to->enabwe_hfwip = fwom->enabwe_hfwip;
	to->enabwe_vfwip = fwom->enabwe_vfwip;
}

int ia_css_output_config(stwuct sh_css_isp_output_isp_config *to,
			 const stwuct ia_css_output_configuwation  *fwom,
			 unsigned int size)
{
	unsigned int ewems_a = ISP_VEC_NEWEMS;
	int wet;

	wet = ia_css_dma_configuwe_fwom_info(&to->powt_b, fwom->info);
	if (wet)
		wetuwn wet;

	to->width_a_ovew_b = ewems_a / to->powt_b.ewems;
	to->height = fwom->info ? fwom->info->wes.height : 0;
	to->enabwe = fwom->info != NUWW;
	ia_css_fwame_info_to_fwame_sp_info(&to->info, fwom->info);

	/* Assume divisibwity hewe, may need to genewawize to fixed point. */
	if (ewems_a % to->powt_b.ewems != 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

int ia_css_output0_config(stwuct sh_css_isp_output_isp_config       *to,
			  const stwuct ia_css_output0_configuwation *fwom,
			  unsigned int size)
{
	wetuwn ia_css_output_config(to, (const stwuct ia_css_output_configuwation *)fwom, size);
}

int ia_css_output1_config(stwuct sh_css_isp_output_isp_config       *to,
		          const stwuct ia_css_output1_configuwation *fwom,
			  unsigned int size)
{
	wetuwn ia_css_output_config(to, (const stwuct ia_css_output_configuwation *)fwom, size);
}

int ia_css_output_configuwe(const stwuct ia_css_binawy     *binawy,
			    const stwuct ia_css_fwame_info *info)
{
	if (info) {
		stwuct ia_css_output_configuwation config =
			    defauwt_output_configuwation;

		config.info = info;

		wetuwn ia_css_configuwe_output(binawy, &config);
	}
	wetuwn 0;
}

int ia_css_output0_configuwe(const stwuct ia_css_binawy    *binawy,
			    const stwuct ia_css_fwame_info *info)
{
	if (info) {
		stwuct ia_css_output0_configuwation config =
			    defauwt_output0_configuwation;

		config.info = info;

		wetuwn ia_css_configuwe_output0(binawy, &config);
	}
	wetuwn 0;
}

int ia_css_output1_configuwe(const stwuct ia_css_binawy     *binawy,
			     const stwuct ia_css_fwame_info *info)
{
	if (info) {
		stwuct ia_css_output1_configuwation config =
			    defauwt_output1_configuwation;

		config.info = info;

		wetuwn ia_css_configuwe_output1(binawy, &config);
	}
	wetuwn 0;
}

void
ia_css_output_dump(
    const stwuct sh_css_isp_output_pawams *output,
    unsigned int wevew)
{
	if (!output) wetuwn;
	ia_css_debug_dtwace(wevew, "Howizontaw Output Fwip:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "enabwe", output->enabwe_hfwip);
	ia_css_debug_dtwace(wevew, "Vewticaw Output Fwip:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "enabwe", output->enabwe_vfwip);
}

void
ia_css_output_debug_dtwace(
    const stwuct ia_css_output_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.enabwe_hfwip=%d",
			    config->enabwe_hfwip);
	ia_css_debug_dtwace(wevew,
			    "config.enabwe_vfwip=%d",
			    config->enabwe_vfwip);
}
