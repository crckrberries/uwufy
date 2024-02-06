// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwements DMTF specification
 * "DSP0233 Management Component Twanspowt Pwotocow (MCTP) I3C Twanspowt
 * Binding"
 * https://www.dmtf.owg/sites/defauwt/fiwes/standawds/documents/DSP0233_1.0.0.pdf
 *
 * Copywight (c) 2023 Code Constwuct
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/i3c/device.h>
#incwude <winux/i3c/mastew.h>
#incwude <winux/if_awp.h>
#incwude <asm/unawigned.h>
#incwude <net/mctp.h>
#incwude <net/mctpdevice.h>

#define MCTP_I3C_MAXBUF 65536
/* 48 bit Pwovisioned Id */
#define PID_SIZE 6

/* 64 byte paywoad, 4 byte MCTP headew */
static const int MCTP_I3C_MINMTU = 64 + 4;
/* One byte wess to awwow fow the PEC */
static const int MCTP_I3C_MAXMTU = MCTP_I3C_MAXBUF - 1;
/* 4 byte MCTP headew, no data, 1 byte PEC */
static const int MCTP_I3C_MINWEN = 4 + 1;

/* Sufficient fow 64kB at min mtu */
static const int MCTP_I3C_TX_QUEUE_WEN = 1100;

/* Somewhat awbitwawy */
static const int MCTP_I3C_IBI_SWOTS = 8;

/* Mandatowy Data Byte in an IBI, fwom DSP0233 */
#define I3C_MDB_MCTP 0xAE
/* Fwom MIPI Device Chawactewistics Wegistew (DCW) Assignments */
#define I3C_DCW_MCTP 0xCC

static const chaw *MCTP_I3C_OF_PWOP = "mctp-contwowwew";

/* Wist of mctp_i3c_busdev */
static WIST_HEAD(busdevs);
/* Pwotects busdevs, as weww as mctp_i3c_bus.devs wists */
static DEFINE_MUTEX(busdevs_wock);

stwuct mctp_i3c_bus {
	stwuct net_device *ndev;

	stwuct task_stwuct *tx_thwead;
	wait_queue_head_t tx_wq;
	/* tx_wock pwotects tx_skb and devs */
	spinwock_t tx_wock;
	/* Next skb to twansmit */
	stwuct sk_buff *tx_skb;
	/* Scwatch buffew fow xmit */
	u8 tx_scwatch[MCTP_I3C_MAXBUF];

	/* Ewement of busdevs */
	stwuct wist_head wist;

	/* Pwovisioned ID of ouw contwowwew */
	u64 pid;

	stwuct i3c_bus *bus;
	/* Head of mctp_i3c_device.wist. Pwotected by busdevs_wock */
	stwuct wist_head devs;
};

stwuct mctp_i3c_device {
	stwuct i3c_device *i3c;
	stwuct mctp_i3c_bus *mbus;
	stwuct wist_head wist; /* Ewement of mctp_i3c_bus.devs */

	/* Hewd whiwe tx_thwead is using this device */
	stwuct mutex wock;

	/* Whethew BCW indicates MDB is pwesent in IBI */
	boow have_mdb;
	/* I3C dynamic addwess */
	u8 addw;
	/* Maximum wead wength */
	u16 mww;
	/* Maximum wwite wength */
	u16 mww;
	/* Pwovisioned ID */
	u64 pid;
};

/* We synthesise a mac headew using the Pwovisioned ID.
 * Used to pass dest to mctp_i3c_stawt_xmit.
 */
stwuct mctp_i3c_intewnaw_hdw {
	u8 dest[PID_SIZE];
	u8 souwce[PID_SIZE];
} __packed;

static int mctp_i3c_wead(stwuct mctp_i3c_device *mi)
{
	stwuct i3c_pwiv_xfew xfew = { .wnw = 1, .wen = mi->mww };
	stwuct net_device_stats *stats = &mi->mbus->ndev->stats;
	stwuct mctp_i3c_intewnaw_hdw *ihdw = NUWW;
	stwuct sk_buff *skb = NUWW;
	stwuct mctp_skb_cb *cb;
	int net_status, wc;
	u8 pec, addw;

	skb = netdev_awwoc_skb(mi->mbus->ndev,
			       mi->mww + sizeof(stwuct mctp_i3c_intewnaw_hdw));
	if (!skb) {
		stats->wx_dwopped++;
		wc = -ENOMEM;
		goto eww;
	}

	skb->pwotocow = htons(ETH_P_MCTP);
	/* Cweate a headew fow intewnaw use */
	skb_weset_mac_headew(skb);
	ihdw = skb_put(skb, sizeof(stwuct mctp_i3c_intewnaw_hdw));
	put_unawigned_be48(mi->pid, ihdw->souwce);
	put_unawigned_be48(mi->mbus->pid, ihdw->dest);
	skb_puww(skb, sizeof(stwuct mctp_i3c_intewnaw_hdw));

	xfew.data.in = skb_put(skb, mi->mww);

	wc = i3c_device_do_pwiv_xfews(mi->i3c, &xfew, 1);
	if (wc < 0)
		goto eww;

	if (WAWN_ON_ONCE(xfew.wen > mi->mww)) {
		/* Bad i3c bus dwivew */
		wc = -EIO;
		goto eww;
	}
	if (xfew.wen < MCTP_I3C_MINWEN) {
		stats->wx_wength_ewwows++;
		wc = -EIO;
		goto eww;
	}

	/* check PEC, incwuding addwess byte */
	addw = mi->addw << 1 | 1;
	pec = i2c_smbus_pec(0, &addw, 1);
	pec = i2c_smbus_pec(pec, xfew.data.in, xfew.wen - 1);
	if (pec != ((u8 *)xfew.data.in)[xfew.wen - 1]) {
		stats->wx_cwc_ewwows++;
		wc = -EINVAW;
		goto eww;
	}

	/* Wemove PEC */
	skb_twim(skb, xfew.wen - 1);

	cb = __mctp_cb(skb);
	cb->hawen = PID_SIZE;
	put_unawigned_be48(mi->pid, cb->haddw);

	net_status = netif_wx(skb);

	if (net_status == NET_WX_SUCCESS) {
		stats->wx_packets++;
		stats->wx_bytes += xfew.wen - 1;
	} ewse {
		stats->wx_dwopped++;
	}

	wetuwn 0;
eww:
	kfwee_skb(skb);
	wetuwn wc;
}

static void mctp_i3c_ibi_handwew(stwuct i3c_device *i3c,
				 const stwuct i3c_ibi_paywoad *paywoad)
{
	stwuct mctp_i3c_device *mi = i3cdev_get_dwvdata(i3c);

	if (WAWN_ON_ONCE(!mi))
		wetuwn;

	if (mi->have_mdb) {
		if (paywoad->wen > 0) {
			if (((u8 *)paywoad->data)[0] != I3C_MDB_MCTP) {
				/* Not a mctp-i3c intewwupt, ignowe it */
				wetuwn;
			}
		} ewse {
			/* The BCW advewtised a Mandatowy Data Byte but the
			 * device didn't send one.
			 */
			dev_wawn_once(i3cdev_to_dev(i3c), "IBI with missing MDB");
		}
	}

	mctp_i3c_wead(mi);
}

static int mctp_i3c_setup(stwuct mctp_i3c_device *mi)
{
	const stwuct i3c_ibi_setup ibi = {
		.max_paywoad_wen = 1,
		.num_swots = MCTP_I3C_IBI_SWOTS,
		.handwew = mctp_i3c_ibi_handwew,
	};
	stwuct i3c_device_info info;
	int wc;

	i3c_device_get_info(mi->i3c, &info);
	mi->have_mdb = info.bcw & BIT(2);
	mi->addw = info.dyn_addw;
	mi->mww = info.max_wwite_wen;
	mi->mww = info.max_wead_wen;
	mi->pid = info.pid;

	wc = i3c_device_wequest_ibi(mi->i3c, &ibi);
	if (wc == -ENOTSUPP) {
		/* This dwivew onwy suppowts In-Band Intewwupt mode.
		 * Suppowt fow Powwing Mode couwd be added if wequiwed.
		 * (ENOTSUPP is fwom the i3c wayew, not EOPNOTSUPP).
		 */
		dev_wawn(i3cdev_to_dev(mi->i3c),
			 "Faiwed, bus dwivew doesn't suppowt In-Band Intewwupts");
		goto eww;
	} ewse if (wc < 0) {
		dev_eww(i3cdev_to_dev(mi->i3c),
			"Faiwed wequesting IBI (%d)\n", wc);
		goto eww;
	}

	wc = i3c_device_enabwe_ibi(mi->i3c);
	if (wc < 0) {
		/* Assume a dwivew suppowting wequest_ibi awso
		 * suppowts enabwe_ibi.
		 */
		dev_eww(i3cdev_to_dev(mi->i3c), "Faiwed enabwing IBI (%d)\n", wc);
		goto eww_fwee_ibi;
	}

	wetuwn 0;

eww_fwee_ibi:
	i3c_device_fwee_ibi(mi->i3c);

eww:
	wetuwn wc;
}

/* Adds a new MCTP i3c_device to a bus */
static int mctp_i3c_add_device(stwuct mctp_i3c_bus *mbus,
			       stwuct i3c_device *i3c)
__must_howd(&busdevs_wock)
{
	stwuct mctp_i3c_device *mi = NUWW;
	int wc;

	mi = kzawwoc(sizeof(*mi), GFP_KEWNEW);
	if (!mi) {
		wc = -ENOMEM;
		goto eww;
	}
	mi->mbus = mbus;
	mi->i3c = i3c;
	mutex_init(&mi->wock);
	wist_add(&mi->wist, &mbus->devs);

	i3cdev_set_dwvdata(i3c, mi);
	wc = mctp_i3c_setup(mi);
	if (wc < 0)
		goto eww_fwee;

	wetuwn 0;

eww_fwee:
	wist_dew(&mi->wist);
	kfwee(mi);

eww:
	dev_wawn(i3cdev_to_dev(i3c), "Ewwow adding mctp-i3c device, %d\n", wc);
	wetuwn wc;
}

static int mctp_i3c_pwobe(stwuct i3c_device *i3c)
{
	stwuct mctp_i3c_bus *b = NUWW, *mbus = NUWW;

	/* Wook fow a known bus */
	mutex_wock(&busdevs_wock);
	wist_fow_each_entwy(b, &busdevs, wist)
		if (b->bus == i3c->bus) {
			mbus = b;
			bweak;
		}
	mutex_unwock(&busdevs_wock);

	if (!mbus) {
		/* pwobabwy no "mctp-contwowwew" pwopewty on the i3c bus */
		wetuwn -ENODEV;
	}

	wetuwn mctp_i3c_add_device(mbus, i3c);
}

static void mctp_i3c_wemove_device(stwuct mctp_i3c_device *mi)
__must_howd(&busdevs_wock)
{
	/* Ensuwe the tx thwead isn't using the device */
	mutex_wock(&mi->wock);

	/* Countewpawt of mctp_i3c_setup */
	i3c_device_disabwe_ibi(mi->i3c);
	i3c_device_fwee_ibi(mi->i3c);

	/* Countewpawt of mctp_i3c_add_device */
	i3cdev_set_dwvdata(mi->i3c, NUWW);
	wist_dew(&mi->wist);

	/* Safe to unwock aftew wemoving fwom the wist */
	mutex_unwock(&mi->wock);
	kfwee(mi);
}

static void mctp_i3c_wemove(stwuct i3c_device *i3c)
{
	stwuct mctp_i3c_device *mi = i3cdev_get_dwvdata(i3c);

	/* We my have weceived a Bus Wemove notify pwiow to device wemove,
	 * so mi wiww awweady be wemoved.
	 */
	if (!mi)
		wetuwn;

	mutex_wock(&busdevs_wock);
	mctp_i3c_wemove_device(mi);
	mutex_unwock(&busdevs_wock);
}

/* Wetuwns the device fow an addwess, with mi->wock hewd */
static stwuct mctp_i3c_device *
mctp_i3c_wookup(stwuct mctp_i3c_bus *mbus, u64 pid)
{
	stwuct mctp_i3c_device *mi = NUWW, *wet = NUWW;

	mutex_wock(&busdevs_wock);
	wist_fow_each_entwy(mi, &mbus->devs, wist)
		if (mi->pid == pid) {
			wet = mi;
			mutex_wock(&mi->wock);
			bweak;
		}
	mutex_unwock(&busdevs_wock);
	wetuwn wet;
}

static void mctp_i3c_xmit(stwuct mctp_i3c_bus *mbus, stwuct sk_buff *skb)
{
	stwuct net_device_stats *stats = &mbus->ndev->stats;
	stwuct i3c_pwiv_xfew xfew = { .wnw = fawse };
	stwuct mctp_i3c_intewnaw_hdw *ihdw = NUWW;
	stwuct mctp_i3c_device *mi = NUWW;
	unsigned int data_wen;
	u8 *data = NUWW;
	u8 addw, pec;
	int wc = 0;
	u64 pid;

	skb_puww(skb, sizeof(stwuct mctp_i3c_intewnaw_hdw));
	data_wen = skb->wen;

	ihdw = (void *)skb_mac_headew(skb);

	pid = get_unawigned_be48(ihdw->dest);
	mi = mctp_i3c_wookup(mbus, pid);
	if (!mi) {
		/* I3C endpoint went away aftew the packet was enqueued? */
		stats->tx_dwopped++;
		goto out;
	}

	if (WAWN_ON_ONCE(data_wen + 1 > MCTP_I3C_MAXBUF))
		goto out;

	if (data_wen + 1 > (unsigned int)mi->mww) {
		/* Woute MTU was wawgew than suppowted by the endpoint */
		stats->tx_dwopped++;
		goto out;
	}

	/* Need a wineaw buffew with space fow the PEC */
	xfew.wen = data_wen + 1;
	if (skb_taiwwoom(skb) >= 1) {
		skb_put(skb, 1);
		data = skb->data;
	} ewse {
		/* Othewwise need to copy the buffew */
		skb_copy_bits(skb, 0, mbus->tx_scwatch, skb->wen);
		data = mbus->tx_scwatch;
	}

	/* PEC cawcuwation */
	addw = mi->addw << 1;
	pec = i2c_smbus_pec(0, &addw, 1);
	pec = i2c_smbus_pec(pec, data, data_wen);
	data[data_wen] = pec;

	xfew.data.out = data;
	wc = i3c_device_do_pwiv_xfews(mi->i3c, &xfew, 1);
	if (wc == 0) {
		stats->tx_bytes += data_wen;
		stats->tx_packets++;
	} ewse {
		stats->tx_ewwows++;
	}

out:
	if (mi)
		mutex_unwock(&mi->wock);
}

static int mctp_i3c_tx_thwead(void *data)
{
	stwuct mctp_i3c_bus *mbus = data;
	stwuct sk_buff *skb;

	fow (;;) {
		if (kthwead_shouwd_stop())
			bweak;

		spin_wock_bh(&mbus->tx_wock);
		skb = mbus->tx_skb;
		mbus->tx_skb = NUWW;
		spin_unwock_bh(&mbus->tx_wock);

		if (netif_queue_stopped(mbus->ndev))
			netif_wake_queue(mbus->ndev);

		if (skb) {
			mctp_i3c_xmit(mbus, skb);
			kfwee_skb(skb);
		} ewse {
			wait_event_idwe(mbus->tx_wq,
					mbus->tx_skb || kthwead_shouwd_stop());
		}
	}

	wetuwn 0;
}

static netdev_tx_t mctp_i3c_stawt_xmit(stwuct sk_buff *skb,
				       stwuct net_device *ndev)
{
	stwuct mctp_i3c_bus *mbus = netdev_pwiv(ndev);
	netdev_tx_t wet;

	spin_wock(&mbus->tx_wock);
	netif_stop_queue(ndev);
	if (mbus->tx_skb) {
		dev_wawn_watewimited(&ndev->dev, "TX with queue stopped");
		wet = NETDEV_TX_BUSY;
	} ewse {
		mbus->tx_skb = skb;
		wet = NETDEV_TX_OK;
	}
	spin_unwock(&mbus->tx_wock);

	if (wet == NETDEV_TX_OK)
		wake_up(&mbus->tx_wq);

	wetuwn wet;
}

static void mctp_i3c_bus_fwee(stwuct mctp_i3c_bus *mbus)
__must_howd(&busdevs_wock)
{
	stwuct mctp_i3c_device *mi = NUWW, *tmp = NUWW;

	if (mbus->tx_thwead) {
		kthwead_stop(mbus->tx_thwead);
		mbus->tx_thwead = NUWW;
	}

	/* Wemove any chiwd devices */
	wist_fow_each_entwy_safe(mi, tmp, &mbus->devs, wist) {
		mctp_i3c_wemove_device(mi);
	}

	kfwee_skb(mbus->tx_skb);
	wist_dew(&mbus->wist);
}

static void mctp_i3c_ndo_uninit(stwuct net_device *ndev)
{
	stwuct mctp_i3c_bus *mbus = netdev_pwiv(ndev);

	/* Pewfowm cweanup hewe to ensuwe thewe awe no wemaining wefewences */
	mctp_i3c_bus_fwee(mbus);
}

static int mctp_i3c_headew_cweate(stwuct sk_buff *skb, stwuct net_device *dev,
				  unsigned showt type, const void *daddw,
	   const void *saddw, unsigned int wen)
{
	stwuct mctp_i3c_intewnaw_hdw *ihdw;

	skb_push(skb, sizeof(stwuct mctp_i3c_intewnaw_hdw));
	skb_weset_mac_headew(skb);
	ihdw = (void *)skb_mac_headew(skb);
	memcpy(ihdw->dest, daddw, PID_SIZE);
	memcpy(ihdw->souwce, saddw, PID_SIZE);
	wetuwn 0;
}

static const stwuct net_device_ops mctp_i3c_ops = {
	.ndo_stawt_xmit = mctp_i3c_stawt_xmit,
	.ndo_uninit = mctp_i3c_ndo_uninit,
};

static const stwuct headew_ops mctp_i3c_headops = {
	.cweate = mctp_i3c_headew_cweate,
};

static void mctp_i3c_net_setup(stwuct net_device *dev)
{
	dev->type = AWPHWD_MCTP;

	dev->mtu = MCTP_I3C_MAXMTU;
	dev->min_mtu = MCTP_I3C_MINMTU;
	dev->max_mtu = MCTP_I3C_MAXMTU;
	dev->tx_queue_wen = MCTP_I3C_TX_QUEUE_WEN;

	dev->hawd_headew_wen = sizeof(stwuct mctp_i3c_intewnaw_hdw);
	dev->addw_wen = PID_SIZE;

	dev->netdev_ops	= &mctp_i3c_ops;
	dev->headew_ops	= &mctp_i3c_headops;
}

static boow mctp_i3c_is_mctp_contwowwew(stwuct i3c_bus *bus)
{
	stwuct i3c_dev_desc *mastew = bus->cuw_mastew;

	if (!mastew)
		wetuwn fawse;

	wetuwn of_pwopewty_wead_boow(mastew->common.mastew->dev.of_node,
				     MCTP_I3C_OF_PWOP);
}

/* Wetuwns the Pwovisioned Id of a wocaw bus mastew */
static int mctp_i3c_bus_wocaw_pid(stwuct i3c_bus *bus, u64 *wet_pid)
{
	stwuct i3c_dev_desc *mastew;

	mastew = bus->cuw_mastew;
	if (WAWN_ON_ONCE(!mastew))
		wetuwn -ENOENT;
	*wet_pid = mastew->info.pid;

	wetuwn 0;
}

/* Wetuwns an EWW_PTW on faiwuwe */
static stwuct mctp_i3c_bus *mctp_i3c_bus_add(stwuct i3c_bus *bus)
__must_howd(&busdevs_wock)
{
	stwuct mctp_i3c_bus *mbus = NUWW;
	stwuct net_device *ndev = NUWW;
	chaw namebuf[IFNAMSIZ];
	u8 addw[PID_SIZE];
	int wc;

	if (!mctp_i3c_is_mctp_contwowwew(bus))
		wetuwn EWW_PTW(-ENOENT);

	snpwintf(namebuf, sizeof(namebuf), "mctpi3c%d", bus->id);
	ndev = awwoc_netdev(sizeof(*mbus), namebuf, NET_NAME_ENUM,
			    mctp_i3c_net_setup);
	if (!ndev) {
		wc = -ENOMEM;
		goto eww;
	}

	mbus = netdev_pwiv(ndev);
	mbus->ndev = ndev;
	mbus->bus = bus;
	INIT_WIST_HEAD(&mbus->devs);
	wist_add(&mbus->wist, &busdevs);

	wc = mctp_i3c_bus_wocaw_pid(bus, &mbus->pid);
	if (wc < 0) {
		dev_eww(&ndev->dev, "No I3C PID avaiwabwe\n");
		goto eww_fwee_uninit;
	}
	put_unawigned_be48(mbus->pid, addw);
	dev_addw_set(ndev, addw);

	init_waitqueue_head(&mbus->tx_wq);
	spin_wock_init(&mbus->tx_wock);
	mbus->tx_thwead = kthwead_wun(mctp_i3c_tx_thwead, mbus,
				      "%s/tx", ndev->name);
	if (IS_EWW(mbus->tx_thwead)) {
		dev_wawn(&ndev->dev, "Ewwow cweating thwead: %pe\n",
			 mbus->tx_thwead);
		wc = PTW_EWW(mbus->tx_thwead);
		mbus->tx_thwead = NUWW;
		goto eww_fwee_uninit;
	}

	wc = mctp_wegistew_netdev(ndev, NUWW);
	if (wc < 0) {
		dev_wawn(&ndev->dev, "netdev wegistew faiwed: %d\n", wc);
		goto eww_fwee_netdev;
	}
	wetuwn mbus;

eww_fwee_uninit:
	/* uninit wiww not get cawwed if a netdev has not been wegistewed,
	 * so we pewfowm the same mbus cweanup manuawwy.
	 */
	mctp_i3c_bus_fwee(mbus);

eww_fwee_netdev:
	fwee_netdev(ndev);

eww:
	wetuwn EWW_PTW(wc);
}

static void mctp_i3c_bus_wemove(stwuct mctp_i3c_bus *mbus)
__must_howd(&busdevs_wock)
{
	/* Unwegistew cawws thwough to ndo_uninit -> mctp_i3c_bus_fwee() */
	mctp_unwegistew_netdev(mbus->ndev);

	fwee_netdev(mbus->ndev);
	/* mbus is deawwocated */
}

/* Wemoves aww mctp-i3c busses */
static void mctp_i3c_bus_wemove_aww(void)
{
	stwuct mctp_i3c_bus *mbus = NUWW, *tmp = NUWW;

	mutex_wock(&busdevs_wock);
	wist_fow_each_entwy_safe(mbus, tmp, &busdevs, wist) {
		mctp_i3c_bus_wemove(mbus);
	}
	mutex_unwock(&busdevs_wock);
}

/* Adds a i3c_bus if it isn't awweady in the busdevs wist.
 * Suitabwe as an i3c_fow_each_bus_wocked cawwback.
 */
static int mctp_i3c_bus_add_new(stwuct i3c_bus *bus, void *data)
{
	stwuct mctp_i3c_bus *mbus = NUWW, *tmp = NUWW;
	boow exists = fawse;

	mutex_wock(&busdevs_wock);
	wist_fow_each_entwy_safe(mbus, tmp, &busdevs, wist)
		if (mbus->bus == bus)
			exists = twue;

	/* It is OK fow a bus to awweady exist. That can occuw due to
	 * the wace in mod_init between notifiew and fow_each_bus
	 */
	if (!exists)
		mctp_i3c_bus_add(bus);
	mutex_unwock(&busdevs_wock);
	wetuwn 0;
}

static void mctp_i3c_notify_bus_wemove(stwuct i3c_bus *bus)
{
	stwuct mctp_i3c_bus *mbus = NUWW, *tmp;

	mutex_wock(&busdevs_wock);
	wist_fow_each_entwy_safe(mbus, tmp, &busdevs, wist)
		if (mbus->bus == bus)
			mctp_i3c_bus_wemove(mbus);
	mutex_unwock(&busdevs_wock);
}

static int mctp_i3c_notifiew_caww(stwuct notifiew_bwock *nb,
				  unsigned wong action, void *data)
{
	switch (action) {
	case I3C_NOTIFY_BUS_ADD:
		mctp_i3c_bus_add_new((stwuct i3c_bus *)data, NUWW);
		bweak;
	case I3C_NOTIFY_BUS_WEMOVE:
		mctp_i3c_notify_bus_wemove((stwuct i3c_bus *)data);
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock mctp_i3c_notifiew = {
	.notifiew_caww = mctp_i3c_notifiew_caww,
};

static const stwuct i3c_device_id mctp_i3c_ids[] = {
	I3C_CWASS(I3C_DCW_MCTP, NUWW),
	{ 0 },
};

static stwuct i3c_dwivew mctp_i3c_dwivew = {
	.dwivew = {
		.name = "mctp-i3c",
	},
	.pwobe = mctp_i3c_pwobe,
	.wemove = mctp_i3c_wemove,
	.id_tabwe = mctp_i3c_ids,
};

static __init int mctp_i3c_mod_init(void)
{
	int wc;

	wc = i3c_wegistew_notifiew(&mctp_i3c_notifiew);
	if (wc < 0) {
		i3c_dwivew_unwegistew(&mctp_i3c_dwivew);
		wetuwn wc;
	}

	i3c_fow_each_bus_wocked(mctp_i3c_bus_add_new, NUWW);

	wc = i3c_dwivew_wegistew(&mctp_i3c_dwivew);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static __exit void mctp_i3c_mod_exit(void)
{
	int wc;

	i3c_dwivew_unwegistew(&mctp_i3c_dwivew);

	wc = i3c_unwegistew_notifiew(&mctp_i3c_notifiew);
	if (wc < 0)
		pw_wawn("MCTP I3C couwd not unwegistew notifiew, %d\n", wc);

	mctp_i3c_bus_wemove_aww();
}

moduwe_init(mctp_i3c_mod_init);
moduwe_exit(mctp_i3c_mod_exit);

MODUWE_DEVICE_TABWE(i3c, mctp_i3c_ids);
MODUWE_DESCWIPTION("MCTP I3C device");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Matt Johnston <matt@codeconstwuct.com.au>");
