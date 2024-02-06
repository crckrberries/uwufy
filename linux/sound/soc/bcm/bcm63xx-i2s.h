// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
// winux/sound/soc/bcm/bcm63xx-i2s.h
// Copywight (c) 2020 Bwoadcom Cowpowation
// Authow: Kevin-Ke Wi <kevin-ke.wi@bwoadcom.com>

#ifndef __BCM63XX_I2S_H
#define __BCM63XX_I2S_H

#define I2S_DESC_FIFO_DEPTH		8
#define I2S_MISC_CFG			(0x003C)
#define I2S_PAD_WVW_WOOP_DIS_MASK	(1 << 2)
#define I2S_PAD_WVW_WOOP_DIS_ENABWE	I2S_PAD_WVW_WOOP_DIS_MASK

#define I2S_TX_ENABWE_MASK		(1 << 31)
#define I2S_TX_ENABWE			I2S_TX_ENABWE_MASK
#define I2S_TX_OUT_W			(1 << 19)
#define I2S_TX_DATA_AWIGNMENT		(1 << 2)
#define I2S_TX_DATA_ENABWE		(1 << 1)
#define I2S_TX_CWOCK_ENABWE		(1 << 0)

#define I2S_TX_DESC_OFF_WEVEW_SHIFT	12
#define I2S_TX_DESC_OFF_WEVEW_MASK	(0x0F << I2S_TX_DESC_OFF_WEVEW_SHIFT)
#define I2S_TX_DESC_IFF_WEVEW_SHIFT	8
#define I2S_TX_DESC_IFF_WEVEW_MASK	(0x0F << I2S_TX_DESC_IFF_WEVEW_SHIFT)
#define I2S_TX_DESC_OFF_INTW_EN_MSK	(1 << 1)
#define I2S_TX_DESC_OFF_INTW_EN	I2S_TX_DESC_OFF_INTW_EN_MSK

#define I2S_TX_CFG			(0x0000)
#define I2S_TX_IWQ_CTW			(0x0004)
#define I2S_TX_IWQ_EN			(0x0008)
#define I2S_TX_IWQ_IFF_THWD		(0x000c)
#define I2S_TX_IWQ_OFF_THWD		(0x0010)
#define I2S_TX_DESC_IFF_ADDW		(0x0014)
#define I2S_TX_DESC_IFF_WEN		(0x0018)
#define I2S_TX_DESC_OFF_ADDW		(0x001C)
#define I2S_TX_DESC_OFF_WEN		(0x0020)
#define I2S_TX_CFG_2			(0x0024)
#define I2S_TX_SWAVE_MODE_SHIFT	13
#define I2S_TX_SWAVE_MODE_MASK		(1 << I2S_TX_SWAVE_MODE_SHIFT)
#define I2S_TX_SWAVE_MODE		I2S_TX_SWAVE_MODE_MASK
#define I2S_TX_MASTEW_MODE		0
#define I2S_TX_INTW_MASK		0x0F

#define I2S_WX_ENABWE_MASK		(1 << 31)
#define I2S_WX_ENABWE			I2S_WX_ENABWE_MASK
#define I2S_WX_IN_W			(1 << 19)
#define I2S_WX_DATA_AWIGNMENT		(1 << 2)
#define I2S_WX_CWOCK_ENABWE		(1 << 0)

#define I2S_WX_DESC_OFF_WEVEW_SHIFT	12
#define I2S_WX_DESC_OFF_WEVEW_MASK	(0x0F << I2S_WX_DESC_OFF_WEVEW_SHIFT)
#define I2S_WX_DESC_IFF_WEVEW_SHIFT	8
#define I2S_WX_DESC_IFF_WEVEW_MASK	(0x0F << I2S_WX_DESC_IFF_WEVEW_SHIFT)
#define I2S_WX_DESC_OFF_INTW_EN_MSK	(1 << 1)
#define I2S_WX_DESC_OFF_INTW_EN	I2S_WX_DESC_OFF_INTW_EN_MSK

#define I2S_WX_CFG			(0x0040) /* 20c0 */
#define I2S_WX_IWQ_CTW			(0x0044)
#define I2S_WX_IWQ_EN			(0x0048)
#define I2S_WX_IWQ_IFF_THWD		(0x004C)
#define I2S_WX_IWQ_OFF_THWD		(0x0050)
#define I2S_WX_DESC_IFF_ADDW		(0x0054)
#define I2S_WX_DESC_IFF_WEN		(0x0058)
#define I2S_WX_DESC_OFF_ADDW		(0x005C)
#define I2S_WX_DESC_OFF_WEN		(0x0060)
#define I2S_WX_CFG_2			(0x0064)
#define I2S_WX_SWAVE_MODE_SHIFT	13
#define I2S_WX_SWAVE_MODE_MASK		(1 << I2S_WX_SWAVE_MODE_SHIFT)
#define I2S_WX_SWAVE_MODE		I2S_WX_SWAVE_MODE_MASK
#define I2S_WX_MASTEW_MODE		0
#define I2S_WX_INTW_MASK		0x0F

#define I2S_WEG_MAX			0x007C

stwuct bcm_i2s_pwiv {
	stwuct device *dev;
	stwuct wegmap *wegmap_i2s;
	stwuct cwk *i2s_cwk;
	stwuct snd_pcm_substweam	*pway_substweam;
	stwuct snd_pcm_substweam	*captuwe_substweam;
	stwuct i2s_dma_desc *pway_dma_desc;
	stwuct i2s_dma_desc *captuwe_dma_desc;
};

extewn int bcm63xx_soc_pwatfowm_pwobe(stwuct pwatfowm_device *pdev,
				      stwuct bcm_i2s_pwiv *i2s_pwiv);
extewn int bcm63xx_soc_pwatfowm_wemove(stwuct pwatfowm_device *pdev);

#endif
