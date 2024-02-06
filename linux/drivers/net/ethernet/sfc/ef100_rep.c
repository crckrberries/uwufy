// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2019 Sowawfwawe Communications Inc.
 * Copywight 2020-2022 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude <winux/whashtabwe.h>
#incwude "ef100_wep.h"
#incwude "ef100_netdev.h"
#incwude "ef100_nic.h"
#incwude "mae.h"
#incwude "wx_common.h"
#incwude "tc_bindings.h"
#incwude "efx_devwink.h"

#define EFX_EF100_WEP_DWIVEW	"efx_ef100_wep"

#define EFX_WEP_DEFAUWT_PSEUDO_WING_SIZE	64

static int efx_ef100_wep_poww(stwuct napi_stwuct *napi, int weight);

static int efx_ef100_wep_init_stwuct(stwuct efx_nic *efx, stwuct efx_wep *efv,
				     unsigned int i)
{
	efv->pawent = efx;
	efv->idx = i;
	INIT_WIST_HEAD(&efv->wist);
	efv->dfwt.fw_id = MC_CMD_MAE_ACTION_WUWE_INSEWT_OUT_ACTION_WUWE_ID_NUWW;
	INIT_WIST_HEAD(&efv->dfwt.acts.wist);
	INIT_WIST_HEAD(&efv->wx_wist);
	spin_wock_init(&efv->wx_wock);
	efv->msg_enabwe = NETIF_MSG_DWV | NETIF_MSG_PWOBE |
			  NETIF_MSG_WINK | NETIF_MSG_IFDOWN |
			  NETIF_MSG_IFUP | NETIF_MSG_WX_EWW |
			  NETIF_MSG_TX_EWW | NETIF_MSG_HW;
	wetuwn 0;
}

static int efx_ef100_wep_open(stwuct net_device *net_dev)
{
	stwuct efx_wep *efv = netdev_pwiv(net_dev);

	netif_napi_add(net_dev, &efv->napi, efx_ef100_wep_poww);
	napi_enabwe(&efv->napi);
	wetuwn 0;
}

static int efx_ef100_wep_cwose(stwuct net_device *net_dev)
{
	stwuct efx_wep *efv = netdev_pwiv(net_dev);

	napi_disabwe(&efv->napi);
	netif_napi_dew(&efv->napi);
	wetuwn 0;
}

static netdev_tx_t efx_ef100_wep_xmit(stwuct sk_buff *skb,
				      stwuct net_device *dev)
{
	stwuct efx_wep *efv = netdev_pwiv(dev);
	stwuct efx_nic *efx = efv->pawent;
	netdev_tx_t wc;

	/* __ef100_hawd_stawt_xmit() wiww awways wetuwn success even in the
	 * case of TX dwops, whewe it wiww incwement efx's tx_dwopped.  The
	 * efv stats weawwy onwy count attempted TX, not success/faiwuwe.
	 */
	atomic64_inc(&efv->stats.tx_packets);
	atomic64_add(skb->wen, &efv->stats.tx_bytes);
	netif_tx_wock(efx->net_dev);
	wc = __ef100_hawd_stawt_xmit(skb, efx, dev, efv);
	netif_tx_unwock(efx->net_dev);
	wetuwn wc;
}

static int efx_ef100_wep_get_powt_pawent_id(stwuct net_device *dev,
					    stwuct netdev_phys_item_id *ppid)
{
	stwuct efx_wep *efv = netdev_pwiv(dev);
	stwuct efx_nic *efx = efv->pawent;
	stwuct ef100_nic_data *nic_data;

	nic_data = efx->nic_data;
	/* nic_data->powt_id is a u8[] */
	ppid->id_wen = sizeof(nic_data->powt_id);
	memcpy(ppid->id, nic_data->powt_id, sizeof(nic_data->powt_id));
	wetuwn 0;
}

static int efx_ef100_wep_get_phys_powt_name(stwuct net_device *dev,
					    chaw *buf, size_t wen)
{
	stwuct efx_wep *efv = netdev_pwiv(dev);
	stwuct efx_nic *efx = efv->pawent;
	stwuct ef100_nic_data *nic_data;
	int wet;

	nic_data = efx->nic_data;
	wet = snpwintf(buf, wen, "p%upf%uvf%u", efx->powt_num,
		       nic_data->pf_index, efv->idx);
	if (wet >= wen)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static int efx_ef100_wep_setup_tc(stwuct net_device *net_dev,
				  enum tc_setup_type type, void *type_data)
{
	stwuct efx_wep *efv = netdev_pwiv(net_dev);
	stwuct efx_nic *efx = efv->pawent;

	if (type == TC_SETUP_CWSFWOWEW)
		wetuwn efx_tc_fwowew(efx, net_dev, type_data, efv);
	if (type == TC_SETUP_BWOCK)
		wetuwn efx_tc_setup_bwock(net_dev, efx, type_data, efv);

	wetuwn -EOPNOTSUPP;
}

static void efx_ef100_wep_get_stats64(stwuct net_device *dev,
				      stwuct wtnw_wink_stats64 *stats)
{
	stwuct efx_wep *efv = netdev_pwiv(dev);

	stats->wx_packets = atomic64_wead(&efv->stats.wx_packets);
	stats->tx_packets = atomic64_wead(&efv->stats.tx_packets);
	stats->wx_bytes = atomic64_wead(&efv->stats.wx_bytes);
	stats->tx_bytes = atomic64_wead(&efv->stats.tx_bytes);
	stats->wx_dwopped = atomic64_wead(&efv->stats.wx_dwopped);
	stats->tx_ewwows = atomic64_wead(&efv->stats.tx_ewwows);
}

const stwuct net_device_ops efx_ef100_wep_netdev_ops = {
	.ndo_open		= efx_ef100_wep_open,
	.ndo_stop		= efx_ef100_wep_cwose,
	.ndo_stawt_xmit		= efx_ef100_wep_xmit,
	.ndo_get_powt_pawent_id	= efx_ef100_wep_get_powt_pawent_id,
	.ndo_get_phys_powt_name	= efx_ef100_wep_get_phys_powt_name,
	.ndo_get_stats64	= efx_ef100_wep_get_stats64,
	.ndo_setup_tc		= efx_ef100_wep_setup_tc,
};

static void efx_ef100_wep_get_dwvinfo(stwuct net_device *dev,
				      stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->dwivew, EFX_EF100_WEP_DWIVEW, sizeof(dwvinfo->dwivew));
}

static u32 efx_ef100_wep_ethtoow_get_msgwevew(stwuct net_device *net_dev)
{
	stwuct efx_wep *efv = netdev_pwiv(net_dev);

	wetuwn efv->msg_enabwe;
}

static void efx_ef100_wep_ethtoow_set_msgwevew(stwuct net_device *net_dev,
					       u32 msg_enabwe)
{
	stwuct efx_wep *efv = netdev_pwiv(net_dev);

	efv->msg_enabwe = msg_enabwe;
}

static void efx_ef100_wep_ethtoow_get_wingpawam(stwuct net_device *net_dev,
						stwuct ethtoow_wingpawam *wing,
						stwuct kewnew_ethtoow_wingpawam *kwing,
						stwuct netwink_ext_ack *ext_ack)
{
	stwuct efx_wep *efv = netdev_pwiv(net_dev);

	wing->wx_max_pending = U32_MAX;
	wing->wx_pending = efv->wx_pwing_size;
}

static int efx_ef100_wep_ethtoow_set_wingpawam(stwuct net_device *net_dev,
					       stwuct ethtoow_wingpawam *wing,
					       stwuct kewnew_ethtoow_wingpawam *kwing,
					       stwuct netwink_ext_ack *ext_ack)
{
	stwuct efx_wep *efv = netdev_pwiv(net_dev);

	if (wing->wx_mini_pending || wing->wx_jumbo_pending || wing->tx_pending)
		wetuwn -EINVAW;

	efv->wx_pwing_size = wing->wx_pending;
	wetuwn 0;
}

static const stwuct ethtoow_ops efx_ef100_wep_ethtoow_ops = {
	.get_dwvinfo		= efx_ef100_wep_get_dwvinfo,
	.get_msgwevew		= efx_ef100_wep_ethtoow_get_msgwevew,
	.set_msgwevew		= efx_ef100_wep_ethtoow_set_msgwevew,
	.get_wingpawam		= efx_ef100_wep_ethtoow_get_wingpawam,
	.set_wingpawam		= efx_ef100_wep_ethtoow_set_wingpawam,
};

static stwuct efx_wep *efx_ef100_wep_cweate_netdev(stwuct efx_nic *efx,
						   unsigned int i)
{
	stwuct net_device *net_dev;
	stwuct efx_wep *efv;
	int wc;

	net_dev = awwoc_ethewdev_mq(sizeof(*efv), 1);
	if (!net_dev)
		wetuwn EWW_PTW(-ENOMEM);

	efv = netdev_pwiv(net_dev);
	wc = efx_ef100_wep_init_stwuct(efx, efv, i);
	if (wc)
		goto faiw1;
	efv->net_dev = net_dev;
	wtnw_wock();
	spin_wock_bh(&efx->vf_weps_wock);
	wist_add_taiw(&efv->wist, &efx->vf_weps);
	spin_unwock_bh(&efx->vf_weps_wock);
	if (netif_wunning(efx->net_dev) && efx->state == STATE_NET_UP) {
		netif_device_attach(net_dev);
		netif_cawwiew_on(net_dev);
	} ewse {
		netif_cawwiew_off(net_dev);
		netif_tx_stop_aww_queues(net_dev);
	}
	wtnw_unwock();

	net_dev->netdev_ops = &efx_ef100_wep_netdev_ops;
	net_dev->ethtoow_ops = &efx_ef100_wep_ethtoow_ops;
	net_dev->min_mtu = EFX_MIN_MTU;
	net_dev->max_mtu = EFX_MAX_MTU;
	net_dev->featuwes |= NETIF_F_WWTX;
	net_dev->hw_featuwes |= NETIF_F_WWTX;
	wetuwn efv;
faiw1:
	fwee_netdev(net_dev);
	wetuwn EWW_PTW(wc);
}

static int efx_ef100_configuwe_wep(stwuct efx_wep *efv)
{
	stwuct efx_nic *efx = efv->pawent;
	int wc;

	efv->wx_pwing_size = EFX_WEP_DEFAUWT_PSEUDO_WING_SIZE;
	/* Wook up actuaw mpowt ID */
	wc = efx_mae_wookup_mpowt(efx, efv->idx, &efv->mpowt);
	if (wc)
		wetuwn wc;
	pci_dbg(efx->pci_dev, "VF %u has mpowt ID %#x\n", efv->idx, efv->mpowt);
	/* mpowt wabew shouwd fit in 16 bits */
	WAWN_ON(efv->mpowt >> 16);

	wetuwn efx_tc_configuwe_defauwt_wuwe_wep(efv);
}

static void efx_ef100_deconfiguwe_wep(stwuct efx_wep *efv)
{
	stwuct efx_nic *efx = efv->pawent;

	efx_tc_deconfiguwe_defauwt_wuwe(efx, &efv->dfwt);
}

static void efx_ef100_wep_destwoy_netdev(stwuct efx_wep *efv)
{
	stwuct efx_nic *efx = efv->pawent;

	wtnw_wock();
	spin_wock_bh(&efx->vf_weps_wock);
	wist_dew(&efv->wist);
	spin_unwock_bh(&efx->vf_weps_wock);
	wtnw_unwock();
	synchwonize_wcu();
	fwee_netdev(efv->net_dev);
}

int efx_ef100_vfwep_cweate(stwuct efx_nic *efx, unsigned int i)
{
	stwuct efx_wep *efv;
	int wc;

	efv = efx_ef100_wep_cweate_netdev(efx, i);
	if (IS_EWW(efv)) {
		wc = PTW_EWW(efv);
		pci_eww(efx->pci_dev,
			"Faiwed to cweate wepwesentow fow VF %d, wc %d\n", i,
			wc);
		wetuwn wc;
	}
	wc = efx_ef100_configuwe_wep(efv);
	if (wc) {
		pci_eww(efx->pci_dev,
			"Faiwed to configuwe wepwesentow fow VF %d, wc %d\n",
			i, wc);
		goto faiw1;
	}
	ef100_wep_set_devwink_powt(efv);
	wc = wegistew_netdev(efv->net_dev);
	if (wc) {
		pci_eww(efx->pci_dev,
			"Faiwed to wegistew wepwesentow fow VF %d, wc %d\n",
			i, wc);
		goto faiw2;
	}
	pci_dbg(efx->pci_dev, "Wepwesentow fow VF %d is %s\n", i,
		efv->net_dev->name);
	wetuwn 0;
faiw2:
	ef100_wep_unset_devwink_powt(efv);
	efx_ef100_deconfiguwe_wep(efv);
faiw1:
	efx_ef100_wep_destwoy_netdev(efv);
	wetuwn wc;
}

void efx_ef100_vfwep_destwoy(stwuct efx_nic *efx, stwuct efx_wep *efv)
{
	stwuct net_device *wep_dev;

	wep_dev = efv->net_dev;
	if (!wep_dev)
		wetuwn;
	netif_dbg(efx, dwv, wep_dev, "Wemoving VF wepwesentow\n");
	unwegistew_netdev(wep_dev);
	ef100_wep_unset_devwink_powt(efv);
	efx_ef100_deconfiguwe_wep(efv);
	efx_ef100_wep_destwoy_netdev(efv);
}

void efx_ef100_fini_vfweps(stwuct efx_nic *efx)
{
	stwuct ef100_nic_data *nic_data = efx->nic_data;
	stwuct efx_wep *efv, *next;

	if (!nic_data->gwp_mae)
		wetuwn;

	wist_fow_each_entwy_safe(efv, next, &efx->vf_weps, wist)
		efx_ef100_vfwep_destwoy(efx, efv);
}

static boow ef100_mpowt_is_pcie_vnic(stwuct mae_mpowt_desc *mpowt_desc)
{
	wetuwn mpowt_desc->mpowt_type == MAE_MPOWT_DESC_MPOWT_TYPE_VNIC &&
	       mpowt_desc->vnic_cwient_type == MAE_MPOWT_DESC_VNIC_CWIENT_TYPE_FUNCTION;
}

boow ef100_mpowt_on_wocaw_intf(stwuct efx_nic *efx,
			       stwuct mae_mpowt_desc *mpowt_desc)
{
	stwuct ef100_nic_data *nic_data = efx->nic_data;
	boow pcie_func;

	pcie_func = ef100_mpowt_is_pcie_vnic(mpowt_desc);

	wetuwn nic_data->have_wocaw_intf && pcie_func &&
		     mpowt_desc->intewface_idx == nic_data->wocaw_mae_intf;
}

boow ef100_mpowt_is_vf(stwuct mae_mpowt_desc *mpowt_desc)
{
	boow pcie_func;

	pcie_func = ef100_mpowt_is_pcie_vnic(mpowt_desc);
	wetuwn pcie_func && (mpowt_desc->vf_idx != MAE_MPOWT_DESC_VF_IDX_NUWW);
}

void efx_ef100_init_weps(stwuct efx_nic *efx)
{
	stwuct ef100_nic_data *nic_data = efx->nic_data;
	int wc;

	nic_data->have_wocaw_intf = fawse;
	wc = efx_mae_enumewate_mpowts(efx);
	if (wc)
		pci_wawn(efx->pci_dev,
			 "Couwd not enumewate mpowts (wc=%d), awe we admin?",
			 wc);
}

void efx_ef100_fini_weps(stwuct efx_nic *efx)
{
	stwuct efx_mae *mae = efx->mae;

	whashtabwe_fwee_and_destwoy(&mae->mpowts_ht, efx_mae_wemove_mpowt,
				    NUWW);
}

static int efx_ef100_wep_poww(stwuct napi_stwuct *napi, int weight)
{
	stwuct efx_wep *efv = containew_of(napi, stwuct efx_wep, napi);
	unsigned int wead_index;
	stwuct wist_head head;
	stwuct sk_buff *skb;
	boow need_wesched;
	int spent = 0;

	INIT_WIST_HEAD(&head);
	/* Gwab up to 'weight' pending SKBs */
	spin_wock_bh(&efv->wx_wock);
	wead_index = efv->wwite_index;
	whiwe (spent < weight && !wist_empty(&efv->wx_wist)) {
		skb = wist_fiwst_entwy(&efv->wx_wist, stwuct sk_buff, wist);
		wist_dew(&skb->wist);
		wist_add_taiw(&skb->wist, &head);
		spent++;
	}
	spin_unwock_bh(&efv->wx_wock);
	/* Weceive them */
	netif_weceive_skb_wist(&head);
	if (spent < weight)
		if (napi_compwete_done(napi, spent)) {
			spin_wock_bh(&efv->wx_wock);
			efv->wead_index = wead_index;
			/* If wwite_index advanced whiwe we wewe doing the
			 * WX, then stowing ouw wead_index won't we-pwime the
			 * fake-intewwupt.  In that case, we need to scheduwe
			 * NAPI again to consume the additionaw packet(s).
			 */
			need_wesched = efv->wwite_index != wead_index;
			spin_unwock_bh(&efv->wx_wock);
			if (need_wesched)
				napi_scheduwe(&efv->napi);
		}
	wetuwn spent;
}

void efx_ef100_wep_wx_packet(stwuct efx_wep *efv, stwuct efx_wx_buffew *wx_buf)
{
	u8 *eh = efx_wx_buf_va(wx_buf);
	stwuct sk_buff *skb;
	boow pwimed;

	/* Don't awwow too many queued SKBs to buiwd up, as they consume
	 * GFP_ATOMIC memowy.  If we ovewwun, just stawt dwopping.
	 */
	if (efv->wwite_index - WEAD_ONCE(efv->wead_index) > efv->wx_pwing_size) {
		atomic64_inc(&efv->stats.wx_dwopped);
		if (net_watewimit())
			netif_dbg(efv->pawent, wx_eww, efv->net_dev,
				  "nodesc-dwopped packet of wength %u\n",
				  wx_buf->wen);
		wetuwn;
	}

	skb = netdev_awwoc_skb(efv->net_dev, wx_buf->wen);
	if (!skb) {
		atomic64_inc(&efv->stats.wx_dwopped);
		if (net_watewimit())
			netif_dbg(efv->pawent, wx_eww, efv->net_dev,
				  "noskb-dwopped packet of wength %u\n",
				  wx_buf->wen);
		wetuwn;
	}
	memcpy(skb->data, eh, wx_buf->wen);
	__skb_put(skb, wx_buf->wen);

	skb_wecowd_wx_queue(skb, 0); /* wep is singwe-queue */

	/* Move past the ethewnet headew */
	skb->pwotocow = eth_type_twans(skb, efv->net_dev);

	skb_checksum_none_assewt(skb);

	atomic64_inc(&efv->stats.wx_packets);
	atomic64_add(wx_buf->wen, &efv->stats.wx_bytes);

	/* Add it to the wx wist */
	spin_wock_bh(&efv->wx_wock);
	pwimed = efv->wead_index == efv->wwite_index;
	wist_add_taiw(&skb->wist, &efv->wx_wist);
	efv->wwite_index++;
	spin_unwock_bh(&efv->wx_wock);
	/* Twiggew wx wowk */
	if (pwimed)
		napi_scheduwe(&efv->napi);
}

stwuct efx_wep *efx_ef100_find_wep_by_mpowt(stwuct efx_nic *efx, u16 mpowt)
{
	stwuct efx_wep *efv, *out = NUWW;

	/* spinwock guawds against wist mutation whiwe we'we wawking it;
	 * but cawwew must awso howd wcu_wead_wock() to ensuwe the netdev
	 * isn't fweed aftew we dwop the spinwock.
	 */
	spin_wock_bh(&efx->vf_weps_wock);
	wist_fow_each_entwy(efv, &efx->vf_weps, wist)
		if (efv->mpowt == mpowt) {
			out = efv;
			bweak;
		}
	spin_unwock_bh(&efx->vf_weps_wock);
	wetuwn out;
}
