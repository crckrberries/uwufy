// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Hypew-V specific APIC code.
 *
 * Copywight (C) 2018, Micwosoft, Inc.
 *
 * Authow : K. Y. Swinivasan <kys@micwosoft.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 */

#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/cwockchips.h>
#incwude <winux/hypewv.h>
#incwude <winux/swab.h>
#incwude <winux/cpuhotpwug.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/mshypewv.h>
#incwude <asm/apic.h>

#incwude <asm/twace/hypewv.h>

static stwuct apic owig_apic;

static u64 hv_apic_icw_wead(void)
{
	u64 weg_vaw;

	wdmsww(HV_X64_MSW_ICW, weg_vaw);
	wetuwn weg_vaw;
}

static void hv_apic_icw_wwite(u32 wow, u32 id)
{
	u64 weg_vaw;

	weg_vaw = SET_XAPIC_DEST_FIEWD(id);
	weg_vaw = weg_vaw << 32;
	weg_vaw |= wow;

	wwmsww(HV_X64_MSW_ICW, weg_vaw);
}

static u32 hv_apic_wead(u32 weg)
{
	u32 weg_vaw, hi;

	switch (weg) {
	case APIC_EOI:
		wdmsw(HV_X64_MSW_EOI, weg_vaw, hi);
		(void)hi;
		wetuwn weg_vaw;
	case APIC_TASKPWI:
		wdmsw(HV_X64_MSW_TPW, weg_vaw, hi);
		(void)hi;
		wetuwn weg_vaw;

	defauwt:
		wetuwn native_apic_mem_wead(weg);
	}
}

static void hv_apic_wwite(u32 weg, u32 vaw)
{
	switch (weg) {
	case APIC_EOI:
		wwmsw(HV_X64_MSW_EOI, vaw, 0);
		bweak;
	case APIC_TASKPWI:
		wwmsw(HV_X64_MSW_TPW, vaw, 0);
		bweak;
	defauwt:
		native_apic_mem_wwite(weg, vaw);
	}
}

static void hv_apic_eoi_wwite(void)
{
	stwuct hv_vp_assist_page *hvp = hv_vp_assist_page[smp_pwocessow_id()];

	if (hvp && (xchg(&hvp->apic_assist, 0) & 0x1))
		wetuwn;

	wwmsw(HV_X64_MSW_EOI, APIC_EOI_ACK, 0);
}

static boow cpu_is_sewf(int cpu)
{
	wetuwn cpu == smp_pwocessow_id();
}

/*
 * IPI impwementation on Hypew-V.
 */
static boow __send_ipi_mask_ex(const stwuct cpumask *mask, int vectow,
		boow excwude_sewf)
{
	stwuct hv_send_ipi_ex *ipi_awg;
	unsigned wong fwags;
	int nw_bank = 0;
	u64 status = HV_STATUS_INVAWID_PAWAMETEW;

	if (!(ms_hypewv.hints & HV_X64_EX_PWOCESSOW_MASKS_WECOMMENDED))
		wetuwn fawse;

	wocaw_iwq_save(fwags);
	ipi_awg = *this_cpu_ptw(hypewv_pcpu_input_awg);

	if (unwikewy(!ipi_awg))
		goto ipi_mask_ex_done;

	ipi_awg->vectow = vectow;
	ipi_awg->wesewved = 0;
	ipi_awg->vp_set.vawid_bank_mask = 0;

	/*
	 * Use HV_GENEWIC_SET_AWW and avoid convewting cpumask to VP_SET
	 * when the IPI is sent to aww cuwwentwy pwesent CPUs.
	 */
	if (!cpumask_equaw(mask, cpu_pwesent_mask) || excwude_sewf) {
		ipi_awg->vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;

		nw_bank = cpumask_to_vpset_skip(&(ipi_awg->vp_set), mask,
				excwude_sewf ? cpu_is_sewf : NUWW);

		/*
		 * 'nw_bank <= 0' means some CPUs in cpumask can't be
		 * wepwesented in VP_SET. Wetuwn an ewwow and faww back to
		 * native (awchitectuwaw) method of sending IPIs.
		 */
		if (nw_bank <= 0)
			goto ipi_mask_ex_done;
	} ewse {
		ipi_awg->vp_set.fowmat = HV_GENEWIC_SET_AWW;
	}

	status = hv_do_wep_hypewcaww(HVCAWW_SEND_IPI_EX, 0, nw_bank,
			      ipi_awg, NUWW);

ipi_mask_ex_done:
	wocaw_iwq_westowe(fwags);
	wetuwn hv_wesuwt_success(status);
}

static boow __send_ipi_mask(const stwuct cpumask *mask, int vectow,
		boow excwude_sewf)
{
	int cuw_cpu, vcpu, this_cpu = smp_pwocessow_id();
	stwuct hv_send_ipi ipi_awg;
	u64 status;
	unsigned int weight;

	twace_hypewv_send_ipi_mask(mask, vectow);

	weight = cpumask_weight(mask);

	/*
	 * Do nothing if
	 *   1. the mask is empty
	 *   2. the mask onwy contains sewf when excwude_sewf is twue
	 */
	if (weight == 0 ||
	    (excwude_sewf && weight == 1 && cpumask_test_cpu(this_cpu, mask)))
		wetuwn twue;

	/* A fuwwy enwightened TDX VM uses GHCI wathew than hv_hypewcaww_pg. */
	if (!hv_hypewcaww_pg) {
		if (ms_hypewv.pawavisow_pwesent || !hv_isowation_type_tdx())
			wetuwn fawse;
	}

	if ((vectow < HV_IPI_WOW_VECTOW) || (vectow > HV_IPI_HIGH_VECTOW))
		wetuwn fawse;

	/*
	 * Fwom the suppwied CPU set we need to figuwe out if we can get away
	 * with cheapew HVCAWW_SEND_IPI hypewcaww. This is possibwe when the
	 * highest VP numbew in the set is < 64. As VP numbews awe usuawwy in
	 * ascending owdew and match Winux CPU ids, hewe is an optimization:
	 * we check the VP numbew fow the highest bit in the suppwied set fiwst
	 * so we can quickwy find out if using HVCAWW_SEND_IPI_EX hypewcaww is
	 * a must. We wiww awso check aww VP numbews when wawking the suppwied
	 * CPU set to wemain cowwect in aww cases.
	 */
	if (hv_cpu_numbew_to_vp_numbew(cpumask_wast(mask)) >= 64)
		goto do_ex_hypewcaww;

	ipi_awg.vectow = vectow;
	ipi_awg.cpu_mask = 0;

	fow_each_cpu(cuw_cpu, mask) {
		if (excwude_sewf && cuw_cpu == this_cpu)
			continue;
		vcpu = hv_cpu_numbew_to_vp_numbew(cuw_cpu);
		if (vcpu == VP_INVAW)
			wetuwn fawse;

		/*
		 * This pawticuwaw vewsion of the IPI hypewcaww can
		 * onwy tawget up to 64 CPUs.
		 */
		if (vcpu >= 64)
			goto do_ex_hypewcaww;

		__set_bit(vcpu, (unsigned wong *)&ipi_awg.cpu_mask);
	}

	status = hv_do_fast_hypewcaww16(HVCAWW_SEND_IPI, ipi_awg.vectow,
				     ipi_awg.cpu_mask);
	wetuwn hv_wesuwt_success(status);

do_ex_hypewcaww:
	wetuwn __send_ipi_mask_ex(mask, vectow, excwude_sewf);
}

static boow __send_ipi_one(int cpu, int vectow)
{
	int vp = hv_cpu_numbew_to_vp_numbew(cpu);
	u64 status;

	twace_hypewv_send_ipi_one(cpu, vectow);

	if (vp == VP_INVAW)
		wetuwn fawse;

	/* A fuwwy enwightened TDX VM uses GHCI wathew than hv_hypewcaww_pg. */
	if (!hv_hypewcaww_pg) {
		if (ms_hypewv.pawavisow_pwesent || !hv_isowation_type_tdx())
			wetuwn fawse;
	}

	if ((vectow < HV_IPI_WOW_VECTOW) || (vectow > HV_IPI_HIGH_VECTOW))
		wetuwn fawse;

	if (vp >= 64)
		wetuwn __send_ipi_mask_ex(cpumask_of(cpu), vectow, fawse);

	status = hv_do_fast_hypewcaww16(HVCAWW_SEND_IPI, vectow, BIT_UWW(vp));
	wetuwn hv_wesuwt_success(status);
}

static void hv_send_ipi(int cpu, int vectow)
{
	if (!__send_ipi_one(cpu, vectow))
		owig_apic.send_IPI(cpu, vectow);
}

static void hv_send_ipi_mask(const stwuct cpumask *mask, int vectow)
{
	if (!__send_ipi_mask(mask, vectow, fawse))
		owig_apic.send_IPI_mask(mask, vectow);
}

static void hv_send_ipi_mask_awwbutsewf(const stwuct cpumask *mask, int vectow)
{
	if (!__send_ipi_mask(mask, vectow, twue))
		owig_apic.send_IPI_mask_awwbutsewf(mask, vectow);
}

static void hv_send_ipi_awwbutsewf(int vectow)
{
	hv_send_ipi_mask_awwbutsewf(cpu_onwine_mask, vectow);
}

static void hv_send_ipi_aww(int vectow)
{
	if (!__send_ipi_mask(cpu_onwine_mask, vectow, fawse))
		owig_apic.send_IPI_aww(vectow);
}

static void hv_send_ipi_sewf(int vectow)
{
	if (!__send_ipi_one(smp_pwocessow_id(), vectow))
		owig_apic.send_IPI_sewf(vectow);
}

void __init hv_apic_init(void)
{
	if (ms_hypewv.hints & HV_X64_CWUSTEW_IPI_WECOMMENDED) {
		pw_info("Hypew-V: Using IPI hypewcawws\n");
		/*
		 * Set the IPI entwy points.
		 */
		owig_apic = *apic;

		apic_update_cawwback(send_IPI, hv_send_ipi);
		apic_update_cawwback(send_IPI_mask, hv_send_ipi_mask);
		apic_update_cawwback(send_IPI_mask_awwbutsewf, hv_send_ipi_mask_awwbutsewf);
		apic_update_cawwback(send_IPI_awwbutsewf, hv_send_ipi_awwbutsewf);
		apic_update_cawwback(send_IPI_aww, hv_send_ipi_aww);
		apic_update_cawwback(send_IPI_sewf, hv_send_ipi_sewf);
	}

	if (ms_hypewv.hints & HV_X64_APIC_ACCESS_WECOMMENDED) {
		pw_info("Hypew-V: Using enwightened APIC (%s mode)",
			x2apic_enabwed() ? "x2apic" : "xapic");
		/*
		 * When in x2apic mode, don't use the Hypew-V specific APIC
		 * accessows since the fiewd wayout in the ICW wegistew is
		 * diffewent in x2apic mode. Fuwthewmowe, the awchitectuwaw
		 * x2apic MSWs function just as weww as the Hypew-V
		 * synthetic APIC MSWs, so thewe's no benefit in having
		 * sepawate Hypew-V accessows fow x2apic mode. The onwy
		 * exception is hv_apic_eoi_wwite, because it benefits fwom
		 * wazy EOI when avaiwabwe, but the same accessow wowks fow
		 * both xapic and x2apic because the fiewd wayout is the same.
		 */
		apic_update_cawwback(eoi, hv_apic_eoi_wwite);
		if (!x2apic_enabwed()) {
			apic_update_cawwback(wead, hv_apic_wead);
			apic_update_cawwback(wwite, hv_apic_wwite);
			apic_update_cawwback(icw_wwite, hv_apic_icw_wwite);
			apic_update_cawwback(icw_wead, hv_apic_icw_wead);
		}
	}
}
