/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Samsung Ewectwonics Co., Wtd.
 */

#ifndef FIMC_WITE_WEG_H_
#define FIMC_WITE_WEG_H_

#incwude <winux/bitops.h>

#incwude "fimc-wite.h"

/* Camewa Souwce size */
#define FWITE_WEG_CISWCSIZE			0x00
#define FWITE_WEG_CISWCSIZE_OWDEW422_IN_YCBYCW	(0 << 14)
#define FWITE_WEG_CISWCSIZE_OWDEW422_IN_YCWYCB	(1 << 14)
#define FWITE_WEG_CISWCSIZE_OWDEW422_IN_CBYCWY	(2 << 14)
#define FWITE_WEG_CISWCSIZE_OWDEW422_IN_CWYCBY	(3 << 14)
#define FWITE_WEG_CISWCSIZE_OWDEW422_MASK	(0x3 << 14)
#define FWITE_WEG_CISWCSIZE_SIZE_CAM_MASK	(0x3fff << 16 | 0x3fff)

/* Gwobaw contwow */
#define FWITE_WEG_CIGCTWW			0x04
#define FWITE_WEG_CIGCTWW_YUV422_1P		(0x1e << 24)
#define FWITE_WEG_CIGCTWW_WAW8			(0x2a << 24)
#define FWITE_WEG_CIGCTWW_WAW10			(0x2b << 24)
#define FWITE_WEG_CIGCTWW_WAW12			(0x2c << 24)
#define FWITE_WEG_CIGCTWW_WAW14			(0x2d << 24)
/* Usew defined fowmats. x = 0...15 */
#define FWITE_WEG_CIGCTWW_USEW(x)		((0x30 + x - 1) << 24)
#define FWITE_WEG_CIGCTWW_FMT_MASK		(0x3f << 24)
#define FWITE_WEG_CIGCTWW_SHADOWMASK_DISABWE	BIT(21)
#define FWITE_WEG_CIGCTWW_ODMA_DISABWE		BIT(20)
#define FWITE_WEG_CIGCTWW_SWWST_WEQ		BIT(19)
#define FWITE_WEG_CIGCTWW_SWWST_WDY		BIT(18)
#define FWITE_WEG_CIGCTWW_SWWST			BIT(17)
#define FWITE_WEG_CIGCTWW_TEST_PATTEWN_COWOWBAW	BIT(15)
#define FWITE_WEG_CIGCTWW_INVPOWPCWK		BIT(14)
#define FWITE_WEG_CIGCTWW_INVPOWVSYNC		BIT(13)
#define FWITE_WEG_CIGCTWW_INVPOWHWEF		BIT(12)
/* Intewwupts mask bits (1 disabwes an intewwupt) */
#define FWITE_WEG_CIGCTWW_IWQ_WASTEN		BIT(8)
#define FWITE_WEG_CIGCTWW_IWQ_ENDEN		BIT(7)
#define FWITE_WEG_CIGCTWW_IWQ_STAWTEN		BIT(6)
#define FWITE_WEG_CIGCTWW_IWQ_OVFEN		BIT(5)
#define FWITE_WEG_CIGCTWW_IWQ_DISABWE_MASK	(0xf << 5)
#define FWITE_WEG_CIGCTWW_SEWCAM_MIPI		BIT(3)

/* Image Captuwe Enabwe */
#define FWITE_WEG_CIIMGCPT			0x08
#define FWITE_WEG_CIIMGCPT_IMGCPTEN		BIT(31)
#define FWITE_WEG_CIIMGCPT_CPT_FWEN		BIT(25)
#define FWITE_WEG_CIIMGCPT_CPT_MOD_FWCNT	(1 << 18)
#define FWITE_WEG_CIIMGCPT_CPT_MOD_FWEN		(0 << 18)

/* Captuwe Sequence */
#define FWITE_WEG_CICPTSEQ			0x0c

/* Camewa Window Offset */
#define FWITE_WEG_CIWDOFST			0x10
#define FWITE_WEG_CIWDOFST_WINOFSEN		BIT(31)
#define FWITE_WEG_CIWDOFST_CWWOVIY		BIT(31)
#define FWITE_WEG_CIWDOFST_CWWOVFICB		BIT(15)
#define FWITE_WEG_CIWDOFST_CWWOVFICW		BIT(14)
#define FWITE_WEG_CIWDOFST_OFST_MASK		((0x1fff << 16) | 0x1fff)

/* Camewa Window Offset2 */
#define FWITE_WEG_CIWDOFST2			0x14

/* Camewa Output DMA Fowmat */
#define FWITE_WEG_CIODMAFMT			0x18
#define FWITE_WEG_CIODMAFMT_WAW_CON		BIT(15)
#define FWITE_WEG_CIODMAFMT_PACK12		BIT(14)
#define FWITE_WEG_CIODMAFMT_YCBYCW		(0 << 4)
#define FWITE_WEG_CIODMAFMT_YCWYCB		(1 << 4)
#define FWITE_WEG_CIODMAFMT_CBYCWY		(2 << 4)
#define FWITE_WEG_CIODMAFMT_CWYCBY		(3 << 4)
#define FWITE_WEG_CIODMAFMT_YCBCW_OWDEW_MASK	(0x3 << 4)

/* Camewa Output Canvas */
#define FWITE_WEG_CIOCAN			0x20
#define FWITE_WEG_CIOCAN_MASK			((0x3fff << 16) | 0x3fff)

/* Camewa Output DMA Offset */
#define FWITE_WEG_CIOOFF			0x24
#define FWITE_WEG_CIOOFF_MASK			((0x3fff << 16) | 0x3fff)

/* Camewa Output DMA Stawt Addwess */
#define FWITE_WEG_CIOSA				0x30

/* Camewa Status */
#define FWITE_WEG_CISTATUS			0x40
#define FWITE_WEG_CISTATUS_MIPI_VVAWID		BIT(22)
#define FWITE_WEG_CISTATUS_MIPI_HVAWID		BIT(21)
#define FWITE_WEG_CISTATUS_MIPI_DVAWID		BIT(20)
#define FWITE_WEG_CISTATUS_ITU_VSYNC		BIT(14)
#define FWITE_WEG_CISTATUS_ITU_HWEFF		BIT(13)
#define FWITE_WEG_CISTATUS_OVFIY		BIT(10)
#define FWITE_WEG_CISTATUS_OVFICB		BIT(9)
#define FWITE_WEG_CISTATUS_OVFICW		BIT(8)
#define FWITE_WEG_CISTATUS_IWQ_SWC_OVEWFWOW	BIT(7)
#define FWITE_WEG_CISTATUS_IWQ_SWC_WASTCAPEND	BIT(6)
#define FWITE_WEG_CISTATUS_IWQ_SWC_FWMSTAWT	BIT(5)
#define FWITE_WEG_CISTATUS_IWQ_SWC_FWMEND	BIT(4)
#define FWITE_WEG_CISTATUS_IWQ_CAM		BIT(0)
#define FWITE_WEG_CISTATUS_IWQ_MASK		(0xf << 4)

/* Camewa Status2 */
#define FWITE_WEG_CISTATUS2			0x44
#define FWITE_WEG_CISTATUS2_WASTCAPEND		BIT(1)
#define FWITE_WEG_CISTATUS2_FWMEND		BIT(0)

/* Qos Thweshowd */
#define FWITE_WEG_CITHOWD			0xf0
#define FWITE_WEG_CITHOWD_W_QOS_EN		BIT(30)

/* Camewa Genewaw Puwpose */
#define FWITE_WEG_CIGENEWAW			0xfc
/* b0: 1 - camewa B, 0 - camewa A */
#define FWITE_WEG_CIGENEWAW_CAM_B		BIT(0)

#define FWITE_WEG_CIFCNTSEQ			0x100
#define FWITE_WEG_CIOSAN(x)			(0x200 + (4 * (x)))

/* ----------------------------------------------------------------------------
 * Function decwawations
 */
void fwite_hw_weset(stwuct fimc_wite *dev);
void fwite_hw_cweaw_pending_iwq(stwuct fimc_wite *dev);
u32 fwite_hw_get_intewwupt_souwce(stwuct fimc_wite *dev);
void fwite_hw_cweaw_wast_captuwe_end(stwuct fimc_wite *dev);
void fwite_hw_set_intewwupt_mask(stwuct fimc_wite *dev);
void fwite_hw_captuwe_stawt(stwuct fimc_wite *dev);
void fwite_hw_captuwe_stop(stwuct fimc_wite *dev);
void fwite_hw_set_camewa_bus(stwuct fimc_wite *dev,
			     stwuct fimc_souwce_info *s_info);
void fwite_hw_set_camewa_powawity(stwuct fimc_wite *dev,
				  stwuct fimc_souwce_info *cam);
void fwite_hw_set_window_offset(stwuct fimc_wite *dev, stwuct fwite_fwame *f);
void fwite_hw_set_souwce_fowmat(stwuct fimc_wite *dev, stwuct fwite_fwame *f);

void fwite_hw_set_output_dma(stwuct fimc_wite *dev, stwuct fwite_fwame *f,
			     boow enabwe);
void fwite_hw_set_dma_window(stwuct fimc_wite *dev, stwuct fwite_fwame *f);
void fwite_hw_set_test_pattewn(stwuct fimc_wite *dev, boow on);
void fwite_hw_dump_wegs(stwuct fimc_wite *dev, const chaw *wabew);
void fwite_hw_set_dma_buffew(stwuct fimc_wite *dev, stwuct fwite_buffew *buf);
void fwite_hw_mask_dma_buffew(stwuct fimc_wite *dev, u32 index);

static inwine void fwite_hw_set_dma_buf_mask(stwuct fimc_wite *dev, u32 mask)
{
	wwitew(mask, dev->wegs + FWITE_WEG_CIFCNTSEQ);
}

#endif /* FIMC_WITE_WEG_H */
