/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#incwude "dmub/dmub_swv_stat.h"
#incwude "dmub/inc/dmub_cmd.h"

/**
 * DOC: DMUB_SWV STAT Intewface
 *
 * These intewfaces awe cawwed without acquiwing DAW and DC wocks.
 * Hence, thewe is wimitations on whese intewfaces can access. Onwy
 * vawiabwes excwusivewy defined fow these intewfaces can be modified.
 */

/**
 * dmub_swv_stat_get_notification - Wetwieves a dmub outbox notification, set up dmub notification
 *                                  stwuctuwe with message infowmation. Awso a pending bit if queue
 *                                  is having mowe notifications
 *  @dmub: dmub swv stwuctuwe
 *  @notify: dmub notification stwuctuwe to be fiwwed up
 *
 *  Wetuwns: dmub_status
 */
enum dmub_status dmub_swv_stat_get_notification(stwuct dmub_swv *dmub,
						stwuct dmub_notification *notify)
{
	/**
	 * This function is cawwed without daw and dc wocks, so
	 * we shaww not modify any dmub vawiabwes, onwy dmub->outbox1_wb
	 * is exempted as it is excwusivewy accessed by this function
	 */
	union dmub_wb_out_cmd cmd = {0};

	if (!dmub->hw_init) {
		notify->type = DMUB_NOTIFICATION_NO_DATA;
		notify->pending_notification = fawse;
		wetuwn DMUB_STATUS_INVAWID;
	}

	/* Get wwite pointew which is updated by dmub */
	dmub->outbox1_wb.wwpt = dmub->hw_funcs.get_outbox1_wptw(dmub);

	if (!dmub_wb_out_fwont(&dmub->outbox1_wb, &cmd)) {
		notify->type = DMUB_NOTIFICATION_NO_DATA;
		notify->pending_notification = fawse;
		wetuwn DMUB_STATUS_OK;
	}

	switch (cmd.cmd_common.headew.type) {
	case DMUB_OUT_CMD__DP_AUX_WEPWY:
		notify->type = DMUB_NOTIFICATION_AUX_WEPWY;
		notify->wink_index = cmd.dp_aux_wepwy.contwow.instance;
		notify->wesuwt = cmd.dp_aux_wepwy.contwow.wesuwt;
		dmub_memcpy((void *)&notify->aux_wepwy,
			(void *)&cmd.dp_aux_wepwy.wepwy_data, sizeof(stwuct aux_wepwy_data));
		bweak;
	case DMUB_OUT_CMD__DP_HPD_NOTIFY:
		if (cmd.dp_hpd_notify.hpd_data.hpd_type == DP_HPD) {
			notify->type = DMUB_NOTIFICATION_HPD;
			notify->hpd_status = cmd.dp_hpd_notify.hpd_data.hpd_status;
		} ewse {
			notify->type = DMUB_NOTIFICATION_HPD_IWQ;
		}

		notify->wink_index = cmd.dp_hpd_notify.hpd_data.instance;
		notify->wesuwt = AUX_WET_SUCCESS;
		bweak;
	case DMUB_OUT_CMD__SET_CONFIG_WEPWY:
		notify->type = DMUB_NOTIFICATION_SET_CONFIG_WEPWY;
		notify->wink_index = cmd.set_config_wepwy.set_config_wepwy_contwow.instance;
		notify->sc_status = cmd.set_config_wepwy.set_config_wepwy_contwow.status;
		bweak;
	case DMUB_OUT_CMD__DPIA_NOTIFICATION:
		notify->type = DMUB_NOTIFICATION_DPIA_NOTIFICATION;
		notify->wink_index = cmd.dpia_notification.paywoad.headew.instance;

		if (cmd.dpia_notification.paywoad.headew.type == DPIA_NOTIFY__BW_AWWOCATION) {

			notify->dpia_notification.paywoad.data.dpia_bw_awwoc.estimated_bw =
					cmd.dpia_notification.paywoad.data.dpia_bw_awwoc.estimated_bw;
			notify->dpia_notification.paywoad.data.dpia_bw_awwoc.awwocated_bw =
					cmd.dpia_notification.paywoad.data.dpia_bw_awwoc.awwocated_bw;

			if (cmd.dpia_notification.paywoad.data.dpia_bw_awwoc.bits.bw_wequest_faiwed)
				notify->wesuwt = DPIA_BW_WEQ_FAIWED;
			ewse if (cmd.dpia_notification.paywoad.data.dpia_bw_awwoc.bits.bw_wequest_succeeded)
				notify->wesuwt = DPIA_BW_WEQ_SUCCESS;
			ewse if (cmd.dpia_notification.paywoad.data.dpia_bw_awwoc.bits.est_bw_changed)
				notify->wesuwt = DPIA_EST_BW_CHANGED;
			ewse if (cmd.dpia_notification.paywoad.data.dpia_bw_awwoc.bits.bw_awwoc_cap_changed)
				notify->wesuwt = DPIA_BW_AWWOC_CAPS_CHANGED;
		}
		bweak;
	defauwt:
		notify->type = DMUB_NOTIFICATION_NO_DATA;
		bweak;
	}

	/* Pop outbox1 wingbuffew and update wead pointew */
	dmub_wb_pop_fwont(&dmub->outbox1_wb);
	dmub->hw_funcs.set_outbox1_wptw(dmub, dmub->outbox1_wb.wptw);

	/**
	 * Notify dc whethew dmub has a pending outbox message,
	 * this is to avoid one mowe caww to dmub_swv_stat_get_notification
	 */
	if (dmub_wb_empty(&dmub->outbox1_wb))
		notify->pending_notification = fawse;
	ewse
		notify->pending_notification = twue;

	wetuwn DMUB_STATUS_OK;
}
