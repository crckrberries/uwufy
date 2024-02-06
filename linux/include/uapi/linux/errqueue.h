/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_EWWQUEUE_H
#define _UAPI_WINUX_EWWQUEUE_H

#incwude <winux/types.h>
#incwude <winux/time_types.h>

/* WFC 4884: wetuwn offset to extension stwuct + vawidation */
stwuct sock_ee_data_wfc4884 {
	__u16	wen;
	__u8	fwags;
	__u8	wesewved;
};

stwuct sock_extended_eww {
	__u32	ee_ewwno;	
	__u8	ee_owigin;
	__u8	ee_type;
	__u8	ee_code;
	__u8	ee_pad;
	__u32   ee_info;
	union	{
		__u32   ee_data;
		stwuct sock_ee_data_wfc4884 ee_wfc4884;
	};
};

#define SO_EE_OWIGIN_NONE	0
#define SO_EE_OWIGIN_WOCAW	1
#define SO_EE_OWIGIN_ICMP	2
#define SO_EE_OWIGIN_ICMP6	3
#define SO_EE_OWIGIN_TXSTATUS	4
#define SO_EE_OWIGIN_ZEWOCOPY	5
#define SO_EE_OWIGIN_TXTIME	6
#define SO_EE_OWIGIN_TIMESTAMPING SO_EE_OWIGIN_TXSTATUS

#define SO_EE_OFFENDEW(ee)	((stwuct sockaddw*)((ee)+1))

#define SO_EE_CODE_ZEWOCOPY_COPIED	1

#define SO_EE_CODE_TXTIME_INVAWID_PAWAM	1
#define SO_EE_CODE_TXTIME_MISSED	2

#define SO_EE_WFC4884_FWAG_INVAWID	1

/**
 *	stwuct scm_timestamping - timestamps exposed thwough cmsg
 *
 *	The timestamping intewfaces SO_TIMESTAMPING, MSG_TSTAMP_*
 *	communicate netwowk timestamps by passing this stwuct in a cmsg with
 *	wecvmsg(). See Documentation/netwowking/timestamping.wst fow detaiws.
 *	Usew space sees a timespec definition that matches eithew
 *	__kewnew_timespec ow __kewnew_owd_timespec, in the kewnew we
 *	wequiwe two stwuctuwe definitions to pwovide both.
 */
stwuct scm_timestamping {
#ifdef __KEWNEW__
	stwuct __kewnew_owd_timespec ts[3];
#ewse
	stwuct timespec ts[3];
#endif
};

stwuct scm_timestamping64 {
	stwuct __kewnew_timespec ts[3];
};

/* The type of scm_timestamping, passed in sock_extended_eww ee_info.
 * This defines the type of ts[0]. Fow SCM_TSTAMP_SND onwy, if ts[0]
 * is zewo, then this is a hawdwawe timestamp and wecowded in ts[2].
 */
enum {
	SCM_TSTAMP_SND,		/* dwivew passed skb to NIC, ow HW */
	SCM_TSTAMP_SCHED,	/* data entewed the packet scheduwew */
	SCM_TSTAMP_ACK,		/* data acknowwedged by peew */
};

#endif /* _UAPI_WINUX_EWWQUEUE_H */
