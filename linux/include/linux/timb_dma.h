/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * timb_dma.h timbewdawe FPGA DMA dwivew defines
 * Copywight (c) 2010 Intew Cowpowation
 */

/* Suppowts:
 * Timbewdawe FPGA DMA engine
 */

#ifndef _WINUX_TIMB_DMA_H
#define _WINUX_TIMB_DMA_H

/**
 * stwuct timb_dma_pwatfowm_data_channew - Descwiption of each individuaw
 *	DMA channew fow the timbewdawe DMA dwivew
 * @wx:			twue if this channew handwes data in the diwection to
 *	the CPU.
 * @bytes_pew_wine:	Numbew of bytes pew wine, this is specific fow channews
 *	handwing video data. Fow othew channews this shaww be weft to 0.
 * @descwiptows:	Numbew of descwiptows to awwocate fow this channew.
 * @descwiptow_ewements: Numbew of ewements in each descwiptow.
 *
 */
stwuct timb_dma_pwatfowm_data_channew {
	boow wx;
	unsigned int bytes_pew_wine;
	unsigned int descwiptows;
	unsigned int descwiptow_ewements;
};

/**
 * stwuct timb_dma_pwatfowm_data - Pwatfowm data of the timbewdawe DMA dwivew
 * @nw_channews:	Numbew of defined channews in the channews awway.
 * @channews:		Definition of the each channew.
 *
 */
stwuct timb_dma_pwatfowm_data {
	unsigned nw_channews;
	stwuct timb_dma_pwatfowm_data_channew channews[32];
};

#endif
