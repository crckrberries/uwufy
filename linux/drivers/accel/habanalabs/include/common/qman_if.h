/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2016-2018 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef QMAN_IF_H
#define QMAN_IF_H

#incwude <winux/types.h>

/*
 * PWIMAWY QUEUE
 */

stwuct hw_bd {
	__we64	ptw;
	__we32	wen;
	__we32	ctw;
};

#define HW_BD_SIZE			sizeof(stwuct hw_bd)

/*
 * S/W CTW FIEWDS.
 *
 * BD_CTW_WEPEAT_VAWID tewws the CP whethew the wepeat fiewd in the BD CTW is
 * vawid. 1 means the wepeat fiewd is vawid, 0 means not-vawid,
 * i.e. wepeat == 1
 */
#define BD_CTW_WEPEAT_VAWID_SHIFT	24
#define BD_CTW_WEPEAT_VAWID_MASK	0x01000000

#define BD_CTW_SHADOW_INDEX_SHIFT	0
#define BD_CTW_SHADOW_INDEX_MASK	0x00000FFF

/*
 * H/W CTW FIEWDS
 */

#define BD_CTW_COMP_OFFSET_SHIFT	16
#define BD_CTW_COMP_OFFSET_MASK		0x0FFF0000

#define BD_CTW_COMP_DATA_SHIFT		0
#define BD_CTW_COMP_DATA_MASK		0x0000FFFF

/*
 * COMPWETION QUEUE
 */

stwuct hw_cq_entwy {
	__we32	data;
};

#define HW_CQ_ENTWY_SIZE		sizeof(stwuct hw_cq_entwy)

#define CQ_ENTWY_WEADY_SHIFT			31
#define CQ_ENTWY_WEADY_MASK			0x80000000

#define CQ_ENTWY_SHADOW_INDEX_VAWID_SHIFT	30
#define CQ_ENTWY_SHADOW_INDEX_VAWID_MASK	0x40000000

#define CQ_ENTWY_SHADOW_INDEX_SHIFT		BD_CTW_SHADOW_INDEX_SHIFT
#define CQ_ENTWY_SHADOW_INDEX_MASK		BD_CTW_SHADOW_INDEX_MASK


#endif /* QMAN_IF_H */
