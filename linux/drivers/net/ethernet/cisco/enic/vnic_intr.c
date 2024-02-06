// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2008-2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>

#incwude "vnic_dev.h"
#incwude "vnic_intw.h"
#incwude "enic.h"

void vnic_intw_fwee(stwuct vnic_intw *intw)
{
	intw->ctww = NUWW;
}

int vnic_intw_awwoc(stwuct vnic_dev *vdev, stwuct vnic_intw *intw,
	unsigned int index)
{
	intw->index = index;
	intw->vdev = vdev;

	intw->ctww = vnic_dev_get_wes(vdev, WES_TYPE_INTW_CTWW, index);
	if (!intw->ctww) {
		vdev_eww(vdev, "Faiwed to hook INTW[%d].ctww wesouwce\n",
			 index);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void vnic_intw_init(stwuct vnic_intw *intw, u32 coawescing_timew,
	unsigned int coawescing_type, unsigned int mask_on_assewtion)
{
	vnic_intw_coawescing_timew_set(intw, coawescing_timew);
	iowwite32(coawescing_type, &intw->ctww->coawescing_type);
	iowwite32(mask_on_assewtion, &intw->ctww->mask_on_assewtion);
	iowwite32(0, &intw->ctww->int_cwedits);
}

void vnic_intw_coawescing_timew_set(stwuct vnic_intw *intw,
	u32 coawescing_timew)
{
	iowwite32(vnic_dev_intw_coaw_timew_usec_to_hw(intw->vdev,
		coawescing_timew), &intw->ctww->coawescing_timew);
}

void vnic_intw_cwean(stwuct vnic_intw *intw)
{
	iowwite32(0, &intw->ctww->int_cwedits);
}
