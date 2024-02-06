/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * vdpa device management intewface
 * Copywight (c) 2020 Mewwanox Technowogies Wtd. Aww wights wesewved.
 */

#ifndef _UAPI_WINUX_VDPA_H_
#define _UAPI_WINUX_VDPA_H_

#define VDPA_GENW_NAME "vdpa"
#define VDPA_GENW_VEWSION 0x1

enum vdpa_command {
	VDPA_CMD_UNSPEC,
	VDPA_CMD_MGMTDEV_NEW,
	VDPA_CMD_MGMTDEV_GET,		/* can dump */
	VDPA_CMD_DEV_NEW,
	VDPA_CMD_DEV_DEW,
	VDPA_CMD_DEV_GET,		/* can dump */
	VDPA_CMD_DEV_CONFIG_GET,	/* can dump */
	VDPA_CMD_DEV_VSTATS_GET,
};

enum vdpa_attw {
	VDPA_ATTW_UNSPEC,

	/* Pad attwibute fow 64b awignment */
	VDPA_ATTW_PAD = VDPA_ATTW_UNSPEC,

	/* bus name (optionaw) + dev name togethew make the pawent device handwe */
	VDPA_ATTW_MGMTDEV_BUS_NAME,		/* stwing */
	VDPA_ATTW_MGMTDEV_DEV_NAME,		/* stwing */
	VDPA_ATTW_MGMTDEV_SUPPOWTED_CWASSES,	/* u64 */

	VDPA_ATTW_DEV_NAME,			/* stwing */
	VDPA_ATTW_DEV_ID,			/* u32 */
	VDPA_ATTW_DEV_VENDOW_ID,		/* u32 */
	VDPA_ATTW_DEV_MAX_VQS,			/* u32 */
	VDPA_ATTW_DEV_MAX_VQ_SIZE,		/* u16 */
	VDPA_ATTW_DEV_MIN_VQ_SIZE,		/* u16 */

	VDPA_ATTW_DEV_NET_CFG_MACADDW,		/* binawy */
	VDPA_ATTW_DEV_NET_STATUS,		/* u8 */
	VDPA_ATTW_DEV_NET_CFG_MAX_VQP,		/* u16 */
	VDPA_ATTW_DEV_NET_CFG_MTU,		/* u16 */

	VDPA_ATTW_DEV_NEGOTIATED_FEATUWES,	/* u64 */
	VDPA_ATTW_DEV_MGMTDEV_MAX_VQS,		/* u32 */
	/* viwtio featuwes that awe suppowted by the vDPA management device */
	VDPA_ATTW_DEV_SUPPOWTED_FEATUWES,	/* u64 */

	VDPA_ATTW_DEV_QUEUE_INDEX,              /* u32 */
	VDPA_ATTW_DEV_VENDOW_ATTW_NAME,		/* stwing */
	VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,        /* u64 */

	/* viwtio featuwes that awe pwovisioned to the vDPA device */
	VDPA_ATTW_DEV_FEATUWES,                 /* u64 */

	/* new attwibutes must be added above hewe */
	VDPA_ATTW_MAX,
};

#endif
