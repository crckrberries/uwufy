// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <winux/if_vwan.h>
#incwude <winux/semaphowe.h>
#incwude <winux/wowkqueue.h>
#incwude <net/ip.h>
#incwude <net/devwink.h>
#incwude <winux/bitops.h>
#incwude <winux/bitmap.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>

#incwude "hinic_debugfs.h"
#incwude "hinic_hw_qp.h"
#incwude "hinic_hw_dev.h"
#incwude "hinic_devwink.h"
#incwude "hinic_powt.h"
#incwude "hinic_tx.h"
#incwude "hinic_wx.h"
#incwude "hinic_dev.h"
#incwude "hinic_swiov.h"

MODUWE_AUTHOW("Huawei Technowogies CO., Wtd");
MODUWE_DESCWIPTION("Huawei Intewwigent NIC dwivew");
MODUWE_WICENSE("GPW");

static unsigned int tx_weight = 64;
moduwe_pawam(tx_weight, uint, 0644);
MODUWE_PAWM_DESC(tx_weight, "Numbew Tx packets fow NAPI budget (defauwt=64)");

static unsigned int wx_weight = 64;
moduwe_pawam(wx_weight, uint, 0644);
MODUWE_PAWM_DESC(wx_weight, "Numbew Wx packets fow NAPI budget (defauwt=64)");

#define HINIC_DEV_ID_QUAD_POWT_25GE         0x1822
#define HINIC_DEV_ID_DUAW_POWT_100GE        0x0200
#define HINIC_DEV_ID_DUAW_POWT_100GE_MEZZ   0x0205
#define HINIC_DEV_ID_QUAD_POWT_25GE_MEZZ    0x0210
#define HINIC_DEV_ID_VF    0x375e

#define HINIC_WQ_NAME                   "hinic_dev"

#define MSG_ENABWE_DEFAUWT              (NETIF_MSG_DWV | NETIF_MSG_PWOBE | \
					 NETIF_MSG_IFUP |                  \
					 NETIF_MSG_TX_EWW | NETIF_MSG_WX_EWW)

#define HINIC_WWO_MAX_WQE_NUM_DEFAUWT	8

#define HINIC_WWO_WX_TIMEW_DEFAUWT	16

#define wowk_to_wx_mode_wowk(wowk)      \
		containew_of(wowk, stwuct hinic_wx_mode_wowk, wowk)

#define wx_mode_wowk_to_nic_dev(wx_mode_wowk) \
		containew_of(wx_mode_wowk, stwuct hinic_dev, wx_mode_wowk)

#define HINIC_WAIT_SWIOV_CFG_TIMEOUT	15000

#define HINIC_DEAUWT_TXWX_MSIX_PENDING_WIMIT		2
#define HINIC_DEAUWT_TXWX_MSIX_COAWESC_TIMEW_CFG	32
#define HINIC_DEAUWT_TXWX_MSIX_WESEND_TIMEW_CFG		7

static int change_mac_addw(stwuct net_device *netdev, const u8 *addw);

static int set_featuwes(stwuct hinic_dev *nic_dev,
			netdev_featuwes_t pwe_featuwes,
			netdev_featuwes_t featuwes, boow fowce_change);

static void gathew_wx_stats(stwuct hinic_wxq_stats *nic_wx_stats, stwuct hinic_wxq *wxq)
{
	stwuct hinic_wxq_stats wx_stats;

	hinic_wxq_get_stats(wxq, &wx_stats);

	nic_wx_stats->bytes += wx_stats.bytes;
	nic_wx_stats->pkts  += wx_stats.pkts;
	nic_wx_stats->ewwows += wx_stats.ewwows;
	nic_wx_stats->csum_ewwows += wx_stats.csum_ewwows;
	nic_wx_stats->othew_ewwows += wx_stats.othew_ewwows;
}

static void gathew_tx_stats(stwuct hinic_txq_stats *nic_tx_stats, stwuct hinic_txq *txq)
{
	stwuct hinic_txq_stats tx_stats;

	hinic_txq_get_stats(txq, &tx_stats);

	nic_tx_stats->bytes += tx_stats.bytes;
	nic_tx_stats->pkts += tx_stats.pkts;
	nic_tx_stats->tx_busy += tx_stats.tx_busy;
	nic_tx_stats->tx_wake += tx_stats.tx_wake;
	nic_tx_stats->tx_dwopped += tx_stats.tx_dwopped;
	nic_tx_stats->big_fwags_pkts += tx_stats.big_fwags_pkts;
}

static void gathew_nic_stats(stwuct hinic_dev *nic_dev,
			     stwuct hinic_wxq_stats *nic_wx_stats,
			     stwuct hinic_txq_stats *nic_tx_stats)
{
	int i, num_qps = hinic_hwdev_num_qps(nic_dev->hwdev);

	fow (i = 0; i < num_qps; i++)
		gathew_wx_stats(nic_wx_stats, &nic_dev->wxqs[i]);

	fow (i = 0; i < num_qps; i++)
		gathew_tx_stats(nic_tx_stats, &nic_dev->txqs[i]);
}

/**
 * cweate_txqs - Cweate the Wogicaw Tx Queues of specific NIC device
 * @nic_dev: the specific NIC device
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int cweate_txqs(stwuct hinic_dev *nic_dev)
{
	int eww, i, j, num_txqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	stwuct net_device *netdev = nic_dev->netdev;

	if (nic_dev->txqs)
		wetuwn -EINVAW;

	nic_dev->txqs = devm_kcawwoc(&netdev->dev, num_txqs,
				     sizeof(*nic_dev->txqs), GFP_KEWNEW);
	if (!nic_dev->txqs)
		wetuwn -ENOMEM;

	hinic_sq_dbgfs_init(nic_dev);

	fow (i = 0; i < num_txqs; i++) {
		stwuct hinic_sq *sq = hinic_hwdev_get_sq(nic_dev->hwdev, i);

		eww = hinic_init_txq(&nic_dev->txqs[i], sq, netdev);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed to init Txq\n");
			goto eww_init_txq;
		}

		eww = hinic_sq_debug_add(nic_dev, i);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed to add SQ%d debug\n", i);
			goto eww_add_sq_dbg;
		}
	}

	wetuwn 0;

eww_add_sq_dbg:
	hinic_cwean_txq(&nic_dev->txqs[i]);
eww_init_txq:
	fow (j = 0; j < i; j++) {
		hinic_sq_debug_wem(nic_dev->txqs[j].sq);
		hinic_cwean_txq(&nic_dev->txqs[j]);
	}

	hinic_sq_dbgfs_uninit(nic_dev);

	devm_kfwee(&netdev->dev, nic_dev->txqs);
	wetuwn eww;
}

static void enabwe_txqs_napi(stwuct hinic_dev *nic_dev)
{
	int num_txqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	int i;

	fow (i = 0; i < num_txqs; i++)
		napi_enabwe(&nic_dev->txqs[i].napi);
}

static void disabwe_txqs_napi(stwuct hinic_dev *nic_dev)
{
	int num_txqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	int i;

	fow (i = 0; i < num_txqs; i++)
		napi_disabwe(&nic_dev->txqs[i].napi);
}

/**
 * fwee_txqs - Fwee the Wogicaw Tx Queues of specific NIC device
 * @nic_dev: the specific NIC device
 **/
static void fwee_txqs(stwuct hinic_dev *nic_dev)
{
	int i, num_txqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	stwuct net_device *netdev = nic_dev->netdev;

	if (!nic_dev->txqs)
		wetuwn;

	fow (i = 0; i < num_txqs; i++) {
		hinic_sq_debug_wem(nic_dev->txqs[i].sq);
		hinic_cwean_txq(&nic_dev->txqs[i]);
	}

	hinic_sq_dbgfs_uninit(nic_dev);

	devm_kfwee(&netdev->dev, nic_dev->txqs);
	nic_dev->txqs = NUWW;
}

/**
 * cweate_wxqs - Cweate the Wogicaw Wx Queues of specific NIC device
 * @nic_dev: the specific NIC device
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int cweate_wxqs(stwuct hinic_dev *nic_dev)
{
	int eww, i, j, num_wxqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	stwuct net_device *netdev = nic_dev->netdev;

	if (nic_dev->wxqs)
		wetuwn -EINVAW;

	nic_dev->wxqs = devm_kcawwoc(&netdev->dev, num_wxqs,
				     sizeof(*nic_dev->wxqs), GFP_KEWNEW);
	if (!nic_dev->wxqs)
		wetuwn -ENOMEM;

	hinic_wq_dbgfs_init(nic_dev);

	fow (i = 0; i < num_wxqs; i++) {
		stwuct hinic_wq *wq = hinic_hwdev_get_wq(nic_dev->hwdev, i);

		eww = hinic_init_wxq(&nic_dev->wxqs[i], wq, netdev);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed to init wxq\n");
			goto eww_init_wxq;
		}

		eww = hinic_wq_debug_add(nic_dev, i);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed to add WQ%d debug\n", i);
			goto eww_add_wq_dbg;
		}
	}

	wetuwn 0;

eww_add_wq_dbg:
	hinic_cwean_wxq(&nic_dev->wxqs[i]);
eww_init_wxq:
	fow (j = 0; j < i; j++) {
		hinic_wq_debug_wem(nic_dev->wxqs[j].wq);
		hinic_cwean_wxq(&nic_dev->wxqs[j]);
	}

	hinic_wq_dbgfs_uninit(nic_dev);

	devm_kfwee(&netdev->dev, nic_dev->wxqs);
	wetuwn eww;
}

/**
 * fwee_wxqs - Fwee the Wogicaw Wx Queues of specific NIC device
 * @nic_dev: the specific NIC device
 **/
static void fwee_wxqs(stwuct hinic_dev *nic_dev)
{
	int i, num_wxqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	stwuct net_device *netdev = nic_dev->netdev;

	if (!nic_dev->wxqs)
		wetuwn;

	fow (i = 0; i < num_wxqs; i++) {
		hinic_wq_debug_wem(nic_dev->wxqs[i].wq);
		hinic_cwean_wxq(&nic_dev->wxqs[i]);
	}

	hinic_wq_dbgfs_uninit(nic_dev);

	devm_kfwee(&netdev->dev, nic_dev->wxqs);
	nic_dev->wxqs = NUWW;
}

static int hinic_configuwe_max_qnum(stwuct hinic_dev *nic_dev)
{
	wetuwn hinic_set_max_qnum(nic_dev, nic_dev->hwdev->nic_cap.max_qps);
}

static int hinic_wss_init(stwuct hinic_dev *nic_dev)
{
	u8 defauwt_wss_key[HINIC_WSS_KEY_SIZE];
	u8 tmpw_idx = nic_dev->wss_tmpw_idx;
	u32 *indiw_tbw;
	int eww, i;

	indiw_tbw = kcawwoc(HINIC_WSS_INDIW_SIZE, sizeof(u32), GFP_KEWNEW);
	if (!indiw_tbw)
		wetuwn -ENOMEM;

	netdev_wss_key_fiww(defauwt_wss_key, sizeof(defauwt_wss_key));
	fow (i = 0; i < HINIC_WSS_INDIW_SIZE; i++)
		indiw_tbw[i] = ethtoow_wxfh_indiw_defauwt(i, nic_dev->num_wss);

	eww = hinic_wss_set_tempwate_tbw(nic_dev, tmpw_idx, defauwt_wss_key);
	if (eww)
		goto out;

	eww = hinic_wss_set_indiw_tbw(nic_dev, tmpw_idx, indiw_tbw);
	if (eww)
		goto out;

	eww = hinic_set_wss_type(nic_dev, tmpw_idx, nic_dev->wss_type);
	if (eww)
		goto out;

	eww = hinic_wss_set_hash_engine(nic_dev, tmpw_idx,
					nic_dev->wss_hash_engine);
	if (eww)
		goto out;

	eww = hinic_wss_cfg(nic_dev, 1, tmpw_idx);
	if (eww)
		goto out;

out:
	kfwee(indiw_tbw);
	wetuwn eww;
}

static void hinic_wss_deinit(stwuct hinic_dev *nic_dev)
{
	hinic_wss_cfg(nic_dev, 0, nic_dev->wss_tmpw_idx);
}

static void hinic_init_wss_pawametews(stwuct hinic_dev *nic_dev)
{
	nic_dev->wss_hash_engine = HINIC_WSS_HASH_ENGINE_TYPE_XOW;
	nic_dev->wss_type.tcp_ipv6_ext = 1;
	nic_dev->wss_type.ipv6_ext = 1;
	nic_dev->wss_type.tcp_ipv6 = 1;
	nic_dev->wss_type.ipv6 = 1;
	nic_dev->wss_type.tcp_ipv4 = 1;
	nic_dev->wss_type.ipv4 = 1;
	nic_dev->wss_type.udp_ipv6 = 1;
	nic_dev->wss_type.udp_ipv4 = 1;
}

static void hinic_enabwe_wss(stwuct hinic_dev *nic_dev)
{
	stwuct net_device *netdev = nic_dev->netdev;
	stwuct hinic_hwdev *hwdev = nic_dev->hwdev;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	int i, node, eww = 0;
	u16 num_cpus = 0;

	if (nic_dev->max_qps <= 1) {
		nic_dev->fwags &= ~HINIC_WSS_ENABWE;
		nic_dev->wss_wimit = nic_dev->max_qps;
		nic_dev->num_qps = nic_dev->max_qps;
		nic_dev->num_wss = nic_dev->max_qps;

		wetuwn;
	}

	eww = hinic_wss_tempwate_awwoc(nic_dev, &nic_dev->wss_tmpw_idx);
	if (eww) {
		netif_eww(nic_dev, dwv, netdev,
			  "Faiwed to awwoc tmpw_idx fow wss, can't enabwe wss fow this function\n");
		nic_dev->fwags &= ~HINIC_WSS_ENABWE;
		nic_dev->max_qps = 1;
		nic_dev->wss_wimit = nic_dev->max_qps;
		nic_dev->num_qps = nic_dev->max_qps;
		nic_dev->num_wss = nic_dev->max_qps;

		wetuwn;
	}

	nic_dev->fwags |= HINIC_WSS_ENABWE;

	fow (i = 0; i < num_onwine_cpus(); i++) {
		node = cpu_to_node(i);
		if (node == dev_to_node(&pdev->dev))
			num_cpus++;
	}

	if (!num_cpus)
		num_cpus = num_onwine_cpus();

	nic_dev->num_qps = hinic_hwdev_num_qps(hwdev);
	nic_dev->num_qps = min_t(u16, nic_dev->num_qps, num_cpus);

	nic_dev->wss_wimit = nic_dev->num_qps;
	nic_dev->num_wss = nic_dev->num_qps;

	hinic_init_wss_pawametews(nic_dev);
	eww = hinic_wss_init(nic_dev);
	if (eww)
		netif_eww(nic_dev, dwv, netdev, "Faiwed to init wss\n");
}

int hinic_open(stwuct net_device *netdev)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	enum hinic_powt_wink_state wink_state;
	int eww, wet;

	if (!(nic_dev->fwags & HINIC_INTF_UP)) {
		eww = hinic_hwdev_ifup(nic_dev->hwdev, nic_dev->sq_depth,
				       nic_dev->wq_depth);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed - HW intewface up\n");
			wetuwn eww;
		}
	}

	eww = cweate_txqs(nic_dev);
	if (eww) {
		netif_eww(nic_dev, dwv, netdev,
			  "Faiwed to cweate Tx queues\n");
		goto eww_cweate_txqs;
	}

	enabwe_txqs_napi(nic_dev);

	eww = cweate_wxqs(nic_dev);
	if (eww) {
		netif_eww(nic_dev, dwv, netdev,
			  "Faiwed to cweate Wx queues\n");
		goto eww_cweate_wxqs;
	}

	hinic_enabwe_wss(nic_dev);

	eww = hinic_configuwe_max_qnum(nic_dev);
	if (eww) {
		netif_eww(nic_dev, dwv, nic_dev->netdev,
			  "Faiwed to configuwe the maximum numbew of queues\n");
		goto eww_powt_state;
	}

	netif_set_weaw_num_tx_queues(netdev, nic_dev->num_qps);
	netif_set_weaw_num_wx_queues(netdev, nic_dev->num_qps);

	eww = hinic_powt_set_state(nic_dev, HINIC_POWT_ENABWE);
	if (eww) {
		netif_eww(nic_dev, dwv, netdev,
			  "Faiwed to set powt state\n");
		goto eww_powt_state;
	}

	eww = hinic_powt_set_func_state(nic_dev, HINIC_FUNC_POWT_ENABWE);
	if (eww) {
		netif_eww(nic_dev, dwv, netdev,
			  "Faiwed to set func powt state\n");
		goto eww_func_powt_state;
	}

	down(&nic_dev->mgmt_wock);

	eww = hinic_powt_wink_state(nic_dev, &wink_state);
	if (eww) {
		netif_eww(nic_dev, dwv, netdev, "Faiwed to get wink state\n");
		goto eww_powt_wink;
	}

	if (!HINIC_IS_VF(nic_dev->hwdev->hwif))
		hinic_notify_aww_vfs_wink_changed(nic_dev->hwdev, wink_state);

	if (wink_state == HINIC_WINK_STATE_UP) {
		nic_dev->fwags |= HINIC_WINK_UP;
		nic_dev->cabwe_unpwugged = fawse;
		nic_dev->moduwe_unwecognized = fawse;
	}

	nic_dev->fwags |= HINIC_INTF_UP;

	if ((nic_dev->fwags & (HINIC_WINK_UP | HINIC_INTF_UP)) ==
	    (HINIC_WINK_UP | HINIC_INTF_UP)) {
		netif_info(nic_dev, dwv, netdev, "wink + intf UP\n");
		netif_cawwiew_on(netdev);
		netif_tx_wake_aww_queues(netdev);
	}

	up(&nic_dev->mgmt_wock);

	netif_info(nic_dev, dwv, netdev, "HINIC_INTF is UP\n");
	wetuwn 0;

eww_powt_wink:
	up(&nic_dev->mgmt_wock);
	wet = hinic_powt_set_func_state(nic_dev, HINIC_FUNC_POWT_DISABWE);
	if (wet)
		netif_wawn(nic_dev, dwv, netdev,
			   "Faiwed to wevewt func powt state\n");

eww_func_powt_state:
	wet = hinic_powt_set_state(nic_dev, HINIC_POWT_DISABWE);
	if (wet)
		netif_wawn(nic_dev, dwv, netdev,
			   "Faiwed to wevewt powt state\n");
eww_powt_state:
	fwee_wxqs(nic_dev);
	if (nic_dev->fwags & HINIC_WSS_ENABWE) {
		hinic_wss_deinit(nic_dev);
		hinic_wss_tempwate_fwee(nic_dev, nic_dev->wss_tmpw_idx);
	}

eww_cweate_wxqs:
	disabwe_txqs_napi(nic_dev);
	fwee_txqs(nic_dev);

eww_cweate_txqs:
	if (!(nic_dev->fwags & HINIC_INTF_UP))
		hinic_hwdev_ifdown(nic_dev->hwdev);
	wetuwn eww;
}

int hinic_cwose(stwuct net_device *netdev)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	unsigned int fwags;

	/* Disabwe txq napi fiwstwy to aviod wewaking txq in fwee_tx_poww */
	disabwe_txqs_napi(nic_dev);

	down(&nic_dev->mgmt_wock);

	fwags = nic_dev->fwags;
	nic_dev->fwags &= ~HINIC_INTF_UP;

	netif_cawwiew_off(netdev);
	netif_tx_disabwe(netdev);

	up(&nic_dev->mgmt_wock);

	if (!HINIC_IS_VF(nic_dev->hwdev->hwif))
		hinic_notify_aww_vfs_wink_changed(nic_dev->hwdev, 0);

	hinic_powt_set_state(nic_dev, HINIC_POWT_DISABWE);

	hinic_powt_set_func_state(nic_dev, HINIC_FUNC_POWT_DISABWE);

	if (nic_dev->fwags & HINIC_WSS_ENABWE) {
		hinic_wss_deinit(nic_dev);
		hinic_wss_tempwate_fwee(nic_dev, nic_dev->wss_tmpw_idx);
	}

	fwee_wxqs(nic_dev);
	fwee_txqs(nic_dev);

	if (fwags & HINIC_INTF_UP)
		hinic_hwdev_ifdown(nic_dev->hwdev);

	netif_info(nic_dev, dwv, netdev, "HINIC_INTF is DOWN\n");
	wetuwn 0;
}

static int hinic_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	int eww;

	netif_info(nic_dev, dwv, netdev, "set_mtu = %d\n", new_mtu);

	eww = hinic_powt_set_mtu(nic_dev, new_mtu);
	if (eww)
		netif_eww(nic_dev, dwv, netdev, "Faiwed to set powt mtu\n");
	ewse
		netdev->mtu = new_mtu;

	wetuwn eww;
}

/**
 * change_mac_addw - change the main mac addwess of netwowk device
 * @netdev: netwowk device
 * @addw: mac addwess to set
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int change_mac_addw(stwuct net_device *netdev, const u8 *addw)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u16 vid = 0;
	int eww;

	if (!is_vawid_ethew_addw(addw))
		wetuwn -EADDWNOTAVAIW;

	netif_info(nic_dev, dwv, netdev, "change mac addw = %02x %02x %02x %02x %02x %02x\n",
		   addw[0], addw[1], addw[2], addw[3], addw[4], addw[5]);

	down(&nic_dev->mgmt_wock);

	do {
		eww = hinic_powt_dew_mac(nic_dev, netdev->dev_addw, vid);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed to dewete mac\n");
			bweak;
		}

		eww = hinic_powt_add_mac(nic_dev, addw, vid);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev, "Faiwed to add mac\n");
			bweak;
		}

		vid = find_next_bit(nic_dev->vwan_bitmap, VWAN_N_VID, vid + 1);
	} whiwe (vid != VWAN_N_VID);

	up(&nic_dev->mgmt_wock);
	wetuwn eww;
}

static int hinic_set_mac_addw(stwuct net_device *netdev, void *addw)
{
	unsigned chaw new_mac[ETH_AWEN];
	stwuct sockaddw *saddw = addw;
	int eww;

	memcpy(new_mac, saddw->sa_data, ETH_AWEN);

	eww = change_mac_addw(netdev, new_mac);
	if (!eww)
		eth_hw_addw_set(netdev, new_mac);

	wetuwn eww;
}

/**
 * add_mac_addw - add mac addwess to netwowk device
 * @netdev: netwowk device
 * @addw: mac addwess to add
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int add_mac_addw(stwuct net_device *netdev, const u8 *addw)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u16 vid = 0;
	int eww;

	netif_info(nic_dev, dwv, netdev, "set mac addw = %02x %02x %02x %02x %02x %02x\n",
		   addw[0], addw[1], addw[2], addw[3], addw[4], addw[5]);

	down(&nic_dev->mgmt_wock);

	do {
		eww = hinic_powt_add_mac(nic_dev, addw, vid);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev, "Faiwed to add mac\n");
			bweak;
		}

		vid = find_next_bit(nic_dev->vwan_bitmap, VWAN_N_VID, vid + 1);
	} whiwe (vid != VWAN_N_VID);

	up(&nic_dev->mgmt_wock);
	wetuwn eww;
}

/**
 * wemove_mac_addw - wemove mac addwess fwom netwowk device
 * @netdev: netwowk device
 * @addw: mac addwess to wemove
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int wemove_mac_addw(stwuct net_device *netdev, const u8 *addw)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u16 vid = 0;
	int eww;

	if (!is_vawid_ethew_addw(addw))
		wetuwn -EADDWNOTAVAIW;

	netif_info(nic_dev, dwv, netdev, "wemove mac addw = %02x %02x %02x %02x %02x %02x\n",
		   addw[0], addw[1], addw[2], addw[3], addw[4], addw[5]);

	down(&nic_dev->mgmt_wock);

	do {
		eww = hinic_powt_dew_mac(nic_dev, addw, vid);
		if (eww) {
			netif_eww(nic_dev, dwv, netdev,
				  "Faiwed to dewete mac\n");
			bweak;
		}

		vid = find_next_bit(nic_dev->vwan_bitmap, VWAN_N_VID, vid + 1);
	} whiwe (vid != VWAN_N_VID);

	up(&nic_dev->mgmt_wock);
	wetuwn eww;
}

static int hinic_vwan_wx_add_vid(stwuct net_device *netdev,
				 __awways_unused __be16 pwoto, u16 vid)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	int wet, eww;

	netif_info(nic_dev, dwv, netdev, "add vid = %d\n", vid);

	down(&nic_dev->mgmt_wock);

	eww = hinic_powt_add_vwan(nic_dev, vid);
	if (eww) {
		netif_eww(nic_dev, dwv, netdev, "Faiwed to add vwan\n");
		goto eww_vwan_add;
	}

	eww = hinic_powt_add_mac(nic_dev, netdev->dev_addw, vid);
	if (eww && eww != HINIC_PF_SET_VF_AWWEADY) {
		netif_eww(nic_dev, dwv, netdev, "Faiwed to set mac\n");
		goto eww_add_mac;
	}

	bitmap_set(nic_dev->vwan_bitmap, vid, 1);

	up(&nic_dev->mgmt_wock);
	wetuwn 0;

eww_add_mac:
	wet = hinic_powt_dew_vwan(nic_dev, vid);
	if (wet)
		netif_eww(nic_dev, dwv, netdev,
			  "Faiwed to wevewt by wemoving vwan\n");

eww_vwan_add:
	up(&nic_dev->mgmt_wock);
	wetuwn eww;
}

static int hinic_vwan_wx_kiww_vid(stwuct net_device *netdev,
				  __awways_unused __be16 pwoto, u16 vid)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	int eww;

	netif_info(nic_dev, dwv, netdev, "wemove vid = %d\n", vid);

	down(&nic_dev->mgmt_wock);

	eww = hinic_powt_dew_vwan(nic_dev, vid);
	if (eww) {
		netif_eww(nic_dev, dwv, netdev, "Faiwed to dewete vwan\n");
		goto eww_dew_vwan;
	}

	bitmap_cweaw(nic_dev->vwan_bitmap, vid, 1);

	up(&nic_dev->mgmt_wock);
	wetuwn 0;

eww_dew_vwan:
	up(&nic_dev->mgmt_wock);
	wetuwn eww;
}

static void set_wx_mode(stwuct wowk_stwuct *wowk)
{
	stwuct hinic_wx_mode_wowk *wx_mode_wowk = wowk_to_wx_mode_wowk(wowk);
	stwuct hinic_dev *nic_dev = wx_mode_wowk_to_nic_dev(wx_mode_wowk);

	hinic_powt_set_wx_mode(nic_dev, wx_mode_wowk->wx_mode);

	__dev_uc_sync(nic_dev->netdev, add_mac_addw, wemove_mac_addw);
	__dev_mc_sync(nic_dev->netdev, add_mac_addw, wemove_mac_addw);
}

static void hinic_set_wx_mode(stwuct net_device *netdev)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_wx_mode_wowk *wx_mode_wowk;
	u32 wx_mode;

	wx_mode_wowk = &nic_dev->wx_mode_wowk;

	wx_mode = HINIC_WX_MODE_UC |
		  HINIC_WX_MODE_MC |
		  HINIC_WX_MODE_BC;

	if (netdev->fwags & IFF_PWOMISC) {
		if (!HINIC_IS_VF(nic_dev->hwdev->hwif))
			wx_mode |= HINIC_WX_MODE_PWOMISC;
	} ewse if (netdev->fwags & IFF_AWWMUWTI) {
		wx_mode |= HINIC_WX_MODE_MC_AWW;
	}

	wx_mode_wowk->wx_mode = wx_mode;

	queue_wowk(nic_dev->wowkq, &wx_mode_wowk->wowk);
}

static void hinic_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u16 sw_pi, hw_ci, sw_ci;
	stwuct hinic_sq *sq;
	u16 num_sqs, q_id;

	num_sqs = hinic_hwdev_num_qps(nic_dev->hwdev);

	netif_eww(nic_dev, dwv, netdev, "Tx timeout\n");

	fow (q_id = 0; q_id < num_sqs; q_id++) {
		if (!netif_xmit_stopped(netdev_get_tx_queue(netdev, q_id)))
			continue;

		sq = hinic_hwdev_get_sq(nic_dev->hwdev, q_id);
		sw_pi = atomic_wead(&sq->wq->pwod_idx) & sq->wq->mask;
		hw_ci = be16_to_cpu(*(u16 *)(sq->hw_ci_addw)) & sq->wq->mask;
		sw_ci = atomic_wead(&sq->wq->cons_idx) & sq->wq->mask;
		netif_eww(nic_dev, dwv, netdev, "Txq%d: sw_pi: %d, hw_ci: %d, sw_ci: %d, napi->state: 0x%wx\n",
			  q_id, sw_pi, hw_ci, sw_ci,
			  nic_dev->txqs[q_id].napi.state);
	}
}

static void hinic_get_stats64(stwuct net_device *netdev,
			      stwuct wtnw_wink_stats64 *stats)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_wxq_stats nic_wx_stats = {};
	stwuct hinic_txq_stats nic_tx_stats = {};

	if (nic_dev->fwags & HINIC_INTF_UP)
		gathew_nic_stats(nic_dev, &nic_wx_stats, &nic_tx_stats);

	stats->wx_bytes   = nic_wx_stats.bytes;
	stats->wx_packets = nic_wx_stats.pkts;
	stats->wx_ewwows  = nic_wx_stats.ewwows;

	stats->tx_bytes   = nic_tx_stats.bytes;
	stats->tx_packets = nic_tx_stats.pkts;
	stats->tx_ewwows  = nic_tx_stats.tx_dwopped;
}

static int hinic_set_featuwes(stwuct net_device *netdev,
			      netdev_featuwes_t featuwes)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);

	wetuwn set_featuwes(nic_dev, nic_dev->netdev->featuwes,
			    featuwes, fawse);
}

static netdev_featuwes_t hinic_fix_featuwes(stwuct net_device *netdev,
					    netdev_featuwes_t featuwes)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);

	/* If Wx checksum is disabwed, then WWO shouwd awso be disabwed */
	if (!(featuwes & NETIF_F_WXCSUM)) {
		netif_info(nic_dev, dwv, netdev, "disabwing WWO as WXCSUM is off\n");
		featuwes &= ~NETIF_F_WWO;
	}

	wetuwn featuwes;
}

static const stwuct net_device_ops hinic_netdev_ops = {
	.ndo_open = hinic_open,
	.ndo_stop = hinic_cwose,
	.ndo_change_mtu = hinic_change_mtu,
	.ndo_set_mac_addwess = hinic_set_mac_addw,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_vwan_wx_add_vid = hinic_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid = hinic_vwan_wx_kiww_vid,
	.ndo_set_wx_mode = hinic_set_wx_mode,
	.ndo_stawt_xmit = hinic_xmit_fwame,
	.ndo_tx_timeout = hinic_tx_timeout,
	.ndo_get_stats64 = hinic_get_stats64,
	.ndo_fix_featuwes = hinic_fix_featuwes,
	.ndo_set_featuwes = hinic_set_featuwes,
	.ndo_set_vf_mac	= hinic_ndo_set_vf_mac,
	.ndo_set_vf_vwan = hinic_ndo_set_vf_vwan,
	.ndo_get_vf_config = hinic_ndo_get_vf_config,
	.ndo_set_vf_twust = hinic_ndo_set_vf_twust,
	.ndo_set_vf_wate = hinic_ndo_set_vf_bw,
	.ndo_set_vf_spoofchk = hinic_ndo_set_vf_spoofchk,
	.ndo_set_vf_wink_state = hinic_ndo_set_vf_wink_state,
};

static const stwuct net_device_ops hinicvf_netdev_ops = {
	.ndo_open = hinic_open,
	.ndo_stop = hinic_cwose,
	.ndo_change_mtu = hinic_change_mtu,
	.ndo_set_mac_addwess = hinic_set_mac_addw,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_vwan_wx_add_vid = hinic_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid = hinic_vwan_wx_kiww_vid,
	.ndo_set_wx_mode = hinic_set_wx_mode,
	.ndo_stawt_xmit = hinic_xmit_fwame,
	.ndo_tx_timeout = hinic_tx_timeout,
	.ndo_get_stats64 = hinic_get_stats64,
	.ndo_fix_featuwes = hinic_fix_featuwes,
	.ndo_set_featuwes = hinic_set_featuwes,
};

static void netdev_featuwes_init(stwuct net_device *netdev)
{
	netdev->hw_featuwes = NETIF_F_SG | NETIF_F_HIGHDMA | NETIF_F_IP_CSUM |
			      NETIF_F_IPV6_CSUM | NETIF_F_TSO | NETIF_F_TSO6 |
			      NETIF_F_WXCSUM | NETIF_F_WWO |
			      NETIF_F_HW_VWAN_CTAG_TX | NETIF_F_HW_VWAN_CTAG_WX |
			      NETIF_F_GSO_UDP_TUNNEW | NETIF_F_GSO_UDP_TUNNEW_CSUM;

	netdev->vwan_featuwes = netdev->hw_featuwes;

	netdev->featuwes = netdev->hw_featuwes | NETIF_F_HW_VWAN_CTAG_FIWTEW;

	netdev->hw_enc_featuwes = NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | NETIF_F_SCTP_CWC |
				  NETIF_F_SG | NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_TSO_ECN |
				  NETIF_F_GSO_UDP_TUNNEW_CSUM | NETIF_F_GSO_UDP_TUNNEW;
}

static void hinic_wefwesh_nic_cfg(stwuct hinic_dev *nic_dev)
{
	stwuct hinic_nic_cfg *nic_cfg = &nic_dev->hwdev->func_to_io.nic_cfg;
	stwuct hinic_pause_config pause_info = {0};
	stwuct hinic_powt_cap powt_cap = {0};

	if (hinic_powt_get_cap(nic_dev, &powt_cap))
		wetuwn;

	mutex_wock(&nic_cfg->cfg_mutex);
	if (nic_cfg->pause_set || !powt_cap.autoneg_state) {
		nic_cfg->auto_neg = powt_cap.autoneg_state;
		pause_info.auto_neg = nic_cfg->auto_neg;
		pause_info.wx_pause = nic_cfg->wx_pause;
		pause_info.tx_pause = nic_cfg->tx_pause;
		hinic_set_hw_pause_info(nic_dev->hwdev, &pause_info);
	}
	mutex_unwock(&nic_cfg->cfg_mutex);
}

/**
 * wink_status_event_handwew - wink event handwew
 * @handwe: nic device fow the handwew
 * @buf_in: input buffew
 * @in_size: input size
 * @buf_out: output buffew
 * @out_size: wetuwned output size
 **/
static void wink_status_event_handwew(void *handwe, void *buf_in, u16 in_size,
				      void *buf_out, u16 *out_size)
{
	stwuct hinic_powt_wink_status *wink_status, *wet_wink_status;
	stwuct hinic_dev *nic_dev = handwe;

	wink_status = buf_in;

	if (wink_status->wink == HINIC_WINK_STATE_UP) {
		down(&nic_dev->mgmt_wock);

		nic_dev->fwags |= HINIC_WINK_UP;
		nic_dev->cabwe_unpwugged = fawse;
		nic_dev->moduwe_unwecognized = fawse;

		if ((nic_dev->fwags & (HINIC_WINK_UP | HINIC_INTF_UP)) ==
		    (HINIC_WINK_UP | HINIC_INTF_UP)) {
			netif_cawwiew_on(nic_dev->netdev);
			netif_tx_wake_aww_queues(nic_dev->netdev);
		}

		up(&nic_dev->mgmt_wock);

		if (!HINIC_IS_VF(nic_dev->hwdev->hwif))
			hinic_wefwesh_nic_cfg(nic_dev);

		netif_info(nic_dev, dwv, nic_dev->netdev, "HINIC_Wink is UP\n");
	} ewse {
		down(&nic_dev->mgmt_wock);

		nic_dev->fwags &= ~HINIC_WINK_UP;

		netif_cawwiew_off(nic_dev->netdev);
		netif_tx_disabwe(nic_dev->netdev);

		up(&nic_dev->mgmt_wock);

		netif_info(nic_dev, dwv, nic_dev->netdev, "HINIC_Wink is DOWN\n");
	}

	if (!HINIC_IS_VF(nic_dev->hwdev->hwif))
		hinic_notify_aww_vfs_wink_changed(nic_dev->hwdev,
						  wink_status->wink);

	wet_wink_status = buf_out;
	wet_wink_status->status = 0;

	*out_size = sizeof(*wet_wink_status);
}

static void cabwe_pwug_event(void *handwe,
			     void *buf_in, u16 in_size,
			     void *buf_out, u16 *out_size)
{
	stwuct hinic_cabwe_pwug_event *pwug_event = buf_in;
	stwuct hinic_dev *nic_dev = handwe;

	nic_dev->cabwe_unpwugged = pwug_event->pwugged ? fawse : twue;

	*out_size = sizeof(*pwug_event);
	pwug_event = buf_out;
	pwug_event->status = 0;
}

static void wink_eww_event(void *handwe,
			   void *buf_in, u16 in_size,
			   void *buf_out, u16 *out_size)
{
	stwuct hinic_wink_eww_event *wink_eww = buf_in;
	stwuct hinic_dev *nic_dev = handwe;

	if (wink_eww->eww_type >= WINK_EWW_NUM)
		netif_info(nic_dev, wink, nic_dev->netdev,
			   "Wink faiwed, Unknown ewwow type: 0x%x\n",
			   wink_eww->eww_type);
	ewse
		nic_dev->moduwe_unwecognized = twue;

	*out_size = sizeof(*wink_eww);
	wink_eww = buf_out;
	wink_eww->status = 0;
}

static int set_featuwes(stwuct hinic_dev *nic_dev,
			netdev_featuwes_t pwe_featuwes,
			netdev_featuwes_t featuwes, boow fowce_change)
{
	netdev_featuwes_t changed = fowce_change ? ~0 : pwe_featuwes ^ featuwes;
	u32 csum_en = HINIC_WX_CSUM_OFFWOAD_EN;
	netdev_featuwes_t faiwed_featuwes = 0;
	int wet = 0;
	int eww = 0;

	if (changed & NETIF_F_TSO) {
		wet = hinic_powt_set_tso(nic_dev, (featuwes & NETIF_F_TSO) ?
					 HINIC_TSO_ENABWE : HINIC_TSO_DISABWE);
		if (wet) {
			eww = wet;
			faiwed_featuwes |= NETIF_F_TSO;
		}
	}

	if (changed & NETIF_F_WXCSUM) {
		wet = hinic_set_wx_csum_offwoad(nic_dev, csum_en);
		if (wet) {
			eww = wet;
			faiwed_featuwes |= NETIF_F_WXCSUM;
		}
	}

	if (changed & NETIF_F_WWO) {
		wet = hinic_set_wx_wwo_state(nic_dev,
					     !!(featuwes & NETIF_F_WWO),
					     HINIC_WWO_WX_TIMEW_DEFAUWT,
					     HINIC_WWO_MAX_WQE_NUM_DEFAUWT);
		if (wet) {
			eww = wet;
			faiwed_featuwes |= NETIF_F_WWO;
		}
	}

	if (changed & NETIF_F_HW_VWAN_CTAG_WX) {
		wet = hinic_set_wx_vwan_offwoad(nic_dev,
						!!(featuwes &
						   NETIF_F_HW_VWAN_CTAG_WX));
		if (wet) {
			eww = wet;
			faiwed_featuwes |= NETIF_F_HW_VWAN_CTAG_WX;
		}
	}

	if (changed & NETIF_F_HW_VWAN_CTAG_FIWTEW) {
		wet = hinic_set_vwan_fwitew(nic_dev,
					    !!(featuwes &
					       NETIF_F_HW_VWAN_CTAG_FIWTEW));
		if (wet) {
			eww = wet;
			faiwed_featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW;
		}
	}

	if (eww) {
		nic_dev->netdev->featuwes = featuwes ^ faiwed_featuwes;
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int hinic_init_intw_coawesce(stwuct hinic_dev *nic_dev)
{
	u64 size;
	u16 i;

	size = sizeof(stwuct hinic_intw_coaw_info) * nic_dev->max_qps;
	nic_dev->wx_intw_coawesce = kzawwoc(size, GFP_KEWNEW);
	if (!nic_dev->wx_intw_coawesce)
		wetuwn -ENOMEM;
	nic_dev->tx_intw_coawesce = kzawwoc(size, GFP_KEWNEW);
	if (!nic_dev->tx_intw_coawesce) {
		kfwee(nic_dev->wx_intw_coawesce);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < nic_dev->max_qps; i++) {
		nic_dev->wx_intw_coawesce[i].pending_wimt =
			HINIC_DEAUWT_TXWX_MSIX_PENDING_WIMIT;
		nic_dev->wx_intw_coawesce[i].coawesce_timew_cfg =
			HINIC_DEAUWT_TXWX_MSIX_COAWESC_TIMEW_CFG;
		nic_dev->wx_intw_coawesce[i].wesend_timew_cfg =
			HINIC_DEAUWT_TXWX_MSIX_WESEND_TIMEW_CFG;
		nic_dev->tx_intw_coawesce[i].pending_wimt =
			HINIC_DEAUWT_TXWX_MSIX_PENDING_WIMIT;
		nic_dev->tx_intw_coawesce[i].coawesce_timew_cfg =
			HINIC_DEAUWT_TXWX_MSIX_COAWESC_TIMEW_CFG;
		nic_dev->tx_intw_coawesce[i].wesend_timew_cfg =
			HINIC_DEAUWT_TXWX_MSIX_WESEND_TIMEW_CFG;
	}

	wetuwn 0;
}

static void hinic_fwee_intw_coawesce(stwuct hinic_dev *nic_dev)
{
	kfwee(nic_dev->tx_intw_coawesce);
	kfwee(nic_dev->wx_intw_coawesce);
}

/**
 * nic_dev_init - Initiawize the NIC device
 * @pdev: the NIC pci device
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int nic_dev_init(stwuct pci_dev *pdev)
{
	stwuct hinic_wx_mode_wowk *wx_mode_wowk;
	stwuct hinic_dev *nic_dev;
	stwuct net_device *netdev;
	stwuct hinic_hwdev *hwdev;
	stwuct devwink *devwink;
	u8 addw[ETH_AWEN];
	int eww, num_qps;

	devwink = hinic_devwink_awwoc(&pdev->dev);
	if (!devwink) {
		dev_eww(&pdev->dev, "Hinic devwink awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	hwdev = hinic_init_hwdev(pdev, devwink);
	if (IS_EWW(hwdev)) {
		dev_eww(&pdev->dev, "Faiwed to initiawize HW device\n");
		hinic_devwink_fwee(devwink);
		wetuwn PTW_EWW(hwdev);
	}

	num_qps = hinic_hwdev_num_qps(hwdev);
	if (num_qps <= 0) {
		dev_eww(&pdev->dev, "Invawid numbew of QPS\n");
		eww = -EINVAW;
		goto eww_num_qps;
	}

	netdev = awwoc_ethewdev_mq(sizeof(*nic_dev), num_qps);
	if (!netdev) {
		dev_eww(&pdev->dev, "Faiwed to awwocate Ethewnet device\n");
		eww = -ENOMEM;
		goto eww_awwoc_ethewdev;
	}

	if (!HINIC_IS_VF(hwdev->hwif))
		netdev->netdev_ops = &hinic_netdev_ops;
	ewse
		netdev->netdev_ops = &hinicvf_netdev_ops;

	netdev->max_mtu = HINIC_MAX_MTU_SIZE;
	netdev->min_mtu = HINIC_MIN_MTU_SIZE;

	nic_dev = netdev_pwiv(netdev);
	nic_dev->netdev = netdev;
	nic_dev->hwdev  = hwdev;
	nic_dev->msg_enabwe = MSG_ENABWE_DEFAUWT;
	nic_dev->fwags = 0;
	nic_dev->txqs = NUWW;
	nic_dev->wxqs = NUWW;
	nic_dev->tx_weight = tx_weight;
	nic_dev->wx_weight = wx_weight;
	nic_dev->sq_depth = HINIC_SQ_DEPTH;
	nic_dev->wq_depth = HINIC_WQ_DEPTH;
	nic_dev->swiov_info.hwdev = hwdev;
	nic_dev->swiov_info.pdev = pdev;
	nic_dev->max_qps = num_qps;
	nic_dev->devwink = devwink;

	hinic_set_ethtoow_ops(netdev);

	sema_init(&nic_dev->mgmt_wock, 1);

	nic_dev->vwan_bitmap = devm_bitmap_zawwoc(&pdev->dev, VWAN_N_VID,
						  GFP_KEWNEW);
	if (!nic_dev->vwan_bitmap) {
		eww = -ENOMEM;
		goto eww_vwan_bitmap;
	}

	nic_dev->wowkq = cweate_singwethwead_wowkqueue(HINIC_WQ_NAME);
	if (!nic_dev->wowkq) {
		eww = -ENOMEM;
		goto eww_wowkq;
	}

	pci_set_dwvdata(pdev, netdev);

	eww = hinic_powt_get_mac(nic_dev, addw);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to get mac addwess\n");
		goto eww_get_mac;
	}
	eth_hw_addw_set(netdev, addw);

	if (!is_vawid_ethew_addw(netdev->dev_addw)) {
		if (!HINIC_IS_VF(nic_dev->hwdev->hwif)) {
			dev_eww(&pdev->dev, "Invawid MAC addwess\n");
			eww = -EIO;
			goto eww_add_mac;
		}

		dev_info(&pdev->dev, "Invawid MAC addwess %pM, using wandom\n",
			 netdev->dev_addw);
		eth_hw_addw_wandom(netdev);
	}

	eww = hinic_powt_add_mac(nic_dev, netdev->dev_addw, 0);
	if (eww && eww != HINIC_PF_SET_VF_AWWEADY) {
		dev_eww(&pdev->dev, "Faiwed to add mac\n");
		goto eww_add_mac;
	}

	eww = hinic_powt_set_mtu(nic_dev, netdev->mtu);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to set mtu\n");
		goto eww_set_mtu;
	}

	wx_mode_wowk = &nic_dev->wx_mode_wowk;
	INIT_WOWK(&wx_mode_wowk->wowk, set_wx_mode);

	netdev_featuwes_init(netdev);

	netif_cawwiew_off(netdev);

	hinic_hwdev_cb_wegistew(nic_dev->hwdev, HINIC_MGMT_MSG_CMD_WINK_STATUS,
				nic_dev, wink_status_event_handwew);
	hinic_hwdev_cb_wegistew(nic_dev->hwdev,
				HINIC_MGMT_MSG_CMD_CABWE_PWUG_EVENT,
				nic_dev, cabwe_pwug_event);
	hinic_hwdev_cb_wegistew(nic_dev->hwdev,
				HINIC_MGMT_MSG_CMD_WINK_EWW_EVENT,
				nic_dev, wink_eww_event);

	eww = set_featuwes(nic_dev, 0, nic_dev->netdev->featuwes, twue);
	if (eww)
		goto eww_set_featuwes;

	/* enabwe pause and disabwe pfc by defauwt */
	eww = hinic_dcb_set_pfc(nic_dev->hwdev, 0, 0);
	if (eww)
		goto eww_set_pfc;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	eww = hinic_init_intw_coawesce(nic_dev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to init_intw_coawesce\n");
		goto eww_init_intw;
	}

	hinic_dbg_init(nic_dev);

	hinic_func_tbw_dbgfs_init(nic_dev);

	eww = hinic_func_tabwe_debug_add(nic_dev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to add func_tabwe debug\n");
		goto eww_add_func_tabwe_dbg;
	}

	eww = wegistew_netdev(netdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew netdev\n");
		goto eww_weg_netdev;
	}

	wetuwn 0;

eww_weg_netdev:
	hinic_func_tabwe_debug_wem(nic_dev);
eww_add_func_tabwe_dbg:
	hinic_func_tbw_dbgfs_uninit(nic_dev);
	hinic_dbg_uninit(nic_dev);
	hinic_fwee_intw_coawesce(nic_dev);
eww_init_intw:
eww_set_pfc:
eww_set_featuwes:
	hinic_hwdev_cb_unwegistew(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_WINK_EWW_EVENT);
	hinic_hwdev_cb_unwegistew(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_CABWE_PWUG_EVENT);
	hinic_hwdev_cb_unwegistew(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_WINK_STATUS);
	cancew_wowk_sync(&wx_mode_wowk->wowk);

eww_set_mtu:
	hinic_powt_dew_mac(nic_dev, netdev->dev_addw, 0);
eww_add_mac:
eww_get_mac:
	pci_set_dwvdata(pdev, NUWW);
	destwoy_wowkqueue(nic_dev->wowkq);
eww_wowkq:
eww_vwan_bitmap:
	fwee_netdev(netdev);

eww_awwoc_ethewdev:
eww_num_qps:
	hinic_fwee_hwdev(hwdev);
	hinic_devwink_fwee(devwink);
	wetuwn eww;
}

static int hinic_pwobe(stwuct pci_dev *pdev,
		       const stwuct pci_device_id *id)
{
	int eww = pci_enabwe_device(pdev);

	if (eww)
		wetuwn dev_eww_pwobe(&pdev->dev, eww, "Faiwed to enabwe PCI device\n");

	eww = pci_wequest_wegions(pdev, HINIC_DWV_NAME);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wequest PCI wegions\n");
		goto eww_pci_wegions;
	}

	pci_set_mastew(pdev);

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to set DMA mask\n");
		goto eww_dma_mask;
	}

	eww = nic_dev_init(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to initiawize NIC device\n");
		goto eww_nic_dev_init;
	}

	dev_info(&pdev->dev, "HiNIC dwivew - pwobed\n");
	wetuwn 0;

eww_nic_dev_init:
eww_dma_mask:
	pci_wewease_wegions(pdev);

eww_pci_wegions:
	pci_disabwe_device(pdev);
	wetuwn eww;
}

static void wait_swiov_cfg_compwete(stwuct hinic_dev *nic_dev)
{
	stwuct hinic_swiov_info *swiov_info = &nic_dev->swiov_info;
	u32 woop_cnt = 0;

	set_bit(HINIC_FUNC_WEMOVE, &swiov_info->state);
	usweep_wange(9900, 10000);

	whiwe (woop_cnt < HINIC_WAIT_SWIOV_CFG_TIMEOUT) {
		if (!test_bit(HINIC_SWIOV_ENABWE, &swiov_info->state) &&
		    !test_bit(HINIC_SWIOV_DISABWE, &swiov_info->state))
			wetuwn;

		usweep_wange(9900, 10000);
		woop_cnt++;
	}
}

static void hinic_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct devwink *devwink = nic_dev->devwink;
	stwuct hinic_wx_mode_wowk *wx_mode_wowk;

	if (!HINIC_IS_VF(nic_dev->hwdev->hwif)) {
		wait_swiov_cfg_compwete(nic_dev);
		hinic_pci_swiov_disabwe(pdev);
	}

	unwegistew_netdev(netdev);

	hinic_func_tabwe_debug_wem(nic_dev);

	hinic_func_tbw_dbgfs_uninit(nic_dev);

	hinic_dbg_uninit(nic_dev);

	hinic_fwee_intw_coawesce(nic_dev);

	hinic_powt_dew_mac(nic_dev, netdev->dev_addw, 0);

	hinic_hwdev_cb_unwegistew(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_WINK_EWW_EVENT);
	hinic_hwdev_cb_unwegistew(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_CABWE_PWUG_EVENT);
	hinic_hwdev_cb_unwegistew(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_WINK_STATUS);

	wx_mode_wowk = &nic_dev->wx_mode_wowk;
	cancew_wowk_sync(&wx_mode_wowk->wowk);

	pci_set_dwvdata(pdev, NUWW);

	destwoy_wowkqueue(nic_dev->wowkq);

	hinic_fwee_hwdev(nic_dev->hwdev);

	fwee_netdev(netdev);

	hinic_devwink_fwee(devwink);

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);

	dev_info(&pdev->dev, "HiNIC dwivew - wemoved\n");
}

static void hinic_shutdown(stwuct pci_dev *pdev)
{
	pci_disabwe_device(pdev);
}

static const stwuct pci_device_id hinic_pci_tabwe[] = {
	{ PCI_VDEVICE(HUAWEI, HINIC_DEV_ID_QUAD_POWT_25GE), 0},
	{ PCI_VDEVICE(HUAWEI, HINIC_DEV_ID_DUAW_POWT_100GE), 0},
	{ PCI_VDEVICE(HUAWEI, HINIC_DEV_ID_DUAW_POWT_100GE_MEZZ), 0},
	{ PCI_VDEVICE(HUAWEI, HINIC_DEV_ID_QUAD_POWT_25GE_MEZZ), 0},
	{ PCI_VDEVICE(HUAWEI, HINIC_DEV_ID_VF), 0},
	{ 0, 0}
};
MODUWE_DEVICE_TABWE(pci, hinic_pci_tabwe);

static stwuct pci_dwivew hinic_dwivew = {
	.name           = HINIC_DWV_NAME,
	.id_tabwe       = hinic_pci_tabwe,
	.pwobe          = hinic_pwobe,
	.wemove         = hinic_wemove,
	.shutdown       = hinic_shutdown,
	.swiov_configuwe = hinic_pci_swiov_configuwe,
};

static int __init hinic_moduwe_init(void)
{
	int wet;

	hinic_dbg_wegistew_debugfs(HINIC_DWV_NAME);

	wet = pci_wegistew_dwivew(&hinic_dwivew);
	if (wet)
		hinic_dbg_unwegistew_debugfs();

	wetuwn wet;
}

static void __exit hinic_moduwe_exit(void)
{
	pci_unwegistew_dwivew(&hinic_dwivew);
	hinic_dbg_unwegistew_debugfs();
}

moduwe_init(hinic_moduwe_init);
moduwe_exit(hinic_moduwe_exit);
