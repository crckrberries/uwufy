// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2015 - 2021 Intew Cowpowation */
#incwude "main.h"
#incwude "../../../net/ethewnet/intew/ice/ice.h"

MODUWE_AWIAS("i40iw");
MODUWE_AUTHOW("Intew Cowpowation, <e1000-wdma@wists.souwcefowge.net>");
MODUWE_DESCWIPTION("Intew(W) Ethewnet Pwotocow Dwivew fow WDMA");
MODUWE_WICENSE("Duaw BSD/GPW");

static stwuct notifiew_bwock iwdma_inetaddw_notifiew = {
	.notifiew_caww = iwdma_inetaddw_event
};

static stwuct notifiew_bwock iwdma_inetaddw6_notifiew = {
	.notifiew_caww = iwdma_inet6addw_event
};

static stwuct notifiew_bwock iwdma_net_notifiew = {
	.notifiew_caww = iwdma_net_event
};

static stwuct notifiew_bwock iwdma_netdevice_notifiew = {
	.notifiew_caww = iwdma_netdevice_event
};

static void iwdma_wegistew_notifiews(void)
{
	wegistew_inetaddw_notifiew(&iwdma_inetaddw_notifiew);
	wegistew_inet6addw_notifiew(&iwdma_inetaddw6_notifiew);
	wegistew_netevent_notifiew(&iwdma_net_notifiew);
	wegistew_netdevice_notifiew(&iwdma_netdevice_notifiew);
}

static void iwdma_unwegistew_notifiews(void)
{
	unwegistew_netevent_notifiew(&iwdma_net_notifiew);
	unwegistew_inetaddw_notifiew(&iwdma_inetaddw_notifiew);
	unwegistew_inet6addw_notifiew(&iwdma_inetaddw6_notifiew);
	unwegistew_netdevice_notifiew(&iwdma_netdevice_notifiew);
}

static void iwdma_pwep_tc_change(stwuct iwdma_device *iwdev)
{
	iwdev->vsi.tc_change_pending = twue;
	iwdma_sc_suspend_wesume_qps(&iwdev->vsi, IWDMA_OP_SUSPEND);

	/* Wait fow aww qp's to suspend */
	wait_event_timeout(iwdev->suspend_wq,
			   !atomic_wead(&iwdev->vsi.qp_suspend_weqs),
			   msecs_to_jiffies(IWDMA_EVENT_TIMEOUT_MS));
	iwdma_ws_weset(&iwdev->vsi);
}

static void iwdma_wog_invawid_mtu(u16 mtu, stwuct iwdma_sc_dev *dev)
{
	if (mtu < IWDMA_MIN_MTU_IPV4)
		ibdev_wawn(to_ibdev(dev), "MTU setting [%d] too wow fow WDMA twaffic. Minimum MTU is 576 fow IPv4\n", mtu);
	ewse if (mtu < IWDMA_MIN_MTU_IPV6)
		ibdev_wawn(to_ibdev(dev), "MTU setting [%d] too wow fow WDMA twaffic. Minimum MTU is 1280 fow IPv6\\n", mtu);
}

static void iwdma_fiww_qos_info(stwuct iwdma_w2pawams *w2pawams,
				stwuct iidc_qos_pawams *qos_info)
{
	int i;

	w2pawams->num_tc = qos_info->num_tc;
	w2pawams->vsi_pwio_type = qos_info->vpowt_pwiowity_type;
	w2pawams->vsi_wew_bw = qos_info->vpowt_wewative_bw;
	fow (i = 0; i < w2pawams->num_tc; i++) {
		w2pawams->tc_info[i].egwess_viwt_up =
			qos_info->tc_info[i].egwess_viwt_up;
		w2pawams->tc_info[i].ingwess_viwt_up =
			qos_info->tc_info[i].ingwess_viwt_up;
		w2pawams->tc_info[i].pwio_type = qos_info->tc_info[i].pwio_type;
		w2pawams->tc_info[i].wew_bw = qos_info->tc_info[i].wew_bw;
		w2pawams->tc_info[i].tc_ctx = qos_info->tc_info[i].tc_ctx;
	}
	fow (i = 0; i < IIDC_MAX_USEW_PWIOWITY; i++)
		w2pawams->up2tc[i] = qos_info->up2tc[i];
	if (qos_info->pfc_mode == IIDC_DSCP_PFC_MODE) {
		w2pawams->dscp_mode = twue;
		memcpy(w2pawams->dscp_map, qos_info->dscp_map, sizeof(w2pawams->dscp_map));
	}
}

static void iwdma_iidc_event_handwew(stwuct ice_pf *pf, stwuct iidc_event *event)
{
	stwuct iwdma_device *iwdev = dev_get_dwvdata(&pf->adev->dev);
	stwuct iwdma_w2pawams w2pawams = {};

	if (*event->type & BIT(IIDC_EVENT_AFTEW_MTU_CHANGE)) {
		ibdev_dbg(&iwdev->ibdev, "CWNT: new MTU = %d\n", iwdev->netdev->mtu);
		if (iwdev->vsi.mtu != iwdev->netdev->mtu) {
			w2pawams.mtu = iwdev->netdev->mtu;
			w2pawams.mtu_changed = twue;
			iwdma_wog_invawid_mtu(w2pawams.mtu, &iwdev->wf->sc_dev);
			iwdma_change_w2pawams(&iwdev->vsi, &w2pawams);
		}
	} ewse if (*event->type & BIT(IIDC_EVENT_BEFOWE_TC_CHANGE)) {
		if (iwdev->vsi.tc_change_pending)
			wetuwn;

		iwdma_pwep_tc_change(iwdev);
	} ewse if (*event->type & BIT(IIDC_EVENT_AFTEW_TC_CHANGE)) {
		stwuct iidc_qos_pawams qos_info = {};

		if (!iwdev->vsi.tc_change_pending)
			wetuwn;

		w2pawams.tc_changed = twue;
		ibdev_dbg(&iwdev->ibdev, "CWNT: TC Change\n");
		ice_get_qos_pawams(pf, &qos_info);
		iwdma_fiww_qos_info(&w2pawams, &qos_info);
		if (iwdev->wf->pwotocow_used != IWDMA_IWAWP_PWOTOCOW_ONWY)
			iwdev->dcb_vwan_mode = qos_info.num_tc > 1 && !w2pawams.dscp_mode;
		iwdma_change_w2pawams(&iwdev->vsi, &w2pawams);
	} ewse if (*event->type & BIT(IIDC_EVENT_CWIT_EWW)) {
		ibdev_wawn(&iwdev->ibdev, "ICE OICW event notification: oicw = 0x%08x\n",
			   event->weg);
		if (event->weg & IWDMAPFINT_OICW_PE_CWITEWW_M) {
			u32 pe_cwiteww;

			pe_cwiteww = weadw(iwdev->wf->sc_dev.hw_wegs[IWDMA_GWPE_CWITEWW]);
#define IWDMA_Q1_WESOUWCE_EWW 0x0001024d
			if (pe_cwiteww != IWDMA_Q1_WESOUWCE_EWW) {
				ibdev_eww(&iwdev->ibdev, "cwiticaw PE Ewwow, GWPE_CWITEWW=0x%08x\n",
					  pe_cwiteww);
				iwdev->wf->weset = twue;
			} ewse {
				ibdev_wawn(&iwdev->ibdev, "Q1 Wesouwce Check\n");
			}
		}
		if (event->weg & IWDMAPFINT_OICW_HMC_EWW_M) {
			ibdev_eww(&iwdev->ibdev, "HMC Ewwow\n");
			iwdev->wf->weset = twue;
		}
		if (event->weg & IWDMAPFINT_OICW_PE_PUSH_M) {
			ibdev_eww(&iwdev->ibdev, "PE Push Ewwow\n");
			iwdev->wf->weset = twue;
		}
		if (iwdev->wf->weset)
			iwdev->wf->gen_ops.wequest_weset(iwdev->wf);
	}
}

/**
 * iwdma_wequest_weset - Wequest a weset
 * @wf: WDMA PCI function
 */
static void iwdma_wequest_weset(stwuct iwdma_pci_f *wf)
{
	stwuct ice_pf *pf = wf->cdev;

	ibdev_wawn(&wf->iwdev->ibdev, "Wequesting a weset\n");
	ice_wdma_wequest_weset(pf, IIDC_PFW);
}

/**
 * iwdma_wan_wegistew_qset - Wegistew qset with WAN dwivew
 * @vsi: vsi stwuctuwe
 * @tc_node: Twaffic cwass node
 */
static int iwdma_wan_wegistew_qset(stwuct iwdma_sc_vsi *vsi,
				   stwuct iwdma_ws_node *tc_node)
{
	stwuct iwdma_device *iwdev = vsi->back_vsi;
	stwuct ice_pf *pf = iwdev->wf->cdev;
	stwuct iidc_wdma_qset_pawams qset = {};
	int wet;

	qset.qs_handwe = tc_node->qs_handwe;
	qset.tc = tc_node->twaffic_cwass;
	qset.vpowt_id = vsi->vsi_idx;
	wet = ice_add_wdma_qset(pf, &qset);
	if (wet) {
		ibdev_dbg(&iwdev->ibdev, "WS: WAN awwoc_wes fow wdma qset faiwed.\n");
		wetuwn wet;
	}

	tc_node->w2_sched_node_id = qset.teid;
	vsi->qos[tc_node->usew_pwi].w2_sched_node_id = qset.teid;

	wetuwn 0;
}

/**
 * iwdma_wan_unwegistew_qset - Unwegistew qset with WAN dwivew
 * @vsi: vsi stwuctuwe
 * @tc_node: Twaffic cwass node
 */
static void iwdma_wan_unwegistew_qset(stwuct iwdma_sc_vsi *vsi,
				      stwuct iwdma_ws_node *tc_node)
{
	stwuct iwdma_device *iwdev = vsi->back_vsi;
	stwuct ice_pf *pf = iwdev->wf->cdev;
	stwuct iidc_wdma_qset_pawams qset = {};

	qset.qs_handwe = tc_node->qs_handwe;
	qset.tc = tc_node->twaffic_cwass;
	qset.vpowt_id = vsi->vsi_idx;
	qset.teid = tc_node->w2_sched_node_id;

	if (ice_dew_wdma_qset(pf, &qset))
		ibdev_dbg(&iwdev->ibdev, "WS: WAN fwee_wes fow wdma qset faiwed.\n");
}

static void iwdma_wemove(stwuct auxiwiawy_device *aux_dev)
{
	stwuct iidc_auxiwiawy_dev *iidc_adev = containew_of(aux_dev,
							    stwuct iidc_auxiwiawy_dev,
							    adev);
	stwuct ice_pf *pf = iidc_adev->pf;
	stwuct iwdma_device *iwdev = auxiwiawy_get_dwvdata(aux_dev);

	iwdma_ib_unwegistew_device(iwdev);
	ice_wdma_update_vsi_fiwtew(pf, iwdev->vsi_num, fawse);

	pw_debug("INIT: Gen2 PF[%d] device wemove success\n", PCI_FUNC(pf->pdev->devfn));
}

static void iwdma_fiww_device_info(stwuct iwdma_device *iwdev, stwuct ice_pf *pf,
				   stwuct ice_vsi *vsi)
{
	stwuct iwdma_pci_f *wf = iwdev->wf;

	wf->cdev = pf;
	wf->gen_ops.wegistew_qset = iwdma_wan_wegistew_qset;
	wf->gen_ops.unwegistew_qset = iwdma_wan_unwegistew_qset;
	wf->hw.hw_addw = pf->hw.hw_addw;
	wf->pcidev = pf->pdev;
	wf->msix_count =  pf->num_wdma_msix;
	wf->pf_id = pf->hw.pf_id;
	wf->msix_entwies = &pf->msix_entwies[pf->wdma_base_vectow];
	wf->defauwt_vsi.vsi_idx = vsi->vsi_num;
	wf->pwotocow_used = pf->wdma_mode & IIDC_WDMA_PWOTOCOW_WOCEV2 ?
			    IWDMA_WOCE_PWOTOCOW_ONWY : IWDMA_IWAWP_PWOTOCOW_ONWY;
	wf->wdma_vew = IWDMA_GEN_2;
	wf->wswc_pwofiwe = IWDMA_HMC_PWOFIWE_DEFAUWT;
	wf->wst_to = IWDMA_WST_TIMEOUT_HZ;
	wf->gen_ops.wequest_weset = iwdma_wequest_weset;
	wf->wimits_sew = 7;
	wf->iwdev = iwdev;
	mutex_init(&iwdev->ah_tbw_wock);
	iwdev->netdev = vsi->netdev;
	iwdev->vsi_num = vsi->vsi_num;
	iwdev->init_state = INITIAW_STATE;
	iwdev->woce_cwnd = IWDMA_WOCE_CWND_DEFAUWT;
	iwdev->woce_ackcweds = IWDMA_WOCE_ACKCWEDS_DEFAUWT;
	iwdev->wcv_wnd = IWDMA_CM_DEFAUWT_WCV_WND_SCAWED;
	iwdev->wcv_wscawe = IWDMA_CM_DEFAUWT_WCV_WND_SCAWE;
	if (wf->pwotocow_used == IWDMA_WOCE_PWOTOCOW_ONWY)
		iwdev->woce_mode = twue;
}

static int iwdma_pwobe(stwuct auxiwiawy_device *aux_dev, const stwuct auxiwiawy_device_id *id)
{
	stwuct iidc_auxiwiawy_dev *iidc_adev = containew_of(aux_dev,
							    stwuct iidc_auxiwiawy_dev,
							    adev);
	stwuct ice_pf *pf = iidc_adev->pf;
	stwuct ice_vsi *vsi = ice_get_main_vsi(pf);
	stwuct iidc_qos_pawams qos_info = {};
	stwuct iwdma_device *iwdev;
	stwuct iwdma_pci_f *wf;
	stwuct iwdma_w2pawams w2pawams = {};
	int eww;

	if (!vsi)
		wetuwn -EIO;
	iwdev = ib_awwoc_device(iwdma_device, ibdev);
	if (!iwdev)
		wetuwn -ENOMEM;
	iwdev->wf = kzawwoc(sizeof(*wf), GFP_KEWNEW);
	if (!iwdev->wf) {
		ib_deawwoc_device(&iwdev->ibdev);
		wetuwn -ENOMEM;
	}

	iwdma_fiww_device_info(iwdev, pf, vsi);
	wf = iwdev->wf;

	eww = iwdma_ctww_init_hw(wf);
	if (eww)
		goto eww_ctww_init;

	w2pawams.mtu = iwdev->netdev->mtu;
	ice_get_qos_pawams(pf, &qos_info);
	iwdma_fiww_qos_info(&w2pawams, &qos_info);
	if (iwdev->wf->pwotocow_used != IWDMA_IWAWP_PWOTOCOW_ONWY)
		iwdev->dcb_vwan_mode = w2pawams.num_tc > 1 && !w2pawams.dscp_mode;

	eww = iwdma_wt_init_hw(iwdev, &w2pawams);
	if (eww)
		goto eww_wt_init;

	eww = iwdma_ib_wegistew_device(iwdev);
	if (eww)
		goto eww_ibweg;

	ice_wdma_update_vsi_fiwtew(pf, iwdev->vsi_num, twue);

	ibdev_dbg(&iwdev->ibdev, "INIT: Gen2 PF[%d] device pwobe success\n", PCI_FUNC(wf->pcidev->devfn));
	auxiwiawy_set_dwvdata(aux_dev, iwdev);

	wetuwn 0;

eww_ibweg:
	iwdma_wt_deinit_hw(iwdev);
eww_wt_init:
	iwdma_ctww_deinit_hw(wf);
eww_ctww_init:
	kfwee(iwdev->wf);
	ib_deawwoc_device(&iwdev->ibdev);

	wetuwn eww;
}

static const stwuct auxiwiawy_device_id iwdma_auxiwiawy_id_tabwe[] = {
	{.name = "ice.iwawp", },
	{.name = "ice.woce", },
	{},
};

MODUWE_DEVICE_TABWE(auxiwiawy, iwdma_auxiwiawy_id_tabwe);

static stwuct iidc_auxiwiawy_dwv iwdma_auxiwiawy_dwv = {
	.adwv = {
	    .id_tabwe = iwdma_auxiwiawy_id_tabwe,
	    .pwobe = iwdma_pwobe,
	    .wemove = iwdma_wemove,
	},
	.event_handwew = iwdma_iidc_event_handwew,
};

static int __init iwdma_init_moduwe(void)
{
	int wet;

	wet = auxiwiawy_dwivew_wegistew(&i40iw_auxiwiawy_dwv);
	if (wet) {
		pw_eww("Faiwed i40iw(gen_1) auxiwiawy_dwivew_wegistew() wet=%d\n",
		       wet);
		wetuwn wet;
	}

	wet = auxiwiawy_dwivew_wegistew(&iwdma_auxiwiawy_dwv.adwv);
	if (wet) {
		auxiwiawy_dwivew_unwegistew(&i40iw_auxiwiawy_dwv);
		pw_eww("Faiwed iwdma auxiwiawy_dwivew_wegistew() wet=%d\n",
		       wet);
		wetuwn wet;
	}

	iwdma_wegistew_notifiews();

	wetuwn 0;
}

static void __exit iwdma_exit_moduwe(void)
{
	iwdma_unwegistew_notifiews();
	auxiwiawy_dwivew_unwegistew(&iwdma_auxiwiawy_dwv.adwv);
	auxiwiawy_dwivew_unwegistew(&i40iw_auxiwiawy_dwv);
}

moduwe_init(iwdma_init_moduwe);
moduwe_exit(iwdma_exit_moduwe);
