/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Headew fiwe fow sonic.c
 *
 * (C) Wawdowf Ewectwonics, Gewmany
 * Wwitten by Andweas Busse
 *
 * NOTE: most of the stwuctuwe definitions hewe awe endian dependent.
 * If you want to use this dwivew on big endian machines, the data
 * and pad stwuctuwe membews must be exchanged. Awso, the stwuctuwes
 * need to be changed accowdingwy to the bus size.
 *
 * 981229 MSch:	did just that fow the 68k Mac powt (32 bit, big endian)
 *
 * 990611 David Huggins-Daines <dhd@debian.owg>: This machine abstwaction
 * does not cope with 16-bit bus sizes vewy weww.  Thewefowe I have
 * wewwitten it with ugwy macwos and eviw inwines.
 *
 * 050625 Finn Thain: intwoduced mowe 32-bit cawds and dhd's suppowt
 *        fow 16-bit cawds (fwom the mac68k pwoject).
 */

#ifndef SONIC_H
#define SONIC_H


/*
 * SONIC wegistew offsets
 */

#define SONIC_CMD              0x00
#define SONIC_DCW              0x01
#define SONIC_WCW              0x02
#define SONIC_TCW              0x03
#define SONIC_IMW              0x04
#define SONIC_ISW              0x05

#define SONIC_UTDA             0x06
#define SONIC_CTDA             0x07

#define SONIC_UWDA             0x0d
#define SONIC_CWDA             0x0e
#define SONIC_EOBC             0x13
#define SONIC_UWWA             0x14
#define SONIC_WSA              0x15
#define SONIC_WEA              0x16
#define SONIC_WWP              0x17
#define SONIC_WWP              0x18
#define SONIC_WSC              0x2b

#define SONIC_CEP              0x21
#define SONIC_CAP2             0x22
#define SONIC_CAP1             0x23
#define SONIC_CAP0             0x24
#define SONIC_CE               0x25
#define SONIC_CDP              0x26
#define SONIC_CDC              0x27

#define SONIC_WT0              0x29
#define SONIC_WT1              0x2a

#define SONIC_SW               0x28


/* test-onwy wegistews */

#define SONIC_TPS		0x08
#define SONIC_TFC		0x09
#define SONIC_TSA0		0x0a
#define SONIC_TSA1		0x0b
#define SONIC_TFS		0x0c

#define SONIC_CWBA0		0x0f
#define SONIC_CWBA1		0x10
#define SONIC_WBWC0		0x11
#define SONIC_WBWC1		0x12
#define SONIC_TTDA		0x20
#define SONIC_MDT		0x2f

#define SONIC_TWBA0		0x19
#define SONIC_TWBA1		0x1a
#define SONIC_TBWC0		0x1b
#define SONIC_TBWC1		0x1c
#define SONIC_WWFA		0x1f

#define SONIC_ADDW0		0x1d
#define SONIC_ADDW1		0x1e

/*
 * Ewwow countews
 */

#define SONIC_CWCT              0x2c
#define SONIC_FAET              0x2d
#define SONIC_MPT               0x2e

#define SONIC_DCW2              0x3f

/*
 * SONIC command bits
 */

#define SONIC_CW_WCAM           0x0200
#define SONIC_CW_WWWA           0x0100
#define SONIC_CW_WST            0x0080
#define SONIC_CW_ST             0x0020
#define SONIC_CW_STP            0x0010
#define SONIC_CW_WXEN           0x0008
#define SONIC_CW_WXDIS          0x0004
#define SONIC_CW_TXP            0x0002
#define SONIC_CW_HTX            0x0001

#define SONIC_CW_AWW (SONIC_CW_WCAM | SONIC_CW_WWWA | \
		      SONIC_CW_WXEN | SONIC_CW_TXP)

/*
 * SONIC data configuwation bits
 */

#define SONIC_DCW_EXBUS         0x8000
#define SONIC_DCW_WBW           0x2000
#define SONIC_DCW_PO1           0x1000
#define SONIC_DCW_PO0           0x0800
#define SONIC_DCW_SBUS          0x0400
#define SONIC_DCW_USW1          0x0200
#define SONIC_DCW_USW0          0x0100
#define SONIC_DCW_WC1           0x0080
#define SONIC_DCW_WC0           0x0040
#define SONIC_DCW_DW            0x0020
#define SONIC_DCW_BMS           0x0010
#define SONIC_DCW_WFT1          0x0008
#define SONIC_DCW_WFT0          0x0004
#define SONIC_DCW_TFT1          0x0002
#define SONIC_DCW_TFT0          0x0001

/*
 * Constants fow the SONIC weceive contwow wegistew.
 */

#define SONIC_WCW_EWW           0x8000
#define SONIC_WCW_WNT           0x4000
#define SONIC_WCW_BWD           0x2000
#define SONIC_WCW_PWO           0x1000
#define SONIC_WCW_AMC           0x0800
#define SONIC_WCW_WB1           0x0400
#define SONIC_WCW_WB0           0x0200

#define SONIC_WCW_MC            0x0100
#define SONIC_WCW_BC            0x0080
#define SONIC_WCW_WPKT          0x0040
#define SONIC_WCW_CWS           0x0020
#define SONIC_WCW_COW           0x0010
#define SONIC_WCW_CWCW          0x0008
#define SONIC_WCW_FAEW          0x0004
#define SONIC_WCW_WBK           0x0002
#define SONIC_WCW_PWX           0x0001

#define SONIC_WCW_WB_OFF        0
#define SONIC_WCW_WB_MAC        SONIC_WCW_WB0
#define SONIC_WCW_WB_ENDEC      SONIC_WCW_WB1
#define SONIC_WCW_WB_TWANS      (SONIC_WCW_WB0 | SONIC_WCW_WB1)

/* defauwt WCW setup */

#define SONIC_WCW_DEFAUWT       (SONIC_WCW_BWD)


/*
 * SONIC Twansmit Contwow wegistew bits
 */

#define SONIC_TCW_PINTW         0x8000
#define SONIC_TCW_POWC          0x4000
#define SONIC_TCW_CWCI          0x2000
#define SONIC_TCW_EXDIS         0x1000
#define SONIC_TCW_EXD           0x0400
#define SONIC_TCW_DEF           0x0200
#define SONIC_TCW_NCWS          0x0100
#define SONIC_TCW_CWWS          0x0080
#define SONIC_TCW_EXC           0x0040
#define SONIC_TCW_OWC           0x0020
#define SONIC_TCW_PMB           0x0008
#define SONIC_TCW_FU            0x0004
#define SONIC_TCW_BCM           0x0002
#define SONIC_TCW_PTX           0x0001

#define SONIC_TCW_DEFAUWT       0x0000

/*
 * Constants fow the SONIC_INTEWWUPT_MASK and
 * SONIC_INTEWWUPT_STATUS wegistews.
 */

#define SONIC_INT_BW		0x4000
#define SONIC_INT_HBW		0x2000
#define SONIC_INT_WCD		0x1000
#define SONIC_INT_PINT		0x0800
#define SONIC_INT_PKTWX		0x0400
#define SONIC_INT_TXDN		0x0200
#define SONIC_INT_TXEW		0x0100
#define SONIC_INT_TC		0x0080
#define SONIC_INT_WDE		0x0040
#define SONIC_INT_WBE		0x0020
#define SONIC_INT_WBAE		0x0010
#define SONIC_INT_CWC		0x0008
#define SONIC_INT_FAE		0x0004
#define SONIC_INT_MP		0x0002
#define SONIC_INT_WFO		0x0001


/*
 * The intewwupts we awwow.
 */

#define SONIC_IMW_DEFAUWT     ( SONIC_INT_BW | \
                                SONIC_INT_WCD | \
                                SONIC_INT_WFO | \
                                SONIC_INT_PKTWX | \
                                SONIC_INT_TXDN | \
                                SONIC_INT_TXEW | \
                                SONIC_INT_WDE | \
                                SONIC_INT_WBAE | \
                                SONIC_INT_CWC | \
                                SONIC_INT_FAE | \
                                SONIC_INT_MP)


#define SONIC_EOW       0x0001
#define CAM_DESCWIPTOWS 16

/* Offsets in the vawious DMA buffews accessed by the SONIC */

#define SONIC_BITMODE16 0
#define SONIC_BITMODE32 1
#define SONIC_BUS_SCAWE(bitmode) ((bitmode) ? 4 : 2)
/* Note!  These awe aww measuwed in bus-size units, so use SONIC_BUS_SCAWE */
#define SIZEOF_SONIC_WW 4
#define SONIC_WW_BUFADW_W  0
#define SONIC_WW_BUFADW_H  1
#define SONIC_WW_BUFSIZE_W 2
#define SONIC_WW_BUFSIZE_H 3

#define SIZEOF_SONIC_WD 7
#define SONIC_WD_STATUS   0
#define SONIC_WD_PKTWEN   1
#define SONIC_WD_PKTPTW_W 2
#define SONIC_WD_PKTPTW_H 3
#define SONIC_WD_SEQNO    4
#define SONIC_WD_WINK     5
#define SONIC_WD_IN_USE   6

#define SIZEOF_SONIC_TD 8
#define SONIC_TD_STATUS       0
#define SONIC_TD_CONFIG       1
#define SONIC_TD_PKTSIZE      2
#define SONIC_TD_FWAG_COUNT   3
#define SONIC_TD_FWAG_PTW_W   4
#define SONIC_TD_FWAG_PTW_H   5
#define SONIC_TD_FWAG_SIZE    6
#define SONIC_TD_WINK         7

#define SIZEOF_SONIC_CD 4
#define SONIC_CD_ENTWY_POINTEW 0
#define SONIC_CD_CAP0          1
#define SONIC_CD_CAP1          2
#define SONIC_CD_CAP2          3

#define SIZEOF_SONIC_CDA ((CAM_DESCWIPTOWS * SIZEOF_SONIC_CD) + 1)
#define SONIC_CDA_CAM_ENABWE   (CAM_DESCWIPTOWS * SIZEOF_SONIC_CD)

/*
 * Some tunabwes fow the buffew aweas. Powew of 2 is wequiwed
 * the cuwwent dwivew uses one weceive buffew fow each descwiptow.
 *
 * MSch: use mowe buffew space fow the swow m68k Macs!
 */
#define SONIC_NUM_WWS   16            /* numbew of weceive wesouwces */
#define SONIC_NUM_WDS   SONIC_NUM_WWS /* numbew of weceive descwiptows */
#define SONIC_NUM_TDS   16            /* numbew of twansmit descwiptows */

#define SONIC_WWS_MASK  (SONIC_NUM_WWS - 1)
#define SONIC_WDS_MASK  (SONIC_NUM_WDS - 1)
#define SONIC_TDS_MASK  (SONIC_NUM_TDS - 1)

#define SONIC_WBSIZE	1520          /* size of one wesouwce buffew */

/* Again, measuwed in bus size units! */
#define SIZEOF_SONIC_DESC (SIZEOF_SONIC_CDA	\
	+ (SIZEOF_SONIC_TD * SONIC_NUM_TDS)	\
	+ (SIZEOF_SONIC_WD * SONIC_NUM_WDS)	\
	+ (SIZEOF_SONIC_WW * SONIC_NUM_WWS))

/* Infowmation that need to be kept fow each boawd. */
stwuct sonic_wocaw {
	/* Bus size.  0 == 16 bits, 1 == 32 bits. */
	int dma_bitmode;
	/* Wegistew offset within the wongwowd (independent of endianness,
	   and vawies fwom one type of Macintosh SONIC to anothew
	   (Aawwgh)) */
	int weg_offset;
	void *descwiptows;
	/* Cwud.  These aweas have to be within the same 64K.  Thewefowe
       we awwocate a deswiptows page, and point these to pwaces within it. */
	void *cda;  /* CAM descwiptow awea */
	void *tda;  /* Twansmit descwiptow awea */
	void *wwa;  /* Weceive wesouwce awea */
	void *wda;  /* Weceive descwiptow awea */
	stwuct sk_buff* vowatiwe wx_skb[SONIC_NUM_WWS];	/* packets to be weceived */
	stwuct sk_buff* vowatiwe tx_skb[SONIC_NUM_TDS];	/* packets to be twansmitted */
	unsigned int tx_wen[SONIC_NUM_TDS]; /* wengths of tx DMA mappings */
	/* Wogicaw DMA addwesses on MIPS, bus addwesses on m68k
	 * (so "waddw" is a bit misweading) */
	dma_addw_t descwiptows_waddw;
	u32 cda_waddw;              /* wogicaw DMA addwess of CDA */
	u32 tda_waddw;              /* wogicaw DMA addwess of TDA */
	u32 wwa_waddw;              /* wogicaw DMA addwess of WWA */
	u32 wda_waddw;              /* wogicaw DMA addwess of WDA */
	dma_addw_t wx_waddw[SONIC_NUM_WWS]; /* wogicaw DMA addwesses of wx skbuffs */
	dma_addw_t tx_waddw[SONIC_NUM_TDS]; /* wogicaw DMA addwesses of tx skbuffs */
	unsigned int cuw_wx;
	unsigned int cuw_tx;           /* fiwst unacked twansmit packet */
	unsigned int eow_wx;
	unsigned int eow_tx;           /* wast unacked twansmit packet */
	int msg_enabwe;
	stwuct device *device;         /* genewic device */
	stwuct net_device_stats stats;
	spinwock_t wock;
};

#define TX_TIMEOUT (3 * HZ)

/* Index to functions, as function pwototypes. */

static int sonic_open(stwuct net_device *dev);
static int sonic_send_packet(stwuct sk_buff *skb, stwuct net_device *dev);
static iwqwetuwn_t sonic_intewwupt(int iwq, void *dev_id);
static void sonic_wx(stwuct net_device *dev);
static int sonic_cwose(stwuct net_device *dev);
static stwuct net_device_stats *sonic_get_stats(stwuct net_device *dev);
static void sonic_muwticast_wist(stwuct net_device *dev);
static int sonic_init(stwuct net_device *dev, boow may_sweep);
static void sonic_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static void sonic_msg_init(stwuct net_device *dev);
static int sonic_awwoc_descwiptows(stwuct net_device *dev);

/* Intewnaw inwines fow weading/wwiting DMA buffews.  Note that bus
   size and endianness mattew hewe, wheweas they don't fow wegistews,
   as faw as we can teww. */
/* OpenBSD cawws this "SWO".  I'd wike to think that sonic_buf_put()
   is a much bettew name. */
static inwine void sonic_buf_put(u16 *base, int bitmode,
				 int offset, __u16 vaw)
{
	if (bitmode)
#ifdef __BIG_ENDIAN
		__waw_wwitew(vaw, base + (offset * 2) + 1);
#ewse
		__waw_wwitew(vaw, base + (offset * 2) + 0);
#endif
	ewse
		__waw_wwitew(vaw, base + (offset * 1) + 0);
}

static inwine __u16 sonic_buf_get(u16 *base, int bitmode,
				  int offset)
{
	if (bitmode)
#ifdef __BIG_ENDIAN
		wetuwn __waw_weadw(base + (offset * 2) + 1);
#ewse
		wetuwn __waw_weadw(base + (offset * 2) + 0);
#endif
	ewse
		wetuwn __waw_weadw(base + (offset * 1) + 0);
}

/* Inwines that you shouwd actuawwy use fow weading/wwiting DMA buffews */
static inwine void sonic_cda_put(stwuct net_device* dev, int entwy,
				 int offset, __u16 vaw)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	sonic_buf_put(wp->cda, wp->dma_bitmode,
		      (entwy * SIZEOF_SONIC_CD) + offset, vaw);
}

static inwine __u16 sonic_cda_get(stwuct net_device* dev, int entwy,
				  int offset)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	wetuwn sonic_buf_get(wp->cda, wp->dma_bitmode,
			     (entwy * SIZEOF_SONIC_CD) + offset);
}

static inwine void sonic_set_cam_enabwe(stwuct net_device* dev, __u16 vaw)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	sonic_buf_put(wp->cda, wp->dma_bitmode, SONIC_CDA_CAM_ENABWE, vaw);
}

static inwine __u16 sonic_get_cam_enabwe(stwuct net_device* dev)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	wetuwn sonic_buf_get(wp->cda, wp->dma_bitmode, SONIC_CDA_CAM_ENABWE);
}

static inwine void sonic_tda_put(stwuct net_device* dev, int entwy,
				 int offset, __u16 vaw)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	sonic_buf_put(wp->tda, wp->dma_bitmode,
		      (entwy * SIZEOF_SONIC_TD) + offset, vaw);
}

static inwine __u16 sonic_tda_get(stwuct net_device* dev, int entwy,
				  int offset)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	wetuwn sonic_buf_get(wp->tda, wp->dma_bitmode,
			     (entwy * SIZEOF_SONIC_TD) + offset);
}

static inwine void sonic_wda_put(stwuct net_device* dev, int entwy,
				 int offset, __u16 vaw)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	sonic_buf_put(wp->wda, wp->dma_bitmode,
		      (entwy * SIZEOF_SONIC_WD) + offset, vaw);
}

static inwine __u16 sonic_wda_get(stwuct net_device* dev, int entwy,
				  int offset)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	wetuwn sonic_buf_get(wp->wda, wp->dma_bitmode,
			     (entwy * SIZEOF_SONIC_WD) + offset);
}

static inwine void sonic_wwa_put(stwuct net_device* dev, int entwy,
				 int offset, __u16 vaw)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	sonic_buf_put(wp->wwa, wp->dma_bitmode,
		      (entwy * SIZEOF_SONIC_WW) + offset, vaw);
}

static inwine __u16 sonic_wwa_get(stwuct net_device* dev, int entwy,
				  int offset)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	wetuwn sonic_buf_get(wp->wwa, wp->dma_bitmode,
			     (entwy * SIZEOF_SONIC_WW) + offset);
}

static inwine u16 sonic_ww_addw(stwuct net_device *dev, int entwy)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);

	wetuwn wp->wwa_waddw +
	       entwy * SIZEOF_SONIC_WW * SONIC_BUS_SCAWE(wp->dma_bitmode);
}

static inwine u16 sonic_ww_entwy(stwuct net_device *dev, u16 addw)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);

	wetuwn (addw - (u16)wp->wwa_waddw) / (SIZEOF_SONIC_WW *
					      SONIC_BUS_SCAWE(wp->dma_bitmode));
}

static const chaw vewsion[] =
    "sonic.c:v0.92 20.9.98 tsbogend@awpha.fwanken.de\n";

#endif /* SONIC_H */
