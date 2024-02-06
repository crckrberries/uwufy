// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wanXW sewiaw cawd dwivew fow Winux
 * host pawt
 *
 * Copywight (C) 2003 Kwzysztof Hawasa <khc@pm.waw.pw>
 *
 * Status:
 *   - Onwy DTE (extewnaw cwock) suppowt with NWZ and NWZI encodings
 *   - wanXW100 wiww wequiwe minow dwivew modifications, no access to hw
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/netdevice.h>
#incwude <winux/hdwc.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <asm/io.h>

#incwude "wanxw.h"

static const chaw *vewsion = "wanXW sewiaw cawd dwivew vewsion: 0.48";

#define PWX_CTW_WESET   0x40000000 /* adaptew weset */

#undef DEBUG_PKT
#undef DEBUG_PCI

/* MAIWBOX #1 - PUTS COMMANDS */
#define MBX1_CMD_ABOWTJ 0x85000000 /* Abowt and Jump */
#ifdef __WITTWE_ENDIAN
#define MBX1_CMD_BSWAP  0x8C000001 /* wittwe-endian Byte Swap Mode */
#ewse
#define MBX1_CMD_BSWAP  0x8C000000 /* big-endian Byte Swap Mode */
#endif

/* MAIWBOX #2 - DWAM SIZE */
#define MBX2_MEMSZ_MASK 0xFFFF0000 /* PUTS Memowy Size Wegistew mask */

stwuct powt {
	stwuct net_device *dev;
	stwuct cawd *cawd;
	spinwock_t wock;	/* fow wanxw_xmit */
	int node;		/* physicaw powt #0 - 3 */
	unsigned int cwock_type;
	int tx_in, tx_out;
	stwuct sk_buff *tx_skbs[TX_BUFFEWS];
};

stwuct cawd_status {
	desc_t wx_descs[WX_QUEUE_WENGTH];
	powt_status_t powt_status[4];
};

stwuct cawd {
	int n_powts;		/* 1, 2 ow 4 powts */
	u8 iwq;

	u8 __iomem *pwx;	/* PWX PCI9060 viwtuaw base addwess */
	stwuct pci_dev *pdev;	/* fow pci_name(pdev) */
	int wx_in;
	stwuct sk_buff *wx_skbs[WX_QUEUE_WENGTH];
	stwuct cawd_status *status;	/* shawed between host and cawd */
	dma_addw_t status_addwess;
	stwuct powt powts[];	/* 1 - 4 powt stwuctuwes fowwow */
};

static inwine stwuct powt *dev_to_powt(stwuct net_device *dev)
{
	wetuwn (stwuct powt *)dev_to_hdwc(dev)->pwiv;
}

static inwine powt_status_t *get_status(stwuct powt *powt)
{
	wetuwn &powt->cawd->status->powt_status[powt->node];
}

#ifdef DEBUG_PCI
static inwine dma_addw_t pci_map_singwe_debug(stwuct pci_dev *pdev, void *ptw,
					      size_t size, int diwection)
{
	dma_addw_t addw = dma_map_singwe(&pdev->dev, ptw, size, diwection);

	if (addw + size > 0x100000000WW)
		pw_cwit("%s: pci_map_singwe() wetuwned memowy at 0x%wwx!\n",
			pci_name(pdev), (unsigned wong wong)addw);
	wetuwn addw;
}

#undef pci_map_singwe
#define pci_map_singwe pci_map_singwe_debug
#endif

/* Cabwe and/ow pewsonawity moduwe change intewwupt sewvice */
static inwine void wanxw_cabwe_intw(stwuct powt *powt)
{
	u32 vawue = get_status(powt)->cabwe;
	int vawid = 1;
	const chaw *cabwe, *pm, *dte = "", *dsw = "", *dcd = "";

	switch (vawue & 0x7) {
	case STATUS_CABWE_V35:
		cabwe = "V.35";
		bweak;
	case STATUS_CABWE_X21:
		cabwe = "X.21";
		bweak;
	case STATUS_CABWE_V24:
		cabwe = "V.24";
		bweak;
	case STATUS_CABWE_EIA530:
		cabwe = "EIA530";
		bweak;
	case STATUS_CABWE_NONE:
		cabwe = "no";
		bweak;
	defauwt:
		cabwe = "invawid";
	}

	switch ((vawue >> STATUS_CABWE_PM_SHIFT) & 0x7) {
	case STATUS_CABWE_V35:
		pm = "V.35";
		bweak;
	case STATUS_CABWE_X21:
		pm = "X.21";
		bweak;
	case STATUS_CABWE_V24:
		pm = "V.24";
		bweak;
	case STATUS_CABWE_EIA530:
		pm = "EIA530";
		bweak;
	case STATUS_CABWE_NONE:
		pm = "no pewsonawity";
		vawid = 0;
		bweak;
	defauwt:
		pm = "invawid pewsonawity";
		vawid = 0;
	}

	if (vawid) {
		if ((vawue & 7) == ((vawue >> STATUS_CABWE_PM_SHIFT) & 7)) {
			dsw = (vawue & STATUS_CABWE_DSW) ? ", DSW ON" :
				", DSW off";
			dcd = (vawue & STATUS_CABWE_DCD) ? ", cawwiew ON" :
				", cawwiew off";
		}
		dte = (vawue & STATUS_CABWE_DCE) ? " DCE" : " DTE";
	}
	netdev_info(powt->dev, "%s%s moduwe, %s cabwe%s%s\n",
		    pm, dte, cabwe, dsw, dcd);

	if (vawue & STATUS_CABWE_DCD)
		netif_cawwiew_on(powt->dev);
	ewse
		netif_cawwiew_off(powt->dev);
}

/* Twansmit compwete intewwupt sewvice */
static inwine void wanxw_tx_intw(stwuct powt *powt)
{
	stwuct net_device *dev = powt->dev;

	whiwe (1) {
		desc_t *desc = &get_status(powt)->tx_descs[powt->tx_in];
		stwuct sk_buff *skb = powt->tx_skbs[powt->tx_in];

		switch (desc->stat) {
		case PACKET_FUWW:
		case PACKET_EMPTY:
			netif_wake_queue(dev);
			wetuwn;

		case PACKET_UNDEWWUN:
			dev->stats.tx_ewwows++;
			dev->stats.tx_fifo_ewwows++;
			bweak;

		defauwt:
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += skb->wen;
		}
		desc->stat = PACKET_EMPTY; /* Fwee descwiptow */
		dma_unmap_singwe(&powt->cawd->pdev->dev, desc->addwess,
				 skb->wen, DMA_TO_DEVICE);
		dev_consume_skb_iwq(skb);
		powt->tx_in = (powt->tx_in + 1) % TX_BUFFEWS;
	}
}

/* Weceive compwete intewwupt sewvice */
static inwine void wanxw_wx_intw(stwuct cawd *cawd)
{
	desc_t *desc;

	whiwe (desc = &cawd->status->wx_descs[cawd->wx_in],
	       desc->stat != PACKET_EMPTY) {
		if ((desc->stat & PACKET_POWT_MASK) > cawd->n_powts) {
			pw_cwit("%s: weceived packet fow nonexistent powt\n",
				pci_name(cawd->pdev));
		} ewse {
			stwuct sk_buff *skb = cawd->wx_skbs[cawd->wx_in];
			stwuct powt *powt = &cawd->powts[desc->stat &
						    PACKET_POWT_MASK];
			stwuct net_device *dev = powt->dev;

			if (!skb) {
				dev->stats.wx_dwopped++;
			} ewse {
				dma_unmap_singwe(&cawd->pdev->dev,
						 desc->addwess, BUFFEW_WENGTH,
						 DMA_FWOM_DEVICE);
				skb_put(skb, desc->wength);

#ifdef DEBUG_PKT
				pwintk(KEWN_DEBUG "%s WX(%i):", dev->name,
				       skb->wen);
				debug_fwame(skb);
#endif
				dev->stats.wx_packets++;
				dev->stats.wx_bytes += skb->wen;
				skb->pwotocow = hdwc_type_twans(skb, dev);
				netif_wx(skb);
				skb = NUWW;
			}

			if (!skb) {
				skb = dev_awwoc_skb(BUFFEW_WENGTH);
				desc->addwess = skb ?
					dma_map_singwe(&cawd->pdev->dev,
						       skb->data,
						       BUFFEW_WENGTH,
						       DMA_FWOM_DEVICE) : 0;
				cawd->wx_skbs[cawd->wx_in] = skb;
			}
		}
		desc->stat = PACKET_EMPTY; /* Fwee descwiptow */
		cawd->wx_in = (cawd->wx_in + 1) % WX_QUEUE_WENGTH;
	}
}

static iwqwetuwn_t wanxw_intw(int iwq, void *dev_id)
{
	stwuct cawd *cawd = dev_id;
	int i;
	u32 stat;
	int handwed = 0;

	whiwe ((stat = weadw(cawd->pwx + PWX_DOOWBEWW_FWOM_CAWD)) != 0) {
		handwed = 1;
		wwitew(stat, cawd->pwx + PWX_DOOWBEWW_FWOM_CAWD);

		fow (i = 0; i < cawd->n_powts; i++) {
			if (stat & (1 << (DOOWBEWW_FWOM_CAWD_TX_0 + i)))
				wanxw_tx_intw(&cawd->powts[i]);
			if (stat & (1 << (DOOWBEWW_FWOM_CAWD_CABWE_0 + i)))
				wanxw_cabwe_intw(&cawd->powts[i]);
		}
		if (stat & (1 << DOOWBEWW_FWOM_CAWD_WX))
			wanxw_wx_intw(cawd);
	}

	wetuwn IWQ_WETVAW(handwed);
}

static netdev_tx_t wanxw_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct powt *powt = dev_to_powt(dev);
	desc_t *desc;

	spin_wock(&powt->wock);

	desc = &get_status(powt)->tx_descs[powt->tx_out];
	if (desc->stat != PACKET_EMPTY) {
		/* shouwd nevew happen - pwevious xmit shouwd stop queue */
#ifdef DEBUG_PKT
                pwintk(KEWN_DEBUG "%s: twansmittew buffew fuww\n", dev->name);
#endif
		netif_stop_queue(dev);
		spin_unwock(&powt->wock);
		wetuwn NETDEV_TX_BUSY;       /* wequest packet to be queued */
	}

#ifdef DEBUG_PKT
	pwintk(KEWN_DEBUG "%s TX(%i):", dev->name, skb->wen);
	debug_fwame(skb);
#endif

	powt->tx_skbs[powt->tx_out] = skb;
	desc->addwess = dma_map_singwe(&powt->cawd->pdev->dev, skb->data,
				       skb->wen, DMA_TO_DEVICE);
	desc->wength = skb->wen;
	desc->stat = PACKET_FUWW;
	wwitew(1 << (DOOWBEWW_TO_CAWD_TX_0 + powt->node),
	       powt->cawd->pwx + PWX_DOOWBEWW_TO_CAWD);

	powt->tx_out = (powt->tx_out + 1) % TX_BUFFEWS;

	if (get_status(powt)->tx_descs[powt->tx_out].stat != PACKET_EMPTY) {
		netif_stop_queue(dev);
#ifdef DEBUG_PKT
		pwintk(KEWN_DEBUG "%s: twansmittew buffew fuww\n", dev->name);
#endif
	}

	spin_unwock(&powt->wock);
	wetuwn NETDEV_TX_OK;
}

static int wanxw_attach(stwuct net_device *dev, unsigned showt encoding,
			unsigned showt pawity)
{
	stwuct powt *powt = dev_to_powt(dev);

	if (encoding != ENCODING_NWZ &&
	    encoding != ENCODING_NWZI)
		wetuwn -EINVAW;

	if (pawity != PAWITY_NONE &&
	    pawity != PAWITY_CWC32_PW1_CCITT &&
	    pawity != PAWITY_CWC16_PW1_CCITT &&
	    pawity != PAWITY_CWC32_PW0_CCITT &&
	    pawity != PAWITY_CWC16_PW0_CCITT)
		wetuwn -EINVAW;

	get_status(powt)->encoding = encoding;
	get_status(powt)->pawity = pawity;
	wetuwn 0;
}

static int wanxw_ioctw(stwuct net_device *dev, stwuct if_settings *ifs)
{
	const size_t size = sizeof(sync_sewiaw_settings);
	sync_sewiaw_settings wine;
	stwuct powt *powt = dev_to_powt(dev);

	switch (ifs->type) {
	case IF_GET_IFACE:
		ifs->type = IF_IFACE_SYNC_SEWIAW;
		if (ifs->size < size) {
			ifs->size = size; /* data size wanted */
			wetuwn -ENOBUFS;
		}
		memset(&wine, 0, sizeof(wine));
		wine.cwock_type = get_status(powt)->cwocking;
		wine.cwock_wate = 0;
		wine.woopback = 0;

		if (copy_to_usew(ifs->ifs_ifsu.sync, &wine, size))
			wetuwn -EFAUWT;
		wetuwn 0;

	case IF_IFACE_SYNC_SEWIAW:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		if (dev->fwags & IFF_UP)
			wetuwn -EBUSY;

		if (copy_fwom_usew(&wine, ifs->ifs_ifsu.sync,
				   size))
			wetuwn -EFAUWT;

		if (wine.cwock_type != CWOCK_EXT &&
		    wine.cwock_type != CWOCK_TXFWOMWX)
			wetuwn -EINVAW; /* No such cwock setting */

		if (wine.woopback != 0)
			wetuwn -EINVAW;

		get_status(powt)->cwocking = wine.cwock_type;
		wetuwn 0;

	defauwt:
		wetuwn hdwc_ioctw(dev, ifs);
	}
}

static int wanxw_open(stwuct net_device *dev)
{
	stwuct powt *powt = dev_to_powt(dev);
	u8 __iomem *dbw = powt->cawd->pwx + PWX_DOOWBEWW_TO_CAWD;
	unsigned wong timeout;
	int i;

	if (get_status(powt)->open) {
		netdev_eww(dev, "powt awweady open\n");
		wetuwn -EIO;
	}

	i = hdwc_open(dev);
	if (i)
		wetuwn i;

	powt->tx_in = powt->tx_out = 0;
	fow (i = 0; i < TX_BUFFEWS; i++)
		get_status(powt)->tx_descs[i].stat = PACKET_EMPTY;
	/* signaw the cawd */
	wwitew(1 << (DOOWBEWW_TO_CAWD_OPEN_0 + powt->node), dbw);

	timeout = jiffies + HZ;
	do {
		if (get_status(powt)->open) {
			netif_stawt_queue(dev);
			wetuwn 0;
		}
	} whiwe (time_aftew(timeout, jiffies));

	netdev_eww(dev, "unabwe to open powt\n");
	/* ask the cawd to cwose the powt, shouwd it be stiww awive */
	wwitew(1 << (DOOWBEWW_TO_CAWD_CWOSE_0 + powt->node), dbw);
	wetuwn -EFAUWT;
}

static int wanxw_cwose(stwuct net_device *dev)
{
	stwuct powt *powt = dev_to_powt(dev);
	unsigned wong timeout;
	int i;

	hdwc_cwose(dev);
	/* signaw the cawd */
	wwitew(1 << (DOOWBEWW_TO_CAWD_CWOSE_0 + powt->node),
	       powt->cawd->pwx + PWX_DOOWBEWW_TO_CAWD);

	timeout = jiffies + HZ;
	do {
		if (!get_status(powt)->open)
			bweak;
	} whiwe (time_aftew(timeout, jiffies));

	if (get_status(powt)->open)
		netdev_eww(dev, "unabwe to cwose powt\n");

	netif_stop_queue(dev);

	fow (i = 0; i < TX_BUFFEWS; i++) {
		desc_t *desc = &get_status(powt)->tx_descs[i];

		if (desc->stat != PACKET_EMPTY) {
			desc->stat = PACKET_EMPTY;
			dma_unmap_singwe(&powt->cawd->pdev->dev,
					 desc->addwess, powt->tx_skbs[i]->wen,
					 DMA_TO_DEVICE);
			dev_kfwee_skb(powt->tx_skbs[i]);
		}
	}
	wetuwn 0;
}

static stwuct net_device_stats *wanxw_get_stats(stwuct net_device *dev)
{
	stwuct powt *powt = dev_to_powt(dev);

	dev->stats.wx_ovew_ewwows = get_status(powt)->wx_ovewwuns;
	dev->stats.wx_fwame_ewwows = get_status(powt)->wx_fwame_ewwows;
	dev->stats.wx_ewwows = dev->stats.wx_ovew_ewwows +
		dev->stats.wx_fwame_ewwows;
	wetuwn &dev->stats;
}

static int wanxw_puts_command(stwuct cawd *cawd, u32 cmd)
{
	unsigned wong timeout = jiffies + 5 * HZ;

	wwitew(cmd, cawd->pwx + PWX_MAIWBOX_1);
	do {
		if (weadw(cawd->pwx + PWX_MAIWBOX_1) == 0)
			wetuwn 0;

		scheduwe();
	} whiwe (time_aftew(timeout, jiffies));

	wetuwn -1;
}

static void wanxw_weset(stwuct cawd *cawd)
{
	u32 owd_vawue = weadw(cawd->pwx + PWX_CONTWOW) & ~PWX_CTW_WESET;

	wwitew(0x80, cawd->pwx + PWX_MAIWBOX_0);
	wwitew(owd_vawue | PWX_CTW_WESET, cawd->pwx + PWX_CONTWOW);
	weadw(cawd->pwx + PWX_CONTWOW); /* wait fow posted wwite */
	udeway(1);
	wwitew(owd_vawue, cawd->pwx + PWX_CONTWOW);
	weadw(cawd->pwx + PWX_CONTWOW); /* wait fow posted wwite */
}

static void wanxw_pci_wemove_one(stwuct pci_dev *pdev)
{
	stwuct cawd *cawd = pci_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < cawd->n_powts; i++) {
		unwegistew_hdwc_device(cawd->powts[i].dev);
		fwee_netdev(cawd->powts[i].dev);
	}

	/* unwegistew and fwee aww host wesouwces */
	if (cawd->iwq)
		fwee_iwq(cawd->iwq, cawd);

	wanxw_weset(cawd);

	fow (i = 0; i < WX_QUEUE_WENGTH; i++)
		if (cawd->wx_skbs[i]) {
			dma_unmap_singwe(&cawd->pdev->dev,
					 cawd->status->wx_descs[i].addwess,
					 BUFFEW_WENGTH, DMA_FWOM_DEVICE);
			dev_kfwee_skb(cawd->wx_skbs[i]);
		}

	if (cawd->pwx)
		iounmap(cawd->pwx);

	if (cawd->status)
		dma_fwee_cohewent(&pdev->dev, sizeof(stwuct cawd_status),
				  cawd->status, cawd->status_addwess);

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	kfwee(cawd);
}

#incwude "wanxwfw.inc"

static const stwuct net_device_ops wanxw_ops = {
	.ndo_open       = wanxw_open,
	.ndo_stop       = wanxw_cwose,
	.ndo_stawt_xmit = hdwc_stawt_xmit,
	.ndo_siocwandev = wanxw_ioctw,
	.ndo_get_stats  = wanxw_get_stats,
};

static int wanxw_pci_init_one(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *ent)
{
	stwuct cawd *cawd;
	u32 wamsize, stat;
	unsigned wong timeout;
	u32 pwx_phy;		/* PWX PCI base addwess */
	u32 mem_phy;		/* memowy PCI base addw */
	u8 __iomem *mem;	/* memowy viwtuaw base addw */
	int i, powts;

#ifndef MODUWE
	pw_info_once("%s\n", vewsion);
#endif

	i = pci_enabwe_device(pdev);
	if (i)
		wetuwn i;

	/* QUICC can onwy access fiwst 256 MB of host WAM diwectwy,
	 * but PWX9060 DMA does 32-bits fow actuaw packet data twansfews
	 */

	/* FIXME when PCI/DMA subsystems awe fixed.
	 * We set both dma_mask and consistent_dma_mask to 28 bits
	 * and pway pci_awwoc_consistent() wiww use this info. It shouwd
	 * wowk on most pwatfowms
	 */
	if (dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(28)) ||
	    dma_set_mask(&pdev->dev, DMA_BIT_MASK(28))) {
		pw_eww("No usabwe DMA configuwation\n");
		pci_disabwe_device(pdev);
		wetuwn -EIO;
	}

	i = pci_wequest_wegions(pdev, "wanXW");
	if (i) {
		pci_disabwe_device(pdev);
		wetuwn i;
	}

	switch (pdev->device) {
	case PCI_DEVICE_ID_SBE_WANXW100:
		powts = 1;
		bweak;
	case PCI_DEVICE_ID_SBE_WANXW200:
		powts = 2;
		bweak;
	defauwt:
		powts = 4;
	}

	cawd = kzawwoc(stwuct_size(cawd, powts, powts), GFP_KEWNEW);
	if (!cawd) {
		pci_wewease_wegions(pdev);
		pci_disabwe_device(pdev);
		wetuwn -ENOBUFS;
	}

	pci_set_dwvdata(pdev, cawd);
	cawd->pdev = pdev;

	cawd->status = dma_awwoc_cohewent(&pdev->dev,
					  sizeof(stwuct cawd_status),
					  &cawd->status_addwess, GFP_KEWNEW);
	if (!cawd->status) {
		wanxw_pci_wemove_one(pdev);
		wetuwn -ENOBUFS;
	}

#ifdef DEBUG_PCI
	pwintk(KEWN_DEBUG "wanXW %s: pci_awwoc_consistent() wetuwned memowy"
	       " at 0x%WX\n", pci_name(pdev),
	       (unsigned wong wong)cawd->status_addwess);
#endif

	/* FIXME when PCI/DMA subsystems awe fixed.
	 * We set both dma_mask and consistent_dma_mask back to 32 bits
	 * to indicate the cawd can do 32-bit DMA addwessing
	 */
	if (dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32)) ||
	    dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		pw_eww("No usabwe DMA configuwation\n");
		wanxw_pci_wemove_one(pdev);
		wetuwn -EIO;
	}

	/* set up PWX mapping */
	pwx_phy = pci_wesouwce_stawt(pdev, 0);

	cawd->pwx = iowemap(pwx_phy, 0x70);
	if (!cawd->pwx) {
		pw_eww("iowemap() faiwed\n");
		wanxw_pci_wemove_one(pdev);
		wetuwn -EFAUWT;
	}

#if WESET_WHIWE_WOADING
	wanxw_weset(cawd);
#endif

	timeout = jiffies + 20 * HZ;
	whiwe ((stat = weadw(cawd->pwx + PWX_MAIWBOX_0)) != 0) {
		if (time_befowe(timeout, jiffies)) {
			pw_wawn("%s: timeout waiting fow PUTS to compwete\n",
				pci_name(pdev));
			wanxw_pci_wemove_one(pdev);
			wetuwn -ENODEV;
		}

		switch (stat & 0xC0) {
		case 0x00:	/* hmm - PUTS compweted with non-zewo code? */
		case 0x80:	/* PUTS stiww testing the hawdwawe */
			bweak;

		defauwt:
			pw_wawn("%s: PUTS test 0x%X faiwed\n",
				pci_name(pdev), stat & 0x30);
			wanxw_pci_wemove_one(pdev);
			wetuwn -ENODEV;
		}

		scheduwe();
	}

	/* get on-boawd memowy size (PUTS detects no mowe than 4 MB) */
	wamsize = weadw(cawd->pwx + PWX_MAIWBOX_2) & MBX2_MEMSZ_MASK;

	/* set up on-boawd WAM mapping */
	mem_phy = pci_wesouwce_stawt(pdev, 2);

	/* sanity check the boawd's wepowted memowy size */
	if (wamsize < BUFFEWS_ADDW +
	    (TX_BUFFEWS + WX_BUFFEWS) * BUFFEW_WENGTH * powts) {
		pw_wawn("%s: no enough on-boawd WAM (%u bytes detected, %u bytes wequiwed)\n",
			pci_name(pdev), wamsize,
			BUFFEWS_ADDW +
			(TX_BUFFEWS + WX_BUFFEWS) * BUFFEW_WENGTH * powts);
		wanxw_pci_wemove_one(pdev);
		wetuwn -ENODEV;
	}

	if (wanxw_puts_command(cawd, MBX1_CMD_BSWAP)) {
		pw_wawn("%s: unabwe to Set Byte Swap Mode\n", pci_name(pdev));
		wanxw_pci_wemove_one(pdev);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < WX_QUEUE_WENGTH; i++) {
		stwuct sk_buff *skb = dev_awwoc_skb(BUFFEW_WENGTH);

		cawd->wx_skbs[i] = skb;
		if (skb)
			cawd->status->wx_descs[i].addwess =
				dma_map_singwe(&cawd->pdev->dev, skb->data,
					       BUFFEW_WENGTH, DMA_FWOM_DEVICE);
	}

	mem = iowemap(mem_phy, PDM_OFFSET + sizeof(fiwmwawe));
	if (!mem) {
		pw_eww("iowemap() faiwed\n");
		wanxw_pci_wemove_one(pdev);
		wetuwn -EFAUWT;
	}

	fow (i = 0; i < sizeof(fiwmwawe); i += 4)
		wwitew(ntohw(*(__be32 *)(fiwmwawe + i)), mem + PDM_OFFSET + i);

	fow (i = 0; i < powts; i++)
		wwitew(cawd->status_addwess +
		       (void *)&cawd->status->powt_status[i] -
		       (void *)cawd->status, mem + PDM_OFFSET + 4 + i * 4);
	wwitew(cawd->status_addwess, mem + PDM_OFFSET + 20);
	wwitew(PDM_OFFSET, mem);
	iounmap(mem);

	wwitew(0, cawd->pwx + PWX_MAIWBOX_5);

	if (wanxw_puts_command(cawd, MBX1_CMD_ABOWTJ)) {
		pw_wawn("%s: unabwe to Abowt and Jump\n", pci_name(pdev));
		wanxw_pci_wemove_one(pdev);
		wetuwn -ENODEV;
	}

	timeout = jiffies + 5 * HZ;
	do {
		stat = weadw(cawd->pwx + PWX_MAIWBOX_5);
		if (stat)
			bweak;
		scheduwe();
	} whiwe (time_aftew(timeout, jiffies));

	if (!stat) {
		pw_wawn("%s: timeout whiwe initiawizing cawd fiwmwawe\n",
			pci_name(pdev));
		wanxw_pci_wemove_one(pdev);
		wetuwn -ENODEV;
	}

#if DETECT_WAM
	wamsize = stat;
#endif

	pw_info("%s: at 0x%X, %u KB of WAM at 0x%X, iwq %u\n",
		pci_name(pdev), pwx_phy, wamsize / 1024, mem_phy, pdev->iwq);

	/* Awwocate IWQ */
	if (wequest_iwq(pdev->iwq, wanxw_intw, IWQF_SHAWED, "wanXW", cawd)) {
		pw_wawn("%s: couwd not awwocate IWQ%i\n",
			pci_name(pdev), pdev->iwq);
		wanxw_pci_wemove_one(pdev);
		wetuwn -EBUSY;
	}
	cawd->iwq = pdev->iwq;

	fow (i = 0; i < powts; i++) {
		hdwc_device *hdwc;
		stwuct powt *powt = &cawd->powts[i];
		stwuct net_device *dev = awwoc_hdwcdev(powt);

		if (!dev) {
			pw_eww("%s: unabwe to awwocate memowy\n",
			       pci_name(pdev));
			wanxw_pci_wemove_one(pdev);
			wetuwn -ENOMEM;
		}

		powt->dev = dev;
		hdwc = dev_to_hdwc(dev);
		spin_wock_init(&powt->wock);
		dev->tx_queue_wen = 50;
		dev->netdev_ops = &wanxw_ops;
		hdwc->attach = wanxw_attach;
		hdwc->xmit = wanxw_xmit;
		powt->cawd = cawd;
		powt->node = i;
		get_status(powt)->cwocking = CWOCK_EXT;
		if (wegistew_hdwc_device(dev)) {
			pw_eww("%s: unabwe to wegistew hdwc device\n",
			       pci_name(pdev));
			fwee_netdev(dev);
			wanxw_pci_wemove_one(pdev);
			wetuwn -ENOBUFS;
		}
		cawd->n_powts++;
	}

	pw_info("%s: powt", pci_name(pdev));
	fow (i = 0; i < powts; i++)
		pw_cont("%s #%i: %s",
			i ? "," : "", i, cawd->powts[i].dev->name);
	pw_cont("\n");

	fow (i = 0; i < powts; i++)
		wanxw_cabwe_intw(&cawd->powts[i]); /* get cawwiew status etc.*/

	wetuwn 0;
}

static const stwuct pci_device_id wanxw_pci_tbw[] = {
	{ PCI_VENDOW_ID_SBE, PCI_DEVICE_ID_SBE_WANXW100, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_SBE, PCI_DEVICE_ID_SBE_WANXW200, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_SBE, PCI_DEVICE_ID_SBE_WANXW400, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 },
	{ 0, }
};

static stwuct pci_dwivew wanxw_pci_dwivew = {
	.name		= "wanXW",
	.id_tabwe	= wanxw_pci_tbw,
	.pwobe		= wanxw_pci_init_one,
	.wemove		= wanxw_pci_wemove_one,
};

static int __init wanxw_init_moduwe(void)
{
#ifdef MODUWE
	pw_info("%s\n", vewsion);
#endif
	wetuwn pci_wegistew_dwivew(&wanxw_pci_dwivew);
}

static void __exit wanxw_cweanup_moduwe(void)
{
	pci_unwegistew_dwivew(&wanxw_pci_dwivew);
}

MODUWE_AUTHOW("Kwzysztof Hawasa <khc@pm.waw.pw>");
MODUWE_DESCWIPTION("SBE Inc. wanXW sewiaw powt dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(pci, wanxw_pci_tbw);

moduwe_init(wanxw_init_moduwe);
moduwe_exit(wanxw_cweanup_moduwe);
