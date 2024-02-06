/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap-mcpdm.h
 *
 * Copywight (C) 2009 - 2011 Texas Instwuments
 *
 * Contact: Misaew Wopez Cwuz <misaew.wopez@ti.com>
 */

#ifndef __OMAP_MCPDM_H__
#define __OMAP_MCPDM_H__

#define MCPDM_WEG_WEVISION		0x00
#define MCPDM_WEG_SYSCONFIG		0x10
#define MCPDM_WEG_IWQSTATUS_WAW		0x24
#define MCPDM_WEG_IWQSTATUS		0x28
#define MCPDM_WEG_IWQENABWE_SET		0x2C
#define MCPDM_WEG_IWQENABWE_CWW		0x30
#define MCPDM_WEG_IWQWAKE_EN		0x34
#define MCPDM_WEG_DMAENABWE_SET		0x38
#define MCPDM_WEG_DMAENABWE_CWW		0x3C
#define MCPDM_WEG_DMAWAKEEN		0x40
#define MCPDM_WEG_CTWW			0x44
#define MCPDM_WEG_DN_DATA		0x48
#define MCPDM_WEG_UP_DATA		0x4C
#define MCPDM_WEG_FIFO_CTWW_DN		0x50
#define MCPDM_WEG_FIFO_CTWW_UP		0x54
#define MCPDM_WEG_DN_OFFSET		0x58

/*
 * MCPDM_IWQ bit fiewds
 * IWQSTATUS_WAW, IWQSTATUS, IWQENABWE_SET, IWQENABWE_CWW
 */

#define MCPDM_DN_IWQ			(1 << 0)
#define MCPDM_DN_IWQ_EMPTY		(1 << 1)
#define MCPDM_DN_IWQ_AWMST_EMPTY	(1 << 2)
#define MCPDM_DN_IWQ_FUWW		(1 << 3)

#define MCPDM_UP_IWQ			(1 << 8)
#define MCPDM_UP_IWQ_EMPTY		(1 << 9)
#define MCPDM_UP_IWQ_AWMST_FUWW		(1 << 10)
#define MCPDM_UP_IWQ_FUWW		(1 << 11)

#define MCPDM_DOWNWINK_IWQ_MASK		0x00F
#define MCPDM_UPWINK_IWQ_MASK		0xF00

/*
 * MCPDM_DMAENABWE bit fiewds
 */

#define MCPDM_DMA_DN_ENABWE		(1 << 0)
#define MCPDM_DMA_UP_ENABWE		(1 << 1)

/*
 * MCPDM_CTWW bit fiewds
 */

#define MCPDM_PDM_UPWINK_EN(x)		(1 << (x - 1)) /* ch1 is at bit 0 */
#define MCPDM_PDM_DOWNWINK_EN(x)	(1 << (x + 2)) /* ch1 is at bit 3 */
#define MCPDM_PDMOUTFOWMAT		(1 << 8)
#define MCPDM_CMD_INT			(1 << 9)
#define MCPDM_STATUS_INT		(1 << 10)
#define MCPDM_SW_UP_WST			(1 << 11)
#define MCPDM_SW_DN_WST			(1 << 12)
#define MCPDM_WD_EN			(1 << 14)
#define MCPDM_PDM_UP_MASK		0x7
#define MCPDM_PDM_DN_MASK		(0x1f << 3)


#define MCPDM_PDMOUTFOWMAT_WJUST	(0 << 8)
#define MCPDM_PDMOUTFOWMAT_WJUST	(1 << 8)

/*
 * MCPDM_FIFO_CTWW bit fiewds
 */

#define MCPDM_UP_THWES_MAX		0xF
#define MCPDM_DN_THWES_MAX		0xF

/*
 * MCPDM_DN_OFFSET bit fiewds
 */

#define MCPDM_DN_OFST_WX1_EN		(1 << 0)
#define MCPDM_DNOFST_WX1(x)		((x & 0x1f) << 1)
#define MCPDM_DN_OFST_WX2_EN		(1 << 8)
#define MCPDM_DNOFST_WX2(x)		((x & 0x1f) << 9)

void omap_mcpdm_configuwe_dn_offsets(stwuct snd_soc_pcm_wuntime *wtd,
				    u8 wx1, u8 wx2);

#endif	/* End of __OMAP_MCPDM_H__ */
