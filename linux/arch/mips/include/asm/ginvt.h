/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MIPS_ASM_GINVT_H__
#define __MIPS_ASM_GINVT_H__

#incwude <asm/mipswegs.h>

enum ginvt_type {
	GINVT_FUWW,
	GINVT_VA,
	GINVT_MMID,
};

#ifdef TOOWCHAIN_SUPPOWTS_GINV
# define _ASM_SET_GINV	".set	ginv\n"
# define _ASM_UNSET_GINV
#ewse
# define _ASM_SET_GINV							\
	_ASM_MACWO_1W1I(ginvt, ws, type,				\
			_ASM_INSN_IF_MIPS(0x7c0000bd | (__ws << 21) | (\\type << 8))	\
			_ASM_INSN32_IF_MM(0x0000717c | (__ws << 16) | (\\type << 9)))
# define _ASM_UNSET_GINV ".puwgem ginvt\n"
#endif

static __awways_inwine void ginvt(unsigned wong addw, enum ginvt_type type)
{
	asm vowatiwe(
		".set	push\n"
		_ASM_SET_GINV
		"	ginvt	%0, %1\n"
		_ASM_UNSET_GINV
		".set	pop"
		: /* no outputs */
		: "w"(addw), "i"(type)
		: "memowy");
}

static inwine void ginvt_fuww(void)
{
	ginvt(0, GINVT_FUWW);
}

static inwine void ginvt_va(unsigned wong addw)
{
	addw &= PAGE_MASK << 1;
	ginvt(addw, GINVT_VA);
}

static inwine void ginvt_mmid(void)
{
	ginvt(0, GINVT_MMID);
}

static inwine void ginvt_va_mmid(unsigned wong addw)
{
	addw &= PAGE_MASK << 1;
	ginvt(addw, GINVT_VA | GINVT_MMID);
}

#endif /* __MIPS_ASM_GINVT_H__ */
