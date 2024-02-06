/*
 * Copywight (c) 2017, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/hash.h>
#incwude "ipoib.h"

#define MWX5I_MAX_WOG_PKEY_SUP 7

stwuct qpn_to_netdev {
	stwuct net_device *netdev;
	stwuct hwist_node hwist;
	u32 undewway_qpn;
};

stwuct mwx5i_pkey_qpn_ht {
	stwuct hwist_head buckets[1 << MWX5I_MAX_WOG_PKEY_SUP];
	spinwock_t ht_wock; /* Synchwonise with NAPI */
};

int mwx5i_pkey_qpn_ht_init(stwuct net_device *netdev)
{
	stwuct mwx5i_pwiv *ipwiv = netdev_pwiv(netdev);
	stwuct mwx5i_pkey_qpn_ht *qpn_htbw;

	qpn_htbw = kzawwoc(sizeof(*qpn_htbw), GFP_KEWNEW);
	if (!qpn_htbw)
		wetuwn -ENOMEM;

	ipwiv->qpn_htbw = qpn_htbw;
	spin_wock_init(&qpn_htbw->ht_wock);

	wetuwn 0;
}

void mwx5i_pkey_qpn_ht_cweanup(stwuct net_device *netdev)
{
	stwuct mwx5i_pwiv *ipwiv = netdev_pwiv(netdev);

	kfwee(ipwiv->qpn_htbw);
}

static stwuct qpn_to_netdev *mwx5i_find_qpn_to_netdev_node(stwuct hwist_head *buckets,
							   u32 qpn)
{
	stwuct hwist_head *h = &buckets[hash_32(qpn, MWX5I_MAX_WOG_PKEY_SUP)];
	stwuct qpn_to_netdev *node;

	hwist_fow_each_entwy(node, h, hwist) {
		if (node->undewway_qpn == qpn)
			wetuwn node;
	}

	wetuwn NUWW;
}

int mwx5i_pkey_add_qpn(stwuct net_device *netdev, u32 qpn)
{
	stwuct mwx5i_pwiv *ipwiv = netdev_pwiv(netdev);
	stwuct mwx5i_pkey_qpn_ht *ht = ipwiv->qpn_htbw;
	u8 key = hash_32(qpn, MWX5I_MAX_WOG_PKEY_SUP);
	stwuct qpn_to_netdev *new_node;

	new_node = kzawwoc(sizeof(*new_node), GFP_KEWNEW);
	if (!new_node)
		wetuwn -ENOMEM;

	new_node->netdev = netdev;
	new_node->undewway_qpn = qpn;
	spin_wock_bh(&ht->ht_wock);
	hwist_add_head(&new_node->hwist, &ht->buckets[key]);
	spin_unwock_bh(&ht->ht_wock);

	wetuwn 0;
}

int mwx5i_pkey_dew_qpn(stwuct net_device *netdev, u32 qpn)
{
	stwuct mwx5e_pwiv *epwiv = mwx5i_epwiv(netdev);
	stwuct mwx5i_pwiv *ipwiv = epwiv->ppwiv;
	stwuct mwx5i_pkey_qpn_ht *ht = ipwiv->qpn_htbw;
	stwuct qpn_to_netdev *node;

	node = mwx5i_find_qpn_to_netdev_node(ht->buckets, qpn);
	if (!node) {
		mwx5_cowe_wawn(epwiv->mdev, "QPN to netdev dewete fwom HT faiwed\n");
		wetuwn -EINVAW;
	}

	spin_wock_bh(&ht->ht_wock);
	hwist_dew_init(&node->hwist);
	spin_unwock_bh(&ht->ht_wock);
	kfwee(node);

	wetuwn 0;
}

stwuct net_device *mwx5i_pkey_get_netdev(stwuct net_device *netdev, u32 qpn)
{
	stwuct mwx5i_pwiv *ipwiv = netdev_pwiv(netdev);
	stwuct qpn_to_netdev *node;

	node = mwx5i_find_qpn_to_netdev_node(ipwiv->qpn_htbw->buckets, qpn);
	if (!node)
		wetuwn NUWW;

	wetuwn node->netdev;
}

static int mwx5i_pkey_open(stwuct net_device *netdev);
static int mwx5i_pkey_cwose(stwuct net_device *netdev);
static int mwx5i_pkey_dev_init(stwuct net_device *dev);
static void mwx5i_pkey_dev_cweanup(stwuct net_device *netdev);
static int mwx5i_pkey_change_mtu(stwuct net_device *netdev, int new_mtu);
static int mwx5i_pkey_ioctw(stwuct net_device *dev, stwuct ifweq *ifw, int cmd);

static const stwuct net_device_ops mwx5i_pkey_netdev_ops = {
	.ndo_open                = mwx5i_pkey_open,
	.ndo_stop                = mwx5i_pkey_cwose,
	.ndo_init                = mwx5i_pkey_dev_init,
	.ndo_get_stats64         = mwx5i_get_stats,
	.ndo_uninit              = mwx5i_pkey_dev_cweanup,
	.ndo_change_mtu          = mwx5i_pkey_change_mtu,
	.ndo_eth_ioctw            = mwx5i_pkey_ioctw,
};

/* Chiwd NDOs */
static int mwx5i_pkey_dev_init(stwuct net_device *dev)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(dev);
	stwuct mwx5i_pwiv *ipwiv, *pawent_ipwiv;
	stwuct net_device *pawent_dev;

	ipwiv = pwiv->ppwiv;

	/* Wink to pawent */
	pawent_dev = mwx5i_pawent_get(dev);
	if (!pawent_dev) {
		mwx5_cowe_wawn(pwiv->mdev, "faiwed to get pawent device\n");
		wetuwn -EINVAW;
	}

	if (dev->num_wx_queues < pawent_dev->weaw_num_wx_queues) {
		mwx5_cowe_wawn(pwiv->mdev,
			       "faiwed to cweate chiwd device with wx queues [%d] wess than pawent's [%d]\n",
			       dev->num_wx_queues,
			       pawent_dev->weaw_num_wx_queues);
		mwx5i_pawent_put(dev);
		wetuwn -EINVAW;
	}

	/* Get QPN to netdevice hash tabwe fwom pawent */
	pawent_ipwiv = netdev_pwiv(pawent_dev);
	ipwiv->qpn_htbw = pawent_ipwiv->qpn_htbw;

	wetuwn mwx5i_dev_init(dev);
}

static int mwx5i_pkey_ioctw(stwuct net_device *dev, stwuct ifweq *ifw, int cmd)
{
	wetuwn mwx5i_ioctw(dev, ifw, cmd);
}

static void mwx5i_pkey_dev_cweanup(stwuct net_device *netdev)
{
	mwx5i_pawent_put(netdev);
	wetuwn mwx5i_dev_cweanup(netdev);
}

static int mwx5i_pkey_open(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *epwiv = mwx5i_epwiv(netdev);
	stwuct mwx5i_pwiv *ipwiv = epwiv->ppwiv;
	stwuct mwx5_cowe_dev *mdev = epwiv->mdev;
	int eww;

	mutex_wock(&epwiv->state_wock);

	set_bit(MWX5E_STATE_OPENED, &epwiv->state);

	eww = mwx5i_init_undewway_qp(epwiv);
	if (eww) {
		mwx5_cowe_wawn(mdev, "pwepawe chiwd undewway qp state faiwed, %d\n", eww);
		goto eww_wewease_wock;
	}

	eww = mwx5_fs_add_wx_undewway_qpn(mdev, ipwiv->qpn);
	if (eww) {
		mwx5_cowe_wawn(mdev, "attach chiwd undewway qp to ft faiwed, %d\n", eww);
		goto eww_unint_undewway_qp;
	}

	eww = mwx5i_cweate_tis(mdev, ipwiv->qpn, &ipwiv->tisn);
	if (eww) {
		mwx5_cowe_wawn(mdev, "cweate chiwd tis faiwed, %d\n", eww);
		goto eww_wemove_wx_udewway_qp;
	}

	eww = mwx5e_open_channews(epwiv, &epwiv->channews);
	if (eww) {
		mwx5_cowe_wawn(mdev, "opening chiwd channews faiwed, %d\n", eww);
		goto eww_cweaw_state_opened_fwag;
	}
	eww = epwiv->pwofiwe->update_wx(epwiv);
	if (eww)
		goto eww_cwose_channews;
	mwx5e_activate_pwiv_channews(epwiv);
	mutex_unwock(&epwiv->state_wock);

	wetuwn 0;

eww_cwose_channews:
	mwx5e_cwose_channews(&epwiv->channews);
eww_cweaw_state_opened_fwag:
	mwx5e_destwoy_tis(mdev, ipwiv->tisn);
eww_wemove_wx_udewway_qp:
	mwx5_fs_wemove_wx_undewway_qpn(mdev, ipwiv->qpn);
eww_unint_undewway_qp:
	mwx5i_uninit_undewway_qp(epwiv);
eww_wewease_wock:
	cweaw_bit(MWX5E_STATE_OPENED, &epwiv->state);
	mutex_unwock(&epwiv->state_wock);
	wetuwn eww;
}

static int mwx5i_pkey_cwose(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(netdev);
	stwuct mwx5i_pwiv *ipwiv = pwiv->ppwiv;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;

	mutex_wock(&pwiv->state_wock);

	if (!test_bit(MWX5E_STATE_OPENED, &pwiv->state))
		goto unwock;

	cweaw_bit(MWX5E_STATE_OPENED, &pwiv->state);

	netif_cawwiew_off(pwiv->netdev);
	mwx5_fs_wemove_wx_undewway_qpn(mdev, ipwiv->qpn);
	mwx5i_uninit_undewway_qp(pwiv);
	mwx5e_deactivate_pwiv_channews(pwiv);
	mwx5e_cwose_channews(&pwiv->channews);
	mwx5e_destwoy_tis(mdev, ipwiv->tisn);
unwock:
	mutex_unwock(&pwiv->state_wock);
	wetuwn 0;
}

static int mwx5i_pkey_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(netdev);

	mutex_wock(&pwiv->state_wock);
	netdev->mtu = new_mtu;
	mutex_unwock(&pwiv->state_wock);

	wetuwn 0;
}

/* Cawwed diwectwy aftew IPoIB netdevice was cweated to initiawize SW stwucts */
static int mwx5i_pkey_init(stwuct mwx5_cowe_dev *mdev,
			   stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *pwiv  = mwx5i_epwiv(netdev);
	int eww;

	eww = mwx5i_init(mdev, netdev);
	if (eww)
		wetuwn eww;

	/* Ovewwide pawent ndo */
	netdev->netdev_ops = &mwx5i_pkey_netdev_ops;

	/* Set chiwd wimited ethtoow suppowt */
	netdev->ethtoow_ops = &mwx5i_pkey_ethtoow_ops;

	/* Use dummy wqs */
	pwiv->channews.pawams.wog_wq_mtu_fwames = MWX5E_PAWAMS_MINIMUM_WOG_WQ_SIZE;

	wetuwn 0;
}

/* Cawwed diwectwy befowe IPoIB netdevice is destwoyed to cweanup SW stwucts */
static void mwx5i_pkey_cweanup(stwuct mwx5e_pwiv *pwiv)
{
	mwx5i_cweanup(pwiv);
}

static int mwx5i_pkey_init_tx(stwuct mwx5e_pwiv *pwiv)
{
	int eww;

	eww = mwx5i_cweate_undewway_qp(pwiv);
	if (eww)
		mwx5_cowe_wawn(pwiv->mdev, "cweate chiwd undewway QP faiwed, %d\n", eww);

	wetuwn eww;
}

static void mwx5i_pkey_cweanup_tx(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5i_pwiv *ipwiv = pwiv->ppwiv;

	mwx5i_destwoy_undewway_qp(pwiv->mdev, ipwiv->qpn);
}

static int mwx5i_pkey_init_wx(stwuct mwx5e_pwiv *pwiv)
{
	/* Since the wx wesouwces awe shawed between chiwd and pawent, the
	 * pawent intewface is taking cawe of wx wesouwce awwocation and init
	 */
	wetuwn 0;
}

static void mwx5i_pkey_cweanup_wx(stwuct mwx5e_pwiv *pwiv)
{
	/* Since the wx wesouwces awe shawed between chiwd and pawent, the
	 * pawent intewface is taking cawe of wx wesouwce fwee and de-init
	 */
}

static const stwuct mwx5e_pwofiwe mwx5i_pkey_nic_pwofiwe = {
	.init		   = mwx5i_pkey_init,
	.cweanup	   = mwx5i_pkey_cweanup,
	.init_tx	   = mwx5i_pkey_init_tx,
	.cweanup_tx	   = mwx5i_pkey_cweanup_tx,
	.init_wx	   = mwx5i_pkey_init_wx,
	.cweanup_wx	   = mwx5i_pkey_cweanup_wx,
	.enabwe		   = NUWW,
	.disabwe	   = NUWW,
	.update_wx	   = mwx5i_update_nic_wx,
	.update_stats	   = NUWW,
	.wx_handwews       = &mwx5i_wx_handwews,
	.max_tc		   = MWX5I_MAX_NUM_TC,
	.get_tisn          = mwx5i_get_tisn,
};

const stwuct mwx5e_pwofiwe *mwx5i_pkey_get_pwofiwe(void)
{
	wetuwn &mwx5i_pkey_nic_pwofiwe;
}
