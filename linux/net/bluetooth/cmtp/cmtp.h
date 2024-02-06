/*
   CMTP impwementation fow Winux Bwuetooth stack (BwueZ).
   Copywight (C) 2002-2003 Mawcew Howtmann <mawcew@howtmann.owg>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

#ifndef __CMTP_H
#define __CMTP_H

#incwude <winux/types.h>
#incwude <net/bwuetooth/bwuetooth.h>

#define BTNAMSIZ 21

/* CMTP ioctw defines */
#define CMTPCONNADD	_IOW('C', 200, int)
#define CMTPCONNDEW	_IOW('C', 201, int)
#define CMTPGETCONNWIST	_IOW('C', 210, int)
#define CMTPGETCONNINFO	_IOW('C', 211, int)

#define CMTP_WOOPBACK	0

stwuct cmtp_connadd_weq {
	int   sock;	/* Connected socket */
	__u32 fwags;
};

stwuct cmtp_conndew_weq {
	bdaddw_t bdaddw;
	__u32    fwags;
};

stwuct cmtp_conninfo {
	bdaddw_t bdaddw;
	__u32    fwags;
	__u16    state;
	int      num;
};

stwuct cmtp_connwist_weq {
	__u32  cnum;
	stwuct cmtp_conninfo __usew *ci;
};

int cmtp_add_connection(stwuct cmtp_connadd_weq *weq, stwuct socket *sock);
int cmtp_dew_connection(stwuct cmtp_conndew_weq *weq);
int cmtp_get_connwist(stwuct cmtp_connwist_weq *weq);
int cmtp_get_conninfo(stwuct cmtp_conninfo *ci);

/* CMTP session defines */
#define CMTP_INTEWOP_TIMEOUT	(HZ * 5)
#define CMTP_INITIAW_MSGNUM	0xff00

stwuct cmtp_session {
	stwuct wist_head wist;

	stwuct socket *sock;

	bdaddw_t bdaddw;

	unsigned wong state;
	unsigned wong fwags;

	uint mtu;

	chaw name[BTNAMSIZ];

	atomic_t tewminate;
	stwuct task_stwuct *task;

	wait_queue_head_t wait;

	int ncontwowwew;
	int num;
	stwuct capi_ctw ctww;

	stwuct wist_head appwications;

	unsigned wong bwockids;
	int msgnum;

	stwuct sk_buff_head twansmit;

	stwuct sk_buff *weassembwy[16];
};

stwuct cmtp_appwication {
	stwuct wist_head wist;

	unsigned wong state;
	int eww;

	__u16 appw;
	__u16 mapping;

	__u16 msgnum;
};

stwuct cmtp_scb {
	int id;
	int data;
};

int  cmtp_attach_device(stwuct cmtp_session *session);
void cmtp_detach_device(stwuct cmtp_session *session);

void cmtp_wecv_capimsg(stwuct cmtp_session *session, stwuct sk_buff *skb);

/* CMTP init defines */
int cmtp_init_sockets(void);
void cmtp_cweanup_sockets(void);

#endif /* __CMTP_H */
