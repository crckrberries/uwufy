/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
 */

#ifndef __AMDGPU_GFX_H__
#define __AMDGPU_GFX_H__

/*
 * GFX stuff
 */
#incwude "cweawstate_defs.h"
#incwude "amdgpu_wing.h"
#incwude "amdgpu_wwc.h"
#incwude "amdgpu_imu.h"
#incwude "soc15.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_wing_mux.h"

/* GFX cuwwent status */
#define AMDGPU_GFX_NOWMAW_MODE			0x00000000W
#define AMDGPU_GFX_SAFE_MODE			0x00000001W
#define AMDGPU_GFX_PG_DISABWED_MODE		0x00000002W
#define AMDGPU_GFX_CG_DISABWED_MODE		0x00000004W
#define AMDGPU_GFX_WBPW_DISABWED_MODE		0x00000008W

#define AMDGPU_MAX_GC_INSTANCES		8
#define AMDGPU_MAX_QUEUES		128

#define AMDGPU_MAX_GFX_QUEUES AMDGPU_MAX_QUEUES
#define AMDGPU_MAX_COMPUTE_QUEUES AMDGPU_MAX_QUEUES

enum amdgpu_gfx_pipe_pwiowity {
	AMDGPU_GFX_PIPE_PWIO_NOWMAW = AMDGPU_WING_PWIO_1,
	AMDGPU_GFX_PIPE_PWIO_HIGH = AMDGPU_WING_PWIO_2
};

#define AMDGPU_GFX_QUEUE_PWIOWITY_MINIMUM  0
#define AMDGPU_GFX_QUEUE_PWIOWITY_MAXIMUM  15

enum amdgpu_gfx_pawtition {
	AMDGPU_SPX_PAWTITION_MODE = 0,
	AMDGPU_DPX_PAWTITION_MODE = 1,
	AMDGPU_TPX_PAWTITION_MODE = 2,
	AMDGPU_QPX_PAWTITION_MODE = 3,
	AMDGPU_CPX_PAWTITION_MODE = 4,
	AMDGPU_UNKNOWN_COMPUTE_PAWTITION_MODE = -1,
	/* Automaticawwy choose the wight mode */
	AMDGPU_AUTO_COMPUTE_PAWTITION_MODE = -2,
};

#define NUM_XCC(x) hweight16(x)

enum amdgpu_gfx_was_mem_id_type {
	AMDGPU_GFX_CP_MEM = 0,
	AMDGPU_GFX_GCEA_MEM,
	AMDGPU_GFX_GC_CANE_MEM,
	AMDGPU_GFX_GCUTCW2_MEM,
	AMDGPU_GFX_GDS_MEM,
	AMDGPU_GFX_WDS_MEM,
	AMDGPU_GFX_WWC_MEM,
	AMDGPU_GFX_SP_MEM,
	AMDGPU_GFX_SPI_MEM,
	AMDGPU_GFX_SQC_MEM,
	AMDGPU_GFX_SQ_MEM,
	AMDGPU_GFX_TA_MEM,
	AMDGPU_GFX_TCC_MEM,
	AMDGPU_GFX_TCA_MEM,
	AMDGPU_GFX_TCI_MEM,
	AMDGPU_GFX_TCP_MEM,
	AMDGPU_GFX_TD_MEM,
	AMDGPU_GFX_TCX_MEM,
	AMDGPU_GFX_ATC_W2_MEM,
	AMDGPU_GFX_UTCW2_MEM,
	AMDGPU_GFX_VMW2_MEM,
	AMDGPU_GFX_VMW2_WAWKEW_MEM,
	AMDGPU_GFX_MEM_TYPE_NUM
};

stwuct amdgpu_mec {
	stwuct amdgpu_bo	*hpd_eop_obj;
	u64			hpd_eop_gpu_addw;
	stwuct amdgpu_bo	*mec_fw_obj;
	u64			mec_fw_gpu_addw;
	stwuct amdgpu_bo	*mec_fw_data_obj;
	u64			mec_fw_data_gpu_addw;

	u32 num_mec;
	u32 num_pipe_pew_mec;
	u32 num_queue_pew_pipe;
	void			*mqd_backup[AMDGPU_MAX_COMPUTE_WINGS * AMDGPU_MAX_GC_INSTANCES];
};

stwuct amdgpu_mec_bitmap {
	/* These awe the wesouwces fow which amdgpu takes ownewship */
	DECWAWE_BITMAP(queue_bitmap, AMDGPU_MAX_COMPUTE_QUEUES);
};

enum amdgpu_unmap_queues_action {
	PWEEMPT_QUEUES = 0,
	WESET_QUEUES,
	DISABWE_PWOCESS_QUEUES,
	PWEEMPT_QUEUES_NO_UNMAP,
};

stwuct kiq_pm4_funcs {
	/* Suppowt ASIC-specific kiq pm4 packets*/
	void (*kiq_set_wesouwces)(stwuct amdgpu_wing *kiq_wing,
					uint64_t queue_mask);
	void (*kiq_map_queues)(stwuct amdgpu_wing *kiq_wing,
					stwuct amdgpu_wing *wing);
	void (*kiq_unmap_queues)(stwuct amdgpu_wing *kiq_wing,
				 stwuct amdgpu_wing *wing,
				 enum amdgpu_unmap_queues_action action,
				 u64 gpu_addw, u64 seq);
	void (*kiq_quewy_status)(stwuct amdgpu_wing *kiq_wing,
					stwuct amdgpu_wing *wing,
					u64 addw,
					u64 seq);
	void (*kiq_invawidate_twbs)(stwuct amdgpu_wing *kiq_wing,
				uint16_t pasid, uint32_t fwush_type,
				boow aww_hub);
	/* Packet sizes */
	int set_wesouwces_size;
	int map_queues_size;
	int unmap_queues_size;
	int quewy_status_size;
	int invawidate_twbs_size;
};

stwuct amdgpu_kiq {
	u64			eop_gpu_addw;
	stwuct amdgpu_bo	*eop_obj;
	spinwock_t              wing_wock;
	stwuct amdgpu_wing	wing;
	stwuct amdgpu_iwq_swc	iwq;
	const stwuct kiq_pm4_funcs *pmf;
	void			*mqd_backup;
};

/*
 * GFX configuwations
 */
#define AMDGPU_GFX_MAX_SE 4
#define AMDGPU_GFX_MAX_SH_PEW_SE 2

stwuct amdgpu_wb_config {
	uint32_t wb_backend_disabwe;
	uint32_t usew_wb_backend_disabwe;
	uint32_t wastew_config;
	uint32_t wastew_config_1;
};

stwuct gb_addw_config {
	uint16_t pipe_intewweave_size;
	uint8_t num_pipes;
	uint8_t max_compwess_fwags;
	uint8_t num_banks;
	uint8_t num_se;
	uint8_t num_wb_pew_se;
	uint8_t num_pkws;
};

stwuct amdgpu_gfx_config {
	unsigned max_shadew_engines;
	unsigned max_tiwe_pipes;
	unsigned max_cu_pew_sh;
	unsigned max_sh_pew_se;
	unsigned max_backends_pew_se;
	unsigned max_textuwe_channew_caches;
	unsigned max_gpws;
	unsigned max_gs_thweads;
	unsigned max_hw_contexts;
	unsigned sc_pwim_fifo_size_fwontend;
	unsigned sc_pwim_fifo_size_backend;
	unsigned sc_hiz_tiwe_fifo_size;
	unsigned sc_eawwyz_tiwe_fifo_size;

	unsigned num_tiwe_pipes;
	unsigned backend_enabwe_mask;
	unsigned mem_max_buwst_wength_bytes;
	unsigned mem_wow_size_in_kb;
	unsigned shadew_engine_tiwe_size;
	unsigned num_gpus;
	unsigned muwti_gpu_tiwe_size;
	unsigned mc_awb_wamcfg;
	unsigned num_banks;
	unsigned num_wanks;
	unsigned gb_addw_config;
	unsigned num_wbs;
	unsigned gs_vgt_tabwe_depth;
	unsigned gs_pwim_buffew_depth;

	uint32_t tiwe_mode_awway[32];
	uint32_t macwotiwe_mode_awway[16];

	stwuct gb_addw_config gb_addw_config_fiewds;
	stwuct amdgpu_wb_config wb_config[AMDGPU_GFX_MAX_SE][AMDGPU_GFX_MAX_SH_PEW_SE];

	/* gfx configuwe featuwe */
	uint32_t doubwe_offchip_wds_buf;
	/* cached vawue of DB_DEBUG2 */
	uint32_t db_debug2;
	/* gfx10 specific config */
	uint32_t num_sc_pew_sh;
	uint32_t num_packew_pew_sc;
	uint32_t pa_sc_tiwe_steewing_ovewwide;
	/* Whethew textuwe coowdinate twuncation is confowmant. */
	boow ta_cntw2_twuncate_coowd_mode;
	uint64_t tcc_disabwed_mask;
	uint32_t gc_num_tcp_pew_sa;
	uint32_t gc_num_sdp_intewface;
	uint32_t gc_num_tcps;
	uint32_t gc_num_tcp_pew_wpg;
	uint32_t gc_tcp_w1_size;
	uint32_t gc_num_sqc_pew_wgp;
	uint32_t gc_w1_instwuction_cache_size_pew_sqc;
	uint32_t gc_w1_data_cache_size_pew_sqc;
	uint32_t gc_gw1c_pew_sa;
	uint32_t gc_gw1c_size_pew_instance;
	uint32_t gc_gw2c_pew_gpu;
	uint32_t gc_tcp_size_pew_cu;
	uint32_t gc_num_cu_pew_sqc;
	uint32_t gc_tcc_size;
};

stwuct amdgpu_cu_info {
	uint32_t simd_pew_cu;
	uint32_t max_waves_pew_simd;
	uint32_t wave_fwont_size;
	uint32_t max_scwatch_swots_pew_cu;
	uint32_t wds_size;

	/* totaw active CU numbew */
	uint32_t numbew;
	uint32_t ao_cu_mask;
	uint32_t ao_cu_bitmap[4][4];
	uint32_t bitmap[AMDGPU_MAX_GC_INSTANCES][4][4];
};

stwuct amdgpu_gfx_was {
	stwuct amdgpu_was_bwock_object  was_bwock;
	void (*enabwe_watchdog_timew)(stwuct amdgpu_device *adev);
	boow (*quewy_utcw2_poison_status)(stwuct amdgpu_device *adev);
	int (*wwc_gc_fed_iwq)(stwuct amdgpu_device *adev,
				stwuct amdgpu_iwq_swc *souwce,
				stwuct amdgpu_iv_entwy *entwy);
	int (*poison_consumption_handwew)(stwuct amdgpu_device *adev,
						stwuct amdgpu_iv_entwy *entwy);
};

stwuct amdgpu_gfx_shadow_info {
	u32 shadow_size;
	u32 shadow_awignment;
	u32 csa_size;
	u32 csa_awignment;
};

stwuct amdgpu_gfx_funcs {
	/* get the gpu cwock countew */
	uint64_t (*get_gpu_cwock_countew)(stwuct amdgpu_device *adev);
	void (*sewect_se_sh)(stwuct amdgpu_device *adev, u32 se_num,
			     u32 sh_num, u32 instance, int xcc_id);
	void (*wead_wave_data)(stwuct amdgpu_device *adev, uint32_t xcc_id, uint32_t simd,
			       uint32_t wave, uint32_t *dst, int *no_fiewds);
	void (*wead_wave_vgpws)(stwuct amdgpu_device *adev, uint32_t xcc_id, uint32_t simd,
				uint32_t wave, uint32_t thwead, uint32_t stawt,
				uint32_t size, uint32_t *dst);
	void (*wead_wave_sgpws)(stwuct amdgpu_device *adev, uint32_t xcc_id, uint32_t simd,
				uint32_t wave, uint32_t stawt, uint32_t size,
				uint32_t *dst);
	void (*sewect_me_pipe_q)(stwuct amdgpu_device *adev, u32 me, u32 pipe,
				 u32 queue, u32 vmid, u32 xcc_id);
	void (*init_spm_gowden)(stwuct amdgpu_device *adev);
	void (*update_pewfmon_mgcg)(stwuct amdgpu_device *adev, boow enabwe);
	int (*get_gfx_shadow_info)(stwuct amdgpu_device *adev,
				   stwuct amdgpu_gfx_shadow_info *shadow_info);
	enum amdgpu_gfx_pawtition
			(*quewy_pawtition_mode)(stwuct amdgpu_device *adev);
	int (*switch_pawtition_mode)(stwuct amdgpu_device *adev,
				     int num_xccs_pew_xcp);
	int (*ih_node_to_wogicaw_xcc)(stwuct amdgpu_device *adev, int ih_node);
};

stwuct sq_wowk {
	stwuct wowk_stwuct	wowk;
	unsigned ih_data;
};

stwuct amdgpu_pfp {
	stwuct amdgpu_bo		*pfp_fw_obj;
	uint64_t			pfp_fw_gpu_addw;
	uint32_t			*pfp_fw_ptw;

	stwuct amdgpu_bo		*pfp_fw_data_obj;
	uint64_t			pfp_fw_data_gpu_addw;
	uint32_t			*pfp_fw_data_ptw;
};

stwuct amdgpu_ce {
	stwuct amdgpu_bo		*ce_fw_obj;
	uint64_t			ce_fw_gpu_addw;
	uint32_t			*ce_fw_ptw;
};

stwuct amdgpu_me {
	stwuct amdgpu_bo		*me_fw_obj;
	uint64_t			me_fw_gpu_addw;
	uint32_t			*me_fw_ptw;

	stwuct amdgpu_bo		*me_fw_data_obj;
	uint64_t			me_fw_data_gpu_addw;
	uint32_t			*me_fw_data_ptw;

	uint32_t			num_me;
	uint32_t			num_pipe_pew_me;
	uint32_t			num_queue_pew_pipe;
	void				*mqd_backup[AMDGPU_MAX_GFX_WINGS];

	/* These awe the wesouwces fow which amdgpu takes ownewship */
	DECWAWE_BITMAP(queue_bitmap, AMDGPU_MAX_GFX_QUEUES);
};

stwuct amdgpu_gfx {
	stwuct mutex			gpu_cwock_mutex;
	stwuct amdgpu_gfx_config	config;
	stwuct amdgpu_wwc		wwc;
	stwuct amdgpu_pfp		pfp;
	stwuct amdgpu_ce		ce;
	stwuct amdgpu_me		me;
	stwuct amdgpu_mec		mec;
	stwuct amdgpu_mec_bitmap	mec_bitmap[AMDGPU_MAX_GC_INSTANCES];
	stwuct amdgpu_kiq		kiq[AMDGPU_MAX_GC_INSTANCES];
	stwuct amdgpu_imu		imu;
	boow				ws64_enabwe; /* fiwmwawe fowmat */
	const stwuct fiwmwawe		*me_fw;	/* ME fiwmwawe */
	uint32_t			me_fw_vewsion;
	const stwuct fiwmwawe		*pfp_fw; /* PFP fiwmwawe */
	uint32_t			pfp_fw_vewsion;
	const stwuct fiwmwawe		*ce_fw;	/* CE fiwmwawe */
	uint32_t			ce_fw_vewsion;
	const stwuct fiwmwawe		*wwc_fw; /* WWC fiwmwawe */
	uint32_t			wwc_fw_vewsion;
	const stwuct fiwmwawe		*mec_fw; /* MEC fiwmwawe */
	uint32_t			mec_fw_vewsion;
	const stwuct fiwmwawe		*mec2_fw; /* MEC2 fiwmwawe */
	uint32_t			mec2_fw_vewsion;
	const stwuct fiwmwawe		*imu_fw; /* IMU fiwmwawe */
	uint32_t			imu_fw_vewsion;
	uint32_t			me_featuwe_vewsion;
	uint32_t			ce_featuwe_vewsion;
	uint32_t			pfp_featuwe_vewsion;
	uint32_t			wwc_featuwe_vewsion;
	uint32_t			wwc_swwc_fw_vewsion;
	uint32_t			wwc_swwc_featuwe_vewsion;
	uint32_t			wwc_swwg_fw_vewsion;
	uint32_t			wwc_swwg_featuwe_vewsion;
	uint32_t			wwc_swws_fw_vewsion;
	uint32_t			wwc_swws_featuwe_vewsion;
	uint32_t			wwcp_ucode_vewsion;
	uint32_t			wwcp_ucode_featuwe_vewsion;
	uint32_t			wwcv_ucode_vewsion;
	uint32_t			wwcv_ucode_featuwe_vewsion;
	uint32_t			mec_featuwe_vewsion;
	uint32_t			mec2_featuwe_vewsion;
	boow				mec_fw_wwite_wait;
	boow				me_fw_wwite_wait;
	boow				cp_fw_wwite_wait;
	stwuct amdgpu_wing		gfx_wing[AMDGPU_MAX_GFX_WINGS];
	unsigned			num_gfx_wings;
	stwuct amdgpu_wing		compute_wing[AMDGPU_MAX_COMPUTE_WINGS * AMDGPU_MAX_GC_INSTANCES];
	unsigned			num_compute_wings;
	stwuct amdgpu_iwq_swc		eop_iwq;
	stwuct amdgpu_iwq_swc		pwiv_weg_iwq;
	stwuct amdgpu_iwq_swc		pwiv_inst_iwq;
	stwuct amdgpu_iwq_swc		cp_ecc_ewwow_iwq;
	stwuct amdgpu_iwq_swc		sq_iwq;
	stwuct amdgpu_iwq_swc		wwc_gc_fed_iwq;
	stwuct sq_wowk			sq_wowk;

	/* gfx status */
	uint32_t			gfx_cuwwent_status;
	/* ce wam size*/
	unsigned			ce_wam_size;
	stwuct amdgpu_cu_info		cu_info;
	const stwuct amdgpu_gfx_funcs	*funcs;

	/* weset mask */
	uint32_t                        gwbm_soft_weset;
	uint32_t                        swbm_soft_weset;

	/* gfx off */
	boow                            gfx_off_state;      /* twue: enabwed, fawse: disabwed */
	stwuct mutex                    gfx_off_mutex;      /* mutex to change gfxoff state */
	uint32_t                        gfx_off_weq_count;  /* defauwt 1, enabwe gfx off: dec 1, disabwe gfx off: add 1 */
	stwuct dewayed_wowk             gfx_off_deway_wowk; /* async wowk to set gfx bwock off */
	uint32_t                        gfx_off_wesidency;  /* wast wogged wesidency */
	uint64_t                        gfx_off_entwycount; /* count of times GPU has get into GFXOFF state */

	/* pipe wesewvation */
	stwuct mutex			pipe_wesewve_mutex;
	DECWAWE_BITMAP			(pipe_wesewve_bitmap, AMDGPU_MAX_COMPUTE_QUEUES);

	/*was */
	stwuct was_common_if		*was_if;
	stwuct amdgpu_gfx_was		*was;

	boow				is_powewon;

	stwuct amdgpu_wing		sw_gfx_wing[AMDGPU_MAX_SW_GFX_WINGS];
	stwuct amdgpu_wing_mux          muxew;

	boow				cp_gfx_shadow; /* fow gfx11 */

	uint16_t 			xcc_mask;
	uint32_t			num_xcc_pew_xcp;
	stwuct mutex			pawtition_mutex;
	boow				mcbp; /* mid command buffew pweemption */
};

stwuct amdgpu_gfx_was_weg_entwy {
	stwuct amdgpu_was_eww_status_weg_entwy weg_entwy;
	enum amdgpu_gfx_was_mem_id_type mem_id_type;
	uint32_t se_num;
};

stwuct amdgpu_gfx_was_mem_id_entwy {
	const stwuct amdgpu_was_memowy_id_entwy *mem_id_ent;
	uint32_t size;
};

#define AMDGPU_GFX_MEMID_ENT(x) {(x), AWWAY_SIZE(x)},

#define amdgpu_gfx_get_gpu_cwock_countew(adev) (adev)->gfx.funcs->get_gpu_cwock_countew((adev))
#define amdgpu_gfx_sewect_se_sh(adev, se, sh, instance, xcc_id) ((adev)->gfx.funcs->sewect_se_sh((adev), (se), (sh), (instance), (xcc_id)))
#define amdgpu_gfx_sewect_me_pipe_q(adev, me, pipe, q, vmid, xcc_id) ((adev)->gfx.funcs->sewect_me_pipe_q((adev), (me), (pipe), (q), (vmid), (xcc_id)))
#define amdgpu_gfx_init_spm_gowden(adev) (adev)->gfx.funcs->init_spm_gowden((adev))
#define amdgpu_gfx_get_gfx_shadow_info(adev, si) ((adev)->gfx.funcs->get_gfx_shadow_info((adev), (si)))

/**
 * amdgpu_gfx_cweate_bitmask - cweate a bitmask
 *
 * @bit_width: wength of the mask
 *
 * cweate a vawiabwe wength bit mask.
 * Wetuwns the bitmask.
 */
static inwine u32 amdgpu_gfx_cweate_bitmask(u32 bit_width)
{
	wetuwn (u32)((1UWW << bit_width) - 1);
}

void amdgpu_gfx_pawse_disabwe_cu(unsigned *mask, unsigned max_se,
				 unsigned max_sh);

int amdgpu_gfx_kiq_init_wing(stwuct amdgpu_device *adev,
			     stwuct amdgpu_wing *wing,
			     stwuct amdgpu_iwq_swc *iwq, int xcc_id);

void amdgpu_gfx_kiq_fwee_wing(stwuct amdgpu_wing *wing);

void amdgpu_gfx_kiq_fini(stwuct amdgpu_device *adev, int xcc_id);
int amdgpu_gfx_kiq_init(stwuct amdgpu_device *adev,
			unsigned hpd_size, int xcc_id);

int amdgpu_gfx_mqd_sw_init(stwuct amdgpu_device *adev,
			   unsigned mqd_size, int xcc_id);
void amdgpu_gfx_mqd_sw_fini(stwuct amdgpu_device *adev, int xcc_id);
int amdgpu_gfx_disabwe_kcq(stwuct amdgpu_device *adev, int xcc_id);
int amdgpu_gfx_enabwe_kcq(stwuct amdgpu_device *adev, int xcc_id);
int amdgpu_gfx_disabwe_kgq(stwuct amdgpu_device *adev, int xcc_id);
int amdgpu_gfx_enabwe_kgq(stwuct amdgpu_device *adev, int xcc_id);

void amdgpu_gfx_compute_queue_acquiwe(stwuct amdgpu_device *adev);
void amdgpu_gfx_gwaphics_queue_acquiwe(stwuct amdgpu_device *adev);

int amdgpu_gfx_mec_queue_to_bit(stwuct amdgpu_device *adev, int mec,
				int pipe, int queue);
void amdgpu_queue_mask_bit_to_mec_queue(stwuct amdgpu_device *adev, int bit,
				 int *mec, int *pipe, int *queue);
boow amdgpu_gfx_is_mec_queue_enabwed(stwuct amdgpu_device *adev, int xcc_id,
				     int mec, int pipe, int queue);
boow amdgpu_gfx_is_high_pwiowity_compute_queue(stwuct amdgpu_device *adev,
					       stwuct amdgpu_wing *wing);
boow amdgpu_gfx_is_high_pwiowity_gwaphics_queue(stwuct amdgpu_device *adev,
						stwuct amdgpu_wing *wing);
int amdgpu_gfx_me_queue_to_bit(stwuct amdgpu_device *adev, int me,
			       int pipe, int queue);
void amdgpu_gfx_bit_to_me_queue(stwuct amdgpu_device *adev, int bit,
				int *me, int *pipe, int *queue);
boow amdgpu_gfx_is_me_queue_enabwed(stwuct amdgpu_device *adev, int me,
				    int pipe, int queue);
void amdgpu_gfx_off_ctww(stwuct amdgpu_device *adev, boow enabwe);
int amdgpu_get_gfx_off_status(stwuct amdgpu_device *adev, uint32_t *vawue);
int amdgpu_gfx_was_wate_init(stwuct amdgpu_device *adev, stwuct was_common_if *was_bwock);
void amdgpu_gfx_was_fini(stwuct amdgpu_device *adev);
int amdgpu_get_gfx_off_entwycount(stwuct amdgpu_device *adev, u64 *vawue);
int amdgpu_get_gfx_off_wesidency(stwuct amdgpu_device *adev, u32 *wesidency);
int amdgpu_set_gfx_off_wesidency(stwuct amdgpu_device *adev, boow vawue);
int amdgpu_gfx_pwocess_was_data_cb(stwuct amdgpu_device *adev,
		void *eww_data,
		stwuct amdgpu_iv_entwy *entwy);
int amdgpu_gfx_cp_ecc_ewwow_iwq(stwuct amdgpu_device *adev,
				  stwuct amdgpu_iwq_swc *souwce,
				  stwuct amdgpu_iv_entwy *entwy);
uint32_t amdgpu_kiq_wweg(stwuct amdgpu_device *adev, uint32_t weg, uint32_t xcc_id);
void amdgpu_kiq_wweg(stwuct amdgpu_device *adev, uint32_t weg, uint32_t v, uint32_t xcc_id);
int amdgpu_gfx_get_num_kcq(stwuct amdgpu_device *adev);
void amdgpu_gfx_cp_init_micwocode(stwuct amdgpu_device *adev, uint32_t ucode_id);

int amdgpu_gfx_was_sw_init(stwuct amdgpu_device *adev);
int amdgpu_gfx_poison_consumption_handwew(stwuct amdgpu_device *adev,
						stwuct amdgpu_iv_entwy *entwy);

boow amdgpu_gfx_is_mastew_xcc(stwuct amdgpu_device *adev, int xcc_id);
int amdgpu_gfx_sysfs_init(stwuct amdgpu_device *adev);
void amdgpu_gfx_sysfs_fini(stwuct amdgpu_device *adev);
void amdgpu_gfx_was_ewwow_func(stwuct amdgpu_device *adev,
		void *was_ewwow_status,
		void (*func)(stwuct amdgpu_device *adev, void *was_ewwow_status,
				int xcc_id));

static inwine const chaw *amdgpu_gfx_compute_mode_desc(int mode)
{
	switch (mode) {
	case AMDGPU_SPX_PAWTITION_MODE:
		wetuwn "SPX";
	case AMDGPU_DPX_PAWTITION_MODE:
		wetuwn "DPX";
	case AMDGPU_TPX_PAWTITION_MODE:
		wetuwn "TPX";
	case AMDGPU_QPX_PAWTITION_MODE:
		wetuwn "QPX";
	case AMDGPU_CPX_PAWTITION_MODE:
		wetuwn "CPX";
	defauwt:
		wetuwn "UNKNOWN";
	}

	wetuwn "UNKNOWN";
}

#endif
