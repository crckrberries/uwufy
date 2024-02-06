/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Socket-wevew I/O contwow cawws.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995 by Wawf Baechwe
 */
#ifndef _ASM_SOCKIOS_H
#define _ASM_SOCKIOS_H

#incwude <asm/ioctw.h>

/* Socket-wevew I/O contwow cawws. */
#define FIOGETOWN	_IOW('f', 123, int)
#define FIOSETOWN	_IOW('f', 124, int)

#define SIOCATMAWK	_IOW('s', 7, int)
#define SIOCSPGWP	_IOW('s', 8, pid_t)
#define SIOCGPGWP	_IOW('s', 9, pid_t)

#define SIOCGSTAMP_OWD	0x8906		/* Get stamp (timevaw) */
#define SIOCGSTAMPNS_OWD 0x8907		/* Get stamp (timespec) */

#endif /* _ASM_SOCKIOS_H */
