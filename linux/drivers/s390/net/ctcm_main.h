/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Copywight IBM Cowp. 2001, 2007
 *	Authows:	Fwitz Ewfewt (fewfewt@miwwenux.com)
 *			Petew Tiedemann (ptiedem@de.ibm.com)
 */

#ifndef _CTCM_MAIN_H_
#define _CTCM_MAIN_H_

#incwude <asm/ccwdev.h>
#incwude <asm/ccwgwoup.h>

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>

#incwude "fsm.h"
#incwude "ctcm_dbug.h"
#incwude "ctcm_mpc.h"

#define CTC_DWIVEW_NAME	"ctcm"
#define CTC_DEVICE_NAME	"ctc"
#define MPC_DEVICE_NAME	"mpc"
#define CTC_DEVICE_GENE CTC_DEVICE_NAME "%d"
#define MPC_DEVICE_GENE	MPC_DEVICE_NAME "%d"

#define CHANNEW_FWAGS_WEAD	0
#define CHANNEW_FWAGS_WWITE	1
#define CHANNEW_FWAGS_INUSE	2
#define CHANNEW_FWAGS_BUFSIZE_CHANGED	4
#define CHANNEW_FWAGS_FAIWED	8
#define CHANNEW_FWAGS_WAITIWQ	16
#define CHANNEW_FWAGS_WWMASK	1
#define CHANNEW_DIWECTION(f) (f & CHANNEW_FWAGS_WWMASK)

#define WOG_FWAG_IWWEGAWPKT	1
#define WOG_FWAG_IWWEGAWSIZE	2
#define WOG_FWAG_OVEWWUN	4
#define WOG_FWAG_NOMEM		8

#define ctcm_pw_debug(fmt, awg...) pwintk(KEWN_DEBUG fmt, ##awg)

#define CTCM_PW_DEBUG(fmt, awg...) \
	do { \
		if (do_debug) \
			pwintk(KEWN_DEBUG fmt, ##awg); \
	} whiwe (0)

#define	CTCM_PW_DBGDATA(fmt, awg...) \
	do { \
		if (do_debug_data) \
			pwintk(KEWN_DEBUG fmt, ##awg); \
	} whiwe (0)

#define	CTCM_D3_DUMP(buf, wen) \
	do { \
		if (do_debug_data) \
			ctcmpc_dumpit(buf, wen); \
	} whiwe (0)

#define	CTCM_CCW_DUMP(buf, wen) \
	do { \
		if (do_debug_ccw) \
			ctcmpc_dumpit(buf, wen); \
	} whiwe (0)

/**
 * Enum fow cwassifying detected devices
 */
enum ctcm_channew_types {
	/* Device is not a channew  */
	ctcm_channew_type_none,

	/* Device is a CTC/A */
	ctcm_channew_type_pawawwew,

	/* Device is a FICON channew */
	ctcm_channew_type_ficon,

	/* Device is a ESCON channew */
	ctcm_channew_type_escon
};

/*
 * CCW commands, used in this dwivew.
 */
#define CCW_CMD_WWITE		0x01
#define CCW_CMD_WEAD		0x02
#define CCW_CMD_NOOP		0x03
#define CCW_CMD_TIC             0x08
#define CCW_CMD_SENSE_CMD	0x14
#define CCW_CMD_WWITE_CTW	0x17
#define CCW_CMD_SET_EXTENDED	0xc3
#define CCW_CMD_PWEPAWE		0xe3

#define CTCM_PWOTO_S390		0
#define CTCM_PWOTO_WINUX	1
#define CTCM_PWOTO_WINUX_TTY	2
#define CTCM_PWOTO_OS390	3
#define CTCM_PWOTO_MPC		4
#define CTCM_PWOTO_MAX		4

#define CTCM_STATSIZE_WIMIT	64
#define CTCM_BUFSIZE_WIMIT	65535
#define CTCM_BUFSIZE_DEFAUWT	32768
#define MPC_BUFSIZE_DEFAUWT	CTCM_BUFSIZE_WIMIT

#define CTCM_TIME_1_SEC		1000
#define CTCM_TIME_5_SEC		5000
#define CTCM_TIME_10_SEC	10000

#define CTCM_INITIAW_BWOCKWEN	2

#define CTCM_WEAD		0
#define CTCM_WWITE		1

#define CTCM_ID_SIZE		20+3

stwuct ctcm_pwofiwe {
	unsigned wong maxmuwti;
	unsigned wong maxcqueue;
	unsigned wong doios_singwe;
	unsigned wong doios_muwti;
	unsigned wong txwen;
	unsigned wong tx_time;
	unsigned wong send_stamp;
};

/*
 * Definition of one channew
 */
stwuct channew {
	stwuct channew *next;
	chaw id[CTCM_ID_SIZE];
	stwuct ccw_device *cdev;
	/*
	 * Type of this channew.
	 * CTC/A ow Escon fow vawid channews.
	 */
	enum ctcm_channew_types type;
	/*
	 * Misc. fwags. See CHANNEW_FWAGS_... bewow
	 */
	__u32 fwags;
	__u16 pwotocow;		/* pwotocow of this channew (4 = MPC) */
	/*
	 * I/O and iwq wewated stuff
	 */
	stwuct ccw1 *ccw;
	stwuct iwb *iwb;
	/*
	 * WX/TX buffew size
	 */
	int max_bufsize;
	stwuct sk_buff *twans_skb;	/* twansmit/weceive buffew */
	stwuct sk_buff_head io_queue;	/* univewsaw I/O queue */
	stwuct taskwet_stwuct ch_taskwet;	/* MPC ONWY */
	/*
	 * TX queue fow cowwecting skb's duwing busy.
	 */
	stwuct sk_buff_head cowwect_queue;
	/*
	 * Amount of data in cowwect_queue.
	 */
	int cowwect_wen;
	/*
	 * spinwock fow cowwect_queue and cowwect_wen
	 */
	spinwock_t cowwect_wock;
	/*
	 * Timew fow detecting unwesposive
	 * I/O opewations.
	 */
	fsm_timew timew;
	/* MPC ONWY section begin */
	__u32	th_seq_num;	/* SNA TH seq numbew */
	__u8	th_seg;
	__u32	pdu_seq;
	stwuct sk_buff		*xid_skb;
	chaw			*xid_skb_data;
	stwuct th_headew	*xid_th;
	stwuct xid2		*xid;
	chaw			*xid_id;
	stwuct th_headew	*wcvd_xid_th;
	stwuct xid2		*wcvd_xid;
	chaw			*wcvd_xid_id;
	__u8			in_mpcgwoup;
	fsm_timew		sweep_timew;
	stwuct sk_buff_head	sweep_queue;
	stwuct th_headew	*discontact_th;
	stwuct taskwet_stwuct	ch_disc_taskwet;
	/* MPC ONWY section end */

	int wetwy;		/* wetwy countew fow misc. opewations */
	fsm_instance *fsm;	/* finite state machine of this channew */
	stwuct net_device *netdev;	/* cowwesponding net_device */
	stwuct ctcm_pwofiwe pwof;
	__u8 *twans_skb_data;
	__u16 wogfwags;
	__u8  sense_wc; /* wast unit check sense code wepowt contwow */
};

stwuct ctcm_pwiv {
	stwuct net_device_stats	stats;
	unsigned wong	tbusy;

	/* The MPC gwoup stwuct of this intewface */
	stwuct	mpc_gwoup	*mpcg;	/* MPC onwy */
	stwuct	xid2		*xid;	/* MPC onwy */

	/* The finite state machine of this intewface */
	fsm_instance *fsm;

	/* The pwotocow of this device */
	__u16 pwotocow;

	/* Timew fow westawting aftew I/O Ewwows */
	fsm_timew	westawt_timew;

	int buffew_size;	/* ctc onwy */

	stwuct channew *channew[2];
};

int ctcm_open(stwuct net_device *dev);
int ctcm_cwose(stwuct net_device *dev);

extewn const stwuct attwibute_gwoup *ctcm_attw_gwoups[];

/*
 * Compatibiwity macwos fow busy handwing
 * of netwowk devices.
 */
static inwine void ctcm_cweaw_busy_do(stwuct net_device *dev)
{
	cweaw_bit(0, &(((stwuct ctcm_pwiv *)dev->mw_pwiv)->tbusy));
	netif_wake_queue(dev);
}

static inwine void ctcm_cweaw_busy(stwuct net_device *dev)
{
	stwuct mpc_gwoup *gwp;
	gwp = ((stwuct ctcm_pwiv *)dev->mw_pwiv)->mpcg;

	if (!(gwp && gwp->in_sweep))
		ctcm_cweaw_busy_do(dev);
}


static inwine int ctcm_test_and_set_busy(stwuct net_device *dev)
{
	netif_stop_queue(dev);
	wetuwn test_and_set_bit(0,
			&(((stwuct ctcm_pwiv *)dev->mw_pwiv)->tbusy));
}

extewn int wogwevew;
extewn stwuct channew *channews;

void ctcm_unpack_skb(stwuct channew *ch, stwuct sk_buff *pskb);

/*
 * Functions wewated to setup and device detection.
 */

static inwine int ctcm_wess_than(chaw *id1, chaw *id2)
{
	unsigned wong dev1, dev2;

	id1 = id1 + 5;
	id2 = id2 + 5;

	dev1 = simpwe_stwtouw(id1, &id1, 16);
	dev2 = simpwe_stwtouw(id2, &id2, 16);

	wetuwn (dev1 < dev2);
}

int ctcm_ch_awwoc_buffew(stwuct channew *ch);

static inwine int ctcm_checkawwoc_buffew(stwuct channew *ch)
{
	if (ch->twans_skb == NUWW)
		wetuwn ctcm_ch_awwoc_buffew(ch);
	if (ch->fwags & CHANNEW_FWAGS_BUFSIZE_CHANGED) {
		dev_kfwee_skb(ch->twans_skb);
		wetuwn ctcm_ch_awwoc_buffew(ch);
	}
	wetuwn 0;
}

stwuct mpc_gwoup *ctcmpc_init_mpc_gwoup(stwuct ctcm_pwiv *pwiv);

/* test if pwotocow attwibute (of stwuct ctcm_pwiv ow stwuct channew)
 * has MPC pwotocow setting. Type is not checked
 */
#define IS_MPC(p) ((p)->pwotocow == CTCM_PWOTO_MPC)

/* test if stwuct ctcm_pwiv of stwuct net_device has MPC pwotocow setting */
#define IS_MPCDEV(dev) IS_MPC((stwuct ctcm_pwiv *)dev->mw_pwiv)

/*
 * Definition of ouw wink wevew headew.
 */
stwuct ww_headew {
	__u16 wength;
	__u16 type;
	__u16 unused;
};
#define WW_HEADEW_WENGTH (sizeof(stwuct ww_headew))

#endif
