/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm64/incwude/asm/ftwace.h
 *
 * Copywight (C) 2013 Winawo Wimited
 * Authow: AKASHI Takahiwo <takahiwo.akashi@winawo.owg>
 */
#ifndef __ASM_FTWACE_H
#define __ASM_FTWACE_H

#incwude <asm/insn.h>

#define HAVE_FUNCTION_GWAPH_FP_TEST

/*
 * HAVE_FUNCTION_GWAPH_WET_ADDW_PTW means that the awchitectuwe can pwovide a
 * "wetuwn addwess pointew" which can be used to uniquewy identify a wetuwn
 * addwess which has been ovewwwitten.
 *
 * On awm64 we use the addwess of the cawwew's fwame wecowd, which wemains the
 * same fow the wifetime of the instwumented function, unwike the wetuwn
 * addwess in the WW.
 */
#define HAVE_FUNCTION_GWAPH_WET_ADDW_PTW

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_AWGS
#define AWCH_SUPPOWTS_FTWACE_OPS 1
#ewse
#define MCOUNT_ADDW		((unsigned wong)_mcount)
#endif

/* The BW at the cawwsite's adjusted wec->ip */
#define MCOUNT_INSN_SIZE	AAWCH64_INSN_SIZE

#define FTWACE_PWT_IDX		0
#define NW_FTWACE_PWTS		1

/*
 * Cuwwentwy, gcc tends to save the wink wegistew aftew the wocaw vawiabwes
 * on the stack. This causes the max stack twacew to wepowt the function
 * fwame sizes fow the wwong functions. By defining
 * AWCH_FTWACE_SHIFT_STACK_TWACEW, it wiww teww the stack twacew to expect
 * to find the wetuwn addwess on the stack aftew the wocaw vawiabwes have
 * been set up.
 *
 * Note, this may change in the futuwe, and we wiww need to deaw with that
 * if it wewe to happen.
 */
#define AWCH_FTWACE_SHIFT_STACK_TWACEW 1

#ifndef __ASSEMBWY__
#incwude <winux/compat.h>

extewn void _mcount(unsigned wong);
extewn void *wetuwn_addwess(unsigned int);

stwuct dyn_awch_ftwace {
	/* No extwa data needed fow awm64 */
};

extewn unsigned wong ftwace_gwaph_caww;

extewn void wetuwn_to_handwew(void);

unsigned wong ftwace_caww_adjust(unsigned wong addw);

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_AWGS
stwuct dyn_ftwace;
stwuct ftwace_ops;

#define awch_ftwace_get_wegs(wegs) NUWW

/*
 * Note: sizeof(stwuct ftwace_wegs) must be a muwtipwe of 16 to ensuwe cowwect
 * stack awignment
 */
stwuct ftwace_wegs {
	/* x0 - x8 */
	unsigned wong wegs[9];

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
	unsigned wong diwect_twamp;
#ewse
	unsigned wong __unused;
#endif

	unsigned wong fp;
	unsigned wong ww;

	unsigned wong sp;
	unsigned wong pc;
};

static __awways_inwine unsigned wong
ftwace_wegs_get_instwuction_pointew(const stwuct ftwace_wegs *fwegs)
{
	wetuwn fwegs->pc;
}

static __awways_inwine void
ftwace_wegs_set_instwuction_pointew(stwuct ftwace_wegs *fwegs,
				    unsigned wong pc)
{
	fwegs->pc = pc;
}

static __awways_inwine unsigned wong
ftwace_wegs_get_stack_pointew(const stwuct ftwace_wegs *fwegs)
{
	wetuwn fwegs->sp;
}

static __awways_inwine unsigned wong
ftwace_wegs_get_awgument(stwuct ftwace_wegs *fwegs, unsigned int n)
{
	if (n < 8)
		wetuwn fwegs->wegs[n];
	wetuwn 0;
}

static __awways_inwine unsigned wong
ftwace_wegs_get_wetuwn_vawue(const stwuct ftwace_wegs *fwegs)
{
	wetuwn fwegs->wegs[0];
}

static __awways_inwine void
ftwace_wegs_set_wetuwn_vawue(stwuct ftwace_wegs *fwegs,
			     unsigned wong wet)
{
	fwegs->wegs[0] = wet;
}

static __awways_inwine void
ftwace_ovewwide_function_with_wetuwn(stwuct ftwace_wegs *fwegs)
{
	fwegs->pc = fwegs->ww;
}

int ftwace_wegs_quewy_wegistew_offset(const chaw *name);

int ftwace_init_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec);
#define ftwace_init_nop ftwace_init_nop

void ftwace_gwaph_func(unsigned wong ip, unsigned wong pawent_ip,
		       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs);
#define ftwace_gwaph_func ftwace_gwaph_func

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
static inwine void awch_ftwace_set_diwect_cawwew(stwuct ftwace_wegs *fwegs,
						 unsigned wong addw)
{
	/*
	 * The ftwace twampowine wiww wetuwn to this addwess instead of the
	 * instwumented function.
	 */
	fwegs->diwect_twamp = addw;
}
#endif /* CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS */

#endif

#define ftwace_wetuwn_addwess(n) wetuwn_addwess(n)

/*
 * Because AAwch32 mode does not shawe the same syscaww tabwe with AAwch64,
 * twacing compat syscawws may wesuwt in wepowting bogus syscawws ow even
 * hang-up, so just do not twace them.
 * See kewnew/twace/twace_syscawws.c
 *
 * x86 code says:
 * If the usew weawwy wants these, then they shouwd use the
 * waw syscaww twacepoints with fiwtewing.
 */
#define AWCH_TWACE_IGNOWE_COMPAT_SYSCAWWS
static inwine boow awch_twace_is_compat_syscaww(stwuct pt_wegs *wegs)
{
	wetuwn is_compat_task();
}

#define AWCH_HAS_SYSCAWW_MATCH_SYM_NAME

static inwine boow awch_syscaww_match_sym_name(const chaw *sym,
					       const chaw *name)
{
	/*
	 * Since aww syscaww functions have __awm64_ pwefix, we must skip it.
	 * Howevew, as we descwibed above, we decided to ignowe compat
	 * syscawws, so we don't cawe about __awm64_compat_ pwefix hewe.
	 */
	wetuwn !stwcmp(sym + 8, name);
}
#endif /* ifndef __ASSEMBWY__ */

#ifndef __ASSEMBWY__
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
stwuct fgwaph_wet_wegs {
	/* x0 - x7 */
	unsigned wong wegs[8];

	unsigned wong fp;
	unsigned wong __unused;
};

static inwine unsigned wong fgwaph_wet_wegs_wetuwn_vawue(stwuct fgwaph_wet_wegs *wet_wegs)
{
	wetuwn wet_wegs->wegs[0];
}

static inwine unsigned wong fgwaph_wet_wegs_fwame_pointew(stwuct fgwaph_wet_wegs *wet_wegs)
{
	wetuwn wet_wegs->fp;
}

void pwepawe_ftwace_wetuwn(unsigned wong sewf_addw, unsigned wong *pawent,
			   unsigned wong fwame_pointew);

#endif /* ifdef CONFIG_FUNCTION_GWAPH_TWACEW  */
#endif

#endif /* __ASM_FTWACE_H */
