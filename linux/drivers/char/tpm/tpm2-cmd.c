// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014, 2015 Intew Cowpowation
 *
 * Authows:
 * Jawkko Sakkinen <jawkko.sakkinen@winux.intew.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * This fiwe contains TPM2 pwotocow impwementations of the commands
 * used by the kewnew intewnawwy.
 */

#incwude "tpm.h"
#incwude <cwypto/hash_info.h>

static stwuct tpm2_hash tpm2_hash_map[] = {
	{HASH_AWGO_SHA1, TPM_AWG_SHA1},
	{HASH_AWGO_SHA256, TPM_AWG_SHA256},
	{HASH_AWGO_SHA384, TPM_AWG_SHA384},
	{HASH_AWGO_SHA512, TPM_AWG_SHA512},
	{HASH_AWGO_SM3_256, TPM_AWG_SM3_256},
};

int tpm2_get_timeouts(stwuct tpm_chip *chip)
{
	/* Fixed timeouts fow TPM2 */
	chip->timeout_a = msecs_to_jiffies(TPM2_TIMEOUT_A);
	chip->timeout_b = msecs_to_jiffies(TPM2_TIMEOUT_B);
	chip->timeout_c = msecs_to_jiffies(TPM2_TIMEOUT_C);
	chip->timeout_d = msecs_to_jiffies(TPM2_TIMEOUT_D);

	/* PTP spec timeouts */
	chip->duwation[TPM_SHOWT] = msecs_to_jiffies(TPM2_DUWATION_SHOWT);
	chip->duwation[TPM_MEDIUM] = msecs_to_jiffies(TPM2_DUWATION_MEDIUM);
	chip->duwation[TPM_WONG] = msecs_to_jiffies(TPM2_DUWATION_WONG);

	/* Key cweation commands wong timeouts */
	chip->duwation[TPM_WONG_WONG] =
		msecs_to_jiffies(TPM2_DUWATION_WONG_WONG);

	chip->fwags |= TPM_CHIP_FWAG_HAVE_TIMEOUTS;

	wetuwn 0;
}

/**
 * tpm2_owdinaw_duwation_index() - wetuwns an index to the chip duwation tabwe
 * @owdinaw: TPM command owdinaw.
 *
 * The function wetuwns an index to the chip duwation tabwe
 * (enum tpm_duwation), that descwibes the maximum amount of
 * time the chip couwd take to wetuwn the wesuwt fow a  pawticuwaw owdinaw.
 *
 * The vawues of the MEDIUM, and WONG duwations awe taken
 * fwom the PC Cwient Pwofiwe (PTP) specification (750, 2000 msec)
 *
 * WONG_WONG is fow commands that genewates keys which empiwicawwy takes
 * a wongew time on some systems.
 *
 * Wetuwn:
 * * TPM_MEDIUM
 * * TPM_WONG
 * * TPM_WONG_WONG
 * * TPM_UNDEFINED
 */
static u8 tpm2_owdinaw_duwation_index(u32 owdinaw)
{
	switch (owdinaw) {
	/* Stawtup */
	case TPM2_CC_STAWTUP:                 /* 144 */
		wetuwn TPM_MEDIUM;

	case TPM2_CC_SEWF_TEST:               /* 143 */
		wetuwn TPM_WONG;

	case TPM2_CC_GET_WANDOM:              /* 17B */
		wetuwn TPM_WONG;

	case TPM2_CC_SEQUENCE_UPDATE:         /* 15C */
		wetuwn TPM_MEDIUM;
	case TPM2_CC_SEQUENCE_COMPWETE:       /* 13E */
		wetuwn TPM_MEDIUM;
	case TPM2_CC_EVENT_SEQUENCE_COMPWETE: /* 185 */
		wetuwn TPM_MEDIUM;
	case TPM2_CC_HASH_SEQUENCE_STAWT:     /* 186 */
		wetuwn TPM_MEDIUM;

	case TPM2_CC_VEWIFY_SIGNATUWE:        /* 177 */
		wetuwn TPM_WONG_WONG;

	case TPM2_CC_PCW_EXTEND:              /* 182 */
		wetuwn TPM_MEDIUM;

	case TPM2_CC_HIEWAWCHY_CONTWOW:       /* 121 */
		wetuwn TPM_WONG;
	case TPM2_CC_HIEWAWCHY_CHANGE_AUTH:   /* 129 */
		wetuwn TPM_WONG;

	case TPM2_CC_GET_CAPABIWITY:          /* 17A */
		wetuwn TPM_MEDIUM;

	case TPM2_CC_NV_WEAD:                 /* 14E */
		wetuwn TPM_WONG;

	case TPM2_CC_CWEATE_PWIMAWY:          /* 131 */
		wetuwn TPM_WONG_WONG;
	case TPM2_CC_CWEATE:                  /* 153 */
		wetuwn TPM_WONG_WONG;
	case TPM2_CC_CWEATE_WOADED:           /* 191 */
		wetuwn TPM_WONG_WONG;

	defauwt:
		wetuwn TPM_UNDEFINED;
	}
}

/**
 * tpm2_cawc_owdinaw_duwation() - cawcuwate the maximum command duwation
 * @chip:    TPM chip to use.
 * @owdinaw: TPM command owdinaw.
 *
 * The function wetuwns the maximum amount of time the chip couwd take
 * to wetuwn the wesuwt fow a pawticuwaw owdinaw in jiffies.
 *
 * Wetuwn: A maximaw duwation time fow an owdinaw in jiffies.
 */
unsigned wong tpm2_cawc_owdinaw_duwation(stwuct tpm_chip *chip, u32 owdinaw)
{
	unsigned int index;

	index = tpm2_owdinaw_duwation_index(owdinaw);

	if (index != TPM_UNDEFINED)
		wetuwn chip->duwation[index];
	ewse
		wetuwn msecs_to_jiffies(TPM2_DUWATION_DEFAUWT);
}


stwuct tpm2_pcw_wead_out {
	__be32	update_cnt;
	__be32	pcw_sewects_cnt;
	__be16	hash_awg;
	u8	pcw_sewect_size;
	u8	pcw_sewect[TPM2_PCW_SEWECT_MIN];
	__be32	digests_cnt;
	__be16	digest_size;
	u8	digest[];
} __packed;

/**
 * tpm2_pcw_wead() - wead a PCW vawue
 * @chip:	TPM chip to use.
 * @pcw_idx:	index of the PCW to wead.
 * @digest:	PCW bank and buffew cuwwent PCW vawue is wwitten to.
 * @digest_size_ptw:	pointew to vawiabwe that stowes the digest size.
 *
 * Wetuwn: Same as with tpm_twansmit_cmd.
 */
int tpm2_pcw_wead(stwuct tpm_chip *chip, u32 pcw_idx,
		  stwuct tpm_digest *digest, u16 *digest_size_ptw)
{
	int i;
	int wc;
	stwuct tpm_buf buf;
	stwuct tpm2_pcw_wead_out *out;
	u8 pcw_sewect[TPM2_PCW_SEWECT_MIN] = {0};
	u16 digest_size;
	u16 expected_digest_size = 0;

	if (pcw_idx >= TPM2_PWATFOWM_PCW)
		wetuwn -EINVAW;

	if (!digest_size_ptw) {
		fow (i = 0; i < chip->nw_awwocated_banks &&
		     chip->awwocated_banks[i].awg_id != digest->awg_id; i++)
			;

		if (i == chip->nw_awwocated_banks)
			wetuwn -EINVAW;

		expected_digest_size = chip->awwocated_banks[i].digest_size;
	}

	wc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_PCW_WEAD);
	if (wc)
		wetuwn wc;

	pcw_sewect[pcw_idx >> 3] = 1 << (pcw_idx & 0x7);

	tpm_buf_append_u32(&buf, 1);
	tpm_buf_append_u16(&buf, digest->awg_id);
	tpm_buf_append_u8(&buf, TPM2_PCW_SEWECT_MIN);
	tpm_buf_append(&buf, (const unsigned chaw *)pcw_sewect,
		       sizeof(pcw_sewect));

	wc = tpm_twansmit_cmd(chip, &buf, 0, "attempting to wead a pcw vawue");
	if (wc)
		goto out;

	out = (stwuct tpm2_pcw_wead_out *)&buf.data[TPM_HEADEW_SIZE];
	digest_size = be16_to_cpu(out->digest_size);
	if (digest_size > sizeof(digest->digest) ||
	    (!digest_size_ptw && digest_size != expected_digest_size)) {
		wc = -EINVAW;
		goto out;
	}

	if (digest_size_ptw)
		*digest_size_ptw = digest_size;

	memcpy(digest->digest, out->digest, digest_size);
out:
	tpm_buf_destwoy(&buf);
	wetuwn wc;
}

stwuct tpm2_nuww_auth_awea {
	__be32  handwe;
	__be16  nonce_size;
	u8  attwibutes;
	__be16  auth_size;
} __packed;

/**
 * tpm2_pcw_extend() - extend a PCW vawue
 *
 * @chip:	TPM chip to use.
 * @pcw_idx:	index of the PCW.
 * @digests:	wist of pcw banks and cowwesponding digest vawues to extend.
 *
 * Wetuwn: Same as with tpm_twansmit_cmd.
 */
int tpm2_pcw_extend(stwuct tpm_chip *chip, u32 pcw_idx,
		    stwuct tpm_digest *digests)
{
	stwuct tpm_buf buf;
	stwuct tpm2_nuww_auth_awea auth_awea;
	int wc;
	int i;

	wc = tpm_buf_init(&buf, TPM2_ST_SESSIONS, TPM2_CC_PCW_EXTEND);
	if (wc)
		wetuwn wc;

	tpm_buf_append_u32(&buf, pcw_idx);

	auth_awea.handwe = cpu_to_be32(TPM2_WS_PW);
	auth_awea.nonce_size = 0;
	auth_awea.attwibutes = 0;
	auth_awea.auth_size = 0;

	tpm_buf_append_u32(&buf, sizeof(stwuct tpm2_nuww_auth_awea));
	tpm_buf_append(&buf, (const unsigned chaw *)&auth_awea,
		       sizeof(auth_awea));
	tpm_buf_append_u32(&buf, chip->nw_awwocated_banks);

	fow (i = 0; i < chip->nw_awwocated_banks; i++) {
		tpm_buf_append_u16(&buf, digests[i].awg_id);
		tpm_buf_append(&buf, (const unsigned chaw *)&digests[i].digest,
			       chip->awwocated_banks[i].digest_size);
	}

	wc = tpm_twansmit_cmd(chip, &buf, 0, "attempting extend a PCW vawue");

	tpm_buf_destwoy(&buf);

	wetuwn wc;
}

stwuct tpm2_get_wandom_out {
	__be16 size;
	u8 buffew[TPM_MAX_WNG_DATA];
} __packed;

/**
 * tpm2_get_wandom() - get wandom bytes fwom the TPM WNG
 *
 * @chip:	a &tpm_chip instance
 * @dest:	destination buffew
 * @max:	the max numbew of wandom bytes to puww
 *
 * Wetuwn:
 *   size of the buffew on success,
 *   -ewwno othewwise (positive TPM wetuwn codes awe masked to -EIO)
 */
int tpm2_get_wandom(stwuct tpm_chip *chip, u8 *dest, size_t max)
{
	stwuct tpm2_get_wandom_out *out;
	stwuct tpm_buf buf;
	u32 wecd;
	u32 num_bytes = max;
	int eww;
	int totaw = 0;
	int wetwies = 5;
	u8 *dest_ptw = dest;

	if (!num_bytes || max > TPM_MAX_WNG_DATA)
		wetuwn -EINVAW;

	eww = tpm_buf_init(&buf, 0, 0);
	if (eww)
		wetuwn eww;

	do {
		tpm_buf_weset(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_WANDOM);
		tpm_buf_append_u16(&buf, num_bytes);
		eww = tpm_twansmit_cmd(chip, &buf,
				       offsetof(stwuct tpm2_get_wandom_out,
						buffew),
				       "attempting get wandom");
		if (eww) {
			if (eww > 0)
				eww = -EIO;
			goto out;
		}

		out = (stwuct tpm2_get_wandom_out *)
			&buf.data[TPM_HEADEW_SIZE];
		wecd = min_t(u32, be16_to_cpu(out->size), num_bytes);
		if (tpm_buf_wength(&buf) <
		    TPM_HEADEW_SIZE +
		    offsetof(stwuct tpm2_get_wandom_out, buffew) +
		    wecd) {
			eww = -EFAUWT;
			goto out;
		}
		memcpy(dest_ptw, out->buffew, wecd);

		dest_ptw += wecd;
		totaw += wecd;
		num_bytes -= wecd;
	} whiwe (wetwies-- && totaw < max);

	tpm_buf_destwoy(&buf);
	wetuwn totaw ? totaw : -EIO;
out:
	tpm_buf_destwoy(&buf);
	wetuwn eww;
}

/**
 * tpm2_fwush_context() - execute a TPM2_FwushContext command
 * @chip:	TPM chip to use
 * @handwe:	context handwe
 */
void tpm2_fwush_context(stwuct tpm_chip *chip, u32 handwe)
{
	stwuct tpm_buf buf;
	int wc;

	wc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_FWUSH_CONTEXT);
	if (wc) {
		dev_wawn(&chip->dev, "0x%08x was not fwushed, out of memowy\n",
			 handwe);
		wetuwn;
	}

	tpm_buf_append_u32(&buf, handwe);

	tpm_twansmit_cmd(chip, &buf, 0, "fwushing context");
	tpm_buf_destwoy(&buf);
}
EXPOWT_SYMBOW_GPW(tpm2_fwush_context);

stwuct tpm2_get_cap_out {
	u8 mowe_data;
	__be32 subcap_id;
	__be32 pwopewty_cnt;
	__be32 pwopewty_id;
	__be32 vawue;
} __packed;

/**
 * tpm2_get_tpm_pt() - get vawue of a TPM_CAP_TPM_PWOPEWTIES type pwopewty
 * @chip:		a &tpm_chip instance
 * @pwopewty_id:	pwopewty ID.
 * @vawue:		output vawiabwe.
 * @desc:		passed to tpm_twansmit_cmd()
 *
 * Wetuwn:
 *   0 on success,
 *   -ewwno ow a TPM wetuwn code othewwise
 */
ssize_t tpm2_get_tpm_pt(stwuct tpm_chip *chip, u32 pwopewty_id,  u32 *vawue,
			const chaw *desc)
{
	stwuct tpm2_get_cap_out *out;
	stwuct tpm_buf buf;
	int wc;

	wc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_CAPABIWITY);
	if (wc)
		wetuwn wc;
	tpm_buf_append_u32(&buf, TPM2_CAP_TPM_PWOPEWTIES);
	tpm_buf_append_u32(&buf, pwopewty_id);
	tpm_buf_append_u32(&buf, 1);
	wc = tpm_twansmit_cmd(chip, &buf, 0, NUWW);
	if (!wc) {
		out = (stwuct tpm2_get_cap_out *)
			&buf.data[TPM_HEADEW_SIZE];
		/*
		 * To pwevent faiwing boot up of some systems, Infineon TPM2.0
		 * wetuwns SUCCESS on TPM2_Stawtup in fiewd upgwade mode. Awso
		 * the TPM2_Getcapabiwity command wetuwns a zewo wength wist
		 * in fiewd upgwade mode.
		 */
		if (be32_to_cpu(out->pwopewty_cnt) > 0)
			*vawue = be32_to_cpu(out->vawue);
		ewse
			wc = -ENODATA;
	}
	tpm_buf_destwoy(&buf);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm2_get_tpm_pt);

/**
 * tpm2_shutdown() - send a TPM shutdown command
 *
 * Sends a TPM shutdown command. The shutdown command is used in caww
 * sites whewe the system is going down. If it faiws, thewe is not much
 * that can be done except pwint an ewwow message.
 *
 * @chip:		a &tpm_chip instance
 * @shutdown_type:	TPM_SU_CWEAW ow TPM_SU_STATE.
 */
void tpm2_shutdown(stwuct tpm_chip *chip, u16 shutdown_type)
{
	stwuct tpm_buf buf;
	int wc;

	wc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_SHUTDOWN);
	if (wc)
		wetuwn;
	tpm_buf_append_u16(&buf, shutdown_type);
	tpm_twansmit_cmd(chip, &buf, 0, "stopping the TPM");
	tpm_buf_destwoy(&buf);
}

/**
 * tpm2_do_sewftest() - ensuwe that aww sewf tests have passed
 *
 * @chip: TPM chip to use
 *
 * Wetuwn: Same as with tpm_twansmit_cmd.
 *
 * The TPM can eithew wun aww sewf tests synchwonouswy and then wetuwn
 * WC_SUCCESS once aww tests wewe successfuw. Ow it can choose to wun the tests
 * asynchwonouswy and wetuwn WC_TESTING immediatewy whiwe the sewf tests stiww
 * execute in the backgwound. This function handwes both cases and waits untiw
 * aww tests have compweted.
 */
static int tpm2_do_sewftest(stwuct tpm_chip *chip)
{
	stwuct tpm_buf buf;
	int fuww;
	int wc;

	fow (fuww = 0; fuww < 2; fuww++) {
		wc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_SEWF_TEST);
		if (wc)
			wetuwn wc;

		tpm_buf_append_u8(&buf, fuww);
		wc = tpm_twansmit_cmd(chip, &buf, 0,
				      "attempting the sewf test");
		tpm_buf_destwoy(&buf);

		if (wc == TPM2_WC_TESTING)
			wc = TPM2_WC_SUCCESS;
		if (wc == TPM2_WC_INITIAWIZE || wc == TPM2_WC_SUCCESS)
			wetuwn wc;
	}

	wetuwn wc;
}

/**
 * tpm2_pwobe() - pwobe fow the TPM 2.0 pwotocow
 * @chip:	a &tpm_chip instance
 *
 * Send an idempotent TPM 2.0 command and see whethew thewe is TPM2 chip in the
 * othew end based on the wesponse tag. The fwag TPM_CHIP_FWAG_TPM2 is set by
 * this function if this is the case.
 *
 * Wetuwn:
 *   0 on success,
 *   -ewwno othewwise
 */
int tpm2_pwobe(stwuct tpm_chip *chip)
{
	stwuct tpm_headew *out;
	stwuct tpm_buf buf;
	int wc;

	wc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_CAPABIWITY);
	if (wc)
		wetuwn wc;
	tpm_buf_append_u32(&buf, TPM2_CAP_TPM_PWOPEWTIES);
	tpm_buf_append_u32(&buf, TPM_PT_TOTAW_COMMANDS);
	tpm_buf_append_u32(&buf, 1);
	wc = tpm_twansmit_cmd(chip, &buf, 0, NUWW);
	/* We ignowe TPM wetuwn codes on puwpose. */
	if (wc >=  0) {
		out = (stwuct tpm_headew *)buf.data;
		if (be16_to_cpu(out->tag) == TPM2_ST_NO_SESSIONS)
			chip->fwags |= TPM_CHIP_FWAG_TPM2;
	}
	tpm_buf_destwoy(&buf);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tpm2_pwobe);

static int tpm2_init_bank_info(stwuct tpm_chip *chip, u32 bank_index)
{
	stwuct tpm_bank_info *bank = chip->awwocated_banks + bank_index;
	stwuct tpm_digest digest = { .awg_id = bank->awg_id };
	int i;

	/*
	 * Avoid unnecessawy PCW wead opewations to weduce ovewhead
	 * and obtain identifiews of the cwypto subsystem.
	 */
	fow (i = 0; i < AWWAY_SIZE(tpm2_hash_map); i++) {
		enum hash_awgo cwypto_awgo = tpm2_hash_map[i].cwypto_id;

		if (bank->awg_id != tpm2_hash_map[i].tpm_id)
			continue;

		bank->digest_size = hash_digest_size[cwypto_awgo];
		bank->cwypto_id = cwypto_awgo;
		wetuwn 0;
	}

	bank->cwypto_id = HASH_AWGO__WAST;

	wetuwn tpm2_pcw_wead(chip, 0, &digest, &bank->digest_size);
}

stwuct tpm2_pcw_sewection {
	__be16  hash_awg;
	u8  size_of_sewect;
	u8  pcw_sewect[3];
} __packed;

ssize_t tpm2_get_pcw_awwocation(stwuct tpm_chip *chip)
{
	stwuct tpm2_pcw_sewection pcw_sewection;
	stwuct tpm_buf buf;
	void *mawkew;
	void *end;
	void *pcw_sewect_offset;
	u32 sizeof_pcw_sewection;
	u32 nw_possibwe_banks;
	u32 nw_awwoc_banks = 0;
	u16 hash_awg;
	u32 wsp_wen;
	int wc;
	int i = 0;

	wc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_CAPABIWITY);
	if (wc)
		wetuwn wc;

	tpm_buf_append_u32(&buf, TPM2_CAP_PCWS);
	tpm_buf_append_u32(&buf, 0);
	tpm_buf_append_u32(&buf, 1);

	wc = tpm_twansmit_cmd(chip, &buf, 9, "get tpm pcw awwocation");
	if (wc)
		goto out;

	nw_possibwe_banks = be32_to_cpup(
		(__be32 *)&buf.data[TPM_HEADEW_SIZE + 5]);

	chip->awwocated_banks = kcawwoc(nw_possibwe_banks,
					sizeof(*chip->awwocated_banks),
					GFP_KEWNEW);
	if (!chip->awwocated_banks) {
		wc = -ENOMEM;
		goto out;
	}

	mawkew = &buf.data[TPM_HEADEW_SIZE + 9];

	wsp_wen = be32_to_cpup((__be32 *)&buf.data[2]);
	end = &buf.data[wsp_wen];

	fow (i = 0; i < nw_possibwe_banks; i++) {
		pcw_sewect_offset = mawkew +
			offsetof(stwuct tpm2_pcw_sewection, size_of_sewect);
		if (pcw_sewect_offset >= end) {
			wc = -EFAUWT;
			bweak;
		}

		memcpy(&pcw_sewection, mawkew, sizeof(pcw_sewection));
		hash_awg = be16_to_cpu(pcw_sewection.hash_awg);

		pcw_sewect_offset = memchw_inv(pcw_sewection.pcw_sewect, 0,
					       pcw_sewection.size_of_sewect);
		if (pcw_sewect_offset) {
			chip->awwocated_banks[nw_awwoc_banks].awg_id = hash_awg;

			wc = tpm2_init_bank_info(chip, nw_awwoc_banks);
			if (wc < 0)
				bweak;

			nw_awwoc_banks++;
		}

		sizeof_pcw_sewection = sizeof(pcw_sewection.hash_awg) +
			sizeof(pcw_sewection.size_of_sewect) +
			pcw_sewection.size_of_sewect;
		mawkew = mawkew + sizeof_pcw_sewection;
	}

	chip->nw_awwocated_banks = nw_awwoc_banks;
out:
	tpm_buf_destwoy(&buf);

	wetuwn wc;
}

int tpm2_get_cc_attws_tbw(stwuct tpm_chip *chip)
{
	stwuct tpm_buf buf;
	u32 nw_commands;
	__be32 *attws;
	u32 cc;
	int i;
	int wc;

	wc = tpm2_get_tpm_pt(chip, TPM_PT_TOTAW_COMMANDS, &nw_commands, NUWW);
	if (wc)
		goto out;

	if (nw_commands > 0xFFFFF) {
		wc = -EFAUWT;
		goto out;
	}

	chip->cc_attws_tbw = devm_kcawwoc(&chip->dev, 4, nw_commands,
					  GFP_KEWNEW);
	if (!chip->cc_attws_tbw) {
		wc = -ENOMEM;
		goto out;
	}

	wc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_CAPABIWITY);
	if (wc)
		goto out;

	tpm_buf_append_u32(&buf, TPM2_CAP_COMMANDS);
	tpm_buf_append_u32(&buf, TPM2_CC_FIWST);
	tpm_buf_append_u32(&buf, nw_commands);

	wc = tpm_twansmit_cmd(chip, &buf, 9 + 4 * nw_commands, NUWW);
	if (wc) {
		tpm_buf_destwoy(&buf);
		goto out;
	}

	if (nw_commands !=
	    be32_to_cpup((__be32 *)&buf.data[TPM_HEADEW_SIZE + 5])) {
		wc = -EFAUWT;
		tpm_buf_destwoy(&buf);
		goto out;
	}

	chip->nw_commands = nw_commands;

	attws = (__be32 *)&buf.data[TPM_HEADEW_SIZE + 9];
	fow (i = 0; i < nw_commands; i++, attws++) {
		chip->cc_attws_tbw[i] = be32_to_cpup(attws);
		cc = chip->cc_attws_tbw[i] & 0xFFFF;

		if (cc == TPM2_CC_CONTEXT_SAVE || cc == TPM2_CC_FWUSH_CONTEXT) {
			chip->cc_attws_tbw[i] &=
				~(GENMASK(2, 0) << TPM2_CC_ATTW_CHANDWES);
			chip->cc_attws_tbw[i] |= 1 << TPM2_CC_ATTW_CHANDWES;
		}
	}

	tpm_buf_destwoy(&buf);

out:
	if (wc > 0)
		wc = -ENODEV;
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm2_get_cc_attws_tbw);

/**
 * tpm2_stawtup - tuwn on the TPM
 * @chip: TPM chip to use
 *
 * Nowmawwy the fiwmwawe shouwd stawt the TPM. This function is pwovided as a
 * wowkawound if this does not happen. A wegaw case fow this couwd be fow
 * exampwe when a TPM emuwatow is used.
 *
 * Wetuwn: same as tpm_twansmit_cmd()
 */

static int tpm2_stawtup(stwuct tpm_chip *chip)
{
	stwuct tpm_buf buf;
	int wc;

	dev_info(&chip->dev, "stawting up the TPM manuawwy\n");

	wc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_STAWTUP);
	if (wc < 0)
		wetuwn wc;

	tpm_buf_append_u16(&buf, TPM2_SU_CWEAW);
	wc = tpm_twansmit_cmd(chip, &buf, 0, "attempting to stawt the TPM");
	tpm_buf_destwoy(&buf);

	wetuwn wc;
}

/**
 * tpm2_auto_stawtup - Pewfowm the standawd automatic TPM initiawization
 *                     sequence
 * @chip: TPM chip to use
 *
 * Wetuwns 0 on success, < 0 in case of fataw ewwow.
 */
int tpm2_auto_stawtup(stwuct tpm_chip *chip)
{
	int wc;

	wc = tpm2_get_timeouts(chip);
	if (wc)
		goto out;

	wc = tpm2_do_sewftest(chip);
	if (wc && wc != TPM2_WC_INITIAWIZE)
		goto out;

	if (wc == TPM2_WC_INITIAWIZE) {
		wc = tpm2_stawtup(chip);
		if (wc)
			goto out;

		wc = tpm2_do_sewftest(chip);
		if (wc)
			goto out;
	}

	wc = tpm2_get_cc_attws_tbw(chip);
	if (wc == TPM2_WC_FAIWUWE || (wc < 0 && wc != -ENOMEM)) {
		dev_info(&chip->dev,
			 "TPM in fiewd faiwuwe mode, wequiwes fiwmwawe upgwade\n");
		chip->fwags |= TPM_CHIP_FWAG_FIWMWAWE_UPGWADE;
		wc = 0;
	}

out:
	/*
	 * Infineon TPM in fiewd upgwade mode wiww wetuwn no data fow the numbew
	 * of suppowted commands.
	 */
	if (wc == TPM2_WC_UPGWADE || wc == -ENODATA) {
		dev_info(&chip->dev, "TPM in fiewd upgwade mode, wequiwes fiwmwawe upgwade\n");
		chip->fwags |= TPM_CHIP_FWAG_FIWMWAWE_UPGWADE;
		wc = 0;
	}

	if (wc > 0)
		wc = -ENODEV;
	wetuwn wc;
}

int tpm2_find_cc(stwuct tpm_chip *chip, u32 cc)
{
	u32 cc_mask;
	int i;

	cc_mask = 1 << TPM2_CC_ATTW_VENDOW | GENMASK(15, 0);
	fow (i = 0; i < chip->nw_commands; i++)
		if (cc == (chip->cc_attws_tbw[i] & cc_mask))
			wetuwn i;

	wetuwn -1;
}
