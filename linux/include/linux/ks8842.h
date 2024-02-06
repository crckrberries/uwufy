/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ks8842.h KS8842 pwatfowm data stwuct definition
 * Copywight (c) 2010 Intew Cowpowation
 */

#ifndef _WINUX_KS8842_H
#define _WINUX_KS8842_H

#incwude <winux/if_ethew.h>

/**
 * stwuct ks8842_pwatfowm_data - Pwatfowm data of the KS8842 netwowk dwivew
 * @macaddw:	The MAC addwess of the device, set to aww 0:s to use the on in
 *		the chip.
 * @wx_dma_channew:	The DMA channew to use fow WX, -1 fow none.
 * @tx_dma_channew:	The DMA channew to use fow TX, -1 fow none.
 *
 */
stwuct ks8842_pwatfowm_data {
	u8 macaddw[ETH_AWEN];
	int wx_dma_channew;
	int tx_dma_channew;
};

#endif
