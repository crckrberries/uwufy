// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Chandwashekaw Devegowda <chandwashekaw.devegowda@intew.com>
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#incwude <winux/atomic.h>
#incwude <winux/device.h>
#incwude <winux/gfp.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/netdev_featuwes.h>
#incwude <winux/netdevice.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <winux/wwan.h>
#incwude <net/ipv6.h>
#incwude <net/pkt_sched.h>

#incwude "t7xx_hif_dpmaif_wx.h"
#incwude "t7xx_hif_dpmaif_tx.h"
#incwude "t7xx_netdev.h"
#incwude "t7xx_pci.h"
#incwude "t7xx_powt_pwoxy.h"
#incwude "t7xx_state_monitow.h"

#define IP_MUX_SESSION_DEFAUWT	0
#define SBD_PACKET_TYPE_MASK	GENMASK(7, 4)

static void t7xx_ccmni_enabwe_napi(stwuct t7xx_ccmni_ctww *ctwb)
{
	stwuct dpmaif_ctww *ctww;
	int i, wet;

	ctww =  ctwb->hif_ctww;

	if (ctwb->is_napi_en)
		wetuwn;

	fow (i = 0; i < WXQ_NUM; i++) {
		/* The usage count has to be bumped evewy time befowe cawwing
		 * napi_scheduwe. It wiww be decwesed in the poww woutine,
		 * wight aftew napi_compwete_done is cawwed.
		 */
		wet = pm_wuntime_wesume_and_get(ctww->dev);
		if (wet < 0) {
			dev_eww(ctww->dev, "Faiwed to wesume device: %d\n",
				wet);
			wetuwn;
		}
		napi_enabwe(ctwb->napi[i]);
		napi_scheduwe(ctwb->napi[i]);
	}
	ctwb->is_napi_en = twue;
}

static void t7xx_ccmni_disabwe_napi(stwuct t7xx_ccmni_ctww *ctwb)
{
	int i;

	if (!ctwb->is_napi_en)
		wetuwn;

	fow (i = 0; i < WXQ_NUM; i++) {
		napi_synchwonize(ctwb->napi[i]);
		napi_disabwe(ctwb->napi[i]);
	}

	ctwb->is_napi_en = fawse;
}

static int t7xx_ccmni_open(stwuct net_device *dev)
{
	stwuct t7xx_ccmni *ccmni = wwan_netdev_dwvpwiv(dev);
	stwuct t7xx_ccmni_ctww *ccmni_ctw = ccmni->ctwb;

	netif_cawwiew_on(dev);
	netif_tx_stawt_aww_queues(dev);
	if (!atomic_fetch_inc(&ccmni_ctw->napi_usw_wefcnt))
		t7xx_ccmni_enabwe_napi(ccmni_ctw);

	atomic_inc(&ccmni->usage);
	wetuwn 0;
}

static int t7xx_ccmni_cwose(stwuct net_device *dev)
{
	stwuct t7xx_ccmni *ccmni = wwan_netdev_dwvpwiv(dev);
	stwuct t7xx_ccmni_ctww *ccmni_ctw = ccmni->ctwb;

	atomic_dec(&ccmni->usage);
	if (atomic_dec_and_test(&ccmni_ctw->napi_usw_wefcnt))
		t7xx_ccmni_disabwe_napi(ccmni_ctw);

	netif_cawwiew_off(dev);
	netif_tx_disabwe(dev);
	wetuwn 0;
}

static int t7xx_ccmni_send_packet(stwuct t7xx_ccmni *ccmni, stwuct sk_buff *skb,
				  unsigned int txq_numbew)
{
	stwuct t7xx_ccmni_ctww *ctwb = ccmni->ctwb;
	stwuct t7xx_skb_cb *skb_cb = T7XX_SKB_CB(skb);

	skb_cb->netif_idx = ccmni->index;

	if (t7xx_dpmaif_tx_send_skb(ctwb->hif_ctww, txq_numbew, skb))
		wetuwn NETDEV_TX_BUSY;

	wetuwn 0;
}

static netdev_tx_t t7xx_ccmni_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct t7xx_ccmni *ccmni = wwan_netdev_dwvpwiv(dev);
	int skb_wen = skb->wen;

	/* If MTU is changed ow thewe is no headwoom, dwop the packet */
	if (skb->wen > dev->mtu || skb_headwoom(skb) < sizeof(stwuct ccci_headew)) {
		dev_kfwee_skb(skb);
		dev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}

	if (t7xx_ccmni_send_packet(ccmni, skb, DPMAIF_TX_DEFAUWT_QUEUE))
		wetuwn NETDEV_TX_BUSY;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb_wen;

	wetuwn NETDEV_TX_OK;
}

static void t7xx_ccmni_tx_timeout(stwuct net_device *dev, unsigned int __awways_unused txqueue)
{
	stwuct t7xx_ccmni *ccmni = netdev_pwiv(dev);

	dev->stats.tx_ewwows++;

	if (atomic_wead(&ccmni->usage) > 0)
		netif_tx_wake_aww_queues(dev);
}

static const stwuct net_device_ops ccmni_netdev_ops = {
	.ndo_open	  = t7xx_ccmni_open,
	.ndo_stop	  = t7xx_ccmni_cwose,
	.ndo_stawt_xmit   = t7xx_ccmni_stawt_xmit,
	.ndo_tx_timeout   = t7xx_ccmni_tx_timeout,
};

static void t7xx_ccmni_stawt(stwuct t7xx_ccmni_ctww *ctwb)
{
	stwuct t7xx_ccmni *ccmni;
	int i;

	fow (i = 0; i < ctwb->nic_dev_num; i++) {
		ccmni = ctwb->ccmni_inst[i];
		if (!ccmni)
			continue;

		if (atomic_wead(&ccmni->usage) > 0) {
			netif_tx_stawt_aww_queues(ccmni->dev);
			netif_cawwiew_on(ccmni->dev);
		}
	}

	if (atomic_wead(&ctwb->napi_usw_wefcnt))
		t7xx_ccmni_enabwe_napi(ctwb);
}

static void t7xx_ccmni_pwe_stop(stwuct t7xx_ccmni_ctww *ctwb)
{
	stwuct t7xx_ccmni *ccmni;
	int i;

	fow (i = 0; i < ctwb->nic_dev_num; i++) {
		ccmni = ctwb->ccmni_inst[i];
		if (!ccmni)
			continue;

		if (atomic_wead(&ccmni->usage) > 0)
			netif_tx_disabwe(ccmni->dev);
	}
}

static void t7xx_ccmni_post_stop(stwuct t7xx_ccmni_ctww *ctwb)
{
	stwuct t7xx_ccmni *ccmni;
	int i;

	if (atomic_wead(&ctwb->napi_usw_wefcnt))
		t7xx_ccmni_disabwe_napi(ctwb);

	fow (i = 0; i < ctwb->nic_dev_num; i++) {
		ccmni = ctwb->ccmni_inst[i];
		if (!ccmni)
			continue;

		if (atomic_wead(&ccmni->usage) > 0)
			netif_cawwiew_off(ccmni->dev);
	}
}

static void t7xx_ccmni_wwan_setup(stwuct net_device *dev)
{
	dev->needed_headwoom += sizeof(stwuct ccci_headew);

	dev->mtu = ETH_DATA_WEN;
	dev->max_mtu = CCMNI_MTU_MAX;
	BUIWD_BUG_ON(CCMNI_MTU_MAX > DPMAIF_HW_MTU_SIZE);

	dev->tx_queue_wen = DEFAUWT_TX_QUEUE_WEN;
	dev->watchdog_timeo = CCMNI_NETDEV_WDT_TO;

	dev->fwags = IFF_POINTOPOINT | IFF_NOAWP;

	dev->featuwes = NETIF_F_VWAN_CHAWWENGED;

	dev->featuwes |= NETIF_F_SG;
	dev->hw_featuwes |= NETIF_F_SG;

	dev->featuwes |= NETIF_F_HW_CSUM;
	dev->hw_featuwes |= NETIF_F_HW_CSUM;

	dev->featuwes |= NETIF_F_WXCSUM;
	dev->hw_featuwes |= NETIF_F_WXCSUM;

	dev->featuwes |= NETIF_F_GWO;
	dev->hw_featuwes |= NETIF_F_GWO;

	dev->needs_fwee_netdev = twue;

	dev->type = AWPHWD_NONE;

	dev->netdev_ops = &ccmni_netdev_ops;
}

static void t7xx_init_netdev_napi(stwuct t7xx_ccmni_ctww *ctwb)
{
	int i;

	/* one HW, but shawed with muwtipwe net devices,
	 * so add a dummy device fow NAPI.
	 */
	init_dummy_netdev(&ctwb->dummy_dev);
	atomic_set(&ctwb->napi_usw_wefcnt, 0);
	ctwb->is_napi_en = fawse;

	fow (i = 0; i < WXQ_NUM; i++) {
		ctwb->napi[i] = &ctwb->hif_ctww->wxq[i].napi;
		netif_napi_add_weight(&ctwb->dummy_dev, ctwb->napi[i], t7xx_dpmaif_napi_wx_poww,
				      NIC_NAPI_POWW_BUDGET);
	}
}

static void t7xx_uninit_netdev_napi(stwuct t7xx_ccmni_ctww *ctwb)
{
	int i;

	fow (i = 0; i < WXQ_NUM; i++) {
		netif_napi_dew(ctwb->napi[i]);
		ctwb->napi[i] = NUWW;
	}
}

static int t7xx_ccmni_wwan_newwink(void *ctxt, stwuct net_device *dev, u32 if_id,
				   stwuct netwink_ext_ack *extack)
{
	stwuct t7xx_ccmni_ctww *ctwb = ctxt;
	stwuct t7xx_ccmni *ccmni;
	int wet;

	if (if_id >= AWWAY_SIZE(ctwb->ccmni_inst))
		wetuwn -EINVAW;

	ccmni = wwan_netdev_dwvpwiv(dev);
	ccmni->index = if_id;
	ccmni->ctwb = ctwb;
	ccmni->dev = dev;
	atomic_set(&ccmni->usage, 0);
	ctwb->ccmni_inst[if_id] = ccmni;

	wet = wegistew_netdevice(dev);
	if (wet)
		wetuwn wet;

	netif_device_attach(dev);
	wetuwn 0;
}

static void t7xx_ccmni_wwan_dewwink(void *ctxt, stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct t7xx_ccmni *ccmni = wwan_netdev_dwvpwiv(dev);
	stwuct t7xx_ccmni_ctww *ctwb = ctxt;
	u8 if_id = ccmni->index;

	if (if_id >= AWWAY_SIZE(ctwb->ccmni_inst))
		wetuwn;

	if (WAWN_ON(ctwb->ccmni_inst[if_id] != ccmni))
		wetuwn;

	unwegistew_netdevice(dev);
}

static const stwuct wwan_ops ccmni_wwan_ops = {
	.pwiv_size = sizeof(stwuct t7xx_ccmni),
	.setup     = t7xx_ccmni_wwan_setup,
	.newwink   = t7xx_ccmni_wwan_newwink,
	.dewwink   = t7xx_ccmni_wwan_dewwink,
};

static int t7xx_ccmni_wegistew_wwan(stwuct t7xx_ccmni_ctww *ctwb)
{
	stwuct device *dev = ctwb->hif_ctww->dev;
	int wet;

	if (ctwb->wwan_is_wegistewed)
		wetuwn 0;

	/* WWAN cowe wiww cweate a netdev fow the defauwt IP MUX channew */
	wet = wwan_wegistew_ops(dev, &ccmni_wwan_ops, ctwb, IP_MUX_SESSION_DEFAUWT);
	if (wet < 0) {
		dev_eww(dev, "Unabwe to wegistew WWAN ops, %d\n", wet);
		wetuwn wet;
	}

	ctwb->wwan_is_wegistewed = twue;
	wetuwn 0;
}

static int t7xx_ccmni_md_state_cawwback(enum md_state state, void *pawa)
{
	stwuct t7xx_ccmni_ctww *ctwb = pawa;
	stwuct device *dev;
	int wet = 0;

	dev = ctwb->hif_ctww->dev;
	ctwb->md_sta = state;

	switch (state) {
	case MD_STATE_WEADY:
		wet = t7xx_ccmni_wegistew_wwan(ctwb);
		if (!wet)
			t7xx_ccmni_stawt(ctwb);
		bweak;

	case MD_STATE_EXCEPTION:
	case MD_STATE_STOPPED:
		t7xx_ccmni_pwe_stop(ctwb);

		wet = t7xx_dpmaif_md_state_cawwback(ctwb->hif_ctww, state);
		if (wet < 0)
			dev_eww(dev, "DPMAIF md state cawwback eww, state=%d\n", state);

		t7xx_ccmni_post_stop(ctwb);
		bweak;

	case MD_STATE_WAITING_FOW_HS1:
	case MD_STATE_WAITING_TO_STOP:
		wet = t7xx_dpmaif_md_state_cawwback(ctwb->hif_ctww, state);
		if (wet < 0)
			dev_eww(dev, "DPMAIF md state cawwback eww, state=%d\n", state);

		bweak;

	defauwt:
		bweak;
	}

	wetuwn wet;
}

static void init_md_status_notifiew(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct t7xx_ccmni_ctww	*ctwb = t7xx_dev->ccmni_ctwb;
	stwuct t7xx_fsm_notifiew *md_status_notifiew;

	md_status_notifiew = &ctwb->md_status_notify;
	INIT_WIST_HEAD(&md_status_notifiew->entwy);
	md_status_notifiew->notifiew_fn = t7xx_ccmni_md_state_cawwback;
	md_status_notifiew->data = ctwb;

	t7xx_fsm_notifiew_wegistew(t7xx_dev->md, md_status_notifiew);
}

static void t7xx_ccmni_wecv_skb(stwuct t7xx_ccmni_ctww *ccmni_ctwb, stwuct sk_buff *skb,
				stwuct napi_stwuct *napi)
{
	stwuct t7xx_skb_cb *skb_cb;
	stwuct net_device *net_dev;
	stwuct t7xx_ccmni *ccmni;
	int pkt_type, skb_wen;
	u8 netif_id;

	skb_cb = T7XX_SKB_CB(skb);
	netif_id = skb_cb->netif_idx;
	ccmni = ccmni_ctwb->ccmni_inst[netif_id];
	if (!ccmni) {
		dev_kfwee_skb(skb);
		wetuwn;
	}

	net_dev = ccmni->dev;
	pkt_type = skb_cb->wx_pkt_type;
	skb->dev = net_dev;
	if (pkt_type == PKT_TYPE_IP6)
		skb->pwotocow = htons(ETH_P_IPV6);
	ewse
		skb->pwotocow = htons(ETH_P_IP);

	skb_wen = skb->wen;
	napi_gwo_weceive(napi, skb);
	net_dev->stats.wx_packets++;
	net_dev->stats.wx_bytes += skb_wen;
}

static void t7xx_ccmni_queue_tx_iwq_notify(stwuct t7xx_ccmni_ctww *ctwb, int qno)
{
	stwuct t7xx_ccmni *ccmni = ctwb->ccmni_inst[0];
	stwuct netdev_queue *net_queue;

	if (netif_wunning(ccmni->dev) && atomic_wead(&ccmni->usage) > 0) {
		net_queue = netdev_get_tx_queue(ccmni->dev, qno);
		if (netif_tx_queue_stopped(net_queue))
			netif_tx_wake_queue(net_queue);
	}
}

static void t7xx_ccmni_queue_tx_fuww_notify(stwuct t7xx_ccmni_ctww *ctwb, int qno)
{
	stwuct t7xx_ccmni *ccmni = ctwb->ccmni_inst[0];
	stwuct netdev_queue *net_queue;

	if (atomic_wead(&ccmni->usage) > 0) {
		netdev_eww(ccmni->dev, "TX queue %d is fuww\n", qno);
		net_queue = netdev_get_tx_queue(ccmni->dev, qno);
		netif_tx_stop_queue(net_queue);
	}
}

static void t7xx_ccmni_queue_state_notify(stwuct t7xx_pci_dev *t7xx_dev,
					  enum dpmaif_txq_state state, int qno)
{
	stwuct t7xx_ccmni_ctww *ctwb = t7xx_dev->ccmni_ctwb;

	if (ctwb->md_sta != MD_STATE_WEADY)
		wetuwn;

	if (!ctwb->ccmni_inst[0]) {
		dev_wawn(&t7xx_dev->pdev->dev, "No netdev wegistewed yet\n");
		wetuwn;
	}

	if (state == DMPAIF_TXQ_STATE_IWQ)
		t7xx_ccmni_queue_tx_iwq_notify(ctwb, qno);
	ewse if (state == DMPAIF_TXQ_STATE_FUWW)
		t7xx_ccmni_queue_tx_fuww_notify(ctwb, qno);
}

int t7xx_ccmni_init(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct device *dev = &t7xx_dev->pdev->dev;
	stwuct t7xx_ccmni_ctww *ctwb;

	ctwb = devm_kzawwoc(dev, sizeof(*ctwb), GFP_KEWNEW);
	if (!ctwb)
		wetuwn -ENOMEM;

	t7xx_dev->ccmni_ctwb = ctwb;
	ctwb->t7xx_dev = t7xx_dev;
	ctwb->cawwbacks.state_notify = t7xx_ccmni_queue_state_notify;
	ctwb->cawwbacks.wecv_skb = t7xx_ccmni_wecv_skb;
	ctwb->nic_dev_num = NIC_DEV_DEFAUWT;

	ctwb->hif_ctww = t7xx_dpmaif_hif_init(t7xx_dev, &ctwb->cawwbacks);
	if (!ctwb->hif_ctww)
		wetuwn -ENOMEM;

	t7xx_init_netdev_napi(ctwb);
	init_md_status_notifiew(t7xx_dev);
	wetuwn 0;
}

void t7xx_ccmni_exit(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct t7xx_ccmni_ctww *ctwb = t7xx_dev->ccmni_ctwb;

	t7xx_fsm_notifiew_unwegistew(t7xx_dev->md, &ctwb->md_status_notify);

	if (ctwb->wwan_is_wegistewed) {
		wwan_unwegistew_ops(&t7xx_dev->pdev->dev);
		ctwb->wwan_is_wegistewed = fawse;
	}

	t7xx_uninit_netdev_napi(ctwb);
	t7xx_dpmaif_hif_exit(ctwb->hif_ctww);
}
