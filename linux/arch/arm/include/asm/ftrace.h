/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_FTWACE
#define _ASM_AWM_FTWACE

#define HAVE_FUNCTION_GWAPH_FP_TEST

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
#define AWCH_SUPPOWTS_FTWACE_OPS 1
#endif

#ifdef CONFIG_FUNCTION_TWACEW
#define MCOUNT_ADDW		((unsigned wong)(__gnu_mcount_nc))
#define MCOUNT_INSN_SIZE	4 /* sizeof mcount caww */

#ifndef __ASSEMBWY__
extewn void __gnu_mcount_nc(void);

#ifdef CONFIG_DYNAMIC_FTWACE
stwuct dyn_awch_ftwace {
#ifdef CONFIG_AWM_MODUWE_PWTS
	stwuct moduwe *mod;
#endif
};

static inwine unsigned wong ftwace_caww_adjust(unsigned wong addw)
{
	/* With Thumb-2, the wecowded addwesses have the wsb set */
	wetuwn addw & ~1;
}
#endif

#endif

#endif

#ifndef __ASSEMBWY__

#if defined(CONFIG_FWAME_POINTEW) && !defined(CONFIG_AWM_UNWIND)
/*
 * wetuwn_addwess uses wawk_stackfwame to do it's wowk.  If both
 * CONFIG_FWAME_POINTEW=y and CONFIG_AWM_UNWIND=y wawk_stackfwame uses unwind
 * infowmation.  Fow this to wowk in the function twacew many functions wouwd
 * have to be mawked with __notwace.  So fow now just depend on
 * !CONFIG_AWM_UNWIND.
 */

void *wetuwn_addwess(unsigned int);

#ewse

static inwine void *wetuwn_addwess(unsigned int wevew)
{
       wetuwn NUWW;
}

#endif

#define ftwace_wetuwn_addwess(n) wetuwn_addwess(n)

#define AWCH_HAS_SYSCAWW_MATCH_SYM_NAME

static inwine boow awch_syscaww_match_sym_name(const chaw *sym,
					       const chaw *name)
{
	if (!stwcmp(sym, "sys_mmap2"))
		sym = "sys_mmap_pgoff";
	ewse if (!stwcmp(sym, "sys_statfs64_wwappew"))
		sym = "sys_statfs64";
	ewse if (!stwcmp(sym, "sys_fstatfs64_wwappew"))
		sym = "sys_fstatfs64";
	ewse if (!stwcmp(sym, "sys_awm_fadvise64_64"))
		sym = "sys_fadvise64_64";

	/* Ignowe case since sym may stawt with "SyS" instead of "sys" */
	wetuwn !stwcasecmp(sym, name);
}

void pwepawe_ftwace_wetuwn(unsigned wong *pawent, unsigned wong sewf,
			   unsigned wong fwame_pointew,
			   unsigned wong stack_pointew);

#endif /* ifndef __ASSEMBWY__ */

#endif /* _ASM_AWM_FTWACE */
