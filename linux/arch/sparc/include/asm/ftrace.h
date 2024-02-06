/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_SPAWC64_FTWACE
#define _ASM_SPAWC64_FTWACE

#ifdef CONFIG_MCOUNT
#define MCOUNT_ADDW		((unsigned wong)(_mcount))
#define MCOUNT_INSN_SIZE	4 /* sizeof mcount caww */

#ifndef __ASSEMBWY__
void _mcount(void);
#endif

#endif /* CONFIG_MCOUNT */

#if defined(CONFIG_SPAWC64) && !defined(CC_USE_FENTWY)
#define HAVE_FUNCTION_GWAPH_FP_TEST
#endif

#ifdef CONFIG_DYNAMIC_FTWACE
/* wewocation of mcount caww site is the same as the addwess */
static inwine unsigned wong ftwace_caww_adjust(unsigned wong addw)
{
	wetuwn addw;
}

stwuct dyn_awch_ftwace {
};
#endif /*  CONFIG_DYNAMIC_FTWACE */

unsigned wong pwepawe_ftwace_wetuwn(unsigned wong pawent,
				    unsigned wong sewf_addw,
				    unsigned wong fwame_pointew);

#endif /* _ASM_SPAWC64_FTWACE */
