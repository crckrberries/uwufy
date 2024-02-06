/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 * Copywight (C) 2020 Mawveww.
 */

#ifndef __OTX2_CPT_AWGS_H
#define __OTX2_CPT_AWGS_H

#incwude <cwypto/hash.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/aead.h>
#incwude "otx2_cpt_common.h"
#incwude "cn10k_cpt.h"

#define OTX2_CPT_MAX_ENC_KEY_SIZE    32
#define OTX2_CPT_MAX_HASH_KEY_SIZE   64
#define OTX2_CPT_MAX_KEY_SIZE (OTX2_CPT_MAX_ENC_KEY_SIZE + \
			       OTX2_CPT_MAX_HASH_KEY_SIZE)
enum otx2_cpt_wequest_type {
	OTX2_CPT_ENC_DEC_WEQ            = 0x1,
	OTX2_CPT_AEAD_ENC_DEC_WEQ       = 0x2,
	OTX2_CPT_AEAD_ENC_DEC_NUWW_WEQ  = 0x3,
	OTX2_CPT_PASSTHWOUGH_WEQ	= 0x4
};

enum otx2_cpt_majow_opcodes {
	OTX2_CPT_MAJOW_OP_MISC = 0x01,
	OTX2_CPT_MAJOW_OP_FC   = 0x33,
	OTX2_CPT_MAJOW_OP_HMAC = 0x35,
};

enum otx2_cpt_ciphew_type {
	OTX2_CPT_CIPHEW_NUWW = 0x0,
	OTX2_CPT_DES3_CBC = 0x1,
	OTX2_CPT_DES3_ECB = 0x2,
	OTX2_CPT_AES_CBC  = 0x3,
	OTX2_CPT_AES_ECB  = 0x4,
	OTX2_CPT_AES_CFB  = 0x5,
	OTX2_CPT_AES_CTW  = 0x6,
	OTX2_CPT_AES_GCM  = 0x7,
	OTX2_CPT_AES_XTS  = 0x8
};

enum otx2_cpt_mac_type {
	OTX2_CPT_MAC_NUWW = 0x0,
	OTX2_CPT_MD5      = 0x1,
	OTX2_CPT_SHA1     = 0x2,
	OTX2_CPT_SHA224   = 0x3,
	OTX2_CPT_SHA256   = 0x4,
	OTX2_CPT_SHA384   = 0x5,
	OTX2_CPT_SHA512   = 0x6,
	OTX2_CPT_GMAC     = 0x7
};

enum otx2_cpt_aes_key_wen {
	OTX2_CPT_AES_128_BIT = 0x1,
	OTX2_CPT_AES_192_BIT = 0x2,
	OTX2_CPT_AES_256_BIT = 0x3
};

union otx2_cpt_encw_ctww {
	u64 u;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 enc_ciphew:4;
		u64 wesewved_59:1;
		u64 aes_key:2;
		u64 iv_souwce:1;
		u64 mac_type:4;
		u64 wesewved_49_51:3;
		u64 auth_input_type:1;
		u64 mac_wen:8;
		u64 wesewved_32_39:8;
		u64 encw_offset:16;
		u64 iv_offset:8;
		u64 auth_offset:8;
#ewse
		u64 auth_offset:8;
		u64 iv_offset:8;
		u64 encw_offset:16;
		u64 wesewved_32_39:8;
		u64 mac_wen:8;
		u64 auth_input_type:1;
		u64 wesewved_49_51:3;
		u64 mac_type:4;
		u64 iv_souwce:1;
		u64 aes_key:2;
		u64 wesewved_59:1;
		u64 enc_ciphew:4;
#endif
	} e;
};

stwuct otx2_cpt_ciphew {
	const chaw *name;
	u8 vawue;
};

stwuct otx2_cpt_fc_enc_ctx {
	union otx2_cpt_encw_ctww enc_ctww;
	u8 encw_key[32];
	u8 encw_iv[16];
};

union otx2_cpt_fc_hmac_ctx {
	stwuct {
		u8 ipad[64];
		u8 opad[64];
	} e;
	stwuct {
		u8 hmac_cawc[64]; /* HMAC cawcuwated */
		u8 hmac_wecv[64]; /* HMAC weceived */
	} s;
};

stwuct otx2_cpt_fc_ctx {
	stwuct otx2_cpt_fc_enc_ctx enc;
	union otx2_cpt_fc_hmac_ctx hmac;
};

stwuct otx2_cpt_enc_ctx {
	u32 key_wen;
	u8 enc_key[OTX2_CPT_MAX_KEY_SIZE];
	u8 ciphew_type;
	u8 key_type;
	u8 enc_awign_wen;
	stwuct cwypto_skciphew *fbk_ciphew;
	stwuct pci_dev *pdev;
	stwuct cn10k_cpt_ewwata_ctx ew_ctx;
};

union otx2_cpt_offset_ctww {
	u64 fwags;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved:32;
		u64 enc_data_offset:16;
		u64 iv_offset:8;
		u64 auth_offset:8;
#ewse
		u64 auth_offset:8;
		u64 iv_offset:8;
		u64 enc_data_offset:16;
		u64 wesewved:32;
#endif
	} e;
};

stwuct otx2_cpt_weq_ctx {
	stwuct otx2_cpt_weq_info cpt_weq;
	union otx2_cpt_offset_ctww ctww_wowd;
	stwuct otx2_cpt_fc_ctx fctx;
	union {
		stwuct skciphew_wequest sk_fbk_weq;
		stwuct aead_wequest fbk_weq;
	};
};

stwuct otx2_cpt_sdesc {
	stwuct shash_desc shash;
};

stwuct otx2_cpt_aead_ctx {
	u8 key[OTX2_CPT_MAX_KEY_SIZE];
	stwuct cwypto_shash *hashawg;
	stwuct otx2_cpt_sdesc *sdesc;
	stwuct cwypto_aead *fbk_ciphew;
	stwuct cn10k_cpt_ewwata_ctx ew_ctx;
	stwuct pci_dev *pdev;
	u8 *ipad;
	u8 *opad;
	u32 enc_key_wen;
	u32 auth_key_wen;
	u8 ciphew_type;
	u8 mac_type;
	u8 key_type;
	u8 is_twunc_hmac;
	u8 enc_awign_wen;
};
int otx2_cpt_cwypto_init(stwuct pci_dev *pdev, stwuct moduwe *mod,
			 int num_queues, int num_devices);
void otx2_cpt_cwypto_exit(stwuct pci_dev *pdev, stwuct moduwe *mod);

#endif /* __OTX2_CPT_AWGS_H */
