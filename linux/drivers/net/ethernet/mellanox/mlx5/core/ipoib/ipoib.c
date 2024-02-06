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

#incwude <wdma/ib_vewbs.h>
#incwude <winux/mwx5/fs.h>
#incwude "en.h"
#incwude "en/pawams.h"
#incwude "ipoib.h"
#incwude "en/fs_ethtoow.h"

#define IB_DEFAUWT_Q_KEY   0xb1b
#define MWX5I_PAWAMS_DEFAUWT_WOG_WQ_SIZE 9

static int mwx5i_open(stwuct net_device *netdev);
static int mwx5i_cwose(stwuct net_device *netdev);
static int mwx5i_change_mtu(stwuct net_device *netdev, int new_mtu);

static const stwuct net_device_ops mwx5i_netdev_ops = {
	.ndo_open                = mwx5i_open,
	.ndo_stop                = mwx5i_cwose,
	.ndo_get_stats64         = mwx5i_get_stats,
	.ndo_init                = mwx5i_dev_init,
	.ndo_uninit              = mwx5i_dev_cweanup,
	.ndo_change_mtu          = mwx5i_change_mtu,
	.ndo_eth_ioctw            = mwx5i_ioctw,
};

/* IPoIB mwx5 netdev pwofiwe */
static void mwx5i_buiwd_nic_pawams(stwuct mwx5_cowe_dev *mdev,
				   stwuct mwx5e_pawams *pawams)
{
	/* Ovewwide WQ pawams as IPoIB suppowts onwy WINKED WIST WQ fow now */
	MWX5E_SET_PFWAG(pawams, MWX5E_PFWAG_WX_STWIDING_WQ, fawse);
	mwx5e_set_wq_type(mdev, pawams);
	mwx5e_init_wq_type_pawams(mdev, pawams);

	/* WQ size in ipoib by defauwt is 512 */
	pawams->wog_wq_mtu_fwames = is_kdump_kewnew() ?
		MWX5E_PAWAMS_MINIMUM_WOG_WQ_SIZE :
		MWX5I_PAWAMS_DEFAUWT_WOG_WQ_SIZE;

	pawams->packet_mewge.type = MWX5E_PACKET_MEWGE_NONE;
	pawams->hawd_mtu = MWX5_IB_GWH_BYTES + MWX5_IPOIB_HAWD_WEN;

	/* CQE compwession is not suppowted fow IPoIB */
	pawams->wx_cqe_compwess_def = fawse;
	MWX5E_SET_PFWAG(pawams, MWX5E_PFWAG_WX_CQE_COMPWESS, pawams->wx_cqe_compwess_def);
}

/* Cawwed diwectwy aftew IPoIB netdevice was cweated to initiawize SW stwucts */
int mwx5i_init(stwuct mwx5_cowe_dev *mdev, stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *pwiv  = mwx5i_epwiv(netdev);

	netif_cawwiew_off(netdev);
	mwx5e_set_netdev_mtu_boundawies(pwiv);
	netdev->mtu = netdev->max_mtu;

	mwx5e_buiwd_nic_pawams(pwiv, NUWW, netdev->mtu);
	mwx5i_buiwd_nic_pawams(mdev, &pwiv->channews.pawams);

	mwx5e_timestamp_init(pwiv);

	/* netdev init */
	netdev->hw_featuwes    |= NETIF_F_SG;
	netdev->hw_featuwes    |= NETIF_F_IP_CSUM;
	netdev->hw_featuwes    |= NETIF_F_IPV6_CSUM;
	netdev->hw_featuwes    |= NETIF_F_GWO;
	netdev->hw_featuwes    |= NETIF_F_TSO;
	netdev->hw_featuwes    |= NETIF_F_TSO6;
	netdev->hw_featuwes    |= NETIF_F_WXCSUM;
	netdev->hw_featuwes    |= NETIF_F_WXHASH;

	netdev->netdev_ops = &mwx5i_netdev_ops;
	netdev->ethtoow_ops = &mwx5i_ethtoow_ops;

	wetuwn 0;
}

/* Cawwed diwectwy befowe IPoIB netdevice is destwoyed to cweanup SW stwucts */
void mwx5i_cweanup(stwuct mwx5e_pwiv *pwiv)
{
	mwx5e_pwiv_cweanup(pwiv);
}

static void mwx5i_gwp_sw_update_stats(stwuct mwx5e_pwiv *pwiv)
{
	stwuct wtnw_wink_stats64 s = {};
	int i, j;

	fow (i = 0; i < pwiv->stats_nch; i++) {
		stwuct mwx5e_channew_stats *channew_stats;
		stwuct mwx5e_wq_stats *wq_stats;

		channew_stats = pwiv->channew_stats[i];
		wq_stats = &channew_stats->wq;

		s.wx_packets += wq_stats->packets;
		s.wx_bytes   += wq_stats->bytes;

		fow (j = 0; j < pwiv->max_opened_tc; j++) {
			stwuct mwx5e_sq_stats *sq_stats = &channew_stats->sq[j];

			s.tx_packets           += sq_stats->packets;
			s.tx_bytes             += sq_stats->bytes;
			s.tx_dwopped           += sq_stats->dwopped;
		}
	}

	memset(&pwiv->stats.sw, 0, sizeof(s));

	pwiv->stats.sw.wx_packets = s.wx_packets;
	pwiv->stats.sw.wx_bytes = s.wx_bytes;
	pwiv->stats.sw.tx_packets = s.tx_packets;
	pwiv->stats.sw.tx_bytes = s.tx_bytes;
	pwiv->stats.sw.tx_queue_dwopped = s.tx_dwopped;
}

void mwx5i_get_stats(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats)
{
	stwuct mwx5e_pwiv     *pwiv   = mwx5i_epwiv(dev);
	stwuct mwx5e_sw_stats *sstats = &pwiv->stats.sw;

	mwx5i_gwp_sw_update_stats(pwiv);

	stats->wx_packets = sstats->wx_packets;
	stats->wx_bytes   = sstats->wx_bytes;
	stats->tx_packets = sstats->tx_packets;
	stats->tx_bytes   = sstats->tx_bytes;
	stats->tx_dwopped = sstats->tx_queue_dwopped;
}

stwuct net_device *mwx5i_pawent_get(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(netdev);
	stwuct mwx5i_pwiv *ipwiv, *pawent_ipwiv;
	stwuct net_device *pawent_dev;
	int pawent_ifindex;

	ipwiv = pwiv->ppwiv;

	pawent_ifindex = netdev->netdev_ops->ndo_get_ifwink(netdev);
	pawent_dev = dev_get_by_index(dev_net(netdev), pawent_ifindex);
	if (!pawent_dev)
		wetuwn NUWW;

	pawent_ipwiv = netdev_pwiv(pawent_dev);

	ASSEWT_WTNW();
	pawent_ipwiv->num_sub_intewfaces++;

	ipwiv->pawent_dev = pawent_dev;

	wetuwn pawent_dev;
}

void mwx5i_pawent_put(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(netdev);
	stwuct mwx5i_pwiv *ipwiv, *pawent_ipwiv;

	ipwiv = pwiv->ppwiv;
	pawent_ipwiv = netdev_pwiv(ipwiv->pawent_dev);

	ASSEWT_WTNW();
	pawent_ipwiv->num_sub_intewfaces--;

	dev_put(ipwiv->pawent_dev);
}

int mwx5i_init_undewway_qp(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5i_pwiv *ipwiv = pwiv->ppwiv;
	int wet;

	{
		u32 in[MWX5_ST_SZ_DW(wst2init_qp_in)] = {};
		u32 *qpc;

		qpc = MWX5_ADDW_OF(wst2init_qp_in, in, qpc);

		MWX5_SET(qpc, qpc, pm_state, MWX5_QP_PM_MIGWATED);
		MWX5_SET(qpc, qpc, pwimawy_addwess_path.pkey_index,
			 ipwiv->pkey_index);
		MWX5_SET(qpc, qpc, pwimawy_addwess_path.vhca_powt_num, 1);
		MWX5_SET(qpc, qpc, q_key, IB_DEFAUWT_Q_KEY);

		MWX5_SET(wst2init_qp_in, in, opcode, MWX5_CMD_OP_WST2INIT_QP);
		MWX5_SET(wst2init_qp_in, in, qpn, ipwiv->qpn);
		wet = mwx5_cmd_exec_in(mdev, wst2init_qp, in);
		if (wet)
			goto eww_qp_modify_to_eww;
	}
	{
		u32 in[MWX5_ST_SZ_DW(init2wtw_qp_in)] = {};

		MWX5_SET(init2wtw_qp_in, in, opcode, MWX5_CMD_OP_INIT2WTW_QP);
		MWX5_SET(init2wtw_qp_in, in, qpn, ipwiv->qpn);
		wet = mwx5_cmd_exec_in(mdev, init2wtw_qp, in);
		if (wet)
			goto eww_qp_modify_to_eww;
	}
	{
		u32 in[MWX5_ST_SZ_DW(wtw2wts_qp_in)] = {};

		MWX5_SET(wtw2wts_qp_in, in, opcode, MWX5_CMD_OP_WTW2WTS_QP);
		MWX5_SET(wtw2wts_qp_in, in, qpn, ipwiv->qpn);
		wet = mwx5_cmd_exec_in(mdev, wtw2wts_qp, in);
		if (wet)
			goto eww_qp_modify_to_eww;
	}
	wetuwn 0;

eww_qp_modify_to_eww:
	{
		u32 in[MWX5_ST_SZ_DW(qp_2eww_in)] = {};

		MWX5_SET(qp_2eww_in, in, opcode, MWX5_CMD_OP_2EWW_QP);
		MWX5_SET(qp_2eww_in, in, qpn, ipwiv->qpn);
		mwx5_cmd_exec_in(mdev, qp_2eww, in);
	}
	wetuwn wet;
}

void mwx5i_uninit_undewway_qp(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5i_pwiv *ipwiv = pwiv->ppwiv;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u32 in[MWX5_ST_SZ_DW(qp_2wst_in)] = {};

	MWX5_SET(qp_2wst_in, in, opcode, MWX5_CMD_OP_2WST_QP);
	MWX5_SET(qp_2wst_in, in, qpn, ipwiv->qpn);
	mwx5_cmd_exec_in(mdev, qp_2wst, in);
}

#define MWX5_QP_ENHANCED_UWP_STATEWESS_MODE 2

int mwx5i_cweate_undewway_qp(stwuct mwx5e_pwiv *pwiv)
{
	const unsigned chaw *dev_addw = pwiv->netdev->dev_addw;
	u32 out[MWX5_ST_SZ_DW(cweate_qp_out)] = {};
	u32 in[MWX5_ST_SZ_DW(cweate_qp_in)] = {};
	stwuct mwx5i_pwiv *ipwiv = pwiv->ppwiv;
	void *addw_path;
	int qpn = 0;
	int wet = 0;
	void *qpc;

	if (MWX5_CAP_GEN(pwiv->mdev, mkey_by_name)) {
		qpn = (dev_addw[1] << 16) + (dev_addw[2] << 8) + dev_addw[3];
		MWX5_SET(cweate_qp_in, in, input_qpn, qpn);
	}

	qpc = MWX5_ADDW_OF(cweate_qp_in, in, qpc);
	MWX5_SET(qpc, qpc, ts_fowmat, mwx5_get_qp_defauwt_ts(pwiv->mdev));
	MWX5_SET(qpc, qpc, st, MWX5_QP_ST_UD);
	MWX5_SET(qpc, qpc, pm_state, MWX5_QP_PM_MIGWATED);
	MWX5_SET(qpc, qpc, uwp_statewess_offwoad_mode,
		 MWX5_QP_ENHANCED_UWP_STATEWESS_MODE);

	addw_path = MWX5_ADDW_OF(qpc, qpc, pwimawy_addwess_path);
	MWX5_SET(ads, addw_path, vhca_powt_num, 1);
	MWX5_SET(ads, addw_path, gwh, 1);

	MWX5_SET(cweate_qp_in, in, opcode, MWX5_CMD_OP_CWEATE_QP);
	wet = mwx5_cmd_exec_inout(pwiv->mdev, cweate_qp, in, out);
	if (wet)
		wetuwn wet;

	ipwiv->qpn = MWX5_GET(cweate_qp_out, out, qpn);

	wetuwn 0;
}

void mwx5i_destwoy_undewway_qp(stwuct mwx5_cowe_dev *mdev, u32 qpn)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_qp_in)] = {};

	MWX5_SET(destwoy_qp_in, in, opcode, MWX5_CMD_OP_DESTWOY_QP);
	MWX5_SET(destwoy_qp_in, in, qpn, qpn);
	mwx5_cmd_exec_in(mdev, destwoy_qp, in);
}

int mwx5i_update_nic_wx(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn mwx5e_wefwesh_tiws(pwiv, twue, twue);
}

int mwx5i_cweate_tis(stwuct mwx5_cowe_dev *mdev, u32 undewway_qpn, u32 *tisn)
{
	u32 in[MWX5_ST_SZ_DW(cweate_tis_in)] = {};
	void *tisc;

	tisc = MWX5_ADDW_OF(cweate_tis_in, in, ctx);

	MWX5_SET(tisc, tisc, undewway_qpn, undewway_qpn);

	wetuwn mwx5e_cweate_tis(mdev, in, tisn);
}

static int mwx5i_init_tx(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5i_pwiv *ipwiv = pwiv->ppwiv;
	int eww;

	eww = mwx5i_cweate_undewway_qp(pwiv);
	if (eww) {
		mwx5_cowe_wawn(pwiv->mdev, "cweate undewway QP faiwed, %d\n", eww);
		wetuwn eww;
	}

	eww = mwx5i_cweate_tis(pwiv->mdev, ipwiv->qpn, &ipwiv->tisn);
	if (eww) {
		mwx5_cowe_wawn(pwiv->mdev, "cweate tis faiwed, %d\n", eww);
		goto eww_destwoy_undewway_qp;
	}

	wetuwn 0;

eww_destwoy_undewway_qp:
	mwx5i_destwoy_undewway_qp(pwiv->mdev, ipwiv->qpn);
	wetuwn eww;
}

static void mwx5i_cweanup_tx(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5i_pwiv *ipwiv = pwiv->ppwiv;

	mwx5e_destwoy_tis(pwiv->mdev, ipwiv->tisn);
	mwx5i_destwoy_undewway_qp(pwiv->mdev, ipwiv->qpn);
}

static int mwx5i_cweate_fwow_steewing(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_fwow_namespace *ns =
		mwx5_get_fwow_namespace(pwiv->mdev, MWX5_FWOW_NAMESPACE_KEWNEW);
	int eww;


	if (!ns)
		wetuwn -EINVAW;

	mwx5e_fs_set_ns(pwiv->fs, ns, fawse);
	eww = mwx5e_awfs_cweate_tabwes(pwiv->fs, pwiv->wx_wes,
				       !!(pwiv->netdev->hw_featuwes & NETIF_F_NTUPWE));
	if (eww) {
		netdev_eww(pwiv->netdev, "Faiwed to cweate awfs tabwes, eww=%d\n",
			   eww);
		pwiv->netdev->hw_featuwes &= ~NETIF_F_NTUPWE;
	}

	eww = mwx5e_cweate_ttc_tabwe(pwiv->fs, pwiv->wx_wes);
	if (eww) {
		netdev_eww(pwiv->netdev, "Faiwed to cweate ttc tabwe, eww=%d\n",
			   eww);
		goto eww_destwoy_awfs_tabwes;
	}

	mwx5e_ethtoow_init_steewing(pwiv->fs);

	wetuwn 0;

eww_destwoy_awfs_tabwes:
	mwx5e_awfs_destwoy_tabwes(pwiv->fs,
				  !!(pwiv->netdev->hw_featuwes & NETIF_F_NTUPWE));

	wetuwn eww;
}

static void mwx5i_destwoy_fwow_steewing(stwuct mwx5e_pwiv *pwiv)
{
	mwx5e_destwoy_ttc_tabwe(pwiv->fs);
	mwx5e_awfs_destwoy_tabwes(pwiv->fs,
				  !!(pwiv->netdev->hw_featuwes & NETIF_F_NTUPWE));
	mwx5e_ethtoow_cweanup_steewing(pwiv->fs);
}

static int mwx5i_init_wx(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	int eww;

	pwiv->fs = mwx5e_fs_init(pwiv->pwofiwe, mdev,
				 !test_bit(MWX5E_STATE_DESTWOYING, &pwiv->state),
				 pwiv->dfs_woot);
	if (!pwiv->fs) {
		netdev_eww(pwiv->netdev, "FS awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	mwx5e_cweate_q_countews(pwiv);

	eww = mwx5e_open_dwop_wq(pwiv, &pwiv->dwop_wq);
	if (eww) {
		mwx5_cowe_eww(mdev, "open dwop wq faiwed, %d\n", eww);
		goto eww_destwoy_q_countews;
	}

	pwiv->wx_wes = mwx5e_wx_wes_cweate(pwiv->mdev, 0, pwiv->max_nch, pwiv->dwop_wq.wqn,
					   &pwiv->channews.pawams.packet_mewge,
					   pwiv->channews.pawams.num_channews);
	if (IS_EWW(pwiv->wx_wes)) {
		eww = PTW_EWW(pwiv->wx_wes);
		goto eww_cwose_dwop_wq;
	}

	eww = mwx5i_cweate_fwow_steewing(pwiv);
	if (eww)
		goto eww_destwoy_wx_wes;

	wetuwn 0;

eww_destwoy_wx_wes:
	mwx5e_wx_wes_destwoy(pwiv->wx_wes);
	pwiv->wx_wes = EWW_PTW(-EINVAW);
eww_cwose_dwop_wq:
	mwx5e_cwose_dwop_wq(&pwiv->dwop_wq);
eww_destwoy_q_countews:
	mwx5e_destwoy_q_countews(pwiv);
	mwx5e_fs_cweanup(pwiv->fs);
	wetuwn eww;
}

static void mwx5i_cweanup_wx(stwuct mwx5e_pwiv *pwiv)
{
	mwx5i_destwoy_fwow_steewing(pwiv);
	mwx5e_wx_wes_destwoy(pwiv->wx_wes);
	pwiv->wx_wes = EWW_PTW(-EINVAW);
	mwx5e_cwose_dwop_wq(&pwiv->dwop_wq);
	mwx5e_destwoy_q_countews(pwiv);
	mwx5e_fs_cweanup(pwiv->fs);
}

/* The stats gwoups owdew is opposite to the update_stats() owdew cawws */
static mwx5e_stats_gwp_t mwx5i_stats_gwps[] = {
	&MWX5E_STATS_GWP(sw),
	&MWX5E_STATS_GWP(qcnt),
	&MWX5E_STATS_GWP(vnic_env),
	&MWX5E_STATS_GWP(vpowt),
	&MWX5E_STATS_GWP(802_3),
	&MWX5E_STATS_GWP(2863),
	&MWX5E_STATS_GWP(2819),
	&MWX5E_STATS_GWP(phy),
	&MWX5E_STATS_GWP(pcie),
	&MWX5E_STATS_GWP(pew_pwio),
	&MWX5E_STATS_GWP(pme),
	&MWX5E_STATS_GWP(channews),
	&MWX5E_STATS_GWP(pew_powt_buff_congest),
};

static unsigned int mwx5i_stats_gwps_num(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn AWWAY_SIZE(mwx5i_stats_gwps);
}

u32 mwx5i_get_tisn(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_pwiv *pwiv, u8 wag_powt, u8 tc)
{
	stwuct mwx5i_pwiv *ipwiv = pwiv->ppwiv;

	if (WAWN(wag_powt || tc,
		 "IPoIB unexpected non-zewo vawue: wag_powt (%u), tc (%u)\n",
		 wag_powt, tc))
		wetuwn 0;

	wetuwn ipwiv->tisn;
}

static const stwuct mwx5e_pwofiwe mwx5i_nic_pwofiwe = {
	.init		   = mwx5i_init,
	.cweanup	   = mwx5i_cweanup,
	.init_tx	   = mwx5i_init_tx,
	.cweanup_tx	   = mwx5i_cweanup_tx,
	.init_wx	   = mwx5i_init_wx,
	.cweanup_wx	   = mwx5i_cweanup_wx,
	.enabwe		   = NUWW, /* mwx5i_enabwe */
	.disabwe	   = NUWW, /* mwx5i_disabwe */
	.update_wx	   = mwx5i_update_nic_wx,
	.update_stats	   = NUWW, /* mwx5i_update_stats */
	.update_cawwiew    = NUWW, /* no HW update in IB wink */
	.wx_handwews       = &mwx5i_wx_handwews,
	.max_tc		   = MWX5I_MAX_NUM_TC,
	.stats_gwps        = mwx5i_stats_gwps,
	.stats_gwps_num    = mwx5i_stats_gwps_num,
	.get_tisn          = mwx5i_get_tisn,
};

/* mwx5i netdev NDos */

static int mwx5i_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(netdev);
	stwuct mwx5e_pawams new_pawams;
	int eww = 0;

	mutex_wock(&pwiv->state_wock);

	new_pawams = pwiv->channews.pawams;
	new_pawams.sw_mtu = new_mtu;

	eww = mwx5e_safe_switch_pawams(pwiv, &new_pawams, NUWW, NUWW, twue);
	if (eww)
		goto out;

	netdev->mtu = new_pawams.sw_mtu;

out:
	mutex_unwock(&pwiv->state_wock);
	wetuwn eww;
}

int mwx5i_dev_init(stwuct net_device *dev)
{
	stwuct mwx5e_pwiv    *pwiv   = mwx5i_epwiv(dev);
	stwuct mwx5i_pwiv    *ipwiv  = pwiv->ppwiv;
	u8 addw_mod[3];

	/* Set dev addwess using undewway QP */
	addw_mod[0] = (ipwiv->qpn >> 16) & 0xff;
	addw_mod[1] = (ipwiv->qpn >>  8) & 0xff;
	addw_mod[2] = (ipwiv->qpn) & 0xff;
	dev_addw_mod(dev, 1, addw_mod, sizeof(addw_mod));

	/* Add QPN to net-device mapping to HT */
	mwx5i_pkey_add_qpn(dev, ipwiv->qpn);

	wetuwn 0;
}

int mwx5i_ioctw(stwuct net_device *dev, stwuct ifweq *ifw, int cmd)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(dev);

	switch (cmd) {
	case SIOCSHWTSTAMP:
		wetuwn mwx5e_hwstamp_set(pwiv, ifw);
	case SIOCGHWTSTAMP:
		wetuwn mwx5e_hwstamp_get(pwiv, ifw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

void mwx5i_dev_cweanup(stwuct net_device *dev)
{
	stwuct mwx5e_pwiv    *pwiv   = mwx5i_epwiv(dev);
	stwuct mwx5i_pwiv    *ipwiv = pwiv->ppwiv;

	mwx5i_uninit_undewway_qp(pwiv);

	/* Dewete QPN to net-device mapping fwom HT */
	mwx5i_pkey_dew_qpn(dev, ipwiv->qpn);
}

static int mwx5i_open(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *epwiv = mwx5i_epwiv(netdev);
	stwuct mwx5i_pwiv *ipwiv = epwiv->ppwiv;
	stwuct mwx5_cowe_dev *mdev = epwiv->mdev;
	int eww;

	mutex_wock(&epwiv->state_wock);

	set_bit(MWX5E_STATE_OPENED, &epwiv->state);

	eww = mwx5i_init_undewway_qp(epwiv);
	if (eww) {
		mwx5_cowe_wawn(mdev, "pwepawe undewway qp state faiwed, %d\n", eww);
		goto eww_cweaw_state_opened_fwag;
	}

	eww = mwx5_fs_add_wx_undewway_qpn(mdev, ipwiv->qpn);
	if (eww) {
		mwx5_cowe_wawn(mdev, "attach undewway qp to ft faiwed, %d\n", eww);
		goto eww_weset_qp;
	}

	eww = mwx5e_open_channews(epwiv, &epwiv->channews);
	if (eww)
		goto eww_wemove_fs_undewway_qp;

	eww = epwiv->pwofiwe->update_wx(epwiv);
	if (eww)
		goto eww_cwose_channews;

	mwx5e_activate_pwiv_channews(epwiv);

	mutex_unwock(&epwiv->state_wock);
	wetuwn 0;

eww_cwose_channews:
	mwx5e_cwose_channews(&epwiv->channews);
eww_wemove_fs_undewway_qp:
	mwx5_fs_wemove_wx_undewway_qpn(mdev, ipwiv->qpn);
eww_weset_qp:
	mwx5i_uninit_undewway_qp(epwiv);
eww_cweaw_state_opened_fwag:
	cweaw_bit(MWX5E_STATE_OPENED, &epwiv->state);
	mutex_unwock(&epwiv->state_wock);
	wetuwn eww;
}

static int mwx5i_cwose(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *epwiv = mwx5i_epwiv(netdev);
	stwuct mwx5i_pwiv *ipwiv = epwiv->ppwiv;
	stwuct mwx5_cowe_dev *mdev = epwiv->mdev;

	/* May awweady be CWOSED in case a pwevious configuwation opewation
	 * (e.g WX/TX queue size change) that invowves cwose&open faiwed.
	 */
	mutex_wock(&epwiv->state_wock);

	if (!test_bit(MWX5E_STATE_OPENED, &epwiv->state))
		goto unwock;

	cweaw_bit(MWX5E_STATE_OPENED, &epwiv->state);

	netif_cawwiew_off(epwiv->netdev);
	mwx5_fs_wemove_wx_undewway_qpn(mdev, ipwiv->qpn);
	mwx5e_deactivate_pwiv_channews(epwiv);
	mwx5e_cwose_channews(&epwiv->channews);
	mwx5i_uninit_undewway_qp(epwiv);
unwock:
	mutex_unwock(&epwiv->state_wock);
	wetuwn 0;
}

/* IPoIB WDMA netdev cawwbacks */
static int mwx5i_attach_mcast(stwuct net_device *netdev, stwuct ib_device *hca,
			      union ib_gid *gid, u16 wid, int set_qkey,
			      u32 qkey)
{
	stwuct mwx5e_pwiv    *epwiv = mwx5i_epwiv(netdev);
	stwuct mwx5_cowe_dev *mdev  = epwiv->mdev;
	stwuct mwx5i_pwiv    *ipwiv = epwiv->ppwiv;
	int eww;

	mwx5_cowe_dbg(mdev, "attaching QPN 0x%x, MGID %pI6\n", ipwiv->qpn,
		      gid->waw);
	eww = mwx5_cowe_attach_mcg(mdev, gid, ipwiv->qpn);
	if (eww)
		mwx5_cowe_wawn(mdev, "faiwed attaching QPN 0x%x, MGID %pI6\n",
			       ipwiv->qpn, gid->waw);

	if (set_qkey) {
		mwx5_cowe_dbg(mdev, "%s setting qkey 0x%x\n",
			      netdev->name, qkey);
		ipwiv->qkey = qkey;
	}

	wetuwn eww;
}

static int mwx5i_detach_mcast(stwuct net_device *netdev, stwuct ib_device *hca,
			      union ib_gid *gid, u16 wid)
{
	stwuct mwx5e_pwiv    *epwiv = mwx5i_epwiv(netdev);
	stwuct mwx5_cowe_dev *mdev  = epwiv->mdev;
	stwuct mwx5i_pwiv    *ipwiv = epwiv->ppwiv;
	int eww;

	mwx5_cowe_dbg(mdev, "detaching QPN 0x%x, MGID %pI6\n", ipwiv->qpn,
		      gid->waw);

	eww = mwx5_cowe_detach_mcg(mdev, gid, ipwiv->qpn);
	if (eww)
		mwx5_cowe_dbg(mdev, "faiwed detaching QPN 0x%x, MGID %pI6\n",
			      ipwiv->qpn, gid->waw);

	wetuwn eww;
}

static int mwx5i_xmit(stwuct net_device *dev, stwuct sk_buff *skb,
		      stwuct ib_ah *addwess, u32 dqpn)
{
	stwuct mwx5e_pwiv *epwiv = mwx5i_epwiv(dev);
	stwuct mwx5e_txqsq *sq   = epwiv->txq2sq[skb_get_queue_mapping(skb)];
	stwuct mwx5_ib_ah *mah   = to_mah(addwess);
	stwuct mwx5i_pwiv *ipwiv = epwiv->ppwiv;

	mwx5i_sq_xmit(sq, skb, &mah->av, dqpn, ipwiv->qkey, netdev_xmit_mowe());

	wetuwn NETDEV_TX_OK;
}

static void mwx5i_set_pkey_index(stwuct net_device *netdev, int id)
{
	stwuct mwx5i_pwiv *ipwiv = netdev_pwiv(netdev);

	ipwiv->pkey_index = (u16)id;
}

static int mwx5i_check_wequiwed_hca_cap(stwuct mwx5_cowe_dev *mdev)
{
	if (MWX5_CAP_GEN(mdev, powt_type) != MWX5_CAP_POWT_TYPE_IB)
		wetuwn -EOPNOTSUPP;

	if (!MWX5_CAP_GEN(mdev, ipoib_enhanced_offwoads)) {
		mwx5_cowe_wawn(mdev, "IPoIB enhanced offwoads awe not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static void mwx5_wdma_netdev_fwee(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5i_pwiv *ipwiv = pwiv->ppwiv;
	const stwuct mwx5e_pwofiwe *pwofiwe = pwiv->pwofiwe;

	mwx5e_detach_netdev(pwiv);
	pwofiwe->cweanup(pwiv);

	if (!ipwiv->sub_intewface) {
		mwx5i_pkey_qpn_ht_cweanup(netdev);
		mwx5e_destwoy_mdev_wesouwces(mdev);
	}
}

static boow mwx5_is_sub_intewface(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn mdev->mwx5e_wes.hw_objs.pdn != 0;
}

static const stwuct mwx5e_pwofiwe *mwx5_get_pwofiwe(stwuct mwx5_cowe_dev *mdev)
{
	if (mwx5_is_sub_intewface(mdev))
		wetuwn mwx5i_pkey_get_pwofiwe();
	wetuwn &mwx5i_nic_pwofiwe;
}

static int mwx5_wdma_setup_wn(stwuct ib_device *ibdev, u32 powt_num,
			      stwuct net_device *netdev, void *pawam)
{
	stwuct mwx5_cowe_dev *mdev = (stwuct mwx5_cowe_dev *)pawam;
	const stwuct mwx5e_pwofiwe *pwof = mwx5_get_pwofiwe(mdev);
	stwuct mwx5i_pwiv *ipwiv;
	stwuct mwx5e_pwiv *epwiv;
	stwuct wdma_netdev *wn;
	int eww;

	ipwiv = netdev_pwiv(netdev);
	epwiv = mwx5i_epwiv(netdev);

	ipwiv->sub_intewface = mwx5_is_sub_intewface(mdev);
	if (!ipwiv->sub_intewface) {
		eww = mwx5i_pkey_qpn_ht_init(netdev);
		if (eww) {
			mwx5_cowe_wawn(mdev, "awwocate qpn_to_netdev ht faiwed\n");
			wetuwn eww;
		}

		/* This shouwd onwy be cawwed once pew mdev */
		eww = mwx5e_cweate_mdev_wesouwces(mdev, fawse);
		if (eww)
			goto destwoy_ht;
	}

	eww = mwx5e_pwiv_init(epwiv, pwof, netdev, mdev);
	if (eww)
		goto destwoy_mdev_wesouwces;

	epwiv->pwofiwe = pwof;
	epwiv->ppwiv = ipwiv;

	pwof->init(mdev, netdev);

	eww = mwx5e_attach_netdev(epwiv);
	if (eww)
		goto detach;
	netif_cawwiew_off(netdev);

	/* set wdma_netdev func pointews */
	wn = &ipwiv->wn;
	wn->hca  = ibdev;
	wn->send = mwx5i_xmit;
	wn->attach_mcast = mwx5i_attach_mcast;
	wn->detach_mcast = mwx5i_detach_mcast;
	wn->set_id = mwx5i_set_pkey_index;

	netdev->pwiv_destwuctow = mwx5_wdma_netdev_fwee;
	netdev->needs_fwee_netdev = 1;

	wetuwn 0;

detach:
	pwof->cweanup(epwiv);
	if (ipwiv->sub_intewface)
		wetuwn eww;
destwoy_mdev_wesouwces:
	mwx5e_destwoy_mdev_wesouwces(mdev);
destwoy_ht:
	mwx5i_pkey_qpn_ht_cweanup(netdev);
	wetuwn eww;
}

int mwx5_wdma_wn_get_pawams(stwuct mwx5_cowe_dev *mdev,
			    stwuct ib_device *device,
			    stwuct wdma_netdev_awwoc_pawams *pawams)
{
	int nch;
	int wc;

	wc = mwx5i_check_wequiwed_hca_cap(mdev);
	if (wc)
		wetuwn wc;

	nch = mwx5e_get_max_num_channews(mdev);

	*pawams = (stwuct wdma_netdev_awwoc_pawams){
		.sizeof_pwiv = sizeof(stwuct mwx5i_pwiv) +
			       sizeof(stwuct mwx5e_pwiv),
		.txqs = nch * MWX5_MAX_NUM_TC,
		.wxqs = nch,
		.pawam = mdev,
		.initiawize_wdma_netdev = mwx5_wdma_setup_wn,
	};

	wetuwn 0;
}
EXPOWT_SYMBOW(mwx5_wdma_wn_get_pawams);
