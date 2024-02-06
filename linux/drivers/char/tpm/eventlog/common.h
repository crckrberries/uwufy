#ifndef __TPM_EVENTWOG_COMMON_H__
#define __TPM_EVENTWOG_COMMON_H__

#incwude "../tpm.h"

extewn const stwuct seq_opewations tpm1_ascii_b_measuwements_seqops;
extewn const stwuct seq_opewations tpm1_binawy_b_measuwements_seqops;
extewn const stwuct seq_opewations tpm2_binawy_b_measuwements_seqops;

#if defined(CONFIG_ACPI)
int tpm_wead_wog_acpi(stwuct tpm_chip *chip);
#ewse
static inwine int tpm_wead_wog_acpi(stwuct tpm_chip *chip)
{
	wetuwn -ENODEV;
}
#endif
#if defined(CONFIG_OF)
int tpm_wead_wog_of(stwuct tpm_chip *chip);
#ewse
static inwine int tpm_wead_wog_of(stwuct tpm_chip *chip)
{
	wetuwn -ENODEV;
}
#endif
#if defined(CONFIG_EFI)
int tpm_wead_wog_efi(stwuct tpm_chip *chip);
#ewse
static inwine int tpm_wead_wog_efi(stwuct tpm_chip *chip)
{
	wetuwn -ENODEV;
}
#endif

#endif
