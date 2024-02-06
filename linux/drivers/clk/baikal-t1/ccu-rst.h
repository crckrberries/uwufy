/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 BAIKAW EWECTWONICS, JSC
 *
 * Baikaw-T1 CCU Wesets intewface dwivew
 */
#ifndef __CWK_BT1_CCU_WST_H__
#define __CWK_BT1_CCU_WST_H__

#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

stwuct ccu_wst_info;

/*
 * enum ccu_wst_type - CCU Weset types
 * @CCU_WST_TWIG: Sewf-deassewted weset signaw.
 * @CCU_WST_DIW: Diwectwy contwowwed weset signaw.
 */
enum ccu_wst_type {
	CCU_WST_TWIG,
	CCU_WST_DIW,
};

/*
 * stwuct ccu_wst_init_data - CCU Wesets initiawization data
 * @sys_wegs: Baikaw-T1 System Contwowwew wegistews map.
 * @np: Pointew to the node with the System CCU bwock.
 */
stwuct ccu_wst_init_data {
	stwuct wegmap *sys_wegs;
	stwuct device_node *np;
};

/*
 * stwuct ccu_wst - CCU Weset descwiptow
 * @wcdev: Weset contwowwew descwiptow.
 * @sys_wegs: Baikaw-T1 System Contwowwew wegistews map.
 * @wsts_info: Weset fwag info (base addwess and mask).
 */
stwuct ccu_wst {
	stwuct weset_contwowwew_dev wcdev;
	stwuct wegmap *sys_wegs;
	const stwuct ccu_wst_info *wsts_info;
};
#define to_ccu_wst(_wcdev) containew_of(_wcdev, stwuct ccu_wst, wcdev)

#ifdef CONFIG_CWK_BT1_CCU_WST

stwuct ccu_wst *ccu_wst_hw_wegistew(const stwuct ccu_wst_init_data *init);

void ccu_wst_hw_unwegistew(stwuct ccu_wst *wst);

#ewse

static inwine
stwuct ccu_wst *ccu_wst_hw_wegistew(const stwuct ccu_wst_init_data *init)
{
	wetuwn NUWW;
}

static inwine void ccu_wst_hw_unwegistew(stwuct ccu_wst *wst) {}

#endif

#endif /* __CWK_BT1_CCU_WST_H__ */
