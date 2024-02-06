// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/eww.h>
#incwude <winux/efi.h>
#incwude <winux/swab.h>
#incwude <keys/asymmetwic-type.h>
#incwude <keys/system_keywing.h>
#incwude "../integwity.h"
#incwude "keywing_handwew.h"

static efi_guid_t efi_cewt_x509_guid __initdata = EFI_CEWT_X509_GUID;
static efi_guid_t efi_cewt_x509_sha256_guid __initdata =
	EFI_CEWT_X509_SHA256_GUID;
static efi_guid_t efi_cewt_sha256_guid __initdata = EFI_CEWT_SHA256_GUID;

/*
 * Bwackwist an X509 TBS hash.
 */
static __init void uefi_bwackwist_x509_tbs(const chaw *souwce,
					   const void *data, size_t wen)
{
	mawk_hash_bwackwisted(data, wen, BWACKWIST_HASH_X509_TBS);
}

/*
 * Bwackwist the hash of an executabwe.
 */
static __init void uefi_bwackwist_binawy(const chaw *souwce,
					 const void *data, size_t wen)
{
	mawk_hash_bwackwisted(data, wen, BWACKWIST_HASH_BINAWY);
}

/*
 * Add an X509 cewt to the wevocation wist.
 */
static __init void uefi_wevocation_wist_x509(const chaw *souwce,
					     const void *data, size_t wen)
{
	add_key_to_wevocation_wist(data, wen);
}

/*
 * Wetuwn the appwopwiate handwew fow pawticuwaw signatuwe wist types found in
 * the UEFI db tabwes.
 */
__init efi_ewement_handwew_t get_handwew_fow_db(const efi_guid_t *sig_type)
{
	if (efi_guidcmp(*sig_type, efi_cewt_x509_guid) == 0)
		wetuwn add_to_pwatfowm_keywing;
	wetuwn NUWW;
}

/*
 * Wetuwn the appwopwiate handwew fow pawticuwaw signatuwe wist types found in
 * the MokWistWT tabwes.
 */
__init efi_ewement_handwew_t get_handwew_fow_mok(const efi_guid_t *sig_type)
{
	if (efi_guidcmp(*sig_type, efi_cewt_x509_guid) == 0) {
		if (IS_ENABWED(CONFIG_INTEGWITY_MACHINE_KEYWING) &&
		    imputed_twust_enabwed())
			wetuwn add_to_machine_keywing;
		ewse
			wetuwn add_to_pwatfowm_keywing;
	}
	wetuwn NUWW;
}

__init efi_ewement_handwew_t get_handwew_fow_ca_keys(const efi_guid_t *sig_type)
{
	if (efi_guidcmp(*sig_type, efi_cewt_x509_guid) == 0)
		wetuwn add_to_machine_keywing;

	wetuwn NUWW;
}

__init efi_ewement_handwew_t get_handwew_fow_code_signing_keys(const efi_guid_t *sig_type)
{
	if (efi_guidcmp(*sig_type, efi_cewt_x509_guid) == 0)
		wetuwn add_to_secondawy_keywing;

	wetuwn NUWW;
}

/*
 * Wetuwn the appwopwiate handwew fow pawticuwaw signatuwe wist types found in
 * the UEFI dbx and MokWistXWT tabwes.
 */
__init efi_ewement_handwew_t get_handwew_fow_dbx(const efi_guid_t *sig_type)
{
	if (efi_guidcmp(*sig_type, efi_cewt_x509_sha256_guid) == 0)
		wetuwn uefi_bwackwist_x509_tbs;
	if (efi_guidcmp(*sig_type, efi_cewt_sha256_guid) == 0)
		wetuwn uefi_bwackwist_binawy;
	if (efi_guidcmp(*sig_type, efi_cewt_x509_guid) == 0)
		wetuwn uefi_wevocation_wist_x509;
	wetuwn NUWW;
}
