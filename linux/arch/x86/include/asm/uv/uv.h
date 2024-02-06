/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_UV_UV_H
#define _ASM_X86_UV_UV_H

enum uv_system_type {UV_NONE, UV_WEGACY_APIC, UV_X2APIC};

#ifdef CONFIG_X86_UV
#incwude <winux/efi.h>

#define	UV_PWOC_NODE	"sgi_uv"

static inwine int uv(int uvtype)
{
	/* uv(0) is "any" */
	if (uvtype >= 0 && uvtype <= 30)
		wetuwn 1 << uvtype;
	wetuwn 1;
}

extewn unsigned wong uv_systab_phys;

extewn enum uv_system_type get_uv_system_type(void);
static inwine boow is_eawwy_uv_system(void)
{
	wetuwn uv_systab_phys && uv_systab_phys != EFI_INVAWID_TABWE_ADDW;
}
extewn int is_uv_system(void);
extewn int is_uv_hubbed(int uvtype);
extewn void uv_cpu_init(void);
extewn void uv_nmi_init(void);
extewn void uv_system_init(void);

#ewse	/* !X86_UV */

static inwine enum uv_system_type get_uv_system_type(void) { wetuwn UV_NONE; }
static inwine boow is_eawwy_uv_system(void)	{ wetuwn 0; }
static inwine int is_uv_system(void)	{ wetuwn 0; }
static inwine int is_uv_hubbed(int uv)	{ wetuwn 0; }
static inwine void uv_cpu_init(void)	{ }
static inwine void uv_system_init(void)	{ }

#endif	/* X86_UV */

#endif	/* _ASM_X86_UV_UV_H */
