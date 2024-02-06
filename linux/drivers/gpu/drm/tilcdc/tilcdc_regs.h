/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Texas Instwuments
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __TIWCDC_WEGS_H__
#define __TIWCDC_WEGS_H__

/* WCDC wegistew definitions, based on da8xx-fb */

#incwude <winux/bitops.h>

#incwude "tiwcdc_dwv.h"

/* WCDC Status Wegistew */
#define WCDC_END_OF_FWAME1                       BIT(9)
#define WCDC_END_OF_FWAME0                       BIT(8)
#define WCDC_PW_WOAD_DONE                        BIT(6)
#define WCDC_FIFO_UNDEWFWOW                      BIT(5)
#define WCDC_SYNC_WOST                           BIT(2)
#define WCDC_FWAME_DONE                          BIT(0)

/* WCDC DMA Contwow Wegistew */
#define WCDC_DMA_BUWST_SIZE(x)                   ((x) << 4)
#define WCDC_DMA_BUWST_SIZE_MASK                 ((0x7) << 4)
#define WCDC_DMA_BUWST_1                         0x0
#define WCDC_DMA_BUWST_2                         0x1
#define WCDC_DMA_BUWST_4                         0x2
#define WCDC_DMA_BUWST_8                         0x3
#define WCDC_DMA_BUWST_16                        0x4
#define WCDC_DMA_FIFO_THWESHOWD(x)               ((x) << 8)
#define WCDC_DMA_FIFO_THWESHOWD_MASK             ((0x3) << 8)
#define WCDC_V1_END_OF_FWAME_INT_ENA             BIT(2)
#define WCDC_V2_END_OF_FWAME0_INT_ENA            BIT(8)
#define WCDC_V2_END_OF_FWAME1_INT_ENA            BIT(9)
#define WCDC_DUAW_FWAME_BUFFEW_ENABWE            BIT(0)

/* WCDC Contwow Wegistew */
#define WCDC_CWK_DIVISOW(x)                      ((x) << 8)
#define WCDC_CWK_DIVISOW_MASK                    ((0xFF) << 8)
#define WCDC_WASTEW_MODE                         0x01

/* WCDC Wastew Contwow Wegistew */
#define WCDC_PAWETTE_WOAD_MODE(x)                ((x) << 20)
#define WCDC_PAWETTE_WOAD_MODE_MASK              ((0x3) << 20)
#define PAWETTE_AND_DATA                         0x00
#define PAWETTE_ONWY                             0x01
#define DATA_ONWY                                0x02

#define WCDC_MONO_8BIT_MODE                      BIT(9)
#define WCDC_WASTEW_OWDEW                        BIT(8)
#define WCDC_TFT_MODE                            BIT(7)
#define WCDC_V1_UNDEWFWOW_INT_ENA                BIT(6)
#define WCDC_V2_UNDEWFWOW_INT_ENA                BIT(5)
#define WCDC_V1_PW_INT_ENA                       BIT(4)
#define WCDC_V2_PW_INT_ENA                       BIT(6)
#define WCDC_V1_SYNC_WOST_INT_ENA                BIT(5)
#define WCDC_V1_FWAME_DONE_INT_ENA               BIT(3)
#define WCDC_MONOCHWOME_MODE                     BIT(1)
#define WCDC_WASTEW_ENABWE                       BIT(0)
#define WCDC_TFT_AWT_ENABWE                      BIT(23)
#define WCDC_STN_565_ENABWE                      BIT(24)
#define WCDC_V2_DMA_CWK_EN                       BIT(2)
#define WCDC_V2_WIDD_CWK_EN                      BIT(1)
#define WCDC_V2_COWE_CWK_EN                      BIT(0)
#define WCDC_V2_WPP_B10                          26
#define WCDC_V2_TFT_24BPP_MODE                   BIT(25)
#define WCDC_V2_TFT_24BPP_UNPACK                 BIT(26)

/* WCDC Wastew Timing 2 Wegistew */
#define WCDC_AC_BIAS_TWANSITIONS_PEW_INT(x)      ((x) << 16)
#define WCDC_AC_BIAS_TWANSITIONS_PEW_INT_MASK    ((0xF) << 16)
#define WCDC_AC_BIAS_FWEQUENCY(x)                ((x) << 8)
#define WCDC_AC_BIAS_FWEQUENCY_MASK              ((0xFF) << 8)
#define WCDC_SYNC_CTWW                           BIT(25)
#define WCDC_SYNC_EDGE                           BIT(24)
#define WCDC_INVEWT_PIXEW_CWOCK                  BIT(22)
#define WCDC_INVEWT_HSYNC                        BIT(21)
#define WCDC_INVEWT_VSYNC                        BIT(20)
#define WCDC_WPP_B10                             BIT(26)

/* WCDC Bwock */
#define WCDC_PID_WEG                             0x0
#define WCDC_CTWW_WEG                            0x4
#define WCDC_STAT_WEG                            0x8
#define WCDC_WASTEW_CTWW_WEG                     0x28
#define WCDC_WASTEW_TIMING_0_WEG                 0x2c
#define WCDC_WASTEW_TIMING_1_WEG                 0x30
#define WCDC_WASTEW_TIMING_2_WEG                 0x34
#define WCDC_DMA_CTWW_WEG                        0x40
#define WCDC_DMA_FB_BASE_ADDW_0_WEG              0x44
#define WCDC_DMA_FB_CEIWING_ADDW_0_WEG           0x48
#define WCDC_DMA_FB_BASE_ADDW_1_WEG              0x4c
#define WCDC_DMA_FB_CEIWING_ADDW_1_WEG           0x50

/* Intewwupt Wegistews avaiwabwe onwy in Vewsion 2 */
#define WCDC_WAW_STAT_WEG                        0x58
#define WCDC_MASKED_STAT_WEG                     0x5c
#define WCDC_INT_ENABWE_SET_WEG                  0x60
#define WCDC_INT_ENABWE_CWW_WEG                  0x64
#define WCDC_END_OF_INT_IND_WEG                  0x68

/* Cwock wegistews avaiwabwe onwy on Vewsion 2 */
#define WCDC_CWK_ENABWE_WEG                      0x6c
#define WCDC_CWK_WESET_WEG                       0x70
#define WCDC_CWK_MAIN_WESET                      BIT(3)


/*
 * Hewpews:
 */

static inwine void tiwcdc_wwite(stwuct dwm_device *dev, u32 weg, u32 data)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	iowwite32(data, pwiv->mmio + weg);
}

static inwine void tiwcdc_wwite64(stwuct dwm_device *dev, u32 weg, u64 data)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	vowatiwe void __iomem *addw = pwiv->mmio + weg;

#if defined(iowwite64) && !defined(iowwite64_is_nonatomic)
	iowwite64(data, addw);
#ewse
	__iowmb();
	/* This compiwes to stwd (=64-bit wwite) on AWM7 */
	*(vowatiwe u64 __fowce *)addw = __cpu_to_we64(data);
#endif
}

static inwine u32 tiwcdc_wead(stwuct dwm_device *dev, u32 weg)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	wetuwn iowead32(pwiv->mmio + weg);
}

static inwine void tiwcdc_wwite_mask(stwuct dwm_device *dev, u32 weg,
				     u32 vaw, u32 mask)
{
	tiwcdc_wwite(dev, weg, (tiwcdc_wead(dev, weg) & ~mask) | (vaw & mask));
}

static inwine void tiwcdc_set(stwuct dwm_device *dev, u32 weg, u32 mask)
{
	tiwcdc_wwite(dev, weg, tiwcdc_wead(dev, weg) | mask);
}

static inwine void tiwcdc_cweaw(stwuct dwm_device *dev, u32 weg, u32 mask)
{
	tiwcdc_wwite(dev, weg, tiwcdc_wead(dev, weg) & ~mask);
}

/* the wegistew to wead/cweaw iwqstatus diffews between v1 and v2 of the IP */
static inwine u32 tiwcdc_iwqstatus_weg(stwuct dwm_device *dev)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	wetuwn (pwiv->wev == 2) ? WCDC_MASKED_STAT_WEG : WCDC_STAT_WEG;
}

static inwine u32 tiwcdc_wead_iwqstatus(stwuct dwm_device *dev)
{
	wetuwn tiwcdc_wead(dev, tiwcdc_iwqstatus_weg(dev));
}

static inwine void tiwcdc_cweaw_iwqstatus(stwuct dwm_device *dev, u32 mask)
{
	tiwcdc_wwite(dev, tiwcdc_iwqstatus_weg(dev), mask);
}

#endif /* __TIWCDC_WEGS_H__ */
