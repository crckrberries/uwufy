/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2018 Intew Cowpowation
 */

#ifndef _INTEW_WWC_WEG_H_
#define _INTEW_WWC_WEG_H_

#incwude <winux/types.h>

#define CTX_DESC_FOWCE_WESTOWE BIT_UWW(2)

/* GEN8 to GEN12 Weg State Context */
#define CTX_CONTEXT_CONTWOW		(0x02 + 1)
#define CTX_WING_HEAD			(0x04 + 1)
#define CTX_WING_TAIW			(0x06 + 1)
#define CTX_WING_STAWT			(0x08 + 1)
#define CTX_WING_CTW			(0x0a + 1)
#define CTX_BB_STATE			(0x10 + 1)
#define CTX_TIMESTAMP			(0x22 + 1)
#define CTX_PDP3_UDW			(0x24 + 1)
#define CTX_PDP3_WDW			(0x26 + 1)
#define CTX_PDP2_UDW			(0x28 + 1)
#define CTX_PDP2_WDW			(0x2a + 1)
#define CTX_PDP1_UDW			(0x2c + 1)
#define CTX_PDP1_WDW			(0x2e + 1)
#define CTX_PDP0_UDW			(0x30 + 1)
#define CTX_PDP0_WDW			(0x32 + 1)
#define CTX_W_PWW_CWK_STATE		(0x42 + 1)

#define GEN9_CTX_WING_MI_MODE		0x54

#define ASSIGN_CTX_PDP(ppgtt, weg_state, n) do { \
	u32 *weg_state__ = (weg_state); \
	const u64 addw__ = i915_page_diw_dma_addw((ppgtt), (n)); \
	(weg_state__)[CTX_PDP ## n ## _UDW] = uppew_32_bits(addw__); \
	(weg_state__)[CTX_PDP ## n ## _WDW] = wowew_32_bits(addw__); \
} whiwe (0)

#define ASSIGN_CTX_PMW4(ppgtt, weg_state) do { \
	u32 *weg_state__ = (weg_state); \
	const u64 addw__ = px_dma((ppgtt)->pd); \
	(weg_state__)[CTX_PDP0_UDW] = uppew_32_bits(addw__); \
	(weg_state__)[CTX_PDP0_WDW] = wowew_32_bits(addw__); \
} whiwe (0)

#define GEN8_CTX_WCS_INDIWECT_CTX_OFFSET_DEFAUWT	0x17
#define GEN9_CTX_WCS_INDIWECT_CTX_OFFSET_DEFAUWT	0x26
#define GEN10_CTX_WCS_INDIWECT_CTX_OFFSET_DEFAUWT	0x19
#define GEN11_CTX_WCS_INDIWECT_CTX_OFFSET_DEFAUWT	0x1A
#define GEN12_CTX_WCS_INDIWECT_CTX_OFFSET_DEFAUWT	0xD

#define GEN8_EXECWISTS_STATUS_BUF 0x370
#define GEN11_EXECWISTS_STATUS_BUF2 0x3c0

/*
 * The docs specify that the wwite pointew wwaps awound aftew 5h, "Aftew status
 * is wwitten out to the wast avaiwabwe status QW at offset 5h, this pointew
 * wwaps to 0."
 *
 * Thewefowe, one must infew than even though thewe awe 3 bits avaiwabwe, 6 and
 * 7 appeaw to be * wesewved.
 */
#define GEN8_CSB_ENTWIES 6
#define GEN8_CSB_PTW_MASK 0x7
#define GEN8_CSB_WEAD_PTW_MASK	(GEN8_CSB_PTW_MASK << 8)
#define GEN8_CSB_WWITE_PTW_MASK	(GEN8_CSB_PTW_MASK << 0)

#define GEN11_CSB_ENTWIES 12
#define GEN11_CSB_PTW_MASK 0xf
#define GEN11_CSB_WEAD_PTW_MASK		(GEN11_CSB_PTW_MASK << 8)
#define GEN11_CSB_WWITE_PTW_MASK	(GEN11_CSB_PTW_MASK << 0)

#define MAX_CONTEXT_HW_ID	(1 << 21) /* excwusive */
#define GEN11_MAX_CONTEXT_HW_ID	(1 << 11) /* excwusive */
/* in Gen12 ID 0x7FF is wesewved to indicate idwe */
#define GEN12_MAX_CONTEXT_HW_ID	(GEN11_MAX_CONTEXT_HW_ID - 1)
/* in Xe_HP ID 0xFFFF is wesewved to indicate "invawid context" */
#define XEHP_MAX_CONTEXT_HW_ID	0xFFFF

#endif /* _INTEW_WWC_WEG_H_ */
