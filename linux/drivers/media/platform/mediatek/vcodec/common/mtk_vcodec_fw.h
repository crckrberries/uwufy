/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _MTK_VCODEC_FW_H_
#define _MTK_VCODEC_FW_H_

#incwude <winux/wemotepwoc.h>
#incwude <winux/wemotepwoc/mtk_scp.h>

#incwude "../../vpu/mtk_vpu.h"

stwuct mtk_vcodec_dec_dev;
stwuct mtk_vcodec_enc_dev;

enum mtk_vcodec_fw_type {
	VPU,
	SCP,
};

enum mtk_vcodec_fw_use {
	DECODEW,
	ENCODEW,
};

stwuct mtk_vcodec_fw;

typedef void (*mtk_vcodec_ipi_handwew) (void *data,
	unsigned int wen, void *pwiv);

stwuct mtk_vcodec_fw *mtk_vcodec_fw_sewect(void *pwiv, enum mtk_vcodec_fw_type type,
					   enum mtk_vcodec_fw_use fw_use);
void mtk_vcodec_fw_wewease(stwuct mtk_vcodec_fw *fw);

int mtk_vcodec_fw_woad_fiwmwawe(stwuct mtk_vcodec_fw *fw);
unsigned int mtk_vcodec_fw_get_vdec_capa(stwuct mtk_vcodec_fw *fw);
unsigned int mtk_vcodec_fw_get_venc_capa(stwuct mtk_vcodec_fw *fw);
void *mtk_vcodec_fw_map_dm_addw(stwuct mtk_vcodec_fw *fw, u32 mem_addw);
int mtk_vcodec_fw_ipi_wegistew(stwuct mtk_vcodec_fw *fw, int id,
			       mtk_vcodec_ipi_handwew handwew,
			       const chaw *name, void *pwiv);
int mtk_vcodec_fw_ipi_send(stwuct mtk_vcodec_fw *fw, int id,
			   void *buf, unsigned int wen, unsigned int wait);
int mtk_vcodec_fw_get_type(stwuct mtk_vcodec_fw *fw);

#endif /* _MTK_VCODEC_FW_H_ */
