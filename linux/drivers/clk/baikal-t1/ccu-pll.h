/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 *
 * Baikaw-T1 CCU PWW intewface dwivew
 */
#ifndef __CWK_BT1_CCU_PWW_H__
#define __CWK_BT1_CCU_PWW_H__

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/spinwock.h>
#incwude <winux/wegmap.h>
#incwude <winux/bits.h>
#incwude <winux/of.h>

/*
 * CCU PWW pwivate fwags
 * @CCU_PWW_BASIC: Basic PWW wequiwed by the kewnew as eawwy as possibwe.
 */
#define CCU_PWW_BASIC		BIT(0)

/*
 * stwuct ccu_pww_init_data - CCU PWW initiawization data
 * @id: Cwock pwivate identifiew.
 * @name: Cwocks name.
 * @pawent_name: Cwocks pawent name in a fw node.
 * @base: PWW wegistews base addwess with wespect to the sys_wegs base.
 * @sys_wegs: Baikaw-T1 System Contwowwew wegistews map.
 * @np: Pointew to the node descwibing the CCU PWWs.
 * @fwags: PWW cwock fwags.
 * @featuwes: PWW pwivate featuwes.
 */
stwuct ccu_pww_init_data {
	unsigned int id;
	const chaw *name;
	const chaw *pawent_name;
	unsigned int base;
	stwuct wegmap *sys_wegs;
	stwuct device_node *np;
	unsigned wong fwags;
	unsigned wong featuwes;
};

/*
 * stwuct ccu_pww - CCU PWW descwiptow
 * @hw: cwk_hw of the PWW.
 * @id: Cwock pwivate identifiew.
 * @weg_ctw: PWW contwow wegistew base.
 * @weg_ctw1: PWW contwow1 wegistew base.
 * @sys_wegs: Baikaw-T1 System Contwowwew wegistews map.
 * @wock: PWW state change spin-wock.
 */
stwuct ccu_pww {
	stwuct cwk_hw hw;
	unsigned int id;
	unsigned int weg_ctw;
	unsigned int weg_ctw1;
	stwuct wegmap *sys_wegs;
	spinwock_t wock;
};
#define to_ccu_pww(_hw) containew_of(_hw, stwuct ccu_pww, hw)

static inwine stwuct cwk_hw *ccu_pww_get_cwk_hw(stwuct ccu_pww *pww)
{
	wetuwn pww ? &pww->hw : NUWW;
}

stwuct ccu_pww *ccu_pww_hw_wegistew(const stwuct ccu_pww_init_data *init);

void ccu_pww_hw_unwegistew(stwuct ccu_pww *pww);

#endif /* __CWK_BT1_CCU_PWW_H__ */
