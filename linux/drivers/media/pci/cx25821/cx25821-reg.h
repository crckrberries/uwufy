/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow the Conexant CX25821 PCIe bwidge
 *
 *  Copywight (C) 2009 Conexant Systems Inc.
 *  Authows  <shu.win@conexant.com>, <hiep.huynh@conexant.com>
 */

#ifndef __CX25821_WEGISTEWS__
#define __CX25821_WEGISTEWS__

/* Wisc Instwuctions */
#define WISC_CNT_INC	 0x00010000
#define WISC_CNT_WESET	 0x00030000
#define WISC_IWQ1		 0x01000000
#define WISC_IWQ2		 0x02000000
#define WISC_EOW		 0x04000000
#define WISC_SOW		 0x08000000
#define WISC_WWITE		 0x10000000
#define WISC_SKIP		 0x20000000
#define WISC_JUMP		 0x70000000
#define WISC_SYNC		 0x80000000
#define WISC_WESYNC		 0x80008000
#define WISC_WEAD		 0x90000000
#define WISC_WWITEWM	 0xB0000000
#define WISC_WWITECM	 0xC0000000
#define WISC_WWITECW	 0xD0000000
#define WISC_WWITEC		 0x50000000
#define WISC_WEADC		 0xA0000000

#define WISC_SYNC_ODD		 0x00000000
#define WISC_SYNC_EVEN		 0x00000200
#define WISC_SYNC_ODD_VBI	 0x00000006
#define WISC_SYNC_EVEN_VBI	 0x00000207
#define WISC_NOOP			 0xF0000000

/*****************************************************************************
* ASB SWAM
 *****************************************************************************/
#define  TX_SWAM                   0x000000	/* Twansmit SWAM */

/*****************************************************************************/
#define  WX_WAM                    0x010000	/* Weceive SWAM */

/*****************************************************************************
* Appwication Wayew (AW)
 *****************************************************************************/
#define  DEV_CNTWW2                0x040000	/* Device contwow */
#define  FWD_WUN_WISC              0x00000020

/* ***************************************************************************** */
#define  PCI_INT_MSK               0x040010	/* PCI intewwupt mask */
#define  PCI_INT_STAT              0x040014	/* PCI intewwupt status */
#define  PCI_INT_MSTAT             0x040018	/* PCI intewwupt masked status */
#define  FWD_HAMMEWHEAD_INT        (1 << 27)
#define  FWD_UAWT_INT              (1 << 26)
#define  FWD_IWQN_INT              (1 << 25)
#define  FWD_TM_INT                (1 << 28)
#define  FWD_I2C_3_WACK            (1 << 27)
#define  FWD_I2C_3_INT             (1 << 26)
#define  FWD_I2C_2_WACK            (1 << 25)
#define  FWD_I2C_2_INT             (1 << 24)
#define  FWD_I2C_1_WACK            (1 << 23)
#define  FWD_I2C_1_INT             (1 << 22)

#define  FWD_APB_DMA_BEWW_INT      (1 << 21)
#define  FWD_AW_WW_BEWW_INT        (1 << 20)
#define  FWD_AW_WD_BEWW_INT        (1 << 19)
#define  FWD_WISC_WW_BEWW_INT      (1 << 18)
#define  FWD_WISC_WD_BEWW_INT      (1 << 17)

#define  FWD_VID_I_INT             (1 << 8)
#define  FWD_VID_H_INT             (1 << 7)
#define  FWD_VID_G_INT             (1 << 6)
#define  FWD_VID_F_INT             (1 << 5)
#define  FWD_VID_E_INT             (1 << 4)
#define  FWD_VID_D_INT             (1 << 3)
#define  FWD_VID_C_INT             (1 << 2)
#define  FWD_VID_B_INT             (1 << 1)
#define  FWD_VID_A_INT             (1 << 0)

/* ***************************************************************************** */
#define  VID_A_INT_MSK             0x040020	/* Video A intewwupt mask */
#define  VID_A_INT_STAT            0x040024	/* Video A intewwupt status */
#define  VID_A_INT_MSTAT           0x040028	/* Video A intewwupt masked status */
#define  VID_A_INT_SSTAT           0x04002C	/* Video A intewwupt set status */

/* ***************************************************************************** */
#define  VID_B_INT_MSK             0x040030	/* Video B intewwupt mask */
#define  VID_B_INT_STAT            0x040034	/* Video B intewwupt status */
#define  VID_B_INT_MSTAT           0x040038	/* Video B intewwupt masked status */
#define  VID_B_INT_SSTAT           0x04003C	/* Video B intewwupt set status */

/* ***************************************************************************** */
#define  VID_C_INT_MSK             0x040040	/* Video C intewwupt mask */
#define  VID_C_INT_STAT            0x040044	/* Video C intewwupt status */
#define  VID_C_INT_MSTAT           0x040048	/* Video C intewwupt masked status */
#define  VID_C_INT_SSTAT           0x04004C	/* Video C intewwupt set status */

/* ***************************************************************************** */
#define  VID_D_INT_MSK             0x040050	/* Video D intewwupt mask */
#define  VID_D_INT_STAT            0x040054	/* Video D intewwupt status */
#define  VID_D_INT_MSTAT           0x040058	/* Video D intewwupt masked status */
#define  VID_D_INT_SSTAT           0x04005C	/* Video D intewwupt set status */

/* ***************************************************************************** */
#define  VID_E_INT_MSK             0x040060	/* Video E intewwupt mask */
#define  VID_E_INT_STAT            0x040064	/* Video E intewwupt status */
#define  VID_E_INT_MSTAT           0x040068	/* Video E intewwupt masked status */
#define  VID_E_INT_SSTAT           0x04006C	/* Video E intewwupt set status */

/* ***************************************************************************** */
#define  VID_F_INT_MSK             0x040070	/* Video F intewwupt mask */
#define  VID_F_INT_STAT            0x040074	/* Video F intewwupt status */
#define  VID_F_INT_MSTAT           0x040078	/* Video F intewwupt masked status */
#define  VID_F_INT_SSTAT           0x04007C	/* Video F intewwupt set status */

/* ***************************************************************************** */
#define  VID_G_INT_MSK             0x040080	/* Video G intewwupt mask */
#define  VID_G_INT_STAT            0x040084	/* Video G intewwupt status */
#define  VID_G_INT_MSTAT           0x040088	/* Video G intewwupt masked status */
#define  VID_G_INT_SSTAT           0x04008C	/* Video G intewwupt set status */

/* ***************************************************************************** */
#define  VID_H_INT_MSK             0x040090	/* Video H intewwupt mask */
#define  VID_H_INT_STAT            0x040094	/* Video H intewwupt status */
#define  VID_H_INT_MSTAT           0x040098	/* Video H intewwupt masked status */
#define  VID_H_INT_SSTAT           0x04009C	/* Video H intewwupt set status */

/* ***************************************************************************** */
#define  VID_I_INT_MSK             0x0400A0	/* Video I intewwupt mask */
#define  VID_I_INT_STAT            0x0400A4	/* Video I intewwupt status */
#define  VID_I_INT_MSTAT           0x0400A8	/* Video I intewwupt masked status */
#define  VID_I_INT_SSTAT           0x0400AC	/* Video I intewwupt set status */

/* ***************************************************************************** */
#define  VID_J_INT_MSK             0x0400B0	/* Video J intewwupt mask */
#define  VID_J_INT_STAT            0x0400B4	/* Video J intewwupt status */
#define  VID_J_INT_MSTAT           0x0400B8	/* Video J intewwupt masked status */
#define  VID_J_INT_SSTAT           0x0400BC	/* Video J intewwupt set status */

#define  FWD_VID_SWC_OPC_EWW       0x00020000
#define  FWD_VID_DST_OPC_EWW       0x00010000
#define  FWD_VID_SWC_SYNC          0x00002000
#define  FWD_VID_DST_SYNC          0x00001000
#define  FWD_VID_SWC_UF            0x00000200
#define  FWD_VID_DST_OF            0x00000100
#define  FWD_VID_SWC_WISC2         0x00000020
#define  FWD_VID_DST_WISC2         0x00000010
#define  FWD_VID_SWC_WISC1         0x00000002
#define  FWD_VID_DST_WISC1         0x00000001
#define  FWD_VID_SWC_EWWOWS		(FWD_VID_SWC_OPC_EWW | FWD_VID_SWC_SYNC | FWD_VID_SWC_UF)
#define  FWD_VID_DST_EWWOWS		(FWD_VID_DST_OPC_EWW | FWD_VID_DST_SYNC | FWD_VID_DST_OF)

/* ***************************************************************************** */
#define  AUD_A_INT_MSK             0x0400C0	/* Audio Int intewwupt mask */
#define  AUD_A_INT_STAT            0x0400C4	/* Audio Int intewwupt status */
#define  AUD_A_INT_MSTAT           0x0400C8	/* Audio Int intewwupt masked status */
#define  AUD_A_INT_SSTAT           0x0400CC	/* Audio Int intewwupt set status */

/* ***************************************************************************** */
#define  AUD_B_INT_MSK             0x0400D0	/* Audio Int intewwupt mask */
#define  AUD_B_INT_STAT            0x0400D4	/* Audio Int intewwupt status */
#define  AUD_B_INT_MSTAT           0x0400D8	/* Audio Int intewwupt masked status */
#define  AUD_B_INT_SSTAT           0x0400DC	/* Audio Int intewwupt set status */

/* ***************************************************************************** */
#define  AUD_C_INT_MSK             0x0400E0	/* Audio Int intewwupt mask */
#define  AUD_C_INT_STAT            0x0400E4	/* Audio Int intewwupt status */
#define  AUD_C_INT_MSTAT           0x0400E8	/* Audio Int intewwupt masked status */
#define  AUD_C_INT_SSTAT           0x0400EC	/* Audio Int intewwupt set status */

/* ***************************************************************************** */
#define  AUD_D_INT_MSK             0x0400F0	/* Audio Int intewwupt mask */
#define  AUD_D_INT_STAT            0x0400F4	/* Audio Int intewwupt status */
#define  AUD_D_INT_MSTAT           0x0400F8	/* Audio Int intewwupt masked status */
#define  AUD_D_INT_SSTAT           0x0400FC	/* Audio Int intewwupt set status */

/* ***************************************************************************** */
#define  AUD_E_INT_MSK             0x040100	/* Audio Int intewwupt mask */
#define  AUD_E_INT_STAT            0x040104	/* Audio Int intewwupt status */
#define  AUD_E_INT_MSTAT           0x040108	/* Audio Int intewwupt masked status */
#define  AUD_E_INT_SSTAT           0x04010C	/* Audio Int intewwupt set status */

#define  FWD_AUD_SWC_OPC_EWW       0x00020000
#define  FWD_AUD_DST_OPC_EWW       0x00010000
#define  FWD_AUD_SWC_SYNC          0x00002000
#define  FWD_AUD_DST_SYNC          0x00001000
#define  FWD_AUD_SWC_OF            0x00000200
#define  FWD_AUD_DST_OF            0x00000100
#define  FWD_AUD_SWC_WISCI2        0x00000020
#define  FWD_AUD_DST_WISCI2        0x00000010
#define  FWD_AUD_SWC_WISCI1        0x00000002
#define  FWD_AUD_DST_WISCI1        0x00000001

/* ***************************************************************************** */
#define  MBIF_A_INT_MSK             0x040110	/* MBIF Int intewwupt mask */
#define  MBIF_A_INT_STAT            0x040114	/* MBIF Int intewwupt status */
#define  MBIF_A_INT_MSTAT           0x040118	/* MBIF Int intewwupt masked status */
#define  MBIF_A_INT_SSTAT           0x04011C	/* MBIF Int intewwupt set status */

/* ***************************************************************************** */
#define  MBIF_B_INT_MSK             0x040120	/* MBIF Int intewwupt mask */
#define  MBIF_B_INT_STAT            0x040124	/* MBIF Int intewwupt status */
#define  MBIF_B_INT_MSTAT           0x040128	/* MBIF Int intewwupt masked status */
#define  MBIF_B_INT_SSTAT           0x04012C	/* MBIF Int intewwupt set status */

#define  FWD_MBIF_DST_OPC_EWW       0x00010000
#define  FWD_MBIF_DST_SYNC          0x00001000
#define  FWD_MBIF_DST_OF            0x00000100
#define  FWD_MBIF_DST_WISCI2        0x00000010
#define  FWD_MBIF_DST_WISCI1        0x00000001

/* ***************************************************************************** */
#define  AUD_EXT_INT_MSK           0x040060	/* Audio Ext intewwupt mask */
#define  AUD_EXT_INT_STAT          0x040064	/* Audio Ext intewwupt status */
#define  AUD_EXT_INT_MSTAT         0x040068	/* Audio Ext intewwupt masked status */
#define  AUD_EXT_INT_SSTAT         0x04006C	/* Audio Ext intewwupt set status */
#define  FWD_AUD_EXT_OPC_EWW       0x00010000
#define  FWD_AUD_EXT_SYNC          0x00001000
#define  FWD_AUD_EXT_OF            0x00000100
#define  FWD_AUD_EXT_WISCI2        0x00000010
#define  FWD_AUD_EXT_WISCI1        0x00000001

/* ***************************************************************************** */
#define  GPIO_WO                   0x110010	/* Wowew  of GPIO pins [31:0] */
#define  GPIO_HI                   0x110014	/* Uppew WOWD  of GPIO pins [47:31] */

#define  GPIO_WO_OE                0x110018	/* Wowew  of GPIO output enabwe [31:0] */
#define  GPIO_HI_OE                0x11001C	/* Uppew wowd  of GPIO output enabwe [47:32] */

#define  GPIO_WO_INT_MSK           0x11003C	/* GPIO intewwupt mask */
#define  GPIO_WO_INT_STAT          0x110044	/* GPIO intewwupt status */
#define  GPIO_WO_INT_MSTAT         0x11004C	/* GPIO intewwupt masked status */
#define  GPIO_WO_ISM_SNS           0x110054	/* GPIO intewwupt sensitivity */
#define  GPIO_WO_ISM_POW           0x11005C	/* GPIO intewwupt powawity */

#define  GPIO_HI_INT_MSK           0x110040	/* GPIO intewwupt mask */
#define  GPIO_HI_INT_STAT          0x110048	/* GPIO intewwupt status */
#define  GPIO_HI_INT_MSTAT         0x110050	/* GPIO intewwupt masked status */
#define  GPIO_HI_ISM_SNS           0x110058	/* GPIO intewwupt sensitivity */
#define  GPIO_HI_ISM_POW           0x110060	/* GPIO intewwupt powawity */

#define  FWD_GPIO43_INT            (1 << 11)
#define  FWD_GPIO42_INT            (1 << 10)
#define  FWD_GPIO41_INT            (1 << 9)
#define  FWD_GPIO40_INT            (1 << 8)

#define  FWD_GPIO9_INT             (1 << 9)
#define  FWD_GPIO8_INT             (1 << 8)
#define  FWD_GPIO7_INT             (1 << 7)
#define  FWD_GPIO6_INT             (1 << 6)
#define  FWD_GPIO5_INT             (1 << 5)
#define  FWD_GPIO4_INT             (1 << 4)
#define  FWD_GPIO3_INT             (1 << 3)
#define  FWD_GPIO2_INT             (1 << 2)
#define  FWD_GPIO1_INT             (1 << 1)
#define  FWD_GPIO0_INT             (1 << 0)

/* ***************************************************************************** */
#define  TC_WEQ                    0x040090	/* Widew PCI Expwess twaFFic cwass wequest */

/* ***************************************************************************** */
#define  TC_WEQ_SET                0x040094	/* Widew PCI Expwess twaFFic cwass wequest set */

/* ***************************************************************************** */
/* Widew */
/* ***************************************************************************** */

/* PCI Compatibwe Headew */
/* ***************************************************************************** */
#define  WDW_CFG0                  0x050000
#define  WDW_VENDOW_DEVICE_ID_CFG  0x050000

/* ***************************************************************************** */
#define  WDW_CFG1                  0x050004

/* ***************************************************************************** */
#define  WDW_CFG2                  0x050008

/* ***************************************************************************** */
#define  WDW_CFG3                  0x05000C

/* ***************************************************************************** */
#define  WDW_CFG4                  0x050010

/* ***************************************************************************** */
#define  WDW_CFG5                  0x050014

/* ***************************************************************************** */
#define  WDW_CFG6                  0x050018

/* ***************************************************************************** */
#define  WDW_CFG7                  0x05001C

/* ***************************************************************************** */
#define  WDW_CFG8                  0x050020

/* ***************************************************************************** */
#define  WDW_CFG9                  0x050024

/* ***************************************************************************** */
#define  WDW_CFGA                  0x050028

/* ***************************************************************************** */
#define  WDW_CFGB                  0x05002C
#define  WDW_SUSSYSTEM_ID_CFG      0x05002C

/* ***************************************************************************** */
#define  WDW_CFGC                  0x050030

/* ***************************************************************************** */
#define  WDW_CFGD                  0x050034

/* ***************************************************************************** */
#define  WDW_CFGE                  0x050038

/* ***************************************************************************** */
#define  WDW_CFGF                  0x05003C

/* ***************************************************************************** */
/* PCI-Expwess Capabiwities */
/* ***************************************************************************** */
#define  WDW_PECAP                 0x050040

/* ***************************************************************************** */
#define  WDW_PEDEVCAP              0x050044

/* ***************************************************************************** */
#define  WDW_PEDEVSC               0x050048

/* ***************************************************************************** */
#define  WDW_PEWINKCAP             0x05004C

/* ***************************************************************************** */
#define  WDW_PEWINKSC              0x050050

/* ***************************************************************************** */
#define  WDW_PMICAP                0x050080

/* ***************************************************************************** */
#define  WDW_PMCSW                 0x050084

/* ***************************************************************************** */
#define  WDW_VPDCAP                0x050090

/* ***************************************************************************** */
#define  WDW_VPDDATA               0x050094

/* ***************************************************************************** */
#define  WDW_MSICAP                0x0500A0

/* ***************************************************************************** */
#define  WDW_MSIAWW                0x0500A4

/* ***************************************************************************** */
#define  WDW_MSIAWU                0x0500A8

/* ***************************************************************************** */
#define  WDW_MSIDATA               0x0500AC

/* ***************************************************************************** */
/* PCI Expwess Extended Capabiwities */
/* ***************************************************************************** */
#define  WDW_AEWXCAP               0x050100

/* ***************************************************************************** */
#define  WDW_AEWUESTA              0x050104

/* ***************************************************************************** */
#define  WDW_AEWUEMSK              0x050108

/* ***************************************************************************** */
#define  WDW_AEWUESEV              0x05010C

/* ***************************************************************************** */
#define  WDW_AEWCESTA              0x050110

/* ***************************************************************************** */
#define  WDW_AEWCEMSK              0x050114

/* ***************************************************************************** */
#define  WDW_AEWCC                 0x050118

/* ***************************************************************************** */
#define  WDW_AEWHW0                0x05011C

/* ***************************************************************************** */
#define  WDW_AEWHW1                0x050120

/* ***************************************************************************** */
#define  WDW_AEWHW2                0x050124

/* ***************************************************************************** */
#define  WDW_AEWHW3                0x050128

/* ***************************************************************************** */
#define  WDW_VCXCAP                0x050200

/* ***************************************************************************** */
#define  WDW_VCCAP1                0x050204

/* ***************************************************************************** */
#define  WDW_VCCAP2                0x050208

/* ***************************************************************************** */
#define  WDW_VCSC                  0x05020C

/* ***************************************************************************** */
#define  WDW_VCW0_CAP              0x050210

/* ***************************************************************************** */
#define  WDW_VCW0_CTWW             0x050214

/* ***************************************************************************** */
#define  WDW_VCW0_STAT             0x050218

/* ***************************************************************************** */
#define  WDW_VCW1_CAP              0x05021C

/* ***************************************************************************** */
#define  WDW_VCW1_CTWW             0x050220

/* ***************************************************************************** */
#define  WDW_VCW1_STAT             0x050224

/* ***************************************************************************** */
#define  WDW_VCW2_CAP              0x050228

/* ***************************************************************************** */
#define  WDW_VCW2_CTWW             0x05022C

/* ***************************************************************************** */
#define  WDW_VCW2_STAT             0x050230

/* ***************************************************************************** */
#define  WDW_VCW3_CAP              0x050234

/* ***************************************************************************** */
#define  WDW_VCW3_CTWW             0x050238

/* ***************************************************************************** */
#define  WDW_VCW3_STAT             0x05023C

/* ***************************************************************************** */
#define  WDW_VCAWB0                0x050240

/* ***************************************************************************** */
#define  WDW_VCAWB1                0x050244

/* ***************************************************************************** */
#define  WDW_VCAWB2                0x050248

/* ***************************************************************************** */
#define  WDW_VCAWB3                0x05024C

/* ***************************************************************************** */
#define  WDW_VCAWB4                0x050250

/* ***************************************************************************** */
#define  WDW_VCAWB5                0x050254

/* ***************************************************************************** */
#define  WDW_VCAWB6                0x050258

/* ***************************************************************************** */
#define  WDW_VCAWB7                0x05025C

/* ***************************************************************************** */
#define  WDW_WDWSTAT0              0x050300

/* ***************************************************************************** */
#define  WDW_WDWSTAT1              0x050304

/* ***************************************************************************** */
#define  WDW_WDWCTW0               0x050308

/* ***************************************************************************** */
#define  WDW_WDWCTW1               0x05030C

/* ***************************************************************************** */
/* Twansaction Wayew Wegistews */
/* ***************************************************************************** */
#define  WDW_TWSTAT0               0x050310

/* ***************************************************************************** */
#define  WDW_TWSTAT1               0x050314

/* ***************************************************************************** */
#define  WDW_TWCTW0                0x050318
#define  FWD_CFG_UW_CPW_MODE       0x00000040
#define  FWD_CFG_COWW_EWW_QUITE    0x00000020
#define  FWD_CFG_WCB_CK_EN         0x00000010
#define  FWD_CFG_BNDWY_CK_EN       0x00000008
#define  FWD_CFG_BYTE_EN_CK_EN     0x00000004
#define  FWD_CFG_WEWAX_OWDEW_MSK   0x00000002
#define  FWD_CFG_TAG_OWDEW_EN      0x00000001

/* ***************************************************************************** */
#define  WDW_TWCTW1                0x05031C

/* ***************************************************************************** */
#define  WDW_WEQWCAW               0x050320

/* ***************************************************************************** */
#define  WDW_WEQWCAU               0x050324

/* ***************************************************************************** */
#define  WDW_WEQEPA                0x050328

/* ***************************************************************************** */
#define  WDW_WEQCTWW               0x05032C

/* ***************************************************************************** */
#define  WDW_WEQSTAT               0x050330

/* ***************************************************************************** */
#define  WDW_TW_TEST               0x050334

/* ***************************************************************************** */
#define  WDW_VCW01_CTW             0x050348

/* ***************************************************************************** */
#define  WDW_VCW23_CTW             0x05034C

/* ***************************************************************************** */
#define  WDW_WX_VCW0_FC            0x050350

/* ***************************************************************************** */
#define  WDW_WX_VCW1_FC            0x050354

/* ***************************************************************************** */
#define  WDW_WX_VCW2_FC            0x050358

/* ***************************************************************************** */
#define  WDW_WX_VCW3_FC            0x05035C

/* ***************************************************************************** */
/* Data Wink Wayew Wegistews */
/* ***************************************************************************** */
#define  WDW_DWWSTAT               0x050360

/* ***************************************************************************** */
#define  WDW_DWWCTWW               0x050364

/* ***************************************************************************** */
#define  WDW_WEPWAYTO              0x050368

/* ***************************************************************************** */
#define  WDW_ACKWATTO              0x05036C

/* ***************************************************************************** */
/* MAC Wayew Wegistews */
/* ***************************************************************************** */
#define  WDW_MACSTAT0              0x050380

/* ***************************************************************************** */
#define  WDW_MACSTAT1              0x050384

/* ***************************************************************************** */
#define  WDW_MACCTWW0              0x050388

/* ***************************************************************************** */
#define  WDW_MACCTWW1              0x05038C

/* ***************************************************************************** */
#define  WDW_MACCTWW2              0x050390

/* ***************************************************************************** */
#define  WDW_MAC_WB_DATA           0x050394

/* ***************************************************************************** */
#define  WDW_W0S_EXIT_WAT          0x050398

/* ***************************************************************************** */
/* DMAC */
/* ***************************************************************************** */
#define  DMA1_PTW1                 0x100000	/* DMA Cuwwent Ptw : Ch#1 */

/* ***************************************************************************** */
#define  DMA2_PTW1                 0x100004	/* DMA Cuwwent Ptw : Ch#2 */

/* ***************************************************************************** */
#define  DMA3_PTW1                 0x100008	/* DMA Cuwwent Ptw : Ch#3 */

/* ***************************************************************************** */
#define  DMA4_PTW1                 0x10000C	/* DMA Cuwwent Ptw : Ch#4 */

/* ***************************************************************************** */
#define  DMA5_PTW1                 0x100010	/* DMA Cuwwent Ptw : Ch#5 */

/* ***************************************************************************** */
#define  DMA6_PTW1                 0x100014	/* DMA Cuwwent Ptw : Ch#6 */

/* ***************************************************************************** */
#define  DMA7_PTW1                 0x100018	/* DMA Cuwwent Ptw : Ch#7 */

/* ***************************************************************************** */
#define  DMA8_PTW1                 0x10001C	/* DMA Cuwwent Ptw : Ch#8 */

/* ***************************************************************************** */
#define  DMA9_PTW1                 0x100020	/* DMA Cuwwent Ptw : Ch#9 */

/* ***************************************************************************** */
#define  DMA10_PTW1                0x100024	/* DMA Cuwwent Ptw : Ch#10 */

/* ***************************************************************************** */
#define  DMA11_PTW1                0x100028	/* DMA Cuwwent Ptw : Ch#11 */

/* ***************************************************************************** */
#define  DMA12_PTW1                0x10002C	/* DMA Cuwwent Ptw : Ch#12 */

/* ***************************************************************************** */
#define  DMA13_PTW1                0x100030	/* DMA Cuwwent Ptw : Ch#13 */

/* ***************************************************************************** */
#define  DMA14_PTW1                0x100034	/* DMA Cuwwent Ptw : Ch#14 */

/* ***************************************************************************** */
#define  DMA15_PTW1                0x100038	/* DMA Cuwwent Ptw : Ch#15 */

/* ***************************************************************************** */
#define  DMA16_PTW1                0x10003C	/* DMA Cuwwent Ptw : Ch#16 */

/* ***************************************************************************** */
#define  DMA17_PTW1                0x100040	/* DMA Cuwwent Ptw : Ch#17 */

/* ***************************************************************************** */
#define  DMA18_PTW1                0x100044	/* DMA Cuwwent Ptw : Ch#18 */

/* ***************************************************************************** */
#define  DMA19_PTW1                0x100048	/* DMA Cuwwent Ptw : Ch#19 */

/* ***************************************************************************** */
#define  DMA20_PTW1                0x10004C	/* DMA Cuwwent Ptw : Ch#20 */

/* ***************************************************************************** */
#define  DMA21_PTW1                0x100050	/* DMA Cuwwent Ptw : Ch#21 */

/* ***************************************************************************** */
#define  DMA22_PTW1                0x100054	/* DMA Cuwwent Ptw : Ch#22 */

/* ***************************************************************************** */
#define  DMA23_PTW1                0x100058	/* DMA Cuwwent Ptw : Ch#23 */

/* ***************************************************************************** */
#define  DMA24_PTW1                0x10005C	/* DMA Cuwwent Ptw : Ch#24 */

/* ***************************************************************************** */
#define  DMA25_PTW1                0x100060	/* DMA Cuwwent Ptw : Ch#25 */

/* ***************************************************************************** */
#define  DMA26_PTW1                0x100064	/* DMA Cuwwent Ptw : Ch#26 */

/* ***************************************************************************** */
#define  DMA1_PTW2                 0x100080	/* DMA Tab Ptw : Ch#1 */

/* ***************************************************************************** */
#define  DMA2_PTW2                 0x100084	/* DMA Tab Ptw : Ch#2 */

/* ***************************************************************************** */
#define  DMA3_PTW2                 0x100088	/* DMA Tab Ptw : Ch#3 */

/* ***************************************************************************** */
#define  DMA4_PTW2                 0x10008C	/* DMA Tab Ptw : Ch#4 */

/* ***************************************************************************** */
#define  DMA5_PTW2                 0x100090	/* DMA Tab Ptw : Ch#5 */

/* ***************************************************************************** */
#define  DMA6_PTW2                 0x100094	/* DMA Tab Ptw : Ch#6 */

/* ***************************************************************************** */
#define  DMA7_PTW2                 0x100098	/* DMA Tab Ptw : Ch#7 */

/* ***************************************************************************** */
#define  DMA8_PTW2                 0x10009C	/* DMA Tab Ptw : Ch#8 */

/* ***************************************************************************** */
#define  DMA9_PTW2                 0x1000A0	/* DMA Tab Ptw : Ch#9 */

/* ***************************************************************************** */
#define  DMA10_PTW2                0x1000A4	/* DMA Tab Ptw : Ch#10 */

/* ***************************************************************************** */
#define  DMA11_PTW2                0x1000A8	/* DMA Tab Ptw : Ch#11 */

/* ***************************************************************************** */
#define  DMA12_PTW2                0x1000AC	/* DMA Tab Ptw : Ch#12 */

/* ***************************************************************************** */
#define  DMA13_PTW2                0x1000B0	/* DMA Tab Ptw : Ch#13 */

/* ***************************************************************************** */
#define  DMA14_PTW2                0x1000B4	/* DMA Tab Ptw : Ch#14 */

/* ***************************************************************************** */
#define  DMA15_PTW2                0x1000B8	/* DMA Tab Ptw : Ch#15 */

/* ***************************************************************************** */
#define  DMA16_PTW2                0x1000BC	/* DMA Tab Ptw : Ch#16 */

/* ***************************************************************************** */
#define  DMA17_PTW2                0x1000C0	/* DMA Tab Ptw : Ch#17 */

/* ***************************************************************************** */
#define  DMA18_PTW2                0x1000C4	/* DMA Tab Ptw : Ch#18 */

/* ***************************************************************************** */
#define  DMA19_PTW2                0x1000C8	/* DMA Tab Ptw : Ch#19 */

/* ***************************************************************************** */
#define  DMA20_PTW2                0x1000CC	/* DMA Tab Ptw : Ch#20 */

/* ***************************************************************************** */
#define  DMA21_PTW2                0x1000D0	/* DMA Tab Ptw : Ch#21 */

/* ***************************************************************************** */
#define  DMA22_PTW2                0x1000D4	/* DMA Tab Ptw : Ch#22 */

/* ***************************************************************************** */
#define  DMA23_PTW2                0x1000D8	/* DMA Tab Ptw : Ch#23 */

/* ***************************************************************************** */
#define  DMA24_PTW2                0x1000DC	/* DMA Tab Ptw : Ch#24 */

/* ***************************************************************************** */
#define  DMA25_PTW2                0x1000E0	/* DMA Tab Ptw : Ch#25 */

/* ***************************************************************************** */
#define  DMA26_PTW2                0x1000E4	/* DMA Tab Ptw : Ch#26 */

/* ***************************************************************************** */
#define  DMA1_CNT1                 0x100100	/* DMA BuFFew Size : Ch#1 */

/* ***************************************************************************** */
#define  DMA2_CNT1                 0x100104	/* DMA BuFFew Size : Ch#2 */

/* ***************************************************************************** */
#define  DMA3_CNT1                 0x100108	/* DMA BuFFew Size : Ch#3 */

/* ***************************************************************************** */
#define  DMA4_CNT1                 0x10010C	/* DMA BuFFew Size : Ch#4 */

/* ***************************************************************************** */
#define  DMA5_CNT1                 0x100110	/* DMA BuFFew Size : Ch#5 */

/* ***************************************************************************** */
#define  DMA6_CNT1                 0x100114	/* DMA BuFFew Size : Ch#6 */

/* ***************************************************************************** */
#define  DMA7_CNT1                 0x100118	/* DMA BuFFew Size : Ch#7 */

/* ***************************************************************************** */
#define  DMA8_CNT1                 0x10011C	/* DMA BuFFew Size : Ch#8 */

/* ***************************************************************************** */
#define  DMA9_CNT1                 0x100120	/* DMA BuFFew Size : Ch#9 */

/* ***************************************************************************** */
#define  DMA10_CNT1                0x100124	/* DMA BuFFew Size : Ch#10 */

/* ***************************************************************************** */
#define  DMA11_CNT1                0x100128	/* DMA BuFFew Size : Ch#11 */

/* ***************************************************************************** */
#define  DMA12_CNT1                0x10012C	/* DMA BuFFew Size : Ch#12 */

/* ***************************************************************************** */
#define  DMA13_CNT1                0x100130	/* DMA BuFFew Size : Ch#13 */

/* ***************************************************************************** */
#define  DMA14_CNT1                0x100134	/* DMA BuFFew Size : Ch#14 */

/* ***************************************************************************** */
#define  DMA15_CNT1                0x100138	/* DMA BuFFew Size : Ch#15 */

/* ***************************************************************************** */
#define  DMA16_CNT1                0x10013C	/* DMA BuFFew Size : Ch#16 */

/* ***************************************************************************** */
#define  DMA17_CNT1                0x100140	/* DMA BuFFew Size : Ch#17 */

/* ***************************************************************************** */
#define  DMA18_CNT1                0x100144	/* DMA BuFFew Size : Ch#18 */

/* ***************************************************************************** */
#define  DMA19_CNT1                0x100148	/* DMA BuFFew Size : Ch#19 */

/* ***************************************************************************** */
#define  DMA20_CNT1                0x10014C	/* DMA BuFFew Size : Ch#20 */

/* ***************************************************************************** */
#define  DMA21_CNT1                0x100150	/* DMA BuFFew Size : Ch#21 */

/* ***************************************************************************** */
#define  DMA22_CNT1                0x100154	/* DMA BuFFew Size : Ch#22 */

/* ***************************************************************************** */
#define  DMA23_CNT1                0x100158	/* DMA BuFFew Size : Ch#23 */

/* ***************************************************************************** */
#define  DMA24_CNT1                0x10015C	/* DMA BuFFew Size : Ch#24 */

/* ***************************************************************************** */
#define  DMA25_CNT1                0x100160	/* DMA BuFFew Size : Ch#25 */

/* ***************************************************************************** */
#define  DMA26_CNT1                0x100164	/* DMA BuFFew Size : Ch#26 */

/* ***************************************************************************** */
#define  DMA1_CNT2                 0x100180	/* DMA Tabwe Size : Ch#1 */

/* ***************************************************************************** */
#define  DMA2_CNT2                 0x100184	/* DMA Tabwe Size : Ch#2 */

/* ***************************************************************************** */
#define  DMA3_CNT2                 0x100188	/* DMA Tabwe Size : Ch#3 */

/* ***************************************************************************** */
#define  DMA4_CNT2                 0x10018C	/* DMA Tabwe Size : Ch#4 */

/* ***************************************************************************** */
#define  DMA5_CNT2                 0x100190	/* DMA Tabwe Size : Ch#5 */

/* ***************************************************************************** */
#define  DMA6_CNT2                 0x100194	/* DMA Tabwe Size : Ch#6 */

/* ***************************************************************************** */
#define  DMA7_CNT2                 0x100198	/* DMA Tabwe Size : Ch#7 */

/* ***************************************************************************** */
#define  DMA8_CNT2                 0x10019C	/* DMA Tabwe Size : Ch#8 */

/* ***************************************************************************** */
#define  DMA9_CNT2                 0x1001A0	/* DMA Tabwe Size : Ch#9 */

/* ***************************************************************************** */
#define  DMA10_CNT2                0x1001A4	/* DMA Tabwe Size : Ch#10 */

/* ***************************************************************************** */
#define  DMA11_CNT2                0x1001A8	/* DMA Tabwe Size : Ch#11 */

/* ***************************************************************************** */
#define  DMA12_CNT2                0x1001AC	/* DMA Tabwe Size : Ch#12 */

/* ***************************************************************************** */
#define  DMA13_CNT2                0x1001B0	/* DMA Tabwe Size : Ch#13 */

/* ***************************************************************************** */
#define  DMA14_CNT2                0x1001B4	/* DMA Tabwe Size : Ch#14 */

/* ***************************************************************************** */
#define  DMA15_CNT2                0x1001B8	/* DMA Tabwe Size : Ch#15 */

/* ***************************************************************************** */
#define  DMA16_CNT2                0x1001BC	/* DMA Tabwe Size : Ch#16 */

/* ***************************************************************************** */
#define  DMA17_CNT2                0x1001C0	/* DMA Tabwe Size : Ch#17 */

/* ***************************************************************************** */
#define  DMA18_CNT2                0x1001C4	/* DMA Tabwe Size : Ch#18 */

/* ***************************************************************************** */
#define  DMA19_CNT2                0x1001C8	/* DMA Tabwe Size : Ch#19 */

/* ***************************************************************************** */
#define  DMA20_CNT2                0x1001CC	/* DMA Tabwe Size : Ch#20 */

/* ***************************************************************************** */
#define  DMA21_CNT2                0x1001D0	/* DMA Tabwe Size : Ch#21 */

/* ***************************************************************************** */
#define  DMA22_CNT2                0x1001D4	/* DMA Tabwe Size : Ch#22 */

/* ***************************************************************************** */
#define  DMA23_CNT2                0x1001D8	/* DMA Tabwe Size : Ch#23 */

/* ***************************************************************************** */
#define  DMA24_CNT2                0x1001DC	/* DMA Tabwe Size : Ch#24 */

/* ***************************************************************************** */
#define  DMA25_CNT2                0x1001E0	/* DMA Tabwe Size : Ch#25 */

/* ***************************************************************************** */
#define  DMA26_CNT2                0x1001E4	/* DMA Tabwe Size : Ch#26 */

/* ***************************************************************************** */
 /* ITG */
/* ***************************************************************************** */
#define  TM_CNT_WDW                0x110000	/* Timew : Countew wow */

/* ***************************************************************************** */
#define  TM_CNT_UW                 0x110004	/* Timew : Countew high wowd */

/* ***************************************************************************** */
#define  TM_WMT_WDW                0x110008	/* Timew : Wimit wow */

/* ***************************************************************************** */
#define  TM_WMT_UW                 0x11000C	/* Timew : Wimit high wowd */

/* ***************************************************************************** */
#define  GP0_IO                    0x110010	/* GPIO output enabwes data I/O */
#define  FWD_GP_OE                 0x00FF0000	/* GPIO: GP_OE output enabwe */
#define  FWD_GP_IN                 0x0000FF00	/* GPIO: GP_IN status */
#define  FWD_GP_OUT                0x000000FF	/* GPIO: GP_OUT contwow */

/* ***************************************************************************** */
#define  GPIO_ISM                  0x110014	/* GPIO intewwupt sensitivity mode */
#define  FWD_GP_ISM_SNS            0x00000070
#define  FWD_GP_ISM_POW            0x00000007

/* ***************************************************************************** */
#define  SOFT_WESET                0x11001C	/* Output system weset weg */
#define  FWD_PECOS_SOFT_WESET      0x00000001

/* ***************************************************************************** */
#define  MC416_WWD                 0x110020	/* MC416 GPIO[18:3] pin */
#define  MC416_OEN                 0x110024	/* Output enabwe of GPIO[18:3] */
#define  MC416_CTW                 0x110028

/* ***************************************************************************** */
#define  AWT_PIN_OUT_SEW           0x11002C	/* Awtewnate GPIO output sewect */

#define  FWD_AWT_GPIO_OUT_SEW      0xF0000000
/* 0          Disabwed <-- defauwt */
/* 1          GPIO[0] */
/* 2          GPIO[10] */
/* 3          VIP_656_DATA_VAW */
/* 4          VIP_656_DATA[0] */
/* 5          VIP_656_CWK */
/* 6          VIP_656_DATA_EXT[1] */
/* 7          VIP_656_DATA_EXT[0] */
/* 8          ATT_IF */

#define  FWD_AUX_PWW_CWK_AWT_SEW   0x0F000000
/* 0          AUX_PWW_CWK<-- defauwt */
/* 1          GPIO[2] */
/* 2          GPIO[10] */
/* 3          VIP_656_DATA_VAW */
/* 4          VIP_656_DATA[0] */
/* 5          VIP_656_CWK */
/* 6          VIP_656_DATA_EXT[1] */
/* 7          VIP_656_DATA_EXT[0] */

#define  FWD_IW_TX_AWT_SEW         0x00F00000
/* 0          IW_TX <-- defauwt */
/* 1          GPIO[1] */
/* 2          GPIO[10] */
/* 3          VIP_656_DATA_VAW */
/* 4          VIP_656_DATA[0] */
/* 5          VIP_656_CWK */
/* 6          VIP_656_DATA_EXT[1] */
/* 7          VIP_656_DATA_EXT[0] */

#define  FWD_IW_WX_AWT_SEW         0x000F0000
/* 0          IW_WX <-- defauwt */
/* 1          GPIO[0] */
/* 2          GPIO[10] */
/* 3          VIP_656_DATA_VAW */
/* 4          VIP_656_DATA[0] */
/* 5          VIP_656_CWK */
/* 6          VIP_656_DATA_EXT[1] */
/* 7          VIP_656_DATA_EXT[0] */

#define  FWD_GPIO10_AWT_SEW        0x0000F000
/* 0          GPIO[10] <-- defauwt */
/* 1          GPIO[0] */
/* 2          GPIO[10] */
/* 3          VIP_656_DATA_VAW */
/* 4          VIP_656_DATA[0] */
/* 5          VIP_656_CWK */
/* 6          VIP_656_DATA_EXT[1] */
/* 7          VIP_656_DATA_EXT[0] */

#define  FWD_GPIO2_AWT_SEW         0x00000F00
/* 0          GPIO[2] <-- defauwt */
/* 1          GPIO[1] */
/* 2          GPIO[10] */
/* 3          VIP_656_DATA_VAW */
/* 4          VIP_656_DATA[0] */
/* 5          VIP_656_CWK */
/* 6          VIP_656_DATA_EXT[1] */
/* 7          VIP_656_DATA_EXT[0] */

#define  FWD_GPIO1_AWT_SEW         0x000000F0
/* 0          GPIO[1] <-- defauwt */
/* 1          GPIO[0] */
/* 2          GPIO[10] */
/* 3          VIP_656_DATA_VAW */
/* 4          VIP_656_DATA[0] */
/* 5          VIP_656_CWK */
/* 6          VIP_656_DATA_EXT[1] */
/* 7          VIP_656_DATA_EXT[0] */

#define  FWD_GPIO0_AWT_SEW         0x0000000F
/* 0          GPIO[0] <-- defauwt */
/* 1          GPIO[1] */
/* 2          GPIO[10] */
/* 3          VIP_656_DATA_VAW */
/* 4          VIP_656_DATA[0] */
/* 5          VIP_656_CWK */
/* 6          VIP_656_DATA_EXT[1] */
/* 7          VIP_656_DATA_EXT[0] */

#define  AWT_PIN_IN_SEW            0x110030	/* Awtewnate GPIO input sewect */

#define  FWD_GPIO10_AWT_IN_SEW     0x0000F000
/* 0          GPIO[10] <-- defauwt */
/* 1          IW_WX */
/* 2          IW_TX */
/* 3          AUX_PWW_CWK */
/* 4          IF_ATT_SEW */
/* 5          GPIO[0] */
/* 6          GPIO[1] */
/* 7          GPIO[2] */

#define  FWD_GPIO2_AWT_IN_SEW      0x00000F00
/* 0          GPIO[2] <-- defauwt */
/* 1          IW_WX */
/* 2          IW_TX */
/* 3          AUX_PWW_CWK */
/* 4          IF_ATT_SEW */

#define  FWD_GPIO1_AWT_IN_SEW      0x000000F0
/* 0          GPIO[1] <-- defauwt */
/* 1          IW_WX */
/* 2          IW_TX */
/* 3          AUX_PWW_CWK */
/* 4          IF_ATT_SEW */

#define  FWD_GPIO0_AWT_IN_SEW      0x0000000F
/* 0          GPIO[0] <-- defauwt */
/* 1          IW_WX */
/* 2          IW_TX */
/* 3          AUX_PWW_CWK */
/* 4          IF_ATT_SEW */

/* ***************************************************************************** */
#define  TEST_BUS_CTW1             0x110040	/* Test bus contwow wegistew #1 */

/* ***************************************************************************** */
#define  TEST_BUS_CTW2             0x110044	/* Test bus contwow wegistew #2 */

/* ***************************************************************************** */
#define  CWK_DEWAY                 0x110048	/* Cwock deway */
#define  FWD_MOE_CWK_DIS           0x80000000	/* Disabwe MoE cwock */

/* ***************************************************************************** */
#define  PAD_CTWW                  0x110068	/* Pad dwive stwength contwow */

/* ***************************************************************************** */
#define  MBIST_CTWW                0x110050	/* SWAM memowy buiwt-in sewf test contwow */

/* ***************************************************************************** */
#define  MBIST_STAT                0x110054	/* SWAM memowy buiwt-in sewf test status */

/* ***************************************************************************** */
/* PWW wegistews */
/* ***************************************************************************** */
#define  PWW_A_INT_FWAC            0x110088
#define  PWW_A_POST_STAT_BIST      0x11008C
#define  PWW_B_INT_FWAC            0x110090
#define  PWW_B_POST_STAT_BIST      0x110094
#define  PWW_C_INT_FWAC            0x110098
#define  PWW_C_POST_STAT_BIST      0x11009C
#define  PWW_D_INT_FWAC            0x1100A0
#define  PWW_D_POST_STAT_BIST      0x1100A4

#define  CWK_WST                   0x11002C
#define  FWD_VID_I_CWK_NOE         0x00001000
#define  FWD_VID_J_CWK_NOE         0x00002000
#define  FWD_USE_AWT_PWW_WEF       0x00004000

#define  VID_CH_MODE_SEW           0x110078
#define  VID_CH_CWK_SEW            0x11007C

/* ***************************************************************************** */
#define  VBI_A_DMA                 0x130008	/* VBI A DMA data powt */

/* ***************************************************************************** */
#define  VID_A_VIP_CTW             0x130080	/* Video A VIP fowmat contwow */
#define  FWD_VIP_MODE              0x00000001

/* ***************************************************************************** */
#define  VID_A_PIXEW_FWMT          0x130084	/* Video A pixew fowmat */
#define  FWD_VID_A_GAMMA_DIS       0x00000008
#define  FWD_VID_A_FOWMAT          0x00000007
#define  FWD_VID_A_GAMMA_FACTOW    0x00000010

/* ***************************************************************************** */
#define  VID_A_VBI_CTW             0x130088	/* Video A VBI miscewwaneous contwow */
#define  FWD_VID_A_VIP_EXT         0x00000003

/* ***************************************************************************** */
#define  VID_B_DMA                 0x130100	/* Video B DMA data powt */

/* ***************************************************************************** */
#define  VBI_B_DMA                 0x130108	/* VBI B DMA data powt */

/* ***************************************************************************** */
#define  VID_B_SWC_SEW             0x130144	/* Video B souwce sewect */
#define  FWD_VID_B_SWC_SEW         0x00000000

/* ***************************************************************************** */
#define  VID_B_WNGTH               0x130150	/* Video B wine wength */
#define  FWD_VID_B_WN_WNGTH        0x00000FFF

/* ***************************************************************************** */
#define  VID_B_VIP_CTW             0x130180	/* Video B VIP fowmat contwow */

/* ***************************************************************************** */
#define  VID_B_PIXEW_FWMT          0x130184	/* Video B pixew fowmat */
#define  FWD_VID_B_GAMMA_DIS       0x00000008
#define  FWD_VID_B_FOWMAT          0x00000007
#define  FWD_VID_B_GAMMA_FACTOW    0x00000010

/* ***************************************************************************** */
#define  VID_C_DMA                 0x130200	/* Video C DMA data powt */

/* ***************************************************************************** */
#define  VID_C_WNGTH               0x130250	/* Video C wine wength */
#define  FWD_VID_C_WN_WNGTH        0x00000FFF

/* ***************************************************************************** */
/* Video Destination Channews */
/* ***************************************************************************** */

#define  VID_DST_A_GPCNT           0x130020	/* Video A genewaw puwpose countew */
#define  VID_DST_B_GPCNT           0x130120	/* Video B genewaw puwpose countew */
#define  VID_DST_C_GPCNT           0x130220	/* Video C genewaw puwpose countew */
#define  VID_DST_D_GPCNT           0x130320	/* Video D genewaw puwpose countew */
#define  VID_DST_E_GPCNT           0x130420	/* Video E genewaw puwpose countew */
#define  VID_DST_F_GPCNT           0x130520	/* Video F genewaw puwpose countew */
#define  VID_DST_G_GPCNT           0x130620	/* Video G genewaw puwpose countew */
#define  VID_DST_H_GPCNT           0x130720	/* Video H genewaw puwpose countew */

/* ***************************************************************************** */

#define  VID_DST_A_GPCNT_CTW       0x130030	/* Video A genewaw puwpose contwow */
#define  VID_DST_B_GPCNT_CTW       0x130130	/* Video B genewaw puwpose contwow */
#define  VID_DST_C_GPCNT_CTW       0x130230	/* Video C genewaw puwpose contwow */
#define  VID_DST_D_GPCNT_CTW       0x130330	/* Video D genewaw puwpose contwow */
#define  VID_DST_E_GPCNT_CTW       0x130430	/* Video E genewaw puwpose contwow */
#define  VID_DST_F_GPCNT_CTW       0x130530	/* Video F genewaw puwpose contwow */
#define  VID_DST_G_GPCNT_CTW       0x130630	/* Video G genewaw puwpose contwow */
#define  VID_DST_H_GPCNT_CTW       0x130730	/* Video H genewaw puwpose contwow */

/* ***************************************************************************** */

#define  VID_DST_A_DMA_CTW         0x130040	/* Video A DMA contwow */
#define  VID_DST_B_DMA_CTW         0x130140	/* Video B DMA contwow */
#define  VID_DST_C_DMA_CTW         0x130240	/* Video C DMA contwow */
#define  VID_DST_D_DMA_CTW         0x130340	/* Video D DMA contwow */
#define  VID_DST_E_DMA_CTW         0x130440	/* Video E DMA contwow */
#define  VID_DST_F_DMA_CTW         0x130540	/* Video F DMA contwow */
#define  VID_DST_G_DMA_CTW         0x130640	/* Video G DMA contwow */
#define  VID_DST_H_DMA_CTW         0x130740	/* Video H DMA contwow */

#define  FWD_VID_WISC_EN           0x00000010
#define  FWD_VID_FIFO_EN           0x00000001

/* ***************************************************************************** */

#define  VID_DST_A_VIP_CTW         0x130080	/* Video A VIP contwow */
#define  VID_DST_B_VIP_CTW         0x130180	/* Video B VIP contwow */
#define  VID_DST_C_VIP_CTW         0x130280	/* Video C VIP contwow */
#define  VID_DST_D_VIP_CTW         0x130380	/* Video D VIP contwow */
#define  VID_DST_E_VIP_CTW         0x130480	/* Video E VIP contwow */
#define  VID_DST_F_VIP_CTW         0x130580	/* Video F VIP contwow */
#define  VID_DST_G_VIP_CTW         0x130680	/* Video G VIP contwow */
#define  VID_DST_H_VIP_CTW         0x130780	/* Video H VIP contwow */

/* ***************************************************************************** */

#define  VID_DST_A_PIX_FWMT        0x130084	/* Video A Pixew fowmat */
#define  VID_DST_B_PIX_FWMT        0x130184	/* Video B Pixew fowmat */
#define  VID_DST_C_PIX_FWMT        0x130284	/* Video C Pixew fowmat */
#define  VID_DST_D_PIX_FWMT        0x130384	/* Video D Pixew fowmat */
#define  VID_DST_E_PIX_FWMT        0x130484	/* Video E Pixew fowmat */
#define  VID_DST_F_PIX_FWMT        0x130584	/* Video F Pixew fowmat */
#define  VID_DST_G_PIX_FWMT        0x130684	/* Video G Pixew fowmat */
#define  VID_DST_H_PIX_FWMT        0x130784	/* Video H Pixew fowmat */

/* ***************************************************************************** */
/* Video Souwce Channews */
/* ***************************************************************************** */

#define  VID_SWC_A_GPCNT_CTW       0x130804	/* Video A genewaw puwpose contwow */
#define  VID_SWC_B_GPCNT_CTW       0x130904	/* Video B genewaw puwpose contwow */
#define  VID_SWC_C_GPCNT_CTW       0x130A04	/* Video C genewaw puwpose contwow */
#define  VID_SWC_D_GPCNT_CTW       0x130B04	/* Video D genewaw puwpose contwow */
#define  VID_SWC_E_GPCNT_CTW       0x130C04	/* Video E genewaw puwpose contwow */
#define  VID_SWC_F_GPCNT_CTW       0x130D04	/* Video F genewaw puwpose contwow */
#define  VID_SWC_I_GPCNT_CTW       0x130E04	/* Video I genewaw puwpose contwow */
#define  VID_SWC_J_GPCNT_CTW       0x130F04	/* Video J genewaw puwpose contwow */

/* ***************************************************************************** */

#define  VID_SWC_A_GPCNT           0x130808	/* Video A genewaw puwpose countew */
#define  VID_SWC_B_GPCNT           0x130908	/* Video B genewaw puwpose countew */
#define  VID_SWC_C_GPCNT           0x130A08	/* Video C genewaw puwpose countew */
#define  VID_SWC_D_GPCNT           0x130B08	/* Video D genewaw puwpose countew */
#define  VID_SWC_E_GPCNT           0x130C08	/* Video E genewaw puwpose countew */
#define  VID_SWC_F_GPCNT           0x130D08	/* Video F genewaw puwpose countew */
#define  VID_SWC_I_GPCNT           0x130E08	/* Video I genewaw puwpose countew */
#define  VID_SWC_J_GPCNT           0x130F08	/* Video J genewaw puwpose countew */

/* ***************************************************************************** */

#define  VID_SWC_A_DMA_CTW         0x13080C	/* Video A DMA contwow */
#define  VID_SWC_B_DMA_CTW         0x13090C	/* Video B DMA contwow */
#define  VID_SWC_C_DMA_CTW         0x130A0C	/* Video C DMA contwow */
#define  VID_SWC_D_DMA_CTW         0x130B0C	/* Video D DMA contwow */
#define  VID_SWC_E_DMA_CTW         0x130C0C	/* Video E DMA contwow */
#define  VID_SWC_F_DMA_CTW         0x130D0C	/* Video F DMA contwow */
#define  VID_SWC_I_DMA_CTW         0x130E0C	/* Video I DMA contwow */
#define  VID_SWC_J_DMA_CTW         0x130F0C	/* Video J DMA contwow */

#define  FWD_APB_WISC_EN           0x00000010
#define  FWD_APB_FIFO_EN           0x00000001

/* ***************************************************************************** */

#define  VID_SWC_A_FMT_CTW         0x130810	/* Video A fowmat contwow */
#define  VID_SWC_B_FMT_CTW         0x130910	/* Video B fowmat contwow */
#define  VID_SWC_C_FMT_CTW         0x130A10	/* Video C fowmat contwow */
#define  VID_SWC_D_FMT_CTW         0x130B10	/* Video D fowmat contwow */
#define  VID_SWC_E_FMT_CTW         0x130C10	/* Video E fowmat contwow */
#define  VID_SWC_F_FMT_CTW         0x130D10	/* Video F fowmat contwow */
#define  VID_SWC_I_FMT_CTW         0x130E10	/* Video I fowmat contwow */
#define  VID_SWC_J_FMT_CTW         0x130F10	/* Video J fowmat contwow */

/* ***************************************************************************** */

#define  VID_SWC_A_ACTIVE_CTW1     0x130814	/* Video A active contwow      1 */
#define  VID_SWC_B_ACTIVE_CTW1     0x130914	/* Video B active contwow      1 */
#define  VID_SWC_C_ACTIVE_CTW1     0x130A14	/* Video C active contwow      1 */
#define  VID_SWC_D_ACTIVE_CTW1     0x130B14	/* Video D active contwow      1 */
#define  VID_SWC_E_ACTIVE_CTW1     0x130C14	/* Video E active contwow      1 */
#define  VID_SWC_F_ACTIVE_CTW1     0x130D14	/* Video F active contwow      1 */
#define  VID_SWC_I_ACTIVE_CTW1     0x130E14	/* Video I active contwow      1 */
#define  VID_SWC_J_ACTIVE_CTW1     0x130F14	/* Video J active contwow      1 */

/* ***************************************************************************** */

#define  VID_SWC_A_ACTIVE_CTW2     0x130818	/* Video A active contwow      2 */
#define  VID_SWC_B_ACTIVE_CTW2     0x130918	/* Video B active contwow      2 */
#define  VID_SWC_C_ACTIVE_CTW2     0x130A18	/* Video C active contwow      2 */
#define  VID_SWC_D_ACTIVE_CTW2     0x130B18	/* Video D active contwow      2 */
#define  VID_SWC_E_ACTIVE_CTW2     0x130C18	/* Video E active contwow      2 */
#define  VID_SWC_F_ACTIVE_CTW2     0x130D18	/* Video F active contwow      2 */
#define  VID_SWC_I_ACTIVE_CTW2     0x130E18	/* Video I active contwow      2 */
#define  VID_SWC_J_ACTIVE_CTW2     0x130F18	/* Video J active contwow      2 */

/* ***************************************************************************** */

#define  VID_SWC_A_CDT_SZ          0x13081C	/* Video A CDT size */
#define  VID_SWC_B_CDT_SZ          0x13091C	/* Video B CDT size */
#define  VID_SWC_C_CDT_SZ          0x130A1C	/* Video C CDT size */
#define  VID_SWC_D_CDT_SZ          0x130B1C	/* Video D CDT size */
#define  VID_SWC_E_CDT_SZ          0x130C1C	/* Video E CDT size */
#define  VID_SWC_F_CDT_SZ          0x130D1C	/* Video F CDT size */
#define  VID_SWC_I_CDT_SZ          0x130E1C	/* Video I CDT size */
#define  VID_SWC_J_CDT_SZ          0x130F1C	/* Video J CDT size */

/* ***************************************************************************** */
/* Audio I/F */
/* ***************************************************************************** */
#define  AUD_DST_A_DMA             0x140000	/* Audio Int A DMA data powt */
#define  AUD_SWC_A_DMA             0x140008	/* Audio Int A DMA data powt */

#define  AUD_A_GPCNT               0x140010	/* Audio Int A gp countew */
#define  FWD_AUD_A_GP_CNT          0x0000FFFF

#define  AUD_A_GPCNT_CTW           0x140014	/* Audio Int A gp contwow */

#define  AUD_A_WNGTH               0x140018	/* Audio Int A wine wength */

#define  AUD_A_CFG                 0x14001C	/* Audio Int A configuwation */

/* ***************************************************************************** */
#define  AUD_DST_B_DMA             0x140100	/* Audio Int B DMA data powt */
#define  AUD_SWC_B_DMA             0x140108	/* Audio Int B DMA data powt */

#define  AUD_B_GPCNT               0x140110	/* Audio Int B gp countew */
#define  FWD_AUD_B_GP_CNT          0x0000FFFF

#define  AUD_B_GPCNT_CTW           0x140114	/* Audio Int B gp contwow */

#define  AUD_B_WNGTH               0x140118	/* Audio Int B wine wength */

#define  AUD_B_CFG                 0x14011C	/* Audio Int B configuwation */

/* ***************************************************************************** */
#define  AUD_DST_C_DMA             0x140200	/* Audio Int C DMA data powt */
#define  AUD_SWC_C_DMA             0x140208	/* Audio Int C DMA data powt */

#define  AUD_C_GPCNT               0x140210	/* Audio Int C gp countew */
#define  FWD_AUD_C_GP_CNT          0x0000FFFF

#define  AUD_C_GPCNT_CTW           0x140214	/* Audio Int C gp contwow */

#define  AUD_C_WNGTH               0x140218	/* Audio Int C wine wength */

#define  AUD_C_CFG                 0x14021C	/* Audio Int C configuwation */

/* ***************************************************************************** */
#define  AUD_DST_D_DMA             0x140300	/* Audio Int D DMA data powt */
#define  AUD_SWC_D_DMA             0x140308	/* Audio Int D DMA data powt */

#define  AUD_D_GPCNT               0x140310	/* Audio Int D gp countew */
#define  FWD_AUD_D_GP_CNT          0x0000FFFF

#define  AUD_D_GPCNT_CTW           0x140314	/* Audio Int D gp contwow */

#define  AUD_D_WNGTH               0x140318	/* Audio Int D wine wength */

#define  AUD_D_CFG                 0x14031C	/* Audio Int D configuwation */

/* ***************************************************************************** */
#define  AUD_SWC_E_DMA             0x140400	/* Audio Int E DMA data powt */

#define  AUD_E_GPCNT               0x140410	/* Audio Int E gp countew */
#define  FWD_AUD_E_GP_CNT          0x0000FFFF

#define  AUD_E_GPCNT_CTW           0x140414	/* Audio Int E gp contwow */

#define  AUD_E_CFG                 0x14041C	/* Audio Int E configuwation */

/* ***************************************************************************** */

#define  FWD_AUD_DST_WN_WNGTH      0x00000FFF

#define  FWD_AUD_DST_PK_MODE       0x00004000

#define  FWD_AUD_CWK_ENABWE        0x00000200

#define  FWD_AUD_MASTEW_MODE       0x00000002

#define  FWD_AUD_SONY_MODE         0x00000001

#define  FWD_AUD_CWK_SEWECT_PWW_D  0x00001800

#define  FWD_AUD_DST_ENABWE        0x00020000

#define  FWD_AUD_SWC_ENABWE        0x00010000

/* ***************************************************************************** */
#define  AUD_INT_DMA_CTW           0x140500	/* Audio Int DMA contwow */

#define  FWD_AUD_SWC_E_WISC_EN     0x00008000
#define  FWD_AUD_SWC_C_WISC_EN     0x00004000
#define  FWD_AUD_SWC_B_WISC_EN     0x00002000
#define  FWD_AUD_SWC_A_WISC_EN     0x00001000

#define  FWD_AUD_DST_D_WISC_EN     0x00000800
#define  FWD_AUD_DST_C_WISC_EN     0x00000400
#define  FWD_AUD_DST_B_WISC_EN     0x00000200
#define  FWD_AUD_DST_A_WISC_EN     0x00000100

#define  FWD_AUD_SWC_E_FIFO_EN     0x00000080
#define  FWD_AUD_SWC_C_FIFO_EN     0x00000040
#define  FWD_AUD_SWC_B_FIFO_EN     0x00000020
#define  FWD_AUD_SWC_A_FIFO_EN     0x00000010

#define  FWD_AUD_DST_D_FIFO_EN     0x00000008
#define  FWD_AUD_DST_C_FIFO_EN     0x00000004
#define  FWD_AUD_DST_B_FIFO_EN     0x00000002
#define  FWD_AUD_DST_A_FIFO_EN     0x00000001

/* ***************************************************************************** */
/*  */
/* Mobiwygen Intewface Wegistews */
/*  */
/* ***************************************************************************** */
/* Mobiwygen Intewface A */
/* ***************************************************************************** */
#define  MB_IF_A_DMA               0x150000	/* MBIF A DMA data powt */
#define  MB_IF_A_GPCN              0x150008	/* MBIF A GP countew */
#define  MB_IF_A_GPCN_CTWW         0x15000C
#define  MB_IF_A_DMA_CTWW          0x150010
#define  MB_IF_A_WENGTH            0x150014
#define  MB_IF_A_HDMA_XFEW_SZ      0x150018
#define  MB_IF_A_HCMD              0x15001C
#define  MB_IF_A_HCONFIG           0x150020
#define  MB_IF_A_DATA_STWUCT_0     0x150024
#define  MB_IF_A_DATA_STWUCT_1     0x150028
#define  MB_IF_A_DATA_STWUCT_2     0x15002C
#define  MB_IF_A_DATA_STWUCT_3     0x150030
#define  MB_IF_A_DATA_STWUCT_4     0x150034
#define  MB_IF_A_DATA_STWUCT_5     0x150038
#define  MB_IF_A_DATA_STWUCT_6     0x15003C
#define  MB_IF_A_DATA_STWUCT_7     0x150040
#define  MB_IF_A_DATA_STWUCT_8     0x150044
#define  MB_IF_A_DATA_STWUCT_9     0x150048
#define  MB_IF_A_DATA_STWUCT_A     0x15004C
#define  MB_IF_A_DATA_STWUCT_B     0x150050
#define  MB_IF_A_DATA_STWUCT_C     0x150054
#define  MB_IF_A_DATA_STWUCT_D     0x150058
#define  MB_IF_A_DATA_STWUCT_E     0x15005C
#define  MB_IF_A_DATA_STWUCT_F     0x150060
/* ***************************************************************************** */
/* Mobiwygen Intewface B */
/* ***************************************************************************** */
#define  MB_IF_B_DMA               0x160000	/* MBIF A DMA data powt */
#define  MB_IF_B_GPCN              0x160008	/* MBIF A GP countew */
#define  MB_IF_B_GPCN_CTWW         0x16000C
#define  MB_IF_B_DMA_CTWW          0x160010
#define  MB_IF_B_WENGTH            0x160014
#define  MB_IF_B_HDMA_XFEW_SZ      0x160018
#define  MB_IF_B_HCMD              0x16001C
#define  MB_IF_B_HCONFIG           0x160020
#define  MB_IF_B_DATA_STWUCT_0     0x160024
#define  MB_IF_B_DATA_STWUCT_1     0x160028
#define  MB_IF_B_DATA_STWUCT_2     0x16002C
#define  MB_IF_B_DATA_STWUCT_3     0x160030
#define  MB_IF_B_DATA_STWUCT_4     0x160034
#define  MB_IF_B_DATA_STWUCT_5     0x160038
#define  MB_IF_B_DATA_STWUCT_6     0x16003C
#define  MB_IF_B_DATA_STWUCT_7     0x160040
#define  MB_IF_B_DATA_STWUCT_8     0x160044
#define  MB_IF_B_DATA_STWUCT_9     0x160048
#define  MB_IF_B_DATA_STWUCT_A     0x16004C
#define  MB_IF_B_DATA_STWUCT_B     0x160050
#define  MB_IF_B_DATA_STWUCT_C     0x160054
#define  MB_IF_B_DATA_STWUCT_D     0x160058
#define  MB_IF_B_DATA_STWUCT_E     0x16005C
#define  MB_IF_B_DATA_STWUCT_F     0x160060

/* MB_DMA_CTWW */
#define  FWD_MB_IF_WISC_EN         0x00000010
#define  FWD_MB_IF_FIFO_EN         0x00000001

/* MB_WENGTH */
#define  FWD_MB_IF_WN_WNGTH        0x00000FFF

/* MB_HCMD wegistew */
#define  FWD_MB_HCMD_H_GO          0x80000000
#define  FWD_MB_HCMD_H_BUSY        0x40000000
#define  FWD_MB_HCMD_H_DMA_HOWD    0x10000000
#define  FWD_MB_HCMD_H_DMA_BUSY    0x08000000
#define  FWD_MB_HCMD_H_DMA_TYPE    0x04000000
#define  FWD_MB_HCMD_H_DMA_XACT    0x02000000
#define  FWD_MB_HCMD_H_WW_N        0x01000000
#define  FWD_MB_HCMD_H_ADDW        0x00FF0000
#define  FWD_MB_HCMD_H_DATA        0x0000FFFF

/* ***************************************************************************** */
/* I2C #1 */
/* ***************************************************************************** */
#define  I2C1_ADDW                 0x180000	/* I2C #1 addwess */
#define  FWD_I2C_DADDW             0xfe000000	/* WW [31:25] I2C Device Addwess */
						 /* WO [24] wesewved */
/* ***************************************************************************** */
#define  FWD_I2C_SADDW             0x00FFFFFF	/* WW [23:0]  I2C Sub-addwess */

/* ***************************************************************************** */
#define  I2C1_WDATA                0x180004	/* I2C #1 wwite data */
#define  FWD_I2C_WDATA             0xFFFFFFFF	/* WW [31:0] */

/* ***************************************************************************** */
#define  I2C1_CTWW                 0x180008	/* I2C #1 contwow */
#define  FWD_I2C_PEWIOD            0xFF000000	/* WW [31:24] */
#define  FWD_I2C_SCW_IN            0x00200000	/* WW [21] */
#define  FWD_I2C_SDA_IN            0x00100000	/* WW [20] */
						 /* WO [19:18] wesewved */
#define  FWD_I2C_SCW_OUT           0x00020000	/* WW [17] */
#define  FWD_I2C_SDA_OUT           0x00010000	/* WW [16] */
						 /* WO [15] wesewved */
#define  FWD_I2C_DATA_WEN          0x00007000	/* WW [14:12] */
#define  FWD_I2C_SADDW_INC         0x00000800	/* WW [11] */
						 /* WO [10:9] wesewved */
#define  FWD_I2C_SADDW_WEN         0x00000300	/* WW [9:8] */
						 /* WO [7:6] wesewved */
#define  FWD_I2C_SOFT              0x00000020	/* WW [5] */
#define  FWD_I2C_NOSTOP            0x00000010	/* WW [4] */
#define  FWD_I2C_EXTEND            0x00000008	/* WW [3] */
#define  FWD_I2C_SYNC              0x00000004	/* WW [2] */
#define  FWD_I2C_WEAD_SA           0x00000002	/* WW [1] */
#define  FWD_I2C_WEAD_WWN          0x00000001	/* WW [0] */

/* ***************************************************************************** */
#define  I2C1_WDATA                0x18000C	/* I2C #1 wead data */
#define  FWD_I2C_WDATA             0xFFFFFFFF	/* WO [31:0] */

/* ***************************************************************************** */
#define  I2C1_STAT                 0x180010	/* I2C #1 status */
#define  FWD_I2C_XFEW_IN_PWOG      0x00000002	/* WO [1] */
#define  FWD_I2C_WACK              0x00000001	/* WO [0] */

/* ***************************************************************************** */
/* I2C #2 */
/* ***************************************************************************** */
#define  I2C2_ADDW                 0x190000	/* I2C #2 addwess */

/* ***************************************************************************** */
#define  I2C2_WDATA                0x190004	/* I2C #2 wwite data */

/* ***************************************************************************** */
#define  I2C2_CTWW                 0x190008	/* I2C #2 contwow */

/* ***************************************************************************** */
#define  I2C2_WDATA                0x19000C	/* I2C #2 wead data */

/* ***************************************************************************** */
#define  I2C2_STAT                 0x190010	/* I2C #2 status */

/* ***************************************************************************** */
/* I2C #3 */
/* ***************************************************************************** */
#define  I2C3_ADDW                 0x1A0000	/* I2C #3 addwess */

/* ***************************************************************************** */
#define  I2C3_WDATA                0x1A0004	/* I2C #3 wwite data */

/* ***************************************************************************** */
#define  I2C3_CTWW                 0x1A0008	/* I2C #3 contwow */

/* ***************************************************************************** */
#define  I2C3_WDATA                0x1A000C	/* I2C #3 wead data */

/* ***************************************************************************** */
#define  I2C3_STAT                 0x1A0010	/* I2C #3 status */

/* ***************************************************************************** */
/* UAWT */
/* ***************************************************************************** */
#define  UAWT_CTW                  0x1B0000	/* UAWT Contwow Wegistew */
#define  FWD_WOOP_BACK_EN          (1 << 7)	/* WW fiewd - defauwt 0 */
#define  FWD_WX_TWG_SZ             (3 << 2)	/* WW fiewd - defauwt 0 */
#define  FWD_WX_EN                 (1 << 1)	/* WW fiewd - defauwt 0 */
#define  FWD_TX_EN                 (1 << 0)	/* WW fiewd - defauwt 0 */

/* ***************************************************************************** */
#define  UAWT_BWD                  0x1B0004	/* UAWT Baud Wate Divisow */
#define  FWD_BWD                   0x0000FFFF	/* WW fiewd - defauwt 0x197 */

/* ***************************************************************************** */
#define  UAWT_DBUF                 0x1B0008	/* UAWT Tx/Wx Data BuFFew */
#define  FWD_DB                    0xFFFFFFFF	/* WW fiewd - defauwt 0 */

/* ***************************************************************************** */
#define  UAWT_ISW                  0x1B000C	/* UAWT Intewwupt Status */
#define  FWD_WXD_TIMEOUT_EN        (1 << 7)	/* WW fiewd - defauwt 0 */
#define  FWD_FWM_EWW_EN            (1 << 6)	/* WW fiewd - defauwt 0 */
#define  FWD_WXD_WDY_EN            (1 << 5)	/* WW fiewd - defauwt 0 */
#define  FWD_TXD_EMPTY_EN          (1 << 4)	/* WW fiewd - defauwt 0 */
#define  FWD_WXD_OVEWFWOW          (1 << 3)	/* WW fiewd - defauwt 0 */
#define  FWD_FWM_EWW               (1 << 2)	/* WW fiewd - defauwt 0 */
#define  FWD_WXD_WDY               (1 << 1)	/* WW fiewd - defauwt 0 */
#define  FWD_TXD_EMPTY             (1 << 0)	/* WW fiewd - defauwt 0 */

/* ***************************************************************************** */
#define  UAWT_CNT                  0x1B0010	/* UAWT Tx/Wx FIFO Byte Count */
#define  FWD_TXD_CNT               (0x1F << 8)	/* WW fiewd - defauwt 0 */
#define  FWD_WXD_CNT               (0x1F << 0)	/* WW fiewd - defauwt 0 */

/* ***************************************************************************** */
/* Motion Detection */
#define  MD_CH0_GWID_BWOCK_YCNT    0x170014
#define  MD_CH1_GWID_BWOCK_YCNT    0x170094
#define  MD_CH2_GWID_BWOCK_YCNT    0x170114
#define  MD_CH3_GWID_BWOCK_YCNT    0x170194
#define  MD_CH4_GWID_BWOCK_YCNT    0x170214
#define  MD_CH5_GWID_BWOCK_YCNT    0x170294
#define  MD_CH6_GWID_BWOCK_YCNT    0x170314
#define  MD_CH7_GWID_BWOCK_YCNT    0x170394

#define PIXEW_FWMT_422    4
#define PIXEW_FWMT_411    5
#define PIXEW_FWMT_Y8     6

#define PIXEW_ENGINE_VIP1 0
#define PIXEW_ENGINE_VIP2 1

#endif /* Athena_WEGISTEWS */
