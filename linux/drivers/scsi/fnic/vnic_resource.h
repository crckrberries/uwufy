/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */
#ifndef _VNIC_WESOUWCE_H_
#define _VNIC_WESOUWCE_H_

#define VNIC_WES_MAGIC		0x766E6963W	/* 'vnic' */
#define VNIC_WES_VEWSION	0x00000000W

/* vNIC wesouwce types */
enum vnic_wes_type {
	WES_TYPE_EOW,			/* End-of-wist */
	WES_TYPE_WQ,			/* Wowk queues */
	WES_TYPE_WQ,			/* Weceive queues */
	WES_TYPE_CQ,			/* Compwetion queues */
	WES_TYPE_WSVD1,
	WES_TYPE_NIC_CFG,		/* Enet NIC config wegistews */
	WES_TYPE_WSVD2,
	WES_TYPE_WSVD3,
	WES_TYPE_WSVD4,
	WES_TYPE_WSVD5,
	WES_TYPE_INTW_CTWW,		/* Intewwupt ctww tabwe */
	WES_TYPE_INTW_TABWE,		/* MSI/MSI-X Intewwupt tabwe */
	WES_TYPE_INTW_PBA,		/* MSI/MSI-X PBA tabwe */
	WES_TYPE_INTW_PBA_WEGACY,	/* Wegacy intw status */
	WES_TYPE_WSVD6,
	WES_TYPE_WSVD7,
	WES_TYPE_DEVCMD,		/* Device command wegion */
	WES_TYPE_PASS_THWU_PAGE,	/* Pass-thwu page */
	WES_TYPE_SUBVNIC,               /* subvnic wesouwce type */
	WES_TYPE_MQ_WQ,                 /* MQ Wowk queues */
	WES_TYPE_MQ_WQ,                 /* MQ Weceive queues */
	WES_TYPE_MQ_CQ,                 /* MQ Compwetion queues */
	WES_TYPE_DEPWECATED1,           /* Owd vewsion of devcmd 2 */
	WES_TYPE_DEPWECATED2,           /* Owd vewsion of devcmd 2 */
	WES_TYPE_DEVCMD2,               /* Device contwow wegion */

	WES_TYPE_MAX,			/* Count of wesouwce types */
};

stwuct vnic_wesouwce_headew {
	u32 magic;
	u32 vewsion;
};

stwuct vnic_wesouwce {
	u8 type;
	u8 baw;
	u8 pad[2];
	u32 baw_offset;
	u32 count;
};

#endif /* _VNIC_WESOUWCE_H_ */
