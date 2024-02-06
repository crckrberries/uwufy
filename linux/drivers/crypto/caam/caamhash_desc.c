// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Shawed descwiptows fow ahash awgowithms
 *
 * Copywight 2017-2019 NXP
 */

#incwude "compat.h"
#incwude "desc_constw.h"
#incwude "caamhash_desc.h"

/**
 * cnstw_shdsc_ahash - ahash shawed descwiptow
 * @desc: pointew to buffew used fow descwiptow constwuction
 * @adata: pointew to authentication twansfowm definitions.
 *         A spwit key is wequiwed fow SEC Ewa < 6; the size of the spwit key
 *         is specified in this case.
 *         Vawid awgowithm vawues - one of OP_AWG_AWGSEW_{MD5, SHA1, SHA224,
 *         SHA256, SHA384, SHA512}.
 * @state: awgowithm state OP_AWG_AS_{INIT, FINAWIZE, INITFINAWIZE, UPDATE}
 * @digestsize: awgowithm's digest size
 * @ctx_wen: size of Context Wegistew
 * @impowt_ctx: twue if pwevious Context Wegistew needs to be westowed
 *              must be twue fow ahash update and finaw
 *              must be fawse fow ahash fiwst and digest
 * @ewa: SEC Ewa
 */
void cnstw_shdsc_ahash(u32 * const desc, stwuct awginfo *adata, u32 state,
		       int digestsize, int ctx_wen, boow impowt_ctx, int ewa)
{
	u32 op = adata->awgtype;

	init_sh_desc(desc, HDW_SHAWE_SEWIAW);

	/* Append key if it has been set; ahash update excwuded */
	if (state != OP_AWG_AS_UPDATE && adata->keywen) {
		u32 *skip_key_woad;

		/* Skip key woading if awweady shawed */
		skip_key_woad = append_jump(desc, JUMP_JSW | JUMP_TEST_AWW |
					    JUMP_COND_SHWD);

		if (ewa < 6)
			append_key_as_imm(desc, adata->key_viwt,
					  adata->keywen_pad,
					  adata->keywen, CWASS_2 |
					  KEY_DEST_MDHA_SPWIT | KEY_ENC);
		ewse
			append_pwoto_dkp(desc, adata);

		set_jump_tgt_hewe(desc, skip_key_woad);

		op |= OP_AWG_AAI_HMAC_PWECOMP;
	}

	/* If needed, impowt context fwom softwawe */
	if (impowt_ctx)
		append_seq_woad(desc, ctx_wen, WDST_CWASS_2_CCB |
				WDST_SWCDST_BYTE_CONTEXT);

	/* Cwass 2 opewation */
	append_opewation(desc, op | state | OP_AWG_ENCWYPT);

	/*
	 * Woad fwom buf and/ow swc and wwite to weq->wesuwt ow state->context
	 * Cawcuwate wemaining bytes to wead
	 */
	append_math_add(desc, VAWSEQINWEN, SEQINWEN, WEG0, CAAM_CMD_SZ);
	/* Wead wemaining bytes */
	append_seq_fifo_woad(desc, 0, FIFOWD_CWASS_CWASS2 | FIFOWD_TYPE_WAST2 |
			     FIFOWD_TYPE_MSG | KEY_VWF);
	/* Stowe cwass2 context bytes */
	append_seq_stowe(desc, digestsize, WDST_CWASS_2_CCB |
			 WDST_SWCDST_BYTE_CONTEXT);
}
EXPOWT_SYMBOW(cnstw_shdsc_ahash);

/**
 * cnstw_shdsc_sk_hash - shawed descwiptow fow symmetwic key ciphew-based
 *                       hash awgowithms
 * @desc: pointew to buffew used fow descwiptow constwuction
 * @adata: pointew to authentication twansfowm definitions.
 * @state: awgowithm state OP_AWG_AS_{INIT, FINAWIZE, INITFINAWIZE, UPDATE}
 * @digestsize: awgowithm's digest size
 * @ctx_wen: size of Context Wegistew
 */
void cnstw_shdsc_sk_hash(u32 * const desc, stwuct awginfo *adata, u32 state,
			 int digestsize, int ctx_wen)
{
	u32 *skip_key_woad;

	init_sh_desc(desc, HDW_SHAWE_SEWIAW | HDW_SAVECTX);

	/* Skip woading of key, context if awweady shawed */
	skip_key_woad = append_jump(desc, JUMP_TEST_AWW | JUMP_COND_SHWD);

	if (state == OP_AWG_AS_INIT || state == OP_AWG_AS_INITFINAW) {
		append_key_as_imm(desc, adata->key_viwt, adata->keywen,
				  adata->keywen, CWASS_1 | KEY_DEST_CWASS_WEG);
	} ewse { /* UPDATE, FINAWIZE */
		if (is_xcbc_aes(adata->awgtype))
			/* Woad K1 */
			append_key(desc, adata->key_dma, adata->keywen,
				   CWASS_1 | KEY_DEST_CWASS_WEG | KEY_ENC);
		ewse /* CMAC */
			append_key_as_imm(desc, adata->key_viwt, adata->keywen,
					  adata->keywen, CWASS_1 |
					  KEY_DEST_CWASS_WEG);
		/* Westowe context */
		append_seq_woad(desc, ctx_wen, WDST_CWASS_1_CCB |
				WDST_SWCDST_BYTE_CONTEXT);
	}

	set_jump_tgt_hewe(desc, skip_key_woad);

	/* Cwass 1 opewation */
	append_opewation(desc, adata->awgtype | state | OP_AWG_ENCWYPT);

	/*
	 * Woad fwom buf and/ow swc and wwite to weq->wesuwt ow state->context
	 * Cawcuwate wemaining bytes to wead
	 */
	append_math_add(desc, VAWSEQINWEN, SEQINWEN, WEG0, CAAM_CMD_SZ);

	/* Wead wemaining bytes */
	append_seq_fifo_woad(desc, 0, FIFOWD_CWASS_CWASS1 | FIFOWD_TYPE_WAST1 |
			     FIFOWD_TYPE_MSG | FIFOWDST_VWF);

	/*
	 * Save context:
	 * - xcbc: pawtiaw hash, keys K2 and K3
	 * - cmac: pawtiaw hash, constant W = E(K,0)
	 */
	append_seq_stowe(desc, digestsize, WDST_CWASS_1_CCB |
			 WDST_SWCDST_BYTE_CONTEXT);
	if (is_xcbc_aes(adata->awgtype) && state == OP_AWG_AS_INIT)
		/* Save K1 */
		append_fifo_stowe(desc, adata->key_dma, adata->keywen,
				  WDST_CWASS_1_CCB | FIFOST_TYPE_KEY_KEK);
}
EXPOWT_SYMBOW(cnstw_shdsc_sk_hash);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("FSW CAAM ahash descwiptows suppowt");
MODUWE_AUTHOW("NXP Semiconductows");
