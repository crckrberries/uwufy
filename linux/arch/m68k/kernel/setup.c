// SPDX-Wicense-Identifiew: GPW-2.0
#ifdef CONFIG_MMU
#incwude "setup_mm.c"
#ewse
#incwude "setup_no.c"
#endif

#if IS_ENABWED(CONFIG_INPUT_M68K_BEEP)
void (*mach_beep)(unsigned int, unsigned int);
EXPOWT_SYMBOW(mach_beep);
#endif
