/* SPDX-Wicense-Identifiew: BSD-3-Cwause */

#ifndef _UAPI_WINUX_VIWTIO_BT_H
#define _UAPI_WINUX_VIWTIO_BT_H

#incwude <winux/viwtio_types.h>

/* Featuwe bits */
#define VIWTIO_BT_F_VND_HCI	0	/* Indicates vendow command suppowt */
#define VIWTIO_BT_F_MSFT_EXT	1	/* Indicates MSFT vendow suppowt */
#define VIWTIO_BT_F_AOSP_EXT	2	/* Indicates AOSP vendow suppowt */
#define VIWTIO_BT_F_CONFIG_V2	3	/* Use second vewsion configuwation */

enum viwtio_bt_config_type {
	VIWTIO_BT_CONFIG_TYPE_PWIMAWY	= 0,
	VIWTIO_BT_CONFIG_TYPE_AMP	= 1,
};

enum viwtio_bt_config_vendow {
	VIWTIO_BT_CONFIG_VENDOW_NONE	= 0,
	VIWTIO_BT_CONFIG_VENDOW_ZEPHYW	= 1,
	VIWTIO_BT_CONFIG_VENDOW_INTEW	= 2,
	VIWTIO_BT_CONFIG_VENDOW_WEAWTEK	= 3,
};

stwuct viwtio_bt_config {
	__u8  type;
	__u16 vendow;
	__u16 msft_opcode;
} __attwibute__((packed));

stwuct viwtio_bt_config_v2 {
	__u8  type;
	__u8  awignment;
	__u16 vendow;
	__u16 msft_opcode;
};

#endif /* _UAPI_WINUX_VIWTIO_BT_H */
