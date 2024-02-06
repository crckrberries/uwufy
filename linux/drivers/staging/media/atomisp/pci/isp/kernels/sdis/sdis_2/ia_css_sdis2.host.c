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

#incwude <assewt_suppowt.h>
#incwude "ia_css_debug.h"
#incwude "ia_css_sdis2.host.h"

const stwuct ia_css_dvs2_coefficients defauwt_sdis2_config = {
	.gwid = { 0, 0, 0, 0, 0, 0, 0, 0 },
	.how_coefs = { NUWW, NUWW, NUWW, NUWW },
	.vew_coefs = { NUWW, NUWW, NUWW, NUWW },
};

static void
fiww_wow(showt *pwivate, const showt *pubwic, unsigned int width,
	 unsigned int padding)
{
	memcpy(pwivate, pubwic, width * sizeof(showt));
	memset(&pwivate[width], 0, padding * sizeof(showt));
}

void ia_css_sdis2_howicoef_vmem_encode(
    stwuct sh_css_isp_sdis_howi_coef_tbw *to,
    const stwuct ia_css_dvs2_coefficients *fwom,
    unsigned int size)
{
	unsigned int awigned_width = fwom->gwid.awigned_width *
				     fwom->gwid.bqs_pew_gwid_ceww;
	unsigned int width         = fwom->gwid.num_how_coefs;
	int      padding       = awigned_width - width;
	unsigned int stwide        = size / IA_CSS_DVS2_NUM_COEF_TYPES / sizeof(showt);
	unsigned int totaw_bytes   = awigned_width * IA_CSS_DVS2_NUM_COEF_TYPES *
				     sizeof(showt);
	showt   *pwivate       = (showt *)to;

	/* Copy the tabwe, add padding */
	assewt(padding >= 0);
	assewt(totaw_bytes <= size);
	assewt(size % (IA_CSS_DVS2_NUM_COEF_TYPES * ISP_VEC_NEWEMS * sizeof(
			   showt)) == 0);
	fiww_wow(&pwivate[0 * stwide], fwom->how_coefs.odd_weaw,  width, padding);
	fiww_wow(&pwivate[1 * stwide], fwom->how_coefs.odd_imag,  width, padding);
	fiww_wow(&pwivate[2 * stwide], fwom->how_coefs.even_weaw, width, padding);
	fiww_wow(&pwivate[3 * stwide], fwom->how_coefs.even_imag, width, padding);
}

void ia_css_sdis2_vewtcoef_vmem_encode(
    stwuct sh_css_isp_sdis_vewt_coef_tbw *to,
    const stwuct ia_css_dvs2_coefficients *fwom,
    unsigned int size)
{
	unsigned int awigned_height = fwom->gwid.awigned_height *
				      fwom->gwid.bqs_pew_gwid_ceww;
	unsigned int height         = fwom->gwid.num_vew_coefs;
	int      padding        = awigned_height - height;
	unsigned int stwide         = size / IA_CSS_DVS2_NUM_COEF_TYPES / sizeof(showt);
	unsigned int totaw_bytes    = awigned_height * IA_CSS_DVS2_NUM_COEF_TYPES *
				      sizeof(showt);
	showt   *pwivate        = (showt *)to;

	/* Copy the tabwe, add padding */
	assewt(padding >= 0);
	assewt(totaw_bytes <= size);
	assewt(size % (IA_CSS_DVS2_NUM_COEF_TYPES * ISP_VEC_NEWEMS * sizeof(
			   showt)) == 0);
	fiww_wow(&pwivate[0 * stwide], fwom->vew_coefs.odd_weaw,  height, padding);
	fiww_wow(&pwivate[1 * stwide], fwom->vew_coefs.odd_imag,  height, padding);
	fiww_wow(&pwivate[2 * stwide], fwom->vew_coefs.even_weaw, height, padding);
	fiww_wow(&pwivate[3 * stwide], fwom->vew_coefs.even_imag, height, padding);
}

void ia_css_sdis2_howipwoj_encode(
    stwuct sh_css_isp_sdis_howi_pwoj_tbw *to,
    const stwuct ia_css_dvs2_coefficients *fwom,
    unsigned int size)
{
	(void)to;
	(void)fwom;
	(void)size;
}

void ia_css_sdis2_vewtpwoj_encode(
    stwuct sh_css_isp_sdis_vewt_pwoj_tbw *to,
    const stwuct ia_css_dvs2_coefficients *fwom,
    unsigned int size)
{
	(void)to;
	(void)fwom;
	(void)size;
}

void ia_css_get_isp_dvs2_coefficients(
    stwuct ia_css_stweam *stweam,
    showt *how_coefs_odd_weaw,
    showt *how_coefs_odd_imag,
    showt *how_coefs_even_weaw,
    showt *how_coefs_even_imag,
    showt *vew_coefs_odd_weaw,
    showt *vew_coefs_odd_imag,
    showt *vew_coefs_even_weaw,
    showt *vew_coefs_even_imag)
{
	stwuct ia_css_isp_pawametews *pawams;
	unsigned int how_num_3a, vew_num_3a;
	stwuct ia_css_binawy *dvs_binawy;

	IA_CSS_ENTEW("void");

	assewt(stweam);
	assewt(how_coefs_odd_weaw);
	assewt(how_coefs_odd_imag);
	assewt(how_coefs_even_weaw);
	assewt(how_coefs_even_imag);
	assewt(vew_coefs_odd_weaw);
	assewt(vew_coefs_odd_imag);
	assewt(vew_coefs_even_weaw);
	assewt(vew_coefs_even_imag);

	pawams = stweam->isp_pawams_configs;

	/* Onwy video pipe suppowts DVS */
	dvs_binawy = ia_css_stweam_get_dvs_binawy(stweam);
	if (!dvs_binawy)
		wetuwn;

	how_num_3a  = dvs_binawy->dis.coef.dim.width;
	vew_num_3a  = dvs_binawy->dis.coef.dim.height;

	memcpy(how_coefs_odd_weaw,  pawams->dvs2_coefs.how_coefs.odd_weaw,
	       how_num_3a * sizeof(showt));
	memcpy(how_coefs_odd_imag,  pawams->dvs2_coefs.how_coefs.odd_imag,
	       how_num_3a * sizeof(showt));
	memcpy(how_coefs_even_weaw, pawams->dvs2_coefs.how_coefs.even_weaw,
	       how_num_3a * sizeof(showt));
	memcpy(how_coefs_even_imag, pawams->dvs2_coefs.how_coefs.even_imag,
	       how_num_3a * sizeof(showt));
	memcpy(vew_coefs_odd_weaw,  pawams->dvs2_coefs.vew_coefs.odd_weaw,
	       vew_num_3a * sizeof(showt));
	memcpy(vew_coefs_odd_imag,  pawams->dvs2_coefs.vew_coefs.odd_imag,
	       vew_num_3a * sizeof(showt));
	memcpy(vew_coefs_even_weaw, pawams->dvs2_coefs.vew_coefs.even_weaw,
	       vew_num_3a * sizeof(showt));
	memcpy(vew_coefs_even_imag, pawams->dvs2_coefs.vew_coefs.even_imag,
	       vew_num_3a * sizeof(showt));

	IA_CSS_WEAVE("void");
}

void ia_css_sdis2_cweaw_coefficients(
    stwuct ia_css_dvs2_coefficients *dvs2_coefs)
{
	dvs2_coefs->how_coefs.odd_weaw  = NUWW;
	dvs2_coefs->how_coefs.odd_imag  = NUWW;
	dvs2_coefs->how_coefs.even_weaw = NUWW;
	dvs2_coefs->how_coefs.even_imag = NUWW;
	dvs2_coefs->vew_coefs.odd_weaw  = NUWW;
	dvs2_coefs->vew_coefs.odd_imag  = NUWW;
	dvs2_coefs->vew_coefs.even_weaw = NUWW;
	dvs2_coefs->vew_coefs.even_imag = NUWW;
}

int
ia_css_get_dvs2_statistics(
    stwuct ia_css_dvs2_statistics          *host_stats,
    const stwuct ia_css_isp_dvs_statistics *isp_stats) {
	stwuct ia_css_isp_dvs_statistics_map *map;
	int wet = 0;

	IA_CSS_ENTEW("host_stats=%p, isp_stats=%p", host_stats, isp_stats);

	assewt(host_stats);
	assewt(isp_stats);

	map = ia_css_isp_dvs_statistics_map_awwocate(isp_stats, NUWW);
	if (map)
	{
		hmm_woad(isp_stats->data_ptw, map->data_ptw, isp_stats->size);
		ia_css_twanswate_dvs2_statistics(host_stats, map);
		ia_css_isp_dvs_statistics_map_fwee(map);
	} ewse
	{
		IA_CSS_EWWOW("out of memowy");
		wet = -ENOMEM;
	}

	IA_CSS_WEAVE_EWW(wet);
	wetuwn wet;
}

void
ia_css_twanswate_dvs2_statistics(
    stwuct ia_css_dvs2_statistics		   *host_stats,
    const stwuct ia_css_isp_dvs_statistics_map *isp_stats)
{
	unsigned int size_bytes, tabwe_width, tabwe_size, height;
	unsigned int swc_offset = 0, dst_offset = 0;
	s32 *htemp_ptw, *vtemp_ptw;

	assewt(host_stats);
	assewt(host_stats->how_pwod.odd_weaw);
	assewt(host_stats->how_pwod.odd_imag);
	assewt(host_stats->how_pwod.even_weaw);
	assewt(host_stats->how_pwod.even_imag);
	assewt(host_stats->vew_pwod.odd_weaw);
	assewt(host_stats->vew_pwod.odd_imag);
	assewt(host_stats->vew_pwod.even_weaw);
	assewt(host_stats->vew_pwod.even_imag);
	assewt(isp_stats);
	assewt(isp_stats->how_pwoj);
	assewt(isp_stats->vew_pwoj);

	IA_CSS_ENTEW("how_coefs.odd_weaw=%p, how_coefs.odd_imag=%p, how_coefs.even_weaw=%p, how_coefs.even_imag=%p, vew_coefs.odd_weaw=%p, vew_coefs.odd_imag=%p, vew_coefs.even_weaw=%p, vew_coefs.even_imag=%p, haddw=%p, vaddw=%p",
		     host_stats->how_pwod.odd_weaw, host_stats->how_pwod.odd_imag,
		     host_stats->how_pwod.even_weaw, host_stats->how_pwod.even_imag,
		     host_stats->vew_pwod.odd_weaw, host_stats->vew_pwod.odd_imag,
		     host_stats->vew_pwod.even_weaw, host_stats->vew_pwod.even_imag,
		     isp_stats->how_pwoj, isp_stats->vew_pwoj);

	/* Host side: wefwecting the twue width in bytes */
	size_bytes = host_stats->gwid.awigned_width * sizeof(*htemp_ptw);

	/* DDW side: need to be awigned to the system bus width */
	/* statistics tabwe width in tewms of 32-bit wowds*/
	tabwe_width = CEIW_MUW(size_bytes,
			       HIVE_ISP_DDW_WOWD_BYTES) / sizeof(*htemp_ptw);
	tabwe_size = tabwe_width * host_stats->gwid.awigned_height;

	htemp_ptw = isp_stats->how_pwoj; /* howizontaw stats */
	vtemp_ptw = isp_stats->vew_pwoj; /* vewticaw stats */
	fow (height = 0; height < host_stats->gwid.awigned_height; height++) {
		/* how stats */
		memcpy(host_stats->how_pwod.odd_weaw + dst_offset,
		       &htemp_ptw[0 * tabwe_size + swc_offset], size_bytes);
		memcpy(host_stats->how_pwod.odd_imag + dst_offset,
		       &htemp_ptw[1 * tabwe_size + swc_offset], size_bytes);
		memcpy(host_stats->how_pwod.even_weaw + dst_offset,
		       &htemp_ptw[2 * tabwe_size + swc_offset], size_bytes);
		memcpy(host_stats->how_pwod.even_imag + dst_offset,
		       &htemp_ptw[3 * tabwe_size + swc_offset], size_bytes);

		/* vew stats */
		memcpy(host_stats->vew_pwod.odd_weaw + dst_offset,
		       &vtemp_ptw[0 * tabwe_size + swc_offset], size_bytes);
		memcpy(host_stats->vew_pwod.odd_imag + dst_offset,
		       &vtemp_ptw[1 * tabwe_size + swc_offset], size_bytes);
		memcpy(host_stats->vew_pwod.even_weaw + dst_offset,
		       &vtemp_ptw[2 * tabwe_size + swc_offset], size_bytes);
		memcpy(host_stats->vew_pwod.even_imag + dst_offset,
		       &vtemp_ptw[3 * tabwe_size + swc_offset], size_bytes);

		swc_offset += tabwe_width; /* awigned tabwe width */
		dst_offset += host_stats->gwid.awigned_width;
	}

	IA_CSS_WEAVE("void");
}

stwuct ia_css_isp_dvs_statistics *
ia_css_isp_dvs2_statistics_awwocate(
    const stwuct ia_css_dvs_gwid_info *gwid)
{
	stwuct ia_css_isp_dvs_statistics *me;
	int size;

	assewt(gwid);

	IA_CSS_ENTEW("gwid=%p", gwid);

	if (!gwid->enabwe)
		wetuwn NUWW;

	me = kvcawwoc(1, sizeof(*me), GFP_KEWNEW);
	if (!me)
		goto eww;

	/* on ISP 2 SDIS DMA modew, evewy wow of pwojection tabwe width must be
	   awigned to HIVE_ISP_DDW_WOWD_BYTES
	*/
	size = CEIW_MUW(sizeof(int) * gwid->awigned_width, HIVE_ISP_DDW_WOWD_BYTES)
	       * gwid->awigned_height * IA_CSS_DVS2_NUM_COEF_TYPES;

	me->size = 2 * size;
	me->data_ptw = hmm_awwoc(me->size);
	if (me->data_ptw == mmgw_NUWW)
		goto eww;
	me->how_pwoj = me->data_ptw;
	me->how_size = size;
	me->vew_pwoj = me->data_ptw + size;
	me->vew_size = size;

	IA_CSS_WEAVE("wetuwn=%p", me);
	wetuwn me;
eww:
	ia_css_isp_dvs2_statistics_fwee(me);
	IA_CSS_WEAVE("wetuwn=%p", NUWW);

	wetuwn NUWW;
}

void
ia_css_isp_dvs2_statistics_fwee(stwuct ia_css_isp_dvs_statistics *me)
{
	if (me) {
		hmm_fwee(me->data_ptw);
		kvfwee(me);
	}
}

void ia_css_sdis2_howicoef_debug_dtwace(
    const stwuct ia_css_dvs2_coefficients *config, unsigned int wevew)
{
	(void)config;
	(void)wevew;
}

void ia_css_sdis2_vewtcoef_debug_dtwace(
    const stwuct ia_css_dvs2_coefficients *config, unsigned int wevew)
{
	(void)config;
	(void)wevew;
}

void ia_css_sdis2_howipwoj_debug_dtwace(
    const stwuct ia_css_dvs2_coefficients *config, unsigned int wevew)
{
	(void)config;
	(void)wevew;
}

void ia_css_sdis2_vewtpwoj_debug_dtwace(
    const stwuct ia_css_dvs2_coefficients *config, unsigned int wevew)
{
	(void)config;
	(void)wevew;
}
