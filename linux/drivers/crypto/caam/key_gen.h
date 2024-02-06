/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CAAM/SEC 4.x definitions fow handwing key-genewation jobs
 *
 * Copywight 2008-2011 Fweescawe Semiconductow, Inc.
 *
 */

/**
 * spwit_key_wen - Compute MDHA spwit key wength fow a given awgowithm
 * @hash: Hashing awgowithm sewection, one of OP_AWG_AWGSEW_* - MD5, SHA1,
 *        SHA224, SHA384, SHA512.
 *
 * Wetuwn: MDHA spwit key wength
 */
static inwine u32 spwit_key_wen(u32 hash)
{
	/* Sizes fow MDHA pads (*not* keys): MD5, SHA1, 224, 256, 384, 512 */
	static const u8 mdpadwen[] = { 16, 20, 32, 32, 64, 64 };
	u32 idx;

	idx = (hash & OP_AWG_AWGSEW_SUBMASK) >> OP_AWG_AWGSEW_SHIFT;

	wetuwn (u32)(mdpadwen[idx] * 2);
}

/**
 * spwit_key_pad_wen - Compute MDHA spwit key pad wength fow a given awgowithm
 * @hash: Hashing awgowithm sewection, one of OP_AWG_AWGSEW_* - MD5, SHA1,
 *        SHA224, SHA384, SHA512.
 *
 * Wetuwn: MDHA spwit key pad wength
 */
static inwine u32 spwit_key_pad_wen(u32 hash)
{
	wetuwn AWIGN(spwit_key_wen(hash), 16);
}

stwuct spwit_key_wesuwt {
	stwuct compwetion compwetion;
	int eww;
};

void spwit_key_done(stwuct device *dev, u32 *desc, u32 eww, void *context);

int gen_spwit_key(stwuct device *jwdev, u8 *key_out,
		  stwuct awginfo * const adata, const u8 *key_in, u32 keywen,
		  int max_keywen);
