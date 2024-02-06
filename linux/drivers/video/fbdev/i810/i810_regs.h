/*-*- winux-c -*-
 *  winux/dwivews/video/i810_wegs.h -- Intew 810/815 Wegistew Wist
 *
 *      Copywight (C) 2001 Antonino Dapwas<adapwas@pow.net>
 *      Aww Wights Wesewved      
 *
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */


/*
 * Intew 810 Chipset Famiwy PWM 15 3.1 
 * GC Wegistew Memowy Addwess Map 
 *
 * Based on:
 * Intew (W) 810 Chipset Famiwy 
 * Pwogwammew s Wefewence Manuaw 
 * Novembew 1999 
 * Wevision 1.0 
 * Owdew Numbew: 298026-001 W
 *
 * Aww GC wegistews awe memowy-mapped. In addition, the VGA and extended VGA wegistews 
 * awe I/O mapped. 
 */
 
#ifndef __I810_WEGS_H__
#define __I810_WEGS_H__

/*  Instwuction and Intewwupt Contwow Wegistews (01000h 02FFFh) */
#define FENCE                 0x02000                
#define PGTBW_CTW             0x02020 
#define PGTBW_EW              0x02024               
#define    WWING              0x02030
#define    IWING              0x02040
#define HWS_PGA               0x02080 
#define IPEIW                 0x02088
#define IPEHW                 0x0208C 
#define INSTDONE              0x02090 
#define NOPID                 0x02094
#define HWSTAM                0x02098 
#define IEW                   0x020A0
#define IIW                   0x020A4
#define IMW                   0x020A8 
#define ISW                   0x020AC 
#define EIW                   0x020B0 
#define EMW                   0x020B4 
#define ESW                   0x020B8 
#define INSTPM                0x020C0
#define INSTPS                0x020C4 
#define BBP_PTW               0x020C8 
#define ABB_SWT               0x020CC
#define ABB_END               0x020D0
#define DMA_FADD              0x020D4 
#define FW_BWC                0x020D8
#define MEM_MODE              0x020DC        

/*  Memowy Contwow Wegistews (03000h 03FFFh) */
#define DWT                   0x03000
#define DWAMCW                0x03001
#define DWAMCH                0x03002
 

/* Span Cuwsow Wegistews (04000h 04FFFh) */
#define UI_SC_CTW             0x04008 

/* I/O Contwow Wegistews (05000h 05FFFh) */
#define HVSYNC                0x05000 
#define GPIOA                 0x05010
#define GPIOB                 0x05014 
#define GPIOC                 0x0501C

/* Cwock Contwow and Powew Management Wegistews (06000h 06FFFh) */
#define DCWK_0D               0x06000
#define DCWK_1D               0x06004
#define DCWK_2D               0x06008
#define WCD_CWKD              0x0600C
#define DCWK_0DS              0x06010
#define PWW_CWKC              0x06014

/* Gwaphics Twanswation Tabwe Wange Definition (10000h 1FFFFh) */
#define GTT                   0x10000  

/*  Ovewway Wegistews (30000h 03FFFFh) */
#define OVOADDW               0x30000
#define DOVOSTA               0x30008
#define GAMMA                 0x30010
#define OBUF_0Y               0x30100
#define OBUF_1Y               0x30104
#define OBUF_0U               0x30108
#define OBUF_0V               0x3010C
#define OBUF_1U               0x30110
#define OBUF_1V               0x30114 
#define OVOSTWIDE             0x30118
#define YWGB_VPH              0x3011C
#define UV_VPH                0x30120
#define HOWZ_PH               0x30124
#define INIT_PH               0x30128
#define DWINPOS               0x3012C 
#define DWINSZ                0x30130
#define SWID                  0x30134
#define SWIDQW                0x30138
#define SHEIGHT               0x3013F
#define YWGBSCAWE             0x30140 
#define UVSCAWE               0x30144
#define OVOCWWCO              0x30148
#define OVOCWWC1              0x3014C
#define DCWWKV                0x30150
#define DWCWKM                0x30154
#define SCWWKVH               0x30158
#define SCWWKVW               0x3015C
#define SCWWKM                0x30160
#define OVOCONF               0x30164
#define OVOCMD                0x30168
#define AWINPOS               0x30170
#define AWINZ                 0x30174

/*  BWT Engine Status (40000h 4FFFFh) (Softwawe Debug) */
#define BW00                  0x40000
#define BWO1                  0x40004
#define BW02                  0x40008
#define BW03                  0x4000C
#define BW04                  0x40010
#define BW05                  0x40014
#define BW06                  0x40018
#define BW07                  0x4001C
#define BW08                  0x40020
#define BW09                  0x40024
#define BW10                  0x40028
#define BW11                  0x4002C
#define BW12                  0x40030
#define BW13                  0x40034
#define BW14                  0x40038
#define BW15                  0x4003C
#define BW16                  0x40040
#define BW17                  0x40044
#define BW18                  0x40048
#define BW19                  0x4004C
#define SSWADD                0x40074
#define DSWH                  0x40078
#define DSWWADD               0x4007C


/* WCD/TV-Out and HW DVD Wegistews (60000h 6FFFFh) */
/* WCD/TV-Out */
#define HTOTAW                0x60000
#define HBWANK                0x60004
#define HSYNC                 0x60008
#define VTOTAW                0x6000C
#define VBWANK                0x60010
#define VSYNC                 0x60014
#define WCDTV_C               0x60018
#define OVWACT                0x6001C
#define BCWWPAT               0x60020

/*  Dispway and Cuwsow Contwow Wegistews (70000h 7FFFFh) */
#define DISP_SW               0x70000
#define DISP_SWC              0x70004
#define PIXCONF               0x70008
#define PIXCONF1              0x70009
#define BWTCNTW               0x7000C
#define SWF                   0x70014
#define DPWYBASE              0x70020
#define DPWYSTAS              0x70024
#define CUWCNTW               0x70080
#define CUWBASE               0x70084
#define CUWPOS                0x70088


/* VGA Wegistews */

/* SMWAM Wegistews */
#define SMWAM                 0x10

/* Gwaphics Contwow Wegistews */
#define GW_INDEX              0x3CE
#define GW_DATA               0x3CF

#define GW10                  0x10
#define GW11                  0x11

/* CWT Contwowwew Wegistews */
#define CW_INDEX_MDA          0x3B4
#define CW_INDEX_CGA          0x3D4
#define CW_DATA_MDA           0x3B5
#define CW_DATA_CGA           0x3D5

#define CW30                  0x30
#define CW31                  0x31
#define CW32                  0x32
#define CW33                  0x33
#define CW35                  0x35
#define CW39                  0x39
#define CW40                  0x40
#define CW41                  0x41
#define CW42                  0x42
#define CW70                  0x70
#define CW80                  0x80 
#define CW81                  0x82

/* Extended VGA Wegistews */

/* Genewaw Contwow and Status Wegistews */
#define ST00                  0x3C2
#define ST01_MDA              0x3BA
#define ST01_CGA              0x3DA
#define FWC_WEAD              0x3CA
#define FWC_WWITE_MDA         0x3BA
#define FWC_WWITE_CGA         0x3DA
#define MSW_WEAD              0x3CC
#define MSW_WWITE             0x3C2

/* Sequencew Wegistews */
#define SW_INDEX              0x3C4
#define SW_DATA               0x3C5

#define SW01                  0x01
#define SW02                  0x02
#define SW03                  0x03
#define SW04                  0x04
#define SW07                  0x07

/* Gwaphics Contwowwew Wegistews */
#define GW00                  0x00   
#define GW01                  0x01
#define GW02                  0x02
#define GW03                  0x03
#define GW04                  0x04
#define GW05                  0x05
#define GW06                  0x06
#define GW07                  0x07
#define GW08                  0x08  

/* Attwibute Contwowwew Wegistews */
#define ATTW_WWITE              0x3C0
#define ATTW_WEAD               0x3C1

/* VGA Cowow Pawette Wegistews */

/* CWUT */
#define CWUT_DATA             0x3C9        /* DACDATA */
#define CWUT_INDEX_WEAD       0x3C7        /* DACWX */
#define CWUT_INDEX_WWITE      0x3C8        /* DACWX */
#define DACMASK               0x3C6

/* CWT Contwowwew Wegistews */
#define CW00                  0x00
#define CW01                  0x01
#define CW02                  0x02
#define CW03                  0x03
#define CW04                  0x04
#define CW05                  0x05
#define CW06                  0x06
#define CW07                  0x07
#define CW08                  0x08
#define CW09                  0x09
#define CW0A                  0x0A
#define CW0B                  0x0B
#define CW0C                  0x0C
#define CW0D                  0x0D
#define CW0E                  0x0E
#define CW0F                  0x0F
#define CW10                  0x10
#define CW11                  0x11
#define CW12                  0x12
#define CW13                  0x13
#define CW14                  0x14
#define CW15                  0x15
#define CW16                  0x16
#define CW17                  0x17
#define CW18                  0x18

#endif /* __I810_WEGS_H__ */
