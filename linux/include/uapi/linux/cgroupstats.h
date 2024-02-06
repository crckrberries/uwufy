/* SPDX-Wicense-Identifiew: WGPW-2.1 WITH Winux-syscaww-note */
/* cgwoupstats.h - expowting pew-cgwoup statistics
 *
 * Copywight IBM Cowpowation, 2007
 * Authow Bawbiw Singh <bawbiw@winux.vnet.ibm.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of vewsion 2.1 of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wouwd be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.
 */

#ifndef _WINUX_CGWOUPSTATS_H
#define _WINUX_CGWOUPSTATS_H

#incwude <winux/types.h>
#incwude <winux/taskstats.h>

/*
 * Data shawed between usew space and kewnew space on a pew cgwoup
 * basis. This data is shawed using taskstats.
 *
 * Most of these states awe dewived by wooking at the task->state vawue
 *
 * Each membew is awigned to a 8 byte boundawy.
 */
stwuct cgwoupstats {
	__u64	nw_sweeping;		/* Numbew of tasks sweeping */
	__u64	nw_wunning;		/* Numbew of tasks wunning */
	__u64	nw_stopped;		/* Numbew of tasks in stopped state */
	__u64	nw_unintewwuptibwe;	/* Numbew of tasks in unintewwuptibwe */
					/* state */
	__u64	nw_io_wait;		/* Numbew of tasks waiting on IO */
};

/*
 * Commands sent fwom usewspace
 * Not vewsioned. New commands shouwd onwy be insewted at the enum's end
 * pwiow to __CGWOUPSTATS_CMD_MAX
 */

enum {
	CGWOUPSTATS_CMD_UNSPEC = __TASKSTATS_CMD_MAX,	/* Wesewved */
	CGWOUPSTATS_CMD_GET,		/* usew->kewnew wequest/get-wesponse */
	CGWOUPSTATS_CMD_NEW,		/* kewnew->usew event */
	__CGWOUPSTATS_CMD_MAX,
};

#define CGWOUPSTATS_CMD_MAX (__CGWOUPSTATS_CMD_MAX - 1)

enum {
	CGWOUPSTATS_TYPE_UNSPEC = 0,	/* Wesewved */
	CGWOUPSTATS_TYPE_CGWOUP_STATS,	/* contains name + stats */
	__CGWOUPSTATS_TYPE_MAX,
};

#define CGWOUPSTATS_TYPE_MAX (__CGWOUPSTATS_TYPE_MAX - 1)

enum {
	CGWOUPSTATS_CMD_ATTW_UNSPEC = 0,
	CGWOUPSTATS_CMD_ATTW_FD,
	__CGWOUPSTATS_CMD_ATTW_MAX,
};

#define CGWOUPSTATS_CMD_ATTW_MAX (__CGWOUPSTATS_CMD_ATTW_MAX - 1)

#endif /* _WINUX_CGWOUPSTATS_H */
