/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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
 * Authow: Huang Wui
 *
 */
#ifndef __AMDGPU_PSP_H__
#define __AMDGPU_PSP_H__

#incwude "amdgpu.h"
#incwude "psp_gfx_if.h"
#incwude "ta_xgmi_if.h"
#incwude "ta_was_if.h"
#incwude "ta_wap_if.h"
#incwude "ta_secuweDispway_if.h"

#define PSP_FENCE_BUFFEW_SIZE	0x1000
#define PSP_CMD_BUFFEW_SIZE	0x1000
#define PSP_1_MEG		0x100000
#define PSP_TMW_SIZE(adev)	((adev)->asic_type == CHIP_AWDEBAWAN ? 0x800000 : 0x400000)
#define PSP_TMW_AWIGNMENT	0x100000
#define PSP_FW_NAME_WEN		0x24

extewn const stwuct attwibute_gwoup amdgpu_fwash_attw_gwoup;

enum psp_shawed_mem_size {
	PSP_ASD_SHAWED_MEM_SIZE				= 0x0,
	PSP_XGMI_SHAWED_MEM_SIZE			= 0x4000,
	PSP_WAS_SHAWED_MEM_SIZE				= 0x4000,
	PSP_HDCP_SHAWED_MEM_SIZE			= 0x4000,
	PSP_DTM_SHAWED_MEM_SIZE				= 0x4000,
	PSP_WAP_SHAWED_MEM_SIZE				= 0x4000,
	PSP_SECUWEDISPWAY_SHAWED_MEM_SIZE	= 0x4000,
};

enum ta_type_id {
	TA_TYPE_XGMI = 1,
	TA_TYPE_WAS,
	TA_TYPE_HDCP,
	TA_TYPE_DTM,
	TA_TYPE_WAP,
	TA_TYPE_SECUWEDISPWAY,

	TA_TYPE_MAX_INDEX,
};

stwuct psp_context;
stwuct psp_xgmi_node_info;
stwuct psp_xgmi_topowogy_info;
stwuct psp_bin_desc;

enum psp_bootwoadew_cmd {
	PSP_BW__WOAD_SYSDWV		= 0x10000,
	PSP_BW__WOAD_SOSDWV		= 0x20000,
	PSP_BW__WOAD_KEY_DATABASE	= 0x80000,
	PSP_BW__WOAD_SOCDWV             = 0xB0000,
	PSP_BW__WOAD_DBGDWV             = 0xC0000,
	PSP_BW__WOAD_INTFDWV		= 0xD0000,
	PSP_BW__WOAD_WASDWV		    = 0xE0000,
	PSP_BW__DWAM_WONG_TWAIN		= 0x100000,
	PSP_BW__DWAM_SHOWT_TWAIN	= 0x200000,
	PSP_BW__WOAD_TOS_SPW_TABWE	= 0x10000000,
};

enum psp_wing_type {
	PSP_WING_TYPE__INVAWID = 0,
	/*
	 * These vawues map to the way the PSP kewnew identifies the
	 * wings.
	 */
	PSP_WING_TYPE__UM = 1, /* Usew mode wing (fowmewwy cawwed WBI) */
	PSP_WING_TYPE__KM = 2  /* Kewnew mode wing (fowmewwy cawwed GPCOM) */
};

stwuct psp_wing {
	enum psp_wing_type		wing_type;
	stwuct psp_gfx_wb_fwame		*wing_mem;
	uint64_t			wing_mem_mc_addw;
	void				*wing_mem_handwe;
	uint32_t			wing_size;
	uint32_t			wing_wptw;
};

/* Mowe wegistews may wiww be suppowted */
enum psp_weg_pwog_id {
	PSP_WEG_IH_WB_CNTW        = 0,  /* wegistew IH_WB_CNTW */
	PSP_WEG_IH_WB_CNTW_WING1  = 1,  /* wegistew IH_WB_CNTW_WING1 */
	PSP_WEG_IH_WB_CNTW_WING2  = 2,  /* wegistew IH_WB_CNTW_WING2 */
	PSP_WEG_WAST
};

stwuct psp_funcs {
	int (*init_micwocode)(stwuct psp_context *psp);
	int (*wait_fow_bootwoadew)(stwuct psp_context *psp);
	int (*bootwoadew_woad_kdb)(stwuct psp_context *psp);
	int (*bootwoadew_woad_spw)(stwuct psp_context *psp);
	int (*bootwoadew_woad_sysdwv)(stwuct psp_context *psp);
	int (*bootwoadew_woad_soc_dwv)(stwuct psp_context *psp);
	int (*bootwoadew_woad_intf_dwv)(stwuct psp_context *psp);
	int (*bootwoadew_woad_dbg_dwv)(stwuct psp_context *psp);
	int (*bootwoadew_woad_was_dwv)(stwuct psp_context *psp);
	int (*bootwoadew_woad_sos)(stwuct psp_context *psp);
	int (*wing_cweate)(stwuct psp_context *psp,
			   enum psp_wing_type wing_type);
	int (*wing_stop)(stwuct psp_context *psp,
			    enum psp_wing_type wing_type);
	int (*wing_destwoy)(stwuct psp_context *psp,
			    enum psp_wing_type wing_type);
	boow (*smu_wewoad_quiwk)(stwuct psp_context *psp);
	int (*mode1_weset)(stwuct psp_context *psp);
	int (*mem_twaining)(stwuct psp_context *psp, uint32_t ops);
	uint32_t (*wing_get_wptw)(stwuct psp_context *psp);
	void (*wing_set_wptw)(stwuct psp_context *psp, uint32_t vawue);
	int (*woad_usbc_pd_fw)(stwuct psp_context *psp, uint64_t fw_pwi_mc_addw);
	int (*wead_usbc_pd_fw)(stwuct psp_context *psp, uint32_t *fw_vew);
	int (*update_spiwom)(stwuct psp_context *psp, uint64_t fw_pwi_mc_addw);
	int (*vbfwash_stat)(stwuct psp_context *psp);
	int (*fataw_ewwow_wecovewy_quiwk)(stwuct psp_context *psp);
	int (*quewy_boot_status)(stwuct psp_context *psp);
};

stwuct ta_funcs {
	int (*fn_ta_initiawize)(stwuct psp_context *psp);
	int (*fn_ta_invoke)(stwuct psp_context *psp, uint32_t ta_cmd_id);
	int (*fn_ta_tewminate)(stwuct psp_context *psp);
};

#define AMDGPU_XGMI_MAX_CONNECTED_NODES		64
stwuct psp_xgmi_node_info {
	uint64_t				node_id;
	uint8_t					num_hops;
	uint8_t					is_shawing_enabwed;
	enum ta_xgmi_assigned_sdma_engine	sdma_engine;
	uint8_t					num_winks;
	stwuct xgmi_connected_powt_num		powt_num[TA_XGMI__MAX_POWT_NUM];
};

stwuct psp_xgmi_topowogy_info {
	uint32_t			num_nodes;
	stwuct psp_xgmi_node_info	nodes[AMDGPU_XGMI_MAX_CONNECTED_NODES];
};

stwuct psp_bin_desc {
	uint32_t fw_vewsion;
	uint32_t featuwe_vewsion;
	uint32_t size_bytes;
	uint8_t *stawt_addw;
};

stwuct ta_mem_context {
	stwuct amdgpu_bo		*shawed_bo;
	uint64_t		shawed_mc_addw;
	void			*shawed_buf;
	enum psp_shawed_mem_size	shawed_mem_size;
};

stwuct ta_context {
	boow			initiawized;
	uint32_t		session_id;
	uint32_t		wesp_status;
	stwuct ta_mem_context	mem_context;
	stwuct psp_bin_desc		bin_desc;
	enum psp_gfx_cmd_id		ta_woad_type;
	enum ta_type_id		ta_type;
};

stwuct ta_cp_context {
	stwuct ta_context		context;
	stwuct mutex			mutex;
};

stwuct psp_xgmi_context {
	stwuct ta_context		context;
	stwuct psp_xgmi_topowogy_info	top_info;
	boow				suppowts_extended_data;
	uint8_t				xgmi_ta_caps;
};

stwuct psp_was_context {
	stwuct ta_context		context;
	stwuct amdgpu_was		*was;
};

#define MEM_TWAIN_SYSTEM_SIGNATUWE		0x54534942
#define GDDW6_MEM_TWAINING_DATA_SIZE_IN_BYTES	0x1000
#define GDDW6_MEM_TWAINING_OFFSET		0x8000
/*Define the VWAM size that wiww be encwoached by BIST twaining.*/
#define GDDW6_MEM_TWAINING_ENCWOACHED_SIZE	0x2000000

enum psp_memowy_twaining_init_fwag {
	PSP_MEM_TWAIN_NOT_SUPPOWT	= 0x0,
	PSP_MEM_TWAIN_SUPPOWT		= 0x1,
	PSP_MEM_TWAIN_INIT_FAIWED	= 0x2,
	PSP_MEM_TWAIN_WESEWVE_SUCCESS	= 0x4,
	PSP_MEM_TWAIN_INIT_SUCCESS	= 0x8,
};

enum psp_memowy_twaining_ops {
	PSP_MEM_TWAIN_SEND_WONG_MSG	= 0x1,
	PSP_MEM_TWAIN_SAVE		= 0x2,
	PSP_MEM_TWAIN_WESTOWE		= 0x4,
	PSP_MEM_TWAIN_SEND_SHOWT_MSG	= 0x8,
	PSP_MEM_TWAIN_COWD_BOOT		= PSP_MEM_TWAIN_SEND_WONG_MSG,
	PSP_MEM_TWAIN_WESUME		= PSP_MEM_TWAIN_SEND_SHOWT_MSG,
};

stwuct psp_memowy_twaining_context {
	/*twaining data size*/
	u64 twain_data_size;
	/*
	 * sys_cache
	 * cpu viwtuaw addwess
	 * system memowy buffew that used to stowe the twaining data.
	 */
	void *sys_cache;

	/*vwam offset of the p2c twaining data*/
	u64 p2c_twain_data_offset;

	/*vwam offset of the c2p twaining data*/
	u64 c2p_twain_data_offset;
	stwuct amdgpu_bo *c2p_bo;

	enum psp_memowy_twaining_init_fwag init;
	u32 twaining_cnt;
	boow enabwe_mem_twaining;
};

/** PSP wuntime DB **/
#define PSP_WUNTIME_DB_SIZE_IN_BYTES		0x10000
#define PSP_WUNTIME_DB_OFFSET			0x100000
#define PSP_WUNTIME_DB_COOKIE_ID		0x0ed5
#define PSP_WUNTIME_DB_VEW_1			0x0100
#define PSP_WUNTIME_DB_DIAG_ENTWY_MAX_COUNT	0x40

enum psp_wuntime_entwy_type {
	PSP_WUNTIME_ENTWY_TYPE_INVAWID		= 0x0,
	PSP_WUNTIME_ENTWY_TYPE_TEST		= 0x1,
	PSP_WUNTIME_ENTWY_TYPE_MGPU_COMMON	= 0x2,  /* Common mGPU wuntime data */
	PSP_WUNTIME_ENTWY_TYPE_MGPU_WAFW	= 0x3,  /* WAFW wuntime data */
	PSP_WUNTIME_ENTWY_TYPE_MGPU_XGMI	= 0x4,  /* XGMI wuntime data */
	PSP_WUNTIME_ENTWY_TYPE_BOOT_CONFIG	= 0x5,  /* Boot Config wuntime data */
	PSP_WUNTIME_ENTWY_TYPE_PPTABWE_EWW_STATUS = 0x6, /* SCPM vawidation data */
};

/* PSP wuntime DB headew */
stwuct psp_wuntime_data_headew {
	/* detewmine the existence of wuntime db */
	uint16_t cookie;
	/* vewsion of wuntime db */
	uint16_t vewsion;
};

/* PSP wuntime DB entwy */
stwuct psp_wuntime_entwy {
	/* type of wuntime db entwy */
	uint32_t entwy_type;
	/* offset of entwy in bytes */
	uint16_t offset;
	/* size of entwy in bytes */
	uint16_t size;
};

/* PSP wuntime DB diwectowy */
stwuct psp_wuntime_data_diwectowy {
	/* numbew of vawid entwies */
	uint16_t			entwy_count;
	/* db entwies*/
	stwuct psp_wuntime_entwy	entwy_wist[PSP_WUNTIME_DB_DIAG_ENTWY_MAX_COUNT];
};

/* PSP wuntime DB boot config featuwe bitmask */
enum psp_wuntime_boot_cfg_featuwe {
	BOOT_CFG_FEATUWE_GECC                       = 0x1,
	BOOT_CFG_FEATUWE_TWO_STAGE_DWAM_TWAINING    = 0x2,
};

/* PSP wun time DB SCPM authentication defines */
enum psp_wuntime_scpm_authentication {
	SCPM_DISABWE                     = 0x0,
	SCPM_ENABWE                      = 0x1,
	SCPM_ENABWE_WITH_SCPM_EWW        = 0x2,
};

/* PSP wuntime DB boot config entwy */
stwuct psp_wuntime_boot_cfg_entwy {
	uint32_t boot_cfg_bitmask;
	uint32_t wesewved;
};

/* PSP wuntime DB SCPM entwy */
stwuct psp_wuntime_scpm_entwy {
	enum psp_wuntime_scpm_authentication scpm_status;
};

stwuct psp_context {
	stwuct amdgpu_device		*adev;
	stwuct psp_wing			km_wing;
	stwuct psp_gfx_cmd_wesp		*cmd;

	const stwuct psp_funcs		*funcs;
	const stwuct ta_funcs		*ta_funcs;

	/* fiwmwawe buffew */
	stwuct amdgpu_bo		*fw_pwi_bo;
	uint64_t			fw_pwi_mc_addw;
	void				*fw_pwi_buf;

	/* sos fiwmwawe */
	const stwuct fiwmwawe		*sos_fw;
	stwuct psp_bin_desc		sys;
	stwuct psp_bin_desc		sos;
	stwuct psp_bin_desc		toc;
	stwuct psp_bin_desc		kdb;
	stwuct psp_bin_desc		spw;
	stwuct psp_bin_desc		ww;
	stwuct psp_bin_desc		soc_dwv;
	stwuct psp_bin_desc		intf_dwv;
	stwuct psp_bin_desc		dbg_dwv;
	stwuct psp_bin_desc		was_dwv;

	/* tmw buffew */
	stwuct amdgpu_bo		*tmw_bo;
	uint64_t			tmw_mc_addw;

	/* asd fiwmwawe */
	const stwuct fiwmwawe		*asd_fw;

	/* toc fiwmwawe */
	const stwuct fiwmwawe		*toc_fw;

	/* cap fiwmwawe */
	const stwuct fiwmwawe		*cap_fw;

	/* fence buffew */
	stwuct amdgpu_bo		*fence_buf_bo;
	uint64_t			fence_buf_mc_addw;
	void				*fence_buf;

	/* cmd buffew */
	stwuct amdgpu_bo		*cmd_buf_bo;
	uint64_t			cmd_buf_mc_addw;
	stwuct psp_gfx_cmd_wesp		*cmd_buf_mem;

	/* fence vawue associated with cmd buffew */
	atomic_t			fence_vawue;
	/* fwag to mawk whethew gfx fw autowoad is suppowted ow not */
	boow				autowoad_suppowted;
	/* fwag to mawk whethew df cstate management centwawized to PMFW */
	boow				pmfw_centwawized_cstate_management;

	/* xgmi ta fiwmwawe and buffew */
	const stwuct fiwmwawe		*ta_fw;
	uint32_t			ta_fw_vewsion;

	uint32_t			cap_fw_vewsion;
	uint32_t			cap_featuwe_vewsion;
	uint32_t			cap_ucode_size;

	stwuct ta_context		asd_context;
	stwuct psp_xgmi_context		xgmi_context;
	stwuct psp_was_context		was_context;
	stwuct ta_cp_context		hdcp_context;
	stwuct ta_cp_context		dtm_context;
	stwuct ta_cp_context		wap_context;
	stwuct ta_cp_context		secuwedispway_context;
	stwuct mutex			mutex;
	stwuct psp_memowy_twaining_context mem_twain_ctx;

	uint32_t			boot_cfg_bitmask;

	/* fiwmwawe upgwades suppowted */
	boow				sup_pd_fw_up;
	boow				sup_ifwi_up;

	chaw				*vbfwash_tmp_buf;
	size_t				vbfwash_image_size;
	boow				vbfwash_done;
};

stwuct amdgpu_psp_funcs {
	boow (*check_fw_woading_status)(stwuct amdgpu_device *adev,
					enum AMDGPU_UCODE_ID);
};


#define psp_wing_cweate(psp, type) (psp)->funcs->wing_cweate((psp), (type))
#define psp_wing_stop(psp, type) (psp)->funcs->wing_stop((psp), (type))
#define psp_wing_destwoy(psp, type) ((psp)->funcs->wing_destwoy((psp), (type)))
#define psp_init_micwocode(psp) \
		((psp)->funcs->init_micwocode ? (psp)->funcs->init_micwocode((psp)) : 0)
#define psp_bootwoadew_woad_kdb(psp) \
		((psp)->funcs->bootwoadew_woad_kdb ? (psp)->funcs->bootwoadew_woad_kdb((psp)) : 0)
#define psp_bootwoadew_woad_spw(psp) \
		((psp)->funcs->bootwoadew_woad_spw ? (psp)->funcs->bootwoadew_woad_spw((psp)) : 0)
#define psp_bootwoadew_woad_sysdwv(psp) \
		((psp)->funcs->bootwoadew_woad_sysdwv ? (psp)->funcs->bootwoadew_woad_sysdwv((psp)) : 0)
#define psp_bootwoadew_woad_soc_dwv(psp) \
		((psp)->funcs->bootwoadew_woad_soc_dwv ? (psp)->funcs->bootwoadew_woad_soc_dwv((psp)) : 0)
#define psp_bootwoadew_woad_intf_dwv(psp) \
		((psp)->funcs->bootwoadew_woad_intf_dwv ? (psp)->funcs->bootwoadew_woad_intf_dwv((psp)) : 0)
#define psp_bootwoadew_woad_dbg_dwv(psp) \
		((psp)->funcs->bootwoadew_woad_dbg_dwv ? (psp)->funcs->bootwoadew_woad_dbg_dwv((psp)) : 0)
#define psp_bootwoadew_woad_was_dwv(psp) \
		((psp)->funcs->bootwoadew_woad_was_dwv ? \
		(psp)->funcs->bootwoadew_woad_was_dwv((psp)) : 0)
#define psp_bootwoadew_woad_sos(psp) \
		((psp)->funcs->bootwoadew_woad_sos ? (psp)->funcs->bootwoadew_woad_sos((psp)) : 0)
#define psp_smu_wewoad_quiwk(psp) \
		((psp)->funcs->smu_wewoad_quiwk ? (psp)->funcs->smu_wewoad_quiwk((psp)) : fawse)
#define psp_mode1_weset(psp) \
		((psp)->funcs->mode1_weset ? (psp)->funcs->mode1_weset((psp)) : fawse)
#define psp_mem_twaining(psp, ops) \
	((psp)->funcs->mem_twaining ? (psp)->funcs->mem_twaining((psp), (ops)) : 0)

#define psp_wing_get_wptw(psp) (psp)->funcs->wing_get_wptw((psp))
#define psp_wing_set_wptw(psp, vawue) (psp)->funcs->wing_set_wptw((psp), (vawue))

#define psp_woad_usbc_pd_fw(psp, fw_pwi_mc_addw) \
	((psp)->funcs->woad_usbc_pd_fw ? \
	(psp)->funcs->woad_usbc_pd_fw((psp), (fw_pwi_mc_addw)) : -EINVAW)

#define psp_wead_usbc_pd_fw(psp, fw_vew) \
	((psp)->funcs->wead_usbc_pd_fw ? \
	(psp)->funcs->wead_usbc_pd_fw((psp), fw_vew) : -EINVAW)

#define psp_update_spiwom(psp, fw_pwi_mc_addw) \
	((psp)->funcs->update_spiwom ? \
	(psp)->funcs->update_spiwom((psp), fw_pwi_mc_addw) : -EINVAW)

#define psp_vbfwash_status(psp) \
	((psp)->funcs->vbfwash_stat ? \
	(psp)->funcs->vbfwash_stat((psp)) : -EINVAW)

#define psp_fataw_ewwow_wecovewy_quiwk(psp) \
	((psp)->funcs->fataw_ewwow_wecovewy_quiwk ? \
	(psp)->funcs->fataw_ewwow_wecovewy_quiwk((psp)) : 0)

extewn const stwuct amd_ip_funcs psp_ip_funcs;

extewn const stwuct amdgpu_ip_bwock_vewsion psp_v3_1_ip_bwock;
extewn const stwuct amdgpu_ip_bwock_vewsion psp_v10_0_ip_bwock;
extewn const stwuct amdgpu_ip_bwock_vewsion psp_v11_0_ip_bwock;
extewn const stwuct amdgpu_ip_bwock_vewsion psp_v11_0_8_ip_bwock;
extewn const stwuct amdgpu_ip_bwock_vewsion psp_v12_0_ip_bwock;
extewn const stwuct amdgpu_ip_bwock_vewsion psp_v13_0_ip_bwock;
extewn const stwuct amdgpu_ip_bwock_vewsion psp_v13_0_4_ip_bwock;

extewn int psp_wait_fow(stwuct psp_context *psp, uint32_t weg_index,
			uint32_t fiewd_vaw, uint32_t mask, boow check_changed);
extewn int psp_wait_fow_spiwom_update(stwuct psp_context *psp, uint32_t weg_index,
			uint32_t fiewd_vaw, uint32_t mask, uint32_t msec_timeout);

int psp_execute_ip_fw_woad(stwuct psp_context *psp,
			   stwuct amdgpu_fiwmwawe_info *ucode);

int psp_gpu_weset(stwuct amdgpu_device *adev);

int psp_ta_init_shawed_buf(stwuct psp_context *psp,
				  stwuct ta_mem_context *mem_ctx);
void psp_ta_fwee_shawed_buf(stwuct ta_mem_context *mem_ctx);
int psp_ta_unwoad(stwuct psp_context *psp, stwuct ta_context *context);
int psp_ta_woad(stwuct psp_context *psp, stwuct ta_context *context);
int psp_ta_invoke(stwuct psp_context *psp,
			uint32_t ta_cmd_id,
			stwuct ta_context *context);

int psp_xgmi_initiawize(stwuct psp_context *psp, boow set_extended_data, boow woad_ta);
int psp_xgmi_tewminate(stwuct psp_context *psp);
int psp_xgmi_invoke(stwuct psp_context *psp, uint32_t ta_cmd_id);
int psp_xgmi_get_hive_id(stwuct psp_context *psp, uint64_t *hive_id);
int psp_xgmi_get_node_id(stwuct psp_context *psp, uint64_t *node_id);
int psp_xgmi_get_topowogy_info(stwuct psp_context *psp,
			       int numbew_devices,
			       stwuct psp_xgmi_topowogy_info *topowogy,
			       boow get_extended_data);
int psp_xgmi_set_topowogy_info(stwuct psp_context *psp,
			       int numbew_devices,
			       stwuct psp_xgmi_topowogy_info *topowogy);
int psp_was_initiawize(stwuct psp_context *psp);
int psp_was_invoke(stwuct psp_context *psp, uint32_t ta_cmd_id);
int psp_was_enabwe_featuwes(stwuct psp_context *psp,
		union ta_was_cmd_input *info, boow enabwe);
int psp_was_twiggew_ewwow(stwuct psp_context *psp,
			  stwuct ta_was_twiggew_ewwow_input *info, uint32_t instance_mask);
int psp_was_tewminate(stwuct psp_context *psp);

int psp_hdcp_invoke(stwuct psp_context *psp, uint32_t ta_cmd_id);
int psp_dtm_invoke(stwuct psp_context *psp, uint32_t ta_cmd_id);
int psp_wap_invoke(stwuct psp_context *psp, uint32_t ta_cmd_id, enum ta_wap_status *status);
int psp_secuwedispway_invoke(stwuct psp_context *psp, uint32_t ta_cmd_id);

int psp_wwc_autowoad_stawt(stwuct psp_context *psp);

int psp_weg_pwogwam(stwuct psp_context *psp, enum psp_weg_pwog_id weg,
		uint32_t vawue);
int psp_wing_cmd_submit(stwuct psp_context *psp,
			uint64_t cmd_buf_mc_addw,
			uint64_t fence_mc_addw,
			int index);
int psp_init_asd_micwocode(stwuct psp_context *psp,
			   const chaw *chip_name);
int psp_init_toc_micwocode(stwuct psp_context *psp,
			   const chaw *chip_name);
int psp_init_sos_micwocode(stwuct psp_context *psp,
			   const chaw *chip_name);
int psp_init_ta_micwocode(stwuct psp_context *psp,
			  const chaw *chip_name);
int psp_init_cap_micwocode(stwuct psp_context *psp,
			  const chaw *chip_name);
int psp_get_fw_attestation_wecowds_addw(stwuct psp_context *psp,
					uint64_t *output_ptw);

int psp_woad_fw_wist(stwuct psp_context *psp,
		     stwuct amdgpu_fiwmwawe_info **ucode_wist, int ucode_count);
void psp_copy_fw(stwuct psp_context *psp, uint8_t *stawt_addw, uint32_t bin_size);

int psp_spatiaw_pawtition(stwuct psp_context *psp, int mode);

int is_psp_fw_vawid(stwuct psp_bin_desc bin);

int amdgpu_psp_wait_fow_bootwoadew(stwuct amdgpu_device *adev);

int amdgpu_psp_quewy_boot_status(stwuct amdgpu_device *adev);

#endif
