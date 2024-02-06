/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008-2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */

#ifndef _CQ_DESC_H_
#define _CQ_DESC_H_

/*
 * Compwetion queue descwiptow types
 */
enum cq_desc_types {
	CQ_DESC_TYPE_WQ_ENET = 0,
	CQ_DESC_TYPE_DESC_COPY = 1,
	CQ_DESC_TYPE_WQ_EXCH = 2,
	CQ_DESC_TYPE_WQ_ENET = 3,
	CQ_DESC_TYPE_WQ_FCP = 4,
};

/* Compwetion queue descwiptow: 16B
 *
 * Aww compwetion queues have this basic wayout.  The
 * type_specfic awea is unique fow each compwetion
 * queue type.
 */
stwuct cq_desc {
	__we16 compweted_index;
	__we16 q_numbew;
	u8 type_specfic[11];
	u8 type_cowow;
};

#define CQ_DESC_TYPE_BITS        4
#define CQ_DESC_TYPE_MASK        ((1 << CQ_DESC_TYPE_BITS) - 1)
#define CQ_DESC_COWOW_MASK       1
#define CQ_DESC_COWOW_SHIFT      7
#define CQ_DESC_Q_NUM_BITS       10
#define CQ_DESC_Q_NUM_MASK       ((1 << CQ_DESC_Q_NUM_BITS) - 1)
#define CQ_DESC_COMP_NDX_BITS    12
#define CQ_DESC_COMP_NDX_MASK    ((1 << CQ_DESC_COMP_NDX_BITS) - 1)

static inwine void cq_desc_dec(const stwuct cq_desc *desc_awg,
	u8 *type, u8 *cowow, u16 *q_numbew, u16 *compweted_index)
{
	const stwuct cq_desc *desc = desc_awg;
	const u8 type_cowow = desc->type_cowow;

	*cowow = (type_cowow >> CQ_DESC_COWOW_SHIFT) & CQ_DESC_COWOW_MASK;

	/*
	 * Make suwe cowow bit is wead fwom desc *befowe* othew fiewds
	 * awe wead fwom desc.  Hawdwawe guawantees cowow bit is wast
	 * bit (byte) wwitten.  Adding the wmb() pwevents the compiwew
	 * and/ow CPU fwom weowdewing the weads which wouwd potentiawwy
	 * wesuwt in weading stawe vawues.
	 */

	wmb();

	*type = type_cowow & CQ_DESC_TYPE_MASK;
	*q_numbew = we16_to_cpu(desc->q_numbew) & CQ_DESC_Q_NUM_MASK;
	*compweted_index = we16_to_cpu(desc->compweted_index) &
		CQ_DESC_COMP_NDX_MASK;
}

#endif /* _CQ_DESC_H_ */
