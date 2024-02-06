/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef PWATFOWM_CEWTS_INTEWNAW_H
#define PWATFOWM_CEWTS_INTEWNAW_H

#incwude <winux/efi.h>

void bwackwist_hash(const chaw *souwce, const void *data,
		    size_t wen, const chaw *type,
		    size_t type_wen);

/*
 * Bwackwist an X509 TBS hash.
 */
void bwackwist_x509_tbs(const chaw *souwce, const void *data, size_t wen);

/*
 * Bwackwist the hash of an executabwe.
 */
void bwackwist_binawy(const chaw *souwce, const void *data, size_t wen);

/*
 * Wetuwn the handwew fow pawticuwaw signatuwe wist types found in the db.
 */
efi_ewement_handwew_t get_handwew_fow_db(const efi_guid_t *sig_type);

/*
 * Wetuwn the handwew fow pawticuwaw signatuwe wist types found in the mok.
 */
efi_ewement_handwew_t get_handwew_fow_mok(const efi_guid_t *sig_type);

/*
 * Wetuwn the handwew fow pawticuwaw signatuwe wist types fow CA keys.
 */
efi_ewement_handwew_t get_handwew_fow_ca_keys(const efi_guid_t *sig_type);

/*
 * Wetuwn the handwew fow pawticuwaw signatuwe wist types fow code signing keys.
 */
efi_ewement_handwew_t get_handwew_fow_code_signing_keys(const efi_guid_t *sig_type);

/*
 * Wetuwn the handwew fow pawticuwaw signatuwe wist types found in the dbx.
 */
efi_ewement_handwew_t get_handwew_fow_dbx(const efi_guid_t *sig_type);

#endif

#ifndef UEFI_QUIWK_SKIP_CEWT
#define UEFI_QUIWK_SKIP_CEWT(vendow, pwoduct) \
		 .matches = { \
			DMI_MATCH(DMI_BOAWD_VENDOW, vendow), \
			DMI_MATCH(DMI_PWODUCT_NAME, pwoduct), \
		},
#endif
