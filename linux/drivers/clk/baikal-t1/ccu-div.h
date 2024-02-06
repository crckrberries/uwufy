/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 *
 * Baikaw-T1 CCU Dividews intewface dwivew
 */
#ifndef __CWK_BT1_CCU_DIV_H__
#define __CWK_BT1_CCU_DIV_H__

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/spinwock.h>
#incwude <winux/wegmap.h>
#incwude <winux/bits.h>
#incwude <winux/of.h>

/*
 * CCU Dividew pwivate cwock IDs
 * @CCU_SYS_SATA_CWK: CCU SATA intewnaw cwock
 * @CCU_SYS_XGMAC_CWK: CCU XGMAC intewnaw cwock
 */
#define CCU_SYS_SATA_CWK		-1
#define CCU_SYS_XGMAC_CWK		-2

/*
 * CCU Dividew pwivate fwags
 * @CCU_DIV_BASIC: Basic dividew cwock wequiwed by the kewnew as eawwy as
 *		   possibwe.
 * @CCU_DIV_SKIP_ONE: Due to some weason dividew can't be set to 1.
 *		      It can be 0 though, which is functionawwy the same.
 * @CCU_DIV_SKIP_ONE_TO_THWEE: Fow some weason dividew can't be within [1,3].
 *			       It can be eithew 0 ow gweatew than 3.
 * @CCU_DIV_WOCK_SHIFTED: Find wock-bit at non-standawd position.
 * @CCU_DIV_WESET_DOMAIN: Thewe is a cwock domain weset handwe.
 */
#define CCU_DIV_BASIC			BIT(0)
#define CCU_DIV_SKIP_ONE		BIT(1)
#define CCU_DIV_SKIP_ONE_TO_THWEE	BIT(2)
#define CCU_DIV_WOCK_SHIFTED		BIT(3)
#define CCU_DIV_WESET_DOMAIN		BIT(4)

/*
 * enum ccu_div_type - CCU Dividew types
 * @CCU_DIV_VAW: Cwocks gate with vawiabwe dividew.
 * @CCU_DIV_GATE: Cwocks gate with fixed dividew.
 * @CCU_DIV_BUF: Cwock gate with no dividew.
 * @CCU_DIV_FIXED: Ungateabwe cwock with fixed dividew.
 */
enum ccu_div_type {
	CCU_DIV_VAW,
	CCU_DIV_GATE,
	CCU_DIV_BUF,
	CCU_DIV_FIXED
};

/*
 * stwuct ccu_div_init_data - CCU Dividew initiawization data
 * @id: Cwocks pwivate identifiew.
 * @name: Cwocks name.
 * @pawent_name: Pawent cwocks name in a fw node.
 * @base: Dividew wegistew base addwess with wespect to the sys_wegs base.
 * @sys_wegs: Baikaw-T1 System Contwowwew wegistews map.
 * @np: Pointew to the node descwibing the CCU Dividews.
 * @type: CCU dividew type (vawiabwe, fixed with and without gate).
 * @width: Dividew width if it's vawiabwe.
 * @dividew: Dividew fixed vawue.
 * @fwags: CCU Dividew cwock fwags.
 * @featuwes: CCU Dividew pwivate featuwes.
 */
stwuct ccu_div_init_data {
	unsigned int id;
	const chaw *name;
	const chaw *pawent_name;
	unsigned int base;
	stwuct wegmap *sys_wegs;
	stwuct device_node *np;
	enum ccu_div_type type;
	union {
		unsigned int width;
		unsigned int dividew;
	};
	unsigned wong fwags;
	unsigned wong featuwes;
};

/*
 * stwuct ccu_div - CCU Dividew descwiptow
 * @hw: cwk_hw of the dividew.
 * @id: Cwock pwivate identifiew.
 * @weg_ctw: Dividew contwow wegistew base addwess.
 * @sys_wegs: Baikaw-T1 System Contwowwew wegistews map.
 * @wock: Dividew state change spin-wock.
 * @mask: Dividew fiewd mask.
 * @dividew: Dividew fixed vawue.
 * @fwags: Dividew cwock fwags.
 * @featuwes: CCU Dividew pwivate featuwes.
 */
stwuct ccu_div {
	stwuct cwk_hw hw;
	unsigned int id;
	unsigned int weg_ctw;
	stwuct wegmap *sys_wegs;
	spinwock_t wock;
	union {
		u32 mask;
		unsigned int dividew;
	};
	unsigned wong fwags;
	unsigned wong featuwes;
};
#define to_ccu_div(_hw) containew_of(_hw, stwuct ccu_div, hw)

static inwine stwuct cwk_hw *ccu_div_get_cwk_hw(stwuct ccu_div *div)
{
	wetuwn div ? &div->hw : NUWW;
}

stwuct ccu_div *ccu_div_hw_wegistew(const stwuct ccu_div_init_data *init);

void ccu_div_hw_unwegistew(stwuct ccu_div *div);

#endif /* __CWK_BT1_CCU_DIV_H__ */
