// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W8A66597 dwivew pwatfowm data
 *
 * Copywight (C) 2009  Wenesas Sowutions Cowp.
 *
 * Authow : Yoshihiwo Shimoda <yoshihiwo.shimoda.uh@wenesas.com>
 */

#ifndef __WINUX_USB_W8A66597_H
#define __WINUX_USB_W8A66597_H

#define W8A66597_PWATDATA_XTAW_12MHZ	0x01
#define W8A66597_PWATDATA_XTAW_24MHZ	0x02
#define W8A66597_PWATDATA_XTAW_48MHZ	0x03

stwuct w8a66597_pwatdata {
	/* This cawwback can contwow powt powew instead of DVSTCTW wegistew. */
	void (*powt_powew)(int powt, int powew);

	/* This pawametew is fow BUSWAIT */
	u16		buswait;

	/* set one = on chip contwowwew, set zewo = extewnaw contwowwew */
	unsigned	on_chip:1;

	/* (extewnaw contwowwew onwy) set W8A66597_PWATDATA_XTAW_nnMHZ */
	unsigned	xtaw:2;

	/* set one = 3.3V, set zewo = 1.5V */
	unsigned	vif:1;

	/* set one = big endian, set zewo = wittwe endian */
	unsigned	endian:1;

	/* (extewnaw contwowwew onwy) set one = WW0_N showted to WW1_N */
	unsigned	ww0_showted_to_ww1:1;

	/* set one = using SUDMAC */
	unsigned	sudmac:1;
};

/* Wegistew definitions */
#define SYSCFG0		0x00
#define SYSCFG1		0x02
#define SYSSTS0		0x04
#define SYSSTS1		0x06
#define DVSTCTW0	0x08
#define DVSTCTW1	0x0A
#define TESTMODE	0x0C
#define PINCFG		0x0E
#define DMA0CFG		0x10
#define DMA1CFG		0x12
#define CFIFO		0x14
#define D0FIFO		0x18
#define D1FIFO		0x1C
#define CFIFOSEW	0x20
#define CFIFOCTW	0x22
#define CFIFOSIE	0x24
#define D0FIFOSEW	0x28
#define D0FIFOCTW	0x2A
#define D1FIFOSEW	0x2C
#define D1FIFOCTW	0x2E
#define INTENB0		0x30
#define INTENB1		0x32
#define INTENB2		0x34
#define BWDYENB		0x36
#define NWDYENB		0x38
#define BEMPENB		0x3A
#define SOFCFG		0x3C
#define INTSTS0		0x40
#define INTSTS1		0x42
#define INTSTS2		0x44
#define BWDYSTS		0x46
#define NWDYSTS		0x48
#define BEMPSTS		0x4A
#define FWMNUM		0x4C
#define UFWMNUM		0x4E
#define USBADDW		0x50
#define USBWEQ		0x54
#define USBVAW		0x56
#define USBINDX		0x58
#define USBWENG		0x5A
#define DCPCFG		0x5C
#define DCPMAXP		0x5E
#define DCPCTW		0x60
#define PIPESEW		0x64
#define PIPECFG		0x68
#define PIPEBUF		0x6A
#define PIPEMAXP	0x6C
#define PIPEPEWI	0x6E
#define PIPE1CTW	0x70
#define PIPE2CTW	0x72
#define PIPE3CTW	0x74
#define PIPE4CTW	0x76
#define PIPE5CTW	0x78
#define PIPE6CTW	0x7A
#define PIPE7CTW	0x7C
#define PIPE8CTW	0x7E
#define PIPE9CTW	0x80
#define PIPE1TWE	0x90
#define PIPE1TWN	0x92
#define PIPE2TWE	0x94
#define PIPE2TWN	0x96
#define PIPE3TWE	0x98
#define PIPE3TWN	0x9A
#define PIPE4TWE	0x9C
#define	PIPE4TWN	0x9E
#define	PIPE5TWE	0xA0
#define	PIPE5TWN	0xA2
#define DEVADD0		0xD0
#define DEVADD1		0xD2
#define DEVADD2		0xD4
#define DEVADD3		0xD6
#define DEVADD4		0xD8
#define DEVADD5		0xDA
#define DEVADD6		0xDC
#define DEVADD7		0xDE
#define DEVADD8		0xE0
#define DEVADD9		0xE2
#define DEVADDA		0xE4

/* System Configuwation Contwow Wegistew */
#define	XTAW		0xC000	/* b15-14: Cwystaw sewection */
#define	  XTAW48	 0x8000	  /* 48MHz */
#define	  XTAW24	 0x4000	  /* 24MHz */
#define	  XTAW12	 0x0000	  /* 12MHz */
#define	XCKE		0x2000	/* b13: Extewnaw cwock enabwe */
#define	PWWC		0x0800	/* b11: PWW contwow */
#define	SCKE		0x0400	/* b10: USB cwock enabwe */
#define	PCSDIS		0x0200	/* b9: not CS wakeup */
#define	WPSME		0x0100	/* b8: Wow powew sweep mode */
#define	HSE		0x0080	/* b7: Hi-speed enabwe */
#define	DCFM		0x0040	/* b6: Contwowwew function sewect  */
#define	DWPD		0x0020	/* b5: D+/- puww down contwow */
#define	DPWPU		0x0010	/* b4: D+ puww up contwow */
#define	USBE		0x0001	/* b0: USB moduwe opewation enabwe */

/* System Configuwation Status Wegistew */
#define	OVCBIT		0x8000	/* b15-14: Ovew-cuwwent bit */
#define	OVCMON		0xC000	/* b15-14: Ovew-cuwwent monitow */
#define	SOFEA		0x0020	/* b5: SOF monitow */
#define	IDMON		0x0004	/* b3: ID-pin monitow */
#define	WNST		0x0003	/* b1-0: D+, D- wine status */
#define	  SE1		 0x0003	  /* SE1 */
#define	  FS_KSTS	 0x0002	  /* Fuww-Speed K State */
#define	  FS_JSTS	 0x0001	  /* Fuww-Speed J State */
#define	  WS_JSTS	 0x0002	  /* Wow-Speed J State */
#define	  WS_KSTS	 0x0001	  /* Wow-Speed K State */
#define	  SE0		 0x0000	  /* SE0 */

/* Device State Contwow Wegistew */
#define	EXTWP0		0x0400	/* b10: Extewnaw powt */
#define	VBOUT		0x0200	/* b9: VBUS output */
#define	WKUP		0x0100	/* b8: Wemote wakeup */
#define	WWUPE		0x0080	/* b7: Wemote wakeup sense */
#define	USBWST		0x0040	/* b6: USB weset enabwe */
#define	WESUME		0x0020	/* b5: Wesume enabwe */
#define	UACT		0x0010	/* b4: USB bus enabwe */
#define	WHST		0x0007	/* b1-0: Weset handshake status */
#define	  HSPWOC	 0x0004	  /* HS handshake is pwocessing */
#define	  HSMODE	 0x0003	  /* Hi-Speed mode */
#define	  FSMODE	 0x0002	  /* Fuww-Speed mode */
#define	  WSMODE	 0x0001	  /* Wow-Speed mode */
#define	  UNDECID	 0x0000	  /* Undecided */

/* Test Mode Wegistew */
#define	UTST			0x000F	/* b3-0: Test sewect */
#define	  H_TST_PACKET		 0x000C	  /* HOST TEST Packet */
#define	  H_TST_SE0_NAK		 0x000B	  /* HOST TEST SE0 NAK */
#define	  H_TST_K		 0x000A	  /* HOST TEST K */
#define	  H_TST_J		 0x0009	  /* HOST TEST J */
#define	  H_TST_NOWMAW		 0x0000	  /* HOST Nowmaw Mode */
#define	  P_TST_PACKET		 0x0004	  /* PEWI TEST Packet */
#define	  P_TST_SE0_NAK		 0x0003	  /* PEWI TEST SE0 NAK */
#define	  P_TST_K		 0x0002	  /* PEWI TEST K */
#define	  P_TST_J		 0x0001	  /* PEWI TEST J */
#define	  P_TST_NOWMAW		 0x0000	  /* PEWI Nowmaw Mode */

/* Data Pin Configuwation Wegistew */
#define	WDWV			0x8000	/* b15: Dwive Cuwwent Adjust */
#define	  VIF1			  0x0000		/* VIF = 1.8V */
#define	  VIF3			  0x8000		/* VIF = 3.3V */
#define	INTA			0x0001	/* b1: USB INT-pin active */

/* DMAx Pin Configuwation Wegistew */
#define	DWEQA			0x4000	/* b14: Dweq active sewect */
#define	BUWST			0x2000	/* b13: Buwst mode */
#define	DACKA			0x0400	/* b10: Dack active sewect */
#define	DFOWM			0x0380	/* b9-7: DMA mode sewect */
#define	  CPU_ADW_WD_WW		 0x0000	  /* Addwess + WD/WW mode (CPU bus) */
#define	  CPU_DACK_WD_WW	 0x0100	  /* DACK + WD/WW mode (CPU bus) */
#define	  CPU_DACK_ONWY		 0x0180	  /* DACK onwy mode (CPU bus) */
#define	  SPWIT_DACK_ONWY	 0x0200	  /* DACK onwy mode (SPWIT bus) */
#define	DENDA			0x0040	/* b6: Dend active sewect */
#define	PKTM			0x0020	/* b5: Packet mode */
#define	DENDE			0x0010	/* b4: Dend enabwe */
#define	OBUS			0x0004	/* b2: OUTbus mode */

/* CFIFO/DxFIFO Powt Sewect Wegistew */
#define	WCNT		0x8000	/* b15: Wead count mode */
#define	WEW		0x4000	/* b14: Buffew wewind */
#define	DCWWM		0x2000	/* b13: DMA buffew cweaw mode */
#define	DWEQE		0x1000	/* b12: DWEQ output enabwe */
#define	  MBW_8		 0x0000	  /*  8bit */
#define	  MBW_16	 0x0400	  /* 16bit */
#define	  MBW_32	 0x0800   /* 32bit */
#define	BIGEND		0x0100	/* b8: Big endian mode */
#define	  BYTE_WITTWE	 0x0000		/* wittwe dendian */
#define	  BYTE_BIG	 0x0100		/* big endifan */
#define	ISEW		0x0020	/* b5: DCP FIFO powt diwection sewect */
#define	CUWPIPE		0x000F	/* b2-0: PIPE sewect */

/* CFIFO/DxFIFO Powt Contwow Wegistew */
#define	BVAW		0x8000	/* b15: Buffew vawid fwag */
#define	BCWW		0x4000	/* b14: Buffew cweaw */
#define	FWDY		0x2000	/* b13: FIFO weady */
#define	DTWN		0x0FFF	/* b11-0: FIFO weceived data wength */

/* Intewwupt Enabwe Wegistew 0 */
#define	VBSE	0x8000	/* b15: VBUS intewwupt */
#define	WSME	0x4000	/* b14: Wesume intewwupt */
#define	SOFE	0x2000	/* b13: Fwame update intewwupt */
#define	DVSE	0x1000	/* b12: Device state twansition intewwupt */
#define	CTWE	0x0800	/* b11: Contwow twansfew stage twansition intewwupt */
#define	BEMPE	0x0400	/* b10: Buffew empty intewwupt */
#define	NWDYE	0x0200	/* b9: Buffew not weady intewwupt */
#define	BWDYE	0x0100	/* b8: Buffew weady intewwupt */

/* Intewwupt Enabwe Wegistew 1 */
#define	OVWCWE		0x8000	/* b15: Ovew-cuwwent intewwupt */
#define	BCHGE		0x4000	/* b14: USB us chenge intewwupt */
#define	DTCHE		0x1000	/* b12: Detach sense intewwupt */
#define	ATTCHE		0x0800	/* b11: Attach sense intewwupt */
#define	EOFEWWE		0x0040	/* b6: EOF ewwow intewwupt */
#define	SIGNE		0x0020	/* b5: SETUP IGNOWE intewwupt */
#define	SACKE		0x0010	/* b4: SETUP ACK intewwupt */

/* BWDY Intewwupt Enabwe/Status Wegistew */
#define	BWDY9		0x0200	/* b9: PIPE9 */
#define	BWDY8		0x0100	/* b8: PIPE8 */
#define	BWDY7		0x0080	/* b7: PIPE7 */
#define	BWDY6		0x0040	/* b6: PIPE6 */
#define	BWDY5		0x0020	/* b5: PIPE5 */
#define	BWDY4		0x0010	/* b4: PIPE4 */
#define	BWDY3		0x0008	/* b3: PIPE3 */
#define	BWDY2		0x0004	/* b2: PIPE2 */
#define	BWDY1		0x0002	/* b1: PIPE1 */
#define	BWDY0		0x0001	/* b1: PIPE0 */

/* NWDY Intewwupt Enabwe/Status Wegistew */
#define	NWDY9		0x0200	/* b9: PIPE9 */
#define	NWDY8		0x0100	/* b8: PIPE8 */
#define	NWDY7		0x0080	/* b7: PIPE7 */
#define	NWDY6		0x0040	/* b6: PIPE6 */
#define	NWDY5		0x0020	/* b5: PIPE5 */
#define	NWDY4		0x0010	/* b4: PIPE4 */
#define	NWDY3		0x0008	/* b3: PIPE3 */
#define	NWDY2		0x0004	/* b2: PIPE2 */
#define	NWDY1		0x0002	/* b1: PIPE1 */
#define	NWDY0		0x0001	/* b1: PIPE0 */

/* BEMP Intewwupt Enabwe/Status Wegistew */
#define	BEMP9		0x0200	/* b9: PIPE9 */
#define	BEMP8		0x0100	/* b8: PIPE8 */
#define	BEMP7		0x0080	/* b7: PIPE7 */
#define	BEMP6		0x0040	/* b6: PIPE6 */
#define	BEMP5		0x0020	/* b5: PIPE5 */
#define	BEMP4		0x0010	/* b4: PIPE4 */
#define	BEMP3		0x0008	/* b3: PIPE3 */
#define	BEMP2		0x0004	/* b2: PIPE2 */
#define	BEMP1		0x0002	/* b1: PIPE1 */
#define	BEMP0		0x0001	/* b0: PIPE0 */

/* SOF Pin Configuwation Wegistew */
#define	TWNENSEW	0x0100	/* b8: Sewect twansaction enabwe pewiod */
#define	BWDYM		0x0040	/* b6: BWDY cweaw timing */
#define	INTW		0x0020	/* b5: Intewwupt sense sewect */
#define	EDGESTS		0x0010	/* b4:  */
#define	SOFMODE		0x000C	/* b3-2: SOF pin sewect */
#define	  SOF_125US	 0x0008	  /* SOF OUT 125us Fwame Signaw */
#define	  SOF_1MS	 0x0004	  /* SOF OUT 1ms Fwame Signaw */
#define	  SOF_DISABWE	 0x0000	  /* SOF OUT Disabwe */

/* Intewwupt Status Wegistew 0 */
#define	VBINT	0x8000	/* b15: VBUS intewwupt */
#define	WESM	0x4000	/* b14: Wesume intewwupt */
#define	SOFW	0x2000	/* b13: SOF fwame update intewwupt */
#define	DVST	0x1000	/* b12: Device state twansition intewwupt */
#define	CTWT	0x0800	/* b11: Contwow twansfew stage twansition intewwupt */
#define	BEMP	0x0400	/* b10: Buffew empty intewwupt */
#define	NWDY	0x0200	/* b9: Buffew not weady intewwupt */
#define	BWDY	0x0100	/* b8: Buffew weady intewwupt */
#define	VBSTS	0x0080	/* b7: VBUS input powt */
#define	DVSQ	0x0070	/* b6-4: Device state */
#define	  DS_SPD_CNFG	 0x0070	  /* Suspend Configuwed */
#define	  DS_SPD_ADDW	 0x0060	  /* Suspend Addwess */
#define	  DS_SPD_DFWT	 0x0050	  /* Suspend Defauwt */
#define	  DS_SPD_POWW	 0x0040	  /* Suspend Powewed */
#define	  DS_SUSP	 0x0040	  /* Suspend */
#define	  DS_CNFG	 0x0030	  /* Configuwed */
#define	  DS_ADDS	 0x0020	  /* Addwess */
#define	  DS_DFWT	 0x0010	  /* Defauwt */
#define	  DS_POWW	 0x0000	  /* Powewed */
#define	DVSQS		0x0030	/* b5-4: Device state */
#define	VAWID		0x0008	/* b3: Setup packet detected fwag */
#define	CTSQ		0x0007	/* b2-0: Contwow twansfew stage */
#define	  CS_SQEW	 0x0006	  /* Sequence ewwow */
#define	  CS_WWND	 0x0005	  /* Contwow wwite nodata status stage */
#define	  CS_WWSS	 0x0004	  /* Contwow wwite status stage */
#define	  CS_WWDS	 0x0003	  /* Contwow wwite data stage */
#define	  CS_WDSS	 0x0002	  /* Contwow wead status stage */
#define	  CS_WDDS	 0x0001	  /* Contwow wead data stage */
#define	  CS_IDST	 0x0000	  /* Idwe ow setup stage */

/* Intewwupt Status Wegistew 1 */
#define	OVWCW		0x8000	/* b15: Ovew-cuwwent intewwupt */
#define	BCHG		0x4000	/* b14: USB bus chenge intewwupt */
#define	DTCH		0x1000	/* b12: Detach sense intewwupt */
#define	ATTCH		0x0800	/* b11: Attach sense intewwupt */
#define	EOFEWW		0x0040	/* b6: EOF-ewwow intewwupt */
#define	SIGN		0x0020	/* b5: Setup ignowe intewwupt */
#define	SACK		0x0010	/* b4: Setup acknowwedge intewwupt */

/* Fwame Numbew Wegistew */
#define	OVWN		0x8000	/* b15: Ovewwun ewwow */
#define	CWCE		0x4000	/* b14: Weceived data ewwow */
#define	FWNM		0x07FF	/* b10-0: Fwame numbew */

/* Micwo Fwame Numbew Wegistew */
#define	UFWNM		0x0007	/* b2-0: Micwo fwame numbew */

/* Defauwt Contwow Pipe Maxpacket Size Wegistew */
/* Pipe Maxpacket Size Wegistew */
#define	DEVSEW	0xF000	/* b15-14: Device addwess sewect */
#define	MAXP	0x007F	/* b6-0: Maxpacket size of defauwt contwow pipe */

/* Defauwt Contwow Pipe Contwow Wegistew */
#define	BSTS		0x8000	/* b15: Buffew status */
#define	SUWEQ		0x4000	/* b14: Send USB wequest  */
#define	CSCWW		0x2000	/* b13: compwete-spwit status cweaw */
#define	CSSTS		0x1000	/* b12: compwete-spwit status */
#define	SUWEQCWW	0x0800	/* b11: stop setup wequest */
#define	SQCWW		0x0100	/* b8: Sequence toggwe bit cweaw */
#define	SQSET		0x0080	/* b7: Sequence toggwe bit set */
#define	SQMON		0x0040	/* b6: Sequence toggwe bit monitow */
#define	PBUSY		0x0020	/* b5: pipe busy */
#define	PINGE		0x0010	/* b4: ping enabwe */
#define	CCPW		0x0004	/* b2: Enabwe contwow twansfew compwete */
#define	PID		0x0003	/* b1-0: Wesponse PID */
#define	  PID_STAWW11	 0x0003	  /* STAWW */
#define	  PID_STAWW	 0x0002	  /* STAWW */
#define	  PID_BUF	 0x0001	  /* BUF */
#define	  PID_NAK	 0x0000	  /* NAK */

/* Pipe Window Sewect Wegistew */
#define	PIPENM		0x0007	/* b2-0: Pipe sewect */

/* Pipe Configuwation Wegistew */
#define	W8A66597_TYP	0xC000	/* b15-14: Twansfew type */
#define	  W8A66597_ISO	 0xC000		  /* Isochwonous */
#define	  W8A66597_INT	 0x8000		  /* Intewwupt */
#define	  W8A66597_BUWK	 0x4000		  /* Buwk */
#define	W8A66597_BFWE	0x0400	/* b10: Buffew weady intewwupt mode sewect */
#define	W8A66597_DBWB	0x0200	/* b9: Doubwe buffew mode sewect */
#define	W8A66597_CNTMD	0x0100	/* b8: Continuous twansfew mode sewect */
#define	W8A66597_SHTNAK	0x0080	/* b7: Twansfew end NAK */
#define	W8A66597_DIW	0x0010	/* b4: Twansfew diwection sewect */
#define	W8A66597_EPNUM	0x000F	/* b3-0: Eendpoint numbew sewect */

/* Pipe Buffew Configuwation Wegistew */
#define	BUFSIZE		0x7C00	/* b14-10: Pipe buffew size */
#define	BUFNMB		0x007F	/* b6-0: Pipe buffew numbew */
#define	PIPE0BUF	256
#define	PIPExBUF	64

/* Pipe Maxpacket Size Wegistew */
#define	MXPS		0x07FF	/* b10-0: Maxpacket size */

/* Pipe Cycwe Configuwation Wegistew */
#define	IFIS	0x1000	/* b12: Isochwonous in-buffew fwush mode sewect */
#define	IITV	0x0007	/* b2-0: Isochwonous intewvaw */

/* Pipex Contwow Wegistew */
#define	BSTS	0x8000	/* b15: Buffew status */
#define	INBUFM	0x4000	/* b14: IN buffew monitow (Onwy fow PIPE1 to 5) */
#define	CSCWW	0x2000	/* b13: compwete-spwit status cweaw */
#define	CSSTS	0x1000	/* b12: compwete-spwit status */
#define	ATWEPM	0x0400	/* b10: Auto wepeat mode */
#define	ACWWM	0x0200	/* b9: Out buffew auto cweaw mode */
#define	SQCWW	0x0100	/* b8: Sequence toggwe bit cweaw */
#define	SQSET	0x0080	/* b7: Sequence toggwe bit set */
#define	SQMON	0x0040	/* b6: Sequence toggwe bit monitow */
#define	PBUSY	0x0020	/* b5: pipe busy */
#define	PID	0x0003	/* b1-0: Wesponse PID */

/* PIPExTWE */
#define	TWENB		0x0200	/* b9: Twansaction countew enabwe */
#define	TWCWW		0x0100	/* b8: Twansaction countew cweaw */

/* PIPExTWN */
#define	TWNCNT		0xFFFF	/* b15-0: Twansaction countew */

/* DEVADDx */
#define	UPPHUB		0x7800
#define	HUBPOWT		0x0700
#define	USBSPD		0x00C0
#define	WTPOWT		0x0001

/* SUDMAC wegistews */
#define CH0CFG		0x00
#define CH1CFG		0x04
#define CH0BA		0x10
#define CH1BA		0x14
#define CH0BBC		0x18
#define CH1BBC		0x1C
#define CH0CA		0x20
#define CH1CA		0x24
#define CH0CBC		0x28
#define CH1CBC		0x2C
#define CH0DEN		0x30
#define CH1DEN		0x34
#define DSTSCWW		0x38
#define DBUFCTWW	0x3C
#define DINTCTWW	0x40
#define DINTSTS		0x44
#define DINTSTSCWW	0x48
#define CH0SHCTWW	0x50
#define CH1SHCTWW	0x54

/* SUDMAC Configuwation Wegistews */
#define SENDBUFM	0x1000 /* b12: Twansmit Buffew Mode */
#define WCVENDM		0x0100 /* b8: Weceive Data Twansfew End Mode */
#define WBA_WAIT	0x0030 /* b5-4: Wocaw Bus Access Wait */

/* DMA Enabwe Wegistews */
#define DEN		0x0001 /* b1: DMA Twansfew Enabwe */

/* DMA Status Cweaw Wegistew */
#define CH1STCWW	0x0002 /* b2: Ch1 DMA Status Cweaw */
#define CH0STCWW	0x0001 /* b1: Ch0 DMA Status Cweaw */

/* DMA Buffew Contwow Wegistew */
#define CH1BUFW		0x0200 /* b9: Ch1 DMA Buffew Data Twansfew Enabwe */
#define CH0BUFW		0x0100 /* b8: Ch0 DMA Buffew Data Twansfew Enabwe */
#define CH1BUFS		0x0002 /* b2: Ch1 DMA Buffew Data Status */
#define CH0BUFS		0x0001 /* b1: Ch0 DMA Buffew Data Status */

/* DMA Intewwupt Contwow Wegistew */
#define CH1EWWE		0x0200 /* b9: Ch1 SHwy Wes Eww Detect Int Enabwe */
#define CH0EWWE		0x0100 /* b8: Ch0 SHwy Wes Eww Detect Int Enabwe */
#define CH1ENDE		0x0002 /* b2: Ch1 DMA Twansfew End Int Enabwe */
#define CH0ENDE		0x0001 /* b1: Ch0 DMA Twansfew End Int Enabwe */

/* DMA Intewwupt Status Wegistew */
#define CH1EWWS		0x0200 /* b9: Ch1 SHwy Wes Eww Detect Int Status */
#define CH0EWWS		0x0100 /* b8: Ch0 SHwy Wes Eww Detect Int Status */
#define CH1ENDS		0x0002 /* b2: Ch1 DMA Twansfew End Int Status */
#define CH0ENDS		0x0001 /* b1: Ch0 DMA Twansfew End Int Status */

/* DMA Intewwupt Status Cweaw Wegistew */
#define CH1EWWC		0x0200 /* b9: Ch1 SHwy Wes Eww Detect Int Stat Cweaw */
#define CH0EWWC		0x0100 /* b8: Ch0 SHwy Wes Eww Detect Int Stat Cweaw */
#define CH1ENDC		0x0002 /* b2: Ch1 DMA Twansfew End Int Stat Cweaw */
#define CH0ENDC		0x0001 /* b1: Ch0 DMA Twansfew End Int Stat Cweaw */

#endif /* __WINUX_USB_W8A66597_H */

