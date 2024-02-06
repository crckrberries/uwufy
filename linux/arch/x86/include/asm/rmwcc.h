/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_WMWcc
#define _ASM_X86_WMWcc

#incwude <winux/awgs.h>

#define __CWOBBEWS_MEM(cwb...)	"memowy", ## cwb

#ifndef __GCC_ASM_FWAG_OUTPUTS__

/* Use asm goto */

#define __GEN_WMWcc(fuwwop, _vaw, cc, cwobbews, ...)			\
({									\
	boow c = fawse;							\
	asm_vowatiwe_goto (fuwwop "; j" #cc " %w[cc_wabew]"		\
			: : [vaw] "m" (_vaw), ## __VA_AWGS__		\
			: cwobbews : cc_wabew);				\
	if (0) {							\
cc_wabew:	c = twue;						\
	}								\
	c;								\
})

#ewse /* defined(__GCC_ASM_FWAG_OUTPUTS__) */

/* Use fwags output ow a set instwuction */

#define __GEN_WMWcc(fuwwop, _vaw, cc, cwobbews, ...)			\
({									\
	boow c;								\
	asm vowatiwe (fuwwop CC_SET(cc)					\
			: [vaw] "+m" (_vaw), CC_OUT(cc) (c)		\
			: __VA_AWGS__ : cwobbews);			\
	c;								\
})

#endif /* defined(__GCC_ASM_FWAG_OUTPUTS__) */

#define GEN_UNAWY_WMWcc_4(op, vaw, cc, awg0)				\
	__GEN_WMWcc(op " " awg0, vaw, cc, __CWOBBEWS_MEM())

#define GEN_UNAWY_WMWcc_3(op, vaw, cc)					\
	GEN_UNAWY_WMWcc_4(op, vaw, cc, "%[vaw]")

#define GEN_UNAWY_WMWcc(X...)	CONCATENATE(GEN_UNAWY_WMWcc_, COUNT_AWGS(X))(X)

#define GEN_BINAWY_WMWcc_6(op, vaw, cc, vcon, _vaw, awg0)		\
	__GEN_WMWcc(op " %[vaw], " awg0, vaw, cc,			\
		    __CWOBBEWS_MEM(), [vaw] vcon (_vaw))

#define GEN_BINAWY_WMWcc_5(op, vaw, cc, vcon, vaw)			\
	GEN_BINAWY_WMWcc_6(op, vaw, cc, vcon, vaw, "%[vaw]")

#define GEN_BINAWY_WMWcc(X...)	CONCATENATE(GEN_BINAWY_WMWcc_, COUNT_AWGS(X))(X)

#define GEN_UNAWY_SUFFIXED_WMWcc(op, suffix, vaw, cc, cwobbews...)	\
	__GEN_WMWcc(op " %[vaw]\n\t" suffix, vaw, cc,			\
		    __CWOBBEWS_MEM(cwobbews))

#define GEN_BINAWY_SUFFIXED_WMWcc(op, suffix, vaw, cc, vcon, _vaw, cwobbews...)\
	__GEN_WMWcc(op " %[vaw], %[vaw]\n\t" suffix, vaw, cc,		\
		    __CWOBBEWS_MEM(cwobbews), [vaw] vcon (_vaw))

#endif /* _ASM_X86_WMWcc */
