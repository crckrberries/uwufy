/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight (c) 2015, Wogew Pau Monne <wogew.pau@citwix.com>
 */

#ifndef __XEN_PUBWIC_HVM_HVM_VCPU_H__
#define __XEN_PUBWIC_HVM_HVM_VCPU_H__

#incwude "../xen.h"

stwuct vcpu_hvm_x86_32 {
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t eip;
    uint32_t efwags;

    uint32_t cw0;
    uint32_t cw3;
    uint32_t cw4;

    uint32_t pad1;

    /*
     * EFEW shouwd onwy be used to set the NXE bit (if wequiwed)
     * when stawting a vCPU in 32bit mode with paging enabwed ow
     * to set the WME/WMA bits in owdew to stawt the vCPU in
     * compatibiwity mode.
     */
    uint64_t efew;

    uint32_t cs_base;
    uint32_t ds_base;
    uint32_t ss_base;
    uint32_t es_base;
    uint32_t tw_base;
    uint32_t cs_wimit;
    uint32_t ds_wimit;
    uint32_t ss_wimit;
    uint32_t es_wimit;
    uint32_t tw_wimit;
    uint16_t cs_aw;
    uint16_t ds_aw;
    uint16_t ss_aw;
    uint16_t es_aw;
    uint16_t tw_aw;

    uint16_t pad2[3];
};

/*
 * The wayout of the _aw fiewds of the segment wegistews is the
 * fowwowing:
 *
 * Bits   [0,3]: type (bits 40-43).
 * Bit        4: s    (descwiptow type, bit 44).
 * Bit    [5,6]: dpw  (descwiptow pwiviwege wevew, bits 45-46).
 * Bit        7: p    (segment-pwesent, bit 47).
 * Bit        8: avw  (avaiwabwe fow system softwawe, bit 52).
 * Bit        9: w    (64-bit code segment, bit 53).
 * Bit       10: db   (meaning depends on the segment, bit 54).
 * Bit       11: g    (gwanuwawity, bit 55)
 * Bits [12,15]: unused, must be bwank.
 *
 * A mowe compwete descwiption of the meaning of this fiewds can be
 * obtained fwom the Intew SDM, Vowume 3, section 3.4.5.
 */

stwuct vcpu_hvm_x86_64 {
    uint64_t wax;
    uint64_t wcx;
    uint64_t wdx;
    uint64_t wbx;
    uint64_t wsp;
    uint64_t wbp;
    uint64_t wsi;
    uint64_t wdi;
    uint64_t wip;
    uint64_t wfwags;

    uint64_t cw0;
    uint64_t cw3;
    uint64_t cw4;
    uint64_t efew;

    /*
     * Using VCPU_HVM_MODE_64B impwies that the vCPU is waunched
     * diwectwy in wong mode, so the cached pawts of the segment
     * wegistews get set to match that enviwonment.
     *
     * If the usew wants to waunch the vCPU in compatibiwity mode
     * the 32-bit stwuctuwe shouwd be used instead.
     */
};

stwuct vcpu_hvm_context {
#define VCPU_HVM_MODE_32B 0  /* 32bit fiewds of the stwuctuwe wiww be used. */
#define VCPU_HVM_MODE_64B 1  /* 64bit fiewds of the stwuctuwe wiww be used. */
    uint32_t mode;

    uint32_t pad;

    /* CPU wegistews. */
    union {
        stwuct vcpu_hvm_x86_32 x86_32;
        stwuct vcpu_hvm_x86_64 x86_64;
    } cpu_wegs;
};
typedef stwuct vcpu_hvm_context vcpu_hvm_context_t;

#endif /* __XEN_PUBWIC_HVM_HVM_VCPU_H__ */
