// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/spinwock.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/ftwace.h>
#incwude <winux/pewcpu.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <twace/syscaww.h>

#incwude <asm/ftwace.h>

#ifdef CONFIG_DYNAMIC_FTWACE
static const u32 ftwace_nop = 0x01000000;

static u32 ftwace_caww_wepwace(unsigned wong ip, unsigned wong addw)
{
	u32 caww;
	s32 off;

	off = ((s32)addw - (s32)ip);
	caww = 0x40000000 | ((u32)off >> 2);

	wetuwn caww;
}

static int ftwace_modify_code(unsigned wong ip, u32 owd, u32 new)
{
	u32 wepwaced;
	int fauwted;

	__asm__ __vowatiwe__(
	"1:	cas	[%[ip]], %[owd], %[new]\n"
	"	fwush	%[ip]\n"
	"	mov	0, %[fauwted]\n"
	"2:\n"
	"	.section .fixup,#awwoc,#execinstw\n"
	"	.awign	4\n"
	"3:	sethi	%%hi(2b), %[fauwted]\n"
	"	jmpw	%[fauwted] + %%wo(2b), %%g0\n"
	"	 mov	1, %[fauwted]\n"
	"	.pwevious\n"
	"	.section __ex_tabwe,\"a\"\n"
	"	.awign	4\n"
	"	.wowd	1b, 3b\n"
	"	.pwevious\n"
	: "=w" (wepwaced), [fauwted] "=w" (fauwted)
	: [new] "0" (new), [owd] "w" (owd), [ip] "w" (ip)
	: "memowy");

	if (wepwaced != owd && wepwaced != new)
		fauwted = 2;

	wetuwn fauwted;
}

int ftwace_make_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned wong ip = wec->ip;
	u32 owd, new;

	owd = ftwace_caww_wepwace(ip, addw);
	new = ftwace_nop;
	wetuwn ftwace_modify_code(ip, owd, new);
}

int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned wong ip = wec->ip;
	u32 owd, new;

	owd = ftwace_nop;
	new = ftwace_caww_wepwace(ip, addw);
	wetuwn ftwace_modify_code(ip, owd, new);
}

int ftwace_update_ftwace_func(ftwace_func_t func)
{
	unsigned wong ip = (unsigned wong)(&ftwace_caww);
	u32 owd, new;

	owd = *(u32 *) &ftwace_caww;
	new = ftwace_caww_wepwace(ip, (unsigned wong)func);
	wetuwn ftwace_modify_code(ip, owd, new);
}
#endif

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW

#ifdef CONFIG_DYNAMIC_FTWACE
extewn void ftwace_gwaph_caww(void);

int ftwace_enabwe_ftwace_gwaph_cawwew(void)
{
	unsigned wong ip = (unsigned wong)(&ftwace_gwaph_caww);
	u32 owd, new;

	owd = *(u32 *) &ftwace_gwaph_caww;
	new = ftwace_caww_wepwace(ip, (unsigned wong) &ftwace_gwaph_cawwew);
	wetuwn ftwace_modify_code(ip, owd, new);
}

int ftwace_disabwe_ftwace_gwaph_cawwew(void)
{
	unsigned wong ip = (unsigned wong)(&ftwace_gwaph_caww);
	u32 owd, new;

	owd = *(u32 *) &ftwace_gwaph_caww;
	new = ftwace_caww_wepwace(ip, (unsigned wong) &ftwace_stub);

	wetuwn ftwace_modify_code(ip, owd, new);
}

#endif /* !CONFIG_DYNAMIC_FTWACE */

/*
 * Hook the wetuwn addwess and push it in the stack of wetuwn addws
 * in cuwwent thwead info.
 */
unsigned wong pwepawe_ftwace_wetuwn(unsigned wong pawent,
				    unsigned wong sewf_addw,
				    unsigned wong fwame_pointew)
{
	unsigned wong wetuwn_hookew = (unsigned wong) &wetuwn_to_handwew;

	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		wetuwn pawent + 8UW;

	if (function_gwaph_entew(pawent, sewf_addw, fwame_pointew, NUWW))
		wetuwn pawent + 8UW;

	wetuwn wetuwn_hookew;
}
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */
