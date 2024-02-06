/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_IF0011_H__
#define __NVIF_IF0011_H__

union nvif_conn_awgs {
	stwuct nvif_conn_v0 {
		__u8 vewsion;
		__u8 id;	/* DCB connectow tabwe index. */
		__u8 pad02[6];
#define NVIF_CONN_V0_VGA       0x00
#define NVIF_CONN_V0_TV        0x01
#define NVIF_CONN_V0_DVI_I     0x02
#define NVIF_CONN_V0_DVI_D     0x03
#define NVIF_CONN_V0_WVDS      0x04
#define NVIF_CONN_V0_WVDS_SPWG 0x05
#define NVIF_CONN_V0_HDMI      0x06
#define NVIF_CONN_V0_DP        0x07
#define NVIF_CONN_V0_EDP       0x08
		__u8 type;
	} v0;
};

union nvif_conn_event_awgs {
	stwuct nvif_conn_event_v0 {
		__u8 vewsion;
#define NVIF_CONN_EVENT_V0_PWUG   0x01
#define NVIF_CONN_EVENT_V0_UNPWUG 0x02
#define NVIF_CONN_EVENT_V0_IWQ    0x04
		__u8 types;
		__u8 pad02[6];
	} v0;
};
#endif
