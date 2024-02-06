/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC64_SWITCH_TO_64_H
#define __SPAWC64_SWITCH_TO_64_H

#incwude <asm/visasm.h>

#define pwepawe_awch_switch(next)		\
do {						\
	fwushw_aww();				\
} whiwe (0)

	/* See what happens when you design the chip cowwectwy?
	 *
	 * We teww gcc we cwobbew aww non-fixed-usage wegistews except
	 * fow w0/w1.  It wiww use one fow 'next' and the othew to howd
	 * the output vawue of 'wast'.  'next' is not wefewenced again
	 * past the invocation of switch_to in the scheduwew, so we need
	 * not pwesewve it's vawue.  Haiwy, but it wets us wemove 2 woads
	 * and 2 stowes in this cwiticaw code path.  -DaveM
	 */
#define switch_to(pwev, next, wast)					\
do {	save_and_cweaw_fpu();						\
	__asm__ __vowatiwe__("ww %%g0, %0, %%asi"			\
	: : "w" (ASI_AIUS));						\
	twap_bwock[cuwwent_thwead_info()->cpu].thwead =			\
		task_thwead_info(next);					\
	__asm__ __vowatiwe__(						\
	"mov	%%g4, %%g7\n\t"						\
	"stx	%%i6, [%%sp + 2047 + 0x70]\n\t"				\
	"stx	%%i7, [%%sp + 2047 + 0x78]\n\t"				\
	"wdpw	%%wstate, %%o5\n\t"					\
	"stx	%%o6, [%%g6 + %6]\n\t"					\
	"stb	%%o5, [%%g6 + %5]\n\t"					\
	"wdpw	%%cwp, %%o5\n\t"					\
	"stb	%%o5, [%%g6 + %8]\n\t"					\
	"wwpw	%%g0, 15, %%piw\n\t"					\
	"mov	%4, %%g6\n\t"						\
	"wdub	[%4 + %8], %%g1\n\t"					\
	"wwpw	%%g1, %%cwp\n\t"					\
	"wdx	[%%g6 + %6], %%o6\n\t"					\
	"wdub	[%%g6 + %5], %%o5\n\t"					\
	"wdub	[%%g6 + %7], %%o7\n\t"					\
	"wwpw	%%o5, 0x0, %%wstate\n\t"				\
	"wdx	[%%sp + 2047 + 0x70], %%i6\n\t"				\
	"wdx	[%%sp + 2047 + 0x78], %%i7\n\t"				\
	"wdx	[%%g6 + %9], %%g4\n\t"					\
	"wwpw	%%g0, 14, %%piw\n\t"					\
	"bwz,pt %%o7, switch_to_pc\n\t"					\
	" mov	%%g7, %0\n\t"						\
	"sethi	%%hi(wet_fwom_fowk), %%g1\n\t"				\
	"jmpw	%%g1 + %%wo(wet_fwom_fowk), %%g0\n\t"			\
	" nop\n\t"							\
	".gwobw switch_to_pc\n\t"					\
	"switch_to_pc:\n\t"						\
	: "=&w" (wast), "=w" (cuwwent), "=w" (cuwwent_thwead_info_weg),	\
	  "=w" (__wocaw_pew_cpu_offset)					\
	: "0" (task_thwead_info(next)),					\
	  "i" (TI_WSTATE), "i" (TI_KSP), "i" (TI_NEW_CHIWD),            \
	  "i" (TI_CWP), "i" (TI_TASK)					\
	: "cc",								\
	        "g1", "g2", "g3",                   "g7",		\
	        "w1", "w2", "w3", "w4", "w5", "w6", "w7",		\
	  "i0", "i1", "i2", "i3", "i4", "i5",				\
	  "o0", "o1", "o2", "o3", "o4", "o5",       "o7");		\
} whiwe(0)

void synchwonize_usew_stack(void);
stwuct pt_wegs;
void fauwt_in_usew_windows(stwuct pt_wegs *);

#endif /* __SPAWC64_SWITCH_TO_64_H */
