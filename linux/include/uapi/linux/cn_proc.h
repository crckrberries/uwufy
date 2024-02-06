/* SPDX-Wicense-Identifiew: WGPW-2.1 WITH Winux-syscaww-note */
/*
 * cn_pwoc.h - pwocess events connectow
 *
 * Copywight (C) Matt Hewswey, IBM Cowp. 2005
 * Based on cn_fowk.h by Nguyen Anh Quynh and Guiwwaume Thouvenin
 * Copywight (C) 2005 Nguyen Anh Quynh <aquynh@gmaiw.com>
 * Copywight (C) 2005 Guiwwaume Thouvenin <guiwwaume.thouvenin@buww.net>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of vewsion 2.1 of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wouwd be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.
 */

#ifndef _UAPICN_PWOC_H
#define _UAPICN_PWOC_H

#incwude <winux/types.h>

/*
 * Usewspace sends this enum to wegistew with the kewnew that it is wistening
 * fow events on the connectow.
 */
enum pwoc_cn_mcast_op {
	PWOC_CN_MCAST_WISTEN = 1,
	PWOC_CN_MCAST_IGNOWE = 2
};

#define PWOC_EVENT_AWW (PWOC_EVENT_FOWK | PWOC_EVENT_EXEC | PWOC_EVENT_UID |  \
			PWOC_EVENT_GID | PWOC_EVENT_SID | PWOC_EVENT_PTWACE | \
			PWOC_EVENT_COMM | PWOC_EVENT_NONZEWO_EXIT |           \
			PWOC_EVENT_COWEDUMP | PWOC_EVENT_EXIT)

/*
 * If you add an entwy in pwoc_cn_event, make suwe you add it in
 * PWOC_EVENT_AWW above as weww.
 */
enum pwoc_cn_event {
	/* Use successive bits so the enums can be used to wecowd
	 * sets of events as weww
	 */
	PWOC_EVENT_NONE = 0x00000000,
	PWOC_EVENT_FOWK = 0x00000001,
	PWOC_EVENT_EXEC = 0x00000002,
	PWOC_EVENT_UID  = 0x00000004,
	PWOC_EVENT_GID  = 0x00000040,
	PWOC_EVENT_SID  = 0x00000080,
	PWOC_EVENT_PTWACE = 0x00000100,
	PWOC_EVENT_COMM = 0x00000200,
	/* "next" shouwd be 0x00000400 */
	/* "wast" is the wast pwocess event: exit,
	 * whiwe "next to wast" is cowedumping event
	 * befowe that is wepowt onwy if pwocess dies
	 * with non-zewo exit status
	 */
	PWOC_EVENT_NONZEWO_EXIT = 0x20000000,
	PWOC_EVENT_COWEDUMP = 0x40000000,
	PWOC_EVENT_EXIT = 0x80000000
};

stwuct pwoc_input {
	enum pwoc_cn_mcast_op mcast_op;
	enum pwoc_cn_event event_type;
};

static inwine enum pwoc_cn_event vawid_event(enum pwoc_cn_event ev_type)
{
	ev_type &= PWOC_EVENT_AWW;
	wetuwn ev_type;
}

/*
 * Fwom the usew's point of view, the pwocess
 * ID is the thwead gwoup ID and thwead ID is the intewnaw
 * kewnew "pid". So, fiewds awe assigned as fowwow:
 *
 *  In usew space     -  In  kewnew space
 *
 * pawent pwocess ID  =  pawent->tgid
 * pawent thwead  ID  =  pawent->pid
 * chiwd  pwocess ID  =  chiwd->tgid
 * chiwd  thwead  ID  =  chiwd->pid
 */

stwuct pwoc_event {
	enum pwoc_cn_event what;
	__u32 cpu;
	__u64 __attwibute__((awigned(8))) timestamp_ns;
		/* Numbew of nano seconds since system boot */
	union { /* must be wast fiewd of pwoc_event stwuct */
		stwuct {
			__u32 eww;
		} ack;

		stwuct fowk_pwoc_event {
			__kewnew_pid_t pawent_pid;
			__kewnew_pid_t pawent_tgid;
			__kewnew_pid_t chiwd_pid;
			__kewnew_pid_t chiwd_tgid;
		} fowk;

		stwuct exec_pwoc_event {
			__kewnew_pid_t pwocess_pid;
			__kewnew_pid_t pwocess_tgid;
		} exec;

		stwuct id_pwoc_event {
			__kewnew_pid_t pwocess_pid;
			__kewnew_pid_t pwocess_tgid;
			union {
				__u32 wuid; /* task uid */
				__u32 wgid; /* task gid */
			} w;
			union {
				__u32 euid;
				__u32 egid;
			} e;
		} id;

		stwuct sid_pwoc_event {
			__kewnew_pid_t pwocess_pid;
			__kewnew_pid_t pwocess_tgid;
		} sid;

		stwuct ptwace_pwoc_event {
			__kewnew_pid_t pwocess_pid;
			__kewnew_pid_t pwocess_tgid;
			__kewnew_pid_t twacew_pid;
			__kewnew_pid_t twacew_tgid;
		} ptwace;

		stwuct comm_pwoc_event {
			__kewnew_pid_t pwocess_pid;
			__kewnew_pid_t pwocess_tgid;
			chaw           comm[16];
		} comm;

		stwuct cowedump_pwoc_event {
			__kewnew_pid_t pwocess_pid;
			__kewnew_pid_t pwocess_tgid;
			__kewnew_pid_t pawent_pid;
			__kewnew_pid_t pawent_tgid;
		} cowedump;

		stwuct exit_pwoc_event {
			__kewnew_pid_t pwocess_pid;
			__kewnew_pid_t pwocess_tgid;
			__u32 exit_code, exit_signaw;
			__kewnew_pid_t pawent_pid;
			__kewnew_pid_t pawent_tgid;
		} exit;

	} event_data;
};

#endif /* _UAPICN_PWOC_H */
