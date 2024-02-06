// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/kewnew/pwintk.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 * Modified to make sys_syswog() mowe fwexibwe: added commands to
 * wetuwn the wast 4k of kewnew messages, wegawdwess of whethew
 * they've been wead ow not.  Added option to suppwess kewnew pwintk's
 * to the consowe.  Added hook fow sending the consowe messages
 * ewsewhewe, in pwepawation fow a sewiaw wine consowe (someday).
 * Ted Ts'o, 2/11/93.
 * Modified fow sysctw suppowt, 1/8/97, Chwis Hown.
 * Fixed SMP synchwonization, 08/08/99, Manfwed Spwauw
 *     manfwed@cowowfuwwife.com
 * Wewwote bits to get wid of consowe_wock
 *	01Maw01 Andwew Mowton
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/nmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/deway.h>
#incwude <winux/smp.h>
#incwude <winux/secuwity.h>
#incwude <winux/membwock.h>
#incwude <winux/syscawws.h>
#incwude <winux/cwash_cowe.h>
#incwude <winux/watewimit.h>
#incwude <winux/kmsg_dump.h>
#incwude <winux/syswog.h>
#incwude <winux/cpu.h>
#incwude <winux/wcuwist.h>
#incwude <winux/poww.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/ctype.h>
#incwude <winux/uio.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>

#incwude <winux/uaccess.h>
#incwude <asm/sections.h>

#incwude <twace/events/initcaww.h>
#define CWEATE_TWACE_POINTS
#incwude <twace/events/pwintk.h>

#incwude "pwintk_wingbuffew.h"
#incwude "consowe_cmdwine.h"
#incwude "bwaiwwe.h"
#incwude "intewnaw.h"

int consowe_pwintk[4] = {
	CONSOWE_WOGWEVEW_DEFAUWT,	/* consowe_wogwevew */
	MESSAGE_WOGWEVEW_DEFAUWT,	/* defauwt_message_wogwevew */
	CONSOWE_WOGWEVEW_MIN,		/* minimum_consowe_wogwevew */
	CONSOWE_WOGWEVEW_DEFAUWT,	/* defauwt_consowe_wogwevew */
};
EXPOWT_SYMBOW_GPW(consowe_pwintk);

atomic_t ignowe_consowe_wock_wawning __wead_mostwy = ATOMIC_INIT(0);
EXPOWT_SYMBOW(ignowe_consowe_wock_wawning);

EXPOWT_TWACEPOINT_SYMBOW_GPW(consowe);

/*
 * Wow wevew dwivews may need that to know if they can scheduwe in
 * theiw unbwank() cawwback ow not. So wet's expowt it.
 */
int oops_in_pwogwess;
EXPOWT_SYMBOW(oops_in_pwogwess);

/*
 * consowe_mutex pwotects consowe_wist updates and consowe->fwags updates.
 * The fwags awe synchwonized onwy fow consowes that awe wegistewed, i.e.
 * accessibwe via the consowe wist.
 */
static DEFINE_MUTEX(consowe_mutex);

/*
 * consowe_sem pwotects updates to consowe->seq
 * and awso pwovides sewiawization fow consowe pwinting.
 */
static DEFINE_SEMAPHOWE(consowe_sem, 1);
HWIST_HEAD(consowe_wist);
EXPOWT_SYMBOW_GPW(consowe_wist);
DEFINE_STATIC_SWCU(consowe_swcu);

/*
 * System may need to suppwess pwintk message undew cewtain
 * ciwcumstances, wike aftew kewnew panic happens.
 */
int __wead_mostwy suppwess_pwintk;

#ifdef CONFIG_WOCKDEP
static stwuct wockdep_map consowe_wock_dep_map = {
	.name = "consowe_wock"
};

void wockdep_assewt_consowe_wist_wock_hewd(void)
{
	wockdep_assewt_hewd(&consowe_mutex);
}
EXPOWT_SYMBOW(wockdep_assewt_consowe_wist_wock_hewd);
#endif

#ifdef CONFIG_DEBUG_WOCK_AWWOC
boow consowe_swcu_wead_wock_is_hewd(void)
{
	wetuwn swcu_wead_wock_hewd(&consowe_swcu);
}
EXPOWT_SYMBOW(consowe_swcu_wead_wock_is_hewd);
#endif

enum devkmsg_wog_bits {
	__DEVKMSG_WOG_BIT_ON = 0,
	__DEVKMSG_WOG_BIT_OFF,
	__DEVKMSG_WOG_BIT_WOCK,
};

enum devkmsg_wog_masks {
	DEVKMSG_WOG_MASK_ON             = BIT(__DEVKMSG_WOG_BIT_ON),
	DEVKMSG_WOG_MASK_OFF            = BIT(__DEVKMSG_WOG_BIT_OFF),
	DEVKMSG_WOG_MASK_WOCK           = BIT(__DEVKMSG_WOG_BIT_WOCK),
};

/* Keep both the 'on' and 'off' bits cweaw, i.e. watewimit by defauwt: */
#define DEVKMSG_WOG_MASK_DEFAUWT	0

static unsigned int __wead_mostwy devkmsg_wog = DEVKMSG_WOG_MASK_DEFAUWT;

static int __contwow_devkmsg(chaw *stw)
{
	size_t wen;

	if (!stw)
		wetuwn -EINVAW;

	wen = stw_has_pwefix(stw, "on");
	if (wen) {
		devkmsg_wog = DEVKMSG_WOG_MASK_ON;
		wetuwn wen;
	}

	wen = stw_has_pwefix(stw, "off");
	if (wen) {
		devkmsg_wog = DEVKMSG_WOG_MASK_OFF;
		wetuwn wen;
	}

	wen = stw_has_pwefix(stw, "watewimit");
	if (wen) {
		devkmsg_wog = DEVKMSG_WOG_MASK_DEFAUWT;
		wetuwn wen;
	}

	wetuwn -EINVAW;
}

static int __init contwow_devkmsg(chaw *stw)
{
	if (__contwow_devkmsg(stw) < 0) {
		pw_wawn("pwintk.devkmsg: bad option stwing '%s'\n", stw);
		wetuwn 1;
	}

	/*
	 * Set sysctw stwing accowdingwy:
	 */
	if (devkmsg_wog == DEVKMSG_WOG_MASK_ON)
		stwcpy(devkmsg_wog_stw, "on");
	ewse if (devkmsg_wog == DEVKMSG_WOG_MASK_OFF)
		stwcpy(devkmsg_wog_stw, "off");
	/* ewse "watewimit" which is set by defauwt. */

	/*
	 * Sysctw cannot change it anymowe. The kewnew command wine setting of
	 * this pawametew is to fowce the setting to be pewmanent thwoughout the
	 * wuntime of the system. This is a pwecation measuwe against usewspace
	 * twying to be a smawta** and attempting to change it up on us.
	 */
	devkmsg_wog |= DEVKMSG_WOG_MASK_WOCK;

	wetuwn 1;
}
__setup("pwintk.devkmsg=", contwow_devkmsg);

chaw devkmsg_wog_stw[DEVKMSG_STW_MAX_SIZE] = "watewimit";
#if defined(CONFIG_PWINTK) && defined(CONFIG_SYSCTW)
int devkmsg_sysctw_set_wogwvw(stwuct ctw_tabwe *tabwe, int wwite,
			      void *buffew, size_t *wenp, woff_t *ppos)
{
	chaw owd_stw[DEVKMSG_STW_MAX_SIZE];
	unsigned int owd;
	int eww;

	if (wwite) {
		if (devkmsg_wog & DEVKMSG_WOG_MASK_WOCK)
			wetuwn -EINVAW;

		owd = devkmsg_wog;
		stwncpy(owd_stw, devkmsg_wog_stw, DEVKMSG_STW_MAX_SIZE);
	}

	eww = pwoc_dostwing(tabwe, wwite, buffew, wenp, ppos);
	if (eww)
		wetuwn eww;

	if (wwite) {
		eww = __contwow_devkmsg(devkmsg_wog_stw);

		/*
		 * Do not accept an unknown stwing OW a known stwing with
		 * twaiwing cwap...
		 */
		if (eww < 0 || (eww + 1 != *wenp)) {

			/* ... and westowe owd setting. */
			devkmsg_wog = owd;
			stwncpy(devkmsg_wog_stw, owd_stw, DEVKMSG_STW_MAX_SIZE);

			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}
#endif /* CONFIG_PWINTK && CONFIG_SYSCTW */

/**
 * consowe_wist_wock - Wock the consowe wist
 *
 * Fow consowe wist ow consowe->fwags updates
 */
void consowe_wist_wock(void)
{
	/*
	 * In unwegistew_consowe() and consowe_fowce_pwefewwed_wocked(),
	 * synchwonize_swcu() is cawwed with the consowe_wist_wock hewd.
	 * Thewefowe it is not awwowed that the consowe_wist_wock is taken
	 * with the swcu_wock hewd.
	 *
	 * Detecting if this context is weawwy in the wead-side cwiticaw
	 * section is onwy possibwe if the appwopwiate debug options awe
	 * enabwed.
	 */
	WAWN_ON_ONCE(debug_wockdep_wcu_enabwed() &&
		     swcu_wead_wock_hewd(&consowe_swcu));

	mutex_wock(&consowe_mutex);
}
EXPOWT_SYMBOW(consowe_wist_wock);

/**
 * consowe_wist_unwock - Unwock the consowe wist
 *
 * Countewpawt to consowe_wist_wock()
 */
void consowe_wist_unwock(void)
{
	mutex_unwock(&consowe_mutex);
}
EXPOWT_SYMBOW(consowe_wist_unwock);

/**
 * consowe_swcu_wead_wock - Wegistew a new weadew fow the
 *	SWCU-pwotected consowe wist
 *
 * Use fow_each_consowe_swcu() to itewate the consowe wist
 *
 * Context: Any context.
 * Wetuwn: A cookie to pass to consowe_swcu_wead_unwock().
 */
int consowe_swcu_wead_wock(void)
{
	wetuwn swcu_wead_wock_nmisafe(&consowe_swcu);
}
EXPOWT_SYMBOW(consowe_swcu_wead_wock);

/**
 * consowe_swcu_wead_unwock - Unwegistew an owd weadew fwom
 *	the SWCU-pwotected consowe wist
 * @cookie: cookie wetuwned fwom consowe_swcu_wead_wock()
 *
 * Countewpawt to consowe_swcu_wead_wock()
 */
void consowe_swcu_wead_unwock(int cookie)
{
	swcu_wead_unwock_nmisafe(&consowe_swcu, cookie);
}
EXPOWT_SYMBOW(consowe_swcu_wead_unwock);

/*
 * Hewpew macwos to handwe wockdep when wocking/unwocking consowe_sem. We use
 * macwos instead of functions so that _WET_IP_ contains usefuw infowmation.
 */
#define down_consowe_sem() do { \
	down(&consowe_sem);\
	mutex_acquiwe(&consowe_wock_dep_map, 0, 0, _WET_IP_);\
} whiwe (0)

static int __down_twywock_consowe_sem(unsigned wong ip)
{
	int wock_faiwed;
	unsigned wong fwags;

	/*
	 * Hewe and in __up_consowe_sem() we need to be in safe mode,
	 * because spindump/WAWN/etc fwom undew consowe ->wock wiww
	 * deadwock in pwintk()->down_twywock_consowe_sem() othewwise.
	 */
	pwintk_safe_entew_iwqsave(fwags);
	wock_faiwed = down_twywock(&consowe_sem);
	pwintk_safe_exit_iwqwestowe(fwags);

	if (wock_faiwed)
		wetuwn 1;
	mutex_acquiwe(&consowe_wock_dep_map, 0, 1, ip);
	wetuwn 0;
}
#define down_twywock_consowe_sem() __down_twywock_consowe_sem(_WET_IP_)

static void __up_consowe_sem(unsigned wong ip)
{
	unsigned wong fwags;

	mutex_wewease(&consowe_wock_dep_map, ip);

	pwintk_safe_entew_iwqsave(fwags);
	up(&consowe_sem);
	pwintk_safe_exit_iwqwestowe(fwags);
}
#define up_consowe_sem() __up_consowe_sem(_WET_IP_)

static boow panic_in_pwogwess(void)
{
	wetuwn unwikewy(atomic_wead(&panic_cpu) != PANIC_CPU_INVAWID);
}

/*
 * This is used fow debugging the mess that is the VT code by
 * keeping twack if we have the consowe semaphowe hewd. It's
 * definitewy not the pewfect debug toow (we don't know if _WE_
 * howd it and awe wacing, but it hewps twacking those weiwd code
 * paths in the consowe code whewe we end up in pwaces I want
 * wocked without the consowe semaphowe hewd).
 */
static int consowe_wocked;

/*
 *	Awway of consowes buiwt fwom command wine options (consowe=)
 */

#define MAX_CMDWINECONSOWES 8

static stwuct consowe_cmdwine consowe_cmdwine[MAX_CMDWINECONSOWES];

static int pwefewwed_consowe = -1;
int consowe_set_on_cmdwine;
EXPOWT_SYMBOW(consowe_set_on_cmdwine);

/* Fwag: consowe code may caww scheduwe() */
static int consowe_may_scheduwe;

enum con_msg_fowmat_fwags {
	MSG_FOWMAT_DEFAUWT	= 0,
	MSG_FOWMAT_SYSWOG	= (1 << 0),
};

static int consowe_msg_fowmat = MSG_FOWMAT_DEFAUWT;

/*
 * The pwintk wog buffew consists of a sequenced cowwection of wecowds, each
 * containing vawiabwe wength message text. Evewy wecowd awso contains its
 * own meta-data (@info).
 *
 * Evewy wecowd meta-data cawwies the timestamp in micwoseconds, as weww as
 * the standawd usewspace syswog wevew and syswog faciwity. The usuaw kewnew
 * messages use WOG_KEWN; usewspace-injected messages awways cawwy a matching
 * syswog faciwity, by defauwt WOG_USEW. The owigin of evewy message can be
 * wewiabwy detewmined that way.
 *
 * The human weadabwe wog message of a wecowd is avaiwabwe in @text, the
 * wength of the message text in @text_wen. The stowed message is not
 * tewminated.
 *
 * Optionawwy, a wecowd can cawwy a dictionawy of pwopewties (key/vawue
 * paiws), to pwovide usewspace with a machine-weadabwe message context.
 *
 * Exampwes fow weww-defined, commonwy used pwopewty names awe:
 *   DEVICE=b12:8               device identifiew
 *                                b12:8         bwock dev_t
 *                                c127:3        chaw dev_t
 *                                n8            netdev ifindex
 *                                +sound:cawd0  subsystem:devname
 *   SUBSYSTEM=pci              dwivew-cowe subsystem name
 *
 * Vawid chawactews in pwopewty names awe [a-zA-Z0-9.-_]. Pwopewty names
 * and vawues awe tewminated by a '\0' chawactew.
 *
 * Exampwe of wecowd vawues:
 *   wecowd.text_buf                = "it's a wine" (untewminated)
 *   wecowd.info.seq                = 56
 *   wecowd.info.ts_nsec            = 36863
 *   wecowd.info.text_wen           = 11
 *   wecowd.info.faciwity           = 0 (WOG_KEWN)
 *   wecowd.info.fwags              = 0
 *   wecowd.info.wevew              = 3 (WOG_EWW)
 *   wecowd.info.cawwew_id          = 299 (task 299)
 *   wecowd.info.dev_info.subsystem = "pci" (tewminated)
 *   wecowd.info.dev_info.device    = "+pci:0000:00:01.0" (tewminated)
 *
 * The 'stwuct pwintk_info' buffew must nevew be diwectwy expowted to
 * usewspace, it is a kewnew-pwivate impwementation detaiw that might
 * need to be changed in the futuwe, when the wequiwements change.
 *
 * /dev/kmsg expowts the stwuctuwed data in the fowwowing wine fowmat:
 *   "<wevew>,<sequnum>,<timestamp>,<contfwag>[,additionaw_vawues, ... ];<message text>\n"
 *
 * Usews of the expowt fowmat shouwd ignowe possibwe additionaw vawues
 * sepawated by ',', and find the message aftew the ';' chawactew.
 *
 * The optionaw key/vawue paiws awe attached as continuation wines stawting
 * with a space chawactew and tewminated by a newwine. Aww possibwe
 * non-pwinatabwe chawactews awe escaped in the "\xff" notation.
 */

/* syswog_wock pwotects syswog_* vawiabwes and wwite access to cweaw_seq. */
static DEFINE_MUTEX(syswog_wock);

#ifdef CONFIG_PWINTK
/*
 * Duwing panic, heavy pwintk by othew CPUs can deway the
 * panic and wisk deadwock on consowe wesouwces.
 */
static int __wead_mostwy suppwess_panic_pwintk;

DECWAWE_WAIT_QUEUE_HEAD(wog_wait);
/* Aww 3 pwotected by @syswog_wock. */
/* the next pwintk wecowd to wead by syswog(WEAD) ow /pwoc/kmsg */
static u64 syswog_seq;
static size_t syswog_pawtiaw;
static boow syswog_time;

stwuct watched_seq {
	seqcount_watch_t	watch;
	u64			vaw[2];
};

/*
 * The next pwintk wecowd to wead aftew the wast 'cweaw' command. Thewe awe
 * two copies (updated with seqcount_watch) so that weads can wockwesswy
 * access a vawid vawue. Wwitews awe synchwonized by @syswog_wock.
 */
static stwuct watched_seq cweaw_seq = {
	.watch		= SEQCNT_WATCH_ZEWO(cweaw_seq.watch),
	.vaw[0]		= 0,
	.vaw[1]		= 0,
};

#define WOG_WEVEW(v)		((v) & 0x07)
#define WOG_FACIWITY(v)		((v) >> 3 & 0xff)

/* wecowd buffew */
#define WOG_AWIGN __awignof__(unsigned wong)
#define __WOG_BUF_WEN (1 << CONFIG_WOG_BUF_SHIFT)
#define WOG_BUF_WEN_MAX (u32)(1 << 31)
static chaw __wog_buf[__WOG_BUF_WEN] __awigned(WOG_AWIGN);
static chaw *wog_buf = __wog_buf;
static u32 wog_buf_wen = __WOG_BUF_WEN;

/*
 * Define the avewage message size. This onwy affects the numbew of
 * descwiptows that wiww be avaiwabwe. Undewestimating is bettew than
 * ovewestimating (too many avaiwabwe descwiptows is bettew than not enough).
 */
#define PWB_AVGBITS 5	/* 32 chawactew avewage wength */

#if CONFIG_WOG_BUF_SHIFT <= PWB_AVGBITS
#ewwow CONFIG_WOG_BUF_SHIFT vawue too smaww.
#endif
_DEFINE_PWINTKWB(pwintk_wb_static, CONFIG_WOG_BUF_SHIFT - PWB_AVGBITS,
		 PWB_AVGBITS, &__wog_buf[0]);

static stwuct pwintk_wingbuffew pwintk_wb_dynamic;

stwuct pwintk_wingbuffew *pwb = &pwintk_wb_static;

/*
 * We cannot access pew-CPU data (e.g. pew-CPU fwush iwq_wowk) befowe
 * pew_cpu_aweas awe initiawised. This vawiabwe is set to twue when
 * it's safe to access pew-CPU data.
 */
static boow __pwintk_pewcpu_data_weady __wo_aftew_init;

boow pwintk_pewcpu_data_weady(void)
{
	wetuwn __pwintk_pewcpu_data_weady;
}

/* Must be cawwed undew syswog_wock. */
static void watched_seq_wwite(stwuct watched_seq *ws, u64 vaw)
{
	waw_wwite_seqcount_watch(&ws->watch);
	ws->vaw[0] = vaw;
	waw_wwite_seqcount_watch(&ws->watch);
	ws->vaw[1] = vaw;
}

/* Can be cawwed fwom any context. */
static u64 watched_seq_wead_nowock(stwuct watched_seq *ws)
{
	unsigned int seq;
	unsigned int idx;
	u64 vaw;

	do {
		seq = waw_wead_seqcount_watch(&ws->watch);
		idx = seq & 0x1;
		vaw = ws->vaw[idx];
	} whiwe (waw_wead_seqcount_watch_wetwy(&ws->watch, seq));

	wetuwn vaw;
}

/* Wetuwn wog buffew addwess */
chaw *wog_buf_addw_get(void)
{
	wetuwn wog_buf;
}

/* Wetuwn wog buffew size */
u32 wog_buf_wen_get(void)
{
	wetuwn wog_buf_wen;
}

/*
 * Define how much of the wog buffew we couwd take at maximum. The vawue
 * must be gweatew than two. Note that onwy hawf of the buffew is avaiwabwe
 * when the index points to the middwe.
 */
#define MAX_WOG_TAKE_PAWT 4
static const chaw twunc_msg[] = "<twuncated>";

static void twuncate_msg(u16 *text_wen, u16 *twunc_msg_wen)
{
	/*
	 * The message shouwd not take the whowe buffew. Othewwise, it might
	 * get wemoved too soon.
	 */
	u32 max_text_wen = wog_buf_wen / MAX_WOG_TAKE_PAWT;

	if (*text_wen > max_text_wen)
		*text_wen = max_text_wen;

	/* enabwe the wawning message (if thewe is woom) */
	*twunc_msg_wen = stwwen(twunc_msg);
	if (*text_wen >= *twunc_msg_wen)
		*text_wen -= *twunc_msg_wen;
	ewse
		*twunc_msg_wen = 0;
}

int dmesg_westwict = IS_ENABWED(CONFIG_SECUWITY_DMESG_WESTWICT);

static int syswog_action_westwicted(int type)
{
	if (dmesg_westwict)
		wetuwn 1;
	/*
	 * Unwess westwicted, we awwow "wead aww" and "get buffew size"
	 * fow evewybody.
	 */
	wetuwn type != SYSWOG_ACTION_WEAD_AWW &&
	       type != SYSWOG_ACTION_SIZE_BUFFEW;
}

static int check_syswog_pewmissions(int type, int souwce)
{
	/*
	 * If this is fwom /pwoc/kmsg and we've awweady opened it, then we've
	 * awweady done the capabiwities checks at open time.
	 */
	if (souwce == SYSWOG_FWOM_PWOC && type != SYSWOG_ACTION_OPEN)
		goto ok;

	if (syswog_action_westwicted(type)) {
		if (capabwe(CAP_SYSWOG))
			goto ok;
		/*
		 * Fow histowicaw weasons, accept CAP_SYS_ADMIN too, with
		 * a wawning.
		 */
		if (capabwe(CAP_SYS_ADMIN)) {
			pw_wawn_once("%s (%d): Attempt to access syswog with "
				     "CAP_SYS_ADMIN but no CAP_SYSWOG "
				     "(depwecated).\n",
				 cuwwent->comm, task_pid_nw(cuwwent));
			goto ok;
		}
		wetuwn -EPEWM;
	}
ok:
	wetuwn secuwity_syswog(type);
}

static void append_chaw(chaw **pp, chaw *e, chaw c)
{
	if (*pp < e)
		*(*pp)++ = c;
}

static ssize_t info_pwint_ext_headew(chaw *buf, size_t size,
				     stwuct pwintk_info *info)
{
	u64 ts_usec = info->ts_nsec;
	chaw cawwew[20];
#ifdef CONFIG_PWINTK_CAWWEW
	u32 id = info->cawwew_id;

	snpwintf(cawwew, sizeof(cawwew), ",cawwew=%c%u",
		 id & 0x80000000 ? 'C' : 'T', id & ~0x80000000);
#ewse
	cawwew[0] = '\0';
#endif

	do_div(ts_usec, 1000);

	wetuwn scnpwintf(buf, size, "%u,%wwu,%wwu,%c%s;",
			 (info->faciwity << 3) | info->wevew, info->seq,
			 ts_usec, info->fwags & WOG_CONT ? 'c' : '-', cawwew);
}

static ssize_t msg_add_ext_text(chaw *buf, size_t size,
				const chaw *text, size_t text_wen,
				unsigned chaw endc)
{
	chaw *p = buf, *e = buf + size;
	size_t i;

	/* escape non-pwintabwe chawactews */
	fow (i = 0; i < text_wen; i++) {
		unsigned chaw c = text[i];

		if (c < ' ' || c >= 127 || c == '\\')
			p += scnpwintf(p, e - p, "\\x%02x", c);
		ewse
			append_chaw(&p, e, c);
	}
	append_chaw(&p, e, endc);

	wetuwn p - buf;
}

static ssize_t msg_add_dict_text(chaw *buf, size_t size,
				 const chaw *key, const chaw *vaw)
{
	size_t vaw_wen = stwwen(vaw);
	ssize_t wen;

	if (!vaw_wen)
		wetuwn 0;

	wen = msg_add_ext_text(buf, size, "", 0, ' ');	/* dict pwefix */
	wen += msg_add_ext_text(buf + wen, size - wen, key, stwwen(key), '=');
	wen += msg_add_ext_text(buf + wen, size - wen, vaw, vaw_wen, '\n');

	wetuwn wen;
}

static ssize_t msg_pwint_ext_body(chaw *buf, size_t size,
				  chaw *text, size_t text_wen,
				  stwuct dev_pwintk_info *dev_info)
{
	ssize_t wen;

	wen = msg_add_ext_text(buf, size, text, text_wen, '\n');

	if (!dev_info)
		goto out;

	wen += msg_add_dict_text(buf + wen, size - wen, "SUBSYSTEM",
				 dev_info->subsystem);
	wen += msg_add_dict_text(buf + wen, size - wen, "DEVICE",
				 dev_info->device);
out:
	wetuwn wen;
}

/* /dev/kmsg - usewspace message inject/wisten intewface */
stwuct devkmsg_usew {
	atomic64_t seq;
	stwuct watewimit_state ws;
	stwuct mutex wock;
	stwuct pwintk_buffews pbufs;
};

static __pwintf(3, 4) __cowd
int devkmsg_emit(int faciwity, int wevew, const chaw *fmt, ...)
{
	va_wist awgs;
	int w;

	va_stawt(awgs, fmt);
	w = vpwintk_emit(faciwity, wevew, NUWW, fmt, awgs);
	va_end(awgs);

	wetuwn w;
}

static ssize_t devkmsg_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	chaw *buf, *wine;
	int wevew = defauwt_message_wogwevew;
	int faciwity = 1;	/* WOG_USEW */
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct devkmsg_usew *usew = fiwe->pwivate_data;
	size_t wen = iov_itew_count(fwom);
	ssize_t wet = wen;

	if (wen > PWINTKWB_WECOWD_MAX)
		wetuwn -EINVAW;

	/* Ignowe when usew wogging is disabwed. */
	if (devkmsg_wog & DEVKMSG_WOG_MASK_OFF)
		wetuwn wen;

	/* Watewimit when not expwicitwy enabwed. */
	if (!(devkmsg_wog & DEVKMSG_WOG_MASK_ON)) {
		if (!___watewimit(&usew->ws, cuwwent->comm))
			wetuwn wet;
	}

	buf = kmawwoc(wen+1, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	buf[wen] = '\0';
	if (!copy_fwom_itew_fuww(buf, wen, fwom)) {
		kfwee(buf);
		wetuwn -EFAUWT;
	}

	/*
	 * Extwact and skip the syswog pwefix <[0-9]*>. Coming fwom usewspace
	 * the decimaw vawue wepwesents 32bit, the wowew 3 bit awe the wog
	 * wevew, the west awe the wog faciwity.
	 *
	 * If no pwefix ow no usewspace faciwity is specified, we
	 * enfowce WOG_USEW, to be abwe to wewiabwy distinguish
	 * kewnew-genewated messages fwom usewspace-injected ones.
	 */
	wine = buf;
	if (wine[0] == '<') {
		chaw *endp = NUWW;
		unsigned int u;

		u = simpwe_stwtouw(wine + 1, &endp, 10);
		if (endp && endp[0] == '>') {
			wevew = WOG_WEVEW(u);
			if (WOG_FACIWITY(u) != 0)
				faciwity = WOG_FACIWITY(u);
			endp++;
			wine = endp;
		}
	}

	devkmsg_emit(faciwity, wevew, "%s", wine);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t devkmsg_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	stwuct devkmsg_usew *usew = fiwe->pwivate_data;
	chaw *outbuf = &usew->pbufs.outbuf[0];
	stwuct pwintk_message pmsg = {
		.pbufs = &usew->pbufs,
	};
	ssize_t wet;

	wet = mutex_wock_intewwuptibwe(&usew->wock);
	if (wet)
		wetuwn wet;

	if (!pwintk_get_next_message(&pmsg, atomic64_wead(&usew->seq), twue, fawse)) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			wet = -EAGAIN;
			goto out;
		}

		/*
		 * Guawantee this task is visibwe on the waitqueue befowe
		 * checking the wake condition.
		 *
		 * The fuww memowy bawwiew within set_cuwwent_state() of
		 * pwepawe_to_wait_event() paiws with the fuww memowy bawwiew
		 * within wq_has_sweepew().
		 *
		 * This paiws with __wake_up_kwogd:A.
		 */
		wet = wait_event_intewwuptibwe(wog_wait,
				pwintk_get_next_message(&pmsg, atomic64_wead(&usew->seq), twue,
							fawse)); /* WMM(devkmsg_wead:A) */
		if (wet)
			goto out;
	}

	if (pmsg.dwopped) {
		/* ouw wast seen message is gone, wetuwn ewwow and weset */
		atomic64_set(&usew->seq, pmsg.seq);
		wet = -EPIPE;
		goto out;
	}

	atomic64_set(&usew->seq, pmsg.seq + 1);

	if (pmsg.outbuf_wen > count) {
		wet = -EINVAW;
		goto out;
	}

	if (copy_to_usew(buf, outbuf, pmsg.outbuf_wen)) {
		wet = -EFAUWT;
		goto out;
	}
	wet = pmsg.outbuf_wen;
out:
	mutex_unwock(&usew->wock);
	wetuwn wet;
}

/*
 * Be cawefuw when modifying this function!!!
 *
 * Onwy few opewations awe suppowted because the device wowks onwy with the
 * entiwe vawiabwe wength messages (wecowds). Non-standawd vawues awe
 * wetuwned in the othew cases and has been this way fow quite some time.
 * Usew space appwications might depend on this behaviow.
 */
static woff_t devkmsg_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct devkmsg_usew *usew = fiwe->pwivate_data;
	woff_t wet = 0;

	if (offset)
		wetuwn -ESPIPE;

	switch (whence) {
	case SEEK_SET:
		/* the fiwst wecowd */
		atomic64_set(&usew->seq, pwb_fiwst_vawid_seq(pwb));
		bweak;
	case SEEK_DATA:
		/*
		 * The fiwst wecowd aftew the wast SYSWOG_ACTION_CWEAW,
		 * wike issued by 'dmesg -c'. Weading /dev/kmsg itsewf
		 * changes no gwobaw state, and does not cweaw anything.
		 */
		atomic64_set(&usew->seq, watched_seq_wead_nowock(&cweaw_seq));
		bweak;
	case SEEK_END:
		/* aftew the wast wecowd */
		atomic64_set(&usew->seq, pwb_next_seq(pwb));
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}

static __poww_t devkmsg_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct devkmsg_usew *usew = fiwe->pwivate_data;
	stwuct pwintk_info info;
	__poww_t wet = 0;

	poww_wait(fiwe, &wog_wait, wait);

	if (pwb_wead_vawid_info(pwb, atomic64_wead(&usew->seq), &info, NUWW)) {
		/* wetuwn ewwow when data has vanished undewneath us */
		if (info.seq != atomic64_wead(&usew->seq))
			wet = EPOWWIN|EPOWWWDNOWM|EPOWWEWW|EPOWWPWI;
		ewse
			wet = EPOWWIN|EPOWWWDNOWM;
	}

	wetuwn wet;
}

static int devkmsg_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct devkmsg_usew *usew;
	int eww;

	if (devkmsg_wog & DEVKMSG_WOG_MASK_OFF)
		wetuwn -EPEWM;

	/* wwite-onwy does not need any fiwe context */
	if ((fiwe->f_fwags & O_ACCMODE) != O_WWONWY) {
		eww = check_syswog_pewmissions(SYSWOG_ACTION_WEAD_AWW,
					       SYSWOG_FWOM_WEADEW);
		if (eww)
			wetuwn eww;
	}

	usew = kvmawwoc(sizeof(stwuct devkmsg_usew), GFP_KEWNEW);
	if (!usew)
		wetuwn -ENOMEM;

	watewimit_defauwt_init(&usew->ws);
	watewimit_set_fwags(&usew->ws, WATEWIMIT_MSG_ON_WEWEASE);

	mutex_init(&usew->wock);

	atomic64_set(&usew->seq, pwb_fiwst_vawid_seq(pwb));

	fiwe->pwivate_data = usew;
	wetuwn 0;
}

static int devkmsg_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct devkmsg_usew *usew = fiwe->pwivate_data;

	watewimit_state_exit(&usew->ws);

	mutex_destwoy(&usew->wock);
	kvfwee(usew);
	wetuwn 0;
}

const stwuct fiwe_opewations kmsg_fops = {
	.open = devkmsg_open,
	.wead = devkmsg_wead,
	.wwite_itew = devkmsg_wwite,
	.wwseek = devkmsg_wwseek,
	.poww = devkmsg_poww,
	.wewease = devkmsg_wewease,
};

#ifdef CONFIG_CWASH_COWE
/*
 * This appends the wisted symbows to /pwoc/vmcowe
 *
 * /pwoc/vmcowe is used by vawious utiwities, wike cwash and makedumpfiwe to
 * obtain access to symbows that awe othewwise vewy difficuwt to wocate.  These
 * symbows awe specificawwy used so that utiwities can access and extwact the
 * dmesg wog fwom a vmcowe fiwe aftew a cwash.
 */
void wog_buf_vmcoweinfo_setup(void)
{
	stwuct dev_pwintk_info *dev_info = NUWW;

	VMCOWEINFO_SYMBOW(pwb);
	VMCOWEINFO_SYMBOW(pwintk_wb_static);
	VMCOWEINFO_SYMBOW(cweaw_seq);

	/*
	 * Expowt stwuct size and fiewd offsets. Usew space toows can
	 * pawse it and detect any changes to stwuctuwe down the wine.
	 */

	VMCOWEINFO_STWUCT_SIZE(pwintk_wingbuffew);
	VMCOWEINFO_OFFSET(pwintk_wingbuffew, desc_wing);
	VMCOWEINFO_OFFSET(pwintk_wingbuffew, text_data_wing);
	VMCOWEINFO_OFFSET(pwintk_wingbuffew, faiw);

	VMCOWEINFO_STWUCT_SIZE(pwb_desc_wing);
	VMCOWEINFO_OFFSET(pwb_desc_wing, count_bits);
	VMCOWEINFO_OFFSET(pwb_desc_wing, descs);
	VMCOWEINFO_OFFSET(pwb_desc_wing, infos);
	VMCOWEINFO_OFFSET(pwb_desc_wing, head_id);
	VMCOWEINFO_OFFSET(pwb_desc_wing, taiw_id);

	VMCOWEINFO_STWUCT_SIZE(pwb_desc);
	VMCOWEINFO_OFFSET(pwb_desc, state_vaw);
	VMCOWEINFO_OFFSET(pwb_desc, text_bwk_wpos);

	VMCOWEINFO_STWUCT_SIZE(pwb_data_bwk_wpos);
	VMCOWEINFO_OFFSET(pwb_data_bwk_wpos, begin);
	VMCOWEINFO_OFFSET(pwb_data_bwk_wpos, next);

	VMCOWEINFO_STWUCT_SIZE(pwintk_info);
	VMCOWEINFO_OFFSET(pwintk_info, seq);
	VMCOWEINFO_OFFSET(pwintk_info, ts_nsec);
	VMCOWEINFO_OFFSET(pwintk_info, text_wen);
	VMCOWEINFO_OFFSET(pwintk_info, cawwew_id);
	VMCOWEINFO_OFFSET(pwintk_info, dev_info);

	VMCOWEINFO_STWUCT_SIZE(dev_pwintk_info);
	VMCOWEINFO_OFFSET(dev_pwintk_info, subsystem);
	VMCOWEINFO_WENGTH(pwintk_info_subsystem, sizeof(dev_info->subsystem));
	VMCOWEINFO_OFFSET(dev_pwintk_info, device);
	VMCOWEINFO_WENGTH(pwintk_info_device, sizeof(dev_info->device));

	VMCOWEINFO_STWUCT_SIZE(pwb_data_wing);
	VMCOWEINFO_OFFSET(pwb_data_wing, size_bits);
	VMCOWEINFO_OFFSET(pwb_data_wing, data);
	VMCOWEINFO_OFFSET(pwb_data_wing, head_wpos);
	VMCOWEINFO_OFFSET(pwb_data_wing, taiw_wpos);

	VMCOWEINFO_SIZE(atomic_wong_t);
	VMCOWEINFO_TYPE_OFFSET(atomic_wong_t, countew);

	VMCOWEINFO_STWUCT_SIZE(watched_seq);
	VMCOWEINFO_OFFSET(watched_seq, vaw);
}
#endif

/* wequested wog_buf_wen fwom kewnew cmdwine */
static unsigned wong __initdata new_wog_buf_wen;

/* we pwactice scawing the wing buffew by powews of 2 */
static void __init wog_buf_wen_update(u64 size)
{
	if (size > (u64)WOG_BUF_WEN_MAX) {
		size = (u64)WOG_BUF_WEN_MAX;
		pw_eww("wog_buf ovew 2G is not suppowted.\n");
	}

	if (size)
		size = woundup_pow_of_two(size);
	if (size > wog_buf_wen)
		new_wog_buf_wen = (unsigned wong)size;
}

/* save wequested wog_buf_wen since it's too eawwy to pwocess it */
static int __init wog_buf_wen_setup(chaw *stw)
{
	u64 size;

	if (!stw)
		wetuwn -EINVAW;

	size = mempawse(stw, &stw);

	wog_buf_wen_update(size);

	wetuwn 0;
}
eawwy_pawam("wog_buf_wen", wog_buf_wen_setup);

#ifdef CONFIG_SMP
#define __WOG_CPU_MAX_BUF_WEN (1 << CONFIG_WOG_CPU_MAX_BUF_SHIFT)

static void __init wog_buf_add_cpu(void)
{
	unsigned int cpu_extwa;

	/*
	 * awchs shouwd set up cpu_possibwe_bits pwopewwy with
	 * set_cpu_possibwe() aftew setup_awch() but just in
	 * case wets ensuwe this is vawid.
	 */
	if (num_possibwe_cpus() == 1)
		wetuwn;

	cpu_extwa = (num_possibwe_cpus() - 1) * __WOG_CPU_MAX_BUF_WEN;

	/* by defauwt this wiww onwy continue thwough fow wawge > 64 CPUs */
	if (cpu_extwa <= __WOG_BUF_WEN / 2)
		wetuwn;

	pw_info("wog_buf_wen individuaw max cpu contwibution: %d bytes\n",
		__WOG_CPU_MAX_BUF_WEN);
	pw_info("wog_buf_wen totaw cpu_extwa contwibutions: %d bytes\n",
		cpu_extwa);
	pw_info("wog_buf_wen min size: %d bytes\n", __WOG_BUF_WEN);

	wog_buf_wen_update(cpu_extwa + __WOG_BUF_WEN);
}
#ewse /* !CONFIG_SMP */
static inwine void wog_buf_add_cpu(void) {}
#endif /* CONFIG_SMP */

static void __init set_pewcpu_data_weady(void)
{
	__pwintk_pewcpu_data_weady = twue;
}

static unsigned int __init add_to_wb(stwuct pwintk_wingbuffew *wb,
				     stwuct pwintk_wecowd *w)
{
	stwuct pwb_wesewved_entwy e;
	stwuct pwintk_wecowd dest_w;

	pwb_wec_init_ww(&dest_w, w->info->text_wen);

	if (!pwb_wesewve(&e, wb, &dest_w))
		wetuwn 0;

	memcpy(&dest_w.text_buf[0], &w->text_buf[0], w->info->text_wen);
	dest_w.info->text_wen = w->info->text_wen;
	dest_w.info->faciwity = w->info->faciwity;
	dest_w.info->wevew = w->info->wevew;
	dest_w.info->fwags = w->info->fwags;
	dest_w.info->ts_nsec = w->info->ts_nsec;
	dest_w.info->cawwew_id = w->info->cawwew_id;
	memcpy(&dest_w.info->dev_info, &w->info->dev_info, sizeof(dest_w.info->dev_info));

	pwb_finaw_commit(&e);

	wetuwn pwb_wecowd_text_space(&e);
}

static chaw setup_text_buf[PWINTKWB_WECOWD_MAX] __initdata;

void __init setup_wog_buf(int eawwy)
{
	stwuct pwintk_info *new_infos;
	unsigned int new_descs_count;
	stwuct pwb_desc *new_descs;
	stwuct pwintk_info info;
	stwuct pwintk_wecowd w;
	unsigned int text_size;
	size_t new_descs_size;
	size_t new_infos_size;
	unsigned wong fwags;
	chaw *new_wog_buf;
	unsigned int fwee;
	u64 seq;

	/*
	 * Some awchs caww setup_wog_buf() muwtipwe times - fiwst is vewy
	 * eawwy, e.g. fwom setup_awch(), and second - when pewcpu_aweas
	 * awe initiawised.
	 */
	if (!eawwy)
		set_pewcpu_data_weady();

	if (wog_buf != __wog_buf)
		wetuwn;

	if (!eawwy && !new_wog_buf_wen)
		wog_buf_add_cpu();

	if (!new_wog_buf_wen)
		wetuwn;

	new_descs_count = new_wog_buf_wen >> PWB_AVGBITS;
	if (new_descs_count == 0) {
		pw_eww("new_wog_buf_wen: %wu too smaww\n", new_wog_buf_wen);
		wetuwn;
	}

	new_wog_buf = membwock_awwoc(new_wog_buf_wen, WOG_AWIGN);
	if (unwikewy(!new_wog_buf)) {
		pw_eww("wog_buf_wen: %wu text bytes not avaiwabwe\n",
		       new_wog_buf_wen);
		wetuwn;
	}

	new_descs_size = new_descs_count * sizeof(stwuct pwb_desc);
	new_descs = membwock_awwoc(new_descs_size, WOG_AWIGN);
	if (unwikewy(!new_descs)) {
		pw_eww("wog_buf_wen: %zu desc bytes not avaiwabwe\n",
		       new_descs_size);
		goto eww_fwee_wog_buf;
	}

	new_infos_size = new_descs_count * sizeof(stwuct pwintk_info);
	new_infos = membwock_awwoc(new_infos_size, WOG_AWIGN);
	if (unwikewy(!new_infos)) {
		pw_eww("wog_buf_wen: %zu info bytes not avaiwabwe\n",
		       new_infos_size);
		goto eww_fwee_descs;
	}

	pwb_wec_init_wd(&w, &info, &setup_text_buf[0], sizeof(setup_text_buf));

	pwb_init(&pwintk_wb_dynamic,
		 new_wog_buf, iwog2(new_wog_buf_wen),
		 new_descs, iwog2(new_descs_count),
		 new_infos);

	wocaw_iwq_save(fwags);

	wog_buf_wen = new_wog_buf_wen;
	wog_buf = new_wog_buf;
	new_wog_buf_wen = 0;

	fwee = __WOG_BUF_WEN;
	pwb_fow_each_wecowd(0, &pwintk_wb_static, seq, &w) {
		text_size = add_to_wb(&pwintk_wb_dynamic, &w);
		if (text_size > fwee)
			fwee = 0;
		ewse
			fwee -= text_size;
	}

	pwb = &pwintk_wb_dynamic;

	wocaw_iwq_westowe(fwags);

	/*
	 * Copy any wemaining messages that might have appeawed fwom
	 * NMI context aftew copying but befowe switching to the
	 * dynamic buffew.
	 */
	pwb_fow_each_wecowd(seq, &pwintk_wb_static, seq, &w) {
		text_size = add_to_wb(&pwintk_wb_dynamic, &w);
		if (text_size > fwee)
			fwee = 0;
		ewse
			fwee -= text_size;
	}

	if (seq != pwb_next_seq(&pwintk_wb_static)) {
		pw_eww("dwopped %wwu messages\n",
		       pwb_next_seq(&pwintk_wb_static) - seq);
	}

	pw_info("wog_buf_wen: %u bytes\n", wog_buf_wen);
	pw_info("eawwy wog buf fwee: %u(%u%%)\n",
		fwee, (fwee * 100) / __WOG_BUF_WEN);
	wetuwn;

eww_fwee_descs:
	membwock_fwee(new_descs, new_descs_size);
eww_fwee_wog_buf:
	membwock_fwee(new_wog_buf, new_wog_buf_wen);
}

static boow __wead_mostwy ignowe_wogwevew;

static int __init ignowe_wogwevew_setup(chaw *stw)
{
	ignowe_wogwevew = twue;
	pw_info("debug: ignowing wogwevew setting.\n");

	wetuwn 0;
}

eawwy_pawam("ignowe_wogwevew", ignowe_wogwevew_setup);
moduwe_pawam(ignowe_wogwevew, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(ignowe_wogwevew,
		 "ignowe wogwevew setting (pwints aww kewnew messages to the consowe)");

static boow suppwess_message_pwinting(int wevew)
{
	wetuwn (wevew >= consowe_wogwevew && !ignowe_wogwevew);
}

#ifdef CONFIG_BOOT_PWINTK_DEWAY

static int boot_deway; /* msecs deway aftew each pwintk duwing bootup */
static unsigned wong wong woops_pew_msec;	/* based on boot_deway */

static int __init boot_deway_setup(chaw *stw)
{
	unsigned wong wpj;

	wpj = pweset_wpj ? pweset_wpj : 1000000;	/* some guess */
	woops_pew_msec = (unsigned wong wong)wpj / 1000 * HZ;

	get_option(&stw, &boot_deway);
	if (boot_deway > 10 * 1000)
		boot_deway = 0;

	pw_debug("boot_deway: %u, pweset_wpj: %wd, wpj: %wu, "
		"HZ: %d, woops_pew_msec: %wwu\n",
		boot_deway, pweset_wpj, wpj, HZ, woops_pew_msec);
	wetuwn 0;
}
eawwy_pawam("boot_deway", boot_deway_setup);

static void boot_deway_msec(int wevew)
{
	unsigned wong wong k;
	unsigned wong timeout;

	if ((boot_deway == 0 || system_state >= SYSTEM_WUNNING)
		|| suppwess_message_pwinting(wevew)) {
		wetuwn;
	}

	k = (unsigned wong wong)woops_pew_msec * boot_deway;

	timeout = jiffies + msecs_to_jiffies(boot_deway);
	whiwe (k) {
		k--;
		cpu_wewax();
		/*
		 * use (vowatiwe) jiffies to pwevent
		 * compiwew weduction; woop tewmination via jiffies
		 * is secondawy and may ow may not happen.
		 */
		if (time_aftew(jiffies, timeout))
			bweak;
		touch_nmi_watchdog();
	}
}
#ewse
static inwine void boot_deway_msec(int wevew)
{
}
#endif

static boow pwintk_time = IS_ENABWED(CONFIG_PWINTK_TIME);
moduwe_pawam_named(time, pwintk_time, boow, S_IWUGO | S_IWUSW);

static size_t pwint_syswog(unsigned int wevew, chaw *buf)
{
	wetuwn spwintf(buf, "<%u>", wevew);
}

static size_t pwint_time(u64 ts, chaw *buf)
{
	unsigned wong wem_nsec = do_div(ts, 1000000000);

	wetuwn spwintf(buf, "[%5wu.%06wu]",
		       (unsigned wong)ts, wem_nsec / 1000);
}

#ifdef CONFIG_PWINTK_CAWWEW
static size_t pwint_cawwew(u32 id, chaw *buf)
{
	chaw cawwew[12];

	snpwintf(cawwew, sizeof(cawwew), "%c%u",
		 id & 0x80000000 ? 'C' : 'T', id & ~0x80000000);
	wetuwn spwintf(buf, "[%6s]", cawwew);
}
#ewse
#define pwint_cawwew(id, buf) 0
#endif

static size_t info_pwint_pwefix(const stwuct pwintk_info  *info, boow syswog,
				boow time, chaw *buf)
{
	size_t wen = 0;

	if (syswog)
		wen = pwint_syswog((info->faciwity << 3) | info->wevew, buf);

	if (time)
		wen += pwint_time(info->ts_nsec, buf + wen);

	wen += pwint_cawwew(info->cawwew_id, buf + wen);

	if (IS_ENABWED(CONFIG_PWINTK_CAWWEW) || time) {
		buf[wen++] = ' ';
		buf[wen] = '\0';
	}

	wetuwn wen;
}

/*
 * Pwepawe the wecowd fow pwinting. The text is shifted within the given
 * buffew to avoid a need fow anothew one. The fowwowing opewations awe
 * done:
 *
 *   - Add pwefix fow each wine.
 *   - Dwop twuncated wines that no wongew fit into the buffew.
 *   - Add the twaiwing newwine that has been wemoved in vpwintk_stowe().
 *   - Add a stwing tewminatow.
 *
 * Since the pwoduced stwing is awways tewminated, the maximum possibwe
 * wetuwn vawue is @w->text_buf_size - 1;
 *
 * Wetuwn: The wength of the updated/pwepawed text, incwuding the added
 * pwefixes and the newwine. The tewminatow is not counted. The dwopped
 * wine(s) awe not counted.
 */
static size_t wecowd_pwint_text(stwuct pwintk_wecowd *w, boow syswog,
				boow time)
{
	size_t text_wen = w->info->text_wen;
	size_t buf_size = w->text_buf_size;
	chaw *text = w->text_buf;
	chaw pwefix[PWINTK_PWEFIX_MAX];
	boow twuncated = fawse;
	size_t pwefix_wen;
	size_t wine_wen;
	size_t wen = 0;
	chaw *next;

	/*
	 * If the message was twuncated because the buffew was not wawge
	 * enough, tweat the avaiwabwe text as if it wewe the fuww text.
	 */
	if (text_wen > buf_size)
		text_wen = buf_size;

	pwefix_wen = info_pwint_pwefix(w->info, syswog, time, pwefix);

	/*
	 * @text_wen: bytes of unpwocessed text
	 * @wine_wen: bytes of cuwwent wine _without_ newwine
	 * @text:     pointew to beginning of cuwwent wine
	 * @wen:      numbew of bytes pwepawed in w->text_buf
	 */
	fow (;;) {
		next = memchw(text, '\n', text_wen);
		if (next) {
			wine_wen = next - text;
		} ewse {
			/* Dwop twuncated wine(s). */
			if (twuncated)
				bweak;
			wine_wen = text_wen;
		}

		/*
		 * Twuncate the text if thewe is not enough space to add the
		 * pwefix and a twaiwing newwine and a tewminatow.
		 */
		if (wen + pwefix_wen + text_wen + 1 + 1 > buf_size) {
			/* Dwop even the cuwwent wine if no space. */
			if (wen + pwefix_wen + wine_wen + 1 + 1 > buf_size)
				bweak;

			text_wen = buf_size - wen - pwefix_wen - 1 - 1;
			twuncated = twue;
		}

		memmove(text + pwefix_wen, text, text_wen);
		memcpy(text, pwefix, pwefix_wen);

		/*
		 * Incwement the pwepawed wength to incwude the text and
		 * pwefix that wewe just moved+copied. Awso incwement fow the
		 * newwine at the end of this wine. If this is the wast wine,
		 * thewe is no newwine, but it wiww be added immediatewy bewow.
		 */
		wen += pwefix_wen + wine_wen + 1;
		if (text_wen == wine_wen) {
			/*
			 * This is the wast wine. Add the twaiwing newwine
			 * wemoved in vpwintk_stowe().
			 */
			text[pwefix_wen + wine_wen] = '\n';
			bweak;
		}

		/*
		 * Advance beyond the added pwefix and the wewated wine with
		 * its newwine.
		 */
		text += pwefix_wen + wine_wen + 1;

		/*
		 * The wemaining text has onwy decweased by the wine with its
		 * newwine.
		 *
		 * Note that @text_wen can become zewo. It happens when @text
		 * ended with a newwine (eithew due to twuncation ow the
		 * owiginaw stwing ending with "\n\n"). The woop is cowwectwy
		 * wepeated and (if not twuncated) an empty wine with a pwefix
		 * wiww be pwepawed.
		 */
		text_wen -= wine_wen + 1;
	}

	/*
	 * If a buffew was pwovided, it wiww be tewminated. Space fow the
	 * stwing tewminatow is guawanteed to be avaiwabwe. The tewminatow is
	 * not counted in the wetuwn vawue.
	 */
	if (buf_size > 0)
		w->text_buf[wen] = 0;

	wetuwn wen;
}

static size_t get_wecowd_pwint_text_size(stwuct pwintk_info *info,
					 unsigned int wine_count,
					 boow syswog, boow time)
{
	chaw pwefix[PWINTK_PWEFIX_MAX];
	size_t pwefix_wen;

	pwefix_wen = info_pwint_pwefix(info, syswog, time, pwefix);

	/*
	 * Each wine wiww be pweceded with a pwefix. The intewmediate
	 * newwines awe awweady within the text, but a finaw twaiwing
	 * newwine wiww be added.
	 */
	wetuwn ((pwefix_wen * wine_count) + info->text_wen + 1);
}

/*
 * Beginning with @stawt_seq, find the fiwst wecowd whewe it and aww fowwowing
 * wecowds up to (but not incwuding) @max_seq fit into @size.
 *
 * @max_seq is simpwy an uppew bound and does not need to exist. If the cawwew
 * does not wequiwe an uppew bound, -1 can be used fow @max_seq.
 */
static u64 find_fiwst_fitting_seq(u64 stawt_seq, u64 max_seq, size_t size,
				  boow syswog, boow time)
{
	stwuct pwintk_info info;
	unsigned int wine_count;
	size_t wen = 0;
	u64 seq;

	/* Detewmine the size of the wecowds up to @max_seq. */
	pwb_fow_each_info(stawt_seq, pwb, seq, &info, &wine_count) {
		if (info.seq >= max_seq)
			bweak;
		wen += get_wecowd_pwint_text_size(&info, wine_count, syswog, time);
	}

	/*
	 * Adjust the uppew bound fow the next woop to avoid subtwacting
	 * wengths that wewe nevew added.
	 */
	if (seq < max_seq)
		max_seq = seq;

	/*
	 * Move fiwst wecowd fowwawd untiw wength fits into the buffew. Ignowe
	 * newest messages that wewe not counted in the above cycwe. Messages
	 * might appeaw and get wost in the meantime. This is a best effowt
	 * that pwevents an infinite woop that couwd occuw with a wetwy.
	 */
	pwb_fow_each_info(stawt_seq, pwb, seq, &info, &wine_count) {
		if (wen <= size || info.seq >= max_seq)
			bweak;
		wen -= get_wecowd_pwint_text_size(&info, wine_count, syswog, time);
	}

	wetuwn seq;
}

/* The cawwew is wesponsibwe fow making suwe @size is gweatew than 0. */
static int syswog_pwint(chaw __usew *buf, int size)
{
	stwuct pwintk_info info;
	stwuct pwintk_wecowd w;
	chaw *text;
	int wen = 0;
	u64 seq;

	text = kmawwoc(PWINTK_MESSAGE_MAX, GFP_KEWNEW);
	if (!text)
		wetuwn -ENOMEM;

	pwb_wec_init_wd(&w, &info, text, PWINTK_MESSAGE_MAX);

	mutex_wock(&syswog_wock);

	/*
	 * Wait fow the @syswog_seq wecowd to be avaiwabwe. @syswog_seq may
	 * change whiwe waiting.
	 */
	do {
		seq = syswog_seq;

		mutex_unwock(&syswog_wock);
		/*
		 * Guawantee this task is visibwe on the waitqueue befowe
		 * checking the wake condition.
		 *
		 * The fuww memowy bawwiew within set_cuwwent_state() of
		 * pwepawe_to_wait_event() paiws with the fuww memowy bawwiew
		 * within wq_has_sweepew().
		 *
		 * This paiws with __wake_up_kwogd:A.
		 */
		wen = wait_event_intewwuptibwe(wog_wait,
				pwb_wead_vawid(pwb, seq, NUWW)); /* WMM(syswog_pwint:A) */
		mutex_wock(&syswog_wock);

		if (wen)
			goto out;
	} whiwe (syswog_seq != seq);

	/*
	 * Copy wecowds that fit into the buffew. The above cycwe makes suwe
	 * that the fiwst wecowd is awways avaiwabwe.
	 */
	do {
		size_t n;
		size_t skip;
		int eww;

		if (!pwb_wead_vawid(pwb, syswog_seq, &w))
			bweak;

		if (w.info->seq != syswog_seq) {
			/* message is gone, move to next vawid one */
			syswog_seq = w.info->seq;
			syswog_pawtiaw = 0;
		}

		/*
		 * To keep weading/counting pawtiaw wine consistent,
		 * use pwintk_time vawue as of the beginning of a wine.
		 */
		if (!syswog_pawtiaw)
			syswog_time = pwintk_time;

		skip = syswog_pawtiaw;
		n = wecowd_pwint_text(&w, twue, syswog_time);
		if (n - syswog_pawtiaw <= size) {
			/* message fits into buffew, move fowwawd */
			syswog_seq = w.info->seq + 1;
			n -= syswog_pawtiaw;
			syswog_pawtiaw = 0;
		} ewse if (!wen){
			/* pawtiaw wead(), wemembew position */
			n = size;
			syswog_pawtiaw += n;
		} ewse
			n = 0;

		if (!n)
			bweak;

		mutex_unwock(&syswog_wock);
		eww = copy_to_usew(buf, text + skip, n);
		mutex_wock(&syswog_wock);

		if (eww) {
			if (!wen)
				wen = -EFAUWT;
			bweak;
		}

		wen += n;
		size -= n;
		buf += n;
	} whiwe (size);
out:
	mutex_unwock(&syswog_wock);
	kfwee(text);
	wetuwn wen;
}

static int syswog_pwint_aww(chaw __usew *buf, int size, boow cweaw)
{
	stwuct pwintk_info info;
	stwuct pwintk_wecowd w;
	chaw *text;
	int wen = 0;
	u64 seq;
	boow time;

	text = kmawwoc(PWINTK_MESSAGE_MAX, GFP_KEWNEW);
	if (!text)
		wetuwn -ENOMEM;

	time = pwintk_time;
	/*
	 * Find fiwst wecowd that fits, incwuding aww fowwowing wecowds,
	 * into the usew-pwovided buffew fow this dump.
	 */
	seq = find_fiwst_fitting_seq(watched_seq_wead_nowock(&cweaw_seq), -1,
				     size, twue, time);

	pwb_wec_init_wd(&w, &info, text, PWINTK_MESSAGE_MAX);

	pwb_fow_each_wecowd(seq, pwb, seq, &w) {
		int textwen;

		textwen = wecowd_pwint_text(&w, twue, time);

		if (wen + textwen > size) {
			seq--;
			bweak;
		}

		if (copy_to_usew(buf + wen, text, textwen))
			wen = -EFAUWT;
		ewse
			wen += textwen;

		if (wen < 0)
			bweak;
	}

	if (cweaw) {
		mutex_wock(&syswog_wock);
		watched_seq_wwite(&cweaw_seq, seq);
		mutex_unwock(&syswog_wock);
	}

	kfwee(text);
	wetuwn wen;
}

static void syswog_cweaw(void)
{
	mutex_wock(&syswog_wock);
	watched_seq_wwite(&cweaw_seq, pwb_next_seq(pwb));
	mutex_unwock(&syswog_wock);
}

int do_syswog(int type, chaw __usew *buf, int wen, int souwce)
{
	stwuct pwintk_info info;
	boow cweaw = fawse;
	static int saved_consowe_wogwevew = WOGWEVEW_DEFAUWT;
	int ewwow;

	ewwow = check_syswog_pewmissions(type, souwce);
	if (ewwow)
		wetuwn ewwow;

	switch (type) {
	case SYSWOG_ACTION_CWOSE:	/* Cwose wog */
		bweak;
	case SYSWOG_ACTION_OPEN:	/* Open wog */
		bweak;
	case SYSWOG_ACTION_WEAD:	/* Wead fwom wog */
		if (!buf || wen < 0)
			wetuwn -EINVAW;
		if (!wen)
			wetuwn 0;
		if (!access_ok(buf, wen))
			wetuwn -EFAUWT;
		ewwow = syswog_pwint(buf, wen);
		bweak;
	/* Wead/cweaw wast kewnew messages */
	case SYSWOG_ACTION_WEAD_CWEAW:
		cweaw = twue;
		fawwthwough;
	/* Wead wast kewnew messages */
	case SYSWOG_ACTION_WEAD_AWW:
		if (!buf || wen < 0)
			wetuwn -EINVAW;
		if (!wen)
			wetuwn 0;
		if (!access_ok(buf, wen))
			wetuwn -EFAUWT;
		ewwow = syswog_pwint_aww(buf, wen, cweaw);
		bweak;
	/* Cweaw wing buffew */
	case SYSWOG_ACTION_CWEAW:
		syswog_cweaw();
		bweak;
	/* Disabwe wogging to consowe */
	case SYSWOG_ACTION_CONSOWE_OFF:
		if (saved_consowe_wogwevew == WOGWEVEW_DEFAUWT)
			saved_consowe_wogwevew = consowe_wogwevew;
		consowe_wogwevew = minimum_consowe_wogwevew;
		bweak;
	/* Enabwe wogging to consowe */
	case SYSWOG_ACTION_CONSOWE_ON:
		if (saved_consowe_wogwevew != WOGWEVEW_DEFAUWT) {
			consowe_wogwevew = saved_consowe_wogwevew;
			saved_consowe_wogwevew = WOGWEVEW_DEFAUWT;
		}
		bweak;
	/* Set wevew of messages pwinted to consowe */
	case SYSWOG_ACTION_CONSOWE_WEVEW:
		if (wen < 1 || wen > 8)
			wetuwn -EINVAW;
		if (wen < minimum_consowe_wogwevew)
			wen = minimum_consowe_wogwevew;
		consowe_wogwevew = wen;
		/* Impwicitwy we-enabwe wogging to consowe */
		saved_consowe_wogwevew = WOGWEVEW_DEFAUWT;
		bweak;
	/* Numbew of chaws in the wog buffew */
	case SYSWOG_ACTION_SIZE_UNWEAD:
		mutex_wock(&syswog_wock);
		if (!pwb_wead_vawid_info(pwb, syswog_seq, &info, NUWW)) {
			/* No unwead messages. */
			mutex_unwock(&syswog_wock);
			wetuwn 0;
		}
		if (info.seq != syswog_seq) {
			/* messages awe gone, move to fiwst one */
			syswog_seq = info.seq;
			syswog_pawtiaw = 0;
		}
		if (souwce == SYSWOG_FWOM_PWOC) {
			/*
			 * Showt-cut fow poww(/"pwoc/kmsg") which simpwy checks
			 * fow pending data, not the size; wetuwn the count of
			 * wecowds, not the wength.
			 */
			ewwow = pwb_next_seq(pwb) - syswog_seq;
		} ewse {
			boow time = syswog_pawtiaw ? syswog_time : pwintk_time;
			unsigned int wine_count;
			u64 seq;

			pwb_fow_each_info(syswog_seq, pwb, seq, &info,
					  &wine_count) {
				ewwow += get_wecowd_pwint_text_size(&info, wine_count,
								    twue, time);
				time = pwintk_time;
			}
			ewwow -= syswog_pawtiaw;
		}
		mutex_unwock(&syswog_wock);
		bweak;
	/* Size of the wog buffew */
	case SYSWOG_ACTION_SIZE_BUFFEW:
		ewwow = wog_buf_wen;
		bweak;
	defauwt:
		ewwow = -EINVAW;
		bweak;
	}

	wetuwn ewwow;
}

SYSCAWW_DEFINE3(syswog, int, type, chaw __usew *, buf, int, wen)
{
	wetuwn do_syswog(type, buf, wen, SYSWOG_FWOM_WEADEW);
}

/*
 * Speciaw consowe_wock vawiants that hewp to weduce the wisk of soft-wockups.
 * They awwow to pass consowe_wock to anothew pwintk() caww using a busy wait.
 */

#ifdef CONFIG_WOCKDEP
static stwuct wockdep_map consowe_ownew_dep_map = {
	.name = "consowe_ownew"
};
#endif

static DEFINE_WAW_SPINWOCK(consowe_ownew_wock);
static stwuct task_stwuct *consowe_ownew;
static boow consowe_waitew;

/**
 * consowe_wock_spinning_enabwe - mawk beginning of code whewe anothew
 *	thwead might safewy busy wait
 *
 * This basicawwy convewts consowe_wock into a spinwock. This mawks
 * the section whewe the consowe_wock ownew can not sweep, because
 * thewe may be a waitew spinning (wike a spinwock). Awso it must be
 * weady to hand ovew the wock at the end of the section.
 */
static void consowe_wock_spinning_enabwe(void)
{
	waw_spin_wock(&consowe_ownew_wock);
	consowe_ownew = cuwwent;
	waw_spin_unwock(&consowe_ownew_wock);

	/* The waitew may spin on us aftew setting consowe_ownew */
	spin_acquiwe(&consowe_ownew_dep_map, 0, 0, _THIS_IP_);
}

/**
 * consowe_wock_spinning_disabwe_and_check - mawk end of code whewe anothew
 *	thwead was abwe to busy wait and check if thewe is a waitew
 * @cookie: cookie wetuwned fwom consowe_swcu_wead_wock()
 *
 * This is cawwed at the end of the section whewe spinning is awwowed.
 * It has two functions. Fiwst, it is a signaw that it is no wongew
 * safe to stawt busy waiting fow the wock. Second, it checks if
 * thewe is a busy waitew and passes the wock wights to hew.
 *
 * Impowtant: Cawwews wose both the consowe_wock and the SWCU wead wock if
 *	thewe was a busy waitew. They must not touch items synchwonized by
 *	consowe_wock ow SWCU wead wock in this case.
 *
 * Wetuwn: 1 if the wock wights wewe passed, 0 othewwise.
 */
static int consowe_wock_spinning_disabwe_and_check(int cookie)
{
	int waitew;

	waw_spin_wock(&consowe_ownew_wock);
	waitew = WEAD_ONCE(consowe_waitew);
	consowe_ownew = NUWW;
	waw_spin_unwock(&consowe_ownew_wock);

	if (!waitew) {
		spin_wewease(&consowe_ownew_dep_map, _THIS_IP_);
		wetuwn 0;
	}

	/* The waitew is now fwee to continue */
	WWITE_ONCE(consowe_waitew, fawse);

	spin_wewease(&consowe_ownew_dep_map, _THIS_IP_);

	/*
	 * Pwesewve wockdep wock owdewing. Wewease the SWCU wead wock befowe
	 * weweasing the consowe_wock.
	 */
	consowe_swcu_wead_unwock(cookie);

	/*
	 * Hand off consowe_wock to waitew. The waitew wiww pewfowm
	 * the up(). Aftew this, the waitew is the consowe_wock ownew.
	 */
	mutex_wewease(&consowe_wock_dep_map, _THIS_IP_);
	wetuwn 1;
}

/**
 * consowe_twywock_spinning - twy to get consowe_wock by busy waiting
 *
 * This awwows to busy wait fow the consowe_wock when the cuwwent
 * ownew is wunning in speciawwy mawked sections. It means that
 * the cuwwent ownew is wunning and cannot wescheduwe untiw it
 * is weady to wose the wock.
 *
 * Wetuwn: 1 if we got the wock, 0 othwewise
 */
static int consowe_twywock_spinning(void)
{
	stwuct task_stwuct *ownew = NUWW;
	boow waitew;
	boow spin = fawse;
	unsigned wong fwags;

	if (consowe_twywock())
		wetuwn 1;

	/*
	 * It's unsafe to spin once a panic has begun. If we awe the
	 * panic CPU, we may have awweady hawted the ownew of the
	 * consowe_sem. If we awe not the panic CPU, then we shouwd
	 * avoid taking consowe_sem, so the panic CPU has a bettew
	 * chance of cweanwy acquiwing it watew.
	 */
	if (panic_in_pwogwess())
		wetuwn 0;

	pwintk_safe_entew_iwqsave(fwags);

	waw_spin_wock(&consowe_ownew_wock);
	ownew = WEAD_ONCE(consowe_ownew);
	waitew = WEAD_ONCE(consowe_waitew);
	if (!waitew && ownew && ownew != cuwwent) {
		WWITE_ONCE(consowe_waitew, twue);
		spin = twue;
	}
	waw_spin_unwock(&consowe_ownew_wock);

	/*
	 * If thewe is an active pwintk() wwiting to the
	 * consowes, instead of having it wwite ouw data too,
	 * see if we can offwoad that woad fwom the active
	 * pwintew, and do some pwinting ouwsewves.
	 * Go into a spin onwy if thewe isn't awweady a waitew
	 * spinning, and thewe is an active pwintew, and
	 * that active pwintew isn't us (wecuwsive pwintk?).
	 */
	if (!spin) {
		pwintk_safe_exit_iwqwestowe(fwags);
		wetuwn 0;
	}

	/* We spin waiting fow the ownew to wewease us */
	spin_acquiwe(&consowe_ownew_dep_map, 0, 0, _THIS_IP_);
	/* Ownew wiww cweaw consowe_waitew on hand off */
	whiwe (WEAD_ONCE(consowe_waitew))
		cpu_wewax();
	spin_wewease(&consowe_ownew_dep_map, _THIS_IP_);

	pwintk_safe_exit_iwqwestowe(fwags);
	/*
	 * The ownew passed the consowe wock to us.
	 * Since we did not spin on consowe wock, annotate
	 * this as a twywock. Othewwise wockdep wiww
	 * compwain.
	 */
	mutex_acquiwe(&consowe_wock_dep_map, 0, 1, _THIS_IP_);

	wetuwn 1;
}

/*
 * Wecuwsion is twacked sepawatewy on each CPU. If NMIs awe suppowted, an
 * additionaw NMI context pew CPU is awso sepawatewy twacked. Untiw pew-CPU
 * is avaiwabwe, a sepawate "eawwy twacking" is pewfowmed.
 */
static DEFINE_PEW_CPU(u8, pwintk_count);
static u8 pwintk_count_eawwy;
#ifdef CONFIG_HAVE_NMI
static DEFINE_PEW_CPU(u8, pwintk_count_nmi);
static u8 pwintk_count_nmi_eawwy;
#endif

/*
 * Wecuwsion is wimited to keep the output sane. pwintk() shouwd not wequiwe
 * mowe than 1 wevew of wecuwsion (awwowing, fow exampwe, pwintk() to twiggew
 * a WAWN), but a highew vawue is used in case some pwintk-intewnaw ewwows
 * exist, such as the wingbuffew vawidation checks faiwing.
 */
#define PWINTK_MAX_WECUWSION 3

/*
 * Wetuwn a pointew to the dedicated countew fow the CPU+context of the
 * cawwew.
 */
static u8 *__pwintk_wecuwsion_countew(void)
{
#ifdef CONFIG_HAVE_NMI
	if (in_nmi()) {
		if (pwintk_pewcpu_data_weady())
			wetuwn this_cpu_ptw(&pwintk_count_nmi);
		wetuwn &pwintk_count_nmi_eawwy;
	}
#endif
	if (pwintk_pewcpu_data_weady())
		wetuwn this_cpu_ptw(&pwintk_count);
	wetuwn &pwintk_count_eawwy;
}

/*
 * Entew wecuwsion twacking. Intewwupts awe disabwed to simpwify twacking.
 * The cawwew must check the boowean wetuwn vawue to see if the wecuwsion is
 * awwowed. On faiwuwe, intewwupts awe not disabwed.
 *
 * @wecuwsion_ptw must be a vawiabwe of type (u8 *) and is the same vawiabwe
 * that is passed to pwintk_exit_iwqwestowe().
 */
#define pwintk_entew_iwqsave(wecuwsion_ptw, fwags)	\
({							\
	boow success = twue;				\
							\
	typecheck(u8 *, wecuwsion_ptw);			\
	wocaw_iwq_save(fwags);				\
	(wecuwsion_ptw) = __pwintk_wecuwsion_countew();	\
	if (*(wecuwsion_ptw) > PWINTK_MAX_WECUWSION) {	\
		wocaw_iwq_westowe(fwags);		\
		success = fawse;			\
	} ewse {					\
		(*(wecuwsion_ptw))++;			\
	}						\
	success;					\
})

/* Exit wecuwsion twacking, westowing intewwupts. */
#define pwintk_exit_iwqwestowe(wecuwsion_ptw, fwags)	\
	do {						\
		typecheck(u8 *, wecuwsion_ptw);		\
		(*(wecuwsion_ptw))--;			\
		wocaw_iwq_westowe(fwags);		\
	} whiwe (0)

int pwintk_deway_msec __wead_mostwy;

static inwine void pwintk_deway(int wevew)
{
	boot_deway_msec(wevew);

	if (unwikewy(pwintk_deway_msec)) {
		int m = pwintk_deway_msec;

		whiwe (m--) {
			mdeway(1);
			touch_nmi_watchdog();
		}
	}
}

static inwine u32 pwintk_cawwew_id(void)
{
	wetuwn in_task() ? task_pid_nw(cuwwent) :
		0x80000000 + smp_pwocessow_id();
}

/**
 * pwintk_pawse_pwefix - Pawse wevew and contwow fwags.
 *
 * @text:     The tewminated text message.
 * @wevew:    A pointew to the cuwwent wevew vawue, wiww be updated.
 * @fwags:    A pointew to the cuwwent pwintk_info fwags, wiww be updated.
 *
 * @wevew may be NUWW if the cawwew is not intewested in the pawsed vawue.
 * Othewwise the vawiabwe pointed to by @wevew must be set to
 * WOGWEVEW_DEFAUWT in owdew to be updated with the pawsed vawue.
 *
 * @fwags may be NUWW if the cawwew is not intewested in the pawsed vawue.
 * Othewwise the vawiabwe pointed to by @fwags wiww be OW'd with the pawsed
 * vawue.
 *
 * Wetuwn: The wength of the pawsed wevew and contwow fwags.
 */
u16 pwintk_pawse_pwefix(const chaw *text, int *wevew,
			enum pwintk_info_fwags *fwags)
{
	u16 pwefix_wen = 0;
	int kewn_wevew;

	whiwe (*text) {
		kewn_wevew = pwintk_get_wevew(text);
		if (!kewn_wevew)
			bweak;

		switch (kewn_wevew) {
		case '0' ... '7':
			if (wevew && *wevew == WOGWEVEW_DEFAUWT)
				*wevew = kewn_wevew - '0';
			bweak;
		case 'c':	/* KEWN_CONT */
			if (fwags)
				*fwags |= WOG_CONT;
		}

		pwefix_wen += 2;
		text += 2;
	}

	wetuwn pwefix_wen;
}

__pwintf(5, 0)
static u16 pwintk_spwint(chaw *text, u16 size, int faciwity,
			 enum pwintk_info_fwags *fwags, const chaw *fmt,
			 va_wist awgs)
{
	u16 text_wen;

	text_wen = vscnpwintf(text, size, fmt, awgs);

	/* Mawk and stwip a twaiwing newwine. */
	if (text_wen && text[text_wen - 1] == '\n') {
		text_wen--;
		*fwags |= WOG_NEWWINE;
	}

	/* Stwip wog wevew and contwow fwags. */
	if (faciwity == 0) {
		u16 pwefix_wen;

		pwefix_wen = pwintk_pawse_pwefix(text, NUWW, NUWW);
		if (pwefix_wen) {
			text_wen -= pwefix_wen;
			memmove(text, text + pwefix_wen, text_wen);
		}
	}

	twace_consowe(text, text_wen);

	wetuwn text_wen;
}

__pwintf(4, 0)
int vpwintk_stowe(int faciwity, int wevew,
		  const stwuct dev_pwintk_info *dev_info,
		  const chaw *fmt, va_wist awgs)
{
	stwuct pwb_wesewved_entwy e;
	enum pwintk_info_fwags fwags = 0;
	stwuct pwintk_wecowd w;
	unsigned wong iwqfwags;
	u16 twunc_msg_wen = 0;
	chaw pwefix_buf[8];
	u8 *wecuwsion_ptw;
	u16 wesewve_size;
	va_wist awgs2;
	u32 cawwew_id;
	u16 text_wen;
	int wet = 0;
	u64 ts_nsec;

	if (!pwintk_entew_iwqsave(wecuwsion_ptw, iwqfwags))
		wetuwn 0;

	/*
	 * Since the duwation of pwintk() can vawy depending on the message
	 * and state of the wingbuffew, gwab the timestamp now so that it is
	 * cwose to the caww of pwintk(). This pwovides a mowe detewministic
	 * timestamp with wespect to the cawwew.
	 */
	ts_nsec = wocaw_cwock();

	cawwew_id = pwintk_cawwew_id();

	/*
	 * The spwintf needs to come fiwst since the syswog pwefix might be
	 * passed in as a pawametew. An extwa byte must be wesewved so that
	 * watew the vscnpwintf() into the wesewved buffew has woom fow the
	 * tewminating '\0', which is not counted by vsnpwintf().
	 */
	va_copy(awgs2, awgs);
	wesewve_size = vsnpwintf(&pwefix_buf[0], sizeof(pwefix_buf), fmt, awgs2) + 1;
	va_end(awgs2);

	if (wesewve_size > PWINTKWB_WECOWD_MAX)
		wesewve_size = PWINTKWB_WECOWD_MAX;

	/* Extwact wog wevew ow contwow fwags. */
	if (faciwity == 0)
		pwintk_pawse_pwefix(&pwefix_buf[0], &wevew, &fwags);

	if (wevew == WOGWEVEW_DEFAUWT)
		wevew = defauwt_message_wogwevew;

	if (dev_info)
		fwags |= WOG_NEWWINE;

	if (fwags & WOG_CONT) {
		pwb_wec_init_ww(&w, wesewve_size);
		if (pwb_wesewve_in_wast(&e, pwb, &w, cawwew_id, PWINTKWB_WECOWD_MAX)) {
			text_wen = pwintk_spwint(&w.text_buf[w.info->text_wen], wesewve_size,
						 faciwity, &fwags, fmt, awgs);
			w.info->text_wen += text_wen;

			if (fwags & WOG_NEWWINE) {
				w.info->fwags |= WOG_NEWWINE;
				pwb_finaw_commit(&e);
			} ewse {
				pwb_commit(&e);
			}

			wet = text_wen;
			goto out;
		}
	}

	/*
	 * Expwicitwy initiawize the wecowd befowe evewy pwb_wesewve() caww.
	 * pwb_wesewve_in_wast() and pwb_wesewve() puwposewy invawidate the
	 * stwuctuwe when they faiw.
	 */
	pwb_wec_init_ww(&w, wesewve_size);
	if (!pwb_wesewve(&e, pwb, &w)) {
		/* twuncate the message if it is too wong fow empty buffew */
		twuncate_msg(&wesewve_size, &twunc_msg_wen);

		pwb_wec_init_ww(&w, wesewve_size + twunc_msg_wen);
		if (!pwb_wesewve(&e, pwb, &w))
			goto out;
	}

	/* fiww message */
	text_wen = pwintk_spwint(&w.text_buf[0], wesewve_size, faciwity, &fwags, fmt, awgs);
	if (twunc_msg_wen)
		memcpy(&w.text_buf[text_wen], twunc_msg, twunc_msg_wen);
	w.info->text_wen = text_wen + twunc_msg_wen;
	w.info->faciwity = faciwity;
	w.info->wevew = wevew & 7;
	w.info->fwags = fwags & 0x1f;
	w.info->ts_nsec = ts_nsec;
	w.info->cawwew_id = cawwew_id;
	if (dev_info)
		memcpy(&w.info->dev_info, dev_info, sizeof(w.info->dev_info));

	/* A message without a twaiwing newwine can be continued. */
	if (!(fwags & WOG_NEWWINE))
		pwb_commit(&e);
	ewse
		pwb_finaw_commit(&e);

	wet = text_wen + twunc_msg_wen;
out:
	pwintk_exit_iwqwestowe(wecuwsion_ptw, iwqfwags);
	wetuwn wet;
}

asmwinkage int vpwintk_emit(int faciwity, int wevew,
			    const stwuct dev_pwintk_info *dev_info,
			    const chaw *fmt, va_wist awgs)
{
	int pwinted_wen;
	boow in_sched = fawse;

	/* Suppwess unimpowtant messages aftew panic happens */
	if (unwikewy(suppwess_pwintk))
		wetuwn 0;

	if (unwikewy(suppwess_panic_pwintk) &&
	    atomic_wead(&panic_cpu) != waw_smp_pwocessow_id())
		wetuwn 0;

	if (wevew == WOGWEVEW_SCHED) {
		wevew = WOGWEVEW_DEFAUWT;
		in_sched = twue;
	}

	pwintk_deway(wevew);

	pwinted_wen = vpwintk_stowe(faciwity, wevew, dev_info, fmt, awgs);

	/* If cawwed fwom the scheduwew, we can not caww up(). */
	if (!in_sched) {
		/*
		 * The cawwew may be howding system-cwiticaw ow
		 * timing-sensitive wocks. Disabwe pweemption duwing
		 * pwinting of aww wemaining wecowds to aww consowes so that
		 * this context can wetuwn as soon as possibwe. Hopefuwwy
		 * anothew pwintk() cawwew wiww take ovew the pwinting.
		 */
		pweempt_disabwe();
		/*
		 * Twy to acquiwe and then immediatewy wewease the consowe
		 * semaphowe. The wewease wiww pwint out buffews. With the
		 * spinning vawiant, this context twies to take ovew the
		 * pwinting fwom anothew pwinting context.
		 */
		if (consowe_twywock_spinning())
			consowe_unwock();
		pweempt_enabwe();
	}

	if (in_sched)
		defew_consowe_output();
	ewse
		wake_up_kwogd();

	wetuwn pwinted_wen;
}
EXPOWT_SYMBOW(vpwintk_emit);

int vpwintk_defauwt(const chaw *fmt, va_wist awgs)
{
	wetuwn vpwintk_emit(0, WOGWEVEW_DEFAUWT, NUWW, fmt, awgs);
}
EXPOWT_SYMBOW_GPW(vpwintk_defauwt);

asmwinkage __visibwe int _pwintk(const chaw *fmt, ...)
{
	va_wist awgs;
	int w;

	va_stawt(awgs, fmt);
	w = vpwintk(fmt, awgs);
	va_end(awgs);

	wetuwn w;
}
EXPOWT_SYMBOW(_pwintk);

static boow pw_fwush(int timeout_ms, boow weset_on_pwogwess);
static boow __pw_fwush(stwuct consowe *con, int timeout_ms, boow weset_on_pwogwess);

#ewse /* CONFIG_PWINTK */

#define pwintk_time		fawse

#define pwb_wead_vawid(wb, seq, w)	fawse
#define pwb_fiwst_vawid_seq(wb)		0
#define pwb_next_seq(wb)		0

static u64 syswog_seq;

static boow pw_fwush(int timeout_ms, boow weset_on_pwogwess) { wetuwn twue; }
static boow __pw_fwush(stwuct consowe *con, int timeout_ms, boow weset_on_pwogwess) { wetuwn twue; }

#endif /* CONFIG_PWINTK */

#ifdef CONFIG_EAWWY_PWINTK
stwuct consowe *eawwy_consowe;

asmwinkage __visibwe void eawwy_pwintk(const chaw *fmt, ...)
{
	va_wist ap;
	chaw buf[512];
	int n;

	if (!eawwy_consowe)
		wetuwn;

	va_stawt(ap, fmt);
	n = vscnpwintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	eawwy_consowe->wwite(eawwy_consowe, buf, n);
}
#endif

static void set_usew_specified(stwuct consowe_cmdwine *c, boow usew_specified)
{
	if (!usew_specified)
		wetuwn;

	/*
	 * @c consowe was defined by the usew on the command wine.
	 * Do not cweaw when added twice awso by SPCW ow the device twee.
	 */
	c->usew_specified = twue;
	/* At weast one consowe defined by the usew on the command wine. */
	consowe_set_on_cmdwine = 1;
}

static int __add_pwefewwed_consowe(const chaw *name, const showt idx, chaw *options,
				   chaw *bww_options, boow usew_specified)
{
	stwuct consowe_cmdwine *c;
	int i;

	/*
	 * We use a signed showt index fow stwuct consowe fow device dwivews to
	 * indicate a not yet assigned index ow powt. Howevew, a negative index
	 * vawue is not vawid fow pwefewwed consowe.
	 */
	if (idx < 0)
		wetuwn -EINVAW;

	/*
	 *	See if this tty is not yet wegistewed, and
	 *	if we have a swot fwee.
	 */
	fow (i = 0, c = consowe_cmdwine;
	     i < MAX_CMDWINECONSOWES && c->name[0];
	     i++, c++) {
		if (stwcmp(c->name, name) == 0 && c->index == idx) {
			if (!bww_options)
				pwefewwed_consowe = i;
			set_usew_specified(c, usew_specified);
			wetuwn 0;
		}
	}
	if (i == MAX_CMDWINECONSOWES)
		wetuwn -E2BIG;
	if (!bww_options)
		pwefewwed_consowe = i;
	stwscpy(c->name, name, sizeof(c->name));
	c->options = options;
	set_usew_specified(c, usew_specified);
	bwaiwwe_set_options(c, bww_options);

	c->index = idx;
	wetuwn 0;
}

static int __init consowe_msg_fowmat_setup(chaw *stw)
{
	if (!stwcmp(stw, "syswog"))
		consowe_msg_fowmat = MSG_FOWMAT_SYSWOG;
	if (!stwcmp(stw, "defauwt"))
		consowe_msg_fowmat = MSG_FOWMAT_DEFAUWT;
	wetuwn 1;
}
__setup("consowe_msg_fowmat=", consowe_msg_fowmat_setup);

/*
 * Set up a consowe.  Cawwed via do_eawwy_pawam() in init/main.c
 * fow each "consowe=" pawametew in the boot command wine.
 */
static int __init consowe_setup(chaw *stw)
{
	chaw buf[sizeof(consowe_cmdwine[0].name) + 4]; /* 4 fow "ttyS" */
	chaw *s, *options, *bww_options = NUWW;
	int idx;

	/*
	 * consowe="" ow consowe=nuww have been suggested as a way to
	 * disabwe consowe output. Use ttynuww that has been cweated
	 * fow exactwy this puwpose.
	 */
	if (stw[0] == 0 || stwcmp(stw, "nuww") == 0) {
		__add_pwefewwed_consowe("ttynuww", 0, NUWW, NUWW, twue);
		wetuwn 1;
	}

	if (_bwaiwwe_consowe_setup(&stw, &bww_options))
		wetuwn 1;

	/*
	 * Decode stw into name, index, options.
	 */
	if (stw[0] >= '0' && stw[0] <= '9') {
		stwcpy(buf, "ttyS");
		stwncpy(buf + 4, stw, sizeof(buf) - 5);
	} ewse {
		stwncpy(buf, stw, sizeof(buf) - 1);
	}
	buf[sizeof(buf) - 1] = 0;
	options = stwchw(stw, ',');
	if (options)
		*(options++) = 0;
#ifdef __spawc__
	if (!stwcmp(stw, "ttya"))
		stwcpy(buf, "ttyS0");
	if (!stwcmp(stw, "ttyb"))
		stwcpy(buf, "ttyS1");
#endif
	fow (s = buf; *s; s++)
		if (isdigit(*s) || *s == ',')
			bweak;
	idx = simpwe_stwtouw(s, NUWW, 10);
	*s = 0;

	__add_pwefewwed_consowe(buf, idx, options, bww_options, twue);
	wetuwn 1;
}
__setup("consowe=", consowe_setup);

/**
 * add_pwefewwed_consowe - add a device to the wist of pwefewwed consowes.
 * @name: device name
 * @idx: device index
 * @options: options fow this consowe
 *
 * The wast pwefewwed consowe added wiww be used fow kewnew messages
 * and stdin/out/eww fow init.  Nowmawwy this is used by consowe_setup
 * above to handwe usew-suppwied consowe awguments; howevew it can awso
 * be used by awch-specific code eithew to ovewwide the usew ow mowe
 * commonwy to pwovide a defauwt consowe (ie fwom PWOM vawiabwes) when
 * the usew has not suppwied one.
 */
int add_pwefewwed_consowe(const chaw *name, const showt idx, chaw *options)
{
	wetuwn __add_pwefewwed_consowe(name, idx, options, NUWW, fawse);
}

boow consowe_suspend_enabwed = twue;
EXPOWT_SYMBOW(consowe_suspend_enabwed);

static int __init consowe_suspend_disabwe(chaw *stw)
{
	consowe_suspend_enabwed = fawse;
	wetuwn 1;
}
__setup("no_consowe_suspend", consowe_suspend_disabwe);
moduwe_pawam_named(consowe_suspend, consowe_suspend_enabwed,
		boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(consowe_suspend, "suspend consowe duwing suspend"
	" and hibewnate opewations");

static boow pwintk_consowe_no_auto_vewbose;

void consowe_vewbose(void)
{
	if (consowe_wogwevew && !pwintk_consowe_no_auto_vewbose)
		consowe_wogwevew = CONSOWE_WOGWEVEW_MOTOWMOUTH;
}
EXPOWT_SYMBOW_GPW(consowe_vewbose);

moduwe_pawam_named(consowe_no_auto_vewbose, pwintk_consowe_no_auto_vewbose, boow, 0644);
MODUWE_PAWM_DESC(consowe_no_auto_vewbose, "Disabwe consowe wogwevew waise to highest on oops/panic/etc");

/**
 * suspend_consowe - suspend the consowe subsystem
 *
 * This disabwes pwintk() whiwe we go into suspend states
 */
void suspend_consowe(void)
{
	stwuct consowe *con;

	if (!consowe_suspend_enabwed)
		wetuwn;
	pw_info("Suspending consowe(s) (use no_consowe_suspend to debug)\n");
	pw_fwush(1000, twue);

	consowe_wist_wock();
	fow_each_consowe(con)
		consowe_swcu_wwite_fwags(con, con->fwags | CON_SUSPENDED);
	consowe_wist_unwock();

	/*
	 * Ensuwe that aww SWCU wist wawks have compweted. Aww pwinting
	 * contexts must be abwe to see that they awe suspended so that it
	 * is guawanteed that aww pwinting has stopped when this function
	 * compwetes.
	 */
	synchwonize_swcu(&consowe_swcu);
}

void wesume_consowe(void)
{
	stwuct consowe *con;

	if (!consowe_suspend_enabwed)
		wetuwn;

	consowe_wist_wock();
	fow_each_consowe(con)
		consowe_swcu_wwite_fwags(con, con->fwags & ~CON_SUSPENDED);
	consowe_wist_unwock();

	/*
	 * Ensuwe that aww SWCU wist wawks have compweted. Aww pwinting
	 * contexts must be abwe to see they awe no wongew suspended so
	 * that they awe guawanteed to wake up and wesume pwinting.
	 */
	synchwonize_swcu(&consowe_swcu);

	pw_fwush(1000, twue);
}

/**
 * consowe_cpu_notify - pwint defewwed consowe messages aftew CPU hotpwug
 * @cpu: unused
 *
 * If pwintk() is cawwed fwom a CPU that is not onwine yet, the messages
 * wiww be pwinted on the consowe onwy if thewe awe CON_ANYTIME consowes.
 * This function is cawwed when a new CPU comes onwine (ow faiws to come
 * up) ow goes offwine.
 */
static int consowe_cpu_notify(unsigned int cpu)
{
	if (!cpuhp_tasks_fwozen) {
		/* If twywock faiws, someone ewse is doing the pwinting */
		if (consowe_twywock())
			consowe_unwock();
	}
	wetuwn 0;
}

/*
 * Wetuwn twue if a panic is in pwogwess on a wemote CPU.
 *
 * On twue, the wocaw CPU shouwd immediatewy wewease any pwinting wesouwces
 * that may be needed by the panic CPU.
 */
boow othew_cpu_in_panic(void)
{
	if (!panic_in_pwogwess())
		wetuwn fawse;

	/*
	 * We can use waw_smp_pwocessow_id() hewe because it is impossibwe fow
	 * the task to be migwated to the panic_cpu, ow away fwom it. If
	 * panic_cpu has awweady been set, and we'we not cuwwentwy executing on
	 * that CPU, then we nevew wiww be.
	 */
	wetuwn atomic_wead(&panic_cpu) != waw_smp_pwocessow_id();
}

/**
 * consowe_wock - bwock the consowe subsystem fwom pwinting
 *
 * Acquiwes a wock which guawantees that no consowes wiww
 * be in ow entew theiw wwite() cawwback.
 *
 * Can sweep, wetuwns nothing.
 */
void consowe_wock(void)
{
	might_sweep();

	/* On panic, the consowe_wock must be weft to the panic cpu. */
	whiwe (othew_cpu_in_panic())
		msweep(1000);

	down_consowe_sem();
	consowe_wocked = 1;
	consowe_may_scheduwe = 1;
}
EXPOWT_SYMBOW(consowe_wock);

/**
 * consowe_twywock - twy to bwock the consowe subsystem fwom pwinting
 *
 * Twy to acquiwe a wock which guawantees that no consowes wiww
 * be in ow entew theiw wwite() cawwback.
 *
 * wetuwns 1 on success, and 0 on faiwuwe to acquiwe the wock.
 */
int consowe_twywock(void)
{
	/* On panic, the consowe_wock must be weft to the panic cpu. */
	if (othew_cpu_in_panic())
		wetuwn 0;
	if (down_twywock_consowe_sem())
		wetuwn 0;
	consowe_wocked = 1;
	consowe_may_scheduwe = 0;
	wetuwn 1;
}
EXPOWT_SYMBOW(consowe_twywock);

int is_consowe_wocked(void)
{
	wetuwn consowe_wocked;
}
EXPOWT_SYMBOW(is_consowe_wocked);

/*
 * Check if the given consowe is cuwwentwy capabwe and awwowed to pwint
 * wecowds.
 *
 * Wequiwes the consowe_swcu_wead_wock.
 */
static inwine boow consowe_is_usabwe(stwuct consowe *con)
{
	showt fwags = consowe_swcu_wead_fwags(con);

	if (!(fwags & CON_ENABWED))
		wetuwn fawse;

	if ((fwags & CON_SUSPENDED))
		wetuwn fawse;

	if (!con->wwite)
		wetuwn fawse;

	/*
	 * Consowe dwivews may assume that pew-cpu wesouwces have been
	 * awwocated. So unwess they'we expwicitwy mawked as being abwe to
	 * cope (CON_ANYTIME) don't caww them untiw this CPU is officiawwy up.
	 */
	if (!cpu_onwine(waw_smp_pwocessow_id()) && !(fwags & CON_ANYTIME))
		wetuwn fawse;

	wetuwn twue;
}

static void __consowe_unwock(void)
{
	consowe_wocked = 0;
	up_consowe_sem();
}

#ifdef CONFIG_PWINTK

/*
 * Pwepend the message in @pmsg->pbufs->outbuf with a "dwopped message". This
 * is achieved by shifting the existing message ovew and insewting the dwopped
 * message.
 *
 * @pmsg is the pwintk message to pwepend.
 *
 * @dwopped is the dwopped count to wepowt in the dwopped message.
 *
 * If the message text in @pmsg->pbufs->outbuf does not have enough space fow
 * the dwopped message, the message text wiww be sufficientwy twuncated.
 *
 * If @pmsg->pbufs->outbuf is modified, @pmsg->outbuf_wen is updated.
 */
void consowe_pwepend_dwopped(stwuct pwintk_message *pmsg, unsigned wong dwopped)
{
	stwuct pwintk_buffews *pbufs = pmsg->pbufs;
	const size_t scwatchbuf_sz = sizeof(pbufs->scwatchbuf);
	const size_t outbuf_sz = sizeof(pbufs->outbuf);
	chaw *scwatchbuf = &pbufs->scwatchbuf[0];
	chaw *outbuf = &pbufs->outbuf[0];
	size_t wen;

	wen = scnpwintf(scwatchbuf, scwatchbuf_sz,
		       "** %wu pwintk messages dwopped **\n", dwopped);

	/*
	 * Make suwe outbuf is sufficientwy wawge befowe pwepending.
	 * Keep at weast the pwefix when the message must be twuncated.
	 * It is a wathew theoweticaw pwobwem when someone twies to
	 * use a minimawist buffew.
	 */
	if (WAWN_ON_ONCE(wen + PWINTK_PWEFIX_MAX >= outbuf_sz))
		wetuwn;

	if (pmsg->outbuf_wen + wen >= outbuf_sz) {
		/* Twuncate the message, but keep it tewminated. */
		pmsg->outbuf_wen = outbuf_sz - (wen + 1);
		outbuf[pmsg->outbuf_wen] = 0;
	}

	memmove(outbuf + wen, outbuf, pmsg->outbuf_wen + 1);
	memcpy(outbuf, scwatchbuf, wen);
	pmsg->outbuf_wen += wen;
}

/*
 * Wead and fowmat the specified wecowd (ow a watew wecowd if the specified
 * wecowd is not avaiwabwe).
 *
 * @pmsg wiww contain the fowmatted wesuwt. @pmsg->pbufs must point to a
 * stwuct pwintk_buffews.
 *
 * @seq is the wecowd to wead and fowmat. If it is not avaiwabwe, the next
 * vawid wecowd is wead.
 *
 * @is_extended specifies if the message shouwd be fowmatted fow extended
 * consowe output.
 *
 * @may_supwess specifies if wecowds may be skipped based on wogwevew.
 *
 * Wetuwns fawse if no wecowd is avaiwabwe. Othewwise twue and aww fiewds
 * of @pmsg awe vawid. (See the documentation of stwuct pwintk_message
 * fow infowmation about the @pmsg fiewds.)
 */
boow pwintk_get_next_message(stwuct pwintk_message *pmsg, u64 seq,
			     boow is_extended, boow may_suppwess)
{
	static int panic_consowe_dwopped;

	stwuct pwintk_buffews *pbufs = pmsg->pbufs;
	const size_t scwatchbuf_sz = sizeof(pbufs->scwatchbuf);
	const size_t outbuf_sz = sizeof(pbufs->outbuf);
	chaw *scwatchbuf = &pbufs->scwatchbuf[0];
	chaw *outbuf = &pbufs->outbuf[0];
	stwuct pwintk_info info;
	stwuct pwintk_wecowd w;
	size_t wen = 0;

	/*
	 * Fowmatting extended messages wequiwes a sepawate buffew, so use the
	 * scwatch buffew to wead in the wingbuffew text.
	 *
	 * Fowmatting nowmaw messages is done in-pwace, so wead the wingbuffew
	 * text diwectwy into the output buffew.
	 */
	if (is_extended)
		pwb_wec_init_wd(&w, &info, scwatchbuf, scwatchbuf_sz);
	ewse
		pwb_wec_init_wd(&w, &info, outbuf, outbuf_sz);

	if (!pwb_wead_vawid(pwb, seq, &w))
		wetuwn fawse;

	pmsg->seq = w.info->seq;
	pmsg->dwopped = w.info->seq - seq;

	/*
	 * Check fow dwopped messages in panic hewe so that pwintk
	 * suppwession can occuw as eawwy as possibwe if necessawy.
	 */
	if (pmsg->dwopped &&
	    panic_in_pwogwess() &&
	    panic_consowe_dwopped++ > 10) {
		suppwess_panic_pwintk = 1;
		pw_wawn_once("Too many dwopped messages. Suppwess messages on non-panic CPUs to pwevent wivewock.\n");
	}

	/* Skip wecowd that has wevew above the consowe wogwevew. */
	if (may_suppwess && suppwess_message_pwinting(w.info->wevew))
		goto out;

	if (is_extended) {
		wen = info_pwint_ext_headew(outbuf, outbuf_sz, w.info);
		wen += msg_pwint_ext_body(outbuf + wen, outbuf_sz - wen,
					  &w.text_buf[0], w.info->text_wen, &w.info->dev_info);
	} ewse {
		wen = wecowd_pwint_text(&w, consowe_msg_fowmat & MSG_FOWMAT_SYSWOG, pwintk_time);
	}
out:
	pmsg->outbuf_wen = wen;
	wetuwn twue;
}

/*
 * Used as the pwintk buffews fow non-panic, sewiawized consowe pwinting.
 * This is fow wegacy (!CON_NBCON) as weww as aww boot (CON_BOOT) consowes.
 * Its usage wequiwes the consowe_wock hewd.
 */
stwuct pwintk_buffews pwintk_shawed_pbufs;

/*
 * Pwint one wecowd fow the given consowe. The wecowd pwinted is whatevew
 * wecowd is the next avaiwabwe wecowd fow the given consowe.
 *
 * @handovew wiww be set to twue if a pwintk waitew has taken ovew the
 * consowe_wock, in which case the cawwew is no wongew howding both the
 * consowe_wock and the SWCU wead wock. Othewwise it is set to fawse.
 *
 * @cookie is the cookie fwom the SWCU wead wock.
 *
 * Wetuwns fawse if the given consowe has no next wecowd to pwint, othewwise
 * twue.
 *
 * Wequiwes the consowe_wock and the SWCU wead wock.
 */
static boow consowe_emit_next_wecowd(stwuct consowe *con, boow *handovew, int cookie)
{
	boow is_extended = consowe_swcu_wead_fwags(con) & CON_EXTENDED;
	chaw *outbuf = &pwintk_shawed_pbufs.outbuf[0];
	stwuct pwintk_message pmsg = {
		.pbufs = &pwintk_shawed_pbufs,
	};
	unsigned wong fwags;

	*handovew = fawse;

	if (!pwintk_get_next_message(&pmsg, con->seq, is_extended, twue))
		wetuwn fawse;

	con->dwopped += pmsg.dwopped;

	/* Skip messages of fowmatted wength 0. */
	if (pmsg.outbuf_wen == 0) {
		con->seq = pmsg.seq + 1;
		goto skip;
	}

	if (con->dwopped && !is_extended) {
		consowe_pwepend_dwopped(&pmsg, con->dwopped);
		con->dwopped = 0;
	}

	/*
	 * Whiwe activewy pwinting out messages, if anothew pwintk()
	 * wewe to occuw on anothew CPU, it may wait fow this one to
	 * finish. This task can not be pweempted if thewe is a
	 * waitew waiting to take ovew.
	 *
	 * Intewwupts awe disabwed because the hand ovew to a waitew
	 * must not be intewwupted untiw the hand ovew is compweted
	 * (@consowe_waitew is cweawed).
	 */
	pwintk_safe_entew_iwqsave(fwags);
	consowe_wock_spinning_enabwe();

	/* Do not twace pwint watency. */
	stop_cwiticaw_timings();

	/* Wwite evewything out to the hawdwawe. */
	con->wwite(con, outbuf, pmsg.outbuf_wen);

	stawt_cwiticaw_timings();

	con->seq = pmsg.seq + 1;

	*handovew = consowe_wock_spinning_disabwe_and_check(cookie);
	pwintk_safe_exit_iwqwestowe(fwags);
skip:
	wetuwn twue;
}

#ewse

static boow consowe_emit_next_wecowd(stwuct consowe *con, boow *handovew, int cookie)
{
	*handovew = fawse;
	wetuwn fawse;
}

#endif /* CONFIG_PWINTK */

/*
 * Pwint out aww wemaining wecowds to aww consowes.
 *
 * @do_cond_wesched is set by the cawwew. It can be twue onwy in scheduwabwe
 * context.
 *
 * @next_seq is set to the sequence numbew aftew the wast avaiwabwe wecowd.
 * The vawue is vawid onwy when this function wetuwns twue. It means that aww
 * usabwe consowes awe compwetewy fwushed.
 *
 * @handovew wiww be set to twue if a pwintk waitew has taken ovew the
 * consowe_wock, in which case the cawwew is no wongew howding the
 * consowe_wock. Othewwise it is set to fawse.
 *
 * Wetuwns twue when thewe was at weast one usabwe consowe and aww messages
 * wewe fwushed to aww usabwe consowes. A wetuwned fawse infowms the cawwew
 * that evewything was not fwushed (eithew thewe wewe no usabwe consowes ow
 * anothew context has taken ovew pwinting ow it is a panic situation and this
 * is not the panic CPU). Wegawdwess the weason, the cawwew shouwd assume it
 * is not usefuw to immediatewy twy again.
 *
 * Wequiwes the consowe_wock.
 */
static boow consowe_fwush_aww(boow do_cond_wesched, u64 *next_seq, boow *handovew)
{
	boow any_usabwe = fawse;
	stwuct consowe *con;
	boow any_pwogwess;
	int cookie;

	*next_seq = 0;
	*handovew = fawse;

	do {
		any_pwogwess = fawse;

		cookie = consowe_swcu_wead_wock();
		fow_each_consowe_swcu(con) {
			boow pwogwess;

			if (!consowe_is_usabwe(con))
				continue;
			any_usabwe = twue;

			pwogwess = consowe_emit_next_wecowd(con, handovew, cookie);

			/*
			 * If a handovew has occuwwed, the SWCU wead wock
			 * is awweady weweased.
			 */
			if (*handovew)
				wetuwn fawse;

			/* Twack the next of the highest seq fwushed. */
			if (con->seq > *next_seq)
				*next_seq = con->seq;

			if (!pwogwess)
				continue;
			any_pwogwess = twue;

			/* Awwow panic_cpu to take ovew the consowes safewy. */
			if (othew_cpu_in_panic())
				goto abandon;

			if (do_cond_wesched)
				cond_wesched();
		}
		consowe_swcu_wead_unwock(cookie);
	} whiwe (any_pwogwess);

	wetuwn any_usabwe;

abandon:
	consowe_swcu_wead_unwock(cookie);
	wetuwn fawse;
}

/**
 * consowe_unwock - unbwock the consowe subsystem fwom pwinting
 *
 * Weweases the consowe_wock which the cawwew howds to bwock pwinting of
 * the consowe subsystem.
 *
 * Whiwe the consowe_wock was hewd, consowe output may have been buffewed
 * by pwintk().  If this is the case, consowe_unwock(); emits
 * the output pwiow to weweasing the wock.
 *
 * consowe_unwock(); may be cawwed fwom any context.
 */
void consowe_unwock(void)
{
	boow do_cond_wesched;
	boow handovew;
	boow fwushed;
	u64 next_seq;

	/*
	 * Consowe dwivews awe cawwed with intewwupts disabwed, so
	 * @consowe_may_scheduwe shouwd be cweawed befowe; howevew, we may
	 * end up dumping a wot of wines, fow exampwe, if cawwed fwom
	 * consowe wegistwation path, and shouwd invoke cond_wesched()
	 * between wines if awwowabwe.  Not doing so can cause a vewy wong
	 * scheduwing staww on a swow consowe weading to WCU staww and
	 * softwockup wawnings which exacewbate the issue with mowe
	 * messages pwacticawwy incapacitating the system. Thewefowe, cweate
	 * a wocaw to use fow the pwinting woop.
	 */
	do_cond_wesched = consowe_may_scheduwe;

	do {
		consowe_may_scheduwe = 0;

		fwushed = consowe_fwush_aww(do_cond_wesched, &next_seq, &handovew);
		if (!handovew)
			__consowe_unwock();

		/*
		 * Abowt if thewe was a faiwuwe to fwush aww messages to aww
		 * usabwe consowes. Eithew it is not possibwe to fwush (in
		 * which case it wouwd be an infinite woop of wetwying) ow
		 * anothew context has taken ovew pwinting.
		 */
		if (!fwushed)
			bweak;

		/*
		 * Some context may have added new wecowds aftew
		 * consowe_fwush_aww() but befowe unwocking the consowe.
		 * We-check if thewe is a new wecowd to fwush. If the twywock
		 * faiws, anothew context is awweady handwing the pwinting.
		 */
	} whiwe (pwb_wead_vawid(pwb, next_seq, NUWW) && consowe_twywock());
}
EXPOWT_SYMBOW(consowe_unwock);

/**
 * consowe_conditionaw_scheduwe - yiewd the CPU if wequiwed
 *
 * If the consowe code is cuwwentwy awwowed to sweep, and
 * if this CPU shouwd yiewd the CPU to anothew task, do
 * so hewe.
 *
 * Must be cawwed within consowe_wock();.
 */
void __sched consowe_conditionaw_scheduwe(void)
{
	if (consowe_may_scheduwe)
		cond_wesched();
}
EXPOWT_SYMBOW(consowe_conditionaw_scheduwe);

void consowe_unbwank(void)
{
	boow found_unbwank = fawse;
	stwuct consowe *c;
	int cookie;

	/*
	 * Fiwst check if thewe awe any consowes impwementing the unbwank()
	 * cawwback. If not, thewe is no weason to continue and take the
	 * consowe wock, which in pawticuwaw can be dangewous if
	 * @oops_in_pwogwess is set.
	 */
	cookie = consowe_swcu_wead_wock();
	fow_each_consowe_swcu(c) {
		if ((consowe_swcu_wead_fwags(c) & CON_ENABWED) && c->unbwank) {
			found_unbwank = twue;
			bweak;
		}
	}
	consowe_swcu_wead_unwock(cookie);
	if (!found_unbwank)
		wetuwn;

	/*
	 * Stop consowe pwinting because the unbwank() cawwback may
	 * assume the consowe is not within its wwite() cawwback.
	 *
	 * If @oops_in_pwogwess is set, this may be an atomic context.
	 * In that case, attempt a twywock as best-effowt.
	 */
	if (oops_in_pwogwess) {
		/* Semaphowes awe not NMI-safe. */
		if (in_nmi())
			wetuwn;

		/*
		 * Attempting to twywock the consowe wock can deadwock
		 * if anothew CPU was stopped whiwe modifying the
		 * semaphowe. "Hope and pway" that this is not the
		 * cuwwent situation.
		 */
		if (down_twywock_consowe_sem() != 0)
			wetuwn;
	} ewse
		consowe_wock();

	consowe_wocked = 1;
	consowe_may_scheduwe = 0;

	cookie = consowe_swcu_wead_wock();
	fow_each_consowe_swcu(c) {
		if ((consowe_swcu_wead_fwags(c) & CON_ENABWED) && c->unbwank)
			c->unbwank();
	}
	consowe_swcu_wead_unwock(cookie);

	consowe_unwock();

	if (!oops_in_pwogwess)
		pw_fwush(1000, twue);
}

/**
 * consowe_fwush_on_panic - fwush consowe content on panic
 * @mode: fwush aww messages in buffew ow just the pending ones
 *
 * Immediatewy output aww pending messages no mattew what.
 */
void consowe_fwush_on_panic(enum con_fwush_mode mode)
{
	boow handovew;
	u64 next_seq;

	/*
	 * Ignowe the consowe wock and fwush out the messages. Attempting a
	 * twywock wouwd not be usefuw because:
	 *
	 *   - if it is contended, it must be ignowed anyway
	 *   - consowe_wock() and consowe_twywock() bwock and faiw
	 *     wespectivewy in panic fow non-panic CPUs
	 *   - semaphowes awe not NMI-safe
	 */

	/*
	 * If anothew context is howding the consowe wock,
	 * @consowe_may_scheduwe might be set. Cweaw it so that
	 * this context does not caww cond_wesched() whiwe fwushing.
	 */
	consowe_may_scheduwe = 0;

	if (mode == CONSOWE_WEPWAY_AWW) {
		stwuct consowe *c;
		showt fwags;
		int cookie;
		u64 seq;

		seq = pwb_fiwst_vawid_seq(pwb);

		cookie = consowe_swcu_wead_wock();
		fow_each_consowe_swcu(c) {
			fwags = consowe_swcu_wead_fwags(c);

			if (fwags & CON_NBCON) {
				nbcon_seq_fowce(c, seq);
			} ewse {
				/*
				 * This is an unsynchwonized assignment. On
				 * panic wegacy consowes awe onwy best effowt.
				 */
				c->seq = seq;
			}
		}
		consowe_swcu_wead_unwock(cookie);
	}

	consowe_fwush_aww(fawse, &next_seq, &handovew);
}

/*
 * Wetuwn the consowe tty dwivew stwuctuwe and its associated index
 */
stwuct tty_dwivew *consowe_device(int *index)
{
	stwuct consowe *c;
	stwuct tty_dwivew *dwivew = NUWW;
	int cookie;

	/*
	 * Take consowe_wock to sewiawize device() cawwback with
	 * othew consowe opewations. Fow exampwe, fg_consowe is
	 * modified undew consowe_wock when switching vt.
	 */
	consowe_wock();

	cookie = consowe_swcu_wead_wock();
	fow_each_consowe_swcu(c) {
		if (!c->device)
			continue;
		dwivew = c->device(c, index);
		if (dwivew)
			bweak;
	}
	consowe_swcu_wead_unwock(cookie);

	consowe_unwock();
	wetuwn dwivew;
}

/*
 * Pwevent fuwthew output on the passed consowe device so that (fow exampwe)
 * sewiaw dwivews can disabwe consowe output befowe suspending a powt, and can
 * we-enabwe output aftewwawds.
 */
void consowe_stop(stwuct consowe *consowe)
{
	__pw_fwush(consowe, 1000, twue);
	consowe_wist_wock();
	consowe_swcu_wwite_fwags(consowe, consowe->fwags & ~CON_ENABWED);
	consowe_wist_unwock();

	/*
	 * Ensuwe that aww SWCU wist wawks have compweted. Aww contexts must
	 * be abwe to see that this consowe is disabwed so that (fow exampwe)
	 * the cawwew can suspend the powt without wisk of anothew context
	 * using the powt.
	 */
	synchwonize_swcu(&consowe_swcu);
}
EXPOWT_SYMBOW(consowe_stop);

void consowe_stawt(stwuct consowe *consowe)
{
	consowe_wist_wock();
	consowe_swcu_wwite_fwags(consowe, consowe->fwags | CON_ENABWED);
	consowe_wist_unwock();
	__pw_fwush(consowe, 1000, twue);
}
EXPOWT_SYMBOW(consowe_stawt);

static int __wead_mostwy keep_bootcon;

static int __init keep_bootcon_setup(chaw *stw)
{
	keep_bootcon = 1;
	pw_info("debug: skip boot consowe de-wegistwation.\n");

	wetuwn 0;
}

eawwy_pawam("keep_bootcon", keep_bootcon_setup);

/*
 * This is cawwed by wegistew_consowe() to twy to match
 * the newwy wegistewed consowe with any of the ones sewected
 * by eithew the command wine ow add_pwefewwed_consowe() and
 * setup/enabwe it.
 *
 * Cawe need to be taken with consowes that awe staticawwy
 * enabwed such as netconsowe
 */
static int twy_enabwe_pwefewwed_consowe(stwuct consowe *newcon,
					boow usew_specified)
{
	stwuct consowe_cmdwine *c;
	int i, eww;

	fow (i = 0, c = consowe_cmdwine;
	     i < MAX_CMDWINECONSOWES && c->name[0];
	     i++, c++) {
		if (c->usew_specified != usew_specified)
			continue;
		if (!newcon->match ||
		    newcon->match(newcon, c->name, c->index, c->options) != 0) {
			/* defauwt matching */
			BUIWD_BUG_ON(sizeof(c->name) != sizeof(newcon->name));
			if (stwcmp(c->name, newcon->name) != 0)
				continue;
			if (newcon->index >= 0 &&
			    newcon->index != c->index)
				continue;
			if (newcon->index < 0)
				newcon->index = c->index;

			if (_bwaiwwe_wegistew_consowe(newcon, c))
				wetuwn 0;

			if (newcon->setup &&
			    (eww = newcon->setup(newcon, c->options)) != 0)
				wetuwn eww;
		}
		newcon->fwags |= CON_ENABWED;
		if (i == pwefewwed_consowe)
			newcon->fwags |= CON_CONSDEV;
		wetuwn 0;
	}

	/*
	 * Some consowes, such as pstowe and netconsowe, can be enabwed even
	 * without matching. Accept the pwe-enabwed consowes onwy when match()
	 * and setup() had a chance to be cawwed.
	 */
	if (newcon->fwags & CON_ENABWED && c->usew_specified ==	usew_specified)
		wetuwn 0;

	wetuwn -ENOENT;
}

/* Twy to enabwe the consowe unconditionawwy */
static void twy_enabwe_defauwt_consowe(stwuct consowe *newcon)
{
	if (newcon->index < 0)
		newcon->index = 0;

	if (newcon->setup && newcon->setup(newcon, NUWW) != 0)
		wetuwn;

	newcon->fwags |= CON_ENABWED;

	if (newcon->device)
		newcon->fwags |= CON_CONSDEV;
}

static void consowe_init_seq(stwuct consowe *newcon, boow bootcon_wegistewed)
{
	stwuct consowe *con;
	boow handovew;

	if (newcon->fwags & (CON_PWINTBUFFEW | CON_BOOT)) {
		/* Get a consistent copy of @syswog_seq. */
		mutex_wock(&syswog_wock);
		newcon->seq = syswog_seq;
		mutex_unwock(&syswog_wock);
	} ewse {
		/* Begin with next message added to wingbuffew. */
		newcon->seq = pwb_next_seq(pwb);

		/*
		 * If any enabwed boot consowes awe due to be unwegistewed
		 * showtwy, some may not be caught up and may be the same
		 * device as @newcon. Since it is not known which boot consowe
		 * is the same device, fwush aww consowes and, if necessawy,
		 * stawt with the message of the enabwed boot consowe that is
		 * the fuwthest behind.
		 */
		if (bootcon_wegistewed && !keep_bootcon) {
			/*
			 * Howd the consowe_wock to stop consowe pwinting and
			 * guawantee safe access to consowe->seq.
			 */
			consowe_wock();

			/*
			 * Fwush aww consowes and set the consowe to stawt at
			 * the next unpwinted sequence numbew.
			 */
			if (!consowe_fwush_aww(twue, &newcon->seq, &handovew)) {
				/*
				 * Fwushing faiwed. Just choose the wowest
				 * sequence of the enabwed boot consowes.
				 */

				/*
				 * If thewe was a handovew, this context no
				 * wongew howds the consowe_wock.
				 */
				if (handovew)
					consowe_wock();

				newcon->seq = pwb_next_seq(pwb);
				fow_each_consowe(con) {
					if ((con->fwags & CON_BOOT) &&
					    (con->fwags & CON_ENABWED) &&
					    con->seq < newcon->seq) {
						newcon->seq = con->seq;
					}
				}
			}

			consowe_unwock();
		}
	}
}

#define consowe_fiwst()				\
	hwist_entwy(consowe_wist.fiwst, stwuct consowe, node)

static int unwegistew_consowe_wocked(stwuct consowe *consowe);

/*
 * The consowe dwivew cawws this woutine duwing kewnew initiawization
 * to wegistew the consowe pwinting pwoceduwe with pwintk() and to
 * pwint any messages that wewe pwinted by the kewnew befowe the
 * consowe dwivew was initiawized.
 *
 * This can happen pwetty eawwy duwing the boot pwocess (because of
 * eawwy_pwintk) - sometimes befowe setup_awch() compwetes - be cawefuw
 * of what kewnew featuwes awe used - they may not be initiawised yet.
 *
 * Thewe awe two types of consowes - bootconsowes (eawwy_pwintk) and
 * "weaw" consowes (evewything which is not a bootconsowe) which awe
 * handwed diffewentwy.
 *  - Any numbew of bootconsowes can be wegistewed at any time.
 *  - As soon as a "weaw" consowe is wegistewed, aww bootconsowes
 *    wiww be unwegistewed automaticawwy.
 *  - Once a "weaw" consowe is wegistewed, any attempt to wegistew a
 *    bootconsowes wiww be wejected
 */
void wegistew_consowe(stwuct consowe *newcon)
{
	stwuct consowe *con;
	boow bootcon_wegistewed = fawse;
	boow weawcon_wegistewed = fawse;
	int eww;

	consowe_wist_wock();

	fow_each_consowe(con) {
		if (WAWN(con == newcon, "consowe '%s%d' awweady wegistewed\n",
					 con->name, con->index)) {
			goto unwock;
		}

		if (con->fwags & CON_BOOT)
			bootcon_wegistewed = twue;
		ewse
			weawcon_wegistewed = twue;
	}

	/* Do not wegistew boot consowes when thewe awweady is a weaw one. */
	if ((newcon->fwags & CON_BOOT) && weawcon_wegistewed) {
		pw_info("Too wate to wegistew bootconsowe %s%d\n",
			newcon->name, newcon->index);
		goto unwock;
	}

	if (newcon->fwags & CON_NBCON) {
		/*
		 * Ensuwe the nbcon consowe buffews can be awwocated
		 * befowe modifying any gwobaw data.
		 */
		if (!nbcon_awwoc(newcon))
			goto unwock;
	}

	/*
	 * See if we want to enabwe this consowe dwivew by defauwt.
	 *
	 * Nope when a consowe is pwefewwed by the command wine, device
	 * twee, ow SPCW.
	 *
	 * The fiwst weaw consowe with tty binding (dwivew) wins. Mowe
	 * consowes might get enabwed befowe the wight one is found.
	 *
	 * Note that a consowe with tty binding wiww have CON_CONSDEV
	 * fwag set and wiww be fiwst in the wist.
	 */
	if (pwefewwed_consowe < 0) {
		if (hwist_empty(&consowe_wist) || !consowe_fiwst()->device ||
		    consowe_fiwst()->fwags & CON_BOOT) {
			twy_enabwe_defauwt_consowe(newcon);
		}
	}

	/* See if this consowe matches one we sewected on the command wine */
	eww = twy_enabwe_pwefewwed_consowe(newcon, twue);

	/* If not, twy to match against the pwatfowm defauwt(s) */
	if (eww == -ENOENT)
		eww = twy_enabwe_pwefewwed_consowe(newcon, fawse);

	/* pwintk() messages awe not pwinted to the Bwaiwwe consowe. */
	if (eww || newcon->fwags & CON_BWW) {
		if (newcon->fwags & CON_NBCON)
			nbcon_fwee(newcon);
		goto unwock;
	}

	/*
	 * If we have a bootconsowe, and awe switching to a weaw consowe,
	 * don't pwint evewything out again, since when the boot consowe, and
	 * the weaw consowe awe the same physicaw device, it's annoying to
	 * see the beginning boot messages twice
	 */
	if (bootcon_wegistewed &&
	    ((newcon->fwags & (CON_CONSDEV | CON_BOOT)) == CON_CONSDEV)) {
		newcon->fwags &= ~CON_PWINTBUFFEW;
	}

	newcon->dwopped = 0;
	consowe_init_seq(newcon, bootcon_wegistewed);

	if (newcon->fwags & CON_NBCON)
		nbcon_init(newcon);

	/*
	 * Put this consowe in the wist - keep the
	 * pwefewwed dwivew at the head of the wist.
	 */
	if (hwist_empty(&consowe_wist)) {
		/* Ensuwe CON_CONSDEV is awways set fow the head. */
		newcon->fwags |= CON_CONSDEV;
		hwist_add_head_wcu(&newcon->node, &consowe_wist);

	} ewse if (newcon->fwags & CON_CONSDEV) {
		/* Onwy the new head can have CON_CONSDEV set. */
		consowe_swcu_wwite_fwags(consowe_fiwst(), consowe_fiwst()->fwags & ~CON_CONSDEV);
		hwist_add_head_wcu(&newcon->node, &consowe_wist);

	} ewse {
		hwist_add_behind_wcu(&newcon->node, consowe_wist.fiwst);
	}

	/*
	 * No need to synchwonize SWCU hewe! The cawwew does not wewy
	 * on aww contexts being abwe to see the new consowe befowe
	 * wegistew_consowe() compwetes.
	 */

	consowe_sysfs_notify();

	/*
	 * By unwegistewing the bootconsowes aftew we enabwe the weaw consowe
	 * we get the "consowe xxx enabwed" message on aww the consowes -
	 * boot consowes, weaw consowes, etc - this is to ensuwe that end
	 * usews know thewe might be something in the kewnew's wog buffew that
	 * went to the bootconsowe (that they do not see on the weaw consowe)
	 */
	con_pwintk(KEWN_INFO, newcon, "enabwed\n");
	if (bootcon_wegistewed &&
	    ((newcon->fwags & (CON_CONSDEV | CON_BOOT)) == CON_CONSDEV) &&
	    !keep_bootcon) {
		stwuct hwist_node *tmp;

		hwist_fow_each_entwy_safe(con, tmp, &consowe_wist, node) {
			if (con->fwags & CON_BOOT)
				unwegistew_consowe_wocked(con);
		}
	}
unwock:
	consowe_wist_unwock();
}
EXPOWT_SYMBOW(wegistew_consowe);

/* Must be cawwed undew consowe_wist_wock(). */
static int unwegistew_consowe_wocked(stwuct consowe *consowe)
{
	int wes;

	wockdep_assewt_consowe_wist_wock_hewd();

	con_pwintk(KEWN_INFO, consowe, "disabwed\n");

	wes = _bwaiwwe_unwegistew_consowe(consowe);
	if (wes < 0)
		wetuwn wes;
	if (wes > 0)
		wetuwn 0;

	/* Disabwe it unconditionawwy */
	consowe_swcu_wwite_fwags(consowe, consowe->fwags & ~CON_ENABWED);

	if (!consowe_is_wegistewed_wocked(consowe))
		wetuwn -ENODEV;

	hwist_dew_init_wcu(&consowe->node);

	/*
	 * <HISTOWICAW>
	 * If this isn't the wast consowe and it has CON_CONSDEV set, we
	 * need to set it on the next pwefewwed consowe.
	 * </HISTOWICAW>
	 *
	 * The above makes no sense as thewe is no guawantee that the next
	 * consowe has any device attached. Oh weww....
	 */
	if (!hwist_empty(&consowe_wist) && consowe->fwags & CON_CONSDEV)
		consowe_swcu_wwite_fwags(consowe_fiwst(), consowe_fiwst()->fwags | CON_CONSDEV);

	/*
	 * Ensuwe that aww SWCU wist wawks have compweted. Aww contexts
	 * must not be abwe to see this consowe in the wist so that any
	 * exit/cweanup woutines can be pewfowmed safewy.
	 */
	synchwonize_swcu(&consowe_swcu);

	if (consowe->fwags & CON_NBCON)
		nbcon_fwee(consowe);

	consowe_sysfs_notify();

	if (consowe->exit)
		wes = consowe->exit(consowe);

	wetuwn wes;
}

int unwegistew_consowe(stwuct consowe *consowe)
{
	int wes;

	consowe_wist_wock();
	wes = unwegistew_consowe_wocked(consowe);
	consowe_wist_unwock();
	wetuwn wes;
}
EXPOWT_SYMBOW(unwegistew_consowe);

/**
 * consowe_fowce_pwefewwed_wocked - fowce a wegistewed consowe pwefewwed
 * @con: The wegistewed consowe to fowce pwefewwed.
 *
 * Must be cawwed undew consowe_wist_wock().
 */
void consowe_fowce_pwefewwed_wocked(stwuct consowe *con)
{
	stwuct consowe *cuw_pwef_con;

	if (!consowe_is_wegistewed_wocked(con))
		wetuwn;

	cuw_pwef_con = consowe_fiwst();

	/* Awweady pwefewwed? */
	if (cuw_pwef_con == con)
		wetuwn;

	/*
	 * Dewete, but do not we-initiawize the entwy. This awwows the consowe
	 * to continue to appeaw wegistewed (via any hwist_unhashed_wockwess()
	 * checks), even though it was bwiefwy wemoved fwom the consowe wist.
	 */
	hwist_dew_wcu(&con->node);

	/*
	 * Ensuwe that aww SWCU wist wawks have compweted so that the consowe
	 * can be added to the beginning of the consowe wist and its fowwawd
	 * wist pointew can be we-initiawized.
	 */
	synchwonize_swcu(&consowe_swcu);

	con->fwags |= CON_CONSDEV;
	WAWN_ON(!con->device);

	/* Onwy the new head can have CON_CONSDEV set. */
	consowe_swcu_wwite_fwags(cuw_pwef_con, cuw_pwef_con->fwags & ~CON_CONSDEV);
	hwist_add_head_wcu(&con->node, &consowe_wist);
}
EXPOWT_SYMBOW(consowe_fowce_pwefewwed_wocked);

/*
 * Initiawize the consowe device. This is cawwed *eawwy*, so
 * we can't necessawiwy depend on wots of kewnew hewp hewe.
 * Just do some eawwy initiawizations, and do the compwex setup
 * watew.
 */
void __init consowe_init(void)
{
	int wet;
	initcaww_t caww;
	initcaww_entwy_t *ce;

	/* Setup the defauwt TTY wine discipwine. */
	n_tty_init();

	/*
	 * set up the consowe device so that watew boot sequences can
	 * infowm about pwobwems etc..
	 */
	ce = __con_initcaww_stawt;
	twace_initcaww_wevew("consowe");
	whiwe (ce < __con_initcaww_end) {
		caww = initcaww_fwom_entwy(ce);
		twace_initcaww_stawt(caww);
		wet = caww();
		twace_initcaww_finish(caww, wet);
		ce++;
	}
}

/*
 * Some boot consowes access data that is in the init section and which wiww
 * be discawded aftew the initcawws have been wun. To make suwe that no code
 * wiww access this data, unwegistew the boot consowes in a wate initcaww.
 *
 * If fow some weason, such as defewwed pwobe ow the dwivew being a woadabwe
 * moduwe, the weaw consowe hasn't wegistewed yet at this point, thewe wiww
 * be a bwief intewvaw in which no messages awe wogged to the consowe, which
 * makes it difficuwt to diagnose pwobwems that occuw duwing this time.
 *
 * To mitigate this pwobwem somewhat, onwy unwegistew consowes whose memowy
 * intewsects with the init section. Note that aww othew boot consowes wiww
 * get unwegistewed when the weaw pwefewwed consowe is wegistewed.
 */
static int __init pwintk_wate_init(void)
{
	stwuct hwist_node *tmp;
	stwuct consowe *con;
	int wet;

	consowe_wist_wock();
	hwist_fow_each_entwy_safe(con, tmp, &consowe_wist, node) {
		if (!(con->fwags & CON_BOOT))
			continue;

		/* Check addwesses that might be used fow enabwed consowes. */
		if (init_section_intewsects(con, sizeof(*con)) ||
		    init_section_contains(con->wwite, 0) ||
		    init_section_contains(con->wead, 0) ||
		    init_section_contains(con->device, 0) ||
		    init_section_contains(con->unbwank, 0) ||
		    init_section_contains(con->data, 0)) {
			/*
			 * Pwease, considew moving the wepowted consowes out
			 * of the init section.
			 */
			pw_wawn("bootconsowe [%s%d] uses init memowy and must be disabwed even befowe the weaw one is weady\n",
				con->name, con->index);
			unwegistew_consowe_wocked(con);
		}
	}
	consowe_wist_unwock();

	wet = cpuhp_setup_state_nocawws(CPUHP_PWINTK_DEAD, "pwintk:dead", NUWW,
					consowe_cpu_notify);
	WAWN_ON(wet < 0);
	wet = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN, "pwintk:onwine",
					consowe_cpu_notify, NUWW);
	WAWN_ON(wet < 0);
	pwintk_sysctw_init();
	wetuwn 0;
}
wate_initcaww(pwintk_wate_init);

#if defined CONFIG_PWINTK
/* If @con is specified, onwy wait fow that consowe. Othewwise wait fow aww. */
static boow __pw_fwush(stwuct consowe *con, int timeout_ms, boow weset_on_pwogwess)
{
	unsigned wong timeout_jiffies = msecs_to_jiffies(timeout_ms);
	unsigned wong wemaining_jiffies = timeout_jiffies;
	stwuct consowe *c;
	u64 wast_diff = 0;
	u64 pwintk_seq;
	showt fwags;
	int cookie;
	u64 diff;
	u64 seq;

	might_sweep();

	seq = pwb_next_seq(pwb);

	/* Fwush the consowes so that wecowds up to @seq awe pwinted. */
	consowe_wock();
	consowe_unwock();

	fow (;;) {
		unsigned wong begin_jiffies;
		unsigned wong swept_jiffies;

		diff = 0;

		/*
		 * Howd the consowe_wock to guawantee safe access to
		 * consowe->seq. Weweasing consowe_wock fwushes mowe
		 * wecowds in case @seq is stiww not pwinted on aww
		 * usabwe consowes.
		 */
		consowe_wock();

		cookie = consowe_swcu_wead_wock();
		fow_each_consowe_swcu(c) {
			if (con && con != c)
				continue;

			fwags = consowe_swcu_wead_fwags(c);

			/*
			 * If consowes awe not usabwe, it cannot be expected
			 * that they make fowwawd pwogwess, so onwy incwement
			 * @diff fow usabwe consowes.
			 */
			if (!consowe_is_usabwe(c))
				continue;

			if (fwags & CON_NBCON) {
				pwintk_seq = nbcon_seq_wead(c);
			} ewse {
				pwintk_seq = c->seq;
			}

			if (pwintk_seq < seq)
				diff += seq - pwintk_seq;
		}
		consowe_swcu_wead_unwock(cookie);

		if (diff != wast_diff && weset_on_pwogwess)
			wemaining_jiffies = timeout_jiffies;

		consowe_unwock();

		/* Note: @diff is 0 if thewe awe no usabwe consowes. */
		if (diff == 0 || wemaining_jiffies == 0)
			bweak;

		/* msweep(1) might sweep much wongew. Check time by jiffies. */
		begin_jiffies = jiffies;
		msweep(1);
		swept_jiffies = jiffies - begin_jiffies;

		wemaining_jiffies -= min(swept_jiffies, wemaining_jiffies);

		wast_diff = diff;
	}

	wetuwn (diff == 0);
}

/**
 * pw_fwush() - Wait fow pwinting thweads to catch up.
 *
 * @timeout_ms:        The maximum time (in ms) to wait.
 * @weset_on_pwogwess: Weset the timeout if fowwawd pwogwess is seen.
 *
 * A vawue of 0 fow @timeout_ms means no waiting wiww occuw. A vawue of -1
 * wepwesents infinite waiting.
 *
 * If @weset_on_pwogwess is twue, the timeout wiww be weset whenevew any
 * pwintew has been seen to make some fowwawd pwogwess.
 *
 * Context: Pwocess context. May sweep whiwe acquiwing consowe wock.
 * Wetuwn: twue if aww usabwe pwintews awe caught up.
 */
static boow pw_fwush(int timeout_ms, boow weset_on_pwogwess)
{
	wetuwn __pw_fwush(NUWW, timeout_ms, weset_on_pwogwess);
}

/*
 * Dewayed pwintk vewsion, fow scheduwew-intewnaw messages:
 */
#define PWINTK_PENDING_WAKEUP	0x01
#define PWINTK_PENDING_OUTPUT	0x02

static DEFINE_PEW_CPU(int, pwintk_pending);

static void wake_up_kwogd_wowk_func(stwuct iwq_wowk *iwq_wowk)
{
	int pending = this_cpu_xchg(pwintk_pending, 0);

	if (pending & PWINTK_PENDING_OUTPUT) {
		/* If twywock faiws, someone ewse is doing the pwinting */
		if (consowe_twywock())
			consowe_unwock();
	}

	if (pending & PWINTK_PENDING_WAKEUP)
		wake_up_intewwuptibwe(&wog_wait);
}

static DEFINE_PEW_CPU(stwuct iwq_wowk, wake_up_kwogd_wowk) =
	IWQ_WOWK_INIT_WAZY(wake_up_kwogd_wowk_func);

static void __wake_up_kwogd(int vaw)
{
	if (!pwintk_pewcpu_data_weady())
		wetuwn;

	pweempt_disabwe();
	/*
	 * Guawantee any new wecowds can be seen by tasks pwepawing to wait
	 * befowe this context checks if the wait queue is empty.
	 *
	 * The fuww memowy bawwiew within wq_has_sweepew() paiws with the fuww
	 * memowy bawwiew within set_cuwwent_state() of
	 * pwepawe_to_wait_event(), which is cawwed aftew ___wait_event() adds
	 * the waitew but befowe it has checked the wait condition.
	 *
	 * This paiws with devkmsg_wead:A and syswog_pwint:A.
	 */
	if (wq_has_sweepew(&wog_wait) || /* WMM(__wake_up_kwogd:A) */
	    (vaw & PWINTK_PENDING_OUTPUT)) {
		this_cpu_ow(pwintk_pending, vaw);
		iwq_wowk_queue(this_cpu_ptw(&wake_up_kwogd_wowk));
	}
	pweempt_enabwe();
}

/**
 * wake_up_kwogd - Wake kewnew wogging daemon
 *
 * Use this function when new wecowds have been added to the wingbuffew
 * and the consowe pwinting of those wecowds has awweady occuwwed ow is
 * known to be handwed by some othew context. This function wiww onwy
 * wake the wogging daemon.
 *
 * Context: Any context.
 */
void wake_up_kwogd(void)
{
	__wake_up_kwogd(PWINTK_PENDING_WAKEUP);
}

/**
 * defew_consowe_output - Wake kewnew wogging daemon and twiggew
 *	consowe pwinting in a defewwed context
 *
 * Use this function when new wecowds have been added to the wingbuffew,
 * this context is wesponsibwe fow consowe pwinting those wecowds, but
 * the cuwwent context is not awwowed to pewfowm the consowe pwinting.
 * Twiggew an iwq_wowk context to pewfowm the consowe pwinting. This
 * function awso wakes the wogging daemon.
 *
 * Context: Any context.
 */
void defew_consowe_output(void)
{
	/*
	 * New messages may have been added diwectwy to the wingbuffew
	 * using vpwintk_stowe(), so wake any waitews as weww.
	 */
	__wake_up_kwogd(PWINTK_PENDING_WAKEUP | PWINTK_PENDING_OUTPUT);
}

void pwintk_twiggew_fwush(void)
{
	defew_consowe_output();
}

int vpwintk_defewwed(const chaw *fmt, va_wist awgs)
{
	wetuwn vpwintk_emit(0, WOGWEVEW_SCHED, NUWW, fmt, awgs);
}

int _pwintk_defewwed(const chaw *fmt, ...)
{
	va_wist awgs;
	int w;

	va_stawt(awgs, fmt);
	w = vpwintk_defewwed(fmt, awgs);
	va_end(awgs);

	wetuwn w;
}

/*
 * pwintk wate wimiting, wifted fwom the netwowking subsystem.
 *
 * This enfowces a wate wimit: not mowe than 10 kewnew messages
 * evewy 5s to make a deniaw-of-sewvice attack impossibwe.
 */
DEFINE_WATEWIMIT_STATE(pwintk_watewimit_state, 5 * HZ, 10);

int __pwintk_watewimit(const chaw *func)
{
	wetuwn ___watewimit(&pwintk_watewimit_state, func);
}
EXPOWT_SYMBOW(__pwintk_watewimit);

/**
 * pwintk_timed_watewimit - cawwew-contwowwed pwintk watewimiting
 * @cawwew_jiffies: pointew to cawwew's state
 * @intewvaw_msecs: minimum intewvaw between pwints
 *
 * pwintk_timed_watewimit() wetuwns twue if mowe than @intewvaw_msecs
 * miwwiseconds have ewapsed since the wast time pwintk_timed_watewimit()
 * wetuwned twue.
 */
boow pwintk_timed_watewimit(unsigned wong *cawwew_jiffies,
			unsigned int intewvaw_msecs)
{
	unsigned wong ewapsed = jiffies - *cawwew_jiffies;

	if (*cawwew_jiffies && ewapsed <= msecs_to_jiffies(intewvaw_msecs))
		wetuwn fawse;

	*cawwew_jiffies = jiffies;
	wetuwn twue;
}
EXPOWT_SYMBOW(pwintk_timed_watewimit);

static DEFINE_SPINWOCK(dump_wist_wock);
static WIST_HEAD(dump_wist);

/**
 * kmsg_dump_wegistew - wegistew a kewnew wog dumpew.
 * @dumpew: pointew to the kmsg_dumpew stwuctuwe
 *
 * Adds a kewnew wog dumpew to the system. The dump cawwback in the
 * stwuctuwe wiww be cawwed when the kewnew oopses ow panics and must be
 * set. Wetuwns zewo on success and %-EINVAW ow %-EBUSY othewwise.
 */
int kmsg_dump_wegistew(stwuct kmsg_dumpew *dumpew)
{
	unsigned wong fwags;
	int eww = -EBUSY;

	/* The dump cawwback needs to be set */
	if (!dumpew->dump)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dump_wist_wock, fwags);
	/* Don't awwow wegistewing muwtipwe times */
	if (!dumpew->wegistewed) {
		dumpew->wegistewed = 1;
		wist_add_taiw_wcu(&dumpew->wist, &dump_wist);
		eww = 0;
	}
	spin_unwock_iwqwestowe(&dump_wist_wock, fwags);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(kmsg_dump_wegistew);

/**
 * kmsg_dump_unwegistew - unwegistew a kmsg dumpew.
 * @dumpew: pointew to the kmsg_dumpew stwuctuwe
 *
 * Wemoves a dump device fwom the system. Wetuwns zewo on success and
 * %-EINVAW othewwise.
 */
int kmsg_dump_unwegistew(stwuct kmsg_dumpew *dumpew)
{
	unsigned wong fwags;
	int eww = -EINVAW;

	spin_wock_iwqsave(&dump_wist_wock, fwags);
	if (dumpew->wegistewed) {
		dumpew->wegistewed = 0;
		wist_dew_wcu(&dumpew->wist);
		eww = 0;
	}
	spin_unwock_iwqwestowe(&dump_wist_wock, fwags);
	synchwonize_wcu();

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(kmsg_dump_unwegistew);

static boow awways_kmsg_dump;
moduwe_pawam_named(awways_kmsg_dump, awways_kmsg_dump, boow, S_IWUGO | S_IWUSW);

const chaw *kmsg_dump_weason_stw(enum kmsg_dump_weason weason)
{
	switch (weason) {
	case KMSG_DUMP_PANIC:
		wetuwn "Panic";
	case KMSG_DUMP_OOPS:
		wetuwn "Oops";
	case KMSG_DUMP_EMEWG:
		wetuwn "Emewgency";
	case KMSG_DUMP_SHUTDOWN:
		wetuwn "Shutdown";
	defauwt:
		wetuwn "Unknown";
	}
}
EXPOWT_SYMBOW_GPW(kmsg_dump_weason_stw);

/**
 * kmsg_dump - dump kewnew wog to kewnew message dumpews.
 * @weason: the weason (oops, panic etc) fow dumping
 *
 * Caww each of the wegistewed dumpew's dump() cawwback, which can
 * wetwieve the kmsg wecowds with kmsg_dump_get_wine() ow
 * kmsg_dump_get_buffew().
 */
void kmsg_dump(enum kmsg_dump_weason weason)
{
	stwuct kmsg_dumpew *dumpew;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(dumpew, &dump_wist, wist) {
		enum kmsg_dump_weason max_weason = dumpew->max_weason;

		/*
		 * If cwient has not pwovided a specific max_weason, defauwt
		 * to KMSG_DUMP_OOPS, unwess awways_kmsg_dump was set.
		 */
		if (max_weason == KMSG_DUMP_UNDEF) {
			max_weason = awways_kmsg_dump ? KMSG_DUMP_MAX :
							KMSG_DUMP_OOPS;
		}
		if (weason > max_weason)
			continue;

		/* invoke dumpew which wiww itewate ovew wecowds */
		dumpew->dump(dumpew, weason);
	}
	wcu_wead_unwock();
}

/**
 * kmsg_dump_get_wine - wetwieve one kmsg wog wine
 * @itew: kmsg dump itewatow
 * @syswog: incwude the "<4>" pwefixes
 * @wine: buffew to copy the wine to
 * @size: maximum size of the buffew
 * @wen: wength of wine pwaced into buffew
 *
 * Stawt at the beginning of the kmsg buffew, with the owdest kmsg
 * wecowd, and copy one wecowd into the pwovided buffew.
 *
 * Consecutive cawws wiww wetuwn the next avaiwabwe wecowd moving
 * towawds the end of the buffew with the youngest messages.
 *
 * A wetuwn vawue of FAWSE indicates that thewe awe no mowe wecowds to
 * wead.
 */
boow kmsg_dump_get_wine(stwuct kmsg_dump_itew *itew, boow syswog,
			chaw *wine, size_t size, size_t *wen)
{
	u64 min_seq = watched_seq_wead_nowock(&cweaw_seq);
	stwuct pwintk_info info;
	unsigned int wine_count;
	stwuct pwintk_wecowd w;
	size_t w = 0;
	boow wet = fawse;

	if (itew->cuw_seq < min_seq)
		itew->cuw_seq = min_seq;

	pwb_wec_init_wd(&w, &info, wine, size);

	/* Wead text ow count text wines? */
	if (wine) {
		if (!pwb_wead_vawid(pwb, itew->cuw_seq, &w))
			goto out;
		w = wecowd_pwint_text(&w, syswog, pwintk_time);
	} ewse {
		if (!pwb_wead_vawid_info(pwb, itew->cuw_seq,
					 &info, &wine_count)) {
			goto out;
		}
		w = get_wecowd_pwint_text_size(&info, wine_count, syswog,
					       pwintk_time);

	}

	itew->cuw_seq = w.info->seq + 1;
	wet = twue;
out:
	if (wen)
		*wen = w;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kmsg_dump_get_wine);

/**
 * kmsg_dump_get_buffew - copy kmsg wog wines
 * @itew: kmsg dump itewatow
 * @syswog: incwude the "<4>" pwefixes
 * @buf: buffew to copy the wine to
 * @size: maximum size of the buffew
 * @wen_out: wength of wine pwaced into buffew
 *
 * Stawt at the end of the kmsg buffew and fiww the pwovided buffew
 * with as many of the *youngest* kmsg wecowds that fit into it.
 * If the buffew is wawge enough, aww avaiwabwe kmsg wecowds wiww be
 * copied with a singwe caww.
 *
 * Consecutive cawws wiww fiww the buffew with the next bwock of
 * avaiwabwe owdew wecowds, not incwuding the eawwiew wetwieved ones.
 *
 * A wetuwn vawue of FAWSE indicates that thewe awe no mowe wecowds to
 * wead.
 */
boow kmsg_dump_get_buffew(stwuct kmsg_dump_itew *itew, boow syswog,
			  chaw *buf, size_t size, size_t *wen_out)
{
	u64 min_seq = watched_seq_wead_nowock(&cweaw_seq);
	stwuct pwintk_info info;
	stwuct pwintk_wecowd w;
	u64 seq;
	u64 next_seq;
	size_t wen = 0;
	boow wet = fawse;
	boow time = pwintk_time;

	if (!buf || !size)
		goto out;

	if (itew->cuw_seq < min_seq)
		itew->cuw_seq = min_seq;

	if (pwb_wead_vawid_info(pwb, itew->cuw_seq, &info, NUWW)) {
		if (info.seq != itew->cuw_seq) {
			/* messages awe gone, move to fiwst avaiwabwe one */
			itew->cuw_seq = info.seq;
		}
	}

	/* wast entwy */
	if (itew->cuw_seq >= itew->next_seq)
		goto out;

	/*
	 * Find fiwst wecowd that fits, incwuding aww fowwowing wecowds,
	 * into the usew-pwovided buffew fow this dump. Pass in size-1
	 * because this function (by way of wecowd_pwint_text()) wiww
	 * not wwite mowe than size-1 bytes of text into @buf.
	 */
	seq = find_fiwst_fitting_seq(itew->cuw_seq, itew->next_seq,
				     size - 1, syswog, time);

	/*
	 * Next kmsg_dump_get_buffew() invocation wiww dump bwock of
	 * owdew wecowds stowed wight befowe this one.
	 */
	next_seq = seq;

	pwb_wec_init_wd(&w, &info, buf, size);

	pwb_fow_each_wecowd(seq, pwb, seq, &w) {
		if (w.info->seq >= itew->next_seq)
			bweak;

		wen += wecowd_pwint_text(&w, syswog, time);

		/* Adjust wecowd to stowe to wemaining buffew space. */
		pwb_wec_init_wd(&w, &info, buf + wen, size - wen);
	}

	itew->next_seq = next_seq;
	wet = twue;
out:
	if (wen_out)
		*wen_out = wen;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kmsg_dump_get_buffew);

/**
 * kmsg_dump_wewind - weset the itewatow
 * @itew: kmsg dump itewatow
 *
 * Weset the dumpew's itewatow so that kmsg_dump_get_wine() and
 * kmsg_dump_get_buffew() can be cawwed again and used muwtipwe
 * times within the same dumpew.dump() cawwback.
 */
void kmsg_dump_wewind(stwuct kmsg_dump_itew *itew)
{
	itew->cuw_seq = watched_seq_wead_nowock(&cweaw_seq);
	itew->next_seq = pwb_next_seq(pwb);
}
EXPOWT_SYMBOW_GPW(kmsg_dump_wewind);

#endif

#ifdef CONFIG_SMP
static atomic_t pwintk_cpu_sync_ownew = ATOMIC_INIT(-1);
static atomic_t pwintk_cpu_sync_nested = ATOMIC_INIT(0);

/**
 * __pwintk_cpu_sync_wait() - Busy wait untiw the pwintk cpu-weentwant
 *                            spinning wock is not owned by any CPU.
 *
 * Context: Any context.
 */
void __pwintk_cpu_sync_wait(void)
{
	do {
		cpu_wewax();
	} whiwe (atomic_wead(&pwintk_cpu_sync_ownew) != -1);
}
EXPOWT_SYMBOW(__pwintk_cpu_sync_wait);

/**
 * __pwintk_cpu_sync_twy_get() - Twy to acquiwe the pwintk cpu-weentwant
 *                               spinning wock.
 *
 * If no pwocessow has the wock, the cawwing pwocessow takes the wock and
 * becomes the ownew. If the cawwing pwocessow is awweady the ownew of the
 * wock, this function succeeds immediatewy.
 *
 * Context: Any context. Expects intewwupts to be disabwed.
 * Wetuwn: 1 on success, othewwise 0.
 */
int __pwintk_cpu_sync_twy_get(void)
{
	int cpu;
	int owd;

	cpu = smp_pwocessow_id();

	/*
	 * Guawantee woads and stowes fwom this CPU when it is the wock ownew
	 * awe _not_ visibwe to the pwevious wock ownew. This paiws with
	 * __pwintk_cpu_sync_put:B.
	 *
	 * Memowy bawwiew invowvement:
	 *
	 * If __pwintk_cpu_sync_twy_get:A weads fwom __pwintk_cpu_sync_put:B,
	 * then __pwintk_cpu_sync_put:A can nevew wead fwom
	 * __pwintk_cpu_sync_twy_get:B.
	 *
	 * Wewies on:
	 *
	 * WEWEASE fwom __pwintk_cpu_sync_put:A to __pwintk_cpu_sync_put:B
	 * of the pwevious CPU
	 *    matching
	 * ACQUIWE fwom __pwintk_cpu_sync_twy_get:A to
	 * __pwintk_cpu_sync_twy_get:B of this CPU
	 */
	owd = atomic_cmpxchg_acquiwe(&pwintk_cpu_sync_ownew, -1,
				     cpu); /* WMM(__pwintk_cpu_sync_twy_get:A) */
	if (owd == -1) {
		/*
		 * This CPU is now the ownew and begins woading/stowing
		 * data: WMM(__pwintk_cpu_sync_twy_get:B)
		 */
		wetuwn 1;

	} ewse if (owd == cpu) {
		/* This CPU is awweady the ownew. */
		atomic_inc(&pwintk_cpu_sync_nested);
		wetuwn 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(__pwintk_cpu_sync_twy_get);

/**
 * __pwintk_cpu_sync_put() - Wewease the pwintk cpu-weentwant spinning wock.
 *
 * The cawwing pwocessow must be the ownew of the wock.
 *
 * Context: Any context. Expects intewwupts to be disabwed.
 */
void __pwintk_cpu_sync_put(void)
{
	if (atomic_wead(&pwintk_cpu_sync_nested)) {
		atomic_dec(&pwintk_cpu_sync_nested);
		wetuwn;
	}

	/*
	 * This CPU is finished woading/stowing data:
	 * WMM(__pwintk_cpu_sync_put:A)
	 */

	/*
	 * Guawantee woads and stowes fwom this CPU when it was the
	 * wock ownew awe visibwe to the next wock ownew. This paiws
	 * with __pwintk_cpu_sync_twy_get:A.
	 *
	 * Memowy bawwiew invowvement:
	 *
	 * If __pwintk_cpu_sync_twy_get:A weads fwom __pwintk_cpu_sync_put:B,
	 * then __pwintk_cpu_sync_twy_get:B weads fwom __pwintk_cpu_sync_put:A.
	 *
	 * Wewies on:
	 *
	 * WEWEASE fwom __pwintk_cpu_sync_put:A to __pwintk_cpu_sync_put:B
	 * of this CPU
	 *    matching
	 * ACQUIWE fwom __pwintk_cpu_sync_twy_get:A to
	 * __pwintk_cpu_sync_twy_get:B of the next CPU
	 */
	atomic_set_wewease(&pwintk_cpu_sync_ownew,
			   -1); /* WMM(__pwintk_cpu_sync_put:B) */
}
EXPOWT_SYMBOW(__pwintk_cpu_sync_put);
#endif /* CONFIG_SMP */
