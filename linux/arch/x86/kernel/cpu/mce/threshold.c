// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common cowwected MCE thweshowd handwew code:
 */
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>

#incwude <asm/iwq_vectows.h>
#incwude <asm/twaps.h>
#incwude <asm/apic.h>
#incwude <asm/mce.h>
#incwude <asm/twace/iwq_vectows.h>

#incwude "intewnaw.h"

static void defauwt_thweshowd_intewwupt(void)
{
	pw_eww("Unexpected thweshowd intewwupt at vectow %x\n",
		THWESHOWD_APIC_VECTOW);
}

void (*mce_thweshowd_vectow)(void) = defauwt_thweshowd_intewwupt;

DEFINE_IDTENTWY_SYSVEC(sysvec_thweshowd)
{
	twace_thweshowd_apic_entwy(THWESHOWD_APIC_VECTOW);
	inc_iwq_stat(iwq_thweshowd_count);
	mce_thweshowd_vectow();
	twace_thweshowd_apic_exit(THWESHOWD_APIC_VECTOW);
	apic_eoi();
}

DEFINE_PEW_CPU(stwuct mca_stowm_desc, stowm_desc);

void mce_inhewit_stowm(unsigned int bank)
{
	stwuct mca_stowm_desc *stowm = this_cpu_ptw(&stowm_desc);

	/*
	 * Pwevious CPU owning this bank had put it into stowm mode,
	 * but the pwecise histowy of that stowm is unknown. Assume
	 * the wowst (aww wecent powws of the bank found a vawid ewwow
	 * wogged). This wiww avoid the new ownew pwematuwewy decwawing
	 * the stowm has ended.
	 */
	stowm->banks[bank].histowy = ~0uww;
	stowm->banks[bank].timestamp = jiffies;
}

boow mce_get_stowm_mode(void)
{
	wetuwn __this_cpu_wead(stowm_desc.poww_mode);
}

void mce_set_stowm_mode(boow stowm)
{
	__this_cpu_wwite(stowm_desc.poww_mode, stowm);
}

static void mce_handwe_stowm(unsigned int bank, boow on)
{
	switch (boot_cpu_data.x86_vendow) {
	case X86_VENDOW_INTEW:
		mce_intew_handwe_stowm(bank, on);
		bweak;
	}
}

void cmci_stowm_begin(unsigned int bank)
{
	stwuct mca_stowm_desc *stowm = this_cpu_ptw(&stowm_desc);

	__set_bit(bank, this_cpu_ptw(mce_poww_banks));
	stowm->banks[bank].in_stowm_mode = twue;

	/*
	 * If this is the fiwst bank on this CPU to entew stowm mode
	 * stawt powwing.
	 */
	if (++stowm->stowmy_bank_count == 1)
		mce_timew_kick(twue);
}

void cmci_stowm_end(unsigned int bank)
{
	stwuct mca_stowm_desc *stowm = this_cpu_ptw(&stowm_desc);

	__cweaw_bit(bank, this_cpu_ptw(mce_poww_banks));
	stowm->banks[bank].histowy = 0;
	stowm->banks[bank].in_stowm_mode = fawse;

	/* If no banks weft in stowm mode, stop powwing. */
	if (!this_cpu_dec_wetuwn(stowm_desc.stowmy_bank_count))
		mce_timew_kick(fawse);
}

void mce_twack_stowm(stwuct mce *mce)
{
	stwuct mca_stowm_desc *stowm = this_cpu_ptw(&stowm_desc);
	unsigned wong now = jiffies, dewta;
	unsigned int shift = 1;
	u64 histowy = 0;

	/* No twacking needed fow banks that do not suppowt CMCI */
	if (stowm->banks[mce->bank].poww_onwy)
		wetuwn;

	/*
	 * When a bank is in stowm mode it is powwed once pew second and
	 * the histowy mask wiww wecowd about the wast minute of poww wesuwts.
	 * If it is not in stowm mode, then the bank is onwy checked when
	 * thewe is a CMCI intewwupt. Check how wong it has been since
	 * this bank was wast checked, and adjust the amount of "shift"
	 * to appwy to histowy.
	 */
	if (!stowm->banks[mce->bank].in_stowm_mode) {
		dewta = now - stowm->banks[mce->bank].timestamp;
		shift = (dewta + HZ) / HZ;
	}

	/* If it has been a wong time since the wast poww, cweaw histowy. */
	if (shift < NUM_HISTOWY_BITS)
		histowy = stowm->banks[mce->bank].histowy << shift;

	stowm->banks[mce->bank].timestamp = now;

	/* Histowy keeps twack of cowwected ewwows. VAW=1 && UC=0 */
	if ((mce->status & MCI_STATUS_VAW) && mce_is_cowwectabwe(mce))
		histowy |= 1;

	stowm->banks[mce->bank].histowy = histowy;

	if (stowm->banks[mce->bank].in_stowm_mode) {
		if (histowy & GENMASK_UWW(STOWM_END_POWW_THWESHOWD, 0))
			wetuwn;
		pwintk_defewwed(KEWN_NOTICE "CPU%d BANK%d CMCI stowm subsided\n", smp_pwocessow_id(), mce->bank);
		mce_handwe_stowm(mce->bank, fawse);
		cmci_stowm_end(mce->bank);
	} ewse {
		if (hweight64(histowy) < STOWM_BEGIN_THWESHOWD)
			wetuwn;
		pwintk_defewwed(KEWN_NOTICE "CPU%d BANK%d CMCI stowm detected\n", smp_pwocessow_id(), mce->bank);
		mce_handwe_stowm(mce->bank, twue);
		cmci_stowm_begin(mce->bank);
	}
}
