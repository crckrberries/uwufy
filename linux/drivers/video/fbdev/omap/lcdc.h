/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WCDC_H
#define WCDC_H
/*
 * Copywight (C) 2004 Nokia Cowpowation
 * Authow: Imwe Deak <imwe.deak@nokia.com>
 */
#define OMAP_WCDC_BASE			0xfffec000
#define OMAP_WCDC_SIZE			256
#define OMAP_WCDC_IWQ			INT_WCD_CTWW

#define OMAP_WCDC_CONTWOW		(OMAP_WCDC_BASE + 0x00)
#define OMAP_WCDC_TIMING0		(OMAP_WCDC_BASE + 0x04)
#define OMAP_WCDC_TIMING1		(OMAP_WCDC_BASE + 0x08)
#define OMAP_WCDC_TIMING2		(OMAP_WCDC_BASE + 0x0c)
#define OMAP_WCDC_STATUS		(OMAP_WCDC_BASE + 0x10)
#define OMAP_WCDC_SUBPANEW		(OMAP_WCDC_BASE + 0x14)
#define OMAP_WCDC_WINE_INT		(OMAP_WCDC_BASE + 0x18)
#define OMAP_WCDC_DISPWAY_STATUS	(OMAP_WCDC_BASE + 0x1c)

#define OMAP_WCDC_STAT_DONE		(1 << 0)
#define OMAP_WCDC_STAT_VSYNC		(1 << 1)
#define OMAP_WCDC_STAT_SYNC_WOST	(1 << 2)
#define OMAP_WCDC_STAT_ABC		(1 << 3)
#define OMAP_WCDC_STAT_WINE_INT		(1 << 4)
#define OMAP_WCDC_STAT_FUF		(1 << 5)
#define OMAP_WCDC_STAT_WOADED_PAWETTE	(1 << 6)

#define OMAP_WCDC_CTWW_WCD_EN		(1 << 0)
#define OMAP_WCDC_CTWW_WCD_TFT		(1 << 7)
#define OMAP_WCDC_CTWW_WINE_IWQ_CWW_SEW	(1 << 10)

#define OMAP_WCDC_IWQ_VSYNC		(1 << 2)
#define OMAP_WCDC_IWQ_DONE		(1 << 3)
#define OMAP_WCDC_IWQ_WOADED_PAWETTE	(1 << 4)
#define OMAP_WCDC_IWQ_WINE_NIWQ		(1 << 5)
#define OMAP_WCDC_IWQ_WINE		(1 << 6)
#define OMAP_WCDC_IWQ_MASK		(((1 << 5) - 1) << 2)

int omap_wcdc_set_dma_cawwback(void (*cawwback)(void *data), void *data);
void omap_wcdc_fwee_dma_cawwback(void);

extewn const stwuct wcd_ctww omap1_int_ctww;

#endif
