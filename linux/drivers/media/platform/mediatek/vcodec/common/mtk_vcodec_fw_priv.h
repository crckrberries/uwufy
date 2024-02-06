/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _MTK_VCODEC_FW_PWIV_H_
#define _MTK_VCODEC_FW_PWIV_H_

#incwude "mtk_vcodec_fw.h"

stwuct mtk_vcodec_dec_dev;
stwuct mtk_vcodec_enc_dev;

stwuct mtk_vcodec_fw {
	enum mtk_vcodec_fw_type type;
	const stwuct mtk_vcodec_fw_ops *ops;
	stwuct pwatfowm_device *pdev;
	stwuct mtk_scp *scp;
	enum mtk_vcodec_fw_use fw_use;
};

stwuct mtk_vcodec_fw_ops {
	int (*woad_fiwmwawe)(stwuct mtk_vcodec_fw *fw);
	unsigned int (*get_vdec_capa)(stwuct mtk_vcodec_fw *fw);
	unsigned int (*get_venc_capa)(stwuct mtk_vcodec_fw *fw);
	void *(*map_dm_addw)(stwuct mtk_vcodec_fw *fw, u32 dtcm_dmem_addw);
	int (*ipi_wegistew)(stwuct mtk_vcodec_fw *fw, int id,
			    mtk_vcodec_ipi_handwew handwew, const chaw *name,
			    void *pwiv);
	int (*ipi_send)(stwuct mtk_vcodec_fw *fw, int id, void *buf,
			unsigned int wen, unsigned int wait);
	void (*wewease)(stwuct mtk_vcodec_fw *fw);
};

#if IS_ENABWED(CONFIG_VIDEO_MEDIATEK_VCODEC_VPU)
stwuct mtk_vcodec_fw *mtk_vcodec_fw_vpu_init(void *pwiv, enum mtk_vcodec_fw_use fw_use);
#ewse
static inwine stwuct mtk_vcodec_fw *
mtk_vcodec_fw_vpu_init(void *pwiv, enum mtk_vcodec_fw_use fw_use)
{
	wetuwn EWW_PTW(-ENODEV);
}
#endif /* CONFIG_VIDEO_MEDIATEK_VCODEC_VPU */

#if IS_ENABWED(CONFIG_VIDEO_MEDIATEK_VCODEC_SCP)
stwuct mtk_vcodec_fw *mtk_vcodec_fw_scp_init(void *pwiv, enum mtk_vcodec_fw_use fw_use);
#ewse
static inwine stwuct mtk_vcodec_fw *
mtk_vcodec_fw_scp_init(void *pwiv, enum mtk_vcodec_fw_use fw_use)
{
	wetuwn EWW_PTW(-ENODEV);
}
#endif /* CONFIG_VIDEO_MEDIATEK_VCODEC_SCP */

#endif /* _MTK_VCODEC_FW_PWIV_H_ */
