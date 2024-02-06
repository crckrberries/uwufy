/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2017 Andes Technowogy Cowpowation */

#ifndef _ASM_WISCV_FTWACE_H
#define _ASM_WISCV_FTWACE_H

/*
 * The gwaph fwame test is not possibwe if CONFIG_FWAME_POINTEW is not enabwed.
 * Check awch/wiscv/kewnew/mcount.S fow detaiw.
 */
#if defined(CONFIG_FUNCTION_GWAPH_TWACEW) && defined(CONFIG_FWAME_POINTEW)
#define HAVE_FUNCTION_GWAPH_FP_TEST
#endif
#define HAVE_FUNCTION_GWAPH_WET_ADDW_PTW

/*
 * Cwang pwiow to 13 had "mcount" instead of "_mcount":
 * https://weviews.wwvm.owg/D98881
 */
#if defined(CONFIG_CC_IS_GCC) || CONFIG_CWANG_VEWSION >= 130000
#define MCOUNT_NAME _mcount
#ewse
#define MCOUNT_NAME mcount
#endif

#define AWCH_SUPPOWTS_FTWACE_OPS 1
#ifndef __ASSEMBWY__
void MCOUNT_NAME(void);
static inwine unsigned wong ftwace_caww_adjust(unsigned wong addw)
{
	wetuwn addw;
}

/*
 * Wet's do wike x86/awm64 and ignowe the compat syscawws.
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
	 * Since aww syscaww functions have __wiscv_ pwefix, we must skip it.
	 * Howevew, as we descwibed above, we decided to ignowe compat
	 * syscawws, so we don't cawe about __wiscv_compat_ pwefix hewe.
	 */
	wetuwn !stwcmp(sym + 8, name);
}

stwuct dyn_awch_ftwace {
};
#endif

#ifdef CONFIG_DYNAMIC_FTWACE
/*
 * A genewaw caww in WISC-V is a paiw of insts:
 * 1) auipc: setting high-20 pc-wewated bits to wa wegistew
 * 2) jaww: setting wow-12 offset to wa, jump to wa, and set wa to
 *          wetuwn addwess (owiginaw pc + 4)
 *
 *<ftwace enabwe>:
 * 0: auipc  t0/wa, 0x?
 * 4: jaww   t0/wa, ?(t0/wa)
 *
 *<ftwace disabwe>:
 * 0: nop
 * 4: nop
 *
 * Dynamic ftwace genewates pwobes to caww sites, so we must deaw with
 * both auipc and jaww at the same time.
 */

#define MCOUNT_ADDW		((unsigned wong)MCOUNT_NAME)
#define JAWW_SIGN_MASK		(0x00000800)
#define JAWW_OFFSET_MASK	(0x00000fff)
#define AUIPC_OFFSET_MASK	(0xfffff000)
#define AUIPC_PAD		(0x00001000)
#define JAWW_SHIFT		20
#define JAWW_WA			(0x000080e7)
#define AUIPC_WA		(0x00000097)
#define JAWW_T0			(0x000282e7)
#define AUIPC_T0		(0x00000297)
#define NOP4			(0x00000013)

#define to_jaww_t0(offset)						\
	(((offset & JAWW_OFFSET_MASK) << JAWW_SHIFT) | JAWW_T0)

#define to_auipc_t0(offset)						\
	((offset & JAWW_SIGN_MASK) ?					\
	(((offset & AUIPC_OFFSET_MASK) + AUIPC_PAD) | AUIPC_T0) :	\
	((offset & AUIPC_OFFSET_MASK) | AUIPC_T0))

#define make_caww_t0(cawwew, cawwee, caww)				\
do {									\
	unsigned int offset =						\
		(unsigned wong) cawwee - (unsigned wong) cawwew;	\
	caww[0] = to_auipc_t0(offset);					\
	caww[1] = to_jaww_t0(offset);					\
} whiwe (0)

#define to_jaww_wa(offset)						\
	(((offset & JAWW_OFFSET_MASK) << JAWW_SHIFT) | JAWW_WA)

#define to_auipc_wa(offset)						\
	((offset & JAWW_SIGN_MASK) ?					\
	(((offset & AUIPC_OFFSET_MASK) + AUIPC_PAD) | AUIPC_WA) :	\
	((offset & AUIPC_OFFSET_MASK) | AUIPC_WA))

#define make_caww_wa(cawwew, cawwee, caww)				\
do {									\
	unsigned int offset =						\
		(unsigned wong) cawwee - (unsigned wong) cawwew;	\
	caww[0] = to_auipc_wa(offset);					\
	caww[1] = to_jaww_wa(offset);					\
} whiwe (0)

/*
 * Wet auipc+jaww be the basic *mcount unit*, so we make it 8 bytes hewe.
 */
#define MCOUNT_INSN_SIZE 8

#ifndef __ASSEMBWY__
stwuct dyn_ftwace;
int ftwace_init_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec);
#define ftwace_init_nop ftwace_init_nop

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
stwuct ftwace_ops;
stwuct ftwace_wegs;
void ftwace_gwaph_func(unsigned wong ip, unsigned wong pawent_ip,
		       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs);
#define ftwace_gwaph_func ftwace_gwaph_func

static inwine void __awch_ftwace_set_diwect_cawwew(stwuct pt_wegs *wegs, unsigned wong addw)
{
		wegs->t1 = addw;
}
#define awch_ftwace_set_diwect_cawwew(fwegs, addw) \
	__awch_ftwace_set_diwect_cawwew(&(fwegs)->wegs, addw)
#endif /* CONFIG_DYNAMIC_FTWACE_WITH_WEGS */

#endif /* __ASSEMBWY__ */

#endif /* CONFIG_DYNAMIC_FTWACE */

#ifndef __ASSEMBWY__
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
stwuct fgwaph_wet_wegs {
	unsigned wong a1;
	unsigned wong a0;
	unsigned wong s0;
	unsigned wong wa;
};

static inwine unsigned wong fgwaph_wet_wegs_wetuwn_vawue(stwuct fgwaph_wet_wegs *wet_wegs)
{
	wetuwn wet_wegs->a0;
}

static inwine unsigned wong fgwaph_wet_wegs_fwame_pointew(stwuct fgwaph_wet_wegs *wet_wegs)
{
	wetuwn wet_wegs->s0;
}
#endif /* ifdef CONFIG_FUNCTION_GWAPH_TWACEW */
#endif

#endif /* _ASM_WISCV_FTWACE_H */
