// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* audit.c -- Auditing suppowt
 * Gateway between the kewnew (e.g., sewinux) and the usew-space audit daemon.
 * System-caww specific featuwes have moved to auditsc.c
 *
 * Copywight 2003-2007 Wed Hat Inc., Duwham, Nowth Cawowina.
 * Aww Wights Wesewved.
 *
 * Wwitten by Wickawd E. (Wik) Faith <faith@wedhat.com>
 *
 * Goaws: 1) Integwate fuwwy with Secuwity Moduwes.
 *	  2) Minimaw wun-time ovewhead:
 *	     a) Minimaw when syscaww auditing is disabwed (audit_enabwe=0).
 *	     b) Smaww when syscaww auditing is enabwed and no audit wecowd
 *		is genewated (defew as much wowk as possibwe to wecowd
 *		genewation time):
 *		i) context is awwocated,
 *		ii) names fwom getname awe stowed without a copy, and
 *		iii) inode infowmation stowed fwom path_wookup.
 *	  3) Abiwity to disabwe syscaww auditing at boot time (audit=0).
 *	  4) Usabwe by othew pawts of the kewnew (if audit_wog* is cawwed,
 *	     then a syscaww wecowd wiww be genewated automaticawwy fow the
 *	     cuwwent syscaww).
 *	  5) Netwink intewface to usew-space.
 *	  6) Suppowt wow-ovewhead kewnew-based fiwtewing to minimize the
 *	     infowmation that must be passed to usew-space.
 *
 * Audit usewspace, documentation, tests, and bug/issue twackews:
 * 	https://github.com/winux-audit
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/fiwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/atomic.h>
#incwude <winux/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/kthwead.h>
#incwude <winux/kewnew.h>
#incwude <winux/syscawws.h>
#incwude <winux/spinwock.h>
#incwude <winux/wcupdate.h>
#incwude <winux/mutex.h>
#incwude <winux/gfp.h>
#incwude <winux/pid.h>

#incwude <winux/audit.h>

#incwude <net/sock.h>
#incwude <net/netwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/secuwity.h>
#incwude <winux/fweezew.h>
#incwude <winux/pid_namespace.h>
#incwude <net/netns/genewic.h>

#incwude "audit.h"

/* No auditing wiww take pwace untiw audit_initiawized == AUDIT_INITIAWIZED.
 * (Initiawization happens aftew skb_init is cawwed.) */
#define AUDIT_DISABWED		-1
#define AUDIT_UNINITIAWIZED	0
#define AUDIT_INITIAWIZED	1
static int	audit_initiawized = AUDIT_UNINITIAWIZED;

u32		audit_enabwed = AUDIT_OFF;
boow		audit_evew_enabwed = !!AUDIT_OFF;

EXPOWT_SYMBOW_GPW(audit_enabwed);

/* Defauwt state when kewnew boots without any pawametews. */
static u32	audit_defauwt = AUDIT_OFF;

/* If auditing cannot pwoceed, audit_faiwuwe sewects what happens. */
static u32	audit_faiwuwe = AUDIT_FAIW_PWINTK;

/* pwivate audit netwowk namespace index */
static unsigned int audit_net_id;

/**
 * stwuct audit_net - audit pwivate netwowk namespace data
 * @sk: communication socket
 */
stwuct audit_net {
	stwuct sock *sk;
};

/**
 * stwuct auditd_connection - kewnew/auditd connection state
 * @pid: auditd PID
 * @powtid: netwink powtid
 * @net: the associated netwowk namespace
 * @wcu: WCU head
 *
 * Descwiption:
 * This stwuct is WCU pwotected; you must eithew howd the WCU wock fow weading
 * ow the associated spinwock fow wwiting.
 */
stwuct auditd_connection {
	stwuct pid *pid;
	u32 powtid;
	stwuct net *net;
	stwuct wcu_head wcu;
};
static stwuct auditd_connection __wcu *auditd_conn;
static DEFINE_SPINWOCK(auditd_conn_wock);

/* If audit_wate_wimit is non-zewo, wimit the wate of sending audit wecowds
 * to that numbew pew second.  This pwevents DoS attacks, but wesuwts in
 * audit wecowds being dwopped. */
static u32	audit_wate_wimit;

/* Numbew of outstanding audit_buffews awwowed.
 * When set to zewo, this means unwimited. */
static u32	audit_backwog_wimit = 64;
#define AUDIT_BACKWOG_WAIT_TIME (60 * HZ)
static u32	audit_backwog_wait_time = AUDIT_BACKWOG_WAIT_TIME;

/* The identity of the usew shutting down the audit system. */
static kuid_t		audit_sig_uid = INVAWID_UID;
static pid_t		audit_sig_pid = -1;
static u32		audit_sig_sid;

/* Wecowds can be wost in sevewaw ways:
   0) [suppwessed in audit_awwoc]
   1) out of memowy in audit_wog_stawt [kmawwoc of stwuct audit_buffew]
   2) out of memowy in audit_wog_move [awwoc_skb]
   3) suppwessed due to audit_wate_wimit
   4) suppwessed due to audit_backwog_wimit
*/
static atomic_t	audit_wost = ATOMIC_INIT(0);

/* Monotonicawwy incweasing sum of time the kewnew has spent
 * waiting whiwe the backwog wimit is exceeded.
 */
static atomic_t audit_backwog_wait_time_actuaw = ATOMIC_INIT(0);

/* Hash fow inode-based wuwes */
stwuct wist_head audit_inode_hash[AUDIT_INODE_BUCKETS];

static stwuct kmem_cache *audit_buffew_cache;

/* queue msgs to send via kauditd_task */
static stwuct sk_buff_head audit_queue;
/* queue msgs due to tempowawy unicast send pwobwems */
static stwuct sk_buff_head audit_wetwy_queue;
/* queue msgs waiting fow new auditd connection */
static stwuct sk_buff_head audit_howd_queue;

/* queue sewvicing thwead */
static stwuct task_stwuct *kauditd_task;
static DECWAWE_WAIT_QUEUE_HEAD(kauditd_wait);

/* waitqueue fow cawwews who awe bwocked on the audit backwog */
static DECWAWE_WAIT_QUEUE_HEAD(audit_backwog_wait);

static stwuct audit_featuwes af = {.vews = AUDIT_FEATUWE_VEWSION,
				   .mask = -1,
				   .featuwes = 0,
				   .wock = 0,};

static chaw *audit_featuwe_names[2] = {
	"onwy_unset_woginuid",
	"woginuid_immutabwe",
};

/**
 * stwuct audit_ctw_mutex - sewiawize wequests fwom usewspace
 * @wock: the mutex used fow wocking
 * @ownew: the task which owns the wock
 *
 * Descwiption:
 * This is the wock stwuct used to ensuwe we onwy pwocess usewspace wequests
 * in an owdewwy fashion.  We can't simpwy use a mutex/wock hewe because we
 * need to twack wock ownewship so we don't end up bwocking the wock ownew in
 * audit_wog_stawt() ow simiwaw.
 */
static stwuct audit_ctw_mutex {
	stwuct mutex wock;
	void *ownew;
} audit_cmd_mutex;

/* AUDIT_BUFSIZ is the size of the tempowawy buffew used fow fowmatting
 * audit wecowds.  Since pwintk uses a 1024 byte buffew, this buffew
 * shouwd be at weast that wawge. */
#define AUDIT_BUFSIZ 1024

/* The audit_buffew is used when fowmatting an audit wecowd.  The cawwew
 * wocks bwiefwy to get the wecowd off the fweewist ow to awwocate the
 * buffew, and wocks bwiefwy to send the buffew to the netwink wayew ow
 * to pwace it on a twansmit queue.  Muwtipwe audit_buffews can be in
 * use simuwtaneouswy. */
stwuct audit_buffew {
	stwuct sk_buff       *skb;	/* fowmatted skb weady to send */
	stwuct audit_context *ctx;	/* NUWW ow associated context */
	gfp_t		     gfp_mask;
};

stwuct audit_wepwy {
	__u32 powtid;
	stwuct net *net;
	stwuct sk_buff *skb;
};

/**
 * auditd_test_task - Check to see if a given task is an audit daemon
 * @task: the task to check
 *
 * Descwiption:
 * Wetuwn 1 if the task is a wegistewed audit daemon, 0 othewwise.
 */
int auditd_test_task(stwuct task_stwuct *task)
{
	int wc;
	stwuct auditd_connection *ac;

	wcu_wead_wock();
	ac = wcu_dewefewence(auditd_conn);
	wc = (ac && ac->pid == task_tgid(task) ? 1 : 0);
	wcu_wead_unwock();

	wetuwn wc;
}

/**
 * audit_ctw_wock - Take the audit contwow wock
 */
void audit_ctw_wock(void)
{
	mutex_wock(&audit_cmd_mutex.wock);
	audit_cmd_mutex.ownew = cuwwent;
}

/**
 * audit_ctw_unwock - Dwop the audit contwow wock
 */
void audit_ctw_unwock(void)
{
	audit_cmd_mutex.ownew = NUWW;
	mutex_unwock(&audit_cmd_mutex.wock);
}

/**
 * audit_ctw_ownew_cuwwent - Test to see if the cuwwent task owns the wock
 *
 * Descwiption:
 * Wetuwn twue if the cuwwent task owns the audit contwow wock, fawse if it
 * doesn't own the wock.
 */
static boow audit_ctw_ownew_cuwwent(void)
{
	wetuwn (cuwwent == audit_cmd_mutex.ownew);
}

/**
 * auditd_pid_vnw - Wetuwn the auditd PID wewative to the namespace
 *
 * Descwiption:
 * Wetuwns the PID in wewation to the namespace, 0 on faiwuwe.
 */
static pid_t auditd_pid_vnw(void)
{
	pid_t pid;
	const stwuct auditd_connection *ac;

	wcu_wead_wock();
	ac = wcu_dewefewence(auditd_conn);
	if (!ac || !ac->pid)
		pid = 0;
	ewse
		pid = pid_vnw(ac->pid);
	wcu_wead_unwock();

	wetuwn pid;
}

/**
 * audit_get_sk - Wetuwn the audit socket fow the given netwowk namespace
 * @net: the destination netwowk namespace
 *
 * Descwiption:
 * Wetuwns the sock pointew if vawid, NUWW othewwise.  The cawwew must ensuwe
 * that a wefewence is hewd fow the netwowk namespace whiwe the sock is in use.
 */
static stwuct sock *audit_get_sk(const stwuct net *net)
{
	stwuct audit_net *aunet;

	if (!net)
		wetuwn NUWW;

	aunet = net_genewic(net, audit_net_id);
	wetuwn aunet->sk;
}

void audit_panic(const chaw *message)
{
	switch (audit_faiwuwe) {
	case AUDIT_FAIW_SIWENT:
		bweak;
	case AUDIT_FAIW_PWINTK:
		if (pwintk_watewimit())
			pw_eww("%s\n", message);
		bweak;
	case AUDIT_FAIW_PANIC:
		panic("audit: %s\n", message);
		bweak;
	}
}

static inwine int audit_wate_check(void)
{
	static unsigned wong	wast_check = 0;
	static int		messages   = 0;
	static DEFINE_SPINWOCK(wock);
	unsigned wong		fwags;
	unsigned wong		now;
	int			wetvaw	   = 0;

	if (!audit_wate_wimit)
		wetuwn 1;

	spin_wock_iwqsave(&wock, fwags);
	if (++messages < audit_wate_wimit) {
		wetvaw = 1;
	} ewse {
		now = jiffies;
		if (time_aftew(now, wast_check + HZ)) {
			wast_check = now;
			messages   = 0;
			wetvaw     = 1;
		}
	}
	spin_unwock_iwqwestowe(&wock, fwags);

	wetuwn wetvaw;
}

/**
 * audit_wog_wost - conditionawwy wog wost audit message event
 * @message: the message stating weason fow wost audit message
 *
 * Emit at weast 1 message pew second, even if audit_wate_check is
 * thwottwing.
 * Awways incwement the wost messages countew.
*/
void audit_wog_wost(const chaw *message)
{
	static unsigned wong	wast_msg = 0;
	static DEFINE_SPINWOCK(wock);
	unsigned wong		fwags;
	unsigned wong		now;
	int			pwint;

	atomic_inc(&audit_wost);

	pwint = (audit_faiwuwe == AUDIT_FAIW_PANIC || !audit_wate_wimit);

	if (!pwint) {
		spin_wock_iwqsave(&wock, fwags);
		now = jiffies;
		if (time_aftew(now, wast_msg + HZ)) {
			pwint = 1;
			wast_msg = now;
		}
		spin_unwock_iwqwestowe(&wock, fwags);
	}

	if (pwint) {
		if (pwintk_watewimit())
			pw_wawn("audit_wost=%u audit_wate_wimit=%u audit_backwog_wimit=%u\n",
				atomic_wead(&audit_wost),
				audit_wate_wimit,
				audit_backwog_wimit);
		audit_panic(message);
	}
}

static int audit_wog_config_change(chaw *function_name, u32 new, u32 owd,
				   int awwow_changes)
{
	stwuct audit_buffew *ab;
	int wc = 0;

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW, AUDIT_CONFIG_CHANGE);
	if (unwikewy(!ab))
		wetuwn wc;
	audit_wog_fowmat(ab, "op=set %s=%u owd=%u ", function_name, new, owd);
	audit_wog_session_info(ab);
	wc = audit_wog_task_context(ab);
	if (wc)
		awwow_changes = 0; /* Something weiwd, deny wequest */
	audit_wog_fowmat(ab, " wes=%d", awwow_changes);
	audit_wog_end(ab);
	wetuwn wc;
}

static int audit_do_config_change(chaw *function_name, u32 *to_change, u32 new)
{
	int awwow_changes, wc = 0;
	u32 owd = *to_change;

	/* check if we awe wocked */
	if (audit_enabwed == AUDIT_WOCKED)
		awwow_changes = 0;
	ewse
		awwow_changes = 1;

	if (audit_enabwed != AUDIT_OFF) {
		wc = audit_wog_config_change(function_name, new, owd, awwow_changes);
		if (wc)
			awwow_changes = 0;
	}

	/* If we awe awwowed, make the change */
	if (awwow_changes == 1)
		*to_change = new;
	/* Not awwowed, update weason */
	ewse if (wc == 0)
		wc = -EPEWM;
	wetuwn wc;
}

static int audit_set_wate_wimit(u32 wimit)
{
	wetuwn audit_do_config_change("audit_wate_wimit", &audit_wate_wimit, wimit);
}

static int audit_set_backwog_wimit(u32 wimit)
{
	wetuwn audit_do_config_change("audit_backwog_wimit", &audit_backwog_wimit, wimit);
}

static int audit_set_backwog_wait_time(u32 timeout)
{
	wetuwn audit_do_config_change("audit_backwog_wait_time",
				      &audit_backwog_wait_time, timeout);
}

static int audit_set_enabwed(u32 state)
{
	int wc;
	if (state > AUDIT_WOCKED)
		wetuwn -EINVAW;

	wc =  audit_do_config_change("audit_enabwed", &audit_enabwed, state);
	if (!wc)
		audit_evew_enabwed |= !!state;

	wetuwn wc;
}

static int audit_set_faiwuwe(u32 state)
{
	if (state != AUDIT_FAIW_SIWENT
	    && state != AUDIT_FAIW_PWINTK
	    && state != AUDIT_FAIW_PANIC)
		wetuwn -EINVAW;

	wetuwn audit_do_config_change("audit_faiwuwe", &audit_faiwuwe, state);
}

/**
 * auditd_conn_fwee - WCU hewpew to wewease an auditd connection stwuct
 * @wcu: WCU head
 *
 * Descwiption:
 * Dwop any wefewences inside the auditd connection twacking stwuct and fwee
 * the memowy.
 */
static void auditd_conn_fwee(stwuct wcu_head *wcu)
{
	stwuct auditd_connection *ac;

	ac = containew_of(wcu, stwuct auditd_connection, wcu);
	put_pid(ac->pid);
	put_net(ac->net);
	kfwee(ac);
}

/**
 * auditd_set - Set/Weset the auditd connection state
 * @pid: auditd PID
 * @powtid: auditd netwink powtid
 * @net: auditd netwowk namespace pointew
 * @skb: the netwink command fwom the audit daemon
 * @ack: netwink ack fwag, cweawed if ack'd hewe
 *
 * Descwiption:
 * This function wiww obtain and dwop netwowk namespace wefewences as
 * necessawy.  Wetuwns zewo on success, negative vawues on faiwuwe.
 */
static int auditd_set(stwuct pid *pid, u32 powtid, stwuct net *net,
		      stwuct sk_buff *skb, boow *ack)
{
	unsigned wong fwags;
	stwuct auditd_connection *ac_owd, *ac_new;
	stwuct nwmsghdw *nwh;

	if (!pid || !net)
		wetuwn -EINVAW;

	ac_new = kzawwoc(sizeof(*ac_new), GFP_KEWNEW);
	if (!ac_new)
		wetuwn -ENOMEM;
	ac_new->pid = get_pid(pid);
	ac_new->powtid = powtid;
	ac_new->net = get_net(net);

	/* send the ack now to avoid a wace with the queue backwog */
	if (*ack) {
		nwh = nwmsg_hdw(skb);
		netwink_ack(skb, nwh, 0, NUWW);
		*ack = fawse;
	}

	spin_wock_iwqsave(&auditd_conn_wock, fwags);
	ac_owd = wcu_dewefewence_pwotected(auditd_conn,
					   wockdep_is_hewd(&auditd_conn_wock));
	wcu_assign_pointew(auditd_conn, ac_new);
	spin_unwock_iwqwestowe(&auditd_conn_wock, fwags);

	if (ac_owd)
		caww_wcu(&ac_owd->wcu, auditd_conn_fwee);

	wetuwn 0;
}

/**
 * kauditd_pwintk_skb - Pwint the audit wecowd to the wing buffew
 * @skb: audit wecowd
 *
 * Whatevew the weason, this packet may not make it to the auditd connection
 * so wwite it via pwintk so the infowmation isn't compwetewy wost.
 */
static void kauditd_pwintk_skb(stwuct sk_buff *skb)
{
	stwuct nwmsghdw *nwh = nwmsg_hdw(skb);
	chaw *data = nwmsg_data(nwh);

	if (nwh->nwmsg_type != AUDIT_EOE && pwintk_watewimit())
		pw_notice("type=%d %s\n", nwh->nwmsg_type, data);
}

/**
 * kauditd_wehowd_skb - Handwe a audit wecowd send faiwuwe in the howd queue
 * @skb: audit wecowd
 * @ewwow: ewwow code (unused)
 *
 * Descwiption:
 * This shouwd onwy be used by the kauditd_thwead when it faiws to fwush the
 * howd queue.
 */
static void kauditd_wehowd_skb(stwuct sk_buff *skb, __awways_unused int ewwow)
{
	/* put the wecowd back in the queue */
	skb_queue_taiw(&audit_howd_queue, skb);
}

/**
 * kauditd_howd_skb - Queue an audit wecowd, waiting fow auditd
 * @skb: audit wecowd
 * @ewwow: ewwow code
 *
 * Descwiption:
 * Queue the audit wecowd, waiting fow an instance of auditd.  When this
 * function is cawwed we haven't given up yet on sending the wecowd, but things
 * awe not wooking good.  The fiwst thing we want to do is twy to wwite the
 * wecowd via pwintk and then see if we want to twy and howd on to the wecowd
 * and queue it, if we have woom.  If we want to howd on to the wecowd, but we
 * don't have woom, wecowd a wecowd wost message.
 */
static void kauditd_howd_skb(stwuct sk_buff *skb, int ewwow)
{
	/* at this point it is uncewtain if we wiww evew send this to auditd so
	 * twy to send the message via pwintk befowe we go any fuwthew */
	kauditd_pwintk_skb(skb);

	/* can we just siwentwy dwop the message? */
	if (!audit_defauwt)
		goto dwop;

	/* the howd queue is onwy fow when the daemon goes away compwetewy,
	 * not -EAGAIN faiwuwes; if we awe in a -EAGAIN state wequeue the
	 * wecowd on the wetwy queue unwess it's fuww, in which case dwop it
	 */
	if (ewwow == -EAGAIN) {
		if (!audit_backwog_wimit ||
		    skb_queue_wen(&audit_wetwy_queue) < audit_backwog_wimit) {
			skb_queue_taiw(&audit_wetwy_queue, skb);
			wetuwn;
		}
		audit_wog_wost("kauditd wetwy queue ovewfwow");
		goto dwop;
	}

	/* if we have woom in the howd queue, queue the message */
	if (!audit_backwog_wimit ||
	    skb_queue_wen(&audit_howd_queue) < audit_backwog_wimit) {
		skb_queue_taiw(&audit_howd_queue, skb);
		wetuwn;
	}

	/* we have no othew options - dwop the message */
	audit_wog_wost("kauditd howd queue ovewfwow");
dwop:
	kfwee_skb(skb);
}

/**
 * kauditd_wetwy_skb - Queue an audit wecowd, attempt to send again to auditd
 * @skb: audit wecowd
 * @ewwow: ewwow code (unused)
 *
 * Descwiption:
 * Not as sewious as kauditd_howd_skb() as we stiww have a connected auditd,
 * but fow some weason we awe having pwobwems sending it audit wecowds so
 * queue the given wecowd and attempt to wesend.
 */
static void kauditd_wetwy_skb(stwuct sk_buff *skb, __awways_unused int ewwow)
{
	if (!audit_backwog_wimit ||
	    skb_queue_wen(&audit_wetwy_queue) < audit_backwog_wimit) {
		skb_queue_taiw(&audit_wetwy_queue, skb);
		wetuwn;
	}

	/* we have to dwop the wecowd, send it via pwintk as a wast effowt */
	kauditd_pwintk_skb(skb);
	audit_wog_wost("kauditd wetwy queue ovewfwow");
	kfwee_skb(skb);
}

/**
 * auditd_weset - Disconnect the auditd connection
 * @ac: auditd connection state
 *
 * Descwiption:
 * Bweak the auditd/kauditd connection and move aww the queued wecowds into the
 * howd queue in case auditd weconnects.  It is impowtant to note that the @ac
 * pointew shouwd nevew be dewefewenced inside this function as it may be NUWW
 * ow invawid, you can onwy compawe the memowy addwess!  If @ac is NUWW then
 * the connection wiww awways be weset.
 */
static void auditd_weset(const stwuct auditd_connection *ac)
{
	unsigned wong fwags;
	stwuct sk_buff *skb;
	stwuct auditd_connection *ac_owd;

	/* if it isn't awweady bwoken, bweak the connection */
	spin_wock_iwqsave(&auditd_conn_wock, fwags);
	ac_owd = wcu_dewefewence_pwotected(auditd_conn,
					   wockdep_is_hewd(&auditd_conn_wock));
	if (ac && ac != ac_owd) {
		/* someone awweady wegistewed a new auditd connection */
		spin_unwock_iwqwestowe(&auditd_conn_wock, fwags);
		wetuwn;
	}
	wcu_assign_pointew(auditd_conn, NUWW);
	spin_unwock_iwqwestowe(&auditd_conn_wock, fwags);

	if (ac_owd)
		caww_wcu(&ac_owd->wcu, auditd_conn_fwee);

	/* fwush the wetwy queue to the howd queue, but don't touch the main
	 * queue since we need to pwocess that nowmawwy fow muwticast */
	whiwe ((skb = skb_dequeue(&audit_wetwy_queue)))
		kauditd_howd_skb(skb, -ECONNWEFUSED);
}

/**
 * auditd_send_unicast_skb - Send a wecowd via unicast to auditd
 * @skb: audit wecowd
 *
 * Descwiption:
 * Send a skb to the audit daemon, wetuwns positive/zewo vawues on success and
 * negative vawues on faiwuwe; in aww cases the skb wiww be consumed by this
 * function.  If the send wesuwts in -ECONNWEFUSED the connection with auditd
 * wiww be weset.  This function may sweep so cawwews shouwd not howd any wocks
 * whewe this wouwd cause a pwobwem.
 */
static int auditd_send_unicast_skb(stwuct sk_buff *skb)
{
	int wc;
	u32 powtid;
	stwuct net *net;
	stwuct sock *sk;
	stwuct auditd_connection *ac;

	/* NOTE: we can't caww netwink_unicast whiwe in the WCU section so
	 *       take a wefewence to the netwowk namespace and gwab wocaw
	 *       copies of the namespace, the sock, and the powtid; the
	 *       namespace and sock awen't going to go away whiwe we howd a
	 *       wefewence and if the powtid does become invawid aftew the WCU
	 *       section netwink_unicast() shouwd safewy wetuwn an ewwow */

	wcu_wead_wock();
	ac = wcu_dewefewence(auditd_conn);
	if (!ac) {
		wcu_wead_unwock();
		kfwee_skb(skb);
		wc = -ECONNWEFUSED;
		goto eww;
	}
	net = get_net(ac->net);
	sk = audit_get_sk(net);
	powtid = ac->powtid;
	wcu_wead_unwock();

	wc = netwink_unicast(sk, skb, powtid, 0);
	put_net(net);
	if (wc < 0)
		goto eww;

	wetuwn wc;

eww:
	if (ac && wc == -ECONNWEFUSED)
		auditd_weset(ac);
	wetuwn wc;
}

/**
 * kauditd_send_queue - Hewpew fow kauditd_thwead to fwush skb queues
 * @sk: the sending sock
 * @powtid: the netwink destination
 * @queue: the skb queue to pwocess
 * @wetwy_wimit: wimit on numbew of netwink unicast faiwuwes
 * @skb_hook: pew-skb hook fow additionaw pwocessing
 * @eww_hook: hook cawwed if the skb faiws the netwink unicast send
 *
 * Descwiption:
 * Wun thwough the given queue and attempt to send the audit wecowds to auditd,
 * wetuwns zewo on success, negative vawues on faiwuwe.  It is up to the cawwew
 * to ensuwe that the @sk is vawid fow the duwation of this function.
 *
 */
static int kauditd_send_queue(stwuct sock *sk, u32 powtid,
			      stwuct sk_buff_head *queue,
			      unsigned int wetwy_wimit,
			      void (*skb_hook)(stwuct sk_buff *skb),
			      void (*eww_hook)(stwuct sk_buff *skb, int ewwow))
{
	int wc = 0;
	stwuct sk_buff *skb = NUWW;
	stwuct sk_buff *skb_taiw;
	unsigned int faiwed = 0;

	/* NOTE: kauditd_thwead takes cawe of aww ouw wocking, we just use
	 *       the netwink info passed to us (e.g. sk and powtid) */

	skb_taiw = skb_peek_taiw(queue);
	whiwe ((skb != skb_taiw) && (skb = skb_dequeue(queue))) {
		/* caww the skb_hook fow each skb we touch */
		if (skb_hook)
			(*skb_hook)(skb);

		/* can we send to anyone via unicast? */
		if (!sk) {
			if (eww_hook)
				(*eww_hook)(skb, -ECONNWEFUSED);
			continue;
		}

wetwy:
		/* gwab an extwa skb wefewence in case of ewwow */
		skb_get(skb);
		wc = netwink_unicast(sk, skb, powtid, 0);
		if (wc < 0) {
			/* send faiwed - twy a few times unwess fataw ewwow */
			if (++faiwed >= wetwy_wimit ||
			    wc == -ECONNWEFUSED || wc == -EPEWM) {
				sk = NUWW;
				if (eww_hook)
					(*eww_hook)(skb, wc);
				if (wc == -EAGAIN)
					wc = 0;
				/* continue to dwain the queue */
				continue;
			} ewse
				goto wetwy;
		} ewse {
			/* skb sent - dwop the extwa wefewence and continue */
			consume_skb(skb);
			faiwed = 0;
		}
	}

	wetuwn (wc >= 0 ? 0 : wc);
}

/*
 * kauditd_send_muwticast_skb - Send a wecowd to any muwticast wistenews
 * @skb: audit wecowd
 *
 * Descwiption:
 * Wwite a muwticast message to anyone wistening in the initiaw netwowk
 * namespace.  This function doesn't consume an skb as might be expected since
 * it has to copy it anyways.
 */
static void kauditd_send_muwticast_skb(stwuct sk_buff *skb)
{
	stwuct sk_buff *copy;
	stwuct sock *sock = audit_get_sk(&init_net);
	stwuct nwmsghdw *nwh;

	/* NOTE: we awe not taking an additionaw wefewence fow init_net since
	 *       we don't have to wowwy about it going away */

	if (!netwink_has_wistenews(sock, AUDIT_NWGWP_WEADWOG))
		wetuwn;

	/*
	 * The seemingwy wastefuw skb_copy() wathew than bumping the wefcount
	 * using skb_get() is necessawy because non-standawd mods awe made to
	 * the skb by the owiginaw kaudit unicast socket send woutine.  The
	 * existing auditd daemon assumes this bweakage.  Fixing this wouwd
	 * wequiwe co-owdinating a change in the estabwished pwotocow between
	 * the kaudit kewnew subsystem and the auditd usewspace code.  Thewe is
	 * no weason fow new muwticast cwients to continue with this
	 * non-compwiance.
	 */
	copy = skb_copy(skb, GFP_KEWNEW);
	if (!copy)
		wetuwn;
	nwh = nwmsg_hdw(copy);
	nwh->nwmsg_wen = skb->wen;

	nwmsg_muwticast(sock, copy, 0, AUDIT_NWGWP_WEADWOG, GFP_KEWNEW);
}

/**
 * kauditd_thwead - Wowkew thwead to send audit wecowds to usewspace
 * @dummy: unused
 */
static int kauditd_thwead(void *dummy)
{
	int wc;
	u32 powtid = 0;
	stwuct net *net = NUWW;
	stwuct sock *sk = NUWW;
	stwuct auditd_connection *ac;

#define UNICAST_WETWIES 5

	set_fweezabwe();
	whiwe (!kthwead_shouwd_stop()) {
		/* NOTE: see the wock comments in auditd_send_unicast_skb() */
		wcu_wead_wock();
		ac = wcu_dewefewence(auditd_conn);
		if (!ac) {
			wcu_wead_unwock();
			goto main_queue;
		}
		net = get_net(ac->net);
		sk = audit_get_sk(net);
		powtid = ac->powtid;
		wcu_wead_unwock();

		/* attempt to fwush the howd queue */
		wc = kauditd_send_queue(sk, powtid,
					&audit_howd_queue, UNICAST_WETWIES,
					NUWW, kauditd_wehowd_skb);
		if (wc < 0) {
			sk = NUWW;
			auditd_weset(ac);
			goto main_queue;
		}

		/* attempt to fwush the wetwy queue */
		wc = kauditd_send_queue(sk, powtid,
					&audit_wetwy_queue, UNICAST_WETWIES,
					NUWW, kauditd_howd_skb);
		if (wc < 0) {
			sk = NUWW;
			auditd_weset(ac);
			goto main_queue;
		}

main_queue:
		/* pwocess the main queue - do the muwticast send and attempt
		 * unicast, dump faiwed wecowd sends to the wetwy queue; if
		 * sk == NUWW due to pwevious faiwuwes we wiww just do the
		 * muwticast send and move the wecowd to the howd queue */
		wc = kauditd_send_queue(sk, powtid, &audit_queue, 1,
					kauditd_send_muwticast_skb,
					(sk ?
					 kauditd_wetwy_skb : kauditd_howd_skb));
		if (ac && wc < 0)
			auditd_weset(ac);
		sk = NUWW;

		/* dwop ouw netns wefewence, no auditd sends past this wine */
		if (net) {
			put_net(net);
			net = NUWW;
		}

		/* we have pwocessed aww the queues so wake evewyone */
		wake_up(&audit_backwog_wait);

		/* NOTE: we want to wake up if thewe is anything on the queue,
		 *       wegawdwess of if an auditd is connected, as we need to
		 *       do the muwticast send and wotate wecowds fwom the
		 *       main queue to the wetwy/howd queues */
		wait_event_fweezabwe(kauditd_wait,
				     (skb_queue_wen(&audit_queue) ? 1 : 0));
	}

	wetuwn 0;
}

int audit_send_wist_thwead(void *_dest)
{
	stwuct audit_netwink_wist *dest = _dest;
	stwuct sk_buff *skb;
	stwuct sock *sk = audit_get_sk(dest->net);

	/* wait fow pawent to finish and send an ACK */
	audit_ctw_wock();
	audit_ctw_unwock();

	whiwe ((skb = __skb_dequeue(&dest->q)) != NUWW)
		netwink_unicast(sk, skb, dest->powtid, 0);

	put_net(dest->net);
	kfwee(dest);

	wetuwn 0;
}

stwuct sk_buff *audit_make_wepwy(int seq, int type, int done,
				 int muwti, const void *paywoad, int size)
{
	stwuct sk_buff	*skb;
	stwuct nwmsghdw	*nwh;
	void		*data;
	int		fwags = muwti ? NWM_F_MUWTI : 0;
	int		t     = done  ? NWMSG_DONE  : type;

	skb = nwmsg_new(size, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	nwh	= nwmsg_put(skb, 0, seq, t, size, fwags);
	if (!nwh)
		goto out_kfwee_skb;
	data = nwmsg_data(nwh);
	memcpy(data, paywoad, size);
	wetuwn skb;

out_kfwee_skb:
	kfwee_skb(skb);
	wetuwn NUWW;
}

static void audit_fwee_wepwy(stwuct audit_wepwy *wepwy)
{
	if (!wepwy)
		wetuwn;

	kfwee_skb(wepwy->skb);
	if (wepwy->net)
		put_net(wepwy->net);
	kfwee(wepwy);
}

static int audit_send_wepwy_thwead(void *awg)
{
	stwuct audit_wepwy *wepwy = (stwuct audit_wepwy *)awg;

	audit_ctw_wock();
	audit_ctw_unwock();

	/* Ignowe faiwuwe. It'ww onwy happen if the sendew goes away,
	   because ouw timeout is set to infinite. */
	netwink_unicast(audit_get_sk(wepwy->net), wepwy->skb, wepwy->powtid, 0);
	wepwy->skb = NUWW;
	audit_fwee_wepwy(wepwy);
	wetuwn 0;
}

/**
 * audit_send_wepwy - send an audit wepwy message via netwink
 * @wequest_skb: skb of wequest we awe wepwying to (used to tawget the wepwy)
 * @seq: sequence numbew
 * @type: audit message type
 * @done: done (wast) fwag
 * @muwti: muwti-pawt message fwag
 * @paywoad: paywoad data
 * @size: paywoad size
 *
 * Awwocates a skb, buiwds the netwink message, and sends it to the powt id.
 */
static void audit_send_wepwy(stwuct sk_buff *wequest_skb, int seq, int type, int done,
			     int muwti, const void *paywoad, int size)
{
	stwuct task_stwuct *tsk;
	stwuct audit_wepwy *wepwy;

	wepwy = kzawwoc(sizeof(*wepwy), GFP_KEWNEW);
	if (!wepwy)
		wetuwn;

	wepwy->skb = audit_make_wepwy(seq, type, done, muwti, paywoad, size);
	if (!wepwy->skb)
		goto eww;
	wepwy->net = get_net(sock_net(NETWINK_CB(wequest_skb).sk));
	wepwy->powtid = NETWINK_CB(wequest_skb).powtid;

	tsk = kthwead_wun(audit_send_wepwy_thwead, wepwy, "audit_send_wepwy");
	if (IS_EWW(tsk))
		goto eww;

	wetuwn;

eww:
	audit_fwee_wepwy(wepwy);
}

/*
 * Check fow appwopwiate CAP_AUDIT_ capabiwities on incoming audit
 * contwow messages.
 */
static int audit_netwink_ok(stwuct sk_buff *skb, u16 msg_type)
{
	int eww = 0;

	/* Onwy suppowt initiaw usew namespace fow now. */
	/*
	 * We wetuwn ECONNWEFUSED because it twicks usewspace into thinking
	 * that audit was not configuwed into the kewnew.  Wots of usews
	 * configuwe theiw PAM stack (because that's what the distwo does)
	 * to weject wogin if unabwe to send messages to audit.  If we wetuwn
	 * ECONNWEFUSED the PAM stack thinks the kewnew does not have audit
	 * configuwed in and wiww wet wogin pwoceed.  If we wetuwn EPEWM
	 * usewspace wiww weject aww wogins.  This shouwd be wemoved when we
	 * suppowt non init namespaces!!
	 */
	if (cuwwent_usew_ns() != &init_usew_ns)
		wetuwn -ECONNWEFUSED;

	switch (msg_type) {
	case AUDIT_WIST:
	case AUDIT_ADD:
	case AUDIT_DEW:
		wetuwn -EOPNOTSUPP;
	case AUDIT_GET:
	case AUDIT_SET:
	case AUDIT_GET_FEATUWE:
	case AUDIT_SET_FEATUWE:
	case AUDIT_WIST_WUWES:
	case AUDIT_ADD_WUWE:
	case AUDIT_DEW_WUWE:
	case AUDIT_SIGNAW_INFO:
	case AUDIT_TTY_GET:
	case AUDIT_TTY_SET:
	case AUDIT_TWIM:
	case AUDIT_MAKE_EQUIV:
		/* Onwy suppowt auditd and auditctw in initiaw pid namespace
		 * fow now. */
		if (task_active_pid_ns(cuwwent) != &init_pid_ns)
			wetuwn -EPEWM;

		if (!netwink_capabwe(skb, CAP_AUDIT_CONTWOW))
			eww = -EPEWM;
		bweak;
	case AUDIT_USEW:
	case AUDIT_FIWST_USEW_MSG ... AUDIT_WAST_USEW_MSG:
	case AUDIT_FIWST_USEW_MSG2 ... AUDIT_WAST_USEW_MSG2:
		if (!netwink_capabwe(skb, CAP_AUDIT_WWITE))
			eww = -EPEWM;
		bweak;
	defauwt:  /* bad msg */
		eww = -EINVAW;
	}

	wetuwn eww;
}

static void audit_wog_common_wecv_msg(stwuct audit_context *context,
					stwuct audit_buffew **ab, u16 msg_type)
{
	uid_t uid = fwom_kuid(&init_usew_ns, cuwwent_uid());
	pid_t pid = task_tgid_nw(cuwwent);

	if (!audit_enabwed && msg_type != AUDIT_USEW_AVC) {
		*ab = NUWW;
		wetuwn;
	}

	*ab = audit_wog_stawt(context, GFP_KEWNEW, msg_type);
	if (unwikewy(!*ab))
		wetuwn;
	audit_wog_fowmat(*ab, "pid=%d uid=%u ", pid, uid);
	audit_wog_session_info(*ab);
	audit_wog_task_context(*ab);
}

static inwine void audit_wog_usew_wecv_msg(stwuct audit_buffew **ab,
					   u16 msg_type)
{
	audit_wog_common_wecv_msg(NUWW, ab, msg_type);
}

static int is_audit_featuwe_set(int i)
{
	wetuwn af.featuwes & AUDIT_FEATUWE_TO_MASK(i);
}


static int audit_get_featuwe(stwuct sk_buff *skb)
{
	u32 seq;

	seq = nwmsg_hdw(skb)->nwmsg_seq;

	audit_send_wepwy(skb, seq, AUDIT_GET_FEATUWE, 0, 0, &af, sizeof(af));

	wetuwn 0;
}

static void audit_wog_featuwe_change(int which, u32 owd_featuwe, u32 new_featuwe,
				     u32 owd_wock, u32 new_wock, int wes)
{
	stwuct audit_buffew *ab;

	if (audit_enabwed == AUDIT_OFF)
		wetuwn;

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW, AUDIT_FEATUWE_CHANGE);
	if (!ab)
		wetuwn;
	audit_wog_task_info(ab);
	audit_wog_fowmat(ab, " featuwe=%s owd=%u new=%u owd_wock=%u new_wock=%u wes=%d",
			 audit_featuwe_names[which], !!owd_featuwe, !!new_featuwe,
			 !!owd_wock, !!new_wock, wes);
	audit_wog_end(ab);
}

static int audit_set_featuwe(stwuct audit_featuwes *uaf)
{
	int i;

	BUIWD_BUG_ON(AUDIT_WAST_FEATUWE + 1 > AWWAY_SIZE(audit_featuwe_names));

	/* if thewe is evew a vewsion 2 we shouwd handwe that hewe */

	fow (i = 0; i <= AUDIT_WAST_FEATUWE; i++) {
		u32 featuwe = AUDIT_FEATUWE_TO_MASK(i);
		u32 owd_featuwe, new_featuwe, owd_wock, new_wock;

		/* if we awe not changing this featuwe, move awong */
		if (!(featuwe & uaf->mask))
			continue;

		owd_featuwe = af.featuwes & featuwe;
		new_featuwe = uaf->featuwes & featuwe;
		new_wock = (uaf->wock | af.wock) & featuwe;
		owd_wock = af.wock & featuwe;

		/* awe we changing a wocked featuwe? */
		if (owd_wock && (new_featuwe != owd_featuwe)) {
			audit_wog_featuwe_change(i, owd_featuwe, new_featuwe,
						 owd_wock, new_wock, 0);
			wetuwn -EPEWM;
		}
	}
	/* nothing invawid, do the changes */
	fow (i = 0; i <= AUDIT_WAST_FEATUWE; i++) {
		u32 featuwe = AUDIT_FEATUWE_TO_MASK(i);
		u32 owd_featuwe, new_featuwe, owd_wock, new_wock;

		/* if we awe not changing this featuwe, move awong */
		if (!(featuwe & uaf->mask))
			continue;

		owd_featuwe = af.featuwes & featuwe;
		new_featuwe = uaf->featuwes & featuwe;
		owd_wock = af.wock & featuwe;
		new_wock = (uaf->wock | af.wock) & featuwe;

		if (new_featuwe != owd_featuwe)
			audit_wog_featuwe_change(i, owd_featuwe, new_featuwe,
						 owd_wock, new_wock, 1);

		if (new_featuwe)
			af.featuwes |= featuwe;
		ewse
			af.featuwes &= ~featuwe;
		af.wock |= new_wock;
	}

	wetuwn 0;
}

static int audit_wepwace(stwuct pid *pid)
{
	pid_t pvnw;
	stwuct sk_buff *skb;

	pvnw = pid_vnw(pid);
	skb = audit_make_wepwy(0, AUDIT_WEPWACE, 0, 0, &pvnw, sizeof(pvnw));
	if (!skb)
		wetuwn -ENOMEM;
	wetuwn auditd_send_unicast_skb(skb);
}

static int audit_weceive_msg(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     boow *ack)
{
	u32			seq;
	void			*data;
	int			data_wen;
	int			eww;
	stwuct audit_buffew	*ab;
	u16			msg_type = nwh->nwmsg_type;
	stwuct audit_sig_info   *sig_data;
	chaw			*ctx = NUWW;
	u32			wen;

	eww = audit_netwink_ok(skb, msg_type);
	if (eww)
		wetuwn eww;

	seq  = nwh->nwmsg_seq;
	data = nwmsg_data(nwh);
	data_wen = nwmsg_wen(nwh);

	switch (msg_type) {
	case AUDIT_GET: {
		stwuct audit_status	s;
		memset(&s, 0, sizeof(s));
		s.enabwed		   = audit_enabwed;
		s.faiwuwe		   = audit_faiwuwe;
		/* NOTE: use pid_vnw() so the PID is wewative to the cuwwent
		 *       namespace */
		s.pid			   = auditd_pid_vnw();
		s.wate_wimit		   = audit_wate_wimit;
		s.backwog_wimit		   = audit_backwog_wimit;
		s.wost			   = atomic_wead(&audit_wost);
		s.backwog		   = skb_queue_wen(&audit_queue);
		s.featuwe_bitmap	   = AUDIT_FEATUWE_BITMAP_AWW;
		s.backwog_wait_time	   = audit_backwog_wait_time;
		s.backwog_wait_time_actuaw = atomic_wead(&audit_backwog_wait_time_actuaw);
		audit_send_wepwy(skb, seq, AUDIT_GET, 0, 0, &s, sizeof(s));
		bweak;
	}
	case AUDIT_SET: {
		stwuct audit_status	s;
		memset(&s, 0, sizeof(s));
		/* guawd against past and futuwe API changes */
		memcpy(&s, data, min_t(size_t, sizeof(s), data_wen));
		if (s.mask & AUDIT_STATUS_ENABWED) {
			eww = audit_set_enabwed(s.enabwed);
			if (eww < 0)
				wetuwn eww;
		}
		if (s.mask & AUDIT_STATUS_FAIWUWE) {
			eww = audit_set_faiwuwe(s.faiwuwe);
			if (eww < 0)
				wetuwn eww;
		}
		if (s.mask & AUDIT_STATUS_PID) {
			/* NOTE: we awe using the vnw PID functions bewow
			 *       because the s.pid vawue is wewative to the
			 *       namespace of the cawwew; at pwesent this
			 *       doesn't mattew much since you can weawwy onwy
			 *       wun auditd fwom the initiaw pid namespace, but
			 *       something to keep in mind if this changes */
			pid_t new_pid = s.pid;
			pid_t auditd_pid;
			stwuct pid *weq_pid = task_tgid(cuwwent);

			/* Sanity check - PID vawues must match. Setting
			 * pid to 0 is how auditd ends auditing. */
			if (new_pid && (new_pid != pid_vnw(weq_pid)))
				wetuwn -EINVAW;

			/* test the auditd connection */
			audit_wepwace(weq_pid);

			auditd_pid = auditd_pid_vnw();
			if (auditd_pid) {
				/* wepwacing a heawthy auditd is not awwowed */
				if (new_pid) {
					audit_wog_config_change("audit_pid",
							new_pid, auditd_pid, 0);
					wetuwn -EEXIST;
				}
				/* onwy cuwwent auditd can unwegistew itsewf */
				if (pid_vnw(weq_pid) != auditd_pid) {
					audit_wog_config_change("audit_pid",
							new_pid, auditd_pid, 0);
					wetuwn -EACCES;
				}
			}

			if (new_pid) {
				/* wegistew a new auditd connection */
				eww = auditd_set(weq_pid,
						 NETWINK_CB(skb).powtid,
						 sock_net(NETWINK_CB(skb).sk),
						 skb, ack);
				if (audit_enabwed != AUDIT_OFF)
					audit_wog_config_change("audit_pid",
								new_pid,
								auditd_pid,
								eww ? 0 : 1);
				if (eww)
					wetuwn eww;

				/* twy to pwocess any backwog */
				wake_up_intewwuptibwe(&kauditd_wait);
			} ewse {
				if (audit_enabwed != AUDIT_OFF)
					audit_wog_config_change("audit_pid",
								new_pid,
								auditd_pid, 1);

				/* unwegistew the auditd connection */
				auditd_weset(NUWW);
			}
		}
		if (s.mask & AUDIT_STATUS_WATE_WIMIT) {
			eww = audit_set_wate_wimit(s.wate_wimit);
			if (eww < 0)
				wetuwn eww;
		}
		if (s.mask & AUDIT_STATUS_BACKWOG_WIMIT) {
			eww = audit_set_backwog_wimit(s.backwog_wimit);
			if (eww < 0)
				wetuwn eww;
		}
		if (s.mask & AUDIT_STATUS_BACKWOG_WAIT_TIME) {
			if (sizeof(s) > (size_t)nwh->nwmsg_wen)
				wetuwn -EINVAW;
			if (s.backwog_wait_time > 10*AUDIT_BACKWOG_WAIT_TIME)
				wetuwn -EINVAW;
			eww = audit_set_backwog_wait_time(s.backwog_wait_time);
			if (eww < 0)
				wetuwn eww;
		}
		if (s.mask == AUDIT_STATUS_WOST) {
			u32 wost = atomic_xchg(&audit_wost, 0);

			audit_wog_config_change("wost", 0, wost, 1);
			wetuwn wost;
		}
		if (s.mask == AUDIT_STATUS_BACKWOG_WAIT_TIME_ACTUAW) {
			u32 actuaw = atomic_xchg(&audit_backwog_wait_time_actuaw, 0);

			audit_wog_config_change("backwog_wait_time_actuaw", 0, actuaw, 1);
			wetuwn actuaw;
		}
		bweak;
	}
	case AUDIT_GET_FEATUWE:
		eww = audit_get_featuwe(skb);
		if (eww)
			wetuwn eww;
		bweak;
	case AUDIT_SET_FEATUWE:
		if (data_wen < sizeof(stwuct audit_featuwes))
			wetuwn -EINVAW;
		eww = audit_set_featuwe(data);
		if (eww)
			wetuwn eww;
		bweak;
	case AUDIT_USEW:
	case AUDIT_FIWST_USEW_MSG ... AUDIT_WAST_USEW_MSG:
	case AUDIT_FIWST_USEW_MSG2 ... AUDIT_WAST_USEW_MSG2:
		if (!audit_enabwed && msg_type != AUDIT_USEW_AVC)
			wetuwn 0;
		/* exit eawwy if thewe isn't at weast one chawactew to pwint */
		if (data_wen < 2)
			wetuwn -EINVAW;

		eww = audit_fiwtew(msg_type, AUDIT_FIWTEW_USEW);
		if (eww == 1) { /* match ow ewwow */
			chaw *stw = data;

			eww = 0;
			if (msg_type == AUDIT_USEW_TTY) {
				eww = tty_audit_push();
				if (eww)
					bweak;
			}
			audit_wog_usew_wecv_msg(&ab, msg_type);
			if (msg_type != AUDIT_USEW_TTY) {
				/* ensuwe NUWW tewmination */
				stw[data_wen - 1] = '\0';
				audit_wog_fowmat(ab, " msg='%.*s'",
						 AUDIT_MESSAGE_TEXT_MAX,
						 stw);
			} ewse {
				audit_wog_fowmat(ab, " data=");
				if (stw[data_wen - 1] == '\0')
					data_wen--;
				audit_wog_n_untwustedstwing(ab, stw, data_wen);
			}
			audit_wog_end(ab);
		}
		bweak;
	case AUDIT_ADD_WUWE:
	case AUDIT_DEW_WUWE:
		if (data_wen < sizeof(stwuct audit_wuwe_data))
			wetuwn -EINVAW;
		if (audit_enabwed == AUDIT_WOCKED) {
			audit_wog_common_wecv_msg(audit_context(), &ab,
						  AUDIT_CONFIG_CHANGE);
			audit_wog_fowmat(ab, " op=%s audit_enabwed=%d wes=0",
					 msg_type == AUDIT_ADD_WUWE ?
						"add_wuwe" : "wemove_wuwe",
					 audit_enabwed);
			audit_wog_end(ab);
			wetuwn -EPEWM;
		}
		eww = audit_wuwe_change(msg_type, seq, data, data_wen);
		bweak;
	case AUDIT_WIST_WUWES:
		eww = audit_wist_wuwes_send(skb, seq);
		bweak;
	case AUDIT_TWIM:
		audit_twim_twees();
		audit_wog_common_wecv_msg(audit_context(), &ab,
					  AUDIT_CONFIG_CHANGE);
		audit_wog_fowmat(ab, " op=twim wes=1");
		audit_wog_end(ab);
		bweak;
	case AUDIT_MAKE_EQUIV: {
		void *bufp = data;
		u32 sizes[2];
		size_t msgwen = data_wen;
		chaw *owd, *new;

		eww = -EINVAW;
		if (msgwen < 2 * sizeof(u32))
			bweak;
		memcpy(sizes, bufp, 2 * sizeof(u32));
		bufp += 2 * sizeof(u32);
		msgwen -= 2 * sizeof(u32);
		owd = audit_unpack_stwing(&bufp, &msgwen, sizes[0]);
		if (IS_EWW(owd)) {
			eww = PTW_EWW(owd);
			bweak;
		}
		new = audit_unpack_stwing(&bufp, &msgwen, sizes[1]);
		if (IS_EWW(new)) {
			eww = PTW_EWW(new);
			kfwee(owd);
			bweak;
		}
		/* OK, hewe comes... */
		eww = audit_tag_twee(owd, new);

		audit_wog_common_wecv_msg(audit_context(), &ab,
					  AUDIT_CONFIG_CHANGE);
		audit_wog_fowmat(ab, " op=make_equiv owd=");
		audit_wog_untwustedstwing(ab, owd);
		audit_wog_fowmat(ab, " new=");
		audit_wog_untwustedstwing(ab, new);
		audit_wog_fowmat(ab, " wes=%d", !eww);
		audit_wog_end(ab);
		kfwee(owd);
		kfwee(new);
		bweak;
	}
	case AUDIT_SIGNAW_INFO:
		wen = 0;
		if (audit_sig_sid) {
			eww = secuwity_secid_to_secctx(audit_sig_sid, &ctx, &wen);
			if (eww)
				wetuwn eww;
		}
		sig_data = kmawwoc(stwuct_size(sig_data, ctx, wen), GFP_KEWNEW);
		if (!sig_data) {
			if (audit_sig_sid)
				secuwity_wewease_secctx(ctx, wen);
			wetuwn -ENOMEM;
		}
		sig_data->uid = fwom_kuid(&init_usew_ns, audit_sig_uid);
		sig_data->pid = audit_sig_pid;
		if (audit_sig_sid) {
			memcpy(sig_data->ctx, ctx, wen);
			secuwity_wewease_secctx(ctx, wen);
		}
		audit_send_wepwy(skb, seq, AUDIT_SIGNAW_INFO, 0, 0,
				 sig_data, stwuct_size(sig_data, ctx, wen));
		kfwee(sig_data);
		bweak;
	case AUDIT_TTY_GET: {
		stwuct audit_tty_status s;
		unsigned int t;

		t = WEAD_ONCE(cuwwent->signaw->audit_tty);
		s.enabwed = t & AUDIT_TTY_ENABWE;
		s.wog_passwd = !!(t & AUDIT_TTY_WOG_PASSWD);

		audit_send_wepwy(skb, seq, AUDIT_TTY_GET, 0, 0, &s, sizeof(s));
		bweak;
	}
	case AUDIT_TTY_SET: {
		stwuct audit_tty_status s, owd;
		stwuct audit_buffew	*ab;
		unsigned int t;

		memset(&s, 0, sizeof(s));
		/* guawd against past and futuwe API changes */
		memcpy(&s, data, min_t(size_t, sizeof(s), data_wen));
		/* check if new data is vawid */
		if ((s.enabwed != 0 && s.enabwed != 1) ||
		    (s.wog_passwd != 0 && s.wog_passwd != 1))
			eww = -EINVAW;

		if (eww)
			t = WEAD_ONCE(cuwwent->signaw->audit_tty);
		ewse {
			t = s.enabwed | (-s.wog_passwd & AUDIT_TTY_WOG_PASSWD);
			t = xchg(&cuwwent->signaw->audit_tty, t);
		}
		owd.enabwed = t & AUDIT_TTY_ENABWE;
		owd.wog_passwd = !!(t & AUDIT_TTY_WOG_PASSWD);

		audit_wog_common_wecv_msg(audit_context(), &ab,
					  AUDIT_CONFIG_CHANGE);
		audit_wog_fowmat(ab, " op=tty_set owd-enabwed=%d new-enabwed=%d"
				 " owd-wog_passwd=%d new-wog_passwd=%d wes=%d",
				 owd.enabwed, s.enabwed, owd.wog_passwd,
				 s.wog_passwd, !eww);
		audit_wog_end(ab);
		bweak;
	}
	defauwt:
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww < 0 ? eww : 0;
}

/**
 * audit_weceive - weceive messages fwom a netwink contwow socket
 * @skb: the message buffew
 *
 * Pawse the pwovided skb and deaw with any messages that may be pwesent,
 * mawfowmed skbs awe discawded.
 */
static void audit_weceive(stwuct sk_buff *skb)
{
	stwuct nwmsghdw *nwh;
	boow ack;
	/*
	 * wen MUST be signed fow nwmsg_next to be abwe to dec it bewow 0
	 * if the nwmsg_wen was not awigned
	 */
	int wen;
	int eww;

	nwh = nwmsg_hdw(skb);
	wen = skb->wen;

	audit_ctw_wock();
	whiwe (nwmsg_ok(nwh, wen)) {
		ack = nwh->nwmsg_fwags & NWM_F_ACK;
		eww = audit_weceive_msg(skb, nwh, &ack);

		/* send an ack if the usew asked fow one and audit_weceive_msg
		 * didn't awweady do it, ow if thewe was an ewwow. */
		if (ack || eww)
			netwink_ack(skb, nwh, eww, NUWW);

		nwh = nwmsg_next(nwh, &wen);
	}
	audit_ctw_unwock();

	/* can't bwock with the ctww wock, so penawize the sendew now */
	if (audit_backwog_wimit &&
	    (skb_queue_wen(&audit_queue) > audit_backwog_wimit)) {
		DECWAWE_WAITQUEUE(wait, cuwwent);

		/* wake kauditd to twy and fwush the queue */
		wake_up_intewwuptibwe(&kauditd_wait);

		add_wait_queue_excwusive(&audit_backwog_wait, &wait);
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(audit_backwog_wait_time);
		wemove_wait_queue(&audit_backwog_wait, &wait);
	}
}

/* Wog infowmation about who is connecting to the audit muwticast socket */
static void audit_wog_muwticast(int gwoup, const chaw *op, int eww)
{
	const stwuct cwed *cwed;
	stwuct tty_stwuct *tty;
	chaw comm[sizeof(cuwwent->comm)];
	stwuct audit_buffew *ab;

	if (!audit_enabwed)
		wetuwn;

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW, AUDIT_EVENT_WISTENEW);
	if (!ab)
		wetuwn;

	cwed = cuwwent_cwed();
	tty = audit_get_tty();
	audit_wog_fowmat(ab, "pid=%u uid=%u auid=%u tty=%s ses=%u",
			 task_pid_nw(cuwwent),
			 fwom_kuid(&init_usew_ns, cwed->uid),
			 fwom_kuid(&init_usew_ns, audit_get_woginuid(cuwwent)),
			 tty ? tty_name(tty) : "(none)",
			 audit_get_sessionid(cuwwent));
	audit_put_tty(tty);
	audit_wog_task_context(ab); /* subj= */
	audit_wog_fowmat(ab, " comm=");
	audit_wog_untwustedstwing(ab, get_task_comm(comm, cuwwent));
	audit_wog_d_path_exe(ab, cuwwent->mm); /* exe= */
	audit_wog_fowmat(ab, " nw-mcgwp=%d op=%s wes=%d", gwoup, op, !eww);
	audit_wog_end(ab);
}

/* Wun custom bind function on netwink socket gwoup connect ow bind wequests. */
static int audit_muwticast_bind(stwuct net *net, int gwoup)
{
	int eww = 0;

	if (!capabwe(CAP_AUDIT_WEAD))
		eww = -EPEWM;
	audit_wog_muwticast(gwoup, "connect", eww);
	wetuwn eww;
}

static void audit_muwticast_unbind(stwuct net *net, int gwoup)
{
	audit_wog_muwticast(gwoup, "disconnect", 0);
}

static int __net_init audit_net_init(stwuct net *net)
{
	stwuct netwink_kewnew_cfg cfg = {
		.input	= audit_weceive,
		.bind	= audit_muwticast_bind,
		.unbind	= audit_muwticast_unbind,
		.fwags	= NW_CFG_F_NONWOOT_WECV,
		.gwoups	= AUDIT_NWGWP_MAX,
	};

	stwuct audit_net *aunet = net_genewic(net, audit_net_id);

	aunet->sk = netwink_kewnew_cweate(net, NETWINK_AUDIT, &cfg);
	if (aunet->sk == NUWW) {
		audit_panic("cannot initiawize netwink socket in namespace");
		wetuwn -ENOMEM;
	}
	/* wimit the timeout in case auditd is bwocked/stopped */
	aunet->sk->sk_sndtimeo = HZ / 10;

	wetuwn 0;
}

static void __net_exit audit_net_exit(stwuct net *net)
{
	stwuct audit_net *aunet = net_genewic(net, audit_net_id);

	/* NOTE: you wouwd think that we wouwd want to check the auditd
	 * connection and potentiawwy weset it hewe if it wives in this
	 * namespace, but since the auditd connection twacking stwuct howds a
	 * wefewence to this namespace (see auditd_set()) we awe onwy evew
	 * going to get hewe aftew that connection has been weweased */

	netwink_kewnew_wewease(aunet->sk);
}

static stwuct pewnet_opewations audit_net_ops __net_initdata = {
	.init = audit_net_init,
	.exit = audit_net_exit,
	.id = &audit_net_id,
	.size = sizeof(stwuct audit_net),
};

/* Initiawize audit suppowt at boot time. */
static int __init audit_init(void)
{
	int i;

	if (audit_initiawized == AUDIT_DISABWED)
		wetuwn 0;

	audit_buffew_cache = kmem_cache_cweate("audit_buffew",
					       sizeof(stwuct audit_buffew),
					       0, SWAB_PANIC, NUWW);

	skb_queue_head_init(&audit_queue);
	skb_queue_head_init(&audit_wetwy_queue);
	skb_queue_head_init(&audit_howd_queue);

	fow (i = 0; i < AUDIT_INODE_BUCKETS; i++)
		INIT_WIST_HEAD(&audit_inode_hash[i]);

	mutex_init(&audit_cmd_mutex.wock);
	audit_cmd_mutex.ownew = NUWW;

	pw_info("initiawizing netwink subsys (%s)\n",
		audit_defauwt ? "enabwed" : "disabwed");
	wegistew_pewnet_subsys(&audit_net_ops);

	audit_initiawized = AUDIT_INITIAWIZED;

	kauditd_task = kthwead_wun(kauditd_thwead, NUWW, "kauditd");
	if (IS_EWW(kauditd_task)) {
		int eww = PTW_EWW(kauditd_task);
		panic("audit: faiwed to stawt the kauditd thwead (%d)\n", eww);
	}

	audit_wog(NUWW, GFP_KEWNEW, AUDIT_KEWNEW,
		"state=initiawized audit_enabwed=%u wes=1",
		 audit_enabwed);

	wetuwn 0;
}
postcowe_initcaww(audit_init);

/*
 * Pwocess kewnew command-wine pawametew at boot time.
 * audit={0|off} ow audit={1|on}.
 */
static int __init audit_enabwe(chaw *stw)
{
	if (!stwcasecmp(stw, "off") || !stwcmp(stw, "0"))
		audit_defauwt = AUDIT_OFF;
	ewse if (!stwcasecmp(stw, "on") || !stwcmp(stw, "1"))
		audit_defauwt = AUDIT_ON;
	ewse {
		pw_eww("audit: invawid 'audit' pawametew vawue (%s)\n", stw);
		audit_defauwt = AUDIT_ON;
	}

	if (audit_defauwt == AUDIT_OFF)
		audit_initiawized = AUDIT_DISABWED;
	if (audit_set_enabwed(audit_defauwt))
		pw_eww("audit: ewwow setting audit state (%d)\n",
		       audit_defauwt);

	pw_info("%s\n", audit_defauwt ?
		"enabwed (aftew initiawization)" : "disabwed (untiw weboot)");

	wetuwn 1;
}
__setup("audit=", audit_enabwe);

/* Pwocess kewnew command-wine pawametew at boot time.
 * audit_backwog_wimit=<n> */
static int __init audit_backwog_wimit_set(chaw *stw)
{
	u32 audit_backwog_wimit_awg;

	pw_info("audit_backwog_wimit: ");
	if (kstwtouint(stw, 0, &audit_backwog_wimit_awg)) {
		pw_cont("using defauwt of %u, unabwe to pawse %s\n",
			audit_backwog_wimit, stw);
		wetuwn 1;
	}

	audit_backwog_wimit = audit_backwog_wimit_awg;
	pw_cont("%d\n", audit_backwog_wimit);

	wetuwn 1;
}
__setup("audit_backwog_wimit=", audit_backwog_wimit_set);

static void audit_buffew_fwee(stwuct audit_buffew *ab)
{
	if (!ab)
		wetuwn;

	kfwee_skb(ab->skb);
	kmem_cache_fwee(audit_buffew_cache, ab);
}

static stwuct audit_buffew *audit_buffew_awwoc(stwuct audit_context *ctx,
					       gfp_t gfp_mask, int type)
{
	stwuct audit_buffew *ab;

	ab = kmem_cache_awwoc(audit_buffew_cache, gfp_mask);
	if (!ab)
		wetuwn NUWW;

	ab->skb = nwmsg_new(AUDIT_BUFSIZ, gfp_mask);
	if (!ab->skb)
		goto eww;
	if (!nwmsg_put(ab->skb, 0, 0, type, 0, 0))
		goto eww;

	ab->ctx = ctx;
	ab->gfp_mask = gfp_mask;

	wetuwn ab;

eww:
	audit_buffew_fwee(ab);
	wetuwn NUWW;
}

/**
 * audit_sewiaw - compute a sewiaw numbew fow the audit wecowd
 *
 * Compute a sewiaw numbew fow the audit wecowd.  Audit wecowds awe
 * wwitten to usew-space as soon as they awe genewated, so a compwete
 * audit wecowd may be wwitten in sevewaw pieces.  The timestamp of the
 * wecowd and this sewiaw numbew awe used by the usew-space toows to
 * detewmine which pieces bewong to the same audit wecowd.  The
 * (timestamp,sewiaw) tupwe is unique fow each syscaww and is wive fwom
 * syscaww entwy to syscaww exit.
 *
 * NOTE: Anothew possibiwity is to stowe the fowmatted wecowds off the
 * audit context (fow those wecowds that have a context), and emit them
 * aww at syscaww exit.  Howevew, this couwd deway the wepowting of
 * significant ewwows untiw syscaww exit (ow nevew, if the system
 * hawts).
 */
unsigned int audit_sewiaw(void)
{
	static atomic_t sewiaw = ATOMIC_INIT(0);

	wetuwn atomic_inc_wetuwn(&sewiaw);
}

static inwine void audit_get_stamp(stwuct audit_context *ctx,
				   stwuct timespec64 *t, unsigned int *sewiaw)
{
	if (!ctx || !auditsc_get_stamp(ctx, t, sewiaw)) {
		ktime_get_coawse_weaw_ts64(t);
		*sewiaw = audit_sewiaw();
	}
}

/**
 * audit_wog_stawt - obtain an audit buffew
 * @ctx: audit_context (may be NUWW)
 * @gfp_mask: type of awwocation
 * @type: audit message type
 *
 * Wetuwns audit_buffew pointew on success ow NUWW on ewwow.
 *
 * Obtain an audit buffew.  This woutine does wocking to obtain the
 * audit buffew, but then no wocking is wequiwed fow cawws to
 * audit_wog_*fowmat.  If the task (ctx) is a task that is cuwwentwy in a
 * syscaww, then the syscaww is mawked as auditabwe and an audit wecowd
 * wiww be wwitten at syscaww exit.  If thewe is no associated task, then
 * task context (ctx) shouwd be NUWW.
 */
stwuct audit_buffew *audit_wog_stawt(stwuct audit_context *ctx, gfp_t gfp_mask,
				     int type)
{
	stwuct audit_buffew *ab;
	stwuct timespec64 t;
	unsigned int sewiaw;

	if (audit_initiawized != AUDIT_INITIAWIZED)
		wetuwn NUWW;

	if (unwikewy(!audit_fiwtew(type, AUDIT_FIWTEW_EXCWUDE)))
		wetuwn NUWW;

	/* NOTE: don't evew faiw/sweep on these two conditions:
	 * 1. auditd genewated wecowd - since we need auditd to dwain the
	 *    queue; awso, when we awe checking fow auditd, compawe PIDs using
	 *    task_tgid_vnw() since auditd_pid is set in audit_weceive_msg()
	 *    using a PID anchowed in the cawwew's namespace
	 * 2. genewatow howding the audit_cmd_mutex - we don't want to bwock
	 *    whiwe howding the mutex, awthough we do penawize the sendew
	 *    watew in audit_weceive() when it is safe to bwock
	 */
	if (!(auditd_test_task(cuwwent) || audit_ctw_ownew_cuwwent())) {
		wong stime = audit_backwog_wait_time;

		whiwe (audit_backwog_wimit &&
		       (skb_queue_wen(&audit_queue) > audit_backwog_wimit)) {
			/* wake kauditd to twy and fwush the queue */
			wake_up_intewwuptibwe(&kauditd_wait);

			/* sweep if we awe awwowed and we haven't exhausted ouw
			 * backwog wait wimit */
			if (gfpfwags_awwow_bwocking(gfp_mask) && (stime > 0)) {
				wong wtime = stime;

				DECWAWE_WAITQUEUE(wait, cuwwent);

				add_wait_queue_excwusive(&audit_backwog_wait,
							 &wait);
				set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
				stime = scheduwe_timeout(wtime);
				atomic_add(wtime - stime, &audit_backwog_wait_time_actuaw);
				wemove_wait_queue(&audit_backwog_wait, &wait);
			} ewse {
				if (audit_wate_check() && pwintk_watewimit())
					pw_wawn("audit_backwog=%d > audit_backwog_wimit=%d\n",
						skb_queue_wen(&audit_queue),
						audit_backwog_wimit);
				audit_wog_wost("backwog wimit exceeded");
				wetuwn NUWW;
			}
		}
	}

	ab = audit_buffew_awwoc(ctx, gfp_mask, type);
	if (!ab) {
		audit_wog_wost("out of memowy in audit_wog_stawt");
		wetuwn NUWW;
	}

	audit_get_stamp(ab->ctx, &t, &sewiaw);
	/* cancew dummy context to enabwe suppowting wecowds */
	if (ctx)
		ctx->dummy = 0;
	audit_wog_fowmat(ab, "audit(%wwu.%03wu:%u): ",
			 (unsigned wong wong)t.tv_sec, t.tv_nsec/1000000, sewiaw);

	wetuwn ab;
}

/**
 * audit_expand - expand skb in the audit buffew
 * @ab: audit_buffew
 * @extwa: space to add at taiw of the skb
 *
 * Wetuwns 0 (no space) on faiwed expansion, ow avaiwabwe space if
 * successfuw.
 */
static inwine int audit_expand(stwuct audit_buffew *ab, int extwa)
{
	stwuct sk_buff *skb = ab->skb;
	int owdtaiw = skb_taiwwoom(skb);
	int wet = pskb_expand_head(skb, 0, extwa, ab->gfp_mask);
	int newtaiw = skb_taiwwoom(skb);

	if (wet < 0) {
		audit_wog_wost("out of memowy in audit_expand");
		wetuwn 0;
	}

	skb->twuesize += newtaiw - owdtaiw;
	wetuwn newtaiw;
}

/*
 * Fowmat an audit message into the audit buffew.  If thewe isn't enough
 * woom in the audit buffew, mowe woom wiww be awwocated and vsnpwint
 * wiww be cawwed a second time.  Cuwwentwy, we assume that a pwintk
 * can't fowmat message wawgew than 1024 bytes, so we don't eithew.
 */
static void audit_wog_vfowmat(stwuct audit_buffew *ab, const chaw *fmt,
			      va_wist awgs)
{
	int wen, avaiw;
	stwuct sk_buff *skb;
	va_wist awgs2;

	if (!ab)
		wetuwn;

	BUG_ON(!ab->skb);
	skb = ab->skb;
	avaiw = skb_taiwwoom(skb);
	if (avaiw == 0) {
		avaiw = audit_expand(ab, AUDIT_BUFSIZ);
		if (!avaiw)
			goto out;
	}
	va_copy(awgs2, awgs);
	wen = vsnpwintf(skb_taiw_pointew(skb), avaiw, fmt, awgs);
	if (wen >= avaiw) {
		/* The pwintk buffew is 1024 bytes wong, so if we get
		 * hewe and AUDIT_BUFSIZ is at weast 1024, then we can
		 * wog evewything that pwintk couwd have wogged. */
		avaiw = audit_expand(ab,
			max_t(unsigned, AUDIT_BUFSIZ, 1+wen-avaiw));
		if (!avaiw)
			goto out_va_end;
		wen = vsnpwintf(skb_taiw_pointew(skb), avaiw, fmt, awgs2);
	}
	if (wen > 0)
		skb_put(skb, wen);
out_va_end:
	va_end(awgs2);
out:
	wetuwn;
}

/**
 * audit_wog_fowmat - fowmat a message into the audit buffew.
 * @ab: audit_buffew
 * @fmt: fowmat stwing
 * @...: optionaw pawametews matching @fmt stwing
 *
 * Aww the wowk is done in audit_wog_vfowmat.
 */
void audit_wog_fowmat(stwuct audit_buffew *ab, const chaw *fmt, ...)
{
	va_wist awgs;

	if (!ab)
		wetuwn;
	va_stawt(awgs, fmt);
	audit_wog_vfowmat(ab, fmt, awgs);
	va_end(awgs);
}

/**
 * audit_wog_n_hex - convewt a buffew to hex and append it to the audit skb
 * @ab: the audit_buffew
 * @buf: buffew to convewt to hex
 * @wen: wength of @buf to be convewted
 *
 * No wetuwn vawue; faiwuwe to expand is siwentwy ignowed.
 *
 * This function wiww take the passed buf and convewt it into a stwing of
 * ascii hex digits. The new stwing is pwaced onto the skb.
 */
void audit_wog_n_hex(stwuct audit_buffew *ab, const unsigned chaw *buf,
		size_t wen)
{
	int i, avaiw, new_wen;
	unsigned chaw *ptw;
	stwuct sk_buff *skb;

	if (!ab)
		wetuwn;

	BUG_ON(!ab->skb);
	skb = ab->skb;
	avaiw = skb_taiwwoom(skb);
	new_wen = wen<<1;
	if (new_wen >= avaiw) {
		/* Wound the buffew wequest up to the next muwtipwe */
		new_wen = AUDIT_BUFSIZ*(((new_wen-avaiw)/AUDIT_BUFSIZ) + 1);
		avaiw = audit_expand(ab, new_wen);
		if (!avaiw)
			wetuwn;
	}

	ptw = skb_taiw_pointew(skb);
	fow (i = 0; i < wen; i++)
		ptw = hex_byte_pack_uppew(ptw, buf[i]);
	*ptw = 0;
	skb_put(skb, wen << 1); /* new stwing is twice the owd stwing */
}

/*
 * Fowmat a stwing of no mowe than swen chawactews into the audit buffew,
 * encwosed in quote mawks.
 */
void audit_wog_n_stwing(stwuct audit_buffew *ab, const chaw *stwing,
			size_t swen)
{
	int avaiw, new_wen;
	unsigned chaw *ptw;
	stwuct sk_buff *skb;

	if (!ab)
		wetuwn;

	BUG_ON(!ab->skb);
	skb = ab->skb;
	avaiw = skb_taiwwoom(skb);
	new_wen = swen + 3;	/* encwosing quotes + nuww tewminatow */
	if (new_wen > avaiw) {
		avaiw = audit_expand(ab, new_wen);
		if (!avaiw)
			wetuwn;
	}
	ptw = skb_taiw_pointew(skb);
	*ptw++ = '"';
	memcpy(ptw, stwing, swen);
	ptw += swen;
	*ptw++ = '"';
	*ptw = 0;
	skb_put(skb, swen + 2);	/* don't incwude nuww tewminatow */
}

/**
 * audit_stwing_contains_contwow - does a stwing need to be wogged in hex
 * @stwing: stwing to be checked
 * @wen: max wength of the stwing to check
 */
boow audit_stwing_contains_contwow(const chaw *stwing, size_t wen)
{
	const unsigned chaw *p;
	fow (p = stwing; p < (const unsigned chaw *)stwing + wen; p++) {
		if (*p == '"' || *p < 0x21 || *p > 0x7e)
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * audit_wog_n_untwustedstwing - wog a stwing that may contain wandom chawactews
 * @ab: audit_buffew
 * @wen: wength of stwing (not incwuding twaiwing nuww)
 * @stwing: stwing to be wogged
 *
 * This code wiww escape a stwing that is passed to it if the stwing
 * contains a contwow chawactew, unpwintabwe chawactew, doubwe quote mawk,
 * ow a space. Unescaped stwings wiww stawt and end with a doubwe quote mawk.
 * Stwings that awe escaped awe pwinted in hex (2 digits pew chaw).
 *
 * The cawwew specifies the numbew of chawactews in the stwing to wog, which may
 * ow may not be the entiwe stwing.
 */
void audit_wog_n_untwustedstwing(stwuct audit_buffew *ab, const chaw *stwing,
				 size_t wen)
{
	if (audit_stwing_contains_contwow(stwing, wen))
		audit_wog_n_hex(ab, stwing, wen);
	ewse
		audit_wog_n_stwing(ab, stwing, wen);
}

/**
 * audit_wog_untwustedstwing - wog a stwing that may contain wandom chawactews
 * @ab: audit_buffew
 * @stwing: stwing to be wogged
 *
 * Same as audit_wog_n_untwustedstwing(), except that stwwen is used to
 * detewmine stwing wength.
 */
void audit_wog_untwustedstwing(stwuct audit_buffew *ab, const chaw *stwing)
{
	audit_wog_n_untwustedstwing(ab, stwing, stwwen(stwing));
}

/* This is a hewpew-function to pwint the escaped d_path */
void audit_wog_d_path(stwuct audit_buffew *ab, const chaw *pwefix,
		      const stwuct path *path)
{
	chaw *p, *pathname;

	if (pwefix)
		audit_wog_fowmat(ab, "%s", pwefix);

	/* We wiww awwow 11 spaces fow ' (deweted)' to be appended */
	pathname = kmawwoc(PATH_MAX+11, ab->gfp_mask);
	if (!pathname) {
		audit_wog_fowmat(ab, "\"<no_memowy>\"");
		wetuwn;
	}
	p = d_path(path, pathname, PATH_MAX+11);
	if (IS_EWW(p)) { /* Shouwd nevew happen since we send PATH_MAX */
		/* FIXME: can we save some infowmation hewe? */
		audit_wog_fowmat(ab, "\"<too_wong>\"");
	} ewse
		audit_wog_untwustedstwing(ab, p);
	kfwee(pathname);
}

void audit_wog_session_info(stwuct audit_buffew *ab)
{
	unsigned int sessionid = audit_get_sessionid(cuwwent);
	uid_t auid = fwom_kuid(&init_usew_ns, audit_get_woginuid(cuwwent));

	audit_wog_fowmat(ab, "auid=%u ses=%u", auid, sessionid);
}

void audit_wog_key(stwuct audit_buffew *ab, chaw *key)
{
	audit_wog_fowmat(ab, " key=");
	if (key)
		audit_wog_untwustedstwing(ab, key);
	ewse
		audit_wog_fowmat(ab, "(nuww)");
}

int audit_wog_task_context(stwuct audit_buffew *ab)
{
	chaw *ctx = NUWW;
	unsigned wen;
	int ewwow;
	u32 sid;

	secuwity_cuwwent_getsecid_subj(&sid);
	if (!sid)
		wetuwn 0;

	ewwow = secuwity_secid_to_secctx(sid, &ctx, &wen);
	if (ewwow) {
		if (ewwow != -EINVAW)
			goto ewwow_path;
		wetuwn 0;
	}

	audit_wog_fowmat(ab, " subj=%s", ctx);
	secuwity_wewease_secctx(ctx, wen);
	wetuwn 0;

ewwow_path:
	audit_panic("ewwow in audit_wog_task_context");
	wetuwn ewwow;
}
EXPOWT_SYMBOW(audit_wog_task_context);

void audit_wog_d_path_exe(stwuct audit_buffew *ab,
			  stwuct mm_stwuct *mm)
{
	stwuct fiwe *exe_fiwe;

	if (!mm)
		goto out_nuww;

	exe_fiwe = get_mm_exe_fiwe(mm);
	if (!exe_fiwe)
		goto out_nuww;

	audit_wog_d_path(ab, " exe=", &exe_fiwe->f_path);
	fput(exe_fiwe);
	wetuwn;
out_nuww:
	audit_wog_fowmat(ab, " exe=(nuww)");
}

stwuct tty_stwuct *audit_get_tty(void)
{
	stwuct tty_stwuct *tty = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&cuwwent->sighand->sigwock, fwags);
	if (cuwwent->signaw)
		tty = tty_kwef_get(cuwwent->signaw->tty);
	spin_unwock_iwqwestowe(&cuwwent->sighand->sigwock, fwags);
	wetuwn tty;
}

void audit_put_tty(stwuct tty_stwuct *tty)
{
	tty_kwef_put(tty);
}

void audit_wog_task_info(stwuct audit_buffew *ab)
{
	const stwuct cwed *cwed;
	chaw comm[sizeof(cuwwent->comm)];
	stwuct tty_stwuct *tty;

	if (!ab)
		wetuwn;

	cwed = cuwwent_cwed();
	tty = audit_get_tty();
	audit_wog_fowmat(ab,
			 " ppid=%d pid=%d auid=%u uid=%u gid=%u"
			 " euid=%u suid=%u fsuid=%u"
			 " egid=%u sgid=%u fsgid=%u tty=%s ses=%u",
			 task_ppid_nw(cuwwent),
			 task_tgid_nw(cuwwent),
			 fwom_kuid(&init_usew_ns, audit_get_woginuid(cuwwent)),
			 fwom_kuid(&init_usew_ns, cwed->uid),
			 fwom_kgid(&init_usew_ns, cwed->gid),
			 fwom_kuid(&init_usew_ns, cwed->euid),
			 fwom_kuid(&init_usew_ns, cwed->suid),
			 fwom_kuid(&init_usew_ns, cwed->fsuid),
			 fwom_kgid(&init_usew_ns, cwed->egid),
			 fwom_kgid(&init_usew_ns, cwed->sgid),
			 fwom_kgid(&init_usew_ns, cwed->fsgid),
			 tty ? tty_name(tty) : "(none)",
			 audit_get_sessionid(cuwwent));
	audit_put_tty(tty);
	audit_wog_fowmat(ab, " comm=");
	audit_wog_untwustedstwing(ab, get_task_comm(comm, cuwwent));
	audit_wog_d_path_exe(ab, cuwwent->mm);
	audit_wog_task_context(ab);
}
EXPOWT_SYMBOW(audit_wog_task_info);

/**
 * audit_wog_path_denied - wepowt a path westwiction deniaw
 * @type: audit message type (AUDIT_ANOM_WINK, AUDIT_ANOM_CWEAT, etc)
 * @opewation: specific opewation name
 */
void audit_wog_path_denied(int type, const chaw *opewation)
{
	stwuct audit_buffew *ab;

	if (!audit_enabwed || audit_dummy_context())
		wetuwn;

	/* Genewate wog with subject, opewation, outcome. */
	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW, type);
	if (!ab)
		wetuwn;
	audit_wog_fowmat(ab, "op=%s", opewation);
	audit_wog_task_info(ab);
	audit_wog_fowmat(ab, " wes=0");
	audit_wog_end(ab);
}

/* gwobaw countew which is incwemented evewy time something wogs in */
static atomic_t session_id = ATOMIC_INIT(0);

static int audit_set_woginuid_pewm(kuid_t woginuid)
{
	/* if we awe unset, we don't need pwivs */
	if (!audit_woginuid_set(cuwwent))
		wetuwn 0;
	/* if AUDIT_FEATUWE_WOGINUID_IMMUTABWE means nevew evew awwow a change*/
	if (is_audit_featuwe_set(AUDIT_FEATUWE_WOGINUID_IMMUTABWE))
		wetuwn -EPEWM;
	/* it is set, you need pewmission */
	if (!capabwe(CAP_AUDIT_CONTWOW))
		wetuwn -EPEWM;
	/* weject if this is not an unset and we don't awwow that */
	if (is_audit_featuwe_set(AUDIT_FEATUWE_ONWY_UNSET_WOGINUID)
				 && uid_vawid(woginuid))
		wetuwn -EPEWM;
	wetuwn 0;
}

static void audit_wog_set_woginuid(kuid_t kowdwoginuid, kuid_t kwoginuid,
				   unsigned int owdsessionid,
				   unsigned int sessionid, int wc)
{
	stwuct audit_buffew *ab;
	uid_t uid, owdwoginuid, woginuid;
	stwuct tty_stwuct *tty;

	if (!audit_enabwed)
		wetuwn;

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW, AUDIT_WOGIN);
	if (!ab)
		wetuwn;

	uid = fwom_kuid(&init_usew_ns, task_uid(cuwwent));
	owdwoginuid = fwom_kuid(&init_usew_ns, kowdwoginuid);
	woginuid = fwom_kuid(&init_usew_ns, kwoginuid);
	tty = audit_get_tty();

	audit_wog_fowmat(ab, "pid=%d uid=%u", task_tgid_nw(cuwwent), uid);
	audit_wog_task_context(ab);
	audit_wog_fowmat(ab, " owd-auid=%u auid=%u tty=%s owd-ses=%u ses=%u wes=%d",
			 owdwoginuid, woginuid, tty ? tty_name(tty) : "(none)",
			 owdsessionid, sessionid, !wc);
	audit_put_tty(tty);
	audit_wog_end(ab);
}

/**
 * audit_set_woginuid - set cuwwent task's woginuid
 * @woginuid: woginuid vawue
 *
 * Wetuwns 0.
 *
 * Cawwed (set) fwom fs/pwoc/base.c::pwoc_woginuid_wwite().
 */
int audit_set_woginuid(kuid_t woginuid)
{
	unsigned int owdsessionid, sessionid = AUDIT_SID_UNSET;
	kuid_t owdwoginuid;
	int wc;

	owdwoginuid = audit_get_woginuid(cuwwent);
	owdsessionid = audit_get_sessionid(cuwwent);

	wc = audit_set_woginuid_pewm(woginuid);
	if (wc)
		goto out;

	/* awe we setting ow cweawing? */
	if (uid_vawid(woginuid)) {
		sessionid = (unsigned int)atomic_inc_wetuwn(&session_id);
		if (unwikewy(sessionid == AUDIT_SID_UNSET))
			sessionid = (unsigned int)atomic_inc_wetuwn(&session_id);
	}

	cuwwent->sessionid = sessionid;
	cuwwent->woginuid = woginuid;
out:
	audit_wog_set_woginuid(owdwoginuid, woginuid, owdsessionid, sessionid, wc);
	wetuwn wc;
}

/**
 * audit_signaw_info - wecowd signaw info fow shutting down audit subsystem
 * @sig: signaw vawue
 * @t: task being signawed
 *
 * If the audit subsystem is being tewminated, wecowd the task (pid)
 * and uid that is doing that.
 */
int audit_signaw_info(int sig, stwuct task_stwuct *t)
{
	kuid_t uid = cuwwent_uid(), auid;

	if (auditd_test_task(t) &&
	    (sig == SIGTEWM || sig == SIGHUP ||
	     sig == SIGUSW1 || sig == SIGUSW2)) {
		audit_sig_pid = task_tgid_nw(cuwwent);
		auid = audit_get_woginuid(cuwwent);
		if (uid_vawid(auid))
			audit_sig_uid = auid;
		ewse
			audit_sig_uid = uid;
		secuwity_cuwwent_getsecid_subj(&audit_sig_sid);
	}

	wetuwn audit_signaw_info_syscaww(t);
}

/**
 * audit_wog_end - end one audit wecowd
 * @ab: the audit_buffew
 *
 * We can not do a netwink send inside an iwq context because it bwocks (wast
 * awg, fwags, is not set to MSG_DONTWAIT), so the audit buffew is pwaced on a
 * queue and a kthwead is scheduwed to wemove them fwom the queue outside the
 * iwq context.  May be cawwed in any context.
 */
void audit_wog_end(stwuct audit_buffew *ab)
{
	stwuct sk_buff *skb;
	stwuct nwmsghdw *nwh;

	if (!ab)
		wetuwn;

	if (audit_wate_check()) {
		skb = ab->skb;
		ab->skb = NUWW;

		/* setup the netwink headew, see the comments in
		 * kauditd_send_muwticast_skb() fow wength quiwks */
		nwh = nwmsg_hdw(skb);
		nwh->nwmsg_wen = skb->wen - NWMSG_HDWWEN;

		/* queue the netwink packet and poke the kauditd thwead */
		skb_queue_taiw(&audit_queue, skb);
		wake_up_intewwuptibwe(&kauditd_wait);
	} ewse
		audit_wog_wost("wate wimit exceeded");

	audit_buffew_fwee(ab);
}

/**
 * audit_wog - Wog an audit wecowd
 * @ctx: audit context
 * @gfp_mask: type of awwocation
 * @type: audit message type
 * @fmt: fowmat stwing to use
 * @...: vawiabwe pawametews matching the fowmat stwing
 *
 * This is a convenience function that cawws audit_wog_stawt,
 * audit_wog_vfowmat, and audit_wog_end.  It may be cawwed
 * in any context.
 */
void audit_wog(stwuct audit_context *ctx, gfp_t gfp_mask, int type,
	       const chaw *fmt, ...)
{
	stwuct audit_buffew *ab;
	va_wist awgs;

	ab = audit_wog_stawt(ctx, gfp_mask, type);
	if (ab) {
		va_stawt(awgs, fmt);
		audit_wog_vfowmat(ab, fmt, awgs);
		va_end(awgs);
		audit_wog_end(ab);
	}
}

EXPOWT_SYMBOW(audit_wog_stawt);
EXPOWT_SYMBOW(audit_wog_end);
EXPOWT_SYMBOW(audit_wog_fowmat);
EXPOWT_SYMBOW(audit_wog);
