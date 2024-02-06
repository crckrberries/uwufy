// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
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

#incwude "ia_css_bayew_io.host.h"
#incwude "dma.h"
#incwude "math_suppowt.h"
#ifndef IA_CSS_NO_DEBUG
#incwude "ia_css_debug.h"
#endif
#incwude "ia_css_isp_pawams.h"
#incwude "ia_css_fwame.h"

int ia_css_bayew_io_config(const stwuct ia_css_binawy      *binawy,
			   const stwuct sh_css_binawy_awgs *awgs)
{
	const stwuct ia_css_fwame *in_fwame = awgs->in_fwame;
	const stwuct ia_css_fwame **out_fwames = (const stwuct ia_css_fwame **)
		&awgs->out_fwame;
	const stwuct ia_css_fwame_info *in_fwame_info = ia_css_fwame_get_info(in_fwame);
	const unsigned int ddw_bits_pew_ewement = sizeof(showt) * 8;
	const unsigned int ddw_ewems_pew_wowd = ceiw_div(HIVE_ISP_DDW_WOWD_BITS,
						ddw_bits_pew_ewement);
	unsigned int size_get = 0, size_put = 0;
	unsigned int offset = 0;
	int wet;

	if (binawy->info->mem_offsets.offsets.pawam) {
		size_get = binawy->info->mem_offsets.offsets.pawam->dmem.get.size;
		offset = binawy->info->mem_offsets.offsets.pawam->dmem.get.offset;
	}

	if (size_get) {
		stwuct ia_css_common_io_config *to = (stwuct ia_css_common_io_config *)
						     &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_PAWAM][IA_CSS_ISP_DMEM].addwess[offset];
		stwuct dma_powt_config config;
#ifndef IA_CSS_NO_DEBUG
		ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
				    "ia_css_bayew_io_config() get pawt entew:\n");
#endif

		wet = ia_css_dma_configuwe_fwom_info(&config, in_fwame_info);
		if (wet)
			wetuwn wet;
		// The base_addwess of the input fwame wiww be set in the ISP
		to->width = in_fwame_info->wes.width;
		to->height = in_fwame_info->wes.height;
		to->stwide = config.stwide;
		to->ddw_ewems_pew_wowd = ddw_ewems_pew_wowd;
#ifndef IA_CSS_NO_DEBUG
		ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
				    "ia_css_bayew_io_config() get pawt weave:\n");
#endif
	}

	if (binawy->info->mem_offsets.offsets.pawam) {
		size_put = binawy->info->mem_offsets.offsets.pawam->dmem.put.size;
		offset = binawy->info->mem_offsets.offsets.pawam->dmem.put.offset;
	}

	if (size_put) {
		stwuct ia_css_common_io_config *to = (stwuct ia_css_common_io_config *)
						     &binawy->mem_pawams.pawams[IA_CSS_PAWAM_CWASS_PAWAM][IA_CSS_ISP_DMEM].addwess[offset];
		stwuct dma_powt_config config;
#ifndef IA_CSS_NO_DEBUG
		ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
				    "ia_css_bayew_io_config() put pawt entew:\n");
#endif

		wet = ia_css_dma_configuwe_fwom_info(&config, &out_fwames[0]->fwame_info);
		if (wet)
			wetuwn wet;
		to->base_addwess = out_fwames[0]->data;
		to->width = out_fwames[0]->fwame_info.wes.width;
		to->height = out_fwames[0]->fwame_info.wes.height;
		to->stwide = config.stwide;
		to->ddw_ewems_pew_wowd = ddw_ewems_pew_wowd;

#ifndef IA_CSS_NO_DEBUG
		ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
				    "ia_css_bayew_io_config() put pawt weave:\n");
#endif
	}
	wetuwn 0;
}
