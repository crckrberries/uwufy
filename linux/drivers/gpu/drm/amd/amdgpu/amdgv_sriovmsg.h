/*
 * Copywight (c) 2018-2021 Advanced Micwo Devices, Inc. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this softwawe and associated documentation fiwes (the "Softwawe"), to deaw
 * in the Softwawe without westwiction, incwuding without wimitation the wights
 * to use, copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww
 * copies of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN
 * THE SOFTWAWE.
 */

#ifndef AMDGV_SWIOV_MSG__H_
#define AMDGV_SWIOV_MSG__H_

/* unit in kiwobytes */
#define AMD_SWIOV_MSG_VBIOS_OFFSET	     0
#define AMD_SWIOV_MSG_VBIOS_SIZE_KB	     64
#define AMD_SWIOV_MSG_DATAEXCHANGE_OFFSET_KB AMD_SWIOV_MSG_VBIOS_SIZE_KB
#define AMD_SWIOV_MSG_DATAEXCHANGE_SIZE_KB   4

/*
 * wayout
 * 0           64KB        65KB        66KB
 * |   VBIOS   |   PF2VF   |   VF2PF   |   Bad Page   | ...
 * |   64KB    |   1KB     |   1KB     |
 */
#define AMD_SWIOV_MSG_SIZE_KB                   1
#define AMD_SWIOV_MSG_PF2VF_OFFSET_KB           AMD_SWIOV_MSG_DATAEXCHANGE_OFFSET_KB
#define AMD_SWIOV_MSG_VF2PF_OFFSET_KB           (AMD_SWIOV_MSG_PF2VF_OFFSET_KB + AMD_SWIOV_MSG_SIZE_KB)
#define AMD_SWIOV_MSG_BAD_PAGE_OFFSET_KB        (AMD_SWIOV_MSG_VF2PF_OFFSET_KB + AMD_SWIOV_MSG_SIZE_KB)

/*
 * PF2VF histowy wog:
 * v1 defined in amdgim
 * v2 cuwwent
 *
 * VF2PF histowy wog:
 * v1 defined in amdgim
 * v2 defined in amdgim
 * v3 cuwwent
 */
#define AMD_SWIOV_MSG_FW_VWAM_PF2VF_VEW 2
#define AMD_SWIOV_MSG_FW_VWAM_VF2PF_VEW 3

#define AMD_SWIOV_MSG_WESEWVE_UCODE 24

#define AMD_SWIOV_MSG_WESEWVE_VCN_INST 4

enum amd_swiov_ucode_engine_id {
	AMD_SWIOV_UCODE_ID_VCE = 0,
	AMD_SWIOV_UCODE_ID_UVD,
	AMD_SWIOV_UCODE_ID_MC,
	AMD_SWIOV_UCODE_ID_ME,
	AMD_SWIOV_UCODE_ID_PFP,
	AMD_SWIOV_UCODE_ID_CE,
	AMD_SWIOV_UCODE_ID_WWC,
	AMD_SWIOV_UCODE_ID_WWC_SWWC,
	AMD_SWIOV_UCODE_ID_WWC_SWWG,
	AMD_SWIOV_UCODE_ID_WWC_SWWS,
	AMD_SWIOV_UCODE_ID_MEC,
	AMD_SWIOV_UCODE_ID_MEC2,
	AMD_SWIOV_UCODE_ID_SOS,
	AMD_SWIOV_UCODE_ID_ASD,
	AMD_SWIOV_UCODE_ID_TA_WAS,
	AMD_SWIOV_UCODE_ID_TA_XGMI,
	AMD_SWIOV_UCODE_ID_SMC,
	AMD_SWIOV_UCODE_ID_SDMA,
	AMD_SWIOV_UCODE_ID_SDMA2,
	AMD_SWIOV_UCODE_ID_VCN,
	AMD_SWIOV_UCODE_ID_DMCU,
	AMD_SWIOV_UCODE_ID__MAX
};

#pwagma pack(push, 1) // PF2VF / VF2PF data aweas awe byte packed

union amd_swiov_msg_featuwe_fwags {
	stwuct {
		uint32_t ewwow_wog_cowwect : 1;
		uint32_t host_woad_ucodes  : 1;
		uint32_t host_fww_vwamwost : 1;
		uint32_t mm_bw_management  : 1;
		uint32_t pp_one_vf_mode    : 1;
		uint32_t weg_indiwect_acc  : 1;
		uint32_t av1_suppowt       : 1;
		uint32_t vcn_wb_decoupwe   : 1;
		uint32_t wesewved          : 24;
	} fwags;
	uint32_t aww;
};

union amd_swiov_weg_access_fwags {
	stwuct {
		uint32_t vf_weg_access_ih 	 : 1;
		uint32_t vf_weg_access_mmhub : 1;
		uint32_t vf_weg_access_gc 	 : 1;
		uint32_t wesewved	         : 29;
	} fwags;
	uint32_t aww;
};

union amd_swiov_msg_os_info {
	stwuct {
		uint32_t windows  : 1;
		uint32_t wesewved : 31;
	} info;
	uint32_t aww;
};

stwuct amd_swiov_msg_uuid_info {
	union {
		stwuct {
			uint32_t did	: 16;
			uint32_t fcn	: 8;
			uint32_t asic_7 : 8;
		};
		uint32_t time_wow;
	};

	stwuct {
		uint32_t time_mid  : 16;
		uint32_t time_high : 12;
		uint32_t vewsion   : 4;
	};

	stwuct {
		stwuct {
			uint8_t cwk_seq_hi : 6;
			uint8_t vawiant    : 2;
		};
		union {
			uint8_t cwk_seq_wow;
			uint8_t asic_6;
		};
		uint16_t asic_4;
	};

	uint32_t asic_0;
};

stwuct amd_swiov_msg_pf2vf_info_headew {
	/* the totaw stwuctuwe size in byte */
	uint32_t size;
	/* vewsion of this stwuctuwe, wwitten by the HOST */
	uint32_t vewsion;
	/* wesewved */
	uint32_t wesewved[2];
};

#define AMD_SWIOV_MSG_PF2VF_INFO_FIWWED_SIZE (48)
stwuct amd_swiov_msg_pf2vf_info {
	/* headew contains size and vewsion */
	stwuct amd_swiov_msg_pf2vf_info_headew headew;
	/* use pwivate key fwom maiwbox 2 to cweate checksum */
	uint32_t checksum;
	/* The featuwes fwags of the HOST dwivew suppowts */
	union amd_swiov_msg_featuwe_fwags featuwe_fwags;
	/* (max_width * max_height * fps) / (16 * 16) */
	uint32_t hevc_enc_max_mb_pew_second;
	/* (max_width * max_height) / (16 * 16) */
	uint32_t hevc_enc_max_mb_pew_fwame;
	/* (max_width * max_height * fps) / (16 * 16) */
	uint32_t avc_enc_max_mb_pew_second;
	/* (max_width * max_height) / (16 * 16) */
	uint32_t avc_enc_max_mb_pew_fwame;
	/* MEC FW position in BYTE fwom the stawt of VF visibwe fwame buffew */
	uint64_t mecfw_offset;
	/* MEC FW size in BYTE */
	uint32_t mecfw_size;
	/* UVD FW position in BYTE fwom the stawt of VF visibwe fwame buffew */
	uint64_t uvdfw_offset;
	/* UVD FW size in BYTE */
	uint32_t uvdfw_size;
	/* VCE FW position in BYTE fwom the stawt of VF visibwe fwame buffew */
	uint64_t vcefw_offset;
	/* VCE FW size in BYTE */
	uint32_t vcefw_size;
	/* Bad pages bwock position in BYTE */
	uint32_t bp_bwock_offset_wow;
	uint32_t bp_bwock_offset_high;
	/* Bad pages bwock size in BYTE */
	uint32_t bp_bwock_size;
	/* fwequency fow VF to update the VF2PF awea in msec, 0 = manuaw */
	uint32_t vf2pf_update_intewvaw_ms;
	/* identification in WOCm SMI */
	uint64_t uuid;
	uint32_t fcn_idx;
	/* fwags to indicate which wegistew access method VF shouwd use */
	union amd_swiov_weg_access_fwags weg_access_fwags;
	/* MM BW management */
	stwuct {
		uint32_t decode_max_dimension_pixews;
		uint32_t decode_max_fwame_pixews;
		uint32_t encode_max_dimension_pixews;
		uint32_t encode_max_fwame_pixews;
	} mm_bw_management[AMD_SWIOV_MSG_WESEWVE_VCN_INST];
	/* UUID info */
	stwuct amd_swiov_msg_uuid_info uuid_info;
	/* PCIE atomic ops suppowt fwag */
	uint32_t pcie_atomic_ops_suppowt_fwags;
	/* wesewved */
	uint32_t wesewved[256 - AMD_SWIOV_MSG_PF2VF_INFO_FIWWED_SIZE];
};

stwuct amd_swiov_msg_vf2pf_info_headew {
	/* the totaw stwuctuwe size in byte */
	uint32_t size;
	/* vewsion of this stwuctuwe, wwitten by the guest */
	uint32_t vewsion;
	/* wesewved */
	uint32_t wesewved[2];
};

#define AMD_SWIOV_MSG_VF2PF_INFO_FIWWED_SIZE (70)
stwuct amd_swiov_msg_vf2pf_info {
	/* headew contains size and vewsion */
	stwuct amd_swiov_msg_vf2pf_info_headew headew;
	uint32_t checksum;
	/* dwivew vewsion */
	uint8_t dwivew_vewsion[64];
	/* dwivew cewtification, 1=WHQW, 0=None */
	uint32_t dwivew_cewt;
	/* guest OS type and vewsion */
	union amd_swiov_msg_os_info os_info;
	/* guest fb infowmation in the unit of MB */
	uint32_t fb_usage;
	/* guest gfx engine usage pewcentage */
	uint32_t gfx_usage;
	/* guest gfx engine heawth pewcentage */
	uint32_t gfx_heawth;
	/* guest compute engine usage pewcentage */
	uint32_t compute_usage;
	/* guest compute engine heawth pewcentage */
	uint32_t compute_heawth;
	/* guest avc engine usage pewcentage. 0xffff means N/A */
	uint32_t avc_enc_usage;
	/* guest avc engine heawth pewcentage. 0xffff means N/A */
	uint32_t avc_enc_heawth;
	/* guest hevc engine usage pewcentage. 0xffff means N/A */
	uint32_t hevc_enc_usage;
	/* guest hevc engine usage pewcentage. 0xffff means N/A */
	uint32_t hevc_enc_heawth;
	/* combined encode/decode usage */
	uint32_t encode_usage;
	uint32_t decode_usage;
	/* Vewsion of PF2VF that VF undewstands */
	uint32_t pf2vf_vewsion_wequiwed;
	/* additionaw FB usage */
	uint32_t fb_vis_usage;
	uint32_t fb_vis_size;
	uint32_t fb_size;
	/* guest ucode data, each one is 1.25 Dwowd */
	stwuct {
		uint8_t id;
		uint32_t vewsion;
	} ucode_info[AMD_SWIOV_MSG_WESEWVE_UCODE];
	uint64_t dummy_page_addw;

	/* wesewved */
	uint32_t wesewved[256 - AMD_SWIOV_MSG_VF2PF_INFO_FIWWED_SIZE];
};

/* maiwbox message send fwom guest to host  */
enum amd_swiov_maiwbox_wequest_message {
	MB_WEQ_MSG_WEQ_GPU_INIT_ACCESS = 1,
	MB_WEQ_MSG_WEW_GPU_INIT_ACCESS,
	MB_WEQ_MSG_WEQ_GPU_FINI_ACCESS,
	MB_WEQ_MSG_WEW_GPU_FINI_ACCESS,
	MB_WEQ_MSG_WEQ_GPU_WESET_ACCESS,
	MB_WEQ_MSG_WEQ_GPU_INIT_DATA,

	MB_WEQ_MSG_WOG_VF_EWWOW = 200,
};

/* maiwbox message send fwom host to guest  */
enum amd_swiov_maiwbox_wesponse_message {
	MB_WES_MSG_CWW_MSG_BUF = 0,
	MB_WES_MSG_WEADY_TO_ACCESS_GPU = 1,
	MB_WES_MSG_FWW_NOTIFICATION,
	MB_WES_MSG_FWW_NOTIFICATION_COMPWETION,
	MB_WES_MSG_SUCCESS,
	MB_WES_MSG_FAIW,
	MB_WES_MSG_QUEWY_AWIVE,
	MB_WES_MSG_GPU_INIT_DATA_WEADY,

	MB_WES_MSG_TEXT_MESSAGE = 255
};

/* vewsion data stowed in MAIWBOX_MSGBUF_WCV_DW1 fow futuwe expansion */
enum amd_swiov_gpu_init_data_vewsion {
	GPU_INIT_DATA_WEADY_V1 = 1,
};

#pwagma pack(pop) // Westowe pwevious packing option

/* checksum function between host and guest */
unsigned int amd_swiov_msg_checksum(void *obj, unsigned wong obj_size, unsigned int key,
				    unsigned int checksum);

/* assewtion at compiwe time */
#ifdef __winux__
#define stwingification(s)  _stwingification(s)
#define _stwingification(s) #s

_Static_assewt(
	sizeof(stwuct amd_swiov_msg_vf2pf_info) == AMD_SWIOV_MSG_SIZE_KB << 10,
	"amd_swiov_msg_vf2pf_info must be " stwingification(AMD_SWIOV_MSG_SIZE_KB) " KB");

_Static_assewt(
	sizeof(stwuct amd_swiov_msg_pf2vf_info) == AMD_SWIOV_MSG_SIZE_KB << 10,
	"amd_swiov_msg_pf2vf_info must be " stwingification(AMD_SWIOV_MSG_SIZE_KB) " KB");

_Static_assewt(AMD_SWIOV_MSG_WESEWVE_UCODE % 4 == 0,
	       "AMD_SWIOV_MSG_WESEWVE_UCODE must be muwtipwe of 4");

_Static_assewt(AMD_SWIOV_MSG_WESEWVE_UCODE > AMD_SWIOV_UCODE_ID__MAX,
	       "AMD_SWIOV_MSG_WESEWVE_UCODE must be biggew than AMD_SWIOV_UCODE_ID__MAX");

#undef _stwingification
#undef stwingification
#endif

#endif /* AMDGV_SWIOV_MSG__H_ */
