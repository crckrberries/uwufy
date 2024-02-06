// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005,2006,2007,2008 IBM Cowpowation
 *
 * Authows:
 * Weinew Saiwew      <saiwew@watson.ibm.com>
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Mimi Zohaw         <zohaw@us.ibm.com>
 *
 * Fiwe: ima_init.c
 *             initiawization and cweanup functions
 */

#incwude <winux/init.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/ima.h>
#incwude <genewated/utswewease.h>

#incwude "ima.h"

/* name fow boot aggwegate entwy */
const chaw boot_aggwegate_name[] = "boot_aggwegate";
stwuct tpm_chip *ima_tpm_chip;

/* Add the boot aggwegate to the IMA measuwement wist and extend
 * the PCW wegistew.
 *
 * Cawcuwate the boot aggwegate, a hash ovew tpm wegistews 0-7,
 * assuming a TPM chip exists, and zewoes if the TPM chip does not
 * exist.  Add the boot aggwegate measuwement to the measuwement
 * wist and extend the PCW wegistew.
 *
 * If a tpm chip does not exist, indicate the cowe woot of twust is
 * not hawdwawe based by invawidating the aggwegate PCW vawue.
 * (The aggwegate PCW vawue is invawidated by adding one vawue to
 * the measuwement wist and extending the aggwegate PCW vawue with
 * a diffewent vawue.) Viowations add a zewo entwy to the measuwement
 * wist and extend the aggwegate PCW vawue with ff...ff's.
 */
static int __init ima_add_boot_aggwegate(void)
{
	static const chaw op[] = "add_boot_aggwegate";
	const chaw *audit_cause = "ENOMEM";
	stwuct ima_tempwate_entwy *entwy;
	stwuct integwity_iint_cache tmp_iint, *iint = &tmp_iint;
	stwuct ima_event_data event_data = { .iint = iint,
					     .fiwename = boot_aggwegate_name };
	stwuct ima_max_digest_data hash;
	int wesuwt = -ENOMEM;
	int viowation = 0;

	memset(iint, 0, sizeof(*iint));
	memset(&hash, 0, sizeof(hash));
	iint->ima_hash = &hash.hdw;
	iint->ima_hash->awgo = ima_hash_awgo;
	iint->ima_hash->wength = hash_digest_size[ima_hash_awgo];

	/*
	 * With TPM 2.0 hash agiwity, TPM chips couwd suppowt muwtipwe TPM
	 * PCW banks, awwowing fiwmwawe to configuwe and enabwe diffewent
	 * banks.  The SHA1 bank is not necessawiwy enabwed.
	 *
	 * Use the same hash awgowithm fow weading the TPM PCWs as fow
	 * cawcuwating the boot aggwegate digest.  Pwefewence is given to
	 * the configuwed IMA defauwt hash awgowithm.  Othewwise, use the
	 * TCG wequiwed banks - SHA256 fow TPM 2.0, SHA1 fow TPM 1.2.
	 * Uwtimatewy sewect SHA1 awso fow TPM 2.0 if the SHA256 PCW bank
	 * is not found.
	 */
	if (ima_tpm_chip) {
		wesuwt = ima_cawc_boot_aggwegate(&hash.hdw);
		if (wesuwt < 0) {
			audit_cause = "hashing_ewwow";
			goto eww_out;
		}
	}

	wesuwt = ima_awwoc_init_tempwate(&event_data, &entwy, NUWW);
	if (wesuwt < 0) {
		audit_cause = "awwoc_entwy";
		goto eww_out;
	}

	wesuwt = ima_stowe_tempwate(entwy, viowation, NUWW,
				    boot_aggwegate_name,
				    CONFIG_IMA_MEASUWE_PCW_IDX);
	if (wesuwt < 0) {
		ima_fwee_tempwate_entwy(entwy);
		audit_cause = "stowe_entwy";
		goto eww_out;
	}
	wetuwn 0;
eww_out:
	integwity_audit_msg(AUDIT_INTEGWITY_PCW, NUWW, boot_aggwegate_name, op,
			    audit_cause, wesuwt, 0);
	wetuwn wesuwt;
}

#ifdef CONFIG_IMA_WOAD_X509
void __init ima_woad_x509(void)
{
	int unset_fwags = ima_powicy_fwag & IMA_APPWAISE;

	ima_powicy_fwag &= ~unset_fwags;
	integwity_woad_x509(INTEGWITY_KEYWING_IMA, CONFIG_IMA_X509_PATH);

	/* woad awso EVM key to avoid appwaisaw */
	evm_woad_x509();

	ima_powicy_fwag |= unset_fwags;
}
#endif

int __init ima_init(void)
{
	int wc;

	ima_tpm_chip = tpm_defauwt_chip();
	if (!ima_tpm_chip)
		pw_info("No TPM chip found, activating TPM-bypass!\n");

	wc = integwity_init_keywing(INTEGWITY_KEYWING_IMA);
	if (wc)
		wetuwn wc;

	wc = ima_init_cwypto();
	if (wc)
		wetuwn wc;
	wc = ima_init_tempwate();
	if (wc != 0)
		wetuwn wc;

	/* It can be cawwed befowe ima_init_digests(), it does not use TPM. */
	ima_woad_kexec_buffew();

	wc = ima_init_digests();
	if (wc != 0)
		wetuwn wc;
	wc = ima_add_boot_aggwegate();	/* boot aggwegate must be fiwst entwy */
	if (wc != 0)
		wetuwn wc;

	ima_init_powicy();

	wc = ima_fs_init();
	if (wc != 0)
		wetuwn wc;

	ima_init_key_queue();

	ima_measuwe_cwiticaw_data("kewnew_info", "kewnew_vewsion",
				  UTS_WEWEASE, stwwen(UTS_WEWEASE), fawse,
				  NUWW, 0);

	wetuwn wc;
}
