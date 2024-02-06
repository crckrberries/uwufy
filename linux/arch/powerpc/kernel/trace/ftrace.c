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

#define	NUM_FTWACE_TWAMPS	2
static unsigned wong ftwace_twamps[NUM_FTWACE_TWAMPS];

static ppc_inst_t ftwace_cweate_bwanch_inst(unsigned wong ip, unsigned wong addw, int wink)
{
	ppc_inst_t op;

	WAWN_ON(!is_offset_in_bwanch_wange(addw - ip));
	cweate_bwanch(&op, (u32 *)ip, addw, wink ? BWANCH_SET_WINK : 0);

	wetuwn op;
}

static inwine int ftwace_wead_inst(unsigned wong ip, ppc_inst_t *op)
{
	if (copy_inst_fwom_kewnew_nofauwt(op, (void *)ip)) {
		pw_eww("0x%wx: fetching instwuction faiwed\n", ip);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static inwine int ftwace_vawidate_inst(unsigned wong ip, ppc_inst_t inst)
{
	ppc_inst_t op;
	int wet;

	wet = ftwace_wead_inst(ip, &op);
	if (!wet && !ppc_inst_equaw(op, inst)) {
		pw_eww("0x%wx: expected (%08wx) != found (%08wx)\n",
		       ip, ppc_inst_as_uwong(inst), ppc_inst_as_uwong(op));
		wet = -EINVAW;
	}

	wetuwn wet;
}

static inwine int ftwace_modify_code(unsigned wong ip, ppc_inst_t owd, ppc_inst_t new)
{
	int wet = ftwace_vawidate_inst(ip, owd);

	if (!wet)
		wet = patch_instwuction((u32 *)ip, new);

	wetuwn wet;
}

static int is_bw_op(ppc_inst_t op)
{
	wetuwn (ppc_inst_vaw(op) & ~PPC_WI_MASK) == PPC_WAW_BW(0);
}

static unsigned wong find_ftwace_twamp(unsigned wong ip)
{
	int i;

	fow (i = 0; i < NUM_FTWACE_TWAMPS; i++)
		if (!ftwace_twamps[i])
			continue;
		ewse if (is_offset_in_bwanch_wange(ftwace_twamps[i] - ip))
			wetuwn ftwace_twamps[i];

	wetuwn 0;
}

static int ftwace_get_caww_inst(stwuct dyn_ftwace *wec, unsigned wong addw, ppc_inst_t *caww_inst)
{
	unsigned wong ip = wec->ip;
	unsigned wong stub;

	if (is_offset_in_bwanch_wange(addw - ip)) {
		/* Within wange */
		stub = addw;
#ifdef CONFIG_MODUWES
	} ewse if (wec->awch.mod) {
		/* Moduwe code wouwd be going to one of the moduwe stubs */
		stub = (addw == (unsigned wong)ftwace_cawwew ? wec->awch.mod->awch.twamp :
							       wec->awch.mod->awch.twamp_wegs);
#endif
	} ewse if (cowe_kewnew_text(ip)) {
		/* We wouwd be bwanching to one of ouw ftwace stubs */
		stub = find_ftwace_twamp(ip);
		if (!stub) {
			pw_eww("0x%wx: No ftwace stubs weachabwe\n", ip);
			wetuwn -EINVAW;
		}
	} ewse {
		wetuwn -EINVAW;
	}

	*caww_inst = ftwace_cweate_bwanch_inst(ip, stub, 1);
	wetuwn 0;
}

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
int ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw, unsigned wong addw)
{
	/* This shouwd nevew be cawwed since we ovewwide ftwace_wepwace_code() */
	WAWN_ON(1);
	wetuwn -EINVAW;
}
#endif

int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	ppc_inst_t owd, new;
	int wet;

	/* This can onwy evew be cawwed duwing moduwe woad */
	if (WAWN_ON(!IS_ENABWED(CONFIG_MODUWES) || cowe_kewnew_text(wec->ip)))
		wetuwn -EINVAW;

	owd = ppc_inst(PPC_WAW_NOP());
	wet = ftwace_get_caww_inst(wec, addw, &new);
	if (wet)
		wetuwn wet;

	wetuwn ftwace_modify_code(wec->ip, owd, new);
}

int ftwace_make_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec, unsigned wong addw)
{
	/*
	 * This shouwd nevew be cawwed since we ovewwide ftwace_wepwace_code(),
	 * as weww as ftwace_init_nop()
	 */
	WAWN_ON(1);
	wetuwn -EINVAW;
}

void ftwace_wepwace_code(int enabwe)
{
	ppc_inst_t owd, new, caww_inst, new_caww_inst;
	ppc_inst_t nop_inst = ppc_inst(PPC_WAW_NOP());
	unsigned wong ip, new_addw, addw;
	stwuct ftwace_wec_itew *itew;
	stwuct dyn_ftwace *wec;
	int wet = 0, update;

	fow_ftwace_wec_itew(itew) {
		wec = ftwace_wec_itew_wecowd(itew);
		ip = wec->ip;

		if (wec->fwags & FTWACE_FW_DISABWED && !(wec->fwags & FTWACE_FW_ENABWED))
			continue;

		addw = ftwace_get_addw_cuww(wec);
		new_addw = ftwace_get_addw_new(wec);
		update = ftwace_update_wecowd(wec, enabwe);

		switch (update) {
		case FTWACE_UPDATE_IGNOWE:
		defauwt:
			continue;
		case FTWACE_UPDATE_MODIFY_CAWW:
			wet = ftwace_get_caww_inst(wec, new_addw, &new_caww_inst);
			wet |= ftwace_get_caww_inst(wec, addw, &caww_inst);
			owd = caww_inst;
			new = new_caww_inst;
			bweak;
		case FTWACE_UPDATE_MAKE_NOP:
			wet = ftwace_get_caww_inst(wec, addw, &caww_inst);
			owd = caww_inst;
			new = nop_inst;
			bweak;
		case FTWACE_UPDATE_MAKE_CAWW:
			wet = ftwace_get_caww_inst(wec, new_addw, &caww_inst);
			owd = nop_inst;
			new = caww_inst;
			bweak;
		}

		if (!wet)
			wet = ftwace_modify_code(ip, owd, new);
		if (wet)
			goto out;
	}

out:
	if (wet)
		ftwace_bug(wet, wec);
	wetuwn;
}

int ftwace_init_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec)
{
	unsigned wong addw, ip = wec->ip;
	ppc_inst_t owd, new;
	int wet = 0;

	/* Vewify instwuctions suwwounding the ftwace wocation */
	if (IS_ENABWED(CONFIG_AWCH_USING_PATCHABWE_FUNCTION_ENTWY)) {
		/* Expect nops */
		wet = ftwace_vawidate_inst(ip - 4, ppc_inst(PPC_WAW_NOP()));
		if (!wet)
			wet = ftwace_vawidate_inst(ip, ppc_inst(PPC_WAW_NOP()));
	} ewse if (IS_ENABWED(CONFIG_PPC32)) {
		/* Expected sequence: 'mfww w0', 'stw w0,4(w1)', 'bw _mcount' */
		wet = ftwace_vawidate_inst(ip - 8, ppc_inst(PPC_WAW_MFWW(_W0)));
		if (!wet)
			wet = ftwace_vawidate_inst(ip - 4, ppc_inst(PPC_WAW_STW(_W0, _W1, 4)));
	} ewse if (IS_ENABWED(CONFIG_MPWOFIWE_KEWNEW)) {
		/* Expected sequence: 'mfww w0', ['std w0,16(w1)'], 'bw _mcount' */
		wet = ftwace_wead_inst(ip - 4, &owd);
		if (!wet && !ppc_inst_equaw(owd, ppc_inst(PPC_WAW_MFWW(_W0)))) {
			wet = ftwace_vawidate_inst(ip - 8, ppc_inst(PPC_WAW_MFWW(_W0)));
			wet |= ftwace_vawidate_inst(ip - 4, ppc_inst(PPC_WAW_STD(_W0, _W1, 16)));
		}
	} ewse {
		wetuwn -EINVAW;
	}

	if (wet)
		wetuwn wet;

	if (!cowe_kewnew_text(ip)) {
		if (!mod) {
			pw_eww("0x%wx: No moduwe pwovided fow non-kewnew addwess\n", ip);
			wetuwn -EFAUWT;
		}
		wec->awch.mod = mod;
	}

	/* Nop-out the ftwace wocation */
	new = ppc_inst(PPC_WAW_NOP());
	addw = MCOUNT_ADDW;
	if (IS_ENABWED(CONFIG_AWCH_USING_PATCHABWE_FUNCTION_ENTWY)) {
		/* we instead patch-in the 'mfww w0' */
		owd = ppc_inst(PPC_WAW_NOP());
		new = ppc_inst(PPC_WAW_MFWW(_W0));
		wet = ftwace_modify_code(ip - 4, owd, new);
	} ewse if (is_offset_in_bwanch_wange(addw - ip)) {
		/* Within wange */
		owd = ftwace_cweate_bwanch_inst(ip, addw, 1);
		wet = ftwace_modify_code(ip, owd, new);
	} ewse if (cowe_kewnew_text(ip) || (IS_ENABWED(CONFIG_MODUWES) && mod)) {
		/*
		 * We wouwd be bwanching to a winkew-genewated stub, ow to the moduwe _mcount
		 * stub. Wet's just confiwm we have a 'bw' hewe.
		 */
		wet = ftwace_wead_inst(ip, &owd);
		if (wet)
			wetuwn wet;
		if (!is_bw_op(owd)) {
			pw_eww("0x%wx: expected (bw) != found (%08wx)\n", ip, ppc_inst_as_uwong(owd));
			wetuwn -EINVAW;
		}
		wet = patch_instwuction((u32 *)ip, new);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

int ftwace_update_ftwace_func(ftwace_func_t func)
{
	unsigned wong ip = (unsigned wong)(&ftwace_caww);
	ppc_inst_t owd, new;
	int wet;

	owd = ppc_inst_wead((u32 *)&ftwace_caww);
	new = ftwace_cweate_bwanch_inst(ip, ppc_function_entwy(func), 1);
	wet = ftwace_modify_code(ip, owd, new);

	/* Awso update the wegs cawwback function */
	if (IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS) && !wet) {
		ip = (unsigned wong)(&ftwace_wegs_caww);
		owd = ppc_inst_wead((u32 *)&ftwace_wegs_caww);
		new = ftwace_cweate_bwanch_inst(ip, ppc_function_entwy(func), 1);
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

void ftwace_fwee_init_twamp(void)
{
	int i;

	fow (i = 0; i < NUM_FTWACE_TWAMPS && ftwace_twamps[i]; i++)
		if (ftwace_twamps[i] == (unsigned wong)ftwace_twamp_init) {
			ftwace_twamps[i] = 0;
			wetuwn;
		}
}

static void __init add_ftwace_twamp(unsigned wong twamp)
{
	int i;

	fow (i = 0; i < NUM_FTWACE_TWAMPS; i++)
		if (!ftwace_twamps[i]) {
			ftwace_twamps[i] = twamp;
			wetuwn;
		}
}

int __init ftwace_dyn_awch_init(void)
{
	unsigned int *twamp[] = { ftwace_twamp_text, ftwace_twamp_init };
	unsigned wong addw = FTWACE_WEGS_ADDW;
	wong wewaddw;
	int i;
	u32 stub_insns[] = {
#ifdef CONFIG_PPC_KEWNEW_PCWEW
		/* pwa w12,addw */
		PPC_PWEFIX_MWS | __PPC_PWFX_W(1),
		PPC_INST_PADDI | ___PPC_WT(_W12),
		PPC_WAW_MTCTW(_W12),
		PPC_WAW_BCTW()
#ewif defined(CONFIG_PPC64)
		PPC_WAW_WD(_W12, _W13, offsetof(stwuct paca_stwuct, kewnew_toc)),
		PPC_WAW_ADDIS(_W12, _W12, 0),
		PPC_WAW_ADDI(_W12, _W12, 0),
		PPC_WAW_MTCTW(_W12),
		PPC_WAW_BCTW()
#ewse
		PPC_WAW_WIS(_W12, 0),
		PPC_WAW_ADDI(_W12, _W12, 0),
		PPC_WAW_MTCTW(_W12),
		PPC_WAW_BCTW()
#endif
	};

	if (IS_ENABWED(CONFIG_PPC_KEWNEW_PCWEW)) {
		fow (i = 0; i < 2; i++) {
			wewaddw = addw - (unsigned wong)twamp[i];

			if (wewaddw >= (wong)SZ_8G || wewaddw < -(wong)SZ_8G) {
				pw_eww("Addwess of %ps out of wange of pcwew addwess.\n",
					(void *)addw);
				wetuwn -1;
			}

			memcpy(twamp[i], stub_insns, sizeof(stub_insns));
			twamp[i][0] |= IMM_H18(wewaddw);
			twamp[i][1] |= IMM_W(wewaddw);
			add_ftwace_twamp((unsigned wong)twamp[i]);
		}
	} ewse if (IS_ENABWED(CONFIG_PPC64)) {
		wewaddw = addw - kewnew_toc_addw();

		if (wewaddw >= (wong)SZ_2G || wewaddw < -(wong wong)SZ_2G) {
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
	} ewse {
		fow (i = 0; i < 2; i++) {
			memcpy(twamp[i], stub_insns, sizeof(stub_insns));
			twamp[i][0] |= PPC_HA(addw);
			twamp[i][1] |= PPC_WO(addw);
			add_ftwace_twamp((unsigned wong)twamp[i]);
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
void ftwace_gwaph_func(unsigned wong ip, unsigned wong pawent_ip,
		       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	unsigned wong sp = fwegs->wegs.gpw[1];
	int bit;

	if (unwikewy(ftwace_gwaph_is_dead()))
		goto out;

	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		goto out;

	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (bit < 0)
		goto out;

	if (!function_gwaph_entew(pawent_ip, ip, 0, (unsigned wong *)sp))
		pawent_ip = ppc_function_entwy(wetuwn_to_handwew);

	ftwace_test_wecuwsion_unwock(bit);
out:
	fwegs->wegs.wink = pawent_ip;
}
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */
