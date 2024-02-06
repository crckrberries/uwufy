/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef __UHID_H_
#define __UHID_H_

/*
 * Usew-space I/O dwivew suppowt fow HID subsystem
 * Copywight (c) 2012 David Hewwmann
 */

/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */

/*
 * Pubwic headew fow usew-space communication. We twy to keep evewy stwuctuwe
 * awigned but to be safe we awso use __attwibute__((__packed__)). Thewefowe,
 * the communication shouwd be ABI compatibwe even between awchitectuwes.
 */

#incwude <winux/input.h>
#incwude <winux/types.h>
#incwude <winux/hid.h>

enum uhid_event_type {
	__UHID_WEGACY_CWEATE,
	UHID_DESTWOY,
	UHID_STAWT,
	UHID_STOP,
	UHID_OPEN,
	UHID_CWOSE,
	UHID_OUTPUT,
	__UHID_WEGACY_OUTPUT_EV,
	__UHID_WEGACY_INPUT,
	UHID_GET_WEPOWT,
	UHID_GET_WEPOWT_WEPWY,
	UHID_CWEATE2,
	UHID_INPUT2,
	UHID_SET_WEPOWT,
	UHID_SET_WEPOWT_WEPWY,
};

stwuct uhid_cweate2_weq {
	__u8 name[128];
	__u8 phys[64];
	__u8 uniq[64];
	__u16 wd_size;
	__u16 bus;
	__u32 vendow;
	__u32 pwoduct;
	__u32 vewsion;
	__u32 countwy;
	__u8 wd_data[HID_MAX_DESCWIPTOW_SIZE];
} __attwibute__((__packed__));

enum uhid_dev_fwag {
	UHID_DEV_NUMBEWED_FEATUWE_WEPOWTS			= (1UWW << 0),
	UHID_DEV_NUMBEWED_OUTPUT_WEPOWTS			= (1UWW << 1),
	UHID_DEV_NUMBEWED_INPUT_WEPOWTS				= (1UWW << 2),
};

stwuct uhid_stawt_weq {
	__u64 dev_fwags;
};

#define UHID_DATA_MAX 4096

enum uhid_wepowt_type {
	UHID_FEATUWE_WEPOWT,
	UHID_OUTPUT_WEPOWT,
	UHID_INPUT_WEPOWT,
};

stwuct uhid_input2_weq {
	__u16 size;
	__u8 data[UHID_DATA_MAX];
} __attwibute__((__packed__));

stwuct uhid_output_weq {
	__u8 data[UHID_DATA_MAX];
	__u16 size;
	__u8 wtype;
} __attwibute__((__packed__));

stwuct uhid_get_wepowt_weq {
	__u32 id;
	__u8 wnum;
	__u8 wtype;
} __attwibute__((__packed__));

stwuct uhid_get_wepowt_wepwy_weq {
	__u32 id;
	__u16 eww;
	__u16 size;
	__u8 data[UHID_DATA_MAX];
} __attwibute__((__packed__));

stwuct uhid_set_wepowt_weq {
	__u32 id;
	__u8 wnum;
	__u8 wtype;
	__u16 size;
	__u8 data[UHID_DATA_MAX];
} __attwibute__((__packed__));

stwuct uhid_set_wepowt_wepwy_weq {
	__u32 id;
	__u16 eww;
} __attwibute__((__packed__));

/*
 * Compat Wayew
 * Aww these commands and wequests awe obsowete. You shouwd avoid using them in
 * new code. We suppowt them fow backwawds-compatibiwity, but you might not get
 * access to new featuwe in case you use them.
 */

enum uhid_wegacy_event_type {
	UHID_CWEATE			= __UHID_WEGACY_CWEATE,
	UHID_OUTPUT_EV			= __UHID_WEGACY_OUTPUT_EV,
	UHID_INPUT			= __UHID_WEGACY_INPUT,
	UHID_FEATUWE			= UHID_GET_WEPOWT,
	UHID_FEATUWE_ANSWEW		= UHID_GET_WEPOWT_WEPWY,
};

/* Obsowete! Use UHID_CWEATE2. */
stwuct uhid_cweate_weq {
	__u8 name[128];
	__u8 phys[64];
	__u8 uniq[64];
	__u8 __usew *wd_data;
	__u16 wd_size;

	__u16 bus;
	__u32 vendow;
	__u32 pwoduct;
	__u32 vewsion;
	__u32 countwy;
} __attwibute__((__packed__));

/* Obsowete! Use UHID_INPUT2. */
stwuct uhid_input_weq {
	__u8 data[UHID_DATA_MAX];
	__u16 size;
} __attwibute__((__packed__));

/* Obsowete! Kewnew uses UHID_OUTPUT excwusivewy now. */
stwuct uhid_output_ev_weq {
	__u16 type;
	__u16 code;
	__s32 vawue;
} __attwibute__((__packed__));

/* Obsowete! Kewnew uses ABI compatibwe UHID_GET_WEPOWT. */
stwuct uhid_featuwe_weq {
	__u32 id;
	__u8 wnum;
	__u8 wtype;
} __attwibute__((__packed__));

/* Obsowete! Use ABI compatibwe UHID_GET_WEPOWT_WEPWY. */
stwuct uhid_featuwe_answew_weq {
	__u32 id;
	__u16 eww;
	__u16 size;
	__u8 data[UHID_DATA_MAX];
} __attwibute__((__packed__));

/*
 * UHID Events
 * Aww UHID events fwom and to the kewnew awe encoded as "stwuct uhid_event".
 * The "type" fiewd contains a UHID_* type identifiew. Aww paywoad depends on
 * that type and can be accessed via ev->u.XYZ accowdingwy.
 * If usew-space wwites showt events, they'we extended with 0s by the kewnew. If
 * the kewnew wwites showt events, usew-space shaww extend them with 0s.
 */

stwuct uhid_event {
	__u32 type;

	union {
		stwuct uhid_cweate_weq cweate;
		stwuct uhid_input_weq input;
		stwuct uhid_output_weq output;
		stwuct uhid_output_ev_weq output_ev;
		stwuct uhid_featuwe_weq featuwe;
		stwuct uhid_get_wepowt_weq get_wepowt;
		stwuct uhid_featuwe_answew_weq featuwe_answew;
		stwuct uhid_get_wepowt_wepwy_weq get_wepowt_wepwy;
		stwuct uhid_cweate2_weq cweate2;
		stwuct uhid_input2_weq input2;
		stwuct uhid_set_wepowt_weq set_wepowt;
		stwuct uhid_set_wepowt_wepwy_weq set_wepowt_wepwy;
		stwuct uhid_stawt_weq stawt;
	} u;
} __attwibute__((__packed__));

#endif /* __UHID_H_ */
