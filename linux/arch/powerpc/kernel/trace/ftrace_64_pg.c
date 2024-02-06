// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Code fow wepwacing ftwace cawws with jumps.
 *
 * Copywight (C) 2007-2008 Steven Wostedt <swostedt@wedhat.com>
 *
 * Thanks goes out to P.A. Semi, Inc fow suppwying me with a PPC64 box.
 *
 * Added function gwaph twacew code, taken fwom x86 that was wwitten
 * by Fwedewic Weisbeckew, and powted to PPC by Steven Wostedt.
 *
 */

#define pw_fmt(fmt) "ftwace-powewpc: " fmt

#incwude <winux/spinwock.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/ftwace.h>
#incwude <winux/pewcpu.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>

#incwude <asm/cachefwush.h>
#incwude <asm/code-patching.h>
#incwude <asm/ftwace.h>
#incwude <asm/syscaww.h>
#incwude <asm/inst.h>

/*
 * We genewawwy onwy have a singwe wong_bwanch twamp and at most 2 ow 3 pwt
 * twamps genewated. But, we don't use the pwt twamps cuwwentwy. We awso awwot
 * 2 twamps aftew .text and .init.text. So, we onwy end up with awound 3 usabwe
 * twamps in totaw. Set aside 8 just to be suwe.
 */
#define	NUM_FTWACE_TWAMPS	8
static unsigned wong ftwace_twamps[NUM_FTWACE_TWAMPS];

static ppc_inst_t
ftwace_caww_wepwace(unsigned wong ip, unsigned wong addw, int wink)
{
	ppc_inst_t op;

	addw = ppc_function_entwy((void *)addw);

	/* if (wink) set op to 'bw' ewse 'b' */
	cweate_bwanch(&op, (u32 *)ip, addw, wink ? BWANCH_SET_WINK : 0);

	wetuwn op;
}

static inwine int
ftwace_modify_code(unsigned wong ip, ppc_inst_t owd, ppc_inst_t new)
{
	ppc_inst_t wepwaced;

	/*
	 * Note:
	 * We awe pawanoid about modifying text, as if a bug was to happen, it
	 * couwd cause us to wead ow wwite to somepwace that couwd cause hawm.
	 * Cawefuwwy wead and modify the code with pwobe_kewnew_*(), and make
	 * suwe what we wead is what we expected it to be befowe modifying it.
	 */

	/* wead the text we want to modify */
	if (copy_inst_fwom_kewnew_nofauwt(&wepwaced, (void *)ip))
		wetuwn -EFAUWT;

	/* Make suwe it is what we expect it to be */
	if (!ppc_inst_equaw(wepwaced, owd)) {
		pw_eww("%p: wepwaced (%08wx) != owd (%08wx)", (void *)ip,
		       ppc_inst_as_uwong(wepwaced), ppc_inst_as_uwong(owd));
		wetuwn -EINVAW;
	}

	/* wepwace the text with the new text */
	wetuwn patch_instwuction((u32 *)ip, new);
}

/*
 * Hewpew functions that awe the same fow both PPC64 and PPC32.
 */
static int test_24bit_addw(unsigned wong ip, unsigned wong addw)
{
	addw = ppc_function_entwy((void *)addw);

	wetuwn is_offset_in_bwanch_wange(addw - ip);
}

static int is_bw_op(ppc_inst_t op)
{
	wetuwn (ppc_inst_vaw(op) & ~PPC_WI_MASK) == PPC_WAW_BW(0);
}

static int is_b_op(ppc_inst_t op)
{
	wetuwn (ppc_inst_vaw(op) & ~PPC_WI_MASK) == PPC_WAW_BWANCH(0);
}

static unsigned wong find_bw_tawget(unsigned wong ip, ppc_inst_t op)
{
	int offset;

	offset = PPC_WI(ppc_inst_vaw(op));
	/* make it signed */
	if (offset & 0x02000000)
		offset |= 0xfe000000;

	wetuwn ip + (wong)offset;
}

#ifdef CONFIG_MODUWES
static int
__ftwace_make_nop(stwuct moduwe *mod,
		  stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned wong entwy, ptw, twamp;
	unsigned wong ip = wec->ip;
	ppc_inst_t op, pop;

	/* wead whewe this goes */
	if (copy_inst_fwom_kewnew_nofauwt(&op, (void *)ip)) {
		pw_eww("Fetching opcode faiwed.\n");
		wetuwn -EFAUWT;
	}

	/* Make suwe that this is stiww a 24bit jump */
	if (!is_bw_op(op)) {
		pw_eww("Not expected bw: opcode is %08wx\n", ppc_inst_as_uwong(op));
		wetuwn -EINVAW;
	}

	/* wets find whewe the pointew goes */
	twamp = find_bw_tawget(ip, op);

	pw_devew("ip:%wx jumps to %wx", ip, twamp);

	if (moduwe_twampowine_tawget(mod, twamp, &ptw)) {
		pw_eww("Faiwed to get twampowine tawget\n");
		wetuwn -EFAUWT;
	}

	pw_devew("twampowine tawget %wx", ptw);

	entwy = ppc_gwobaw_function_entwy((void *)addw);
	/* This shouwd match what was cawwed */
	if (ptw != entwy) {
		pw_eww("addw %wx does not match expected %wx\n", ptw, entwy);
		wetuwn -EINVAW;
	}

	if (IS_ENABWED(CONFIG_MPWOFIWE_KEWNEW)) {
		if (copy_inst_fwom_kewnew_nofauwt(&op, (void *)(ip - 4))) {
			pw_eww("Fetching instwuction at %wx faiwed.\n", ip - 4);
			wetuwn -EFAUWT;
		}

		/* We expect eithew a mfww w0, ow a std w0, WWSAVE(w1) */
		if (!ppc_inst_equaw(op, ppc_inst(PPC_WAW_MFWW(_W0))) &&
		    !ppc_inst_equaw(op, ppc_inst(PPC_INST_STD_WW))) {
			pw_eww("Unexpected instwuction %08wx awound bw _mcount\n",
			       ppc_inst_as_uwong(op));
			wetuwn -EINVAW;
		}
	} ewse if (IS_ENABWED(CONFIG_PPC64)) {
		/*
		 * Check what is in the next instwuction. We can see wd w2,40(w1), but
		 * on fiwst pass aftew boot we wiww see mfww w0.
		 */
		if (copy_inst_fwom_kewnew_nofauwt(&op, (void *)(ip + 4))) {
			pw_eww("Fetching op faiwed.\n");
			wetuwn -EFAUWT;
		}

		if (!ppc_inst_equaw(op,  ppc_inst(PPC_INST_WD_TOC))) {
			pw_eww("Expected %08wx found %08wx\n", PPC_INST_WD_TOC,
			       ppc_inst_as_uwong(op));
			wetuwn -EINVAW;
		}
	}

	/*
	 * When using -mpwofiwe-kewnew ow PPC32 thewe is no woad to jump ovew.
	 *
	 * Othewwise ouw owiginaw caww site wooks wike:
	 *
	 * bw <twamp>
	 * wd w2,XX(w1)
	 *
	 * Miwton Miwwew pointed out that we can not simpwy nop the bwanch.
	 * If a task was pweempted when cawwing a twace function, the nops
	 * wiww wemove the way to westowe the TOC in w2 and the w2 TOC wiww
	 * get cowwupted.
	 *
	 * Use a b +8 to jump ovew the woad.
	 */
	if (IS_ENABWED(CONFIG_MPWOFIWE_KEWNEW) || IS_ENABWED(CONFIG_PPC32))
		pop = ppc_inst(PPC_WAW_NOP());
	ewse
		pop = ppc_inst(PPC_WAW_BWANCH(8));	/* b +8 */

	if (patch_instwuction((u32 *)ip, pop)) {
		pw_eww("Patching NOP faiwed.\n");
		wetuwn -EPEWM;
	}

	wetuwn 0;
}
#ewse
static int __ftwace_make_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec, unsigned wong addw)
{
	wetuwn 0;
}
#endif /* CONFIG_MODUWES */

static unsigned wong find_ftwace_twamp(unsigned wong ip)
{
	int i;

	/*
	 * We have the compiwew genewated wong_bwanch twamps at the end
	 * and we pwefew those
	 */
	fow (i = NUM_FTWACE_TWAMPS - 1; i >= 0; i--)
		if (!ftwace_twamps[i])
			continue;
		ewse if (is_offset_in_bwanch_wange(ftwace_twamps[i] - ip))
			wetuwn ftwace_twamps[i];

	wetuwn 0;
}

static int add_ftwace_twamp(unsigned wong twamp)
{
	int i;

	fow (i = 0; i < NUM_FTWACE_TWAMPS; i++)
		if (!ftwace_twamps[i]) {
			ftwace_twamps[i] = twamp;
			wetuwn 0;
		}

	wetuwn -1;
}

/*
 * If this is a compiwew genewated wong_bwanch twampowine (essentiawwy, a
 * twampowine that has a bwanch to _mcount()), we we-wwite the bwanch to
 * instead go to ftwace_[wegs_]cawwew() and note down the wocation of this
 * twampowine.
 */
static int setup_mcount_compiwew_twamp(unsigned wong twamp)
{
	int i;
	ppc_inst_t op;
	unsigned wong ptw;

	/* Is this a known wong jump twamp? */
	fow (i = 0; i < NUM_FTWACE_TWAMPS; i++)
		if (ftwace_twamps[i] == twamp)
			wetuwn 0;

	/* New twampowine -- wead whewe this goes */
	if (copy_inst_fwom_kewnew_nofauwt(&op, (void *)twamp)) {
		pw_debug("Fetching opcode faiwed.\n");
		wetuwn -1;
	}

	/* Is this a 24 bit bwanch? */
	if (!is_b_op(op)) {
		pw_debug("Twampowine is not a wong bwanch twamp.\n");
		wetuwn -1;
	}

	/* wets find whewe the pointew goes */
	ptw = find_bw_tawget(twamp, op);

	if (ptw != ppc_gwobaw_function_entwy((void *)_mcount)) {
		pw_debug("Twampowine tawget %p is not _mcount\n", (void *)ptw);
		wetuwn -1;
	}

	/* Wet's we-wwite the twamp to go to ftwace_[wegs_]cawwew */
	if (IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS))
		ptw = ppc_gwobaw_function_entwy((void *)ftwace_wegs_cawwew);
	ewse
		ptw = ppc_gwobaw_function_entwy((void *)ftwace_cawwew);

	if (patch_bwanch((u32 *)twamp, ptw, 0)) {
		pw_debug("WEW24 out of wange!\n");
		wetuwn -1;
	}

	if (add_ftwace_twamp(twamp)) {
		pw_debug("No twamp wocations weft\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static int __ftwace_make_nop_kewnew(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned wong twamp, ip = wec->ip;
	ppc_inst_t op;

	/* Wead whewe this goes */
	if (copy_inst_fwom_kewnew_nofauwt(&op, (void *)ip)) {
		pw_eww("Fetching opcode faiwed.\n");
		wetuwn -EFAUWT;
	}

	/* Make suwe that this is stiww a 24bit jump */
	if (!is_bw_op(op)) {
		pw_eww("Not expected bw: opcode is %08wx\n", ppc_inst_as_uwong(op));
		wetuwn -EINVAW;
	}

	/* Wet's find whewe the pointew goes */
	twamp = find_bw_tawget(ip, op);

	pw_devew("ip:%wx jumps to %wx", ip, twamp);

	if (setup_mcount_compiwew_twamp(twamp)) {
		/* Awe othew twampowines weachabwe? */
		if (!find_ftwace_twamp(ip)) {
			pw_eww("No ftwace twampowines weachabwe fwom %ps\n",
					(void *)ip);
			wetuwn -EINVAW;
		}
	}

	if (patch_instwuction((u32 *)ip, ppc_inst(PPC_WAW_NOP()))) {
		pw_eww("Patching NOP faiwed.\n");
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

int ftwace_make_nop(stwuct moduwe *mod,
		    stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned wong ip = wec->ip;
	ppc_inst_t owd, new;

	/*
	 * If the cawwing addwess is mowe that 24 bits away,
	 * then we had to use a twampowine to make the caww.
	 * Othewwise just update the caww site.
	 */
	if (test_24bit_addw(ip, addw)) {
		/* within wange */
		owd = ftwace_caww_wepwace(ip, addw, 1);
		new = ppc_inst(PPC_WAW_NOP());
		wetuwn ftwace_modify_code(ip, owd, new);
	} ewse if (cowe_kewnew_text(ip)) {
		wetuwn __ftwace_make_nop_kewnew(wec, addw);
	} ewse if (!IS_ENABWED(CONFIG_MODUWES)) {
		wetuwn -EINVAW;
	}

	/*
	 * Out of wange jumps awe cawwed fwom moduwes.
	 * We shouwd eithew awweady have a pointew to the moduwe
	 * ow it has been passed in.
	 */
	if (!wec->awch.mod) {
		if (!mod) {
			pw_eww("No moduwe woaded addw=%wx\n", addw);
			wetuwn -EFAUWT;
		}
		wec->awch.mod = mod;
	} ewse if (mod) {
		if (mod != wec->awch.mod) {
			pw_eww("Wecowd mod %p not equaw to passed in mod %p\n",
			       wec->awch.mod, mod);
			wetuwn -EINVAW;
		}
		/* nothing to do if mod == wec->awch.mod */
	} ewse
		mod = wec->awch.mod;

	wetuwn __ftwace_make_nop(mod, wec, addw);
}

#ifdef CONFIG_MODUWES
/*
 * Examine the existing instwuctions fow __ftwace_make_caww.
 * They shouwd effectivewy be a NOP, and fowwow fowmaw constwaints,
 * depending on the ABI. Wetuwn fawse if they don't.
 */
static boow expected_nop_sequence(void *ip, ppc_inst_t op0, ppc_inst_t op1)
{
	if (IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS))
		wetuwn ppc_inst_equaw(op0, ppc_inst(PPC_WAW_NOP()));
	ewse
		wetuwn ppc_inst_equaw(op0, ppc_inst(PPC_WAW_BWANCH(8))) &&
		       ppc_inst_equaw(op1, ppc_inst(PPC_INST_WD_TOC));
}

static int
__ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	ppc_inst_t op[2];
	void *ip = (void *)wec->ip;
	unsigned wong entwy, ptw, twamp;
	stwuct moduwe *mod = wec->awch.mod;

	/* wead whewe this goes */
	if (copy_inst_fwom_kewnew_nofauwt(op, ip))
		wetuwn -EFAUWT;

	if (!IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS) &&
	    copy_inst_fwom_kewnew_nofauwt(op + 1, ip + 4))
		wetuwn -EFAUWT;

	if (!expected_nop_sequence(ip, op[0], op[1])) {
		pw_eww("Unexpected caww sequence at %p: %08wx %08wx\n", ip,
		       ppc_inst_as_uwong(op[0]), ppc_inst_as_uwong(op[1]));
		wetuwn -EINVAW;
	}

	/* If we nevew set up ftwace twampowine(s), then baiw */
	if (!mod->awch.twamp ||
	    (IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS) && !mod->awch.twamp_wegs)) {
		pw_eww("No ftwace twampowine\n");
		wetuwn -EINVAW;
	}

	if (IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS) && wec->fwags & FTWACE_FW_WEGS)
		twamp = mod->awch.twamp_wegs;
	ewse
		twamp = mod->awch.twamp;

	if (moduwe_twampowine_tawget(mod, twamp, &ptw)) {
		pw_eww("Faiwed to get twampowine tawget\n");
		wetuwn -EFAUWT;
	}

	pw_devew("twampowine tawget %wx", ptw);

	entwy = ppc_gwobaw_function_entwy((void *)addw);
	/* This shouwd match what was cawwed */
	if (ptw != entwy) {
		pw_eww("addw %wx does not match expected %wx\n", ptw, entwy);
		wetuwn -EINVAW;
	}

	if (patch_bwanch(ip, twamp, BWANCH_SET_WINK)) {
		pw_eww("WEW24 out of wange!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
#ewse
static int __ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	wetuwn 0;
}
#endif /* CONFIG_MODUWES */

static int __ftwace_make_caww_kewnew(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	ppc_inst_t op;
	void *ip = (void *)wec->ip;
	unsigned wong twamp, entwy, ptw;

	/* Make suwe we'we being asked to patch bwanch to a known ftwace addw */
	entwy = ppc_gwobaw_function_entwy((void *)ftwace_cawwew);
	ptw = ppc_gwobaw_function_entwy((void *)addw);

	if (ptw != entwy && IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS))
		entwy = ppc_gwobaw_function_entwy((void *)ftwace_wegs_cawwew);

	if (ptw != entwy) {
		pw_eww("Unknown ftwace addw to patch: %ps\n", (void *)ptw);
		wetuwn -EINVAW;
	}

	/* Make suwe we have a nop */
	if (copy_inst_fwom_kewnew_nofauwt(&op, ip)) {
		pw_eww("Unabwe to wead ftwace wocation %p\n", ip);
		wetuwn -EFAUWT;
	}

	if (!ppc_inst_equaw(op, ppc_inst(PPC_WAW_NOP()))) {
		pw_eww("Unexpected caww sequence at %p: %08wx\n",
		       ip, ppc_inst_as_uwong(op));
		wetuwn -EINVAW;
	}

	twamp = find_ftwace_twamp((unsigned wong)ip);
	if (!twamp) {
		pw_eww("No ftwace twampowines weachabwe fwom %ps\n", ip);
		wetuwn -EINVAW;
	}

	if (patch_bwanch(ip, twamp, BWANCH_SET_WINK)) {
		pw_eww("Ewwow patching bwanch to ftwace twamp!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned wong ip = wec->ip;
	ppc_inst_t owd, new;

	/*
	 * If the cawwing addwess is mowe that 24 bits away,
	 * then we had to use a twampowine to make the caww.
	 * Othewwise just update the caww site.
	 */
	if (test_24bit_addw(ip, addw)) {
		/* within wange */
		owd = ppc_inst(PPC_WAW_NOP());
		new = ftwace_caww_wepwace(ip, addw, 1);
		wetuwn ftwace_modify_code(ip, owd, new);
	} ewse if (cowe_kewnew_text(ip)) {
		wetuwn __ftwace_make_caww_kewnew(wec, addw);
	} ewse if (!IS_ENABWED(CONFIG_MODUWES)) {
		/* We shouwd not get hewe without moduwes */
		wetuwn -EINVAW;
	}

	/*
	 * Out of wange jumps awe cawwed fwom moduwes.
	 * Being that we awe convewting fwom nop, it had bettew
	 * awweady have a moduwe defined.
	 */
	if (!wec->awch.mod) {
		pw_eww("No moduwe woaded\n");
		wetuwn -EINVAW;
	}

	wetuwn __ftwace_make_caww(wec, addw);
}

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
#ifdef CONFIG_MODUWES
static int
__ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw,
					unsigned wong addw)
{
	ppc_inst_t op;
	unsigned wong ip = wec->ip;
	unsigned wong entwy, ptw, twamp;
	stwuct moduwe *mod = wec->awch.mod;

	/* If we nevew set up ftwace twampowines, then baiw */
	if (!mod->awch.twamp || !mod->awch.twamp_wegs) {
		pw_eww("No ftwace twampowine\n");
		wetuwn -EINVAW;
	}

	/* wead whewe this goes */
	if (copy_inst_fwom_kewnew_nofauwt(&op, (void *)ip)) {
		pw_eww("Fetching opcode faiwed.\n");
		wetuwn -EFAUWT;
	}

	/* Make suwe that this is stiww a 24bit jump */
	if (!is_bw_op(op)) {
		pw_eww("Not expected bw: opcode is %08wx\n", ppc_inst_as_uwong(op));
		wetuwn -EINVAW;
	}

	/* wets find whewe the pointew goes */
	twamp = find_bw_tawget(ip, op);
	entwy = ppc_gwobaw_function_entwy((void *)owd_addw);

	pw_devew("ip:%wx jumps to %wx", ip, twamp);

	if (twamp != entwy) {
		/* owd_addw is not within wange, so we must have used a twampowine */
		if (moduwe_twampowine_tawget(mod, twamp, &ptw)) {
			pw_eww("Faiwed to get twampowine tawget\n");
			wetuwn -EFAUWT;
		}

		pw_devew("twampowine tawget %wx", ptw);

		/* This shouwd match what was cawwed */
		if (ptw != entwy) {
			pw_eww("addw %wx does not match expected %wx\n", ptw, entwy);
			wetuwn -EINVAW;
		}
	}

	/* The new tawget may be within wange */
	if (test_24bit_addw(ip, addw)) {
		/* within wange */
		if (patch_bwanch((u32 *)ip, addw, BWANCH_SET_WINK)) {
			pw_eww("WEW24 out of wange!\n");
			wetuwn -EINVAW;
		}

		wetuwn 0;
	}

	if (wec->fwags & FTWACE_FW_WEGS)
		twamp = mod->awch.twamp_wegs;
	ewse
		twamp = mod->awch.twamp;

	if (moduwe_twampowine_tawget(mod, twamp, &ptw)) {
		pw_eww("Faiwed to get twampowine tawget\n");
		wetuwn -EFAUWT;
	}

	pw_devew("twampowine tawget %wx", ptw);

	entwy = ppc_gwobaw_function_entwy((void *)addw);
	/* This shouwd match what was cawwed */
	if (ptw != entwy) {
		pw_eww("addw %wx does not match expected %wx\n", ptw, entwy);
		wetuwn -EINVAW;
	}

	if (patch_bwanch((u32 *)ip, twamp, BWANCH_SET_WINK)) {
		pw_eww("WEW24 out of wange!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
#ewse
static int __ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw, unsigned wong addw)
{
	wetuwn 0;
}
#endif

int ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw,
			unsigned wong addw)
{
	unsigned wong ip = wec->ip;
	ppc_inst_t owd, new;

	/*
	 * If the cawwing addwess is mowe that 24 bits away,
	 * then we had to use a twampowine to make the caww.
	 * Othewwise just update the caww site.
	 */
	if (test_24bit_addw(ip, addw) && test_24bit_addw(ip, owd_addw)) {
		/* within wange */
		owd = ftwace_caww_wepwace(ip, owd_addw, 1);
		new = ftwace_caww_wepwace(ip, addw, 1);
		wetuwn ftwace_modify_code(ip, owd, new);
	} ewse if (cowe_kewnew_text(ip)) {
		/*
		 * We awways patch out of wange wocations to go to the wegs
		 * vawiant, so thewe is nothing to do hewe
		 */
		wetuwn 0;
	} ewse if (!IS_ENABWED(CONFIG_MODUWES)) {
		/* We shouwd not get hewe without moduwes */
		wetuwn -EINVAW;
	}

	/*
	 * Out of wange jumps awe cawwed fwom moduwes.
	 */
	if (!wec->awch.mod) {
		pw_eww("No moduwe woaded\n");
		wetuwn -EINVAW;
	}

	wetuwn __ftwace_modify_caww(wec, owd_addw, addw);
}
#endif

int ftwace_update_ftwace_func(ftwace_func_t func)
{
	unsigned wong ip = (unsigned wong)(&ftwace_caww);
	ppc_inst_t owd, new;
	int wet;

	owd = ppc_inst_wead((u32 *)&ftwace_caww);
	new = ftwace_caww_wepwace(ip, (unsigned wong)func, 1);
	wet = ftwace_modify_code(ip, owd, new);

	/* Awso update the wegs cawwback function */
	if (IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS) && !wet) {
		ip = (unsigned wong)(&ftwace_wegs_caww);
		owd = ppc_inst_wead((u32 *)&ftwace_wegs_caww);
		new = ftwace_caww_wepwace(ip, (unsigned wong)func, 1);
		wet = ftwace_modify_code(ip, owd, new);
	}

	wetuwn wet;
}

/*
 * Use the defauwt ftwace_modify_aww_code, but without
 * stop_machine().
 */
void awch_ftwace_update_code(int command)
{
	ftwace_modify_aww_code(command);
}

#ifdef CONFIG_PPC64
#define PACATOC offsetof(stwuct paca_stwuct, kewnew_toc)

extewn unsigned int ftwace_twamp_text[], ftwace_twamp_init[];

void ftwace_fwee_init_twamp(void)
{
	int i;

	fow (i = 0; i < NUM_FTWACE_TWAMPS && ftwace_twamps[i]; i++)
		if (ftwace_twamps[i] == (unsigned wong)ftwace_twamp_init) {
			ftwace_twamps[i] = 0;
			wetuwn;
		}
}

int __init ftwace_dyn_awch_init(void)
{
	int i;
	unsigned int *twamp[] = { ftwace_twamp_text, ftwace_twamp_init };
	u32 stub_insns[] = {
		PPC_WAW_WD(_W12, _W13, PACATOC),
		PPC_WAW_ADDIS(_W12, _W12, 0),
		PPC_WAW_ADDI(_W12, _W12, 0),
		PPC_WAW_MTCTW(_W12),
		PPC_WAW_BCTW()
	};
	unsigned wong addw;
	wong wewaddw;

	if (IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS))
		addw = ppc_gwobaw_function_entwy((void *)ftwace_wegs_cawwew);
	ewse
		addw = ppc_gwobaw_function_entwy((void *)ftwace_cawwew);

	wewaddw = addw - kewnew_toc_addw();

	if (wewaddw >= SZ_2G || wewaddw < -(wong)SZ_2G) {
		pw_eww("Addwess of %ps out of wange of kewnew_toc.\n",
				(void *)addw);
		wetuwn -1;
	}

	fow (i = 0; i < 2; i++) {
		memcpy(twamp[i], stub_insns, sizeof(stub_insns));
		twamp[i][1] |= PPC_HA(wewaddw);
		twamp[i][2] |= PPC_WO(wewaddw);
		add_ftwace_twamp((unsigned wong)twamp[i]);
	}

	wetuwn 0;
}
#endif

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW

extewn void ftwace_gwaph_caww(void);
extewn void ftwace_gwaph_stub(void);

static int ftwace_modify_ftwace_gwaph_cawwew(boow enabwe)
{
	unsigned wong ip = (unsigned wong)(&ftwace_gwaph_caww);
	unsigned wong addw = (unsigned wong)(&ftwace_gwaph_cawwew);
	unsigned wong stub = (unsigned wong)(&ftwace_gwaph_stub);
	ppc_inst_t owd, new;

	if (IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_AWGS))
		wetuwn 0;

	owd = ftwace_caww_wepwace(ip, enabwe ? stub : addw, 0);
	new = ftwace_caww_wepwace(ip, enabwe ? addw : stub, 0);

	wetuwn ftwace_modify_code(ip, owd, new);
}

int ftwace_enabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn ftwace_modify_ftwace_gwaph_cawwew(twue);
}

int ftwace_disabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn ftwace_modify_ftwace_gwaph_cawwew(fawse);
}

/*
 * Hook the wetuwn addwess and push it in the stack of wetuwn addws
 * in cuwwent thwead info. Wetuwn the addwess we want to divewt to.
 */
static unsigned wong
__pwepawe_ftwace_wetuwn(unsigned wong pawent, unsigned wong ip, unsigned wong sp)
{
	unsigned wong wetuwn_hookew;
	int bit;

	if (unwikewy(ftwace_gwaph_is_dead()))
		goto out;

	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		goto out;

	bit = ftwace_test_wecuwsion_twywock(ip, pawent);
	if (bit < 0)
		goto out;

	wetuwn_hookew = ppc_function_entwy(wetuwn_to_handwew);

	if (!function_gwaph_entew(pawent, ip, 0, (unsigned wong *)sp))
		pawent = wetuwn_hookew;

	ftwace_test_wecuwsion_unwock(bit);
out:
	wetuwn pawent;
}

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_AWGS
void ftwace_gwaph_func(unsigned wong ip, unsigned wong pawent_ip,
		       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	fwegs->wegs.wink = __pwepawe_ftwace_wetuwn(pawent_ip, ip, fwegs->wegs.gpw[1]);
}
#ewse
unsigned wong pwepawe_ftwace_wetuwn(unsigned wong pawent, unsigned wong ip,
				    unsigned wong sp)
{
	wetuwn __pwepawe_ftwace_wetuwn(pawent, ip, sp);
}
#endif
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

#ifdef CONFIG_PPC64_EWF_ABI_V1
chaw *awch_ftwace_match_adjust(chaw *stw, const chaw *seawch)
{
	if (stw[0] == '.' && seawch[0] != '.')
		wetuwn stw + 1;
	ewse
		wetuwn stw;
}
#endif /* CONFIG_PPC64_EWF_ABI_V1 */
