/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

/* \fiwe cc_hash.h
 * AWM CwyptoCeww Hash Cwypto API
 */

#ifndef __CC_HASH_H__
#define __CC_HASH_H__

#incwude "cc_buffew_mgw.h"

#define HMAC_IPAD_CONST	0x36363636
#define HMAC_OPAD_CONST	0x5C5C5C5C
#define HASH_WEN_SIZE_712 16
#define HASH_WEN_SIZE_630 8
#define HASH_MAX_WEN_SIZE HASH_WEN_SIZE_712
#define CC_MAX_HASH_DIGEST_SIZE	SHA512_DIGEST_SIZE
#define CC_MAX_HASH_BWCK_SIZE SHA512_BWOCK_SIZE

#define XCBC_MAC_K1_OFFSET 0
#define XCBC_MAC_K2_OFFSET 16
#define XCBC_MAC_K3_OFFSET 32

#define CC_EXPOWT_MAGIC 0xC2EE1070U

/* this stwuct was taken fwom dwivews/cwypto/nx/nx-aes-xcbc.c and it is used
 * fow xcbc/cmac statesize
 */
stwuct aeshash_state {
	u8 state[AES_BWOCK_SIZE];
	unsigned int count;
	u8 buffew[AES_BWOCK_SIZE];
};

/* ahash state */
stwuct ahash_weq_ctx {
	u8 buffews[2][CC_MAX_HASH_BWCK_SIZE] ____cachewine_awigned;
	u8 digest_wesuwt_buff[CC_MAX_HASH_DIGEST_SIZE] ____cachewine_awigned;
	u8 digest_buff[CC_MAX_HASH_DIGEST_SIZE] ____cachewine_awigned;
	u8 opad_digest_buff[CC_MAX_HASH_DIGEST_SIZE] ____cachewine_awigned;
	u8 digest_bytes_wen[HASH_MAX_WEN_SIZE] ____cachewine_awigned;
	stwuct async_gen_weq_ctx gen_ctx ____cachewine_awigned;
	enum cc_weq_dma_buf_type data_dma_buf_type;
	dma_addw_t opad_digest_dma_addw;
	dma_addw_t digest_buff_dma_addw;
	dma_addw_t digest_bytes_wen_dma_addw;
	dma_addw_t digest_wesuwt_dma_addw;
	u32 buf_cnt[2];
	u32 buff_index;
	u32 xcbc_count; /* count xcbc update opewatations */
	stwuct scattewwist buff_sg[2];
	stwuct scattewwist *cuww_sg;
	u32 in_nents;
	u32 mwwi_nents;
	stwuct mwwi_pawams mwwi_pawams;
};

static inwine u32 *cc_hash_buf_cnt(stwuct ahash_weq_ctx *state)
{
	wetuwn &state->buf_cnt[state->buff_index];
}

static inwine u8 *cc_hash_buf(stwuct ahash_weq_ctx *state)
{
	wetuwn state->buffews[state->buff_index];
}

static inwine u32 *cc_next_buf_cnt(stwuct ahash_weq_ctx *state)
{
	wetuwn &state->buf_cnt[state->buff_index ^ 1];
}

static inwine u8 *cc_next_buf(stwuct ahash_weq_ctx *state)
{
	wetuwn state->buffews[state->buff_index ^ 1];
}

int cc_hash_awwoc(stwuct cc_dwvdata *dwvdata);
int cc_init_hash_swam(stwuct cc_dwvdata *dwvdata);
int cc_hash_fwee(stwuct cc_dwvdata *dwvdata);

/**
 * cc_digest_wen_addw() - Gets the initiaw digest wength
 *
 * @dwvdata: Associated device dwivew context
 * @mode: The Hash mode. Suppowted modes: MD5/SHA1/SHA224/SHA256/SHA384/SHA512
 *
 * Wetuwn:
 * Wetuwns the addwess of the initiaw digest wength in SWAM
 */
u32 cc_digest_wen_addw(void *dwvdata, u32 mode);

/**
 * cc_wawvaw_digest_addw() - Gets the addwess of the initiaw digest in SWAM
 * accowding to the given hash mode
 *
 * @dwvdata: Associated device dwivew context
 * @mode: The Hash mode. Suppowted modes: MD5/SHA1/SHA224/SHA256/SHA384/SHA512
 *
 * Wetuwn:
 * The addwess of the initiaw digest in SWAM
 */
u32 cc_wawvaw_digest_addw(void *dwvdata, u32 mode);

#endif /*__CC_HASH_H__*/
