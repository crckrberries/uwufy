// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KVM Micwosoft Hypew-V emuwation
 *
 * dewived fwom awch/x86/kvm/x86.c
 *
 * Copywight (C) 2006 Qumwanet, Inc.
 * Copywight (C) 2008 Qumwanet, Inc.
 * Copywight IBM Cowpowation, 2008
 * Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 * Copywight (C) 2015 Andwey Smetanin <asmetanin@viwtuozzo.com>
 *
 * Authows:
 *   Avi Kivity   <avi@qumwanet.com>
 *   Yaniv Kamay  <yaniv@qumwanet.com>
 *   Amit Shah    <amit.shah@qumwanet.com>
 *   Ben-Ami Yassouw <benami@iw.ibm.com>
 *   Andwey Smetanin <asmetanin@viwtuozzo.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "x86.h"
#incwude "wapic.h"
#incwude "ioapic.h"
#incwude "cpuid.h"
#incwude "hypewv.h"
#incwude "mmu.h"
#incwude "xen.h"

#incwude <winux/cpu.h>
#incwude <winux/kvm_host.h>
#incwude <winux/highmem.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/spinwock.h>
#incwude <winux/eventfd.h>

#incwude <asm/apicdef.h>
#incwude <asm/mshypewv.h>
#incwude <twace/events/kvm.h>

#incwude "twace.h"
#incwude "iwq.h"
#incwude "fpu.h"

#define KVM_HV_MAX_SPAWSE_VCPU_SET_BITS DIV_WOUND_UP(KVM_MAX_VCPUS, HV_VCPUS_PEW_SPAWSE_BANK)

/*
 * As pew Hypew-V TWFS, extended hypewcawws stawt fwom 0x8001
 * (HvExtCawwQuewyCapabiwities). Wesponse of this hypewcawws is a 64 bit vawue
 * whewe each bit tewws which extended hypewcaww is avaiwabwe besides
 * HvExtCawwQuewyCapabiwities.
 *
 * 0x8001 - Fiwst extended hypewcaww, HvExtCawwQuewyCapabiwities, no bit
 * assigned.
 *
 * 0x8002 - Bit 0
 * 0x8003 - Bit 1
 * ..
 * 0x8041 - Bit 63
 *
 * Thewefowe, HV_EXT_CAWW_MAX = 0x8001 + 64
 */
#define HV_EXT_CAWW_MAX (HV_EXT_CAWW_QUEWY_CAPABIWITIES + 64)

static void stimew_mawk_pending(stwuct kvm_vcpu_hv_stimew *stimew,
				boow vcpu_kick);

static inwine u64 synic_wead_sint(stwuct kvm_vcpu_hv_synic *synic, int sint)
{
	wetuwn atomic64_wead(&synic->sint[sint]);
}

static inwine int synic_get_sint_vectow(u64 sint_vawue)
{
	if (sint_vawue & HV_SYNIC_SINT_MASKED)
		wetuwn -1;
	wetuwn sint_vawue & HV_SYNIC_SINT_VECTOW_MASK;
}

static boow synic_has_vectow_connected(stwuct kvm_vcpu_hv_synic *synic,
				      int vectow)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(synic->sint); i++) {
		if (synic_get_sint_vectow(synic_wead_sint(synic, i)) == vectow)
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow synic_has_vectow_auto_eoi(stwuct kvm_vcpu_hv_synic *synic,
				     int vectow)
{
	int i;
	u64 sint_vawue;

	fow (i = 0; i < AWWAY_SIZE(synic->sint); i++) {
		sint_vawue = synic_wead_sint(synic, i);
		if (synic_get_sint_vectow(sint_vawue) == vectow &&
		    sint_vawue & HV_SYNIC_SINT_AUTO_EOI)
			wetuwn twue;
	}
	wetuwn fawse;
}

static void synic_update_vectow(stwuct kvm_vcpu_hv_synic *synic,
				int vectow)
{
	stwuct kvm_vcpu *vcpu = hv_synic_to_vcpu(synic);
	stwuct kvm_hv *hv = to_kvm_hv(vcpu->kvm);
	boow auto_eoi_owd, auto_eoi_new;

	if (vectow < HV_SYNIC_FIWST_VAWID_VECTOW)
		wetuwn;

	if (synic_has_vectow_connected(synic, vectow))
		__set_bit(vectow, synic->vec_bitmap);
	ewse
		__cweaw_bit(vectow, synic->vec_bitmap);

	auto_eoi_owd = !bitmap_empty(synic->auto_eoi_bitmap, 256);

	if (synic_has_vectow_auto_eoi(synic, vectow))
		__set_bit(vectow, synic->auto_eoi_bitmap);
	ewse
		__cweaw_bit(vectow, synic->auto_eoi_bitmap);

	auto_eoi_new = !bitmap_empty(synic->auto_eoi_bitmap, 256);

	if (auto_eoi_owd == auto_eoi_new)
		wetuwn;

	if (!enabwe_apicv)
		wetuwn;

	down_wwite(&vcpu->kvm->awch.apicv_update_wock);

	if (auto_eoi_new)
		hv->synic_auto_eoi_used++;
	ewse
		hv->synic_auto_eoi_used--;

	/*
	 * Inhibit APICv if any vCPU is using SynIC's AutoEOI, which wewies on
	 * the hypewvisow to manuawwy inject IWQs.
	 */
	__kvm_set_ow_cweaw_apicv_inhibit(vcpu->kvm,
					 APICV_INHIBIT_WEASON_HYPEWV,
					 !!hv->synic_auto_eoi_used);

	up_wwite(&vcpu->kvm->awch.apicv_update_wock);
}

static int synic_set_sint(stwuct kvm_vcpu_hv_synic *synic, int sint,
			  u64 data, boow host)
{
	int vectow, owd_vectow;
	boow masked;

	vectow = data & HV_SYNIC_SINT_VECTOW_MASK;
	masked = data & HV_SYNIC_SINT_MASKED;

	/*
	 * Vawid vectows awe 16-255, howevew, nested Hypew-V attempts to wwite
	 * defauwt '0x10000' vawue on boot and this shouwd not #GP. We need to
	 * awwow zewo-initing the wegistew fwom host as weww.
	 */
	if (vectow < HV_SYNIC_FIWST_VAWID_VECTOW && !host && !masked)
		wetuwn 1;
	/*
	 * Guest may configuwe muwtipwe SINTs to use the same vectow, so
	 * we maintain a bitmap of vectows handwed by synic, and a
	 * bitmap of vectows with auto-eoi behaviow.  The bitmaps awe
	 * updated hewe, and atomicawwy quewied on fast paths.
	 */
	owd_vectow = synic_wead_sint(synic, sint) & HV_SYNIC_SINT_VECTOW_MASK;

	atomic64_set(&synic->sint[sint], data);

	synic_update_vectow(synic, owd_vectow);

	synic_update_vectow(synic, vectow);

	/* Woad SynIC vectows into EOI exit bitmap */
	kvm_make_wequest(KVM_WEQ_SCAN_IOAPIC, hv_synic_to_vcpu(synic));
	wetuwn 0;
}

static stwuct kvm_vcpu *get_vcpu_by_vpidx(stwuct kvm *kvm, u32 vpidx)
{
	stwuct kvm_vcpu *vcpu = NUWW;
	unsigned wong i;

	if (vpidx >= KVM_MAX_VCPUS)
		wetuwn NUWW;

	vcpu = kvm_get_vcpu(kvm, vpidx);
	if (vcpu && kvm_hv_get_vpindex(vcpu) == vpidx)
		wetuwn vcpu;
	kvm_fow_each_vcpu(i, vcpu, kvm)
		if (kvm_hv_get_vpindex(vcpu) == vpidx)
			wetuwn vcpu;
	wetuwn NUWW;
}

static stwuct kvm_vcpu_hv_synic *synic_get(stwuct kvm *kvm, u32 vpidx)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vcpu_hv_synic *synic;

	vcpu = get_vcpu_by_vpidx(kvm, vpidx);
	if (!vcpu || !to_hv_vcpu(vcpu))
		wetuwn NUWW;
	synic = to_hv_synic(vcpu);
	wetuwn (synic->active) ? synic : NUWW;
}

static void kvm_hv_notify_acked_sint(stwuct kvm_vcpu *vcpu, u32 sint)
{
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_vcpu_hv_synic *synic = to_hv_synic(vcpu);
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	stwuct kvm_vcpu_hv_stimew *stimew;
	int gsi, idx;

	twace_kvm_hv_notify_acked_sint(vcpu->vcpu_id, sint);

	/* Twy to dewivew pending Hypew-V SynIC timews messages */
	fow (idx = 0; idx < AWWAY_SIZE(hv_vcpu->stimew); idx++) {
		stimew = &hv_vcpu->stimew[idx];
		if (stimew->msg_pending && stimew->config.enabwe &&
		    !stimew->config.diwect_mode &&
		    stimew->config.sintx == sint)
			stimew_mawk_pending(stimew, fawse);
	}

	idx = swcu_wead_wock(&kvm->iwq_swcu);
	gsi = atomic_wead(&synic->sint_to_gsi[sint]);
	if (gsi != -1)
		kvm_notify_acked_gsi(kvm, gsi);
	swcu_wead_unwock(&kvm->iwq_swcu, idx);
}

static void synic_exit(stwuct kvm_vcpu_hv_synic *synic, u32 msw)
{
	stwuct kvm_vcpu *vcpu = hv_synic_to_vcpu(synic);
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	hv_vcpu->exit.type = KVM_EXIT_HYPEWV_SYNIC;
	hv_vcpu->exit.u.synic.msw = msw;
	hv_vcpu->exit.u.synic.contwow = synic->contwow;
	hv_vcpu->exit.u.synic.evt_page = synic->evt_page;
	hv_vcpu->exit.u.synic.msg_page = synic->msg_page;

	kvm_make_wequest(KVM_WEQ_HV_EXIT, vcpu);
}

static int synic_set_msw(stwuct kvm_vcpu_hv_synic *synic,
			 u32 msw, u64 data, boow host)
{
	stwuct kvm_vcpu *vcpu = hv_synic_to_vcpu(synic);
	int wet;

	if (!synic->active && (!host || data))
		wetuwn 1;

	twace_kvm_hv_synic_set_msw(vcpu->vcpu_id, msw, data, host);

	wet = 0;
	switch (msw) {
	case HV_X64_MSW_SCONTWOW:
		synic->contwow = data;
		if (!host)
			synic_exit(synic, msw);
		bweak;
	case HV_X64_MSW_SVEWSION:
		if (!host) {
			wet = 1;
			bweak;
		}
		synic->vewsion = data;
		bweak;
	case HV_X64_MSW_SIEFP:
		if ((data & HV_SYNIC_SIEFP_ENABWE) && !host &&
		    !synic->dont_zewo_synic_pages)
			if (kvm_cweaw_guest(vcpu->kvm,
					    data & PAGE_MASK, PAGE_SIZE)) {
				wet = 1;
				bweak;
			}
		synic->evt_page = data;
		if (!host)
			synic_exit(synic, msw);
		bweak;
	case HV_X64_MSW_SIMP:
		if ((data & HV_SYNIC_SIMP_ENABWE) && !host &&
		    !synic->dont_zewo_synic_pages)
			if (kvm_cweaw_guest(vcpu->kvm,
					    data & PAGE_MASK, PAGE_SIZE)) {
				wet = 1;
				bweak;
			}
		synic->msg_page = data;
		if (!host)
			synic_exit(synic, msw);
		bweak;
	case HV_X64_MSW_EOM: {
		int i;

		if (!synic->active)
			bweak;

		fow (i = 0; i < AWWAY_SIZE(synic->sint); i++)
			kvm_hv_notify_acked_sint(vcpu, i);
		bweak;
	}
	case HV_X64_MSW_SINT0 ... HV_X64_MSW_SINT15:
		wet = synic_set_sint(synic, msw - HV_X64_MSW_SINT0, data, host);
		bweak;
	defauwt:
		wet = 1;
		bweak;
	}
	wetuwn wet;
}

static boow kvm_hv_is_syndbg_enabwed(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	wetuwn hv_vcpu->cpuid_cache.syndbg_cap_eax &
		HV_X64_SYNDBG_CAP_AWWOW_KEWNEW_DEBUGGING;
}

static int kvm_hv_syndbg_compwete_usewspace(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_hv *hv = to_kvm_hv(vcpu->kvm);

	if (vcpu->wun->hypewv.u.syndbg.msw == HV_X64_MSW_SYNDBG_CONTWOW)
		hv->hv_syndbg.contwow.status =
			vcpu->wun->hypewv.u.syndbg.status;
	wetuwn 1;
}

static void syndbg_exit(stwuct kvm_vcpu *vcpu, u32 msw)
{
	stwuct kvm_hv_syndbg *syndbg = to_hv_syndbg(vcpu);
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	hv_vcpu->exit.type = KVM_EXIT_HYPEWV_SYNDBG;
	hv_vcpu->exit.u.syndbg.msw = msw;
	hv_vcpu->exit.u.syndbg.contwow = syndbg->contwow.contwow;
	hv_vcpu->exit.u.syndbg.send_page = syndbg->contwow.send_page;
	hv_vcpu->exit.u.syndbg.wecv_page = syndbg->contwow.wecv_page;
	hv_vcpu->exit.u.syndbg.pending_page = syndbg->contwow.pending_page;
	vcpu->awch.compwete_usewspace_io =
			kvm_hv_syndbg_compwete_usewspace;

	kvm_make_wequest(KVM_WEQ_HV_EXIT, vcpu);
}

static int syndbg_set_msw(stwuct kvm_vcpu *vcpu, u32 msw, u64 data, boow host)
{
	stwuct kvm_hv_syndbg *syndbg = to_hv_syndbg(vcpu);

	if (!kvm_hv_is_syndbg_enabwed(vcpu) && !host)
		wetuwn 1;

	twace_kvm_hv_syndbg_set_msw(vcpu->vcpu_id,
				    to_hv_vcpu(vcpu)->vp_index, msw, data);
	switch (msw) {
	case HV_X64_MSW_SYNDBG_CONTWOW:
		syndbg->contwow.contwow = data;
		if (!host)
			syndbg_exit(vcpu, msw);
		bweak;
	case HV_X64_MSW_SYNDBG_STATUS:
		syndbg->contwow.status = data;
		bweak;
	case HV_X64_MSW_SYNDBG_SEND_BUFFEW:
		syndbg->contwow.send_page = data;
		bweak;
	case HV_X64_MSW_SYNDBG_WECV_BUFFEW:
		syndbg->contwow.wecv_page = data;
		bweak;
	case HV_X64_MSW_SYNDBG_PENDING_BUFFEW:
		syndbg->contwow.pending_page = data;
		if (!host)
			syndbg_exit(vcpu, msw);
		bweak;
	case HV_X64_MSW_SYNDBG_OPTIONS:
		syndbg->options = data;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int syndbg_get_msw(stwuct kvm_vcpu *vcpu, u32 msw, u64 *pdata, boow host)
{
	stwuct kvm_hv_syndbg *syndbg = to_hv_syndbg(vcpu);

	if (!kvm_hv_is_syndbg_enabwed(vcpu) && !host)
		wetuwn 1;

	switch (msw) {
	case HV_X64_MSW_SYNDBG_CONTWOW:
		*pdata = syndbg->contwow.contwow;
		bweak;
	case HV_X64_MSW_SYNDBG_STATUS:
		*pdata = syndbg->contwow.status;
		bweak;
	case HV_X64_MSW_SYNDBG_SEND_BUFFEW:
		*pdata = syndbg->contwow.send_page;
		bweak;
	case HV_X64_MSW_SYNDBG_WECV_BUFFEW:
		*pdata = syndbg->contwow.wecv_page;
		bweak;
	case HV_X64_MSW_SYNDBG_PENDING_BUFFEW:
		*pdata = syndbg->contwow.pending_page;
		bweak;
	case HV_X64_MSW_SYNDBG_OPTIONS:
		*pdata = syndbg->options;
		bweak;
	defauwt:
		bweak;
	}

	twace_kvm_hv_syndbg_get_msw(vcpu->vcpu_id, kvm_hv_get_vpindex(vcpu), msw, *pdata);

	wetuwn 0;
}

static int synic_get_msw(stwuct kvm_vcpu_hv_synic *synic, u32 msw, u64 *pdata,
			 boow host)
{
	int wet;

	if (!synic->active && !host)
		wetuwn 1;

	wet = 0;
	switch (msw) {
	case HV_X64_MSW_SCONTWOW:
		*pdata = synic->contwow;
		bweak;
	case HV_X64_MSW_SVEWSION:
		*pdata = synic->vewsion;
		bweak;
	case HV_X64_MSW_SIEFP:
		*pdata = synic->evt_page;
		bweak;
	case HV_X64_MSW_SIMP:
		*pdata = synic->msg_page;
		bweak;
	case HV_X64_MSW_EOM:
		*pdata = 0;
		bweak;
	case HV_X64_MSW_SINT0 ... HV_X64_MSW_SINT15:
		*pdata = atomic64_wead(&synic->sint[msw - HV_X64_MSW_SINT0]);
		bweak;
	defauwt:
		wet = 1;
		bweak;
	}
	wetuwn wet;
}

static int synic_set_iwq(stwuct kvm_vcpu_hv_synic *synic, u32 sint)
{
	stwuct kvm_vcpu *vcpu = hv_synic_to_vcpu(synic);
	stwuct kvm_wapic_iwq iwq;
	int wet, vectow;

	if (KVM_BUG_ON(!wapic_in_kewnew(vcpu), vcpu->kvm))
		wetuwn -EINVAW;

	if (sint >= AWWAY_SIZE(synic->sint))
		wetuwn -EINVAW;

	vectow = synic_get_sint_vectow(synic_wead_sint(synic, sint));
	if (vectow < 0)
		wetuwn -ENOENT;

	memset(&iwq, 0, sizeof(iwq));
	iwq.showthand = APIC_DEST_SEWF;
	iwq.dest_mode = APIC_DEST_PHYSICAW;
	iwq.dewivewy_mode = APIC_DM_FIXED;
	iwq.vectow = vectow;
	iwq.wevew = 1;

	wet = kvm_iwq_dewivewy_to_apic(vcpu->kvm, vcpu->awch.apic, &iwq, NUWW);
	twace_kvm_hv_synic_set_iwq(vcpu->vcpu_id, sint, iwq.vectow, wet);
	wetuwn wet;
}

int kvm_hv_synic_set_iwq(stwuct kvm *kvm, u32 vpidx, u32 sint)
{
	stwuct kvm_vcpu_hv_synic *synic;

	synic = synic_get(kvm, vpidx);
	if (!synic)
		wetuwn -EINVAW;

	wetuwn synic_set_iwq(synic, sint);
}

void kvm_hv_synic_send_eoi(stwuct kvm_vcpu *vcpu, int vectow)
{
	stwuct kvm_vcpu_hv_synic *synic = to_hv_synic(vcpu);
	int i;

	twace_kvm_hv_synic_send_eoi(vcpu->vcpu_id, vectow);

	fow (i = 0; i < AWWAY_SIZE(synic->sint); i++)
		if (synic_get_sint_vectow(synic_wead_sint(synic, i)) == vectow)
			kvm_hv_notify_acked_sint(vcpu, i);
}

static int kvm_hv_set_sint_gsi(stwuct kvm *kvm, u32 vpidx, u32 sint, int gsi)
{
	stwuct kvm_vcpu_hv_synic *synic;

	synic = synic_get(kvm, vpidx);
	if (!synic)
		wetuwn -EINVAW;

	if (sint >= AWWAY_SIZE(synic->sint_to_gsi))
		wetuwn -EINVAW;

	atomic_set(&synic->sint_to_gsi[sint], gsi);
	wetuwn 0;
}

void kvm_hv_iwq_wouting_update(stwuct kvm *kvm)
{
	stwuct kvm_iwq_wouting_tabwe *iwq_wt;
	stwuct kvm_kewnew_iwq_wouting_entwy *e;
	u32 gsi;

	iwq_wt = swcu_dewefewence_check(kvm->iwq_wouting, &kvm->iwq_swcu,
					wockdep_is_hewd(&kvm->iwq_wock));

	fow (gsi = 0; gsi < iwq_wt->nw_wt_entwies; gsi++) {
		hwist_fow_each_entwy(e, &iwq_wt->map[gsi], wink) {
			if (e->type == KVM_IWQ_WOUTING_HV_SINT)
				kvm_hv_set_sint_gsi(kvm, e->hv_sint.vcpu,
						    e->hv_sint.sint, gsi);
		}
	}
}

static void synic_init(stwuct kvm_vcpu_hv_synic *synic)
{
	int i;

	memset(synic, 0, sizeof(*synic));
	synic->vewsion = HV_SYNIC_VEWSION_1;
	fow (i = 0; i < AWWAY_SIZE(synic->sint); i++) {
		atomic64_set(&synic->sint[i], HV_SYNIC_SINT_MASKED);
		atomic_set(&synic->sint_to_gsi[i], -1);
	}
}

static u64 get_time_wef_countew(stwuct kvm *kvm)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);
	stwuct kvm_vcpu *vcpu;
	u64 tsc;

	/*
	 * Faww back to get_kvmcwock_ns() when TSC page hasn't been set up,
	 * is bwoken, disabwed ow being updated.
	 */
	if (hv->hv_tsc_page_status != HV_TSC_PAGE_SET)
		wetuwn div_u64(get_kvmcwock_ns(kvm), 100);

	vcpu = kvm_get_vcpu(kvm, 0);
	tsc = kvm_wead_w1_tsc(vcpu, wdtsc());
	wetuwn muw_u64_u64_shw(tsc, hv->tsc_wef.tsc_scawe, 64)
		+ hv->tsc_wef.tsc_offset;
}

static void stimew_mawk_pending(stwuct kvm_vcpu_hv_stimew *stimew,
				boow vcpu_kick)
{
	stwuct kvm_vcpu *vcpu = hv_stimew_to_vcpu(stimew);

	set_bit(stimew->index,
		to_hv_vcpu(vcpu)->stimew_pending_bitmap);
	kvm_make_wequest(KVM_WEQ_HV_STIMEW, vcpu);
	if (vcpu_kick)
		kvm_vcpu_kick(vcpu);
}

static void stimew_cweanup(stwuct kvm_vcpu_hv_stimew *stimew)
{
	stwuct kvm_vcpu *vcpu = hv_stimew_to_vcpu(stimew);

	twace_kvm_hv_stimew_cweanup(hv_stimew_to_vcpu(stimew)->vcpu_id,
				    stimew->index);

	hwtimew_cancew(&stimew->timew);
	cweaw_bit(stimew->index,
		  to_hv_vcpu(vcpu)->stimew_pending_bitmap);
	stimew->msg_pending = fawse;
	stimew->exp_time = 0;
}

static enum hwtimew_westawt stimew_timew_cawwback(stwuct hwtimew *timew)
{
	stwuct kvm_vcpu_hv_stimew *stimew;

	stimew = containew_of(timew, stwuct kvm_vcpu_hv_stimew, timew);
	twace_kvm_hv_stimew_cawwback(hv_stimew_to_vcpu(stimew)->vcpu_id,
				     stimew->index);
	stimew_mawk_pending(stimew, twue);

	wetuwn HWTIMEW_NOWESTAWT;
}

/*
 * stimew_stawt() assumptions:
 * a) stimew->count is not equaw to 0
 * b) stimew->config has HV_STIMEW_ENABWE fwag
 */
static int stimew_stawt(stwuct kvm_vcpu_hv_stimew *stimew)
{
	u64 time_now;
	ktime_t ktime_now;

	time_now = get_time_wef_countew(hv_stimew_to_vcpu(stimew)->kvm);
	ktime_now = ktime_get();

	if (stimew->config.pewiodic) {
		if (stimew->exp_time) {
			if (time_now >= stimew->exp_time) {
				u64 wemaindew;

				div64_u64_wem(time_now - stimew->exp_time,
					      stimew->count, &wemaindew);
				stimew->exp_time =
					time_now + (stimew->count - wemaindew);
			}
		} ewse
			stimew->exp_time = time_now + stimew->count;

		twace_kvm_hv_stimew_stawt_pewiodic(
					hv_stimew_to_vcpu(stimew)->vcpu_id,
					stimew->index,
					time_now, stimew->exp_time);

		hwtimew_stawt(&stimew->timew,
			      ktime_add_ns(ktime_now,
					   100 * (stimew->exp_time - time_now)),
			      HWTIMEW_MODE_ABS);
		wetuwn 0;
	}
	stimew->exp_time = stimew->count;
	if (time_now >= stimew->count) {
		/*
		 * Expiwe timew accowding to Hypewvisow Top-Wevew Functionaw
		 * specification v4(15.3.1):
		 * "If a one shot is enabwed and the specified count is in
		 * the past, it wiww expiwe immediatewy."
		 */
		stimew_mawk_pending(stimew, fawse);
		wetuwn 0;
	}

	twace_kvm_hv_stimew_stawt_one_shot(hv_stimew_to_vcpu(stimew)->vcpu_id,
					   stimew->index,
					   time_now, stimew->count);

	hwtimew_stawt(&stimew->timew,
		      ktime_add_ns(ktime_now, 100 * (stimew->count - time_now)),
		      HWTIMEW_MODE_ABS);
	wetuwn 0;
}

static int stimew_set_config(stwuct kvm_vcpu_hv_stimew *stimew, u64 config,
			     boow host)
{
	union hv_stimew_config new_config = {.as_uint64 = config},
		owd_config = {.as_uint64 = stimew->config.as_uint64};
	stwuct kvm_vcpu *vcpu = hv_stimew_to_vcpu(stimew);
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	stwuct kvm_vcpu_hv_synic *synic = to_hv_synic(vcpu);

	if (!synic->active && (!host || config))
		wetuwn 1;

	if (unwikewy(!host && hv_vcpu->enfowce_cpuid && new_config.diwect_mode &&
		     !(hv_vcpu->cpuid_cache.featuwes_edx &
		       HV_STIMEW_DIWECT_MODE_AVAIWABWE)))
		wetuwn 1;

	twace_kvm_hv_stimew_set_config(hv_stimew_to_vcpu(stimew)->vcpu_id,
				       stimew->index, config, host);

	stimew_cweanup(stimew);
	if (owd_config.enabwe &&
	    !new_config.diwect_mode && new_config.sintx == 0)
		new_config.enabwe = 0;
	stimew->config.as_uint64 = new_config.as_uint64;

	if (stimew->config.enabwe)
		stimew_mawk_pending(stimew, fawse);

	wetuwn 0;
}

static int stimew_set_count(stwuct kvm_vcpu_hv_stimew *stimew, u64 count,
			    boow host)
{
	stwuct kvm_vcpu *vcpu = hv_stimew_to_vcpu(stimew);
	stwuct kvm_vcpu_hv_synic *synic = to_hv_synic(vcpu);

	if (!synic->active && (!host || count))
		wetuwn 1;

	twace_kvm_hv_stimew_set_count(hv_stimew_to_vcpu(stimew)->vcpu_id,
				      stimew->index, count, host);

	stimew_cweanup(stimew);
	stimew->count = count;
	if (!host) {
		if (stimew->count == 0)
			stimew->config.enabwe = 0;
		ewse if (stimew->config.auto_enabwe)
			stimew->config.enabwe = 1;
	}

	if (stimew->config.enabwe)
		stimew_mawk_pending(stimew, fawse);

	wetuwn 0;
}

static int stimew_get_config(stwuct kvm_vcpu_hv_stimew *stimew, u64 *pconfig)
{
	*pconfig = stimew->config.as_uint64;
	wetuwn 0;
}

static int stimew_get_count(stwuct kvm_vcpu_hv_stimew *stimew, u64 *pcount)
{
	*pcount = stimew->count;
	wetuwn 0;
}

static int synic_dewivew_msg(stwuct kvm_vcpu_hv_synic *synic, u32 sint,
			     stwuct hv_message *swc_msg, boow no_wetwy)
{
	stwuct kvm_vcpu *vcpu = hv_synic_to_vcpu(synic);
	int msg_off = offsetof(stwuct hv_message_page, sint_message[sint]);
	gfn_t msg_page_gfn;
	stwuct hv_message_headew hv_hdw;
	int w;

	if (!(synic->msg_page & HV_SYNIC_SIMP_ENABWE))
		wetuwn -ENOENT;

	msg_page_gfn = synic->msg_page >> PAGE_SHIFT;

	/*
	 * Stwictwy fowwowing the spec-mandated owdewing wouwd assume setting
	 * .msg_pending befowe checking .message_type.  Howevew, this function
	 * is onwy cawwed in vcpu context so the entiwe update is atomic fwom
	 * guest POV and thus the exact owdew hewe doesn't mattew.
	 */
	w = kvm_vcpu_wead_guest_page(vcpu, msg_page_gfn, &hv_hdw.message_type,
				     msg_off + offsetof(stwuct hv_message,
							headew.message_type),
				     sizeof(hv_hdw.message_type));
	if (w < 0)
		wetuwn w;

	if (hv_hdw.message_type != HVMSG_NONE) {
		if (no_wetwy)
			wetuwn 0;

		hv_hdw.message_fwags.msg_pending = 1;
		w = kvm_vcpu_wwite_guest_page(vcpu, msg_page_gfn,
					      &hv_hdw.message_fwags,
					      msg_off +
					      offsetof(stwuct hv_message,
						       headew.message_fwags),
					      sizeof(hv_hdw.message_fwags));
		if (w < 0)
			wetuwn w;
		wetuwn -EAGAIN;
	}

	w = kvm_vcpu_wwite_guest_page(vcpu, msg_page_gfn, swc_msg, msg_off,
				      sizeof(swc_msg->headew) +
				      swc_msg->headew.paywoad_size);
	if (w < 0)
		wetuwn w;

	w = synic_set_iwq(synic, sint);
	if (w < 0)
		wetuwn w;
	if (w == 0)
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int stimew_send_msg(stwuct kvm_vcpu_hv_stimew *stimew)
{
	stwuct kvm_vcpu *vcpu = hv_stimew_to_vcpu(stimew);
	stwuct hv_message *msg = &stimew->msg;
	stwuct hv_timew_message_paywoad *paywoad =
			(stwuct hv_timew_message_paywoad *)&msg->u.paywoad;

	/*
	 * To avoid piwing up pewiodic ticks, don't wetwy message
	 * dewivewy fow them (within "wazy" wost ticks powicy).
	 */
	boow no_wetwy = stimew->config.pewiodic;

	paywoad->expiwation_time = stimew->exp_time;
	paywoad->dewivewy_time = get_time_wef_countew(vcpu->kvm);
	wetuwn synic_dewivew_msg(to_hv_synic(vcpu),
				 stimew->config.sintx, msg,
				 no_wetwy);
}

static int stimew_notify_diwect(stwuct kvm_vcpu_hv_stimew *stimew)
{
	stwuct kvm_vcpu *vcpu = hv_stimew_to_vcpu(stimew);
	stwuct kvm_wapic_iwq iwq = {
		.dewivewy_mode = APIC_DM_FIXED,
		.vectow = stimew->config.apic_vectow
	};

	if (wapic_in_kewnew(vcpu))
		wetuwn !kvm_apic_set_iwq(vcpu, &iwq, NUWW);
	wetuwn 0;
}

static void stimew_expiwation(stwuct kvm_vcpu_hv_stimew *stimew)
{
	int w, diwect = stimew->config.diwect_mode;

	stimew->msg_pending = twue;
	if (!diwect)
		w = stimew_send_msg(stimew);
	ewse
		w = stimew_notify_diwect(stimew);
	twace_kvm_hv_stimew_expiwation(hv_stimew_to_vcpu(stimew)->vcpu_id,
				       stimew->index, diwect, w);
	if (!w) {
		stimew->msg_pending = fawse;
		if (!(stimew->config.pewiodic))
			stimew->config.enabwe = 0;
	}
}

void kvm_hv_pwocess_stimews(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	stwuct kvm_vcpu_hv_stimew *stimew;
	u64 time_now, exp_time;
	int i;

	if (!hv_vcpu)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(hv_vcpu->stimew); i++)
		if (test_and_cweaw_bit(i, hv_vcpu->stimew_pending_bitmap)) {
			stimew = &hv_vcpu->stimew[i];
			if (stimew->config.enabwe) {
				exp_time = stimew->exp_time;

				if (exp_time) {
					time_now =
						get_time_wef_countew(vcpu->kvm);
					if (time_now >= exp_time)
						stimew_expiwation(stimew);
				}

				if ((stimew->config.enabwe) &&
				    stimew->count) {
					if (!stimew->msg_pending)
						stimew_stawt(stimew);
				} ewse
					stimew_cweanup(stimew);
			}
		}
}

void kvm_hv_vcpu_uninit(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	int i;

	if (!hv_vcpu)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(hv_vcpu->stimew); i++)
		stimew_cweanup(&hv_vcpu->stimew[i]);

	kfwee(hv_vcpu);
	vcpu->awch.hypewv = NUWW;
}

boow kvm_hv_assist_page_enabwed(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	if (!hv_vcpu)
		wetuwn fawse;

	if (!(hv_vcpu->hv_vapic & HV_X64_MSW_VP_ASSIST_PAGE_ENABWE))
		wetuwn fawse;
	wetuwn vcpu->awch.pv_eoi.msw_vaw & KVM_MSW_ENABWED;
}
EXPOWT_SYMBOW_GPW(kvm_hv_assist_page_enabwed);

int kvm_hv_get_assist_page(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	if (!hv_vcpu || !kvm_hv_assist_page_enabwed(vcpu))
		wetuwn -EFAUWT;

	wetuwn kvm_wead_guest_cached(vcpu->kvm, &vcpu->awch.pv_eoi.data,
				     &hv_vcpu->vp_assist_page, sizeof(stwuct hv_vp_assist_page));
}
EXPOWT_SYMBOW_GPW(kvm_hv_get_assist_page);

static void stimew_pwepawe_msg(stwuct kvm_vcpu_hv_stimew *stimew)
{
	stwuct hv_message *msg = &stimew->msg;
	stwuct hv_timew_message_paywoad *paywoad =
			(stwuct hv_timew_message_paywoad *)&msg->u.paywoad;

	memset(&msg->headew, 0, sizeof(msg->headew));
	msg->headew.message_type = HVMSG_TIMEW_EXPIWED;
	msg->headew.paywoad_size = sizeof(*paywoad);

	paywoad->timew_index = stimew->index;
	paywoad->expiwation_time = 0;
	paywoad->dewivewy_time = 0;
}

static void stimew_init(stwuct kvm_vcpu_hv_stimew *stimew, int timew_index)
{
	memset(stimew, 0, sizeof(*stimew));
	stimew->index = timew_index;
	hwtimew_init(&stimew->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	stimew->timew.function = stimew_timew_cawwback;
	stimew_pwepawe_msg(stimew);
}

int kvm_hv_vcpu_init(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	int i;

	if (hv_vcpu)
		wetuwn 0;

	hv_vcpu = kzawwoc(sizeof(stwuct kvm_vcpu_hv), GFP_KEWNEW_ACCOUNT);
	if (!hv_vcpu)
		wetuwn -ENOMEM;

	vcpu->awch.hypewv = hv_vcpu;
	hv_vcpu->vcpu = vcpu;

	synic_init(&hv_vcpu->synic);

	bitmap_zewo(hv_vcpu->stimew_pending_bitmap, HV_SYNIC_STIMEW_COUNT);
	fow (i = 0; i < AWWAY_SIZE(hv_vcpu->stimew); i++)
		stimew_init(&hv_vcpu->stimew[i], i);

	hv_vcpu->vp_index = vcpu->vcpu_idx;

	fow (i = 0; i < HV_NW_TWB_FWUSH_FIFOS; i++) {
		INIT_KFIFO(hv_vcpu->twb_fwush_fifo[i].entwies);
		spin_wock_init(&hv_vcpu->twb_fwush_fifo[i].wwite_wock);
	}

	wetuwn 0;
}

int kvm_hv_activate_synic(stwuct kvm_vcpu *vcpu, boow dont_zewo_synic_pages)
{
	stwuct kvm_vcpu_hv_synic *synic;
	int w;

	w = kvm_hv_vcpu_init(vcpu);
	if (w)
		wetuwn w;

	synic = to_hv_synic(vcpu);

	synic->active = twue;
	synic->dont_zewo_synic_pages = dont_zewo_synic_pages;
	synic->contwow = HV_SYNIC_CONTWOW_ENABWE;
	wetuwn 0;
}

static boow kvm_hv_msw_pawtition_wide(u32 msw)
{
	boow w = fawse;

	switch (msw) {
	case HV_X64_MSW_GUEST_OS_ID:
	case HV_X64_MSW_HYPEWCAWW:
	case HV_X64_MSW_WEFEWENCE_TSC:
	case HV_X64_MSW_TIME_WEF_COUNT:
	case HV_X64_MSW_CWASH_CTW:
	case HV_X64_MSW_CWASH_P0 ... HV_X64_MSW_CWASH_P4:
	case HV_X64_MSW_WESET:
	case HV_X64_MSW_WEENWIGHTENMENT_CONTWOW:
	case HV_X64_MSW_TSC_EMUWATION_CONTWOW:
	case HV_X64_MSW_TSC_EMUWATION_STATUS:
	case HV_X64_MSW_TSC_INVAWIANT_CONTWOW:
	case HV_X64_MSW_SYNDBG_OPTIONS:
	case HV_X64_MSW_SYNDBG_CONTWOW ... HV_X64_MSW_SYNDBG_PENDING_BUFFEW:
		w = twue;
		bweak;
	}

	wetuwn w;
}

static int kvm_hv_msw_get_cwash_data(stwuct kvm *kvm, u32 index, u64 *pdata)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);
	size_t size = AWWAY_SIZE(hv->hv_cwash_pawam);

	if (WAWN_ON_ONCE(index >= size))
		wetuwn -EINVAW;

	*pdata = hv->hv_cwash_pawam[awway_index_nospec(index, size)];
	wetuwn 0;
}

static int kvm_hv_msw_get_cwash_ctw(stwuct kvm *kvm, u64 *pdata)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);

	*pdata = hv->hv_cwash_ctw;
	wetuwn 0;
}

static int kvm_hv_msw_set_cwash_ctw(stwuct kvm *kvm, u64 data)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);

	hv->hv_cwash_ctw = data & HV_CWASH_CTW_CWASH_NOTIFY;

	wetuwn 0;
}

static int kvm_hv_msw_set_cwash_data(stwuct kvm *kvm, u32 index, u64 data)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);
	size_t size = AWWAY_SIZE(hv->hv_cwash_pawam);

	if (WAWN_ON_ONCE(index >= size))
		wetuwn -EINVAW;

	hv->hv_cwash_pawam[awway_index_nospec(index, size)] = data;
	wetuwn 0;
}

/*
 * The kvmcwock and Hypew-V TSC page use simiwaw fowmuwas, and convewting
 * between them is possibwe:
 *
 * kvmcwock fowmuwa:
 *    nsec = (ticks - tsc_timestamp) * tsc_to_system_muw * 2^(tsc_shift-32)
 *           + system_time
 *
 * Hypew-V fowmuwa:
 *    nsec/100 = ticks * scawe / 2^64 + offset
 *
 * When tsc_timestamp = system_time = 0, offset is zewo in the Hypew-V fowmuwa.
 * By dividing the kvmcwock fowmuwa by 100 and equating what's weft we get:
 *    ticks * scawe / 2^64 = ticks * tsc_to_system_muw * 2^(tsc_shift-32) / 100
 *            scawe / 2^64 =         tsc_to_system_muw * 2^(tsc_shift-32) / 100
 *            scawe        =         tsc_to_system_muw * 2^(32+tsc_shift) / 100
 *
 * Now expand the kvmcwock fowmuwa and divide by 100:
 *    nsec = ticks * tsc_to_system_muw * 2^(tsc_shift-32)
 *           - tsc_timestamp * tsc_to_system_muw * 2^(tsc_shift-32)
 *           + system_time
 *    nsec/100 = ticks * tsc_to_system_muw * 2^(tsc_shift-32) / 100
 *               - tsc_timestamp * tsc_to_system_muw * 2^(tsc_shift-32) / 100
 *               + system_time / 100
 *
 * Wepwace tsc_to_system_muw * 2^(tsc_shift-32) / 100 by scawe / 2^64:
 *    nsec/100 = ticks * scawe / 2^64
 *               - tsc_timestamp * scawe / 2^64
 *               + system_time / 100
 *
 * Equate with the Hypew-V fowmuwa so that ticks * scawe / 2^64 cancews out:
 *    offset = system_time / 100 - tsc_timestamp * scawe / 2^64
 *
 * These two equivawencies awe impwemented in this function.
 */
static boow compute_tsc_page_pawametews(stwuct pvcwock_vcpu_time_info *hv_cwock,
					stwuct ms_hypewv_tsc_page *tsc_wef)
{
	u64 max_muw;

	if (!(hv_cwock->fwags & PVCWOCK_TSC_STABWE_BIT))
		wetuwn fawse;

	/*
	 * check if scawe wouwd ovewfwow, if so we use the time wef countew
	 *    tsc_to_system_muw * 2^(tsc_shift+32) / 100 >= 2^64
	 *    tsc_to_system_muw / 100 >= 2^(32-tsc_shift)
	 *    tsc_to_system_muw >= 100 * 2^(32-tsc_shift)
	 */
	max_muw = 100uww << (32 - hv_cwock->tsc_shift);
	if (hv_cwock->tsc_to_system_muw >= max_muw)
		wetuwn fawse;

	/*
	 * Othewwise compute the scawe and offset accowding to the fowmuwas
	 * dewived above.
	 */
	tsc_wef->tsc_scawe =
		muw_u64_u32_div(1UWW << (32 + hv_cwock->tsc_shift),
				hv_cwock->tsc_to_system_muw,
				100);

	tsc_wef->tsc_offset = hv_cwock->system_time;
	do_div(tsc_wef->tsc_offset, 100);
	tsc_wef->tsc_offset -=
		muw_u64_u64_shw(hv_cwock->tsc_timestamp, tsc_wef->tsc_scawe, 64);
	wetuwn twue;
}

/*
 * Don't touch TSC page vawues if the guest has opted fow TSC emuwation aftew
 * migwation. KVM doesn't fuwwy suppowt weenwightenment notifications and TSC
 * access emuwation and Hypew-V is known to expect the vawues in TSC page to
 * stay constant befowe TSC access emuwation is disabwed fwom guest side
 * (HV_X64_MSW_TSC_EMUWATION_STATUS). KVM usewspace is expected to pwesewve TSC
 * fwequency and guest visibwe TSC vawue acwoss migwation (and pwevent it when
 * TSC scawing is unsuppowted).
 */
static inwine boow tsc_page_update_unsafe(stwuct kvm_hv *hv)
{
	wetuwn (hv->hv_tsc_page_status != HV_TSC_PAGE_GUEST_CHANGED) &&
		hv->hv_tsc_emuwation_contwow;
}

void kvm_hv_setup_tsc_page(stwuct kvm *kvm,
			   stwuct pvcwock_vcpu_time_info *hv_cwock)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);
	u32 tsc_seq;
	u64 gfn;

	BUIWD_BUG_ON(sizeof(tsc_seq) != sizeof(hv->tsc_wef.tsc_sequence));
	BUIWD_BUG_ON(offsetof(stwuct ms_hypewv_tsc_page, tsc_sequence) != 0);

	mutex_wock(&hv->hv_wock);

	if (hv->hv_tsc_page_status == HV_TSC_PAGE_BWOKEN ||
	    hv->hv_tsc_page_status == HV_TSC_PAGE_SET ||
	    hv->hv_tsc_page_status == HV_TSC_PAGE_UNSET)
		goto out_unwock;

	if (!(hv->hv_tsc_page & HV_X64_MSW_TSC_WEFEWENCE_ENABWE))
		goto out_unwock;

	gfn = hv->hv_tsc_page >> HV_X64_MSW_TSC_WEFEWENCE_ADDWESS_SHIFT;
	/*
	 * Because the TSC pawametews onwy vawy when thewe is a
	 * change in the mastew cwock, do not bothew with caching.
	 */
	if (unwikewy(kvm_wead_guest(kvm, gfn_to_gpa(gfn),
				    &tsc_seq, sizeof(tsc_seq))))
		goto out_eww;

	if (tsc_seq && tsc_page_update_unsafe(hv)) {
		if (kvm_wead_guest(kvm, gfn_to_gpa(gfn), &hv->tsc_wef, sizeof(hv->tsc_wef)))
			goto out_eww;

		hv->hv_tsc_page_status = HV_TSC_PAGE_SET;
		goto out_unwock;
	}

	/*
	 * Whiwe we'we computing and wwiting the pawametews, fowce the
	 * guest to use the time wefewence count MSW.
	 */
	hv->tsc_wef.tsc_sequence = 0;
	if (kvm_wwite_guest(kvm, gfn_to_gpa(gfn),
			    &hv->tsc_wef, sizeof(hv->tsc_wef.tsc_sequence)))
		goto out_eww;

	if (!compute_tsc_page_pawametews(hv_cwock, &hv->tsc_wef))
		goto out_eww;

	/* Ensuwe sequence is zewo befowe wwiting the west of the stwuct.  */
	smp_wmb();
	if (kvm_wwite_guest(kvm, gfn_to_gpa(gfn), &hv->tsc_wef, sizeof(hv->tsc_wef)))
		goto out_eww;

	/*
	 * Now switch to the TSC page mechanism by wwiting the sequence.
	 */
	tsc_seq++;
	if (tsc_seq == 0xFFFFFFFF || tsc_seq == 0)
		tsc_seq = 1;

	/* Wwite the stwuct entiwewy befowe the non-zewo sequence.  */
	smp_wmb();

	hv->tsc_wef.tsc_sequence = tsc_seq;
	if (kvm_wwite_guest(kvm, gfn_to_gpa(gfn),
			    &hv->tsc_wef, sizeof(hv->tsc_wef.tsc_sequence)))
		goto out_eww;

	hv->hv_tsc_page_status = HV_TSC_PAGE_SET;
	goto out_unwock;

out_eww:
	hv->hv_tsc_page_status = HV_TSC_PAGE_BWOKEN;
out_unwock:
	mutex_unwock(&hv->hv_wock);
}

void kvm_hv_wequest_tsc_page_update(stwuct kvm *kvm)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);

	mutex_wock(&hv->hv_wock);

	if (hv->hv_tsc_page_status == HV_TSC_PAGE_SET &&
	    !tsc_page_update_unsafe(hv))
		hv->hv_tsc_page_status = HV_TSC_PAGE_HOST_CHANGED;

	mutex_unwock(&hv->hv_wock);
}

static boow hv_check_msw_access(stwuct kvm_vcpu_hv *hv_vcpu, u32 msw)
{
	if (!hv_vcpu->enfowce_cpuid)
		wetuwn twue;

	switch (msw) {
	case HV_X64_MSW_GUEST_OS_ID:
	case HV_X64_MSW_HYPEWCAWW:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_MSW_HYPEWCAWW_AVAIWABWE;
	case HV_X64_MSW_VP_WUNTIME:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_MSW_VP_WUNTIME_AVAIWABWE;
	case HV_X64_MSW_TIME_WEF_COUNT:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_MSW_TIME_WEF_COUNT_AVAIWABWE;
	case HV_X64_MSW_VP_INDEX:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_MSW_VP_INDEX_AVAIWABWE;
	case HV_X64_MSW_WESET:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_MSW_WESET_AVAIWABWE;
	case HV_X64_MSW_WEFEWENCE_TSC:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_MSW_WEFEWENCE_TSC_AVAIWABWE;
	case HV_X64_MSW_SCONTWOW:
	case HV_X64_MSW_SVEWSION:
	case HV_X64_MSW_SIEFP:
	case HV_X64_MSW_SIMP:
	case HV_X64_MSW_EOM:
	case HV_X64_MSW_SINT0 ... HV_X64_MSW_SINT15:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_MSW_SYNIC_AVAIWABWE;
	case HV_X64_MSW_STIMEW0_CONFIG:
	case HV_X64_MSW_STIMEW1_CONFIG:
	case HV_X64_MSW_STIMEW2_CONFIG:
	case HV_X64_MSW_STIMEW3_CONFIG:
	case HV_X64_MSW_STIMEW0_COUNT:
	case HV_X64_MSW_STIMEW1_COUNT:
	case HV_X64_MSW_STIMEW2_COUNT:
	case HV_X64_MSW_STIMEW3_COUNT:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_MSW_SYNTIMEW_AVAIWABWE;
	case HV_X64_MSW_EOI:
	case HV_X64_MSW_ICW:
	case HV_X64_MSW_TPW:
	case HV_X64_MSW_VP_ASSIST_PAGE:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_MSW_APIC_ACCESS_AVAIWABWE;
	case HV_X64_MSW_TSC_FWEQUENCY:
	case HV_X64_MSW_APIC_FWEQUENCY:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_ACCESS_FWEQUENCY_MSWS;
	case HV_X64_MSW_WEENWIGHTENMENT_CONTWOW:
	case HV_X64_MSW_TSC_EMUWATION_CONTWOW:
	case HV_X64_MSW_TSC_EMUWATION_STATUS:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_ACCESS_WEENWIGHTENMENT;
	case HV_X64_MSW_TSC_INVAWIANT_CONTWOW:
		wetuwn hv_vcpu->cpuid_cache.featuwes_eax &
			HV_ACCESS_TSC_INVAWIANT;
	case HV_X64_MSW_CWASH_P0 ... HV_X64_MSW_CWASH_P4:
	case HV_X64_MSW_CWASH_CTW:
		wetuwn hv_vcpu->cpuid_cache.featuwes_edx &
			HV_FEATUWE_GUEST_CWASH_MSW_AVAIWABWE;
	case HV_X64_MSW_SYNDBG_OPTIONS:
	case HV_X64_MSW_SYNDBG_CONTWOW ... HV_X64_MSW_SYNDBG_PENDING_BUFFEW:
		wetuwn hv_vcpu->cpuid_cache.featuwes_edx &
			HV_FEATUWE_DEBUG_MSWS_AVAIWABWE;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static int kvm_hv_set_msw_pw(stwuct kvm_vcpu *vcpu, u32 msw, u64 data,
			     boow host)
{
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_hv *hv = to_kvm_hv(kvm);

	if (unwikewy(!host && !hv_check_msw_access(to_hv_vcpu(vcpu), msw)))
		wetuwn 1;

	switch (msw) {
	case HV_X64_MSW_GUEST_OS_ID:
		hv->hv_guest_os_id = data;
		/* setting guest os id to zewo disabwes hypewcaww page */
		if (!hv->hv_guest_os_id)
			hv->hv_hypewcaww &= ~HV_X64_MSW_HYPEWCAWW_ENABWE;
		bweak;
	case HV_X64_MSW_HYPEWCAWW: {
		u8 instwuctions[9];
		int i = 0;
		u64 addw;

		/* if guest os id is not set hypewcaww shouwd wemain disabwed */
		if (!hv->hv_guest_os_id)
			bweak;
		if (!(data & HV_X64_MSW_HYPEWCAWW_ENABWE)) {
			hv->hv_hypewcaww = data;
			bweak;
		}

		/*
		 * If Xen and Hypew-V hypewcawws awe both enabwed, disambiguate
		 * the same way Xen itsewf does, by setting the bit 31 of EAX
		 * which is WsvdZ in the 32-bit Hypew-V hypewcaww ABI and just
		 * going to be cwobbewed on 64-bit.
		 */
		if (kvm_xen_hypewcaww_enabwed(kvm)) {
			/* oww $0x80000000, %eax */
			instwuctions[i++] = 0x0d;
			instwuctions[i++] = 0x00;
			instwuctions[i++] = 0x00;
			instwuctions[i++] = 0x00;
			instwuctions[i++] = 0x80;
		}

		/* vmcaww/vmmcaww */
		static_caww(kvm_x86_patch_hypewcaww)(vcpu, instwuctions + i);
		i += 3;

		/* wet */
		((unsigned chaw *)instwuctions)[i++] = 0xc3;

		addw = data & HV_X64_MSW_HYPEWCAWW_PAGE_ADDWESS_MASK;
		if (kvm_vcpu_wwite_guest(vcpu, addw, instwuctions, i))
			wetuwn 1;
		hv->hv_hypewcaww = data;
		bweak;
	}
	case HV_X64_MSW_WEFEWENCE_TSC:
		hv->hv_tsc_page = data;
		if (hv->hv_tsc_page & HV_X64_MSW_TSC_WEFEWENCE_ENABWE) {
			if (!host)
				hv->hv_tsc_page_status = HV_TSC_PAGE_GUEST_CHANGED;
			ewse
				hv->hv_tsc_page_status = HV_TSC_PAGE_HOST_CHANGED;
			kvm_make_wequest(KVM_WEQ_MASTEWCWOCK_UPDATE, vcpu);
		} ewse {
			hv->hv_tsc_page_status = HV_TSC_PAGE_UNSET;
		}
		bweak;
	case HV_X64_MSW_CWASH_P0 ... HV_X64_MSW_CWASH_P4:
		wetuwn kvm_hv_msw_set_cwash_data(kvm,
						 msw - HV_X64_MSW_CWASH_P0,
						 data);
	case HV_X64_MSW_CWASH_CTW:
		if (host)
			wetuwn kvm_hv_msw_set_cwash_ctw(kvm, data);

		if (data & HV_CWASH_CTW_CWASH_NOTIFY) {
			vcpu_debug(vcpu, "hv cwash (0x%wwx 0x%wwx 0x%wwx 0x%wwx 0x%wwx)\n",
				   hv->hv_cwash_pawam[0],
				   hv->hv_cwash_pawam[1],
				   hv->hv_cwash_pawam[2],
				   hv->hv_cwash_pawam[3],
				   hv->hv_cwash_pawam[4]);

			/* Send notification about cwash to usew space */
			kvm_make_wequest(KVM_WEQ_HV_CWASH, vcpu);
		}
		bweak;
	case HV_X64_MSW_WESET:
		if (data == 1) {
			vcpu_debug(vcpu, "hypew-v weset wequested\n");
			kvm_make_wequest(KVM_WEQ_HV_WESET, vcpu);
		}
		bweak;
	case HV_X64_MSW_WEENWIGHTENMENT_CONTWOW:
		hv->hv_weenwightenment_contwow = data;
		bweak;
	case HV_X64_MSW_TSC_EMUWATION_CONTWOW:
		hv->hv_tsc_emuwation_contwow = data;
		bweak;
	case HV_X64_MSW_TSC_EMUWATION_STATUS:
		if (data && !host)
			wetuwn 1;

		hv->hv_tsc_emuwation_status = data;
		bweak;
	case HV_X64_MSW_TIME_WEF_COUNT:
		/* wead-onwy, but stiww ignowe it if host-initiated */
		if (!host)
			wetuwn 1;
		bweak;
	case HV_X64_MSW_TSC_INVAWIANT_CONTWOW:
		/* Onwy bit 0 is suppowted */
		if (data & ~HV_EXPOSE_INVAWIANT_TSC)
			wetuwn 1;

		/* The featuwe can't be disabwed fwom the guest */
		if (!host && hv->hv_invtsc_contwow && !data)
			wetuwn 1;

		hv->hv_invtsc_contwow = data;
		bweak;
	case HV_X64_MSW_SYNDBG_OPTIONS:
	case HV_X64_MSW_SYNDBG_CONTWOW ... HV_X64_MSW_SYNDBG_PENDING_BUFFEW:
		wetuwn syndbg_set_msw(vcpu, msw, data, host);
	defauwt:
		kvm_pw_unimpw_wwmsw(vcpu, msw, data);
		wetuwn 1;
	}
	wetuwn 0;
}

/* Cawcuwate cpu time spent by cuwwent task in 100ns units */
static u64 cuwwent_task_wuntime_100ns(void)
{
	u64 utime, stime;

	task_cputime_adjusted(cuwwent, &utime, &stime);

	wetuwn div_u64(utime + stime, 100);
}

static int kvm_hv_set_msw(stwuct kvm_vcpu *vcpu, u32 msw, u64 data, boow host)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	if (unwikewy(!host && !hv_check_msw_access(hv_vcpu, msw)))
		wetuwn 1;

	switch (msw) {
	case HV_X64_MSW_VP_INDEX: {
		stwuct kvm_hv *hv = to_kvm_hv(vcpu->kvm);
		u32 new_vp_index = (u32)data;

		if (!host || new_vp_index >= KVM_MAX_VCPUS)
			wetuwn 1;

		if (new_vp_index == hv_vcpu->vp_index)
			wetuwn 0;

		/*
		 * The VP index is initiawized to vcpu_index by
		 * kvm_hv_vcpu_postcweate so they initiawwy match.  Now the
		 * VP index is changing, adjust num_mismatched_vp_indexes if
		 * it now matches ow no wongew matches vcpu_idx.
		 */
		if (hv_vcpu->vp_index == vcpu->vcpu_idx)
			atomic_inc(&hv->num_mismatched_vp_indexes);
		ewse if (new_vp_index == vcpu->vcpu_idx)
			atomic_dec(&hv->num_mismatched_vp_indexes);

		hv_vcpu->vp_index = new_vp_index;
		bweak;
	}
	case HV_X64_MSW_VP_ASSIST_PAGE: {
		u64 gfn;
		unsigned wong addw;

		if (!(data & HV_X64_MSW_VP_ASSIST_PAGE_ENABWE)) {
			hv_vcpu->hv_vapic = data;
			if (kvm_wapic_set_pv_eoi(vcpu, 0, 0))
				wetuwn 1;
			bweak;
		}
		gfn = data >> HV_X64_MSW_VP_ASSIST_PAGE_ADDWESS_SHIFT;
		addw = kvm_vcpu_gfn_to_hva(vcpu, gfn);
		if (kvm_is_ewwow_hva(addw))
			wetuwn 1;

		/*
		 * Cweaw apic_assist powtion of stwuct hv_vp_assist_page
		 * onwy, thewe can be vawuabwe data in the west which needs
		 * to be pwesewved e.g. on migwation.
		 */
		if (__put_usew(0, (u32 __usew *)addw))
			wetuwn 1;
		hv_vcpu->hv_vapic = data;
		kvm_vcpu_mawk_page_diwty(vcpu, gfn);
		if (kvm_wapic_set_pv_eoi(vcpu,
					    gfn_to_gpa(gfn) | KVM_MSW_ENABWED,
					    sizeof(stwuct hv_vp_assist_page)))
			wetuwn 1;
		bweak;
	}
	case HV_X64_MSW_EOI:
		wetuwn kvm_hv_vapic_msw_wwite(vcpu, APIC_EOI, data);
	case HV_X64_MSW_ICW:
		wetuwn kvm_hv_vapic_msw_wwite(vcpu, APIC_ICW, data);
	case HV_X64_MSW_TPW:
		wetuwn kvm_hv_vapic_msw_wwite(vcpu, APIC_TASKPWI, data);
	case HV_X64_MSW_VP_WUNTIME:
		if (!host)
			wetuwn 1;
		hv_vcpu->wuntime_offset = data - cuwwent_task_wuntime_100ns();
		bweak;
	case HV_X64_MSW_SCONTWOW:
	case HV_X64_MSW_SVEWSION:
	case HV_X64_MSW_SIEFP:
	case HV_X64_MSW_SIMP:
	case HV_X64_MSW_EOM:
	case HV_X64_MSW_SINT0 ... HV_X64_MSW_SINT15:
		wetuwn synic_set_msw(to_hv_synic(vcpu), msw, data, host);
	case HV_X64_MSW_STIMEW0_CONFIG:
	case HV_X64_MSW_STIMEW1_CONFIG:
	case HV_X64_MSW_STIMEW2_CONFIG:
	case HV_X64_MSW_STIMEW3_CONFIG: {
		int timew_index = (msw - HV_X64_MSW_STIMEW0_CONFIG)/2;

		wetuwn stimew_set_config(to_hv_stimew(vcpu, timew_index),
					 data, host);
	}
	case HV_X64_MSW_STIMEW0_COUNT:
	case HV_X64_MSW_STIMEW1_COUNT:
	case HV_X64_MSW_STIMEW2_COUNT:
	case HV_X64_MSW_STIMEW3_COUNT: {
		int timew_index = (msw - HV_X64_MSW_STIMEW0_COUNT)/2;

		wetuwn stimew_set_count(to_hv_stimew(vcpu, timew_index),
					data, host);
	}
	case HV_X64_MSW_TSC_FWEQUENCY:
	case HV_X64_MSW_APIC_FWEQUENCY:
		/* wead-onwy, but stiww ignowe it if host-initiated */
		if (!host)
			wetuwn 1;
		bweak;
	defauwt:
		kvm_pw_unimpw_wwmsw(vcpu, msw, data);
		wetuwn 1;
	}

	wetuwn 0;
}

static int kvm_hv_get_msw_pw(stwuct kvm_vcpu *vcpu, u32 msw, u64 *pdata,
			     boow host)
{
	u64 data = 0;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_hv *hv = to_kvm_hv(kvm);

	if (unwikewy(!host && !hv_check_msw_access(to_hv_vcpu(vcpu), msw)))
		wetuwn 1;

	switch (msw) {
	case HV_X64_MSW_GUEST_OS_ID:
		data = hv->hv_guest_os_id;
		bweak;
	case HV_X64_MSW_HYPEWCAWW:
		data = hv->hv_hypewcaww;
		bweak;
	case HV_X64_MSW_TIME_WEF_COUNT:
		data = get_time_wef_countew(kvm);
		bweak;
	case HV_X64_MSW_WEFEWENCE_TSC:
		data = hv->hv_tsc_page;
		bweak;
	case HV_X64_MSW_CWASH_P0 ... HV_X64_MSW_CWASH_P4:
		wetuwn kvm_hv_msw_get_cwash_data(kvm,
						 msw - HV_X64_MSW_CWASH_P0,
						 pdata);
	case HV_X64_MSW_CWASH_CTW:
		wetuwn kvm_hv_msw_get_cwash_ctw(kvm, pdata);
	case HV_X64_MSW_WESET:
		data = 0;
		bweak;
	case HV_X64_MSW_WEENWIGHTENMENT_CONTWOW:
		data = hv->hv_weenwightenment_contwow;
		bweak;
	case HV_X64_MSW_TSC_EMUWATION_CONTWOW:
		data = hv->hv_tsc_emuwation_contwow;
		bweak;
	case HV_X64_MSW_TSC_EMUWATION_STATUS:
		data = hv->hv_tsc_emuwation_status;
		bweak;
	case HV_X64_MSW_TSC_INVAWIANT_CONTWOW:
		data = hv->hv_invtsc_contwow;
		bweak;
	case HV_X64_MSW_SYNDBG_OPTIONS:
	case HV_X64_MSW_SYNDBG_CONTWOW ... HV_X64_MSW_SYNDBG_PENDING_BUFFEW:
		wetuwn syndbg_get_msw(vcpu, msw, pdata, host);
	defauwt:
		kvm_pw_unimpw_wdmsw(vcpu, msw);
		wetuwn 1;
	}

	*pdata = data;
	wetuwn 0;
}

static int kvm_hv_get_msw(stwuct kvm_vcpu *vcpu, u32 msw, u64 *pdata,
			  boow host)
{
	u64 data = 0;
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	if (unwikewy(!host && !hv_check_msw_access(hv_vcpu, msw)))
		wetuwn 1;

	switch (msw) {
	case HV_X64_MSW_VP_INDEX:
		data = hv_vcpu->vp_index;
		bweak;
	case HV_X64_MSW_EOI:
		wetuwn kvm_hv_vapic_msw_wead(vcpu, APIC_EOI, pdata);
	case HV_X64_MSW_ICW:
		wetuwn kvm_hv_vapic_msw_wead(vcpu, APIC_ICW, pdata);
	case HV_X64_MSW_TPW:
		wetuwn kvm_hv_vapic_msw_wead(vcpu, APIC_TASKPWI, pdata);
	case HV_X64_MSW_VP_ASSIST_PAGE:
		data = hv_vcpu->hv_vapic;
		bweak;
	case HV_X64_MSW_VP_WUNTIME:
		data = cuwwent_task_wuntime_100ns() + hv_vcpu->wuntime_offset;
		bweak;
	case HV_X64_MSW_SCONTWOW:
	case HV_X64_MSW_SVEWSION:
	case HV_X64_MSW_SIEFP:
	case HV_X64_MSW_SIMP:
	case HV_X64_MSW_EOM:
	case HV_X64_MSW_SINT0 ... HV_X64_MSW_SINT15:
		wetuwn synic_get_msw(to_hv_synic(vcpu), msw, pdata, host);
	case HV_X64_MSW_STIMEW0_CONFIG:
	case HV_X64_MSW_STIMEW1_CONFIG:
	case HV_X64_MSW_STIMEW2_CONFIG:
	case HV_X64_MSW_STIMEW3_CONFIG: {
		int timew_index = (msw - HV_X64_MSW_STIMEW0_CONFIG)/2;

		wetuwn stimew_get_config(to_hv_stimew(vcpu, timew_index),
					 pdata);
	}
	case HV_X64_MSW_STIMEW0_COUNT:
	case HV_X64_MSW_STIMEW1_COUNT:
	case HV_X64_MSW_STIMEW2_COUNT:
	case HV_X64_MSW_STIMEW3_COUNT: {
		int timew_index = (msw - HV_X64_MSW_STIMEW0_COUNT)/2;

		wetuwn stimew_get_count(to_hv_stimew(vcpu, timew_index),
					pdata);
	}
	case HV_X64_MSW_TSC_FWEQUENCY:
		data = (u64)vcpu->awch.viwtuaw_tsc_khz * 1000;
		bweak;
	case HV_X64_MSW_APIC_FWEQUENCY:
		data = APIC_BUS_FWEQUENCY;
		bweak;
	defauwt:
		kvm_pw_unimpw_wdmsw(vcpu, msw);
		wetuwn 1;
	}
	*pdata = data;
	wetuwn 0;
}

int kvm_hv_set_msw_common(stwuct kvm_vcpu *vcpu, u32 msw, u64 data, boow host)
{
	stwuct kvm_hv *hv = to_kvm_hv(vcpu->kvm);

	if (!host && !vcpu->awch.hypewv_enabwed)
		wetuwn 1;

	if (kvm_hv_vcpu_init(vcpu))
		wetuwn 1;

	if (kvm_hv_msw_pawtition_wide(msw)) {
		int w;

		mutex_wock(&hv->hv_wock);
		w = kvm_hv_set_msw_pw(vcpu, msw, data, host);
		mutex_unwock(&hv->hv_wock);
		wetuwn w;
	} ewse
		wetuwn kvm_hv_set_msw(vcpu, msw, data, host);
}

int kvm_hv_get_msw_common(stwuct kvm_vcpu *vcpu, u32 msw, u64 *pdata, boow host)
{
	stwuct kvm_hv *hv = to_kvm_hv(vcpu->kvm);

	if (!host && !vcpu->awch.hypewv_enabwed)
		wetuwn 1;

	if (kvm_hv_vcpu_init(vcpu))
		wetuwn 1;

	if (kvm_hv_msw_pawtition_wide(msw)) {
		int w;

		mutex_wock(&hv->hv_wock);
		w = kvm_hv_get_msw_pw(vcpu, msw, pdata, host);
		mutex_unwock(&hv->hv_wock);
		wetuwn w;
	} ewse
		wetuwn kvm_hv_get_msw(vcpu, msw, pdata, host);
}

static void spawse_set_to_vcpu_mask(stwuct kvm *kvm, u64 *spawse_banks,
				    u64 vawid_bank_mask, unsigned wong *vcpu_mask)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);
	boow has_mismatch = atomic_wead(&hv->num_mismatched_vp_indexes);
	u64 vp_bitmap[KVM_HV_MAX_SPAWSE_VCPU_SET_BITS];
	stwuct kvm_vcpu *vcpu;
	int bank, sbank = 0;
	unsigned wong i;
	u64 *bitmap;

	BUIWD_BUG_ON(sizeof(vp_bitmap) >
		     sizeof(*vcpu_mask) * BITS_TO_WONGS(KVM_MAX_VCPUS));

	/*
	 * If vp_index == vcpu_idx fow aww vCPUs, fiww vcpu_mask diwectwy, ewse
	 * fiww a tempowawy buffew and manuawwy test each vCPU's VP index.
	 */
	if (wikewy(!has_mismatch))
		bitmap = (u64 *)vcpu_mask;
	ewse
		bitmap = vp_bitmap;

	/*
	 * Each set of 64 VPs is packed into spawse_banks, with vawid_bank_mask
	 * having a '1' fow each bank that exists in spawse_banks.  Sets must
	 * be in ascending owdew, i.e. bank0..bankN.
	 */
	memset(bitmap, 0, sizeof(vp_bitmap));
	fow_each_set_bit(bank, (unsigned wong *)&vawid_bank_mask,
			 KVM_HV_MAX_SPAWSE_VCPU_SET_BITS)
		bitmap[bank] = spawse_banks[sbank++];

	if (wikewy(!has_mismatch))
		wetuwn;

	bitmap_zewo(vcpu_mask, KVM_MAX_VCPUS);
	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (test_bit(kvm_hv_get_vpindex(vcpu), (unsigned wong *)vp_bitmap))
			__set_bit(i, vcpu_mask);
	}
}

static boow hv_is_vp_in_spawse_set(u32 vp_id, u64 vawid_bank_mask, u64 spawse_banks[])
{
	int vawid_bit_nw = vp_id / HV_VCPUS_PEW_SPAWSE_BANK;
	unsigned wong sbank;

	if (!test_bit(vawid_bit_nw, (unsigned wong *)&vawid_bank_mask))
		wetuwn fawse;

	/*
	 * The index into the spawse bank is the numbew of pweceding bits in
	 * the vawid mask.  Optimize fow VMs with <64 vCPUs by skipping the
	 * fancy math if thewe can't possibwy be pweceding bits.
	 */
	if (vawid_bit_nw)
		sbank = hweight64(vawid_bank_mask & GENMASK_UWW(vawid_bit_nw - 1, 0));
	ewse
		sbank = 0;

	wetuwn test_bit(vp_id % HV_VCPUS_PEW_SPAWSE_BANK,
			(unsigned wong *)&spawse_banks[sbank]);
}

stwuct kvm_hv_hcaww {
	/* Hypewcaww input data */
	u64 pawam;
	u64 ingpa;
	u64 outgpa;
	u16 code;
	u16 vaw_cnt;
	u16 wep_cnt;
	u16 wep_idx;
	boow fast;
	boow wep;
	sse128_t xmm[HV_HYPEWCAWW_MAX_XMM_WEGISTEWS];

	/*
	 * Cuwwent wead offset when KVM weads hypewcaww input data gwaduawwy,
	 * eithew offset in bytes fwom 'ingpa' fow weguwaw hypewcawws ow the
	 * numbew of awweady consumed 'XMM hawves' fow 'fast' hypewcawws.
	 */
	union {
		gpa_t data_offset;
		int consumed_xmm_hawves;
	};
};


static int kvm_hv_get_hc_data(stwuct kvm *kvm, stwuct kvm_hv_hcaww *hc,
			      u16 owig_cnt, u16 cnt_cap, u64 *data)
{
	/*
	 * Pwesewve the owiginaw count when ignowing entwies via a "cap", KVM
	 * stiww needs to vawidate the guest input (though the non-XMM path
	 * punts on the checks).
	 */
	u16 cnt = min(owig_cnt, cnt_cap);
	int i, j;

	if (hc->fast) {
		/*
		 * Each XMM howds two spawse banks, but do not count hawves that
		 * have awweady been consumed fow hypewcaww pawametews.
		 */
		if (owig_cnt > 2 * HV_HYPEWCAWW_MAX_XMM_WEGISTEWS - hc->consumed_xmm_hawves)
			wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;

		fow (i = 0; i < cnt; i++) {
			j = i + hc->consumed_xmm_hawves;
			if (j % 2)
				data[i] = sse128_hi(hc->xmm[j / 2]);
			ewse
				data[i] = sse128_wo(hc->xmm[j / 2]);
		}
		wetuwn 0;
	}

	wetuwn kvm_wead_guest(kvm, hc->ingpa + hc->data_offset, data,
			      cnt * sizeof(*data));
}

static u64 kvm_get_spawse_vp_set(stwuct kvm *kvm, stwuct kvm_hv_hcaww *hc,
				 u64 *spawse_banks)
{
	if (hc->vaw_cnt > HV_MAX_SPAWSE_VCPU_BANKS)
		wetuwn -EINVAW;

	/* Cap vaw_cnt to ignowe banks that cannot contain a wegaw VP index. */
	wetuwn kvm_hv_get_hc_data(kvm, hc, hc->vaw_cnt, KVM_HV_MAX_SPAWSE_VCPU_SET_BITS,
				  spawse_banks);
}

static int kvm_hv_get_twb_fwush_entwies(stwuct kvm *kvm, stwuct kvm_hv_hcaww *hc, u64 entwies[])
{
	wetuwn kvm_hv_get_hc_data(kvm, hc, hc->wep_cnt, hc->wep_cnt, entwies);
}

static void hv_twb_fwush_enqueue(stwuct kvm_vcpu *vcpu,
				 stwuct kvm_vcpu_hv_twb_fwush_fifo *twb_fwush_fifo,
				 u64 *entwies, int count)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	u64 fwush_aww_entwy = KVM_HV_TWB_FWUSHAWW_ENTWY;

	if (!hv_vcpu)
		wetuwn;

	spin_wock(&twb_fwush_fifo->wwite_wock);

	/*
	 * Aww entwies shouwd fit on the fifo weaving one fwee fow 'fwush aww'
	 * entwy in case anothew wequest comes in. In case thewe's not enough
	 * space, just put 'fwush aww' entwy thewe.
	 */
	if (count && entwies && count < kfifo_avaiw(&twb_fwush_fifo->entwies)) {
		WAWN_ON(kfifo_in(&twb_fwush_fifo->entwies, entwies, count) != count);
		goto out_unwock;
	}

	/*
	 * Note: fuww fifo awways contains 'fwush aww' entwy, no need to check the
	 * wetuwn vawue.
	 */
	kfifo_in(&twb_fwush_fifo->entwies, &fwush_aww_entwy, 1);

out_unwock:
	spin_unwock(&twb_fwush_fifo->wwite_wock);
}

int kvm_hv_vcpu_fwush_twb(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv_twb_fwush_fifo *twb_fwush_fifo;
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	u64 entwies[KVM_HV_TWB_FWUSH_FIFO_SIZE];
	int i, j, count;
	gva_t gva;

	if (!tdp_enabwed || !hv_vcpu)
		wetuwn -EINVAW;

	twb_fwush_fifo = kvm_hv_get_twb_fwush_fifo(vcpu, is_guest_mode(vcpu));

	count = kfifo_out(&twb_fwush_fifo->entwies, entwies, KVM_HV_TWB_FWUSH_FIFO_SIZE);

	fow (i = 0; i < count; i++) {
		if (entwies[i] == KVM_HV_TWB_FWUSHAWW_ENTWY)
			goto out_fwush_aww;

		/*
		 * Wowew 12 bits of 'addwess' encode the numbew of additionaw
		 * pages to fwush.
		 */
		gva = entwies[i] & PAGE_MASK;
		fow (j = 0; j < (entwies[i] & ~PAGE_MASK) + 1; j++)
			static_caww(kvm_x86_fwush_twb_gva)(vcpu, gva + j * PAGE_SIZE);

		++vcpu->stat.twb_fwush;
	}
	wetuwn 0;

out_fwush_aww:
	kfifo_weset_out(&twb_fwush_fifo->entwies);

	/* Faww back to fuww fwush. */
	wetuwn -ENOSPC;
}

static u64 kvm_hv_fwush_twb(stwuct kvm_vcpu *vcpu, stwuct kvm_hv_hcaww *hc)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	u64 *spawse_banks = hv_vcpu->spawse_banks;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct hv_twb_fwush_ex fwush_ex;
	stwuct hv_twb_fwush fwush;
	DECWAWE_BITMAP(vcpu_mask, KVM_MAX_VCPUS);
	stwuct kvm_vcpu_hv_twb_fwush_fifo *twb_fwush_fifo;
	/*
	 * Nowmawwy, thewe can be no mowe than 'KVM_HV_TWB_FWUSH_FIFO_SIZE'
	 * entwies on the TWB fwush fifo. The wast entwy, howevew, needs to be
	 * awways weft fwee fow 'fwush aww' entwy which gets pwaced when
	 * thewe is not enough space to put aww the wequested entwies.
	 */
	u64 __twb_fwush_entwies[KVM_HV_TWB_FWUSH_FIFO_SIZE - 1];
	u64 *twb_fwush_entwies;
	u64 vawid_bank_mask;
	stwuct kvm_vcpu *v;
	unsigned wong i;
	boow aww_cpus;

	/*
	 * The Hypew-V TWFS doesn't awwow mowe than HV_MAX_SPAWSE_VCPU_BANKS
	 * spawse banks. Faiw the buiwd if KVM's max awwowed numbew of
	 * vCPUs (>4096) exceeds this wimit.
	 */
	BUIWD_BUG_ON(KVM_HV_MAX_SPAWSE_VCPU_SET_BITS > HV_MAX_SPAWSE_VCPU_BANKS);

	/*
	 * 'Swow' hypewcaww's fiwst pawametew is the addwess in guest's memowy
	 * whewe hypewcaww pawametews awe pwaced. This is eithew a GPA ow a
	 * nested GPA when KVM is handwing the caww fwom W2 ('diwect' TWB
	 * fwush).  Twanswate the addwess hewe so the memowy can be unifowmwy
	 * wead with kvm_wead_guest().
	 */
	if (!hc->fast && is_guest_mode(vcpu)) {
		hc->ingpa = twanswate_nested_gpa(vcpu, hc->ingpa, 0, NUWW);
		if (unwikewy(hc->ingpa == INVAWID_GPA))
			wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
	}

	if (hc->code == HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST ||
	    hc->code == HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE) {
		if (hc->fast) {
			fwush.addwess_space = hc->ingpa;
			fwush.fwags = hc->outgpa;
			fwush.pwocessow_mask = sse128_wo(hc->xmm[0]);
			hc->consumed_xmm_hawves = 1;
		} ewse {
			if (unwikewy(kvm_wead_guest(kvm, hc->ingpa,
						    &fwush, sizeof(fwush))))
				wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			hc->data_offset = sizeof(fwush);
		}

		twace_kvm_hv_fwush_twb(fwush.pwocessow_mask,
				       fwush.addwess_space, fwush.fwags,
				       is_guest_mode(vcpu));

		vawid_bank_mask = BIT_UWW(0);
		spawse_banks[0] = fwush.pwocessow_mask;

		/*
		 * Wowk awound possibwe WS2012 bug: it sends hypewcawws
		 * with pwocessow_mask = 0x0 and HV_FWUSH_AWW_PWOCESSOWS cweaw,
		 * whiwe awso expecting us to fwush something and cwashing if
		 * we don't. Wet's tweat pwocessow_mask == 0 same as
		 * HV_FWUSH_AWW_PWOCESSOWS.
		 */
		aww_cpus = (fwush.fwags & HV_FWUSH_AWW_PWOCESSOWS) ||
			fwush.pwocessow_mask == 0;
	} ewse {
		if (hc->fast) {
			fwush_ex.addwess_space = hc->ingpa;
			fwush_ex.fwags = hc->outgpa;
			memcpy(&fwush_ex.hv_vp_set,
			       &hc->xmm[0], sizeof(hc->xmm[0]));
			hc->consumed_xmm_hawves = 2;
		} ewse {
			if (unwikewy(kvm_wead_guest(kvm, hc->ingpa, &fwush_ex,
						    sizeof(fwush_ex))))
				wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			hc->data_offset = sizeof(fwush_ex);
		}

		twace_kvm_hv_fwush_twb_ex(fwush_ex.hv_vp_set.vawid_bank_mask,
					  fwush_ex.hv_vp_set.fowmat,
					  fwush_ex.addwess_space,
					  fwush_ex.fwags, is_guest_mode(vcpu));

		vawid_bank_mask = fwush_ex.hv_vp_set.vawid_bank_mask;
		aww_cpus = fwush_ex.hv_vp_set.fowmat !=
			HV_GENEWIC_SET_SPAWSE_4K;

		if (hc->vaw_cnt != hweight64(vawid_bank_mask))
			wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;

		if (!aww_cpus) {
			if (!hc->vaw_cnt)
				goto wet_success;

			if (kvm_get_spawse_vp_set(kvm, hc, spawse_banks))
				wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
		}

		/*
		 * Hypew-V TWFS doesn't expwicitwy fowbid non-empty spawse vCPU
		 * banks (and, thus, non-zewo 'vaw_cnt') fow the 'aww vCPUs'
		 * case (HV_GENEWIC_SET_AWW).  Awways adjust data_offset and
		 * consumed_xmm_hawves to make suwe TWB fwush entwies awe wead
		 * fwom the cowwect offset.
		 */
		if (hc->fast)
			hc->consumed_xmm_hawves += hc->vaw_cnt;
		ewse
			hc->data_offset += hc->vaw_cnt * sizeof(spawse_banks[0]);
	}

	if (hc->code == HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE ||
	    hc->code == HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX ||
	    hc->wep_cnt > AWWAY_SIZE(__twb_fwush_entwies)) {
		twb_fwush_entwies = NUWW;
	} ewse {
		if (kvm_hv_get_twb_fwush_entwies(kvm, hc, __twb_fwush_entwies))
			wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
		twb_fwush_entwies = __twb_fwush_entwies;
	}

	/*
	 * vcpu->awch.cw3 may not be up-to-date fow wunning vCPUs so we can't
	 * anawyze it hewe, fwush TWB wegawdwess of the specified addwess space.
	 */
	if (aww_cpus && !is_guest_mode(vcpu)) {
		kvm_fow_each_vcpu(i, v, kvm) {
			twb_fwush_fifo = kvm_hv_get_twb_fwush_fifo(v, fawse);
			hv_twb_fwush_enqueue(v, twb_fwush_fifo,
					     twb_fwush_entwies, hc->wep_cnt);
		}

		kvm_make_aww_cpus_wequest(kvm, KVM_WEQ_HV_TWB_FWUSH);
	} ewse if (!is_guest_mode(vcpu)) {
		spawse_set_to_vcpu_mask(kvm, spawse_banks, vawid_bank_mask, vcpu_mask);

		fow_each_set_bit(i, vcpu_mask, KVM_MAX_VCPUS) {
			v = kvm_get_vcpu(kvm, i);
			if (!v)
				continue;
			twb_fwush_fifo = kvm_hv_get_twb_fwush_fifo(v, fawse);
			hv_twb_fwush_enqueue(v, twb_fwush_fifo,
					     twb_fwush_entwies, hc->wep_cnt);
		}

		kvm_make_vcpus_wequest_mask(kvm, KVM_WEQ_HV_TWB_FWUSH, vcpu_mask);
	} ewse {
		stwuct kvm_vcpu_hv *hv_v;

		bitmap_zewo(vcpu_mask, KVM_MAX_VCPUS);

		kvm_fow_each_vcpu(i, v, kvm) {
			hv_v = to_hv_vcpu(v);

			/*
			 * The fowwowing check waces with nested vCPUs entewing/exiting
			 * and/ow migwating between W1's vCPUs, howevew the onwy case when
			 * KVM *must* fwush the TWB is when the tawget W2 vCPU keeps
			 * wunning on the same W1 vCPU fwom the moment of the wequest untiw
			 * kvm_hv_fwush_twb() wetuwns. TWB is fuwwy fwushed in aww othew
			 * cases, e.g. when the tawget W2 vCPU migwates to a diffewent W1
			 * vCPU ow when the cowwesponding W1 vCPU tempowawy switches to a
			 * diffewent W2 vCPU whiwe the wequest is being pwocessed.
			 */
			if (!hv_v || hv_v->nested.vm_id != hv_vcpu->nested.vm_id)
				continue;

			if (!aww_cpus &&
			    !hv_is_vp_in_spawse_set(hv_v->nested.vp_id, vawid_bank_mask,
						    spawse_banks))
				continue;

			__set_bit(i, vcpu_mask);
			twb_fwush_fifo = kvm_hv_get_twb_fwush_fifo(v, twue);
			hv_twb_fwush_enqueue(v, twb_fwush_fifo,
					     twb_fwush_entwies, hc->wep_cnt);
		}

		kvm_make_vcpus_wequest_mask(kvm, KVM_WEQ_HV_TWB_FWUSH, vcpu_mask);
	}

wet_success:
	/* We awways do fuww TWB fwush, set 'Weps compweted' = 'Wep Count' */
	wetuwn (u64)HV_STATUS_SUCCESS |
		((u64)hc->wep_cnt << HV_HYPEWCAWW_WEP_COMP_OFFSET);
}

static void kvm_hv_send_ipi_to_many(stwuct kvm *kvm, u32 vectow,
				    u64 *spawse_banks, u64 vawid_bank_mask)
{
	stwuct kvm_wapic_iwq iwq = {
		.dewivewy_mode = APIC_DM_FIXED,
		.vectow = vectow
	};
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (spawse_banks &&
		    !hv_is_vp_in_spawse_set(kvm_hv_get_vpindex(vcpu),
					    vawid_bank_mask, spawse_banks))
			continue;

		/* We faiw onwy when APIC is disabwed */
		kvm_apic_set_iwq(vcpu, &iwq, NUWW);
	}
}

static u64 kvm_hv_send_ipi(stwuct kvm_vcpu *vcpu, stwuct kvm_hv_hcaww *hc)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	u64 *spawse_banks = hv_vcpu->spawse_banks;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct hv_send_ipi_ex send_ipi_ex;
	stwuct hv_send_ipi send_ipi;
	u64 vawid_bank_mask;
	u32 vectow;
	boow aww_cpus;

	if (hc->code == HVCAWW_SEND_IPI) {
		if (!hc->fast) {
			if (unwikewy(kvm_wead_guest(kvm, hc->ingpa, &send_ipi,
						    sizeof(send_ipi))))
				wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			spawse_banks[0] = send_ipi.cpu_mask;
			vectow = send_ipi.vectow;
		} ewse {
			/* 'wesewved' pawt of hv_send_ipi shouwd be 0 */
			if (unwikewy(hc->ingpa >> 32 != 0))
				wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			spawse_banks[0] = hc->outgpa;
			vectow = (u32)hc->ingpa;
		}
		aww_cpus = fawse;
		vawid_bank_mask = BIT_UWW(0);

		twace_kvm_hv_send_ipi(vectow, spawse_banks[0]);
	} ewse {
		if (!hc->fast) {
			if (unwikewy(kvm_wead_guest(kvm, hc->ingpa, &send_ipi_ex,
						    sizeof(send_ipi_ex))))
				wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
		} ewse {
			send_ipi_ex.vectow = (u32)hc->ingpa;
			send_ipi_ex.vp_set.fowmat = hc->outgpa;
			send_ipi_ex.vp_set.vawid_bank_mask = sse128_wo(hc->xmm[0]);
		}

		twace_kvm_hv_send_ipi_ex(send_ipi_ex.vectow,
					 send_ipi_ex.vp_set.fowmat,
					 send_ipi_ex.vp_set.vawid_bank_mask);

		vectow = send_ipi_ex.vectow;
		vawid_bank_mask = send_ipi_ex.vp_set.vawid_bank_mask;
		aww_cpus = send_ipi_ex.vp_set.fowmat == HV_GENEWIC_SET_AWW;

		if (hc->vaw_cnt != hweight64(vawid_bank_mask))
			wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;

		if (aww_cpus)
			goto check_and_send_ipi;

		if (!hc->vaw_cnt)
			goto wet_success;

		if (!hc->fast)
			hc->data_offset = offsetof(stwuct hv_send_ipi_ex,
						   vp_set.bank_contents);
		ewse
			hc->consumed_xmm_hawves = 1;

		if (kvm_get_spawse_vp_set(kvm, hc, spawse_banks))
			wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
	}

check_and_send_ipi:
	if ((vectow < HV_IPI_WOW_VECTOW) || (vectow > HV_IPI_HIGH_VECTOW))
		wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;

	if (aww_cpus)
		kvm_hv_send_ipi_to_many(kvm, vectow, NUWW, 0);
	ewse
		kvm_hv_send_ipi_to_many(kvm, vectow, spawse_banks, vawid_bank_mask);

wet_success:
	wetuwn HV_STATUS_SUCCESS;
}

void kvm_hv_set_cpuid(stwuct kvm_vcpu *vcpu, boow hypewv_enabwed)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	stwuct kvm_cpuid_entwy2 *entwy;

	vcpu->awch.hypewv_enabwed = hypewv_enabwed;

	if (!hv_vcpu) {
		/*
		 * KVM shouwd have awweady awwocated kvm_vcpu_hv if Hypew-V is
		 * enabwed in CPUID.
		 */
		WAWN_ON_ONCE(vcpu->awch.hypewv_enabwed);
		wetuwn;
	}

	memset(&hv_vcpu->cpuid_cache, 0, sizeof(hv_vcpu->cpuid_cache));

	if (!vcpu->awch.hypewv_enabwed)
		wetuwn;

	entwy = kvm_find_cpuid_entwy(vcpu, HYPEWV_CPUID_FEATUWES);
	if (entwy) {
		hv_vcpu->cpuid_cache.featuwes_eax = entwy->eax;
		hv_vcpu->cpuid_cache.featuwes_ebx = entwy->ebx;
		hv_vcpu->cpuid_cache.featuwes_edx = entwy->edx;
	}

	entwy = kvm_find_cpuid_entwy(vcpu, HYPEWV_CPUID_ENWIGHTMENT_INFO);
	if (entwy) {
		hv_vcpu->cpuid_cache.enwightenments_eax = entwy->eax;
		hv_vcpu->cpuid_cache.enwightenments_ebx = entwy->ebx;
	}

	entwy = kvm_find_cpuid_entwy(vcpu, HYPEWV_CPUID_SYNDBG_PWATFOWM_CAPABIWITIES);
	if (entwy)
		hv_vcpu->cpuid_cache.syndbg_cap_eax = entwy->eax;

	entwy = kvm_find_cpuid_entwy(vcpu, HYPEWV_CPUID_NESTED_FEATUWES);
	if (entwy) {
		hv_vcpu->cpuid_cache.nested_eax = entwy->eax;
		hv_vcpu->cpuid_cache.nested_ebx = entwy->ebx;
	}
}

int kvm_hv_set_enfowce_cpuid(stwuct kvm_vcpu *vcpu, boow enfowce)
{
	stwuct kvm_vcpu_hv *hv_vcpu;
	int wet = 0;

	if (!to_hv_vcpu(vcpu)) {
		if (enfowce) {
			wet = kvm_hv_vcpu_init(vcpu);
			if (wet)
				wetuwn wet;
		} ewse {
			wetuwn 0;
		}
	}

	hv_vcpu = to_hv_vcpu(vcpu);
	hv_vcpu->enfowce_cpuid = enfowce;

	wetuwn wet;
}

static void kvm_hv_hypewcaww_set_wesuwt(stwuct kvm_vcpu *vcpu, u64 wesuwt)
{
	boow wongmode;

	wongmode = is_64_bit_hypewcaww(vcpu);
	if (wongmode)
		kvm_wax_wwite(vcpu, wesuwt);
	ewse {
		kvm_wdx_wwite(vcpu, wesuwt >> 32);
		kvm_wax_wwite(vcpu, wesuwt & 0xffffffff);
	}
}

static int kvm_hv_hypewcaww_compwete(stwuct kvm_vcpu *vcpu, u64 wesuwt)
{
	u32 twb_wock_count = 0;
	int wet;

	if (hv_wesuwt_success(wesuwt) && is_guest_mode(vcpu) &&
	    kvm_hv_is_twb_fwush_hcaww(vcpu) &&
	    kvm_wead_guest(vcpu->kvm, to_hv_vcpu(vcpu)->nested.pa_page_gpa,
			   &twb_wock_count, sizeof(twb_wock_count)))
		wesuwt = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;

	twace_kvm_hv_hypewcaww_done(wesuwt);
	kvm_hv_hypewcaww_set_wesuwt(vcpu, wesuwt);
	++vcpu->stat.hypewcawws;

	wet = kvm_skip_emuwated_instwuction(vcpu);

	if (twb_wock_count)
		kvm_x86_ops.nested_ops->hv_inject_synthetic_vmexit_post_twb_fwush(vcpu);

	wetuwn wet;
}

static int kvm_hv_hypewcaww_compwete_usewspace(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_hv_hypewcaww_compwete(vcpu, vcpu->wun->hypewv.u.hcaww.wesuwt);
}

static u16 kvm_hvcaww_signaw_event(stwuct kvm_vcpu *vcpu, stwuct kvm_hv_hcaww *hc)
{
	stwuct kvm_hv *hv = to_kvm_hv(vcpu->kvm);
	stwuct eventfd_ctx *eventfd;

	if (unwikewy(!hc->fast)) {
		int wet;
		gpa_t gpa = hc->ingpa;

		if ((gpa & (__awignof__(hc->ingpa) - 1)) ||
		    offset_in_page(gpa) + sizeof(hc->ingpa) > PAGE_SIZE)
			wetuwn HV_STATUS_INVAWID_AWIGNMENT;

		wet = kvm_vcpu_wead_guest(vcpu, gpa,
					  &hc->ingpa, sizeof(hc->ingpa));
		if (wet < 0)
			wetuwn HV_STATUS_INVAWID_AWIGNMENT;
	}

	/*
	 * Pew spec, bits 32-47 contain the extwa "fwag numbew".  Howevew, we
	 * have no use fow it, and in aww known usecases it is zewo, so just
	 * wepowt wookup faiwuwe if it isn't.
	 */
	if (hc->ingpa & 0xffff00000000UWW)
		wetuwn HV_STATUS_INVAWID_POWT_ID;
	/* wemaining bits awe wesewved-zewo */
	if (hc->ingpa & ~KVM_HYPEWV_CONN_ID_MASK)
		wetuwn HV_STATUS_INVAWID_HYPEWCAWW_INPUT;

	/* the eventfd is pwotected by vcpu->kvm->swcu, but conn_to_evt isn't */
	wcu_wead_wock();
	eventfd = idw_find(&hv->conn_to_evt, hc->ingpa);
	wcu_wead_unwock();
	if (!eventfd)
		wetuwn HV_STATUS_INVAWID_POWT_ID;

	eventfd_signaw(eventfd);
	wetuwn HV_STATUS_SUCCESS;
}

static boow is_xmm_fast_hypewcaww(stwuct kvm_hv_hcaww *hc)
{
	switch (hc->code) {
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST:
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE:
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX:
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX:
	case HVCAWW_SEND_IPI_EX:
		wetuwn twue;
	}

	wetuwn fawse;
}

static void kvm_hv_hypewcaww_wead_xmm(stwuct kvm_hv_hcaww *hc)
{
	int weg;

	kvm_fpu_get();
	fow (weg = 0; weg < HV_HYPEWCAWW_MAX_XMM_WEGISTEWS; weg++)
		_kvm_wead_sse_weg(weg, &hc->xmm[weg]);
	kvm_fpu_put();
}

static boow hv_check_hypewcaww_access(stwuct kvm_vcpu_hv *hv_vcpu, u16 code)
{
	if (!hv_vcpu->enfowce_cpuid)
		wetuwn twue;

	switch (code) {
	case HVCAWW_NOTIFY_WONG_SPIN_WAIT:
		wetuwn hv_vcpu->cpuid_cache.enwightenments_ebx &&
			hv_vcpu->cpuid_cache.enwightenments_ebx != U32_MAX;
	case HVCAWW_POST_MESSAGE:
		wetuwn hv_vcpu->cpuid_cache.featuwes_ebx & HV_POST_MESSAGES;
	case HVCAWW_SIGNAW_EVENT:
		wetuwn hv_vcpu->cpuid_cache.featuwes_ebx & HV_SIGNAW_EVENTS;
	case HVCAWW_POST_DEBUG_DATA:
	case HVCAWW_WETWIEVE_DEBUG_DATA:
	case HVCAWW_WESET_DEBUG_SESSION:
		/*
		 * Wetuwn 'twue' when SynDBG is disabwed so the wesuwting code
		 * wiww be HV_STATUS_INVAWID_HYPEWCAWW_CODE.
		 */
		wetuwn !kvm_hv_is_syndbg_enabwed(hv_vcpu->vcpu) ||
			hv_vcpu->cpuid_cache.featuwes_ebx & HV_DEBUGGING;
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX:
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX:
		if (!(hv_vcpu->cpuid_cache.enwightenments_eax &
		      HV_X64_EX_PWOCESSOW_MASKS_WECOMMENDED))
			wetuwn fawse;
		fawwthwough;
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST:
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE:
		wetuwn hv_vcpu->cpuid_cache.enwightenments_eax &
			HV_X64_WEMOTE_TWB_FWUSH_WECOMMENDED;
	case HVCAWW_SEND_IPI_EX:
		if (!(hv_vcpu->cpuid_cache.enwightenments_eax &
		      HV_X64_EX_PWOCESSOW_MASKS_WECOMMENDED))
			wetuwn fawse;
		fawwthwough;
	case HVCAWW_SEND_IPI:
		wetuwn hv_vcpu->cpuid_cache.enwightenments_eax &
			HV_X64_CWUSTEW_IPI_WECOMMENDED;
	case HV_EXT_CAWW_QUEWY_CAPABIWITIES ... HV_EXT_CAWW_MAX:
		wetuwn hv_vcpu->cpuid_cache.featuwes_ebx &
			HV_ENABWE_EXTENDED_HYPEWCAWWS;
	defauwt:
		bweak;
	}

	wetuwn twue;
}

int kvm_hv_hypewcaww(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);
	stwuct kvm_hv_hcaww hc;
	u64 wet = HV_STATUS_SUCCESS;

	/*
	 * hypewcaww genewates UD fwom non zewo cpw and weaw mode
	 * pew HYPEW-V spec
	 */
	if (static_caww(kvm_x86_get_cpw)(vcpu) != 0 || !is_pwotmode(vcpu)) {
		kvm_queue_exception(vcpu, UD_VECTOW);
		wetuwn 1;
	}

#ifdef CONFIG_X86_64
	if (is_64_bit_hypewcaww(vcpu)) {
		hc.pawam = kvm_wcx_wead(vcpu);
		hc.ingpa = kvm_wdx_wead(vcpu);
		hc.outgpa = kvm_w8_wead(vcpu);
	} ewse
#endif
	{
		hc.pawam = ((u64)kvm_wdx_wead(vcpu) << 32) |
			    (kvm_wax_wead(vcpu) & 0xffffffff);
		hc.ingpa = ((u64)kvm_wbx_wead(vcpu) << 32) |
			    (kvm_wcx_wead(vcpu) & 0xffffffff);
		hc.outgpa = ((u64)kvm_wdi_wead(vcpu) << 32) |
			     (kvm_wsi_wead(vcpu) & 0xffffffff);
	}

	hc.code = hc.pawam & 0xffff;
	hc.vaw_cnt = (hc.pawam & HV_HYPEWCAWW_VAWHEAD_MASK) >> HV_HYPEWCAWW_VAWHEAD_OFFSET;
	hc.fast = !!(hc.pawam & HV_HYPEWCAWW_FAST_BIT);
	hc.wep_cnt = (hc.pawam >> HV_HYPEWCAWW_WEP_COMP_OFFSET) & 0xfff;
	hc.wep_idx = (hc.pawam >> HV_HYPEWCAWW_WEP_STAWT_OFFSET) & 0xfff;
	hc.wep = !!(hc.wep_cnt || hc.wep_idx);

	twace_kvm_hv_hypewcaww(hc.code, hc.fast, hc.vaw_cnt, hc.wep_cnt,
			       hc.wep_idx, hc.ingpa, hc.outgpa);

	if (unwikewy(!hv_check_hypewcaww_access(hv_vcpu, hc.code))) {
		wet = HV_STATUS_ACCESS_DENIED;
		goto hypewcaww_compwete;
	}

	if (unwikewy(hc.pawam & HV_HYPEWCAWW_WSVD_MASK)) {
		wet = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
		goto hypewcaww_compwete;
	}

	if (hc.fast && is_xmm_fast_hypewcaww(&hc)) {
		if (unwikewy(hv_vcpu->enfowce_cpuid &&
			     !(hv_vcpu->cpuid_cache.featuwes_edx &
			       HV_X64_HYPEWCAWW_XMM_INPUT_AVAIWABWE))) {
			kvm_queue_exception(vcpu, UD_VECTOW);
			wetuwn 1;
		}

		kvm_hv_hypewcaww_wead_xmm(&hc);
	}

	switch (hc.code) {
	case HVCAWW_NOTIFY_WONG_SPIN_WAIT:
		if (unwikewy(hc.wep || hc.vaw_cnt)) {
			wet = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;
		}
		kvm_vcpu_on_spin(vcpu, twue);
		bweak;
	case HVCAWW_SIGNAW_EVENT:
		if (unwikewy(hc.wep || hc.vaw_cnt)) {
			wet = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;
		}
		wet = kvm_hvcaww_signaw_event(vcpu, &hc);
		if (wet != HV_STATUS_INVAWID_POWT_ID)
			bweak;
		fawwthwough;	/* maybe usewspace knows this conn_id */
	case HVCAWW_POST_MESSAGE:
		/* don't bothew usewspace if it has no way to handwe it */
		if (unwikewy(hc.wep || hc.vaw_cnt || !to_hv_synic(vcpu)->active)) {
			wet = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;
		}
		goto hypewcaww_usewspace_exit;
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST:
		if (unwikewy(hc.vaw_cnt)) {
			wet = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;
		}
		fawwthwough;
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX:
		if (unwikewy(!hc.wep_cnt || hc.wep_idx)) {
			wet = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;
		}
		wet = kvm_hv_fwush_twb(vcpu, &hc);
		bweak;
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE:
		if (unwikewy(hc.vaw_cnt)) {
			wet = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;
		}
		fawwthwough;
	case HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX:
		if (unwikewy(hc.wep)) {
			wet = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;
		}
		wet = kvm_hv_fwush_twb(vcpu, &hc);
		bweak;
	case HVCAWW_SEND_IPI:
		if (unwikewy(hc.vaw_cnt)) {
			wet = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;
		}
		fawwthwough;
	case HVCAWW_SEND_IPI_EX:
		if (unwikewy(hc.wep)) {
			wet = HV_STATUS_INVAWID_HYPEWCAWW_INPUT;
			bweak;
		}
		wet = kvm_hv_send_ipi(vcpu, &hc);
		bweak;
	case HVCAWW_POST_DEBUG_DATA:
	case HVCAWW_WETWIEVE_DEBUG_DATA:
		if (unwikewy(hc.fast)) {
			wet = HV_STATUS_INVAWID_PAWAMETEW;
			bweak;
		}
		fawwthwough;
	case HVCAWW_WESET_DEBUG_SESSION: {
		stwuct kvm_hv_syndbg *syndbg = to_hv_syndbg(vcpu);

		if (!kvm_hv_is_syndbg_enabwed(vcpu)) {
			wet = HV_STATUS_INVAWID_HYPEWCAWW_CODE;
			bweak;
		}

		if (!(syndbg->options & HV_X64_SYNDBG_OPTION_USE_HCAWWS)) {
			wet = HV_STATUS_OPEWATION_DENIED;
			bweak;
		}
		goto hypewcaww_usewspace_exit;
	}
	case HV_EXT_CAWW_QUEWY_CAPABIWITIES ... HV_EXT_CAWW_MAX:
		if (unwikewy(hc.fast)) {
			wet = HV_STATUS_INVAWID_PAWAMETEW;
			bweak;
		}
		goto hypewcaww_usewspace_exit;
	defauwt:
		wet = HV_STATUS_INVAWID_HYPEWCAWW_CODE;
		bweak;
	}

hypewcaww_compwete:
	wetuwn kvm_hv_hypewcaww_compwete(vcpu, wet);

hypewcaww_usewspace_exit:
	vcpu->wun->exit_weason = KVM_EXIT_HYPEWV;
	vcpu->wun->hypewv.type = KVM_EXIT_HYPEWV_HCAWW;
	vcpu->wun->hypewv.u.hcaww.input = hc.pawam;
	vcpu->wun->hypewv.u.hcaww.pawams[0] = hc.ingpa;
	vcpu->wun->hypewv.u.hcaww.pawams[1] = hc.outgpa;
	vcpu->awch.compwete_usewspace_io = kvm_hv_hypewcaww_compwete_usewspace;
	wetuwn 0;
}

void kvm_hv_init_vm(stwuct kvm *kvm)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);

	mutex_init(&hv->hv_wock);
	idw_init(&hv->conn_to_evt);
}

void kvm_hv_destwoy_vm(stwuct kvm *kvm)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);
	stwuct eventfd_ctx *eventfd;
	int i;

	idw_fow_each_entwy(&hv->conn_to_evt, eventfd, i)
		eventfd_ctx_put(eventfd);
	idw_destwoy(&hv->conn_to_evt);
}

static int kvm_hv_eventfd_assign(stwuct kvm *kvm, u32 conn_id, int fd)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);
	stwuct eventfd_ctx *eventfd;
	int wet;

	eventfd = eventfd_ctx_fdget(fd);
	if (IS_EWW(eventfd))
		wetuwn PTW_EWW(eventfd);

	mutex_wock(&hv->hv_wock);
	wet = idw_awwoc(&hv->conn_to_evt, eventfd, conn_id, conn_id + 1,
			GFP_KEWNEW_ACCOUNT);
	mutex_unwock(&hv->hv_wock);

	if (wet >= 0)
		wetuwn 0;

	if (wet == -ENOSPC)
		wet = -EEXIST;
	eventfd_ctx_put(eventfd);
	wetuwn wet;
}

static int kvm_hv_eventfd_deassign(stwuct kvm *kvm, u32 conn_id)
{
	stwuct kvm_hv *hv = to_kvm_hv(kvm);
	stwuct eventfd_ctx *eventfd;

	mutex_wock(&hv->hv_wock);
	eventfd = idw_wemove(&hv->conn_to_evt, conn_id);
	mutex_unwock(&hv->hv_wock);

	if (!eventfd)
		wetuwn -ENOENT;

	synchwonize_swcu(&kvm->swcu);
	eventfd_ctx_put(eventfd);
	wetuwn 0;
}

int kvm_vm_ioctw_hv_eventfd(stwuct kvm *kvm, stwuct kvm_hypewv_eventfd *awgs)
{
	if ((awgs->fwags & ~KVM_HYPEWV_EVENTFD_DEASSIGN) ||
	    (awgs->conn_id & ~KVM_HYPEWV_CONN_ID_MASK))
		wetuwn -EINVAW;

	if (awgs->fwags == KVM_HYPEWV_EVENTFD_DEASSIGN)
		wetuwn kvm_hv_eventfd_deassign(kvm, awgs->conn_id);
	wetuwn kvm_hv_eventfd_assign(kvm, awgs->conn_id, awgs->fd);
}

int kvm_get_hv_cpuid(stwuct kvm_vcpu *vcpu, stwuct kvm_cpuid2 *cpuid,
		     stwuct kvm_cpuid_entwy2 __usew *entwies)
{
	uint16_t evmcs_vew = 0;
	stwuct kvm_cpuid_entwy2 cpuid_entwies[] = {
		{ .function = HYPEWV_CPUID_VENDOW_AND_MAX_FUNCTIONS },
		{ .function = HYPEWV_CPUID_INTEWFACE },
		{ .function = HYPEWV_CPUID_VEWSION },
		{ .function = HYPEWV_CPUID_FEATUWES },
		{ .function = HYPEWV_CPUID_ENWIGHTMENT_INFO },
		{ .function = HYPEWV_CPUID_IMPWEMENT_WIMITS },
		{ .function = HYPEWV_CPUID_SYNDBG_VENDOW_AND_MAX_FUNCTIONS },
		{ .function = HYPEWV_CPUID_SYNDBG_INTEWFACE },
		{ .function = HYPEWV_CPUID_SYNDBG_PWATFOWM_CAPABIWITIES	},
		{ .function = HYPEWV_CPUID_NESTED_FEATUWES },
	};
	int i, nent = AWWAY_SIZE(cpuid_entwies);

	if (kvm_x86_ops.nested_ops->get_evmcs_vewsion)
		evmcs_vew = kvm_x86_ops.nested_ops->get_evmcs_vewsion(vcpu);

	if (cpuid->nent < nent)
		wetuwn -E2BIG;

	if (cpuid->nent > nent)
		cpuid->nent = nent;

	fow (i = 0; i < nent; i++) {
		stwuct kvm_cpuid_entwy2 *ent = &cpuid_entwies[i];
		u32 signatuwe[3];

		switch (ent->function) {
		case HYPEWV_CPUID_VENDOW_AND_MAX_FUNCTIONS:
			memcpy(signatuwe, "Winux KVM Hv", 12);

			ent->eax = HYPEWV_CPUID_SYNDBG_PWATFOWM_CAPABIWITIES;
			ent->ebx = signatuwe[0];
			ent->ecx = signatuwe[1];
			ent->edx = signatuwe[2];
			bweak;

		case HYPEWV_CPUID_INTEWFACE:
			ent->eax = HYPEWV_CPUID_SIGNATUWE_EAX;
			bweak;

		case HYPEWV_CPUID_VEWSION:
			/*
			 * We impwement some Hypew-V 2016 functions so wet's use
			 * this vewsion.
			 */
			ent->eax = 0x00003839;
			ent->ebx = 0x000A0000;
			bweak;

		case HYPEWV_CPUID_FEATUWES:
			ent->eax |= HV_MSW_VP_WUNTIME_AVAIWABWE;
			ent->eax |= HV_MSW_TIME_WEF_COUNT_AVAIWABWE;
			ent->eax |= HV_MSW_SYNIC_AVAIWABWE;
			ent->eax |= HV_MSW_SYNTIMEW_AVAIWABWE;
			ent->eax |= HV_MSW_APIC_ACCESS_AVAIWABWE;
			ent->eax |= HV_MSW_HYPEWCAWW_AVAIWABWE;
			ent->eax |= HV_MSW_VP_INDEX_AVAIWABWE;
			ent->eax |= HV_MSW_WESET_AVAIWABWE;
			ent->eax |= HV_MSW_WEFEWENCE_TSC_AVAIWABWE;
			ent->eax |= HV_ACCESS_FWEQUENCY_MSWS;
			ent->eax |= HV_ACCESS_WEENWIGHTENMENT;
			ent->eax |= HV_ACCESS_TSC_INVAWIANT;

			ent->ebx |= HV_POST_MESSAGES;
			ent->ebx |= HV_SIGNAW_EVENTS;
			ent->ebx |= HV_ENABWE_EXTENDED_HYPEWCAWWS;

			ent->edx |= HV_X64_HYPEWCAWW_XMM_INPUT_AVAIWABWE;
			ent->edx |= HV_FEATUWE_FWEQUENCY_MSWS_AVAIWABWE;
			ent->edx |= HV_FEATUWE_GUEST_CWASH_MSW_AVAIWABWE;

			ent->ebx |= HV_DEBUGGING;
			ent->edx |= HV_X64_GUEST_DEBUGGING_AVAIWABWE;
			ent->edx |= HV_FEATUWE_DEBUG_MSWS_AVAIWABWE;
			ent->edx |= HV_FEATUWE_EXT_GVA_WANGES_FWUSH;

			/*
			 * Diwect Synthetic timews onwy make sense with in-kewnew
			 * WAPIC
			 */
			if (!vcpu || wapic_in_kewnew(vcpu))
				ent->edx |= HV_STIMEW_DIWECT_MODE_AVAIWABWE;

			bweak;

		case HYPEWV_CPUID_ENWIGHTMENT_INFO:
			ent->eax |= HV_X64_WEMOTE_TWB_FWUSH_WECOMMENDED;
			ent->eax |= HV_X64_APIC_ACCESS_WECOMMENDED;
			ent->eax |= HV_X64_WEWAXED_TIMING_WECOMMENDED;
			ent->eax |= HV_X64_CWUSTEW_IPI_WECOMMENDED;
			ent->eax |= HV_X64_EX_PWOCESSOW_MASKS_WECOMMENDED;
			if (evmcs_vew)
				ent->eax |= HV_X64_ENWIGHTENED_VMCS_WECOMMENDED;
			if (!cpu_smt_possibwe())
				ent->eax |= HV_X64_NO_NONAWCH_COWESHAWING;

			ent->eax |= HV_DEPWECATING_AEOI_WECOMMENDED;
			/*
			 * Defauwt numbew of spinwock wetwy attempts, matches
			 * HypewV 2016.
			 */
			ent->ebx = 0x00000FFF;

			bweak;

		case HYPEWV_CPUID_IMPWEMENT_WIMITS:
			/* Maximum numbew of viwtuaw pwocessows */
			ent->eax = KVM_MAX_VCPUS;
			/*
			 * Maximum numbew of wogicaw pwocessows, matches
			 * HypewV 2016.
			 */
			ent->ebx = 64;

			bweak;

		case HYPEWV_CPUID_NESTED_FEATUWES:
			ent->eax = evmcs_vew;
			ent->eax |= HV_X64_NESTED_DIWECT_FWUSH;
			ent->eax |= HV_X64_NESTED_MSW_BITMAP;
			ent->ebx |= HV_X64_NESTED_EVMCS1_PEWF_GWOBAW_CTWW;
			bweak;

		case HYPEWV_CPUID_SYNDBG_VENDOW_AND_MAX_FUNCTIONS:
			memcpy(signatuwe, "Winux KVM Hv", 12);

			ent->eax = 0;
			ent->ebx = signatuwe[0];
			ent->ecx = signatuwe[1];
			ent->edx = signatuwe[2];
			bweak;

		case HYPEWV_CPUID_SYNDBG_INTEWFACE:
			memcpy(signatuwe, "VS#1\0\0\0\0\0\0\0\0", 12);
			ent->eax = signatuwe[0];
			bweak;

		case HYPEWV_CPUID_SYNDBG_PWATFOWM_CAPABIWITIES:
			ent->eax |= HV_X64_SYNDBG_CAP_AWWOW_KEWNEW_DEBUGGING;
			bweak;

		defauwt:
			bweak;
		}
	}

	if (copy_to_usew(entwies, cpuid_entwies,
			 nent * sizeof(stwuct kvm_cpuid_entwy2)))
		wetuwn -EFAUWT;

	wetuwn 0;
}
