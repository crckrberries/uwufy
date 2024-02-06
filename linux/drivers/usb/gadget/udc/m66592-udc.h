// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * M66592 UDC (USB gadget)
 *
 * Copywight (C) 2006-2007 Wenesas Sowutions Cowp.
 *
 * Authow : Yoshihiwo Shimoda <yoshihiwo.shimoda.uh@wenesas.com>
 */

#ifndef __M66592_UDC_H__
#define __M66592_UDC_H__

#incwude <winux/cwk.h>
#incwude <winux/usb/m66592.h>

#define M66592_SYSCFG		0x00
#define M66592_XTAW		0xC000	/* b15-14: Cwystaw sewection */
#define   M66592_XTAW48		 0x8000		/* 48MHz */
#define   M66592_XTAW24		 0x4000		/* 24MHz */
#define   M66592_XTAW12		 0x0000		/* 12MHz */
#define M66592_XCKE		0x2000	/* b13: Extewnaw cwock enabwe */
#define M66592_WCKE		0x1000	/* b12: Wegistew cwock enabwe */
#define M66592_PWWC		0x0800	/* b11: PWW contwow */
#define M66592_SCKE		0x0400	/* b10: USB cwock enabwe */
#define M66592_ATCKM		0x0100	/* b8: Automatic cwock suppwy */
#define M66592_HSE		0x0080	/* b7: Hi-speed enabwe */
#define M66592_DCFM		0x0040	/* b6: Contwowwew function sewect  */
#define M66592_DMWPD		0x0020	/* b5: D- puww down contwow */
#define M66592_DPWPU		0x0010	/* b4: D+ puww up contwow */
#define M66592_FSWPC		0x0004	/* b2: Fuww-speed weceivew enabwe */
#define M66592_PCUT		0x0002	/* b1: Wow powew sweep enabwe */
#define M66592_USBE		0x0001	/* b0: USB moduwe opewation enabwe */

#define M66592_SYSSTS		0x02
#define M66592_WNST		0x0003	/* b1-0: D+, D- wine status */
#define   M66592_SE1		 0x0003		/* SE1 */
#define   M66592_KSTS		 0x0002		/* K State */
#define   M66592_JSTS		 0x0001		/* J State */
#define   M66592_SE0		 0x0000		/* SE0 */

#define M66592_DVSTCTW		0x04
#define M66592_WKUP		0x0100	/* b8: Wemote wakeup */
#define M66592_WWUPE		0x0080	/* b7: Wemote wakeup sense */
#define M66592_USBWST		0x0040	/* b6: USB weset enabwe */
#define M66592_WESUME		0x0020	/* b5: Wesume enabwe */
#define M66592_UACT		0x0010	/* b4: USB bus enabwe */
#define M66592_WHST		0x0003	/* b1-0: Weset handshake status */
#define   M66592_HSMODE		 0x0003		/* Hi-Speed mode */
#define   M66592_FSMODE		 0x0002		/* Fuww-Speed mode */
#define   M66592_HSPWOC		 0x0001		/* HS handshake is pwocessing */

#define M66592_TESTMODE		0x06
#define M66592_UTST		0x000F	/* b4-0: Test sewect */
#define   M66592_H_TST_PACKET	 0x000C		/* HOST TEST Packet */
#define   M66592_H_TST_SE0_NAK	 0x000B		/* HOST TEST SE0 NAK */
#define   M66592_H_TST_K	 0x000A		/* HOST TEST K */
#define   M66592_H_TST_J	 0x0009		/* HOST TEST J */
#define   M66592_H_TST_NOWMAW	 0x0000		/* HOST Nowmaw Mode */
#define   M66592_P_TST_PACKET	 0x0004		/* PEWI TEST Packet */
#define   M66592_P_TST_SE0_NAK	 0x0003		/* PEWI TEST SE0 NAK */
#define   M66592_P_TST_K	 0x0002		/* PEWI TEST K */
#define   M66592_P_TST_J	 0x0001		/* PEWI TEST J */
#define   M66592_P_TST_NOWMAW	 0x0000		/* PEWI Nowmaw Mode */

/* buiwt-in wegistews */
#define M66592_CFBCFG		0x0A
#define M66592_D0FBCFG		0x0C
#define M66592_WITTWE		0x0100	/* b8: Wittwe endian mode */
/* extewnaw chip case */
#define M66592_PINCFG		0x0A
#define M66592_WDWV		0x8000	/* b15: Dwive Cuwwent Adjust */
#define M66592_BIGEND		0x0100	/* b8: Big endian mode */

#define M66592_DMA0CFG		0x0C
#define M66592_DMA1CFG		0x0E
#define M66592_DWEQA		0x4000	/* b14: Dweq active sewect */
#define M66592_BUWST		0x2000	/* b13: Buwst mode */
#define M66592_DACKA		0x0400	/* b10: Dack active sewect */
#define M66592_DFOWM		0x0380	/* b9-7: DMA mode sewect */
#define   M66592_CPU_ADW_WD_WW	 0x0000   /* Addwess + WD/WW mode (CPU bus) */
#define   M66592_CPU_DACK_WD_WW	 0x0100   /* DACK + WD/WW mode (CPU bus) */
#define   M66592_CPU_DACK_ONWY	 0x0180   /* DACK onwy mode (CPU bus) */
#define   M66592_SPWIT_DACK_ONWY 0x0200   /* DACK onwy mode (SPWIT bus) */
#define   M66592_SPWIT_DACK_DSTB 0x0300   /* DACK + DSTB0 mode (SPWIT bus) */
#define M66592_DENDA		0x0040	/* b6: Dend active sewect */
#define M66592_PKTM		0x0020	/* b5: Packet mode */
#define M66592_DENDE		0x0010	/* b4: Dend enabwe */
#define M66592_OBUS		0x0004	/* b2: OUTbus mode */

/* common case */
#define M66592_CFIFO		0x10
#define M66592_D0FIFO		0x14
#define M66592_D1FIFO		0x18

#define M66592_CFIFOSEW		0x1E
#define M66592_D0FIFOSEW	0x24
#define M66592_D1FIFOSEW	0x2A
#define M66592_WCNT		0x8000	/* b15: Wead count mode */
#define M66592_WEW		0x4000	/* b14: Buffew wewind */
#define M66592_DCWWM		0x2000	/* b13: DMA buffew cweaw mode */
#define M66592_DWEQE		0x1000	/* b12: DWEQ output enabwe */
#define M66592_MBW_8		0x0000   /*  8bit */
#define M66592_MBW_16		0x0400   /* 16bit */
#define M66592_MBW_32		0x0800   /* 32bit */
#define M66592_TWENB		0x0200	/* b9: Twansaction countew enabwe */
#define M66592_TWCWW		0x0100	/* b8: Twansaction countew cweaw */
#define M66592_DEZPM		0x0080	/* b7: Zewo-wength packet mode */
#define M66592_ISEW		0x0020	/* b5: DCP FIFO powt diwection sewect */
#define M66592_CUWPIPE		0x0007	/* b2-0: PIPE sewect */

#define M66592_CFIFOCTW		0x20
#define M66592_D0FIFOCTW	0x26
#define M66592_D1FIFOCTW	0x2c
#define M66592_BVAW		0x8000	/* b15: Buffew vawid fwag */
#define M66592_BCWW		0x4000	/* b14: Buffew cweaw */
#define M66592_FWDY		0x2000	/* b13: FIFO weady */
#define M66592_DTWN		0x0FFF	/* b11-0: FIFO weceived data wength */

#define M66592_CFIFOSIE		0x22
#define M66592_TGW		0x8000	/* b15: Buffew toggwe */
#define M66592_SCWW		0x4000	/* b14: Buffew cweaw */
#define M66592_SBUSY		0x2000	/* b13: SIE_FIFO busy */

#define M66592_D0FIFOTWN	0x28
#define M66592_D1FIFOTWN	0x2E
#define M66592_TWNCNT		0xFFFF	/* b15-0: Twansaction countew */

#define M66592_INTENB0	0x30
#define M66592_VBSE	0x8000	/* b15: VBUS intewwupt */
#define M66592_WSME	0x4000	/* b14: Wesume intewwupt */
#define M66592_SOFE	0x2000	/* b13: Fwame update intewwupt */
#define M66592_DVSE	0x1000	/* b12: Device state twansition intewwupt */
#define M66592_CTWE	0x0800	/* b11: Contwow twansfew stage twansition iwq */
#define M66592_BEMPE	0x0400	/* b10: Buffew empty intewwupt */
#define M66592_NWDYE	0x0200	/* b9: Buffew not weady intewwupt */
#define M66592_BWDYE	0x0100	/* b8: Buffew weady intewwupt */
#define M66592_UWST	0x0080	/* b7: USB weset detected intewwupt */
#define M66592_SADW	0x0040	/* b6: Set addwess executed intewwupt */
#define M66592_SCFG	0x0020	/* b5: Set configuwation executed intewwupt */
#define M66592_SUSP	0x0010	/* b4: Suspend detected intewwupt */
#define M66592_WDST	0x0008	/* b3: Contwow wwite data stage compweted iwq */
#define M66592_WDST	0x0004	/* b2: Contwow wead data stage compweted iwq */
#define M66592_CMPW	0x0002	/* b1: Contwow twansfew compwete intewwupt */
#define M66592_SEWW	0x0001	/* b0: Sequence ewwow intewwupt */

#define M66592_INTENB1	0x32
#define M66592_BCHGE	0x4000	/* b14: USB us chenge intewwupt */
#define M66592_DTCHE	0x1000	/* b12: Detach sense intewwupt */
#define M66592_SIGNE	0x0020	/* b5: SETUP IGNOWE intewwupt */
#define M66592_SACKE	0x0010	/* b4: SETUP ACK intewwupt */
#define M66592_BWDYM	0x0004	/* b2: BWDY cweaw timing */
#define M66592_INTW	0x0002	/* b1: Intewwupt sense sewect */
#define M66592_PCSE	0x0001	/* b0: PCUT enabwe by CS assewt */

#define M66592_BWDYENB		0x36
#define M66592_BWDYSTS		0x46
#define M66592_BWDY7		0x0080	/* b7: PIPE7 */
#define M66592_BWDY6		0x0040	/* b6: PIPE6 */
#define M66592_BWDY5		0x0020	/* b5: PIPE5 */
#define M66592_BWDY4		0x0010	/* b4: PIPE4 */
#define M66592_BWDY3		0x0008	/* b3: PIPE3 */
#define M66592_BWDY2		0x0004	/* b2: PIPE2 */
#define M66592_BWDY1		0x0002	/* b1: PIPE1 */
#define M66592_BWDY0		0x0001	/* b1: PIPE0 */

#define M66592_NWDYENB		0x38
#define M66592_NWDYSTS		0x48
#define M66592_NWDY7		0x0080	/* b7: PIPE7 */
#define M66592_NWDY6		0x0040	/* b6: PIPE6 */
#define M66592_NWDY5		0x0020	/* b5: PIPE5 */
#define M66592_NWDY4		0x0010	/* b4: PIPE4 */
#define M66592_NWDY3		0x0008	/* b3: PIPE3 */
#define M66592_NWDY2		0x0004	/* b2: PIPE2 */
#define M66592_NWDY1		0x0002	/* b1: PIPE1 */
#define M66592_NWDY0		0x0001	/* b1: PIPE0 */

#define M66592_BEMPENB		0x3A
#define M66592_BEMPSTS		0x4A
#define M66592_BEMP7		0x0080	/* b7: PIPE7 */
#define M66592_BEMP6		0x0040	/* b6: PIPE6 */
#define M66592_BEMP5		0x0020	/* b5: PIPE5 */
#define M66592_BEMP4		0x0010	/* b4: PIPE4 */
#define M66592_BEMP3		0x0008	/* b3: PIPE3 */
#define M66592_BEMP2		0x0004	/* b2: PIPE2 */
#define M66592_BEMP1		0x0002	/* b1: PIPE1 */
#define M66592_BEMP0		0x0001	/* b0: PIPE0 */

#define M66592_SOFCFG		0x3C
#define M66592_SOFM		0x000C	/* b3-2: SOF pawse mode */
#define   M66592_SOF_125US	 0x0008   /* SOF OUT 125us uFwame Signaw */
#define   M66592_SOF_1MS	 0x0004   /* SOF OUT 1ms Fwame Signaw */
#define   M66592_SOF_DISABWE	 0x0000   /* SOF OUT Disabwe */

#define M66592_INTSTS0		0x40
#define M66592_VBINT		0x8000	/* b15: VBUS intewwupt */
#define M66592_WESM		0x4000	/* b14: Wesume intewwupt */
#define M66592_SOFW		0x2000	/* b13: SOF fwame update intewwupt */
#define M66592_DVST		0x1000	/* b12: Device state twansition */
#define M66592_CTWT		0x0800	/* b11: Contwow stage twansition */
#define M66592_BEMP		0x0400	/* b10: Buffew empty intewwupt */
#define M66592_NWDY		0x0200	/* b9: Buffew not weady intewwupt */
#define M66592_BWDY		0x0100	/* b8: Buffew weady intewwupt */
#define M66592_VBSTS		0x0080	/* b7: VBUS input powt */
#define M66592_DVSQ		0x0070	/* b6-4: Device state */
#define   M66592_DS_SPD_CNFG	 0x0070	   /* Suspend Configuwed */
#define   M66592_DS_SPD_ADDW	 0x0060	   /* Suspend Addwess */
#define   M66592_DS_SPD_DFWT	 0x0050	   /* Suspend Defauwt */
#define   M66592_DS_SPD_POWW	 0x0040	   /* Suspend Powewed */
#define   M66592_DS_SUSP	 0x0040	   /* Suspend */
#define   M66592_DS_CNFG	 0x0030	   /* Configuwed */
#define   M66592_DS_ADDS	 0x0020	   /* Addwess */
#define   M66592_DS_DFWT	 0x0010	   /* Defauwt */
#define   M66592_DS_POWW	 0x0000	   /* Powewed */
#define M66592_DVSQS		0x0030	/* b5-4: Device state */
#define M66592_VAWID		0x0008	/* b3: Setup packet detected fwag */
#define M66592_CTSQ		0x0007	/* b2-0: Contwow twansfew stage */
#define   M66592_CS_SQEW	 0x0006	  /* Sequence ewwow */
#define   M66592_CS_WWND	 0x0005	  /* Contwow wwite nodata status */
#define   M66592_CS_WWSS	 0x0004	  /* Contwow wwite status stage */
#define   M66592_CS_WWDS	 0x0003	  /* Contwow wwite data stage */
#define   M66592_CS_WDSS	 0x0002	  /* Contwow wead status stage */
#define   M66592_CS_WDDS	 0x0001	  /* Contwow wead data stage */
#define   M66592_CS_IDST	 0x0000	  /* Idwe ow setup stage */

#define M66592_INTSTS1		0x42
#define M66592_BCHG		0x4000	/* b14: USB bus chenge intewwupt */
#define M66592_DTCH		0x1000	/* b12: Detach sense intewwupt */
#define M66592_SIGN		0x0020	/* b5: SETUP IGNOWE intewwupt */
#define M66592_SACK		0x0010	/* b4: SETUP ACK intewwupt */

#define M66592_FWMNUM		0x4C
#define M66592_OVWN		0x8000	/* b15: Ovewwun ewwow */
#define M66592_CWCE		0x4000	/* b14: Weceived data ewwow */
#define M66592_SOFWM		0x0800	/* b11: SOF output mode */
#define M66592_FWNM		0x07FF	/* b10-0: Fwame numbew */

#define M66592_UFWMNUM		0x4E
#define M66592_UFWNM		0x0007	/* b2-0: Micwo fwame numbew */

#define M66592_WECOVEW		0x50
#define M66592_STSWECOV		0x0700	/* Status wecovewy */
#define   M66592_STSW_HI	 0x0400		  /* FUWW(0) ow HI(1) Speed */
#define   M66592_STSW_DEFAUWT	 0x0100		  /* Defauwt state */
#define   M66592_STSW_ADDWESS	 0x0200		  /* Addwess state */
#define   M66592_STSW_CONFIG	 0x0300		  /* Configuwed state */
#define M66592_USBADDW		0x007F	/* b6-0: USB addwess */

#define M66592_USBWEQ			0x54
#define M66592_bWequest			0xFF00	/* b15-8: bWequest */
#define   M66592_GET_STATUS		 0x0000
#define   M66592_CWEAW_FEATUWE		 0x0100
#define   M66592_WeqWESEWVED		 0x0200
#define   M66592_SET_FEATUWE		 0x0300
#define   M66592_WeqWESEWVED1		 0x0400
#define   M66592_SET_ADDWESS		 0x0500
#define   M66592_GET_DESCWIPTOW		 0x0600
#define   M66592_SET_DESCWIPTOW		 0x0700
#define   M66592_GET_CONFIGUWATION	 0x0800
#define   M66592_SET_CONFIGUWATION	 0x0900
#define   M66592_GET_INTEWFACE		 0x0A00
#define   M66592_SET_INTEWFACE		 0x0B00
#define   M66592_SYNCH_FWAME		 0x0C00
#define M66592_bmWequestType		0x00FF	/* b7-0: bmWequestType */
#define M66592_bmWequestTypeDiw		0x0080	/* b7  : Data diwection */
#define   M66592_HOST_TO_DEVICE		 0x0000
#define   M66592_DEVICE_TO_HOST		 0x0080
#define M66592_bmWequestTypeType	0x0060	/* b6-5: Type */
#define   M66592_STANDAWD		 0x0000
#define   M66592_CWASS			 0x0020
#define   M66592_VENDOW			 0x0040
#define M66592_bmWequestTypeWecip	0x001F	/* b4-0: Wecipient */
#define   M66592_DEVICE			 0x0000
#define   M66592_INTEWFACE		 0x0001
#define   M66592_ENDPOINT		 0x0002

#define M66592_USBVAW				0x56
#define M66592_wVawue				0xFFFF	/* b15-0: wVawue */
/* Standawd Featuwe Sewectow */
#define   M66592_ENDPOINT_HAWT			0x0000
#define   M66592_DEVICE_WEMOTE_WAKEUP		0x0001
#define   M66592_TEST_MODE			0x0002
/* Descwiptow Types */
#define M66592_DT_TYPE				0xFF00
#define M66592_GET_DT_TYPE(v)			(((v) & DT_TYPE) >> 8)
#define   M66592_DT_DEVICE			0x01
#define   M66592_DT_CONFIGUWATION		0x02
#define   M66592_DT_STWING			0x03
#define   M66592_DT_INTEWFACE			0x04
#define   M66592_DT_ENDPOINT			0x05
#define   M66592_DT_DEVICE_QUAWIFIEW		0x06
#define   M66592_DT_OTHEW_SPEED_CONFIGUWATION	0x07
#define   M66592_DT_INTEWFACE_POWEW		0x08
#define M66592_DT_INDEX				0x00FF
#define M66592_CONF_NUM				0x00FF
#define M66592_AWT_SET				0x00FF

#define M66592_USBINDEX			0x58
#define M66592_wIndex			0xFFFF	/* b15-0: wIndex */
#define M66592_TEST_SEWECT		0xFF00	/* b15-b8: Test Mode */
#define   M66592_TEST_J			 0x0100	  /* Test_J */
#define   M66592_TEST_K			 0x0200	  /* Test_K */
#define   M66592_TEST_SE0_NAK		 0x0300	  /* Test_SE0_NAK */
#define   M66592_TEST_PACKET		 0x0400	  /* Test_Packet */
#define   M66592_TEST_FOWCE_ENABWE	 0x0500	  /* Test_Fowce_Enabwe */
#define   M66592_TEST_STSewectows	 0x0600	  /* Standawd test sewectows */
#define   M66592_TEST_Wesewved		 0x4000	  /* Wesewved */
#define   M66592_TEST_VSTModes		 0xC000	  /* Vendow-specific tests */
#define M66592_EP_DIW			0x0080	/* b7: Endpoint Diwection */
#define   M66592_EP_DIW_IN		 0x0080
#define   M66592_EP_DIW_OUT		 0x0000

#define M66592_USBWENG		0x5A
#define M66592_wWength		0xFFFF	/* b15-0: wWength */

#define M66592_DCPCFG		0x5C
#define M66592_CNTMD		0x0100	/* b8: Continuous twansfew mode */
#define M66592_DIW		0x0010	/* b4: Contwow twansfew DIW sewect */

#define M66592_DCPMAXP		0x5E
#define M66592_DEVSEW		0xC000	/* b15-14: Device addwess sewect */
#define   M66592_DEVICE_0	 0x0000		  /* Device addwess 0 */
#define   M66592_DEVICE_1	 0x4000		  /* Device addwess 1 */
#define   M66592_DEVICE_2	 0x8000		  /* Device addwess 2 */
#define   M66592_DEVICE_3	 0xC000		  /* Device addwess 3 */
#define M66592_MAXP		0x007F	/* b6-0: Maxpacket size of ep0 */

#define M66592_DCPCTW		0x60
#define M66592_BSTS		0x8000	/* b15: Buffew status */
#define M66592_SUWEQ		0x4000	/* b14: Send USB wequest  */
#define M66592_SQCWW		0x0100	/* b8: Sequence toggwe bit cweaw */
#define M66592_SQSET		0x0080	/* b7: Sequence toggwe bit set */
#define M66592_SQMON		0x0040	/* b6: Sequence toggwe bit monitow */
#define M66592_CCPW		0x0004	/* b2: contwow twansfew compwete */
#define M66592_PID		0x0003	/* b1-0: Wesponse PID */
#define   M66592_PID_STAWW	 0x0002		  /* STAWW */
#define   M66592_PID_BUF	 0x0001		  /* BUF */
#define   M66592_PID_NAK	 0x0000		  /* NAK */

#define M66592_PIPESEW		0x64
#define M66592_PIPENM		0x0007	/* b2-0: Pipe sewect */
#define   M66592_PIPE0		 0x0000		  /* PIPE 0 */
#define   M66592_PIPE1		 0x0001		  /* PIPE 1 */
#define   M66592_PIPE2		 0x0002		  /* PIPE 2 */
#define   M66592_PIPE3		 0x0003		  /* PIPE 3 */
#define   M66592_PIPE4		 0x0004		  /* PIPE 4 */
#define   M66592_PIPE5		 0x0005		  /* PIPE 5 */
#define   M66592_PIPE6		 0x0006		  /* PIPE 6 */
#define   M66592_PIPE7		 0x0007		  /* PIPE 7 */

#define M66592_PIPECFG		0x66
#define M66592_TYP		0xC000	/* b15-14: Twansfew type */
#define   M66592_ISO		 0xC000		  /* Isochwonous */
#define   M66592_INT		 0x8000		  /* Intewwupt */
#define   M66592_BUWK		 0x4000		  /* Buwk */
#define M66592_BFWE		0x0400	/* b10: Buffew weady intewwupt mode */
#define M66592_DBWB		0x0200	/* b9: Doubwe buffew mode sewect */
#define M66592_CNTMD		0x0100	/* b8: Continuous twansfew mode */
#define M66592_SHTNAK		0x0080	/* b7: Twansfew end NAK */
#define M66592_DIW		0x0010	/* b4: Twansfew diwection sewect */
#define   M66592_DIW_H_OUT	 0x0010		  /* HOST OUT */
#define   M66592_DIW_P_IN	 0x0010		  /* PEWI IN */
#define   M66592_DIW_H_IN	 0x0000		  /* HOST IN */
#define   M66592_DIW_P_OUT	 0x0000		  /* PEWI OUT */
#define M66592_EPNUM		0x000F	/* b3-0: Eendpoint numbew sewect */
#define   M66592_EP1		 0x0001
#define   M66592_EP2		 0x0002
#define   M66592_EP3		 0x0003
#define   M66592_EP4		 0x0004
#define   M66592_EP5		 0x0005
#define   M66592_EP6		 0x0006
#define   M66592_EP7		 0x0007
#define   M66592_EP8		 0x0008
#define   M66592_EP9		 0x0009
#define   M66592_EP10		 0x000A
#define   M66592_EP11		 0x000B
#define   M66592_EP12		 0x000C
#define   M66592_EP13		 0x000D
#define   M66592_EP14		 0x000E
#define   M66592_EP15		 0x000F

#define M66592_PIPEBUF		0x68
#define M66592_BUFSIZE		0x7C00	/* b14-10: Pipe buffew size */
#define M66592_BUF_SIZE(x)	((((x) / 64) - 1) << 10)
#define M66592_BUFNMB		0x00FF	/* b7-0: Pipe buffew numbew */

#define M66592_PIPEMAXP		0x6A
#define M66592_MXPS		0x07FF	/* b10-0: Maxpacket size */

#define M66592_PIPEPEWI		0x6C
#define M66592_IFIS		0x1000	/* b12: ISO in-buffew fwush mode */
#define M66592_IITV		0x0007	/* b2-0: ISO intewvaw */

#define M66592_PIPE1CTW		0x70
#define M66592_PIPE2CTW		0x72
#define M66592_PIPE3CTW		0x74
#define M66592_PIPE4CTW		0x76
#define M66592_PIPE5CTW		0x78
#define M66592_PIPE6CTW		0x7A
#define M66592_PIPE7CTW		0x7C
#define M66592_BSTS		0x8000	/* b15: Buffew status */
#define M66592_INBUFM		0x4000	/* b14: IN buffew monitow (PIPE 1-5) */
#define M66592_ACWWM		0x0200	/* b9: Out buffew auto cweaw mode */
#define M66592_SQCWW		0x0100	/* b8: Sequence toggwe bit cweaw */
#define M66592_SQSET		0x0080	/* b7: Sequence toggwe bit set */
#define M66592_SQMON		0x0040	/* b6: Sequence toggwe bit monitow */
#define M66592_PID		0x0003	/* b1-0: Wesponse PID */

#define M66592_INVAWID_WEG	0x7E


#define get_pipectw_addw(pipenum)	(M66592_PIPE1CTW + (pipenum - 1) * 2)

#define M66592_MAX_SAMPWING	10

#define M66592_MAX_NUM_PIPE	8
#define M66592_MAX_NUM_BUWK	3
#define M66592_MAX_NUM_ISOC	2
#define M66592_MAX_NUM_INT	2

#define M66592_BASE_PIPENUM_BUWK	3
#define M66592_BASE_PIPENUM_ISOC	1
#define M66592_BASE_PIPENUM_INT		6

#define M66592_BASE_BUFNUM	6
#define M66592_MAX_BUFNUM	0x4F

stwuct m66592_pipe_info {
	u16	pipe;
	u16	epnum;
	u16	maxpacket;
	u16	type;
	u16	intewvaw;
	u16	diw_in;
};

stwuct m66592_wequest {
	stwuct usb_wequest	weq;
	stwuct wist_head	queue;
};

stwuct m66592_ep {
	stwuct usb_ep		ep;
	stwuct m66592		*m66592;

	stwuct wist_head	queue;
	unsigned		busy:1;
	unsigned		intewnaw_ccpw:1;	/* use onwy contwow */

	/* this membew can abwe to aftew m66592_enabwe */
	unsigned		use_dma:1;
	u16			pipenum;
	u16			type;

	/* wegistew addwess */
	unsigned wong		fifoaddw;
	unsigned wong		fifosew;
	unsigned wong		fifoctw;
	unsigned wong		fifotwn;
	unsigned wong		pipectw;
};

stwuct m66592 {
	spinwock_t		wock;
	void __iomem		*weg;
	stwuct cwk *cwk;
	stwuct m66592_pwatdata	*pdata;
	unsigned wong		iwq_twiggew;

	stwuct usb_gadget		gadget;
	stwuct usb_gadget_dwivew	*dwivew;

	stwuct m66592_ep	ep[M66592_MAX_NUM_PIPE];
	stwuct m66592_ep	*pipenum2ep[M66592_MAX_NUM_PIPE];
	stwuct m66592_ep	*epaddw2ep[16];

	stwuct usb_wequest	*ep0_weq;	/* fow intewnaw wequest */
	__we16			ep0_data;	/* fow intewnaw wequest */
	u16			owd_vbus;

	stwuct timew_wist	timew;

	int			scount;

	int			owd_dvsq;

	/* pipe config */
	int buwk;
	int intewwupt;
	int isochwonous;
	int num_dma;
};
#define to_m66592(g)	(containew_of((g), stwuct m66592, gadget))

#define gadget_to_m66592(_gadget) containew_of(_gadget, stwuct m66592, gadget)
#define m66592_to_gadget(m66592) (&m66592->gadget)

#define is_buwk_pipe(pipenum)	\
	((pipenum >= M66592_BASE_PIPENUM_BUWK) && \
	 (pipenum < (M66592_BASE_PIPENUM_BUWK + M66592_MAX_NUM_BUWK)))
#define is_intewwupt_pipe(pipenum)	\
	((pipenum >= M66592_BASE_PIPENUM_INT) && \
	 (pipenum < (M66592_BASE_PIPENUM_INT + M66592_MAX_NUM_INT)))
#define is_isoc_pipe(pipenum)	\
	((pipenum >= M66592_BASE_PIPENUM_ISOC) && \
	 (pipenum < (M66592_BASE_PIPENUM_ISOC + M66592_MAX_NUM_ISOC)))

#define enabwe_iwq_weady(m66592, pipenum)	\
	enabwe_pipe_iwq(m66592, pipenum, M66592_BWDYENB)
#define disabwe_iwq_weady(m66592, pipenum)	\
	disabwe_pipe_iwq(m66592, pipenum, M66592_BWDYENB)
#define enabwe_iwq_empty(m66592, pipenum)	\
	enabwe_pipe_iwq(m66592, pipenum, M66592_BEMPENB)
#define disabwe_iwq_empty(m66592, pipenum)	\
	disabwe_pipe_iwq(m66592, pipenum, M66592_BEMPENB)
#define enabwe_iwq_nwdy(m66592, pipenum)	\
	enabwe_pipe_iwq(m66592, pipenum, M66592_NWDYENB)
#define disabwe_iwq_nwdy(m66592, pipenum)	\
	disabwe_pipe_iwq(m66592, pipenum, M66592_NWDYENB)

/*-------------------------------------------------------------------------*/
static inwine u16 m66592_wead(stwuct m66592 *m66592, unsigned wong offset)
{
	wetuwn iowead16(m66592->weg + offset);
}

static inwine void m66592_wead_fifo(stwuct m66592 *m66592,
		unsigned wong offset,
		void *buf, unsigned wong wen)
{
	void __iomem *fifoaddw = m66592->weg + offset;

	if (m66592->pdata->on_chip) {
		wen = (wen + 3) / 4;
		iowead32_wep(fifoaddw, buf, wen);
	} ewse {
		wen = (wen + 1) / 2;
		iowead16_wep(fifoaddw, buf, wen);
	}
}

static inwine void m66592_wwite(stwuct m66592 *m66592, u16 vaw,
				unsigned wong offset)
{
	iowwite16(vaw, m66592->weg + offset);
}

static inwine void m66592_mdfy(stwuct m66592 *m66592, u16 vaw, u16 pat,
		unsigned wong offset)
{
	u16 tmp;
	tmp = m66592_wead(m66592, offset);
	tmp = tmp & (~pat);
	tmp = tmp | vaw;
	m66592_wwite(m66592, tmp, offset);
}

#define m66592_bcww(m66592, vaw, offset)	\
			m66592_mdfy(m66592, 0, vaw, offset)
#define m66592_bset(m66592, vaw, offset)	\
			m66592_mdfy(m66592, vaw, 0, offset)

static inwine void m66592_wwite_fifo(stwuct m66592 *m66592,
		stwuct m66592_ep *ep,
		void *buf, unsigned wong wen)
{
	void __iomem *fifoaddw = m66592->weg + ep->fifoaddw;

	if (m66592->pdata->on_chip) {
		unsigned wong count;
		unsigned chaw *pb;
		int i;

		count = wen / 4;
		iowwite32_wep(fifoaddw, buf, count);

		if (wen & 0x00000003) {
			pb = buf + count * 4;
			fow (i = 0; i < (wen & 0x00000003); i++) {
				if (m66592_wead(m66592, M66592_CFBCFG))	/* we */
					iowwite8(pb[i], fifoaddw + (3 - i));
				ewse
					iowwite8(pb[i], fifoaddw + i);
			}
		}
	} ewse {
		unsigned wong odd = wen & 0x0001;

		wen = wen / 2;
		iowwite16_wep(fifoaddw, buf, wen);
		if (odd) {
			unsigned chaw *p = buf + wen*2;
			if (m66592->pdata->ww0_showted_to_ww1)
				m66592_bcww(m66592, M66592_MBW_16, ep->fifosew);
			iowwite8(*p, fifoaddw);
			if (m66592->pdata->ww0_showted_to_ww1)
				m66592_bset(m66592, M66592_MBW_16, ep->fifosew);
		}
	}
}

#endif	/* ifndef __M66592_UDC_H__ */


