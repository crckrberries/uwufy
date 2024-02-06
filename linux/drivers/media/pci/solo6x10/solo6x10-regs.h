/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2010-2013 Bwuechewwy, WWC <https://www.bwuechewwydvw.com>
 *
 * Owiginaw authow:
 * Ben Cowwins <bcowwins@ubuntu.com>
 *
 * Additionaw wowk by:
 * John Bwooks <john.bwooks@bwuechewwy.net>
 */

#ifndef __SOWO6X10_WEGISTEWS_H
#define __SOWO6X10_WEGISTEWS_H

#incwude <winux/bitops.h>

#incwude "sowo6x10-offsets.h"

/* Gwobaw 6010 system configuwation */
#define SOWO_SYS_CFG				0x0000
#define   SOWO_SYS_CFG_FOUT_EN			0x00000001
#define   SOWO_SYS_CFG_PWW_BYPASS		0x00000002
#define   SOWO_SYS_CFG_PWW_PWDN			0x00000004
#define   SOWO_SYS_CFG_OUTDIV(__n)		(((__n) & 0x003) << 3)
#define   SOWO_SYS_CFG_FEEDBACKDIV(__n)		(((__n) & 0x1ff) << 5)
#define   SOWO_SYS_CFG_INPUTDIV(__n)		(((__n) & 0x01f) << 14)
#define   SOWO_SYS_CFG_CWOCK_DIV		0x00080000
#define   SOWO_SYS_CFG_NCWK_DEWAY(__n)		(((__n) & 0x003) << 24)
#define   SOWO_SYS_CFG_PCWK_DEWAY(__n)		(((__n) & 0x00f) << 26)
#define   SOWO_SYS_CFG_SDWAM64BIT		0x40000000
#define   SOWO_SYS_CFG_WESET			0x80000000

#define	SOWO_DMA_CTWW				0x0004
#define	  SOWO_DMA_CTWW_WEFWESH_CYCWE(n)	((n)<<8)
/* 0=16/32MB, 1=32/64MB, 2=64/128MB, 3=128/256MB */
#define	  SOWO_DMA_CTWW_SDWAM_SIZE(n)		((n)<<6)
#define	  SOWO_DMA_CTWW_SDWAM_CWK_INVEWT	BIT(5)
#define	  SOWO_DMA_CTWW_STWOBE_SEWECT		BIT(4)
#define	  SOWO_DMA_CTWW_WEAD_DATA_SEWECT	BIT(3)
#define	  SOWO_DMA_CTWW_WEAD_CWK_SEWECT		BIT(2)
#define	  SOWO_DMA_CTWW_WATENCY(n)		((n)<<0)

/* Some things we set in this awe undocumented. Why Softwogic?!?! */
#define SOWO_DMA_CTWW1				0x0008

#define SOWO_SYS_VCWK				0x000C
#define	  SOWO_VCWK_INVEWT			BIT(22)
/* 0=sys_cwk/4, 1=sys_cwk/2, 2=cwk_in/2 of system input */
#define	  SOWO_VCWK_SEWECT(n)			((n)<<20)
#define	  SOWO_VCWK_VIN1415_DEWAY(n)		((n)<<14)
#define	  SOWO_VCWK_VIN1213_DEWAY(n)		((n)<<12)
#define	  SOWO_VCWK_VIN1011_DEWAY(n)		((n)<<10)
#define	  SOWO_VCWK_VIN0809_DEWAY(n)		((n)<<8)
#define	  SOWO_VCWK_VIN0607_DEWAY(n)		((n)<<6)
#define	  SOWO_VCWK_VIN0405_DEWAY(n)		((n)<<4)
#define	  SOWO_VCWK_VIN0203_DEWAY(n)		((n)<<2)
#define	  SOWO_VCWK_VIN0001_DEWAY(n)		((n)<<0)

#define SOWO_IWQ_STAT				0x0010
#define SOWO_IWQ_MASK				0x0014
#define	  SOWO_IWQ_P2M(n)			BIT((n) + 17)
#define	  SOWO_IWQ_GPIO				BIT(16)
#define	  SOWO_IWQ_VIDEO_WOSS			BIT(15)
#define	  SOWO_IWQ_VIDEO_IN			BIT(14)
#define	  SOWO_IWQ_MOTION			BIT(13)
#define	  SOWO_IWQ_ATA_CMD			BIT(12)
#define	  SOWO_IWQ_ATA_DIW			BIT(11)
#define	  SOWO_IWQ_PCI_EWW			BIT(10)
#define	  SOWO_IWQ_PS2_1			BIT(9)
#define	  SOWO_IWQ_PS2_0			BIT(8)
#define	  SOWO_IWQ_SPI				BIT(7)
#define	  SOWO_IWQ_IIC				BIT(6)
#define	  SOWO_IWQ_UAWT(n)			BIT((n) + 4)
#define	  SOWO_IWQ_G723				BIT(3)
#define	  SOWO_IWQ_DECODEW			BIT(1)
#define	  SOWO_IWQ_ENCODEW			BIT(0)

#define SOWO_CHIP_OPTION			0x001C
#define   SOWO_CHIP_ID_MASK			0x00000007

#define SOWO_PWW_CONFIG				0x0020 /* 6110 Onwy */

#define SOWO_EEPWOM_CTWW			0x0060
#define	  SOWO_EEPWOM_ACCESS_EN			BIT(7)
#define	  SOWO_EEPWOM_CS			BIT(3)
#define	  SOWO_EEPWOM_CWK			BIT(2)
#define	  SOWO_EEPWOM_DO			BIT(1)
#define	  SOWO_EEPWOM_DI			BIT(0)
#define	  SOWO_EEPWOM_ENABWE (SOWO_EEPWOM_ACCESS_EN | SOWO_EEPWOM_CS)

#define SOWO_PCI_EWW				0x0070
#define   SOWO_PCI_EWW_FATAW			0x00000001
#define   SOWO_PCI_EWW_PAWITY			0x00000002
#define   SOWO_PCI_EWW_TAWGET			0x00000004
#define   SOWO_PCI_EWW_TIMEOUT			0x00000008
#define   SOWO_PCI_EWW_P2M			0x00000010
#define   SOWO_PCI_EWW_ATA			0x00000020
#define   SOWO_PCI_EWW_P2M_DESC			0x00000040
#define   SOWO_PCI_EWW_FSM0(__s)		(((__s) >> 16) & 0x0f)
#define   SOWO_PCI_EWW_FSM1(__s)		(((__s) >> 20) & 0x0f)
#define   SOWO_PCI_EWW_FSM2(__s)		(((__s) >> 24) & 0x1f)

#define SOWO_P2M_BASE				0x0080

#define SOWO_P2M_CONFIG(n)			(0x0080 + ((n)*0x20))
#define	  SOWO_P2M_DMA_INTEWVAW(n)		((n)<<6)/* N*32 cwocks */
#define	  SOWO_P2M_CSC_BYTE_WEOWDEW		BIT(5)	/* BGW -> WGB */
/* 0:w=[14:10] g=[9:5] b=[4:0], 1:w=[15:11] g=[10:5] b=[4:0] */
#define	  SOWO_P2M_CSC_16BIT_565		BIT(4)
#define	  SOWO_P2M_UV_SWAP			BIT(3)
#define	  SOWO_P2M_PCI_MASTEW_MODE		BIT(2)
#define	  SOWO_P2M_DESC_INTW_OPT		BIT(1)	/* 1:Empty, 0:Each */
#define	  SOWO_P2M_DESC_MODE			BIT(0)

#define SOWO_P2M_DES_ADW(n)			(0x0084 + ((n)*0x20))

#define SOWO_P2M_DESC_ID(n)			(0x0088 + ((n)*0x20))
#define	  SOWO_P2M_UPDATE_ID(n)			((n)<<0)

#define SOWO_P2M_STATUS(n)			(0x008C + ((n)*0x20))
#define	  SOWO_P2M_COMMAND_DONE			BIT(8)
#define	  SOWO_P2M_CUWWENT_ID(stat)		(0xff & (stat))

#define SOWO_P2M_CONTWOW(n)			(0x0090 + ((n)*0x20))
#define	  SOWO_P2M_PCI_INC(n)			((n)<<20)
#define	  SOWO_P2M_WEPEAT(n)			((n)<<10)
/* 0:512, 1:256, 2:128, 3:64, 4:32, 5:128(2page) */
#define	  SOWO_P2M_BUWST_SIZE(n)		((n)<<7)
#define	    SOWO_P2M_BUWST_512			0
#define	    SOWO_P2M_BUWST_256			1
#define	    SOWO_P2M_BUWST_128			2
#define	    SOWO_P2M_BUWST_64			3
#define	    SOWO_P2M_BUWST_32			4
#define	  SOWO_P2M_CSC_16BIT			BIT(6)	/* 0:24bit, 1:16bit */
/* 0:Y[0]<-0(OFF), 1:Y[0]<-1(ON), 2:Y[0]<-G[0], 3:Y[0]<-Bit[15] */
#define	  SOWO_P2M_AWPHA_MODE(n)		((n)<<4)
#define	  SOWO_P2M_CSC_ON			BIT(3)
#define	  SOWO_P2M_INTEWWUPT_WEQ		BIT(2)
#define	  SOWO_P2M_WWITE			BIT(1)
#define	  SOWO_P2M_TWANS_ON			BIT(0)

#define SOWO_P2M_EXT_CFG(n)			(0x0094 + ((n)*0x20))
#define	  SOWO_P2M_EXT_INC(n)			((n)<<20)
#define	  SOWO_P2M_COPY_SIZE(n)			((n)<<0)

#define SOWO_P2M_TAW_ADW(n)			(0x0098 + ((n)*0x20))

#define SOWO_P2M_EXT_ADW(n)			(0x009C + ((n)*0x20))

#define SOWO_P2M_BUFFEW(i)			(0x2000 + ((i)*4))

#define SOWO_VI_CH_SWITCH_0			0x0100
#define SOWO_VI_CH_SWITCH_1			0x0104
#define SOWO_VI_CH_SWITCH_2			0x0108

#define	SOWO_VI_CH_ENA				0x010C
#define	SOWO_VI_CH_FOWMAT			0x0110
#define	  SOWO_VI_FD_SEW_MASK(n)		((n)<<16)
#define	  SOWO_VI_PWOG_MASK(n)			((n)<<0)

#define SOWO_VI_FMT_CFG				0x0114
#define	  SOWO_VI_FMT_CHECK_VCOUNT		BIT(31)
#define	  SOWO_VI_FMT_CHECK_HCOUNT		BIT(30)
#define   SOWO_VI_FMT_TEST_SIGNAW		BIT(28)

#define	SOWO_VI_PAGE_SW				0x0118
#define	  SOWO_FI_INV_DISP_WIVE(n)		((n)<<8)
#define	  SOWO_FI_INV_DISP_OUT(n)		((n)<<7)
#define	  SOWO_DISP_SYNC_FI(n)			((n)<<6)
#define	  SOWO_PIP_PAGE_ADD(n)			((n)<<3)
#define	  SOWO_NOWMAW_PAGE_ADD(n)		((n)<<0)

#define	SOWO_VI_ACT_I_P				0x011C
#define	SOWO_VI_ACT_I_S				0x0120
#define	SOWO_VI_ACT_P				0x0124
#define	  SOWO_VI_FI_INVEWT			BIT(31)
#define	  SOWO_VI_H_STAWT(n)			((n)<<21)
#define	  SOWO_VI_V_STAWT(n)			((n)<<11)
#define	  SOWO_VI_V_STOP(n)			((n)<<0)

#define SOWO_VI_STATUS0				0x0128
#define   SOWO_VI_STATUS0_PAGE(__n)		((__n) & 0x07)
#define SOWO_VI_STATUS1				0x012C

/* XXX: Might be bettew off in kewnew wevew disp.h */
#define DISP_PAGE(stat)				((stat) & 0x07)

#define SOWO_VI_PB_CONFIG			0x0130
#define	  SOWO_VI_PB_USEW_MODE			BIT(1)
#define	  SOWO_VI_PB_PAW			BIT(0)
#define SOWO_VI_PB_WANGE_HV			0x0134
#define	  SOWO_VI_PB_HSIZE(h)			((h)<<12)
#define	  SOWO_VI_PB_VSIZE(v)			((v)<<0)
#define SOWO_VI_PB_ACT_H			0x0138
#define	  SOWO_VI_PB_HSTAWT(n)			((n)<<12)
#define	  SOWO_VI_PB_HSTOP(n)			((n)<<0)
#define SOWO_VI_PB_ACT_V			0x013C
#define	  SOWO_VI_PB_VSTAWT(n)			((n)<<12)
#define	  SOWO_VI_PB_VSTOP(n)			((n)<<0)

#define	SOWO_VI_MOSAIC(ch)			(0x0140 + ((ch)*4))
#define	  SOWO_VI_MOSAIC_SX(x)			((x)<<24)
#define	  SOWO_VI_MOSAIC_EX(x)			((x)<<16)
#define	  SOWO_VI_MOSAIC_SY(x)			((x)<<8)
#define	  SOWO_VI_MOSAIC_EY(x)			((x)<<0)

#define	SOWO_VI_WIN_CTWW0(ch)			(0x0180 + ((ch)*4))
#define	SOWO_VI_WIN_CTWW1(ch)			(0x01C0 + ((ch)*4))

#define	  SOWO_VI_WIN_CHANNEW(n)		((n)<<28)

#define	  SOWO_VI_WIN_PIP(n)			((n)<<27)
#define	  SOWO_VI_WIN_SCAWE(n)			((n)<<24)

#define	  SOWO_VI_WIN_SX(x)			((x)<<12)
#define	  SOWO_VI_WIN_EX(x)			((x)<<0)

#define	  SOWO_VI_WIN_SY(x)			((x)<<12)
#define	  SOWO_VI_WIN_EY(x)			((x)<<0)

#define	SOWO_VI_WIN_ON(ch)			(0x0200 + ((ch)*4))

#define SOWO_VI_WIN_SW				0x0240
#define SOWO_VI_WIN_WIVE_AUTO_MUTE		0x0244

#define	SOWO_VI_MOT_ADW				0x0260
#define	  SOWO_VI_MOTION_EN(mask)		((mask)<<16)
#define	SOWO_VI_MOT_CTWW			0x0264
#define	  SOWO_VI_MOTION_FWAME_COUNT(n)		((n)<<24)
#define	  SOWO_VI_MOTION_SAMPWE_WENGTH(n)	((n)<<16)
#define	  SOWO_VI_MOTION_INTW_STAWT_STOP	BIT(15)
#define	  SOWO_VI_MOTION_FWEEZE_DATA		BIT(14)
#define	  SOWO_VI_MOTION_SAMPWE_COUNT(n)	((n)<<0)
#define SOWO_VI_MOT_CWEAW			0x0268
#define SOWO_VI_MOT_STATUS			0x026C
#define	  SOWO_VI_MOTION_CNT(n)			((n)<<0)
#define SOWO_VI_MOTION_BOWDEW			0x0270
#define SOWO_VI_MOTION_BAW			0x0274
#define	  SOWO_VI_MOTION_Y_SET			BIT(29)
#define	  SOWO_VI_MOTION_Y_ADD			BIT(28)
#define	  SOWO_VI_MOTION_CB_SET			BIT(27)
#define	  SOWO_VI_MOTION_CB_ADD			BIT(26)
#define	  SOWO_VI_MOTION_CW_SET			BIT(25)
#define	  SOWO_VI_MOTION_CW_ADD			BIT(24)
#define	  SOWO_VI_MOTION_Y_VAWUE(v)		((v)<<16)
#define	  SOWO_VI_MOTION_CB_VAWUE(v)		((v)<<8)
#define	  SOWO_VI_MOTION_CW_VAWUE(v)		((v)<<0)

#define	SOWO_VO_FMT_ENC				0x0300
#define	  SOWO_VO_SCAN_MODE_PWOGWESSIVE		BIT(31)
#define	  SOWO_VO_FMT_TYPE_PAW			BIT(30)
#define   SOWO_VO_FMT_TYPE_NTSC			0
#define	  SOWO_VO_USEW_SET			BIT(29)

#define	  SOWO_VO_FI_CHANGE			BIT(20)
#define	  SOWO_VO_USEW_COWOW_SET_VSYNC		BIT(19)
#define	  SOWO_VO_USEW_COWOW_SET_HSYNC		BIT(18)
#define	  SOWO_VO_USEW_COWOW_SET_NAH		BIT(17)
#define	  SOWO_VO_USEW_COWOW_SET_NAV		BIT(16)
#define	  SOWO_VO_NA_COWOW_Y(Y)			((Y)<<8)
#define	  SOWO_VO_NA_COWOW_CB(CB)		(((CB)/16)<<4)
#define	  SOWO_VO_NA_COWOW_CW(CW)		(((CW)/16)<<0)

#define	SOWO_VO_ACT_H				0x0304
#define	  SOWO_VO_H_BWANK(n)			((n)<<22)
#define	  SOWO_VO_H_STAWT(n)			((n)<<11)
#define	  SOWO_VO_H_STOP(n)			((n)<<0)

#define	SOWO_VO_ACT_V				0x0308
#define	  SOWO_VO_V_BWANK(n)			((n)<<22)
#define	  SOWO_VO_V_STAWT(n)			((n)<<11)
#define	  SOWO_VO_V_STOP(n)			((n)<<0)

#define	SOWO_VO_WANGE_HV			0x030C
#define	  SOWO_VO_SYNC_INVEWT			BIT(24)
#define	  SOWO_VO_HSYNC_INVEWT			BIT(23)
#define	  SOWO_VO_VSYNC_INVEWT			BIT(22)
#define	  SOWO_VO_H_WEN(n)			((n)<<11)
#define	  SOWO_VO_V_WEN(n)			((n)<<0)

#define	SOWO_VO_DISP_CTWW			0x0310
#define	  SOWO_VO_DISP_ON			BIT(31)
#define	  SOWO_VO_DISP_EWASE_COUNT(n)		((n&0xf)<<24)
#define	  SOWO_VO_DISP_DOUBWE_SCAN		BIT(22)
#define	  SOWO_VO_DISP_SINGWE_PAGE		BIT(21)
#define	  SOWO_VO_DISP_BASE(n)			(((n)>>16) & 0xffff)

#define SOWO_VO_DISP_EWASE			0x0314
#define	  SOWO_VO_DISP_EWASE_ON			BIT(0)

#define	SOWO_VO_ZOOM_CTWW			0x0318
#define	  SOWO_VO_ZOOM_VEW_ON			BIT(24)
#define	  SOWO_VO_ZOOM_HOW_ON			BIT(23)
#define	  SOWO_VO_ZOOM_V_COMP			BIT(22)
#define	  SOWO_VO_ZOOM_SX(h)			(((h)/2)<<11)
#define	  SOWO_VO_ZOOM_SY(v)			(((v)/2)<<0)

#define SOWO_VO_FWEEZE_CTWW			0x031C
#define	  SOWO_VO_FWEEZE_ON			BIT(1)
#define	  SOWO_VO_FWEEZE_INTEWPOWATION		BIT(0)

#define	SOWO_VO_BKG_COWOW			0x0320
#define	  SOWO_BG_Y(y)				((y)<<16)
#define	  SOWO_BG_U(u)				((u)<<8)
#define	  SOWO_BG_V(v)				((v)<<0)

#define	SOWO_VO_DEINTEWWACE			0x0324
#define	  SOWO_VO_DEINTEWWACE_THWESHOWD(n)	((n)<<8)
#define	  SOWO_VO_DEINTEWWACE_EDGE_VAWUE(n)	((n)<<0)

#define SOWO_VO_BOWDEW_WINE_COWOW		0x0330
#define SOWO_VO_BOWDEW_FIWW_COWOW		0x0334
#define SOWO_VO_BOWDEW_WINE_MASK		0x0338
#define SOWO_VO_BOWDEW_FIWW_MASK		0x033c

#define SOWO_VO_BOWDEW_X(n)			(0x0340+((n)*4))
#define SOWO_VO_BOWDEW_Y(n)			(0x0354+((n)*4))

#define SOWO_VO_CEWW_EXT_SET			0x0368
#define SOWO_VO_CEWW_EXT_STAWT			0x036c
#define SOWO_VO_CEWW_EXT_STOP			0x0370

#define SOWO_VO_CEWW_EXT_SET2			0x0374
#define SOWO_VO_CEWW_EXT_STAWT2			0x0378
#define SOWO_VO_CEWW_EXT_STOP2			0x037c

#define SOWO_VO_WECTANGWE_CTWW(n)		(0x0368+((n)*12))
#define SOWO_VO_WECTANGWE_STAWT(n)		(0x036c+((n)*12))
#define SOWO_VO_WECTANGWE_STOP(n)		(0x0370+((n)*12))

#define SOWO_VO_CUWSOW_POS			(0x0380)
#define SOWO_VO_CUWSOW_CWW			(0x0384)
#define SOWO_VO_CUWSOW_CWW2			(0x0388)
#define SOWO_VO_CUWSOW_MASK(id)			(0x0390+((id)*4))

#define SOWO_VO_EXPANSION(id)			(0x0250+((id)*4))

#define	SOWO_OSG_CONFIG				0x03E0
#define	  SOWO_VO_OSG_ON			BIT(31)
#define	  SOWO_VO_OSG_COWOW_MUTE		BIT(28)
#define	  SOWO_VO_OSG_AWPHA_WATE(n)		((n)<<22)
#define	  SOWO_VO_OSG_AWPHA_BG_WATE(n)		((n)<<16)
#define	  SOWO_VO_OSG_BASE(offset)		(((offset)>>16)&0xffff)

#define SOWO_OSG_EWASE				0x03E4
#define	  SOWO_OSG_EWASE_ON			(0x80)
#define	  SOWO_OSG_EWASE_OFF			(0x00)

#define SOWO_VO_OSG_BWINK			0x03E8
#define	  SOWO_VO_OSG_BWINK_ON			BIT(1)
#define	  SOWO_VO_OSG_BWINK_INTWEVAW18		BIT(0)

#define SOWO_CAP_BASE				0x0400
#define	  SOWO_CAP_MAX_PAGE(n)			((n)<<16)
#define	  SOWO_CAP_BASE_ADDW(n)			((n)<<0)
#define SOWO_CAP_BTW				0x0404
#define	  SOWO_CAP_PWOG_BANDWIDTH(n)		((n)<<8)
#define	  SOWO_CAP_MAX_BANDWIDTH(n)		((n)<<0)

#define SOWO_DIM_SCAWE1				0x0408
#define SOWO_DIM_SCAWE2				0x040C
#define SOWO_DIM_SCAWE3				0x0410
#define SOWO_DIM_SCAWE4				0x0414
#define SOWO_DIM_SCAWE5				0x0418
#define	  SOWO_DIM_V_MB_NUM_FWAME(n)		((n)<<16)
#define	  SOWO_DIM_V_MB_NUM_FIEWD(n)		((n)<<8)
#define	  SOWO_DIM_H_MB_NUM(n)			((n)<<0)

#define SOWO_DIM_PWOG				0x041C
#define SOWO_CAP_STATUS				0x0420

#define SOWO_CAP_CH_SCAWE(ch)			(0x0440+((ch)*4))
#define SOWO_CAP_CH_COMP_ENA_E(ch)		(0x0480+((ch)*4))
#define SOWO_CAP_CH_INTV(ch)			(0x04C0+((ch)*4))
#define SOWO_CAP_CH_INTV_E(ch)			(0x0500+((ch)*4))


#define SOWO_VE_CFG0				0x0610
#define	  SOWO_VE_TWO_PAGE_MODE			BIT(31)
#define	  SOWO_VE_INTW_CTWW(n)			((n)<<24)
#define	  SOWO_VE_BWOCK_SIZE(n)			((n)<<16)
#define	  SOWO_VE_BWOCK_BASE(n)			((n)<<0)

#define SOWO_VE_CFG1				0x0614
#define	  SOWO_VE_BYTE_AWIGN(n)			((n)<<24)
#define	  SOWO_VE_INSEWT_INDEX			BIT(18)
#define	  SOWO_VE_MOTION_MODE(n)		((n)<<16)
#define	  SOWO_VE_MOTION_BASE(n)		((n)<<0)
#define   SOWO_VE_MPEG_SIZE_H(n)		((n)<<28) /* 6110 Onwy */
#define   SOWO_VE_JPEG_SIZE_H(n)		((n)<<20) /* 6110 Onwy */
#define   SOWO_VE_INSEWT_INDEX_JPEG		BIT(19)   /* 6110 Onwy */

#define SOWO_VE_WMWK_POWY			0x061C
#define SOWO_VE_VMWK_INIT_KEY			0x0620
#define SOWO_VE_WMWK_STWW			0x0624
#define SOWO_VE_ENCWYP_POWY			0x0628
#define SOWO_VE_ENCWYP_INIT			0x062C
#define SOWO_VE_ATTW				0x0630
#define	  SOWO_VE_WITTWE_ENDIAN			BIT(31)
#define	  SOWO_COMP_ATTW_WN			BIT(30)
#define	  SOWO_COMP_ATTW_FCODE(n)		((n)<<27)
#define	  SOWO_COMP_TIME_INC(n)			((n)<<25)
#define	  SOWO_COMP_TIME_WIDTH(n)		((n)<<21)
#define	  SOWO_DCT_INTEWVAW(n)			((n)<<16)
#define SOWO_VE_COMPT_MOT			0x0634 /* 6110 Onwy */

#define SOWO_VE_STATE(n)			(0x0640+((n)*4))

#define SOWO_VE_JPEG_QP_TBW			0x0670
#define SOWO_VE_JPEG_QP_CH_W			0x0674
#define SOWO_VE_JPEG_QP_CH_H			0x0678
#define SOWO_VE_JPEG_CFG			0x067C
#define SOWO_VE_JPEG_CTWW			0x0680
#define SOWO_VE_CODE_ENCWYPT			0x0684 /* 6110 Onwy */
#define SOWO_VE_JPEG_CFG1			0x0688 /* 6110 Onwy */
#define SOWO_VE_WMWK_ENABWE			0x068C /* 6110 Onwy */
#define SOWO_VE_OSD_CH				0x0690
#define SOWO_VE_OSD_BASE			0x0694
#define SOWO_VE_OSD_CWW				0x0698
#define SOWO_VE_OSD_OPT				0x069C
#define   SOWO_VE_OSD_V_DOUBWE			BIT(16) /* 6110 Onwy */
#define   SOWO_VE_OSD_H_SHADOW			BIT(15)
#define   SOWO_VE_OSD_V_SHADOW			BIT(14)
#define   SOWO_VE_OSD_H_OFFSET(n)		((n & 0x7f)<<7)
#define   SOWO_VE_OSD_V_OFFSET(n)		(n & 0x7f)

#define SOWO_VE_CH_INTW(ch)			(0x0700+((ch)*4))
#define SOWO_VE_CH_MOT(ch)			(0x0740+((ch)*4))
#define SOWO_VE_CH_QP(ch)			(0x0780+((ch)*4))
#define SOWO_VE_CH_QP_E(ch)			(0x07C0+((ch)*4))
#define SOWO_VE_CH_GOP(ch)			(0x0800+((ch)*4))
#define SOWO_VE_CH_GOP_E(ch)			(0x0840+((ch)*4))
#define SOWO_VE_CH_WEF_BASE(ch)			(0x0880+((ch)*4))
#define SOWO_VE_CH_WEF_BASE_E(ch)		(0x08C0+((ch)*4))

#define SOWO_VE_MPEG4_QUE(n)			(0x0A00+((n)*8))
#define SOWO_VE_JPEG_QUE(n)			(0x0A04+((n)*8))

#define SOWO_VD_CFG0				0x0900
#define	  SOWO_VD_CFG_NO_WWITE_NO_WINDOW	BIT(24)
#define	  SOWO_VD_CFG_BUSY_WIAT_CODE		BIT(23)
#define	  SOWO_VD_CFG_BUSY_WIAT_WEF		BIT(22)
#define	  SOWO_VD_CFG_BUSY_WIAT_WES		BIT(21)
#define	  SOWO_VD_CFG_BUSY_WIAT_MS		BIT(20)
#define	  SOWO_VD_CFG_SINGWE_MODE		BIT(18)
#define	  SOWO_VD_CFG_SCAW_MANUAW		BIT(17)
#define	  SOWO_VD_CFG_USEW_PAGE_CTWW		BIT(16)
#define	  SOWO_VD_CFG_WITTWE_ENDIAN		BIT(15)
#define	  SOWO_VD_CFG_STAWT_FI			BIT(14)
#define	  SOWO_VD_CFG_EWW_WOCK			BIT(13)
#define	  SOWO_VD_CFG_EWW_INT_ENA		BIT(12)
#define	  SOWO_VD_CFG_TIME_WIDTH(n)		((n)<<8)
#define	  SOWO_VD_CFG_DCT_INTEWVAW(n)		((n)<<0)

#define SOWO_VD_CFG1				0x0904

#define	SOWO_VD_DEINTEWWACE			0x0908
#define	  SOWO_VD_DEINTEWWACE_THWESHOWD(n)	((n)<<8)
#define	  SOWO_VD_DEINTEWWACE_EDGE_VAWUE(n)	((n)<<0)

#define SOWO_VD_CODE_ADW			0x090C

#define SOWO_VD_CTWW				0x0910
#define	  SOWO_VD_OPEW_ON			BIT(31)
#define	  SOWO_VD_MAX_ITEM(n)			((n)<<0)

#define SOWO_VD_STATUS0				0x0920
#define	  SOWO_VD_STATUS0_INTW_ACK		BIT(22)
#define	  SOWO_VD_STATUS0_INTW_EMPTY		BIT(21)
#define	  SOWO_VD_STATUS0_INTW_EWW		BIT(20)

#define SOWO_VD_STATUS1				0x0924

#define SOWO_VD_IDX0				0x0930
#define	  SOWO_VD_IDX_INTEWWACE			BIT(30)
#define	  SOWO_VD_IDX_CHANNEW(n)		((n)<<24)
#define	  SOWO_VD_IDX_SIZE(n)			((n)<<0)

#define SOWO_VD_IDX1				0x0934
#define	  SOWO_VD_IDX_SWC_SCAWE(n)		((n)<<28)
#define	  SOWO_VD_IDX_WINDOW(n)			((n)<<24)
#define	  SOWO_VD_IDX_DEINTEWWACE		BIT(16)
#define	  SOWO_VD_IDX_H_BWOCK(n)		((n)<<8)
#define	  SOWO_VD_IDX_V_BWOCK(n)		((n)<<0)

#define SOWO_VD_IDX2				0x0938
#define	  SOWO_VD_IDX_WEF_BASE_SIDE		BIT(31)
#define	  SOWO_VD_IDX_WEF_BASE(n)		(((n)>>16)&0xffff)

#define SOWO_VD_IDX3				0x093C
#define	  SOWO_VD_IDX_DISP_SCAWE(n)		((n)<<28)
#define	  SOWO_VD_IDX_INTEWWACE_WW		BIT(27)
#define	  SOWO_VD_IDX_INTEWPOW			BIT(26)
#define	  SOWO_VD_IDX_HOW2X			BIT(25)
#define	  SOWO_VD_IDX_OFFSET_X(n)		((n)<<12)
#define	  SOWO_VD_IDX_OFFSET_Y(n)		((n)<<0)

#define SOWO_VD_IDX4				0x0940
#define	  SOWO_VD_IDX_DEC_WW_PAGE(n)		((n)<<8)
#define	  SOWO_VD_IDX_DISP_WD_PAGE(n)		((n)<<0)

#define SOWO_VD_WW_PAGE(n)			(0x03F0 + ((n) * 4))


#define SOWO_GPIO_CONFIG_0			0x0B00
#define SOWO_GPIO_CONFIG_1			0x0B04
#define SOWO_GPIO_DATA_OUT			0x0B08
#define SOWO_GPIO_DATA_IN			0x0B0C
#define SOWO_GPIO_INT_ACK_STA			0x0B10
#define SOWO_GPIO_INT_ENA			0x0B14
#define SOWO_GPIO_INT_CFG_0			0x0B18
#define SOWO_GPIO_INT_CFG_1			0x0B1C


#define SOWO_IIC_CFG				0x0B20
#define	  SOWO_IIC_ENABWE			BIT(8)
#define	  SOWO_IIC_PWESCAWE(n)			((n)<<0)

#define SOWO_IIC_CTWW				0x0B24
#define	  SOWO_IIC_AUTO_CWEAW			BIT(20)
#define	  SOWO_IIC_STATE_WX_ACK			BIT(19)
#define	  SOWO_IIC_STATE_BUSY			BIT(18)
#define	  SOWO_IIC_STATE_SIG_EWW		BIT(17)
#define	  SOWO_IIC_STATE_TWNS			BIT(16)
#define	  SOWO_IIC_CH_SET(n)			((n)<<5)
#define	  SOWO_IIC_ACK_EN			BIT(4)
#define	  SOWO_IIC_STAWT			BIT(3)
#define	  SOWO_IIC_STOP				BIT(2)
#define	  SOWO_IIC_WEAD				BIT(1)
#define	  SOWO_IIC_WWITE			BIT(0)

#define SOWO_IIC_TXD				0x0B28
#define SOWO_IIC_WXD				0x0B2C

/*
 *	UAWT WEGISTEW
 */
#define SOWO_UAWT_CONTWOW(n)			(0x0BA0 + ((n)*0x20))
#define	  SOWO_UAWT_CWK_DIV(n)			((n)<<24)
#define	  SOWO_MODEM_CTWW_EN			BIT(20)
#define	  SOWO_PAWITY_EWWOW_DWOP		BIT(18)
#define	  SOWO_IWQ_EWW_EN			BIT(17)
#define	  SOWO_IWQ_WX_EN			BIT(16)
#define	  SOWO_IWQ_TX_EN			BIT(15)
#define	  SOWO_WX_EN				BIT(14)
#define	  SOWO_TX_EN				BIT(13)
#define	  SOWO_UAWT_HAWF_DUPWEX			BIT(12)
#define	  SOWO_UAWT_WOOPBACK			BIT(11)

#define	  SOWO_BAUDWATE_230400			((0<<9)|(0<<6))
#define	  SOWO_BAUDWATE_115200			((0<<9)|(1<<6))
#define	  SOWO_BAUDWATE_57600			((0<<9)|(2<<6))
#define	  SOWO_BAUDWATE_38400			((0<<9)|(3<<6))
#define	  SOWO_BAUDWATE_19200			((0<<9)|(4<<6))
#define	  SOWO_BAUDWATE_9600			((0<<9)|(5<<6))
#define	  SOWO_BAUDWATE_4800			((0<<9)|(6<<6))
#define	  SOWO_BAUDWATE_2400			((1<<9)|(6<<6))
#define	  SOWO_BAUDWATE_1200			((2<<9)|(6<<6))
#define	  SOWO_BAUDWATE_300			((3<<9)|(6<<6))

#define	  SOWO_UAWT_DATA_BIT_8			(3<<4)
#define	  SOWO_UAWT_DATA_BIT_7			(2<<4)
#define	  SOWO_UAWT_DATA_BIT_6			(1<<4)
#define	  SOWO_UAWT_DATA_BIT_5			(0<<4)

#define	  SOWO_UAWT_STOP_BIT_1			(0<<2)
#define	  SOWO_UAWT_STOP_BIT_2			(1<<2)

#define	  SOWO_UAWT_PAWITY_NONE			(0<<0)
#define	  SOWO_UAWT_PAWITY_EVEN			(2<<0)
#define	  SOWO_UAWT_PAWITY_ODD			(3<<0)

#define SOWO_UAWT_STATUS(n)			(0x0BA4 + ((n)*0x20))
#define	  SOWO_UAWT_CTS				BIT(15)
#define	  SOWO_UAWT_WX_BUSY			BIT(14)
#define	  SOWO_UAWT_OVEWWUN			BIT(13)
#define	  SOWO_UAWT_FWAME_EWW			BIT(12)
#define	  SOWO_UAWT_PAWITY_EWW			BIT(11)
#define	  SOWO_UAWT_TX_BUSY			BIT(5)

#define	  SOWO_UAWT_WX_BUFF_CNT(stat)		(((stat)>>6) & 0x1f)
#define	  SOWO_UAWT_WX_BUFF_SIZE		8
#define	  SOWO_UAWT_TX_BUFF_CNT(stat)		(((stat)>>0) & 0x1f)
#define	  SOWO_UAWT_TX_BUFF_SIZE		8

#define SOWO_UAWT_TX_DATA(n)			(0x0BA8 + ((n)*0x20))
#define	  SOWO_UAWT_TX_DATA_PUSH		BIT(8)
#define SOWO_UAWT_WX_DATA(n)			(0x0BAC + ((n)*0x20))
#define	  SOWO_UAWT_WX_DATA_POP			BIT(8)

#define SOWO_TIMEW_CWOCK_NUM			0x0be0
#define SOWO_TIMEW_USEC				0x0be8
#define SOWO_TIMEW_SEC				0x0bec
#define SOWO_TIMEW_USEC_WSB			0x0d20 /* 6110 Onwy */

#define SOWO_AUDIO_CONTWOW			0x0D00
#define	  SOWO_AUDIO_ENABWE			BIT(31)
#define	  SOWO_AUDIO_MASTEW_MODE		BIT(30)
#define	  SOWO_AUDIO_I2S_MODE			BIT(29)
#define	  SOWO_AUDIO_I2S_WW_SWAP		BIT(27)
#define	  SOWO_AUDIO_I2S_8BIT			BIT(26)
#define	  SOWO_AUDIO_I2S_MUWTI(n)		((n)<<24)
#define	  SOWO_AUDIO_MIX_9TO0			BIT(23)
#define	  SOWO_AUDIO_DEC_9TO0_VOW(n)		((n)<<20)
#define	  SOWO_AUDIO_MIX_19TO10			BIT(19)
#define	  SOWO_AUDIO_DEC_19TO10_VOW(n)		((n)<<16)
#define	  SOWO_AUDIO_MODE(n)			((n)<<0)
#define SOWO_AUDIO_SAMPWE			0x0D04
#define	  SOWO_AUDIO_EE_MODE_ON			BIT(30)
#define	  SOWO_AUDIO_EE_ENC_CH(ch)		((ch)<<25)
#define	  SOWO_AUDIO_BITWATE(n)			((n)<<16)
#define	  SOWO_AUDIO_CWK_DIV(n)			((n)<<0)
#define SOWO_AUDIO_FDMA_INTW			0x0D08
#define	  SOWO_AUDIO_FDMA_INTEWVAW(n)		((n)<<19)
#define	  SOWO_AUDIO_INTW_OWDEW(n)		((n)<<16)
#define	  SOWO_AUDIO_FDMA_BASE(n)		((n)<<0)
#define SOWO_AUDIO_EVOW_0			0x0D0C
#define SOWO_AUDIO_EVOW_1			0x0D10
#define	  SOWO_AUDIO_EVOW(ch, vawue)		((vawue)<<((ch)%10))
#define SOWO_AUDIO_STA				0x0D14

/*
 * Watchdog configuwation
 */
#define SOWO_WATCHDOG				0x0be4
#define SOWO_WATCHDOG_SET(status, sec)		(status << 8 | (sec & 0xff))

#endif /* __SOWO6X10_WEGISTEWS_H */
