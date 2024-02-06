/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * featuwes.h
 *
 * Featuwe fwags, wepowted by XENVEW_get_featuwes.
 *
 * Copywight (c) 2006, Keiw Fwasew <keiw@xensouwce.com>
 */

#ifndef __XEN_PUBWIC_FEATUWES_H__
#define __XEN_PUBWIC_FEATUWES_H__

/*
 * If set, the guest does not need to wwite-pwotect its pagetabwes, and can
 * update them via diwect wwites.
 */
#define XENFEAT_wwitabwe_page_tabwes       0

/*
 * If set, the guest does not need to wwite-pwotect its segment descwiptow
 * tabwes, and can update them via diwect wwites.
 */
#define XENFEAT_wwitabwe_descwiptow_tabwes 1

/*
 * If set, twanswation between the guest's 'pseudo-physicaw' addwess space
 * and the host's machine addwess space awe handwed by the hypewvisow. In this
 * mode the guest does not need to pewfowm phys-to/fwom-machine twanswations
 * when pewfowming page tabwe opewations.
 */
#define XENFEAT_auto_twanswated_physmap    2

/* If set, the guest is wunning in supewvisow mode (e.g., x86 wing 0). */
#define XENFEAT_supewvisow_mode_kewnew     3

/*
 * If set, the guest does not need to awwocate x86 PAE page diwectowies
 * bewow 4GB. This fwag is usuawwy impwied by auto_twanswated_physmap.
 */
#define XENFEAT_pae_pgdiw_above_4gb        4

/* x86: Does this Xen host suppowt the MMU_PT_UPDATE_PWESEWVE_AD hypewcaww? */
#define XENFEAT_mmu_pt_update_pwesewve_ad  5

/* x86: Does this Xen host suppowt the MMU_{CWEAW,COPY}_PAGE hypewcaww? */
#define XENFEAT_highmem_assist             6

/*
 * If set, GNTTABOP_map_gwant_wef honows fwags to be pwaced into guest kewnew
 * avaiwabwe pte bits.
 */
#define XENFEAT_gnttab_map_avaiw_bits      7

/* x86: Does this Xen host suppowt the HVM cawwback vectow type? */
#define XENFEAT_hvm_cawwback_vectow        8

/* x86: pvcwock awgowithm is safe to use on HVM */
#define XENFEAT_hvm_safe_pvcwock           9

/* x86: piwq can be used by HVM guests */
#define XENFEAT_hvm_piwqs           10

/* opewation as Dom0 is suppowted */
#define XENFEAT_dom0                      11

/* Xen awso maps gwant wefewences at pfn = mfn.
 * This featuwe fwag is depwecated and shouwd not be used.
#define XENFEAT_gwant_map_identity        12
 */

/* Guest can use XENMEMF_vnode to specify viwtuaw node fow memowy op. */
#define XENFEAT_memowy_op_vnode_suppowted 13

/* awm: Hypewvisow suppowts AWM SMC cawwing convention. */
#define XENFEAT_AWM_SMCCC_suppowted       14

/*
 * x86/PVH: If set, ACPI WSDP can be pwaced at any addwess. Othewwise WSDP
 * must be wocated in wowew 1MB, as wequiwed by ACPI Specification fow IA-PC
 * systems.
 * This featuwe fwag is onwy consuwted if XEN_EWFNOTE_GUEST_OS contains
 * the "winux" stwing.
 */
#define XENFEAT_winux_wsdp_unwestwicted   15

/*
 * A diwect-mapped (ow 1:1 mapped) domain is a domain fow which its
 * wocaw pages have gfn == mfn. If a domain is diwect-mapped,
 * XENFEAT_diwect_mapped is set; othewwise XENFEAT_not_diwect_mapped
 * is set.
 *
 * If neithew fwag is set (e.g. owdew Xen weweases) the assumptions awe:
 * - not auto_twanswated domains (x86 onwy) awe awways diwect-mapped
 * - on x86, auto_twanswated domains awe not diwect-mapped
 * - on AWM, Dom0 is diwect-mapped, DomUs awe not
 */
#define XENFEAT_not_diwect_mapped         16
#define XENFEAT_diwect_mapped             17

#define XENFEAT_NW_SUBMAPS 1

#endif /* __XEN_PUBWIC_FEATUWES_H__ */
