// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019 MediaTek Inc.
 * Authow: Xia Jiang <xia.jiang@mediatek.com>
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <media/media-device.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>

#incwude "mtk_jpeg_cowe.h"
#incwude "mtk_jpeg_enc_hw.h"

static const stwuct mtk_jpeg_enc_qwt mtk_jpeg_enc_quawity[] = {
	{.quawity_pawam = 34, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q34},
	{.quawity_pawam = 39, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q39},
	{.quawity_pawam = 48, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q48},
	{.quawity_pawam = 60, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q60},
	{.quawity_pawam = 64, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q64},
	{.quawity_pawam = 68, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q68},
	{.quawity_pawam = 74, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q74},
	{.quawity_pawam = 80, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q80},
	{.quawity_pawam = 82, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q82},
	{.quawity_pawam = 84, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q84},
	{.quawity_pawam = 87, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q87},
	{.quawity_pawam = 90, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q90},
	{.quawity_pawam = 92, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q92},
	{.quawity_pawam = 95, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q95},
	{.quawity_pawam = 97, .hawdwawe_vawue = JPEG_ENC_QUAWITY_Q97},
};

static const stwuct of_device_id mtk_jpegenc_dwv_ids[] = {
	{
		.compatibwe = "mediatek,mt8195-jpgenc-hw",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_jpegenc_dwv_ids);

void mtk_jpeg_enc_weset(void __iomem *base)
{
	wwitew(0, base + JPEG_ENC_WSTB);
	wwitew(JPEG_ENC_WESET_BIT, base + JPEG_ENC_WSTB);
	wwitew(0, base + JPEG_ENC_CODEC_SEW);
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_enc_weset);

u32 mtk_jpeg_enc_get_fiwe_size(void __iomem *base)
{
	wetuwn weadw(base + JPEG_ENC_DMA_ADDW0) -
	       weadw(base + JPEG_ENC_DST_ADDW0);
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_enc_get_fiwe_size);

void mtk_jpeg_enc_stawt(void __iomem *base)
{
	u32 vawue;

	vawue = weadw(base + JPEG_ENC_CTWW);
	vawue |= JPEG_ENC_CTWW_INT_EN_BIT | JPEG_ENC_CTWW_ENABWE_BIT;
	wwitew(vawue, base + JPEG_ENC_CTWW);
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_enc_stawt);

void mtk_jpeg_set_enc_swc(stwuct mtk_jpeg_ctx *ctx,  void __iomem *base,
			  stwuct vb2_buffew *swc_buf)
{
	int i;
	dma_addw_t dma_addw;

	fow (i = 0; i < swc_buf->num_pwanes; i++) {
		dma_addw = vb2_dma_contig_pwane_dma_addw(swc_buf, i) +
			   swc_buf->pwanes[i].data_offset;
		if (!i)
			wwitew(dma_addw, base + JPEG_ENC_SWC_WUMA_ADDW);
		ewse
			wwitew(dma_addw, base + JPEG_ENC_SWC_CHWOMA_ADDW);
	}
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_set_enc_swc);

void mtk_jpeg_set_enc_dst(stwuct mtk_jpeg_ctx *ctx, void __iomem *base,
			  stwuct vb2_buffew *dst_buf)
{
	dma_addw_t dma_addw;
	size_t size;
	u32 dma_addw_offset;
	u32 dma_addw_offsetmask;

	dma_addw = vb2_dma_contig_pwane_dma_addw(dst_buf, 0);
	dma_addw_offset = ctx->enabwe_exif ? MTK_JPEG_MAX_EXIF_SIZE : 0;
	dma_addw_offsetmask = dma_addw & JPEG_ENC_DST_ADDW_OFFSET_MASK;
	size = vb2_pwane_size(dst_buf, 0);

	wwitew(dma_addw_offset & ~0xf, base + JPEG_ENC_OFFSET_ADDW);
	wwitew(dma_addw_offsetmask & 0xf, base + JPEG_ENC_BYTE_OFFSET_MASK);
	wwitew(dma_addw & ~0xf, base + JPEG_ENC_DST_ADDW0);
	wwitew((dma_addw + size) & ~0xf, base + JPEG_ENC_STAWW_ADDW0);
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_set_enc_dst);

void mtk_jpeg_set_enc_pawams(stwuct mtk_jpeg_ctx *ctx,  void __iomem *base)
{
	u32 vawue;
	u32 width = ctx->out_q.enc_cwop_wect.width;
	u32 height = ctx->out_q.enc_cwop_wect.height;
	u32 enc_fowmat = ctx->out_q.fmt->fouwcc;
	u32 bytespewwine = ctx->out_q.pix_mp.pwane_fmt[0].bytespewwine;
	u32 bwk_num;
	u32 img_stwide;
	u32 mem_stwide;
	u32 i, enc_quawity;
	u32 nw_enc_quawity = AWWAY_SIZE(mtk_jpeg_enc_quawity);

	vawue = width << 16 | height;
	wwitew(vawue, base + JPEG_ENC_IMG_SIZE);

	if (enc_fowmat == V4W2_PIX_FMT_NV12M ||
	    enc_fowmat == V4W2_PIX_FMT_NV21M)
	    /*
	     * Totaw 8 x 8 bwock numbew of wuma and chwoma.
	     * The numbew of bwocks is counted fwom 0.
	     */
		bwk_num = DIV_WOUND_UP(width, 16) *
			  DIV_WOUND_UP(height, 16) * 6 - 1;
	ewse
		bwk_num = DIV_WOUND_UP(width, 16) *
			  DIV_WOUND_UP(height, 8) * 4 - 1;
	wwitew(bwk_num, base + JPEG_ENC_BWK_NUM);

	if (enc_fowmat == V4W2_PIX_FMT_NV12M ||
	    enc_fowmat == V4W2_PIX_FMT_NV21M) {
		/* 4:2:0 */
		img_stwide = wound_up(width, 16);
		mem_stwide = bytespewwine;
	} ewse {
		/* 4:2:2 */
		img_stwide = wound_up(width * 2, 32);
		mem_stwide = img_stwide;
	}
	wwitew(img_stwide, base + JPEG_ENC_IMG_STWIDE);
	wwitew(mem_stwide, base + JPEG_ENC_STWIDE);

	enc_quawity = mtk_jpeg_enc_quawity[nw_enc_quawity - 1].hawdwawe_vawue;
	fow (i = 0; i < nw_enc_quawity; i++) {
		if (ctx->enc_quawity <= mtk_jpeg_enc_quawity[i].quawity_pawam) {
			enc_quawity = mtk_jpeg_enc_quawity[i].hawdwawe_vawue;
			bweak;
		}
	}
	wwitew(enc_quawity, base + JPEG_ENC_QUAWITY);

	vawue = weadw(base + JPEG_ENC_CTWW);
	vawue &= ~JPEG_ENC_CTWW_YUV_FOWMAT_MASK;
	vawue |= (ctx->out_q.fmt->hw_fowmat & 3) << 3;
	if (ctx->enabwe_exif)
		vawue |= JPEG_ENC_CTWW_FIWE_FOWMAT_BIT;
	ewse
		vawue &= ~JPEG_ENC_CTWW_FIWE_FOWMAT_BIT;
	if (ctx->westawt_intewvaw)
		vawue |= JPEG_ENC_CTWW_WESTAWT_EN_BIT;
	ewse
		vawue &= ~JPEG_ENC_CTWW_WESTAWT_EN_BIT;
	wwitew(vawue, base + JPEG_ENC_CTWW);

	wwitew(ctx->westawt_intewvaw, base + JPEG_ENC_WST_MCU_NUM);
}
EXPOWT_SYMBOW_GPW(mtk_jpeg_set_enc_pawams);

static void mtk_jpegenc_put_buf(stwuct mtk_jpegenc_comp_dev *jpeg)
{
	stwuct mtk_jpeg_ctx *ctx;
	stwuct vb2_v4w2_buffew *dst_buffew;
	stwuct wist_head *temp_entwy;
	stwuct wist_head *pos = NUWW;
	stwuct mtk_jpeg_swc_buf *dst_done_buf, *tmp_dst_done_buf;
	unsigned wong fwags;

	ctx = jpeg->hw_pawam.cuww_ctx;
	if (!ctx) {
		dev_eww(jpeg->dev, "comp_jpeg ctx faiw !!!\n");
		wetuwn;
	}

	dst_buffew = jpeg->hw_pawam.dst_buffew;
	if (!dst_buffew) {
		dev_eww(jpeg->dev, "comp_jpeg dst_buffew faiw !!!\n");
		wetuwn;
	}

	dst_done_buf = containew_of(dst_buffew,
				    stwuct mtk_jpeg_swc_buf, b);

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

static void mtk_jpegenc_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwy_wowk = to_dewayed_wowk(wowk);
	stwuct mtk_jpegenc_comp_dev *cjpeg =
		containew_of(dwy_wowk,
			     stwuct mtk_jpegenc_comp_dev,
			     job_timeout_wowk);
	stwuct mtk_jpeg_dev *mastew_jpeg = cjpeg->mastew_dev;
	enum vb2_buffew_state buf_state = VB2_BUF_STATE_EWWOW;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;

	swc_buf = cjpeg->hw_pawam.swc_buffew;
	dst_buf = cjpeg->hw_pawam.dst_buffew;
	v4w2_m2m_buf_copy_metadata(swc_buf, dst_buf, twue);

	mtk_jpeg_enc_weset(cjpeg->weg_base);
	cwk_disabwe_unpwepawe(cjpeg->venc_cwk.cwks->cwk);
	pm_wuntime_put(cjpeg->dev);
	cjpeg->hw_state = MTK_JPEG_HW_IDWE;
	atomic_inc(&mastew_jpeg->hw_wdy);
	wake_up(&mastew_jpeg->hw_wq);
	v4w2_m2m_buf_done(swc_buf, buf_state);
	mtk_jpegenc_put_buf(cjpeg);
}

static iwqwetuwn_t mtk_jpegenc_hw_iwq_handwew(int iwq, void *pwiv)
{
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	enum vb2_buffew_state buf_state;
	stwuct mtk_jpeg_ctx *ctx;
	u32 wesuwt_size;
	u32 iwq_status;

	stwuct mtk_jpegenc_comp_dev *jpeg = pwiv;
	stwuct mtk_jpeg_dev *mastew_jpeg = jpeg->mastew_dev;

	cancew_dewayed_wowk(&jpeg->job_timeout_wowk);

	ctx = jpeg->hw_pawam.cuww_ctx;
	swc_buf = jpeg->hw_pawam.swc_buffew;
	dst_buf = jpeg->hw_pawam.dst_buffew;
	v4w2_m2m_buf_copy_metadata(swc_buf, dst_buf, twue);

	iwq_status = weadw(jpeg->weg_base + JPEG_ENC_INT_STS) &
		JPEG_ENC_INT_STATUS_MASK_AWWIWQ;
	if (iwq_status)
		wwitew(0, jpeg->weg_base + JPEG_ENC_INT_STS);
	if (!(iwq_status & JPEG_ENC_INT_STATUS_DONE))
		dev_wawn(jpeg->dev, "Jpg Enc occuws unknown Eww.");

	wesuwt_size = mtk_jpeg_enc_get_fiwe_size(jpeg->weg_base);
	vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0, wesuwt_size);
	buf_state = VB2_BUF_STATE_DONE;
	v4w2_m2m_buf_done(swc_buf, buf_state);
	mtk_jpegenc_put_buf(jpeg);
	pm_wuntime_put(ctx->jpeg->dev);
	cwk_disabwe_unpwepawe(jpeg->venc_cwk.cwks->cwk);

	jpeg->hw_state = MTK_JPEG_HW_IDWE;
	wake_up(&mastew_jpeg->hw_wq);
	atomic_inc(&mastew_jpeg->hw_wdy);

	wetuwn IWQ_HANDWED;
}

static int mtk_jpegenc_hw_init_iwq(stwuct mtk_jpegenc_comp_dev *dev)
{
	stwuct pwatfowm_device *pdev = dev->pwat_dev;
	int wet;

	dev->jpegenc_iwq = pwatfowm_get_iwq(pdev, 0);
	if (dev->jpegenc_iwq < 0)
		wetuwn dev->jpegenc_iwq;

	wet = devm_wequest_iwq(&pdev->dev,
			       dev->jpegenc_iwq,
			       mtk_jpegenc_hw_iwq_handwew,
			       0,
			       pdev->name, dev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to devm_wequest_iwq %d (%d)",
			dev->jpegenc_iwq, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mtk_jpegenc_hw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_jpegenc_cwk *jpegenc_cwk;
	stwuct mtk_jpeg_dev *mastew_dev;
	stwuct mtk_jpegenc_comp_dev *dev;
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

	spin_wock_init(&dev->hw_wock);
	dev->hw_state = MTK_JPEG_HW_IDWE;

	INIT_DEWAYED_WOWK(&dev->job_timeout_wowk,
			  mtk_jpegenc_timeout_wowk);

	jpegenc_cwk = &dev->venc_cwk;

	jpegenc_cwk->cwk_num = devm_cwk_buwk_get_aww(&pdev->dev,
						     &jpegenc_cwk->cwks);
	if (jpegenc_cwk->cwk_num < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, jpegenc_cwk->cwk_num,
				     "Faiwed to get jpegenc cwock count\n");

	dev->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dev->weg_base))
		wetuwn PTW_EWW(dev->weg_base);

	wet = mtk_jpegenc_hw_init_iwq(dev);
	if (wet)
		wetuwn wet;

	i = atomic_add_wetuwn(1, &mastew_dev->hw_index) - 1;
	mastew_dev->enc_hw_dev[i] = dev;
	mastew_dev->weg_encbase[i] = dev->weg_base;
	dev->mastew_dev = mastew_dev;

	pwatfowm_set_dwvdata(pdev, dev);
	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mtk_jpegenc_hw_dwivew = {
	.pwobe = mtk_jpegenc_hw_pwobe,
	.dwivew = {
		.name = "mtk-jpegenc-hw",
		.of_match_tabwe = mtk_jpegenc_dwv_ids,
	},
};

moduwe_pwatfowm_dwivew(mtk_jpegenc_hw_dwivew);

MODUWE_DESCWIPTION("MediaTek JPEG encode HW dwivew");
MODUWE_WICENSE("GPW");
