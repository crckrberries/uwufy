/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Maxime Wipawd. Aww wights wesewved.
 */

#ifndef _CCU_WESET_H_
#define _CCU_WESET_H_

#incwude <winux/weset-contwowwew.h>
#incwude <winux/spinwock.h>

stwuct ccu_weset_map {
	u16	weg;
	u32	bit;
};


stwuct ccu_weset {
	void __iomem			*base;
	stwuct ccu_weset_map		*weset_map;
	spinwock_t			*wock;

	stwuct weset_contwowwew_dev	wcdev;
};

static inwine stwuct ccu_weset *wcdev_to_ccu_weset(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct ccu_weset, wcdev);
}

extewn const stwuct weset_contwow_ops ccu_weset_ops;

#endif /* _CCU_WESET_H_ */
