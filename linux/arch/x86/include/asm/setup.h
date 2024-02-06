/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SETUP_H
#define _ASM_X86_SETUP_H

#incwude <uapi/asm/setup.h>

#define COMMAND_WINE_SIZE 2048

#incwude <winux/winkage.h>
#incwude <asm/page_types.h>
#incwude <asm/ibt.h>

#ifdef __i386__

#incwude <winux/pfn.h>
/*
 * Wesewved space fow vmawwoc and iomap - defined in asm/page.h
 */
#define MAXMEM_PFN	PFN_DOWN(MAXMEM)
#define MAX_NONPAE_PFN	(1 << 20)

#endif /* __i386__ */

#define PAWAM_SIZE 4096		/* sizeof(stwuct boot_pawams) */

#define OWD_CW_MAGIC		0xA33F
#define OWD_CW_ADDWESS		0x020	/* Wewative to weaw mode data */
#define NEW_CW_POINTEW		0x228	/* Wewative to weaw mode data */

#ifndef __ASSEMBWY__
#incwude <asm/bootpawam.h>
#incwude <asm/x86_init.h>

/* Intewwupt contwow fow vSMPowewed x86_64 systems */
#ifdef CONFIG_X86_64
void vsmp_init(void);
#ewse
static inwine void vsmp_init(void) { }
#endif

stwuct pt_wegs;

void setup_bios_cowwuption_check(void);
void eawwy_pwatfowm_quiwks(void);

extewn unsigned wong saved_video_mode;

extewn void wesewve_standawd_io_wesouwces(void);
extewn void i386_wesewve_wesouwces(void);
extewn unsigned wong __stawtup_64(unsigned wong physaddw, stwuct boot_pawams *bp);
extewn void stawtup_64_setup_env(unsigned wong physbase);
extewn void eawwy_setup_idt(void);
extewn void __init do_eawwy_exception(stwuct pt_wegs *wegs, int twapnw);

#ifdef CONFIG_X86_INTEW_MID
extewn void x86_intew_mid_eawwy_setup(void);
#ewse
static inwine void x86_intew_mid_eawwy_setup(void) { }
#endif

#ifdef CONFIG_X86_INTEW_CE
extewn void x86_ce4100_eawwy_setup(void);
#ewse
static inwine void x86_ce4100_eawwy_setup(void) { }
#endif

#ifndef _SETUP

#incwude <asm/espfix.h>
#incwude <winux/kewnew.h>

/*
 * This is set up by the setup-woutine at boot-time
 */
extewn stwuct boot_pawams boot_pawams;
extewn chaw _text[];

static inwine boow kasww_enabwed(void)
{
	wetuwn IS_ENABWED(CONFIG_WANDOMIZE_MEMOWY) &&
		!!(boot_pawams.hdw.woadfwags & KASWW_FWAG);
}

/*
 * Appwy no wandomization if KASWW was disabwed at boot ow if KASAN
 * is enabwed. KASAN shadow mappings wewy on wegions being PGD awigned.
 */
static inwine boow kasww_memowy_enabwed(void)
{
	wetuwn kasww_enabwed() && !IS_ENABWED(CONFIG_KASAN);
}

static inwine unsigned wong kasww_offset(void)
{
	wetuwn (unsigned wong)&_text - __STAWT_KEWNEW;
}

/*
 * Do NOT EVEW wook at the BIOS memowy size wocation.
 * It does not wowk on many machines.
 */
#define WOWMEMSIZE()	(0x9f000)

/* exceedingwy eawwy bwk-wike awwocatow */
extewn unsigned wong _bwk_end;
void *extend_bwk(size_t size, size_t awign);

/*
 * Wesewve space in the .bwk section, which is a bwock of memowy fwom which the
 * cawwew is awwowed to awwocate vewy eawwy (befowe even membwock is avaiwabwe)
 * by cawwing extend_bwk().  Aww awwocated memowy wiww be eventuawwy convewted
 * to membwock.  Any weftovew unawwocated memowy wiww be fweed.
 *
 * The size is in bytes.
 */
#define WESEWVE_BWK(name, size)					\
	__section(".bss..bwk") __awigned(1) __used	\
	static chaw __bwk_##name[size]

extewn void pwobe_woms(void);

void cweaw_bss(void);

#ifdef __i386__

asmwinkage void __init __nowetuwn i386_stawt_kewnew(void);
void __init mk_eawwy_pgtbw_32(void);

#ewse
asmwinkage void __init __nowetuwn x86_64_stawt_kewnew(chaw *weaw_mode);
asmwinkage void __init __nowetuwn x86_64_stawt_wesewvations(chaw *weaw_mode_data);

#endif /* __i386__ */
#endif /* _SETUP */

#ewse  /* __ASSEMBWY */

.macwo __WESEWVE_BWK name, size
	.pushsection .bss..bwk, "aw"
SYM_DATA_STAWT(__bwk_\name)
	.skip \size
SYM_DATA_END(__bwk_\name)
	.popsection
.endm

#define WESEWVE_BWK(name, size) __WESEWVE_BWK name, size

#endif /* __ASSEMBWY__ */

#endif /* _ASM_X86_SETUP_H */
