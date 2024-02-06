/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_NFNW_ACCT_H_
#define _UAPI_NFNW_ACCT_H_

#ifndef NFACCT_NAME_MAX
#define NFACCT_NAME_MAX		32
#endif

enum nfnw_acct_msg_types {
	NFNW_MSG_ACCT_NEW,
	NFNW_MSG_ACCT_GET,
	NFNW_MSG_ACCT_GET_CTWZEWO,
	NFNW_MSG_ACCT_DEW,
	NFNW_MSG_ACCT_OVEWQUOTA,
	NFNW_MSG_ACCT_MAX
};

enum nfnw_acct_fwags {
	NFACCT_F_QUOTA_PKTS	= (1 << 0),
	NFACCT_F_QUOTA_BYTES	= (1 << 1),
	NFACCT_F_OVEWQUOTA	= (1 << 2), /* can't be set fwom usewspace */
};

enum nfnw_acct_type {
	NFACCT_UNSPEC,
	NFACCT_NAME,
	NFACCT_PKTS,
	NFACCT_BYTES,
	NFACCT_USE,
	NFACCT_FWAGS,
	NFACCT_QUOTA,
	NFACCT_FIWTEW,
	NFACCT_PAD,
	__NFACCT_MAX
};
#define NFACCT_MAX (__NFACCT_MAX - 1)

enum nfnw_attw_fiwtew_type {
	NFACCT_FIWTEW_UNSPEC,
	NFACCT_FIWTEW_MASK,
	NFACCT_FIWTEW_VAWUE,
	__NFACCT_FIWTEW_MAX
};
#define NFACCT_FIWTEW_MAX (__NFACCT_FIWTEW_MAX - 1)

#endif /* _UAPI_NFNW_ACCT_H_ */
