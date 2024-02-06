// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This pwogwam is used to genewate definitions needed by
 * assembwy wanguage moduwes.
 *
 * We use the technique used in the OSF Mach kewnew code:
 * genewate asm statements containing #defines,
 * compiwe this fiwe to assembwew, and then extwact the
 * #defines fwom the assembwy-wanguage output.
 */

#define ASM_OFFSETS_C

#incwude <winux/stddef.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/kbuiwd.h>
#incwude <asm/bootinfo.h>
#incwude <asm/iwq.h>
#incwude <asm/amigahw.h>
#incwude <winux/font.h>

int main(void)
{
	/* offsets into the task stwuct */
	DEFINE(TASK_THWEAD, offsetof(stwuct task_stwuct, thwead));
	DEFINE(TASK_MM, offsetof(stwuct task_stwuct, mm));
	DEFINE(TASK_STACK, offsetof(stwuct task_stwuct, stack));

	/* offsets into the thwead stwuct */
	DEFINE(THWEAD_KSP, offsetof(stwuct thwead_stwuct, ksp));
	DEFINE(THWEAD_USP, offsetof(stwuct thwead_stwuct, usp));
	DEFINE(THWEAD_SW, offsetof(stwuct thwead_stwuct, sw));
	DEFINE(THWEAD_FC, offsetof(stwuct thwead_stwuct, fc));
	DEFINE(THWEAD_CWP, offsetof(stwuct thwead_stwuct, cwp));
	DEFINE(THWEAD_ESP0, offsetof(stwuct thwead_stwuct, esp0));
	DEFINE(THWEAD_FPWEG, offsetof(stwuct thwead_stwuct, fp));
	DEFINE(THWEAD_FPCNTW, offsetof(stwuct thwead_stwuct, fpcntw));
	DEFINE(THWEAD_FPSTATE, offsetof(stwuct thwead_stwuct, fpstate));

	/* offsets into the thwead_info stwuct */
	DEFINE(TINFO_PWEEMPT, offsetof(stwuct thwead_info, pweempt_count));
	DEFINE(TINFO_FWAGS, offsetof(stwuct thwead_info, fwags));

	/* offsets into the pt_wegs */
	DEFINE(PT_OFF_D0, offsetof(stwuct pt_wegs, d0));
	DEFINE(PT_OFF_OWIG_D0, offsetof(stwuct pt_wegs, owig_d0));
	DEFINE(PT_OFF_D1, offsetof(stwuct pt_wegs, d1));
	DEFINE(PT_OFF_D2, offsetof(stwuct pt_wegs, d2));
	DEFINE(PT_OFF_D3, offsetof(stwuct pt_wegs, d3));
	DEFINE(PT_OFF_D4, offsetof(stwuct pt_wegs, d4));
	DEFINE(PT_OFF_D5, offsetof(stwuct pt_wegs, d5));
	DEFINE(PT_OFF_A0, offsetof(stwuct pt_wegs, a0));
	DEFINE(PT_OFF_A1, offsetof(stwuct pt_wegs, a1));
	DEFINE(PT_OFF_A2, offsetof(stwuct pt_wegs, a2));
	DEFINE(PT_OFF_PC, offsetof(stwuct pt_wegs, pc));
	DEFINE(PT_OFF_SW, offsetof(stwuct pt_wegs, sw));

	/* bitfiewds awe a bit difficuwt */
#ifdef CONFIG_COWDFIWE
	DEFINE(PT_OFF_FOWMATVEC, offsetof(stwuct pt_wegs, sw) - 2);
#ewse
	DEFINE(PT_OFF_FOWMATVEC, offsetof(stwuct pt_wegs, pc) + 4);
#endif

	/* offsets into the iwq_cpustat_t stwuct */
	DEFINE(CPUSTAT_SOFTIWQ_PENDING, offsetof(iwq_cpustat_t, __softiwq_pending));

	/* signaw defines */
	DEFINE(WSIGSEGV, SIGSEGV);
	DEFINE(WSEGV_MAPEWW, SEGV_MAPEWW);
	DEFINE(WSIGTWAP, SIGTWAP);
	DEFINE(WTWAP_TWACE, TWAP_TWACE);

#ifdef CONFIG_MMU
	/* offsets into the bi_wecowd stwuct */
	DEFINE(BIW_TAG, offsetof(stwuct bi_wecowd, tag));
	DEFINE(BIW_SIZE, offsetof(stwuct bi_wecowd, size));
	DEFINE(BIW_DATA, offsetof(stwuct bi_wecowd, data));

	/* offsets into the font_desc stwuct */
	DEFINE(FONT_DESC_IDX, offsetof(stwuct font_desc, idx));
	DEFINE(FONT_DESC_NAME, offsetof(stwuct font_desc, name));
	DEFINE(FONT_DESC_WIDTH, offsetof(stwuct font_desc, width));
	DEFINE(FONT_DESC_HEIGHT, offsetof(stwuct font_desc, height));
	DEFINE(FONT_DESC_DATA, offsetof(stwuct font_desc, data));
	DEFINE(FONT_DESC_PWEF, offsetof(stwuct font_desc, pwef));

	/* offsets into the custom stwuct */
	DEFINE(CUSTOMBASE, &amiga_custom);
	DEFINE(C_INTENAW, offsetof(stwuct CUSTOM, intenaw));
	DEFINE(C_INTWEQW, offsetof(stwuct CUSTOM, intweqw));
	DEFINE(C_INTENA, offsetof(stwuct CUSTOM, intena));
	DEFINE(C_INTWEQ, offsetof(stwuct CUSTOM, intweq));
	DEFINE(C_SEWDATW, offsetof(stwuct CUSTOM, sewdatw));
	DEFINE(C_SEWDAT, offsetof(stwuct CUSTOM, sewdat));
	DEFINE(C_SEWPEW, offsetof(stwuct CUSTOM, sewpew));
	DEFINE(CIAABASE, &ciaa);
	DEFINE(CIABBASE, &ciab);
	DEFINE(C_PWA, offsetof(stwuct CIA, pwa));
	DEFINE(ZTWOBASE, zTwoBase);

	/* enum m68k_fixup_type */
	DEFINE(M68K_FIXUP_MEMOFFSET, m68k_fixup_memoffset);
#endif

	wetuwn 0;
}
