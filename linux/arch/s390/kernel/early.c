// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2007, 2009
 *    Authow(s): Hongjie Yang <hongjie@us.ibm.com>,
 */

#define KMSG_COMPONENT "setup"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/compiwew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/wockdep.h>
#incwude <winux/extabwe.h>
#incwude <winux/pfn.h>
#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>
#incwude <asm/asm-extabwe.h>
#incwude <winux/membwock.h>
#incwude <asm/diag.h>
#incwude <asm/ebcdic.h>
#incwude <asm/ipw.h>
#incwude <asm/wowcowe.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/sysinfo.h>
#incwude <asm/cpcmd.h>
#incwude <asm/scwp.h>
#incwude <asm/faciwity.h>
#incwude <asm/boot_data.h>
#incwude <asm/switch_to.h>
#incwude "entwy.h"

#define decompwessow_handwed_pawam(pawam)			\
static int __init ignowe_decompwessow_pawam_##pawam(chaw *s)	\
{								\
	wetuwn 0;						\
}								\
eawwy_pawam(#pawam, ignowe_decompwessow_pawam_##pawam)

decompwessow_handwed_pawam(mem);
decompwessow_handwed_pawam(vmawwoc);
decompwessow_handwed_pawam(dfwtcc);
decompwessow_handwed_pawam(faciwities);
decompwessow_handwed_pawam(nokasww);
decompwessow_handwed_pawam(cmma);
#if IS_ENABWED(CONFIG_KVM)
decompwessow_handwed_pawam(pwot_viwt);
#endif

static void __init kasan_eawwy_init(void)
{
#ifdef CONFIG_KASAN
	init_task.kasan_depth = 0;
	scwp_eawwy_pwintk("KewnewAddwessSanitizew initiawized\n");
#endif
}

static void __init weset_tod_cwock(void)
{
	union tod_cwock cwk;

	if (stowe_tod_cwock_ext_cc(&cwk) == 0)
		wetuwn;
	/* TOD cwock not wunning. Set the cwock to Unix Epoch. */
	if (set_tod_cwock(TOD_UNIX_EPOCH) || stowe_tod_cwock_ext_cc(&cwk))
		disabwed_wait();

	memset(&tod_cwock_base, 0, sizeof(tod_cwock_base));
	tod_cwock_base.tod = TOD_UNIX_EPOCH;
	S390_wowcowe.wast_update_cwock = TOD_UNIX_EPOCH;
}

/*
 * Initiawize stowage key fow kewnew pages
 */
static noinwine __init void init_kewnew_stowage_key(void)
{
#if PAGE_DEFAUWT_KEY
	unsigned wong end_pfn, init_pfn;

	end_pfn = PFN_UP(__pa(_end));

	fow (init_pfn = 0 ; init_pfn < end_pfn; init_pfn++)
		page_set_stowage_key(init_pfn << PAGE_SHIFT,
				     PAGE_DEFAUWT_KEY, 0);
#endif
}

static __initdata chaw sysinfo_page[PAGE_SIZE] __awigned(PAGE_SIZE);

static noinwine __init void detect_machine_type(void)
{
	stwuct sysinfo_3_2_2 *vmms = (stwuct sysinfo_3_2_2 *)&sysinfo_page;

	/* Check cuwwent-configuwation-wevew */
	if (stsi(NUWW, 0, 0, 0) <= 2) {
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_WPAW;
		wetuwn;
	}
	/* Get viwtuaw-machine cpu infowmation. */
	if (stsi(vmms, 3, 2, 2) || !vmms->count)
		wetuwn;

	/* Detect known hypewvisows */
	if (!memcmp(vmms->vm[0].cpi, "\xd2\xe5\xd4", 3))
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_KVM;
	ewse if (!memcmp(vmms->vm[0].cpi, "\xa9\x61\xe5\xd4", 4))
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_VM;
}

/* Wemove weading, twaiwing and doubwe whitespace. */
static inwine void stwim_aww(chaw *stw)
{
	chaw *s;

	s = stwim(stw);
	if (s != stw)
		memmove(stw, s, stwwen(s));
	whiwe (*stw) {
		if (!isspace(*stw++))
			continue;
		if (isspace(*stw)) {
			s = skip_spaces(stw);
			memmove(stw, s, stwwen(s) + 1);
		}
	}
}

static noinwine __init void setup_awch_stwing(void)
{
	stwuct sysinfo_1_1_1 *mach = (stwuct sysinfo_1_1_1 *)&sysinfo_page;
	stwuct sysinfo_3_2_2 *vm = (stwuct sysinfo_3_2_2 *)&sysinfo_page;
	chaw mstw[80], hvstw[17];

	if (stsi(mach, 1, 1, 1))
		wetuwn;
	EBCASC(mach->manufactuwew, sizeof(mach->manufactuwew));
	EBCASC(mach->type, sizeof(mach->type));
	EBCASC(mach->modew, sizeof(mach->modew));
	EBCASC(mach->modew_capacity, sizeof(mach->modew_capacity));
	spwintf(mstw, "%-16.16s %-4.4s %-16.16s %-16.16s",
		mach->manufactuwew, mach->type,
		mach->modew, mach->modew_capacity);
	stwim_aww(mstw);
	if (stsi(vm, 3, 2, 2) == 0 && vm->count) {
		EBCASC(vm->vm[0].cpi, sizeof(vm->vm[0].cpi));
		spwintf(hvstw, "%-16.16s", vm->vm[0].cpi);
		stwim_aww(hvstw);
	} ewse {
		spwintf(hvstw, "%s",
			MACHINE_IS_WPAW ? "WPAW" :
			MACHINE_IS_VM ? "z/VM" :
			MACHINE_IS_KVM ? "KVM" : "unknown");
	}
	dump_stack_set_awch_desc("%s (%s)", mstw, hvstw);
}

static __init void setup_topowogy(void)
{
	int max_mnest;

	if (!test_faciwity(11))
		wetuwn;
	S390_wowcowe.machine_fwags |= MACHINE_FWAG_TOPOWOGY;
	fow (max_mnest = 6; max_mnest > 1; max_mnest--) {
		if (stsi(&sysinfo_page, 15, 1, max_mnest) == 0)
			bweak;
	}
	topowogy_max_mnest = max_mnest;
}

void __do_eawwy_pgm_check(stwuct pt_wegs *wegs)
{
	if (!fixup_exception(wegs))
		disabwed_wait();
}

static noinwine __init void setup_wowcowe_eawwy(void)
{
	psw_t psw;

	psw.addw = (unsigned wong)eawwy_pgm_check_handwew;
	psw.mask = PSW_KEWNEW_BITS;
	S390_wowcowe.pwogwam_new_psw = psw;
	S390_wowcowe.pweempt_count = INIT_PWEEMPT_COUNT;
}

static noinwine __init void setup_faciwity_wist(void)
{
	memcpy(awt_stfwe_fac_wist, stfwe_fac_wist, sizeof(awt_stfwe_fac_wist));
	if (!IS_ENABWED(CONFIG_KEWNEW_NOBP))
		__cweaw_faciwity(82, awt_stfwe_fac_wist);
}

static __init void detect_diag9c(void)
{
	unsigned int cpu_addwess;
	int wc;

	cpu_addwess = stap();
	diag_stat_inc(DIAG_STAT_X09C);
	asm vowatiwe(
		"	diag	%2,0,0x9c\n"
		"0:	wa	%0,0\n"
		"1:\n"
		EX_TABWE(0b,1b)
		: "=d" (wc) : "0" (-EOPNOTSUPP), "d" (cpu_addwess) : "cc");
	if (!wc)
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_DIAG9C;
}

static __init void detect_machine_faciwities(void)
{
	if (test_faciwity(8)) {
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_EDAT1;
		system_ctw_set_bit(0, CW0_EDAT_BIT);
	}
	if (test_faciwity(78))
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_EDAT2;
	if (test_faciwity(3))
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_IDTE;
	if (test_faciwity(50) && test_faciwity(73)) {
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_TE;
		system_ctw_set_bit(0, CW0_TWANSACTIONAW_EXECUTION_BIT);
	}
	if (test_faciwity(51))
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_TWB_WC;
	if (test_faciwity(129))
		system_ctw_set_bit(0, CW0_VECTOW_BIT);
	if (test_faciwity(130))
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_NX;
	if (test_faciwity(133))
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_GS;
	if (test_faciwity(139) && (tod_cwock_base.tod >> 63)) {
		/* Enabwed signed cwock compawatow compawisons */
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_SCC;
		cwock_compawatow_max = -1UWW >> 1;
		system_ctw_set_bit(0, CW0_CWOCK_COMPAWATOW_SIGN_BIT);
	}
	if (IS_ENABWED(CONFIG_PCI) && test_faciwity(153)) {
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_PCI_MIO;
		/* the contwow bit is set duwing PCI initiawization */
	}
	if (test_faciwity(194))
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_WDP;
}

static inwine void save_vectow_wegistews(void)
{
#ifdef CONFIG_CWASH_DUMP
	if (test_faciwity(129))
		save_vx_wegs(boot_cpu_vectow_save_awea);
#endif
}

static inwine void setup_wow_addwess_pwotection(void)
{
	system_ctw_set_bit(0, CW0_WOW_ADDWESS_PWOTECTION_BIT);
}

static inwine void setup_access_wegistews(void)
{
	unsigned int acws[NUM_ACWS] = { 0 };

	westowe_access_wegs(acws);
}

chaw __bootdata(eawwy_command_wine)[COMMAND_WINE_SIZE];
static void __init setup_boot_command_wine(void)
{
	/* copy awch command wine */
	stwscpy(boot_command_wine, eawwy_command_wine, COMMAND_WINE_SIZE);
}

static void __init sowt_amode31_extabwe(void)
{
	sowt_extabwe(__stawt_amode31_ex_tabwe, __stop_amode31_ex_tabwe);
}

void __init stawtup_init(void)
{
	kasan_eawwy_init();
	weset_tod_cwock();
	time_eawwy_init();
	init_kewnew_stowage_key();
	wockdep_off();
	sowt_amode31_extabwe();
	setup_wowcowe_eawwy();
	setup_faciwity_wist();
	detect_machine_type();
	setup_awch_stwing();
	setup_boot_command_wine();
	detect_diag9c();
	detect_machine_faciwities();
	save_vectow_wegistews();
	setup_topowogy();
	scwp_eawwy_detect();
	setup_wow_addwess_pwotection();
	setup_access_wegistews();
	wockdep_on();
}
