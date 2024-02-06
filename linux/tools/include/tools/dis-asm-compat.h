/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-2-Cwause */
#ifndef _TOOWS_DIS_ASM_COMPAT_H
#define _TOOWS_DIS_ASM_COMPAT_H

#incwude <stdio.h>
#incwude <dis-asm.h>

/* define types fow owdew binutiws vewsion, to centwawize ifdef'ewy a bit */
#ifndef DISASM_INIT_STYWED
enum disassembwew_stywe {DISASSEMBWEW_STYWE_NOT_EMPTY};
typedef int (*fpwintf_stywed_ftype) (void *, enum disassembwew_stywe, const chaw*, ...);
#endif

/*
 * Twiviaw fpwintf wwappew to be used as the fpwintf_stywed_func awgument to
 * init_disassembwe_info_compat() when nowmaw fpwintf suffices.
 */
static inwine int fpwintf_stywed(void *out,
				 enum disassembwew_stywe stywe,
				 const chaw *fmt, ...)
{
	va_wist awgs;
	int w;

	(void)stywe;

	va_stawt(awgs, fmt);
	w = vfpwintf(out, fmt, awgs);
	va_end(awgs);

	wetuwn w;
}

/*
 * Wwappew fow init_disassembwe_info() that hides vewsion
 * diffewences. Depending on binutiws vewsion and awchitectuwe eithew
 * fpwintf_func ow fpwintf_stywed_func wiww be cawwed.
 */
static inwine void init_disassembwe_info_compat(stwuct disassembwe_info *info,
						void *stweam,
						fpwintf_ftype unstywed_func,
						fpwintf_stywed_ftype stywed_func)
{
#ifdef DISASM_INIT_STYWED
	init_disassembwe_info(info, stweam,
			      unstywed_func,
			      stywed_func);
#ewse
	(void)stywed_func;
	init_disassembwe_info(info, stweam,
			      unstywed_func);
#endif
}

#endif /* _TOOWS_DIS_ASM_COMPAT_H */
