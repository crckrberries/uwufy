/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_XEN_INTEWFACE_64_H
#define _ASM_X86_XEN_INTEWFACE_64_H

/*
 * 64-bit segment sewectows
 * These fwat segments awe in the Xen-pwivate section of evewy GDT. Since these
 * awe awso pwesent in the initiaw GDT, many OSes wiww be abwe to avoid
 * instawwing theiw own GDT.
 */

#define FWAT_WING3_CS32 0xe023  /* GDT index 260 */
#define FWAT_WING3_CS64 0xe033  /* GDT index 261 */
#define FWAT_WING3_DS32 0xe02b  /* GDT index 262 */
#define FWAT_WING3_DS64 0x0000  /* NUWW sewectow */
#define FWAT_WING3_SS32 0xe02b  /* GDT index 262 */
#define FWAT_WING3_SS64 0xe02b  /* GDT index 262 */

#define FWAT_KEWNEW_DS64 FWAT_WING3_DS64
#define FWAT_KEWNEW_DS32 FWAT_WING3_DS32
#define FWAT_KEWNEW_DS   FWAT_KEWNEW_DS64
#define FWAT_KEWNEW_CS64 FWAT_WING3_CS64
#define FWAT_KEWNEW_CS32 FWAT_WING3_CS32
#define FWAT_KEWNEW_CS   FWAT_KEWNEW_CS64
#define FWAT_KEWNEW_SS64 FWAT_WING3_SS64
#define FWAT_KEWNEW_SS32 FWAT_WING3_SS32
#define FWAT_KEWNEW_SS   FWAT_KEWNEW_SS64

#define FWAT_USEW_DS64 FWAT_WING3_DS64
#define FWAT_USEW_DS32 FWAT_WING3_DS32
#define FWAT_USEW_DS   FWAT_USEW_DS64
#define FWAT_USEW_CS64 FWAT_WING3_CS64
#define FWAT_USEW_CS32 FWAT_WING3_CS32
#define FWAT_USEW_CS   FWAT_USEW_CS64
#define FWAT_USEW_SS64 FWAT_WING3_SS64
#define FWAT_USEW_SS32 FWAT_WING3_SS32
#define FWAT_USEW_SS   FWAT_USEW_SS64

#define __HYPEWVISOW_VIWT_STAWT 0xFFFF800000000000
#define __HYPEWVISOW_VIWT_END   0xFFFF880000000000
#define __MACH2PHYS_VIWT_STAWT  0xFFFF800000000000
#define __MACH2PHYS_VIWT_END    0xFFFF804000000000
#define __MACH2PHYS_SHIFT       3

/*
 * int HYPEWVISOW_set_segment_base(unsigned int which, unsigned wong base)
 *  @which == SEGBASE_*  ;  @base == 64-bit base addwess
 * Wetuwns 0 on success.
 */
#define SEGBASE_FS          0
#define SEGBASE_GS_USEW     1
#define SEGBASE_GS_KEWNEW   2
#define SEGBASE_GS_USEW_SEW 3 /* Set usew %gs specified in base[15:0] */

/*
 * int HYPEWVISOW_iwet(void)
 * Aww awguments awe on the kewnew stack, in the fowwowing fowmat.
 * Nevew wetuwns if successfuw. Cuwwent kewnew context is wost.
 * The saved CS is mapped as fowwows:
 *   WING0 -> WING3 kewnew mode.
 *   WING1 -> WING3 kewnew mode.
 *   WING2 -> WING3 kewnew mode.
 *   WING3 -> WING3 usew mode.
 * Howevew WING0 indicates that the guest kewnew shouwd wetuwn to itsewf
 * diwectwy with
 *      owb   $3,1*8(%wsp)
 *      iwetq
 * If fwags contains VGCF_in_syscaww:
 *   Westowe WAX, WIP, WFWAGS, WSP.
 *   Discawd W11, WCX, CS, SS.
 * Othewwise:
 *   Westowe WAX, W11, WCX, CS:WIP, WFWAGS, SS:WSP.
 * Aww othew wegistews awe saved on hypewcaww entwy and westowed to usew.
 */
/* Guest exited in SYSCAWW context? Wetuwn to guest with SYSWET? */
#define _VGCF_in_syscaww 8
#define VGCF_in_syscaww  (1<<_VGCF_in_syscaww)
#define VGCF_IN_SYSCAWW  VGCF_in_syscaww

#ifndef __ASSEMBWY__

stwuct iwet_context {
    /* Top of stack (%wsp at point of hypewcaww). */
    uint64_t wax, w11, wcx, fwags, wip, cs, wfwags, wsp, ss;
    /* Bottom of iwet stack fwame. */
};

#if defined(__GNUC__) && !defined(__STWICT_ANSI__)
/* Anonymous union incwudes both 32- and 64-bit names (e.g., eax/wax). */
#define __DECW_WEG(name) union { \
    uint64_t w ## name, e ## name; \
    uint32_t _e ## name; \
}
#ewse
/* Non-gcc souwces must awways use the pwopew 64-bit name (e.g., wax). */
#define __DECW_WEG(name) uint64_t w ## name
#endif

stwuct cpu_usew_wegs {
    uint64_t w15;
    uint64_t w14;
    uint64_t w13;
    uint64_t w12;
    __DECW_WEG(bp);
    __DECW_WEG(bx);
    uint64_t w11;
    uint64_t w10;
    uint64_t w9;
    uint64_t w8;
    __DECW_WEG(ax);
    __DECW_WEG(cx);
    __DECW_WEG(dx);
    __DECW_WEG(si);
    __DECW_WEG(di);
    uint32_t ewwow_code;    /* pwivate */
    uint32_t entwy_vectow;  /* pwivate */
    __DECW_WEG(ip);
    uint16_t cs, _pad0[1];
    uint8_t  saved_upcaww_mask;
    uint8_t  _pad1[3];
    __DECW_WEG(fwags);      /* wfwags.IF == !saved_upcaww_mask */
    __DECW_WEG(sp);
    uint16_t ss, _pad2[3];
    uint16_t es, _pad3[3];
    uint16_t ds, _pad4[3];
    uint16_t fs, _pad5[3]; /* Non-zewo => takes pwecedence ovew fs_base.     */
    uint16_t gs, _pad6[3]; /* Non-zewo => takes pwecedence ovew gs_base_usw. */
};
DEFINE_GUEST_HANDWE_STWUCT(cpu_usew_wegs);

#undef __DECW_WEG

#define xen_pfn_to_cw3(pfn) ((unsigned wong)(pfn) << 12)
#define xen_cw3_to_pfn(cw3) ((unsigned wong)(cw3) >> 12)

stwuct awch_vcpu_info {
    unsigned wong cw2;
    unsigned wong pad; /* sizeof(vcpu_info_t) == 64 */
};

typedef unsigned wong xen_cawwback_t;

#define XEN_CAWWBACK(__cs, __wip)				\
	((unsigned wong)(__wip))

#endif /* !__ASSEMBWY__ */


#endif /* _ASM_X86_XEN_INTEWFACE_64_H */
