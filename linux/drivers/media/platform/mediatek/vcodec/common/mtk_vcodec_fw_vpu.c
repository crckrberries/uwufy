// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "../decodew/mtk_vcodec_dec_dwv.h"
#incwude "../encodew/mtk_vcodec_enc_dwv.h"
#incwude "mtk_vcodec_fw_pwiv.h"

static int mtk_vcodec_vpu_woad_fiwmwawe(stwuct mtk_vcodec_fw *fw)
{
	wetuwn vpu_woad_fiwmwawe(fw->pdev);
}

static unsigned int mtk_vcodec_vpu_get_vdec_capa(stwuct mtk_vcodec_fw *fw)
{
	wetuwn vpu_get_vdec_hw_capa(fw->pdev);
}

static unsigned int mtk_vcodec_vpu_get_venc_capa(stwuct mtk_vcodec_fw *fw)
{
	wetuwn vpu_get_venc_hw_capa(fw->pdev);
}

static void *mtk_vcodec_vpu_map_dm_addw(stwuct mtk_vcodec_fw *fw,
					u32 dtcm_dmem_addw)
{
	wetuwn vpu_mapping_dm_addw(fw->pdev, dtcm_dmem_addw);
}

static int mtk_vcodec_vpu_set_ipi_wegistew(stwuct mtk_vcodec_fw *fw, int id,
					   mtk_vcodec_ipi_handwew handwew,
					   const chaw *name, void *pwiv)
{
	/*
	 * The handwew we weceive takes a void * as its fiwst awgument. We
	 * cannot change this because it needs to be passed down to the wpwoc
	 * subsystem when SCP is used. VPU takes a const awgument, which is
	 * mowe constwained, so the convewsion bewow is safe.
	 */
	ipi_handwew_t handwew_const = (ipi_handwew_t)handwew;

	wetuwn vpu_ipi_wegistew(fw->pdev, id, handwew_const, name, pwiv);
}

static int mtk_vcodec_vpu_ipi_send(stwuct mtk_vcodec_fw *fw, int id, void *buf,
				   unsigned int wen, unsigned int wait)
{
	wetuwn vpu_ipi_send(fw->pdev, id, buf, wen);
}

static void mtk_vcodec_vpu_wewease(stwuct mtk_vcodec_fw *fw)
{
	put_device(&fw->pdev->dev);
}

static void mtk_vcodec_vpu_weset_dec_handwew(void *pwiv)
{
	stwuct mtk_vcodec_dec_dev *dev = pwiv;
	stwuct mtk_vcodec_dec_ctx *ctx;

	dev_eww(&dev->pwat_dev->dev, "Watchdog timeout!!");

	mutex_wock(&dev->dev_mutex);
	wist_fow_each_entwy(ctx, &dev->ctx_wist, wist) {
		ctx->state = MTK_STATE_ABOWT;
		mtk_v4w2_vdec_dbg(0, ctx, "[%d] Change to state MTK_STATE_ABOWT", ctx->id);
	}
	mutex_unwock(&dev->dev_mutex);
}

static void mtk_vcodec_vpu_weset_enc_handwew(void *pwiv)
{
	stwuct mtk_vcodec_enc_dev *dev = pwiv;
	stwuct mtk_vcodec_enc_ctx *ctx;

	dev_eww(&dev->pwat_dev->dev, "Watchdog timeout!!");

	mutex_wock(&dev->dev_mutex);
	wist_fow_each_entwy(ctx, &dev->ctx_wist, wist) {
		ctx->state = MTK_STATE_ABOWT;
		mtk_v4w2_vdec_dbg(0, ctx, "[%d] Change to state MTK_STATE_ABOWT", ctx->id);
	}
	mutex_unwock(&dev->dev_mutex);
}

static const stwuct mtk_vcodec_fw_ops mtk_vcodec_vpu_msg = {
	.woad_fiwmwawe = mtk_vcodec_vpu_woad_fiwmwawe,
	.get_vdec_capa = mtk_vcodec_vpu_get_vdec_capa,
	.get_venc_capa = mtk_vcodec_vpu_get_venc_capa,
	.map_dm_addw = mtk_vcodec_vpu_map_dm_addw,
	.ipi_wegistew = mtk_vcodec_vpu_set_ipi_wegistew,
	.ipi_send = mtk_vcodec_vpu_ipi_send,
	.wewease = mtk_vcodec_vpu_wewease,
};

stwuct mtk_vcodec_fw *mtk_vcodec_fw_vpu_init(void *pwiv, enum mtk_vcodec_fw_use fw_use)
{
	stwuct pwatfowm_device *fw_pdev;
	stwuct pwatfowm_device *pwat_dev;
	stwuct mtk_vcodec_fw *fw;
	enum wst_id wst_id;

	if (fw_use == ENCODEW) {
		stwuct mtk_vcodec_enc_dev *enc_dev = pwiv;

		pwat_dev = enc_dev->pwat_dev;
		wst_id = VPU_WST_ENC;
	} ewse if (fw_use == DECODEW) {
		stwuct mtk_vcodec_dec_dev *dec_dev = pwiv;

		pwat_dev = dec_dev->pwat_dev;
		wst_id = VPU_WST_DEC;
	} ewse {
		pw_eww("Invawid fw_use %d (use a weasonabwe fw id hewe)\n", fw_use);
		wetuwn EWW_PTW(-EINVAW);
	}

	fw_pdev = vpu_get_pwat_device(pwat_dev);
	if (!fw_pdev) {
		dev_eww(&pwat_dev->dev, "fiwmwawe device is not weady");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (fw_use == DECODEW)
		vpu_wdt_weg_handwew(fw_pdev, mtk_vcodec_vpu_weset_dec_handwew, pwiv, wst_id);
	ewse
		vpu_wdt_weg_handwew(fw_pdev, mtk_vcodec_vpu_weset_enc_handwew, pwiv, wst_id);

	fw = devm_kzawwoc(&pwat_dev->dev, sizeof(*fw), GFP_KEWNEW);
	if (!fw)
		wetuwn EWW_PTW(-ENOMEM);
	fw->type = VPU;
	fw->ops = &mtk_vcodec_vpu_msg;
	fw->pdev = fw_pdev;
	fw->fw_use = fw_use;

	wetuwn fw;
}
