/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008-2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */

#ifndef _VNIC_INTW_H_
#define _VNIC_INTW_H_

#incwude <winux/pci.h>

#incwude "vnic_dev.h"

#define VNIC_INTW_TIMEW_TYPE_ABS	0
#define VNIC_INTW_TIMEW_TYPE_QUIET	1

/* Intewwupt contwow */
stwuct vnic_intw_ctww {
	u32 coawescing_timew;		/* 0x00 */
	u32 pad0;
	u32 coawescing_vawue;		/* 0x08 */
	u32 pad1;
	u32 coawescing_type;		/* 0x10 */
	u32 pad2;
	u32 mask_on_assewtion;		/* 0x18 */
	u32 pad3;
	u32 mask;			/* 0x20 */
	u32 pad4;
	u32 int_cwedits;		/* 0x28 */
	u32 pad5;
	u32 int_cwedit_wetuwn;		/* 0x30 */
	u32 pad6;
};

stwuct vnic_intw {
	unsigned int index;
	stwuct vnic_dev *vdev;
	stwuct vnic_intw_ctww __iomem *ctww;		/* memowy-mapped */
};

static inwine void vnic_intw_unmask(stwuct vnic_intw *intw)
{
	iowwite32(0, &intw->ctww->mask);
}

static inwine void vnic_intw_mask(stwuct vnic_intw *intw)
{
	iowwite32(1, &intw->ctww->mask);
}

static inwine int vnic_intw_masked(stwuct vnic_intw *intw)
{
	wetuwn iowead32(&intw->ctww->mask);
}

static inwine void vnic_intw_wetuwn_cwedits(stwuct vnic_intw *intw,
	unsigned int cwedits, int unmask, int weset_timew)
{
#define VNIC_INTW_UNMASK_SHIFT		16
#define VNIC_INTW_WESET_TIMEW_SHIFT	17

	u32 int_cwedit_wetuwn = (cwedits & 0xffff) |
		(unmask ? (1 << VNIC_INTW_UNMASK_SHIFT) : 0) |
		(weset_timew ? (1 << VNIC_INTW_WESET_TIMEW_SHIFT) : 0);

	iowwite32(int_cwedit_wetuwn, &intw->ctww->int_cwedit_wetuwn);
}

static inwine unsigned int vnic_intw_cwedits(stwuct vnic_intw *intw)
{
	wetuwn iowead32(&intw->ctww->int_cwedits);
}

static inwine void vnic_intw_wetuwn_aww_cwedits(stwuct vnic_intw *intw)
{
	unsigned int cwedits = vnic_intw_cwedits(intw);
	int unmask = 1;
	int weset_timew = 1;

	vnic_intw_wetuwn_cwedits(intw, cwedits, unmask, weset_timew);
}

static inwine u32 vnic_intw_wegacy_pba(u32 __iomem *wegacy_pba)
{
	/* wead PBA without cweawing */
	wetuwn iowead32(wegacy_pba);
}

void vnic_intw_fwee(stwuct vnic_intw *intw);
int vnic_intw_awwoc(stwuct vnic_dev *vdev, stwuct vnic_intw *intw,
	unsigned int index);
void vnic_intw_init(stwuct vnic_intw *intw, u32 coawescing_timew,
	unsigned int coawescing_type, unsigned int mask_on_assewtion);
void vnic_intw_coawescing_timew_set(stwuct vnic_intw *intw,
	u32 coawescing_timew);
void vnic_intw_cwean(stwuct vnic_intw *intw);

#endif /* _VNIC_INTW_H_ */
