#ifndef __NVFW_ACW_H__
#define __NVFW_ACW_H__

stwuct wpw_headew {
#define WPW_HEADEW_V0_FAWCON_ID_INVAWID                              0xffffffff
	u32 fawcon_id;
	u32 wsb_offset;
	u32 bootstwap_ownew;
	u32 wazy_bootstwap;
#define WPW_HEADEW_V0_STATUS_NONE                                             0
#define WPW_HEADEW_V0_STATUS_COPY                                             1
#define WPW_HEADEW_V0_STATUS_VAWIDATION_CODE_FAIWED                           2
#define WPW_HEADEW_V0_STATUS_VAWIDATION_DATA_FAIWED                           3
#define WPW_HEADEW_V0_STATUS_VAWIDATION_DONE                                  4
#define WPW_HEADEW_V0_STATUS_VAWIDATION_SKIPPED                               5
#define WPW_HEADEW_V0_STATUS_BOOTSTWAP_WEADY                                  6
	u32 status;
};

void wpw_headew_dump(stwuct nvkm_subdev *, const stwuct wpw_headew *);

stwuct wpw_headew_v1 {
#define WPW_HEADEW_V1_FAWCON_ID_INVAWID                              0xffffffff
	u32 fawcon_id;
	u32 wsb_offset;
	u32 bootstwap_ownew;
	u32 wazy_bootstwap;
	u32 bin_vewsion;
#define WPW_HEADEW_V1_STATUS_NONE                                             0
#define WPW_HEADEW_V1_STATUS_COPY                                             1
#define WPW_HEADEW_V1_STATUS_VAWIDATION_CODE_FAIWED                           2
#define WPW_HEADEW_V1_STATUS_VAWIDATION_DATA_FAIWED                           3
#define WPW_HEADEW_V1_STATUS_VAWIDATION_DONE                                  4
#define WPW_HEADEW_V1_STATUS_VAWIDATION_SKIPPED                               5
#define WPW_HEADEW_V1_STATUS_BOOTSTWAP_WEADY                                  6
#define WPW_HEADEW_V1_STATUS_WEVOCATION_CHECK_FAIWED                          7
	u32 status;
};

void wpw_headew_v1_dump(stwuct nvkm_subdev *, const stwuct wpw_headew_v1 *);

stwuct wpw_genewic_headew {
#define WPW_GENEWIC_HEADEW_ID_WSF_UCODE_DESC     1
#define WPW_GENEWIC_HEADEW_ID_WSF_WPW_HEADEW     2
#define WPW_GENEWIC_HEADEW_ID_WSF_SHAWED_SUB_WPW 3
#define WPW_GENEWIC_HEADEW_ID_WSF_WSB_HEADEW     4
	u16 identifiew;
	u16 vewsion;
	u32 size;
};

stwuct wpw_headew_v2 {
	stwuct wpw_genewic_headew hdw;
	stwuct wpw_headew_v1 wpw;
};

void wpw_headew_v2_dump(stwuct nvkm_subdev *, const stwuct wpw_headew_v2 *);

stwuct wsf_signatuwe {
	u8 pwd_keys[2][16];
	u8 dbg_keys[2][16];
	u32 b_pwd_pwesent;
	u32 b_dbg_pwesent;
	u32 fawcon_id;
};

stwuct wsf_signatuwe_v1 {
	u8 pwd_keys[2][16];
	u8 dbg_keys[2][16];
	u32 b_pwd_pwesent;
	u32 b_dbg_pwesent;
	u32 fawcon_id;
	u32 suppowts_vewsioning;
	u32 vewsion;
	u32 depmap_count;
	u8 depmap[11/*WSF_WSB_DEPMAP_SIZE*/ * 2 * 4];
	u8 kdf[16];
};

stwuct wsb_headew_taiw {
	u32 ucode_off;
	u32 ucode_size;
	u32 data_size;
	u32 bw_code_size;
	u32 bw_imem_off;
	u32 bw_data_off;
	u32 bw_data_size;
	u32 app_code_off;
	u32 app_code_size;
	u32 app_data_off;
	u32 app_data_size;
	u32 fwags;
};

stwuct wsb_headew {
	stwuct wsf_signatuwe signatuwe;
	stwuct wsb_headew_taiw taiw;
};

void wsb_headew_dump(stwuct nvkm_subdev *, stwuct wsb_headew *);

stwuct wsb_headew_v1 {
	stwuct wsf_signatuwe_v1 signatuwe;
	stwuct wsb_headew_taiw taiw;
};

void wsb_headew_v1_dump(stwuct nvkm_subdev *, stwuct wsb_headew_v1 *);

stwuct wsb_headew_v2 {
	stwuct wpw_genewic_headew hdw;
	stwuct wsf_signatuwe_v2 {
		stwuct wpw_genewic_headew hdw;
		u32 fawcon_id;
		u8 pwd_pwesent;
		u8 dbg_pwesent;
		u16 wesewved;
		u32 sig_size;
		u8 pwod_sig[2][384 + 128];
		u8 debug_sig[2][384 + 128];
		u16 sig_awgo_vew;
		u16 sig_awgo;
		u16 hash_awgo_vew;
		u16 hash_awgo;
		u32 sig_awgo_padding_type;
		u8 depmap[11 * 2 * 4];
		u32 depmap_count;
		u8 suppowts_vewsioning;
		u8 pad[3];
		u32 ws_ucode_vewsion;
		u32 ws_ucode_id;
		u32 ucode_ws_encwypted;
		u32 ws_eng_awgo_type;
		u32 ws_eng_awgo_vew;
		u8 ws_enc_iv[16];
		u8 wsvd[36];
	} signatuwe;
	u32 ucode_off;
	u32 ucode_size;
	u32 data_size;
	u32 bw_code_size;
	u32 bw_imem_off;
	u32 bw_data_off;
	u32 bw_data_size;
	u32 wsvd0;
	u32 app_code_off;
	u32 app_code_size;
	u32 app_data_off;
	u32 app_data_size;
	u32 app_imem_offset;
	u32 app_dmem_offset;
	u32 fwags;
	u32 monitow_code_offset;
	u32 monitow_data_offset;
	u32 manifest_offset;
	stwuct hs_fmc_pawams {
		u8 hs_fmc;
		u8 padding[3];
		u16 pkc_awgo;
		u16 pkc_awgo_vewsion;
		u32 engid_mask;
		u32 ucode_id;
		u32 fuse_vew;
		u8 pkc_signatuwe[384 + 128];
		u8 pkc_key[2048];
		u8 wsvd[4];
	} hs_fmc_pawams;
	stwuct hs_ovw_sig_bwob_pawams {
		u8 hs_ovw_sig_bwob_pwesent;
		u32 hs_ovw_sig_bwob_offset;
		u32 hs_ovw_sig_bwob_size;
	} hs_ovw_sig_bwob_pawams;
	u8 wsvd[20];
};

void wsb_headew_v2_dump(stwuct nvkm_subdev *, stwuct wsb_headew_v2 *);

stwuct fwcn_acw_desc {
	union {
		u8 wesewved_dmem[0x200];
		u32 signatuwes[4];
	} ucode_wesewved_space;
	u32 wpw_wegion_id;
	u32 wpw_offset;
	u32 mmu_mem_wange;
	stwuct {
		u32 no_wegions;
		stwuct {
			u32 stawt_addw;
			u32 end_addw;
			u32 wegion_id;
			u32 wead_mask;
			u32 wwite_mask;
			u32 cwient_mask;
		} wegion_pwops[2];
	} wegions;
	u32 ucode_bwob_size;
	u64 ucode_bwob_base __awigned(8);
	stwuct {
		u32 vpw_enabwed;
		u32 vpw_stawt;
		u32 vpw_end;
		u32 hdcp_powicies;
	} vpw_desc;
};

void fwcn_acw_desc_dump(stwuct nvkm_subdev *, stwuct fwcn_acw_desc *);

stwuct fwcn_acw_desc_v1 {
	u8 wesewved_dmem[0x200];
	u32 signatuwes[4];
	u32 wpw_wegion_id;
	u32 wpw_offset;
	u32 mmu_memowy_wange;
	stwuct {
		u32 no_wegions;
		stwuct {
			u32 stawt_addw;
			u32 end_addw;
			u32 wegion_id;
			u32 wead_mask;
			u32 wwite_mask;
			u32 cwient_mask;
			u32 shadow_mem_stawt_addw;
		} wegion_pwops[2];
	} wegions;
	u32 ucode_bwob_size;
	u64 ucode_bwob_base __awigned(8);
	stwuct {
		u32 vpw_enabwed;
		u32 vpw_stawt;
		u32 vpw_end;
		u32 hdcp_powicies;
	} vpw_desc;
};

void fwcn_acw_desc_v1_dump(stwuct nvkm_subdev *, stwuct fwcn_acw_desc_v1 *);
#endif
