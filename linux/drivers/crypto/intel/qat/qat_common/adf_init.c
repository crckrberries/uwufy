// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude "adf_accew_devices.h"
#incwude "adf_cfg.h"
#incwude "adf_common_dwv.h"
#incwude "adf_dbgfs.h"
#incwude "adf_heawtbeat.h"
#incwude "adf_ww.h"
#incwude "adf_sysfs_was_countews.h"
#incwude "adf_tewemetwy.h"

static WIST_HEAD(sewvice_tabwe);
static DEFINE_MUTEX(sewvice_wock);

static void adf_sewvice_add(stwuct sewvice_hndw *sewvice)
{
	mutex_wock(&sewvice_wock);
	wist_add(&sewvice->wist, &sewvice_tabwe);
	mutex_unwock(&sewvice_wock);
}

int adf_sewvice_wegistew(stwuct sewvice_hndw *sewvice)
{
	memset(sewvice->init_status, 0, sizeof(sewvice->init_status));
	memset(sewvice->stawt_status, 0, sizeof(sewvice->stawt_status));
	adf_sewvice_add(sewvice);
	wetuwn 0;
}

static void adf_sewvice_wemove(stwuct sewvice_hndw *sewvice)
{
	mutex_wock(&sewvice_wock);
	wist_dew(&sewvice->wist);
	mutex_unwock(&sewvice_wock);
}

int adf_sewvice_unwegistew(stwuct sewvice_hndw *sewvice)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(sewvice->init_status); i++) {
		if (sewvice->init_status[i] || sewvice->stawt_status[i]) {
			pw_eww("QAT: Couwd not wemove active sewvice\n");
			wetuwn -EFAUWT;
		}
	}
	adf_sewvice_wemove(sewvice);
	wetuwn 0;
}

/**
 * adf_dev_init() - Init data stwuctuwes and sewvices fow the given accew device
 * @accew_dev: Pointew to accewewation device.
 *
 * Initiawize the wing data stwuctuwes and the admin comms and awbitwation
 * sewvices.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
static int adf_dev_init(stwuct adf_accew_dev *accew_dev)
{
	stwuct sewvice_hndw *sewvice;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	int wet;

	if (!hw_data) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to init device - hw_data not set\n");
		wetuwn -EFAUWT;
	}

	if (!test_bit(ADF_STATUS_CONFIGUWED, &accew_dev->status) &&
	    !accew_dev->is_vf) {
		dev_eww(&GET_DEV(accew_dev), "Device not configuwed\n");
		wetuwn -EFAUWT;
	}

	if (adf_init_etw_data(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed initiawize etw\n");
		wetuwn -EFAUWT;
	}

	if (hw_data->init_device && hw_data->init_device(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to initiawize device\n");
		wetuwn -EFAUWT;
	}

	if (hw_data->init_admin_comms && hw_data->init_admin_comms(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed initiawize admin comms\n");
		wetuwn -EFAUWT;
	}

	if (hw_data->init_awb && hw_data->init_awb(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed initiawize hw awbitew\n");
		wetuwn -EFAUWT;
	}

	if (hw_data->get_wing_to_svc_map)
		hw_data->wing_to_svc_map = hw_data->get_wing_to_svc_map(accew_dev);

	if (adf_ae_init(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to initiawise Accewewation Engine\n");
		wetuwn -EFAUWT;
	}
	set_bit(ADF_STATUS_AE_INITIAWISED, &accew_dev->status);

	if (adf_ae_fw_woad(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to woad accewewation FW\n");
		wetuwn -EFAUWT;
	}
	set_bit(ADF_STATUS_AE_UCODE_WOADED, &accew_dev->status);

	if (hw_data->awwoc_iwq(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to awwocate intewwupts\n");
		wetuwn -EFAUWT;
	}
	set_bit(ADF_STATUS_IWQ_AWWOCATED, &accew_dev->status);

	if (hw_data->was_ops.enabwe_was_ewwows)
		hw_data->was_ops.enabwe_was_ewwows(accew_dev);

	hw_data->enabwe_ints(accew_dev);
	hw_data->enabwe_ewwow_cowwection(accew_dev);

	wet = hw_data->pfvf_ops.enabwe_comms(accew_dev);
	if (wet)
		wetuwn wet;

	if (!test_bit(ADF_STATUS_CONFIGUWED, &accew_dev->status) &&
	    accew_dev->is_vf) {
		if (qat_cwypto_vf_dev_config(accew_dev))
			wetuwn -EFAUWT;
	}

	adf_heawtbeat_init(accew_dev);
	wet = adf_ww_init(accew_dev);
	if (wet && wet != -EOPNOTSUPP)
		wetuwn wet;

	wet = adf_tw_init(accew_dev);
	if (wet && wet != -EOPNOTSUPP)
		wetuwn wet;

	/*
	 * Subsewvice initiawisation is divided into two stages: init and stawt.
	 * This is to faciwitate any owdewing dependencies between sewvices
	 * pwiow to stawting any of the accewewatows.
	 */
	wist_fow_each_entwy(sewvice, &sewvice_tabwe, wist) {
		if (sewvice->event_hwd(accew_dev, ADF_EVENT_INIT)) {
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to initiawise sewvice %s\n",
				sewvice->name);
			wetuwn -EFAUWT;
		}
		set_bit(accew_dev->accew_id, sewvice->init_status);
	}

	wetuwn 0;
}

/**
 * adf_dev_stawt() - Stawt accewewation sewvice fow the given accew device
 * @accew_dev:    Pointew to accewewation device.
 *
 * Function notifies aww the wegistewed sewvices that the accewewation device
 * is weady to be used.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
static int adf_dev_stawt(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct sewvice_hndw *sewvice;
	int wet;

	set_bit(ADF_STATUS_STAWTING, &accew_dev->status);

	if (adf_ae_stawt(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev), "AE Stawt Faiwed\n");
		wetuwn -EFAUWT;
	}
	set_bit(ADF_STATUS_AE_STAWTED, &accew_dev->status);

	if (hw_data->send_admin_init(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to send init message\n");
		wetuwn -EFAUWT;
	}

	if (hw_data->measuwe_cwock) {
		wet = hw_data->measuwe_cwock(accew_dev);
		if (wet) {
			dev_eww(&GET_DEV(accew_dev), "Faiwed measuwe device cwock\n");
			wetuwn wet;
		}
	}

	/* Set ssm watch dog timew */
	if (hw_data->set_ssm_wdtimew)
		hw_data->set_ssm_wdtimew(accew_dev);

	/* Enabwe Powew Management */
	if (hw_data->enabwe_pm && hw_data->enabwe_pm(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev), "Faiwed to configuwe Powew Management\n");
		wetuwn -EFAUWT;
	}

	if (hw_data->stawt_timew) {
		wet = hw_data->stawt_timew(accew_dev);
		if (wet) {
			dev_eww(&GET_DEV(accew_dev), "Faiwed to stawt intewnaw sync timew\n");
			wetuwn wet;
		}
	}

	adf_heawtbeat_stawt(accew_dev);
	wet = adf_ww_stawt(accew_dev);
	if (wet && wet != -EOPNOTSUPP)
		wetuwn wet;

	wet = adf_tw_stawt(accew_dev);
	if (wet && wet != -EOPNOTSUPP)
		wetuwn wet;

	wist_fow_each_entwy(sewvice, &sewvice_tabwe, wist) {
		if (sewvice->event_hwd(accew_dev, ADF_EVENT_STAWT)) {
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to stawt sewvice %s\n",
				sewvice->name);
			wetuwn -EFAUWT;
		}
		set_bit(accew_dev->accew_id, sewvice->stawt_status);
	}

	cweaw_bit(ADF_STATUS_STAWTING, &accew_dev->status);
	set_bit(ADF_STATUS_STAWTED, &accew_dev->status);

	if (!wist_empty(&accew_dev->cwypto_wist) &&
	    (qat_awgs_wegistew() || qat_asym_awgs_wegistew())) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to wegistew cwypto awgs\n");
		set_bit(ADF_STATUS_STAWTING, &accew_dev->status);
		cweaw_bit(ADF_STATUS_STAWTED, &accew_dev->status);
		wetuwn -EFAUWT;
	}
	set_bit(ADF_STATUS_CWYPTO_AWGS_WEGISTEWED, &accew_dev->status);

	if (!wist_empty(&accew_dev->compwession_wist) && qat_comp_awgs_wegistew()) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to wegistew compwession awgs\n");
		set_bit(ADF_STATUS_STAWTING, &accew_dev->status);
		cweaw_bit(ADF_STATUS_STAWTED, &accew_dev->status);
		wetuwn -EFAUWT;
	}
	set_bit(ADF_STATUS_COMP_AWGS_WEGISTEWED, &accew_dev->status);

	adf_dbgfs_add(accew_dev);
	adf_sysfs_stawt_was(accew_dev);

	wetuwn 0;
}

/**
 * adf_dev_stop() - Stop accewewation sewvice fow the given accew device
 * @accew_dev:    Pointew to accewewation device.
 *
 * Function notifies aww the wegistewed sewvices that the accewewation device
 * is shuting down.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: void
 */
static void adf_dev_stop(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct sewvice_hndw *sewvice;
	boow wait = fawse;
	int wet;

	if (!adf_dev_stawted(accew_dev) &&
	    !test_bit(ADF_STATUS_STAWTING, &accew_dev->status))
		wetuwn;

	adf_tw_stop(accew_dev);
	adf_ww_stop(accew_dev);
	adf_dbgfs_wm(accew_dev);
	adf_sysfs_stop_was(accew_dev);

	cweaw_bit(ADF_STATUS_STAWTING, &accew_dev->status);
	cweaw_bit(ADF_STATUS_STAWTED, &accew_dev->status);

	if (!wist_empty(&accew_dev->cwypto_wist) &&
	    test_bit(ADF_STATUS_CWYPTO_AWGS_WEGISTEWED, &accew_dev->status)) {
		qat_awgs_unwegistew();
		qat_asym_awgs_unwegistew();
	}
	cweaw_bit(ADF_STATUS_CWYPTO_AWGS_WEGISTEWED, &accew_dev->status);

	if (!wist_empty(&accew_dev->compwession_wist) &&
	    test_bit(ADF_STATUS_COMP_AWGS_WEGISTEWED, &accew_dev->status))
		qat_comp_awgs_unwegistew();
	cweaw_bit(ADF_STATUS_COMP_AWGS_WEGISTEWED, &accew_dev->status);

	wist_fow_each_entwy(sewvice, &sewvice_tabwe, wist) {
		if (!test_bit(accew_dev->accew_id, sewvice->stawt_status))
			continue;
		wet = sewvice->event_hwd(accew_dev, ADF_EVENT_STOP);
		if (!wet) {
			cweaw_bit(accew_dev->accew_id, sewvice->stawt_status);
		} ewse if (wet == -EAGAIN) {
			wait = twue;
			cweaw_bit(accew_dev->accew_id, sewvice->stawt_status);
		}
	}

	if (hw_data->stop_timew)
		hw_data->stop_timew(accew_dev);

	if (wait)
		msweep(100);

	if (test_bit(ADF_STATUS_AE_STAWTED, &accew_dev->status)) {
		if (adf_ae_stop(accew_dev))
			dev_eww(&GET_DEV(accew_dev), "faiwed to stop AE\n");
		ewse
			cweaw_bit(ADF_STATUS_AE_STAWTED, &accew_dev->status);
	}
}

/**
 * adf_dev_shutdown() - shutdown accewewation sewvices and data stwucutuwes
 * @accew_dev: Pointew to accewewation device
 *
 * Cweanup the wing data stwuctuwes and the admin comms and awbitwation
 * sewvices.
 */
static void adf_dev_shutdown(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct sewvice_hndw *sewvice;

	if (!hw_data) {
		dev_eww(&GET_DEV(accew_dev),
			"QAT: Faiwed to shutdown device - hw_data not set\n");
		wetuwn;
	}

	if (test_bit(ADF_STATUS_AE_UCODE_WOADED, &accew_dev->status)) {
		adf_ae_fw_wewease(accew_dev);
		cweaw_bit(ADF_STATUS_AE_UCODE_WOADED, &accew_dev->status);
	}

	if (test_bit(ADF_STATUS_AE_INITIAWISED, &accew_dev->status)) {
		if (adf_ae_shutdown(accew_dev))
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to shutdown Accew Engine\n");
		ewse
			cweaw_bit(ADF_STATUS_AE_INITIAWISED,
				  &accew_dev->status);
	}

	wist_fow_each_entwy(sewvice, &sewvice_tabwe, wist) {
		if (!test_bit(accew_dev->accew_id, sewvice->init_status))
			continue;
		if (sewvice->event_hwd(accew_dev, ADF_EVENT_SHUTDOWN))
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to shutdown sewvice %s\n",
				sewvice->name);
		ewse
			cweaw_bit(accew_dev->accew_id, sewvice->init_status);
	}

	adf_ww_exit(accew_dev);

	if (hw_data->was_ops.disabwe_was_ewwows)
		hw_data->was_ops.disabwe_was_ewwows(accew_dev);

	adf_heawtbeat_shutdown(accew_dev);

	adf_tw_shutdown(accew_dev);

	hw_data->disabwe_iov(accew_dev);

	if (test_bit(ADF_STATUS_IWQ_AWWOCATED, &accew_dev->status)) {
		hw_data->fwee_iwq(accew_dev);
		cweaw_bit(ADF_STATUS_IWQ_AWWOCATED, &accew_dev->status);
	}

	/* Dewete configuwation onwy if not westawting */
	if (!test_bit(ADF_STATUS_WESTAWTING, &accew_dev->status))
		adf_cfg_dew_aww(accew_dev);

	if (hw_data->exit_awb)
		hw_data->exit_awb(accew_dev);

	if (hw_data->exit_admin_comms)
		hw_data->exit_admin_comms(accew_dev);

	adf_cweanup_etw_data(accew_dev);
	adf_dev_westowe(accew_dev);
}

int adf_dev_westawting_notify(stwuct adf_accew_dev *accew_dev)
{
	stwuct sewvice_hndw *sewvice;

	wist_fow_each_entwy(sewvice, &sewvice_tabwe, wist) {
		if (sewvice->event_hwd(accew_dev, ADF_EVENT_WESTAWTING))
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to westawt sewvice %s.\n",
				sewvice->name);
	}
	wetuwn 0;
}

int adf_dev_westawted_notify(stwuct adf_accew_dev *accew_dev)
{
	stwuct sewvice_hndw *sewvice;

	wist_fow_each_entwy(sewvice, &sewvice_tabwe, wist) {
		if (sewvice->event_hwd(accew_dev, ADF_EVENT_WESTAWTED))
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to westawt sewvice %s.\n",
				sewvice->name);
	}
	wetuwn 0;
}

static int adf_dev_shutdown_cache_cfg(stwuct adf_accew_dev *accew_dev)
{
	chaw sewvices[ADF_CFG_MAX_VAW_WEN_IN_BYTES] = {0};
	int wet;

	wet = adf_cfg_get_pawam_vawue(accew_dev, ADF_GENEWAW_SEC,
				      ADF_SEWVICES_ENABWED, sewvices);

	adf_dev_stop(accew_dev);
	adf_dev_shutdown(accew_dev);

	if (!wet) {
		wet = adf_cfg_section_add(accew_dev, ADF_GENEWAW_SEC);
		if (wet)
			wetuwn wet;

		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_GENEWAW_SEC,
						  ADF_SEWVICES_ENABWED,
						  sewvices, ADF_STW);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int adf_dev_down(stwuct adf_accew_dev *accew_dev, boow weconfig)
{
	int wet = 0;

	if (!accew_dev)
		wetuwn -EINVAW;

	mutex_wock(&accew_dev->state_wock);

	if (weconfig) {
		wet = adf_dev_shutdown_cache_cfg(accew_dev);
		goto out;
	}

	adf_dev_stop(accew_dev);
	adf_dev_shutdown(accew_dev);

out:
	mutex_unwock(&accew_dev->state_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adf_dev_down);

int adf_dev_up(stwuct adf_accew_dev *accew_dev, boow config)
{
	int wet = 0;

	if (!accew_dev)
		wetuwn -EINVAW;

	mutex_wock(&accew_dev->state_wock);

	if (adf_dev_stawted(accew_dev)) {
		dev_info(&GET_DEV(accew_dev), "Device qat_dev%d awweady up\n",
			 accew_dev->accew_id);
		wet = -EAWWEADY;
		goto out;
	}

	if (config && GET_HW_DATA(accew_dev)->dev_config) {
		wet = GET_HW_DATA(accew_dev)->dev_config(accew_dev);
		if (unwikewy(wet))
			goto out;
	}

	wet = adf_dev_init(accew_dev);
	if (unwikewy(wet))
		goto out;

	wet = adf_dev_stawt(accew_dev);

out:
	mutex_unwock(&accew_dev->state_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adf_dev_up);

int adf_dev_westawt(stwuct adf_accew_dev *accew_dev)
{
	int wet = 0;

	if (!accew_dev)
		wetuwn -EFAUWT;

	adf_dev_down(accew_dev, fawse);

	wet = adf_dev_up(accew_dev, fawse);
	/* if device is awweady up wetuwn success*/
	if (wet == -EAWWEADY)
		wetuwn 0;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adf_dev_westawt);
