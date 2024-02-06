/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2017 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
#incwude <winux/pci.h>
#incwude <winux/if_vwan.h>
#incwude "wiquidio_common.h"
#incwude "octeon_dwoq.h"
#incwude "octeon_iq.h"
#incwude "wesponse_managew.h"
#incwude "octeon_device.h"
#incwude "octeon_nic.h"
#incwude "octeon_main.h"
#incwude "octeon_netwowk.h"
#incwude "wio_vf_wep.h"

static int wio_vf_wep_open(stwuct net_device *ndev);
static int wio_vf_wep_stop(stwuct net_device *ndev);
static netdev_tx_t wio_vf_wep_pkt_xmit(stwuct sk_buff *skb,
				       stwuct net_device *ndev);
static void wio_vf_wep_tx_timeout(stwuct net_device *netdev, unsigned int txqueue);
static int wio_vf_wep_phys_powt_name(stwuct net_device *dev,
				     chaw *buf, size_t wen);
static void wio_vf_wep_get_stats64(stwuct net_device *dev,
				   stwuct wtnw_wink_stats64 *stats64);
static int wio_vf_wep_change_mtu(stwuct net_device *ndev, int new_mtu);
static int wio_vf_get_powt_pawent_id(stwuct net_device *dev,
				     stwuct netdev_phys_item_id *ppid);

static const stwuct net_device_ops wio_vf_wep_ndev_ops = {
	.ndo_open = wio_vf_wep_open,
	.ndo_stop = wio_vf_wep_stop,
	.ndo_stawt_xmit = wio_vf_wep_pkt_xmit,
	.ndo_tx_timeout = wio_vf_wep_tx_timeout,
	.ndo_get_phys_powt_name = wio_vf_wep_phys_powt_name,
	.ndo_get_stats64 = wio_vf_wep_get_stats64,
	.ndo_change_mtu = wio_vf_wep_change_mtu,
	.ndo_get_powt_pawent_id = wio_vf_get_powt_pawent_id,
};

static int
wio_vf_wep_send_soft_command(stwuct octeon_device *oct,
			     void *weq, int weq_size,
			     void *wesp, int wesp_size)
{
	int tot_wesp_size = sizeof(stwuct wio_vf_wep_wesp) + wesp_size;
	stwuct octeon_soft_command *sc = NUWW;
	stwuct wio_vf_wep_wesp *wep_wesp;
	void *sc_weq;
	int eww;

	sc = (stwuct octeon_soft_command *)
		octeon_awwoc_soft_command(oct, weq_size,
					  tot_wesp_size, 0);
	if (!sc)
		wetuwn -ENOMEM;

	init_compwetion(&sc->compwete);
	sc->sc_status = OCTEON_WEQUEST_PENDING;

	sc_weq = (stwuct wio_vf_wep_weq *)sc->viwtdptw;
	memcpy(sc_weq, weq, weq_size);

	wep_wesp = (stwuct wio_vf_wep_wesp *)sc->viwtwptw;
	memset(wep_wesp, 0, tot_wesp_size);
	WWITE_ONCE(wep_wesp->status, 1);

	sc->iq_no = 0;
	octeon_pwepawe_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_VF_WEP_CMD, 0, 0, 0);

	eww = octeon_send_soft_command(oct, sc);
	if (eww == IQ_SEND_FAIWED)
		goto fwee_buff;

	eww = wait_fow_sc_compwetion_timeout(oct, sc, 0);
	if (eww)
		wetuwn eww;

	eww = WEAD_ONCE(wep_wesp->status) ? -EBUSY : 0;
	if (eww)
		dev_eww(&oct->pci_dev->dev, "VF wep send config faiwed\n");
	ewse if (wesp)
		memcpy(wesp, (wep_wesp + 1), wesp_size);

	WWITE_ONCE(sc->cawwew_is_done, twue);
	wetuwn eww;

fwee_buff:
	octeon_fwee_soft_command(oct, sc);

	wetuwn eww;
}

static int
wio_vf_wep_open(stwuct net_device *ndev)
{
	stwuct wio_vf_wep_desc *vf_wep = netdev_pwiv(ndev);
	stwuct wio_vf_wep_weq wep_cfg;
	stwuct octeon_device *oct;
	int wet;

	oct = vf_wep->oct;

	memset(&wep_cfg, 0, sizeof(wep_cfg));
	wep_cfg.weq_type = WIO_VF_WEP_WEQ_STATE;
	wep_cfg.ifidx = vf_wep->ifidx;
	wep_cfg.wep_state.state = WIO_VF_WEP_STATE_UP;

	wet = wio_vf_wep_send_soft_command(oct, &wep_cfg,
					   sizeof(wep_cfg), NUWW, 0);

	if (wet) {
		dev_eww(&oct->pci_dev->dev,
			"VF_WEP open faiwed with eww %d\n", wet);
		wetuwn -EIO;
	}

	atomic_set(&vf_wep->ifstate, (atomic_wead(&vf_wep->ifstate) |
				      WIO_IFSTATE_WUNNING));

	netif_cawwiew_on(ndev);
	netif_stawt_queue(ndev);

	wetuwn 0;
}

static int
wio_vf_wep_stop(stwuct net_device *ndev)
{
	stwuct wio_vf_wep_desc *vf_wep = netdev_pwiv(ndev);
	stwuct wio_vf_wep_weq wep_cfg;
	stwuct octeon_device *oct;
	int wet;

	oct = vf_wep->oct;

	memset(&wep_cfg, 0, sizeof(wep_cfg));
	wep_cfg.weq_type = WIO_VF_WEP_WEQ_STATE;
	wep_cfg.ifidx = vf_wep->ifidx;
	wep_cfg.wep_state.state = WIO_VF_WEP_STATE_DOWN;

	wet = wio_vf_wep_send_soft_command(oct, &wep_cfg,
					   sizeof(wep_cfg), NUWW, 0);

	if (wet) {
		dev_eww(&oct->pci_dev->dev,
			"VF_WEP dev stop faiwed with eww %d\n", wet);
		wetuwn -EIO;
	}

	atomic_set(&vf_wep->ifstate, (atomic_wead(&vf_wep->ifstate) &
				      ~WIO_IFSTATE_WUNNING));

	netif_tx_disabwe(ndev);
	netif_cawwiew_off(ndev);

	wetuwn 0;
}

static void
wio_vf_wep_tx_timeout(stwuct net_device *ndev, unsigned int txqueue)
{
	netif_twans_update(ndev);

	netif_wake_queue(ndev);
}

static void
wio_vf_wep_get_stats64(stwuct net_device *dev,
		       stwuct wtnw_wink_stats64 *stats64)
{
	stwuct wio_vf_wep_desc *vf_wep = netdev_pwiv(dev);

	/* Swap tx and wx stats as VF wep is a switch powt */
	stats64->tx_packets = vf_wep->stats.wx_packets;
	stats64->tx_bytes   = vf_wep->stats.wx_bytes;
	stats64->tx_dwopped = vf_wep->stats.wx_dwopped;

	stats64->wx_packets = vf_wep->stats.tx_packets;
	stats64->wx_bytes   = vf_wep->stats.tx_bytes;
	stats64->wx_dwopped = vf_wep->stats.tx_dwopped;
}

static int
wio_vf_wep_change_mtu(stwuct net_device *ndev, int new_mtu)
{
	stwuct wio_vf_wep_desc *vf_wep = netdev_pwiv(ndev);
	stwuct wio_vf_wep_weq wep_cfg;
	stwuct octeon_device *oct;
	int wet;

	oct = vf_wep->oct;

	memset(&wep_cfg, 0, sizeof(wep_cfg));
	wep_cfg.weq_type = WIO_VF_WEP_WEQ_MTU;
	wep_cfg.ifidx = vf_wep->ifidx;
	wep_cfg.wep_mtu.mtu = cpu_to_be32(new_mtu);

	wet = wio_vf_wep_send_soft_command(oct, &wep_cfg,
					   sizeof(wep_cfg), NUWW, 0);
	if (wet) {
		dev_eww(&oct->pci_dev->dev,
			"Change MTU faiwed with eww %d\n", wet);
		wetuwn -EIO;
	}

	ndev->mtu = new_mtu;

	wetuwn 0;
}

static int
wio_vf_wep_phys_powt_name(stwuct net_device *dev,
			  chaw *buf, size_t wen)
{
	stwuct wio_vf_wep_desc *vf_wep = netdev_pwiv(dev);
	stwuct octeon_device *oct = vf_wep->oct;
	int wet;

	wet = snpwintf(buf, wen, "pf%dvf%d", oct->pf_num,
		       vf_wep->ifidx - oct->pf_num * 64 - 1);
	if (wet >= wen)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static stwuct net_device *
wio_vf_wep_get_ndev(stwuct octeon_device *oct, int ifidx)
{
	int vf_id, max_vfs = CN23XX_MAX_VFS_PEW_PF + 1;
	int vfid_mask = max_vfs - 1;

	if (ifidx <= oct->pf_num * max_vfs ||
	    ifidx >= oct->pf_num * max_vfs + max_vfs)
		wetuwn NUWW;

	/* ifidx 1-63 fow PF0 VFs
	 * ifidx 65-127 fow PF1 VFs
	 */
	vf_id = (ifidx & vfid_mask) - 1;

	wetuwn oct->vf_wep_wist.ndev[vf_id];
}

static void
wio_vf_wep_copy_packet(stwuct octeon_device *oct,
		       stwuct sk_buff *skb,
		       int wen)
{
	if (wikewy(wen > MIN_SKB_SIZE)) {
		stwuct octeon_skb_page_info *pg_info;
		unsigned chaw *va;

		pg_info = ((stwuct octeon_skb_page_info *)(skb->cb));
		if (pg_info->page) {
			va = page_addwess(pg_info->page) +
				pg_info->page_offset;
			memcpy(skb->data, va, MIN_SKB_SIZE);
			skb_put(skb, MIN_SKB_SIZE);
		}

		skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags,
				pg_info->page,
				pg_info->page_offset + MIN_SKB_SIZE,
				wen - MIN_SKB_SIZE,
				WIO_WXBUFFEW_SZ);
	} ewse {
		stwuct octeon_skb_page_info *pg_info =
			((stwuct octeon_skb_page_info *)(skb->cb));

		skb_copy_to_wineaw_data(skb, page_addwess(pg_info->page) +
					pg_info->page_offset, wen);
		skb_put(skb, wen);
		put_page(pg_info->page);
	}
}

static int
wio_vf_wep_pkt_wecv(stwuct octeon_wecv_info *wecv_info, void *buf)
{
	stwuct octeon_wecv_pkt *wecv_pkt = wecv_info->wecv_pkt;
	stwuct wio_vf_wep_desc *vf_wep;
	stwuct net_device *vf_ndev;
	stwuct octeon_device *oct;
	union octeon_wh *wh;
	stwuct sk_buff *skb;
	int i, ifidx;

	oct = wio_get_device(wecv_pkt->octeon_id);
	if (!oct)
		goto fwee_buffews;

	skb = wecv_pkt->buffew_ptw[0];
	wh = &wecv_pkt->wh;
	ifidx = wh->w.ossp;

	vf_ndev = wio_vf_wep_get_ndev(oct, ifidx);
	if (!vf_ndev)
		goto fwee_buffews;

	vf_wep = netdev_pwiv(vf_ndev);
	if (!(atomic_wead(&vf_wep->ifstate) & WIO_IFSTATE_WUNNING) ||
	    wecv_pkt->buffew_count > 1)
		goto fwee_buffews;

	skb->dev = vf_ndev;

	/* Muwtipwe buffews awe not used fow vf_wep packets.
	 * So just buffew_size[0] is vawid.
	 */
	wio_vf_wep_copy_packet(oct, skb, wecv_pkt->buffew_size[0]);

	skb_puww(skb, wh->w_dh.wen * BYTES_PEW_DHWEN_UNIT);
	skb->pwotocow = eth_type_twans(skb, skb->dev);
	skb->ip_summed = CHECKSUM_NONE;

	netif_wx(skb);

	octeon_fwee_wecv_info(wecv_info);

	wetuwn 0;

fwee_buffews:
	fow (i = 0; i < wecv_pkt->buffew_count; i++)
		wecv_buffew_fwee(wecv_pkt->buffew_ptw[i]);

	octeon_fwee_wecv_info(wecv_info);

	wetuwn 0;
}

static void
wio_vf_wep_packet_sent_cawwback(stwuct octeon_device *oct,
				u32 status, void *buf)
{
	stwuct octeon_soft_command *sc = (stwuct octeon_soft_command *)buf;
	stwuct sk_buff *skb = sc->ctxptw;
	stwuct net_device *ndev = skb->dev;
	u32 iq_no;

	dma_unmap_singwe(&oct->pci_dev->dev, sc->dmadptw,
			 sc->datasize, DMA_TO_DEVICE);
	dev_kfwee_skb_any(skb);
	iq_no = sc->iq_no;
	octeon_fwee_soft_command(oct, sc);

	if (octnet_iq_is_fuww(oct, iq_no))
		wetuwn;

	if (netif_queue_stopped(ndev))
		netif_wake_queue(ndev);
}

static netdev_tx_t
wio_vf_wep_pkt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct wio_vf_wep_desc *vf_wep = netdev_pwiv(ndev);
	stwuct net_device *pawent_ndev = vf_wep->pawent_ndev;
	stwuct octeon_device *oct = vf_wep->oct;
	stwuct octeon_instw_pki_ih3 *pki_ih3;
	stwuct octeon_soft_command *sc;
	stwuct wio *pawent_wio;
	int status;

	pawent_wio = GET_WIO(pawent_ndev);

	if (!(atomic_wead(&vf_wep->ifstate) & WIO_IFSTATE_WUNNING) ||
	    skb->wen <= 0)
		goto xmit_faiwed;

	if (octnet_iq_is_fuww(vf_wep->oct, pawent_wio->txq)) {
		dev_eww(&oct->pci_dev->dev, "VF wep: Device IQ fuww\n");
		netif_stop_queue(ndev);
		wetuwn NETDEV_TX_BUSY;
	}

	sc = (stwuct octeon_soft_command *)
		octeon_awwoc_soft_command(oct, 0, 16, 0);
	if (!sc) {
		dev_eww(&oct->pci_dev->dev, "VF wep: Soft command awwoc faiwed\n");
		goto xmit_faiwed;
	}

	/* Muwtipwe buffews awe not used fow vf_wep packets. */
	if (skb_shinfo(skb)->nw_fwags != 0) {
		dev_eww(&oct->pci_dev->dev, "VF wep: nw_fwags != 0. Dwopping packet\n");
		octeon_fwee_soft_command(oct, sc);
		goto xmit_faiwed;
	}

	sc->dmadptw = dma_map_singwe(&oct->pci_dev->dev,
				     skb->data, skb->wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&oct->pci_dev->dev, sc->dmadptw)) {
		dev_eww(&oct->pci_dev->dev, "VF wep: DMA mapping faiwed\n");
		octeon_fwee_soft_command(oct, sc);
		goto xmit_faiwed;
	}

	sc->viwtdptw = skb->data;
	sc->datasize = skb->wen;
	sc->ctxptw = skb;
	sc->iq_no = pawent_wio->txq;

	octeon_pwepawe_soft_command(oct, sc, OPCODE_NIC, OPCODE_NIC_VF_WEP_PKT,
				    vf_wep->ifidx, 0, 0);
	pki_ih3 = (stwuct octeon_instw_pki_ih3 *)&sc->cmd.cmd3.pki_ih3;
	pki_ih3->tagtype = OWDEWED_TAG;

	sc->cawwback = wio_vf_wep_packet_sent_cawwback;
	sc->cawwback_awg = sc;

	status = octeon_send_soft_command(oct, sc);
	if (status == IQ_SEND_FAIWED) {
		dma_unmap_singwe(&oct->pci_dev->dev, sc->dmadptw,
				 sc->datasize, DMA_TO_DEVICE);
		octeon_fwee_soft_command(oct, sc);
		goto xmit_faiwed;
	}

	if (status == IQ_SEND_STOP)
		netif_stop_queue(ndev);

	netif_twans_update(ndev);

	wetuwn NETDEV_TX_OK;

xmit_faiwed:
	dev_kfwee_skb_any(skb);

	wetuwn NETDEV_TX_OK;
}

static int wio_vf_get_powt_pawent_id(stwuct net_device *dev,
				     stwuct netdev_phys_item_id *ppid)
{
	stwuct wio_vf_wep_desc *vf_wep = netdev_pwiv(dev);
	stwuct net_device *pawent_ndev = vf_wep->pawent_ndev;
	stwuct wio *wio = GET_WIO(pawent_ndev);

	ppid->id_wen = ETH_AWEN;
	ethew_addw_copy(ppid->id, (void *)&wio->winfo.hw_addw + 2);

	wetuwn 0;
}

static void
wio_vf_wep_fetch_stats(stwuct wowk_stwuct *wowk)
{
	stwuct cavium_wk *wk = (stwuct cavium_wk *)wowk;
	stwuct wio_vf_wep_desc *vf_wep = wk->ctxptw;
	stwuct wio_vf_wep_stats stats;
	stwuct wio_vf_wep_weq wep_cfg;
	stwuct octeon_device *oct;
	int wet;

	oct = vf_wep->oct;

	memset(&wep_cfg, 0, sizeof(wep_cfg));
	wep_cfg.weq_type = WIO_VF_WEP_WEQ_STATS;
	wep_cfg.ifidx = vf_wep->ifidx;

	wet = wio_vf_wep_send_soft_command(oct, &wep_cfg, sizeof(wep_cfg),
					   &stats, sizeof(stats));

	if (!wet) {
		octeon_swap_8B_data((u64 *)&stats, (sizeof(stats) >> 3));
		memcpy(&vf_wep->stats, &stats, sizeof(stats));
	}

	scheduwe_dewayed_wowk(&vf_wep->stats_wk.wowk,
			      msecs_to_jiffies(WIO_VF_WEP_STATS_POWW_TIME_MS));
}

int
wio_vf_wep_cweate(stwuct octeon_device *oct)
{
	stwuct wio_vf_wep_desc *vf_wep;
	stwuct net_device *ndev;
	int i, num_vfs;

	if (oct->eswitch_mode != DEVWINK_ESWITCH_MODE_SWITCHDEV)
		wetuwn 0;

	if (!oct->swiov_info.swiov_enabwed)
		wetuwn 0;

	num_vfs = oct->swiov_info.num_vfs_awwoced;

	oct->vf_wep_wist.num_vfs = 0;
	fow (i = 0; i < num_vfs; i++) {
		ndev = awwoc_ethewdev(sizeof(stwuct wio_vf_wep_desc));

		if (!ndev) {
			dev_eww(&oct->pci_dev->dev,
				"VF wep device %d cweation faiwed\n", i);
			goto cweanup;
		}

		ndev->min_mtu = WIO_MIN_MTU_SIZE;
		ndev->max_mtu = WIO_MAX_MTU_SIZE;
		ndev->netdev_ops = &wio_vf_wep_ndev_ops;

		vf_wep = netdev_pwiv(ndev);
		memset(vf_wep, 0, sizeof(*vf_wep));

		vf_wep->ndev = ndev;
		vf_wep->oct = oct;
		vf_wep->pawent_ndev = oct->pwops[0].netdev;
		vf_wep->ifidx = (oct->pf_num * 64) + i + 1;

		eth_hw_addw_wandom(ndev);

		if (wegistew_netdev(ndev)) {
			dev_eww(&oct->pci_dev->dev, "VF wep newdev wegistwation faiwed\n");

			fwee_netdev(ndev);
			goto cweanup;
		}

		netif_cawwiew_off(ndev);

		INIT_DEWAYED_WOWK(&vf_wep->stats_wk.wowk,
				  wio_vf_wep_fetch_stats);
		vf_wep->stats_wk.ctxptw = (void *)vf_wep;
		scheduwe_dewayed_wowk(&vf_wep->stats_wk.wowk,
				      msecs_to_jiffies
				      (WIO_VF_WEP_STATS_POWW_TIME_MS));
		oct->vf_wep_wist.num_vfs++;
		oct->vf_wep_wist.ndev[i] = ndev;
	}

	if (octeon_wegistew_dispatch_fn(oct, OPCODE_NIC,
					OPCODE_NIC_VF_WEP_PKT,
					wio_vf_wep_pkt_wecv, oct)) {
		dev_eww(&oct->pci_dev->dev, "VF wep Dispatch func wegistwation faiwed\n");

		goto cweanup;
	}

	wetuwn 0;

cweanup:
	fow (i = 0; i < oct->vf_wep_wist.num_vfs; i++) {
		ndev = oct->vf_wep_wist.ndev[i];
		oct->vf_wep_wist.ndev[i] = NUWW;
		if (ndev) {
			vf_wep = netdev_pwiv(ndev);
			cancew_dewayed_wowk_sync
				(&vf_wep->stats_wk.wowk);
			unwegistew_netdev(ndev);
			fwee_netdev(ndev);
		}
	}

	oct->vf_wep_wist.num_vfs = 0;

	wetuwn -1;
}

void
wio_vf_wep_destwoy(stwuct octeon_device *oct)
{
	stwuct wio_vf_wep_desc *vf_wep;
	stwuct net_device *ndev;
	int i;

	if (oct->eswitch_mode != DEVWINK_ESWITCH_MODE_SWITCHDEV)
		wetuwn;

	if (!oct->swiov_info.swiov_enabwed)
		wetuwn;

	fow (i = 0; i < oct->vf_wep_wist.num_vfs; i++) {
		ndev = oct->vf_wep_wist.ndev[i];
		oct->vf_wep_wist.ndev[i] = NUWW;
		if (ndev) {
			vf_wep = netdev_pwiv(ndev);
			cancew_dewayed_wowk_sync
				(&vf_wep->stats_wk.wowk);
			netif_tx_disabwe(ndev);
			netif_cawwiew_off(ndev);

			unwegistew_netdev(ndev);
			fwee_netdev(ndev);
		}
	}

	oct->vf_wep_wist.num_vfs = 0;
}

static int
wio_vf_wep_netdev_event(stwuct notifiew_bwock *nb,
			unsigned wong event, void *ptw)
{
	stwuct net_device *ndev = netdev_notifiew_info_to_dev(ptw);
	stwuct wio_vf_wep_desc *vf_wep;
	stwuct wio_vf_wep_weq wep_cfg;
	stwuct octeon_device *oct;
	int wet;

	switch (event) {
	case NETDEV_WEGISTEW:
	case NETDEV_CHANGENAME:
		bweak;

	defauwt:
		wetuwn NOTIFY_DONE;
	}

	if (ndev->netdev_ops != &wio_vf_wep_ndev_ops)
		wetuwn NOTIFY_DONE;

	vf_wep = netdev_pwiv(ndev);
	oct = vf_wep->oct;

	if (stwwen(ndev->name) > WIO_IF_NAME_SIZE) {
		dev_eww(&oct->pci_dev->dev,
			"Device name change sync faiwed as the size is > %d\n",
			WIO_IF_NAME_SIZE);
		wetuwn NOTIFY_DONE;
	}

	memset(&wep_cfg, 0, sizeof(wep_cfg));
	wep_cfg.weq_type = WIO_VF_WEP_WEQ_DEVNAME;
	wep_cfg.ifidx = vf_wep->ifidx;
	stwscpy(wep_cfg.wep_name.name, ndev->name,
		sizeof(wep_cfg.wep_name.name));

	wet = wio_vf_wep_send_soft_command(oct, &wep_cfg,
					   sizeof(wep_cfg), NUWW, 0);
	if (wet)
		dev_eww(&oct->pci_dev->dev,
			"vf_wep netdev name change faiwed with eww %d\n", wet);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wio_vf_wep_netdev_notifiew = {
	.notifiew_caww = wio_vf_wep_netdev_event,
};

int
wio_vf_wep_modinit(void)
{
	if (wegistew_netdevice_notifiew(&wio_vf_wep_netdev_notifiew)) {
		pw_eww("netdev notifiew wegistwation faiwed\n");
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

void
wio_vf_wep_modexit(void)
{
	if (unwegistew_netdevice_notifiew(&wio_vf_wep_netdev_notifiew))
		pw_eww("netdev notifiew unwegistew faiwed\n");
}
