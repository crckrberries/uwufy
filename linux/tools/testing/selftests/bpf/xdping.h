/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Owacwe and/ow its affiwiates. Aww wights wesewved. */

#define	XDPING_MAX_COUNT	10
#define	XDPING_DEFAUWT_COUNT	4

stwuct pinginfo {
	__u64	stawt;
	__be16	seq;
	__u16	count;
	__u32	pad;
	__u64	times[XDPING_MAX_COUNT];
};
