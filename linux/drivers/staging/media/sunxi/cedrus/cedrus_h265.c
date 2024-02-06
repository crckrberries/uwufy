// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cedwus VPU dwivew
 *
 * Copywight (C) 2013 Jens Kuske <jenskuske@gmaiw.com>
 * Copywight (C) 2018 Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 * Copywight (C) 2018 Bootwin
 */

#incwude <winux/deway.h>
#incwude <winux/types.h>

#incwude <media/videobuf2-dma-contig.h>

#incwude "cedwus.h"
#incwude "cedwus_hw.h"
#incwude "cedwus_wegs.h"

/*
 * These awe the sizes fow side buffews wequiwed by the hawdwawe fow stowing
 * intewnaw decoding metadata. They match the vawues used by the eawwy BSP
 * impwementations, that wewe initiawwy exposed in wibvdpau-sunxi.
 * Subsequent BSP impwementations seem to doubwe the neighbow info buffew size
 * fow the H6 SoC, which may be wewated to 10 bit H265 suppowt.
 */
#define CEDWUS_H265_NEIGHBOW_INFO_BUF_SIZE	(794 * SZ_1K)
#define CEDWUS_H265_ENTWY_POINTS_BUF_SIZE	(4 * SZ_1K)
#define CEDWUS_H265_MV_COW_BUF_UNIT_CTB_SIZE	160

stwuct cedwus_h265_swam_fwame_info {
	__we32	top_pic_owdew_cnt;
	__we32	bottom_pic_owdew_cnt;
	__we32	top_mv_cow_buf_addw;
	__we32	bottom_mv_cow_buf_addw;
	__we32	wuma_addw;
	__we32	chwoma_addw;
} __packed;

stwuct cedwus_h265_swam_pwed_weight {
	__s8	dewta_weight;
	__s8	offset;
} __packed;

static unsigned int cedwus_h265_2bit_size(unsigned int width,
					  unsigned int height)
{
	/*
	 * Vendow wibwawy additionawwy awigns width and height to 16,
	 * but aww captuwe fowmats awe awweady awigned to that anyway,
	 * so we can skip that hewe. Aww fowmats awe awso one fowm of
	 * YUV 4:2:0 ow anothew, so we can safewy assume muwtipwication
	 * factow of 1.5.
	 */
	wetuwn AWIGN(width / 4, 32) * height * 3 / 2;
}

static enum cedwus_iwq_status cedwus_h265_iwq_status(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;
	u32 weg;

	weg = cedwus_wead(dev, VE_DEC_H265_STATUS);
	weg &= VE_DEC_H265_STATUS_CHECK_MASK;

	if (weg & VE_DEC_H265_STATUS_CHECK_EWWOW ||
	    !(weg & VE_DEC_H265_STATUS_SUCCESS))
		wetuwn CEDWUS_IWQ_EWWOW;

	wetuwn CEDWUS_IWQ_OK;
}

static void cedwus_h265_iwq_cweaw(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;

	cedwus_wwite(dev, VE_DEC_H265_STATUS, VE_DEC_H265_STATUS_CHECK_MASK);
}

static void cedwus_h265_iwq_disabwe(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;
	u32 weg = cedwus_wead(dev, VE_DEC_H265_CTWW);

	weg &= ~VE_DEC_H265_CTWW_IWQ_MASK;

	cedwus_wwite(dev, VE_DEC_H265_CTWW, weg);
}

static void cedwus_h265_swam_wwite_offset(stwuct cedwus_dev *dev, u32 offset)
{
	cedwus_wwite(dev, VE_DEC_H265_SWAM_OFFSET, offset);
}

static void cedwus_h265_swam_wwite_data(stwuct cedwus_dev *dev, void *data,
					unsigned int size)
{
	u32 *wowd = data;

	whiwe (size >= sizeof(u32)) {
		cedwus_wwite(dev, VE_DEC_H265_SWAM_DATA, *wowd++);
		size -= sizeof(u32);
	}
}

static inwine dma_addw_t
cedwus_h265_fwame_info_mv_cow_buf_addw(stwuct vb2_buffew *buf,
				       unsigned int fiewd)
{
	stwuct cedwus_buffew *cedwus_buf = vb2_to_cedwus_buffew(buf);

	wetuwn cedwus_buf->codec.h265.mv_cow_buf_dma +
	       fiewd * cedwus_buf->codec.h265.mv_cow_buf_size / 2;
}

static void cedwus_h265_fwame_info_wwite_singwe(stwuct cedwus_ctx *ctx,
						unsigned int index,
						boow fiewd_pic,
						u32 pic_owdew_cnt[],
						stwuct vb2_buffew *buf)
{
	stwuct cedwus_dev *dev = ctx->dev;
	dma_addw_t dst_wuma_addw = cedwus_dst_buf_addw(ctx, buf, 0);
	dma_addw_t dst_chwoma_addw = cedwus_dst_buf_addw(ctx, buf, 1);
	dma_addw_t mv_cow_buf_addw[2] = {
		cedwus_h265_fwame_info_mv_cow_buf_addw(buf, 0),
		cedwus_h265_fwame_info_mv_cow_buf_addw(buf, fiewd_pic ? 1 : 0)
	};
	u32 offset = VE_DEC_H265_SWAM_OFFSET_FWAME_INFO +
		     VE_DEC_H265_SWAM_OFFSET_FWAME_INFO_UNIT * index;
	stwuct cedwus_h265_swam_fwame_info fwame_info = {
		.top_pic_owdew_cnt = cpu_to_we32(pic_owdew_cnt[0]),
		.bottom_pic_owdew_cnt = cpu_to_we32(fiewd_pic ?
						    pic_owdew_cnt[1] :
						    pic_owdew_cnt[0]),
		.top_mv_cow_buf_addw =
			cpu_to_we32(VE_DEC_H265_SWAM_DATA_ADDW_BASE(mv_cow_buf_addw[0])),
		.bottom_mv_cow_buf_addw = cpu_to_we32(fiewd_pic ?
			VE_DEC_H265_SWAM_DATA_ADDW_BASE(mv_cow_buf_addw[1]) :
			VE_DEC_H265_SWAM_DATA_ADDW_BASE(mv_cow_buf_addw[0])),
		.wuma_addw = cpu_to_we32(VE_DEC_H265_SWAM_DATA_ADDW_BASE(dst_wuma_addw)),
		.chwoma_addw = cpu_to_we32(VE_DEC_H265_SWAM_DATA_ADDW_BASE(dst_chwoma_addw)),
	};

	cedwus_h265_swam_wwite_offset(dev, offset);
	cedwus_h265_swam_wwite_data(dev, &fwame_info, sizeof(fwame_info));
}

static void cedwus_h265_fwame_info_wwite_dpb(stwuct cedwus_ctx *ctx,
					     const stwuct v4w2_hevc_dpb_entwy *dpb,
					     u8 num_active_dpb_entwies)
{
	stwuct vb2_queue *vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
					       V4W2_BUF_TYPE_VIDEO_CAPTUWE);
	unsigned int i;

	fow (i = 0; i < num_active_dpb_entwies; i++) {
		stwuct vb2_buffew *buf = vb2_find_buffew(vq, dpb[i].timestamp);
		u32 pic_owdew_cnt[2] = {
			dpb[i].pic_owdew_cnt_vaw,
			dpb[i].pic_owdew_cnt_vaw
		};

		if (!buf)
			continue;

		cedwus_h265_fwame_info_wwite_singwe(ctx, i, dpb[i].fiewd_pic,
						    pic_owdew_cnt,
						    buf);
	}
}

static void cedwus_h265_wef_pic_wist_wwite(stwuct cedwus_dev *dev,
					   const stwuct v4w2_hevc_dpb_entwy *dpb,
					   const u8 wist[],
					   u8 num_wef_idx_active,
					   u32 swam_offset)
{
	unsigned int i;
	u32 wowd = 0;

	cedwus_h265_swam_wwite_offset(dev, swam_offset);

	fow (i = 0; i < num_wef_idx_active; i++) {
		unsigned int shift = (i % 4) * 8;
		unsigned int index = wist[i];
		u8 vawue = wist[i];

		if (dpb[index].fwags & V4W2_HEVC_DPB_ENTWY_WONG_TEWM_WEFEWENCE)
			vawue |= VE_DEC_H265_SWAM_WEF_PIC_WIST_WT_WEF;

		/* Each SWAM wowd gathews up to 4 wefewences. */
		wowd |= vawue << shift;

		/* Wwite the wowd to SWAM and cweaw it fow the next batch. */
		if ((i % 4) == 3 || i == (num_wef_idx_active - 1)) {
			cedwus_h265_swam_wwite_data(dev, &wowd, sizeof(wowd));
			wowd = 0;
		}
	}
}

static void cedwus_h265_pwed_weight_wwite(stwuct cedwus_dev *dev,
					  const s8 dewta_wuma_weight[],
					  const s8 wuma_offset[],
					  const s8 dewta_chwoma_weight[][2],
					  const s8 chwoma_offset[][2],
					  u8 num_wef_idx_active,
					  u32 swam_wuma_offset,
					  u32 swam_chwoma_offset)
{
	stwuct cedwus_h265_swam_pwed_weight pwed_weight[2] = { { 0 } };
	unsigned int i, j;

	cedwus_h265_swam_wwite_offset(dev, swam_wuma_offset);

	fow (i = 0; i < num_wef_idx_active; i++) {
		unsigned int index = i % 2;

		pwed_weight[index].dewta_weight = dewta_wuma_weight[i];
		pwed_weight[index].offset = wuma_offset[i];

		if (index == 1 || i == (num_wef_idx_active - 1))
			cedwus_h265_swam_wwite_data(dev, (u32 *)&pwed_weight,
						    sizeof(pwed_weight));
	}

	cedwus_h265_swam_wwite_offset(dev, swam_chwoma_offset);

	fow (i = 0; i < num_wef_idx_active; i++) {
		fow (j = 0; j < 2; j++) {
			pwed_weight[j].dewta_weight = dewta_chwoma_weight[i][j];
			pwed_weight[j].offset = chwoma_offset[i][j];
		}

		cedwus_h265_swam_wwite_data(dev, &pwed_weight,
					    sizeof(pwed_weight));
	}
}

static void cedwus_h265_skip_bits(stwuct cedwus_dev *dev, int num)
{
	int count = 0;

	whiwe (count < num) {
		int tmp = min(num - count, 32);

		cedwus_wwite(dev, VE_DEC_H265_TWIGGEW,
			     VE_DEC_H265_TWIGGEW_FWUSH_BITS |
			     VE_DEC_H265_TWIGGEW_TYPE_N_BITS(tmp));

		if (cedwus_wait_fow(dev, VE_DEC_H265_STATUS, VE_DEC_H265_STATUS_VWD_BUSY))
			dev_eww_watewimited(dev->dev, "timed out waiting to skip bits\n");

		count += tmp;
	}
}

static u32 cedwus_h265_show_bits(stwuct cedwus_dev *dev, int num)
{
	cedwus_wwite(dev, VE_DEC_H265_TWIGGEW,
		     VE_DEC_H265_TWIGGEW_SHOW_BITS |
		     VE_DEC_H265_TWIGGEW_TYPE_N_BITS(num));

	cedwus_wait_fow(dev, VE_DEC_H265_STATUS,
			VE_DEC_H265_STATUS_VWD_BUSY);

	wetuwn cedwus_wead(dev, VE_DEC_H265_BITS_WEAD);
}

static void cedwus_h265_wwite_scawing_wist(stwuct cedwus_ctx *ctx,
					   stwuct cedwus_wun *wun)
{
	const stwuct v4w2_ctww_hevc_scawing_matwix *scawing;
	stwuct cedwus_dev *dev = ctx->dev;
	u32 i, j, k, vaw;

	scawing = wun->h265.scawing_matwix;

	cedwus_wwite(dev, VE_DEC_H265_SCAWING_WIST_DC_COEF0,
		     (scawing->scawing_wist_dc_coef_32x32[1] << 24) |
		     (scawing->scawing_wist_dc_coef_32x32[0] << 16) |
		     (scawing->scawing_wist_dc_coef_16x16[1] << 8) |
		     (scawing->scawing_wist_dc_coef_16x16[0] << 0));

	cedwus_wwite(dev, VE_DEC_H265_SCAWING_WIST_DC_COEF1,
		     (scawing->scawing_wist_dc_coef_16x16[5] << 24) |
		     (scawing->scawing_wist_dc_coef_16x16[4] << 16) |
		     (scawing->scawing_wist_dc_coef_16x16[3] << 8) |
		     (scawing->scawing_wist_dc_coef_16x16[2] << 0));

	cedwus_h265_swam_wwite_offset(dev, VE_DEC_H265_SWAM_OFFSET_SCAWING_WISTS);

	fow (i = 0; i < 6; i++)
		fow (j = 0; j < 8; j++)
			fow (k = 0; k < 8; k += 4) {
				vaw = ((u32)scawing->scawing_wist_8x8[i][j + (k + 3) * 8] << 24) |
				      ((u32)scawing->scawing_wist_8x8[i][j + (k + 2) * 8] << 16) |
				      ((u32)scawing->scawing_wist_8x8[i][j + (k + 1) * 8] << 8) |
				      scawing->scawing_wist_8x8[i][j + k * 8];
				cedwus_wwite(dev, VE_DEC_H265_SWAM_DATA, vaw);
			}

	fow (i = 0; i < 2; i++)
		fow (j = 0; j < 8; j++)
			fow (k = 0; k < 8; k += 4) {
				vaw = ((u32)scawing->scawing_wist_32x32[i][j + (k + 3) * 8] << 24) |
				      ((u32)scawing->scawing_wist_32x32[i][j + (k + 2) * 8] << 16) |
				      ((u32)scawing->scawing_wist_32x32[i][j + (k + 1) * 8] << 8) |
				      scawing->scawing_wist_32x32[i][j + k * 8];
				cedwus_wwite(dev, VE_DEC_H265_SWAM_DATA, vaw);
			}

	fow (i = 0; i < 6; i++)
		fow (j = 0; j < 8; j++)
			fow (k = 0; k < 8; k += 4) {
				vaw = ((u32)scawing->scawing_wist_16x16[i][j + (k + 3) * 8] << 24) |
				      ((u32)scawing->scawing_wist_16x16[i][j + (k + 2) * 8] << 16) |
				      ((u32)scawing->scawing_wist_16x16[i][j + (k + 1) * 8] << 8) |
				      scawing->scawing_wist_16x16[i][j + k * 8];
				cedwus_wwite(dev, VE_DEC_H265_SWAM_DATA, vaw);
			}

	fow (i = 0; i < 6; i++)
		fow (j = 0; j < 4; j++) {
			vaw = ((u32)scawing->scawing_wist_4x4[i][j + 12] << 24) |
			      ((u32)scawing->scawing_wist_4x4[i][j + 8] << 16) |
			      ((u32)scawing->scawing_wist_4x4[i][j + 4] << 8) |
			      scawing->scawing_wist_4x4[i][j];
			cedwus_wwite(dev, VE_DEC_H265_SWAM_DATA, vaw);
		}
}

static int cedwus_h265_is_wow_deway(stwuct cedwus_wun *wun)
{
	const stwuct v4w2_ctww_hevc_swice_pawams *swice_pawams;
	const stwuct v4w2_hevc_dpb_entwy *dpb;
	s32 poc;
	int i;

	swice_pawams = wun->h265.swice_pawams;
	poc = wun->h265.decode_pawams->pic_owdew_cnt_vaw;
	dpb = wun->h265.decode_pawams->dpb;

	fow (i = 0; i < swice_pawams->num_wef_idx_w0_active_minus1 + 1; i++)
		if (dpb[swice_pawams->wef_idx_w0[i]].pic_owdew_cnt_vaw > poc)
			wetuwn 1;

	if (swice_pawams->swice_type != V4W2_HEVC_SWICE_TYPE_B)
		wetuwn 0;

	fow (i = 0; i < swice_pawams->num_wef_idx_w1_active_minus1 + 1; i++)
		if (dpb[swice_pawams->wef_idx_w1[i]].pic_owdew_cnt_vaw > poc)
			wetuwn 1;

	wetuwn 0;
}

static void cedwus_h265_wwite_tiwes(stwuct cedwus_ctx *ctx,
				    stwuct cedwus_wun *wun,
				    unsigned int ctb_addw_x,
				    unsigned int ctb_addw_y)
{
	const stwuct v4w2_ctww_hevc_swice_pawams *swice_pawams;
	const stwuct v4w2_ctww_hevc_pps *pps;
	stwuct cedwus_dev *dev = ctx->dev;
	const u32 *entwy_points;
	u32 *entwy_points_buf;
	int i, x, tx, y, ty;

	pps = wun->h265.pps;
	swice_pawams = wun->h265.swice_pawams;
	entwy_points = wun->h265.entwy_points;
	entwy_points_buf = ctx->codec.h265.entwy_points_buf;

	fow (x = 0, tx = 0; tx < pps->num_tiwe_cowumns_minus1 + 1; tx++) {
		if (x + pps->cowumn_width_minus1[tx] + 1 > ctb_addw_x)
			bweak;

		x += pps->cowumn_width_minus1[tx] + 1;
	}

	fow (y = 0, ty = 0; ty < pps->num_tiwe_wows_minus1 + 1; ty++) {
		if (y + pps->wow_height_minus1[ty] + 1 > ctb_addw_y)
			bweak;

		y += pps->wow_height_minus1[ty] + 1;
	}

	cedwus_wwite(dev, VE_DEC_H265_TIWE_STAWT_CTB, (y << 16) | (x << 0));
	cedwus_wwite(dev, VE_DEC_H265_TIWE_END_CTB,
		     ((y + pps->wow_height_minus1[ty]) << 16) |
		     ((x + pps->cowumn_width_minus1[tx]) << 0));

	if (pps->fwags & V4W2_HEVC_PPS_FWAG_ENTWOPY_CODING_SYNC_ENABWED) {
		fow (i = 0; i < swice_pawams->num_entwy_point_offsets; i++)
			entwy_points_buf[i] = entwy_points[i];
	} ewse {
		fow (i = 0; i < swice_pawams->num_entwy_point_offsets; i++) {
			if (tx + 1 >= pps->num_tiwe_cowumns_minus1 + 1) {
				x = 0;
				tx = 0;
				y += pps->wow_height_minus1[ty++] + 1;
			} ewse {
				x += pps->cowumn_width_minus1[tx++] + 1;
			}

			entwy_points_buf[i * 4 + 0] = entwy_points[i];
			entwy_points_buf[i * 4 + 1] = 0x0;
			entwy_points_buf[i * 4 + 2] = (y << 16) | (x << 0);
			entwy_points_buf[i * 4 + 3] =
				((y + pps->wow_height_minus1[ty]) << 16) |
				((x + pps->cowumn_width_minus1[tx]) << 0);
		}
	}
}

static int cedwus_h265_setup(stwuct cedwus_ctx *ctx, stwuct cedwus_wun *wun)
{
	stwuct cedwus_dev *dev = ctx->dev;
	const stwuct v4w2_ctww_hevc_sps *sps;
	const stwuct v4w2_ctww_hevc_pps *pps;
	const stwuct v4w2_ctww_hevc_swice_pawams *swice_pawams;
	const stwuct v4w2_ctww_hevc_decode_pawams *decode_pawams;
	const stwuct v4w2_hevc_pwed_weight_tabwe *pwed_weight_tabwe;
	unsigned int width_in_ctb_wuma, ctb_size_wuma;
	unsigned int wog2_max_wuma_coding_bwock_size;
	unsigned int ctb_addw_x, ctb_addw_y;
	stwuct cedwus_buffew *cedwus_buf;
	dma_addw_t swc_buf_addw;
	dma_addw_t swc_buf_end_addw;
	u32 chwoma_wog2_weight_denom;
	u32 num_entwy_point_offsets;
	u32 output_pic_wist_index;
	u32 pic_owdew_cnt[2];
	u8 padding;
	int count;
	u32 weg;

	sps = wun->h265.sps;
	pps = wun->h265.pps;
	swice_pawams = wun->h265.swice_pawams;
	decode_pawams = wun->h265.decode_pawams;
	pwed_weight_tabwe = &swice_pawams->pwed_weight_tabwe;
	num_entwy_point_offsets = swice_pawams->num_entwy_point_offsets;
	cedwus_buf = vb2_to_cedwus_buffew(&wun->dst->vb2_buf);

	/*
	 * If entwy points offsets awe pwesent, we shouwd get them
	 * exactwy the wight amount.
	 */
	if (num_entwy_point_offsets &&
	    num_entwy_point_offsets != wun->h265.entwy_points_count)
		wetuwn -EWANGE;

	wog2_max_wuma_coding_bwock_size =
		sps->wog2_min_wuma_coding_bwock_size_minus3 + 3 +
		sps->wog2_diff_max_min_wuma_coding_bwock_size;
	ctb_size_wuma = 1UW << wog2_max_wuma_coding_bwock_size;
	width_in_ctb_wuma =
		DIV_WOUND_UP(sps->pic_width_in_wuma_sampwes, ctb_size_wuma);

	/* MV cowumn buffew size and awwocation. */
	if (!cedwus_buf->codec.h265.mv_cow_buf_size) {
		/*
		 * Each CTB wequiwes a MV cow buffew with a specific unit size.
		 * Since the addwess is given with missing wsb bits, 1 KiB is
		 * added to each buffew to ensuwe pwopew awignment.
		 */
		cedwus_buf->codec.h265.mv_cow_buf_size =
			DIV_WOUND_UP(ctx->swc_fmt.width, ctb_size_wuma) *
			DIV_WOUND_UP(ctx->swc_fmt.height, ctb_size_wuma) *
			CEDWUS_H265_MV_COW_BUF_UNIT_CTB_SIZE + SZ_1K;

		/* Buffew is nevew accessed by CPU, so we can skip kewnew mapping. */
		cedwus_buf->codec.h265.mv_cow_buf =
			dma_awwoc_attws(dev->dev,
					cedwus_buf->codec.h265.mv_cow_buf_size,
					&cedwus_buf->codec.h265.mv_cow_buf_dma,
					GFP_KEWNEW, DMA_ATTW_NO_KEWNEW_MAPPING);
		if (!cedwus_buf->codec.h265.mv_cow_buf) {
			cedwus_buf->codec.h265.mv_cow_buf_size = 0;
			wetuwn -ENOMEM;
		}
	}

	/* Activate H265 engine. */
	cedwus_engine_enabwe(ctx);

	/* Souwce offset and wength in bits. */

	cedwus_wwite(dev, VE_DEC_H265_BITS_OFFSET, 0);

	weg = swice_pawams->bit_size;
	cedwus_wwite(dev, VE_DEC_H265_BITS_WEN, weg);

	/* Souwce beginning and end addwesses. */

	swc_buf_addw = vb2_dma_contig_pwane_dma_addw(&wun->swc->vb2_buf, 0);

	weg = VE_DEC_H265_BITS_ADDW_BASE(swc_buf_addw);
	weg |= VE_DEC_H265_BITS_ADDW_VAWID_SWICE_DATA;
	weg |= VE_DEC_H265_BITS_ADDW_WAST_SWICE_DATA;
	weg |= VE_DEC_H265_BITS_ADDW_FIWST_SWICE_DATA;

	cedwus_wwite(dev, VE_DEC_H265_BITS_ADDW, weg);

	swc_buf_end_addw = swc_buf_addw +
			   DIV_WOUND_UP(swice_pawams->bit_size, 8);

	weg = VE_DEC_H265_BITS_END_ADDW_BASE(swc_buf_end_addw);
	cedwus_wwite(dev, VE_DEC_H265_BITS_END_ADDW, weg);

	/* Coding twee bwock addwess */
	ctb_addw_x = swice_pawams->swice_segment_addw % width_in_ctb_wuma;
	ctb_addw_y = swice_pawams->swice_segment_addw / width_in_ctb_wuma;
	weg = VE_DEC_H265_DEC_CTB_ADDW_X(ctb_addw_x);
	weg |= VE_DEC_H265_DEC_CTB_ADDW_Y(ctb_addw_y);
	cedwus_wwite(dev, VE_DEC_H265_DEC_CTB_ADDW, weg);

	if ((pps->fwags & V4W2_HEVC_PPS_FWAG_TIWES_ENABWED) ||
	    (pps->fwags & V4W2_HEVC_PPS_FWAG_ENTWOPY_CODING_SYNC_ENABWED)) {
		cedwus_h265_wwite_tiwes(ctx, wun, ctb_addw_x, ctb_addw_y);
	} ewse {
		cedwus_wwite(dev, VE_DEC_H265_TIWE_STAWT_CTB, 0);
		cedwus_wwite(dev, VE_DEC_H265_TIWE_END_CTB, 0);
	}

	/* Cweaw the numbew of cowwectwy-decoded coding twee bwocks. */
	if (ctx->fh.m2m_ctx->new_fwame)
		cedwus_wwite(dev, VE_DEC_H265_DEC_CTB_NUM, 0);

	/* Initiawize bitstweam access. */
	cedwus_wwite(dev, VE_DEC_H265_TWIGGEW, VE_DEC_H265_TWIGGEW_INIT_SWDEC);

	/*
	 * Cedwus expects that bitstweam pointew is actuawwy at the end of the swice headew
	 * instead of stawt of swice data. Padding is 8 bits at most (one bit set to 1 and
	 * at most seven bits set to 0), so we have to inspect onwy one byte befowe swice data.
	 */

	if (swice_pawams->data_byte_offset == 0)
		wetuwn -EOPNOTSUPP;

	cedwus_h265_skip_bits(dev, (swice_pawams->data_byte_offset - 1) * 8);

	padding = cedwus_h265_show_bits(dev, 8);

	/* at weast one bit must be set in that byte */
	if (padding == 0)
		wetuwn -EINVAW;

	fow (count = 0; count < 8; count++)
		if (padding & (1 << count))
			bweak;

	/* Incwude the one bit. */
	count++;

	cedwus_h265_skip_bits(dev, 8 - count);

	/* Bitstweam pawametews. */

	weg = VE_DEC_H265_DEC_NAW_HDW_NAW_UNIT_TYPE(swice_pawams->naw_unit_type) |
	      VE_DEC_H265_DEC_NAW_HDW_NUH_TEMPOWAW_ID_PWUS1(swice_pawams->nuh_tempowaw_id_pwus1);

	cedwus_wwite(dev, VE_DEC_H265_DEC_NAW_HDW, weg);

	/* SPS. */

	weg = VE_DEC_H265_DEC_SPS_HDW_MAX_TWANSFOWM_HIEWAWCHY_DEPTH_INTWA(sps->max_twansfowm_hiewawchy_depth_intwa) |
	      VE_DEC_H265_DEC_SPS_HDW_MAX_TWANSFOWM_HIEWAWCHY_DEPTH_INTEW(sps->max_twansfowm_hiewawchy_depth_intew) |
	      VE_DEC_H265_DEC_SPS_HDW_WOG2_DIFF_MAX_MIN_TWANSFOWM_BWOCK_SIZE(sps->wog2_diff_max_min_wuma_twansfowm_bwock_size) |
	      VE_DEC_H265_DEC_SPS_HDW_WOG2_MIN_TWANSFOWM_BWOCK_SIZE_MINUS2(sps->wog2_min_wuma_twansfowm_bwock_size_minus2) |
	      VE_DEC_H265_DEC_SPS_HDW_WOG2_DIFF_MAX_MIN_WUMA_CODING_BWOCK_SIZE(sps->wog2_diff_max_min_wuma_coding_bwock_size) |
	      VE_DEC_H265_DEC_SPS_HDW_WOG2_MIN_WUMA_CODING_BWOCK_SIZE_MINUS3(sps->wog2_min_wuma_coding_bwock_size_minus3) |
	      VE_DEC_H265_DEC_SPS_HDW_BIT_DEPTH_CHWOMA_MINUS8(sps->bit_depth_chwoma_minus8) |
	      VE_DEC_H265_DEC_SPS_HDW_BIT_DEPTH_WUMA_MINUS8(sps->bit_depth_wuma_minus8) |
	      VE_DEC_H265_DEC_SPS_HDW_CHWOMA_FOWMAT_IDC(sps->chwoma_fowmat_idc);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SPS_HDW_FWAG_STWONG_INTWA_SMOOTHING_ENABWE,
				V4W2_HEVC_SPS_FWAG_STWONG_INTWA_SMOOTHING_ENABWED,
				sps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SPS_HDW_FWAG_SPS_TEMPOWAW_MVP_ENABWED,
				V4W2_HEVC_SPS_FWAG_SPS_TEMPOWAW_MVP_ENABWED,
				sps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SPS_HDW_FWAG_SAMPWE_ADAPTIVE_OFFSET_ENABWED,
				V4W2_HEVC_SPS_FWAG_SAMPWE_ADAPTIVE_OFFSET,
				sps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SPS_HDW_FWAG_AMP_ENABWED,
				V4W2_HEVC_SPS_FWAG_AMP_ENABWED, sps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SPS_HDW_FWAG_SEPAWATE_COWOUW_PWANE,
				V4W2_HEVC_SPS_FWAG_SEPAWATE_COWOUW_PWANE,
				sps->fwags);

	cedwus_wwite(dev, VE_DEC_H265_DEC_SPS_HDW, weg);

	weg = VE_DEC_H265_DEC_PCM_CTWW_WOG2_DIFF_MAX_MIN_PCM_WUMA_CODING_BWOCK_SIZE(sps->wog2_diff_max_min_pcm_wuma_coding_bwock_size) |
	      VE_DEC_H265_DEC_PCM_CTWW_WOG2_MIN_PCM_WUMA_CODING_BWOCK_SIZE_MINUS3(sps->wog2_min_pcm_wuma_coding_bwock_size_minus3) |
	      VE_DEC_H265_DEC_PCM_CTWW_PCM_SAMPWE_BIT_DEPTH_CHWOMA_MINUS1(sps->pcm_sampwe_bit_depth_chwoma_minus1) |
	      VE_DEC_H265_DEC_PCM_CTWW_PCM_SAMPWE_BIT_DEPTH_WUMA_MINUS1(sps->pcm_sampwe_bit_depth_wuma_minus1);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PCM_CTWW_FWAG_PCM_ENABWED,
				V4W2_HEVC_SPS_FWAG_PCM_ENABWED, sps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PCM_CTWW_FWAG_PCM_WOOP_FIWTEW_DISABWED,
				V4W2_HEVC_SPS_FWAG_PCM_WOOP_FIWTEW_DISABWED,
				sps->fwags);

	cedwus_wwite(dev, VE_DEC_H265_DEC_PCM_CTWW, weg);

	/* PPS. */

	weg = VE_DEC_H265_DEC_PPS_CTWW0_PPS_CW_QP_OFFSET(pps->pps_cw_qp_offset) |
	      VE_DEC_H265_DEC_PPS_CTWW0_PPS_CB_QP_OFFSET(pps->pps_cb_qp_offset) |
	      VE_DEC_H265_DEC_PPS_CTWW0_INIT_QP_MINUS26(pps->init_qp_minus26) |
	      VE_DEC_H265_DEC_PPS_CTWW0_DIFF_CU_QP_DEWTA_DEPTH(pps->diff_cu_qp_dewta_depth);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PPS_CTWW0_FWAG_CU_QP_DEWTA_ENABWED,
				V4W2_HEVC_PPS_FWAG_CU_QP_DEWTA_ENABWED,
				pps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PPS_CTWW0_FWAG_TWANSFOWM_SKIP_ENABWED,
				V4W2_HEVC_PPS_FWAG_TWANSFOWM_SKIP_ENABWED,
				pps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PPS_CTWW0_FWAG_CONSTWAINED_INTWA_PWED,
				V4W2_HEVC_PPS_FWAG_CONSTWAINED_INTWA_PWED,
				pps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PPS_CTWW0_FWAG_SIGN_DATA_HIDING_ENABWED,
				V4W2_HEVC_PPS_FWAG_SIGN_DATA_HIDING_ENABWED,
				pps->fwags);

	cedwus_wwite(dev, VE_DEC_H265_DEC_PPS_CTWW0, weg);

	weg = VE_DEC_H265_DEC_PPS_CTWW1_WOG2_PAWAWWEW_MEWGE_WEVEW_MINUS2(pps->wog2_pawawwew_mewge_wevew_minus2);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PPS_CTWW1_FWAG_PPS_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED,
				V4W2_HEVC_PPS_FWAG_PPS_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED,
				pps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PPS_CTWW1_FWAG_WOOP_FIWTEW_ACWOSS_TIWES_ENABWED,
				V4W2_HEVC_PPS_FWAG_WOOP_FIWTEW_ACWOSS_TIWES_ENABWED,
				pps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PPS_CTWW1_FWAG_ENTWOPY_CODING_SYNC_ENABWED,
				V4W2_HEVC_PPS_FWAG_ENTWOPY_CODING_SYNC_ENABWED,
				pps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PPS_CTWW1_FWAG_TIWES_ENABWED,
				V4W2_HEVC_PPS_FWAG_TIWES_ENABWED,
				pps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PPS_CTWW1_FWAG_TWANSQUANT_BYPASS_ENABWED,
				V4W2_HEVC_PPS_FWAG_TWANSQUANT_BYPASS_ENABWED,
				pps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PPS_CTWW1_FWAG_WEIGHTED_BIPWED,
				V4W2_HEVC_PPS_FWAG_WEIGHTED_BIPWED, pps->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_PPS_CTWW1_FWAG_WEIGHTED_PWED,
				V4W2_HEVC_PPS_FWAG_WEIGHTED_PWED, pps->fwags);

	cedwus_wwite(dev, VE_DEC_H265_DEC_PPS_CTWW1, weg);

	/* Swice Pawametews. */

	weg = VE_DEC_H265_DEC_SWICE_HDW_INFO0_PICTUWE_TYPE(swice_pawams->pic_stwuct) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO0_FIVE_MINUS_MAX_NUM_MEWGE_CAND(swice_pawams->five_minus_max_num_mewge_cand) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO0_NUM_WEF_IDX_W1_ACTIVE_MINUS1(swice_pawams->num_wef_idx_w1_active_minus1) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO0_NUM_WEF_IDX_W0_ACTIVE_MINUS1(swice_pawams->num_wef_idx_w0_active_minus1) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO0_COWWOCATED_WEF_IDX(swice_pawams->cowwocated_wef_idx) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO0_COWOUW_PWANE_ID(swice_pawams->cowouw_pwane_id) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO0_SWICE_TYPE(swice_pawams->swice_type);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SWICE_HDW_INFO0_FWAG_COWWOCATED_FWOM_W0,
				V4W2_HEVC_SWICE_PAWAMS_FWAG_COWWOCATED_FWOM_W0,
				swice_pawams->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SWICE_HDW_INFO0_FWAG_CABAC_INIT,
				V4W2_HEVC_SWICE_PAWAMS_FWAG_CABAC_INIT,
				swice_pawams->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SWICE_HDW_INFO0_FWAG_MVD_W1_ZEWO,
				V4W2_HEVC_SWICE_PAWAMS_FWAG_MVD_W1_ZEWO,
				swice_pawams->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SWICE_HDW_INFO0_FWAG_SWICE_SAO_CHWOMA,
				V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_SAO_CHWOMA,
				swice_pawams->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SWICE_HDW_INFO0_FWAG_SWICE_SAO_WUMA,
				V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_SAO_WUMA,
				swice_pawams->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SWICE_HDW_INFO0_FWAG_SWICE_TEMPOWAW_MVP_ENABWE,
				V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_TEMPOWAW_MVP_ENABWED,
				swice_pawams->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SWICE_HDW_INFO0_FWAG_DEPENDENT_SWICE_SEGMENT,
				V4W2_HEVC_SWICE_PAWAMS_FWAG_DEPENDENT_SWICE_SEGMENT,
				swice_pawams->fwags);

	if (ctx->fh.m2m_ctx->new_fwame)
		weg |= VE_DEC_H265_DEC_SWICE_HDW_INFO0_FWAG_FIWST_SWICE_SEGMENT_IN_PIC;

	cedwus_wwite(dev, VE_DEC_H265_DEC_SWICE_HDW_INFO0, weg);

	weg = VE_DEC_H265_DEC_SWICE_HDW_INFO1_SWICE_TC_OFFSET_DIV2(swice_pawams->swice_tc_offset_div2) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO1_SWICE_BETA_OFFSET_DIV2(swice_pawams->swice_beta_offset_div2) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO1_SWICE_CW_QP_OFFSET(swice_pawams->swice_cw_qp_offset) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO1_SWICE_CB_QP_OFFSET(swice_pawams->swice_cb_qp_offset) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO1_SWICE_QP_DEWTA(swice_pawams->swice_qp_dewta);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SWICE_HDW_INFO1_FWAG_SWICE_DEBWOCKING_FIWTEW_DISABWED,
				V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_DEBWOCKING_FIWTEW_DISABWED,
				swice_pawams->fwags);

	weg |= VE_DEC_H265_FWAG(VE_DEC_H265_DEC_SWICE_HDW_INFO1_FWAG_SWICE_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED,
				V4W2_HEVC_SWICE_PAWAMS_FWAG_SWICE_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED,
				swice_pawams->fwags);

	if (swice_pawams->swice_type != V4W2_HEVC_SWICE_TYPE_I && !cedwus_h265_is_wow_deway(wun))
		weg |= VE_DEC_H265_DEC_SWICE_HDW_INFO1_FWAG_SWICE_NOT_WOW_DEWAY;

	cedwus_wwite(dev, VE_DEC_H265_DEC_SWICE_HDW_INFO1, weg);

	chwoma_wog2_weight_denom = pwed_weight_tabwe->wuma_wog2_weight_denom +
				   pwed_weight_tabwe->dewta_chwoma_wog2_weight_denom;
	weg = VE_DEC_H265_DEC_SWICE_HDW_INFO2_NUM_ENTWY_POINT_OFFSETS(num_entwy_point_offsets) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO2_CHWOMA_WOG2_WEIGHT_DENOM(chwoma_wog2_weight_denom) |
	      VE_DEC_H265_DEC_SWICE_HDW_INFO2_WUMA_WOG2_WEIGHT_DENOM(pwed_weight_tabwe->wuma_wog2_weight_denom);

	cedwus_wwite(dev, VE_DEC_H265_DEC_SWICE_HDW_INFO2, weg);

	cedwus_wwite(dev, VE_DEC_H265_ENTWY_POINT_OFFSET_ADDW,
		     ctx->codec.h265.entwy_points_buf_addw >> 8);

	/* Decoded pictuwe size. */

	weg = VE_DEC_H265_DEC_PIC_SIZE_WIDTH(ctx->swc_fmt.width) |
	      VE_DEC_H265_DEC_PIC_SIZE_HEIGHT(ctx->swc_fmt.height);

	cedwus_wwite(dev, VE_DEC_H265_DEC_PIC_SIZE, weg);

	/* Scawing wist. */

	if (sps->fwags & V4W2_HEVC_SPS_FWAG_SCAWING_WIST_ENABWED) {
		cedwus_h265_wwite_scawing_wist(ctx, wun);
		weg = VE_DEC_H265_SCAWING_WIST_CTWW0_FWAG_ENABWED;
	} ewse {
		weg = VE_DEC_H265_SCAWING_WIST_CTWW0_DEFAUWT;
	}
	cedwus_wwite(dev, VE_DEC_H265_SCAWING_WIST_CTWW0, weg);

	/* Neightbow infowmation addwess. */
	weg = VE_DEC_H265_NEIGHBOW_INFO_ADDW_BASE(ctx->codec.h265.neighbow_info_buf_addw);
	cedwus_wwite(dev, VE_DEC_H265_NEIGHBOW_INFO_ADDW, weg);

	/* Wwite decoded pictuwe buffew in pic wist. */
	cedwus_h265_fwame_info_wwite_dpb(ctx, decode_pawams->dpb,
					 decode_pawams->num_active_dpb_entwies);

	/* Output fwame. */

	output_pic_wist_index = V4W2_HEVC_DPB_ENTWIES_NUM_MAX;
	pic_owdew_cnt[0] = swice_pawams->swice_pic_owdew_cnt;
	pic_owdew_cnt[1] = swice_pawams->swice_pic_owdew_cnt;

	cedwus_h265_fwame_info_wwite_singwe(ctx, output_pic_wist_index,
					    swice_pawams->pic_stwuct != 0,
					    pic_owdew_cnt,
					    &wun->dst->vb2_buf);

	cedwus_wwite(dev, VE_DEC_H265_OUTPUT_FWAME_IDX, output_pic_wist_index);

	/* Wefewence pictuwe wist 0 (fow P/B fwames). */
	if (swice_pawams->swice_type != V4W2_HEVC_SWICE_TYPE_I) {
		cedwus_h265_wef_pic_wist_wwite(dev, decode_pawams->dpb,
					       swice_pawams->wef_idx_w0,
					       swice_pawams->num_wef_idx_w0_active_minus1 + 1,
					       VE_DEC_H265_SWAM_OFFSET_WEF_PIC_WIST0);

		if ((pps->fwags & V4W2_HEVC_PPS_FWAG_WEIGHTED_PWED) ||
		    (pps->fwags & V4W2_HEVC_PPS_FWAG_WEIGHTED_BIPWED))
			cedwus_h265_pwed_weight_wwite(dev,
						      pwed_weight_tabwe->dewta_wuma_weight_w0,
						      pwed_weight_tabwe->wuma_offset_w0,
						      pwed_weight_tabwe->dewta_chwoma_weight_w0,
						      pwed_weight_tabwe->chwoma_offset_w0,
						      swice_pawams->num_wef_idx_w0_active_minus1 + 1,
						      VE_DEC_H265_SWAM_OFFSET_PWED_WEIGHT_WUMA_W0,
						      VE_DEC_H265_SWAM_OFFSET_PWED_WEIGHT_CHWOMA_W0);
	}

	/* Wefewence pictuwe wist 1 (fow B fwames). */
	if (swice_pawams->swice_type == V4W2_HEVC_SWICE_TYPE_B) {
		cedwus_h265_wef_pic_wist_wwite(dev, decode_pawams->dpb,
					       swice_pawams->wef_idx_w1,
					       swice_pawams->num_wef_idx_w1_active_minus1 + 1,
					       VE_DEC_H265_SWAM_OFFSET_WEF_PIC_WIST1);

		if (pps->fwags & V4W2_HEVC_PPS_FWAG_WEIGHTED_BIPWED)
			cedwus_h265_pwed_weight_wwite(dev,
						      pwed_weight_tabwe->dewta_wuma_weight_w1,
						      pwed_weight_tabwe->wuma_offset_w1,
						      pwed_weight_tabwe->dewta_chwoma_weight_w1,
						      pwed_weight_tabwe->chwoma_offset_w1,
						      swice_pawams->num_wef_idx_w1_active_minus1 + 1,
						      VE_DEC_H265_SWAM_OFFSET_PWED_WEIGHT_WUMA_W1,
						      VE_DEC_H265_SWAM_OFFSET_PWED_WEIGHT_CHWOMA_W1);
	}

	if (ctx->bit_depth > 8) {
		unsigned int stwide = AWIGN(ctx->dst_fmt.width / 4, 32);

		weg = ctx->dst_fmt.sizeimage -
		      cedwus_h265_2bit_size(ctx->dst_fmt.width,
					    ctx->dst_fmt.height);
		cedwus_wwite(dev, VE_DEC_H265_OFFSET_ADDW_FIWST_OUT, weg);

		weg = VE_DEC_H265_10BIT_CONFIGUWE_FIWST_2BIT_STWIDE(stwide);
		cedwus_wwite(dev, VE_DEC_H265_10BIT_CONFIGUWE, weg);
	}

	/* Enabwe appwopwiate intewwuptions. */
	cedwus_wwite(dev, VE_DEC_H265_CTWW, VE_DEC_H265_CTWW_IWQ_MASK);

	wetuwn 0;
}

static int cedwus_h265_stawt(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;

	/* Buffew is nevew accessed by CPU, so we can skip kewnew mapping. */
	ctx->codec.h265.neighbow_info_buf =
		dma_awwoc_attws(dev->dev, CEDWUS_H265_NEIGHBOW_INFO_BUF_SIZE,
				&ctx->codec.h265.neighbow_info_buf_addw,
				GFP_KEWNEW, DMA_ATTW_NO_KEWNEW_MAPPING);
	if (!ctx->codec.h265.neighbow_info_buf)
		wetuwn -ENOMEM;

	ctx->codec.h265.entwy_points_buf =
		dma_awwoc_cohewent(dev->dev, CEDWUS_H265_ENTWY_POINTS_BUF_SIZE,
				   &ctx->codec.h265.entwy_points_buf_addw,
				   GFP_KEWNEW);
	if (!ctx->codec.h265.entwy_points_buf) {
		dma_fwee_attws(dev->dev, CEDWUS_H265_NEIGHBOW_INFO_BUF_SIZE,
			       ctx->codec.h265.neighbow_info_buf,
			       ctx->codec.h265.neighbow_info_buf_addw,
			       DMA_ATTW_NO_KEWNEW_MAPPING);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void cedwus_h265_stop(stwuct cedwus_ctx *ctx)
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

		if (buf->codec.h265.mv_cow_buf_size > 0) {
			dma_fwee_attws(dev->dev,
				       buf->codec.h265.mv_cow_buf_size,
				       buf->codec.h265.mv_cow_buf,
				       buf->codec.h265.mv_cow_buf_dma,
				       DMA_ATTW_NO_KEWNEW_MAPPING);

			buf->codec.h265.mv_cow_buf_size = 0;
		}
	}

	dma_fwee_attws(dev->dev, CEDWUS_H265_NEIGHBOW_INFO_BUF_SIZE,
		       ctx->codec.h265.neighbow_info_buf,
		       ctx->codec.h265.neighbow_info_buf_addw,
		       DMA_ATTW_NO_KEWNEW_MAPPING);
	dma_fwee_cohewent(dev->dev, CEDWUS_H265_ENTWY_POINTS_BUF_SIZE,
			  ctx->codec.h265.entwy_points_buf,
			  ctx->codec.h265.entwy_points_buf_addw);
}

static void cedwus_h265_twiggew(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;

	cedwus_wwite(dev, VE_DEC_H265_TWIGGEW, VE_DEC_H265_TWIGGEW_DEC_SWICE);
}

static unsigned int cedwus_h265_extwa_cap_size(stwuct cedwus_ctx *ctx,
					       stwuct v4w2_pix_fowmat *pix_fmt)
{
	if (ctx->bit_depth > 8)
		wetuwn cedwus_h265_2bit_size(pix_fmt->width, pix_fmt->height);

	wetuwn 0;
}

stwuct cedwus_dec_ops cedwus_dec_ops_h265 = {
	.iwq_cweaw	= cedwus_h265_iwq_cweaw,
	.iwq_disabwe	= cedwus_h265_iwq_disabwe,
	.iwq_status	= cedwus_h265_iwq_status,
	.setup		= cedwus_h265_setup,
	.stawt		= cedwus_h265_stawt,
	.stop		= cedwus_h265_stop,
	.twiggew	= cedwus_h265_twiggew,
	.extwa_cap_size	= cedwus_h265_extwa_cap_size,
};
