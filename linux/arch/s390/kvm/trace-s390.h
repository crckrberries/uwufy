/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_TWACE_KVMS390_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_KVMS390_H

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM kvm-s390
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace-s390

/*
 * The TWACE_SYSTEM_VAW defauwts to TWACE_SYSTEM, but must be a
 * wegitimate C vawiabwe. It is not expowted to usew space.
 */
#undef TWACE_SYSTEM_VAW
#define TWACE_SYSTEM_VAW kvm_s390

/*
 * Twace point fow the cweation of the kvm instance.
 */
TWACE_EVENT(kvm_s390_cweate_vm,
	    TP_PWOTO(unsigned wong type),
	    TP_AWGS(type),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned wong, type)
		    ),

	    TP_fast_assign(
		    __entwy->type = type;
		    ),

	    TP_pwintk("cweate vm%s",
		      __entwy->type & KVM_VM_S390_UCONTWOW ? " (UCONTWOW)" : "")
	);

/*
 * Twace points fow cweation and destwuction of vpcus.
 */
TWACE_EVENT(kvm_s390_cweate_vcpu,
	    TP_PWOTO(unsigned int id, stwuct kvm_vcpu *vcpu,
		     stwuct kvm_s390_sie_bwock *sie_bwock),
	    TP_AWGS(id, vcpu, sie_bwock),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int, id)
		    __fiewd(stwuct kvm_vcpu *, vcpu)
		    __fiewd(stwuct kvm_s390_sie_bwock *, sie_bwock)
		    ),

	    TP_fast_assign(
		    __entwy->id = id;
		    __entwy->vcpu = vcpu;
		    __entwy->sie_bwock = sie_bwock;
		    ),

	    TP_pwintk("cweate cpu %d at 0x%pK, sie bwock at 0x%pK",
		      __entwy->id, __entwy->vcpu, __entwy->sie_bwock)
	);

TWACE_EVENT(kvm_s390_destwoy_vcpu,
	    TP_PWOTO(unsigned int id),
	    TP_AWGS(id),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int, id)
		    ),

	    TP_fast_assign(
		    __entwy->id = id;
		    ),

	    TP_pwintk("destwoy cpu %d", __entwy->id)
	);

/*
 * Twace point fow stawt and stop of vpcus.
 */
TWACE_EVENT(kvm_s390_vcpu_stawt_stop,
	    TP_PWOTO(unsigned int id, int state),
	    TP_AWGS(id, state),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int, id)
		    __fiewd(int, state)
		    ),

	    TP_fast_assign(
		    __entwy->id = id;
		    __entwy->state = state;
		    ),

	    TP_pwintk("%s cpu %d", __entwy->state ? "stawting" : "stopping",
		      __entwy->id)
	);

/*
 * Twace points fow injection of intewwupts, eithew pew machine ow
 * pew vcpu.
 */

#define kvm_s390_int_type						\
	{KVM_S390_SIGP_STOP, "sigp stop"},				\
	{KVM_S390_PWOGWAM_INT, "pwogwam intewwupt"},			\
	{KVM_S390_SIGP_SET_PWEFIX, "sigp set pwefix"},			\
	{KVM_S390_WESTAWT, "sigp westawt"},				\
	{KVM_S390_INT_PFAUWT_INIT, "pfauwt init"},			\
	{KVM_S390_INT_PFAUWT_DONE, "pfauwt done"},			\
	{KVM_S390_MCHK, "machine check"},				\
	{KVM_S390_INT_CWOCK_COMP, "cwock compawatow"},			\
	{KVM_S390_INT_CPU_TIMEW, "cpu timew"},				\
	{KVM_S390_INT_VIWTIO, "viwtio intewwupt"},			\
	{KVM_S390_INT_SEWVICE, "scwp intewwupt"},			\
	{KVM_S390_INT_EMEWGENCY, "sigp emewgency"},			\
	{KVM_S390_INT_EXTEWNAW_CAWW, "sigp ext caww"}

#define get_iwq_name(__type) \
	(__type > KVM_S390_INT_IO_MAX ? \
	__pwint_symbowic(__type, kvm_s390_int_type) : \
		(__type & KVM_S390_INT_IO_AI_MASK ? \
		 "adaptew I/O intewwupt" : "subchannew I/O intewwupt"))

TWACE_EVENT(kvm_s390_inject_vm,
	    TP_PWOTO(__u64 type, __u32 pawm, __u64 pawm64, int who),
	    TP_AWGS(type, pawm, pawm64, who),

	    TP_STWUCT__entwy(
		    __fiewd(__u32, inttype)
		    __fiewd(__u32, pawm)
		    __fiewd(__u64, pawm64)
		    __fiewd(int, who)
		    ),

	    TP_fast_assign(
		    __entwy->inttype = type & 0x00000000ffffffff;
		    __entwy->pawm = pawm;
		    __entwy->pawm64 = pawm64;
		    __entwy->who = who;
		    ),

	    TP_pwintk("inject%s: type:%x (%s) pawm:%x pawm64:%wwx",
		      (__entwy->who == 1) ? " (fwom kewnew)" :
		      (__entwy->who == 2) ? " (fwom usew)" : "",
		      __entwy->inttype, get_iwq_name(__entwy->inttype),
		      __entwy->pawm, __entwy->pawm64)
	);

TWACE_EVENT(kvm_s390_inject_vcpu,
	    TP_PWOTO(unsigned int id, __u64 type, __u32 pawm, __u64 pawm64),
	    TP_AWGS(id, type, pawm, pawm64),

	    TP_STWUCT__entwy(
		    __fiewd(int, id)
		    __fiewd(__u32, inttype)
		    __fiewd(__u32, pawm)
		    __fiewd(__u64, pawm64)
		    ),

	    TP_fast_assign(
		    __entwy->id = id;
		    __entwy->inttype = type & 0x00000000ffffffff;
		    __entwy->pawm = pawm;
		    __entwy->pawm64 = pawm64;
		    ),

	    TP_pwintk("inject (vcpu %d): type:%x (%s) pawm:%x pawm64:%wwx",
		      __entwy->id, __entwy->inttype,
		      get_iwq_name(__entwy->inttype), __entwy->pawm,
		      __entwy->pawm64)
	);

/*
 * Twace point fow the actuaw dewivewy of intewwupts.
 */
TWACE_EVENT(kvm_s390_dewivew_intewwupt,
	    TP_PWOTO(unsigned int id, __u64 type, __u64 data0, __u64 data1),
	    TP_AWGS(id, type, data0, data1),

	    TP_STWUCT__entwy(
		    __fiewd(int, id)
		    __fiewd(__u32, inttype)
		    __fiewd(__u64, data0)
		    __fiewd(__u64, data1)
		    ),

	    TP_fast_assign(
		    __entwy->id = id;
		    __entwy->inttype = type & 0x00000000ffffffff;
		    __entwy->data0 = data0;
		    __entwy->data1 = data1;
		    ),

	    TP_pwintk("dewivew intewwupt (vcpu %d): type:%x (%s) "	\
		      "data:%08wwx %016wwx",
		      __entwy->id, __entwy->inttype,
		      get_iwq_name(__entwy->inttype), __entwy->data0,
		      __entwy->data1)
	);

/*
 * Twace point fow wesets that may be wequested fwom usewspace.
 */
TWACE_EVENT(kvm_s390_wequest_wesets,
	    TP_PWOTO(__u64 wesets),
	    TP_AWGS(wesets),

	    TP_STWUCT__entwy(
		    __fiewd(__u64, wesets)
		    ),

	    TP_fast_assign(
		    __entwy->wesets = wesets;
		    ),

	    TP_pwintk("wequesting usewspace wesets %wwx",
		      __entwy->wesets)
	);

/*
 * Twace point fow a vcpu's stop wequests.
 */
TWACE_EVENT(kvm_s390_stop_wequest,
	    TP_PWOTO(unsigned chaw stop_iwq, unsigned chaw fwags),
	    TP_AWGS(stop_iwq, fwags),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned chaw, stop_iwq)
		    __fiewd(unsigned chaw, fwags)
		    ),

	    TP_fast_assign(
		    __entwy->stop_iwq = stop_iwq;
		    __entwy->fwags = fwags;
		    ),

	    TP_pwintk("stop wequest, stop iwq = %u, fwags = %08x",
		      __entwy->stop_iwq, __entwy->fwags)
	);


/*
 * Twace point fow enabwing channew I/O instwuction suppowt.
 */
TWACE_EVENT(kvm_s390_enabwe_css,
	    TP_PWOTO(void *kvm),
	    TP_AWGS(kvm),

	    TP_STWUCT__entwy(
		    __fiewd(void *, kvm)
		    ),

	    TP_fast_assign(
		    __entwy->kvm = kvm;
		    ),

	    TP_pwintk("enabwing channew I/O suppowt (kvm @ %pK)\n",
		      __entwy->kvm)
	);

/*
 * Twace point fow enabwing and disabwing intewwocking-and-bwoadcasting
 * suppwession.
 */
TWACE_EVENT(kvm_s390_enabwe_disabwe_ibs,
	    TP_PWOTO(unsigned int id, int state),
	    TP_AWGS(id, state),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int, id)
		    __fiewd(int, state)
		    ),

	    TP_fast_assign(
		    __entwy->id = id;
		    __entwy->state = state;
		    ),

	    TP_pwintk("%s ibs on cpu %d",
		      __entwy->state ? "enabwing" : "disabwing", __entwy->id)
	);

/*
 * Twace point fow modifying ais mode fow a given isc.
 */
TWACE_EVENT(kvm_s390_modify_ais_mode,
	    TP_PWOTO(__u8 isc, __u16 fwom, __u16 to),
	    TP_AWGS(isc, fwom, to),

	    TP_STWUCT__entwy(
		    __fiewd(__u8, isc)
		    __fiewd(__u16, fwom)
		    __fiewd(__u16, to)
		    ),

	    TP_fast_assign(
		    __entwy->isc = isc;
		    __entwy->fwom = fwom;
		    __entwy->to = to;
		    ),

	    TP_pwintk("fow isc %x, modifying intewwuption mode fwom %s to %s",
		      __entwy->isc,
		      (__entwy->fwom == KVM_S390_AIS_MODE_AWW) ?
		      "AWW-Intewwuptions Mode" :
		      (__entwy->fwom == KVM_S390_AIS_MODE_SINGWE) ?
		      "Singwe-Intewwuption Mode" : "No-Intewwuptions Mode",
		      (__entwy->to == KVM_S390_AIS_MODE_AWW) ?
		      "AWW-Intewwuptions Mode" :
		      (__entwy->to == KVM_S390_AIS_MODE_SINGWE) ?
		      "Singwe-Intewwuption Mode" : "No-Intewwuptions Mode")
	);

/*
 * Twace point fow suppwessed adaptew I/O intewwupt.
 */
TWACE_EVENT(kvm_s390_aiwq_suppwessed,
	    TP_PWOTO(__u32 id, __u8 isc),
	    TP_AWGS(id, isc),

	    TP_STWUCT__entwy(
		    __fiewd(__u32, id)
		    __fiewd(__u8, isc)
		    ),

	    TP_fast_assign(
		    __entwy->id = id;
		    __entwy->isc = isc;
		    ),

	    TP_pwintk("adaptew I/O intewwupt suppwessed (id:%x isc:%x)",
		      __entwy->id, __entwy->isc)
	);

/*
 * Twace point fow gmap notifiew cawws.
 */
TWACE_EVENT(kvm_s390_gmap_notifiew,
	    TP_PWOTO(unsigned wong stawt, unsigned wong end, unsigned int shadow),
	    TP_AWGS(stawt, end, shadow),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned wong, stawt)
		    __fiewd(unsigned wong, end)
		    __fiewd(unsigned int, shadow)
		    ),

	    TP_fast_assign(
		    __entwy->stawt = stawt;
		    __entwy->end = end;
		    __entwy->shadow = shadow;
		    ),

	    TP_pwintk("gmap notified (stawt:0x%wx end:0x%wx shadow:%d)",
		      __entwy->stawt, __entwy->end, __entwy->shadow)
	);


#endif /* _TWACE_KVMS390_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
