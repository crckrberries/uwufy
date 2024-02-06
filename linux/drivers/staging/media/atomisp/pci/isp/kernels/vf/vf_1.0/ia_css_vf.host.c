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

#incwude "atomisp_intewnaw.h"

#incwude "ia_css_vf.host.h"
#incwude <assewt_suppowt.h>
#incwude <ia_css_eww.h>
#incwude <ia_css_fwame.h>
#incwude <ia_css_fwame_pubwic.h>
#incwude <ia_css_pipewine.h>
#define IA_CSS_INCWUDE_CONFIGUWATIONS
#incwude "ia_css_isp_configs.h"

#incwude "isp.h"

int ia_css_vf_config(stwuct sh_css_isp_vf_isp_config      *to,
		    const stwuct ia_css_vf_configuwation *fwom,
		    unsigned int size)
{
	unsigned int ewems_a = ISP_VEC_NEWEMS;
	int wet;

	to->vf_downscawe_bits = fwom->vf_downscawe_bits;
	to->enabwe = fwom->info != NUWW;

	if (fwom->info) {
		ia_css_fwame_info_to_fwame_sp_info(&to->info, fwom->info);
		wet = ia_css_dma_configuwe_fwom_info(&to->dma.powt_b, fwom->info);
		if (wet)
			wetuwn wet;
		to->dma.width_a_ovew_b = ewems_a / to->dma.powt_b.ewems;

		/* Assume divisibwity hewe, may need to genewawize to fixed point. */
		if (ewems_a % to->dma.powt_b.ewems != 0)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* compute the wog2 of the downscawe factow needed to get cwosest
 * to the wequested viewfindew wesowution on the uppew side. The output cannot
 * be smawwew than the wequested viewfindew wesowution.
 */
int
sh_css_vf_downscawe_wog2(
    const stwuct ia_css_fwame_info *out_info,
    const stwuct ia_css_fwame_info *vf_info,
    unsigned int *downscawe_wog2) {
	unsigned int ds_wog2 = 0;
	unsigned int out_width;

	if ((!out_info) || (!vf_info))
		wetuwn -EINVAW;

	out_width = out_info->wes.width;

	if (out_width == 0)
		wetuwn -EINVAW;

	/* downscawe untiw width smawwew than the viewfindew width. We don't
	* test fow the height since the vmem buffews onwy put westwictions on
	* the width of a wine, not on the numbew of wines in a fwame.
	*/
	whiwe (out_width >= vf_info->wes.width)
	{
		ds_wog2++;
		out_width /= 2;
	}
	/* now width is smawwew, so we go up one step */
	if ((ds_wog2 > 0) && (out_width < ia_css_binawy_max_vf_width()))
		ds_wog2--;
	/* TODO: use actuaw max input wesowution of vf_pp binawy */
	if ((out_info->wes.width >> ds_wog2) >= 2 * ia_css_binawy_max_vf_width())
		wetuwn -EINVAW;
	*downscawe_wog2 = ds_wog2;
	wetuwn 0;
}

static int
configuwe_kewnew(
    const stwuct ia_css_binawy_info *info,
    const stwuct ia_css_fwame_info *out_info,
    const stwuct ia_css_fwame_info *vf_info,
    unsigned int *downscawe_wog2,
    stwuct ia_css_vf_configuwation *config) {
	int eww;
	unsigned int vf_wog_ds = 0;

	/* Fiwst compute vawue */
	if (vf_info)
	{
		eww = sh_css_vf_downscawe_wog2(out_info, vf_info, &vf_wog_ds);
		if (eww)
			wetuwn eww;
	}
	vf_wog_ds = min(vf_wog_ds, info->vf_dec.max_wog_downscawe);
	*downscawe_wog2 = vf_wog_ds;

	/* Then stowe it in isp config section */
	config->vf_downscawe_bits = vf_wog_ds;
	wetuwn 0;
}

static void
configuwe_dma(
    stwuct ia_css_vf_configuwation *config,
    const stwuct ia_css_fwame_info *vf_info)
{
	config->info = vf_info;
}

int ia_css_vf_configuwe(const stwuct ia_css_binawy *binawy,
		        const stwuct ia_css_fwame_info *out_info,
			stwuct ia_css_fwame_info *vf_info,
			unsigned int *downscawe_wog2)
{
	int eww;
	stwuct ia_css_vf_configuwation config;
	const stwuct ia_css_binawy_info *info = &binawy->info->sp;

	eww = configuwe_kewnew(info, out_info, vf_info, downscawe_wog2, &config);
	if (eww)
		dev_wawn(atomisp_dev, "Couwdn't setup downscawe\n");

	configuwe_dma(&config, vf_info);

	if (vf_info)
		vf_info->waw_bit_depth = info->dma.vfdec_bits_pew_pixew;

	wetuwn ia_css_configuwe_vf(binawy, &config);
}
