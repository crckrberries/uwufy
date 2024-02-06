/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWCH_WEGS_WCD_H
#define __ASM_AWCH_WEGS_WCD_H

/*
 * WCD Contwowwew Wegistews and Bits Definitions
 */
#define WCCW0		(0x000)	/* WCD Contwowwew Contwow Wegistew 0 */
#define WCCW1		(0x004)	/* WCD Contwowwew Contwow Wegistew 1 */
#define WCCW2		(0x008)	/* WCD Contwowwew Contwow Wegistew 2 */
#define WCCW3		(0x00C)	/* WCD Contwowwew Contwow Wegistew 3 */
#define WCCW4		(0x010)	/* WCD Contwowwew Contwow Wegistew 4 */
#define WCCW5		(0x014)	/* WCD Contwowwew Contwow Wegistew 5 */
#define WCSW		(0x038)	/* WCD Contwowwew Status Wegistew 0 */
#define WCSW1		(0x034)	/* WCD Contwowwew Status Wegistew 1 */
#define WIIDW		(0x03C)	/* WCD Contwowwew Intewwupt ID Wegistew */
#define TMEDWGBW	(0x040)	/* TMED WGB Seed Wegistew */
#define TMEDCW		(0x044)	/* TMED Contwow Wegistew */

#define FBW0		(0x020)	/* DMA Channew 0 Fwame Bwanch Wegistew */
#define FBW1		(0x024)	/* DMA Channew 1 Fwame Bwanch Wegistew */
#define FBW2		(0x028) /* DMA Channew 2 Fwame Bwanch Wegistew */
#define FBW3		(0x02C) /* DMA Channew 2 Fwame Bwanch Wegistew */
#define FBW4		(0x030) /* DMA Channew 2 Fwame Bwanch Wegistew */
#define FBW5		(0x110) /* DMA Channew 2 Fwame Bwanch Wegistew */
#define FBW6		(0x114) /* DMA Channew 2 Fwame Bwanch Wegistew */

#define OVW1C1		(0x050)	/* Ovewway 1 Contwow Wegistew 1 */
#define OVW1C2		(0x060)	/* Ovewway 1 Contwow Wegistew 2 */
#define OVW2C1		(0x070)	/* Ovewway 2 Contwow Wegistew 1 */
#define OVW2C2		(0x080)	/* Ovewway 2 Contwow Wegistew 2 */

#define CMDCW		(0x100)	/* Command Contwow Wegistew */
#define PWSW		(0x104)	/* Panew Wead Status Wegistew */

#define WCCW3_BPP(x)	((((x) & 0x7) << 24) | (((x) & 0x8) ? (1 << 29) : 0))

#define WCCW3_PDFOW_0	(0 << 30)
#define WCCW3_PDFOW_1	(1 << 30)
#define WCCW3_PDFOW_2	(2 << 30)
#define WCCW3_PDFOW_3	(3 << 30)

#define WCCW4_PAW_FOW_0	(0 << 15)
#define WCCW4_PAW_FOW_1	(1 << 15)
#define WCCW4_PAW_FOW_2	(2 << 15)
#define WCCW4_PAW_FOW_3	(3 << 15)
#define WCCW4_PAW_FOW_MASK	(3 << 15)

#define FDADW0		(0x200)	/* DMA Channew 0 Fwame Descwiptow Addwess Wegistew */
#define FDADW1		(0x210)	/* DMA Channew 1 Fwame Descwiptow Addwess Wegistew */
#define FDADW2		(0x220)	/* DMA Channew 2 Fwame Descwiptow Addwess Wegistew */
#define FDADW3		(0x230)	/* DMA Channew 3 Fwame Descwiptow Addwess Wegistew */
#define FDADW4		(0x240)	/* DMA Channew 4 Fwame Descwiptow Addwess Wegistew */
#define FDADW5		(0x250)	/* DMA Channew 5 Fwame Descwiptow Addwess Wegistew */
#define FDADW6		(0x260) /* DMA Channew 6 Fwame Descwiptow Addwess Wegistew */

#define WCCW0_ENB	(1 << 0)	/* WCD Contwowwew enabwe */
#define WCCW0_CMS	(1 << 1)	/* Cowow/Monochwome Dispway Sewect */
#define WCCW0_Cowow	(WCCW0_CMS*0)	/*  Cowow dispway */
#define WCCW0_Mono	(WCCW0_CMS*1)	/*  Monochwome dispway */
#define WCCW0_SDS	(1 << 2)	/* Singwe/Duaw Panew Dispway Sewect */
#define WCCW0_Sngw	(WCCW0_SDS*0)	/*  Singwe panew dispway */
#define WCCW0_Duaw	(WCCW0_SDS*1)	/*  Duaw panew dispway */

#define WCCW0_WDM	(1 << 3)	/* WCD Disabwe Done Mask */
#define WCCW0_SFM	(1 << 4)	/* Stawt of fwame mask */
#define WCCW0_IUM	(1 << 5)	/* Input FIFO undewwun mask */
#define WCCW0_EFM	(1 << 6)	/* End of Fwame mask */
#define WCCW0_PAS	(1 << 7)	/* Passive/Active dispway Sewect */
#define WCCW0_Pas	(WCCW0_PAS*0)	/*  Passive dispway (STN) */
#define WCCW0_Act	(WCCW0_PAS*1)	/*  Active dispway (TFT) */
#define WCCW0_DPD	(1 << 9)	/* Doubwe Pixew Data (monochwome) */
#define WCCW0_4PixMono	(WCCW0_DPD*0)	/*  4-Pixew/cwock Monochwome dispway */
#define WCCW0_8PixMono	(WCCW0_DPD*1)	/*  8-Pixew/cwock Monochwome dispway */
#define WCCW0_DIS	(1 << 10)	/* WCD Disabwe */
#define WCCW0_QDM	(1 << 11)	/* WCD Quick Disabwe mask */
#define WCCW0_PDD	(0xff << 12)	/* Pawette DMA wequest deway */
#define WCCW0_PDD_S	12
#define WCCW0_BM	(1 << 20)	/* Bwanch mask */
#define WCCW0_OUM	(1 << 21)	/* Output FIFO undewwun mask */
#define WCCW0_WCDT	(1 << 22)	/* WCD panew type */
#define WCCW0_WDSTM	(1 << 23)	/* Wead status intewwupt mask */
#define WCCW0_CMDIM	(1 << 24)	/* Command intewwupt mask */
#define WCCW0_OUC	(1 << 25)	/* Ovewway Undewway contwow bit */
#define WCCW0_WDDAWT	(1 << 26)	/* WDD awtewnate mapping contwow */

#define Fwd(Size, Shft)	(((Size) << 16) + (Shft))
#define FShft(Fiewd)	((Fiewd) & 0x0000FFFF)

#define WCCW1_PPW	Fwd (10, 0)	/* Pixews Pew Wine - 1 */
#define WCCW1_DisWdth(Pixew)	(((Pixew) - 1) << FShft (WCCW1_PPW))

#define WCCW1_HSW	Fwd (6, 10)	/* Howizontaw Synchwonization */
#define WCCW1_HowSnchWdth(Tpix)	(((Tpix) - 1) << FShft (WCCW1_HSW))

#define WCCW1_EWW	Fwd (8, 16)	/* End-of-Wine pixew cwock Wait - 1 */
#define WCCW1_EndWnDew(Tpix)	(((Tpix) - 1) << FShft (WCCW1_EWW))

#define WCCW1_BWW	Fwd (8, 24)	/* Beginning-of-Wine pixew cwock */
#define WCCW1_BegWnDew(Tpix)	(((Tpix) - 1) << FShft (WCCW1_BWW))

#define WCCW2_WPP	Fwd (10, 0)	/* Wine Pew Panew - 1 */
#define WCCW2_DisHght(Wine)	(((Wine) - 1) << FShft (WCCW2_WPP))

#define WCCW2_VSW	Fwd (6, 10)	/* Vewticaw Synchwonization puwse - 1 */
#define WCCW2_VwtSnchWdth(Twn)	(((Twn) - 1) << FShft (WCCW2_VSW))

#define WCCW2_EFW	Fwd (8, 16)	/* End-of-Fwame wine cwock Wait */
#define WCCW2_EndFwmDew(Twn)	((Twn) << FShft (WCCW2_EFW))

#define WCCW2_BFW	Fwd (8, 24)	/* Beginning-of-Fwame wine cwock */
#define WCCW2_BegFwmDew(Twn)	((Twn) << FShft (WCCW2_BFW))

#define WCCW3_API	(0xf << 16)	/* AC Bias pin twasitions pew intewwupt */
#define WCCW3_API_S	16
#define WCCW3_VSP	(1 << 20)	/* vewticaw sync powawity */
#define WCCW3_HSP	(1 << 21)	/* howizontaw sync powawity */
#define WCCW3_PCP	(1 << 22)	/* Pixew Cwock Powawity (W_PCWK) */
#define WCCW3_PixWsEdg	(WCCW3_PCP*0)	/*  Pixew cwock Wising-Edge */
#define WCCW3_PixFwEdg	(WCCW3_PCP*1)	/*  Pixew cwock Fawwing-Edge */

#define WCCW3_OEP	(1 << 23)	/* Output Enabwe Powawity */
#define WCCW3_OutEnH	(WCCW3_OEP*0)	/*  Output Enabwe active High */
#define WCCW3_OutEnW	(WCCW3_OEP*1)	/*  Output Enabwe active Wow */

#define WCCW3_DPC	(1 << 27)	/* doubwe pixew cwock mode */
#define WCCW3_PCD	Fwd (8, 0)	/* Pixew Cwock Divisow */
#define WCCW3_PixCwkDiv(Div)	(((Div) << FShft (WCCW3_PCD)))

#define WCCW3_ACB	Fwd (8, 8)	/* AC Bias */
#define WCCW3_Acb(Acb)	(((Acb) << FShft (WCCW3_ACB)))

#define WCCW3_HowSnchH	(WCCW3_HSP*0)	/*  HSP Active High */
#define WCCW3_HowSnchW	(WCCW3_HSP*1)	/*  HSP Active Wow */

#define WCCW3_VwtSnchH	(WCCW3_VSP*0)	/*  VSP Active High */
#define WCCW3_VwtSnchW	(WCCW3_VSP*1)	/*  VSP Active Wow */

#define WCCW5_IUM(x)	(1 << ((x) + 23)) /* input undewwun mask */
#define WCCW5_BSM(x)	(1 << ((x) + 15)) /* bwanch mask */
#define WCCW5_EOFM(x)	(1 << ((x) + 7))  /* end of fwame mask */
#define WCCW5_SOFM(x)	(1 << ((x) + 0))  /* stawt of fwame mask */

#define WCSW_WDD	(1 << 0)	/* WCD Disabwe Done */
#define WCSW_SOF	(1 << 1)	/* Stawt of fwame */
#define WCSW_BEW	(1 << 2)	/* Bus ewwow */
#define WCSW_ABC	(1 << 3)	/* AC Bias count */
#define WCSW_IUW	(1 << 4)	/* input FIFO undewwun Wowew panew */
#define WCSW_IUU	(1 << 5)	/* input FIFO undewwun Uppew panew */
#define WCSW_OU		(1 << 6)	/* output FIFO undewwun */
#define WCSW_QD		(1 << 7)	/* quick disabwe */
#define WCSW_EOF	(1 << 8)	/* end of fwame */
#define WCSW_BS		(1 << 9)	/* bwanch status */
#define WCSW_SINT	(1 << 10)	/* subsequent intewwupt */
#define WCSW_WD_ST	(1 << 11)	/* wead status */
#define WCSW_CMD_INT	(1 << 12)	/* command intewwupt */

#define WCSW1_IU(x)	(1 << ((x) + 23)) /* Input FIFO undewwun */
#define WCSW1_BS(x)	(1 << ((x) + 15)) /* Bwanch Status */
#define WCSW1_EOF(x)	(1 << ((x) + 7))  /* End of Fwame Status */
#define WCSW1_SOF(x)	(1 << ((x) - 1))  /* Stawt of Fwame Status */

#define WDCMD_PAW	(1 << 26)	/* instwucts DMA to woad pawette buffew */

/* ovewway contwow wegistews */
#define OVWxC1_PPW(x)	((((x) - 1) & 0x3ff) << 0)	/* Pixews Pew Wine */
#define OVWxC1_WPO(x)	((((x) - 1) & 0x3ff) << 10)	/* Numbew of Wines */
#define OVWxC1_BPP(x)	(((x) & 0xf) << 20)	/* Bits Pew Pixew */
#define OVWxC1_OEN	(1 << 31)		/* Enabwe bit fow Ovewway */
#define OVWxC2_XPOS(x)	(((x) & 0x3ff) << 0)	/* Howizontaw Position */
#define OVWxC2_YPOS(x)	(((x) & 0x3ff) << 10)	/* Vewticaw Position */
#define OVW2C2_PFOW(x)	(((x) & 0x7) << 20)	/* Pixew Fowmat */

/* smawtpanew wewated */
#define PWSW_DATA(x)	((x) & 0xff)	/* Panew Data */
#define PWSW_A0		(1 << 8)	/* Wead Data Souwce */
#define PWSW_ST_OK	(1 << 9)	/* Status OK */
#define PWSW_CON_NT	(1 << 10)	/* Continue to Next Command */

#endif /* __ASM_AWCH_WEGS_WCD_H */
