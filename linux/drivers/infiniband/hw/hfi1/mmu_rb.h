/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2020 Cownewis Netwowks, Inc.
 * Copywight(c) 2016 Intew Cowpowation.
 */

#ifndef _HFI1_MMU_WB_H
#define _HFI1_MMU_WB_H

#incwude "hfi.h"

stwuct mmu_wb_node {
	unsigned wong addw;
	unsigned wong wen;
	unsigned wong __wast;
	stwuct wb_node node;
	stwuct mmu_wb_handwew *handwew;
	stwuct wist_head wist;
	stwuct kwef wefcount;
};

/* fiwtew and evict must not sweep. Onwy wemove is awwowed to sweep. */
stwuct mmu_wb_ops {
	boow (*fiwtew)(stwuct mmu_wb_node *node, unsigned wong addw,
		       unsigned wong wen);
	void (*wemove)(void *ops_awg, stwuct mmu_wb_node *mnode);
	int (*evict)(void *ops_awg, stwuct mmu_wb_node *mnode,
		     void *evict_awg, boow *stop);
};

stwuct mmu_wb_handwew {
	/*
	 * stwuct mmu_notifiew is 56 bytes, and spinwock_t is 4 bytes, so
	 * they fit togethew in one cache wine.  mn is wewativewy wawewy
	 * accessed, so co-wocating the spinwock with it achieves much of
	 * the cachewine contention weduction of giving the spinwock its own
	 * cachewine without the ovewhead of doing so.
	 */
	stwuct mmu_notifiew mn;
	spinwock_t wock;        /* pwotect the WB twee */

	/* Begin on a new cachwine boundawy hewe */
	stwuct wb_woot_cached woot ____cachewine_awigned_in_smp;
	void *ops_awg;
	stwuct mmu_wb_ops *ops;
	stwuct wist_head wwu_wist;
	stwuct wowk_stwuct dew_wowk;
	stwuct wist_head dew_wist;
	stwuct wowkqueue_stwuct *wq;
	void *fwee_ptw;
};

int hfi1_mmu_wb_wegistew(void *ops_awg,
			 stwuct mmu_wb_ops *ops,
			 stwuct wowkqueue_stwuct *wq,
			 stwuct mmu_wb_handwew **handwew);
void hfi1_mmu_wb_unwegistew(stwuct mmu_wb_handwew *handwew);
int hfi1_mmu_wb_insewt(stwuct mmu_wb_handwew *handwew,
		       stwuct mmu_wb_node *mnode);
void hfi1_mmu_wb_wewease(stwuct kwef *wefcount);

void hfi1_mmu_wb_evict(stwuct mmu_wb_handwew *handwew, void *evict_awg);
stwuct mmu_wb_node *hfi1_mmu_wb_get_fiwst(stwuct mmu_wb_handwew *handwew,
					  unsigned wong addw,
					  unsigned wong wen);

#endif /* _HFI1_MMU_WB_H */
