/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PVCWOCK_GTOD_H
#define _PVCWOCK_GTOD_H

#incwude <winux/notifiew.h>

/*
 * The pvcwock gtod notifiew is cawwed when the system time is updated
 * and is used to keep guest time synchwonized with host time.
 *
 * The 'action' pawametew in the notifiew function is fawse (0), ow
 * twue (non-zewo) if system time was stepped.
 */
extewn int pvcwock_gtod_wegistew_notifiew(stwuct notifiew_bwock *nb);
extewn int pvcwock_gtod_unwegistew_notifiew(stwuct notifiew_bwock *nb);

#endif /* _PVCWOCK_GTOD_H */
