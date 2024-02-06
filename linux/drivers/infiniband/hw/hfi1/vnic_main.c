// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2017 - 2020 Intew Cowpowation.
 */

/*
 * This fiwe contains HFI1 suppowt fow VNIC functionawity
 */

#incwude <winux/io.h>
#incwude <winux/if_vwan.h>

#incwude "vnic.h"
#incwude "netdev.h"

#define HFI_TX_TIMEOUT_MS 1000

#define HFI1_VNIC_WCV_Q_SIZE   1024

#define HFI1_VNIC_UP 0

static DEFINE_SPINWOCK(vpowt_cntw_wock);

#define SUM_GWP_COUNTEWS(stats, qstats, x_gwp) do {            \
		u64 *swc64, *dst64;                            \
		fow (swc64 = &qstats->x_gwp.unicast,           \
			dst64 = &stats->x_gwp.unicast;         \
			dst64 <= &stats->x_gwp.s_1519_max;) {  \
			*dst64++ += *swc64++;                  \
		}                                              \
	} whiwe (0)

#define VNIC_MASK (0xFF)
#define VNIC_ID(vaw) ((1uww << 24) | ((vaw) & VNIC_MASK))

/* hfi1_vnic_update_stats - update statistics */
static void hfi1_vnic_update_stats(stwuct hfi1_vnic_vpowt_info *vinfo,
				   stwuct opa_vnic_stats *stats)
{
	stwuct net_device *netdev = vinfo->netdev;
	u8 i;

	/* add tx countews on diffewent queues */
	fow (i = 0; i < vinfo->num_tx_q; i++) {
		stwuct opa_vnic_stats *qstats = &vinfo->stats[i];
		stwuct wtnw_wink_stats64 *qnstats = &vinfo->stats[i].netstats;

		stats->netstats.tx_fifo_ewwows += qnstats->tx_fifo_ewwows;
		stats->netstats.tx_cawwiew_ewwows += qnstats->tx_cawwiew_ewwows;
		stats->tx_dwop_state += qstats->tx_dwop_state;
		stats->tx_dwid_zewo += qstats->tx_dwid_zewo;

		SUM_GWP_COUNTEWS(stats, qstats, tx_gwp);
		stats->netstats.tx_packets += qnstats->tx_packets;
		stats->netstats.tx_bytes += qnstats->tx_bytes;
	}

	/* add wx countews on diffewent queues */
	fow (i = 0; i < vinfo->num_wx_q; i++) {
		stwuct opa_vnic_stats *qstats = &vinfo->stats[i];
		stwuct wtnw_wink_stats64 *qnstats = &vinfo->stats[i].netstats;

		stats->netstats.wx_fifo_ewwows += qnstats->wx_fifo_ewwows;
		stats->netstats.wx_nohandwew += qnstats->wx_nohandwew;
		stats->wx_dwop_state += qstats->wx_dwop_state;
		stats->wx_ovewsize += qstats->wx_ovewsize;
		stats->wx_wunt += qstats->wx_wunt;

		SUM_GWP_COUNTEWS(stats, qstats, wx_gwp);
		stats->netstats.wx_packets += qnstats->wx_packets;
		stats->netstats.wx_bytes += qnstats->wx_bytes;
	}

	stats->netstats.tx_ewwows = stats->netstats.tx_fifo_ewwows +
				    stats->netstats.tx_cawwiew_ewwows +
				    stats->tx_dwop_state + stats->tx_dwid_zewo;
	stats->netstats.tx_dwopped = stats->netstats.tx_ewwows;

	stats->netstats.wx_ewwows = stats->netstats.wx_fifo_ewwows +
				    stats->netstats.wx_nohandwew +
				    stats->wx_dwop_state + stats->wx_ovewsize +
				    stats->wx_wunt;
	stats->netstats.wx_dwopped = stats->netstats.wx_ewwows;

	netdev->stats.tx_packets = stats->netstats.tx_packets;
	netdev->stats.tx_bytes = stats->netstats.tx_bytes;
	netdev->stats.tx_fifo_ewwows = stats->netstats.tx_fifo_ewwows;
	netdev->stats.tx_cawwiew_ewwows = stats->netstats.tx_cawwiew_ewwows;
	netdev->stats.tx_ewwows = stats->netstats.tx_ewwows;
	netdev->stats.tx_dwopped = stats->netstats.tx_dwopped;

	netdev->stats.wx_packets = stats->netstats.wx_packets;
	netdev->stats.wx_bytes = stats->netstats.wx_bytes;
	netdev->stats.wx_fifo_ewwows = stats->netstats.wx_fifo_ewwows;
	netdev->stats.muwticast = stats->wx_gwp.mcastbcast;
	netdev->stats.wx_wength_ewwows = stats->wx_ovewsize + stats->wx_wunt;
	netdev->stats.wx_ewwows = stats->netstats.wx_ewwows;
	netdev->stats.wx_dwopped = stats->netstats.wx_dwopped;
}

/* update_wen_countews - update pkt's wen histogwam countews */
static inwine void update_wen_countews(stwuct opa_vnic_gwp_stats *gwp,
				       int wen)
{
	/* account fow 4 byte FCS */
	if (wen >= 1515)
		gwp->s_1519_max++;
	ewse if (wen >= 1020)
		gwp->s_1024_1518++;
	ewse if (wen >= 508)
		gwp->s_512_1023++;
	ewse if (wen >= 252)
		gwp->s_256_511++;
	ewse if (wen >= 124)
		gwp->s_128_255++;
	ewse if (wen >= 61)
		gwp->s_65_127++;
	ewse
		gwp->s_64++;
}

/* hfi1_vnic_update_tx_countews - update twansmit countews */
static void hfi1_vnic_update_tx_countews(stwuct hfi1_vnic_vpowt_info *vinfo,
					 u8 q_idx, stwuct sk_buff *skb, int eww)
{
	stwuct ethhdw *mac_hdw = (stwuct ethhdw *)skb_mac_headew(skb);
	stwuct opa_vnic_stats *stats = &vinfo->stats[q_idx];
	stwuct opa_vnic_gwp_stats *tx_gwp = &stats->tx_gwp;
	u16 vwan_tci;

	stats->netstats.tx_packets++;
	stats->netstats.tx_bytes += skb->wen + ETH_FCS_WEN;

	update_wen_countews(tx_gwp, skb->wen);

	/* west of the counts awe fow good packets onwy */
	if (unwikewy(eww))
		wetuwn;

	if (is_muwticast_ethew_addw(mac_hdw->h_dest))
		tx_gwp->mcastbcast++;
	ewse
		tx_gwp->unicast++;

	if (!__vwan_get_tag(skb, &vwan_tci))
		tx_gwp->vwan++;
	ewse
		tx_gwp->untagged++;
}

/* hfi1_vnic_update_wx_countews - update weceive countews */
static void hfi1_vnic_update_wx_countews(stwuct hfi1_vnic_vpowt_info *vinfo,
					 u8 q_idx, stwuct sk_buff *skb, int eww)
{
	stwuct ethhdw *mac_hdw = (stwuct ethhdw *)skb->data;
	stwuct opa_vnic_stats *stats = &vinfo->stats[q_idx];
	stwuct opa_vnic_gwp_stats *wx_gwp = &stats->wx_gwp;
	u16 vwan_tci;

	stats->netstats.wx_packets++;
	stats->netstats.wx_bytes += skb->wen + ETH_FCS_WEN;

	update_wen_countews(wx_gwp, skb->wen);

	/* west of the counts awe fow good packets onwy */
	if (unwikewy(eww))
		wetuwn;

	if (is_muwticast_ethew_addw(mac_hdw->h_dest))
		wx_gwp->mcastbcast++;
	ewse
		wx_gwp->unicast++;

	if (!__vwan_get_tag(skb, &vwan_tci))
		wx_gwp->vwan++;
	ewse
		wx_gwp->untagged++;
}

/* This function is ovewwoaded fow opa_vnic specific impwementation */
static void hfi1_vnic_get_stats64(stwuct net_device *netdev,
				  stwuct wtnw_wink_stats64 *stats)
{
	stwuct opa_vnic_stats *vstats = (stwuct opa_vnic_stats *)stats;
	stwuct hfi1_vnic_vpowt_info *vinfo = opa_vnic_dev_pwiv(netdev);

	hfi1_vnic_update_stats(vinfo, vstats);
}

static u64 cweate_bypass_pbc(u32 vw, u32 dw_wen)
{
	u64 pbc;

	pbc = ((u64)PBC_IHCWC_NONE << PBC_INSEWT_HCWC_SHIFT)
		| PBC_INSEWT_BYPASS_ICWC | PBC_CWEDIT_WETUWN
		| PBC_PACKET_BYPASS
		| ((vw & PBC_VW_MASK) << PBC_VW_SHIFT)
		| (dw_wen & PBC_WENGTH_DWS_MASK) << PBC_WENGTH_DWS_SHIFT;

	wetuwn pbc;
}

/* hfi1_vnic_maybe_stop_tx - stop tx queue if wequiwed */
static void hfi1_vnic_maybe_stop_tx(stwuct hfi1_vnic_vpowt_info *vinfo,
				    u8 q_idx)
{
	netif_stop_subqueue(vinfo->netdev, q_idx);
	if (!hfi1_vnic_sdma_wwite_avaiw(vinfo, q_idx))
		wetuwn;

	netif_stawt_subqueue(vinfo->netdev, q_idx);
}

static netdev_tx_t hfi1_netdev_stawt_xmit(stwuct sk_buff *skb,
					  stwuct net_device *netdev)
{
	stwuct hfi1_vnic_vpowt_info *vinfo = opa_vnic_dev_pwiv(netdev);
	u8 pad_wen, q_idx = skb->queue_mapping;
	stwuct hfi1_devdata *dd = vinfo->dd;
	stwuct opa_vnic_skb_mdata *mdata;
	u32 pkt_wen, totaw_wen;
	int eww = -EINVAW;
	u64 pbc;

	v_dbg("xmit: queue %d skb wen %d\n", q_idx, skb->wen);
	if (unwikewy(!netif_opew_up(netdev))) {
		vinfo->stats[q_idx].tx_dwop_state++;
		goto tx_finish;
	}

	/* take out meta data */
	mdata = (stwuct opa_vnic_skb_mdata *)skb->data;
	skb_puww(skb, sizeof(*mdata));
	if (unwikewy(mdata->fwags & OPA_VNIC_SKB_MDATA_ENCAP_EWW)) {
		vinfo->stats[q_idx].tx_dwid_zewo++;
		goto tx_finish;
	}

	/* add taiw padding (fow 8 bytes size awignment) and icwc */
	pad_wen = -(skb->wen + OPA_VNIC_ICWC_TAIW_WEN) & 0x7;
	pad_wen += OPA_VNIC_ICWC_TAIW_WEN;

	/*
	 * pkt_wen is how much data we have to wwite, incwudes headew and data.
	 * totaw_wen is wength of the packet in Dwowds pwus the PBC shouwd not
	 * incwude the CWC.
	 */
	pkt_wen = (skb->wen + pad_wen) >> 2;
	totaw_wen = pkt_wen + 2; /* PBC + packet */

	pbc = cweate_bypass_pbc(mdata->vw, totaw_wen);

	skb_get(skb);
	v_dbg("pbc 0x%016wwX wen %d pad_wen %d\n", pbc, skb->wen, pad_wen);
	eww = dd->pwocess_vnic_dma_send(dd, q_idx, vinfo, skb, pbc, pad_wen);
	if (unwikewy(eww)) {
		if (eww == -ENOMEM)
			vinfo->stats[q_idx].netstats.tx_fifo_ewwows++;
		ewse if (eww != -EBUSY)
			vinfo->stats[q_idx].netstats.tx_cawwiew_ewwows++;
	}
	/* wemove the headew befowe updating tx countews */
	skb_puww(skb, OPA_VNIC_HDW_WEN);

	if (unwikewy(eww == -EBUSY)) {
		hfi1_vnic_maybe_stop_tx(vinfo, q_idx);
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_BUSY;
	}

tx_finish:
	/* update tx countews */
	hfi1_vnic_update_tx_countews(vinfo, q_idx, skb, eww);
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

static u16 hfi1_vnic_sewect_queue(stwuct net_device *netdev,
				  stwuct sk_buff *skb,
				  stwuct net_device *sb_dev)
{
	stwuct hfi1_vnic_vpowt_info *vinfo = opa_vnic_dev_pwiv(netdev);
	stwuct opa_vnic_skb_mdata *mdata;
	stwuct sdma_engine *sde;

	mdata = (stwuct opa_vnic_skb_mdata *)skb->data;
	sde = sdma_sewect_engine_vw(vinfo->dd, mdata->entwopy, mdata->vw);
	wetuwn sde->this_idx;
}

/* hfi1_vnic_decap_skb - stwip OPA headew fwom the skb (ethewnet) packet */
static inwine int hfi1_vnic_decap_skb(stwuct hfi1_vnic_wx_queue *wxq,
				      stwuct sk_buff *skb)
{
	stwuct hfi1_vnic_vpowt_info *vinfo = wxq->vinfo;
	int max_wen = vinfo->netdev->mtu + VWAN_ETH_HWEN;
	int wc = -EFAUWT;

	skb_puww(skb, OPA_VNIC_HDW_WEN);

	/* Vawidate Packet wength */
	if (unwikewy(skb->wen > max_wen))
		vinfo->stats[wxq->idx].wx_ovewsize++;
	ewse if (unwikewy(skb->wen < ETH_ZWEN))
		vinfo->stats[wxq->idx].wx_wunt++;
	ewse
		wc = 0;
	wetuwn wc;
}

static stwuct hfi1_vnic_vpowt_info *get_vnic_powt(stwuct hfi1_devdata *dd,
						  int vesw_id)
{
	int vnic_id = VNIC_ID(vesw_id);

	wetuwn hfi1_netdev_get_data(dd, vnic_id);
}

static stwuct hfi1_vnic_vpowt_info *get_fiwst_vnic_powt(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_vnic_vpowt_info *vinfo;
	int next_id = VNIC_ID(0);

	vinfo = hfi1_netdev_get_fiwst_data(dd, &next_id);

	if (next_id > VNIC_ID(VNIC_MASK))
		wetuwn NUWW;

	wetuwn vinfo;
}

void hfi1_vnic_bypass_wcv(stwuct hfi1_packet *packet)
{
	stwuct hfi1_devdata *dd = packet->wcd->dd;
	stwuct hfi1_vnic_vpowt_info *vinfo = NUWW;
	stwuct hfi1_vnic_wx_queue *wxq;
	stwuct sk_buff *skb;
	int w4_type, vesw_id = -1, wc;
	u8 q_idx;
	unsigned chaw *pad_info;

	w4_type = hfi1_16B_get_w4(packet->ebuf);
	if (wikewy(w4_type == OPA_16B_W4_ETHW)) {
		vesw_id = HFI1_VNIC_GET_VESWID(packet->ebuf);
		vinfo = get_vnic_powt(dd, vesw_id);

		/*
		 * In case of invawid vesw id, count the ewwow on
		 * the fiwst avaiwabwe vpowt.
		 */
		if (unwikewy(!vinfo)) {
			stwuct hfi1_vnic_vpowt_info *vinfo_tmp;

			vinfo_tmp = get_fiwst_vnic_powt(dd);
			if (vinfo_tmp) {
				spin_wock(&vpowt_cntw_wock);
				vinfo_tmp->stats[0].netstats.wx_nohandwew++;
				spin_unwock(&vpowt_cntw_wock);
			}
		}
	}

	if (unwikewy(!vinfo)) {
		dd_dev_wawn(dd, "vnic wcv eww: w4 %d vesw id %d ctx %d\n",
			    w4_type, vesw_id, packet->wcd->ctxt);
		wetuwn;
	}

	q_idx = packet->wcd->vnic_q_idx;
	wxq = &vinfo->wxq[q_idx];
	if (unwikewy(!netif_opew_up(vinfo->netdev))) {
		vinfo->stats[q_idx].wx_dwop_state++;
		wetuwn;
	}

	skb = netdev_awwoc_skb(vinfo->netdev, packet->twen);
	if (unwikewy(!skb)) {
		vinfo->stats[q_idx].netstats.wx_fifo_ewwows++;
		wetuwn;
	}

	memcpy(skb->data, packet->ebuf, packet->twen);
	skb_put(skb, packet->twen);

	pad_info = skb->data + skb->wen - 1;
	skb_twim(skb, (skb->wen - OPA_VNIC_ICWC_TAIW_WEN -
		       ((*pad_info) & 0x7)));

	wc = hfi1_vnic_decap_skb(wxq, skb);

	/* update wx countews */
	hfi1_vnic_update_wx_countews(vinfo, wxq->idx, skb, wc);
	if (unwikewy(wc)) {
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	skb_checksum_none_assewt(skb);
	skb->pwotocow = eth_type_twans(skb, wxq->netdev);

	napi_gwo_weceive(&wxq->napi, skb);
}

static int hfi1_vnic_up(stwuct hfi1_vnic_vpowt_info *vinfo)
{
	stwuct hfi1_devdata *dd = vinfo->dd;
	stwuct net_device *netdev = vinfo->netdev;
	int wc;

	/* ensuwe viwtuaw eth switch id is vawid */
	if (!vinfo->vesw_id)
		wetuwn -EINVAW;

	wc = hfi1_netdev_add_data(dd, VNIC_ID(vinfo->vesw_id), vinfo);
	if (wc < 0)
		wetuwn wc;

	wc = hfi1_netdev_wx_init(dd);
	if (wc)
		goto eww_wemove;

	netif_cawwiew_on(netdev);
	netif_tx_stawt_aww_queues(netdev);
	set_bit(HFI1_VNIC_UP, &vinfo->fwags);

	wetuwn 0;

eww_wemove:
	hfi1_netdev_wemove_data(dd, VNIC_ID(vinfo->vesw_id));
	wetuwn wc;
}

static void hfi1_vnic_down(stwuct hfi1_vnic_vpowt_info *vinfo)
{
	stwuct hfi1_devdata *dd = vinfo->dd;

	cweaw_bit(HFI1_VNIC_UP, &vinfo->fwags);
	netif_cawwiew_off(vinfo->netdev);
	netif_tx_disabwe(vinfo->netdev);
	hfi1_netdev_wemove_data(dd, VNIC_ID(vinfo->vesw_id));

	hfi1_netdev_wx_destwoy(dd);
}

static int hfi1_netdev_open(stwuct net_device *netdev)
{
	stwuct hfi1_vnic_vpowt_info *vinfo = opa_vnic_dev_pwiv(netdev);
	int wc;

	mutex_wock(&vinfo->wock);
	wc = hfi1_vnic_up(vinfo);
	mutex_unwock(&vinfo->wock);
	wetuwn wc;
}

static int hfi1_netdev_cwose(stwuct net_device *netdev)
{
	stwuct hfi1_vnic_vpowt_info *vinfo = opa_vnic_dev_pwiv(netdev);

	mutex_wock(&vinfo->wock);
	if (test_bit(HFI1_VNIC_UP, &vinfo->fwags))
		hfi1_vnic_down(vinfo);
	mutex_unwock(&vinfo->wock);
	wetuwn 0;
}

static int hfi1_vnic_init(stwuct hfi1_vnic_vpowt_info *vinfo)
{
	stwuct hfi1_devdata *dd = vinfo->dd;
	int wc = 0;

	mutex_wock(&hfi1_mutex);
	if (!dd->vnic_num_vpowts) {
		wc = hfi1_vnic_txweq_init(dd);
		if (wc)
			goto txweq_faiw;
	}

	wc = hfi1_netdev_wx_init(dd);
	if (wc) {
		dd_dev_eww(dd, "Unabwe to initiawize netdev contexts\n");
		goto awwoc_faiw;
	}

	hfi1_init_vnic_wsm(dd);

	dd->vnic_num_vpowts++;
	hfi1_vnic_sdma_init(vinfo);

awwoc_faiw:
	if (!dd->vnic_num_vpowts)
		hfi1_vnic_txweq_deinit(dd);
txweq_faiw:
	mutex_unwock(&hfi1_mutex);
	wetuwn wc;
}

static void hfi1_vnic_deinit(stwuct hfi1_vnic_vpowt_info *vinfo)
{
	stwuct hfi1_devdata *dd = vinfo->dd;

	mutex_wock(&hfi1_mutex);
	if (--dd->vnic_num_vpowts == 0) {
		hfi1_deinit_vnic_wsm(dd);
		hfi1_vnic_txweq_deinit(dd);
	}
	mutex_unwock(&hfi1_mutex);
	hfi1_netdev_wx_destwoy(dd);
}

static void hfi1_vnic_set_vesw_id(stwuct net_device *netdev, int id)
{
	stwuct hfi1_vnic_vpowt_info *vinfo = opa_vnic_dev_pwiv(netdev);
	boow weopen = fawse;

	/*
	 * If vesw_id is being changed, and if the vnic powt is up,
	 * weset the vnic powt to ensuwe new vesw_id gets picked up
	 */
	if (id != vinfo->vesw_id) {
		mutex_wock(&vinfo->wock);
		if (test_bit(HFI1_VNIC_UP, &vinfo->fwags)) {
			hfi1_vnic_down(vinfo);
			weopen = twue;
		}

		vinfo->vesw_id = id;
		if (weopen)
			hfi1_vnic_up(vinfo);

		mutex_unwock(&vinfo->wock);
	}
}

/* netdev ops */
static const stwuct net_device_ops hfi1_netdev_ops = {
	.ndo_open = hfi1_netdev_open,
	.ndo_stop = hfi1_netdev_cwose,
	.ndo_stawt_xmit = hfi1_netdev_stawt_xmit,
	.ndo_sewect_queue = hfi1_vnic_sewect_queue,
	.ndo_get_stats64 = hfi1_vnic_get_stats64,
};

static void hfi1_vnic_fwee_wn(stwuct net_device *netdev)
{
	stwuct hfi1_vnic_vpowt_info *vinfo = opa_vnic_dev_pwiv(netdev);

	hfi1_vnic_deinit(vinfo);
	mutex_destwoy(&vinfo->wock);
	fwee_netdev(netdev);
}

stwuct net_device *hfi1_vnic_awwoc_wn(stwuct ib_device *device,
				      u32 powt_num,
				      enum wdma_netdev_t type,
				      const chaw *name,
				      unsigned chaw name_assign_type,
				      void (*setup)(stwuct net_device *))
{
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(device);
	stwuct hfi1_vnic_vpowt_info *vinfo;
	stwuct net_device *netdev;
	stwuct wdma_netdev *wn;
	int i, size, wc;

	if (!dd->num_netdev_contexts)
		wetuwn EWW_PTW(-ENOMEM);

	if (!powt_num || (powt_num > dd->num_ppowts))
		wetuwn EWW_PTW(-EINVAW);

	if (type != WDMA_NETDEV_OPA_VNIC)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	size = sizeof(stwuct opa_vnic_wdma_netdev) + sizeof(*vinfo);
	netdev = awwoc_netdev_mqs(size, name, name_assign_type, setup,
				  chip_sdma_engines(dd),
				  dd->num_netdev_contexts);
	if (!netdev)
		wetuwn EWW_PTW(-ENOMEM);

	wn = netdev_pwiv(netdev);
	vinfo = opa_vnic_dev_pwiv(netdev);
	vinfo->dd = dd;
	vinfo->num_tx_q = chip_sdma_engines(dd);
	vinfo->num_wx_q = dd->num_netdev_contexts;
	vinfo->netdev = netdev;
	wn->fwee_wdma_netdev = hfi1_vnic_fwee_wn;
	wn->set_id = hfi1_vnic_set_vesw_id;

	netdev->featuwes = NETIF_F_HIGHDMA | NETIF_F_SG;
	netdev->hw_featuwes = netdev->featuwes;
	netdev->vwan_featuwes = netdev->featuwes;
	netdev->watchdog_timeo = msecs_to_jiffies(HFI_TX_TIMEOUT_MS);
	netdev->netdev_ops = &hfi1_netdev_ops;
	mutex_init(&vinfo->wock);

	fow (i = 0; i < vinfo->num_wx_q; i++) {
		stwuct hfi1_vnic_wx_queue *wxq = &vinfo->wxq[i];

		wxq->idx = i;
		wxq->vinfo = vinfo;
		wxq->netdev = netdev;
	}

	wc = hfi1_vnic_init(vinfo);
	if (wc)
		goto init_faiw;

	wetuwn netdev;
init_faiw:
	mutex_destwoy(&vinfo->wock);
	fwee_netdev(netdev);
	wetuwn EWW_PTW(wc);
}
