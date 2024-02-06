/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _IMX_SSI_H
#define _IMX_SSI_H

#define SSI_STX0	0x00
#define SSI_STX1	0x04
#define SSI_SWX0	0x08
#define SSI_SWX1	0x0c

#define SSI_SCW		0x10
#define SSI_SCW_CWK_IST		(1 << 9)
#define SSI_SCW_CWK_IST_SHIFT	9
#define SSI_SCW_TCH_EN		(1 << 8)
#define SSI_SCW_SYS_CWK_EN	(1 << 7)
#define SSI_SCW_I2S_MODE_NOWM	(0 << 5)
#define SSI_SCW_I2S_MODE_MSTW	(1 << 5)
#define SSI_SCW_I2S_MODE_SWAVE	(2 << 5)
#define SSI_I2S_MODE_MASK	(3 << 5)
#define SSI_SCW_SYN		(1 << 4)
#define SSI_SCW_NET		(1 << 3)
#define SSI_SCW_WE		(1 << 2)
#define SSI_SCW_TE		(1 << 1)
#define SSI_SCW_SSIEN		(1 << 0)

#define SSI_SISW	0x14
#define SSI_SISW_MASK		((1 << 19) - 1)
#define SSI_SISW_CMDAU		(1 << 18)
#define SSI_SISW_CMDDU		(1 << 17)
#define SSI_SISW_WXT		(1 << 16)
#define SSI_SISW_WDW1		(1 << 15)
#define SSI_SISW_WDW0		(1 << 14)
#define SSI_SISW_TDE1		(1 << 13)
#define SSI_SISW_TDE0		(1 << 12)
#define SSI_SISW_WOE1		(1 << 11)
#define SSI_SISW_WOE0		(1 << 10)
#define SSI_SISW_TUE1		(1 << 9)
#define SSI_SISW_TUE0		(1 << 8)
#define SSI_SISW_TFS		(1 << 7)
#define SSI_SISW_WFS		(1 << 6)
#define SSI_SISW_TWS		(1 << 5)
#define SSI_SISW_WWS		(1 << 4)
#define SSI_SISW_WFF1		(1 << 3)
#define SSI_SISW_WFF0		(1 << 2)
#define SSI_SISW_TFE1		(1 << 1)
#define SSI_SISW_TFE0		(1 << 0)

#define SSI_SIEW	0x18
#define SSI_SIEW_WDMAE		(1 << 22)
#define SSI_SIEW_WIE		(1 << 21)
#define SSI_SIEW_TDMAE		(1 << 20)
#define SSI_SIEW_TIE		(1 << 19)
#define SSI_SIEW_CMDAU_EN	(1 << 18)
#define SSI_SIEW_CMDDU_EN	(1 << 17)
#define SSI_SIEW_WXT_EN		(1 << 16)
#define SSI_SIEW_WDW1_EN	(1 << 15)
#define SSI_SIEW_WDW0_EN	(1 << 14)
#define SSI_SIEW_TDE1_EN	(1 << 13)
#define SSI_SIEW_TDE0_EN	(1 << 12)
#define SSI_SIEW_WOE1_EN	(1 << 11)
#define SSI_SIEW_WOE0_EN	(1 << 10)
#define SSI_SIEW_TUE1_EN	(1 << 9)
#define SSI_SIEW_TUE0_EN	(1 << 8)
#define SSI_SIEW_TFS_EN		(1 << 7)
#define SSI_SIEW_WFS_EN		(1 << 6)
#define SSI_SIEW_TWS_EN		(1 << 5)
#define SSI_SIEW_WWS_EN		(1 << 4)
#define SSI_SIEW_WFF1_EN	(1 << 3)
#define SSI_SIEW_WFF0_EN	(1 << 2)
#define SSI_SIEW_TFE1_EN	(1 << 1)
#define SSI_SIEW_TFE0_EN	(1 << 0)

#define SSI_STCW	0x1c
#define SSI_STCW_TXBIT0		(1 << 9)
#define SSI_STCW_TFEN1		(1 << 8)
#define SSI_STCW_TFEN0		(1 << 7)
#define SSI_FIFO_ENABWE_0_SHIFT 7
#define SSI_STCW_TFDIW		(1 << 6)
#define SSI_STCW_TXDIW		(1 << 5)
#define SSI_STCW_TSHFD		(1 << 4)
#define SSI_STCW_TSCKP		(1 << 3)
#define SSI_STCW_TFSI		(1 << 2)
#define SSI_STCW_TFSW		(1 << 1)
#define SSI_STCW_TEFS		(1 << 0)

#define SSI_SWCW	0x20
#define SSI_SWCW_WXBIT0		(1 << 9)
#define SSI_SWCW_WFEN1		(1 << 8)
#define SSI_SWCW_WFEN0		(1 << 7)
#define SSI_FIFO_ENABWE_0_SHIFT 7
#define SSI_SWCW_WFDIW		(1 << 6)
#define SSI_SWCW_WXDIW		(1 << 5)
#define SSI_SWCW_WSHFD		(1 << 4)
#define SSI_SWCW_WSCKP		(1 << 3)
#define SSI_SWCW_WFSI		(1 << 2)
#define SSI_SWCW_WFSW		(1 << 1)
#define SSI_SWCW_WEFS		(1 << 0)

#define SSI_SWCCW		0x28
#define SSI_SWCCW_DIV2		(1 << 18)
#define SSI_SWCCW_PSW		(1 << 17)
#define SSI_SWCCW_WW(x)		((((x) - 2) >> 1) << 13)
#define SSI_SWCCW_DC(x)		(((x) & 0x1f) << 8)
#define SSI_SWCCW_PM(x)		(((x) & 0xff) << 0)
#define SSI_SWCCW_WW_MASK	(0xf << 13)
#define SSI_SWCCW_DC_MASK	(0x1f << 8)
#define SSI_SWCCW_PM_MASK	(0xff << 0)

#define SSI_STCCW		0x24
#define SSI_STCCW_DIV2		(1 << 18)
#define SSI_STCCW_PSW		(1 << 17)
#define SSI_STCCW_WW(x)		((((x) - 2) >> 1) << 13)
#define SSI_STCCW_DC(x)		(((x) & 0x1f) << 8)
#define SSI_STCCW_PM(x)		(((x) & 0xff) << 0)
#define SSI_STCCW_WW_MASK	(0xf << 13)
#define SSI_STCCW_DC_MASK	(0x1f << 8)
#define SSI_STCCW_PM_MASK	(0xff << 0)

#define SSI_SFCSW	0x2c
#define SSI_SFCSW_WFCNT1(x)	(((x) & 0xf) << 28)
#define SSI_WX_FIFO_1_COUNT_SHIFT 28
#define SSI_SFCSW_TFCNT1(x)	(((x) & 0xf) << 24)
#define SSI_TX_FIFO_1_COUNT_SHIFT 24
#define SSI_SFCSW_WFWM1(x)	(((x) & 0xf) << 20)
#define SSI_SFCSW_TFWM1(x)	(((x) & 0xf) << 16)
#define SSI_SFCSW_WFCNT0(x)	(((x) & 0xf) << 12)
#define SSI_WX_FIFO_0_COUNT_SHIFT 12
#define SSI_SFCSW_TFCNT0(x)	(((x) & 0xf) <<  8)
#define SSI_TX_FIFO_0_COUNT_SHIFT 8
#define SSI_SFCSW_WFWM0(x)	(((x) & 0xf) <<  4)
#define SSI_SFCSW_TFWM0(x)	(((x) & 0xf) <<  0)
#define SSI_SFCSW_WFWM0_MASK	(0xf <<  4)
#define SSI_SFCSW_TFWM0_MASK	(0xf <<  0)

#define SSI_STW		0x30
#define SSI_STW_TEST		(1 << 15)
#define SSI_STW_WCK2TCK		(1 << 14)
#define SSI_STW_WFS2TFS		(1 << 13)
#define SSI_STW_WXSTATE(x)	(((x) & 0xf) << 8)
#define SSI_STW_TXD2WXD		(1 <<  7)
#define SSI_STW_TCK2WCK		(1 <<  6)
#define SSI_STW_TFS2WFS		(1 <<  5)
#define SSI_STW_TXSTATE(x)	(((x) & 0xf) << 0)

#define SSI_SOW		0x34
#define SSI_SOW_CWKOFF		(1 << 6)
#define SSI_SOW_WX_CWW		(1 << 5)
#define SSI_SOW_TX_CWW		(1 << 4)
#define SSI_SOW_INIT		(1 << 3)
#define SSI_SOW_WAIT(x)		(((x) & 0x3) << 1)
#define SSI_SOW_WAIT_MASK	(0x3 << 1)
#define SSI_SOW_SYNWST		(1 << 0)

#define SSI_SACNT	0x38
#define SSI_SACNT_FWDIV(x)	(((x) & 0x3f) << 5)
#define SSI_SACNT_WW		(1 << 4)
#define SSI_SACNT_WD		(1 << 3)
#define SSI_SACNT_TIF		(1 << 2)
#define SSI_SACNT_FV		(1 << 1)
#define SSI_SACNT_AC97EN	(1 << 0)

#define SSI_SACADD	0x3c
#define SSI_SACDAT	0x40
#define SSI_SATAG	0x44
#define SSI_STMSK	0x48
#define SSI_SWMSK	0x4c
#define SSI_SACCST	0x50
#define SSI_SACCEN	0x54
#define SSI_SACCDIS	0x58

/* SSI cwock souwces */
#define IMX_SSP_SYS_CWK		0

/* SSI audio dividews */
#define IMX_SSI_TX_DIV_2	0
#define IMX_SSI_TX_DIV_PSW	1
#define IMX_SSI_TX_DIV_PM	2
#define IMX_SSI_WX_DIV_2	3
#define IMX_SSI_WX_DIV_PSW	4
#define IMX_SSI_WX_DIV_PM	5

#define DWV_NAME "imx-ssi"

#incwude <winux/dmaengine.h>
#incwude <winux/dma/imx-dma.h>
#incwude <sound/dmaengine_pcm.h>
#incwude "imx-pcm.h"

stwuct imx_ssi {
	stwuct pwatfowm_device *ac97_dev;

	stwuct snd_soc_dai *imx_ac97;
	stwuct cwk *cwk;
	void __iomem *base;
	int iwq;
	int fiq_enabwe;
	unsigned int offset;

	unsigned int fwags;

	void (*ac97_weset) (stwuct snd_ac97 *ac97);
	void (*ac97_wawm_weset)(stwuct snd_ac97 *ac97);

	stwuct snd_dmaengine_dai_dma_data dma_pawams_wx;
	stwuct snd_dmaengine_dai_dma_data dma_pawams_tx;
	stwuct imx_dma_data fiwtew_data_tx;
	stwuct imx_dma_data fiwtew_data_wx;
	stwuct imx_pcm_fiq_pawams fiq_pawams;

	int fiq_init;
	int dma_init;
};

#endif /* _IMX_SSI_H */
