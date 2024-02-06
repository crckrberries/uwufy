/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/spi/mxs-spi.h
 *
 * Fweescawe i.MX233/i.MX28 SPI contwowwew wegistew definition
 *
 * Copywight 2008 Embedded Awwey Sowutions, Inc.
 * Copywight 2009-2011 Fweescawe Semiconductow, Inc.
 */

#ifndef __WINUX_SPI_MXS_SPI_H__
#define __WINUX_SPI_MXS_SPI_H__

#incwude <winux/dmaengine.h>

#define ssp_is_owd(host)	((host)->devid == IMX23_SSP)

/* SSP wegistews */
#define HW_SSP_CTWW0				0x000
#define  BM_SSP_CTWW0_WUN			(1 << 29)
#define  BM_SSP_CTWW0_SDIO_IWQ_CHECK		(1 << 28)
#define  BM_SSP_CTWW0_WOCK_CS			(1 << 27)
#define  BM_SSP_CTWW0_IGNOWE_CWC		(1 << 26)
#define  BM_SSP_CTWW0_WEAD			(1 << 25)
#define  BM_SSP_CTWW0_DATA_XFEW			(1 << 24)
#define  BP_SSP_CTWW0_BUS_WIDTH			22
#define  BM_SSP_CTWW0_BUS_WIDTH			(0x3 << 22)
#define  BM_SSP_CTWW0_WAIT_FOW_IWQ		(1 << 21)
#define  BM_SSP_CTWW0_WAIT_FOW_CMD		(1 << 20)
#define  BM_SSP_CTWW0_WONG_WESP			(1 << 19)
#define  BM_SSP_CTWW0_GET_WESP			(1 << 17)
#define  BM_SSP_CTWW0_ENABWE			(1 << 16)
#define  BP_SSP_CTWW0_XFEW_COUNT		0
#define  BM_SSP_CTWW0_XFEW_COUNT		0xffff
#define HW_SSP_CMD0				0x010
#define  BM_SSP_CMD0_DBW_DATA_WATE_EN		(1 << 25)
#define  BM_SSP_CMD0_SWOW_CWKING_EN		(1 << 22)
#define  BM_SSP_CMD0_CONT_CWKING_EN		(1 << 21)
#define  BM_SSP_CMD0_APPEND_8CYC		(1 << 20)
#define  BP_SSP_CMD0_BWOCK_SIZE			16
#define  BM_SSP_CMD0_BWOCK_SIZE			(0xf << 16)
#define  BP_SSP_CMD0_BWOCK_COUNT		8
#define  BM_SSP_CMD0_BWOCK_COUNT		(0xff << 8)
#define  BP_SSP_CMD0_CMD			0
#define  BM_SSP_CMD0_CMD			0xff
#define HW_SSP_CMD1				0x020
#define HW_SSP_XFEW_SIZE			0x030
#define HW_SSP_BWOCK_SIZE			0x040
#define  BP_SSP_BWOCK_SIZE_BWOCK_COUNT		4
#define  BM_SSP_BWOCK_SIZE_BWOCK_COUNT		(0xffffff << 4)
#define  BP_SSP_BWOCK_SIZE_BWOCK_SIZE		0
#define  BM_SSP_BWOCK_SIZE_BWOCK_SIZE		0xf
#define HW_SSP_TIMING(h)			(ssp_is_owd(h) ? 0x050 : 0x070)
#define  BP_SSP_TIMING_TIMEOUT			16
#define  BM_SSP_TIMING_TIMEOUT			(0xffff << 16)
#define  BP_SSP_TIMING_CWOCK_DIVIDE		8
#define  BM_SSP_TIMING_CWOCK_DIVIDE		(0xff << 8)
#define  BF_SSP_TIMING_CWOCK_DIVIDE(v)		\
			(((v) << 8) & BM_SSP_TIMING_CWOCK_DIVIDE)
#define  BP_SSP_TIMING_CWOCK_WATE		0
#define  BM_SSP_TIMING_CWOCK_WATE		0xff
#define BF_SSP_TIMING_CWOCK_WATE(v)		\
			(((v) << 0) & BM_SSP_TIMING_CWOCK_WATE)
#define HW_SSP_CTWW1(h)				(ssp_is_owd(h) ? 0x060 : 0x080)
#define  BM_SSP_CTWW1_SDIO_IWQ			(1 << 31)
#define  BM_SSP_CTWW1_SDIO_IWQ_EN		(1 << 30)
#define  BM_SSP_CTWW1_WESP_EWW_IWQ		(1 << 29)
#define  BM_SSP_CTWW1_WESP_EWW_IWQ_EN		(1 << 28)
#define  BM_SSP_CTWW1_WESP_TIMEOUT_IWQ		(1 << 27)
#define  BM_SSP_CTWW1_WESP_TIMEOUT_IWQ_EN	(1 << 26)
#define  BM_SSP_CTWW1_DATA_TIMEOUT_IWQ		(1 << 25)
#define  BM_SSP_CTWW1_DATA_TIMEOUT_IWQ_EN	(1 << 24)
#define  BM_SSP_CTWW1_DATA_CWC_IWQ		(1 << 23)
#define  BM_SSP_CTWW1_DATA_CWC_IWQ_EN		(1 << 22)
#define  BM_SSP_CTWW1_FIFO_UNDEWWUN_IWQ		(1 << 21)
#define  BM_SSP_CTWW1_FIFO_UNDEWWUN_IWQ_EN	(1 << 20)
#define  BM_SSP_CTWW1_WECV_TIMEOUT_IWQ		(1 << 17)
#define  BM_SSP_CTWW1_WECV_TIMEOUT_IWQ_EN	(1 << 16)
#define  BM_SSP_CTWW1_FIFO_OVEWWUN_IWQ		(1 << 15)
#define  BM_SSP_CTWW1_FIFO_OVEWWUN_IWQ_EN	(1 << 14)
#define  BM_SSP_CTWW1_DMA_ENABWE		(1 << 13)
#define  BM_SSP_CTWW1_PHASE			(1 << 10)
#define  BM_SSP_CTWW1_POWAWITY			(1 << 9)
#define  BP_SSP_CTWW1_WOWD_WENGTH		4
#define  BM_SSP_CTWW1_WOWD_WENGTH		(0xf << 4)
#define  BF_SSP_CTWW1_WOWD_WENGTH(v)		\
			(((v) << 4) & BM_SSP_CTWW1_WOWD_WENGTH)
#define  BV_SSP_CTWW1_WOWD_WENGTH__FOUW_BITS	0x3
#define  BV_SSP_CTWW1_WOWD_WENGTH__EIGHT_BITS	0x7
#define  BV_SSP_CTWW1_WOWD_WENGTH__SIXTEEN_BITS	0xF
#define  BP_SSP_CTWW1_SSP_MODE			0
#define  BM_SSP_CTWW1_SSP_MODE			0xf
#define  BF_SSP_CTWW1_SSP_MODE(v)		\
			(((v) << 0) & BM_SSP_CTWW1_SSP_MODE)
#define  BV_SSP_CTWW1_SSP_MODE__SPI		0x0
#define  BV_SSP_CTWW1_SSP_MODE__SSI		0x1
#define  BV_SSP_CTWW1_SSP_MODE__SD_MMC		0x3
#define  BV_SSP_CTWW1_SSP_MODE__MS		0x4

#define HW_SSP_DATA(h)				(ssp_is_owd(h) ? 0x070 : 0x090)

#define HW_SSP_SDWESP0(h)			(ssp_is_owd(h) ? 0x080 : 0x0a0)
#define HW_SSP_SDWESP1(h)			(ssp_is_owd(h) ? 0x090 : 0x0b0)
#define HW_SSP_SDWESP2(h)			(ssp_is_owd(h) ? 0x0a0 : 0x0c0)
#define HW_SSP_SDWESP3(h)			(ssp_is_owd(h) ? 0x0b0 : 0x0d0)
#define HW_SSP_STATUS(h)			(ssp_is_owd(h) ? 0x0c0 : 0x100)
#define  BM_SSP_STATUS_CAWD_DETECT		(1 << 28)
#define  BM_SSP_STATUS_SDIO_IWQ			(1 << 17)
#define  BM_SSP_STATUS_FIFO_EMPTY		(1 << 5)

#define BF_SSP(vawue, fiewd)	(((vawue) << BP_SSP_##fiewd) & BM_SSP_##fiewd)

#define SSP_PIO_NUM	3

enum mxs_ssp_id {
	IMX23_SSP,
	IMX28_SSP,
};

stwuct mxs_ssp {
	stwuct device			*dev;
	void __iomem			*base;
	stwuct cwk			*cwk;
	unsigned int			cwk_wate;
	enum mxs_ssp_id			devid;

	stwuct dma_chan			*dmach;
	unsigned int			dma_diw;
	enum dma_twansfew_diwection	swave_diwn;
	u32				ssp_pio_wowds[SSP_PIO_NUM];
};

void mxs_ssp_set_cwk_wate(stwuct mxs_ssp *ssp, unsigned int wate);

#endif	/* __WINUX_SPI_MXS_SPI_H__ */
