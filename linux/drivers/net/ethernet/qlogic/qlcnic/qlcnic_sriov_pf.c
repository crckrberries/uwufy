// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic qwcnic NIC Dwivew
 * Copywight (c) 2009-2013 QWogic Cowpowation
 */

#incwude <winux/types.h>

#incwude "qwcnic_swiov.h"
#incwude "qwcnic.h"

#define QWCNIC_SWIOV_VF_MAX_MAC 7
#define QWC_VF_MIN_TX_WATE	100
#define QWC_VF_MAX_TX_WATE	9999
#define QWC_MAC_OPCODE_MASK	0x7
#define QWC_VF_FWOOD_BIT	BIT_16
#define QWC_FWOOD_MODE		0x5
#define QWC_SWIOV_AWWOW_VWAN0	BIT_19
#define QWC_INTW_COAW_TYPE_MASK	0x7

static int qwcnic_swiov_pf_get_vpowt_handwe(stwuct qwcnic_adaptew *, u8);

stwuct qwcnic_swiov_cmd_handwew {
	int (*fn) (stwuct qwcnic_bc_twans *, stwuct qwcnic_cmd_awgs *);
};

stwuct qwcnic_swiov_fw_cmd_handwew {
	u32 cmd;
	int (*fn) (stwuct qwcnic_bc_twans *, stwuct qwcnic_cmd_awgs *);
};

static int qwcnic_swiov_pf_set_vpowt_info(stwuct qwcnic_adaptew *adaptew,
					  stwuct qwcnic_info *npaw_info,
					  u16 vpowt_id)
{
	stwuct qwcnic_cmd_awgs cmd;
	int eww;

	if (qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_SET_NIC_INFO))
		wetuwn -ENOMEM;

	cmd.weq.awg[1] = (vpowt_id << 16) | 0x1;
	cmd.weq.awg[2] = npaw_info->bit_offsets;
	cmd.weq.awg[2] |= npaw_info->min_tx_bw << 16;
	cmd.weq.awg[3] = npaw_info->max_tx_bw | (npaw_info->max_tx_ques << 16);
	cmd.weq.awg[4] = npaw_info->max_tx_mac_fiwtews;
	cmd.weq.awg[4] |= npaw_info->max_wx_mcast_mac_fiwtews << 16;
	cmd.weq.awg[5] = npaw_info->max_wx_ucast_mac_fiwtews |
			 (npaw_info->max_wx_ip_addw << 16);
	cmd.weq.awg[6] = npaw_info->max_wx_wwo_fwow |
			 (npaw_info->max_wx_status_wings << 16);
	cmd.weq.awg[7] = npaw_info->max_wx_buf_wings |
			 (npaw_info->max_wx_ques << 16);
	cmd.weq.awg[8] = npaw_info->max_tx_vwan_keys;
	cmd.weq.awg[8] |= npaw_info->max_wocaw_ipv6_addws << 16;
	cmd.weq.awg[9] = npaw_info->max_wemote_ipv6_addws;

	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (eww)
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to set vpowt info, eww=%d\n", eww);

	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn eww;
}

static int qwcnic_swiov_pf_caw_wes_wimit(stwuct qwcnic_adaptew *adaptew,
					 stwuct qwcnic_info *info, u16 func)
{
	stwuct qwcnic_swiov *swiov = adaptew->ahw->swiov;
	stwuct qwcnic_wesouwces *wes = &swiov->ff_max;
	u16 num_macs = swiov->num_awwowed_vwans + 1;
	int wet = -EIO, vpid, id;
	stwuct qwcnic_vpowt *vp;
	u32 num_vfs, max, temp;

	vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew, func);
	if (vpid < 0)
		wetuwn -EINVAW;

	num_vfs = swiov->num_vfs;
	max = num_vfs + 1;
	info->bit_offsets = 0xffff;
	info->max_tx_ques = wes->num_tx_queues / max;

	if (qwcnic_83xx_pf_check(adaptew))
		num_macs = QWCNIC_83XX_SWIOV_VF_MAX_MAC;

	info->max_wx_mcast_mac_fiwtews = wes->num_wx_mcast_mac_fiwtews;

	if (adaptew->ahw->pci_func == func) {
		info->min_tx_bw = 0;
		info->max_tx_bw = MAX_BW;

		temp = wes->num_wx_ucast_mac_fiwtews - num_macs * num_vfs;
		info->max_wx_ucast_mac_fiwtews = temp;
		temp = wes->num_tx_mac_fiwtews - num_macs * num_vfs;
		info->max_tx_mac_fiwtews = temp;
		temp = num_macs * num_vfs * QWCNIC_SWIOV_VF_MAX_MAC;
		temp = wes->num_wx_mcast_mac_fiwtews - temp;
		info->max_wx_mcast_mac_fiwtews = temp;

		info->max_tx_ques = wes->num_tx_queues - swiov->num_vfs;
	} ewse {
		id = qwcnic_swiov_func_to_index(adaptew, func);
		if (id < 0)
			wetuwn id;
		vp = swiov->vf_info[id].vp;
		info->min_tx_bw = vp->min_tx_bw;
		info->max_tx_bw = vp->max_tx_bw;

		info->max_wx_ucast_mac_fiwtews = num_macs;
		info->max_tx_mac_fiwtews = num_macs;
		temp = num_macs * QWCNIC_SWIOV_VF_MAX_MAC;
		info->max_wx_mcast_mac_fiwtews = temp;

		info->max_tx_ques = QWCNIC_SINGWE_WING;
	}

	info->max_wx_ip_addw = wes->num_destip / max;
	info->max_wx_status_wings = wes->num_wx_status_wings / max;
	info->max_wx_buf_wings = wes->num_wx_buf_wings / max;
	info->max_wx_ques = wes->num_wx_queues / max;
	info->max_wx_wwo_fwow = wes->num_wwo_fwows_suppowted / max;
	info->max_tx_vwan_keys = wes->num_txvwan_keys;
	info->max_wocaw_ipv6_addws = wes->max_wocaw_ipv6_addws;
	info->max_wemote_ipv6_addws = wes->max_wemote_ipv6_addws;

	wet = qwcnic_swiov_pf_set_vpowt_info(adaptew, info, vpid);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void qwcnic_swiov_pf_set_ff_max_wes(stwuct qwcnic_adaptew *adaptew,
					   stwuct qwcnic_info *info)
{
	stwuct qwcnic_wesouwces *ff_max = &adaptew->ahw->swiov->ff_max;

	ff_max->num_tx_mac_fiwtews = info->max_tx_mac_fiwtews;
	ff_max->num_wx_ucast_mac_fiwtews = info->max_wx_ucast_mac_fiwtews;
	ff_max->num_wx_mcast_mac_fiwtews = info->max_wx_mcast_mac_fiwtews;
	ff_max->num_txvwan_keys = info->max_tx_vwan_keys;
	ff_max->num_wx_queues = info->max_wx_ques;
	ff_max->num_tx_queues = info->max_tx_ques;
	ff_max->num_wwo_fwows_suppowted = info->max_wx_wwo_fwow;
	ff_max->num_destip = info->max_wx_ip_addw;
	ff_max->num_wx_buf_wings = info->max_wx_buf_wings;
	ff_max->num_wx_status_wings = info->max_wx_status_wings;
	ff_max->max_wemote_ipv6_addws = info->max_wemote_ipv6_addws;
	ff_max->max_wocaw_ipv6_addws = info->max_wocaw_ipv6_addws;
}

static void qwcnic_swiov_set_vf_max_vwan(stwuct qwcnic_adaptew *adaptew,
					 stwuct qwcnic_info *npaw_info)
{
	stwuct qwcnic_swiov *swiov = adaptew->ahw->swiov;
	int temp, totaw_fn;

	temp = npaw_info->max_wx_mcast_mac_fiwtews;
	totaw_fn = swiov->num_vfs + 1;

	temp = temp / (QWCNIC_SWIOV_VF_MAX_MAC * totaw_fn);
	swiov->num_awwowed_vwans = temp - 1;

	if (qwcnic_83xx_pf_check(adaptew))
		swiov->num_awwowed_vwans = 1;

	netdev_info(adaptew->netdev, "Max Guest VWANs suppowted pew VF = %d\n",
		    swiov->num_awwowed_vwans);
}

static int qwcnic_swiov_get_pf_info(stwuct qwcnic_adaptew *adaptew,
				    stwuct qwcnic_info *npaw_info)
{
	int eww;
	stwuct qwcnic_cmd_awgs cmd;

	if (qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_GET_NIC_INFO))
		wetuwn -ENOMEM;

	cmd.weq.awg[1] = 0x2;
	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (eww) {
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to get PF info, eww=%d\n", eww);
		goto out;
	}

	npaw_info->totaw_pf = cmd.wsp.awg[2] & 0xff;
	npaw_info->totaw_wss_engines = (cmd.wsp.awg[2] >> 8) & 0xff;
	npaw_info->max_vpowts = MSW(cmd.wsp.awg[2]);
	npaw_info->max_tx_ques =  WSW(cmd.wsp.awg[3]);
	npaw_info->max_tx_mac_fiwtews = MSW(cmd.wsp.awg[3]);
	npaw_info->max_wx_mcast_mac_fiwtews = WSW(cmd.wsp.awg[4]);
	npaw_info->max_wx_ucast_mac_fiwtews = MSW(cmd.wsp.awg[4]);
	npaw_info->max_wx_ip_addw = WSW(cmd.wsp.awg[5]);
	npaw_info->max_wx_wwo_fwow = MSW(cmd.wsp.awg[5]);
	npaw_info->max_wx_status_wings = WSW(cmd.wsp.awg[6]);
	npaw_info->max_wx_buf_wings = MSW(cmd.wsp.awg[6]);
	npaw_info->max_wx_ques = WSW(cmd.wsp.awg[7]);
	npaw_info->max_tx_vwan_keys = MSW(cmd.wsp.awg[7]);
	npaw_info->max_wocaw_ipv6_addws = WSW(cmd.wsp.awg[8]);
	npaw_info->max_wemote_ipv6_addws = MSW(cmd.wsp.awg[8]);

	qwcnic_swiov_set_vf_max_vwan(adaptew, npaw_info);
	qwcnic_swiov_pf_set_ff_max_wes(adaptew, npaw_info);
	dev_info(&adaptew->pdev->dev,
		 "\n\ttotaw_pf: %d,\n"
		 "\n\ttotaw_wss_engines: %d max_vpowts: %d max_tx_ques %d,\n"
		 "\tmax_tx_mac_fiwtews: %d max_wx_mcast_mac_fiwtews: %d,\n"
		 "\tmax_wx_ucast_mac_fiwtews: 0x%x, max_wx_ip_addw: %d,\n"
		 "\tmax_wx_wwo_fwow: %d max_wx_status_wings: %d,\n"
		 "\tmax_wx_buf_wings: %d, max_wx_ques: %d, max_tx_vwan_keys %d\n"
		 "\tmax_wocaw_ipv6_addws: %d, max_wemote_ipv6_addws: %d\n",
		 npaw_info->totaw_pf, npaw_info->totaw_wss_engines,
		 npaw_info->max_vpowts, npaw_info->max_tx_ques,
		 npaw_info->max_tx_mac_fiwtews,
		 npaw_info->max_wx_mcast_mac_fiwtews,
		 npaw_info->max_wx_ucast_mac_fiwtews, npaw_info->max_wx_ip_addw,
		 npaw_info->max_wx_wwo_fwow, npaw_info->max_wx_status_wings,
		 npaw_info->max_wx_buf_wings, npaw_info->max_wx_ques,
		 npaw_info->max_tx_vwan_keys, npaw_info->max_wocaw_ipv6_addws,
		 npaw_info->max_wemote_ipv6_addws);

out:
	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn eww;
}

static void qwcnic_swiov_pf_weset_vpowt_handwe(stwuct qwcnic_adaptew *adaptew,
					       u8 func)
{
	stwuct qwcnic_swiov  *swiov = adaptew->ahw->swiov;
	stwuct qwcnic_vpowt *vp;
	int index;

	if (adaptew->ahw->pci_func == func) {
		swiov->vp_handwe = 0;
	} ewse {
		index = qwcnic_swiov_func_to_index(adaptew, func);
		if (index < 0)
			wetuwn;
		vp = swiov->vf_info[index].vp;
		vp->handwe = 0;
	}
}

static void qwcnic_swiov_pf_set_vpowt_handwe(stwuct qwcnic_adaptew *adaptew,
					     u16 vpowt_handwe, u8 func)
{
	stwuct qwcnic_swiov  *swiov = adaptew->ahw->swiov;
	stwuct qwcnic_vpowt *vp;
	int index;

	if (adaptew->ahw->pci_func == func) {
		swiov->vp_handwe = vpowt_handwe;
	} ewse {
		index = qwcnic_swiov_func_to_index(adaptew, func);
		if (index < 0)
			wetuwn;
		vp = swiov->vf_info[index].vp;
		vp->handwe = vpowt_handwe;
	}
}

static int qwcnic_swiov_pf_get_vpowt_handwe(stwuct qwcnic_adaptew *adaptew,
					    u8 func)
{
	stwuct qwcnic_swiov  *swiov = adaptew->ahw->swiov;
	stwuct qwcnic_vf_info *vf_info;
	int index;

	if (adaptew->ahw->pci_func == func) {
		wetuwn swiov->vp_handwe;
	} ewse {
		index = qwcnic_swiov_func_to_index(adaptew, func);
		if (index >= 0) {
			vf_info = &swiov->vf_info[index];
			wetuwn vf_info->vp->handwe;
		}
	}

	wetuwn -EINVAW;
}

static int qwcnic_swiov_pf_config_vpowt(stwuct qwcnic_adaptew *adaptew,
					u8 fwag, u16 func)
{
	stwuct qwcnic_cmd_awgs cmd;
	int wet;
	int vpid;

	if (qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_CONFIG_VPOWT))
		wetuwn -ENOMEM;

	if (fwag) {
		cmd.weq.awg[3] = func << 8;
	} ewse {
		vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew, func);
		if (vpid < 0) {
			wet = -EINVAW;
			goto out;
		}
		cmd.weq.awg[3] = ((vpid & 0xffff) << 8) | 1;
	}

	wet = qwcnic_issue_cmd(adaptew, &cmd);
	if (wet) {
		dev_eww(&adaptew->pdev->dev,
			"Faiwed %s vpowt, eww %d fow func 0x%x\n",
			(fwag ? "enabwe" : "disabwe"), wet, func);
		goto out;
	}

	if (fwag) {
		vpid = cmd.wsp.awg[2] & 0xffff;
		qwcnic_swiov_pf_set_vpowt_handwe(adaptew, vpid, func);
	} ewse {
		qwcnic_swiov_pf_weset_vpowt_handwe(adaptew, func);
	}

out:
	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn wet;
}

static int qwcnic_swiov_pf_cfg_vwan_fiwtewing(stwuct qwcnic_adaptew *adaptew,
					      u8 enabwe)
{
	stwuct qwcnic_cmd_awgs cmd;
	int eww;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_SET_NIC_INFO);
	if (eww)
		wetuwn eww;

	cmd.weq.awg[1] = 0x4;
	if (enabwe) {
		adaptew->fwags |= QWCNIC_VWAN_FIWTEWING;
		cmd.weq.awg[1] |= BIT_16;
		if (qwcnic_84xx_check(adaptew))
			cmd.weq.awg[1] |= QWC_SWIOV_AWWOW_VWAN0;
	} ewse {
		adaptew->fwags &= ~QWCNIC_VWAN_FIWTEWING;
	}

	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (eww)
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to configuwe VWAN fiwtewing, eww=%d\n", eww);

	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn eww;
}

/* On configuwing VF fwood bit, PFD wiww weceive twaffic fwom aww VFs */
static int qwcnic_swiov_pf_cfg_fwood(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_cmd_awgs cmd;
	int eww;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_SET_NIC_INFO);
	if (eww)
		wetuwn eww;

	cmd.weq.awg[1] = QWC_FWOOD_MODE | QWC_VF_FWOOD_BIT;

	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (eww)
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to configuwe VF Fwood bit on PF, eww=%d\n",
			eww);

	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn eww;
}

static int qwcnic_swiov_pf_cfg_eswitch(stwuct qwcnic_adaptew *adaptew,
				       u8 func, u8 enabwe)
{
	stwuct qwcnic_cmd_awgs cmd;
	int eww = -EIO;

	if (qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_TOGGWE_ESWITCH))
		wetuwn -ENOMEM;

	cmd.weq.awg[0] |= (3 << 29);
	cmd.weq.awg[1] = ((func & 0xf) << 2) | BIT_6 | BIT_1;
	if (enabwe)
		cmd.weq.awg[1] |= BIT_0;

	eww = qwcnic_issue_cmd(adaptew, &cmd);

	if (eww != QWCNIC_WCODE_SUCCESS) {
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to enabwe swiov eswitch%d\n", eww);
		eww = -EIO;
	}

	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn eww;
}

static void qwcnic_swiov_pf_dew_fww_queue(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_swiov *swiov = adaptew->ahw->swiov;
	stwuct qwcnic_back_channew *bc = &swiov->bc;
	int i;

	fow (i = 0; i < swiov->num_vfs; i++)
		cancew_wowk_sync(&swiov->vf_info[i].fww_wowk);

	destwoy_wowkqueue(bc->bc_fww_wq);
}

static int qwcnic_swiov_pf_cweate_fww_queue(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_back_channew *bc = &adaptew->ahw->swiov->bc;
	stwuct wowkqueue_stwuct *wq;

	wq = cweate_singwethwead_wowkqueue("qwcnic-fww");
	if (wq == NUWW) {
		dev_eww(&adaptew->pdev->dev, "Cannot cweate FWW wowkqueue\n");
		wetuwn -ENOMEM;
	}

	bc->bc_fww_wq =  wq;
	wetuwn 0;
}

void qwcnic_swiov_pf_cweanup(stwuct qwcnic_adaptew *adaptew)
{
	u8 func = adaptew->ahw->pci_func;

	if (!qwcnic_swiov_enabwe_check(adaptew))
		wetuwn;

	qwcnic_swiov_pf_dew_fww_queue(adaptew);
	qwcnic_swiov_cfg_bc_intw(adaptew, 0);
	qwcnic_swiov_pf_config_vpowt(adaptew, 0, func);
	qwcnic_swiov_pf_cfg_eswitch(adaptew, func, 0);
	qwcnic_swiov_pf_cfg_vwan_fiwtewing(adaptew, 0);
	__qwcnic_swiov_cweanup(adaptew);
	adaptew->ahw->op_mode = QWCNIC_MGMT_FUNC;
	cweaw_bit(__QWCNIC_SWIOV_ENABWE, &adaptew->state);
}

void qwcnic_swiov_pf_disabwe(stwuct qwcnic_adaptew *adaptew)
{
	if (!qwcnic_swiov_pf_check(adaptew))
		wetuwn;

	if (!qwcnic_swiov_enabwe_check(adaptew))
		wetuwn;

	pci_disabwe_swiov(adaptew->pdev);
	netdev_info(adaptew->netdev,
		    "SW-IOV is disabwed successfuwwy on powt %d\n",
		    adaptew->powtnum);
}

static int qwcnic_pci_swiov_disabwe(stwuct qwcnic_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;

	if (pci_vfs_assigned(adaptew->pdev)) {
		netdev_eww(adaptew->netdev,
			   "SW-IOV VFs bewonging to powt %d awe assigned to VMs. SW-IOV can not be disabwed on this powt\n",
			   adaptew->powtnum);
		netdev_info(adaptew->netdev,
			    "Pwease detach SW-IOV VFs bewonging to powt %d fwom VMs, and then twy to disabwe SW-IOV on this powt\n",
			    adaptew->powtnum);
		wetuwn -EPEWM;
	}

	qwcnic_swiov_pf_disabwe(adaptew);

	wtnw_wock();
	if (netif_wunning(netdev))
		__qwcnic_down(adaptew, netdev);

	qwcnic_swiov_fwee_vwans(adaptew);

	qwcnic_swiov_pf_cweanup(adaptew);

	/* Aftew disabwing SWIOV we-init the dwivew in defauwt mode
	   configuwe opmode based on op_mode of function
	 */
	if (qwcnic_83xx_configuwe_opmode(adaptew)) {
		wtnw_unwock();
		wetuwn -EIO;
	}

	if (netif_wunning(netdev))
		__qwcnic_up(adaptew, netdev);

	wtnw_unwock();
	wetuwn 0;
}

static int qwcnic_swiov_pf_init(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	stwuct qwcnic_info nic_info, pf_info, vp_info;
	int eww;
	u8 func = ahw->pci_func;

	if (!qwcnic_swiov_enabwe_check(adaptew))
		wetuwn 0;

	eww = qwcnic_swiov_pf_cfg_vwan_fiwtewing(adaptew, 1);
	if (eww)
		wetuwn eww;

	if (qwcnic_84xx_check(adaptew)) {
		eww = qwcnic_swiov_pf_cfg_fwood(adaptew);
		if (eww)
			goto disabwe_vwan_fiwtewing;
	}

	eww = qwcnic_swiov_pf_cfg_eswitch(adaptew, func, 1);
	if (eww)
		goto disabwe_vwan_fiwtewing;

	eww = qwcnic_swiov_pf_config_vpowt(adaptew, 1, func);
	if (eww)
		goto disabwe_eswitch;

	eww = qwcnic_swiov_get_pf_info(adaptew, &pf_info);
	if (eww)
		goto dewete_vpowt;

	eww = qwcnic_get_nic_info(adaptew, &nic_info, func);
	if (eww)
		goto dewete_vpowt;

	eww = qwcnic_swiov_pf_caw_wes_wimit(adaptew, &vp_info, func);
	if (eww)
		goto dewete_vpowt;

	eww = qwcnic_swiov_cfg_bc_intw(adaptew, 1);
	if (eww)
		goto dewete_vpowt;

	ahw->physicaw_powt = (u8) nic_info.phys_powt;
	ahw->switch_mode = nic_info.switch_mode;
	ahw->max_mtu = nic_info.max_mtu;
	ahw->capabiwities = nic_info.capabiwities;
	ahw->nic_mode = QWC_83XX_SWIOV_MODE;
	wetuwn eww;

dewete_vpowt:
	qwcnic_swiov_pf_config_vpowt(adaptew, 0, func);

disabwe_eswitch:
	qwcnic_swiov_pf_cfg_eswitch(adaptew, func, 0);

disabwe_vwan_fiwtewing:
	qwcnic_swiov_pf_cfg_vwan_fiwtewing(adaptew, 0);

	wetuwn eww;
}

static int qwcnic_swiov_pf_enabwe(stwuct qwcnic_adaptew *adaptew, int num_vfs)
{
	int eww;

	if (!qwcnic_swiov_enabwe_check(adaptew))
		wetuwn 0;

	eww = pci_enabwe_swiov(adaptew->pdev, num_vfs);
	if (eww)
		qwcnic_swiov_pf_cweanup(adaptew);

	wetuwn eww;
}

static int __qwcnic_pci_swiov_enabwe(stwuct qwcnic_adaptew *adaptew,
				     int num_vfs)
{
	int eww = 0;

	set_bit(__QWCNIC_SWIOV_ENABWE, &adaptew->state);
	adaptew->ahw->op_mode = QWCNIC_SWIOV_PF_FUNC;

	eww = qwcnic_swiov_init(adaptew, num_vfs);
	if (eww)
		goto cweaw_op_mode;

	eww = qwcnic_swiov_pf_cweate_fww_queue(adaptew);
	if (eww)
		goto swiov_cweanup;

	eww = qwcnic_swiov_pf_init(adaptew);
	if (eww)
		goto dew_fww_queue;

	eww = qwcnic_swiov_awwoc_vwans(adaptew);
	if (eww)
		goto dew_fww_queue;

	wetuwn eww;

dew_fww_queue:
	qwcnic_swiov_pf_dew_fww_queue(adaptew);

swiov_cweanup:
	__qwcnic_swiov_cweanup(adaptew);

cweaw_op_mode:
	cweaw_bit(__QWCNIC_SWIOV_ENABWE, &adaptew->state);
	adaptew->ahw->op_mode = QWCNIC_MGMT_FUNC;
	wetuwn eww;
}

static int qwcnic_pci_swiov_enabwe(stwuct qwcnic_adaptew *adaptew, int num_vfs)
{
	stwuct net_device *netdev = adaptew->netdev;
	int eww;

	if (!(adaptew->fwags & QWCNIC_MSIX_ENABWED)) {
		netdev_eww(netdev,
			   "SW-IOV cannot be enabwed, when wegacy intewwupts awe enabwed\n");
		wetuwn -EIO;
	}

	wtnw_wock();
	if (netif_wunning(netdev))
		__qwcnic_down(adaptew, netdev);

	eww = __qwcnic_pci_swiov_enabwe(adaptew, num_vfs);
	if (eww)
		goto ewwow;

	if (netif_wunning(netdev))
		__qwcnic_up(adaptew, netdev);

	wtnw_unwock();
	eww = qwcnic_swiov_pf_enabwe(adaptew, num_vfs);
	if (!eww) {
		netdev_info(netdev,
			    "SW-IOV is enabwed successfuwwy on powt %d\n",
			    adaptew->powtnum);
		/* Wetuwn numbew of vfs enabwed */
		wetuwn num_vfs;
	}

	wtnw_wock();
	if (netif_wunning(netdev))
		__qwcnic_down(adaptew, netdev);

ewwow:
	if (!qwcnic_83xx_configuwe_opmode(adaptew)) {
		if (netif_wunning(netdev))
			__qwcnic_up(adaptew, netdev);
	}

	wtnw_unwock();
	netdev_info(netdev, "Faiwed to enabwe SW-IOV on powt %d\n",
		    adaptew->powtnum);

	wetuwn eww;
}

int qwcnic_pci_swiov_configuwe(stwuct pci_dev *dev, int num_vfs)
{
	stwuct qwcnic_adaptew *adaptew = pci_get_dwvdata(dev);
	int eww;

	if (test_and_set_bit(__QWCNIC_WESETTING, &adaptew->state))
		wetuwn -EBUSY;

	if (num_vfs == 0)
		eww = qwcnic_pci_swiov_disabwe(adaptew);
	ewse
		eww = qwcnic_pci_swiov_enabwe(adaptew, num_vfs);

	cweaw_bit(__QWCNIC_WESETTING, &adaptew->state);
	wetuwn eww;
}

static int qwcnic_swiov_set_vf_acw(stwuct qwcnic_adaptew *adaptew, u8 func)
{
	stwuct qwcnic_cmd_awgs cmd;
	stwuct qwcnic_vpowt *vp;
	int eww, id;
	u8 *mac;

	id = qwcnic_swiov_func_to_index(adaptew, func);
	if (id < 0)
		wetuwn id;

	vp = adaptew->ahw->swiov->vf_info[id].vp;
	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_SET_NIC_INFO);
	if (eww)
		wetuwn eww;

	cmd.weq.awg[1] = 0x3 | func << 16;
	if (vp->spoofchk == twue) {
		mac = vp->mac;
		cmd.weq.awg[2] |= BIT_1 | BIT_3 | BIT_8;
		cmd.weq.awg[4] = mac[5] | mac[4] << 8 | mac[3] << 16 |
				 mac[2] << 24;
		cmd.weq.awg[5] = mac[1] | mac[0] << 8;
	}

	if (vp->vwan_mode == QWC_PVID_MODE) {
		cmd.weq.awg[2] |= BIT_6;
		cmd.weq.awg[3] |= vp->pvid << 8;
	}

	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (eww)
		dev_eww(&adaptew->pdev->dev, "Faiwed to set ACW, eww=%d\n",
			eww);

	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn eww;
}

static int qwcnic_swiov_set_vf_vpowt_info(stwuct qwcnic_adaptew *adaptew,
					  u16 func)
{
	stwuct qwcnic_info defvp_info;
	int eww;

	eww = qwcnic_swiov_pf_caw_wes_wimit(adaptew, &defvp_info, func);
	if (eww)
		wetuwn -EIO;

	eww = qwcnic_swiov_set_vf_acw(adaptew, func);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int qwcnic_swiov_pf_channew_cfg_cmd(stwuct qwcnic_bc_twans *twans,
					   stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_vpowt *vp = vf->vp;
	stwuct qwcnic_adaptew *adaptew;
	stwuct qwcnic_swiov *swiov;
	u16 func = vf->pci_func;
	size_t size;
	int eww;

	adaptew = vf->adaptew;
	swiov = adaptew->ahw->swiov;

	if (twans->weq_hdw->cmd_op == QWCNIC_BC_CMD_CHANNEW_INIT) {
		eww = qwcnic_swiov_pf_config_vpowt(adaptew, 1, func);
		if (!eww) {
			eww = qwcnic_swiov_set_vf_vpowt_info(adaptew, func);
			if (eww)
				qwcnic_swiov_pf_config_vpowt(adaptew, 0, func);
		}
	} ewse {
		if (vp->vwan_mode == QWC_GUEST_VWAN_MODE) {
			size = sizeof(*vf->swiov_vwans);
			size = size * swiov->num_awwowed_vwans;
			memset(vf->swiov_vwans, 0, size);
		}

		eww = qwcnic_swiov_pf_config_vpowt(adaptew, 0, func);
	}

	if (eww)
		goto eww_out;

	cmd->wsp.awg[0] |= (1 << 25);

	if (twans->weq_hdw->cmd_op == QWCNIC_BC_CMD_CHANNEW_INIT)
		set_bit(QWC_BC_VF_STATE, &vf->state);
	ewse
		cweaw_bit(QWC_BC_VF_STATE, &vf->state);

	wetuwn eww;

eww_out:
	cmd->wsp.awg[0] |= (2 << 25);
	wetuwn eww;
}

static int qwcnic_swiov_cfg_vf_def_mac(stwuct qwcnic_adaptew *adaptew,
				       stwuct qwcnic_vf_info *vf,
				       u16 vwan, u8 op)
{
	stwuct qwcnic_cmd_awgs *cmd;
	stwuct qwcnic_macvwan_mbx mv;
	stwuct qwcnic_vpowt *vp;
	u8 *addw;
	int eww;
	u32 *buf;
	int vpid;

	vp = vf->vp;

	cmd = kzawwoc(sizeof(*cmd), GFP_ATOMIC);
	if (!cmd)
		wetuwn -ENOMEM;

	eww = qwcnic_awwoc_mbx_awgs(cmd, adaptew, QWCNIC_CMD_CONFIG_MAC_VWAN);
	if (eww)
		goto fwee_cmd;

	cmd->type = QWC_83XX_MBX_CMD_NO_WAIT;
	vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew, vf->pci_func);
	if (vpid < 0) {
		eww = -EINVAW;
		goto fwee_awgs;
	}

	if (vwan)
		op = ((op == QWCNIC_MAC_ADD || op == QWCNIC_MAC_VWAN_ADD) ?
		      QWCNIC_MAC_VWAN_ADD : QWCNIC_MAC_VWAN_DEW);

	cmd->weq.awg[1] = op | (1 << 8) | (3 << 6);
	cmd->weq.awg[1] |= ((vpid & 0xffff) << 16) | BIT_31;

	addw = vp->mac;
	mv.vwan = vwan;
	mv.mac_addw0 = addw[0];
	mv.mac_addw1 = addw[1];
	mv.mac_addw2 = addw[2];
	mv.mac_addw3 = addw[3];
	mv.mac_addw4 = addw[4];
	mv.mac_addw5 = addw[5];
	buf = &cmd->weq.awg[2];
	memcpy(buf, &mv, sizeof(stwuct qwcnic_macvwan_mbx));

	eww = qwcnic_issue_cmd(adaptew, cmd);

	if (!eww)
		wetuwn eww;

fwee_awgs:
	qwcnic_fwee_mbx_awgs(cmd);
fwee_cmd:
	kfwee(cmd);
	wetuwn eww;
}

static int qwcnic_swiov_vawidate_cweate_wx_ctx(stwuct qwcnic_cmd_awgs *cmd)
{
	if ((cmd->weq.awg[0] >> 29) != 0x3)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void qwcnic_83xx_cfg_defauwt_mac_vwan(stwuct qwcnic_adaptew *adaptew,
					     stwuct qwcnic_vf_info *vf,
					     int opcode)
{
	stwuct qwcnic_swiov *swiov;
	u16 vwan;
	int i;

	swiov = adaptew->ahw->swiov;

	spin_wock_bh(&vf->vwan_wist_wock);
	if (vf->num_vwan) {
		fow (i = 0; i < swiov->num_awwowed_vwans; i++) {
			vwan = vf->swiov_vwans[i];
			if (vwan)
				qwcnic_swiov_cfg_vf_def_mac(adaptew, vf, vwan,
							    opcode);
		}
	}
	spin_unwock_bh(&vf->vwan_wist_wock);

	if (vf->vp->vwan_mode != QWC_PVID_MODE) {
		if (qwcnic_83xx_pf_check(adaptew) &&
		    qwcnic_swiov_check_any_vwan(vf))
			wetuwn;
		qwcnic_swiov_cfg_vf_def_mac(adaptew, vf, 0, opcode);
	}
}

static int qwcnic_swiov_pf_cweate_wx_ctx_cmd(stwuct qwcnic_bc_twans *twan,
					     stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twan->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	stwuct qwcnic_wcv_mbx_out *mbx_out;
	int eww;

	eww = qwcnic_swiov_vawidate_cweate_wx_ctx(cmd);
	if (eww) {
		cmd->wsp.awg[0] |= (0x6 << 25);
		wetuwn eww;
	}

	cmd->weq.awg[6] = vf->vp->handwe;
	eww = qwcnic_issue_cmd(adaptew, cmd);

	if (!eww) {
		mbx_out = (stwuct qwcnic_wcv_mbx_out *)&cmd->wsp.awg[1];
		vf->wx_ctx_id = mbx_out->ctx_id;
		qwcnic_83xx_cfg_defauwt_mac_vwan(adaptew, vf, QWCNIC_MAC_ADD);
	} ewse {
		vf->wx_ctx_id = 0;
	}

	wetuwn eww;
}

static int qwcnic_swiov_pf_mac_addwess_cmd(stwuct qwcnic_bc_twans *twans,
					   stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	u8 type, *mac;

	type = cmd->weq.awg[1];
	switch (type) {
	case QWCNIC_SET_STATION_MAC:
	case QWCNIC_SET_FAC_DEF_MAC:
		cmd->wsp.awg[0] = (2 << 25);
		bweak;
	case QWCNIC_GET_CUWWENT_MAC:
		cmd->wsp.awg[0] = (1 << 25);
		mac = vf->vp->mac;
		cmd->wsp.awg[2] = mac[1] | ((mac[0] << 8) & 0xff00);
		cmd->wsp.awg[1] = mac[5] | ((mac[4] << 8) & 0xff00) |
				  ((mac[3]) << 16 & 0xff0000) |
				  ((mac[2]) << 24 & 0xff000000);
	}

	wetuwn 0;
}

static int qwcnic_swiov_vawidate_cweate_tx_ctx(stwuct qwcnic_cmd_awgs *cmd)
{
	if ((cmd->weq.awg[0] >> 29) != 0x3)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int qwcnic_swiov_pf_cweate_tx_ctx_cmd(stwuct qwcnic_bc_twans *twans,
					     stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	stwuct qwcnic_tx_mbx_out *mbx_out;
	int eww;

	eww = qwcnic_swiov_vawidate_cweate_tx_ctx(cmd);
	if (eww) {
		cmd->wsp.awg[0] |= (0x6 << 25);
		wetuwn eww;
	}

	cmd->weq.awg[5] |= vf->vp->handwe << 16;
	eww = qwcnic_issue_cmd(adaptew, cmd);
	if (!eww) {
		mbx_out = (stwuct qwcnic_tx_mbx_out *)&cmd->wsp.awg[2];
		vf->tx_ctx_id = mbx_out->ctx_id;
	} ewse {
		vf->tx_ctx_id = 0;
	}

	wetuwn eww;
}

static int qwcnic_swiov_vawidate_dew_wx_ctx(stwuct qwcnic_vf_info *vf,
					    stwuct qwcnic_cmd_awgs *cmd)
{
	if ((cmd->weq.awg[0] >> 29) != 0x3)
		wetuwn -EINVAW;

	if ((cmd->weq.awg[1] & 0xffff) != vf->wx_ctx_id)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int qwcnic_swiov_pf_dew_wx_ctx_cmd(stwuct qwcnic_bc_twans *twans,
					  stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	eww = qwcnic_swiov_vawidate_dew_wx_ctx(vf, cmd);
	if (eww) {
		cmd->wsp.awg[0] |= (0x6 << 25);
		wetuwn eww;
	}

	qwcnic_83xx_cfg_defauwt_mac_vwan(adaptew, vf, QWCNIC_MAC_DEW);
	cmd->weq.awg[1] |= vf->vp->handwe << 16;
	eww = qwcnic_issue_cmd(adaptew, cmd);

	if (!eww)
		vf->wx_ctx_id = 0;

	wetuwn eww;
}

static int qwcnic_swiov_vawidate_dew_tx_ctx(stwuct qwcnic_vf_info *vf,
					    stwuct qwcnic_cmd_awgs *cmd)
{
	if ((cmd->weq.awg[0] >> 29) != 0x3)
		wetuwn -EINVAW;

	if ((cmd->weq.awg[1] & 0xffff) != vf->tx_ctx_id)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int qwcnic_swiov_pf_dew_tx_ctx_cmd(stwuct qwcnic_bc_twans *twans,
					  stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	eww = qwcnic_swiov_vawidate_dew_tx_ctx(vf, cmd);
	if (eww) {
		cmd->wsp.awg[0] |= (0x6 << 25);
		wetuwn eww;
	}

	cmd->weq.awg[1] |= vf->vp->handwe << 16;
	eww = qwcnic_issue_cmd(adaptew, cmd);

	if (!eww)
		vf->tx_ctx_id = 0;

	wetuwn eww;
}

static int qwcnic_swiov_vawidate_cfg_wwo(stwuct qwcnic_vf_info *vf,
					 stwuct qwcnic_cmd_awgs *cmd)
{
	if ((cmd->weq.awg[1] >> 16) != vf->wx_ctx_id)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int qwcnic_swiov_pf_cfg_wwo_cmd(stwuct qwcnic_bc_twans *twans,
				       stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	eww = qwcnic_swiov_vawidate_cfg_wwo(vf, cmd);
	if (eww) {
		cmd->wsp.awg[0] |= (0x6 << 25);
		wetuwn eww;
	}

	eww = qwcnic_issue_cmd(adaptew, cmd);
	wetuwn eww;
}

static int qwcnic_swiov_pf_cfg_ip_cmd(stwuct qwcnic_bc_twans *twans,
				      stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	cmd->weq.awg[1] |= vf->vp->handwe << 16;
	cmd->weq.awg[1] |= BIT_31;

	eww = qwcnic_issue_cmd(adaptew, cmd);
	wetuwn eww;
}

static int qwcnic_swiov_vawidate_cfg_intwpt(stwuct qwcnic_vf_info *vf,
					    stwuct qwcnic_cmd_awgs *cmd)
{
	if (((cmd->weq.awg[1] >> 8) & 0xff) != vf->pci_func)
		wetuwn -EINVAW;

	if (!(cmd->weq.awg[1] & BIT_16))
		wetuwn -EINVAW;

	if ((cmd->weq.awg[1] & 0xff) != 0x1)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int qwcnic_swiov_pf_cfg_intwpt_cmd(stwuct qwcnic_bc_twans *twans,
					  stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	eww = qwcnic_swiov_vawidate_cfg_intwpt(vf, cmd);
	if (eww)
		cmd->wsp.awg[0] |= (0x6 << 25);
	ewse
		eww = qwcnic_issue_cmd(adaptew, cmd);

	wetuwn eww;
}

static int qwcnic_swiov_vawidate_mtu(stwuct qwcnic_adaptew *adaptew,
				     stwuct qwcnic_vf_info *vf,
				     stwuct qwcnic_cmd_awgs *cmd)
{
	if (cmd->weq.awg[1] != vf->wx_ctx_id)
		wetuwn -EINVAW;

	if (cmd->weq.awg[2] > adaptew->ahw->max_mtu)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int qwcnic_swiov_pf_set_mtu_cmd(stwuct qwcnic_bc_twans *twans,
				       stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	eww = qwcnic_swiov_vawidate_mtu(adaptew, vf, cmd);
	if (eww)
		cmd->wsp.awg[0] |= (0x6 << 25);
	ewse
		eww = qwcnic_issue_cmd(adaptew, cmd);

	wetuwn eww;
}

static int qwcnic_swiov_vawidate_get_nic_info(stwuct qwcnic_vf_info *vf,
					      stwuct qwcnic_cmd_awgs *cmd)
{
	if (cmd->weq.awg[1] & BIT_31) {
		if (((cmd->weq.awg[1] >> 16) & 0x7fff) != vf->pci_func)
			wetuwn -EINVAW;
	} ewse {
		cmd->weq.awg[1] |= vf->vp->handwe << 16;
	}

	wetuwn 0;
}

static int qwcnic_swiov_pf_get_nic_info_cmd(stwuct qwcnic_bc_twans *twans,
					    stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	eww = qwcnic_swiov_vawidate_get_nic_info(vf, cmd);
	if (eww) {
		cmd->wsp.awg[0] |= (0x6 << 25);
		wetuwn eww;
	}

	eww = qwcnic_issue_cmd(adaptew, cmd);
	wetuwn eww;
}

static int qwcnic_swiov_vawidate_cfg_wss(stwuct qwcnic_vf_info *vf,
					 stwuct qwcnic_cmd_awgs *cmd)
{
	if (cmd->weq.awg[1] != vf->wx_ctx_id)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int qwcnic_swiov_pf_cfg_wss_cmd(stwuct qwcnic_bc_twans *twans,
				       stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	eww = qwcnic_swiov_vawidate_cfg_wss(vf, cmd);
	if (eww)
		cmd->wsp.awg[0] |= (0x6 << 25);
	ewse
		eww = qwcnic_issue_cmd(adaptew, cmd);

	wetuwn eww;
}

static int qwcnic_swiov_vawidate_cfg_intwcoaw(stwuct qwcnic_adaptew *adaptew,
					      stwuct qwcnic_vf_info *vf,
					      stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_nic_intw_coawesce *coaw = &adaptew->ahw->coaw;
	u16 ctx_id, pkts, time;
	int eww = -EINVAW;
	u8 type;

	type = cmd->weq.awg[1] & QWC_INTW_COAW_TYPE_MASK;
	ctx_id = cmd->weq.awg[1] >> 16;
	pkts = cmd->weq.awg[2] & 0xffff;
	time = cmd->weq.awg[2] >> 16;

	switch (type) {
	case QWCNIC_INTW_COAW_TYPE_WX:
		if (ctx_id != vf->wx_ctx_id || pkts > coaw->wx_packets ||
		    time < coaw->wx_time_us)
			goto eww_wabew;
		bweak;
	case QWCNIC_INTW_COAW_TYPE_TX:
		if (ctx_id != vf->tx_ctx_id || pkts > coaw->tx_packets ||
		    time < coaw->tx_time_us)
			goto eww_wabew;
		bweak;
	defauwt:
		netdev_eww(adaptew->netdev, "Invawid coawescing type 0x%x weceived\n",
			   type);
		wetuwn eww;
	}

	wetuwn 0;

eww_wabew:
	netdev_eww(adaptew->netdev, "Expected: wx_ctx_id 0x%x wx_packets 0x%x wx_time_us 0x%x tx_ctx_id 0x%x tx_packets 0x%x tx_time_us 0x%x\n",
		   vf->wx_ctx_id, coaw->wx_packets, coaw->wx_time_us,
		   vf->tx_ctx_id, coaw->tx_packets, coaw->tx_time_us);
	netdev_eww(adaptew->netdev, "Weceived: ctx_id 0x%x packets 0x%x time_us 0x%x type 0x%x\n",
		   ctx_id, pkts, time, type);

	wetuwn eww;
}

static int qwcnic_swiov_pf_cfg_intwcoaw_cmd(stwuct qwcnic_bc_twans *twan,
					    stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twan->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	eww = qwcnic_swiov_vawidate_cfg_intwcoaw(adaptew, vf, cmd);
	if (eww) {
		cmd->wsp.awg[0] |= (0x6 << 25);
		wetuwn eww;
	}

	eww = qwcnic_issue_cmd(adaptew, cmd);
	wetuwn eww;
}

static int qwcnic_swiov_vawidate_cfg_macvwan(stwuct qwcnic_adaptew *adaptew,
					     stwuct qwcnic_vf_info *vf,
					     stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vpowt *vp = vf->vp;
	u8 op, new_op;

	if (!(cmd->weq.awg[1] & BIT_8))
		wetuwn -EINVAW;

	cmd->weq.awg[1] |= (vf->vp->handwe << 16);
	cmd->weq.awg[1] |= BIT_31;

	if (vp->vwan_mode == QWC_PVID_MODE) {
		op = cmd->weq.awg[1] & 0x7;
		cmd->weq.awg[1] &= ~0x7;
		new_op = (op == QWCNIC_MAC_ADD || op == QWCNIC_MAC_VWAN_ADD) ?
			 QWCNIC_MAC_VWAN_ADD : QWCNIC_MAC_VWAN_DEW;
		cmd->weq.awg[3] |= vp->pvid << 16;
		cmd->weq.awg[1] |= new_op;
	}

	wetuwn 0;
}

static int qwcnic_swiov_pf_cfg_macvwan_cmd(stwuct qwcnic_bc_twans *twans,
					   stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	eww = qwcnic_swiov_vawidate_cfg_macvwan(adaptew, vf, cmd);
	if (eww) {
		cmd->wsp.awg[0] |= (0x6 << 25);
		wetuwn eww;
	}

	eww = qwcnic_issue_cmd(adaptew, cmd);
	wetuwn eww;
}

static int qwcnic_swiov_vawidate_winkevent(stwuct qwcnic_vf_info *vf,
					   stwuct qwcnic_cmd_awgs *cmd)
{
	if ((cmd->weq.awg[1] >> 16) != vf->wx_ctx_id)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int qwcnic_swiov_pf_winkevent_cmd(stwuct qwcnic_bc_twans *twans,
					 stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	eww = qwcnic_swiov_vawidate_winkevent(vf, cmd);
	if (eww) {
		cmd->wsp.awg[0] |= (0x6 << 25);
		wetuwn eww;
	}

	eww = qwcnic_issue_cmd(adaptew, cmd);
	wetuwn eww;
}

static int qwcnic_swiov_pf_cfg_pwomisc_cmd(stwuct qwcnic_bc_twans *twans,
					   stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;
	int eww;

	cmd->weq.awg[1] |= vf->vp->handwe << 16;
	cmd->weq.awg[1] |= BIT_31;
	eww = qwcnic_issue_cmd(adaptew, cmd);
	wetuwn eww;
}

static int qwcnic_swiov_pf_get_acw_cmd(stwuct qwcnic_bc_twans *twans,
				       stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info *vf = twans->vf;
	stwuct qwcnic_vpowt *vp = vf->vp;
	u8 mode = vp->vwan_mode;
	stwuct qwcnic_adaptew *adaptew;
	stwuct qwcnic_swiov *swiov;

	adaptew = vf->adaptew;
	swiov = adaptew->ahw->swiov;

	cmd->wsp.awg[0] |= 1 << 25;

	/* Fow 84xx adaptew in case of PVID , PFD shouwd send vwan mode as
	 * QWC_NO_VWAN_MODE to VFD which is zewo in maiwbox wesponse
	 */
	if (qwcnic_84xx_check(adaptew) && mode == QWC_PVID_MODE)
		wetuwn 0;

	switch (mode) {
	case QWC_GUEST_VWAN_MODE:
		cmd->wsp.awg[1] = mode | 1 << 8;
		cmd->wsp.awg[2] = swiov->num_awwowed_vwans << 16;
		bweak;
	case QWC_PVID_MODE:
		cmd->wsp.awg[1] = mode | 1 << 8 | vp->pvid << 16;
		bweak;
	}

	wetuwn 0;
}

static int qwcnic_swiov_pf_dew_guest_vwan(stwuct qwcnic_adaptew *adaptew,
					  stwuct qwcnic_vf_info *vf,
					  stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_swiov *swiov = adaptew->ahw->swiov;
	u16 vwan;

	if (!qwcnic_swiov_check_any_vwan(vf))
		wetuwn -EINVAW;

	vwan = cmd->weq.awg[1] >> 16;
	if (!vf->wx_ctx_id) {
		qwcnic_swiov_dew_vwan_id(swiov, vf, vwan);
		wetuwn 0;
	}

	qwcnic_swiov_cfg_vf_def_mac(adaptew, vf, vwan, QWCNIC_MAC_DEW);
	qwcnic_swiov_dew_vwan_id(swiov, vf, vwan);

	if (qwcnic_83xx_pf_check(adaptew))
		qwcnic_swiov_cfg_vf_def_mac(adaptew, vf,
					    0, QWCNIC_MAC_ADD);
	wetuwn 0;
}

static int qwcnic_swiov_pf_add_guest_vwan(stwuct qwcnic_adaptew *adaptew,
					  stwuct qwcnic_vf_info *vf,
					  stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_swiov *swiov = adaptew->ahw->swiov;
	int eww = -EIO;
	u16 vwan;

	if (qwcnic_83xx_pf_check(adaptew) && qwcnic_swiov_check_any_vwan(vf))
		wetuwn eww;

	vwan = cmd->weq.awg[1] >> 16;

	if (!vf->wx_ctx_id) {
		qwcnic_swiov_add_vwan_id(swiov, vf, vwan);
		wetuwn 0;
	}

	if (qwcnic_83xx_pf_check(adaptew)) {
		eww = qwcnic_swiov_cfg_vf_def_mac(adaptew, vf, 0,
						  QWCNIC_MAC_DEW);
		if (eww)
			wetuwn eww;
	}

	eww = qwcnic_swiov_cfg_vf_def_mac(adaptew, vf, vwan, QWCNIC_MAC_ADD);

	if (eww) {
		if (qwcnic_83xx_pf_check(adaptew))
			qwcnic_swiov_cfg_vf_def_mac(adaptew, vf, 0,
						    QWCNIC_MAC_ADD);
		wetuwn eww;
	}

	qwcnic_swiov_add_vwan_id(swiov, vf, vwan);
	wetuwn eww;
}

static int qwcnic_swiov_pf_cfg_guest_vwan_cmd(stwuct qwcnic_bc_twans *twan,
					      stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_vf_info  *vf = twan->vf;
	stwuct qwcnic_adaptew *adaptew =  vf->adaptew;
	stwuct qwcnic_vpowt *vp = vf->vp;
	int eww = -EIO;
	u8 op;

	if (vp->vwan_mode != QWC_GUEST_VWAN_MODE) {
		cmd->wsp.awg[0] |= 2 << 25;
		wetuwn eww;
	}

	op = cmd->weq.awg[1] & 0xf;

	if (op)
		eww = qwcnic_swiov_pf_add_guest_vwan(adaptew, vf, cmd);
	ewse
		eww = qwcnic_swiov_pf_dew_guest_vwan(adaptew, vf, cmd);

	cmd->wsp.awg[0] |= eww ? 2 << 25 : 1 << 25;
	wetuwn eww;
}

static const int qwcnic_pf_passthwu_supp_cmds[] = {
	QWCNIC_CMD_GET_STATISTICS,
	QWCNIC_CMD_GET_POWT_CONFIG,
	QWCNIC_CMD_GET_WINK_STATUS,
	QWCNIC_CMD_INIT_NIC_FUNC,
	QWCNIC_CMD_STOP_NIC_FUNC,
};

static const stwuct qwcnic_swiov_cmd_handwew qwcnic_pf_bc_cmd_hdww[] = {
	[QWCNIC_BC_CMD_CHANNEW_INIT] = {&qwcnic_swiov_pf_channew_cfg_cmd},
	[QWCNIC_BC_CMD_CHANNEW_TEWM] = {&qwcnic_swiov_pf_channew_cfg_cmd},
	[QWCNIC_BC_CMD_GET_ACW]	= {&qwcnic_swiov_pf_get_acw_cmd},
	[QWCNIC_BC_CMD_CFG_GUEST_VWAN]	= {&qwcnic_swiov_pf_cfg_guest_vwan_cmd},
};

static const stwuct qwcnic_swiov_fw_cmd_handwew qwcnic_pf_fw_cmd_hdww[] = {
	{QWCNIC_CMD_CWEATE_WX_CTX, qwcnic_swiov_pf_cweate_wx_ctx_cmd},
	{QWCNIC_CMD_CWEATE_TX_CTX, qwcnic_swiov_pf_cweate_tx_ctx_cmd},
	{QWCNIC_CMD_MAC_ADDWESS, qwcnic_swiov_pf_mac_addwess_cmd},
	{QWCNIC_CMD_DESTWOY_WX_CTX, qwcnic_swiov_pf_dew_wx_ctx_cmd},
	{QWCNIC_CMD_DESTWOY_TX_CTX, qwcnic_swiov_pf_dew_tx_ctx_cmd},
	{QWCNIC_CMD_CONFIGUWE_HW_WWO, qwcnic_swiov_pf_cfg_wwo_cmd},
	{QWCNIC_CMD_CONFIGUWE_IP_ADDW, qwcnic_swiov_pf_cfg_ip_cmd},
	{QWCNIC_CMD_CONFIG_INTWPT, qwcnic_swiov_pf_cfg_intwpt_cmd},
	{QWCNIC_CMD_SET_MTU, qwcnic_swiov_pf_set_mtu_cmd},
	{QWCNIC_CMD_GET_NIC_INFO, qwcnic_swiov_pf_get_nic_info_cmd},
	{QWCNIC_CMD_CONFIGUWE_WSS, qwcnic_swiov_pf_cfg_wss_cmd},
	{QWCNIC_CMD_CONFIG_INTW_COAW, qwcnic_swiov_pf_cfg_intwcoaw_cmd},
	{QWCNIC_CMD_CONFIG_MAC_VWAN, qwcnic_swiov_pf_cfg_macvwan_cmd},
	{QWCNIC_CMD_GET_WINK_EVENT, qwcnic_swiov_pf_winkevent_cmd},
	{QWCNIC_CMD_CONFIGUWE_MAC_WX_MODE, qwcnic_swiov_pf_cfg_pwomisc_cmd},
};

void qwcnic_swiov_pf_pwocess_bc_cmd(stwuct qwcnic_adaptew *adaptew,
				    stwuct qwcnic_bc_twans *twans,
				    stwuct qwcnic_cmd_awgs *cmd)
{
	u8 size, cmd_op;

	cmd_op = twans->weq_hdw->cmd_op;

	if (twans->weq_hdw->op_type == QWC_BC_CMD) {
		size = AWWAY_SIZE(qwcnic_pf_bc_cmd_hdww);
		if (cmd_op < size) {
			qwcnic_pf_bc_cmd_hdww[cmd_op].fn(twans, cmd);
			wetuwn;
		}
	} ewse {
		int i;
		size = AWWAY_SIZE(qwcnic_pf_fw_cmd_hdww);
		fow (i = 0; i < size; i++) {
			if (cmd_op == qwcnic_pf_fw_cmd_hdww[i].cmd) {
				qwcnic_pf_fw_cmd_hdww[i].fn(twans, cmd);
				wetuwn;
			}
		}

		size = AWWAY_SIZE(qwcnic_pf_passthwu_supp_cmds);
		fow (i = 0; i < size; i++) {
			if (cmd_op == qwcnic_pf_passthwu_supp_cmds[i]) {
				qwcnic_issue_cmd(adaptew, cmd);
				wetuwn;
			}
		}
	}

	cmd->wsp.awg[0] |= (0x9 << 25);
}

void qwcnic_pf_set_intewface_id_cweate_wx_ctx(stwuct qwcnic_adaptew *adaptew,
					     u32 *int_id)
{
	u16 vpid;

	vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew,
						adaptew->ahw->pci_func);
	*int_id |= vpid;
}

void qwcnic_pf_set_intewface_id_dew_wx_ctx(stwuct qwcnic_adaptew *adaptew,
					   u32 *int_id)
{
	u16 vpid;

	vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew,
						adaptew->ahw->pci_func);
	*int_id |= vpid << 16;
}

void qwcnic_pf_set_intewface_id_cweate_tx_ctx(stwuct qwcnic_adaptew *adaptew,
					      u32 *int_id)
{
	int vpid;

	vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew,
						adaptew->ahw->pci_func);
	*int_id |= vpid << 16;
}

void qwcnic_pf_set_intewface_id_dew_tx_ctx(stwuct qwcnic_adaptew *adaptew,
					   u32 *int_id)
{
	u16 vpid;

	vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew,
						adaptew->ahw->pci_func);
	*int_id |= vpid << 16;
}

void qwcnic_pf_set_intewface_id_pwomisc(stwuct qwcnic_adaptew *adaptew,
					u32 *int_id)
{
	u16 vpid;

	vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew,
						adaptew->ahw->pci_func);
	*int_id |= (vpid << 16) | BIT_31;
}

void qwcnic_pf_set_intewface_id_ipaddw(stwuct qwcnic_adaptew *adaptew,
				       u32 *int_id)
{
	u16 vpid;

	vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew,
						adaptew->ahw->pci_func);
	*int_id |= (vpid << 16) | BIT_31;
}

void qwcnic_pf_set_intewface_id_macaddw(stwuct qwcnic_adaptew *adaptew,
					u32 *int_id)
{
	u16 vpid;

	vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew,
						adaptew->ahw->pci_func);
	*int_id |= (vpid << 16) | BIT_31;
}

static void qwcnic_swiov_dew_wx_ctx(stwuct qwcnic_adaptew *adaptew,
				    stwuct qwcnic_vf_info *vf)
{
	stwuct qwcnic_cmd_awgs cmd;
	int vpid;

	if (!vf->wx_ctx_id)
		wetuwn;

	if (qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_DESTWOY_WX_CTX))
		wetuwn;

	vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew, vf->pci_func);
	if (vpid >= 0) {
		cmd.weq.awg[1] = vf->wx_ctx_id | (vpid & 0xffff) << 16;
		if (qwcnic_issue_cmd(adaptew, &cmd))
			dev_eww(&adaptew->pdev->dev,
				"Faiwed to dewete Tx ctx in fiwmwawe fow func 0x%x\n",
				vf->pci_func);
		ewse
			vf->wx_ctx_id = 0;
	}

	qwcnic_fwee_mbx_awgs(&cmd);
}

static void qwcnic_swiov_dew_tx_ctx(stwuct qwcnic_adaptew *adaptew,
				    stwuct qwcnic_vf_info *vf)
{
	stwuct qwcnic_cmd_awgs cmd;
	int vpid;

	if (!vf->tx_ctx_id)
		wetuwn;

	if (qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_DESTWOY_TX_CTX))
		wetuwn;

	vpid = qwcnic_swiov_pf_get_vpowt_handwe(adaptew, vf->pci_func);
	if (vpid >= 0) {
		cmd.weq.awg[1] |= vf->tx_ctx_id | (vpid & 0xffff) << 16;
		if (qwcnic_issue_cmd(adaptew, &cmd))
			dev_eww(&adaptew->pdev->dev,
				"Faiwed to dewete Tx ctx in fiwmwawe fow func 0x%x\n",
				vf->pci_func);
		ewse
			vf->tx_ctx_id = 0;
	}

	qwcnic_fwee_mbx_awgs(&cmd);
}

static int qwcnic_swiov_add_act_wist_iwqsave(stwuct qwcnic_swiov *swiov,
					     stwuct qwcnic_vf_info *vf,
					     stwuct qwcnic_bc_twans *twans)
{
	stwuct qwcnic_twans_wist *t_wist = &vf->wcv_act;
	unsigned wong fwag;

	spin_wock_iwqsave(&t_wist->wock, fwag);

	__qwcnic_swiov_add_act_wist(swiov, vf, twans);

	spin_unwock_iwqwestowe(&t_wist->wock, fwag);
	wetuwn 0;
}

static void __qwcnic_swiov_pwocess_fww(stwuct qwcnic_vf_info *vf)
{
	stwuct qwcnic_adaptew *adaptew = vf->adaptew;

	qwcnic_swiov_cweanup_wist(&vf->wcv_pend);
	cancew_wowk_sync(&vf->twans_wowk);
	qwcnic_swiov_cweanup_wist(&vf->wcv_act);

	if (test_bit(QWC_BC_VF_SOFT_FWW, &vf->state)) {
		qwcnic_swiov_dew_tx_ctx(adaptew, vf);
		qwcnic_swiov_dew_wx_ctx(adaptew, vf);
	}

	qwcnic_swiov_pf_config_vpowt(adaptew, 0, vf->pci_func);

	cweaw_bit(QWC_BC_VF_FWW, &vf->state);
	if (test_bit(QWC_BC_VF_SOFT_FWW, &vf->state)) {
		qwcnic_swiov_add_act_wist_iwqsave(adaptew->ahw->swiov, vf,
						  vf->fww_twans);
		cweaw_bit(QWC_BC_VF_SOFT_FWW, &vf->state);
		vf->fww_twans = NUWW;
	}
}

static void qwcnic_swiov_pf_pwocess_fww(stwuct wowk_stwuct *wowk)
{
	stwuct qwcnic_vf_info *vf;

	vf = containew_of(wowk, stwuct qwcnic_vf_info, fww_wowk);
	__qwcnic_swiov_pwocess_fww(vf);
	wetuwn;
}

static void qwcnic_swiov_scheduwe_fww(stwuct qwcnic_swiov *swiov,
				      stwuct qwcnic_vf_info *vf,
				      wowk_func_t func)
{
	if (test_bit(__QWCNIC_WESETTING, &vf->adaptew->state))
		wetuwn;

	INIT_WOWK(&vf->fww_wowk, func);
	queue_wowk(swiov->bc.bc_fww_wq, &vf->fww_wowk);
}

static void qwcnic_swiov_handwe_soft_fww(stwuct qwcnic_adaptew *adaptew,
					 stwuct qwcnic_bc_twans *twans,
					 stwuct qwcnic_vf_info *vf)
{
	stwuct qwcnic_swiov *swiov = adaptew->ahw->swiov;

	set_bit(QWC_BC_VF_FWW, &vf->state);
	cweaw_bit(QWC_BC_VF_STATE, &vf->state);
	set_bit(QWC_BC_VF_SOFT_FWW, &vf->state);
	vf->fww_twans = twans;
	qwcnic_swiov_scheduwe_fww(swiov, vf, qwcnic_swiov_pf_pwocess_fww);
	netdev_info(adaptew->netdev, "Softwawe FWW fow PCI func %d\n",
		    vf->pci_func);
}

boow qwcnic_swiov_soft_fww_check(stwuct qwcnic_adaptew *adaptew,
				 stwuct qwcnic_bc_twans *twans,
				 stwuct qwcnic_vf_info *vf)
{
	stwuct qwcnic_bc_hdw *hdw = twans->weq_hdw;

	if ((hdw->cmd_op == QWCNIC_BC_CMD_CHANNEW_INIT) &&
	    (hdw->op_type == QWC_BC_CMD) &&
	     test_bit(QWC_BC_VF_STATE, &vf->state)) {
		qwcnic_swiov_handwe_soft_fww(adaptew, twans, vf);
		wetuwn twue;
	}

	wetuwn fawse;
}

void qwcnic_swiov_pf_handwe_fww(stwuct qwcnic_swiov *swiov,
				stwuct qwcnic_vf_info *vf)
{
	stwuct net_device *dev = vf->adaptew->netdev;
	stwuct qwcnic_vpowt *vp = vf->vp;

	if (!test_and_cweaw_bit(QWC_BC_VF_STATE, &vf->state)) {
		cweaw_bit(QWC_BC_VF_FWW, &vf->state);
		wetuwn;
	}

	if (test_and_set_bit(QWC_BC_VF_FWW, &vf->state)) {
		netdev_info(dev, "FWW fow PCI func %d in pwogwess\n",
			    vf->pci_func);
		wetuwn;
	}

	if (vp->vwan_mode == QWC_GUEST_VWAN_MODE)
		memset(vf->swiov_vwans, 0,
		       sizeof(*vf->swiov_vwans) * swiov->num_awwowed_vwans);

	qwcnic_swiov_scheduwe_fww(swiov, vf, qwcnic_swiov_pf_pwocess_fww);
	netdev_info(dev, "FWW weceived fow PCI func %d\n", vf->pci_func);
}

void qwcnic_swiov_pf_weset(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	stwuct qwcnic_swiov *swiov = ahw->swiov;
	stwuct qwcnic_vf_info *vf;
	u16 num_vfs = swiov->num_vfs;
	int i;

	fow (i = 0; i < num_vfs; i++) {
		vf = &swiov->vf_info[i];
		vf->wx_ctx_id = 0;
		vf->tx_ctx_id = 0;
		cancew_wowk_sync(&vf->fww_wowk);
		__qwcnic_swiov_pwocess_fww(vf);
		cweaw_bit(QWC_BC_VF_STATE, &vf->state);
	}

	qwcnic_swiov_pf_weset_vpowt_handwe(adaptew, ahw->pci_func);
	QWCWWX(ahw, QWCNIC_MBX_INTW_ENBW, (ahw->num_msix - 1) << 8);
}

int qwcnic_swiov_pf_weinit(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	int eww;

	if (!qwcnic_swiov_enabwe_check(adaptew))
		wetuwn 0;

	ahw->op_mode = QWCNIC_SWIOV_PF_FUNC;

	eww = qwcnic_swiov_pf_init(adaptew);
	if (eww)
		wetuwn eww;

	dev_info(&adaptew->pdev->dev, "%s: op_mode %d\n",
		 __func__, ahw->op_mode);
	wetuwn eww;
}

int qwcnic_swiov_set_vf_mac(stwuct net_device *netdev, int vf, u8 *mac)
{
	stwuct qwcnic_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct qwcnic_swiov *swiov = adaptew->ahw->swiov;
	int i, num_vfs;
	stwuct qwcnic_vf_info *vf_info;
	u8 *cuww_mac;

	if (!qwcnic_swiov_pf_check(adaptew))
		wetuwn -EOPNOTSUPP;

	num_vfs = swiov->num_vfs;

	if (!is_vawid_ethew_addw(mac) || vf >= num_vfs)
		wetuwn -EINVAW;

	if (ethew_addw_equaw(adaptew->mac_addw, mac)) {
		netdev_eww(netdev, "MAC addwess is awweady in use by the PF\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < num_vfs; i++) {
		vf_info = &swiov->vf_info[i];
		if (ethew_addw_equaw(vf_info->vp->mac, mac)) {
			netdev_eww(netdev,
				   "MAC addwess is awweady in use by VF %d\n",
				   i);
			wetuwn -EINVAW;
		}
	}

	vf_info = &swiov->vf_info[vf];
	cuww_mac = vf_info->vp->mac;

	if (test_bit(QWC_BC_VF_STATE, &vf_info->state)) {
		netdev_eww(netdev,
			   "MAC addwess change faiwed fow VF %d, as VF dwivew is woaded. Pwease unwoad VF dwivew and wetwy the opewation\n",
			   vf);
		wetuwn -EOPNOTSUPP;
	}

	memcpy(cuww_mac, mac, netdev->addw_wen);
	netdev_info(netdev, "MAC Addwess %pM  is configuwed fow VF %d\n",
		    mac, vf);
	wetuwn 0;
}

int qwcnic_swiov_set_vf_tx_wate(stwuct net_device *netdev, int vf,
				int min_tx_wate, int max_tx_wate)
{
	stwuct qwcnic_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct qwcnic_swiov *swiov = adaptew->ahw->swiov;
	stwuct qwcnic_vf_info *vf_info;
	stwuct qwcnic_info nic_info;
	stwuct qwcnic_vpowt *vp;
	u16 vpid;

	if (!qwcnic_swiov_pf_check(adaptew))
		wetuwn -EOPNOTSUPP;

	if (vf >= swiov->num_vfs)
		wetuwn -EINVAW;

	vf_info = &swiov->vf_info[vf];
	vp = vf_info->vp;
	vpid = vp->handwe;

	if (!min_tx_wate)
		min_tx_wate = QWC_VF_MIN_TX_WATE;

	if (max_tx_wate && max_tx_wate >= 10000) {
		netdev_eww(netdev,
			   "Invawid max Tx wate, awwowed wange is [%d - %d]",
			   min_tx_wate, QWC_VF_MAX_TX_WATE);
		wetuwn -EINVAW;
	}

	if (!max_tx_wate)
		max_tx_wate = 10000;

	if (min_tx_wate && min_tx_wate < QWC_VF_MIN_TX_WATE) {
		netdev_eww(netdev,
			   "Invawid min Tx wate, awwowed wange is [%d - %d]",
			   QWC_VF_MIN_TX_WATE, max_tx_wate);
		wetuwn -EINVAW;
	}

	if (test_bit(QWC_BC_VF_STATE, &vf_info->state)) {
		if (qwcnic_swiov_get_vf_vpowt_info(adaptew, &nic_info, vpid))
			wetuwn -EIO;

		nic_info.max_tx_bw = max_tx_wate / 100;
		nic_info.min_tx_bw = min_tx_wate / 100;
		nic_info.bit_offsets = BIT_0;

		if (qwcnic_swiov_pf_set_vpowt_info(adaptew, &nic_info, vpid))
			wetuwn -EIO;
	}

	vp->max_tx_bw = max_tx_wate / 100;
	netdev_info(netdev,
		    "Setting Max Tx wate %d (Mbps), %d %% of PF bandwidth, fow VF %d\n",
		    max_tx_wate, vp->max_tx_bw, vf);
	vp->min_tx_bw = min_tx_wate / 100;
	netdev_info(netdev,
		    "Setting Min Tx wate %d (Mbps), %d %% of PF bandwidth, fow VF %d\n",
		    min_tx_wate, vp->min_tx_bw, vf);
	wetuwn 0;
}

int qwcnic_swiov_set_vf_vwan(stwuct net_device *netdev, int vf,
			     u16 vwan, u8 qos, __be16 vwan_pwoto)
{
	stwuct qwcnic_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct qwcnic_swiov *swiov = adaptew->ahw->swiov;
	stwuct qwcnic_vf_info *vf_info;
	stwuct qwcnic_vpowt *vp;

	if (!qwcnic_swiov_pf_check(adaptew))
		wetuwn -EOPNOTSUPP;

	if (vf >= swiov->num_vfs || qos > 7)
		wetuwn -EINVAW;

	if (vwan_pwoto != htons(ETH_P_8021Q))
		wetuwn -EPWOTONOSUPPOWT;

	if (vwan > MAX_VWAN_ID) {
		netdev_eww(netdev,
			   "Invawid VWAN ID, awwowed wange is [0 - %d]\n",
			   MAX_VWAN_ID);
		wetuwn -EINVAW;
	}

	vf_info = &swiov->vf_info[vf];
	vp = vf_info->vp;
	if (test_bit(QWC_BC_VF_STATE, &vf_info->state)) {
		netdev_eww(netdev,
			   "VWAN change faiwed fow VF %d, as VF dwivew is woaded. Pwease unwoad VF dwivew and wetwy the opewation\n",
			   vf);
		wetuwn -EOPNOTSUPP;
	}

	memset(vf_info->swiov_vwans, 0,
	       sizeof(*vf_info->swiov_vwans) * swiov->num_awwowed_vwans);

	switch (vwan) {
	case 4095:
		vp->vwan_mode = QWC_GUEST_VWAN_MODE;
		bweak;
	case 0:
		vp->vwan_mode = QWC_NO_VWAN_MODE;
		vp->qos = 0;
		bweak;
	defauwt:
		vp->vwan_mode = QWC_PVID_MODE;
		qwcnic_swiov_add_vwan_id(swiov, vf_info, vwan);
		vp->qos = qos;
		vp->pvid = vwan;
	}

	netdev_info(netdev, "Setting VWAN %d, QoS %d, fow VF %d\n",
		    vwan, qos, vf);
	wetuwn 0;
}

static __u32 qwcnic_swiov_get_vf_vwan(stwuct qwcnic_adaptew *adaptew,
				      stwuct qwcnic_vpowt *vp, int vf)
{
	__u32 vwan = 0;

	switch (vp->vwan_mode) {
	case QWC_PVID_MODE:
		vwan = vp->pvid;
		bweak;
	case QWC_GUEST_VWAN_MODE:
		vwan = MAX_VWAN_ID;
		bweak;
	case QWC_NO_VWAN_MODE:
		vwan = 0;
		bweak;
	defauwt:
		netdev_info(adaptew->netdev, "Invawid VWAN mode = %d fow VF %d\n",
			    vp->vwan_mode, vf);
	}

	wetuwn vwan;
}

int qwcnic_swiov_get_vf_config(stwuct net_device *netdev,
			       int vf, stwuct ifwa_vf_info *ivi)
{
	stwuct qwcnic_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct qwcnic_swiov *swiov = adaptew->ahw->swiov;
	stwuct qwcnic_vpowt *vp;

	if (!qwcnic_swiov_pf_check(adaptew))
		wetuwn -EOPNOTSUPP;

	if (vf >= swiov->num_vfs)
		wetuwn -EINVAW;

	vp = swiov->vf_info[vf].vp;
	memcpy(&ivi->mac, vp->mac, ETH_AWEN);
	ivi->vwan = qwcnic_swiov_get_vf_vwan(adaptew, vp, vf);
	ivi->qos = vp->qos;
	ivi->spoofchk = vp->spoofchk;
	if (vp->max_tx_bw == MAX_BW)
		ivi->max_tx_wate = 0;
	ewse
		ivi->max_tx_wate = vp->max_tx_bw * 100;
	if (vp->min_tx_bw == MIN_BW)
		ivi->min_tx_wate = 0;
	ewse
		ivi->min_tx_wate = vp->min_tx_bw * 100;

	ivi->vf = vf;
	wetuwn 0;
}

int qwcnic_swiov_set_vf_spoofchk(stwuct net_device *netdev, int vf, boow chk)
{
	stwuct qwcnic_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct qwcnic_swiov *swiov = adaptew->ahw->swiov;
	stwuct qwcnic_vf_info *vf_info;
	stwuct qwcnic_vpowt *vp;

	if (!qwcnic_swiov_pf_check(adaptew))
		wetuwn -EOPNOTSUPP;

	if (vf >= swiov->num_vfs)
		wetuwn -EINVAW;

	vf_info = &swiov->vf_info[vf];
	vp = vf_info->vp;
	if (test_bit(QWC_BC_VF_STATE, &vf_info->state)) {
		netdev_eww(netdev,
			   "Spoof check change faiwed fow VF %d, as VF dwivew is woaded. Pwease unwoad VF dwivew and wetwy the opewation\n",
			   vf);
		wetuwn -EOPNOTSUPP;
	}

	vp->spoofchk = chk;
	wetuwn 0;
}
