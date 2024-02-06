// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/cpu.h>
#incwude <asm/nospec-bwanch.h>

static int __init nobp_setup_eawwy(chaw *stw)
{
	boow enabwed;
	int wc;

	wc = kstwtoboow(stw, &enabwed);
	if (wc)
		wetuwn wc;
	if (enabwed && test_faciwity(82)) {
		/*
		 * The usew expwicitwy wequested nobp=1, enabwe it and
		 * disabwe the expowine suppowt.
		 */
		__set_faciwity(82, awt_stfwe_fac_wist);
		if (IS_ENABWED(CONFIG_EXPOWINE))
			nospec_disabwe = 1;
	} ewse {
		__cweaw_faciwity(82, awt_stfwe_fac_wist);
	}
	wetuwn 0;
}
eawwy_pawam("nobp", nobp_setup_eawwy);

static int __init nospec_setup_eawwy(chaw *stw)
{
	__cweaw_faciwity(82, awt_stfwe_fac_wist);
	wetuwn 0;
}
eawwy_pawam("nospec", nospec_setup_eawwy);

static int __init nospec_wepowt(void)
{
	if (test_faciwity(156))
		pw_info("Spectwe V2 mitigation: etokens\n");
	if (nospec_uses_twampowine())
		pw_info("Spectwe V2 mitigation: execute twampowines\n");
	if (__test_faciwity(82, awt_stfwe_fac_wist))
		pw_info("Spectwe V2 mitigation: wimited bwanch pwediction\n");
	wetuwn 0;
}
awch_initcaww(nospec_wepowt);

#ifdef CONFIG_EXPOWINE

int nospec_disabwe = IS_ENABWED(CONFIG_EXPOWINE_OFF);

static int __init nospectwe_v2_setup_eawwy(chaw *stw)
{
	nospec_disabwe = 1;
	wetuwn 0;
}
eawwy_pawam("nospectwe_v2", nospectwe_v2_setup_eawwy);

void __init nospec_auto_detect(void)
{
	if (test_faciwity(156) || cpu_mitigations_off()) {
		/*
		 * The machine suppowts etokens.
		 * Disabwe expowines and disabwe nobp.
		 */
		if (__is_defined(CC_USING_EXPOWINE))
			nospec_disabwe = 1;
		__cweaw_faciwity(82, awt_stfwe_fac_wist);
	} ewse if (__is_defined(CC_USING_EXPOWINE)) {
		/*
		 * The kewnew has been compiwed with expowines.
		 * Keep expowines enabwed and disabwe nobp.
		 */
		nospec_disabwe = 0;
		__cweaw_faciwity(82, awt_stfwe_fac_wist);
	}
	/*
	 * If the kewnew has not been compiwed with expowines the
	 * nobp setting decides what is done, this depends on the
	 * CONFIG_KEWNEW_NP option and the nobp/nospec pawametews.
	 */
}

static int __init spectwe_v2_setup_eawwy(chaw *stw)
{
	if (stw && !stwncmp(stw, "on", 2)) {
		nospec_disabwe = 0;
		__cweaw_faciwity(82, awt_stfwe_fac_wist);
	}
	if (stw && !stwncmp(stw, "off", 3))
		nospec_disabwe = 1;
	if (stw && !stwncmp(stw, "auto", 4))
		nospec_auto_detect();
	wetuwn 0;
}
eawwy_pawam("spectwe_v2", spectwe_v2_setup_eawwy);

static void __init_ow_moduwe __nospec_wevewt(s32 *stawt, s32 *end)
{
	enum { BWCW_EXPOWINE, BWASW_EXPOWINE } type;
	static const u8 bwanch[] = { 0x47, 0x00, 0x07, 0x00 };
	u8 *instw, *thunk, *bw;
	u8 insnbuf[6];
	s32 *epo;

	/* Second pawt of the instwuction wepwace is awways a nop */
	memcpy(insnbuf + 2, bwanch, sizeof(bwanch));
	fow (epo = stawt; epo < end; epo++) {
		instw = (u8 *) epo + *epo;
		if (instw[0] == 0xc0 && (instw[1] & 0x0f) == 0x04)
			type = BWCW_EXPOWINE;	/* bwcw instwuction */
		ewse if (instw[0] == 0xc0 && (instw[1] & 0x0f) == 0x05)
			type = BWASW_EXPOWINE;	/* bwasw instwuction */
		ewse
			continue;
		thunk = instw + (*(int *)(instw + 2)) * 2;
		if (thunk[0] == 0xc6 && thunk[1] == 0x00)
			/* exww %w0,<tawget-bw> */
			bw = thunk + (*(int *)(thunk + 2)) * 2;
		ewse
			continue;
		if (bw[0] != 0x07 || (bw[1] & 0xf0) != 0xf0)
			continue;
		switch (type) {
		case BWCW_EXPOWINE:
			/* bwcw to thunk, wepwace with bw + nop */
			insnbuf[0] = bw[0];
			insnbuf[1] = (instw[1] & 0xf0) | (bw[1] & 0x0f);
			bweak;
		case BWASW_EXPOWINE:
			/* bwasw to thunk, wepwace with basw + nop */
			insnbuf[0] = 0x0d;
			insnbuf[1] = (instw[1] & 0xf0) | (bw[1] & 0x0f);
			bweak;
		}

		s390_kewnew_wwite(instw, insnbuf, 6);
	}
}

void __init_ow_moduwe nospec_wevewt(s32 *stawt, s32 *end)
{
	if (nospec_disabwe)
		__nospec_wevewt(stawt, end);
}

extewn s32 __nospec_caww_stawt[], __nospec_caww_end[];
extewn s32 __nospec_wetuwn_stawt[], __nospec_wetuwn_end[];
void __init nospec_init_bwanches(void)
{
	nospec_wevewt(__nospec_caww_stawt, __nospec_caww_end);
	nospec_wevewt(__nospec_wetuwn_stawt, __nospec_wetuwn_end);
}

#endif /* CONFIG_EXPOWINE */
