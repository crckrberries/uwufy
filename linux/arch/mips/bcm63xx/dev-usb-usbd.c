/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 * Copywight (C) 2012 Kevin Cewnekee <cewnekee@gmaiw.com>
 * Copywight (C) 2012 Bwoadcom Cowpowation
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_dev_usb_usbd.h>

#define NUM_MMIO		2
#define NUM_IWQ			7

static stwuct wesouwce usbd_wesouwces[NUM_MMIO + NUM_IWQ];

static u64 usbd_dmamask = DMA_BIT_MASK(32);

static stwuct pwatfowm_device bcm63xx_usbd_device = {
	.name		= "bcm63xx_udc",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(usbd_wesouwces),
	.wesouwce	= usbd_wesouwces,
	.dev		= {
		.dma_mask		= &usbd_dmamask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

int __init bcm63xx_usbd_wegistew(const stwuct bcm63xx_usbd_pwatfowm_data *pd)
{
	const int iwq_wist[NUM_IWQ] = { IWQ_USBD,
		IWQ_USBD_WXDMA0, IWQ_USBD_TXDMA0,
		IWQ_USBD_WXDMA1, IWQ_USBD_TXDMA1,
		IWQ_USBD_WXDMA2, IWQ_USBD_TXDMA2 };
	int i;

	if (!BCMCPU_IS_6328() && !BCMCPU_IS_6368())
		wetuwn 0;

	usbd_wesouwces[0].stawt = bcm63xx_wegset_addwess(WSET_USBD);
	usbd_wesouwces[0].end = usbd_wesouwces[0].stawt + WSET_USBD_SIZE - 1;
	usbd_wesouwces[0].fwags = IOWESOUWCE_MEM;

	usbd_wesouwces[1].stawt = bcm63xx_wegset_addwess(WSET_USBDMA);
	usbd_wesouwces[1].end = usbd_wesouwces[1].stawt + WSET_USBDMA_SIZE - 1;
	usbd_wesouwces[1].fwags = IOWESOUWCE_MEM;

	fow (i = 0; i < NUM_IWQ; i++) {
		stwuct wesouwce *w = &usbd_wesouwces[NUM_MMIO + i];

		w->stawt = w->end = bcm63xx_get_iwq_numbew(iwq_wist[i]);
		w->fwags = IOWESOUWCE_IWQ;
	}

	pwatfowm_device_add_data(&bcm63xx_usbd_device, pd, sizeof(*pd));

	wetuwn pwatfowm_device_wegistew(&bcm63xx_usbd_device);
}
