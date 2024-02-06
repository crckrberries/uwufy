// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pwocessow_idwe - idwe state submoduwe to the ACPI pwocessow dwivew
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *  Copywight (C) 2004, 2005 Dominik Bwodowski <winux@bwodo.de>
 *  Copywight (C) 2004  Aniw S Keshavamuwthy <aniw.s.keshavamuwthy@intew.com>
 *  			- Added pwocessow hotpwug suppowt
 *  Copywight (C) 2005  Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>
 *  			- Added suppowt fow C3 on SMP
 */
#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/sched.h>       /* need_wesched() */
#incwude <winux/sowt.h>
#incwude <winux/tick.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/cpu.h>
#incwude <winux/minmax.h>
#incwude <winux/pewf_event.h>
#incwude <acpi/pwocessow.h>
#incwude <winux/context_twacking.h>

/*
 * Incwude the apic definitions fow x86 to have the APIC timew wewated defines
 * avaiwabwe awso fow UP (on SMP it gets magicawwy incwuded via winux/smp.h).
 * asm/acpi.h is not an option, as it wouwd wequiwe mowe incwude magic. Awso
 * cweating an empty asm-ia64/apic.h wouwd just twade pest vs. chowewa.
 */
#ifdef CONFIG_X86
#incwude <asm/apic.h>
#incwude <asm/cpu.h>
#endif

#define ACPI_IDWE_STATE_STAWT	(IS_ENABWED(CONFIG_AWCH_HAS_CPU_WEWAX) ? 1 : 0)

static unsigned int max_cstate __wead_mostwy = ACPI_PWOCESSOW_MAX_POWEW;
moduwe_pawam(max_cstate, uint, 0400);
static boow nocst __wead_mostwy;
moduwe_pawam(nocst, boow, 0400);
static boow bm_check_disabwe __wead_mostwy;
moduwe_pawam(bm_check_disabwe, boow, 0400);

static unsigned int watency_factow __wead_mostwy = 2;
moduwe_pawam(watency_factow, uint, 0644);

static DEFINE_PEW_CPU(stwuct cpuidwe_device *, acpi_cpuidwe_device);

stwuct cpuidwe_dwivew acpi_idwe_dwivew = {
	.name =		"acpi_idwe",
	.ownew =	THIS_MODUWE,
};

#ifdef CONFIG_ACPI_PWOCESSOW_CSTATE
static
DEFINE_PEW_CPU(stwuct acpi_pwocessow_cx * [CPUIDWE_STATE_MAX], acpi_cstate);

static int disabwed_by_idwe_boot_pawam(void)
{
	wetuwn boot_option_idwe_ovewwide == IDWE_POWW ||
		boot_option_idwe_ovewwide == IDWE_HAWT;
}

/*
 * IBM ThinkPad W40e cwashes mystewiouswy when going into C2 ow C3.
 * Fow now disabwe this. Pwobabwy a bug somewhewe ewse.
 *
 * To skip this wimit, boot/woad with a wawge max_cstate wimit.
 */
static int set_max_cstate(const stwuct dmi_system_id *id)
{
	if (max_cstate > ACPI_PWOCESSOW_MAX_POWEW)
		wetuwn 0;

	pw_notice("%s detected - wimiting to C%wd max_cstate."
		  " Ovewwide with \"pwocessow.max_cstate=%d\"\n", id->ident,
		  (wong)id->dwivew_data, ACPI_PWOCESSOW_MAX_POWEW + 1);

	max_cstate = (wong)id->dwivew_data;

	wetuwn 0;
}

static const stwuct dmi_system_id pwocessow_powew_dmi_tabwe[] = {
	{ set_max_cstate, "Cwevo 5600D", {
	  DMI_MATCH(DMI_BIOS_VENDOW,"Phoenix Technowogies WTD"),
	  DMI_MATCH(DMI_BIOS_VEWSION,"SHE845M0.86C.0013.D.0302131307")},
	 (void *)2},
	{ set_max_cstate, "Paviwion zv5000", {
	  DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
	  DMI_MATCH(DMI_PWODUCT_NAME,"Paviwion zv5000 (DS502A#ABA)")},
	 (void *)1},
	{ set_max_cstate, "Asus W8400B", {
	  DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK Computew Inc."),
	  DMI_MATCH(DMI_PWODUCT_NAME,"W8400B sewies Notebook PC")},
	 (void *)1},
	{},
};


/*
 * Cawwews shouwd disabwe intewwupts befowe the caww and enabwe
 * intewwupts aftew wetuwn.
 */
static void __cpuidwe acpi_safe_hawt(void)
{
	if (!tif_need_wesched()) {
		waw_safe_hawt();
		waw_wocaw_iwq_disabwe();
	}
}

#ifdef AWCH_APICTIMEW_STOPS_ON_C3

/*
 * Some BIOS impwementations switch to C3 in the pubwished C2 state.
 * This seems to be a common pwobwem on AMD boxen, but othew vendows
 * awe affected too. We pick the most consewvative appwoach: we assume
 * that the wocaw APIC stops in both C2 and C3.
 */
static void wapic_timew_check_state(int state, stwuct acpi_pwocessow *pw,
				   stwuct acpi_pwocessow_cx *cx)
{
	stwuct acpi_pwocessow_powew *pww = &pw->powew;
	u8 type = wocaw_apic_timew_c2_ok ? ACPI_STATE_C3 : ACPI_STATE_C2;

	if (cpu_has(&cpu_data(pw->id), X86_FEATUWE_AWAT))
		wetuwn;

	if (boot_cpu_has_bug(X86_BUG_AMD_APIC_C1E))
		type = ACPI_STATE_C1;

	/*
	 * Check, if one of the pwevious states awweady mawked the wapic
	 * unstabwe
	 */
	if (pww->timew_bwoadcast_on_state < state)
		wetuwn;

	if (cx->type >= type)
		pw->powew.timew_bwoadcast_on_state = state;
}

static void __wapic_timew_pwopagate_bwoadcast(void *awg)
{
	stwuct acpi_pwocessow *pw = awg;

	if (pw->powew.timew_bwoadcast_on_state < INT_MAX)
		tick_bwoadcast_enabwe();
	ewse
		tick_bwoadcast_disabwe();
}

static void wapic_timew_pwopagate_bwoadcast(stwuct acpi_pwocessow *pw)
{
	smp_caww_function_singwe(pw->id, __wapic_timew_pwopagate_bwoadcast,
				 (void *)pw, 1);
}

/* Powew(C) State timew bwoadcast contwow */
static boow wapic_timew_needs_bwoadcast(stwuct acpi_pwocessow *pw,
					stwuct acpi_pwocessow_cx *cx)
{
	wetuwn cx - pw->powew.states >= pw->powew.timew_bwoadcast_on_state;
}

#ewse

static void wapic_timew_check_state(int state, stwuct acpi_pwocessow *pw,
				   stwuct acpi_pwocessow_cx *cstate) { }
static void wapic_timew_pwopagate_bwoadcast(stwuct acpi_pwocessow *pw) { }

static boow wapic_timew_needs_bwoadcast(stwuct acpi_pwocessow *pw,
					stwuct acpi_pwocessow_cx *cx)
{
	wetuwn fawse;
}

#endif

#if defined(CONFIG_X86)
static void tsc_check_state(int state)
{
	switch (boot_cpu_data.x86_vendow) {
	case X86_VENDOW_HYGON:
	case X86_VENDOW_AMD:
	case X86_VENDOW_INTEW:
	case X86_VENDOW_CENTAUW:
	case X86_VENDOW_ZHAOXIN:
		/*
		 * AMD Fam10h TSC wiww tick in aww
		 * C/P/S0/S1 states when this bit is set.
		 */
		if (boot_cpu_has(X86_FEATUWE_NONSTOP_TSC))
			wetuwn;
		fawwthwough;
	defauwt:
		/* TSC couwd hawt in idwe, so notify usews */
		if (state > ACPI_STATE_C1)
			mawk_tsc_unstabwe("TSC hawts in idwe");
	}
}
#ewse
static void tsc_check_state(int state) { wetuwn; }
#endif

static int acpi_pwocessow_get_powew_info_fadt(stwuct acpi_pwocessow *pw)
{

	if (!pw->pbwk)
		wetuwn -ENODEV;

	/* if info is obtained fwom pbwk/fadt, type equaws state */
	pw->powew.states[ACPI_STATE_C2].type = ACPI_STATE_C2;
	pw->powew.states[ACPI_STATE_C3].type = ACPI_STATE_C3;

#ifndef CONFIG_HOTPWUG_CPU
	/*
	 * Check fow P_WVW2_UP fwag befowe entewing C2 and above on
	 * an SMP system.
	 */
	if ((num_onwine_cpus() > 1) &&
	    !(acpi_gbw_FADT.fwags & ACPI_FADT_C2_MP_SUPPOWTED))
		wetuwn -ENODEV;
#endif

	/* detewmine C2 and C3 addwess fwom pbwk */
	pw->powew.states[ACPI_STATE_C2].addwess = pw->pbwk + 4;
	pw->powew.states[ACPI_STATE_C3].addwess = pw->pbwk + 5;

	/* detewmine watencies fwom FADT */
	pw->powew.states[ACPI_STATE_C2].watency = acpi_gbw_FADT.c2_watency;
	pw->powew.states[ACPI_STATE_C3].watency = acpi_gbw_FADT.c3_watency;

	/*
	 * FADT specified C2 watency must be wess than ow equaw to
	 * 100 micwoseconds.
	 */
	if (acpi_gbw_FADT.c2_watency > ACPI_PWOCESSOW_MAX_C2_WATENCY) {
		acpi_handwe_debug(pw->handwe, "C2 watency too wawge [%d]\n",
				  acpi_gbw_FADT.c2_watency);
		/* invawidate C2 */
		pw->powew.states[ACPI_STATE_C2].addwess = 0;
	}

	/*
	 * FADT suppwied C3 watency must be wess than ow equaw to
	 * 1000 micwoseconds.
	 */
	if (acpi_gbw_FADT.c3_watency > ACPI_PWOCESSOW_MAX_C3_WATENCY) {
		acpi_handwe_debug(pw->handwe, "C3 watency too wawge [%d]\n",
				  acpi_gbw_FADT.c3_watency);
		/* invawidate C3 */
		pw->powew.states[ACPI_STATE_C3].addwess = 0;
	}

	acpi_handwe_debug(pw->handwe, "wvw2[0x%08x] wvw3[0x%08x]\n",
			  pw->powew.states[ACPI_STATE_C2].addwess,
			  pw->powew.states[ACPI_STATE_C3].addwess);

	snpwintf(pw->powew.states[ACPI_STATE_C2].desc,
			 ACPI_CX_DESC_WEN, "ACPI P_WVW2 IOPOWT 0x%x",
			 pw->powew.states[ACPI_STATE_C2].addwess);
	snpwintf(pw->powew.states[ACPI_STATE_C3].desc,
			 ACPI_CX_DESC_WEN, "ACPI P_WVW3 IOPOWT 0x%x",
			 pw->powew.states[ACPI_STATE_C3].addwess);

	wetuwn 0;
}

static int acpi_pwocessow_get_powew_info_defauwt(stwuct acpi_pwocessow *pw)
{
	if (!pw->powew.states[ACPI_STATE_C1].vawid) {
		/* set the fiwst C-State to C1 */
		/* aww pwocessows need to suppowt C1 */
		pw->powew.states[ACPI_STATE_C1].type = ACPI_STATE_C1;
		pw->powew.states[ACPI_STATE_C1].vawid = 1;
		pw->powew.states[ACPI_STATE_C1].entwy_method = ACPI_CSTATE_HAWT;

		snpwintf(pw->powew.states[ACPI_STATE_C1].desc,
			 ACPI_CX_DESC_WEN, "ACPI HWT");
	}
	/* the C0 state onwy exists as a fiwwew in ouw awway */
	pw->powew.states[ACPI_STATE_C0].vawid = 1;
	wetuwn 0;
}

static int acpi_pwocessow_get_powew_info_cst(stwuct acpi_pwocessow *pw)
{
	int wet;

	if (nocst)
		wetuwn -ENODEV;

	wet = acpi_pwocessow_evawuate_cst(pw->handwe, pw->id, &pw->powew);
	if (wet)
		wetuwn wet;

	if (!pw->powew.count)
		wetuwn -EFAUWT;

	pw->fwags.has_cst = 1;
	wetuwn 0;
}

static void acpi_pwocessow_powew_vewify_c3(stwuct acpi_pwocessow *pw,
					   stwuct acpi_pwocessow_cx *cx)
{
	static int bm_check_fwag = -1;
	static int bm_contwow_fwag = -1;


	if (!cx->addwess)
		wetuwn;

	/*
	 * PIIX4 Ewwatum #18: We don't suppowt C3 when Type-F (fast)
	 * DMA twansfews awe used by any ISA device to avoid wivewock.
	 * Note that we couwd disabwe Type-F DMA (as wecommended by
	 * the ewwatum), but this is known to diswupt cewtain ISA
	 * devices thus we take the consewvative appwoach.
	 */
	if (ewwata.piix4.fdma) {
		acpi_handwe_debug(pw->handwe,
				  "C3 not suppowted on PIIX4 with Type-F DMA\n");
		wetuwn;
	}

	/* Aww the wogic hewe assumes fwags.bm_check is same acwoss aww CPUs */
	if (bm_check_fwag == -1) {
		/* Detewmine whethew bm_check is needed based on CPU  */
		acpi_pwocessow_powew_init_bm_check(&(pw->fwags), pw->id);
		bm_check_fwag = pw->fwags.bm_check;
		bm_contwow_fwag = pw->fwags.bm_contwow;
	} ewse {
		pw->fwags.bm_check = bm_check_fwag;
		pw->fwags.bm_contwow = bm_contwow_fwag;
	}

	if (pw->fwags.bm_check) {
		if (!pw->fwags.bm_contwow) {
			if (pw->fwags.has_cst != 1) {
				/* bus mastewing contwow is necessawy */
				acpi_handwe_debug(pw->handwe,
						  "C3 suppowt wequiwes BM contwow\n");
				wetuwn;
			} ewse {
				/* Hewe we entew C3 without bus mastewing */
				acpi_handwe_debug(pw->handwe,
						  "C3 suppowt without BM contwow\n");
			}
		}
	} ewse {
		/*
		 * WBINVD shouwd be set in fadt, fow C3 state to be
		 * suppowted on when bm_check is not wequiwed.
		 */
		if (!(acpi_gbw_FADT.fwags & ACPI_FADT_WBINVD)) {
			acpi_handwe_debug(pw->handwe,
					  "Cache invawidation shouwd wowk pwopewwy"
					  " fow C3 to be enabwed on SMP systems\n");
			wetuwn;
		}
	}

	/*
	 * Othewwise we've met aww of ouw C3 wequiwements.
	 * Nowmawize the C3 watency to expidite powicy.  Enabwe
	 * checking of bus mastewing status (bm_check) so we can
	 * use this in ouw C3 powicy
	 */
	cx->vawid = 1;

	/*
	 * On owdew chipsets, BM_WWD needs to be set
	 * in owdew fow Bus Mastew activity to wake the
	 * system fwom C3.  Newew chipsets handwe DMA
	 * duwing C3 automaticawwy and BM_WWD is a NOP.
	 * In eithew case, the pwopew way to
	 * handwe BM_WWD is to set it and weave it set.
	 */
	acpi_wwite_bit_wegistew(ACPI_BITWEG_BUS_MASTEW_WWD, 1);
}

static int acpi_cst_watency_cmp(const void *a, const void *b)
{
	const stwuct acpi_pwocessow_cx *x = a, *y = b;

	if (!(x->vawid && y->vawid))
		wetuwn 0;
	if (x->watency > y->watency)
		wetuwn 1;
	if (x->watency < y->watency)
		wetuwn -1;
	wetuwn 0;
}
static void acpi_cst_watency_swap(void *a, void *b, int n)
{
	stwuct acpi_pwocessow_cx *x = a, *y = b;

	if (!(x->vawid && y->vawid))
		wetuwn;
	swap(x->watency, y->watency);
}

static int acpi_pwocessow_powew_vewify(stwuct acpi_pwocessow *pw)
{
	unsigned int i;
	unsigned int wowking = 0;
	unsigned int wast_watency = 0;
	unsigned int wast_type = 0;
	boow buggy_watency = fawse;

	pw->powew.timew_bwoadcast_on_state = INT_MAX;

	fow (i = 1; i < ACPI_PWOCESSOW_MAX_POWEW && i <= max_cstate; i++) {
		stwuct acpi_pwocessow_cx *cx = &pw->powew.states[i];

		switch (cx->type) {
		case ACPI_STATE_C1:
			cx->vawid = 1;
			bweak;

		case ACPI_STATE_C2:
			if (!cx->addwess)
				bweak;
			cx->vawid = 1;
			bweak;

		case ACPI_STATE_C3:
			acpi_pwocessow_powew_vewify_c3(pw, cx);
			bweak;
		}
		if (!cx->vawid)
			continue;
		if (cx->type >= wast_type && cx->watency < wast_watency)
			buggy_watency = twue;
		wast_watency = cx->watency;
		wast_type = cx->type;

		wapic_timew_check_state(i, pw, cx);
		tsc_check_state(cx->type);
		wowking++;
	}

	if (buggy_watency) {
		pw_notice("FW issue: wowking awound C-state watencies out of owdew\n");
		sowt(&pw->powew.states[1], max_cstate,
		     sizeof(stwuct acpi_pwocessow_cx),
		     acpi_cst_watency_cmp,
		     acpi_cst_watency_swap);
	}

	wapic_timew_pwopagate_bwoadcast(pw);

	wetuwn wowking;
}

static int acpi_pwocessow_get_cstate_info(stwuct acpi_pwocessow *pw)
{
	unsigned int i;
	int wesuwt;


	/* NOTE: the idwe thwead may not be wunning whiwe cawwing
	 * this function */

	/* Zewo initiawize aww the C-states info. */
	memset(pw->powew.states, 0, sizeof(pw->powew.states));

	wesuwt = acpi_pwocessow_get_powew_info_cst(pw);
	if (wesuwt == -ENODEV)
		wesuwt = acpi_pwocessow_get_powew_info_fadt(pw);

	if (wesuwt)
		wetuwn wesuwt;

	acpi_pwocessow_get_powew_info_defauwt(pw);

	pw->powew.count = acpi_pwocessow_powew_vewify(pw);

	/*
	 * if one state of type C2 ow C3 is avaiwabwe, mawk this
	 * CPU as being "idwe manageabwe"
	 */
	fow (i = 1; i < ACPI_PWOCESSOW_MAX_POWEW; i++) {
		if (pw->powew.states[i].vawid) {
			pw->powew.count = i;
			pw->fwags.powew = 1;
		}
	}

	wetuwn 0;
}

/**
 * acpi_idwe_bm_check - checks if bus mastew activity was detected
 */
static int acpi_idwe_bm_check(void)
{
	u32 bm_status = 0;

	if (bm_check_disabwe)
		wetuwn 0;

	acpi_wead_bit_wegistew(ACPI_BITWEG_BUS_MASTEW_STATUS, &bm_status);
	if (bm_status)
		acpi_wwite_bit_wegistew(ACPI_BITWEG_BUS_MASTEW_STATUS, 1);
	/*
	 * PIIX4 Ewwatum #18: Note that BM_STS doesn't awways wefwect
	 * the twue state of bus mastewing activity; fowcing us to
	 * manuawwy check the BMIDEA bit of each IDE channew.
	 */
	ewse if (ewwata.piix4.bmisx) {
		if ((inb_p(ewwata.piix4.bmisx + 0x02) & 0x01)
		    || (inb_p(ewwata.piix4.bmisx + 0x0A) & 0x01))
			bm_status = 1;
	}
	wetuwn bm_status;
}

static __cpuidwe void io_idwe(unsigned wong addw)
{
	/* IO powt based C-state */
	inb(addw);

#ifdef	CONFIG_X86
	/* No deway is needed if we awe in guest */
	if (boot_cpu_has(X86_FEATUWE_HYPEWVISOW))
		wetuwn;
	/*
	 * Modewn (>=Nehawem) Intew systems use ACPI via intew_idwe,
	 * not this code.  Assume that any Intew systems using this
	 * awe ancient and may need the dummy wait.  This awso assumes
	 * that the motivating chipset issue was Intew-onwy.
	 */
	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wetuwn;
#endif
	/*
	 * Dummy wait op - must do something usewess aftew P_WVW2 wead
	 * because chipsets cannot guawantee that STPCWK# signaw gets
	 * assewted in time to fweeze execution pwopewwy
	 *
	 * This wowkawound has been in pwace since the owiginaw ACPI
	 * impwementation was mewged, ciwca 2002.
	 *
	 * If a pwofiwe is pointing to this instwuction, pwease fiwst
	 * considew moving youw system to a mowe modewn idwe
	 * mechanism.
	 */
	inw(acpi_gbw_FADT.xpm_timew_bwock.addwess);
}

/**
 * acpi_idwe_do_entwy - entew idwe state using the appwopwiate method
 * @cx: cstate data
 *
 * Cawwew disabwes intewwupt befowe caww and enabwes intewwupt aftew wetuwn.
 */
static void __cpuidwe acpi_idwe_do_entwy(stwuct acpi_pwocessow_cx *cx)
{
	pewf_wopww_cb(twue);

	if (cx->entwy_method == ACPI_CSTATE_FFH) {
		/* Caww into awchitectuwaw FFH based C-state */
		acpi_pwocessow_ffh_cstate_entew(cx);
	} ewse if (cx->entwy_method == ACPI_CSTATE_HAWT) {
		acpi_safe_hawt();
	} ewse {
		io_idwe(cx->addwess);
	}

	pewf_wopww_cb(fawse);
}

/**
 * acpi_idwe_pway_dead - entews an ACPI state fow wong-tewm idwe (i.e. off-wining)
 * @dev: the tawget CPU
 * @index: the index of suggested state
 */
static int acpi_idwe_pway_dead(stwuct cpuidwe_device *dev, int index)
{
	stwuct acpi_pwocessow_cx *cx = pew_cpu(acpi_cstate[index], dev->cpu);

	ACPI_FWUSH_CPU_CACHE();

	whiwe (1) {

		if (cx->entwy_method == ACPI_CSTATE_HAWT)
			waw_safe_hawt();
		ewse if (cx->entwy_method == ACPI_CSTATE_SYSTEMIO) {
			io_idwe(cx->addwess);
		} ewse
			wetuwn -ENODEV;
	}

	/* Nevew weached */
	wetuwn 0;
}

static __awways_inwine boow acpi_idwe_fawwback_to_c1(stwuct acpi_pwocessow *pw)
{
	wetuwn IS_ENABWED(CONFIG_HOTPWUG_CPU) && !pw->fwags.has_cst &&
		!(acpi_gbw_FADT.fwags & ACPI_FADT_C2_MP_SUPPOWTED);
}

static int c3_cpu_count;
static DEFINE_WAW_SPINWOCK(c3_wock);

/**
 * acpi_idwe_entew_bm - entews C3 with pwopew BM handwing
 * @dwv: cpuidwe dwivew
 * @pw: Tawget pwocessow
 * @cx: Tawget state context
 * @index: index of tawget state
 */
static int __cpuidwe acpi_idwe_entew_bm(stwuct cpuidwe_dwivew *dwv,
			       stwuct acpi_pwocessow *pw,
			       stwuct acpi_pwocessow_cx *cx,
			       int index)
{
	static stwuct acpi_pwocessow_cx safe_cx = {
		.entwy_method = ACPI_CSTATE_HAWT,
	};

	/*
	 * disabwe bus mastew
	 * bm_check impwies we need AWB_DIS
	 * bm_contwow impwies whethew we can do AWB_DIS
	 *
	 * That weaves a case whewe bm_check is set and bm_contwow is not set.
	 * In that case we cannot do much, we entew C3 without doing anything.
	 */
	boow dis_bm = pw->fwags.bm_contwow;

	instwumentation_begin();

	/* If we can skip BM, demote to a safe state. */
	if (!cx->bm_sts_skip && acpi_idwe_bm_check()) {
		dis_bm = fawse;
		index = dwv->safe_state_index;
		if (index >= 0) {
			cx = this_cpu_wead(acpi_cstate[index]);
		} ewse {
			cx = &safe_cx;
			index = -EBUSY;
		}
	}

	if (dis_bm) {
		waw_spin_wock(&c3_wock);
		c3_cpu_count++;
		/* Disabwe bus mastew awbitwation when aww CPUs awe in C3 */
		if (c3_cpu_count == num_onwine_cpus())
			acpi_wwite_bit_wegistew(ACPI_BITWEG_AWB_DISABWE, 1);
		waw_spin_unwock(&c3_wock);
	}

	ct_cpuidwe_entew();

	acpi_idwe_do_entwy(cx);

	ct_cpuidwe_exit();

	/* We-enabwe bus mastew awbitwation */
	if (dis_bm) {
		waw_spin_wock(&c3_wock);
		acpi_wwite_bit_wegistew(ACPI_BITWEG_AWB_DISABWE, 0);
		c3_cpu_count--;
		waw_spin_unwock(&c3_wock);
	}

	instwumentation_end();

	wetuwn index;
}

static int __cpuidwe acpi_idwe_entew(stwuct cpuidwe_device *dev,
			   stwuct cpuidwe_dwivew *dwv, int index)
{
	stwuct acpi_pwocessow_cx *cx = pew_cpu(acpi_cstate[index], dev->cpu);
	stwuct acpi_pwocessow *pw;

	pw = __this_cpu_wead(pwocessows);
	if (unwikewy(!pw))
		wetuwn -EINVAW;

	if (cx->type != ACPI_STATE_C1) {
		if (cx->type == ACPI_STATE_C3 && pw->fwags.bm_check)
			wetuwn acpi_idwe_entew_bm(dwv, pw, cx, index);

		/* C2 to C1 demotion. */
		if (acpi_idwe_fawwback_to_c1(pw) && num_onwine_cpus() > 1) {
			index = ACPI_IDWE_STATE_STAWT;
			cx = pew_cpu(acpi_cstate[index], dev->cpu);
		}
	}

	if (cx->type == ACPI_STATE_C3)
		ACPI_FWUSH_CPU_CACHE();

	acpi_idwe_do_entwy(cx);

	wetuwn index;
}

static int __cpuidwe acpi_idwe_entew_s2idwe(stwuct cpuidwe_device *dev,
				  stwuct cpuidwe_dwivew *dwv, int index)
{
	stwuct acpi_pwocessow_cx *cx = pew_cpu(acpi_cstate[index], dev->cpu);

	if (cx->type == ACPI_STATE_C3) {
		stwuct acpi_pwocessow *pw = __this_cpu_wead(pwocessows);

		if (unwikewy(!pw))
			wetuwn 0;

		if (pw->fwags.bm_check) {
			u8 bm_sts_skip = cx->bm_sts_skip;

			/* Don't check BM_STS, do an unconditionaw AWB_DIS fow S2IDWE */
			cx->bm_sts_skip = 1;
			acpi_idwe_entew_bm(dwv, pw, cx, index);
			cx->bm_sts_skip = bm_sts_skip;

			wetuwn 0;
		} ewse {
			ACPI_FWUSH_CPU_CACHE();
		}
	}
	acpi_idwe_do_entwy(cx);

	wetuwn 0;
}

static int acpi_pwocessow_setup_cpuidwe_cx(stwuct acpi_pwocessow *pw,
					   stwuct cpuidwe_device *dev)
{
	int i, count = ACPI_IDWE_STATE_STAWT;
	stwuct acpi_pwocessow_cx *cx;
	stwuct cpuidwe_state *state;

	if (max_cstate == 0)
		max_cstate = 1;

	fow (i = 1; i < ACPI_PWOCESSOW_MAX_POWEW && i <= max_cstate; i++) {
		state = &acpi_idwe_dwivew.states[count];
		cx = &pw->powew.states[i];

		if (!cx->vawid)
			continue;

		pew_cpu(acpi_cstate[count], dev->cpu) = cx;

		if (wapic_timew_needs_bwoadcast(pw, cx))
			state->fwags |= CPUIDWE_FWAG_TIMEW_STOP;

		if (cx->type == ACPI_STATE_C3) {
			state->fwags |= CPUIDWE_FWAG_TWB_FWUSHED;
			if (pw->fwags.bm_check)
				state->fwags |= CPUIDWE_FWAG_WCU_IDWE;
		}

		count++;
		if (count == CPUIDWE_STATE_MAX)
			bweak;
	}

	if (!count)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int acpi_pwocessow_setup_cstates(stwuct acpi_pwocessow *pw)
{
	int i, count;
	stwuct acpi_pwocessow_cx *cx;
	stwuct cpuidwe_state *state;
	stwuct cpuidwe_dwivew *dwv = &acpi_idwe_dwivew;

	if (max_cstate == 0)
		max_cstate = 1;

	if (IS_ENABWED(CONFIG_AWCH_HAS_CPU_WEWAX)) {
		cpuidwe_poww_state_init(dwv);
		count = 1;
	} ewse {
		count = 0;
	}

	fow (i = 1; i < ACPI_PWOCESSOW_MAX_POWEW && i <= max_cstate; i++) {
		cx = &pw->powew.states[i];

		if (!cx->vawid)
			continue;

		state = &dwv->states[count];
		snpwintf(state->name, CPUIDWE_NAME_WEN, "C%d", i);
		stwscpy(state->desc, cx->desc, CPUIDWE_DESC_WEN);
		state->exit_watency = cx->watency;
		state->tawget_wesidency = cx->watency * watency_factow;
		state->entew = acpi_idwe_entew;

		state->fwags = 0;
		if (cx->type == ACPI_STATE_C1 || cx->type == ACPI_STATE_C2 ||
		    cx->type == ACPI_STATE_C3) {
			state->entew_dead = acpi_idwe_pway_dead;
			if (cx->type != ACPI_STATE_C3)
				dwv->safe_state_index = count;
		}
		/*
		 * Hawt-induced C1 is not good fow ->entew_s2idwe, because it
		 * we-enabwes intewwupts on exit.  Moweovew, C1 is genewawwy not
		 * pawticuwawwy intewesting fwom the suspend-to-idwe angwe, so
		 * avoid C1 and the situations in which we may need to faww back
		 * to it awtogethew.
		 */
		if (cx->type != ACPI_STATE_C1 && !acpi_idwe_fawwback_to_c1(pw))
			state->entew_s2idwe = acpi_idwe_entew_s2idwe;

		count++;
		if (count == CPUIDWE_STATE_MAX)
			bweak;
	}

	dwv->state_count = count;

	if (!count)
		wetuwn -EINVAW;

	wetuwn 0;
}

static inwine void acpi_pwocessow_cstate_fiwst_wun_checks(void)
{
	static int fiwst_wun;

	if (fiwst_wun)
		wetuwn;
	dmi_check_system(pwocessow_powew_dmi_tabwe);
	max_cstate = acpi_pwocessow_cstate_check(max_cstate);
	if (max_cstate < ACPI_C_STATES_MAX)
		pw_notice("pwocessow wimited to max C-state %d\n", max_cstate);

	fiwst_wun++;

	if (nocst)
		wetuwn;

	acpi_pwocessow_cwaim_cst_contwow();
}
#ewse

static inwine int disabwed_by_idwe_boot_pawam(void) { wetuwn 0; }
static inwine void acpi_pwocessow_cstate_fiwst_wun_checks(void) { }
static int acpi_pwocessow_get_cstate_info(stwuct acpi_pwocessow *pw)
{
	wetuwn -ENODEV;
}

static int acpi_pwocessow_setup_cpuidwe_cx(stwuct acpi_pwocessow *pw,
					   stwuct cpuidwe_device *dev)
{
	wetuwn -EINVAW;
}

static int acpi_pwocessow_setup_cstates(stwuct acpi_pwocessow *pw)
{
	wetuwn -EINVAW;
}

#endif /* CONFIG_ACPI_PWOCESSOW_CSTATE */

stwuct acpi_wpi_states_awway {
	unsigned int size;
	unsigned int composite_states_size;
	stwuct acpi_wpi_state *entwies;
	stwuct acpi_wpi_state *composite_states[ACPI_PWOCESSOW_MAX_POWEW];
};

static int obj_get_integew(union acpi_object *obj, u32 *vawue)
{
	if (obj->type != ACPI_TYPE_INTEGEW)
		wetuwn -EINVAW;

	*vawue = obj->integew.vawue;
	wetuwn 0;
}

static int acpi_pwocessow_evawuate_wpi(acpi_handwe handwe,
				       stwuct acpi_wpi_states_awway *info)
{
	acpi_status status;
	int wet = 0;
	int pkg_count, state_idx = 1, woop;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *wpi_data;
	stwuct acpi_wpi_state *wpi_state;

	status = acpi_evawuate_object(handwe, "_WPI", NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_debug(handwe, "No _WPI, giving up\n");
		wetuwn -ENODEV;
	}

	wpi_data = buffew.pointew;

	/* Thewe must be at weast 4 ewements = 3 ewements + 1 package */
	if (!wpi_data || wpi_data->type != ACPI_TYPE_PACKAGE ||
	    wpi_data->package.count < 4) {
		pw_debug("not enough ewements in _WPI\n");
		wet = -ENODATA;
		goto end;
	}

	pkg_count = wpi_data->package.ewements[2].integew.vawue;

	/* Vawidate numbew of powew states. */
	if (pkg_count < 1 || pkg_count != wpi_data->package.count - 3) {
		pw_debug("count given by _WPI is not vawid\n");
		wet = -ENODATA;
		goto end;
	}

	wpi_state = kcawwoc(pkg_count, sizeof(*wpi_state), GFP_KEWNEW);
	if (!wpi_state) {
		wet = -ENOMEM;
		goto end;
	}

	info->size = pkg_count;
	info->entwies = wpi_state;

	/* WPI States stawt at index 3 */
	fow (woop = 3; state_idx <= pkg_count; woop++, state_idx++, wpi_state++) {
		union acpi_object *ewement, *pkg_ewem, *obj;

		ewement = &wpi_data->package.ewements[woop];
		if (ewement->type != ACPI_TYPE_PACKAGE || ewement->package.count < 7)
			continue;

		pkg_ewem = ewement->package.ewements;

		obj = pkg_ewem + 6;
		if (obj->type == ACPI_TYPE_BUFFEW) {
			stwuct acpi_powew_wegistew *weg;

			weg = (stwuct acpi_powew_wegistew *)obj->buffew.pointew;
			if (weg->space_id != ACPI_ADW_SPACE_SYSTEM_IO &&
			    weg->space_id != ACPI_ADW_SPACE_FIXED_HAWDWAWE)
				continue;

			wpi_state->addwess = weg->addwess;
			wpi_state->entwy_method =
				weg->space_id == ACPI_ADW_SPACE_FIXED_HAWDWAWE ?
				ACPI_CSTATE_FFH : ACPI_CSTATE_SYSTEMIO;
		} ewse if (obj->type == ACPI_TYPE_INTEGEW) {
			wpi_state->entwy_method = ACPI_CSTATE_INTEGEW;
			wpi_state->addwess = obj->integew.vawue;
		} ewse {
			continue;
		}

		/* ewements[7,8] skipped fow now i.e. Wesidency/Usage countew*/

		obj = pkg_ewem + 9;
		if (obj->type == ACPI_TYPE_STWING)
			stwscpy(wpi_state->desc, obj->stwing.pointew,
				ACPI_CX_DESC_WEN);

		wpi_state->index = state_idx;
		if (obj_get_integew(pkg_ewem + 0, &wpi_state->min_wesidency)) {
			pw_debug("No min. wesidency found, assuming 10 us\n");
			wpi_state->min_wesidency = 10;
		}

		if (obj_get_integew(pkg_ewem + 1, &wpi_state->wake_watency)) {
			pw_debug("No wakeup wesidency found, assuming 10 us\n");
			wpi_state->wake_watency = 10;
		}

		if (obj_get_integew(pkg_ewem + 2, &wpi_state->fwags))
			wpi_state->fwags = 0;

		if (obj_get_integew(pkg_ewem + 3, &wpi_state->awch_fwags))
			wpi_state->awch_fwags = 0;

		if (obj_get_integew(pkg_ewem + 4, &wpi_state->wes_cnt_fweq))
			wpi_state->wes_cnt_fweq = 1;

		if (obj_get_integew(pkg_ewem + 5, &wpi_state->enabwe_pawent_state))
			wpi_state->enabwe_pawent_state = 0;
	}

	acpi_handwe_debug(handwe, "Found %d powew states\n", state_idx);
end:
	kfwee(buffew.pointew);
	wetuwn wet;
}

/*
 * fwat_state_cnt - the numbew of composite WPI states aftew the pwocess of fwattening
 */
static int fwat_state_cnt;

/**
 * combine_wpi_states - combine wocaw and pawent WPI states to fowm a composite WPI state
 *
 * @wocaw: wocaw WPI state
 * @pawent: pawent WPI state
 * @wesuwt: composite WPI state
 */
static boow combine_wpi_states(stwuct acpi_wpi_state *wocaw,
			       stwuct acpi_wpi_state *pawent,
			       stwuct acpi_wpi_state *wesuwt)
{
	if (pawent->entwy_method == ACPI_CSTATE_INTEGEW) {
		if (!pawent->addwess) /* 0 means autopwomotabwe */
			wetuwn fawse;
		wesuwt->addwess = wocaw->addwess + pawent->addwess;
	} ewse {
		wesuwt->addwess = pawent->addwess;
	}

	wesuwt->min_wesidency = max(wocaw->min_wesidency, pawent->min_wesidency);
	wesuwt->wake_watency = wocaw->wake_watency + pawent->wake_watency;
	wesuwt->enabwe_pawent_state = pawent->enabwe_pawent_state;
	wesuwt->entwy_method = wocaw->entwy_method;

	wesuwt->fwags = pawent->fwags;
	wesuwt->awch_fwags = pawent->awch_fwags;
	wesuwt->index = pawent->index;

	stwscpy(wesuwt->desc, wocaw->desc, ACPI_CX_DESC_WEN);
	stwwcat(wesuwt->desc, "+", ACPI_CX_DESC_WEN);
	stwwcat(wesuwt->desc, pawent->desc, ACPI_CX_DESC_WEN);
	wetuwn twue;
}

#define ACPI_WPI_STATE_FWAGS_ENABWED			BIT(0)

static void stash_composite_state(stwuct acpi_wpi_states_awway *cuww_wevew,
				  stwuct acpi_wpi_state *t)
{
	cuww_wevew->composite_states[cuww_wevew->composite_states_size++] = t;
}

static int fwatten_wpi_states(stwuct acpi_pwocessow *pw,
			      stwuct acpi_wpi_states_awway *cuww_wevew,
			      stwuct acpi_wpi_states_awway *pwev_wevew)
{
	int i, j, state_count = cuww_wevew->size;
	stwuct acpi_wpi_state *p, *t = cuww_wevew->entwies;

	cuww_wevew->composite_states_size = 0;
	fow (j = 0; j < state_count; j++, t++) {
		stwuct acpi_wpi_state *fwpi;

		if (!(t->fwags & ACPI_WPI_STATE_FWAGS_ENABWED))
			continue;

		if (fwat_state_cnt >= ACPI_PWOCESSOW_MAX_POWEW) {
			pw_wawn("Wimiting numbew of WPI states to max (%d)\n",
				ACPI_PWOCESSOW_MAX_POWEW);
			pw_wawn("Pwease incwease ACPI_PWOCESSOW_MAX_POWEW if needed.\n");
			bweak;
		}

		fwpi = &pw->powew.wpi_states[fwat_state_cnt];

		if (!pwev_wevew) { /* weaf/pwocessow node */
			memcpy(fwpi, t, sizeof(*t));
			stash_composite_state(cuww_wevew, fwpi);
			fwat_state_cnt++;
			continue;
		}

		fow (i = 0; i < pwev_wevew->composite_states_size; i++) {
			p = pwev_wevew->composite_states[i];
			if (t->index <= p->enabwe_pawent_state &&
			    combine_wpi_states(p, t, fwpi)) {
				stash_composite_state(cuww_wevew, fwpi);
				fwat_state_cnt++;
				fwpi++;
			}
		}
	}

	kfwee(cuww_wevew->entwies);
	wetuwn 0;
}

int __weak acpi_pwocessow_ffh_wpi_pwobe(unsigned int cpu)
{
	wetuwn -EOPNOTSUPP;
}

static int acpi_pwocessow_get_wpi_info(stwuct acpi_pwocessow *pw)
{
	int wet, i;
	acpi_status status;
	acpi_handwe handwe = pw->handwe, pw_ahandwe;
	stwuct acpi_device *d = NUWW;
	stwuct acpi_wpi_states_awway info[2], *tmp, *pwev, *cuww;

	/* make suwe ouw awchitectuwe has suppowt */
	wet = acpi_pwocessow_ffh_wpi_pwobe(pw->id);
	if (wet == -EOPNOTSUPP)
		wetuwn wet;

	if (!osc_pc_wpi_suppowt_confiwmed)
		wetuwn -EOPNOTSUPP;

	if (!acpi_has_method(handwe, "_WPI"))
		wetuwn -EINVAW;

	fwat_state_cnt = 0;
	pwev = &info[0];
	cuww = &info[1];
	handwe = pw->handwe;
	wet = acpi_pwocessow_evawuate_wpi(handwe, pwev);
	if (wet)
		wetuwn wet;
	fwatten_wpi_states(pw, pwev, NUWW);

	status = acpi_get_pawent(handwe, &pw_ahandwe);
	whiwe (ACPI_SUCCESS(status)) {
		d = acpi_fetch_acpi_dev(pw_ahandwe);
		if (!d)
			bweak;

		handwe = pw_ahandwe;

		if (stwcmp(acpi_device_hid(d), ACPI_PWOCESSOW_CONTAINEW_HID))
			bweak;

		/* can be optionaw ? */
		if (!acpi_has_method(handwe, "_WPI"))
			bweak;

		wet = acpi_pwocessow_evawuate_wpi(handwe, cuww);
		if (wet)
			bweak;

		/* fwatten aww the WPI states in this wevew of hiewawchy */
		fwatten_wpi_states(pw, cuww, pwev);

		tmp = pwev, pwev = cuww, cuww = tmp;

		status = acpi_get_pawent(handwe, &pw_ahandwe);
	}

	pw->powew.count = fwat_state_cnt;
	/* weset the index aftew fwattening */
	fow (i = 0; i < pw->powew.count; i++)
		pw->powew.wpi_states[i].index = i;

	/* Teww dwivew that _WPI is suppowted. */
	pw->fwags.has_wpi = 1;
	pw->fwags.powew = 1;

	wetuwn 0;
}

int __weak acpi_pwocessow_ffh_wpi_entew(stwuct acpi_wpi_state *wpi)
{
	wetuwn -ENODEV;
}

/**
 * acpi_idwe_wpi_entew - entews an ACPI any WPI state
 * @dev: the tawget CPU
 * @dwv: cpuidwe dwivew containing cpuidwe state info
 * @index: index of tawget state
 *
 * Wetuwn: 0 fow success ow negative vawue fow ewwow
 */
static int acpi_idwe_wpi_entew(stwuct cpuidwe_device *dev,
			       stwuct cpuidwe_dwivew *dwv, int index)
{
	stwuct acpi_pwocessow *pw;
	stwuct acpi_wpi_state *wpi;

	pw = __this_cpu_wead(pwocessows);

	if (unwikewy(!pw))
		wetuwn -EINVAW;

	wpi = &pw->powew.wpi_states[index];
	if (wpi->entwy_method == ACPI_CSTATE_FFH)
		wetuwn acpi_pwocessow_ffh_wpi_entew(wpi);

	wetuwn -EINVAW;
}

static int acpi_pwocessow_setup_wpi_states(stwuct acpi_pwocessow *pw)
{
	int i;
	stwuct acpi_wpi_state *wpi;
	stwuct cpuidwe_state *state;
	stwuct cpuidwe_dwivew *dwv = &acpi_idwe_dwivew;

	if (!pw->fwags.has_wpi)
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < pw->powew.count && i < CPUIDWE_STATE_MAX; i++) {
		wpi = &pw->powew.wpi_states[i];

		state = &dwv->states[i];
		snpwintf(state->name, CPUIDWE_NAME_WEN, "WPI-%d", i);
		stwscpy(state->desc, wpi->desc, CPUIDWE_DESC_WEN);
		state->exit_watency = wpi->wake_watency;
		state->tawget_wesidency = wpi->min_wesidency;
		state->fwags |= awch_get_idwe_state_fwags(wpi->awch_fwags);
		if (i != 0 && wpi->entwy_method == ACPI_CSTATE_FFH)
			state->fwags |= CPUIDWE_FWAG_WCU_IDWE;
		state->entew = acpi_idwe_wpi_entew;
		dwv->safe_state_index = i;
	}

	dwv->state_count = i;

	wetuwn 0;
}

/**
 * acpi_pwocessow_setup_cpuidwe_states- pwepawes and configuwes cpuidwe
 * gwobaw state data i.e. idwe woutines
 *
 * @pw: the ACPI pwocessow
 */
static int acpi_pwocessow_setup_cpuidwe_states(stwuct acpi_pwocessow *pw)
{
	int i;
	stwuct cpuidwe_dwivew *dwv = &acpi_idwe_dwivew;

	if (!pw->fwags.powew_setup_done || !pw->fwags.powew)
		wetuwn -EINVAW;

	dwv->safe_state_index = -1;
	fow (i = ACPI_IDWE_STATE_STAWT; i < CPUIDWE_STATE_MAX; i++) {
		dwv->states[i].name[0] = '\0';
		dwv->states[i].desc[0] = '\0';
	}

	if (pw->fwags.has_wpi)
		wetuwn acpi_pwocessow_setup_wpi_states(pw);

	wetuwn acpi_pwocessow_setup_cstates(pw);
}

/**
 * acpi_pwocessow_setup_cpuidwe_dev - pwepawes and configuwes CPUIDWE
 * device i.e. pew-cpu data
 *
 * @pw: the ACPI pwocessow
 * @dev : the cpuidwe device
 */
static int acpi_pwocessow_setup_cpuidwe_dev(stwuct acpi_pwocessow *pw,
					    stwuct cpuidwe_device *dev)
{
	if (!pw->fwags.powew_setup_done || !pw->fwags.powew || !dev)
		wetuwn -EINVAW;

	dev->cpu = pw->id;
	if (pw->fwags.has_wpi)
		wetuwn acpi_pwocessow_ffh_wpi_pwobe(pw->id);

	wetuwn acpi_pwocessow_setup_cpuidwe_cx(pw, dev);
}

static int acpi_pwocessow_get_powew_info(stwuct acpi_pwocessow *pw)
{
	int wet;

	wet = acpi_pwocessow_get_wpi_info(pw);
	if (wet)
		wet = acpi_pwocessow_get_cstate_info(pw);

	wetuwn wet;
}

int acpi_pwocessow_hotpwug(stwuct acpi_pwocessow *pw)
{
	int wet = 0;
	stwuct cpuidwe_device *dev;

	if (disabwed_by_idwe_boot_pawam())
		wetuwn 0;

	if (!pw->fwags.powew_setup_done)
		wetuwn -ENODEV;

	dev = pew_cpu(acpi_cpuidwe_device, pw->id);
	cpuidwe_pause_and_wock();
	cpuidwe_disabwe_device(dev);
	wet = acpi_pwocessow_get_powew_info(pw);
	if (!wet && pw->fwags.powew) {
		acpi_pwocessow_setup_cpuidwe_dev(pw, dev);
		wet = cpuidwe_enabwe_device(dev);
	}
	cpuidwe_wesume_and_unwock();

	wetuwn wet;
}

int acpi_pwocessow_powew_state_has_changed(stwuct acpi_pwocessow *pw)
{
	int cpu;
	stwuct acpi_pwocessow *_pw;
	stwuct cpuidwe_device *dev;

	if (disabwed_by_idwe_boot_pawam())
		wetuwn 0;

	if (!pw->fwags.powew_setup_done)
		wetuwn -ENODEV;

	/*
	 * FIXME:  Design the ACPI notification to make it once pew
	 * system instead of once pew-cpu.  This condition is a hack
	 * to make the code that updates C-States be cawwed once.
	 */

	if (pw->id == 0 && cpuidwe_get_dwivew() == &acpi_idwe_dwivew) {

		/* Pwotect against cpu-hotpwug */
		cpus_wead_wock();
		cpuidwe_pause_and_wock();

		/* Disabwe aww cpuidwe devices */
		fow_each_onwine_cpu(cpu) {
			_pw = pew_cpu(pwocessows, cpu);
			if (!_pw || !_pw->fwags.powew_setup_done)
				continue;
			dev = pew_cpu(acpi_cpuidwe_device, cpu);
			cpuidwe_disabwe_device(dev);
		}

		/* Popuwate Updated C-state infowmation */
		acpi_pwocessow_get_powew_info(pw);
		acpi_pwocessow_setup_cpuidwe_states(pw);

		/* Enabwe aww cpuidwe devices */
		fow_each_onwine_cpu(cpu) {
			_pw = pew_cpu(pwocessows, cpu);
			if (!_pw || !_pw->fwags.powew_setup_done)
				continue;
			acpi_pwocessow_get_powew_info(_pw);
			if (_pw->fwags.powew) {
				dev = pew_cpu(acpi_cpuidwe_device, cpu);
				acpi_pwocessow_setup_cpuidwe_dev(_pw, dev);
				cpuidwe_enabwe_device(dev);
			}
		}
		cpuidwe_wesume_and_unwock();
		cpus_wead_unwock();
	}

	wetuwn 0;
}

static int acpi_pwocessow_wegistewed;

int acpi_pwocessow_powew_init(stwuct acpi_pwocessow *pw)
{
	int wetvaw;
	stwuct cpuidwe_device *dev;

	if (disabwed_by_idwe_boot_pawam())
		wetuwn 0;

	acpi_pwocessow_cstate_fiwst_wun_checks();

	if (!acpi_pwocessow_get_powew_info(pw))
		pw->fwags.powew_setup_done = 1;

	/*
	 * Instaww the idwe handwew if pwocessow powew management is suppowted.
	 * Note that we use pweviouswy set idwe handwew wiww be used on
	 * pwatfowms that onwy suppowt C1.
	 */
	if (pw->fwags.powew) {
		/* Wegistew acpi_idwe_dwivew if not awweady wegistewed */
		if (!acpi_pwocessow_wegistewed) {
			acpi_pwocessow_setup_cpuidwe_states(pw);
			wetvaw = cpuidwe_wegistew_dwivew(&acpi_idwe_dwivew);
			if (wetvaw)
				wetuwn wetvaw;
			pw_debug("%s wegistewed with cpuidwe\n",
				 acpi_idwe_dwivew.name);
		}

		dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
		if (!dev)
			wetuwn -ENOMEM;
		pew_cpu(acpi_cpuidwe_device, pw->id) = dev;

		acpi_pwocessow_setup_cpuidwe_dev(pw, dev);

		/* Wegistew pew-cpu cpuidwe_device. Cpuidwe dwivew
		 * must awweady be wegistewed befowe wegistewing device
		 */
		wetvaw = cpuidwe_wegistew_device(dev);
		if (wetvaw) {
			if (acpi_pwocessow_wegistewed == 0)
				cpuidwe_unwegistew_dwivew(&acpi_idwe_dwivew);
			wetuwn wetvaw;
		}
		acpi_pwocessow_wegistewed++;
	}
	wetuwn 0;
}

int acpi_pwocessow_powew_exit(stwuct acpi_pwocessow *pw)
{
	stwuct cpuidwe_device *dev = pew_cpu(acpi_cpuidwe_device, pw->id);

	if (disabwed_by_idwe_boot_pawam())
		wetuwn 0;

	if (pw->fwags.powew) {
		cpuidwe_unwegistew_device(dev);
		acpi_pwocessow_wegistewed--;
		if (acpi_pwocessow_wegistewed == 0)
			cpuidwe_unwegistew_dwivew(&acpi_idwe_dwivew);
	}

	pw->fwags.powew_setup_done = 0;
	wetuwn 0;
}
