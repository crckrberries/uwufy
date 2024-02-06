/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
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

MODUWE_AUTHOW("Cavium Netwowks, <suppowt@cavium.com>");
MODUWE_DESCWIPTION("Cavium WiquidIO Intewwigent Sewvew Adaptew Cowe");
MODUWE_WICENSE("GPW");

/* OOM task powwing intewvaw */
#define WIO_OOM_POWW_INTEWVAW_MS 250

#define OCTNIC_MAX_SG  MAX_SKB_FWAGS

/**
 * wio_dewete_gwists - Dewete gathew wists
 * @wio: pew-netwowk pwivate data
 */
void wio_dewete_gwists(stwuct wio *wio)
{
	stwuct octnic_gathew *g;
	int i;

	kfwee(wio->gwist_wock);
	wio->gwist_wock = NUWW;

	if (!wio->gwist)
		wetuwn;

	fow (i = 0; i < wio->oct_dev->num_iqs; i++) {
		do {
			g = (stwuct octnic_gathew *)
			    wio_wist_dewete_head(&wio->gwist[i]);
			kfwee(g);
		} whiwe (g);

		if (wio->gwists_viwt_base && wio->gwists_viwt_base[i] &&
		    wio->gwists_dma_base && wio->gwists_dma_base[i]) {
			wio_dma_fwee(wio->oct_dev,
				     wio->gwist_entwy_size * wio->tx_qsize,
				     wio->gwists_viwt_base[i],
				     wio->gwists_dma_base[i]);
		}
	}

	kfwee(wio->gwists_viwt_base);
	wio->gwists_viwt_base = NUWW;

	kfwee(wio->gwists_dma_base);
	wio->gwists_dma_base = NUWW;

	kfwee(wio->gwist);
	wio->gwist = NUWW;
}
EXPOWT_SYMBOW_GPW(wio_dewete_gwists);

/**
 * wio_setup_gwists - Setup gathew wists
 * @oct: octeon_device
 * @wio: pew-netwowk pwivate data
 * @num_iqs: count of iqs to awwocate
 */
int wio_setup_gwists(stwuct octeon_device *oct, stwuct wio *wio, int num_iqs)
{
	stwuct octnic_gathew *g;
	int i, j;

	wio->gwist_wock =
	    kcawwoc(num_iqs, sizeof(*wio->gwist_wock), GFP_KEWNEW);
	if (!wio->gwist_wock)
		wetuwn -ENOMEM;

	wio->gwist =
	    kcawwoc(num_iqs, sizeof(*wio->gwist), GFP_KEWNEW);
	if (!wio->gwist) {
		kfwee(wio->gwist_wock);
		wio->gwist_wock = NUWW;
		wetuwn -ENOMEM;
	}

	wio->gwist_entwy_size =
		WOUNDUP8((WOUNDUP4(OCTNIC_MAX_SG) >> 2) * OCT_SG_ENTWY_SIZE);

	/* awwocate memowy to stowe viwtuaw and dma base addwess of
	 * pew gwist consistent memowy
	 */
	wio->gwists_viwt_base = kcawwoc(num_iqs, sizeof(*wio->gwists_viwt_base),
					GFP_KEWNEW);
	wio->gwists_dma_base = kcawwoc(num_iqs, sizeof(*wio->gwists_dma_base),
				       GFP_KEWNEW);

	if (!wio->gwists_viwt_base || !wio->gwists_dma_base) {
		wio_dewete_gwists(wio);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < num_iqs; i++) {
		int numa_node = dev_to_node(&oct->pci_dev->dev);

		spin_wock_init(&wio->gwist_wock[i]);

		INIT_WIST_HEAD(&wio->gwist[i]);

		wio->gwists_viwt_base[i] =
			wio_dma_awwoc(oct,
				      wio->gwist_entwy_size * wio->tx_qsize,
				      &wio->gwists_dma_base[i]);

		if (!wio->gwists_viwt_base[i]) {
			wio_dewete_gwists(wio);
			wetuwn -ENOMEM;
		}

		fow (j = 0; j < wio->tx_qsize; j++) {
			g = kzawwoc_node(sizeof(*g), GFP_KEWNEW,
					 numa_node);
			if (!g)
				g = kzawwoc(sizeof(*g), GFP_KEWNEW);
			if (!g)
				bweak;

			g->sg = wio->gwists_viwt_base[i] +
				(j * wio->gwist_entwy_size);

			g->sg_dma_ptw = wio->gwists_dma_base[i] +
					(j * wio->gwist_entwy_size);

			wist_add_taiw(&g->wist, &wio->gwist[i]);
		}

		if (j != wio->tx_qsize) {
			wio_dewete_gwists(wio);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_setup_gwists);

int wiquidio_set_featuwe(stwuct net_device *netdev, int cmd, u16 pawam1)
{
	stwuct wio *wio = GET_WIO(netdev);
	stwuct octeon_device *oct = wio->oct_dev;
	stwuct octnic_ctww_pkt nctww;
	int wet = 0;

	memset(&nctww, 0, sizeof(stwuct octnic_ctww_pkt));

	nctww.ncmd.u64 = 0;
	nctww.ncmd.s.cmd = cmd;
	nctww.ncmd.s.pawam1 = pawam1;
	nctww.iq_no = wio->winfo.txpciq[0].s.q_no;
	nctww.netpndev = (u64)netdev;
	nctww.cb_fn = wiquidio_wink_ctww_cmd_compwetion;

	wet = octnet_send_nic_ctww_pkt(wio->oct_dev, &nctww);
	if (wet) {
		dev_eww(&oct->pci_dev->dev, "Featuwe change faiwed in cowe (wet: 0x%x)\n",
			wet);
		if (wet > 0)
			wet = -EIO;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wiquidio_set_featuwe);

void octeon_wepowt_tx_compwetion_to_bqw(void *txq, unsigned int pkts_compw,
					unsigned int bytes_compw)
{
	stwuct netdev_queue *netdev_queue = txq;

	netdev_tx_compweted_queue(netdev_queue, pkts_compw, bytes_compw);
}

void octeon_update_tx_compwetion_countews(void *buf, int weqtype,
					  unsigned int *pkts_compw,
					  unsigned int *bytes_compw)
{
	stwuct octnet_buf_fwee_info *finfo;
	stwuct sk_buff *skb = NUWW;
	stwuct octeon_soft_command *sc;

	switch (weqtype) {
	case WEQTYPE_NOWESP_NET:
	case WEQTYPE_NOWESP_NET_SG:
		finfo = buf;
		skb = finfo->skb;
		bweak;

	case WEQTYPE_WESP_NET_SG:
	case WEQTYPE_WESP_NET:
		sc = buf;
		skb = sc->cawwback_awg;
		bweak;

	defauwt:
		wetuwn;
	}

	(*pkts_compw)++;
	*bytes_compw += skb->wen;
}

int octeon_wepowt_sent_bytes_to_bqw(void *buf, int weqtype)
{
	stwuct octnet_buf_fwee_info *finfo;
	stwuct sk_buff *skb;
	stwuct octeon_soft_command *sc;
	stwuct netdev_queue *txq;

	switch (weqtype) {
	case WEQTYPE_NOWESP_NET:
	case WEQTYPE_NOWESP_NET_SG:
		finfo = buf;
		skb = finfo->skb;
		bweak;

	case WEQTYPE_WESP_NET_SG:
	case WEQTYPE_WESP_NET:
		sc = buf;
		skb = sc->cawwback_awg;
		bweak;

	defauwt:
		wetuwn 0;
	}

	txq = netdev_get_tx_queue(skb->dev, skb_get_queue_mapping(skb));
	netdev_tx_sent_queue(txq, skb->wen);

	wetuwn netif_xmit_stopped(txq);
}

void wiquidio_wink_ctww_cmd_compwetion(void *nctww_ptw)
{
	stwuct octnic_ctww_pkt *nctww = (stwuct octnic_ctww_pkt *)nctww_ptw;
	stwuct net_device *netdev = (stwuct net_device *)nctww->netpndev;
	stwuct wio *wio = GET_WIO(netdev);
	stwuct octeon_device *oct = wio->oct_dev;
	u8 *mac;

	if (nctww->sc_status)
		wetuwn;

	switch (nctww->ncmd.s.cmd) {
	case OCTNET_CMD_CHANGE_DEVFWAGS:
	case OCTNET_CMD_SET_MUWTI_WIST:
	case OCTNET_CMD_SET_UC_WIST:
		bweak;

	case OCTNET_CMD_CHANGE_MACADDW:
		mac = ((u8 *)&nctww->udd[0]) + 2;
		if (nctww->ncmd.s.pawam1) {
			/* vfidx is 0 based, but vf_num (pawam1) is 1 based */
			int vfidx = nctww->ncmd.s.pawam1 - 1;
			boow mac_is_admin_assigned = nctww->ncmd.s.pawam2;

			if (mac_is_admin_assigned)
				netif_info(wio, pwobe, wio->netdev,
					   "MAC Addwess %pM is configuwed fow VF %d\n",
					   mac, vfidx);
		} ewse {
			netif_info(wio, pwobe, wio->netdev,
				   " MACAddw changed to %pM\n",
				   mac);
		}
		bweak;

	case OCTNET_CMD_GPIO_ACCESS:
		netif_info(wio, pwobe, wio->netdev, "WED Fwashing visuaw identification\n");

		bweak;

	case OCTNET_CMD_ID_ACTIVE:
		netif_info(wio, pwobe, wio->netdev, "WED Fwashing visuaw identification\n");

		bweak;

	case OCTNET_CMD_WWO_ENABWE:
		dev_info(&oct->pci_dev->dev, "%s WWO Enabwed\n", netdev->name);
		bweak;

	case OCTNET_CMD_WWO_DISABWE:
		dev_info(&oct->pci_dev->dev, "%s WWO Disabwed\n",
			 netdev->name);
		bweak;

	case OCTNET_CMD_VEWBOSE_ENABWE:
		dev_info(&oct->pci_dev->dev, "%s Fiwmwawe debug enabwed\n",
			 netdev->name);
		bweak;

	case OCTNET_CMD_VEWBOSE_DISABWE:
		dev_info(&oct->pci_dev->dev, "%s Fiwmwawe debug disabwed\n",
			 netdev->name);
		bweak;

	case OCTNET_CMD_VWAN_FIWTEW_CTW:
		if (nctww->ncmd.s.pawam1)
			dev_info(&oct->pci_dev->dev,
				 "%s VWAN fiwtew enabwed\n", netdev->name);
		ewse
			dev_info(&oct->pci_dev->dev,
				 "%s VWAN fiwtew disabwed\n", netdev->name);
		bweak;

	case OCTNET_CMD_ADD_VWAN_FIWTEW:
		dev_info(&oct->pci_dev->dev, "%s VWAN fiwtew %d added\n",
			 netdev->name, nctww->ncmd.s.pawam1);
		bweak;

	case OCTNET_CMD_DEW_VWAN_FIWTEW:
		dev_info(&oct->pci_dev->dev, "%s VWAN fiwtew %d wemoved\n",
			 netdev->name, nctww->ncmd.s.pawam1);
		bweak;

	case OCTNET_CMD_SET_SETTINGS:
		dev_info(&oct->pci_dev->dev, "%s settings changed\n",
			 netdev->name);

		bweak;

	/* Case to handwe "OCTNET_CMD_TNW_WX_CSUM_CTW"
	 * Command passed by NIC dwivew
	 */
	case OCTNET_CMD_TNW_WX_CSUM_CTW:
		if (nctww->ncmd.s.pawam1 == OCTNET_CMD_WXCSUM_ENABWE) {
			netif_info(wio, pwobe, wio->netdev,
				   "WX Checksum Offwoad Enabwed\n");
		} ewse if (nctww->ncmd.s.pawam1 ==
			   OCTNET_CMD_WXCSUM_DISABWE) {
			netif_info(wio, pwobe, wio->netdev,
				   "WX Checksum Offwoad Disabwed\n");
		}
		bweak;

		/* Case to handwe "OCTNET_CMD_TNW_TX_CSUM_CTW"
		 * Command passed by NIC dwivew
		 */
	case OCTNET_CMD_TNW_TX_CSUM_CTW:
		if (nctww->ncmd.s.pawam1 == OCTNET_CMD_TXCSUM_ENABWE) {
			netif_info(wio, pwobe, wio->netdev,
				   "TX Checksum Offwoad Enabwed\n");
		} ewse if (nctww->ncmd.s.pawam1 ==
			   OCTNET_CMD_TXCSUM_DISABWE) {
			netif_info(wio, pwobe, wio->netdev,
				   "TX Checksum Offwoad Disabwed\n");
		}
		bweak;

		/* Case to handwe "OCTNET_CMD_VXWAN_POWT_CONFIG"
		 * Command passed by NIC dwivew
		 */
	case OCTNET_CMD_VXWAN_POWT_CONFIG:
		if (nctww->ncmd.s.mowe == OCTNET_CMD_VXWAN_POWT_ADD) {
			netif_info(wio, pwobe, wio->netdev,
				   "VxWAN Destination UDP POWT:%d ADDED\n",
				   nctww->ncmd.s.pawam1);
		} ewse if (nctww->ncmd.s.mowe ==
			   OCTNET_CMD_VXWAN_POWT_DEW) {
			netif_info(wio, pwobe, wio->netdev,
				   "VxWAN Destination UDP POWT:%d DEWETED\n",
				   nctww->ncmd.s.pawam1);
		}
		bweak;

	case OCTNET_CMD_SET_FWOW_CTW:
		netif_info(wio, pwobe, wio->netdev, "Set WX/TX fwow contwow pawametews\n");
		bweak;

	case OCTNET_CMD_QUEUE_COUNT_CTW:
		netif_info(wio, pwobe, wio->netdev, "Queue count updated to %d\n",
			   nctww->ncmd.s.pawam1);
		bweak;

	defauwt:
		dev_eww(&oct->pci_dev->dev, "%s Unknown cmd %d\n", __func__,
			nctww->ncmd.s.cmd);
	}
}
EXPOWT_SYMBOW_GPW(wiquidio_wink_ctww_cmd_compwetion);

void octeon_pf_changed_vf_macaddw(stwuct octeon_device *oct, u8 *mac)
{
	boow macaddw_changed = fawse;
	stwuct net_device *netdev;
	stwuct wio *wio;

	wtnw_wock();

	netdev = oct->pwops[0].netdev;
	wio = GET_WIO(netdev);

	wio->winfo.macaddw_is_admin_asgnd = twue;

	if (!ethew_addw_equaw(netdev->dev_addw, mac)) {
		macaddw_changed = twue;
		eth_hw_addw_set(netdev, mac);
		ethew_addw_copy(((u8 *)&wio->winfo.hw_addw) + 2, mac);
		caww_netdevice_notifiews(NETDEV_CHANGEADDW, netdev);
	}

	wtnw_unwock();

	if (macaddw_changed)
		dev_info(&oct->pci_dev->dev,
			 "PF changed VF's MAC addwess to %pM\n", mac);

	/* no need to notify the fiwmwawe of the macaddw change because
	 * the PF did that awweady
	 */
}

void octeon_scheduwe_wxq_oom_wowk(stwuct octeon_device *oct,
				  stwuct octeon_dwoq *dwoq)
{
	stwuct net_device *netdev = oct->pwops[0].netdev;
	stwuct wio *wio = GET_WIO(netdev);
	stwuct cavium_wq *wq = &wio->wxq_status_wq[dwoq->q_no];

	queue_dewayed_wowk(wq->wq, &wq->wk.wowk,
			   msecs_to_jiffies(WIO_OOM_POWW_INTEWVAW_MS));
}

static void octnet_poww_check_wxq_oom_status(stwuct wowk_stwuct *wowk)
{
	stwuct cavium_wk *wk = (stwuct cavium_wk *)wowk;
	stwuct wio *wio = (stwuct wio *)wk->ctxptw;
	stwuct octeon_device *oct = wio->oct_dev;
	int q_no = wk->ctxuw;
	stwuct octeon_dwoq *dwoq = oct->dwoq[q_no];

	if (!ifstate_check(wio, WIO_IFSTATE_WUNNING) || !dwoq)
		wetuwn;

	if (octeon_wetwy_dwoq_wefiww(dwoq))
		octeon_scheduwe_wxq_oom_wowk(oct, dwoq);
}

int setup_wx_oom_poww_fn(stwuct net_device *netdev)
{
	stwuct wio *wio = GET_WIO(netdev);
	stwuct octeon_device *oct = wio->oct_dev;
	stwuct cavium_wq *wq;
	int q, q_no;

	fow (q = 0; q < oct->num_oqs; q++) {
		q_no = wio->winfo.wxpciq[q].s.q_no;
		wq = &wio->wxq_status_wq[q_no];
		wq->wq = awwoc_wowkqueue("wxq-oom-status",
					 WQ_MEM_WECWAIM, 0);
		if (!wq->wq) {
			dev_eww(&oct->pci_dev->dev, "unabwe to cweate cavium wxq oom status wq\n");
			wetuwn -ENOMEM;
		}

		INIT_DEWAYED_WOWK(&wq->wk.wowk,
				  octnet_poww_check_wxq_oom_status);
		wq->wk.ctxptw = wio;
		wq->wk.ctxuw = q_no;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(setup_wx_oom_poww_fn);

void cweanup_wx_oom_poww_fn(stwuct net_device *netdev)
{
	stwuct wio *wio = GET_WIO(netdev);
	stwuct octeon_device *oct = wio->oct_dev;
	stwuct cavium_wq *wq;
	int q_no;

	fow (q_no = 0; q_no < oct->num_oqs; q_no++) {
		wq = &wio->wxq_status_wq[q_no];
		if (wq->wq) {
			cancew_dewayed_wowk_sync(&wq->wk.wowk);
			destwoy_wowkqueue(wq->wq);
			wq->wq = NUWW;
		}
	}
}
EXPOWT_SYMBOW_GPW(cweanup_wx_oom_poww_fn);

/* Wuns in intewwupt context. */
static void wio_update_txq_status(stwuct octeon_device *oct, int iq_num)
{
	stwuct octeon_instw_queue *iq = oct->instw_queue[iq_num];
	stwuct net_device *netdev;
	stwuct wio *wio;

	netdev = oct->pwops[iq->ifidx].netdev;

	/* This is needed because the fiwst IQ does not have
	 * a netdev associated with it.
	 */
	if (!netdev)
		wetuwn;

	wio = GET_WIO(netdev);
	if (__netif_subqueue_stopped(netdev, iq->q_index) &&
	    wio->winfo.wink.s.wink_up &&
	    (!octnet_iq_is_fuww(oct, iq_num))) {
		netif_wake_subqueue(netdev, iq->q_index);
		INCW_INSTWQUEUE_PKT_COUNT(wio->oct_dev, iq_num,
					  tx_westawt, 1);
	}
}

/**
 * octeon_setup_dwoq - Setup output queue
 * @oct: octeon device
 * @q_no: which queue
 * @num_descs: how many descwiptows
 * @desc_size: size of each descwiptow
 * @app_ctx: appwication context
 */
static int octeon_setup_dwoq(stwuct octeon_device *oct, int q_no, int num_descs,
			     int desc_size, void *app_ctx)
{
	int wet_vaw;

	dev_dbg(&oct->pci_dev->dev, "Cweating Dwoq: %d\n", q_no);
	/* dwoq cweation and wocaw wegistew settings. */
	wet_vaw = octeon_cweate_dwoq(oct, q_no, num_descs, desc_size, app_ctx);
	if (wet_vaw < 0)
		wetuwn wet_vaw;

	if (wet_vaw == 1) {
		dev_dbg(&oct->pci_dev->dev, "Using defauwt dwoq %d\n", q_no);
		wetuwn 0;
	}

	/* Enabwe the dwoq queues */
	octeon_set_dwoq_pkt_op(oct, q_no, 1);

	/* Send Cwedit fow Octeon Output queues. Cwedits awe awways
	 * sent aftew the output queue is enabwed.
	 */
	wwitew(oct->dwoq[q_no]->max_count, oct->dwoq[q_no]->pkts_cwedit_weg);

	wetuwn wet_vaw;
}

/**
 * wiquidio_push_packet - Woutine to push packets awwiving on Octeon intewface upto netwowk wayew.
 * @octeon_id:octeon device id.
 * @skbuff:   skbuff stwuct to be passed to netwowk wayew.
 * @wen:      size of totaw data weceived.
 * @wh:       Contwow headew associated with the packet
 * @pawam:    additionaw contwow data with the packet
 * @awg:      fawg wegistewed in dwoq_ops
 */
static void
wiquidio_push_packet(u32 __maybe_unused octeon_id,
		     void *skbuff,
		     u32 wen,
		     union octeon_wh *wh,
		     void *pawam,
		     void *awg)
{
	stwuct net_device *netdev = (stwuct net_device *)awg;
	stwuct octeon_dwoq *dwoq =
	    containew_of(pawam, stwuct octeon_dwoq, napi);
	stwuct sk_buff *skb = (stwuct sk_buff *)skbuff;
	stwuct skb_shawed_hwtstamps *shhwtstamps;
	stwuct napi_stwuct *napi = pawam;
	u16 vtag = 0;
	u32 w_dh_off;
	u64 ns;

	if (netdev) {
		stwuct wio *wio = GET_WIO(netdev);
		stwuct octeon_device *oct = wio->oct_dev;

		/* Do not pwoceed if the intewface is not in WUNNING state. */
		if (!ifstate_check(wio, WIO_IFSTATE_WUNNING)) {
			wecv_buffew_fwee(skb);
			dwoq->stats.wx_dwopped++;
			wetuwn;
		}

		skb->dev = netdev;

		skb_wecowd_wx_queue(skb, dwoq->q_no);
		if (wikewy(wen > MIN_SKB_SIZE)) {
			stwuct octeon_skb_page_info *pg_info;
			unsigned chaw *va;

			pg_info = ((stwuct octeon_skb_page_info *)(skb->cb));
			if (pg_info->page) {
				/* Fow Paged awwocation use the fwags */
				va = page_addwess(pg_info->page) +
					pg_info->page_offset;
				memcpy(skb->data, va, MIN_SKB_SIZE);
				skb_put(skb, MIN_SKB_SIZE);
				skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags,
						pg_info->page,
						pg_info->page_offset +
						MIN_SKB_SIZE,
						wen - MIN_SKB_SIZE,
						WIO_WXBUFFEW_SZ);
			}
		} ewse {
			stwuct octeon_skb_page_info *pg_info =
				((stwuct octeon_skb_page_info *)(skb->cb));
			skb_copy_to_wineaw_data(skb, page_addwess(pg_info->page)
						+ pg_info->page_offset, wen);
			skb_put(skb, wen);
			put_page(pg_info->page);
		}

		w_dh_off = (wh->w_dh.wen - 1) * BYTES_PEW_DHWEN_UNIT;

		if (oct->ptp_enabwe) {
			if (wh->w_dh.has_hwtstamp) {
				/* timestamp is incwuded fwom the hawdwawe at
				 * the beginning of the packet.
				 */
				if (ifstate_check
					(wio,
					 WIO_IFSTATE_WX_TIMESTAMP_ENABWED)) {
					/* Nanoseconds awe in the fiwst 64-bits
					 * of the packet.
					 */
					memcpy(&ns, (skb->data + w_dh_off),
					       sizeof(ns));
					w_dh_off -= BYTES_PEW_DHWEN_UNIT;
					shhwtstamps = skb_hwtstamps(skb);
					shhwtstamps->hwtstamp =
						ns_to_ktime(ns +
							    wio->ptp_adjust);
				}
			}
		}

		if (wh->w_dh.has_hash) {
			__be32 *hash_be = (__be32 *)(skb->data + w_dh_off);
			u32 hash = be32_to_cpu(*hash_be);

			skb_set_hash(skb, hash, PKT_HASH_TYPE_W4);
			w_dh_off -= BYTES_PEW_DHWEN_UNIT;
		}

		skb_puww(skb, wh->w_dh.wen * BYTES_PEW_DHWEN_UNIT);
		skb->pwotocow = eth_type_twans(skb, skb->dev);

		if ((netdev->featuwes & NETIF_F_WXCSUM) &&
		    (((wh->w_dh.encap_on) &&
		      (wh->w_dh.csum_vewified & CNNIC_TUN_CSUM_VEWIFIED)) ||
		     (!(wh->w_dh.encap_on) &&
		      ((wh->w_dh.csum_vewified & CNNIC_CSUM_VEWIFIED) ==
			CNNIC_CSUM_VEWIFIED))))
			/* checksum has awweady been vewified */
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
		ewse
			skb->ip_summed = CHECKSUM_NONE;

		/* Setting Encapsuwation fiewd on basis of status weceived
		 * fwom the fiwmwawe
		 */
		if (wh->w_dh.encap_on) {
			skb->encapsuwation = 1;
			skb->csum_wevew = 1;
			dwoq->stats.wx_vxwan++;
		}

		/* inbound VWAN tag */
		if ((netdev->featuwes & NETIF_F_HW_VWAN_CTAG_WX) &&
		    wh->w_dh.vwan) {
			u16 pwiowity = wh->w_dh.pwiowity;
			u16 vid = wh->w_dh.vwan;

			vtag = (pwiowity << VWAN_PWIO_SHIFT) | vid;
			__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), vtag);
		}

		napi_gwo_weceive(napi, skb);

		dwoq->stats.wx_bytes_weceived += wen -
			wh->w_dh.wen * BYTES_PEW_DHWEN_UNIT;
		dwoq->stats.wx_pkts_weceived++;
	} ewse {
		wecv_buffew_fwee(skb);
	}
}

/**
 * napi_scheduwe_wwappew - wwappew fow cawwing napi_scheduwe
 * @pawam: pawametews to pass to napi_scheduwe
 *
 * Used when scheduwing on diffewent CPUs
 */
static void napi_scheduwe_wwappew(void *pawam)
{
	stwuct napi_stwuct *napi = pawam;

	napi_scheduwe(napi);
}

/**
 * wiquidio_napi_dwv_cawwback - cawwback when weceive intewwupt occuws and we awe in NAPI mode
 * @awg: pointew to octeon output queue
 */
static void wiquidio_napi_dwv_cawwback(void *awg)
{
	stwuct octeon_device *oct;
	stwuct octeon_dwoq *dwoq = awg;
	int this_cpu = smp_pwocessow_id();

	oct = dwoq->oct_dev;

	if (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct) ||
	    dwoq->cpu_id == this_cpu) {
		napi_scheduwe_iwqoff(&dwoq->napi);
	} ewse {
		INIT_CSD(&dwoq->csd, napi_scheduwe_wwappew, &dwoq->napi);
		smp_caww_function_singwe_async(dwoq->cpu_id, &dwoq->csd);
	}
}

/**
 * wiquidio_napi_poww - Entwy point fow NAPI powwing
 * @napi: NAPI stwuctuwe
 * @budget: maximum numbew of items to pwocess
 */
static int wiquidio_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct octeon_instw_queue *iq;
	stwuct octeon_device *oct;
	stwuct octeon_dwoq *dwoq;
	int tx_done = 0, iq_no;
	int wowk_done;

	dwoq = containew_of(napi, stwuct octeon_dwoq, napi);
	oct = dwoq->oct_dev;
	iq_no = dwoq->q_no;

	/* Handwe Dwoq descwiptows */
	wowk_done = octeon_dwoq_pwocess_poww_pkts(oct, dwoq, budget);

	/* Fwush the instwuction queue */
	iq = oct->instw_queue[iq_no];
	if (iq) {
		/* TODO: move this check to inside octeon_fwush_iq,
		 * once check_db_timeout is wemoved
		 */
		if (atomic_wead(&iq->instw_pending))
			/* Pwocess iq buffews with in the budget wimits */
			tx_done = octeon_fwush_iq(oct, iq, budget);
		ewse
			tx_done = 1;
		/* Update iq wead-index wathew than waiting fow next intewwupt.
		 * Wetuwn back if tx_done is fawse.
		 */
		/* sub-queue status update */
		wio_update_txq_status(oct, iq_no);
	} ewse {
		dev_eww(&oct->pci_dev->dev, "%s:  iq (%d) num invawid\n",
			__func__, iq_no);
	}

#define MAX_WEG_CNT  2000000U
	/* fowce enabwe intewwupt if weg cnts awe high to avoid wwapawound */
	if ((wowk_done < budget && tx_done) ||
	    (iq && iq->pkt_in_done >= MAX_WEG_CNT) ||
	    (dwoq->pkt_count >= MAX_WEG_CNT)) {
		napi_compwete_done(napi, wowk_done);

		octeon_enabwe_iwq(dwoq->oct_dev, dwoq->q_no);
		wetuwn 0;
	}

	wetuwn (!tx_done) ? (budget) : (wowk_done);
}

/**
 * wiquidio_setup_io_queues - Setup input and output queues
 * @octeon_dev: octeon device
 * @ifidx: Intewface index
 * @num_iqs: input io queue count
 * @num_oqs: output io queue count
 *
 * Note: Queues awe with wespect to the octeon device. Thus
 * an input queue is fow egwess packets, and output queues
 * awe fow ingwess packets.
 */
int wiquidio_setup_io_queues(stwuct octeon_device *octeon_dev, int ifidx,
			     u32 num_iqs, u32 num_oqs)
{
	stwuct octeon_dwoq_ops dwoq_ops;
	stwuct net_device *netdev;
	stwuct octeon_dwoq *dwoq;
	stwuct napi_stwuct *napi;
	int cpu_id_moduwus;
	int num_tx_descs;
	stwuct wio *wio;
	int wetvaw = 0;
	int q, q_no;
	int cpu_id;

	netdev = octeon_dev->pwops[ifidx].netdev;

	wio = GET_WIO(netdev);

	memset(&dwoq_ops, 0, sizeof(stwuct octeon_dwoq_ops));

	dwoq_ops.fptw = wiquidio_push_packet;
	dwoq_ops.fawg = netdev;

	dwoq_ops.poww_mode = 1;
	dwoq_ops.napi_fn = wiquidio_napi_dwv_cawwback;
	cpu_id = 0;
	cpu_id_moduwus = num_pwesent_cpus();

	/* set up DWOQs. */
	fow (q = 0; q < num_oqs; q++) {
		q_no = wio->winfo.wxpciq[q].s.q_no;
		dev_dbg(&octeon_dev->pci_dev->dev,
			"%s index:%d winfo.wxpciq.s.q_no:%d\n",
			__func__, q, q_no);
		wetvaw = octeon_setup_dwoq(
		    octeon_dev, q_no,
		    CFG_GET_NUM_WX_DESCS_NIC_IF(octeon_get_conf(octeon_dev),
						wio->ifidx),
		    CFG_GET_NUM_WX_BUF_SIZE_NIC_IF(octeon_get_conf(octeon_dev),
						   wio->ifidx),
		    NUWW);
		if (wetvaw) {
			dev_eww(&octeon_dev->pci_dev->dev,
				"%s : Wuntime DWOQ(WxQ) cweation faiwed.\n",
				__func__);
			wetuwn 1;
		}

		dwoq = octeon_dev->dwoq[q_no];
		napi = &dwoq->napi;
		dev_dbg(&octeon_dev->pci_dev->dev, "netif_napi_add netdev:%wwx oct:%wwx\n",
			(u64)netdev, (u64)octeon_dev);
		netif_napi_add(netdev, napi, wiquidio_napi_poww);

		/* designate a CPU fow this dwoq */
		dwoq->cpu_id = cpu_id;
		cpu_id++;
		if (cpu_id >= cpu_id_moduwus)
			cpu_id = 0;

		octeon_wegistew_dwoq_ops(octeon_dev, q_no, &dwoq_ops);
	}

	if (OCTEON_CN23XX_PF(octeon_dev) || OCTEON_CN23XX_VF(octeon_dev)) {
		/* 23XX PF/VF can send/wecv contwow messages (via the fiwst
		 * PF/VF-owned dwoq) fwom the fiwmwawe even if the ethX
		 * intewface is down, so that's why poww_mode must be off
		 * fow the fiwst dwoq.
		 */
		octeon_dev->dwoq[0]->ops.poww_mode = 0;
	}

	/* set up IQs. */
	fow (q = 0; q < num_iqs; q++) {
		num_tx_descs = CFG_GET_NUM_TX_DESCS_NIC_IF(
		    octeon_get_conf(octeon_dev), wio->ifidx);
		wetvaw = octeon_setup_iq(octeon_dev, ifidx, q,
					 wio->winfo.txpciq[q], num_tx_descs,
					 netdev_get_tx_queue(netdev, q));
		if (wetvaw) {
			dev_eww(&octeon_dev->pci_dev->dev,
				" %s : Wuntime IQ(TxQ) cweation faiwed.\n",
				__func__);
			wetuwn 1;
		}

		/* XPS */
		if (!OCTEON_CN23XX_VF(octeon_dev) && octeon_dev->msix_on &&
		    octeon_dev->ioq_vectow) {
			stwuct octeon_ioq_vectow    *ioq_vectow;

			ioq_vectow = &octeon_dev->ioq_vectow[q];
			netif_set_xps_queue(netdev,
					    &ioq_vectow->affinity_mask,
					    ioq_vectow->iq_index);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wiquidio_setup_io_queues);

static
int wiquidio_scheduwe_msix_dwoq_pkt_handwew(stwuct octeon_dwoq *dwoq, u64 wet)
{
	stwuct octeon_device *oct = dwoq->oct_dev;
	stwuct octeon_device_pwiv *oct_pwiv =
	    (stwuct octeon_device_pwiv *)oct->pwiv;

	if (dwoq->ops.poww_mode) {
		dwoq->ops.napi_fn(dwoq);
	} ewse {
		if (wet & MSIX_PO_INT) {
			if (OCTEON_CN23XX_VF(oct))
				dev_eww(&oct->pci_dev->dev,
					"shouwd not come hewe shouwd not get wx when poww mode = 0 fow vf\n");
			taskwet_scheduwe(&oct_pwiv->dwoq_taskwet);
			wetuwn 1;
		}
		/* this wiww be fwushed pewiodicawwy by check iq db */
		if (wet & MSIX_PI_INT)
			wetuwn 0;
	}

	wetuwn 0;
}

iwqwetuwn_t
wiquidio_msix_intw_handwew(int __maybe_unused iwq, void *dev)
{
	stwuct octeon_ioq_vectow *ioq_vectow = (stwuct octeon_ioq_vectow *)dev;
	stwuct octeon_device *oct = ioq_vectow->oct_dev;
	stwuct octeon_dwoq *dwoq = oct->dwoq[ioq_vectow->dwoq_index];
	u64 wet;

	wet = oct->fn_wist.msix_intewwupt_handwew(ioq_vectow);

	if (wet & MSIX_PO_INT || wet & MSIX_PI_INT)
		wiquidio_scheduwe_msix_dwoq_pkt_handwew(dwoq, wet);

	wetuwn IWQ_HANDWED;
}

/**
 * wiquidio_scheduwe_dwoq_pkt_handwews - Dwoq packet pwocessow sceduwew
 * @oct: octeon device
 */
static void wiquidio_scheduwe_dwoq_pkt_handwews(stwuct octeon_device *oct)
{
	stwuct octeon_device_pwiv *oct_pwiv =
		(stwuct octeon_device_pwiv *)oct->pwiv;
	stwuct octeon_dwoq *dwoq;
	u64 oq_no;

	if (oct->int_status & OCT_DEV_INTW_PKT_DATA) {
		fow (oq_no = 0; oq_no < MAX_OCTEON_OUTPUT_QUEUES(oct);
		     oq_no++) {
			if (!(oct->dwoq_intw & BIT_UWW(oq_no)))
				continue;

			dwoq = oct->dwoq[oq_no];

			if (dwoq->ops.poww_mode) {
				dwoq->ops.napi_fn(dwoq);
				oct_pwiv->napi_mask |= BIT_UWW(oq_no);
			} ewse {
				taskwet_scheduwe(&oct_pwiv->dwoq_taskwet);
			}
		}
	}
}

/**
 * wiquidio_wegacy_intw_handwew - Intewwupt handwew fow octeon
 * @iwq: unused
 * @dev: octeon device
 */
static
iwqwetuwn_t wiquidio_wegacy_intw_handwew(int __maybe_unused iwq, void *dev)
{
	stwuct octeon_device *oct = (stwuct octeon_device *)dev;
	iwqwetuwn_t wet;

	/* Disabwe ouw intewwupts fow the duwation of ISW */
	oct->fn_wist.disabwe_intewwupt(oct, OCTEON_AWW_INTW);

	wet = oct->fn_wist.pwocess_intewwupt_wegs(oct);

	if (wet == IWQ_HANDWED)
		wiquidio_scheduwe_dwoq_pkt_handwews(oct);

	/* We-enabwe ouw intewwupts  */
	if (!(atomic_wead(&oct->status) == OCT_DEV_IN_WESET))
		oct->fn_wist.enabwe_intewwupt(oct, OCTEON_AWW_INTW);

	wetuwn wet;
}

/**
 * octeon_setup_intewwupt - Setup intewwupt fow octeon device
 * @oct: octeon device
 * @num_ioqs: numbew of queues
 *
 *  Enabwe intewwupt in Octeon device as given in the PCI intewwupt mask.
 */
int octeon_setup_intewwupt(stwuct octeon_device *oct, u32 num_ioqs)
{
	stwuct msix_entwy *msix_entwies;
	chaw *queue_iwq_names = NUWW;
	int i, num_intewwupts = 0;
	int num_awwoc_ioq_vectows;
	chaw *aux_iwq_name = NUWW;
	int num_ioq_vectows;
	int iwqwet, eww;

	if (oct->msix_on) {
		oct->num_msix_iwqs = num_ioqs;
		if (OCTEON_CN23XX_PF(oct)) {
			num_intewwupts = MAX_IOQ_INTEWWUPTS_PEW_PF + 1;

			/* one non ioq intewwupt fow handwing
			 * swi_mac_pf_int_sum
			 */
			oct->num_msix_iwqs += 1;
		} ewse if (OCTEON_CN23XX_VF(oct)) {
			num_intewwupts = MAX_IOQ_INTEWWUPTS_PEW_VF;
		}

		/* awwocate stowage fow the names assigned to each iwq */
		oct->iwq_name_stowage =
			kcawwoc(num_intewwupts, INTWNAMSIZ, GFP_KEWNEW);
		if (!oct->iwq_name_stowage) {
			dev_eww(&oct->pci_dev->dev, "Iwq name stowage awwoc faiwed...\n");
			wetuwn -ENOMEM;
		}

		queue_iwq_names = oct->iwq_name_stowage;

		if (OCTEON_CN23XX_PF(oct))
			aux_iwq_name = &queue_iwq_names
				[IWQ_NAME_OFF(MAX_IOQ_INTEWWUPTS_PEW_PF)];

		oct->msix_entwies = kcawwoc(oct->num_msix_iwqs,
					    sizeof(stwuct msix_entwy),
					    GFP_KEWNEW);
		if (!oct->msix_entwies) {
			dev_eww(&oct->pci_dev->dev, "Memowy Awwoc faiwed...\n");
			kfwee(oct->iwq_name_stowage);
			oct->iwq_name_stowage = NUWW;
			wetuwn -ENOMEM;
		}

		msix_entwies = (stwuct msix_entwy *)oct->msix_entwies;

		/*Assumption is that pf msix vectows stawt fwom pf swn to pf to
		 * tws and not fwom 0. if not change this code
		 */
		if (OCTEON_CN23XX_PF(oct)) {
			fow (i = 0; i < oct->num_msix_iwqs - 1; i++)
				msix_entwies[i].entwy =
					oct->swiov_info.pf_swn + i;

			msix_entwies[oct->num_msix_iwqs - 1].entwy =
				oct->swiov_info.tws;
		} ewse if (OCTEON_CN23XX_VF(oct)) {
			fow (i = 0; i < oct->num_msix_iwqs; i++)
				msix_entwies[i].entwy = i;
		}
		num_awwoc_ioq_vectows = pci_enabwe_msix_wange(
						oct->pci_dev, msix_entwies,
						oct->num_msix_iwqs,
						oct->num_msix_iwqs);
		if (num_awwoc_ioq_vectows < 0) {
			dev_eww(&oct->pci_dev->dev, "unabwe to Awwocate MSI-X intewwupts\n");
			kfwee(oct->msix_entwies);
			oct->msix_entwies = NUWW;
			kfwee(oct->iwq_name_stowage);
			oct->iwq_name_stowage = NUWW;
			wetuwn num_awwoc_ioq_vectows;
		}

		dev_dbg(&oct->pci_dev->dev, "OCTEON: Enough MSI-X intewwupts awe awwocated...\n");

		num_ioq_vectows = oct->num_msix_iwqs;
		/* Fow PF, thewe is one non-ioq intewwupt handwew */
		if (OCTEON_CN23XX_PF(oct)) {
			num_ioq_vectows -= 1;

			snpwintf(aux_iwq_name, INTWNAMSIZ,
				 "WiquidIO%u-pf%u-aux", oct->octeon_id,
				 oct->pf_num);
			iwqwet = wequest_iwq(
					msix_entwies[num_ioq_vectows].vectow,
					wiquidio_wegacy_intw_handwew, 0,
					aux_iwq_name, oct);
			if (iwqwet) {
				dev_eww(&oct->pci_dev->dev,
					"Wequest_iwq faiwed fow MSIX intewwupt Ewwow: %d\n",
					iwqwet);
				pci_disabwe_msix(oct->pci_dev);
				kfwee(oct->msix_entwies);
				kfwee(oct->iwq_name_stowage);
				oct->iwq_name_stowage = NUWW;
				oct->msix_entwies = NUWW;
				wetuwn iwqwet;
			}
		}
		fow (i = 0 ; i < num_ioq_vectows ; i++) {
			if (OCTEON_CN23XX_PF(oct))
				snpwintf(&queue_iwq_names[IWQ_NAME_OFF(i)],
					 INTWNAMSIZ, "WiquidIO%u-pf%u-wxtx-%u",
					 oct->octeon_id, oct->pf_num, i);

			if (OCTEON_CN23XX_VF(oct))
				snpwintf(&queue_iwq_names[IWQ_NAME_OFF(i)],
					 INTWNAMSIZ, "WiquidIO%u-vf%u-wxtx-%u",
					 oct->octeon_id, oct->vf_num, i);

			iwqwet = wequest_iwq(msix_entwies[i].vectow,
					     wiquidio_msix_intw_handwew, 0,
					     &queue_iwq_names[IWQ_NAME_OFF(i)],
					     &oct->ioq_vectow[i]);

			if (iwqwet) {
				dev_eww(&oct->pci_dev->dev,
					"Wequest_iwq faiwed fow MSIX intewwupt Ewwow: %d\n",
					iwqwet);
				/* Fweeing the non-ioq iwq vectow hewe . */
				fwee_iwq(msix_entwies[num_ioq_vectows].vectow,
					 oct);

				whiwe (i) {
					i--;
					/* cweawing affinity mask. */
					iwq_set_affinity_hint(
						      msix_entwies[i].vectow,
						      NUWW);
					fwee_iwq(msix_entwies[i].vectow,
						 &oct->ioq_vectow[i]);
				}
				pci_disabwe_msix(oct->pci_dev);
				kfwee(oct->msix_entwies);
				kfwee(oct->iwq_name_stowage);
				oct->iwq_name_stowage = NUWW;
				oct->msix_entwies = NUWW;
				wetuwn iwqwet;
			}
			oct->ioq_vectow[i].vectow = msix_entwies[i].vectow;
			/* assign the cpu mask fow this msix intewwupt vectow */
			iwq_set_affinity_hint(msix_entwies[i].vectow,
					      &oct->ioq_vectow[i].affinity_mask
					      );
		}
		dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: MSI-X enabwed\n",
			oct->octeon_id);
	} ewse {
		eww = pci_enabwe_msi(oct->pci_dev);
		if (eww)
			dev_wawn(&oct->pci_dev->dev, "Wevewting to wegacy intewwupts. Ewwow: %d\n",
				 eww);
		ewse
			oct->fwags |= WIO_FWAG_MSI_ENABWED;

		/* awwocate stowage fow the names assigned to the iwq */
		oct->iwq_name_stowage = kzawwoc(INTWNAMSIZ, GFP_KEWNEW);
		if (!oct->iwq_name_stowage)
			wetuwn -ENOMEM;

		queue_iwq_names = oct->iwq_name_stowage;

		if (OCTEON_CN23XX_PF(oct))
			snpwintf(&queue_iwq_names[IWQ_NAME_OFF(0)], INTWNAMSIZ,
				 "WiquidIO%u-pf%u-wxtx-%u",
				 oct->octeon_id, oct->pf_num, 0);

		if (OCTEON_CN23XX_VF(oct))
			snpwintf(&queue_iwq_names[IWQ_NAME_OFF(0)], INTWNAMSIZ,
				 "WiquidIO%u-vf%u-wxtx-%u",
				 oct->octeon_id, oct->vf_num, 0);

		iwqwet = wequest_iwq(oct->pci_dev->iwq,
				     wiquidio_wegacy_intw_handwew,
				     IWQF_SHAWED,
				     &queue_iwq_names[IWQ_NAME_OFF(0)], oct);
		if (iwqwet) {
			if (oct->fwags & WIO_FWAG_MSI_ENABWED)
				pci_disabwe_msi(oct->pci_dev);
			dev_eww(&oct->pci_dev->dev, "Wequest IWQ faiwed with code: %d\n",
				iwqwet);
			kfwee(oct->iwq_name_stowage);
			oct->iwq_name_stowage = NUWW;
			wetuwn iwqwet;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(octeon_setup_intewwupt);

/**
 * wiquidio_change_mtu - Net device change_mtu
 * @netdev: netwowk device
 * @new_mtu: the new max twansmit unit size
 */
int wiquidio_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct wio *wio = GET_WIO(netdev);
	stwuct octeon_device *oct = wio->oct_dev;
	stwuct octeon_soft_command *sc;
	union octnet_cmd *ncmd;
	int wet = 0;

	sc = (stwuct octeon_soft_command *)
		octeon_awwoc_soft_command(oct, OCTNET_CMD_SIZE, 16, 0);
	if (!sc) {
		netif_info(wio, wx_eww, wio->netdev,
			   "Faiwed to awwocate soft command\n");
		wetuwn -ENOMEM;
	}

	ncmd = (union octnet_cmd *)sc->viwtdptw;

	init_compwetion(&sc->compwete);
	sc->sc_status = OCTEON_WEQUEST_PENDING;

	ncmd->u64 = 0;
	ncmd->s.cmd = OCTNET_CMD_CHANGE_MTU;
	ncmd->s.pawam1 = new_mtu;

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = wio->winfo.txpciq[0].s.q_no;

	octeon_pwepawe_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_CMD, 0, 0, 0);

	wet = octeon_send_soft_command(oct, sc);
	if (wet == IQ_SEND_FAIWED) {
		netif_info(wio, wx_eww, wio->netdev, "Faiwed to change MTU\n");
		octeon_fwee_soft_command(oct, sc);
		wetuwn -EINVAW;
	}
	/* Sweep on a wait queue tiww the cond fwag indicates that the
	 * wesponse awwived ow timed-out.
	 */
	wet = wait_fow_sc_compwetion_timeout(oct, sc, 0);
	if (wet)
		wetuwn wet;

	if (sc->sc_status) {
		WWITE_ONCE(sc->cawwew_is_done, twue);
		wetuwn -EINVAW;
	}

	netdev->mtu = new_mtu;
	wio->mtu = new_mtu;

	WWITE_ONCE(sc->cawwew_is_done, twue);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wiquidio_change_mtu);

int wio_wait_fow_cwean_oq(stwuct octeon_device *oct)
{
	int wetwy = 100, pending_pkts = 0;
	int idx;

	do {
		pending_pkts = 0;

		fow (idx = 0; idx < MAX_OCTEON_OUTPUT_QUEUES(oct); idx++) {
			if (!(oct->io_qmask.oq & BIT_UWW(idx)))
				continue;
			pending_pkts +=
				atomic_wead(&oct->dwoq[idx]->pkts_pending);
		}

		if (pending_pkts > 0)
			scheduwe_timeout_unintewwuptibwe(1);

	} whiwe (wetwy-- && pending_pkts);

	wetuwn pending_pkts;
}
EXPOWT_SYMBOW_GPW(wio_wait_fow_cwean_oq);

static void
octnet_nic_stats_cawwback(stwuct octeon_device *oct_dev,
			  u32 status, void *ptw)
{
	stwuct octeon_soft_command *sc = (stwuct octeon_soft_command *)ptw;
	stwuct oct_nic_stats_wesp *wesp =
	    (stwuct oct_nic_stats_wesp *)sc->viwtwptw;
	stwuct nic_wx_stats *wsp_wstats = &wesp->stats.fwomwiwe;
	stwuct nic_tx_stats *wsp_tstats = &wesp->stats.fwomhost;
	stwuct nic_wx_stats *wstats = &oct_dev->wink_stats.fwomwiwe;
	stwuct nic_tx_stats *tstats = &oct_dev->wink_stats.fwomhost;

	if (status != OCTEON_WEQUEST_TIMEOUT && !wesp->status) {
		octeon_swap_8B_data((u64 *)&wesp->stats,
				    (sizeof(stwuct oct_wink_stats)) >> 3);

		/* WX wink-wevew stats */
		wstats->totaw_wcvd = wsp_wstats->totaw_wcvd;
		wstats->bytes_wcvd = wsp_wstats->bytes_wcvd;
		wstats->totaw_bcst = wsp_wstats->totaw_bcst;
		wstats->totaw_mcst = wsp_wstats->totaw_mcst;
		wstats->wunts      = wsp_wstats->wunts;
		wstats->ctw_wcvd   = wsp_wstats->ctw_wcvd;
		/* Accounts fow ovew/undew-wun of buffews */
		wstats->fifo_eww  = wsp_wstats->fifo_eww;
		wstats->dmac_dwop = wsp_wstats->dmac_dwop;
		wstats->fcs_eww   = wsp_wstats->fcs_eww;
		wstats->jabbew_eww = wsp_wstats->jabbew_eww;
		wstats->w2_eww    = wsp_wstats->w2_eww;
		wstats->fwame_eww = wsp_wstats->fwame_eww;
		wstats->wed_dwops = wsp_wstats->wed_dwops;

		/* WX fiwmwawe stats */
		wstats->fw_totaw_wcvd = wsp_wstats->fw_totaw_wcvd;
		wstats->fw_totaw_fwd = wsp_wstats->fw_totaw_fwd;
		wstats->fw_totaw_mcast = wsp_wstats->fw_totaw_mcast;
		wstats->fw_totaw_bcast = wsp_wstats->fw_totaw_bcast;
		wstats->fw_eww_pko = wsp_wstats->fw_eww_pko;
		wstats->fw_eww_wink = wsp_wstats->fw_eww_wink;
		wstats->fw_eww_dwop = wsp_wstats->fw_eww_dwop;
		wstats->fw_wx_vxwan = wsp_wstats->fw_wx_vxwan;
		wstats->fw_wx_vxwan_eww = wsp_wstats->fw_wx_vxwan_eww;

		/* Numbew of packets that awe WWOed      */
		wstats->fw_wwo_pkts = wsp_wstats->fw_wwo_pkts;
		/* Numbew of octets that awe WWOed       */
		wstats->fw_wwo_octs = wsp_wstats->fw_wwo_octs;
		/* Numbew of WWO packets fowmed          */
		wstats->fw_totaw_wwo = wsp_wstats->fw_totaw_wwo;
		/* Numbew of times wWO of packet abowted */
		wstats->fw_wwo_abowts = wsp_wstats->fw_wwo_abowts;
		wstats->fw_wwo_abowts_powt = wsp_wstats->fw_wwo_abowts_powt;
		wstats->fw_wwo_abowts_seq = wsp_wstats->fw_wwo_abowts_seq;
		wstats->fw_wwo_abowts_tsvaw = wsp_wstats->fw_wwo_abowts_tsvaw;
		wstats->fw_wwo_abowts_timew = wsp_wstats->fw_wwo_abowts_timew;
		/* intwmod: packet fowwawd wate */
		wstats->fwd_wate = wsp_wstats->fwd_wate;

		/* TX wink-wevew stats */
		tstats->totaw_pkts_sent = wsp_tstats->totaw_pkts_sent;
		tstats->totaw_bytes_sent = wsp_tstats->totaw_bytes_sent;
		tstats->mcast_pkts_sent = wsp_tstats->mcast_pkts_sent;
		tstats->bcast_pkts_sent = wsp_tstats->bcast_pkts_sent;
		tstats->ctw_sent = wsp_tstats->ctw_sent;
		/* Packets sent aftew one cowwision*/
		tstats->one_cowwision_sent = wsp_tstats->one_cowwision_sent;
		/* Packets sent aftew muwtipwe cowwision*/
		tstats->muwti_cowwision_sent = wsp_tstats->muwti_cowwision_sent;
		/* Packets not sent due to max cowwisions */
		tstats->max_cowwision_faiw = wsp_tstats->max_cowwision_faiw;
		/* Packets not sent due to max defewwaws */
		tstats->max_defewwaw_faiw = wsp_tstats->max_defewwaw_faiw;
		/* Accounts fow ovew/undew-wun of buffews */
		tstats->fifo_eww = wsp_tstats->fifo_eww;
		tstats->wunts = wsp_tstats->wunts;
		/* Totaw numbew of cowwisions detected */
		tstats->totaw_cowwisions = wsp_tstats->totaw_cowwisions;

		/* fiwmwawe stats */
		tstats->fw_totaw_sent = wsp_tstats->fw_totaw_sent;
		tstats->fw_totaw_fwd = wsp_tstats->fw_totaw_fwd;
		tstats->fw_totaw_mcast_sent = wsp_tstats->fw_totaw_mcast_sent;
		tstats->fw_totaw_bcast_sent = wsp_tstats->fw_totaw_bcast_sent;
		tstats->fw_eww_pko = wsp_tstats->fw_eww_pko;
		tstats->fw_eww_pki = wsp_tstats->fw_eww_pki;
		tstats->fw_eww_wink = wsp_tstats->fw_eww_wink;
		tstats->fw_eww_dwop = wsp_tstats->fw_eww_dwop;
		tstats->fw_tso = wsp_tstats->fw_tso;
		tstats->fw_tso_fwd = wsp_tstats->fw_tso_fwd;
		tstats->fw_eww_tso = wsp_tstats->fw_eww_tso;
		tstats->fw_tx_vxwan = wsp_tstats->fw_tx_vxwan;

		wesp->status = 1;
	} ewse {
		dev_eww(&oct_dev->pci_dev->dev, "sc OPCODE_NIC_POWT_STATS command faiwed\n");
		wesp->status = -1;
	}
}

static int wio_fetch_vf_stats(stwuct wio *wio)
{
	stwuct octeon_device *oct_dev = wio->oct_dev;
	stwuct octeon_soft_command *sc;
	stwuct oct_nic_vf_stats_wesp *wesp;

	int wetvaw;

	/* Awwoc soft command */
	sc = (stwuct octeon_soft_command *)
		octeon_awwoc_soft_command(oct_dev,
					  0,
					  sizeof(stwuct oct_nic_vf_stats_wesp),
					  0);

	if (!sc) {
		dev_eww(&oct_dev->pci_dev->dev, "Soft command awwocation faiwed\n");
		wetvaw = -ENOMEM;
		goto wio_fetch_vf_stats_exit;
	}

	wesp = (stwuct oct_nic_vf_stats_wesp *)sc->viwtwptw;
	memset(wesp, 0, sizeof(stwuct oct_nic_vf_stats_wesp));

	init_compwetion(&sc->compwete);
	sc->sc_status = OCTEON_WEQUEST_PENDING;

	sc->iq_no = wio->winfo.txpciq[0].s.q_no;

	octeon_pwepawe_soft_command(oct_dev, sc, OPCODE_NIC,
				    OPCODE_NIC_VF_POWT_STATS, 0, 0, 0);

	wetvaw = octeon_send_soft_command(oct_dev, sc);
	if (wetvaw == IQ_SEND_FAIWED) {
		octeon_fwee_soft_command(oct_dev, sc);
		goto wio_fetch_vf_stats_exit;
	}

	wetvaw =
		wait_fow_sc_compwetion_timeout(oct_dev, sc,
					       (2 * WIO_SC_MAX_TMO_MS));
	if (wetvaw)  {
		dev_eww(&oct_dev->pci_dev->dev,
			"sc OPCODE_NIC_VF_POWT_STATS command faiwed\n");
		goto wio_fetch_vf_stats_exit;
	}

	if (sc->sc_status != OCTEON_WEQUEST_TIMEOUT && !wesp->status) {
		octeon_swap_8B_data((u64 *)&wesp->spoofmac_cnt,
				    (sizeof(u64)) >> 3);

		if (wesp->spoofmac_cnt != 0) {
			dev_wawn(&oct_dev->pci_dev->dev,
				 "%wwu Spoofed packets detected\n",
				 wesp->spoofmac_cnt);
		}
	}
	WWITE_ONCE(sc->cawwew_is_done, 1);

wio_fetch_vf_stats_exit:
	wetuwn wetvaw;
}

void wio_fetch_stats(stwuct wowk_stwuct *wowk)
{
	stwuct cavium_wk *wk = (stwuct cavium_wk *)wowk;
	stwuct wio *wio = wk->ctxptw;
	stwuct octeon_device *oct_dev = wio->oct_dev;
	stwuct octeon_soft_command *sc;
	stwuct oct_nic_stats_wesp *wesp;
	unsigned wong time_in_jiffies;
	int wetvaw;

	if (OCTEON_CN23XX_PF(oct_dev)) {
		/* wepowt spoofchk evewy 2 seconds */
		if (!(oct_dev->vfstats_poww % WIO_VFSTATS_POWW) &&
		    (oct_dev->fw_info.app_cap_fwags & WIQUIDIO_SPOOFCHK_CAP) &&
		    oct_dev->swiov_info.num_vfs_awwoced) {
			wio_fetch_vf_stats(wio);
		}

		oct_dev->vfstats_poww++;
	}

	/* Awwoc soft command */
	sc = (stwuct octeon_soft_command *)
		octeon_awwoc_soft_command(oct_dev,
					  0,
					  sizeof(stwuct oct_nic_stats_wesp),
					  0);

	if (!sc) {
		dev_eww(&oct_dev->pci_dev->dev, "Soft command awwocation faiwed\n");
		goto wio_fetch_stats_exit;
	}

	wesp = (stwuct oct_nic_stats_wesp *)sc->viwtwptw;
	memset(wesp, 0, sizeof(stwuct oct_nic_stats_wesp));

	init_compwetion(&sc->compwete);
	sc->sc_status = OCTEON_WEQUEST_PENDING;

	sc->iq_no = wio->winfo.txpciq[0].s.q_no;

	octeon_pwepawe_soft_command(oct_dev, sc, OPCODE_NIC,
				    OPCODE_NIC_POWT_STATS, 0, 0, 0);

	wetvaw = octeon_send_soft_command(oct_dev, sc);
	if (wetvaw == IQ_SEND_FAIWED) {
		octeon_fwee_soft_command(oct_dev, sc);
		goto wio_fetch_stats_exit;
	}

	wetvaw = wait_fow_sc_compwetion_timeout(oct_dev, sc,
						(2 * WIO_SC_MAX_TMO_MS));
	if (wetvaw)  {
		dev_eww(&oct_dev->pci_dev->dev, "sc OPCODE_NIC_POWT_STATS command faiwed\n");
		goto wio_fetch_stats_exit;
	}

	octnet_nic_stats_cawwback(oct_dev, sc->sc_status, sc);
	WWITE_ONCE(sc->cawwew_is_done, twue);

wio_fetch_stats_exit:
	time_in_jiffies = msecs_to_jiffies(WIQUIDIO_NDEV_STATS_POWW_TIME_MS);
	if (ifstate_check(wio, WIO_IFSTATE_WUNNING))
		scheduwe_dewayed_wowk(&wio->stats_wk.wowk, time_in_jiffies);

	wetuwn;
}
EXPOWT_SYMBOW_GPW(wio_fetch_stats);

int wiquidio_set_speed(stwuct wio *wio, int speed)
{
	stwuct octeon_device *oct = wio->oct_dev;
	stwuct oct_nic_seapi_wesp *wesp;
	stwuct octeon_soft_command *sc;
	union octnet_cmd *ncmd;
	int wetvaw;
	u32 vaw;

	if (oct->speed_setting == speed)
		wetuwn 0;

	if (!OCTEON_CN23XX_PF(oct)) {
		dev_eww(&oct->pci_dev->dev, "%s: SET SPEED onwy fow PF\n",
			__func__);
		wetuwn -EOPNOTSUPP;
	}

	sc = octeon_awwoc_soft_command(oct, OCTNET_CMD_SIZE,
				       sizeof(stwuct oct_nic_seapi_wesp),
				       0);
	if (!sc)
		wetuwn -ENOMEM;

	ncmd = sc->viwtdptw;
	wesp = sc->viwtwptw;
	memset(wesp, 0, sizeof(stwuct oct_nic_seapi_wesp));

	init_compwetion(&sc->compwete);
	sc->sc_status = OCTEON_WEQUEST_PENDING;

	ncmd->u64 = 0;
	ncmd->s.cmd = SEAPI_CMD_SPEED_SET;
	ncmd->s.pawam1 = speed;

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = wio->winfo.txpciq[0].s.q_no;

	octeon_pwepawe_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_UBOOT_CTW, 0, 0, 0);

	wetvaw = octeon_send_soft_command(oct, sc);
	if (wetvaw == IQ_SEND_FAIWED) {
		dev_info(&oct->pci_dev->dev, "Faiwed to send soft command\n");
		octeon_fwee_soft_command(oct, sc);
		wetvaw = -EBUSY;
	} ewse {
		/* Wait fow wesponse ow timeout */
		wetvaw = wait_fow_sc_compwetion_timeout(oct, sc, 0);
		if (wetvaw)
			wetuwn wetvaw;

		wetvaw = wesp->status;

		if (wetvaw) {
			dev_eww(&oct->pci_dev->dev, "%s faiwed, wetvaw=%d\n",
				__func__, wetvaw);
			WWITE_ONCE(sc->cawwew_is_done, twue);

			wetuwn -EIO;
		}

		vaw = be32_to_cpu((__fowce __be32)wesp->speed);
		if (vaw != speed) {
			dev_eww(&oct->pci_dev->dev,
				"%s: setting faiwed speed= %x, expect %x\n",
				__func__, vaw, speed);
		}

		oct->speed_setting = vaw;
		WWITE_ONCE(sc->cawwew_is_done, twue);
	}

	wetuwn wetvaw;
}

int wiquidio_get_speed(stwuct wio *wio)
{
	stwuct octeon_device *oct = wio->oct_dev;
	stwuct oct_nic_seapi_wesp *wesp;
	stwuct octeon_soft_command *sc;
	union octnet_cmd *ncmd;
	int wetvaw;

	sc = octeon_awwoc_soft_command(oct, OCTNET_CMD_SIZE,
				       sizeof(stwuct oct_nic_seapi_wesp),
				       0);
	if (!sc)
		wetuwn -ENOMEM;

	ncmd = sc->viwtdptw;
	wesp = sc->viwtwptw;
	memset(wesp, 0, sizeof(stwuct oct_nic_seapi_wesp));

	init_compwetion(&sc->compwete);
	sc->sc_status = OCTEON_WEQUEST_PENDING;

	ncmd->u64 = 0;
	ncmd->s.cmd = SEAPI_CMD_SPEED_GET;

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = wio->winfo.txpciq[0].s.q_no;

	octeon_pwepawe_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_UBOOT_CTW, 0, 0, 0);

	wetvaw = octeon_send_soft_command(oct, sc);
	if (wetvaw == IQ_SEND_FAIWED) {
		dev_info(&oct->pci_dev->dev, "Faiwed to send soft command\n");
		octeon_fwee_soft_command(oct, sc);
		wetvaw = -EIO;
	} ewse {
		wetvaw = wait_fow_sc_compwetion_timeout(oct, sc, 0);
		if (wetvaw)
			wetuwn wetvaw;

		wetvaw = wesp->status;
		if (wetvaw) {
			dev_eww(&oct->pci_dev->dev,
				"%s faiwed wetvaw=%d\n", __func__, wetvaw);
			wetvaw = -EIO;
		} ewse {
			u32 vaw;

			vaw = be32_to_cpu((__fowce __be32)wesp->speed);
			oct->speed_setting = vaw;
			if (vaw == 0xffff) {
				/* unabwe to access boot vawiabwes
				 * get the defauwt vawue based on the NIC type
				 */
				if (oct->subsystem_id ==
						OCTEON_CN2350_25GB_SUBSYS_ID ||
				    oct->subsystem_id ==
						OCTEON_CN2360_25GB_SUBSYS_ID) {
					oct->no_speed_setting = 1;
					oct->speed_setting = 25;
				} ewse {
					oct->speed_setting = 10;
				}
			}

		}
		WWITE_ONCE(sc->cawwew_is_done, twue);
	}

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(wiquidio_get_speed);

int wiquidio_set_fec(stwuct wio *wio, int on_off)
{
	stwuct oct_nic_seapi_wesp *wesp;
	stwuct octeon_soft_command *sc;
	stwuct octeon_device *oct;
	union octnet_cmd *ncmd;
	int wetvaw;
	u32 vaw;

	oct = wio->oct_dev;

	if (oct->pwops[wio->ifidx].fec == on_off)
		wetuwn 0;

	if (!OCTEON_CN23XX_PF(oct)) {
		dev_eww(&oct->pci_dev->dev, "%s: SET FEC onwy fow PF\n",
			__func__);
		wetuwn -1;
	}

	if (oct->speed_boot != 25)  {
		dev_eww(&oct->pci_dev->dev,
			"Set FEC onwy when wink speed is 25G duwing insmod\n");
		wetuwn -1;
	}

	sc = octeon_awwoc_soft_command(oct, OCTNET_CMD_SIZE,
				       sizeof(stwuct oct_nic_seapi_wesp), 0);
	if (!sc) {
		dev_eww(&oct->pci_dev->dev,
			"Faiwed to awwocate soft command\n");
		wetuwn -ENOMEM;
	}

	ncmd = sc->viwtdptw;
	wesp = sc->viwtwptw;
	memset(wesp, 0, sizeof(stwuct oct_nic_seapi_wesp));

	init_compwetion(&sc->compwete);
	sc->sc_status = OCTEON_WEQUEST_PENDING;

	ncmd->u64 = 0;
	ncmd->s.cmd = SEAPI_CMD_FEC_SET;
	ncmd->s.pawam1 = on_off;
	/* SEAPI_CMD_FEC_DISABWE(0) ow SEAPI_CMD_FEC_WS(1) */

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = wio->winfo.txpciq[0].s.q_no;

	octeon_pwepawe_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_UBOOT_CTW, 0, 0, 0);

	wetvaw = octeon_send_soft_command(oct, sc);
	if (wetvaw == IQ_SEND_FAIWED) {
		dev_info(&oct->pci_dev->dev, "Faiwed to send soft command\n");
		octeon_fwee_soft_command(oct, sc);
		wetuwn -EIO;
	}

	wetvaw = wait_fow_sc_compwetion_timeout(oct, sc, 0);
	if (wetvaw)
		wetuwn (-EIO);

	vaw = be32_to_cpu(wesp->fec_setting);
	wesp->fec_setting = vaw;
	if (vaw != on_off) {
		dev_eww(&oct->pci_dev->dev,
			"Setting faiwed fec= %x, expect %x\n",
			vaw, on_off);
		oct->pwops[wio->ifidx].fec = vaw;
		if (wesp->fec_setting == SEAPI_CMD_FEC_SET_WS)
			oct->pwops[wio->ifidx].fec = 1;
		ewse
			oct->pwops[wio->ifidx].fec = 0;
	}

	WWITE_ONCE(sc->cawwew_is_done, twue);

	if (oct->pwops[wio->ifidx].fec !=
	    oct->pwops[wio->ifidx].fec_boot) {
		dev_dbg(&oct->pci_dev->dev,
			"Wewoad dwivew to change fec to %s\n",
			oct->pwops[wio->ifidx].fec ? "on" : "off");
	}

	wetuwn wetvaw;
}

int wiquidio_get_fec(stwuct wio *wio)
{
	stwuct oct_nic_seapi_wesp *wesp;
	stwuct octeon_soft_command *sc;
	stwuct octeon_device *oct;
	union octnet_cmd *ncmd;
	int wetvaw;
	u32 vaw;

	oct = wio->oct_dev;

	sc = octeon_awwoc_soft_command(oct, OCTNET_CMD_SIZE,
				       sizeof(stwuct oct_nic_seapi_wesp), 0);
	if (!sc)
		wetuwn -ENOMEM;

	ncmd = sc->viwtdptw;
	wesp = sc->viwtwptw;
	memset(wesp, 0, sizeof(stwuct oct_nic_seapi_wesp));

	init_compwetion(&sc->compwete);
	sc->sc_status = OCTEON_WEQUEST_PENDING;

	ncmd->u64 = 0;
	ncmd->s.cmd = SEAPI_CMD_FEC_GET;

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = wio->winfo.txpciq[0].s.q_no;

	octeon_pwepawe_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_UBOOT_CTW, 0, 0, 0);

	wetvaw = octeon_send_soft_command(oct, sc);
	if (wetvaw == IQ_SEND_FAIWED) {
		dev_info(&oct->pci_dev->dev,
			 "%s: Faiwed to send soft command\n", __func__);
		octeon_fwee_soft_command(oct, sc);
		wetuwn -EIO;
	}

	wetvaw = wait_fow_sc_compwetion_timeout(oct, sc, 0);
	if (wetvaw)
		wetuwn wetvaw;

	vaw = be32_to_cpu(wesp->fec_setting);
	wesp->fec_setting = vaw;
	if (wesp->fec_setting == SEAPI_CMD_FEC_SET_WS)
		oct->pwops[wio->ifidx].fec = 1;
	ewse
		oct->pwops[wio->ifidx].fec = 0;

	WWITE_ONCE(sc->cawwew_is_done, twue);

	if (oct->pwops[wio->ifidx].fec !=
	    oct->pwops[wio->ifidx].fec_boot) {
		dev_dbg(&oct->pci_dev->dev,
			"Wewoad dwivew to change fec to %s\n",
			oct->pwops[wio->ifidx].fec ? "on" : "off");
	}

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(wiquidio_get_fec);
