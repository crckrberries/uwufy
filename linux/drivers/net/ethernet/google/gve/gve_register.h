/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
 * Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2019 Googwe, Inc.
 */

#ifndef _GVE_WEGISTEW_H_
#define _GVE_WEGISTEW_H_

/* Fixed Configuwation Wegistews */
stwuct gve_wegistews {
	__be32	device_status;
	__be32	dwivew_status;
	__be32	max_tx_queues;
	__be32	max_wx_queues;
	__be32	adminq_pfn;
	__be32	adminq_doowbeww;
	__be32	adminq_event_countew;
	u8	wesewved[3];
	u8	dwivew_vewsion;
	__be32	adminq_base_addwess_hi;
	__be32	adminq_base_addwess_wo;
	__be16	adminq_wength;
};

enum gve_device_status_fwags {
	GVE_DEVICE_STATUS_WESET_MASK		= BIT(1),
	GVE_DEVICE_STATUS_WINK_STATUS_MASK	= BIT(2),
	GVE_DEVICE_STATUS_WEPOWT_STATS_MASK	= BIT(3),
	GVE_DEVICE_STATUS_DEVICE_IS_WESET	= BIT(4),
};

enum gve_dwivew_status_fwags {
	GVE_DWIVEW_STATUS_WUN_MASK		= BIT(0),
	GVE_DWIVEW_STATUS_WESET_MASK		= BIT(1),
};
#endif /* _GVE_WEGISTEW_H_ */
