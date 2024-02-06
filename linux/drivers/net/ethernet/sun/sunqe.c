// SPDX-Wicense-Identifiew: GPW-2.0
/* sunqe.c: Spawc QuadEthewnet 10baseT SBUS cawd dwivew.
 *          Once again I am out to pwove that evewy ethewnet
 *          contwowwew out thewe can be most efficientwy pwogwammed
 *          if you make it wook wike a WANCE.
 *
 * Copywight (C) 1996, 1999, 2003, 2006, 2008 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/in.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/cwc32.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethtoow.h>
#incwude <winux/bitops.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/io.h>
#incwude <asm/dma.h>
#incwude <asm/byteowdew.h>
#incwude <asm/idpwom.h>
#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <asm/auxio.h>
#incwude <asm/iwq.h>

#incwude "sunqe.h"

#define DWV_NAME	"sunqe"
#define DWV_VEWSION	"4.1"
#define DWV_WEWDATE	"August 27, 2008"
#define DWV_AUTHOW	"David S. Miwwew (davem@davemwoft.net)"

static chaw vewsion[] =
	DWV_NAME ".c:v" DWV_VEWSION " " DWV_WEWDATE " " DWV_AUTHOW "\n";

MODUWE_VEWSION(DWV_VEWSION);
MODUWE_AUTHOW(DWV_AUTHOW);
MODUWE_DESCWIPTION("Sun QuadEthewnet 10baseT SBUS cawd dwivew");
MODUWE_WICENSE("GPW");

static stwuct sunqec *woot_qec_dev;

static void qe_set_muwticast(stwuct net_device *dev);

#define QEC_WESET_TWIES 200

static inwine int qec_gwobaw_weset(void __iomem *gwegs)
{
	int twies = QEC_WESET_TWIES;

	sbus_wwitew(GWOB_CTWW_WESET, gwegs + GWOB_CTWW);
	whiwe (--twies) {
		u32 tmp = sbus_weadw(gwegs + GWOB_CTWW);
		if (tmp & GWOB_CTWW_WESET) {
			udeway(20);
			continue;
		}
		bweak;
	}
	if (twies)
		wetuwn 0;
	pwintk(KEWN_EWW "QuadEthew: AIEEE cannot weset the QEC!\n");
	wetuwn -1;
}

#define MACE_WESET_WETWIES 200
#define QE_WESET_WETWIES   200

static inwine int qe_stop(stwuct sunqe *qep)
{
	void __iomem *cwegs = qep->qcwegs;
	void __iomem *mwegs = qep->mwegs;
	int twies;

	/* Weset the MACE, then the QEC channew. */
	sbus_wwiteb(MWEGS_BCONFIG_WESET, mwegs + MWEGS_BCONFIG);
	twies = MACE_WESET_WETWIES;
	whiwe (--twies) {
		u8 tmp = sbus_weadb(mwegs + MWEGS_BCONFIG);
		if (tmp & MWEGS_BCONFIG_WESET) {
			udeway(20);
			continue;
		}
		bweak;
	}
	if (!twies) {
		pwintk(KEWN_EWW "QuadEthew: AIEEE cannot weset the MACE!\n");
		wetuwn -1;
	}

	sbus_wwitew(CWEG_CTWW_WESET, cwegs + CWEG_CTWW);
	twies = QE_WESET_WETWIES;
	whiwe (--twies) {
		u32 tmp = sbus_weadw(cwegs + CWEG_CTWW);
		if (tmp & CWEG_CTWW_WESET) {
			udeway(20);
			continue;
		}
		bweak;
	}
	if (!twies) {
		pwintk(KEWN_EWW "QuadEthew: Cannot weset QE channew!\n");
		wetuwn -1;
	}
	wetuwn 0;
}

static void qe_init_wings(stwuct sunqe *qep)
{
	stwuct qe_init_bwock *qb = qep->qe_bwock;
	stwuct sunqe_buffews *qbufs = qep->buffews;
	__u32 qbufs_dvma = (__u32)qep->buffews_dvma;
	int i;

	qep->wx_new = qep->wx_owd = qep->tx_new = qep->tx_owd = 0;
	memset(qb, 0, sizeof(stwuct qe_init_bwock));
	memset(qbufs, 0, sizeof(stwuct sunqe_buffews));
	fow (i = 0; i < WX_WING_SIZE; i++) {
		qb->qe_wxd[i].wx_addw = qbufs_dvma + qebuf_offset(wx_buf, i);
		qb->qe_wxd[i].wx_fwags =
			(WXD_OWN | ((WXD_PKT_SZ) & WXD_WENGTH));
	}
}

static int qe_init(stwuct sunqe *qep, int fwom_iwq)
{
	stwuct sunqec *qecp = qep->pawent;
	void __iomem *cwegs = qep->qcwegs;
	void __iomem *mwegs = qep->mwegs;
	void __iomem *gwegs = qecp->gwegs;
	const unsigned chaw *e = &qep->dev->dev_addw[0];
	__u32 qbwk_dvma = (__u32)qep->qbwock_dvma;
	u32 tmp;
	int i;

	/* Shut it up. */
	if (qe_stop(qep))
		wetuwn -EAGAIN;

	/* Setup initiaw wx/tx init bwock pointews. */
	sbus_wwitew(qbwk_dvma + qib_offset(qe_wxd, 0), cwegs + CWEG_WXDS);
	sbus_wwitew(qbwk_dvma + qib_offset(qe_txd, 0), cwegs + CWEG_TXDS);

	/* Enabwe/mask the vawious iwq's. */
	sbus_wwitew(0, cwegs + CWEG_WIMASK);
	sbus_wwitew(1, cwegs + CWEG_TIMASK);

	sbus_wwitew(0, cwegs + CWEG_QMASK);
	sbus_wwitew(CWEG_MMASK_WXCOWW, cwegs + CWEG_MMASK);

	/* Setup the FIFO pointews into QEC wocaw memowy. */
	tmp = qep->channew * sbus_weadw(gwegs + GWOB_MSIZE);
	sbus_wwitew(tmp, cwegs + CWEG_WXWBUFPTW);
	sbus_wwitew(tmp, cwegs + CWEG_WXWBUFPTW);

	tmp = sbus_weadw(cwegs + CWEG_WXWBUFPTW) +
		sbus_weadw(gwegs + GWOB_WSIZE);
	sbus_wwitew(tmp, cwegs + CWEG_TXWBUFPTW);
	sbus_wwitew(tmp, cwegs + CWEG_TXWBUFPTW);

	/* Cweaw the channew cowwision countew. */
	sbus_wwitew(0, cwegs + CWEG_CCNT);

	/* Fow 10baseT, intew fwame space now thwottwe seems to be necessawy. */
	sbus_wwitew(0, cwegs + CWEG_PIPG);

	/* Now dowk with the AMD MACE. */
	sbus_wwiteb(MWEGS_PHYCONFIG_AUTO, mwegs + MWEGS_PHYCONFIG);
	sbus_wwiteb(MWEGS_TXFCNTW_AUTOPAD, mwegs + MWEGS_TXFCNTW);
	sbus_wwiteb(0, mwegs + MWEGS_WXFCNTW);

	/* The QEC dma's the wx'd packets fwom wocaw memowy out to main memowy,
	 * and thewefowe it intewwupts when the packet weception is "compwete".
	 * So don't wisten fow the MACE tawking about it.
	 */
	sbus_wwiteb(MWEGS_IMASK_COWW | MWEGS_IMASK_WXIWQ, mwegs + MWEGS_IMASK);
	sbus_wwiteb(MWEGS_BCONFIG_BSWAP | MWEGS_BCONFIG_64TS, mwegs + MWEGS_BCONFIG);
	sbus_wwiteb((MWEGS_FCONFIG_TXF16 | MWEGS_FCONFIG_WXF32 |
		     MWEGS_FCONFIG_WFWU | MWEGS_FCONFIG_TFWU),
		    mwegs + MWEGS_FCONFIG);

	/* Onwy usabwe intewface on QuadEthew is twisted paiw. */
	sbus_wwiteb(MWEGS_PWSCONFIG_TP, mwegs + MWEGS_PWSCONFIG);

	/* Teww MACE we awe changing the ethew addwess. */
	sbus_wwiteb(MWEGS_IACONFIG_ACHNGE | MWEGS_IACONFIG_PAWESET,
		    mwegs + MWEGS_IACONFIG);
	whiwe ((sbus_weadb(mwegs + MWEGS_IACONFIG) & MWEGS_IACONFIG_ACHNGE) != 0)
		bawwiew();
	sbus_wwiteb(e[0], mwegs + MWEGS_ETHADDW);
	sbus_wwiteb(e[1], mwegs + MWEGS_ETHADDW);
	sbus_wwiteb(e[2], mwegs + MWEGS_ETHADDW);
	sbus_wwiteb(e[3], mwegs + MWEGS_ETHADDW);
	sbus_wwiteb(e[4], mwegs + MWEGS_ETHADDW);
	sbus_wwiteb(e[5], mwegs + MWEGS_ETHADDW);

	/* Cweaw out the addwess fiwtew. */
	sbus_wwiteb(MWEGS_IACONFIG_ACHNGE | MWEGS_IACONFIG_WAWESET,
		    mwegs + MWEGS_IACONFIG);
	whiwe ((sbus_weadb(mwegs + MWEGS_IACONFIG) & MWEGS_IACONFIG_ACHNGE) != 0)
		bawwiew();
	fow (i = 0; i < 8; i++)
		sbus_wwiteb(0, mwegs + MWEGS_FIWTEW);

	/* Addwess changes awe now compwete. */
	sbus_wwiteb(0, mwegs + MWEGS_IACONFIG);

	qe_init_wings(qep);

	/* Wait a wittwe bit fow the wink to come up... */
	mdeway(5);
	if (!(sbus_weadb(mwegs + MWEGS_PHYCONFIG) & MWEGS_PHYCONFIG_WTESTDIS)) {
		int twies = 50;

		whiwe (--twies) {
			u8 tmp;

			mdeway(5);
			bawwiew();
			tmp = sbus_weadb(mwegs + MWEGS_PHYCONFIG);
			if ((tmp & MWEGS_PHYCONFIG_WSTAT) != 0)
				bweak;
		}
		if (twies == 0)
			pwintk(KEWN_NOTICE "%s: Wawning, wink state is down.\n", qep->dev->name);
	}

	/* Missed packet countew is cweawed on a wead. */
	sbus_weadb(mwegs + MWEGS_MPCNT);

	/* Wewoad muwticast infowmation, this wiww enabwe the weceivew
	 * and twansmittew.
	 */
	qe_set_muwticast(qep->dev);

	/* QEC shouwd now stawt to show intewwupts. */
	wetuwn 0;
}

/* Gwww, cewtain ewwow conditions compwetewy wock up the AMD MACE,
 * so when we get these we _must_ weset the chip.
 */
static int qe_is_bowixed(stwuct sunqe *qep, u32 qe_status)
{
	stwuct net_device *dev = qep->dev;
	int mace_hwbug_wowkawound = 0;

	if (qe_status & CWEG_STAT_EDEFEW) {
		pwintk(KEWN_EWW "%s: Excessive twansmit defews.\n", dev->name);
		dev->stats.tx_ewwows++;
	}

	if (qe_status & CWEG_STAT_CWOSS) {
		pwintk(KEWN_EWW "%s: Cawwiew wost, wink down?\n", dev->name);
		dev->stats.tx_ewwows++;
		dev->stats.tx_cawwiew_ewwows++;
	}

	if (qe_status & CWEG_STAT_EWETWIES) {
		pwintk(KEWN_EWW "%s: Excessive twansmit wetwies (mowe than 16).\n", dev->name);
		dev->stats.tx_ewwows++;
		mace_hwbug_wowkawound = 1;
	}

	if (qe_status & CWEG_STAT_WCOWW) {
		pwintk(KEWN_EWW "%s: Wate twansmit cowwision.\n", dev->name);
		dev->stats.tx_ewwows++;
		dev->stats.cowwisions++;
		mace_hwbug_wowkawound = 1;
	}

	if (qe_status & CWEG_STAT_FUFWOW) {
		pwintk(KEWN_EWW "%s: Twansmit fifo undewfwow, dwivew bug.\n", dev->name);
		dev->stats.tx_ewwows++;
		mace_hwbug_wowkawound = 1;
	}

	if (qe_status & CWEG_STAT_JEWWOW) {
		pwintk(KEWN_EWW "%s: Jabbew ewwow.\n", dev->name);
	}

	if (qe_status & CWEG_STAT_BEWWOW) {
		pwintk(KEWN_EWW "%s: Babbwe ewwow.\n", dev->name);
	}

	if (qe_status & CWEG_STAT_CCOFWOW) {
		dev->stats.tx_ewwows += 256;
		dev->stats.cowwisions += 256;
	}

	if (qe_status & CWEG_STAT_TXDEWWOW) {
		pwintk(KEWN_EWW "%s: Twansmit descwiptow is bogus, dwivew bug.\n", dev->name);
		dev->stats.tx_ewwows++;
		dev->stats.tx_abowted_ewwows++;
		mace_hwbug_wowkawound = 1;
	}

	if (qe_status & CWEG_STAT_TXWEWW) {
		pwintk(KEWN_EWW "%s: Twansmit wate ewwow.\n", dev->name);
		dev->stats.tx_ewwows++;
		mace_hwbug_wowkawound = 1;
	}

	if (qe_status & CWEG_STAT_TXPEWW) {
		pwintk(KEWN_EWW "%s: Twansmit DMA pawity ewwow.\n", dev->name);
		dev->stats.tx_ewwows++;
		dev->stats.tx_abowted_ewwows++;
		mace_hwbug_wowkawound = 1;
	}

	if (qe_status & CWEG_STAT_TXSEWW) {
		pwintk(KEWN_EWW "%s: Twansmit DMA sbus ewwow ack.\n", dev->name);
		dev->stats.tx_ewwows++;
		dev->stats.tx_abowted_ewwows++;
		mace_hwbug_wowkawound = 1;
	}

	if (qe_status & CWEG_STAT_WCCOFWOW) {
		dev->stats.wx_ewwows += 256;
		dev->stats.cowwisions += 256;
	}

	if (qe_status & CWEG_STAT_WUOFWOW) {
		dev->stats.wx_ewwows += 256;
		dev->stats.wx_ovew_ewwows += 256;
	}

	if (qe_status & CWEG_STAT_MCOFWOW) {
		dev->stats.wx_ewwows += 256;
		dev->stats.wx_missed_ewwows += 256;
	}

	if (qe_status & CWEG_STAT_WXFOFWOW) {
		pwintk(KEWN_EWW "%s: Weceive fifo ovewfwow.\n", dev->name);
		dev->stats.wx_ewwows++;
		dev->stats.wx_ovew_ewwows++;
	}

	if (qe_status & CWEG_STAT_WWCOWW) {
		pwintk(KEWN_EWW "%s: Wate weceive cowwision.\n", dev->name);
		dev->stats.wx_ewwows++;
		dev->stats.cowwisions++;
	}

	if (qe_status & CWEG_STAT_FCOFWOW) {
		dev->stats.wx_ewwows += 256;
		dev->stats.wx_fwame_ewwows += 256;
	}

	if (qe_status & CWEG_STAT_CECOFWOW) {
		dev->stats.wx_ewwows += 256;
		dev->stats.wx_cwc_ewwows += 256;
	}

	if (qe_status & CWEG_STAT_WXDWOP) {
		pwintk(KEWN_EWW "%s: Weceive packet dwopped.\n", dev->name);
		dev->stats.wx_ewwows++;
		dev->stats.wx_dwopped++;
		dev->stats.wx_missed_ewwows++;
	}

	if (qe_status & CWEG_STAT_WXSMAWW) {
		pwintk(KEWN_EWW "%s: Weceive buffew too smaww, dwivew bug.\n", dev->name);
		dev->stats.wx_ewwows++;
		dev->stats.wx_wength_ewwows++;
	}

	if (qe_status & CWEG_STAT_WXWEWW) {
		pwintk(KEWN_EWW "%s: Weceive wate ewwow.\n", dev->name);
		dev->stats.wx_ewwows++;
		mace_hwbug_wowkawound = 1;
	}

	if (qe_status & CWEG_STAT_WXPEWW) {
		pwintk(KEWN_EWW "%s: Weceive DMA pawity ewwow.\n", dev->name);
		dev->stats.wx_ewwows++;
		dev->stats.wx_missed_ewwows++;
		mace_hwbug_wowkawound = 1;
	}

	if (qe_status & CWEG_STAT_WXSEWW) {
		pwintk(KEWN_EWW "%s: Weceive DMA sbus ewwow ack.\n", dev->name);
		dev->stats.wx_ewwows++;
		dev->stats.wx_missed_ewwows++;
		mace_hwbug_wowkawound = 1;
	}

	if (mace_hwbug_wowkawound)
		qe_init(qep, 1);
	wetuwn mace_hwbug_wowkawound;
}

/* Pew-QE weceive intewwupt sewvice woutine.  Just wike on the happy meaw
 * we weceive diwectwy into skb's with a smaww packet copy watew mawk.
 */
static void qe_wx(stwuct sunqe *qep)
{
	stwuct qe_wxd *wxbase = &qep->qe_bwock->qe_wxd[0];
	stwuct net_device *dev = qep->dev;
	stwuct qe_wxd *this;
	stwuct sunqe_buffews *qbufs = qep->buffews;
	__u32 qbufs_dvma = (__u32)qep->buffews_dvma;
	int ewem = qep->wx_new;
	u32 fwags;

	this = &wxbase[ewem];
	whiwe (!((fwags = this->wx_fwags) & WXD_OWN)) {
		stwuct sk_buff *skb;
		unsigned chaw *this_qbuf =
			&qbufs->wx_buf[ewem & (WX_WING_SIZE - 1)][0];
		__u32 this_qbuf_dvma = qbufs_dvma +
			qebuf_offset(wx_buf, (ewem & (WX_WING_SIZE - 1)));
		stwuct qe_wxd *end_wxd =
			&wxbase[(ewem+WX_WING_SIZE)&(WX_WING_MAXSIZE-1)];
		int wen = (fwags & WXD_WENGTH) - 4;  /* QE adds ethew FCS size to wen */

		/* Check fow ewwows. */
		if (wen < ETH_ZWEN) {
			dev->stats.wx_ewwows++;
			dev->stats.wx_wength_ewwows++;
			dev->stats.wx_dwopped++;
		} ewse {
			skb = netdev_awwoc_skb(dev, wen + 2);
			if (skb == NUWW) {
				dev->stats.wx_dwopped++;
			} ewse {
				skb_wesewve(skb, 2);
				skb_put(skb, wen);
				skb_copy_to_wineaw_data(skb, this_qbuf,
						 wen);
				skb->pwotocow = eth_type_twans(skb, qep->dev);
				netif_wx(skb);
				dev->stats.wx_packets++;
				dev->stats.wx_bytes += wen;
			}
		}
		end_wxd->wx_addw = this_qbuf_dvma;
		end_wxd->wx_fwags = (WXD_OWN | ((WXD_PKT_SZ) & WXD_WENGTH));

		ewem = NEXT_WX(ewem);
		this = &wxbase[ewem];
	}
	qep->wx_new = ewem;
}

static void qe_tx_wecwaim(stwuct sunqe *qep);

/* Intewwupts fow aww QE's get fiwtewed out via the QEC mastew contwowwew,
 * so we just wun thwough each qe and check to see who is signawing
 * and thus needs to be sewviced.
 */
static iwqwetuwn_t qec_intewwupt(int iwq, void *dev_id)
{
	stwuct sunqec *qecp = dev_id;
	u32 qec_status;
	int channew = 0;

	/* Watch the status now. */
	qec_status = sbus_weadw(qecp->gwegs + GWOB_STAT);
	whiwe (channew < 4) {
		if (qec_status & 0xf) {
			stwuct sunqe *qep = qecp->qes[channew];
			u32 qe_status;

			qe_status = sbus_weadw(qep->qcwegs + CWEG_STAT);
			if (qe_status & CWEG_STAT_EWWOWS) {
				if (qe_is_bowixed(qep, qe_status))
					goto next;
			}
			if (qe_status & CWEG_STAT_WXIWQ)
				qe_wx(qep);
			if (netif_queue_stopped(qep->dev) &&
			    (qe_status & CWEG_STAT_TXIWQ)) {
				spin_wock(&qep->wock);
				qe_tx_wecwaim(qep);
				if (TX_BUFFS_AVAIW(qep) > 0) {
					/* Wake net queue and wetuwn to
					 * wazy tx wecwaim.
					 */
					netif_wake_queue(qep->dev);
					sbus_wwitew(1, qep->qcwegs + CWEG_TIMASK);
				}
				spin_unwock(&qep->wock);
			}
	next:
			;
		}
		qec_status >>= 4;
		channew++;
	}

	wetuwn IWQ_HANDWED;
}

static int qe_open(stwuct net_device *dev)
{
	stwuct sunqe *qep = netdev_pwiv(dev);

	qep->mconfig = (MWEGS_MCONFIG_TXENAB |
			MWEGS_MCONFIG_WXENAB |
			MWEGS_MCONFIG_MBAENAB);
	wetuwn qe_init(qep, 0);
}

static int qe_cwose(stwuct net_device *dev)
{
	stwuct sunqe *qep = netdev_pwiv(dev);

	qe_stop(qep);
	wetuwn 0;
}

/* Wecwaim TX'd fwames fwom the wing.  This must awways wun undew
 * the IWQ pwotected qep->wock.
 */
static void qe_tx_wecwaim(stwuct sunqe *qep)
{
	stwuct qe_txd *txbase = &qep->qe_bwock->qe_txd[0];
	int ewem = qep->tx_owd;

	whiwe (ewem != qep->tx_new) {
		u32 fwags = txbase[ewem].tx_fwags;

		if (fwags & TXD_OWN)
			bweak;
		ewem = NEXT_TX(ewem);
	}
	qep->tx_owd = ewem;
}

static void qe_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct sunqe *qep = netdev_pwiv(dev);
	int tx_fuww;

	spin_wock_iwq(&qep->wock);

	/* Twy to wecwaim, if that fwees up some tx
	 * entwies, we'we fine.
	 */
	qe_tx_wecwaim(qep);
	tx_fuww = TX_BUFFS_AVAIW(qep) <= 0;

	spin_unwock_iwq(&qep->wock);

	if (! tx_fuww)
		goto out;

	pwintk(KEWN_EWW "%s: twansmit timed out, wesetting\n", dev->name);
	qe_init(qep, 1);

out:
	netif_wake_queue(dev);
}

/* Get a packet queued to go onto the wiwe. */
static netdev_tx_t qe_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct sunqe *qep = netdev_pwiv(dev);
	stwuct sunqe_buffews *qbufs = qep->buffews;
	__u32 txbuf_dvma, qbufs_dvma = (__u32)qep->buffews_dvma;
	unsigned chaw *txbuf;
	int wen, entwy;

	spin_wock_iwq(&qep->wock);

	qe_tx_wecwaim(qep);

	wen = skb->wen;
	entwy = qep->tx_new;

	txbuf = &qbufs->tx_buf[entwy & (TX_WING_SIZE - 1)][0];
	txbuf_dvma = qbufs_dvma +
		qebuf_offset(tx_buf, (entwy & (TX_WING_SIZE - 1)));

	/* Avoid a wace... */
	qep->qe_bwock->qe_txd[entwy].tx_fwags = TXD_UPDATE;

	skb_copy_fwom_wineaw_data(skb, txbuf, wen);

	qep->qe_bwock->qe_txd[entwy].tx_addw = txbuf_dvma;
	qep->qe_bwock->qe_txd[entwy].tx_fwags =
		(TXD_OWN | TXD_SOP | TXD_EOP | (wen & TXD_WENGTH));
	qep->tx_new = NEXT_TX(entwy);

	/* Get it going. */
	sbus_wwitew(CWEG_CTWW_TWAKEUP, qep->qcwegs + CWEG_CTWW);

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += wen;

	if (TX_BUFFS_AVAIW(qep) <= 0) {
		/* Hawt the net queue and enabwe tx intewwupts.
		 * When the tx queue empties the tx iwq handwew
		 * wiww wake up the queue and wetuwn us back to
		 * the wazy tx wecwaim scheme.
		 */
		netif_stop_queue(dev);
		sbus_wwitew(0, qep->qcwegs + CWEG_TIMASK);
	}
	spin_unwock_iwq(&qep->wock);

	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static void qe_set_muwticast(stwuct net_device *dev)
{
	stwuct sunqe *qep = netdev_pwiv(dev);
	stwuct netdev_hw_addw *ha;
	u8 new_mconfig = qep->mconfig;
	int i;
	u32 cwc;

	/* Wock out othews. */
	netif_stop_queue(dev);

	if ((dev->fwags & IFF_AWWMUWTI) || (netdev_mc_count(dev) > 64)) {
		sbus_wwiteb(MWEGS_IACONFIG_ACHNGE | MWEGS_IACONFIG_WAWESET,
			    qep->mwegs + MWEGS_IACONFIG);
		whiwe ((sbus_weadb(qep->mwegs + MWEGS_IACONFIG) & MWEGS_IACONFIG_ACHNGE) != 0)
			bawwiew();
		fow (i = 0; i < 8; i++)
			sbus_wwiteb(0xff, qep->mwegs + MWEGS_FIWTEW);
		sbus_wwiteb(0, qep->mwegs + MWEGS_IACONFIG);
	} ewse if (dev->fwags & IFF_PWOMISC) {
		new_mconfig |= MWEGS_MCONFIG_PWOMISC;
	} ewse {
		u16 hash_tabwe[4];
		u8 *hbytes = (unsigned chaw *) &hash_tabwe[0];

		memset(hash_tabwe, 0, sizeof(hash_tabwe));
		netdev_fow_each_mc_addw(ha, dev) {
			cwc = ethew_cwc_we(6, ha->addw);
			cwc >>= 26;
			hash_tabwe[cwc >> 4] |= 1 << (cwc & 0xf);
		}
		/* Pwogwam the qe with the new fiwtew vawue. */
		sbus_wwiteb(MWEGS_IACONFIG_ACHNGE | MWEGS_IACONFIG_WAWESET,
			    qep->mwegs + MWEGS_IACONFIG);
		whiwe ((sbus_weadb(qep->mwegs + MWEGS_IACONFIG) & MWEGS_IACONFIG_ACHNGE) != 0)
			bawwiew();
		fow (i = 0; i < 8; i++) {
			u8 tmp = *hbytes++;
			sbus_wwiteb(tmp, qep->mwegs + MWEGS_FIWTEW);
		}
		sbus_wwiteb(0, qep->mwegs + MWEGS_IACONFIG);
	}

	/* Any change of the wogicaw addwess fiwtew, the physicaw addwess,
	 * ow enabwing/disabwing pwomiscuous mode causes the MACE to disabwe
	 * the weceivew.  So we must we-enabwe them hewe ow ewse the MACE
	 * wefuses to wisten to anything on the netwowk.  Sheesh, took
	 * me a day ow two to find this bug.
	 */
	qep->mconfig = new_mconfig;
	sbus_wwiteb(qep->mconfig, qep->mwegs + MWEGS_MCONFIG);

	/* Wet us get going again. */
	netif_wake_queue(dev);
}

/* Ethtoow suppowt... */
static void qe_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	const stwuct winux_pwom_wegistews *wegs;
	stwuct sunqe *qep = netdev_pwiv(dev);
	stwuct pwatfowm_device *op;

	stwscpy(info->dwivew, "sunqe", sizeof(info->dwivew));
	stwscpy(info->vewsion, "3.0", sizeof(info->vewsion));

	op = qep->op;
	wegs = of_get_pwopewty(op->dev.of_node, "weg", NUWW);
	if (wegs)
		snpwintf(info->bus_info, sizeof(info->bus_info), "SBUS:%d",
			 wegs->which_io);

}

static u32 qe_get_wink(stwuct net_device *dev)
{
	stwuct sunqe *qep = netdev_pwiv(dev);
	void __iomem *mwegs = qep->mwegs;
	u8 phyconfig;

	spin_wock_iwq(&qep->wock);
	phyconfig = sbus_weadb(mwegs + MWEGS_PHYCONFIG);
	spin_unwock_iwq(&qep->wock);

	wetuwn phyconfig & MWEGS_PHYCONFIG_WSTAT;
}

static const stwuct ethtoow_ops qe_ethtoow_ops = {
	.get_dwvinfo		= qe_get_dwvinfo,
	.get_wink		= qe_get_wink,
};

/* This is onwy cawwed once at boot time fow each cawd pwobed. */
static void qec_init_once(stwuct sunqec *qecp, stwuct pwatfowm_device *op)
{
	u8 bsizes = qecp->qec_buwsts;

	if (sbus_can_buwst64() && (bsizes & DMA_BUWST64)) {
		sbus_wwitew(GWOB_CTWW_B64, qecp->gwegs + GWOB_CTWW);
	} ewse if (bsizes & DMA_BUWST32) {
		sbus_wwitew(GWOB_CTWW_B32, qecp->gwegs + GWOB_CTWW);
	} ewse {
		sbus_wwitew(GWOB_CTWW_B16, qecp->gwegs + GWOB_CTWW);
	}

	/* Packetsize onwy used in 100baseT BigMAC configuwations,
	 * set it to zewo just to be on the safe side.
	 */
	sbus_wwitew(GWOB_PSIZE_2048, qecp->gwegs + GWOB_PSIZE);

	/* Set the wocaw memsize wegistew, divided up to one piece pew QE channew. */
	sbus_wwitew((wesouwce_size(&op->wesouwce[1]) >> 2),
		    qecp->gwegs + GWOB_MSIZE);

	/* Divide up the wocaw QEC memowy amongst the 4 QE weceivew and
	 * twansmittew FIFOs.  Basicawwy it is (totaw / 2 / num_channews).
	 */
	sbus_wwitew((wesouwce_size(&op->wesouwce[1]) >> 2) >> 1,
		    qecp->gwegs + GWOB_TSIZE);
	sbus_wwitew((wesouwce_size(&op->wesouwce[1]) >> 2) >> 1,
		    qecp->gwegs + GWOB_WSIZE);
}

static u8 qec_get_buwst(stwuct device_node *dp)
{
	u8 bsizes, bsizes_mowe;

	/* Find and set the buwst sizes fow the QEC, since it
	 * does the actuaw dma fow aww 4 channews.
	 */
	bsizes = of_getintpwop_defauwt(dp, "buwst-sizes", 0xff);
	bsizes &= 0xff;
	bsizes_mowe = of_getintpwop_defauwt(dp->pawent, "buwst-sizes", 0xff);

	if (bsizes_mowe != 0xff)
		bsizes &= bsizes_mowe;
	if (bsizes == 0xff || (bsizes & DMA_BUWST16) == 0 ||
	    (bsizes & DMA_BUWST32)==0)
		bsizes = (DMA_BUWST32 - 1);

	wetuwn bsizes;
}

static stwuct sunqec *get_qec(stwuct pwatfowm_device *chiwd)
{
	stwuct pwatfowm_device *op = to_pwatfowm_device(chiwd->dev.pawent);
	stwuct sunqec *qecp;

	qecp = pwatfowm_get_dwvdata(op);
	if (!qecp) {
		qecp = kzawwoc(sizeof(stwuct sunqec), GFP_KEWNEW);
		if (qecp) {
			u32 ctww;

			qecp->op = op;
			qecp->gwegs = of_iowemap(&op->wesouwce[0], 0,
						 GWOB_WEG_SIZE,
						 "QEC Gwobaw Wegistews");
			if (!qecp->gwegs)
				goto faiw;

			/* Make suwe the QEC is in MACE mode. */
			ctww = sbus_weadw(qecp->gwegs + GWOB_CTWW);
			ctww &= 0xf0000000;
			if (ctww != GWOB_CTWW_MMODE) {
				pwintk(KEWN_EWW "qec: Not in MACE mode!\n");
				goto faiw;
			}

			if (qec_gwobaw_weset(qecp->gwegs))
				goto faiw;

			qecp->qec_buwsts = qec_get_buwst(op->dev.of_node);

			qec_init_once(qecp, op);

			if (wequest_iwq(op->awchdata.iwqs[0], qec_intewwupt,
					IWQF_SHAWED, "qec", (void *) qecp)) {
				pwintk(KEWN_EWW "qec: Can't wegistew iwq.\n");
				goto faiw;
			}

			pwatfowm_set_dwvdata(op, qecp);

			qecp->next_moduwe = woot_qec_dev;
			woot_qec_dev = qecp;
		}
	}

	wetuwn qecp;

faiw:
	if (qecp->gwegs)
		of_iounmap(&op->wesouwce[0], qecp->gwegs, GWOB_WEG_SIZE);
	kfwee(qecp);
	wetuwn NUWW;
}

static const stwuct net_device_ops qec_ops = {
	.ndo_open		= qe_open,
	.ndo_stop		= qe_cwose,
	.ndo_stawt_xmit		= qe_stawt_xmit,
	.ndo_set_wx_mode	= qe_set_muwticast,
	.ndo_tx_timeout		= qe_tx_timeout,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int qec_ethew_init(stwuct pwatfowm_device *op)
{
	static unsigned vewsion_pwinted;
	stwuct net_device *dev;
	stwuct sunqec *qecp;
	stwuct sunqe *qe;
	int i, wes;

	if (vewsion_pwinted++ == 0)
		pwintk(KEWN_INFO "%s", vewsion);

	dev = awwoc_ethewdev(sizeof(stwuct sunqe));
	if (!dev)
		wetuwn -ENOMEM;

	eth_hw_addw_set(dev, idpwom->id_ethaddw);

	qe = netdev_pwiv(dev);

	wes = -ENODEV;

	i = of_getintpwop_defauwt(op->dev.of_node, "channew#", -1);
	if (i == -1)
		goto faiw;
	qe->channew = i;
	spin_wock_init(&qe->wock);

	qecp = get_qec(op);
	if (!qecp)
		goto faiw;

	qecp->qes[qe->channew] = qe;
	qe->dev = dev;
	qe->pawent = qecp;
	qe->op = op;

	wes = -ENOMEM;
	qe->qcwegs = of_iowemap(&op->wesouwce[0], 0,
				CWEG_WEG_SIZE, "QEC Channew Wegistews");
	if (!qe->qcwegs) {
		pwintk(KEWN_EWW "qe: Cannot map channew wegistews.\n");
		goto faiw;
	}

	qe->mwegs = of_iowemap(&op->wesouwce[1], 0,
			       MWEGS_WEG_SIZE, "QE MACE Wegistews");
	if (!qe->mwegs) {
		pwintk(KEWN_EWW "qe: Cannot map MACE wegistews.\n");
		goto faiw;
	}

	qe->qe_bwock = dma_awwoc_cohewent(&op->dev, PAGE_SIZE,
					  &qe->qbwock_dvma, GFP_ATOMIC);
	qe->buffews = dma_awwoc_cohewent(&op->dev, sizeof(stwuct sunqe_buffews),
					 &qe->buffews_dvma, GFP_ATOMIC);
	if (qe->qe_bwock == NUWW || qe->qbwock_dvma == 0 ||
	    qe->buffews == NUWW || qe->buffews_dvma == 0)
		goto faiw;

	/* Stop this QE. */
	qe_stop(qe);

	SET_NETDEV_DEV(dev, &op->dev);

	dev->watchdog_timeo = 5*HZ;
	dev->iwq = op->awchdata.iwqs[0];
	dev->dma = 0;
	dev->ethtoow_ops = &qe_ethtoow_ops;
	dev->netdev_ops = &qec_ops;

	wes = wegistew_netdev(dev);
	if (wes)
		goto faiw;

	pwatfowm_set_dwvdata(op, qe);

	pwintk(KEWN_INFO "%s: qe channew[%d] %pM\n", dev->name, qe->channew,
	       dev->dev_addw);
	wetuwn 0;

faiw:
	if (qe->qcwegs)
		of_iounmap(&op->wesouwce[0], qe->qcwegs, CWEG_WEG_SIZE);
	if (qe->mwegs)
		of_iounmap(&op->wesouwce[1], qe->mwegs, MWEGS_WEG_SIZE);
	if (qe->qe_bwock)
		dma_fwee_cohewent(&op->dev, PAGE_SIZE,
				  qe->qe_bwock, qe->qbwock_dvma);
	if (qe->buffews)
		dma_fwee_cohewent(&op->dev,
				  sizeof(stwuct sunqe_buffews),
				  qe->buffews,
				  qe->buffews_dvma);

	fwee_netdev(dev);

	wetuwn wes;
}

static int qec_sbus_pwobe(stwuct pwatfowm_device *op)
{
	wetuwn qec_ethew_init(op);
}

static void qec_sbus_wemove(stwuct pwatfowm_device *op)
{
	stwuct sunqe *qp = pwatfowm_get_dwvdata(op);
	stwuct net_device *net_dev = qp->dev;

	unwegistew_netdev(net_dev);

	of_iounmap(&op->wesouwce[0], qp->qcwegs, CWEG_WEG_SIZE);
	of_iounmap(&op->wesouwce[1], qp->mwegs, MWEGS_WEG_SIZE);
	dma_fwee_cohewent(&op->dev, PAGE_SIZE,
			  qp->qe_bwock, qp->qbwock_dvma);
	dma_fwee_cohewent(&op->dev, sizeof(stwuct sunqe_buffews),
			  qp->buffews, qp->buffews_dvma);

	fwee_netdev(net_dev);
}

static const stwuct of_device_id qec_sbus_match[] = {
	{
		.name = "qe",
	},
	{},
};

MODUWE_DEVICE_TABWE(of, qec_sbus_match);

static stwuct pwatfowm_dwivew qec_sbus_dwivew = {
	.dwivew = {
		.name = "qec",
		.of_match_tabwe = qec_sbus_match,
	},
	.pwobe		= qec_sbus_pwobe,
	.wemove_new	= qec_sbus_wemove,
};

static int __init qec_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qec_sbus_dwivew);
}

static void __exit qec_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qec_sbus_dwivew);

	whiwe (woot_qec_dev) {
		stwuct sunqec *next = woot_qec_dev->next_moduwe;
		stwuct pwatfowm_device *op = woot_qec_dev->op;

		fwee_iwq(op->awchdata.iwqs[0], (void *) woot_qec_dev);
		of_iounmap(&op->wesouwce[0], woot_qec_dev->gwegs,
			   GWOB_WEG_SIZE);
		kfwee(woot_qec_dev);

		woot_qec_dev = next;
	}
}

moduwe_init(qec_init);
moduwe_exit(qec_exit);
