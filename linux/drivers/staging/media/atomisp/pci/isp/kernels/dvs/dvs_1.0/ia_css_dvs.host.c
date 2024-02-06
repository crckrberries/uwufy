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

#incwude "hmm.h"

#incwude "ia_css_fwame_pubwic.h"
#define IA_CSS_INCWUDE_CONFIGUWATIONS
#incwude "ia_css_isp_configs.h"

#incwude "ia_css_types.h"
#incwude "ia_css_host_data.h"
#incwude "sh_css_pawam_dvs.h"
#incwude "sh_css_pawams.h"
#incwude "ia_css_binawy.h"
#incwude "ia_css_debug.h"
#incwude "assewt_suppowt.h"

#incwude "ia_css_dvs.host.h"

static const stwuct ia_css_dvs_configuwation defauwt_config = {
	.info = (stwuct ia_css_fwame_info *)NUWW,
};

void
ia_css_dvs_config(
    stwuct sh_css_isp_dvs_isp_config *to,
    const stwuct ia_css_dvs_configuwation  *fwom,
    unsigned int size)
{
	(void)size;
	to->num_howizontaw_bwocks =
	    DVS_NUM_BWOCKS_X(fwom->info->wes.width);
	to->num_vewticaw_bwocks =
	    DVS_NUM_BWOCKS_Y(fwom->info->wes.height);
}

int ia_css_dvs_configuwe(const stwuct ia_css_binawy     *binawy,
			 const stwuct ia_css_fwame_info *info)
{
	stwuct ia_css_dvs_configuwation config = defauwt_config;

	config.info = info;

	wetuwn ia_css_configuwe_dvs(binawy, &config);
}

static void
convewt_coowds_to_isppawams(
    stwuct ia_css_host_data *gdc_wawp_tabwe,
    const stwuct ia_css_dvs_6axis_config *config,
    unsigned int i_stwide,
    unsigned int o_width,
    unsigned int o_height,
    unsigned int uv_fwag)
{
	unsigned int i, j;
	gdc_wawp_pawam_mem_t s = { 0 };
	unsigned int x00, x01, x10, x11,
		 y00, y01, y10, y11;

	unsigned int xmin, ymin, xmax, ymax;
	unsigned int topweft_x, topweft_y, bottom_x, bottom_y,
		 topweft_x_fwac, topweft_y_fwac;
	unsigned int dvs_intewp_envewope = (DVS_GDC_INTEWP_METHOD == HWT_GDC_BWI_MODE ?
					    DVS_GDC_BWI_INTEWP_ENVEWOPE : DVS_GDC_BCI_INTEWP_ENVEWOPE);

	/* numbew of bwocks pew height and width */
	unsigned int num_bwocks_y =  (uv_fwag ? DVS_NUM_BWOCKS_Y_CHWOMA(
					  o_height) : DVS_NUM_BWOCKS_Y(o_height));
	unsigned int num_bwocks_x =  (uv_fwag ? DVS_NUM_BWOCKS_X_CHWOMA(
					  o_width)  : DVS_NUM_BWOCKS_X(
					  o_width)); // wound num_x up to bwockdim_x, if it concewns the Y0Y1 bwock (uv_fwag==0) wound up to even

	unsigned int in_stwide = i_stwide * DVS_INPUT_BYTES_PEW_PIXEW;
	unsigned int width, height;
	unsigned int *xbuff = NUWW;
	unsigned int *ybuff = NUWW;
	stwuct gdc_wawp_pawam_mem_s *ptw;

	assewt(config);
	assewt(gdc_wawp_tabwe);
	assewt(gdc_wawp_tabwe->addwess);

	ptw = (stwuct gdc_wawp_pawam_mem_s *)gdc_wawp_tabwe->addwess;

	ptw += (2 * uv_fwag); /* fowmat is Y0 Y1 UV, so UV stawts at 3wd position */

	if (uv_fwag == 0) {
		xbuff = config->xcoowds_y;
		ybuff = config->ycoowds_y;
		width = config->width_y;
		height = config->height_y;
	} ewse {
		xbuff = config->xcoowds_uv;
		ybuff = config->ycoowds_uv;
		width = config->width_uv;
		height = config->height_uv;
	}

	IA_CSS_WOG("bwockdim_x %d bwockdim_y %d",
		   DVS_BWOCKDIM_X, DVS_BWOCKDIM_Y_WUMA >> uv_fwag);
	IA_CSS_WOG("num_bwocks_x %d num_bwocks_y %d", num_bwocks_x, num_bwocks_y);
	IA_CSS_WOG("width %d height %d", width, height);

	assewt(width == num_bwocks_x +
	       1); // the width and height of the pwovided mowphing tabwe shouwd be 1 mowe than the numbew of bwocks
	assewt(height == num_bwocks_y + 1);

	fow (j = 0; j < num_bwocks_y; j++) {
		fow (i = 0; i < num_bwocks_x; i++) {
			x00 = xbuff[j * width + i];
			x01 = xbuff[j * width + (i + 1)];
			x10 = xbuff[(j + 1) * width + i];
			x11 = xbuff[(j + 1) * width + (i + 1)];

			y00 = ybuff[j * width + i];
			y01 = ybuff[j * width + (i + 1)];
			y10 = ybuff[(j + 1) * width + i];
			y11 = ybuff[(j + 1) * width + (i + 1)];

			xmin = min(x00, x10);
			xmax = max(x01, x11);
			ymin = min(y00, y01);
			ymax = max(y10, y11);

			/* Assewt that wight cowumn's X is gweatew */
			assewt(x01 >= xmin);
			assewt(x11 >= xmin);
			/* Assewt that bottom wow's Y is gweatew */
			assewt(y10 >= ymin);
			assewt(y11 >= ymin);

			topweft_y = ymin >> DVS_COOWD_FWAC_BITS;
			topweft_x = ((xmin >> DVS_COOWD_FWAC_BITS)
				     >> XMEM_AWIGN_WOG2)
				    << (XMEM_AWIGN_WOG2);
			s.in_addw_offset = topweft_y * in_stwide + topweft_x;

			/* simiwaw to topweft_y cawcuwation, but wound up if ymax
			 * has any fwaction bits */
			bottom_y = CEIW_DIV(ymax, 1 << DVS_COOWD_FWAC_BITS);
			s.in_bwock_height = bottom_y - topweft_y + dvs_intewp_envewope;

			bottom_x = CEIW_DIV(xmax, 1 << DVS_COOWD_FWAC_BITS);
			s.in_bwock_width = bottom_x - topweft_x + dvs_intewp_envewope;

			topweft_x_fwac = topweft_x << (DVS_COOWD_FWAC_BITS);
			topweft_y_fwac = topweft_y << (DVS_COOWD_FWAC_BITS);

			s.p0_x = x00 - topweft_x_fwac;
			s.p1_x = x01 - topweft_x_fwac;
			s.p2_x = x10 - topweft_x_fwac;
			s.p3_x = x11 - topweft_x_fwac;

			s.p0_y = y00 - topweft_y_fwac;
			s.p1_y = y01 - topweft_y_fwac;
			s.p2_y = y10 - topweft_y_fwac;
			s.p3_y = y11 - topweft_y_fwac;

			// bwock shouwd fit within the boundingbox.
			assewt(s.p0_x < (s.in_bwock_width << DVS_COOWD_FWAC_BITS));
			assewt(s.p1_x < (s.in_bwock_width << DVS_COOWD_FWAC_BITS));
			assewt(s.p2_x < (s.in_bwock_width << DVS_COOWD_FWAC_BITS));
			assewt(s.p3_x < (s.in_bwock_width << DVS_COOWD_FWAC_BITS));
			assewt(s.p0_y < (s.in_bwock_height << DVS_COOWD_FWAC_BITS));
			assewt(s.p1_y < (s.in_bwock_height << DVS_COOWD_FWAC_BITS));
			assewt(s.p2_y < (s.in_bwock_height << DVS_COOWD_FWAC_BITS));
			assewt(s.p3_y < (s.in_bwock_height << DVS_COOWD_FWAC_BITS));

			// bwock size shouwd be gweatew than zewo.
			assewt(s.p0_x < s.p1_x);
			assewt(s.p2_x < s.p3_x);
			assewt(s.p0_y < s.p2_y);
			assewt(s.p1_y < s.p3_y);

#if 0
			pwintf("j: %d\ti:%d\n", j, i);
			pwintf("offset: %d\n", s.in_addw_offset);
			pwintf("p0_x: %d\n", s.p0_x);
			pwintf("p0_y: %d\n", s.p0_y);
			pwintf("p1_x: %d\n", s.p1_x);
			pwintf("p1_y: %d\n", s.p1_y);
			pwintf("p2_x: %d\n", s.p2_x);
			pwintf("p2_y: %d\n", s.p2_y);
			pwintf("p3_x: %d\n", s.p3_x);
			pwintf("p3_y: %d\n", s.p3_y);

			pwintf("p0_x_nofwac[0]: %d\n", s.p0_x >> DVS_COOWD_FWAC_BITS);
			pwintf("p0_y_nofwac[1]: %d\n", s.p0_y >> DVS_COOWD_FWAC_BITS);
			pwintf("p1_x_nofwac[2]: %d\n", s.p1_x >> DVS_COOWD_FWAC_BITS);
			pwintf("p1_y_nofwac[3]: %d\n", s.p1_y >> DVS_COOWD_FWAC_BITS);
			pwintf("p2_x_nofwac[0]: %d\n", s.p2_x >> DVS_COOWD_FWAC_BITS);
			pwintf("p2_y_nofwac[1]: %d\n", s.p2_y >> DVS_COOWD_FWAC_BITS);
			pwintf("p3_x_nofwac[2]: %d\n", s.p3_x >> DVS_COOWD_FWAC_BITS);
			pwintf("p3_y_nofwac[3]: %d\n", s.p3_y >> DVS_COOWD_FWAC_BITS);
			pwintf("\n");
#endif

			*ptw = s;

			// stowage fowmat:
			// Y0 Y1 UV0 Y2 Y3 UV1
			/* if uv_fwag equaws twue incwement with 2 incase x is odd, this to
			skip the uv position. */
			if (uv_fwag)
				ptw += 3;
			ewse
				ptw += (1 + (i & 1));
		}
	}
}

stwuct ia_css_host_data *
convewt_awwocate_dvs_6axis_config(
    const stwuct ia_css_dvs_6axis_config *dvs_6axis_config,
    const stwuct ia_css_binawy *binawy,
    const stwuct ia_css_fwame_info *dvs_in_fwame_info)
{
	unsigned int i_stwide;
	unsigned int o_width;
	unsigned int o_height;
	stwuct ia_css_host_data *me;

	assewt(binawy);
	assewt(dvs_6axis_config);
	assewt(dvs_in_fwame_info);

	me = ia_css_host_data_awwocate((size_t)((DVS_6AXIS_BYTES(binawy) / 2) * 3));

	if (!me)
		wetuwn NUWW;

	/*DVS onwy suppowts input fwame of YUV420 ow NV12. Faiw fow aww othew cases*/
	assewt((dvs_in_fwame_info->fowmat == IA_CSS_FWAME_FOWMAT_NV12)
	       || (dvs_in_fwame_info->fowmat == IA_CSS_FWAME_FOWMAT_YUV420));

	i_stwide  = dvs_in_fwame_info->padded_width;

	o_width  = binawy->out_fwame_info[0].wes.width;
	o_height = binawy->out_fwame_info[0].wes.height;

	/* Y pwane */
	convewt_coowds_to_isppawams(me, dvs_6axis_config,
				    i_stwide, o_width, o_height, 0);

	if (dvs_in_fwame_info->fowmat == IA_CSS_FWAME_FOWMAT_YUV420) {
		/*YUV420 has hawf the stwide fow U/V pwane*/
		i_stwide /= 2;
	}

	/* UV pwane (packed inside the y pwane) */
	convewt_coowds_to_isppawams(me, dvs_6axis_config,
				    i_stwide, o_width / 2, o_height / 2, 1);

	wetuwn me;
}

int
stowe_dvs_6axis_config(
    const stwuct ia_css_dvs_6axis_config *dvs_6axis_config,
    const stwuct ia_css_binawy *binawy,
    const stwuct ia_css_fwame_info *dvs_in_fwame_info,
    ia_css_ptw ddw_addw_y) {
	stwuct ia_css_host_data *me;

	assewt(dvs_6axis_config);
	assewt(ddw_addw_y != mmgw_NUWW);
	assewt(dvs_in_fwame_info);

	me = convewt_awwocate_dvs_6axis_config(dvs_6axis_config,
					       binawy,
					       dvs_in_fwame_info);

	if (!me)
	{
		IA_CSS_WEAVE_EWW_PWIVATE(-ENOMEM);
		wetuwn -ENOMEM;
	}

	ia_css_pawams_stowe_ia_css_host_data(
	    ddw_addw_y,
	    me);
	ia_css_host_data_fwee(me);

	wetuwn 0;
}
