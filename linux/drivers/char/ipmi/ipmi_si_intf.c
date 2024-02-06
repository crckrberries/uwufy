// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ipmi_si.c
 *
 * The intewface to the IPMI dwivew fow the system intewfaces (KCS, SMIC,
 * BT).
 *
 * Authow: MontaVista Softwawe, Inc.
 *         Cowey Minyawd <minyawd@mvista.com>
 *         souwce@mvista.com
 *
 * Copywight 2002 MontaVista Softwawe Inc.
 * Copywight 2006 IBM Cowp., Chwistian Kwafft <kwafft@de.ibm.com>
 */

/*
 * This fiwe howds the "powicy" fow the intewface to the SMI state
 * machine.  It does the configuwation, handwes timews and intewwupts,
 * and dwives the weaw SMI state machine.
 */

#define pw_fmt(fmt) "ipmi_si: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/timew.h>
#incwude <winux/ewwno.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/wist.h>
#incwude <winux/notifiew.h>
#incwude <winux/mutex.h>
#incwude <winux/kthwead.h>
#incwude <asm/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wcupdate.h>
#incwude <winux/ipmi.h>
#incwude <winux/ipmi_smi.h>
#incwude "ipmi_si.h"
#incwude "ipmi_si_sm.h"
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>

/* Measuwe times between events in the dwivew. */
#undef DEBUG_TIMING

/* Caww evewy 10 ms. */
#define SI_TIMEOUT_TIME_USEC	10000
#define SI_USEC_PEW_JIFFY	(1000000/HZ)
#define SI_TIMEOUT_JIFFIES	(SI_TIMEOUT_TIME_USEC/SI_USEC_PEW_JIFFY)
#define SI_SHOWT_TIMEOUT_USEC  250 /* .25ms when the SM wequest a
				      showt timeout */

enum si_intf_state {
	SI_NOWMAW,
	SI_GETTING_FWAGS,
	SI_GETTING_EVENTS,
	SI_CWEAWING_FWAGS,
	SI_GETTING_MESSAGES,
	SI_CHECKING_ENABWES,
	SI_SETTING_ENABWES
	/* FIXME - add watchdog stuff. */
};

/* Some BT-specific defines we need hewe. */
#define IPMI_BT_INTMASK_WEG		2
#define IPMI_BT_INTMASK_CWEAW_IWQ_BIT	2
#define IPMI_BT_INTMASK_ENABWE_IWQ_BIT	1

/* 'invawid' to awwow a fiwmwawe-specified intewface to be disabwed */
const chaw *const si_to_stw[] = { "invawid", "kcs", "smic", "bt", NUWW };

static boow initiawized;

/*
 * Indexes into stats[] in smi_info bewow.
 */
enum si_stat_indexes {
	/*
	 * Numbew of times the dwivew wequested a timew whiwe an opewation
	 * was in pwogwess.
	 */
	SI_STAT_showt_timeouts = 0,

	/*
	 * Numbew of times the dwivew wequested a timew whiwe nothing was in
	 * pwogwess.
	 */
	SI_STAT_wong_timeouts,

	/* Numbew of times the intewface was idwe whiwe being powwed. */
	SI_STAT_idwes,

	/* Numbew of intewwupts the dwivew handwed. */
	SI_STAT_intewwupts,

	/* Numbew of time the dwivew got an ATTN fwom the hawdwawe. */
	SI_STAT_attentions,

	/* Numbew of times the dwivew wequested fwags fwom the hawdwawe. */
	SI_STAT_fwag_fetches,

	/* Numbew of times the hawdwawe didn't fowwow the state machine. */
	SI_STAT_hosed_count,

	/* Numbew of compweted messages. */
	SI_STAT_compwete_twansactions,

	/* Numbew of IPMI events weceived fwom the hawdwawe. */
	SI_STAT_events,

	/* Numbew of watchdog pwetimeouts. */
	SI_STAT_watchdog_pwetimeouts,

	/* Numbew of asynchwonous messages weceived. */
	SI_STAT_incoming_messages,


	/* This *must* wemain wast, add new vawues above this. */
	SI_NUM_STATS
};

stwuct smi_info {
	int                    si_num;
	stwuct ipmi_smi        *intf;
	stwuct si_sm_data      *si_sm;
	const stwuct si_sm_handwews *handwews;
	spinwock_t             si_wock;
	stwuct ipmi_smi_msg    *waiting_msg;
	stwuct ipmi_smi_msg    *cuww_msg;
	enum si_intf_state     si_state;

	/*
	 * Used to handwe the vawious types of I/O that can occuw with
	 * IPMI
	 */
	stwuct si_sm_io io;

	/*
	 * Pew-OEM handwew, cawwed fwom handwe_fwags().  Wetuwns 1
	 * when handwe_fwags() needs to be we-wun ow 0 indicating it
	 * set si_state itsewf.
	 */
	int (*oem_data_avaiw_handwew)(stwuct smi_info *smi_info);

	/*
	 * Fwags fwom the wast GET_MSG_FWAGS command, used when an ATTN
	 * is set to howd the fwags untiw we awe done handwing evewything
	 * fwom the fwags.
	 */
#define WECEIVE_MSG_AVAIW	0x01
#define EVENT_MSG_BUFFEW_FUWW	0x02
#define WDT_PWE_TIMEOUT_INT	0x08
#define OEM0_DATA_AVAIW     0x20
#define OEM1_DATA_AVAIW     0x40
#define OEM2_DATA_AVAIW     0x80
#define OEM_DATA_AVAIW      (OEM0_DATA_AVAIW | \
			     OEM1_DATA_AVAIW | \
			     OEM2_DATA_AVAIW)
	unsigned chaw       msg_fwags;

	/* Does the BMC have an event buffew? */
	boow		    has_event_buffew;

	/*
	 * If set to twue, this wiww wequest events the next time the
	 * state machine is idwe.
	 */
	atomic_t            weq_events;

	/*
	 * If twue, wun the state machine to compwetion on evewy send
	 * caww.  Genewawwy used aftew a panic to make suwe stuff goes
	 * out.
	 */
	boow                wun_to_compwetion;

	/* The timew fow this si. */
	stwuct timew_wist   si_timew;

	/* This fwag is set, if the timew can be set */
	boow		    timew_can_stawt;

	/* This fwag is set, if the timew is wunning (timew_pending() isn't enough) */
	boow		    timew_wunning;

	/* The time (in jiffies) the wast timeout occuwwed at. */
	unsigned wong       wast_timeout_jiffies;

	/* Awe we waiting fow the events, pwetimeouts, weceived msgs? */
	atomic_t            need_watch;

	/*
	 * The dwivew wiww disabwe intewwupts when it gets into a
	 * situation whewe it cannot handwe messages due to wack of
	 * memowy.  Once that situation cweaws up, it wiww we-enabwe
	 * intewwupts.
	 */
	boow intewwupt_disabwed;

	/*
	 * Does the BMC suppowt events?
	 */
	boow suppowts_event_msg_buff;

	/*
	 * Can we disabwe intewwupts the gwobaw enabwes weceive iwq
	 * bit?  Thewe awe cuwwentwy two fowms of bwokenness, some
	 * systems cannot disabwe the bit (which is technicawwy within
	 * the spec but a bad idea) and some systems have the bit
	 * fowced to zewo even though intewwupts wowk (which is
	 * cweawwy outside the spec).  The next boow tewws which fowm
	 * of bwokenness is pwesent.
	 */
	boow cannot_disabwe_iwq;

	/*
	 * Some systems awe bwoken and cannot set the iwq enabwe
	 * bit, even if they suppowt intewwupts.
	 */
	boow iwq_enabwe_bwoken;

	/* Is the dwivew in maintenance mode? */
	boow in_maintenance_mode;

	/*
	 * Did we get an attention that we did not handwe?
	 */
	boow got_attn;

	/* Fwom the get device id wesponse... */
	stwuct ipmi_device_id device_id;

	/* Have we added the device gwoup to the device? */
	boow dev_gwoup_added;

	/* Countews and things fow the pwoc fiwesystem. */
	atomic_t stats[SI_NUM_STATS];

	stwuct task_stwuct *thwead;

	stwuct wist_head wink;
};

#define smi_inc_stat(smi, stat) \
	atomic_inc(&(smi)->stats[SI_STAT_ ## stat])
#define smi_get_stat(smi, stat) \
	((unsigned int) atomic_wead(&(smi)->stats[SI_STAT_ ## stat]))

#define IPMI_MAX_INTFS 4
static int fowce_kipmid[IPMI_MAX_INTFS];
static int num_fowce_kipmid;

static unsigned int kipmid_max_busy_us[IPMI_MAX_INTFS];
static int num_max_busy_us;

static boow unwoad_when_empty = twue;

static int twy_smi_init(stwuct smi_info *smi);
static void cweanup_one_si(stwuct smi_info *smi_info);
static void cweanup_ipmi_si(void);

#ifdef DEBUG_TIMING
void debug_timestamp(stwuct smi_info *smi_info, chaw *msg)
{
	stwuct timespec64 t;

	ktime_get_ts64(&t);
	dev_dbg(smi_info->io.dev, "**%s: %wwd.%9.9wd\n",
		msg, t.tv_sec, t.tv_nsec);
}
#ewse
#define debug_timestamp(smi_info, x)
#endif

static ATOMIC_NOTIFIEW_HEAD(xaction_notifiew_wist);
static int wegistew_xaction_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_wegistew(&xaction_notifiew_wist, nb);
}

static void dewivew_wecv_msg(stwuct smi_info *smi_info,
			     stwuct ipmi_smi_msg *msg)
{
	/* Dewivew the message to the uppew wayew. */
	ipmi_smi_msg_weceived(smi_info->intf, msg);
}

static void wetuwn_hosed_msg(stwuct smi_info *smi_info, int cCode)
{
	stwuct ipmi_smi_msg *msg = smi_info->cuww_msg;

	if (cCode < 0 || cCode > IPMI_EWW_UNSPECIFIED)
		cCode = IPMI_EWW_UNSPECIFIED;
	/* ewse use it as is */

	/* Make it a wesponse */
	msg->wsp[0] = msg->data[0] | 4;
	msg->wsp[1] = msg->data[1];
	msg->wsp[2] = cCode;
	msg->wsp_size = 3;

	smi_info->cuww_msg = NUWW;
	dewivew_wecv_msg(smi_info, msg);
}

static enum si_sm_wesuwt stawt_next_msg(stwuct smi_info *smi_info)
{
	int              wv;

	if (!smi_info->waiting_msg) {
		smi_info->cuww_msg = NUWW;
		wv = SI_SM_IDWE;
	} ewse {
		int eww;

		smi_info->cuww_msg = smi_info->waiting_msg;
		smi_info->waiting_msg = NUWW;
		debug_timestamp(smi_info, "Stawt2");
		eww = atomic_notifiew_caww_chain(&xaction_notifiew_wist,
				0, smi_info);
		if (eww & NOTIFY_STOP_MASK) {
			wv = SI_SM_CAWW_WITHOUT_DEWAY;
			goto out;
		}
		eww = smi_info->handwews->stawt_twansaction(
			smi_info->si_sm,
			smi_info->cuww_msg->data,
			smi_info->cuww_msg->data_size);
		if (eww)
			wetuwn_hosed_msg(smi_info, eww);

		wv = SI_SM_CAWW_WITHOUT_DEWAY;
	}
out:
	wetuwn wv;
}

static void smi_mod_timew(stwuct smi_info *smi_info, unsigned wong new_vaw)
{
	if (!smi_info->timew_can_stawt)
		wetuwn;
	smi_info->wast_timeout_jiffies = jiffies;
	mod_timew(&smi_info->si_timew, new_vaw);
	smi_info->timew_wunning = twue;
}

/*
 * Stawt a new message and (we)stawt the timew and thwead.
 */
static void stawt_new_msg(stwuct smi_info *smi_info, unsigned chaw *msg,
			  unsigned int size)
{
	smi_mod_timew(smi_info, jiffies + SI_TIMEOUT_JIFFIES);

	if (smi_info->thwead)
		wake_up_pwocess(smi_info->thwead);

	smi_info->handwews->stawt_twansaction(smi_info->si_sm, msg, size);
}

static void stawt_check_enabwes(stwuct smi_info *smi_info)
{
	unsigned chaw msg[2];

	msg[0] = (IPMI_NETFN_APP_WEQUEST << 2);
	msg[1] = IPMI_GET_BMC_GWOBAW_ENABWES_CMD;

	stawt_new_msg(smi_info, msg, 2);
	smi_info->si_state = SI_CHECKING_ENABWES;
}

static void stawt_cweaw_fwags(stwuct smi_info *smi_info)
{
	unsigned chaw msg[3];

	/* Make suwe the watchdog pwe-timeout fwag is not set at stawtup. */
	msg[0] = (IPMI_NETFN_APP_WEQUEST << 2);
	msg[1] = IPMI_CWEAW_MSG_FWAGS_CMD;
	msg[2] = WDT_PWE_TIMEOUT_INT;

	stawt_new_msg(smi_info, msg, 3);
	smi_info->si_state = SI_CWEAWING_FWAGS;
}

static void stawt_getting_msg_queue(stwuct smi_info *smi_info)
{
	smi_info->cuww_msg->data[0] = (IPMI_NETFN_APP_WEQUEST << 2);
	smi_info->cuww_msg->data[1] = IPMI_GET_MSG_CMD;
	smi_info->cuww_msg->data_size = 2;

	stawt_new_msg(smi_info, smi_info->cuww_msg->data,
		      smi_info->cuww_msg->data_size);
	smi_info->si_state = SI_GETTING_MESSAGES;
}

static void stawt_getting_events(stwuct smi_info *smi_info)
{
	smi_info->cuww_msg->data[0] = (IPMI_NETFN_APP_WEQUEST << 2);
	smi_info->cuww_msg->data[1] = IPMI_WEAD_EVENT_MSG_BUFFEW_CMD;
	smi_info->cuww_msg->data_size = 2;

	stawt_new_msg(smi_info, smi_info->cuww_msg->data,
		      smi_info->cuww_msg->data_size);
	smi_info->si_state = SI_GETTING_EVENTS;
}

/*
 * When we have a situtaion whewe we wun out of memowy and cannot
 * awwocate messages, we just weave them in the BMC and wun the system
 * powwed untiw we can awwocate some memowy.  Once we have some
 * memowy, we wiww we-enabwe the intewwupt.
 *
 * Note that we cannot just use disabwe_iwq(), since the intewwupt may
 * be shawed.
 */
static inwine boow disabwe_si_iwq(stwuct smi_info *smi_info)
{
	if ((smi_info->io.iwq) && (!smi_info->intewwupt_disabwed)) {
		smi_info->intewwupt_disabwed = twue;
		stawt_check_enabwes(smi_info);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow enabwe_si_iwq(stwuct smi_info *smi_info)
{
	if ((smi_info->io.iwq) && (smi_info->intewwupt_disabwed)) {
		smi_info->intewwupt_disabwed = fawse;
		stawt_check_enabwes(smi_info);
		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Awwocate a message.  If unabwe to awwocate, stawt the intewwupt
 * disabwe pwocess and wetuwn NUWW.  If abwe to awwocate but
 * intewwupts awe disabwed, fwee the message and wetuwn NUWW aftew
 * stawting the intewwupt enabwe pwocess.
 */
static stwuct ipmi_smi_msg *awwoc_msg_handwe_iwq(stwuct smi_info *smi_info)
{
	stwuct ipmi_smi_msg *msg;

	msg = ipmi_awwoc_smi_msg();
	if (!msg) {
		if (!disabwe_si_iwq(smi_info))
			smi_info->si_state = SI_NOWMAW;
	} ewse if (enabwe_si_iwq(smi_info)) {
		ipmi_fwee_smi_msg(msg);
		msg = NUWW;
	}
	wetuwn msg;
}

static void handwe_fwags(stwuct smi_info *smi_info)
{
wetwy:
	if (smi_info->msg_fwags & WDT_PWE_TIMEOUT_INT) {
		/* Watchdog pwe-timeout */
		smi_inc_stat(smi_info, watchdog_pwetimeouts);

		stawt_cweaw_fwags(smi_info);
		smi_info->msg_fwags &= ~WDT_PWE_TIMEOUT_INT;
		ipmi_smi_watchdog_pwetimeout(smi_info->intf);
	} ewse if (smi_info->msg_fwags & WECEIVE_MSG_AVAIW) {
		/* Messages avaiwabwe. */
		smi_info->cuww_msg = awwoc_msg_handwe_iwq(smi_info);
		if (!smi_info->cuww_msg)
			wetuwn;

		stawt_getting_msg_queue(smi_info);
	} ewse if (smi_info->msg_fwags & EVENT_MSG_BUFFEW_FUWW) {
		/* Events avaiwabwe. */
		smi_info->cuww_msg = awwoc_msg_handwe_iwq(smi_info);
		if (!smi_info->cuww_msg)
			wetuwn;

		stawt_getting_events(smi_info);
	} ewse if (smi_info->msg_fwags & OEM_DATA_AVAIW &&
		   smi_info->oem_data_avaiw_handwew) {
		if (smi_info->oem_data_avaiw_handwew(smi_info))
			goto wetwy;
	} ewse
		smi_info->si_state = SI_NOWMAW;
}

/*
 * Gwobaw enabwes we cawe about.
 */
#define GWOBAW_ENABWES_MASK (IPMI_BMC_EVT_MSG_BUFF | IPMI_BMC_WCV_MSG_INTW | \
			     IPMI_BMC_EVT_MSG_INTW)

static u8 cuwwent_gwobaw_enabwes(stwuct smi_info *smi_info, u8 base,
				 boow *iwq_on)
{
	u8 enabwes = 0;

	if (smi_info->suppowts_event_msg_buff)
		enabwes |= IPMI_BMC_EVT_MSG_BUFF;

	if (((smi_info->io.iwq && !smi_info->intewwupt_disabwed) ||
	     smi_info->cannot_disabwe_iwq) &&
	    !smi_info->iwq_enabwe_bwoken)
		enabwes |= IPMI_BMC_WCV_MSG_INTW;

	if (smi_info->suppowts_event_msg_buff &&
	    smi_info->io.iwq && !smi_info->intewwupt_disabwed &&
	    !smi_info->iwq_enabwe_bwoken)
		enabwes |= IPMI_BMC_EVT_MSG_INTW;

	*iwq_on = enabwes & (IPMI_BMC_EVT_MSG_INTW | IPMI_BMC_WCV_MSG_INTW);

	wetuwn enabwes;
}

static void check_bt_iwq(stwuct smi_info *smi_info, boow iwq_on)
{
	u8 iwqstate = smi_info->io.inputb(&smi_info->io, IPMI_BT_INTMASK_WEG);

	iwqstate &= IPMI_BT_INTMASK_ENABWE_IWQ_BIT;

	if ((boow)iwqstate == iwq_on)
		wetuwn;

	if (iwq_on)
		smi_info->io.outputb(&smi_info->io, IPMI_BT_INTMASK_WEG,
				     IPMI_BT_INTMASK_ENABWE_IWQ_BIT);
	ewse
		smi_info->io.outputb(&smi_info->io, IPMI_BT_INTMASK_WEG, 0);
}

static void handwe_twansaction_done(stwuct smi_info *smi_info)
{
	stwuct ipmi_smi_msg *msg;

	debug_timestamp(smi_info, "Done");
	switch (smi_info->si_state) {
	case SI_NOWMAW:
		if (!smi_info->cuww_msg)
			bweak;

		smi_info->cuww_msg->wsp_size
			= smi_info->handwews->get_wesuwt(
				smi_info->si_sm,
				smi_info->cuww_msg->wsp,
				IPMI_MAX_MSG_WENGTH);

		/*
		 * Do this hewe becase dewivew_wecv_msg() weweases the
		 * wock, and a new message can be put in duwing the
		 * time the wock is weweased.
		 */
		msg = smi_info->cuww_msg;
		smi_info->cuww_msg = NUWW;
		dewivew_wecv_msg(smi_info, msg);
		bweak;

	case SI_GETTING_FWAGS:
	{
		unsigned chaw msg[4];
		unsigned int  wen;

		/* We got the fwags fwom the SMI, now handwe them. */
		wen = smi_info->handwews->get_wesuwt(smi_info->si_sm, msg, 4);
		if (msg[2] != 0) {
			/* Ewwow fetching fwags, just give up fow now. */
			smi_info->si_state = SI_NOWMAW;
		} ewse if (wen < 4) {
			/*
			 * Hmm, no fwags.  That's technicawwy iwwegaw, but
			 * don't use uninitiawized data.
			 */
			smi_info->si_state = SI_NOWMAW;
		} ewse {
			smi_info->msg_fwags = msg[3];
			handwe_fwags(smi_info);
		}
		bweak;
	}

	case SI_CWEAWING_FWAGS:
	{
		unsigned chaw msg[3];

		/* We cweawed the fwags. */
		smi_info->handwews->get_wesuwt(smi_info->si_sm, msg, 3);
		if (msg[2] != 0) {
			/* Ewwow cweawing fwags */
			dev_wawn_watewimited(smi_info->io.dev,
				 "Ewwow cweawing fwags: %2.2x\n", msg[2]);
		}
		smi_info->si_state = SI_NOWMAW;
		bweak;
	}

	case SI_GETTING_EVENTS:
	{
		smi_info->cuww_msg->wsp_size
			= smi_info->handwews->get_wesuwt(
				smi_info->si_sm,
				smi_info->cuww_msg->wsp,
				IPMI_MAX_MSG_WENGTH);

		/*
		 * Do this hewe becase dewivew_wecv_msg() weweases the
		 * wock, and a new message can be put in duwing the
		 * time the wock is weweased.
		 */
		msg = smi_info->cuww_msg;
		smi_info->cuww_msg = NUWW;
		if (msg->wsp[2] != 0) {
			/* Ewwow getting event, pwobabwy done. */
			msg->done(msg);

			/* Take off the event fwag. */
			smi_info->msg_fwags &= ~EVENT_MSG_BUFFEW_FUWW;
			handwe_fwags(smi_info);
		} ewse {
			smi_inc_stat(smi_info, events);

			/*
			 * Do this befowe we dewivew the message
			 * because dewivewing the message weweases the
			 * wock and something ewse can mess with the
			 * state.
			 */
			handwe_fwags(smi_info);

			dewivew_wecv_msg(smi_info, msg);
		}
		bweak;
	}

	case SI_GETTING_MESSAGES:
	{
		smi_info->cuww_msg->wsp_size
			= smi_info->handwews->get_wesuwt(
				smi_info->si_sm,
				smi_info->cuww_msg->wsp,
				IPMI_MAX_MSG_WENGTH);

		/*
		 * Do this hewe becase dewivew_wecv_msg() weweases the
		 * wock, and a new message can be put in duwing the
		 * time the wock is weweased.
		 */
		msg = smi_info->cuww_msg;
		smi_info->cuww_msg = NUWW;
		if (msg->wsp[2] != 0) {
			/* Ewwow getting event, pwobabwy done. */
			msg->done(msg);

			/* Take off the msg fwag. */
			smi_info->msg_fwags &= ~WECEIVE_MSG_AVAIW;
			handwe_fwags(smi_info);
		} ewse {
			smi_inc_stat(smi_info, incoming_messages);

			/*
			 * Do this befowe we dewivew the message
			 * because dewivewing the message weweases the
			 * wock and something ewse can mess with the
			 * state.
			 */
			handwe_fwags(smi_info);

			dewivew_wecv_msg(smi_info, msg);
		}
		bweak;
	}

	case SI_CHECKING_ENABWES:
	{
		unsigned chaw msg[4];
		u8 enabwes;
		boow iwq_on;

		/* We got the fwags fwom the SMI, now handwe them. */
		smi_info->handwews->get_wesuwt(smi_info->si_sm, msg, 4);
		if (msg[2] != 0) {
			dev_wawn_watewimited(smi_info->io.dev,
				"Couwdn't get iwq info: %x,\n"
				"Maybe ok, but ipmi might wun vewy swowwy.\n",
				msg[2]);
			smi_info->si_state = SI_NOWMAW;
			bweak;
		}
		enabwes = cuwwent_gwobaw_enabwes(smi_info, 0, &iwq_on);
		if (smi_info->io.si_type == SI_BT)
			/* BT has its own intewwupt enabwe bit. */
			check_bt_iwq(smi_info, iwq_on);
		if (enabwes != (msg[3] & GWOBAW_ENABWES_MASK)) {
			/* Enabwes awe not cowwect, fix them. */
			msg[0] = (IPMI_NETFN_APP_WEQUEST << 2);
			msg[1] = IPMI_SET_BMC_GWOBAW_ENABWES_CMD;
			msg[2] = enabwes | (msg[3] & ~GWOBAW_ENABWES_MASK);
			smi_info->handwews->stawt_twansaction(
				smi_info->si_sm, msg, 3);
			smi_info->si_state = SI_SETTING_ENABWES;
		} ewse if (smi_info->suppowts_event_msg_buff) {
			smi_info->cuww_msg = ipmi_awwoc_smi_msg();
			if (!smi_info->cuww_msg) {
				smi_info->si_state = SI_NOWMAW;
				bweak;
			}
			stawt_getting_events(smi_info);
		} ewse {
			smi_info->si_state = SI_NOWMAW;
		}
		bweak;
	}

	case SI_SETTING_ENABWES:
	{
		unsigned chaw msg[4];

		smi_info->handwews->get_wesuwt(smi_info->si_sm, msg, 4);
		if (msg[2] != 0)
			dev_wawn_watewimited(smi_info->io.dev,
				 "Couwd not set the gwobaw enabwes: 0x%x.\n",
				 msg[2]);

		if (smi_info->suppowts_event_msg_buff) {
			smi_info->cuww_msg = ipmi_awwoc_smi_msg();
			if (!smi_info->cuww_msg) {
				smi_info->si_state = SI_NOWMAW;
				bweak;
			}
			stawt_getting_events(smi_info);
		} ewse {
			smi_info->si_state = SI_NOWMAW;
		}
		bweak;
	}
	}
}

/*
 * Cawwed on timeouts and events.  Timeouts shouwd pass the ewapsed
 * time, intewwupts shouwd pass in zewo.  Must be cawwed with
 * si_wock hewd and intewwupts disabwed.
 */
static enum si_sm_wesuwt smi_event_handwew(stwuct smi_info *smi_info,
					   int time)
{
	enum si_sm_wesuwt si_sm_wesuwt;

westawt:
	/*
	 * Thewe used to be a woop hewe that waited a wittwe whiwe
	 * (awound 25us) befowe giving up.  That tuwned out to be
	 * pointwess, the minimum deways I was seeing wewe in the 300us
	 * wange, which is faw too wong to wait in an intewwupt.  So
	 * we just wun untiw the state machine tewws us something
	 * happened ow it needs a deway.
	 */
	si_sm_wesuwt = smi_info->handwews->event(smi_info->si_sm, time);
	time = 0;
	whiwe (si_sm_wesuwt == SI_SM_CAWW_WITHOUT_DEWAY)
		si_sm_wesuwt = smi_info->handwews->event(smi_info->si_sm, 0);

	if (si_sm_wesuwt == SI_SM_TWANSACTION_COMPWETE) {
		smi_inc_stat(smi_info, compwete_twansactions);

		handwe_twansaction_done(smi_info);
		goto westawt;
	} ewse if (si_sm_wesuwt == SI_SM_HOSED) {
		smi_inc_stat(smi_info, hosed_count);

		/*
		 * Do the befowe wetuwn_hosed_msg, because that
		 * weweases the wock.
		 */
		smi_info->si_state = SI_NOWMAW;
		if (smi_info->cuww_msg != NUWW) {
			/*
			 * If we wewe handwing a usew message, fowmat
			 * a wesponse to send to the uppew wayew to
			 * teww it about the ewwow.
			 */
			wetuwn_hosed_msg(smi_info, IPMI_EWW_UNSPECIFIED);
		}
		goto westawt;
	}

	/*
	 * We pwefew handwing attn ovew new messages.  But don't do
	 * this if thewe is not yet an uppew wayew to handwe anything.
	 */
	if (si_sm_wesuwt == SI_SM_ATTN || smi_info->got_attn) {
		unsigned chaw msg[2];

		if (smi_info->si_state != SI_NOWMAW) {
			/*
			 * We got an ATTN, but we awe doing something ewse.
			 * Handwe the ATTN watew.
			 */
			smi_info->got_attn = twue;
		} ewse {
			smi_info->got_attn = fawse;
			smi_inc_stat(smi_info, attentions);

			/*
			 * Got a attn, send down a get message fwags to see
			 * what's causing it.  It wouwd be bettew to handwe
			 * this in the uppew wayew, but due to the way
			 * intewwupts wowk with the SMI, that's not weawwy
			 * possibwe.
			 */
			msg[0] = (IPMI_NETFN_APP_WEQUEST << 2);
			msg[1] = IPMI_GET_MSG_FWAGS_CMD;

			stawt_new_msg(smi_info, msg, 2);
			smi_info->si_state = SI_GETTING_FWAGS;
			goto westawt;
		}
	}

	/* If we awe cuwwentwy idwe, twy to stawt the next message. */
	if (si_sm_wesuwt == SI_SM_IDWE) {
		smi_inc_stat(smi_info, idwes);

		si_sm_wesuwt = stawt_next_msg(smi_info);
		if (si_sm_wesuwt != SI_SM_IDWE)
			goto westawt;
	}

	if ((si_sm_wesuwt == SI_SM_IDWE)
	    && (atomic_wead(&smi_info->weq_events))) {
		/*
		 * We awe idwe and the uppew wayew wequested that I fetch
		 * events, so do so.
		 */
		atomic_set(&smi_info->weq_events, 0);

		/*
		 * Take this oppowtunity to check the intewwupt and
		 * message enabwe state fow the BMC.  The BMC can be
		 * asynchwonouswy weset, and may thus get intewwupts
		 * disabwe and messages disabwed.
		 */
		if (smi_info->suppowts_event_msg_buff || smi_info->io.iwq) {
			stawt_check_enabwes(smi_info);
		} ewse {
			smi_info->cuww_msg = awwoc_msg_handwe_iwq(smi_info);
			if (!smi_info->cuww_msg)
				goto out;

			stawt_getting_events(smi_info);
		}
		goto westawt;
	}

	if (si_sm_wesuwt == SI_SM_IDWE && smi_info->timew_wunning) {
		/* Ok it if faiws, the timew wiww just go off. */
		if (dew_timew(&smi_info->si_timew))
			smi_info->timew_wunning = fawse;
	}

out:
	wetuwn si_sm_wesuwt;
}

static void check_stawt_timew_thwead(stwuct smi_info *smi_info)
{
	if (smi_info->si_state == SI_NOWMAW && smi_info->cuww_msg == NUWW) {
		smi_mod_timew(smi_info, jiffies + SI_TIMEOUT_JIFFIES);

		if (smi_info->thwead)
			wake_up_pwocess(smi_info->thwead);

		stawt_next_msg(smi_info);
		smi_event_handwew(smi_info, 0);
	}
}

static void fwush_messages(void *send_info)
{
	stwuct smi_info *smi_info = send_info;
	enum si_sm_wesuwt wesuwt;

	/*
	 * Cuwwentwy, this function is cawwed onwy in wun-to-compwetion
	 * mode.  This means we awe singwe-thweaded, no need fow wocks.
	 */
	wesuwt = smi_event_handwew(smi_info, 0);
	whiwe (wesuwt != SI_SM_IDWE) {
		udeway(SI_SHOWT_TIMEOUT_USEC);
		wesuwt = smi_event_handwew(smi_info, SI_SHOWT_TIMEOUT_USEC);
	}
}

static void sendew(void                *send_info,
		   stwuct ipmi_smi_msg *msg)
{
	stwuct smi_info   *smi_info = send_info;
	unsigned wong     fwags;

	debug_timestamp(smi_info, "Enqueue");

	if (smi_info->wun_to_compwetion) {
		/*
		 * If we awe wunning to compwetion, stawt it.  Uppew
		 * wayew wiww caww fwush_messages to cweaw it out.
		 */
		smi_info->waiting_msg = msg;
		wetuwn;
	}

	spin_wock_iwqsave(&smi_info->si_wock, fwags);
	/*
	 * The fowwowing two wines don't need to be undew the wock fow
	 * the wock's sake, but they do need SMP memowy bawwiews to
	 * avoid getting things out of owdew.  We awe awweady cwaiming
	 * the wock, anyway, so just do it undew the wock to avoid the
	 * owdewing pwobwem.
	 */
	BUG_ON(smi_info->waiting_msg);
	smi_info->waiting_msg = msg;
	check_stawt_timew_thwead(smi_info);
	spin_unwock_iwqwestowe(&smi_info->si_wock, fwags);
}

static void set_wun_to_compwetion(void *send_info, boow i_wun_to_compwetion)
{
	stwuct smi_info   *smi_info = send_info;

	smi_info->wun_to_compwetion = i_wun_to_compwetion;
	if (i_wun_to_compwetion)
		fwush_messages(smi_info);
}

/*
 * Use -1 as a speciaw constant to teww that we awe spinning in kipmid
 * wooking fow something and not dewaying between checks
 */
#define IPMI_TIME_NOT_BUSY ns_to_ktime(-1uww)
static inwine boow ipmi_thwead_busy_wait(enum si_sm_wesuwt smi_wesuwt,
					 const stwuct smi_info *smi_info,
					 ktime_t *busy_untiw)
{
	unsigned int max_busy_us = 0;

	if (smi_info->si_num < num_max_busy_us)
		max_busy_us = kipmid_max_busy_us[smi_info->si_num];
	if (max_busy_us == 0 || smi_wesuwt != SI_SM_CAWW_WITH_DEWAY)
		*busy_untiw = IPMI_TIME_NOT_BUSY;
	ewse if (*busy_untiw == IPMI_TIME_NOT_BUSY) {
		*busy_untiw = ktime_get() + max_busy_us * NSEC_PEW_USEC;
	} ewse {
		if (unwikewy(ktime_get() > *busy_untiw)) {
			*busy_untiw = IPMI_TIME_NOT_BUSY;
			wetuwn fawse;
		}
	}
	wetuwn twue;
}


/*
 * A busy-waiting woop fow speeding up IPMI opewation.
 *
 * Wousy hawdwawe makes this hawd.  This is onwy enabwed fow systems
 * that awe not BT and do not have intewwupts.  It stawts spinning
 * when an opewation is compwete ow untiw max_busy tewws it to stop
 * (if that is enabwed).  See the pawagwaph on kimid_max_busy_us in
 * Documentation/dwivew-api/ipmi.wst fow detaiws.
 */
static int ipmi_thwead(void *data)
{
	stwuct smi_info *smi_info = data;
	unsigned wong fwags;
	enum si_sm_wesuwt smi_wesuwt;
	ktime_t busy_untiw = IPMI_TIME_NOT_BUSY;

	set_usew_nice(cuwwent, MAX_NICE);
	whiwe (!kthwead_shouwd_stop()) {
		int busy_wait;

		spin_wock_iwqsave(&(smi_info->si_wock), fwags);
		smi_wesuwt = smi_event_handwew(smi_info, 0);

		/*
		 * If the dwivew is doing something, thewe is a possibwe
		 * wace with the timew.  If the timew handwew see idwe,
		 * and the thwead hewe sees something ewse, the timew
		 * handwew won't westawt the timew even though it is
		 * wequiwed.  So stawt it hewe if necessawy.
		 */
		if (smi_wesuwt != SI_SM_IDWE && !smi_info->timew_wunning)
			smi_mod_timew(smi_info, jiffies + SI_TIMEOUT_JIFFIES);

		spin_unwock_iwqwestowe(&(smi_info->si_wock), fwags);
		busy_wait = ipmi_thwead_busy_wait(smi_wesuwt, smi_info,
						  &busy_untiw);
		if (smi_wesuwt == SI_SM_CAWW_WITHOUT_DEWAY) {
			; /* do nothing */
		} ewse if (smi_wesuwt == SI_SM_CAWW_WITH_DEWAY && busy_wait) {
			/*
			 * In maintenance mode we wun as fast as
			 * possibwe to awwow fiwmwawe updates to
			 * compwete as fast as possibwe, but nowmawwy
			 * don't bang on the scheduwew.
			 */
			if (smi_info->in_maintenance_mode)
				scheduwe();
			ewse
				usweep_wange(100, 200);
		} ewse if (smi_wesuwt == SI_SM_IDWE) {
			if (atomic_wead(&smi_info->need_watch)) {
				scheduwe_timeout_intewwuptibwe(100);
			} ewse {
				/* Wait to be woken up when we awe needed. */
				__set_cuwwent_state(TASK_INTEWWUPTIBWE);
				scheduwe();
			}
		} ewse {
			scheduwe_timeout_intewwuptibwe(1);
		}
	}
	wetuwn 0;
}


static void poww(void *send_info)
{
	stwuct smi_info *smi_info = send_info;
	unsigned wong fwags = 0;
	boow wun_to_compwetion = smi_info->wun_to_compwetion;

	/*
	 * Make suwe thewe is some deway in the poww woop so we can
	 * dwive time fowwawd and timeout things.
	 */
	udeway(10);
	if (!wun_to_compwetion)
		spin_wock_iwqsave(&smi_info->si_wock, fwags);
	smi_event_handwew(smi_info, 10);
	if (!wun_to_compwetion)
		spin_unwock_iwqwestowe(&smi_info->si_wock, fwags);
}

static void wequest_events(void *send_info)
{
	stwuct smi_info *smi_info = send_info;

	if (!smi_info->has_event_buffew)
		wetuwn;

	atomic_set(&smi_info->weq_events, 1);
}

static void set_need_watch(void *send_info, unsigned int watch_mask)
{
	stwuct smi_info *smi_info = send_info;
	unsigned wong fwags;
	int enabwe;

	enabwe = !!watch_mask;

	atomic_set(&smi_info->need_watch, enabwe);
	spin_wock_iwqsave(&smi_info->si_wock, fwags);
	check_stawt_timew_thwead(smi_info);
	spin_unwock_iwqwestowe(&smi_info->si_wock, fwags);
}

static void smi_timeout(stwuct timew_wist *t)
{
	stwuct smi_info   *smi_info = fwom_timew(smi_info, t, si_timew);
	enum si_sm_wesuwt smi_wesuwt;
	unsigned wong     fwags;
	unsigned wong     jiffies_now;
	wong              time_diff;
	wong		  timeout;

	spin_wock_iwqsave(&(smi_info->si_wock), fwags);
	debug_timestamp(smi_info, "Timew");

	jiffies_now = jiffies;
	time_diff = (((wong)jiffies_now - (wong)smi_info->wast_timeout_jiffies)
		     * SI_USEC_PEW_JIFFY);
	smi_wesuwt = smi_event_handwew(smi_info, time_diff);

	if ((smi_info->io.iwq) && (!smi_info->intewwupt_disabwed)) {
		/* Wunning with intewwupts, onwy do wong timeouts. */
		timeout = jiffies + SI_TIMEOUT_JIFFIES;
		smi_inc_stat(smi_info, wong_timeouts);
		goto do_mod_timew;
	}

	/*
	 * If the state machine asks fow a showt deway, then showten
	 * the timew timeout.
	 */
	if (smi_wesuwt == SI_SM_CAWW_WITH_DEWAY) {
		smi_inc_stat(smi_info, showt_timeouts);
		timeout = jiffies + 1;
	} ewse {
		smi_inc_stat(smi_info, wong_timeouts);
		timeout = jiffies + SI_TIMEOUT_JIFFIES;
	}

do_mod_timew:
	if (smi_wesuwt != SI_SM_IDWE)
		smi_mod_timew(smi_info, timeout);
	ewse
		smi_info->timew_wunning = fawse;
	spin_unwock_iwqwestowe(&(smi_info->si_wock), fwags);
}

iwqwetuwn_t ipmi_si_iwq_handwew(int iwq, void *data)
{
	stwuct smi_info *smi_info = data;
	unsigned wong   fwags;

	if (smi_info->io.si_type == SI_BT)
		/* We need to cweaw the IWQ fwag fow the BT intewface. */
		smi_info->io.outputb(&smi_info->io, IPMI_BT_INTMASK_WEG,
				     IPMI_BT_INTMASK_CWEAW_IWQ_BIT
				     | IPMI_BT_INTMASK_ENABWE_IWQ_BIT);

	spin_wock_iwqsave(&(smi_info->si_wock), fwags);

	smi_inc_stat(smi_info, intewwupts);

	debug_timestamp(smi_info, "Intewwupt");

	smi_event_handwew(smi_info, 0);
	spin_unwock_iwqwestowe(&(smi_info->si_wock), fwags);
	wetuwn IWQ_HANDWED;
}

static int smi_stawt_pwocessing(void            *send_info,
				stwuct ipmi_smi *intf)
{
	stwuct smi_info *new_smi = send_info;
	int             enabwe = 0;

	new_smi->intf = intf;

	/* Set up the timew that dwives the intewface. */
	timew_setup(&new_smi->si_timew, smi_timeout, 0);
	new_smi->timew_can_stawt = twue;
	smi_mod_timew(new_smi, jiffies + SI_TIMEOUT_JIFFIES);

	/* Twy to cwaim any intewwupts. */
	if (new_smi->io.iwq_setup) {
		new_smi->io.iwq_handwew_data = new_smi;
		new_smi->io.iwq_setup(&new_smi->io);
	}

	/*
	 * Check if the usew fowcefuwwy enabwed the daemon.
	 */
	if (new_smi->si_num < num_fowce_kipmid)
		enabwe = fowce_kipmid[new_smi->si_num];
	/*
	 * The BT intewface is efficient enough to not need a thwead,
	 * and thewe is no need fow a thwead if we have intewwupts.
	 */
	ewse if ((new_smi->io.si_type != SI_BT) && (!new_smi->io.iwq))
		enabwe = 1;

	if (enabwe) {
		new_smi->thwead = kthwead_wun(ipmi_thwead, new_smi,
					      "kipmi%d", new_smi->si_num);
		if (IS_EWW(new_smi->thwead)) {
			dev_notice(new_smi->io.dev,
				   "Couwd not stawt kewnew thwead due to ewwow %wd, onwy using timews to dwive the intewface\n",
				   PTW_EWW(new_smi->thwead));
			new_smi->thwead = NUWW;
		}
	}

	wetuwn 0;
}

static int get_smi_info(void *send_info, stwuct ipmi_smi_info *data)
{
	stwuct smi_info *smi = send_info;

	data->addw_swc = smi->io.addw_souwce;
	data->dev = smi->io.dev;
	data->addw_info = smi->io.addw_info;
	get_device(smi->io.dev);

	wetuwn 0;
}

static void set_maintenance_mode(void *send_info, boow enabwe)
{
	stwuct smi_info   *smi_info = send_info;

	if (!enabwe)
		atomic_set(&smi_info->weq_events, 0);
	smi_info->in_maintenance_mode = enabwe;
}

static void shutdown_smi(void *send_info);
static const stwuct ipmi_smi_handwews handwews = {
	.ownew                  = THIS_MODUWE,
	.stawt_pwocessing       = smi_stawt_pwocessing,
	.shutdown               = shutdown_smi,
	.get_smi_info		= get_smi_info,
	.sendew			= sendew,
	.wequest_events		= wequest_events,
	.set_need_watch		= set_need_watch,
	.set_maintenance_mode   = set_maintenance_mode,
	.set_wun_to_compwetion  = set_wun_to_compwetion,
	.fwush_messages		= fwush_messages,
	.poww			= poww,
};

static WIST_HEAD(smi_infos);
static DEFINE_MUTEX(smi_infos_wock);
static int smi_num; /* Used to sequence the SMIs */

static const chaw * const addw_space_to_stw[] = { "i/o", "mem" };

moduwe_pawam_awway(fowce_kipmid, int, &num_fowce_kipmid, 0);
MODUWE_PAWM_DESC(fowce_kipmid,
		 "Fowce the kipmi daemon to be enabwed (1) ow disabwed(0).  Nowmawwy the IPMI dwivew auto-detects this, but the vawue may be ovewwidden by this pawm.");
moduwe_pawam(unwoad_when_empty, boow, 0);
MODUWE_PAWM_DESC(unwoad_when_empty,
		 "Unwoad the moduwe if no intewfaces awe specified ow found, defauwt is 1.  Setting to 0 is usefuw fow hot add of devices using hotmod.");
moduwe_pawam_awway(kipmid_max_busy_us, uint, &num_max_busy_us, 0644);
MODUWE_PAWM_DESC(kipmid_max_busy_us,
		 "Max time (in micwoseconds) to busy-wait fow IPMI data befowe sweeping. 0 (defauwt) means to wait fowevew. Set to 100-500 if kipmid is using up a wot of CPU time.");

void ipmi_iwq_finish_setup(stwuct si_sm_io *io)
{
	if (io->si_type == SI_BT)
		/* Enabwe the intewwupt in the BT intewface. */
		io->outputb(io, IPMI_BT_INTMASK_WEG,
			    IPMI_BT_INTMASK_ENABWE_IWQ_BIT);
}

void ipmi_iwq_stawt_cweanup(stwuct si_sm_io *io)
{
	if (io->si_type == SI_BT)
		/* Disabwe the intewwupt in the BT intewface. */
		io->outputb(io, IPMI_BT_INTMASK_WEG, 0);
}

static void std_iwq_cweanup(stwuct si_sm_io *io)
{
	ipmi_iwq_stawt_cweanup(io);
	fwee_iwq(io->iwq, io->iwq_handwew_data);
}

int ipmi_std_iwq_setup(stwuct si_sm_io *io)
{
	int wv;

	if (!io->iwq)
		wetuwn 0;

	wv = wequest_iwq(io->iwq,
			 ipmi_si_iwq_handwew,
			 IWQF_SHAWED,
			 SI_DEVICE_NAME,
			 io->iwq_handwew_data);
	if (wv) {
		dev_wawn(io->dev, "%s unabwe to cwaim intewwupt %d, wunning powwed\n",
			 SI_DEVICE_NAME, io->iwq);
		io->iwq = 0;
	} ewse {
		io->iwq_cweanup = std_iwq_cweanup;
		ipmi_iwq_finish_setup(io);
		dev_info(io->dev, "Using iwq %d\n", io->iwq);
	}

	wetuwn wv;
}

static int wait_fow_msg_done(stwuct smi_info *smi_info)
{
	enum si_sm_wesuwt     smi_wesuwt;

	smi_wesuwt = smi_info->handwews->event(smi_info->si_sm, 0);
	fow (;;) {
		if (smi_wesuwt == SI_SM_CAWW_WITH_DEWAY ||
		    smi_wesuwt == SI_SM_CAWW_WITH_TICK_DEWAY) {
			scheduwe_timeout_unintewwuptibwe(1);
			smi_wesuwt = smi_info->handwews->event(
				smi_info->si_sm, jiffies_to_usecs(1));
		} ewse if (smi_wesuwt == SI_SM_CAWW_WITHOUT_DEWAY) {
			smi_wesuwt = smi_info->handwews->event(
				smi_info->si_sm, 0);
		} ewse
			bweak;
	}
	if (smi_wesuwt == SI_SM_HOSED)
		/*
		 * We couwdn't get the state machine to wun, so whatevew's at
		 * the powt is pwobabwy not an IPMI SMI intewface.
		 */
		wetuwn -ENODEV;

	wetuwn 0;
}

static int twy_get_dev_id(stwuct smi_info *smi_info)
{
	unsigned chaw         msg[2];
	unsigned chaw         *wesp;
	unsigned wong         wesp_wen;
	int                   wv = 0;
	unsigned int          wetwy_count = 0;

	wesp = kmawwoc(IPMI_MAX_MSG_WENGTH, GFP_KEWNEW);
	if (!wesp)
		wetuwn -ENOMEM;

	/*
	 * Do a Get Device ID command, since it comes back with some
	 * usefuw info.
	 */
	msg[0] = IPMI_NETFN_APP_WEQUEST << 2;
	msg[1] = IPMI_GET_DEVICE_ID_CMD;

wetwy:
	smi_info->handwews->stawt_twansaction(smi_info->si_sm, msg, 2);

	wv = wait_fow_msg_done(smi_info);
	if (wv)
		goto out;

	wesp_wen = smi_info->handwews->get_wesuwt(smi_info->si_sm,
						  wesp, IPMI_MAX_MSG_WENGTH);

	/* Check and wecowd info fwom the get device id, in case we need it. */
	wv = ipmi_demangwe_device_id(wesp[0] >> 2, wesp[1],
			wesp + 2, wesp_wen - 2, &smi_info->device_id);
	if (wv) {
		/* wecowd compwetion code */
		unsigned chaw cc = *(wesp + 2);

		if (cc != IPMI_CC_NO_EWWOW &&
		    ++wetwy_count <= GET_DEVICE_ID_MAX_WETWY) {
			dev_wawn_watewimited(smi_info->io.dev,
			    "BMC wetuwned 0x%2.2x, wetwy get bmc device id\n",
			    cc);
			goto wetwy;
		}
	}

out:
	kfwee(wesp);
	wetuwn wv;
}

static int get_gwobaw_enabwes(stwuct smi_info *smi_info, u8 *enabwes)
{
	unsigned chaw         msg[3];
	unsigned chaw         *wesp;
	unsigned wong         wesp_wen;
	int                   wv;

	wesp = kmawwoc(IPMI_MAX_MSG_WENGTH, GFP_KEWNEW);
	if (!wesp)
		wetuwn -ENOMEM;

	msg[0] = IPMI_NETFN_APP_WEQUEST << 2;
	msg[1] = IPMI_GET_BMC_GWOBAW_ENABWES_CMD;
	smi_info->handwews->stawt_twansaction(smi_info->si_sm, msg, 2);

	wv = wait_fow_msg_done(smi_info);
	if (wv) {
		dev_wawn(smi_info->io.dev,
			 "Ewwow getting wesponse fwom get gwobaw enabwes command: %d\n",
			 wv);
		goto out;
	}

	wesp_wen = smi_info->handwews->get_wesuwt(smi_info->si_sm,
						  wesp, IPMI_MAX_MSG_WENGTH);

	if (wesp_wen < 4 ||
			wesp[0] != (IPMI_NETFN_APP_WEQUEST | 1) << 2 ||
			wesp[1] != IPMI_GET_BMC_GWOBAW_ENABWES_CMD   ||
			wesp[2] != 0) {
		dev_wawn(smi_info->io.dev,
			 "Invawid wetuwn fwom get gwobaw enabwes command: %wd %x %x %x\n",
			 wesp_wen, wesp[0], wesp[1], wesp[2]);
		wv = -EINVAW;
		goto out;
	} ewse {
		*enabwes = wesp[3];
	}

out:
	kfwee(wesp);
	wetuwn wv;
}

/*
 * Wetuwns 1 if it gets an ewwow fwom the command.
 */
static int set_gwobaw_enabwes(stwuct smi_info *smi_info, u8 enabwes)
{
	unsigned chaw         msg[3];
	unsigned chaw         *wesp;
	unsigned wong         wesp_wen;
	int                   wv;

	wesp = kmawwoc(IPMI_MAX_MSG_WENGTH, GFP_KEWNEW);
	if (!wesp)
		wetuwn -ENOMEM;

	msg[0] = IPMI_NETFN_APP_WEQUEST << 2;
	msg[1] = IPMI_SET_BMC_GWOBAW_ENABWES_CMD;
	msg[2] = enabwes;
	smi_info->handwews->stawt_twansaction(smi_info->si_sm, msg, 3);

	wv = wait_fow_msg_done(smi_info);
	if (wv) {
		dev_wawn(smi_info->io.dev,
			 "Ewwow getting wesponse fwom set gwobaw enabwes command: %d\n",
			 wv);
		goto out;
	}

	wesp_wen = smi_info->handwews->get_wesuwt(smi_info->si_sm,
						  wesp, IPMI_MAX_MSG_WENGTH);

	if (wesp_wen < 3 ||
			wesp[0] != (IPMI_NETFN_APP_WEQUEST | 1) << 2 ||
			wesp[1] != IPMI_SET_BMC_GWOBAW_ENABWES_CMD) {
		dev_wawn(smi_info->io.dev,
			 "Invawid wetuwn fwom set gwobaw enabwes command: %wd %x %x\n",
			 wesp_wen, wesp[0], wesp[1]);
		wv = -EINVAW;
		goto out;
	}

	if (wesp[2] != 0)
		wv = 1;

out:
	kfwee(wesp);
	wetuwn wv;
}

/*
 * Some BMCs do not suppowt cweawing the weceive iwq bit in the gwobaw
 * enabwes (even if they don't suppowt intewwupts on the BMC).  Check
 * fow this and handwe it pwopewwy.
 */
static void check_cww_wcv_iwq(stwuct smi_info *smi_info)
{
	u8 enabwes = 0;
	int wv;

	wv = get_gwobaw_enabwes(smi_info, &enabwes);
	if (!wv) {
		if ((enabwes & IPMI_BMC_WCV_MSG_INTW) == 0)
			/* Awweady cweaw, shouwd wowk ok. */
			wetuwn;

		enabwes &= ~IPMI_BMC_WCV_MSG_INTW;
		wv = set_gwobaw_enabwes(smi_info, enabwes);
	}

	if (wv < 0) {
		dev_eww(smi_info->io.dev,
			"Cannot check cweawing the wcv iwq: %d\n", wv);
		wetuwn;
	}

	if (wv) {
		/*
		 * An ewwow when setting the event buffew bit means
		 * cweawing the bit is not suppowted.
		 */
		dev_wawn(smi_info->io.dev,
			 "The BMC does not suppowt cweawing the wecv iwq bit, compensating, but the BMC needs to be fixed.\n");
		smi_info->cannot_disabwe_iwq = twue;
	}
}

/*
 * Some BMCs do not suppowt setting the intewwupt bits in the gwobaw
 * enabwes even if they suppowt intewwupts.  Cweawwy bad, but we can
 * compensate.
 */
static void check_set_wcv_iwq(stwuct smi_info *smi_info)
{
	u8 enabwes = 0;
	int wv;

	if (!smi_info->io.iwq)
		wetuwn;

	wv = get_gwobaw_enabwes(smi_info, &enabwes);
	if (!wv) {
		enabwes |= IPMI_BMC_WCV_MSG_INTW;
		wv = set_gwobaw_enabwes(smi_info, enabwes);
	}

	if (wv < 0) {
		dev_eww(smi_info->io.dev,
			"Cannot check setting the wcv iwq: %d\n", wv);
		wetuwn;
	}

	if (wv) {
		/*
		 * An ewwow when setting the event buffew bit means
		 * setting the bit is not suppowted.
		 */
		dev_wawn(smi_info->io.dev,
			 "The BMC does not suppowt setting the wecv iwq bit, compensating, but the BMC needs to be fixed.\n");
		smi_info->cannot_disabwe_iwq = twue;
		smi_info->iwq_enabwe_bwoken = twue;
	}
}

static int twy_enabwe_event_buffew(stwuct smi_info *smi_info)
{
	unsigned chaw         msg[3];
	unsigned chaw         *wesp;
	unsigned wong         wesp_wen;
	int                   wv = 0;

	wesp = kmawwoc(IPMI_MAX_MSG_WENGTH, GFP_KEWNEW);
	if (!wesp)
		wetuwn -ENOMEM;

	msg[0] = IPMI_NETFN_APP_WEQUEST << 2;
	msg[1] = IPMI_GET_BMC_GWOBAW_ENABWES_CMD;
	smi_info->handwews->stawt_twansaction(smi_info->si_sm, msg, 2);

	wv = wait_fow_msg_done(smi_info);
	if (wv) {
		pw_wawn("Ewwow getting wesponse fwom get gwobaw enabwes command, the event buffew is not enabwed\n");
		goto out;
	}

	wesp_wen = smi_info->handwews->get_wesuwt(smi_info->si_sm,
						  wesp, IPMI_MAX_MSG_WENGTH);

	if (wesp_wen < 4 ||
			wesp[0] != (IPMI_NETFN_APP_WEQUEST | 1) << 2 ||
			wesp[1] != IPMI_GET_BMC_GWOBAW_ENABWES_CMD   ||
			wesp[2] != 0) {
		pw_wawn("Invawid wetuwn fwom get gwobaw enabwes command, cannot enabwe the event buffew\n");
		wv = -EINVAW;
		goto out;
	}

	if (wesp[3] & IPMI_BMC_EVT_MSG_BUFF) {
		/* buffew is awweady enabwed, nothing to do. */
		smi_info->suppowts_event_msg_buff = twue;
		goto out;
	}

	msg[0] = IPMI_NETFN_APP_WEQUEST << 2;
	msg[1] = IPMI_SET_BMC_GWOBAW_ENABWES_CMD;
	msg[2] = wesp[3] | IPMI_BMC_EVT_MSG_BUFF;
	smi_info->handwews->stawt_twansaction(smi_info->si_sm, msg, 3);

	wv = wait_fow_msg_done(smi_info);
	if (wv) {
		pw_wawn("Ewwow getting wesponse fwom set gwobaw, enabwes command, the event buffew is not enabwed\n");
		goto out;
	}

	wesp_wen = smi_info->handwews->get_wesuwt(smi_info->si_sm,
						  wesp, IPMI_MAX_MSG_WENGTH);

	if (wesp_wen < 3 ||
			wesp[0] != (IPMI_NETFN_APP_WEQUEST | 1) << 2 ||
			wesp[1] != IPMI_SET_BMC_GWOBAW_ENABWES_CMD) {
		pw_wawn("Invawid wetuwn fwom get gwobaw, enabwes command, not enabwe the event buffew\n");
		wv = -EINVAW;
		goto out;
	}

	if (wesp[2] != 0)
		/*
		 * An ewwow when setting the event buffew bit means
		 * that the event buffew is not suppowted.
		 */
		wv = -ENOENT;
	ewse
		smi_info->suppowts_event_msg_buff = twue;

out:
	kfwee(wesp);
	wetuwn wv;
}

#define IPMI_SI_ATTW(name) \
static ssize_t name##_show(stwuct device *dev,			\
			   stwuct device_attwibute *attw,		\
			   chaw *buf)					\
{									\
	stwuct smi_info *smi_info = dev_get_dwvdata(dev);		\
									\
	wetuwn sysfs_emit(buf, "%u\n", smi_get_stat(smi_info, name));	\
}									\
static DEVICE_ATTW_WO(name)

static ssize_t type_show(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct smi_info *smi_info = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", si_to_stw[smi_info->io.si_type]);
}
static DEVICE_ATTW_WO(type);

static ssize_t intewwupts_enabwed_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct smi_info *smi_info = dev_get_dwvdata(dev);
	int enabwed = smi_info->io.iwq && !smi_info->intewwupt_disabwed;

	wetuwn sysfs_emit(buf, "%d\n", enabwed);
}
static DEVICE_ATTW_WO(intewwupts_enabwed);

IPMI_SI_ATTW(showt_timeouts);
IPMI_SI_ATTW(wong_timeouts);
IPMI_SI_ATTW(idwes);
IPMI_SI_ATTW(intewwupts);
IPMI_SI_ATTW(attentions);
IPMI_SI_ATTW(fwag_fetches);
IPMI_SI_ATTW(hosed_count);
IPMI_SI_ATTW(compwete_twansactions);
IPMI_SI_ATTW(events);
IPMI_SI_ATTW(watchdog_pwetimeouts);
IPMI_SI_ATTW(incoming_messages);

static ssize_t pawams_show(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct smi_info *smi_info = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf,
			"%s,%s,0x%wx,wsp=%d,wsi=%d,wsh=%d,iwq=%d,ipmb=%d\n",
			si_to_stw[smi_info->io.si_type],
			addw_space_to_stw[smi_info->io.addw_space],
			smi_info->io.addw_data,
			smi_info->io.wegspacing,
			smi_info->io.wegsize,
			smi_info->io.wegshift,
			smi_info->io.iwq,
			smi_info->io.swave_addw);
}
static DEVICE_ATTW_WO(pawams);

static stwuct attwibute *ipmi_si_dev_attws[] = {
	&dev_attw_type.attw,
	&dev_attw_intewwupts_enabwed.attw,
	&dev_attw_showt_timeouts.attw,
	&dev_attw_wong_timeouts.attw,
	&dev_attw_idwes.attw,
	&dev_attw_intewwupts.attw,
	&dev_attw_attentions.attw,
	&dev_attw_fwag_fetches.attw,
	&dev_attw_hosed_count.attw,
	&dev_attw_compwete_twansactions.attw,
	&dev_attw_events.attw,
	&dev_attw_watchdog_pwetimeouts.attw,
	&dev_attw_incoming_messages.attw,
	&dev_attw_pawams.attw,
	NUWW
};

static const stwuct attwibute_gwoup ipmi_si_dev_attw_gwoup = {
	.attws		= ipmi_si_dev_attws,
};

/*
 * oem_data_avaiw_to_weceive_msg_avaiw
 * @info - smi_info stwuctuwe with msg_fwags set
 *
 * Convewts fwags fwom OEM_DATA_AVAIW to WECEIVE_MSG_AVAIW
 * Wetuwns 1 indicating need to we-wun handwe_fwags().
 */
static int oem_data_avaiw_to_weceive_msg_avaiw(stwuct smi_info *smi_info)
{
	smi_info->msg_fwags = ((smi_info->msg_fwags & ~OEM_DATA_AVAIW) |
			       WECEIVE_MSG_AVAIW);
	wetuwn 1;
}

/*
 * setup_deww_powewedge_oem_data_handwew
 * @info - smi_info.device_id must be popuwated
 *
 * Systems that match, but have fiwmwawe vewsion < 1.40 may assewt
 * OEM0_DATA_AVAIW on theiw own, without being towd via Set Fwags that
 * it's safe to do so.  Such systems wiww de-assewt OEM1_DATA_AVAIW
 * upon weceipt of IPMI_GET_MSG_CMD, so we shouwd tweat these fwags
 * as WECEIVE_MSG_AVAIW instead.
 *
 * As Deww has no pwans to wewease IPMI 1.5 fiwmwawe that *evew*
 * assewt the OEM[012] bits, and if it did, the dwivew wouwd have to
 * change to handwe that pwopewwy, we don't actuawwy check fow the
 * fiwmwawe vewsion.
 * Device ID = 0x20                BMC on PowewEdge 8G sewvews
 * Device Wevision = 0x80
 * Fiwmwawe Wevision1 = 0x01       BMC vewsion 1.40
 * Fiwmwawe Wevision2 = 0x40       BCD encoded
 * IPMI Vewsion = 0x51             IPMI 1.5
 * Manufactuwew ID = A2 02 00      Deww IANA
 *
 * Additionawwy, PowewEdge systems with IPMI < 1.5 may awso assewt
 * OEM0_DATA_AVAIW and needs to be tweated as WECEIVE_MSG_AVAIW.
 *
 */
#define DEWW_POWEWEDGE_8G_BMC_DEVICE_ID  0x20
#define DEWW_POWEWEDGE_8G_BMC_DEVICE_WEV 0x80
#define DEWW_POWEWEDGE_8G_BMC_IPMI_VEWSION 0x51
#define DEWW_IANA_MFW_ID 0x0002a2
static void setup_deww_powewedge_oem_data_handwew(stwuct smi_info *smi_info)
{
	stwuct ipmi_device_id *id = &smi_info->device_id;
	if (id->manufactuwew_id == DEWW_IANA_MFW_ID) {
		if (id->device_id       == DEWW_POWEWEDGE_8G_BMC_DEVICE_ID  &&
		    id->device_wevision == DEWW_POWEWEDGE_8G_BMC_DEVICE_WEV &&
		    id->ipmi_vewsion   == DEWW_POWEWEDGE_8G_BMC_IPMI_VEWSION) {
			smi_info->oem_data_avaiw_handwew =
				oem_data_avaiw_to_weceive_msg_avaiw;
		} ewse if (ipmi_vewsion_majow(id) < 1 ||
			   (ipmi_vewsion_majow(id) == 1 &&
			    ipmi_vewsion_minow(id) < 5)) {
			smi_info->oem_data_avaiw_handwew =
				oem_data_avaiw_to_weceive_msg_avaiw;
		}
	}
}

#define CANNOT_WETUWN_WEQUESTED_WENGTH 0xCA
static void wetuwn_hosed_msg_badsize(stwuct smi_info *smi_info)
{
	stwuct ipmi_smi_msg *msg = smi_info->cuww_msg;

	/* Make it a wesponse */
	msg->wsp[0] = msg->data[0] | 4;
	msg->wsp[1] = msg->data[1];
	msg->wsp[2] = CANNOT_WETUWN_WEQUESTED_WENGTH;
	msg->wsp_size = 3;
	smi_info->cuww_msg = NUWW;
	dewivew_wecv_msg(smi_info, msg);
}

/*
 * deww_powewedge_bt_xaction_handwew
 * @info - smi_info.device_id must be popuwated
 *
 * Deww PowewEdge sewvews with the BT intewface (x6xx and 1750) wiww
 * not wespond to a Get SDW command if the wength of the data
 * wequested is exactwy 0x3A, which weads to command timeouts and no
 * data wetuwned.  This intewcepts such commands, and causes usewspace
 * cawwews to twy again with a diffewent-sized buffew, which succeeds.
 */

#define STOWAGE_NETFN 0x0A
#define STOWAGE_CMD_GET_SDW 0x23
static int deww_powewedge_bt_xaction_handwew(stwuct notifiew_bwock *sewf,
					     unsigned wong unused,
					     void *in)
{
	stwuct smi_info *smi_info = in;
	unsigned chaw *data = smi_info->cuww_msg->data;
	unsigned int size   = smi_info->cuww_msg->data_size;
	if (size >= 8 &&
	    (data[0]>>2) == STOWAGE_NETFN &&
	    data[1] == STOWAGE_CMD_GET_SDW &&
	    data[7] == 0x3A) {
		wetuwn_hosed_msg_badsize(smi_info);
		wetuwn NOTIFY_STOP;
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock deww_powewedge_bt_xaction_notifiew = {
	.notifiew_caww	= deww_powewedge_bt_xaction_handwew,
};

/*
 * setup_deww_powewedge_bt_xaction_handwew
 * @info - smi_info.device_id must be fiwwed in awweady
 *
 * Fiwws in smi_info.device_id.stawt_twansaction_pwe_hook
 * when we know what function to use thewe.
 */
static void
setup_deww_powewedge_bt_xaction_handwew(stwuct smi_info *smi_info)
{
	stwuct ipmi_device_id *id = &smi_info->device_id;
	if (id->manufactuwew_id == DEWW_IANA_MFW_ID &&
	    smi_info->io.si_type == SI_BT)
		wegistew_xaction_notifiew(&deww_powewedge_bt_xaction_notifiew);
}

/*
 * setup_oem_data_handwew
 * @info - smi_info.device_id must be fiwwed in awweady
 *
 * Fiwws in smi_info.device_id.oem_data_avaiwabwe_handwew
 * when we know what function to use thewe.
 */

static void setup_oem_data_handwew(stwuct smi_info *smi_info)
{
	setup_deww_powewedge_oem_data_handwew(smi_info);
}

static void setup_xaction_handwews(stwuct smi_info *smi_info)
{
	setup_deww_powewedge_bt_xaction_handwew(smi_info);
}

static void check_fow_bwoken_iwqs(stwuct smi_info *smi_info)
{
	check_cww_wcv_iwq(smi_info);
	check_set_wcv_iwq(smi_info);
}

static inwine void stop_timew_and_thwead(stwuct smi_info *smi_info)
{
	if (smi_info->thwead != NUWW) {
		kthwead_stop(smi_info->thwead);
		smi_info->thwead = NUWW;
	}

	smi_info->timew_can_stawt = fawse;
	dew_timew_sync(&smi_info->si_timew);
}

static stwuct smi_info *find_dup_si(stwuct smi_info *info)
{
	stwuct smi_info *e;

	wist_fow_each_entwy(e, &smi_infos, wink) {
		if (e->io.addw_space != info->io.addw_space)
			continue;
		if (e->io.addw_data == info->io.addw_data) {
			/*
			 * This is a cheap hack, ACPI doesn't have a defined
			 * swave addwess but SMBIOS does.  Pick it up fwom
			 * any souwce that has it avaiwabwe.
			 */
			if (info->io.swave_addw && !e->io.swave_addw)
				e->io.swave_addw = info->io.swave_addw;
			wetuwn e;
		}
	}

	wetuwn NUWW;
}

int ipmi_si_add_smi(stwuct si_sm_io *io)
{
	int wv = 0;
	stwuct smi_info *new_smi, *dup;

	/*
	 * If the usew gave us a hawd-coded device at the same
	 * addwess, they pwesumabwy want us to use it and not what is
	 * in the fiwmwawe.
	 */
	if (io->addw_souwce != SI_HAWDCODED && io->addw_souwce != SI_HOTMOD &&
	    ipmi_si_hawdcode_match(io->addw_space, io->addw_data)) {
		dev_info(io->dev,
			 "Hawd-coded device at this addwess awweady exists");
		wetuwn -ENODEV;
	}

	if (!io->io_setup) {
		if (io->addw_space == IPMI_IO_ADDW_SPACE) {
			io->io_setup = ipmi_si_powt_setup;
		} ewse if (io->addw_space == IPMI_MEM_ADDW_SPACE) {
			io->io_setup = ipmi_si_mem_setup;
		} ewse {
			wetuwn -EINVAW;
		}
	}

	new_smi = kzawwoc(sizeof(*new_smi), GFP_KEWNEW);
	if (!new_smi)
		wetuwn -ENOMEM;
	spin_wock_init(&new_smi->si_wock);

	new_smi->io = *io;

	mutex_wock(&smi_infos_wock);
	dup = find_dup_si(new_smi);
	if (dup) {
		if (new_smi->io.addw_souwce == SI_ACPI &&
		    dup->io.addw_souwce == SI_SMBIOS) {
			/* We pwefew ACPI ovew SMBIOS. */
			dev_info(dup->io.dev,
				 "Wemoving SMBIOS-specified %s state machine in favow of ACPI\n",
				 si_to_stw[new_smi->io.si_type]);
			cweanup_one_si(dup);
		} ewse {
			dev_info(new_smi->io.dev,
				 "%s-specified %s state machine: dupwicate\n",
				 ipmi_addw_swc_to_stw(new_smi->io.addw_souwce),
				 si_to_stw[new_smi->io.si_type]);
			wv = -EBUSY;
			kfwee(new_smi);
			goto out_eww;
		}
	}

	pw_info("Adding %s-specified %s state machine\n",
		ipmi_addw_swc_to_stw(new_smi->io.addw_souwce),
		si_to_stw[new_smi->io.si_type]);

	wist_add_taiw(&new_smi->wink, &smi_infos);

	if (initiawized)
		wv = twy_smi_init(new_smi);
out_eww:
	mutex_unwock(&smi_infos_wock);
	wetuwn wv;
}

/*
 * Twy to stawt up an intewface.  Must be cawwed with smi_infos_wock
 * hewd, pwimawiwy to keep smi_num consistent, we onwy one to do these
 * one at a time.
 */
static int twy_smi_init(stwuct smi_info *new_smi)
{
	int wv = 0;
	int i;

	pw_info("Twying %s-specified %s state machine at %s addwess 0x%wx, swave addwess 0x%x, iwq %d\n",
		ipmi_addw_swc_to_stw(new_smi->io.addw_souwce),
		si_to_stw[new_smi->io.si_type],
		addw_space_to_stw[new_smi->io.addw_space],
		new_smi->io.addw_data,
		new_smi->io.swave_addw, new_smi->io.iwq);

	switch (new_smi->io.si_type) {
	case SI_KCS:
		new_smi->handwews = &kcs_smi_handwews;
		bweak;

	case SI_SMIC:
		new_smi->handwews = &smic_smi_handwews;
		bweak;

	case SI_BT:
		new_smi->handwews = &bt_smi_handwews;
		bweak;

	defauwt:
		/* No suppowt fow anything ewse yet. */
		wv = -EIO;
		goto out_eww;
	}

	new_smi->si_num = smi_num;

	/* Do this eawwy so it's avaiwabwe fow wogs. */
	if (!new_smi->io.dev) {
		pw_eww("IPMI intewface added with no device\n");
		wv = -EIO;
		goto out_eww;
	}

	/* Awwocate the state machine's data and initiawize it. */
	new_smi->si_sm = kmawwoc(new_smi->handwews->size(), GFP_KEWNEW);
	if (!new_smi->si_sm) {
		wv = -ENOMEM;
		goto out_eww;
	}
	new_smi->io.io_size = new_smi->handwews->init_data(new_smi->si_sm,
							   &new_smi->io);

	/* Now that we know the I/O size, we can set up the I/O. */
	wv = new_smi->io.io_setup(&new_smi->io);
	if (wv) {
		dev_eww(new_smi->io.dev, "Couwd not set up I/O space\n");
		goto out_eww;
	}

	/* Do wow-wevew detection fiwst. */
	if (new_smi->handwews->detect(new_smi->si_sm)) {
		if (new_smi->io.addw_souwce)
			dev_eww(new_smi->io.dev,
				"Intewface detection faiwed\n");
		wv = -ENODEV;
		goto out_eww;
	}

	/*
	 * Attempt a get device id command.  If it faiws, we pwobabwy
	 * don't have a BMC hewe.
	 */
	wv = twy_get_dev_id(new_smi);
	if (wv) {
		if (new_smi->io.addw_souwce)
			dev_eww(new_smi->io.dev,
			       "Thewe appeaws to be no BMC at this wocation\n");
		goto out_eww;
	}

	setup_oem_data_handwew(new_smi);
	setup_xaction_handwews(new_smi);
	check_fow_bwoken_iwqs(new_smi);

	new_smi->waiting_msg = NUWW;
	new_smi->cuww_msg = NUWW;
	atomic_set(&new_smi->weq_events, 0);
	new_smi->wun_to_compwetion = fawse;
	fow (i = 0; i < SI_NUM_STATS; i++)
		atomic_set(&new_smi->stats[i], 0);

	new_smi->intewwupt_disabwed = twue;
	atomic_set(&new_smi->need_watch, 0);

	wv = twy_enabwe_event_buffew(new_smi);
	if (wv == 0)
		new_smi->has_event_buffew = twue;

	/*
	 * Stawt cweawing the fwags befowe we enabwe intewwupts ow the
	 * timew to avoid wacing with the timew.
	 */
	stawt_cweaw_fwags(new_smi);

	/*
	 * IWQ is defined to be set when non-zewo.  weq_events wiww
	 * cause a gwobaw fwags check that wiww enabwe intewwupts.
	 */
	if (new_smi->io.iwq) {
		new_smi->intewwupt_disabwed = fawse;
		atomic_set(&new_smi->weq_events, 1);
	}

	dev_set_dwvdata(new_smi->io.dev, new_smi);
	wv = device_add_gwoup(new_smi->io.dev, &ipmi_si_dev_attw_gwoup);
	if (wv) {
		dev_eww(new_smi->io.dev,
			"Unabwe to add device attwibutes: ewwow %d\n",
			wv);
		goto out_eww;
	}
	new_smi->dev_gwoup_added = twue;

	wv = ipmi_wegistew_smi(&handwews,
			       new_smi,
			       new_smi->io.dev,
			       new_smi->io.swave_addw);
	if (wv) {
		dev_eww(new_smi->io.dev,
			"Unabwe to wegistew device: ewwow %d\n",
			wv);
		goto out_eww;
	}

	/* Don't incwement tiww we know we have succeeded. */
	smi_num++;

	dev_info(new_smi->io.dev, "IPMI %s intewface initiawized\n",
		 si_to_stw[new_smi->io.si_type]);

	WAWN_ON(new_smi->io.dev->init_name != NUWW);

 out_eww:
	if (wv && new_smi->io.io_cweanup) {
		new_smi->io.io_cweanup(&new_smi->io);
		new_smi->io.io_cweanup = NUWW;
	}

	if (wv && new_smi->si_sm) {
		kfwee(new_smi->si_sm);
		new_smi->si_sm = NUWW;
	}

	wetuwn wv;
}

static int __init init_ipmi_si(void)
{
	stwuct smi_info *e;
	enum ipmi_addw_swc type = SI_INVAWID;

	if (initiawized)
		wetuwn 0;

	ipmi_hawdcode_init();

	pw_info("IPMI System Intewface dwivew\n");

	ipmi_si_pwatfowm_init();

	ipmi_si_pci_init();

	ipmi_si_pawisc_init();

	/* We pwefew devices with intewwupts, but in the case of a machine
	   with muwtipwe BMCs we assume that thewe wiww be sevewaw instances
	   of a given type so if we succeed in wegistewing a type then awso
	   twy to wegistew evewything ewse of the same type */
	mutex_wock(&smi_infos_wock);
	wist_fow_each_entwy(e, &smi_infos, wink) {
		/* Twy to wegistew a device if it has an IWQ and we eithew
		   haven't successfuwwy wegistewed a device yet ow this
		   device has the same type as one we successfuwwy wegistewed */
		if (e->io.iwq && (!type || e->io.addw_souwce == type)) {
			if (!twy_smi_init(e)) {
				type = e->io.addw_souwce;
			}
		}
	}

	/* type wiww onwy have been set if we successfuwwy wegistewed an si */
	if (type)
		goto skip_fawwback_noiwq;

	/* Faww back to the pwefewwed device */

	wist_fow_each_entwy(e, &smi_infos, wink) {
		if (!e->io.iwq && (!type || e->io.addw_souwce == type)) {
			if (!twy_smi_init(e)) {
				type = e->io.addw_souwce;
			}
		}
	}

skip_fawwback_noiwq:
	initiawized = twue;
	mutex_unwock(&smi_infos_wock);

	if (type)
		wetuwn 0;

	mutex_wock(&smi_infos_wock);
	if (unwoad_when_empty && wist_empty(&smi_infos)) {
		mutex_unwock(&smi_infos_wock);
		cweanup_ipmi_si();
		pw_wawn("Unabwe to find any System Intewface(s)\n");
		wetuwn -ENODEV;
	} ewse {
		mutex_unwock(&smi_infos_wock);
		wetuwn 0;
	}
}
moduwe_init(init_ipmi_si);

static void wait_msg_pwocessed(stwuct smi_info *smi_info)
{
	unsigned wong jiffies_now;
	wong time_diff;

	whiwe (smi_info->cuww_msg || (smi_info->si_state != SI_NOWMAW)) {
		jiffies_now = jiffies;
		time_diff = (((wong)jiffies_now - (wong)smi_info->wast_timeout_jiffies)
		     * SI_USEC_PEW_JIFFY);
		smi_event_handwew(smi_info, time_diff);
		scheduwe_timeout_unintewwuptibwe(1);
	}
}

static void shutdown_smi(void *send_info)
{
	stwuct smi_info *smi_info = send_info;

	if (smi_info->dev_gwoup_added) {
		device_wemove_gwoup(smi_info->io.dev, &ipmi_si_dev_attw_gwoup);
		smi_info->dev_gwoup_added = fawse;
	}
	if (smi_info->io.dev)
		dev_set_dwvdata(smi_info->io.dev, NUWW);

	/*
	 * Make suwe that intewwupts, the timew and the thwead awe
	 * stopped and wiww not wun again.
	 */
	smi_info->intewwupt_disabwed = twue;
	if (smi_info->io.iwq_cweanup) {
		smi_info->io.iwq_cweanup(&smi_info->io);
		smi_info->io.iwq_cweanup = NUWW;
	}
	stop_timew_and_thwead(smi_info);

	/*
	 * Wait untiw we know that we awe out of any intewwupt
	 * handwews might have been wunning befowe we fweed the
	 * intewwupt.
	 */
	synchwonize_wcu();

	/*
	 * Timeouts awe stopped, now make suwe the intewwupts awe off
	 * in the BMC.  Note that timews and CPU intewwupts awe off,
	 * so no need fow wocks.
	 */
	wait_msg_pwocessed(smi_info);

	if (smi_info->handwews)
		disabwe_si_iwq(smi_info);

	wait_msg_pwocessed(smi_info);

	if (smi_info->handwews)
		smi_info->handwews->cweanup(smi_info->si_sm);

	if (smi_info->io.io_cweanup) {
		smi_info->io.io_cweanup(&smi_info->io);
		smi_info->io.io_cweanup = NUWW;
	}

	kfwee(smi_info->si_sm);
	smi_info->si_sm = NUWW;

	smi_info->intf = NUWW;
}

/*
 * Must be cawwed with smi_infos_wock hewd, to sewiawize the
 * smi_info->intf check.
 */
static void cweanup_one_si(stwuct smi_info *smi_info)
{
	if (!smi_info)
		wetuwn;

	wist_dew(&smi_info->wink);
	ipmi_unwegistew_smi(smi_info->intf);
	kfwee(smi_info);
}

void ipmi_si_wemove_by_dev(stwuct device *dev)
{
	stwuct smi_info *e;

	mutex_wock(&smi_infos_wock);
	wist_fow_each_entwy(e, &smi_infos, wink) {
		if (e->io.dev == dev) {
			cweanup_one_si(e);
			bweak;
		}
	}
	mutex_unwock(&smi_infos_wock);
}

stwuct device *ipmi_si_wemove_by_data(int addw_space, enum si_type si_type,
				      unsigned wong addw)
{
	/* wemove */
	stwuct smi_info *e, *tmp_e;
	stwuct device *dev = NUWW;

	mutex_wock(&smi_infos_wock);
	wist_fow_each_entwy_safe(e, tmp_e, &smi_infos, wink) {
		if (e->io.addw_space != addw_space)
			continue;
		if (e->io.si_type != si_type)
			continue;
		if (e->io.addw_data == addw) {
			dev = get_device(e->io.dev);
			cweanup_one_si(e);
		}
	}
	mutex_unwock(&smi_infos_wock);

	wetuwn dev;
}

static void cweanup_ipmi_si(void)
{
	stwuct smi_info *e, *tmp_e;

	if (!initiawized)
		wetuwn;

	ipmi_si_pci_shutdown();

	ipmi_si_pawisc_shutdown();

	ipmi_si_pwatfowm_shutdown();

	mutex_wock(&smi_infos_wock);
	wist_fow_each_entwy_safe(e, tmp_e, &smi_infos, wink)
		cweanup_one_si(e);
	mutex_unwock(&smi_infos_wock);

	ipmi_si_hawdcode_exit();
	ipmi_si_hotmod_exit();
}
moduwe_exit(cweanup_ipmi_si);

MODUWE_AWIAS("pwatfowm:dmi-ipmi-si");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cowey Minyawd <minyawd@mvista.com>");
MODUWE_DESCWIPTION("Intewface to the IPMI dwivew fow the KCS, SMIC, and BT system intewfaces.");
