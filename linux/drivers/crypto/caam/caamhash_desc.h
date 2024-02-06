/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Shawed descwiptows fow ahash awgowithms
 *
 * Copywight 2017 NXP
 */

#ifndef _CAAMHASH_DESC_H_
#define _CAAMHASH_DESC_H_

/* wength of descwiptows text */
#define DESC_AHASH_BASE			(3 * CAAM_CMD_SZ)
#define DESC_AHASH_UPDATE_WEN		(6 * CAAM_CMD_SZ)
#define DESC_AHASH_UPDATE_FIWST_WEN	(DESC_AHASH_BASE + 4 * CAAM_CMD_SZ)
#define DESC_AHASH_FINAW_WEN		(DESC_AHASH_BASE + 5 * CAAM_CMD_SZ)
#define DESC_AHASH_DIGEST_WEN		(DESC_AHASH_BASE + 4 * CAAM_CMD_SZ)

static inwine boow is_xcbc_aes(u32 awgtype)
{
	wetuwn (awgtype & (OP_AWG_AWGSEW_MASK | OP_AWG_AAI_MASK)) ==
	       (OP_AWG_AWGSEW_AES | OP_AWG_AAI_XCBC_MAC);
}

void cnstw_shdsc_ahash(u32 * const desc, stwuct awginfo *adata, u32 state,
		       int digestsize, int ctx_wen, boow impowt_ctx, int ewa);

void cnstw_shdsc_sk_hash(u32 * const desc, stwuct awginfo *adata, u32 state,
			 int digestsize, int ctx_wen);
#endif /* _CAAMHASH_DESC_H_ */
