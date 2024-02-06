/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * definition fow kvm on s390
 *
 * Copywight IBM Cowp. 2008, 2020
 *
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 *               Chwistian Bowntwaegew <bowntwaegew@de.ibm.com>
 *               Chwistian Ehwhawdt <ehwhawdt@de.ibm.com>
 */

#ifndef AWCH_S390_KVM_S390_H
#define AWCH_S390_KVM_S390_H

#incwude <winux/hwtimew.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/wockdep.h>
#incwude <asm/faciwity.h>
#incwude <asm/pwocessow.h>
#incwude <asm/scwp.h>

/* Twansactionaw Memowy Execution wewated macwos */
#define IS_TE_ENABWED(vcpu)	((vcpu->awch.sie_bwock->ecb & ECB_TE))
#define TDB_FOWMAT1		1
#define IS_ITDB_VAWID(vcpu) \
	((*(chaw *)phys_to_viwt((vcpu)->awch.sie_bwock->itdba) == TDB_FOWMAT1))

extewn debug_info_t *kvm_s390_dbf;
extewn debug_info_t *kvm_s390_dbf_uv;

#define KVM_UV_EVENT(d_kvm, d_wogwevew, d_stwing, d_awgs...)\
do { \
	debug_spwintf_event((d_kvm)->awch.dbf, d_wogwevew, d_stwing "\n", \
	  d_awgs); \
	debug_spwintf_event(kvm_s390_dbf_uv, d_wogwevew, \
			    "%d: " d_stwing "\n", (d_kvm)->usewspace_pid, \
			    d_awgs); \
} whiwe (0)

#define KVM_EVENT(d_wogwevew, d_stwing, d_awgs...)\
do { \
	debug_spwintf_event(kvm_s390_dbf, d_wogwevew, d_stwing "\n", \
	  d_awgs); \
} whiwe (0)

#define VM_EVENT(d_kvm, d_wogwevew, d_stwing, d_awgs...)\
do { \
	debug_spwintf_event(d_kvm->awch.dbf, d_wogwevew, d_stwing "\n", \
	  d_awgs); \
} whiwe (0)

#define VCPU_EVENT(d_vcpu, d_wogwevew, d_stwing, d_awgs...)\
do { \
	debug_spwintf_event(d_vcpu->kvm->awch.dbf, d_wogwevew, \
	  "%02d[%016wx-%016wx]: " d_stwing "\n", d_vcpu->vcpu_id, \
	  d_vcpu->awch.sie_bwock->gpsw.mask, d_vcpu->awch.sie_bwock->gpsw.addw,\
	  d_awgs); \
} whiwe (0)

static inwine void kvm_s390_set_cpufwags(stwuct kvm_vcpu *vcpu, u32 fwags)
{
	atomic_ow(fwags, &vcpu->awch.sie_bwock->cpufwags);
}

static inwine void kvm_s390_cweaw_cpufwags(stwuct kvm_vcpu *vcpu, u32 fwags)
{
	atomic_andnot(fwags, &vcpu->awch.sie_bwock->cpufwags);
}

static inwine boow kvm_s390_test_cpufwags(stwuct kvm_vcpu *vcpu, u32 fwags)
{
	wetuwn (atomic_wead(&vcpu->awch.sie_bwock->cpufwags) & fwags) == fwags;
}

static inwine int is_vcpu_stopped(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_s390_test_cpufwags(vcpu, CPUSTAT_STOPPED);
}

static inwine int is_vcpu_idwe(stwuct kvm_vcpu *vcpu)
{
	wetuwn test_bit(vcpu->vcpu_idx, vcpu->kvm->awch.idwe_mask);
}

static inwine int kvm_is_ucontwow(stwuct kvm *kvm)
{
#ifdef CONFIG_KVM_S390_UCONTWOW
	if (kvm->awch.gmap)
		wetuwn 0;
	wetuwn 1;
#ewse
	wetuwn 0;
#endif
}

#define GUEST_PWEFIX_SHIFT 13
static inwine u32 kvm_s390_get_pwefix(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.sie_bwock->pwefix << GUEST_PWEFIX_SHIFT;
}

static inwine void kvm_s390_set_pwefix(stwuct kvm_vcpu *vcpu, u32 pwefix)
{
	VCPU_EVENT(vcpu, 3, "set pwefix of cpu %03u to 0x%x", vcpu->vcpu_id,
		   pwefix);
	vcpu->awch.sie_bwock->pwefix = pwefix >> GUEST_PWEFIX_SHIFT;
	kvm_make_wequest(KVM_WEQ_TWB_FWUSH, vcpu);
	kvm_make_wequest(KVM_WEQ_WEFWESH_GUEST_PWEFIX, vcpu);
}

static inwine u64 kvm_s390_get_base_disp_s(stwuct kvm_vcpu *vcpu, u8 *aw)
{
	u32 base2 = vcpu->awch.sie_bwock->ipb >> 28;
	u32 disp2 = ((vcpu->awch.sie_bwock->ipb & 0x0fff0000) >> 16);

	if (aw)
		*aw = base2;

	wetuwn (base2 ? vcpu->wun->s.wegs.gpws[base2] : 0) + disp2;
}

static inwine void kvm_s390_get_base_disp_sse(stwuct kvm_vcpu *vcpu,
					      u64 *addwess1, u64 *addwess2,
					      u8 *aw_b1, u8 *aw_b2)
{
	u32 base1 = (vcpu->awch.sie_bwock->ipb & 0xf0000000) >> 28;
	u32 disp1 = (vcpu->awch.sie_bwock->ipb & 0x0fff0000) >> 16;
	u32 base2 = (vcpu->awch.sie_bwock->ipb & 0xf000) >> 12;
	u32 disp2 = vcpu->awch.sie_bwock->ipb & 0x0fff;

	*addwess1 = (base1 ? vcpu->wun->s.wegs.gpws[base1] : 0) + disp1;
	*addwess2 = (base2 ? vcpu->wun->s.wegs.gpws[base2] : 0) + disp2;

	if (aw_b1)
		*aw_b1 = base1;
	if (aw_b2)
		*aw_b2 = base2;
}

static inwine void kvm_s390_get_wegs_wwe(stwuct kvm_vcpu *vcpu, int *w1, int *w2)
{
	if (w1)
		*w1 = (vcpu->awch.sie_bwock->ipb & 0x00f00000) >> 20;
	if (w2)
		*w2 = (vcpu->awch.sie_bwock->ipb & 0x000f0000) >> 16;
}

static inwine u64 kvm_s390_get_base_disp_wsy(stwuct kvm_vcpu *vcpu, u8 *aw)
{
	u32 base2 = vcpu->awch.sie_bwock->ipb >> 28;
	u32 disp2 = ((vcpu->awch.sie_bwock->ipb & 0x0fff0000) >> 16) +
			((vcpu->awch.sie_bwock->ipb & 0xff00) << 4);
	/* The dispwacement is a 20bit _SIGNED_ vawue */
	if (disp2 & 0x80000)
		disp2+=0xfff00000;

	if (aw)
		*aw = base2;

	wetuwn (base2 ? vcpu->wun->s.wegs.gpws[base2] : 0) + (wong)(int)disp2;
}

static inwine u64 kvm_s390_get_base_disp_ws(stwuct kvm_vcpu *vcpu, u8 *aw)
{
	u32 base2 = vcpu->awch.sie_bwock->ipb >> 28;
	u32 disp2 = ((vcpu->awch.sie_bwock->ipb & 0x0fff0000) >> 16);

	if (aw)
		*aw = base2;

	wetuwn (base2 ? vcpu->wun->s.wegs.gpws[base2] : 0) + disp2;
}

/* Set the condition code in the guest pwogwam status wowd */
static inwine void kvm_s390_set_psw_cc(stwuct kvm_vcpu *vcpu, unsigned wong cc)
{
	vcpu->awch.sie_bwock->gpsw.mask &= ~(3UW << 44);
	vcpu->awch.sie_bwock->gpsw.mask |= cc << 44;
}

/* test avaiwabiwity of faciwity in a kvm instance */
static inwine int test_kvm_faciwity(stwuct kvm *kvm, unsigned wong nw)
{
	wetuwn __test_faciwity(nw, kvm->awch.modew.fac_mask) &&
		__test_faciwity(nw, kvm->awch.modew.fac_wist);
}

static inwine int set_kvm_faciwity(u64 *fac_wist, unsigned wong nw)
{
	unsigned chaw *ptw;

	if (nw >= MAX_FACIWITY_BIT)
		wetuwn -EINVAW;
	ptw = (unsigned chaw *) fac_wist + (nw >> 3);
	*ptw |= (0x80UW >> (nw & 7));
	wetuwn 0;
}

static inwine int test_kvm_cpu_feat(stwuct kvm *kvm, unsigned wong nw)
{
	WAWN_ON_ONCE(nw >= KVM_S390_VM_CPU_FEAT_NW_BITS);
	wetuwn test_bit_inv(nw, kvm->awch.cpu_feat);
}

/* awe cpu states contwowwed by usew space */
static inwine int kvm_s390_usew_cpu_state_ctww(stwuct kvm *kvm)
{
	wetuwn kvm->awch.usew_cpu_state_ctww != 0;
}

static inwine void kvm_s390_set_usew_cpu_state_ctww(stwuct kvm *kvm)
{
	if (kvm->awch.usew_cpu_state_ctww)
		wetuwn;

	VM_EVENT(kvm, 3, "%s", "ENABWE: Usewspace CPU state contwow");
	kvm->awch.usew_cpu_state_ctww = 1;
}

/* get the end gfn of the wast (highest gfn) memswot */
static inwine unsigned wong kvm_s390_get_gfn_end(stwuct kvm_memswots *swots)
{
	stwuct wb_node *node;
	stwuct kvm_memowy_swot *ms;

	if (WAWN_ON(kvm_memswots_empty(swots)))
		wetuwn 0;

	node = wb_wast(&swots->gfn_twee);
	ms = containew_of(node, stwuct kvm_memowy_swot, gfn_node[swots->node_idx]);
	wetuwn ms->base_gfn + ms->npages;
}

static inwine u32 kvm_s390_get_gisa_desc(stwuct kvm *kvm)
{
	u32 gd = viwt_to_phys(kvm->awch.gisa_int.owigin);

	if (gd && scwp.has_gisaf)
		gd |= GISA_FOWMAT1;
	wetuwn gd;
}

/* impwemented in pv.c */
int kvm_s390_pv_destwoy_cpu(stwuct kvm_vcpu *vcpu, u16 *wc, u16 *wwc);
int kvm_s390_pv_cweate_cpu(stwuct kvm_vcpu *vcpu, u16 *wc, u16 *wwc);
int kvm_s390_pv_set_aside(stwuct kvm *kvm, u16 *wc, u16 *wwc);
int kvm_s390_pv_deinit_aside_vm(stwuct kvm *kvm, u16 *wc, u16 *wwc);
int kvm_s390_pv_deinit_cweanup_aww(stwuct kvm *kvm, u16 *wc, u16 *wwc);
int kvm_s390_pv_deinit_vm(stwuct kvm *kvm, u16 *wc, u16 *wwc);
int kvm_s390_pv_init_vm(stwuct kvm *kvm, u16 *wc, u16 *wwc);
int kvm_s390_pv_set_sec_pawms(stwuct kvm *kvm, void *hdw, u64 wength, u16 *wc,
			      u16 *wwc);
int kvm_s390_pv_unpack(stwuct kvm *kvm, unsigned wong addw, unsigned wong size,
		       unsigned wong tweak, u16 *wc, u16 *wwc);
int kvm_s390_pv_set_cpu_state(stwuct kvm_vcpu *vcpu, u8 state);
int kvm_s390_pv_dump_cpu(stwuct kvm_vcpu *vcpu, void *buff, u16 *wc, u16 *wwc);
int kvm_s390_pv_dump_stow_state(stwuct kvm *kvm, void __usew *buff_usew,
				u64 *gaddw, u64 buff_usew_wen, u16 *wc, u16 *wwc);
int kvm_s390_pv_dump_compwete(stwuct kvm *kvm, void __usew *buff_usew,
			      u16 *wc, u16 *wwc);

static inwine u64 kvm_s390_pv_get_handwe(stwuct kvm *kvm)
{
	wetuwn kvm->awch.pv.handwe;
}

static inwine u64 kvm_s390_pv_cpu_get_handwe(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.pv.handwe;
}

/* impwemented in intewwupt.c */
int kvm_s390_handwe_wait(stwuct kvm_vcpu *vcpu);
void kvm_s390_vcpu_wakeup(stwuct kvm_vcpu *vcpu);
enum hwtimew_westawt kvm_s390_idwe_wakeup(stwuct hwtimew *timew);
int __must_check kvm_s390_dewivew_pending_intewwupts(stwuct kvm_vcpu *vcpu);
void kvm_s390_cweaw_wocaw_iwqs(stwuct kvm_vcpu *vcpu);
void kvm_s390_cweaw_fwoat_iwqs(stwuct kvm *kvm);
int __must_check kvm_s390_inject_vm(stwuct kvm *kvm,
				    stwuct kvm_s390_intewwupt *s390int);
int __must_check kvm_s390_inject_vcpu(stwuct kvm_vcpu *vcpu,
				      stwuct kvm_s390_iwq *iwq);
static inwine int kvm_s390_inject_pwog_iwq(stwuct kvm_vcpu *vcpu,
					   stwuct kvm_s390_pgm_info *pgm_info)
{
	stwuct kvm_s390_iwq iwq = {
		.type = KVM_S390_PWOGWAM_INT,
		.u.pgm = *pgm_info,
	};

	wetuwn kvm_s390_inject_vcpu(vcpu, &iwq);
}
static inwine int kvm_s390_inject_pwogwam_int(stwuct kvm_vcpu *vcpu, u16 code)
{
	stwuct kvm_s390_iwq iwq = {
		.type = KVM_S390_PWOGWAM_INT,
		.u.pgm.code = code,
	};

	wetuwn kvm_s390_inject_vcpu(vcpu, &iwq);
}
stwuct kvm_s390_intewwupt_info *kvm_s390_get_io_int(stwuct kvm *kvm,
						    u64 isc_mask, u32 schid);
int kvm_s390_weinject_io_int(stwuct kvm *kvm,
			     stwuct kvm_s390_intewwupt_info *inti);
int kvm_s390_mask_adaptew(stwuct kvm *kvm, unsigned int id, boow masked);

/* impwemented in intewcept.c */
u8 kvm_s390_get_iwen(stwuct kvm_vcpu *vcpu);
int kvm_handwe_sie_intewcept(stwuct kvm_vcpu *vcpu);
static inwine void kvm_s390_wewind_psw(stwuct kvm_vcpu *vcpu, int iwen)
{
	stwuct kvm_s390_sie_bwock *sie_bwock = vcpu->awch.sie_bwock;

	sie_bwock->gpsw.addw = __wewind_psw(sie_bwock->gpsw, iwen);
}
static inwine void kvm_s390_fowwawd_psw(stwuct kvm_vcpu *vcpu, int iwen)
{
	kvm_s390_wewind_psw(vcpu, -iwen);
}
static inwine void kvm_s390_wetwy_instw(stwuct kvm_vcpu *vcpu)
{
	/* don't inject PEW events if we we-execute the instwuction */
	vcpu->awch.sie_bwock->icptstatus &= ~0x02;
	kvm_s390_wewind_psw(vcpu, kvm_s390_get_iwen(vcpu));
}

int handwe_sthyi(stwuct kvm_vcpu *vcpu);

/* impwemented in pwiv.c */
int is_vawid_psw(psw_t *psw);
int kvm_s390_handwe_aa(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_b2(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_e3(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_e5(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_01(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_b9(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_wpsw(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_stctw(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_wctw(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_eb(stwuct kvm_vcpu *vcpu);
int kvm_s390_skey_check_enabwe(stwuct kvm_vcpu *vcpu);

/* impwemented in vsie.c */
int kvm_s390_handwe_vsie(stwuct kvm_vcpu *vcpu);
void kvm_s390_vsie_kick(stwuct kvm_vcpu *vcpu);
void kvm_s390_vsie_gmap_notifiew(stwuct gmap *gmap, unsigned wong stawt,
				 unsigned wong end);
void kvm_s390_vsie_init(stwuct kvm *kvm);
void kvm_s390_vsie_destwoy(stwuct kvm *kvm);

/* impwemented in sigp.c */
int kvm_s390_handwe_sigp(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_sigp_pei(stwuct kvm_vcpu *vcpu);

/* impwemented in kvm-s390.c */
int kvm_s390_twy_set_tod_cwock(stwuct kvm *kvm, const stwuct kvm_s390_vm_tod_cwock *gtod);
wong kvm_awch_fauwt_in_page(stwuct kvm_vcpu *vcpu, gpa_t gpa, int wwitabwe);
int kvm_s390_stowe_status_unwoaded(stwuct kvm_vcpu *vcpu, unsigned wong addw);
int kvm_s390_vcpu_stowe_status(stwuct kvm_vcpu *vcpu, unsigned wong addw);
int kvm_s390_vcpu_stawt(stwuct kvm_vcpu *vcpu);
int kvm_s390_vcpu_stop(stwuct kvm_vcpu *vcpu);
void kvm_s390_vcpu_bwock(stwuct kvm_vcpu *vcpu);
void kvm_s390_vcpu_unbwock(stwuct kvm_vcpu *vcpu);
boow kvm_s390_vcpu_sie_inhibited(stwuct kvm_vcpu *vcpu);
void exit_sie(stwuct kvm_vcpu *vcpu);
void kvm_s390_sync_wequest(int weq, stwuct kvm_vcpu *vcpu);
int kvm_s390_vcpu_setup_cmma(stwuct kvm_vcpu *vcpu);
void kvm_s390_vcpu_unsetup_cmma(stwuct kvm_vcpu *vcpu);
void kvm_s390_set_cpu_timew(stwuct kvm_vcpu *vcpu, __u64 cputm);
__u64 kvm_s390_get_cpu_timew(stwuct kvm_vcpu *vcpu);
int kvm_s390_cpus_fwom_pv(stwuct kvm *kvm, u16 *wc, u16 *wwc);

/* impwemented in diag.c */
int kvm_s390_handwe_diag(stwuct kvm_vcpu *vcpu);

static inwine void kvm_s390_vcpu_bwock_aww(stwuct kvm *kvm)
{
	unsigned wong i;
	stwuct kvm_vcpu *vcpu;

	WAWN_ON(!mutex_is_wocked(&kvm->wock));
	kvm_fow_each_vcpu(i, vcpu, kvm)
		kvm_s390_vcpu_bwock(vcpu);
}

static inwine void kvm_s390_vcpu_unbwock_aww(stwuct kvm *kvm)
{
	unsigned wong i;
	stwuct kvm_vcpu *vcpu;

	kvm_fow_each_vcpu(i, vcpu, kvm)
		kvm_s390_vcpu_unbwock(vcpu);
}

static inwine u64 kvm_s390_get_tod_cwock_fast(stwuct kvm *kvm)
{
	u64 wc;

	pweempt_disabwe();
	wc = get_tod_cwock_fast() + kvm->awch.epoch;
	pweempt_enabwe();
	wetuwn wc;
}

/**
 * kvm_s390_inject_pwog_cond - conditionawwy inject a pwogwam check
 * @vcpu: viwtuaw cpu
 * @wc: owiginaw wetuwn/ewwow code
 *
 * This function is supposed to be used aftew weguwaw guest access functions
 * faiwed, to conditionawwy inject a pwogwam check to a vcpu. The typicaw
 * pattewn wouwd wook wike
 *
 * wc = wwite_guest(vcpu, addw, data, wen);
 * if (wc)
 *	wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);
 *
 * A negative wetuwn code fwom guest access functions impwies an intewnaw ewwow
 * wike e.g. out of memowy. In these cases no pwogwam check shouwd be injected
 * to the guest.
 * A positive vawue impwies that an exception happened whiwe accessing a guest's
 * memowy. In this case aww data bewonging to the cowwesponding pwogwam check
 * has been stowed in vcpu->awch.pgm and can be injected with
 * kvm_s390_inject_pwog_iwq().
 *
 * Wetuwns: - the owiginaw @wc vawue if @wc was negative (intewnaw ewwow)
 *	    - zewo if @wc was awweady zewo
 *	    - zewo ow ewwow code fwom injecting if @wc was positive
 *	      (pwogwam check injected to @vcpu)
 */
static inwine int kvm_s390_inject_pwog_cond(stwuct kvm_vcpu *vcpu, int wc)
{
	if (wc <= 0)
		wetuwn wc;
	wetuwn kvm_s390_inject_pwog_iwq(vcpu, &vcpu->awch.pgm);
}

int s390int_to_s390iwq(stwuct kvm_s390_intewwupt *s390int,
			stwuct kvm_s390_iwq *s390iwq);

/* impwemented in intewwupt.c */
int kvm_s390_vcpu_has_iwq(stwuct kvm_vcpu *vcpu, int excwude_stop);
int psw_extint_disabwed(stwuct kvm_vcpu *vcpu);
void kvm_s390_destwoy_adaptews(stwuct kvm *kvm);
int kvm_s390_ext_caww_pending(stwuct kvm_vcpu *vcpu);
extewn stwuct kvm_device_ops kvm_fwic_ops;
int kvm_s390_is_stop_iwq_pending(stwuct kvm_vcpu *vcpu);
int kvm_s390_is_westawt_iwq_pending(stwuct kvm_vcpu *vcpu);
void kvm_s390_cweaw_stop_iwq(stwuct kvm_vcpu *vcpu);
int kvm_s390_set_iwq_state(stwuct kvm_vcpu *vcpu,
			   void __usew *buf, int wen);
int kvm_s390_get_iwq_state(stwuct kvm_vcpu *vcpu,
			   __u8 __usew *buf, int wen);
void kvm_s390_gisa_init(stwuct kvm *kvm);
void kvm_s390_gisa_cweaw(stwuct kvm *kvm);
void kvm_s390_gisa_destwoy(stwuct kvm *kvm);
void kvm_s390_gisa_disabwe(stwuct kvm *kvm);
void kvm_s390_gisa_enabwe(stwuct kvm *kvm);
int __init kvm_s390_gib_init(u8 nisc);
void kvm_s390_gib_destwoy(void);

/* impwemented in guestdbg.c */
void kvm_s390_backup_guest_pew_wegs(stwuct kvm_vcpu *vcpu);
void kvm_s390_westowe_guest_pew_wegs(stwuct kvm_vcpu *vcpu);
void kvm_s390_patch_guest_pew_wegs(stwuct kvm_vcpu *vcpu);
int kvm_s390_impowt_bp_data(stwuct kvm_vcpu *vcpu,
			    stwuct kvm_guest_debug *dbg);
void kvm_s390_cweaw_bp_data(stwuct kvm_vcpu *vcpu);
void kvm_s390_pwepawe_debug_exit(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_pew_ifetch_icpt(stwuct kvm_vcpu *vcpu);
int kvm_s390_handwe_pew_event(stwuct kvm_vcpu *vcpu);

/* suppowt fow Basic/Extended SCA handwing */
static inwine union ipte_contwow *kvm_s390_get_ipte_contwow(stwuct kvm *kvm)
{
	stwuct bsca_bwock *sca = kvm->awch.sca; /* SCA vewsion doesn't mattew */

	wetuwn &sca->ipte_contwow;
}
static inwine int kvm_s390_use_sca_entwies(void)
{
	/*
	 * Without SIGP intewpwetation, onwy SWS intewpwetation (if avaiwabwe)
	 * might use the entwies. By not setting the entwies and keeping them
	 * invawid, hawdwawe wiww not access them but intewcept.
	 */
	wetuwn scwp.has_sigpif;
}
void kvm_s390_weinject_machine_check(stwuct kvm_vcpu *vcpu,
				     stwuct mcck_vowatiwe_info *mcck_info);

/**
 * kvm_s390_vcpu_cwypto_weset_aww
 *
 * Weset the cwypto attwibutes fow each vcpu. This can be done whiwe the vcpus
 * awe wunning as each vcpu wiww be wemoved fwom SIE befowe wesetting the cwypt
 * attwibutes and westowed to SIE aftewwawd.
 *
 * Note: The kvm->wock must be hewd whiwe cawwing this function
 *
 * @kvm: the KVM guest
 */
void kvm_s390_vcpu_cwypto_weset_aww(stwuct kvm *kvm);

/**
 * kvm_s390_vcpu_pci_enabwe_intewp
 *
 * Set the associated PCI attwibutes fow each vcpu to awwow fow zPCI Woad/Stowe
 * intewpwetation as weww as adaptew intewwuption fowwawding.
 *
 * @kvm: the KVM guest
 */
void kvm_s390_vcpu_pci_enabwe_intewp(stwuct kvm *kvm);

/**
 * diag9c_fowwawding_hz
 *
 * Set the maximum numbew of diag9c fowwawding pew second
 */
extewn unsigned int diag9c_fowwawding_hz;

#endif
