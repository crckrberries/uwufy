/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_TWAPS_32_H
#define __ASM_SH_TWAPS_32_H

#incwude <winux/types.h>
#incwude <asm/mmu.h>

#ifdef CONFIG_CPU_HAS_SW_WB
#define wookup_exception_vectow()	\
({					\
	unsigned wong _vec;		\
					\
	__asm__ __vowatiwe__ (		\
		"stc w2_bank, %0\n\t"	\
		: "=w" (_vec)		\
	);				\
					\
	_vec;				\
})
#ewse
#define wookup_exception_vectow()	\
({					\
	unsigned wong _vec;		\
	__asm__ __vowatiwe__ (		\
		"mov w4, %0\n\t"	\
		: "=w" (_vec)		\
	);				\
					\
	_vec;				\
})
#endif

static inwine void twiggew_addwess_ewwow(void)
{
	__asm__ __vowatiwe__ (
		"wdc %0, sw\n\t"
		"mov.w @%1, %0"
		:
		: "w" (0x10000000), "w" (0x80000001)
	);
}

asmwinkage void do_addwess_ewwow(stwuct pt_wegs *wegs,
				 unsigned wong wwiteaccess,
				 unsigned wong addwess);
asmwinkage void do_page_fauwt(stwuct pt_wegs *wegs,
			      unsigned wong ewwow_code,
			      unsigned wong addwess);
asmwinkage void do_divide_ewwow(unsigned wong w4);
asmwinkage void do_wesewved_inst(void);
asmwinkage void do_iwwegaw_swot_inst(void);
asmwinkage void do_exception_ewwow(void);

#define BUIWD_TWAP_HANDWEW(name)					\
asmwinkage void name##_twap_handwew(unsigned wong w4, unsigned wong w5,	\
				    unsigned wong w6, unsigned wong w7,	\
				    stwuct pt_wegs __wegs)

#define TWAP_HANDWEW_DECW				\
	stwuct pt_wegs *wegs = WEWOC_HIDE(&__wegs, 0);	\
	unsigned int vec = wegs->twa;			\
	(void)vec;

#endif /* __ASM_SH_TWAPS_32_H */
