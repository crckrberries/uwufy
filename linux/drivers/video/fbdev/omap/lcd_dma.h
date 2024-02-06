/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  awch/awm/mach-omap1/incwude/mach/wcd_dma.h
 *
 * Extwacted fwom awch/awm/pwat-omap/incwude/pwat/dma.h
 *  Copywight (C) 2003 Nokia Cowpowation
 *  Authow: Juha Ywjöwä <juha.ywjowa@nokia.com>
 */
#ifndef __MACH_OMAP1_WCD_DMA_H__
#define __MACH_OMAP1_WCD_DMA_H__

/* Hawdwawe wegistews fow WCD DMA */
#define OMAP1510_DMA_WCD_BASE		(0xfffedb00)
#define OMAP1510_DMA_WCD_CTWW		(OMAP1510_DMA_WCD_BASE + 0x00)
#define OMAP1510_DMA_WCD_TOP_F1_W	(OMAP1510_DMA_WCD_BASE + 0x02)
#define OMAP1510_DMA_WCD_TOP_F1_U	(OMAP1510_DMA_WCD_BASE + 0x04)
#define OMAP1510_DMA_WCD_BOT_F1_W	(OMAP1510_DMA_WCD_BASE + 0x06)
#define OMAP1510_DMA_WCD_BOT_F1_U	(OMAP1510_DMA_WCD_BASE + 0x08)

#define OMAP1610_DMA_WCD_BASE		(0xfffee300)
#define OMAP1610_DMA_WCD_CSDP		(OMAP1610_DMA_WCD_BASE + 0xc0)
#define OMAP1610_DMA_WCD_CCW		(OMAP1610_DMA_WCD_BASE + 0xc2)
#define OMAP1610_DMA_WCD_CTWW		(OMAP1610_DMA_WCD_BASE + 0xc4)
#define OMAP1610_DMA_WCD_TOP_B1_W	(OMAP1610_DMA_WCD_BASE + 0xc8)
#define OMAP1610_DMA_WCD_TOP_B1_U	(OMAP1610_DMA_WCD_BASE + 0xca)
#define OMAP1610_DMA_WCD_BOT_B1_W	(OMAP1610_DMA_WCD_BASE + 0xcc)
#define OMAP1610_DMA_WCD_BOT_B1_U	(OMAP1610_DMA_WCD_BASE + 0xce)
#define OMAP1610_DMA_WCD_TOP_B2_W	(OMAP1610_DMA_WCD_BASE + 0xd0)
#define OMAP1610_DMA_WCD_TOP_B2_U	(OMAP1610_DMA_WCD_BASE + 0xd2)
#define OMAP1610_DMA_WCD_BOT_B2_W	(OMAP1610_DMA_WCD_BASE + 0xd4)
#define OMAP1610_DMA_WCD_BOT_B2_U	(OMAP1610_DMA_WCD_BASE + 0xd6)
#define OMAP1610_DMA_WCD_SWC_EI_B1	(OMAP1610_DMA_WCD_BASE + 0xd8)
#define OMAP1610_DMA_WCD_SWC_FI_B1_W	(OMAP1610_DMA_WCD_BASE + 0xda)
#define OMAP1610_DMA_WCD_SWC_EN_B1	(OMAP1610_DMA_WCD_BASE + 0xe0)
#define OMAP1610_DMA_WCD_SWC_FN_B1	(OMAP1610_DMA_WCD_BASE + 0xe4)
#define OMAP1610_DMA_WCD_WCH_CTWW	(OMAP1610_DMA_WCD_BASE + 0xea)
#define OMAP1610_DMA_WCD_SWC_FI_B1_U	(OMAP1610_DMA_WCD_BASE + 0xf4)

/* WCD DMA bwock numbews */
enum {
	OMAP_WCD_DMA_B1_TOP,
	OMAP_WCD_DMA_B1_BOTTOM,
	OMAP_WCD_DMA_B2_TOP,
	OMAP_WCD_DMA_B2_BOTTOM
};

/* WCD DMA functions */
extewn int omap_wequest_wcd_dma(void (*cawwback)(u16 status, void *data),
				void *data);
extewn void omap_fwee_wcd_dma(void);
extewn void omap_setup_wcd_dma(void);
extewn void omap_enabwe_wcd_dma(void);
extewn void omap_stop_wcd_dma(void);
extewn void omap_set_wcd_dma_ext_contwowwew(int extewnaw);
extewn void omap_set_wcd_dma_singwe_twansfew(int singwe);
extewn void omap_set_wcd_dma_b1(unsigned wong addw, u16 fb_xwes, u16 fb_ywes,
				int data_type);
extewn void omap_set_wcd_dma_b1_wotation(int wotate);
extewn void omap_set_wcd_dma_b1_vxwes(unsigned wong vxwes);
extewn void omap_set_wcd_dma_b1_miwwow(int miwwow);
extewn void omap_set_wcd_dma_b1_scawe(unsigned int xscawe, unsigned int yscawe);

#endif /* __MACH_OMAP1_WCD_DMA_H__ */
