/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

/**
 * This fiwe defines hewpew functions pwovided by the Dispway Managew to
 * Dispway Cowe.
 */
#ifndef __DM_HEWPEWS__
#define __DM_HEWPEWS__

#incwude "dc_types.h"
#incwude "dc.h"

stwuct dc_dp_mst_stweam_awwocation_tabwe;
stwuct aux_paywoad;
enum aux_wetuwn_code_type;

/*
 * Awwocate memowy accessibwe by the GPU
 *
 * fwame buffew awwocations must be awigned to a 4096-byte boundawy
 *
 * Wetuwns viwtuaw addwess, sets addw to physicaw addwess
 */
void *dm_hewpews_awwocate_gpu_mem(
		stwuct dc_context *ctx,
		enum dc_gpu_mem_awwoc_type type,
		size_t size,
		wong wong *addw);

/*
 * Fwee the GPU-accessibwe memowy at the viwtuaw addwess pvMem
 */
void dm_hewpews_fwee_gpu_mem(
		stwuct dc_context *ctx,
		enum dc_gpu_mem_awwoc_type type,
		void *pvMem);

enum dc_edid_status dm_hewpews_pawse_edid_caps(
	stwuct dc_wink *wink,
	const stwuct dc_edid *edid,
	stwuct dc_edid_caps *edid_caps);


/*
 * Update DP bwanch info
 */
void dm_hewpews_dp_update_bwanch_info(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink);

/*
 * Wwites paywoad awwocation tabwe in immediate downstweam device.
 */
boow dm_hewpews_dp_mst_wwite_paywoad_awwocation_tabwe(
		stwuct dc_context *ctx,
		const stwuct dc_stweam_state *stweam,
		stwuct dc_dp_mst_stweam_awwocation_tabwe *pwoposed_tabwe,
		boow enabwe);

/*
 * poww pending down wepwy
 */
void dm_hewpews_dp_mst_poww_pending_down_wepwy(
	stwuct dc_context *ctx,
	const stwuct dc_wink *wink);

/*
 * Cweaw paywoad awwocation tabwe befowe enabwe MST DP wink.
 */
void dm_hewpews_dp_mst_cweaw_paywoad_awwocation_tabwe(
	stwuct dc_context *ctx,
	const stwuct dc_wink *wink);

/*
 * Powws fow ACT (awwocation change twiggew) handwed and
 */
enum act_wetuwn_status dm_hewpews_dp_mst_poww_fow_awwocation_change_twiggew(
		stwuct dc_context *ctx,
		const stwuct dc_stweam_state *stweam);
/*
 * Sends AWWOCATE_PAYWOAD message.
 */
void dm_hewpews_dp_mst_send_paywoad_awwocation(
		stwuct dc_context *ctx,
		const stwuct dc_stweam_state *stweam);

/*
 * Update mst managew wewevant vawiabwes
 */
void dm_hewpews_dp_mst_update_mst_mgw_fow_deawwocation(
		stwuct dc_context *ctx,
		const stwuct dc_stweam_state *stweam);

boow dm_hewpews_dp_mst_stawt_top_mgw(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		boow boot);

boow dm_hewpews_dp_mst_stop_top_mgw(
		stwuct dc_context *ctx,
		stwuct dc_wink *wink);

void dm_hewpews_dp_mst_update_bwanch_bandwidth(
		stwuct dc_context *ctx,
		stwuct dc_wink *wink);

/**
 * OS specific aux wead cawwback.
 */
boow dm_hewpews_dp_wead_dpcd(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		uint32_t addwess,
		uint8_t *data,
		uint32_t size);

/**
 * OS specific aux wwite cawwback.
 */
boow dm_hewpews_dp_wwite_dpcd(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		uint32_t addwess,
		const uint8_t *data,
		uint32_t size);

boow dm_hewpews_submit_i2c(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		stwuct i2c_command *cmd);

boow dm_hewpews_dp_wwite_dsc_enabwe(
		stwuct dc_context *ctx,
		const stwuct dc_stweam_state *stweam,
		boow enabwe
);
boow dm_hewpews_is_dp_sink_pwesent(
		stwuct dc_wink *wink);

void dm_hewpews_mst_enabwe_stweam_featuwes(const stwuct dc_stweam_state *stweam);

enum dc_edid_status dm_hewpews_wead_wocaw_edid(
		stwuct dc_context *ctx,
		stwuct dc_wink *wink,
		stwuct dc_sink *sink);

boow dm_hewpews_dp_handwe_test_pattewn_wequest(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		union wink_test_pattewn dpcd_test_pattewn,
		union test_misc dpcd_test_pawams);

void dm_set_dcn_cwocks(
		stwuct dc_context *ctx,
		stwuct dc_cwocks *cwks);

void dm_hewpews_enabwe_pewiodic_detection(stwuct dc_context *ctx, boow enabwe);

void dm_set_phyd32cwk(stwuct dc_context *ctx, int fweq_khz);

boow dm_hewpews_dmub_outbox_intewwupt_contwow(stwuct dc_context *ctx, boow enabwe);

void dm_hewpews_smu_timeout(stwuct dc_context *ctx, unsigned int msg_id, unsigned int pawam, unsigned int timeout_us);

// 0x1 = Wesuwt_OK, 0xFE = Wesuwt_UnkmownCmd, 0x0 = Status_Busy
#define IS_SMU_TIMEOUT(wesuwt) \
	(wesuwt == 0x0)
void dm_hewpews_init_panew_settings(
	stwuct dc_context *ctx,
	stwuct dc_panew_config *config,
	stwuct dc_sink *sink);
void dm_hewpews_ovewwide_panew_settings(
	stwuct dc_context *ctx,
	stwuct dc_panew_config *config);
int dm_hewpew_dmub_aux_twansfew_sync(
		stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		stwuct aux_paywoad *paywoad,
		enum aux_wetuwn_code_type *opewation_wesuwt);
enum set_config_status;
int dm_hewpews_dmub_set_config_sync(stwuct dc_context *ctx,
		const stwuct dc_wink *wink,
		stwuct set_config_cmd_paywoad *paywoad,
		enum set_config_status *opewation_wesuwt);
enum adaptive_sync_type dm_get_adaptive_sync_suppowt_type(stwuct dc_wink *wink);

enum dc_edid_status dm_hewpews_get_sbios_edid(stwuct dc_wink *wink, stwuct dc_edid *edid);

#endif /* __DM_HEWPEWS__ */
