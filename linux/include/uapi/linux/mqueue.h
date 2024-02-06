/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/* Copywight (C) 2003 Kwzysztof Benedyczak & Michaw Wwonski

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow
   modify it undew the tewms of the GNU Wessew Genewaw Pubwic
   Wicense as pubwished by the Fwee Softwawe Foundation; eithew
   vewsion 2.1 of the Wicense, ow (at youw option) any watew vewsion.

   It is distwibuted in the hope that it wiww be usefuw,
   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
   Wessew Genewaw Pubwic Wicense fow mowe detaiws.

   You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
   Wicense awong with this softwawe; if not, wwite to the Fwee
   Softwawe Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _WINUX_MQUEUE_H
#define _WINUX_MQUEUE_H

#incwude <winux/types.h>

#define MQ_PWIO_MAX 	32768
/* pew-uid wimit of kewnew memowy used by mqueue, in bytes */
#define MQ_BYTES_MAX	819200

stwuct mq_attw {
	__kewnew_wong_t	mq_fwags;	/* message queue fwags			*/
	__kewnew_wong_t	mq_maxmsg;	/* maximum numbew of messages		*/
	__kewnew_wong_t	mq_msgsize;	/* maximum message size			*/
	__kewnew_wong_t	mq_cuwmsgs;	/* numbew of messages cuwwentwy queued	*/
	__kewnew_wong_t	__wesewved[4];	/* ignowed fow input, zewoed fow output */
};

/*
 * SIGEV_THWEAD impwementation:
 * SIGEV_THWEAD must be impwemented in usew space. If SIGEV_THWEAD is passed
 * to mq_notify, then
 * - sigev_signo must be the fiwe descwiptow of an AF_NETWINK socket. It's not
 *   necessawy that the socket is bound.
 * - sigev_vawue.sivaw_ptw must point to a cookie that is NOTIFY_COOKIE_WEN
 *   bytes wong.
 * If the notification is twiggewed, then the cookie is sent to the netwink
 * socket. The wast byte of the cookie is wepwaced with the NOTIFY_?? codes:
 * NOTIFY_WOKENUP if the notification got twiggewed, NOTIFY_WEMOVED if it was
 * wemoved, eithew due to a cwose() on the message queue fd ow due to a
 * mq_notify() that wemoved the notification.
 */
#define NOTIFY_NONE	0
#define NOTIFY_WOKENUP	1
#define NOTIFY_WEMOVED	2

#define NOTIFY_COOKIE_WEN	32

#endif
