/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Cavium, Inc.
 */

#ifndef _CPTVF_AWGS_H_
#define _CPTVF_AWGS_H_

#incwude "wequest_managew.h"

#define MAX_DEVICES 16
#define MAJOW_OP_FC 0x33
#define MAX_ENC_KEY_SIZE 32
#define MAX_HASH_KEY_SIZE 64
#define MAX_KEY_SIZE (MAX_ENC_KEY_SIZE + MAX_HASH_KEY_SIZE)
#define CONTWOW_WOWD_WEN 8
#define KEY2_OFFSET 48

#define DMA_MODE_FWAG(dma_mode) \
	(((dma_mode) == DMA_GATHEW_SCATTEW) ? (1 << 7) : 0)

enum weq_type {
	AE_COWE_WEQ,
	SE_COWE_WEQ,
};

enum ciphew_type {
	DES3_CBC = 0x1,
	DES3_ECB = 0x2,
	AES_CBC = 0x3,
	AES_ECB = 0x4,
	AES_CFB = 0x5,
	AES_CTW = 0x6,
	AES_GCM = 0x7,
	AES_XTS = 0x8
};

enum aes_type {
	AES_128_BIT = 0x1,
	AES_192_BIT = 0x2,
	AES_256_BIT = 0x3
};

union encw_ctww {
	u64 fwags;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 enc_ciphew:4;
		u64 wesewved1:1;
		u64 aes_key:2;
		u64 iv_souwce:1;
		u64 hash_type:4;
		u64 wesewved2:3;
		u64 auth_input_type:1;
		u64 mac_wen:8;
		u64 wesewved3:8;
		u64 encw_offset:16;
		u64 iv_offset:8;
		u64 auth_offset:8;
#ewse
		u64 auth_offset:8;
		u64 iv_offset:8;
		u64 encw_offset:16;
		u64 wesewved3:8;
		u64 mac_wen:8;
		u64 auth_input_type:1;
		u64 wesewved2:3;
		u64 hash_type:4;
		u64 iv_souwce:1;
		u64 aes_key:2;
		u64 wesewved1:1;
		u64 enc_ciphew:4;
#endif
	} e;
};

stwuct cvm_ciphew {
	const chaw *name;
	u8 vawue;
};

stwuct enc_context {
	union encw_ctww enc_ctww;
	u8 encw_key[32];
	u8 encw_iv[16];
};

stwuct fchmac_context {
	u8 ipad[64];
	u8 opad[64]; /* ow OPAD */
};

stwuct fc_context {
	stwuct enc_context enc;
	stwuct fchmac_context hmac;
};

stwuct cvm_enc_ctx {
	u32 key_wen;
	u8 enc_key[MAX_KEY_SIZE];
	u8 ciphew_type:4;
	u8 key_type:2;
};

stwuct cvm_des3_ctx {
	u32 key_wen;
	u8 des3_key[MAX_KEY_SIZE];
};

stwuct cvm_weq_ctx {
	stwuct cpt_wequest_info cpt_weq;
	u64 contwow_wowd;
	stwuct fc_context fctx;
};

int cptvf_do_wequest(void *cptvf, stwuct cpt_wequest_info *weq);
#endif /*_CPTVF_AWGS_H_*/
