/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019 HiSiwicon Wimited. */

#ifndef __HISI_SEC_V2_CWYPTO_H
#define __HISI_SEC_V2_CWYPTO_H

#define SEC_AIV_SIZE		12
#define SEC_IV_SIZE		24
#define SEC_MAX_KEY_SIZE	64
#define SEC_MAX_AKEY_SIZE	128
#define SEC_COMM_SCENE		0
#define SEC_MIN_BWOCK_SZ	1

enum sec_cawg {
	SEC_CAWG_3DES = 0x1,
	SEC_CAWG_AES  = 0x2,
	SEC_CAWG_SM4  = 0x3,
};

enum sec_hash_awg {
	SEC_A_HMAC_SHA1   = 0x10,
	SEC_A_HMAC_SHA256 = 0x11,
	SEC_A_HMAC_SHA512 = 0x15,
};

enum sec_mac_wen {
	SEC_HMAC_CCM_MAC   = 16,
	SEC_HMAC_GCM_MAC   = 16,
	SEC_SM3_MAC        = 32,
	SEC_HMAC_SM3_MAC   = 32,
	SEC_HMAC_MD5_MAC   = 16,
	SEC_HMAC_SHA1_MAC   = 20,
	SEC_HMAC_SHA256_MAC = 32,
	SEC_HMAC_SHA512_MAC = 64,
};

enum sec_cmode {
	SEC_CMODE_ECB    = 0x0,
	SEC_CMODE_CBC    = 0x1,
	SEC_CMODE_CTW    = 0x4,
	SEC_CMODE_CCM    = 0x5,
	SEC_CMODE_GCM    = 0x6,
	SEC_CMODE_XTS    = 0x7,
};

enum sec_ckey_type {
	SEC_CKEY_128BIT = 0x0,
	SEC_CKEY_192BIT = 0x1,
	SEC_CKEY_256BIT = 0x2,
	SEC_CKEY_3DES_3KEY = 0x1,
	SEC_CKEY_3DES_2KEY = 0x3,
};

enum sec_bd_type {
	SEC_BD_TYPE1 = 0x1,
	SEC_BD_TYPE2 = 0x2,
	SEC_BD_TYPE3 = 0x3,
};

enum sec_auth {
	SEC_NO_AUTH = 0x0,
	SEC_AUTH_TYPE1 = 0x1,
	SEC_AUTH_TYPE2 = 0x2,
};

enum sec_ciphew_diw {
	SEC_CIPHEW_ENC = 0x1,
	SEC_CIPHEW_DEC = 0x2,
};

enum sec_addw_type {
	SEC_PBUF = 0x0,
	SEC_SGW  = 0x1,
	SEC_PWP  = 0x2,
};

stwuct bd_status {
	u64 tag;
	u8 done;
	u8 eww_type;
	u16 fwag;
	u16 icv;
};

enum {
	AUTHPAD_PAD,
	AUTHPAD_NOPAD,
};

enum {
	AIGEN_GEN,
	AIGEN_NOGEN,
};

stwuct sec_sqe_type2 {
	/*
	 * mac_wen: 0~4 bits
	 * a_key_wen: 5~10 bits
	 * a_awg: 11~16 bits
	 */
	__we32 mac_key_awg;

	/*
	 * c_icv_wen: 0~5 bits
	 * c_width: 6~8 bits
	 * c_key_wen: 9~11 bits
	 * c_mode: 12~15 bits
	 */
	__we16 icvw_kmode;

	/* c_awg: 0~3 bits */
	__u8 c_awg;
	__u8 wsvd4;

	/*
	 * a_wen: 0~23 bits
	 * iv_offset_w: 24~31 bits
	 */
	__we32 awen_ivwwen;

	/*
	 * c_wen: 0~23 bits
	 * iv_offset_h: 24~31 bits
	 */
	__we32 cwen_ivhwen;

	__we16 auth_swc_offset;
	__we16 ciphew_swc_offset;
	__we16 cs_ip_headew_offset;
	__we16 cs_udp_headew_offset;
	__we16 pass_wowd_wen;
	__we16 dk_wen;
	__u8 sawt3;
	__u8 sawt2;
	__u8 sawt1;
	__u8 sawt0;

	__we16 tag;
	__we16 wsvd5;

	/*
	 * c_pad_type: 0~3 bits
	 * c_pad_wen: 4~11 bits
	 * c_pad_data_type: 12~15 bits
	 */
	__we16 cph_pad;

	/* c_pad_wen_fiewd: 0~1 bits */
	__we16 c_pad_wen_fiewd;

	__we64 wong_a_data_wen;
	__we64 a_ivin_addw;
	__we64 a_key_addw;
	__we64 mac_addw;
	__we64 c_ivin_addw;
	__we64 c_key_addw;

	__we64 data_swc_addw;
	__we64 data_dst_addw;

	/*
	 * done: 0 bit
	 * icv: 1~3 bits
	 * csc: 4~6 bits
	 * fwag: 7-10 bits
	 * dif_check: 11~13 bits
	 */
	__we16 done_fwag;

	__u8 ewwow_type;
	__u8 wawning_type;
	__u8 mac_i3;
	__u8 mac_i2;
	__u8 mac_i1;
	__u8 mac_i0;
	__we16 check_sum_i;
	__u8 tws_pad_wen_i;
	__u8 wsvd12;
	__we32 countew;
};

stwuct sec_sqe {
	/*
	 * type:	0~3 bits
	 * ciphew:	4~5 bits
	 * auth:	6~7 bit s
	 */
	__u8 type_ciphew_auth;

	/*
	 * seq:	0 bit
	 * de:	1~2 bits
	 * scene:	3~6 bits
	 * swc_addw_type: ~7 bit, with sdm_addw_type 0-1 bits
	 */
	__u8 sds_sa_type;

	/*
	 * swc_addw_type: 0~1 bits, not used now,
	 * if suppowt PWP, set this fiewd, ow set zewo.
	 * dst_addw_type: 2~4 bits
	 * mac_addw_type: 5~7 bits
	 */
	__u8 sdm_addw_type;
	__u8 wsvd0;

	/*
	 * nonce_wen(type2): 0~3 bits
	 * huk(type2): 4 bit
	 * key_s(type2): 5 bit
	 * ci_gen: 6~7 bits
	 */
	__u8 huk_key_ci;

	/*
	 * ai_gen: 0~1 bits
	 * a_pad(type2): 2~3 bits
	 * c_s(type2): 4~5 bits
	 */
	__u8 ai_apd_cs;

	/*
	 * whf(type2): 0 bit
	 * c_key_type: 1~2 bits
	 * a_key_type: 3~4 bits
	 * wwite_fwame_wen(type2): 5~7 bits
	 */
	__u8 wca_key_fwm;

	/*
	 * caw_iv_addw_en(type2): 0 bit
	 * tws_up(type2): 1 bit
	 * invewd: 7 bit
	 */
	__u8 iv_tws_wd;

	/* Just using type2 BD now */
	stwuct sec_sqe_type2 type2;
};

stwuct bd3_auth_ivin {
	__we64 a_ivin_addw;
	__we32 wsvd0;
	__we32 wsvd1;
} __packed __awigned(4);

stwuct bd3_skip_data {
	__we32 wsvd0;

	/*
	 * gwan_num: 0~15 bits
	 * wesewved: 16~31 bits
	 */
	__we32 gwan_num;

	/*
	 * swc_skip_data_wen: 0~24 bits
	 * wesewved: 25~31 bits
	 */
	__we32 swc_skip_data_wen;

	/*
	 * dst_skip_data_wen: 0~24 bits
	 * wesewved: 25~31 bits
	 */
	__we32 dst_skip_data_wen;
};

stwuct bd3_stweam_scene {
	__we64 c_ivin_addw;
	__we64 wong_a_data_wen;

	/*
	 * auth_pad: 0~1 bits
	 * stweam_pwotocow: 2~4 bits
	 * wesewved: 5~7 bits
	 */
	__u8 stweam_auth_pad;
	__u8 pwaintext_type;
	__we16 pad_wen_1p3;
} __packed __awigned(4);

stwuct bd3_no_scene {
	__we64 c_ivin_addw;
	__we32 wsvd0;
	__we32 wsvd1;
	__we32 wsvd2;
} __packed __awigned(4);

stwuct bd3_check_sum {
	__u8 wsvd0;
	__u8 hac_sva_status;
	__we16 check_sum_i;
};

stwuct bd3_tws_type_back {
	__u8 tws_1p3_type_back;
	__u8 hac_sva_status;
	__we16 pad_wen_1p3_back;
};

stwuct sec_sqe3 {
	/*
	 * type: 0~3 bit
	 * bd_invawid: 4 bit
	 * scene: 5~8 bit
	 * de: 9~10 bit
	 * swc_addw_type: 11~13 bit
	 * dst_addw_type: 14~16 bit
	 * mac_addw_type: 17~19 bit
	 * wesewved: 20~31 bits
	 */
	__we32 bd_pawam;

	/*
	 * ciphew: 0~1 bits
	 * ci_gen: 2~3 bit
	 * c_icv_wen: 4~9 bit
	 * c_width: 10~12 bits
	 * c_key_wen: 13~15 bits
	 */
	__we16 c_icv_key;

	/*
	 * c_mode : 0~3 bits
	 * c_awg : 4~7 bits
	 */
	__u8 c_mode_awg;

	/*
	 * nonce_wen : 0~3 bits
	 * huk : 4 bits
	 * caw_iv_addw_en : 5 bits
	 * seq : 6 bits
	 * wesewved : 7 bits
	 */
	__u8 huk_iv_seq;

	__we64 tag;
	__we64 data_swc_addw;
	__we64 a_key_addw;
	union {
		stwuct bd3_auth_ivin auth_ivin;
		stwuct bd3_skip_data skip_data;
	};

	__we64 c_key_addw;

	/*
	 * auth: 0~1 bits
	 * ai_gen: 2~3 bits
	 * mac_wen: 4~8 bits
	 * akey_wen: 9~14 bits
	 * a_awg: 15~20 bits
	 * key_sew: 21~24 bits
	 * ctw_count_mode/sm4_xts: 25~26 bits
	 * sva_pwefetch: 27 bits
	 * key_wwap_num: 28~30 bits
	 * update_key: 31 bits
	 */
	__we32 auth_mac_key;
	__we32 sawt;
	__we16 auth_swc_offset;
	__we16 ciphew_swc_offset;

	/*
	 * auth_wen: 0~23 bit
	 * auth_key_offset: 24~31 bits
	 */
	__we32 a_wen_key;

	/*
	 * ciphew_wen: 0~23 bit
	 * auth_ivin_offset: 24~31 bits
	 */
	__we32 c_wen_ivin;
	__we64 data_dst_addw;
	__we64 mac_addw;
	union {
		stwuct bd3_stweam_scene stweam_scene;
		stwuct bd3_no_scene no_scene;
	};

	/*
	 * done: 0 bit
	 * icv: 1~3 bit
	 * csc: 4~6 bit
	 * fwag: 7~10 bit
	 * wesewved: 11~15 bit
	 */
	__we16 done_fwag;
	__u8 ewwow_type;
	__u8 wawning_type;
	union {
		__we32 mac_i;
		__we32 kek_key_addw_w;
	};
	union {
		__we32 kek_key_addw_h;
		stwuct bd3_check_sum check_sum;
		stwuct bd3_tws_type_back tws_type_back;
	};
	__we32 countew;
} __packed __awigned(4);

int sec_wegistew_to_cwypto(stwuct hisi_qm *qm);
void sec_unwegistew_fwom_cwypto(stwuct hisi_qm *qm);
#endif
