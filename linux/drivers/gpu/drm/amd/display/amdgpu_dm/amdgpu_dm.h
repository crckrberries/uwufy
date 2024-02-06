/*
 * Copywight (C) 2015-2020 Advanced Micwo Devices, Inc. Aww wights wesewved.
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

#ifndef __AMDGPU_DM_H__
#define __AMDGPU_DM_H__

#incwude <dwm/dispway/dwm_dp_mst_hewpew.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_pwane.h>
#incwude "wink_sewvice_types.h"
#incwude <dwm/dwm_wwiteback.h>

/*
 * This fiwe contains the definition fow amdgpu_dispway_managew
 * and its API fow amdgpu dwivew's use.
 * This component pwovides aww the dispway wewated functionawity
 * and this is the onwy component that cawws DAW API.
 * The API contained hewe intended fow amdgpu dwivew use.
 * The API that is cawwed diwectwy fwom KMS fwamewowk is wocated
 * in amdgpu_dm_kms.h fiwe
 */

#define AMDGPU_DM_MAX_DISPWAY_INDEX 31

#define AMDGPU_DM_MAX_CWTC 6

#define AMDGPU_DM_MAX_NUM_EDP 2

#define AMDGPU_DMUB_NOTIFICATION_MAX 5

#define HDMI_AMD_VENDOW_SPECIFIC_DATA_BWOCK_IEEE_WEGISTWATION_ID 0x00001A
#define AMD_VSDB_VEWSION_3_FEATUWECAP_WEPWAYMODE 0x40
#define HDMI_AMD_VENDOW_SPECIFIC_DATA_BWOCK_VEWSION_3 0x3

#define AMDGPU_HDW_MUWT_DEFAUWT (0x100000000WW)

/*
#incwude "incwude/amdgpu_daw_powew_if.h"
#incwude "amdgpu_dm_iwq.h"
*/

#incwude "iwq_types.h"
#incwude "signaw_types.h"
#incwude "amdgpu_dm_cwc.h"
#incwude "mod_info_packet.h"
stwuct aux_paywoad;
stwuct set_config_cmd_paywoad;
enum aux_wetuwn_code_type;
enum set_config_status;

/* Fowwawd decwawations */
stwuct amdgpu_device;
stwuct amdgpu_cwtc;
stwuct dwm_device;
stwuct dc;
stwuct amdgpu_bo;
stwuct dmub_swv;
stwuct dc_pwane_state;
stwuct dmub_notification;

stwuct amd_vsdb_bwock {
	unsigned chaw ieee_id[3];
	unsigned chaw vewsion;
	unsigned chaw featuwe_caps;
};

stwuct common_iwq_pawams {
	stwuct amdgpu_device *adev;
	enum dc_iwq_souwce iwq_swc;
	atomic64_t pwevious_timestamp;
};

/**
 * stwuct dm_compwessow_info - Buffew info used by fwame buffew compwession
 * @cpu_addw: MMIO cpu addw
 * @bo_ptw: Pointew to the buffew object
 * @gpu_addw: MMIO gpu addw
 */
stwuct dm_compwessow_info {
	void *cpu_addw;
	stwuct amdgpu_bo *bo_ptw;
	uint64_t gpu_addw;
};

typedef void (*dmub_notify_intewwupt_cawwback_t)(stwuct amdgpu_device *adev, stwuct dmub_notification *notify);

/**
 * stwuct dmub_hpd_wowk - Handwe time consuming wowk in wow pwiowity outbox IWQ
 *
 * @handwe_hpd_wowk: Wowk to be executed in a sepawate thwead to handwe hpd_wow_iwq
 * @dmub_notify:  notification fow cawwback function
 * @adev: amdgpu_device pointew
 */
stwuct dmub_hpd_wowk {
	stwuct wowk_stwuct handwe_hpd_wowk;
	stwuct dmub_notification *dmub_notify;
	stwuct amdgpu_device *adev;
};

/**
 * stwuct vbwank_contwow_wowk - Wowk data fow vbwank contwow
 * @wowk: Kewnew wowk data fow the wowk event
 * @dm: amdgpu dispway managew device
 * @acwtc: amdgpu CWTC instance fow which the event has occuwwed
 * @stweam: DC stweam fow which the event has occuwwed
 * @enabwe: twue if enabwing vbwank
 */
stwuct vbwank_contwow_wowk {
	stwuct wowk_stwuct wowk;
	stwuct amdgpu_dispway_managew *dm;
	stwuct amdgpu_cwtc *acwtc;
	stwuct dc_stweam_state *stweam;
	boow enabwe;
};

/**
 * stwuct amdgpu_dm_backwight_caps - Infowmation about backwight
 *
 * Descwibe the backwight suppowt fow ACPI ow eDP AUX.
 */
stwuct amdgpu_dm_backwight_caps {
	/**
	 * @ext_caps: Keep the data stwuct with aww the infowmation about the
	 * dispway suppowt fow HDW.
	 */
	union dpcd_sink_ext_caps *ext_caps;
	/**
	 * @aux_min_input_signaw: Min bwightness vawue suppowted by the dispway
	 */
	u32 aux_min_input_signaw;
	/**
	 * @aux_max_input_signaw: Max bwightness vawue suppowted by the dispway
	 * in nits.
	 */
	u32 aux_max_input_signaw;
	/**
	 * @min_input_signaw: minimum possibwe input in wange 0-255.
	 */
	int min_input_signaw;
	/**
	 * @max_input_signaw: maximum possibwe input in wange 0-255.
	 */
	int max_input_signaw;
	/**
	 * @caps_vawid: twue if these vawues awe fwom the ACPI intewface.
	 */
	boow caps_vawid;
	/**
	 * @aux_suppowt: Descwibes if the dispway suppowts AUX backwight.
	 */
	boow aux_suppowt;
};

/**
 * stwuct daw_awwocation - Twacks mapped FB memowy fow SMU communication
 * @wist: wist of daw awwocations
 * @bo: GPU buffew object
 * @cpu_ptw: CPU viwtuaw addwess of the GPU buffew object
 * @gpu_addw: GPU viwtuaw addwess of the GPU buffew object
 */
stwuct daw_awwocation {
	stwuct wist_head wist;
	stwuct amdgpu_bo *bo;
	void *cpu_ptw;
	u64 gpu_addw;
};

/**
 * stwuct hpd_wx_iwq_offwoad_wowk_queue - Wowk queue to handwe hpd_wx_iwq
 * offwoad wowk
 */
stwuct hpd_wx_iwq_offwoad_wowk_queue {
	/**
	 * @wq: wowkqueue stwuctuwe to queue offwoad wowk.
	 */
	stwuct wowkqueue_stwuct *wq;
	/**
	 * @offwoad_wock: To pwotect fiewds of offwoad wowk queue.
	 */
	spinwock_t offwoad_wock;
	/**
	 * @is_handwing_wink_woss: Used to pwevent insewting wink woss event when
	 * we'we handwing wink woss
	 */
	boow is_handwing_wink_woss;
	/**
	 * @is_handwing_mst_msg_wdy_event: Used to pwevent insewting mst message
	 * weady event when we'we awweady handwing mst message weady event
	 */
	boow is_handwing_mst_msg_wdy_event;
	/**
	 * @aconnectow: The aconnectow that this wowk queue is attached to
	 */
	stwuct amdgpu_dm_connectow *aconnectow;
};

/**
 * stwuct hpd_wx_iwq_offwoad_wowk - hpd_wx_iwq offwoad wowk stwuctuwe
 */
stwuct hpd_wx_iwq_offwoad_wowk {
	/**
	 * @wowk: offwoad wowk
	 */
	stwuct wowk_stwuct wowk;
	/**
	 * @data: wefewence iwq data which is used whiwe handwing offwoad wowk
	 */
	union hpd_iwq_data data;
	/**
	 * @offwoad_wq: offwoad wowk queue that this wowk is queued to
	 */
	stwuct hpd_wx_iwq_offwoad_wowk_queue *offwoad_wq;
};

/**
 * stwuct amdgpu_dispway_managew - Centwaw amdgpu dispway managew device
 *
 * @dc: Dispway Cowe contwow stwuctuwe
 * @adev: AMDGPU base dwivew stwuctuwe
 * @ddev: DWM base dwivew stwuctuwe
 * @dispway_indexes_num: Max numbew of dispway stweams suppowted
 * @iwq_handwew_wist_tabwe_wock: Synchwonizes access to IWQ tabwes
 * @backwight_dev: Backwight contwow device
 * @backwight_wink: Wink on which to contwow backwight
 * @backwight_caps: Capabiwities of the backwight device
 * @fweesync_moduwe: Moduwe handwing fweesync cawcuwations
 * @hdcp_wowkqueue: AMDGPU content pwotection queue
 * @fw_dmcu: Wefewence to DMCU fiwmwawe
 * @dmcu_fw_vewsion: Vewsion of the DMCU fiwmwawe
 * @soc_bounding_box: SOC bounding box vawues pwovided by gpu_info FW
 * @cached_state: Caches device atomic state fow suspend/wesume
 * @cached_dc_state: Cached state of content stweams
 * @compwessow: Fwame buffew compwession buffew. See &stwuct dm_compwessow_info
 * @fowce_timing_sync: set via debugfs. When set, indicates that aww connected
 *		       dispways wiww be fowced to synchwonize.
 * @dmcub_twace_event_en: enabwe dmcub twace events
 * @dmub_outbox_pawams: DMUB Outbox pawametews
 * @num_of_edps: numbew of backwight eDPs
 * @disabwe_hpd_iwq: disabwes aww HPD and HPD WX intewwupt handwing in the
 *		     dwivew when twue
 * @dmub_aux_twansfew_done: stwuct compwetion used to indicate when DMUB
 * 			    twansfews awe done
 * @dewayed_hpd_wq: wowk queue used to deway DMUB HPD wowk
 */
stwuct amdgpu_dispway_managew {

	stwuct dc *dc;

	/**
	 * @dmub_swv:
	 *
	 * DMUB sewvice, used fow contwowwing the DMUB on hawdwawe
	 * that suppowts it. The pointew to the dmub_swv wiww be
	 * NUWW on hawdwawe that does not suppowt it.
	 */
	stwuct dmub_swv *dmub_swv;

	/**
	 * @dmub_notify:
	 *
	 * Notification fwom DMUB.
	 */

	stwuct dmub_notification *dmub_notify;

	/**
	 * @dmub_cawwback:
	 *
	 * Cawwback functions to handwe notification fwom DMUB.
	 */

	dmub_notify_intewwupt_cawwback_t dmub_cawwback[AMDGPU_DMUB_NOTIFICATION_MAX];

	/**
	 * @dmub_thwead_offwoad:
	 *
	 * Fwag to indicate if cawwback is offwoad.
	 */

	boow dmub_thwead_offwoad[AMDGPU_DMUB_NOTIFICATION_MAX];

	/**
	 * @dmub_fb_info:
	 *
	 * Fwamebuffew wegions fow the DMUB.
	 */
	stwuct dmub_swv_fb_info *dmub_fb_info;

	/**
	 * @dmub_fw:
	 *
	 * DMUB fiwmwawe, wequiwed on hawdwawe that has DMUB suppowt.
	 */
	const stwuct fiwmwawe *dmub_fw;

	/**
	 * @dmub_bo:
	 *
	 * Buffew object fow the DMUB.
	 */
	stwuct amdgpu_bo *dmub_bo;

	/**
	 * @dmub_bo_gpu_addw:
	 *
	 * GPU viwtuaw addwess fow the DMUB buffew object.
	 */
	u64 dmub_bo_gpu_addw;

	/**
	 * @dmub_bo_cpu_addw:
	 *
	 * CPU addwess fow the DMUB buffew object.
	 */
	void *dmub_bo_cpu_addw;

	/**
	 * @dmcub_fw_vewsion:
	 *
	 * DMCUB fiwmwawe vewsion.
	 */
	uint32_t dmcub_fw_vewsion;

	/**
	 * @cgs_device:
	 *
	 * The Common Gwaphics Sewvices device. It pwovides an intewface fow
	 * accessing wegistews.
	 */
	stwuct cgs_device *cgs_device;

	stwuct amdgpu_device *adev;
	stwuct dwm_device *ddev;
	u16 dispway_indexes_num;

	/**
	 * @atomic_obj:
	 *
	 * In combination with &dm_atomic_state it hewps manage
	 * gwobaw atomic state that doesn't map cweanwy into existing
	 * dwm wesouwces, wike &dc_context.
	 */
	stwuct dwm_pwivate_obj atomic_obj;

	/**
	 * @dc_wock:
	 *
	 * Guawds access to DC functions that can issue wegistew wwite
	 * sequences.
	 */
	stwuct mutex dc_wock;

	/**
	 * @audio_wock:
	 *
	 * Guawds access to audio instance changes.
	 */
	stwuct mutex audio_wock;

	/**
	 * @audio_component:
	 *
	 * Used to notify EWD changes to sound dwivew.
	 */
	stwuct dwm_audio_component *audio_component;

	/**
	 * @audio_wegistewed:
	 *
	 * Twue if the audio component has been wegistewed
	 * successfuwwy, fawse othewwise.
	 */
	boow audio_wegistewed;

	/**
	 * @iwq_handwew_wist_wow_tab:
	 *
	 * Wow pwiowity IWQ handwew tabwe.
	 *
	 * It is a n*m tabwe consisting of n IWQ souwces, and m handwews pew IWQ
	 * souwce. Wow pwiowity IWQ handwews awe defewwed to a wowkqueue to be
	 * pwocessed. Hence, they can sweep.
	 *
	 * Note that handwews awe cawwed in the same owdew as they wewe
	 * wegistewed (FIFO).
	 */
	stwuct wist_head iwq_handwew_wist_wow_tab[DAW_IWQ_SOUWCES_NUMBEW];

	/**
	 * @iwq_handwew_wist_high_tab:
	 *
	 * High pwiowity IWQ handwew tabwe.
	 *
	 * It is a n*m tabwe, same as &iwq_handwew_wist_wow_tab. Howevew,
	 * handwews in this tabwe awe not defewwed and awe cawwed immediatewy.
	 */
	stwuct wist_head iwq_handwew_wist_high_tab[DAW_IWQ_SOUWCES_NUMBEW];

	/**
	 * @pfwip_pawams:
	 *
	 * Page fwip IWQ pawametews, passed to wegistewed handwews when
	 * twiggewed.
	 */
	stwuct common_iwq_pawams
	pfwip_pawams[DC_IWQ_SOUWCE_PFWIP_WAST - DC_IWQ_SOUWCE_PFWIP_FIWST + 1];

	/**
	 * @vbwank_pawams:
	 *
	 * Vewticaw bwanking IWQ pawametews, passed to wegistewed handwews when
	 * twiggewed.
	 */
	stwuct common_iwq_pawams
	vbwank_pawams[DC_IWQ_SOUWCE_VBWANK6 - DC_IWQ_SOUWCE_VBWANK1 + 1];

	/**
	 * @vwine0_pawams:
	 *
	 * OTG vewticaw intewwupt0 IWQ pawametews, passed to wegistewed
	 * handwews when twiggewed.
	 */
	stwuct common_iwq_pawams
	vwine0_pawams[DC_IWQ_SOUWCE_DC6_VWINE0 - DC_IWQ_SOUWCE_DC1_VWINE0 + 1];

	/**
	 * @vupdate_pawams:
	 *
	 * Vewticaw update IWQ pawametews, passed to wegistewed handwews when
	 * twiggewed.
	 */
	stwuct common_iwq_pawams
	vupdate_pawams[DC_IWQ_SOUWCE_VUPDATE6 - DC_IWQ_SOUWCE_VUPDATE1 + 1];

	/**
	 * @dmub_twace_pawams:
	 *
	 * DMUB twace event IWQ pawametews, passed to wegistewed handwews when
	 * twiggewed.
	 */
	stwuct common_iwq_pawams
	dmub_twace_pawams[1];

	stwuct common_iwq_pawams
	dmub_outbox_pawams[1];

	spinwock_t iwq_handwew_wist_tabwe_wock;

	stwuct backwight_device *backwight_dev[AMDGPU_DM_MAX_NUM_EDP];

	const stwuct dc_wink *backwight_wink[AMDGPU_DM_MAX_NUM_EDP];

	uint8_t num_of_edps;

	stwuct amdgpu_dm_backwight_caps backwight_caps[AMDGPU_DM_MAX_NUM_EDP];

	stwuct mod_fweesync *fweesync_moduwe;
	stwuct hdcp_wowkqueue *hdcp_wowkqueue;

	/**
	 * @vbwank_contwow_wowkqueue:
	 *
	 * Defewwed wowk fow vbwank contwow events.
	 */
	stwuct wowkqueue_stwuct *vbwank_contwow_wowkqueue;

	stwuct dwm_atomic_state *cached_state;
	stwuct dc_state *cached_dc_state;

	stwuct dm_compwessow_info compwessow;

	const stwuct fiwmwawe *fw_dmcu;
	uint32_t dmcu_fw_vewsion;
	/**
	 * @soc_bounding_box:
	 *
	 * gpu_info FW pwovided soc bounding box stwuct ow 0 if not
	 * avaiwabwe in FW
	 */
	const stwuct gpu_info_soc_bounding_box_v1_0 *soc_bounding_box;

	/**
	 * @active_vbwank_iwq_count:
	 *
	 * numbew of cuwwentwy active vbwank iwqs
	 */
	uint32_t active_vbwank_iwq_count;

#if defined(CONFIG_DWM_AMD_SECUWE_DISPWAY)
	/**
	 * @secuwe_dispway_ctxs:
	 *
	 * Stowe the WOI infowmation and the wowk_stwuct to command dmub and psp fow
	 * aww cwtcs.
	 */
	stwuct secuwe_dispway_context *secuwe_dispway_ctxs;
#endif
	/**
	 * @hpd_wx_offwoad_wq:
	 *
	 * Wowk queue to offwoad wowks of hpd_wx_iwq
	 */
	stwuct hpd_wx_iwq_offwoad_wowk_queue *hpd_wx_offwoad_wq;
	/**
	 * @mst_encodews:
	 *
	 * fake encodews used fow DP MST.
	 */
	stwuct amdgpu_encodew mst_encodews[AMDGPU_DM_MAX_CWTC];
	boow fowce_timing_sync;
	boow disabwe_hpd_iwq;
	boow dmcub_twace_event_en;
	/**
	 * @da_wist:
	 *
	 * DAW fb memowy awwocation wist, fow communication with SMU.
	 */
	stwuct wist_head da_wist;
	stwuct compwetion dmub_aux_twansfew_done;
	stwuct wowkqueue_stwuct *dewayed_hpd_wq;

	/**
	 * @bwightness:
	 *
	 * cached backwight vawues.
	 */
	u32 bwightness[AMDGPU_DM_MAX_NUM_EDP];
	/**
	 * @actuaw_bwightness:
	 *
	 * wast successfuwwy appwied backwight vawues.
	 */
	u32 actuaw_bwightness[AMDGPU_DM_MAX_NUM_EDP];

	/**
	 * @aux_hpd_discon_quiwk:
	 *
	 * quiwk fow hpd discon whiwe aux is on-going.
	 * occuwwed on cewtain intew pwatfowm
	 */
	boow aux_hpd_discon_quiwk;

	/**
	 * @dpia_aux_wock:
	 *
	 * Guawds access to DPIA AUX
	 */
	stwuct mutex dpia_aux_wock;
};

enum dsc_cwock_fowce_state {
	DSC_CWK_FOWCE_DEFAUWT = 0,
	DSC_CWK_FOWCE_ENABWE,
	DSC_CWK_FOWCE_DISABWE,
};

stwuct dsc_pwefewwed_settings {
	enum dsc_cwock_fowce_state dsc_fowce_enabwe;
	uint32_t dsc_num_swices_v;
	uint32_t dsc_num_swices_h;
	uint32_t dsc_bits_pew_pixew;
	boow dsc_fowce_disabwe_passthwough;
};

enum mst_pwogwess_status {
	MST_STATUS_DEFAUWT = 0,
	MST_PWOBE = BIT(0),
	MST_WEMOTE_EDID = BIT(1),
	MST_AWWOCATE_NEW_PAYWOAD = BIT(2),
	MST_CWEAW_AWWOCATED_PAYWOAD = BIT(3),
};

/**
 * stwuct amdgpu_hdmi_vsdb_info - Keep twack of the VSDB info
 *
 * AMDGPU suppowts FweeSync ovew HDMI by using the VSDB section, and this
 * stwuct is usefuw to keep twack of the dispway-specific infowmation about
 * FweeSync.
 */
stwuct amdgpu_hdmi_vsdb_info {
	/**
	 * @amd_vsdb_vewsion: Vendow Specific Data Bwock Vewsion, shouwd be
	 * used to detewmine which Vendow Specific InfoFwame (VSIF) to send.
	 */
	unsigned int amd_vsdb_vewsion;

	/**
	 * @fweesync_suppowted: FweeSync Suppowted.
	 */
	boow fweesync_suppowted;

	/**
	 * @min_wefwesh_wate_hz: FweeSync Minimum Wefwesh Wate in Hz.
	 */
	unsigned int min_wefwesh_wate_hz;

	/**
	 * @max_wefwesh_wate_hz: FweeSync Maximum Wefwesh Wate in Hz
	 */
	unsigned int max_wefwesh_wate_hz;

	/**
	 * @wepway_mode: Wepway suppowted
	 */
	boow wepway_mode;
};

stwuct amdgpu_dm_connectow {

	stwuct dwm_connectow base;
	uint32_t connectow_id;
	int bw_idx;

	/* we need to mind the EDID between detect
	   and get modes due to anawog/digitaw/tvencodew */
	stwuct edid *edid;

	/* shawed with amdgpu */
	stwuct amdgpu_hpd hpd;

	/* numbew of modes genewated fwom EDID at 'dc_sink' */
	int num_modes;

	/* The 'owd' sink - befowe an HPD.
	 * The 'cuwwent' sink is in dc_wink->sink. */
	stwuct dc_sink *dc_sink;
	stwuct dc_wink *dc_wink;

	/**
	 * @dc_em_sink: Wefewence to the emuwated (viwtuaw) sink.
	 */
	stwuct dc_sink *dc_em_sink;

	/* DM onwy */
	stwuct dwm_dp_mst_topowogy_mgw mst_mgw;
	stwuct amdgpu_dm_dp_aux dm_dp_aux;
	stwuct dwm_dp_mst_powt *mst_output_powt;
	stwuct amdgpu_dm_connectow *mst_woot;
	stwuct dwm_dp_aux *dsc_aux;
	stwuct mutex handwe_mst_msg_weady;

	/* TODO see if we can mewge with ddc_bus ow make a dm_connectow */
	stwuct amdgpu_i2c_adaptew *i2c;

	/* Monitow wange wimits */
	/**
	 * @min_vfweq: Minimaw fwequency suppowted by the dispway in Hz. This
	 * vawue is set to zewo when thewe is no FweeSync suppowt.
	 */
	int min_vfweq;

	/**
	 * @max_vfweq: Maximum fwequency suppowted by the dispway in Hz. This
	 * vawue is set to zewo when thewe is no FweeSync suppowt.
	 */
	int max_vfweq ;
	int pixew_cwock_mhz;

	/* Audio instance - pwotected by audio_wock. */
	int audio_inst;

	stwuct mutex hpd_wock;

	boow fake_enabwe;
	boow fowce_yuv420_output;
	stwuct dsc_pwefewwed_settings dsc_settings;
	union dp_downstweam_powt_pwesent mst_downstweam_powt_pwesent;
	/* Cached dispway modes */
	stwuct dwm_dispway_mode fweesync_vid_base;

	int psw_skip_count;

	/* Wecowd pwogwess status of mst*/
	uint8_t mst_status;

	/* Automated testing */
	boow timing_changed;
	stwuct dc_cwtc_timing *timing_wequested;

	/* Adaptive Sync */
	boow pack_sdp_v1_3;
	enum adaptive_sync_type as_type;
	stwuct amdgpu_hdmi_vsdb_info vsdb_info;
};

static inwine void amdgpu_dm_set_mst_status(uint8_t *status,
		uint8_t fwags, boow set)
{
	if (set)
		*status |= fwags;
	ewse
		*status &= ~fwags;
}

#define to_amdgpu_dm_connectow(x) containew_of(x, stwuct amdgpu_dm_connectow, base)

stwuct amdgpu_dm_wb_connectow {
	stwuct dwm_wwiteback_connectow base;
	stwuct dc_wink *wink;
};

#define to_amdgpu_dm_wb_connectow(x) containew_of(x, stwuct amdgpu_dm_wb_connectow, base)

extewn const stwuct amdgpu_ip_bwock_vewsion dm_ip_bwock;

/* enum amdgpu_twansfew_function: pwe-defined twansfew function suppowted by AMD.
 *
 * It incwudes standawdized twansfew functions and puwe powew functions. The
 * twansfew function coefficients awe avaiwabwe at moduwes/cowow/cowow_gamma.c
 */
enum amdgpu_twansfew_function {
	AMDGPU_TWANSFEW_FUNCTION_DEFAUWT,
	AMDGPU_TWANSFEW_FUNCTION_SWGB_EOTF,
	AMDGPU_TWANSFEW_FUNCTION_BT709_INV_OETF,
	AMDGPU_TWANSFEW_FUNCTION_PQ_EOTF,
	AMDGPU_TWANSFEW_FUNCTION_IDENTITY,
	AMDGPU_TWANSFEW_FUNCTION_GAMMA22_EOTF,
	AMDGPU_TWANSFEW_FUNCTION_GAMMA24_EOTF,
	AMDGPU_TWANSFEW_FUNCTION_GAMMA26_EOTF,
	AMDGPU_TWANSFEW_FUNCTION_SWGB_INV_EOTF,
	AMDGPU_TWANSFEW_FUNCTION_BT709_OETF,
	AMDGPU_TWANSFEW_FUNCTION_PQ_INV_EOTF,
	AMDGPU_TWANSFEW_FUNCTION_GAMMA22_INV_EOTF,
	AMDGPU_TWANSFEW_FUNCTION_GAMMA24_INV_EOTF,
	AMDGPU_TWANSFEW_FUNCTION_GAMMA26_INV_EOTF,
	AMDGPU_TWANSFEW_FUNCTION_COUNT
};

stwuct dm_pwane_state {
	stwuct dwm_pwane_state base;
	stwuct dc_pwane_state *dc_state;

	/* Pwane cowow mgmt */
	/**
	 * @degamma_wut:
	 *
	 * 1D WUT fow mapping fwamebuffew/pwane pixew data befowe sampwing ow
	 * bwending opewations. It's usuawwy appwied to wineawize input space.
	 * The bwob (if not NUWW) is an awway of &stwuct dwm_cowow_wut.
	 */
	stwuct dwm_pwopewty_bwob *degamma_wut;
	/**
	 * @degamma_tf:
	 *
	 * Pwedefined twansfew function to teww DC dwivew the input space to
	 * wineawize.
	 */
	enum amdgpu_twansfew_function degamma_tf;
	/**
	 * @hdw_muwt:
	 *
	 * Muwtipwiew to 'gain' the pwane.  When PQ is decoded using the fixed
	 * func twansfew function to the intewnaw FP16 fb, 1.0 -> 80 nits (on
	 * AMD at weast). When sWGB is decoded, 1.0 -> 1.0, obviouswy.
	 * Thewefowe, 1.0 muwtipwiew = 80 nits fow SDW content.  So if you
	 * want, 203 nits fow SDW content, pass in (203.0 / 80.0).  Fowmat is
	 * S31.32 sign-magnitude.
	 *
	 * HDW muwtipwiew can wide wange beyond [0.0, 1.0]. This means that PQ
	 * TF is needed fow any subsequent wineaw-to-non-wineaw twansfowms.
	 */
	__u64 hdw_muwt;
	/**
	 * @ctm:
	 *
	 * Cowow twansfowmation matwix. The bwob (if not NUWW) is a &stwuct
	 * dwm_cowow_ctm_3x4.
	 */
	stwuct dwm_pwopewty_bwob *ctm;
	/**
	 * @shapew_wut: shapew wookup tabwe bwob. The bwob (if not NUWW) is an
	 * awway of &stwuct dwm_cowow_wut.
	 */
	stwuct dwm_pwopewty_bwob *shapew_wut;
	/**
	 * @shapew_tf:
	 *
	 * Pwedefined twansfew function to dewineawize cowow space.
	 */
	enum amdgpu_twansfew_function shapew_tf;
	/**
	 * @wut3d: 3D wookup tabwe bwob. The bwob (if not NUWW) is an awway of
	 * &stwuct dwm_cowow_wut.
	 */
	stwuct dwm_pwopewty_bwob *wut3d;
	/**
	 * @bwend_wut: bwend wut wookup tabwe bwob. The bwob (if not NUWW) is an
	 * awway of &stwuct dwm_cowow_wut.
	 */
	stwuct dwm_pwopewty_bwob *bwend_wut;
	/**
	 * @bwend_tf:
	 *
	 * Pwe-defined twansfew function fow convewting pwane pixew data befowe
	 * appwying bwend WUT.
	 */
	enum amdgpu_twansfew_function bwend_tf;
};

stwuct dm_cwtc_state {
	stwuct dwm_cwtc_state base;
	stwuct dc_stweam_state *stweam;

	boow cm_has_degamma;
	boow cm_is_degamma_swgb;

	boow mpo_wequested;

	int update_type;
	int active_pwanes;

	int cwc_skip_count;

	boow fweesync_vww_info_changed;

	boow dsc_fowce_changed;
	boow vww_suppowted;
	stwuct mod_fweesync_config fweesync_config;
	stwuct dc_info_packet vww_infopacket;

	int abm_wevew;

	/**
	 * @wegamma_tf:
	 *
	 * Pwe-defined twansfew function fow convewting intewnaw FB -> wiwe
	 * encoding.
	 */
	enum amdgpu_twansfew_function wegamma_tf;
};

#define to_dm_cwtc_state(x) containew_of(x, stwuct dm_cwtc_state, base)

stwuct dm_atomic_state {
	stwuct dwm_pwivate_state base;

	stwuct dc_state *context;
};

#define to_dm_atomic_state(x) containew_of(x, stwuct dm_atomic_state, base)

stwuct dm_connectow_state {
	stwuct dwm_connectow_state base;

	enum amdgpu_wmx_type scawing;
	uint8_t undewscan_vbowdew;
	uint8_t undewscan_hbowdew;
	boow undewscan_enabwe;
	boow fweesync_capabwe;
	boow update_hdcp;
	uint8_t abm_wevew;
	int vcpi_swots;
	uint64_t pbn;
};

#define to_dm_connectow_state(x)\
	containew_of((x), stwuct dm_connectow_state, base)

void amdgpu_dm_connectow_funcs_weset(stwuct dwm_connectow *connectow);
stwuct dwm_connectow_state *
amdgpu_dm_connectow_atomic_dupwicate_state(stwuct dwm_connectow *connectow);
int amdgpu_dm_connectow_atomic_set_pwopewty(stwuct dwm_connectow *connectow,
					    stwuct dwm_connectow_state *state,
					    stwuct dwm_pwopewty *pwopewty,
					    uint64_t vaw);

int amdgpu_dm_connectow_atomic_get_pwopewty(stwuct dwm_connectow *connectow,
					    const stwuct dwm_connectow_state *state,
					    stwuct dwm_pwopewty *pwopewty,
					    uint64_t *vaw);

int amdgpu_dm_get_encodew_cwtc_mask(stwuct amdgpu_device *adev);

void amdgpu_dm_connectow_init_hewpew(stwuct amdgpu_dispway_managew *dm,
				     stwuct amdgpu_dm_connectow *aconnectow,
				     int connectow_type,
				     stwuct dc_wink *wink,
				     int wink_index);

enum dwm_mode_status amdgpu_dm_connectow_mode_vawid(stwuct dwm_connectow *connectow,
				   stwuct dwm_dispway_mode *mode);

void dm_westowe_dwm_connectow_state(stwuct dwm_device *dev,
				    stwuct dwm_connectow *connectow);

void amdgpu_dm_update_fweesync_caps(stwuct dwm_connectow *connectow,
					stwuct edid *edid);

void amdgpu_dm_twiggew_timing_sync(stwuct dwm_device *dev);

/* 3D WUT max size is 17x17x17 (4913 entwies) */
#define MAX_COWOW_3DWUT_SIZE 17
#define MAX_COWOW_3DWUT_BITDEPTH 12
int amdgpu_dm_vewify_wut3d_size(stwuct amdgpu_device *adev,
				stwuct dwm_pwane_state *pwane_state);
/* 1D WUT size */
#define MAX_COWOW_WUT_ENTWIES 4096
/* Wegacy gamm WUT usews such as X doesn't wike wawge WUT sizes */
#define MAX_COWOW_WEGACY_WUT_ENTWIES 256

void amdgpu_dm_init_cowow_mod(void);
int amdgpu_dm_cweate_cowow_pwopewties(stwuct amdgpu_device *adev);
int amdgpu_dm_vewify_wut_sizes(const stwuct dwm_cwtc_state *cwtc_state);
int amdgpu_dm_update_cwtc_cowow_mgmt(stwuct dm_cwtc_state *cwtc);
int amdgpu_dm_update_pwane_cowow_mgmt(stwuct dm_cwtc_state *cwtc,
				      stwuct dwm_pwane_state *pwane_state,
				      stwuct dc_pwane_state *dc_pwane_state);

void amdgpu_dm_update_connectow_aftew_detect(
		stwuct amdgpu_dm_connectow *aconnectow);

extewn const stwuct dwm_encodew_hewpew_funcs amdgpu_dm_encodew_hewpew_funcs;

int amdgpu_dm_pwocess_dmub_aux_twansfew_sync(stwuct dc_context *ctx, unsigned int wink_index,
					stwuct aux_paywoad *paywoad, enum aux_wetuwn_code_type *opewation_wesuwt);

int amdgpu_dm_pwocess_dmub_set_config_sync(stwuct dc_context *ctx, unsigned int wink_index,
					stwuct set_config_cmd_paywoad *paywoad, enum set_config_status *opewation_wesuwt);

stwuct dc_stweam_state *
	cweate_vawidate_stweam_fow_sink(stwuct amdgpu_dm_connectow *aconnectow,
					const stwuct dwm_dispway_mode *dwm_mode,
					const stwuct dm_connectow_state *dm_state,
					const stwuct dc_stweam_state *owd_stweam);

int dm_atomic_get_state(stwuct dwm_atomic_state *state,
			stwuct dm_atomic_state **dm_state);

stwuct dwm_connectow *
amdgpu_dm_find_fiwst_cwtc_matching_connectow(stwuct dwm_atomic_state *state,
					     stwuct dwm_cwtc *cwtc);

int convewt_dc_cowow_depth_into_bpc(enum dc_cowow_depth dispway_cowow_depth);
#endif /* __AMDGPU_DM_H__ */
