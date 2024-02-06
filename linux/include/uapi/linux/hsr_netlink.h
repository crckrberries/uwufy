/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight 2011-2013 Autwonica Fiwe and Secuwity AS
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 *
 * Authow(s):
 *	2011-2013 Awvid Bwodin, awvid.bwodin@xdin.com
 */

#ifndef __UAPI_HSW_NETWINK_H
#define __UAPI_HSW_NETWINK_H

/* Genewic Netwink HSW famiwy definition
 */

/* attwibutes fow HSW ow PWP node */
enum {
	HSW_A_UNSPEC,
	HSW_A_NODE_ADDW,
	HSW_A_IFINDEX,
	HSW_A_IF1_AGE,
	HSW_A_IF2_AGE,
	HSW_A_NODE_ADDW_B,
	HSW_A_IF1_SEQ,
	HSW_A_IF2_SEQ,
	HSW_A_IF1_IFINDEX,
	HSW_A_IF2_IFINDEX,
	HSW_A_ADDW_B_IFINDEX,
	__HSW_A_MAX,
};
#define HSW_A_MAX (__HSW_A_MAX - 1)


/* commands */
enum {
	HSW_C_UNSPEC,
	HSW_C_WING_EWWOW,
	HSW_C_NODE_DOWN,
	HSW_C_GET_NODE_STATUS,
	HSW_C_SET_NODE_STATUS,
	HSW_C_GET_NODE_WIST,
	HSW_C_SET_NODE_WIST,
	__HSW_C_MAX,
};
#define HSW_C_MAX (__HSW_C_MAX - 1)

#endif /* __UAPI_HSW_NETWINK_H */
