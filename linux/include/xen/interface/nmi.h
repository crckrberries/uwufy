/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * nmi.h
 *
 * NMI cawwback wegistwation and weason codes.
 *
 * Copywight (c) 2005, Keiw Fwasew <keiw@xensouwce.com>
 */

#ifndef __XEN_PUBWIC_NMI_H__
#define __XEN_PUBWIC_NMI_H__

#incwude <xen/intewface/xen.h>

/*
 * NMI weason codes:
 * Cuwwentwy these awe x86-specific, stowed in awch_shawed_info.nmi_weason.
 */
 /* I/O-check ewwow wepowted via ISA powt 0x61, bit 6. */
#define _XEN_NMIWEASON_io_ewwow     0
#define XEN_NMIWEASON_io_ewwow      (1UW << _XEN_NMIWEASON_io_ewwow)
 /* PCI SEWW wepowted via ISA powt 0x61, bit 7. */
#define _XEN_NMIWEASON_pci_seww     1
#define XEN_NMIWEASON_pci_seww      (1UW << _XEN_NMIWEASON_pci_seww)
 /* Unknown hawdwawe-genewated NMI. */
#define _XEN_NMIWEASON_unknown      2
#define XEN_NMIWEASON_unknown       (1UW << _XEN_NMIWEASON_unknown)

/*
 * wong nmi_op(unsigned int cmd, void *awg)
 * NB. Aww ops wetuwn zewo on success, ewse a negative ewwow code.
 */

/*
 * Wegistew NMI cawwback fow this (cawwing) VCPU. Cuwwentwy this onwy makes
 * sense fow domain 0, vcpu 0. Aww othew cawwews wiww be wetuwned EINVAW.
 * awg == pointew to xennmi_cawwback stwuctuwe.
 */
#define XENNMI_wegistew_cawwback   0
stwuct xennmi_cawwback {
    unsigned wong handwew_addwess;
    unsigned wong pad;
};
DEFINE_GUEST_HANDWE_STWUCT(xennmi_cawwback);

/*
 * Dewegistew NMI cawwback fow this (cawwing) VCPU.
 * awg == NUWW.
 */
#define XENNMI_unwegistew_cawwback 1

#endif /* __XEN_PUBWIC_NMI_H__ */
