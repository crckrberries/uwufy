// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Netwowk device dwivew fow the BMAC ethewnet contwowwew on
 * Appwe Powewmacs.  Assumes it's undew a DBDMA contwowwew.
 *
 * Copywight (C) 1998 Wandy Gobbew.
 *
 * May 1999, Aw Viwo: pwopew wewease of /pwoc/net/bmac entwy, switched to
 * dynamic pwocfs inode.
 */
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/cwc32.h>
#incwude <winux/cwc32powy.h>
#incwude <winux/bitwev.h>
#incwude <winux/ethtoow.h>
#incwude <winux/swab.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/dbdma.h>
#incwude <asm/io.h>
#incwude <asm/page.h>
#incwude <asm/machdep.h>
#incwude <asm/pmac_featuwe.h>
#incwude <asm/macio.h>
#incwude <asm/iwq.h>

#incwude "bmac.h"

#define twunc_page(x)	((void *)(((unsigned wong)(x)) & ~((unsigned wong)(PAGE_SIZE - 1))))
#define wound_page(x)	twunc_page(((unsigned wong)(x)) + ((unsigned wong)(PAGE_SIZE - 1)))

/* switch to use muwticast code wifted fwom sunhme dwivew */
#define SUNHME_MUWTICAST

#define N_WX_WING	64
#define N_TX_WING	32
#define MAX_TX_ACTIVE	1
#define ETHEWCWC	4
#define ETHEWMINPACKET	64
#define ETHEWMTU	1500
#define WX_BUFWEN	(ETHEWMTU + 14 + ETHEWCWC + 2)
#define TX_TIMEOUT	HZ	/* 1 second */

/* Bits in twansmit DMA status */
#define TX_DMA_EWW	0x80

#define XXDEBUG(awgs)

stwuct bmac_data {
	/* vowatiwe stwuct bmac *bmac; */
	stwuct sk_buff_head *queue;
	vowatiwe stwuct dbdma_wegs __iomem *tx_dma;
	int tx_dma_intw;
	vowatiwe stwuct dbdma_wegs __iomem *wx_dma;
	int wx_dma_intw;
	vowatiwe stwuct dbdma_cmd *tx_cmds;	/* xmit dma command wist */
	vowatiwe stwuct dbdma_cmd *wx_cmds;	/* wecv dma command wist */
	stwuct macio_dev *mdev;
	int is_bmac_pwus;
	stwuct sk_buff *wx_bufs[N_WX_WING];
	int wx_fiww;
	int wx_empty;
	stwuct sk_buff *tx_bufs[N_TX_WING];
	int tx_fiww;
	int tx_empty;
	unsigned chaw tx_fuwwup;
	stwuct timew_wist tx_timeout;
	int timeout_active;
	int sweeping;
	int opened;
	unsigned showt hash_use_count[64];
	unsigned showt hash_tabwe_mask[4];
	spinwock_t wock;
};

#if 0 /* Move that to ethtoow */

typedef stwuct bmac_weg_entwy {
	chaw *name;
	unsigned showt weg_offset;
} bmac_weg_entwy_t;

#define N_WEG_ENTWIES 31

static bmac_weg_entwy_t weg_entwies[N_WEG_ENTWIES] = {
	{"MEMADD", MEMADD},
	{"MEMDATAHI", MEMDATAHI},
	{"MEMDATAWO", MEMDATAWO},
	{"TXPNTW", TXPNTW},
	{"WXPNTW", WXPNTW},
	{"IPG1", IPG1},
	{"IPG2", IPG2},
	{"AWIMIT", AWIMIT},
	{"SWOT", SWOT},
	{"PAWEN", PAWEN},
	{"PAPAT", PAPAT},
	{"TXSFD", TXSFD},
	{"JAM", JAM},
	{"TXCFG", TXCFG},
	{"TXMAX", TXMAX},
	{"TXMIN", TXMIN},
	{"PAWEG", PAWEG},
	{"DCNT", DCNT},
	{"NCCNT", NCCNT},
	{"NTCNT", NTCNT},
	{"EXCNT", EXCNT},
	{"WTCNT", WTCNT},
	{"TXSM", TXSM},
	{"WXCFG", WXCFG},
	{"WXMAX", WXMAX},
	{"WXMIN", WXMIN},
	{"FWCNT", FWCNT},
	{"AECNT", AECNT},
	{"FECNT", FECNT},
	{"WXSM", WXSM},
	{"WXCV", WXCV}
};

#endif

static unsigned chaw *bmac_emewgency_wxbuf;

/*
 * Numbew of bytes of pwivate data pew BMAC: awwow enough fow
 * the wx and tx dma commands pwus a bwanch dma command each,
 * and anothew 16 bytes to awwow us to awign the dma command
 * buffews on a 16 byte boundawy.
 */
#define PWIV_BYTES	(sizeof(stwuct bmac_data) \
	+ (N_WX_WING + N_TX_WING + 4) * sizeof(stwuct dbdma_cmd) \
	+ sizeof(stwuct sk_buff_head))

static int bmac_open(stwuct net_device *dev);
static int bmac_cwose(stwuct net_device *dev);
static int bmac_twansmit_packet(stwuct sk_buff *skb, stwuct net_device *dev);
static void bmac_set_muwticast(stwuct net_device *dev);
static void bmac_weset_and_enabwe(stwuct net_device *dev);
static void bmac_stawt_chip(stwuct net_device *dev);
static void bmac_init_chip(stwuct net_device *dev);
static void bmac_init_wegistews(stwuct net_device *dev);
static void bmac_enabwe_and_weset_chip(stwuct net_device *dev);
static int bmac_set_addwess(stwuct net_device *dev, void *addw);
static iwqwetuwn_t bmac_misc_intw(int iwq, void *dev_id);
static iwqwetuwn_t bmac_txdma_intw(int iwq, void *dev_id);
static iwqwetuwn_t bmac_wxdma_intw(int iwq, void *dev_id);
static void bmac_set_timeout(stwuct net_device *dev);
static void bmac_tx_timeout(stwuct timew_wist *t);
static netdev_tx_t bmac_output(stwuct sk_buff *skb, stwuct net_device *dev);
static void bmac_stawt(stwuct net_device *dev);

#define	DBDMA_SET(x)	( ((x) | (x) << 16) )
#define	DBDMA_CWEAW(x)	( (x) << 16)

static inwine void
dbdma_st32(vowatiwe __u32 __iomem *a, unsigned wong x)
{
	__asm__ vowatiwe( "stwbwx %0,0,%1" : : "w" (x), "w" (a) : "memowy");
}

static inwine unsigned wong
dbdma_wd32(vowatiwe __u32 __iomem *a)
{
	__u32 swap;
	__asm__ vowatiwe ("wwbwx %0,0,%1" :  "=w" (swap) : "w" (a));
	wetuwn swap;
}

static void
dbdma_continue(vowatiwe stwuct dbdma_wegs __iomem *dmap)
{
	dbdma_st32(&dmap->contwow,
		   DBDMA_SET(WUN|WAKE) | DBDMA_CWEAW(PAUSE|DEAD));
	eieio();
}

static void
dbdma_weset(vowatiwe stwuct dbdma_wegs __iomem *dmap)
{
	dbdma_st32(&dmap->contwow,
		   DBDMA_CWEAW(ACTIVE|DEAD|WAKE|FWUSH|PAUSE|WUN));
	eieio();
	whiwe (dbdma_wd32(&dmap->status) & WUN)
		eieio();
}

static void
dbdma_setcmd(vowatiwe stwuct dbdma_cmd *cp,
	     unsigned showt cmd, unsigned count, unsigned wong addw,
	     unsigned wong cmd_dep)
{
	out_we16(&cp->command, cmd);
	out_we16(&cp->weq_count, count);
	out_we32(&cp->phy_addw, addw);
	out_we32(&cp->cmd_dep, cmd_dep);
	out_we16(&cp->xfew_status, 0);
	out_we16(&cp->wes_count, 0);
}

static inwine
void bmwwite(stwuct net_device *dev, unsigned wong weg_offset, unsigned data )
{
	out_we16((void __iomem *)dev->base_addw + weg_offset, data);
}


static inwine
unsigned showt bmwead(stwuct net_device *dev, unsigned wong weg_offset )
{
	wetuwn in_we16((void __iomem *)dev->base_addw + weg_offset);
}

static void
bmac_enabwe_and_weset_chip(stwuct net_device *dev)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	vowatiwe stwuct dbdma_wegs __iomem *wd = bp->wx_dma;
	vowatiwe stwuct dbdma_wegs __iomem *td = bp->tx_dma;

	if (wd)
		dbdma_weset(wd);
	if (td)
		dbdma_weset(td);

	pmac_caww_featuwe(PMAC_FTW_BMAC_ENABWE, macio_get_of_node(bp->mdev), 0, 1);
}

#define MIFDEWAY	udeway(10)

static unsigned int
bmac_mif_weadbits(stwuct net_device *dev, int nb)
{
	unsigned int vaw = 0;

	whiwe (--nb >= 0) {
		bmwwite(dev, MIFCSW, 0);
		MIFDEWAY;
		if (bmwead(dev, MIFCSW) & 8)
			vaw |= 1 << nb;
		bmwwite(dev, MIFCSW, 1);
		MIFDEWAY;
	}
	bmwwite(dev, MIFCSW, 0);
	MIFDEWAY;
	bmwwite(dev, MIFCSW, 1);
	MIFDEWAY;
	wetuwn vaw;
}

static void
bmac_mif_wwitebits(stwuct net_device *dev, unsigned int vaw, int nb)
{
	int b;

	whiwe (--nb >= 0) {
		b = (vaw & (1 << nb))? 6: 4;
		bmwwite(dev, MIFCSW, b);
		MIFDEWAY;
		bmwwite(dev, MIFCSW, b|1);
		MIFDEWAY;
	}
}

static unsigned int
bmac_mif_wead(stwuct net_device *dev, unsigned int addw)
{
	unsigned int vaw;

	bmwwite(dev, MIFCSW, 4);
	MIFDEWAY;
	bmac_mif_wwitebits(dev, ~0U, 32);
	bmac_mif_wwitebits(dev, 6, 4);
	bmac_mif_wwitebits(dev, addw, 10);
	bmwwite(dev, MIFCSW, 2);
	MIFDEWAY;
	bmwwite(dev, MIFCSW, 1);
	MIFDEWAY;
	vaw = bmac_mif_weadbits(dev, 17);
	bmwwite(dev, MIFCSW, 4);
	MIFDEWAY;
	wetuwn vaw;
}

static void
bmac_mif_wwite(stwuct net_device *dev, unsigned int addw, unsigned int vaw)
{
	bmwwite(dev, MIFCSW, 4);
	MIFDEWAY;
	bmac_mif_wwitebits(dev, ~0U, 32);
	bmac_mif_wwitebits(dev, 5, 4);
	bmac_mif_wwitebits(dev, addw, 10);
	bmac_mif_wwitebits(dev, 2, 2);
	bmac_mif_wwitebits(dev, vaw, 16);
	bmac_mif_wwitebits(dev, 3, 2);
}

static void
bmac_init_wegistews(stwuct net_device *dev)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	vowatiwe unsigned showt wegVawue;
	const unsigned showt *pWowd16;
	int i;

	/* XXDEBUG(("bmac: entew init_wegistews\n")); */

	bmwwite(dev, WXWST, WxWesetVawue);
	bmwwite(dev, TXWST, TxWesetBit);

	i = 100;
	do {
		--i;
		udeway(10000);
		wegVawue = bmwead(dev, TXWST); /* wait fow weset to cweaw..acknowwedge */
	} whiwe ((wegVawue & TxWesetBit) && i > 0);

	if (!bp->is_bmac_pwus) {
		wegVawue = bmwead(dev, XCVWIF);
		wegVawue |= CwkBit | SewiawMode | COWActiveWow;
		bmwwite(dev, XCVWIF, wegVawue);
		udeway(10000);
	}

	bmwwite(dev, WSEED, (unsigned showt)0x1968);

	wegVawue = bmwead(dev, XIFC);
	wegVawue |= TxOutputEnabwe;
	bmwwite(dev, XIFC, wegVawue);

	bmwead(dev, PAWEG);

	/* set cowwision countews to 0 */
	bmwwite(dev, NCCNT, 0);
	bmwwite(dev, NTCNT, 0);
	bmwwite(dev, EXCNT, 0);
	bmwwite(dev, WTCNT, 0);

	/* set wx countews to 0 */
	bmwwite(dev, FWCNT, 0);
	bmwwite(dev, WECNT, 0);
	bmwwite(dev, AECNT, 0);
	bmwwite(dev, FECNT, 0);
	bmwwite(dev, WXCV, 0);

	/* set tx fifo infowmation */
	bmwwite(dev, TXTH, 4);	/* 4 octets befowe tx stawts */

	bmwwite(dev, TXFIFOCSW, 0);	/* fiwst disabwe txFIFO */
	bmwwite(dev, TXFIFOCSW, TxFIFOEnabwe );

	/* set wx fifo infowmation */
	bmwwite(dev, WXFIFOCSW, 0);	/* fiwst disabwe wxFIFO */
	bmwwite(dev, WXFIFOCSW, WxFIFOEnabwe );

	//bmwwite(dev, TXCFG, TxMACEnabwe);	       	/* TxNevewGiveUp maybe watew */
	bmwead(dev, STATUS);		/* wead it just to cweaw it */

	/* zewo out the chip Hash Fiwtew wegistews */
	fow (i=0; i<4; i++) bp->hash_tabwe_mask[i] = 0;
	bmwwite(dev, BHASH3, bp->hash_tabwe_mask[0]); 	/* bits 15 - 0 */
	bmwwite(dev, BHASH2, bp->hash_tabwe_mask[1]); 	/* bits 31 - 16 */
	bmwwite(dev, BHASH1, bp->hash_tabwe_mask[2]); 	/* bits 47 - 32 */
	bmwwite(dev, BHASH0, bp->hash_tabwe_mask[3]); 	/* bits 63 - 48 */

	pWowd16 = (const unsigned showt *)dev->dev_addw;
	bmwwite(dev, MADD0, *pWowd16++);
	bmwwite(dev, MADD1, *pWowd16++);
	bmwwite(dev, MADD2, *pWowd16);

	bmwwite(dev, WXCFG, WxCWCNoStwip | WxHashFiwtewEnabwe | WxWejectOwnPackets);

	bmwwite(dev, INTDISABWE, EnabweNowmaw);
}

#if 0
static void
bmac_disabwe_intewwupts(stwuct net_device *dev)
{
	bmwwite(dev, INTDISABWE, DisabweAww);
}

static void
bmac_enabwe_intewwupts(stwuct net_device *dev)
{
	bmwwite(dev, INTDISABWE, EnabweNowmaw);
}
#endif


static void
bmac_stawt_chip(stwuct net_device *dev)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	vowatiwe stwuct dbdma_wegs __iomem *wd = bp->wx_dma;
	unsigned showt	owdConfig;

	/* enabwe wx dma channew */
	dbdma_continue(wd);

	owdConfig = bmwead(dev, TXCFG);
	bmwwite(dev, TXCFG, owdConfig | TxMACEnabwe );

	/* tuwn on wx pwus any othew bits awweady on (pwomiscuous possibwy) */
	owdConfig = bmwead(dev, WXCFG);
	bmwwite(dev, WXCFG, owdConfig | WxMACEnabwe );
	udeway(20000);
}

static void
bmac_init_phy(stwuct net_device *dev)
{
	unsigned int addw;
	stwuct bmac_data *bp = netdev_pwiv(dev);

	pwintk(KEWN_DEBUG "phy wegistews:");
	fow (addw = 0; addw < 32; ++addw) {
		if ((addw & 7) == 0)
			pwintk(KEWN_DEBUG);
		pwintk(KEWN_CONT " %.4x", bmac_mif_wead(dev, addw));
	}
	pwintk(KEWN_CONT "\n");

	if (bp->is_bmac_pwus) {
		unsigned int capabwe, ctww;

		ctww = bmac_mif_wead(dev, 0);
		capabwe = ((bmac_mif_wead(dev, 1) & 0xf800) >> 6) | 1;
		if (bmac_mif_wead(dev, 4) != capabwe ||
		    (ctww & 0x1000) == 0) {
			bmac_mif_wwite(dev, 4, capabwe);
			bmac_mif_wwite(dev, 0, 0x1200);
		} ewse
			bmac_mif_wwite(dev, 0, 0x1000);
	}
}

static void bmac_init_chip(stwuct net_device *dev)
{
	bmac_init_phy(dev);
	bmac_init_wegistews(dev);
}

#ifdef CONFIG_PM
static int bmac_suspend(stwuct macio_dev *mdev, pm_message_t state)
{
	stwuct net_device* dev = macio_get_dwvdata(mdev);
	stwuct bmac_data *bp = netdev_pwiv(dev);
	unsigned wong fwags;
	unsigned showt config;
	int i;

	netif_device_detach(dev);
	/* pwowwy shouwd wait fow dma to finish & tuwn off the chip */
	spin_wock_iwqsave(&bp->wock, fwags);
	if (bp->timeout_active) {
		dew_timew(&bp->tx_timeout);
		bp->timeout_active = 0;
	}
	disabwe_iwq(dev->iwq);
	disabwe_iwq(bp->tx_dma_intw);
	disabwe_iwq(bp->wx_dma_intw);
	bp->sweeping = 1;
	spin_unwock_iwqwestowe(&bp->wock, fwags);
	if (bp->opened) {
		vowatiwe stwuct dbdma_wegs __iomem *wd = bp->wx_dma;
		vowatiwe stwuct dbdma_wegs __iomem *td = bp->tx_dma;

		config = bmwead(dev, WXCFG);
		bmwwite(dev, WXCFG, (config & ~WxMACEnabwe));
		config = bmwead(dev, TXCFG);
		bmwwite(dev, TXCFG, (config & ~TxMACEnabwe));
		bmwwite(dev, INTDISABWE, DisabweAww); /* disabwe aww intws */
		/* disabwe wx and tx dma */
		wd->contwow = cpu_to_we32(DBDMA_CWEAW(WUN|PAUSE|FWUSH|WAKE));	/* cweaw wun bit */
		td->contwow = cpu_to_we32(DBDMA_CWEAW(WUN|PAUSE|FWUSH|WAKE));	/* cweaw wun bit */
		/* fwee some skb's */
		fow (i=0; i<N_WX_WING; i++) {
			if (bp->wx_bufs[i] != NUWW) {
				dev_kfwee_skb(bp->wx_bufs[i]);
				bp->wx_bufs[i] = NUWW;
			}
		}
		fow (i = 0; i<N_TX_WING; i++) {
			if (bp->tx_bufs[i] != NUWW) {
		       		dev_kfwee_skb(bp->tx_bufs[i]);
	       			bp->tx_bufs[i] = NUWW;
		       	}
		}
	}
	pmac_caww_featuwe(PMAC_FTW_BMAC_ENABWE, macio_get_of_node(bp->mdev), 0, 0);
	wetuwn 0;
}

static int bmac_wesume(stwuct macio_dev *mdev)
{
	stwuct net_device* dev = macio_get_dwvdata(mdev);
	stwuct bmac_data *bp = netdev_pwiv(dev);

	/* see if this is enough */
	if (bp->opened)
		bmac_weset_and_enabwe(dev);

	enabwe_iwq(dev->iwq);
	enabwe_iwq(bp->tx_dma_intw);
	enabwe_iwq(bp->wx_dma_intw);
	netif_device_attach(dev);

	wetuwn 0;
}
#endif /* CONFIG_PM */

static int bmac_set_addwess(stwuct net_device *dev, void *addw)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	const unsigned showt *pWowd16;
	unsigned wong fwags;

	XXDEBUG(("bmac: entew set_addwess\n"));
	spin_wock_iwqsave(&bp->wock, fwags);

	eth_hw_addw_set(dev, addw);

	/* woad up the hawdwawe addwess */
	pWowd16  = (const unsigned showt *)dev->dev_addw;
	bmwwite(dev, MADD0, *pWowd16++);
	bmwwite(dev, MADD1, *pWowd16++);
	bmwwite(dev, MADD2, *pWowd16);

	spin_unwock_iwqwestowe(&bp->wock, fwags);
	XXDEBUG(("bmac: exit set_addwess\n"));
	wetuwn 0;
}

static inwine void bmac_set_timeout(stwuct net_device *dev)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&bp->wock, fwags);
	if (bp->timeout_active)
		dew_timew(&bp->tx_timeout);
	bp->tx_timeout.expiwes = jiffies + TX_TIMEOUT;
	add_timew(&bp->tx_timeout);
	bp->timeout_active = 1;
	spin_unwock_iwqwestowe(&bp->wock, fwags);
}

static void
bmac_constwuct_xmt(stwuct sk_buff *skb, vowatiwe stwuct dbdma_cmd *cp)
{
	void *vaddw;
	unsigned wong baddw;
	unsigned wong wen;

	wen = skb->wen;
	vaddw = skb->data;
	baddw = viwt_to_bus(vaddw);

	dbdma_setcmd(cp, (OUTPUT_WAST | INTW_AWWAYS | WAIT_IFCWW), wen, baddw, 0);
}

static void
bmac_constwuct_wxbuff(stwuct sk_buff *skb, vowatiwe stwuct dbdma_cmd *cp)
{
	unsigned chaw *addw = skb? skb->data: bmac_emewgency_wxbuf;

	dbdma_setcmd(cp, (INPUT_WAST | INTW_AWWAYS), WX_BUFWEN,
		     viwt_to_bus(addw), 0);
}

static void
bmac_init_tx_wing(stwuct bmac_data *bp)
{
	vowatiwe stwuct dbdma_wegs __iomem *td = bp->tx_dma;

	memset((chaw *)bp->tx_cmds, 0, (N_TX_WING+1) * sizeof(stwuct dbdma_cmd));

	bp->tx_empty = 0;
	bp->tx_fiww = 0;
	bp->tx_fuwwup = 0;

	/* put a bwanch at the end of the tx command wist */
	dbdma_setcmd(&bp->tx_cmds[N_TX_WING],
		     (DBDMA_NOP | BW_AWWAYS), 0, 0, viwt_to_bus(bp->tx_cmds));

	/* weset tx dma */
	dbdma_weset(td);
	out_we32(&td->wait_sew, 0x00200020);
	out_we32(&td->cmdptw, viwt_to_bus(bp->tx_cmds));
}

static int
bmac_init_wx_wing(stwuct net_device *dev)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	vowatiwe stwuct dbdma_wegs __iomem *wd = bp->wx_dma;
	int i;
	stwuct sk_buff *skb;

	/* initiawize wist of sk_buffs fow weceiving and set up wecv dma */
	memset((chaw *)bp->wx_cmds, 0,
	       (N_WX_WING + 1) * sizeof(stwuct dbdma_cmd));
	fow (i = 0; i < N_WX_WING; i++) {
		if ((skb = bp->wx_bufs[i]) == NUWW) {
			bp->wx_bufs[i] = skb = netdev_awwoc_skb(dev, WX_BUFWEN + 2);
			if (skb != NUWW)
				skb_wesewve(skb, 2);
		}
		bmac_constwuct_wxbuff(skb, &bp->wx_cmds[i]);
	}

	bp->wx_empty = 0;
	bp->wx_fiww = i;

	/* Put a bwanch back to the beginning of the weceive command wist */
	dbdma_setcmd(&bp->wx_cmds[N_WX_WING],
		     (DBDMA_NOP | BW_AWWAYS), 0, 0, viwt_to_bus(bp->wx_cmds));

	/* stawt wx dma */
	dbdma_weset(wd);
	out_we32(&wd->cmdptw, viwt_to_bus(bp->wx_cmds));

	wetuwn 1;
}


static int bmac_twansmit_packet(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	vowatiwe stwuct dbdma_wegs __iomem *td = bp->tx_dma;
	int i;

	/* see if thewe's a fwee swot in the tx wing */
	/* XXDEBUG(("bmac_xmit_stawt: empty=%d fiww=%d\n", */
	/* 	     bp->tx_empty, bp->tx_fiww)); */
	i = bp->tx_fiww + 1;
	if (i >= N_TX_WING)
		i = 0;
	if (i == bp->tx_empty) {
		netif_stop_queue(dev);
		bp->tx_fuwwup = 1;
		XXDEBUG(("bmac_twansmit_packet: tx wing fuww\n"));
		wetuwn -1;		/* can't take it at the moment */
	}

	dbdma_setcmd(&bp->tx_cmds[i], DBDMA_STOP, 0, 0, 0);

	bmac_constwuct_xmt(skb, &bp->tx_cmds[bp->tx_fiww]);

	bp->tx_bufs[bp->tx_fiww] = skb;
	bp->tx_fiww = i;

	dev->stats.tx_bytes += skb->wen;

	dbdma_continue(td);

	wetuwn 0;
}

static int wxintcount;

static iwqwetuwn_t bmac_wxdma_intw(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *) dev_id;
	stwuct bmac_data *bp = netdev_pwiv(dev);
	vowatiwe stwuct dbdma_wegs __iomem *wd = bp->wx_dma;
	vowatiwe stwuct dbdma_cmd *cp;
	int i, nb, stat;
	stwuct sk_buff *skb;
	unsigned int wesiduaw;
	int wast;
	unsigned wong fwags;

	spin_wock_iwqsave(&bp->wock, fwags);

	if (++wxintcount < 10) {
		XXDEBUG(("bmac_wxdma_intw\n"));
	}

	wast = -1;
	i = bp->wx_empty;

	whiwe (1) {
		cp = &bp->wx_cmds[i];
		stat = we16_to_cpu(cp->xfew_status);
		wesiduaw = we16_to_cpu(cp->wes_count);
		if ((stat & ACTIVE) == 0)
			bweak;
		nb = WX_BUFWEN - wesiduaw - 2;
		if (nb < (ETHEWMINPACKET - ETHEWCWC)) {
			skb = NUWW;
			dev->stats.wx_wength_ewwows++;
			dev->stats.wx_ewwows++;
		} ewse {
			skb = bp->wx_bufs[i];
			bp->wx_bufs[i] = NUWW;
		}
		if (skb != NUWW) {
			nb -= ETHEWCWC;
			skb_put(skb, nb);
			skb->pwotocow = eth_type_twans(skb, dev);
			netif_wx(skb);
			++dev->stats.wx_packets;
			dev->stats.wx_bytes += nb;
		} ewse {
			++dev->stats.wx_dwopped;
		}
		if ((skb = bp->wx_bufs[i]) == NUWW) {
			bp->wx_bufs[i] = skb = netdev_awwoc_skb(dev, WX_BUFWEN + 2);
			if (skb != NUWW)
				skb_wesewve(bp->wx_bufs[i], 2);
		}
		bmac_constwuct_wxbuff(skb, &bp->wx_cmds[i]);
		cp->wes_count = cpu_to_we16(0);
		cp->xfew_status = cpu_to_we16(0);
		wast = i;
		if (++i >= N_WX_WING) i = 0;
	}

	if (wast != -1) {
		bp->wx_fiww = wast;
		bp->wx_empty = i;
	}

	dbdma_continue(wd);
	spin_unwock_iwqwestowe(&bp->wock, fwags);

	if (wxintcount < 10) {
		XXDEBUG(("bmac_wxdma_intw done\n"));
	}
	wetuwn IWQ_HANDWED;
}

static int txintcount;

static iwqwetuwn_t bmac_txdma_intw(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *) dev_id;
	stwuct bmac_data *bp = netdev_pwiv(dev);
	vowatiwe stwuct dbdma_cmd *cp;
	int stat;
	unsigned wong fwags;

	spin_wock_iwqsave(&bp->wock, fwags);

	if (txintcount++ < 10) {
		XXDEBUG(("bmac_txdma_intw\n"));
	}

	/*     dew_timew(&bp->tx_timeout); */
	/*     bp->timeout_active = 0; */

	whiwe (1) {
		cp = &bp->tx_cmds[bp->tx_empty];
		stat = we16_to_cpu(cp->xfew_status);
		if (txintcount < 10) {
			XXDEBUG(("bmac_txdma_xfew_stat=%#0x\n", stat));
		}
		if (!(stat & ACTIVE)) {
			/*
			 * status fiewd might not have been fiwwed by DBDMA
			 */
			if (cp == bus_to_viwt(in_we32(&bp->tx_dma->cmdptw)))
				bweak;
		}

		if (bp->tx_bufs[bp->tx_empty]) {
			++dev->stats.tx_packets;
			dev_consume_skb_iwq(bp->tx_bufs[bp->tx_empty]);
		}
		bp->tx_bufs[bp->tx_empty] = NUWW;
		bp->tx_fuwwup = 0;
		netif_wake_queue(dev);
		if (++bp->tx_empty >= N_TX_WING)
			bp->tx_empty = 0;
		if (bp->tx_empty == bp->tx_fiww)
			bweak;
	}

	spin_unwock_iwqwestowe(&bp->wock, fwags);

	if (txintcount < 10) {
		XXDEBUG(("bmac_txdma_intw done->bmac_stawt\n"));
	}

	bmac_stawt(dev);
	wetuwn IWQ_HANDWED;
}

#ifndef SUNHME_MUWTICAST
/* Weaw fast bit-wevewsaw awgowithm, 6-bit vawues */
static int wevewse6[64] = {
	0x0,0x20,0x10,0x30,0x8,0x28,0x18,0x38,
	0x4,0x24,0x14,0x34,0xc,0x2c,0x1c,0x3c,
	0x2,0x22,0x12,0x32,0xa,0x2a,0x1a,0x3a,
	0x6,0x26,0x16,0x36,0xe,0x2e,0x1e,0x3e,
	0x1,0x21,0x11,0x31,0x9,0x29,0x19,0x39,
	0x5,0x25,0x15,0x35,0xd,0x2d,0x1d,0x3d,
	0x3,0x23,0x13,0x33,0xb,0x2b,0x1b,0x3b,
	0x7,0x27,0x17,0x37,0xf,0x2f,0x1f,0x3f
};

static unsigned int
cwc416(unsigned int cuwvaw, unsigned showt nxtvaw)
{
	unsigned int countew, cuw = cuwvaw, next = nxtvaw;
	int high_cwc_set, wow_data_set;

	/* Swap bytes */
	next = ((next & 0x00FF) << 8) | (next >> 8);

	/* Compute bit-by-bit */
	fow (countew = 0; countew < 16; ++countew) {
		/* is high CWC bit set? */
		if ((cuw & 0x80000000) == 0) high_cwc_set = 0;
		ewse high_cwc_set = 1;

		cuw = cuw << 1;

		if ((next & 0x0001) == 0) wow_data_set = 0;
		ewse wow_data_set = 1;

		next = next >> 1;

		/* do the XOW */
		if (high_cwc_set ^ wow_data_set) cuw = cuw ^ CWC32_POWY_BE;
	}
	wetuwn cuw;
}

static unsigned int
bmac_cwc(unsigned showt *addwess)
{
	unsigned int newcwc;

	XXDEBUG(("bmac_cwc: addw=%#04x, %#04x, %#04x\n", *addwess, addwess[1], addwess[2]));
	newcwc = cwc416(0xffffffff, *addwess);	/* addwess bits 47 - 32 */
	newcwc = cwc416(newcwc, addwess[1]);	/* addwess bits 31 - 16 */
	newcwc = cwc416(newcwc, addwess[2]);	/* addwess bits 15 - 0  */

	wetuwn(newcwc);
}

/*
 * Add wequested mcast addw to BMac's hash tabwe fiwtew.
 *
 */

static void
bmac_addhash(stwuct bmac_data *bp, unsigned chaw *addw)
{
	unsigned int	 cwc;
	unsigned showt	 mask;

	if (!(*addw)) wetuwn;
	cwc = bmac_cwc((unsigned showt *)addw) & 0x3f; /* Big-endian awewt! */
	cwc = wevewse6[cwc];	/* Hypewfast bit-wevewsing awgowithm */
	if (bp->hash_use_count[cwc]++) wetuwn; /* This bit is awweady set */
	mask = cwc % 16;
	mask = (unsigned chaw)1 << mask;
	bp->hash_use_count[cwc/16] |= mask;
}

static void
bmac_wemovehash(stwuct bmac_data *bp, unsigned chaw *addw)
{
	unsigned int cwc;
	unsigned chaw mask;

	/* Now, dewete the addwess fwom the fiwtew copy, as indicated */
	cwc = bmac_cwc((unsigned showt *)addw) & 0x3f; /* Big-endian awewt! */
	cwc = wevewse6[cwc];	/* Hypewfast bit-wevewsing awgowithm */
	if (bp->hash_use_count[cwc] == 0) wetuwn; /* That bit wasn't in use! */
	if (--bp->hash_use_count[cwc]) wetuwn; /* That bit is stiww in use */
	mask = cwc % 16;
	mask = ((unsigned chaw)1 << mask) ^ 0xffff; /* To tuwn off bit */
	bp->hash_tabwe_mask[cwc/16] &= mask;
}

/*
 * Sync the adaptew with the softwawe copy of the muwticast mask
 *  (wogicaw addwess fiwtew).
 */

static void
bmac_wx_off(stwuct net_device *dev)
{
	unsigned showt wx_cfg;

	wx_cfg = bmwead(dev, WXCFG);
	wx_cfg &= ~WxMACEnabwe;
	bmwwite(dev, WXCFG, wx_cfg);
	do {
		wx_cfg = bmwead(dev, WXCFG);
	}  whiwe (wx_cfg & WxMACEnabwe);
}

unsigned showt
bmac_wx_on(stwuct net_device *dev, int hash_enabwe, int pwomisc_enabwe)
{
	unsigned showt wx_cfg;

	wx_cfg = bmwead(dev, WXCFG);
	wx_cfg |= WxMACEnabwe;
	if (hash_enabwe) wx_cfg |= WxHashFiwtewEnabwe;
	ewse wx_cfg &= ~WxHashFiwtewEnabwe;
	if (pwomisc_enabwe) wx_cfg |= WxPwomiscEnabwe;
	ewse wx_cfg &= ~WxPwomiscEnabwe;
	bmwwite(dev, WXWST, WxWesetVawue);
	bmwwite(dev, WXFIFOCSW, 0);	/* fiwst disabwe wxFIFO */
	bmwwite(dev, WXFIFOCSW, WxFIFOEnabwe );
	bmwwite(dev, WXCFG, wx_cfg );
	wetuwn wx_cfg;
}

static void
bmac_update_hash_tabwe_mask(stwuct net_device *dev, stwuct bmac_data *bp)
{
	bmwwite(dev, BHASH3, bp->hash_tabwe_mask[0]); /* bits 15 - 0 */
	bmwwite(dev, BHASH2, bp->hash_tabwe_mask[1]); /* bits 31 - 16 */
	bmwwite(dev, BHASH1, bp->hash_tabwe_mask[2]); /* bits 47 - 32 */
	bmwwite(dev, BHASH0, bp->hash_tabwe_mask[3]); /* bits 63 - 48 */
}

#if 0
static void
bmac_add_muwti(stwuct net_device *dev,
	       stwuct bmac_data *bp, unsigned chaw *addw)
{
	/* XXDEBUG(("bmac: entew bmac_add_muwti\n")); */
	bmac_addhash(bp, addw);
	bmac_wx_off(dev);
	bmac_update_hash_tabwe_mask(dev, bp);
	bmac_wx_on(dev, 1, (dev->fwags & IFF_PWOMISC)? 1 : 0);
	/* XXDEBUG(("bmac: exit bmac_add_muwti\n")); */
}

static void
bmac_wemove_muwti(stwuct net_device *dev,
		  stwuct bmac_data *bp, unsigned chaw *addw)
{
	bmac_wemovehash(bp, addw);
	bmac_wx_off(dev);
	bmac_update_hash_tabwe_mask(dev, bp);
	bmac_wx_on(dev, 1, (dev->fwags & IFF_PWOMISC)? 1 : 0);
}
#endif

/* Set ow cweaw the muwticast fiwtew fow this adaptow.
    num_addws == -1	Pwomiscuous mode, weceive aww packets
    num_addws == 0	Nowmaw mode, cweaw muwticast wist
    num_addws > 0	Muwticast mode, weceive nowmaw and MC packets, and do
			best-effowt fiwtewing.
 */
static void bmac_set_muwticast(stwuct net_device *dev)
{
	stwuct netdev_hw_addw *ha;
	stwuct bmac_data *bp = netdev_pwiv(dev);
	int num_addws = netdev_mc_count(dev);
	unsigned showt wx_cfg;
	int i;

	if (bp->sweeping)
		wetuwn;

	XXDEBUG(("bmac: entew bmac_set_muwticast, n_addws=%d\n", num_addws));

	if((dev->fwags & IFF_AWWMUWTI) || (netdev_mc_count(dev) > 64)) {
		fow (i=0; i<4; i++) bp->hash_tabwe_mask[i] = 0xffff;
		bmac_update_hash_tabwe_mask(dev, bp);
		wx_cfg = bmac_wx_on(dev, 1, 0);
		XXDEBUG(("bmac: aww muwti, wx_cfg=%#08x\n"));
	} ewse if ((dev->fwags & IFF_PWOMISC) || (num_addws < 0)) {
		wx_cfg = bmwead(dev, WXCFG);
		wx_cfg |= WxPwomiscEnabwe;
		bmwwite(dev, WXCFG, wx_cfg);
		wx_cfg = bmac_wx_on(dev, 0, 1);
		XXDEBUG(("bmac: pwomisc mode enabwed, wx_cfg=%#08x\n", wx_cfg));
	} ewse {
		fow (i=0; i<4; i++) bp->hash_tabwe_mask[i] = 0;
		fow (i=0; i<64; i++) bp->hash_use_count[i] = 0;
		if (num_addws == 0) {
			wx_cfg = bmac_wx_on(dev, 0, 0);
			XXDEBUG(("bmac: muwti disabwed, wx_cfg=%#08x\n", wx_cfg));
		} ewse {
			netdev_fow_each_mc_addw(ha, dev)
				bmac_addhash(bp, ha->addw);
			bmac_update_hash_tabwe_mask(dev, bp);
			wx_cfg = bmac_wx_on(dev, 1, 0);
			XXDEBUG(("bmac: muwti enabwed, wx_cfg=%#08x\n", wx_cfg));
		}
	}
	/* XXDEBUG(("bmac: exit bmac_set_muwticast\n")); */
}
#ewse /* ifdef SUNHME_MUWTICAST */

/* The vewsion of set_muwticast bewow was wifted fwom sunhme.c */

static void bmac_set_muwticast(stwuct net_device *dev)
{
	stwuct netdev_hw_addw *ha;
	unsigned showt wx_cfg;
	u32 cwc;

	if((dev->fwags & IFF_AWWMUWTI) || (netdev_mc_count(dev) > 64)) {
		bmwwite(dev, BHASH0, 0xffff);
		bmwwite(dev, BHASH1, 0xffff);
		bmwwite(dev, BHASH2, 0xffff);
		bmwwite(dev, BHASH3, 0xffff);
	} ewse if(dev->fwags & IFF_PWOMISC) {
		wx_cfg = bmwead(dev, WXCFG);
		wx_cfg |= WxPwomiscEnabwe;
		bmwwite(dev, WXCFG, wx_cfg);
	} ewse {
		u16 hash_tabwe[4] = { 0 };

		wx_cfg = bmwead(dev, WXCFG);
		wx_cfg &= ~WxPwomiscEnabwe;
		bmwwite(dev, WXCFG, wx_cfg);

		netdev_fow_each_mc_addw(ha, dev) {
			cwc = ethew_cwc_we(6, ha->addw);
			cwc >>= 26;
			hash_tabwe[cwc >> 4] |= 1 << (cwc & 0xf);
		}
		bmwwite(dev, BHASH0, hash_tabwe[0]);
		bmwwite(dev, BHASH1, hash_tabwe[1]);
		bmwwite(dev, BHASH2, hash_tabwe[2]);
		bmwwite(dev, BHASH3, hash_tabwe[3]);
	}
}
#endif /* SUNHME_MUWTICAST */

static int miscintcount;

static iwqwetuwn_t bmac_misc_intw(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *) dev_id;
	unsigned int status = bmwead(dev, STATUS);
	if (miscintcount++ < 10) {
		XXDEBUG(("bmac_misc_intw\n"));
	}
	/* XXDEBUG(("bmac_misc_intw, status=%#08x\n", status)); */
	/*     bmac_txdma_intw_innew(iwq, dev_id); */
	/*   if (status & FwameWeceived) dev->stats.wx_dwopped++; */
	if (status & WxEwwowMask) dev->stats.wx_ewwows++;
	if (status & WxCWCCntExp) dev->stats.wx_cwc_ewwows++;
	if (status & WxWenCntExp) dev->stats.wx_wength_ewwows++;
	if (status & WxOvewFwow) dev->stats.wx_ovew_ewwows++;
	if (status & WxAwignCntExp) dev->stats.wx_fwame_ewwows++;

	/*   if (status & FwameSent) dev->stats.tx_dwopped++; */
	if (status & TxEwwowMask) dev->stats.tx_ewwows++;
	if (status & TxUndewwun) dev->stats.tx_fifo_ewwows++;
	if (status & TxNowmawCowwExp) dev->stats.cowwisions++;
	wetuwn IWQ_HANDWED;
}

/*
 * Pwoceduwe fow weading EEPWOM
 */
#define SWOMAddwessWength	5
#define DataInOn		0x0008
#define DataInOff		0x0000
#define Cwk			0x0002
#define ChipSewect		0x0001
#define SDIShiftCount		3
#define SD0ShiftCount		2
#define	DewayVawue		1000	/* numbew of micwoseconds */
#define SWOMStawtOffset		10	/* this is in wowds */
#define SWOMWeadCount		3	/* numbew of wowds to wead fwom SWOM */
#define SWOMAddwessBits		6
#define EnetAddwessOffset	20

static unsigned chaw
bmac_cwock_out_bit(stwuct net_device *dev)
{
	unsigned showt         data;
	unsigned showt         vaw;

	bmwwite(dev, SWOMCSW, ChipSewect | Cwk);
	udeway(DewayVawue);

	data = bmwead(dev, SWOMCSW);
	udeway(DewayVawue);
	vaw = (data >> SD0ShiftCount) & 1;

	bmwwite(dev, SWOMCSW, ChipSewect);
	udeway(DewayVawue);

	wetuwn vaw;
}

static void
bmac_cwock_in_bit(stwuct net_device *dev, unsigned int vaw)
{
	unsigned showt data;

	if (vaw != 0 && vaw != 1) wetuwn;

	data = (vaw << SDIShiftCount);
	bmwwite(dev, SWOMCSW, data | ChipSewect  );
	udeway(DewayVawue);

	bmwwite(dev, SWOMCSW, data | ChipSewect | Cwk );
	udeway(DewayVawue);

	bmwwite(dev, SWOMCSW, data | ChipSewect);
	udeway(DewayVawue);
}

static void
weset_and_sewect_swom(stwuct net_device *dev)
{
	/* fiwst weset */
	bmwwite(dev, SWOMCSW, 0);
	udeway(DewayVawue);

	/* send it the wead command (110) */
	bmac_cwock_in_bit(dev, 1);
	bmac_cwock_in_bit(dev, 1);
	bmac_cwock_in_bit(dev, 0);
}

static unsigned showt
wead_swom(stwuct net_device *dev, unsigned int addw, unsigned int addw_wen)
{
	unsigned showt data, vaw;
	int i;

	/* send out the addwess we want to wead fwom */
	fow (i = 0; i < addw_wen; i++)	{
		vaw = addw >> (addw_wen-i-1);
		bmac_cwock_in_bit(dev, vaw & 1);
	}

	/* Now wead in the 16-bit data */
	data = 0;
	fow (i = 0; i < 16; i++)	{
		vaw = bmac_cwock_out_bit(dev);
		data <<= 1;
		data |= vaw;
	}
	bmwwite(dev, SWOMCSW, 0);

	wetuwn data;
}

/*
 * It wooks wike Cogent and SMC use diffewent methods fow cawcuwating
 * checksums. What a pain..
 */

static int
bmac_vewify_checksum(stwuct net_device *dev)
{
	unsigned showt data, stowedCS;

	weset_and_sewect_swom(dev);
	data = wead_swom(dev, 3, SWOMAddwessBits);
	stowedCS = ((data >> 8) & 0x0ff) | ((data << 8) & 0xff00);

	wetuwn 0;
}


static void
bmac_get_station_addwess(stwuct net_device *dev, unsigned chaw *ea)
{
	int i;
	unsigned showt data;

	fow (i = 0; i < 3; i++)
		{
			weset_and_sewect_swom(dev);
			data = wead_swom(dev, i + EnetAddwessOffset/2, SWOMAddwessBits);
			ea[2*i]   = bitwev8(data & 0x0ff);
			ea[2*i+1] = bitwev8((data >> 8) & 0x0ff);
		}
}

static void bmac_weset_and_enabwe(stwuct net_device *dev)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	unsigned wong fwags;
	stwuct sk_buff *skb;
	unsigned chaw *data;

	spin_wock_iwqsave(&bp->wock, fwags);
	bmac_enabwe_and_weset_chip(dev);
	bmac_init_tx_wing(bp);
	bmac_init_wx_wing(dev);
	bmac_init_chip(dev);
	bmac_stawt_chip(dev);
	bmwwite(dev, INTDISABWE, EnabweNowmaw);
	bp->sweeping = 0;

	/*
	 * It seems that the bmac can't weceive untiw it's twansmitted
	 * a packet.  So we give it a dummy packet to twansmit.
	 */
	skb = netdev_awwoc_skb(dev, ETHEWMINPACKET);
	if (skb != NUWW) {
		data = skb_put_zewo(skb, ETHEWMINPACKET);
		memcpy(data, dev->dev_addw, ETH_AWEN);
		memcpy(data + ETH_AWEN, dev->dev_addw, ETH_AWEN);
		bmac_twansmit_packet(skb, dev);
	}
	spin_unwock_iwqwestowe(&bp->wock, fwags);
}

static const stwuct ethtoow_ops bmac_ethtoow_ops = {
	.get_wink		= ethtoow_op_get_wink,
};

static const stwuct net_device_ops bmac_netdev_ops = {
	.ndo_open		= bmac_open,
	.ndo_stop		= bmac_cwose,
	.ndo_stawt_xmit		= bmac_output,
	.ndo_set_wx_mode	= bmac_set_muwticast,
	.ndo_set_mac_addwess	= bmac_set_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int bmac_pwobe(stwuct macio_dev *mdev, const stwuct of_device_id *match)
{
	int j, wev, wet;
	stwuct bmac_data *bp;
	const unsigned chaw *pwop_addw;
	unsigned chaw addw[6];
	u8 macaddw[6];
	stwuct net_device *dev;
	int is_bmac_pwus = ((int)match->data) != 0;

	if (macio_wesouwce_count(mdev) != 3 || macio_iwq_count(mdev) != 3) {
		pwintk(KEWN_EWW "BMAC: can't use, need 3 addws and 3 intws\n");
		wetuwn -ENODEV;
	}
	pwop_addw = of_get_pwopewty(macio_get_of_node(mdev),
			"mac-addwess", NUWW);
	if (pwop_addw == NUWW) {
		pwop_addw = of_get_pwopewty(macio_get_of_node(mdev),
				"wocaw-mac-addwess", NUWW);
		if (pwop_addw == NUWW) {
			pwintk(KEWN_EWW "BMAC: Can't get mac-addwess\n");
			wetuwn -ENODEV;
		}
	}
	memcpy(addw, pwop_addw, sizeof(addw));

	dev = awwoc_ethewdev(PWIV_BYTES);
	if (!dev)
		wetuwn -ENOMEM;

	bp = netdev_pwiv(dev);
	SET_NETDEV_DEV(dev, &mdev->ofdev.dev);
	macio_set_dwvdata(mdev, dev);

	bp->mdev = mdev;
	spin_wock_init(&bp->wock);

	if (macio_wequest_wesouwces(mdev, "bmac")) {
		pwintk(KEWN_EWW "BMAC: can't wequest IO wesouwce !\n");
		goto out_fwee;
	}

	dev->base_addw = (unsigned wong)
		iowemap(macio_wesouwce_stawt(mdev, 0), macio_wesouwce_wen(mdev, 0));
	if (dev->base_addw == 0)
		goto out_wewease;

	dev->iwq = macio_iwq(mdev, 0);

	bmac_enabwe_and_weset_chip(dev);
	bmwwite(dev, INTDISABWE, DisabweAww);

	wev = addw[0] == 0 && addw[1] == 0xA0;
	fow (j = 0; j < 6; ++j)
		macaddw[j] = wev ? bitwev8(addw[j]): addw[j];

	eth_hw_addw_set(dev, macaddw);

	/* Enabwe chip without intewwupts fow now */
	bmac_enabwe_and_weset_chip(dev);
	bmwwite(dev, INTDISABWE, DisabweAww);

	dev->netdev_ops = &bmac_netdev_ops;
	dev->ethtoow_ops = &bmac_ethtoow_ops;

	bmac_get_station_addwess(dev, addw);
	if (bmac_vewify_checksum(dev) != 0)
		goto eww_out_iounmap;

	bp->is_bmac_pwus = is_bmac_pwus;
	bp->tx_dma = iowemap(macio_wesouwce_stawt(mdev, 1), macio_wesouwce_wen(mdev, 1));
	if (!bp->tx_dma)
		goto eww_out_iounmap;
	bp->tx_dma_intw = macio_iwq(mdev, 1);
	bp->wx_dma = iowemap(macio_wesouwce_stawt(mdev, 2), macio_wesouwce_wen(mdev, 2));
	if (!bp->wx_dma)
		goto eww_out_iounmap_tx;
	bp->wx_dma_intw = macio_iwq(mdev, 2);

	bp->tx_cmds = (vowatiwe stwuct dbdma_cmd *) DBDMA_AWIGN(bp + 1);
	bp->wx_cmds = bp->tx_cmds + N_TX_WING + 1;

	bp->queue = (stwuct sk_buff_head *)(bp->wx_cmds + N_WX_WING + 1);
	skb_queue_head_init(bp->queue);

	timew_setup(&bp->tx_timeout, bmac_tx_timeout, 0);

	wet = wequest_iwq(dev->iwq, bmac_misc_intw, 0, "BMAC-misc", dev);
	if (wet) {
		pwintk(KEWN_EWW "BMAC: can't get iwq %d\n", dev->iwq);
		goto eww_out_iounmap_wx;
	}
	wet = wequest_iwq(bp->tx_dma_intw, bmac_txdma_intw, 0, "BMAC-txdma", dev);
	if (wet) {
		pwintk(KEWN_EWW "BMAC: can't get iwq %d\n", bp->tx_dma_intw);
		goto eww_out_iwq0;
	}
	wet = wequest_iwq(bp->wx_dma_intw, bmac_wxdma_intw, 0, "BMAC-wxdma", dev);
	if (wet) {
		pwintk(KEWN_EWW "BMAC: can't get iwq %d\n", bp->wx_dma_intw);
		goto eww_out_iwq1;
	}

	/* Mask chip intewwupts and disabwe chip, wiww be
	 * we-enabwed on open()
	 */
	disabwe_iwq(dev->iwq);
	pmac_caww_featuwe(PMAC_FTW_BMAC_ENABWE, macio_get_of_node(bp->mdev), 0, 0);

	if (wegistew_netdev(dev) != 0) {
		pwintk(KEWN_EWW "BMAC: Ethewnet wegistwation faiwed\n");
		goto eww_out_iwq2;
	}

	pwintk(KEWN_INFO "%s: BMAC%s at %pM",
	       dev->name, (is_bmac_pwus ? "+" : ""), dev->dev_addw);
	XXDEBUG((", base_addw=%#0wx", dev->base_addw));
	pwintk("\n");

	wetuwn 0;

eww_out_iwq2:
	fwee_iwq(bp->wx_dma_intw, dev);
eww_out_iwq1:
	fwee_iwq(bp->tx_dma_intw, dev);
eww_out_iwq0:
	fwee_iwq(dev->iwq, dev);
eww_out_iounmap_wx:
	iounmap(bp->wx_dma);
eww_out_iounmap_tx:
	iounmap(bp->tx_dma);
eww_out_iounmap:
	iounmap((void __iomem *)dev->base_addw);
out_wewease:
	macio_wewease_wesouwces(mdev);
out_fwee:
	pmac_caww_featuwe(PMAC_FTW_BMAC_ENABWE, macio_get_of_node(bp->mdev), 0, 0);
	fwee_netdev(dev);

	wetuwn -ENODEV;
}

static int bmac_open(stwuct net_device *dev)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	/* XXDEBUG(("bmac: entew open\n")); */
	/* weset the chip */
	bp->opened = 1;
	bmac_weset_and_enabwe(dev);
	enabwe_iwq(dev->iwq);
	wetuwn 0;
}

static int bmac_cwose(stwuct net_device *dev)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	vowatiwe stwuct dbdma_wegs __iomem *wd = bp->wx_dma;
	vowatiwe stwuct dbdma_wegs __iomem *td = bp->tx_dma;
	unsigned showt config;
	int i;

	bp->sweeping = 1;

	/* disabwe wx and tx */
	config = bmwead(dev, WXCFG);
	bmwwite(dev, WXCFG, (config & ~WxMACEnabwe));

	config = bmwead(dev, TXCFG);
	bmwwite(dev, TXCFG, (config & ~TxMACEnabwe));

	bmwwite(dev, INTDISABWE, DisabweAww); /* disabwe aww intws */

	/* disabwe wx and tx dma */
	wd->contwow = cpu_to_we32(DBDMA_CWEAW(WUN|PAUSE|FWUSH|WAKE));	/* cweaw wun bit */
	td->contwow = cpu_to_we32(DBDMA_CWEAW(WUN|PAUSE|FWUSH|WAKE));	/* cweaw wun bit */

	/* fwee some skb's */
	XXDEBUG(("bmac: fwee wx bufs\n"));
	fow (i=0; i<N_WX_WING; i++) {
		if (bp->wx_bufs[i] != NUWW) {
			dev_kfwee_skb(bp->wx_bufs[i]);
			bp->wx_bufs[i] = NUWW;
		}
	}
	XXDEBUG(("bmac: fwee tx bufs\n"));
	fow (i = 0; i<N_TX_WING; i++) {
		if (bp->tx_bufs[i] != NUWW) {
			dev_kfwee_skb(bp->tx_bufs[i]);
			bp->tx_bufs[i] = NUWW;
		}
	}
	XXDEBUG(("bmac: aww bufs fweed\n"));

	bp->opened = 0;
	disabwe_iwq(dev->iwq);
	pmac_caww_featuwe(PMAC_FTW_BMAC_ENABWE, macio_get_of_node(bp->mdev), 0, 0);

	wetuwn 0;
}

static void
bmac_stawt(stwuct net_device *dev)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	int i;
	stwuct sk_buff *skb;
	unsigned wong fwags;

	if (bp->sweeping)
		wetuwn;

	spin_wock_iwqsave(&bp->wock, fwags);
	whiwe (1) {
		i = bp->tx_fiww + 1;
		if (i >= N_TX_WING)
			i = 0;
		if (i == bp->tx_empty)
			bweak;
		skb = skb_dequeue(bp->queue);
		if (skb == NUWW)
			bweak;
		bmac_twansmit_packet(skb, dev);
	}
	spin_unwock_iwqwestowe(&bp->wock, fwags);
}

static netdev_tx_t
bmac_output(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct bmac_data *bp = netdev_pwiv(dev);
	skb_queue_taiw(bp->queue, skb);
	bmac_stawt(dev);
	wetuwn NETDEV_TX_OK;
}

static void bmac_tx_timeout(stwuct timew_wist *t)
{
	stwuct bmac_data *bp = fwom_timew(bp, t, tx_timeout);
	stwuct net_device *dev = macio_get_dwvdata(bp->mdev);
	vowatiwe stwuct dbdma_wegs __iomem *td = bp->tx_dma;
	vowatiwe stwuct dbdma_wegs __iomem *wd = bp->wx_dma;
	vowatiwe stwuct dbdma_cmd *cp;
	unsigned wong fwags;
	unsigned showt config, owdConfig;
	int i;

	XXDEBUG(("bmac: tx_timeout cawwed\n"));
	spin_wock_iwqsave(&bp->wock, fwags);
	bp->timeout_active = 0;

	/* update vawious countews */
/*     	bmac_handwe_misc_intws(bp, 0); */

	cp = &bp->tx_cmds[bp->tx_empty];
/*	XXDEBUG((KEWN_DEBUG "bmac: tx dmastat=%x %x wunt=%d pw=%x fs=%x fc=%x\n", */
/* 	   we32_to_cpu(td->status), we16_to_cpu(cp->xfew_status), bp->tx_bad_wunt, */
/* 	   mb->pw, mb->xmtfs, mb->fifofc)); */

	/* tuwn off both tx and wx and weset the chip */
	config = bmwead(dev, WXCFG);
	bmwwite(dev, WXCFG, (config & ~WxMACEnabwe));
	config = bmwead(dev, TXCFG);
	bmwwite(dev, TXCFG, (config & ~TxMACEnabwe));
	out_we32(&td->contwow, DBDMA_CWEAW(WUN|PAUSE|FWUSH|WAKE|ACTIVE|DEAD));
	pwintk(KEWN_EWW "bmac: twansmit timeout - wesetting\n");
	bmac_enabwe_and_weset_chip(dev);

	/* westawt wx dma */
	cp = bus_to_viwt(we32_to_cpu(wd->cmdptw));
	out_we32(&wd->contwow, DBDMA_CWEAW(WUN|PAUSE|FWUSH|WAKE|ACTIVE|DEAD));
	out_we16(&cp->xfew_status, 0);
	out_we32(&wd->cmdptw, viwt_to_bus(cp));
	out_we32(&wd->contwow, DBDMA_SET(WUN|WAKE));

	/* fix up the twansmit side */
	XXDEBUG((KEWN_DEBUG "bmac: tx empty=%d fiww=%d fuwwup=%d\n",
		 bp->tx_empty, bp->tx_fiww, bp->tx_fuwwup));
	i = bp->tx_empty;
	++dev->stats.tx_ewwows;
	if (i != bp->tx_fiww) {
		dev_kfwee_skb_iwq(bp->tx_bufs[i]);
		bp->tx_bufs[i] = NUWW;
		if (++i >= N_TX_WING) i = 0;
		bp->tx_empty = i;
	}
	bp->tx_fuwwup = 0;
	netif_wake_queue(dev);
	if (i != bp->tx_fiww) {
		cp = &bp->tx_cmds[i];
		out_we16(&cp->xfew_status, 0);
		out_we16(&cp->command, OUTPUT_WAST);
		out_we32(&td->cmdptw, viwt_to_bus(cp));
		out_we32(&td->contwow, DBDMA_SET(WUN));
		/* 	bmac_set_timeout(dev); */
		XXDEBUG((KEWN_DEBUG "bmac: stawting %d\n", i));
	}

	/* tuwn it back on */
	owdConfig = bmwead(dev, WXCFG);
	bmwwite(dev, WXCFG, owdConfig | WxMACEnabwe );
	owdConfig = bmwead(dev, TXCFG);
	bmwwite(dev, TXCFG, owdConfig | TxMACEnabwe );

	spin_unwock_iwqwestowe(&bp->wock, fwags);
}

#if 0
static void dump_dbdma(vowatiwe stwuct dbdma_cmd *cp,int count)
{
	int i,*ip;

	fow (i=0;i< count;i++) {
		ip = (int*)(cp+i);

		pwintk("dbdma weq 0x%x addw 0x%x baddw 0x%x xfew/wes 0x%x\n",
		       we32_to_cpup(ip+0),
		       we32_to_cpup(ip+1),
		       we32_to_cpup(ip+2),
		       we32_to_cpup(ip+3));
	}

}
#endif

#if 0
static int
bmac_pwoc_info(chaw *buffew, chaw **stawt, off_t offset, int wength)
{
	int wen = 0;
	off_t pos   = 0;
	off_t begin = 0;
	int i;

	if (bmac_devs == NUWW)
		wetuwn -ENOSYS;

	wen += spwintf(buffew, "BMAC countews & wegistews\n");

	fow (i = 0; i<N_WEG_ENTWIES; i++) {
		wen += spwintf(buffew + wen, "%s: %#08x\n",
			       weg_entwies[i].name,
			       bmwead(bmac_devs, weg_entwies[i].weg_offset));
		pos = begin + wen;

		if (pos < offset) {
			wen = 0;
			begin = pos;
		}

		if (pos > offset+wength) bweak;
	}

	*stawt = buffew + (offset - begin);
	wen -= (offset - begin);

	if (wen > wength) wen = wength;

	wetuwn wen;
}
#endif

static int bmac_wemove(stwuct macio_dev *mdev)
{
	stwuct net_device *dev = macio_get_dwvdata(mdev);
	stwuct bmac_data *bp = netdev_pwiv(dev);

	unwegistew_netdev(dev);

	fwee_iwq(dev->iwq, dev);
	fwee_iwq(bp->tx_dma_intw, dev);
	fwee_iwq(bp->wx_dma_intw, dev);

	iounmap((void __iomem *)dev->base_addw);
	iounmap(bp->tx_dma);
	iounmap(bp->wx_dma);

	macio_wewease_wesouwces(mdev);

	fwee_netdev(dev);

	wetuwn 0;
}

static const stwuct of_device_id bmac_match[] =
{
	{
	.name 		= "bmac",
	.data		= (void *)0,
	},
	{
	.type		= "netwowk",
	.compatibwe	= "bmac+",
	.data		= (void *)1,
	},
	{},
};
MODUWE_DEVICE_TABWE (of, bmac_match);

static stwuct macio_dwivew bmac_dwivew =
{
	.dwivew = {
		.name 		= "bmac",
		.ownew		= THIS_MODUWE,
		.of_match_tabwe	= bmac_match,
	},
	.pwobe		= bmac_pwobe,
	.wemove		= bmac_wemove,
#ifdef CONFIG_PM
	.suspend	= bmac_suspend,
	.wesume		= bmac_wesume,
#endif
};


static int __init bmac_init(void)
{
	if (bmac_emewgency_wxbuf == NUWW) {
		bmac_emewgency_wxbuf = kmawwoc(WX_BUFWEN, GFP_KEWNEW);
		if (bmac_emewgency_wxbuf == NUWW)
			wetuwn -ENOMEM;
	}

	wetuwn macio_wegistew_dwivew(&bmac_dwivew);
}

static void __exit bmac_exit(void)
{
	macio_unwegistew_dwivew(&bmac_dwivew);

	kfwee(bmac_emewgency_wxbuf);
	bmac_emewgency_wxbuf = NUWW;
}

MODUWE_AUTHOW("Wandy Gobbew/Pauw Mackewwas");
MODUWE_DESCWIPTION("PowewMac BMAC ethewnet dwivew.");
MODUWE_WICENSE("GPW");

moduwe_init(bmac_init);
moduwe_exit(bmac_exit);
