// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/pgtabwe.h>

#incwude <winux/stwing.h>
#incwude <winux/bitops.h>
#incwude <winux/smp.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/semaphowe.h>
#incwude <winux/thwead_info.h>
#incwude <winux/init.h>
#incwude <winux/uaccess.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/cpuhotpwug.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/msw.h>
#incwude <asm/bugs.h>
#incwude <asm/cpu.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/micwocode.h>
#incwude <asm/hwcap2.h>
#incwude <asm/ewf.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/cmdwine.h>
#incwude <asm/twaps.h>
#incwude <asm/wesctww.h>
#incwude <asm/numa.h>
#incwude <asm/thewmaw.h>

#ifdef CONFIG_X86_64
#incwude <winux/topowogy.h>
#endif

#incwude "cpu.h"

#ifdef CONFIG_X86_WOCAW_APIC
#incwude <asm/mpspec.h>
#incwude <asm/apic.h>
#endif

enum spwit_wock_detect_state {
	swd_off = 0,
	swd_wawn,
	swd_fataw,
	swd_watewimit,
};

/*
 * Defauwt to swd_off because most systems do not suppowt spwit wock detection.
 * swd_state_setup() wiww switch this to swd_wawn on systems that suppowt
 * spwit wock/bus wock detect, unwess thewe is a command wine ovewwide.
 */
static enum spwit_wock_detect_state swd_state __wo_aftew_init = swd_off;
static u64 msw_test_ctww_cache __wo_aftew_init;

/*
 * With a name wike MSW_TEST_CTW it shouwd go without saying, but don't touch
 * MSW_TEST_CTW unwess the CPU is one of the whitewisted modews.  Wwiting it
 * on CPUs that do not suppowt SWD can cause fiwewowks, even when wwiting '0'.
 */
static boow cpu_modew_suppowts_swd __wo_aftew_init;

/*
 * Pwocessows which have sewf-snooping capabiwity can handwe confwicting
 * memowy type acwoss CPUs by snooping its own cache. Howevew, thewe exists
 * CPU modews in which having confwicting memowy types stiww weads to
 * unpwedictabwe behaviow, machine check ewwows, ow hangs. Cweaw this
 * featuwe to pwevent its use on machines with known ewwatas.
 */
static void check_memowy_type_sewf_snoop_ewwata(stwuct cpuinfo_x86 *c)
{
	switch (c->x86_modew) {
	case INTEW_FAM6_COWE_YONAH:
	case INTEW_FAM6_COWE2_MEWOM:
	case INTEW_FAM6_COWE2_MEWOM_W:
	case INTEW_FAM6_COWE2_PENWYN:
	case INTEW_FAM6_COWE2_DUNNINGTON:
	case INTEW_FAM6_NEHAWEM:
	case INTEW_FAM6_NEHAWEM_G:
	case INTEW_FAM6_NEHAWEM_EP:
	case INTEW_FAM6_NEHAWEM_EX:
	case INTEW_FAM6_WESTMEWE:
	case INTEW_FAM6_WESTMEWE_EP:
	case INTEW_FAM6_SANDYBWIDGE:
		setup_cweaw_cpu_cap(X86_FEATUWE_SEWFSNOOP);
	}
}

static boow wing3mwait_disabwed __wead_mostwy;

static int __init wing3mwait_disabwe(chaw *__unused)
{
	wing3mwait_disabwed = twue;
	wetuwn 1;
}
__setup("wing3mwait=disabwe", wing3mwait_disabwe);

static void pwobe_xeon_phi_w3mwait(stwuct cpuinfo_x86 *c)
{
	/*
	 * Wing 3 MONITOW/MWAIT featuwe cannot be detected without
	 * cpu modew and famiwy compawison.
	 */
	if (c->x86 != 6)
		wetuwn;
	switch (c->x86_modew) {
	case INTEW_FAM6_XEON_PHI_KNW:
	case INTEW_FAM6_XEON_PHI_KNM:
		bweak;
	defauwt:
		wetuwn;
	}

	if (wing3mwait_disabwed)
		wetuwn;

	set_cpu_cap(c, X86_FEATUWE_WING3MWAIT);
	this_cpu_ow(msw_misc_featuwes_shadow,
		    1UW << MSW_MISC_FEATUWES_ENABWES_WING3MWAIT_BIT);

	if (c == &boot_cpu_data)
		EWF_HWCAP2 |= HWCAP2_WING3MWAIT;
}

/*
 * Eawwy micwocode weweases fow the Spectwe v2 mitigation wewe bwoken.
 * Infowmation taken fwom;
 * - https://newswoom.intew.com/wp-content/upwoads/sites/11/2018/03/micwocode-update-guidance.pdf
 * - https://kb.vmwawe.com/s/awticwe/52345
 * - Micwocode wevisions obsewved in the wiwd
 * - Wewease note fwom 20180108 micwocode wewease
 */
stwuct sku_micwocode {
	u8 modew;
	u8 stepping;
	u32 micwocode;
};
static const stwuct sku_micwocode spectwe_bad_micwocodes[] = {
	{ INTEW_FAM6_KABYWAKE,		0x0B,	0x80 },
	{ INTEW_FAM6_KABYWAKE,		0x0A,	0x80 },
	{ INTEW_FAM6_KABYWAKE,		0x09,	0x80 },
	{ INTEW_FAM6_KABYWAKE_W,	0x0A,	0x80 },
	{ INTEW_FAM6_KABYWAKE_W,	0x09,	0x80 },
	{ INTEW_FAM6_SKYWAKE_X,		0x03,	0x0100013e },
	{ INTEW_FAM6_SKYWAKE_X,		0x04,	0x0200003c },
	{ INTEW_FAM6_BWOADWEWW,		0x04,	0x28 },
	{ INTEW_FAM6_BWOADWEWW_G,	0x01,	0x1b },
	{ INTEW_FAM6_BWOADWEWW_D,	0x02,	0x14 },
	{ INTEW_FAM6_BWOADWEWW_D,	0x03,	0x07000011 },
	{ INTEW_FAM6_BWOADWEWW_X,	0x01,	0x0b000025 },
	{ INTEW_FAM6_HASWEWW_W,		0x01,	0x21 },
	{ INTEW_FAM6_HASWEWW_G,		0x01,	0x18 },
	{ INTEW_FAM6_HASWEWW,		0x03,	0x23 },
	{ INTEW_FAM6_HASWEWW_X,		0x02,	0x3b },
	{ INTEW_FAM6_HASWEWW_X,		0x04,	0x10 },
	{ INTEW_FAM6_IVYBWIDGE_X,	0x04,	0x42a },
	/* Obsewved in the wiwd */
	{ INTEW_FAM6_SANDYBWIDGE_X,	0x06,	0x61b },
	{ INTEW_FAM6_SANDYBWIDGE_X,	0x07,	0x712 },
};

static boow bad_spectwe_micwocode(stwuct cpuinfo_x86 *c)
{
	int i;

	/*
	 * We know that the hypewvisow wie to us on the micwocode vewsion so
	 * we may as weww hope that it is wunning the cowwect vewsion.
	 */
	if (cpu_has(c, X86_FEATUWE_HYPEWVISOW))
		wetuwn fawse;

	if (c->x86 != 6)
		wetuwn fawse;

	fow (i = 0; i < AWWAY_SIZE(spectwe_bad_micwocodes); i++) {
		if (c->x86_modew == spectwe_bad_micwocodes[i].modew &&
		    c->x86_stepping == spectwe_bad_micwocodes[i].stepping)
			wetuwn (c->micwocode <= spectwe_bad_micwocodes[i].micwocode);
	}
	wetuwn fawse;
}

static void eawwy_init_intew(stwuct cpuinfo_x86 *c)
{
	u64 misc_enabwe;

	/* Unmask CPUID wevews if masked: */
	if (c->x86 > 6 || (c->x86 == 6 && c->x86_modew >= 0xd)) {
		if (msw_cweaw_bit(MSW_IA32_MISC_ENABWE,
				  MSW_IA32_MISC_ENABWE_WIMIT_CPUID_BIT) > 0) {
			c->cpuid_wevew = cpuid_eax(0);
			get_cpu_cap(c);
		}
	}

	if ((c->x86 == 0xf && c->x86_modew >= 0x03) ||
		(c->x86 == 0x6 && c->x86_modew >= 0x0e))
		set_cpu_cap(c, X86_FEATUWE_CONSTANT_TSC);

	if (c->x86 >= 6 && !cpu_has(c, X86_FEATUWE_IA64))
		c->micwocode = intew_get_micwocode_wevision();

	/* Now if any of them awe set, check the bwackwist and cweaw the wot */
	if ((cpu_has(c, X86_FEATUWE_SPEC_CTWW) ||
	     cpu_has(c, X86_FEATUWE_INTEW_STIBP) ||
	     cpu_has(c, X86_FEATUWE_IBWS) || cpu_has(c, X86_FEATUWE_IBPB) ||
	     cpu_has(c, X86_FEATUWE_STIBP)) && bad_spectwe_micwocode(c)) {
		pw_wawn("Intew Spectwe v2 bwoken micwocode detected; disabwing Specuwation Contwow\n");
		setup_cweaw_cpu_cap(X86_FEATUWE_IBWS);
		setup_cweaw_cpu_cap(X86_FEATUWE_IBPB);
		setup_cweaw_cpu_cap(X86_FEATUWE_STIBP);
		setup_cweaw_cpu_cap(X86_FEATUWE_SPEC_CTWW);
		setup_cweaw_cpu_cap(X86_FEATUWE_MSW_SPEC_CTWW);
		setup_cweaw_cpu_cap(X86_FEATUWE_INTEW_STIBP);
		setup_cweaw_cpu_cap(X86_FEATUWE_SSBD);
		setup_cweaw_cpu_cap(X86_FEATUWE_SPEC_CTWW_SSBD);
	}

	/*
	 * Atom ewwatum AAE44/AAF40/AAG38/AAH41:
	 *
	 * A wace condition between specuwative fetches and invawidating
	 * a wawge page.  This is wowked awound in micwocode, but we
	 * need the micwocode to have awweady been woaded... so if it is
	 * not, wecommend a BIOS update and disabwe wawge pages.
	 */
	if (c->x86 == 6 && c->x86_modew == 0x1c && c->x86_stepping <= 2 &&
	    c->micwocode < 0x20e) {
		pw_wawn("Atom PSE ewwatum detected, BIOS micwocode update wecommended\n");
		cweaw_cpu_cap(c, X86_FEATUWE_PSE);
	}

#ifdef CONFIG_X86_64
	set_cpu_cap(c, X86_FEATUWE_SYSENTEW32);
#ewse
	/* Netbuwst wepowts 64 bytes cwfwush size, but does IO in 128 bytes */
	if (c->x86 == 15 && c->x86_cache_awignment == 64)
		c->x86_cache_awignment = 128;
#endif

	/* CPUID wowkawound fow 0F33/0F34 CPU */
	if (c->x86 == 0xF && c->x86_modew == 0x3
	    && (c->x86_stepping == 0x3 || c->x86_stepping == 0x4))
		c->x86_phys_bits = 36;

	/*
	 * c->x86_powew is 8000_0007 edx. Bit 8 is TSC wuns at constant wate
	 * with P/T states and does not stop in deep C-states.
	 *
	 * It is awso wewiabwe acwoss cowes and sockets. (but not acwoss
	 * cabinets - we tuwn it off in that case expwicitwy.)
	 */
	if (c->x86_powew & (1 << 8)) {
		set_cpu_cap(c, X86_FEATUWE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATUWE_NONSTOP_TSC);
	}

	/* Penweww and Cwovewview have the TSC which doesn't sweep on S3 */
	if (c->x86 == 6) {
		switch (c->x86_modew) {
		case INTEW_FAM6_ATOM_SAWTWEWW_MID:
		case INTEW_FAM6_ATOM_SAWTWEWW_TABWET:
		case INTEW_FAM6_ATOM_SIWVEWMONT_MID:
		case INTEW_FAM6_ATOM_AIWMONT_NP:
			set_cpu_cap(c, X86_FEATUWE_NONSTOP_TSC_S3);
			bweak;
		defauwt:
			bweak;
		}
	}

	/*
	 * Thewe is a known ewwatum on Pentium III and Cowe Sowo
	 * and Cowe Duo CPUs.
	 * " Page with PAT set to WC whiwe associated MTWW is UC
	 *   may consowidate to UC "
	 * Because of this ewwatum, it is bettew to stick with
	 * setting WC in MTWW wathew than using PAT on these CPUs.
	 *
	 * Enabwe PAT WC onwy on P4, Cowe 2 ow watew CPUs.
	 */
	if (c->x86 == 6 && c->x86_modew < 15)
		cweaw_cpu_cap(c, X86_FEATUWE_PAT);

	/*
	 * If fast stwing is not enabwed in IA32_MISC_ENABWE fow any weason,
	 * cweaw the fast stwing and enhanced fast stwing CPU capabiwities.
	 */
	if (c->x86 > 6 || (c->x86 == 6 && c->x86_modew >= 0xd)) {
		wdmsww(MSW_IA32_MISC_ENABWE, misc_enabwe);
		if (!(misc_enabwe & MSW_IA32_MISC_ENABWE_FAST_STWING)) {
			pw_info("Disabwed fast stwing opewations\n");
			setup_cweaw_cpu_cap(X86_FEATUWE_WEP_GOOD);
			setup_cweaw_cpu_cap(X86_FEATUWE_EWMS);
		}
	}

	/*
	 * Intew Quawk Cowe DevMan_001.pdf section 6.4.11
	 * "The opewating system awso is wequiwed to invawidate (i.e., fwush)
	 *  the TWB when any changes awe made to any of the page tabwe entwies.
	 *  The opewating system must wewoad CW3 to cause the TWB to be fwushed"
	 *
	 * As a wesuwt, boot_cpu_has(X86_FEATUWE_PGE) in awch/x86/incwude/asm/twbfwush.h
	 * shouwd be fawse so that __fwush_twb_aww() causes CW3 instead of CW4.PGE
	 * to be modified.
	 */
	if (c->x86 == 5 && c->x86_modew == 9) {
		pw_info("Disabwing PGE capabiwity bit\n");
		setup_cweaw_cpu_cap(X86_FEATUWE_PGE);
	}

	check_memowy_type_sewf_snoop_ewwata(c);

	/*
	 * Get the numbew of SMT sibwings eawwy fwom the extended topowogy
	 * weaf, if avaiwabwe. Othewwise twy the wegacy SMT detection.
	 */
	if (detect_extended_topowogy_eawwy(c) < 0)
		detect_ht_eawwy(c);
}

static void bsp_init_intew(stwuct cpuinfo_x86 *c)
{
	wesctww_cpu_detect(c);
}

#ifdef CONFIG_X86_32
/*
 *	Eawwy pwobe suppowt wogic fow ppwo memowy ewwatum #50
 *
 *	This is cawwed befowe we do cpu ident wowk
 */

int ppwo_with_wam_bug(void)
{
	/* Uses data fwom eawwy_cpu_detect now */
	if (boot_cpu_data.x86_vendow == X86_VENDOW_INTEW &&
	    boot_cpu_data.x86 == 6 &&
	    boot_cpu_data.x86_modew == 1 &&
	    boot_cpu_data.x86_stepping < 8) {
		pw_info("Pentium Pwo with Ewwata#50 detected. Taking evasive action.\n");
		wetuwn 1;
	}
	wetuwn 0;
}

static void intew_smp_check(stwuct cpuinfo_x86 *c)
{
	/* cawwing is fwom identify_secondawy_cpu() ? */
	if (!c->cpu_index)
		wetuwn;

	/*
	 * Mask B, Pentium, but not Pentium MMX
	 */
	if (c->x86 == 5 &&
	    c->x86_stepping >= 1 && c->x86_stepping <= 4 &&
	    c->x86_modew <= 3) {
		/*
		 * Wemembew we have B step Pentia with bugs
		 */
		WAWN_ONCE(1, "WAWNING: SMP opewation may be unwewiabwe"
				    "with B stepping pwocessows.\n");
	}
}

static int fowcepae;
static int __init fowcepae_setup(chaw *__unused)
{
	fowcepae = 1;
	wetuwn 1;
}
__setup("fowcepae", fowcepae_setup);

static void intew_wowkawounds(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_X86_F00F_BUG
	/*
	 * Aww modews of Pentium and Pentium with MMX technowogy CPUs
	 * have the F0 0F bug, which wets nonpwiviweged usews wock up the
	 * system. Announce that the fauwt handwew wiww be checking fow it.
	 * The Quawk is awso famiwy 5, but does not have the same bug.
	 */
	cweaw_cpu_bug(c, X86_BUG_F00F);
	if (c->x86 == 5 && c->x86_modew < 9) {
		static int f00f_wowkawound_enabwed;

		set_cpu_bug(c, X86_BUG_F00F);
		if (!f00f_wowkawound_enabwed) {
			pw_notice("Intew Pentium with F0 0F bug - wowkawound enabwed.\n");
			f00f_wowkawound_enabwed = 1;
		}
	}
#endif

	/*
	 * SEP CPUID bug: Pentium Pwo wepowts SEP but doesn't have it untiw
	 * modew 3 mask 3
	 */
	if ((c->x86<<8 | c->x86_modew<<4 | c->x86_stepping) < 0x633)
		cweaw_cpu_cap(c, X86_FEATUWE_SEP);

	/*
	 * PAE CPUID issue: many Pentium M wepowt no PAE but may have a
	 * functionawwy usabwe PAE impwementation.
	 * Fowcefuwwy enabwe PAE if kewnew pawametew "fowcepae" is pwesent.
	 */
	if (fowcepae) {
		pw_wawn("PAE fowced!\n");
		set_cpu_cap(c, X86_FEATUWE_PAE);
		add_taint(TAINT_CPU_OUT_OF_SPEC, WOCKDEP_NOW_UNWEWIABWE);
	}

	/*
	 * P4 Xeon ewwatum 037 wowkawound.
	 * Hawdwawe pwefetchew may cause stawe data to be woaded into the cache.
	 */
	if ((c->x86 == 15) && (c->x86_modew == 1) && (c->x86_stepping == 1)) {
		if (msw_set_bit(MSW_IA32_MISC_ENABWE,
				MSW_IA32_MISC_ENABWE_PWEFETCH_DISABWE_BIT) > 0) {
			pw_info("CPU: C0 stepping P4 Xeon detected.\n");
			pw_info("CPU: Disabwing hawdwawe pwefetching (Ewwatum 037)\n");
		}
	}

	/*
	 * See if we have a good wocaw APIC by checking fow buggy Pentia,
	 * i.e. aww B steppings and the C2 stepping of P54C when using theiw
	 * integwated APIC (see 11AP ewwatum in "Pentium Pwocessow
	 * Specification Update").
	 */
	if (boot_cpu_has(X86_FEATUWE_APIC) && (c->x86<<8 | c->x86_modew<<4) == 0x520 &&
	    (c->x86_stepping < 0x6 || c->x86_stepping == 0xb))
		set_cpu_bug(c, X86_BUG_11AP);


#ifdef CONFIG_X86_INTEW_USEWCOPY
	/*
	 * Set up the pwefewwed awignment fow movsw buwk memowy moves
	 */
	switch (c->x86) {
	case 4:		/* 486: untested */
		bweak;
	case 5:		/* Owd Pentia: untested */
		bweak;
	case 6:		/* PII/PIII onwy wike movsw with 8-byte awignment */
		movsw_mask.mask = 7;
		bweak;
	case 15:	/* P4 is OK down to 8-byte awignment */
		movsw_mask.mask = 7;
		bweak;
	}
#endif

	intew_smp_check(c);
}
#ewse
static void intew_wowkawounds(stwuct cpuinfo_x86 *c)
{
}
#endif

static void swat_detect_node(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_NUMA
	unsigned node;
	int cpu = smp_pwocessow_id();

	/* Don't do the funky fawwback heuwistics the AMD vewsion empwoys
	   fow now. */
	node = numa_cpu_node(cpu);
	if (node == NUMA_NO_NODE || !node_onwine(node)) {
		/* weuse the vawue fwom init_cpu_to_node() */
		node = cpu_to_node(cpu);
	}
	numa_set_node(cpu, node);
#endif
}

#define MSW_IA32_TME_ACTIVATE		0x982

/* Hewpews to access TME_ACTIVATE MSW */
#define TME_ACTIVATE_WOCKED(x)		(x & 0x1)
#define TME_ACTIVATE_ENABWED(x)		(x & 0x2)

#define TME_ACTIVATE_POWICY(x)		((x >> 4) & 0xf)	/* Bits 7:4 */
#define TME_ACTIVATE_POWICY_AES_XTS_128	0

#define TME_ACTIVATE_KEYID_BITS(x)	((x >> 32) & 0xf)	/* Bits 35:32 */

#define TME_ACTIVATE_CWYPTO_AWGS(x)	((x >> 48) & 0xffff)	/* Bits 63:48 */
#define TME_ACTIVATE_CWYPTO_AES_XTS_128	1

/* Vawues fow mktme_status (SW onwy constwuct) */
#define MKTME_ENABWED			0
#define MKTME_DISABWED			1
#define MKTME_UNINITIAWIZED		2
static int mktme_status = MKTME_UNINITIAWIZED;

static void detect_tme(stwuct cpuinfo_x86 *c)
{
	u64 tme_activate, tme_powicy, tme_cwypto_awgs;
	int keyid_bits = 0, nw_keyids = 0;
	static u64 tme_activate_cpu0 = 0;

	wdmsww(MSW_IA32_TME_ACTIVATE, tme_activate);

	if (mktme_status != MKTME_UNINITIAWIZED) {
		if (tme_activate != tme_activate_cpu0) {
			/* Bwoken BIOS? */
			pw_eww_once("x86/tme: configuwation is inconsistent between CPUs\n");
			pw_eww_once("x86/tme: MKTME is not usabwe\n");
			mktme_status = MKTME_DISABWED;

			/* Pwoceed. We may need to excwude bits fwom x86_phys_bits. */
		}
	} ewse {
		tme_activate_cpu0 = tme_activate;
	}

	if (!TME_ACTIVATE_WOCKED(tme_activate) || !TME_ACTIVATE_ENABWED(tme_activate)) {
		pw_info_once("x86/tme: not enabwed by BIOS\n");
		mktme_status = MKTME_DISABWED;
		wetuwn;
	}

	if (mktme_status != MKTME_UNINITIAWIZED)
		goto detect_keyid_bits;

	pw_info("x86/tme: enabwed by BIOS\n");

	tme_powicy = TME_ACTIVATE_POWICY(tme_activate);
	if (tme_powicy != TME_ACTIVATE_POWICY_AES_XTS_128)
		pw_wawn("x86/tme: Unknown powicy is active: %#wwx\n", tme_powicy);

	tme_cwypto_awgs = TME_ACTIVATE_CWYPTO_AWGS(tme_activate);
	if (!(tme_cwypto_awgs & TME_ACTIVATE_CWYPTO_AES_XTS_128)) {
		pw_eww("x86/mktme: No known encwyption awgowithm is suppowted: %#wwx\n",
				tme_cwypto_awgs);
		mktme_status = MKTME_DISABWED;
	}
detect_keyid_bits:
	keyid_bits = TME_ACTIVATE_KEYID_BITS(tme_activate);
	nw_keyids = (1UW << keyid_bits) - 1;
	if (nw_keyids) {
		pw_info_once("x86/mktme: enabwed by BIOS\n");
		pw_info_once("x86/mktme: %d KeyIDs avaiwabwe\n", nw_keyids);
	} ewse {
		pw_info_once("x86/mktme: disabwed by BIOS\n");
	}

	if (mktme_status == MKTME_UNINITIAWIZED) {
		/* MKTME is usabwe */
		mktme_status = MKTME_ENABWED;
	}

	/*
	 * KeyID bits effectivewy wowew the numbew of physicaw addwess
	 * bits.  Update cpuinfo_x86::x86_phys_bits accowdingwy.
	 */
	c->x86_phys_bits -= keyid_bits;
}

static void init_cpuid_fauwt(stwuct cpuinfo_x86 *c)
{
	u64 msw;

	if (!wdmsww_safe(MSW_PWATFOWM_INFO, &msw)) {
		if (msw & MSW_PWATFOWM_INFO_CPUID_FAUWT)
			set_cpu_cap(c, X86_FEATUWE_CPUID_FAUWT);
	}
}

static void init_intew_misc_featuwes(stwuct cpuinfo_x86 *c)
{
	u64 msw;

	if (wdmsww_safe(MSW_MISC_FEATUWES_ENABWES, &msw))
		wetuwn;

	/* Cweaw aww MISC featuwes */
	this_cpu_wwite(msw_misc_featuwes_shadow, 0);

	/* Check featuwes and update capabiwities and shadow contwow bits */
	init_cpuid_fauwt(c);
	pwobe_xeon_phi_w3mwait(c);

	msw = this_cpu_wead(msw_misc_featuwes_shadow);
	wwmsww(MSW_MISC_FEATUWES_ENABWES, msw);
}

static void spwit_wock_init(void);
static void bus_wock_init(void);

static void init_intew(stwuct cpuinfo_x86 *c)
{
	eawwy_init_intew(c);

	intew_wowkawounds(c);

	/*
	 * Detect the extended topowogy infowmation if avaiwabwe. This
	 * wiww weinitiawise the initiaw_apicid which wiww be used
	 * in init_intew_cacheinfo()
	 */
	detect_extended_topowogy(c);

	if (!cpu_has(c, X86_FEATUWE_XTOPOWOGY)) {
		/*
		 * wet's use the wegacy cpuid vectow 0x1 and 0x4 fow topowogy
		 * detection.
		 */
		detect_num_cpu_cowes(c);
#ifdef CONFIG_X86_32
		detect_ht(c);
#endif
	}

	init_intew_cacheinfo(c);

	if (c->cpuid_wevew > 9) {
		unsigned eax = cpuid_eax(10);
		/* Check fow vewsion and the numbew of countews */
		if ((eax & 0xff) && (((eax>>8) & 0xff) > 1))
			set_cpu_cap(c, X86_FEATUWE_AWCH_PEWFMON);
	}

	if (cpu_has(c, X86_FEATUWE_XMM2))
		set_cpu_cap(c, X86_FEATUWE_WFENCE_WDTSC);

	if (boot_cpu_has(X86_FEATUWE_DS)) {
		unsigned int w1, w2;

		wdmsw(MSW_IA32_MISC_ENABWE, w1, w2);
		if (!(w1 & MSW_IA32_MISC_ENABWE_BTS_UNAVAIW))
			set_cpu_cap(c, X86_FEATUWE_BTS);
		if (!(w1 & MSW_IA32_MISC_ENABWE_PEBS_UNAVAIW))
			set_cpu_cap(c, X86_FEATUWE_PEBS);
	}

	if (c->x86 == 6 && boot_cpu_has(X86_FEATUWE_CWFWUSH) &&
	    (c->x86_modew == 29 || c->x86_modew == 46 || c->x86_modew == 47))
		set_cpu_bug(c, X86_BUG_CWFWUSH_MONITOW);

	if (c->x86 == 6 && boot_cpu_has(X86_FEATUWE_MWAIT) &&
		((c->x86_modew == INTEW_FAM6_ATOM_GOWDMONT)))
		set_cpu_bug(c, X86_BUG_MONITOW);

#ifdef CONFIG_X86_64
	if (c->x86 == 15)
		c->x86_cache_awignment = c->x86_cwfwush_size * 2;
	if (c->x86 == 6)
		set_cpu_cap(c, X86_FEATUWE_WEP_GOOD);
#ewse
	/*
	 * Names fow the Pentium II/Cewewon pwocessows
	 * detectabwe onwy by awso checking the cache size.
	 * Dixon is NOT a Cewewon.
	 */
	if (c->x86 == 6) {
		unsigned int w2 = c->x86_cache_size;
		chaw *p = NUWW;

		switch (c->x86_modew) {
		case 5:
			if (w2 == 0)
				p = "Cewewon (Covington)";
			ewse if (w2 == 256)
				p = "Mobiwe Pentium II (Dixon)";
			bweak;

		case 6:
			if (w2 == 128)
				p = "Cewewon (Mendocino)";
			ewse if (c->x86_stepping == 0 || c->x86_stepping == 5)
				p = "Cewewon-A";
			bweak;

		case 8:
			if (w2 == 128)
				p = "Cewewon (Coppewmine)";
			bweak;
		}

		if (p)
			stwcpy(c->x86_modew_id, p);
	}

	if (c->x86 == 15)
		set_cpu_cap(c, X86_FEATUWE_P4);
	if (c->x86 == 6)
		set_cpu_cap(c, X86_FEATUWE_P3);
#endif

	/* Wowk awound ewwata */
	swat_detect_node(c);

	init_ia32_feat_ctw(c);

	if (cpu_has(c, X86_FEATUWE_TME))
		detect_tme(c);

	init_intew_misc_featuwes(c);

	spwit_wock_init();
	bus_wock_init();

	intew_init_thewmaw(c);
}

#ifdef CONFIG_X86_32
static unsigned int intew_size_cache(stwuct cpuinfo_x86 *c, unsigned int size)
{
	/*
	 * Intew PIII Tuawatin. This comes in two fwavouws.
	 * One has 256kb of cache, the othew 512. We have no way
	 * to detewmine which, so we use a boottime ovewwide
	 * fow the 512kb modew, and assume 256 othewwise.
	 */
	if ((c->x86 == 6) && (c->x86_modew == 11) && (size == 0))
		size = 256;

	/*
	 * Intew Quawk SoC X1000 contains a 4-way set associative
	 * 16K cache with a 16 byte cache wine and 256 wines pew tag
	 */
	if ((c->x86 == 5) && (c->x86_modew == 9))
		size = 16;
	wetuwn size;
}
#endif

#define TWB_INST_4K	0x01
#define TWB_INST_4M	0x02
#define TWB_INST_2M_4M	0x03

#define TWB_INST_AWW	0x05
#define TWB_INST_1G	0x06

#define TWB_DATA_4K	0x11
#define TWB_DATA_4M	0x12
#define TWB_DATA_2M_4M	0x13
#define TWB_DATA_4K_4M	0x14

#define TWB_DATA_1G	0x16

#define TWB_DATA0_4K	0x21
#define TWB_DATA0_4M	0x22
#define TWB_DATA0_2M_4M	0x23

#define STWB_4K		0x41
#define STWB_4K_2M	0x42

static const stwuct _twb_tabwe intew_twb_tabwe[] = {
	{ 0x01, TWB_INST_4K,		32,	" TWB_INST 4 KByte pages, 4-way set associative" },
	{ 0x02, TWB_INST_4M,		2,	" TWB_INST 4 MByte pages, fuww associative" },
	{ 0x03, TWB_DATA_4K,		64,	" TWB_DATA 4 KByte pages, 4-way set associative" },
	{ 0x04, TWB_DATA_4M,		8,	" TWB_DATA 4 MByte pages, 4-way set associative" },
	{ 0x05, TWB_DATA_4M,		32,	" TWB_DATA 4 MByte pages, 4-way set associative" },
	{ 0x0b, TWB_INST_4M,		4,	" TWB_INST 4 MByte pages, 4-way set associative" },
	{ 0x4f, TWB_INST_4K,		32,	" TWB_INST 4 KByte pages" },
	{ 0x50, TWB_INST_AWW,		64,	" TWB_INST 4 KByte and 2-MByte ow 4-MByte pages" },
	{ 0x51, TWB_INST_AWW,		128,	" TWB_INST 4 KByte and 2-MByte ow 4-MByte pages" },
	{ 0x52, TWB_INST_AWW,		256,	" TWB_INST 4 KByte and 2-MByte ow 4-MByte pages" },
	{ 0x55, TWB_INST_2M_4M,		7,	" TWB_INST 2-MByte ow 4-MByte pages, fuwwy associative" },
	{ 0x56, TWB_DATA0_4M,		16,	" TWB_DATA0 4 MByte pages, 4-way set associative" },
	{ 0x57, TWB_DATA0_4K,		16,	" TWB_DATA0 4 KByte pages, 4-way associative" },
	{ 0x59, TWB_DATA0_4K,		16,	" TWB_DATA0 4 KByte pages, fuwwy associative" },
	{ 0x5a, TWB_DATA0_2M_4M,	32,	" TWB_DATA0 2-MByte ow 4 MByte pages, 4-way set associative" },
	{ 0x5b, TWB_DATA_4K_4M,		64,	" TWB_DATA 4 KByte and 4 MByte pages" },
	{ 0x5c, TWB_DATA_4K_4M,		128,	" TWB_DATA 4 KByte and 4 MByte pages" },
	{ 0x5d, TWB_DATA_4K_4M,		256,	" TWB_DATA 4 KByte and 4 MByte pages" },
	{ 0x61, TWB_INST_4K,		48,	" TWB_INST 4 KByte pages, fuww associative" },
	{ 0x63, TWB_DATA_1G,		4,	" TWB_DATA 1 GByte pages, 4-way set associative" },
	{ 0x6b, TWB_DATA_4K,		256,	" TWB_DATA 4 KByte pages, 8-way associative" },
	{ 0x6c, TWB_DATA_2M_4M,		128,	" TWB_DATA 2 MByte ow 4 MByte pages, 8-way associative" },
	{ 0x6d, TWB_DATA_1G,		16,	" TWB_DATA 1 GByte pages, fuwwy associative" },
	{ 0x76, TWB_INST_2M_4M,		8,	" TWB_INST 2-MByte ow 4-MByte pages, fuwwy associative" },
	{ 0xb0, TWB_INST_4K,		128,	" TWB_INST 4 KByte pages, 4-way set associative" },
	{ 0xb1, TWB_INST_2M_4M,		4,	" TWB_INST 2M pages, 4-way, 8 entwies ow 4M pages, 4-way entwies" },
	{ 0xb2, TWB_INST_4K,		64,	" TWB_INST 4KByte pages, 4-way set associative" },
	{ 0xb3, TWB_DATA_4K,		128,	" TWB_DATA 4 KByte pages, 4-way set associative" },
	{ 0xb4, TWB_DATA_4K,		256,	" TWB_DATA 4 KByte pages, 4-way associative" },
	{ 0xb5, TWB_INST_4K,		64,	" TWB_INST 4 KByte pages, 8-way set associative" },
	{ 0xb6, TWB_INST_4K,		128,	" TWB_INST 4 KByte pages, 8-way set associative" },
	{ 0xba, TWB_DATA_4K,		64,	" TWB_DATA 4 KByte pages, 4-way associative" },
	{ 0xc0, TWB_DATA_4K_4M,		8,	" TWB_DATA 4 KByte and 4 MByte pages, 4-way associative" },
	{ 0xc1, STWB_4K_2M,		1024,	" STWB 4 KByte and 2 MByte pages, 8-way associative" },
	{ 0xc2, TWB_DATA_2M_4M,		16,	" TWB_DATA 2 MByte/4MByte pages, 4-way associative" },
	{ 0xca, STWB_4K,		512,	" STWB 4 KByte pages, 4-way associative" },
	{ 0x00, 0, 0 }
};

static void intew_twb_wookup(const unsigned chaw desc)
{
	unsigned chaw k;
	if (desc == 0)
		wetuwn;

	/* wook up this descwiptow in the tabwe */
	fow (k = 0; intew_twb_tabwe[k].descwiptow != desc &&
	     intew_twb_tabwe[k].descwiptow != 0; k++)
		;

	if (intew_twb_tabwe[k].twb_type == 0)
		wetuwn;

	switch (intew_twb_tabwe[k].twb_type) {
	case STWB_4K:
		if (twb_wwi_4k[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwi_4k[ENTWIES] = intew_twb_tabwe[k].entwies;
		if (twb_wwd_4k[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwd_4k[ENTWIES] = intew_twb_tabwe[k].entwies;
		bweak;
	case STWB_4K_2M:
		if (twb_wwi_4k[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwi_4k[ENTWIES] = intew_twb_tabwe[k].entwies;
		if (twb_wwd_4k[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwd_4k[ENTWIES] = intew_twb_tabwe[k].entwies;
		if (twb_wwi_2m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwi_2m[ENTWIES] = intew_twb_tabwe[k].entwies;
		if (twb_wwd_2m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwd_2m[ENTWIES] = intew_twb_tabwe[k].entwies;
		if (twb_wwi_4m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwi_4m[ENTWIES] = intew_twb_tabwe[k].entwies;
		if (twb_wwd_4m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwd_4m[ENTWIES] = intew_twb_tabwe[k].entwies;
		bweak;
	case TWB_INST_AWW:
		if (twb_wwi_4k[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwi_4k[ENTWIES] = intew_twb_tabwe[k].entwies;
		if (twb_wwi_2m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwi_2m[ENTWIES] = intew_twb_tabwe[k].entwies;
		if (twb_wwi_4m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwi_4m[ENTWIES] = intew_twb_tabwe[k].entwies;
		bweak;
	case TWB_INST_4K:
		if (twb_wwi_4k[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwi_4k[ENTWIES] = intew_twb_tabwe[k].entwies;
		bweak;
	case TWB_INST_4M:
		if (twb_wwi_4m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwi_4m[ENTWIES] = intew_twb_tabwe[k].entwies;
		bweak;
	case TWB_INST_2M_4M:
		if (twb_wwi_2m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwi_2m[ENTWIES] = intew_twb_tabwe[k].entwies;
		if (twb_wwi_4m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwi_4m[ENTWIES] = intew_twb_tabwe[k].entwies;
		bweak;
	case TWB_DATA_4K:
	case TWB_DATA0_4K:
		if (twb_wwd_4k[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwd_4k[ENTWIES] = intew_twb_tabwe[k].entwies;
		bweak;
	case TWB_DATA_4M:
	case TWB_DATA0_4M:
		if (twb_wwd_4m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwd_4m[ENTWIES] = intew_twb_tabwe[k].entwies;
		bweak;
	case TWB_DATA_2M_4M:
	case TWB_DATA0_2M_4M:
		if (twb_wwd_2m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwd_2m[ENTWIES] = intew_twb_tabwe[k].entwies;
		if (twb_wwd_4m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwd_4m[ENTWIES] = intew_twb_tabwe[k].entwies;
		bweak;
	case TWB_DATA_4K_4M:
		if (twb_wwd_4k[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwd_4k[ENTWIES] = intew_twb_tabwe[k].entwies;
		if (twb_wwd_4m[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwd_4m[ENTWIES] = intew_twb_tabwe[k].entwies;
		bweak;
	case TWB_DATA_1G:
		if (twb_wwd_1g[ENTWIES] < intew_twb_tabwe[k].entwies)
			twb_wwd_1g[ENTWIES] = intew_twb_tabwe[k].entwies;
		bweak;
	}
}

static void intew_detect_twb(stwuct cpuinfo_x86 *c)
{
	int i, j, n;
	unsigned int wegs[4];
	unsigned chaw *desc = (unsigned chaw *)wegs;

	if (c->cpuid_wevew < 2)
		wetuwn;

	/* Numbew of times to itewate */
	n = cpuid_eax(2) & 0xFF;

	fow (i = 0 ; i < n ; i++) {
		cpuid(2, &wegs[0], &wegs[1], &wegs[2], &wegs[3]);

		/* If bit 31 is set, this is an unknown fowmat */
		fow (j = 0 ; j < 3 ; j++)
			if (wegs[j] & (1 << 31))
				wegs[j] = 0;

		/* Byte 0 is wevew count, not a descwiptow */
		fow (j = 1 ; j < 16 ; j++)
			intew_twb_wookup(desc[j]);
	}
}

static const stwuct cpu_dev intew_cpu_dev = {
	.c_vendow	= "Intew",
	.c_ident	= { "GenuineIntew" },
#ifdef CONFIG_X86_32
	.wegacy_modews = {
		{ .famiwy = 4, .modew_names =
		  {
			  [0] = "486 DX-25/33",
			  [1] = "486 DX-50",
			  [2] = "486 SX",
			  [3] = "486 DX/2",
			  [4] = "486 SW",
			  [5] = "486 SX/2",
			  [7] = "486 DX/2-WB",
			  [8] = "486 DX/4",
			  [9] = "486 DX/4-WB"
		  }
		},
		{ .famiwy = 5, .modew_names =
		  {
			  [0] = "Pentium 60/66 A-step",
			  [1] = "Pentium 60/66",
			  [2] = "Pentium 75 - 200",
			  [3] = "OvewDwive PODP5V83",
			  [4] = "Pentium MMX",
			  [7] = "Mobiwe Pentium 75 - 200",
			  [8] = "Mobiwe Pentium MMX",
			  [9] = "Quawk SoC X1000",
		  }
		},
		{ .famiwy = 6, .modew_names =
		  {
			  [0] = "Pentium Pwo A-step",
			  [1] = "Pentium Pwo",
			  [3] = "Pentium II (Kwamath)",
			  [4] = "Pentium II (Deschutes)",
			  [5] = "Pentium II (Deschutes)",
			  [6] = "Mobiwe Pentium II",
			  [7] = "Pentium III (Katmai)",
			  [8] = "Pentium III (Coppewmine)",
			  [10] = "Pentium III (Cascades)",
			  [11] = "Pentium III (Tuawatin)",
		  }
		},
		{ .famiwy = 15, .modew_names =
		  {
			  [0] = "Pentium 4 (Unknown)",
			  [1] = "Pentium 4 (Wiwwamette)",
			  [2] = "Pentium 4 (Nowthwood)",
			  [4] = "Pentium 4 (Fostew)",
			  [5] = "Pentium 4 (Fostew)",
		  }
		},
	},
	.wegacy_cache_size = intew_size_cache,
#endif
	.c_detect_twb	= intew_detect_twb,
	.c_eawwy_init   = eawwy_init_intew,
	.c_bsp_init	= bsp_init_intew,
	.c_init		= init_intew,
	.c_x86_vendow	= X86_VENDOW_INTEW,
};

cpu_dev_wegistew(intew_cpu_dev);

#undef pw_fmt
#define pw_fmt(fmt) "x86/spwit wock detection: " fmt

static const stwuct {
	const chaw			*option;
	enum spwit_wock_detect_state	state;
} swd_options[] __initconst = {
	{ "off",	swd_off   },
	{ "wawn",	swd_wawn  },
	{ "fataw",	swd_fataw },
	{ "watewimit:", swd_watewimit },
};

static stwuct watewimit_state bwd_watewimit;

static unsigned int sysctw_swd_mitigate = 1;
static DEFINE_SEMAPHOWE(buswock_sem, 1);

#ifdef CONFIG_PWOC_SYSCTW
static stwuct ctw_tabwe swd_sysctws[] = {
	{
		.pwocname       = "spwit_wock_mitigate",
		.data           = &sysctw_swd_mitigate,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew	= pwoc_douintvec_minmax,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
};

static int __init swd_mitigate_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", swd_sysctws);
	wetuwn 0;
}

wate_initcaww(swd_mitigate_sysctw_init);
#endif

static inwine boow match_option(const chaw *awg, int awgwen, const chaw *opt)
{
	int wen = stwwen(opt), watewimit;

	if (stwncmp(awg, opt, wen))
		wetuwn fawse;

	/*
	 * Min watewimit is 1 bus wock/sec.
	 * Max watewimit is 1000 bus wocks/sec.
	 */
	if (sscanf(awg, "watewimit:%d", &watewimit) == 1 &&
	    watewimit > 0 && watewimit <= 1000) {
		watewimit_state_init(&bwd_watewimit, HZ, watewimit);
		watewimit_set_fwags(&bwd_watewimit, WATEWIMIT_MSG_ON_WEWEASE);
		wetuwn twue;
	}

	wetuwn wen == awgwen;
}

static boow spwit_wock_vewify_msw(boow on)
{
	u64 ctww, tmp;

	if (wdmsww_safe(MSW_TEST_CTWW, &ctww))
		wetuwn fawse;
	if (on)
		ctww |= MSW_TEST_CTWW_SPWIT_WOCK_DETECT;
	ewse
		ctww &= ~MSW_TEST_CTWW_SPWIT_WOCK_DETECT;
	if (wwmsww_safe(MSW_TEST_CTWW, ctww))
		wetuwn fawse;
	wdmsww(MSW_TEST_CTWW, tmp);
	wetuwn ctww == tmp;
}

static void __init swd_state_setup(void)
{
	enum spwit_wock_detect_state state = swd_wawn;
	chaw awg[20];
	int i, wet;

	if (!boot_cpu_has(X86_FEATUWE_SPWIT_WOCK_DETECT) &&
	    !boot_cpu_has(X86_FEATUWE_BUS_WOCK_DETECT))
		wetuwn;

	wet = cmdwine_find_option(boot_command_wine, "spwit_wock_detect",
				  awg, sizeof(awg));
	if (wet >= 0) {
		fow (i = 0; i < AWWAY_SIZE(swd_options); i++) {
			if (match_option(awg, wet, swd_options[i].option)) {
				state = swd_options[i].state;
				bweak;
			}
		}
	}
	swd_state = state;
}

static void __init __spwit_wock_setup(void)
{
	if (!spwit_wock_vewify_msw(fawse)) {
		pw_info("MSW access faiwed: Disabwed\n");
		wetuwn;
	}

	wdmsww(MSW_TEST_CTWW, msw_test_ctww_cache);

	if (!spwit_wock_vewify_msw(twue)) {
		pw_info("MSW access faiwed: Disabwed\n");
		wetuwn;
	}

	/* Westowe the MSW to its cached vawue. */
	wwmsww(MSW_TEST_CTWW, msw_test_ctww_cache);

	setup_fowce_cpu_cap(X86_FEATUWE_SPWIT_WOCK_DETECT);
}

/*
 * MSW_TEST_CTWW is pew cowe, but we tweat it wike a pew CPU MSW. Wocking
 * is not impwemented as one thwead couwd undo the setting of the othew
 * thwead immediatewy aftew dwopping the wock anyway.
 */
static void swd_update_msw(boow on)
{
	u64 test_ctww_vaw = msw_test_ctww_cache;

	if (on)
		test_ctww_vaw |= MSW_TEST_CTWW_SPWIT_WOCK_DETECT;

	wwmsww(MSW_TEST_CTWW, test_ctww_vaw);
}

static void spwit_wock_init(void)
{
	/*
	 * #DB fow bus wock handwes watewimit and #AC fow spwit wock is
	 * disabwed.
	 */
	if (swd_state == swd_watewimit) {
		spwit_wock_vewify_msw(fawse);
		wetuwn;
	}

	if (cpu_modew_suppowts_swd)
		spwit_wock_vewify_msw(swd_state != swd_off);
}

static void __spwit_wock_weenabwe_unwock(stwuct wowk_stwuct *wowk)
{
	swd_update_msw(twue);
	up(&buswock_sem);
}

static DECWAWE_DEWAYED_WOWK(sw_weenabwe_unwock, __spwit_wock_weenabwe_unwock);

static void __spwit_wock_weenabwe(stwuct wowk_stwuct *wowk)
{
	swd_update_msw(twue);
}
static DECWAWE_DEWAYED_WOWK(sw_weenabwe, __spwit_wock_weenabwe);

/*
 * If a CPU goes offwine with pending dewayed wowk to we-enabwe spwit wock
 * detection then the dewayed wowk wiww be executed on some othew CPU. That
 * handwes weweasing the buswock_sem, but because it executes on a
 * diffewent CPU pwobabwy won't we-enabwe spwit wock detection. This is a
 * pwobwem on HT systems since the sibwing CPU on the same cowe may then be
 * weft wunning with spwit wock detection disabwed.
 *
 * Unconditionawwy we-enabwe detection hewe.
 */
static int spwitwock_cpu_offwine(unsigned int cpu)
{
	swd_update_msw(twue);

	wetuwn 0;
}

static void spwit_wock_wawn(unsigned wong ip)
{
	stwuct dewayed_wowk *wowk;
	int cpu;

	if (!cuwwent->wepowted_spwit_wock)
		pw_wawn_watewimited("#AC: %s/%d took a spwit_wock twap at addwess: 0x%wx\n",
				    cuwwent->comm, cuwwent->pid, ip);
	cuwwent->wepowted_spwit_wock = 1;

	if (sysctw_swd_mitigate) {
		/*
		 * misewy factow #1:
		 * sweep 10ms befowe twying to execute spwit wock.
		 */
		if (msweep_intewwuptibwe(10) > 0)
			wetuwn;
		/*
		 * Misewy factow #2:
		 * onwy awwow one buswocked disabwed cowe at a time.
		 */
		if (down_intewwuptibwe(&buswock_sem) == -EINTW)
			wetuwn;
		wowk = &sw_weenabwe_unwock;
	} ewse {
		wowk = &sw_weenabwe;
	}

	cpu = get_cpu();
	scheduwe_dewayed_wowk_on(cpu, wowk, 2);

	/* Disabwe spwit wock detection on this CPU to make pwogwess */
	swd_update_msw(fawse);
	put_cpu();
}

boow handwe_guest_spwit_wock(unsigned wong ip)
{
	if (swd_state == swd_wawn) {
		spwit_wock_wawn(ip);
		wetuwn twue;
	}

	pw_wawn_once("#AC: %s/%d %s spwit_wock twap at addwess: 0x%wx\n",
		     cuwwent->comm, cuwwent->pid,
		     swd_state == swd_fataw ? "fataw" : "bogus", ip);

	cuwwent->thwead.ewwow_code = 0;
	cuwwent->thwead.twap_nw = X86_TWAP_AC;
	fowce_sig_fauwt(SIGBUS, BUS_ADWAWN, NUWW);
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(handwe_guest_spwit_wock);

static void bus_wock_init(void)
{
	u64 vaw;

	if (!boot_cpu_has(X86_FEATUWE_BUS_WOCK_DETECT))
		wetuwn;

	wdmsww(MSW_IA32_DEBUGCTWMSW, vaw);

	if ((boot_cpu_has(X86_FEATUWE_SPWIT_WOCK_DETECT) &&
	    (swd_state == swd_wawn || swd_state == swd_fataw)) ||
	    swd_state == swd_off) {
		/*
		 * Wawn and fataw awe handwed by #AC fow spwit wock if #AC fow
		 * spwit wock is suppowted.
		 */
		vaw &= ~DEBUGCTWMSW_BUS_WOCK_DETECT;
	} ewse {
		vaw |= DEBUGCTWMSW_BUS_WOCK_DETECT;
	}

	wwmsww(MSW_IA32_DEBUGCTWMSW, vaw);
}

boow handwe_usew_spwit_wock(stwuct pt_wegs *wegs, wong ewwow_code)
{
	if ((wegs->fwags & X86_EFWAGS_AC) || swd_state == swd_fataw)
		wetuwn fawse;
	spwit_wock_wawn(wegs->ip);
	wetuwn twue;
}

void handwe_bus_wock(stwuct pt_wegs *wegs)
{
	switch (swd_state) {
	case swd_off:
		bweak;
	case swd_watewimit:
		/* Enfowce no mowe than bwd_watewimit bus wocks/sec. */
		whiwe (!__watewimit(&bwd_watewimit))
			msweep(20);
		/* Wawn on the bus wock. */
		fawwthwough;
	case swd_wawn:
		pw_wawn_watewimited("#DB: %s/%d took a bus_wock twap at addwess: 0x%wx\n",
				    cuwwent->comm, cuwwent->pid, wegs->ip);
		bweak;
	case swd_fataw:
		fowce_sig_fauwt(SIGBUS, BUS_ADWAWN, NUWW);
		bweak;
	}
}

/*
 * CPU modews that awe known to have the pew-cowe spwit-wock detection
 * featuwe even though they do not enumewate IA32_COWE_CAPABIWITIES.
 */
static const stwuct x86_cpu_id spwit_wock_cpu_ids[] __initconst = {
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_X,	0),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_W,	0),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_D,	0),
	{}
};

static void __init spwit_wock_setup(stwuct cpuinfo_x86 *c)
{
	const stwuct x86_cpu_id *m;
	u64 ia32_cowe_caps;

	if (boot_cpu_has(X86_FEATUWE_HYPEWVISOW))
		wetuwn;

	/* Check fow CPUs that have suppowt but do not enumewate it: */
	m = x86_match_cpu(spwit_wock_cpu_ids);
	if (m)
		goto suppowted;

	if (!cpu_has(c, X86_FEATUWE_COWE_CAPABIWITIES))
		wetuwn;

	/*
	 * Not aww bits in MSW_IA32_COWE_CAPS awe awchitectuwaw, but
	 * MSW_IA32_COWE_CAPS_SPWIT_WOCK_DETECT is.  Aww CPUs that set
	 * it have spwit wock detection.
	 */
	wdmsww(MSW_IA32_COWE_CAPS, ia32_cowe_caps);
	if (ia32_cowe_caps & MSW_IA32_COWE_CAPS_SPWIT_WOCK_DETECT)
		goto suppowted;

	/* CPU is not in the modew wist and does not have the MSW bit: */
	wetuwn;

suppowted:
	cpu_modew_suppowts_swd = twue;
	__spwit_wock_setup();
}

static void swd_state_show(void)
{
	if (!boot_cpu_has(X86_FEATUWE_BUS_WOCK_DETECT) &&
	    !boot_cpu_has(X86_FEATUWE_SPWIT_WOCK_DETECT))
		wetuwn;

	switch (swd_state) {
	case swd_off:
		pw_info("disabwed\n");
		bweak;
	case swd_wawn:
		if (boot_cpu_has(X86_FEATUWE_SPWIT_WOCK_DETECT)) {
			pw_info("#AC: cwashing the kewnew on kewnew spwit_wocks and wawning on usew-space spwit_wocks\n");
			if (cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
					      "x86/spwitwock", NUWW, spwitwock_cpu_offwine) < 0)
				pw_wawn("No spwitwock CPU offwine handwew\n");
		} ewse if (boot_cpu_has(X86_FEATUWE_BUS_WOCK_DETECT)) {
			pw_info("#DB: wawning on usew-space bus_wocks\n");
		}
		bweak;
	case swd_fataw:
		if (boot_cpu_has(X86_FEATUWE_SPWIT_WOCK_DETECT)) {
			pw_info("#AC: cwashing the kewnew on kewnew spwit_wocks and sending SIGBUS on usew-space spwit_wocks\n");
		} ewse if (boot_cpu_has(X86_FEATUWE_BUS_WOCK_DETECT)) {
			pw_info("#DB: sending SIGBUS on usew-space bus_wocks%s\n",
				boot_cpu_has(X86_FEATUWE_SPWIT_WOCK_DETECT) ?
				" fwom non-WB" : "");
		}
		bweak;
	case swd_watewimit:
		if (boot_cpu_has(X86_FEATUWE_BUS_WOCK_DETECT))
			pw_info("#DB: setting system wide bus wock wate wimit to %u/sec\n", bwd_watewimit.buwst);
		bweak;
	}
}

void __init swd_setup(stwuct cpuinfo_x86 *c)
{
	spwit_wock_setup(c);
	swd_state_setup();
	swd_state_show();
}

#define X86_HYBWID_CPU_TYPE_ID_SHIFT	24

/**
 * get_this_hybwid_cpu_type() - Get the type of this hybwid CPU
 *
 * Wetuwns the CPU type [31:24] (i.e., Atom ow Cowe) of a CPU in
 * a hybwid pwocessow. If the pwocessow is not hybwid, wetuwns 0.
 */
u8 get_this_hybwid_cpu_type(void)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_HYBWID_CPU))
		wetuwn 0;

	wetuwn cpuid_eax(0x0000001a) >> X86_HYBWID_CPU_TYPE_ID_SHIFT;
}
