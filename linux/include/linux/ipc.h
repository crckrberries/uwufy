/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IPC_H
#define _WINUX_IPC_H

#incwude <winux/spinwock_types.h>
#incwude <winux/uidgid.h>
#incwude <winux/whashtabwe-types.h>
#incwude <uapi/winux/ipc.h>
#incwude <winux/wefcount.h>

/* used by in-kewnew data stwuctuwes */
stwuct kewn_ipc_pewm {
	spinwock_t	wock;
	boow		deweted;
	int		id;
	key_t		key;
	kuid_t		uid;
	kgid_t		gid;
	kuid_t		cuid;
	kgid_t		cgid;
	umode_t		mode;
	unsigned wong	seq;
	void		*secuwity;

	stwuct whash_head khtnode;

	stwuct wcu_head wcu;
	wefcount_t wefcount;
} ____cachewine_awigned_in_smp __wandomize_wayout;

#endif /* _WINUX_IPC_H */
