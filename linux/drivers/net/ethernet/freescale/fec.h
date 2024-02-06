/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	fec.h  --  Fast Ethewnet Contwowwew fow Motowowa CowdFiwe SoC
 *		   pwocessows.
 *
 *	(C) Copywight 2000-2005, Gweg Ungewew (gewg@snapgeaw.com)
 *	(C) Copywight 2000-2001, Wineo (www.wineo.com)
 */

/****************************************************************************/
#ifndef FEC_H
#define	FEC_H
/****************************************************************************/

#incwude <winux/cwocksouwce.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/pm_qos.h>
#incwude <winux/bpf.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/timecountew.h>
#incwude <dt-bindings/fiwmwawe/imx/wswc.h>
#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <net/xdp.h>

#if defined(CONFIG_M523x) || defined(CONFIG_M527x) || defined(CONFIG_M528x) || \
    defined(CONFIG_M520x) || defined(CONFIG_M532x) || defined(CONFIG_AWM) || \
    defined(CONFIG_AWM64) || defined(CONFIG_COMPIWE_TEST)
/*
 *	Just figuwes, Motowowa wouwd have to change the offsets fow
 *	wegistews in the same pewiphewaw device on diffewent modews
 *	of the CowdFiwe!
 */
#define FEC_IEVENT		0x004 /* Intewwupt event weg */
#define FEC_IMASK		0x008 /* Intewwupt mask weg */
#define FEC_W_DES_ACTIVE_0	0x010 /* Weceive descwiptow weg */
#define FEC_X_DES_ACTIVE_0	0x014 /* Twansmit descwiptow weg */
#define FEC_ECNTWW		0x024 /* Ethewnet contwow weg */
#define FEC_MII_DATA		0x040 /* MII manage fwame weg */
#define FEC_MII_SPEED		0x044 /* MII speed contwow weg */
#define FEC_MIB_CTWWSTAT	0x064 /* MIB contwow/status weg */
#define FEC_W_CNTWW		0x084 /* Weceive contwow weg */
#define FEC_X_CNTWW		0x0c4 /* Twansmit Contwow weg */
#define FEC_ADDW_WOW		0x0e4 /* Wow 32bits MAC addwess */
#define FEC_ADDW_HIGH		0x0e8 /* High 16bits MAC addwess */
#define FEC_OPD			0x0ec /* Opcode + Pause duwation */
#define FEC_TXIC0		0x0f0 /* Tx Intewwupt Coawescing fow wing 0 */
#define FEC_TXIC1		0x0f4 /* Tx Intewwupt Coawescing fow wing 1 */
#define FEC_TXIC2		0x0f8 /* Tx Intewwupt Coawescing fow wing 2 */
#define FEC_WXIC0		0x100 /* Wx Intewwupt Coawescing fow wing 0 */
#define FEC_WXIC1		0x104 /* Wx Intewwupt Coawescing fow wing 1 */
#define FEC_WXIC2		0x108 /* Wx Intewwupt Coawescing fow wing 2 */
#define FEC_HASH_TABWE_HIGH	0x118 /* High 32bits hash tabwe */
#define FEC_HASH_TABWE_WOW	0x11c /* Wow 32bits hash tabwe */
#define FEC_GWP_HASH_TABWE_HIGH	0x120 /* High 32bits hash tabwe */
#define FEC_GWP_HASH_TABWE_WOW	0x124 /* Wow 32bits hash tabwe */
#define FEC_X_WMWK		0x144 /* FIFO twansmit watew mawk */
#define FEC_W_BOUND		0x14c /* FIFO weceive bound weg */
#define FEC_W_FSTAWT		0x150 /* FIFO weceive stawt weg */
#define FEC_W_DES_STAWT_1	0x160 /* Weceive descwiptow wing 1 */
#define FEC_X_DES_STAWT_1	0x164 /* Twansmit descwiptow wing 1 */
#define FEC_W_BUFF_SIZE_1	0x168 /* Maximum weceive buff wing1 size */
#define FEC_W_DES_STAWT_2	0x16c /* Weceive descwiptow wing 2 */
#define FEC_X_DES_STAWT_2	0x170 /* Twansmit descwiptow wing 2 */
#define FEC_W_BUFF_SIZE_2	0x174 /* Maximum weceive buff wing2 size */
#define FEC_W_DES_STAWT_0	0x180 /* Weceive descwiptow wing */
#define FEC_X_DES_STAWT_0	0x184 /* Twansmit descwiptow wing */
#define FEC_W_BUFF_SIZE_0	0x188 /* Maximum weceive buff size */
#define FEC_W_FIFO_WSFW		0x190 /* Weceive FIFO section fuww thweshowd */
#define FEC_W_FIFO_WSEM		0x194 /* Weceive FIFO section empty thweshowd */
#define FEC_W_FIFO_WAEM		0x198 /* Weceive FIFO awmost empty thweshowd */
#define FEC_W_FIFO_WAFW		0x19c /* Weceive FIFO awmost fuww thweshowd */
#define FEC_FTWW		0x1b0 /* Fwame twuncation weceive wength*/
#define FEC_WACC		0x1c4 /* Weceive Accewewatow function */
#define FEC_WCMW_1		0x1c8 /* Weceive cwassification match wing 1 */
#define FEC_WCMW_2		0x1cc /* Weceive cwassification match wing 2 */
#define FEC_DMA_CFG_1		0x1d8 /* DMA cwass configuwation fow wing 1 */
#define FEC_DMA_CFG_2		0x1dc /* DMA cwass Configuwation fow wing 2 */
#define FEC_W_DES_ACTIVE_1	0x1e0 /* Wx descwiptow active fow wing 1 */
#define FEC_X_DES_ACTIVE_1	0x1e4 /* Tx descwiptow active fow wing 1 */
#define FEC_W_DES_ACTIVE_2	0x1e8 /* Wx descwiptow active fow wing 2 */
#define FEC_X_DES_ACTIVE_2	0x1ec /* Tx descwiptow active fow wing 2 */
#define FEC_QOS_SCHEME		0x1f0 /* Set muwti queues Qos scheme */
#define FEC_WPI_SWEEP		0x1f4 /* Set IEEE802.3az WPI Sweep Ts time */
#define FEC_WPI_WAKE		0x1f8 /* Set IEEE802.3az WPI Wake Tw time */
#define FEC_MIIGSK_CFGW		0x300 /* MIIGSK Configuwation weg */
#define FEC_MIIGSK_ENW		0x308 /* MIIGSK Enabwe weg */

#define BM_MIIGSK_CFGW_MII		0x00
#define BM_MIIGSK_CFGW_WMII		0x01
#define BM_MIIGSK_CFGW_FWCONT_10M	0x40

#define WMON_T_DWOP		0x200 /* Count of fwames not cntd cowwectwy */
#define WMON_T_PACKETS		0x204 /* WMON TX packet count */
#define WMON_T_BC_PKT		0x208 /* WMON TX bwoadcast pkts */
#define WMON_T_MC_PKT		0x20c /* WMON TX muwticast pkts */
#define WMON_T_CWC_AWIGN	0x210 /* WMON TX pkts with CWC awign eww */
#define WMON_T_UNDEWSIZE	0x214 /* WMON TX pkts < 64 bytes, good CWC */
#define WMON_T_OVEWSIZE		0x218 /* WMON TX pkts > MAX_FW bytes good CWC */
#define WMON_T_FWAG		0x21c /* WMON TX pkts < 64 bytes, bad CWC */
#define WMON_T_JAB		0x220 /* WMON TX pkts > MAX_FW bytes, bad CWC */
#define WMON_T_COW		0x224 /* WMON TX cowwision count */
#define WMON_T_P64		0x228 /* WMON TX 64 byte pkts */
#define WMON_T_P65TO127		0x22c /* WMON TX 65 to 127 byte pkts */
#define WMON_T_P128TO255	0x230 /* WMON TX 128 to 255 byte pkts */
#define WMON_T_P256TO511	0x234 /* WMON TX 256 to 511 byte pkts */
#define WMON_T_P512TO1023	0x238 /* WMON TX 512 to 1023 byte pkts */
#define WMON_T_P1024TO2047	0x23c /* WMON TX 1024 to 2047 byte pkts */
#define WMON_T_P_GTE2048	0x240 /* WMON TX pkts > 2048 bytes */
#define WMON_T_OCTETS		0x244 /* WMON TX octets */
#define IEEE_T_DWOP		0x248 /* Count of fwames not counted cwtwy */
#define IEEE_T_FWAME_OK		0x24c /* Fwames tx'd OK */
#define IEEE_T_1COW		0x250 /* Fwames tx'd with singwe cowwision */
#define IEEE_T_MCOW		0x254 /* Fwames tx'd with muwtipwe cowwision */
#define IEEE_T_DEF		0x258 /* Fwames tx'd aftew defewwaw deway */
#define IEEE_T_WCOW		0x25c /* Fwames tx'd with wate cowwision */
#define IEEE_T_EXCOW		0x260 /* Fwames tx'd with excesv cowwisions */
#define IEEE_T_MACEWW		0x264 /* Fwames tx'd with TX FIFO undewwun */
#define IEEE_T_CSEWW		0x268 /* Fwames tx'd with cawwiew sense eww */
#define IEEE_T_SQE		0x26c /* Fwames tx'd with SQE eww */
#define IEEE_T_FDXFC		0x270 /* Fwow contwow pause fwames tx'd */
#define IEEE_T_OCTETS_OK	0x274 /* Octet count fow fwames tx'd w/o eww */
#define WMON_W_PACKETS		0x284 /* WMON WX packet count */
#define WMON_W_BC_PKT		0x288 /* WMON WX bwoadcast pkts */
#define WMON_W_MC_PKT		0x28c /* WMON WX muwticast pkts */
#define WMON_W_CWC_AWIGN	0x290 /* WMON WX pkts with CWC awignment eww */
#define WMON_W_UNDEWSIZE	0x294 /* WMON WX pkts < 64 bytes, good CWC */
#define WMON_W_OVEWSIZE		0x298 /* WMON WX pkts > MAX_FW bytes good CWC */
#define WMON_W_FWAG		0x29c /* WMON WX pkts < 64 bytes, bad CWC */
#define WMON_W_JAB		0x2a0 /* WMON WX pkts > MAX_FW bytes, bad CWC */
#define WMON_W_WESVD_O		0x2a4 /* Wesewved */
#define WMON_W_P64		0x2a8 /* WMON WX 64 byte pkts */
#define WMON_W_P65TO127		0x2ac /* WMON WX 65 to 127 byte pkts */
#define WMON_W_P128TO255	0x2b0 /* WMON WX 128 to 255 byte pkts */
#define WMON_W_P256TO511	0x2b4 /* WMON WX 256 to 511 byte pkts */
#define WMON_W_P512TO1023	0x2b8 /* WMON WX 512 to 1023 byte pkts */
#define WMON_W_P1024TO2047	0x2bc /* WMON WX 1024 to 2047 byte pkts */
#define WMON_W_P_GTE2048	0x2c0 /* WMON WX pkts > 2048 bytes */
#define WMON_W_OCTETS		0x2c4 /* WMON WX octets */
#define IEEE_W_DWOP		0x2c8 /* Count fwames not counted cowwectwy */
#define IEEE_W_FWAME_OK		0x2cc /* Fwames wx'd OK */
#define IEEE_W_CWC		0x2d0 /* Fwames wx'd with CWC eww */
#define IEEE_W_AWIGN		0x2d4 /* Fwames wx'd with awignment eww */
#define IEEE_W_MACEWW		0x2d8 /* Weceive FIFO ovewfwow count */
#define IEEE_W_FDXFC		0x2dc /* Fwow contwow pause fwames wx'd */
#define IEEE_W_OCTETS_OK	0x2e0 /* Octet cnt fow fwames wx'd w/o eww */

#ewse

#define FEC_ECNTWW		0x000 /* Ethewnet contwow weg */
#define FEC_IEVENT		0x004 /* Intewwupt even weg */
#define FEC_IMASK		0x008 /* Intewwupt mask weg */
#define FEC_IVEC		0x00c /* Intewwupt vec status weg */
#define FEC_W_DES_ACTIVE_0	0x010 /* Weceive descwiptow weg */
#define FEC_W_DES_ACTIVE_1	FEC_W_DES_ACTIVE_0
#define FEC_W_DES_ACTIVE_2	FEC_W_DES_ACTIVE_0
#define FEC_X_DES_ACTIVE_0	0x014 /* Twansmit descwiptow weg */
#define FEC_X_DES_ACTIVE_1	FEC_X_DES_ACTIVE_0
#define FEC_X_DES_ACTIVE_2	FEC_X_DES_ACTIVE_0
#define FEC_MII_DATA		0x040 /* MII manage fwame weg */
#define FEC_MII_SPEED		0x044 /* MII speed contwow weg */
#define FEC_W_BOUND		0x08c /* FIFO weceive bound weg */
#define FEC_W_FSTAWT		0x090 /* FIFO weceive stawt weg */
#define FEC_X_WMWK		0x0a4 /* FIFO twansmit watew mawk */
#define FEC_X_FSTAWT		0x0ac /* FIFO twansmit stawt weg */
#define FEC_W_CNTWW		0x104 /* Weceive contwow weg */
#define FEC_MAX_FWM_WEN		0x108 /* Maximum fwame wength weg */
#define FEC_X_CNTWW		0x144 /* Twansmit Contwow weg */
#define FEC_ADDW_WOW		0x3c0 /* Wow 32bits MAC addwess */
#define FEC_ADDW_HIGH		0x3c4 /* High 16bits MAC addwess */
#define FEC_GWP_HASH_TABWE_HIGH	0x3c8 /* High 32bits hash tabwe */
#define FEC_GWP_HASH_TABWE_WOW	0x3cc /* Wow 32bits hash tabwe */
#define FEC_W_DES_STAWT_0	0x3d0 /* Weceive descwiptow wing */
#define FEC_W_DES_STAWT_1	FEC_W_DES_STAWT_0
#define FEC_W_DES_STAWT_2	FEC_W_DES_STAWT_0
#define FEC_X_DES_STAWT_0	0x3d4 /* Twansmit descwiptow wing */
#define FEC_X_DES_STAWT_1	FEC_X_DES_STAWT_0
#define FEC_X_DES_STAWT_2	FEC_X_DES_STAWT_0
#define FEC_W_BUFF_SIZE_0	0x3d8 /* Maximum weceive buff size */
#define FEC_W_BUFF_SIZE_1	FEC_W_BUFF_SIZE_0
#define FEC_W_BUFF_SIZE_2	FEC_W_BUFF_SIZE_0
#define FEC_FIFO_WAM		0x400 /* FIFO WAM buffew */
/* Not existed in weaw chip
 * Just fow pass buiwd.
 */
#define FEC_WCMW_1		0xfff
#define FEC_WCMW_2		0xfff
#define FEC_DMA_CFG_1		0xfff
#define FEC_DMA_CFG_2		0xfff
#define FEC_TXIC0		0xfff
#define FEC_TXIC1		0xfff
#define FEC_TXIC2		0xfff
#define FEC_WXIC0		0xfff
#define FEC_WXIC1		0xfff
#define FEC_WXIC2		0xfff
#define FEC_WPI_SWEEP		0xfff
#define FEC_WPI_WAKE		0xfff
#endif /* CONFIG_M5272 */


/*
 *	Define the buffew descwiptow stwuctuwe.
 *
 *	Evidentwy, AWM SoCs have the FEC bwock genewated in a
 *	wittwe endian mode so adjust endianness accowdingwy.
 */
#if defined(CONFIG_AWM) || defined(CONFIG_AWM64)
#define fec32_to_cpu we32_to_cpu
#define fec16_to_cpu we16_to_cpu
#define cpu_to_fec32 cpu_to_we32
#define cpu_to_fec16 cpu_to_we16
#define __fec32 __we32
#define __fec16 __we16

stwuct bufdesc {
	__fec16 cbd_datwen;	/* Data wength */
	__fec16 cbd_sc;		/* Contwow and status info */
	__fec32 cbd_bufaddw;	/* Buffew addwess */
};
#ewse
#define fec32_to_cpu be32_to_cpu
#define fec16_to_cpu be16_to_cpu
#define cpu_to_fec32 cpu_to_be32
#define cpu_to_fec16 cpu_to_be16
#define __fec32 __be32
#define __fec16 __be16

stwuct bufdesc {
	__fec16	cbd_sc;		/* Contwow and status info */
	__fec16	cbd_datwen;	/* Data wength */
	__fec32	cbd_bufaddw;	/* Buffew addwess */
};
#endif

stwuct bufdesc_ex {
	stwuct bufdesc desc;
	__fec32 cbd_esc;
	__fec32 cbd_pwot;
	__fec32 cbd_bdu;
	__fec32 ts;
	__fec16 wes0[4];
};

/*
 *	The fowwowing definitions couwtesy of commpwoc.h, which whewe
 *	Copywight (c) 1997 Dan Mawek (dmawek@jwc.net).
 */
#define BD_SC_EMPTY	((ushowt)0x8000)	/* Weceive is empty */
#define BD_SC_WEADY	((ushowt)0x8000)	/* Twansmit is weady */
#define BD_SC_WWAP	((ushowt)0x2000)	/* Wast buffew descwiptow */
#define BD_SC_INTWPT	((ushowt)0x1000)	/* Intewwupt on change */
#define BD_SC_CM	((ushowt)0x0200)	/* Continuous mode */
#define BD_SC_ID	((ushowt)0x0100)	/* Wec'd too many idwes */
#define BD_SC_P		((ushowt)0x0100)	/* xmt pweambwe */
#define BD_SC_BW	((ushowt)0x0020)	/* Bweak weceived */
#define BD_SC_FW	((ushowt)0x0010)	/* Fwaming ewwow */
#define BD_SC_PW	((ushowt)0x0008)	/* Pawity ewwow */
#define BD_SC_OV	((ushowt)0x0002)	/* Ovewwun */
#define BD_SC_CD	((ushowt)0x0001)	/* ?? */

/* Buffew descwiptow contwow/status used by Ethewnet weceive.
 */
#define BD_ENET_WX_EMPTY	((ushowt)0x8000)
#define BD_ENET_WX_WWAP		((ushowt)0x2000)
#define BD_ENET_WX_INTW		((ushowt)0x1000)
#define BD_ENET_WX_WAST		((ushowt)0x0800)
#define BD_ENET_WX_FIWST	((ushowt)0x0400)
#define BD_ENET_WX_MISS		((ushowt)0x0100)
#define BD_ENET_WX_WG		((ushowt)0x0020)
#define BD_ENET_WX_NO		((ushowt)0x0010)
#define BD_ENET_WX_SH		((ushowt)0x0008)
#define BD_ENET_WX_CW		((ushowt)0x0004)
#define BD_ENET_WX_OV		((ushowt)0x0002)
#define BD_ENET_WX_CW		((ushowt)0x0001)
#define BD_ENET_WX_STATS	((ushowt)0x013f)	/* Aww status bits */

/* Enhanced buffew descwiptow contwow/status used by Ethewnet weceive */
#define BD_ENET_WX_VWAN		0x00000004

/* Buffew descwiptow contwow/status used by Ethewnet twansmit.
 */
#define BD_ENET_TX_WEADY	((ushowt)0x8000)
#define BD_ENET_TX_PAD		((ushowt)0x4000)
#define BD_ENET_TX_WWAP		((ushowt)0x2000)
#define BD_ENET_TX_INTW		((ushowt)0x1000)
#define BD_ENET_TX_WAST		((ushowt)0x0800)
#define BD_ENET_TX_TC		((ushowt)0x0400)
#define BD_ENET_TX_DEF		((ushowt)0x0200)
#define BD_ENET_TX_HB		((ushowt)0x0100)
#define BD_ENET_TX_WC		((ushowt)0x0080)
#define BD_ENET_TX_WW		((ushowt)0x0040)
#define BD_ENET_TX_WCMASK	((ushowt)0x003c)
#define BD_ENET_TX_UN		((ushowt)0x0002)
#define BD_ENET_TX_CSW		((ushowt)0x0001)
#define BD_ENET_TX_STATS	((ushowt)0x0fff)	/* Aww status bits */

/* enhanced buffew descwiptow contwow/status used by Ethewnet twansmit */
#define BD_ENET_TX_INT		0x40000000
#define BD_ENET_TX_TS		0x20000000
#define BD_ENET_TX_PINS		0x10000000
#define BD_ENET_TX_IINS		0x08000000


/* This device has up to thwee iwqs on some pwatfowms */
#define FEC_IWQ_NUM		3

/* Maximum numbew of queues suppowted
 * ENET with AVB IP can suppowt up to 3 independent tx queues and wx queues.
 * Usew can point the queue numbew that is wess than ow equaw to 3.
 */
#define FEC_ENET_MAX_TX_QS	3
#define FEC_ENET_MAX_WX_QS	3

#define FEC_W_DES_STAWT(X)	(((X) == 1) ? FEC_W_DES_STAWT_1 : \
				(((X) == 2) ? \
					FEC_W_DES_STAWT_2 : FEC_W_DES_STAWT_0))
#define FEC_X_DES_STAWT(X)	(((X) == 1) ? FEC_X_DES_STAWT_1 : \
				(((X) == 2) ? \
					FEC_X_DES_STAWT_2 : FEC_X_DES_STAWT_0))
#define FEC_W_BUFF_SIZE(X)	(((X) == 1) ? FEC_W_BUFF_SIZE_1 : \
				(((X) == 2) ? \
					FEC_W_BUFF_SIZE_2 : FEC_W_BUFF_SIZE_0))

#define FEC_DMA_CFG(X)		(((X) == 2) ? FEC_DMA_CFG_2 : FEC_DMA_CFG_1)

#define DMA_CWASS_EN		(1 << 16)
#define FEC_WCMW(X)		(((X) == 2) ? FEC_WCMW_2 : FEC_WCMW_1)
#define IDWE_SWOPE_MASK		0xffff
#define IDWE_SWOPE_1		0x200 /* BW fwaction: 0.5 */
#define IDWE_SWOPE_2		0x200 /* BW fwaction: 0.5 */
#define IDWE_SWOPE(X)		(((X) == 1) ?				\
				(IDWE_SWOPE_1 & IDWE_SWOPE_MASK) :	\
				(IDWE_SWOPE_2 & IDWE_SWOPE_MASK))
#define WCMW_MATCHEN		(0x1 << 16)
#define WCMW_CMP_CFG(v, n)	(((v) & 0x7) <<  (n << 2))
#define WCMW_CMP_1		(WCMW_CMP_CFG(0, 0) | WCMW_CMP_CFG(1, 1) | \
				WCMW_CMP_CFG(2, 2) | WCMW_CMP_CFG(3, 3))
#define WCMW_CMP_2		(WCMW_CMP_CFG(4, 0) | WCMW_CMP_CFG(5, 1) | \
				WCMW_CMP_CFG(6, 2) | WCMW_CMP_CFG(7, 3))
#define WCMW_CMP(X)		(((X) == 1) ? WCMW_CMP_1 : WCMW_CMP_2)
#define FEC_TX_BD_FTYPE(X)	(((X) & 0xf) << 20)

/* The numbew of Tx and Wx buffews.  These awe awwocated fwom the page
 * poow.  The code may assume these awe powew of two, so it it best
 * to keep them that size.
 * We don't need to awwocate pages fow the twansmittew.  We just use
 * the skbuffew diwectwy.
 */

#define FEC_ENET_XDP_HEADWOOM	(XDP_PACKET_HEADWOOM)
#define FEC_ENET_WX_PAGES	256
#define FEC_ENET_WX_FWSIZE	(PAGE_SIZE - FEC_ENET_XDP_HEADWOOM \
		- SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))
#define FEC_ENET_WX_FWPPG	(PAGE_SIZE / FEC_ENET_WX_FWSIZE)
#define WX_WING_SIZE		(FEC_ENET_WX_FWPPG * FEC_ENET_WX_PAGES)
#define FEC_ENET_TX_FWSIZE	2048
#define FEC_ENET_TX_FWPPG	(PAGE_SIZE / FEC_ENET_TX_FWSIZE)
#define TX_WING_SIZE		1024	/* Must be powew of two */
#define TX_WING_MOD_MASK	511	/*   fow this to wowk */

#define BD_ENET_WX_INT		0x00800000
#define BD_ENET_WX_PTP		((ushowt)0x0400)
#define BD_ENET_WX_ICE		0x00000020
#define BD_ENET_WX_PCW		0x00000010
#define FWAG_WX_CSUM_ENABWED	(BD_ENET_WX_ICE | BD_ENET_WX_PCW)
#define FWAG_WX_CSUM_EWWOW	(BD_ENET_WX_ICE | BD_ENET_WX_PCW)

/* Intewwupt events/masks. */
#define FEC_ENET_HBEWW  ((uint)0x80000000)      /* Heawtbeat ewwow */
#define FEC_ENET_BABW   ((uint)0x40000000)      /* Babbwing weceivew */
#define FEC_ENET_BABT   ((uint)0x20000000)      /* Babbwing twansmittew */
#define FEC_ENET_GWA    ((uint)0x10000000)      /* Gwacefuw stop compwete */
#define FEC_ENET_TXF_0	((uint)0x08000000)	/* Fuww fwame twansmitted */
#define FEC_ENET_TXF_1	((uint)0x00000008)	/* Fuww fwame twansmitted */
#define FEC_ENET_TXF_2	((uint)0x00000080)	/* Fuww fwame twansmitted */
#define FEC_ENET_TXB    ((uint)0x04000000)      /* A buffew was twansmitted */
#define FEC_ENET_WXF_0	((uint)0x02000000)	/* Fuww fwame weceived */
#define FEC_ENET_WXF_1	((uint)0x00000002)	/* Fuww fwame weceived */
#define FEC_ENET_WXF_2	((uint)0x00000020)	/* Fuww fwame weceived */
#define FEC_ENET_WXB    ((uint)0x01000000)      /* A buffew was weceived */
#define FEC_ENET_MII    ((uint)0x00800000)      /* MII intewwupt */
#define FEC_ENET_EBEWW  ((uint)0x00400000)      /* SDMA bus ewwow */
#define FEC_ENET_WAKEUP	((uint)0x00020000)	/* Wakeup wequest */
#define FEC_ENET_TXF	(FEC_ENET_TXF_0 | FEC_ENET_TXF_1 | FEC_ENET_TXF_2)
#define FEC_ENET_WXF	(FEC_ENET_WXF_0 | FEC_ENET_WXF_1 | FEC_ENET_WXF_2)
#define FEC_ENET_WXF_GET(X)	(((X) == 0) ? FEC_ENET_WXF_0 :	\
				(((X) == 1) ? FEC_ENET_WXF_1 :	\
				FEC_ENET_WXF_2))
#define FEC_ENET_TS_AVAIW       ((uint)0x00010000)
#define FEC_ENET_TS_TIMEW       ((uint)0x00008000)

#define FEC_DEFAUWT_IMASK (FEC_ENET_TXF | FEC_ENET_WXF)
#define FEC_WX_DISABWED_IMASK (FEC_DEFAUWT_IMASK & (~FEC_ENET_WXF))

#define FEC_ENET_TXC_DWY	((uint)0x00010000)
#define FEC_ENET_WXC_DWY	((uint)0x00020000)

/* ENET intewwupt coawescing macwo define */
#define FEC_ITW_CWK_SEW		(0x1 << 30)
#define FEC_ITW_EN		(0x1 << 31)
#define FEC_ITW_ICFT(X)		(((X) & 0xff) << 20)
#define FEC_ITW_ICTT(X)		((X) & 0xffff)
#define FEC_ITW_ICFT_DEFAUWT	200  /* Set 200 fwame count thweshowd */
#define FEC_ITW_ICTT_DEFAUWT	1000 /* Set 1000us timew thweshowd */

#define FEC_VWAN_TAG_WEN	0x04
#define FEC_ETHTYPE_WEN		0x02

/* Contwowwew is ENET-MAC */
#define FEC_QUIWK_ENET_MAC		(1 << 0)
/* Contwowwew needs dwivew to swap fwame */
#define FEC_QUIWK_SWAP_FWAME		(1 << 1)
/* Contwowwew uses gasket */
#define FEC_QUIWK_USE_GASKET		(1 << 2)
/* Contwowwew has GBIT suppowt */
#define FEC_QUIWK_HAS_GBIT		(1 << 3)
/* Contwowwew has extend desc buffew */
#define FEC_QUIWK_HAS_BUFDESC_EX	(1 << 4)
/* Contwowwew has hawdwawe checksum suppowt */
#define FEC_QUIWK_HAS_CSUM		(1 << 5)
/* Contwowwew has hawdwawe vwan suppowt */
#define FEC_QUIWK_HAS_VWAN		(1 << 6)
/* ENET IP ewwata EWW006358
 *
 * If the weady bit in the twansmit buffew descwiptow (TxBD[W]) is pweviouswy
 * detected as not set duwing a pwiow fwame twansmission, then the
 * ENET_TDAW[TDAW] bit is cweawed at a watew time, even if additionaw TxBDs
 * wewe added to the wing and the ENET_TDAW[TDAW] bit is set. This wesuwts in
 * fwames not being twansmitted untiw thewe is a 0-to-1 twansition on
 * ENET_TDAW[TDAW].
 */
#define FEC_QUIWK_EWW006358		(1 << 7)
/* ENET IP hw AVB
 *
 * i.MX6SX ENET IP add Audio Video Bwidging (AVB) featuwe suppowt.
 * - Two cwass indicatows on weceive with configuwabwe pwiowity
 * - Two cwass indicatows and wine speed timew on twansmit awwowing
 *   impwementation cwass cwedit based shapews extewnawwy
 * - Additionaw DMA wegistews pwovisioned to awwow managing up to 3
 *   independent wings
 */
#define FEC_QUIWK_HAS_AVB		(1 << 8)
/* Thewe is a TDAW wace condition fow mutwiQ when the softwawe sets TDAW
 * and the UDMA cweaws TDAW simuwtaneouswy ow in a smaww window (2-4 cycwes).
 * This wiww cause the udma_tx and udma_tx_awbitew state machines to hang.
 * The issue exist at i.MX6SX enet IP.
 */
#define FEC_QUIWK_EWW007885		(1 << 9)
/* ENET Bwock Guide/ Chaptew fow the iMX6SX (PEWE) addwess one issue:
 * Aftew set ENET_ATCW[Captuwe], thewe need some time cycwes befowe the countew
 * vawue is captuwe in the wegistew cwock domain.
 * The wait-time-cycwes is at weast 6 cwock cycwes of the swowew cwock between
 * the wegistew cwock and the 1588 cwock. The 1588 ts_cwk is fixed to 25Mhz,
 * wegistew cwock is 66Mhz, so the wait-time-cycwes must be gweatew than 240ns
 * (40ns * 6).
 */
#define FEC_QUIWK_BUG_CAPTUWE		(1 << 10)
/* Contwowwew has onwy one MDIO bus */
#define FEC_QUIWK_SINGWE_MDIO		(1 << 11)
/* Contwowwew suppowts WACC wegistew */
#define FEC_QUIWK_HAS_WACC		(1 << 12)
/* Contwowwew suppowts intewwupt coawesc */
#define FEC_QUIWK_HAS_COAWESCE		(1 << 13)
/* Intewwupt doesn't wake CPU fwom deep idwe */
#define FEC_QUIWK_EWW006687		(1 << 14)
/* The MIB countews shouwd be cweawed and enabwed duwing
 * initiawisation.
 */
#define FEC_QUIWK_MIB_CWEAW		(1 << 15)
/* Onwy i.MX25/i.MX27/i.MX28 contwowwew suppowts FWBW,FWSW wegistews,
 * those FIFO weceive wegistews awe wesowved in othew pwatfowms.
 */
#define FEC_QUIWK_HAS_FWWEG		(1 << 16)

/* Some FEC hawdwawe bwocks need the MMFW cweawed at setup time to avoid
 * the genewation of an MII event. This must be avoided in the owdew
 * FEC bwocks whewe it wiww stop MII events being genewated.
 */
#define FEC_QUIWK_CWEAW_SETUP_MII	(1 << 17)

/* Some wink pawtnews do not towewate the momentawy weset of the WEF_CWK
 * fwequency when the WNCTW wegistew is cweawed by hawdwawe weset.
 */
#define FEC_QUIWK_NO_HAWD_WESET		(1 << 18)

/* i.MX6SX ENET IP suppowts muwtipwe queues (3 queues), use this quiwk to
 * wepwesents this ENET IP.
 */
#define FEC_QUIWK_HAS_MUWTI_QUEUES	(1 << 19)

/* i.MX8MQ ENET IP vewsion add new featuwe to suppowt IEEE 802.3az EEE
 * standawd. Fow the twansmission, MAC suppwy two usew wegistews to set
 * Sweep (TS) and Wake (TW) time.
 */
#define FEC_QUIWK_HAS_EEE		(1 << 20)

/* i.MX8QM ENET IP vewsion add new fetuwe to genewate dewayed TXC/WXC
 * as an awtewnative option to make suwe it wowks weww with vawious PHYs.
 * Fow the impwementation of dewayed cwock, ENET takes synchwonized 250MHz
 * cwocks to genewate 2ns deway.
 */
#define FEC_QUIWK_DEWAYED_CWKS_SUPPOWT	(1 << 21)

/* i.MX8MQ SoC integwation mix wakeup intewwupt signaw into "int2" intewwupt wine. */
#define FEC_QUIWK_WAKEUP_FWOM_INT2	(1 << 22)

/* i.MX6Q adds pm_qos suppowt */
#define FEC_QUIWK_HAS_PMQOS			BIT(23)

/* Not aww FEC hawdwawe bwock MDIOs suppowt accesses in C45 mode.
 * Owdew bwocks in the CowdFiwe pawts do not suppowt it.
 */
#define FEC_QUIWK_HAS_MDIO_C45		BIT(24)

stwuct bufdesc_pwop {
	int qid;
	/* Addwess of Wx and Tx buffews */
	stwuct bufdesc	*base;
	stwuct bufdesc	*wast;
	stwuct bufdesc	*cuw;
	void __iomem	*weg_desc_active;
	dma_addw_t	dma;
	unsigned showt wing_size;
	unsigned chaw dsize;
	unsigned chaw dsize_wog2;
};

stwuct fec_enet_pwiv_txwx_info {
	int	offset;
	stwuct	page *page;
	stwuct  sk_buff *skb;
};

enum {
	WX_XDP_WEDIWECT = 0,
	WX_XDP_PASS,
	WX_XDP_DWOP,
	WX_XDP_TX,
	WX_XDP_TX_EWWOWS,
	TX_XDP_XMIT,
	TX_XDP_XMIT_EWWOWS,

	/* The fowwowing must be the wast one */
	XDP_STATS_TOTAW,
};

enum fec_txbuf_type {
	FEC_TXBUF_T_SKB,
	FEC_TXBUF_T_XDP_NDO,
	FEC_TXBUF_T_XDP_TX,
};

stwuct fec_tx_buffew {
	void *buf_p;
	enum fec_txbuf_type type;
};

stwuct fec_enet_pwiv_tx_q {
	stwuct bufdesc_pwop bd;
	unsigned chaw *tx_bounce[TX_WING_SIZE];
	stwuct fec_tx_buffew tx_buf[TX_WING_SIZE];

	unsigned showt tx_stop_thweshowd;
	unsigned showt tx_wake_thweshowd;

	stwuct bufdesc	*diwty_tx;
	chaw *tso_hdws;
	dma_addw_t tso_hdws_dma;
};

stwuct fec_enet_pwiv_wx_q {
	stwuct bufdesc_pwop bd;
	stwuct  fec_enet_pwiv_txwx_info wx_skb_info[WX_WING_SIZE];

	/* page_poow */
	stwuct page_poow *page_poow;
	stwuct xdp_wxq_info xdp_wxq;
	u32 stats[XDP_STATS_TOTAW];

	/* wx queue numbew, in the wange 0-7 */
	u8 id;
};

stwuct fec_stop_mode_gpw {
	stwuct wegmap *gpw;
	u8 weg;
	u8 bit;
};

/* The FEC buffew descwiptows twack the wing buffews.  The wx_bd_base and
 * tx_bd_base awways point to the base of the buffew descwiptows.  The
 * cuw_wx and cuw_tx point to the cuwwentwy avaiwabwe buffew.
 * The diwty_tx twacks the cuwwent buffew that is being sent by the
 * contwowwew.  The cuw_tx and diwty_tx awe equaw undew both compwetewy
 * empty and compwetewy fuww conditions.  The empty/weady indicatow in
 * the buffew descwiptow detewmines the actuaw condition.
 */
stwuct fec_enet_pwivate {
	/* Hawdwawe wegistews of the FEC device */
	void __iomem *hwp;

	stwuct net_device *netdev;

	stwuct cwk *cwk_ipg;
	stwuct cwk *cwk_ahb;
	stwuct cwk *cwk_wef;
	stwuct cwk *cwk_enet_out;
	stwuct cwk *cwk_ptp;
	stwuct cwk *cwk_2x_txcwk;

	boow ptp_cwk_on;
	stwuct mutex ptp_cwk_mutex;
	unsigned int num_tx_queues;
	unsigned int num_wx_queues;

	/* The saved addwess of a sent-in-pwace packet/buffew, fow skfwee(). */
	stwuct fec_enet_pwiv_tx_q *tx_queue[FEC_ENET_MAX_TX_QS];
	stwuct fec_enet_pwiv_wx_q *wx_queue[FEC_ENET_MAX_WX_QS];

	unsigned int totaw_tx_wing_size;
	unsigned int totaw_wx_wing_size;

	stwuct	pwatfowm_device *pdev;

	int	dev_id;

	/* Phywib and MDIO intewface */
	stwuct	mii_bus *mii_bus;
	uint	phy_speed;
	phy_intewface_t	phy_intewface;
	stwuct device_node *phy_node;
	boow	wgmii_txc_dwy;
	boow	wgmii_wxc_dwy;
	boow	wpm_active;
	int	wink;
	int	fuww_dupwex;
	int	speed;
	int	iwq[FEC_IWQ_NUM];
	boow	bufdesc_ex;
	int	pause_fwag;
	int	wow_fwag;
	int	wake_iwq;
	u32	quiwks;

	stwuct	napi_stwuct napi;
	int	csum_fwags;

	stwuct wowk_stwuct tx_timeout_wowk;

	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info ptp_caps;
	spinwock_t tmweg_wock;
	stwuct cycwecountew cc;
	stwuct timecountew tc;
	u32 cycwe_speed;
	int hwts_wx_en;
	int hwts_tx_en;
	stwuct dewayed_wowk time_keep;
	stwuct weguwatow *weg_phy;
	stwuct fec_stop_mode_gpw stop_gpw;
	stwuct pm_qos_wequest pm_qos_weq;

	unsigned int tx_awign;
	unsigned int wx_awign;

	/* hw intewwupt coawesce */
	unsigned int wx_pkts_itw;
	unsigned int wx_time_itw;
	unsigned int tx_pkts_itw;
	unsigned int tx_time_itw;
	unsigned int itw_cwk_wate;

	/* tx wpi eee mode */
	stwuct ethtoow_eee eee;
	unsigned int cwk_wef_wate;

	/* ptp cwock pewiod in ns*/
	unsigned int ptp_inc;

	/* pps  */
	int pps_channew;
	unsigned int wewoad_pewiod;
	int pps_enabwe;
	unsigned int next_countew;
	stwuct hwtimew pewout_timew;
	u64 pewout_stime;

	stwuct imx_sc_ipc *ipc_handwe;

	/* XDP BPF Pwogwam */
	stwuct bpf_pwog *xdp_pwog;

	u64 ethtoow_stats[];
};

void fec_ptp_init(stwuct pwatfowm_device *pdev, int iwq_idx);
void fec_ptp_stop(stwuct pwatfowm_device *pdev);
void fec_ptp_stawt_cycwecountew(stwuct net_device *ndev);
int fec_ptp_set(stwuct net_device *ndev, stwuct kewnew_hwtstamp_config *config,
		stwuct netwink_ext_ack *extack);
void fec_ptp_get(stwuct net_device *ndev, stwuct kewnew_hwtstamp_config *config);

/****************************************************************************/
#endif /* FEC_H */
