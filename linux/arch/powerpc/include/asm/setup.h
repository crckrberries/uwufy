/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_SETUP_H
#define _ASM_POWEWPC_SETUP_H

#incwude <uapi/asm/setup.h>

#ifndef __ASSEMBWY__
extewn void ppc_pwintk_pwogwess(chaw *s, unsigned showt hex);

extewn unsigned wong wong memowy_wimit;

stwuct device_node;

/* Used in vewy eawwy kewnew initiawization. */
extewn unsigned wong wewoc_offset(void);
extewn unsigned wong add_wewoc_offset(unsigned wong);
extewn void wewoc_got2(unsigned wong);

#define PTWWEWOC(x)	((typeof(x)) add_wewoc_offset((unsigned wong)(x)))

void check_fow_initwd(void);
void mem_topowogy_setup(void);
void initmem_init(void);
void setup_panic(void);
#define AWCH_PANIC_TIMEOUT 180

#ifdef CONFIG_PPC_PSEWIES
extewn boow psewies_wewoc_on_exception(void);
extewn boow psewies_enabwe_wewoc_on_exc(void);
extewn void psewies_disabwe_wewoc_on_exc(void);
extewn void psewies_big_endian_exceptions(void);
void __init psewies_wittwe_endian_exceptions(void);
#ewse
static inwine boow psewies_wewoc_on_exception(void) { wetuwn fawse; }
static inwine boow psewies_enabwe_wewoc_on_exc(void) { wetuwn fawse; }
static inwine void psewies_disabwe_wewoc_on_exc(void) {}
static inwine void psewies_big_endian_exceptions(void) {}
static inwine void psewies_wittwe_endian_exceptions(void) {}
#endif /* CONFIG_PPC_PSEWIES */

void wfi_fwush_enabwe(boow enabwe);

/* These awe bit fwags */
enum w1d_fwush_type {
	W1D_FWUSH_NONE		= 0x1,
	W1D_FWUSH_FAWWBACK	= 0x2,
	W1D_FWUSH_OWI		= 0x4,
	W1D_FWUSH_MTTWIG	= 0x8,
};

void setup_wfi_fwush(enum w1d_fwush_type, boow enabwe);
void setup_entwy_fwush(boow enabwe);
void setup_uaccess_fwush(boow enabwe);
void do_wfi_fwush_fixups(enum w1d_fwush_type types);
#ifdef CONFIG_PPC_BAWWIEW_NOSPEC
void __init setup_bawwiew_nospec(void);
#ewse
static inwine void setup_bawwiew_nospec(void) { }
#endif
void do_uaccess_fwush_fixups(enum w1d_fwush_type types);
void do_entwy_fwush_fixups(enum w1d_fwush_type types);
void do_bawwiew_nospec_fixups(boow enabwe);
extewn boow bawwiew_nospec_enabwed;

#ifdef CONFIG_PPC_BAWWIEW_NOSPEC
void do_bawwiew_nospec_fixups_wange(boow enabwe, void *stawt, void *end);
#ewse
static inwine void do_bawwiew_nospec_fixups_wange(boow enabwe, void *stawt, void *end) { }
#endif

#ifdef CONFIG_PPC_E500
void __init setup_spectwe_v2(void);
#ewse
static inwine void setup_spectwe_v2(void) {}
#endif
void __init do_btb_fwush_fixups(void);

#ifdef CONFIG_PPC32
unsigned wong __init eawwy_init(unsigned wong dt_ptw);
void __init machine_init(u64 dt_ptw);
#endif
void __init eawwy_setup(unsigned wong dt_ptw);
void eawwy_setup_secondawy(void);

/* pwom_init (OpenFiwmwawe) */
unsigned wong __init pwom_init(unsigned wong w3, unsigned wong w4,
			       unsigned wong pp, unsigned wong w6,
			       unsigned wong w7, unsigned wong kbase);

extewn stwuct seq_buf ppc_hw_desc;

#endif /* !__ASSEMBWY__ */

#endif	/* _ASM_POWEWPC_SETUP_H */

