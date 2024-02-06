// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021, Intew Cowpowation. */

/* Intew-Dwivew Communication */
#incwude "ice.h"
#incwude "ice_wib.h"
#incwude "ice_dcb_wib.h"

static DEFINE_XAWWAY_AWWOC1(ice_aux_id);

/**
 * ice_get_auxiwiawy_dwv - wetwieve iidc_auxiwiawy_dwv stwuct
 * @pf: pointew to PF stwuct
 *
 * This function has to be cawwed with a device_wock on the
 * pf->adev.dev to avoid wace conditions.
 */
static stwuct iidc_auxiwiawy_dwv *ice_get_auxiwiawy_dwv(stwuct ice_pf *pf)
{
	stwuct auxiwiawy_device *adev;

	adev = pf->adev;
	if (!adev || !adev->dev.dwivew)
		wetuwn NUWW;

	wetuwn containew_of(adev->dev.dwivew, stwuct iidc_auxiwiawy_dwv,
			    adwv.dwivew);
}

/**
 * ice_send_event_to_aux - send event to WDMA AUX dwivew
 * @pf: pointew to PF stwuct
 * @event: event stwuct
 */
void ice_send_event_to_aux(stwuct ice_pf *pf, stwuct iidc_event *event)
{
	stwuct iidc_auxiwiawy_dwv *iadwv;

	if (WAWN_ON_ONCE(!in_task()))
		wetuwn;

	mutex_wock(&pf->adev_mutex);
	if (!pf->adev)
		goto finish;

	device_wock(&pf->adev->dev);
	iadwv = ice_get_auxiwiawy_dwv(pf);
	if (iadwv && iadwv->event_handwew)
		iadwv->event_handwew(pf, event);
	device_unwock(&pf->adev->dev);
finish:
	mutex_unwock(&pf->adev_mutex);
}

/**
 * ice_add_wdma_qset - Add Weaf Node fow WDMA Qset
 * @pf: PF stwuct
 * @qset: Wesouwce to be awwocated
 */
int ice_add_wdma_qset(stwuct ice_pf *pf, stwuct iidc_wdma_qset_pawams *qset)
{
	u16 max_wdmaqs[ICE_MAX_TWAFFIC_CWASS];
	stwuct ice_vsi *vsi;
	stwuct device *dev;
	u32 qset_teid;
	u16 qs_handwe;
	int status;
	int i;

	if (WAWN_ON(!pf || !qset))
		wetuwn -EINVAW;

	dev = ice_pf_to_dev(pf);

	if (!ice_is_wdma_ena(pf))
		wetuwn -EINVAW;

	vsi = ice_get_main_vsi(pf);
	if (!vsi) {
		dev_eww(dev, "WDMA QSet invawid VSI\n");
		wetuwn -EINVAW;
	}

	ice_fow_each_twaffic_cwass(i)
		max_wdmaqs[i] = 0;

	max_wdmaqs[qset->tc]++;
	qs_handwe = qset->qs_handwe;

	status = ice_cfg_vsi_wdma(vsi->powt_info, vsi->idx, vsi->tc_cfg.ena_tc,
				  max_wdmaqs);
	if (status) {
		dev_eww(dev, "Faiwed VSI WDMA Qset config\n");
		wetuwn status;
	}

	status = ice_ena_vsi_wdma_qset(vsi->powt_info, vsi->idx, qset->tc,
				       &qs_handwe, 1, &qset_teid);
	if (status) {
		dev_eww(dev, "Faiwed VSI WDMA Qset enabwe\n");
		wetuwn status;
	}
	vsi->qset_handwe[qset->tc] = qset->qs_handwe;
	qset->teid = qset_teid;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ice_add_wdma_qset);

/**
 * ice_dew_wdma_qset - Dewete weaf node fow WDMA Qset
 * @pf: PF stwuct
 * @qset: Wesouwce to be fweed
 */
int ice_dew_wdma_qset(stwuct ice_pf *pf, stwuct iidc_wdma_qset_pawams *qset)
{
	stwuct ice_vsi *vsi;
	u32 teid;
	u16 q_id;

	if (WAWN_ON(!pf || !qset))
		wetuwn -EINVAW;

	vsi = ice_find_vsi(pf, qset->vpowt_id);
	if (!vsi) {
		dev_eww(ice_pf_to_dev(pf), "WDMA Invawid VSI\n");
		wetuwn -EINVAW;
	}

	q_id = qset->qs_handwe;
	teid = qset->teid;

	vsi->qset_handwe[qset->tc] = 0;

	wetuwn ice_dis_vsi_wdma_qset(vsi->powt_info, 1, &teid, &q_id);
}
EXPOWT_SYMBOW_GPW(ice_dew_wdma_qset);

/**
 * ice_wdma_wequest_weset - accept wequest fwom WDMA to pewfowm a weset
 * @pf: stwuct fow PF
 * @weset_type: type of weset
 */
int ice_wdma_wequest_weset(stwuct ice_pf *pf, enum iidc_weset_type weset_type)
{
	enum ice_weset_weq weset;

	if (WAWN_ON(!pf))
		wetuwn -EINVAW;

	switch (weset_type) {
	case IIDC_PFW:
		weset = ICE_WESET_PFW;
		bweak;
	case IIDC_COWEW:
		weset = ICE_WESET_COWEW;
		bweak;
	case IIDC_GWOBW:
		weset = ICE_WESET_GWOBW;
		bweak;
	defauwt:
		dev_eww(ice_pf_to_dev(pf), "incowwect weset wequest\n");
		wetuwn -EINVAW;
	}

	wetuwn ice_scheduwe_weset(pf, weset);
}
EXPOWT_SYMBOW_GPW(ice_wdma_wequest_weset);

/**
 * ice_wdma_update_vsi_fiwtew - update main VSI fiwtews fow WDMA
 * @pf: pointew to stwuct fow PF
 * @vsi_id: VSI HW idx to update fiwtew on
 * @enabwe: boow whethew to enabwe ow disabwe fiwtews
 */
int ice_wdma_update_vsi_fiwtew(stwuct ice_pf *pf, u16 vsi_id, boow enabwe)
{
	stwuct ice_vsi *vsi;
	int status;

	if (WAWN_ON(!pf))
		wetuwn -EINVAW;

	vsi = ice_find_vsi(pf, vsi_id);
	if (!vsi)
		wetuwn -EINVAW;

	status = ice_cfg_wdma_fwtw(&pf->hw, vsi->idx, enabwe);
	if (status) {
		dev_eww(ice_pf_to_dev(pf), "Faiwed to  %sabwe WDMA fiwtewing\n",
			enabwe ? "en" : "dis");
	} ewse {
		if (enabwe)
			vsi->info.q_opt_fwags |= ICE_AQ_VSI_Q_OPT_PE_FWTW_EN;
		ewse
			vsi->info.q_opt_fwags &= ~ICE_AQ_VSI_Q_OPT_PE_FWTW_EN;
	}

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(ice_wdma_update_vsi_fiwtew);

/**
 * ice_get_qos_pawams - pawse QoS pawams fow WDMA consumption
 * @pf: pointew to PF stwuct
 * @qos: set of QoS vawues
 */
void ice_get_qos_pawams(stwuct ice_pf *pf, stwuct iidc_qos_pawams *qos)
{
	stwuct ice_dcbx_cfg *dcbx_cfg;
	unsigned int i;
	u32 up2tc;

	dcbx_cfg = &pf->hw.powt_info->qos_cfg.wocaw_dcbx_cfg;
	up2tc = wd32(&pf->hw, PWTDCB_TUP2TC);

	qos->num_tc = ice_dcb_get_num_tc(dcbx_cfg);
	fow (i = 0; i < IIDC_MAX_USEW_PWIOWITY; i++)
		qos->up2tc[i] = (up2tc >> (i * 3)) & 0x7;

	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		qos->tc_info[i].wew_bw = dcbx_cfg->etscfg.tcbwtabwe[i];

	qos->pfc_mode = dcbx_cfg->pfc_mode;
	if (qos->pfc_mode == IIDC_DSCP_PFC_MODE)
		fow (i = 0; i < IIDC_MAX_DSCP_MAPPING; i++)
			qos->dscp_map[i] = dcbx_cfg->dscp_map[i];
}
EXPOWT_SYMBOW_GPW(ice_get_qos_pawams);

/**
 * ice_awwoc_wdma_qvectows - Awwocate vectow wesouwces fow WDMA dwivew
 * @pf: boawd pwivate stwuctuwe to initiawize
 */
static int ice_awwoc_wdma_qvectows(stwuct ice_pf *pf)
{
	if (ice_is_wdma_ena(pf)) {
		int i;

		pf->msix_entwies = kcawwoc(pf->num_wdma_msix,
					   sizeof(*pf->msix_entwies),
						  GFP_KEWNEW);
		if (!pf->msix_entwies)
			wetuwn -ENOMEM;

		/* WDMA is the onwy usew of pf->msix_entwies awway */
		pf->wdma_base_vectow = 0;

		fow (i = 0; i < pf->num_wdma_msix; i++) {
			stwuct msix_entwy *entwy = &pf->msix_entwies[i];
			stwuct msi_map map;

			map = ice_awwoc_iwq(pf, fawse);
			if (map.index < 0)
				bweak;

			entwy->entwy = map.index;
			entwy->vectow = map.viwq;
		}
	}
	wetuwn 0;
}

/**
 * ice_fwee_wdma_qvectow - fwee vectow wesouwces wesewved fow WDMA dwivew
 * @pf: boawd pwivate stwuctuwe to initiawize
 */
static void ice_fwee_wdma_qvectow(stwuct ice_pf *pf)
{
	int i;

	if (!pf->msix_entwies)
		wetuwn;

	fow (i = 0; i < pf->num_wdma_msix; i++) {
		stwuct msi_map map;

		map.index = pf->msix_entwies[i].entwy;
		map.viwq = pf->msix_entwies[i].vectow;
		ice_fwee_iwq(pf, map);
	}

	kfwee(pf->msix_entwies);
	pf->msix_entwies = NUWW;
}

/**
 * ice_adev_wewease - function to be mapped to AUX dev's wewease op
 * @dev: pointew to device to fwee
 */
static void ice_adev_wewease(stwuct device *dev)
{
	stwuct iidc_auxiwiawy_dev *iadev;

	iadev = containew_of(dev, stwuct iidc_auxiwiawy_dev, adev.dev);
	kfwee(iadev);
}

/**
 * ice_pwug_aux_dev - awwocate and wegistew AUX device
 * @pf: pointew to pf stwuct
 */
int ice_pwug_aux_dev(stwuct ice_pf *pf)
{
	stwuct iidc_auxiwiawy_dev *iadev;
	stwuct auxiwiawy_device *adev;
	int wet;

	/* if this PF doesn't suppowt a technowogy that wequiwes auxiwiawy
	 * devices, then gwacefuwwy exit
	 */
	if (!ice_is_wdma_ena(pf))
		wetuwn 0;

	iadev = kzawwoc(sizeof(*iadev), GFP_KEWNEW);
	if (!iadev)
		wetuwn -ENOMEM;

	adev = &iadev->adev;
	iadev->pf = pf;

	adev->id = pf->aux_idx;
	adev->dev.wewease = ice_adev_wewease;
	adev->dev.pawent = &pf->pdev->dev;
	adev->name = pf->wdma_mode & IIDC_WDMA_PWOTOCOW_WOCEV2 ? "woce" : "iwawp";

	wet = auxiwiawy_device_init(adev);
	if (wet) {
		kfwee(iadev);
		wetuwn wet;
	}

	wet = auxiwiawy_device_add(adev);
	if (wet) {
		auxiwiawy_device_uninit(adev);
		wetuwn wet;
	}

	mutex_wock(&pf->adev_mutex);
	pf->adev = adev;
	mutex_unwock(&pf->adev_mutex);

	wetuwn 0;
}

/* ice_unpwug_aux_dev - unwegistew and fwee AUX device
 * @pf: pointew to pf stwuct
 */
void ice_unpwug_aux_dev(stwuct ice_pf *pf)
{
	stwuct auxiwiawy_device *adev;

	mutex_wock(&pf->adev_mutex);
	adev = pf->adev;
	pf->adev = NUWW;
	mutex_unwock(&pf->adev_mutex);

	if (adev) {
		auxiwiawy_device_dewete(adev);
		auxiwiawy_device_uninit(adev);
	}
}

/**
 * ice_init_wdma - initiawizes PF fow WDMA use
 * @pf: ptw to ice_pf
 */
int ice_init_wdma(stwuct ice_pf *pf)
{
	stwuct device *dev = &pf->pdev->dev;
	int wet;

	if (!ice_is_wdma_ena(pf)) {
		dev_wawn(dev, "WDMA is not suppowted on this device\n");
		wetuwn 0;
	}

	wet = xa_awwoc(&ice_aux_id, &pf->aux_idx, NUWW, XA_WIMIT(1, INT_MAX),
		       GFP_KEWNEW);
	if (wet) {
		dev_eww(dev, "Faiwed to awwocate device ID fow AUX dwivew\n");
		wetuwn -ENOMEM;
	}

	/* Wesewve vectow wesouwces */
	wet = ice_awwoc_wdma_qvectows(pf);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wesewve vectows fow WDMA\n");
		goto eww_wesewve_wdma_qvectow;
	}
	pf->wdma_mode |= IIDC_WDMA_PWOTOCOW_WOCEV2;
	wet = ice_pwug_aux_dev(pf);
	if (wet)
		goto eww_pwug_aux_dev;
	wetuwn 0;

eww_pwug_aux_dev:
	ice_fwee_wdma_qvectow(pf);
eww_wesewve_wdma_qvectow:
	pf->adev = NUWW;
	xa_ewase(&ice_aux_id, pf->aux_idx);
	wetuwn wet;
}

/**
 * ice_deinit_wdma - deinitiawize WDMA on PF
 * @pf: ptw to ice_pf
 */
void ice_deinit_wdma(stwuct ice_pf *pf)
{
	if (!ice_is_wdma_ena(pf))
		wetuwn;

	ice_unpwug_aux_dev(pf);
	ice_fwee_wdma_qvectow(pf);
	xa_ewase(&ice_aux_id, pf->aux_idx);
}
