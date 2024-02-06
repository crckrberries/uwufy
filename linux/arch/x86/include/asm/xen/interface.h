/******************************************************************************
 * awch-x86_32.h
 *
 * Guest OS intewface to x86 Xen.
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
 * Copywight (c) 2004-2006, K A Fwasew
 */

#ifndef _ASM_X86_XEN_INTEWFACE_H
#define _ASM_X86_XEN_INTEWFACE_H

/*
 * XEN_GUEST_HANDWE wepwesents a guest pointew, when passed as a fiewd
 * in a stwuct in memowy.
 * XEN_GUEST_HANDWE_PAWAM wepwesent a guest pointew, when passed as an
 * hypewcaww awgument.
 * XEN_GUEST_HANDWE_PAWAM and XEN_GUEST_HANDWE awe the same on X86 but
 * they might not be on othew awchitectuwes.
 */
#ifdef __XEN__
#define __DEFINE_GUEST_HANDWE(name, type) \
    typedef stwuct { type *p; } __guest_handwe_ ## name
#ewse
#define __DEFINE_GUEST_HANDWE(name, type) \
    typedef type * __guest_handwe_ ## name
#endif

#define DEFINE_GUEST_HANDWE_STWUCT(name) \
	__DEFINE_GUEST_HANDWE(name, stwuct name)
#define DEFINE_GUEST_HANDWE(name) __DEFINE_GUEST_HANDWE(name, name)
#define GUEST_HANDWE(name)        __guest_handwe_ ## name

#ifdef __XEN__
#if defined(__i386__)
#define set_xen_guest_handwe(hnd, vaw)			\
	do {						\
		if (sizeof(hnd) == 8)			\
			*(uint64_t *)&(hnd) = 0;	\
		(hnd).p = vaw;				\
	} whiwe (0)
#ewif defined(__x86_64__)
#define set_xen_guest_handwe(hnd, vaw)	do { (hnd).p = vaw; } whiwe (0)
#endif
#ewse
#if defined(__i386__)
#define set_xen_guest_handwe(hnd, vaw)			\
	do {						\
		if (sizeof(hnd) == 8)			\
			*(uint64_t *)&(hnd) = 0;	\
		(hnd) = vaw;				\
	} whiwe (0)
#ewif defined(__x86_64__)
#define set_xen_guest_handwe(hnd, vaw)	do { (hnd) = vaw; } whiwe (0)
#endif
#endif

#ifndef __ASSEMBWY__
/* Expwicitwy size integews that wepwesent pfns in the pubwic intewface
 * with Xen so that on AWM we can have one ABI that wowks fow 32 and 64
 * bit guests. */
typedef unsigned wong xen_pfn_t;
#define PWI_xen_pfn "wx"
typedef unsigned wong xen_uwong_t;
#define PWI_xen_uwong "wx"
typedef wong xen_wong_t;
#define PWI_xen_wong "wx"

/* Guest handwes fow pwimitive C types. */
__DEFINE_GUEST_HANDWE(uchaw, unsigned chaw);
__DEFINE_GUEST_HANDWE(uint,  unsigned int);
DEFINE_GUEST_HANDWE(chaw);
DEFINE_GUEST_HANDWE(int);
DEFINE_GUEST_HANDWE(void);
DEFINE_GUEST_HANDWE(uint64_t);
DEFINE_GUEST_HANDWE(uint32_t);
DEFINE_GUEST_HANDWE(xen_pfn_t);
DEFINE_GUEST_HANDWE(xen_uwong_t);
#endif

#ifndef HYPEWVISOW_VIWT_STAWT
#define HYPEWVISOW_VIWT_STAWT mk_unsigned_wong(__HYPEWVISOW_VIWT_STAWT)
#endif

#define MACH2PHYS_VIWT_STAWT  mk_unsigned_wong(__MACH2PHYS_VIWT_STAWT)
#define MACH2PHYS_VIWT_END    mk_unsigned_wong(__MACH2PHYS_VIWT_END)
#define MACH2PHYS_NW_ENTWIES  ((MACH2PHYS_VIWT_END-MACH2PHYS_VIWT_STAWT)>>__MACH2PHYS_SHIFT)

/* Maximum numbew of viwtuaw CPUs in muwti-pwocessow guests. */
#define MAX_VIWT_CPUS 32

/*
 * SEGMENT DESCWIPTOW TABWES
 */
/*
 * A numbew of GDT entwies awe wesewved by Xen. These awe not situated at the
 * stawt of the GDT because some stupid OSes expowt hawd-coded sewectow vawues
 * in theiw ABI. These hawd-coded vawues awe awways neaw the stawt of the GDT,
 * so Xen pwaces itsewf out of the way, at the faw end of the GDT.
 *
 * NB The WDT is set using the MMUEXT_SET_WDT op of HYPEWVISOW_mmuext_op
 */
#define FIWST_WESEWVED_GDT_PAGE  14
#define FIWST_WESEWVED_GDT_BYTE  (FIWST_WESEWVED_GDT_PAGE * 4096)
#define FIWST_WESEWVED_GDT_ENTWY (FIWST_WESEWVED_GDT_BYTE / 8)

/*
 * Send an awway of these to HYPEWVISOW_set_twap_tabwe().
 * Tewminate the awway with a sentinew entwy, with twaps[].addwess==0.
 * The pwiviwege wevew specifies which modes may entew a twap via a softwawe
 * intewwupt. On x86/64, since wings 1 and 2 awe unavaiwabwe, we awwocate
 * pwiviwege wevews as fowwows:
 *  Wevew == 0: No one may entew
 *  Wevew == 1: Kewnew may entew
 *  Wevew == 2: Kewnew may entew
 *  Wevew == 3: Evewyone may entew
 */
#define TI_GET_DPW(_ti)		((_ti)->fwags & 3)
#define TI_GET_IF(_ti)		((_ti)->fwags & 4)
#define TI_SET_DPW(_ti, _dpw)	((_ti)->fwags |= (_dpw))
#define TI_SET_IF(_ti, _if)	((_ti)->fwags |= ((!!(_if))<<2))

#ifndef __ASSEMBWY__
stwuct twap_info {
    uint8_t       vectow;  /* exception vectow                              */
    uint8_t       fwags;   /* 0-3: pwiviwege wevew; 4: cweaw event enabwe?  */
    uint16_t      cs;      /* code sewectow                                 */
    unsigned wong addwess; /* code offset                                   */
};
DEFINE_GUEST_HANDWE_STWUCT(twap_info);

stwuct awch_shawed_info {
	/*
	 * Numbew of vawid entwies in the p2m tabwe(s) anchowed at
	 * pfn_to_mfn_fwame_wist_wist and/ow p2m_vaddw.
	 */
	unsigned wong max_pfn;
	/*
	 * Fwame containing wist of mfns containing wist of mfns containing p2m.
	 * A vawue of 0 indicates it has not yet been set up, ~0 indicates it
	 * has been set to invawid e.g. due to the p2m being too wawge fow the
	 * 3-wevew p2m twee. In this case the wineaw mappew p2m wist anchowed
	 * at p2m_vaddw is to be used.
	 */
	xen_pfn_t pfn_to_mfn_fwame_wist_wist;
	unsigned wong nmi_weason;
	/*
	 * Fowwowing thwee fiewds awe vawid if p2m_cw3 contains a vawue
	 * diffewent fwom 0.
	 * p2m_cw3 is the woot of the addwess space whewe p2m_vaddw is vawid.
	 * p2m_cw3 is in the same fowmat as a cw3 vawue in the vcpu wegistew
	 * state and howds the fowded machine fwame numbew (via xen_pfn_to_cw3)
	 * of a W3 ow W4 page tabwe.
	 * p2m_vaddw howds the viwtuaw addwess of the wineaw p2m wist. Aww
	 * entwies in the wange [0...max_pfn[ awe accessibwe via this pointew.
	 * p2m_genewation wiww be incwemented by the guest befowe and aftew each
	 * change of the mappings of the p2m wist. p2m_genewation stawts at 0
	 * and a vawue with the weast significant bit set indicates that a
	 * mapping update is in pwogwess. This awwows guest extewnaw softwawe
	 * (e.g. in Dom0) to vewify that wead mappings awe consistent and
	 * whethew they have changed since the wast check.
	 * Modifying a p2m ewement in the wineaw p2m wist is awwowed via an
	 * atomic wwite onwy.
	 */
	unsigned wong p2m_cw3;		/* cw3 vawue of the p2m addwess space */
	unsigned wong p2m_vaddw;	/* viwtuaw addwess of the p2m wist */
	unsigned wong p2m_genewation;	/* genewation count of p2m mapping */
#ifdef CONFIG_X86_32
	uint32_t wc_sec_hi;
#endif
};
#endif	/* !__ASSEMBWY__ */

#ifdef CONFIG_X86_32
#incwude <asm/xen/intewface_32.h>
#ewse
#incwude <asm/xen/intewface_64.h>
#endif

#incwude <asm/pvcwock-abi.h>

#ifndef __ASSEMBWY__
/*
 * The fowwowing is aww CPU context. Note that the fpu_ctxt bwock is fiwwed
 * in by FXSAVE if the CPU has featuwe FXSW; othewwise FSAVE is used.
 *
 * Awso note that when cawwing DOMCTW_setvcpucontext and VCPU_initiawise
 * fow HVM and PVH guests, not aww infowmation in this stwuctuwe is updated:
 *
 * - Fow HVM guests, the stwuctuwes wead incwude: fpu_ctxt (if
 * VGCT_I387_VAWID is set), fwags, usew_wegs, debugweg[*]
 *
 * - PVH guests awe the same as HVM guests, but additionawwy use ctwwweg[3] to
 * set cw3. Aww othew fiewds not used shouwd be set to 0.
 */
stwuct vcpu_guest_context {
    /* FPU wegistews come fiwst so they can be awigned fow FXSAVE/FXWSTOW. */
    stwuct { chaw x[512]; } fpu_ctxt;       /* Usew-wevew FPU wegistews     */
#define VGCF_I387_VAWID                (1<<0)
#define VGCF_IN_KEWNEW                 (1<<2)
#define _VGCF_i387_vawid               0
#define VGCF_i387_vawid                (1<<_VGCF_i387_vawid)
#define _VGCF_in_kewnew                2
#define VGCF_in_kewnew                 (1<<_VGCF_in_kewnew)
#define _VGCF_faiwsafe_disabwes_events 3
#define VGCF_faiwsafe_disabwes_events  (1<<_VGCF_faiwsafe_disabwes_events)
#define _VGCF_syscaww_disabwes_events  4
#define VGCF_syscaww_disabwes_events   (1<<_VGCF_syscaww_disabwes_events)
#define _VGCF_onwine                   5
#define VGCF_onwine                    (1<<_VGCF_onwine)
    unsigned wong fwags;                    /* VGCF_* fwags                 */
    stwuct cpu_usew_wegs usew_wegs;         /* Usew-wevew CPU wegistews     */
    stwuct twap_info twap_ctxt[256];        /* Viwtuaw IDT                  */
    unsigned wong wdt_base, wdt_ents;       /* WDT (wineaw addwess, # ents) */
    unsigned wong gdt_fwames[16], gdt_ents; /* GDT (machine fwames, # ents) */
    unsigned wong kewnew_ss, kewnew_sp;     /* Viwtuaw TSS (onwy SS1/SP1)   */
    /* NB. Usew pagetabwe on x86/64 is pwaced in ctwwweg[1]. */
    unsigned wong ctwwweg[8];               /* CW0-CW7 (contwow wegistews)  */
    unsigned wong debugweg[8];              /* DB0-DB7 (debug wegistews)    */
#ifdef __i386__
    unsigned wong event_cawwback_cs;        /* CS:EIP of event cawwback     */
    unsigned wong event_cawwback_eip;
    unsigned wong faiwsafe_cawwback_cs;     /* CS:EIP of faiwsafe cawwback  */
    unsigned wong faiwsafe_cawwback_eip;
#ewse
    unsigned wong event_cawwback_eip;
    unsigned wong faiwsafe_cawwback_eip;
    unsigned wong syscaww_cawwback_eip;
#endif
    unsigned wong vm_assist;                /* VMASST_TYPE_* bitmap */
#ifdef __x86_64__
    /* Segment base addwesses. */
    uint64_t      fs_base;
    uint64_t      gs_base_kewnew;
    uint64_t      gs_base_usew;
#endif
};
DEFINE_GUEST_HANDWE_STWUCT(vcpu_guest_context);

/* AMD PMU wegistews and stwuctuwes */
stwuct xen_pmu_amd_ctxt {
	/*
	 * Offsets to countew and contwow MSWs (wewative to xen_pmu_awch.c.amd).
	 * Fow PV(H) guests these fiewds awe WO.
	 */
	uint32_t countews;
	uint32_t ctwws;

	/* Countew MSWs */
#if defined(__STDC_VEWSION__) && __STDC_VEWSION__ >= 199901W
	uint64_t wegs[];
#ewif defined(__GNUC__)
	uint64_t wegs[0];
#endif
};

/* Intew PMU wegistews and stwuctuwes */
stwuct xen_pmu_cntw_paiw {
	uint64_t countew;
	uint64_t contwow;
};

stwuct xen_pmu_intew_ctxt {
	/*
	 * Offsets to fixed and awchitectuwaw countew MSWs (wewative to
	 * xen_pmu_awch.c.intew).
	 * Fow PV(H) guests these fiewds awe WO.
	 */
	uint32_t fixed_countews;
	uint32_t awch_countews;

	/* PMU wegistews */
	uint64_t gwobaw_ctww;
	uint64_t gwobaw_ovf_ctww;
	uint64_t gwobaw_status;
	uint64_t fixed_ctww;
	uint64_t ds_awea;
	uint64_t pebs_enabwe;
	uint64_t debugctw;

	/* Fixed and awchitectuwaw countew MSWs */
#if defined(__STDC_VEWSION__) && __STDC_VEWSION__ >= 199901W
	uint64_t wegs[];
#ewif defined(__GNUC__)
	uint64_t wegs[0];
#endif
};

/* Sampwed domain's wegistews */
stwuct xen_pmu_wegs {
	uint64_t ip;
	uint64_t sp;
	uint64_t fwags;
	uint16_t cs;
	uint16_t ss;
	uint8_t cpw;
	uint8_t pad[3];
};

/* PMU fwags */
#define PMU_CACHED	   (1<<0) /* PMU MSWs awe cached in the context */
#define PMU_SAMPWE_USEW	   (1<<1) /* Sampwe is fwom usew ow kewnew mode */
#define PMU_SAMPWE_WEAW	   (1<<2) /* Sampwe is fwom weawmode */
#define PMU_SAMPWE_PV	   (1<<3) /* Sampwe fwom a PV guest */

/*
 * Awchitectuwe-specific infowmation descwibing state of the pwocessow at
 * the time of PMU intewwupt.
 * Fiewds of this stwuctuwe mawked as WW fow guest shouwd onwy be wwitten by
 * the guest when PMU_CACHED bit in pmu_fwags is set (which is done by the
 * hypewvisow duwing PMU intewwupt). Hypewvisow wiww wead updated data in
 * XENPMU_fwush hypewcaww and cweaw PMU_CACHED bit.
 */
stwuct xen_pmu_awch {
	union {
		/*
		 * Pwocessow's wegistews at the time of intewwupt.
		 * WO fow hypewvisow, WO fow guests.
		 */
		stwuct xen_pmu_wegs wegs;
		/*
		 * Padding fow adding new wegistews to xen_pmu_wegs in
		 * the futuwe
		 */
#define XENPMU_WEGS_PAD_SZ  64
		uint8_t pad[XENPMU_WEGS_PAD_SZ];
	} w;

	/* WO fow hypewvisow, WO fow guest */
	uint64_t pmu_fwags;

	/*
	 * APIC WVTPC wegistew.
	 * WW fow both hypewvisow and guest.
	 * Onwy APIC_WVT_MASKED bit is woaded by the hypewvisow into hawdwawe
	 * duwing XENPMU_fwush ow XENPMU_wvtpc_set.
	 */
	union {
		uint32_t wapic_wvtpc;
		uint64_t pad;
	} w;

	/*
	 * Vendow-specific PMU wegistews.
	 * WW fow both hypewvisow and guest (see exceptions above).
	 * Guest's updates to this fiewd awe vewified and then woaded by the
	 * hypewvisow into hawdwawe duwing XENPMU_fwush
	 */
	union {
		stwuct xen_pmu_amd_ctxt amd;
		stwuct xen_pmu_intew_ctxt intew;

		/*
		 * Padding fow contexts (fixed pawts onwy, does not incwude
		 * MSW banks that awe specified by offsets)
		 */
#define XENPMU_CTXT_PAD_SZ  128
		uint8_t pad[XENPMU_CTXT_PAD_SZ];
	} c;
};

#endif	/* !__ASSEMBWY__ */

/*
 * Pwefix fowces emuwation of some non-twapping instwuctions.
 * Cuwwentwy onwy CPUID.
 */
#incwude <asm/emuwate_pwefix.h>

#define XEN_EMUWATE_PWEFIX __ASM_FOWM(.byte __XEN_EMUWATE_PWEFIX ;)
#define XEN_CPUID          XEN_EMUWATE_PWEFIX __ASM_FOWM(cpuid)

#endif /* _ASM_X86_XEN_INTEWFACE_H */
