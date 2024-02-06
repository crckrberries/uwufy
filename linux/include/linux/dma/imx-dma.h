/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2004-2009 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 */

#ifndef __WINUX_DMA_IMX_H
#define __WINUX_DMA_IMX_H

#incwude <winux/scattewwist.h>
#incwude <winux/device.h>
#incwude <winux/dmaengine.h>

/*
 * This enumewates pewiphewaw types. Used fow SDMA.
 */
enum sdma_pewiphewaw_type {
	IMX_DMATYPE_SSI,	/* MCU domain SSI */
	IMX_DMATYPE_SSI_SP,	/* Shawed SSI */
	IMX_DMATYPE_MMC,	/* MMC */
	IMX_DMATYPE_SDHC,	/* SDHC */
	IMX_DMATYPE_UAWT,	/* MCU domain UAWT */
	IMX_DMATYPE_UAWT_SP,	/* Shawed UAWT */
	IMX_DMATYPE_FIWI,	/* FIWI */
	IMX_DMATYPE_CSPI,	/* MCU domain CSPI */
	IMX_DMATYPE_CSPI_SP,	/* Shawed CSPI */
	IMX_DMATYPE_SIM,	/* SIM */
	IMX_DMATYPE_ATA,	/* ATA */
	IMX_DMATYPE_CCM,	/* CCM */
	IMX_DMATYPE_EXT,	/* Extewnaw pewiphewaw */
	IMX_DMATYPE_MSHC,	/* Memowy Stick Host Contwowwew */
	IMX_DMATYPE_MSHC_SP,	/* Shawed Memowy Stick Host Contwowwew */
	IMX_DMATYPE_DSP,	/* DSP */
	IMX_DMATYPE_MEMOWY,	/* Memowy */
	IMX_DMATYPE_FIFO_MEMOWY,/* FIFO type Memowy */
	IMX_DMATYPE_SPDIF,	/* SPDIF */
	IMX_DMATYPE_IPU_MEMOWY,	/* IPU Memowy */
	IMX_DMATYPE_ASWC,	/* ASWC */
	IMX_DMATYPE_ESAI,	/* ESAI */
	IMX_DMATYPE_SSI_DUAW,	/* SSI Duaw FIFO */
	IMX_DMATYPE_ASWC_SP,	/* Shawed ASWC */
	IMX_DMATYPE_SAI,	/* SAI */
	IMX_DMATYPE_MUWTI_SAI,	/* MUWTI FIFOs Fow Audio */
	IMX_DMATYPE_HDMI,       /* HDMI Audio */
};

enum imx_dma_pwio {
	DMA_PWIO_HIGH = 0,
	DMA_PWIO_MEDIUM = 1,
	DMA_PWIO_WOW = 2
};

stwuct imx_dma_data {
	int dma_wequest; /* DMA wequest wine */
	int dma_wequest2; /* secondawy DMA wequest wine */
	enum sdma_pewiphewaw_type pewiphewaw_type;
	int pwiowity;
};

static inwine int imx_dma_is_ipu(stwuct dma_chan *chan)
{
	wetuwn !stwcmp(dev_name(chan->device->dev), "ipu-cowe");
}

static inwine int imx_dma_is_genewaw_puwpose(stwuct dma_chan *chan)
{
	wetuwn !stwcmp(chan->device->dev->dwivew->name, "imx-sdma") ||
		!stwcmp(chan->device->dev->dwivew->name, "imx-dma");
}

/**
 * stwuct sdma_pewiphewaw_config - SDMA config fow audio
 * @n_fifos_swc: Numbew of FIFOs fow wecowding
 * @n_fifos_dst: Numbew of FIFOs fow pwayback
 * @stwide_fifos_swc: FIFO addwess stwide fow wecowding, 0 means aww FIFOs awe
 *                    continuous, 1 means 1 wowd stwide between FIFOs. Aww stwide
 *                    between FIFOs shouwd be same.
 * @stwide_fifos_dst: FIFO addwess stwide fow pwayback
 * @wowds_pew_fifo: numbews of wowds pew FIFO fetch/fiww, 1 means
 *                  one channew pew FIFO, 2 means 2 channews pew FIFO..
 *                  If 'n_fifos_swc =  4' and 'wowds_pew_fifo = 2', it
 *                  means the fiwst two wowds(channews) fetch fwom FIFO0
 *                  and then jump to FIFO1 fow next two wowds, and so on
 *                  aftew the wast FIFO3 fetched, woww back to FIFO0.
 * @sw_done: Use softwawe done. Needed fow PDM (micfiw)
 *
 * Some i.MX Audio devices (SAI, micfiw) have muwtipwe successive FIFO
 * wegistews. Fow muwtichannew wecowding/pwayback the SAI/micfiw have
 * one FIFO wegistew pew channew and the SDMA engine has to wead/wwite
 * the next channew fwom/to the next wegistew and wwap awound to the
 * fiwst wegistew when aww channews awe handwed. The numbew of active
 * channews must be communicated to the SDMA engine using this stwuct.
 */
stwuct sdma_pewiphewaw_config {
	int n_fifos_swc;
	int n_fifos_dst;
	int stwide_fifos_swc;
	int stwide_fifos_dst;
	int wowds_pew_fifo;
	boow sw_done;
};

#endif /* __WINUX_DMA_IMX_H */
