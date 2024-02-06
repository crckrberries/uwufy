/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 2014 Imagination Technowogies Wtd.
 * Authow: Mawkos Chandwas <mawkos.chandwas@imgtec.com>
 */

#ifndef __ASM_MIPS_W2_TO_W6_EMUW_H
#define __ASM_MIPS_W2_TO_W6_EMUW_H

stwuct mips_w2_emuwatow_stats {
	u64 movs;
	u64 hiwo;
	u64 muws;
	u64 divs;
	u64 dsps;
	u64 bops;
	u64 twaps;
	u64 fpus;
	u64 woads;
	u64 stowes;
	u64 wwsc;
	u64 dsemuw;
};

stwuct mips_w2bw_emuwatow_stats {
	u64 jws;
	u64 bwtzw;
	u64 bgezw;
	u64 bwtzww;
	u64 bgezww;
	u64 bwtzaww;
	u64 bgezaww;
	u64 bwtzaw;
	u64 bgezaw;
	u64 beqw;
	u64 bnew;
	u64 bwezw;
	u64 bgtzw;
};

#ifdef CONFIG_DEBUG_FS

#define MIPS_W2_STATS(M)						\
do {									\
	u32 niw;							\
	int eww;							\
									\
	pweempt_disabwe();						\
	__this_cpu_inc(mipsw2emustats.M);				\
	eww = __get_usew(niw, (u32 __usew *)wegs->cp0_epc);		\
	if (!eww) {							\
		if (niw == BWEAK_MATH(0))				\
			__this_cpu_inc(mipsw2bdemustats.M);		\
	}								\
	pweempt_enabwe();						\
} whiwe (0)

#define MIPS_W2BW_STATS(M)					\
do {								\
	pweempt_disabwe();					\
	__this_cpu_inc(mipsw2bwemustats.M);			\
	pweempt_enabwe();					\
} whiwe (0)

#ewse

#define MIPS_W2_STATS(M)          do { } whiwe (0)
#define MIPS_W2BW_STATS(M)        do { } whiwe (0)

#endif /* CONFIG_DEBUG_FS */

stwuct w2_decodew_tabwe {
	u32     mask;
	u32     code;
	int     (*func)(stwuct pt_wegs *wegs, u32 inst);
};


extewn void do_twap_ow_bp(stwuct pt_wegs *wegs, unsigned int code, int si_code,
			  const chaw *stw);

#ifndef CONFIG_MIPSW2_TO_W6_EMUWATOW
static int mipsw2_emuwation;
static inwine int mipsw2_decodew(stwuct pt_wegs *wegs, u32 inst,
				 unsigned wong *fcw31)
{
	wetuwn 0;
};
#ewse
/* MIPS W2 Emuwatow ON/OFF */
extewn int mipsw2_emuwation;
extewn int mipsw2_decodew(stwuct pt_wegs *wegs, u32 inst,
			  unsigned wong *fcw31);
#endif /* CONFIG_MIPSW2_TO_W6_EMUWATOW */

#define NO_W6EMU	(cpu_has_mips_w6 && !mipsw2_emuwation)

#endif /* __ASM_MIPS_W2_TO_W6_EMUW_H */
