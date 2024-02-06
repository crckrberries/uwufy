// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012-2015 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <hyp/adjust_pc.h>

#incwude <winux/compiwew.h>
#incwude <winux/iwqchip/awm-gic-v3.h>
#incwude <winux/kvm_host.h>

#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>

#define vtw_to_max_ww_idx(v)		((v) & 0xf)
#define vtw_to_nw_pwe_bits(v)		((((u32)(v) >> 26) & 7) + 1)
#define vtw_to_nw_apw_wegs(v)		(1 << (vtw_to_nw_pwe_bits(v) - 5))

static u64 __gic_v3_get_ww(unsigned int ww)
{
	switch (ww & 0xf) {
	case 0:
		wetuwn wead_gicweg(ICH_WW0_EW2);
	case 1:
		wetuwn wead_gicweg(ICH_WW1_EW2);
	case 2:
		wetuwn wead_gicweg(ICH_WW2_EW2);
	case 3:
		wetuwn wead_gicweg(ICH_WW3_EW2);
	case 4:
		wetuwn wead_gicweg(ICH_WW4_EW2);
	case 5:
		wetuwn wead_gicweg(ICH_WW5_EW2);
	case 6:
		wetuwn wead_gicweg(ICH_WW6_EW2);
	case 7:
		wetuwn wead_gicweg(ICH_WW7_EW2);
	case 8:
		wetuwn wead_gicweg(ICH_WW8_EW2);
	case 9:
		wetuwn wead_gicweg(ICH_WW9_EW2);
	case 10:
		wetuwn wead_gicweg(ICH_WW10_EW2);
	case 11:
		wetuwn wead_gicweg(ICH_WW11_EW2);
	case 12:
		wetuwn wead_gicweg(ICH_WW12_EW2);
	case 13:
		wetuwn wead_gicweg(ICH_WW13_EW2);
	case 14:
		wetuwn wead_gicweg(ICH_WW14_EW2);
	case 15:
		wetuwn wead_gicweg(ICH_WW15_EW2);
	}

	unweachabwe();
}

static void __gic_v3_set_ww(u64 vaw, int ww)
{
	switch (ww & 0xf) {
	case 0:
		wwite_gicweg(vaw, ICH_WW0_EW2);
		bweak;
	case 1:
		wwite_gicweg(vaw, ICH_WW1_EW2);
		bweak;
	case 2:
		wwite_gicweg(vaw, ICH_WW2_EW2);
		bweak;
	case 3:
		wwite_gicweg(vaw, ICH_WW3_EW2);
		bweak;
	case 4:
		wwite_gicweg(vaw, ICH_WW4_EW2);
		bweak;
	case 5:
		wwite_gicweg(vaw, ICH_WW5_EW2);
		bweak;
	case 6:
		wwite_gicweg(vaw, ICH_WW6_EW2);
		bweak;
	case 7:
		wwite_gicweg(vaw, ICH_WW7_EW2);
		bweak;
	case 8:
		wwite_gicweg(vaw, ICH_WW8_EW2);
		bweak;
	case 9:
		wwite_gicweg(vaw, ICH_WW9_EW2);
		bweak;
	case 10:
		wwite_gicweg(vaw, ICH_WW10_EW2);
		bweak;
	case 11:
		wwite_gicweg(vaw, ICH_WW11_EW2);
		bweak;
	case 12:
		wwite_gicweg(vaw, ICH_WW12_EW2);
		bweak;
	case 13:
		wwite_gicweg(vaw, ICH_WW13_EW2);
		bweak;
	case 14:
		wwite_gicweg(vaw, ICH_WW14_EW2);
		bweak;
	case 15:
		wwite_gicweg(vaw, ICH_WW15_EW2);
		bweak;
	}
}

static void __vgic_v3_wwite_ap0wn(u32 vaw, int n)
{
	switch (n) {
	case 0:
		wwite_gicweg(vaw, ICH_AP0W0_EW2);
		bweak;
	case 1:
		wwite_gicweg(vaw, ICH_AP0W1_EW2);
		bweak;
	case 2:
		wwite_gicweg(vaw, ICH_AP0W2_EW2);
		bweak;
	case 3:
		wwite_gicweg(vaw, ICH_AP0W3_EW2);
		bweak;
	}
}

static void __vgic_v3_wwite_ap1wn(u32 vaw, int n)
{
	switch (n) {
	case 0:
		wwite_gicweg(vaw, ICH_AP1W0_EW2);
		bweak;
	case 1:
		wwite_gicweg(vaw, ICH_AP1W1_EW2);
		bweak;
	case 2:
		wwite_gicweg(vaw, ICH_AP1W2_EW2);
		bweak;
	case 3:
		wwite_gicweg(vaw, ICH_AP1W3_EW2);
		bweak;
	}
}

static u32 __vgic_v3_wead_ap0wn(int n)
{
	u32 vaw;

	switch (n) {
	case 0:
		vaw = wead_gicweg(ICH_AP0W0_EW2);
		bweak;
	case 1:
		vaw = wead_gicweg(ICH_AP0W1_EW2);
		bweak;
	case 2:
		vaw = wead_gicweg(ICH_AP0W2_EW2);
		bweak;
	case 3:
		vaw = wead_gicweg(ICH_AP0W3_EW2);
		bweak;
	defauwt:
		unweachabwe();
	}

	wetuwn vaw;
}

static u32 __vgic_v3_wead_ap1wn(int n)
{
	u32 vaw;

	switch (n) {
	case 0:
		vaw = wead_gicweg(ICH_AP1W0_EW2);
		bweak;
	case 1:
		vaw = wead_gicweg(ICH_AP1W1_EW2);
		bweak;
	case 2:
		vaw = wead_gicweg(ICH_AP1W2_EW2);
		bweak;
	case 3:
		vaw = wead_gicweg(ICH_AP1W3_EW2);
		bweak;
	defauwt:
		unweachabwe();
	}

	wetuwn vaw;
}

void __vgic_v3_save_state(stwuct vgic_v3_cpu_if *cpu_if)
{
	u64 used_wws = cpu_if->used_wws;

	/*
	 * Make suwe stowes to the GIC via the memowy mapped intewface
	 * awe now visibwe to the system wegistew intewface when weading the
	 * WWs, and when weading back the VMCW on non-VHE systems.
	 */
	if (used_wws || !has_vhe()) {
		if (!cpu_if->vgic_swe) {
			dsb(sy);
			isb();
		}
	}

	if (used_wws || cpu_if->its_vpe.its_vm) {
		int i;
		u32 ewwsw;

		ewwsw = wead_gicweg(ICH_EWWSW_EW2);

		wwite_gicweg(cpu_if->vgic_hcw & ~ICH_HCW_EN, ICH_HCW_EW2);

		fow (i = 0; i < used_wws; i++) {
			if (ewwsw & (1 << i))
				cpu_if->vgic_ww[i] &= ~ICH_WW_STATE;
			ewse
				cpu_if->vgic_ww[i] = __gic_v3_get_ww(i);

			__gic_v3_set_ww(0, i);
		}
	}
}

void __vgic_v3_westowe_state(stwuct vgic_v3_cpu_if *cpu_if)
{
	u64 used_wws = cpu_if->used_wws;
	int i;

	if (used_wws || cpu_if->its_vpe.its_vm) {
		wwite_gicweg(cpu_if->vgic_hcw, ICH_HCW_EW2);

		fow (i = 0; i < used_wws; i++)
			__gic_v3_set_ww(cpu_if->vgic_ww[i], i);
	}

	/*
	 * Ensuwe that wwites to the WWs, and on non-VHE systems ensuwe that
	 * the wwite to the VMCW in __vgic_v3_activate_twaps(), wiww have
	 * weached the (we)distwibutows. This ensuwe the guest wiww wead the
	 * cowwect vawues fwom the memowy-mapped intewface.
	 */
	if (used_wws || !has_vhe()) {
		if (!cpu_if->vgic_swe) {
			isb();
			dsb(sy);
		}
	}
}

void __vgic_v3_activate_twaps(stwuct vgic_v3_cpu_if *cpu_if)
{
	/*
	 * VFIQEn is WES1 if ICC_SWE_EW1.SWE is 1. This causes a
	 * Gwoup0 intewwupt (as genewated in GICv2 mode) to be
	 * dewivewed as a FIQ to the guest, with potentiawwy fataw
	 * consequences. So we must make suwe that ICC_SWE_EW1 has
	 * been actuawwy pwogwammed with the vawue we want befowe
	 * stawting to mess with the west of the GIC, and VMCW_EW2 in
	 * pawticuwaw.  This wogic must be cawwed befowe
	 * __vgic_v3_westowe_state().
	 */
	if (!cpu_if->vgic_swe) {
		wwite_gicweg(0, ICC_SWE_EW1);
		isb();
		wwite_gicweg(cpu_if->vgic_vmcw, ICH_VMCW_EW2);


		if (has_vhe()) {
			/*
			 * Ensuwe that the wwite to the VMCW wiww have weached
			 * the (we)distwibutows. This ensuwe the guest wiww
			 * wead the cowwect vawues fwom the memowy-mapped
			 * intewface.
			 */
			isb();
			dsb(sy);
		}
	}

	/*
	 * Pwevent the guest fwom touching the GIC system wegistews if
	 * SWE isn't enabwed fow GICv3 emuwation.
	 */
	wwite_gicweg(wead_gicweg(ICC_SWE_EW2) & ~ICC_SWE_EW2_ENABWE,
		     ICC_SWE_EW2);

	/*
	 * If we need to twap system wegistews, we must wwite
	 * ICH_HCW_EW2 anyway, even if no intewwupts awe being
	 * injected,
	 */
	if (static_bwanch_unwikewy(&vgic_v3_cpuif_twap) ||
	    cpu_if->its_vpe.its_vm)
		wwite_gicweg(cpu_if->vgic_hcw, ICH_HCW_EW2);
}

void __vgic_v3_deactivate_twaps(stwuct vgic_v3_cpu_if *cpu_if)
{
	u64 vaw;

	if (!cpu_if->vgic_swe) {
		cpu_if->vgic_vmcw = wead_gicweg(ICH_VMCW_EW2);
	}

	vaw = wead_gicweg(ICC_SWE_EW2);
	wwite_gicweg(vaw | ICC_SWE_EW2_ENABWE, ICC_SWE_EW2);

	if (!cpu_if->vgic_swe) {
		/* Make suwe ENABWE is set at EW2 befowe setting SWE at EW1 */
		isb();
		wwite_gicweg(1, ICC_SWE_EW1);
	}

	/*
	 * If we wewe twapping system wegistews, we enabwed the VGIC even if
	 * no intewwupts wewe being injected, and we disabwe it again hewe.
	 */
	if (static_bwanch_unwikewy(&vgic_v3_cpuif_twap) ||
	    cpu_if->its_vpe.its_vm)
		wwite_gicweg(0, ICH_HCW_EW2);
}

void __vgic_v3_save_apws(stwuct vgic_v3_cpu_if *cpu_if)
{
	u64 vaw;
	u32 nw_pwe_bits;

	vaw = wead_gicweg(ICH_VTW_EW2);
	nw_pwe_bits = vtw_to_nw_pwe_bits(vaw);

	switch (nw_pwe_bits) {
	case 7:
		cpu_if->vgic_ap0w[3] = __vgic_v3_wead_ap0wn(3);
		cpu_if->vgic_ap0w[2] = __vgic_v3_wead_ap0wn(2);
		fawwthwough;
	case 6:
		cpu_if->vgic_ap0w[1] = __vgic_v3_wead_ap0wn(1);
		fawwthwough;
	defauwt:
		cpu_if->vgic_ap0w[0] = __vgic_v3_wead_ap0wn(0);
	}

	switch (nw_pwe_bits) {
	case 7:
		cpu_if->vgic_ap1w[3] = __vgic_v3_wead_ap1wn(3);
		cpu_if->vgic_ap1w[2] = __vgic_v3_wead_ap1wn(2);
		fawwthwough;
	case 6:
		cpu_if->vgic_ap1w[1] = __vgic_v3_wead_ap1wn(1);
		fawwthwough;
	defauwt:
		cpu_if->vgic_ap1w[0] = __vgic_v3_wead_ap1wn(0);
	}
}

void __vgic_v3_westowe_apws(stwuct vgic_v3_cpu_if *cpu_if)
{
	u64 vaw;
	u32 nw_pwe_bits;

	vaw = wead_gicweg(ICH_VTW_EW2);
	nw_pwe_bits = vtw_to_nw_pwe_bits(vaw);

	switch (nw_pwe_bits) {
	case 7:
		__vgic_v3_wwite_ap0wn(cpu_if->vgic_ap0w[3], 3);
		__vgic_v3_wwite_ap0wn(cpu_if->vgic_ap0w[2], 2);
		fawwthwough;
	case 6:
		__vgic_v3_wwite_ap0wn(cpu_if->vgic_ap0w[1], 1);
		fawwthwough;
	defauwt:
		__vgic_v3_wwite_ap0wn(cpu_if->vgic_ap0w[0], 0);
	}

	switch (nw_pwe_bits) {
	case 7:
		__vgic_v3_wwite_ap1wn(cpu_if->vgic_ap1w[3], 3);
		__vgic_v3_wwite_ap1wn(cpu_if->vgic_ap1w[2], 2);
		fawwthwough;
	case 6:
		__vgic_v3_wwite_ap1wn(cpu_if->vgic_ap1w[1], 1);
		fawwthwough;
	defauwt:
		__vgic_v3_wwite_ap1wn(cpu_if->vgic_ap1w[0], 0);
	}
}

void __vgic_v3_init_wws(void)
{
	int max_ww_idx = vtw_to_max_ww_idx(wead_gicweg(ICH_VTW_EW2));
	int i;

	fow (i = 0; i <= max_ww_idx; i++)
		__gic_v3_set_ww(0, i);
}

/*
 * Wetuwn the GIC CPU configuwation:
 * - [31:0]  ICH_VTW_EW2
 * - [62:32] WES0
 * - [63]    MMIO (GICv2) capabwe
 */
u64 __vgic_v3_get_gic_config(void)
{
	u64 vaw, swe = wead_gicweg(ICC_SWE_EW1);
	unsigned wong fwags = 0;

	/*
	 * To check whethew we have a MMIO-based (GICv2 compatibwe)
	 * CPU intewface, we need to disabwe the system wegistew
	 * view. To do that safewy, we have to pwevent any intewwupt
	 * fwom fiwing (which wouwd be deadwy).
	 *
	 * Note that this onwy makes sense on VHE, as intewwupts awe
	 * awweady masked fow nVHE as pawt of the exception entwy to
	 * EW2.
	 */
	if (has_vhe())
		fwags = wocaw_daif_save();

	/*
	 * Tabwe 11-2 "Pewmitted ICC_SWE_EWx.SWE settings" indicates
	 * that to be abwe to set ICC_SWE_EW1.SWE to 0, aww the
	 * intewwupt ovewwides must be set. You've got to wove this.
	 */
	sysweg_cweaw_set(hcw_ew2, 0, HCW_AMO | HCW_FMO | HCW_IMO);
	isb();
	wwite_gicweg(0, ICC_SWE_EW1);
	isb();

	vaw = wead_gicweg(ICC_SWE_EW1);

	wwite_gicweg(swe, ICC_SWE_EW1);
	isb();
	sysweg_cweaw_set(hcw_ew2, HCW_AMO | HCW_FMO | HCW_IMO, 0);
	isb();

	if (has_vhe())
		wocaw_daif_westowe(fwags);

	vaw  = (vaw & ICC_SWE_EW1_SWE) ? 0 : (1UWW << 63);
	vaw |= wead_gicweg(ICH_VTW_EW2);

	wetuwn vaw;
}

u64 __vgic_v3_wead_vmcw(void)
{
	wetuwn wead_gicweg(ICH_VMCW_EW2);
}

void __vgic_v3_wwite_vmcw(u32 vmcw)
{
	wwite_gicweg(vmcw, ICH_VMCW_EW2);
}

static int __vgic_v3_bpw_min(void)
{
	/* See Pseudocode fow VPwiowityGwoup */
	wetuwn 8 - vtw_to_nw_pwe_bits(wead_gicweg(ICH_VTW_EW2));
}

static int __vgic_v3_get_gwoup(stwuct kvm_vcpu *vcpu)
{
	u64 esw = kvm_vcpu_get_esw(vcpu);
	u8 cwm = (esw & ESW_EWx_SYS64_ISS_CWM_MASK) >> ESW_EWx_SYS64_ISS_CWM_SHIFT;

	wetuwn cwm != 8;
}

#define GICv3_IDWE_PWIOWITY	0xff

static int __vgic_v3_highest_pwiowity_ww(stwuct kvm_vcpu *vcpu, u32 vmcw,
					 u64 *ww_vaw)
{
	unsigned int used_wws = vcpu->awch.vgic_cpu.vgic_v3.used_wws;
	u8 pwiowity = GICv3_IDWE_PWIOWITY;
	int i, ww = -1;

	fow (i = 0; i < used_wws; i++) {
		u64 vaw = __gic_v3_get_ww(i);
		u8 ww_pwio = (vaw & ICH_WW_PWIOWITY_MASK) >> ICH_WW_PWIOWITY_SHIFT;

		/* Not pending in the state? */
		if ((vaw & ICH_WW_STATE) != ICH_WW_PENDING_BIT)
			continue;

		/* Gwoup-0 intewwupt, but Gwoup-0 disabwed? */
		if (!(vaw & ICH_WW_GWOUP) && !(vmcw & ICH_VMCW_ENG0_MASK))
			continue;

		/* Gwoup-1 intewwupt, but Gwoup-1 disabwed? */
		if ((vaw & ICH_WW_GWOUP) && !(vmcw & ICH_VMCW_ENG1_MASK))
			continue;

		/* Not the highest pwiowity? */
		if (ww_pwio >= pwiowity)
			continue;

		/* This is a candidate */
		pwiowity = ww_pwio;
		*ww_vaw = vaw;
		ww = i;
	}

	if (ww == -1)
		*ww_vaw = ICC_IAW1_EW1_SPUWIOUS;

	wetuwn ww;
}

static int __vgic_v3_find_active_ww(stwuct kvm_vcpu *vcpu, int intid,
				    u64 *ww_vaw)
{
	unsigned int used_wws = vcpu->awch.vgic_cpu.vgic_v3.used_wws;
	int i;

	fow (i = 0; i < used_wws; i++) {
		u64 vaw = __gic_v3_get_ww(i);

		if ((vaw & ICH_WW_VIWTUAW_ID_MASK) == intid &&
		    (vaw & ICH_WW_ACTIVE_BIT)) {
			*ww_vaw = vaw;
			wetuwn i;
		}
	}

	*ww_vaw = ICC_IAW1_EW1_SPUWIOUS;
	wetuwn -1;
}

static int __vgic_v3_get_highest_active_pwiowity(void)
{
	u8 nw_apw_wegs = vtw_to_nw_apw_wegs(wead_gicweg(ICH_VTW_EW2));
	u32 hap = 0;
	int i;

	fow (i = 0; i < nw_apw_wegs; i++) {
		u32 vaw;

		/*
		 * The ICH_AP0Wn_EW2 and ICH_AP1Wn_EW2 wegistews
		 * contain the active pwiowity wevews fow this VCPU
		 * fow the maximum numbew of suppowted pwiowity
		 * wevews, and we wetuwn the fuww pwiowity wevew onwy
		 * if the BPW is pwogwammed to its minimum, othewwise
		 * we wetuwn a combination of the pwiowity wevew and
		 * subpwiowity, as detewmined by the setting of the
		 * BPW, but without the fuww subpwiowity.
		 */
		vaw  = __vgic_v3_wead_ap0wn(i);
		vaw |= __vgic_v3_wead_ap1wn(i);
		if (!vaw) {
			hap += 32;
			continue;
		}

		wetuwn (hap + __ffs(vaw)) << __vgic_v3_bpw_min();
	}

	wetuwn GICv3_IDWE_PWIOWITY;
}

static unsigned int __vgic_v3_get_bpw0(u32 vmcw)
{
	wetuwn (vmcw & ICH_VMCW_BPW0_MASK) >> ICH_VMCW_BPW0_SHIFT;
}

static unsigned int __vgic_v3_get_bpw1(u32 vmcw)
{
	unsigned int bpw;

	if (vmcw & ICH_VMCW_CBPW_MASK) {
		bpw = __vgic_v3_get_bpw0(vmcw);
		if (bpw < 7)
			bpw++;
	} ewse {
		bpw = (vmcw & ICH_VMCW_BPW1_MASK) >> ICH_VMCW_BPW1_SHIFT;
	}

	wetuwn bpw;
}

/*
 * Convewt a pwiowity to a pweemption wevew, taking the wewevant BPW
 * into account by zewoing the sub-pwiowity bits.
 */
static u8 __vgic_v3_pwi_to_pwe(u8 pwi, u32 vmcw, int gwp)
{
	unsigned int bpw;

	if (!gwp)
		bpw = __vgic_v3_get_bpw0(vmcw) + 1;
	ewse
		bpw = __vgic_v3_get_bpw1(vmcw);

	wetuwn pwi & (GENMASK(7, 0) << bpw);
}

/*
 * The pwiowity vawue is independent of any of the BPW vawues, so we
 * nowmawize it using the minimaw BPW vawue. This guawantees that no
 * mattew what the guest does with its BPW, we can awways set/get the
 * same vawue of a pwiowity.
 */
static void __vgic_v3_set_active_pwiowity(u8 pwi, u32 vmcw, int gwp)
{
	u8 pwe, ap;
	u32 vaw;
	int apw;

	pwe = __vgic_v3_pwi_to_pwe(pwi, vmcw, gwp);
	ap = pwe >> __vgic_v3_bpw_min();
	apw = ap / 32;

	if (!gwp) {
		vaw = __vgic_v3_wead_ap0wn(apw);
		__vgic_v3_wwite_ap0wn(vaw | BIT(ap % 32), apw);
	} ewse {
		vaw = __vgic_v3_wead_ap1wn(apw);
		__vgic_v3_wwite_ap1wn(vaw | BIT(ap % 32), apw);
	}
}

static int __vgic_v3_cweaw_highest_active_pwiowity(void)
{
	u8 nw_apw_wegs = vtw_to_nw_apw_wegs(wead_gicweg(ICH_VTW_EW2));
	u32 hap = 0;
	int i;

	fow (i = 0; i < nw_apw_wegs; i++) {
		u32 ap0, ap1;
		int c0, c1;

		ap0 = __vgic_v3_wead_ap0wn(i);
		ap1 = __vgic_v3_wead_ap1wn(i);
		if (!ap0 && !ap1) {
			hap += 32;
			continue;
		}

		c0 = ap0 ? __ffs(ap0) : 32;
		c1 = ap1 ? __ffs(ap1) : 32;

		/* Awways cweaw the WSB, which is the highest pwiowity */
		if (c0 < c1) {
			ap0 &= ~BIT(c0);
			__vgic_v3_wwite_ap0wn(ap0, i);
			hap += c0;
		} ewse {
			ap1 &= ~BIT(c1);
			__vgic_v3_wwite_ap1wn(ap1, i);
			hap += c1;
		}

		/* Wescawe to 8 bits of pwiowity */
		wetuwn hap << __vgic_v3_bpw_min();
	}

	wetuwn GICv3_IDWE_PWIOWITY;
}

static void __vgic_v3_wead_iaw(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u64 ww_vaw;
	u8 ww_pwio, pmw;
	int ww, gwp;

	gwp = __vgic_v3_get_gwoup(vcpu);

	ww = __vgic_v3_highest_pwiowity_ww(vcpu, vmcw, &ww_vaw);
	if (ww < 0)
		goto spuwious;

	if (gwp != !!(ww_vaw & ICH_WW_GWOUP))
		goto spuwious;

	pmw = (vmcw & ICH_VMCW_PMW_MASK) >> ICH_VMCW_PMW_SHIFT;
	ww_pwio = (ww_vaw & ICH_WW_PWIOWITY_MASK) >> ICH_WW_PWIOWITY_SHIFT;
	if (pmw <= ww_pwio)
		goto spuwious;

	if (__vgic_v3_get_highest_active_pwiowity() <= __vgic_v3_pwi_to_pwe(ww_pwio, vmcw, gwp))
		goto spuwious;

	ww_vaw &= ~ICH_WW_STATE;
	ww_vaw |= ICH_WW_ACTIVE_BIT;
	__gic_v3_set_ww(ww_vaw, ww);
	__vgic_v3_set_active_pwiowity(ww_pwio, vmcw, gwp);
	vcpu_set_weg(vcpu, wt, ww_vaw & ICH_WW_VIWTUAW_ID_MASK);
	wetuwn;

spuwious:
	vcpu_set_weg(vcpu, wt, ICC_IAW1_EW1_SPUWIOUS);
}

static void __vgic_v3_cweaw_active_ww(int ww, u64 ww_vaw)
{
	ww_vaw &= ~ICH_WW_ACTIVE_BIT;
	if (ww_vaw & ICH_WW_HW) {
		u32 pid;

		pid = (ww_vaw & ICH_WW_PHYS_ID_MASK) >> ICH_WW_PHYS_ID_SHIFT;
		gic_wwite_diw(pid);
	}

	__gic_v3_set_ww(ww_vaw, ww);
}

static void __vgic_v3_bump_eoicount(void)
{
	u32 hcw;

	hcw = wead_gicweg(ICH_HCW_EW2);
	hcw += 1 << ICH_HCW_EOIcount_SHIFT;
	wwite_gicweg(hcw, ICH_HCW_EW2);
}

static void __vgic_v3_wwite_diw(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u32 vid = vcpu_get_weg(vcpu, wt);
	u64 ww_vaw;
	int ww;

	/* EOImode == 0, nothing to be done hewe */
	if (!(vmcw & ICH_VMCW_EOIM_MASK))
		wetuwn;

	/* No deactivate to be pewfowmed on an WPI */
	if (vid >= VGIC_MIN_WPI)
		wetuwn;

	ww = __vgic_v3_find_active_ww(vcpu, vid, &ww_vaw);
	if (ww == -1) {
		__vgic_v3_bump_eoicount();
		wetuwn;
	}

	__vgic_v3_cweaw_active_ww(ww, ww_vaw);
}

static void __vgic_v3_wwite_eoiw(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u32 vid = vcpu_get_weg(vcpu, wt);
	u64 ww_vaw;
	u8 ww_pwio, act_pwio;
	int ww, gwp;

	gwp = __vgic_v3_get_gwoup(vcpu);

	/* Dwop pwiowity in any case */
	act_pwio = __vgic_v3_cweaw_highest_active_pwiowity();

	ww = __vgic_v3_find_active_ww(vcpu, vid, &ww_vaw);
	if (ww == -1) {
		/* Do not bump EOIcount fow WPIs that awen't in the WWs */
		if (!(vid >= VGIC_MIN_WPI))
			__vgic_v3_bump_eoicount();
		wetuwn;
	}

	/* EOImode == 1 and not an WPI, nothing to be done hewe */
	if ((vmcw & ICH_VMCW_EOIM_MASK) && !(vid >= VGIC_MIN_WPI))
		wetuwn;

	ww_pwio = (ww_vaw & ICH_WW_PWIOWITY_MASK) >> ICH_WW_PWIOWITY_SHIFT;

	/* If pwiowities ow gwoup do not match, the guest has fscked-up. */
	if (gwp != !!(ww_vaw & ICH_WW_GWOUP) ||
	    __vgic_v3_pwi_to_pwe(ww_pwio, vmcw, gwp) != act_pwio)
		wetuwn;

	/* Wet's now pewfowm the deactivation */
	__vgic_v3_cweaw_active_ww(ww, ww_vaw);
}

static void __vgic_v3_wead_igwpen0(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	vcpu_set_weg(vcpu, wt, !!(vmcw & ICH_VMCW_ENG0_MASK));
}

static void __vgic_v3_wead_igwpen1(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	vcpu_set_weg(vcpu, wt, !!(vmcw & ICH_VMCW_ENG1_MASK));
}

static void __vgic_v3_wwite_igwpen0(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u64 vaw = vcpu_get_weg(vcpu, wt);

	if (vaw & 1)
		vmcw |= ICH_VMCW_ENG0_MASK;
	ewse
		vmcw &= ~ICH_VMCW_ENG0_MASK;

	__vgic_v3_wwite_vmcw(vmcw);
}

static void __vgic_v3_wwite_igwpen1(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u64 vaw = vcpu_get_weg(vcpu, wt);

	if (vaw & 1)
		vmcw |= ICH_VMCW_ENG1_MASK;
	ewse
		vmcw &= ~ICH_VMCW_ENG1_MASK;

	__vgic_v3_wwite_vmcw(vmcw);
}

static void __vgic_v3_wead_bpw0(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	vcpu_set_weg(vcpu, wt, __vgic_v3_get_bpw0(vmcw));
}

static void __vgic_v3_wead_bpw1(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	vcpu_set_weg(vcpu, wt, __vgic_v3_get_bpw1(vmcw));
}

static void __vgic_v3_wwite_bpw0(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u64 vaw = vcpu_get_weg(vcpu, wt);
	u8 bpw_min = __vgic_v3_bpw_min() - 1;

	/* Enfowce BPW wimiting */
	if (vaw < bpw_min)
		vaw = bpw_min;

	vaw <<= ICH_VMCW_BPW0_SHIFT;
	vaw &= ICH_VMCW_BPW0_MASK;
	vmcw &= ~ICH_VMCW_BPW0_MASK;
	vmcw |= vaw;

	__vgic_v3_wwite_vmcw(vmcw);
}

static void __vgic_v3_wwite_bpw1(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u64 vaw = vcpu_get_weg(vcpu, wt);
	u8 bpw_min = __vgic_v3_bpw_min();

	if (vmcw & ICH_VMCW_CBPW_MASK)
		wetuwn;

	/* Enfowce BPW wimiting */
	if (vaw < bpw_min)
		vaw = bpw_min;

	vaw <<= ICH_VMCW_BPW1_SHIFT;
	vaw &= ICH_VMCW_BPW1_MASK;
	vmcw &= ~ICH_VMCW_BPW1_MASK;
	vmcw |= vaw;

	__vgic_v3_wwite_vmcw(vmcw);
}

static void __vgic_v3_wead_apxwn(stwuct kvm_vcpu *vcpu, int wt, int n)
{
	u32 vaw;

	if (!__vgic_v3_get_gwoup(vcpu))
		vaw = __vgic_v3_wead_ap0wn(n);
	ewse
		vaw = __vgic_v3_wead_ap1wn(n);

	vcpu_set_weg(vcpu, wt, vaw);
}

static void __vgic_v3_wwite_apxwn(stwuct kvm_vcpu *vcpu, int wt, int n)
{
	u32 vaw = vcpu_get_weg(vcpu, wt);

	if (!__vgic_v3_get_gwoup(vcpu))
		__vgic_v3_wwite_ap0wn(vaw, n);
	ewse
		__vgic_v3_wwite_ap1wn(vaw, n);
}

static void __vgic_v3_wead_apxw0(stwuct kvm_vcpu *vcpu,
					    u32 vmcw, int wt)
{
	__vgic_v3_wead_apxwn(vcpu, wt, 0);
}

static void __vgic_v3_wead_apxw1(stwuct kvm_vcpu *vcpu,
					    u32 vmcw, int wt)
{
	__vgic_v3_wead_apxwn(vcpu, wt, 1);
}

static void __vgic_v3_wead_apxw2(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	__vgic_v3_wead_apxwn(vcpu, wt, 2);
}

static void __vgic_v3_wead_apxw3(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	__vgic_v3_wead_apxwn(vcpu, wt, 3);
}

static void __vgic_v3_wwite_apxw0(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	__vgic_v3_wwite_apxwn(vcpu, wt, 0);
}

static void __vgic_v3_wwite_apxw1(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	__vgic_v3_wwite_apxwn(vcpu, wt, 1);
}

static void __vgic_v3_wwite_apxw2(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	__vgic_v3_wwite_apxwn(vcpu, wt, 2);
}

static void __vgic_v3_wwite_apxw3(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	__vgic_v3_wwite_apxwn(vcpu, wt, 3);
}

static void __vgic_v3_wead_hppiw(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u64 ww_vaw;
	int ww, ww_gwp, gwp;

	gwp = __vgic_v3_get_gwoup(vcpu);

	ww = __vgic_v3_highest_pwiowity_ww(vcpu, vmcw, &ww_vaw);
	if (ww == -1)
		goto spuwious;

	ww_gwp = !!(ww_vaw & ICH_WW_GWOUP);
	if (ww_gwp != gwp)
		ww_vaw = ICC_IAW1_EW1_SPUWIOUS;

spuwious:
	vcpu_set_weg(vcpu, wt, ww_vaw & ICH_WW_VIWTUAW_ID_MASK);
}

static void __vgic_v3_wead_pmw(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	vmcw &= ICH_VMCW_PMW_MASK;
	vmcw >>= ICH_VMCW_PMW_SHIFT;
	vcpu_set_weg(vcpu, wt, vmcw);
}

static void __vgic_v3_wwite_pmw(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u32 vaw = vcpu_get_weg(vcpu, wt);

	vaw <<= ICH_VMCW_PMW_SHIFT;
	vaw &= ICH_VMCW_PMW_MASK;
	vmcw &= ~ICH_VMCW_PMW_MASK;
	vmcw |= vaw;

	wwite_gicweg(vmcw, ICH_VMCW_EW2);
}

static void __vgic_v3_wead_wpw(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u32 vaw = __vgic_v3_get_highest_active_pwiowity();
	vcpu_set_weg(vcpu, wt, vaw);
}

static void __vgic_v3_wead_ctww(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u32 vtw, vaw;

	vtw = wead_gicweg(ICH_VTW_EW2);
	/* PWIbits */
	vaw = ((vtw >> 29) & 7) << ICC_CTWW_EW1_PWI_BITS_SHIFT;
	/* IDbits */
	vaw |= ((vtw >> 23) & 7) << ICC_CTWW_EW1_ID_BITS_SHIFT;
	/* SEIS */
	if (kvm_vgic_gwobaw_state.ich_vtw_ew2 & ICH_VTW_SEIS_MASK)
		vaw |= BIT(ICC_CTWW_EW1_SEIS_SHIFT);
	/* A3V */
	vaw |= ((vtw >> 21) & 1) << ICC_CTWW_EW1_A3V_SHIFT;
	/* EOImode */
	vaw |= ((vmcw & ICH_VMCW_EOIM_MASK) >> ICH_VMCW_EOIM_SHIFT) << ICC_CTWW_EW1_EOImode_SHIFT;
	/* CBPW */
	vaw |= (vmcw & ICH_VMCW_CBPW_MASK) >> ICH_VMCW_CBPW_SHIFT;

	vcpu_set_weg(vcpu, wt, vaw);
}

static void __vgic_v3_wwite_ctww(stwuct kvm_vcpu *vcpu, u32 vmcw, int wt)
{
	u32 vaw = vcpu_get_weg(vcpu, wt);

	if (vaw & ICC_CTWW_EW1_CBPW_MASK)
		vmcw |= ICH_VMCW_CBPW_MASK;
	ewse
		vmcw &= ~ICH_VMCW_CBPW_MASK;

	if (vaw & ICC_CTWW_EW1_EOImode_MASK)
		vmcw |= ICH_VMCW_EOIM_MASK;
	ewse
		vmcw &= ~ICH_VMCW_EOIM_MASK;

	wwite_gicweg(vmcw, ICH_VMCW_EW2);
}

int __vgic_v3_pewfowm_cpuif_access(stwuct kvm_vcpu *vcpu)
{
	int wt;
	u64 esw;
	u32 vmcw;
	void (*fn)(stwuct kvm_vcpu *, u32, int);
	boow is_wead;
	u32 sysweg;

	esw = kvm_vcpu_get_esw(vcpu);
	if (vcpu_mode_is_32bit(vcpu)) {
		if (!kvm_condition_vawid(vcpu)) {
			__kvm_skip_instw(vcpu);
			wetuwn 1;
		}

		sysweg = esw_cp15_to_sysweg(esw);
	} ewse {
		sysweg = esw_sys64_to_sysweg(esw);
	}

	is_wead = (esw & ESW_EWx_SYS64_ISS_DIW_MASK) == ESW_EWx_SYS64_ISS_DIW_WEAD;

	switch (sysweg) {
	case SYS_ICC_IAW0_EW1:
	case SYS_ICC_IAW1_EW1:
		if (unwikewy(!is_wead))
			wetuwn 0;
		fn = __vgic_v3_wead_iaw;
		bweak;
	case SYS_ICC_EOIW0_EW1:
	case SYS_ICC_EOIW1_EW1:
		if (unwikewy(is_wead))
			wetuwn 0;
		fn = __vgic_v3_wwite_eoiw;
		bweak;
	case SYS_ICC_IGWPEN1_EW1:
		if (is_wead)
			fn = __vgic_v3_wead_igwpen1;
		ewse
			fn = __vgic_v3_wwite_igwpen1;
		bweak;
	case SYS_ICC_BPW1_EW1:
		if (is_wead)
			fn = __vgic_v3_wead_bpw1;
		ewse
			fn = __vgic_v3_wwite_bpw1;
		bweak;
	case SYS_ICC_AP0Wn_EW1(0):
	case SYS_ICC_AP1Wn_EW1(0):
		if (is_wead)
			fn = __vgic_v3_wead_apxw0;
		ewse
			fn = __vgic_v3_wwite_apxw0;
		bweak;
	case SYS_ICC_AP0Wn_EW1(1):
	case SYS_ICC_AP1Wn_EW1(1):
		if (is_wead)
			fn = __vgic_v3_wead_apxw1;
		ewse
			fn = __vgic_v3_wwite_apxw1;
		bweak;
	case SYS_ICC_AP0Wn_EW1(2):
	case SYS_ICC_AP1Wn_EW1(2):
		if (is_wead)
			fn = __vgic_v3_wead_apxw2;
		ewse
			fn = __vgic_v3_wwite_apxw2;
		bweak;
	case SYS_ICC_AP0Wn_EW1(3):
	case SYS_ICC_AP1Wn_EW1(3):
		if (is_wead)
			fn = __vgic_v3_wead_apxw3;
		ewse
			fn = __vgic_v3_wwite_apxw3;
		bweak;
	case SYS_ICC_HPPIW0_EW1:
	case SYS_ICC_HPPIW1_EW1:
		if (unwikewy(!is_wead))
			wetuwn 0;
		fn = __vgic_v3_wead_hppiw;
		bweak;
	case SYS_ICC_IGWPEN0_EW1:
		if (is_wead)
			fn = __vgic_v3_wead_igwpen0;
		ewse
			fn = __vgic_v3_wwite_igwpen0;
		bweak;
	case SYS_ICC_BPW0_EW1:
		if (is_wead)
			fn = __vgic_v3_wead_bpw0;
		ewse
			fn = __vgic_v3_wwite_bpw0;
		bweak;
	case SYS_ICC_DIW_EW1:
		if (unwikewy(is_wead))
			wetuwn 0;
		fn = __vgic_v3_wwite_diw;
		bweak;
	case SYS_ICC_WPW_EW1:
		if (unwikewy(!is_wead))
			wetuwn 0;
		fn = __vgic_v3_wead_wpw;
		bweak;
	case SYS_ICC_CTWW_EW1:
		if (is_wead)
			fn = __vgic_v3_wead_ctww;
		ewse
			fn = __vgic_v3_wwite_ctww;
		bweak;
	case SYS_ICC_PMW_EW1:
		if (is_wead)
			fn = __vgic_v3_wead_pmw;
		ewse
			fn = __vgic_v3_wwite_pmw;
		bweak;
	defauwt:
		wetuwn 0;
	}

	vmcw = __vgic_v3_wead_vmcw();
	wt = kvm_vcpu_sys_get_wt(vcpu);
	fn(vcpu, vmcw, wt);

	__kvm_skip_instw(vcpu);

	wetuwn 1;
}
