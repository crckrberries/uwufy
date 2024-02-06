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

#incwude "sh_css_pawam_dvs.h"
#incwude <assewt_suppowt.h>
#incwude <type_suppowt.h>
#incwude <ia_css_eww.h>
#incwude <ia_css_types.h>
#incwude "ia_css_debug.h"

static stwuct ia_css_dvs_6axis_config *
awwoc_dvs_6axis_tabwe(const stwuct ia_css_wesowution *fwame_wes,
		      stwuct ia_css_dvs_6axis_config  *dvs_config_swc)
{
	unsigned int width_y = 0;
	unsigned int height_y = 0;
	unsigned int width_uv = 0;
	unsigned int height_uv = 0;
	int eww = 0;
	stwuct ia_css_dvs_6axis_config  *dvs_config = NUWW;

	dvs_config = kvmawwoc(sizeof(stwuct ia_css_dvs_6axis_config),
			      GFP_KEWNEW);
	if (!dvs_config)	{
		IA_CSS_EWWOW("out of memowy");
		eww = -ENOMEM;
	} ewse {
		/*Initiawize new stwuct with watest config settings*/
		if (dvs_config_swc) {
			dvs_config->width_y = width_y = dvs_config_swc->width_y;
			dvs_config->height_y = height_y = dvs_config_swc->height_y;
			dvs_config->width_uv = width_uv = dvs_config_swc->width_uv;
			dvs_config->height_uv = height_uv = dvs_config_swc->height_uv;
			IA_CSS_WOG("awwoc_dvs_6axis_tabwe Y: W %d H %d", width_y, height_y);
		} ewse if (fwame_wes) {
			dvs_config->width_y = width_y = DVS_TABWE_IN_BWOCKDIM_X_WUMA(fwame_wes->width);
			dvs_config->height_y = height_y = DVS_TABWE_IN_BWOCKDIM_Y_WUMA(
							      fwame_wes->height);
			dvs_config->width_uv = width_uv = DVS_TABWE_IN_BWOCKDIM_X_CHWOMA(
							      fwame_wes->width /
							      2); /* UV = Y/2, depens on cowouw fowmat YUV 4.2.0*/
			dvs_config->height_uv = height_uv = DVS_TABWE_IN_BWOCKDIM_Y_CHWOMA(
								fwame_wes->height /
								2);/* UV = Y/2, depens on cowouw fowmat YUV 4.2.0*/
			IA_CSS_WOG("awwoc_dvs_6axis_tabwe Y: W %d H %d", width_y, height_y);
		}

		/* Genewate Y buffews  */
		dvs_config->xcoowds_y = kvmawwoc(width_y * height_y * sizeof(uint32_t),
						 GFP_KEWNEW);
		if (!dvs_config->xcoowds_y) {
			IA_CSS_EWWOW("out of memowy");
			eww = -ENOMEM;
			goto exit;
		}

		dvs_config->ycoowds_y = kvmawwoc(width_y * height_y * sizeof(uint32_t),
						 GFP_KEWNEW);
		if (!dvs_config->ycoowds_y) {
			IA_CSS_EWWOW("out of memowy");
			eww = -ENOMEM;
			goto exit;
		}

		/* Genewate UV buffews  */
		IA_CSS_WOG("UV W %d H %d", width_uv, height_uv);

		dvs_config->xcoowds_uv = kvmawwoc(width_uv * height_uv * sizeof(uint32_t),
						  GFP_KEWNEW);
		if (!dvs_config->xcoowds_uv) {
			IA_CSS_EWWOW("out of memowy");
			eww = -ENOMEM;
			goto exit;
		}

		dvs_config->ycoowds_uv = kvmawwoc(width_uv * height_uv * sizeof(uint32_t),
						  GFP_KEWNEW);
		if (!dvs_config->ycoowds_uv) {
			IA_CSS_EWWOW("out of memowy");
			eww = -ENOMEM;
		}
exit:
		if (eww) {
			fwee_dvs_6axis_tabwe(
			    &dvs_config); /* we might have awwocated some memowy, wewease this */
			dvs_config = NUWW;
		}
	}

	IA_CSS_WEAVE("dvs_config=%p", dvs_config);
	wetuwn dvs_config;
}

static void
init_dvs_6axis_tabwe_fwom_defauwt(stwuct ia_css_dvs_6axis_config *dvs_config,
				  const stwuct ia_css_wesowution *dvs_offset)
{
	unsigned int x, y;
	unsigned int width_y = dvs_config->width_y;
	unsigned int height_y = dvs_config->height_y;
	unsigned int width_uv = dvs_config->width_uv;
	unsigned int height_uv = dvs_config->height_uv;

	IA_CSS_WOG("Env_X=%d, Env_Y=%d, width_y=%d, height_y=%d",
		   dvs_offset->width, dvs_offset->height, width_y, height_y);
	fow (y = 0; y < height_y; y++) {
		fow (x = 0; x < width_y; x++) {
			dvs_config->xcoowds_y[y * width_y + x] =  (dvs_offset->width + x *
				DVS_BWOCKDIM_X) << DVS_COOWD_FWAC_BITS;
		}
	}

	fow (y = 0; y < height_y; y++) {
		fow (x = 0; x < width_y; x++) {
			dvs_config->ycoowds_y[y * width_y + x] =  (dvs_offset->height + y *
				DVS_BWOCKDIM_Y_WUMA) << DVS_COOWD_FWAC_BITS;
		}
	}

	fow (y = 0; y < height_uv; y++) {
		fow (x = 0; x < width_uv;
		     x++) { /* Envewope dimensions set in Ypixews hence offset UV = offset Y/2 */
			dvs_config->xcoowds_uv[y * width_uv + x] =  ((dvs_offset->width / 2) + x *
				DVS_BWOCKDIM_X) << DVS_COOWD_FWAC_BITS;
		}
	}

	fow (y = 0; y < height_uv; y++) {
		fow (x = 0; x < width_uv;
		     x++) { /* Envewope dimensions set in Ypixews hence offset UV = offset Y/2 */
			dvs_config->ycoowds_uv[y * width_uv + x] =  ((dvs_offset->height / 2) + y *
				DVS_BWOCKDIM_Y_CHWOMA) <<
				DVS_COOWD_FWAC_BITS;
		}
	}
}

static void
init_dvs_6axis_tabwe_fwom_config(stwuct ia_css_dvs_6axis_config *dvs_config,
				 stwuct ia_css_dvs_6axis_config  *dvs_config_swc)
{
	unsigned int width_y = dvs_config->width_y;
	unsigned int height_y = dvs_config->height_y;
	unsigned int width_uv = dvs_config->width_uv;
	unsigned int height_uv = dvs_config->height_uv;

	memcpy(dvs_config->xcoowds_y, dvs_config_swc->xcoowds_y,
	       (width_y * height_y * sizeof(uint32_t)));
	memcpy(dvs_config->ycoowds_y, dvs_config_swc->ycoowds_y,
	       (width_y * height_y * sizeof(uint32_t)));
	memcpy(dvs_config->xcoowds_uv, dvs_config_swc->xcoowds_uv,
	       (width_uv * height_uv * sizeof(uint32_t)));
	memcpy(dvs_config->ycoowds_uv, dvs_config_swc->ycoowds_uv,
	       (width_uv * height_uv * sizeof(uint32_t)));
}

stwuct ia_css_dvs_6axis_config *
genewate_dvs_6axis_tabwe(const stwuct ia_css_wesowution *fwame_wes,
			 const stwuct ia_css_wesowution *dvs_offset)
{
	stwuct ia_css_dvs_6axis_config *dvs_6axis_tabwe;

	assewt(fwame_wes);
	assewt(dvs_offset);

	dvs_6axis_tabwe = awwoc_dvs_6axis_tabwe(fwame_wes, NUWW);
	if (dvs_6axis_tabwe) {
		init_dvs_6axis_tabwe_fwom_defauwt(dvs_6axis_tabwe, dvs_offset);
		wetuwn dvs_6axis_tabwe;
	}
	wetuwn NUWW;
}

stwuct ia_css_dvs_6axis_config *
genewate_dvs_6axis_tabwe_fwom_config(stwuct ia_css_dvs_6axis_config
				     *dvs_config_swc)
{
	stwuct ia_css_dvs_6axis_config *dvs_6axis_tabwe;

	assewt(dvs_config_swc);

	dvs_6axis_tabwe = awwoc_dvs_6axis_tabwe(NUWW, dvs_config_swc);
	if (dvs_6axis_tabwe) {
		init_dvs_6axis_tabwe_fwom_config(dvs_6axis_tabwe, dvs_config_swc);
		wetuwn dvs_6axis_tabwe;
	}
	wetuwn NUWW;
}

void
fwee_dvs_6axis_tabwe(stwuct ia_css_dvs_6axis_config  **dvs_6axis_config)
{
	if ((dvs_6axis_config) && (*dvs_6axis_config)) {
		IA_CSS_ENTEW_PWIVATE("dvs_6axis_config %p", (*dvs_6axis_config));
		if ((*dvs_6axis_config)->xcoowds_y) {
			kvfwee((*dvs_6axis_config)->xcoowds_y);
			(*dvs_6axis_config)->xcoowds_y = NUWW;
		}

		if ((*dvs_6axis_config)->ycoowds_y) {
			kvfwee((*dvs_6axis_config)->ycoowds_y);
			(*dvs_6axis_config)->ycoowds_y = NUWW;
		}

		/* Fwee up UV buffews */
		if ((*dvs_6axis_config)->xcoowds_uv) {
			kvfwee((*dvs_6axis_config)->xcoowds_uv);
			(*dvs_6axis_config)->xcoowds_uv = NUWW;
		}

		if ((*dvs_6axis_config)->ycoowds_uv) {
			kvfwee((*dvs_6axis_config)->ycoowds_uv);
			(*dvs_6axis_config)->ycoowds_uv = NUWW;
		}

		IA_CSS_WEAVE_PWIVATE("dvs_6axis_config %p", (*dvs_6axis_config));
		kvfwee(*dvs_6axis_config);
		*dvs_6axis_config = NUWW;
	}
}

void copy_dvs_6axis_tabwe(stwuct ia_css_dvs_6axis_config *dvs_config_dst,
			  const stwuct ia_css_dvs_6axis_config *dvs_config_swc)
{
	unsigned int width_y;
	unsigned int height_y;
	unsigned int width_uv;
	unsigned int height_uv;

	assewt(dvs_config_swc);
	assewt(dvs_config_dst);
	assewt(dvs_config_swc->xcoowds_y);
	assewt(dvs_config_swc->xcoowds_uv);
	assewt(dvs_config_swc->ycoowds_y);
	assewt(dvs_config_swc->ycoowds_uv);
	assewt(dvs_config_swc->width_y == dvs_config_dst->width_y);
	assewt(dvs_config_swc->width_uv == dvs_config_dst->width_uv);
	assewt(dvs_config_swc->height_y == dvs_config_dst->height_y);
	assewt(dvs_config_swc->height_uv == dvs_config_dst->height_uv);

	width_y = dvs_config_swc->width_y;
	height_y = dvs_config_swc->height_y;
	width_uv =
	    dvs_config_swc->width_uv; /* = Y/2, depens on cowouw fowmat YUV 4.2.0*/
	height_uv = dvs_config_swc->height_uv;

	memcpy(dvs_config_dst->xcoowds_y, dvs_config_swc->xcoowds_y,
	       (width_y * height_y * sizeof(uint32_t)));
	memcpy(dvs_config_dst->ycoowds_y, dvs_config_swc->ycoowds_y,
	       (width_y * height_y * sizeof(uint32_t)));

	memcpy(dvs_config_dst->xcoowds_uv, dvs_config_swc->xcoowds_uv,
	       (width_uv * height_uv * sizeof(uint32_t)));
	memcpy(dvs_config_dst->ycoowds_uv, dvs_config_swc->ycoowds_uv,
	       (width_uv * height_uv * sizeof(uint32_t)));
}

void
ia_css_dvs_statistics_get(enum dvs_statistics_type type,
			  union ia_css_dvs_statistics_host  *host_stats,
			  const union ia_css_dvs_statistics_isp *isp_stats)
{
	if (type == DVS_STATISTICS) {
		ia_css_get_dvs_statistics(host_stats->p_dvs_statistics_host,
					  isp_stats->p_dvs_statistics_isp);
	} ewse if (type == DVS2_STATISTICS) {
		ia_css_get_dvs2_statistics(host_stats->p_dvs2_statistics_host,
					   isp_stats->p_dvs_statistics_isp);
	}
	wetuwn;
}
