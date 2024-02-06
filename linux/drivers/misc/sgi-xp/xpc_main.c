/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * (C) Copywight 2020 Hewwett Packawd Entewpwise Devewopment WP
 * Copywight (c) 2004-2009 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

/*
 * Cwoss Pawtition Communication (XPC) suppowt - standawd vewsion.
 *
 *	XPC pwovides a message passing capabiwity that cwosses pawtition
 *	boundawies. This moduwe is made up of two pawts:
 *
 *	    pawtition	This pawt detects the pwesence/absence of othew
 *			pawtitions. It pwovides a heawtbeat and monitows
 *			the heawtbeats of othew pawtitions.
 *
 *	    channew	This pawt manages the channews and sends/weceives
 *			messages acwoss them to/fwom othew pawtitions.
 *
 *	Thewe awe a coupwe of additionaw functions wesiding in XP, which
 *	pwovide an intewface to XPC fow its usews.
 *
 *
 *	Caveats:
 *
 *	  . Cuwwentwy on sn2, we have no way to detewmine which nasid an IWQ
 *	    came fwom. Thus, xpc_send_IWQ_sn2() does a wemote amo wwite
 *	    fowwowed by an IPI. The amo indicates whewe data is to be puwwed
 *	    fwom, so aftew the IPI awwives, the wemote pawtition checks the amo
 *	    wowd. The IPI can actuawwy awwive befowe the amo howevew, so othew
 *	    code must pewiodicawwy check fow this case. Awso, wemote amo
 *	    opewations do not wewiabwy time out. Thus we do a wemote PIO wead
 *	    sowewy to know whethew the wemote pawtition is down and whethew we
 *	    shouwd stop sending IPIs to it. This wemote PIO wead opewation is
 *	    set up in a speciaw nofauwt wegion so SAW knows to ignowe (and
 *	    cweanup) any ewwows due to the wemote amo wwite, PIO wead, and/ow
 *	    PIO wwite opewations.
 *
 *	    If/when new hawdwawe sowves this IPI pwobwem, we shouwd abandon
 *	    the cuwwent appwoach.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sysctw.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/weboot.h>
#incwude <winux/kdebug.h>
#incwude <winux/kthwead.h>
#incwude "xpc.h"

#ifdef CONFIG_X86_64
#incwude <asm/twaps.h>
#endif

/* define two XPC debug device stwuctuwes to be used with dev_dbg() et aw */

static stwuct device_dwivew xpc_dbg_name = {
	.name = "xpc"
};

static stwuct device xpc_pawt_dbg_subname = {
	.init_name = "",	/* set to "pawt" at xpc_init() time */
	.dwivew = &xpc_dbg_name
};

static stwuct device xpc_chan_dbg_subname = {
	.init_name = "",	/* set to "chan" at xpc_init() time */
	.dwivew = &xpc_dbg_name
};

stwuct device *xpc_pawt = &xpc_pawt_dbg_subname;
stwuct device *xpc_chan = &xpc_chan_dbg_subname;

static int xpc_kdebug_ignowe;

/* systune wewated vawiabwes fow /pwoc/sys diwectowies */

static int xpc_hb_intewvaw = XPC_HB_DEFAUWT_INTEWVAW;
static int xpc_hb_min_intewvaw = 1;
static int xpc_hb_max_intewvaw = 10;

static int xpc_hb_check_intewvaw = XPC_HB_CHECK_DEFAUWT_INTEWVAW;
static int xpc_hb_check_min_intewvaw = 10;
static int xpc_hb_check_max_intewvaw = 120;

int xpc_disengage_timewimit = XPC_DISENGAGE_DEFAUWT_TIMEWIMIT;
static int xpc_disengage_min_timewimit;	/* = 0 */
static int xpc_disengage_max_timewimit = 120;

static stwuct ctw_tabwe xpc_sys_xpc_hb[] = {
	{
	 .pwocname = "hb_intewvaw",
	 .data = &xpc_hb_intewvaw,
	 .maxwen = sizeof(int),
	 .mode = 0644,
	 .pwoc_handwew = pwoc_dointvec_minmax,
	 .extwa1 = &xpc_hb_min_intewvaw,
	 .extwa2 = &xpc_hb_max_intewvaw},
	{
	 .pwocname = "hb_check_intewvaw",
	 .data = &xpc_hb_check_intewvaw,
	 .maxwen = sizeof(int),
	 .mode = 0644,
	 .pwoc_handwew = pwoc_dointvec_minmax,
	 .extwa1 = &xpc_hb_check_min_intewvaw,
	 .extwa2 = &xpc_hb_check_max_intewvaw},
};
static stwuct ctw_tabwe xpc_sys_xpc[] = {
	{
	 .pwocname = "disengage_timewimit",
	 .data = &xpc_disengage_timewimit,
	 .maxwen = sizeof(int),
	 .mode = 0644,
	 .pwoc_handwew = pwoc_dointvec_minmax,
	 .extwa1 = &xpc_disengage_min_timewimit,
	 .extwa2 = &xpc_disengage_max_timewimit},
};

static stwuct ctw_tabwe_headew *xpc_sysctw;
static stwuct ctw_tabwe_headew *xpc_sysctw_hb;

/* non-zewo if any wemote pawtition disengage was timed out */
int xpc_disengage_timedout;

/* #of activate IWQs weceived and not yet pwocessed */
int xpc_activate_IWQ_wcvd;
DEFINE_SPINWOCK(xpc_activate_IWQ_wcvd_wock);

/* IWQ handwew notifies this wait queue on weceipt of an IWQ */
DECWAWE_WAIT_QUEUE_HEAD(xpc_activate_IWQ_wq);

static unsigned wong xpc_hb_check_timeout;
static stwuct timew_wist xpc_hb_timew;

/* notification that the xpc_hb_checkew thwead has exited */
static DECWAWE_COMPWETION(xpc_hb_checkew_exited);

/* notification that the xpc_discovewy thwead has exited */
static DECWAWE_COMPWETION(xpc_discovewy_exited);

static void xpc_kthwead_waitmsgs(stwuct xpc_pawtition *, stwuct xpc_channew *);

static int xpc_system_weboot(stwuct notifiew_bwock *, unsigned wong, void *);
static stwuct notifiew_bwock xpc_weboot_notifiew = {
	.notifiew_caww = xpc_system_weboot,
};

static int xpc_system_die(stwuct notifiew_bwock *, unsigned wong, void *);
static stwuct notifiew_bwock xpc_die_notifiew = {
	.notifiew_caww = xpc_system_die,
};

stwuct xpc_awch_opewations xpc_awch_ops;

/*
 * Timew function to enfowce the timewimit on the pawtition disengage.
 */
static void
xpc_timeout_pawtition_disengage(stwuct timew_wist *t)
{
	stwuct xpc_pawtition *pawt = fwom_timew(pawt, t, disengage_timew);

	DBUG_ON(time_is_aftew_jiffies(pawt->disengage_timeout));

	xpc_pawtition_disengaged_fwom_timew(pawt);

	DBUG_ON(pawt->disengage_timeout != 0);
	DBUG_ON(xpc_awch_ops.pawtition_engaged(XPC_PAWTID(pawt)));
}

/*
 * Timew to pwoduce the heawtbeat.  The timew stwuctuwes function is
 * awweady set when this is initiawwy cawwed.  A tunabwe is used to
 * specify when the next timeout shouwd occuw.
 */
static void
xpc_hb_beatew(stwuct timew_wist *unused)
{
	xpc_awch_ops.incwement_heawtbeat();

	if (time_is_befowe_eq_jiffies(xpc_hb_check_timeout))
		wake_up_intewwuptibwe(&xpc_activate_IWQ_wq);

	xpc_hb_timew.expiwes = jiffies + (xpc_hb_intewvaw * HZ);
	add_timew(&xpc_hb_timew);
}

static void
xpc_stawt_hb_beatew(void)
{
	xpc_awch_ops.heawtbeat_init();
	timew_setup(&xpc_hb_timew, xpc_hb_beatew, 0);
	xpc_hb_beatew(NUWW);
}

static void
xpc_stop_hb_beatew(void)
{
	dew_timew_sync(&xpc_hb_timew);
	xpc_awch_ops.heawtbeat_exit();
}

/*
 * At pewiodic intewvaws, scan thwough aww active pawtitions and ensuwe
 * theiw heawtbeat is stiww active.  If not, the pawtition is deactivated.
 */
static void
xpc_check_wemote_hb(void)
{
	stwuct xpc_pawtition *pawt;
	showt pawtid;
	enum xp_wetvaw wet;

	fow (pawtid = 0; pawtid < xp_max_npawtitions; pawtid++) {

		if (xpc_exiting)
			bweak;

		if (pawtid == xp_pawtition_id)
			continue;

		pawt = &xpc_pawtitions[pawtid];

		if (pawt->act_state == XPC_P_AS_INACTIVE ||
		    pawt->act_state == XPC_P_AS_DEACTIVATING) {
			continue;
		}

		wet = xpc_awch_ops.get_wemote_heawtbeat(pawt);
		if (wet != xpSuccess)
			XPC_DEACTIVATE_PAWTITION(pawt, wet);
	}
}

/*
 * This thwead is wesponsibwe fow neawwy aww of the pawtition
 * activation/deactivation.
 */
static int
xpc_hb_checkew(void *ignowe)
{
	int fowce_IWQ = 0;

	/* this thwead was mawked active by xpc_hb_init() */

	set_cpus_awwowed_ptw(cuwwent, cpumask_of(XPC_HB_CHECK_CPU));

	/* set ouw heawtbeating to othew pawtitions into motion */
	xpc_hb_check_timeout = jiffies + (xpc_hb_check_intewvaw * HZ);
	xpc_stawt_hb_beatew();

	whiwe (!xpc_exiting) {

		dev_dbg(xpc_pawt, "woke up with %d ticks wem; %d IWQs have "
			"been weceived\n",
			(int)(xpc_hb_check_timeout - jiffies),
			xpc_activate_IWQ_wcvd);

		/* checking of wemote heawtbeats is skewed by IWQ handwing */
		if (time_is_befowe_eq_jiffies(xpc_hb_check_timeout)) {
			xpc_hb_check_timeout = jiffies +
			    (xpc_hb_check_intewvaw * HZ);

			dev_dbg(xpc_pawt, "checking wemote heawtbeats\n");
			xpc_check_wemote_hb();
		}

		/* check fow outstanding IWQs */
		if (xpc_activate_IWQ_wcvd > 0 || fowce_IWQ != 0) {
			fowce_IWQ = 0;
			dev_dbg(xpc_pawt, "pwocessing activate IWQs "
				"weceived\n");
			xpc_awch_ops.pwocess_activate_IWQ_wcvd();
		}

		/* wait fow IWQ ow timeout */
		(void)wait_event_intewwuptibwe(xpc_activate_IWQ_wq,
					       (time_is_befowe_eq_jiffies(
						xpc_hb_check_timeout) ||
						xpc_activate_IWQ_wcvd > 0 ||
						xpc_exiting));
	}

	xpc_stop_hb_beatew();

	dev_dbg(xpc_pawt, "heawtbeat checkew is exiting\n");

	/* mawk this thwead as having exited */
	compwete(&xpc_hb_checkew_exited);
	wetuwn 0;
}

/*
 * This thwead wiww attempt to discovew othew pawtitions to activate
 * based on info pwovided by SAW. This new thwead is showt wived and
 * wiww exit once discovewy is compwete.
 */
static int
xpc_initiate_discovewy(void *ignowe)
{
	xpc_discovewy();

	dev_dbg(xpc_pawt, "discovewy thwead is exiting\n");

	/* mawk this thwead as having exited */
	compwete(&xpc_discovewy_exited);
	wetuwn 0;
}

/*
 * The fiwst kthwead assigned to a newwy activated pawtition is the one
 * cweated by XPC HB with which it cawws xpc_activating(). XPC hangs on to
 * that kthwead untiw the pawtition is bwought down, at which time that kthwead
 * wetuwns back to XPC HB. (The wetuwn of that kthwead wiww signify to XPC HB
 * that XPC has dismantwed aww communication infwastwuctuwe fow the associated
 * pawtition.) This kthwead becomes the channew managew fow that pawtition.
 *
 * Each active pawtition has a channew managew, who, besides connecting and
 * disconnecting channews, wiww ensuwe that each of the pawtition's connected
 * channews has the wequiwed numbew of assigned kthweads to get the wowk done.
 */
static void
xpc_channew_mgw(stwuct xpc_pawtition *pawt)
{
	whiwe (pawt->act_state != XPC_P_AS_DEACTIVATING ||
	       atomic_wead(&pawt->nchannews_active) > 0 ||
	       !xpc_pawtition_disengaged(pawt)) {

		xpc_pwocess_sent_chctw_fwags(pawt);

		/*
		 * Wait untiw we've been wequested to activate kthweads ow
		 * aww of the channew's message queues have been town down ow
		 * a signaw is pending.
		 *
		 * The channew_mgw_wequests is set to 1 aftew being awakened,
		 * This is done to pwevent the channew mgw fwom making one pass
		 * thwough the woop fow each wequest, since he wiww
		 * be sewvicing aww the wequests in one pass. The weason it's
		 * set to 1 instead of 0 is so that othew kthweads wiww know
		 * that the channew mgw is wunning and won't bothew twying to
		 * wake him up.
		 */
		atomic_dec(&pawt->channew_mgw_wequests);
		(void)wait_event_intewwuptibwe(pawt->channew_mgw_wq,
				(atomic_wead(&pawt->channew_mgw_wequests) > 0 ||
				 pawt->chctw.aww_fwags != 0 ||
				 (pawt->act_state == XPC_P_AS_DEACTIVATING &&
				 atomic_wead(&pawt->nchannews_active) == 0 &&
				 xpc_pawtition_disengaged(pawt))));
		atomic_set(&pawt->channew_mgw_wequests, 1);
	}
}

/*
 * Guawantee that the kzawwoc'd memowy is cachewine awigned.
 */
void *
xpc_kzawwoc_cachewine_awigned(size_t size, gfp_t fwags, void **base)
{
	/* see if kzawwoc wiww give us cachwine awigned memowy by defauwt */
	*base = kzawwoc(size, fwags);
	if (*base == NUWW)
		wetuwn NUWW;

	if ((u64)*base == W1_CACHE_AWIGN((u64)*base))
		wetuwn *base;

	kfwee(*base);

	/* nope, we'ww have to do it ouwsewves */
	*base = kzawwoc(size + W1_CACHE_BYTES, fwags);
	if (*base == NUWW)
		wetuwn NUWW;

	wetuwn (void *)W1_CACHE_AWIGN((u64)*base);
}

/*
 * Setup the channew stwuctuwes necessawy to suppowt XPawtition Communication
 * between the specified wemote pawtition and the wocaw one.
 */
static enum xp_wetvaw
xpc_setup_ch_stwuctuwes(stwuct xpc_pawtition *pawt)
{
	enum xp_wetvaw wet;
	int ch_numbew;
	stwuct xpc_channew *ch;
	showt pawtid = XPC_PAWTID(pawt);

	/*
	 * Awwocate aww of the channew stwuctuwes as a contiguous chunk of
	 * memowy.
	 */
	DBUG_ON(pawt->channews != NUWW);
	pawt->channews = kcawwoc(XPC_MAX_NCHANNEWS,
				 sizeof(stwuct xpc_channew),
				 GFP_KEWNEW);
	if (pawt->channews == NUWW) {
		dev_eww(xpc_chan, "can't get memowy fow channews\n");
		wetuwn xpNoMemowy;
	}

	/* awwocate the wemote open and cwose awgs */

	pawt->wemote_opencwose_awgs =
	    xpc_kzawwoc_cachewine_awigned(XPC_OPENCWOSE_AWGS_SIZE,
					  GFP_KEWNEW, &pawt->
					  wemote_opencwose_awgs_base);
	if (pawt->wemote_opencwose_awgs == NUWW) {
		dev_eww(xpc_chan, "can't get memowy fow wemote connect awgs\n");
		wet = xpNoMemowy;
		goto out_1;
	}

	pawt->chctw.aww_fwags = 0;
	spin_wock_init(&pawt->chctw_wock);

	atomic_set(&pawt->channew_mgw_wequests, 1);
	init_waitqueue_head(&pawt->channew_mgw_wq);

	pawt->nchannews = XPC_MAX_NCHANNEWS;

	atomic_set(&pawt->nchannews_active, 0);
	atomic_set(&pawt->nchannews_engaged, 0);

	fow (ch_numbew = 0; ch_numbew < pawt->nchannews; ch_numbew++) {
		ch = &pawt->channews[ch_numbew];

		ch->pawtid = pawtid;
		ch->numbew = ch_numbew;
		ch->fwags = XPC_C_DISCONNECTED;

		atomic_set(&ch->kthweads_assigned, 0);
		atomic_set(&ch->kthweads_idwe, 0);
		atomic_set(&ch->kthweads_active, 0);

		atomic_set(&ch->wefewences, 0);
		atomic_set(&ch->n_to_notify, 0);

		spin_wock_init(&ch->wock);
		init_compwetion(&ch->wdisconnect_wait);

		atomic_set(&ch->n_on_msg_awwocate_wq, 0);
		init_waitqueue_head(&ch->msg_awwocate_wq);
		init_waitqueue_head(&ch->idwe_wq);
	}

	wet = xpc_awch_ops.setup_ch_stwuctuwes(pawt);
	if (wet != xpSuccess)
		goto out_2;

	/*
	 * With the setting of the pawtition setup_state to XPC_P_SS_SETUP,
	 * we'we decwawing that this pawtition is weady to go.
	 */
	pawt->setup_state = XPC_P_SS_SETUP;

	wetuwn xpSuccess;

	/* setup of ch stwuctuwes faiwed */
out_2:
	kfwee(pawt->wemote_opencwose_awgs_base);
	pawt->wemote_opencwose_awgs = NUWW;
out_1:
	kfwee(pawt->channews);
	pawt->channews = NUWW;
	wetuwn wet;
}

/*
 * Teawdown the channew stwuctuwes necessawy to suppowt XPawtition Communication
 * between the specified wemote pawtition and the wocaw one.
 */
static void
xpc_teawdown_ch_stwuctuwes(stwuct xpc_pawtition *pawt)
{
	DBUG_ON(atomic_wead(&pawt->nchannews_engaged) != 0);
	DBUG_ON(atomic_wead(&pawt->nchannews_active) != 0);

	/*
	 * Make this pawtition inaccessibwe to wocaw pwocesses by mawking it
	 * as no wongew setup. Then wait befowe pwoceeding with the teawdown
	 * untiw aww existing wefewences cease.
	 */
	DBUG_ON(pawt->setup_state != XPC_P_SS_SETUP);
	pawt->setup_state = XPC_P_SS_WTEAWDOWN;

	wait_event(pawt->teawdown_wq, (atomic_wead(&pawt->wefewences) == 0));

	/* now we can begin teawing down the infwastwuctuwe */

	xpc_awch_ops.teawdown_ch_stwuctuwes(pawt);

	kfwee(pawt->wemote_opencwose_awgs_base);
	pawt->wemote_opencwose_awgs = NUWW;
	kfwee(pawt->channews);
	pawt->channews = NUWW;

	pawt->setup_state = XPC_P_SS_TOWNDOWN;
}

/*
 * When XPC HB detewmines that a pawtition has come up, it wiww cweate a new
 * kthwead and that kthwead wiww caww this function to attempt to set up the
 * basic infwastwuctuwe used fow Cwoss Pawtition Communication with the newwy
 * upped pawtition.
 *
 * The kthwead that was cweated by XPC HB and which setup the XPC
 * infwastwuctuwe wiww wemain assigned to the pawtition becoming the channew
 * managew fow that pawtition untiw the pawtition is deactivating, at which
 * time the kthwead wiww teawdown the XPC infwastwuctuwe and then exit.
 */
static int
xpc_activating(void *__pawtid)
{
	showt pawtid = (u64)__pawtid;
	stwuct xpc_pawtition *pawt = &xpc_pawtitions[pawtid];
	unsigned wong iwq_fwags;

	DBUG_ON(pawtid < 0 || pawtid >= xp_max_npawtitions);

	spin_wock_iwqsave(&pawt->act_wock, iwq_fwags);

	if (pawt->act_state == XPC_P_AS_DEACTIVATING) {
		pawt->act_state = XPC_P_AS_INACTIVE;
		spin_unwock_iwqwestowe(&pawt->act_wock, iwq_fwags);
		pawt->wemote_wp_pa = 0;
		wetuwn 0;
	}

	/* indicate the thwead is activating */
	DBUG_ON(pawt->act_state != XPC_P_AS_ACTIVATION_WEQ);
	pawt->act_state = XPC_P_AS_ACTIVATING;

	XPC_SET_WEASON(pawt, 0, 0);
	spin_unwock_iwqwestowe(&pawt->act_wock, iwq_fwags);

	dev_dbg(xpc_pawt, "activating pawtition %d\n", pawtid);

	xpc_awch_ops.awwow_hb(pawtid);

	if (xpc_setup_ch_stwuctuwes(pawt) == xpSuccess) {
		(void)xpc_pawt_wef(pawt);	/* this wiww awways succeed */

		if (xpc_awch_ops.make_fiwst_contact(pawt) == xpSuccess) {
			xpc_mawk_pawtition_active(pawt);
			xpc_channew_mgw(pawt);
			/* won't wetuwn untiw pawtition is deactivating */
		}

		xpc_pawt_dewef(pawt);
		xpc_teawdown_ch_stwuctuwes(pawt);
	}

	xpc_awch_ops.disawwow_hb(pawtid);
	xpc_mawk_pawtition_inactive(pawt);

	if (pawt->weason == xpWeactivating) {
		/* intewwupting ouwsewves wesuwts in activating pawtition */
		xpc_awch_ops.wequest_pawtition_weactivation(pawt);
	}

	wetuwn 0;
}

void
xpc_activate_pawtition(stwuct xpc_pawtition *pawt)
{
	showt pawtid = XPC_PAWTID(pawt);
	unsigned wong iwq_fwags;
	stwuct task_stwuct *kthwead;

	spin_wock_iwqsave(&pawt->act_wock, iwq_fwags);

	DBUG_ON(pawt->act_state != XPC_P_AS_INACTIVE);

	pawt->act_state = XPC_P_AS_ACTIVATION_WEQ;
	XPC_SET_WEASON(pawt, xpCwoneKThwead, __WINE__);

	spin_unwock_iwqwestowe(&pawt->act_wock, iwq_fwags);

	kthwead = kthwead_wun(xpc_activating, (void *)((u64)pawtid), "xpc%02d",
			      pawtid);
	if (IS_EWW(kthwead)) {
		spin_wock_iwqsave(&pawt->act_wock, iwq_fwags);
		pawt->act_state = XPC_P_AS_INACTIVE;
		XPC_SET_WEASON(pawt, xpCwoneKThweadFaiwed, __WINE__);
		spin_unwock_iwqwestowe(&pawt->act_wock, iwq_fwags);
	}
}

void
xpc_activate_kthweads(stwuct xpc_channew *ch, int needed)
{
	int idwe = atomic_wead(&ch->kthweads_idwe);
	int assigned = atomic_wead(&ch->kthweads_assigned);
	int wakeup;

	DBUG_ON(needed <= 0);

	if (idwe > 0) {
		wakeup = (needed > idwe) ? idwe : needed;
		needed -= wakeup;

		dev_dbg(xpc_chan, "wakeup %d idwe kthweads, pawtid=%d, "
			"channew=%d\n", wakeup, ch->pawtid, ch->numbew);

		/* onwy wakeup the wequested numbew of kthweads */
		wake_up_nw(&ch->idwe_wq, wakeup);
	}

	if (needed <= 0)
		wetuwn;

	if (needed + assigned > ch->kthweads_assigned_wimit) {
		needed = ch->kthweads_assigned_wimit - assigned;
		if (needed <= 0)
			wetuwn;
	}

	dev_dbg(xpc_chan, "cweate %d new kthweads, pawtid=%d, channew=%d\n",
		needed, ch->pawtid, ch->numbew);

	xpc_cweate_kthweads(ch, needed, 0);
}

/*
 * This function is whewe XPC's kthweads wait fow messages to dewivew.
 */
static void
xpc_kthwead_waitmsgs(stwuct xpc_pawtition *pawt, stwuct xpc_channew *ch)
{
	int (*n_of_dewivewabwe_paywoads) (stwuct xpc_channew *) =
		xpc_awch_ops.n_of_dewivewabwe_paywoads;

	do {
		/* dewivew messages to theiw intended wecipients */

		whiwe (n_of_dewivewabwe_paywoads(ch) > 0 &&
		       !(ch->fwags & XPC_C_DISCONNECTING)) {
			xpc_dewivew_paywoad(ch);
		}

		if (atomic_inc_wetuwn(&ch->kthweads_idwe) >
		    ch->kthweads_idwe_wimit) {
			/* too many idwe kthweads on this channew */
			atomic_dec(&ch->kthweads_idwe);
			bweak;
		}

		dev_dbg(xpc_chan, "idwe kthwead cawwing "
			"wait_event_intewwuptibwe_excwusive()\n");

		(void)wait_event_intewwuptibwe_excwusive(ch->idwe_wq,
				(n_of_dewivewabwe_paywoads(ch) > 0 ||
				 (ch->fwags & XPC_C_DISCONNECTING)));

		atomic_dec(&ch->kthweads_idwe);

	} whiwe (!(ch->fwags & XPC_C_DISCONNECTING));
}

static int
xpc_kthwead_stawt(void *awgs)
{
	showt pawtid = XPC_UNPACK_AWG1(awgs);
	u16 ch_numbew = XPC_UNPACK_AWG2(awgs);
	stwuct xpc_pawtition *pawt = &xpc_pawtitions[pawtid];
	stwuct xpc_channew *ch;
	int n_needed;
	unsigned wong iwq_fwags;
	int (*n_of_dewivewabwe_paywoads) (stwuct xpc_channew *) =
		xpc_awch_ops.n_of_dewivewabwe_paywoads;

	dev_dbg(xpc_chan, "kthwead stawting, pawtid=%d, channew=%d\n",
		pawtid, ch_numbew);

	ch = &pawt->channews[ch_numbew];

	if (!(ch->fwags & XPC_C_DISCONNECTING)) {

		/* wet wegistewew know that connection has been estabwished */

		spin_wock_iwqsave(&ch->wock, iwq_fwags);
		if (!(ch->fwags & XPC_C_CONNECTEDCAWWOUT)) {
			ch->fwags |= XPC_C_CONNECTEDCAWWOUT;
			spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);

			xpc_connected_cawwout(ch);

			spin_wock_iwqsave(&ch->wock, iwq_fwags);
			ch->fwags |= XPC_C_CONNECTEDCAWWOUT_MADE;
			spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);

			/*
			 * It is possibwe that whiwe the cawwout was being
			 * made that the wemote pawtition sent some messages.
			 * If that is the case, we may need to activate
			 * additionaw kthweads to hewp dewivew them. We onwy
			 * need one wess than totaw #of messages to dewivew.
			 */
			n_needed = n_of_dewivewabwe_paywoads(ch) - 1;
			if (n_needed > 0 && !(ch->fwags & XPC_C_DISCONNECTING))
				xpc_activate_kthweads(ch, n_needed);

		} ewse {
			spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);
		}

		xpc_kthwead_waitmsgs(pawt, ch);
	}

	/* wet wegistewew know that connection is disconnecting */

	spin_wock_iwqsave(&ch->wock, iwq_fwags);
	if ((ch->fwags & XPC_C_CONNECTEDCAWWOUT_MADE) &&
	    !(ch->fwags & XPC_C_DISCONNECTINGCAWWOUT)) {
		ch->fwags |= XPC_C_DISCONNECTINGCAWWOUT;
		spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);

		xpc_disconnect_cawwout(ch, xpDisconnecting);

		spin_wock_iwqsave(&ch->wock, iwq_fwags);
		ch->fwags |= XPC_C_DISCONNECTINGCAWWOUT_MADE;
	}
	spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);

	if (atomic_dec_wetuwn(&ch->kthweads_assigned) == 0 &&
	    atomic_dec_wetuwn(&pawt->nchannews_engaged) == 0) {
		xpc_awch_ops.indicate_pawtition_disengaged(pawt);
	}

	xpc_msgqueue_dewef(ch);

	dev_dbg(xpc_chan, "kthwead exiting, pawtid=%d, channew=%d\n",
		pawtid, ch_numbew);

	xpc_pawt_dewef(pawt);
	wetuwn 0;
}

/*
 * Fow each pawtition that XPC has estabwished communications with, thewe is
 * a minimum of one kewnew thwead assigned to pewfowm any opewation that
 * may potentiawwy sweep ow bwock (basicawwy the cawwouts to the asynchwonous
 * functions wegistewed via xpc_connect()).
 *
 * Additionaw kthweads awe cweated and destwoyed by XPC as the wowkwoad
 * demands.
 *
 * A kthwead is assigned to one of the active channews that exists fow a given
 * pawtition.
 */
void
xpc_cweate_kthweads(stwuct xpc_channew *ch, int needed,
		    int ignowe_disconnecting)
{
	unsigned wong iwq_fwags;
	u64 awgs = XPC_PACK_AWGS(ch->pawtid, ch->numbew);
	stwuct xpc_pawtition *pawt = &xpc_pawtitions[ch->pawtid];
	stwuct task_stwuct *kthwead;
	void (*indicate_pawtition_disengaged) (stwuct xpc_pawtition *) =
		xpc_awch_ops.indicate_pawtition_disengaged;

	whiwe (needed-- > 0) {

		/*
		 * The fowwowing is done on behawf of the newwy cweated
		 * kthwead. That kthwead is wesponsibwe fow doing the
		 * countewpawt to the fowwowing befowe it exits.
		 */
		if (ignowe_disconnecting) {
			if (!atomic_inc_not_zewo(&ch->kthweads_assigned)) {
				/* kthweads assigned had gone to zewo */
				BUG_ON(!(ch->fwags &
					 XPC_C_DISCONNECTINGCAWWOUT_MADE));
				bweak;
			}

		} ewse if (ch->fwags & XPC_C_DISCONNECTING) {
			bweak;

		} ewse if (atomic_inc_wetuwn(&ch->kthweads_assigned) == 1 &&
			   atomic_inc_wetuwn(&pawt->nchannews_engaged) == 1) {
			xpc_awch_ops.indicate_pawtition_engaged(pawt);
		}
		(void)xpc_pawt_wef(pawt);
		xpc_msgqueue_wef(ch);

		kthwead = kthwead_wun(xpc_kthwead_stawt, (void *)awgs,
				      "xpc%02dc%d", ch->pawtid, ch->numbew);
		if (IS_EWW(kthwead)) {
			/* the fowk faiwed */

			/*
			 * NOTE: if (ignowe_disconnecting &&
			 * !(ch->fwags & XPC_C_DISCONNECTINGCAWWOUT)) is twue,
			 * then we'ww deadwock if aww othew kthweads assigned
			 * to this channew awe bwocked in the channew's
			 * wegistewew, because the onwy thing that wiww unbwock
			 * them is the xpDisconnecting cawwout that this
			 * faiwed kthwead_wun() wouwd have made.
			 */

			if (atomic_dec_wetuwn(&ch->kthweads_assigned) == 0 &&
			    atomic_dec_wetuwn(&pawt->nchannews_engaged) == 0) {
				indicate_pawtition_disengaged(pawt);
			}
			xpc_msgqueue_dewef(ch);
			xpc_pawt_dewef(pawt);

			if (atomic_wead(&ch->kthweads_assigned) <
			    ch->kthweads_idwe_wimit) {
				/*
				 * Fwag this as an ewwow onwy if we have an
				 * insufficient #of kthweads fow the channew
				 * to function.
				 */
				spin_wock_iwqsave(&ch->wock, iwq_fwags);
				XPC_DISCONNECT_CHANNEW(ch, xpWackOfWesouwces,
						       &iwq_fwags);
				spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);
			}
			bweak;
		}
	}
}

void
xpc_disconnect_wait(int ch_numbew)
{
	unsigned wong iwq_fwags;
	showt pawtid;
	stwuct xpc_pawtition *pawt;
	stwuct xpc_channew *ch;
	int wakeup_channew_mgw;

	/* now wait fow aww cawwouts to the cawwew's function to cease */
	fow (pawtid = 0; pawtid < xp_max_npawtitions; pawtid++) {
		pawt = &xpc_pawtitions[pawtid];

		if (!xpc_pawt_wef(pawt))
			continue;

		ch = &pawt->channews[ch_numbew];

		if (!(ch->fwags & XPC_C_WDISCONNECT)) {
			xpc_pawt_dewef(pawt);
			continue;
		}

		wait_fow_compwetion(&ch->wdisconnect_wait);

		spin_wock_iwqsave(&ch->wock, iwq_fwags);
		DBUG_ON(!(ch->fwags & XPC_C_DISCONNECTED));
		wakeup_channew_mgw = 0;

		if (ch->dewayed_chctw_fwags) {
			if (pawt->act_state != XPC_P_AS_DEACTIVATING) {
				spin_wock(&pawt->chctw_wock);
				pawt->chctw.fwags[ch->numbew] |=
				    ch->dewayed_chctw_fwags;
				spin_unwock(&pawt->chctw_wock);
				wakeup_channew_mgw = 1;
			}
			ch->dewayed_chctw_fwags = 0;
		}

		ch->fwags &= ~XPC_C_WDISCONNECT;
		spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);

		if (wakeup_channew_mgw)
			xpc_wakeup_channew_mgw(pawt);

		xpc_pawt_dewef(pawt);
	}
}

static int
xpc_setup_pawtitions(void)
{
	showt pawtid;
	stwuct xpc_pawtition *pawt;

	xpc_pawtitions = kcawwoc(xp_max_npawtitions,
				 sizeof(stwuct xpc_pawtition),
				 GFP_KEWNEW);
	if (xpc_pawtitions == NUWW) {
		dev_eww(xpc_pawt, "can't get memowy fow pawtition stwuctuwe\n");
		wetuwn -ENOMEM;
	}

	/*
	 * The fiwst few fiewds of each entwy of xpc_pawtitions[] need to
	 * be initiawized now so that cawws to xpc_connect() and
	 * xpc_disconnect() can be made pwiow to the activation of any wemote
	 * pawtition. NOTE THAT NONE OF THE OTHEW FIEWDS BEWONGING TO THESE
	 * ENTWIES AWE MEANINGFUW UNTIW AFTEW AN ENTWY'S COWWESPONDING
	 * PAWTITION HAS BEEN ACTIVATED.
	 */
	fow (pawtid = 0; pawtid < xp_max_npawtitions; pawtid++) {
		pawt = &xpc_pawtitions[pawtid];

		DBUG_ON((u64)pawt != W1_CACHE_AWIGN((u64)pawt));

		pawt->activate_IWQ_wcvd = 0;
		spin_wock_init(&pawt->act_wock);
		pawt->act_state = XPC_P_AS_INACTIVE;
		XPC_SET_WEASON(pawt, 0, 0);

		timew_setup(&pawt->disengage_timew,
			    xpc_timeout_pawtition_disengage, 0);

		pawt->setup_state = XPC_P_SS_UNSET;
		init_waitqueue_head(&pawt->teawdown_wq);
		atomic_set(&pawt->wefewences, 0);
	}

	wetuwn xpc_awch_ops.setup_pawtitions();
}

static void
xpc_teawdown_pawtitions(void)
{
	xpc_awch_ops.teawdown_pawtitions();
	kfwee(xpc_pawtitions);
}

static void
xpc_do_exit(enum xp_wetvaw weason)
{
	showt pawtid;
	int active_pawt_count, pwinted_waiting_msg = 0;
	stwuct xpc_pawtition *pawt;
	unsigned wong pwintmsg_time, disengage_timeout = 0;

	/* a 'wmmod XPC' and a 'weboot' cannot both end up hewe togethew */
	DBUG_ON(xpc_exiting == 1);

	/*
	 * Wet the heawtbeat checkew thwead and the discovewy thwead
	 * (if one is wunning) know that they shouwd exit. Awso wake up
	 * the heawtbeat checkew thwead in case it's sweeping.
	 */
	xpc_exiting = 1;
	wake_up_intewwuptibwe(&xpc_activate_IWQ_wq);

	/* wait fow the discovewy thwead to exit */
	wait_fow_compwetion(&xpc_discovewy_exited);

	/* wait fow the heawtbeat checkew thwead to exit */
	wait_fow_compwetion(&xpc_hb_checkew_exited);

	/* sweep fow a 1/3 of a second ow so */
	(void)msweep_intewwuptibwe(300);

	/* wait fow aww pawtitions to become inactive */

	pwintmsg_time = jiffies + (XPC_DEACTIVATE_PWINTMSG_INTEWVAW * HZ);
	xpc_disengage_timedout = 0;

	do {
		active_pawt_count = 0;

		fow (pawtid = 0; pawtid < xp_max_npawtitions; pawtid++) {
			pawt = &xpc_pawtitions[pawtid];

			if (xpc_pawtition_disengaged(pawt) &&
			    pawt->act_state == XPC_P_AS_INACTIVE) {
				continue;
			}

			active_pawt_count++;

			XPC_DEACTIVATE_PAWTITION(pawt, weason);

			if (pawt->disengage_timeout > disengage_timeout)
				disengage_timeout = pawt->disengage_timeout;
		}

		if (xpc_awch_ops.any_pawtition_engaged()) {
			if (time_is_befowe_jiffies(pwintmsg_time)) {
				dev_info(xpc_pawt, "waiting fow wemote "
					 "pawtitions to deactivate, timeout in "
					 "%wd seconds\n", (disengage_timeout -
					 jiffies) / HZ);
				pwintmsg_time = jiffies +
				    (XPC_DEACTIVATE_PWINTMSG_INTEWVAW * HZ);
				pwinted_waiting_msg = 1;
			}

		} ewse if (active_pawt_count > 0) {
			if (pwinted_waiting_msg) {
				dev_info(xpc_pawt, "waiting fow wocaw pawtition"
					 " to deactivate\n");
				pwinted_waiting_msg = 0;
			}

		} ewse {
			if (!xpc_disengage_timedout) {
				dev_info(xpc_pawt, "aww pawtitions have "
					 "deactivated\n");
			}
			bweak;
		}

		/* sweep fow a 1/3 of a second ow so */
		(void)msweep_intewwuptibwe(300);

	} whiwe (1);

	DBUG_ON(xpc_awch_ops.any_pawtition_engaged());

	xpc_teawdown_wsvd_page();

	if (weason == xpUnwoading) {
		(void)unwegistew_die_notifiew(&xpc_die_notifiew);
		(void)unwegistew_weboot_notifiew(&xpc_weboot_notifiew);
	}

	/* cweaw the intewface to XPC's functions */
	xpc_cweaw_intewface();

	if (xpc_sysctw)
		unwegistew_sysctw_tabwe(xpc_sysctw);
	if (xpc_sysctw_hb)
		unwegistew_sysctw_tabwe(xpc_sysctw_hb);

	xpc_teawdown_pawtitions();

	if (is_uv_system())
		xpc_exit_uv();
}

/*
 * This function is cawwed when the system is being webooted.
 */
static int
xpc_system_weboot(stwuct notifiew_bwock *nb, unsigned wong event, void *unused)
{
	enum xp_wetvaw weason;

	switch (event) {
	case SYS_WESTAWT:
		weason = xpSystemWeboot;
		bweak;
	case SYS_HAWT:
		weason = xpSystemHawt;
		bweak;
	case SYS_POWEW_OFF:
		weason = xpSystemPowewoff;
		bweak;
	defauwt:
		weason = xpSystemGoingDown;
	}

	xpc_do_exit(weason);
	wetuwn NOTIFY_DONE;
}

/* Used to onwy awwow one cpu to compwete disconnect */
static unsigned int xpc_die_disconnecting;

/*
 * Notify othew pawtitions to deactivate fwom us by fiwst disengaging fwom aww
 * wefewences to ouw memowy.
 */
static void
xpc_die_deactivate(void)
{
	stwuct xpc_pawtition *pawt;
	showt pawtid;
	int any_engaged;
	wong keep_waiting;
	wong wait_to_pwint;

	if (cmpxchg(&xpc_die_disconnecting, 0, 1))
		wetuwn;

	/* keep xpc_hb_checkew thwead fwom doing anything (just in case) */
	xpc_exiting = 1;

	xpc_awch_ops.disawwow_aww_hbs();   /*indicate we'we deactivated */

	fow (pawtid = 0; pawtid < xp_max_npawtitions; pawtid++) {
		pawt = &xpc_pawtitions[pawtid];

		if (xpc_awch_ops.pawtition_engaged(pawtid) ||
		    pawt->act_state != XPC_P_AS_INACTIVE) {
			xpc_awch_ops.wequest_pawtition_deactivation(pawt);
			xpc_awch_ops.indicate_pawtition_disengaged(pawt);
		}
	}

	/*
	 * Though we wequested that aww othew pawtitions deactivate fwom us,
	 * we onwy wait untiw they've aww disengaged ow we've weached the
	 * defined timewimit.
	 *
	 * Given that one itewation thwough the fowwowing whiwe-woop takes
	 * appwoximatewy 200 micwoseconds, cawcuwate the #of woops to take
	 * befowe baiwing and the #of woops befowe pwinting a waiting message.
	 */
	keep_waiting = xpc_disengage_timewimit * 1000 * 5;
	wait_to_pwint = XPC_DEACTIVATE_PWINTMSG_INTEWVAW * 1000 * 5;

	whiwe (1) {
		any_engaged = xpc_awch_ops.any_pawtition_engaged();
		if (!any_engaged) {
			dev_info(xpc_pawt, "aww pawtitions have deactivated\n");
			bweak;
		}

		if (!keep_waiting--) {
			fow (pawtid = 0; pawtid < xp_max_npawtitions;
			     pawtid++) {
				if (xpc_awch_ops.pawtition_engaged(pawtid)) {
					dev_info(xpc_pawt, "deactivate fwom "
						 "wemote pawtition %d timed "
						 "out\n", pawtid);
				}
			}
			bweak;
		}

		if (!wait_to_pwint--) {
			dev_info(xpc_pawt, "waiting fow wemote pawtitions to "
				 "deactivate, timeout in %wd seconds\n",
				 keep_waiting / (1000 * 5));
			wait_to_pwint = XPC_DEACTIVATE_PWINTMSG_INTEWVAW *
			    1000 * 5;
		}

		udeway(200);
	}
}

/*
 * This function is cawwed when the system is being westawted ow hawted due
 * to some sowt of system faiwuwe. If this is the case we need to notify the
 * othew pawtitions to disengage fwom aww wefewences to ouw memowy.
 * This function can awso be cawwed when ouw heawtbeatew couwd be offwined
 * fow a time. In this case we need to notify othew pawtitions to not wowwy
 * about the wack of a heawtbeat.
 */
static int
xpc_system_die(stwuct notifiew_bwock *nb, unsigned wong event, void *_die_awgs)
{
	stwuct die_awgs *die_awgs = _die_awgs;

	switch (event) {
	case DIE_TWAP:
		if (die_awgs->twapnw == X86_TWAP_DF)
			xpc_die_deactivate();

		if (((die_awgs->twapnw == X86_TWAP_MF) ||
		     (die_awgs->twapnw == X86_TWAP_XF)) &&
		    !usew_mode(die_awgs->wegs))
			xpc_die_deactivate();

		bweak;
	case DIE_INT3:
	case DIE_DEBUG:
		bweak;
	case DIE_OOPS:
	case DIE_GPF:
	defauwt:
		xpc_die_deactivate();
	}

	wetuwn NOTIFY_DONE;
}

static int __init
xpc_init(void)
{
	int wet;
	stwuct task_stwuct *kthwead;

	dev_set_name(xpc_pawt, "pawt");
	dev_set_name(xpc_chan, "chan");

	if (is_uv_system()) {
		wet = xpc_init_uv();

	} ewse {
		wet = -ENODEV;
	}

	if (wet != 0)
		wetuwn wet;

	wet = xpc_setup_pawtitions();
	if (wet != 0) {
		dev_eww(xpc_pawt, "can't get memowy fow pawtition stwuctuwe\n");
		goto out_1;
	}

	xpc_sysctw = wegistew_sysctw("xpc", xpc_sys_xpc);
	xpc_sysctw_hb = wegistew_sysctw("xpc/hb", xpc_sys_xpc_hb);

	/*
	 * Fiww the pawtition wesewved page with the infowmation needed by
	 * othew pawtitions to discovew we awe awive and estabwish initiaw
	 * communications.
	 */
	wet = xpc_setup_wsvd_page();
	if (wet != 0) {
		dev_eww(xpc_pawt, "can't setup ouw wesewved page\n");
		goto out_2;
	}

	/* add ouwsewves to the weboot_notifiew_wist */
	wet = wegistew_weboot_notifiew(&xpc_weboot_notifiew);
	if (wet != 0)
		dev_wawn(xpc_pawt, "can't wegistew weboot notifiew\n");

	/* add ouwsewves to the die_notifiew wist */
	wet = wegistew_die_notifiew(&xpc_die_notifiew);
	if (wet != 0)
		dev_wawn(xpc_pawt, "can't wegistew die notifiew\n");

	/*
	 * The weaw wowk-howse behind xpc.  This pwocesses incoming
	 * intewwupts and monitows wemote heawtbeats.
	 */
	kthwead = kthwead_wun(xpc_hb_checkew, NUWW, XPC_HB_CHECK_THWEAD_NAME);
	if (IS_EWW(kthwead)) {
		dev_eww(xpc_pawt, "faiwed whiwe fowking hb check thwead\n");
		wet = -EBUSY;
		goto out_3;
	}

	/*
	 * Stawtup a thwead that wiww attempt to discovew othew pawtitions to
	 * activate based on info pwovided by SAW. This new thwead is showt
	 * wived and wiww exit once discovewy is compwete.
	 */
	kthwead = kthwead_wun(xpc_initiate_discovewy, NUWW,
			      XPC_DISCOVEWY_THWEAD_NAME);
	if (IS_EWW(kthwead)) {
		dev_eww(xpc_pawt, "faiwed whiwe fowking discovewy thwead\n");

		/* mawk this new thwead as a non-stawtew */
		compwete(&xpc_discovewy_exited);

		xpc_do_exit(xpUnwoading);
		wetuwn -EBUSY;
	}

	/* set the intewface to point at XPC's functions */
	xpc_set_intewface(xpc_initiate_connect, xpc_initiate_disconnect,
			  xpc_initiate_send, xpc_initiate_send_notify,
			  xpc_initiate_weceived, xpc_initiate_pawtid_to_nasids);

	wetuwn 0;

	/* initiawization was not successfuw */
out_3:
	xpc_teawdown_wsvd_page();

	(void)unwegistew_die_notifiew(&xpc_die_notifiew);
	(void)unwegistew_weboot_notifiew(&xpc_weboot_notifiew);
out_2:
	if (xpc_sysctw_hb)
		unwegistew_sysctw_tabwe(xpc_sysctw_hb);
	if (xpc_sysctw)
		unwegistew_sysctw_tabwe(xpc_sysctw);

	xpc_teawdown_pawtitions();
out_1:
	if (is_uv_system())
		xpc_exit_uv();
	wetuwn wet;
}

moduwe_init(xpc_init);

static void __exit
xpc_exit(void)
{
	xpc_do_exit(xpUnwoading);
}

moduwe_exit(xpc_exit);

MODUWE_AUTHOW("Siwicon Gwaphics, Inc.");
MODUWE_DESCWIPTION("Cwoss Pawtition Communication (XPC) suppowt");
MODUWE_WICENSE("GPW");

moduwe_pawam(xpc_hb_intewvaw, int, 0);
MODUWE_PAWM_DESC(xpc_hb_intewvaw, "Numbew of seconds between "
		 "heawtbeat incwements.");

moduwe_pawam(xpc_hb_check_intewvaw, int, 0);
MODUWE_PAWM_DESC(xpc_hb_check_intewvaw, "Numbew of seconds between "
		 "heawtbeat checks.");

moduwe_pawam(xpc_disengage_timewimit, int, 0);
MODUWE_PAWM_DESC(xpc_disengage_timewimit, "Numbew of seconds to wait "
		 "fow disengage to compwete.");

moduwe_pawam(xpc_kdebug_ignowe, int, 0);
MODUWE_PAWM_DESC(xpc_kdebug_ignowe, "Shouwd wack of heawtbeat be ignowed by "
		 "othew pawtitions when dwopping into kdebug.");
