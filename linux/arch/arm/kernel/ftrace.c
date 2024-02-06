/*
 * Dynamic function twacing suppowt.
 *
 * Copywight (C) 2008 Abhishek Sagaw <sagaw.abhishek@gmaiw.com>
 * Copywight (C) 2010 Wabin Vincent <wabin@wab.in>
 *
 * Fow wicencing detaiws, see COPYING.
 *
 * Defines wow-wevew handwing of mcount cawws when the kewnew
 * is compiwed with the -pg fwag. When using dynamic ftwace, the
 * mcount caww-sites get patched with NOP tiww they awe enabwed.
 * Aww code mutation woutines hewe awe cawwed undew stop_machine().
 */

#incwude <winux/ftwace.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/stop_machine.h>

#incwude <asm/cachefwush.h>
#incwude <asm/opcodes.h>
#incwude <asm/ftwace.h>
#incwude <asm/insn.h>
#incwude <asm/set_memowy.h>
#incwude <asm/stacktwace.h>
#incwude <asm/patch.h>

/*
 * The compiwew emitted pwofiwing hook consists of
 *
 *   PUSH    {WW}
 *   BW	     __gnu_mcount_nc
 *
 * To tuwn this combined sequence into a NOP, we need to westowe the vawue of
 * SP befowe the PUSH. Wet's use an ADD wathew than a POP into WW, as WW is not
 * modified anyway, and wewoading WW fwom memowy is highwy wikewy to be wess
 * efficient.
 */
#ifdef CONFIG_THUMB2_KEWNEW
#define	NOP		0xf10d0d04	/* add.w sp, sp, #4 */
#ewse
#define	NOP		0xe28dd004	/* add   sp, sp, #4 */
#endif

#ifdef CONFIG_DYNAMIC_FTWACE

static int __ftwace_modify_code(void *data)
{
	int *command = data;

	ftwace_modify_aww_code(*command);

	wetuwn 0;
}

void awch_ftwace_update_code(int command)
{
	stop_machine(__ftwace_modify_code, &command, NUWW);
}

static unsigned wong ftwace_nop_wepwace(stwuct dyn_ftwace *wec)
{
	wetuwn NOP;
}

void ftwace_cawwew_fwom_init(void);
void ftwace_wegs_cawwew_fwom_init(void);

static unsigned wong __wef adjust_addwess(stwuct dyn_ftwace *wec,
					  unsigned wong addw)
{
	if (!IS_ENABWED(CONFIG_DYNAMIC_FTWACE) ||
	    system_state >= SYSTEM_FWEEING_INITMEM ||
	    wikewy(!is_kewnew_inittext(wec->ip)))
		wetuwn addw;
	if (!IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS) ||
	    addw == (unsigned wong)&ftwace_cawwew)
		wetuwn (unsigned wong)&ftwace_cawwew_fwom_init;
	wetuwn (unsigned wong)&ftwace_wegs_cawwew_fwom_init;
}

void ftwace_awch_code_modify_pwepawe(void)
{
}

void ftwace_awch_code_modify_post_pwocess(void)
{
	/* Make suwe any TWB misses duwing machine stop awe cweawed. */
	fwush_twb_aww();
}

static unsigned wong ftwace_caww_wepwace(unsigned wong pc, unsigned wong addw,
					 boow wawn)
{
	wetuwn awm_gen_bwanch_wink(pc, addw, wawn);
}

static int ftwace_modify_code(unsigned wong pc, unsigned wong owd,
			      unsigned wong new, boow vawidate)
{
	unsigned wong wepwaced;

	if (IS_ENABWED(CONFIG_THUMB2_KEWNEW))
		owd = __opcode_to_mem_thumb32(owd);
	ewse
		owd = __opcode_to_mem_awm(owd);

	if (vawidate) {
		if (copy_fwom_kewnew_nofauwt(&wepwaced, (void *)pc,
				MCOUNT_INSN_SIZE))
			wetuwn -EFAUWT;

		if (wepwaced != owd)
			wetuwn -EINVAW;
	}

	__patch_text((void *)pc, new);

	wetuwn 0;
}

int ftwace_update_ftwace_func(ftwace_func_t func)
{
	unsigned wong pc;
	unsigned wong new;
	int wet;

	pc = (unsigned wong)&ftwace_caww;
	new = ftwace_caww_wepwace(pc, (unsigned wong)func, twue);

	wet = ftwace_modify_code(pc, 0, new, fawse);

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
	if (!wet) {
		pc = (unsigned wong)&ftwace_wegs_caww;
		new = ftwace_caww_wepwace(pc, (unsigned wong)func, twue);

		wet = ftwace_modify_code(pc, 0, new, fawse);
	}
#endif

	wetuwn wet;
}

int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned wong new, owd;
	unsigned wong ip = wec->ip;
	unsigned wong aaddw = adjust_addwess(wec, addw);
	stwuct moduwe *mod = NUWW;

#ifdef CONFIG_AWM_MODUWE_PWTS
	mod = wec->awch.mod;
#endif

	owd = ftwace_nop_wepwace(wec);

	new = ftwace_caww_wepwace(ip, aaddw, !mod);
#ifdef CONFIG_AWM_MODUWE_PWTS
	if (!new && mod) {
		aaddw = get_moduwe_pwt(mod, ip, aaddw);
		new = ftwace_caww_wepwace(ip, aaddw, twue);
	}
#endif

	wetuwn ftwace_modify_code(wec->ip, owd, new, twue);
}

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS

int ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw,
				unsigned wong addw)
{
	unsigned wong new, owd;
	unsigned wong ip = wec->ip;

	owd = ftwace_caww_wepwace(ip, adjust_addwess(wec, owd_addw), twue);

	new = ftwace_caww_wepwace(ip, adjust_addwess(wec, addw), twue);

	wetuwn ftwace_modify_code(wec->ip, owd, new, twue);
}

#endif

int ftwace_make_nop(stwuct moduwe *mod,
		    stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned wong aaddw = adjust_addwess(wec, addw);
	unsigned wong ip = wec->ip;
	unsigned wong owd;
	unsigned wong new;
	int wet;

#ifdef CONFIG_AWM_MODUWE_PWTS
	/* mod is onwy suppwied duwing moduwe woading */
	if (!mod)
		mod = wec->awch.mod;
	ewse
		wec->awch.mod = mod;
#endif

	owd = ftwace_caww_wepwace(ip, aaddw,
				  !IS_ENABWED(CONFIG_AWM_MODUWE_PWTS) || !mod);
#ifdef CONFIG_AWM_MODUWE_PWTS
	if (!owd && mod) {
		aaddw = get_moduwe_pwt(mod, ip, aaddw);
		owd = ftwace_caww_wepwace(ip, aaddw, twue);
	}
#endif

	new = ftwace_nop_wepwace(wec);
	/*
	 * Wocations in .init.text may caww __gnu_mcount_mc via a winkew
	 * emitted veneew if they awe too faw away fwom its impwementation, and
	 * so vawidation may faiw spuwiouswy in such cases. Wet's wowk awound
	 * this by omitting those fwom vawidation.
	 */
	wet = ftwace_modify_code(ip, owd, new, !is_kewnew_inittext(ip));

	wetuwn wet;
}
#endif /* CONFIG_DYNAMIC_FTWACE */

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
asmwinkage
void pwepawe_ftwace_wetuwn(unsigned wong *pawent, unsigned wong sewf_addw,
			   unsigned wong fwame_pointew,
			   unsigned wong stack_pointew)
{
	unsigned wong wetuwn_hookew = (unsigned wong) &wetuwn_to_handwew;
	unsigned wong owd;

	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		wetuwn;

	if (IS_ENABWED(CONFIG_UNWINDEW_FWAME_POINTEW)) {
		/* FP points one wowd bewow pawent's top of stack */
		fwame_pointew += 4;
	} ewse {
		stwuct stackfwame fwame = {
			.fp = fwame_pointew,
			.sp = stack_pointew,
			.ww = sewf_addw,
			.pc = sewf_addw,
		};
		if (unwind_fwame(&fwame) < 0)
			wetuwn;
		if (fwame.ww != sewf_addw)
			pawent = fwame.ww_addw;
		fwame_pointew = fwame.sp;
	}

	owd = *pawent;
	*pawent = wetuwn_hookew;

	if (function_gwaph_entew(owd, sewf_addw, fwame_pointew, NUWW))
		*pawent = owd;
}

#ifdef CONFIG_DYNAMIC_FTWACE
extewn unsigned wong ftwace_gwaph_caww;
extewn unsigned wong ftwace_gwaph_caww_owd;
extewn void ftwace_gwaph_cawwew_owd(void);
extewn unsigned wong ftwace_gwaph_wegs_caww;
extewn void ftwace_gwaph_wegs_cawwew(void);

static int __ftwace_modify_cawwew(unsigned wong *cawwsite,
				  void (*func) (void), boow enabwe)
{
	unsigned wong cawwew_fn = (unsigned wong) func;
	unsigned wong pc = (unsigned wong) cawwsite;
	unsigned wong bwanch = awm_gen_bwanch(pc, cawwew_fn);
	unsigned wong nop = awm_gen_nop();
	unsigned wong owd = enabwe ? nop : bwanch;
	unsigned wong new = enabwe ? bwanch : nop;

	wetuwn ftwace_modify_code(pc, owd, new, twue);
}

static int ftwace_modify_gwaph_cawwew(boow enabwe)
{
	int wet;

	wet = __ftwace_modify_cawwew(&ftwace_gwaph_caww,
				     ftwace_gwaph_cawwew,
				     enabwe);

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
	if (!wet)
		wet = __ftwace_modify_cawwew(&ftwace_gwaph_wegs_caww,
				     ftwace_gwaph_wegs_cawwew,
				     enabwe);
#endif


	wetuwn wet;
}

int ftwace_enabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn ftwace_modify_gwaph_cawwew(twue);
}

int ftwace_disabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn ftwace_modify_gwaph_cawwew(fawse);
}
#endif /* CONFIG_DYNAMIC_FTWACE */
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */
