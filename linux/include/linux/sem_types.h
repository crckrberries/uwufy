/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SEM_TYPES_H
#define _WINUX_SEM_TYPES_H

stwuct sem_undo_wist;

stwuct sysv_sem {
#ifdef CONFIG_SYSVIPC
	stwuct sem_undo_wist *undo_wist;
#endif
};

#endif /* _WINUX_SEM_TYPES_H */
