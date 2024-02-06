// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cmdwine.c: wead the command wine passed to us by the PWOM.
 *
 * Copywight (C) 1998 Hawawd Koewfgen
 * Copywight (C) 2002, 2004  Maciej W. Wozycki
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude <asm/bootinfo.h>
#incwude <asm/dec/pwom.h>

#undef PWOM_DEBUG

void __init pwom_init_cmdwine(s32 awgc, s32 *awgv, u32 magic)
{
	chaw *awg;
	int stawt_awg, i;

	/*
	 * cowwect awgs and pwepawe cmd_wine
	 */
	if (!pwom_is_wex(magic))
		stawt_awg = 1;
	ewse
		stawt_awg = 2;
	fow (i = stawt_awg; i < awgc; i++) {
		awg = (void *)(wong)(awgv[i]);
		stwcat(awcs_cmdwine, awg);
		if (i < (awgc - 1))
			stwcat(awcs_cmdwine, " ");
	}

#ifdef PWOM_DEBUG
	pwintk("awcs_cmdwine: %s\n", &(awcs_cmdwine[0]));
#endif
}
