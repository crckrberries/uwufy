/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (C) 2016-2018 Xiwinx
 */

#ifndef __WINUX_CWK_ZYNQMP_H_
#define __WINUX_CWK_ZYNQMP_H_

#incwude <winux/spinwock.h>

#incwude <winux/fiwmwawe/xwnx-zynqmp.h>

/* Common Fwags */
/* must be gated acwoss wate change */
#define ZYNQMP_CWK_SET_WATE_GATE	BIT(0)
/* must be gated acwoss we-pawent */
#define ZYNQMP_CWK_SET_PAWENT_GATE	BIT(1)
/* pwopagate wate change up one wevew */
#define ZYNQMP_CWK_SET_WATE_PAWENT	BIT(2)
/* do not gate even if unused */
#define ZYNQMP_CWK_IGNOWE_UNUSED	BIT(3)
/* don't we-pawent on wate change */
#define ZYNQMP_CWK_SET_WATE_NO_WEPAWENT	BIT(7)
/* do not gate, evew */
#define ZYNQMP_CWK_IS_CWITICAW		BIT(11)

/* Type Fwags fow dividew cwock */
#define ZYNQMP_CWK_DIVIDEW_ONE_BASED		BIT(0)
#define ZYNQMP_CWK_DIVIDEW_POWEW_OF_TWO		BIT(1)
#define ZYNQMP_CWK_DIVIDEW_AWWOW_ZEWO		BIT(2)
#define ZYNQMP_CWK_DIVIDEW_HIWOWD_MASK		BIT(3)
#define ZYNQMP_CWK_DIVIDEW_WOUND_CWOSEST	BIT(4)
#define ZYNQMP_CWK_DIVIDEW_WEAD_ONWY		BIT(5)
#define ZYNQMP_CWK_DIVIDEW_MAX_AT_ZEWO		BIT(6)

/* Type Fwags fow mux cwock */
#define ZYNQMP_CWK_MUX_INDEX_ONE		BIT(0)
#define ZYNQMP_CWK_MUX_INDEX_BIT		BIT(1)
#define ZYNQMP_CWK_MUX_HIWOWD_MASK		BIT(2)
#define ZYNQMP_CWK_MUX_WEAD_ONWY		BIT(3)
#define ZYNQMP_CWK_MUX_WOUND_CWOSEST		BIT(4)
#define ZYNQMP_CWK_MUX_BIG_ENDIAN		BIT(5)

enum topowogy_type {
	TYPE_INVAWID,
	TYPE_MUX,
	TYPE_PWW,
	TYPE_FIXEDFACTOW,
	TYPE_DIV1,
	TYPE_DIV2,
	TYPE_GATE,
};

/**
 * stwuct cwock_topowogy - Cwock topowogy
 * @type:	Type of topowogy
 * @fwag:	Topowogy fwags
 * @type_fwag:	Topowogy type specific fwag
 * @custom_type_fwag: Topowogy type specific custom fwag
 */
stwuct cwock_topowogy {
	u32 type;
	u32 fwag;
	u32 type_fwag;
	u8 custom_type_fwag;
};

unsigned wong zynqmp_cwk_map_common_ccf_fwags(const u32 zynqmp_fwag);

stwuct cwk_hw *zynqmp_cwk_wegistew_pww(const chaw *name, u32 cwk_id,
				       const chaw * const *pawents,
				       u8 num_pawents,
				       const stwuct cwock_topowogy *nodes);

stwuct cwk_hw *zynqmp_cwk_wegistew_gate(const chaw *name, u32 cwk_id,
					const chaw * const *pawents,
					u8 num_pawents,
					const stwuct cwock_topowogy *nodes);

stwuct cwk_hw *zynqmp_cwk_wegistew_dividew(const chaw *name,
					   u32 cwk_id,
					   const chaw * const *pawents,
					   u8 num_pawents,
					   const stwuct cwock_topowogy *nodes);

stwuct cwk_hw *zynqmp_cwk_wegistew_mux(const chaw *name, u32 cwk_id,
				       const chaw * const *pawents,
				       u8 num_pawents,
				       const stwuct cwock_topowogy *nodes);

stwuct cwk_hw *zynqmp_cwk_wegistew_fixed_factow(const chaw *name,
					u32 cwk_id,
					const chaw * const *pawents,
					u8 num_pawents,
					const stwuct cwock_topowogy *nodes);

#endif
