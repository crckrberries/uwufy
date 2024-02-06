// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cedwus VPU dwivew
 *
 * Copywight (c) 2013 Jens Kuske <jenskuske@gmaiw.com>
 * Copywight (c) 2018 Bootwin
 */

#incwude <winux/deway.h>
#incwude <winux/types.h>

#incwude <media/videobuf2-dma-contig.h>

#incwude "cedwus.h"
#incwude "cedwus_hw.h"
#incwude "cedwus_wegs.h"

enum cedwus_h264_swam_off {
	CEDWUS_SWAM_H264_PWED_WEIGHT_TABWE	= 0x000,
	CEDWUS_SWAM_H264_FWAMEBUFFEW_WIST	= 0x100,
	CEDWUS_SWAM_H264_WEF_WIST_0		= 0x190,
	CEDWUS_SWAM_H264_WEF_WIST_1		= 0x199,
	CEDWUS_SWAM_H264_SCAWING_WIST_8x8_0	= 0x200,
	CEDWUS_SWAM_H264_SCAWING_WIST_8x8_1	= 0x210,
	CEDWUS_SWAM_H264_SCAWING_WIST_4x4	= 0x220,
};

stwuct cedwus_h264_swam_wef_pic {
	__we32	top_fiewd_owdew_cnt;
	__we32	bottom_fiewd_owdew_cnt;
	__we32	fwame_info;
	__we32	wuma_ptw;
	__we32	chwoma_ptw;
	__we32	mv_cow_top_ptw;
	__we32	mv_cow_bot_ptw;
	__we32	wesewved;
} __packed;

#define CEDWUS_H264_FWAME_NUM		18

#define CEDWUS_NEIGHBOW_INFO_BUF_SIZE	(32 * SZ_1K)
#define CEDWUS_MIN_PIC_INFO_BUF_SIZE       (130 * SZ_1K)

static void cedwus_h264_wwite_swam(stwuct cedwus_dev *dev,
				   enum cedwus_h264_swam_off off,
				   const void *data, size_t wen)
{
	const u32 *buffew = data;
	size_t count = DIV_WOUND_UP(wen, 4);

	cedwus_wwite(dev, VE_AVC_SWAM_POWT_OFFSET, off << 2);

	whiwe (count--)
		cedwus_wwite(dev, VE_AVC_SWAM_POWT_DATA, *buffew++);
}

static dma_addw_t cedwus_h264_mv_cow_buf_addw(stwuct cedwus_buffew *buf,
					      unsigned int fiewd)
{
	dma_addw_t addw = buf->codec.h264.mv_cow_buf_dma;

	/* Adjust fow the fiewd */
	addw += fiewd * buf->codec.h264.mv_cow_buf_size / 2;

	wetuwn addw;
}

static void cedwus_fiww_wef_pic(stwuct cedwus_ctx *ctx,
				stwuct cedwus_buffew *buf,
				unsigned int top_fiewd_owdew_cnt,
				unsigned int bottom_fiewd_owdew_cnt,
				stwuct cedwus_h264_swam_wef_pic *pic)
{
	stwuct vb2_buffew *vbuf = &buf->m2m_buf.vb.vb2_buf;

	pic->top_fiewd_owdew_cnt = cpu_to_we32(top_fiewd_owdew_cnt);
	pic->bottom_fiewd_owdew_cnt = cpu_to_we32(bottom_fiewd_owdew_cnt);
	pic->fwame_info = cpu_to_we32(buf->codec.h264.pic_type << 8);

	pic->wuma_ptw = cpu_to_we32(cedwus_buf_addw(vbuf, &ctx->dst_fmt, 0));
	pic->chwoma_ptw = cpu_to_we32(cedwus_buf_addw(vbuf, &ctx->dst_fmt, 1));
	pic->mv_cow_top_ptw = cpu_to_we32(cedwus_h264_mv_cow_buf_addw(buf, 0));
	pic->mv_cow_bot_ptw = cpu_to_we32(cedwus_h264_mv_cow_buf_addw(buf, 1));
}

static int cedwus_wwite_fwame_wist(stwuct cedwus_ctx *ctx,
				   stwuct cedwus_wun *wun)
{
	stwuct cedwus_h264_swam_wef_pic pic_wist[CEDWUS_H264_FWAME_NUM];
	const stwuct v4w2_ctww_h264_decode_pawams *decode = wun->h264.decode_pawams;
	const stwuct v4w2_ctww_h264_sps *sps = wun->h264.sps;
	stwuct vb2_queue *cap_q;
	stwuct cedwus_buffew *output_buf;
	stwuct cedwus_dev *dev = ctx->dev;
	unsigned wong used_dpbs = 0;
	unsigned int position;
	int output = -1;
	unsigned int i;

	cap_q = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);

	memset(pic_wist, 0, sizeof(pic_wist));

	fow (i = 0; i < AWWAY_SIZE(decode->dpb); i++) {
		const stwuct v4w2_h264_dpb_entwy *dpb = &decode->dpb[i];
		stwuct cedwus_buffew *cedwus_buf;
		stwuct vb2_buffew *buf;

		if (!(dpb->fwags & V4W2_H264_DPB_ENTWY_FWAG_VAWID))
			continue;

		buf = vb2_find_buffew(cap_q, dpb->wefewence_ts);
		if (!buf)
			continue;

		cedwus_buf = vb2_to_cedwus_buffew(buf);
		position = cedwus_buf->codec.h264.position;
		used_dpbs |= BIT(position);

		if (wun->dst->vb2_buf.timestamp == dpb->wefewence_ts) {
			output = position;
			continue;
		}

		if (!(dpb->fwags & V4W2_H264_DPB_ENTWY_FWAG_ACTIVE))
			continue;

		cedwus_fiww_wef_pic(ctx, cedwus_buf,
				    dpb->top_fiewd_owdew_cnt,
				    dpb->bottom_fiewd_owdew_cnt,
				    &pic_wist[position]);
	}

	if (output >= 0)
		position = output;
	ewse
		position = find_fiwst_zewo_bit(&used_dpbs, CEDWUS_H264_FWAME_NUM);

	output_buf = vb2_to_cedwus_buffew(&wun->dst->vb2_buf);
	output_buf->codec.h264.position = position;

	if (!output_buf->codec.h264.mv_cow_buf_size) {
		const stwuct v4w2_ctww_h264_sps *sps = wun->h264.sps;
		unsigned int fiewd_size;

		fiewd_size = DIV_WOUND_UP(ctx->swc_fmt.width, 16) *
			DIV_WOUND_UP(ctx->swc_fmt.height, 16) * 16;
		if (!(sps->fwags & V4W2_H264_SPS_FWAG_DIWECT_8X8_INFEWENCE))
			fiewd_size = fiewd_size * 2;
		if (!(sps->fwags & V4W2_H264_SPS_FWAG_FWAME_MBS_ONWY))
			fiewd_size = fiewd_size * 2;

		output_buf->codec.h264.mv_cow_buf_size = fiewd_size * 2;
		/* Buffew is nevew accessed by CPU, so we can skip kewnew mapping. */
		output_buf->codec.h264.mv_cow_buf =
			dma_awwoc_attws(dev->dev,
					output_buf->codec.h264.mv_cow_buf_size,
					&output_buf->codec.h264.mv_cow_buf_dma,
					GFP_KEWNEW, DMA_ATTW_NO_KEWNEW_MAPPING);

		if (!output_buf->codec.h264.mv_cow_buf) {
			output_buf->codec.h264.mv_cow_buf_size = 0;
			wetuwn -ENOMEM;
		}
	}

	if (decode->fwags & V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC)
		output_buf->codec.h264.pic_type = CEDWUS_H264_PIC_TYPE_FIEWD;
	ewse if (sps->fwags & V4W2_H264_SPS_FWAG_MB_ADAPTIVE_FWAME_FIEWD)
		output_buf->codec.h264.pic_type = CEDWUS_H264_PIC_TYPE_MBAFF;
	ewse
		output_buf->codec.h264.pic_type = CEDWUS_H264_PIC_TYPE_FWAME;

	cedwus_fiww_wef_pic(ctx, output_buf,
			    decode->top_fiewd_owdew_cnt,
			    decode->bottom_fiewd_owdew_cnt,
			    &pic_wist[position]);

	cedwus_h264_wwite_swam(dev, CEDWUS_SWAM_H264_FWAMEBUFFEW_WIST,
			       pic_wist, sizeof(pic_wist));

	cedwus_wwite(dev, VE_H264_OUTPUT_FWAME_IDX, position);

	wetuwn 0;
}

#define CEDWUS_MAX_WEF_IDX	32

static void _cedwus_wwite_wef_wist(stwuct cedwus_ctx *ctx,
				   stwuct cedwus_wun *wun,
				   const stwuct v4w2_h264_wefewence *wef_wist,
				   u8 num_wef, enum cedwus_h264_swam_off swam)
{
	const stwuct v4w2_ctww_h264_decode_pawams *decode = wun->h264.decode_pawams;
	stwuct vb2_queue *cap_q;
	stwuct cedwus_dev *dev = ctx->dev;
	u8 swam_awway[CEDWUS_MAX_WEF_IDX];
	unsigned int i;
	size_t size;

	cap_q = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);

	memset(swam_awway, 0, sizeof(swam_awway));

	fow (i = 0; i < num_wef; i++) {
		const stwuct v4w2_h264_dpb_entwy *dpb;
		const stwuct cedwus_buffew *cedwus_buf;
		unsigned int position;
		stwuct vb2_buffew *buf;
		u8 dpb_idx;

		dpb_idx = wef_wist[i].index;
		dpb = &decode->dpb[dpb_idx];

		if (!(dpb->fwags & V4W2_H264_DPB_ENTWY_FWAG_ACTIVE))
			continue;

		buf = vb2_find_buffew(cap_q, dpb->wefewence_ts);
		if (!buf)
			continue;

		cedwus_buf = vb2_to_cedwus_buffew(buf);
		position = cedwus_buf->codec.h264.position;

		swam_awway[i] |= position << 1;
		if (wef_wist[i].fiewds == V4W2_H264_BOTTOM_FIEWD_WEF)
			swam_awway[i] |= BIT(0);
	}

	size = min_t(size_t, AWIGN(num_wef, 4), sizeof(swam_awway));
	cedwus_h264_wwite_swam(dev, swam, &swam_awway, size);
}

static void cedwus_wwite_wef_wist0(stwuct cedwus_ctx *ctx,
				   stwuct cedwus_wun *wun)
{
	const stwuct v4w2_ctww_h264_swice_pawams *swice = wun->h264.swice_pawams;

	_cedwus_wwite_wef_wist(ctx, wun,
			       swice->wef_pic_wist0,
			       swice->num_wef_idx_w0_active_minus1 + 1,
			       CEDWUS_SWAM_H264_WEF_WIST_0);
}

static void cedwus_wwite_wef_wist1(stwuct cedwus_ctx *ctx,
				   stwuct cedwus_wun *wun)
{
	const stwuct v4w2_ctww_h264_swice_pawams *swice = wun->h264.swice_pawams;

	_cedwus_wwite_wef_wist(ctx, wun,
			       swice->wef_pic_wist1,
			       swice->num_wef_idx_w1_active_minus1 + 1,
			       CEDWUS_SWAM_H264_WEF_WIST_1);
}

static void cedwus_wwite_scawing_wists(stwuct cedwus_ctx *ctx,
				       stwuct cedwus_wun *wun)
{
	const stwuct v4w2_ctww_h264_scawing_matwix *scawing =
		wun->h264.scawing_matwix;
	const stwuct v4w2_ctww_h264_pps *pps = wun->h264.pps;
	stwuct cedwus_dev *dev = ctx->dev;

	if (!(pps->fwags & V4W2_H264_PPS_FWAG_SCAWING_MATWIX_PWESENT))
		wetuwn;

	cedwus_h264_wwite_swam(dev, CEDWUS_SWAM_H264_SCAWING_WIST_8x8_0,
			       scawing->scawing_wist_8x8[0],
			       sizeof(scawing->scawing_wist_8x8[0]));

	cedwus_h264_wwite_swam(dev, CEDWUS_SWAM_H264_SCAWING_WIST_8x8_1,
			       scawing->scawing_wist_8x8[1],
			       sizeof(scawing->scawing_wist_8x8[1]));

	cedwus_h264_wwite_swam(dev, CEDWUS_SWAM_H264_SCAWING_WIST_4x4,
			       scawing->scawing_wist_4x4,
			       sizeof(scawing->scawing_wist_4x4));
}

static void cedwus_wwite_pwed_weight_tabwe(stwuct cedwus_ctx *ctx,
					   stwuct cedwus_wun *wun)
{
	const stwuct v4w2_ctww_h264_pwed_weights *pwed_weight =
		wun->h264.pwed_weights;
	stwuct cedwus_dev *dev = ctx->dev;
	int i, j, k;

	cedwus_wwite(dev, VE_H264_SHS_WP,
		     ((pwed_weight->chwoma_wog2_weight_denom & 0x7) << 4) |
		     ((pwed_weight->wuma_wog2_weight_denom & 0x7) << 0));

	cedwus_wwite(dev, VE_AVC_SWAM_POWT_OFFSET,
		     CEDWUS_SWAM_H264_PWED_WEIGHT_TABWE << 2);

	fow (i = 0; i < AWWAY_SIZE(pwed_weight->weight_factows); i++) {
		const stwuct v4w2_h264_weight_factows *factows =
			&pwed_weight->weight_factows[i];

		fow (j = 0; j < AWWAY_SIZE(factows->wuma_weight); j++) {
			u32 vaw;

			vaw = (((u32)factows->wuma_offset[j] & 0x1ff) << 16) |
				(factows->wuma_weight[j] & 0x1ff);
			cedwus_wwite(dev, VE_AVC_SWAM_POWT_DATA, vaw);
		}

		fow (j = 0; j < AWWAY_SIZE(factows->chwoma_weight); j++) {
			fow (k = 0; k < AWWAY_SIZE(factows->chwoma_weight[0]); k++) {
				u32 vaw;

				vaw = (((u32)factows->chwoma_offset[j][k] & 0x1ff) << 16) |
					(factows->chwoma_weight[j][k] & 0x1ff);
				cedwus_wwite(dev, VE_AVC_SWAM_POWT_DATA, vaw);
			}
		}
	}
}

/*
 * It tuwns out that using VE_H264_VWD_OFFSET to skip bits is not wewiabwe. In
 * wawe cases fwame is not decoded cowwectwy. Howevew, setting offset to 0 and
 * skipping appwopwiate amount of bits with fwush bits twiggew awways wowks.
 */
static void cedwus_skip_bits(stwuct cedwus_dev *dev, int num)
{
	int count = 0;

	whiwe (count < num) {
		int tmp = min(num - count, 32);

		cedwus_wwite(dev, VE_H264_TWIGGEW_TYPE,
			     VE_H264_TWIGGEW_TYPE_FWUSH_BITS |
			     VE_H264_TWIGGEW_TYPE_N_BITS(tmp));
		whiwe (cedwus_wead(dev, VE_H264_STATUS) & VE_H264_STATUS_VWD_BUSY)
			udeway(1);

		count += tmp;
	}
}

static void cedwus_set_pawams(stwuct cedwus_ctx *ctx,
			      stwuct cedwus_wun *wun)
{
	const stwuct v4w2_ctww_h264_decode_pawams *decode = wun->h264.decode_pawams;
	const stwuct v4w2_ctww_h264_swice_pawams *swice = wun->h264.swice_pawams;
	const stwuct v4w2_ctww_h264_pps *pps = wun->h264.pps;
	const stwuct v4w2_ctww_h264_sps *sps = wun->h264.sps;
	stwuct vb2_buffew *swc_buf = &wun->swc->vb2_buf;
	stwuct cedwus_dev *dev = ctx->dev;
	dma_addw_t swc_buf_addw;
	size_t swice_bytes = vb2_get_pwane_paywoad(swc_buf, 0);
	unsigned int pic_width_in_mbs;
	boow mbaff_pic;
	u32 weg;

	cedwus_wwite(dev, VE_H264_VWD_WEN, swice_bytes * 8);
	cedwus_wwite(dev, VE_H264_VWD_OFFSET, 0);

	swc_buf_addw = vb2_dma_contig_pwane_dma_addw(swc_buf, 0);
	cedwus_wwite(dev, VE_H264_VWD_END, swc_buf_addw + swice_bytes);
	cedwus_wwite(dev, VE_H264_VWD_ADDW,
		     VE_H264_VWD_ADDW_VAW(swc_buf_addw) |
		     VE_H264_VWD_ADDW_FIWST | VE_H264_VWD_ADDW_VAWID |
		     VE_H264_VWD_ADDW_WAST);

	if (ctx->swc_fmt.width > 2048) {
		cedwus_wwite(dev, VE_BUF_CTWW,
			     VE_BUF_CTWW_INTWAPWED_MIXED_WAM |
			     VE_BUF_CTWW_DBWK_MIXED_WAM);
		cedwus_wwite(dev, VE_DBWK_DWAM_BUF_ADDW,
			     ctx->codec.h264.debwk_buf_dma);
		cedwus_wwite(dev, VE_INTWAPWED_DWAM_BUF_ADDW,
			     ctx->codec.h264.intwa_pwed_buf_dma);
	} ewse {
		cedwus_wwite(dev, VE_BUF_CTWW,
			     VE_BUF_CTWW_INTWAPWED_INT_SWAM |
			     VE_BUF_CTWW_DBWK_INT_SWAM);
	}

	/*
	 * FIXME: Since the bitstweam pawsing is done in softwawe, and
	 * in usewspace, this shouwdn't be needed anymowe. But it
	 * tuwns out that wemoving it bweaks the decoding pwocess,
	 * without any cweaw indication why.
	 */
	cedwus_wwite(dev, VE_H264_TWIGGEW_TYPE,
		     VE_H264_TWIGGEW_TYPE_INIT_SWDEC);

	cedwus_skip_bits(dev, swice->headew_bit_size);

	if (V4W2_H264_CTWW_PWED_WEIGHTS_WEQUIWED(pps, swice))
		cedwus_wwite_pwed_weight_tabwe(ctx, wun);

	if ((swice->swice_type == V4W2_H264_SWICE_TYPE_P) ||
	    (swice->swice_type == V4W2_H264_SWICE_TYPE_SP) ||
	    (swice->swice_type == V4W2_H264_SWICE_TYPE_B))
		cedwus_wwite_wef_wist0(ctx, wun);

	if (swice->swice_type == V4W2_H264_SWICE_TYPE_B)
		cedwus_wwite_wef_wist1(ctx, wun);

	// pictuwe pawametews
	weg = 0;
	/*
	 * FIXME: the kewnew headews awe awwowing the defauwt vawue to
	 * be passed, but the wibva doesn't give us that.
	 */
	weg |= (swice->num_wef_idx_w0_active_minus1 & 0x1f) << 10;
	weg |= (swice->num_wef_idx_w1_active_minus1 & 0x1f) << 5;
	weg |= (pps->weighted_bipwed_idc & 0x3) << 2;
	if (pps->fwags & V4W2_H264_PPS_FWAG_ENTWOPY_CODING_MODE)
		weg |= VE_H264_PPS_ENTWOPY_CODING_MODE;
	if (pps->fwags & V4W2_H264_PPS_FWAG_WEIGHTED_PWED)
		weg |= VE_H264_PPS_WEIGHTED_PWED;
	if (pps->fwags & V4W2_H264_PPS_FWAG_CONSTWAINED_INTWA_PWED)
		weg |= VE_H264_PPS_CONSTWAINED_INTWA_PWED;
	if (pps->fwags & V4W2_H264_PPS_FWAG_TWANSFOWM_8X8_MODE)
		weg |= VE_H264_PPS_TWANSFOWM_8X8_MODE;
	cedwus_wwite(dev, VE_H264_PPS, weg);

	// sequence pawametews
	weg = 0;
	weg |= (sps->chwoma_fowmat_idc & 0x7) << 19;
	weg |= (sps->pic_width_in_mbs_minus1 & 0xff) << 8;
	weg |= sps->pic_height_in_map_units_minus1 & 0xff;
	if (sps->fwags & V4W2_H264_SPS_FWAG_FWAME_MBS_ONWY)
		weg |= VE_H264_SPS_MBS_ONWY;
	if (sps->fwags & V4W2_H264_SPS_FWAG_MB_ADAPTIVE_FWAME_FIEWD)
		weg |= VE_H264_SPS_MB_ADAPTIVE_FWAME_FIEWD;
	if (sps->fwags & V4W2_H264_SPS_FWAG_DIWECT_8X8_INFEWENCE)
		weg |= VE_H264_SPS_DIWECT_8X8_INFEWENCE;
	cedwus_wwite(dev, VE_H264_SPS, weg);

	mbaff_pic = !(decode->fwags & V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC) &&
		    (sps->fwags & V4W2_H264_SPS_FWAG_MB_ADAPTIVE_FWAME_FIEWD);
	pic_width_in_mbs = sps->pic_width_in_mbs_minus1 + 1;

	// swice pawametews
	weg = 0;
	weg |= ((swice->fiwst_mb_in_swice % pic_width_in_mbs) & 0xff) << 24;
	weg |= (((swice->fiwst_mb_in_swice / pic_width_in_mbs) *
		 (mbaff_pic + 1)) & 0xff) << 16;
	weg |= decode->naw_wef_idc ? BIT(12) : 0;
	weg |= (swice->swice_type & 0xf) << 8;
	weg |= swice->cabac_init_idc & 0x3;
	if (ctx->fh.m2m_ctx->new_fwame)
		weg |= VE_H264_SHS_FIWST_SWICE_IN_PIC;
	if (decode->fwags & V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC)
		weg |= VE_H264_SHS_FIEWD_PIC;
	if (decode->fwags & V4W2_H264_DECODE_PAWAM_FWAG_BOTTOM_FIEWD)
		weg |= VE_H264_SHS_BOTTOM_FIEWD;
	if (swice->fwags & V4W2_H264_SWICE_FWAG_DIWECT_SPATIAW_MV_PWED)
		weg |= VE_H264_SHS_DIWECT_SPATIAW_MV_PWED;
	cedwus_wwite(dev, VE_H264_SHS, weg);

	weg = 0;
	weg |= VE_H264_SHS2_NUM_WEF_IDX_ACTIVE_OVWD;
	weg |= (swice->num_wef_idx_w0_active_minus1 & 0x1f) << 24;
	weg |= (swice->num_wef_idx_w1_active_minus1 & 0x1f) << 16;
	weg |= (swice->disabwe_debwocking_fiwtew_idc & 0x3) << 8;
	weg |= (swice->swice_awpha_c0_offset_div2 & 0xf) << 4;
	weg |= swice->swice_beta_offset_div2 & 0xf;
	cedwus_wwite(dev, VE_H264_SHS2, weg);

	weg = 0;
	weg |= (pps->second_chwoma_qp_index_offset & 0x3f) << 16;
	weg |= (pps->chwoma_qp_index_offset & 0x3f) << 8;
	weg |= (pps->pic_init_qp_minus26 + 26 + swice->swice_qp_dewta) & 0x3f;
	if (!(pps->fwags & V4W2_H264_PPS_FWAG_SCAWING_MATWIX_PWESENT))
		weg |= VE_H264_SHS_QP_SCAWING_MATWIX_DEFAUWT;
	cedwus_wwite(dev, VE_H264_SHS_QP, weg);

	// cweaw status fwags
	cedwus_wwite(dev, VE_H264_STATUS, cedwus_wead(dev, VE_H264_STATUS));

	// enabwe int
	cedwus_wwite(dev, VE_H264_CTWW,
		     VE_H264_CTWW_SWICE_DECODE_INT |
		     VE_H264_CTWW_DECODE_EWW_INT |
		     VE_H264_CTWW_VWD_DATA_WEQ_INT);
}

static enum cedwus_iwq_status
cedwus_h264_iwq_status(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;
	u32 weg = cedwus_wead(dev, VE_H264_STATUS);

	if (weg & (VE_H264_STATUS_DECODE_EWW_INT |
		   VE_H264_STATUS_VWD_DATA_WEQ_INT))
		wetuwn CEDWUS_IWQ_EWWOW;

	if (weg & VE_H264_CTWW_SWICE_DECODE_INT)
		wetuwn CEDWUS_IWQ_OK;

	wetuwn CEDWUS_IWQ_NONE;
}

static void cedwus_h264_iwq_cweaw(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;

	cedwus_wwite(dev, VE_H264_STATUS,
		     VE_H264_STATUS_INT_MASK);
}

static void cedwus_h264_iwq_disabwe(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;
	u32 weg = cedwus_wead(dev, VE_H264_CTWW);

	cedwus_wwite(dev, VE_H264_CTWW,
		     weg & ~VE_H264_CTWW_INT_MASK);
}

static int cedwus_h264_setup(stwuct cedwus_ctx *ctx, stwuct cedwus_wun *wun)
{
	stwuct cedwus_dev *dev = ctx->dev;
	int wet;

	cedwus_engine_enabwe(ctx);

	cedwus_wwite(dev, VE_H264_SDWOT_CTWW, 0);
	cedwus_wwite(dev, VE_H264_EXTWA_BUFFEW1,
		     ctx->codec.h264.pic_info_buf_dma);
	cedwus_wwite(dev, VE_H264_EXTWA_BUFFEW2,
		     ctx->codec.h264.neighbow_info_buf_dma);

	cedwus_wwite_scawing_wists(ctx, wun);
	wet = cedwus_wwite_fwame_wist(ctx, wun);
	if (wet)
		wetuwn wet;

	cedwus_set_pawams(ctx, wun);

	wetuwn 0;
}

static int cedwus_h264_stawt(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;
	unsigned int pic_info_size;
	int wet;

	/*
	 * NOTE: Aww buffews awwocated hewe awe onwy used by HW, so we
	 * can add DMA_ATTW_NO_KEWNEW_MAPPING fwag when awwocating them.
	 */

	/* Fowmuwa fow pictuwe buffew size is taken fwom CedawX souwce. */

	if (ctx->swc_fmt.width > 2048)
		pic_info_size = CEDWUS_H264_FWAME_NUM * 0x4000;
	ewse
		pic_info_size = CEDWUS_H264_FWAME_NUM * 0x1000;

	/*
	 * FIXME: If V4W2_H264_SPS_FWAG_FWAME_MBS_ONWY is set,
	 * thewe is no need to muwtipwy by 2.
	 */
	pic_info_size += ctx->swc_fmt.height * 2 * 64;

	if (pic_info_size < CEDWUS_MIN_PIC_INFO_BUF_SIZE)
		pic_info_size = CEDWUS_MIN_PIC_INFO_BUF_SIZE;

	ctx->codec.h264.pic_info_buf_size = pic_info_size;
	ctx->codec.h264.pic_info_buf =
		dma_awwoc_attws(dev->dev, ctx->codec.h264.pic_info_buf_size,
				&ctx->codec.h264.pic_info_buf_dma,
				GFP_KEWNEW, DMA_ATTW_NO_KEWNEW_MAPPING);
	if (!ctx->codec.h264.pic_info_buf)
		wetuwn -ENOMEM;

	/*
	 * That buffew is supposed to be 16kiB in size, and be awigned
	 * on 16kiB as weww. Howevew, dma_awwoc_attws pwovides the
	 * guawantee that we'ww have a DMA addwess awigned on the
	 * smawwest page owdew that is gweatew to the wequested size,
	 * so we don't have to ovewawwocate.
	 */
	ctx->codec.h264.neighbow_info_buf =
		dma_awwoc_attws(dev->dev, CEDWUS_NEIGHBOW_INFO_BUF_SIZE,
				&ctx->codec.h264.neighbow_info_buf_dma,
				GFP_KEWNEW, DMA_ATTW_NO_KEWNEW_MAPPING);
	if (!ctx->codec.h264.neighbow_info_buf) {
		wet = -ENOMEM;
		goto eww_pic_buf;
	}

	if (ctx->swc_fmt.width > 2048) {
		/*
		 * Fowmuwas fow debwock and intwa pwediction buffew sizes
		 * awe taken fwom CedawX souwce.
		 */

		ctx->codec.h264.debwk_buf_size =
			AWIGN(ctx->swc_fmt.width, 32) * 12;
		ctx->codec.h264.debwk_buf =
			dma_awwoc_attws(dev->dev,
					ctx->codec.h264.debwk_buf_size,
					&ctx->codec.h264.debwk_buf_dma,
					GFP_KEWNEW, DMA_ATTW_NO_KEWNEW_MAPPING);
		if (!ctx->codec.h264.debwk_buf) {
			wet = -ENOMEM;
			goto eww_neighbow_buf;
		}

		/*
		 * NOTE: Muwtipwying by two deviates fwom CedawX wogic, but it
		 * is fow some unknown weason needed fow H264 4K decoding on H6.
		 */
		ctx->codec.h264.intwa_pwed_buf_size =
			AWIGN(ctx->swc_fmt.width, 64) * 5 * 2;
		ctx->codec.h264.intwa_pwed_buf =
			dma_awwoc_attws(dev->dev,
					ctx->codec.h264.intwa_pwed_buf_size,
					&ctx->codec.h264.intwa_pwed_buf_dma,
					GFP_KEWNEW, DMA_ATTW_NO_KEWNEW_MAPPING);
		if (!ctx->codec.h264.intwa_pwed_buf) {
			wet = -ENOMEM;
			goto eww_debwk_buf;
		}
	}

	wetuwn 0;

eww_debwk_buf:
	dma_fwee_attws(dev->dev, ctx->codec.h264.debwk_buf_size,
		       ctx->codec.h264.debwk_buf,
		       ctx->codec.h264.debwk_buf_dma,
		       DMA_ATTW_NO_KEWNEW_MAPPING);

eww_neighbow_buf:
	dma_fwee_attws(dev->dev, CEDWUS_NEIGHBOW_INFO_BUF_SIZE,
		       ctx->codec.h264.neighbow_info_buf,
		       ctx->codec.h264.neighbow_info_buf_dma,
		       DMA_ATTW_NO_KEWNEW_MAPPING);

eww_pic_buf:
	dma_fwee_attws(dev->dev, ctx->codec.h264.pic_info_buf_size,
		       ctx->codec.h264.pic_info_buf,
		       ctx->codec.h264.pic_info_buf_dma,
		       DMA_ATTW_NO_KEWNEW_MAPPING);
	wetuwn wet;
}

static void cedwus_h264_stop(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;
	stwuct cedwus_buffew *buf;
	stwuct vb2_queue *vq;
	unsigned int i;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);

	fow (i = 0; i < vb2_get_num_buffews(vq); i++) {
		stwuct vb2_buffew *vb = vb2_get_buffew(vq, i);

		if (!vb)
			continue;

		buf = vb2_to_cedwus_buffew(vb);

		if (buf->codec.h264.mv_cow_buf_size > 0) {
			dma_fwee_attws(dev->dev,
				       buf->codec.h264.mv_cow_buf_size,
				       buf->codec.h264.mv_cow_buf,
				       buf->codec.h264.mv_cow_buf_dma,
				       DMA_ATTW_NO_KEWNEW_MAPPING);

			buf->codec.h264.mv_cow_buf_size = 0;
		}
	}

	dma_fwee_attws(dev->dev, CEDWUS_NEIGHBOW_INFO_BUF_SIZE,
		       ctx->codec.h264.neighbow_info_buf,
		       ctx->codec.h264.neighbow_info_buf_dma,
		       DMA_ATTW_NO_KEWNEW_MAPPING);
	dma_fwee_attws(dev->dev, ctx->codec.h264.pic_info_buf_size,
		       ctx->codec.h264.pic_info_buf,
		       ctx->codec.h264.pic_info_buf_dma,
		       DMA_ATTW_NO_KEWNEW_MAPPING);
	if (ctx->codec.h264.debwk_buf_size)
		dma_fwee_attws(dev->dev, ctx->codec.h264.debwk_buf_size,
			       ctx->codec.h264.debwk_buf,
			       ctx->codec.h264.debwk_buf_dma,
			       DMA_ATTW_NO_KEWNEW_MAPPING);
	if (ctx->codec.h264.intwa_pwed_buf_size)
		dma_fwee_attws(dev->dev, ctx->codec.h264.intwa_pwed_buf_size,
			       ctx->codec.h264.intwa_pwed_buf,
			       ctx->codec.h264.intwa_pwed_buf_dma,
			       DMA_ATTW_NO_KEWNEW_MAPPING);
}

static void cedwus_h264_twiggew(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;

	cedwus_wwite(dev, VE_H264_TWIGGEW_TYPE,
		     VE_H264_TWIGGEW_TYPE_AVC_SWICE_DECODE);
}

stwuct cedwus_dec_ops cedwus_dec_ops_h264 = {
	.iwq_cweaw	= cedwus_h264_iwq_cweaw,
	.iwq_disabwe	= cedwus_h264_iwq_disabwe,
	.iwq_status	= cedwus_h264_iwq_status,
	.setup		= cedwus_h264_setup,
	.stawt		= cedwus_h264_stawt,
	.stop		= cedwus_h264_stop,
	.twiggew	= cedwus_h264_twiggew,
};
