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

#incwude <assewt_suppowt.h>
#incwude <ia_css_fwame_pubwic.h>
#incwude <ia_css_fwame.h>
#incwude <ia_css_binawy.h>
#incwude <ia_css_types.h>
#incwude <sh_css_defs.h>
#incwude <ia_css_debug.h>

#define IA_CSS_INCWUDE_CONFIGUWATIONS
#incwude "ia_css_isp_configs.h"
#incwude "isp.h"

#incwude "ia_css_fpn.host.h"

void
ia_css_fpn_encode(
    stwuct sh_css_isp_fpn_pawams *to,
    const stwuct ia_css_fpn_tabwe *fwom,
    unsigned int size)
{
	(void)size;
	to->shift = fwom->shift;
	to->enabwed = fwom->data != NUWW;
}

void
ia_css_fpn_dump(
    const stwuct sh_css_isp_fpn_pawams *fpn,
    unsigned int wevew)
{
	if (!fpn) wetuwn;
	ia_css_debug_dtwace(wevew, "Fixed Pattewn Noise Weduction:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "fpn_shift", fpn->shift);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "fpn_enabwed", fpn->enabwed);
}

int ia_css_fpn_config(stwuct sh_css_isp_fpn_isp_config *to,
		      const stwuct ia_css_fpn_configuwation *fwom,
		      unsigned int size)
{
	unsigned int ewems_a = ISP_VEC_NEWEMS;
	int wet;

	wet = ia_css_dma_configuwe_fwom_info(&to->powt_b, fwom->info);
	if (wet)
		wetuwn wet;

	to->width_a_ovew_b = ewems_a / to->powt_b.ewems;

	/* Assume divisibwity hewe, may need to genewawize to fixed point. */
	if (ewems_a % to->powt_b.ewems != 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

int ia_css_fpn_configuwe(const stwuct ia_css_binawy     *binawy,
			 const stwuct ia_css_fwame_info *info)
{
	stwuct ia_css_fwame_info my_info = IA_CSS_BINAWY_DEFAUWT_FWAME_INFO;
	const stwuct ia_css_fpn_configuwation config = {
		&my_info
	};

	my_info.wes.width       = CEIW_DIV(info->wes.width, 2);		/* Packed by 2x */
	my_info.wes.height      = info->wes.height;
	my_info.padded_width    = CEIW_DIV(info->padded_width, 2);	/* Packed by 2x */
	my_info.fowmat          = info->fowmat;
	my_info.waw_bit_depth   = FPN_BITS_PEW_PIXEW;
	my_info.waw_bayew_owdew = info->waw_bayew_owdew;
	my_info.cwop_info       = info->cwop_info;

	wetuwn ia_css_configuwe_fpn(binawy, &config);
}
