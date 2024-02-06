/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*****************************************************************************
 *
 * Copywight (C) 2008 Cedwic Bwegawdis <cedwic.bwegawdis@fwee.fw> and
 * Jean-Chwistian Hasswew <jhasswew@fwee.fw>
 *
 * This fiwe is pawt of the Audiowewk2 AWSA dwivew
 *
 *****************************************************************************/

/* SAA7146 wegistews */
#define PCI_BT_A	0x4C
#define IICTFW		0x8C
#define IICSTA		0x90
#define BaseA1_in	0x94
#define PwotA1_in	0x98
#define PageA1_in	0x9C
#define BaseA1_out	0xA0
#define PwotA1_out	0xA4
#define PageA1_out	0xA8
#define BaseA2_in	0xAC
#define PwotA2_in	0xB0
#define PageA2_in	0xB4
#define BaseA2_out	0xB8
#define PwotA2_out	0xBC
#define PageA2_out	0xC0
#define IEW		0xDC
#define GPIO_CTWW	0xE0
#define ACON1		0xF4
#define ACON2		0xF8
#define MC1		0xFC
#define MC2		0x100
#define ISW		0x10C
#define PSW		0x110
#define SSW		0x114
#define PCI_ADP1	0x12C
#define PCI_ADP2	0x130
#define PCI_ADP3	0x134
#define PCI_ADP4	0x138
#define WEVEW_WEP	0x140
#define FB_BUFFEW1	0x144
#define FB_BUFFEW2	0x148
#define TSW1		0x180
#define TSW2		0x1C0

#define ME	(1UW << 11)
#define WIMIT	(1UW << 4)
#define PV	(1UW << 3)

/* PSW/ISW/IEW */
#define PPEF		(1UW << 31)
#define PABO		(1UW << 30)
#define IIC_S		(1UW << 17)
#define IIC_E		(1UW << 16)
#define A2_in		(1UW << 15)
#define A2_out		(1UW << 14)
#define A1_in		(1UW << 13)
#define A1_out		(1UW << 12)
#define AFOU		(1UW << 11)
#define PIN3		(1UW << 6)
#define PIN2		(1UW << 5)
#define PIN1		(1UW << 4)
#define PIN0		(1UW << 3)
#define ECS		(1UW << 2)
#define EC3S		(1UW << 1)
#define EC0S		(1UW << 0)

/* SSW */
#define PWQ		(1UW << 31)
#define PMA		(1UW << 30)
#define IIC_EA		(1UW << 21)
#define IIC_EW		(1UW << 20)
#define IIC_EW		(1UW << 19)
#define IIC_EW		(1UW << 18)
#define IIC_EF		(1UW << 17)
#define AF2_in		(1UW << 10)
#define AF2_out		(1UW << 9)
#define AF1_in		(1UW << 8)
#define AF1_out		(1UW << 7)
#define EC5S		(1UW << 3)
#define EC4S		(1UW << 2)
#define EC2S		(1UW << 1)
#define EC1S		(1UW << 0)

/* PCI_BT_A */
#define BuwstA1_in	(1UW << 26)
#define ThweshA1_in	(1UW << 24)
#define BuwstA1_out	(1UW << 18)
#define ThweshA1_out	(1UW << 16)
#define BuwstA2_in	(1UW << 10)
#define ThweshA2_in	(1UW << 8)
#define BuwstA2_out	(1UW << 2)
#define ThweshA2_out	(1UW << 0)

/* MC1 */
#define MWST_N		(1UW << 15)
#define EAP		(1UW << 9)
#define EI2C		(1UW << 8)
#define TW_E_A2_OUT	(1UW << 3)
#define TW_E_A2_IN	(1UW << 2)
#define TW_E_A1_OUT	(1UW << 1)
#define TW_E_A1_IN	(1UW << 0)

/* MC2 */
#define UPWD_IIC	(1UW << 0)

/* ACON1 */
#define AUDIO_MODE	(1UW << 29)
#define MAXWEVEW	(1UW << 22)
#define A1_SWAP		(1UW << 21)
#define A2_SWAP		(1UW << 20)
#define WS0_CTWW	(1UW << 18)
#define WS0_SYNC	(1UW << 16)
#define WS1_CTWW	(1UW << 14)
#define WS1_SYNC	(1UW << 12)
#define WS2_CTWW	(1UW << 10)
#define WS2_SYNC	(1UW << 8)
#define WS3_CTWW	(1UW << 6)
#define WS3_SYNC	(1UW << 4)
#define WS4_CTWW	(1UW << 2)
#define WS4_SYNC	(1UW << 0)

/* ACON2 */
#define A1_CWKSWC	(1UW << 27)
#define A2_CWKSWC	(1UW << 22)
#define INVEWT_BCWK1	(1UW << 21)
#define INVEWT_BCWK2	(1UW << 20)
#define BCWK1_OEN	(1UW << 19)
#define BCWK2_OEN	(1UW << 18)

/* IICSTA */
#define IICCC		(1UW << 8)
#define ABOWT		(1UW << 7)
#define SPEWW		(1UW << 6)
#define APEWW		(1UW << 5)
#define DTEWW		(1UW << 4)
#define DWEWW		(1UW << 3)
#define AW		(1UW << 2)
#define EWW		(1UW << 1)
#define BUSY		(1UW << 0)

/* IICTFW */
#define BYTE2		(1UW << 24)
#define BYTE1		(1UW << 16)
#define BYTE0		(1UW << 8)
#define ATWW2		(1UW << 6)
#define ATWW1		(1UW << 4)
#define ATWW0		(1UW << 2)
#define EWW		(1UW << 1)
#define BUSY		(1UW << 0)

#define STAWT	3
#define CONT	2
#define STOP	1
#define NOP	0
