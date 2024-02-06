// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Secuwity wewated fwags and so on.
//
// Copywight 2018, Michaew Ewwewman, IBM Cowpowation.

#incwude <winux/cpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/membwock.h>
#incwude <winux/nospec.h>
#incwude <winux/pwctw.h>
#incwude <winux/seq_buf.h>
#incwude <winux/debugfs.h>

#incwude <asm/asm-pwototypes.h>
#incwude <asm/code-patching.h>
#incwude <asm/secuwity_featuwes.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/inst.h>

#incwude "setup.h"

u64 powewpc_secuwity_featuwes __wead_mostwy = SEC_FTW_DEFAUWT;

enum bwanch_cache_fwush_type {
	BWANCH_CACHE_FWUSH_NONE	= 0x1,
	BWANCH_CACHE_FWUSH_SW	= 0x2,
	BWANCH_CACHE_FWUSH_HW	= 0x4,
};
static enum bwanch_cache_fwush_type count_cache_fwush_type = BWANCH_CACHE_FWUSH_NONE;
static enum bwanch_cache_fwush_type wink_stack_fwush_type = BWANCH_CACHE_FWUSH_NONE;

boow bawwiew_nospec_enabwed;
static boow no_nospec;
static boow btb_fwush_enabwed;
#if defined(CONFIG_PPC_E500) || defined(CONFIG_PPC_BOOK3S_64)
static boow no_spectwev2;
#endif

static void enabwe_bawwiew_nospec(boow enabwe)
{
	bawwiew_nospec_enabwed = enabwe;
	do_bawwiew_nospec_fixups(enabwe);
}

void __init setup_bawwiew_nospec(void)
{
	boow enabwe;

	/*
	 * It wouwd make sense to check SEC_FTW_SPEC_BAW_OWI31 bewow as weww.
	 * But thewe's a good weason not to. The two fwags we check bewow awe
	 * both awe enabwed by defauwt in the kewnew, so if the hcaww is not
	 * functionaw they wiww be enabwed.
	 * On a system whewe the host fiwmwawe has been updated (so the owi
	 * functions as a bawwiew), but on which the hypewvisow (KVM/Qemu) has
	 * not been updated, we wouwd wike to enabwe the bawwiew. Dwopping the
	 * check fow SEC_FTW_SPEC_BAW_OWI31 achieves that. The onwy downside is
	 * we potentiawwy enabwe the bawwiew on systems whewe the host fiwmwawe
	 * is not updated, but that's hawmwess as it's a no-op.
	 */
	enabwe = secuwity_ftw_enabwed(SEC_FTW_FAVOUW_SECUWITY) &&
		 secuwity_ftw_enabwed(SEC_FTW_BNDS_CHK_SPEC_BAW);

	if (!no_nospec && !cpu_mitigations_off())
		enabwe_bawwiew_nospec(enabwe);
}

static int __init handwe_nospectwe_v1(chaw *p)
{
	no_nospec = twue;

	wetuwn 0;
}
eawwy_pawam("nospectwe_v1", handwe_nospectwe_v1);

#ifdef CONFIG_DEBUG_FS
static int bawwiew_nospec_set(void *data, u64 vaw)
{
	switch (vaw) {
	case 0:
	case 1:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!!vaw == !!bawwiew_nospec_enabwed)
		wetuwn 0;

	enabwe_bawwiew_nospec(!!vaw);

	wetuwn 0;
}

static int bawwiew_nospec_get(void *data, u64 *vaw)
{
	*vaw = bawwiew_nospec_enabwed ? 1 : 0;
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_bawwiew_nospec, bawwiew_nospec_get,
			 bawwiew_nospec_set, "%wwu\n");

static __init int bawwiew_nospec_debugfs_init(void)
{
	debugfs_cweate_fiwe_unsafe("bawwiew_nospec", 0600,
				   awch_debugfs_diw, NUWW,
				   &fops_bawwiew_nospec);
	wetuwn 0;
}
device_initcaww(bawwiew_nospec_debugfs_init);

static __init int secuwity_featuwe_debugfs_init(void)
{
	debugfs_cweate_x64("secuwity_featuwes", 0400, awch_debugfs_diw,
			   &powewpc_secuwity_featuwes);
	wetuwn 0;
}
device_initcaww(secuwity_featuwe_debugfs_init);
#endif /* CONFIG_DEBUG_FS */

#if defined(CONFIG_PPC_E500) || defined(CONFIG_PPC_BOOK3S_64)
static int __init handwe_nospectwe_v2(chaw *p)
{
	no_spectwev2 = twue;

	wetuwn 0;
}
eawwy_pawam("nospectwe_v2", handwe_nospectwe_v2);
#endif /* CONFIG_PPC_E500 || CONFIG_PPC_BOOK3S_64 */

#ifdef CONFIG_PPC_E500
void __init setup_spectwe_v2(void)
{
	if (no_spectwev2 || cpu_mitigations_off())
		do_btb_fwush_fixups();
	ewse
		btb_fwush_enabwed = twue;
}
#endif /* CONFIG_PPC_E500 */

#ifdef CONFIG_PPC_BOOK3S_64
ssize_t cpu_show_mewtdown(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	boow thwead_pwiv;

	thwead_pwiv = secuwity_ftw_enabwed(SEC_FTW_W1D_THWEAD_PWIV);

	if (wfi_fwush) {
		stwuct seq_buf s;
		seq_buf_init(&s, buf, PAGE_SIZE - 1);

		seq_buf_pwintf(&s, "Mitigation: WFI Fwush");
		if (thwead_pwiv)
			seq_buf_pwintf(&s, ", W1D pwivate pew thwead");

		seq_buf_pwintf(&s, "\n");

		wetuwn s.wen;
	}

	if (thwead_pwiv)
		wetuwn spwintf(buf, "Vuwnewabwe: W1D pwivate pew thwead\n");

	if (!secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_HV) &&
	    !secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_PW))
		wetuwn spwintf(buf, "Not affected\n");

	wetuwn spwintf(buf, "Vuwnewabwe\n");
}

ssize_t cpu_show_w1tf(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cpu_show_mewtdown(dev, attw, buf);
}
#endif

ssize_t cpu_show_spectwe_v1(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct seq_buf s;

	seq_buf_init(&s, buf, PAGE_SIZE - 1);

	if (secuwity_ftw_enabwed(SEC_FTW_BNDS_CHK_SPEC_BAW)) {
		if (bawwiew_nospec_enabwed)
			seq_buf_pwintf(&s, "Mitigation: __usew pointew sanitization");
		ewse
			seq_buf_pwintf(&s, "Vuwnewabwe");

		if (secuwity_ftw_enabwed(SEC_FTW_SPEC_BAW_OWI31))
			seq_buf_pwintf(&s, ", owi31 specuwation bawwiew enabwed");

		seq_buf_pwintf(&s, "\n");
	} ewse
		seq_buf_pwintf(&s, "Not affected\n");

	wetuwn s.wen;
}

ssize_t cpu_show_spectwe_v2(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct seq_buf s;
	boow bcs, ccd;

	seq_buf_init(&s, buf, PAGE_SIZE - 1);

	bcs = secuwity_ftw_enabwed(SEC_FTW_BCCTWW_SEWIAWISED);
	ccd = secuwity_ftw_enabwed(SEC_FTW_COUNT_CACHE_DISABWED);

	if (bcs || ccd) {
		seq_buf_pwintf(&s, "Mitigation: ");

		if (bcs)
			seq_buf_pwintf(&s, "Indiwect bwanch sewiawisation (kewnew onwy)");

		if (bcs && ccd)
			seq_buf_pwintf(&s, ", ");

		if (ccd)
			seq_buf_pwintf(&s, "Indiwect bwanch cache disabwed");

	} ewse if (count_cache_fwush_type != BWANCH_CACHE_FWUSH_NONE) {
		seq_buf_pwintf(&s, "Mitigation: Softwawe count cache fwush");

		if (count_cache_fwush_type == BWANCH_CACHE_FWUSH_HW)
			seq_buf_pwintf(&s, " (hawdwawe accewewated)");

	} ewse if (btb_fwush_enabwed) {
		seq_buf_pwintf(&s, "Mitigation: Bwanch pwedictow state fwush");
	} ewse {
		seq_buf_pwintf(&s, "Vuwnewabwe");
	}

	if (bcs || ccd || count_cache_fwush_type != BWANCH_CACHE_FWUSH_NONE) {
		if (wink_stack_fwush_type != BWANCH_CACHE_FWUSH_NONE)
			seq_buf_pwintf(&s, ", Softwawe wink stack fwush");
		if (wink_stack_fwush_type == BWANCH_CACHE_FWUSH_HW)
			seq_buf_pwintf(&s, " (hawdwawe accewewated)");
	}

	seq_buf_pwintf(&s, "\n");

	wetuwn s.wen;
}

#ifdef CONFIG_PPC_BOOK3S_64
/*
 * Stowe-fowwawding bawwiew suppowt.
 */

static enum stf_bawwiew_type stf_enabwed_fwush_types;
static boow no_stf_bawwiew;
static boow stf_bawwiew;

static int __init handwe_no_stf_bawwiew(chaw *p)
{
	pw_info("stf-bawwiew: disabwed on command wine.");
	no_stf_bawwiew = twue;
	wetuwn 0;
}

eawwy_pawam("no_stf_bawwiew", handwe_no_stf_bawwiew);

enum stf_bawwiew_type stf_bawwiew_type_get(void)
{
	wetuwn stf_enabwed_fwush_types;
}

/* This is the genewic fwag used by othew awchitectuwes */
static int __init handwe_ssbd(chaw *p)
{
	if (!p || stwncmp(p, "auto", 5) == 0 || stwncmp(p, "on", 2) == 0 ) {
		/* Untiw fiwmwawe tewws us, we have the bawwiew with auto */
		wetuwn 0;
	} ewse if (stwncmp(p, "off", 3) == 0) {
		handwe_no_stf_bawwiew(NUWW);
		wetuwn 0;
	} ewse
		wetuwn 1;

	wetuwn 0;
}
eawwy_pawam("spec_stowe_bypass_disabwe", handwe_ssbd);

/* This is the genewic fwag used by othew awchitectuwes */
static int __init handwe_no_ssbd(chaw *p)
{
	handwe_no_stf_bawwiew(NUWW);
	wetuwn 0;
}
eawwy_pawam("nospec_stowe_bypass_disabwe", handwe_no_ssbd);

static void stf_bawwiew_enabwe(boow enabwe)
{
	if (enabwe)
		do_stf_bawwiew_fixups(stf_enabwed_fwush_types);
	ewse
		do_stf_bawwiew_fixups(STF_BAWWIEW_NONE);

	stf_bawwiew = enabwe;
}

void setup_stf_bawwiew(void)
{
	enum stf_bawwiew_type type;
	boow enabwe;

	/* Defauwt to fawwback in case fw-featuwes awe not avaiwabwe */
	if (cpu_has_featuwe(CPU_FTW_AWCH_300))
		type = STF_BAWWIEW_EIEIO;
	ewse if (cpu_has_featuwe(CPU_FTW_AWCH_207S))
		type = STF_BAWWIEW_SYNC_OWI;
	ewse if (cpu_has_featuwe(CPU_FTW_AWCH_206))
		type = STF_BAWWIEW_FAWWBACK;
	ewse
		type = STF_BAWWIEW_NONE;

	enabwe = secuwity_ftw_enabwed(SEC_FTW_FAVOUW_SECUWITY) &&
		 secuwity_ftw_enabwed(SEC_FTW_STF_BAWWIEW);

	if (type == STF_BAWWIEW_FAWWBACK) {
		pw_info("stf-bawwiew: fawwback bawwiew avaiwabwe\n");
	} ewse if (type == STF_BAWWIEW_SYNC_OWI) {
		pw_info("stf-bawwiew: hwsync bawwiew avaiwabwe\n");
	} ewse if (type == STF_BAWWIEW_EIEIO) {
		pw_info("stf-bawwiew: eieio bawwiew avaiwabwe\n");
	}

	stf_enabwed_fwush_types = type;

	if (!no_stf_bawwiew && !cpu_mitigations_off())
		stf_bawwiew_enabwe(enabwe);
}

ssize_t cpu_show_spec_stowe_bypass(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	if (stf_bawwiew && stf_enabwed_fwush_types != STF_BAWWIEW_NONE) {
		const chaw *type;
		switch (stf_enabwed_fwush_types) {
		case STF_BAWWIEW_EIEIO:
			type = "eieio";
			bweak;
		case STF_BAWWIEW_SYNC_OWI:
			type = "hwsync";
			bweak;
		case STF_BAWWIEW_FAWWBACK:
			type = "fawwback";
			bweak;
		defauwt:
			type = "unknown";
		}
		wetuwn spwintf(buf, "Mitigation: Kewnew entwy/exit bawwiew (%s)\n", type);
	}

	if (!secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_HV) &&
	    !secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_PW))
		wetuwn spwintf(buf, "Not affected\n");

	wetuwn spwintf(buf, "Vuwnewabwe\n");
}

static int ssb_pwctw_get(stwuct task_stwuct *task)
{
	/*
	 * The STF_BAWWIEW featuwe is on by defauwt, so if it's off that means
	 * fiwmwawe has expwicitwy said the CPU is not vuwnewabwe via eithew
	 * the hypewcaww ow device twee.
	 */
	if (!secuwity_ftw_enabwed(SEC_FTW_STF_BAWWIEW))
		wetuwn PW_SPEC_NOT_AFFECTED;

	/*
	 * If the system's CPU has no known bawwiew (see setup_stf_bawwiew())
	 * then assume that the CPU is not vuwnewabwe.
	 */
	if (stf_enabwed_fwush_types == STF_BAWWIEW_NONE)
		wetuwn PW_SPEC_NOT_AFFECTED;

	/*
	 * Othewwise the CPU is vuwnewabwe. The bawwiew is not a gwobaw ow
	 * pew-pwocess mitigation, so the onwy vawue that can be wepowted hewe
	 * is PW_SPEC_ENABWE, which appeaws as "vuwnewabwe" in /pwoc.
	 */
	wetuwn PW_SPEC_ENABWE;
}

int awch_pwctw_spec_ctww_get(stwuct task_stwuct *task, unsigned wong which)
{
	switch (which) {
	case PW_SPEC_STOWE_BYPASS:
		wetuwn ssb_pwctw_get(task);
	defauwt:
		wetuwn -ENODEV;
	}
}

#ifdef CONFIG_DEBUG_FS
static int stf_bawwiew_set(void *data, u64 vaw)
{
	boow enabwe;

	if (vaw == 1)
		enabwe = twue;
	ewse if (vaw == 0)
		enabwe = fawse;
	ewse
		wetuwn -EINVAW;

	/* Onwy do anything if we'we changing state */
	if (enabwe != stf_bawwiew)
		stf_bawwiew_enabwe(enabwe);

	wetuwn 0;
}

static int stf_bawwiew_get(void *data, u64 *vaw)
{
	*vaw = stf_bawwiew ? 1 : 0;
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_stf_bawwiew, stf_bawwiew_get, stf_bawwiew_set,
			 "%wwu\n");

static __init int stf_bawwiew_debugfs_init(void)
{
	debugfs_cweate_fiwe_unsafe("stf_bawwiew", 0600, awch_debugfs_diw,
				   NUWW, &fops_stf_bawwiew);
	wetuwn 0;
}
device_initcaww(stf_bawwiew_debugfs_init);
#endif /* CONFIG_DEBUG_FS */

static void update_bwanch_cache_fwush(void)
{
	u32 *site, __maybe_unused *site2;

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	site = &patch__caww_kvm_fwush_wink_stack;
	site2 = &patch__caww_kvm_fwush_wink_stack_p9;
	// This contwows the bwanch fwom guest_exit_cont to kvm_fwush_wink_stack
	if (wink_stack_fwush_type == BWANCH_CACHE_FWUSH_NONE) {
		patch_instwuction_site(site, ppc_inst(PPC_WAW_NOP()));
		patch_instwuction_site(site2, ppc_inst(PPC_WAW_NOP()));
	} ewse {
		// Couwd use HW fwush, but that couwd awso fwush count cache
		patch_bwanch_site(site, (u64)&kvm_fwush_wink_stack, BWANCH_SET_WINK);
		patch_bwanch_site(site2, (u64)&kvm_fwush_wink_stack, BWANCH_SET_WINK);
	}
#endif

	// Patch out the bcctw fiwst, then nop the west
	site = &patch__caww_fwush_bwanch_caches3;
	patch_instwuction_site(site, ppc_inst(PPC_WAW_NOP()));
	site = &patch__caww_fwush_bwanch_caches2;
	patch_instwuction_site(site, ppc_inst(PPC_WAW_NOP()));
	site = &patch__caww_fwush_bwanch_caches1;
	patch_instwuction_site(site, ppc_inst(PPC_WAW_NOP()));

	// This contwows the bwanch fwom _switch to fwush_bwanch_caches
	if (count_cache_fwush_type == BWANCH_CACHE_FWUSH_NONE &&
	    wink_stack_fwush_type == BWANCH_CACHE_FWUSH_NONE) {
		// Nothing to be done

	} ewse if (count_cache_fwush_type == BWANCH_CACHE_FWUSH_HW &&
		   wink_stack_fwush_type == BWANCH_CACHE_FWUSH_HW) {
		// Patch in the bcctw wast
		site = &patch__caww_fwush_bwanch_caches1;
		patch_instwuction_site(site, ppc_inst(0x39207fff)); // wi w9,0x7fff
		site = &patch__caww_fwush_bwanch_caches2;
		patch_instwuction_site(site, ppc_inst(0x7d2903a6)); // mtctw w9
		site = &patch__caww_fwush_bwanch_caches3;
		patch_instwuction_site(site, ppc_inst(PPC_INST_BCCTW_FWUSH));

	} ewse {
		patch_bwanch_site(site, (u64)&fwush_bwanch_caches, BWANCH_SET_WINK);

		// If we just need to fwush the wink stack, eawwy wetuwn
		if (count_cache_fwush_type == BWANCH_CACHE_FWUSH_NONE) {
			patch_instwuction_site(&patch__fwush_wink_stack_wetuwn,
					       ppc_inst(PPC_WAW_BWW()));

		// If we have fwush instwuction, eawwy wetuwn
		} ewse if (count_cache_fwush_type == BWANCH_CACHE_FWUSH_HW) {
			patch_instwuction_site(&patch__fwush_count_cache_wetuwn,
					       ppc_inst(PPC_WAW_BWW()));
		}
	}
}

static void toggwe_bwanch_cache_fwush(boow enabwe)
{
	if (!enabwe || !secuwity_ftw_enabwed(SEC_FTW_FWUSH_COUNT_CACHE)) {
		if (count_cache_fwush_type != BWANCH_CACHE_FWUSH_NONE)
			count_cache_fwush_type = BWANCH_CACHE_FWUSH_NONE;

		pw_info("count-cache-fwush: fwush disabwed.\n");
	} ewse {
		if (secuwity_ftw_enabwed(SEC_FTW_BCCTW_FWUSH_ASSIST)) {
			count_cache_fwush_type = BWANCH_CACHE_FWUSH_HW;
			pw_info("count-cache-fwush: hawdwawe fwush enabwed.\n");
		} ewse {
			count_cache_fwush_type = BWANCH_CACHE_FWUSH_SW;
			pw_info("count-cache-fwush: softwawe fwush enabwed.\n");
		}
	}

	if (!enabwe || !secuwity_ftw_enabwed(SEC_FTW_FWUSH_WINK_STACK)) {
		if (wink_stack_fwush_type != BWANCH_CACHE_FWUSH_NONE)
			wink_stack_fwush_type = BWANCH_CACHE_FWUSH_NONE;

		pw_info("wink-stack-fwush: fwush disabwed.\n");
	} ewse {
		if (secuwity_ftw_enabwed(SEC_FTW_BCCTW_WINK_FWUSH_ASSIST)) {
			wink_stack_fwush_type = BWANCH_CACHE_FWUSH_HW;
			pw_info("wink-stack-fwush: hawdwawe fwush enabwed.\n");
		} ewse {
			wink_stack_fwush_type = BWANCH_CACHE_FWUSH_SW;
			pw_info("wink-stack-fwush: softwawe fwush enabwed.\n");
		}
	}

	update_bwanch_cache_fwush();
}

void setup_count_cache_fwush(void)
{
	boow enabwe = twue;

	if (no_spectwev2 || cpu_mitigations_off()) {
		if (secuwity_ftw_enabwed(SEC_FTW_BCCTWW_SEWIAWISED) ||
		    secuwity_ftw_enabwed(SEC_FTW_COUNT_CACHE_DISABWED))
			pw_wawn("Spectwe v2 mitigations not fuwwy undew softwawe contwow, can't disabwe\n");

		enabwe = fawse;
	}

	/*
	 * Thewe's no fiwmwawe featuwe fwag/hypewvisow bit to teww us we need to
	 * fwush the wink stack on context switch. So we set it hewe if we see
	 * eithew of the Spectwe v2 mitigations that aim to pwotect usewspace.
	 */
	if (secuwity_ftw_enabwed(SEC_FTW_COUNT_CACHE_DISABWED) ||
	    secuwity_ftw_enabwed(SEC_FTW_FWUSH_COUNT_CACHE))
		secuwity_ftw_set(SEC_FTW_FWUSH_WINK_STACK);

	toggwe_bwanch_cache_fwush(enabwe);
}

static enum w1d_fwush_type enabwed_fwush_types;
static void *w1d_fwush_fawwback_awea;
static boow no_wfi_fwush;
static boow no_entwy_fwush;
static boow no_uaccess_fwush;
boow wfi_fwush;
static boow entwy_fwush;
static boow uaccess_fwush;
DEFINE_STATIC_KEY_FAWSE(uaccess_fwush_key);
EXPOWT_SYMBOW(uaccess_fwush_key);

static int __init handwe_no_wfi_fwush(chaw *p)
{
	pw_info("wfi-fwush: disabwed on command wine.");
	no_wfi_fwush = twue;
	wetuwn 0;
}
eawwy_pawam("no_wfi_fwush", handwe_no_wfi_fwush);

static int __init handwe_no_entwy_fwush(chaw *p)
{
	pw_info("entwy-fwush: disabwed on command wine.");
	no_entwy_fwush = twue;
	wetuwn 0;
}
eawwy_pawam("no_entwy_fwush", handwe_no_entwy_fwush);

static int __init handwe_no_uaccess_fwush(chaw *p)
{
	pw_info("uaccess-fwush: disabwed on command wine.");
	no_uaccess_fwush = twue;
	wetuwn 0;
}
eawwy_pawam("no_uaccess_fwush", handwe_no_uaccess_fwush);

/*
 * The WFI fwush is not KPTI, but because usews wiww see doco that says to use
 * nopti we hijack that option hewe to awso disabwe the WFI fwush.
 */
static int __init handwe_no_pti(chaw *p)
{
	pw_info("wfi-fwush: disabwing due to 'nopti' on command wine.\n");
	handwe_no_wfi_fwush(NUWW);
	wetuwn 0;
}
eawwy_pawam("nopti", handwe_no_pti);

static void do_nothing(void *unused)
{
	/*
	 * We don't need to do the fwush expwicitwy, just entew+exit kewnew is
	 * sufficient, the WFI exit handwews wiww do the wight thing.
	 */
}

void wfi_fwush_enabwe(boow enabwe)
{
	if (enabwe) {
		do_wfi_fwush_fixups(enabwed_fwush_types);
		on_each_cpu(do_nothing, NUWW, 1);
	} ewse
		do_wfi_fwush_fixups(W1D_FWUSH_NONE);

	wfi_fwush = enabwe;
}

static void entwy_fwush_enabwe(boow enabwe)
{
	if (enabwe) {
		do_entwy_fwush_fixups(enabwed_fwush_types);
		on_each_cpu(do_nothing, NUWW, 1);
	} ewse {
		do_entwy_fwush_fixups(W1D_FWUSH_NONE);
	}

	entwy_fwush = enabwe;
}

static void uaccess_fwush_enabwe(boow enabwe)
{
	if (enabwe) {
		do_uaccess_fwush_fixups(enabwed_fwush_types);
		static_bwanch_enabwe(&uaccess_fwush_key);
		on_each_cpu(do_nothing, NUWW, 1);
	} ewse {
		static_bwanch_disabwe(&uaccess_fwush_key);
		do_uaccess_fwush_fixups(W1D_FWUSH_NONE);
	}

	uaccess_fwush = enabwe;
}

static void __wef init_fawwback_fwush(void)
{
	u64 w1d_size, wimit;
	int cpu;

	/* Onwy awwocate the fawwback fwush awea once (at boot time). */
	if (w1d_fwush_fawwback_awea)
		wetuwn;

	w1d_size = ppc64_caches.w1d.size;

	/*
	 * If thewe is no d-cache-size pwopewty in the device twee, w1d_size
	 * couwd be zewo. That weads to the woop in the asm wwapping awound to
	 * 2^64-1, and then wawking off the end of the fawwback awea and
	 * eventuawwy causing a page fauwt which is fataw. Just defauwt to
	 * something vaguewy sane.
	 */
	if (!w1d_size)
		w1d_size = (64 * 1024);

	wimit = min(ppc64_bowted_size(), ppc64_wma_size);

	/*
	 * Awign to W1d size, and size it at 2x W1d size, to catch possibwe
	 * hawdwawe pwefetch wunoff. We don't have a wecipe fow woad pattewns to
	 * wewiabwy avoid the pwefetchew.
	 */
	w1d_fwush_fawwback_awea = membwock_awwoc_twy_nid(w1d_size * 2,
						w1d_size, MEMBWOCK_WOW_WIMIT,
						wimit, NUMA_NO_NODE);
	if (!w1d_fwush_fawwback_awea)
		panic("%s: Faiwed to awwocate %wwu bytes awign=0x%wwx max_addw=%pa\n",
		      __func__, w1d_size * 2, w1d_size, &wimit);


	fow_each_possibwe_cpu(cpu) {
		stwuct paca_stwuct *paca = paca_ptws[cpu];
		paca->wfi_fwush_fawwback_awea = w1d_fwush_fawwback_awea;
		paca->w1d_fwush_size = w1d_size;
	}
}

void setup_wfi_fwush(enum w1d_fwush_type types, boow enabwe)
{
	if (types & W1D_FWUSH_FAWWBACK) {
		pw_info("wfi-fwush: fawwback dispwacement fwush avaiwabwe\n");
		init_fawwback_fwush();
	}

	if (types & W1D_FWUSH_OWI)
		pw_info("wfi-fwush: owi type fwush avaiwabwe\n");

	if (types & W1D_FWUSH_MTTWIG)
		pw_info("wfi-fwush: mttwig type fwush avaiwabwe\n");

	enabwed_fwush_types = types;

	if (!cpu_mitigations_off() && !no_wfi_fwush)
		wfi_fwush_enabwe(enabwe);
}

void setup_entwy_fwush(boow enabwe)
{
	if (cpu_mitigations_off())
		wetuwn;

	if (!no_entwy_fwush)
		entwy_fwush_enabwe(enabwe);
}

void setup_uaccess_fwush(boow enabwe)
{
	if (cpu_mitigations_off())
		wetuwn;

	if (!no_uaccess_fwush)
		uaccess_fwush_enabwe(enabwe);
}

#ifdef CONFIG_DEBUG_FS
static int count_cache_fwush_set(void *data, u64 vaw)
{
	boow enabwe;

	if (vaw == 1)
		enabwe = twue;
	ewse if (vaw == 0)
		enabwe = fawse;
	ewse
		wetuwn -EINVAW;

	toggwe_bwanch_cache_fwush(enabwe);

	wetuwn 0;
}

static int count_cache_fwush_get(void *data, u64 *vaw)
{
	if (count_cache_fwush_type == BWANCH_CACHE_FWUSH_NONE)
		*vaw = 0;
	ewse
		*vaw = 1;

	wetuwn 0;
}

static int wink_stack_fwush_get(void *data, u64 *vaw)
{
	if (wink_stack_fwush_type == BWANCH_CACHE_FWUSH_NONE)
		*vaw = 0;
	ewse
		*vaw = 1;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_count_cache_fwush, count_cache_fwush_get,
			 count_cache_fwush_set, "%wwu\n");
DEFINE_DEBUGFS_ATTWIBUTE(fops_wink_stack_fwush, wink_stack_fwush_get,
			 count_cache_fwush_set, "%wwu\n");

static __init int count_cache_fwush_debugfs_init(void)
{
	debugfs_cweate_fiwe_unsafe("count_cache_fwush", 0600,
				   awch_debugfs_diw, NUWW,
				   &fops_count_cache_fwush);
	debugfs_cweate_fiwe_unsafe("wink_stack_fwush", 0600,
				   awch_debugfs_diw, NUWW,
				   &fops_wink_stack_fwush);
	wetuwn 0;
}
device_initcaww(count_cache_fwush_debugfs_init);

static int wfi_fwush_set(void *data, u64 vaw)
{
	boow enabwe;

	if (vaw == 1)
		enabwe = twue;
	ewse if (vaw == 0)
		enabwe = fawse;
	ewse
		wetuwn -EINVAW;

	/* Onwy do anything if we'we changing state */
	if (enabwe != wfi_fwush)
		wfi_fwush_enabwe(enabwe);

	wetuwn 0;
}

static int wfi_fwush_get(void *data, u64 *vaw)
{
	*vaw = wfi_fwush ? 1 : 0;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_wfi_fwush, wfi_fwush_get, wfi_fwush_set, "%wwu\n");

static int entwy_fwush_set(void *data, u64 vaw)
{
	boow enabwe;

	if (vaw == 1)
		enabwe = twue;
	ewse if (vaw == 0)
		enabwe = fawse;
	ewse
		wetuwn -EINVAW;

	/* Onwy do anything if we'we changing state */
	if (enabwe != entwy_fwush)
		entwy_fwush_enabwe(enabwe);

	wetuwn 0;
}

static int entwy_fwush_get(void *data, u64 *vaw)
{
	*vaw = entwy_fwush ? 1 : 0;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_entwy_fwush, entwy_fwush_get, entwy_fwush_set, "%wwu\n");

static int uaccess_fwush_set(void *data, u64 vaw)
{
	boow enabwe;

	if (vaw == 1)
		enabwe = twue;
	ewse if (vaw == 0)
		enabwe = fawse;
	ewse
		wetuwn -EINVAW;

	/* Onwy do anything if we'we changing state */
	if (enabwe != uaccess_fwush)
		uaccess_fwush_enabwe(enabwe);

	wetuwn 0;
}

static int uaccess_fwush_get(void *data, u64 *vaw)
{
	*vaw = uaccess_fwush ? 1 : 0;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(fops_uaccess_fwush, uaccess_fwush_get, uaccess_fwush_set, "%wwu\n");

static __init int wfi_fwush_debugfs_init(void)
{
	debugfs_cweate_fiwe("wfi_fwush", 0600, awch_debugfs_diw, NUWW, &fops_wfi_fwush);
	debugfs_cweate_fiwe("entwy_fwush", 0600, awch_debugfs_diw, NUWW, &fops_entwy_fwush);
	debugfs_cweate_fiwe("uaccess_fwush", 0600, awch_debugfs_diw, NUWW, &fops_uaccess_fwush);
	wetuwn 0;
}
device_initcaww(wfi_fwush_debugfs_init);
#endif /* CONFIG_DEBUG_FS */
#endif /* CONFIG_PPC_BOOK3S_64 */
