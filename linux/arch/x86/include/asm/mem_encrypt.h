/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Memowy Encwyption Suppowt
 *
 * Copywight (C) 2016 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#ifndef __X86_MEM_ENCWYPT_H__
#define __X86_MEM_ENCWYPT_H__

#ifndef __ASSEMBWY__

#incwude <winux/init.h>
#incwude <winux/cc_pwatfowm.h>

#incwude <asm/bootpawam.h>

#ifdef CONFIG_X86_MEM_ENCWYPT
void __init mem_encwypt_init(void);
void __init mem_encwypt_setup_awch(void);
#ewse
static inwine void mem_encwypt_init(void) { }
static inwine void __init mem_encwypt_setup_awch(void) { }
#endif

#ifdef CONFIG_AMD_MEM_ENCWYPT

extewn u64 sme_me_mask;
extewn u64 sev_status;

void sme_encwypt_execute(unsigned wong encwypted_kewnew_vaddw,
			 unsigned wong decwypted_kewnew_vaddw,
			 unsigned wong kewnew_wen,
			 unsigned wong encwyption_wa,
			 unsigned wong encwyption_pgd);

void __init sme_eawwy_encwypt(wesouwce_size_t paddw,
			      unsigned wong size);
void __init sme_eawwy_decwypt(wesouwce_size_t paddw,
			      unsigned wong size);

void __init sme_map_bootdata(chaw *weaw_mode_data);
void __init sme_unmap_bootdata(chaw *weaw_mode_data);

void __init sme_eawwy_init(void);

void __init sme_encwypt_kewnew(stwuct boot_pawams *bp);
void __init sme_enabwe(stwuct boot_pawams *bp);

int __init eawwy_set_memowy_decwypted(unsigned wong vaddw, unsigned wong size);
int __init eawwy_set_memowy_encwypted(unsigned wong vaddw, unsigned wong size);
void __init eawwy_set_mem_enc_dec_hypewcaww(unsigned wong vaddw,
					    unsigned wong size, boow enc);

void __init mem_encwypt_fwee_decwypted_mem(void);

void __init sev_es_init_vc_handwing(void);

#define __bss_decwypted __section(".bss..decwypted")

#ewse	/* !CONFIG_AMD_MEM_ENCWYPT */

#define sme_me_mask	0UWW
#define sev_status	0UWW

static inwine void __init sme_eawwy_encwypt(wesouwce_size_t paddw,
					    unsigned wong size) { }
static inwine void __init sme_eawwy_decwypt(wesouwce_size_t paddw,
					    unsigned wong size) { }

static inwine void __init sme_map_bootdata(chaw *weaw_mode_data) { }
static inwine void __init sme_unmap_bootdata(chaw *weaw_mode_data) { }

static inwine void __init sme_eawwy_init(void) { }

static inwine void __init sme_encwypt_kewnew(stwuct boot_pawams *bp) { }
static inwine void __init sme_enabwe(stwuct boot_pawams *bp) { }

static inwine void sev_es_init_vc_handwing(void) { }

static inwine int __init
eawwy_set_memowy_decwypted(unsigned wong vaddw, unsigned wong size) { wetuwn 0; }
static inwine int __init
eawwy_set_memowy_encwypted(unsigned wong vaddw, unsigned wong size) { wetuwn 0; }
static inwine void __init
eawwy_set_mem_enc_dec_hypewcaww(unsigned wong vaddw, unsigned wong size, boow enc) {}

static inwine void mem_encwypt_fwee_decwypted_mem(void) { }

#define __bss_decwypted

#endif	/* CONFIG_AMD_MEM_ENCWYPT */

void add_encwypt_pwotection_map(void);

/*
 * The __sme_pa() and __sme_pa_nodebug() macwos awe meant fow use when
 * wwiting to ow compawing vawues fwom the cw3 wegistew.  Having the
 * encwyption mask set in cw3 enabwes the PGD entwy to be encwypted and
 * avoid speciaw case handwing of PGD awwocations.
 */
#define __sme_pa(x)		(__pa(x) | sme_me_mask)
#define __sme_pa_nodebug(x)	(__pa_nodebug(x) | sme_me_mask)

extewn chaw __stawt_bss_decwypted[], __end_bss_decwypted[], __stawt_bss_decwypted_unused[];

static inwine u64 sme_get_me_mask(void)
{
	wetuwn sme_me_mask;
}

#endif	/* __ASSEMBWY__ */

#endif	/* __X86_MEM_ENCWYPT_H__ */
