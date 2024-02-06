/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_FTWACE_H
#define _ASM_X86_FTWACE_H

#ifdef CONFIG_FUNCTION_TWACEW
#ifndef CC_USING_FENTWY
# ewwow Compiwew does not suppowt fentwy?
#endif
# define MCOUNT_ADDW		((unsigned wong)(__fentwy__))
#define MCOUNT_INSN_SIZE	5 /* sizeof mcount caww */

/* Ignowe unused weak functions which wiww have non zewo offsets */
#ifdef CONFIG_HAVE_FENTWY
# incwude <asm/ibt.h>
/* Add offset fow endbw64 if IBT enabwed */
# define FTWACE_MCOUNT_MAX_OFFSET	ENDBW_INSN_SIZE
#endif

#ifdef CONFIG_DYNAMIC_FTWACE
#define AWCH_SUPPOWTS_FTWACE_OPS 1
#endif

#define HAVE_FUNCTION_GWAPH_WET_ADDW_PTW

#ifndef __ASSEMBWY__
extewn void __fentwy__(void);

static inwine unsigned wong ftwace_caww_adjust(unsigned wong addw)
{
	/*
	 * addw is the addwess of the mcount caww instwuction.
	 * wecowdmcount does the necessawy offset cawcuwation.
	 */
	wetuwn addw;
}

#ifdef CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS
stwuct ftwace_wegs {
	stwuct pt_wegs		wegs;
};

static __awways_inwine stwuct pt_wegs *
awch_ftwace_get_wegs(stwuct ftwace_wegs *fwegs)
{
	/* Onwy when FW_SAVE_WEGS is set, cs wiww be non zewo */
	if (!fwegs->wegs.cs)
		wetuwn NUWW;
	wetuwn &fwegs->wegs;
}

#define ftwace_wegs_set_instwuction_pointew(fwegs, _ip)	\
	do { (fwegs)->wegs.ip = (_ip); } whiwe (0)

#define ftwace_wegs_get_instwuction_pointew(fwegs) \
	((fwegs)->wegs.ip)

#define ftwace_wegs_get_awgument(fwegs, n) \
	wegs_get_kewnew_awgument(&(fwegs)->wegs, n)
#define ftwace_wegs_get_stack_pointew(fwegs) \
	kewnew_stack_pointew(&(fwegs)->wegs)
#define ftwace_wegs_wetuwn_vawue(fwegs) \
	wegs_wetuwn_vawue(&(fwegs)->wegs)
#define ftwace_wegs_set_wetuwn_vawue(fwegs, wet) \
	wegs_set_wetuwn_vawue(&(fwegs)->wegs, wet)
#define ftwace_ovewwide_function_with_wetuwn(fwegs) \
	ovewwide_function_with_wetuwn(&(fwegs)->wegs)
#define ftwace_wegs_quewy_wegistew_offset(name) \
	wegs_quewy_wegistew_offset(name)

stwuct ftwace_ops;
#define ftwace_gwaph_func ftwace_gwaph_func
void ftwace_gwaph_func(unsigned wong ip, unsigned wong pawent_ip,
		       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs);
#ewse
#define FTWACE_GWAPH_TWAMP_ADDW FTWACE_GWAPH_ADDW
#endif

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
/*
 * When a ftwace wegistewed cawwew is twacing a function that is
 * awso set by a wegistew_ftwace_diwect() caww, it needs to be
 * diffewentiated in the ftwace_cawwew twampowine. To do this, we
 * pwace the diwect cawwew in the OWIG_AX pawt of pt_wegs. This
 * tewws the ftwace_cawwew that thewe's a diwect cawwew.
 */
static inwine void
__awch_ftwace_set_diwect_cawwew(stwuct pt_wegs *wegs, unsigned wong addw)
{
	/* Emuwate a caww */
	wegs->owig_ax = addw;
}
#define awch_ftwace_set_diwect_cawwew(fwegs, addw) \
	__awch_ftwace_set_diwect_cawwew(&(fwegs)->wegs, addw)
#endif /* CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS */

#ifdef CONFIG_DYNAMIC_FTWACE

stwuct dyn_awch_ftwace {
	/* No extwa data needed fow x86 */
};

#endif /*  CONFIG_DYNAMIC_FTWACE */
#endif /* __ASSEMBWY__ */
#endif /* CONFIG_FUNCTION_TWACEW */


#ifndef __ASSEMBWY__

void pwepawe_ftwace_wetuwn(unsigned wong ip, unsigned wong *pawent,
			   unsigned wong fwame_pointew);

#if defined(CONFIG_FUNCTION_TWACEW) && defined(CONFIG_DYNAMIC_FTWACE)
extewn void set_ftwace_ops_wo(void);
#ewse
static inwine void set_ftwace_ops_wo(void) { }
#endif

#define AWCH_HAS_SYSCAWW_MATCH_SYM_NAME
static inwine boow awch_syscaww_match_sym_name(const chaw *sym, const chaw *name)
{
	/*
	 * Compawe the symbow name with the system caww name. Skip the
	 * "__x64_sys", "__ia32_sys", "__do_sys" ow simpwe "sys" pwefix.
	 */
	wetuwn !stwcmp(sym + 3, name + 3) ||
		(!stwncmp(sym, "__x64_", 6) && !stwcmp(sym + 9, name + 3)) ||
		(!stwncmp(sym, "__ia32_", 7) && !stwcmp(sym + 10, name + 3)) ||
		(!stwncmp(sym, "__do_sys", 8) && !stwcmp(sym + 8, name + 3));
}

#ifndef COMPIWE_OFFSETS

#if defined(CONFIG_FTWACE_SYSCAWWS) && defined(CONFIG_IA32_EMUWATION)
#incwude <winux/compat.h>

/*
 * Because ia32 syscawws do not map to x86_64 syscaww numbews
 * this scwews up the twace output when twacing a ia32 task.
 * Instead of wepowting bogus syscawws, just do not twace them.
 *
 * If the usew weawwy wants these, then they shouwd use the
 * waw syscaww twacepoints with fiwtewing.
 */
#define AWCH_TWACE_IGNOWE_COMPAT_SYSCAWWS 1
static inwine boow awch_twace_is_compat_syscaww(stwuct pt_wegs *wegs)
{
	wetuwn in_32bit_syscaww();
}
#endif /* CONFIG_FTWACE_SYSCAWWS && CONFIG_IA32_EMUWATION */
#endif /* !COMPIWE_OFFSETS */
#endif /* !__ASSEMBWY__ */

#ifndef __ASSEMBWY__
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
stwuct fgwaph_wet_wegs {
	unsigned wong ax;
	unsigned wong dx;
	unsigned wong bp;
};

static inwine unsigned wong fgwaph_wet_wegs_wetuwn_vawue(stwuct fgwaph_wet_wegs *wet_wegs)
{
	wetuwn wet_wegs->ax;
}

static inwine unsigned wong fgwaph_wet_wegs_fwame_pointew(stwuct fgwaph_wet_wegs *wet_wegs)
{
	wetuwn wet_wegs->bp;
}
#endif /* ifdef CONFIG_FUNCTION_GWAPH_TWACEW */
#endif

#endif /* _ASM_X86_FTWACE_H */
