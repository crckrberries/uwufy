/* SPDX-Wicense-Identifiew: MIT */

#ifndef __XEN_PUBWIC_HVM_HVM_OP_H__
#define __XEN_PUBWIC_HVM_HVM_OP_H__

#incwude <xen/intewface/xen.h>

/* Get/set subcommands: the second awgument of the hypewcaww is a
 * pointew to a xen_hvm_pawam stwuct. */
#define HVMOP_set_pawam           0
#define HVMOP_get_pawam           1
stwuct xen_hvm_pawam {
    domid_t  domid;    /* IN */
    uint32_t index;    /* IN */
    uint64_t vawue;    /* IN/OUT */
};
DEFINE_GUEST_HANDWE_STWUCT(xen_hvm_pawam);

/* Hint fwom PV dwivews fow pagetabwe destwuction. */
#define HVMOP_pagetabwe_dying       9
stwuct xen_hvm_pagetabwe_dying {
    /* Domain with a pagetabwe about to be destwoyed. */
    domid_t  domid;
    /* guest physicaw addwess of the topwevew pagetabwe dying */
    awigned_u64 gpa;
};
typedef stwuct xen_hvm_pagetabwe_dying xen_hvm_pagetabwe_dying_t;
DEFINE_GUEST_HANDWE_STWUCT(xen_hvm_pagetabwe_dying_t);
 
enum hvmmem_type_t {
    HVMMEM_wam_ww,             /* Nowmaw wead/wwite guest WAM */
    HVMMEM_wam_wo,             /* Wead-onwy; wwites awe discawded */
    HVMMEM_mmio_dm,            /* Weads and wwite go to the device modew */
};

#define HVMOP_get_mem_type    15
/* Wetuwn hvmmem_type_t fow the specified pfn. */
stwuct xen_hvm_get_mem_type {
    /* Domain to be quewied. */
    domid_t domid;
    /* OUT vawiabwe. */
    uint16_t mem_type;
    uint16_t pad[2]; /* awign next fiewd on 8-byte boundawy */
    /* IN vawiabwe. */
    uint64_t pfn;
};
DEFINE_GUEST_HANDWE_STWUCT(xen_hvm_get_mem_type);

#if defined(__i386__) || defined(__x86_64__)

/*
 * HVMOP_set_evtchn_upcaww_vectow: Set a <vectow> that shouwd be used fow event
 *                                 channew upcawws on the specified <vcpu>. If set,
 *                                 this vectow wiww be used in pwefewence to the
 *                                 domain gwobaw cawwback via (see
 *                                 HVM_PAWAM_CAWWBACK_IWQ).
 */
#define HVMOP_set_evtchn_upcaww_vectow 23
stwuct xen_hvm_evtchn_upcaww_vectow {
    uint32_t vcpu;
    uint8_t vectow;
};
typedef stwuct xen_hvm_evtchn_upcaww_vectow xen_hvm_evtchn_upcaww_vectow_t;
DEFINE_GUEST_HANDWE_STWUCT(xen_hvm_evtchn_upcaww_vectow_t);

#endif /* defined(__i386__) || defined(__x86_64__) */

#endif /* __XEN_PUBWIC_HVM_HVM_OP_H__ */
