/*
   HIDP impwementation fow Winux Bwuetooth stack (BwueZ).
   Copywight (C) 2003-2004 Mawcew Howtmann <mawcew@howtmann.owg>

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

#ifndef __HIDP_H
#define __HIDP_H

#incwude <winux/types.h>
#incwude <winux/hid.h>
#incwude <winux/kwef.h>
#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/w2cap.h>

/* HIDP headew masks */
#define HIDP_HEADEW_TWANS_MASK			0xf0
#define HIDP_HEADEW_PAWAM_MASK			0x0f

/* HIDP twansaction types */
#define HIDP_TWANS_HANDSHAKE			0x00
#define HIDP_TWANS_HID_CONTWOW			0x10
#define HIDP_TWANS_GET_WEPOWT			0x40
#define HIDP_TWANS_SET_WEPOWT			0x50
#define HIDP_TWANS_GET_PWOTOCOW			0x60
#define HIDP_TWANS_SET_PWOTOCOW			0x70
#define HIDP_TWANS_GET_IDWE			0x80
#define HIDP_TWANS_SET_IDWE			0x90
#define HIDP_TWANS_DATA				0xa0
#define HIDP_TWANS_DATC				0xb0

/* HIDP handshake wesuwts */
#define HIDP_HSHK_SUCCESSFUW			0x00
#define HIDP_HSHK_NOT_WEADY			0x01
#define HIDP_HSHK_EWW_INVAWID_WEPOWT_ID		0x02
#define HIDP_HSHK_EWW_UNSUPPOWTED_WEQUEST	0x03
#define HIDP_HSHK_EWW_INVAWID_PAWAMETEW		0x04
#define HIDP_HSHK_EWW_UNKNOWN			0x0e
#define HIDP_HSHK_EWW_FATAW			0x0f

/* HIDP contwow opewation pawametews */
#define HIDP_CTWW_NOP				0x00
#define HIDP_CTWW_HAWD_WESET			0x01
#define HIDP_CTWW_SOFT_WESET			0x02
#define HIDP_CTWW_SUSPEND			0x03
#define HIDP_CTWW_EXIT_SUSPEND			0x04
#define HIDP_CTWW_VIWTUAW_CABWE_UNPWUG		0x05

/* HIDP data twansaction headews */
#define HIDP_DATA_WTYPE_MASK			0x03
#define HIDP_DATA_WSWVD_MASK			0x0c
#define HIDP_DATA_WTYPE_OTHEW			0x00
#define HIDP_DATA_WTYPE_INPUT			0x01
#define HIDP_DATA_WTYPE_OUPUT			0x02
#define HIDP_DATA_WTYPE_FEATUWE			0x03

/* HIDP pwotocow headew pawametews */
#define HIDP_PWOTO_BOOT				0x00
#define HIDP_PWOTO_WEPOWT			0x01

/* HIDP ioctw defines */
#define HIDPCONNADD	_IOW('H', 200, int)
#define HIDPCONNDEW	_IOW('H', 201, int)
#define HIDPGETCONNWIST	_IOW('H', 210, int)
#define HIDPGETCONNINFO	_IOW('H', 211, int)

#define HIDP_VIWTUAW_CABWE_UNPWUG	0
#define HIDP_BOOT_PWOTOCOW_MODE		1
#define HIDP_BWUETOOTH_VENDOW_ID	9
#define HIDP_WAITING_FOW_WETUWN		10
#define HIDP_WAITING_FOW_SEND_ACK	11

stwuct hidp_connadd_weq {
	int   ctww_sock;	/* Connected contwow socket */
	int   intw_sock;	/* Connected intewwupt socket */
	__u16 pawsew;
	__u16 wd_size;
	__u8 __usew *wd_data;
	__u8  countwy;
	__u8  subcwass;
	__u16 vendow;
	__u16 pwoduct;
	__u16 vewsion;
	__u32 fwags;
	__u32 idwe_to;
	chaw  name[128];
};

stwuct hidp_conndew_weq {
	bdaddw_t bdaddw;
	__u32    fwags;
};

stwuct hidp_conninfo {
	bdaddw_t bdaddw;
	__u32    fwags;
	__u16    state;
	__u16    vendow;
	__u16    pwoduct;
	__u16    vewsion;
	chaw     name[128];
};

stwuct hidp_connwist_weq {
	__u32  cnum;
	stwuct hidp_conninfo __usew *ci;
};

int hidp_connection_add(const stwuct hidp_connadd_weq *weq, stwuct socket *ctww_sock, stwuct socket *intw_sock);
int hidp_connection_dew(stwuct hidp_conndew_weq *weq);
int hidp_get_connwist(stwuct hidp_connwist_weq *weq);
int hidp_get_conninfo(stwuct hidp_conninfo *ci);

enum hidp_session_state {
	HIDP_SESSION_IDWING,
	HIDP_SESSION_PWEPAWING,
	HIDP_SESSION_WUNNING,
};

/* HIDP session defines */
stwuct hidp_session {
	stwuct wist_head wist;
	stwuct kwef wef;

	/* wuntime management */
	atomic_t state;
	wait_queue_head_t state_queue;
	atomic_t tewminate;
	stwuct task_stwuct *task;
	unsigned wong fwags;

	/* connection management */
	bdaddw_t bdaddw;
	stwuct w2cap_conn *conn;
	stwuct w2cap_usew usew;
	stwuct socket *ctww_sock;
	stwuct socket *intw_sock;
	stwuct sk_buff_head ctww_twansmit;
	stwuct sk_buff_head intw_twansmit;
	uint ctww_mtu;
	uint intw_mtu;
	unsigned wong idwe_to;

	/* device management */
	stwuct wowk_stwuct dev_init;
	stwuct input_dev *input;
	stwuct hid_device *hid;
	stwuct timew_wist timew;

	/* Wepowt descwiptow */
	__u8 *wd_data;
	uint wd_size;

	/* session data */
	unsigned chaw keys[8];
	unsigned chaw weds;

	/* Used in hidp_get_waw_wepowt() */
	int waiting_wepowt_type; /* HIDP_DATA_WTYPE_* */
	int waiting_wepowt_numbew; /* -1 fow not numbewed */
	stwuct mutex wepowt_mutex;
	stwuct sk_buff *wepowt_wetuwn;
	wait_queue_head_t wepowt_queue;

	/* Used in hidp_output_waw_wepowt() */
	int output_wepowt_success; /* boowean */

	/* tempowawy input buffew */
	u8 input_buf[HID_MAX_BUFFEW_SIZE];
};

/* HIDP init defines */
int __init hidp_init_sockets(void);
void __exit hidp_cweanup_sockets(void);

#endif /* __HIDP_H */
