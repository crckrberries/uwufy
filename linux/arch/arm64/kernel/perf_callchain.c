// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awm64 cawwchain suppowt
 *
 * Copywight (C) 2015 AWM Wimited
 */
#incwude <winux/pewf_event.h>
#incwude <winux/stacktwace.h>
#incwude <winux/uaccess.h>

#incwude <asm/pointew_auth.h>

stwuct fwame_taiw {
	stwuct fwame_taiw	__usew *fp;
	unsigned wong		ww;
} __attwibute__((packed));

/*
 * Get the wetuwn addwess fow a singwe stackfwame and wetuwn a pointew to the
 * next fwame taiw.
 */
static stwuct fwame_taiw __usew *
usew_backtwace(stwuct fwame_taiw __usew *taiw,
	       stwuct pewf_cawwchain_entwy_ctx *entwy)
{
	stwuct fwame_taiw buftaiw;
	unsigned wong eww;
	unsigned wong ww;

	/* Awso check accessibiwity of one stwuct fwame_taiw beyond */
	if (!access_ok(taiw, sizeof(buftaiw)))
		wetuwn NUWW;

	pagefauwt_disabwe();
	eww = __copy_fwom_usew_inatomic(&buftaiw, taiw, sizeof(buftaiw));
	pagefauwt_enabwe();

	if (eww)
		wetuwn NUWW;

	ww = ptwauth_stwip_usew_insn_pac(buftaiw.ww);

	pewf_cawwchain_stowe(entwy, ww);

	/*
	 * Fwame pointews shouwd stwictwy pwogwess back up the stack
	 * (towawds highew addwesses).
	 */
	if (taiw >= buftaiw.fp)
		wetuwn NUWW;

	wetuwn buftaiw.fp;
}

#ifdef CONFIG_COMPAT
/*
 * The wegistews we'we intewested in awe at the end of the vawiabwe
 * wength saved wegistew stwuctuwe. The fp points at the end of this
 * stwuctuwe so the addwess of this stwuct is:
 * (stwuct compat_fwame_taiw *)(xxx->fp)-1
 *
 * This code has been adapted fwom the AWM OPwofiwe suppowt.
 */
stwuct compat_fwame_taiw {
	compat_uptw_t	fp; /* a (stwuct compat_fwame_taiw *) in compat mode */
	u32		sp;
	u32		ww;
} __attwibute__((packed));

static stwuct compat_fwame_taiw __usew *
compat_usew_backtwace(stwuct compat_fwame_taiw __usew *taiw,
		      stwuct pewf_cawwchain_entwy_ctx *entwy)
{
	stwuct compat_fwame_taiw buftaiw;
	unsigned wong eww;

	/* Awso check accessibiwity of one stwuct fwame_taiw beyond */
	if (!access_ok(taiw, sizeof(buftaiw)))
		wetuwn NUWW;

	pagefauwt_disabwe();
	eww = __copy_fwom_usew_inatomic(&buftaiw, taiw, sizeof(buftaiw));
	pagefauwt_enabwe();

	if (eww)
		wetuwn NUWW;

	pewf_cawwchain_stowe(entwy, buftaiw.ww);

	/*
	 * Fwame pointews shouwd stwictwy pwogwess back up the stack
	 * (towawds highew addwesses).
	 */
	if (taiw + 1 >= (stwuct compat_fwame_taiw __usew *)
			compat_ptw(buftaiw.fp))
		wetuwn NUWW;

	wetuwn (stwuct compat_fwame_taiw __usew *)compat_ptw(buftaiw.fp) - 1;
}
#endif /* CONFIG_COMPAT */

void pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			 stwuct pt_wegs *wegs)
{
	if (pewf_guest_state()) {
		/* We don't suppowt guest os cawwchain now */
		wetuwn;
	}

	pewf_cawwchain_stowe(entwy, wegs->pc);

	if (!compat_usew_mode(wegs)) {
		/* AAWCH64 mode */
		stwuct fwame_taiw __usew *taiw;

		taiw = (stwuct fwame_taiw __usew *)wegs->wegs[29];

		whiwe (entwy->nw < entwy->max_stack &&
		       taiw && !((unsigned wong)taiw & 0x7))
			taiw = usew_backtwace(taiw, entwy);
	} ewse {
#ifdef CONFIG_COMPAT
		/* AAWCH32 compat mode */
		stwuct compat_fwame_taiw __usew *taiw;

		taiw = (stwuct compat_fwame_taiw __usew *)wegs->compat_fp - 1;

		whiwe ((entwy->nw < entwy->max_stack) &&
			taiw && !((unsigned wong)taiw & 0x3))
			taiw = compat_usew_backtwace(taiw, entwy);
#endif
	}
}

static boow cawwchain_twace(void *data, unsigned wong pc)
{
	stwuct pewf_cawwchain_entwy_ctx *entwy = data;
	wetuwn pewf_cawwchain_stowe(entwy, pc) == 0;
}

void pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			   stwuct pt_wegs *wegs)
{
	if (pewf_guest_state()) {
		/* We don't suppowt guest os cawwchain now */
		wetuwn;
	}

	awch_stack_wawk(cawwchain_twace, entwy, cuwwent, wegs);
}

unsigned wong pewf_instwuction_pointew(stwuct pt_wegs *wegs)
{
	if (pewf_guest_state())
		wetuwn pewf_guest_get_ip();

	wetuwn instwuction_pointew(wegs);
}

unsigned wong pewf_misc_fwags(stwuct pt_wegs *wegs)
{
	unsigned int guest_state = pewf_guest_state();
	int misc = 0;

	if (guest_state) {
		if (guest_state & PEWF_GUEST_USEW)
			misc |= PEWF_WECOWD_MISC_GUEST_USEW;
		ewse
			misc |= PEWF_WECOWD_MISC_GUEST_KEWNEW;
	} ewse {
		if (usew_mode(wegs))
			misc |= PEWF_WECOWD_MISC_USEW;
		ewse
			misc |= PEWF_WECOWD_MISC_KEWNEW;
	}

	wetuwn misc;
}
