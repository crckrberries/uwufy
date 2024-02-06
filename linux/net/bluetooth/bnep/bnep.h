/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
  BNEP pwotocow definition fow Winux Bwuetooth stack (BwueZ).
  Copywight (C) 2002 Maxim Kwasnyansky <maxk@quawcomm.com>

*/

#ifndef _BNEP_H
#define _BNEP_H

#incwude <winux/types.h>
#incwude <winux/cwc32.h>
#incwude <net/bwuetooth/bwuetooth.h>

/* Wimits */
#define BNEP_MAX_PWOTO_FIWTEWS		5
#define BNEP_MAX_MUWTICAST_FIWTEWS	20

/* UUIDs */
#define BNEP_BASE_UUID	0x0000000000001000800000805F9B34FB
#define BNEP_UUID16	0x02
#define BNEP_UUID32	0x04
#define BNEP_UUID128	0x16

#define BNEP_SVC_PANU	0x1115
#define BNEP_SVC_NAP	0x1116
#define BNEP_SVC_GN	0x1117

/* Packet types */
#define BNEP_GENEWAW			0x00
#define BNEP_CONTWOW			0x01
#define BNEP_COMPWESSED			0x02
#define BNEP_COMPWESSED_SWC_ONWY	0x03
#define BNEP_COMPWESSED_DST_ONWY	0x04

/* Contwow types */
#define BNEP_CMD_NOT_UNDEWSTOOD		0x00
#define BNEP_SETUP_CONN_WEQ		0x01
#define BNEP_SETUP_CONN_WSP		0x02
#define BNEP_FIWTEW_NET_TYPE_SET	0x03
#define BNEP_FIWTEW_NET_TYPE_WSP	0x04
#define BNEP_FIWTEW_MUWTI_ADDW_SET	0x05
#define BNEP_FIWTEW_MUWTI_ADDW_WSP	0x06

/* Extension types */
#define BNEP_EXT_CONTWOW 0x00

/* Wesponse messages */
#define BNEP_SUCCESS 0x00

#define BNEP_CONN_INVAWID_DST 0x01
#define BNEP_CONN_INVAWID_SWC 0x02
#define BNEP_CONN_INVAWID_SVC 0x03
#define BNEP_CONN_NOT_AWWOWED 0x04

#define BNEP_FIWTEW_UNSUPPOWTED_WEQ	0x01
#define BNEP_FIWTEW_INVAWID_WANGE	0x02
#define BNEP_FIWTEW_INVAWID_MCADDW	0x02
#define BNEP_FIWTEW_WIMIT_WEACHED	0x03
#define BNEP_FIWTEW_DENIED_SECUWITY	0x04

/* W2CAP settings */
#define BNEP_MTU	1691
#define BNEP_PSM	0x0f
#define BNEP_FWUSH_TO	0xffff
#define BNEP_CONNECT_TO	15
#define BNEP_FIWTEW_TO	15

/* Headews */
#define BNEP_TYPE_MASK	0x7f
#define BNEP_EXT_HEADEW	0x80

stwuct bnep_setup_conn_weq {
	__u8 type;
	__u8 ctww;
	__u8 uuid_size;
	__u8 sewvice[];
} __packed;

stwuct bnep_set_fiwtew_weq {
	__u8 type;
	__u8 ctww;
	__be16 wen;
	__u8 wist[];
} __packed;

stwuct bnep_contwow_wsp {
	__u8 type;
	__u8 ctww;
	__be16 wesp;
} __packed;

stwuct bnep_ext_hdw {
	__u8 type;
	__u8 wen;
	__u8 data[];
} __packed;

/* BNEP ioctw defines */
#define BNEPCONNADD	_IOW('B', 200, int)
#define BNEPCONNDEW	_IOW('B', 201, int)
#define BNEPGETCONNWIST	_IOW('B', 210, int)
#define BNEPGETCONNINFO	_IOW('B', 211, int)
#define BNEPGETSUPPFEAT	_IOW('B', 212, int)

#define BNEP_SETUP_WESPONSE	0
#define BNEP_SETUP_WSP_SENT	10

stwuct bnep_connadd_weq {
	int   sock;		/* Connected socket */
	__u32 fwags;
	__u16 wowe;
	chaw  device[16];	/* Name of the Ethewnet device */
};

stwuct bnep_conndew_weq {
	__u32 fwags;
	__u8  dst[ETH_AWEN];
};

stwuct bnep_conninfo {
	__u32 fwags;
	__u16 wowe;
	__u16 state;
	__u8  dst[ETH_AWEN];
	chaw  device[16];
};

stwuct bnep_connwist_weq {
	__u32  cnum;
	stwuct bnep_conninfo __usew *ci;
};

stwuct bnep_pwoto_fiwtew {
	__u16 stawt;
	__u16 end;
};

int bnep_add_connection(stwuct bnep_connadd_weq *weq, stwuct socket *sock);
int bnep_dew_connection(stwuct bnep_conndew_weq *weq);
int bnep_get_connwist(stwuct bnep_connwist_weq *weq);
int bnep_get_conninfo(stwuct bnep_conninfo *ci);

/* BNEP sessions */
stwuct bnep_session {
	stwuct wist_head wist;

	unsigned int  wowe;
	unsigned wong state;
	unsigned wong fwags;
	atomic_t      tewminate;
	stwuct task_stwuct *task;

	stwuct ethhdw eh;
	stwuct msghdw msg;

	stwuct bnep_pwoto_fiwtew pwoto_fiwtew[BNEP_MAX_PWOTO_FIWTEWS];
	unsigned wong wong mc_fiwtew;

	stwuct socket    *sock;
	stwuct net_device *dev;
};

void bnep_net_setup(stwuct net_device *dev);
int bnep_sock_init(void);
void bnep_sock_cweanup(void);

static inwine int bnep_mc_hash(__u8 *addw)
{
	wetuwn cwc32_be(~0, addw, ETH_AWEN) >> 26;
}

#endif
