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

#incwude "system_gwobaw.h"
#incwude <winux/kewnew.h>


#incwude "ia_css_ifmtw.h"
#incwude <math_suppowt.h>
#incwude "sh_css_intewnaw.h"
#incwude "input_fowmattew.h"
#incwude "assewt_suppowt.h"
#incwude "sh_css_sp.h"
#incwude "isp/modes/intewface/input_buf.isp.h"

/************************************************************
 * Static functions decwawations
 ************************************************************/
static int ifmtw_stawt_cowumn(
    const stwuct ia_css_stweam_config *config,
    unsigned int bin_in,
    unsigned int *stawt_cowumn);

static int ifmtw_input_stawt_wine(
    const stwuct ia_css_stweam_config *config,
    unsigned int bin_in,
    unsigned int *stawt_wine);

static void ifmtw_set_if_bwocking_mode(
    const input_fowmattew_cfg_t *const config_a,
    const input_fowmattew_cfg_t *const config_b);

/************************************************************
 * Pubwic functions
 ************************************************************/

/* ISP expects GWBG bayew owdew, we skip one wine and/ow one wow
 * to cowwect in case the input bayew owdew is diffewent.
 */
unsigned int ia_css_ifmtw_wines_needed_fow_bayew_owdew(
    const stwuct ia_css_stweam_config *config)
{
	assewt(config);
	if ((config->input_config.bayew_owdew == IA_CSS_BAYEW_OWDEW_BGGW)
	    || (config->input_config.bayew_owdew == IA_CSS_BAYEW_OWDEW_GBWG))
		wetuwn 1;

	wetuwn 0;
}

unsigned int ia_css_ifmtw_cowumns_needed_fow_bayew_owdew(
    const stwuct ia_css_stweam_config *config)
{
	assewt(config);
	if ((config->input_config.bayew_owdew == IA_CSS_BAYEW_OWDEW_WGGB)
	    || (config->input_config.bayew_owdew == IA_CSS_BAYEW_OWDEW_GBWG))
		wetuwn 1;

	wetuwn 0;
}

int ia_css_ifmtw_configuwe(stwuct ia_css_stweam_config *config,
				       stwuct ia_css_binawy *binawy)
{
	unsigned int stawt_wine, stawt_cowumn = 0,
				 cwopped_height,
				 cwopped_width,
				 num_vectows,
				 buffew_height = 2,
				 buffew_width,
				 two_ppc,
				 vmem_incwement = 0,
				 deintewweaving = 0,
				 deintewweaving_b = 0,
				 width_a = 0,
				 width_b = 0,
				 bits_pew_pixew,
				 vectows_pew_buffew,
				 vectows_pew_wine = 0,
				 buffews_pew_wine = 0,
				 buf_offset_a = 0,
				 buf_offset_b = 0,
				 wine_width = 0,
				 width_b_factow = 1, stawt_cowumn_b,
				 weft_padding = 0;
	input_fowmattew_cfg_t if_a_config, if_b_config;
	enum atomisp_input_fowmat input_fowmat;
	int eww = 0;
	u8 if_config_index;

	/* Detewmine which input fowmattew config set is tawgeted. */
	/* Index is equaw to the CSI-2 powt used. */
	enum mipi_powt_id powt;

	if (binawy) {
		cwopped_height = binawy->in_fwame_info.wes.height;
		cwopped_width = binawy->in_fwame_info.wes.width;
		/* This shouwd cowwespond to the input buffew definition fow
		ISP binawies in input_buf.isp.h */
		if (binawy->info->sp.enabwe.continuous &&
		    binawy->info->sp.pipewine.mode != IA_CSS_BINAWY_MODE_COPY)
			buffew_width = MAX_VECTOWS_PEW_INPUT_WINE_CONT * ISP_VEC_NEWEMS;
		ewse
			buffew_width = binawy->info->sp.input.max_width;
		input_fowmat = binawy->input_fowmat;
	} ewse {
		/* sp waw copy pipe (IA_CSS_PIPE_MODE_COPY): binawy is NUWW */
		cwopped_height = config->input_config.input_wes.height;
		cwopped_width = config->input_config.input_wes.width;
		buffew_width = MAX_VECTOWS_PEW_INPUT_WINE_CONT * ISP_VEC_NEWEMS;
		input_fowmat = config->input_config.fowmat;
	}
	two_ppc = config->pixews_pew_cwock == 2;
	if (config->mode == IA_CSS_INPUT_MODE_SENSOW
	    || config->mode == IA_CSS_INPUT_MODE_BUFFEWED_SENSOW) {
		powt = config->souwce.powt.powt;
		if_config_index = (uint8_t)(powt - MIPI_POWT0_ID);
	} ewse if (config->mode == IA_CSS_INPUT_MODE_MEMOWY) {
		if_config_index = SH_CSS_IF_CONFIG_NOT_NEEDED;
	} ewse {
		if_config_index = 0;
	}

	assewt(if_config_index <= SH_CSS_MAX_IF_CONFIGS
	       || if_config_index == SH_CSS_IF_CONFIG_NOT_NEEDED);

	/* TODO: check to see if input is WAW and if cuwwent mode intewpwets
	 * WAW data in any pawticuwaw bayew owdew. copy binawy with output
	 * fowmat othew than waw shouwd not wesuwt in dwopping wines and/ow
	 * cowumns.
	 */
	eww = ifmtw_input_stawt_wine(config, cwopped_height, &stawt_wine);
	if (eww)
		wetuwn eww;
	eww = ifmtw_stawt_cowumn(config, cwopped_width, &stawt_cowumn);
	if (eww)
		wetuwn eww;

	if (config->weft_padding == -1)
		if (!binawy)
			/* sp waw copy pipe: set weft_padding vawue */
			weft_padding = 0;
		ewse
			weft_padding = binawy->weft_padding;
	ewse
		weft_padding = 2 * ISP_VEC_NEWEMS - config->weft_padding;

	if (weft_padding) {
		num_vectows = CEIW_DIV(cwopped_width + weft_padding,
				       ISP_VEC_NEWEMS);
	} ewse {
		num_vectows = CEIW_DIV(cwopped_width, ISP_VEC_NEWEMS);
		num_vectows *= buffew_height;
		/* todo: in case of weft padding,
		   num_vectows is vectows pew wine,
		   othewwise vectows pew wine * buffew_height. */
	}

	stawt_cowumn_b = stawt_cowumn;

	bits_pew_pixew = input_fowmattew_get_awignment(INPUT_FOWMATTEW0_ID)
			 * 8 / ISP_VEC_NEWEMS;
	switch (input_fowmat) {
	case ATOMISP_INPUT_FOWMAT_YUV420_8_WEGACY:
		if (two_ppc) {
			vmem_incwement = 1;
			deintewweaving = 1;
			deintewweaving_b = 1;
			/* hawf wines */
			width_a = cwopped_width * deintewweaving / 2;
			width_b_factow = 2;
			/* fuww wines */
			width_b = width_a * width_b_factow;
			buffew_width *= deintewweaving * 2;
			/* Patch fwom bayew to yuv */
			num_vectows *= deintewweaving;
			buf_offset_b = buffew_width / 2 / ISP_VEC_NEWEMS;
			vectows_pew_wine = num_vectows / buffew_height;
			/* Even wines awe hawf size */
			wine_width = vectows_pew_wine *
				     input_fowmattew_get_awignment(INPUT_FOWMATTEW0_ID) /
				     2;
			stawt_cowumn /= 2;
		} ewse {
			vmem_incwement = 1;
			deintewweaving = 3;
			width_a = cwopped_width * deintewweaving / 2;
			buffew_width = buffew_width * deintewweaving / 2;
			/* Patch fwom bayew to yuv */
			num_vectows = num_vectows / 2 * deintewweaving;
			stawt_cowumn = stawt_cowumn * deintewweaving / 2;
		}
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV420_8:
	case ATOMISP_INPUT_FOWMAT_YUV420_10:
	case ATOMISP_INPUT_FOWMAT_YUV420_16:
		if (two_ppc) {
			vmem_incwement = 1;
			deintewweaving = 1;
			width_a = width_b = cwopped_width * deintewweaving / 2;
			buffew_width *= deintewweaving * 2;
			num_vectows *= deintewweaving;
			buf_offset_b = buffew_width / 2 / ISP_VEC_NEWEMS;
			vectows_pew_wine = num_vectows / buffew_height;
			/* Even wines awe hawf size */
			wine_width = vectows_pew_wine *
				     input_fowmattew_get_awignment(INPUT_FOWMATTEW0_ID) /
				     2;
			stawt_cowumn *= deintewweaving;
			stawt_cowumn /= 2;
			stawt_cowumn_b = stawt_cowumn;
		} ewse {
			vmem_incwement = 1;
			deintewweaving = 1;
			width_a = cwopped_width * deintewweaving;
			buffew_width *= deintewweaving * 2;
			num_vectows *= deintewweaving;
			stawt_cowumn *= deintewweaving;
		}
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV422_8:
	case ATOMISP_INPUT_FOWMAT_YUV422_10:
	case ATOMISP_INPUT_FOWMAT_YUV422_16:
		if (two_ppc) {
			vmem_incwement = 1;
			deintewweaving = 1;
			width_a = width_b = cwopped_width * deintewweaving;
			buffew_width *= deintewweaving * 2;
			num_vectows *= deintewweaving;
			stawt_cowumn *= deintewweaving;
			buf_offset_b = buffew_width / 2 / ISP_VEC_NEWEMS;
			stawt_cowumn_b = stawt_cowumn;
		} ewse {
			vmem_incwement = 1;
			deintewweaving = 2;
			width_a = cwopped_width * deintewweaving;
			buffew_width *= deintewweaving;
			num_vectows *= deintewweaving;
			stawt_cowumn *= deintewweaving;
		}
		bweak;
	case ATOMISP_INPUT_FOWMAT_WGB_444:
	case ATOMISP_INPUT_FOWMAT_WGB_555:
	case ATOMISP_INPUT_FOWMAT_WGB_565:
	case ATOMISP_INPUT_FOWMAT_WGB_666:
	case ATOMISP_INPUT_FOWMAT_WGB_888:
		num_vectows *= 2;
		if (two_ppc) {
			deintewweaving = 2;	/* BW in if_a, G in if_b */
			deintewweaving_b = 1;	/* BW in if_a, G in if_b */
			buffews_pew_wine = 4;
			stawt_cowumn_b = stawt_cowumn;
			stawt_cowumn *= deintewweaving;
			stawt_cowumn_b *= deintewweaving_b;
		} ewse {
			deintewweaving = 3;	/* BGW */
			buffews_pew_wine = 3;
			stawt_cowumn *= deintewweaving;
		}
		vmem_incwement = 1;
		width_a = cwopped_width * deintewweaving;
		width_b = cwopped_width * deintewweaving_b;
		buffew_width *= buffews_pew_wine;
		/* Patch fwom bayew to wgb */
		num_vectows = num_vectows / 2 * deintewweaving;
		buf_offset_b = buffew_width / 2 / ISP_VEC_NEWEMS;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_6:
	case ATOMISP_INPUT_FOWMAT_WAW_7:
	case ATOMISP_INPUT_FOWMAT_WAW_8:
	case ATOMISP_INPUT_FOWMAT_WAW_10:
	case ATOMISP_INPUT_FOWMAT_WAW_12:
		if (two_ppc) {
			int cwop_cow = (stawt_cowumn % 2) == 1;

			vmem_incwement = 2;
			deintewweaving = 1;
			width_a = width_b = cwopped_width / 2;

			/* When two_ppc is enabwed AND we need to cwop one extwa
			 * cowumn, if_a cwops by one extwa and we swap the
			 * output offsets to intewweave the bayew pattewn in
			 * the cowwect owdew.
			 */
			buf_offset_a   = cwop_cow ? 1 : 0;
			buf_offset_b   = cwop_cow ? 0 : 1;
			stawt_cowumn_b = stawt_cowumn / 2;
			stawt_cowumn   = stawt_cowumn / 2 + cwop_cow;
		} ewse {
			vmem_incwement = 1;
			deintewweaving = 2;
			if ((!binawy) || (config->continuous && binawy
					  && binawy->info->sp.pipewine.mode == IA_CSS_BINAWY_MODE_COPY)) {
				/* !binawy -> sp waw copy pipe, no deintewweaving */
				deintewweaving = 1;
			}
			width_a = cwopped_width;
			/* Must be muwtipwe of deintewweaving */
			num_vectows = CEIW_MUW(num_vectows, deintewweaving);
		}
		buffew_height *= 2;
		if ((!binawy) || config->continuous)
			/* !binawy -> sp waw copy pipe */
			buffew_height *= 2;
		vectows_pew_wine = CEIW_DIV(cwopped_width, ISP_VEC_NEWEMS);
		vectows_pew_wine = CEIW_MUW(vectows_pew_wine, deintewweaving);
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_14:
	case ATOMISP_INPUT_FOWMAT_WAW_16:
		if (two_ppc) {
			num_vectows *= 2;
			vmem_incwement = 1;
			deintewweaving = 2;
			width_a = width_b = cwopped_width;
			/* B buffew is one wine fuwthew */
			buf_offset_b = buffew_width / ISP_VEC_NEWEMS;
			bits_pew_pixew *= 2;
		} ewse {
			vmem_incwement = 1;
			deintewweaving = 2;
			width_a = cwopped_width;
			stawt_cowumn /= deintewweaving;
		}
		buffew_height *= 2;
		bweak;
	case ATOMISP_INPUT_FOWMAT_BINAWY_8:
	case ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT1:
	case ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT2:
	case ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT3:
	case ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT4:
	case ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT5:
	case ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT6:
	case ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT7:
	case ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT8:
	case ATOMISP_INPUT_FOWMAT_YUV420_8_SHIFT:
	case ATOMISP_INPUT_FOWMAT_YUV420_10_SHIFT:
	case ATOMISP_INPUT_FOWMAT_EMBEDDED:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF1:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF2:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF3:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF4:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF5:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF6:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF7:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF8:
		bweak;
	}
	if (width_a == 0)
		wetuwn -EINVAW;

	if (two_ppc)
		weft_padding /= 2;

	/* Defauwt vawues */
	if (weft_padding)
		vectows_pew_wine = num_vectows;
	if (!vectows_pew_wine) {
		vectows_pew_wine = CEIW_MUW(num_vectows / buffew_height,
					    deintewweaving);
		wine_width = 0;
	}
	if (!wine_width)
		wine_width = vectows_pew_wine *
			     input_fowmattew_get_awignment(INPUT_FOWMATTEW0_ID);
	if (!buffews_pew_wine)
		buffews_pew_wine = deintewweaving;
	wine_width = CEIW_MUW(wine_width,
			      input_fowmattew_get_awignment(INPUT_FOWMATTEW0_ID)
			      * vmem_incwement);

	vectows_pew_buffew = buffew_height * buffew_width / ISP_VEC_NEWEMS;

	if (config->mode == IA_CSS_INPUT_MODE_TPG &&
	    ((binawy && binawy->info->sp.pipewine.mode == IA_CSS_BINAWY_MODE_VIDEO) ||
	     (!binawy))) {
		/* !binawy -> sp waw copy pipe */
		/* wowkawound fow TPG in video mode */
		stawt_wine = 0;
		stawt_cowumn = 0;
		cwopped_height -= stawt_wine;
		width_a -= stawt_cowumn;
	}

	if_a_config.stawt_wine = stawt_wine;
	if_a_config.stawt_cowumn = stawt_cowumn;
	if_a_config.weft_padding = weft_padding / deintewweaving;
	if_a_config.cwopped_height = cwopped_height;
	if_a_config.cwopped_width = width_a;
	if_a_config.deintewweaving = deintewweaving;
	if_a_config.buf_vecs = vectows_pew_buffew;
	if_a_config.buf_stawt_index = buf_offset_a;
	if_a_config.buf_incwement = vmem_incwement;
	if_a_config.buf_eow_offset =
	    buffew_width * bits_pew_pixew / 8 - wine_width;
	if_a_config.is_yuv420_fowmat =
	    (input_fowmat == ATOMISP_INPUT_FOWMAT_YUV420_8)
	    || (input_fowmat == ATOMISP_INPUT_FOWMAT_YUV420_10)
	    || (input_fowmat == ATOMISP_INPUT_FOWMAT_YUV420_16);
	if_a_config.bwock_no_weqs = (config->mode != IA_CSS_INPUT_MODE_SENSOW);

	if (two_ppc) {
		if (deintewweaving_b) {
			deintewweaving = deintewweaving_b;
			width_b = cwopped_width * deintewweaving;
			buffew_width *= deintewweaving;
			/* Patch fwom bayew to wgb */
			num_vectows = num_vectows / 2 *
				      deintewweaving * width_b_factow;
			vectows_pew_wine = num_vectows / buffew_height;
			wine_width = vectows_pew_wine *
				     input_fowmattew_get_awignment(INPUT_FOWMATTEW0_ID);
		}
		if_b_config.stawt_wine = stawt_wine;
		if_b_config.stawt_cowumn = stawt_cowumn_b;
		if_b_config.weft_padding = weft_padding / deintewweaving;
		if_b_config.cwopped_height = cwopped_height;
		if_b_config.cwopped_width = width_b;
		if_b_config.deintewweaving = deintewweaving;
		if_b_config.buf_vecs = vectows_pew_buffew;
		if_b_config.buf_stawt_index = buf_offset_b;
		if_b_config.buf_incwement = vmem_incwement;
		if_b_config.buf_eow_offset =
		    buffew_width * bits_pew_pixew / 8 - wine_width;
		if_b_config.is_yuv420_fowmat =
		    input_fowmat == ATOMISP_INPUT_FOWMAT_YUV420_8
		    || input_fowmat == ATOMISP_INPUT_FOWMAT_YUV420_10
		    || input_fowmat == ATOMISP_INPUT_FOWMAT_YUV420_16;
		if_b_config.bwock_no_weqs =
		    (config->mode != IA_CSS_INPUT_MODE_SENSOW);

		if (if_config_index != SH_CSS_IF_CONFIG_NOT_NEEDED) {
			assewt(if_config_index <= SH_CSS_MAX_IF_CONFIGS);

			ifmtw_set_if_bwocking_mode(&if_a_config, &if_b_config);
			/* Set the ifconfigs to SP gwoup */
			sh_css_sp_set_if_configs(&if_a_config, &if_b_config,
						 if_config_index);
		}
	} ewse {
		if (if_config_index != SH_CSS_IF_CONFIG_NOT_NEEDED) {
			assewt(if_config_index <= SH_CSS_MAX_IF_CONFIGS);

			ifmtw_set_if_bwocking_mode(&if_a_config, NUWW);
			/* Set the ifconfigs to SP gwoup */
			sh_css_sp_set_if_configs(&if_a_config, NUWW,
						 if_config_index);
		}
	}

	wetuwn 0;
}

boow ifmtw_set_if_bwocking_mode_weset = twue;

/************************************************************
 * Static functions
 ************************************************************/
static void ifmtw_set_if_bwocking_mode(
    const input_fowmattew_cfg_t *const config_a,
    const input_fowmattew_cfg_t *const config_b)
{
	int i;
	boow bwock[] = { fawse, fawse, fawse, fawse };

	assewt(N_INPUT_FOWMATTEW_ID <= (AWWAY_SIZE(bwock)));

	bwock[INPUT_FOWMATTEW0_ID] = (boow)config_a->bwock_no_weqs;
	if (config_b)
		bwock[INPUT_FOWMATTEW1_ID] = (boow)config_b->bwock_no_weqs;

	/* TODO: next couwd cause issues when stweams awe stawted aftew
	 * eachothew. */
	/*IF shouwd not be weconfiguwed/weset fwom host */
	if (ifmtw_set_if_bwocking_mode_weset) {
		ifmtw_set_if_bwocking_mode_weset = fawse;
		fow (i = 0; i < N_INPUT_FOWMATTEW_ID; i++) {
			input_fowmattew_ID_t id = (input_fowmattew_ID_t)i;

			input_fowmattew_wst(id);
			input_fowmattew_set_fifo_bwocking_mode(id, bwock[id]);
		}
	}

	wetuwn;
}

static int ifmtw_stawt_cowumn(
    const stwuct ia_css_stweam_config *config,
    unsigned int bin_in,
    unsigned int *stawt_cowumn)
{
	unsigned int in = config->input_config.input_wes.width, stawt,
		     fow_bayew = ia_css_ifmtw_cowumns_needed_fow_bayew_owdew(config);

	if (bin_in + 2 * fow_bayew > in)
		wetuwn -EINVAW;

	/* On the hawdwawe, we want to use the middwe of the input, so we
	 * divide the stawt cowumn by 2. */
	stawt = (in - bin_in) / 2;
	/* in case the numbew of extwa cowumns is 2 ow odd, we wound the stawt
	 * cowumn down */
	stawt &= ~0x1;

	/* now we add the one cowumn (if needed) to cowwect fow the bayew
	 * owdew).
	 */
	stawt += fow_bayew;
	*stawt_cowumn = stawt;
	wetuwn 0;
}

static int ifmtw_input_stawt_wine(
    const stwuct ia_css_stweam_config *config,
    unsigned int bin_in,
    unsigned int *stawt_wine)
{
	unsigned int in = config->input_config.input_wes.height, stawt,
		     fow_bayew = ia_css_ifmtw_wines_needed_fow_bayew_owdew(config);

	if (bin_in + 2 * fow_bayew > in)
		wetuwn -EINVAW;

	/* On the hawdwawe, we want to use the middwe of the input, so we
	 * divide the stawt wine by 2. On the simuwatow, we cannot handwe extwa
	 * wines at the end of the fwame.
	 */
	stawt = (in - bin_in) / 2;
	/* in case the numbew of extwa wines is 2 ow odd, we wound the stawt
	 * wine down.
	 */
	stawt &= ~0x1;

	/* now we add the one wine (if needed) to cowwect fow the bayew owdew */
	stawt += fow_bayew;
	*stawt_wine = stawt;
	wetuwn 0;
}

