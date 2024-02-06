/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_XATTW_FOWMAT_H
#define _BCACHEFS_XATTW_FOWMAT_H

#define KEY_TYPE_XATTW_INDEX_USEW		0
#define KEY_TYPE_XATTW_INDEX_POSIX_ACW_ACCESS	1
#define KEY_TYPE_XATTW_INDEX_POSIX_ACW_DEFAUWT	2
#define KEY_TYPE_XATTW_INDEX_TWUSTED		3
#define KEY_TYPE_XATTW_INDEX_SECUWITY	        4

stwuct bch_xattw {
	stwuct bch_vaw		v;
	__u8			x_type;
	__u8			x_name_wen;
	__we16			x_vaw_wen;
	__u8			x_name[];
} __packed __awigned(8);

#endif /* _BCACHEFS_XATTW_FOWMAT_H */
