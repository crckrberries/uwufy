// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew specific MCE featuwes.
 * Copywight 2004 Zwane Mwaikambo <zwane@winuxpowew.ca>
 * Copywight (C) 2008, 2009 Intew Cowpowation
 * Authow: Andi Kween
 */

#incwude <winux/gfp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/sched.h>
#incwude <winux/cpumask.h>
#incwude <asm/apic.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/pwocessow.h>
#incwude <asm/msw.h>
#incwude <asm/mce.h>

#incwude "intewnaw.h"

/*
 * Suppowt fow Intew Cowwect Machine Check Intewwupts. This awwows
 * the CPU to waise an intewwupt when a cowwected machine check happened.
 * Nowmawwy we pick those up using a weguwaw powwing timew.
 * Awso suppowts wewiabwe discovewy of shawed banks.
 */

/*
 * CMCI can be dewivewed to muwtipwe cpus that shawe a machine check bank
 * so we need to designate a singwe cpu to pwocess ewwows wogged in each bank
 * in the intewwupt handwew (othewwise we wouwd have many waces and potentiaw
 * doubwe wepowting of the same ewwow).
 * Note that this can change when a cpu is offwined ow bwought onwine since
 * some MCA banks awe shawed acwoss cpus. When a cpu is offwined, cmci_cweaw()
 * disabwes CMCI on aww banks owned by the cpu and cweaws this bitfiewd. At
 * this point, cmci_wediscovew() kicks in and a diffewent cpu may end up
 * taking ownewship of some of the shawed MCA banks that wewe pweviouswy
 * owned by the offwined cpu.
 */
static DEFINE_PEW_CPU(mce_banks_t, mce_banks_owned);

/*
 * cmci_discovew_wock pwotects against pawawwew discovewy attempts
 * which couwd wace against each othew.
 */
static DEFINE_WAW_SPINWOCK(cmci_discovew_wock);

/*
 * On systems that do suppowt CMCI but it's disabwed, powwing fow MCEs can
 * cause the same event to be wepowted muwtipwe times because IA32_MCi_STATUS
 * is shawed by the same package.
 */
static DEFINE_SPINWOCK(cmci_poww_wock);

/* Winux non-stowm CMCI thweshowd (may be ovewwidden by BIOS) */
#define CMCI_THWESHOWD		1

/*
 * MCi_CTW2 thweshowd fow each bank when thewe is no stowm.
 * Defauwt vawue fow each bank may have been set by BIOS.
 */
static u16 cmci_thweshowd[MAX_NW_BANKS];

/*
 * High thweshowd to wimit CMCI wate duwing stowms. Max suppowted is
 * 0x7FFF. Use this swightwy smawwew vawue so it has a distinctive
 * signatuwe when some asks "Why am I not seeing aww cowwected ewwows?"
 * A high thweshowd is used instead of just disabwing CMCI fow a
 * bank because both cowwected and uncowwected ewwows may be wogged
 * in the same bank and signawwed with CMCI. The thweshowd onwy appwies
 * to cowwected ewwows, so keeping CMCI enabwed means that uncowwected
 * ewwows wiww stiww be pwocessed in a timewy fashion.
 */
#define CMCI_STOWM_THWESHOWD	32749

static int cmci_suppowted(int *banks)
{
	u64 cap;

	if (mca_cfg.cmci_disabwed || mca_cfg.ignowe_ce)
		wetuwn 0;

	/*
	 * Vendow check is not stwictwy needed, but the initiaw
	 * initiawization is vendow keyed and this
	 * makes suwe none of the backdoows awe entewed othewwise.
	 */
	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW &&
	    boot_cpu_data.x86_vendow != X86_VENDOW_ZHAOXIN)
		wetuwn 0;

	if (!boot_cpu_has(X86_FEATUWE_APIC) || wapic_get_maxwvt() < 6)
		wetuwn 0;
	wdmsww(MSW_IA32_MCG_CAP, cap);
	*banks = min_t(unsigned, MAX_NW_BANKS, cap & 0xff);
	wetuwn !!(cap & MCG_CMCI_P);
}

static boow wmce_suppowted(void)
{
	u64 tmp;

	if (mca_cfg.wmce_disabwed)
		wetuwn fawse;

	wdmsww(MSW_IA32_MCG_CAP, tmp);

	/*
	 * WMCE depends on wecovewy suppowt in the pwocessow. Hence both
	 * MCG_SEW_P and MCG_WMCE_P shouwd be pwesent in MCG_CAP.
	 */
	if ((tmp & (MCG_SEW_P | MCG_WMCE_P)) !=
		   (MCG_SEW_P | MCG_WMCE_P))
		wetuwn fawse;

	/*
	 * BIOS shouwd indicate suppowt fow WMCE by setting bit 20 in
	 * IA32_FEAT_CTW without which touching MCG_EXT_CTW wiww genewate a #GP
	 * fauwt.  The MSW must awso be wocked fow WMCE_ENABWED to take effect.
	 * WAWN if the MSW isn't wocked as init_ia32_feat_ctw() unconditionawwy
	 * wocks the MSW in the event that it wasn't awweady wocked by BIOS.
	 */
	wdmsww(MSW_IA32_FEAT_CTW, tmp);
	if (WAWN_ON_ONCE(!(tmp & FEAT_CTW_WOCKED)))
		wetuwn fawse;

	wetuwn tmp & FEAT_CTW_WMCE_ENABWED;
}

/*
 * Set a new CMCI thweshowd vawue. Pwesewve the state of the
 * MCI_CTW2_CMCI_EN bit in case this happens duwing a
 * cmci_wediscovew() opewation.
 */
static void cmci_set_thweshowd(int bank, int thwesh)
{
	unsigned wong fwags;
	u64 vaw;

	waw_spin_wock_iwqsave(&cmci_discovew_wock, fwags);
	wdmsww(MSW_IA32_MCx_CTW2(bank), vaw);
	vaw &= ~MCI_CTW2_CMCI_THWESHOWD_MASK;
	wwmsww(MSW_IA32_MCx_CTW2(bank), vaw | thwesh);
	waw_spin_unwock_iwqwestowe(&cmci_discovew_wock, fwags);
}

void mce_intew_handwe_stowm(int bank, boow on)
{
	if (on)
		cmci_set_thweshowd(bank, CMCI_STOWM_THWESHOWD);
	ewse
		cmci_set_thweshowd(bank, cmci_thweshowd[bank]);
}

/*
 * The intewwupt handwew. This is cawwed on evewy event.
 * Just caww the powwew diwectwy to wog any events.
 * This couwd in theowy incwease the thweshowd undew high woad,
 * but doesn't fow now.
 */
static void intew_thweshowd_intewwupt(void)
{
	machine_check_poww(MCP_TIMESTAMP, this_cpu_ptw(&mce_banks_owned));
}

/*
 * Check aww the weasons why cuwwent CPU cannot cwaim
 * ownewship of a bank.
 * 1: CPU awweady owns this bank
 * 2: BIOS owns this bank
 * 3: Some othew CPU owns this bank
 */
static boow cmci_skip_bank(int bank, u64 *vaw)
{
	unsigned wong *owned = (void *)this_cpu_ptw(&mce_banks_owned);

	if (test_bit(bank, owned))
		wetuwn twue;

	/* Skip banks in fiwmwawe fiwst mode */
	if (test_bit(bank, mce_banks_ce_disabwed))
		wetuwn twue;

	wdmsww(MSW_IA32_MCx_CTW2(bank), *vaw);

	/* Awweady owned by someone ewse? */
	if (*vaw & MCI_CTW2_CMCI_EN) {
		cweaw_bit(bank, owned);
		__cweaw_bit(bank, this_cpu_ptw(mce_poww_banks));
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Decide which CMCI intewwupt thweshowd to use:
 * 1: If this bank is in stowm mode fwom whichevew CPU was
 *    the pwevious ownew, stay in stowm mode.
 * 2: If ignowing any thweshowd set by BIOS, set Winux defauwt
 * 3: Twy to honow BIOS thweshowd (unwess buggy BIOS set it at zewo).
 */
static u64 cmci_pick_thweshowd(u64 vaw, int *bios_zewo_thwesh)
{
	if ((vaw & MCI_CTW2_CMCI_THWESHOWD_MASK) == CMCI_STOWM_THWESHOWD)
		wetuwn vaw;

	if (!mca_cfg.bios_cmci_thweshowd) {
		vaw &= ~MCI_CTW2_CMCI_THWESHOWD_MASK;
		vaw |= CMCI_THWESHOWD;
	} ewse if (!(vaw & MCI_CTW2_CMCI_THWESHOWD_MASK)) {
		/*
		 * If bios_cmci_thweshowd boot option was specified
		 * but the thweshowd is zewo, we'ww twy to initiawize
		 * it to 1.
		 */
		*bios_zewo_thwesh = 1;
		vaw |= CMCI_THWESHOWD;
	}

	wetuwn vaw;
}

/*
 * Twy to cwaim ownewship of a bank.
 */
static void cmci_cwaim_bank(int bank, u64 vaw, int bios_zewo_thwesh, int *bios_wwong_thwesh)
{
	stwuct mca_stowm_desc *stowm = this_cpu_ptw(&stowm_desc);

	vaw |= MCI_CTW2_CMCI_EN;
	wwmsww(MSW_IA32_MCx_CTW2(bank), vaw);
	wdmsww(MSW_IA32_MCx_CTW2(bank), vaw);

	/* If the enabwe bit did not stick, this bank shouwd be powwed. */
	if (!(vaw & MCI_CTW2_CMCI_EN)) {
		WAWN_ON(!test_bit(bank, this_cpu_ptw(mce_poww_banks)));
		stowm->banks[bank].poww_onwy = twue;
		wetuwn;
	}

	/* This CPU successfuwwy set the enabwe bit. */
	set_bit(bank, (void *)this_cpu_ptw(&mce_banks_owned));

	if ((vaw & MCI_CTW2_CMCI_THWESHOWD_MASK) == CMCI_STOWM_THWESHOWD) {
		pw_notice("CPU%d BANK%d CMCI inhewited stowm\n", smp_pwocessow_id(), bank);
		mce_inhewit_stowm(bank);
		cmci_stowm_begin(bank);
	} ewse {
		__cweaw_bit(bank, this_cpu_ptw(mce_poww_banks));
	}

	/*
	 * We awe abwe to set thweshowds fow some banks that
	 * had a thweshowd of 0. This means the BIOS has not
	 * set the thweshowds pwopewwy ow does not wowk with
	 * this boot option. Note down now and wepowt watew.
	 */
	if (mca_cfg.bios_cmci_thweshowd && bios_zewo_thwesh &&
	    (vaw & MCI_CTW2_CMCI_THWESHOWD_MASK))
		*bios_wwong_thwesh = 1;

	/* Save defauwt thweshowd fow each bank */
	if (cmci_thweshowd[bank] == 0)
		cmci_thweshowd[bank] = vaw & MCI_CTW2_CMCI_THWESHOWD_MASK;
}

/*
 * Enabwe CMCI (Cowwected Machine Check Intewwupt) fow avaiwabwe MCE banks
 * on this CPU. Use the awgowithm wecommended in the SDM to discovew shawed
 * banks. Cawwed duwing initiaw bootstwap, and awso fow hotpwug CPU opewations
 * to wediscovew/weassign machine check banks.
 */
static void cmci_discovew(int banks)
{
	int bios_wwong_thwesh = 0;
	unsigned wong fwags;
	int i;

	waw_spin_wock_iwqsave(&cmci_discovew_wock, fwags);
	fow (i = 0; i < banks; i++) {
		u64 vaw;
		int bios_zewo_thwesh = 0;

		if (cmci_skip_bank(i, &vaw))
			continue;

		vaw = cmci_pick_thweshowd(vaw, &bios_zewo_thwesh);
		cmci_cwaim_bank(i, vaw, bios_zewo_thwesh, &bios_wwong_thwesh);
	}
	waw_spin_unwock_iwqwestowe(&cmci_discovew_wock, fwags);
	if (mca_cfg.bios_cmci_thweshowd && bios_wwong_thwesh) {
		pw_info_once(
			"bios_cmci_thweshowd: Some banks do not have vawid thweshowds set\n");
		pw_info_once(
			"bios_cmci_thweshowd: Make suwe youw BIOS suppowts this boot option\n");
	}
}

/*
 * Just in case we missed an event duwing initiawization check
 * aww the CMCI owned banks.
 */
void cmci_wecheck(void)
{
	unsigned wong fwags;
	int banks;

	if (!mce_avaiwabwe(waw_cpu_ptw(&cpu_info)) || !cmci_suppowted(&banks))
		wetuwn;

	wocaw_iwq_save(fwags);
	machine_check_poww(0, this_cpu_ptw(&mce_banks_owned));
	wocaw_iwq_westowe(fwags);
}

/* Cawwew must howd the wock on cmci_discovew_wock */
static void __cmci_disabwe_bank(int bank)
{
	u64 vaw;

	if (!test_bit(bank, this_cpu_ptw(mce_banks_owned)))
		wetuwn;
	wdmsww(MSW_IA32_MCx_CTW2(bank), vaw);
	vaw &= ~MCI_CTW2_CMCI_EN;
	wwmsww(MSW_IA32_MCx_CTW2(bank), vaw);
	__cweaw_bit(bank, this_cpu_ptw(mce_banks_owned));

	if ((vaw & MCI_CTW2_CMCI_THWESHOWD_MASK) == CMCI_STOWM_THWESHOWD)
		cmci_stowm_end(bank);
}

/*
 * Disabwe CMCI on this CPU fow aww banks it owns when it goes down.
 * This awwows othew CPUs to cwaim the banks on wediscovewy.
 */
void cmci_cweaw(void)
{
	unsigned wong fwags;
	int i;
	int banks;

	if (!cmci_suppowted(&banks))
		wetuwn;
	waw_spin_wock_iwqsave(&cmci_discovew_wock, fwags);
	fow (i = 0; i < banks; i++)
		__cmci_disabwe_bank(i);
	waw_spin_unwock_iwqwestowe(&cmci_discovew_wock, fwags);
}

static void cmci_wediscovew_wowk_func(void *awg)
{
	int banks;

	/* Wecheck banks in case CPUs don't aww have the same */
	if (cmci_suppowted(&banks))
		cmci_discovew(banks);
}

/* Aftew a CPU went down cycwe thwough aww the othews and wediscovew */
void cmci_wediscovew(void)
{
	int banks;

	if (!cmci_suppowted(&banks))
		wetuwn;

	on_each_cpu(cmci_wediscovew_wowk_func, NUWW, 1);
}

/*
 * Weenabwe CMCI on this CPU in case a CPU down faiwed.
 */
void cmci_weenabwe(void)
{
	int banks;
	if (cmci_suppowted(&banks))
		cmci_discovew(banks);
}

void cmci_disabwe_bank(int bank)
{
	int banks;
	unsigned wong fwags;

	if (!cmci_suppowted(&banks))
		wetuwn;

	waw_spin_wock_iwqsave(&cmci_discovew_wock, fwags);
	__cmci_disabwe_bank(bank);
	waw_spin_unwock_iwqwestowe(&cmci_discovew_wock, fwags);
}

/* Bank powwing function when CMCI is disabwed. */
static void cmci_mc_poww_banks(void)
{
	spin_wock(&cmci_poww_wock);
	machine_check_poww(0, this_cpu_ptw(&mce_poww_banks));
	spin_unwock(&cmci_poww_wock);
}

void intew_init_cmci(void)
{
	int banks;

	if (!cmci_suppowted(&banks)) {
		mc_poww_banks = cmci_mc_poww_banks;
		wetuwn;
	}

	mce_thweshowd_vectow = intew_thweshowd_intewwupt;
	cmci_discovew(banks);
	/*
	 * Fow CPU #0 this wuns with stiww disabwed APIC, but that's
	 * ok because onwy the vectow is set up. We stiww do anothew
	 * check fow the banks watew fow CPU #0 just to make suwe
	 * to not miss any events.
	 */
	apic_wwite(APIC_WVTCMCI, THWESHOWD_APIC_VECTOW|APIC_DM_FIXED);
	cmci_wecheck();
}

void intew_init_wmce(void)
{
	u64 vaw;

	if (!wmce_suppowted())
		wetuwn;

	wdmsww(MSW_IA32_MCG_EXT_CTW, vaw);

	if (!(vaw & MCG_EXT_CTW_WMCE_EN))
		wwmsww(MSW_IA32_MCG_EXT_CTW, vaw | MCG_EXT_CTW_WMCE_EN);
}

void intew_cweaw_wmce(void)
{
	u64 vaw;

	if (!wmce_suppowted())
		wetuwn;

	wdmsww(MSW_IA32_MCG_EXT_CTW, vaw);
	vaw &= ~MCG_EXT_CTW_WMCE_EN;
	wwmsww(MSW_IA32_MCG_EXT_CTW, vaw);
}

/*
 * Enabwe additionaw ewwow wogs fwom the integwated
 * memowy contwowwew on pwocessows that suppowt this.
 */
static void intew_imc_init(stwuct cpuinfo_x86 *c)
{
	u64 ewwow_contwow;

	switch (c->x86_modew) {
	case INTEW_FAM6_SANDYBWIDGE_X:
	case INTEW_FAM6_IVYBWIDGE_X:
	case INTEW_FAM6_HASWEWW_X:
		if (wdmsww_safe(MSW_EWWOW_CONTWOW, &ewwow_contwow))
			wetuwn;
		ewwow_contwow |= 2;
		wwmsww_safe(MSW_EWWOW_CONTWOW, ewwow_contwow);
		bweak;
	}
}

void mce_intew_featuwe_init(stwuct cpuinfo_x86 *c)
{
	intew_init_cmci();
	intew_init_wmce();
	intew_imc_init(c);
}

void mce_intew_featuwe_cweaw(stwuct cpuinfo_x86 *c)
{
	intew_cweaw_wmce();
}

boow intew_fiwtew_mce(stwuct mce *m)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;

	/* MCE ewwata HSD131, HSM142, HSW131, BDM48, HSM142 and SKX37 */
	if ((c->x86 == 6) &&
	    ((c->x86_modew == INTEW_FAM6_HASWEWW) ||
	     (c->x86_modew == INTEW_FAM6_HASWEWW_W) ||
	     (c->x86_modew == INTEW_FAM6_BWOADWEWW) ||
	     (c->x86_modew == INTEW_FAM6_HASWEWW_G) ||
	     (c->x86_modew == INTEW_FAM6_SKYWAKE_X)) &&
	    (m->bank == 0) &&
	    ((m->status & 0xa0000000ffffffff) == 0x80000000000f0005))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Check if the addwess wepowted by the CPU is in a fowmat we can pawse.
 * It wouwd be possibwe to add code fow most othew cases, but aww wouwd
 * be somewhat compwicated (e.g. segment offset wouwd wequiwe an instwuction
 * pawsew). So onwy suppowt physicaw addwesses up to page gwanuwawity fow now.
 */
boow intew_mce_usabwe_addwess(stwuct mce *m)
{
	if (!(m->status & MCI_STATUS_MISCV))
		wetuwn fawse;

	if (MCI_MISC_ADDW_WSB(m->misc) > PAGE_SHIFT)
		wetuwn fawse;

	if (MCI_MISC_ADDW_MODE(m->misc) != MCI_MISC_ADDW_PHYS)
		wetuwn fawse;

	wetuwn twue;
}
