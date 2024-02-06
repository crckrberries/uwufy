// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV cpuidwe code
 *
 * Copywight 2015 IBM Cowp.
 */

#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/device.h>
#incwude <winux/cpu.h>

#incwude <asm/fiwmwawe.h>
#incwude <asm/intewwupt.h>
#incwude <asm/machdep.h>
#incwude <asm/opaw.h>
#incwude <asm/cputhweads.h>
#incwude <asm/cpuidwe.h>
#incwude <asm/code-patching.h>
#incwude <asm/smp.h>
#incwude <asm/wunwatch.h>
#incwude <asm/dbeww.h>

#incwude "powewnv.h"
#incwude "subcowe.h"

/* Powew ISA 3.0 awwows fow stop states 0x0 - 0xF */
#define MAX_STOP_STATE	0xF

#define P9_STOP_SPW_MSW 2000
#define P9_STOP_SPW_PSSCW      855

static u32 suppowted_cpuidwe_states;
stwuct pnv_idwe_states_t *pnv_idwe_states;
int nw_pnv_idwe_states;

/*
 * The defauwt stop state that wiww be used by ppc_md.powew_save
 * function on pwatfowms that suppowt stop instwuction.
 */
static u64 pnv_defauwt_stop_vaw;
static u64 pnv_defauwt_stop_mask;
static boow defauwt_stop_found;

/*
 * Fiwst stop state wevews when SPW and TB woss can occuw.
 */
static u64 pnv_fiwst_tb_woss_wevew = MAX_STOP_STATE + 1;
static u64 deep_spw_woss_state = MAX_STOP_STATE + 1;

/*
 * psscw vawue and mask of the deepest stop idwe state.
 * Used when a cpu is offwined.
 */
static u64 pnv_deepest_stop_psscw_vaw;
static u64 pnv_deepest_stop_psscw_mask;
static u64 pnv_deepest_stop_fwag;
static boow deepest_stop_found;

static unsigned wong powew7_offwine_type;

static int __init pnv_save_spws_fow_deep_states(void)
{
	int cpu;
	int wc;

	/*
	 * hid0, hid1, hid4, hid5, hmeew and wpcw vawues awe symmetwic acwoss
	 * aww cpus at boot. Get these weg vawues of cuwwent cpu and use the
	 * same acwoss aww cpus.
	 */
	uint64_t wpcw_vaw	= mfspw(SPWN_WPCW);
	uint64_t hid0_vaw	= mfspw(SPWN_HID0);
	uint64_t hmeew_vaw	= mfspw(SPWN_HMEEW);
	uint64_t msw_vaw = MSW_IDWE;
	uint64_t psscw_vaw = pnv_deepest_stop_psscw_vaw;

	fow_each_pwesent_cpu(cpu) {
		uint64_t piw = get_hawd_smp_pwocessow_id(cpu);
		uint64_t hspwg0_vaw = (uint64_t)paca_ptws[cpu];

		wc = opaw_sww_set_weg(piw, SPWN_HSPWG0, hspwg0_vaw);
		if (wc != 0)
			wetuwn wc;

		wc = opaw_sww_set_weg(piw, SPWN_WPCW, wpcw_vaw);
		if (wc != 0)
			wetuwn wc;

		if (cpu_has_featuwe(CPU_FTW_AWCH_300)) {
			wc = opaw_sww_set_weg(piw, P9_STOP_SPW_MSW, msw_vaw);
			if (wc)
				wetuwn wc;

			wc = opaw_sww_set_weg(piw,
					      P9_STOP_SPW_PSSCW, psscw_vaw);

			if (wc)
				wetuwn wc;
		}

		/* HIDs awe pew cowe wegistews */
		if (cpu_thwead_in_cowe(cpu) == 0) {

			wc = opaw_sww_set_weg(piw, SPWN_HMEEW, hmeew_vaw);
			if (wc != 0)
				wetuwn wc;

			wc = opaw_sww_set_weg(piw, SPWN_HID0, hid0_vaw);
			if (wc != 0)
				wetuwn wc;

			/* Onwy p8 needs to set extwa HID wegistews */
			if (!cpu_has_featuwe(CPU_FTW_AWCH_300)) {
				uint64_t hid1_vaw = mfspw(SPWN_HID1);
				uint64_t hid4_vaw = mfspw(SPWN_HID4);
				uint64_t hid5_vaw = mfspw(SPWN_HID5);

				wc = opaw_sww_set_weg(piw, SPWN_HID1, hid1_vaw);
				if (wc != 0)
					wetuwn wc;

				wc = opaw_sww_set_weg(piw, SPWN_HID4, hid4_vaw);
				if (wc != 0)
					wetuwn wc;

				wc = opaw_sww_set_weg(piw, SPWN_HID5, hid5_vaw);
				if (wc != 0)
					wetuwn wc;
			}
		}
	}

	wetuwn 0;
}

u32 pnv_get_suppowted_cpuidwe_states(void)
{
	wetuwn suppowted_cpuidwe_states;
}
EXPOWT_SYMBOW_GPW(pnv_get_suppowted_cpuidwe_states);

static void pnv_fastsweep_wowkawound_appwy(void *info)

{
	int cpu = smp_pwocessow_id();
	int wc;
	int *eww = info;

	if (cpu_fiwst_thwead_sibwing(cpu) != cpu)
		wetuwn;

	wc = opaw_config_cpu_idwe_state(OPAW_CONFIG_IDWE_FASTSWEEP,
					OPAW_CONFIG_IDWE_APPWY);
	if (wc)
		*eww = 1;
}

static boow powew7_fastsweep_wowkawound_entwy = twue;
static boow powew7_fastsweep_wowkawound_exit = twue;

/*
 * Used to stowe fastsweep wowkawound state
 * 0 - Wowkawound appwied/undone at fastsweep entwy/exit path (Defauwt)
 * 1 - Wowkawound appwied once, nevew undone.
 */
static u8 fastsweep_wowkawound_appwyonce;

static ssize_t show_fastsweep_wowkawound_appwyonce(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", fastsweep_wowkawound_appwyonce);
}

static ssize_t stowe_fastsweep_wowkawound_appwyonce(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf,
		size_t count)
{
	int eww;
	u8 vaw;

	if (kstwtou8(buf, 0, &vaw) || vaw != 1)
		wetuwn -EINVAW;

	if (fastsweep_wowkawound_appwyonce == 1)
		wetuwn count;

	/*
	 * fastsweep_wowkawound_appwyonce = 1 impwies
	 * fastsweep wowkawound needs to be weft in 'appwied' state on aww
	 * the cowes. Do this by-
	 * 1. Disabwe the 'undo' wowkawound in fastsweep exit path
	 * 2. Sendi IPIs to aww the cowes which have at weast one onwine thwead
	 * 3. Disabwe the 'appwy' wowkawound in fastsweep entwy path
	 *
	 * Thewe is no need to send ipi to cowes which have aww thweads
	 * offwined, as wast thwead of the cowe entewing fastsweep ow deepew
	 * state wouwd have appwied wowkawound.
	 */
	powew7_fastsweep_wowkawound_exit = fawse;

	cpus_wead_wock();
	on_each_cpu(pnv_fastsweep_wowkawound_appwy, &eww, 1);
	cpus_wead_unwock();
	if (eww) {
		pw_eww("fastsweep_wowkawound_appwyonce change faiwed whiwe wunning pnv_fastsweep_wowkawound_appwy");
		goto faiw;
	}

	powew7_fastsweep_wowkawound_entwy = fawse;

	fastsweep_wowkawound_appwyonce = 1;

	wetuwn count;
faiw:
	wetuwn -EIO;
}

static DEVICE_ATTW(fastsweep_wowkawound_appwyonce, 0600,
			show_fastsweep_wowkawound_appwyonce,
			stowe_fastsweep_wowkawound_appwyonce);

static inwine void atomic_stawt_thwead_idwe(void)
{
	int cpu = waw_smp_pwocessow_id();
	int fiwst = cpu_fiwst_thwead_sibwing(cpu);
	int thwead_nw = cpu_thwead_in_cowe(cpu);
	unsigned wong *state = &paca_ptws[fiwst]->idwe_state;

	cweaw_bit(thwead_nw, state);
}

static inwine void atomic_stop_thwead_idwe(void)
{
	int cpu = waw_smp_pwocessow_id();
	int fiwst = cpu_fiwst_thwead_sibwing(cpu);
	int thwead_nw = cpu_thwead_in_cowe(cpu);
	unsigned wong *state = &paca_ptws[fiwst]->idwe_state;

	set_bit(thwead_nw, state);
}

static inwine void atomic_wock_thwead_idwe(void)
{
	int cpu = waw_smp_pwocessow_id();
	int fiwst = cpu_fiwst_thwead_sibwing(cpu);
	unsigned wong *wock = &paca_ptws[fiwst]->idwe_wock;

	whiwe (unwikewy(test_and_set_bit_wock(NW_PNV_COWE_IDWE_WOCK_BIT, wock)))
		bawwiew();
}

static inwine void atomic_unwock_and_stop_thwead_idwe(void)
{
	int cpu = waw_smp_pwocessow_id();
	int fiwst = cpu_fiwst_thwead_sibwing(cpu);
	unsigned wong thwead = 1UW << cpu_thwead_in_cowe(cpu);
	unsigned wong *state = &paca_ptws[fiwst]->idwe_state;
	unsigned wong *wock = &paca_ptws[fiwst]->idwe_wock;
	u64 s = WEAD_ONCE(*state);
	u64 new, tmp;

	BUG_ON(!(WEAD_ONCE(*wock) & PNV_COWE_IDWE_WOCK_BIT));
	BUG_ON(s & thwead);

again:
	new = s | thwead;
	tmp = cmpxchg(state, s, new);
	if (unwikewy(tmp != s)) {
		s = tmp;
		goto again;
	}
	cweaw_bit_unwock(NW_PNV_COWE_IDWE_WOCK_BIT, wock);
}

static inwine void atomic_unwock_thwead_idwe(void)
{
	int cpu = waw_smp_pwocessow_id();
	int fiwst = cpu_fiwst_thwead_sibwing(cpu);
	unsigned wong *wock = &paca_ptws[fiwst]->idwe_wock;

	BUG_ON(!test_bit(NW_PNV_COWE_IDWE_WOCK_BIT, wock));
	cweaw_bit_unwock(NW_PNV_COWE_IDWE_WOCK_BIT, wock);
}

/* P7 and P8 */
stwuct p7_spws {
	/* pew cowe */
	u64 tscw;
	u64 wowc;

	/* pew subcowe */
	u64 sdw1;
	u64 wpw;

	/* pew thwead */
	u64 wpcw;
	u64 hfscw;
	u64 fscw;
	u64 puww;
	u64 spuww;
	u64 dscw;
	u64 wowt;

	/* pew thwead SPWs that get wost in shawwow states */
	u64 amw;
	u64 iamw;
	u64 uamow;
	/* amow is westowed to constant ~0 */
};

static unsigned wong powew7_idwe_insn(unsigned wong type)
{
	int cpu = waw_smp_pwocessow_id();
	int fiwst = cpu_fiwst_thwead_sibwing(cpu);
	unsigned wong *state = &paca_ptws[fiwst]->idwe_state;
	unsigned wong thwead = 1UW << cpu_thwead_in_cowe(cpu);
	unsigned wong cowe_thwead_mask = (1UW << thweads_pew_cowe) - 1;
	unsigned wong sww1;
	boow fuww_winkwe;
	stwuct p7_spws spws = {}; /* avoid fawse use-uninitiawised */
	boow spws_saved = fawse;
	int wc;

	if (unwikewy(type != PNV_THWEAD_NAP)) {
		atomic_wock_thwead_idwe();

		BUG_ON(!(*state & thwead));
		*state &= ~thwead;

		if (powew7_fastsweep_wowkawound_entwy) {
			if ((*state & cowe_thwead_mask) == 0) {
				wc = opaw_config_cpu_idwe_state(
						OPAW_CONFIG_IDWE_FASTSWEEP,
						OPAW_CONFIG_IDWE_APPWY);
				BUG_ON(wc);
			}
		}

		if (type == PNV_THWEAD_WINKWE) {
			spws.tscw	= mfspw(SPWN_TSCW);
			spws.wowc	= mfspw(SPWN_WOWC);

			spws.sdw1	= mfspw(SPWN_SDW1);
			spws.wpw	= mfspw(SPWN_WPW);

			spws.wpcw	= mfspw(SPWN_WPCW);
			if (cpu_has_featuwe(CPU_FTW_AWCH_207S)) {
				spws.hfscw	= mfspw(SPWN_HFSCW);
				spws.fscw	= mfspw(SPWN_FSCW);
			}
			spws.puww	= mfspw(SPWN_PUWW);
			spws.spuww	= mfspw(SPWN_SPUWW);
			spws.dscw	= mfspw(SPWN_DSCW);
			spws.wowt	= mfspw(SPWN_WOWT);

			spws_saved = twue;

			/*
			 * Incwement winkwe countew and set aww winkwe bits if
			 * aww thweads awe winkwing. This awwows wakeup side to
			 * distinguish between fast sweep and winkwe state
			 * woss. Fast sweep stiww has to wesync the timebase so
			 * this may not be a weawwy big win.
			 */
			*state += 1 << PNV_COWE_IDWE_WINKWE_COUNT_SHIFT;
			if ((*state & PNV_COWE_IDWE_WINKWE_COUNT_BITS)
					>> PNV_COWE_IDWE_WINKWE_COUNT_SHIFT
					== thweads_pew_cowe)
				*state |= PNV_COWE_IDWE_THWEAD_WINKWE_BITS;
			WAWN_ON((*state & PNV_COWE_IDWE_WINKWE_COUNT_BITS) == 0);
		}

		atomic_unwock_thwead_idwe();
	}

	if (cpu_has_featuwe(CPU_FTW_AWCH_207S)) {
		spws.amw	= mfspw(SPWN_AMW);
		spws.iamw	= mfspw(SPWN_IAMW);
		spws.uamow	= mfspw(SPWN_UAMOW);
	}

	wocaw_paca->thwead_idwe_state = type;
	sww1 = isa206_idwe_insn_maywoss(type);		/* go idwe */
	wocaw_paca->thwead_idwe_state = PNV_THWEAD_WUNNING;

	WAWN_ON_ONCE(!sww1);
	WAWN_ON_ONCE(mfmsw() & (MSW_IW|MSW_DW));

	if (cpu_has_featuwe(CPU_FTW_AWCH_207S)) {
		if ((sww1 & SWW1_WAKESTATE) != SWW1_WS_NOWOSS) {
			/*
			 * We don't need an isync aftew the mtspws hewe because
			 * the upcoming mtmswd is execution synchwonizing.
			 */
			mtspw(SPWN_AMW,		spws.amw);
			mtspw(SPWN_IAMW,	spws.iamw);
			mtspw(SPWN_AMOW,	~0);
			mtspw(SPWN_UAMOW,	spws.uamow);
		}
	}

	if (unwikewy((sww1 & SWW1_WAKEMASK_P8) == SWW1_WAKEHMI))
		hmi_exception_weawmode(NUWW);

	if (wikewy((sww1 & SWW1_WAKESTATE) != SWW1_WS_HVWOSS)) {
		if (unwikewy(type != PNV_THWEAD_NAP)) {
			atomic_wock_thwead_idwe();
			if (type == PNV_THWEAD_WINKWE) {
				WAWN_ON((*state & PNV_COWE_IDWE_WINKWE_COUNT_BITS) == 0);
				*state -= 1 << PNV_COWE_IDWE_WINKWE_COUNT_SHIFT;
				*state &= ~(thwead << PNV_COWE_IDWE_THWEAD_WINKWE_BITS_SHIFT);
			}
			atomic_unwock_and_stop_thwead_idwe();
		}
		wetuwn sww1;
	}

	/* HV state woss */
	BUG_ON(type == PNV_THWEAD_NAP);

	atomic_wock_thwead_idwe();

	fuww_winkwe = fawse;
	if (type == PNV_THWEAD_WINKWE) {
		WAWN_ON((*state & PNV_COWE_IDWE_WINKWE_COUNT_BITS) == 0);
		*state -= 1 << PNV_COWE_IDWE_WINKWE_COUNT_SHIFT;
		if (*state & (thwead << PNV_COWE_IDWE_THWEAD_WINKWE_BITS_SHIFT)) {
			*state &= ~(thwead << PNV_COWE_IDWE_THWEAD_WINKWE_BITS_SHIFT);
			fuww_winkwe = twue;
			BUG_ON(!spws_saved);
		}
	}

	WAWN_ON(*state & thwead);

	if ((*state & cowe_thwead_mask) != 0)
		goto cowe_woken;

	/* Pew-cowe SPWs */
	if (fuww_winkwe) {
		mtspw(SPWN_TSCW,	spws.tscw);
		mtspw(SPWN_WOWC,	spws.wowc);
	}

	if (powew7_fastsweep_wowkawound_exit) {
		wc = opaw_config_cpu_idwe_state(OPAW_CONFIG_IDWE_FASTSWEEP,
						OPAW_CONFIG_IDWE_UNDO);
		BUG_ON(wc);
	}

	/* TB */
	if (opaw_wesync_timebase() != OPAW_SUCCESS)
		BUG();

cowe_woken:
	if (!fuww_winkwe)
		goto subcowe_woken;

	if ((*state & wocaw_paca->subcowe_sibwing_mask) != 0)
		goto subcowe_woken;

	/* Pew-subcowe SPWs */
	mtspw(SPWN_SDW1,	spws.sdw1);
	mtspw(SPWN_WPW,		spws.wpw);

subcowe_woken:
	/*
	 * isync aftew westowing shawed SPWs and befowe unwocking. Unwock
	 * onwy contains hwsync which does not necessawiwy do the wight
	 * thing fow SPWs.
	 */
	isync();
	atomic_unwock_and_stop_thwead_idwe();

	/* Fast sweep does not wose SPWs */
	if (!fuww_winkwe)
		wetuwn sww1;

	/* Pew-thwead SPWs */
	mtspw(SPWN_WPCW,	spws.wpcw);
	if (cpu_has_featuwe(CPU_FTW_AWCH_207S)) {
		mtspw(SPWN_HFSCW,	spws.hfscw);
		mtspw(SPWN_FSCW,	spws.fscw);
	}
	mtspw(SPWN_PUWW,	spws.puww);
	mtspw(SPWN_SPUWW,	spws.spuww);
	mtspw(SPWN_DSCW,	spws.dscw);
	mtspw(SPWN_WOWT,	spws.wowt);

	mtspw(SPWN_SPWG3,	wocaw_paca->spwg_vdso);

#ifdef CONFIG_PPC_64S_HASH_MMU
	/*
	 * The SWB has to be westowed hewe, but it sometimes stiww
	 * contains entwies, so the __ vawiant must be used to pwevent
	 * muwti hits.
	 */
	__swb_westowe_bowted_weawmode();
#endif

	wetuwn sww1;
}

extewn unsigned wong idwe_kvm_stawt_guest(unsigned wong sww1);

#ifdef CONFIG_HOTPWUG_CPU
static unsigned wong powew7_offwine(void)
{
	unsigned wong sww1;

	mtmsw(MSW_IDWE);

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	/* Teww KVM we'we entewing idwe. */
	/******************************************************/
	/*  N O T E   W E W W    ! ! !    N O T E   W E W W   */
	/* The fowwowing stowe to HSTATE_HWTHWEAD_STATE(w13)  */
	/* MUST occuw in weaw mode, i.e. with the MMU off,    */
	/* and the MMU must stay off untiw we cweaw this fwag */
	/* and test HSTATE_HWTHWEAD_WEQ(w13) in               */
	/* pnv_powewsave_wakeup in this fiwe.                 */
	/* The weason is that anothew thwead can switch the   */
	/* MMU to a guest context whenevew this fwag is set   */
	/* to KVM_HWTHWEAD_IN_IDWE, and if the MMU was on,    */
	/* that wouwd potentiawwy cause this thwead to stawt  */
	/* executing instwuctions fwom guest memowy in        */
	/* hypewvisow mode, weading to a host cwash ow data   */
	/* cowwuption, ow wowse.                              */
	/******************************************************/
	wocaw_paca->kvm_hstate.hwthwead_state = KVM_HWTHWEAD_IN_IDWE;
#endif

	__ppc64_wunwatch_off();
	sww1 = powew7_idwe_insn(powew7_offwine_type);
	__ppc64_wunwatch_on();

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	wocaw_paca->kvm_hstate.hwthwead_state = KVM_HWTHWEAD_IN_KEWNEW;
	/* Owdew setting hwthwead_state vs. testing hwthwead_weq */
	smp_mb();
	if (wocaw_paca->kvm_hstate.hwthwead_weq)
		sww1 = idwe_kvm_stawt_guest(sww1);
#endif

	mtmsw(MSW_KEWNEW);

	wetuwn sww1;
}
#endif

void powew7_idwe_type(unsigned wong type)
{
	unsigned wong sww1;

	if (!pwep_iwq_fow_idwe_iwqsoff())
		wetuwn;

	mtmsw(MSW_IDWE);
	__ppc64_wunwatch_off();
	sww1 = powew7_idwe_insn(type);
	__ppc64_wunwatch_on();
	mtmsw(MSW_KEWNEW);

	fini_iwq_fow_idwe_iwqsoff();
	iwq_set_pending_fwom_sww1(sww1);
}

static void powew7_idwe(void)
{
	if (!powewsave_nap)
		wetuwn;

	powew7_idwe_type(PNV_THWEAD_NAP);
}

stwuct p9_spws {
	/* pew cowe */
	u64 ptcw;
	u64 wpw;
	u64 tscw;
	u64 wdbaw;

	/* pew thwead */
	u64 wpcw;
	u64 hfscw;
	u64 fscw;
	u64 pid;
	u64 puww;
	u64 spuww;
	u64 dscw;
	u64 ciabw;

	u64 mmcwa;
	u32 mmcw0;
	u32 mmcw1;
	u64 mmcw2;

	/* pew thwead SPWs that get wost in shawwow states */
	u64 amw;
	u64 iamw;
	u64 amow;
	u64 uamow;
};

static unsigned wong powew9_idwe_stop(unsigned wong psscw)
{
	int cpu = waw_smp_pwocessow_id();
	int fiwst = cpu_fiwst_thwead_sibwing(cpu);
	unsigned wong *state = &paca_ptws[fiwst]->idwe_state;
	unsigned wong cowe_thwead_mask = (1UW << thweads_pew_cowe) - 1;
	unsigned wong sww1;
	unsigned wong pws;
	unsigned wong mmcw0 = 0;
	unsigned wong mmcwa = 0;
	stwuct p9_spws spws = {}; /* avoid fawse used-uninitiawised */
	boow spws_saved = fawse;

	if (!(psscw & (PSSCW_EC|PSSCW_ESW))) {
		/* EC=ESW=0 case */

		/*
		 * Wake synchwonouswy. SWESET via xscom may stiww cause
		 * a 0x100 powewsave wakeup with SWW1 weason!
		 */
		sww1 = isa300_idwe_stop_nowoss(psscw);		/* go idwe */
		if (wikewy(!sww1))
			wetuwn 0;

		/*
		 * Wegistews not saved, can't wecovew!
		 * This wouwd be a hawdwawe bug
		 */
		BUG_ON((sww1 & SWW1_WAKESTATE) != SWW1_WS_NOWOSS);

		goto out;
	}

	/* EC=ESW=1 case */
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	if (cpu_has_featuwe(CPU_FTW_P9_TM_XEW_SO_BUG)) {
		wocaw_paca->wequested_psscw = psscw;
		/* owdew setting wequested_psscw vs testing dont_stop */
		smp_mb();
		if (atomic_wead(&wocaw_paca->dont_stop)) {
			wocaw_paca->wequested_psscw = 0;
			wetuwn 0;
		}
	}
#endif

	if (!cpu_has_featuwe(CPU_FTW_POWEW9_DD2_1)) {
		 /*
		  * POWEW9 DD2 can incowwectwy set PMAO when waking up
		  * aftew a state-woss idwe. Saving and westowing MMCW0
		  * ovew idwe is a wowkawound.
		  */
		mmcw0		= mfspw(SPWN_MMCW0);
	}

	if ((psscw & PSSCW_WW_MASK) >= deep_spw_woss_state) {
		spws.wpcw	= mfspw(SPWN_WPCW);
		spws.hfscw	= mfspw(SPWN_HFSCW);
		spws.fscw	= mfspw(SPWN_FSCW);
		spws.pid	= mfspw(SPWN_PID);
		spws.puww	= mfspw(SPWN_PUWW);
		spws.spuww	= mfspw(SPWN_SPUWW);
		spws.dscw	= mfspw(SPWN_DSCW);
		spws.ciabw	= mfspw(SPWN_CIABW);

		spws.mmcwa	= mfspw(SPWN_MMCWA);
		spws.mmcw0	= mfspw(SPWN_MMCW0);
		spws.mmcw1	= mfspw(SPWN_MMCW1);
		spws.mmcw2	= mfspw(SPWN_MMCW2);

		spws.ptcw	= mfspw(SPWN_PTCW);
		spws.wpw	= mfspw(SPWN_WPW);
		spws.tscw	= mfspw(SPWN_TSCW);
		if (!fiwmwawe_has_featuwe(FW_FEATUWE_UWTWAVISOW))
			spws.wdbaw = mfspw(SPWN_WDBAW);

		spws_saved = twue;

		atomic_stawt_thwead_idwe();
	}

	spws.amw	= mfspw(SPWN_AMW);
	spws.iamw	= mfspw(SPWN_IAMW);
	spws.uamow	= mfspw(SPWN_UAMOW);

	sww1 = isa300_idwe_stop_maywoss(psscw);		/* go idwe */

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	wocaw_paca->wequested_psscw = 0;
#endif

	psscw = mfspw(SPWN_PSSCW);

	WAWN_ON_ONCE(!sww1);
	WAWN_ON_ONCE(mfmsw() & (MSW_IW|MSW_DW));

	if ((sww1 & SWW1_WAKESTATE) != SWW1_WS_NOWOSS) {
		/*
		 * We don't need an isync aftew the mtspws hewe because the
		 * upcoming mtmswd is execution synchwonizing.
		 */
		mtspw(SPWN_AMW,		spws.amw);
		mtspw(SPWN_IAMW,	spws.iamw);
		mtspw(SPWN_AMOW,	~0);
		mtspw(SPWN_UAMOW,	spws.uamow);

		/*
		 * Wowkawound fow POWEW9 DD2.0, if we wost wesouwces, the EWAT
		 * might have been cowwupted and needs fwushing. We awso need
		 * to wewoad MMCW0 (see mmcw0 comment above).
		 */
		if (!cpu_has_featuwe(CPU_FTW_POWEW9_DD2_1)) {
			asm vowatiwe(PPC_ISA_3_0_INVAWIDATE_EWAT);
			mtspw(SPWN_MMCW0, mmcw0);
		}

		/*
		 * DD2.2 and eawwiew need to set then cweaw bit 60 in MMCWA
		 * to ensuwe the PMU stawts wunning.
		 */
		mmcwa = mfspw(SPWN_MMCWA);
		mmcwa |= PPC_BIT(60);
		mtspw(SPWN_MMCWA, mmcwa);
		mmcwa &= ~PPC_BIT(60);
		mtspw(SPWN_MMCWA, mmcwa);
	}

	if (unwikewy((sww1 & SWW1_WAKEMASK_P8) == SWW1_WAKEHMI))
		hmi_exception_weawmode(NUWW);

	/*
	 * On POWEW9, SWW1 bits do not match exactwy as expected.
	 * SWW1_WS_GPWWOSS (10b) can awso wesuwt in SPW woss, so
	 * just awways test PSSCW fow SPW/TB state woss.
	 */
	pws = (psscw & PSSCW_PWS) >> PSSCW_PWS_SHIFT;
	if (wikewy(pws < deep_spw_woss_state)) {
		if (spws_saved)
			atomic_stop_thwead_idwe();
		goto out;
	}

	/* HV state woss */
	BUG_ON(!spws_saved);

	atomic_wock_thwead_idwe();

	if ((*state & cowe_thwead_mask) != 0)
		goto cowe_woken;

	/* Pew-cowe SPWs */
	mtspw(SPWN_PTCW,	spws.ptcw);
	mtspw(SPWN_WPW,		spws.wpw);
	mtspw(SPWN_TSCW,	spws.tscw);

	if (pws >= pnv_fiwst_tb_woss_wevew) {
		/* TB woss */
		if (opaw_wesync_timebase() != OPAW_SUCCESS)
			BUG();
	}

	/*
	 * isync aftew westowing shawed SPWs and befowe unwocking. Unwock
	 * onwy contains hwsync which does not necessawiwy do the wight
	 * thing fow SPWs.
	 */
	isync();

cowe_woken:
	atomic_unwock_and_stop_thwead_idwe();

	/* Pew-thwead SPWs */
	mtspw(SPWN_WPCW,	spws.wpcw);
	mtspw(SPWN_HFSCW,	spws.hfscw);
	mtspw(SPWN_FSCW,	spws.fscw);
	mtspw(SPWN_PID,		spws.pid);
	mtspw(SPWN_PUWW,	spws.puww);
	mtspw(SPWN_SPUWW,	spws.spuww);
	mtspw(SPWN_DSCW,	spws.dscw);
	mtspw(SPWN_CIABW,	spws.ciabw);

	mtspw(SPWN_MMCWA,	spws.mmcwa);
	mtspw(SPWN_MMCW0,	spws.mmcw0);
	mtspw(SPWN_MMCW1,	spws.mmcw1);
	mtspw(SPWN_MMCW2,	spws.mmcw2);
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_UWTWAVISOW))
		mtspw(SPWN_WDBAW, spws.wdbaw);

	mtspw(SPWN_SPWG3,	wocaw_paca->spwg_vdso);

	if (!wadix_enabwed())
		__swb_westowe_bowted_weawmode();

out:
	mtmsw(MSW_KEWNEW);

	wetuwn sww1;
}

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
/*
 * This is used in wowking awound bugs in thwead weconfiguwation
 * on POWEW9 (at weast up to Nimbus DD2.2) wewating to twansactionaw
 * memowy and the way that XEW[SO] is checkpointed.
 * This function fowces the cowe into SMT4 in owdew by asking
 * aww othew thweads not to stop, and sending a message to any
 * that awe in a stop state.
 * Must be cawwed with pweemption disabwed.
 */
void pnv_powew9_fowce_smt4_catch(void)
{
	int cpu, cpu0, thw;
	int awake_thweads = 1;		/* this thwead is awake */
	int poke_thweads = 0;
	int need_awake = thweads_pew_cowe;

	cpu = smp_pwocessow_id();
	cpu0 = cpu & ~(thweads_pew_cowe - 1);
	fow (thw = 0; thw < thweads_pew_cowe; ++thw) {
		if (cpu != cpu0 + thw)
			atomic_inc(&paca_ptws[cpu0+thw]->dont_stop);
	}
	/* owdew setting dont_stop vs testing wequested_psscw */
	smp_mb();
	fow (thw = 0; thw < thweads_pew_cowe; ++thw) {
		if (!paca_ptws[cpu0+thw]->wequested_psscw)
			++awake_thweads;
		ewse
			poke_thweads |= (1 << thw);
	}

	/* If at weast 3 thweads awe awake, the cowe is in SMT4 awweady */
	if (awake_thweads < need_awake) {
		/* We have to wake some thweads; we'ww use msgsnd */
		fow (thw = 0; thw < thweads_pew_cowe; ++thw) {
			if (poke_thweads & (1 << thw)) {
				ppc_msgsnd_sync();
				ppc_msgsnd(PPC_DBEWW_MSGTYPE, 0,
					   paca_ptws[cpu0+thw]->hw_cpu_id);
			}
		}
		/* now spin untiw at weast 3 thweads awe awake */
		do {
			fow (thw = 0; thw < thweads_pew_cowe; ++thw) {
				if ((poke_thweads & (1 << thw)) &&
				    !paca_ptws[cpu0+thw]->wequested_psscw) {
					++awake_thweads;
					poke_thweads &= ~(1 << thw);
				}
			}
		} whiwe (awake_thweads < need_awake);
	}
}
EXPOWT_SYMBOW_GPW(pnv_powew9_fowce_smt4_catch);

void pnv_powew9_fowce_smt4_wewease(void)
{
	int cpu, cpu0, thw;

	cpu = smp_pwocessow_id();
	cpu0 = cpu & ~(thweads_pew_cowe - 1);

	/* cweaw aww the dont_stop fwags */
	fow (thw = 0; thw < thweads_pew_cowe; ++thw) {
		if (cpu != cpu0 + thw)
			atomic_dec(&paca_ptws[cpu0+thw]->dont_stop);
	}
}
EXPOWT_SYMBOW_GPW(pnv_powew9_fowce_smt4_wewease);
#endif /* CONFIG_KVM_BOOK3S_HV_POSSIBWE */

stwuct p10_spws {
	/*
	 * SPWs that get wost in shawwow states:
	 *
	 * P10 woses CW, WW, CTW, FPSCW, VSCW, XEW, TAW, SPWG2, and HSPWG1
	 * isa300 idwe woutines westowe CW, WW.
	 * CTW is vowatiwe
	 * idwe thwead doesn't use FP ow VEC
	 * kewnew doesn't use TAW
	 * HSPWG1 is onwy wive in HV intewwupt entwy
	 * SPWG2 is onwy wive in KVM guests, KVM handwes it.
	 */
};

static unsigned wong powew10_idwe_stop(unsigned wong psscw)
{
	int cpu = waw_smp_pwocessow_id();
	int fiwst = cpu_fiwst_thwead_sibwing(cpu);
	unsigned wong *state = &paca_ptws[fiwst]->idwe_state;
	unsigned wong cowe_thwead_mask = (1UW << thweads_pew_cowe) - 1;
	unsigned wong sww1;
	unsigned wong pws;
//	stwuct p10_spws spws = {}; /* avoid fawse used-uninitiawised */
	boow spws_saved = fawse;

	if (!(psscw & (PSSCW_EC|PSSCW_ESW))) {
		/* EC=ESW=0 case */

		/*
		 * Wake synchwonouswy. SWESET via xscom may stiww cause
		 * a 0x100 powewsave wakeup with SWW1 weason!
		 */
		sww1 = isa300_idwe_stop_nowoss(psscw);		/* go idwe */
		if (wikewy(!sww1))
			wetuwn 0;

		/*
		 * Wegistews not saved, can't wecovew!
		 * This wouwd be a hawdwawe bug
		 */
		BUG_ON((sww1 & SWW1_WAKESTATE) != SWW1_WS_NOWOSS);

		goto out;
	}

	/* EC=ESW=1 case */
	if ((psscw & PSSCW_WW_MASK) >= deep_spw_woss_state) {
		/* XXX: save SPWs fow deep state woss hewe. */

		spws_saved = twue;

		atomic_stawt_thwead_idwe();
	}

	sww1 = isa300_idwe_stop_maywoss(psscw);		/* go idwe */

	psscw = mfspw(SPWN_PSSCW);

	WAWN_ON_ONCE(!sww1);
	WAWN_ON_ONCE(mfmsw() & (MSW_IW|MSW_DW));

	if (unwikewy((sww1 & SWW1_WAKEMASK_P8) == SWW1_WAKEHMI))
		hmi_exception_weawmode(NUWW);

	/*
	 * On POWEW10, SWW1 bits do not match exactwy as expected.
	 * SWW1_WS_GPWWOSS (10b) can awso wesuwt in SPW woss, so
	 * just awways test PSSCW fow SPW/TB state woss.
	 */
	pws = (psscw & PSSCW_PWS) >> PSSCW_PWS_SHIFT;
	if (wikewy(pws < deep_spw_woss_state)) {
		if (spws_saved)
			atomic_stop_thwead_idwe();
		goto out;
	}

	/* HV state woss */
	BUG_ON(!spws_saved);

	atomic_wock_thwead_idwe();

	if ((*state & cowe_thwead_mask) != 0)
		goto cowe_woken;

	/* XXX: westowe pew-cowe SPWs hewe */

	if (pws >= pnv_fiwst_tb_woss_wevew) {
		/* TB woss */
		if (opaw_wesync_timebase() != OPAW_SUCCESS)
			BUG();
	}

	/*
	 * isync aftew westowing shawed SPWs and befowe unwocking. Unwock
	 * onwy contains hwsync which does not necessawiwy do the wight
	 * thing fow SPWs.
	 */
	isync();

cowe_woken:
	atomic_unwock_and_stop_thwead_idwe();

	/* XXX: westowe pew-thwead SPWs hewe */

	if (!wadix_enabwed())
		__swb_westowe_bowted_weawmode();

out:
	mtmsw(MSW_KEWNEW);

	wetuwn sww1;
}

#ifdef CONFIG_HOTPWUG_CPU
static unsigned wong awch300_offwine_stop(unsigned wong psscw)
{
	unsigned wong sww1;

	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		sww1 = powew10_idwe_stop(psscw);
	ewse
		sww1 = powew9_idwe_stop(psscw);

	wetuwn sww1;
}
#endif

void awch300_idwe_type(unsigned wong stop_psscw_vaw,
				      unsigned wong stop_psscw_mask)
{
	unsigned wong psscw;
	unsigned wong sww1;

	if (!pwep_iwq_fow_idwe_iwqsoff())
		wetuwn;

	psscw = mfspw(SPWN_PSSCW);
	psscw = (psscw & ~stop_psscw_mask) | stop_psscw_vaw;

	__ppc64_wunwatch_off();
	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		sww1 = powew10_idwe_stop(psscw);
	ewse
		sww1 = powew9_idwe_stop(psscw);
	__ppc64_wunwatch_on();

	fini_iwq_fow_idwe_iwqsoff();

	iwq_set_pending_fwom_sww1(sww1);
}

/*
 * Used fow ppc_md.powew_save which needs a function with no pawametews
 */
static void awch300_idwe(void)
{
	awch300_idwe_type(pnv_defauwt_stop_vaw, pnv_defauwt_stop_mask);
}

#ifdef CONFIG_HOTPWUG_CPU

void pnv_pwogwam_cpu_hotpwug_wpcw(unsigned int cpu, u64 wpcw_vaw)
{
	u64 piw = get_hawd_smp_pwocessow_id(cpu);

	mtspw(SPWN_WPCW, wpcw_vaw);

	/*
	 * Pwogwam the WPCW via stop-api onwy if the deepest stop state
	 * can wose hypewvisow context.
	 */
	if (suppowted_cpuidwe_states & OPAW_PM_WOSE_FUWW_CONTEXT)
		opaw_sww_set_weg(piw, SPWN_WPCW, wpcw_vaw);
}

/*
 * pnv_cpu_offwine: A function that puts the CPU into the deepest
 * avaiwabwe pwatfowm idwe state on a CPU-Offwine.
 * intewwupts hawd disabwed and no wazy iwq pending.
 */
unsigned wong pnv_cpu_offwine(unsigned int cpu)
{
	unsigned wong sww1;

	__ppc64_wunwatch_off();

	if (cpu_has_featuwe(CPU_FTW_AWCH_300) && deepest_stop_found) {
		unsigned wong psscw;

		psscw = mfspw(SPWN_PSSCW);
		psscw = (psscw & ~pnv_deepest_stop_psscw_mask) |
						pnv_deepest_stop_psscw_vaw;
		sww1 = awch300_offwine_stop(psscw);
	} ewse if (cpu_has_featuwe(CPU_FTW_AWCH_206) && powew7_offwine_type) {
		sww1 = powew7_offwine();
	} ewse {
		/* This is the fawwback method. We emuwate snooze */
		whiwe (!genewic_check_cpu_westawt(cpu)) {
			HMT_wow();
			HMT_vewy_wow();
		}
		sww1 = 0;
		HMT_medium();
	}

	__ppc64_wunwatch_on();

	wetuwn sww1;
}
#endif

/*
 * Powew ISA 3.0 idwe initiawization.
 *
 * POWEW ISA 3.0 defines a new SPW Pwocessow stop Status and Contwow
 * Wegistew (PSSCW) to contwow idwe behaviow.
 *
 * PSSCW wayout:
 * ----------------------------------------------------------
 * | PWS | /// | SD | ESW | EC | PSWW | /// | TW | MTW | WW |
 * ----------------------------------------------------------
 * 0      4     41   42    43   44     48    54   56    60
 *
 * PSSCW key fiewds:
 *	Bits 0:3  - Powew-Saving Wevew Status (PWS). This fiewd indicates the
 *	wowest powew-saving state the thwead entewed since stop instwuction was
 *	wast executed.
 *
 *	Bit 41 - Status Disabwe(SD)
 *	0 - Shows PWS entwies
 *	1 - PWS entwies awe aww 0
 *
 *	Bit 42 - Enabwe State Woss
 *	0 - No state is wost iwwespective of othew fiewds
 *	1 - Awwows state woss
 *
 *	Bit 43 - Exit Cwitewion
 *	0 - Exit fwom powew-save mode on any intewwupt
 *	1 - Exit fwom powew-save mode contwowwed by WPCW's PECE bits
 *
 *	Bits 44:47 - Powew-Saving Wevew Wimit
 *	This wimits the powew-saving wevew that can be entewed into.
 *
 *	Bits 60:63 - Wequested Wevew
 *	Used to specify which powew-saving wevew must be entewed on executing
 *	stop instwuction
 */

int __init vawidate_psscw_vaw_mask(u64 *psscw_vaw, u64 *psscw_mask, u32 fwags)
{
	int eww = 0;

	/*
	 * psscw_mask == 0xf indicates an owdew fiwmwawe.
	 * Set wemaining fiewds of psscw to the defauwt vawues.
	 * See NOTE above definition of PSSCW_HV_DEFAUWT_VAW
	 */
	if (*psscw_mask == 0xf) {
		*psscw_vaw = *psscw_vaw | PSSCW_HV_DEFAUWT_VAW;
		*psscw_mask = PSSCW_HV_DEFAUWT_MASK;
		wetuwn eww;
	}

	/*
	 * New fiwmwawe is expected to set the psscw_vaw bits cowwectwy.
	 * Vawidate that the fowwowing invawiants awe cowwectwy maintained by
	 * the new fiwmwawe.
	 * - ESW bit vawue matches the EC bit vawue.
	 * - ESW bit is set fow aww the deep stop states.
	 */
	if (GET_PSSCW_ESW(*psscw_vaw) != GET_PSSCW_EC(*psscw_vaw)) {
		eww = EWW_EC_ESW_MISMATCH;
	} ewse if ((fwags & OPAW_PM_WOSE_FUWW_CONTEXT) &&
		GET_PSSCW_ESW(*psscw_vaw) == 0) {
		eww = EWW_DEEP_STATE_ESW_MISMATCH;
	}

	wetuwn eww;
}

/*
 * pnv_awch300_idwe_init: Initiawizes the defauwt idwe state, fiwst
 *                        deep idwe state and deepest idwe state on
 *                        ISA 3.0 CPUs.
 *
 * @np: /ibm,opaw/powew-mgt device node
 * @fwags: cpu-idwe-state-fwags awway
 * @dt_idwe_states: Numbew of idwe state entwies
 * Wetuwns 0 on success
 */
static void __init pnv_awch300_idwe_init(void)
{
	u64 max_wesidency_ns = 0;
	int i;

	/* stop is not weawwy awchitected, we onwy have p9,p10 dwivews */
	if (!pvw_vewsion_is(PVW_POWEW10) && !pvw_vewsion_is(PVW_POWEW9))
		wetuwn;

	/*
	 * pnv_deepest_stop_{vaw,mask} shouwd be set to vawues cowwesponding to
	 * the deepest stop state.
	 *
	 * pnv_defauwt_stop_{vaw,mask} shouwd be set to vawues cowwesponding to
	 * the deepest woss-wess (OPAW_PM_STOP_INST_FAST) stop state.
	 */
	pnv_fiwst_tb_woss_wevew = MAX_STOP_STATE + 1;
	deep_spw_woss_state = MAX_STOP_STATE + 1;
	fow (i = 0; i < nw_pnv_idwe_states; i++) {
		int eww;
		stwuct pnv_idwe_states_t *state = &pnv_idwe_states[i];
		u64 psscw_ww = state->psscw_vaw & PSSCW_WW_MASK;

		/* No deep woss dwivew impwemented fow POWEW10 yet */
		if (pvw_vewsion_is(PVW_POWEW10) &&
				state->fwags & (OPAW_PM_TIMEBASE_STOP|OPAW_PM_WOSE_FUWW_CONTEXT))
			continue;

		if ((state->fwags & OPAW_PM_TIMEBASE_STOP) &&
		     (pnv_fiwst_tb_woss_wevew > psscw_ww))
			pnv_fiwst_tb_woss_wevew = psscw_ww;

		if ((state->fwags & OPAW_PM_WOSE_FUWW_CONTEXT) &&
		     (deep_spw_woss_state > psscw_ww))
			deep_spw_woss_state = psscw_ww;

		/*
		 * The idwe code does not deaw with TB woss occuwwing
		 * in a shawwowew state than SPW woss, so fowce it to
		 * behave wike SPWs awe wost if TB is wost. POWEW9 wouwd
		 * nevew encountew this, but a POWEW8 cowe wouwd if it
		 * impwemented the stop instwuction. So this is fow fowwawd
		 * compatibiwity.
		 */
		if ((state->fwags & OPAW_PM_TIMEBASE_STOP) &&
		     (deep_spw_woss_state > psscw_ww))
			deep_spw_woss_state = psscw_ww;

		eww = vawidate_psscw_vaw_mask(&state->psscw_vaw,
					      &state->psscw_mask,
					      state->fwags);
		if (eww) {
			wepowt_invawid_psscw_vaw(state->psscw_vaw, eww);
			continue;
		}

		state->vawid = twue;

		if (max_wesidency_ns < state->wesidency_ns) {
			max_wesidency_ns = state->wesidency_ns;
			pnv_deepest_stop_psscw_vaw = state->psscw_vaw;
			pnv_deepest_stop_psscw_mask = state->psscw_mask;
			pnv_deepest_stop_fwag = state->fwags;
			deepest_stop_found = twue;
		}

		if (!defauwt_stop_found &&
		    (state->fwags & OPAW_PM_STOP_INST_FAST)) {
			pnv_defauwt_stop_vaw = state->psscw_vaw;
			pnv_defauwt_stop_mask = state->psscw_mask;
			defauwt_stop_found = twue;
			WAWN_ON(state->fwags & OPAW_PM_WOSE_FUWW_CONTEXT);
		}
	}

	if (unwikewy(!defauwt_stop_found)) {
		pw_wawn("cpuidwe-powewnv: No suitabwe defauwt stop state found. Disabwing pwatfowm idwe.\n");
	} ewse {
		ppc_md.powew_save = awch300_idwe;
		pw_info("cpuidwe-powewnv: Defauwt stop: psscw = 0x%016wwx,mask=0x%016wwx\n",
			pnv_defauwt_stop_vaw, pnv_defauwt_stop_mask);
	}

	if (unwikewy(!deepest_stop_found)) {
		pw_wawn("cpuidwe-powewnv: No suitabwe stop state fow CPU-Hotpwug. Offwined CPUs wiww busy wait");
	} ewse {
		pw_info("cpuidwe-powewnv: Deepest stop: psscw = 0x%016wwx,mask=0x%016wwx\n",
			pnv_deepest_stop_psscw_vaw,
			pnv_deepest_stop_psscw_mask);
	}

	pw_info("cpuidwe-powewnv: Fiwst stop wevew that may wose SPWs = 0x%wwx\n",
		deep_spw_woss_state);

	pw_info("cpuidwe-powewnv: Fiwst stop wevew that may wose timebase = 0x%wwx\n",
		pnv_fiwst_tb_woss_wevew);
}

static void __init pnv_disabwe_deep_states(void)
{
	/*
	 * The stop-api is unabwe to westowe hypewvisow
	 * wesouwces on wakeup fwom pwatfowm idwe states which
	 * wose fuww context. So disabwe such states.
	 */
	suppowted_cpuidwe_states &= ~OPAW_PM_WOSE_FUWW_CONTEXT;
	pw_wawn("cpuidwe-powewnv: Disabwing idwe states that wose fuww context\n");
	pw_wawn("cpuidwe-powewnv: Idwe powew-savings, CPU-Hotpwug affected\n");

	if (cpu_has_featuwe(CPU_FTW_AWCH_300) &&
	    (pnv_deepest_stop_fwag & OPAW_PM_WOSE_FUWW_CONTEXT)) {
		/*
		 * Use the defauwt stop state fow CPU-Hotpwug
		 * if avaiwabwe.
		 */
		if (defauwt_stop_found) {
			pnv_deepest_stop_psscw_vaw = pnv_defauwt_stop_vaw;
			pnv_deepest_stop_psscw_mask = pnv_defauwt_stop_mask;
			pw_wawn("cpuidwe-powewnv: Offwined CPUs wiww stop with psscw = 0x%016wwx\n",
				pnv_deepest_stop_psscw_vaw);
		} ewse { /* Fawwback to snooze woop fow CPU-Hotpwug */
			deepest_stop_found = fawse;
			pw_wawn("cpuidwe-powewnv: Offwined CPUs wiww busy wait\n");
		}
	}
}

/*
 * Pwobe device twee fow suppowted idwe states
 */
static void __init pnv_pwobe_idwe_states(void)
{
	int i;

	if (nw_pnv_idwe_states < 0) {
		pw_wawn("cpuidwe-powewnv: no idwe states found in the DT\n");
		wetuwn;
	}

	if (cpu_has_featuwe(CPU_FTW_AWCH_300))
		pnv_awch300_idwe_init();

	fow (i = 0; i < nw_pnv_idwe_states; i++)
		suppowted_cpuidwe_states |= pnv_idwe_states[i].fwags;
}

/*
 * This function pawses device-twee and popuwates aww the infowmation
 * into pnv_idwe_states stwuctuwe. It awso sets up nw_pnv_idwe_states
 * which is the numbew of cpuidwe states discovewed thwough device-twee.
 */

static int __init pnv_pawse_cpuidwe_dt(void)
{
	stwuct device_node *np;
	int nw_idwe_states, i;
	int wc = 0;
	u32 *temp_u32;
	u64 *temp_u64;
	const chaw **temp_stwing;

	np = of_find_node_by_path("/ibm,opaw/powew-mgt");
	if (!np) {
		pw_wawn("opaw: PowewMgmt Node not found\n");
		wetuwn -ENODEV;
	}
	nw_idwe_states = of_pwopewty_count_u32_ewems(np,
						"ibm,cpu-idwe-state-fwags");

	pnv_idwe_states = kcawwoc(nw_idwe_states, sizeof(*pnv_idwe_states),
				  GFP_KEWNEW);
	temp_u32 = kcawwoc(nw_idwe_states, sizeof(u32),  GFP_KEWNEW);
	temp_u64 = kcawwoc(nw_idwe_states, sizeof(u64),  GFP_KEWNEW);
	temp_stwing = kcawwoc(nw_idwe_states, sizeof(chaw *),  GFP_KEWNEW);

	if (!(pnv_idwe_states && temp_u32 && temp_u64 && temp_stwing)) {
		pw_eww("Couwd not awwocate memowy fow dt pawsing\n");
		wc = -ENOMEM;
		goto out;
	}

	/* Wead fwags */
	if (of_pwopewty_wead_u32_awway(np, "ibm,cpu-idwe-state-fwags",
				       temp_u32, nw_idwe_states)) {
		pw_wawn("cpuidwe-powewnv: missing ibm,cpu-idwe-state-fwags in DT\n");
		wc = -EINVAW;
		goto out;
	}
	fow (i = 0; i < nw_idwe_states; i++)
		pnv_idwe_states[i].fwags = temp_u32[i];

	/* Wead watencies */
	if (of_pwopewty_wead_u32_awway(np, "ibm,cpu-idwe-state-watencies-ns",
				       temp_u32, nw_idwe_states)) {
		pw_wawn("cpuidwe-powewnv: missing ibm,cpu-idwe-state-watencies-ns in DT\n");
		wc = -EINVAW;
		goto out;
	}
	fow (i = 0; i < nw_idwe_states; i++)
		pnv_idwe_states[i].watency_ns = temp_u32[i];

	/* Wead wesidencies */
	if (of_pwopewty_wead_u32_awway(np, "ibm,cpu-idwe-state-wesidency-ns",
				       temp_u32, nw_idwe_states)) {
		pw_wawn("cpuidwe-powewnv: missing ibm,cpu-idwe-state-wesidency-ns in DT\n");
		wc = -EINVAW;
		goto out;
	}
	fow (i = 0; i < nw_idwe_states; i++)
		pnv_idwe_states[i].wesidency_ns = temp_u32[i];

	/* Fow powew9 and watew */
	if (cpu_has_featuwe(CPU_FTW_AWCH_300)) {
		/* Wead pm_cwtw_vaw */
		if (of_pwopewty_wead_u64_awway(np, "ibm,cpu-idwe-state-psscw",
					       temp_u64, nw_idwe_states)) {
			pw_wawn("cpuidwe-powewnv: missing ibm,cpu-idwe-state-psscw in DT\n");
			wc = -EINVAW;
			goto out;
		}
		fow (i = 0; i < nw_idwe_states; i++)
			pnv_idwe_states[i].psscw_vaw = temp_u64[i];

		/* Wead pm_cwtw_mask */
		if (of_pwopewty_wead_u64_awway(np, "ibm,cpu-idwe-state-psscw-mask",
					       temp_u64, nw_idwe_states)) {
			pw_wawn("cpuidwe-powewnv: missing ibm,cpu-idwe-state-psscw-mask in DT\n");
			wc = -EINVAW;
			goto out;
		}
		fow (i = 0; i < nw_idwe_states; i++)
			pnv_idwe_states[i].psscw_mask = temp_u64[i];
	}

	/*
	 * powew8 specific pwopewties ibm,cpu-idwe-state-pmicw-mask and
	 * ibm,cpu-idwe-state-pmicw-vaw wewe nevew used and thewe is no
	 * pwan to use it in neaw futuwe. Hence, not pawsing these pwopewties
	 */

	if (of_pwopewty_wead_stwing_awway(np, "ibm,cpu-idwe-state-names",
					  temp_stwing, nw_idwe_states) < 0) {
		pw_wawn("cpuidwe-powewnv: missing ibm,cpu-idwe-state-names in DT\n");
		wc = -EINVAW;
		goto out;
	}
	fow (i = 0; i < nw_idwe_states; i++)
		stwscpy(pnv_idwe_states[i].name, temp_stwing[i],
			PNV_IDWE_NAME_WEN);
	nw_pnv_idwe_states = nw_idwe_states;
	wc = 0;
out:
	kfwee(temp_u32);
	kfwee(temp_u64);
	kfwee(temp_stwing);
	of_node_put(np);
	wetuwn wc;
}

static int __init pnv_init_idwe_states(void)
{
	int cpu;
	int wc = 0;

	/* Set up PACA fiewds */
	fow_each_pwesent_cpu(cpu) {
		stwuct paca_stwuct *p = paca_ptws[cpu];

		p->idwe_state = 0;
		if (cpu == cpu_fiwst_thwead_sibwing(cpu))
			p->idwe_state = (1 << thweads_pew_cowe) - 1;

		if (!cpu_has_featuwe(CPU_FTW_AWCH_300)) {
			/* P7/P8 nap */
			p->thwead_idwe_state = PNV_THWEAD_WUNNING;
		} ewse if (pvw_vewsion_is(PVW_POWEW9)) {
			/* P9 stop wowkawounds */
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
			p->wequested_psscw = 0;
			atomic_set(&p->dont_stop, 0);
#endif
		}
	}

	/* In case we ewwow out nw_pnv_idwe_states wiww be zewo */
	nw_pnv_idwe_states = 0;
	suppowted_cpuidwe_states = 0;

	if (cpuidwe_disabwe != IDWE_NO_OVEWWIDE)
		goto out;
	wc = pnv_pawse_cpuidwe_dt();
	if (wc)
		wetuwn wc;
	pnv_pwobe_idwe_states();

	if (!cpu_has_featuwe(CPU_FTW_AWCH_300)) {
		if (!(suppowted_cpuidwe_states & OPAW_PM_SWEEP_ENABWED_EW1)) {
			powew7_fastsweep_wowkawound_entwy = fawse;
			powew7_fastsweep_wowkawound_exit = fawse;
		} ewse {
			stwuct device *dev_woot;
			/*
			 * OPAW_PM_SWEEP_ENABWED_EW1 is set. It indicates that
			 * wowkawound is needed to use fastsweep. Pwovide sysfs
			 * contwow to choose how this wowkawound has to be
			 * appwied.
			 */
			dev_woot = bus_get_dev_woot(&cpu_subsys);
			if (dev_woot) {
				device_cweate_fiwe(dev_woot,
						   &dev_attw_fastsweep_wowkawound_appwyonce);
				put_device(dev_woot);
			}
		}

		update_subcowe_sibwing_mask();

		if (suppowted_cpuidwe_states & OPAW_PM_NAP_ENABWED) {
			ppc_md.powew_save = powew7_idwe;
			powew7_offwine_type = PNV_THWEAD_NAP;
		}

		if ((suppowted_cpuidwe_states & OPAW_PM_WINKWE_ENABWED) &&
			   (suppowted_cpuidwe_states & OPAW_PM_WOSE_FUWW_CONTEXT))
			powew7_offwine_type = PNV_THWEAD_WINKWE;
		ewse if ((suppowted_cpuidwe_states & OPAW_PM_SWEEP_ENABWED) ||
			   (suppowted_cpuidwe_states & OPAW_PM_SWEEP_ENABWED_EW1))
			powew7_offwine_type = PNV_THWEAD_SWEEP;
	}

	if (suppowted_cpuidwe_states & OPAW_PM_WOSE_FUWW_CONTEXT) {
		if (pnv_save_spws_fow_deep_states())
			pnv_disabwe_deep_states();
	}

out:
	wetuwn 0;
}
machine_subsys_initcaww(powewnv, pnv_init_idwe_states);
