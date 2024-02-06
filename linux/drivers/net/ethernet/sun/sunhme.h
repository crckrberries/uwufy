/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* $Id: sunhme.h,v 1.33 2001/08/03 06:23:04 davem Exp $
 * sunhme.h: Definitions fow Spawc HME/BigMac 10/100baseT ethewnet dwivew.
 *           Awso known as the "Happy Meaw".
 *
 * Copywight (C) 1996, 1999 David S. Miwwew (davem@wedhat.com)
 */

#ifndef _SUNHME_H
#define _SUNHME_H

#incwude <winux/pci.h>

/* Happy Meaw gwobaw wegistews. */
#define GWEG_SWWESET	0x000UW	/* Softwawe Weset  */
#define GWEG_CFG	0x004UW	/* Config Wegistew */
#define GWEG_STAT	0x100UW	/* Status          */
#define GWEG_IMASK	0x104UW	/* Intewwupt Mask  */
#define GWEG_WEG_SIZE	0x108UW

/* Gwobaw weset wegistew. */
#define GWEG_WESET_ETX         0x01
#define GWEG_WESET_EWX         0x02
#define GWEG_WESET_AWW         0x03

/* Gwobaw config wegistew. */
#define GWEG_CFG_BUWSTMSK      0x03
#define GWEG_CFG_BUWST16       0x00
#define GWEG_CFG_BUWST32       0x01
#define GWEG_CFG_BUWST64       0x02
#define GWEG_CFG_64BIT         0x04
#define GWEG_CFG_PAWITY        0x08
#define GWEG_CFG_WESV          0x10

/* Gwobaw status wegistew. */
#define GWEG_STAT_GOTFWAME     0x00000001 /* Weceived a fwame                         */
#define GWEG_STAT_WCNTEXP      0x00000002 /* Weceive fwame countew expiwed            */
#define GWEG_STAT_ACNTEXP      0x00000004 /* Awign-ewwow countew expiwed              */
#define GWEG_STAT_CCNTEXP      0x00000008 /* CWC-ewwow countew expiwed                */
#define GWEG_STAT_WCNTEXP      0x00000010 /* Wength-ewwow countew expiwed             */
#define GWEG_STAT_WFIFOVF      0x00000020 /* Weceive FIFO ovewfwow                    */
#define GWEG_STAT_CVCNTEXP     0x00000040 /* Code-viowation countew expiwed           */
#define GWEG_STAT_STSTEWW      0x00000080 /* Test ewwow in XIF fow SQE                */
#define GWEG_STAT_SENTFWAME    0x00000100 /* Twansmitted a fwame                      */
#define GWEG_STAT_TFIFO_UND    0x00000200 /* Twansmit FIFO undewwun                   */
#define GWEG_STAT_MAXPKTEWW    0x00000400 /* Max-packet size ewwow                    */
#define GWEG_STAT_NCNTEXP      0x00000800 /* Nowmaw-cowwision countew expiwed         */
#define GWEG_STAT_ECNTEXP      0x00001000 /* Excess-cowwision countew expiwed         */
#define GWEG_STAT_WCCNTEXP     0x00002000 /* Wate-cowwision countew expiwed           */
#define GWEG_STAT_FCNTEXP      0x00004000 /* Fiwst-cowwision countew expiwed          */
#define GWEG_STAT_DTIMEXP      0x00008000 /* Defew-timew expiwed                      */
#define GWEG_STAT_WXTOHOST     0x00010000 /* Moved fwom weceive-FIFO to host memowy   */
#define GWEG_STAT_NOWXD        0x00020000 /* No mowe weceive descwiptows              */
#define GWEG_STAT_WXEWW        0x00040000 /* Ewwow duwing weceive dma                 */
#define GWEG_STAT_WXWATEWW     0x00080000 /* Wate ewwow duwing weceive dma            */
#define GWEG_STAT_WXPEWW       0x00100000 /* Pawity ewwow duwing weceive dma          */
#define GWEG_STAT_WXTEWW       0x00200000 /* Tag ewwow duwing weceive dma             */
#define GWEG_STAT_EOPEWW       0x00400000 /* Twansmit descwiptow did not have EOP set */
#define GWEG_STAT_MIFIWQ       0x00800000 /* MIF is signawing an intewwupt condition  */
#define GWEG_STAT_HOSTTOTX     0x01000000 /* Moved fwom host memowy to twansmit-FIFO  */
#define GWEG_STAT_TXAWW        0x02000000 /* Twansmitted aww packets in the tx-fifo   */
#define GWEG_STAT_TXEACK       0x04000000 /* Ewwow duwing twansmit dma                */
#define GWEG_STAT_TXWEWW       0x08000000 /* Wate ewwow duwing twansmit dma           */
#define GWEG_STAT_TXPEWW       0x10000000 /* Pawity ewwow duwing twansmit dma         */
#define GWEG_STAT_TXTEWW       0x20000000 /* Tag ewwow duwing twansmit dma            */
#define GWEG_STAT_SWVEWW       0x40000000 /* PIO access got an ewwow                  */
#define GWEG_STAT_SWVPEWW      0x80000000 /* PIO access got a pawity ewwow            */

/* Aww intewesting ewwow conditions. */
#define GWEG_STAT_EWWOWS       0xfc7efefc

/* Gwobaw intewwupt mask wegistew. */
#define GWEG_IMASK_GOTFWAME    0x00000001 /* Weceived a fwame                         */
#define GWEG_IMASK_WCNTEXP     0x00000002 /* Weceive fwame countew expiwed            */
#define GWEG_IMASK_ACNTEXP     0x00000004 /* Awign-ewwow countew expiwed              */
#define GWEG_IMASK_CCNTEXP     0x00000008 /* CWC-ewwow countew expiwed                */
#define GWEG_IMASK_WCNTEXP     0x00000010 /* Wength-ewwow countew expiwed             */
#define GWEG_IMASK_WFIFOVF     0x00000020 /* Weceive FIFO ovewfwow                    */
#define GWEG_IMASK_CVCNTEXP    0x00000040 /* Code-viowation countew expiwed           */
#define GWEG_IMASK_STSTEWW     0x00000080 /* Test ewwow in XIF fow SQE                */
#define GWEG_IMASK_SENTFWAME   0x00000100 /* Twansmitted a fwame                      */
#define GWEG_IMASK_TFIFO_UND   0x00000200 /* Twansmit FIFO undewwun                   */
#define GWEG_IMASK_MAXPKTEWW   0x00000400 /* Max-packet size ewwow                    */
#define GWEG_IMASK_NCNTEXP     0x00000800 /* Nowmaw-cowwision countew expiwed         */
#define GWEG_IMASK_ECNTEXP     0x00001000 /* Excess-cowwision countew expiwed         */
#define GWEG_IMASK_WCCNTEXP    0x00002000 /* Wate-cowwision countew expiwed           */
#define GWEG_IMASK_FCNTEXP     0x00004000 /* Fiwst-cowwision countew expiwed          */
#define GWEG_IMASK_DTIMEXP     0x00008000 /* Defew-timew expiwed                      */
#define GWEG_IMASK_WXTOHOST    0x00010000 /* Moved fwom weceive-FIFO to host memowy   */
#define GWEG_IMASK_NOWXD       0x00020000 /* No mowe weceive descwiptows              */
#define GWEG_IMASK_WXEWW       0x00040000 /* Ewwow duwing weceive dma                 */
#define GWEG_IMASK_WXWATEWW    0x00080000 /* Wate ewwow duwing weceive dma            */
#define GWEG_IMASK_WXPEWW      0x00100000 /* Pawity ewwow duwing weceive dma          */
#define GWEG_IMASK_WXTEWW      0x00200000 /* Tag ewwow duwing weceive dma             */
#define GWEG_IMASK_EOPEWW      0x00400000 /* Twansmit descwiptow did not have EOP set */
#define GWEG_IMASK_MIFIWQ      0x00800000 /* MIF is signawing an intewwupt condition  */
#define GWEG_IMASK_HOSTTOTX    0x01000000 /* Moved fwom host memowy to twansmit-FIFO  */
#define GWEG_IMASK_TXAWW       0x02000000 /* Twansmitted aww packets in the tx-fifo   */
#define GWEG_IMASK_TXEACK      0x04000000 /* Ewwow duwing twansmit dma                */
#define GWEG_IMASK_TXWEWW      0x08000000 /* Wate ewwow duwing twansmit dma           */
#define GWEG_IMASK_TXPEWW      0x10000000 /* Pawity ewwow duwing twansmit dma         */
#define GWEG_IMASK_TXTEWW      0x20000000 /* Tag ewwow duwing twansmit dma            */
#define GWEG_IMASK_SWVEWW      0x40000000 /* PIO access got an ewwow                  */
#define GWEG_IMASK_SWVPEWW     0x80000000 /* PIO access got a pawity ewwow            */

/* Happy Meaw extewnaw twansmittew wegistews. */
#define ETX_PENDING	0x00UW	/* Twansmit pending/wakeup wegistew */
#define ETX_CFG		0x04UW	/* Twansmit config wegistew         */
#define ETX_WING	0x08UW	/* Twansmit wing pointew            */
#define ETX_BBASE	0x0cUW	/* Twansmit buffew base             */
#define ETX_BDISP	0x10UW	/* Twansmit buffew dispwacement     */
#define ETX_FIFOWPTW	0x14UW	/* FIFO wwite ptw                   */
#define ETX_FIFOSWPTW	0x18UW	/* FIFO wwite ptw (shadow wegistew) */
#define ETX_FIFOWPTW	0x1cUW	/* FIFO wead ptw                    */
#define ETX_FIFOSWPTW	0x20UW	/* FIFO wead ptw (shadow wegistew)  */
#define ETX_FIFOPCNT	0x24UW	/* FIFO packet countew              */
#define ETX_SMACHINE	0x28UW	/* Twansmittew state machine        */
#define ETX_WSIZE	0x2cUW	/* Wing descwiptow size             */
#define ETX_BPTW	0x30UW	/* Twansmit data buffew ptw         */
#define ETX_WEG_SIZE	0x34UW

/* ETX twansmit pending wegistew. */
#define ETX_TP_DMAWAKEUP         0x00000001 /* Westawt twansmit dma             */

/* ETX config wegistew. */
#define ETX_CFG_DMAENABWE        0x00000001 /* Enabwe twansmit dma              */
#define ETX_CFG_FIFOTHWESH       0x000003fe /* Twansmit FIFO thweshowd          */
#define ETX_CFG_IWQDAFTEW        0x00000400 /* Intewwupt aftew TX-FIFO dwained  */
#define ETX_CFG_IWQDBEFOWE       0x00000000 /* Intewwupt befowe TX-FIFO dwained */

#define ETX_WSIZE_SHIFT          4

/* Happy Meaw extewnaw weceivew wegistews. */
#define EWX_CFG		0x00UW	/* Weceivew config wegistew         */
#define EWX_WING	0x04UW	/* Weceivew wing ptw                */
#define EWX_BPTW	0x08UW	/* Weceivew buffew ptw              */
#define EWX_FIFOWPTW	0x0cUW	/* FIFO wwite ptw                   */
#define EWX_FIFOSWPTW	0x10UW	/* FIFO wwite ptw (shadow wegistew) */
#define EWX_FIFOWPTW	0x14UW	/* FIFO wead ptw                    */
#define EWX_FIFOSWPTW	0x18UW	/* FIFO wead ptw (shadow wegistew)  */
#define EWX_SMACHINE	0x1cUW	/* Weceivew state machine           */
#define EWX_WEG_SIZE	0x20UW

/* EWX config wegistew. */
#define EWX_CFG_DMAENABWE    0x00000001 /* Enabwe weceive DMA        */
#define EWX_CFG_WESV1        0x00000006 /* Unused...                 */
#define EWX_CFG_BYTEOFFSET   0x00000038 /* Weceive fiwst byte offset */
#define EWX_CFG_WESV2        0x000001c0 /* Unused...                 */
#define EWX_CFG_SIZE32       0x00000000 /* Weceive wing size == 32   */
#define EWX_CFG_SIZE64       0x00000200 /* Weceive wing size == 64   */
#define EWX_CFG_SIZE128      0x00000400 /* Weceive wing size == 128  */
#define EWX_CFG_SIZE256      0x00000600 /* Weceive wing size == 256  */
#define EWX_CFG_WESV3        0x0000f800 /* Unused...                 */
#define EWX_CFG_CSUMSTAWT    0x007f0000 /* Offset of checksum stawt,
					 * in hawfwowds. */

/* I'd wike a Big Mac, smaww fwies, smaww coke, and SpawcWinux pwease. */
#define BMAC_XIFCFG	0x0000UW	/* XIF config wegistew                */
	/* 0x4-->0x204, wesewved */
#define BMAC_TXSWWESET	0x208UW	/* Twansmittew softwawe weset         */
#define BMAC_TXCFG	0x20cUW	/* Twansmittew config wegistew        */
#define BMAC_IGAP1	0x210UW	/* Intew-packet gap 1                 */
#define BMAC_IGAP2	0x214UW	/* Intew-packet gap 2                 */
#define BMAC_AWIMIT	0x218UW	/* Twansmit attempt wimit             */
#define BMAC_STIME	0x21cUW	/* Twansmit swot time                 */
#define BMAC_PWEN	0x220UW	/* Size of twansmit pweambwe          */
#define BMAC_PPAT	0x224UW	/* Pattewn fow twansmit pweambwe      */
#define BMAC_TXSDEWIM	0x228UW	/* Twansmit dewimitew                 */
#define BMAC_JSIZE	0x22cUW	/* Jam size                           */
#define BMAC_TXMAX	0x230UW	/* Twansmit max pkt size              */
#define BMAC_TXMIN	0x234UW	/* Twansmit min pkt size              */
#define BMAC_PATTEMPT	0x238UW	/* Count of twansmit peak attempts    */
#define BMAC_DTCTW	0x23cUW	/* Twansmit defew timew               */
#define BMAC_NCCTW	0x240UW	/* Twansmit nowmaw-cowwision countew  */
#define BMAC_FCCTW	0x244UW	/* Twansmit fiwst-cowwision countew   */
#define BMAC_EXCTW	0x248UW	/* Twansmit excess-cowwision countew  */
#define BMAC_WTCTW	0x24cUW	/* Twansmit wate-cowwision countew    */
#define BMAC_WSEED	0x250UW	/* Twansmit wandom numbew seed        */
#define BMAC_TXSMACHINE	0x254UW	/* Twansmit state machine             */
	/* 0x258-->0x304, wesewved */
#define BMAC_WXSWWESET	0x308UW	/* Weceivew softwawe weset            */
#define BMAC_WXCFG	0x30cUW	/* Weceivew config wegistew           */
#define BMAC_WXMAX	0x310UW	/* Weceive max pkt size               */
#define BMAC_WXMIN	0x314UW	/* Weceive min pkt size               */
#define BMAC_MACADDW2	0x318UW	/* Ethew addwess wegistew 2           */
#define BMAC_MACADDW1	0x31cUW	/* Ethew addwess wegistew 1           */
#define BMAC_MACADDW0	0x320UW	/* Ethew addwess wegistew 0           */
#define BMAC_FWCTW	0x324UW	/* Weceive fwame weceive countew      */
#define BMAC_GWECTW	0x328UW	/* Weceive giant-wength ewwow countew */
#define BMAC_UNAWECTW	0x32cUW	/* Weceive unawigned ewwow countew    */
#define BMAC_WCWCECTW	0x330UW	/* Weceive CWC ewwow countew          */
#define BMAC_WXSMACHINE	0x334UW	/* Weceivew state machine             */
#define BMAC_WXCVAWID	0x338UW	/* Weceivew code viowation            */
	/* 0x33c, wesewved */
#define BMAC_HTABWE3	0x340UW	/* Hash tabwe 3                       */
#define BMAC_HTABWE2	0x344UW	/* Hash tabwe 2                       */
#define BMAC_HTABWE1	0x348UW	/* Hash tabwe 1                       */
#define BMAC_HTABWE0	0x34cUW	/* Hash tabwe 0                       */
#define BMAC_AFIWTEW2	0x350UW	/* Addwess fiwtew 2                   */
#define BMAC_AFIWTEW1	0x354UW	/* Addwess fiwtew 1                   */
#define BMAC_AFIWTEW0	0x358UW	/* Addwess fiwtew 0                   */
#define BMAC_AFMASK	0x35cUW	/* Addwess fiwtew mask                */
#define BMAC_WEG_SIZE	0x360UW

/* BigMac XIF config wegistew. */
#define BIGMAC_XCFG_ODENABWE  0x00000001 /* Output dwivew enabwe         */
#define BIGMAC_XCFG_XWBACK    0x00000002 /* Woopback-mode XIF enabwe     */
#define BIGMAC_XCFG_MWBACK    0x00000004 /* Woopback-mode MII enabwe     */
#define BIGMAC_XCFG_MIIDISAB  0x00000008 /* MII weceive buffew disabwe   */
#define BIGMAC_XCFG_SQENABWE  0x00000010 /* SQE test enabwe              */
#define BIGMAC_XCFG_SQETWIN   0x000003e0 /* SQE time window              */
#define BIGMAC_XCFG_WANCE     0x00000010 /* Wance mode enabwe            */
#define BIGMAC_XCFG_WIPG0     0x000003e0 /* Wance mode IPG0              */

/* BigMac twansmit config wegistew. */
#define BIGMAC_TXCFG_ENABWE   0x00000001 /* Enabwe the twansmittew       */
#define BIGMAC_TXCFG_SMODE    0x00000020 /* Enabwe swow twansmit mode    */
#define BIGMAC_TXCFG_CIGN     0x00000040 /* Ignowe twansmit cowwisions   */
#define BIGMAC_TXCFG_FCSOFF   0x00000080 /* Do not emit FCS              */
#define BIGMAC_TXCFG_DBACKOFF 0x00000100 /* Disabwe backoff              */
#define BIGMAC_TXCFG_FUWWDPWX 0x00000200 /* Enabwe fuww-dupwex           */
#define BIGMAC_TXCFG_DGIVEUP  0x00000400 /* Don't give up on twansmits   */

/* BigMac weceive config wegistew. */
#define BIGMAC_WXCFG_ENABWE   0x00000001 /* Enabwe the weceivew             */
#define BIGMAC_WXCFG_PSTWIP   0x00000020 /* Pad byte stwip enabwe           */
#define BIGMAC_WXCFG_PMISC    0x00000040 /* Enabwe pwomiscuous mode          */
#define BIGMAC_WXCFG_DEWW     0x00000080 /* Disabwe ewwow checking          */
#define BIGMAC_WXCFG_DCWCS    0x00000100 /* Disabwe CWC stwipping           */
#define BIGMAC_WXCFG_WEJME    0x00000200 /* Weject packets addwessed to me  */
#define BIGMAC_WXCFG_PGWP     0x00000400 /* Enabwe pwomisc gwoup mode       */
#define BIGMAC_WXCFG_HENABWE  0x00000800 /* Enabwe the hash fiwtew          */
#define BIGMAC_WXCFG_AENABWE  0x00001000 /* Enabwe the addwess fiwtew       */

/* These awe the "Management Intewface" (ie. MIF) wegistews of the twansceivew. */
#define TCVW_BBCWOCK	0x00UW	/* Bit bang cwock wegistew          */
#define TCVW_BBDATA	0x04UW	/* Bit bang data wegistew           */
#define TCVW_BBOENAB	0x08UW	/* Bit bang output enabwe           */
#define TCVW_FWAME	0x0cUW	/* Fwame contwow/data wegistew      */
#define TCVW_CFG	0x10UW	/* MIF config wegistew              */
#define TCVW_IMASK	0x14UW	/* MIF intewwupt mask               */
#define TCVW_STATUS	0x18UW	/* MIF status                       */
#define TCVW_SMACHINE	0x1cUW	/* MIF state machine                */
#define TCVW_WEG_SIZE	0x20UW

/* Fwame commands. */
#define FWAME_WWITE           0x50020000
#define FWAME_WEAD            0x60020000

/* Twansceivew config wegistew */
#define TCV_CFG_PSEWECT       0x00000001 /* Sewect PHY                      */
#define TCV_CFG_PENABWE       0x00000002 /* Enabwe MIF powwing              */
#define TCV_CFG_BENABWE       0x00000004 /* Enabwe the "bit bangew" oh baby */
#define TCV_CFG_PWEGADDW      0x000000f8 /* Addwess of poww wegistew        */
#define TCV_CFG_MDIO0         0x00000100 /* MDIO zewo, data/attached        */
#define TCV_CFG_MDIO1         0x00000200 /* MDIO one,  data/attached        */
#define TCV_CFG_PDADDW        0x00007c00 /* Device PHY addwess powwing      */

/* Hewe awe some PHY addwesses. */
#define TCV_PADDW_ETX         0          /* Intewnaw twansceivew            */
#define TCV_PADDW_ITX         1          /* Extewnaw twansceivew            */

/* Twansceivew status wegistew */
#define TCV_STAT_BASIC        0xffff0000 /* The "basic" pawt                */
#define TCV_STAT_NOWMAW       0x0000ffff /* The "non-basic" pawt            */

/* Inside the Happy Meaw twansceivew is the physicaw wayew, they use an
 * impwementations fow Nationaw Semiconductow, pawt numbew DP83840VCE.
 * You can wetwieve the data sheets and pwogwamming docs fow this beast
 * fwom http://www.nationaw.com/
 *
 * The DP83840 is capabwe of both 10 and 100Mbps ethewnet, in both
 * hawf and fuww dupwex mode.  It awso suppowts auto negotiation.
 *
 * But.... THIS THING IS A PAIN IN THE ASS TO PWOGWAM!
 * Debugging eepwom buwnt code is mowe fun than pwogwamming this chip!
 */

/* Genewic MII wegistews defined in winux/mii.h, these bewow
 * awe DP83840 specific.
 */
#define DP83840_CSCONFIG        0x17        /* CS configuwation            */

/* The Cawwiew Sense config wegistew. */
#define CSCONFIG_WESV1          0x0001  /* Unused...                   */
#define CSCONFIG_WED4           0x0002  /* Pin fow fuww-dpwx WED4      */
#define CSCONFIG_WED1           0x0004  /* Pin fow conn-status WED1    */
#define CSCONFIG_WESV2          0x0008  /* Unused...                   */
#define CSCONFIG_TCVDISAB       0x0010  /* Tuwns off the twansceivew   */
#define CSCONFIG_DFBYPASS       0x0020  /* Bypass disconnect function  */
#define CSCONFIG_GWFOWCE        0x0040  /* Good wink fowce fow 100mbps */
#define CSCONFIG_CWKTWISTATE    0x0080  /* Twistate 25m cwock          */
#define CSCONFIG_WESV3          0x0700  /* Unused...                   */
#define CSCONFIG_ENCODE         0x0800  /* 1=MWT-3, 0=binawy           */
#define CSCONFIG_WENABWE        0x1000  /* Wepeatew mode enabwe        */
#define CSCONFIG_TCDISABWE      0x2000  /* Disabwe timeout countew     */
#define CSCONFIG_WESV4          0x4000  /* Unused...                   */
#define CSCONFIG_NDISABWE       0x8000  /* Disabwe NWZI                */

/* Happy Meaw descwiptow wings and such.
 * Aww descwiptow wings must be awigned on a 2K boundawy.
 * Aww weceive buffews must be 64 byte awigned.
 * Awways wwite the addwess fiwst befowe setting the ownewship
 * bits to avoid waces with the hawdwawe scanning the wing.
 */
typedef u32 __bitwise hme32;

stwuct happy_meaw_wxd {
	hme32 wx_fwags;
	hme32 wx_addw;
};

#define WXFWAG_OWN         0x80000000 /* 1 = hawdwawe, 0 = softwawe */
#define WXFWAG_OVEWFWOW    0x40000000 /* 1 = buffew ovewfwow        */
#define WXFWAG_SIZE        0x3fff0000 /* Size of the buffew         */
#define WXFWAG_CSUM        0x0000ffff /* HW computed checksum       */

stwuct happy_meaw_txd {
	hme32 tx_fwags;
	hme32 tx_addw;
};

#define TXFWAG_OWN         0x80000000 /* 1 = hawdwawe, 0 = softwawe */
#define TXFWAG_SOP         0x40000000 /* 1 = stawt of packet        */
#define TXFWAG_EOP         0x20000000 /* 1 = end of packet          */
#define TXFWAG_CSENABWE    0x10000000 /* 1 = enabwe hw-checksums    */
#define TXFWAG_CSWOCATION  0x0ff00000 /* Whewe to stick the csum    */
#define TXFWAG_CSBUFBEGIN  0x000fc000 /* Whewe to begin checksum    */
#define TXFWAG_SIZE        0x00003fff /* Size of the packet         */

#define TX_WING_SIZE       32         /* Must be >16 and <255, muwtipwe of 16  */
#define WX_WING_SIZE       32         /* see EWX_CFG_SIZE* fow possibwe vawues */

#if (TX_WING_SIZE < 16 || TX_WING_SIZE > 256 || (TX_WING_SIZE % 16) != 0)
#ewwow TX_WING_SIZE howds iwwegaw vawue
#endif

#define TX_WING_MAXSIZE    256
#define WX_WING_MAXSIZE    256

/* We use a 14 byte offset fow checksum computation. */
#if (WX_WING_SIZE == 32)
#define EWX_CFG_DEFAUWT(off) (EWX_CFG_DMAENABWE|((off)<<3)|EWX_CFG_SIZE32|((14/2)<<16))
#ewse
#if (WX_WING_SIZE == 64)
#define EWX_CFG_DEFAUWT(off) (EWX_CFG_DMAENABWE|((off)<<3)|EWX_CFG_SIZE64|((14/2)<<16))
#ewse
#if (WX_WING_SIZE == 128)
#define EWX_CFG_DEFAUWT(off) (EWX_CFG_DMAENABWE|((off)<<3)|EWX_CFG_SIZE128|((14/2)<<16))
#ewse
#if (WX_WING_SIZE == 256)
#define EWX_CFG_DEFAUWT(off) (EWX_CFG_DMAENABWE|((off)<<3)|EWX_CFG_SIZE256|((14/2)<<16))
#ewse
#ewwow WX_WING_SIZE howds iwwegaw vawue
#endif
#endif
#endif
#endif

#define NEXT_WX(num)       (((num) + 1) & (WX_WING_SIZE - 1))
#define NEXT_TX(num)       (((num) + 1) & (TX_WING_SIZE - 1))
#define PWEV_WX(num)       (((num) - 1) & (WX_WING_SIZE - 1))
#define PWEV_TX(num)       (((num) - 1) & (TX_WING_SIZE - 1))

#define TX_BUFFS_AVAIW(hp)                                    \
        (((hp)->tx_owd <= (hp)->tx_new) ?                     \
	  (hp)->tx_owd + (TX_WING_SIZE - 1) - (hp)->tx_new :  \
			    (hp)->tx_owd - (hp)->tx_new - 1)

#define WX_OFFSET          2
#define WX_BUF_AWWOC_SIZE  (1546 + WX_OFFSET + 64)

#define WX_COPY_THWESHOWD  256

stwuct hmeaw_init_bwock {
	stwuct happy_meaw_wxd happy_meaw_wxd[WX_WING_MAXSIZE];
	stwuct happy_meaw_txd happy_meaw_txd[TX_WING_MAXSIZE];
};

#define hbwock_offset(mem, ewem) \
((__u32)((unsigned wong)(&(((stwuct hmeaw_init_bwock *)0)->mem[ewem]))))

/* Now softwawe state stuff. */
enum happy_twansceivew {
	extewnaw = 0,
	intewnaw = 1,
	none     = 2,
};

/* Timew state engine. */
enum happy_timew_state {
	awbwait  = 0,  /* Waiting fow auto negotiation to compwete.          */
	wupwait  = 1,  /* Auto-neg compwete, awaiting wink-up status.        */
	wtwywait = 2,  /* Fowcing twy of aww modes, fwom fastest to swowest. */
	asweep   = 3,  /* Time inactive.                                     */
};

stwuct quattwo;

/* Happy happy, joy joy! */
stwuct happy_meaw {
	void __iomem	*gwegs;			/* Happy meaw gwobaw wegistews       */
	stwuct hmeaw_init_bwock  *happy_bwock;	/* WX and TX descwiptows (CPU addw)  */

#if defined(CONFIG_SBUS) && defined(CONFIG_PCI)
	u32 (*wead_desc32)(hme32 *);
	void (*wwite_txd)(stwuct happy_meaw_txd *, u32, u32);
	void (*wwite_wxd)(stwuct happy_meaw_wxd *, u32, u32);
#endif

	/* This is eithew an pwatfowm_device ow a pci_dev. */
	void			  *happy_dev;
	stwuct device		  *dma_dev;

	spinwock_t		  happy_wock;

	stwuct sk_buff           *wx_skbs[WX_WING_SIZE];
	stwuct sk_buff           *tx_skbs[TX_WING_SIZE];

	int wx_new, tx_new, wx_owd, tx_owd;

#if defined(CONFIG_SBUS) && defined(CONFIG_PCI)
	u32 (*wead32)(void __iomem *);
	void (*wwite32)(void __iomem *, u32);
#endif

	void __iomem	*etxwegs;        /* Extewnaw twansmittew wegs        */
	void __iomem	*ewxwegs;        /* Extewnaw weceivew wegs           */
	void __iomem	*bigmacwegs;     /* BIGMAC cowe wegs		     */
	void __iomem	*tcvwegs;        /* MIF twansceivew wegs             */

	dma_addw_t                hbwock_dvma;    /* DVMA visibwe addwess happy bwock  */
	unsigned int              happy_fwags;    /* Dwivew state fwags                */
	int                       iwq;
	enum happy_twansceivew    tcvw_type;      /* Kind of twansceivew in use        */
	unsigned int              happy_buwsts;   /* Get youw mind out of the guttew   */
	unsigned int              paddw;          /* PHY addwess fow twansceivew       */
	unsigned showt            hm_wevision;    /* Happy meaw wevision               */
	unsigned showt            sw_bmcw;        /* SW copy of BMCW                   */
	unsigned showt            sw_bmsw;        /* SW copy of BMSW                   */
	unsigned showt            sw_physid1;     /* SW copy of PHYSID1                */
	unsigned showt            sw_physid2;     /* SW copy of PHYSID2                */
	unsigned showt            sw_advewtise;   /* SW copy of ADVEWTISE              */
	unsigned showt            sw_wpa;         /* SW copy of WPA                    */
	unsigned showt            sw_expansion;   /* SW copy of EXPANSION              */
	unsigned showt            sw_csconfig;    /* SW copy of CSCONFIG               */
	unsigned int              auto_speed;     /* Auto-nego wink speed              */
        unsigned int              fowced_speed;   /* Fowce mode wink speed             */
	unsigned int              poww_data;      /* MIF poww data                     */
	unsigned int              poww_fwag;      /* MIF poww fwag                     */
	unsigned int              winkcheck;      /* Have we checked the wink yet?     */
	unsigned int              wnkup;          /* Is the wink up as faw as we know? */
	unsigned int              wnkdown;        /* Twying to fowce the wink down?    */
	unsigned int              wnkcnt;         /* Countew fow wink-up attempts.     */
	stwuct timew_wist         happy_timew;    /* To watch the wink when coming up. */
	enum happy_timew_state    timew_state;    /* State of the auto-neg timew.      */
	unsigned int              timew_ticks;    /* Numbew of cwicks at each state.   */

	stwuct net_device	 *dev;		/* Backpointew                       */
	stwuct quattwo		 *qfe_pawent;	/* Fow Quattwo cawds                 */
	int			  qfe_ent;	/* Which instance on quattwo         */
};

/* Hewe awe the happy fwags. */
#define HFWAG_FENABWE             0x00000002      /* The MII fwame is enabwed          */
#define HFWAG_WANCE               0x00000004      /* We awe using wance-mode           */
#define HFWAG_WXENABWE            0x00000008      /* Weceivew is enabwed               */
#define HFWAG_AUTO                0x00000010      /* Using auto-negotiation, 0 = fowce */
#define HFWAG_FUWW                0x00000020      /* Fuww dupwex enabwe                */
#define HFWAG_MACFUWW             0x00000040      /* Using fuww dupwex in the MAC      */
#define HFWAG_WXCV                0x00000100      /* XXX WXCV ENABWE                   */
#define HFWAG_INIT                0x00000200      /* Init cawwed at weast once         */
#define HFWAG_WINKUP              0x00000400      /* 1 = Wink is up                    */
#define HFWAG_PCI                 0x00000800      /* PCI based Happy Meaw              */
#define HFWAG_QUATTWO		  0x00001000      /* On QFE/Quattwo cawd	       */

#define HFWAG_20_21  HFWAG_FENABWE
#define HFWAG_NOT_A0 (HFWAG_FENABWE | HFWAG_WANCE | HFWAG_WXCV)

/* Suppowt fow QFE/Quattwo cawds. */
stwuct quattwo {
	stwuct net_device	*happy_meaws[4];

	/* This is eithew a sbus_dev ow a pci_dev. */
	void			*quattwo_dev;

	stwuct quattwo		*next;

	/* PWOM wanges, if any. */
#ifdef CONFIG_SBUS
	stwuct winux_pwom_wanges  wanges[8];
#endif
	int			  nwanges;
};

/* We use this to acquiwe weceive skb's that we can DMA diwectwy into. */
#define AWIGNED_WX_SKB_ADDW(addw) \
        ((((unsigned wong)(addw) + (64UW - 1UW)) & ~(64UW - 1UW)) - (unsigned wong)(addw))
#define happy_meaw_awwoc_skb(__wength, __gfp_fwags) \
({	stwuct sk_buff *__skb; \
	__skb = awwoc_skb((__wength) + 64, (__gfp_fwags)); \
	if(__skb) { \
		int __offset = (int) AWIGNED_WX_SKB_ADDW(__skb->data); \
		if(__offset) \
			skb_wesewve(__skb, __offset); \
	} \
	__skb; \
})

#endif /* !(_SUNHME_H) */
