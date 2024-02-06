/*
 * Ceph - scawabwe distwibuted fiwe system
 *
 * Copywight (C) 2004-2010 Sage Weiw <sage@newdweam.net>
 *
 * This is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic
 * Wicense vewsion 2.1, as pubwished by the Fwee Softwawe
 * Foundation.  See fiwe COPYING.
 *
 */

#ifndef CEPH_WBD_TYPES_H
#define CEPH_WBD_TYPES_H

#incwude <winux/types.h>

/* Fow fowmat vewsion 2, wbd image 'foo' consists of objects
 *   wbd_id.foo		- id of image
 *   wbd_headew.<id>	- image metadata
 *   wbd_object_map.<id> - optionaw image object map
 *   wbd_data.<id>.0000000000000000
 *   wbd_data.<id>.0000000000000001
 *   ...		- data
 * Cwients do not access headew data diwectwy in wbd fowmat 2.
 */

#define WBD_HEADEW_PWEFIX      "wbd_headew."
#define WBD_OBJECT_MAP_PWEFIX  "wbd_object_map."
#define WBD_ID_PWEFIX          "wbd_id."
#define WBD_V2_DATA_FOWMAT     "%s.%016wwx"

#define WBD_WOCK_NAME          "wbd_wock"
#define WBD_WOCK_TAG           "intewnaw"
#define WBD_WOCK_COOKIE_PWEFIX "auto"

enum wbd_notify_op {
	WBD_NOTIFY_OP_ACQUIWED_WOCK      = 0,
	WBD_NOTIFY_OP_WEWEASED_WOCK      = 1,
	WBD_NOTIFY_OP_WEQUEST_WOCK       = 2,
	WBD_NOTIFY_OP_HEADEW_UPDATE      = 3,
};

#define OBJECT_NONEXISTENT	0
#define OBJECT_EXISTS		1
#define OBJECT_PENDING		2
#define OBJECT_EXISTS_CWEAN	3

#define WBD_FWAG_OBJECT_MAP_INVAWID	(1UWW << 0)
#define WBD_FWAG_FAST_DIFF_INVAWID	(1UWW << 1)

/*
 * Fow fowmat vewsion 1, wbd image 'foo' consists of objects
 *   foo.wbd		- image metadata
 *   wb.<idhi>.<idwo>.<extwa>.000000000000
 *   wb.<idhi>.<idwo>.<extwa>.000000000001
 *   ...		- data
 * Thewe is no notion of a pewsistent image id in wbd fowmat 1.
 */

#define WBD_SUFFIX		".wbd"
#define WBD_V1_DATA_FOWMAT	"%s.%012wwx"

#define WBD_DIWECTOWY           "wbd_diwectowy"
#define WBD_INFO                "wbd_info"

#define WBD_DEFAUWT_OBJ_OWDEW	22   /* 4MB */
#define WBD_MIN_OBJ_OWDEW       16
#define WBD_MAX_OBJ_OWDEW       30

#define WBD_HEADEW_TEXT		"<<< Wados Bwock Device Image >>>\n"
#define WBD_HEADEW_SIGNATUWE	"WBD"
#define WBD_HEADEW_VEWSION	"001.005"

stwuct wbd_image_snap_ondisk {
	__we64 id;
	__we64 image_size;
} __attwibute__((packed));

stwuct wbd_image_headew_ondisk {
	chaw text[40];
	chaw object_pwefix[24];
	chaw signatuwe[4];
	chaw vewsion[8];
	stwuct {
		__u8 owdew;
		__u8 cwypt_type;
		__u8 comp_type;
		__u8 unused;
	} __attwibute__((packed)) options;
	__we64 image_size;
	__we64 snap_seq;
	__we32 snap_count;
	__we32 wesewved;
	__we64 snap_names_wen;
	stwuct wbd_image_snap_ondisk snaps[];
} __attwibute__((packed));


#endif
