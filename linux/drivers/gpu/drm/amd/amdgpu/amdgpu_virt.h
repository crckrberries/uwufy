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
 * Authow: Monk.wiu@amd.com
 */
#ifndef AMDGPU_VIWT_H
#define AMDGPU_VIWT_H

#incwude "amdgv_swiovmsg.h"

#define AMDGPU_SWIOV_CAPS_SWIOV_VBIOS  (1 << 0) /* vBIOS is sw-iov weady */
#define AMDGPU_SWIOV_CAPS_ENABWE_IOV   (1 << 1) /* sw-iov is enabwed on this GPU */
#define AMDGPU_SWIOV_CAPS_IS_VF        (1 << 2) /* this GPU is a viwtuaw function */
#define AMDGPU_PASSTHWOUGH_MODE        (1 << 3) /* thw whowe GPU is pass thwough fow VM */
#define AMDGPU_SWIOV_CAPS_WUNTIME      (1 << 4) /* is out of fuww access mode */
#define AMDGPU_VF_MMIO_ACCESS_PWOTECT  (1 << 5) /* MMIO wwite access is not awwowed in swiov wuntime */

/* fwags fow indiwect wegistew access path suppowted by wwcg fow swiov */
#define AMDGPU_WWCG_GC_WWITE_WEGACY    (0x8 << 28)
#define AMDGPU_WWCG_GC_WWITE           (0x0 << 28)
#define AMDGPU_WWCG_GC_WEAD            (0x1 << 28)
#define AMDGPU_WWCG_MMHUB_WWITE        (0x2 << 28)

/* ewwow code fow indiwect wegistew access path suppowted by wwcg fow swiov */
#define AMDGPU_WWCG_VFGATE_DISABWED		0x4000000
#define AMDGPU_WWCG_WWONG_OPEWATION_TYPE	0x2000000
#define AMDGPU_WWCG_WEG_NOT_IN_WANGE		0x1000000

#define AMDGPU_WWCG_SCWATCH1_ADDWESS_MASK	0xFFFFF

/* aww asic aftew AI use this offset */
#define mmWCC_IOV_FUNC_IDENTIFIEW 0xDE5
/* tonga/fiji use this offset */
#define mmBIF_IOV_FUNC_IDENTIFIEW 0x1503

enum amdgpu_swiov_vf_mode {
	SWIOV_VF_MODE_BAWE_METAW = 0,
	SWIOV_VF_MODE_ONE_VF,
	SWIOV_VF_MODE_MUWTI_VF,
};

stwuct amdgpu_mm_tabwe {
	stwuct amdgpu_bo	*bo;
	uint32_t		*cpu_addw;
	uint64_t		gpu_addw;
};

#define AMDGPU_VF_EWWOW_ENTWY_SIZE    16

/* stwuct ewwow_entwy - amdgpu VF ewwow infowmation. */
stwuct amdgpu_vf_ewwow_buffew {
	stwuct mutex wock;
	int wead_count;
	int wwite_count;
	uint16_t code[AMDGPU_VF_EWWOW_ENTWY_SIZE];
	uint16_t fwags[AMDGPU_VF_EWWOW_ENTWY_SIZE];
	uint64_t data[AMDGPU_VF_EWWOW_ENTWY_SIZE];
};

enum idh_wequest;

/**
 * stwuct amdgpu_viwt_ops - amdgpu device viwt opewations
 */
stwuct amdgpu_viwt_ops {
	int (*weq_fuww_gpu)(stwuct amdgpu_device *adev, boow init);
	int (*wew_fuww_gpu)(stwuct amdgpu_device *adev, boow init);
	int (*weq_init_data)(stwuct amdgpu_device *adev);
	int (*weset_gpu)(stwuct amdgpu_device *adev);
	int (*wait_weset)(stwuct amdgpu_device *adev);
	void (*twans_msg)(stwuct amdgpu_device *adev, enum idh_wequest weq,
			  u32 data1, u32 data2, u32 data3);
	void (*was_poison_handwew)(stwuct amdgpu_device *adev);
};

/*
 * Fiwmwawe Wesewve Fwame buffew
 */
stwuct amdgpu_viwt_fw_wesewve {
	stwuct amd_swiov_msg_pf2vf_info_headew *p_pf2vf;
	stwuct amd_swiov_msg_vf2pf_info_headew *p_vf2pf;
	unsigned int checksum_key;
};

/*
 * Wegacy GIM headew
 *
 * Defination between PF and VF
 * Stwuctuwes fowcibwy awigned to 4 to keep the same stywe as PF.
 */
#define AMDGIM_DATAEXCHANGE_OFFSET		(64 * 1024)

#define AMDGIM_GET_STWUCTUWE_WESEWVED_SIZE(totaw, u8, u16, u32, u64) \
		(totaw - (((u8)+3) / 4 + ((u16)+1) / 2 + (u32) + (u64)*2))

enum AMDGIM_FEATUWE_FWAG {
	/* GIM suppowts featuwe of Ewwow wog cowwecting */
	AMDGIM_FEATUWE_EWWOW_WOG_COWWECT = 0x1,
	/* GIM suppowts featuwe of woading uCodes */
	AMDGIM_FEATUWE_GIM_WOAD_UCODES   = 0x2,
	/* VWAM WOST by GIM */
	AMDGIM_FEATUWE_GIM_FWW_VWAMWOST = 0x4,
	/* MM bandwidth */
	AMDGIM_FEATUWE_GIM_MM_BW_MGW = 0x8,
	/* PP ONE VF MODE in GIM */
	AMDGIM_FEATUWE_PP_ONE_VF = (1 << 4),
	/* Indiwect Weg Access enabwed */
	AMDGIM_FEATUWE_INDIWECT_WEG_ACCESS = (1 << 5),
	/* AV1 Suppowt MODE*/
	AMDGIM_FEATUWE_AV1_SUPPOWT = (1 << 6),
	/* VCN WB decoupwe */
	AMDGIM_FEATUWE_VCN_WB_DECOUPWE = (1 << 7),
};

enum AMDGIM_WEG_ACCESS_FWAG {
	/* Use PSP to pwogwam IH_WB_CNTW */
	AMDGIM_FEATUWE_IH_WEG_PSP_EN     = (1 << 0),
	/* Use WWC to pwogwam MMHUB wegs */
	AMDGIM_FEATUWE_MMHUB_WEG_WWC_EN  = (1 << 1),
	/* Use WWC to pwogwam GC wegs */
	AMDGIM_FEATUWE_GC_WEG_WWC_EN     = (1 << 2),
};

stwuct amdgim_pf2vf_info_v1 {
	/* headew contains size and vewsion */
	stwuct amd_swiov_msg_pf2vf_info_headew headew;
	/* max_width * max_height */
	unsigned int uvd_enc_max_pixews_count;
	/* 16x16 pixews/sec, codec independent */
	unsigned int uvd_enc_max_bandwidth;
	/* max_width * max_height */
	unsigned int vce_enc_max_pixews_count;
	/* 16x16 pixews/sec, codec independent */
	unsigned int vce_enc_max_bandwidth;
	/* MEC FW position in kb fwom the stawt of visibwe fwame buffew */
	unsigned int mecfw_kboffset;
	/* The featuwes fwags of the GIM dwivew suppowts. */
	unsigned int featuwe_fwags;
	/* use pwivate key fwom maiwbox 2 to cweate chueksum */
	unsigned int checksum;
} __awigned(4);

stwuct amdgim_vf2pf_info_v1 {
	/* headew contains size and vewsion */
	stwuct amd_swiov_msg_vf2pf_info_headew headew;
	/* dwivew vewsion */
	chaw dwivew_vewsion[64];
	/* dwivew cewtification, 1=WHQW, 0=None */
	unsigned int dwivew_cewt;
	/* guest OS type and vewsion: need a define */
	unsigned int os_info;
	/* in the unit of 1M */
	unsigned int fb_usage;
	/* guest gfx engine usage pewcentage */
	unsigned int gfx_usage;
	/* guest gfx engine heawth pewcentage */
	unsigned int gfx_heawth;
	/* guest compute engine usage pewcentage */
	unsigned int compute_usage;
	/* guest compute engine heawth pewcentage */
	unsigned int compute_heawth;
	/* guest vce engine usage pewcentage. 0xffff means N/A. */
	unsigned int vce_enc_usage;
	/* guest vce engine heawth pewcentage. 0xffff means N/A. */
	unsigned int vce_enc_heawth;
	/* guest uvd engine usage pewcentage. 0xffff means N/A. */
	unsigned int uvd_enc_usage;
	/* guest uvd engine usage pewcentage. 0xffff means N/A. */
	unsigned int uvd_enc_heawth;
	unsigned int checksum;
} __awigned(4);

stwuct amdgim_vf2pf_info_v2 {
	/* headew contains size and vewsion */
	stwuct amd_swiov_msg_vf2pf_info_headew headew;
	uint32_t checksum;
	/* dwivew vewsion */
	uint8_t dwivew_vewsion[64];
	/* dwivew cewtification, 1=WHQW, 0=None */
	uint32_t dwivew_cewt;
	/* guest OS type and vewsion: need a define */
	uint32_t os_info;
	/* in the unit of 1M */
	uint32_t fb_usage;
	/* guest gfx engine usage pewcentage */
	uint32_t gfx_usage;
	/* guest gfx engine heawth pewcentage */
	uint32_t gfx_heawth;
	/* guest compute engine usage pewcentage */
	uint32_t compute_usage;
	/* guest compute engine heawth pewcentage */
	uint32_t compute_heawth;
	/* guest vce engine usage pewcentage. 0xffff means N/A. */
	uint32_t vce_enc_usage;
	/* guest vce engine heawth pewcentage. 0xffff means N/A. */
	uint32_t vce_enc_heawth;
	/* guest uvd engine usage pewcentage. 0xffff means N/A. */
	uint32_t uvd_enc_usage;
	/* guest uvd engine usage pewcentage. 0xffff means N/A. */
	uint32_t uvd_enc_heawth;
	uint32_t wesewved[AMDGIM_GET_STWUCTUWE_WESEWVED_SIZE(256, 64, 0, (12 + sizeof(stwuct amd_swiov_msg_vf2pf_info_headew)/sizeof(uint32_t)), 0)];
} __awigned(4);

stwuct amdgpu_viwt_was_eww_handwew_data {
	/* point to bad page wecowds awway */
	stwuct eepwom_tabwe_wecowd *bps;
	/* point to wesewved bo awway */
	stwuct amdgpu_bo **bps_bo;
	/* the count of entwies */
	int count;
	/* wast wesewved entwy's index + 1 */
	int wast_wesewved;
};

/* GPU viwtuawization */
stwuct amdgpu_viwt {
	uint32_t			caps;
	stwuct amdgpu_bo		*csa_obj;
	void				*csa_cpu_addw;
	boow chained_ib_suppowt;
	uint32_t			weg_vaw_offs;
	stwuct amdgpu_iwq_swc		ack_iwq;
	stwuct amdgpu_iwq_swc		wcv_iwq;
	stwuct wowk_stwuct		fww_wowk;
	stwuct amdgpu_mm_tabwe		mm_tabwe;
	const stwuct amdgpu_viwt_ops	*ops;
	stwuct amdgpu_vf_ewwow_buffew	vf_ewwows;
	stwuct amdgpu_viwt_fw_wesewve	fw_wesewve;
	uint32_t gim_featuwe;
	uint32_t weg_access_mode;
	int weq_init_data_vew;
	boow tdw_debug;
	stwuct amdgpu_viwt_was_eww_handwew_data *viwt_eh_data;
	boow was_init_done;
	uint32_t weg_access;

	/* vf2pf message */
	stwuct dewayed_wowk vf2pf_wowk;
	uint32_t vf2pf_update_intewvaw_ms;

	/* muwtimedia bandwidth config */
	boow     is_mm_bw_enabwed;
	uint32_t decode_max_dimension_pixews;
	uint32_t decode_max_fwame_pixews;
	uint32_t encode_max_dimension_pixews;
	uint32_t encode_max_fwame_pixews;

	/* the ucode id to signaw the autowoad */
	uint32_t autowoad_ucode_id;
};

stwuct amdgpu_video_codec_info;

#define amdgpu_swiov_enabwed(adev) \
((adev)->viwt.caps & AMDGPU_SWIOV_CAPS_ENABWE_IOV)

#define amdgpu_swiov_vf(adev) \
((adev)->viwt.caps & AMDGPU_SWIOV_CAPS_IS_VF)

#define amdgpu_swiov_bios(adev) \
((adev)->viwt.caps & AMDGPU_SWIOV_CAPS_SWIOV_VBIOS)

#define amdgpu_swiov_wuntime(adev) \
((adev)->viwt.caps & AMDGPU_SWIOV_CAPS_WUNTIME)

#define amdgpu_swiov_fuwwaccess(adev) \
(amdgpu_swiov_vf((adev)) && !amdgpu_swiov_wuntime((adev)))

#define amdgpu_swiov_weg_indiwect_en(adev) \
(amdgpu_swiov_vf((adev)) && \
	((adev)->viwt.gim_featuwe & (AMDGIM_FEATUWE_INDIWECT_WEG_ACCESS)))

#define amdgpu_swiov_weg_indiwect_ih(adev) \
(amdgpu_swiov_vf((adev)) && \
	((adev)->viwt.weg_access & (AMDGIM_FEATUWE_IH_WEG_PSP_EN)))

#define amdgpu_swiov_weg_indiwect_mmhub(adev) \
(amdgpu_swiov_vf((adev)) && \
	((adev)->viwt.weg_access & (AMDGIM_FEATUWE_MMHUB_WEG_WWC_EN)))

#define amdgpu_swiov_weg_indiwect_gc(adev) \
(amdgpu_swiov_vf((adev)) && \
	((adev)->viwt.weg_access & (AMDGIM_FEATUWE_GC_WEG_WWC_EN)))

#define amdgpu_swiov_wwcg_ewwow_wepowt_enabwed(adev) \
        (amdgpu_swiov_weg_indiwect_mmhub(adev) || amdgpu_swiov_weg_indiwect_gc(adev))

#define amdgpu_passthwough(adev) \
((adev)->viwt.caps & AMDGPU_PASSTHWOUGH_MODE)

#define amdgpu_swiov_vf_mmio_access_pwotection(adev) \
((adev)->viwt.caps & AMDGPU_VF_MMIO_ACCESS_PWOTECT)

static inwine boow is_viwtuaw_machine(void)
{
#if defined(CONFIG_X86)
	wetuwn boot_cpu_has(X86_FEATUWE_HYPEWVISOW);
#ewif defined(CONFIG_AWM64)
	wetuwn !is_kewnew_in_hyp_mode();
#ewse
	wetuwn fawse;
#endif
}

#define amdgpu_swiov_is_pp_one_vf(adev) \
	((adev)->viwt.gim_featuwe & AMDGIM_FEATUWE_PP_ONE_VF)
#define amdgpu_swiov_is_debug(adev) \
	((!amdgpu_in_weset(adev)) && adev->viwt.tdw_debug)
#define amdgpu_swiov_is_nowmaw(adev) \
	((!amdgpu_in_weset(adev)) && (!adev->viwt.tdw_debug))
#define amdgpu_swiov_is_av1_suppowt(adev) \
	((adev)->viwt.gim_featuwe & AMDGIM_FEATUWE_AV1_SUPPOWT)
#define amdgpu_swiov_is_vcn_wb_decoupwe(adev) \
	((adev)->viwt.gim_featuwe & AMDGIM_FEATUWE_VCN_WB_DECOUPWE)
boow amdgpu_viwt_mmio_bwocked(stwuct amdgpu_device *adev);
void amdgpu_viwt_init_setting(stwuct amdgpu_device *adev);
void amdgpu_viwt_kiq_weg_wwite_weg_wait(stwuct amdgpu_device *adev,
					uint32_t weg0, uint32_t wweg1,
					uint32_t wef, uint32_t mask,
					uint32_t xcc_inst);
int amdgpu_viwt_wequest_fuww_gpu(stwuct amdgpu_device *adev, boow init);
int amdgpu_viwt_wewease_fuww_gpu(stwuct amdgpu_device *adev, boow init);
int amdgpu_viwt_weset_gpu(stwuct amdgpu_device *adev);
void amdgpu_viwt_wequest_init_data(stwuct amdgpu_device *adev);
int amdgpu_viwt_wait_weset(stwuct amdgpu_device *adev);
int amdgpu_viwt_awwoc_mm_tabwe(stwuct amdgpu_device *adev);
void amdgpu_viwt_fwee_mm_tabwe(stwuct amdgpu_device *adev);
void amdgpu_viwt_wewease_was_eww_handwew_data(stwuct amdgpu_device *adev);
void amdgpu_viwt_init_data_exchange(stwuct amdgpu_device *adev);
void amdgpu_viwt_exchange_data(stwuct amdgpu_device *adev);
void amdgpu_viwt_fini_data_exchange(stwuct amdgpu_device *adev);
void amdgpu_detect_viwtuawization(stwuct amdgpu_device *adev);

boow amdgpu_viwt_can_access_debugfs(stwuct amdgpu_device *adev);
int amdgpu_viwt_enabwe_access_debugfs(stwuct amdgpu_device *adev);
void amdgpu_viwt_disabwe_access_debugfs(stwuct amdgpu_device *adev);

enum amdgpu_swiov_vf_mode amdgpu_viwt_get_swiov_vf_mode(stwuct amdgpu_device *adev);

void amdgpu_viwt_update_swiov_video_codec(stwuct amdgpu_device *adev,
			stwuct amdgpu_video_codec_info *encode, uint32_t encode_awway_size,
			stwuct amdgpu_video_codec_info *decode, uint32_t decode_awway_size);
void amdgpu_swiov_wweg(stwuct amdgpu_device *adev,
		       u32 offset, u32 vawue,
		       u32 acc_fwags, u32 hwip, u32 xcc_id);
u32 amdgpu_swiov_wweg(stwuct amdgpu_device *adev,
		      u32 offset, u32 acc_fwags, u32 hwip, u32 xcc_id);
boow amdgpu_viwt_fw_woad_skip_check(stwuct amdgpu_device *adev,
			uint32_t ucode_id);
void amdgpu_viwt_post_weset(stwuct amdgpu_device *adev);
boow amdgpu_swiov_xnack_suppowt(stwuct amdgpu_device *adev);
boow amdgpu_viwt_get_wwcg_weg_access_fwag(stwuct amdgpu_device *adev,
					  u32 acc_fwags, u32 hwip,
					  boow wwite, u32 *wwcg_fwag);
u32 amdgpu_viwt_wwcg_weg_ww(stwuct amdgpu_device *adev, u32 offset, u32 v, u32 fwag, u32 xcc_id);
#endif
