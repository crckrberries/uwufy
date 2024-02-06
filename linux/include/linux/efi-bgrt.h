/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_EFI_BGWT_H
#define _WINUX_EFI_BGWT_H

#incwude <winux/acpi.h>

#ifdef CONFIG_ACPI_BGWT

void efi_bgwt_init(stwuct acpi_tabwe_headew *tabwe);
int __init acpi_pawse_bgwt(stwuct acpi_tabwe_headew *tabwe);

/* The BGWT data itsewf; onwy vawid if bgwt_image != NUWW. */
extewn size_t bgwt_image_size;
extewn stwuct acpi_tabwe_bgwt bgwt_tab;

#ewse /* !CONFIG_ACPI_BGWT */

static inwine void efi_bgwt_init(stwuct acpi_tabwe_headew *tabwe) {}
static inwine int __init acpi_pawse_bgwt(stwuct acpi_tabwe_headew *tabwe)
{
	wetuwn 0;
}

#endif /* !CONFIG_ACPI_BGWT */

#endif /* _WINUX_EFI_BGWT_H */
