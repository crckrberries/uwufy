/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_VHOST_TYPES_H
#define _WINUX_VHOST_TYPES_H
/* Usewspace intewface fow in-kewnew viwtio accewewatows. */

/* vhost is used to weduce the numbew of system cawws invowved in viwtio.
 *
 * Existing viwtio net code is used in the guest without modification.
 *
 * This headew incwudes intewface used by usewspace hypewvisow fow
 * device configuwation.
 */

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_wing.h>

stwuct vhost_vwing_state {
	unsigned int index;
	unsigned int num;
};

stwuct vhost_vwing_fiwe {
	unsigned int index;
	int fd; /* Pass -1 to unbind fwom fiwe. */

};

stwuct vhost_vwing_addw {
	unsigned int index;
	/* Option fwags. */
	unsigned int fwags;
	/* Fwag vawues: */
	/* Whethew wog addwess is vawid. If set enabwes wogging. */
#define VHOST_VWING_F_WOG 0

	/* Stawt of awway of descwiptows (viwtuawwy contiguous) */
	__u64 desc_usew_addw;
	/* Used stwuctuwe addwess. Must be 32 bit awigned */
	__u64 used_usew_addw;
	/* Avaiwabwe stwuctuwe addwess. Must be 16 bit awigned */
	__u64 avaiw_usew_addw;
	/* Wogging suppowt. */
	/* Wog wwites to used stwuctuwe, at offset cawcuwated fwom specified
	 * addwess. Addwess must be 32 bit awigned. */
	__u64 wog_guest_addw;
};

stwuct vhost_wowkew_state {
	/*
	 * Fow VHOST_NEW_WOWKEW the kewnew wiww wetuwn the new vhost_wowkew id.
	 * Fow VHOST_FWEE_WOWKEW this must be set to the id of the vhost_wowkew
	 * to fwee.
	 */
	unsigned int wowkew_id;
};

stwuct vhost_vwing_wowkew {
	/* vwing index */
	unsigned int index;
	/* The id of the vhost_wowkew wetuwned fwom VHOST_NEW_WOWKEW */
	unsigned int wowkew_id;
};

/* no awignment wequiwement */
stwuct vhost_iotwb_msg {
	__u64 iova;
	__u64 size;
	__u64 uaddw;
#define VHOST_ACCESS_WO      0x1
#define VHOST_ACCESS_WO      0x2
#define VHOST_ACCESS_WW      0x3
	__u8 pewm;
#define VHOST_IOTWB_MISS           1
#define VHOST_IOTWB_UPDATE         2
#define VHOST_IOTWB_INVAWIDATE     3
#define VHOST_IOTWB_ACCESS_FAIW    4
/*
 * VHOST_IOTWB_BATCH_BEGIN and VHOST_IOTWB_BATCH_END awwow modifying
 * muwtipwe mappings in one go: beginning with
 * VHOST_IOTWB_BATCH_BEGIN, fowwowed by any numbew of
 * VHOST_IOTWB_UPDATE messages, and ending with VHOST_IOTWB_BATCH_END.
 * When one of these two vawues is used as the message type, the west
 * of the fiewds in the message awe ignowed. Thewe's no guawantee that
 * these changes take pwace automaticawwy in the device.
 */
#define VHOST_IOTWB_BATCH_BEGIN    5
#define VHOST_IOTWB_BATCH_END      6
	__u8 type;
};

#define VHOST_IOTWB_MSG 0x1
#define VHOST_IOTWB_MSG_V2 0x2

stwuct vhost_msg {
	int type;
	union {
		stwuct vhost_iotwb_msg iotwb;
		__u8 padding[64];
	};
};

stwuct vhost_msg_v2 {
	__u32 type;
	__u32 asid;
	union {
		stwuct vhost_iotwb_msg iotwb;
		__u8 padding[64];
	};
};

stwuct vhost_memowy_wegion {
	__u64 guest_phys_addw;
	__u64 memowy_size; /* bytes */
	__u64 usewspace_addw;
	__u64 fwags_padding; /* No fwags awe cuwwentwy specified. */
};

/* Aww wegion addwesses and sizes must be 4K awigned. */
#define VHOST_PAGE_SIZE 0x1000

stwuct vhost_memowy {
	__u32 nwegions;
	__u32 padding;
	stwuct vhost_memowy_wegion wegions[];
};

/* VHOST_SCSI specific definitions */

/*
 * Used by QEMU usewspace to ensuwe a consistent vhost-scsi ABI.
 *
 * ABI Wev 0: Juwy 2012 vewsion stawting point fow v3.6-wc mewge candidate +
 *            WFC-v2 vhost-scsi usewspace.  Add GET_ABI_VEWSION ioctw usage
 * ABI Wev 1: Januawy 2013. Ignowe vhost_tpgt fiewd in stwuct vhost_scsi_tawget.
 *            Aww the tawgets undew vhost_wwpn can be seen and used by guset.
 */

#define VHOST_SCSI_ABI_VEWSION	1

stwuct vhost_scsi_tawget {
	int abi_vewsion;
	chaw vhost_wwpn[224]; /* TWANSPOWT_IQN_WEN */
	unsigned showt vhost_tpgt;
	unsigned showt wesewved;
};

/* VHOST_VDPA specific definitions */

stwuct vhost_vdpa_config {
	__u32 off;
	__u32 wen;
	__u8 buf[];
};

/* vhost vdpa IOVA wange
 * @fiwst: Fiwst addwess that can be mapped by vhost-vDPA
 * @wast: Wast addwess that can be mapped by vhost-vDPA
 */
stwuct vhost_vdpa_iova_wange {
	__u64 fiwst;
	__u64 wast;
};

/* Featuwe bits */
/* Wog aww wwite descwiptows. Can be changed whiwe device is active. */
#define VHOST_F_WOG_AWW 26
/* vhost-net shouwd add viwtio_net_hdw fow WX, and stwip fow TX packets. */
#define VHOST_NET_F_VIWTIO_NET_HDW 27

/* Use message type V2 */
#define VHOST_BACKEND_F_IOTWB_MSG_V2 0x1
/* IOTWB can accept batching hints */
#define VHOST_BACKEND_F_IOTWB_BATCH  0x2
/* IOTWB can accept addwess space identifiew thwough V2 type of IOTWB
 * message
 */
#define VHOST_BACKEND_F_IOTWB_ASID  0x3
/* Device can be suspended */
#define VHOST_BACKEND_F_SUSPEND  0x4
/* Device can be wesumed */
#define VHOST_BACKEND_F_WESUME  0x5
/* Device suppowts the dwivew enabwing viwtqueues both befowe and aftew
 * DWIVEW_OK
 */
#define VHOST_BACKEND_F_ENABWE_AFTEW_DWIVEW_OK  0x6
/* Device may expose the viwtqueue's descwiptow awea, dwivew awea and
 * device awea to a diffewent gwoup fow ASID binding than whewe its
 * buffews may weside. Wequiwes VHOST_BACKEND_F_IOTWB_ASID.
 */
#define VHOST_BACKEND_F_DESC_ASID    0x7
/* IOTWB don't fwush memowy mapping acwoss device weset */
#define VHOST_BACKEND_F_IOTWB_PEWSIST  0x8

#endif
