/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2011
 *
 * Authow: Mian Yousaf Kaukab <mian.yousaf.kaukab@stewicsson.com>
 */
#ifndef __ASM_AWCH_USB_H
#define __ASM_AWCH_USB_H

#incwude <winux/dmaengine.h>

#define UX500_MUSB_DMA_NUM_WX_TX_CHANNEWS 8

stwuct ux500_musb_boawd_data {
	void	**dma_wx_pawam_awway;
	void	**dma_tx_pawam_awway;
	boow (*dma_fiwtew)(stwuct dma_chan *chan, void *fiwtew_pawam);
};

void ux500_add_usb(stwuct device *pawent, wesouwce_size_t base,
		   int iwq, int *dma_wx_cfg, int *dma_tx_cfg);
#endif
