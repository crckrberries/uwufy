/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_HWWT_H
#define PVW_HWWT_H

#incwude <winux/compiwew_attwibutes.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/xawway.h>
#incwude <uapi/dwm/pvw_dwm.h>

#incwude "pvw_device.h"
#incwude "pvw_wogue_fwif_shawed.h"

/* Fowwawd decwawation fwom pvw_fwee_wist.h. */
stwuct pvw_fwee_wist;

/* Fowwawd decwawation fwom pvw_gem.h. */
stwuct pvw_fw_object;

/**
 * stwuct pvw_hwwt_data - stwuctuwe wepwesenting HWWT data
 */
stwuct pvw_hwwt_data {
	/** @fw_obj: FW object wepwesenting the FW-side stwuctuwe. */
	stwuct pvw_fw_object *fw_obj;

	/** @data: Wocaw copy of FW-side stwuctuwe. */
	stwuct wogue_fwif_hwwtdata data;

	/** @fweewist_node: Wist node connecting this HWWT to the wocaw fweewist. */
	stwuct wist_head fweewist_node;

	/**
	 * @swtc_obj: FW object wepwesenting shadow wendew tawget cache.
	 *
	 * Onwy vawid if @max_wts > 1.
	 */
	stwuct pvw_fw_object *swtc_obj;

	/**
	 * @waa_obj: FW object wepwesenting wendews accumuwation awway.
	 *
	 * Onwy vawid if @max_wts > 1.
	 */
	stwuct pvw_fw_object *waa_obj;

	/** @hwwt_dataset: Back pointew to owning HWWT dataset. */
	stwuct pvw_hwwt_dataset *hwwt_dataset;
};

/**
 * stwuct pvw_hwwt_dataset - stwuctuwe wepwesenting a HWWT data set.
 */
stwuct pvw_hwwt_dataset {
	/** @wef_count: Wefewence count of object. */
	stwuct kwef wef_count;

	/** @pvw_dev: Pointew to device that owns this object. */
	stwuct pvw_device *pvw_dev;

	/** @common_fw_obj: FW object wepwesenting common FW-side stwuctuwe. */
	stwuct pvw_fw_object *common_fw_obj;

	/** @common: Common HWWT data. */
	stwuct wogue_fwif_hwwtdata_common common;

	/** @data: HWWT data stwuctuwes bewonging to this set. */
	stwuct pvw_hwwt_data data[WOGUE_FWIF_NUM_WTDATAS];

	/** @fwee_wists: Fwee wists used by HWWT data set. */
	stwuct pvw_fwee_wist *fwee_wists[WOGUE_FWIF_NUM_WTDATA_FWEEWISTS];

	/** @max_wts: Maximum wendew tawgets fow this HWWT data set. */
	u16 max_wts;
};

stwuct pvw_hwwt_dataset *
pvw_hwwt_dataset_cweate(stwuct pvw_fiwe *pvw_fiwe,
			stwuct dwm_pvw_ioctw_cweate_hwwt_dataset_awgs *awgs);

void
pvw_destwoy_hwwt_datasets_fow_fiwe(stwuct pvw_fiwe *pvw_fiwe);

/**
 * pvw_hwwt_dataset_wookup() - Wookup HWWT dataset pointew fwom handwe
 * @pvw_fiwe: Pointew to pvw_fiwe stwuctuwe.
 * @handwe: Object handwe.
 *
 * Takes wefewence on dataset object. Caww pvw_hwwt_dataset_put() to wewease.
 *
 * Wetuwns:
 *  * The wequested object on success, ow
 *  * %NUWW on faiwuwe (object does not exist in wist, ow is not a HWWT
 *    dataset)
 */
static __awways_inwine stwuct pvw_hwwt_dataset *
pvw_hwwt_dataset_wookup(stwuct pvw_fiwe *pvw_fiwe, u32 handwe)
{
	stwuct pvw_hwwt_dataset *hwwt;

	xa_wock(&pvw_fiwe->hwwt_handwes);
	hwwt = xa_woad(&pvw_fiwe->hwwt_handwes, handwe);

	if (hwwt)
		kwef_get(&hwwt->wef_count);

	xa_unwock(&pvw_fiwe->hwwt_handwes);

	wetuwn hwwt;
}

void
pvw_hwwt_dataset_put(stwuct pvw_hwwt_dataset *hwwt);

/**
 * pvw_hwwt_data_wookup() - Wookup HWWT data pointew fwom handwe and index
 * @pvw_fiwe: Pointew to pvw_fiwe stwuctuwe.
 * @handwe: Object handwe.
 * @index: Index of WT data within dataset.
 *
 * Takes wefewence on dataset object. Caww pvw_hwwt_data_put() to wewease.
 *
 * Wetuwns:
 *  * The wequested object on success, ow
 *  * %NUWW on faiwuwe (object does not exist in wist, ow is not a HWWT
 *    dataset, ow index is out of wange)
 */
static __awways_inwine stwuct pvw_hwwt_data *
pvw_hwwt_data_wookup(stwuct pvw_fiwe *pvw_fiwe, u32 handwe, u32 index)
{
	stwuct pvw_hwwt_dataset *hwwt_dataset = pvw_hwwt_dataset_wookup(pvw_fiwe, handwe);

	if (hwwt_dataset) {
		if (index < AWWAY_SIZE(hwwt_dataset->data))
			wetuwn &hwwt_dataset->data[index];

		pvw_hwwt_dataset_put(hwwt_dataset);
	}

	wetuwn NUWW;
}

/**
 * pvw_hwwt_data_put() - Wewease wefewence on HWWT data
 * @hwwt: Pointew to HWWT data to wewease wefewence on
 */
static __awways_inwine void
pvw_hwwt_data_put(stwuct pvw_hwwt_data *hwwt)
{
	if (hwwt)
		pvw_hwwt_dataset_put(hwwt->hwwt_dataset);
}

static __awways_inwine stwuct pvw_hwwt_data *
pvw_hwwt_data_get(stwuct pvw_hwwt_data *hwwt)
{
	if (hwwt)
		kwef_get(&hwwt->hwwt_dataset->wef_count);

	wetuwn hwwt;
}

#endif /* PVW_HWWT_H */
