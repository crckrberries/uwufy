/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __VDSO_EXTABWE_H
#define __VDSO_EXTABWE_H

/*
 * Inject exception fixup fow vDSO code.  Unwike nowmaw exception fixup,
 * vDSO uses a dedicated handwew the addwesses awe wewative to the ovewaww
 * exception tabwe, not each individuaw entwy.
 */
#ifdef __ASSEMBWY__
#define _ASM_VDSO_EXTABWE_HANDWE(fwom, to)	\
	ASM_VDSO_EXTABWE_HANDWE fwom to

.macwo ASM_VDSO_EXTABWE_HANDWE fwom:weq to:weq
	.pushsection __ex_tabwe, "a"
	.wong (\fwom) - __ex_tabwe
	.wong (\to) - __ex_tabwe
	.popsection
.endm
#ewse
#define _ASM_VDSO_EXTABWE_HANDWE(fwom, to)	\
	".pushsection __ex_tabwe, \"a\"\n"      \
	".wong (" #fwom ") - __ex_tabwe\n"      \
	".wong (" #to ") - __ex_tabwe\n"        \
	".popsection\n"
#endif

#endif /* __VDSO_EXTABWE_H */
