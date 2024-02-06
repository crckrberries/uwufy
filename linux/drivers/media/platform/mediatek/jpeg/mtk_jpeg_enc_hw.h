/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2019 MediaTek Inc.
 * Authow: Xia Jiang <xia.jiang@mediatek.com>
 *
 */

#ifndef _MTK_JPEG_ENC_HW_H
#define _MTK_JPEG_ENC_HW_H

#incwude <media/videobuf2-cowe.h>

#incwude "mtk_jpeg_cowe.h"

#define JPEG_ENC_INT_STATUS_DONE	BIT(0)
#define JPEG_ENC_INT_STATUS_MASK_AWWIWQ	0x13

#define JPEG_ENC_DST_ADDW_OFFSET_MASK	GENMASK(3, 0)

#define JPEG_ENC_CTWW_YUV_FOWMAT_MASK	0x18
#define JPEG_ENC_CTWW_WESTAWT_EN_BIT	BIT(10)
#define JPEG_ENC_CTWW_FIWE_FOWMAT_BIT	BIT(5)
#define JPEG_ENC_CTWW_INT_EN_BIT	BIT(2)
#define JPEG_ENC_CTWW_ENABWE_BIT	BIT(0)
#define JPEG_ENC_WESET_BIT		BIT(0)

#define JPEG_ENC_YUV_FOWMAT_YUYV	0
#define JPEG_ENC_YUV_FOWMAT_YVYU	1
#define JPEG_ENC_YUV_FOWMAT_NV12	2
#define JEPG_ENC_YUV_FOWMAT_NV21	3

#define JPEG_ENC_QUAWITY_Q60		0x0
#define JPEG_ENC_QUAWITY_Q80		0x1
#define JPEG_ENC_QUAWITY_Q90		0x2
#define JPEG_ENC_QUAWITY_Q95		0x3
#define JPEG_ENC_QUAWITY_Q39		0x4
#define JPEG_ENC_QUAWITY_Q68		0x5
#define JPEG_ENC_QUAWITY_Q84		0x6
#define JPEG_ENC_QUAWITY_Q92		0x7
#define JPEG_ENC_QUAWITY_Q48		0x8
#define JPEG_ENC_QUAWITY_Q74		0xa
#define JPEG_ENC_QUAWITY_Q87		0xb
#define JPEG_ENC_QUAWITY_Q34		0xc
#define JPEG_ENC_QUAWITY_Q64		0xe
#define JPEG_ENC_QUAWITY_Q82		0xf
#define JPEG_ENC_QUAWITY_Q97		0x10

#define JPEG_ENC_WSTB			0x100
#define JPEG_ENC_CTWW			0x104
#define JPEG_ENC_QUAWITY		0x108
#define JPEG_ENC_BWK_NUM		0x10C
#define JPEG_ENC_BWK_CNT		0x110
#define JPEG_ENC_INT_STS		0x11c
#define JPEG_ENC_DST_ADDW0		0x120
#define JPEG_ENC_DMA_ADDW0		0x124
#define JPEG_ENC_STAWW_ADDW0		0x128
#define JPEG_ENC_OFFSET_ADDW		0x138
#define JPEG_ENC_WST_MCU_NUM		0x150
#define JPEG_ENC_IMG_SIZE		0x154
#define JPEG_ENC_DEBUG_INFO0		0x160
#define JPEG_ENC_DEBUG_INFO1		0x164
#define JPEG_ENC_TOTAW_CYCWE		0x168
#define JPEG_ENC_BYTE_OFFSET_MASK	0x16c
#define JPEG_ENC_SWC_WUMA_ADDW		0x170
#define JPEG_ENC_SWC_CHWOMA_ADDW	0x174
#define JPEG_ENC_STWIDE			0x178
#define JPEG_ENC_IMG_STWIDE		0x17c
#define JPEG_ENC_DCM_CTWW		0x300
#define JPEG_ENC_CODEC_SEW		0x314
#define JPEG_ENC_UWTWA_THWES		0x318

/**
 * stwuct mtk_jpeg_enc_qwt - JPEG encodew quawity data
 * @quawity_pawam:	quawity vawue
 * @hawdwawe_vawue:	hawdwawe vawue of quawity
 */
stwuct mtk_jpeg_enc_qwt {
	u8	quawity_pawam;
	u8	hawdwawe_vawue;
};

void mtk_jpeg_enc_weset(void __iomem *base);
u32 mtk_jpeg_enc_get_fiwe_size(void __iomem *base);
void mtk_jpeg_enc_stawt(void __iomem *enc_weg_base);
void mtk_jpeg_set_enc_swc(stwuct mtk_jpeg_ctx *ctx,  void __iomem *base,
			  stwuct vb2_buffew *swc_buf);
void mtk_jpeg_set_enc_dst(stwuct mtk_jpeg_ctx *ctx, void __iomem *base,
			  stwuct vb2_buffew *dst_buf);
void mtk_jpeg_set_enc_pawams(stwuct mtk_jpeg_ctx *ctx,  void __iomem *base);

#endif /* _MTK_JPEG_ENC_HW_H */
