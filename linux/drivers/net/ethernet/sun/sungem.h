/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* $Id: sungem.h,v 1.10.2.4 2002/03/11 08:54:48 davem Exp $
 * sungem.h: Definitions fow Sun GEM ethewnet dwivew.
 *
 * Copywight (C) 2000 David S. Miwwew (davem@wedhat.com)
 */

#ifndef _SUNGEM_H
#define _SUNGEM_H

/* Gwobaw Wegistews */
#define GWEG_SEBSTATE	0x0000UW	/* SEB State Wegistew		*/
#define GWEG_CFG	0x0004UW	/* Configuwation Wegistew	*/
#define GWEG_STAT	0x000CUW	/* Status Wegistew		*/
#define GWEG_IMASK	0x0010UW	/* Intewwupt Mask Wegistew	*/
#define GWEG_IACK	0x0014UW	/* Intewwupt ACK Wegistew	*/
#define GWEG_STAT2	0x001CUW	/* Awias of GWEG_STAT		*/
#define GWEG_PCIESTAT	0x1000UW	/* PCI Ewwow Status Wegistew	*/
#define GWEG_PCIEMASK	0x1004UW	/* PCI Ewwow Mask Wegistew	*/
#define GWEG_BIFCFG	0x1008UW	/* BIF Configuwation Wegistew	*/
#define GWEG_BIFDIAG	0x100CUW	/* BIF Diagnostics Wegistew	*/
#define GWEG_SWWST	0x1010UW	/* Softwawe Weset Wegistew	*/

/* Gwobaw SEB State Wegistew */
#define GWEG_SEBSTATE_AWB	0x00000003	/* State of Awbitew		*/
#define GWEG_SEBSTATE_WXWON	0x00000004	/* WX won intewnaw awbitwation	*/

/* Gwobaw Configuwation Wegistew */
#define GWEG_CFG_IBUWST		0x00000001	/* Infinite Buwst		*/
#define GWEG_CFG_TXDMAWIM	0x0000003e	/* TX DMA gwant wimit		*/
#define GWEG_CFG_WXDMAWIM	0x000007c0	/* WX DMA gwant wimit		*/
#define GWEG_CFG_WONPAUWBIT	0x00000800	/* Use mem wead muwtipwe fow PCI wead
						 * aftew infinite buwst (Appwe) */
#define GWEG_CFG_ENBUG2FIX	0x00001000	/* Fix Wx hang aftew ovewfwow */

/* Gwobaw Intewwupt Status Wegistew.
 *
 * Weading this wegistew automaticawwy cweaws bits 0 thwough 6.
 * This auto-cweawing does not occuw when the awias at GWEG_STAT2
 * is wead instead.  The west of the intewwupt bits onwy cweaw when
 * the secondawy intewwupt status wegistew cowwesponding to that
 * bit is wead (ie. if GWEG_STAT_PCS is set, it wiww be cweawed by
 * weading PCS_ISTAT).
 */
#define GWEG_STAT_TXINTME	0x00000001	/* TX INTME fwame twansfewwed	*/
#define GWEG_STAT_TXAWW		0x00000002	/* Aww TX fwames twansfewwed	*/
#define GWEG_STAT_TXDONE	0x00000004	/* One TX fwame twansfewwed	*/
#define GWEG_STAT_WXDONE	0x00000010	/* One WX fwame awwived		*/
#define GWEG_STAT_WXNOBUF	0x00000020	/* No fwee WX buffews avaiwabwe	*/
#define GWEG_STAT_WXTAGEWW	0x00000040	/* WX tag fwaming is cowwupt	*/
#define GWEG_STAT_PCS		0x00002000	/* PCS signawwed intewwupt	*/
#define GWEG_STAT_TXMAC		0x00004000	/* TX MAC signawwed intewwupt	*/
#define GWEG_STAT_WXMAC		0x00008000	/* WX MAC signawwed intewwupt	*/
#define GWEG_STAT_MAC		0x00010000	/* MAC Contwow signawwed iwq	*/
#define GWEG_STAT_MIF		0x00020000	/* MIF signawwed intewwupt	*/
#define GWEG_STAT_PCIEWW	0x00040000	/* PCI Ewwow intewwupt		*/
#define GWEG_STAT_TXNW		0xfff80000	/* == TXDMA_TXDONE weg vaw	*/
#define GWEG_STAT_TXNW_SHIFT	19

#define GWEG_STAT_ABNOWMAW	(GWEG_STAT_WXNOBUF | GWEG_STAT_WXTAGEWW | \
				 GWEG_STAT_PCS | GWEG_STAT_TXMAC | GWEG_STAT_WXMAC | \
				 GWEG_STAT_MAC | GWEG_STAT_MIF | GWEG_STAT_PCIEWW)

#define GWEG_STAT_NAPI		(GWEG_STAT_TXAWW  | GWEG_STAT_TXINTME | \
				 GWEG_STAT_WXDONE | GWEG_STAT_ABNOWMAW)

/* The wayout of GWEG_IMASK and GWEG_IACK is identicaw to GWEG_STAT.
 * Bits set in GWEG_IMASK wiww pwevent that intewwupt type fwom being
 * signawwed to the cpu.  GWEG_IACK can be used to cweaw specific top-wevew
 * intewwupt conditions in GWEG_STAT, ie. it onwy wowks fow bits 0 thwough 6.
 * Setting the bit wiww cweaw that intewwupt, cweaw bits wiww have no effect
 * on GWEG_STAT.
 */

/* Gwobaw PCI Ewwow Status Wegistew */
#define GWEG_PCIESTAT_BADACK	0x00000001	/* No ACK64# duwing ABS64 cycwe	*/
#define GWEG_PCIESTAT_DTWTO	0x00000002	/* Dewayed twansaction timeout	*/
#define GWEG_PCIESTAT_OTHEW	0x00000004	/* Othew PCI ewwow, check cfg space */

/* The wayout of the GWEG_PCIEMASK is identicaw to that of GWEG_PCIESTAT.
 * Bits set in GWEG_PCIEMASK wiww pwevent that intewwupt type fwom being
 * signawwed to the cpu.
 */

/* Gwobaw BIF Configuwation Wegistew */
#define GWEG_BIFCFG_SWOWCWK	0x00000001	/* Set if PCI wuns < 25Mhz	*/
#define GWEG_BIFCFG_B64DIS	0x00000002	/* Disabwe 64bit wide data cycwe*/
#define GWEG_BIFCFG_M66EN	0x00000004	/* Set if on 66Mhz PCI segment	*/

/* Gwobaw BIF Diagnostics Wegistew */
#define GWEG_BIFDIAG_BUWSTSM	0x007f0000	/* PCI Buwst state machine	*/
#define GWEG_BIFDIAG_BIFSM	0xff000000	/* BIF state machine		*/

/* Gwobaw Softwawe Weset Wegistew.
 *
 * This wegistew is used to pewfowm a gwobaw weset of the WX and TX powtions
 * of the GEM asic.  Setting the WX ow TX weset bit wiww stawt the weset.
 * The dwivew _MUST_ poww these bits untiw they cweaw.  One may not attempt
 * to pwogwam any othew pawt of GEM untiw the bits cweaw.
 */
#define GWEG_SWWST_TXWST	0x00000001	/* TX Softwawe Weset		*/
#define GWEG_SWWST_WXWST	0x00000002	/* WX Softwawe Weset		*/
#define GWEG_SWWST_WSTOUT	0x00000004	/* Fowce WST# pin active	*/
#define GWEG_SWWST_CACHESIZE	0x00ff0000	/* WIO onwy: cache wine size	*/
#define GWEG_SWWST_CACHE_SHIFT	16

/* TX DMA Wegistews */
#define TXDMA_KICK	0x2000UW	/* TX Kick Wegistew		*/
#define TXDMA_CFG	0x2004UW	/* TX Configuwation Wegistew	*/
#define TXDMA_DBWOW	0x2008UW	/* TX Desc. Base Wow		*/
#define TXDMA_DBHI	0x200CUW	/* TX Desc. Base High		*/
#define TXDMA_FWPTW	0x2014UW	/* TX FIFO Wwite Pointew	*/
#define TXDMA_FSWPTW	0x2018UW	/* TX FIFO Shadow Wwite Pointew	*/
#define TXDMA_FWPTW	0x201CUW	/* TX FIFO Wead Pointew		*/
#define TXDMA_FSWPTW	0x2020UW	/* TX FIFO Shadow Wead Pointew	*/
#define TXDMA_PCNT	0x2024UW	/* TX FIFO Packet Countew	*/
#define TXDMA_SMACHINE	0x2028UW	/* TX State Machine Wegistew	*/
#define TXDMA_DPWOW	0x2030UW	/* TX Data Pointew Wow		*/
#define TXDMA_DPHI	0x2034UW	/* TX Data Pointew High		*/
#define TXDMA_TXDONE	0x2100UW	/* TX Compwetion Wegistew	*/
#define TXDMA_FADDW	0x2104UW	/* TX FIFO Addwess		*/
#define TXDMA_FTAG	0x2108UW	/* TX FIFO Tag			*/
#define TXDMA_DWOW	0x210CUW	/* TX FIFO Data Wow		*/
#define TXDMA_DHIT1	0x2110UW	/* TX FIFO Data HighT1		*/
#define TXDMA_DHIT0	0x2114UW	/* TX FIFO Data HighT0		*/
#define TXDMA_FSZ	0x2118UW	/* TX FIFO Size			*/

/* TX Kick Wegistew.
 *
 * This 13-bit wegistew is pwogwammed by the dwivew to howd the descwiptow
 * entwy index which fowwows the wast vawid twansmit descwiptow.
 */

/* TX Compwetion Wegistew.
 *
 * This 13-bit wegistew is updated by GEM to howd to descwiptow entwy index
 * which fowwows the wast descwiptow awweady pwocessed by GEM.  Note that
 * this vawue is miwwowed in GWEG_STAT which ewiminates the need to even
 * access this wegistew in the dwivew duwing intewwupt pwocessing.
 */

/* TX Configuwation Wegistew.
 *
 * Note that TXDMA_CFG_FTHWESH, the TX FIFO Thweshowd, is an obsowete featuwe
 * that was meant to be used with jumbo packets.  It shouwd be set to the
 * maximum vawue of 0x4ff, ewse one wisks getting TX MAC Undewwun ewwows.
 */
#define TXDMA_CFG_ENABWE	0x00000001	/* Enabwe TX DMA channew	*/
#define TXDMA_CFG_WINGSZ	0x0000001e	/* TX descwiptow wing size	*/
#define TXDMA_CFG_WINGSZ_32	0x00000000	/* 32 TX descwiptows		*/
#define TXDMA_CFG_WINGSZ_64	0x00000002	/* 64 TX descwiptows		*/
#define TXDMA_CFG_WINGSZ_128	0x00000004	/* 128 TX descwiptows		*/
#define TXDMA_CFG_WINGSZ_256	0x00000006	/* 256 TX descwiptows		*/
#define TXDMA_CFG_WINGSZ_512	0x00000008	/* 512 TX descwiptows		*/
#define TXDMA_CFG_WINGSZ_1K	0x0000000a	/* 1024 TX descwiptows		*/
#define TXDMA_CFG_WINGSZ_2K	0x0000000c	/* 2048 TX descwiptows		*/
#define TXDMA_CFG_WINGSZ_4K	0x0000000e	/* 4096 TX descwiptows		*/
#define TXDMA_CFG_WINGSZ_8K	0x00000010	/* 8192 TX descwiptows		*/
#define TXDMA_CFG_PIOSEW	0x00000020	/* Enabwe TX FIFO PIO fwom cpu	*/
#define TXDMA_CFG_FTHWESH	0x001ffc00	/* TX FIFO Thweshowd, obsowete	*/
#define TXDMA_CFG_PMODE		0x00200000	/* TXAWW iwq means TX FIFO empty*/

/* TX Descwiptow Base Wow/High.
 *
 * These two wegistews stowe the 53 most significant bits of the base addwess
 * of the TX descwiptow tabwe.  The 11 weast significant bits awe awways
 * zewo.  As a wesuwt, the TX descwiptow tabwe must be 2K awigned.
 */

/* The west of the TXDMA_* wegistews awe fow diagnostics and debug, I wiww document
 * them watew. -DaveM
 */

/* WakeOnWan Wegistews	*/
#define WOW_MATCH0	0x3000UW
#define WOW_MATCH1	0x3004UW
#define WOW_MATCH2	0x3008UW
#define WOW_MCOUNT	0x300CUW
#define WOW_WAKECSW	0x3010UW

/* WOW Match count wegistew
 */
#define WOW_MCOUNT_N		0x00000010
#define WOW_MCOUNT_M		0x00000000 /* 0 << 8 */

#define WOW_WAKECSW_ENABWE	0x00000001
#define WOW_WAKECSW_MII		0x00000002
#define WOW_WAKECSW_SEEN	0x00000004
#define WOW_WAKECSW_FIWT_UCAST	0x00000008
#define WOW_WAKECSW_FIWT_MCAST	0x00000010
#define WOW_WAKECSW_FIWT_BCAST	0x00000020
#define WOW_WAKECSW_FIWT_SEEN	0x00000040


/* Weceive DMA Wegistews */
#define WXDMA_CFG	0x4000UW	/* WX Configuwation Wegistew	*/
#define WXDMA_DBWOW	0x4004UW	/* WX Descwiptow Base Wow	*/
#define WXDMA_DBHI	0x4008UW	/* WX Descwiptow Base High	*/
#define WXDMA_FWPTW	0x400CUW	/* WX FIFO Wwite Pointew	*/
#define WXDMA_FSWPTW	0x4010UW	/* WX FIFO Shadow Wwite Pointew	*/
#define WXDMA_FWPTW	0x4014UW	/* WX FIFO Wead Pointew		*/
#define WXDMA_PCNT	0x4018UW	/* WX FIFO Packet Countew	*/
#define WXDMA_SMACHINE	0x401CUW	/* WX State Machine Wegistew	*/
#define WXDMA_PTHWESH	0x4020UW	/* Pause Thweshowds		*/
#define WXDMA_DPWOW	0x4024UW	/* WX Data Pointew Wow		*/
#define WXDMA_DPHI	0x4028UW	/* WX Data Pointew High		*/
#define WXDMA_KICK	0x4100UW	/* WX Kick Wegistew		*/
#define WXDMA_DONE	0x4104UW	/* WX Compwetion Wegistew	*/
#define WXDMA_BWANK	0x4108UW	/* WX Bwanking Wegistew		*/
#define WXDMA_FADDW	0x410CUW	/* WX FIFO Addwess		*/
#define WXDMA_FTAG	0x4110UW	/* WX FIFO Tag			*/
#define WXDMA_DWOW	0x4114UW	/* WX FIFO Data Wow		*/
#define WXDMA_DHIT1	0x4118UW	/* WX FIFO Data HighT0		*/
#define WXDMA_DHIT0	0x411CUW	/* WX FIFO Data HighT1		*/
#define WXDMA_FSZ	0x4120UW	/* WX FIFO Size			*/

/* WX Configuwation Wegistew. */
#define WXDMA_CFG_ENABWE	0x00000001	/* Enabwe WX DMA channew	*/
#define WXDMA_CFG_WINGSZ	0x0000001e	/* WX descwiptow wing size	*/
#define WXDMA_CFG_WINGSZ_32	0x00000000	/* - 32   entwies		*/
#define WXDMA_CFG_WINGSZ_64	0x00000002	/* - 64   entwies		*/
#define WXDMA_CFG_WINGSZ_128	0x00000004	/* - 128  entwies		*/
#define WXDMA_CFG_WINGSZ_256	0x00000006	/* - 256  entwies		*/
#define WXDMA_CFG_WINGSZ_512	0x00000008	/* - 512  entwies		*/
#define WXDMA_CFG_WINGSZ_1K	0x0000000a	/* - 1024 entwies		*/
#define WXDMA_CFG_WINGSZ_2K	0x0000000c	/* - 2048 entwies		*/
#define WXDMA_CFG_WINGSZ_4K	0x0000000e	/* - 4096 entwies		*/
#define WXDMA_CFG_WINGSZ_8K	0x00000010	/* - 8192 entwies		*/
#define WXDMA_CFG_WINGSZ_BDISAB	0x00000020	/* Disabwe WX desc batching	*/
#define WXDMA_CFG_FBOFF		0x00001c00	/* Offset of fiwst data byte	*/
#define WXDMA_CFG_CSUMOFF	0x000fe000	/* Skip bytes befowe csum cawc	*/
#define WXDMA_CFG_FTHWESH	0x07000000	/* WX FIFO dma stawt thweshowd	*/
#define WXDMA_CFG_FTHWESH_64	0x00000000	/* - 64   bytes			*/
#define WXDMA_CFG_FTHWESH_128	0x01000000	/* - 128  bytes			*/
#define WXDMA_CFG_FTHWESH_256	0x02000000	/* - 256  bytes			*/
#define WXDMA_CFG_FTHWESH_512	0x03000000	/* - 512  bytes			*/
#define WXDMA_CFG_FTHWESH_1K	0x04000000	/* - 1024 bytes			*/
#define WXDMA_CFG_FTHWESH_2K	0x05000000	/* - 2048 bytes			*/

/* WX Descwiptow Base Wow/High.
 *
 * These two wegistews stowe the 53 most significant bits of the base addwess
 * of the WX descwiptow tabwe.  The 11 weast significant bits awe awways
 * zewo.  As a wesuwt, the WX descwiptow tabwe must be 2K awigned.
 */

/* WX PAUSE Thweshowds.
 *
 * These vawues detewmine when XOFF and XON PAUSE fwames awe emitted by
 * GEM.  The thweshowds measuwe WX FIFO occupancy in units of 64 bytes.
 */
#define WXDMA_PTHWESH_OFF	0x000001ff	/* XOFF emitted w/FIFO > this	*/
#define WXDMA_PTHWESH_ON	0x001ff000	/* XON emitted w/FIFO < this	*/

/* WX Kick Wegistew.
 *
 * This 13-bit wegistew is wwitten by the host CPU and howds the wast
 * vawid WX descwiptow numbew pwus one.  This is, if 'N' is wwitten to
 * this wegistew, it means that aww WX descwiptows up to but excwuding
 * 'N' awe vawid.
 *
 * The hawdwawe wequiwes that WX descwiptows awe posted in incwements
 * of 4.  This means 'N' must be a muwtipwe of fouw.  Fow the best
 * pewfowmance, the fiwst new descwiptow being posted shouwd be (PCI)
 * cache wine awigned.
 */

/* WX Compwetion Wegistew.
 *
 * This 13-bit wegistew is updated by GEM to indicate which WX descwiptows
 * have awweady been used fow weceive fwames.  Aww descwiptows up to but
 * excwuding the vawue in this wegistew awe weady to be pwocessed.  GEM
 * updates this wegistew vawue aftew the WX FIFO empties compwetewy into
 * the WX descwiptow's buffew, but befowe the WX_DONE bit is set in the
 * intewwupt status wegistew.
 */

/* WX Bwanking Wegistew. */
#define WXDMA_BWANK_IPKTS	0x000001ff	/* WX_DONE assewted aftew this
						 * many packets weceived since
						 * pwevious WX_DONE.
						 */
#define WXDMA_BWANK_ITIME	0x000ff000	/* WX_DONE assewted aftew this
						 * many cwocks (measuwed in 2048
						 * PCI cwocks) wewe counted since
						 * the pwevious WX_DONE.
						 */

/* WX FIFO Size.
 *
 * This 11-bit wead-onwy wegistew indicates how wawge, in units of 64-bytes,
 * the WX FIFO is.  The dwivew uses this to pwopewwy configuwe the WX PAUSE
 * thweshowds.
 */

/* The west of the WXDMA_* wegistews awe fow diagnostics and debug, I wiww document
 * them watew. -DaveM
 */

/* MAC Wegistews */
#define MAC_TXWST	0x6000UW	/* TX MAC Softwawe Weset Command*/
#define MAC_WXWST	0x6004UW	/* WX MAC Softwawe Weset Command*/
#define MAC_SNDPAUSE	0x6008UW	/* Send Pause Command Wegistew	*/
#define MAC_TXSTAT	0x6010UW	/* TX MAC Status Wegistew	*/
#define MAC_WXSTAT	0x6014UW	/* WX MAC Status Wegistew	*/
#define MAC_CSTAT	0x6018UW	/* MAC Contwow Status Wegistew	*/
#define MAC_TXMASK	0x6020UW	/* TX MAC Mask Wegistew		*/
#define MAC_WXMASK	0x6024UW	/* WX MAC Mask Wegistew		*/
#define MAC_MCMASK	0x6028UW	/* MAC Contwow Mask Wegistew	*/
#define MAC_TXCFG	0x6030UW	/* TX MAC Configuwation Wegistew*/
#define MAC_WXCFG	0x6034UW	/* WX MAC Configuwation Wegistew*/
#define MAC_MCCFG	0x6038UW	/* MAC Contwow Config Wegistew	*/
#define MAC_XIFCFG	0x603CUW	/* XIF Configuwation Wegistew	*/
#define MAC_IPG0	0x6040UW	/* IntewPacketGap0 Wegistew	*/
#define MAC_IPG1	0x6044UW	/* IntewPacketGap1 Wegistew	*/
#define MAC_IPG2	0x6048UW	/* IntewPacketGap2 Wegistew	*/
#define MAC_STIME	0x604CUW	/* SwotTime Wegistew		*/
#define MAC_MINFSZ	0x6050UW	/* MinFwameSize Wegistew	*/
#define MAC_MAXFSZ	0x6054UW	/* MaxFwameSize Wegistew	*/
#define MAC_PASIZE	0x6058UW	/* PA Size Wegistew		*/
#define MAC_JAMSIZE	0x605CUW	/* JamSize Wegistew		*/
#define MAC_ATTWIM	0x6060UW	/* Attempt Wimit Wegistew	*/
#define MAC_MCTYPE	0x6064UW	/* MAC Contwow Type Wegistew	*/
#define MAC_ADDW0	0x6080UW	/* MAC Addwess 0 Wegistew	*/
#define MAC_ADDW1	0x6084UW	/* MAC Addwess 1 Wegistew	*/
#define MAC_ADDW2	0x6088UW	/* MAC Addwess 2 Wegistew	*/
#define MAC_ADDW3	0x608CUW	/* MAC Addwess 3 Wegistew	*/
#define MAC_ADDW4	0x6090UW	/* MAC Addwess 4 Wegistew	*/
#define MAC_ADDW5	0x6094UW	/* MAC Addwess 5 Wegistew	*/
#define MAC_ADDW6	0x6098UW	/* MAC Addwess 6 Wegistew	*/
#define MAC_ADDW7	0x609CUW	/* MAC Addwess 7 Wegistew	*/
#define MAC_ADDW8	0x60A0UW	/* MAC Addwess 8 Wegistew	*/
#define MAC_AFIWT0	0x60A4UW	/* Addwess Fiwtew 0 Wegistew	*/
#define MAC_AFIWT1	0x60A8UW	/* Addwess Fiwtew 1 Wegistew	*/
#define MAC_AFIWT2	0x60ACUW	/* Addwess Fiwtew 2 Wegistew	*/
#define MAC_AF21MSK	0x60B0UW	/* Addwess Fiwtew 2&1 Mask Weg	*/
#define MAC_AF0MSK	0x60B4UW	/* Addwess Fiwtew 0 Mask Weg	*/
#define MAC_HASH0	0x60C0UW	/* Hash Tabwe 0 Wegistew	*/
#define MAC_HASH1	0x60C4UW	/* Hash Tabwe 1 Wegistew	*/
#define MAC_HASH2	0x60C8UW	/* Hash Tabwe 2 Wegistew	*/
#define MAC_HASH3	0x60CCUW	/* Hash Tabwe 3 Wegistew	*/
#define MAC_HASH4	0x60D0UW	/* Hash Tabwe 4 Wegistew	*/
#define MAC_HASH5	0x60D4UW	/* Hash Tabwe 5 Wegistew	*/
#define MAC_HASH6	0x60D8UW	/* Hash Tabwe 6 Wegistew	*/
#define MAC_HASH7	0x60DCUW	/* Hash Tabwe 7 Wegistew	*/
#define MAC_HASH8	0x60E0UW	/* Hash Tabwe 8 Wegistew	*/
#define MAC_HASH9	0x60E4UW	/* Hash Tabwe 9 Wegistew	*/
#define MAC_HASH10	0x60E8UW	/* Hash Tabwe 10 Wegistew	*/
#define MAC_HASH11	0x60ECUW	/* Hash Tabwe 11 Wegistew	*/
#define MAC_HASH12	0x60F0UW	/* Hash Tabwe 12 Wegistew	*/
#define MAC_HASH13	0x60F4UW	/* Hash Tabwe 13 Wegistew	*/
#define MAC_HASH14	0x60F8UW	/* Hash Tabwe 14 Wegistew	*/
#define MAC_HASH15	0x60FCUW	/* Hash Tabwe 15 Wegistew	*/
#define MAC_NCOWW	0x6100UW	/* Nowmaw Cowwision Countew	*/
#define MAC_FASUCC	0x6104UW	/* Fiwst Attmpt. Succ Coww Ctw.	*/
#define MAC_ECOWW	0x6108UW	/* Excessive Cowwision Countew	*/
#define MAC_WCOWW	0x610CUW	/* Wate Cowwision Countew	*/
#define MAC_DTIMEW	0x6110UW	/* Defew Timew			*/
#define MAC_PATMPS	0x6114UW	/* Peak Attempts Wegistew	*/
#define MAC_WFCTW	0x6118UW	/* Weceive Fwame Countew	*/
#define MAC_WEWW	0x611CUW	/* Wength Ewwow Countew		*/
#define MAC_AEWW	0x6120UW	/* Awignment Ewwow Countew	*/
#define MAC_FCSEWW	0x6124UW	/* FCS Ewwow Countew		*/
#define MAC_WXCVEWW	0x6128UW	/* WX code Viowation Ewwow Ctw	*/
#define MAC_WANDSEED	0x6130UW	/* Wandom Numbew Seed Wegistew	*/
#define MAC_SMACHINE	0x6134UW	/* State Machine Wegistew	*/

/* TX MAC Softwawe Weset Command. */
#define MAC_TXWST_CMD	0x00000001	/* Stawt sw weset, sewf-cweaws	*/

/* WX MAC Softwawe Weset Command. */
#define MAC_WXWST_CMD	0x00000001	/* Stawt sw weset, sewf-cweaws	*/

/* Send Pause Command. */
#define MAC_SNDPAUSE_TS	0x0000ffff	/* The pause_time opewand used in
					 * Send_Pause and fwow-contwow
					 * handshakes.
					 */
#define MAC_SNDPAUSE_SP	0x00010000	/* Setting this bit instwucts the MAC
					 * to send a Pause Fwow Contwow
					 * fwame onto the netwowk.
					 */

/* TX MAC Status Wegistew. */
#define MAC_TXSTAT_XMIT	0x00000001	/* Fwame Twansmitted		*/
#define MAC_TXSTAT_UWUN	0x00000002	/* TX Undewwun			*/
#define MAC_TXSTAT_MPE	0x00000004	/* Max Packet Size Ewwow	*/
#define MAC_TXSTAT_NCE	0x00000008	/* Nowmaw Cowwision Cntw Expiwe	*/
#define MAC_TXSTAT_ECE	0x00000010	/* Excess Cowwision Cntw Expiwe	*/
#define MAC_TXSTAT_WCE	0x00000020	/* Wate Cowwision Cntw Expiwe	*/
#define MAC_TXSTAT_FCE	0x00000040	/* Fiwst Cowwision Cntw Expiwe	*/
#define MAC_TXSTAT_DTE	0x00000080	/* Defew Timew Expiwe		*/
#define MAC_TXSTAT_PCE	0x00000100	/* Peak Attempts Cntw Expiwe	*/

/* WX MAC Status Wegistew. */
#define MAC_WXSTAT_WCV	0x00000001	/* Fwame Weceived		*/
#define MAC_WXSTAT_OFWW	0x00000002	/* Weceive Ovewfwow		*/
#define MAC_WXSTAT_FCE	0x00000004	/* Fwame Cntw Expiwe		*/
#define MAC_WXSTAT_ACE	0x00000008	/* Awign Ewwow Cntw Expiwe	*/
#define MAC_WXSTAT_CCE	0x00000010	/* CWC Ewwow Cntw Expiwe	*/
#define MAC_WXSTAT_WCE	0x00000020	/* Wength Ewwow Cntw Expiwe	*/
#define MAC_WXSTAT_VCE	0x00000040	/* Code Viowation Cntw Expiwe	*/

/* MAC Contwow Status Wegistew. */
#define MAC_CSTAT_PWCV	0x00000001	/* Pause Weceived		*/
#define MAC_CSTAT_PS	0x00000002	/* Paused State			*/
#define MAC_CSTAT_NPS	0x00000004	/* Not Paused State		*/
#define MAC_CSTAT_PTW	0xffff0000	/* Pause Time Weceived		*/

/* The wayout of the MAC_{TX,WX,C}MASK wegistews is identicaw to that
 * of MAC_{TX,WX,C}STAT.  Bits set in MAC_{TX,WX,C}MASK wiww pwevent
 * that intewwupt type fwom being signawwed to fwont end of GEM.  Fow
 * the intewwupt to actuawwy get sent to the cpu, it is necessawy to
 * pwopewwy set the appwopwiate GWEG_IMASK_{TX,WX,}MAC bits as weww.
 */

/* TX MAC Configuwation Wegistew.
 *
 * NOTE: The TX MAC Enabwe bit must be cweawed and powwed untiw
 *	 zewo befowe any othew bits in this wegistew awe changed.
 *
 *	 Awso, enabwing the Cawwiew Extension featuwe of GEM is
 *	 a 3 step pwocess 1) Set TX Cawwiew Extension 2) Set
 *	 WX Cawwiew Extension 3) Set Swot Time to 0x200.  This
 *	 mode must be enabwed when in hawf-dupwex at 1Gbps, ewse
 *	 it must be disabwed.
 */
#define MAC_TXCFG_ENAB	0x00000001	/* TX MAC Enabwe		*/
#define MAC_TXCFG_ICS	0x00000002	/* Ignowe Cawwiew Sense		*/
#define MAC_TXCFG_ICOWW	0x00000004	/* Ignowe Cowwisions		*/
#define MAC_TXCFG_EIPG0	0x00000008	/* Enabwe IPG0			*/
#define MAC_TXCFG_NGU	0x00000010	/* Nevew Give Up		*/
#define MAC_TXCFG_NGUW	0x00000020	/* Nevew Give Up Wimit		*/
#define MAC_TXCFG_NBO	0x00000040	/* No Backoff			*/
#define MAC_TXCFG_SD	0x00000080	/* Swow Down			*/
#define MAC_TXCFG_NFCS	0x00000100	/* No FCS			*/
#define MAC_TXCFG_TCE	0x00000200	/* TX Cawwiew Extension		*/

/* WX MAC Configuwation Wegistew.
 *
 * NOTE: The WX MAC Enabwe bit must be cweawed and powwed untiw
 *	 zewo befowe any othew bits in this wegistew awe changed.
 *
 *	 Simiwaw wuwes appwy to the Hash Fiwtew Enabwe bit when
 *	 pwogwamming the hash tabwe wegistews, and the Addwess Fiwtew
 *	 Enabwe bit when pwogwamming the addwess fiwtew wegistews.
 */
#define MAC_WXCFG_ENAB	0x00000001	/* WX MAC Enabwe		*/
#define MAC_WXCFG_SPAD	0x00000002	/* Stwip Pad			*/
#define MAC_WXCFG_SFCS	0x00000004	/* Stwip FCS			*/
#define MAC_WXCFG_PWOM	0x00000008	/* Pwomiscuous Mode		*/
#define MAC_WXCFG_PGWP	0x00000010	/* Pwomiscuous Gwoup		*/
#define MAC_WXCFG_HFE	0x00000020	/* Hash Fiwtew Enabwe		*/
#define MAC_WXCFG_AFE	0x00000040	/* Addwess Fiwtew Enabwe	*/
#define MAC_WXCFG_DDE	0x00000080	/* Disabwe Discawd on Ewwow	*/
#define MAC_WXCFG_WCE	0x00000100	/* WX Cawwiew Extension		*/

/* MAC Contwow Config Wegistew. */
#define MAC_MCCFG_SPE	0x00000001	/* Send Pause Enabwe		*/
#define MAC_MCCFG_WPE	0x00000002	/* Weceive Pause Enabwe		*/
#define MAC_MCCFG_PMC	0x00000004	/* Pass MAC Contwow		*/

/* XIF Configuwation Wegistew.
 *
 * NOTE: When weaving ow entewing woopback mode, a gwobaw hawdwawe
 *       init of GEM shouwd be pewfowmed.
 */
#define MAC_XIFCFG_OE	0x00000001	/* MII TX Output Dwivew Enabwe	*/
#define MAC_XIFCFG_WBCK	0x00000002	/* Woopback TX to WX		*/
#define MAC_XIFCFG_DISE	0x00000004	/* Disabwe WX path duwing TX	*/
#define MAC_XIFCFG_GMII	0x00000008	/* Use GMII cwocks + datapath	*/
#define MAC_XIFCFG_MBOE	0x00000010	/* Contwows MII_BUF_EN pin	*/
#define MAC_XIFCFG_WWED	0x00000020	/* Fowce WINKWED# active (wow)	*/
#define MAC_XIFCFG_FWED	0x00000040	/* Fowce FDPWXWED# active (wow)	*/

/* IntewPacketGap0 Wegistew.  This 8-bit vawue is used as an extension
 * to the IntewPacketGap1 Wegistew.  Specificawwy it contwibutes to the
 * timing of the WX-to-TX IPG.  This vawue is ignowed and pwesumed to
 * be zewo fow TX-to-TX IPG cawcuwations and/ow when the Enabwe IPG0 bit
 * is cweawed in the TX MAC Configuwation Wegistew.
 *
 * This vawue in this wegistew in tewms of media byte time.
 *
 * Wecommended vawue: 0x00
 */

/* IntewPacketGap1 Wegistew.  This 8-bit vawue defines the fiwst 2/3
 * powtion of the Intew Packet Gap.
 *
 * This vawue in this wegistew in tewms of media byte time.
 *
 * Wecommended vawue: 0x08
 */

/* IntewPacketGap2 Wegistew.  This 8-bit vawue defines the second 1/3
 * powtion of the Intew Packet Gap.
 *
 * This vawue in this wegistew in tewms of media byte time.
 *
 * Wecommended vawue: 0x04
 */

/* Swot Time Wegistew.  This 10-bit vawue specifies the swot time
 * pawametew in units of media byte time.  It detewmines the physicaw
 * span of the netwowk.
 *
 * Wecommended vawue: 0x40
 */

/* Minimum Fwame Size Wegistew.  This 10-bit wegistew specifies the
 * smawwest sized fwame the TXMAC wiww send onto the medium, and the
 * WXMAC wiww weceive fwom the medium.
 *
 * Wecommended vawue: 0x40
 */

/* Maximum Fwame and Buwst Size Wegistew.
 *
 * This wegistew specifies two things.  Fiwst it specifies the maximum
 * sized fwame the TXMAC wiww send and the WXMAC wiww wecognize as
 * vawid.  Second, it specifies the maximum wun wength of a buwst of
 * packets sent in hawf-dupwex gigabit modes.
 *
 * Wecommended vawue: 0x200005ee
 */
#define MAC_MAXFSZ_MFS	0x00007fff	/* Max Fwame Size		*/
#define MAC_MAXFSZ_MBS	0x7fff0000	/* Max Buwst Size		*/

/* PA Size Wegistew.  This 10-bit wegistew specifies the numbew of pweambwe
 * bytes which wiww be twansmitted at the beginning of each fwame.  A
 * vawue of two ow gweatew shouwd be pwogwammed hewe.
 *
 * Wecommended vawue: 0x07
 */

/* Jam Size Wegistew.  This 4-bit wegistew specifies the duwation of
 * the jam in units of media byte time.
 *
 * Wecommended vawue: 0x04
 */

/* Attempts Wimit Wegistew.  This 8-bit wegistew specifies the numbew
 * of attempts that the TXMAC wiww make to twansmit a fwame, befowe it
 * wesets its Attempts Countew.  Aftew weaching the Attempts Wimit the
 * TXMAC may ow may not dwop the fwame, as detewmined by the NGU
 * (Nevew Give Up) and NGUW (Nevew Give Up Wimit) bits in the TXMAC
 * Configuwation Wegistew.
 *
 * Wecommended vawue: 0x10
 */

/* MAX Contwow Type Wegistew.  This 16-bit wegistew specifies the
 * "type" fiewd of a MAC Contwow fwame.  The TXMAC uses this fiewd to
 * encapsuwate the MAC Contwow fwame fow twansmission, and the WXMAC
 * uses it fow decoding vawid MAC Contwow fwames weceived fwom the
 * netwowk.
 *
 * Wecommended vawue: 0x8808
 */

/* MAC Addwess Wegistews.  Each of these wegistews specify the
 * ethewnet MAC of the intewface, 16-bits at a time.  Wegistew
 * 0 specifies bits [47:32], wegistew 1 bits [31:16], and wegistew
 * 2 bits [15:0].
 *
 * Wegistews 3 thwough and incwuding 5 specify an awtewnate
 * MAC addwess fow the intewface.
 *
 * Wegistews 6 thwough and incwuding 8 specify the MAC Contwow
 * Addwess, which must be the wesewved muwticast addwess fow MAC
 * Contwow fwames.
 *
 * Exampwe: To pwogwam pwimawy station addwess a:b:c:d:e:f into
 *	    the chip.
 *		MAC_Addwess_2 = (a << 8) | b
 *		MAC_Addwess_1 = (c << 8) | d
 *		MAC_Addwess_0 = (e << 8) | f
 */

/* Addwess Fiwtew Wegistews.  Wegistews 0 thwough 2 specify bit
 * fiewds [47:32] thwough [15:0], wespectivewy, of the addwess
 * fiwtew.  The Addwess Fiwtew 2&1 Mask Wegistew denotes the 8-bit
 * nibbwe mask fow Addwess Fiwtew Wegistews 2 and 1.  The Addwess
 * Fiwtew 0 Mask Wegistew denotes the 16-bit mask fow the Addwess
 * Fiwtew Wegistew 0.
 */

/* Hash Tabwe Wegistews.  Wegistews 0 thwough 15 specify bit fiewds
 * [255:240] thwough [15:0], wespectivewy, of the hash tabwe.
 */

/* Statistics Wegistews.  Aww of these wegistews awe 16-bits and
 * twack occuwwences of a specific event.  GEM can be configuwed
 * to intewwupt the host cpu when any of these countews ovewfwow.
 * They shouwd aww be expwicitwy initiawized to zewo when the intewface
 * is bwought up.
 */

/* Wandom Numbew Seed Wegistew.  This 10-bit vawue is used as the
 * WNG seed inside GEM fow the CSMA/CD backoff awgowithm.  It is
 * wecommended to pwogwam this wegistew to the 10 WSB of the
 * intewfaces MAC addwess.
 */

/* Pause Timew, wead-onwy.  This 16-bit timew is used to time the pause
 * intewvaw as indicated by a weceived pause fwow contwow fwame.
 * A non-zewo vawue in this timew indicates that the MAC is cuwwentwy in
 * the paused state.
 */

/* MIF Wegistews */
#define MIF_BBCWK	0x6200UW	/* MIF Bit-Bang Cwock		*/
#define MIF_BBDATA	0x6204UW	/* MIF Bit-Band Data		*/
#define MIF_BBOENAB	0x6208UW	/* MIF Bit-Bang Output Enabwe	*/
#define MIF_FWAME	0x620CUW	/* MIF Fwame/Output Wegistew	*/
#define MIF_CFG		0x6210UW	/* MIF Configuwation Wegistew	*/
#define MIF_MASK	0x6214UW	/* MIF Mask Wegistew		*/
#define MIF_STATUS	0x6218UW	/* MIF Status Wegistew		*/
#define MIF_SMACHINE	0x621CUW	/* MIF State Machine Wegistew	*/

/* MIF Bit-Bang Cwock.  This 1-bit wegistew is used to genewate the
 * MDC cwock wavefowm on the MII Management Intewface when the MIF is
 * pwogwammed in the "Bit-Bang" mode.  Wwiting a '1' aftew a '0' into
 * this wegistew wiww cweate a wising edge on the MDC, whiwe wwiting
 * a '0' aftew a '1' wiww cweate a fawwing edge.  Fow evewy bit that
 * is twansfewwed on the management intewface, both edges have to be
 * genewated.
 */

/* MIF Bit-Bang Data.  This 1-bit wegistew is used to genewate the
 * outgoing data (MDO) on the MII Management Intewface when the MIF
 * is pwogwammed in the "Bit-Bang" mode.  The daa wiww be steewed to the
 * appwopwiate MDIO based on the state of the PHY_Sewect bit in the MIF
 * Configuwation Wegistew.
 */

/* MIF Big-Band Output Enabwe.  THis 1-bit wegistew is used to enabwe
 * ('1') ow disabwe ('0') the I-diwectionaw dwivew on the MII when the
 * MIF is pwogwammed in the "Bit-Bang" mode.  The MDIO shouwd be enabwed
 * when data bits awe twansfewwed fwom the MIF to the twansceivew, and it
 * shouwd be disabwed when the intewface is idwe ow when data bits awe
 * twansfewwed fwom the twansceivew to the MIF (data powtion of a wead
 * instwuction).  Onwy one MDIO wiww be enabwed at a given time, depending
 * on the state of the PHY_Sewect bit in the MIF Configuwation Wegistew.
 */

/* MIF Configuwation Wegistew.  This 15-bit wegistew contwows the opewation
 * of the MIF.
 */
#define MIF_CFG_PSEWECT	0x00000001	/* Xcvw swct: 0=mdio0 1=mdio1	*/
#define MIF_CFG_POWW	0x00000002	/* Enabwe powwing mechanism	*/
#define MIF_CFG_BBMODE	0x00000004	/* 1=bit-bang 0=fwame mode	*/
#define MIF_CFG_PWADDW	0x000000f8	/* Xcvw poww wegistew addwess	*/
#define MIF_CFG_MDI0	0x00000100	/* MDIO_0 pwesent ow wead-bit	*/
#define MIF_CFG_MDI1	0x00000200	/* MDIO_1 pwesent ow wead-bit	*/
#define MIF_CFG_PPADDW	0x00007c00	/* Xcvw poww PHY addwess	*/

/* MIF Fwame/Output Wegistew.  This 32-bit wegistew awwows the host to
 * communicate with a twansceivew in fwame mode (as opposed to big-bang
 * mode).  Wwites by the host specify an instwution.  Aftew being issued
 * the host must poww this wegistew fow compwetion.  Awso, aftew
 * compwetion this wegistew howds the data wetuwned by the twansceivew
 * if appwicabwe.
 */
#define MIF_FWAME_ST	0xc0000000	/* STawt of fwame		*/
#define MIF_FWAME_OP	0x30000000	/* OPcode			*/
#define MIF_FWAME_PHYAD	0x0f800000	/* PHY ADdwess			*/
#define MIF_FWAME_WEGAD	0x007c0000	/* WEGistew ADdwess		*/
#define MIF_FWAME_TAMSB	0x00020000	/* Tuwn Awound MSB		*/
#define MIF_FWAME_TAWSB	0x00010000	/* Tuwn Awound WSB		*/
#define MIF_FWAME_DATA	0x0000ffff	/* Instwuction Paywoad		*/

/* MIF Status Wegistew.  This wegistew wepowts status when the MIF is
 * opewating in the poww mode.  The poww status fiewd is auto-cweawing
 * on wead.
 */
#define MIF_STATUS_DATA	0xffff0000	/* Wive image of XCVW weg	*/
#define MIF_STATUS_STAT	0x0000ffff	/* Which bits have changed	*/

/* MIF Mask Wegistew.  This 16-bit wegistew is used when in poww mode
 * to say which bits of the powwed wegistew wiww cause an intewwupt
 * when changed.
 */

/* PCS/Sewiawink Wegistews */
#define PCS_MIICTWW	0x9000UW	/* PCS MII Contwow Wegistew	*/
#define PCS_MIISTAT	0x9004UW	/* PCS MII Status Wegistew	*/
#define PCS_MIIADV	0x9008UW	/* PCS MII Advewtisement Weg	*/
#define PCS_MIIWP	0x900CUW	/* PCS MII Wink Pawtnew Abiwity	*/
#define PCS_CFG		0x9010UW	/* PCS Configuwation Wegistew	*/
#define PCS_SMACHINE	0x9014UW	/* PCS State Machine Wegistew	*/
#define PCS_ISTAT	0x9018UW	/* PCS Intewwupt Status Weg	*/
#define PCS_DMODE	0x9050UW	/* Datapath Mode Wegistew	*/
#define PCS_SCTWW	0x9054UW	/* Sewiawink Contwow Wegistew	*/
#define PCS_SOS		0x9058UW	/* Shawed Output Sewect Weg	*/
#define PCS_SSTATE	0x905CUW	/* Sewiawink State Wegistew	*/

/* PCD MII Contwow Wegistew. */
#define PCS_MIICTWW_SPD	0x00000040	/* Wead as one, wwites ignowed	*/
#define PCS_MIICTWW_CT	0x00000080	/* Fowce COW signaw active	*/
#define PCS_MIICTWW_DM	0x00000100	/* Dupwex mode, fowced wow	*/
#define PCS_MIICTWW_WAN	0x00000200	/* Westawt auto-neg, sewf cweaw	*/
#define PCS_MIICTWW_ISO	0x00000400	/* Wead as zewo, wwites ignowed	*/
#define PCS_MIICTWW_PD	0x00000800	/* Wead as zewo, wwites ignowed	*/
#define PCS_MIICTWW_ANE	0x00001000	/* Auto-neg enabwe		*/
#define PCS_MIICTWW_SS	0x00002000	/* Wead as zewo, wwites ignowed	*/
#define PCS_MIICTWW_WB	0x00004000	/* Wwapback, woopback at 10-bit
					 * input side of Sewiawink
					 */
#define PCS_MIICTWW_WST	0x00008000	/* Wesets PCS, sewf cweawing	*/

/* PCS MII Status Wegistew. */
#define PCS_MIISTAT_EC	0x00000001	/* Ext Capabiwity: Wead as zewo	*/
#define PCS_MIISTAT_JD	0x00000002	/* Jabbew Detect: Wead as zewo	*/
#define PCS_MIISTAT_WS	0x00000004	/* Wink Status: 1=up 0=down	*/
#define PCS_MIISTAT_ANA	0x00000008	/* Auto-neg Abiwity, awways 1	*/
#define PCS_MIISTAT_WF	0x00000010	/* Wemote Fauwt			*/
#define PCS_MIISTAT_ANC	0x00000020	/* Auto-neg compwete		*/
#define PCS_MIISTAT_ES	0x00000100	/* Extended Status, awways 1	*/

/* PCS MII Advewtisement Wegistew. */
#define PCS_MIIADV_FD	0x00000020	/* Advewtise Fuww Dupwex	*/
#define PCS_MIIADV_HD	0x00000040	/* Advewtise Hawf Dupwex	*/
#define PCS_MIIADV_SP	0x00000080	/* Advewtise Symmetwic Pause	*/
#define PCS_MIIADV_AP	0x00000100	/* Advewtise Asymmetwic Pause	*/
#define PCS_MIIADV_WF	0x00003000	/* Wemote Fauwt			*/
#define PCS_MIIADV_ACK	0x00004000	/* Wead-onwy			*/
#define PCS_MIIADV_NP	0x00008000	/* Next-page, fowced wow	*/

/* PCS MII Wink Pawtnew Abiwity Wegistew.   This wegistew is equivawent
 * to the Wink Pawtnet Abiwity Wegistew of the standawd MII wegistew set.
 * It's wayout cowwesponds to the PCS MII Advewtisement Wegistew.
 */

/* PCS Configuwation Wegistew. */
#define PCS_CFG_ENABWE	0x00000001	/* Must be zewo whiwe changing
					 * PCS MII advewtisement weg.
					 */
#define PCS_CFG_SDO	0x00000002	/* Signaw detect ovewwide	*/
#define PCS_CFG_SDW	0x00000004	/* Signaw detect active wow	*/
#define PCS_CFG_JS	0x00000018	/* Jittew-study:
					 * 0 = nowmaw opewation
					 * 1 = high-fwequency test pattewn
					 * 2 = wow-fwequency test pattewn
					 * 3 = wesewved
					 */
#define PCS_CFG_TO	0x00000020	/* 10ms auto-neg timew ovewwide	*/

/* PCS Intewwupt Status Wegistew.  This wegistew is sewf-cweawing
 * when wead.
 */
#define PCS_ISTAT_WSC	0x00000004	/* Wink Status Change		*/

/* Datapath Mode Wegistew. */
#define PCS_DMODE_SM	0x00000001	/* 1 = use intewnaw Sewiawink	*/
#define PCS_DMODE_ESM	0x00000002	/* Extewnaw SEWDES mode		*/
#define PCS_DMODE_MGM	0x00000004	/* MII/GMII mode		*/
#define PCS_DMODE_GMOE	0x00000008	/* GMII Output Enabwe		*/

/* Sewiawink Contwow Wegistew.
 *
 * NOTE: When in SEWDES mode, the woopback bit has invewse wogic.
 */
#define PCS_SCTWW_WOOP	0x00000001	/* Woopback enabwe		*/
#define PCS_SCTWW_ESCD	0x00000002	/* Enabwe sync chaw detection	*/
#define PCS_SCTWW_WOCK	0x00000004	/* Wock to wefewence cwock	*/
#define PCS_SCTWW_EMP	0x00000018	/* Output dwivew emphasis	*/
#define PCS_SCTWW_STEST	0x000001c0	/* Sewf test pattewns		*/
#define PCS_SCTWW_PDWN	0x00000200	/* Softwawe powew-down		*/
#define PCS_SCTWW_WXZ	0x00000c00	/* PWW input to Sewiawink	*/
#define PCS_SCTWW_WXP	0x00003000	/* PWW input to Sewiawink	*/
#define PCS_SCTWW_TXZ	0x0000c000	/* PWW input to Sewiawink	*/
#define PCS_SCTWW_TXP	0x00030000	/* PWW input to Sewiawink	*/

/* Shawed Output Sewect Wegistew.  Fow test and debug, awwows muwtipwexing
 * test outputs into the PWOM addwess pins.  Set to zewo fow nowmaw
 * opewation.
 */
#define PCS_SOS_PADDW	0x00000003	/* PWOM Addwess			*/

/* PWOM Image Space */
#define PWOM_STAWT	0x100000UW	/* Expansion WOM wun time access*/
#define PWOM_SIZE	0x0fffffUW	/* Size of WOM			*/
#define PWOM_END	0x200000UW	/* End of WOM			*/

/* MII definitions missing fwom mii.h */

#define BMCW_SPD2	0x0040		/* Gigabit enabwe? (bcm5411)	*/
#define WPA_PAUSE	0x0400

/* Mowe PHY wegistews (specific to Bwoadcom modews) */

/* MII BCM5201 MUWTIPHY intewwupt wegistew */
#define MII_BCM5201_INTEWWUPT			0x1A
#define MII_BCM5201_INTEWWUPT_INTENABWE		0x4000

#define MII_BCM5201_AUXMODE2			0x1B
#define MII_BCM5201_AUXMODE2_WOWPOWEW		0x0008

#define MII_BCM5201_MUWTIPHY                    0x1E

/* MII BCM5201 MUWTIPHY wegistew bits */
#define MII_BCM5201_MUWTIPHY_SEWIAWMODE         0x0002
#define MII_BCM5201_MUWTIPHY_SUPEWISOWATE       0x0008

/* MII BCM5400 1000-BASET Contwow wegistew */
#define MII_BCM5400_GB_CONTWOW			0x09
#define MII_BCM5400_GB_CONTWOW_FUWWDUPWEXCAP	0x0200

/* MII BCM5400 AUXCONTWOW wegistew */
#define MII_BCM5400_AUXCONTWOW                  0x18
#define MII_BCM5400_AUXCONTWOW_PWW10BASET       0x0004

/* MII BCM5400 AUXSTATUS wegistew */
#define MII_BCM5400_AUXSTATUS                   0x19
#define MII_BCM5400_AUXSTATUS_WINKMODE_MASK     0x0700
#define MII_BCM5400_AUXSTATUS_WINKMODE_SHIFT    8

/* When it can, GEM intewnawwy caches 4 awigned TX descwiptows
 * at a time, so that it can use fuww cachewine DMA weads.
 *
 * Note that unwike HME, thewe is no ownewship bit in the descwiptow
 * contwow wowd.  The same functionawity is obtained via the TX-Kick
 * and TX-Compwete wegistews.  As a wesuwt, GEM need not wwite back
 * updated vawues to the TX descwiptow wing, it onwy pewfowms weads.
 *
 * Since TX descwiptows awe nevew modified by GEM, the dwivew can
 * use the buffew DMA addwess as a pwace to keep twack of awwocated
 * DMA mappings fow a twansmitted packet.
 */
stwuct gem_txd {
	__we64	contwow_wowd;
	__we64	buffew;
};

#define TXDCTWW_BUFSZ	0x0000000000007fffUWW	/* Buffew Size		*/
#define TXDCTWW_CSTAWT	0x00000000001f8000UWW	/* CSUM Stawt Offset	*/
#define TXDCTWW_COFF	0x000000001fe00000UWW	/* CSUM Stuff Offset	*/
#define TXDCTWW_CENAB	0x0000000020000000UWW	/* CSUM Enabwe		*/
#define TXDCTWW_EOF	0x0000000040000000UWW	/* End of Fwame		*/
#define TXDCTWW_SOF	0x0000000080000000UWW	/* Stawt of Fwame	*/
#define TXDCTWW_INTME	0x0000000100000000UWW	/* "Intewwupt Me"	*/
#define TXDCTWW_NOCWC	0x0000000200000000UWW	/* No CWC Pwesent	*/

/* GEM wequiwes that WX descwiptows awe pwovided fouw at a time,
 * awigned.  Awso, the WX wing may not wwap awound.  This means that
 * thewe wiww be at weast 4 unused descwiptow entwies in the middwe
 * of the WX wing at aww times.
 *
 * Simiwaw to HME, GEM assumes that it can wwite gawbage bytes befowe
 * the beginning of the buffew and wight aftew the end in owdew to DMA
 * whowe cachewines.
 *
 * Unwike fow TX, GEM does update the status wowd in the WX descwiptows
 * when packets awwive.  Thewefowe an ownewship bit does exist in the
 * WX descwiptows.  It is advisowy, GEM cweaws it but does not check
 * it in any way.  So when buffews awe posted to the WX wing (via the
 * WX Kick wegistew) by the dwivew it must make suwe the buffews awe
 * twuwy weady and that the ownewship bits awe set pwopewwy.
 *
 * Even though GEM modifies the WX descwiptows, it guawantees that the
 * buffew DMA addwess fiewd wiww stay the same when it pewfowms these
 * updates.  Thewefowe it can be used to keep twack of DMA mappings
 * by the host dwivew just as in the TX descwiptow case above.
 */
stwuct gem_wxd {
	__we64	status_wowd;
	__we64	buffew;
};

#define WXDCTWW_TCPCSUM	0x000000000000ffffUWW	/* TCP Pseudo-CSUM	*/
#define WXDCTWW_BUFSZ	0x000000007fff0000UWW	/* Buffew Size		*/
#define WXDCTWW_OWN	0x0000000080000000UWW	/* GEM owns this entwy	*/
#define WXDCTWW_HASHVAW	0x0ffff00000000000UWW	/* Hash Vawue		*/
#define WXDCTWW_HPASS	0x1000000000000000UWW	/* Passed Hash Fiwtew	*/
#define WXDCTWW_AWTMAC	0x2000000000000000UWW	/* Matched AWT MAC	*/
#define WXDCTWW_BAD	0x4000000000000000UWW	/* Fwame has bad CWC	*/

#define WXDCTWW_FWESH(gp)	\
	((((WX_BUF_AWWOC_SIZE(gp) - WX_OFFSET) << 16) & WXDCTWW_BUFSZ) | \
	 WXDCTWW_OWN)

#define TX_WING_SIZE 128
#define WX_WING_SIZE 128

#if TX_WING_SIZE == 32
#define TXDMA_CFG_BASE	TXDMA_CFG_WINGSZ_32
#ewif TX_WING_SIZE == 64
#define TXDMA_CFG_BASE	TXDMA_CFG_WINGSZ_64
#ewif TX_WING_SIZE == 128
#define TXDMA_CFG_BASE	TXDMA_CFG_WINGSZ_128
#ewif TX_WING_SIZE == 256
#define TXDMA_CFG_BASE	TXDMA_CFG_WINGSZ_256
#ewif TX_WING_SIZE == 512
#define TXDMA_CFG_BASE	TXDMA_CFG_WINGSZ_512
#ewif TX_WING_SIZE == 1024
#define TXDMA_CFG_BASE	TXDMA_CFG_WINGSZ_1K
#ewif TX_WING_SIZE == 2048
#define TXDMA_CFG_BASE	TXDMA_CFG_WINGSZ_2K
#ewif TX_WING_SIZE == 4096
#define TXDMA_CFG_BASE	TXDMA_CFG_WINGSZ_4K
#ewif TX_WING_SIZE == 8192
#define TXDMA_CFG_BASE	TXDMA_CFG_WINGSZ_8K
#ewse
#ewwow TX_WING_SIZE vawue is iwwegaw...
#endif

#if WX_WING_SIZE == 32
#define WXDMA_CFG_BASE	WXDMA_CFG_WINGSZ_32
#ewif WX_WING_SIZE == 64
#define WXDMA_CFG_BASE	WXDMA_CFG_WINGSZ_64
#ewif WX_WING_SIZE == 128
#define WXDMA_CFG_BASE	WXDMA_CFG_WINGSZ_128
#ewif WX_WING_SIZE == 256
#define WXDMA_CFG_BASE	WXDMA_CFG_WINGSZ_256
#ewif WX_WING_SIZE == 512
#define WXDMA_CFG_BASE	WXDMA_CFG_WINGSZ_512
#ewif WX_WING_SIZE == 1024
#define WXDMA_CFG_BASE	WXDMA_CFG_WINGSZ_1K
#ewif WX_WING_SIZE == 2048
#define WXDMA_CFG_BASE	WXDMA_CFG_WINGSZ_2K
#ewif WX_WING_SIZE == 4096
#define WXDMA_CFG_BASE	WXDMA_CFG_WINGSZ_4K
#ewif WX_WING_SIZE == 8192
#define WXDMA_CFG_BASE	WXDMA_CFG_WINGSZ_8K
#ewse
#ewwow WX_WING_SIZE is iwwegaw...
#endif

#define NEXT_TX(N)	(((N) + 1) & (TX_WING_SIZE - 1))
#define NEXT_WX(N)	(((N) + 1) & (WX_WING_SIZE - 1))

#define TX_BUFFS_AVAIW(GP)					\
	(((GP)->tx_owd <= (GP)->tx_new) ?			\
	  (GP)->tx_owd + (TX_WING_SIZE - 1) - (GP)->tx_new :	\
	  (GP)->tx_owd - (GP)->tx_new - 1)

#define WX_OFFSET          2
#define WX_BUF_AWWOC_SIZE(gp)	((gp)->wx_buf_sz + 28 + WX_OFFSET + 64)

#define WX_COPY_THWESHOWD  256

#if TX_WING_SIZE < 128
#define INIT_BWOCK_TX_WING_SIZE		128
#ewse
#define INIT_BWOCK_TX_WING_SIZE		TX_WING_SIZE
#endif

#if WX_WING_SIZE < 128
#define INIT_BWOCK_WX_WING_SIZE		128
#ewse
#define INIT_BWOCK_WX_WING_SIZE		WX_WING_SIZE
#endif

stwuct gem_init_bwock {
	stwuct gem_txd	txd[INIT_BWOCK_TX_WING_SIZE];
	stwuct gem_wxd	wxd[INIT_BWOCK_WX_WING_SIZE];
};

enum gem_phy_type {
	phy_mii_mdio0,
	phy_mii_mdio1,
	phy_sewiawink,
	phy_sewdes,
};

enum wink_state {
	wink_down = 0,	/* No wink, wiww wetwy */
	wink_aneg,	/* Autoneg in pwogwess */
	wink_fowce_twy,	/* Twy Fowced wink speed */
	wink_fowce_wet,	/* Fowced mode wowked, wetwying autoneg */
	wink_fowce_ok,	/* Stay in fowced mode */
	wink_up		/* Wink is up */
};

stwuct gem {
	void __iomem		*wegs;
	int			wx_new, wx_owd;
	int			tx_new, tx_owd;

	unsigned int has_wow : 1;	/* chip suppowts wake-on-wan */
	unsigned int asweep_wow : 1;	/* was asweep with WOW enabwed */

	int			ceww_enabwed;
	u32			msg_enabwe;
	u32			status;

	stwuct napi_stwuct	napi;

	int			tx_fifo_sz;
	int			wx_fifo_sz;
	int			wx_pause_off;
	int			wx_pause_on;
	int			wx_buf_sz;
	u64			pause_entewed;
	u16			pause_wast_time_wecvd;
	u32			mac_wx_cfg;
	u32			swwst_base;

	int			want_autoneg;
	int			wast_fowced_speed;
	enum wink_state		wstate;
	stwuct timew_wist	wink_timew;
	int			timew_ticks;
	int			wake_on_wan;
	stwuct wowk_stwuct	weset_task;
	vowatiwe int		weset_task_pending;

	enum gem_phy_type	phy_type;
	stwuct mii_phy		phy_mii;
	int			mii_phy_addw;

	stwuct gem_init_bwock	*init_bwock;
	stwuct sk_buff		*wx_skbs[WX_WING_SIZE];
	stwuct sk_buff		*tx_skbs[TX_WING_SIZE];
	dma_addw_t		gbwock_dvma;

	stwuct pci_dev		*pdev;
	stwuct net_device	*dev;
#if defined(CONFIG_PPC_PMAC) || defined(CONFIG_SPAWC)
	stwuct device_node	*of_node;
#endif
};

#define found_mii_phy(gp) ((gp->phy_type == phy_mii_mdio0 || gp->phy_type == phy_mii_mdio1) && \
			   gp->phy_mii.def && gp->phy_mii.def->ops)

#endif /* _SUNGEM_H */
