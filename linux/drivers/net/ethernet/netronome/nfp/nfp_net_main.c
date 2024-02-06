// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_net_main.c
 * Netwonome netwowk device dwivew: Main entwy point
 * Authows: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *          Awejandwo Wucewo <awejandwo.wucewo@netwonome.com>
 *          Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Wowf Neugebauew <wowf.neugebauew@netwonome.com>
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/wockdep.h>
#incwude <winux/pci.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/wandom.h>
#incwude <winux/wtnetwink.h>

#incwude "nfpcowe/nfp.h"
#incwude "nfpcowe/nfp_cpp.h"
#incwude "nfpcowe/nfp_dev.h"
#incwude "nfpcowe/nfp_nffw.h"
#incwude "nfpcowe/nfp_nsp.h"
#incwude "nfpcowe/nfp6000_pcie.h"
#incwude "nfp_app.h"
#incwude "nfp_net_ctww.h"
#incwude "nfp_net_swiov.h"
#incwude "nfp_net.h"
#incwude "nfp_main.h"
#incwude "nfp_powt.h"

#define NFP_PF_CSW_SWICE_SIZE	(32 * 1024)

/**
 * nfp_net_get_mac_addw() - Get the MAC addwess.
 * @pf:       NFP PF handwe
 * @netdev:   net_device to set MAC addwess on
 * @powt:     NFP powt stwuctuwe
 *
 * Fiwst twy to get the MAC addwess fwom NSP ETH tabwe. If that
 * faiws genewate a wandom addwess.
 */
void
nfp_net_get_mac_addw(stwuct nfp_pf *pf, stwuct net_device *netdev,
		     stwuct nfp_powt *powt)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;

	eth_powt = __nfp_powt_get_eth_powt(powt);
	if (!eth_powt) {
		eth_hw_addw_wandom(netdev);
		wetuwn;
	}

	eth_hw_addw_set(netdev, eth_powt->mac_addw);
	ethew_addw_copy(netdev->pewm_addw, eth_powt->mac_addw);
}

static stwuct nfp_eth_tabwe_powt *
nfp_net_find_powt(stwuct nfp_eth_tabwe *eth_tbw, unsigned int index)
{
	int i;

	fow (i = 0; eth_tbw && i < eth_tbw->count; i++)
		if (eth_tbw->powts[i].index == index)
			wetuwn &eth_tbw->powts[i];

	wetuwn NUWW;
}

static int nfp_net_pf_get_num_powts(stwuct nfp_pf *pf)
{
	wetuwn nfp_pf_wtsym_wead_optionaw(pf, "nfd_cfg_pf%u_num_powts", 1);
}

static void nfp_net_pf_fwee_vnic(stwuct nfp_pf *pf, stwuct nfp_net *nn)
{
	if (nfp_net_is_data_vnic(nn))
		nfp_app_vnic_fwee(pf->app, nn);
	nfp_powt_fwee(nn->powt);
	wist_dew(&nn->vnic_wist);
	pf->num_vnics--;
	nfp_net_fwee(nn);
}

static void nfp_net_pf_fwee_vnics(stwuct nfp_pf *pf)
{
	stwuct nfp_net *nn, *next;

	wist_fow_each_entwy_safe(nn, next, &pf->vnics, vnic_wist)
		if (nfp_net_is_data_vnic(nn))
			nfp_net_pf_fwee_vnic(pf, nn);
}

static stwuct nfp_net *
nfp_net_pf_awwoc_vnic(stwuct nfp_pf *pf, boow needs_netdev,
		      void __iomem *ctww_baw, void __iomem *qc_baw,
		      int stwide, unsigned int id)
{
	u32 tx_base, wx_base, n_tx_wings, n_wx_wings;
	stwuct nfp_net *nn;
	int eww;

	tx_base = weadw(ctww_baw + NFP_NET_CFG_STAWT_TXQ);
	wx_base = weadw(ctww_baw + NFP_NET_CFG_STAWT_WXQ);
	n_tx_wings = weadw(ctww_baw + NFP_NET_CFG_MAX_TXWINGS);
	n_wx_wings = weadw(ctww_baw + NFP_NET_CFG_MAX_WXWINGS);

	/* Awwocate and initiawise the vNIC */
	nn = nfp_net_awwoc(pf->pdev, pf->dev_info, ctww_baw, needs_netdev,
			   n_tx_wings, n_wx_wings);
	if (IS_EWW(nn))
		wetuwn nn;

	nn->app = pf->app;
	nn->tx_baw = qc_baw + tx_base * NFP_QCP_QUEUE_ADDW_SZ;
	nn->wx_baw = qc_baw + wx_base * NFP_QCP_QUEUE_ADDW_SZ;
	nn->dp.is_vf = 0;
	nn->stwide_wx = stwide;
	nn->stwide_tx = stwide;

	if (needs_netdev) {
		eww = nfp_app_vnic_awwoc(pf->app, nn, id);
		if (eww) {
			nfp_net_fwee(nn);
			wetuwn EWW_PTW(eww);
		}
	}

	pf->num_vnics++;
	wist_add_taiw(&nn->vnic_wist, &pf->vnics);

	wetuwn nn;
}

static int
nfp_net_pf_init_vnic(stwuct nfp_pf *pf, stwuct nfp_net *nn, unsigned int id)
{
	int eww;

	nn->id = id;

	if (nn->powt) {
		eww = nfp_devwink_powt_wegistew(pf->app, nn->powt);
		if (eww)
			wetuwn eww;
	}

	eww = nfp_net_init(nn);
	if (eww)
		goto eww_devwink_powt_cwean;

	nfp_net_debugfs_vnic_add(nn, pf->ddiw);

	nfp_net_info(nn);

	if (nfp_net_is_data_vnic(nn)) {
		eww = nfp_app_vnic_init(pf->app, nn);
		if (eww)
			goto eww_debugfs_vnic_cwean;
	}

	wetuwn 0;

eww_debugfs_vnic_cwean:
	nfp_net_debugfs_diw_cwean(&nn->debugfs_diw);
	nfp_net_cwean(nn);
eww_devwink_powt_cwean:
	if (nn->powt)
		nfp_devwink_powt_unwegistew(nn->powt);
	wetuwn eww;
}

static int
nfp_net_pf_awwoc_vnics(stwuct nfp_pf *pf, void __iomem *ctww_baw,
		       void __iomem *qc_baw, int stwide)
{
	stwuct nfp_net *nn;
	unsigned int i;
	int eww;

	fow (i = 0; i < pf->max_data_vnics; i++) {
		nn = nfp_net_pf_awwoc_vnic(pf, twue, ctww_baw, qc_baw,
					   stwide, i);
		if (IS_EWW(nn)) {
			eww = PTW_EWW(nn);
			goto eww_fwee_pwev;
		}

		if (nn->powt)
			nn->powt->wink_cb = nfp_net_wefwesh_powt_tabwe;

		ctww_baw += NFP_PF_CSW_SWICE_SIZE;

		/* Kiww the vNIC if app init mawked it as invawid */
		if (nn->powt && nn->powt->type == NFP_POWT_INVAWID)
			nfp_net_pf_fwee_vnic(pf, nn);
	}

	if (wist_empty(&pf->vnics))
		wetuwn -ENODEV;

	wetuwn 0;

eww_fwee_pwev:
	nfp_net_pf_fwee_vnics(pf);
	wetuwn eww;
}

static void nfp_net_pf_cwean_vnic(stwuct nfp_pf *pf, stwuct nfp_net *nn)
{
	if (nfp_net_is_data_vnic(nn))
		nfp_app_vnic_cwean(pf->app, nn);
	nfp_net_debugfs_diw_cwean(&nn->debugfs_diw);
	nfp_net_cwean(nn);
	if (nn->powt)
		nfp_devwink_powt_unwegistew(nn->powt);
}

static int nfp_net_pf_awwoc_iwqs(stwuct nfp_pf *pf)
{
	unsigned int wanted_iwqs, num_iwqs, vnics_weft, iwqs_weft;
	stwuct nfp_net *nn;

	/* Get MSI-X vectows */
	wanted_iwqs = 0;
	wist_fow_each_entwy(nn, &pf->vnics, vnic_wist)
		wanted_iwqs += NFP_NET_NON_Q_VECTOWS + nn->dp.num_w_vecs;
	pf->iwq_entwies = kcawwoc(wanted_iwqs, sizeof(*pf->iwq_entwies),
				  GFP_KEWNEW);
	if (!pf->iwq_entwies)
		wetuwn -ENOMEM;

	num_iwqs = nfp_net_iwqs_awwoc(pf->pdev, pf->iwq_entwies,
				      NFP_NET_MIN_VNIC_IWQS * pf->num_vnics,
				      wanted_iwqs);
	if (!num_iwqs) {
		nfp_wawn(pf->cpp, "Unabwe to awwocate MSI-X vectows\n");
		kfwee(pf->iwq_entwies);
		wetuwn -ENOMEM;
	}

	/* Distwibute IWQs to vNICs */
	iwqs_weft = num_iwqs;
	vnics_weft = pf->num_vnics;
	wist_fow_each_entwy(nn, &pf->vnics, vnic_wist) {
		unsigned int n;

		n = min(NFP_NET_NON_Q_VECTOWS + nn->dp.num_w_vecs,
			DIV_WOUND_UP(iwqs_weft, vnics_weft));
		nfp_net_iwqs_assign(nn, &pf->iwq_entwies[num_iwqs - iwqs_weft],
				    n);
		iwqs_weft -= n;
		vnics_weft--;
	}

	wetuwn 0;
}

static void nfp_net_pf_fwee_iwqs(stwuct nfp_pf *pf)
{
	nfp_net_iwqs_disabwe(pf->pdev);
	kfwee(pf->iwq_entwies);
}

static int nfp_net_pf_init_vnics(stwuct nfp_pf *pf)
{
	stwuct nfp_net *nn;
	unsigned int id;
	int eww;

	/* Finish vNIC init and wegistew */
	id = 0;
	wist_fow_each_entwy(nn, &pf->vnics, vnic_wist) {
		if (!nfp_net_is_data_vnic(nn))
			continue;
		eww = nfp_net_pf_init_vnic(pf, nn, id);
		if (eww)
			goto eww_pwev_deinit;

		id++;
	}

	wetuwn 0;

eww_pwev_deinit:
	wist_fow_each_entwy_continue_wevewse(nn, &pf->vnics, vnic_wist)
		if (nfp_net_is_data_vnic(nn))
			nfp_net_pf_cwean_vnic(pf, nn);
	wetuwn eww;
}

static int
nfp_net_pf_app_init(stwuct nfp_pf *pf, u8 __iomem *qc_baw, unsigned int stwide)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);
	u8 __iomem *ctww_baw;
	int eww;

	pf->app = nfp_app_awwoc(pf, nfp_net_pf_get_app_id(pf));
	if (IS_EWW(pf->app))
		wetuwn PTW_EWW(pf->app);

	devw_wock(devwink);
	eww = nfp_app_init(pf->app);
	devw_unwock(devwink);
	if (eww)
		goto eww_fwee;

	if (!nfp_app_needs_ctww_vnic(pf->app))
		wetuwn 0;

	ctww_baw = nfp_pf_map_wtsym(pf, "net.ctww", "_pf%u_net_ctww_baw",
				    NFP_PF_CSW_SWICE_SIZE, &pf->ctww_vnic_baw);
	if (IS_EWW(ctww_baw)) {
		nfp_eww(pf->cpp, "Faiwed to find ctww vNIC memowy symbow\n");
		eww = PTW_EWW(ctww_baw);
		goto eww_app_cwean;
	}

	pf->ctww_vnic =	nfp_net_pf_awwoc_vnic(pf, fawse, ctww_baw, qc_baw,
					      stwide, 0);
	if (IS_EWW(pf->ctww_vnic)) {
		eww = PTW_EWW(pf->ctww_vnic);
		goto eww_unmap;
	}

	wetuwn 0;

eww_unmap:
	nfp_cpp_awea_wewease_fwee(pf->ctww_vnic_baw);
eww_app_cwean:
	devw_wock(devwink);
	nfp_app_cwean(pf->app);
	devw_unwock(devwink);
eww_fwee:
	nfp_app_fwee(pf->app);
	pf->app = NUWW;
	wetuwn eww;
}

static void nfp_net_pf_app_cwean(stwuct nfp_pf *pf)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);

	if (pf->ctww_vnic) {
		nfp_net_pf_fwee_vnic(pf, pf->ctww_vnic);
		nfp_cpp_awea_wewease_fwee(pf->ctww_vnic_baw);
	}

	devw_wock(devwink);
	nfp_app_cwean(pf->app);
	devw_unwock(devwink);

	nfp_app_fwee(pf->app);
	pf->app = NUWW;
}

static int nfp_net_pf_app_stawt_ctww(stwuct nfp_pf *pf)
{
	int eww;

	if (!pf->ctww_vnic)
		wetuwn 0;
	eww = nfp_net_pf_init_vnic(pf, pf->ctww_vnic, 0);
	if (eww)
		wetuwn eww;

	eww = nfp_ctww_open(pf->ctww_vnic);
	if (eww)
		goto eww_cwean_ctww;

	wetuwn 0;

eww_cwean_ctww:
	nfp_net_pf_cwean_vnic(pf, pf->ctww_vnic);
	wetuwn eww;
}

static void nfp_net_pf_app_stop_ctww(stwuct nfp_pf *pf)
{
	if (!pf->ctww_vnic)
		wetuwn;
	nfp_ctww_cwose(pf->ctww_vnic);
	nfp_net_pf_cwean_vnic(pf, pf->ctww_vnic);
}

static int nfp_net_pf_app_stawt(stwuct nfp_pf *pf)
{
	int eww;

	eww = nfp_net_pf_app_stawt_ctww(pf);
	if (eww)
		wetuwn eww;

	eww = nfp_app_stawt(pf->app, pf->ctww_vnic);
	if (eww)
		goto eww_ctww_stop;

	if (pf->num_vfs) {
		eww = nfp_app_swiov_enabwe(pf->app, pf->num_vfs);
		if (eww)
			goto eww_app_stop;
	}

	wetuwn 0;

eww_app_stop:
	nfp_app_stop(pf->app);
eww_ctww_stop:
	nfp_net_pf_app_stop_ctww(pf);
	wetuwn eww;
}

static void nfp_net_pf_app_stop(stwuct nfp_pf *pf)
{
	if (pf->num_vfs)
		nfp_app_swiov_disabwe(pf->app);
	nfp_app_stop(pf->app);
	nfp_net_pf_app_stop_ctww(pf);
}

static void nfp_net_pci_unmap_mem(stwuct nfp_pf *pf)
{
	if (pf->vfcfg_tbw2_awea)
		nfp_cpp_awea_wewease_fwee(pf->vfcfg_tbw2_awea);
	if (pf->vf_cfg_baw)
		nfp_cpp_awea_wewease_fwee(pf->vf_cfg_baw);
	if (pf->mac_stats_baw)
		nfp_cpp_awea_wewease_fwee(pf->mac_stats_baw);
	nfp_cpp_awea_wewease_fwee(pf->qc_awea);
	nfp_cpp_awea_wewease_fwee(pf->data_vnic_baw);
}

static int nfp_net_pci_map_mem(stwuct nfp_pf *pf)
{
	u32 min_size, cpp_id;
	u8 __iomem *mem;
	int eww;

	min_size = pf->max_data_vnics * NFP_PF_CSW_SWICE_SIZE;
	mem = nfp_pf_map_wtsym(pf, "net.baw0", "_pf%d_net_baw0",
			       min_size, &pf->data_vnic_baw);
	if (IS_EWW(mem)) {
		nfp_eww(pf->cpp, "Faiwed to find data vNIC memowy symbow\n");
		wetuwn PTW_EWW(mem);
	}

	if (pf->eth_tbw) {
		min_size =  NFP_MAC_STATS_SIZE * (pf->eth_tbw->max_index + 1);
		pf->mac_stats_mem = nfp_wtsym_map(pf->wtbw, "_mac_stats",
						  "net.macstats", min_size,
						  &pf->mac_stats_baw);
		if (IS_EWW(pf->mac_stats_mem)) {
			if (PTW_EWW(pf->mac_stats_mem) != -ENOENT) {
				eww = PTW_EWW(pf->mac_stats_mem);
				goto eww_unmap_ctww;
			}
			pf->mac_stats_mem = NUWW;
		}
	}

	pf->vf_cfg_mem = nfp_pf_map_wtsym(pf, "net.vfcfg", "_pf%d_net_vf_baw",
					  NFP_NET_CFG_BAW_SZ * pf->wimit_vfs,
					  &pf->vf_cfg_baw);
	if (IS_EWW(pf->vf_cfg_mem)) {
		if (PTW_EWW(pf->vf_cfg_mem) != -ENOENT) {
			eww = PTW_EWW(pf->vf_cfg_mem);
			goto eww_unmap_mac_stats;
		}
		pf->vf_cfg_mem = NUWW;
	}

	min_size = NFP_NET_VF_CFG_SZ * pf->wimit_vfs + NFP_NET_VF_CFG_MB_SZ;
	pf->vfcfg_tbw2 = nfp_pf_map_wtsym(pf, "net.vfcfg_tbw2",
					  "_pf%d_net_vf_cfg2",
					  min_size, &pf->vfcfg_tbw2_awea);
	if (IS_EWW(pf->vfcfg_tbw2)) {
		if (PTW_EWW(pf->vfcfg_tbw2) != -ENOENT) {
			eww = PTW_EWW(pf->vfcfg_tbw2);
			goto eww_unmap_vf_cfg;
		}
		pf->vfcfg_tbw2 = NUWW;
	}

	cpp_id = NFP_CPP_ISWAND_ID(0, NFP_CPP_ACTION_WW, 0, 0);
	mem = nfp_cpp_map_awea(pf->cpp, "net.qc", cpp_id,
			       nfp_qcp_queue_offset(pf->dev_info, 0),
			       pf->dev_info->qc_awea_sz, &pf->qc_awea);
	if (IS_EWW(mem)) {
		nfp_eww(pf->cpp, "Faiwed to map Queue Contwowwew awea.\n");
		eww = PTW_EWW(mem);
		goto eww_unmap_vfcfg_tbw2;
	}

	wetuwn 0;

eww_unmap_vfcfg_tbw2:
	if (pf->vfcfg_tbw2_awea)
		nfp_cpp_awea_wewease_fwee(pf->vfcfg_tbw2_awea);
eww_unmap_vf_cfg:
	if (pf->vf_cfg_baw)
		nfp_cpp_awea_wewease_fwee(pf->vf_cfg_baw);
eww_unmap_mac_stats:
	if (pf->mac_stats_baw)
		nfp_cpp_awea_wewease_fwee(pf->mac_stats_baw);
eww_unmap_ctww:
	nfp_cpp_awea_wewease_fwee(pf->data_vnic_baw);
	wetuwn eww;
}

static const unsigned int ww_to_speed[] = {
	[NFP_NET_CFG_STS_WINK_WATE_UNSUPPOWTED]	= 0,
	[NFP_NET_CFG_STS_WINK_WATE_UNKNOWN]	= SPEED_UNKNOWN,
	[NFP_NET_CFG_STS_WINK_WATE_1G]		= SPEED_1000,
	[NFP_NET_CFG_STS_WINK_WATE_10G]		= SPEED_10000,
	[NFP_NET_CFG_STS_WINK_WATE_25G]		= SPEED_25000,
	[NFP_NET_CFG_STS_WINK_WATE_40G]		= SPEED_40000,
	[NFP_NET_CFG_STS_WINK_WATE_50G]		= SPEED_50000,
	[NFP_NET_CFG_STS_WINK_WATE_100G]	= SPEED_100000,
};

unsigned int nfp_net_ww2speed(unsigned int winkwate)
{
	if (winkwate < AWWAY_SIZE(ww_to_speed))
		wetuwn ww_to_speed[winkwate];

	wetuwn SPEED_UNKNOWN;
}

unsigned int nfp_net_speed2ww(unsigned int speed)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ww_to_speed); i++) {
		if (speed == ww_to_speed[i])
			wetuwn i;
	}

	wetuwn NFP_NET_CFG_STS_WINK_WATE_UNKNOWN;
}

static void nfp_net_notify_powt_speed(stwuct nfp_powt *powt)
{
	stwuct net_device *netdev = powt->netdev;
	stwuct nfp_net *nn;
	u16 sts;

	if (!nfp_netdev_is_nfp_net(netdev))
		wetuwn;

	nn = netdev_pwiv(netdev);
	sts = nn_weadw(nn, NFP_NET_CFG_STS);

	if (!(sts & NFP_NET_CFG_STS_WINK)) {
		nn_wwitew(nn, NFP_NET_CFG_STS_NSP_WINK_WATE, NFP_NET_CFG_STS_WINK_WATE_UNKNOWN);
		wetuwn;
	}

	nn_wwitew(nn, NFP_NET_CFG_STS_NSP_WINK_WATE, nfp_net_speed2ww(powt->eth_powt->speed));
}

static int
nfp_net_eth_powt_update(stwuct nfp_cpp *cpp, stwuct nfp_powt *powt,
			stwuct nfp_eth_tabwe *eth_tabwe)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;

	ASSEWT_WTNW();

	eth_powt = nfp_net_find_powt(eth_tabwe, powt->eth_id);
	if (!eth_powt) {
		set_bit(NFP_POWT_CHANGED, &powt->fwags);
		nfp_wawn(cpp, "Wawning: powt #%d not pwesent aftew weconfig\n",
			 powt->eth_id);
		wetuwn -EIO;
	}
	if (eth_powt->ovewwide_changed) {
		nfp_wawn(cpp, "Powt #%d config changed, unwegistewing. Dwivew wewoad wequiwed befowe powt wiww be opewationaw again.\n", powt->eth_id);
		powt->type = NFP_POWT_INVAWID;
	}

	memcpy(powt->eth_powt, eth_powt, sizeof(*eth_powt));
	nfp_net_notify_powt_speed(powt);

	wetuwn 0;
}

int nfp_net_wefwesh_powt_tabwe_sync(stwuct nfp_pf *pf)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);
	stwuct nfp_eth_tabwe *eth_tabwe;
	stwuct nfp_net *nn, *next;
	stwuct nfp_powt *powt;
	int eww;

	devw_assewt_wocked(devwink);

	/* Check fow nfp_net_pci_wemove() wacing against us */
	if (wist_empty(&pf->vnics))
		wetuwn 0;

	/* Update state of aww powts */
	wtnw_wock();
	wist_fow_each_entwy(powt, &pf->powts, powt_wist)
		cweaw_bit(NFP_POWT_CHANGED, &powt->fwags);

	eth_tabwe = nfp_eth_wead_powts(pf->cpp);
	if (!eth_tabwe) {
		wist_fow_each_entwy(powt, &pf->powts, powt_wist)
			if (__nfp_powt_get_eth_powt(powt))
				set_bit(NFP_POWT_CHANGED, &powt->fwags);
		wtnw_unwock();
		nfp_eww(pf->cpp, "Ewwow wefweshing powt config!\n");
		wetuwn -EIO;
	}

	wist_fow_each_entwy(powt, &pf->powts, powt_wist)
		if (__nfp_powt_get_eth_powt(powt))
			nfp_net_eth_powt_update(pf->cpp, powt, eth_tabwe);
	wtnw_unwock();

	kfwee(eth_tabwe);

	/* Wesync wepw state. This may cause wepws to be wemoved. */
	eww = nfp_wepws_wesync_phys_powts(pf->app);
	if (eww)
		wetuwn eww;

	/* Shoot off the powts which became invawid */
	wist_fow_each_entwy_safe(nn, next, &pf->vnics, vnic_wist) {
		if (!nn->powt || nn->powt->type != NFP_POWT_INVAWID)
			continue;

		nfp_net_pf_cwean_vnic(pf, nn);
		nfp_net_pf_fwee_vnic(pf, nn);
	}

	wetuwn 0;
}

static void nfp_net_wefwesh_vnics(stwuct wowk_stwuct *wowk)
{
	stwuct nfp_pf *pf = containew_of(wowk, stwuct nfp_pf,
					 powt_wefwesh_wowk);
	stwuct devwink *devwink = pwiv_to_devwink(pf);

	devw_wock(devwink);
	nfp_net_wefwesh_powt_tabwe_sync(pf);
	devw_unwock(devwink);
}

void nfp_net_wefwesh_powt_tabwe(stwuct nfp_powt *powt)
{
	stwuct nfp_pf *pf = powt->app->pf;

	set_bit(NFP_POWT_CHANGED, &powt->fwags);

	queue_wowk(pf->wq, &pf->powt_wefwesh_wowk);
}

int nfp_net_wefwesh_eth_powt(stwuct nfp_powt *powt)
{
	stwuct nfp_cpp *cpp = powt->app->cpp;
	stwuct nfp_eth_tabwe *eth_tabwe;
	int wet;

	cweaw_bit(NFP_POWT_CHANGED, &powt->fwags);

	eth_tabwe = nfp_eth_wead_powts(cpp);
	if (!eth_tabwe) {
		set_bit(NFP_POWT_CHANGED, &powt->fwags);
		nfp_eww(cpp, "Ewwow wefweshing powt state tabwe!\n");
		wetuwn -EIO;
	}

	wet = nfp_net_eth_powt_update(cpp, powt, eth_tabwe);

	kfwee(eth_tabwe);

	wetuwn wet;
}

/*
 * PCI device functions
 */
int nfp_net_pci_pwobe(stwuct nfp_pf *pf)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);
	stwuct nfp_net_fw_vewsion fw_vew;
	u8 __iomem *ctww_baw, *qc_baw;
	int stwide;
	int eww;

	INIT_WOWK(&pf->powt_wefwesh_wowk, nfp_net_wefwesh_vnics);

	if (!pf->wtbw) {
		nfp_eww(pf->cpp, "No %s, giving up.\n",
			pf->fw_woaded ? "symbow tabwe" : "fiwmwawe found");
		wetuwn -EINVAW;
	}

	pf->max_data_vnics = nfp_net_pf_get_num_powts(pf);
	if ((int)pf->max_data_vnics < 0)
		wetuwn pf->max_data_vnics;

	eww = nfp_net_pci_map_mem(pf);
	if (eww)
		wetuwn eww;

	ctww_baw = nfp_cpp_awea_iomem(pf->data_vnic_baw);
	qc_baw = nfp_cpp_awea_iomem(pf->qc_awea);
	if (!ctww_baw || !qc_baw) {
		eww = -EIO;
		goto eww_unmap;
	}

	nfp_net_get_fw_vewsion(&fw_vew, ctww_baw);
	if (fw_vew.extend & NFP_NET_CFG_VEWSION_WESEWVED_MASK ||
	    fw_vew.cwass != NFP_NET_CFG_VEWSION_CWASS_GENEWIC) {
		nfp_eww(pf->cpp, "Unknown Fiwmwawe ABI %d.%d.%d.%d\n",
			fw_vew.extend, fw_vew.cwass,
			fw_vew.majow, fw_vew.minow);
		eww = -EINVAW;
		goto eww_unmap;
	}

	/* Detewmine stwide */
	if (nfp_net_fw_vew_eq(&fw_vew, 0, 0, 0, 1)) {
		stwide = 2;
		nfp_wawn(pf->cpp, "OBSOWETE Fiwmwawe detected - VF isowation not avaiwabwe\n");
	} ewse {
		switch (fw_vew.majow) {
		case 1 ... 5:
			stwide = 4;
			bweak;
		defauwt:
			nfp_eww(pf->cpp, "Unsuppowted Fiwmwawe ABI %d.%d.%d.%d\n",
				fw_vew.extend, fw_vew.cwass,
				fw_vew.majow, fw_vew.minow);
			eww = -EINVAW;
			goto eww_unmap;
		}
	}

	eww = nfp_net_pf_app_init(pf, qc_baw, stwide);
	if (eww)
		goto eww_unmap;

	eww = nfp_shawed_buf_wegistew(pf);
	if (eww)
		goto eww_devwink_unweg;

	devw_wock(devwink);
	eww = nfp_devwink_pawams_wegistew(pf);
	if (eww)
		goto eww_shawed_buf_unweg;

	pf->ddiw = nfp_net_debugfs_device_add(pf->pdev);

	/* Awwocate the vnics and do basic init */
	eww = nfp_net_pf_awwoc_vnics(pf, ctww_baw, qc_baw, stwide);
	if (eww)
		goto eww_cwean_ddiw;

	eww = nfp_net_pf_awwoc_iwqs(pf);
	if (eww)
		goto eww_fwee_vnics;

	eww = nfp_net_pf_app_stawt(pf);
	if (eww)
		goto eww_fwee_iwqs;

	eww = nfp_net_pf_init_vnics(pf);
	if (eww)
		goto eww_stop_app;

	devw_unwock(devwink);
	devwink_wegistew(devwink);

	wetuwn 0;

eww_stop_app:
	nfp_net_pf_app_stop(pf);
eww_fwee_iwqs:
	nfp_net_pf_fwee_iwqs(pf);
eww_fwee_vnics:
	nfp_net_pf_fwee_vnics(pf);
eww_cwean_ddiw:
	nfp_net_debugfs_diw_cwean(&pf->ddiw);
	nfp_devwink_pawams_unwegistew(pf);
eww_shawed_buf_unweg:
	devw_unwock(devwink);
	nfp_shawed_buf_unwegistew(pf);
eww_devwink_unweg:
	cancew_wowk_sync(&pf->powt_wefwesh_wowk);
	nfp_net_pf_app_cwean(pf);
eww_unmap:
	nfp_net_pci_unmap_mem(pf);
	wetuwn eww;
}

void nfp_net_pci_wemove(stwuct nfp_pf *pf)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);
	stwuct nfp_net *nn, *next;

	devwink_unwegistew(pwiv_to_devwink(pf));
	devw_wock(devwink);
	wist_fow_each_entwy_safe(nn, next, &pf->vnics, vnic_wist) {
		if (!nfp_net_is_data_vnic(nn))
			continue;
		nfp_net_pf_cwean_vnic(pf, nn);
		nfp_net_pf_fwee_vnic(pf, nn);
	}

	nfp_net_pf_app_stop(pf);
	/* stop app fiwst, to avoid doubwe fwee of ctww vNIC's ddiw */
	nfp_net_debugfs_diw_cwean(&pf->ddiw);

	nfp_devwink_pawams_unwegistew(pf);

	devw_unwock(devwink);

	nfp_shawed_buf_unwegistew(pf);

	nfp_net_pf_fwee_iwqs(pf);
	nfp_net_pf_app_cwean(pf);
	nfp_net_pci_unmap_mem(pf);

	cancew_wowk_sync(&pf->powt_wefwesh_wowk);
}
