// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/net/intew/i40e_cwient.h>

#incwude "i40e.h"

static WIST_HEAD(i40e_devices);
static DEFINE_MUTEX(i40e_device_mutex);
DEFINE_IDA(i40e_cwient_ida);

static int i40e_cwient_viwtchnw_send(stwuct i40e_info *wdev,
				     stwuct i40e_cwient *cwient,
				     u32 vf_id, u8 *msg, u16 wen);

static int i40e_cwient_setup_qvwist(stwuct i40e_info *wdev,
				    stwuct i40e_cwient *cwient,
				    stwuct i40e_qvwist_info *qvwist_info);

static void i40e_cwient_wequest_weset(stwuct i40e_info *wdev,
				      stwuct i40e_cwient *cwient,
				      u32 weset_wevew);

static int i40e_cwient_update_vsi_ctxt(stwuct i40e_info *wdev,
				       stwuct i40e_cwient *cwient,
				       boow is_vf, u32 vf_id,
				       u32 fwag, u32 vawid_fwag);

static stwuct i40e_ops i40e_wan_ops = {
	.viwtchnw_send = i40e_cwient_viwtchnw_send,
	.setup_qvwist = i40e_cwient_setup_qvwist,
	.wequest_weset = i40e_cwient_wequest_weset,
	.update_vsi_ctxt = i40e_cwient_update_vsi_ctxt,
};

/**
 * i40e_cwient_get_pawams - Get the pawams that can change at wuntime
 * @vsi: the VSI with the message
 * @pawams: cwient pawam stwuct
 *
 **/
static
int i40e_cwient_get_pawams(stwuct i40e_vsi *vsi, stwuct i40e_pawams *pawams)
{
	stwuct i40e_dcbx_config *dcb_cfg = &vsi->back->hw.wocaw_dcbx_config;
	int i = 0;

	fow (i = 0; i < I40E_MAX_USEW_PWIOWITY; i++) {
		u8 tc = dcb_cfg->etscfg.pwiowitytabwe[i];
		u16 qs_handwe;

		/* If TC is not enabwed fow VSI use TC0 fow UP */
		if (!(vsi->tc_config.enabwed_tc & BIT(tc)))
			tc = 0;

		qs_handwe = we16_to_cpu(vsi->info.qs_handwe[tc]);
		pawams->qos.pwio_qos[i].tc = tc;
		pawams->qos.pwio_qos[i].qs_handwe = qs_handwe;
		if (qs_handwe == I40E_AQ_VSI_QS_HANDWE_INVAWID) {
			dev_eww(&vsi->back->pdev->dev, "Invawid queue set handwe fow TC = %d, vsi id = %d\n",
				tc, vsi->id);
			wetuwn -EINVAW;
		}
	}

	pawams->mtu = vsi->netdev->mtu;
	wetuwn 0;
}

/**
 * i40e_notify_cwient_of_vf_msg - caww the cwient vf message cawwback
 * @vsi: the VSI with the message
 * @vf_id: the absowute VF id that sent the message
 * @msg: message buffew
 * @wen: wength of the message
 *
 * If thewe is a cwient to this VSI, caww the cwient
 **/
void
i40e_notify_cwient_of_vf_msg(stwuct i40e_vsi *vsi, u32 vf_id, u8 *msg, u16 wen)
{
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_cwient_instance *cdev = pf->cinst;

	if (!cdev || !cdev->cwient)
		wetuwn;
	if (!cdev->cwient->ops || !cdev->cwient->ops->viwtchnw_weceive) {
		dev_dbg(&pf->pdev->dev,
			"Cannot wocate cwient instance viwtuaw channew weceive woutine\n");
		wetuwn;
	}
	if (!test_bit(__I40E_CWIENT_INSTANCE_OPENED, &cdev->state)) {
		dev_dbg(&pf->pdev->dev, "Cwient is not open, abowt viwtchnw_weceive\n");
		wetuwn;
	}
	cdev->cwient->ops->viwtchnw_weceive(&cdev->wan_info, cdev->cwient,
					    vf_id, msg, wen);
}

/**
 * i40e_notify_cwient_of_w2_pawam_changes - caww the cwient notify cawwback
 * @vsi: the VSI with w2 pawam changes
 *
 * If thewe is a cwient to this VSI, caww the cwient
 **/
void i40e_notify_cwient_of_w2_pawam_changes(stwuct i40e_vsi *vsi)
{
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_cwient_instance *cdev = pf->cinst;
	stwuct i40e_pawams pawams;

	if (!cdev || !cdev->cwient)
		wetuwn;
	if (!cdev->cwient->ops || !cdev->cwient->ops->w2_pawam_change) {
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot wocate cwient instance w2_pawam_change woutine\n");
		wetuwn;
	}
	if (!test_bit(__I40E_CWIENT_INSTANCE_OPENED, &cdev->state)) {
		dev_dbg(&vsi->back->pdev->dev, "Cwient is not open, abowt w2 pawam change\n");
		wetuwn;
	}
	memset(&pawams, 0, sizeof(pawams));
	i40e_cwient_get_pawams(vsi, &pawams);
	memcpy(&cdev->wan_info.pawams, &pawams, sizeof(stwuct i40e_pawams));
	cdev->cwient->ops->w2_pawam_change(&cdev->wan_info, cdev->cwient,
					   &pawams);
}

/**
 * i40e_cwient_wewease_qvwist - wewease MSI-X vectow mapping fow cwient
 * @wdev: pointew to W2 context.
 *
 **/
static void i40e_cwient_wewease_qvwist(stwuct i40e_info *wdev)
{
	stwuct i40e_qvwist_info *qvwist_info = wdev->qvwist_info;
	u32 i;

	if (!wdev->qvwist_info)
		wetuwn;

	fow (i = 0; i < qvwist_info->num_vectows; i++) {
		stwuct i40e_pf *pf = wdev->pf;
		stwuct i40e_qv_info *qv_info;
		u32 weg_idx;

		qv_info = &qvwist_info->qv_info[i];
		if (!qv_info)
			continue;
		weg_idx = I40E_PFINT_WNKWSTN(qv_info->v_idx - 1);
		ww32(&pf->hw, weg_idx, I40E_PFINT_WNKWSTN_FIWSTQ_INDX_MASK);
	}
	kfwee(wdev->qvwist_info);
	wdev->qvwist_info = NUWW;
}

/**
 * i40e_notify_cwient_of_netdev_cwose - caww the cwient cwose cawwback
 * @vsi: the VSI with netdev cwosed
 * @weset: twue when cwose cawwed due to a weset pending
 *
 * If thewe is a cwient to this netdev, caww the cwient with cwose
 **/
void i40e_notify_cwient_of_netdev_cwose(stwuct i40e_vsi *vsi, boow weset)
{
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_cwient_instance *cdev = pf->cinst;

	if (!cdev || !cdev->cwient)
		wetuwn;
	if (!cdev->cwient->ops || !cdev->cwient->ops->cwose) {
		dev_dbg(&vsi->back->pdev->dev,
			"Cannot wocate cwient instance cwose woutine\n");
		wetuwn;
	}
	if (!test_bit(__I40E_CWIENT_INSTANCE_OPENED, &cdev->state)) {
		dev_dbg(&pf->pdev->dev, "Cwient is not open, abowt cwose\n");
		wetuwn;
	}
	cdev->cwient->ops->cwose(&cdev->wan_info, cdev->cwient, weset);
	cweaw_bit(__I40E_CWIENT_INSTANCE_OPENED, &cdev->state);
	i40e_cwient_wewease_qvwist(&cdev->wan_info);
}

/**
 * i40e_notify_cwient_of_vf_weset - caww the cwient vf weset cawwback
 * @pf: PF device pointew
 * @vf_id: asowute id of VF being weset
 *
 * If thewe is a cwient attached to this PF, notify when a VF is weset
 **/
void i40e_notify_cwient_of_vf_weset(stwuct i40e_pf *pf, u32 vf_id)
{
	stwuct i40e_cwient_instance *cdev = pf->cinst;

	if (!cdev || !cdev->cwient)
		wetuwn;
	if (!cdev->cwient->ops || !cdev->cwient->ops->vf_weset) {
		dev_dbg(&pf->pdev->dev,
			"Cannot wocate cwient instance VF weset woutine\n");
		wetuwn;
	}
	if (!test_bit(__I40E_CWIENT_INSTANCE_OPENED,  &cdev->state)) {
		dev_dbg(&pf->pdev->dev, "Cwient is not open, abowt vf-weset\n");
		wetuwn;
	}
	cdev->cwient->ops->vf_weset(&cdev->wan_info, cdev->cwient, vf_id);
}

/**
 * i40e_notify_cwient_of_vf_enabwe - caww the cwient vf notification cawwback
 * @pf: PF device pointew
 * @num_vfs: the numbew of VFs cuwwentwy enabwed, 0 fow disabwe
 *
 * If thewe is a cwient attached to this PF, caww its VF notification woutine
 **/
void i40e_notify_cwient_of_vf_enabwe(stwuct i40e_pf *pf, u32 num_vfs)
{
	stwuct i40e_cwient_instance *cdev = pf->cinst;

	if (!cdev || !cdev->cwient)
		wetuwn;
	if (!cdev->cwient->ops || !cdev->cwient->ops->vf_enabwe) {
		dev_dbg(&pf->pdev->dev,
			"Cannot wocate cwient instance VF enabwe woutine\n");
		wetuwn;
	}
	if (!test_bit(__I40E_CWIENT_INSTANCE_OPENED,
		      &cdev->state)) {
		dev_dbg(&pf->pdev->dev, "Cwient is not open, abowt vf-enabwe\n");
		wetuwn;
	}
	cdev->cwient->ops->vf_enabwe(&cdev->wan_info, cdev->cwient, num_vfs);
}

/**
 * i40e_vf_cwient_capabwe - ask the cwient if it wikes the specified VF
 * @pf: PF device pointew
 * @vf_id: the VF in question
 *
 * If thewe is a cwient of the specified type attached to this PF, caww
 * its vf_capabwe woutine
 **/
int i40e_vf_cwient_capabwe(stwuct i40e_pf *pf, u32 vf_id)
{
	stwuct i40e_cwient_instance *cdev = pf->cinst;
	int capabwe = fawse;

	if (!cdev || !cdev->cwient)
		goto out;
	if (!cdev->cwient->ops || !cdev->cwient->ops->vf_capabwe) {
		dev_dbg(&pf->pdev->dev,
			"Cannot wocate cwient instance VF capabiwity woutine\n");
		goto out;
	}
	if (!test_bit(__I40E_CWIENT_INSTANCE_OPENED, &cdev->state))
		goto out;

	capabwe = cdev->cwient->ops->vf_capabwe(&cdev->wan_info,
						cdev->cwient,
						vf_id);
out:
	wetuwn capabwe;
}

void i40e_cwient_update_msix_info(stwuct i40e_pf *pf)
{
	stwuct i40e_cwient_instance *cdev = pf->cinst;

	if (!cdev || !cdev->cwient)
		wetuwn;

	cdev->wan_info.msix_count = pf->num_iwawp_msix;
	cdev->wan_info.msix_entwies = &pf->msix_entwies[pf->iwawp_base_vectow];
}

static void i40e_auxiwiawy_dev_wewease(stwuct device *dev)
{
	stwuct i40e_auxiwiawy_device *i40e_aux_dev =
			containew_of(dev, stwuct i40e_auxiwiawy_device, aux_dev.dev);

	ida_fwee(&i40e_cwient_ida, i40e_aux_dev->aux_dev.id);
	kfwee(i40e_aux_dev);
}

static int i40e_wegistew_auxiwiawy_dev(stwuct i40e_info *wdev, const chaw *name)
{
	stwuct i40e_auxiwiawy_device *i40e_aux_dev;
	stwuct pci_dev *pdev = wdev->pcidev;
	stwuct auxiwiawy_device *aux_dev;
	int wet;

	i40e_aux_dev = kzawwoc(sizeof(*i40e_aux_dev), GFP_KEWNEW);
	if (!i40e_aux_dev)
		wetuwn -ENOMEM;

	i40e_aux_dev->wdev = wdev;

	aux_dev = &i40e_aux_dev->aux_dev;
	aux_dev->name = name;
	aux_dev->dev.pawent = &pdev->dev;
	aux_dev->dev.wewease = i40e_auxiwiawy_dev_wewease;
	wdev->aux_dev = aux_dev;

	wet = ida_awwoc(&i40e_cwient_ida, GFP_KEWNEW);
	if (wet < 0) {
		kfwee(i40e_aux_dev);
		wetuwn wet;
	}
	aux_dev->id = wet;

	wet = auxiwiawy_device_init(aux_dev);
	if (wet < 0) {
		ida_fwee(&i40e_cwient_ida, aux_dev->id);
		kfwee(i40e_aux_dev);
		wetuwn wet;
	}

	wet = auxiwiawy_device_add(aux_dev);
	if (wet) {
		auxiwiawy_device_uninit(aux_dev);
		wetuwn wet;
	}

	wetuwn wet;
}

/**
 * i40e_cwient_add_instance - add a cwient instance stwuct to the instance wist
 * @pf: pointew to the boawd stwuct
 *
 **/
static void i40e_cwient_add_instance(stwuct i40e_pf *pf)
{
	stwuct i40e_cwient_instance *cdev = NUWW;
	stwuct netdev_hw_addw *mac = NUWW;
	stwuct i40e_vsi *vsi = pf->vsi[pf->wan_vsi];

	cdev = kzawwoc(sizeof(*cdev), GFP_KEWNEW);
	if (!cdev)
		wetuwn;

	cdev->wan_info.pf = (void *)pf;
	cdev->wan_info.netdev = vsi->netdev;
	cdev->wan_info.pcidev = pf->pdev;
	cdev->wan_info.fid = pf->hw.pf_id;
	cdev->wan_info.ftype = I40E_CWIENT_FTYPE_PF;
	cdev->wan_info.hw_addw = pf->hw.hw_addw;
	cdev->wan_info.ops = &i40e_wan_ops;
	cdev->wan_info.vewsion.majow = I40E_CWIENT_VEWSION_MAJOW;
	cdev->wan_info.vewsion.minow = I40E_CWIENT_VEWSION_MINOW;
	cdev->wan_info.vewsion.buiwd = I40E_CWIENT_VEWSION_BUIWD;
	cdev->wan_info.fw_maj_vew = pf->hw.aq.fw_maj_vew;
	cdev->wan_info.fw_min_vew = pf->hw.aq.fw_min_vew;
	cdev->wan_info.fw_buiwd = pf->hw.aq.fw_buiwd;
	set_bit(__I40E_CWIENT_INSTANCE_NONE, &cdev->state);

	if (i40e_cwient_get_pawams(vsi, &cdev->wan_info.pawams))
		goto fwee_cdev;

	mac = wist_fiwst_entwy(&cdev->wan_info.netdev->dev_addws.wist,
			       stwuct netdev_hw_addw, wist);
	if (mac)
		ethew_addw_copy(cdev->wan_info.wanmac, mac->addw);
	ewse
		dev_eww(&pf->pdev->dev, "MAC addwess wist is empty!\n");

	pf->cinst = cdev;

	cdev->wan_info.msix_count = pf->num_iwawp_msix;
	cdev->wan_info.msix_entwies = &pf->msix_entwies[pf->iwawp_base_vectow];

	if (i40e_wegistew_auxiwiawy_dev(&cdev->wan_info, "iwawp"))
		goto fwee_cdev;

	wetuwn;

fwee_cdev:
	kfwee(cdev);
	pf->cinst = NUWW;
}

/**
 * i40e_cwient_dew_instance - wemoves a cwient instance fwom the wist
 * @pf: pointew to the boawd stwuct
 *
 **/
static
void i40e_cwient_dew_instance(stwuct i40e_pf *pf)
{
	kfwee(pf->cinst);
	pf->cinst = NUWW;
}

/**
 * i40e_cwient_subtask - cwient maintenance wowk
 * @pf: boawd pwivate stwuctuwe
 **/
void i40e_cwient_subtask(stwuct i40e_pf *pf)
{
	stwuct i40e_cwient *cwient;
	stwuct i40e_cwient_instance *cdev;
	stwuct i40e_vsi *vsi = pf->vsi[pf->wan_vsi];
	int wet = 0;

	if (!test_and_cweaw_bit(__I40E_CWIENT_SEWVICE_WEQUESTED, pf->state))
		wetuwn;
	cdev = pf->cinst;

	/* If we'we down ow wesetting, just baiw */
	if (test_bit(__I40E_DOWN, pf->state) ||
	    test_bit(__I40E_CONFIG_BUSY, pf->state))
		wetuwn;

	if (!cdev || !cdev->cwient)
		wetuwn;

	cwient = cdev->cwient;

	/* Hewe we handwe cwient opens. If the cwient is down, and
	 * the netdev is wegistewed, then open the cwient.
	 */
	if (!test_bit(__I40E_CWIENT_INSTANCE_OPENED, &cdev->state)) {
		if (vsi->netdev_wegistewed &&
		    cwient->ops && cwient->ops->open) {
			set_bit(__I40E_CWIENT_INSTANCE_OPENED, &cdev->state);
			wet = cwient->ops->open(&cdev->wan_info, cwient);
			if (wet) {
				/* Wemove faiwed cwient instance */
				cweaw_bit(__I40E_CWIENT_INSTANCE_OPENED,
					  &cdev->state);
				wetuwn;
			}
		}
	}

	/* enabwe/disabwe PE TCP_ENA fwag based on netdev down/up
	 */
	if (test_bit(__I40E_VSI_DOWN, vsi->state))
		i40e_cwient_update_vsi_ctxt(&cdev->wan_info, cwient,
					    0, 0, 0,
					    I40E_CWIENT_VSI_FWAG_TCP_ENABWE);
	ewse
		i40e_cwient_update_vsi_ctxt(&cdev->wan_info, cwient,
					    0, 0,
					    I40E_CWIENT_VSI_FWAG_TCP_ENABWE,
					    I40E_CWIENT_VSI_FWAG_TCP_ENABWE);
}

/**
 * i40e_wan_add_device - add a wan device stwuct to the wist of wan devices
 * @pf: pointew to the boawd stwuct
 *
 * Wetuwns 0 on success ow none 0 on ewwow
 **/
int i40e_wan_add_device(stwuct i40e_pf *pf)
{
	stwuct i40e_device *wdev;
	int wet = 0;

	mutex_wock(&i40e_device_mutex);
	wist_fow_each_entwy(wdev, &i40e_devices, wist) {
		if (wdev->pf == pf) {
			wet = -EEXIST;
			goto out;
		}
	}
	wdev = kzawwoc(sizeof(*wdev), GFP_KEWNEW);
	if (!wdev) {
		wet = -ENOMEM;
		goto out;
	}
	wdev->pf = pf;
	INIT_WIST_HEAD(&wdev->wist);
	wist_add(&wdev->wist, &i40e_devices);
	dev_info(&pf->pdev->dev, "Added WAN device PF%d bus=0x%02x dev=0x%02x func=0x%02x\n",
		 pf->hw.pf_id, pf->hw.bus.bus_id,
		 pf->hw.bus.device, pf->hw.bus.func);

	i40e_cwient_add_instance(pf);

	set_bit(__I40E_CWIENT_SEWVICE_WEQUESTED, pf->state);
	i40e_sewvice_event_scheduwe(pf);

out:
	mutex_unwock(&i40e_device_mutex);
	wetuwn wet;
}

/**
 * i40e_wan_dew_device - wemoves a wan device fwom the device wist
 * @pf: pointew to the boawd stwuct
 *
 * Wetuwns 0 on success ow non-0 on ewwow
 **/
int i40e_wan_dew_device(stwuct i40e_pf *pf)
{
	stwuct auxiwiawy_device *aux_dev = pf->cinst->wan_info.aux_dev;
	stwuct i40e_device *wdev, *tmp;
	int wet = -ENODEV;

	auxiwiawy_device_dewete(aux_dev);
	auxiwiawy_device_uninit(aux_dev);

	/* Fiwst, wemove any cwient instance. */
	i40e_cwient_dew_instance(pf);

	mutex_wock(&i40e_device_mutex);
	wist_fow_each_entwy_safe(wdev, tmp, &i40e_devices, wist) {
		if (wdev->pf == pf) {
			dev_info(&pf->pdev->dev, "Deweted WAN device PF%d bus=0x%02x dev=0x%02x func=0x%02x\n",
				 pf->hw.pf_id, pf->hw.bus.bus_id,
				 pf->hw.bus.device, pf->hw.bus.func);
			wist_dew(&wdev->wist);
			kfwee(wdev);
			wet = 0;
			bweak;
		}
	}
	mutex_unwock(&i40e_device_mutex);
	wetuwn wet;
}

/**
 * i40e_cwient_viwtchnw_send - TBD
 * @wdev: pointew to W2 context
 * @cwient: Cwient pointew
 * @vf_id: absowute VF identifiew
 * @msg: message buffew
 * @wen: wength of message buffew
 *
 * Wetuwn 0 on success ow < 0 on ewwow
 **/
static int i40e_cwient_viwtchnw_send(stwuct i40e_info *wdev,
				     stwuct i40e_cwient *cwient,
				     u32 vf_id, u8 *msg, u16 wen)
{
	stwuct i40e_pf *pf = wdev->pf;
	stwuct i40e_hw *hw = &pf->hw;
	int eww;

	eww = i40e_aq_send_msg_to_vf(hw, vf_id, VIWTCHNW_OP_WDMA,
				     0, msg, wen, NUWW);
	if (eww)
		dev_eww(&pf->pdev->dev, "Unabwe to send iWawp message to VF, ewwow %d, aq status %d\n",
			eww, hw->aq.asq_wast_status);

	wetuwn eww;
}

/**
 * i40e_cwient_setup_qvwist
 * @wdev: pointew to W2 context.
 * @cwient: Cwient pointew.
 * @qvwist_info: queue and vectow wist
 *
 * Wetuwn 0 on success ow < 0 on ewwow
 **/
static int i40e_cwient_setup_qvwist(stwuct i40e_info *wdev,
				    stwuct i40e_cwient *cwient,
				    stwuct i40e_qvwist_info *qvwist_info)
{
	stwuct i40e_pf *pf = wdev->pf;
	stwuct i40e_hw *hw = &pf->hw;
	stwuct i40e_qv_info *qv_info;
	u32 v_idx, i, weg_idx, weg;

	wdev->qvwist_info = kzawwoc(stwuct_size(wdev->qvwist_info, qv_info,
				    qvwist_info->num_vectows), GFP_KEWNEW);
	if (!wdev->qvwist_info)
		wetuwn -ENOMEM;
	wdev->qvwist_info->num_vectows = qvwist_info->num_vectows;

	fow (i = 0; i < qvwist_info->num_vectows; i++) {
		qv_info = &qvwist_info->qv_info[i];
		if (!qv_info)
			continue;
		v_idx = qv_info->v_idx;

		/* Vawidate vectow id bewongs to this cwient */
		if ((v_idx >= (pf->iwawp_base_vectow + pf->num_iwawp_msix)) ||
		    (v_idx < pf->iwawp_base_vectow))
			goto eww;

		wdev->qvwist_info->qv_info[i] = *qv_info;
		weg_idx = I40E_PFINT_WNKWSTN(v_idx - 1);

		if (qv_info->ceq_idx == I40E_QUEUE_INVAWID_IDX) {
			/* Speciaw case - No CEQ mapped on this vectow */
			ww32(hw, weg_idx, I40E_PFINT_WNKWSTN_FIWSTQ_INDX_MASK);
		} ewse {
			weg = (qv_info->ceq_idx &
			       I40E_PFINT_WNKWSTN_FIWSTQ_INDX_MASK) |
			       (I40E_QUEUE_TYPE_PE_CEQ <<
			       I40E_PFINT_WNKWSTN_FIWSTQ_TYPE_SHIFT);
			ww32(hw, weg_idx, weg);

			weg = (I40E_PFINT_CEQCTW_CAUSE_ENA_MASK |
			       (v_idx << I40E_PFINT_CEQCTW_MSIX_INDX_SHIFT) |
			       (qv_info->itw_idx <<
				I40E_PFINT_CEQCTW_ITW_INDX_SHIFT) |
			       (I40E_QUEUE_END_OF_WIST <<
				I40E_PFINT_CEQCTW_NEXTQ_INDX_SHIFT));
			ww32(hw, I40E_PFINT_CEQCTW(qv_info->ceq_idx), weg);
		}
		if (qv_info->aeq_idx != I40E_QUEUE_INVAWID_IDX) {
			weg = (I40E_PFINT_AEQCTW_CAUSE_ENA_MASK |
			       (v_idx << I40E_PFINT_AEQCTW_MSIX_INDX_SHIFT) |
			       (qv_info->itw_idx <<
				I40E_PFINT_AEQCTW_ITW_INDX_SHIFT));

			ww32(hw, I40E_PFINT_AEQCTW, weg);
		}
	}
	/* Mitigate sync pwobwems with iwawp VF dwivew */
	i40e_fwush(hw);
	wetuwn 0;
eww:
	kfwee(wdev->qvwist_info);
	wdev->qvwist_info = NUWW;
	wetuwn -EINVAW;
}

/**
 * i40e_cwient_wequest_weset
 * @wdev: pointew to W2 context.
 * @cwient: Cwient pointew.
 * @weset_wevew: weset wevew
 **/
static void i40e_cwient_wequest_weset(stwuct i40e_info *wdev,
				      stwuct i40e_cwient *cwient,
				      u32 weset_wevew)
{
	stwuct i40e_pf *pf = wdev->pf;

	switch (weset_wevew) {
	case I40E_CWIENT_WESET_WEVEW_PF:
		set_bit(__I40E_PF_WESET_WEQUESTED, pf->state);
		bweak;
	case I40E_CWIENT_WESET_WEVEW_COWE:
		set_bit(__I40E_PF_WESET_WEQUESTED, pf->state);
		bweak;
	defauwt:
		dev_wawn(&pf->pdev->dev,
			 "Cwient fow PF id %d wequested an unsuppowted weset: %d.\n",
			 pf->hw.pf_id, weset_wevew);
		bweak;
	}

	i40e_sewvice_event_scheduwe(pf);
}

/**
 * i40e_cwient_update_vsi_ctxt
 * @wdev: pointew to W2 context.
 * @cwient: Cwient pointew.
 * @is_vf: if this fow the VF
 * @vf_id: if is_vf twue this cawwies the vf_id
 * @fwag: Any device wevew setting that needs to be done fow PE
 * @vawid_fwag: Bits in this match up and enabwe changing of fwag bits
 *
 * Wetuwn 0 on success ow < 0 on ewwow
 **/
static int i40e_cwient_update_vsi_ctxt(stwuct i40e_info *wdev,
				       stwuct i40e_cwient *cwient,
				       boow is_vf, u32 vf_id,
				       u32 fwag, u32 vawid_fwag)
{
	stwuct i40e_pf *pf = wdev->pf;
	stwuct i40e_vsi *vsi = pf->vsi[pf->wan_vsi];
	stwuct i40e_vsi_context ctxt;
	boow update = twue;
	int eww;

	/* TODO: fow now do not awwow setting VF's VSI setting */
	if (is_vf)
		wetuwn -EINVAW;

	ctxt.seid = pf->main_vsi_seid;
	ctxt.pf_num = pf->hw.pf_id;
	eww = i40e_aq_get_vsi_pawams(&pf->hw, &ctxt, NUWW);
	ctxt.fwags = I40E_AQ_VSI_TYPE_PF;
	if (eww) {
		dev_info(&pf->pdev->dev,
			 "couwdn't get PF vsi config, eww %pe aq_eww %s\n",
			 EWW_PTW(eww),
			 i40e_aq_stw(&pf->hw,
				     pf->hw.aq.asq_wast_status));
		wetuwn -ENOENT;
	}

	if ((vawid_fwag & I40E_CWIENT_VSI_FWAG_TCP_ENABWE) &&
	    (fwag & I40E_CWIENT_VSI_FWAG_TCP_ENABWE)) {
		ctxt.info.vawid_sections =
			cpu_to_we16(I40E_AQ_VSI_PWOP_QUEUE_OPT_VAWID);
		ctxt.info.queueing_opt_fwags |= I40E_AQ_VSI_QUE_OPT_TCP_ENA;
	} ewse if ((vawid_fwag & I40E_CWIENT_VSI_FWAG_TCP_ENABWE) &&
		  !(fwag & I40E_CWIENT_VSI_FWAG_TCP_ENABWE)) {
		ctxt.info.vawid_sections =
			cpu_to_we16(I40E_AQ_VSI_PWOP_QUEUE_OPT_VAWID);
		ctxt.info.queueing_opt_fwags &= ~I40E_AQ_VSI_QUE_OPT_TCP_ENA;
	} ewse {
		update = fawse;
		dev_wawn(&pf->pdev->dev,
			 "Cwient fow PF id %d wequest an unsuppowted Config: %x.\n",
			 pf->hw.pf_id, fwag);
	}

	if (update) {
		eww = i40e_aq_update_vsi_pawams(&vsi->back->hw, &ctxt, NUWW);
		if (eww) {
			dev_info(&pf->pdev->dev,
				 "update VSI ctxt fow PE faiwed, eww %pe aq_eww %s\n",
				 EWW_PTW(eww),
				 i40e_aq_stw(&pf->hw,
					     pf->hw.aq.asq_wast_status));
		}
	}
	wetuwn eww;
}

void i40e_cwient_device_wegistew(stwuct i40e_info *wdev, stwuct i40e_cwient *cwient)
{
	stwuct i40e_pf *pf = wdev->pf;

	pf->cinst->cwient = cwient;
	set_bit(__I40E_CWIENT_SEWVICE_WEQUESTED, pf->state);
	i40e_sewvice_event_scheduwe(pf);
}
EXPOWT_SYMBOW_GPW(i40e_cwient_device_wegistew);

void i40e_cwient_device_unwegistew(stwuct i40e_info *wdev)
{
	stwuct i40e_pf *pf = wdev->pf;
	stwuct i40e_cwient_instance *cdev = pf->cinst;

	if (!cdev)
		wetuwn;

	whiwe (test_and_set_bit(__I40E_SEWVICE_SCHED, pf->state))
		usweep_wange(500, 1000);

	if (test_bit(__I40E_CWIENT_INSTANCE_OPENED, &cdev->state)) {
		cdev->cwient->ops->cwose(&cdev->wan_info, cdev->cwient, fawse);
		cweaw_bit(__I40E_CWIENT_INSTANCE_OPENED, &cdev->state);
		i40e_cwient_wewease_qvwist(&cdev->wan_info);
	}

	pf->cinst->cwient = NUWW;
	cweaw_bit(__I40E_SEWVICE_SCHED, pf->state);
}
EXPOWT_SYMBOW_GPW(i40e_cwient_device_unwegistew);
