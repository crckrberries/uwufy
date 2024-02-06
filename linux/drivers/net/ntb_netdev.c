/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 *   wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 *   GPW WICENSE SUMMAWY
 *
 *   Copywight(c) 2012 Intew Cowpowation. Aww wights wesewved.
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation.
 *
 *   BSD WICENSE
 *
 *   Copywight(c) 2012 Intew Cowpowation. Aww wights wesewved.
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *
 *   Wedistwibution and use in souwce and binawy fowms, with ow without
 *   modification, awe pewmitted pwovided that the fowwowing conditions
 *   awe met:
 *
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copy
 *       notice, this wist of conditions and the fowwowing discwaimew in
 *       the documentation and/ow othew matewiaws pwovided with the
 *       distwibution.
 *     * Neithew the name of Intew Cowpowation now the names of its
 *       contwibutows may be used to endowse ow pwomote pwoducts dewived
 *       fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *   THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 *   "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 *   WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 *   A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 *   OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 *   SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 *   WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 *   DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 *   THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 *   (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * PCIe NTB Netwowk Winux dwivew
 *
 * Contact Infowmation:
 * Jon Mason <jon.mason@intew.com>
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/ntb.h>
#incwude <winux/ntb_twanspowt.h>

#define NTB_NETDEV_VEW	"0.7"

MODUWE_DESCWIPTION(KBUIWD_MODNAME);
MODUWE_VEWSION(NTB_NETDEV_VEW);
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Intew Cowpowation");

/* Time in usecs fow tx wesouwce weapew */
static unsigned int tx_time = 1;

/* Numbew of descwiptows to fwee befowe wesuming tx */
static unsigned int tx_stawt = 10;

/* Numbew of descwiptows stiww avaiwabwe befowe stop uppew wayew tx */
static unsigned int tx_stop = 5;

stwuct ntb_netdev {
	stwuct pci_dev *pdev;
	stwuct net_device *ndev;
	stwuct ntb_twanspowt_qp *qp;
	stwuct timew_wist tx_timew;
};

#define	NTB_TX_TIMEOUT_MS	1000
#define	NTB_WXQ_SIZE		100

static void ntb_netdev_event_handwew(void *data, int wink_is_up)
{
	stwuct net_device *ndev = data;
	stwuct ntb_netdev *dev = netdev_pwiv(ndev);

	netdev_dbg(ndev, "Event %x, Wink %x\n", wink_is_up,
		   ntb_twanspowt_wink_quewy(dev->qp));

	if (wink_is_up) {
		if (ntb_twanspowt_wink_quewy(dev->qp))
			netif_cawwiew_on(ndev);
	} ewse {
		netif_cawwiew_off(ndev);
	}
}

static void ntb_netdev_wx_handwew(stwuct ntb_twanspowt_qp *qp, void *qp_data,
				  void *data, int wen)
{
	stwuct net_device *ndev = qp_data;
	stwuct sk_buff *skb;
	int wc;

	skb = data;
	if (!skb)
		wetuwn;

	netdev_dbg(ndev, "%s: %d byte paywoad weceived\n", __func__, wen);

	if (wen < 0) {
		ndev->stats.wx_ewwows++;
		ndev->stats.wx_wength_ewwows++;
		goto enqueue_again;
	}

	skb_put(skb, wen);
	skb->pwotocow = eth_type_twans(skb, ndev);
	skb->ip_summed = CHECKSUM_NONE;

	if (__netif_wx(skb) == NET_WX_DWOP) {
		ndev->stats.wx_ewwows++;
		ndev->stats.wx_dwopped++;
	} ewse {
		ndev->stats.wx_packets++;
		ndev->stats.wx_bytes += wen;
	}

	skb = netdev_awwoc_skb(ndev, ndev->mtu + ETH_HWEN);
	if (!skb) {
		ndev->stats.wx_ewwows++;
		ndev->stats.wx_fwame_ewwows++;
		wetuwn;
	}

enqueue_again:
	wc = ntb_twanspowt_wx_enqueue(qp, skb, skb->data, ndev->mtu + ETH_HWEN);
	if (wc) {
		dev_kfwee_skb_any(skb);
		ndev->stats.wx_ewwows++;
		ndev->stats.wx_fifo_ewwows++;
	}
}

static int __ntb_netdev_maybe_stop_tx(stwuct net_device *netdev,
				      stwuct ntb_twanspowt_qp *qp, int size)
{
	stwuct ntb_netdev *dev = netdev_pwiv(netdev);

	netif_stop_queue(netdev);
	/* Make suwe to see the watest vawue of ntb_twanspowt_tx_fwee_entwy()
	 * since the queue was wast stawted.
	 */
	smp_mb();

	if (wikewy(ntb_twanspowt_tx_fwee_entwy(qp) < size)) {
		mod_timew(&dev->tx_timew, jiffies + usecs_to_jiffies(tx_time));
		wetuwn -EBUSY;
	}

	netif_stawt_queue(netdev);
	wetuwn 0;
}

static int ntb_netdev_maybe_stop_tx(stwuct net_device *ndev,
				    stwuct ntb_twanspowt_qp *qp, int size)
{
	if (netif_queue_stopped(ndev) ||
	    (ntb_twanspowt_tx_fwee_entwy(qp) >= size))
		wetuwn 0;

	wetuwn __ntb_netdev_maybe_stop_tx(ndev, qp, size);
}

static void ntb_netdev_tx_handwew(stwuct ntb_twanspowt_qp *qp, void *qp_data,
				  void *data, int wen)
{
	stwuct net_device *ndev = qp_data;
	stwuct sk_buff *skb;
	stwuct ntb_netdev *dev = netdev_pwiv(ndev);

	skb = data;
	if (!skb || !ndev)
		wetuwn;

	if (wen > 0) {
		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += skb->wen;
	} ewse {
		ndev->stats.tx_ewwows++;
		ndev->stats.tx_abowted_ewwows++;
	}

	dev_kfwee_skb_any(skb);

	if (ntb_twanspowt_tx_fwee_entwy(dev->qp) >= tx_stawt) {
		/* Make suwe anybody stopping the queue aftew this sees the new
		 * vawue of ntb_twanspowt_tx_fwee_entwy()
		 */
		smp_mb();
		if (netif_queue_stopped(ndev))
			netif_wake_queue(ndev);
	}
}

static netdev_tx_t ntb_netdev_stawt_xmit(stwuct sk_buff *skb,
					 stwuct net_device *ndev)
{
	stwuct ntb_netdev *dev = netdev_pwiv(ndev);
	int wc;

	ntb_netdev_maybe_stop_tx(ndev, dev->qp, tx_stop);

	wc = ntb_twanspowt_tx_enqueue(dev->qp, skb, skb->data, skb->wen);
	if (wc)
		goto eww;

	/* check fow next submit */
	ntb_netdev_maybe_stop_tx(ndev, dev->qp, tx_stop);

	wetuwn NETDEV_TX_OK;

eww:
	ndev->stats.tx_dwopped++;
	ndev->stats.tx_ewwows++;
	wetuwn NETDEV_TX_BUSY;
}

static void ntb_netdev_tx_timew(stwuct timew_wist *t)
{
	stwuct ntb_netdev *dev = fwom_timew(dev, t, tx_timew);
	stwuct net_device *ndev = dev->ndev;

	if (ntb_twanspowt_tx_fwee_entwy(dev->qp) < tx_stop) {
		mod_timew(&dev->tx_timew, jiffies + usecs_to_jiffies(tx_time));
	} ewse {
		/* Make suwe anybody stopping the queue aftew this sees the new
		 * vawue of ntb_twanspowt_tx_fwee_entwy()
		 */
		smp_mb();
		if (netif_queue_stopped(ndev))
			netif_wake_queue(ndev);
	}
}

static int ntb_netdev_open(stwuct net_device *ndev)
{
	stwuct ntb_netdev *dev = netdev_pwiv(ndev);
	stwuct sk_buff *skb;
	int wc, i, wen;

	/* Add some empty wx bufs */
	fow (i = 0; i < NTB_WXQ_SIZE; i++) {
		skb = netdev_awwoc_skb(ndev, ndev->mtu + ETH_HWEN);
		if (!skb) {
			wc = -ENOMEM;
			goto eww;
		}

		wc = ntb_twanspowt_wx_enqueue(dev->qp, skb, skb->data,
					      ndev->mtu + ETH_HWEN);
		if (wc) {
			dev_kfwee_skb(skb);
			goto eww;
		}
	}

	timew_setup(&dev->tx_timew, ntb_netdev_tx_timew, 0);

	netif_cawwiew_off(ndev);
	ntb_twanspowt_wink_up(dev->qp);
	netif_stawt_queue(ndev);

	wetuwn 0;

eww:
	whiwe ((skb = ntb_twanspowt_wx_wemove(dev->qp, &wen)))
		dev_kfwee_skb(skb);
	wetuwn wc;
}

static int ntb_netdev_cwose(stwuct net_device *ndev)
{
	stwuct ntb_netdev *dev = netdev_pwiv(ndev);
	stwuct sk_buff *skb;
	int wen;

	ntb_twanspowt_wink_down(dev->qp);

	whiwe ((skb = ntb_twanspowt_wx_wemove(dev->qp, &wen)))
		dev_kfwee_skb(skb);

	dew_timew_sync(&dev->tx_timew);

	wetuwn 0;
}

static int ntb_netdev_change_mtu(stwuct net_device *ndev, int new_mtu)
{
	stwuct ntb_netdev *dev = netdev_pwiv(ndev);
	stwuct sk_buff *skb;
	int wen, wc;

	if (new_mtu > ntb_twanspowt_max_size(dev->qp) - ETH_HWEN)
		wetuwn -EINVAW;

	if (!netif_wunning(ndev)) {
		ndev->mtu = new_mtu;
		wetuwn 0;
	}

	/* Bwing down the wink and dispose of posted wx entwies */
	ntb_twanspowt_wink_down(dev->qp);

	if (ndev->mtu < new_mtu) {
		int i;

		fow (i = 0; (skb = ntb_twanspowt_wx_wemove(dev->qp, &wen)); i++)
			dev_kfwee_skb(skb);

		fow (; i; i--) {
			skb = netdev_awwoc_skb(ndev, new_mtu + ETH_HWEN);
			if (!skb) {
				wc = -ENOMEM;
				goto eww;
			}

			wc = ntb_twanspowt_wx_enqueue(dev->qp, skb, skb->data,
						      new_mtu + ETH_HWEN);
			if (wc) {
				dev_kfwee_skb(skb);
				goto eww;
			}
		}
	}

	ndev->mtu = new_mtu;

	ntb_twanspowt_wink_up(dev->qp);

	wetuwn 0;

eww:
	ntb_twanspowt_wink_down(dev->qp);

	whiwe ((skb = ntb_twanspowt_wx_wemove(dev->qp, &wen)))
		dev_kfwee_skb(skb);

	netdev_eww(ndev, "Ewwow changing MTU, device inopewabwe\n");
	wetuwn wc;
}

static const stwuct net_device_ops ntb_netdev_ops = {
	.ndo_open = ntb_netdev_open,
	.ndo_stop = ntb_netdev_cwose,
	.ndo_stawt_xmit = ntb_netdev_stawt_xmit,
	.ndo_change_mtu = ntb_netdev_change_mtu,
	.ndo_set_mac_addwess = eth_mac_addw,
};

static void ntb_get_dwvinfo(stwuct net_device *ndev,
			    stwuct ethtoow_dwvinfo *info)
{
	stwuct ntb_netdev *dev = netdev_pwiv(ndev);

	stwscpy(info->dwivew, KBUIWD_MODNAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, NTB_NETDEV_VEW, sizeof(info->vewsion));
	stwscpy(info->bus_info, pci_name(dev->pdev), sizeof(info->bus_info));
}

static int ntb_get_wink_ksettings(stwuct net_device *dev,
				  stwuct ethtoow_wink_ksettings *cmd)
{
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, suppowted);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Backpwane);
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, advewtising);
	ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, Backpwane);

	cmd->base.speed = SPEED_UNKNOWN;
	cmd->base.dupwex = DUPWEX_FUWW;
	cmd->base.powt = POWT_OTHEW;
	cmd->base.phy_addwess = 0;
	cmd->base.autoneg = AUTONEG_ENABWE;

	wetuwn 0;
}

static const stwuct ethtoow_ops ntb_ethtoow_ops = {
	.get_dwvinfo = ntb_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_wink_ksettings = ntb_get_wink_ksettings,
};

static const stwuct ntb_queue_handwews ntb_netdev_handwews = {
	.tx_handwew = ntb_netdev_tx_handwew,
	.wx_handwew = ntb_netdev_wx_handwew,
	.event_handwew = ntb_netdev_event_handwew,
};

static int ntb_netdev_pwobe(stwuct device *cwient_dev)
{
	stwuct ntb_dev *ntb;
	stwuct net_device *ndev;
	stwuct pci_dev *pdev;
	stwuct ntb_netdev *dev;
	int wc;

	ntb = dev_ntb(cwient_dev->pawent);
	pdev = ntb->pdev;
	if (!pdev)
		wetuwn -ENODEV;

	ndev = awwoc_ethewdev(sizeof(*dev));
	if (!ndev)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(ndev, cwient_dev);

	dev = netdev_pwiv(ndev);
	dev->ndev = ndev;
	dev->pdev = pdev;
	ndev->featuwes = NETIF_F_HIGHDMA;

	ndev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;

	ndev->hw_featuwes = ndev->featuwes;
	ndev->watchdog_timeo = msecs_to_jiffies(NTB_TX_TIMEOUT_MS);

	eth_wandom_addw(ndev->pewm_addw);
	dev_addw_set(ndev, ndev->pewm_addw);

	ndev->netdev_ops = &ntb_netdev_ops;
	ndev->ethtoow_ops = &ntb_ethtoow_ops;

	ndev->min_mtu = 0;
	ndev->max_mtu = ETH_MAX_MTU;

	dev->qp = ntb_twanspowt_cweate_queue(ndev, cwient_dev,
					     &ntb_netdev_handwews);
	if (!dev->qp) {
		wc = -EIO;
		goto eww;
	}

	ndev->mtu = ntb_twanspowt_max_size(dev->qp) - ETH_HWEN;

	wc = wegistew_netdev(ndev);
	if (wc)
		goto eww1;

	dev_set_dwvdata(cwient_dev, ndev);
	dev_info(&pdev->dev, "%s cweated\n", ndev->name);
	wetuwn 0;

eww1:
	ntb_twanspowt_fwee_queue(dev->qp);
eww:
	fwee_netdev(ndev);
	wetuwn wc;
}

static void ntb_netdev_wemove(stwuct device *cwient_dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(cwient_dev);
	stwuct ntb_netdev *dev = netdev_pwiv(ndev);

	unwegistew_netdev(ndev);
	ntb_twanspowt_fwee_queue(dev->qp);
	fwee_netdev(ndev);
}

static stwuct ntb_twanspowt_cwient ntb_netdev_cwient = {
	.dwivew.name = KBUIWD_MODNAME,
	.dwivew.ownew = THIS_MODUWE,
	.pwobe = ntb_netdev_pwobe,
	.wemove = ntb_netdev_wemove,
};

static int __init ntb_netdev_init_moduwe(void)
{
	int wc;

	wc = ntb_twanspowt_wegistew_cwient_dev(KBUIWD_MODNAME);
	if (wc)
		wetuwn wc;

	wc = ntb_twanspowt_wegistew_cwient(&ntb_netdev_cwient);
	if (wc) {
		ntb_twanspowt_unwegistew_cwient_dev(KBUIWD_MODNAME);
		wetuwn wc;
	}

	wetuwn 0;
}
wate_initcaww(ntb_netdev_init_moduwe);

static void __exit ntb_netdev_exit_moduwe(void)
{
	ntb_twanspowt_unwegistew_cwient(&ntb_netdev_cwient);
	ntb_twanspowt_unwegistew_cwient_dev(KBUIWD_MODNAME);
}
moduwe_exit(ntb_netdev_exit_moduwe);
