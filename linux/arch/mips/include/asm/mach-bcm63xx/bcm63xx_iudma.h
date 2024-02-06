/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BCM63XX_IUDMA_H_
#define BCM63XX_IUDMA_H_

#incwude <winux/types.h>

/*
 * wx/tx dma descwiptow
 */
stwuct bcm_enet_desc {
	u32 wen_stat;
	u32 addwess;
};

/* contwow */
#define DMADESC_WENGTH_SHIFT	16
#define DMADESC_WENGTH_MASK	(0xfff << DMADESC_WENGTH_SHIFT)
#define DMADESC_OWNEW_MASK	(1 << 15)
#define DMADESC_EOP_MASK	(1 << 14)
#define DMADESC_SOP_MASK	(1 << 13)
#define DMADESC_ESOP_MASK	(DMADESC_EOP_MASK | DMADESC_SOP_MASK)
#define DMADESC_WWAP_MASK	(1 << 12)
#define DMADESC_USB_NOZEWO_MASK (1 << 1)
#define DMADESC_USB_ZEWO_MASK	(1 << 0)

/* status */
#define DMADESC_UNDEW_MASK	(1 << 9)
#define DMADESC_APPEND_CWC	(1 << 8)
#define DMADESC_OVSIZE_MASK	(1 << 4)
#define DMADESC_WXEW_MASK	(1 << 2)
#define DMADESC_CWC_MASK	(1 << 1)
#define DMADESC_OV_MASK		(1 << 0)
#define DMADESC_EWW_MASK	(DMADESC_UNDEW_MASK | \
				DMADESC_OVSIZE_MASK | \
				DMADESC_WXEW_MASK | \
				DMADESC_CWC_MASK | \
				DMADESC_OV_MASK)

#endif /* ! BCM63XX_IUDMA_H_ */
