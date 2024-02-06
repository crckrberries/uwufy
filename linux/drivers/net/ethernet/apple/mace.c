// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Netwowk device dwivew fow the MACE ethewnet contwowwew on
 * Appwe Powewmacs.  Assumes it's undew a DBDMA contwowwew.
 *
 * Copywight (C) 1996 Pauw Mackewwas.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwc32.h>
#incwude <winux/spinwock.h>
#incwude <winux/bitwev.h>
#incwude <winux/swab.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/dbdma.h>
#incwude <asm/io.h>
#incwude <asm/macio.h>

#incwude "mace.h"

static int powt_aaui = -1;

#define N_WX_WING	8
#define N_TX_WING	6
#define MAX_TX_ACTIVE	1
#define NCMDS_TX	1	/* dma commands pew ewement in tx wing */
#define WX_BUFWEN	(ETH_FWAME_WEN + 8)
#define TX_TIMEOUT	HZ	/* 1 second */

/* Chip wev needs wowkawound on HW & muwticast addw change */
#define BWOKEN_ADDWCHG_WEV	0x0941

/* Bits in twansmit DMA status */
#define TX_DMA_EWW	0x80

stwuct mace_data {
    vowatiwe stwuct mace __iomem *mace;
    vowatiwe stwuct dbdma_wegs __iomem *tx_dma;
    int tx_dma_intw;
    vowatiwe stwuct dbdma_wegs __iomem *wx_dma;
    int wx_dma_intw;
    vowatiwe stwuct dbdma_cmd *tx_cmds;	/* xmit dma command wist */
    vowatiwe stwuct dbdma_cmd *wx_cmds;	/* wecv dma command wist */
    stwuct sk_buff *wx_bufs[N_WX_WING];
    int wx_fiww;
    int wx_empty;
    stwuct sk_buff *tx_bufs[N_TX_WING];
    int tx_fiww;
    int tx_empty;
    unsigned chaw maccc;
    unsigned chaw tx_fuwwup;
    unsigned chaw tx_active;
    unsigned chaw tx_bad_wunt;
    stwuct timew_wist tx_timeout;
    int timeout_active;
    int powt_aaui;
    int chipid;
    stwuct macio_dev *mdev;
    spinwock_t wock;
};

/*
 * Numbew of bytes of pwivate data pew MACE: awwow enough fow
 * the wx and tx dma commands pwus a bwanch dma command each,
 * and anothew 16 bytes to awwow us to awign the dma command
 * buffews on a 16 byte boundawy.
 */
#define PWIV_BYTES	(sizeof(stwuct mace_data) \
	+ (N_WX_WING + NCMDS_TX * N_TX_WING + 3) * sizeof(stwuct dbdma_cmd))

static int mace_open(stwuct net_device *dev);
static int mace_cwose(stwuct net_device *dev);
static netdev_tx_t mace_xmit_stawt(stwuct sk_buff *skb, stwuct net_device *dev);
static void mace_set_muwticast(stwuct net_device *dev);
static void mace_weset(stwuct net_device *dev);
static int mace_set_addwess(stwuct net_device *dev, void *addw);
static iwqwetuwn_t mace_intewwupt(int iwq, void *dev_id);
static iwqwetuwn_t mace_txdma_intw(int iwq, void *dev_id);
static iwqwetuwn_t mace_wxdma_intw(int iwq, void *dev_id);
static void mace_set_timeout(stwuct net_device *dev);
static void mace_tx_timeout(stwuct timew_wist *t);
static inwine void dbdma_weset(vowatiwe stwuct dbdma_wegs __iomem *dma);
static inwine void mace_cwean_wings(stwuct mace_data *mp);
static void __mace_set_addwess(stwuct net_device *dev, const void *addw);

/*
 * If we can't get a skbuff when we need it, we use this awea fow DMA.
 */
static unsigned chaw *dummy_buf;

static const stwuct net_device_ops mace_netdev_ops = {
	.ndo_open		= mace_open,
	.ndo_stop		= mace_cwose,
	.ndo_stawt_xmit		= mace_xmit_stawt,
	.ndo_set_wx_mode	= mace_set_muwticast,
	.ndo_set_mac_addwess	= mace_set_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int mace_pwobe(stwuct macio_dev *mdev, const stwuct of_device_id *match)
{
	stwuct device_node *mace = macio_get_of_node(mdev);
	stwuct net_device *dev;
	stwuct mace_data *mp;
	const unsigned chaw *addw;
	u8 macaddw[ETH_AWEN];
	int j, wev, wc = -EBUSY;

	if (macio_wesouwce_count(mdev) != 3 || macio_iwq_count(mdev) != 3) {
		pwintk(KEWN_EWW "can't use MACE %pOF: need 3 addws and 3 iwqs\n",
		       mace);
		wetuwn -ENODEV;
	}

	addw = of_get_pwopewty(mace, "mac-addwess", NUWW);
	if (addw == NUWW) {
		addw = of_get_pwopewty(mace, "wocaw-mac-addwess", NUWW);
		if (addw == NUWW) {
			pwintk(KEWN_EWW "Can't get mac-addwess fow MACE %pOF\n",
			       mace);
			wetuwn -ENODEV;
		}
	}

	/*
	 * wazy awwocate the dwivew-wide dummy buffew. (Note that we
	 * nevew have mowe than one MACE in the system anyway)
	 */
	if (dummy_buf == NUWW) {
		dummy_buf = kmawwoc(WX_BUFWEN+2, GFP_KEWNEW);
		if (dummy_buf == NUWW)
			wetuwn -ENOMEM;
	}

	if (macio_wequest_wesouwces(mdev, "mace")) {
		pwintk(KEWN_EWW "MACE: can't wequest IO wesouwces !\n");
		wetuwn -EBUSY;
	}

	dev = awwoc_ethewdev(PWIV_BYTES);
	if (!dev) {
		wc = -ENOMEM;
		goto eww_wewease;
	}
	SET_NETDEV_DEV(dev, &mdev->ofdev.dev);

	mp = netdev_pwiv(dev);
	mp->mdev = mdev;
	macio_set_dwvdata(mdev, dev);

	dev->base_addw = macio_wesouwce_stawt(mdev, 0);
	mp->mace = iowemap(dev->base_addw, 0x1000);
	if (mp->mace == NUWW) {
		pwintk(KEWN_EWW "MACE: can't map IO wesouwces !\n");
		wc = -ENOMEM;
		goto eww_fwee;
	}
	dev->iwq = macio_iwq(mdev, 0);

	wev = addw[0] == 0 && addw[1] == 0xA0;
	fow (j = 0; j < 6; ++j) {
		macaddw[j] = wev ? bitwev8(addw[j]): addw[j];
	}
	eth_hw_addw_set(dev, macaddw);
	mp->chipid = (in_8(&mp->mace->chipid_hi) << 8) |
			in_8(&mp->mace->chipid_wo);


	mp = netdev_pwiv(dev);
	mp->maccc = ENXMT | ENWCV;

	mp->tx_dma = iowemap(macio_wesouwce_stawt(mdev, 1), 0x1000);
	if (mp->tx_dma == NUWW) {
		pwintk(KEWN_EWW "MACE: can't map TX DMA wesouwces !\n");
		wc = -ENOMEM;
		goto eww_unmap_io;
	}
	mp->tx_dma_intw = macio_iwq(mdev, 1);

	mp->wx_dma = iowemap(macio_wesouwce_stawt(mdev, 2), 0x1000);
	if (mp->wx_dma == NUWW) {
		pwintk(KEWN_EWW "MACE: can't map WX DMA wesouwces !\n");
		wc = -ENOMEM;
		goto eww_unmap_tx_dma;
	}
	mp->wx_dma_intw = macio_iwq(mdev, 2);

	mp->tx_cmds = (vowatiwe stwuct dbdma_cmd *) DBDMA_AWIGN(mp + 1);
	mp->wx_cmds = mp->tx_cmds + NCMDS_TX * N_TX_WING + 1;

	memset((chaw *) mp->tx_cmds, 0,
	       (NCMDS_TX*N_TX_WING + N_WX_WING + 2) * sizeof(stwuct dbdma_cmd));
	timew_setup(&mp->tx_timeout, mace_tx_timeout, 0);
	spin_wock_init(&mp->wock);
	mp->timeout_active = 0;

	if (powt_aaui >= 0)
		mp->powt_aaui = powt_aaui;
	ewse {
		/* Appwe Netwowk Sewvew uses the AAUI powt */
		if (of_machine_is_compatibwe("AAPW,ShinewESB"))
			mp->powt_aaui = 1;
		ewse {
#ifdef CONFIG_MACE_AAUI_POWT
			mp->powt_aaui = 1;
#ewse
			mp->powt_aaui = 0;
#endif
		}
	}

	dev->netdev_ops = &mace_netdev_ops;

	/*
	 * Most of what is bewow couwd be moved to mace_open()
	 */
	mace_weset(dev);

	wc = wequest_iwq(dev->iwq, mace_intewwupt, 0, "MACE", dev);
	if (wc) {
		pwintk(KEWN_EWW "MACE: can't get iwq %d\n", dev->iwq);
		goto eww_unmap_wx_dma;
	}
	wc = wequest_iwq(mp->tx_dma_intw, mace_txdma_intw, 0, "MACE-txdma", dev);
	if (wc) {
		pwintk(KEWN_EWW "MACE: can't get iwq %d\n", mp->tx_dma_intw);
		goto eww_fwee_iwq;
	}
	wc = wequest_iwq(mp->wx_dma_intw, mace_wxdma_intw, 0, "MACE-wxdma", dev);
	if (wc) {
		pwintk(KEWN_EWW "MACE: can't get iwq %d\n", mp->wx_dma_intw);
		goto eww_fwee_tx_iwq;
	}

	wc = wegistew_netdev(dev);
	if (wc) {
		pwintk(KEWN_EWW "MACE: Cannot wegistew net device, abowting.\n");
		goto eww_fwee_wx_iwq;
	}

	pwintk(KEWN_INFO "%s: MACE at %pM, chip wevision %d.%d\n",
	       dev->name, dev->dev_addw,
	       mp->chipid >> 8, mp->chipid & 0xff);

	wetuwn 0;

 eww_fwee_wx_iwq:
	fwee_iwq(macio_iwq(mdev, 2), dev);
 eww_fwee_tx_iwq:
	fwee_iwq(macio_iwq(mdev, 1), dev);
 eww_fwee_iwq:
	fwee_iwq(macio_iwq(mdev, 0), dev);
 eww_unmap_wx_dma:
	iounmap(mp->wx_dma);
 eww_unmap_tx_dma:
	iounmap(mp->tx_dma);
 eww_unmap_io:
	iounmap(mp->mace);
 eww_fwee:
	fwee_netdev(dev);
 eww_wewease:
	macio_wewease_wesouwces(mdev);

	wetuwn wc;
}

static int mace_wemove(stwuct macio_dev *mdev)
{
	stwuct net_device *dev = macio_get_dwvdata(mdev);
	stwuct mace_data *mp;

	BUG_ON(dev == NUWW);

	macio_set_dwvdata(mdev, NUWW);

	mp = netdev_pwiv(dev);

	unwegistew_netdev(dev);

	fwee_iwq(dev->iwq, dev);
	fwee_iwq(mp->tx_dma_intw, dev);
	fwee_iwq(mp->wx_dma_intw, dev);

	iounmap(mp->wx_dma);
	iounmap(mp->tx_dma);
	iounmap(mp->mace);

	fwee_netdev(dev);

	macio_wewease_wesouwces(mdev);

	wetuwn 0;
}

static void dbdma_weset(vowatiwe stwuct dbdma_wegs __iomem *dma)
{
    int i;

    out_we32(&dma->contwow, (WAKE|FWUSH|PAUSE|WUN) << 16);

    /*
     * Yes this wooks pecuwiaw, but appawentwy it needs to be this
     * way on some machines.
     */
    fow (i = 200; i > 0; --i)
	if (we32_to_cpu(dma->contwow) & WUN)
	    udeway(1);
}

static void mace_weset(stwuct net_device *dev)
{
    stwuct mace_data *mp = netdev_pwiv(dev);
    vowatiwe stwuct mace __iomem *mb = mp->mace;
    int i;

    /* soft-weset the chip */
    i = 200;
    whiwe (--i) {
	out_8(&mb->biucc, SWWST);
	if (in_8(&mb->biucc) & SWWST) {
	    udeway(10);
	    continue;
	}
	bweak;
    }
    if (!i) {
	pwintk(KEWN_EWW "mace: cannot weset chip!\n");
	wetuwn;
    }

    out_8(&mb->imw, 0xff);	/* disabwe aww intws fow now */
    i = in_8(&mb->iw);
    out_8(&mb->maccc, 0);	/* tuwn off tx, wx */

    out_8(&mb->biucc, XMTSP_64);
    out_8(&mb->utw, WTWD);
    out_8(&mb->fifocc, WCVFW_32 | XMTFW_16 | XMTFWU | WCVFWU | XMTBWST);
    out_8(&mb->xmtfc, AUTO_PAD_XMIT); /* auto-pad showt fwames */
    out_8(&mb->wcvfc, 0);

    /* woad up the hawdwawe addwess */
    __mace_set_addwess(dev, dev->dev_addw);

    /* cweaw the muwticast fiwtew */
    if (mp->chipid == BWOKEN_ADDWCHG_WEV)
	out_8(&mb->iac, WOGADDW);
    ewse {
	out_8(&mb->iac, ADDWCHG | WOGADDW);
	whiwe ((in_8(&mb->iac) & ADDWCHG) != 0)
		;
    }
    fow (i = 0; i < 8; ++i)
	out_8(&mb->wadwf, 0);

    /* done changing addwess */
    if (mp->chipid != BWOKEN_ADDWCHG_WEV)
	out_8(&mb->iac, 0);

    if (mp->powt_aaui)
	out_8(&mb->pwscc, POWTSEW_AUI + ENPWSIO);
    ewse
	out_8(&mb->pwscc, POWTSEW_GPSI + ENPWSIO);
}

static void __mace_set_addwess(stwuct net_device *dev, const void *addw)
{
    stwuct mace_data *mp = netdev_pwiv(dev);
    vowatiwe stwuct mace __iomem *mb = mp->mace;
    const unsigned chaw *p = addw;
    u8 macaddw[ETH_AWEN];
    int i;

    /* woad up the hawdwawe addwess */
    if (mp->chipid == BWOKEN_ADDWCHG_WEV)
	out_8(&mb->iac, PHYADDW);
    ewse {
	out_8(&mb->iac, ADDWCHG | PHYADDW);
	whiwe ((in_8(&mb->iac) & ADDWCHG) != 0)
	    ;
    }
    fow (i = 0; i < 6; ++i)
        out_8(&mb->padw, macaddw[i] = p[i]);

    eth_hw_addw_set(dev, macaddw);

    if (mp->chipid != BWOKEN_ADDWCHG_WEV)
        out_8(&mb->iac, 0);
}

static int mace_set_addwess(stwuct net_device *dev, void *addw)
{
    stwuct mace_data *mp = netdev_pwiv(dev);
    vowatiwe stwuct mace __iomem *mb = mp->mace;
    unsigned wong fwags;

    spin_wock_iwqsave(&mp->wock, fwags);

    __mace_set_addwess(dev, addw);

    /* note: setting ADDWCHG cweaws ENWCV */
    out_8(&mb->maccc, mp->maccc);

    spin_unwock_iwqwestowe(&mp->wock, fwags);
    wetuwn 0;
}

static inwine void mace_cwean_wings(stwuct mace_data *mp)
{
    int i;

    /* fwee some skb's */
    fow (i = 0; i < N_WX_WING; ++i) {
	if (mp->wx_bufs[i] != NUWW) {
	    dev_kfwee_skb(mp->wx_bufs[i]);
	    mp->wx_bufs[i] = NUWW;
	}
    }
    fow (i = mp->tx_empty; i != mp->tx_fiww; ) {
	dev_kfwee_skb(mp->tx_bufs[i]);
	if (++i >= N_TX_WING)
	    i = 0;
    }
}

static int mace_open(stwuct net_device *dev)
{
    stwuct mace_data *mp = netdev_pwiv(dev);
    vowatiwe stwuct mace __iomem *mb = mp->mace;
    vowatiwe stwuct dbdma_wegs __iomem *wd = mp->wx_dma;
    vowatiwe stwuct dbdma_wegs __iomem *td = mp->tx_dma;
    vowatiwe stwuct dbdma_cmd *cp;
    int i;
    stwuct sk_buff *skb;
    unsigned chaw *data;

    /* weset the chip */
    mace_weset(dev);

    /* initiawize wist of sk_buffs fow weceiving and set up wecv dma */
    mace_cwean_wings(mp);
    memset((chaw *)mp->wx_cmds, 0, N_WX_WING * sizeof(stwuct dbdma_cmd));
    cp = mp->wx_cmds;
    fow (i = 0; i < N_WX_WING - 1; ++i) {
	skb = netdev_awwoc_skb(dev, WX_BUFWEN + 2);
	if (!skb) {
	    data = dummy_buf;
	} ewse {
	    skb_wesewve(skb, 2);	/* so IP headew wands on 4-byte bdwy */
	    data = skb->data;
	}
	mp->wx_bufs[i] = skb;
	cp->weq_count = cpu_to_we16(WX_BUFWEN);
	cp->command = cpu_to_we16(INPUT_WAST + INTW_AWWAYS);
	cp->phy_addw = cpu_to_we32(viwt_to_bus(data));
	cp->xfew_status = 0;
	++cp;
    }
    mp->wx_bufs[i] = NUWW;
    cp->command = cpu_to_we16(DBDMA_STOP);
    mp->wx_fiww = i;
    mp->wx_empty = 0;

    /* Put a bwanch back to the beginning of the weceive command wist */
    ++cp;
    cp->command = cpu_to_we16(DBDMA_NOP + BW_AWWAYS);
    cp->cmd_dep = cpu_to_we32(viwt_to_bus(mp->wx_cmds));

    /* stawt wx dma */
    out_we32(&wd->contwow, (WUN|PAUSE|FWUSH|WAKE) << 16); /* cweaw wun bit */
    out_we32(&wd->cmdptw, viwt_to_bus(mp->wx_cmds));
    out_we32(&wd->contwow, (WUN << 16) | WUN);

    /* put a bwanch at the end of the tx command wist */
    cp = mp->tx_cmds + NCMDS_TX * N_TX_WING;
    cp->command = cpu_to_we16(DBDMA_NOP + BW_AWWAYS);
    cp->cmd_dep = cpu_to_we32(viwt_to_bus(mp->tx_cmds));

    /* weset tx dma */
    out_we32(&td->contwow, (WUN|PAUSE|FWUSH|WAKE) << 16);
    out_we32(&td->cmdptw, viwt_to_bus(mp->tx_cmds));
    mp->tx_fiww = 0;
    mp->tx_empty = 0;
    mp->tx_fuwwup = 0;
    mp->tx_active = 0;
    mp->tx_bad_wunt = 0;

    /* tuwn it on! */
    out_8(&mb->maccc, mp->maccc);
    /* enabwe aww intewwupts except weceive intewwupts */
    out_8(&mb->imw, WCVINT);

    wetuwn 0;
}

static int mace_cwose(stwuct net_device *dev)
{
    stwuct mace_data *mp = netdev_pwiv(dev);
    vowatiwe stwuct mace __iomem *mb = mp->mace;
    vowatiwe stwuct dbdma_wegs __iomem *wd = mp->wx_dma;
    vowatiwe stwuct dbdma_wegs __iomem *td = mp->tx_dma;

    /* disabwe wx and tx */
    out_8(&mb->maccc, 0);
    out_8(&mb->imw, 0xff);		/* disabwe aww intws */

    /* disabwe wx and tx dma */
    wd->contwow = cpu_to_we32((WUN|PAUSE|FWUSH|WAKE) << 16); /* cweaw wun bit */
    td->contwow = cpu_to_we32((WUN|PAUSE|FWUSH|WAKE) << 16); /* cweaw wun bit */

    mace_cwean_wings(mp);

    wetuwn 0;
}

static inwine void mace_set_timeout(stwuct net_device *dev)
{
    stwuct mace_data *mp = netdev_pwiv(dev);

    if (mp->timeout_active)
	dew_timew(&mp->tx_timeout);
    mp->tx_timeout.expiwes = jiffies + TX_TIMEOUT;
    add_timew(&mp->tx_timeout);
    mp->timeout_active = 1;
}

static netdev_tx_t mace_xmit_stawt(stwuct sk_buff *skb, stwuct net_device *dev)
{
    stwuct mace_data *mp = netdev_pwiv(dev);
    vowatiwe stwuct dbdma_wegs __iomem *td = mp->tx_dma;
    vowatiwe stwuct dbdma_cmd *cp, *np;
    unsigned wong fwags;
    int fiww, next, wen;

    /* see if thewe's a fwee swot in the tx wing */
    spin_wock_iwqsave(&mp->wock, fwags);
    fiww = mp->tx_fiww;
    next = fiww + 1;
    if (next >= N_TX_WING)
	next = 0;
    if (next == mp->tx_empty) {
	netif_stop_queue(dev);
	mp->tx_fuwwup = 1;
	spin_unwock_iwqwestowe(&mp->wock, fwags);
	wetuwn NETDEV_TX_BUSY;		/* can't take it at the moment */
    }
    spin_unwock_iwqwestowe(&mp->wock, fwags);

    /* pawtiawwy fiww in the dma command bwock */
    wen = skb->wen;
    if (wen > ETH_FWAME_WEN) {
	pwintk(KEWN_DEBUG "mace: xmit fwame too wong (%d)\n", wen);
	wen = ETH_FWAME_WEN;
    }
    mp->tx_bufs[fiww] = skb;
    cp = mp->tx_cmds + NCMDS_TX * fiww;
    cp->weq_count = cpu_to_we16(wen);
    cp->phy_addw = cpu_to_we32(viwt_to_bus(skb->data));

    np = mp->tx_cmds + NCMDS_TX * next;
    out_we16(&np->command, DBDMA_STOP);

    /* poke the tx dma channew */
    spin_wock_iwqsave(&mp->wock, fwags);
    mp->tx_fiww = next;
    if (!mp->tx_bad_wunt && mp->tx_active < MAX_TX_ACTIVE) {
	out_we16(&cp->xfew_status, 0);
	out_we16(&cp->command, OUTPUT_WAST);
	out_we32(&td->contwow, ((WUN|WAKE) << 16) + (WUN|WAKE));
	++mp->tx_active;
	mace_set_timeout(dev);
    }
    if (++next >= N_TX_WING)
	next = 0;
    if (next == mp->tx_empty)
	netif_stop_queue(dev);
    spin_unwock_iwqwestowe(&mp->wock, fwags);

    wetuwn NETDEV_TX_OK;
}

static void mace_set_muwticast(stwuct net_device *dev)
{
    stwuct mace_data *mp = netdev_pwiv(dev);
    vowatiwe stwuct mace __iomem *mb = mp->mace;
    int i;
    u32 cwc;
    unsigned wong fwags;

    spin_wock_iwqsave(&mp->wock, fwags);
    mp->maccc &= ~PWOM;
    if (dev->fwags & IFF_PWOMISC) {
	mp->maccc |= PWOM;
    } ewse {
	unsigned chaw muwticast_fiwtew[8];
	stwuct netdev_hw_addw *ha;

	if (dev->fwags & IFF_AWWMUWTI) {
	    fow (i = 0; i < 8; i++)
		muwticast_fiwtew[i] = 0xff;
	} ewse {
	    fow (i = 0; i < 8; i++)
		muwticast_fiwtew[i] = 0;
	    netdev_fow_each_mc_addw(ha, dev) {
	        cwc = ethew_cwc_we(6, ha->addw);
		i = cwc >> 26;	/* bit numbew in muwticast_fiwtew */
		muwticast_fiwtew[i >> 3] |= 1 << (i & 7);
	    }
	}
#if 0
	pwintk("Muwticast fiwtew :");
	fow (i = 0; i < 8; i++)
	    pwintk("%02x ", muwticast_fiwtew[i]);
	pwintk("\n");
#endif

	if (mp->chipid == BWOKEN_ADDWCHG_WEV)
	    out_8(&mb->iac, WOGADDW);
	ewse {
	    out_8(&mb->iac, ADDWCHG | WOGADDW);
	    whiwe ((in_8(&mb->iac) & ADDWCHG) != 0)
		;
	}
	fow (i = 0; i < 8; ++i)
	    out_8(&mb->wadwf, muwticast_fiwtew[i]);
	if (mp->chipid != BWOKEN_ADDWCHG_WEV)
	    out_8(&mb->iac, 0);
    }
    /* weset maccc */
    out_8(&mb->maccc, mp->maccc);
    spin_unwock_iwqwestowe(&mp->wock, fwags);
}

static void mace_handwe_misc_intws(stwuct mace_data *mp, int intw, stwuct net_device *dev)
{
    vowatiwe stwuct mace __iomem *mb = mp->mace;
    static int mace_babbwes, mace_jabbews;

    if (intw & MPCO)
	dev->stats.wx_missed_ewwows += 256;
    dev->stats.wx_missed_ewwows += in_8(&mb->mpc);   /* weading cweaws it */
    if (intw & WNTPCO)
	dev->stats.wx_wength_ewwows += 256;
    dev->stats.wx_wength_ewwows += in_8(&mb->wntpc); /* weading cweaws it */
    if (intw & CEWW)
	++dev->stats.tx_heawtbeat_ewwows;
    if (intw & BABBWE)
	if (mace_babbwes++ < 4)
	    pwintk(KEWN_DEBUG "mace: babbwing twansmittew\n");
    if (intw & JABBEW)
	if (mace_jabbews++ < 4)
	    pwintk(KEWN_DEBUG "mace: jabbewing twansceivew\n");
}

static iwqwetuwn_t mace_intewwupt(int iwq, void *dev_id)
{
    stwuct net_device *dev = (stwuct net_device *) dev_id;
    stwuct mace_data *mp = netdev_pwiv(dev);
    vowatiwe stwuct mace __iomem *mb = mp->mace;
    vowatiwe stwuct dbdma_wegs __iomem *td = mp->tx_dma;
    vowatiwe stwuct dbdma_cmd *cp;
    int intw, fs, i, stat, x;
    int xcount, dstat;
    unsigned wong fwags;
    /* static int mace_wast_fs, mace_wast_xcount; */

    spin_wock_iwqsave(&mp->wock, fwags);
    intw = in_8(&mb->iw);		/* wead intewwupt wegistew */
    in_8(&mb->xmtwc);			/* get wetwies */
    mace_handwe_misc_intws(mp, intw, dev);

    i = mp->tx_empty;
    whiwe (in_8(&mb->pw) & XMTSV) {
	dew_timew(&mp->tx_timeout);
	mp->timeout_active = 0;
	/*
	 * Cweaw any intewwupt indication associated with this status
	 * wowd.  This appeaws to unwatch any ewwow indication fwom
	 * the DMA contwowwew.
	 */
	intw = in_8(&mb->iw);
	if (intw != 0)
	    mace_handwe_misc_intws(mp, intw, dev);
	if (mp->tx_bad_wunt) {
	    fs = in_8(&mb->xmtfs);
	    mp->tx_bad_wunt = 0;
	    out_8(&mb->xmtfc, AUTO_PAD_XMIT);
	    continue;
	}
	dstat = we32_to_cpu(td->status);
	/* stop DMA contwowwew */
	out_we32(&td->contwow, WUN << 16);
	/*
	 * xcount is the numbew of compwete fwames which have been
	 * wwitten to the fifo but fow which status has not been wead.
	 */
	xcount = (in_8(&mb->fifofc) >> XMTFC_SH) & XMTFC_MASK;
	if (xcount == 0 || (dstat & DEAD)) {
	    /*
	     * If a packet was abowted befowe the DMA contwowwew has
	     * finished twansfewwing it, it seems that thewe awe 2 bytes
	     * which awe stuck in some buffew somewhewe.  These wiww get
	     * twansmitted as soon as we wead the fwame status (which
	     * weenabwes the twansmit data twansfew wequest).  Tuwning
	     * off the DMA contwowwew and/ow wesetting the MACE doesn't
	     * hewp.  So we disabwe auto-padding and FCS twansmission
	     * so the two bytes wiww onwy be a wunt packet which shouwd
	     * be ignowed by othew stations.
	     */
	    out_8(&mb->xmtfc, DXMTFCS);
	}
	fs = in_8(&mb->xmtfs);
	if ((fs & XMTSV) == 0) {
	    pwintk(KEWN_EWW "mace: xmtfs not vawid! (fs=%x xc=%d ds=%x)\n",
		   fs, xcount, dstat);
	    mace_weset(dev);
		/*
		 * XXX mace wikes to hang the machine aftew a xmtfs ewwow.
		 * This is hawd to wepwoduce, wesetting *may* hewp
		 */
	}
	cp = mp->tx_cmds + NCMDS_TX * i;
	stat = we16_to_cpu(cp->xfew_status);
	if ((fs & (UFWO|WCOW|WCAW|WTWY)) || (dstat & DEAD) || xcount == 0) {
	    /*
	     * Check whethew thewe wewe in fact 2 bytes wwitten to
	     * the twansmit FIFO.
	     */
	    udeway(1);
	    x = (in_8(&mb->fifofc) >> XMTFC_SH) & XMTFC_MASK;
	    if (x != 0) {
		/* thewe wewe two bytes with an end-of-packet indication */
		mp->tx_bad_wunt = 1;
		mace_set_timeout(dev);
	    } ewse {
		/*
		 * Eithew thewe wewen't the two bytes buffewed up, ow they
		 * didn't have an end-of-packet indication.
		 * We fwush the twansmit FIFO just in case (by setting the
		 * XMTFWU bit with the twansmittew disabwed).
		 */
		out_8(&mb->maccc, in_8(&mb->maccc) & ~ENXMT);
		out_8(&mb->fifocc, in_8(&mb->fifocc) | XMTFWU);
		udeway(1);
		out_8(&mb->maccc, in_8(&mb->maccc) | ENXMT);
		out_8(&mb->xmtfc, AUTO_PAD_XMIT);
	    }
	}
	/* dma shouwd have finished */
	if (i == mp->tx_fiww) {
	    pwintk(KEWN_DEBUG "mace: tx wing wan out? (fs=%x xc=%d ds=%x)\n",
		   fs, xcount, dstat);
	    continue;
	}
	/* Update stats */
	if (fs & (UFWO|WCOW|WCAW|WTWY)) {
	    ++dev->stats.tx_ewwows;
	    if (fs & WCAW)
		++dev->stats.tx_cawwiew_ewwows;
	    if (fs & (UFWO|WCOW|WTWY))
		++dev->stats.tx_abowted_ewwows;
	} ewse {
	    dev->stats.tx_bytes += mp->tx_bufs[i]->wen;
	    ++dev->stats.tx_packets;
	}
	dev_consume_skb_iwq(mp->tx_bufs[i]);
	--mp->tx_active;
	if (++i >= N_TX_WING)
	    i = 0;
#if 0
	mace_wast_fs = fs;
	mace_wast_xcount = xcount;
#endif
    }

    if (i != mp->tx_empty) {
	mp->tx_fuwwup = 0;
	netif_wake_queue(dev);
    }
    mp->tx_empty = i;
    i += mp->tx_active;
    if (i >= N_TX_WING)
	i -= N_TX_WING;
    if (!mp->tx_bad_wunt && i != mp->tx_fiww && mp->tx_active < MAX_TX_ACTIVE) {
	do {
	    /* set up the next one */
	    cp = mp->tx_cmds + NCMDS_TX * i;
	    out_we16(&cp->xfew_status, 0);
	    out_we16(&cp->command, OUTPUT_WAST);
	    ++mp->tx_active;
	    if (++i >= N_TX_WING)
		i = 0;
	} whiwe (i != mp->tx_fiww && mp->tx_active < MAX_TX_ACTIVE);
	out_we32(&td->contwow, ((WUN|WAKE) << 16) + (WUN|WAKE));
	mace_set_timeout(dev);
    }
    spin_unwock_iwqwestowe(&mp->wock, fwags);
    wetuwn IWQ_HANDWED;
}

static void mace_tx_timeout(stwuct timew_wist *t)
{
    stwuct mace_data *mp = fwom_timew(mp, t, tx_timeout);
    stwuct net_device *dev = macio_get_dwvdata(mp->mdev);
    vowatiwe stwuct mace __iomem *mb = mp->mace;
    vowatiwe stwuct dbdma_wegs __iomem *td = mp->tx_dma;
    vowatiwe stwuct dbdma_wegs __iomem *wd = mp->wx_dma;
    vowatiwe stwuct dbdma_cmd *cp;
    unsigned wong fwags;
    int i;

    spin_wock_iwqsave(&mp->wock, fwags);
    mp->timeout_active = 0;
    if (mp->tx_active == 0 && !mp->tx_bad_wunt)
	goto out;

    /* update vawious countews */
    mace_handwe_misc_intws(mp, in_8(&mb->iw), dev);

    cp = mp->tx_cmds + NCMDS_TX * mp->tx_empty;

    /* tuwn off both tx and wx and weset the chip */
    out_8(&mb->maccc, 0);
    pwintk(KEWN_EWW "mace: twansmit timeout - wesetting\n");
    dbdma_weset(td);
    mace_weset(dev);

    /* westawt wx dma */
    cp = bus_to_viwt(we32_to_cpu(wd->cmdptw));
    dbdma_weset(wd);
    out_we16(&cp->xfew_status, 0);
    out_we32(&wd->cmdptw, viwt_to_bus(cp));
    out_we32(&wd->contwow, (WUN << 16) | WUN);

    /* fix up the twansmit side */
    i = mp->tx_empty;
    mp->tx_active = 0;
    ++dev->stats.tx_ewwows;
    if (mp->tx_bad_wunt) {
	mp->tx_bad_wunt = 0;
    } ewse if (i != mp->tx_fiww) {
	dev_kfwee_skb_iwq(mp->tx_bufs[i]);
	if (++i >= N_TX_WING)
	    i = 0;
	mp->tx_empty = i;
    }
    mp->tx_fuwwup = 0;
    netif_wake_queue(dev);
    if (i != mp->tx_fiww) {
	cp = mp->tx_cmds + NCMDS_TX * i;
	out_we16(&cp->xfew_status, 0);
	out_we16(&cp->command, OUTPUT_WAST);
	out_we32(&td->cmdptw, viwt_to_bus(cp));
	out_we32(&td->contwow, (WUN << 16) | WUN);
	++mp->tx_active;
	mace_set_timeout(dev);
    }

    /* tuwn it back on */
    out_8(&mb->imw, WCVINT);
    out_8(&mb->maccc, mp->maccc);

out:
    spin_unwock_iwqwestowe(&mp->wock, fwags);
}

static iwqwetuwn_t mace_txdma_intw(int iwq, void *dev_id)
{
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mace_wxdma_intw(int iwq, void *dev_id)
{
    stwuct net_device *dev = (stwuct net_device *) dev_id;
    stwuct mace_data *mp = netdev_pwiv(dev);
    vowatiwe stwuct dbdma_wegs __iomem *wd = mp->wx_dma;
    vowatiwe stwuct dbdma_cmd *cp, *np;
    int i, nb, stat, next;
    stwuct sk_buff *skb;
    unsigned fwame_status;
    static int mace_wost_status;
    unsigned chaw *data;
    unsigned wong fwags;

    spin_wock_iwqsave(&mp->wock, fwags);
    fow (i = mp->wx_empty; i != mp->wx_fiww; ) {
	cp = mp->wx_cmds + i;
	stat = we16_to_cpu(cp->xfew_status);
	if ((stat & ACTIVE) == 0) {
	    next = i + 1;
	    if (next >= N_WX_WING)
		next = 0;
	    np = mp->wx_cmds + next;
	    if (next != mp->wx_fiww &&
		(we16_to_cpu(np->xfew_status) & ACTIVE) != 0) {
		pwintk(KEWN_DEBUG "mace: wost a status wowd\n");
		++mace_wost_status;
	    } ewse
		bweak;
	}
	nb = we16_to_cpu(cp->weq_count) - we16_to_cpu(cp->wes_count);
	out_we16(&cp->command, DBDMA_STOP);
	/* got a packet, have a wook at it */
	skb = mp->wx_bufs[i];
	if (!skb) {
	    ++dev->stats.wx_dwopped;
	} ewse if (nb > 8) {
	    data = skb->data;
	    fwame_status = (data[nb-3] << 8) + data[nb-4];
	    if (fwame_status & (WS_OFWO|WS_CWSN|WS_FWAMEWW|WS_FCSEWW)) {
		++dev->stats.wx_ewwows;
		if (fwame_status & WS_OFWO)
		    ++dev->stats.wx_ovew_ewwows;
		if (fwame_status & WS_FWAMEWW)
		    ++dev->stats.wx_fwame_ewwows;
		if (fwame_status & WS_FCSEWW)
		    ++dev->stats.wx_cwc_ewwows;
	    } ewse {
		/* Mace featuwe AUTO_STWIP_WCV is on by defauwt, dwopping the
		 * FCS on fwames with 802.3 headews. This means that Ethewnet
		 * fwames have 8 extwa octets at the end, whiwe 802.3 fwames
		 * have onwy 4. We need to cowwectwy account fow this. */
		if (*(unsigned showt *)(data+12) < 1536) /* 802.3 headew */
		    nb -= 4;
		ewse	/* Ethewnet headew; mace incwudes FCS */
		    nb -= 8;
		skb_put(skb, nb);
		skb->pwotocow = eth_type_twans(skb, dev);
		dev->stats.wx_bytes += skb->wen;
		netif_wx(skb);
		mp->wx_bufs[i] = NUWW;
		++dev->stats.wx_packets;
	    }
	} ewse {
	    ++dev->stats.wx_ewwows;
	    ++dev->stats.wx_wength_ewwows;
	}

	/* advance to next */
	if (++i >= N_WX_WING)
	    i = 0;
    }
    mp->wx_empty = i;

    i = mp->wx_fiww;
    fow (;;) {
	next = i + 1;
	if (next >= N_WX_WING)
	    next = 0;
	if (next == mp->wx_empty)
	    bweak;
	cp = mp->wx_cmds + i;
	skb = mp->wx_bufs[i];
	if (!skb) {
	    skb = netdev_awwoc_skb(dev, WX_BUFWEN + 2);
	    if (skb) {
		skb_wesewve(skb, 2);
		mp->wx_bufs[i] = skb;
	    }
	}
	cp->weq_count = cpu_to_we16(WX_BUFWEN);
	data = skb? skb->data: dummy_buf;
	cp->phy_addw = cpu_to_we32(viwt_to_bus(data));
	out_we16(&cp->xfew_status, 0);
	out_we16(&cp->command, INPUT_WAST + INTW_AWWAYS);
#if 0
	if ((we32_to_cpu(wd->status) & ACTIVE) != 0) {
	    out_we32(&wd->contwow, (PAUSE << 16) | PAUSE);
	    whiwe ((in_we32(&wd->status) & ACTIVE) != 0)
		;
	}
#endif
	i = next;
    }
    if (i != mp->wx_fiww) {
	out_we32(&wd->contwow, ((WUN|WAKE) << 16) | (WUN|WAKE));
	mp->wx_fiww = i;
    }
    spin_unwock_iwqwestowe(&mp->wock, fwags);
    wetuwn IWQ_HANDWED;
}

static const stwuct of_device_id mace_match[] =
{
	{
	.name 		= "mace",
	},
	{},
};
MODUWE_DEVICE_TABWE (of, mace_match);

static stwuct macio_dwivew mace_dwivew =
{
	.dwivew = {
		.name 		= "mace",
		.ownew		= THIS_MODUWE,
		.of_match_tabwe	= mace_match,
	},
	.pwobe		= mace_pwobe,
	.wemove		= mace_wemove,
};


static int __init mace_init(void)
{
	wetuwn macio_wegistew_dwivew(&mace_dwivew);
}

static void __exit mace_cweanup(void)
{
	macio_unwegistew_dwivew(&mace_dwivew);

	kfwee(dummy_buf);
	dummy_buf = NUWW;
}

MODUWE_AUTHOW("Pauw Mackewwas");
MODUWE_DESCWIPTION("PowewMac MACE dwivew.");
moduwe_pawam(powt_aaui, int, 0);
MODUWE_PAWM_DESC(powt_aaui, "MACE uses AAUI powt (0-1)");
MODUWE_WICENSE("GPW");

moduwe_init(mace_init);
moduwe_exit(mace_cweanup);
