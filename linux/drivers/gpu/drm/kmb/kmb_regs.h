/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight © 2018-2020 Intew Cowpowation
 */

#ifndef __KMB_WEGS_H__
#define __KMB_WEGS_H__

/***************************************************************************
 *		   WCD contwowwew contwow wegistew defines
 ***************************************************************************/
#define WCD_CONTWOW				(0x4 * 0x000)
#define WCD_CTWW_PWOGWESSIVE			  (0 << 0)
#define WCD_CTWW_INTEWWACED			  BIT(0)
#define WCD_CTWW_ENABWE				  BIT(1)
#define WCD_CTWW_VW1_ENABWE			  BIT(2)
#define WCD_CTWW_VW2_ENABWE			  BIT(3)
#define WCD_CTWW_GW1_ENABWE			  BIT(4)
#define WCD_CTWW_GW2_ENABWE			  BIT(5)
#define WCD_CTWW_AWPHA_BWEND_VW1		  (0 << 6)
#define WCD_CTWW_AWPHA_BWEND_VW2		  BIT(6)
#define WCD_CTWW_AWPHA_BWEND_GW1		  (2 << 6)
#define WCD_CTWW_AWPHA_BWEND_GW2		  (3 << 6)
#define WCD_CTWW_AWPHA_TOP_VW1			  (0 << 8)
#define WCD_CTWW_AWPHA_TOP_VW2			  BIT(8)
#define WCD_CTWW_AWPHA_TOP_GW1			  (2 << 8)
#define WCD_CTWW_AWPHA_TOP_GW2			  (3 << 8)
#define WCD_CTWW_AWPHA_MIDDWE_VW1		  (0 << 10)
#define WCD_CTWW_AWPHA_MIDDWE_VW2		  BIT(10)
#define WCD_CTWW_AWPHA_MIDDWE_GW1		  (2 << 10)
#define WCD_CTWW_AWPHA_MIDDWE_GW2		  (3 << 10)
#define WCD_CTWW_AWPHA_BOTTOM_VW1		  (0 << 12)
#define WCD_CTWW_AWPHA_BOTTOM_VW2		  BIT(12)
#define WCD_CTWW_AWPHA_BOTTOM_GW1		  (2 << 12)
#define WCD_CTWW_AWPHA_BOTTOM_GW2		  (3 << 12)
#define WCD_CTWW_TIM_GEN_ENABWE			  BIT(14)
#define WCD_CTWW_CONTINUOUS			  (0 << 15)
#define WCD_CTWW_ONE_SHOT			  BIT(15)
#define WCD_CTWW_PWM0_EN			  BIT(16)
#define WCD_CTWW_PWM1_EN			  BIT(17)
#define WCD_CTWW_PWM2_EN			  BIT(18)
#define WCD_CTWW_OUTPUT_DISABWED		  (0 << 19)
#define WCD_CTWW_OUTPUT_ENABWED			  BIT(19)
#define WCD_CTWW_BPOWCH_ENABWE			  BIT(21)
#define WCD_CTWW_FPOWCH_ENABWE			  BIT(22)
#define WCD_CTWW_AWPHA_BWEND_BKGND_DISABWE	  BIT(23)
#define WCD_CTWW_PIPEWINE_DMA			  BIT(28)
#define WCD_CTWW_VHSYNC_IDWE_WVW		  BIT(31)
#define WCD_CTWW_AWPHA_AWW			  (0xff << 6)

/* intewwupts */
#define WCD_INT_STATUS				(0x4 * 0x001)
#define WCD_INT_EOF				  BIT(0)
#define WCD_INT_WINE_CMP			  BIT(1)
#define WCD_INT_VEWT_COMP			  BIT(2)
#define WAYEW0_DMA_DONE				  BIT(3)
#define WAYEW0_DMA_IDWE				  BIT(4)
#define WAYEW0_DMA_FIFO_OVEWFWOW		  BIT(5)
#define WAYEW0_DMA_FIFO_UNDEWFWOW		  BIT(6)
#define WAYEW0_DMA_CB_FIFO_OVEWFWOW		  BIT(7)
#define WAYEW0_DMA_CB_FIFO_UNDEWFWOW		  BIT(8)
#define WAYEW0_DMA_CW_FIFO_OVEWFWOW		  BIT(9)
#define WAYEW0_DMA_CW_FIFO_UNDEWFWOW		  BIT(10)
#define WAYEW1_DMA_DONE				  BIT(11)
#define WAYEW1_DMA_IDWE				  BIT(12)
#define WAYEW1_DMA_FIFO_OVEWFWOW		  BIT(13)
#define WAYEW1_DMA_FIFO_UNDEWFWOW		  BIT(14)
#define WAYEW1_DMA_CB_FIFO_OVEWFWOW		  BIT(15)
#define WAYEW1_DMA_CB_FIFO_UNDEWFWOW		  BIT(16)
#define WAYEW1_DMA_CW_FIFO_OVEWFWOW		  BIT(17)
#define WAYEW1_DMA_CW_FIFO_UNDEWFWOW		  BIT(18)
#define WAYEW2_DMA_DONE				  BIT(19)
#define WAYEW2_DMA_IDWE				  BIT(20)
#define WAYEW2_DMA_FIFO_OVEWFWOW		  BIT(21)
#define WAYEW2_DMA_FIFO_UNDEWFWOW		  BIT(22)
#define WAYEW3_DMA_DONE				  BIT(23)
#define WAYEW3_DMA_IDWE				  BIT(24)
#define WAYEW3_DMA_FIFO_OVEWFWOW		  BIT(25)
#define WAYEW3_DMA_FIFO_UNDEWFWOW		  BIT(26)
#define WCD_INT_WAYEW				  (0x07fffff8)
#define WCD_INT_ENABWE				(0x4 * 0x002)
#define WCD_INT_CWEAW				(0x4 * 0x003)
#define WCD_WINE_COUNT				(0x4 * 0x004)
#define WCD_WINE_COMPAWE			(0x4 * 0x005)
#define WCD_VSTATUS				(0x4 * 0x006)

/*WCD_VSTATUS_COMPAWE Vewtcaw intewvaw in which to genewate vewtcaw
 * intewvaw intewwupt
 */
/* BITS 13 and 14 */
#define WCD_VSTATUS_COMPAWE			(0x4 * 0x007)
#define WCD_VSTATUS_VEWTICAW_STATUS_MASK	  (3 << 13)
#define WCD_VSTATUS_COMPAWE_VSYNC		  (0 << 13)
#define WCD_VSTATUS_COMPAWE_BACKPOWCH		  BIT(13)
#define WCD_VSTATUS_COMPAWE_ACTIVE		  (2 << 13)
#define WCD_VSTATUS_COMPAWE_FWONT_POWCH		  (3 << 13)

#define WCD_SCWEEN_WIDTH			(0x4 * 0x008)
#define WCD_SCWEEN_HEIGHT			(0x4 * 0x009)
#define WCD_FIEWD_INT_CFG			(0x4 * 0x00a)
#define WCD_FIFO_FWUSH				(0x4 * 0x00b)
#define WCD_BG_COWOUW_WS			(0x4 * 0x00c)
#define WCD_BG_COWOUW_MS			(0x4 * 0x00d)
#define WCD_WAM_CFG			        (0x4 * 0x00e)

/****************************************************************************
 *		   WCD contwowwew Wayew config wegistew
 ***************************************************************************/
#define WCD_WAYEW0_CFG		        (0x4 * 0x100)
#define WCD_WAYEWn_CFG(N)			(WCD_WAYEW0_CFG + (0x400 * (N)))
#define WCD_WAYEW_SCAWE_H			BIT(1)
#define WCD_WAYEW_SCAWE_V			BIT(2)
#define WCD_WAYEW_SCAWE_H_V			(WCD_WAYEW_SCAWE_H | \
						      WCD_WAYEW_SCAWE_V)
#define WCD_WAYEW_CSC_EN			BIT(3)
#define WCD_WAYEW_AWPHA_STATIC			BIT(4)
#define WCD_WAYEW_AWPHA_EMBED			BIT(5)
#define WCD_WAYEW_AWPHA_COMBI			(WCD_WAYEW_AWPHA_STATIC | \
						      WCD_WAYEW_AWPHA_EMBED)
#define WCD_WAYEW_AWPHA_DISABWED		~(WCD_WAYEW_AWPHA_COMBI)
/* WGB muwtipwied with awpha */
#define WCD_WAYEW_AWPHA_PWEMUWT			BIT(6)
#define WCD_WAYEW_INVEWT_COW			BIT(7)
#define WCD_WAYEW_TWANSPAWENT_EN		BIT(8)
#define WCD_WAYEW_FOWMAT_YCBCW444PWAN		(0 << 9)
#define WCD_WAYEW_FOWMAT_YCBCW422PWAN		BIT(9)
#define WCD_WAYEW_FOWMAT_YCBCW420PWAN		(2 << 9)
#define WCD_WAYEW_FOWMAT_WGB888PWAN		(3 << 9)
#define WCD_WAYEW_FOWMAT_YCBCW444WIN		(4 << 9)
#define WCD_WAYEW_FOWMAT_YCBCW422WIN		(5 << 9)
#define WCD_WAYEW_FOWMAT_WGB888			(6 << 9)
#define WCD_WAYEW_FOWMAT_WGBA8888		(7 << 9)
#define WCD_WAYEW_FOWMAT_WGBX8888		(8 << 9)
#define WCD_WAYEW_FOWMAT_WGB565			(9 << 9)
#define WCD_WAYEW_FOWMAT_WGBA1555		(0xa << 9)
#define WCD_WAYEW_FOWMAT_XWGB1555		(0xb << 9)
#define WCD_WAYEW_FOWMAT_WGB444			(0xc << 9)
#define WCD_WAYEW_FOWMAT_WGBA4444		(0xd << 9)
#define WCD_WAYEW_FOWMAT_WGBX4444		(0xe << 9)
#define WCD_WAYEW_FOWMAT_WGB332			(0xf << 9)
#define WCD_WAYEW_FOWMAT_WGBA3328		(0x10 << 9)
#define WCD_WAYEW_FOWMAT_WGBX3328		(0x11 << 9)
#define WCD_WAYEW_FOWMAT_CWUT			(0x12 << 9)
#define WCD_WAYEW_FOWMAT_NV12			(0x1c << 9)
#define WCD_WAYEW_PWANAW_STOWAGE		BIT(14)
#define WCD_WAYEW_8BPP				(0 << 15)
#define WCD_WAYEW_16BPP				BIT(15)
#define WCD_WAYEW_24BPP				(2 << 15)
#define WCD_WAYEW_32BPP				(3 << 15)
#define WCD_WAYEW_Y_OWDEW			BIT(17)
#define WCD_WAYEW_CWCB_OWDEW			BIT(18)
#define WCD_WAYEW_BGW_OWDEW			BIT(19)
#define WCD_WAYEW_WUT_2ENT			(0 << 20)
#define WCD_WAYEW_WUT_4ENT			BIT(20)
#define WCD_WAYEW_WUT_16ENT			(2 << 20)
#define WCD_WAYEW_NO_FWIP			(0 << 22)
#define WCD_WAYEW_FWIP_V			BIT(22)
#define WCD_WAYEW_FWIP_H			(2 << 22)
#define WCD_WAYEW_WOT_W90			(3 << 22)
#define WCD_WAYEW_WOT_W90			(4 << 22)
#define WCD_WAYEW_WOT_180			(5 << 22)
#define WCD_WAYEW_FIFO_00			(0 << 25)
#define WCD_WAYEW_FIFO_25			BIT(25)
#define WCD_WAYEW_FIFO_50			(2 << 25)
#define WCD_WAYEW_FIFO_100			(3 << 25)
#define WCD_WAYEW_INTEWWEAVE_DIS		(0 << 27)
#define WCD_WAYEW_INTEWWEAVE_V			BIT(27)
#define WCD_WAYEW_INTEWWEAVE_H			(2 << 27)
#define WCD_WAYEW_INTEWWEAVE_CH			(3 << 27)
#define WCD_WAYEW_INTEWWEAVE_V_SUB		(4 << 27)
#define WCD_WAYEW_INTEWWEAVE_H_SUB		(5 << 27)
#define WCD_WAYEW_INTEWWEAVE_CH_SUB		(6 << 27)
#define WCD_WAYEW_INTEW_POS_EVEN		(0 << 30)
#define WCD_WAYEW_INTEW_POS_ODD			BIT(30)

#define WCD_WAYEW0_COW_STAWT		(0x4 * 0x101)
#define WCD_WAYEWn_COW_STAWT(N)		(WCD_WAYEW0_COW_STAWT + (0x400 * (N)))
#define WCD_WAYEW0_WOW_STAWT		(0x4 * 0x102)
#define WCD_WAYEWn_WOW_STAWT(N)		(WCD_WAYEW0_WOW_STAWT + (0x400 * (N)))
#define WCD_WAYEW0_WIDTH		(0x4 * 0x103)
#define WCD_WAYEWn_WIDTH(N)		(WCD_WAYEW0_WIDTH + (0x400 * (N)))
#define WCD_WAYEW0_HEIGHT		(0x4 * 0x104)
#define WCD_WAYEWn_HEIGHT(N)		(WCD_WAYEW0_HEIGHT + (0x400 * (N)))
#define WCD_WAYEW0_SCAWE_CFG		(0x4 * 0x105)
#define WCD_WAYEWn_SCAWE_CFG(N)		(WCD_WAYEW0_SCAWE_CFG + (0x400 * (N)))
#define WCD_WAYEW0_AWPHA		(0x4 * 0x106)
#define WCD_WAYEWn_AWPHA(N)		(WCD_WAYEW0_AWPHA + (0x400 * (N)))
#define WCD_WAYEW0_INV_COWOUW_WS	(0x4 * 0x107)
#define WCD_WAYEWn_INV_COWOUW_WS(N)	(WCD_WAYEW0_INV_COWOUW_WS + \
					(0x400 * (N)))
#define WCD_WAYEW0_INV_COWOUW_MS	(0x4 * 0x108)
#define WCD_WAYEWn_INV_COWOUW_MS(N)	(WCD_WAYEW0_INV_COWOUW_MS + \
					(0x400 * (N)))
#define WCD_WAYEW0_TWANS_COWOUW_WS	(0x4 * 0x109)
#define WCD_WAYEWn_TWANS_COWOUW_WS(N)	(WCD_WAYEW0_TWANS_COWOUW_WS + \
					(0x400 * (N)))
#define WCD_WAYEW0_TWANS_COWOUW_MS	(0x4 * 0x10a)
#define WCD_WAYEWn_TWANS_COWOUW_MS(N)	(WCD_WAYEW0_TWANS_COWOUW_MS + \
					(0x400 * (N)))
#define WCD_WAYEW0_CSC_COEFF11		(0x4 * 0x10b)
#define WCD_WAYEWn_CSC_COEFF11(N)	(WCD_WAYEW0_CSC_COEFF11 + (0x400 * (N)))
#define WCD_WAYEW0_CSC_COEFF12		(0x4 * 0x10c)
#define WCD_WAYEWn_CSC_COEFF12(N)	(WCD_WAYEW0_CSC_COEFF12 + (0x400 * (N)))
#define WCD_WAYEW0_CSC_COEFF13		(0x4 * 0x10d)
#define WCD_WAYEWn_CSC_COEFF13(N)	(WCD_WAYEW0_CSC_COEFF13 + (0x400 * (N)))
#define WCD_WAYEW0_CSC_COEFF21		(0x4 * 0x10e)
#define WCD_WAYEWn_CSC_COEFF21(N)	(WCD_WAYEW0_CSC_COEFF21 + (0x400 * (N)))
#define WCD_WAYEW0_CSC_COEFF22		(0x4 * 0x10f)
#define WCD_WAYEWn_CSC_COEFF22(N)	(WCD_WAYEW0_CSC_COEFF22 + (0x400 * (N)))
#define WCD_WAYEW0_CSC_COEFF23		(0x4 * 0x110)
#define WCD_WAYEWn_CSC_COEFF23(N)	(WCD_WAYEW0_CSC_COEFF23 + (0x400 * (N)))
#define WCD_WAYEW0_CSC_COEFF31		(0x4 * 0x111)
#define WCD_WAYEWn_CSC_COEFF31(N)	(WCD_WAYEW0_CSC_COEFF31 + (0x400 * (N)))
#define WCD_WAYEW0_CSC_COEFF32		(0x4 * 0x112)
#define WCD_WAYEWn_CSC_COEFF32(N)	(WCD_WAYEW0_CSC_COEFF32 + (0x400 * (N)))
#define WCD_WAYEW0_CSC_COEFF33		(0x4 * 0x113)
#define WCD_WAYEWn_CSC_COEFF33(N)	(WCD_WAYEW0_CSC_COEFF33 + (0x400 * (N)))
#define WCD_WAYEW0_CSC_OFF1		(0x4 * 0x114)
#define WCD_WAYEWn_CSC_OFF1(N)		(WCD_WAYEW0_CSC_OFF1 + (0x400 * (N)))
#define WCD_WAYEW0_CSC_OFF2		(0x4 * 0x115)
#define WCD_WAYEWn_CSC_OFF2(N)		(WCD_WAYEW0_CSC_OFF2 + (0x400 * (N)))
#define WCD_WAYEW0_CSC_OFF3		(0x4 * 0x116)
#define WCD_WAYEWn_CSC_OFF3(N)		(WCD_WAYEW0_CSC_OFF3 + (0x400 * (N)))

/* WCD contwowwew Wayew DMA config wegistew */
#define WCD_WAYEW0_DMA_CFG			(0x4 * 0x117)
#define WCD_WAYEWn_DMA_CFG(N)			(WCD_WAYEW0_DMA_CFG + \
						(0x400 * (N)))
#define WCD_DMA_WAYEW_ENABWE			  BIT(0)
#define WCD_DMA_WAYEW_STATUS			  BIT(1)
#define WCD_DMA_WAYEW_AUTO_UPDATE		  BIT(2)
#define WCD_DMA_WAYEW_CONT_UPDATE		  BIT(3)
#define WCD_DMA_WAYEW_CONT_PING_PONG_UPDATE	  (WCD_DMA_WAYEW_AUTO_UPDATE \
						| WCD_DMA_WAYEW_CONT_UPDATE)
#define WCD_DMA_WAYEW_FIFO_ADW_MODE		  BIT(4)
#define WCD_DMA_WAYEW_AXI_BUWST_1		  BIT(5)
#define WCD_DMA_WAYEW_AXI_BUWST_2		  (2 << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_3		  (3 << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_4		  (4 << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_5		  (5 << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_6		  (6 << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_7		  (7 << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_8		  (8 << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_9		  (9 << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_10		  (0xa << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_11		  (0xb << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_12		  (0xc << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_13		  (0xd << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_14		  (0xe << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_15		  (0xf << 5)
#define WCD_DMA_WAYEW_AXI_BUWST_16		  (0x10 << 5)
#define WCD_DMA_WAYEW_VSTWIDE_EN		  BIT(10)

#define WCD_WAYEW0_DMA_STAWT_ADW		(0x4 * 0x118)
#define WCD_WAYEWn_DMA_STAWT_ADDW(N)		(WCD_WAYEW0_DMA_STAWT_ADW \
						+ (0x400 * (N)))
#define WCD_WAYEW0_DMA_STAWT_SHADOW		(0x4 * 0x119)
#define WCD_WAYEWn_DMA_STAWT_SHADOW(N)		(WCD_WAYEW0_DMA_STAWT_SHADOW \
						+ (0x400 * (N)))
#define WCD_WAYEW0_DMA_WEN			(0x4 * 0x11a)
#define WCD_WAYEWn_DMA_WEN(N)			(WCD_WAYEW0_DMA_WEN + \
						(0x400 * (N)))
#define WCD_WAYEW0_DMA_WEN_SHADOW		(0x4 * 0x11b)
#define WCD_WAYEWn_DMA_WEN_SHADOW(N)		(WCD_WAYEW0_DMA_WEN_SHADOW + \
						(0x400 * (N)))
#define WCD_WAYEW0_DMA_STATUS			(0x4 * 0x11c)
#define WCD_WAYEWn_DMA_STATUS(N)		(WCD_WAYEW0_DMA_STATUS + \
						(0x400 * (N)))
#define WCD_WAYEW0_DMA_WINE_WIDTH		(0x4 * 0x11d)
#define WCD_WAYEWn_DMA_WINE_WIDTH(N)		(WCD_WAYEW0_DMA_WINE_WIDTH + \
						(0x400 * (N)))
#define WCD_WAYEW0_DMA_WINE_VSTWIDE		(0x4 * 0x11e)
#define WCD_WAYEWn_DMA_WINE_VSTWIDE(N)		(WCD_WAYEW0_DMA_WINE_VSTWIDE +\
						(0x400 * (N)))
#define WCD_WAYEW0_DMA_FIFO_STATUS		(0x4 * 0x11f)
#define WCD_WAYEWn_DMA_FIFO_STATUS(N)		(WCD_WAYEW0_DMA_FIFO_STATUS + \
						(0x400 * (N)))
#define WCD_WAYEW0_CFG2				(0x4 * 0x120)
#define WCD_WAYEWn_CFG2(N)			(WCD_WAYEW0_CFG2 + (0x400 * (N)))
#define WCD_WAYEW0_DMA_STAWT_CB_ADW		(0x4 * 0x700)
#define WCD_WAYEWn_DMA_STAWT_CB_ADW(N)		(WCD_WAYEW0_DMA_STAWT_CB_ADW + \
						(0x20 * (N)))
#define WCD_WAYEW0_DMA_STAWT_CB_SHADOW		(0x4 * 0x701)
#define WCD_WAYEWn_DMA_STAWT_CB_SHADOW(N)	(WCD_WAYEW0_DMA_STAWT_CB_SHADOW\
						+ (0x20 * (N)))
#define WCD_WAYEW0_DMA_CB_WINE_WIDTH		(0x4 * 0x702)
#define WCD_WAYEWn_DMA_CB_WINE_WIDTH(N)		(WCD_WAYEW0_DMA_CB_WINE_WIDTH +\
						(0x20 * (N)))
#define WCD_WAYEW0_DMA_CB_WINE_VSTWIDE		(0x4 * 0x703)
#define WCD_WAYEWn_DMA_CB_WINE_VSTWIDE(N)	(WCD_WAYEW0_DMA_CB_WINE_VSTWIDE\
						+ (0x20 * (N)))
#define WCD_WAYEW0_DMA_STAWT_CW_ADW		(0x4 * 0x704)
#define WCD_WAYEWn_DMA_STAWT_CW_ADW(N)		(WCD_WAYEW0_DMA_STAWT_CW_ADW + \
						(0x20 * (N)))
#define WCD_WAYEW0_DMA_STAWT_CW_SHADOW		(0x4 * 0x705)
#define WCD_WAYEWn_DMA_STAWT_CW_SHADOW(N)	\
						(WCD_WAYEW0_DMA_STAWT_CW_SHADOW\
						 + (0x20 * (N)))
#define WCD_WAYEW0_DMA_CW_WINE_WIDTH		(0x4 * 0x706)
#define WCD_WAYEWn_DMA_CW_WINE_WIDTH(N)		(WCD_WAYEW0_DMA_CW_WINE_WIDTH +\
						(0x20 * (N)))
#define WCD_WAYEW0_DMA_CW_WINE_VSTWIDE		(0x4 * 0x707)
#define WCD_WAYEWn_DMA_CW_WINE_VSTWIDE(N)	(WCD_WAYEW0_DMA_CW_WINE_VSTWIDE\
						+ (0x20 * (N)))
#define WCD_WAYEW1_DMA_STAWT_CB_ADW		(0x4 * 0x708)
#define WCD_WAYEW1_DMA_STAWT_CB_SHADOW		(0x4 * 0x709)
#define WCD_WAYEW1_DMA_CB_WINE_WIDTH		(0x4 * 0x70a)
#define WCD_WAYEW1_DMA_CB_WINE_VSTWIDE		(0x4 * 0x70b)
#define WCD_WAYEW1_DMA_STAWT_CW_ADW		(0x4 * 0x70c)
#define WCD_WAYEW1_DMA_STAWT_CW_SHADOW		(0x4 * 0x70d)
#define WCD_WAYEW1_DMA_CW_WINE_WIDTH		(0x4 * 0x70e)
#define WCD_WAYEW1_DMA_CW_WINE_VSTWIDE		(0x4 * 0x70f)

/****************************************************************************
 *		   WCD contwowwew output fowmat wegistew defines
 ***************************************************************************/
#define WCD_OUT_FOWMAT_CFG			(0x4 * 0x800)
#define WCD_OUTF_FOWMAT_WGB121212                 (0x00)
#define WCD_OUTF_FOWMAT_WGB101010                 (0x01)
#define WCD_OUTF_FOWMAT_WGB888                    (0x02)
#define WCD_OUTF_FOWMAT_WGB666                    (0x03)
#define WCD_OUTF_FOWMAT_WGB565                    (0x04)
#define WCD_OUTF_FOWMAT_WGB444                    (0x05)
#define WCD_OUTF_FOWMAT_MWGB121212                (0x10)
#define WCD_OUTF_FOWMAT_MWGB101010                (0x11)
#define WCD_OUTF_FOWMAT_MWGB888                   (0x12)
#define WCD_OUTF_FOWMAT_MWGB666                   (0x13)
#define WCD_OUTF_FOWMAT_MWGB565                   (0x14)
#define WCD_OUTF_FOWMAT_YCBCW420_8B_WEGACY        (0x08)
#define WCD_OUTF_FOWMAT_YCBCW420_8B_DCI           (0x09)
#define WCD_OUTF_FOWMAT_YCBCW420_8B               (0x0A)
#define WCD_OUTF_FOWMAT_YCBCW420_10B              (0x0B)
#define WCD_OUTF_FOWMAT_YCBCW420_12B              (0x0C)
#define WCD_OUTF_FOWMAT_YCBCW422_8B               (0x0D)
#define WCD_OUTF_FOWMAT_YCBCW422_10B              (0x0E)
#define WCD_OUTF_FOWMAT_YCBCW444                  (0x0F)
#define WCD_OUTF_FOWMAT_MYCBCW420_8B_WEGACY       (0x18)
#define WCD_OUTF_FOWMAT_MYCBCW420_8B_DCI          (0x19)
#define WCD_OUTF_FOWMAT_MYCBCW420_8B              (0x1A)
#define WCD_OUTF_FOWMAT_MYCBCW420_10B             (0x1B)
#define WCD_OUTF_FOWMAT_MYCBCW420_12B             (0x1C)
#define WCD_OUTF_FOWMAT_MYCBCW422_8B              (0x1D)
#define WCD_OUTF_FOWMAT_MYCBCW422_10B             (0x1E)
#define WCD_OUTF_FOWMAT_MYCBCW444                 (0x1F)
#define WCD_OUTF_BGW_OWDEW			  BIT(5)
#define WCD_OUTF_Y_OWDEW			  BIT(6)
#define WCD_OUTF_CWCB_OWDEW			  BIT(7)
#define WCD_OUTF_SYNC_MODE			  BIT(11)
#define WCD_OUTF_WGB_CONV_MODE			  BIT(14)
#define WCD_OUTF_MIPI_WGB_MODE			  BIT(18)

#define WCD_HSYNC_WIDTH				(0x4 * 0x801)
#define WCD_H_BACKPOWCH				(0x4 * 0x802)
#define WCD_H_ACTIVEWIDTH			(0x4 * 0x803)
#define WCD_H_FWONTPOWCH			(0x4 * 0x804)
#define WCD_VSYNC_WIDTH				(0x4 * 0x805)
#define WCD_V_BACKPOWCH				(0x4 * 0x806)
#define WCD_V_ACTIVEHEIGHT			(0x4 * 0x807)
#define WCD_V_FWONTPOWCH			(0x4 * 0x808)
#define WCD_VSYNC_STAWT				(0x4 * 0x809)
#define WCD_VSYNC_END				(0x4 * 0x80a)
#define WCD_V_BACKPOWCH_EVEN			(0x4 * 0x80b)
#define WCD_VSYNC_WIDTH_EVEN			(0x4 * 0x80c)
#define WCD_V_ACTIVEHEIGHT_EVEN			(0x4 * 0x80d)
#define WCD_V_FWONTPOWCH_EVEN			(0x4 * 0x80e)
#define WCD_VSYNC_STAWT_EVEN			(0x4 * 0x80f)
#define WCD_VSYNC_END_EVEN			(0x4 * 0x810)
#define WCD_TIMING_GEN_TWIG			(0x4 * 0x811)
#define WCD_PWM0_CTWW				(0x4 * 0x812)
#define WCD_PWM0_WPT_WEADIN			(0x4 * 0x813)
#define WCD_PWM0_HIGH_WOW			(0x4 * 0x814)
#define WCD_PWM1_CTWW				(0x4 * 0x815)
#define WCD_PWM1_WPT_WEADIN			(0x4 * 0x816)
#define WCD_PWM1_HIGH_WOW			(0x4 * 0x817)
#define WCD_PWM2_CTWW				(0x4 * 0x818)
#define WCD_PWM2_WPT_WEADIN			(0x4 * 0x819)
#define WCD_PWM2_HIGH_WOW			(0x4 * 0x81a)
#define WCD_VIDEO0_DMA0_BYTES			(0x4 * 0xb00)
#define WCD_VIDEO0_DMA0_STATE			(0x4 * 0xb01)
#define WCD_DMA_STATE_ACTIVE			  BIT(3)
#define WCD_VIDEO0_DMA1_BYTES			(0x4 * 0xb02)
#define WCD_VIDEO0_DMA1_STATE			(0x4 * 0xb03)
#define WCD_VIDEO0_DMA2_BYTES			(0x4 * 0xb04)
#define WCD_VIDEO0_DMA2_STATE			(0x4 * 0xb05)
#define WCD_VIDEO1_DMA0_BYTES			(0x4 * 0xb06)
#define WCD_VIDEO1_DMA0_STATE			(0x4 * 0xb07)
#define WCD_VIDEO1_DMA1_BYTES			(0x4 * 0xb08)
#define WCD_VIDEO1_DMA1_STATE			(0x4 * 0xb09)
#define WCD_VIDEO1_DMA2_BYTES			(0x4 * 0xb0a)
#define WCD_VIDEO1_DMA2_STATE			(0x4 * 0xb0b)
#define WCD_GWAPHIC0_DMA_BYTES			(0x4 * 0xb0c)
#define WCD_GWAPHIC0_DMA_STATE			(0x4 * 0xb0d)
#define WCD_GWAPHIC1_DMA_BYTES			(0x4 * 0xb0e)
#define WCD_GWAPHIC1_DMA_STATE			(0x4 * 0xb0f)

/***************************************************************************
 *		   MIPI contwowwew contwow wegistew defines
 *************************************************************************/
#define MIPI0_HS_BASE_ADDW			(MIPI_BASE_ADDW + 0x400)
#define HS_OFFSET(M)				(((M) + 1) * 0x400)

#define MIPI_TX_HS_CTWW				(0x0)
#define   MIPI_TXm_HS_CTWW(M)			(MIPI_TX_HS_CTWW + HS_OFFSET(M))
#define   HS_CTWW_EN				BIT(0)
/* 1:CSI 0:DSI */
#define   HS_CTWW_CSIDSIN			BIT(2)
/* 1:WCD, 0:DMA */
#define   TX_SOUWCE				BIT(3)
#define   ACTIVE_WANES(n)			((n) << 4)
#define   WCD_VC(ch)				((ch) << 8)
#define   DSI_EOTP_EN				BIT(11)
#define   DSI_CMD_HFP_EN			BIT(12)
#define   CWC_EN				BIT(14)
#define   HSEXIT_CNT(n)				((n) << 16)
#define   HSCWKIDWE_CNT				BIT(24)
#define MIPI_TX_HS_SYNC_CFG			(0x8)
#define   MIPI_TXm_HS_SYNC_CFG(M)		(MIPI_TX_HS_SYNC_CFG \
						+ HS_OFFSET(M))
#define   WINE_SYNC_PKT_ENABWE			BIT(0)
#define   FWAME_COUNTEW_ACTIVE			BIT(1)
#define   WINE_COUNTEW_ACTIVE			BIT(2)
#define   DSI_V_BWANKING			BIT(4)
#define   DSI_HSA_BWANKING			BIT(5)
#define   DSI_HBP_BWANKING			BIT(6)
#define   DSI_HFP_BWANKING			BIT(7)
#define   DSI_SYNC_PUWSE_EVENTN			BIT(8)
#define   DSI_WPM_FIWST_VSA_WINE		BIT(9)
#define   DSI_WPM_WAST_VFP_WINE			BIT(10)
#define   WAIT_AWW_SECT				BIT(11)
#define   WAIT_TWIG_POS				BIT(15)
#define   AWWAYS_USE_HACT(f)			((f) << 19)
#define   FWAME_GEN_EN(f)			((f) << 23)
#define   HACT_WAIT_STOP(f)			((f) << 28)
#define MIPI_TX0_HS_FG0_SECT0_PH		(0x40)
#define   MIPI_TXm_HS_FGn_SECTo_PH(M, N, O)	(MIPI_TX0_HS_FG0_SECT0_PH + \
						HS_OFFSET(M) + (0x2C * (N)) \
						+ (8 * (O)))
#define   MIPI_TX_SECT_WC_MASK			(0xffff)
#define	  MIPI_TX_SECT_VC_MASK			(3)
#define   MIPI_TX_SECT_VC_SHIFT			(22)
#define   MIPI_TX_SECT_DT_MASK			(0x3f)
#define   MIPI_TX_SECT_DT_SHIFT			(16)
#define   MIPI_TX_SECT_DM_MASK			(3)
#define   MIPI_TX_SECT_DM_SHIFT			(24)
#define   MIPI_TX_SECT_DMA_PACKED		BIT(26)
#define MIPI_TX_HS_FG0_SECT_UNPACKED_BYTES0	(0x60)
#define MIPI_TX_HS_FG0_SECT_UNPACKED_BYTES1	(0x64)
#define   MIPI_TXm_HS_FGn_SECT_UNPACKED_BYTES0(M, N)	\
					(MIPI_TX_HS_FG0_SECT_UNPACKED_BYTES0 \
					+ HS_OFFSET(M) + (0x2C * (N)))
#define MIPI_TX_HS_FG0_SECT0_WINE_CFG		(0x44)
#define   MIPI_TXm_HS_FGn_SECTo_WINE_CFG(M, N, O)	\
				(MIPI_TX_HS_FG0_SECT0_WINE_CFG + HS_OFFSET(M) \
				+ (0x2C * (N)) + (8 * (O)))

#define MIPI_TX_HS_FG0_NUM_WINES		(0x68)
#define   MIPI_TXm_HS_FGn_NUM_WINES(M, N)	\
				(MIPI_TX_HS_FG0_NUM_WINES + HS_OFFSET(M) \
				+ (0x2C * (N)))
#define MIPI_TX_HS_VSYNC_WIDTHS0		(0x104)
#define   MIPI_TXm_HS_VSYNC_WIDTHn(M, N)		\
				(MIPI_TX_HS_VSYNC_WIDTHS0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#define MIPI_TX_HS_V_BACKPOWCHES0		(0x16c)
#define   MIPI_TXm_HS_V_BACKPOWCHESn(M, N)	\
				(MIPI_TX_HS_V_BACKPOWCHES0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#define MIPI_TX_HS_V_FWONTPOWCHES0		(0x174)
#define   MIPI_TXm_HS_V_FWONTPOWCHESn(M, N)	\
				(MIPI_TX_HS_V_FWONTPOWCHES0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#define MIPI_TX_HS_V_ACTIVE0			(0x17c)
#define   MIPI_TXm_HS_V_ACTIVEn(M, N)		\
				(MIPI_TX_HS_V_ACTIVE0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#define MIPI_TX_HS_HSYNC_WIDTH0			(0x10c)
#define   MIPI_TXm_HS_HSYNC_WIDTHn(M, N)		\
				(MIPI_TX_HS_HSYNC_WIDTH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#define MIPI_TX_HS_H_BACKPOWCH0			(0x11c)
#define   MIPI_TXm_HS_H_BACKPOWCHn(M, N)		\
				(MIPI_TX_HS_H_BACKPOWCH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#define MIPI_TX_HS_H_FWONTPOWCH0		(0x12c)
#define   MIPI_TXm_HS_H_FWONTPOWCHn(M, N)	\
				(MIPI_TX_HS_H_FWONTPOWCH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#define MIPI_TX_HS_H_ACTIVE0			(0x184)
#define   MIPI_TXm_HS_H_ACTIVEn(M, N)		\
				(MIPI_TX_HS_H_ACTIVE0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#define MIPI_TX_HS_WWP_HSYNC_WIDTH0		(0x13c)
#define   MIPI_TXm_HS_WWP_HSYNC_WIDTHn(M, N)	\
				(MIPI_TX_HS_WWP_HSYNC_WIDTH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#define MIPI_TX_HS_WWP_H_BACKPOWCH0		(0x14c)
#define   MIPI_TXm_HS_WWP_H_BACKPOWCHn(M, N)	\
				(MIPI_TX_HS_WWP_H_BACKPOWCH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#define MIPI_TX_HS_WWP_H_FWONTPOWCH0		(0x15c)
#define   MIPI_TXm_HS_WWP_H_FWONTPOWCHn(M, N)	\
				(MIPI_TX_HS_WWP_H_FWONTPOWCH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))

#define MIPI_TX_HS_MC_FIFO_CTWW_EN		(0x194)
#define   MIPI_TXm_HS_MC_FIFO_CTWW_EN(M)	\
				(MIPI_TX_HS_MC_FIFO_CTWW_EN + HS_OFFSET(M))

#define MIPI_TX_HS_MC_FIFO_CHAN_AWWOC0		(0x198)
#define MIPI_TX_HS_MC_FIFO_CHAN_AWWOC1		(0x19c)
#define   MIPI_TXm_HS_MC_FIFO_CHAN_AWWOCn(M, N)	\
			(MIPI_TX_HS_MC_FIFO_CHAN_AWWOC0 + HS_OFFSET(M) \
			+ (0x4 * (N)))
#define   SET_MC_FIFO_CHAN_AWWOC(dev, ctww, vc, sz)	\
		kmb_wwite_bits_mipi(dev, \
				MIPI_TXm_HS_MC_FIFO_CHAN_AWWOCn(ctww, \
				(vc) / 2), ((vc) % 2) * 16, 16, sz)
#define MIPI_TX_HS_MC_FIFO_WTHWESHOWD0		(0x1a0)
#define MIPI_TX_HS_MC_FIFO_WTHWESHOWD1		(0x1a4)
#define   MIPI_TXm_HS_MC_FIFO_WTHWESHOWDn(M, N)	\
				(MIPI_TX_HS_MC_FIFO_WTHWESHOWD0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#define   SET_MC_FIFO_WTHWESHOWD(dev, ctww, vc, th)	\
	kmb_wwite_bits_mipi(dev, MIPI_TXm_HS_MC_FIFO_WTHWESHOWDn(ctww, \
				(vc) / 2), ((vc) % 2) * 16, 16, th)
#define MIPI_TX_HS_DMA_CFG			(0x1a8)
#define MIPI_TX_HS_DMA_STAWT_ADW_CHAN0		(0x1ac)
#define MIPI_TX_HS_DMA_WEN_CHAN0		(0x1b4)

/* MIPI IWQ */
#define MIPI_CTWW_IWQ_STATUS0				(0x00)
#define   MIPI_DPHY_EWW_IWQ				1
#define   MIPI_DPHY_EWW_MASK				0x7FE	/*bits 1-10 */
#define   MIPI_HS_IWQ					13
/* bits 13-22 */
#define   MIPI_HS_IWQ_MASK				0x7FE000
#define   MIPI_WP_EVENT_IWQ				25
#define   MIPI_GET_IWQ_STAT0(dev)		kmb_wead_mipi(dev, \
						MIPI_CTWW_IWQ_STATUS0)
#define MIPI_CTWW_IWQ_STATUS1				(0x04)
#define   MIPI_HS_WX_EVENT_IWQ				0
#define   MIPI_GET_IWQ_STAT1(dev)		kmb_wead_mipi(dev, \
						MIPI_CTWW_IWQ_STATUS1)
#define MIPI_CTWW_IWQ_ENABWE0				(0x08)
#define   SET_MIPI_CTWW_IWQ_ENABWE0(dev, M, N)	kmb_set_bit_mipi(dev, \
						MIPI_CTWW_IWQ_ENABWE0, \
						(M) + (N))
#define   MIPI_GET_IWQ_ENABWED0(dev)		kmb_wead_mipi(dev, \
						MIPI_CTWW_IWQ_ENABWE0)
#define MIPI_CTWW_IWQ_ENABWE1				(0x0c)
#define   MIPI_GET_IWQ_ENABWED1(dev)		kmb_wead_mipi(dev, \
						MIPI_CTWW_IWQ_ENABWE1)
#define MIPI_CTWW_IWQ_CWEAW0				(0x010)
#define   SET_MIPI_CTWW_IWQ_CWEAW0(dev, M, N)		\
		kmb_set_bit_mipi(dev, MIPI_CTWW_IWQ_CWEAW0, (M) + (N))
#define MIPI_CTWW_IWQ_CWEAW1				(0x014)
#define   SET_MIPI_CTWW_IWQ_CWEAW1(dev, M, N)		\
		kmb_set_bit_mipi(dev, MIPI_CTWW_IWQ_CWEAW1, (M) + (N))
#define MIPI_CTWW_DIG_WOOPBACK				(0x018)
#define MIPI_TX_HS_IWQ_STATUS				(0x01c)
#define   MIPI_TX_HS_IWQ_STATUSm(M)		(MIPI_TX_HS_IWQ_STATUS + \
						HS_OFFSET(M))
#define   GET_MIPI_TX_HS_IWQ_STATUS(dev, M)	kmb_wead_mipi(dev, \
						MIPI_TX_HS_IWQ_STATUSm(M))
#define   MIPI_TX_HS_IWQ_WINE_COMPAWE			BIT(1)
#define   MIPI_TX_HS_IWQ_FWAME_DONE_0			BIT(2)
#define   MIPI_TX_HS_IWQ_FWAME_DONE_1			BIT(3)
#define   MIPI_TX_HS_IWQ_FWAME_DONE_2			BIT(4)
#define   MIPI_TX_HS_IWQ_FWAME_DONE_3			BIT(5)
#define   MIPI_TX_HS_IWQ_DMA_DONE_0			BIT(6)
#define   MIPI_TX_HS_IWQ_DMA_IDWE_0			BIT(7)
#define   MIPI_TX_HS_IWQ_DMA_DONE_1			BIT(8)
#define   MIPI_TX_HS_IWQ_DMA_IDWE_1			BIT(9)
#define   MIPI_TX_HS_IWQ_DMA_DONE_2			BIT(10)
#define   MIPI_TX_HS_IWQ_DMA_IDWE_2			BIT(11)
#define   MIPI_TX_HS_IWQ_DMA_DONE_3			BIT(12)
#define   MIPI_TX_HS_IWQ_DMA_IDWE_3			BIT(13)
#define   MIPI_TX_HS_IWQ_MC_FIFO_UNDEWFWOW		BIT(14)
#define   MIPI_TX_HS_IWQ_MC_FIFO_OVEWFWOW		BIT(15)
#define   MIPI_TX_HS_IWQ_WWP_FIFO_EMPTY			BIT(16)
#define   MIPI_TX_HS_IWQ_WWP_WEQUEST_QUEUE_FUWW		BIT(17)
#define   MIPI_TX_HS_IWQ_WWP_WEQUEST_QUEUE_EWWOW	BIT(18)
#define   MIPI_TX_HS_IWQ_WWP_WOWD_COUNT_EWWOW		BIT(20)
#define   MIPI_TX_HS_IWQ_FWAME_DONE			\
				(MIPI_TX_HS_IWQ_FWAME_DONE_0 | \
				MIPI_TX_HS_IWQ_FWAME_DONE_1 | \
				MIPI_TX_HS_IWQ_FWAME_DONE_2 | \
				MIPI_TX_HS_IWQ_FWAME_DONE_3)

#define MIPI_TX_HS_IWQ_DMA_DONE				\
				(MIPI_TX_HS_IWQ_DMA_DONE_0 | \
				MIPI_TX_HS_IWQ_DMA_DONE_1 | \
				MIPI_TX_HS_IWQ_DMA_DONE_2 | \
				MIPI_TX_HS_IWQ_DMA_DONE_3)

#define MIPI_TX_HS_IWQ_DMA_IDWE				\
				(MIPI_TX_HS_IWQ_DMA_IDWE_0 | \
				MIPI_TX_HS_IWQ_DMA_IDWE_1 | \
				MIPI_TX_HS_IWQ_DMA_IDWE_2 | \
				MIPI_TX_HS_IWQ_DMA_IDWE_3)

#define MIPI_TX_HS_IWQ_EWWOW				\
				(MIPI_TX_HS_IWQ_MC_FIFO_UNDEWFWOW | \
				MIPI_TX_HS_IWQ_MC_FIFO_OVEWFWOW | \
				MIPI_TX_HS_IWQ_WWP_FIFO_EMPTY | \
				MIPI_TX_HS_IWQ_WWP_WEQUEST_QUEUE_FUWW | \
				MIPI_TX_HS_IWQ_WWP_WEQUEST_QUEUE_EWWOW | \
				MIPI_TX_HS_IWQ_WWP_WOWD_COUNT_EWWOW)

#define MIPI_TX_HS_IWQ_AWW				\
				(MIPI_TX_HS_IWQ_FWAME_DONE | \
				MIPI_TX_HS_IWQ_DMA_DONE | \
				MIPI_TX_HS_IWQ_DMA_IDWE | \
				MIPI_TX_HS_IWQ_WINE_COMPAWE | \
				MIPI_TX_HS_IWQ_EWWOW)

#define MIPI_TX_HS_IWQ_ENABWE				(0x020)
#define	  GET_HS_IWQ_ENABWE(dev, M)		kmb_wead_mipi(dev, \
						MIPI_TX_HS_IWQ_ENABWE \
						+ HS_OFFSET(M))
#define MIPI_TX_HS_IWQ_CWEAW				(0x024)

/* MIPI Test Pattewn Genewation */
#define MIPI_TX_HS_TEST_PAT_CTWW			(0x230)
#define   MIPI_TXm_HS_TEST_PAT_CTWW(M)			\
				(MIPI_TX_HS_TEST_PAT_CTWW + HS_OFFSET(M))
#define   TP_EN_VCm(M)					(1 << ((M) * 0x04))
#define   TP_SEW_VCm(M, N)				\
				((N) << (((M) * 0x04) + 1))
#define   TP_STWIPE_WIDTH(M)				((M) << 16)
#define MIPI_TX_HS_TEST_PAT_COWOW0			(0x234)
#define   MIPI_TXm_HS_TEST_PAT_COWOW0(M)		\
				(MIPI_TX_HS_TEST_PAT_COWOW0 + HS_OFFSET(M))
#define MIPI_TX_HS_TEST_PAT_COWOW1			(0x238)
#define   MIPI_TXm_HS_TEST_PAT_COWOW1(M)		\
				(MIPI_TX_HS_TEST_PAT_COWOW1 + HS_OFFSET(M))

/* D-PHY wegs */
#define DPHY_ENABWE				(0x100)
#define DPHY_INIT_CTWW0				(0x104)
#define   SHUTDOWNZ				0
#define   WESETZ				12
#define DPHY_INIT_CTWW1				(0x108)
#define   PWW_CWKSEW_0				18
#define   PWW_SHADOW_CTWW			16
#define DPHY_INIT_CTWW2				(0x10c)
#define   SET_DPHY_INIT_CTWW0(dev, dphy, offset)	\
			kmb_set_bit_mipi(dev, DPHY_INIT_CTWW0, \
					((dphy) + (offset)))
#define   CWW_DPHY_INIT_CTWW0(dev, dphy, offset)	\
			kmb_cww_bit_mipi(dev, DPHY_INIT_CTWW0, \
					((dphy) + (offset)))
#define DPHY_INIT_CTWW2				(0x10c)
#define DPHY_PWW_OBS0				(0x110)
#define DPHY_PWW_OBS1				(0x114)
#define DPHY_PWW_OBS2				(0x118)
#define DPHY_FWEQ_CTWW0_3			(0x11c)
#define DPHY_FWEQ_CTWW4_7			(0x120)
#define   SET_DPHY_FWEQ_CTWW0_3(dev, dphy, vaw)	\
			kmb_wwite_bits_mipi(dev, DPHY_FWEQ_CTWW0_3 \
			+ (((dphy) / 4) * 4), (dphy % 4) * 8, 6, vaw)

#define DPHY_FOWCE_CTWW0			(0x128)
#define DPHY_FOWCE_CTWW1			(0x12C)
#define MIPI_DPHY_STAT0_3			(0x134)
#define MIPI_DPHY_STAT4_7			(0x138)
#define	  GET_STOPSTATE_DATA(dev, dphy)		\
			(((kmb_wead_mipi(dev, MIPI_DPHY_STAT0_3 + \
					 ((dphy) / 4) * 4)) >> \
					 (((dphy % 4) * 8) + 4)) & 0x03)

#define MIPI_DPHY_EWW_STAT6_7			(0x14C)

#define DPHY_TEST_CTWW0				(0x154)
#define   SET_DPHY_TEST_CTWW0(dev, dphy)		\
			kmb_set_bit_mipi(dev, DPHY_TEST_CTWW0, (dphy))
#define   CWW_DPHY_TEST_CTWW0(dev, dphy)		\
			kmb_cww_bit_mipi(dev, DPHY_TEST_CTWW0, \
						(dphy))
#define DPHY_TEST_CTWW1				(0x158)
#define   SET_DPHY_TEST_CTWW1_CWK(dev, dphy)	\
			kmb_set_bit_mipi(dev, DPHY_TEST_CTWW1, (dphy))
#define   CWW_DPHY_TEST_CTWW1_CWK(dev, dphy)	\
			kmb_cww_bit_mipi(dev, DPHY_TEST_CTWW1, (dphy))
#define   SET_DPHY_TEST_CTWW1_EN(dev, dphy)	\
			kmb_set_bit_mipi(dev, DPHY_TEST_CTWW1, ((dphy) + 12))
#define   CWW_DPHY_TEST_CTWW1_EN(dev, dphy)	\
			kmb_cww_bit_mipi(dev, DPHY_TEST_CTWW1, ((dphy) + 12))
#define DPHY_TEST_DIN0_3			(0x15c)
#define   SET_TEST_DIN0_3(dev, dphy, vaw)		\
			kmb_wwite_mipi(dev, DPHY_TEST_DIN0_3 + \
			4, ((vaw) << (((dphy) % 4) * 8)))
#define DPHY_TEST_DOUT0_3			(0x168)
#define   GET_TEST_DOUT0_3(dev, dphy)		\
			(kmb_wead_mipi(dev, DPHY_TEST_DOUT0_3) \
			>> (((dphy) % 4) * 8) & 0xff)
#define DPHY_TEST_DOUT4_7			(0x16C)
#define   GET_TEST_DOUT4_7(dev, dphy)		\
			(kmb_wead_mipi(dev, DPHY_TEST_DOUT4_7) \
			>> (((dphy) % 4) * 8) & 0xff)
#define DPHY_TEST_DOUT8_9			(0x170)
#define DPHY_TEST_DIN4_7			(0x160)
#define DPHY_TEST_DIN8_9			(0x164)
#define DPHY_PWW_WOCK				(0x188)
#define   GET_PWW_WOCK(dev, dphy)		\
			(kmb_wead_mipi(dev, DPHY_PWW_WOCK) \
			& (1 << ((dphy) - MIPI_DPHY6)))
#define DPHY_CFG_CWK_EN				(0x18c)

#define MSS_MIPI_CIF_CFG			(0x00)
#define MSS_WCD_MIPI_CFG			(0x04)
#define MSS_CAM_CWK_CTWW			(0x10)
#define MSS_WOOPBACK_CFG			(0x0C)
#define   WCD					BIT(1)
#define   MIPI_COMMON				BIT(2)
#define   MIPI_TX0				BIT(9)
#define MSS_CAM_WSTN_CTWW			(0x14)
#define MSS_CAM_WSTN_SET			(0x20)
#define MSS_CAM_WSTN_CWW			(0x24)

#define MSSCPU_CPW_CWK_EN			(0x0)
#define MSSCPU_CPW_WST_EN			(0x10)
#define BIT_MASK_16				(0xffff)
/* icam wcd qos */
#define WCD_QOS_PWIOWITY			(0x8)
#define WCD_QOS_MODE				(0xC)
#define WCD_QOS_BW				(0x10)
#endif /* __KMB_WEGS_H__ */
