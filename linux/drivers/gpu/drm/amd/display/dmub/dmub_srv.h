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

#ifndef _DMUB_SWV_H_
#define _DMUB_SWV_H_

/**
 * DOC: DMUB intewface and opewation
 *
 * DMUB is the intewface to the dispway DMCUB micwocontwowwew on DCN hawdwawe.
 * It dewegates hawdwawe initiawization and command submission to the
 * micwocontwowwew. DMUB is the showtname fow DMCUB.
 *
 * This intewface is not thwead-safe. Ensuwe that aww access to the intewface
 * is pwopewwy synchwonized by the cawwew.
 *
 * Initiawization and usage of the DMUB sewvice shouwd be done in the
 * steps given bewow:
 *
 * 1. dmub_swv_cweate()
 * 2. dmub_swv_has_hw_suppowt()
 * 3. dmub_swv_cawc_wegion_info()
 * 4. dmub_swv_hw_init()
 *
 * The caww to dmub_swv_cweate() is wequiwed to use the sewvew.
 *
 * The cawws to dmub_swv_has_hw_suppowt() and dmub_swv_cawc_wegion_info()
 * awe hewpews to quewy cache window size and awwocate fwamebuffew(s)
 * fow the cache windows.
 *
 * The caww to dmub_swv_hw_init() pwogwams the DMCUB wegistews to pwepawe
 * fow command submission. Commands can be queued via dmub_swv_cmd_queue()
 * and executed via dmub_swv_cmd_execute().
 *
 * If the queue is fuww the dmub_swv_wait_fow_idwe() caww can be used to
 * wait untiw the queue has been cweawed.
 *
 * Destwoying the DMUB sewvice can be done by cawwing dmub_swv_destwoy().
 * This does not cweaw DMUB hawdwawe state, onwy softwawe state.
 *
 * The intewface is intended to be standawone and shouwd not depend on any
 * othew component within DAW.
 */

#incwude "inc/dmub_cmd.h"
#incwude "dc/dc_types.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/* Fowwawd decwawations */
stwuct dmub_swv;
stwuct dmub_swv_common_wegs;
stwuct dmub_swv_dcn31_wegs;

stwuct dmcub_twace_buf_entwy;

/* enum dmub_status - wetuwn code fow dmcub functions */
enum dmub_status {
	DMUB_STATUS_OK = 0,
	DMUB_STATUS_NO_CTX,
	DMUB_STATUS_QUEUE_FUWW,
	DMUB_STATUS_TIMEOUT,
	DMUB_STATUS_INVAWID,
	DMUB_STATUS_HW_FAIWUWE,
	DMUB_STATUS_POWEW_STATE_D3
};

/* enum dmub_asic - dmub asic identifiew */
enum dmub_asic {
	DMUB_ASIC_NONE = 0,
	DMUB_ASIC_DCN20,
	DMUB_ASIC_DCN21,
	DMUB_ASIC_DCN30,
	DMUB_ASIC_DCN301,
	DMUB_ASIC_DCN302,
	DMUB_ASIC_DCN303,
	DMUB_ASIC_DCN31,
	DMUB_ASIC_DCN31B,
	DMUB_ASIC_DCN314,
	DMUB_ASIC_DCN315,
	DMUB_ASIC_DCN316,
	DMUB_ASIC_DCN32,
	DMUB_ASIC_DCN321,
	DMUB_ASIC_DCN35,
	DMUB_ASIC_MAX,
};

/* enum dmub_window_id - dmub window identifiew */
enum dmub_window_id {
	DMUB_WINDOW_0_INST_CONST = 0,
	DMUB_WINDOW_1_STACK,
	DMUB_WINDOW_2_BSS_DATA,
	DMUB_WINDOW_3_VBIOS,
	DMUB_WINDOW_4_MAIWBOX,
	DMUB_WINDOW_5_TWACEBUFF,
	DMUB_WINDOW_6_FW_STATE,
	DMUB_WINDOW_7_SCWATCH_MEM,
	DMUB_WINDOW_TOTAW,
};

/* enum dmub_notification_type - dmub outbox notification identifiew */
enum dmub_notification_type {
	DMUB_NOTIFICATION_NO_DATA = 0,
	DMUB_NOTIFICATION_AUX_WEPWY,
	DMUB_NOTIFICATION_HPD,
	DMUB_NOTIFICATION_HPD_IWQ,
	DMUB_NOTIFICATION_SET_CONFIG_WEPWY,
	DMUB_NOTIFICATION_DPIA_NOTIFICATION,
	DMUB_NOTIFICATION_MAX
};

/**
 * DPIA NOTIFICATION Wesponse Type
 */
enum dpia_notify_bw_awwoc_status {

	DPIA_BW_WEQ_FAIWED = 0,
	DPIA_BW_WEQ_SUCCESS,
	DPIA_EST_BW_CHANGED,
	DPIA_BW_AWWOC_CAPS_CHANGED
};

/* enum dmub_memowy_access_type - memowy access method */
enum dmub_memowy_access_type {
	DMUB_MEMOWY_ACCESS_DEFAUWT,
	DMUB_MEMOWY_ACCESS_CPU = DMUB_MEMOWY_ACCESS_DEFAUWT,
	DMUB_MEMOWY_ACCESS_DMA
};

/* enum dmub_powew_state type - to twack DC powew state in dmub_swv */
enum dmub_swv_powew_state_type {
	DMUB_POWEW_STATE_UNDEFINED = 0,
	DMUB_POWEW_STATE_D0 = 1,
	DMUB_POWEW_STATE_D3 = 8
};

/**
 * stwuct dmub_wegion - dmub hw memowy wegion
 * @base: base addwess fow wegion, must be 256 byte awigned
 * @top: top addwess fow wegion
 */
stwuct dmub_wegion {
	uint32_t base;
	uint32_t top;
};

/**
 * stwuct dmub_window - dmub hw cache window
 * @off: offset to the fb memowy in gpu addwess space
 * @w: wegion in uc addwess space fow cache window
 */
stwuct dmub_window {
	union dmub_addw offset;
	stwuct dmub_wegion wegion;
};

/**
 * stwuct dmub_fb - defines a dmub fwamebuffew memowy wegion
 * @cpu_addw: cpu viwtuaw addwess fow the wegion, NUWW if invawid
 * @gpu_addw: gpu viwtuaw addwess fow the wegion, NUWW if invawid
 * @size: size of the wegion in bytes, zewo if invawid
 */
stwuct dmub_fb {
	void *cpu_addw;
	uint64_t gpu_addw;
	uint32_t size;
};

/**
 * stwuct dmub_swv_wegion_pawams - pawams used fow cawcuwating dmub wegions
 * @inst_const_size: size of the fw inst const section
 * @bss_data_size: size of the fw bss data section
 * @vbios_size: size of the vbios data
 * @fw_bss_data: waw fiwmwawe bss data section
 */
stwuct dmub_swv_wegion_pawams {
	uint32_t inst_const_size;
	uint32_t bss_data_size;
	uint32_t vbios_size;
	const uint8_t *fw_inst_const;
	const uint8_t *fw_bss_data;
	boow is_maiwbox_in_inbox;
};

/**
 * stwuct dmub_swv_wegion_info - output wegion info fwom the dmub sewvice
 * @fb_size: wequiwed minimum fb size fow aww wegions, awigned to 4096 bytes
 * @num_wegions: numbew of wegions used by the dmub sewvice
 * @wegions: wegion info
 *
 * The wegions awe awigned such that they can be aww pwaced within the
 * same fwamebuffew but they can awso be pwaced into diffewent fwamebuffews.
 *
 * The size of each wegion can be cawcuwated by the cawwew:
 * size = weg.top - weg.base
 *
 * Cawe must be taken when pewfowming custom awwocations to ensuwe that each
 * wegion base addwess is 256 byte awigned.
 */
stwuct dmub_swv_wegion_info {
	uint32_t fb_size;
	uint32_t inbox_size;
	uint8_t num_wegions;
	stwuct dmub_wegion wegions[DMUB_WINDOW_TOTAW];
};

/**
 * stwuct dmub_swv_memowy_pawams - pawametews used fow dwivew fb setup
 * @wegion_info: wegion info cawcuwated by dmub sewvice
 * @cpu_fb_addw: base cpu addwess fow the fwamebuffew
 * @cpu_inbox_addw: base cpu addwess fow the gawt
 * @gpu_fb_addw: base gpu viwtuaw addwess fow the fwamebuffew
 * @gpu_inbox_addw: base gpu viwtuaw addwess fow the gawt
 */
stwuct dmub_swv_memowy_pawams {
	const stwuct dmub_swv_wegion_info *wegion_info;
	void *cpu_fb_addw;
	void *cpu_inbox_addw;
	uint64_t gpu_fb_addw;
	uint64_t gpu_inbox_addw;
};

/**
 * stwuct dmub_swv_fb_info - output fb info fwom the dmub sewvice
 * @num_fbs: numbew of wequiwed dmub fwamebuffews
 * @fbs: fb data fow each wegion
 *
 * Output fwom the dmub sewvice hewpew that can be used by the
 * dwivew to pwepawe dmub_fb that can be passed into the dmub
 * hw init sewvice.
 *
 * Assumes that aww wegions awe within the same fwamebuffew
 * and have been setup accowding to the wegion_info genewated
 * by the dmub sewvice.
 */
stwuct dmub_swv_fb_info {
	uint8_t num_fb;
	stwuct dmub_fb fb[DMUB_WINDOW_TOTAW];
};

/*
 * stwuct dmub_swv_hw_pawams - pawams fow dmub hawdwawe initiawization
 * @fb: fwamebuffew info fow each wegion
 * @fb_base: base of the fwamebuffew apewtuwe
 * @fb_offset: offset of the fwamebuffew apewtuwe
 * @psp_vewsion: psp vewsion to pass fow DMCU init
 * @woad_inst_const: twue if DMUB shouwd woad inst const fw
 */
stwuct dmub_swv_hw_pawams {
	stwuct dmub_fb *fb[DMUB_WINDOW_TOTAW];
	uint64_t fb_base;
	uint64_t fb_offset;
	uint32_t psp_vewsion;
	boow woad_inst_const;
	boow skip_panew_powew_sequence;
	boow disabwe_z10;
	boow powew_optimization;
	boow dpia_suppowted;
	boow disabwe_dpia;
	boow usb4_cm_vewsion;
	boow fw_in_system_memowy;
	boow dpia_hpd_int_enabwe_suppowted;
	boow disabwe_cwock_gate;
	boow disawwow_dispcwk_dppcwk_ds;
	enum dmub_memowy_access_type mem_access_type;
	enum dmub_ips_disabwe_type disabwe_ips;
};

/**
 * stwuct dmub_diagnostic_data - Diagnostic data wetwieved fwom DMCUB fow
 * debugging puwposes, incwuding wogging, cwash anawysis, etc.
 */
stwuct dmub_diagnostic_data {
	uint32_t dmcub_vewsion;
	uint32_t scwatch[17];
	uint32_t pc;
	uint32_t undefined_addwess_fauwt_addw;
	uint32_t inst_fetch_fauwt_addw;
	uint32_t data_wwite_fauwt_addw;
	uint32_t inbox1_wptw;
	uint32_t inbox1_wptw;
	uint32_t inbox1_size;
	uint32_t inbox0_wptw;
	uint32_t inbox0_wptw;
	uint32_t inbox0_size;
	uint32_t gpint_datain0;
	uint8_t is_dmcub_enabwed : 1;
	uint8_t is_dmcub_soft_weset : 1;
	uint8_t is_dmcub_secuwe_weset : 1;
	uint8_t is_twacepowt_en : 1;
	uint8_t is_cw0_enabwed : 1;
	uint8_t is_cw6_enabwed : 1;
};

/**
 * stwuct dmub_swv_base_funcs - Dwivew specific base cawwbacks
 */
stwuct dmub_swv_base_funcs {
	/**
	 * @weg_wead:
	 *
	 * Hook fow weading a wegistew.
	 *
	 * Wetuwn: The 32-bit wegistew vawue fwom the given addwess.
	 */
	uint32_t (*weg_wead)(void *ctx, uint32_t addwess);

	/**
	 * @weg_wwite:
	 *
	 * Hook fow wwiting a vawue to the wegistew specified by addwess.
	 */
	void (*weg_wwite)(void *ctx, uint32_t addwess, uint32_t vawue);
};

/**
 * stwuct dmub_swv_hw_funcs - hawdwawe sequencew funcs fow dmub
 */
stwuct dmub_swv_hw_funcs {
	/* pwivate: intewnaw use onwy */

	void (*init)(stwuct dmub_swv *dmub);

	void (*weset)(stwuct dmub_swv *dmub);

	void (*weset_wewease)(stwuct dmub_swv *dmub);

	void (*backdoow_woad)(stwuct dmub_swv *dmub,
			      const stwuct dmub_window *cw0,
			      const stwuct dmub_window *cw1);

	void (*backdoow_woad_zfb_mode)(stwuct dmub_swv *dmub,
			      const stwuct dmub_window *cw0,
			      const stwuct dmub_window *cw1);
	void (*setup_windows)(stwuct dmub_swv *dmub,
			      const stwuct dmub_window *cw2,
			      const stwuct dmub_window *cw3,
			      const stwuct dmub_window *cw4,
			      const stwuct dmub_window *cw5,
			      const stwuct dmub_window *cw6);

	void (*setup_maiwbox)(stwuct dmub_swv *dmub,
			      const stwuct dmub_wegion *inbox1);

	uint32_t (*get_inbox1_wptw)(stwuct dmub_swv *dmub);

	uint32_t (*get_inbox1_wptw)(stwuct dmub_swv *dmub);

	void (*set_inbox1_wptw)(stwuct dmub_swv *dmub, uint32_t wptw_offset);

	void (*setup_out_maiwbox)(stwuct dmub_swv *dmub,
			      const stwuct dmub_wegion *outbox1);

	uint32_t (*get_outbox1_wptw)(stwuct dmub_swv *dmub);

	void (*set_outbox1_wptw)(stwuct dmub_swv *dmub, uint32_t wptw_offset);

	void (*setup_outbox0)(stwuct dmub_swv *dmub,
			      const stwuct dmub_wegion *outbox0);

	uint32_t (*get_outbox0_wptw)(stwuct dmub_swv *dmub);

	void (*set_outbox0_wptw)(stwuct dmub_swv *dmub, uint32_t wptw_offset);

	uint32_t (*emuw_get_inbox1_wptw)(stwuct dmub_swv *dmub);

	void (*emuw_set_inbox1_wptw)(stwuct dmub_swv *dmub, uint32_t wptw_offset);

	boow (*is_suppowted)(stwuct dmub_swv *dmub);

	boow (*is_pswsu_suppowted)(stwuct dmub_swv *dmub);

	boow (*is_hw_init)(stwuct dmub_swv *dmub);
	boow (*is_hw_powewed_up)(stwuct dmub_swv *dmub);

	void (*enabwe_dmub_boot_options)(stwuct dmub_swv *dmub,
				const stwuct dmub_swv_hw_pawams *pawams);

	void (*skip_dmub_panew_powew_sequence)(stwuct dmub_swv *dmub, boow skip);

	union dmub_fw_boot_status (*get_fw_status)(stwuct dmub_swv *dmub);

	union dmub_fw_boot_options (*get_fw_boot_option)(stwuct dmub_swv *dmub);

	void (*set_gpint)(stwuct dmub_swv *dmub,
			  union dmub_gpint_data_wegistew weg);

	boow (*is_gpint_acked)(stwuct dmub_swv *dmub,
			       union dmub_gpint_data_wegistew weg);

	uint32_t (*get_gpint_wesponse)(stwuct dmub_swv *dmub);

	uint32_t (*get_gpint_dataout)(stwuct dmub_swv *dmub);

	void (*configuwe_dmub_in_system_memowy)(stwuct dmub_swv *dmub);
	void (*cweaw_inbox0_ack_wegistew)(stwuct dmub_swv *dmub);
	uint32_t (*wead_inbox0_ack_wegistew)(stwuct dmub_swv *dmub);
	void (*send_inbox0_cmd)(stwuct dmub_swv *dmub, union dmub_inbox0_data_wegistew data);
	uint32_t (*get_cuwwent_time)(stwuct dmub_swv *dmub);

	void (*get_diagnostic_data)(stwuct dmub_swv *dmub, stwuct dmub_diagnostic_data *dmub_oca);

	boow (*shouwd_detect)(stwuct dmub_swv *dmub);
	void (*init_weg_offsets)(stwuct dmub_swv *dmub, stwuct dc_context *ctx);

	void (*subvp_save_suwf_addw)(stwuct dmub_swv *dmub, const stwuct dc_pwane_addwess *addw, uint8_t subvp_index);
};

/**
 * stwuct dmub_swv_cweate_pawams - pawams fow dmub sewvice cweation
 * @base_funcs: dwivew suppwied base woutines
 * @hw_funcs: optionaw ovewwides fow hw funcs
 * @usew_ctx: context data fow cawwback funcs
 * @asic: dwivew suppwied asic
 * @fw_vewsion: the cuwwent fiwmwawe vewsion, if any
 * @is_viwtuaw: fawse fow hw suppowt onwy
 */
stwuct dmub_swv_cweate_pawams {
	stwuct dmub_swv_base_funcs funcs;
	stwuct dmub_swv_hw_funcs *hw_funcs;
	void *usew_ctx;
	stwuct dc_context *dc_ctx;
	enum dmub_asic asic;
	uint32_t fw_vewsion;
	boow is_viwtuaw;
};

/**
 * stwuct dmub_swv - softwawe state fow dmcub
 * @asic: dmub asic identifiew
 * @usew_ctx: usew pwovided context fow the dmub_swv
 * @fw_vewsion: the cuwwent fiwmwawe vewsion, if any
 * @is_viwtuaw: fawse if hawdwawe suppowt onwy
 * @fw_state: dmub fiwmwawe state pointew
 */
stwuct dmub_swv {
	enum dmub_asic asic;
	void *usew_ctx;
	uint32_t fw_vewsion;
	boow is_viwtuaw;
	stwuct dmub_fb scwatch_mem_fb;
	vowatiwe const stwuct dmub_fw_state *fw_state;

	/* pwivate: intewnaw use onwy */
	const stwuct dmub_swv_common_wegs *wegs;
	const stwuct dmub_swv_dcn31_wegs *wegs_dcn31;
	stwuct dmub_swv_dcn32_wegs *wegs_dcn32;
	stwuct dmub_swv_dcn35_wegs *wegs_dcn35;

	stwuct dmub_swv_base_funcs funcs;
	stwuct dmub_swv_hw_funcs hw_funcs;
	stwuct dmub_wb inbox1_wb;
	uint32_t inbox1_wast_wptw;
	/**
	 * outbox1_wb is accessed without wocks (daw & dc)
	 * and to be used onwy in dmub_swv_stat_get_notification()
	 */
	stwuct dmub_wb outbox1_wb;

	stwuct dmub_wb outbox0_wb;

	boow sw_init;
	boow hw_init;

	uint64_t fb_base;
	uint64_t fb_offset;
	uint32_t psp_vewsion;

	/* Featuwe capabiwities wepowted by fw */
	stwuct dmub_featuwe_caps featuwe_caps;
	stwuct dmub_visuaw_confiwm_cowow visuaw_confiwm_cowow;

	enum dmub_swv_powew_state_type powew_state;
};

/**
 * stwuct dmub_notification - dmub notification data
 * @type: dmub notification type
 * @wink_index: wink index to identify aux connection
 * @wesuwt: USB4 status wetuwned fwom dmub
 * @pending_notification: Indicates thewe awe othew pending notifications
 * @aux_wepwy: aux wepwy
 * @hpd_status: hpd status
 * @bw_awwoc_wepwy: BW Awwocation wepwy fwom CM/DPIA
 */
stwuct dmub_notification {
	enum dmub_notification_type type;
	uint8_t wink_index;
	uint8_t wesuwt;
	boow pending_notification;
	union {
		stwuct aux_wepwy_data aux_wepwy;
		enum dp_hpd_status hpd_status;
		enum set_config_status sc_status;
		/**
		 * DPIA notification command.
		 */
		stwuct dmub_wb_cmd_dpia_notification dpia_notification;
	};
};

/**
 * DMUB fiwmwawe vewsion hewpew macwo - usefuw fow checking if the vewsion
 * of a fiwmwawe to know if featuwe ow functionawity is suppowted ow pwesent.
 */
#define DMUB_FW_VEWSION(majow, minow, wevision) \
	((((majow) & 0xFF) << 24) | (((minow) & 0xFF) << 16) | (((wevision) & 0xFF) << 8))

/**
 * dmub_swv_cweate() - cweates the DMUB sewvice.
 * @dmub: the dmub sewvice
 * @pawams: cweation pawametews fow the sewvice
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_cweate(stwuct dmub_swv *dmub,
				 const stwuct dmub_swv_cweate_pawams *pawams);

/**
 * dmub_swv_destwoy() - destwoys the DMUB sewvice.
 * @dmub: the dmub sewvice
 */
void dmub_swv_destwoy(stwuct dmub_swv *dmub);

/**
 * dmub_swv_cawc_wegion_info() - wetweives wegion info fwom the dmub sewvice
 * @dmub: the dmub sewvice
 * @pawams: pawametews used to cawcuwate wegion wocations
 * @info_out: the output wegion info fwom dmub
 *
 * Cawcuwates the base and top addwess fow aww wewevant dmub wegions
 * using the pawametews given (if any).
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status
dmub_swv_cawc_wegion_info(stwuct dmub_swv *dmub,
			  const stwuct dmub_swv_wegion_pawams *pawams,
			  stwuct dmub_swv_wegion_info *out);

/**
 * dmub_swv_cawc_wegion_info() - wetweives fb info fwom the dmub sewvice
 * @dmub: the dmub sewvice
 * @pawams: pawametews used to cawcuwate fb wocations
 * @info_out: the output fb info fwom dmub
 *
 * Cawcuwates the base and top addwess fow aww wewevant dmub wegions
 * using the pawametews given (if any).
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_cawc_mem_info(stwuct dmub_swv *dmub,
				       const stwuct dmub_swv_memowy_pawams *pawams,
				       stwuct dmub_swv_fb_info *out);

/**
 * dmub_swv_has_hw_suppowt() - wetuwns hw suppowt state fow dmcub
 * @dmub: the dmub sewvice
 * @is_suppowted: hw suppowt state
 *
 * Quewies the hawdwawe fow DMCUB suppowt and wetuwns the wesuwt.
 *
 * Can be cawwed befowe dmub_swv_hw_init().
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_has_hw_suppowt(stwuct dmub_swv *dmub,
					 boow *is_suppowted);

/**
 * dmub_swv_is_hw_init() - wetuwns hawdwawe init state
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_is_hw_init(stwuct dmub_swv *dmub, boow *is_hw_init);

/**
 * dmub_swv_hw_init() - initiawizes the undewwying DMUB hawdwawe
 * @dmub: the dmub sewvice
 * @pawams: pawams fow hawdwawe initiawization
 *
 * Wesets the DMUB hawdwawe and pewfowms backdoow woading of the
 * wequiwed cache wegions based on the input fwamebuffew wegions.
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_NO_CTX - dmcub context not initiawized
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_hw_init(stwuct dmub_swv *dmub,
				  const stwuct dmub_swv_hw_pawams *pawams);

/**
 * dmub_swv_hw_weset() - puts the DMUB hawdwawe in weset state if initiawized
 * @dmub: the dmub sewvice
 *
 * Befowe destwoying the DMUB sewvice ow weweasing the backing fwamebuffew
 * memowy we'ww need to put the DMCUB into weset fiwst.
 *
 * A subsequent caww to dmub_swv_hw_init() wiww we-enabwe the DMCUB.
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_hw_weset(stwuct dmub_swv *dmub);

/**
 * dmub_swv_sync_inbox1() - sync sw state with hw state
 * @dmub: the dmub sewvice
 *
 * Sync sw state with hw state when wesume fwom S0i3
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_sync_inbox1(stwuct dmub_swv *dmub);

/**
 * dmub_swv_cmd_queue() - queues a command to the DMUB
 * @dmub: the dmub sewvice
 * @cmd: the command to queue
 *
 * Queues a command to the DMUB sewvice but does not begin execution
 * immediatewy.
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_QUEUE_FUWW - no wemaining woom in queue
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_cmd_queue(stwuct dmub_swv *dmub,
				    const union dmub_wb_cmd *cmd);

/**
 * dmub_swv_cmd_execute() - Executes a queued sequence to the dmub
 * @dmub: the dmub sewvice
 *
 * Begins execution of queued commands on the dmub.
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_cmd_execute(stwuct dmub_swv *dmub);

/**
 * dmub_swv_wait_fow_hw_pww_up() - Waits fow fiwmwawe hawdwawe powew up is compweted
 * @dmub: the dmub sewvice
 * @timeout_us: the maximum numbew of micwoseconds to wait
 *
 * Waits untiw fiwmwawe hawdwawe is powewed up. The maximum
 * wait time is given in micwoseconds to pwevent spinning fowevew.
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_TIMEOUT - timed out
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_wait_fow_hw_pww_up(stwuct dmub_swv *dmub,
					     uint32_t timeout_us);

boow dmub_swv_is_hw_pww_up(stwuct dmub_swv *dmub);

/**
 * dmub_swv_wait_fow_auto_woad() - Waits fow fiwmwawe auto woad to compwete
 * @dmub: the dmub sewvice
 * @timeout_us: the maximum numbew of micwoseconds to wait
 *
 * Waits untiw fiwmwawe has been autowoaded by the DMCUB. The maximum
 * wait time is given in micwoseconds to pwevent spinning fowevew.
 *
 * On ASICs without fiwmwawe autowoad suppowt this function wiww wetuwn
 * immediatewy.
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_TIMEOUT - wait fow phy init timed out
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_wait_fow_auto_woad(stwuct dmub_swv *dmub,
					     uint32_t timeout_us);

/**
 * dmub_swv_wait_fow_phy_init() - Waits fow DMUB PHY init to compwete
 * @dmub: the dmub sewvice
 * @timeout_us: the maximum numbew of micwoseconds to wait
 *
 * Waits untiw the PHY has been initiawized by the DMUB. The maximum
 * wait time is given in micwoseconds to pwevent spinning fowevew.
 *
 * On ASICs without PHY init suppowt this function wiww wetuwn
 * immediatewy.
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_TIMEOUT - wait fow phy init timed out
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_wait_fow_phy_init(stwuct dmub_swv *dmub,
					    uint32_t timeout_us);

/**
 * dmub_swv_wait_fow_idwe() - Waits fow the DMUB to be idwe
 * @dmub: the dmub sewvice
 * @timeout_us: the maximum numbew of micwoseconds to wait
 *
 * Waits untiw the DMUB buffew is empty and aww commands have
 * finished pwocessing. The maximum wait time is given in
 * micwoseconds to pwevent spinning fowevew.
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_TIMEOUT - wait fow buffew to fwush timed out
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_wait_fow_idwe(stwuct dmub_swv *dmub,
					uint32_t timeout_us);

/**
 * dmub_swv_send_gpint_command() - Sends a GPINT based command.
 * @dmub: the dmub sewvice
 * @command_code: the command code to send
 * @pawam: the command pawametew to send
 * @timeout_us: the maximum numbew of micwoseconds to wait
 *
 * Sends a command via the genewaw puwpose intewwupt (GPINT).
 * Waits fow the numbew of micwoseconds specified by timeout_us
 * fow the command ACK befowe wetuwning.
 *
 * Can be cawwed aftew softwawe initiawization.
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_TIMEOUT - wait fow ACK timed out
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status
dmub_swv_send_gpint_command(stwuct dmub_swv *dmub,
			    enum dmub_gpint_command command_code,
			    uint16_t pawam, uint32_t timeout_us);

/**
 * dmub_swv_get_gpint_wesponse() - Quewies the GPINT wesponse.
 * @dmub: the dmub sewvice
 * @wesponse: the wesponse fow the wast GPINT
 *
 * Wetuwns the wesponse code fow the wast GPINT intewwupt.
 *
 * Can be cawwed aftew softwawe initiawization.
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_get_gpint_wesponse(stwuct dmub_swv *dmub,
					     uint32_t *wesponse);

/**
 * dmub_swv_get_gpint_dataout() - Quewies the GPINT DATAOUT.
 * @dmub: the dmub sewvice
 * @dataout: the data fow the GPINT DATAOUT
 *
 * Wetuwns the wesponse code fow the wast GPINT DATAOUT intewwupt.
 *
 * Can be cawwed aftew softwawe initiawization.
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - unspecified ewwow
 */
enum dmub_status dmub_swv_get_gpint_dataout(stwuct dmub_swv *dmub,
					     uint32_t *dataout);

/**
 * dmub_fwush_buffew_mem() - Wead back entiwe fwame buffew wegion.
 * This ensuwes that the wwite fwom x86 has been fwushed and wiww not
 * hang the DMCUB.
 * @fb: fwame buffew to fwush
 *
 * Can be cawwed aftew softwawe initiawization.
 */
void dmub_fwush_buffew_mem(const stwuct dmub_fb *fb);

/**
 * dmub_swv_get_fw_boot_status() - Wetuwns the DMUB boot status bits.
 *
 * @dmub: the dmub sewvice
 * @status: out pointew fow fiwmwawe status
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - unspecified ewwow, unsuppowted
 */
enum dmub_status dmub_swv_get_fw_boot_status(stwuct dmub_swv *dmub,
					     union dmub_fw_boot_status *status);

enum dmub_status dmub_swv_get_fw_boot_option(stwuct dmub_swv *dmub,
					     union dmub_fw_boot_options *option);

enum dmub_status dmub_swv_cmd_with_wepwy_data(stwuct dmub_swv *dmub,
					      union dmub_wb_cmd *cmd);

enum dmub_status dmub_swv_set_skip_panew_powew_sequence(stwuct dmub_swv *dmub,
					     boow skip);

boow dmub_swv_get_outbox0_msg(stwuct dmub_swv *dmub, stwuct dmcub_twace_buf_entwy *entwy);

boow dmub_swv_get_diagnostic_data(stwuct dmub_swv *dmub, stwuct dmub_diagnostic_data *diag_data);

boow dmub_swv_shouwd_detect(stwuct dmub_swv *dmub);

/**
 * dmub_swv_send_inbox0_cmd() - Send command to DMUB using INBOX0
 * @dmub: the dmub sewvice
 * @data: the data to be sent in the INBOX0 command
 *
 * Send command by wwiting diwectwy to INBOX0 WPTW
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - hw_init fawse ow hw function does not exist
 */
enum dmub_status dmub_swv_send_inbox0_cmd(stwuct dmub_swv *dmub, union dmub_inbox0_data_wegistew data);

/**
 * dmub_swv_wait_fow_inbox0_ack() - wait fow DMUB to ACK INBOX0 command
 * @dmub: the dmub sewvice
 * @timeout_us: the maximum numbew of micwoseconds to wait
 *
 * Wait fow DMUB to ACK the INBOX0 message
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - hw_init fawse ow hw function does not exist
 *   DMUB_STATUS_TIMEOUT - wait fow ack timed out
 */
enum dmub_status dmub_swv_wait_fow_inbox0_ack(stwuct dmub_swv *dmub, uint32_t timeout_us);

/**
 * dmub_swv_wait_fow_inbox0_ack() - cweaw ACK wegistew fow INBOX0
 * @dmub: the dmub sewvice
 *
 * Cweaw ACK wegistew fow INBOX0
 *
 * Wetuwn:
 *   DMUB_STATUS_OK - success
 *   DMUB_STATUS_INVAWID - hw_init fawse ow hw function does not exist
 */
enum dmub_status dmub_swv_cweaw_inbox0_ack(stwuct dmub_swv *dmub);

/**
 * dmub_swv_subvp_save_suwf_addw() - Save pwimawy and meta addwess fow subvp on each fwip
 * @dmub: The dmub sewvice
 * @addw: The suwface addwess to be pwogwammed on the cuwwent fwip
 * @subvp_index: Index of subvp pipe, indicates which subvp pipe the addwess shouwd be saved fow
 *
 * Function to save the suwface fwip addw into scwatch wegistews. This is to fix a wace condition
 * between FW and dwivew weading / wwiting to the suwface addwess at the same time. This is
 * wequiwed because thewe is no EAWWIEST_IN_USE_META.
 *
 * Wetuwn:
 *   void
 */
void dmub_swv_subvp_save_suwf_addw(stwuct dmub_swv *dmub, const stwuct dc_pwane_addwess *addw, uint8_t subvp_index);

/**
 * dmub_swv_set_powew_state() - Twack DC powew state in dmub_swv
 * @dmub: The dmub sewvice
 * @powew_state: DC powew state setting
 *
 * Stowe DC powew state in dmub_swv.  If dmub_swv is in D3, then don't send messages to DMUB
 *
 * Wetuwn:
 *   void
 */
void dmub_swv_set_powew_state(stwuct dmub_swv *dmub, enum dmub_swv_powew_state_type dmub_swv_powew_state);

#if defined(__cpwuspwus)
}
#endif

#endif /* _DMUB_SWV_H_ */
