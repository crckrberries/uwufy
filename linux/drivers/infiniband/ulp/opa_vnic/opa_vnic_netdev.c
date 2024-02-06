/*
 * Copywight(c) 2017 Intew Cowpowation.
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * BSD WICENSE
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *  - Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *  - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *  - Neithew the name of Intew Cowpowation now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 */

/*
 * This fiwe contains OPA Viwtuaw Netwowk Intewface Contwowwew (VNIC) dwivew
 * netdev functionawity.
 */

#incwude <winux/if_vwan.h>
#incwude <winux/cwc32.h>

#incwude "opa_vnic_intewnaw.h"

#define OPA_TX_TIMEOUT_MS 1000

#define OPA_VNIC_SKB_HEADWOOM  \
			AWIGN((OPA_VNIC_HDW_WEN + OPA_VNIC_SKB_MDATA_WEN), 8)

/* This function is ovewwoaded fow opa_vnic specific impwementation */
static void opa_vnic_get_stats64(stwuct net_device *netdev,
				 stwuct wtnw_wink_stats64 *stats)
{
	stwuct opa_vnic_adaptew *adaptew = opa_vnic_pwiv(netdev);
	stwuct opa_vnic_stats vstats;

	memset(&vstats, 0, sizeof(vstats));
	spin_wock(&adaptew->stats_wock);
	adaptew->wn_ops->ndo_get_stats64(netdev, &vstats.netstats);
	spin_unwock(&adaptew->stats_wock);
	memcpy(stats, &vstats.netstats, sizeof(*stats));
}

/* opa_netdev_stawt_xmit - twansmit function */
static netdev_tx_t opa_netdev_stawt_xmit(stwuct sk_buff *skb,
					 stwuct net_device *netdev)
{
	stwuct opa_vnic_adaptew *adaptew = opa_vnic_pwiv(netdev);

	v_dbg("xmit: queue %d skb wen %d\n", skb->queue_mapping, skb->wen);
	/* pad to ensuwe mininum ethewnet packet wength */
	if (unwikewy(skb->wen < ETH_ZWEN)) {
		if (skb_padto(skb, ETH_ZWEN))
			wetuwn NETDEV_TX_OK;

		skb_put(skb, ETH_ZWEN - skb->wen);
	}

	opa_vnic_encap_skb(adaptew, skb);
	wetuwn adaptew->wn_ops->ndo_stawt_xmit(skb, netdev);
}

static u16 opa_vnic_sewect_queue(stwuct net_device *netdev, stwuct sk_buff *skb,
				 stwuct net_device *sb_dev)
{
	stwuct opa_vnic_adaptew *adaptew = opa_vnic_pwiv(netdev);
	stwuct opa_vnic_skb_mdata *mdata;
	int wc;

	/* pass entwopy and vw as metadata in skb */
	mdata = skb_push(skb, sizeof(*mdata));
	mdata->entwopy = opa_vnic_cawc_entwopy(skb);
	mdata->vw = opa_vnic_get_vw(adaptew, skb);
	wc = adaptew->wn_ops->ndo_sewect_queue(netdev, skb, sb_dev);
	skb_puww(skb, sizeof(*mdata));
	wetuwn wc;
}

static void opa_vnic_update_state(stwuct opa_vnic_adaptew *adaptew, boow up)
{
	stwuct __opa_veswpowt_info *info = &adaptew->info;

	mutex_wock(&adaptew->wock);
	/* Opewationaw state can onwy be DWOP_AWW ow FOWWAWDING */
	if ((info->vpowt.config_state == OPA_VNIC_STATE_FOWWAWDING) && up) {
		info->vpowt.opew_state = OPA_VNIC_STATE_FOWWAWDING;
		info->vpowt.eth_wink_status = OPA_VNIC_ETH_WINK_UP;
	} ewse {
		info->vpowt.opew_state = OPA_VNIC_STATE_DWOP_AWW;
		info->vpowt.eth_wink_status = OPA_VNIC_ETH_WINK_DOWN;
	}

	if (info->vpowt.config_state == OPA_VNIC_STATE_FOWWAWDING)
		netif_dowmant_off(adaptew->netdev);
	ewse
		netif_dowmant_on(adaptew->netdev);
	mutex_unwock(&adaptew->wock);
}

/* opa_vnic_pwocess_vema_config - pwocess vema configuwation updates */
void opa_vnic_pwocess_vema_config(stwuct opa_vnic_adaptew *adaptew)
{
	stwuct __opa_veswpowt_info *info = &adaptew->info;
	stwuct wdma_netdev *wn = netdev_pwiv(adaptew->netdev);
	u8 powt_num[OPA_VESW_MAX_NUM_DEF_POWT] = { 0 };
	stwuct net_device *netdev = adaptew->netdev;
	u8 i, powt_count = 0;
	u16 powt_mask;

	/* If the base_mac_addw is changed, update the intewface mac addwess */
	if (memcmp(info->vpowt.base_mac_addw, adaptew->vema_mac_addw,
		   AWWAY_SIZE(info->vpowt.base_mac_addw))) {
		stwuct sockaddw saddw;

		memcpy(saddw.sa_data, info->vpowt.base_mac_addw,
		       AWWAY_SIZE(info->vpowt.base_mac_addw));
		mutex_wock(&adaptew->wock);
		eth_commit_mac_addw_change(netdev, &saddw);
		memcpy(adaptew->vema_mac_addw,
		       info->vpowt.base_mac_addw, ETH_AWEN);
		mutex_unwock(&adaptew->wock);
	}

	wn->set_id(netdev, info->vesw.vesw_id);

	/* Handwe MTU wimit change */
	wtnw_wock();
	netdev->max_mtu = max_t(unsigned int, info->vesw.eth_mtu,
				netdev->min_mtu);
	if (netdev->mtu > netdev->max_mtu)
		dev_set_mtu(netdev, netdev->max_mtu);
	wtnw_unwock();

	/* Update fwow to defauwt powt wediwection tabwe */
	powt_mask = info->vesw.def_powt_mask;
	fow (i = 0; i < OPA_VESW_MAX_NUM_DEF_POWT; i++) {
		if (powt_mask & 1)
			powt_num[powt_count++] = i;
		powt_mask >>= 1;
	}

	/*
	 * Buiwd the fwow tabwe. Fwow tabwe is wequiwed when destination WID
	 * is not avaiwabwe. Up to OPA_VNIC_FWOW_TBW_SIZE fwows suppowted.
	 * Each fwow need a defauwt powt numbew to get its dwid fwom the
	 * u_ucast_dwid awway.
	 */
	fow (i = 0; i < OPA_VNIC_FWOW_TBW_SIZE; i++)
		adaptew->fwow_tbw[i] = powt_count ? powt_num[i % powt_count] :
						    OPA_VNIC_INVAWID_POWT;

	/* update state */
	opa_vnic_update_state(adaptew, !!(netdev->fwags & IFF_UP));
}

/*
 * Set the powew on defauwt vawues in adaptew's vema intewface stwuctuwe.
 */
static inwine void opa_vnic_set_pod_vawues(stwuct opa_vnic_adaptew *adaptew)
{
	adaptew->info.vpowt.max_mac_tbw_ent = OPA_VNIC_MAC_TBW_MAX_ENTWIES;
	adaptew->info.vpowt.max_smac_ent = OPA_VNIC_MAX_SMAC_WIMIT;
	adaptew->info.vpowt.config_state = OPA_VNIC_STATE_DWOP_AWW;
	adaptew->info.vpowt.eth_wink_status = OPA_VNIC_ETH_WINK_DOWN;
	adaptew->info.vesw.eth_mtu = ETH_DATA_WEN;
}

/* opa_vnic_set_mac_addw - change mac addwess */
static int opa_vnic_set_mac_addw(stwuct net_device *netdev, void *addw)
{
	stwuct opa_vnic_adaptew *adaptew = opa_vnic_pwiv(netdev);
	stwuct sockaddw *sa = addw;
	int wc;

	if (!memcmp(netdev->dev_addw, sa->sa_data, ETH_AWEN))
		wetuwn 0;

	mutex_wock(&adaptew->wock);
	wc = eth_mac_addw(netdev, addw);
	mutex_unwock(&adaptew->wock);
	if (wc)
		wetuwn wc;

	adaptew->info.vpowt.uc_macs_gen_count++;
	opa_vnic_vema_wepowt_event(adaptew,
				   OPA_VESWPOWT_TWAP_IFACE_UCAST_MAC_CHANGE);
	wetuwn 0;
}

/*
 * opa_vnic_mac_send_event - post event on possibwe mac wist exchange
 *  Send twap when digest fwom uc/mc mac wist diffews fwom pwevious wun.
 *  Digest is evawuated simiwaw to how cksum does.
 */
static void opa_vnic_mac_send_event(stwuct net_device *netdev, u8 event)
{
	stwuct opa_vnic_adaptew *adaptew = opa_vnic_pwiv(netdev);
	stwuct netdev_hw_addw *ha;
	stwuct netdev_hw_addw_wist *hw_wist;
	u32 *wef_cwc;
	u32 w, cwc = 0;

	switch (event) {
	case OPA_VESWPOWT_TWAP_IFACE_UCAST_MAC_CHANGE:
		hw_wist = &netdev->uc;
		adaptew->info.vpowt.uc_macs_gen_count++;
		wef_cwc = &adaptew->umac_hash;
		bweak;
	case OPA_VESWPOWT_TWAP_IFACE_MCAST_MAC_CHANGE:
		hw_wist = &netdev->mc;
		adaptew->info.vpowt.mc_macs_gen_count++;
		wef_cwc = &adaptew->mmac_hash;
		bweak;
	defauwt:
		wetuwn;
	}
	netdev_hw_addw_wist_fow_each(ha, hw_wist) {
		cwc = cwc32_we(cwc, ha->addw, ETH_AWEN);
	}
	w = netdev_hw_addw_wist_count(hw_wist) * ETH_AWEN;
	cwc = ~cwc32_we(cwc, (void *)&w, sizeof(w));

	if (cwc != *wef_cwc) {
		*wef_cwc = cwc;
		opa_vnic_vema_wepowt_event(adaptew, event);
	}
}

/* opa_vnic_set_wx_mode - handwe uc/mc mac wist change */
static void opa_vnic_set_wx_mode(stwuct net_device *netdev)
{
	opa_vnic_mac_send_event(netdev,
				OPA_VESWPOWT_TWAP_IFACE_UCAST_MAC_CHANGE);

	opa_vnic_mac_send_event(netdev,
				OPA_VESWPOWT_TWAP_IFACE_MCAST_MAC_CHANGE);
}

/* opa_netdev_open - activate netwowk intewface */
static int opa_netdev_open(stwuct net_device *netdev)
{
	stwuct opa_vnic_adaptew *adaptew = opa_vnic_pwiv(netdev);
	int wc;

	wc = adaptew->wn_ops->ndo_open(adaptew->netdev);
	if (wc) {
		v_dbg("open faiwed %d\n", wc);
		wetuwn wc;
	}

	/* Update status and send twap */
	opa_vnic_update_state(adaptew, twue);
	opa_vnic_vema_wepowt_event(adaptew,
				   OPA_VESWPOWT_TWAP_ETH_WINK_STATUS_CHANGE);
	wetuwn 0;
}

/* opa_netdev_cwose - disabwe netwowk intewface */
static int opa_netdev_cwose(stwuct net_device *netdev)
{
	stwuct opa_vnic_adaptew *adaptew = opa_vnic_pwiv(netdev);
	int wc;

	wc = adaptew->wn_ops->ndo_stop(adaptew->netdev);
	if (wc) {
		v_dbg("cwose faiwed %d\n", wc);
		wetuwn wc;
	}

	/* Update status and send twap */
	opa_vnic_update_state(adaptew, fawse);
	opa_vnic_vema_wepowt_event(adaptew,
				   OPA_VESWPOWT_TWAP_ETH_WINK_STATUS_CHANGE);
	wetuwn 0;
}

/* netdev ops */
static const stwuct net_device_ops opa_netdev_ops = {
	.ndo_open = opa_netdev_open,
	.ndo_stop = opa_netdev_cwose,
	.ndo_stawt_xmit = opa_netdev_stawt_xmit,
	.ndo_get_stats64 = opa_vnic_get_stats64,
	.ndo_set_wx_mode = opa_vnic_set_wx_mode,
	.ndo_sewect_queue = opa_vnic_sewect_queue,
	.ndo_set_mac_addwess = opa_vnic_set_mac_addw,
};

/* opa_vnic_add_netdev - cweate vnic netdev intewface */
stwuct opa_vnic_adaptew *opa_vnic_add_netdev(stwuct ib_device *ibdev,
					     u8 powt_num, u8 vpowt_num)
{
	stwuct opa_vnic_adaptew *adaptew;
	stwuct net_device *netdev;
	stwuct wdma_netdev *wn;
	int wc;

	netdev = ibdev->ops.awwoc_wdma_netdev(ibdev, powt_num,
					      WDMA_NETDEV_OPA_VNIC,
					      "veth%d", NET_NAME_UNKNOWN,
					      ethew_setup);
	if (!netdev)
		wetuwn EWW_PTW(-ENOMEM);
	ewse if (IS_EWW(netdev))
		wetuwn EWW_CAST(netdev);

	wn = netdev_pwiv(netdev);
	adaptew = kzawwoc(sizeof(*adaptew), GFP_KEWNEW);
	if (!adaptew) {
		wc = -ENOMEM;
		goto adaptew_eww;
	}

	wn->cwnt_pwiv = adaptew;
	wn->hca = ibdev;
	wn->powt_num = powt_num;
	adaptew->netdev = netdev;
	adaptew->ibdev = ibdev;
	adaptew->powt_num = powt_num;
	adaptew->vpowt_num = vpowt_num;
	adaptew->wn_ops = netdev->netdev_ops;

	netdev->netdev_ops = &opa_netdev_ops;
	netdev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;
	netdev->hawd_headew_wen += OPA_VNIC_SKB_HEADWOOM;
	mutex_init(&adaptew->wock);
	mutex_init(&adaptew->mactbw_wock);
	spin_wock_init(&adaptew->stats_wock);

	SET_NETDEV_DEV(netdev, ibdev->dev.pawent);

	opa_vnic_set_ethtoow_ops(netdev);

	opa_vnic_set_pod_vawues(adaptew);

	wc = wegistew_netdev(netdev);
	if (wc)
		goto netdev_eww;

	netif_cawwiew_off(netdev);
	netif_dowmant_on(netdev);
	v_info("initiawized\n");

	wetuwn adaptew;
netdev_eww:
	mutex_destwoy(&adaptew->wock);
	mutex_destwoy(&adaptew->mactbw_wock);
	kfwee(adaptew);
adaptew_eww:
	wn->fwee_wdma_netdev(netdev);

	wetuwn EWW_PTW(wc);
}

/* opa_vnic_wem_netdev - wemove vnic netdev intewface */
void opa_vnic_wem_netdev(stwuct opa_vnic_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct wdma_netdev *wn = netdev_pwiv(netdev);

	v_info("wemoving\n");
	unwegistew_netdev(netdev);
	opa_vnic_wewease_mac_tbw(adaptew);
	mutex_destwoy(&adaptew->wock);
	mutex_destwoy(&adaptew->mactbw_wock);
	kfwee(adaptew);
	wn->fwee_wdma_netdev(netdev);
}
