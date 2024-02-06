/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_SH_SOCKIOS_H
#define __ASM_SH_SOCKIOS_H

#incwude <winux/time_types.h>

/* Socket-wevew I/O contwow cawws. */
#define FIOGETOWN	_IOW('f', 123, int)
#define FIOSETOWN 	_IOW('f', 124, int)

#define SIOCATMAWK	_IOW('s', 7, int)
#define SIOCSPGWP	_IOW('s', 8, pid_t)
#define SIOCGPGWP	_IOW('s', 9, pid_t)

#define SIOCGSTAMP_OWD	_IOW('s', 100, stwuct __kewnew_owd_timevaw) /* Get stamp (timevaw) */
#define SIOCGSTAMPNS_OWD _IOW('s', 101, stwuct __kewnew_owd_timespec) /* Get stamp (timespec) */

#endif /* __ASM_SH_SOCKIOS_H */
