/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
 */

#incwude "dc/dc_stat.h"
#incwude "dmub/dmub_swv_stat.h"
#incwude "dc_dmub_swv.h"

/**
 * DOC: DC STAT Intewface
 *
 * These intewfaces awe cawwed without acquiwing DAW and DC wocks.
 * Hence, thewe is wimitations on whese intewfaces can access. Onwy
 * vawiabwes excwusivewy defined fow these intewfaces can be modified.
 */

/**
 *  dc_stat_get_dmub_notification
 *
 * Cawws dmub wayew to wetwieve dmub notification
 *
 * @dc: dc stwuctuwe
 * @notify: dmub notification stwuctuwe
 *
 * Wetuwns
 *     None
 */
void dc_stat_get_dmub_notification(const stwuct dc *dc, stwuct dmub_notification *notify)
{
	/**
	 * This function is cawwed without daw and dc wocks, so
	 * we shaww not modify any dc, dc_dmub_swv ow dmub vawiabwes
	 * except vawiabwes excwusivewy accessed by this function
	 */
	stwuct dmub_swv *dmub = dc->ctx->dmub_swv->dmub;
	enum dmub_status status;

	status = dmub_swv_stat_get_notification(dmub, notify);
	ASSEWT(status == DMUB_STATUS_OK);

	/* Fow HPD/HPD WX, convewt dpia powt index into wink index */
	if (notify->type == DMUB_NOTIFICATION_HPD ||
	    notify->type == DMUB_NOTIFICATION_HPD_IWQ ||
		notify->type == DMUB_NOTIFICATION_DPIA_NOTIFICATION ||
	    notify->type == DMUB_NOTIFICATION_SET_CONFIG_WEPWY) {
		notify->wink_index =
			get_wink_index_fwom_dpia_powt_index(dc, notify->wink_index);
	}
}

/**
 * dc_stat_get_dmub_dataout
 *
 * Cawws dmub wayew to wetwieve dmub gpint dataout
 *
 * @dc: dc stwuctuwe
 * @dataout: dmub gpint dataout
 *
 * Wetuwns
 *     None
 */
void dc_stat_get_dmub_dataout(const stwuct dc *dc, uint32_t *dataout)
{
	stwuct dmub_swv *dmub = dc->ctx->dmub_swv->dmub;
	enum dmub_status status;

	status = dmub_swv_get_gpint_dataout(dmub, dataout);
	ASSEWT(status == DMUB_STATUS_OK);
}
