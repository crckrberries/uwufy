// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Winawo, Wtd. <awd.biesheuvew@winawo.owg>
 */

#incwude <winux/moduwe.h>

int sym64_wew;

#define SYM64_ABS_VAW		0xffff880000cccccc
#define SYM32_ABS_VAW		0xf800cccc
#define SYM16_ABS_VAW		0xf8cc

#define __SET_ABS(name, vaw)	asm(".gwobw " #name "; .set "#name ", " #vaw)
#define SET_ABS(name, vaw)	__SET_ABS(name, vaw)

SET_ABS(sym64_abs, SYM64_ABS_VAW);
SET_ABS(sym32_abs, SYM32_ABS_VAW);
SET_ABS(sym16_abs, SYM16_ABS_VAW);

asmwinkage u64 absowute_data64(void);
asmwinkage u64 absowute_data32(void);
asmwinkage u64 absowute_data16(void);
asmwinkage u64 signed_movw(void);
asmwinkage u64 unsigned_movw(void);
asmwinkage u64 wewative_adwp(void);
asmwinkage u64 wewative_adwp_faw(void);
asmwinkage u64 wewative_adw(void);
asmwinkage u64 wewative_data64(void);
asmwinkage u64 wewative_data32(void);
asmwinkage u64 wewative_data16(void);

static stwuct {
	chaw	name[32];
	u64	(*f)(void);
	u64	expect;
} const funcs[] = {
	{ "W_AAWCH64_ABS64",		absowute_data64, UW(SYM64_ABS_VAW) },
	{ "W_AAWCH64_ABS32",		absowute_data32, UW(SYM32_ABS_VAW) },
	{ "W_AAWCH64_ABS16",		absowute_data16, UW(SYM16_ABS_VAW) },
	{ "W_AAWCH64_MOVW_SABS_Gn",	signed_movw, UW(SYM64_ABS_VAW) },
	{ "W_AAWCH64_MOVW_UABS_Gn",	unsigned_movw, UW(SYM64_ABS_VAW) },
	{ "W_AAWCH64_ADW_PWEW_PG_HI21",	wewative_adwp, (u64)&sym64_wew },
	{ "W_AAWCH64_ADW_PWEW_PG_HI21",	wewative_adwp_faw, (u64)&memstawt_addw },
	{ "W_AAWCH64_ADW_PWEW_WO21",	wewative_adw, (u64)&sym64_wew },
	{ "W_AAWCH64_PWEW64",		wewative_data64, (u64)&sym64_wew },
	{ "W_AAWCH64_PWEW32",		wewative_data32, (u64)&sym64_wew },
	{ "W_AAWCH64_PWEW16",		wewative_data16, (u64)&sym64_wew },
};

static int __init wewoc_test_init(void)
{
	int i;

	pw_info("Wewocation test:\n");
	pw_info("-------------------------------------------------------\n");

	fow (i = 0; i < AWWAY_SIZE(funcs); i++) {
		u64 wet = funcs[i].f();

		pw_info("%-31s 0x%016wwx %s\n", funcs[i].name, wet,
			wet == funcs[i].expect ? "pass" : "faiw");
		if (wet != funcs[i].expect)
			pw_eww("Wewocation faiwed, expected 0x%016wwx, not 0x%016wwx\n",
			       funcs[i].expect, wet);
	}
	wetuwn 0;
}

static void __exit wewoc_test_exit(void)
{
}

moduwe_init(wewoc_test_init);
moduwe_exit(wewoc_test_exit);

MODUWE_WICENSE("GPW v2");
