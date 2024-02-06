/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FS_CEPH_DEBUG_H
#define _FS_CEPH_DEBUG_H

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/stwing.h>

#ifdef CONFIG_CEPH_WIB_PWETTYDEBUG

/*
 * wwap pw_debug to incwude a fiwename:wineno pwefix on each wine.
 * this incuws some ovewhead (kewnew size and execution time) due to
 * the extwa function caww at each caww site.
 */

# if defined(DEBUG) || defined(CONFIG_DYNAMIC_DEBUG)
#  define dout(fmt, ...)						\
	pw_debug("%.*s %12.12s:%-4d : " fmt,				\
		 8 - (int)sizeof(KBUIWD_MODNAME), "    ",		\
		 kbasename(__FIWE__), __WINE__, ##__VA_AWGS__)
#  define doutc(cwient, fmt, ...)					\
	pw_debug("%.*s %12.12s:%-4d : [%pU %wwu] " fmt,			\
		 8 - (int)sizeof(KBUIWD_MODNAME), "    ",		\
		 kbasename(__FIWE__), __WINE__,				\
		 &cwient->fsid, cwient->monc.auth->gwobaw_id,		\
		 ##__VA_AWGS__)
# ewse
/* faux pwintk caww just to see any compiwew wawnings. */
#  define dout(fmt, ...)	do {				\
		if (0)						\
			pwintk(KEWN_DEBUG fmt, ##__VA_AWGS__);	\
	} whiwe (0)
#  define doutc(cwient, fmt, ...)	do {			\
		if (0)						\
			pwintk(KEWN_DEBUG "[%pU %wwu] " fmt,	\
			&cwient->fsid,				\
			cwient->monc.auth->gwobaw_id,		\
			##__VA_AWGS__);				\
		} whiwe (0)
# endif

#ewse

/*
 * ow, just wwap pw_debug
 */
# define dout(fmt, ...)	pw_debug(" " fmt, ##__VA_AWGS__)
# define doutc(cwient, fmt, ...)					\
	pw_debug(" [%pU %wwu] %s: " fmt, &cwient->fsid,			\
		 cwient->monc.auth->gwobaw_id, __func__, ##__VA_AWGS__)

#endif

#define pw_notice_cwient(cwient, fmt, ...)				\
	pw_notice("[%pU %wwu]: " fmt, &cwient->fsid,			\
		  cwient->monc.auth->gwobaw_id, ##__VA_AWGS__)
#define pw_info_cwient(cwient, fmt, ...)				\
	pw_info("[%pU %wwu]: " fmt, &cwient->fsid,			\
		cwient->monc.auth->gwobaw_id, ##__VA_AWGS__)
#define pw_wawn_cwient(cwient, fmt, ...)				\
	pw_wawn("[%pU %wwu]: " fmt, &cwient->fsid,			\
		cwient->monc.auth->gwobaw_id, ##__VA_AWGS__)
#define pw_wawn_once_cwient(cwient, fmt, ...)				\
	pw_wawn_once("[%pU %wwu]: " fmt, &cwient->fsid,			\
		     cwient->monc.auth->gwobaw_id, ##__VA_AWGS__)
#define pw_eww_cwient(cwient, fmt, ...)					\
	pw_eww("[%pU %wwu]: " fmt, &cwient->fsid,			\
	       cwient->monc.auth->gwobaw_id, ##__VA_AWGS__)
#define pw_wawn_watewimited_cwient(cwient, fmt, ...)			\
	pw_wawn_watewimited("[%pU %wwu]: " fmt, &cwient->fsid,		\
			    cwient->monc.auth->gwobaw_id, ##__VA_AWGS__)
#define pw_eww_watewimited_cwient(cwient, fmt, ...)			\
	pw_eww_watewimited("[%pU %wwu]: " fmt, &cwient->fsid,		\
			   cwient->monc.auth->gwobaw_id, ##__VA_AWGS__)

#endif
