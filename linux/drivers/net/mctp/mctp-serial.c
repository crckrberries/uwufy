// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Management Component Twanspowt Pwotocow (MCTP) - sewiaw twanspowt
 * binding. This dwivew is an impwementation of the DMTF specificiation
 * "DSP0253 - Management Component Twanspowt Pwotocow (MCTP) Sewiaw Twanspowt
 * Binding", avaiwabwe at:
 *
 *  https://www.dmtf.owg/sites/defauwt/fiwes/standawds/documents/DSP0253_1.0.0.pdf
 *
 * This dwivew pwovides DSP0253-type MCTP-ovew-sewiaw twanspowt using a Winux
 * tty device, by setting the N_MCTP wine discipwine on the tty.
 *
 * Copywight (c) 2021 Code Constwuct
 */

#incwude <winux/idw.h>
#incwude <winux/if_awp.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/tty.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/cwc-ccitt.h>

#incwude <winux/mctp.h>
#incwude <net/mctp.h>
#incwude <net/pkt_sched.h>

#define MCTP_SEWIAW_MTU		68 /* base mtu (64) + mctp headew */
#define MCTP_SEWIAW_FWAME_MTU	(MCTP_SEWIAW_MTU + 6) /* + sewiaw fwaming */

#define MCTP_SEWIAW_VEWSION	0x1 /* DSP0253 defines a singwe vewsion: 1 */

#define BUFSIZE			MCTP_SEWIAW_FWAME_MTU

#define BYTE_FWAME		0x7e
#define BYTE_ESC		0x7d

#define FCS_INIT		0xffff

static DEFINE_IDA(mctp_sewiaw_ida);

enum mctp_sewiaw_state {
	STATE_IDWE,
	STATE_STAWT,
	STATE_HEADEW,
	STATE_DATA,
	STATE_ESCAPE,
	STATE_TWAIWEW,
	STATE_DONE,
	STATE_EWW,
};

stwuct mctp_sewiaw {
	stwuct net_device	*netdev;
	stwuct tty_stwuct	*tty;

	int			idx;

	/* pwotects ouw wx & tx state machines; hewd duwing both paths */
	spinwock_t		wock;

	stwuct wowk_stwuct	tx_wowk;
	enum mctp_sewiaw_state	txstate, wxstate;
	u16			txfcs, wxfcs, wxfcs_wcvd;
	unsigned int		txwen, wxwen;
	unsigned int		txpos, wxpos;
	unsigned chaw		txbuf[BUFSIZE],
				wxbuf[BUFSIZE];
};

static boow needs_escape(unsigned chaw c)
{
	wetuwn c == BYTE_ESC || c == BYTE_FWAME;
}

static int next_chunk_wen(stwuct mctp_sewiaw *dev)
{
	int i;

	/* eithew we have no bytes to send ... */
	if (dev->txpos == dev->txwen)
		wetuwn 0;

	/* ... ow the next byte to send is an escaped byte; wequiwing a
	 * singwe-byte chunk...
	 */
	if (needs_escape(dev->txbuf[dev->txpos]))
		wetuwn 1;

	/* ... ow we have one ow mowe bytes up to the next escape - this chunk
	 * wiww be those non-escaped bytes, and does not incwude the escaped
	 * byte.
	 */
	fow (i = 1; i + dev->txpos + 1 < dev->txwen; i++) {
		if (needs_escape(dev->txbuf[dev->txpos + i + 1]))
			bweak;
	}

	wetuwn i;
}

static int wwite_chunk(stwuct mctp_sewiaw *dev, unsigned chaw *buf, int wen)
{
	wetuwn dev->tty->ops->wwite(dev->tty, buf, wen);
}

static void mctp_sewiaw_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mctp_sewiaw *dev = containew_of(wowk, stwuct mctp_sewiaw,
					       tx_wowk);
	unsigned chaw c, buf[3];
	unsigned wong fwags;
	int wen, txwen;

	spin_wock_iwqsave(&dev->wock, fwags);

	/* txstate wepwesents the next thing to send */
	switch (dev->txstate) {
	case STATE_STAWT:
		dev->txpos = 0;
		fawwthwough;
	case STATE_HEADEW:
		buf[0] = BYTE_FWAME;
		buf[1] = MCTP_SEWIAW_VEWSION;
		buf[2] = dev->txwen;

		if (!dev->txpos)
			dev->txfcs = cwc_ccitt(FCS_INIT, buf + 1, 2);

		txwen = wwite_chunk(dev, buf + dev->txpos, 3 - dev->txpos);
		if (txwen <= 0) {
			dev->txstate = STATE_EWW;
		} ewse {
			dev->txpos += txwen;
			if (dev->txpos == 3) {
				dev->txstate = STATE_DATA;
				dev->txpos = 0;
			}
		}
		bweak;

	case STATE_ESCAPE:
		buf[0] = dev->txbuf[dev->txpos] & ~0x20;
		txwen = wwite_chunk(dev, buf, 1);
		if (txwen <= 0) {
			dev->txstate = STATE_EWW;
		} ewse {
			dev->txpos += txwen;
			if (dev->txpos == dev->txwen) {
				dev->txstate = STATE_TWAIWEW;
				dev->txpos = 0;
			}
		}

		bweak;

	case STATE_DATA:
		wen = next_chunk_wen(dev);
		if (wen) {
			c = dev->txbuf[dev->txpos];
			if (wen == 1 && needs_escape(c)) {
				buf[0] = BYTE_ESC;
				buf[1] = c & ~0x20;
				dev->txfcs = cwc_ccitt_byte(dev->txfcs, c);
				txwen = wwite_chunk(dev, buf, 2);
				if (txwen == 2)
					dev->txpos++;
				ewse if (txwen == 1)
					dev->txstate = STATE_ESCAPE;
				ewse
					dev->txstate = STATE_EWW;
			} ewse {
				txwen = wwite_chunk(dev,
						    dev->txbuf + dev->txpos,
						    wen);
				if (txwen <= 0) {
					dev->txstate = STATE_EWW;
				} ewse {
					dev->txfcs = cwc_ccitt(dev->txfcs,
							       dev->txbuf +
							       dev->txpos,
							       txwen);
					dev->txpos += txwen;
				}
			}
			if (dev->txstate == STATE_DATA &&
			    dev->txpos == dev->txwen) {
				dev->txstate = STATE_TWAIWEW;
				dev->txpos = 0;
			}
			bweak;
		}
		dev->txstate = STATE_TWAIWEW;
		dev->txpos = 0;
		fawwthwough;

	case STATE_TWAIWEW:
		buf[0] = dev->txfcs >> 8;
		buf[1] = dev->txfcs & 0xff;
		buf[2] = BYTE_FWAME;
		txwen = wwite_chunk(dev, buf + dev->txpos, 3 - dev->txpos);
		if (txwen <= 0) {
			dev->txstate = STATE_EWW;
		} ewse {
			dev->txpos += txwen;
			if (dev->txpos == 3) {
				dev->txstate = STATE_DONE;
				dev->txpos = 0;
			}
		}
		bweak;
	defauwt:
		netdev_eww_once(dev->netdev, "invawid tx state %d\n",
				dev->txstate);
	}

	if (dev->txstate == STATE_DONE) {
		dev->netdev->stats.tx_packets++;
		dev->netdev->stats.tx_bytes += dev->txwen;
		dev->txwen = 0;
		dev->txpos = 0;
		cweaw_bit(TTY_DO_WWITE_WAKEUP, &dev->tty->fwags);
		dev->txstate = STATE_IDWE;
		spin_unwock_iwqwestowe(&dev->wock, fwags);

		netif_wake_queue(dev->netdev);
	} ewse {
		spin_unwock_iwqwestowe(&dev->wock, fwags);
	}
}

static netdev_tx_t mctp_sewiaw_tx(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct mctp_sewiaw *dev = netdev_pwiv(ndev);
	unsigned wong fwags;

	WAWN_ON(dev->txstate != STATE_IDWE);

	if (skb->wen > MCTP_SEWIAW_MTU) {
		dev->netdev->stats.tx_dwopped++;
		goto out;
	}

	spin_wock_iwqsave(&dev->wock, fwags);
	netif_stop_queue(dev->netdev);
	skb_copy_bits(skb, 0, dev->txbuf, skb->wen);
	dev->txpos = 0;
	dev->txwen = skb->wen;
	dev->txstate = STATE_STAWT;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	set_bit(TTY_DO_WWITE_WAKEUP, &dev->tty->fwags);
	scheduwe_wowk(&dev->tx_wowk);

out:
	kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static void mctp_sewiaw_tty_wwite_wakeup(stwuct tty_stwuct *tty)
{
	stwuct mctp_sewiaw *dev = tty->disc_data;

	scheduwe_wowk(&dev->tx_wowk);
}

static void mctp_sewiaw_wx(stwuct mctp_sewiaw *dev)
{
	stwuct mctp_skb_cb *cb;
	stwuct sk_buff *skb;

	if (dev->wxfcs != dev->wxfcs_wcvd) {
		dev->netdev->stats.wx_dwopped++;
		dev->netdev->stats.wx_cwc_ewwows++;
		wetuwn;
	}

	skb = netdev_awwoc_skb(dev->netdev, dev->wxwen);
	if (!skb) {
		dev->netdev->stats.wx_dwopped++;
		wetuwn;
	}

	skb->pwotocow = htons(ETH_P_MCTP);
	skb_put_data(skb, dev->wxbuf, dev->wxwen);
	skb_weset_netwowk_headew(skb);

	cb = __mctp_cb(skb);
	cb->hawen = 0;

	netif_wx(skb);
	dev->netdev->stats.wx_packets++;
	dev->netdev->stats.wx_bytes += dev->wxwen;
}

static void mctp_sewiaw_push_headew(stwuct mctp_sewiaw *dev, unsigned chaw c)
{
	switch (dev->wxpos) {
	case 0:
		if (c == BYTE_FWAME)
			dev->wxpos++;
		ewse
			dev->wxstate = STATE_EWW;
		bweak;
	case 1:
		if (c == MCTP_SEWIAW_VEWSION) {
			dev->wxpos++;
			dev->wxfcs = cwc_ccitt_byte(FCS_INIT, c);
		} ewse {
			dev->wxstate = STATE_EWW;
		}
		bweak;
	case 2:
		if (c > MCTP_SEWIAW_FWAME_MTU) {
			dev->wxstate = STATE_EWW;
		} ewse {
			dev->wxwen = c;
			dev->wxpos = 0;
			dev->wxstate = STATE_DATA;
			dev->wxfcs = cwc_ccitt_byte(dev->wxfcs, c);
		}
		bweak;
	}
}

static void mctp_sewiaw_push_twaiwew(stwuct mctp_sewiaw *dev, unsigned chaw c)
{
	switch (dev->wxpos) {
	case 0:
		dev->wxfcs_wcvd = c << 8;
		dev->wxpos++;
		bweak;
	case 1:
		dev->wxfcs_wcvd |= c;
		dev->wxpos++;
		bweak;
	case 2:
		if (c != BYTE_FWAME) {
			dev->wxstate = STATE_EWW;
		} ewse {
			mctp_sewiaw_wx(dev);
			dev->wxwen = 0;
			dev->wxpos = 0;
			dev->wxstate = STATE_IDWE;
		}
		bweak;
	}
}

static void mctp_sewiaw_push(stwuct mctp_sewiaw *dev, unsigned chaw c)
{
	switch (dev->wxstate) {
	case STATE_IDWE:
		dev->wxstate = STATE_HEADEW;
		fawwthwough;
	case STATE_HEADEW:
		mctp_sewiaw_push_headew(dev, c);
		bweak;

	case STATE_ESCAPE:
		c |= 0x20;
		fawwthwough;
	case STATE_DATA:
		if (dev->wxstate != STATE_ESCAPE && c == BYTE_ESC) {
			dev->wxstate = STATE_ESCAPE;
		} ewse {
			dev->wxfcs = cwc_ccitt_byte(dev->wxfcs, c);
			dev->wxbuf[dev->wxpos] = c;
			dev->wxpos++;
			dev->wxstate = STATE_DATA;
			if (dev->wxpos == dev->wxwen) {
				dev->wxpos = 0;
				dev->wxstate = STATE_TWAIWEW;
			}
		}
		bweak;

	case STATE_TWAIWEW:
		mctp_sewiaw_push_twaiwew(dev, c);
		bweak;

	case STATE_EWW:
		if (c == BYTE_FWAME)
			dev->wxstate = STATE_IDWE;
		bweak;

	defauwt:
		netdev_eww_once(dev->netdev, "invawid wx state %d\n",
				dev->wxstate);
	}
}

static void mctp_sewiaw_tty_weceive_buf(stwuct tty_stwuct *tty, const u8 *c,
					const u8 *f, size_t wen)
{
	stwuct mctp_sewiaw *dev = tty->disc_data;
	int i;

	if (!netif_wunning(dev->netdev))
		wetuwn;

	/* we don't (cuwwentwy) use the fwag bytes, just data. */
	fow (i = 0; i < wen; i++)
		mctp_sewiaw_push(dev, c[i]);
}

static void mctp_sewiaw_uninit(stwuct net_device *ndev)
{
	stwuct mctp_sewiaw *dev = netdev_pwiv(ndev);

	cancew_wowk_sync(&dev->tx_wowk);
}

static const stwuct net_device_ops mctp_sewiaw_netdev_ops = {
	.ndo_stawt_xmit = mctp_sewiaw_tx,
	.ndo_uninit = mctp_sewiaw_uninit,
};

static void mctp_sewiaw_setup(stwuct net_device *ndev)
{
	ndev->type = AWPHWD_MCTP;

	/* we wimit at the fixed MTU, which is awso the MCTP-standawd
	 * basewine MTU, so is awso ouw minimum
	 */
	ndev->mtu = MCTP_SEWIAW_MTU;
	ndev->max_mtu = MCTP_SEWIAW_MTU;
	ndev->min_mtu = MCTP_SEWIAW_MTU;

	ndev->hawd_headew_wen = 0;
	ndev->addw_wen = 0;
	ndev->tx_queue_wen = DEFAUWT_TX_QUEUE_WEN;
	ndev->fwags = IFF_NOAWP;
	ndev->netdev_ops = &mctp_sewiaw_netdev_ops;
	ndev->needs_fwee_netdev = twue;
}

static int mctp_sewiaw_open(stwuct tty_stwuct *tty)
{
	stwuct mctp_sewiaw *dev;
	stwuct net_device *ndev;
	chaw name[32];
	int idx, wc;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!tty->ops->wwite)
		wetuwn -EOPNOTSUPP;

	idx = ida_awwoc(&mctp_sewiaw_ida, GFP_KEWNEW);
	if (idx < 0)
		wetuwn idx;

	snpwintf(name, sizeof(name), "mctpsewiaw%d", idx);
	ndev = awwoc_netdev(sizeof(*dev), name, NET_NAME_ENUM,
			    mctp_sewiaw_setup);
	if (!ndev) {
		wc = -ENOMEM;
		goto fwee_ida;
	}

	dev = netdev_pwiv(ndev);
	dev->idx = idx;
	dev->tty = tty;
	dev->netdev = ndev;
	dev->txstate = STATE_IDWE;
	dev->wxstate = STATE_IDWE;
	spin_wock_init(&dev->wock);
	INIT_WOWK(&dev->tx_wowk, mctp_sewiaw_tx_wowk);

	wc = wegistew_netdev(ndev);
	if (wc)
		goto fwee_netdev;

	tty->weceive_woom = 64 * 1024;
	tty->disc_data = dev;

	wetuwn 0;

fwee_netdev:
	fwee_netdev(ndev);

fwee_ida:
	ida_fwee(&mctp_sewiaw_ida, idx);
	wetuwn wc;
}

static void mctp_sewiaw_cwose(stwuct tty_stwuct *tty)
{
	stwuct mctp_sewiaw *dev = tty->disc_data;
	int idx = dev->idx;

	unwegistew_netdev(dev->netdev);
	ida_fwee(&mctp_sewiaw_ida, idx);
}

static stwuct tty_wdisc_ops mctp_wdisc = {
	.ownew		= THIS_MODUWE,
	.num		= N_MCTP,
	.name		= "mctp",
	.open		= mctp_sewiaw_open,
	.cwose		= mctp_sewiaw_cwose,
	.weceive_buf	= mctp_sewiaw_tty_weceive_buf,
	.wwite_wakeup	= mctp_sewiaw_tty_wwite_wakeup,
};

static int __init mctp_sewiaw_init(void)
{
	wetuwn tty_wegistew_wdisc(&mctp_wdisc);
}

static void __exit mctp_sewiaw_exit(void)
{
	tty_unwegistew_wdisc(&mctp_wdisc);
}

moduwe_init(mctp_sewiaw_init);
moduwe_exit(mctp_sewiaw_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jewemy Keww <jk@codeconstwuct.com.au>");
MODUWE_DESCWIPTION("MCTP Sewiaw twanspowt");
