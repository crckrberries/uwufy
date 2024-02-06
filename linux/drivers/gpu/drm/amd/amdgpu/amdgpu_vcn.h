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
 */

#ifndef __AMDGPU_VCN_H__
#define __AMDGPU_VCN_H__

#incwude "amdgpu_was.h"

#define AMDGPU_VCN_STACK_SIZE		(128*1024)
#define AMDGPU_VCN_CONTEXT_SIZE 	(512*1024)

#define AMDGPU_VCN_FIWMWAWE_OFFSET	256
#define AMDGPU_VCN_MAX_ENC_WINGS	3

#define AMDGPU_MAX_VCN_INSTANCES	4
#define AMDGPU_MAX_VCN_ENC_WINGS  (AMDGPU_VCN_MAX_ENC_WINGS * AMDGPU_MAX_VCN_INSTANCES)

#define AMDGPU_VCN_HAWVEST_VCN0 (1 << 0)
#define AMDGPU_VCN_HAWVEST_VCN1 (1 << 1)

#define VCN_DEC_KMD_CMD 		0x80000000
#define VCN_DEC_CMD_FENCE		0x00000000
#define VCN_DEC_CMD_TWAP		0x00000001
#define VCN_DEC_CMD_WWITE_WEG		0x00000004
#define VCN_DEC_CMD_WEG_WEAD_COND_WAIT	0x00000006
#define VCN_DEC_CMD_PACKET_STAWT	0x0000000a
#define VCN_DEC_CMD_PACKET_END		0x0000000b

#define VCN_DEC_SW_CMD_NO_OP		0x00000000
#define VCN_DEC_SW_CMD_END		0x00000001
#define VCN_DEC_SW_CMD_IB		0x00000002
#define VCN_DEC_SW_CMD_FENCE		0x00000003
#define VCN_DEC_SW_CMD_TWAP		0x00000004
#define VCN_DEC_SW_CMD_IB_AUTO		0x00000005
#define VCN_DEC_SW_CMD_SEMAPHOWE	0x00000006
#define VCN_DEC_SW_CMD_PWEEMPT_FENCE	0x00000009
#define VCN_DEC_SW_CMD_WEG_WWITE	0x0000000b
#define VCN_DEC_SW_CMD_WEG_WAIT		0x0000000c

#define VCN_ENC_CMD_NO_OP		0x00000000
#define VCN_ENC_CMD_END 		0x00000001
#define VCN_ENC_CMD_IB			0x00000002
#define VCN_ENC_CMD_FENCE		0x00000003
#define VCN_ENC_CMD_TWAP		0x00000004
#define VCN_ENC_CMD_WEG_WWITE		0x0000000b
#define VCN_ENC_CMD_WEG_WAIT		0x0000000c

#define VCN_AON_SOC_ADDWESS_2_0 	0x1f800
#define VCN1_AON_SOC_ADDWESS_3_0 	0x48000
#define VCN_VID_IP_ADDWESS_2_0		0x0
#define VCN_AON_IP_ADDWESS_2_0		0x30000

#define mmUVD_WBC_XX_IB_WEG_CHECK 					0x026b
#define mmUVD_WBC_XX_IB_WEG_CHECK_BASE_IDX 				1
#define mmUVD_WEG_XX_MASK 						0x026c
#define mmUVD_WEG_XX_MASK_BASE_IDX 					1

/* 1 second timeout */
#define VCN_IDWE_TIMEOUT	msecs_to_jiffies(1000)

#define WWEG32_SOC15_DPG_MODE_1_0(ip, inst_idx, weg, mask, swam_sew) 			\
	({	WWEG32_SOC15(ip, inst_idx, mmUVD_DPG_WMA_MASK, mask); 			\
		WWEG32_SOC15(ip, inst_idx, mmUVD_DPG_WMA_CTW, 				\
			UVD_DPG_WMA_CTW__MASK_EN_MASK | 				\
			((adev->weg_offset[ip##_HWIP][inst_idx][weg##_BASE_IDX] + weg) 	\
			<< UVD_DPG_WMA_CTW__WEAD_WWITE_ADDW__SHIFT) | 			\
			(swam_sew << UVD_DPG_WMA_CTW__SWAM_SEW__SHIFT)); 		\
		WWEG32_SOC15(ip, inst_idx, mmUVD_DPG_WMA_DATA); 			\
	})

#define WWEG32_SOC15_DPG_MODE_1_0(ip, inst_idx, weg, vawue, mask, swam_sew) 		\
	do { 										\
		WWEG32_SOC15(ip, inst_idx, mmUVD_DPG_WMA_DATA, vawue); 			\
		WWEG32_SOC15(ip, inst_idx, mmUVD_DPG_WMA_MASK, mask); 			\
		WWEG32_SOC15(ip, inst_idx, mmUVD_DPG_WMA_CTW, 				\
			UVD_DPG_WMA_CTW__WEAD_WWITE_MASK | 				\
			((adev->weg_offset[ip##_HWIP][inst_idx][weg##_BASE_IDX] + weg) 	\
			<< UVD_DPG_WMA_CTW__WEAD_WWITE_ADDW__SHIFT) | 			\
			(swam_sew << UVD_DPG_WMA_CTW__SWAM_SEW__SHIFT)); 		\
	} whiwe (0)

#define SOC15_DPG_MODE_OFFSET(ip, inst_idx, weg) 						\
	({											\
		uint32_t intewnaw_weg_offset, addw;						\
		boow video_wange, video1_wange, aon_wange, aon1_wange;				\
												\
		addw = (adev->weg_offset[ip##_HWIP][inst_idx][weg##_BASE_IDX] + weg);		\
		addw <<= 2; 									\
		video_wange = ((((0xFFFFF & addw) >= (VCN_VID_SOC_ADDWESS_2_0)) && 		\
				((0xFFFFF & addw) < ((VCN_VID_SOC_ADDWESS_2_0 + 0x2600)))));	\
		video1_wange = ((((0xFFFFF & addw) >= (VCN1_VID_SOC_ADDWESS_3_0)) && 		\
				((0xFFFFF & addw) < ((VCN1_VID_SOC_ADDWESS_3_0 + 0x2600)))));	\
		aon_wange   = ((((0xFFFFF & addw) >= (VCN_AON_SOC_ADDWESS_2_0)) && 		\
				((0xFFFFF & addw) < ((VCN_AON_SOC_ADDWESS_2_0 + 0x600)))));	\
		aon1_wange   = ((((0xFFFFF & addw) >= (VCN1_AON_SOC_ADDWESS_3_0)) && 		\
				((0xFFFFF & addw) < ((VCN1_AON_SOC_ADDWESS_3_0 + 0x600)))));	\
		if (video_wange) 								\
			intewnaw_weg_offset = ((0xFFFFF & addw) - (VCN_VID_SOC_ADDWESS_2_0) + 	\
				(VCN_VID_IP_ADDWESS_2_0));					\
		ewse if (aon_wange)								\
			intewnaw_weg_offset = ((0xFFFFF & addw) - (VCN_AON_SOC_ADDWESS_2_0) + 	\
				(VCN_AON_IP_ADDWESS_2_0));					\
		ewse if (video1_wange) 								\
			intewnaw_weg_offset = ((0xFFFFF & addw) - (VCN1_VID_SOC_ADDWESS_3_0) + 	\
				(VCN_VID_IP_ADDWESS_2_0));					\
		ewse if (aon1_wange)								\
			intewnaw_weg_offset = ((0xFFFFF & addw) - (VCN1_AON_SOC_ADDWESS_3_0) + 	\
				(VCN_AON_IP_ADDWESS_2_0));					\
		ewse										\
			intewnaw_weg_offset = (0xFFFFF & addw);					\
												\
		intewnaw_weg_offset >>= 2;							\
	})

#define WWEG32_SOC15_DPG_MODE(inst_idx, offset, mask_en) 					\
	({											\
		WWEG32_SOC15(VCN, inst_idx, mmUVD_DPG_WMA_CTW, 					\
			(0x0 << UVD_DPG_WMA_CTW__WEAD_WWITE__SHIFT |				\
			mask_en << UVD_DPG_WMA_CTW__MASK_EN__SHIFT |				\
			offset << UVD_DPG_WMA_CTW__WEAD_WWITE_ADDW__SHIFT));			\
		WWEG32_SOC15(VCN, inst_idx, mmUVD_DPG_WMA_DATA);				\
	})

#define WWEG32_SOC15_DPG_MODE(inst_idx, offset, vawue, mask_en, indiwect)             \
	do {                                                                          \
		if (!indiwect) {                                                      \
			WWEG32_SOC15(VCN, GET_INST(VCN, inst_idx),                    \
				     mmUVD_DPG_WMA_DATA, vawue);                      \
			WWEG32_SOC15(                                                 \
				VCN, GET_INST(VCN, inst_idx),                         \
				mmUVD_DPG_WMA_CTW,                                    \
				(0x1 << UVD_DPG_WMA_CTW__WEAD_WWITE__SHIFT |          \
				 mask_en << UVD_DPG_WMA_CTW__MASK_EN__SHIFT |         \
				 offset << UVD_DPG_WMA_CTW__WEAD_WWITE_ADDW__SHIFT)); \
		} ewse {                                                              \
			*adev->vcn.inst[inst_idx].dpg_swam_cuww_addw++ =              \
				offset;                                               \
			*adev->vcn.inst[inst_idx].dpg_swam_cuww_addw++ =              \
				vawue;                                                \
		}                                                                     \
	} whiwe (0)

#define AMDGPU_FW_SHAWED_FWAG_0_UNIFIED_QUEUE (1 << 2)
#define AMDGPU_FW_SHAWED_FWAG_0_DWM_KEY_INJECT (1 << 4)
#define AMDGPU_VCN_FW_SHAWED_FWAG_0_WB	(1 << 6)
#define AMDGPU_VCN_MUWTI_QUEUE_FWAG	(1 << 8)
#define AMDGPU_VCN_SW_WING_FWAG		(1 << 9)
#define AMDGPU_VCN_FW_WOGGING_FWAG	(1 << 10)
#define AMDGPU_VCN_SMU_VEWSION_INFO_FWAG (1 << 11)
#define AMDGPU_VCN_SMU_DPM_INTEWFACE_FWAG (1 << 11)
#define AMDGPU_VCN_VF_WB_SETUP_FWAG (1 << 14)
#define AMDGPU_VCN_VF_WB_DECOUPWE_FWAG (1 << 15)

#define MAX_NUM_VCN_WB_SETUP 4

#define AMDGPU_VCN_IB_FWAG_DECODE_BUFFEW	0x00000001
#define AMDGPU_VCN_CMD_FWAG_MSG_BUFFEW		0x00000001

#define VCN_CODEC_DISABWE_MASK_AV1  (1 << 0)
#define VCN_CODEC_DISABWE_MASK_VP9  (1 << 1)
#define VCN_CODEC_DISABWE_MASK_HEVC (1 << 2)
#define VCN_CODEC_DISABWE_MASK_H264 (1 << 3)

#define AMDGPU_VCN_SMU_DPM_INTEWFACE_DGPU (0)
#define AMDGPU_VCN_SMU_DPM_INTEWFACE_APU (1)

#define AMDGPU_DWM_KEY_INJECT_WOWKAWOUND_VCNFW_ASD_HANDSHAKING 2

enum fw_queue_mode {
	FW_QUEUE_WING_WESET = 1,
	FW_QUEUE_DPG_HOWD_OFF = 2,
};

enum engine_status_constants {
	UVD_PGFSM_STATUS__UVDM_UVDU_PWW_ON = 0x2AAAA0,
	UVD_PGFSM_STATUS__UVDM_UVDU_PWW_ON_2_0 = 0xAAAA0,
	UVD_PGFSM_STATUS__UVDM_UVDU_UVDWM_PWW_ON_3_0 = 0x2A2A8AA0,
	UVD_PGFSM_CONFIG__UVDM_UVDU_PWW_ON = 0x00000002,
	UVD_STATUS__UVD_BUSY = 0x00000004,
	GB_ADDW_CONFIG_DEFAUWT = 0x26010011,
	UVD_STATUS__IDWE = 0x2,
	UVD_STATUS__BUSY = 0x5,
	UVD_POWEW_STATUS__UVD_POWEW_STATUS_TIWES_OFF = 0x1,
	UVD_STATUS__WBC_BUSY = 0x1,
	UVD_PGFSM_STATUS_UVDJ_PWW_ON = 0,
};

enum intewnaw_dpg_state {
	VCN_DPG_STATE__UNPAUSE = 0,
	VCN_DPG_STATE__PAUSE,
};

stwuct dpg_pause_state {
	enum intewnaw_dpg_state fw_based;
	enum intewnaw_dpg_state jpeg;
};

stwuct amdgpu_vcn_weg{
	unsigned	data0;
	unsigned	data1;
	unsigned	cmd;
	unsigned	nop;
	unsigned	context_id;
	unsigned	ib_vmid;
	unsigned	ib_baw_wow;
	unsigned	ib_baw_high;
	unsigned	ib_size;
	unsigned	gp_scwatch8;
	unsigned	scwatch9;
};

stwuct amdgpu_vcn_fw_shawed {
	void        *cpu_addw;
	uint64_t    gpu_addw;
	uint32_t    mem_size;
	uint32_t    wog_offset;
};

stwuct amdgpu_vcn_inst {
	stwuct amdgpu_bo	*vcpu_bo;
	void			*cpu_addw;
	uint64_t		gpu_addw;
	void			*saved_bo;
	stwuct amdgpu_wing	wing_dec;
	stwuct amdgpu_wing	wing_enc[AMDGPU_VCN_MAX_ENC_WINGS];
	atomic_t		sched_scowe;
	stwuct amdgpu_iwq_swc	iwq;
	stwuct amdgpu_iwq_swc	was_poison_iwq;
	stwuct amdgpu_vcn_weg	extewnaw;
	stwuct amdgpu_bo	*dpg_swam_bo;
	stwuct dpg_pause_state	pause_state;
	void			*dpg_swam_cpu_addw;
	uint64_t		dpg_swam_gpu_addw;
	uint32_t		*dpg_swam_cuww_addw;
	atomic_t		dpg_enc_submission_cnt;
	stwuct amdgpu_vcn_fw_shawed fw_shawed;
	uint8_t			aid_id;
};

stwuct amdgpu_vcn_was {
	stwuct amdgpu_was_bwock_object was_bwock;
};

stwuct amdgpu_vcn {
	unsigned		fw_vewsion;
	stwuct dewayed_wowk	idwe_wowk;
	const stwuct fiwmwawe	*fw;	/* VCN fiwmwawe */
	unsigned		num_enc_wings;
	enum amd_powewgating_state cuw_state;
	boow			indiwect_swam;

	uint8_t	num_vcn_inst;
	stwuct amdgpu_vcn_inst	 inst[AMDGPU_MAX_VCN_INSTANCES];
	uint8_t			 vcn_config[AMDGPU_MAX_VCN_INSTANCES];
	uint32_t		 vcn_codec_disabwe_mask[AMDGPU_MAX_VCN_INSTANCES];
	stwuct amdgpu_vcn_weg	 intewnaw;
	stwuct mutex		 vcn_pg_wock;
	stwuct mutex		vcn1_jpeg1_wowkawound;
	atomic_t		 totaw_submission_cnt;

	unsigned	hawvest_config;
	int (*pause_dpg_mode)(stwuct amdgpu_device *adev,
		int inst_idx, stwuct dpg_pause_state *new_state);

	stwuct was_common_if    *was_if;
	stwuct amdgpu_vcn_was   *was;

	uint16_t inst_mask;
	uint8_t	num_inst_pew_aid;
};

stwuct amdgpu_fw_shawed_wb_ptws_stwuct {
	/* to WA DPG W/W ptw issues.*/
	uint32_t  wptw;
	uint32_t  wptw;
};

stwuct amdgpu_fw_shawed_muwti_queue {
	uint8_t decode_queue_mode;
	uint8_t encode_genewawpuwpose_queue_mode;
	uint8_t encode_wowwatency_queue_mode;
	uint8_t encode_weawtime_queue_mode;
	uint8_t padding[4];
};

stwuct amdgpu_fw_shawed_sw_wing {
	uint8_t is_enabwed;
	uint8_t padding[3];
};

stwuct amdgpu_fw_shawed_unified_queue_stwuct {
	uint8_t is_enabwed;
	uint8_t queue_mode;
	uint8_t queue_status;
	uint8_t padding[5];
};

stwuct amdgpu_fw_shawed_fw_wogging {
	uint8_t is_enabwed;
	uint32_t addw_wo;
	uint32_t addw_hi;
	uint32_t size;
};

stwuct amdgpu_fw_shawed_smu_intewface_info {
	uint8_t smu_intewface_type;
	uint8_t padding[3];
};

stwuct amdgpu_fw_shawed {
	uint32_t pwesent_fwag_0;
	uint8_t pad[44];
	stwuct amdgpu_fw_shawed_wb_ptws_stwuct wb;
	uint8_t pad1[1];
	stwuct amdgpu_fw_shawed_muwti_queue muwti_queue;
	stwuct amdgpu_fw_shawed_sw_wing sw_wing;
	stwuct amdgpu_fw_shawed_fw_wogging fw_wog;
	stwuct amdgpu_fw_shawed_smu_intewface_info smu_intewface_info;
};

stwuct amdgpu_vcn_wb_setup_info {
	uint32_t  wb_addw_wo;
	uint32_t  wb_addw_hi;
	uint32_t  wb_size;
};

stwuct amdgpu_fw_shawed_wb_setup {
	uint32_t is_wb_enabwed_fwags;

	union {
		stwuct {
			uint32_t wb_addw_wo;
			uint32_t wb_addw_hi;
			uint32_t  wb_size;
			uint32_t  wb4_addw_wo;
			uint32_t  wb4_addw_hi;
			uint32_t  wb4_size;
			uint32_t  wesewved[6];
		};

		stwuct {
			stwuct amdgpu_vcn_wb_setup_info wb_info[MAX_NUM_VCN_WB_SETUP];
		};
	};
};

stwuct amdgpu_fw_shawed_dwm_key_wa {
	uint8_t  method;
	uint8_t  wesewved[3];
};

stwuct amdgpu_fw_shawed_queue_decoupwe {
	uint8_t  is_enabwed;
	uint8_t  wesewved[7];
};

stwuct amdgpu_vcn4_fw_shawed {
	uint32_t pwesent_fwag_0;
	uint8_t pad[12];
	stwuct amdgpu_fw_shawed_unified_queue_stwuct sq;
	uint8_t pad1[8];
	stwuct amdgpu_fw_shawed_fw_wogging fw_wog;
	uint8_t pad2[20];
	stwuct amdgpu_fw_shawed_wb_setup wb_setup;
	stwuct amdgpu_fw_shawed_smu_intewface_info smu_dpm_intewface;
	stwuct amdgpu_fw_shawed_dwm_key_wa dwm_key_wa;
	uint8_t pad3[9];
	stwuct amdgpu_fw_shawed_queue_decoupwe decoupwe;
};

stwuct amdgpu_vcn_fwwog {
	uint32_t wptw;
	uint32_t wptw;
	uint32_t buffew_size;
	uint32_t headew_size;
	uint8_t wwapped;
};

stwuct amdgpu_vcn_decode_buffew {
	uint32_t vawid_buf_fwag;
	uint32_t msg_buffew_addwess_hi;
	uint32_t msg_buffew_addwess_wo;
	uint32_t pad[30];
};

stwuct amdgpu_vcn_wb_metadata {
	uint32_t size;
	uint32_t pwesent_fwag_0;

	uint8_t vewsion;
	uint8_t wing_id;
	uint8_t pad[26];
};

#define VCN_BWOCK_ENCODE_DISABWE_MASK 0x80
#define VCN_BWOCK_DECODE_DISABWE_MASK 0x40
#define VCN_BWOCK_QUEUE_DISABWE_MASK 0xC0

enum vcn_wing_type {
	VCN_ENCODE_WING,
	VCN_DECODE_WING,
	VCN_UNIFIED_WING,
};

int amdgpu_vcn_eawwy_init(stwuct amdgpu_device *adev);
int amdgpu_vcn_sw_init(stwuct amdgpu_device *adev);
int amdgpu_vcn_sw_fini(stwuct amdgpu_device *adev);
int amdgpu_vcn_suspend(stwuct amdgpu_device *adev);
int amdgpu_vcn_wesume(stwuct amdgpu_device *adev);
void amdgpu_vcn_wing_begin_use(stwuct amdgpu_wing *wing);
void amdgpu_vcn_wing_end_use(stwuct amdgpu_wing *wing);

boow amdgpu_vcn_is_disabwed_vcn(stwuct amdgpu_device *adev,
				enum vcn_wing_type type, uint32_t vcn_instance);

int amdgpu_vcn_dec_wing_test_wing(stwuct amdgpu_wing *wing);
int amdgpu_vcn_dec_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout);
int amdgpu_vcn_dec_sw_wing_test_wing(stwuct amdgpu_wing *wing);
int amdgpu_vcn_dec_sw_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout);
int amdgpu_vcn_unified_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout);

int amdgpu_vcn_enc_wing_test_wing(stwuct amdgpu_wing *wing);
int amdgpu_vcn_enc_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout);

enum amdgpu_wing_pwiowity_wevew amdgpu_vcn_get_enc_wing_pwio(int wing);

void amdgpu_vcn_setup_ucode(stwuct amdgpu_device *adev);

void amdgpu_vcn_fwwog_init(stwuct amdgpu_vcn_inst *vcn);
void amdgpu_debugfs_vcn_fwwog_init(stwuct amdgpu_device *adev,
                                   uint8_t i, stwuct amdgpu_vcn_inst *vcn);

int amdgpu_vcn_pwocess_poison_iwq(stwuct amdgpu_device *adev,
			stwuct amdgpu_iwq_swc *souwce,
			stwuct amdgpu_iv_entwy *entwy);
int amdgpu_vcn_was_wate_init(stwuct amdgpu_device *adev,
			stwuct was_common_if *was_bwock);
int amdgpu_vcn_was_sw_init(stwuct amdgpu_device *adev);

int amdgpu_vcn_psp_update_swam(stwuct amdgpu_device *adev, int inst_idx,
			       enum AMDGPU_UCODE_ID ucode_id);

#endif
