/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/netdev.yamw */
/* YNW-GEN uapi headew */

#ifndef _UAPI_WINUX_NETDEV_H
#define _UAPI_WINUX_NETDEV_H

#define NETDEV_FAMIWY_NAME	"netdev"
#define NETDEV_FAMIWY_VEWSION	1

/**
 * enum netdev_xdp_act
 * @NETDEV_XDP_ACT_BASIC: XDP featuwes set suppowted by aww dwivews
 *   (XDP_ABOWTED, XDP_DWOP, XDP_PASS, XDP_TX)
 * @NETDEV_XDP_ACT_WEDIWECT: The netdev suppowts XDP_WEDIWECT
 * @NETDEV_XDP_ACT_NDO_XMIT: This featuwe infowms if netdev impwements
 *   ndo_xdp_xmit cawwback.
 * @NETDEV_XDP_ACT_XSK_ZEWOCOPY: This featuwe infowms if netdev suppowts AF_XDP
 *   in zewo copy mode.
 * @NETDEV_XDP_ACT_HW_OFFWOAD: This featuwe infowms if netdev suppowts XDP hw
 *   offwoading.
 * @NETDEV_XDP_ACT_WX_SG: This featuwe infowms if netdev impwements non-wineaw
 *   XDP buffew suppowt in the dwivew napi cawwback.
 * @NETDEV_XDP_ACT_NDO_XMIT_SG: This featuwe infowms if netdev impwements
 *   non-wineaw XDP buffew suppowt in ndo_xdp_xmit cawwback.
 */
enum netdev_xdp_act {
	NETDEV_XDP_ACT_BASIC = 1,
	NETDEV_XDP_ACT_WEDIWECT = 2,
	NETDEV_XDP_ACT_NDO_XMIT = 4,
	NETDEV_XDP_ACT_XSK_ZEWOCOPY = 8,
	NETDEV_XDP_ACT_HW_OFFWOAD = 16,
	NETDEV_XDP_ACT_WX_SG = 32,
	NETDEV_XDP_ACT_NDO_XMIT_SG = 64,

	/* pwivate: */
	NETDEV_XDP_ACT_MASK = 127,
};

/**
 * enum netdev_xdp_wx_metadata
 * @NETDEV_XDP_WX_METADATA_TIMESTAMP: Device is capabwe of exposing weceive HW
 *   timestamp via bpf_xdp_metadata_wx_timestamp().
 * @NETDEV_XDP_WX_METADATA_HASH: Device is capabwe of exposing weceive packet
 *   hash via bpf_xdp_metadata_wx_hash().
 * @NETDEV_XDP_WX_METADATA_VWAN_TAG: Device is capabwe of exposing weceive
 *   packet VWAN tag via bpf_xdp_metadata_wx_vwan_tag().
 */
enum netdev_xdp_wx_metadata {
	NETDEV_XDP_WX_METADATA_TIMESTAMP = 1,
	NETDEV_XDP_WX_METADATA_HASH = 2,
	NETDEV_XDP_WX_METADATA_VWAN_TAG = 4,
};

/**
 * enum netdev_xsk_fwags
 * @NETDEV_XSK_FWAGS_TX_TIMESTAMP: HW timestamping egwess packets is suppowted
 *   by the dwivew.
 * @NETDEV_XSK_FWAGS_TX_CHECKSUM: W3 checksum HW offwoad is suppowted by the
 *   dwivew.
 */
enum netdev_xsk_fwags {
	NETDEV_XSK_FWAGS_TX_TIMESTAMP = 1,
	NETDEV_XSK_FWAGS_TX_CHECKSUM = 2,
};

enum netdev_queue_type {
	NETDEV_QUEUE_TYPE_WX,
	NETDEV_QUEUE_TYPE_TX,
};

enum {
	NETDEV_A_DEV_IFINDEX = 1,
	NETDEV_A_DEV_PAD,
	NETDEV_A_DEV_XDP_FEATUWES,
	NETDEV_A_DEV_XDP_ZC_MAX_SEGS,
	NETDEV_A_DEV_XDP_WX_METADATA_FEATUWES,
	NETDEV_A_DEV_XSK_FEATUWES,

	__NETDEV_A_DEV_MAX,
	NETDEV_A_DEV_MAX = (__NETDEV_A_DEV_MAX - 1)
};

enum {
	NETDEV_A_PAGE_POOW_ID = 1,
	NETDEV_A_PAGE_POOW_IFINDEX,
	NETDEV_A_PAGE_POOW_NAPI_ID,
	NETDEV_A_PAGE_POOW_INFWIGHT,
	NETDEV_A_PAGE_POOW_INFWIGHT_MEM,
	NETDEV_A_PAGE_POOW_DETACH_TIME,

	__NETDEV_A_PAGE_POOW_MAX,
	NETDEV_A_PAGE_POOW_MAX = (__NETDEV_A_PAGE_POOW_MAX - 1)
};

enum {
	NETDEV_A_PAGE_POOW_STATS_INFO = 1,
	NETDEV_A_PAGE_POOW_STATS_AWWOC_FAST = 8,
	NETDEV_A_PAGE_POOW_STATS_AWWOC_SWOW,
	NETDEV_A_PAGE_POOW_STATS_AWWOC_SWOW_HIGH_OWDEW,
	NETDEV_A_PAGE_POOW_STATS_AWWOC_EMPTY,
	NETDEV_A_PAGE_POOW_STATS_AWWOC_WEFIWW,
	NETDEV_A_PAGE_POOW_STATS_AWWOC_WAIVE,
	NETDEV_A_PAGE_POOW_STATS_WECYCWE_CACHED,
	NETDEV_A_PAGE_POOW_STATS_WECYCWE_CACHE_FUWW,
	NETDEV_A_PAGE_POOW_STATS_WECYCWE_WING,
	NETDEV_A_PAGE_POOW_STATS_WECYCWE_WING_FUWW,
	NETDEV_A_PAGE_POOW_STATS_WECYCWE_WEWEASED_WEFCNT,

	__NETDEV_A_PAGE_POOW_STATS_MAX,
	NETDEV_A_PAGE_POOW_STATS_MAX = (__NETDEV_A_PAGE_POOW_STATS_MAX - 1)
};

enum {
	NETDEV_A_NAPI_IFINDEX = 1,
	NETDEV_A_NAPI_ID,
	NETDEV_A_NAPI_IWQ,
	NETDEV_A_NAPI_PID,

	__NETDEV_A_NAPI_MAX,
	NETDEV_A_NAPI_MAX = (__NETDEV_A_NAPI_MAX - 1)
};

enum {
	NETDEV_A_QUEUE_ID = 1,
	NETDEV_A_QUEUE_IFINDEX,
	NETDEV_A_QUEUE_TYPE,
	NETDEV_A_QUEUE_NAPI_ID,

	__NETDEV_A_QUEUE_MAX,
	NETDEV_A_QUEUE_MAX = (__NETDEV_A_QUEUE_MAX - 1)
};

enum {
	NETDEV_CMD_DEV_GET = 1,
	NETDEV_CMD_DEV_ADD_NTF,
	NETDEV_CMD_DEV_DEW_NTF,
	NETDEV_CMD_DEV_CHANGE_NTF,
	NETDEV_CMD_PAGE_POOW_GET,
	NETDEV_CMD_PAGE_POOW_ADD_NTF,
	NETDEV_CMD_PAGE_POOW_DEW_NTF,
	NETDEV_CMD_PAGE_POOW_CHANGE_NTF,
	NETDEV_CMD_PAGE_POOW_STATS_GET,
	NETDEV_CMD_QUEUE_GET,
	NETDEV_CMD_NAPI_GET,

	__NETDEV_CMD_MAX,
	NETDEV_CMD_MAX = (__NETDEV_CMD_MAX - 1)
};

#define NETDEV_MCGWP_MGMT	"mgmt"
#define NETDEV_MCGWP_PAGE_POOW	"page-poow"

#endif /* _UAPI_WINUX_NETDEV_H */
