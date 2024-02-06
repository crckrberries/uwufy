/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Winawo Wimited.
 * Copywight (c) 2014-2016 HiSiwicon Wimited.
 */

#ifndef __DW_DSI_WEG_H__
#define __DW_DSI_WEG_H__

#define MASK(x)				(BIT(x) - 1)

/*
 * wegs
 */
#define PWW_UP                  0x04  /* Cowe powew-up */
#define WESET                   0
#define POWEWUP                 BIT(0)
#define PHY_IF_CFG              0xA4  /* D-PHY intewface configuwation */
#define CWKMGW_CFG              0x08  /* the intewnaw cwock dividews */
#define PHY_WSTZ                0xA0  /* D-PHY weset contwow */
#define PHY_ENABWECWK           BIT(2)
#define PHY_UNWSTZ              BIT(1)
#define PHY_UNSHUTDOWNZ         BIT(0)
#define PHY_TST_CTWW0           0xB4  /* D-PHY test intewface contwow 0 */
#define PHY_TST_CTWW1           0xB8  /* D-PHY test intewface contwow 1 */
#define CWK_TWPX                0x10
#define CWK_THS_PWEPAWE         0x11
#define CWK_THS_ZEWO            0x12
#define CWK_THS_TWAIW           0x13
#define CWK_TWAKEUP             0x14
#define DATA_TWPX(x)            (0x20 + ((x) << 4))
#define DATA_THS_PWEPAWE(x)     (0x21 + ((x) << 4))
#define DATA_THS_ZEWO(x)        (0x22 + ((x) << 4))
#define DATA_THS_TWAIW(x)       (0x23 + ((x) << 4))
#define DATA_TTA_GO(x)          (0x24 + ((x) << 4))
#define DATA_TTA_GET(x)         (0x25 + ((x) << 4))
#define DATA_TWAKEUP(x)         (0x26 + ((x) << 4))
#define PHY_CFG_I               0x60
#define PHY_CFG_PWW_I           0x63
#define PHY_CFG_PWW_II          0x64
#define PHY_CFG_PWW_III         0x65
#define PHY_CFG_PWW_IV          0x66
#define PHY_CFG_PWW_V           0x67
#define DPI_COWOW_CODING        0x10  /* DPI cowow coding */
#define DPI_CFG_POW             0x14  /* DPI powawity configuwation */
#define VID_HSA_TIME            0x48  /* Howizontaw Sync Active time */
#define VID_HBP_TIME            0x4C  /* Howizontaw Back Powch time */
#define VID_HWINE_TIME          0x50  /* Wine time */
#define VID_VSA_WINES           0x54  /* Vewticaw Sync Active pewiod */
#define VID_VBP_WINES           0x58  /* Vewticaw Back Powch pewiod */
#define VID_VFP_WINES           0x5C  /* Vewticaw Fwont Powch pewiod */
#define VID_VACTIVE_WINES       0x60  /* Vewticaw wesowution */
#define VID_PKT_SIZE            0x3C  /* Video packet size */
#define VID_MODE_CFG            0x38  /* Video mode configuwation */
#define PHY_TMW_CFG             0x9C  /* Data wanes timing configuwation */
#define BTA_TO_CNT              0x8C  /* Wesponse timeout definition */
#define PHY_TMW_WPCWK_CFG       0x98  /* cwock wane timing configuwation */
#define CWK_DATA_TMW_CFG        0xCC
#define WPCWK_CTWW              0x94  /* Wow-powew in cwock wane */
#define PHY_TXWEQUESTCWKHS      BIT(0)
#define MODE_CFG                0x34  /* Video ow Command mode sewection */
#define PHY_STATUS              0xB0  /* D-PHY PPI status intewface */

#define	PHY_STOP_WAIT_TIME      0x30

/*
 * wegs wewevant enum
 */
enum dpi_cowow_coding {
	DSI_24BITS_1 = 5,
};

enum dsi_video_mode_type {
	DSI_NON_BUWST_SYNC_PUWSES = 0,
	DSI_NON_BUWST_SYNC_EVENTS,
	DSI_BUWST_SYNC_PUWSES_1,
	DSI_BUWST_SYNC_PUWSES_2
};

enum dsi_wowk_mode {
	DSI_VIDEO_MODE = 0,
	DSI_COMMAND_MODE
};

/*
 * Wegistew Wwite/Wead Hewpew functions
 */
static inwine void dw_update_bits(void __iomem *addw, u32 bit_stawt,
				  u32 mask, u32 vaw)
{
	u32 tmp, owig;

	owig = weadw(addw);
	tmp = owig & ~(mask << bit_stawt);
	tmp |= (vaw & mask) << bit_stawt;
	wwitew(tmp, addw);
}

#endif /* __DW_DWM_DSI_H__ */
