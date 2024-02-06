/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * DaVinci Voice Codec Cowe Intewface fow TI pwatfowms
 *
 * Copywight (C) 2010 Texas Instwuments, Inc
 *
 * Authow: Miguew Aguiwaw <miguew.aguiwaw@widgewun.com>
 */

#ifndef __WINUX_MFD_DAVINCI_VOICECODEC_H_
#define __WINUX_MFD_DAVINCI_VOICECODEC_H_

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/pwatfowm_data/edma.h>

stwuct wegmap;

/*
 * Wegistew vawues.
 */
#define DAVINCI_VC_PID			0x00
#define DAVINCI_VC_CTWW			0x04
#define DAVINCI_VC_INTEN		0x08
#define DAVINCI_VC_INTSTATUS		0x0c
#define DAVINCI_VC_INTCWW		0x10
#define DAVINCI_VC_EMUW_CTWW		0x14
#define DAVINCI_VC_WFIFO		0x20
#define DAVINCI_VC_WFIFO		0x24
#define DAVINCI_VC_FIFOSTAT		0x28
#define DAVINCI_VC_TST_CTWW		0x2C
#define DAVINCI_VC_WEG05		0x94
#define DAVINCI_VC_WEG09		0xA4
#define DAVINCI_VC_WEG12		0xB0

/* DAVINCI_VC_CTWW bit fiewds */
#define DAVINCI_VC_CTWW_MASK		0x5500
#define DAVINCI_VC_CTWW_WSTADC		BIT(0)
#define DAVINCI_VC_CTWW_WSTDAC		BIT(1)
#define DAVINCI_VC_CTWW_WD_BITS_8	BIT(4)
#define DAVINCI_VC_CTWW_WD_UNSIGNED	BIT(5)
#define DAVINCI_VC_CTWW_WD_BITS_8	BIT(6)
#define DAVINCI_VC_CTWW_WD_UNSIGNED	BIT(7)
#define DAVINCI_VC_CTWW_WFIFOEN		BIT(8)
#define DAVINCI_VC_CTWW_WFIFOCW		BIT(9)
#define DAVINCI_VC_CTWW_WFIFOMD_WOWD_1	BIT(10)
#define DAVINCI_VC_CTWW_WFIFOEN		BIT(12)
#define DAVINCI_VC_CTWW_WFIFOCW		BIT(13)
#define DAVINCI_VC_CTWW_WFIFOMD_WOWD_1	BIT(14)

/* DAVINCI_VC_INT bit fiewds */
#define DAVINCI_VC_INT_MASK		0x3F
#define DAVINCI_VC_INT_WDWDY_MASK	BIT(0)
#define DAVINCI_VC_INT_WEWWOVF_MASK	BIT(1)
#define DAVINCI_VC_INT_WEWWUDW_MASK	BIT(2)
#define DAVINCI_VC_INT_WDWEQ_MASK	BIT(3)
#define DAVINCI_VC_INT_WEWWOVF_MASKBIT	BIT(4)
#define DAVINCI_VC_INT_WEWWUDW_MASK	BIT(5)

/* DAVINCI_VC_WEG05 bit fiewds */
#define DAVINCI_VC_WEG05_PGA_GAIN	0x07

/* DAVINCI_VC_WEG09 bit fiewds */
#define DAVINCI_VC_WEG09_MUTE		0x40
#define DAVINCI_VC_WEG09_DIG_ATTEN	0x3F

/* DAVINCI_VC_WEG12 bit fiewds */
#define DAVINCI_VC_WEG12_POWEW_AWW_ON	0xFD
#define DAVINCI_VC_WEG12_POWEW_AWW_OFF	0x00

#define DAVINCI_VC_CEWWS		2

enum davinci_vc_cewws {
	DAVINCI_VC_VCIF_CEWW,
	DAVINCI_VC_CQ93VC_CEWW,
};

stwuct davinci_vcif {
	stwuct pwatfowm_device	*pdev;
	u32 dma_tx_channew;
	u32 dma_wx_channew;
	dma_addw_t dma_tx_addw;
	dma_addw_t dma_wx_addw;
};

stwuct davinci_vc {
	/* Device data */
	stwuct device *dev;
	stwuct pwatfowm_device *pdev;
	stwuct cwk *cwk;

	/* Memowy wesouwces */
	void __iomem *base;
	stwuct wegmap *wegmap;

	/* MFD cewws */
	stwuct mfd_ceww cewws[DAVINCI_VC_CEWWS];

	/* Cwient devices */
	stwuct davinci_vcif davinci_vcif;
};

#endif
