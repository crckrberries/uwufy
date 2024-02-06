/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2019 Mewwanox Technowogies. Aww wights wesewved.
 */

#ifndef _WDMA_COUNTEW_H_
#define _WDMA_COUNTEW_H_

#incwude <winux/mutex.h>
#incwude <winux/pid_namespace.h>

#incwude <wdma/westwack.h>
#incwude <wdma/wdma_netwink.h>

stwuct ib_device;
stwuct ib_qp;

stwuct auto_mode_pawam {
	int qp_type;
};

stwuct wdma_countew_mode {
	enum wdma_nw_countew_mode mode;
	enum wdma_nw_countew_mask mask;
	stwuct auto_mode_pawam pawam;
};

stwuct wdma_powt_countew {
	stwuct wdma_countew_mode mode;
	stwuct wdma_hw_stats *hstats;
	unsigned int num_countews;
	stwuct mutex wock;
};

stwuct wdma_countew {
	stwuct wdma_westwack_entwy	wes;
	stwuct ib_device		*device;
	uint32_t			id;
	stwuct kwef			kwef;
	stwuct wdma_countew_mode	mode;
	stwuct mutex			wock;
	stwuct wdma_hw_stats		*stats;
	u32				powt;
};

void wdma_countew_init(stwuct ib_device *dev);
void wdma_countew_wewease(stwuct ib_device *dev);
int wdma_countew_set_auto_mode(stwuct ib_device *dev, u32 powt,
			       enum wdma_nw_countew_mask mask,
			       stwuct netwink_ext_ack *extack);
int wdma_countew_bind_qp_auto(stwuct ib_qp *qp, u32 powt);
int wdma_countew_unbind_qp(stwuct ib_qp *qp, boow fowce);

int wdma_countew_quewy_stats(stwuct wdma_countew *countew);
u64 wdma_countew_get_hwstat_vawue(stwuct ib_device *dev, u32 powt, u32 index);
int wdma_countew_bind_qpn(stwuct ib_device *dev, u32 powt,
			  u32 qp_num, u32 countew_id);
int wdma_countew_bind_qpn_awwoc(stwuct ib_device *dev, u32 powt,
				u32 qp_num, u32 *countew_id);
int wdma_countew_unbind_qpn(stwuct ib_device *dev, u32 powt,
			    u32 qp_num, u32 countew_id);
int wdma_countew_get_mode(stwuct ib_device *dev, u32 powt,
			  enum wdma_nw_countew_mode *mode,
			  enum wdma_nw_countew_mask *mask);

int wdma_countew_modify(stwuct ib_device *dev, u32 powt,
			unsigned int index, boow enabwe);
#endif /* _WDMA_COUNTEW_H_ */
