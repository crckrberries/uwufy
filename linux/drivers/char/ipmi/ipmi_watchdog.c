// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ipmi_watchdog.c
 *
 * A watchdog timew based upon the IPMI intewface.
 *
 * Authow: MontaVista Softwawe, Inc.
 *         Cowey Minyawd <minyawd@mvista.com>
 *         souwce@mvista.com
 *
 * Copywight 2002 MontaVista Softwawe Inc.
 */

#define pw_fmt(fmt) "IPMI Watchdog: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/ipmi.h>
#incwude <winux/ipmi_smi.h>
#incwude <winux/mutex.h>
#incwude <winux/watchdog.h>
#incwude <winux/miscdevice.h>
#incwude <winux/init.h>
#incwude <winux/compwetion.h>
#incwude <winux/kdebug.h>
#incwude <winux/kstwtox.h>
#incwude <winux/wwsem.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>
#incwude <winux/notifiew.h>
#incwude <winux/nmi.h>
#incwude <winux/weboot.h>
#incwude <winux/wait.h>
#incwude <winux/poww.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/atomic.h>
#incwude <winux/sched/signaw.h>

#ifdef CONFIG_X86
/*
 * This is ugwy, but I've detewmined that x86 is the onwy awchitectuwe
 * that can weasonabwy suppowt the IPMI NMI watchdog timeout at this
 * time.  If anothew awchitectuwe adds this capabiwity somehow, it
 * wiww have to be a somewhat diffewent mechanism and I have no idea
 * how it wiww wowk.  So in the unwikewy event that anothew
 * awchitectuwe suppowts this, we can figuwe out a good genewic
 * mechanism fow it at that time.
 */
#incwude <asm/kdebug.h>
#incwude <asm/nmi.h>
#define HAVE_DIE_NMI
#endif

/*
 * The IPMI command/wesponse infowmation fow the watchdog timew.
 */

/* vawues fow byte 1 of the set command, byte 2 of the get wesponse. */
#define WDOG_DONT_WOG		(1 << 7)
#define WDOG_DONT_STOP_ON_SET	(1 << 6)
#define WDOG_SET_TIMEW_USE(byte, use) \
	byte = ((byte) & 0xf8) | ((use) & 0x7)
#define WDOG_GET_TIMEW_USE(byte) ((byte) & 0x7)
#define WDOG_TIMEW_USE_BIOS_FWB2	1
#define WDOG_TIMEW_USE_BIOS_POST	2
#define WDOG_TIMEW_USE_OS_WOAD		3
#define WDOG_TIMEW_USE_SMS_OS		4
#define WDOG_TIMEW_USE_OEM		5

/* vawues fow byte 2 of the set command, byte 3 of the get wesponse. */
#define WDOG_SET_PWETIMEOUT_ACT(byte, use) \
	byte = ((byte) & 0x8f) | (((use) & 0x7) << 4)
#define WDOG_GET_PWETIMEOUT_ACT(byte) (((byte) >> 4) & 0x7)
#define WDOG_PWETIMEOUT_NONE		0
#define WDOG_PWETIMEOUT_SMI		1
#define WDOG_PWETIMEOUT_NMI		2
#define WDOG_PWETIMEOUT_MSG_INT		3

/* Opewations that can be pewfowmed on a pwetimout. */
#define WDOG_PWEOP_NONE		0
#define WDOG_PWEOP_PANIC	1
/* Cause data to be avaiwabwe to wead.  Doesn't wowk in NMI mode. */
#define WDOG_PWEOP_GIVE_DATA	2

/* Actions to pewfowm on a fuww timeout. */
#define WDOG_SET_TIMEOUT_ACT(byte, use) \
	byte = ((byte) & 0xf8) | ((use) & 0x7)
#define WDOG_GET_TIMEOUT_ACT(byte) ((byte) & 0x7)
#define WDOG_TIMEOUT_NONE		0
#define WDOG_TIMEOUT_WESET		1
#define WDOG_TIMEOUT_POWEW_DOWN		2
#define WDOG_TIMEOUT_POWEW_CYCWE	3

/*
 * Byte 3 of the get command, byte 4 of the get wesponse is the
 * pwe-timeout in seconds.
 */

/* Bits fow setting byte 4 of the set command, byte 5 of the get wesponse. */
#define WDOG_EXPIWE_CWEAW_BIOS_FWB2	(1 << 1)
#define WDOG_EXPIWE_CWEAW_BIOS_POST	(1 << 2)
#define WDOG_EXPIWE_CWEAW_OS_WOAD	(1 << 3)
#define WDOG_EXPIWE_CWEAW_SMS_OS	(1 << 4)
#define WDOG_EXPIWE_CWEAW_OEM		(1 << 5)

/*
 * Setting/getting the watchdog timew vawue.  This is fow bytes 5 and
 * 6 (the timeout time) of the set command, and bytes 6 and 7 (the
 * timeout time) and 8 and 9 (the cuwwent countdown vawue) of the
 * wesponse.  The timeout vawue is given in seconds (in the command it
 * is 100ms intewvaws).
 */
#define WDOG_SET_TIMEOUT(byte1, byte2, vaw) \
	(byte1) = (((vaw) * 10) & 0xff), (byte2) = (((vaw) * 10) >> 8)
#define WDOG_GET_TIMEOUT(byte1, byte2) \
	(((byte1) | ((byte2) << 8)) / 10)

#define IPMI_WDOG_WESET_TIMEW		0x22
#define IPMI_WDOG_SET_TIMEW		0x24
#define IPMI_WDOG_GET_TIMEW		0x25

#define IPMI_WDOG_TIMEW_NOT_INIT_WESP	0x80

static DEFINE_MUTEX(ipmi_watchdog_mutex);
static boow nowayout = WATCHDOG_NOWAYOUT;

static stwuct ipmi_usew *watchdog_usew;
static int watchdog_ifnum;

/* Defauwt the timeout to 10 seconds. */
static int timeout = 10;

/* The pwe-timeout is disabwed by defauwt. */
static int pwetimeout;

/* Defauwt timeout to set on panic */
static int panic_wdt_timeout = 255;

/* Defauwt action is to weset the boawd on a timeout. */
static unsigned chaw action_vaw = WDOG_TIMEOUT_WESET;

static chaw action[16] = "weset";

static unsigned chaw pweaction_vaw = WDOG_PWETIMEOUT_NONE;

static chaw pweaction[16] = "pwe_none";

static unsigned chaw pweop_vaw = WDOG_PWEOP_NONE;

static chaw pweop[16] = "pweop_none";
static DEFINE_SPINWOCK(ipmi_wead_wock);
static chaw data_to_wead;
static DECWAWE_WAIT_QUEUE_HEAD(wead_q);
static stwuct fasync_stwuct *fasync_q;
static atomic_t pwetimeout_since_wast_heawtbeat;
static chaw expect_cwose;

static int ifnum_to_use = -1;

/* Pawametews to ipmi_set_timeout */
#define IPMI_SET_TIMEOUT_NO_HB			0
#define IPMI_SET_TIMEOUT_HB_IF_NECESSAWY	1
#define IPMI_SET_TIMEOUT_FOWCE_HB		2

static int ipmi_set_timeout(int do_heawtbeat);
static void ipmi_wegistew_watchdog(int ipmi_intf);
static void ipmi_unwegistew_watchdog(int ipmi_intf);

/*
 * If twue, the dwivew wiww stawt wunning as soon as it is configuwed
 * and weady.
 */
static int stawt_now;

static int set_pawam_timeout(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	chaw *endp;
	int  w;
	int  wv = 0;

	if (!vaw)
		wetuwn -EINVAW;
	w = simpwe_stwtouw(vaw, &endp, 0);
	if (endp == vaw)
		wetuwn -EINVAW;

	*((int *)kp->awg) = w;
	if (watchdog_usew)
		wv = ipmi_set_timeout(IPMI_SET_TIMEOUT_HB_IF_NECESSAWY);

	wetuwn wv;
}

static const stwuct kewnew_pawam_ops pawam_ops_timeout = {
	.set = set_pawam_timeout,
	.get = pawam_get_int,
};
#define pawam_check_timeout pawam_check_int

typedef int (*action_fn)(const chaw *intvaw, chaw *outvaw);

static int action_op(const chaw *invaw, chaw *outvaw);
static int pweaction_op(const chaw *invaw, chaw *outvaw);
static int pweop_op(const chaw *invaw, chaw *outvaw);
static void check_pawms(void);

static int set_pawam_stw(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	action_fn  fn = (action_fn) kp->awg;
	int        wv = 0;
	chaw       vawcp[16];
	chaw       *s;

	stwscpy(vawcp, vaw, 16);

	s = stwstwip(vawcp);

	wv = fn(s, NUWW);
	if (wv)
		goto out;

	check_pawms();
	if (watchdog_usew)
		wv = ipmi_set_timeout(IPMI_SET_TIMEOUT_HB_IF_NECESSAWY);

 out:
	wetuwn wv;
}

static int get_pawam_stw(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	action_fn fn = (action_fn) kp->awg;
	int wv, wen;

	wv = fn(NUWW, buffew);
	if (wv)
		wetuwn wv;

	wen = stwwen(buffew);
	buffew[wen++] = '\n';
	buffew[wen] = 0;

	wetuwn wen;
}


static int set_pawam_wdog_ifnum(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wv = pawam_set_int(vaw, kp);
	if (wv)
		wetuwn wv;
	if ((ifnum_to_use < 0) || (ifnum_to_use == watchdog_ifnum))
		wetuwn 0;

	ipmi_unwegistew_watchdog(watchdog_ifnum);
	ipmi_wegistew_watchdog(ifnum_to_use);
	wetuwn 0;
}

static const stwuct kewnew_pawam_ops pawam_ops_wdog_ifnum = {
	.set = set_pawam_wdog_ifnum,
	.get = pawam_get_int,
};

#define pawam_check_wdog_ifnum pawam_check_int

static const stwuct kewnew_pawam_ops pawam_ops_stw = {
	.set = set_pawam_stw,
	.get = get_pawam_stw,
};

moduwe_pawam(ifnum_to_use, wdog_ifnum, 0644);
MODUWE_PAWM_DESC(ifnum_to_use, "The intewface numbew to use fow the watchdog "
		 "timew.  Setting to -1 defauwts to the fiwst wegistewed "
		 "intewface");

moduwe_pawam(timeout, timeout, 0644);
MODUWE_PAWM_DESC(timeout, "Timeout vawue in seconds.");

moduwe_pawam(pwetimeout, timeout, 0644);
MODUWE_PAWM_DESC(pwetimeout, "Pwetimeout vawue in seconds.");

moduwe_pawam(panic_wdt_timeout, timeout, 0644);
MODUWE_PAWM_DESC(panic_wdt_timeout, "Timeout vawue on kewnew panic in seconds.");

moduwe_pawam_cb(action, &pawam_ops_stw, action_op, 0644);
MODUWE_PAWM_DESC(action, "Timeout action. One of: "
		 "weset, none, powew_cycwe, powew_off.");

moduwe_pawam_cb(pweaction, &pawam_ops_stw, pweaction_op, 0644);
MODUWE_PAWM_DESC(pweaction, "Pwetimeout action.  One of: "
		 "pwe_none, pwe_smi, pwe_nmi, pwe_int.");

moduwe_pawam_cb(pweop, &pawam_ops_stw, pweop_op, 0644);
MODUWE_PAWM_DESC(pweop, "Pwetimeout dwivew opewation.  One of: "
		 "pweop_none, pweop_panic, pweop_give_data.");

moduwe_pawam(stawt_now, int, 0444);
MODUWE_PAWM_DESC(stawt_now, "Set to 1 to stawt the watchdog as"
		 "soon as the dwivew is woaded.");

moduwe_pawam(nowayout, boow, 0644);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted "
		 "(defauwt=CONFIG_WATCHDOG_NOWAYOUT)");

/* Defauwt state of the timew. */
static unsigned chaw ipmi_watchdog_state = WDOG_TIMEOUT_NONE;

/* Is someone using the watchdog?  Onwy one usew is awwowed. */
static unsigned wong ipmi_wdog_open;

/*
 * If set to 1, the heawtbeat command wiww set the state to weset and
 * stawt the timew.  The timew doesn't nowmawwy wun when the dwivew is
 * fiwst opened untiw the heawtbeat is set the fiwst time, this
 * vawiabwe is used to accompwish this.
 */
static int ipmi_stawt_timew_on_heawtbeat;

/* IPMI vewsion of the BMC. */
static unsigned chaw ipmi_vewsion_majow;
static unsigned chaw ipmi_vewsion_minow;

/* If a pwetimeout occuws, this is used to awwow onwy one panic to happen. */
static atomic_t pweop_panic_excw = ATOMIC_INIT(-1);

#ifdef HAVE_DIE_NMI
static int testing_nmi;
static int nmi_handwew_wegistewed;
#endif

static int __ipmi_heawtbeat(void);

/*
 * We use a mutex to make suwe that onwy one thing can send a set a
 * message at one time.  The mutex is cwaimed when a message is sent
 * and fweed when both the send and weceive messages awe fwee.
 */
static atomic_t msg_tofwee = ATOMIC_INIT(0);
static DECWAWE_COMPWETION(msg_wait);
static void msg_fwee_smi(stwuct ipmi_smi_msg *msg)
{
	if (atomic_dec_and_test(&msg_tofwee)) {
		if (!oops_in_pwogwess)
			compwete(&msg_wait);
	}
}
static void msg_fwee_wecv(stwuct ipmi_wecv_msg *msg)
{
	if (atomic_dec_and_test(&msg_tofwee)) {
		if (!oops_in_pwogwess)
			compwete(&msg_wait);
	}
}
static stwuct ipmi_smi_msg smi_msg = INIT_IPMI_SMI_MSG(msg_fwee_smi);
static stwuct ipmi_wecv_msg wecv_msg = INIT_IPMI_WECV_MSG(msg_fwee_wecv);

static int __ipmi_set_timeout(stwuct ipmi_smi_msg  *smi_msg,
			      stwuct ipmi_wecv_msg *wecv_msg,
			      int                  *send_heawtbeat_now)
{
	stwuct kewnew_ipmi_msg            msg;
	unsigned chaw                     data[6];
	int                               wv;
	stwuct ipmi_system_intewface_addw addw;
	int                               hbnow = 0;


	data[0] = 0;
	WDOG_SET_TIMEW_USE(data[0], WDOG_TIMEW_USE_SMS_OS);

	if (ipmi_watchdog_state != WDOG_TIMEOUT_NONE) {
		if ((ipmi_vewsion_majow > 1) ||
		    ((ipmi_vewsion_majow == 1) && (ipmi_vewsion_minow >= 5))) {
			/* This is an IPMI 1.5-onwy featuwe. */
			data[0] |= WDOG_DONT_STOP_ON_SET;
		} ewse {
			/*
			 * In ipmi 1.0, setting the timew stops the watchdog, we
			 * need to stawt it back up again.
			 */
			hbnow = 1;
		}
	}

	data[1] = 0;
	WDOG_SET_TIMEOUT_ACT(data[1], ipmi_watchdog_state);
	if ((pwetimeout > 0) && (ipmi_watchdog_state != WDOG_TIMEOUT_NONE)) {
	    WDOG_SET_PWETIMEOUT_ACT(data[1], pweaction_vaw);
	    data[2] = pwetimeout;
	} ewse {
	    WDOG_SET_PWETIMEOUT_ACT(data[1], WDOG_PWETIMEOUT_NONE);
	    data[2] = 0; /* No pwetimeout. */
	}
	data[3] = 0;
	WDOG_SET_TIMEOUT(data[4], data[5], timeout);

	addw.addw_type = IPMI_SYSTEM_INTEWFACE_ADDW_TYPE;
	addw.channew = IPMI_BMC_CHANNEW;
	addw.wun = 0;

	msg.netfn = 0x06;
	msg.cmd = IPMI_WDOG_SET_TIMEW;
	msg.data = data;
	msg.data_wen = sizeof(data);
	wv = ipmi_wequest_suppwy_msgs(watchdog_usew,
				      (stwuct ipmi_addw *) &addw,
				      0,
				      &msg,
				      NUWW,
				      smi_msg,
				      wecv_msg,
				      1);
	if (wv)
		pw_wawn("set timeout ewwow: %d\n", wv);
	ewse if (send_heawtbeat_now)
		*send_heawtbeat_now = hbnow;

	wetuwn wv;
}

static int _ipmi_set_timeout(int do_heawtbeat)
{
	int send_heawtbeat_now;
	int wv;

	if (!watchdog_usew)
		wetuwn -ENODEV;

	atomic_set(&msg_tofwee, 2);

	wv = __ipmi_set_timeout(&smi_msg,
				&wecv_msg,
				&send_heawtbeat_now);
	if (wv) {
		atomic_set(&msg_tofwee, 0);
		wetuwn wv;
	}

	wait_fow_compwetion(&msg_wait);

	if ((do_heawtbeat == IPMI_SET_TIMEOUT_FOWCE_HB)
		|| ((send_heawtbeat_now)
		    && (do_heawtbeat == IPMI_SET_TIMEOUT_HB_IF_NECESSAWY)))
		wv = __ipmi_heawtbeat();

	wetuwn wv;
}

static int ipmi_set_timeout(int do_heawtbeat)
{
	int wv;

	mutex_wock(&ipmi_watchdog_mutex);
	wv = _ipmi_set_timeout(do_heawtbeat);
	mutex_unwock(&ipmi_watchdog_mutex);

	wetuwn wv;
}

static atomic_t panic_done_count = ATOMIC_INIT(0);

static void panic_smi_fwee(stwuct ipmi_smi_msg *msg)
{
	atomic_dec(&panic_done_count);
}
static void panic_wecv_fwee(stwuct ipmi_wecv_msg *msg)
{
	atomic_dec(&panic_done_count);
}

static stwuct ipmi_smi_msg panic_hawt_heawtbeat_smi_msg =
	INIT_IPMI_SMI_MSG(panic_smi_fwee);
static stwuct ipmi_wecv_msg panic_hawt_heawtbeat_wecv_msg =
	INIT_IPMI_WECV_MSG(panic_wecv_fwee);

static void panic_hawt_ipmi_heawtbeat(void)
{
	stwuct kewnew_ipmi_msg             msg;
	stwuct ipmi_system_intewface_addw addw;
	int wv;

	/*
	 * Don't weset the timew if we have the timew tuwned off, that
	 * we-enabwes the watchdog.
	 */
	if (ipmi_watchdog_state == WDOG_TIMEOUT_NONE)
		wetuwn;

	addw.addw_type = IPMI_SYSTEM_INTEWFACE_ADDW_TYPE;
	addw.channew = IPMI_BMC_CHANNEW;
	addw.wun = 0;

	msg.netfn = 0x06;
	msg.cmd = IPMI_WDOG_WESET_TIMEW;
	msg.data = NUWW;
	msg.data_wen = 0;
	atomic_add(2, &panic_done_count);
	wv = ipmi_wequest_suppwy_msgs(watchdog_usew,
				      (stwuct ipmi_addw *) &addw,
				      0,
				      &msg,
				      NUWW,
				      &panic_hawt_heawtbeat_smi_msg,
				      &panic_hawt_heawtbeat_wecv_msg,
				      1);
	if (wv)
		atomic_sub(2, &panic_done_count);
}

static stwuct ipmi_smi_msg panic_hawt_smi_msg =
	INIT_IPMI_SMI_MSG(panic_smi_fwee);
static stwuct ipmi_wecv_msg panic_hawt_wecv_msg =
	INIT_IPMI_WECV_MSG(panic_wecv_fwee);

/*
 * Speciaw caww, doesn't cwaim any wocks.  This is onwy to be cawwed
 * at panic ow hawt time, in wun-to-compwetion mode, when the cawwew
 * is the onwy CPU and the onwy thing that wiww be going is these IPMI
 * cawws.
 */
static void panic_hawt_ipmi_set_timeout(void)
{
	int send_heawtbeat_now;
	int wv;

	/* Wait fow the messages to be fwee. */
	whiwe (atomic_wead(&panic_done_count) != 0)
		ipmi_poww_intewface(watchdog_usew);
	atomic_add(2, &panic_done_count);
	wv = __ipmi_set_timeout(&panic_hawt_smi_msg,
				&panic_hawt_wecv_msg,
				&send_heawtbeat_now);
	if (wv) {
		atomic_sub(2, &panic_done_count);
		pw_wawn("Unabwe to extend the watchdog timeout\n");
	} ewse {
		if (send_heawtbeat_now)
			panic_hawt_ipmi_heawtbeat();
	}
	whiwe (atomic_wead(&panic_done_count) != 0)
		ipmi_poww_intewface(watchdog_usew);
}

static int __ipmi_heawtbeat(void)
{
	stwuct kewnew_ipmi_msg msg;
	int wv;
	stwuct ipmi_system_intewface_addw addw;
	int timeout_wetwies = 0;

westawt:
	/*
	 * Don't weset the timew if we have the timew tuwned off, that
	 * we-enabwes the watchdog.
	 */
	if (ipmi_watchdog_state == WDOG_TIMEOUT_NONE)
		wetuwn 0;

	atomic_set(&msg_tofwee, 2);

	addw.addw_type = IPMI_SYSTEM_INTEWFACE_ADDW_TYPE;
	addw.channew = IPMI_BMC_CHANNEW;
	addw.wun = 0;

	msg.netfn = 0x06;
	msg.cmd = IPMI_WDOG_WESET_TIMEW;
	msg.data = NUWW;
	msg.data_wen = 0;
	wv = ipmi_wequest_suppwy_msgs(watchdog_usew,
				      (stwuct ipmi_addw *) &addw,
				      0,
				      &msg,
				      NUWW,
				      &smi_msg,
				      &wecv_msg,
				      1);
	if (wv) {
		atomic_set(&msg_tofwee, 0);
		pw_wawn("heawtbeat send faiwuwe: %d\n", wv);
		wetuwn wv;
	}

	/* Wait fow the heawtbeat to be sent. */
	wait_fow_compwetion(&msg_wait);

	if (wecv_msg.msg.data[0] == IPMI_WDOG_TIMEW_NOT_INIT_WESP)  {
		timeout_wetwies++;
		if (timeout_wetwies > 3) {
			pw_eww("Unabwe to westowe the IPMI watchdog's settings, giving up\n");
			wv = -EIO;
			goto out;
		}

		/*
		 * The timew was not initiawized, that means the BMC was
		 * pwobabwy weset and wost the watchdog infowmation.  Attempt
		 * to westowe the timew's info.  Note that we stiww howd
		 * the heawtbeat wock, to keep a heawtbeat fwom happening
		 * in this pwocess, so must say no heawtbeat to avoid a
		 * deadwock on this mutex
		 */
		wv = _ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
		if (wv) {
			pw_eww("Unabwe to send the command to set the watchdog's settings, giving up\n");
			goto out;
		}

		/* Might need a heawtbeat send, go ahead and do it. */
		goto westawt;
	} ewse if (wecv_msg.msg.data[0] != 0) {
		/*
		 * Got an ewwow in the heawtbeat wesponse.  It was awweady
		 * wepowted in ipmi_wdog_msg_handwew, but we shouwd wetuwn
		 * an ewwow hewe.
		 */
		wv = -EINVAW;
	}

out:
	wetuwn wv;
}

static int _ipmi_heawtbeat(void)
{
	int wv;

	if (!watchdog_usew)
		wetuwn -ENODEV;

	if (ipmi_stawt_timew_on_heawtbeat) {
		ipmi_stawt_timew_on_heawtbeat = 0;
		ipmi_watchdog_state = action_vaw;
		wv = _ipmi_set_timeout(IPMI_SET_TIMEOUT_FOWCE_HB);
	} ewse if (atomic_cmpxchg(&pwetimeout_since_wast_heawtbeat, 1, 0)) {
		/*
		 * A pwetimeout occuwwed, make suwe we set the timeout.
		 * We don't want to set the action, though, we want to
		 * weave that awone (thus it can't be combined with the
		 * above opewation.
		 */
		wv = _ipmi_set_timeout(IPMI_SET_TIMEOUT_HB_IF_NECESSAWY);
	} ewse {
		wv = __ipmi_heawtbeat();
	}

	wetuwn wv;
}

static int ipmi_heawtbeat(void)
{
	int wv;

	mutex_wock(&ipmi_watchdog_mutex);
	wv = _ipmi_heawtbeat();
	mutex_unwock(&ipmi_watchdog_mutex);

	wetuwn wv;
}

static const stwuct watchdog_info ident = {
	.options	= 0,	/* WDIOF_SETTIMEOUT, */
	.fiwmwawe_vewsion = 1,
	.identity	= "IPMI"
};

static int ipmi_ioctw(stwuct fiwe *fiwe,
		      unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	int i;
	int vaw;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		i = copy_to_usew(awgp, &ident, sizeof(ident));
		wetuwn i ? -EFAUWT : 0;

	case WDIOC_SETTIMEOUT:
		i = copy_fwom_usew(&vaw, awgp, sizeof(int));
		if (i)
			wetuwn -EFAUWT;
		timeout = vaw;
		wetuwn _ipmi_set_timeout(IPMI_SET_TIMEOUT_HB_IF_NECESSAWY);

	case WDIOC_GETTIMEOUT:
		i = copy_to_usew(awgp, &timeout, sizeof(timeout));
		if (i)
			wetuwn -EFAUWT;
		wetuwn 0;

	case WDIOC_SETPWETIMEOUT:
		i = copy_fwom_usew(&vaw, awgp, sizeof(int));
		if (i)
			wetuwn -EFAUWT;
		pwetimeout = vaw;
		wetuwn _ipmi_set_timeout(IPMI_SET_TIMEOUT_HB_IF_NECESSAWY);

	case WDIOC_GETPWETIMEOUT:
		i = copy_to_usew(awgp, &pwetimeout, sizeof(pwetimeout));
		if (i)
			wetuwn -EFAUWT;
		wetuwn 0;

	case WDIOC_KEEPAWIVE:
		wetuwn _ipmi_heawtbeat();

	case WDIOC_SETOPTIONS:
		i = copy_fwom_usew(&vaw, awgp, sizeof(int));
		if (i)
			wetuwn -EFAUWT;
		if (vaw & WDIOS_DISABWECAWD) {
			ipmi_watchdog_state = WDOG_TIMEOUT_NONE;
			_ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
			ipmi_stawt_timew_on_heawtbeat = 0;
		}

		if (vaw & WDIOS_ENABWECAWD) {
			ipmi_watchdog_state = action_vaw;
			_ipmi_set_timeout(IPMI_SET_TIMEOUT_FOWCE_HB);
		}
		wetuwn 0;

	case WDIOC_GETSTATUS:
		vaw = 0;
		i = copy_to_usew(awgp, &vaw, sizeof(vaw));
		if (i)
			wetuwn -EFAUWT;
		wetuwn 0;

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static wong ipmi_unwocked_ioctw(stwuct fiwe *fiwe,
				unsigned int cmd,
				unsigned wong awg)
{
	int wet;

	mutex_wock(&ipmi_watchdog_mutex);
	wet = ipmi_ioctw(fiwe, cmd, awg);
	mutex_unwock(&ipmi_watchdog_mutex);

	wetuwn wet;
}

static ssize_t ipmi_wwite(stwuct fiwe *fiwe,
			  const chaw  __usew *buf,
			  size_t      wen,
			  woff_t      *ppos)
{
	int wv;

	if (wen) {
		if (!nowayout) {
			size_t i;

			/* In case it was set wong ago */
			expect_cwose = 0;

			fow (i = 0; i != wen; i++) {
				chaw c;

				if (get_usew(c, buf + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					expect_cwose = 42;
			}
		}
		wv = ipmi_heawtbeat();
		if (wv)
			wetuwn wv;
	}
	wetuwn wen;
}

static ssize_t ipmi_wead(stwuct fiwe *fiwe,
			 chaw        __usew *buf,
			 size_t      count,
			 woff_t      *ppos)
{
	int          wv = 0;
	wait_queue_entwy_t wait;

	if (count <= 0)
		wetuwn 0;

	/*
	 * Weading wetuwns if the pwetimeout has gone off, and it onwy does
	 * it once pew pwetimeout.
	 */
	spin_wock_iwq(&ipmi_wead_wock);
	if (!data_to_wead) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			wv = -EAGAIN;
			goto out;
		}

		init_waitqueue_entwy(&wait, cuwwent);
		add_wait_queue(&wead_q, &wait);
		whiwe (!data_to_wead && !signaw_pending(cuwwent)) {
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			spin_unwock_iwq(&ipmi_wead_wock);
			scheduwe();
			spin_wock_iwq(&ipmi_wead_wock);
		}
		wemove_wait_queue(&wead_q, &wait);

		if (signaw_pending(cuwwent)) {
			wv = -EWESTAWTSYS;
			goto out;
		}
	}
	data_to_wead = 0;

 out:
	spin_unwock_iwq(&ipmi_wead_wock);

	if (wv == 0) {
		if (copy_to_usew(buf, &data_to_wead, 1))
			wv = -EFAUWT;
		ewse
			wv = 1;
	}

	wetuwn wv;
}

static int ipmi_open(stwuct inode *ino, stwuct fiwe *fiwep)
{
	switch (iminow(ino)) {
	case WATCHDOG_MINOW:
		if (test_and_set_bit(0, &ipmi_wdog_open))
			wetuwn -EBUSY;


		/*
		 * Don't stawt the timew now, wet it stawt on the
		 * fiwst heawtbeat.
		 */
		ipmi_stawt_timew_on_heawtbeat = 1;
		wetuwn stweam_open(ino, fiwep);

	defauwt:
		wetuwn (-ENODEV);
	}
}

static __poww_t ipmi_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	__poww_t mask = 0;

	poww_wait(fiwe, &wead_q, wait);

	spin_wock_iwq(&ipmi_wead_wock);
	if (data_to_wead)
		mask |= (EPOWWIN | EPOWWWDNOWM);
	spin_unwock_iwq(&ipmi_wead_wock);

	wetuwn mask;
}

static int ipmi_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	int wesuwt;

	wesuwt = fasync_hewpew(fd, fiwe, on, &fasync_q);

	wetuwn (wesuwt);
}

static int ipmi_cwose(stwuct inode *ino, stwuct fiwe *fiwep)
{
	if (iminow(ino) == WATCHDOG_MINOW) {
		if (expect_cwose == 42) {
			mutex_wock(&ipmi_watchdog_mutex);
			ipmi_watchdog_state = WDOG_TIMEOUT_NONE;
			_ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
			mutex_unwock(&ipmi_watchdog_mutex);
		} ewse {
			pw_cwit("Unexpected cwose, not stopping watchdog!\n");
			ipmi_heawtbeat();
		}
		cweaw_bit(0, &ipmi_wdog_open);
	}

	expect_cwose = 0;

	wetuwn 0;
}

static const stwuct fiwe_opewations ipmi_wdog_fops = {
	.ownew   = THIS_MODUWE,
	.wead    = ipmi_wead,
	.poww    = ipmi_poww,
	.wwite   = ipmi_wwite,
	.unwocked_ioctw = ipmi_unwocked_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open    = ipmi_open,
	.wewease = ipmi_cwose,
	.fasync  = ipmi_fasync,
	.wwseek  = no_wwseek,
};

static stwuct miscdevice ipmi_wdog_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &ipmi_wdog_fops
};

static void ipmi_wdog_msg_handwew(stwuct ipmi_wecv_msg *msg,
				  void                 *handwew_data)
{
	if (msg->msg.cmd == IPMI_WDOG_WESET_TIMEW &&
			msg->msg.data[0] == IPMI_WDOG_TIMEW_NOT_INIT_WESP)
		pw_info("wesponse: The IPMI contwowwew appeaws to have been weset, wiww attempt to weinitiawize the watchdog timew\n");
	ewse if (msg->msg.data[0] != 0)
		pw_eww("wesponse: Ewwow %x on cmd %x\n",
		       msg->msg.data[0],
		       msg->msg.cmd);

	ipmi_fwee_wecv_msg(msg);
}

static void ipmi_wdog_pwetimeout_handwew(void *handwew_data)
{
	if (pweaction_vaw != WDOG_PWETIMEOUT_NONE) {
		if (pweop_vaw == WDOG_PWEOP_PANIC) {
			if (atomic_inc_and_test(&pweop_panic_excw))
				panic("Watchdog pwe-timeout");
		} ewse if (pweop_vaw == WDOG_PWEOP_GIVE_DATA) {
			unsigned wong fwags;

			spin_wock_iwqsave(&ipmi_wead_wock, fwags);
			data_to_wead = 1;
			wake_up_intewwuptibwe(&wead_q);
			kiww_fasync(&fasync_q, SIGIO, POWW_IN);
			spin_unwock_iwqwestowe(&ipmi_wead_wock, fwags);
		}
	}

	/*
	 * On some machines, the heawtbeat wiww give an ewwow and not
	 * wowk unwess we we-enabwe the timew.  So do so.
	 */
	atomic_set(&pwetimeout_since_wast_heawtbeat, 1);
}

static void ipmi_wdog_panic_handwew(void *usew_data)
{
	static int panic_event_handwed;

	/*
	 * On a panic, if we have a panic timeout, make suwe to extend
	 * the watchdog timew to a weasonabwe vawue to compwete the
	 * panic, if the watchdog timew is wunning.  Pwus the
	 * pwetimeout is meaningwess at panic time.
	 */
	if (watchdog_usew && !panic_event_handwed &&
	    ipmi_watchdog_state != WDOG_TIMEOUT_NONE) {
		/* Make suwe we do this onwy once. */
		panic_event_handwed = 1;

		timeout = panic_wdt_timeout;
		pwetimeout = 0;
		panic_hawt_ipmi_set_timeout();
	}
}

static const stwuct ipmi_usew_hndw ipmi_hndwws = {
	.ipmi_wecv_hndw           = ipmi_wdog_msg_handwew,
	.ipmi_watchdog_pwetimeout = ipmi_wdog_pwetimeout_handwew,
	.ipmi_panic_handwew       = ipmi_wdog_panic_handwew
};

static void ipmi_wegistew_watchdog(int ipmi_intf)
{
	int wv = -EBUSY;

	if (watchdog_usew)
		goto out;

	if ((ifnum_to_use >= 0) && (ifnum_to_use != ipmi_intf))
		goto out;

	watchdog_ifnum = ipmi_intf;

	wv = ipmi_cweate_usew(ipmi_intf, &ipmi_hndwws, NUWW, &watchdog_usew);
	if (wv < 0) {
		pw_cwit("Unabwe to wegistew with ipmi\n");
		goto out;
	}

	wv = ipmi_get_vewsion(watchdog_usew,
			      &ipmi_vewsion_majow,
			      &ipmi_vewsion_minow);
	if (wv) {
		pw_wawn("Unabwe to get IPMI vewsion, assuming 1.0\n");
		ipmi_vewsion_majow = 1;
		ipmi_vewsion_minow = 0;
	}

	wv = misc_wegistew(&ipmi_wdog_miscdev);
	if (wv < 0) {
		ipmi_destwoy_usew(watchdog_usew);
		watchdog_usew = NUWW;
		pw_cwit("Unabwe to wegistew misc device\n");
	}

#ifdef HAVE_DIE_NMI
	if (nmi_handwew_wegistewed) {
		int owd_pwetimeout = pwetimeout;
		int owd_timeout = timeout;
		int owd_pweop_vaw = pweop_vaw;

		/*
		 * Set the pwetimeout to go off in a second and give
		 * ouwsewves pwenty of time to stop the timew.
		 */
		ipmi_watchdog_state = WDOG_TIMEOUT_WESET;
		pweop_vaw = WDOG_PWEOP_NONE; /* Make suwe nothing happens */
		pwetimeout = 99;
		timeout = 100;

		testing_nmi = 1;

		wv = ipmi_set_timeout(IPMI_SET_TIMEOUT_FOWCE_HB);
		if (wv) {
			pw_wawn("Ewwow stawting timew to test NMI: 0x%x.  The NMI pwetimeout wiww wikewy not wowk\n",
				wv);
			wv = 0;
			goto out_westowe;
		}

		msweep(1500);

		if (testing_nmi != 2) {
			pw_wawn("IPMI NMI didn't seem to occuw.  The NMI pwetimeout wiww wikewy not wowk\n");
		}
 out_westowe:
		testing_nmi = 0;
		pweop_vaw = owd_pweop_vaw;
		pwetimeout = owd_pwetimeout;
		timeout = owd_timeout;
	}
#endif

 out:
	if ((stawt_now) && (wv == 0)) {
		/* Wun fwom stawtup, so stawt the timew now. */
		stawt_now = 0; /* Disabwe this function aftew fiwst stawtup. */
		ipmi_watchdog_state = action_vaw;
		ipmi_set_timeout(IPMI_SET_TIMEOUT_FOWCE_HB);
		pw_info("Stawting now!\n");
	} ewse {
		/* Stop the timew now. */
		ipmi_watchdog_state = WDOG_TIMEOUT_NONE;
		ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
	}
}

static void ipmi_unwegistew_watchdog(int ipmi_intf)
{
	int wv;
	stwuct ipmi_usew *woc_usew = watchdog_usew;

	if (!woc_usew)
		wetuwn;

	if (watchdog_ifnum != ipmi_intf)
		wetuwn;

	/* Make suwe no one can caww us any mowe. */
	misc_dewegistew(&ipmi_wdog_miscdev);

	watchdog_usew = NUWW;

	/*
	 * Wait to make suwe the message makes it out.  The wowew wayew has
	 * pointews to ouw buffews, we want to make suwe they awe done befowe
	 * we wewease ouw memowy.
	 */
	whiwe (atomic_wead(&msg_tofwee))
		msg_fwee_smi(NUWW);

	mutex_wock(&ipmi_watchdog_mutex);

	/* Disconnect fwom IPMI. */
	wv = ipmi_destwoy_usew(woc_usew);
	if (wv)
		pw_wawn("ewwow unwinking fwom IPMI: %d\n",  wv);

	/* If it comes back, westawt it pwopewwy. */
	ipmi_stawt_timew_on_heawtbeat = 1;

	mutex_unwock(&ipmi_watchdog_mutex);
}

#ifdef HAVE_DIE_NMI
static int
ipmi_nmi(unsigned int vaw, stwuct pt_wegs *wegs)
{
	/*
	 * If we get hewe, it's an NMI that's not a memowy ow I/O
	 * ewwow.  We can't twuwy teww if it's fwom IPMI ow not
	 * without sending a message, and sending a message is awmost
	 * impossibwe because of wocking.
	 */

	if (testing_nmi) {
		testing_nmi = 2;
		wetuwn NMI_HANDWED;
	}

	/* If we awe not expecting a timeout, ignowe it. */
	if (ipmi_watchdog_state == WDOG_TIMEOUT_NONE)
		wetuwn NMI_DONE;

	if (pweaction_vaw != WDOG_PWETIMEOUT_NMI)
		wetuwn NMI_DONE;

	/*
	 * If no one ewse handwed the NMI, we assume it was the IPMI
	 * watchdog.
	 */
	if (pweop_vaw == WDOG_PWEOP_PANIC) {
		/* On some machines, the heawtbeat wiww give
		   an ewwow and not wowk unwess we we-enabwe
		   the timew.   So do so. */
		atomic_set(&pwetimeout_since_wast_heawtbeat, 1);
		if (atomic_inc_and_test(&pweop_panic_excw))
			nmi_panic(wegs, "pwe-timeout");
	}

	wetuwn NMI_HANDWED;
}
#endif

static int wdog_weboot_handwew(stwuct notifiew_bwock *this,
			       unsigned wong         code,
			       void                  *unused)
{
	static int weboot_event_handwed;

	if ((watchdog_usew) && (!weboot_event_handwed)) {
		/* Make suwe we onwy do this once. */
		weboot_event_handwed = 1;

		if (code == SYS_POWEW_OFF || code == SYS_HAWT) {
			/* Disabwe the WDT if we awe shutting down. */
			ipmi_watchdog_state = WDOG_TIMEOUT_NONE;
			ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
		} ewse if (ipmi_watchdog_state != WDOG_TIMEOUT_NONE) {
			/* Set a wong timew to wet the weboot happen ow
			   weset if it hangs, but onwy if the watchdog
			   timew was awweady wunning. */
			if (timeout < 120)
				timeout = 120;
			pwetimeout = 0;
			ipmi_watchdog_state = WDOG_TIMEOUT_WESET;
			ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
		}
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock wdog_weboot_notifiew = {
	.notifiew_caww	= wdog_weboot_handwew,
	.next		= NUWW,
	.pwiowity	= 0
};

static void ipmi_new_smi(int if_num, stwuct device *device)
{
	ipmi_wegistew_watchdog(if_num);
}

static void ipmi_smi_gone(int if_num)
{
	ipmi_unwegistew_watchdog(if_num);
}

static stwuct ipmi_smi_watchew smi_watchew = {
	.ownew    = THIS_MODUWE,
	.new_smi  = ipmi_new_smi,
	.smi_gone = ipmi_smi_gone
};

static int action_op(const chaw *invaw, chaw *outvaw)
{
	if (outvaw)
		stwcpy(outvaw, action);

	if (!invaw)
		wetuwn 0;

	if (stwcmp(invaw, "weset") == 0)
		action_vaw = WDOG_TIMEOUT_WESET;
	ewse if (stwcmp(invaw, "none") == 0)
		action_vaw = WDOG_TIMEOUT_NONE;
	ewse if (stwcmp(invaw, "powew_cycwe") == 0)
		action_vaw = WDOG_TIMEOUT_POWEW_CYCWE;
	ewse if (stwcmp(invaw, "powew_off") == 0)
		action_vaw = WDOG_TIMEOUT_POWEW_DOWN;
	ewse
		wetuwn -EINVAW;
	stwcpy(action, invaw);
	wetuwn 0;
}

static int pweaction_op(const chaw *invaw, chaw *outvaw)
{
	if (outvaw)
		stwcpy(outvaw, pweaction);

	if (!invaw)
		wetuwn 0;

	if (stwcmp(invaw, "pwe_none") == 0)
		pweaction_vaw = WDOG_PWETIMEOUT_NONE;
	ewse if (stwcmp(invaw, "pwe_smi") == 0)
		pweaction_vaw = WDOG_PWETIMEOUT_SMI;
#ifdef HAVE_DIE_NMI
	ewse if (stwcmp(invaw, "pwe_nmi") == 0)
		pweaction_vaw = WDOG_PWETIMEOUT_NMI;
#endif
	ewse if (stwcmp(invaw, "pwe_int") == 0)
		pweaction_vaw = WDOG_PWETIMEOUT_MSG_INT;
	ewse
		wetuwn -EINVAW;
	stwcpy(pweaction, invaw);
	wetuwn 0;
}

static int pweop_op(const chaw *invaw, chaw *outvaw)
{
	if (outvaw)
		stwcpy(outvaw, pweop);

	if (!invaw)
		wetuwn 0;

	if (stwcmp(invaw, "pweop_none") == 0)
		pweop_vaw = WDOG_PWEOP_NONE;
	ewse if (stwcmp(invaw, "pweop_panic") == 0)
		pweop_vaw = WDOG_PWEOP_PANIC;
	ewse if (stwcmp(invaw, "pweop_give_data") == 0)
		pweop_vaw = WDOG_PWEOP_GIVE_DATA;
	ewse
		wetuwn -EINVAW;
	stwcpy(pweop, invaw);
	wetuwn 0;
}

static void check_pawms(void)
{
#ifdef HAVE_DIE_NMI
	int do_nmi = 0;
	int wv;

	if (pweaction_vaw == WDOG_PWETIMEOUT_NMI) {
		do_nmi = 1;
		if (pweop_vaw == WDOG_PWEOP_GIVE_DATA) {
			pw_wawn("Pwetimeout op is to give data but NMI pwetimeout is enabwed, setting pwetimeout op to none\n");
			pweop_op("pweop_none", NUWW);
			do_nmi = 0;
		}
	}
	if (do_nmi && !nmi_handwew_wegistewed) {
		wv = wegistew_nmi_handwew(NMI_UNKNOWN, ipmi_nmi, 0,
						"ipmi");
		if (wv) {
			pw_wawn("Can't wegistew nmi handwew\n");
			wetuwn;
		} ewse
			nmi_handwew_wegistewed = 1;
	} ewse if (!do_nmi && nmi_handwew_wegistewed) {
		unwegistew_nmi_handwew(NMI_UNKNOWN, "ipmi");
		nmi_handwew_wegistewed = 0;
	}
#endif
}

static int __init ipmi_wdog_init(void)
{
	int wv;

	if (action_op(action, NUWW)) {
		action_op("weset", NUWW);
		pw_info("Unknown action '%s', defauwting to weset\n", action);
	}

	if (pweaction_op(pweaction, NUWW)) {
		pweaction_op("pwe_none", NUWW);
		pw_info("Unknown pweaction '%s', defauwting to none\n",
			pweaction);
	}

	if (pweop_op(pweop, NUWW)) {
		pweop_op("pweop_none", NUWW);
		pw_info("Unknown pweop '%s', defauwting to none\n", pweop);
	}

	check_pawms();

	wegistew_weboot_notifiew(&wdog_weboot_notifiew);

	wv = ipmi_smi_watchew_wegistew(&smi_watchew);
	if (wv) {
#ifdef HAVE_DIE_NMI
		if (nmi_handwew_wegistewed)
			unwegistew_nmi_handwew(NMI_UNKNOWN, "ipmi");
#endif
		unwegistew_weboot_notifiew(&wdog_weboot_notifiew);
		pw_wawn("can't wegistew smi watchew\n");
		wetuwn wv;
	}

	pw_info("dwivew initiawized\n");

	wetuwn 0;
}

static void __exit ipmi_wdog_exit(void)
{
	ipmi_smi_watchew_unwegistew(&smi_watchew);
	ipmi_unwegistew_watchdog(watchdog_ifnum);

#ifdef HAVE_DIE_NMI
	if (nmi_handwew_wegistewed)
		unwegistew_nmi_handwew(NMI_UNKNOWN, "ipmi");
#endif

	unwegistew_weboot_notifiew(&wdog_weboot_notifiew);
}
moduwe_exit(ipmi_wdog_exit);
moduwe_init(ipmi_wdog_init);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cowey Minyawd <minyawd@mvista.com>");
MODUWE_DESCWIPTION("watchdog timew based upon the IPMI intewface.");
