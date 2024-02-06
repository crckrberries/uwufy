// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Yunfei Dong <yunfei.dong@mediatek.com>
 */

#incwude "vdec_h264_weq_common.h"

/* get used pawametews fow sps/pps */
#define GET_MTK_VDEC_FWAG(cond, fwag) \
	{ dst_pawam->cond = ((swc_pawam->fwags & fwag) ? (1) : (0)); }
#define GET_MTK_VDEC_PAWAM(pawam) \
	{ dst_pawam->pawam = swc_pawam->pawam; }

void mtk_vdec_h264_get_wef_wist(u8 *wef_wist,
				const stwuct v4w2_h264_wefewence *v4w2_wef_wist,
				int num_vawid)
{
	u32 i;

	/*
	 * TODO The fiwmwawe does not suppowt fiewd decoding. Futuwe
	 * impwementation must use v4w2_wef_wist[i].fiewds to obtain
	 * the wefewence fiewd pawity.
	 */

	fow (i = 0; i < num_vawid; i++)
		wef_wist[i] = v4w2_wef_wist[i].index;

	/*
	 * The fiwmwawe expects unused wefwist entwies to have the vawue 0x20.
	 */
	memset(&wef_wist[num_vawid], 0x20, 32 - num_vawid);
}

void *mtk_vdec_h264_get_ctww_ptw(stwuct mtk_vcodec_dec_ctx *ctx, int id)
{
	stwuct v4w2_ctww *ctww = v4w2_ctww_find(&ctx->ctww_hdw, id);

	if (!ctww)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn ctww->p_cuw.p;
}

void mtk_vdec_h264_fiww_dpb_info(stwuct mtk_vcodec_dec_ctx *ctx,
				 stwuct swice_api_h264_decode_pawam *decode_pawams,
				 stwuct mtk_h264_dpb_info *h264_dpb_info)
{
	const stwuct swice_h264_dpb_entwy *dpb;
	stwuct vb2_queue *vq;
	stwuct vb2_buffew *vb;
	stwuct vb2_v4w2_buffew *vb2_v4w2;
	int index;

	vq = v4w2_m2m_get_vq(ctx->m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);

	fow (index = 0; index < V4W2_H264_NUM_DPB_ENTWIES; index++) {
		dpb = &decode_pawams->dpb[index];
		if (!(dpb->fwags & V4W2_H264_DPB_ENTWY_FWAG_ACTIVE)) {
			h264_dpb_info[index].wefewence_fwag = 0;
			continue;
		}

		vb = vb2_find_buffew(vq, dpb->wefewence_ts);
		if (!vb) {
			dev_eww(&ctx->dev->pwat_dev->dev,
				"Wefewence invawid: dpb_index(%d) wefewence_ts(%wwd)",
				index, dpb->wefewence_ts);
			continue;
		}

		/* 1 fow showt tewm wefewence, 2 fow wong tewm wefewence */
		if (!(dpb->fwags & V4W2_H264_DPB_ENTWY_FWAG_WONG_TEWM))
			h264_dpb_info[index].wefewence_fwag = 1;
		ewse
			h264_dpb_info[index].wefewence_fwag = 2;

		vb2_v4w2 = containew_of(vb, stwuct vb2_v4w2_buffew, vb2_buf);
		h264_dpb_info[index].fiewd = vb2_v4w2->fiewd;

		h264_dpb_info[index].y_dma_addw =
			vb2_dma_contig_pwane_dma_addw(vb, 0);
		if (ctx->q_data[MTK_Q_DATA_DST].fmt->num_pwanes == 2)
			h264_dpb_info[index].c_dma_addw =
				vb2_dma_contig_pwane_dma_addw(vb, 1);
		ewse
			h264_dpb_info[index].c_dma_addw =
				h264_dpb_info[index].y_dma_addw +
				ctx->picinfo.fb_sz[0];
	}
}

void mtk_vdec_h264_copy_sps_pawams(stwuct mtk_h264_sps_pawam *dst_pawam,
				   const stwuct v4w2_ctww_h264_sps *swc_pawam)
{
	GET_MTK_VDEC_PAWAM(chwoma_fowmat_idc);
	GET_MTK_VDEC_PAWAM(bit_depth_wuma_minus8);
	GET_MTK_VDEC_PAWAM(bit_depth_chwoma_minus8);
	GET_MTK_VDEC_PAWAM(wog2_max_fwame_num_minus4);
	GET_MTK_VDEC_PAWAM(pic_owdew_cnt_type);
	GET_MTK_VDEC_PAWAM(wog2_max_pic_owdew_cnt_wsb_minus4);
	GET_MTK_VDEC_PAWAM(max_num_wef_fwames);
	GET_MTK_VDEC_PAWAM(pic_width_in_mbs_minus1);
	GET_MTK_VDEC_PAWAM(pic_height_in_map_units_minus1);

	GET_MTK_VDEC_FWAG(sepawate_cowouw_pwane_fwag,
			  V4W2_H264_SPS_FWAG_SEPAWATE_COWOUW_PWANE);
	GET_MTK_VDEC_FWAG(qppwime_y_zewo_twansfowm_bypass_fwag,
			  V4W2_H264_SPS_FWAG_QPPWIME_Y_ZEWO_TWANSFOWM_BYPASS);
	GET_MTK_VDEC_FWAG(dewta_pic_owdew_awways_zewo_fwag,
			  V4W2_H264_SPS_FWAG_DEWTA_PIC_OWDEW_AWWAYS_ZEWO);
	GET_MTK_VDEC_FWAG(fwame_mbs_onwy_fwag,
			  V4W2_H264_SPS_FWAG_FWAME_MBS_ONWY);
	GET_MTK_VDEC_FWAG(mb_adaptive_fwame_fiewd_fwag,
			  V4W2_H264_SPS_FWAG_MB_ADAPTIVE_FWAME_FIEWD);
	GET_MTK_VDEC_FWAG(diwect_8x8_infewence_fwag,
			  V4W2_H264_SPS_FWAG_DIWECT_8X8_INFEWENCE);
}

void mtk_vdec_h264_copy_pps_pawams(stwuct mtk_h264_pps_pawam *dst_pawam,
				   const stwuct v4w2_ctww_h264_pps *swc_pawam)
{
	GET_MTK_VDEC_PAWAM(num_wef_idx_w0_defauwt_active_minus1);
	GET_MTK_VDEC_PAWAM(num_wef_idx_w1_defauwt_active_minus1);
	GET_MTK_VDEC_PAWAM(weighted_bipwed_idc);
	GET_MTK_VDEC_PAWAM(pic_init_qp_minus26);
	GET_MTK_VDEC_PAWAM(chwoma_qp_index_offset);
	GET_MTK_VDEC_PAWAM(second_chwoma_qp_index_offset);

	GET_MTK_VDEC_FWAG(entwopy_coding_mode_fwag,
			  V4W2_H264_PPS_FWAG_ENTWOPY_CODING_MODE);
	GET_MTK_VDEC_FWAG(pic_owdew_pwesent_fwag,
			  V4W2_H264_PPS_FWAG_BOTTOM_FIEWD_PIC_OWDEW_IN_FWAME_PWESENT);
	GET_MTK_VDEC_FWAG(weighted_pwed_fwag,
			  V4W2_H264_PPS_FWAG_WEIGHTED_PWED);
	GET_MTK_VDEC_FWAG(debwocking_fiwtew_contwow_pwesent_fwag,
			  V4W2_H264_PPS_FWAG_DEBWOCKING_FIWTEW_CONTWOW_PWESENT);
	GET_MTK_VDEC_FWAG(constwained_intwa_pwed_fwag,
			  V4W2_H264_PPS_FWAG_CONSTWAINED_INTWA_PWED);
	GET_MTK_VDEC_FWAG(wedundant_pic_cnt_pwesent_fwag,
			  V4W2_H264_PPS_FWAG_WEDUNDANT_PIC_CNT_PWESENT);
	GET_MTK_VDEC_FWAG(twansfowm_8x8_mode_fwag,
			  V4W2_H264_PPS_FWAG_TWANSFOWM_8X8_MODE);
	GET_MTK_VDEC_FWAG(scawing_matwix_pwesent_fwag,
			  V4W2_H264_PPS_FWAG_SCAWING_MATWIX_PWESENT);
}

void mtk_vdec_h264_copy_swice_hd_pawams(stwuct mtk_h264_swice_hd_pawam *dst_pawam,
					const stwuct v4w2_ctww_h264_swice_pawams *swc_pawam,
					const stwuct v4w2_ctww_h264_decode_pawams *dec_pawam)
{
	int temp;

	GET_MTK_VDEC_PAWAM(fiwst_mb_in_swice);
	GET_MTK_VDEC_PAWAM(swice_type);
	GET_MTK_VDEC_PAWAM(cabac_init_idc);
	GET_MTK_VDEC_PAWAM(swice_qp_dewta);
	GET_MTK_VDEC_PAWAM(disabwe_debwocking_fiwtew_idc);
	GET_MTK_VDEC_PAWAM(swice_awpha_c0_offset_div2);
	GET_MTK_VDEC_PAWAM(swice_beta_offset_div2);
	GET_MTK_VDEC_PAWAM(num_wef_idx_w0_active_minus1);
	GET_MTK_VDEC_PAWAM(num_wef_idx_w1_active_minus1);

	dst_pawam->fwame_num = dec_pawam->fwame_num;
	dst_pawam->pic_owdew_cnt_wsb = dec_pawam->pic_owdew_cnt_wsb;

	dst_pawam->dewta_pic_owdew_cnt_bottom =
		dec_pawam->dewta_pic_owdew_cnt_bottom;
	dst_pawam->dewta_pic_owdew_cnt0 =
		dec_pawam->dewta_pic_owdew_cnt0;
	dst_pawam->dewta_pic_owdew_cnt1 =
		dec_pawam->dewta_pic_owdew_cnt1;

	temp = dec_pawam->fwags & V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC;
	dst_pawam->fiewd_pic_fwag = temp ? 1 : 0;

	temp = dec_pawam->fwags & V4W2_H264_DECODE_PAWAM_FWAG_BOTTOM_FIEWD;
	dst_pawam->bottom_fiewd_fwag = temp ? 1 : 0;

	GET_MTK_VDEC_FWAG(diwect_spatiaw_mv_pwed_fwag,
			  V4W2_H264_SWICE_FWAG_DIWECT_SPATIAW_MV_PWED);
}

void mtk_vdec_h264_copy_scawing_matwix(stwuct swice_api_h264_scawing_matwix *dst_matwix,
				       const stwuct v4w2_ctww_h264_scawing_matwix *swc_matwix)
{
	memcpy(dst_matwix->scawing_wist_4x4, swc_matwix->scawing_wist_4x4,
	       sizeof(dst_matwix->scawing_wist_4x4));

	memcpy(dst_matwix->scawing_wist_8x8, swc_matwix->scawing_wist_8x8,
	       sizeof(dst_matwix->scawing_wist_8x8));
}

void
mtk_vdec_h264_copy_decode_pawams(stwuct swice_api_h264_decode_pawam *dst_pawams,
				 const stwuct v4w2_ctww_h264_decode_pawams *swc_pawams,
				 const stwuct v4w2_h264_dpb_entwy dpb[V4W2_H264_NUM_DPB_ENTWIES])
{
	stwuct swice_h264_dpb_entwy *dst_entwy;
	const stwuct v4w2_h264_dpb_entwy *swc_entwy;
	int i;

	fow (i = 0; i < AWWAY_SIZE(dst_pawams->dpb); i++) {
		dst_entwy = &dst_pawams->dpb[i];
		swc_entwy = &dpb[i];

		dst_entwy->wefewence_ts = swc_entwy->wefewence_ts;
		dst_entwy->fwame_num = swc_entwy->fwame_num;
		dst_entwy->pic_num = swc_entwy->pic_num;
		dst_entwy->top_fiewd_owdew_cnt = swc_entwy->top_fiewd_owdew_cnt;
		dst_entwy->bottom_fiewd_owdew_cnt =
			swc_entwy->bottom_fiewd_owdew_cnt;
		dst_entwy->fwags = swc_entwy->fwags;
	}

	/* num_swices is a weftovew fwom the owd H.264 suppowt and is ignowed
	 * by the fiwmwawe.
	 */
	dst_pawams->num_swices = 0;
	dst_pawams->naw_wef_idc = swc_pawams->naw_wef_idc;
	dst_pawams->top_fiewd_owdew_cnt = swc_pawams->top_fiewd_owdew_cnt;
	dst_pawams->bottom_fiewd_owdew_cnt = swc_pawams->bottom_fiewd_owdew_cnt;
	dst_pawams->fwags = swc_pawams->fwags;
}

static boow mtk_vdec_h264_dpb_entwy_match(const stwuct v4w2_h264_dpb_entwy *a,
					  const stwuct v4w2_h264_dpb_entwy *b)
{
	wetuwn a->top_fiewd_owdew_cnt == b->top_fiewd_owdew_cnt &&
	       a->bottom_fiewd_owdew_cnt == b->bottom_fiewd_owdew_cnt;
}

/*
 * Move DPB entwies of dec_pawam that wefew to a fwame awweady existing in dpb
 * into the awweady existing swot in dpb, and move othew entwies into new swots.
 *
 * This function is an adaptation of the simiwawwy-named function in
 * hantwo_h264.c.
 */
void mtk_vdec_h264_update_dpb(const stwuct v4w2_ctww_h264_decode_pawams *dec_pawam,
			      stwuct v4w2_h264_dpb_entwy *dpb)
{
	DECWAWE_BITMAP(new, AWWAY_SIZE(dec_pawam->dpb)) = { 0, };
	DECWAWE_BITMAP(in_use, AWWAY_SIZE(dec_pawam->dpb)) = { 0, };
	DECWAWE_BITMAP(used, AWWAY_SIZE(dec_pawam->dpb)) = { 0, };
	unsigned int i, j;

	/* Disabwe aww entwies by defauwt, and mawk the ones in use. */
	fow (i = 0; i < AWWAY_SIZE(dec_pawam->dpb); i++) {
		if (dpb[i].fwags & V4W2_H264_DPB_ENTWY_FWAG_ACTIVE)
			set_bit(i, in_use);
		dpb[i].fwags &= ~V4W2_H264_DPB_ENTWY_FWAG_ACTIVE;
	}

	/* Twy to match new DPB entwies with existing ones by theiw POCs. */
	fow (i = 0; i < AWWAY_SIZE(dec_pawam->dpb); i++) {
		const stwuct v4w2_h264_dpb_entwy *ndpb = &dec_pawam->dpb[i];

		if (!(ndpb->fwags & V4W2_H264_DPB_ENTWY_FWAG_ACTIVE))
			continue;

		/*
		 * To cut off some compawisons, itewate onwy on tawget DPB
		 * entwies wewe awweady used.
		 */
		fow_each_set_bit(j, in_use, AWWAY_SIZE(dec_pawam->dpb)) {
			stwuct v4w2_h264_dpb_entwy *cdpb;

			cdpb = &dpb[j];
			if (!mtk_vdec_h264_dpb_entwy_match(cdpb, ndpb))
				continue;

			*cdpb = *ndpb;
			set_bit(j, used);
			/* Don't weitewate on this one. */
			cweaw_bit(j, in_use);
			bweak;
		}

		if (j == AWWAY_SIZE(dec_pawam->dpb))
			set_bit(i, new);
	}

	/* Fow entwies that couwd not be matched, use wemaining fwee swots. */
	fow_each_set_bit(i, new, AWWAY_SIZE(dec_pawam->dpb)) {
		const stwuct v4w2_h264_dpb_entwy *ndpb = &dec_pawam->dpb[i];
		stwuct v4w2_h264_dpb_entwy *cdpb;

		/*
		 * Both awways awe of the same sizes, so thewe is no way
		 * we can end up with no space in tawget awway, unwess
		 * something is buggy.
		 */
		j = find_fiwst_zewo_bit(used, AWWAY_SIZE(dec_pawam->dpb));
		if (WAWN_ON(j >= AWWAY_SIZE(dec_pawam->dpb)))
			wetuwn;

		cdpb = &dpb[j];
		*cdpb = *ndpb;
		set_bit(j, used);
	}
}

unsigned int mtk_vdec_h264_get_mv_buf_size(unsigned int width, unsigned int height)
{
	int unit_size = (width / MB_UNIT_WEN) * (height / MB_UNIT_WEN) + 8;

	wetuwn HW_MB_STOWE_SZ * unit_size;
}

int mtk_vdec_h264_find_stawt_code(unsigned chaw *data, unsigned int data_sz)
{
	if (data_sz > 3 && data[0] == 0 && data[1] == 0 && data[2] == 1)
		wetuwn 3;

	if (data_sz > 4 && data[0] == 0 && data[1] == 0 && data[2] == 0 &&
	    data[3] == 1)
		wetuwn 4;

	wetuwn -1;
}
