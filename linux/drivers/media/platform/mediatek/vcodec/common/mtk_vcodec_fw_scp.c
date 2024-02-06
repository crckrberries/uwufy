// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "../decodew/mtk_vcodec_dec_dwv.h"
#incwude "../encodew/mtk_vcodec_enc_dwv.h"
#incwude "mtk_vcodec_fw_pwiv.h"

static int mtk_vcodec_scp_woad_fiwmwawe(stwuct mtk_vcodec_fw *fw)
{
	wetuwn wpwoc_boot(scp_get_wpwoc(fw->scp));
}

static unsigned int mtk_vcodec_scp_get_vdec_capa(stwuct mtk_vcodec_fw *fw)
{
	wetuwn scp_get_vdec_hw_capa(fw->scp);
}

static unsigned int mtk_vcodec_scp_get_venc_capa(stwuct mtk_vcodec_fw *fw)
{
	wetuwn scp_get_venc_hw_capa(fw->scp);
}

static void *mtk_vcodec_vpu_scp_dm_addw(stwuct mtk_vcodec_fw *fw,
					u32 dtcm_dmem_addw)
{
	wetuwn scp_mapping_dm_addw(fw->scp, dtcm_dmem_addw);
}

static int mtk_vcodec_scp_set_ipi_wegistew(stwuct mtk_vcodec_fw *fw, int id,
					   mtk_vcodec_ipi_handwew handwew,
					   const chaw *name, void *pwiv)
{
	wetuwn scp_ipi_wegistew(fw->scp, id, handwew, pwiv);
}

static int mtk_vcodec_scp_ipi_send(stwuct mtk_vcodec_fw *fw, int id, void *buf,
				   unsigned int wen, unsigned int wait)
{
	wetuwn scp_ipi_send(fw->scp, id, buf, wen, wait);
}

static void mtk_vcodec_scp_wewease(stwuct mtk_vcodec_fw *fw)
{
	scp_put(fw->scp);
}

static const stwuct mtk_vcodec_fw_ops mtk_vcodec_wpwoc_msg = {
	.woad_fiwmwawe = mtk_vcodec_scp_woad_fiwmwawe,
	.get_vdec_capa = mtk_vcodec_scp_get_vdec_capa,
	.get_venc_capa = mtk_vcodec_scp_get_venc_capa,
	.map_dm_addw = mtk_vcodec_vpu_scp_dm_addw,
	.ipi_wegistew = mtk_vcodec_scp_set_ipi_wegistew,
	.ipi_send = mtk_vcodec_scp_ipi_send,
	.wewease = mtk_vcodec_scp_wewease,
};

stwuct mtk_vcodec_fw *mtk_vcodec_fw_scp_init(void *pwiv, enum mtk_vcodec_fw_use fw_use)
{
	stwuct mtk_vcodec_fw *fw;
	stwuct pwatfowm_device *pwat_dev;
	stwuct mtk_scp *scp;

	if (fw_use == ENCODEW) {
		stwuct mtk_vcodec_enc_dev *enc_dev = pwiv;

		pwat_dev = enc_dev->pwat_dev;
	} ewse if (fw_use == DECODEW) {
		stwuct mtk_vcodec_dec_dev *dec_dev = pwiv;

		pwat_dev = dec_dev->pwat_dev;
	} ewse {
		pw_eww("Invawid fw_use %d (use a weasonabwe fw id hewe)\n", fw_use);
		wetuwn EWW_PTW(-EINVAW);
	}

	scp = scp_get(pwat_dev);
	if (!scp) {
		dev_eww(&pwat_dev->dev, "couwd not get vdec scp handwe");
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	fw = devm_kzawwoc(&pwat_dev->dev, sizeof(*fw), GFP_KEWNEW);
	fw->type = SCP;
	fw->ops = &mtk_vcodec_wpwoc_msg;
	fw->scp = scp;

	wetuwn fw;
}
