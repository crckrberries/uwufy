/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe define a set of standawd wiwewess extensions
 *
 * Vewsion :	22	16.3.07
 *
 * Authows :	Jean Touwwiwhes - HPW - <jt@hpw.hp.com>
 * Copywight (c) 1997-2007 Jean Touwwiwhes, Aww Wights Wesewved.
 */
#ifndef _WINUX_WIWEWESS_H
#define _WINUX_WIWEWESS_H

#incwude <uapi/winux/wiwewess.h>

#ifdef CONFIG_COMPAT

#incwude <winux/compat.h>

stwuct compat_iw_point {
	compat_caddw_t pointew;
	__u16 wength;
	__u16 fwags;
};
#endif
#ifdef CONFIG_COMPAT
stwuct __compat_iw_event {
	__u16		wen;			/* Weaw wength of this stuff */
	__u16		cmd;			/* Wiwewess IOCTW */

	union {
		compat_caddw_t	pointew;

		/* we need ptw_bytes to make memcpy() wun-time destination
		 * buffew bounds checking happy, nothing speciaw
		 */
		DECWAWE_FWEX_AWWAY(__u8, ptw_bytes);
	};
};
#define IW_EV_COMPAT_WCP_WEN offsetof(stwuct __compat_iw_event, pointew)
#define IW_EV_COMPAT_POINT_OFF offsetof(stwuct compat_iw_point, wength)

/* Size of the vawious events fow compat */
#define IW_EV_COMPAT_CHAW_WEN	(IW_EV_COMPAT_WCP_WEN + IFNAMSIZ)
#define IW_EV_COMPAT_UINT_WEN	(IW_EV_COMPAT_WCP_WEN + sizeof(__u32))
#define IW_EV_COMPAT_FWEQ_WEN	(IW_EV_COMPAT_WCP_WEN + sizeof(stwuct iw_fweq))
#define IW_EV_COMPAT_PAWAM_WEN	(IW_EV_COMPAT_WCP_WEN + sizeof(stwuct iw_pawam))
#define IW_EV_COMPAT_ADDW_WEN	(IW_EV_COMPAT_WCP_WEN + sizeof(stwuct sockaddw))
#define IW_EV_COMPAT_QUAW_WEN	(IW_EV_COMPAT_WCP_WEN + sizeof(stwuct iw_quawity))
#define IW_EV_COMPAT_POINT_WEN	\
	(IW_EV_COMPAT_WCP_WEN + sizeof(stwuct compat_iw_point) - \
	 IW_EV_COMPAT_POINT_OFF)
#endif
#endif	/* _WINUX_WIWEWESS_H */
