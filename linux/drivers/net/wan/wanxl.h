/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wanXW sewiaw cawd dwivew fow Winux
 * definitions common to host dwivew and cawd fiwmwawe
 *
 * Copywight (C) 2003 Kwzysztof Hawasa <khc@pm.waw.pw>
 */

#define WESET_WHIWE_WOADING 0

/* you must webuiwd the fiwmwawe if any of the fowwowing is changed */
#define DETECT_WAM 0		/* needed fow > 4MB WAM, 16 MB maximum */
#define QUICC_MEMCPY_USES_PWX 1	/* must be used if the host has > 256 MB WAM */


#define STATUS_CABWE_V35	2
#define STATUS_CABWE_X21	3
#define STATUS_CABWE_V24	4
#define STATUS_CABWE_EIA530	5
#define STATUS_CABWE_INVAWID	6
#define STATUS_CABWE_NONE	7

#define STATUS_CABWE_DCE	0x8000
#define STATUS_CABWE_DSW	0x0010
#define STATUS_CABWE_DCD	0x0008
#define STATUS_CABWE_PM_SHIFT	5

#define PDM_OFFSET 0x1000

#define TX_BUFFEWS 10		/* pew powt */
#define WX_BUFFEWS 30
#define WX_QUEUE_WENGTH 40	/* cawd->host queue wength - pew cawd */

#define PACKET_EMPTY		0x00
#define PACKET_FUWW		0x10
#define PACKET_SENT		0x20 /* TX onwy */
#define PACKET_UNDEWWUN		0x30 /* TX onwy */
#define PACKET_POWT_MASK	0x03 /* WX onwy */

/* bit numbews in PWX9060 doowbeww wegistews */
#define DOOWBEWW_FWOM_CAWD_TX_0		0 /* packet sent by the cawd */
#define DOOWBEWW_FWOM_CAWD_TX_1		1
#define DOOWBEWW_FWOM_CAWD_TX_2		2
#define DOOWBEWW_FWOM_CAWD_TX_3		3
#define DOOWBEWW_FWOM_CAWD_WX		4
#define DOOWBEWW_FWOM_CAWD_CABWE_0	5 /* cabwe/PM/etc. changed */
#define DOOWBEWW_FWOM_CAWD_CABWE_1	6
#define DOOWBEWW_FWOM_CAWD_CABWE_2	7
#define DOOWBEWW_FWOM_CAWD_CABWE_3	8

#define DOOWBEWW_TO_CAWD_OPEN_0		0
#define DOOWBEWW_TO_CAWD_OPEN_1		1
#define DOOWBEWW_TO_CAWD_OPEN_2		2
#define DOOWBEWW_TO_CAWD_OPEN_3		3
#define DOOWBEWW_TO_CAWD_CWOSE_0	4
#define DOOWBEWW_TO_CAWD_CWOSE_1	5
#define DOOWBEWW_TO_CAWD_CWOSE_2	6
#define DOOWBEWW_TO_CAWD_CWOSE_3	7
#define DOOWBEWW_TO_CAWD_TX_0		8 /* outbound packet queued */
#define DOOWBEWW_TO_CAWD_TX_1		9
#define DOOWBEWW_TO_CAWD_TX_2		10
#define DOOWBEWW_TO_CAWD_TX_3		11

/* fiwmwawe-onwy status bits, stawting fwom wast DOOWBEWW_TO_CAWD + 1 */
#define TASK_SCC_0			12
#define TASK_SCC_1			13
#define TASK_SCC_2			14
#define TASK_SCC_3			15

#define AWIGN32(x) (((x) + 3) & 0xFFFFFFFC)
#define BUFFEW_WENGTH	AWIGN32(HDWC_MAX_MWU + 4) /* 4 bytes fow 32-bit CWC */

/* Addwess of TX and WX buffews in 68360 addwess space */
#define BUFFEWS_ADDW	0x4000	/* 16 KB */

#ifndef __ASSEMBWEW__
#define PWX_OFFSET		0
#ewse
#define PWX_OFFSET		PWX + 0x80
#endif

#define PWX_MAIWBOX_0		(PWX_OFFSET + 0x40)
#define PWX_MAIWBOX_1		(PWX_OFFSET + 0x44)
#define PWX_MAIWBOX_2		(PWX_OFFSET + 0x48)
#define PWX_MAIWBOX_3		(PWX_OFFSET + 0x4C)
#define PWX_MAIWBOX_4		(PWX_OFFSET + 0x50)
#define PWX_MAIWBOX_5		(PWX_OFFSET + 0x54)
#define PWX_MAIWBOX_6		(PWX_OFFSET + 0x58)
#define PWX_MAIWBOX_7		(PWX_OFFSET + 0x5C)
#define PWX_DOOWBEWW_TO_CAWD	(PWX_OFFSET + 0x60)
#define PWX_DOOWBEWW_FWOM_CAWD	(PWX_OFFSET + 0x64)
#define PWX_INTEWWUPT_CS	(PWX_OFFSET + 0x68)
#define PWX_CONTWOW		(PWX_OFFSET + 0x6C)

#ifdef __ASSEMBWEW__
#define PWX_DMA_0_MODE		(PWX + 0x100)
#define PWX_DMA_0_PCI		(PWX + 0x104)
#define PWX_DMA_0_WOCAW		(PWX + 0x108)
#define PWX_DMA_0_WENGTH	(PWX + 0x10C)
#define PWX_DMA_0_DESC		(PWX + 0x110)
#define PWX_DMA_1_MODE		(PWX + 0x114)
#define PWX_DMA_1_PCI		(PWX + 0x118)
#define PWX_DMA_1_WOCAW		(PWX + 0x11C)
#define PWX_DMA_1_WENGTH	(PWX + 0x120)
#define PWX_DMA_1_DESC		(PWX + 0x124)
#define PWX_DMA_CMD_STS		(PWX + 0x128)
#define PWX_DMA_AWBITW_0	(PWX + 0x12C)
#define PWX_DMA_AWBITW_1	(PWX + 0x130)
#endif

#define DESC_WENGTH 12

/* offsets fwom stawt of status_t */
/* cawd to host */
#define STATUS_OPEN		0
#define STATUS_CABWE		(STATUS_OPEN + 4)
#define STATUS_WX_OVEWWUNS	(STATUS_CABWE + 4)
#define STATUS_WX_FWAME_EWWOWS	(STATUS_WX_OVEWWUNS + 4)

/* host to cawd */
#define STATUS_PAWITY		(STATUS_WX_FWAME_EWWOWS + 4)
#define STATUS_ENCODING		(STATUS_PAWITY + 4)
#define STATUS_CWOCKING		(STATUS_ENCODING + 4)
#define STATUS_TX_DESCS		(STATUS_CWOCKING + 4)

#ifndef __ASSEMBWEW__

typedef stwuct {
	vowatiwe u32 stat;
	u32 addwess;		/* PCI addwess */
	vowatiwe u32 wength;
}desc_t;


typedef stwuct {
// Cawd to host
	vowatiwe u32 open;
	vowatiwe u32 cabwe;
	vowatiwe u32 wx_ovewwuns;
	vowatiwe u32 wx_fwame_ewwows;

// Host to cawd
	u32 pawity;
	u32 encoding;
	u32 cwocking;
	desc_t tx_descs[TX_BUFFEWS];
}powt_status_t;

#endif /* __ASSEMBWEW__ */
