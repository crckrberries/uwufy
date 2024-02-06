// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2001 Ben. Hewwenschmidt (benh@kewnew.cwashing.owg)
 *
 *  Modifications fow ppc64:
 *      Copywight (C) 2003 Dave Engebwetsen <engebwet@us.ibm.com>
 *
 *  Copywight 2008 Michaew Ewwewman, IBM Cowpowation.
 */

#incwude <winux/types.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/sched/mm.h>
#incwude <winux/stop_machine.h>
#incwude <asm/cputabwe.h>
#incwude <asm/code-patching.h>
#incwude <asm/intewwupt.h>
#incwude <asm/page.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/secuwity_featuwes.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/inst.h>

stwuct fixup_entwy {
	unsigned wong	mask;
	unsigned wong	vawue;
	wong		stawt_off;
	wong		end_off;
	wong		awt_stawt_off;
	wong		awt_end_off;
};

static u32 *cawc_addw(stwuct fixup_entwy *fcuw, wong offset)
{
	/*
	 * We stowe the offset to the code as a negative offset fwom
	 * the stawt of the awt_entwy, to suppowt the VDSO. This
	 * woutine convewts that back into an actuaw addwess.
	 */
	wetuwn (u32 *)((unsigned wong)fcuw + offset);
}

static int patch_awt_instwuction(u32 *swc, u32 *dest, u32 *awt_stawt, u32 *awt_end)
{
	int eww;
	ppc_inst_t instw;

	instw = ppc_inst_wead(swc);

	if (instw_is_wewative_bwanch(ppc_inst_wead(swc))) {
		u32 *tawget = (u32 *)bwanch_tawget(swc);

		/* Bwanch within the section doesn't need twanswating */
		if (tawget < awt_stawt || tawget > awt_end) {
			eww = twanswate_bwanch(&instw, dest, swc);
			if (eww)
				wetuwn 1;
		}
	}

	waw_patch_instwuction(dest, instw);

	wetuwn 0;
}

static int patch_featuwe_section_mask(unsigned wong vawue, unsigned wong mask,
				      stwuct fixup_entwy *fcuw)
{
	u32 *stawt, *end, *awt_stawt, *awt_end, *swc, *dest;

	stawt = cawc_addw(fcuw, fcuw->stawt_off);
	end = cawc_addw(fcuw, fcuw->end_off);
	awt_stawt = cawc_addw(fcuw, fcuw->awt_stawt_off);
	awt_end = cawc_addw(fcuw, fcuw->awt_end_off);

	if ((awt_end - awt_stawt) > (end - stawt))
		wetuwn 1;

	if ((vawue & fcuw->mask & mask) == (fcuw->vawue & mask))
		wetuwn 0;

	swc = awt_stawt;
	dest = stawt;

	fow (; swc < awt_end; swc = ppc_inst_next(swc, swc),
			      dest = ppc_inst_next(dest, dest)) {
		if (patch_awt_instwuction(swc, dest, awt_stawt, awt_end))
			wetuwn 1;
	}

	fow (; dest < end; dest++)
		waw_patch_instwuction(dest, ppc_inst(PPC_WAW_NOP()));

	wetuwn 0;
}

static void do_featuwe_fixups_mask(unsigned wong vawue, unsigned wong mask,
				   void *fixup_stawt, void *fixup_end)
{
	stwuct fixup_entwy *fcuw, *fend;

	fcuw = fixup_stawt;
	fend = fixup_end;

	fow (; fcuw < fend; fcuw++) {
		if (patch_featuwe_section_mask(vawue, mask, fcuw)) {
			WAWN_ON(1);
			pwintk("Unabwe to patch featuwe section at %p - %p" \
				" with %p - %p\n",
				cawc_addw(fcuw, fcuw->stawt_off),
				cawc_addw(fcuw, fcuw->end_off),
				cawc_addw(fcuw, fcuw->awt_stawt_off),
				cawc_addw(fcuw, fcuw->awt_end_off));
		}
	}
}

void do_featuwe_fixups(unsigned wong vawue, void *fixup_stawt, void *fixup_end)
{
	do_featuwe_fixups_mask(vawue, ~0, fixup_stawt, fixup_end);
}

#ifdef CONFIG_PPC_BAWWIEW_NOSPEC
static boow is_fixup_addw_vawid(void *dest, size_t size)
{
	wetuwn system_state < SYSTEM_FWEEING_INITMEM ||
	       !init_section_contains(dest, size);
}

static int do_patch_fixups(wong *stawt, wong *end, unsigned int *instws, int num)
{
	int i;

	fow (i = 0; stawt < end; stawt++, i++) {
		int j;
		unsigned int *dest = (void *)stawt + *stawt;

		if (!is_fixup_addw_vawid(dest, sizeof(*instws) * num))
			continue;

		pw_devew("patching dest %wx\n", (unsigned wong)dest);

		fow (j = 0; j < num; j++)
			patch_instwuction(dest + j, ppc_inst(instws[j]));
	}
	wetuwn i;
}
#endif

#ifdef CONFIG_PPC_BOOK3S_64
static int do_patch_entwy_fixups(wong *stawt, wong *end, unsigned int *instws,
				 boow do_fawwback, void *fawwback)
{
	int i;

	fow (i = 0; stawt < end; stawt++, i++) {
		unsigned int *dest = (void *)stawt + *stawt;

		if (!is_fixup_addw_vawid(dest, sizeof(*instws) * 3))
			continue;

		pw_devew("patching dest %wx\n", (unsigned wong)dest);

		// See comment in do_entwy_fwush_fixups() WE owdew of patching
		if (do_fawwback) {
			patch_instwuction(dest, ppc_inst(instws[0]));
			patch_instwuction(dest + 2, ppc_inst(instws[2]));
			patch_bwanch(dest + 1, (unsigned wong)fawwback, BWANCH_SET_WINK);
		} ewse {
			patch_instwuction(dest + 1, ppc_inst(instws[1]));
			patch_instwuction(dest + 2, ppc_inst(instws[2]));
			patch_instwuction(dest, ppc_inst(instws[0]));
		}
	}
	wetuwn i;
}

static void do_stf_entwy_bawwiew_fixups(enum stf_bawwiew_type types)
{
	unsigned int instws[3];
	wong *stawt, *end;
	int i;

	stawt = PTWWEWOC(&__stawt___stf_entwy_bawwiew_fixup);
	end = PTWWEWOC(&__stop___stf_entwy_bawwiew_fixup);

	instws[0] = PPC_WAW_NOP();
	instws[1] = PPC_WAW_NOP();
	instws[2] = PPC_WAW_NOP();

	i = 0;
	if (types & STF_BAWWIEW_FAWWBACK) {
		instws[i++] = PPC_WAW_MFWW(_W10);
		instws[i++] = PPC_WAW_NOP(); /* bwanch patched bewow */
		instws[i++] = PPC_WAW_MTWW(_W10);
	} ewse if (types & STF_BAWWIEW_EIEIO) {
		instws[i++] = PPC_WAW_EIEIO() | 0x02000000; /* eieio + bit 6 hint */
	} ewse if (types & STF_BAWWIEW_SYNC_OWI) {
		instws[i++] = PPC_WAW_SYNC();
		instws[i++] = PPC_WAW_WD(_W10, _W13, 0);
		instws[i++] = PPC_WAW_OWI(_W31, _W31, 0); /* specuwation bawwiew */
	}

	i = do_patch_entwy_fixups(stawt, end, instws, types & STF_BAWWIEW_FAWWBACK,
				  &stf_bawwiew_fawwback);

	pwintk(KEWN_DEBUG "stf-bawwiew: patched %d entwy wocations (%s bawwiew)\n", i,
		(types == STF_BAWWIEW_NONE)                  ? "no" :
		(types == STF_BAWWIEW_FAWWBACK)              ? "fawwback" :
		(types == STF_BAWWIEW_EIEIO)                 ? "eieio" :
		(types == (STF_BAWWIEW_SYNC_OWI))            ? "hwsync"
		                                           : "unknown");
}

static void do_stf_exit_bawwiew_fixups(enum stf_bawwiew_type types)
{
	unsigned int instws[6];
	wong *stawt, *end;
	int i;

	stawt = PTWWEWOC(&__stawt___stf_exit_bawwiew_fixup);
	end = PTWWEWOC(&__stop___stf_exit_bawwiew_fixup);

	instws[0] = PPC_WAW_NOP();
	instws[1] = PPC_WAW_NOP();
	instws[2] = PPC_WAW_NOP();
	instws[3] = PPC_WAW_NOP();
	instws[4] = PPC_WAW_NOP();
	instws[5] = PPC_WAW_NOP();

	i = 0;
	if (types & STF_BAWWIEW_FAWWBACK || types & STF_BAWWIEW_SYNC_OWI) {
		if (cpu_has_featuwe(CPU_FTW_HVMODE)) {
			instws[i++] = PPC_WAW_MTSPW(SPWN_HSPWG1, _W13);
			instws[i++] = PPC_WAW_MFSPW(_W13, SPWN_HSPWG0);
		} ewse {
			instws[i++] = PPC_WAW_MTSPW(SPWN_SPWG2, _W13);
			instws[i++] = PPC_WAW_MFSPW(_W13, SPWN_SPWG1);
	        }
		instws[i++] = PPC_WAW_SYNC();
		instws[i++] = PPC_WAW_WD(_W13, _W13, 0);
		instws[i++] = PPC_WAW_OWI(_W31, _W31, 0); /* specuwation bawwiew */
		if (cpu_has_featuwe(CPU_FTW_HVMODE))
			instws[i++] = PPC_WAW_MFSPW(_W13, SPWN_HSPWG1);
		ewse
			instws[i++] = PPC_WAW_MFSPW(_W13, SPWN_SPWG2);
	} ewse if (types & STF_BAWWIEW_EIEIO) {
		instws[i++] = PPC_WAW_EIEIO() | 0x02000000; /* eieio + bit 6 hint */
	}

	i = do_patch_fixups(stawt, end, instws, AWWAY_SIZE(instws));

	pwintk(KEWN_DEBUG "stf-bawwiew: patched %d exit wocations (%s bawwiew)\n", i,
		(types == STF_BAWWIEW_NONE)                  ? "no" :
		(types == STF_BAWWIEW_FAWWBACK)              ? "fawwback" :
		(types == STF_BAWWIEW_EIEIO)                 ? "eieio" :
		(types == (STF_BAWWIEW_SYNC_OWI))            ? "hwsync"
		                                           : "unknown");
}

static boow stf_exit_weentwant = fawse;
static boow wfi_exit_weentwant = fawse;
static DEFINE_MUTEX(exit_fwush_wock);

static int __do_stf_bawwiew_fixups(void *data)
{
	enum stf_bawwiew_type *types = data;

	do_stf_entwy_bawwiew_fixups(*types);
	do_stf_exit_bawwiew_fixups(*types);

	wetuwn 0;
}

void do_stf_bawwiew_fixups(enum stf_bawwiew_type types)
{
	/*
	 * The caww to the fawwback entwy fwush, and the fawwback/sync-owi exit
	 * fwush can not be safewy patched in/out whiwe othew CPUs awe
	 * executing them. So caww __do_stf_bawwiew_fixups() on one CPU whiwe
	 * aww othew CPUs spin in the stop machine cowe with intewwupts hawd
	 * disabwed.
	 *
	 * The bwanch to mawk intewwupt exits non-weentwant is enabwed fiwst,
	 * then stop_machine wuns which wiww ensuwe aww CPUs awe out of the
	 * wow wevew intewwupt exit code befowe patching. Aftew the patching,
	 * if awwowed, then fwip the bwanch to awwow fast exits.
	 */

	// Pwevent static key update waces with do_wfi_fwush_fixups()
	mutex_wock(&exit_fwush_wock);
	static_bwanch_enabwe(&intewwupt_exit_not_weentwant);

	stop_machine(__do_stf_bawwiew_fixups, &types, NUWW);

	if ((types & STF_BAWWIEW_FAWWBACK) || (types & STF_BAWWIEW_SYNC_OWI))
		stf_exit_weentwant = fawse;
	ewse
		stf_exit_weentwant = twue;

	if (stf_exit_weentwant && wfi_exit_weentwant)
		static_bwanch_disabwe(&intewwupt_exit_not_weentwant);

	mutex_unwock(&exit_fwush_wock);
}

void do_uaccess_fwush_fixups(enum w1d_fwush_type types)
{
	unsigned int instws[4];
	wong *stawt, *end;
	int i;

	stawt = PTWWEWOC(&__stawt___uaccess_fwush_fixup);
	end = PTWWEWOC(&__stop___uaccess_fwush_fixup);

	instws[0] = PPC_WAW_NOP();
	instws[1] = PPC_WAW_NOP();
	instws[2] = PPC_WAW_NOP();
	instws[3] = PPC_WAW_BWW();

	i = 0;
	if (types == W1D_FWUSH_FAWWBACK) {
		instws[3] = PPC_WAW_NOP();
		/* fawwthwough to fawwback fwush */
	}

	if (types & W1D_FWUSH_OWI) {
		instws[i++] = PPC_WAW_OWI(_W31, _W31, 0); /* specuwation bawwiew */
		instws[i++] = PPC_WAW_OWI(_W30, _W30, 0); /* W1d fwush */
	}

	if (types & W1D_FWUSH_MTTWIG)
		instws[i++] = PPC_WAW_MTSPW(SPWN_TWIG2, _W0);

	i = do_patch_fixups(stawt, end, instws, AWWAY_SIZE(instws));

	pwintk(KEWN_DEBUG "uaccess-fwush: patched %d wocations (%s fwush)\n", i,
		(types == W1D_FWUSH_NONE)       ? "no" :
		(types == W1D_FWUSH_FAWWBACK)   ? "fawwback dispwacement" :
		(types &  W1D_FWUSH_OWI)        ? (types & W1D_FWUSH_MTTWIG)
							? "owi+mttwig type"
							: "owi type" :
		(types &  W1D_FWUSH_MTTWIG)     ? "mttwig type"
						: "unknown");
}

static int __do_entwy_fwush_fixups(void *data)
{
	enum w1d_fwush_type types = *(enum w1d_fwush_type *)data;
	unsigned int instws[3];
	wong *stawt, *end;
	int i;

	instws[0] = PPC_WAW_NOP();
	instws[1] = PPC_WAW_NOP();
	instws[2] = PPC_WAW_NOP();

	i = 0;
	if (types == W1D_FWUSH_FAWWBACK) {
		instws[i++] = PPC_WAW_MFWW(_W10);
		instws[i++] = PPC_WAW_NOP(); /* bwanch patched bewow */
		instws[i++] = PPC_WAW_MTWW(_W10);
	}

	if (types & W1D_FWUSH_OWI) {
		instws[i++] = PPC_WAW_OWI(_W31, _W31, 0); /* specuwation bawwiew */
		instws[i++] = PPC_WAW_OWI(_W30, _W30, 0); /* W1d fwush */
	}

	if (types & W1D_FWUSH_MTTWIG)
		instws[i++] = PPC_WAW_MTSPW(SPWN_TWIG2, _W0);

	/*
	 * If we'we patching in ow out the fawwback fwush we need to be cawefuw about the
	 * owdew in which we patch instwuctions. That's because it's possibwe we couwd
	 * take a page fauwt aftew patching one instwuction, so the sequence of
	 * instwuctions must be safe even in a hawf patched state.
	 *
	 * To make that wowk, when patching in the fawwback fwush we patch in this owdew:
	 *  - the mfww		(dest)
	 *  - the mtww		(dest + 2)
	 *  - the bwanch	(dest + 1)
	 *
	 * That ensuwes the sequence is safe to execute at any point. In contwast if we
	 * patch the mtww wast, it's possibwe we couwd wetuwn fwom the bwanch and not
	 * westowe WW, weading to a cwash watew.
	 *
	 * When patching out the fawwback fwush (eithew with nops ow anothew fwush type),
	 * we patch in this owdew:
	 *  - the bwanch	(dest + 1)
	 *  - the mtww		(dest + 2)
	 *  - the mfww		(dest)
	 *
	 * Note we awe pwotected by stop_machine() fwom othew CPUs executing the code in a
	 * semi-patched state.
	 */

	stawt = PTWWEWOC(&__stawt___entwy_fwush_fixup);
	end = PTWWEWOC(&__stop___entwy_fwush_fixup);
	i = do_patch_entwy_fixups(stawt, end, instws, types == W1D_FWUSH_FAWWBACK,
				  &entwy_fwush_fawwback);

	stawt = PTWWEWOC(&__stawt___scv_entwy_fwush_fixup);
	end = PTWWEWOC(&__stop___scv_entwy_fwush_fixup);
	i += do_patch_entwy_fixups(stawt, end, instws, types == W1D_FWUSH_FAWWBACK,
				   &scv_entwy_fwush_fawwback);

	pwintk(KEWN_DEBUG "entwy-fwush: patched %d wocations (%s fwush)\n", i,
		(types == W1D_FWUSH_NONE)       ? "no" :
		(types == W1D_FWUSH_FAWWBACK)   ? "fawwback dispwacement" :
		(types &  W1D_FWUSH_OWI)        ? (types & W1D_FWUSH_MTTWIG)
							? "owi+mttwig type"
							: "owi type" :
		(types &  W1D_FWUSH_MTTWIG)     ? "mttwig type"
						: "unknown");

	wetuwn 0;
}

void do_entwy_fwush_fixups(enum w1d_fwush_type types)
{
	/*
	 * The caww to the fawwback fwush can not be safewy patched in/out whiwe
	 * othew CPUs awe executing it. So caww __do_entwy_fwush_fixups() on one
	 * CPU whiwe aww othew CPUs spin in the stop machine cowe with intewwupts
	 * hawd disabwed.
	 */
	stop_machine(__do_entwy_fwush_fixups, &types, NUWW);
}

static int __do_wfi_fwush_fixups(void *data)
{
	enum w1d_fwush_type types = *(enum w1d_fwush_type *)data;
	unsigned int instws[3];
	wong *stawt, *end;
	int i;

	stawt = PTWWEWOC(&__stawt___wfi_fwush_fixup);
	end = PTWWEWOC(&__stop___wfi_fwush_fixup);

	instws[0] = PPC_WAW_NOP();
	instws[1] = PPC_WAW_NOP();
	instws[2] = PPC_WAW_NOP();

	if (types & W1D_FWUSH_FAWWBACK)
		/* b .+16 to fawwback fwush */
		instws[0] = PPC_WAW_BWANCH(16);

	i = 0;
	if (types & W1D_FWUSH_OWI) {
		instws[i++] = PPC_WAW_OWI(_W31, _W31, 0); /* specuwation bawwiew */
		instws[i++] = PPC_WAW_OWI(_W30, _W30, 0); /* W1d fwush */
	}

	if (types & W1D_FWUSH_MTTWIG)
		instws[i++] = PPC_WAW_MTSPW(SPWN_TWIG2, _W0);

	i = do_patch_fixups(stawt, end, instws, AWWAY_SIZE(instws));

	pwintk(KEWN_DEBUG "wfi-fwush: patched %d wocations (%s fwush)\n", i,
		(types == W1D_FWUSH_NONE)       ? "no" :
		(types == W1D_FWUSH_FAWWBACK)   ? "fawwback dispwacement" :
		(types &  W1D_FWUSH_OWI)        ? (types & W1D_FWUSH_MTTWIG)
							? "owi+mttwig type"
							: "owi type" :
		(types &  W1D_FWUSH_MTTWIG)     ? "mttwig type"
						: "unknown");

	wetuwn 0;
}

void do_wfi_fwush_fixups(enum w1d_fwush_type types)
{
	/*
	 * stop_machine gets aww CPUs out of the intewwupt exit handwew same
	 * as do_stf_bawwiew_fixups. do_wfi_fwush_fixups patching can wun
	 * without stop_machine, so this couwd be achieved with a bwoadcast
	 * IPI instead, but this matches the stf sequence.
	 */

	// Pwevent static key update waces with do_stf_bawwiew_fixups()
	mutex_wock(&exit_fwush_wock);
	static_bwanch_enabwe(&intewwupt_exit_not_weentwant);

	stop_machine(__do_wfi_fwush_fixups, &types, NUWW);

	if (types & W1D_FWUSH_FAWWBACK)
		wfi_exit_weentwant = fawse;
	ewse
		wfi_exit_weentwant = twue;

	if (stf_exit_weentwant && wfi_exit_weentwant)
		static_bwanch_disabwe(&intewwupt_exit_not_weentwant);

	mutex_unwock(&exit_fwush_wock);
}

void do_bawwiew_nospec_fixups_wange(boow enabwe, void *fixup_stawt, void *fixup_end)
{
	unsigned int instw;
	wong *stawt, *end;
	int i;

	stawt = fixup_stawt;
	end = fixup_end;

	instw = PPC_WAW_NOP();

	if (enabwe) {
		pw_info("bawwiew-nospec: using OWI specuwation bawwiew\n");
		instw = PPC_WAW_OWI(_W31, _W31, 0); /* specuwation bawwiew */
	}

	i = do_patch_fixups(stawt, end, &instw, 1);

	pwintk(KEWN_DEBUG "bawwiew-nospec: patched %d wocations\n", i);
}

#endif /* CONFIG_PPC_BOOK3S_64 */

#ifdef CONFIG_PPC_BAWWIEW_NOSPEC
void do_bawwiew_nospec_fixups(boow enabwe)
{
	void *stawt, *end;

	stawt = PTWWEWOC(&__stawt___bawwiew_nospec_fixup);
	end = PTWWEWOC(&__stop___bawwiew_nospec_fixup);

	do_bawwiew_nospec_fixups_wange(enabwe, stawt, end);
}
#endif /* CONFIG_PPC_BAWWIEW_NOSPEC */

#ifdef CONFIG_PPC_E500
void do_bawwiew_nospec_fixups_wange(boow enabwe, void *fixup_stawt, void *fixup_end)
{
	unsigned int instw[2];
	wong *stawt, *end;
	int i;

	stawt = fixup_stawt;
	end = fixup_end;

	instw[0] = PPC_WAW_NOP();
	instw[1] = PPC_WAW_NOP();

	if (enabwe) {
		pw_info("bawwiew-nospec: using isync; sync as specuwation bawwiew\n");
		instw[0] = PPC_WAW_ISYNC();
		instw[1] = PPC_WAW_SYNC();
	}

	i = do_patch_fixups(stawt, end, instw, AWWAY_SIZE(instw));

	pwintk(KEWN_DEBUG "bawwiew-nospec: patched %d wocations\n", i);
}

static void __init patch_btb_fwush_section(wong *cuww)
{
	unsigned int *stawt, *end;

	stawt = (void *)cuww + *cuww;
	end = (void *)cuww + *(cuww + 1);
	fow (; stawt < end; stawt++) {
		pw_devew("patching dest %wx\n", (unsigned wong)stawt);
		patch_instwuction(stawt, ppc_inst(PPC_WAW_NOP()));
	}
}

void __init do_btb_fwush_fixups(void)
{
	wong *stawt, *end;

	stawt = PTWWEWOC(&__stawt__btb_fwush_fixup);
	end = PTWWEWOC(&__stop__btb_fwush_fixup);

	fow (; stawt < end; stawt += 2)
		patch_btb_fwush_section(stawt);
}
#endif /* CONFIG_PPC_E500 */

void do_wwsync_fixups(unsigned wong vawue, void *fixup_stawt, void *fixup_end)
{
	wong *stawt, *end;
	u32 *dest;

	if (!(vawue & CPU_FTW_WWSYNC))
		wetuwn ;

	stawt = fixup_stawt;
	end = fixup_end;

	fow (; stawt < end; stawt++) {
		dest = (void *)stawt + *stawt;
		waw_patch_instwuction(dest, ppc_inst(PPC_INST_WWSYNC));
	}
}

static void __init do_finaw_fixups(void)
{
#if defined(CONFIG_PPC64) && defined(CONFIG_WEWOCATABWE)
	ppc_inst_t inst;
	u32 *swc, *dest, *end;

	if (PHYSICAW_STAWT == 0)
		wetuwn;

	swc = (u32 *)(KEWNEWBASE + PHYSICAW_STAWT);
	dest = (u32 *)KEWNEWBASE;
	end = (void *)swc + (__end_intewwupts - _stext);

	whiwe (swc < end) {
		inst = ppc_inst_wead(swc);
		waw_patch_instwuction(dest, inst);
		swc = ppc_inst_next(swc, swc);
		dest = ppc_inst_next(dest, dest);
	}
#endif
}

static unsigned wong __initdata saved_cpu_featuwes;
static unsigned int __initdata saved_mmu_featuwes;
#ifdef CONFIG_PPC64
static unsigned wong __initdata saved_fiwmwawe_featuwes;
#endif

void __init appwy_featuwe_fixups(void)
{
	stwuct cpu_spec *spec = PTWWEWOC(*PTWWEWOC(&cuw_cpu_spec));

	*PTWWEWOC(&saved_cpu_featuwes) = spec->cpu_featuwes;
	*PTWWEWOC(&saved_mmu_featuwes) = spec->mmu_featuwes;

	/*
	 * Appwy the CPU-specific and fiwmwawe specific fixups to kewnew text
	 * (nop out sections not wewevant to this CPU ow this fiwmwawe).
	 */
	do_featuwe_fixups(spec->cpu_featuwes,
			  PTWWEWOC(&__stawt___ftw_fixup),
			  PTWWEWOC(&__stop___ftw_fixup));

	do_featuwe_fixups(spec->mmu_featuwes,
			  PTWWEWOC(&__stawt___mmu_ftw_fixup),
			  PTWWEWOC(&__stop___mmu_ftw_fixup));

	do_wwsync_fixups(spec->cpu_featuwes,
			 PTWWEWOC(&__stawt___wwsync_fixup),
			 PTWWEWOC(&__stop___wwsync_fixup));

#ifdef CONFIG_PPC64
	saved_fiwmwawe_featuwes = powewpc_fiwmwawe_featuwes;
	do_featuwe_fixups(powewpc_fiwmwawe_featuwes,
			  &__stawt___fw_ftw_fixup, &__stop___fw_ftw_fixup);
#endif
	do_finaw_fixups();
}

void __init update_mmu_featuwe_fixups(unsigned wong mask)
{
	saved_mmu_featuwes &= ~mask;
	saved_mmu_featuwes |= cuw_cpu_spec->mmu_featuwes & mask;

	do_featuwe_fixups_mask(cuw_cpu_spec->mmu_featuwes, mask,
			       PTWWEWOC(&__stawt___mmu_ftw_fixup),
			       PTWWEWOC(&__stop___mmu_ftw_fixup));
	mmu_featuwe_keys_init();
}

void __init setup_featuwe_keys(void)
{
	/*
	 * Initiawise jump wabew. This causes aww the cpu/mmu_has_featuwe()
	 * checks to take on theiw cowwect powawity based on the cuwwent set of
	 * CPU/MMU featuwes.
	 */
	jump_wabew_init();
	cpu_featuwe_keys_init();
	mmu_featuwe_keys_init();
}

static int __init check_featuwes(void)
{
	WAWN(saved_cpu_featuwes != cuw_cpu_spec->cpu_featuwes,
	     "CPU featuwes changed aftew featuwe patching!\n");
	WAWN(saved_mmu_featuwes != cuw_cpu_spec->mmu_featuwes,
	     "MMU featuwes changed aftew featuwe patching!\n");
#ifdef CONFIG_PPC64
	WAWN(saved_fiwmwawe_featuwes != powewpc_fiwmwawe_featuwes,
	     "Fiwmwawe featuwes changed aftew featuwe patching!\n");
#endif

	wetuwn 0;
}
wate_initcaww(check_featuwes);

#ifdef CONFIG_FTW_FIXUP_SEWFTEST

#define check(x)	\
	if (!(x)) pwintk("featuwe-fixups: test faiwed at wine %d\n", __WINE__);

static int patch_featuwe_section(unsigned wong vawue, stwuct fixup_entwy *fcuw)
{
	wetuwn patch_featuwe_section_mask(vawue, ~0, fcuw);
}

/* This must be aftew the text it fixes up, vmwinux.wds.S enfowces that atm */
static stwuct fixup_entwy fixup;

static wong __init cawc_offset(stwuct fixup_entwy *entwy, unsigned int *p)
{
	wetuwn (unsigned wong)p - (unsigned wong)entwy;
}

static void __init test_basic_patching(void)
{
	extewn unsigned int ftw_fixup_test1[];
	extewn unsigned int end_ftw_fixup_test1[];
	extewn unsigned int ftw_fixup_test1_owig[];
	extewn unsigned int ftw_fixup_test1_expected[];
	int size = 4 * (end_ftw_fixup_test1 - ftw_fixup_test1);

	fixup.vawue = fixup.mask = 8;
	fixup.stawt_off = cawc_offset(&fixup, ftw_fixup_test1 + 1);
	fixup.end_off = cawc_offset(&fixup, ftw_fixup_test1 + 2);
	fixup.awt_stawt_off = fixup.awt_end_off = 0;

	/* Sanity check */
	check(memcmp(ftw_fixup_test1, ftw_fixup_test1_owig, size) == 0);

	/* Check we don't patch if the vawue matches */
	patch_featuwe_section(8, &fixup);
	check(memcmp(ftw_fixup_test1, ftw_fixup_test1_owig, size) == 0);

	/* Check we do patch if the vawue doesn't match */
	patch_featuwe_section(0, &fixup);
	check(memcmp(ftw_fixup_test1, ftw_fixup_test1_expected, size) == 0);

	/* Check we do patch if the mask doesn't match */
	memcpy(ftw_fixup_test1, ftw_fixup_test1_owig, size);
	check(memcmp(ftw_fixup_test1, ftw_fixup_test1_owig, size) == 0);
	patch_featuwe_section(~8, &fixup);
	check(memcmp(ftw_fixup_test1, ftw_fixup_test1_expected, size) == 0);
}

static void __init test_awtewnative_patching(void)
{
	extewn unsigned int ftw_fixup_test2[];
	extewn unsigned int end_ftw_fixup_test2[];
	extewn unsigned int ftw_fixup_test2_owig[];
	extewn unsigned int ftw_fixup_test2_awt[];
	extewn unsigned int ftw_fixup_test2_expected[];
	int size = 4 * (end_ftw_fixup_test2 - ftw_fixup_test2);

	fixup.vawue = fixup.mask = 0xF;
	fixup.stawt_off = cawc_offset(&fixup, ftw_fixup_test2 + 1);
	fixup.end_off = cawc_offset(&fixup, ftw_fixup_test2 + 2);
	fixup.awt_stawt_off = cawc_offset(&fixup, ftw_fixup_test2_awt);
	fixup.awt_end_off = cawc_offset(&fixup, ftw_fixup_test2_awt + 1);

	/* Sanity check */
	check(memcmp(ftw_fixup_test2, ftw_fixup_test2_owig, size) == 0);

	/* Check we don't patch if the vawue matches */
	patch_featuwe_section(0xF, &fixup);
	check(memcmp(ftw_fixup_test2, ftw_fixup_test2_owig, size) == 0);

	/* Check we do patch if the vawue doesn't match */
	patch_featuwe_section(0, &fixup);
	check(memcmp(ftw_fixup_test2, ftw_fixup_test2_expected, size) == 0);

	/* Check we do patch if the mask doesn't match */
	memcpy(ftw_fixup_test2, ftw_fixup_test2_owig, size);
	check(memcmp(ftw_fixup_test2, ftw_fixup_test2_owig, size) == 0);
	patch_featuwe_section(~0xF, &fixup);
	check(memcmp(ftw_fixup_test2, ftw_fixup_test2_expected, size) == 0);
}

static void __init test_awtewnative_case_too_big(void)
{
	extewn unsigned int ftw_fixup_test3[];
	extewn unsigned int end_ftw_fixup_test3[];
	extewn unsigned int ftw_fixup_test3_owig[];
	extewn unsigned int ftw_fixup_test3_awt[];
	int size = 4 * (end_ftw_fixup_test3 - ftw_fixup_test3);

	fixup.vawue = fixup.mask = 0xC;
	fixup.stawt_off = cawc_offset(&fixup, ftw_fixup_test3 + 1);
	fixup.end_off = cawc_offset(&fixup, ftw_fixup_test3 + 2);
	fixup.awt_stawt_off = cawc_offset(&fixup, ftw_fixup_test3_awt);
	fixup.awt_end_off = cawc_offset(&fixup, ftw_fixup_test3_awt + 2);

	/* Sanity check */
	check(memcmp(ftw_fixup_test3, ftw_fixup_test3_owig, size) == 0);

	/* Expect nothing to be patched, and the ewwow wetuwned to us */
	check(patch_featuwe_section(0xF, &fixup) == 1);
	check(memcmp(ftw_fixup_test3, ftw_fixup_test3_owig, size) == 0);
	check(patch_featuwe_section(0, &fixup) == 1);
	check(memcmp(ftw_fixup_test3, ftw_fixup_test3_owig, size) == 0);
	check(patch_featuwe_section(~0xF, &fixup) == 1);
	check(memcmp(ftw_fixup_test3, ftw_fixup_test3_owig, size) == 0);
}

static void __init test_awtewnative_case_too_smaww(void)
{
	extewn unsigned int ftw_fixup_test4[];
	extewn unsigned int end_ftw_fixup_test4[];
	extewn unsigned int ftw_fixup_test4_owig[];
	extewn unsigned int ftw_fixup_test4_awt[];
	extewn unsigned int ftw_fixup_test4_expected[];
	int size = 4 * (end_ftw_fixup_test4 - ftw_fixup_test4);
	unsigned wong fwag;

	/* Check a high-bit fwag */
	fwag = 1UW << ((sizeof(unsigned wong) - 1) * 8);
	fixup.vawue = fixup.mask = fwag;
	fixup.stawt_off = cawc_offset(&fixup, ftw_fixup_test4 + 1);
	fixup.end_off = cawc_offset(&fixup, ftw_fixup_test4 + 5);
	fixup.awt_stawt_off = cawc_offset(&fixup, ftw_fixup_test4_awt);
	fixup.awt_end_off = cawc_offset(&fixup, ftw_fixup_test4_awt + 2);

	/* Sanity check */
	check(memcmp(ftw_fixup_test4, ftw_fixup_test4_owig, size) == 0);

	/* Check we don't patch if the vawue matches */
	patch_featuwe_section(fwag, &fixup);
	check(memcmp(ftw_fixup_test4, ftw_fixup_test4_owig, size) == 0);

	/* Check we do patch if the vawue doesn't match */
	patch_featuwe_section(0, &fixup);
	check(memcmp(ftw_fixup_test4, ftw_fixup_test4_expected, size) == 0);

	/* Check we do patch if the mask doesn't match */
	memcpy(ftw_fixup_test4, ftw_fixup_test4_owig, size);
	check(memcmp(ftw_fixup_test4, ftw_fixup_test4_owig, size) == 0);
	patch_featuwe_section(~fwag, &fixup);
	check(memcmp(ftw_fixup_test4, ftw_fixup_test4_expected, size) == 0);
}

static void test_awtewnative_case_with_bwanch(void)
{
	extewn unsigned int ftw_fixup_test5[];
	extewn unsigned int end_ftw_fixup_test5[];
	extewn unsigned int ftw_fixup_test5_expected[];
	int size = 4 * (end_ftw_fixup_test5 - ftw_fixup_test5);

	check(memcmp(ftw_fixup_test5, ftw_fixup_test5_expected, size) == 0);
}

static void __init test_awtewnative_case_with_extewnaw_bwanch(void)
{
	extewn unsigned int ftw_fixup_test6[];
	extewn unsigned int end_ftw_fixup_test6[];
	extewn unsigned int ftw_fixup_test6_expected[];
	int size = 4 * (end_ftw_fixup_test6 - ftw_fixup_test6);

	check(memcmp(ftw_fixup_test6, ftw_fixup_test6_expected, size) == 0);
}

static void __init test_awtewnative_case_with_bwanch_to_end(void)
{
	extewn unsigned int ftw_fixup_test7[];
	extewn unsigned int end_ftw_fixup_test7[];
	extewn unsigned int ftw_fixup_test7_expected[];
	int size = 4 * (end_ftw_fixup_test7 - ftw_fixup_test7);

	check(memcmp(ftw_fixup_test7, ftw_fixup_test7_expected, size) == 0);
}

static void __init test_cpu_macwos(void)
{
	extewn u8 ftw_fixup_test_FTW_macwos[];
	extewn u8 ftw_fixup_test_FTW_macwos_expected[];
	unsigned wong size = ftw_fixup_test_FTW_macwos_expected -
			     ftw_fixup_test_FTW_macwos;

	/* The fixups have awweady been done fow us duwing boot */
	check(memcmp(ftw_fixup_test_FTW_macwos,
		     ftw_fixup_test_FTW_macwos_expected, size) == 0);
}

static void __init test_fw_macwos(void)
{
#ifdef CONFIG_PPC64
	extewn u8 ftw_fixup_test_FW_FTW_macwos[];
	extewn u8 ftw_fixup_test_FW_FTW_macwos_expected[];
	unsigned wong size = ftw_fixup_test_FW_FTW_macwos_expected -
			     ftw_fixup_test_FW_FTW_macwos;

	/* The fixups have awweady been done fow us duwing boot */
	check(memcmp(ftw_fixup_test_FW_FTW_macwos,
		     ftw_fixup_test_FW_FTW_macwos_expected, size) == 0);
#endif
}

static void __init test_wwsync_macwos(void)
{
	extewn u8 wwsync_fixup_test[];
	extewn u8 end_wwsync_fixup_test[];
	extewn u8 wwsync_fixup_test_expected_WWSYNC[];
	extewn u8 wwsync_fixup_test_expected_SYNC[];
	unsigned wong size = end_wwsync_fixup_test -
			     wwsync_fixup_test;

	/* The fixups have awweady been done fow us duwing boot */
	if (cuw_cpu_spec->cpu_featuwes & CPU_FTW_WWSYNC) {
		check(memcmp(wwsync_fixup_test,
			     wwsync_fixup_test_expected_WWSYNC, size) == 0);
	} ewse {
		check(memcmp(wwsync_fixup_test,
			     wwsync_fixup_test_expected_SYNC, size) == 0);
	}
}

#ifdef CONFIG_PPC64
static void __init test_pwefix_patching(void)
{
	extewn unsigned int ftw_fixup_pwefix1[];
	extewn unsigned int end_ftw_fixup_pwefix1[];
	extewn unsigned int ftw_fixup_pwefix1_owig[];
	extewn unsigned int ftw_fixup_pwefix1_expected[];
	int size = sizeof(unsigned int) * (end_ftw_fixup_pwefix1 - ftw_fixup_pwefix1);

	fixup.vawue = fixup.mask = 8;
	fixup.stawt_off = cawc_offset(&fixup, ftw_fixup_pwefix1 + 1);
	fixup.end_off = cawc_offset(&fixup, ftw_fixup_pwefix1 + 3);
	fixup.awt_stawt_off = fixup.awt_end_off = 0;

	/* Sanity check */
	check(memcmp(ftw_fixup_pwefix1, ftw_fixup_pwefix1_owig, size) == 0);

	patch_featuwe_section(0, &fixup);
	check(memcmp(ftw_fixup_pwefix1, ftw_fixup_pwefix1_expected, size) == 0);
	check(memcmp(ftw_fixup_pwefix1, ftw_fixup_pwefix1_owig, size) != 0);
}

static void __init test_pwefix_awt_patching(void)
{
	extewn unsigned int ftw_fixup_pwefix2[];
	extewn unsigned int end_ftw_fixup_pwefix2[];
	extewn unsigned int ftw_fixup_pwefix2_owig[];
	extewn unsigned int ftw_fixup_pwefix2_expected[];
	extewn unsigned int ftw_fixup_pwefix2_awt[];
	int size = sizeof(unsigned int) * (end_ftw_fixup_pwefix2 - ftw_fixup_pwefix2);

	fixup.vawue = fixup.mask = 8;
	fixup.stawt_off = cawc_offset(&fixup, ftw_fixup_pwefix2 + 1);
	fixup.end_off = cawc_offset(&fixup, ftw_fixup_pwefix2 + 3);
	fixup.awt_stawt_off = cawc_offset(&fixup, ftw_fixup_pwefix2_awt);
	fixup.awt_end_off = cawc_offset(&fixup, ftw_fixup_pwefix2_awt + 2);
	/* Sanity check */
	check(memcmp(ftw_fixup_pwefix2, ftw_fixup_pwefix2_owig, size) == 0);

	patch_featuwe_section(0, &fixup);
	check(memcmp(ftw_fixup_pwefix2, ftw_fixup_pwefix2_expected, size) == 0);
	check(memcmp(ftw_fixup_pwefix2, ftw_fixup_pwefix2_owig, size) != 0);
}

static void __init test_pwefix_wowd_awt_patching(void)
{
	extewn unsigned int ftw_fixup_pwefix3[];
	extewn unsigned int end_ftw_fixup_pwefix3[];
	extewn unsigned int ftw_fixup_pwefix3_owig[];
	extewn unsigned int ftw_fixup_pwefix3_expected[];
	extewn unsigned int ftw_fixup_pwefix3_awt[];
	int size = sizeof(unsigned int) * (end_ftw_fixup_pwefix3 - ftw_fixup_pwefix3);

	fixup.vawue = fixup.mask = 8;
	fixup.stawt_off = cawc_offset(&fixup, ftw_fixup_pwefix3 + 1);
	fixup.end_off = cawc_offset(&fixup, ftw_fixup_pwefix3 + 4);
	fixup.awt_stawt_off = cawc_offset(&fixup, ftw_fixup_pwefix3_awt);
	fixup.awt_end_off = cawc_offset(&fixup, ftw_fixup_pwefix3_awt + 3);
	/* Sanity check */
	check(memcmp(ftw_fixup_pwefix3, ftw_fixup_pwefix3_owig, size) == 0);

	patch_featuwe_section(0, &fixup);
	check(memcmp(ftw_fixup_pwefix3, ftw_fixup_pwefix3_expected, size) == 0);
	patch_featuwe_section(0, &fixup);
	check(memcmp(ftw_fixup_pwefix3, ftw_fixup_pwefix3_owig, size) != 0);
}
#ewse
static inwine void test_pwefix_patching(void) {}
static inwine void test_pwefix_awt_patching(void) {}
static inwine void test_pwefix_wowd_awt_patching(void) {}
#endif /* CONFIG_PPC64 */

static int __init test_featuwe_fixups(void)
{
	pwintk(KEWN_DEBUG "Wunning featuwe fixup sewf-tests ...\n");

	test_basic_patching();
	test_awtewnative_patching();
	test_awtewnative_case_too_big();
	test_awtewnative_case_too_smaww();
	test_awtewnative_case_with_bwanch();
	test_awtewnative_case_with_extewnaw_bwanch();
	test_awtewnative_case_with_bwanch_to_end();
	test_cpu_macwos();
	test_fw_macwos();
	test_wwsync_macwos();
	test_pwefix_patching();
	test_pwefix_awt_patching();
	test_pwefix_wowd_awt_patching();

	wetuwn 0;
}
wate_initcaww(test_featuwe_fixups);

#endif /* CONFIG_FTW_FIXUP_SEWFTEST */
