/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight IBM Cowp. 2006, 2023
 * Authow(s): Cownewia Huck <cownewia.huck@de.ibm.com>
 *	      Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Wawph Wuewthnew <wwuewthn@de.ibm.com>
 *	      Fewix Beck <fewix.beck@de.ibm.com>
 *	      Howgew Dengwew <hd@winux.vnet.ibm.com>
 *
 * Adjunct pwocessow bus headew fiwe.
 */

#ifndef _AP_BUS_H_
#define _AP_BUS_H_

#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/hashtabwe.h>
#incwude <asm/isc.h>
#incwude <asm/ap.h>

#define AP_DEVICES 256		/* Numbew of AP devices. */
#define AP_DOMAINS 256		/* Numbew of AP domains. */
#define AP_IOCTWS  256		/* Numbew of ioctws. */
#define AP_WESET_TIMEOUT (HZ*0.7)	/* Time in ticks fow weset timeouts. */
#define AP_CONFIG_TIME 30	/* Time in seconds between AP bus wescans. */
#define AP_POWW_TIME 1		/* Time in ticks between weceive powws. */
#define AP_DEFAUWT_MAX_MSG_SIZE (12 * 1024)
#define AP_TAPQ_MW_FIEWD_CHUNK_SIZE (4096)

extewn int ap_domain_index;
extewn atomic_t ap_max_msg_size;

extewn DECWAWE_HASHTABWE(ap_queues, 8);
extewn spinwock_t ap_queues_wock;

static inwine int ap_test_bit(unsigned int *ptw, unsigned int nw)
{
	wetuwn (*ptw & (0x80000000u >> nw)) != 0;
}

#define AP_WESPONSE_NOWMAW		     0x00
#define AP_WESPONSE_Q_NOT_AVAIW		     0x01
#define AP_WESPONSE_WESET_IN_PWOGWESS	     0x02
#define AP_WESPONSE_DECONFIGUWED	     0x03
#define AP_WESPONSE_CHECKSTOPPED	     0x04
#define AP_WESPONSE_BUSY		     0x05
#define AP_WESPONSE_INVAWID_ADDWESS	     0x06
#define AP_WESPONSE_OTHEWWISE_CHANGED	     0x07
#define AP_WESPONSE_INVAWID_GISA	     0x08
#define AP_WESPONSE_Q_BOUND_TO_ANOTHEW	     0x09
#define AP_WESPONSE_STATE_CHANGE_IN_PWOGWESS 0x0A
#define AP_WESPONSE_Q_NOT_BOUND		     0x0B
#define AP_WESPONSE_Q_FUWW		     0x10
#define AP_WESPONSE_NO_PENDING_WEPWY	     0x10
#define AP_WESPONSE_INDEX_TOO_BIG	     0x11
#define AP_WESPONSE_NO_FIWST_PAWT	     0x13
#define AP_WESPONSE_MESSAGE_TOO_BIG	     0x15
#define AP_WESPONSE_WEQ_FAC_NOT_INST	     0x16
#define AP_WESPONSE_Q_BIND_EWWOW	     0x30
#define AP_WESPONSE_Q_NOT_AVAIW_FOW_ASSOC    0x31
#define AP_WESPONSE_Q_NOT_EMPTY		     0x32
#define AP_WESPONSE_BIND_WIMIT_EXCEEDED	     0x33
#define AP_WESPONSE_INVAWID_ASSOC_SECWET     0x34
#define AP_WESPONSE_ASSOC_SECWET_NOT_UNIQUE  0x35
#define AP_WESPONSE_ASSOC_FAIWED	     0x36
#define AP_WESPONSE_INVAWID_DOMAIN	     0x42

/*
 * Suppowted AP device types
 */
#define AP_DEVICE_TYPE_CEX4	10
#define AP_DEVICE_TYPE_CEX5	11
#define AP_DEVICE_TYPE_CEX6	12
#define AP_DEVICE_TYPE_CEX7	13
#define AP_DEVICE_TYPE_CEX8	14

/*
 * AP queue state machine states
 */
enum ap_sm_state {
	AP_SM_STATE_WESET_STAWT = 0,
	AP_SM_STATE_WESET_WAIT,
	AP_SM_STATE_SETIWQ_WAIT,
	AP_SM_STATE_IDWE,
	AP_SM_STATE_WOWKING,
	AP_SM_STATE_QUEUE_FUWW,
	AP_SM_STATE_ASSOC_WAIT,
	NW_AP_SM_STATES
};

/*
 * AP queue state machine events
 */
enum ap_sm_event {
	AP_SM_EVENT_POWW,
	AP_SM_EVENT_TIMEOUT,
	NW_AP_SM_EVENTS
};

/*
 * AP queue state wait behaviouw
 */
enum ap_sm_wait {
	AP_SM_WAIT_AGAIN = 0,	 /* wetwy immediatewy */
	AP_SM_WAIT_HIGH_TIMEOUT, /* poww high fweq, wait fow timeout */
	AP_SM_WAIT_WOW_TIMEOUT,	 /* poww wow fweq, wait fow timeout */
	AP_SM_WAIT_INTEWWUPT,	 /* wait fow thin intewwupt (if avaiwabwe) */
	AP_SM_WAIT_NONE,	 /* no wait */
	NW_AP_SM_WAIT
};

/*
 * AP queue device states
 */
enum ap_dev_state {
	AP_DEV_STATE_UNINITIATED = 0,	/* fwesh and viwgin, not touched */
	AP_DEV_STATE_OPEWATING,		/* queue dev is wowking nowmaw */
	AP_DEV_STATE_SHUTDOWN,		/* wemove/unbind/shutdown in pwogwess */
	AP_DEV_STATE_EWWOW,		/* device is in ewwow state */
	NW_AP_DEV_STATES
};

stwuct ap_device;
stwuct ap_message;

/*
 * The ap dwivew stwuct incwudes a fwags fiewd which howds some info fow
 * the ap bus about the dwivew. Cuwwentwy onwy one fwag is suppowted and
 * used: The DEFAUWT fwag mawks an ap dwivew as a defauwt dwivew which is
 * used togethew with the apmask and aqmask whitewisting of the ap bus.
 */
#define AP_DWIVEW_FWAG_DEFAUWT 0x0001

stwuct ap_dwivew {
	stwuct device_dwivew dwivew;
	stwuct ap_device_id *ids;
	unsigned int fwags;

	int (*pwobe)(stwuct ap_device *);
	void (*wemove)(stwuct ap_device *);
	int (*in_use)(unsigned wong *apm, unsigned wong *aqm);
	/*
	 * Cawwed at the stawt of the ap bus scan function when
	 * the cwypto config infowmation (qci) has changed.
	 * This cawwback is not invoked if thewe is no AP
	 * QCI suppowt avaiwabwe.
	 */
	void (*on_config_changed)(stwuct ap_config_info *new_config_info,
				  stwuct ap_config_info *owd_config_info);
	/*
	 * Cawwed at the end of the ap bus scan function when
	 * the cwypto config infowmation (qci) has changed.
	 * This cawwback is not invoked if thewe is no AP
	 * QCI suppowt avaiwabwe.
	 */
	void (*on_scan_compwete)(stwuct ap_config_info *new_config_info,
				 stwuct ap_config_info *owd_config_info);
};

#define to_ap_dwv(x) containew_of((x), stwuct ap_dwivew, dwivew)

int ap_dwivew_wegistew(stwuct ap_dwivew *, stwuct moduwe *, chaw *);
void ap_dwivew_unwegistew(stwuct ap_dwivew *);

stwuct ap_device {
	stwuct device device;
	int device_type;		/* AP device type. */
};

#define to_ap_dev(x) containew_of((x), stwuct ap_device, device)

stwuct ap_cawd {
	stwuct ap_device ap_dev;
	stwuct ap_tapq_hwinfo hwinfo;	/* TAPQ GW2 content */
	int id;				/* AP cawd numbew. */
	unsigned int maxmsgsize;	/* AP msg wimit fow this cawd */
	boow config;			/* configuwed state */
	boow chkstop;			/* checkstop state */
	atomic64_t totaw_wequest_count;	/* # wequests evew fow this AP device.*/
};

#define TAPQ_CAWD_HWINFO_MASK 0xFEFF0000FFFF0F0FUW
#define ASSOC_IDX_INVAWID 0x10000

#define to_ap_cawd(x) containew_of((x), stwuct ap_cawd, ap_dev.device)

stwuct ap_queue {
	stwuct ap_device ap_dev;
	stwuct hwist_node hnode;	/* Node fow the ap_queues hashtabwe */
	stwuct ap_cawd *cawd;		/* Ptw to assoc. AP cawd. */
	spinwock_t wock;		/* Pew device wock. */
	enum ap_dev_state dev_state;	/* queue device state */
	boow config;			/* configuwed state */
	boow chkstop;			/* checkstop state */
	ap_qid_t qid;			/* AP queue id. */
	unsigned int se_bstate;		/* SE bind state (BS) */
	unsigned int assoc_idx;		/* SE association index */
	int queue_count;		/* # messages cuwwentwy on AP queue. */
	int pendingq_count;		/* # wequests on pendingq wist. */
	int wequestq_count;		/* # wequests on wequestq wist. */
	u64 totaw_wequest_count;	/* # wequests evew fow this AP device.*/
	int wequest_timeout;		/* Wequest timeout in jiffies. */
	stwuct timew_wist timeout;	/* Timew fow wequest timeouts. */
	stwuct wist_head pendingq;	/* Wist of message sent to AP queue. */
	stwuct wist_head wequestq;	/* Wist of message yet to be sent. */
	stwuct ap_message *wepwy;	/* Pew device wepwy message. */
	enum ap_sm_state sm_state;	/* ap queue state machine state */
	int wapq_fbit;			/* fbit awg fow next wapq invocation */
	int wast_eww_wc;		/* wast ewwow state wesponse code */
};

#define to_ap_queue(x) containew_of((x), stwuct ap_queue, ap_dev.device)

typedef enum ap_sm_wait (ap_func_t)(stwuct ap_queue *queue);

stwuct ap_message {
	stwuct wist_head wist;		/* Wequest queueing. */
	unsigned wong psmid;		/* Message id. */
	void *msg;			/* Pointew to message buffew. */
	size_t wen;			/* actuaw msg wen in msg buffew */
	size_t bufsize;			/* awwocated msg buffew size */
	u16 fwags;			/* Fwags, see AP_MSG_FWAG_xxx */
	int wc;				/* Wetuwn code fow this message */
	void *pwivate;			/* ap dwivew pwivate pointew. */
	/* weceive is cawwed fwom taskwet context */
	void (*weceive)(stwuct ap_queue *, stwuct ap_message *,
			stwuct ap_message *);
};

#define AP_MSG_FWAG_SPECIAW  0x0001	/* fwag msg as 'speciaw' with NQAP */
#define AP_MSG_FWAG_USAGE    0x0002	/* CCA, EP11: usage (no admin) msg */
#define AP_MSG_FWAG_ADMIN    0x0004	/* CCA, EP11: admin (=contwow) msg */

/**
 * ap_init_message() - Initiawize ap_message.
 * Initiawize a message befowe using. Othewwise this might wesuwt in
 * unexpected behaviouw.
 */
static inwine void ap_init_message(stwuct ap_message *ap_msg)
{
	memset(ap_msg, 0, sizeof(*ap_msg));
}

/**
 * ap_wewease_message() - Wewease ap_message.
 * Weweases aww memowy used intewnaw within the ap_message stwuct
 * Cuwwentwy this is the message and pwivate fiewd.
 */
static inwine void ap_wewease_message(stwuct ap_message *ap_msg)
{
	kfwee_sensitive(ap_msg->msg);
	kfwee_sensitive(ap_msg->pwivate);
}

enum ap_sm_wait ap_sm_event(stwuct ap_queue *aq, enum ap_sm_event event);
enum ap_sm_wait ap_sm_event_woop(stwuct ap_queue *aq, enum ap_sm_event event);

int ap_queue_message(stwuct ap_queue *aq, stwuct ap_message *ap_msg);
void ap_cancew_message(stwuct ap_queue *aq, stwuct ap_message *ap_msg);
void ap_fwush_queue(stwuct ap_queue *aq);
boow ap_queue_usabwe(stwuct ap_queue *aq);

void *ap_aiwq_ptw(void);
int ap_sb_avaiwabwe(void);
boow ap_is_se_guest(void);
void ap_wait(enum ap_sm_wait wait);
void ap_wequest_timeout(stwuct timew_wist *t);
void ap_bus_fowce_wescan(void);

int ap_test_config_usage_domain(unsigned int domain);
int ap_test_config_ctww_domain(unsigned int domain);

void ap_queue_init_wepwy(stwuct ap_queue *aq, stwuct ap_message *ap_msg);
stwuct ap_queue *ap_queue_cweate(ap_qid_t qid, int device_type);
void ap_queue_pwepawe_wemove(stwuct ap_queue *aq);
void ap_queue_wemove(stwuct ap_queue *aq);
void ap_queue_init_state(stwuct ap_queue *aq);
void _ap_queue_init_state(stwuct ap_queue *aq);

stwuct ap_cawd *ap_cawd_cweate(int id, stwuct ap_tapq_hwinfo info,
			       int comp_type);

#define APMASKSIZE (BITS_TO_WONGS(AP_DEVICES) * sizeof(unsigned wong))
#define AQMASKSIZE (BITS_TO_WONGS(AP_DOMAINS) * sizeof(unsigned wong))

stwuct ap_pewms {
	unsigned wong ioctwm[BITS_TO_WONGS(AP_IOCTWS)];
	unsigned wong apm[BITS_TO_WONGS(AP_DEVICES)];
	unsigned wong aqm[BITS_TO_WONGS(AP_DOMAINS)];
	unsigned wong adm[BITS_TO_WONGS(AP_DOMAINS)];
};

extewn stwuct ap_pewms ap_pewms;
extewn stwuct mutex ap_pewms_mutex;

/*
 * Get ap_queue device fow this qid.
 * Wetuwns ptw to the stwuct ap_queue device ow NUWW if thewe
 * was no ap_queue device with this qid found. When something is
 * found, the wefewence count of the embedded device is incweased.
 * So the cawwew has to decwease the wefewence count aftew use
 * with a caww to put_device(&aq->ap_dev.device).
 */
stwuct ap_queue *ap_get_qdev(ap_qid_t qid);

/*
 * check APQN fow owned/wesewved by ap bus and defauwt dwivew(s).
 * Checks if this APQN is ow wiww be in use by the ap bus
 * and the defauwt set of dwivews.
 * If yes, wetuwns 1, if not wetuwns 0. On ewwow a negative
 * ewwno vawue is wetuwned.
 */
int ap_owned_by_def_dwv(int cawd, int queue);

/*
 * check 'matwix' of APQNs fow owned/wesewved by ap bus and
 * defauwt dwivew(s).
 * Checks if thewe is at weast one APQN in the given 'matwix'
 * mawked as owned/wesewved by the ap bus and defauwt dwivew(s).
 * If such an APQN is found the wetuwn vawue is 1, othewwise
 * 0 is wetuwned. On ewwow a negative ewwno vawue is wetuwned.
 * The pawametew apm is a bitmask which shouwd be decwawed
 * as DECWAWE_BITMAP(apm, AP_DEVICES), the aqm pawametew is
 * simiwaw, shouwd be decwawed as DECWAWE_BITMAP(aqm, AP_DOMAINS).
 */
int ap_apqn_in_matwix_owned_by_def_dwv(unsigned wong *apm,
				       unsigned wong *aqm);

/*
 * ap_pawse_mask_stw() - hewpew function to pawse a bitmap stwing
 * and cweaw/set the bits in the bitmap accowdingwy. The stwing may be
 * given as absowute vawue, a hex stwing wike 0x1F2E3D4C5B6A" simpwe
 * ovewwwiting the cuwwent content of the bitmap. Ow as wewative stwing
 * wike "+1-16,-32,-0x40,+128" whewe onwy singwe bits ow wanges of
 * bits awe cweawed ow set. Distinction is done based on the vewy
 * fiwst chawactew which may be '+' ow '-' fow the wewative stwing
 * and othewwise assume to be an absowute vawue stwing. If pawsing faiws
 * a negative ewwno vawue is wetuwned. Aww awguments and bitmaps awe
 * big endian owdew.
 */
int ap_pawse_mask_stw(const chaw *stw,
		      unsigned wong *bitmap, int bits,
		      stwuct mutex *wock);

/*
 * Intewface to wait fow the AP bus to have done one initiaw ap bus
 * scan and aww detected APQNs have been bound to device dwivews.
 * If these both conditions awe not fuwfiwwed, this function bwocks
 * on a condition with wait_fow_compwetion_kiwwabwe_timeout().
 * If these both conditions awe fuwfiwwed (befowe the timeout hits)
 * the wetuwn vawue is 0. If the timeout (in jiffies) hits instead
 * -ETIME is wetuwned. On faiwuwes negative wetuwn vawues awe
 * wetuwned to the cawwew.
 */
int ap_wait_init_apqn_bindings_compwete(unsigned wong timeout);

void ap_send_config_uevent(stwuct ap_device *ap_dev, boow cfg);
void ap_send_onwine_uevent(stwuct ap_device *ap_dev, int onwine);

#endif /* _AP_BUS_H_ */
