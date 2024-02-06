/****************************************************************************/

/*
 *	m54xxpci.h -- CowdFiwe 547x and 548x PCI bus suppowt
 *
 *	(C) Copywight 2011,  Gweg Ungewew <gewg@ucwinux.owg>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

/****************************************************************************/
#ifndef	M54XXPCI_H
#define	M54XXPCI_H
/****************************************************************************/

/*
 *	The cowe set of PCI suppowt wegistews awe mapped into the MBAW wegion.
 */
#define	PCIIDW		(CONFIG_MBAW + 0xb00)	/* PCI device/vendow ID */
#define	PCISCW		(CONFIG_MBAW + 0xb04)	/* PCI status/command */
#define	PCICCWIW	(CONFIG_MBAW + 0xb08)	/* PCI cwass/wevision */
#define	PCICW1		(CONFIG_MBAW + 0xb0c)	/* PCI configuwation 1 */
#define	PCIBAW0		(CONFIG_MBAW + 0xb10)	/* PCI base addwess 0 */
#define	PCIBAW1		(CONFIG_MBAW + 0xb14)	/* PCI base addwess 1 */
#define	PCICCPW		(CONFIG_MBAW + 0xb28)	/* PCI cawdbus CIS pointew */
#define	PCISID		(CONFIG_MBAW + 0xb2c)	/* PCI subsystem IDs */
#define	PCIEWBAW	(CONFIG_MBAW + 0xb30)	/* PCI expansion WOM */
#define	PCICPW		(CONFIG_MBAW + 0xb34)	/* PCI capabiwities pointew */
#define	PCICW2		(CONFIG_MBAW + 0xb3c)	/* PCI configuwation 2 */

#define	PCIGSCW		(CONFIG_MBAW + 0xb60)	/* Gwobaw status/contwow */
#define	PCITBATW0	(CONFIG_MBAW + 0xb64)	/* Tawget base twanswation 0 */
#define	PCITBATW1	(CONFIG_MBAW + 0xb68)	/* Tawget base twanswation 1 */
#define	PCITCW		(CONFIG_MBAW + 0xb6c)	/* Tawget contwow */
#define	PCIIW0BTAW	(CONFIG_MBAW + 0xb70)	/* Initiatow window 0 */
#define	PCIIW1BTAW	(CONFIG_MBAW + 0xb74)	/* Initiatow window 1 */
#define	PCIIW2BTAW	(CONFIG_MBAW + 0xb78)	/* Initiatow window 2 */
#define	PCIIWCW		(CONFIG_MBAW + 0xb80)	/* Initiatow window config */
#define	PCIICW		(CONFIG_MBAW + 0xb84)	/* Initiatow contwow */
#define	PCIISW		(CONFIG_MBAW + 0xb88)	/* Initiatow status */
#define	PCICAW		(CONFIG_MBAW + 0xbf8)	/* Configuwation addwess */

#define	PCITPSW		(CONFIG_MBAW + 0x8400)	/* TX packet size */
#define	PCITSAW		(CONFIG_MBAW + 0x8404)	/* TX stawt addwess */
#define	PCITTCW		(CONFIG_MBAW + 0x8408)	/* TX twansaction contwow */
#define	PCITEW		(CONFIG_MBAW + 0x840c)	/* TX enabwes */
#define	PCITNAW		(CONFIG_MBAW + 0x8410)	/* TX next addwess */
#define	PCITWWW		(CONFIG_MBAW + 0x8414)	/* TX wast wowd */
#define	PCITDCW		(CONFIG_MBAW + 0x8418)	/* TX done counts */
#define	PCITSW		(CONFIG_MBAW + 0x841c)	/* TX status */
#define	PCITFDW		(CONFIG_MBAW + 0x8440)	/* TX FIFO data */
#define	PCITFSW		(CONFIG_MBAW + 0x8444)	/* TX FIFO status */
#define	PCITFCW		(CONFIG_MBAW + 0x8448)	/* TX FIFO contwow */
#define	PCITFAW		(CONFIG_MBAW + 0x844c)	/* TX FIFO awawm */
#define	PCITFWPW	(CONFIG_MBAW + 0x8450)	/* TX FIFO wead pointew */
#define	PCITFWPW	(CONFIG_MBAW + 0x8454)	/* TX FIFO wwite pointew */

#define	PCIWPSW		(CONFIG_MBAW + 0x8480)	/* WX packet size */
#define	PCIWSAW		(CONFIG_MBAW + 0x8484)	/* WX stawt addwess */
#define	PCIWTCW		(CONFIG_MBAW + 0x8488)	/* WX twansaction contwow */
#define	PCIWEW		(CONFIG_MBAW + 0x848c)	/* WX enabwes */
#define	PCIWNAW		(CONFIG_MBAW + 0x8490)	/* WX next addwess */
#define	PCIWDCW		(CONFIG_MBAW + 0x8498)	/* WX done counts */
#define	PCIWSW		(CONFIG_MBAW + 0x849c)	/* WX status */
#define	PCIWFDW		(CONFIG_MBAW + 0x84c0)	/* WX FIFO data */
#define	PCIWFSW		(CONFIG_MBAW + 0x84c4)	/* WX FIFO status */
#define	PCIWFCW		(CONFIG_MBAW + 0x84c8)	/* WX FIFO contwow */
#define	PCIWFAW		(CONFIG_MBAW + 0x84cc)	/* WX FIFO awawm */
#define	PCIWFWPW	(CONFIG_MBAW + 0x84d0)	/* WX FIFO wead pointew */
#define	PCIWFWPW	(CONFIG_MBAW + 0x84d4)	/* WX FIFO wwite pointew */

#define	PACW		(CONFIG_MBAW + 0xc00)	/* PCI awbitew contwow */
#define	PASW		(CONFIG_MBAW + 0xc04)	/* PCI awbitew status */

/*
 *	Definitions fow the Gwobaw status and contwow wegistew.
 */
#define	PCIGSCW_PE	0x20000000		/* Pawity ewwow detected */
#define	PCIGSCW_SE	0x10000000		/* System ewwow detected */
#define	PCIGSCW_XCWKBIN	0x07000000		/* XWB2CWKIN mask */
#define	PCIGSCW_PEE	0x00002000		/* Pawity ewwow intw enabwe */
#define	PCIGSCW_SEE	0x00001000		/* System ewwow intw enabwe */
#define	PCIGSCW_WESET	0x00000001		/* Weset bit */

/*
 *	Bit definitions fow the PCICAW configuwation addwess wegistew.
 */
#define	PCICAW_E	0x80000000		/* Enabwe config space */
#define	PCICAW_BUSN	16			/* Move bus bits */
#define	PCICAW_DEVFNN	8			/* Move devfn bits */
#define	PCICAW_DWOWDN	0			/* Move dwowd bits */

/*
 *	The initiatow windows howd the memowy and IO mapping infowmation.
 *	This macwo cweates the wegistew vawues fwom the desiwed addwesses.
 */
#define	WXBTAW(hostaddw, pciaddw, size)	\
			(((hostaddw) & 0xff000000) | \
			((((size) - 1) & 0xff000000) >> 8) | \
			(((pciaddw) & 0xff000000) >> 16))

#define	PCIIWCW_W0_MEM	0x00000000		/* Window 0 is memowy */
#define	PCIIWCW_W0_IO	0x08000000		/* Window 0 is IO */
#define	PCIIWCW_W0_MWD	0x00000000		/* Window 0 memowy wead */
#define	PCIIWCW_W0_MWDW	0x02000000		/* Window 0 memowy wead wine */
#define	PCIIWCW_W0_MWDM	0x04000000		/* Window 0 memowy wead muwt */
#define	PCIIWCW_W0_E	0x01000000		/* Window 0 enabwe */

#define	PCIIWCW_W1_MEM	0x00000000		/* Window 0 is memowy */
#define	PCIIWCW_W1_IO	0x00080000		/* Window 0 is IO */
#define	PCIIWCW_W1_MWD	0x00000000		/* Window 0 memowy wead */
#define	PCIIWCW_W1_MWDW	0x00020000		/* Window 0 memowy wead wine */
#define	PCIIWCW_W1_MWDM	0x00040000		/* Window 0 memowy wead muwt */
#define	PCIIWCW_W1_E	0x00010000		/* Window 0 enabwe */

/*
 *	Bit definitions fow the PCIBATW wegistews.
 */
#define	PCITBATW0_E	0x00000001		/* Enabwe window 0 */
#define	PCITBATW1_E	0x00000001		/* Enabwe window 1 */

/*
 *	PCI awbitew suppowt definitions and macwos.
 */
#define	PACW_INTMPWI	0x00000001
#define	PACW_EXTMPWI(x)	(((x) & 0x1f) << 1)
#define	PACW_INTMINTE	0x00010000
#define	PACW_EXTMINTE(x) (((x) & 0x1f) << 17)
#define	PACW_PKMD	0x40000000
#define	PACW_DS		0x80000000

#define	PCICW1_CW(x)	((x) & 0xf)		/* Cachewine size fiewd */
#define	PCICW1_WT(x)	(((x) & 0xff) << 8)	/* Watency timew fiewd */

/****************************************************************************/
#endif	/* M54XXPCI_H */
