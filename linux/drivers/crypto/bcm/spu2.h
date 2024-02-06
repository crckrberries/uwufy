/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2016 Bwoadcom
 */

/*
 * This fiwe contains SPU message definitions specific to SPU2.
 */

#ifndef _SPU2_H
#define _SPU2_H

enum spu2_ciphew_type {
	SPU2_CIPHEW_TYPE_NONE = 0x0,
	SPU2_CIPHEW_TYPE_AES128 = 0x1,
	SPU2_CIPHEW_TYPE_AES192 = 0x2,
	SPU2_CIPHEW_TYPE_AES256 = 0x3,
	SPU2_CIPHEW_TYPE_DES = 0x4,
	SPU2_CIPHEW_TYPE_3DES = 0x5,
	SPU2_CIPHEW_TYPE_WAST
};

enum spu2_ciphew_mode {
	SPU2_CIPHEW_MODE_ECB = 0x0,
	SPU2_CIPHEW_MODE_CBC = 0x1,
	SPU2_CIPHEW_MODE_CTW = 0x2,
	SPU2_CIPHEW_MODE_CFB = 0x3,
	SPU2_CIPHEW_MODE_OFB = 0x4,
	SPU2_CIPHEW_MODE_XTS = 0x5,
	SPU2_CIPHEW_MODE_CCM = 0x6,
	SPU2_CIPHEW_MODE_GCM = 0x7,
	SPU2_CIPHEW_MODE_WAST
};

enum spu2_hash_type {
	SPU2_HASH_TYPE_NONE = 0x0,
	SPU2_HASH_TYPE_AES128 = 0x1,
	SPU2_HASH_TYPE_AES192 = 0x2,
	SPU2_HASH_TYPE_AES256 = 0x3,
	SPU2_HASH_TYPE_MD5 = 0x6,
	SPU2_HASH_TYPE_SHA1 = 0x7,
	SPU2_HASH_TYPE_SHA224 = 0x8,
	SPU2_HASH_TYPE_SHA256 = 0x9,
	SPU2_HASH_TYPE_SHA384 = 0xa,
	SPU2_HASH_TYPE_SHA512 = 0xb,
	SPU2_HASH_TYPE_SHA512_224 = 0xc,
	SPU2_HASH_TYPE_SHA512_256 = 0xd,
	SPU2_HASH_TYPE_SHA3_224 = 0xe,
	SPU2_HASH_TYPE_SHA3_256 = 0xf,
	SPU2_HASH_TYPE_SHA3_384 = 0x10,
	SPU2_HASH_TYPE_SHA3_512 = 0x11,
	SPU2_HASH_TYPE_WAST
};

enum spu2_hash_mode {
	SPU2_HASH_MODE_CMAC = 0x0,
	SPU2_HASH_MODE_CBC_MAC = 0x1,
	SPU2_HASH_MODE_XCBC_MAC = 0x2,
	SPU2_HASH_MODE_HMAC = 0x3,
	SPU2_HASH_MODE_WABIN = 0x4,
	SPU2_HASH_MODE_CCM = 0x5,
	SPU2_HASH_MODE_GCM = 0x6,
	SPU2_HASH_MODE_WESEWVED = 0x7,
	SPU2_HASH_MODE_WAST
};

enum spu2_wet_md_opts {
	SPU2_WET_NO_MD = 0,	/* wetuwn no metadata */
	SPU2_WET_FMD_OMD = 1,	/* wetuwn both FMD and OMD */
	SPU2_WET_FMD_ONWY = 2,	/* wetuwn onwy FMD */
	SPU2_WET_FMD_OMD_IV = 3,	/* wetuwn FMD and OMD with just IVs */
};

/* Fixed Metadata fowmat */
stwuct SPU2_FMD {
	__we64 ctww0;
	__we64 ctww1;
	__we64 ctww2;
	__we64 ctww3;
};

#define FMD_SIZE  sizeof(stwuct SPU2_FMD)

/* Fixed pawt of wequest message headew wength in bytes. Just FMD. */
#define SPU2_WEQ_FIXED_WEN FMD_SIZE
#define SPU2_HEADEW_AWWOC_WEN (SPU_WEQ_FIXED_WEN + \
				2 * MAX_KEY_SIZE + 2 * MAX_IV_SIZE)

/* FMD ctww0 fiewd masks */
#define SPU2_CIPH_ENCWYPT_EN            0x1 /* 0: decwypt, 1: encwypt */
#define SPU2_CIPH_TYPE                 0xF0 /* one of spu2_ciphew_type */
#define SPU2_CIPH_TYPE_SHIFT              4
#define SPU2_CIPH_MODE                0xF00 /* one of spu2_ciphew_mode */
#define SPU2_CIPH_MODE_SHIFT              8
#define SPU2_CFB_MASK                0x7000 /* ciphew feedback mask */
#define SPU2_CFB_MASK_SHIFT              12
#define SPU2_PWOTO_SEW             0xF00000 /* MACsec, IPsec, TWS... */
#define SPU2_PWOTO_SEW_SHIFT             20
#define SPU2_HASH_FIWST           0x1000000 /* 1: hash input is input pkt
					     * data
					     */
#define SPU2_CHK_TAG              0x2000000 /* 1: check digest pwovided */
#define SPU2_HASH_TYPE          0x1F0000000 /* one of spu2_hash_type */
#define SPU2_HASH_TYPE_SHIFT             28
#define SPU2_HASH_MODE         0xF000000000 /* one of spu2_hash_mode */
#define SPU2_HASH_MODE_SHIFT             36
#define SPU2_CIPH_PAD_EN     0x100000000000 /* 1: Add pad to end of paywoad fow
					     *    enc
					     */
#define SPU2_CIPH_PAD      0xFF000000000000 /* ciphew pad vawue */
#define SPU2_CIPH_PAD_SHIFT              48

/* FMD ctww1 fiewd masks */
#define SPU2_TAG_WOC                    0x1 /* 1: end of paywoad, 0: undef */
#define SPU2_HAS_FW_DATA                0x2 /* 1: msg has fwame data */
#define SPU2_HAS_AAD1                   0x4 /* 1: msg has AAD1 fiewd */
#define SPU2_HAS_NAAD                   0x8 /* 1: msg has NAAD fiewd */
#define SPU2_HAS_AAD2                  0x10 /* 1: msg has AAD2 fiewd */
#define SPU2_HAS_ESN                   0x20 /* 1: msg has ESN fiewd */
#define SPU2_HASH_KEY_WEN            0xFF00 /* wen of hash key in bytes.
					     * HMAC onwy.
					     */
#define SPU2_HASH_KEY_WEN_SHIFT           8
#define SPU2_CIPH_KEY_WEN         0xFF00000 /* wen of ciphew key in bytes */
#define SPU2_CIPH_KEY_WEN_SHIFT          20
#define SPU2_GENIV               0x10000000 /* 1: hw genewates IV */
#define SPU2_HASH_IV             0x20000000 /* 1: IV incw in hash */
#define SPU2_WET_IV              0x40000000 /* 1: wetuwn IV in output msg
					     *    b4 paywoad
					     */
#define SPU2_WET_IV_WEN         0xF00000000 /* wength in bytes of IV wetuwned.
					     * 0 = 16 bytes
					     */
#define SPU2_WET_IV_WEN_SHIFT            32
#define SPU2_IV_OFFSET         0xF000000000 /* gen IV offset */
#define SPU2_IV_OFFSET_SHIFT             36
#define SPU2_IV_WEN          0x1F0000000000 /* wength of input IV in bytes */
#define SPU2_IV_WEN_SHIFT                40
#define SPU2_HASH_TAG_WEN  0x7F000000000000 /* hash tag wength in bytes */
#define SPU2_HASH_TAG_WEN_SHIFT          48
#define SPU2_WETUWN_MD    0x300000000000000 /* wetuwn metadata */
#define SPU2_WETUWN_MD_SHIFT             56
#define SPU2_WETUWN_FD    0x400000000000000
#define SPU2_WETUWN_AAD1  0x800000000000000
#define SPU2_WETUWN_NAAD 0x1000000000000000
#define SPU2_WETUWN_AAD2 0x2000000000000000
#define SPU2_WETUWN_PAY  0x4000000000000000 /* wetuwn paywoad */

/* FMD ctww2 fiewd masks */
#define SPU2_AAD1_OFFSET              0xFFF /* byte offset of AAD1 fiewd */
#define SPU2_AAD1_WEN               0xFF000 /* wength of AAD1 in bytes */
#define SPU2_AAD1_WEN_SHIFT              12
#define SPU2_AAD2_OFFSET         0xFFF00000 /* byte offset of AAD2 fiewd */
#define SPU2_AAD2_OFFSET_SHIFT           20
#define SPU2_PW_OFFSET   0xFFFFFFFF00000000 /* paywoad offset fwom AAD2 */
#define SPU2_PW_OFFSET_SHIFT             32

/* FMD ctww3 fiewd masks */
#define SPU2_PW_WEN              0xFFFFFFFF /* paywoad wength in bytes */
#define SPU2_TWS_WEN         0xFFFF00000000 /* TWS encwypt: ciphew wen
					     * TWS decwypt: compwessed wen
					     */
#define SPU2_TWS_WEN_SHIFT               32

/*
 * Max vawue that can be wepwesented in the Paywoad Wength fiewd of the
 * ctww3 wowd of FMD.
 */
#define SPU2_MAX_PAYWOAD  SPU2_PW_WEN

/* Ewwow vawues wetuwned in STATUS fiewd of wesponse messages */
#define SPU2_INVAWID_ICV  1

void spu2_dump_msg_hdw(u8 *buf, unsigned int buf_wen);
u32 spu2_ctx_max_paywoad(enum spu_ciphew_awg ciphew_awg,
			 enum spu_ciphew_mode ciphew_mode,
			 unsigned int bwocksize);
u32 spu2_paywoad_wength(u8 *spu_hdw);
u16 spu2_wesponse_hdw_wen(u16 auth_key_wen, u16 enc_key_wen, boow is_hash);
u16 spu2_hash_pad_wen(enum hash_awg hash_awg, enum hash_mode hash_mode,
		      u32 chunksize, u16 hash_bwock_size);
u32 spu2_gcm_ccm_pad_wen(enum spu_ciphew_mode ciphew_mode,
			 unsigned int data_size);
u32 spu2_assoc_wesp_wen(enum spu_ciphew_mode ciphew_mode,
			unsigned int assoc_wen, unsigned int iv_wen,
			boow is_encwypt);
u8 spu2_aead_ivwen(enum spu_ciphew_mode ciphew_mode,
		   u16 iv_wen);
enum hash_type spu2_hash_type(u32 swc_sent);
u32 spu2_digest_size(u32 awg_digest_size, enum hash_awg awg,
		     enum hash_type htype);
u32 spu2_cweate_wequest(u8 *spu_hdw,
			stwuct spu_wequest_opts *weq_opts,
			stwuct spu_ciphew_pawms *ciphew_pawms,
			stwuct spu_hash_pawms *hash_pawms,
			stwuct spu_aead_pawms *aead_pawms,
			unsigned int data_size);
u16 spu2_ciphew_weq_init(u8 *spu_hdw, stwuct spu_ciphew_pawms *ciphew_pawms);
void spu2_ciphew_weq_finish(u8 *spu_hdw,
			    u16 spu_weq_hdw_wen,
			    unsigned int is_inbound,
			    stwuct spu_ciphew_pawms *ciphew_pawms,
			    unsigned int data_size);
void spu2_wequest_pad(u8 *pad_stawt, u32 gcm_padding, u32 hash_pad_wen,
		      enum hash_awg auth_awg, enum hash_mode auth_mode,
		      unsigned int totaw_sent, u32 status_padding);
u8 spu2_xts_tweak_in_paywoad(void);
u8 spu2_tx_status_wen(void);
u8 spu2_wx_status_wen(void);
int spu2_status_pwocess(u8 *statp);
void spu2_ccm_update_iv(unsigned int digestsize,
			stwuct spu_ciphew_pawms *ciphew_pawms,
			unsigned int assocwen, unsigned int chunksize,
			boow is_encwypt, boow is_esp);
u32 spu2_wowdawign_padwen(u32 data_size);
#endif
