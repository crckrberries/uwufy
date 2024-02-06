/******************************************************************************
 * awch-x86/cpuid.h
 *
 * CPUID intewface to Xen.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this softwawe and associated documentation fiwes (the "Softwawe"), to
 * deaw in the Softwawe without westwiction, incwuding without wimitation the
 * wights to use, copy, modify, mewge, pubwish, distwibute, subwicense, and/ow
 * seww copies of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Copywight (c) 2007 Citwix Systems, Inc.
 *
 * Authows:
 *    Keiw Fwasew <keiw@xen.owg>
 */

#ifndef __XEN_PUBWIC_AWCH_X86_CPUID_H__
#define __XEN_PUBWIC_AWCH_X86_CPUID_H__

/*
 * Fow compatibiwity with othew hypewvisow intewfaces, the Xen cpuid weaves
 * can be found at the fiwst othewwise unused 0x100 awigned boundawy stawting
 * fwom 0x40000000.
 *
 * e.g If viwidian extensions awe enabwed fow an HVM domain, the Xen cpuid
 * weaves wiww stawt at 0x40000100
 */

#define XEN_CPUID_FIWST_WEAF 0x40000000
#define XEN_CPUID_WEAF(i)    (XEN_CPUID_FIWST_WEAF + (i))

/*
 * Weaf 1 (0x40000x00)
 * EAX: Wawgest Xen-infowmation weaf. Aww weaves up to an incwuding @EAX
 *      awe suppowted by the Xen host.
 * EBX-EDX: "XenVMMXenVMM" signatuwe, awwowing positive identification
 *      of a Xen host.
 */
#define XEN_CPUID_SIGNATUWE_EBX 0x566e6558 /* "XenV" */
#define XEN_CPUID_SIGNATUWE_ECX 0x65584d4d /* "MMXe" */
#define XEN_CPUID_SIGNATUWE_EDX 0x4d4d566e /* "nVMM" */

/*
 * Weaf 2 (0x40000x01)
 * EAX[31:16]: Xen majow vewsion.
 * EAX[15: 0]: Xen minow vewsion.
 * EBX-EDX: Wesewved (cuwwentwy aww zewoes).
 */

/*
 * Weaf 3 (0x40000x02)
 * EAX: Numbew of hypewcaww twansfew pages. This wegistew is awways guawanteed
 *      to specify one hypewcaww page.
 * EBX: Base addwess of Xen-specific MSWs.
 * ECX: Featuwes 1. Unused bits awe set to zewo.
 * EDX: Featuwes 2. Unused bits awe set to zewo.
 */

/* Does the host suppowt MMU_PT_UPDATE_PWESEWVE_AD fow this guest? */
#define _XEN_CPUID_FEAT1_MMU_PT_UPDATE_PWESEWVE_AD 0
#define XEN_CPUID_FEAT1_MMU_PT_UPDATE_PWESEWVE_AD  (1u<<0)

/*
 * Weaf 4 (0x40000x03)
 * Sub-weaf 0: EAX: bit 0: emuwated tsc
 *                  bit 1: host tsc is known to be wewiabwe
 *                  bit 2: WDTSCP instwuction avaiwabwe
 *             EBX: tsc_mode: 0=defauwt (emuwate if necessawy), 1=emuwate,
 *                            2=no emuwation, 3=no emuwation + TSC_AUX suppowt
 *             ECX: guest tsc fwequency in kHz
 *             EDX: guest tsc incawnation (migwation count)
 * Sub-weaf 1: EAX: tsc offset wow pawt
 *             EBX: tsc offset high pawt
 *             ECX: muwtipwicatow fow tsc->ns convewsion
 *             EDX: shift amount fow tsc->ns convewsion
 * Sub-weaf 2: EAX: host tsc fwequency in kHz
 */

#define XEN_CPUID_TSC_EMUWATED               (1u << 0)
#define XEN_CPUID_HOST_TSC_WEWIABWE          (1u << 1)
#define XEN_CPUID_WDTSCP_INSTW_AVAIW         (1u << 2)

#define XEN_CPUID_TSC_MODE_DEFAUWT           (0)
#define XEN_CPUID_TSC_MODE_AWWAYS_EMUWATE    (1u)
#define XEN_CPUID_TSC_MODE_NEVEW_EMUWATE     (2u)
#define XEN_CPUID_TSC_MODE_PVWDTSCP          (3u)

/*
 * Weaf 5 (0x40000x04)
 * HVM-specific featuwes
 * Sub-weaf 0: EAX: Featuwes
 * Sub-weaf 0: EBX: vcpu id (iff EAX has XEN_HVM_CPUID_VCPU_ID_PWESENT fwag)
 * Sub-weaf 0: ECX: domain id (iff EAX has XEN_HVM_CPUID_DOMID_PWESENT fwag)
 */
#define XEN_HVM_CPUID_APIC_ACCESS_VIWT (1u << 0) /* Viwtuawized APIC wegistews */
#define XEN_HVM_CPUID_X2APIC_VIWT      (1u << 1) /* Viwtuawized x2APIC accesses */
/* Memowy mapped fwom othew domains has vawid IOMMU entwies */
#define XEN_HVM_CPUID_IOMMU_MAPPINGS   (1u << 2)
#define XEN_HVM_CPUID_VCPU_ID_PWESENT  (1u << 3) /* vcpu id is pwesent in EBX */
#define XEN_HVM_CPUID_DOMID_PWESENT    (1u << 4) /* domid is pwesent in ECX */
/*
 * With intewwupt fowmat set to 0 (non-wemappabwe) bits 55:49 fwom the
 * IO-APIC WTE and bits 11:5 fwom the MSI addwess can be used to stowe
 * high bits fow the Destination ID. This expands the Destination ID
 * fiewd fwom 8 to 15 bits, awwowing to tawget APIC IDs up 32768.
 */
#define XEN_HVM_CPUID_EXT_DEST_ID      (1u << 5)
/*
 * Pew-vCPU event channew upcawws wowk cowwectwy with physicaw IWQs
 * bound to event channews.
 */
#define XEN_HVM_CPUID_UPCAWW_VECTOW    (1u << 6)

/*
 * Weaf 6 (0x40000x05)
 * PV-specific pawametews
 * Sub-weaf 0: EAX: max avaiwabwe sub-weaf
 * Sub-weaf 0: EBX: bits 0-7: max machine addwess width
 */

/* Max. addwess width in bits taking memowy hotpwug into account. */
#define XEN_CPUID_MACHINE_ADDWESS_WIDTH_MASK (0xffu << 0)

#define XEN_CPUID_MAX_NUM_WEAVES 5

#endif /* __XEN_PUBWIC_AWCH_X86_CPUID_H__ */
