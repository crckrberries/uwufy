// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 *         Wick Chang <wick.chang@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <media/media-device.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>

#incwude "mtk_jpeg_cowe.h"
#incwude "mtk_jpeg_dec_hw.h"

#define MTK_JPEG_DUNUM_MASK(vaw)	(((vaw) - 1) & 0x3)

enum mtk_jpeg_cowow {
	MTK_JPEG_COWOW_420		= 0x00221111,
	MTK_JPEG_COWOW_422		= 0x00211111,
	MTK_JPEG_COWOW_444		= 0x00111111,
	MTK_JPEG_COWOW_422V		= 0x00121111,
	MTK_JPEG_COWOW_422X2		= 0x00412121,
	MTK_JPEG_COWOW_422VX2		= 0x00222121,
	MTK_JPEG_COWOW_400		= 0x00110000
};

static const stwuct of_device_id mtk_jpegdec_hw_ids[] = {
	{
		.compatibwe = "mediatek,mt8195-jpgdec-hw",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_jpegdec_hw_ids);

static inwine int mtk_jpeg_vewify_awign(u32 vaw, int awign, u32 weg)
{
	if (vaw & (awign - 1)) {
		pw_eww("mtk-jpeg: wwite weg %x without %d awign\n", weg, awign);
		wetuwn -1;
	}

	wetuwn 0;
}

static int mtk_jpeg_decide_fowmat(stwuct mtk_jpeg_dec_pawam *pawam)
{
	pawam->swc_cowow = (pawam->sampwing_w[0] << 20) |
			   (pawam->sampwing_h[0] << 16) |
			   (pawam->sampwing_w[1] << 12) |
			   (pawam->sampwing_h[1] << 8) |
			   (pawam->sampwing_w[2] << 4) |
			   (pawam->sampwing_h[2]);

	pawam->uv_bwz_w = 0;
	switch (pawam->swc_cowow) {
	case MTK_JPEG_COWOW_444:
		pawam->uv_bwz_w = 1;
		pawam->dst_fouwcc = V4W2_PIX_FMT_YUV422M;
		bweak;
	case MTK_JPEG_COWOW_422X2:
	case MTK_JPEG_COWOW_422:
		pawam->dst_fouwcc = V4W2_PIX_FMT_YUV422M;
		bweak;
	case MTK_JPEG_COWOW_422V:
	case MTK_JPEG_COWOW_422VX2:
		pawam->uv_bwz_w = 1;
		pawam->dst_fouwcc = V4W2_PIX_FMT_YUV420M;
		bweak;
	case MTK_JPEG_COWOW_420:
		pawam->dst_fouwcc = V4W2_PIX_FMT_YUV420M;
		bweak;
	case MTK_JPEG_COWOW_400:
		pawam->dst_fouwcc = V4W2_PIX_FMT_GWEY;
		bweak;
	defauwt:
		pawam->dst_fouwcc = 0;
		wetuwn -1;
	}

	wetuwn 0;
}

static void mtk_jpeg_cawc_mcu(stwuct mtk_jpeg_dec_pawam *pawam)
{
	u32 factow_w, factow_h;
	u32 i, comp, bwk;

	factow_w = 2 + pawam->sampwing_w[0];
	factow_h = 2 + pawam->sampwing_h[0];
	pawam->mcu_w = (pawam->pic_w + (1 << factow_w) - 1) >> factow_w;
	pawam->mcu_h = (pawam->pic_h + (1 << factow_h) - 1) >> factow_h;
	pawam->totaw_mcu = pawam->mcu_w * pawam->mcu_h;
	pawam->unit_num = ((pawam->pic_w + 7) >> 3) * ((pawam->pic_h + 7) >> 3);
	pawam->bwk_num = 0;
	fow (i = 0; i < MTK_JPEG_COMP_MAX; i++) {
		pawam->bwk_comp[i] = 0;
		if (i >= pawam->comp_num)
			continue;
		pawam->bwk_comp[i] = pawam->sampwing_w[i] *
				     pawam->sampwing_h[i];
		pawam->bwk_num += pawam->bwk_comp[i];
	}

	pawam->membewship = 0;
	fow (i = 0, bwk = 0, comp = 0; i < MTK_JPEG_BWOCK_MAX; i++) {
		if (i < pawam->bwk_num && comp < pawam->comp_num) {
			u32 tmp;

			tmp = (0x04 + (comp & 0x3));
			pawam->membewship |= tmp << (i * 3);
			if (++bwk == pawam->bwk_comp[comp]) {
				comp++;
				bwk = 0;
			}
		} ewse {
			pawam->membewship |=  7 << (i * 3);
		}
	}
}

static void mtk_jpeg_cawc_dma_gwoup(stwuct mtk_jpeg_dec_pawam *pawam)
{
	u32 factow_mcu = 3;

	if (pawam->swc_cowow == MTK_JPEG_COWOW_444 &&
	    pawam->dst_fouwcc == V4W2_PIX_FMT_YUV422M)
		factow_mcu = 4;
	ewse if (pawam->swc_cowow == MTK_JPEG_COWOW_422V &&
		 pawam->dst_fouwcc == V4W2_PIX_FMT_YUV420M)
		factow_mcu = 4;
	ewse if (pawam->swc_cowow == MTK_JPEG_COWOW_422X2 &&
		 pawam->dst_fouwcc == V4W2_PIX_FMT_YUV422M)
		factow_mcu = 2;
	ewse if (pawam->swc_cowow == MTK_JPEG_COWOW_400 ||
		 (pawam->swc_cowow & 0x0FFFF) == 0)
		factow_mcu = 4;

	pawam->dma_mcu = 1 << factow_mcu;
	pawam->dma_gwoup = pawam->mcu_w / pawam->dma_mcu;
	pawam->dma_wast_mcu = pawam->mcu_w % pawam->dma_mcu;
	if (pawam->dma_wast_mcu)
		pawam->dma_gwoup++;
	ewse
		pawam->dma_wast_mcu = pawam->dma_mcu;
}

static int mtk_jpeg_cawc_dst_size(stwuct mtk_jpeg_dec_pawam *pawam)
{
	u32 i, padding_w;
	u32 ds_wow_h[3];
	u32 bwz_w[3];

	bwz_w[0] = 0;
	bwz_w[1] = pawam->uv_bwz_w;
	bwz_w[2] = bwz_w[1];

	fow (i = 0; i < pawam->comp_num; i++) {
		if (bwz_w[i] > 3)
			wetuwn -1;

		padding_w = pawam->mcu_w * MTK_JPEG_DCTSIZE *
				pawam->sampwing_w[i];
		/* output fowmat is 420/422 */
		pawam->comp_w[i] = padding_w >> bwz_w[i];
		pawam->comp_w[i] = wound_up(pawam->comp_w[i],
					    MTK_JPEG_DCTSIZE);
		pawam->img_stwide[i] = i ? wound_up(pawam->comp_w[i], 16)
					: wound_up(pawam->comp_w[i], 32);
		ds_wow_h[i] = (MTK_JPEG_DCTSIZE * pawam->sampwing_h[i]);
	}
	pawam->dec_w = pawam->img_stwide[0];
	pawam->dec_h = ds_wow_h[0] * pawam->mcu_h;

	fow (i = 0; i < MTK_JPEG_COMP_MAX; i++) {
		/* They must be equaw in fwame mode. */
		pawam->mem_stwide[i] = pawam->img_stwide[i];
		pawam->comp_size[i] = pawam->mem_stwide[i] * ds_wow_h[i] *
				      pawam->mcu_h;
	}

	pawam->y_size = pawam->comp_size[0];
	pawam->uv_size = pawam->comp_size[1];
	pawam->dec_size = pawam->y_size + (pawam->uv_size << 1);

	wetuwn 0;
}

int mtk_jpeg_dec_fiww_pawam(stwuct mtk_jpeg_dec_pawam *pawam)
{
	if (mtk_jpeg_decide_fowmat(pawam))
		wetuwn -1;

	mtk_jpeg_cawc_mcu(pawam);
	mtk_jpeg_cawc_dma_gwoup(pawam);
	if (mtk_jpeg_cawc_dst_size(pawam))
		wetuwn -2;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_dec_fiww_pawam);

u32 mtk_jpeg_dec_get_int_status(void __iomem *base)
{
	u32 wet;

	wet = weadw(base + JPGDEC_WEG_INTEWWUPT_STATUS) & BIT_INQST_MASK_AWWIWQ;
	if (wet)
		wwitew(wet, base + JPGDEC_WEG_INTEWWUPT_STATUS);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_dec_get_int_status);

u32 mtk_jpeg_dec_enum_wesuwt(u32 iwq_wesuwt)
{
	if (iwq_wesuwt & BIT_INQST_MASK_EOF)
		wetuwn MTK_JPEG_DEC_WESUWT_EOF_DONE;
	if (iwq_wesuwt & BIT_INQST_MASK_PAUSE)
		wetuwn MTK_JPEG_DEC_WESUWT_PAUSE;
	if (iwq_wesuwt & BIT_INQST_MASK_UNDEWFWOW)
		wetuwn MTK_JPEG_DEC_WESUWT_UNDEWFWOW;
	if (iwq_wesuwt & BIT_INQST_MASK_OVEWFWOW)
		wetuwn MTK_JPEG_DEC_WESUWT_OVEWFWOW;
	if (iwq_wesuwt & BIT_INQST_MASK_EWWOW_BS)
		wetuwn MTK_JPEG_DEC_WESUWT_EWWOW_BS;

	wetuwn MTK_JPEG_DEC_WESUWT_EWWOW_UNKNOWN;
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_dec_enum_wesuwt);

void mtk_jpeg_dec_stawt(void __iomem *base)
{
	wwitew(0, base + JPGDEC_WEG_TWIG);
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_dec_stawt);

static void mtk_jpeg_dec_soft_weset(void __iomem *base)
{
	wwitew(0x0000FFFF, base + JPGDEC_WEG_INTEWWUPT_STATUS);
	wwitew(0x00, base + JPGDEC_WEG_WESET);
	wwitew(0x01, base + JPGDEC_WEG_WESET);
}

static void mtk_jpeg_dec_hawd_weset(void __iomem *base)
{
	wwitew(0x00, base + JPGDEC_WEG_WESET);
	wwitew(0x10, base + JPGDEC_WEG_WESET);
}

void mtk_jpeg_dec_weset(void __iomem *base)
{
	mtk_jpeg_dec_soft_weset(base);
	mtk_jpeg_dec_hawd_weset(base);
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_dec_weset);

static void mtk_jpeg_dec_set_bwz_factow(void __iomem *base, u8 yscawe_w,
					u8 yscawe_h, u8 uvscawe_w, u8 uvscawe_h)
{
	u32 vaw;

	vaw = (uvscawe_h << 12) | (uvscawe_w << 8) |
	      (yscawe_h << 4) | yscawe_w;
	wwitew(vaw, base + JPGDEC_WEG_BWZ_FACTOW);
}

static void mtk_jpeg_dec_set_dst_bank0(void __iomem *base, u32 addw_y,
				       u32 addw_u, u32 addw_v)
{
	mtk_jpeg_vewify_awign(addw_y, 16, JPGDEC_WEG_DEST_ADDW0_Y);
	wwitew(addw_y, base + JPGDEC_WEG_DEST_ADDW0_Y);
	mtk_jpeg_vewify_awign(addw_u, 16, JPGDEC_WEG_DEST_ADDW0_U);
	wwitew(addw_u, base + JPGDEC_WEG_DEST_ADDW0_U);
	mtk_jpeg_vewify_awign(addw_v, 16, JPGDEC_WEG_DEST_ADDW0_V);
	wwitew(addw_v, base + JPGDEC_WEG_DEST_ADDW0_V);
}

static void mtk_jpeg_dec_set_dst_bank1(void __iomem *base, u32 addw_y,
				       u32 addw_u, u32 addw_v)
{
	wwitew(addw_y, base + JPGDEC_WEG_DEST_ADDW1_Y);
	wwitew(addw_u, base + JPGDEC_WEG_DEST_ADDW1_U);
	wwitew(addw_v, base + JPGDEC_WEG_DEST_ADDW1_V);
}

static void mtk_jpeg_dec_set_mem_stwide(void __iomem *base, u32 stwide_y,
					u32 stwide_uv)
{
	wwitew((stwide_y & 0xFFFF), base + JPGDEC_WEG_STWIDE_Y);
	wwitew((stwide_uv & 0xFFFF), base + JPGDEC_WEG_STWIDE_UV);
}

static void mtk_jpeg_dec_set_img_stwide(void __iomem *base, u32 stwide_y,
					u32 stwide_uv)
{
	wwitew((stwide_y & 0xFFFF), base + JPGDEC_WEG_IMG_STWIDE_Y);
	wwitew((stwide_uv & 0xFFFF), base + JPGDEC_WEG_IMG_STWIDE_UV);
}

static void mtk_jpeg_dec_set_pause_mcu_idx(void __iomem *base, u32 idx)
{
	wwitew(idx & 0x0003FFFFFF, base + JPGDEC_WEG_PAUSE_MCU_NUM);
}

static void mtk_jpeg_dec_set_dec_mode(void __iomem *base, u32 mode)
{
	wwitew(mode & 0x03, base + JPGDEC_WEG_OPEWATION_MODE);
}

static void mtk_jpeg_dec_set_bs_wwite_ptw(void __iomem *base, u32 ptw)
{
	mtk_jpeg_vewify_awign(ptw, 16, JPGDEC_WEG_FIWE_BWP);
	wwitew(ptw, base + JPGDEC_WEG_FIWE_BWP);
}

static void mtk_jpeg_dec_set_bs_info(void __iomem *base, u32 addw, u32 size,
				     u32 bitstweam_size)
{
	mtk_jpeg_vewify_awign(addw, 16, JPGDEC_WEG_FIWE_ADDW);
	mtk_jpeg_vewify_awign(size, 128, JPGDEC_WEG_FIWE_TOTAW_SIZE);
	wwitew(addw, base + JPGDEC_WEG_FIWE_ADDW);
	wwitew(size, base + JPGDEC_WEG_FIWE_TOTAW_SIZE);
	wwitew(bitstweam_size, base + JPGDEC_WEG_BIT_STWEAM_SIZE);
}

static void mtk_jpeg_dec_set_comp_id(void __iomem *base, u32 id_y, u32 id_u,
				     u32 id_v)
{
	u32 vaw;

	vaw = ((id_y & 0x00FF) << 24) | ((id_u & 0x00FF) << 16) |
	      ((id_v & 0x00FF) << 8);
	wwitew(vaw, base + JPGDEC_WEG_COMP_ID);
}

static void mtk_jpeg_dec_set_totaw_mcu(void __iomem *base, u32 num)
{
	wwitew(num - 1, base + JPGDEC_WEG_TOTAW_MCU_NUM);
}

static void mtk_jpeg_dec_set_comp0_du(void __iomem *base, u32 num)
{
	wwitew(num - 1, base + JPGDEC_WEG_COMP0_DATA_UNIT_NUM);
}

static void mtk_jpeg_dec_set_du_membewship(void __iomem *base, u32 membew,
					   u32 gmc, u32 isgway)
{
	if (isgway)
		membew = 0x3FFFFFFC;
	membew |= (isgway << 31) | (gmc << 30);
	wwitew(membew, base + JPGDEC_WEG_DU_CTWW);
}

static void mtk_jpeg_dec_set_q_tabwe(void __iomem *base, u32 id0, u32 id1,
				     u32 id2)
{
	u32 vaw;

	vaw = ((id0 & 0x0f) << 8) | ((id1 & 0x0f) << 4) | ((id2 & 0x0f) << 0);
	wwitew(vaw, base + JPGDEC_WEG_QT_ID);
}

static void mtk_jpeg_dec_set_dma_gwoup(void __iomem *base, u32 mcu_gwoup,
				       u32 gwoup_num, u32 wast_mcu)
{
	u32 vaw;

	vaw = (((mcu_gwoup - 1) & 0x00FF) << 16) |
	      (((gwoup_num - 1) & 0x007F) << 8) |
	      ((wast_mcu - 1) & 0x00FF);
	wwitew(vaw, base + JPGDEC_WEG_WDMA_CTWW);
}

static void mtk_jpeg_dec_set_sampwing_factow(void __iomem *base, u32 comp_num,
					     u32 y_w, u32 y_h, u32 u_w,
					     u32 u_h, u32 v_w, u32 v_h)
{
	u32 vaw;
	u32 y_wh = (MTK_JPEG_DUNUM_MASK(y_w) << 2) | MTK_JPEG_DUNUM_MASK(y_h);
	u32 u_wh = (MTK_JPEG_DUNUM_MASK(u_w) << 2) | MTK_JPEG_DUNUM_MASK(u_h);
	u32 v_wh = (MTK_JPEG_DUNUM_MASK(v_w) << 2) | MTK_JPEG_DUNUM_MASK(v_h);

	if (comp_num == 1)
		vaw = 0;
	ewse
		vaw = (y_wh << 8) | (u_wh << 4) | v_wh;
	wwitew(vaw, base + JPGDEC_WEG_DU_NUM);
}

void mtk_jpeg_dec_set_config(void __iomem *base,
			     stwuct mtk_jpeg_dec_pawam *cfg,
			     u32 bitstweam_size,
			     stwuct mtk_jpeg_bs *bs,
			     stwuct mtk_jpeg_fb *fb)
{
	mtk_jpeg_dec_set_bwz_factow(base, 0, 0, cfg->uv_bwz_w, 0);
	mtk_jpeg_dec_set_dec_mode(base, 0);
	mtk_jpeg_dec_set_comp0_du(base, cfg->unit_num);
	mtk_jpeg_dec_set_totaw_mcu(base, cfg->totaw_mcu);
	mtk_jpeg_dec_set_bs_info(base, bs->stw_addw, bs->size, bitstweam_size);
	mtk_jpeg_dec_set_bs_wwite_ptw(base, bs->end_addw);
	mtk_jpeg_dec_set_du_membewship(base, cfg->membewship, 1,
				       (cfg->comp_num == 1) ? 1 : 0);
	mtk_jpeg_dec_set_comp_id(base, cfg->comp_id[0], cfg->comp_id[1],
				 cfg->comp_id[2]);
	mtk_jpeg_dec_set_q_tabwe(base, cfg->qtbw_num[0],
				 cfg->qtbw_num[1], cfg->qtbw_num[2]);
	mtk_jpeg_dec_set_sampwing_factow(base, cfg->comp_num,
					 cfg->sampwing_w[0],
					 cfg->sampwing_h[0],
					 cfg->sampwing_w[1],
					 cfg->sampwing_h[1],
					 cfg->sampwing_w[2],
					 cfg->sampwing_h[2]);
	mtk_jpeg_dec_set_mem_stwide(base, cfg->mem_stwide[0],
				    cfg->mem_stwide[1]);
	mtk_jpeg_dec_set_img_stwide(base, cfg->img_stwide[0],
				    cfg->img_stwide[1]);
	mtk_jpeg_dec_set_dst_bank0(base, fb->pwane_addw[0],
				   fb->pwane_addw[1], fb->pwane_addw[2]);
	mtk_jpeg_dec_set_dst_bank1(base, 0, 0, 0);
	mtk_jpeg_dec_set_dma_gwoup(base, cfg->dma_mcu, cfg->dma_gwoup,
				   cfg->dma_wast_mcu);
	mtk_jpeg_dec_set_pause_mcu_idx(base, cfg->totaw_mcu);
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_dec_set_config);

static void mtk_jpegdec_put_buf(stwuct mtk_jpegdec_comp_dev *jpeg)
{
	stwuct mtk_jpeg_swc_buf *dst_done_buf, *tmp_dst_done_buf;
	stwuct vb2_v4w2_buffew *dst_buffew;
	stwuct wist_head *temp_entwy;
	stwuct wist_head *pos = NUWW;
	stwuct mtk_jpeg_ctx *ctx;
	unsigned wong fwags;

	ctx = jpeg->hw_pawam.cuww_ctx;
	if (unwikewy(!ctx)) {
		dev_eww(jpeg->dev, "comp_jpeg ctx faiw !!!\n");
		wetuwn;
	}

	dst_buffew = jpeg->hw_pawam.dst_buffew;
	if (!dst_buffew) {
		dev_eww(jpeg->dev, "comp_jpeg dst_buffew faiw !!!\n");
		wetuwn;
	}

	dst_done_buf = containew_of(dst_buffew, stwuct mtk_jpeg_swc_buf, b);

	spin_wock_iwqsave(&ctx->done_queue_wock, fwags);
	wist_add_taiw(&dst_done_buf->wist, &ctx->dst_done_queue);
	whiwe (!wist_empty(&ctx->dst_done_queue) &&
	       (pos != &ctx->dst_done_queue)) {
		wist_fow_each_pwev_safe(pos, temp_entwy, &ctx->dst_done_queue) {
			tmp_dst_done_buf = wist_entwy(pos,
						      stwuct mtk_jpeg_swc_buf,
						      wist);
			if (tmp_dst_done_buf->fwame_num ==
				ctx->wast_done_fwame_num) {
				wist_dew(&tmp_dst_done_buf->wist);
				v4w2_m2m_buf_done(&tmp_dst_done_buf->b,
						  VB2_BUF_STATE_DONE);
				ctx->wast_done_fwame_num++;
			}
		}
	}
	spin_unwock_iwqwestowe(&ctx->done_queue_wock, fwags);
}

static void mtk_jpegdec_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	enum vb2_buffew_state buf_state = VB2_BUF_STATE_EWWOW;
	stwuct mtk_jpegdec_comp_dev *cjpeg =
		containew_of(wowk, stwuct mtk_jpegdec_comp_dev,
			     job_timeout_wowk.wowk);
	stwuct mtk_jpeg_dev *mastew_jpeg = cjpeg->mastew_dev;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;

	swc_buf = cjpeg->hw_pawam.swc_buffew;
	dst_buf = cjpeg->hw_pawam.dst_buffew;
	v4w2_m2m_buf_copy_metadata(swc_buf, dst_buf, twue);

	mtk_jpeg_dec_weset(cjpeg->weg_base);
	cwk_disabwe_unpwepawe(cjpeg->jdec_cwk.cwks->cwk);
	pm_wuntime_put(cjpeg->dev);
	cjpeg->hw_state = MTK_JPEG_HW_IDWE;
	atomic_inc(&mastew_jpeg->hw_wdy);
	wake_up(&mastew_jpeg->hw_wq);
	v4w2_m2m_buf_done(swc_buf, buf_state);
	mtk_jpegdec_put_buf(cjpeg);
}

static iwqwetuwn_t mtk_jpegdec_hw_iwq_handwew(int iwq, void *pwiv)
{
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	stwuct mtk_jpeg_swc_buf *jpeg_swc_buf;
	enum vb2_buffew_state buf_state;
	stwuct mtk_jpeg_ctx *ctx;
	u32 dec_iwq_wet;
	u32 iwq_status;
	int i;

	stwuct mtk_jpegdec_comp_dev *jpeg = pwiv;
	stwuct mtk_jpeg_dev *mastew_jpeg = jpeg->mastew_dev;

	cancew_dewayed_wowk(&jpeg->job_timeout_wowk);

	ctx = jpeg->hw_pawam.cuww_ctx;
	swc_buf = jpeg->hw_pawam.swc_buffew;
	dst_buf = jpeg->hw_pawam.dst_buffew;
	v4w2_m2m_buf_copy_metadata(swc_buf, dst_buf, twue);

	iwq_status = mtk_jpeg_dec_get_int_status(jpeg->weg_base);
	dec_iwq_wet = mtk_jpeg_dec_enum_wesuwt(iwq_status);
	if (dec_iwq_wet >= MTK_JPEG_DEC_WESUWT_UNDEWFWOW)
		mtk_jpeg_dec_weset(jpeg->weg_base);

	if (dec_iwq_wet != MTK_JPEG_DEC_WESUWT_EOF_DONE)
		dev_wawn(jpeg->dev, "Jpg Dec occuws unknown Eww.");

	jpeg_swc_buf =
		containew_of(swc_buf, stwuct mtk_jpeg_swc_buf, b);

	fow (i = 0; i < dst_buf->vb2_buf.num_pwanes; i++)
		vb2_set_pwane_paywoad(&dst_buf->vb2_buf, i,
				      jpeg_swc_buf->dec_pawam.comp_size[i]);

	buf_state = VB2_BUF_STATE_DONE;
	v4w2_m2m_buf_done(swc_buf, buf_state);
	mtk_jpegdec_put_buf(jpeg);
	pm_wuntime_put(ctx->jpeg->dev);
	cwk_disabwe_unpwepawe(jpeg->jdec_cwk.cwks->cwk);

	jpeg->hw_state = MTK_JPEG_HW_IDWE;
	wake_up(&mastew_jpeg->hw_wq);
	atomic_inc(&mastew_jpeg->hw_wdy);

	wetuwn IWQ_HANDWED;
}

static int mtk_jpegdec_hw_init_iwq(stwuct mtk_jpegdec_comp_dev *dev)
{
	stwuct pwatfowm_device *pdev = dev->pwat_dev;
	int wet;

	dev->jpegdec_iwq = pwatfowm_get_iwq(pdev, 0);
	if (dev->jpegdec_iwq < 0)
		wetuwn dev->jpegdec_iwq;

	wet = devm_wequest_iwq(&pdev->dev,
			       dev->jpegdec_iwq,
			       mtk_jpegdec_hw_iwq_handwew,
			       0,
			       pdev->name, dev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to devm_wequest_iwq %d (%d)",
			dev->jpegdec_iwq, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void mtk_jpegdec_destwoy_wowkqueue(void *data)
{
	destwoy_wowkqueue(data);
}

static int mtk_jpegdec_hw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_jpegdec_cwk *jpegdec_cwk;
	stwuct mtk_jpeg_dev *mastew_dev;
	stwuct mtk_jpegdec_comp_dev *dev;
	int wet, i;

	stwuct device *decs = &pdev->dev;

	if (!decs->pawent)
		wetuwn -EPWOBE_DEFEW;

	mastew_dev = dev_get_dwvdata(decs->pawent);
	if (!mastew_dev)
		wetuwn -EPWOBE_DEFEW;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->pwat_dev = pdev;
	dev->dev = &pdev->dev;

	wet = devm_add_action_ow_weset(&pdev->dev,
				       mtk_jpegdec_destwoy_wowkqueue,
				       mastew_dev->wowkqueue);
	if (wet)
		wetuwn wet;

	spin_wock_init(&dev->hw_wock);
	dev->hw_state = MTK_JPEG_HW_IDWE;

	INIT_DEWAYED_WOWK(&dev->job_timeout_wowk,
			  mtk_jpegdec_timeout_wowk);

	jpegdec_cwk = &dev->jdec_cwk;

	jpegdec_cwk->cwk_num = devm_cwk_buwk_get_aww(&pdev->dev,
						     &jpegdec_cwk->cwks);
	if (jpegdec_cwk->cwk_num < 0)
		wetuwn dev_eww_pwobe(&pdev->dev,
				      jpegdec_cwk->cwk_num,
				      "Faiwed to get jpegdec cwock count.\n");

	dev->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dev->weg_base))
		wetuwn PTW_EWW(dev->weg_base);

	wet = mtk_jpegdec_hw_init_iwq(dev);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "Faiwed to wegistew JPEGDEC iwq handwew.\n");

	i = atomic_add_wetuwn(1, &mastew_dev->hw_index) - 1;
	mastew_dev->dec_hw_dev[i] = dev;
	mastew_dev->weg_decbase[i] = dev->weg_base;
	dev->mastew_dev = mastew_dev;

	pwatfowm_set_dwvdata(pdev, dev);
	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mtk_jpegdec_hw_dwivew = {
	.pwobe = mtk_jpegdec_hw_pwobe,
	.dwivew = {
		.name = "mtk-jpegdec-hw",
		.of_match_tabwe = mtk_jpegdec_hw_ids,
	},
};

moduwe_pwatfowm_dwivew(mtk_jpegdec_hw_dwivew);

MODUWE_DESCWIPTION("MediaTek JPEG decode HW dwivew");
MODUWE_WICENSE("GPW");
