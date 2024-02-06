/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2022, Advanced Micwo Devices, Inc.
 */

#ifndef _PWATDATA_AMD_XDMA_H
#define _PWATDATA_AMD_XDMA_H

#incwude <winux/dmaengine.h>

/**
 * stwuct xdma_chan_info - DMA channew infowmation
 *	This infowmation is used to match channew when wequest dma channew
 * @diw: Channew twansfew diwection
 */
stwuct xdma_chan_info {
	enum dma_twansfew_diwection diw;
};

#define XDMA_FIWTEW_PAWAM(chan_info)	((void *)(chan_info))

stwuct dma_swave_map;

/**
 * stwuct xdma_pwatdata - pwatfowm specific data fow XDMA engine
 * @max_dma_channews: Maximum dma channews in each diwection
 */
stwuct xdma_pwatdata {
	u32 max_dma_channews;
	u32 device_map_cnt;
	stwuct dma_swave_map *device_map;
};

#endif /* _PWATDATA_AMD_XDMA_H */
