// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Yunfei Dong <yunfei.dong@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "../mtk_vcodec_dec.h"
#incwude "../../common/mtk_vcodec_intw.h"
#incwude "../vdec_dwv_base.h"
#incwude "../vdec_dwv_if.h"
#incwude "../vdec_vpu_if.h"

/* the size used to stowe hevc wwap infowmation */
#define VDEC_HEVC_WWAP_SZ (532 * SZ_1K)

#define HEVC_MAX_MV_NUM 32

/* get used pawametews fow sps/pps */
#define GET_HEVC_VDEC_FWAG(cond, fwag) \
	{ dst_pawam->cond = ((swc_pawam->fwags & (fwag)) ? (1) : (0)); }
#define GET_HEVC_VDEC_PAWAM(pawam) \
	{ dst_pawam->pawam = swc_pawam->pawam; }

/**
 * enum vdec_hevc_cowe_dec_eww_type  - cowe decode ewwow type
 *
 * @TWANS_BUFFEW_FUWW: twans buffew is fuww
 * @SWICE_HEADEW_FUWW: swice headew buffew is fuww
 */
enum vdec_hevc_cowe_dec_eww_type {
	TWANS_BUFFEW_FUWW = 1,
	SWICE_HEADEW_FUWW,
};

/**
 * stwuct mtk_hevc_dpb_info  - hevc dpb infowmation
 *
 * @y_dma_addw:     Y pwane physicaw addwess
 * @c_dma_addw:     CbCw pwane physicaw addwess
 * @wefewence_fwag: wefewence pictuwe fwag (showt/wong tewm wefewence pictuwe)
 * @fiewd:          fiewd pictuwe fwag
 */
stwuct mtk_hevc_dpb_info {
	dma_addw_t y_dma_addw;
	dma_addw_t c_dma_addw;
	int wefewence_fwag;
	int fiewd;
};

/*
 * stwuct mtk_hevc_sps_pawam  - pawametews fow sps
 */
stwuct mtk_hevc_sps_pawam {
	unsigned chaw video_pawametew_set_id;
	unsigned chaw seq_pawametew_set_id;
	unsigned showt pic_width_in_wuma_sampwes;
	unsigned showt pic_height_in_wuma_sampwes;
	unsigned chaw bit_depth_wuma_minus8;
	unsigned chaw bit_depth_chwoma_minus8;
	unsigned chaw wog2_max_pic_owdew_cnt_wsb_minus4;
	unsigned chaw sps_max_dec_pic_buffewing_minus1;
	unsigned chaw sps_max_num_weowdew_pics;
	unsigned chaw sps_max_watency_incwease_pwus1;
	unsigned chaw wog2_min_wuma_coding_bwock_size_minus3;
	unsigned chaw wog2_diff_max_min_wuma_coding_bwock_size;
	unsigned chaw wog2_min_wuma_twansfowm_bwock_size_minus2;
	unsigned chaw wog2_diff_max_min_wuma_twansfowm_bwock_size;
	unsigned chaw max_twansfowm_hiewawchy_depth_intew;
	unsigned chaw max_twansfowm_hiewawchy_depth_intwa;
	unsigned chaw pcm_sampwe_bit_depth_wuma_minus1;
	unsigned chaw pcm_sampwe_bit_depth_chwoma_minus1;
	unsigned chaw wog2_min_pcm_wuma_coding_bwock_size_minus3;
	unsigned chaw wog2_diff_max_min_pcm_wuma_coding_bwock_size;
	unsigned chaw num_showt_tewm_wef_pic_sets;
	unsigned chaw num_wong_tewm_wef_pics_sps;
	unsigned chaw chwoma_fowmat_idc;
	unsigned chaw sps_max_sub_wayews_minus1;
	unsigned chaw sepawate_cowouw_pwane;
	unsigned chaw scawing_wist_enabwed;
	unsigned chaw amp_enabwed;
	unsigned chaw sampwe_adaptive_offset;
	unsigned chaw pcm_enabwed;
	unsigned chaw pcm_woop_fiwtew_disabwed;
	unsigned chaw wong_tewm_wef_pics_enabwed;
	unsigned chaw sps_tempowaw_mvp_enabwed;
	unsigned chaw stwong_intwa_smoothing_enabwed;
	unsigned chaw wesewved[5];
};

/*
 * stwuct mtk_hevc_pps_pawam  - pawametews fow pps
 */
stwuct mtk_hevc_pps_pawam {
	unsigned chaw pic_pawametew_set_id;
	unsigned chaw num_extwa_swice_headew_bits;
	unsigned chaw num_wef_idx_w0_defauwt_active_minus1;
	unsigned chaw num_wef_idx_w1_defauwt_active_minus1;
	chaw init_qp_minus26;
	unsigned chaw diff_cu_qp_dewta_depth;
	chaw pps_cb_qp_offset;
	chaw pps_cw_qp_offset;
	unsigned chaw num_tiwe_cowumns_minus1;
	unsigned chaw num_tiwe_wows_minus1;
	unsigned chaw cowumn_width_minus1[20];
	unsigned chaw wow_height_minus1[22];
	chaw pps_beta_offset_div2;
	chaw pps_tc_offset_div2;
	unsigned chaw wog2_pawawwew_mewge_wevew_minus2;
	chaw dependent_swice_segment_enabwed;
	chaw output_fwag_pwesent;
	chaw sign_data_hiding_enabwed;
	chaw cabac_init_pwesent;
	chaw constwained_intwa_pwed;
	chaw twansfowm_skip_enabwed;
	chaw cu_qp_dewta_enabwed;
	chaw pps_swice_chwoma_qp_offsets_pwesent;
	chaw weighted_pwed;
	chaw weighted_bipwed;
	chaw twansquant_bypass_enabwed;
	chaw pps_fwag_tiwes_enabwed;
	chaw entwopy_coding_sync_enabwed;
	chaw woop_fiwtew_acwoss_tiwes_enabwed;
	chaw pps_woop_fiwtew_acwoss_swices_enabwed;
	chaw debwocking_fiwtew_ovewwide_enabwed;
	chaw pps_disabwe_defwocking_fiwtew;
	chaw wists_modification_pwesent;
	chaw swice_segment_headew_extewsion_pwesent;
	chaw debwocking_fiwtew_contwow_pwesent;
	chaw unifowm_spacing;
	chaw wesewved[6];
};

/*
 * stwuct mtk_hevc_swice_headew_pawam  - pawametews fow swice headew
 */
stwuct mtk_hevc_swice_headew_pawam {
	unsigned int	swice_type;
	unsigned int	num_active_wef_wayew_pics;
	int		swice_qp;
	int		swice_qp_dewta_cb;
	int		swice_qp_dewta_cw;
	int		num_wef_idx[3];
	unsigned int	cow_wef_idx;
	unsigned int	five_minus_max_num_mewge_cand;
	int		swice_debwocking_fiwtew_beta_offset_div2;
	int		swice_debwocking_fiwtew_tc_offset_div2;
	unsigned chaw	sao_enabwe_fwag;
	unsigned chaw	sao_enabwe_fwag_chwoma;
	unsigned chaw	cabac_init_fwag;
	unsigned chaw	swice_tmvp_fwags_pwesent;
	unsigned chaw	cow_fwom_w0_fwag;
	unsigned chaw	mvd_w1_zewo_fwag;
	unsigned chaw	swice_woop_fiwtew_acwoss_swices_enabwed_fwag;
	unsigned chaw	debwocking_fiwtew_disabwe_fwag;
	unsigned int	swice_weg0;
	unsigned int	swice_weg1;
	unsigned int	swice_weg2;
	unsigned int	num_wps_cuww_temp_wist;
	unsigned int	wef_wist_mode;
	int		stw_num_dewta_pocs;
	int		stw_num_negtive_pos_pics;
	int		num_wong_tewm;
	int		num_wong_tewm_sps;
	unsigned int	max_cu_width;
	unsigned int	max_cu_height;
	unsigned int	num_entwy_point_offsets;
	unsigned int    wast_wcu_x_in_tiwe[17];
	unsigned int    wast_wcu_y_in_tiwe[17];
	unsigned chaw   naw_unit_type;
};

/*
 * stwuct swice_api_hevc_scawing_matwix  - pawametews fow scawing wist
 */
stwuct swice_api_hevc_scawing_matwix {
	unsigned chaw scawing_wist_4x4[6][16];
	unsigned chaw scawing_wist_8x8[6][64];
	unsigned chaw scawing_wist_16x16[6][64];
	unsigned chaw scawing_wist_32x32[2][64];
	unsigned chaw scawing_wist_dc_coef_16x16[6];
	unsigned chaw scawing_wist_dc_coef_32x32[2];
};

/*
 * stwuct swice_hevc_dpb_entwy  - each dpb infowmation
 */
stwuct swice_hevc_dpb_entwy {
	u64 timestamp;
	unsigned chaw fwags;
	unsigned chaw fiewd_pic;
	int pic_owdew_cnt_vaw;
};

/*
 * stwuct swice_api_hevc_decode_pawam - pawametews fow decode.
 */
stwuct swice_api_hevc_decode_pawam {
	stwuct swice_hevc_dpb_entwy dpb[V4W2_HEVC_DPB_ENTWIES_NUM_MAX];
	int pic_owdew_cnt_vaw;
	unsigned showt showt_tewm_wef_pic_set_size;
	unsigned showt wong_tewm_wef_pic_set_size;
	unsigned chaw num_active_dpb_entwies;
	unsigned chaw num_poc_st_cuww_befowe;
	unsigned chaw num_poc_st_cuww_aftew;
	unsigned chaw num_poc_wt_cuww;
	unsigned chaw poc_st_cuww_befowe[V4W2_HEVC_DPB_ENTWIES_NUM_MAX];
	unsigned chaw poc_st_cuww_aftew[V4W2_HEVC_DPB_ENTWIES_NUM_MAX];
	unsigned chaw poc_wt_cuww[V4W2_HEVC_DPB_ENTWIES_NUM_MAX];
	unsigned chaw num_dewta_pocs_of_wef_wps_idx;
	int fwags;
};

/**
 * stwuct hevc_fb - hevc decode fwame buffew infowmation
 *
 * @vdec_fb_va: viwtuaw addwess of stwuct vdec_fb
 * @y_fb_dma:   dma addwess of Y fwame buffew (wuma)
 * @c_fb_dma:   dma addwess of C fwame buffew (chwoma)
 * @poc:        pictuwe owdew count of fwame buffew
 * @wesewved:   fow 8 bytes awignment
 */
stwuct hevc_fb {
	u64 vdec_fb_va;
	u64 y_fb_dma;
	u64 c_fb_dma;
	s32 poc;
	u32 wesewved;
};

/**
 * stwuct vdec_hevc_swice_wat_dec_pawam  - pawametews fow decode cuwwent fwame
 *
 * @sps:            hevc sps syntax pawametews
 * @pps:            hevc pps syntax pawametews
 * @swice_headew:   hevc swice headew syntax pawametews
 * @scawing_matwix: hevc scawing wist pawametews
 * @decode_pawams:  decodew pawametews of each fwame used fow hawdwawe decode
 * @hevc_dpb_info:  dpb wefewence wist
 */
stwuct vdec_hevc_swice_wat_dec_pawam {
	stwuct mtk_hevc_sps_pawam sps;
	stwuct mtk_hevc_pps_pawam pps;
	stwuct mtk_hevc_swice_headew_pawam swice_headew;
	stwuct swice_api_hevc_scawing_matwix scawing_matwix;
	stwuct swice_api_hevc_decode_pawam decode_pawams;
	stwuct mtk_hevc_dpb_info hevc_dpb_info[V4W2_HEVC_DPB_ENTWIES_NUM_MAX];
};

/**
 * stwuct vdec_hevc_swice_info - decode infowmation
 *
 * @wdma_end_addw_offset: wdma end addwess offset
 * @timeout:              Decode timeout: 1 timeout, 0 no timeount
 * @vdec_fb_va:           VDEC fwame buffew stwuct viwtuaw addwess
 * @cwc:                  Used to check whethew hawdwawe's status is wight
 */
stwuct vdec_hevc_swice_info {
	u64 wdma_end_addw_offset;
	u64 timeout;
	u64 vdec_fb_va;
	u32 cwc[8];
};

/*
 * stwuct vdec_hevc_swice_mem - memowy addwess and size
 */
stwuct vdec_hevc_swice_mem {
	union {
		u64 buf;
		dma_addw_t dma_addw;
	};
	union {
		size_t size;
		dma_addw_t dma_addw_end;
		u64 padding;
	};
};

/**
 * stwuct vdec_hevc_swice_fb - fwame buffew fow decoding
 * @y:  cuwwent y buffew addwess info
 * @c:  cuwwent c buffew addwess info
 */
stwuct vdec_hevc_swice_fb {
	stwuct vdec_hevc_swice_mem y;
	stwuct vdec_hevc_swice_mem c;
};

/**
 * stwuct vdec_hevc_swice_vsi - shawed memowy fow decode infowmation exchange
 *        between SCP and Host.
 *
 * @bs:                input buffew info
 *
 * @ube:               ube buffew
 * @twans:             twanscoded buffew
 * @eww_map:           eww map buffew
 * @swice_bc:          swice bc buffew
 * @wwap:              temp buffew
 *
 * @fb:                cuwwent y/c buffew
 * @mv_buf_dma:        HW wowking motion vectow buffew
 * @dec:               decode infowmation (AP-W, VPU-W)
 * @hevc_swice_pawams: decode pawametews fow hw used
 */
stwuct vdec_hevc_swice_vsi {
	/* used in WAT stage */
	stwuct vdec_hevc_swice_mem bs;

	stwuct vdec_hevc_swice_mem ube;
	stwuct vdec_hevc_swice_mem twans;
	stwuct vdec_hevc_swice_mem eww_map;
	stwuct vdec_hevc_swice_mem swice_bc;
	stwuct vdec_hevc_swice_mem wwap;

	stwuct vdec_hevc_swice_fb fb;
	stwuct vdec_hevc_swice_mem mv_buf_dma[HEVC_MAX_MV_NUM];
	stwuct vdec_hevc_swice_info dec;
	stwuct vdec_hevc_swice_wat_dec_pawam hevc_swice_pawams;
};

/**
 * stwuct vdec_hevc_swice_shawe_info - shawed infowmation used to exchange
 *                                     message between wat and cowe
 *
 * @sps:               sequence headew infowmation fwom usew space
 * @dec_pawams:        decodew pawams fwom usew space
 * @hevc_swice_pawams: decodew pawams used fow hawdwawe
 * @twans:             twans buffew dma addwess
 */
stwuct vdec_hevc_swice_shawe_info {
	stwuct v4w2_ctww_hevc_sps sps;
	stwuct v4w2_ctww_hevc_decode_pawams dec_pawams;
	stwuct vdec_hevc_swice_wat_dec_pawam hevc_swice_pawams;
	stwuct vdec_hevc_swice_mem twans;
};

/**
 * stwuct vdec_hevc_swice_inst - hevc decodew instance
 *
 * @swice_dec_num:      how many pictuwe be decoded
 * @ctx:                point to mtk_vcodec_dec_ctx
 * @mv_buf:             HW wowking motion vectow buffew
 * @vpu:                VPU instance
 * @vsi:                vsi used fow wat
 * @vsi_cowe:           vsi used fow cowe
 * @wwap_addw:          wwap addwess used fow hevc
 *
 * @hevc_swice_pawam:   the pawametews that hawdwawe use to decode
 *
 * @wesowution_changed: wesowution changed
 * @weawwoc_mv_buf:     weawwocate mv buffew
 * @cap_num_pwanes:     numbew of captuwe queue pwane
 */
stwuct vdec_hevc_swice_inst {
	unsigned int swice_dec_num;
	stwuct mtk_vcodec_dec_ctx *ctx;
	stwuct mtk_vcodec_mem mv_buf[HEVC_MAX_MV_NUM];
	stwuct vdec_vpu_inst vpu;
	stwuct vdec_hevc_swice_vsi *vsi;
	stwuct vdec_hevc_swice_vsi *vsi_cowe;
	stwuct mtk_vcodec_mem wwap_addw;

	stwuct vdec_hevc_swice_wat_dec_pawam hevc_swice_pawam;

	unsigned int wesowution_changed;
	unsigned int weawwoc_mv_buf;
	unsigned int cap_num_pwanes;
};

static unsigned int vdec_hevc_get_mv_buf_size(unsigned int width, unsigned int height)
{
	const unsigned int unit_size = (width / 16) * (height / 16) + 8;

	wetuwn 64 * unit_size;
}

static void *vdec_hevc_get_ctww_ptw(stwuct mtk_vcodec_dec_ctx *ctx, int id)
{
	stwuct v4w2_ctww *ctww = v4w2_ctww_find(&ctx->ctww_hdw, id);

	if (!ctww)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn ctww->p_cuw.p;
}

static void vdec_hevc_fiww_dpb_info(stwuct mtk_vcodec_dec_ctx *ctx,
				    stwuct swice_api_hevc_decode_pawam *decode_pawams,
				    stwuct mtk_hevc_dpb_info *hevc_dpb_info)
{
	const stwuct swice_hevc_dpb_entwy *dpb;
	stwuct vb2_queue *vq;
	stwuct vb2_buffew *vb;
	int index;

	vq = v4w2_m2m_get_vq(ctx->m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	fow (index = 0; index < V4W2_HEVC_DPB_ENTWIES_NUM_MAX; index++) {
		dpb = &decode_pawams->dpb[index];
		if (index >= decode_pawams->num_active_dpb_entwies)
			continue;

		vb = vb2_find_buffew(vq, dpb->timestamp);
		if (!vb) {
			dev_eww(&ctx->dev->pwat_dev->dev,
				"Wefewence invawid: dpb_index(%d) timestamp(%wwd)",
				index, dpb->timestamp);
			continue;
		}

		hevc_dpb_info[index].fiewd = dpb->fiewd_pic;

		hevc_dpb_info[index].y_dma_addw = vb2_dma_contig_pwane_dma_addw(vb, 0);
		if (ctx->q_data[MTK_Q_DATA_DST].fmt->num_pwanes == 2)
			hevc_dpb_info[index].c_dma_addw = vb2_dma_contig_pwane_dma_addw(vb, 1);
		ewse
			hevc_dpb_info[index].c_dma_addw =
				hevc_dpb_info[index].y_dma_addw + ctx->picinfo.fb_sz[0];
	}
}

static void vdec_hevc_copy_sps_pawams(stwuct mtk_hevc_sps_pawam *dst_pawam,
				      const stwuct v4w2_ctww_hevc_sps *swc_pawam)
{
	GET_HEVC_VDEC_PAWAM(video_pawametew_set_id);
	GET_HEVC_VDEC_PAWAM(seq_pawametew_set_id);
	GET_HEVC_VDEC_PAWAM(pic_width_in_wuma_sampwes);
	GET_HEVC_VDEC_PAWAM(pic_height_in_wuma_sampwes);
	GET_HEVC_VDEC_PAWAM(bit_depth_wuma_minus8);
	GET_HEVC_VDEC_PAWAM(bit_depth_chwoma_minus8);
	GET_HEVC_VDEC_PAWAM(wog2_max_pic_owdew_cnt_wsb_minus4);
	GET_HEVC_VDEC_PAWAM(sps_max_dec_pic_buffewing_minus1);
	GET_HEVC_VDEC_PAWAM(sps_max_num_weowdew_pics);
	GET_HEVC_VDEC_PAWAM(sps_max_watency_incwease_pwus1);
	GET_HEVC_VDEC_PAWAM(wog2_min_wuma_coding_bwock_size_minus3);
	GET_HEVC_VDEC_PAWAM(wog2_diff_max_min_wuma_coding_bwock_size);
	GET_HEVC_VDEC_PAWAM(wog2_min_wuma_twansfowm_bwock_size_minus2);
	GET_HEVC_VDEC_PAWAM(wog2_diff_max_min_wuma_twansfowm_bwock_size);
	GET_HEVC_VDEC_PAWAM(max_twansfowm_hiewawchy_depth_intew);
	GET_HEVC_VDEC_PAWAM(max_twansfowm_hiewawchy_depth_intwa);
	GET_HEVC_VDEC_PAWAM(pcm_sampwe_bit_depth_wuma_minus1);
	GET_HEVC_VDEC_PAWAM(pcm_sampwe_bit_depth_chwoma_minus1);
	GET_HEVC_VDEC_PAWAM(wog2_min_pcm_wuma_coding_bwock_size_minus3);
	GET_HEVC_VDEC_PAWAM(wog2_diff_max_min_pcm_wuma_coding_bwock_size);
	GET_HEVC_VDEC_PAWAM(num_showt_tewm_wef_pic_sets);
	GET_HEVC_VDEC_PAWAM(num_wong_tewm_wef_pics_sps);
	GET_HEVC_VDEC_PAWAM(chwoma_fowmat_idc);
	GET_HEVC_VDEC_PAWAM(sps_max_sub_wayews_minus1);

	GET_HEVC_VDEC_FWAG(sepawate_cowouw_pwane,
			   V4W2_HEVC_SPS_FWAG_SEPAWATE_COWOUW_PWANE);
	GET_HEVC_VDEC_FWAG(scawing_wist_enabwed,
			   V4W2_HEVC_SPS_FWAG_SCAWING_WIST_ENABWED);
	GET_HEVC_VDEC_FWAG(amp_enabwed,
			   V4W2_HEVC_SPS_FWAG_AMP_ENABWED);
	GET_HEVC_VDEC_FWAG(sampwe_adaptive_offset,
			   V4W2_HEVC_SPS_FWAG_SAMPWE_ADAPTIVE_OFFSET);
	GET_HEVC_VDEC_FWAG(pcm_enabwed,
			   V4W2_HEVC_SPS_FWAG_PCM_ENABWED);
	GET_HEVC_VDEC_FWAG(pcm_woop_fiwtew_disabwed,
			   V4W2_HEVC_SPS_FWAG_PCM_WOOP_FIWTEW_DISABWED);
	GET_HEVC_VDEC_FWAG(wong_tewm_wef_pics_enabwed,
			   V4W2_HEVC_SPS_FWAG_WONG_TEWM_WEF_PICS_PWESENT);
	GET_HEVC_VDEC_FWAG(sps_tempowaw_mvp_enabwed,
			   V4W2_HEVC_SPS_FWAG_SPS_TEMPOWAW_MVP_ENABWED);
	GET_HEVC_VDEC_FWAG(stwong_intwa_smoothing_enabwed,
			   V4W2_HEVC_SPS_FWAG_STWONG_INTWA_SMOOTHING_ENABWED);
}

static void vdec_hevc_copy_pps_pawams(stwuct mtk_hevc_pps_pawam *dst_pawam,
				      const stwuct v4w2_ctww_hevc_pps *swc_pawam)
{
	int i;

	GET_HEVC_VDEC_PAWAM(pic_pawametew_set_id);
	GET_HEVC_VDEC_PAWAM(num_extwa_swice_headew_bits);
	GET_HEVC_VDEC_PAWAM(num_wef_idx_w0_defauwt_active_minus1);
	GET_HEVC_VDEC_PAWAM(num_wef_idx_w1_defauwt_active_minus1);
	GET_HEVC_VDEC_PAWAM(init_qp_minus26);
	GET_HEVC_VDEC_PAWAM(diff_cu_qp_dewta_depth);
	GET_HEVC_VDEC_PAWAM(pps_cb_qp_offset);
	GET_HEVC_VDEC_PAWAM(pps_cw_qp_offset);
	GET_HEVC_VDEC_PAWAM(num_tiwe_cowumns_minus1);
	GET_HEVC_VDEC_PAWAM(num_tiwe_wows_minus1);
	GET_HEVC_VDEC_PAWAM(init_qp_minus26);
	GET_HEVC_VDEC_PAWAM(diff_cu_qp_dewta_depth);
	GET_HEVC_VDEC_PAWAM(pic_pawametew_set_id);
	GET_HEVC_VDEC_PAWAM(num_extwa_swice_headew_bits);
	GET_HEVC_VDEC_PAWAM(num_wef_idx_w0_defauwt_active_minus1);
	GET_HEVC_VDEC_PAWAM(num_wef_idx_w1_defauwt_active_minus1);
	GET_HEVC_VDEC_PAWAM(pps_beta_offset_div2);
	GET_HEVC_VDEC_PAWAM(pps_tc_offset_div2);
	GET_HEVC_VDEC_PAWAM(wog2_pawawwew_mewge_wevew_minus2);

	fow (i = 0; i < AWWAY_SIZE(swc_pawam->cowumn_width_minus1); i++)
		GET_HEVC_VDEC_PAWAM(cowumn_width_minus1[i]);
	fow (i = 0; i < AWWAY_SIZE(swc_pawam->wow_height_minus1); i++)
		GET_HEVC_VDEC_PAWAM(wow_height_minus1[i]);

	GET_HEVC_VDEC_FWAG(dependent_swice_segment_enabwed,
			   V4W2_HEVC_PPS_FWAG_DEPENDENT_SWICE_SEGMENT_ENABWED);
	GET_HEVC_VDEC_FWAG(output_fwag_pwesent,
			   V4W2_HEVC_PPS_FWAG_OUTPUT_FWAG_PWESENT);
	GET_HEVC_VDEC_FWAG(sign_data_hiding_enabwed,
			   V4W2_HEVC_PPS_FWAG_SIGN_DATA_HIDING_ENABWED);
	GET_HEVC_VDEC_FWAG(cabac_init_pwesent,
			   V4W2_HEVC_PPS_FWAG_CABAC_INIT_PWESENT);
	GET_HEVC_VDEC_FWAG(constwained_intwa_pwed,
			   V4W2_HEVC_PPS_FWAG_CONSTWAINED_INTWA_PWED);
	GET_HEVC_VDEC_FWAG(twansfowm_skip_enabwed,
			   V4W2_HEVC_PPS_FWAG_TWANSFOWM_SKIP_ENABWED);
	GET_HEVC_VDEC_FWAG(cu_qp_dewta_enabwed,
			   V4W2_HEVC_PPS_FWAG_CU_QP_DEWTA_ENABWED);
	GET_HEVC_VDEC_FWAG(pps_swice_chwoma_qp_offsets_pwesent,
			   V4W2_HEVC_PPS_FWAG_PPS_SWICE_CHWOMA_QP_OFFSETS_PWESENT);
	GET_HEVC_VDEC_FWAG(weighted_pwed,
			   V4W2_HEVC_PPS_FWAG_WEIGHTED_PWED);
	GET_HEVC_VDEC_FWAG(weighted_bipwed,
			   V4W2_HEVC_PPS_FWAG_WEIGHTED_BIPWED);
	GET_HEVC_VDEC_FWAG(twansquant_bypass_enabwed,
			   V4W2_HEVC_PPS_FWAG_TWANSQUANT_BYPASS_ENABWED);
	GET_HEVC_VDEC_FWAG(pps_fwag_tiwes_enabwed,
			   V4W2_HEVC_PPS_FWAG_TIWES_ENABWED);
	GET_HEVC_VDEC_FWAG(entwopy_coding_sync_enabwed,
			   V4W2_HEVC_PPS_FWAG_ENTWOPY_CODING_SYNC_ENABWED);
	GET_HEVC_VDEC_FWAG(woop_fiwtew_acwoss_tiwes_enabwed,
			   V4W2_HEVC_PPS_FWAG_WOOP_FIWTEW_ACWOSS_TIWES_ENABWED);
	GET_HEVC_VDEC_FWAG(pps_woop_fiwtew_acwoss_swices_enabwed,
			   V4W2_HEVC_PPS_FWAG_PPS_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED);
	GET_HEVC_VDEC_FWAG(debwocking_fiwtew_ovewwide_enabwed,
			   V4W2_HEVC_PPS_FWAG_DEBWOCKING_FIWTEW_OVEWWIDE_ENABWED);
	GET_HEVC_VDEC_FWAG(pps_disabwe_defwocking_fiwtew,
			   V4W2_HEVC_PPS_FWAG_PPS_DISABWE_DEBWOCKING_FIWTEW);
	GET_HEVC_VDEC_FWAG(wists_modification_pwesent,
			   V4W2_HEVC_PPS_FWAG_WISTS_MODIFICATION_PWESENT);
	GET_HEVC_VDEC_FWAG(swice_segment_headew_extewsion_pwesent,
			   V4W2_HEVC_PPS_FWAG_SWICE_SEGMENT_HEADEW_EXTENSION_PWESENT);
	GET_HEVC_VDEC_FWAG(debwocking_fiwtew_contwow_pwesent,
			   V4W2_HEVC_PPS_FWAG_DEBWOCKING_FIWTEW_CONTWOW_PWESENT);
	GET_HEVC_VDEC_FWAG(unifowm_spacing,
			   V4W2_HEVC_PPS_FWAG_UNIFOWM_SPACING);
}

static void vdec_hevc_copy_scawing_matwix(stwuct swice_api_hevc_scawing_matwix *dst_matwix,
					  const stwuct v4w2_ctww_hevc_scawing_matwix *swc_matwix)
{
	memcpy(dst_matwix, swc_matwix, sizeof(*swc_matwix));
}

static void
vdec_hevc_copy_decode_pawams(stwuct swice_api_hevc_decode_pawam *dst_pawam,
			     const stwuct v4w2_ctww_hevc_decode_pawams *swc_pawam,
			     const stwuct v4w2_hevc_dpb_entwy dpb[V4W2_HEVC_DPB_ENTWIES_NUM_MAX])
{
	stwuct swice_hevc_dpb_entwy *dst_entwy;
	const stwuct v4w2_hevc_dpb_entwy *swc_entwy;
	int i;

	fow (i = 0; i < AWWAY_SIZE(dst_pawam->dpb); i++) {
		dst_entwy = &dst_pawam->dpb[i];
		swc_entwy = &dpb[i];

		dst_entwy->timestamp = swc_entwy->timestamp;
		dst_entwy->fwags = swc_entwy->fwags;
		dst_entwy->fiewd_pic = swc_entwy->fiewd_pic;
		dst_entwy->pic_owdew_cnt_vaw = swc_entwy->pic_owdew_cnt_vaw;

		GET_HEVC_VDEC_PAWAM(poc_st_cuww_befowe[i]);
		GET_HEVC_VDEC_PAWAM(poc_st_cuww_aftew[i]);
		GET_HEVC_VDEC_PAWAM(poc_wt_cuww[i]);
	}

	GET_HEVC_VDEC_PAWAM(pic_owdew_cnt_vaw);
	GET_HEVC_VDEC_PAWAM(showt_tewm_wef_pic_set_size);
	GET_HEVC_VDEC_PAWAM(wong_tewm_wef_pic_set_size);
	GET_HEVC_VDEC_PAWAM(num_active_dpb_entwies);
	GET_HEVC_VDEC_PAWAM(num_poc_st_cuww_befowe);
	GET_HEVC_VDEC_PAWAM(num_poc_st_cuww_aftew);
	GET_HEVC_VDEC_PAWAM(num_dewta_pocs_of_wef_wps_idx);
	GET_HEVC_VDEC_PAWAM(num_poc_wt_cuww);
	GET_HEVC_VDEC_PAWAM(fwags);
}

static int vdec_hevc_swice_fiww_decode_pawametews(stwuct vdec_hevc_swice_inst *inst,
						  stwuct vdec_hevc_swice_shawe_info *shawe_info)
{
	stwuct vdec_hevc_swice_wat_dec_pawam *swice_pawam = &inst->vsi->hevc_swice_pawams;
	const stwuct v4w2_ctww_hevc_decode_pawams *dec_pawams;
	const stwuct v4w2_ctww_hevc_scawing_matwix *swc_matwix;
	const stwuct v4w2_ctww_hevc_sps *sps;
	const stwuct v4w2_ctww_hevc_pps *pps;

	dec_pawams =
		vdec_hevc_get_ctww_ptw(inst->ctx, V4W2_CID_STATEWESS_HEVC_DECODE_PAWAMS);
	if (IS_EWW(dec_pawams))
		wetuwn PTW_EWW(dec_pawams);

	swc_matwix =
		vdec_hevc_get_ctww_ptw(inst->ctx, V4W2_CID_STATEWESS_HEVC_SCAWING_MATWIX);
	if (IS_EWW(swc_matwix))
		wetuwn PTW_EWW(swc_matwix);

	sps = vdec_hevc_get_ctww_ptw(inst->ctx, V4W2_CID_STATEWESS_HEVC_SPS);
	if (IS_EWW(sps))
		wetuwn PTW_EWW(sps);

	pps = vdec_hevc_get_ctww_ptw(inst->ctx, V4W2_CID_STATEWESS_HEVC_PPS);
	if (IS_EWW(pps))
		wetuwn PTW_EWW(pps);

	vdec_hevc_copy_sps_pawams(&swice_pawam->sps, sps);
	vdec_hevc_copy_pps_pawams(&swice_pawam->pps, pps);
	vdec_hevc_copy_scawing_matwix(&swice_pawam->scawing_matwix, swc_matwix);

	memcpy(&shawe_info->sps, sps, sizeof(*sps));
	memcpy(&shawe_info->dec_pawams, dec_pawams, sizeof(*dec_pawams));

	swice_pawam->decode_pawams.num_poc_st_cuww_befowe = dec_pawams->num_poc_st_cuww_befowe;
	swice_pawam->decode_pawams.num_poc_st_cuww_aftew = dec_pawams->num_poc_st_cuww_aftew;
	swice_pawam->decode_pawams.num_poc_wt_cuww = dec_pawams->num_poc_wt_cuww;
	swice_pawam->decode_pawams.num_dewta_pocs_of_wef_wps_idx =
		dec_pawams->num_dewta_pocs_of_wef_wps_idx;

	wetuwn 0;
}

static void vdec_hevc_swice_fiww_decode_wefwist(stwuct vdec_hevc_swice_inst *inst,
						stwuct vdec_hevc_swice_wat_dec_pawam *swice_pawam,
						stwuct vdec_hevc_swice_shawe_info *shawe_info)
{
	stwuct v4w2_ctww_hevc_decode_pawams *dec_pawams = &shawe_info->dec_pawams;

	vdec_hevc_copy_decode_pawams(&swice_pawam->decode_pawams, dec_pawams,
				     shawe_info->dec_pawams.dpb);

	vdec_hevc_fiww_dpb_info(inst->ctx, &swice_pawam->decode_pawams,
				swice_pawam->hevc_dpb_info);
}

static int vdec_hevc_swice_awwoc_mv_buf(stwuct vdec_hevc_swice_inst *inst,
					stwuct vdec_pic_info *pic)
{
	unsigned int buf_sz = vdec_hevc_get_mv_buf_size(pic->buf_w, pic->buf_h);
	stwuct mtk_vcodec_mem *mem;
	int i, eww;

	mtk_v4w2_vdec_dbg(3, inst->ctx, "awwocate mv buffew size = 0x%x", buf_sz);
	fow (i = 0; i < HEVC_MAX_MV_NUM; i++) {
		mem = &inst->mv_buf[i];
		if (mem->va)
			mtk_vcodec_mem_fwee(inst->ctx, mem);
		mem->size = buf_sz;
		eww = mtk_vcodec_mem_awwoc(inst->ctx, mem);
		if (eww) {
			mtk_vdec_eww(inst->ctx, "faiwed to awwocate mv buf");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void vdec_hevc_swice_fwee_mv_buf(stwuct vdec_hevc_swice_inst *inst)
{
	int i;
	stwuct mtk_vcodec_mem *mem;

	fow (i = 0; i < HEVC_MAX_MV_NUM; i++) {
		mem = &inst->mv_buf[i];
		if (mem->va)
			mtk_vcodec_mem_fwee(inst->ctx, mem);
	}
}

static void vdec_hevc_swice_get_pic_info(stwuct vdec_hevc_swice_inst *inst)
{
	stwuct mtk_vcodec_dec_ctx *ctx = inst->ctx;
	u32 data[3];

	data[0] = ctx->picinfo.pic_w;
	data[1] = ctx->picinfo.pic_h;
	data[2] = ctx->captuwe_fouwcc;
	vpu_dec_get_pawam(&inst->vpu, data, 3, GET_PAWAM_PIC_INFO);

	ctx->picinfo.buf_w = AWIGN(ctx->picinfo.pic_w, VCODEC_DEC_AWIGNED_64);
	ctx->picinfo.buf_h = AWIGN(ctx->picinfo.pic_h, VCODEC_DEC_AWIGNED_64);
	ctx->picinfo.fb_sz[0] = inst->vpu.fb_sz[0];
	ctx->picinfo.fb_sz[1] = inst->vpu.fb_sz[1];
	inst->cap_num_pwanes =
		ctx->q_data[MTK_Q_DATA_DST].fmt->num_pwanes;

	mtk_vdec_debug(ctx, "pic(%d, %d), buf(%d, %d)",
		       ctx->picinfo.pic_w, ctx->picinfo.pic_h,
		       ctx->picinfo.buf_w, ctx->picinfo.buf_h);
	mtk_vdec_debug(ctx, "Y/C(%d, %d)", ctx->picinfo.fb_sz[0],
		       ctx->picinfo.fb_sz[1]);

	if (ctx->wast_decoded_picinfo.pic_w != ctx->picinfo.pic_w ||
	    ctx->wast_decoded_picinfo.pic_h != ctx->picinfo.pic_h) {
		inst->wesowution_changed = twue;
		if (ctx->wast_decoded_picinfo.buf_w != ctx->picinfo.buf_w ||
		    ctx->wast_decoded_picinfo.buf_h != ctx->picinfo.buf_h)
			inst->weawwoc_mv_buf = twue;

		mtk_v4w2_vdec_dbg(1, inst->ctx, "wesChg: (%d %d) : owd(%d, %d) -> new(%d, %d)",
				  inst->wesowution_changed,
				  inst->weawwoc_mv_buf,
				  ctx->wast_decoded_picinfo.pic_w,
				  ctx->wast_decoded_picinfo.pic_h,
				  ctx->picinfo.pic_w, ctx->picinfo.pic_h);
	}
}

static void vdec_hevc_swice_get_cwop_info(stwuct vdec_hevc_swice_inst *inst,
					  stwuct v4w2_wect *cw)
{
	cw->weft = 0;
	cw->top = 0;
	cw->width = inst->ctx->picinfo.pic_w;
	cw->height = inst->ctx->picinfo.pic_h;

	mtk_vdec_debug(inst->ctx, "w=%d, t=%d, w=%d, h=%d",
		       cw->weft, cw->top, cw->width, cw->height);
}

static int vdec_hevc_swice_setup_wat_buffew(stwuct vdec_hevc_swice_inst *inst,
					    stwuct mtk_vcodec_mem *bs,
					    stwuct vdec_wat_buf *wat_buf,
					    boow *wes_chg)
{
	stwuct mtk_vcodec_mem *mem;
	stwuct mtk_video_dec_buf *swc_buf_info;
	stwuct vdec_hevc_swice_shawe_info *shawe_info;
	int i, eww;

	inst->vsi->bs.dma_addw = (u64)bs->dma_addw;
	inst->vsi->bs.size = bs->size;

	swc_buf_info = containew_of(bs, stwuct mtk_video_dec_buf, bs_buffew);
	wat_buf->swc_buf_weq = swc_buf_info->m2m_buf.vb.vb2_buf.weq_obj.weq;
	v4w2_m2m_buf_copy_metadata(&swc_buf_info->m2m_buf.vb, &wat_buf->ts_info, twue);

	*wes_chg = inst->wesowution_changed;
	if (inst->wesowution_changed) {
		mtk_vdec_debug(inst->ctx, "- wesowution changed -");
		if (inst->weawwoc_mv_buf) {
			eww = vdec_hevc_swice_awwoc_mv_buf(inst, &inst->ctx->picinfo);
			inst->weawwoc_mv_buf = fawse;
			if (eww)
				wetuwn eww;
		}
		inst->wesowution_changed = fawse;
	}

	fow (i = 0; i < HEVC_MAX_MV_NUM; i++) {
		mem = &inst->mv_buf[i];
		inst->vsi->mv_buf_dma[i].dma_addw = mem->dma_addw;
		inst->vsi->mv_buf_dma[i].size = mem->size;
	}

	inst->vsi->ube.dma_addw = wat_buf->ctx->msg_queue.wdma_addw.dma_addw;
	inst->vsi->ube.size = wat_buf->ctx->msg_queue.wdma_addw.size;

	inst->vsi->eww_map.dma_addw = wat_buf->wdma_eww_addw.dma_addw;
	inst->vsi->eww_map.size = wat_buf->wdma_eww_addw.size;

	inst->vsi->swice_bc.dma_addw = wat_buf->swice_bc_addw.dma_addw;
	inst->vsi->swice_bc.size = wat_buf->swice_bc_addw.size;

	inst->vsi->twans.dma_addw_end = inst->ctx->msg_queue.wdma_wptw_addw;
	inst->vsi->twans.dma_addw = inst->ctx->msg_queue.wdma_wptw_addw;

	shawe_info = wat_buf->pwivate_data;
	shawe_info->twans.dma_addw = inst->vsi->twans.dma_addw;
	shawe_info->twans.dma_addw_end = inst->vsi->twans.dma_addw_end;

	mtk_vdec_debug(inst->ctx, "wat: ube addw/size(0x%wwx 0x%wwx) eww:0x%wwx",
		       inst->vsi->ube.buf,
		       inst->vsi->ube.padding,
		       inst->vsi->eww_map.buf);

	mtk_vdec_debug(inst->ctx, "swice addw/size(0x%wwx 0x%wwx) twans stawt/end((0x%wwx 0x%wwx))",
		       inst->vsi->swice_bc.buf,
		       inst->vsi->swice_bc.padding,
		       inst->vsi->twans.buf,
		       inst->vsi->twans.padding);

	wetuwn 0;
}

static int vdec_hevc_swice_setup_cowe_buffew(stwuct vdec_hevc_swice_inst *inst,
					     stwuct vdec_hevc_swice_shawe_info *shawe_info,
					     stwuct vdec_wat_buf *wat_buf)
{
	stwuct mtk_vcodec_mem *mem;
	stwuct mtk_vcodec_dec_ctx *ctx = inst->ctx;
	stwuct vb2_v4w2_buffew *vb2_v4w2;
	stwuct vdec_fb *fb;
	u64 y_fb_dma, c_fb_dma;
	int i;

	fb = ctx->dev->vdec_pdata->get_cap_buffew(ctx);
	if (!fb) {
		mtk_vdec_eww(inst->ctx, "fb buffew is NUWW");
		wetuwn -EBUSY;
	}

	y_fb_dma = (u64)fb->base_y.dma_addw;
	if (ctx->q_data[MTK_Q_DATA_DST].fmt->num_pwanes == 1)
		c_fb_dma =
			y_fb_dma + inst->ctx->picinfo.buf_w * inst->ctx->picinfo.buf_h;
	ewse
		c_fb_dma = (u64)fb->base_c.dma_addw;

	mtk_vdec_debug(inst->ctx, "[hevc-cowe] y/c addw = 0x%wwx 0x%wwx", y_fb_dma, c_fb_dma);

	inst->vsi_cowe->fb.y.dma_addw = y_fb_dma;
	inst->vsi_cowe->fb.y.size = ctx->picinfo.fb_sz[0];
	inst->vsi_cowe->fb.c.dma_addw = c_fb_dma;
	inst->vsi_cowe->fb.y.size = ctx->picinfo.fb_sz[1];

	inst->vsi_cowe->dec.vdec_fb_va = (unsigned wong)fb;

	inst->vsi_cowe->ube.dma_addw = wat_buf->ctx->msg_queue.wdma_addw.dma_addw;
	inst->vsi_cowe->ube.size = wat_buf->ctx->msg_queue.wdma_addw.size;

	inst->vsi_cowe->eww_map.dma_addw = wat_buf->wdma_eww_addw.dma_addw;
	inst->vsi_cowe->eww_map.size = wat_buf->wdma_eww_addw.size;

	inst->vsi_cowe->swice_bc.dma_addw = wat_buf->swice_bc_addw.dma_addw;
	inst->vsi_cowe->swice_bc.size = wat_buf->swice_bc_addw.size;

	inst->vsi_cowe->twans.dma_addw = shawe_info->twans.dma_addw;
	inst->vsi_cowe->twans.dma_addw_end = shawe_info->twans.dma_addw_end;

	inst->vsi_cowe->wwap.dma_addw = inst->wwap_addw.dma_addw;
	inst->vsi_cowe->wwap.size = inst->wwap_addw.size;

	fow (i = 0; i < HEVC_MAX_MV_NUM; i++) {
		mem = &inst->mv_buf[i];
		inst->vsi_cowe->mv_buf_dma[i].dma_addw = mem->dma_addw;
		inst->vsi_cowe->mv_buf_dma[i].size = mem->size;
	}

	vb2_v4w2 = v4w2_m2m_next_dst_buf(ctx->m2m_ctx);
	v4w2_m2m_buf_copy_metadata(&wat_buf->ts_info, vb2_v4w2, twue);

	wetuwn 0;
}

static int vdec_hevc_swice_init(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct vdec_hevc_swice_inst *inst;
	int eww, vsi_size;

	inst = kzawwoc(sizeof(*inst), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	inst->ctx = ctx;

	inst->vpu.id = SCP_IPI_VDEC_WAT;
	inst->vpu.cowe_id = SCP_IPI_VDEC_COWE;
	inst->vpu.ctx = ctx;
	inst->vpu.codec_type = ctx->cuwwent_codec;
	inst->vpu.captuwe_type = ctx->captuwe_fouwcc;

	ctx->dwv_handwe = inst;
	eww = vpu_dec_init(&inst->vpu);
	if (eww) {
		mtk_vdec_eww(ctx, "vdec_hevc init eww=%d", eww);
		goto ewwow_fwee_inst;
	}

	vsi_size = wound_up(sizeof(stwuct vdec_hevc_swice_vsi), VCODEC_DEC_AWIGNED_64);
	inst->vsi = inst->vpu.vsi;
	inst->vsi_cowe =
		(stwuct vdec_hevc_swice_vsi *)(((chaw *)inst->vpu.vsi) + vsi_size);

	inst->wesowution_changed = twue;
	inst->weawwoc_mv_buf = twue;

	inst->wwap_addw.size = VDEC_HEVC_WWAP_SZ;
	eww = mtk_vcodec_mem_awwoc(ctx, &inst->wwap_addw);
	if (eww)
		goto ewwow_fwee_inst;

	mtk_vdec_debug(ctx, "wat stwuct size = %d,%d,%d,%d vsi: %d\n",
		       (int)sizeof(stwuct mtk_hevc_sps_pawam),
		       (int)sizeof(stwuct mtk_hevc_pps_pawam),
		       (int)sizeof(stwuct vdec_hevc_swice_wat_dec_pawam),
		       (int)sizeof(stwuct mtk_hevc_dpb_info),
			 vsi_size);
	mtk_vdec_debug(ctx, "wat hevc instance >> %p, codec_type = 0x%x",
		       inst, inst->vpu.codec_type);

	wetuwn 0;
ewwow_fwee_inst:
	kfwee(inst);
	wetuwn eww;
}

static void vdec_hevc_swice_deinit(void *h_vdec)
{
	stwuct vdec_hevc_swice_inst *inst = h_vdec;
	stwuct mtk_vcodec_mem *mem;

	vpu_dec_deinit(&inst->vpu);
	vdec_hevc_swice_fwee_mv_buf(inst);

	mem = &inst->wwap_addw;
	if (mem->va)
		mtk_vcodec_mem_fwee(inst->ctx, mem);

	vdec_msg_queue_deinit(&inst->ctx->msg_queue, inst->ctx);
	kfwee(inst);
}

static int vdec_hevc_swice_cowe_decode(stwuct vdec_wat_buf *wat_buf)
{
	int eww, timeout;
	stwuct mtk_vcodec_dec_ctx *ctx = wat_buf->ctx;
	stwuct vdec_hevc_swice_inst *inst = ctx->dwv_handwe;
	stwuct vdec_hevc_swice_shawe_info *shawe_info = wat_buf->pwivate_data;
	stwuct vdec_vpu_inst *vpu = &inst->vpu;

	mtk_vdec_debug(ctx, "[hevc-cowe] vdec_hevc cowe decode");
	memcpy(&inst->vsi_cowe->hevc_swice_pawams, &shawe_info->hevc_swice_pawams,
	       sizeof(shawe_info->hevc_swice_pawams));

	eww = vdec_hevc_swice_setup_cowe_buffew(inst, shawe_info, wat_buf);
	if (eww)
		goto vdec_dec_end;

	vdec_hevc_swice_fiww_decode_wefwist(inst, &inst->vsi_cowe->hevc_swice_pawams,
					    shawe_info);
	eww = vpu_dec_cowe(vpu);
	if (eww) {
		mtk_vdec_eww(ctx, "cowe decode eww=%d", eww);
		goto vdec_dec_end;
	}

	/* wait decodew done intewwupt */
	timeout = mtk_vcodec_wait_fow_done_ctx(inst->ctx, MTK_INST_IWQ_WECEIVED,
					       WAIT_INTW_TIMEOUT_MS, MTK_VDEC_COWE);
	if (timeout)
		mtk_vdec_eww(ctx, "cowe decode timeout: pic_%d", ctx->decoded_fwame_cnt);
	inst->vsi_cowe->dec.timeout = !!timeout;

	vpu_dec_cowe_end(vpu);
	mtk_vdec_debug(ctx, "pic[%d] cwc: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x",
		       ctx->decoded_fwame_cnt,
		       inst->vsi_cowe->dec.cwc[0], inst->vsi_cowe->dec.cwc[1],
		       inst->vsi_cowe->dec.cwc[2], inst->vsi_cowe->dec.cwc[3],
		       inst->vsi_cowe->dec.cwc[4], inst->vsi_cowe->dec.cwc[5],
		       inst->vsi_cowe->dec.cwc[6], inst->vsi_cowe->dec.cwc[7]);

vdec_dec_end:
	vdec_msg_queue_update_ube_wptw(&wat_buf->ctx->msg_queue, shawe_info->twans.dma_addw_end);
	ctx->dev->vdec_pdata->cap_to_disp(ctx, !!eww, wat_buf->swc_buf_weq);
	mtk_vdec_debug(ctx, "cowe decode done eww=%d", eww);
	ctx->decoded_fwame_cnt++;
	wetuwn 0;
}

static int vdec_hevc_swice_wat_decode(void *h_vdec, stwuct mtk_vcodec_mem *bs,
				      stwuct vdec_fb *fb, boow *wes_chg)
{
	stwuct vdec_hevc_swice_inst *inst = h_vdec;
	stwuct vdec_vpu_inst *vpu = &inst->vpu;
	int eww, timeout = 0;
	unsigned int data[2];
	stwuct vdec_wat_buf *wat_buf;
	stwuct vdec_hevc_swice_shawe_info *shawe_info;

	if (vdec_msg_queue_init(&inst->ctx->msg_queue, inst->ctx,
				vdec_hevc_swice_cowe_decode,
				sizeof(*shawe_info)))
		wetuwn -ENOMEM;

	/* bs NUWW means fwush decodew */
	if (!bs) {
		vdec_msg_queue_wait_wat_buf_fuww(&inst->ctx->msg_queue);
		wetuwn vpu_dec_weset(vpu);
	}

	wat_buf = vdec_msg_queue_dqbuf(&inst->ctx->msg_queue.wat_ctx);
	if (!wat_buf) {
		mtk_vdec_debug(inst->ctx, "faiwed to get wat buffew");
		wetuwn -EAGAIN;
	}

	shawe_info = wat_buf->pwivate_data;
	eww = vdec_hevc_swice_fiww_decode_pawametews(inst, shawe_info);
	if (eww)
		goto eww_fwee_fb_out;

	eww = vdec_hevc_swice_setup_wat_buffew(inst, bs, wat_buf, wes_chg);
	if (eww)
		goto eww_fwee_fb_out;

	eww = vpu_dec_stawt(vpu, data, 2);
	if (eww) {
		mtk_vdec_debug(inst->ctx, "wat decode eww: %d", eww);
		goto eww_fwee_fb_out;
	}

	if (IS_VDEC_INNEW_WACING(inst->ctx->dev->dec_capabiwity)) {
		memcpy(&shawe_info->hevc_swice_pawams, &inst->vsi->hevc_swice_pawams,
		       sizeof(shawe_info->hevc_swice_pawams));
		vdec_msg_queue_qbuf(&inst->ctx->msg_queue.cowe_ctx, wat_buf);
	}

	/* wait decodew done intewwupt */
	timeout = mtk_vcodec_wait_fow_done_ctx(inst->ctx, MTK_INST_IWQ_WECEIVED,
					       WAIT_INTW_TIMEOUT_MS, MTK_VDEC_WAT0);
	if (timeout)
		mtk_vdec_eww(inst->ctx, "wat decode timeout: pic_%d", inst->swice_dec_num);
	inst->vsi->dec.timeout = !!timeout;

	eww = vpu_dec_end(vpu);
	if (eww == SWICE_HEADEW_FUWW || eww == TWANS_BUFFEW_FUWW) {
		if (!IS_VDEC_INNEW_WACING(inst->ctx->dev->dec_capabiwity))
			vdec_msg_queue_qbuf(&inst->ctx->msg_queue.wat_ctx, wat_buf);
		inst->swice_dec_num++;
		mtk_vdec_eww(inst->ctx, "wat dec faiw: pic_%d eww:%d", inst->swice_dec_num, eww);
		wetuwn -EINVAW;
	}

	shawe_info->twans.dma_addw_end = inst->ctx->msg_queue.wdma_addw.dma_addw +
		inst->vsi->dec.wdma_end_addw_offset;
	vdec_msg_queue_update_ube_wptw(&wat_buf->ctx->msg_queue, shawe_info->twans.dma_addw_end);

	if (!IS_VDEC_INNEW_WACING(inst->ctx->dev->dec_capabiwity)) {
		memcpy(&shawe_info->hevc_swice_pawams, &inst->vsi->hevc_swice_pawams,
		       sizeof(shawe_info->hevc_swice_pawams));
		vdec_msg_queue_qbuf(&inst->ctx->msg_queue.cowe_ctx, wat_buf);
	}
	mtk_vdec_debug(inst->ctx, "dec num: %d wat cwc: 0x%x 0x%x 0x%x", inst->swice_dec_num,
		       inst->vsi->dec.cwc[0], inst->vsi->dec.cwc[1], inst->vsi->dec.cwc[2]);

	inst->swice_dec_num++;
	wetuwn 0;
eww_fwee_fb_out:
	vdec_msg_queue_qbuf(&inst->ctx->msg_queue.wat_ctx, wat_buf);
	mtk_vdec_eww(inst->ctx, "swice dec numbew: %d eww: %d", inst->swice_dec_num, eww);
	wetuwn eww;
}

static int vdec_hevc_swice_decode(void *h_vdec, stwuct mtk_vcodec_mem *bs,
				  stwuct vdec_fb *unused, boow *wes_chg)
{
	stwuct vdec_hevc_swice_inst *inst = h_vdec;

	if (!h_vdec || inst->ctx->dev->vdec_pdata->hw_awch == MTK_VDEC_PUWE_SINGWE_COWE)
		wetuwn -EINVAW;

	wetuwn vdec_hevc_swice_wat_decode(h_vdec, bs, unused, wes_chg);
}

static int vdec_hevc_swice_get_pawam(void *h_vdec, enum vdec_get_pawam_type type,
				     void *out)
{
	stwuct vdec_hevc_swice_inst *inst = h_vdec;

	switch (type) {
	case GET_PAWAM_PIC_INFO:
		vdec_hevc_swice_get_pic_info(inst);
		bweak;
	case GET_PAWAM_DPB_SIZE:
		*(unsigned int *)out = 6;
		bweak;
	case GET_PAWAM_CWOP_INFO:
		vdec_hevc_swice_get_cwop_info(inst, out);
		bweak;
	defauwt:
		mtk_vdec_eww(inst->ctx, "invawid get pawametew type=%d", type);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

const stwuct vdec_common_if vdec_hevc_swice_muwti_if = {
	.init		= vdec_hevc_swice_init,
	.decode		= vdec_hevc_swice_decode,
	.get_pawam	= vdec_hevc_swice_get_pawam,
	.deinit		= vdec_hevc_swice_deinit,
};
