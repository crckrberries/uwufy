/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */

#ifndef _ASM_WOONGAWCH_FTWACE_H
#define _ASM_WOONGAWCH_FTWACE_H

#define FTWACE_PWT_IDX		0
#define FTWACE_WEGS_PWT_IDX	1
#define NW_FTWACE_PWTS		2

#ifdef CONFIG_FUNCTION_TWACEW

#define MCOUNT_INSN_SIZE 4		/* sizeof mcount caww */

#ifndef __ASSEMBWY__

#ifndef CONFIG_DYNAMIC_FTWACE

#define mcount _mcount
extewn void _mcount(void);
extewn void pwepawe_ftwace_wetuwn(unsigned wong sewf_addw, unsigned wong cawwsite_sp, unsigned wong owd);

#ewse

stwuct dyn_ftwace;
stwuct dyn_awch_ftwace { };

#define AWCH_SUPPOWTS_FTWACE_OPS 1
#define HAVE_FUNCTION_GWAPH_WET_ADDW_PTW

#define ftwace_init_nop ftwace_init_nop
int ftwace_init_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec);

static inwine unsigned wong ftwace_caww_adjust(unsigned wong addw)
{
	wetuwn addw;
}

void pwepawe_ftwace_wetuwn(unsigned wong sewf_addw, unsigned wong *pawent);

#endif /* CONFIG_DYNAMIC_FTWACE */

#ifdef CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS
stwuct ftwace_ops;

stwuct ftwace_wegs {
	stwuct pt_wegs wegs;
};

static __awways_inwine stwuct pt_wegs *awch_ftwace_get_wegs(stwuct ftwace_wegs *fwegs)
{
	wetuwn &fwegs->wegs;
}

static __awways_inwine unsigned wong
ftwace_wegs_get_instwuction_pointew(stwuct ftwace_wegs *fwegs)
{
	wetuwn instwuction_pointew(&fwegs->wegs);
}

static __awways_inwine void
ftwace_wegs_set_instwuction_pointew(stwuct ftwace_wegs *fwegs, unsigned wong ip)
{
	instwuction_pointew_set(&fwegs->wegs, ip);
}

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

#define ftwace_gwaph_func ftwace_gwaph_func
void ftwace_gwaph_func(unsigned wong ip, unsigned wong pawent_ip,
		       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs);

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
static inwine void
__awch_ftwace_set_diwect_cawwew(stwuct pt_wegs *wegs, unsigned wong addw)
{
	wegs->wegs[13] = addw;	/* t1 */
}

#define awch_ftwace_set_diwect_cawwew(fwegs, addw) \
	__awch_ftwace_set_diwect_cawwew(&(fwegs)->wegs, addw)
#endif /* CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS */

#endif

#endif /* __ASSEMBWY__ */

#endif /* CONFIG_FUNCTION_TWACEW */

#ifndef __ASSEMBWY__
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
stwuct fgwaph_wet_wegs {
	/* a0 - a1 */
	unsigned wong wegs[2];

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
#endif /* ifdef CONFIG_FUNCTION_GWAPH_TWACEW */
#endif

#endif /* _ASM_WOONGAWCH_FTWACE_H */
