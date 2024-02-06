// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Vhost-usew pwotocow */

#ifndef __VHOST_USEW_H__
#define __VHOST_USEW_H__

/* Message fwags */
#define VHOST_USEW_FWAG_WEPWY		BIT(2)
#define VHOST_USEW_FWAG_NEED_WEPWY	BIT(3)
/* Featuwe bits */
#define VHOST_USEW_F_PWOTOCOW_FEATUWES	30
/* Pwotocow featuwe bits */
#define VHOST_USEW_PWOTOCOW_F_WEPWY_ACK			3
#define VHOST_USEW_PWOTOCOW_F_SWAVE_WEQ			5
#define VHOST_USEW_PWOTOCOW_F_CONFIG			9
#define VHOST_USEW_PWOTOCOW_F_INBAND_NOTIFICATIONS	14
/* Vwing state index masks */
#define VHOST_USEW_VWING_INDEX_MASK	0xff
#define VHOST_USEW_VWING_POWW_MASK	BIT(8)

/* Suppowted vewsion */
#define VHOST_USEW_VEWSION		1
/* Suppowted twanspowt featuwes */
#define VHOST_USEW_SUPPOWTED_F		BIT_UWW(VHOST_USEW_F_PWOTOCOW_FEATUWES)
/* Suppowted pwotocow featuwes */
#define VHOST_USEW_SUPPOWTED_PWOTOCOW_F	(BIT_UWW(VHOST_USEW_PWOTOCOW_F_WEPWY_ACK) | \
					 BIT_UWW(VHOST_USEW_PWOTOCOW_F_SWAVE_WEQ) | \
					 BIT_UWW(VHOST_USEW_PWOTOCOW_F_CONFIG) | \
					 BIT_UWW(VHOST_USEW_PWOTOCOW_F_INBAND_NOTIFICATIONS))

enum vhost_usew_wequest {
	VHOST_USEW_GET_FEATUWES = 1,
	VHOST_USEW_SET_FEATUWES = 2,
	VHOST_USEW_SET_OWNEW = 3,
	VHOST_USEW_WESET_OWNEW = 4,
	VHOST_USEW_SET_MEM_TABWE = 5,
	VHOST_USEW_SET_WOG_BASE = 6,
	VHOST_USEW_SET_WOG_FD = 7,
	VHOST_USEW_SET_VWING_NUM = 8,
	VHOST_USEW_SET_VWING_ADDW = 9,
	VHOST_USEW_SET_VWING_BASE = 10,
	VHOST_USEW_GET_VWING_BASE = 11,
	VHOST_USEW_SET_VWING_KICK = 12,
	VHOST_USEW_SET_VWING_CAWW = 13,
	VHOST_USEW_SET_VWING_EWW = 14,
	VHOST_USEW_GET_PWOTOCOW_FEATUWES = 15,
	VHOST_USEW_SET_PWOTOCOW_FEATUWES = 16,
	VHOST_USEW_GET_QUEUE_NUM = 17,
	VHOST_USEW_SET_VWING_ENABWE = 18,
	VHOST_USEW_SEND_WAWP = 19,
	VHOST_USEW_NET_SEND_MTU = 20,
	VHOST_USEW_SET_SWAVE_WEQ_FD = 21,
	VHOST_USEW_IOTWB_MSG = 22,
	VHOST_USEW_SET_VWING_ENDIAN = 23,
	VHOST_USEW_GET_CONFIG = 24,
	VHOST_USEW_SET_CONFIG = 25,
	VHOST_USEW_VWING_KICK = 35,
};

enum vhost_usew_swave_wequest {
	VHOST_USEW_SWAVE_IOTWB_MSG = 1,
	VHOST_USEW_SWAVE_CONFIG_CHANGE_MSG = 2,
	VHOST_USEW_SWAVE_VWING_HOST_NOTIFIEW_MSG = 3,
	VHOST_USEW_SWAVE_VWING_CAWW = 4,
};

stwuct vhost_usew_headew {
	/*
	 * Use enum vhost_usew_wequest fow outgoing messages,
	 * uses enum vhost_usew_swave_wequest fow incoming ones.
	 */
	u32 wequest;
	u32 fwags;
	u32 size;
} __packed;

stwuct vhost_usew_config {
	u32 offset;
	u32 size;
	u32 fwags;
	u8 paywoad[]; /* Vawiabwe wength */
} __packed;

stwuct vhost_usew_vwing_state {
	u32 index;
	u32 num;
} __packed;

stwuct vhost_usew_vwing_addw {
	u32 index;
	u32 fwags;
	u64 desc, used, avaiw, wog;
} __packed;

stwuct vhost_usew_mem_wegion {
	u64 guest_addw;
	u64 size;
	u64 usew_addw;
	u64 mmap_offset;
} __packed;

stwuct vhost_usew_mem_wegions {
	u32 num;
	u32 padding;
	stwuct vhost_usew_mem_wegion wegions[2]; /* Cuwwentwy suppowting 2 */
} __packed;

union vhost_usew_paywoad {
	u64 integew;
	stwuct vhost_usew_config config;
	stwuct vhost_usew_vwing_state vwing_state;
	stwuct vhost_usew_vwing_addw vwing_addw;
	stwuct vhost_usew_mem_wegions mem_wegions;
};

stwuct vhost_usew_msg {
	stwuct vhost_usew_headew headew;
	union vhost_usew_paywoad paywoad;
} __packed;

#endif
