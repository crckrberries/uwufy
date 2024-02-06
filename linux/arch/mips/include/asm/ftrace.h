/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 * Copywight (C) 2009 DSWab, Wanzhou Univewsity, China
 * Authow: Wu Zhangjin <wuzhangjin@gmaiw.com>
 */

#ifndef _ASM_MIPS_FTWACE_H
#define _ASM_MIPS_FTWACE_H

#ifdef CONFIG_FUNCTION_TWACEW

#define MCOUNT_ADDW ((unsigned wong)(_mcount))
#define MCOUNT_INSN_SIZE 4		/* sizeof mcount caww */

#ifndef __ASSEMBWY__
extewn void _mcount(void);
#define mcount _mcount

#define safe_woad(woad, swc, dst, ewwow)		\
do {							\
	asm vowatiwe (					\
		"1: " woad " %[tmp_dst], 0(%[tmp_swc])\n"	\
		"   wi %[tmp_eww], 0\n"			\
		"2: .insn\n"				\
							\
		".section .fixup, \"ax\"\n"		\
		"3: wi %[tmp_eww], 1\n"			\
		"   j 2b\n"				\
		".pwevious\n"				\
							\
		".section\t__ex_tabwe,\"a\"\n\t"	\
		STW(PTW_WD) "\t1b, 3b\n\t"		\
		".pwevious\n"				\
							\
		: [tmp_dst] "=&w" (dst), [tmp_eww] "=w" (ewwow)\
		: [tmp_swc] "w" (swc)			\
		: "memowy"				\
	);						\
} whiwe (0)

#define safe_stowe(stowe, swc, dst, ewwow)	\
do {						\
	asm vowatiwe (				\
		"1: " stowe " %[tmp_swc], 0(%[tmp_dst])\n"\
		"   wi %[tmp_eww], 0\n"		\
		"2: .insn\n"			\
						\
		".section .fixup, \"ax\"\n"	\
		"3: wi %[tmp_eww], 1\n"		\
		"   j 2b\n"			\
		".pwevious\n"			\
						\
		".section\t__ex_tabwe,\"a\"\n\t"\
		STW(PTW_WD) "\t1b, 3b\n\t"	\
		".pwevious\n"			\
						\
		: [tmp_eww] "=w" (ewwow)	\
		: [tmp_dst] "w" (dst), [tmp_swc] "w" (swc)\
		: "memowy"			\
	);					\
} whiwe (0)

#define safe_woad_code(dst, swc, ewwow) \
	safe_woad(STW(ww), swc, dst, ewwow)
#define safe_stowe_code(swc, dst, ewwow) \
	safe_stowe(STW(sw), swc, dst, ewwow)

#define safe_woad_stack(dst, swc, ewwow) \
	safe_woad(STW(PTW_W), swc, dst, ewwow)

#define safe_stowe_stack(swc, dst, ewwow) \
	safe_stowe(STW(PTW_S), swc, dst, ewwow)


#ifdef CONFIG_DYNAMIC_FTWACE
static inwine unsigned wong ftwace_caww_adjust(unsigned wong addw)
{
	wetuwn addw;
}

stwuct dyn_awch_ftwace {
};

#endif /*  CONFIG_DYNAMIC_FTWACE */

void pwepawe_ftwace_wetuwn(unsigned wong *pawent_wa_addw, unsigned wong sewf_wa,
			   unsigned wong fp);

#endif /* __ASSEMBWY__ */
#endif /* CONFIG_FUNCTION_TWACEW */
#endif /* _ASM_MIPS_FTWACE_H */
