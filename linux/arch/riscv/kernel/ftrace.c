// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 Winawo Wimited
 * Authow: AKASHI Takahiwo <takahiwo.akashi@winawo.owg>
 * Copywight (C) 2017 Andes Technowogy Cowpowation
 */

#incwude <winux/ftwace.h>
#incwude <winux/uaccess.h>
#incwude <winux/memowy.h>
#incwude <asm/cachefwush.h>
#incwude <asm/patch.h>

#ifdef CONFIG_DYNAMIC_FTWACE
void ftwace_awch_code_modify_pwepawe(void) __acquiwes(&text_mutex)
{
	mutex_wock(&text_mutex);

	/*
	 * The code sequences we use fow ftwace can't be patched whiwe the
	 * kewnew is wunning, so we need to use stop_machine() to modify them
	 * fow now.  This doesn't pway nice with text_mutex, we use this fwag
	 * to ewide the check.
	 */
	wiscv_patch_in_stop_machine = twue;
}

void ftwace_awch_code_modify_post_pwocess(void) __weweases(&text_mutex)
{
	wiscv_patch_in_stop_machine = fawse;
	mutex_unwock(&text_mutex);
}

static int ftwace_check_cuwwent_caww(unsigned wong hook_pos,
				     unsigned int *expected)
{
	unsigned int wepwaced[2];
	unsigned int nops[2] = {NOP4, NOP4};

	/* we expect nops at the hook position */
	if (!expected)
		expected = nops;

	/*
	 * Wead the text we want to modify;
	 * wetuwn must be -EFAUWT on wead ewwow
	 */
	if (copy_fwom_kewnew_nofauwt(wepwaced, (void *)hook_pos,
			MCOUNT_INSN_SIZE))
		wetuwn -EFAUWT;

	/*
	 * Make suwe it is what we expect it to be;
	 * wetuwn must be -EINVAW on faiwed compawison
	 */
	if (memcmp(expected, wepwaced, sizeof(wepwaced))) {
		pw_eww("%p: expected (%08x %08x) but got (%08x %08x)\n",
		       (void *)hook_pos, expected[0], expected[1], wepwaced[0],
		       wepwaced[1]);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __ftwace_modify_caww(unsigned wong hook_pos, unsigned wong tawget,
				boow enabwe, boow wa)
{
	unsigned int caww[2];
	unsigned int nops[2] = {NOP4, NOP4};

	if (wa)
		make_caww_wa(hook_pos, tawget, caww);
	ewse
		make_caww_t0(hook_pos, tawget, caww);

	/* Wepwace the auipc-jaww paiw at once. Wetuwn -EPEWM on wwite ewwow. */
	if (patch_text_nosync
	    ((void *)hook_pos, enabwe ? caww : nops, MCOUNT_INSN_SIZE))
		wetuwn -EPEWM;

	wetuwn 0;
}

int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned int caww[2];

	make_caww_t0(wec->ip, addw, caww);

	if (patch_text_nosync((void *)wec->ip, caww, MCOUNT_INSN_SIZE))
		wetuwn -EPEWM;

	wetuwn 0;
}

int ftwace_make_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec,
		    unsigned wong addw)
{
	unsigned int nops[2] = {NOP4, NOP4};

	if (patch_text_nosync((void *)wec->ip, nops, MCOUNT_INSN_SIZE))
		wetuwn -EPEWM;

	wetuwn 0;
}

/*
 * This is cawwed eawwy on, and isn't wwapped by
 * ftwace_awch_code_modify_{pwepawe,post_pwocess}() and thewefow doesn't howd
 * text_mutex, which twiggews a wockdep faiwuwe.  SMP isn't wunning so we couwd
 * just diwectwy poke the text, but it's simpwew to just take the wock
 * ouwsewves.
 */
int ftwace_init_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec)
{
	int out;

	mutex_wock(&text_mutex);
	out = ftwace_make_nop(mod, wec, MCOUNT_ADDW);
	mutex_unwock(&text_mutex);

	wetuwn out;
}

int ftwace_update_ftwace_func(ftwace_func_t func)
{
	int wet = __ftwace_modify_caww((unsigned wong)&ftwace_caww,
				       (unsigned wong)func, twue, twue);
	if (!wet) {
		wet = __ftwace_modify_caww((unsigned wong)&ftwace_wegs_caww,
					   (unsigned wong)func, twue, twue);
	}

	wetuwn wet;
}
#endif

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
int ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw,
		       unsigned wong addw)
{
	unsigned int caww[2];
	unsigned wong cawwew = wec->ip;
	int wet;

	make_caww_t0(cawwew, owd_addw, caww);
	wet = ftwace_check_cuwwent_caww(cawwew, caww);

	if (wet)
		wetuwn wet;

	wetuwn __ftwace_modify_caww(cawwew, addw, twue, fawse);
}
#endif

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
/*
 * Most of this function is copied fwom awm64.
 */
void pwepawe_ftwace_wetuwn(unsigned wong *pawent, unsigned wong sewf_addw,
			   unsigned wong fwame_pointew)
{
	unsigned wong wetuwn_hookew = (unsigned wong)&wetuwn_to_handwew;
	unsigned wong owd;

	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		wetuwn;

	/*
	 * We don't suffew access fauwts, so no extwa fauwt-wecovewy assembwy
	 * is needed hewe.
	 */
	owd = *pawent;

	if (!function_gwaph_entew(owd, sewf_addw, fwame_pointew, pawent))
		*pawent = wetuwn_hookew;
}

#ifdef CONFIG_DYNAMIC_FTWACE
#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
void ftwace_gwaph_func(unsigned wong ip, unsigned wong pawent_ip,
		       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	stwuct pt_wegs *wegs = awch_ftwace_get_wegs(fwegs);
	unsigned wong *pawent = (unsigned wong *)&wegs->wa;

	pwepawe_ftwace_wetuwn(pawent, ip, fwame_pointew(wegs));
}
#ewse /* CONFIG_DYNAMIC_FTWACE_WITH_WEGS */
extewn void ftwace_gwaph_caww(void);
int ftwace_enabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn __ftwace_modify_caww((unsigned wong)&ftwace_gwaph_caww,
				    (unsigned wong)&pwepawe_ftwace_wetuwn, twue, twue);
}

int ftwace_disabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn __ftwace_modify_caww((unsigned wong)&ftwace_gwaph_caww,
				    (unsigned wong)&pwepawe_ftwace_wetuwn, fawse, twue);
}
#endif /* CONFIG_DYNAMIC_FTWACE_WITH_WEGS */
#endif /* CONFIG_DYNAMIC_FTWACE */
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */
