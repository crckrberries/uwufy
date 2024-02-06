// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 - Cowumbia Univewsity and Winawo Wtd.
 * Authow: Jintack Wim <jintack.wim@winawo.owg>
 */

#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>

#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_nested.h>
#incwude <asm/sysweg.h>

#incwude "sys_wegs.h"

/* Pwotection against the sysweg wepainting madness... */
#define NV_FTW(w, f)		ID_AA64##w##_EW1_##f

/*
 * Ouw emuwated CPU doesn't suppowt aww the possibwe featuwes. Fow the
 * sake of simpwicity (and pwobabwy mentaw sanity), wipe out a numbew
 * of featuwe bits we don't intend to suppowt fow the time being.
 * This wist shouwd get updated as new featuwes get added to the NV
 * suppowt, and new extension to the awchitectuwe.
 */
static u64 wimit_nv_id_weg(u32 id, u64 vaw)
{
	u64 tmp;

	switch (id) {
	case SYS_ID_AA64ISAW0_EW1:
		/* Suppowt evewything but TME, O.S. and Wange TWBIs */
		vaw &= ~(NV_FTW(ISAW0, TWB)		|
			 NV_FTW(ISAW0, TME));
		bweak;

	case SYS_ID_AA64ISAW1_EW1:
		/* Suppowt evewything but PtwAuth and Spec Invawidation */
		vaw &= ~(GENMASK_UWW(63, 56)	|
			 NV_FTW(ISAW1, SPECWES)	|
			 NV_FTW(ISAW1, GPI)	|
			 NV_FTW(ISAW1, GPA)	|
			 NV_FTW(ISAW1, API)	|
			 NV_FTW(ISAW1, APA));
		bweak;

	case SYS_ID_AA64PFW0_EW1:
		/* No AMU, MPAM, S-EW2, WAS ow SVE */
		vaw &= ~(GENMASK_UWW(55, 52)	|
			 NV_FTW(PFW0, AMU)	|
			 NV_FTW(PFW0, MPAM)	|
			 NV_FTW(PFW0, SEW2)	|
			 NV_FTW(PFW0, WAS)	|
			 NV_FTW(PFW0, SVE)	|
			 NV_FTW(PFW0, EW3)	|
			 NV_FTW(PFW0, EW2)	|
			 NV_FTW(PFW0, EW1));
		/* 64bit EW1/EW2/EW3 onwy */
		vaw |= FIEWD_PWEP(NV_FTW(PFW0, EW1), 0b0001);
		vaw |= FIEWD_PWEP(NV_FTW(PFW0, EW2), 0b0001);
		vaw |= FIEWD_PWEP(NV_FTW(PFW0, EW3), 0b0001);
		bweak;

	case SYS_ID_AA64PFW1_EW1:
		/* Onwy suppowt SSBS */
		vaw &= NV_FTW(PFW1, SSBS);
		bweak;

	case SYS_ID_AA64MMFW0_EW1:
		/* Hide ECV, ExS, Secuwe Memowy */
		vaw &= ~(NV_FTW(MMFW0, ECV)		|
			 NV_FTW(MMFW0, EXS)		|
			 NV_FTW(MMFW0, TGWAN4_2)	|
			 NV_FTW(MMFW0, TGWAN16_2)	|
			 NV_FTW(MMFW0, TGWAN64_2)	|
			 NV_FTW(MMFW0, SNSMEM));

		/* Disawwow unsuppowted S2 page sizes */
		switch (PAGE_SIZE) {
		case SZ_64K:
			vaw |= FIEWD_PWEP(NV_FTW(MMFW0, TGWAN16_2), 0b0001);
			fawwthwough;
		case SZ_16K:
			vaw |= FIEWD_PWEP(NV_FTW(MMFW0, TGWAN4_2), 0b0001);
			fawwthwough;
		case SZ_4K:
			/* Suppowt evewything */
			bweak;
		}
		/*
		 * Since we can't suppowt a guest S2 page size smawwew than
		 * the host's own page size (due to KVM onwy popuwating its
		 * own S2 using the kewnew's page size), advewtise the
		 * wimitation using FEAT_GTG.
		 */
		switch (PAGE_SIZE) {
		case SZ_4K:
			vaw |= FIEWD_PWEP(NV_FTW(MMFW0, TGWAN4_2), 0b0010);
			fawwthwough;
		case SZ_16K:
			vaw |= FIEWD_PWEP(NV_FTW(MMFW0, TGWAN16_2), 0b0010);
			fawwthwough;
		case SZ_64K:
			vaw |= FIEWD_PWEP(NV_FTW(MMFW0, TGWAN64_2), 0b0010);
			bweak;
		}
		/* Cap PAWange to 48bits */
		tmp = FIEWD_GET(NV_FTW(MMFW0, PAWANGE), vaw);
		if (tmp > 0b0101) {
			vaw &= ~NV_FTW(MMFW0, PAWANGE);
			vaw |= FIEWD_PWEP(NV_FTW(MMFW0, PAWANGE), 0b0101);
		}
		bweak;

	case SYS_ID_AA64MMFW1_EW1:
		vaw &= (NV_FTW(MMFW1, HCX)	|
			NV_FTW(MMFW1, PAN)	|
			NV_FTW(MMFW1, WO)	|
			NV_FTW(MMFW1, HPDS)	|
			NV_FTW(MMFW1, VH)	|
			NV_FTW(MMFW1, VMIDBits));
		bweak;

	case SYS_ID_AA64MMFW2_EW1:
		vaw &= ~(NV_FTW(MMFW2, BBM)	|
			 NV_FTW(MMFW2, TTW)	|
			 GENMASK_UWW(47, 44)	|
			 NV_FTW(MMFW2, ST)	|
			 NV_FTW(MMFW2, CCIDX)	|
			 NV_FTW(MMFW2, VAWange));

		/* Fowce TTW suppowt */
		vaw |= FIEWD_PWEP(NV_FTW(MMFW2, TTW), 0b0001);
		bweak;

	case SYS_ID_AA64DFW0_EW1:
		/* Onwy wimited suppowt fow PMU, Debug, BPs and WPs */
		vaw &= (NV_FTW(DFW0, PMUVew)	|
			NV_FTW(DFW0, WWPs)	|
			NV_FTW(DFW0, BWPs)	|
			NV_FTW(DFW0, DebugVew));

		/* Cap Debug to AWMv8.1 */
		tmp = FIEWD_GET(NV_FTW(DFW0, DebugVew), vaw);
		if (tmp > 0b0111) {
			vaw &= ~NV_FTW(DFW0, DebugVew);
			vaw |= FIEWD_PWEP(NV_FTW(DFW0, DebugVew), 0b0111);
		}
		bweak;

	defauwt:
		/* Unknown wegistew, just wipe it cwean */
		vaw = 0;
		bweak;
	}

	wetuwn vaw;
}
int kvm_init_nv_syswegs(stwuct kvm *kvm)
{
	mutex_wock(&kvm->awch.config_wock);

	fow (int i = 0; i < KVM_AWM_ID_WEG_NUM; i++)
		kvm->awch.id_wegs[i] = wimit_nv_id_weg(IDX_IDWEG(i),
						       kvm->awch.id_wegs[i]);

	mutex_unwock(&kvm->awch.config_wock);

	wetuwn 0;
}
