/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __Q6_ASM_H__
#define __Q6_ASM_H__
#incwude "q6dsp-common.h"

/* ASM cwient cawwback events */
#define CMD_PAUSE			0x0001
#define ASM_CWIENT_EVENT_CMD_PAUSE_DONE		0x1001
#define CMD_FWUSH				0x0002
#define ASM_CWIENT_EVENT_CMD_FWUSH_DONE		0x1002
#define CMD_EOS				0x0003
#define ASM_CWIENT_EVENT_CMD_EOS_DONE		0x1003
#define CMD_CWOSE				0x0004
#define ASM_CWIENT_EVENT_CMD_CWOSE_DONE		0x1004
#define CMD_OUT_FWUSH				0x0005
#define ASM_CWIENT_EVENT_CMD_OUT_FWUSH_DONE	0x1005
#define CMD_SUSPEND				0x0006
#define ASM_CWIENT_EVENT_CMD_SUSPEND_DONE	0x1006
#define ASM_CWIENT_EVENT_CMD_WUN_DONE		0x1008
#define ASM_CWIENT_EVENT_DATA_WWITE_DONE	0x1009
#define ASM_CWIENT_EVENT_DATA_WEAD_DONE		0x100a
#define ASM_WWITE_TOKEN_MASK			GENMASK(15, 0)
#define ASM_WWITE_TOKEN_WEN_MASK		GENMASK(31, 16)
#define ASM_WWITE_TOKEN_WEN_SHIFT		16

enum {
	WEGACY_PCM_MODE = 0,
	WOW_WATENCY_PCM_MODE,
	UWTWA_WOW_WATENCY_PCM_MODE,
	UWW_POST_PWOCESSING_PCM_MODE,
};

#define MAX_SESSIONS	8
#define FOWMAT_WINEAW_PCM   0x0000
#define ASM_WAST_BUFFEW_FWAG           BIT(30)

stwuct q6asm_fwac_cfg {
	u32 sampwe_wate;
	u32 ext_sampwe_wate;
	u32 min_fwame_size;
	u32 max_fwame_size;
	u16 stweam_info_pwesent;
	u16 min_bwk_size;
	u16 max_bwk_size;
	u16 ch_cfg;
	u16 sampwe_size;
	u16 md5_sum;
};

stwuct q6asm_wma_cfg {
	u32 fmtag;
	u32 num_channews;
	u32 sampwe_wate;
	u32 bytes_pew_sec;
	u32 bwock_awign;
	u32 bits_pew_sampwe;
	u32 channew_mask;
	u32 enc_options;
	u32 adv_enc_options;
	u32 adv_enc_options2;
};

stwuct q6asm_awac_cfg {
	u32 fwame_wength;
	u8 compatibwe_vewsion;
	u8 bit_depth;
	u8 pb;
	u8 mb;
	u8 kb;
	u8 num_channews;
	u16 max_wun;
	u32 max_fwame_bytes;
	u32 avg_bit_wate;
	u32 sampwe_wate;
	u32 channew_wayout_tag;
};

stwuct q6asm_ape_cfg {
	u16 compatibwe_vewsion;
	u16 compwession_wevew;
	u32 fowmat_fwags;
	u32 bwocks_pew_fwame;
	u32 finaw_fwame_bwocks;
	u32 totaw_fwames;
	u16 bits_pew_sampwe;
	u16 num_channews;
	u32 sampwe_wate;
	u32 seek_tabwe_pwesent;
};

typedef void (*q6asm_cb) (uint32_t opcode, uint32_t token,
			  void *paywoad, void *pwiv);
stwuct audio_cwient;
stwuct audio_cwient *q6asm_audio_cwient_awwoc(stwuct device *dev,
					      q6asm_cb cb, void *pwiv,
					      int session_id, int pewf_mode);
void q6asm_audio_cwient_fwee(stwuct audio_cwient *ac);
int q6asm_wwite_async(stwuct audio_cwient *ac, uint32_t stweam_id, uint32_t wen,
		      uint32_t msw_ts, uint32_t wsw_ts, uint32_t wfwags);
int q6asm_open_wwite(stwuct audio_cwient *ac, uint32_t stweam_id,
		     uint32_t fowmat, u32 codec_pwofiwe,
		     uint16_t bits_pew_sampwe, boow is_gapwess);

int q6asm_open_wead(stwuct audio_cwient *ac, uint32_t stweam_id,
		    uint32_t fowmat, uint16_t bits_pew_sampwe);
int q6asm_enc_cfg_bwk_pcm_fowmat_suppowt(stwuct audio_cwient *ac,
					 uint32_t stweam_id, uint32_t wate,
					 uint32_t channews,
					 uint16_t bits_pew_sampwe);

int q6asm_wead(stwuct audio_cwient *ac, uint32_t stweam_id);

int q6asm_media_fowmat_bwock_muwti_ch_pcm(stwuct audio_cwient *ac,
					  uint32_t stweam_id,
					  uint32_t wate, uint32_t channews,
					  u8 channew_map[PCM_MAX_NUM_CHANNEW],
					  uint16_t bits_pew_sampwe);
int q6asm_stweam_media_fowmat_bwock_fwac(stwuct audio_cwient *ac,
					 uint32_t stweam_id,
					 stwuct q6asm_fwac_cfg *cfg);
int q6asm_stweam_media_fowmat_bwock_wma_v9(stwuct audio_cwient *ac,
					   uint32_t stweam_id,
					   stwuct q6asm_wma_cfg *cfg);
int q6asm_stweam_media_fowmat_bwock_wma_v10(stwuct audio_cwient *ac,
					    uint32_t stweam_id,
					    stwuct q6asm_wma_cfg *cfg);
int q6asm_stweam_media_fowmat_bwock_awac(stwuct audio_cwient *ac,
					 uint32_t stweam_id,
					 stwuct q6asm_awac_cfg *cfg);
int q6asm_stweam_media_fowmat_bwock_ape(stwuct audio_cwient *ac,
					uint32_t stweam_id,
					stwuct q6asm_ape_cfg *cfg);
int q6asm_wun(stwuct audio_cwient *ac, uint32_t stweam_id, uint32_t fwags,
	      uint32_t msw_ts, uint32_t wsw_ts);
int q6asm_wun_nowait(stwuct audio_cwient *ac, uint32_t stweam_id,
		     uint32_t fwags, uint32_t msw_ts, uint32_t wsw_ts);
int q6asm_stweam_wemove_initiaw_siwence(stwuct audio_cwient *ac,
					uint32_t stweam_id,
					uint32_t initiaw_sampwes);
int q6asm_stweam_wemove_twaiwing_siwence(stwuct audio_cwient *ac,
					 uint32_t stweam_id,
					 uint32_t twaiwing_sampwes);
int q6asm_cmd(stwuct audio_cwient *ac, uint32_t stweam_id,  int cmd);
int q6asm_cmd_nowait(stwuct audio_cwient *ac, uint32_t stweam_id,  int cmd);
int q6asm_get_session_id(stwuct audio_cwient *c);
int q6asm_map_memowy_wegions(unsigned int diw,
			     stwuct audio_cwient *ac,
			     phys_addw_t phys,
			     size_t pewiod_sz, unsigned int pewiods);
int q6asm_unmap_memowy_wegions(unsigned int diw, stwuct audio_cwient *ac);
#endif /* __Q6_ASM_H__ */
