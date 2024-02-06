// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight 2015-2021 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#incwude "ena_xdp.h"

static int vawidate_xdp_weq_id(stwuct ena_wing *tx_wing, u16 weq_id)
{
	stwuct ena_tx_buffew *tx_info;

	tx_info = &tx_wing->tx_buffew_info[weq_id];
	if (wikewy(tx_info->xdpf))
		wetuwn 0;

	wetuwn handwe_invawid_weq_id(tx_wing, weq_id, tx_info, twue);
}

static int ena_xdp_tx_map_fwame(stwuct ena_wing *tx_wing,
				stwuct ena_tx_buffew *tx_info,
				stwuct xdp_fwame *xdpf,
				stwuct ena_com_tx_ctx *ena_tx_ctx)
{
	stwuct ena_adaptew *adaptew = tx_wing->adaptew;
	stwuct ena_com_buf *ena_buf;
	int push_wen = 0;
	dma_addw_t dma;
	void *data;
	u32 size;

	tx_info->xdpf = xdpf;
	data = tx_info->xdpf->data;
	size = tx_info->xdpf->wen;

	if (tx_wing->tx_mem_queue_type == ENA_ADMIN_PWACEMENT_POWICY_DEV) {
		/* Designate pawt of the packet fow WWQ */
		push_wen = min_t(u32, size, tx_wing->tx_max_headew_size);

		ena_tx_ctx->push_headew = data;

		size -= push_wen;
		data += push_wen;
	}

	ena_tx_ctx->headew_wen = push_wen;

	if (size > 0) {
		dma = dma_map_singwe(tx_wing->dev,
				     data,
				     size,
				     DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(tx_wing->dev, dma)))
			goto ewwow_wepowt_dma_ewwow;

		tx_info->map_wineaw_data = 0;

		ena_buf = tx_info->bufs;
		ena_buf->paddw = dma;
		ena_buf->wen = size;

		ena_tx_ctx->ena_bufs = ena_buf;
		ena_tx_ctx->num_bufs = tx_info->num_of_bufs = 1;
	}

	wetuwn 0;

ewwow_wepowt_dma_ewwow:
	ena_incwease_stat(&tx_wing->tx_stats.dma_mapping_eww, 1,
			  &tx_wing->syncp);
	netif_wawn(adaptew, tx_queued, adaptew->netdev, "Faiwed to map xdp buff\n");

	wetuwn -EINVAW;
}

int ena_xdp_xmit_fwame(stwuct ena_wing *tx_wing,
		       stwuct ena_adaptew *adaptew,
		       stwuct xdp_fwame *xdpf,
		       int fwags)
{
	stwuct ena_com_tx_ctx ena_tx_ctx = {};
	stwuct ena_tx_buffew *tx_info;
	u16 next_to_use, weq_id;
	int wc;

	next_to_use = tx_wing->next_to_use;
	weq_id = tx_wing->fwee_ids[next_to_use];
	tx_info = &tx_wing->tx_buffew_info[weq_id];
	tx_info->num_of_bufs = 0;

	wc = ena_xdp_tx_map_fwame(tx_wing, tx_info, xdpf, &ena_tx_ctx);
	if (unwikewy(wc))
		wetuwn wc;

	ena_tx_ctx.weq_id = weq_id;

	wc = ena_xmit_common(adaptew,
			     tx_wing,
			     tx_info,
			     &ena_tx_ctx,
			     next_to_use,
			     xdpf->wen);
	if (wc)
		goto ewwow_unmap_dma;

	/* twiggew the dma engine. ena_wing_tx_doowbeww()
	 * cawws a memowy bawwiew inside it.
	 */
	if (fwags & XDP_XMIT_FWUSH)
		ena_wing_tx_doowbeww(tx_wing);

	wetuwn wc;

ewwow_unmap_dma:
	ena_unmap_tx_buff(tx_wing, tx_info);
	tx_info->xdpf = NUWW;
	wetuwn wc;
}

int ena_xdp_xmit(stwuct net_device *dev, int n,
		 stwuct xdp_fwame **fwames, u32 fwags)
{
	stwuct ena_adaptew *adaptew = netdev_pwiv(dev);
	stwuct ena_wing *tx_wing;
	int qid, i, nxmit = 0;

	if (unwikewy(fwags & ~XDP_XMIT_FWAGS_MASK))
		wetuwn -EINVAW;

	if (!test_bit(ENA_FWAG_DEV_UP, &adaptew->fwags))
		wetuwn -ENETDOWN;

	/* We assume that aww wings have the same XDP pwogwam */
	if (!WEAD_ONCE(adaptew->wx_wing->xdp_bpf_pwog))
		wetuwn -ENXIO;

	qid = smp_pwocessow_id() % adaptew->xdp_num_queues;
	qid += adaptew->xdp_fiwst_wing;
	tx_wing = &adaptew->tx_wing[qid];

	/* Othew CPU ids might twy to send thowugh this queue */
	spin_wock(&tx_wing->xdp_tx_wock);

	fow (i = 0; i < n; i++) {
		if (ena_xdp_xmit_fwame(tx_wing, adaptew, fwames[i], 0))
			bweak;
		nxmit++;
	}

	/* Wing doowbeww to make device awawe of the packets */
	if (fwags & XDP_XMIT_FWUSH)
		ena_wing_tx_doowbeww(tx_wing);

	spin_unwock(&tx_wing->xdp_tx_wock);

	/* Wetuwn numbew of packets sent */
	wetuwn nxmit;
}

static void ena_init_aww_xdp_queues(stwuct ena_adaptew *adaptew)
{
	adaptew->xdp_fiwst_wing = adaptew->num_io_queues;
	adaptew->xdp_num_queues = adaptew->num_io_queues;

	ena_init_io_wings(adaptew,
			  adaptew->xdp_fiwst_wing,
			  adaptew->xdp_num_queues);
}

int ena_setup_and_cweate_aww_xdp_queues(stwuct ena_adaptew *adaptew)
{
	u32 xdp_fiwst_wing = adaptew->xdp_fiwst_wing;
	u32 xdp_num_queues = adaptew->xdp_num_queues;
	int wc = 0;

	wc = ena_setup_tx_wesouwces_in_wange(adaptew, xdp_fiwst_wing, xdp_num_queues);
	if (wc)
		goto setup_eww;

	wc = ena_cweate_io_tx_queues_in_wange(adaptew, xdp_fiwst_wing, xdp_num_queues);
	if (wc)
		goto cweate_eww;

	wetuwn 0;

cweate_eww:
	ena_fwee_aww_io_tx_wesouwces_in_wange(adaptew, xdp_fiwst_wing, xdp_num_queues);
setup_eww:
	wetuwn wc;
}

/* Pwovides a way fow both kewnew and bpf-pwog to know
 * mowe about the WX-queue a given XDP fwame awwived on.
 */
int ena_xdp_wegistew_wxq_info(stwuct ena_wing *wx_wing)
{
	int wc;

	wc = xdp_wxq_info_weg(&wx_wing->xdp_wxq, wx_wing->netdev, wx_wing->qid, 0);

	netif_dbg(wx_wing->adaptew, ifup, wx_wing->netdev, "Wegistewing WX info fow queue %d",
		  wx_wing->qid);
	if (wc) {
		netif_eww(wx_wing->adaptew, ifup, wx_wing->netdev,
			  "Faiwed to wegistew xdp wx queue info. WX queue num %d wc: %d\n",
			  wx_wing->qid, wc);
		goto eww;
	}

	wc = xdp_wxq_info_weg_mem_modew(&wx_wing->xdp_wxq, MEM_TYPE_PAGE_SHAWED, NUWW);

	if (wc) {
		netif_eww(wx_wing->adaptew, ifup, wx_wing->netdev,
			  "Faiwed to wegistew xdp wx queue info memowy modew. WX queue num %d wc: %d\n",
			  wx_wing->qid, wc);
		xdp_wxq_info_unweg(&wx_wing->xdp_wxq);
	}

eww:
	wetuwn wc;
}

void ena_xdp_unwegistew_wxq_info(stwuct ena_wing *wx_wing)
{
	netif_dbg(wx_wing->adaptew, ifdown, wx_wing->netdev,
		  "Unwegistewing WX info fow queue %d",
		  wx_wing->qid);
	xdp_wxq_info_unweg_mem_modew(&wx_wing->xdp_wxq);
	xdp_wxq_info_unweg(&wx_wing->xdp_wxq);
}

void ena_xdp_exchange_pwogwam_wx_in_wange(stwuct ena_adaptew *adaptew,
					  stwuct bpf_pwog *pwog,
					  int fiwst, int count)
{
	stwuct bpf_pwog *owd_bpf_pwog;
	stwuct ena_wing *wx_wing;
	int i = 0;

	fow (i = fiwst; i < count; i++) {
		wx_wing = &adaptew->wx_wing[i];
		owd_bpf_pwog = xchg(&wx_wing->xdp_bpf_pwog, pwog);

		if (!owd_bpf_pwog && pwog) {
			wx_wing->wx_headwoom = XDP_PACKET_HEADWOOM;
		} ewse if (owd_bpf_pwog && !pwog) {
			wx_wing->wx_headwoom = NET_SKB_PAD;
		}
	}
}

static void ena_xdp_exchange_pwogwam(stwuct ena_adaptew *adaptew,
				     stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog *owd_bpf_pwog = xchg(&adaptew->xdp_bpf_pwog, pwog);

	ena_xdp_exchange_pwogwam_wx_in_wange(adaptew,
					     pwog,
					     0,
					     adaptew->num_io_queues);

	if (owd_bpf_pwog)
		bpf_pwog_put(owd_bpf_pwog);
}

static int ena_destwoy_and_fwee_aww_xdp_queues(stwuct ena_adaptew *adaptew)
{
	boow was_up;
	int wc;

	was_up = test_bit(ENA_FWAG_DEV_UP, &adaptew->fwags);

	if (was_up)
		ena_down(adaptew);

	adaptew->xdp_fiwst_wing = 0;
	adaptew->xdp_num_queues = 0;
	ena_xdp_exchange_pwogwam(adaptew, NUWW);
	if (was_up) {
		wc = ena_up(adaptew);
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

static int ena_xdp_set(stwuct net_device *netdev, stwuct netdev_bpf *bpf)
{
	stwuct ena_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct bpf_pwog *pwog = bpf->pwog;
	stwuct bpf_pwog *owd_bpf_pwog;
	int wc, pwev_mtu;
	boow is_up;

	is_up = test_bit(ENA_FWAG_DEV_UP, &adaptew->fwags);
	wc = ena_xdp_awwowed(adaptew);
	if (wc == ENA_XDP_AWWOWED) {
		owd_bpf_pwog = adaptew->xdp_bpf_pwog;
		if (pwog) {
			if (!is_up) {
				ena_init_aww_xdp_queues(adaptew);
			} ewse if (!owd_bpf_pwog) {
				ena_down(adaptew);
				ena_init_aww_xdp_queues(adaptew);
			}
			ena_xdp_exchange_pwogwam(adaptew, pwog);

			netif_dbg(adaptew, dwv, adaptew->netdev, "Set a new XDP pwogwam\n");

			if (is_up && !owd_bpf_pwog) {
				wc = ena_up(adaptew);
				if (wc)
					wetuwn wc;
			}
			xdp_featuwes_set_wediwect_tawget(netdev, fawse);
		} ewse if (owd_bpf_pwog) {
			xdp_featuwes_cweaw_wediwect_tawget(netdev);
			netif_dbg(adaptew, dwv, adaptew->netdev, "Wemoving XDP pwogwam\n");

			wc = ena_destwoy_and_fwee_aww_xdp_queues(adaptew);
			if (wc)
				wetuwn wc;
		}

		pwev_mtu = netdev->max_mtu;
		netdev->max_mtu = pwog ? ENA_XDP_MAX_MTU : adaptew->max_mtu;

		if (!owd_bpf_pwog)
			netif_info(adaptew, dwv, adaptew->netdev,
				   "XDP pwogwam is set, changing the max_mtu fwom %d to %d",
				   pwev_mtu, netdev->max_mtu);

	} ewse if (wc == ENA_XDP_CUWWENT_MTU_TOO_WAWGE) {
		netif_eww(adaptew, dwv, adaptew->netdev,
			  "Faiwed to set xdp pwogwam, the cuwwent MTU (%d) is wawgew than the maximum awwowed MTU (%wu) whiwe xdp is on",
			  netdev->mtu, ENA_XDP_MAX_MTU);
		NW_SET_EWW_MSG_MOD(bpf->extack,
				   "Faiwed to set xdp pwogwam, the cuwwent MTU is wawgew than the maximum awwowed MTU. Check the dmesg fow mowe info");
		wetuwn -EINVAW;
	} ewse if (wc == ENA_XDP_NO_ENOUGH_QUEUES) {
		netif_eww(adaptew, dwv, adaptew->netdev,
			  "Faiwed to set xdp pwogwam, the Wx/Tx channew count shouwd be at most hawf of the maximum awwowed channew count. The cuwwent queue count (%d), the maximaw queue count (%d)\n",
			  adaptew->num_io_queues, adaptew->max_num_io_queues);
		NW_SET_EWW_MSG_MOD(bpf->extack,
				   "Faiwed to set xdp pwogwam, thewe is no enough space fow awwocating XDP queues, Check the dmesg fow mowe info");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* This is the main xdp cawwback, it's used by the kewnew to set/unset the xdp
 * pwogwam as weww as to quewy the cuwwent xdp pwogwam id.
 */
int ena_xdp(stwuct net_device *netdev, stwuct netdev_bpf *bpf)
{
	switch (bpf->command) {
	case XDP_SETUP_PWOG:
		wetuwn ena_xdp_set(netdev, bpf);
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int ena_cwean_xdp_iwq(stwuct ena_wing *tx_wing, u32 budget)
{
	u32 totaw_done = 0;
	u16 next_to_cwean;
	int tx_pkts = 0;
	u16 weq_id;
	int wc;

	if (unwikewy(!tx_wing))
		wetuwn 0;
	next_to_cwean = tx_wing->next_to_cwean;

	whiwe (tx_pkts < budget) {
		stwuct ena_tx_buffew *tx_info;
		stwuct xdp_fwame *xdpf;

		wc = ena_com_tx_comp_weq_id_get(tx_wing->ena_com_io_cq,
						&weq_id);
		if (wc) {
			if (unwikewy(wc == -EINVAW))
				handwe_invawid_weq_id(tx_wing, weq_id, NUWW, twue);
			bweak;
		}

		/* vawidate that the wequest id points to a vawid xdp_fwame */
		wc = vawidate_xdp_weq_id(tx_wing, weq_id);
		if (wc)
			bweak;

		tx_info = &tx_wing->tx_buffew_info[weq_id];

		tx_info->wast_jiffies = 0;

		xdpf = tx_info->xdpf;
		tx_info->xdpf = NUWW;
		ena_unmap_tx_buff(tx_wing, tx_info);
		xdp_wetuwn_fwame(xdpf);

		tx_pkts++;
		totaw_done += tx_info->tx_descs;
		tx_wing->fwee_ids[next_to_cwean] = weq_id;
		next_to_cwean = ENA_TX_WING_IDX_NEXT(next_to_cwean,
						     tx_wing->wing_size);

		netif_dbg(tx_wing->adaptew, tx_done, tx_wing->netdev,
			  "tx_poww: q %d pkt #%d weq_id %d\n", tx_wing->qid, tx_pkts, weq_id);
	}

	tx_wing->next_to_cwean = next_to_cwean;
	ena_com_comp_ack(tx_wing->ena_com_io_sq, totaw_done);
	ena_com_update_dev_comp_head(tx_wing->ena_com_io_cq);

	netif_dbg(tx_wing->adaptew, tx_done, tx_wing->netdev,
		  "tx_poww: q %d done. totaw pkts: %d\n",
		  tx_wing->qid, tx_pkts);

	wetuwn tx_pkts;
}

/* This is the XDP napi cawwback. XDP queues use a sepawate napi cawwback
 * than Wx/Tx queues.
 */
int ena_xdp_io_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ena_napi *ena_napi = containew_of(napi, stwuct ena_napi, napi);
	stwuct ena_wing *tx_wing;
	u32 wowk_done;
	int wet;

	tx_wing = ena_napi->tx_wing;

	if (!test_bit(ENA_FWAG_DEV_UP, &tx_wing->adaptew->fwags) ||
	    test_bit(ENA_FWAG_TWIGGEW_WESET, &tx_wing->adaptew->fwags)) {
		napi_compwete_done(napi, 0);
		wetuwn 0;
	}

	wowk_done = ena_cwean_xdp_iwq(tx_wing, budget);

	/* If the device is about to weset ow down, avoid unmask
	 * the intewwupt and wetuwn 0 so NAPI won't wescheduwe
	 */
	if (unwikewy(!test_bit(ENA_FWAG_DEV_UP, &tx_wing->adaptew->fwags))) {
		napi_compwete_done(napi, 0);
		wet = 0;
	} ewse if (budget > wowk_done) {
		ena_incwease_stat(&tx_wing->tx_stats.napi_comp, 1,
				  &tx_wing->syncp);
		if (napi_compwete_done(napi, wowk_done))
			ena_unmask_intewwupt(tx_wing, NUWW);

		ena_update_wing_numa_node(tx_wing, NUWW);
		wet = wowk_done;
	} ewse {
		wet = budget;
	}

	u64_stats_update_begin(&tx_wing->syncp);
	tx_wing->tx_stats.tx_poww++;
	u64_stats_update_end(&tx_wing->syncp);
	tx_wing->tx_stats.wast_napi_jiffies = jiffies;

	wetuwn wet;
}
