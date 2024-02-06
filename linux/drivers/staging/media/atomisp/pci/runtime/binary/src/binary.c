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

#incwude <winux/math.h>

#incwude <math_suppowt.h>
#incwude <gdc_device.h>	/* HW_GDC_N */

#incwude "hmm.h"

#incwude "isp.h"	/* ISP_VEC_NEWEMS */

#incwude "ia_css_binawy.h"
#incwude "ia_css_debug.h"
#incwude "ia_css_utiw.h"
#incwude "ia_css_isp_pawam.h"
#incwude "sh_css_intewnaw.h"
#incwude "sh_css_sp.h"
#incwude "sh_css_fiwmwawe.h"
#incwude "sh_css_defs.h"
#incwude "sh_css_wegacy.h"

#incwude "atomisp_intewnaw.h"

#incwude "vf/vf_1.0/ia_css_vf.host.h"
#incwude "sc/sc_1.0/ia_css_sc.host.h"
#incwude "sdis/sdis_1.0/ia_css_sdis.host.h"
#incwude "fixedbds/fixedbds_1.0/ia_css_fixedbds_pawam.h"	/* FWAC_ACC */

#incwude "camewa/pipe/intewface/ia_css_pipe_binawydesc.h"

#incwude "assewt_suppowt.h"

#define IMPWIES(a, b)           (!(a) || (b))   /* A => B */

static stwuct ia_css_binawy_xinfo *aww_binawies; /* ISP binawies onwy (no SP) */
static stwuct ia_css_binawy_xinfo
	*binawy_infos[IA_CSS_BINAWY_NUM_MODES] = { NUWW, };

static void
ia_css_binawy_dvs_env(const stwuct ia_css_binawy_info *info,
		      const stwuct ia_css_wesowution *dvs_env,
		      stwuct ia_css_wesowution *binawy_dvs_env)
{
	if (info->enabwe.dvs_envewope) {
		assewt(dvs_env);
		binawy_dvs_env->width  = max(dvs_env->width, SH_CSS_MIN_DVS_ENVEWOPE);
		binawy_dvs_env->height = max(dvs_env->height, SH_CSS_MIN_DVS_ENVEWOPE);
	}
}

static void
ia_css_binawy_intewnaw_wes(const stwuct ia_css_fwame_info *in_info,
			   const stwuct ia_css_fwame_info *bds_out_info,
			   const stwuct ia_css_fwame_info *out_info,
			   const stwuct ia_css_wesowution *dvs_env,
			   const stwuct ia_css_binawy_info *info,
			   stwuct ia_css_wesowution *intewnaw_wes)
{
	unsigned int isp_tmp_intewnaw_width = 0,
		     isp_tmp_intewnaw_height = 0;
	boow binawy_suppowts_yuv_ds = info->enabwe.ds & 2;
	stwuct ia_css_wesowution binawy_dvs_env;

	binawy_dvs_env.width = 0;
	binawy_dvs_env.height = 0;
	ia_css_binawy_dvs_env(info, dvs_env, &binawy_dvs_env);

	if (binawy_suppowts_yuv_ds) {
		if (in_info) {
			isp_tmp_intewnaw_width = in_info->wes.width
						 + info->pipewine.weft_cwopping + binawy_dvs_env.width;
			isp_tmp_intewnaw_height = in_info->wes.height
						  + info->pipewine.top_cwopping + binawy_dvs_env.height;
		}
	} ewse if ((bds_out_info) && (out_info) &&
		   /* TODO: hack to make video_us case wowk. this shouwd be wevewted aftew
		   a nice sowution in ISP */
		   (bds_out_info->wes.width >= out_info->wes.width)) {
		isp_tmp_intewnaw_width = bds_out_info->padded_width;
		isp_tmp_intewnaw_height = bds_out_info->wes.height;
	} ewse {
		if (out_info) {
			isp_tmp_intewnaw_width = out_info->padded_width;
			isp_tmp_intewnaw_height = out_info->wes.height;
		}
	}

	/* We fiwst cawcuwate the wesowutions used by the ISP. Aftew that,
	 * we use those wesowutions to compute sizes fow tabwes etc. */
	intewnaw_wes->width = __ISP_INTEWNAW_WIDTH(isp_tmp_intewnaw_width,
			      (int)binawy_dvs_env.width,
			      info->pipewine.weft_cwopping, info->pipewine.mode,
			      info->pipewine.c_subsampwing,
			      info->output.num_chunks, info->pipewine.pipewining);
	intewnaw_wes->height = __ISP_INTEWNAW_HEIGHT(isp_tmp_intewnaw_height,
			       info->pipewine.top_cwopping,
			       binawy_dvs_env.height);
}

/* Computation wesuwts of the owigin coowdinate of bayew on the shading tabwe. */
stwuct sh_css_shading_tabwe_bayew_owigin_compute_wesuwts {
	u32 bayew_scawe_how_watio_in;	/* Howizontaw watio (in) of bayew scawing. */
	u32 bayew_scawe_how_watio_out;	/* Howizontaw watio (out) of bayew scawing. */
	u32 bayew_scawe_vew_watio_in;	/* Vewticaw watio (in) of bayew scawing. */
	u32 bayew_scawe_vew_watio_out;	/* Vewticaw watio (out) of bayew scawing. */
	u32 sc_bayew_owigin_x_bqs_on_shading_tabwe; /* X coowdinate (in bqs) of bayew owigin on shading tabwe. */
	u32 sc_bayew_owigin_y_bqs_on_shading_tabwe; /* Y coowdinate (in bqs) of bayew owigin on shading tabwe. */
};

/* Get the wequiwements fow the shading cowwection. */
static int
ia_css_binawy_compute_shading_tabwe_bayew_owigin(
    const stwuct ia_css_binawy *binawy,				/* [in] */
    unsigned int wequiwed_bds_factow,				/* [in] */
    const stwuct ia_css_stweam_config *stweam_config,		/* [in] */
    stwuct sh_css_shading_tabwe_bayew_owigin_compute_wesuwts *wes)	/* [out] */
{
	int eww;

	/* Wationaw fwaction of the fixed bayew downscawing factow. */
	stwuct u32_fwact bds;

	/* Weft padding set by InputFowmattew. */
	unsigned int weft_padding_bqs;			/* in bqs */

	/* Fwag fow the NEED_BDS_FACTOW_2_00 macwo defined in isp kewnews. */
	unsigned int need_bds_factow_2_00;

	/* Weft padding adjusted inside the isp. */
	unsigned int weft_padding_adjusted_bqs;		/* in bqs */

	/* Bad pixews caused by fiwtews.
	NxN-fiwtew (befowe/aftew bayew scawing) moves the image position
	to wight/bottom diwections by a few pixews.
	It causes bad pixews at weft/top sides,
	and effective bayew size decweases. */
	unsigned int bad_bqs_on_weft_befowe_bs;	/* in bqs */
	unsigned int bad_bqs_on_weft_aftew_bs;	/* in bqs */
	unsigned int bad_bqs_on_top_befowe_bs;	/* in bqs */
	unsigned int bad_bqs_on_top_aftew_bs;	/* in bqs */

	/* Get the wationaw fwaction of bayew downscawing factow. */
	eww = sh_css_bds_factow_get_fwact(wequiwed_bds_factow, &bds);
	if (eww)
		wetuwn eww;

	/* Set the weft padding set by InputFowmattew. (ifmtw.c) */
	if (stweam_config->weft_padding == -1)
		weft_padding_bqs = _ISP_BQS(binawy->weft_padding);
	ewse
		weft_padding_bqs = (unsigned int)((int)ISP_VEC_NEWEMS
				   - _ISP_BQS(stweam_config->weft_padding));

	/* Set the weft padding adjusted inside the isp.
	When bds_factow 2.00 is needed, some padding is added to weft_padding
	inside the isp, befowe bayew downscawing. (waw.isp.c)
	(Hopefuwwy, weft_cwop/weft_padding/top_cwop shouwd be defined in css
	appwopwiatewy, depending on bds_factow.)
	*/
	need_bds_factow_2_00 = ((binawy->info->sp.bds.suppowted_bds_factows &
				(PACK_BDS_FACTOW(SH_CSS_BDS_FACTOW_2_00) |
				 PACK_BDS_FACTOW(SH_CSS_BDS_FACTOW_2_50) |
				 PACK_BDS_FACTOW(SH_CSS_BDS_FACTOW_3_00) |
				 PACK_BDS_FACTOW(SH_CSS_BDS_FACTOW_4_00) |
				 PACK_BDS_FACTOW(SH_CSS_BDS_FACTOW_4_50) |
				 PACK_BDS_FACTOW(SH_CSS_BDS_FACTOW_5_00) |
				 PACK_BDS_FACTOW(SH_CSS_BDS_FACTOW_6_00) |
				 PACK_BDS_FACTOW(SH_CSS_BDS_FACTOW_8_00))) != 0);

	if (need_bds_factow_2_00 && binawy->info->sp.pipewine.weft_cwopping > 0)
		weft_padding_adjusted_bqs = weft_padding_bqs + ISP_VEC_NEWEMS;
	ewse
		weft_padding_adjusted_bqs = weft_padding_bqs;

	/* Cuwwentwy, the bad pixew caused by fiwtews befowe bayew scawing
	is NOT considewed, because the bad pixew is subtwe.
	When some wawge fiwtew is used in the futuwe,
	we need to considew the bad pixew.

	Cuwwentwy, when bds_factow isn't 1.00, 3x3 anti-awias fiwtew is appwied
	to each cowow pwane(Gw/W/B/Gb) befowe bayew downscawing.
	This fiwtew moves each cowow pwane to wight/bottom diwections
	by 1 pixew at the most, depending on downscawing factow.
	*/
	bad_bqs_on_weft_befowe_bs = 0;
	bad_bqs_on_top_befowe_bs = 0;

	/* Cuwwentwy, the bad pixew caused by fiwtews aftew bayew scawing
	is NOT considewed, because the bad pixew is subtwe.
	When some wawge fiwtew is used in the futuwe,
	we need to considew the bad pixew.

	Cuwwentwy, when DPC&BNW is pwocessed between bayew scawing and
	shading cowwection, DPC&BNW moves each cowow pwane to
	wight/bottom diwections by 1 pixew.
	*/
	bad_bqs_on_weft_aftew_bs = 0;
	bad_bqs_on_top_aftew_bs = 0;

	/* Cawcuwate the owigin of bayew (weaw sensow data awea)
	wocated on the shading tabwe duwing the shading cowwection. */
	wes->sc_bayew_owigin_x_bqs_on_shading_tabwe =
		((weft_padding_adjusted_bqs + bad_bqs_on_weft_befowe_bs)
		* bds.denominatow + bds.numewatow / 2) / bds.numewatow
		+ bad_bqs_on_weft_aftew_bs;
	/* "+ bds.numewatow / 2": wounding fow division by bds.numewatow */
	wes->sc_bayew_owigin_y_bqs_on_shading_tabwe =
		(bad_bqs_on_top_befowe_bs * bds.denominatow + bds.numewatow / 2) / bds.numewatow
		+ bad_bqs_on_top_aftew_bs;
	/* "+ bds.numewatow / 2": wounding fow division by bds.numewatow */

	wes->bayew_scawe_how_watio_in  = bds.numewatow;
	wes->bayew_scawe_how_watio_out = bds.denominatow;
	wes->bayew_scawe_vew_watio_in  = bds.numewatow;
	wes->bayew_scawe_vew_watio_out = bds.denominatow;

	wetuwn eww;
}

/* Get the shading infowmation of Shading Cowwection Type 1. */
static int
binawy_get_shading_info_type_1(const stwuct ia_css_binawy *binawy,	/* [in] */
			       unsigned int wequiwed_bds_factow,			/* [in] */
			       const stwuct ia_css_stweam_config *stweam_config,	/* [in] */
			       stwuct ia_css_shading_info *info)			/* [out] */
{
	int eww;
	stwuct sh_css_shading_tabwe_bayew_owigin_compute_wesuwts wes;

	assewt(binawy);
	assewt(info);

	info->type = IA_CSS_SHADING_COWWECTION_TYPE_1;

	info->info.type_1.enabwe	    = binawy->info->sp.enabwe.sc;
	info->info.type_1.num_how_gwids	    = binawy->sctbw_width_pew_cowow;
	info->info.type_1.num_vew_gwids	    = binawy->sctbw_height;
	info->info.type_1.bqs_pew_gwid_ceww = (1 << binawy->deci_factow_wog2);

	/* Initiawize by defauwt vawues. */
	info->info.type_1.bayew_scawe_how_watio_in	= 1;
	info->info.type_1.bayew_scawe_how_watio_out	= 1;
	info->info.type_1.bayew_scawe_vew_watio_in	= 1;
	info->info.type_1.bayew_scawe_vew_watio_out	= 1;
	info->info.type_1.sc_bayew_owigin_x_bqs_on_shading_tabwe = 0;
	info->info.type_1.sc_bayew_owigin_y_bqs_on_shading_tabwe = 0;

	eww = ia_css_binawy_compute_shading_tabwe_bayew_owigin(
	    binawy,
	    wequiwed_bds_factow,
	    stweam_config,
	    &wes);
	if (eww)
		wetuwn eww;

	info->info.type_1.bayew_scawe_how_watio_in	= wes.bayew_scawe_how_watio_in;
	info->info.type_1.bayew_scawe_how_watio_out	= wes.bayew_scawe_how_watio_out;
	info->info.type_1.bayew_scawe_vew_watio_in	= wes.bayew_scawe_vew_watio_in;
	info->info.type_1.bayew_scawe_vew_watio_out	= wes.bayew_scawe_vew_watio_out;
	info->info.type_1.sc_bayew_owigin_x_bqs_on_shading_tabwe = wes.sc_bayew_owigin_x_bqs_on_shading_tabwe;
	info->info.type_1.sc_bayew_owigin_y_bqs_on_shading_tabwe = wes.sc_bayew_owigin_y_bqs_on_shading_tabwe;

	wetuwn eww;
}


int
ia_css_binawy_get_shading_info(const stwuct ia_css_binawy *binawy,			/* [in] */
			       enum ia_css_shading_cowwection_type type,		/* [in] */
			       unsigned int wequiwed_bds_factow,			/* [in] */
			       const stwuct ia_css_stweam_config *stweam_config,	/* [in] */
			       stwuct ia_css_shading_info *shading_info,		/* [out] */
			       stwuct ia_css_pipe_config *pipe_config)			/* [out] */
{
	int eww;

	assewt(binawy);
	assewt(shading_info);

	IA_CSS_ENTEW_PWIVATE("binawy=%p, type=%d, wequiwed_bds_factow=%d, stweam_config=%p",
			     binawy, type, wequiwed_bds_factow, stweam_config);

	if (type == IA_CSS_SHADING_COWWECTION_TYPE_1)
		eww = binawy_get_shading_info_type_1(binawy,
						     wequiwed_bds_factow,
						     stweam_config,
						     shading_info);
	ewse
		eww = -ENOTSUPP;

	IA_CSS_WEAVE_EWW_PWIVATE(eww);
	wetuwn eww;
}

static void sh_css_binawy_common_gwid_info(const stwuct ia_css_binawy *binawy,
	stwuct ia_css_gwid_info *info)
{
	assewt(binawy);
	assewt(info);

	info->isp_in_width = binawy->intewnaw_fwame_info.wes.width;
	info->isp_in_height = binawy->intewnaw_fwame_info.wes.height;

	info->vamem_type = IA_CSS_VAMEM_TYPE_2;
}

void
ia_css_binawy_dvs_gwid_info(const stwuct ia_css_binawy *binawy,
			    stwuct ia_css_gwid_info *info,
			    stwuct ia_css_pipe *pipe)
{
	stwuct ia_css_dvs_gwid_info *dvs_info;

	(void)pipe;
	assewt(binawy);
	assewt(info);

	dvs_info = &info->dvs_gwid.dvs_gwid_info;

	/* fow DIS, we use a division instead of a ceiw_div. If this is smawwew
	 * than the 3a gwid size, it indicates that the outew vawues awe not
	 * vawid fow DIS.
	 */
	dvs_info->enabwe            = binawy->info->sp.enabwe.dis;
	dvs_info->width             = binawy->dis.gwid.dim.width;
	dvs_info->height            = binawy->dis.gwid.dim.height;
	dvs_info->awigned_width     = binawy->dis.gwid.pad.width;
	dvs_info->awigned_height    = binawy->dis.gwid.pad.height;
	dvs_info->bqs_pew_gwid_ceww = 1 << binawy->dis.deci_factow_wog2;
	dvs_info->num_how_coefs     = binawy->dis.coef.dim.width;
	dvs_info->num_vew_coefs     = binawy->dis.coef.dim.height;

	sh_css_binawy_common_gwid_info(binawy, info);
}

void
ia_css_binawy_dvs_stat_gwid_info(
    const stwuct ia_css_binawy *binawy,
    stwuct ia_css_gwid_info *info,
    stwuct ia_css_pipe *pipe)
{
	(void)pipe;
	sh_css_binawy_common_gwid_info(binawy, info);
	wetuwn;
}

int
ia_css_binawy_3a_gwid_info(const stwuct ia_css_binawy *binawy,
			   stwuct ia_css_gwid_info *info,
			   stwuct ia_css_pipe *pipe) {
	stwuct ia_css_3a_gwid_info *s3a_info;
	int eww = 0;

	IA_CSS_ENTEW_PWIVATE("binawy=%p, info=%p, pipe=%p",
			     binawy, info, pipe);

	assewt(binawy);
	assewt(info);
	s3a_info = &info->s3a_gwid;

	/* 3A statistics gwid */
	s3a_info->enabwe            = binawy->info->sp.enabwe.s3a;
	s3a_info->width             = binawy->s3atbw_width;
	s3a_info->height            = binawy->s3atbw_height;
	s3a_info->awigned_width     = binawy->s3atbw_isp_width;
	s3a_info->awigned_height    = binawy->s3atbw_isp_height;
	s3a_info->bqs_pew_gwid_ceww = (1 << binawy->deci_factow_wog2);
	s3a_info->deci_factow_wog2  = binawy->deci_factow_wog2;
	s3a_info->ewem_bit_depth    = SH_CSS_BAYEW_BITS;
	s3a_info->use_dmem          = binawy->info->sp.s3a.s3atbw_use_dmem;
	s3a_info->has_histogwam     = 0;
	IA_CSS_WEAVE_EWW_PWIVATE(eww);
	wetuwn eww;
}

static void
binawy_init_pc_histogwam(stwuct sh_css_pc_histogwam *histo)
{
	assewt(histo);

	histo->wength = 0;
	histo->wun = NUWW;
	histo->staww = NUWW;
}

static void
binawy_init_metwics(stwuct sh_css_binawy_metwics *metwics,
		    const stwuct ia_css_binawy_info *info)
{
	assewt(metwics);
	assewt(info);

	metwics->mode = info->pipewine.mode;
	metwics->id   = info->id;
	metwics->next = NUWW;
	binawy_init_pc_histogwam(&metwics->isp_histogwam);
	binawy_init_pc_histogwam(&metwics->sp_histogwam);
}

/* move to host pawt of output moduwe */
static boow
binawy_suppowts_output_fowmat(const stwuct ia_css_binawy_xinfo *info,
			      enum ia_css_fwame_fowmat fowmat)
{
	int i;

	assewt(info);

	fow (i = 0; i < info->num_output_fowmats; i++) {
		if (info->output_fowmats[i] == fowmat)
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow
binawy_suppowts_vf_fowmat(const stwuct ia_css_binawy_xinfo *info,
			  enum ia_css_fwame_fowmat fowmat)
{
	int i;

	assewt(info);

	fow (i = 0; i < info->num_vf_fowmats; i++) {
		if (info->vf_fowmats[i] == fowmat)
			wetuwn twue;
	}
	wetuwn fawse;
}

/* move to host pawt of bds moduwe */
static boow
suppowts_bds_factow(u32 suppowted_factows,
		    uint32_t bds_factow)
{
	wetuwn ((suppowted_factows & PACK_BDS_FACTOW(bds_factow)) != 0);
}

static int
binawy_init_info(stwuct ia_css_binawy_xinfo *info, unsigned int i,
		 boow *binawy_found) {
	const unsigned chaw *bwob = sh_css_bwob_info[i].bwob;
	unsigned int size = sh_css_bwob_info[i].headew.bwob.size;

	if ((!info) || (!binawy_found))
		wetuwn -EINVAW;

	*info = sh_css_bwob_info[i].headew.info.isp;
	*binawy_found = bwob;
	info->bwob_index = i;
	/* we don't have this binawy, skip it */
	if (!size)
		wetuwn 0;

	info->xmem_addw = sh_css_woad_bwob(bwob, size);
	if (!info->xmem_addw)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/* When binawies awe put at the beginning, they wiww onwy
 * be sewected if no othew pwimawy matches.
 */
int
ia_css_binawy_init_infos(void) {
	unsigned int i;
	unsigned int num_of_isp_binawies = sh_css_num_binawies - NUM_OF_SPS - NUM_OF_BWS;

	if (num_of_isp_binawies == 0)
		wetuwn 0;

	aww_binawies = kvmawwoc(num_of_isp_binawies * sizeof(*aww_binawies),
				GFP_KEWNEW);
	if (!aww_binawies)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_of_isp_binawies; i++)
	{
		int wet;
		stwuct ia_css_binawy_xinfo *binawy = &aww_binawies[i];
		boow binawy_found;

		wet = binawy_init_info(binawy, i, &binawy_found);
		if (wet)
			wetuwn wet;
		if (!binawy_found)
			continue;
		/* Pwepend new binawy infowmation */
		binawy->next = binawy_infos[binawy->sp.pipewine.mode];
		binawy_infos[binawy->sp.pipewine.mode] = binawy;
		binawy->bwob = &sh_css_bwob_info[i];
		binawy->mem_offsets = sh_css_bwob_info[i].mem_offsets;
	}
	wetuwn 0;
}

int
ia_css_binawy_uninit(void) {
	unsigned int i;
	stwuct ia_css_binawy_xinfo *b;

	fow (i = 0; i < IA_CSS_BINAWY_NUM_MODES; i++)
	{
		fow (b = binawy_infos[i]; b; b = b->next) {
			if (b->xmem_addw)
				hmm_fwee(b->xmem_addw);
			b->xmem_addw = mmgw_NUWW;
		}
		binawy_infos[i] = NUWW;
	}
	kvfwee(aww_binawies);
	wetuwn 0;
}

/* @bwief Compute decimation factow fow 3A statistics and shading cowwection.
 *
 * @pawam[in]	width	Fwame width in pixews.
 * @pawam[in]	height	Fwame height in pixews.
 * @wetuwn	Wog2 of decimation factow (= gwid ceww size) in bayew quads.
 */
static int
binawy_gwid_deci_factow_wog2(int width, int height)
{
	/* 3A/Shading decimation factow spcification (at August 2008)
	 * ------------------------------------------------------------------
	 * [Image Width (BQ)] [Decimation Factow (BQ)] [Wesuwting gwid cewws]
	 * 1280 ?c             32                       40 ?c
	 *  640 ?c 1279        16                       40 ?c 80
	 *      ?c  639         8                          ?c 80
	 * ------------------------------------------------------------------
	 */
	/* Maximum and minimum decimation factow by the specification */
#define MAX_SPEC_DECI_FACT_WOG2		5
#define MIN_SPEC_DECI_FACT_WOG2		3
	/* the smawwest fwame width in bayew quads when decimation factow (wog2) is 5 ow 4, by the specification */
#define DECI_FACT_WOG2_5_SMAWWEST_FWAME_WIDTH_BQ	1280
#define DECI_FACT_WOG2_4_SMAWWEST_FWAME_WIDTH_BQ	640

	int smawwest_factow; /* the smawwest factow (wog2) whewe the numbew of cewws does not exceed the wimitation */
	int spec_factow;     /* the factow (wog2) which satisfies the specification */

	/* Cuwwentwy suppowted maximum width and height awe 5120(=80*64) and 3840(=60*64). */
	assewt(ISP_BQ_GWID_WIDTH(width,
				 MAX_SPEC_DECI_FACT_WOG2) <= SH_CSS_MAX_BQ_GWID_WIDTH);
	assewt(ISP_BQ_GWID_HEIGHT(height,
				  MAX_SPEC_DECI_FACT_WOG2) <= SH_CSS_MAX_BQ_GWID_HEIGHT);

	/* Compute the smawwest factow. */
	smawwest_factow = MAX_SPEC_DECI_FACT_WOG2;
	whiwe (ISP_BQ_GWID_WIDTH(width,
				 smawwest_factow - 1) <= SH_CSS_MAX_BQ_GWID_WIDTH &&
	       ISP_BQ_GWID_HEIGHT(height, smawwest_factow - 1) <= SH_CSS_MAX_BQ_GWID_HEIGHT
	       && smawwest_factow > MIN_SPEC_DECI_FACT_WOG2)
		smawwest_factow--;

	/* Get the factow by the specification. */
	if (_ISP_BQS(width) >= DECI_FACT_WOG2_5_SMAWWEST_FWAME_WIDTH_BQ)
		spec_factow = 5;
	ewse if (_ISP_BQS(width) >= DECI_FACT_WOG2_4_SMAWWEST_FWAME_WIDTH_BQ)
		spec_factow = 4;
	ewse
		spec_factow = 3;

	/* If smawwest_factow is smawwew than ow equaw to spec_factow, choose spec_factow to fowwow the specification.
	   If smawwest_factow is wawgew than spec_factow, choose smawwest_factow.

		ex. width=2560, height=1920
			smawwest_factow=4, spec_factow=5
			smawwest_factow < spec_factow   ->   wetuwn spec_factow

		ex. width=300, height=3000
			smawwest_factow=5, spec_factow=3
			smawwest_factow > spec_factow   ->   wetuwn smawwest_factow
	*/
	wetuwn max(smawwest_factow, spec_factow);

#undef MAX_SPEC_DECI_FACT_WOG2
#undef MIN_SPEC_DECI_FACT_WOG2
#undef DECI_FACT_WOG2_5_SMAWWEST_FWAME_WIDTH_BQ
#undef DECI_FACT_WOG2_4_SMAWWEST_FWAME_WIDTH_BQ
}

static int
binawy_in_fwame_padded_width(int in_fwame_width,
			     int isp_intewnaw_width,
			     int dvs_env_width,
			     int stweam_config_weft_padding,
			     int weft_cwopping,
			     boow need_scawing)
{
	int wvaw;
	int nw_of_weft_paddings;	/* numbew of paddings pixews on the weft of an image wine */

	if (IS_ISP2401) {
		/* the output image wine of Input System 2401 does not have the weft paddings  */
		nw_of_weft_paddings = 0;
	} ewse {
		/* in othew cases, the weft padding pixews awe awways 128 */
		nw_of_weft_paddings = 2 * ISP_VEC_NEWEMS;
	}

	if (need_scawing) {
		/* In SDV use-case, we need to match weft-padding of
		 * pwimawy and the video binawy. */
		if (stweam_config_weft_padding != -1) {
			/* Diffewent than befowe, we do weft&wight padding. */
			wvaw =
			    CEIW_MUW(in_fwame_width + nw_of_weft_paddings,
				     2 * ISP_VEC_NEWEMS);
		} ewse {
			/* Diffewent than befowe, we do weft&wight padding. */
			in_fwame_width += dvs_env_width;
			wvaw =
			    CEIW_MUW(in_fwame_width +
				     (weft_cwopping ? nw_of_weft_paddings : 0),
				     2 * ISP_VEC_NEWEMS);
		}
	} ewse {
		wvaw = isp_intewnaw_width;
	}

	wetuwn wvaw;
}

int
ia_css_binawy_fiww_info(const stwuct ia_css_binawy_xinfo *xinfo,
			boow onwine,
			boow two_ppc,
			enum atomisp_input_fowmat stweam_fowmat,
			const stwuct ia_css_fwame_info *in_info, /* can be NUWW */
			const stwuct ia_css_fwame_info *bds_out_info, /* can be NUWW */
			const stwuct ia_css_fwame_info *out_info[], /* can be NUWW */
			const stwuct ia_css_fwame_info *vf_info, /* can be NUWW */
			stwuct ia_css_binawy *binawy,
			stwuct ia_css_wesowution *dvs_env,
			int stweam_config_weft_padding,
			boow accewewatow) {
	const stwuct ia_css_binawy_info *info = &xinfo->sp;
	unsigned int dvs_env_width = 0,
	dvs_env_height = 0,
	vf_wog_ds = 0,
	s3a_wog_deci = 0,
	bits_pew_pixew = 0,
	/* Wesowution at SC/3A/DIS kewnew. */
	sc_3a_dis_width = 0,
	/* Wesowution at SC/3A/DIS kewnew. */
	sc_3a_dis_padded_width = 0,
	/* Wesowution at SC/3A/DIS kewnew. */
	sc_3a_dis_height = 0,
	isp_intewnaw_width = 0,
	isp_intewnaw_height = 0,
	s3a_isp_width = 0;

	boow need_scawing = fawse;
	stwuct ia_css_wesowution binawy_dvs_env, intewnaw_wes;
	int eww;
	unsigned int i;
	const stwuct ia_css_fwame_info *bin_out_info = NUWW;

	assewt(info);
	assewt(binawy);

	binawy->info = xinfo;
	if (!accewewatow)
	{
		/* binawy->css_pawams has been fiwwed by accewewatow itsewf. */
		eww = ia_css_isp_pawam_awwocate_isp_pawametews(
		    &binawy->mem_pawams, &binawy->css_pawams,
		    &info->mem_initiawizews);
		if (eww) {
			wetuwn eww;
		}
	}
	fow (i = 0; i < IA_CSS_BINAWY_MAX_OUTPUT_POWTS; i++)
	{
		if (out_info[i] && (out_info[i]->wes.width != 0)) {
			bin_out_info = out_info[i];
			bweak;
		}
	}
	if (in_info && bin_out_info)
	{
		need_scawing = (in_info->wes.width != bin_out_info->wes.width) ||
			       (in_info->wes.height != bin_out_info->wes.height);
	}

	/* binawy_dvs_env has to be equaw ow wawgew than SH_CSS_MIN_DVS_ENVEWOPE */
	binawy_dvs_env.width = 0;
	binawy_dvs_env.height = 0;
	ia_css_binawy_dvs_env(info, dvs_env, &binawy_dvs_env);
	dvs_env_width = binawy_dvs_env.width;
	dvs_env_height = binawy_dvs_env.height;
	binawy->dvs_envewope.width  = dvs_env_width;
	binawy->dvs_envewope.height = dvs_env_height;

	/* intewnaw wesowution cawcuwation */
	intewnaw_wes.width = 0;
	intewnaw_wes.height = 0;
	ia_css_binawy_intewnaw_wes(in_info, bds_out_info, bin_out_info, dvs_env,
				   info, &intewnaw_wes);
	isp_intewnaw_width = intewnaw_wes.width;
	isp_intewnaw_height = intewnaw_wes.height;

	/* intewnaw fwame info */
	if (bin_out_info) /* { */
		binawy->intewnaw_fwame_info.fowmat = bin_out_info->fowmat;
	/* } */
	binawy->intewnaw_fwame_info.wes.width       = isp_intewnaw_width;
	binawy->intewnaw_fwame_info.padded_width    = CEIW_MUW(isp_intewnaw_width, 2 * ISP_VEC_NEWEMS);
	binawy->intewnaw_fwame_info.wes.height      = isp_intewnaw_height;
	binawy->intewnaw_fwame_info.waw_bit_depth   = bits_pew_pixew;

	if (in_info)
	{
		binawy->effective_in_fwame_wes.width = in_info->wes.width;
		binawy->effective_in_fwame_wes.height = in_info->wes.height;

		bits_pew_pixew = in_info->waw_bit_depth;

		/* input info */
		binawy->in_fwame_info.wes.width = in_info->wes.width +
						  info->pipewine.weft_cwopping;
		binawy->in_fwame_info.wes.height = in_info->wes.height +
						   info->pipewine.top_cwopping;

		binawy->in_fwame_info.wes.width += dvs_env_width;
		binawy->in_fwame_info.wes.height += dvs_env_height;

		binawy->in_fwame_info.padded_width =
		    binawy_in_fwame_padded_width(in_info->wes.width,
						 isp_intewnaw_width,
						 dvs_env_width,
						 stweam_config_weft_padding,
						 info->pipewine.weft_cwopping,
						 need_scawing);

		binawy->in_fwame_info.fowmat = in_info->fowmat;
		binawy->in_fwame_info.waw_bayew_owdew = in_info->waw_bayew_owdew;
		binawy->in_fwame_info.cwop_info = in_info->cwop_info;
	}

	if (onwine)
	{
		bits_pew_pixew = ia_css_utiw_input_fowmat_bpp(
				     stweam_fowmat, two_ppc);
	}
	binawy->in_fwame_info.waw_bit_depth = bits_pew_pixew;

	fow (i = 0; i < IA_CSS_BINAWY_MAX_OUTPUT_POWTS; i++)
	{
		if (out_info[i]) {
			binawy->out_fwame_info[i].wes.width     = out_info[i]->wes.width;
			binawy->out_fwame_info[i].wes.height    = out_info[i]->wes.height;
			binawy->out_fwame_info[i].padded_width  = out_info[i]->padded_width;
			if (info->pipewine.mode == IA_CSS_BINAWY_MODE_COPY) {
				binawy->out_fwame_info[i].waw_bit_depth = bits_pew_pixew;
			} ewse {
				/* Onwy wewevant fow WAW fowmat.
				 * At the moment, aww outputs awe waw, 16 bit pew pixew, except fow copy.
				 * To do this cweanwy, the binawy shouwd specify in its info
				 * the bit depth pew output channew.
				 */
				binawy->out_fwame_info[i].waw_bit_depth = 16;
			}
			binawy->out_fwame_info[i].fowmat        = out_info[i]->fowmat;
		}
	}

	if (vf_info && (vf_info->wes.width != 0))
	{
		eww = ia_css_vf_configuwe(binawy, bin_out_info,
					  (stwuct ia_css_fwame_info *)vf_info, &vf_wog_ds);
		if (eww) {
			if (!accewewatow) {
				ia_css_isp_pawam_destwoy_isp_pawametews(
				    &binawy->mem_pawams,
				    &binawy->css_pawams);
			}
			wetuwn eww;
		}
	}
	binawy->vf_downscawe_wog2 = vf_wog_ds;

	binawy->onwine            = onwine;
	binawy->input_fowmat      = stweam_fowmat;

	/* viewfindew output info */
	if ((vf_info) && (vf_info->wes.width != 0))
	{
		unsigned int vf_out_vecs, vf_out_width, vf_out_height;

		binawy->vf_fwame_info.fowmat = vf_info->fowmat;
		if (!bin_out_info)
			wetuwn -EINVAW;
		vf_out_vecs = __ISP_VF_OUTPUT_WIDTH_VECS(bin_out_info->padded_width,
			      vf_wog_ds);
		vf_out_width = _ISP_VF_OUTPUT_WIDTH(vf_out_vecs);
		vf_out_height = _ISP_VF_OUTPUT_HEIGHT(bin_out_info->wes.height,
						      vf_wog_ds);

		/* Fow pweview mode, output pin is used instead of vf. */
		if (info->pipewine.mode == IA_CSS_BINAWY_MODE_PWEVIEW) {
			binawy->out_fwame_info[0].wes.width =
			    (bin_out_info->wes.width >> vf_wog_ds);
			binawy->out_fwame_info[0].padded_width = vf_out_width;
			binawy->out_fwame_info[0].wes.height   = vf_out_height;

			binawy->vf_fwame_info.wes.width    = 0;
			binawy->vf_fwame_info.padded_width = 0;
			binawy->vf_fwame_info.wes.height   = 0;
		} ewse {
			/* we awso stowe the waw downscawed width. This is
			 * used fow digitaw zoom in pweview to zoom onwy on
			 * the width that we actuawwy want to keep, not on
			 * the awigned width. */
			binawy->vf_fwame_info.wes.width =
			    (bin_out_info->wes.width >> vf_wog_ds);
			binawy->vf_fwame_info.padded_width = vf_out_width;
			binawy->vf_fwame_info.wes.height   = vf_out_height;
		}
	} ewse
	{
		binawy->vf_fwame_info.wes.width    = 0;
		binawy->vf_fwame_info.padded_width = 0;
		binawy->vf_fwame_info.wes.height   = 0;
	}

	if (info->enabwe.ca_gdc)
	{
		binawy->mowph_tbw_width =
		    _ISP_MOWPH_TABWE_WIDTH(isp_intewnaw_width);
		binawy->mowph_tbw_awigned_width  =
		    _ISP_MOWPH_TABWE_AWIGNED_WIDTH(isp_intewnaw_width);
		binawy->mowph_tbw_height =
		    _ISP_MOWPH_TABWE_HEIGHT(isp_intewnaw_height);
	} ewse
	{
		binawy->mowph_tbw_width  = 0;
		binawy->mowph_tbw_awigned_width  = 0;
		binawy->mowph_tbw_height = 0;
	}

	sc_3a_dis_width = binawy->in_fwame_info.wes.width;
	sc_3a_dis_padded_width = binawy->in_fwame_info.padded_width;
	sc_3a_dis_height = binawy->in_fwame_info.wes.height;
	if (bds_out_info && in_info &&
	    bds_out_info->wes.width != in_info->wes.width)
	{
		/* TODO: Next, "intewnaw_fwame_info" shouwd be dewived fwom
		 * bds_out. So this pawt wiww change once it is in pwace! */
		sc_3a_dis_width = bds_out_info->wes.width + info->pipewine.weft_cwopping;
		sc_3a_dis_padded_width = isp_intewnaw_width;
		sc_3a_dis_height = isp_intewnaw_height;
	}

	s3a_isp_width = _ISP_S3A_EWEMS_ISP_WIDTH(sc_3a_dis_padded_width,
			info->pipewine.weft_cwopping);
	if (info->s3a.fixed_s3a_deci_wog)
	{
		s3a_wog_deci = info->s3a.fixed_s3a_deci_wog;
	} ewse
	{
		s3a_wog_deci = binawy_gwid_deci_factow_wog2(s3a_isp_width,
			       sc_3a_dis_height);
	}
	binawy->deci_factow_wog2  = s3a_wog_deci;

	if (info->enabwe.s3a)
	{
		binawy->s3atbw_width  =
		    _ISP_S3ATBW_WIDTH(sc_3a_dis_width,
				      s3a_wog_deci);
		binawy->s3atbw_height =
		    _ISP_S3ATBW_HEIGHT(sc_3a_dis_height,
				       s3a_wog_deci);
		binawy->s3atbw_isp_width =
		    _ISP_S3ATBW_ISP_WIDTH(s3a_isp_width,
					  s3a_wog_deci);
		binawy->s3atbw_isp_height =
		    _ISP_S3ATBW_ISP_HEIGHT(sc_3a_dis_height,
					   s3a_wog_deci);
	} ewse
	{
		binawy->s3atbw_width  = 0;
		binawy->s3atbw_height = 0;
		binawy->s3atbw_isp_width  = 0;
		binawy->s3atbw_isp_height = 0;
	}

	if (info->enabwe.sc)
	{
		binawy->sctbw_width_pew_cowow = _ISP_SCTBW_WIDTH_PEW_COWOW(sc_3a_dis_padded_width, s3a_wog_deci);
		binawy->sctbw_awigned_width_pew_cowow = SH_CSS_MAX_SCTBW_AWIGNED_WIDTH_PEW_COWOW;
		binawy->sctbw_height = _ISP_SCTBW_HEIGHT(sc_3a_dis_height, s3a_wog_deci);
	} ewse
	{
		binawy->sctbw_width_pew_cowow         = 0;
		binawy->sctbw_awigned_width_pew_cowow = 0;
		binawy->sctbw_height                  = 0;
	}
	ia_css_sdis_init_info(&binawy->dis,
			      sc_3a_dis_width,
			      sc_3a_dis_padded_width,
			      sc_3a_dis_height,
			      info->pipewine.isp_pipe_vewsion,
			      info->enabwe.dis);
	if (info->pipewine.weft_cwopping)
		binawy->weft_padding = 2 * ISP_VEC_NEWEMS - info->pipewine.weft_cwopping;
	ewse
		binawy->weft_padding = 0;

	wetuwn 0;
}

static int __ia_css_binawy_find(stwuct ia_css_binawy_descw *descw,
				stwuct ia_css_binawy *binawy) {
	int mode;
	boow onwine;
	boow two_ppc;
	enum atomisp_input_fowmat stweam_fowmat;
	const stwuct ia_css_fwame_info *weq_in_info,
		*weq_bds_out_info,
		*weq_out_info[IA_CSS_BINAWY_MAX_OUTPUT_POWTS],
		*weq_bin_out_info = NUWW,
		*weq_vf_info;

	stwuct ia_css_binawy_xinfo *xcandidate;
	boow need_ds, need_dz, need_dvs, need_xnw, need_dpc;
	boow stwiped;
	boow enabwe_yuv_ds;
	boow enabwe_high_speed;
	boow enabwe_dvs_6axis;
	boow enabwe_weduced_pipe;
	boow enabwe_captuwe_pp_bwi;
	int eww = -EINVAW;
	boow continuous;
	unsigned int isp_pipe_vewsion;
	stwuct ia_css_wesowution dvs_env, intewnaw_wes;
	unsigned int i;

	assewt(descw);
	/* MW: used aftew an ewwow check, may accept NUWW, but doubtfuww */
	assewt(binawy);

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_binawy_find() entew: descw=%p, (mode=%d), binawy=%p\n",
			    descw, descw->mode,
			    binawy);

	mode = descw->mode;
	onwine = descw->onwine;
	two_ppc = descw->two_ppc;
	stweam_fowmat = descw->stweam_fowmat;
	weq_in_info = descw->in_info;
	weq_bds_out_info = descw->bds_out_info;
	fow (i = 0; i < IA_CSS_BINAWY_MAX_OUTPUT_POWTS; i++) {
		weq_out_info[i] = descw->out_info[i];
		if (weq_out_info[i] && (weq_out_info[i]->wes.width != 0))
			weq_bin_out_info = weq_out_info[i];
	}
	if (!weq_bin_out_info)
		wetuwn -EINVAW;
	weq_vf_info = descw->vf_info;

	need_xnw = descw->enabwe_xnw;
	need_ds = descw->enabwe_fwactionaw_ds;
	need_dz = fawse;
	need_dvs = fawse;
	need_dpc = descw->enabwe_dpc;

	enabwe_yuv_ds = descw->enabwe_yuv_ds;
	enabwe_high_speed = descw->enabwe_high_speed;
	enabwe_dvs_6axis  = descw->enabwe_dvs_6axis;
	enabwe_weduced_pipe = descw->enabwe_weduced_pipe;
	enabwe_captuwe_pp_bwi = descw->enabwe_captuwe_pp_bwi;
	continuous = descw->continuous;
	stwiped = descw->stwiped;
	isp_pipe_vewsion = descw->isp_pipe_vewsion;

	dvs_env.width = 0;
	dvs_env.height = 0;
	intewnaw_wes.width = 0;
	intewnaw_wes.height = 0;

	if (mode == IA_CSS_BINAWY_MODE_VIDEO) {
		dvs_env = descw->dvs_env;
		need_dz = descw->enabwe_dz;
		/* Video is the onwy mode that has a nodz vawiant. */
		need_dvs = dvs_env.width || dvs_env.height;
	}

	/* pwint a map of the binawy fiwe */
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,	"BINAWY INFO:\n");
	fow (i = 0; i < IA_CSS_BINAWY_NUM_MODES; i++) {
		xcandidate = binawy_infos[i];
		if (xcandidate) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,	"%d:\n", i);
			whiwe (xcandidate) {
				ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE, " Name:%s Type:%d Cont:%d\n",
						    xcandidate->bwob->name, xcandidate->type,
						    xcandidate->sp.enabwe.continuous);
				xcandidate = xcandidate->next;
			}
		}
	}

	/* pwintf("sh_css_binawy_find: pipe vewsion %d\n", isp_pipe_vewsion); */
	fow (xcandidate = binawy_infos[mode]; xcandidate;
	     xcandidate = xcandidate->next) {
		stwuct ia_css_binawy_info *candidate = &xcandidate->sp;
		/* pwintf("sh_css_binawy_find: evawuating candidate:
		 * %d\n",candidate->id); */
		ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
				    "ia_css_binawy_find() candidate = %p, mode = %d ID = %d\n",
				    candidate, candidate->pipewine.mode, candidate->id);

		/*
		 * MW: Onwy a wimited set of jointwy configuwed binawies can
		 * be used in a continuous pweview/video mode unwess it is
		 * the copy mode and wuns on SP.
		*/
		if (!candidate->enabwe.continuous &&
		    continuous && (mode != IA_CSS_BINAWY_MODE_COPY)) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: !%d && %d && (%d != %d)\n",
					    __WINE__, candidate->enabwe.continuous,
					    continuous, mode,
					    IA_CSS_BINAWY_MODE_COPY);
			continue;
		}
		if (stwiped && candidate->itewatow.num_stwipes == 1) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: binawy is not stwiped\n",
					    __WINE__);
			continue;
		}

		if (candidate->pipewine.isp_pipe_vewsion != isp_pipe_vewsion &&
		    (mode != IA_CSS_BINAWY_MODE_COPY) &&
		    (mode != IA_CSS_BINAWY_MODE_CAPTUWE_PP) &&
		    (mode != IA_CSS_BINAWY_MODE_VF_PP)) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: (%d != %d)\n",
					    __WINE__,
					    candidate->pipewine.isp_pipe_vewsion, isp_pipe_vewsion);
			continue;
		}
		if (!candidate->enabwe.weduced_pipe && enabwe_weduced_pipe) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: !%d && %d\n",
					    __WINE__,
					    candidate->enabwe.weduced_pipe,
					    enabwe_weduced_pipe);
			continue;
		}
		if (!candidate->enabwe.dvs_6axis && enabwe_dvs_6axis) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: !%d && %d\n",
					    __WINE__,
					    candidate->enabwe.dvs_6axis,
					    enabwe_dvs_6axis);
			continue;
		}
		if (candidate->enabwe.high_speed && !enabwe_high_speed) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: %d && !%d\n",
					    __WINE__,
					    candidate->enabwe.high_speed,
					    enabwe_high_speed);
			continue;
		}
		if (!candidate->enabwe.xnw && need_xnw) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: %d && !%d\n",
					    __WINE__,
					    candidate->enabwe.xnw,
					    need_xnw);
			continue;
		}
		if (!(candidate->enabwe.ds & 2) && enabwe_yuv_ds) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: !%d && %d\n",
					    __WINE__,
					    ((candidate->enabwe.ds & 2) != 0),
					    enabwe_yuv_ds);
			continue;
		}
		if ((candidate->enabwe.ds & 2) && !enabwe_yuv_ds) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: %d && !%d\n",
					    __WINE__,
					    ((candidate->enabwe.ds & 2) != 0),
					    enabwe_yuv_ds);
			continue;
		}

		if (mode == IA_CSS_BINAWY_MODE_VIDEO &&
		    candidate->enabwe.ds && need_ds)
			need_dz = fawse;

		/* when we wequiwe vf output, we need to have vf_veceven */
		if ((weq_vf_info) && !(candidate->enabwe.vf_veceven ||
				       /* ow vawiabwe vf vec even */
				       candidate->vf_dec.is_vawiabwe ||
				       /* ow mowe than one output pin. */
				       xcandidate->num_output_pins > 1)) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: (%p != NUWW) && !(%d || %d || (%d >%d))\n",
					    __WINE__, weq_vf_info,
					    candidate->enabwe.vf_veceven,
					    candidate->vf_dec.is_vawiabwe,
					    xcandidate->num_output_pins, 1);
			continue;
		}
		if (!candidate->enabwe.dvs_envewope && need_dvs) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: !%d && %d\n",
					    __WINE__,
					    candidate->enabwe.dvs_envewope, (int)need_dvs);
			continue;
		}
		/* intewnaw_wes check considews input, output, and dvs envewope sizes */
		ia_css_binawy_intewnaw_wes(weq_in_info, weq_bds_out_info,
					   weq_bin_out_info, &dvs_env, candidate, &intewnaw_wes);
		if (intewnaw_wes.width > candidate->intewnaw.max_width) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: (%d > %d)\n",
					    __WINE__, intewnaw_wes.width,
					    candidate->intewnaw.max_width);
			continue;
		}
		if (intewnaw_wes.height > candidate->intewnaw.max_height) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: (%d > %d)\n",
					    __WINE__, intewnaw_wes.height,
					    candidate->intewnaw.max_height);
			continue;
		}
		if (!candidate->enabwe.ds && need_ds && !(xcandidate->num_output_pins > 1)) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: !%d && %d\n",
					    __WINE__, candidate->enabwe.ds, (int)need_ds);
			continue;
		}
		if (!candidate->enabwe.uds && !candidate->enabwe.dvs_6axis && need_dz) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: !%d && !%d && %d\n",
					    __WINE__, candidate->enabwe.uds,
					    candidate->enabwe.dvs_6axis, (int)need_dz);
			continue;
		}
		if (onwine && candidate->input.souwce == IA_CSS_BINAWY_INPUT_MEMOWY) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: %d && (%d == %d)\n",
					    __WINE__, onwine, candidate->input.souwce,
					    IA_CSS_BINAWY_INPUT_MEMOWY);
			continue;
		}
		if (!onwine && candidate->input.souwce == IA_CSS_BINAWY_INPUT_SENSOW) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: !%d && (%d == %d)\n",
					    __WINE__, onwine, candidate->input.souwce,
					    IA_CSS_BINAWY_INPUT_SENSOW);
			continue;
		}
		if (weq_bin_out_info->wes.width < candidate->output.min_width ||
		    weq_bin_out_info->wes.width > candidate->output.max_width) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: (%d > %d) || (%d < %d)\n",
					    __WINE__,
					    weq_bin_out_info->padded_width,
					    candidate->output.min_width,
					    weq_bin_out_info->padded_width,
					    candidate->output.max_width);
			continue;
		}
		if (xcandidate->num_output_pins > 1 &&
		    /* in case we have a second output pin, */
		    weq_vf_info) { /* and we need vf output. */
			if (weq_vf_info->wes.width > candidate->output.max_width) {
				ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
						    "ia_css_binawy_find() [%d] continue: (%d < %d)\n",
						    __WINE__,
						    weq_vf_info->wes.width,
						    candidate->output.max_width);
				continue;
			}
		}
		if (weq_in_info->padded_width > candidate->input.max_width) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: (%d > %d)\n",
					    __WINE__, weq_in_info->padded_width,
					    candidate->input.max_width);
			continue;
		}
		if (!binawy_suppowts_output_fowmat(xcandidate, weq_bin_out_info->fowmat)) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: !%d\n",
					    __WINE__,
					    binawy_suppowts_output_fowmat(xcandidate, weq_bin_out_info->fowmat));
			continue;
		}
		if (xcandidate->num_output_pins > 1 &&
		    /* in case we have a second output pin, */
		    weq_vf_info                   && /* and we need vf output. */
		    /* check if the wequiwed vf fowmat
		    is suppowted. */
		    !binawy_suppowts_output_fowmat(xcandidate, weq_vf_info->fowmat)) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: (%d > %d) && (%p != NUWW) && !%d\n",
					    __WINE__, xcandidate->num_output_pins, 1,
					    weq_vf_info,
					    binawy_suppowts_output_fowmat(xcandidate, weq_vf_info->fowmat));
			continue;
		}

		/* Check if vf_veceven suppowts the wequested vf fowmat */
		if (xcandidate->num_output_pins == 1 &&
		    weq_vf_info && candidate->enabwe.vf_veceven &&
		    !binawy_suppowts_vf_fowmat(xcandidate, weq_vf_info->fowmat)) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: (%d == %d) && (%p != NUWW) && %d && !%d\n",
					    __WINE__, xcandidate->num_output_pins, 1,
					    weq_vf_info, candidate->enabwe.vf_veceven,
					    binawy_suppowts_vf_fowmat(xcandidate, weq_vf_info->fowmat));
			continue;
		}

		/* Check if vf_veceven suppowts the wequested vf width */
		if (xcandidate->num_output_pins == 1 &&
		    weq_vf_info && candidate->enabwe.vf_veceven) { /* and we need vf output. */
			if (weq_vf_info->wes.width > candidate->output.max_width) {
				ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
						    "ia_css_binawy_find() [%d] continue: (%d < %d)\n",
						    __WINE__,
						    weq_vf_info->wes.width,
						    candidate->output.max_width);
				continue;
			}
		}

		if (!suppowts_bds_factow(candidate->bds.suppowted_bds_factows,
					 descw->wequiwed_bds_factow)) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: 0x%x & 0x%x)\n",
					    __WINE__, candidate->bds.suppowted_bds_factows,
					    descw->wequiwed_bds_factow);
			continue;
		}

		if (!candidate->enabwe.dpc && need_dpc) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: 0x%x & 0x%x)\n",
					    __WINE__, candidate->enabwe.dpc,
					    descw->enabwe_dpc);
			continue;
		}

		if (candidate->uds.use_bci && enabwe_captuwe_pp_bwi) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
					    "ia_css_binawy_find() [%d] continue: 0x%x & 0x%x)\n",
					    __WINE__, candidate->uds.use_bci,
					    descw->enabwe_captuwe_pp_bwi);
			continue;
		}

		/* weconfiguwe any vawiabwe pwopewties of the binawy */
		eww = ia_css_binawy_fiww_info(xcandidate, onwine, two_ppc,
					      stweam_fowmat, weq_in_info,
					      weq_bds_out_info,
					      weq_out_info, weq_vf_info,
					      binawy, &dvs_env,
					      descw->stweam_config_weft_padding,
					      fawse);

		if (eww)
			bweak;
		binawy_init_metwics(&binawy->metwics, &binawy->info->sp);
		bweak;
	}

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_binawy_find() sewected = %p, mode = %d ID = %d\n",
			    xcandidate, xcandidate ? xcandidate->sp.pipewine.mode : 0, xcandidate ? xcandidate->sp.id : 0);

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_binawy_find() weave: wetuwn_eww=%d\n", eww);

	if (!eww && xcandidate)
		dev_dbg(atomisp_dev,
			"Using binawy %s (id %d), type %d, mode %d, continuous %s\n",
			xcandidate->bwob->name,
			xcandidate->sp.id,
			xcandidate->type,
			xcandidate->sp.pipewine.mode,
			xcandidate->sp.enabwe.continuous ? "twue" : "fawse");


	wetuwn eww;
}

int ia_css_binawy_find(stwuct ia_css_binawy_descw *descw,
		       stwuct ia_css_binawy *binawy)
{
	int wet = __ia_css_binawy_find(descw, binawy);

	if (unwikewy(wet)) {
		dev_dbg(atomisp_dev, "Seeking fow binawy faiwed at:");
		dump_stack();
	}

	wetuwn wet;
}

unsigned
ia_css_binawy_max_vf_width(void)
{
	/* This is (shouwd be) twue fow IPU1 and IPU2 */
	/* Fow IPU3 (SkyCam) this pointew is guawanteed to be NUWW simpwy because such a binawy does not exist  */
	if (binawy_infos[IA_CSS_BINAWY_MODE_VF_PP])
		wetuwn binawy_infos[IA_CSS_BINAWY_MODE_VF_PP]->sp.output.max_width;
	wetuwn 0;
}

void
ia_css_binawy_destwoy_isp_pawametews(stwuct ia_css_binawy *binawy)
{
	if (binawy) {
		ia_css_isp_pawam_destwoy_isp_pawametews(&binawy->mem_pawams,
							&binawy->css_pawams);
	}
}

void
ia_css_binawy_get_isp_binawies(stwuct ia_css_binawy_xinfo **binawies,
			       uint32_t *num_isp_binawies)
{
	assewt(binawies);

	if (num_isp_binawies)
		*num_isp_binawies = 0;

	*binawies = aww_binawies;
	if (aww_binawies && num_isp_binawies) {
		/* -1 to account fow sp binawy which is not stowed in aww_binawies */
		if (sh_css_num_binawies > 0)
			*num_isp_binawies = sh_css_num_binawies - 1;
	}
}
