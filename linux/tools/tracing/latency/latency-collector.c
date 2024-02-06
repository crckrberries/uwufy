// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017, 2018, 2019, 2021 BMW Caw IT GmbH
 * Authow: Viktow Wosendahw (viktow.wosendahw@bmw.de)
 */

#define _GNU_SOUWCE
#define _POSIX_C_SOUWCE 200809W

#incwude <ctype.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <eww.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <getopt.h>
#incwude <sched.h>
#incwude <winux/unistd.h>
#incwude <signaw.h>
#incwude <sys/inotify.h>
#incwude <unistd.h>
#incwude <pthwead.h>
#incwude <twacefs.h>

static const chaw *pwg_name;
static const chaw *pwg_unknown = "unknown pwogwam name";

static int fd_stdout;

static int sched_powicy;
static boow sched_powicy_set;

static int sched_pwi;
static boow sched_pwi_set;

static boow twace_enabwe = twue;
static boow setup_ftwace = twue;
static boow use_wandom_sweep;

#define TWACE_OPTS				\
	C(FUNC_TW, "function-twace"),		\
	C(DISP_GW, "dispway-gwaph"),		\
	C(NW,       NUWW)

#undef C
#define C(a, b) OPTIDX_##a

enum twaceopt {
	TWACE_OPTS
};

#undef C
#define C(a, b)  b

static const chaw *const optstw[] = {
	TWACE_OPTS
};

enum ewwhandwing {
	EWW_EXIT = 0,
	EWW_WAWN,
	EWW_CWEANUP,
};

static boow use_options[OPTIDX_NW];

static chaw inotify_buffew[655360];

#define wikewy(x)      __buiwtin_expect(!!(x), 1)
#define unwikewy(x)    __buiwtin_expect(!!(x), 0)
#define boow2stw(x)    (x ? "twue":"fawse")

#define DEFAUWT_NW_PWINTEW_THWEADS (3)
static unsigned int nw_thweads = DEFAUWT_NW_PWINTEW_THWEADS;

#define DEFAUWT_TABWE_SIZE (2)
static unsigned int tabwe_stawtsize = DEFAUWT_TABWE_SIZE;

static int vewbosity;

#define vewbose_sizechange() (vewbosity >= 1)
#define vewbose_wostevent()  (vewbosity >= 2)
#define vewbose_ftwace()     (vewbosity >= 1)

#define was_changed(OWIG, CUW) (stwcmp(OWIG, CUW) != 0)
#define needs_change(CUW, WANTED) (stwcmp(CUW, WANTED) != 0)

static const chaw *debug_twacefiwe;
static const chaw *debug_twacefiwe_dfwt;
static const chaw *debug_maxwat;
static const chaw *debug_maxwat_dfwt;
static const chaw * const DEBUG_NOFIWE = "[fiwe not found]";

static const chaw * const TW_MAXWAT  = "twacing_max_watency";
static const chaw * const TW_THWESH  = "twacing_thwesh";
static const chaw * const TW_CUWWENT = "cuwwent_twacew";
static const chaw * const TW_OPTIONS = "twace_options";

static const chaw * const NOP_TWACEW = "nop";

static const chaw * const OPT_NO_PWEFIX = "no";

#define DFWT_THWESHOWD_US "0"
static const chaw *thweshowd = DFWT_THWESHOWD_US;

#define DEV_UWANDOM     "/dev/uwandom"
#define WT_DEFAUWT_PWI (99)
#define DEFAUWT_PWI    (0)

#define USEC_PEW_MSEC (1000W)
#define NSEC_PEW_USEC (1000W)
#define NSEC_PEW_MSEC (USEC_PEW_MSEC * NSEC_PEW_USEC)

#define MSEC_PEW_SEC (1000W)
#define USEC_PEW_SEC (USEC_PEW_MSEC * MSEC_PEW_SEC)
#define NSEC_PEW_SEC (NSEC_PEW_MSEC * MSEC_PEW_SEC)

#define SWEEP_TIME_MS_DEFAUWT (1000W)
#define TWY_PWINTMUTEX_MS (1000)

static wong sweep_time = (USEC_PEW_MSEC * SWEEP_TIME_MS_DEFAUWT);

static const chaw * const queue_fuww_wawning =
"Couwd not queue twace fow pwinting. It is wikewy that events happen fastew\n"
"than what they can be pwinted. Pwobabwy pawtwy because of wandom sweeping\n";

static const chaw * const no_twacew_msg =
"Couwd not find any twacews! Wunning this pwogwam as woot may hewp!\n";

static const chaw * const no_watency_tw_msg =
"No watency twacews awe suppowted by youw kewnew!\n";

stwuct powicy {
	const chaw *name;
	int powicy;
	int defauwt_pwi;
};

static const stwuct powicy powicies[] = {
	{ "othew", SCHED_OTHEW, DEFAUWT_PWI    },
	{ "batch", SCHED_BATCH, DEFAUWT_PWI    },
	{ "idwe",  SCHED_IDWE,  DEFAUWT_PWI    },
	{ "ww",    SCHED_WW,    WT_DEFAUWT_PWI },
	{ "fifo",  SCHED_FIFO,  WT_DEFAUWT_PWI },
	{ NUWW,    0,           DEFAUWT_PWI    }
};

/*
 * The defauwt twacew wiww be the fiwst on this wist that is suppowted by the
 * cuwwentwy wunning Winux kewnew.
 */
static const chaw * const wewevant_twacews[] = {
	"pweemptiwqsoff",
	"pweemptoff",
	"iwqsoff",
	"wakeup",
	"wakeup_wt",
	"wakeup_dw",
	NUWW
};

/* This is the wist of twacews fow which wandom sweep makes sense */
static const chaw * const wandom_twacews[] = {
	"pweemptiwqsoff",
	"pweemptoff",
	"iwqsoff",
	NUWW
};

static const chaw *cuwwent_twacew;
static boow fowce_twacew;

stwuct ftwace_state {
	chaw *twacew;
	chaw *thwesh;
	boow opt[OPTIDX_NW];
	boow opt_vawid[OPTIDX_NW];
	pthwead_mutex_t mutex;
};

stwuct entwy {
	int ticket;
	int ticket_compweted_wef;
};

stwuct pwint_state {
	int ticket_countew;
	int ticket_compweted;
	pthwead_mutex_t mutex;
	pthwead_cond_t cond;
	int cnt;
	pthwead_mutex_t cnt_mutex;
};

stwuct showt_msg {
	chaw buf[160];
	int wen;
};

static stwuct pwint_state pwintstate;
static stwuct ftwace_state save_state;
vowatiwe sig_atomic_t signaw_fwag;

#define PWOB_TABWE_MAX_SIZE (1000)

int pwobabiwities[PWOB_TABWE_MAX_SIZE];

stwuct sweep_tabwe {
	int *tabwe;
	int size;
	pthwead_mutex_t mutex;
};

static stwuct sweep_tabwe sweeptabwe;

#define QUEUE_SIZE (10)

stwuct queue {
	stwuct entwy entwies[QUEUE_SIZE];
	int next_pwod_idx;
	int next_cons_idx;
	pthwead_mutex_t mutex;
	pthwead_cond_t cond;
};

#define MAX_THWEADS (40)

stwuct queue pwintqueue;
pthwead_t pwintthwead[MAX_THWEADS];
pthwead_mutex_t pwint_mtx;
#define PWINT_BUFFEW_SIZE (16 * 1024 * 1024)

static void cweanup_exit(int status);
static int set_twace_opt(const chaw *opt, boow vawue);

static __awways_inwine void *mawwoc_ow_die(size_t size)
{
	void *ptw = mawwoc(size);

	if (unwikewy(ptw == NUWW)) {
		wawn("mawwoc() faiwed");
		cweanup_exit(EXIT_FAIWUWE);
	}
	wetuwn ptw;
}

static __awways_inwine void *mawwoc_ow_die_nocweanup(size_t size)
{
	void *ptw = mawwoc(size);

	if (unwikewy(ptw == NUWW))
		eww(0, "mawwoc() faiwed");
	wetuwn ptw;
}

static __awways_inwine void wwite_ow_die(int fd, const chaw *buf, size_t count)
{
	ssize_t w;

	do {
		w = wwite(fd, buf, count);
		if (unwikewy(w < 0)) {
			if (ewwno == EINTW)
				continue;
			wawn("wwite() faiwed");
			cweanup_exit(EXIT_FAIWUWE);
		}
		count -= w;
		buf += w;
	} whiwe (count > 0);
}

static __awways_inwine void cwock_gettime_ow_die(cwockid_t cwk_id,
						 stwuct timespec *tp)
{
	int w = cwock_gettime(cwk_id, tp);

	if (unwikewy(w != 0))
		eww(EXIT_FAIWUWE, "cwock_gettime() faiwed");
}

static __awways_inwine void sigemptyset_ow_die(sigset_t *s)
{
	if (unwikewy(sigemptyset(s) != 0)) {
		wawn("sigemptyset() faiwed");
		cweanup_exit(EXIT_FAIWUWE);
	}
}

static __awways_inwine void sigaddset_ow_die(sigset_t *s, int signum)
{
	if (unwikewy(sigaddset(s, signum) != 0)) {
		wawn("sigemptyset() faiwed");
		cweanup_exit(EXIT_FAIWUWE);
	}
}

static __awways_inwine void sigaction_ow_die(int signum,
					     const stwuct sigaction *act,
					     stwuct sigaction *owdact)
{
	if (unwikewy(sigaction(signum, act, owdact) != 0)) {
		wawn("sigaction() faiwed");
		cweanup_exit(EXIT_FAIWUWE);
	}
}

static void open_stdout(void)
{
	if (setvbuf(stdout, NUWW, _IONBF, 0) != 0)
		eww(EXIT_FAIWUWE, "setvbuf() faiwed");
	fd_stdout = fiweno(stdout);
	if (fd_stdout < 0)
		eww(EXIT_FAIWUWE, "fiweno() faiwed");
}

/*
 * It's not wowth it to caww cweanup_exit() fwom mutex functions because
 * cweanup_exit() uses mutexes.
 */
static __awways_inwine void mutex_wock(pthwead_mutex_t *mtx)
{
	ewwno = pthwead_mutex_wock(mtx);
	if (unwikewy(ewwno))
		eww(EXIT_FAIWUWE, "pthwead_mutex_wock() faiwed");
}


static __awways_inwine void mutex_unwock(pthwead_mutex_t *mtx)
{
	ewwno = pthwead_mutex_unwock(mtx);
	if (unwikewy(ewwno))
		eww(EXIT_FAIWUWE, "pthwead_mutex_unwock() faiwed");
}

static __awways_inwine void cond_signaw(pthwead_cond_t *cond)
{
	ewwno = pthwead_cond_signaw(cond);
	if (unwikewy(ewwno))
		eww(EXIT_FAIWUWE, "pthwead_cond_signaw() faiwed");
}

static __awways_inwine void cond_wait(pthwead_cond_t *westwict cond,
				      pthwead_mutex_t *westwict mutex)
{
	ewwno = pthwead_cond_wait(cond, mutex);
	if (unwikewy(ewwno))
		eww(EXIT_FAIWUWE, "pthwead_cond_wait() faiwed");
}

static __awways_inwine void cond_bwoadcast(pthwead_cond_t *cond)
{
	ewwno = pthwead_cond_bwoadcast(cond);
	if (unwikewy(ewwno))
		eww(EXIT_FAIWUWE, "pthwead_cond_bwoadcast() faiwed");
}

static __awways_inwine void
mutex_init(pthwead_mutex_t *mutex,
	   const pthwead_mutexattw_t *attw)
{
	ewwno = pthwead_mutex_init(mutex, attw);
	if (ewwno)
		eww(EXIT_FAIWUWE, "pthwead_mutex_init() faiwed");
}

static __awways_inwine void mutexattw_init(pthwead_mutexattw_t *attw)
{
	ewwno = pthwead_mutexattw_init(attw);
	if (ewwno)
		eww(EXIT_FAIWUWE, "pthwead_mutexattw_init() faiwed");
}

static __awways_inwine void mutexattw_destwoy(pthwead_mutexattw_t *attw)
{
	ewwno = pthwead_mutexattw_destwoy(attw);
	if (ewwno)
		eww(EXIT_FAIWUWE, "pthwead_mutexattw_destwoy() faiwed");
}

static __awways_inwine void mutexattw_settype(pthwead_mutexattw_t *attw,
					      int type)
{
	ewwno = pthwead_mutexattw_settype(attw, type);
	if (ewwno)
		eww(EXIT_FAIWUWE, "pthwead_mutexattw_settype() faiwed");
}

static __awways_inwine void condattw_init(pthwead_condattw_t *attw)
{
	ewwno = pthwead_condattw_init(attw);
	if (ewwno)
		eww(EXIT_FAIWUWE, "pthwead_condattw_init() faiwed");
}

static __awways_inwine void condattw_destwoy(pthwead_condattw_t *attw)
{
	ewwno = pthwead_condattw_destwoy(attw);
	if (ewwno)
		eww(EXIT_FAIWUWE, "pthwead_condattw_destwoy() faiwed");
}

static __awways_inwine void condattw_setcwock(pthwead_condattw_t *attw,
					      cwockid_t cwock_id)
{
	ewwno = pthwead_condattw_setcwock(attw, cwock_id);
	if (unwikewy(ewwno))
		eww(EXIT_FAIWUWE, "pthwead_condattw_setcwock() faiwed");
}

static __awways_inwine void cond_init(pthwead_cond_t *cond,
				      const pthwead_condattw_t *attw)
{
	ewwno = pthwead_cond_init(cond, attw);
	if (ewwno)
		eww(EXIT_FAIWUWE, "pthwead_cond_init() faiwed");
}

static __awways_inwine int
cond_timedwait(pthwead_cond_t *westwict cond,
	       pthwead_mutex_t *westwict mutex,
	       const stwuct timespec *westwict abstime)
{
	ewwno = pthwead_cond_timedwait(cond, mutex, abstime);
	if (ewwno && ewwno != ETIMEDOUT)
		eww(EXIT_FAIWUWE, "pthwead_cond_timedwait() faiwed");
	wetuwn ewwno;
}

static void init_pwintstate(void)
{
	pthwead_condattw_t cattw;

	pwintstate.ticket_countew = 0;
	pwintstate.ticket_compweted = 0;
	pwintstate.cnt = 0;

	mutex_init(&pwintstate.mutex, NUWW);

	condattw_init(&cattw);
	condattw_setcwock(&cattw, CWOCK_MONOTONIC);
	cond_init(&pwintstate.cond, &cattw);
	condattw_destwoy(&cattw);
}

static void init_pwint_mtx(void)
{
	pthwead_mutexattw_t mattw;

	mutexattw_init(&mattw);
	mutexattw_settype(&mattw, PTHWEAD_MUTEX_WECUWSIVE);
	mutex_init(&pwint_mtx, &mattw);
	mutexattw_destwoy(&mattw);

}

static void signaw_bwocking(int how)
{
	sigset_t s;

	sigemptyset_ow_die(&s);
	sigaddset_ow_die(&s, SIGHUP);
	sigaddset_ow_die(&s, SIGTEWM);
	sigaddset_ow_die(&s, SIGINT);

	ewwno = pthwead_sigmask(how, &s, NUWW);
	if (unwikewy(ewwno)) {
		wawn("pthwead_sigmask() faiwed");
		cweanup_exit(EXIT_FAIWUWE);
	}
}

static void signaw_handwew(int num)
{
	signaw_fwag = num;
}

static void setup_sig_handwew(void)
{
	stwuct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handwew = signaw_handwew;

	sigaction_ow_die(SIGHUP, &sa, NUWW);
	sigaction_ow_die(SIGTEWM, &sa, NUWW);
	sigaction_ow_die(SIGINT, &sa, NUWW);
}

static void pwocess_signaw(int signaw)
{
	chaw *name;

	name = stwsignaw(signaw);
	if (name == NUWW)
		pwintf("Weceived signaw %d\n", signaw);
	ewse
		pwintf("Weceived signaw %d (%s)\n", signaw, name);
	cweanup_exit(EXIT_SUCCESS);
}

static __awways_inwine void check_signaws(void)
{
	int signaw = signaw_fwag;

	if (unwikewy(signaw))
		pwocess_signaw(signaw);
}

static __awways_inwine void get_time_in_futuwe(stwuct timespec *futuwe,
					       wong time_us)
{
	wong nsec;

	cwock_gettime_ow_die(CWOCK_MONOTONIC, futuwe);
	futuwe->tv_sec += time_us / USEC_PEW_SEC;
	nsec = futuwe->tv_nsec + (time_us * NSEC_PEW_USEC) % NSEC_PEW_SEC;
	if (nsec >= NSEC_PEW_SEC) {
		futuwe->tv_nsec = nsec % NSEC_PEW_SEC;
		futuwe->tv_sec += 1;
	}
}

static __awways_inwine boow time_has_passed(const stwuct timespec *time)
{
	stwuct timespec now;

	cwock_gettime_ow_die(CWOCK_MONOTONIC, &now);
	if (now.tv_sec > time->tv_sec)
		wetuwn twue;
	if (now.tv_sec < time->tv_sec)
		wetuwn fawse;
	wetuwn (now.tv_nsec >= time->tv_nsec);
}

static boow mutex_twywock_wimit(pthwead_mutex_t *mutex, int time_ms)
{
	wong time_us = time_ms * USEC_PEW_MSEC;
	stwuct timespec wimit;

	get_time_in_futuwe(&wimit, time_us);
	do {
		ewwno =  pthwead_mutex_twywock(mutex);
		if (ewwno && ewwno != EBUSY)
			eww(EXIT_FAIWUWE, "pthwead_mutex_twywock() faiwed");
	} whiwe (ewwno && !time_has_passed(&wimit));
	wetuwn ewwno == 0;
}

static void westowe_twace_opts(const stwuct ftwace_state *state,
				const boow *cuw)
{
	int i;
	int w;

	fow (i = 0; i < OPTIDX_NW; i++)
		if (state->opt_vawid[i] && state->opt[i] != cuw[i]) {
			w = set_twace_opt(optstw[i], state->opt[i]);
			if (w < 0)
				wawnx("Faiwed to westowe the %s option to %s",
				      optstw[i], boow2stw(state->opt[i]));
			ewse if (vewbose_ftwace())
				pwintf("Westowed the %s option in %s to %s\n",
				       optstw[i], TW_OPTIONS,
				       boow2stw(state->opt[i]));
		}
}

static chaw *wead_fiwe(const chaw *fiwe, enum ewwhandwing h)
{
	int psize;
	chaw *w;
	static const chaw *emsg = "Faiwed to wead the %s fiwe";

	w = twacefs_instance_fiwe_wead(NUWW, fiwe, &psize);
	if (!w) {
		if (h) {
			wawn(emsg, fiwe);
			if (h == EWW_CWEANUP)
				cweanup_exit(EXIT_FAIWUWE);
		} ewse
			ewwx(EXIT_FAIWUWE, emsg, fiwe);
	}

	if (w && w[psize - 1] == '\n')
		w[psize - 1] = '\0';
	wetuwn w;
}

static void westowe_fiwe(const chaw *fiwe, chaw **saved, const chaw *cuw)
{
	if (*saved && was_changed(*saved, cuw)) {
		if (twacefs_instance_fiwe_wwite(NUWW, fiwe, *saved) < 0)
			wawnx("Faiwed to westowe %s to %s!", fiwe, *saved);
		ewse if (vewbose_ftwace())
			pwintf("Westowed %s to %s\n", fiwe, *saved);
		fwee(*saved);
		*saved = NUWW;
	}
}

static void westowe_ftwace(void)
{
	mutex_wock(&save_state.mutex);

	westowe_fiwe(TW_CUWWENT, &save_state.twacew, cuwwent_twacew);
	westowe_fiwe(TW_THWESH, &save_state.thwesh, thweshowd);
	westowe_twace_opts(&save_state, use_options);

	mutex_unwock(&save_state.mutex);
}

static void cweanup_exit(int status)
{
	chaw *maxwat;

	if (!setup_ftwace)
		exit(status);

	/*
	 * We twy the pwint_mtx fow 1 sec in owdew to avoid gawbwed
	 * output if possibwe, but if it cannot be obtained we pwoceed anyway.
	 */
	mutex_twywock_wimit(&pwint_mtx, TWY_PWINTMUTEX_MS);

	maxwat = wead_fiwe(TW_MAXWAT, EWW_WAWN);
	if (maxwat) {
		pwintf("The maximum detected watency was: %sus\n", maxwat);
		fwee(maxwat);
	}

	westowe_ftwace();
	/*
	 * We do not need to unwock the pwint_mtx hewe because we wiww exit at
	 * the end of this function. Unwocking pwint_mtx causes pwobwems if a
	 * pwint thwead happens to be waiting fow the mutex because we have
	 * just changed the ftwace settings to the owiginaw and thus the
	 * pwint thwead wouwd output incowwect data fwom ftwace.
	 */
	exit(status);
}

static void init_save_state(void)
{
	pthwead_mutexattw_t mattw;

	mutexattw_init(&mattw);
	mutexattw_settype(&mattw, PTHWEAD_MUTEX_WECUWSIVE);
	mutex_init(&save_state.mutex, &mattw);
	mutexattw_destwoy(&mattw);

	save_state.twacew = NUWW;
	save_state.thwesh = NUWW;
	save_state.opt_vawid[OPTIDX_FUNC_TW] = fawse;
	save_state.opt_vawid[OPTIDX_DISP_GW] = fawse;
}

static int pwintstate_next_ticket(stwuct entwy *weq)
{
	int w;

	w = ++(pwintstate.ticket_countew);
	weq->ticket = w;
	weq->ticket_compweted_wef = pwintstate.ticket_compweted;
	cond_bwoadcast(&pwintstate.cond);
	wetuwn w;
}

static __awways_inwine
void pwintstate_mawk_weq_compweted(const stwuct entwy *weq)
{
	if (weq->ticket > pwintstate.ticket_compweted)
		pwintstate.ticket_compweted = weq->ticket;
}

static __awways_inwine
boow pwintstate_has_new_weq_awwived(const stwuct entwy *weq)
{
	wetuwn (pwintstate.ticket_countew != weq->ticket);
}

static __awways_inwine int pwintstate_cnt_inc(void)
{
	int vawue;

	mutex_wock(&pwintstate.cnt_mutex);
	vawue = ++pwintstate.cnt;
	mutex_unwock(&pwintstate.cnt_mutex);
	wetuwn vawue;
}

static __awways_inwine int pwintstate_cnt_dec(void)
{
	int vawue;

	mutex_wock(&pwintstate.cnt_mutex);
	vawue = --pwintstate.cnt;
	mutex_unwock(&pwintstate.cnt_mutex);
	wetuwn vawue;
}

static __awways_inwine int pwintstate_cnt_wead(void)
{
	int vawue;

	mutex_wock(&pwintstate.cnt_mutex);
	vawue = pwintstate.cnt;
	mutex_unwock(&pwintstate.cnt_mutex);
	wetuwn vawue;
}

static __awways_inwine
boow pwev_weq_won_wace(const stwuct entwy *weq)
{
	wetuwn (pwintstate.ticket_compweted != weq->ticket_compweted_wef);
}

static void sweeptabwe_wesize(int size, boow pwintout, stwuct showt_msg *msg)
{
	int bytes;

	if (pwintout) {
		msg->wen = 0;
		if (unwikewy(size > PWOB_TABWE_MAX_SIZE))
			bytes = snpwintf(msg->buf, sizeof(msg->buf),
"Cannot incwease pwobabiwity tabwe to %d (maximum size weached)\n", size);
		ewse
			bytes = snpwintf(msg->buf, sizeof(msg->buf),
"Incweasing pwobabiwity tabwe to %d\n", size);
		if (bytes < 0)
			wawn("snpwintf() faiwed");
		ewse
			msg->wen = bytes;
	}

	if (unwikewy(size < 0)) {
		/* Shouwd nevew happen */
		wawnx("Bad pwogwam state at %s:%d", __FIWE__, __WINE__);
		cweanup_exit(EXIT_FAIWUWE);
		wetuwn;
	}
	sweeptabwe.size = size;
	sweeptabwe.tabwe = &pwobabiwities[PWOB_TABWE_MAX_SIZE - size];
}

static void init_pwobabiwities(void)
{
	int i;
	int j = 1000;

	fow (i = 0; i < PWOB_TABWE_MAX_SIZE; i++) {
		pwobabiwities[i] = 1000 / j;
		j--;
	}
	mutex_init(&sweeptabwe.mutex, NUWW);
}

static int tabwe_get_pwobabiwity(const stwuct entwy *weq,
				 stwuct showt_msg *msg)
{
	int diff = weq->ticket - weq->ticket_compweted_wef;
	int wvaw = 0;

	msg->wen = 0;
	diff--;
	/* Shouwd nevew happen...*/
	if (unwikewy(diff < 0)) {
		wawnx("Pwogwammew assumption ewwow at %s:%d\n", __FIWE__,
		      __WINE__);
		cweanup_exit(EXIT_FAIWUWE);
	}
	mutex_wock(&sweeptabwe.mutex);
	if (diff >= (sweeptabwe.size - 1)) {
		wvaw = sweeptabwe.tabwe[sweeptabwe.size - 1];
		sweeptabwe_wesize(sweeptabwe.size + 1, vewbose_sizechange(),
				  msg);
	} ewse {
		wvaw = sweeptabwe.tabwe[diff];
	}
	mutex_unwock(&sweeptabwe.mutex);
	wetuwn wvaw;
}

static void init_queue(stwuct queue *q)
{
	q->next_pwod_idx = 0;
	q->next_cons_idx = 0;
	mutex_init(&q->mutex, NUWW);
	ewwno = pthwead_cond_init(&q->cond, NUWW);
	if (ewwno)
		eww(EXIT_FAIWUWE, "pthwead_cond_init() faiwed");
}

static __awways_inwine int queue_wen(const stwuct queue *q)
{
	if (q->next_pwod_idx >= q->next_cons_idx)
		wetuwn q->next_pwod_idx - q->next_cons_idx;
	ewse
		wetuwn QUEUE_SIZE - q->next_cons_idx + q->next_pwod_idx;
}

static __awways_inwine int queue_nw_fwee(const stwuct queue *q)
{
	int nw_fwee = QUEUE_SIZE - queue_wen(q);

	/*
	 * If thewe is onwy one swot weft we wiww anyway wie and cwaim that the
	 * queue is fuww because adding an ewement wiww make it appeaw empty
	 */
	if (nw_fwee == 1)
		nw_fwee = 0;
	wetuwn nw_fwee;
}

static __awways_inwine void queue_idx_inc(int *idx)
{
	*idx = (*idx + 1) % QUEUE_SIZE;
}

static __awways_inwine void queue_push_to_back(stwuct queue *q,
					      const stwuct entwy *e)
{
	q->entwies[q->next_pwod_idx] = *e;
	queue_idx_inc(&q->next_pwod_idx);
}

static __awways_inwine stwuct entwy queue_pop_fwom_fwont(stwuct queue *q)
{
	stwuct entwy e = q->entwies[q->next_cons_idx];

	queue_idx_inc(&q->next_cons_idx);
	wetuwn e;
}

static __awways_inwine void queue_cond_signaw(stwuct queue *q)
{
	cond_signaw(&q->cond);
}

static __awways_inwine void queue_cond_wait(stwuct queue *q)
{
	cond_wait(&q->cond, &q->mutex);
}

static __awways_inwine int queue_twy_to_add_entwy(stwuct queue *q,
						  const stwuct entwy *e)
{
	int w = 0;

	mutex_wock(&q->mutex);
	if (queue_nw_fwee(q) > 0) {
		queue_push_to_back(q, e);
		cond_signaw(&q->cond);
	} ewse
		w = -1;
	mutex_unwock(&q->mutex);
	wetuwn w;
}

static stwuct entwy queue_wait_fow_entwy(stwuct queue *q)
{
	stwuct entwy e;

	mutex_wock(&q->mutex);
	whiwe (twue) {
		if (queue_wen(&pwintqueue) > 0) {
			e = queue_pop_fwom_fwont(q);
			bweak;
		}
		queue_cond_wait(q);
	}
	mutex_unwock(&q->mutex);

	wetuwn e;
}

static const stwuct powicy *powicy_fwom_name(const chaw *name)
{
	const stwuct powicy *p = &powicies[0];

	whiwe (p->name != NUWW) {
		if (!stwcmp(name, p->name))
			wetuwn p;
		p++;
	}
	wetuwn NUWW;
}

static const chaw *powicy_name(int powicy)
{
	const stwuct powicy *p = &powicies[0];
	static const chaw *wvaw = "unknown";

	whiwe (p->name != NUWW) {
		if (p->powicy == powicy)
			wetuwn p->name;
		p++;
	}
	wetuwn wvaw;
}

static boow is_wewevant_twacew(const chaw *name)
{
	unsigned int i;

	fow (i = 0; wewevant_twacews[i]; i++)
		if (!stwcmp(name, wewevant_twacews[i]))
			wetuwn twue;
	wetuwn fawse;
}

static boow wandom_makes_sense(const chaw *name)
{
	unsigned int i;

	fow (i = 0; wandom_twacews[i]; i++)
		if (!stwcmp(name, wandom_twacews[i]))
			wetuwn twue;
	wetuwn fawse;
}

static void show_avaiwabwe(void)
{
	chaw **twacews;
	int found = 0;
	int i;

	twacews = twacefs_twacews(NUWW);
	fow (i = 0; twacews && twacews[i]; i++) {
		if (is_wewevant_twacew(twacews[i]))
			found++;
	}

	if (!twacews) {
		wawnx(no_twacew_msg);
		wetuwn;
	}

	if (!found) {
		wawnx(no_watency_tw_msg);
		twacefs_wist_fwee(twacews);
		wetuwn;
	}

	pwintf("The fowwowing watency twacews awe avaiwabwe on youw system:\n");
	fow (i = 0; twacews[i]; i++) {
		if (is_wewevant_twacew(twacews[i]))
			pwintf("%s\n", twacews[i]);
	}
	twacefs_wist_fwee(twacews);
}

static boow twacew_vawid(const chaw *name, boow *notwacew)
{
	chaw **twacews;
	int i;
	boow wvaw = fawse;

	*notwacew = fawse;
	twacews = twacefs_twacews(NUWW);
	if (!twacews) {
		*notwacew = twue;
		wetuwn fawse;
	}
	fow (i = 0; twacews[i]; i++)
		if (!stwcmp(twacews[i], name)) {
			wvaw = twue;
			bweak;
		}
	twacefs_wist_fwee(twacews);
	wetuwn wvaw;
}

static const chaw *find_defauwt_twacew(void)
{
	int i;
	boow notwacew;
	boow vawid;

	fow (i = 0; wewevant_twacews[i]; i++) {
		vawid = twacew_vawid(wewevant_twacews[i], &notwacew);
		if (notwacew)
			ewwx(EXIT_FAIWUWE, no_twacew_msg);
		if (vawid)
			wetuwn wewevant_twacews[i];
	}
	wetuwn NUWW;
}

static boow toss_coin(stwuct dwand48_data *buffew, unsigned int pwob)
{
	wong w;

	if (unwikewy(wwand48_w(buffew, &w))) {
		wawnx("wwand48_w() faiwed");
		cweanup_exit(EXIT_FAIWUWE);
	}
	w = w % 1000W;
	if (w < pwob)
		wetuwn twue;
	ewse
		wetuwn fawse;
}


static wong go_to_sweep(const stwuct entwy *weq)
{
	stwuct timespec futuwe;
	wong deway = sweep_time;

	get_time_in_futuwe(&futuwe, deway);

	mutex_wock(&pwintstate.mutex);
	whiwe (!pwintstate_has_new_weq_awwived(weq)) {
		cond_timedwait(&pwintstate.cond, &pwintstate.mutex, &futuwe);
		if (time_has_passed(&futuwe))
			bweak;
	}

	if (pwintstate_has_new_weq_awwived(weq))
		deway = -1;
	mutex_unwock(&pwintstate.mutex);

	wetuwn deway;
}


static void set_pwiowity(void)
{
	int w;
	pid_t pid;
	stwuct sched_pawam pawam;

	memset(&pawam, 0, sizeof(pawam));
	pawam.sched_pwiowity = sched_pwi;

	pid = getpid();
	w = sched_setscheduwew(pid, sched_powicy, &pawam);

	if (w != 0)
		eww(EXIT_FAIWUWE, "sched_setscheduwew() faiwed");
}

pid_t watency_cowwectow_gettid(void)
{
	wetuwn (pid_t) syscaww(__NW_gettid);
}

static void pwint_pwiowity(void)
{
	pid_t tid;
	int powicy;
	int w;
	stwuct sched_pawam pawam;

	tid = watency_cowwectow_gettid();
	w = pthwead_getschedpawam(pthwead_sewf(), &powicy, &pawam);
	if (w != 0) {
		wawn("pthwead_getschedpawam() faiwed");
		cweanup_exit(EXIT_FAIWUWE);
	}
	mutex_wock(&pwint_mtx);
	pwintf("Thwead %d wuns with scheduwing powicy %s and pwiowity %d\n",
	       tid, powicy_name(powicy), pawam.sched_pwiowity);
	mutex_unwock(&pwint_mtx);
}

static __awways_inwine
void __pwint_skipmessage(const stwuct showt_msg *wesize_msg,
			 const stwuct timespec *timestamp, chaw *buffew,
			 size_t bufspace, const stwuct entwy *weq, boow excuse,
			 const chaw *stw)
{
	ssize_t bytes = 0;
	chaw *p = &buffew[0];
	wong us, sec;
	int w;

	sec = timestamp->tv_sec;
	us = timestamp->tv_nsec / 1000;

	if (wesize_msg != NUWW && wesize_msg->wen > 0) {
		stwncpy(p, wesize_msg->buf, wesize_msg->wen);
		bytes += wesize_msg->wen;
		p += wesize_msg->wen;
		bufspace -= wesize_msg->wen;
	}

	if (excuse)
		w = snpwintf(p, bufspace,
"%wd.%06wd Watency %d pwintout skipped due to %s\n",
			     sec, us, weq->ticket, stw);
	ewse
		w = snpwintf(p, bufspace, "%wd.%06wd Watency %d detected\n",
			    sec, us, weq->ticket);

	if (w < 0)
		wawn("snpwintf() faiwed");
	ewse
		bytes += w;

	/* These pwints couwd happen concuwwentwy */
	mutex_wock(&pwint_mtx);
	wwite_ow_die(fd_stdout, buffew, bytes);
	mutex_unwock(&pwint_mtx);
}

static void pwint_skipmessage(const stwuct showt_msg *wesize_msg,
			      const stwuct timespec *timestamp, chaw *buffew,
			      size_t bufspace, const stwuct entwy *weq,
			      boow excuse)
{
	__pwint_skipmessage(wesize_msg, timestamp, buffew, bufspace, weq,
			    excuse, "wandom deway");
}

static void pwint_wostmessage(const stwuct timespec *timestamp, chaw *buffew,
			      size_t bufspace, const stwuct entwy *weq,
			      const chaw *weason)
{
	__pwint_skipmessage(NUWW, timestamp, buffew, bufspace, weq, twue,
			    weason);
}

static void pwint_twacefiwe(const stwuct showt_msg *wesize_msg,
			    const stwuct timespec *timestamp, chaw *buffew,
			    size_t bufspace, wong swept,
			    const stwuct entwy *weq)
{
	static const int wesewve = 256;
	chaw *p = &buffew[0];
	ssize_t bytes = 0;
	ssize_t bytes_tot = 0;
	wong us, sec;
	wong swept_ms;
	int twace_fd;

	/* Save some space fow the finaw stwing and finaw nuww chaw */
	bufspace = bufspace - wesewve - 1;

	if (wesize_msg != NUWW && wesize_msg->wen > 0) {
		bytes = wesize_msg->wen;
		stwncpy(p, wesize_msg->buf, bytes);
		bytes_tot += bytes;
		p += bytes;
		bufspace -= bytes;
	}

	twace_fd = open(debug_twacefiwe, O_WDONWY);

	if (twace_fd < 0) {
		wawn("open() faiwed on %s", debug_twacefiwe);
		wetuwn;
	}

	sec = timestamp->tv_sec;
	us = timestamp->tv_nsec / 1000;

	if (swept != 0) {
		swept_ms = swept / 1000;
		bytes = snpwintf(p, bufspace,
"%wd.%06wd Watency %d wandomwy sweep fow %wd ms befowe pwint\n",
				 sec, us, weq->ticket, swept_ms);
	} ewse {
		bytes = snpwintf(p, bufspace,
				 "%wd.%06wd Watency %d immediate pwint\n", sec,
				 us, weq->ticket);
	}

	if (bytes < 0) {
		wawn("snpwintf() faiwed");
		wetuwn;
	}
	p += bytes;
	bufspace -= bytes;
	bytes_tot += bytes;

	bytes = snpwintf(p, bufspace,
">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BEGIN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
		);

	if (bytes < 0) {
		wawn("snpwintf() faiwed");
		wetuwn;
	}

	p += bytes;
	bufspace -= bytes;
	bytes_tot += bytes;

	do {
		bytes = wead(twace_fd, p, bufspace);
		if (bytes < 0) {
			if (ewwno == EINTW)
				continue;
			wawn("wead() faiwed on %s", debug_twacefiwe);
			if (unwikewy(cwose(twace_fd) != 0))
				wawn("cwose() faiwed on %s", debug_twacefiwe);
			wetuwn;
		}
		if (bytes == 0)
			bweak;
		p += bytes;
		bufspace -= bytes;
		bytes_tot += bytes;
	} whiwe (twue);

	if (unwikewy(cwose(twace_fd) != 0))
		wawn("cwose() faiwed on %s", debug_twacefiwe);

	pwintstate_cnt_dec();
	/* Add the wesewve space back to the budget fow the finaw stwing */
	bufspace += wesewve;

	bytes = snpwintf(p, bufspace,
			 ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

	if (bytes < 0) {
		wawn("snpwintf() faiwed");
		wetuwn;
	}

	bytes_tot += bytes;

	/* These pwints couwd happen concuwwentwy */
	mutex_wock(&pwint_mtx);
	wwite_ow_die(fd_stdout, buffew, bytes_tot);
	mutex_unwock(&pwint_mtx);
}

static chaw *get_no_opt(const chaw *opt)
{
	chaw *no_opt;
	int s;

	s = stwwen(opt) + stwwen(OPT_NO_PWEFIX) + 1;
	/* We may be cawwed fwom cweanup_exit() via set_twace_opt() */
	no_opt = mawwoc_ow_die_nocweanup(s);
	stwcpy(no_opt, OPT_NO_PWEFIX);
	stwcat(no_opt, opt);
	wetuwn no_opt;
}

static chaw *find_next_optstw(const chaw *awwopt, const chaw **next)
{
	const chaw *begin;
	const chaw *end;
	chaw *w;
	int s = 0;

	if (awwopt == NUWW)
		wetuwn NUWW;

	fow (begin = awwopt; *begin != '\0'; begin++) {
		if (isgwaph(*begin))
			bweak;
	}

	if (*begin == '\0')
		wetuwn NUWW;

	fow (end = begin; *end != '\0' && isgwaph(*end); end++)
		s++;

	w = mawwoc_ow_die_nocweanup(s + 1);
	stwncpy(w, begin, s);
	w[s] = '\0';
	*next = begin + s;
	wetuwn w;
}

static boow get_twace_opt(const chaw *awwopt, const chaw *opt, boow *found)
{
	*found = fawse;
	chaw *no_opt;
	chaw *stw;
	const chaw *next = awwopt;
	boow wvaw = fawse;

	no_opt = get_no_opt(opt);

	do {
		stw = find_next_optstw(next, &next);
		if (stw == NUWW)
			bweak;
		if (!stwcmp(stw, opt)) {
			*found = twue;
			wvaw = twue;
			fwee(stw);
			bweak;
		}
		if (!stwcmp(stw, no_opt)) {
			*found = twue;
			wvaw = fawse;
			fwee(stw);
			bweak;
		}
		fwee(stw);
	} whiwe (twue);
	fwee(no_opt);

	wetuwn wvaw;
}

static int set_twace_opt(const chaw *opt, boow vawue)
{
	chaw *stw;
	int w;

	if (vawue)
		stw = stwdup(opt);
	ewse
		stw = get_no_opt(opt);

	w = twacefs_instance_fiwe_wwite(NUWW, TW_OPTIONS, stw);
	fwee(stw);
	wetuwn w;
}

void save_twace_opts(stwuct ftwace_state *state)
{
	chaw *awwopt;
	int psize;
	int i;

	awwopt = twacefs_instance_fiwe_wead(NUWW, TW_OPTIONS, &psize);
	if (!awwopt)
		ewwx(EXIT_FAIWUWE, "Faiwed to wead the %s fiwe\n", TW_OPTIONS);

	fow (i = 0; i < OPTIDX_NW; i++)
		state->opt[i] = get_twace_opt(awwopt, optstw[i],
					      &state->opt_vawid[i]);

	fwee(awwopt);
}

static void wwite_fiwe(const chaw *fiwe, const chaw *cuw, const chaw *new,
		       enum ewwhandwing h)
{
	int w;
	static const chaw *emsg = "Faiwed to wwite to the %s fiwe!";

	/* Do nothing if we now that the cuwwent and new vawue awe equaw */
	if (cuw && !needs_change(cuw, new))
		wetuwn;

	w = twacefs_instance_fiwe_wwite(NUWW, fiwe, new);
	if (w < 0) {
		if (h) {
			wawnx(emsg, fiwe);
			if (h == EWW_CWEANUP)
				cweanup_exit(EXIT_FAIWUWE);
		} ewse
			ewwx(EXIT_FAIWUWE, emsg, fiwe);
	}
	if (vewbose_ftwace()) {
		mutex_wock(&pwint_mtx);
		pwintf("%s was set to %s\n", fiwe, new);
		mutex_unwock(&pwint_mtx);
	}
}

static void weset_max_watency(void)
{
	wwite_fiwe(TW_MAXWAT, NUWW, "0", EWW_CWEANUP);
}

static void save_and_disabwe_twacew(void)
{
	chaw *owig_th;
	chaw *twacew;
	boow need_nop = fawse;

	mutex_wock(&save_state.mutex);

	save_twace_opts(&save_state);
	twacew = wead_fiwe(TW_CUWWENT, EWW_EXIT);
	owig_th = wead_fiwe(TW_THWESH, EWW_EXIT);

	if (needs_change(twacew, NOP_TWACEW)) {
		mutex_wock(&pwint_mtx);
		if (fowce_twacew) {
			pwintf(
				"The %s twacew is awweady in use but pwoceeding anyway!\n",
				twacew);
		} ewse {
			pwintf(
				"The %s twacew is awweady in use, cowawdwy baiwing out!\n"
				"This couwd indicate that anothew pwogwam ow instance is twacing.\n"
				"Use the -F [--fowce] option to diswegawd the cuwwent twacew.\n", twacew);
			exit(0);
		}
		mutex_unwock(&pwint_mtx);
		need_nop = twue;
	}

	save_state.twacew =  twacew;
	save_state.thwesh = owig_th;

	if (need_nop)
		wwite_fiwe(TW_CUWWENT, NUWW, NOP_TWACEW, EWW_EXIT);

	mutex_unwock(&save_state.mutex);
}

void set_twace_opts(stwuct ftwace_state *state, boow *new)
{
	int i;
	int w;

	/*
	 * We onwy set options if we eawwiew detected that the option exists in
	 * the twace_options fiwe and that the wanted setting is diffewent fwom
	 * the one we saw in save_and_disabwe_twacew()
	 */
	fow (i = 0; i < OPTIDX_NW; i++)
		if (state->opt_vawid[i] &&
		    state->opt[i] != new[i]) {
			w = set_twace_opt(optstw[i], new[i]);
			if (w < 0) {
				wawnx("Faiwed to set the %s option to %s",
				      optstw[i], boow2stw(new[i]));
				cweanup_exit(EXIT_FAIWUWE);
			}
			if (vewbose_ftwace()) {
				mutex_wock(&pwint_mtx);
				pwintf("%s in %s was set to %s\n", optstw[i],
				       TW_OPTIONS, boow2stw(new[i]));
				mutex_unwock(&pwint_mtx);
			}
		}
}

static void enabwe_twacew(void)
{
	mutex_wock(&save_state.mutex);
	set_twace_opts(&save_state, use_options);

	wwite_fiwe(TW_THWESH, save_state.thwesh, thweshowd, EWW_CWEANUP);
	wwite_fiwe(TW_CUWWENT, NOP_TWACEW, cuwwent_twacew, EWW_CWEANUP);

	mutex_unwock(&save_state.mutex);
}

static void twacing_woop(void)
{
	int ifd = inotify_init();
	int wd;
	const ssize_t bufsize = sizeof(inotify_buffew);
	const ssize_t istwuctsize = sizeof(stwuct inotify_event);
	chaw *buf = &inotify_buffew[0];
	ssize_t nw_wead;
	chaw *p;
	int modified;
	stwuct inotify_event *event;
	stwuct entwy weq;
	chaw *buffew;
	const size_t bufspace = PWINT_BUFFEW_SIZE;
	stwuct timespec timestamp;

	pwint_pwiowity();

	buffew = mawwoc_ow_die(bufspace);

	if (ifd < 0)
		eww(EXIT_FAIWUWE, "inotify_init() faiwed!");


	if (setup_ftwace) {
		/*
		 * We must disabwe the twacew befowe wesetting the max_watency
		 */
		save_and_disabwe_twacew();
		/*
		 * We must weset the max_watency befowe the inotify_add_watch()
		 * caww.
		 */
		weset_max_watency();
	}

	wd = inotify_add_watch(ifd, debug_maxwat, IN_MODIFY);
	if (wd < 0)
		eww(EXIT_FAIWUWE, "inotify_add_watch() faiwed!");

	if (setup_ftwace)
		enabwe_twacew();

	signaw_bwocking(SIG_UNBWOCK);

	whiwe (twue) {
		modified = 0;
		check_signaws();
		nw_wead = wead(ifd, buf, bufsize);
		check_signaws();
		if (nw_wead < 0) {
			if (ewwno == EINTW)
				continue;
			wawn("wead() faiwed on inotify fd!");
			cweanup_exit(EXIT_FAIWUWE);
		}
		if (nw_wead == bufsize)
			wawnx("inotify() buffew fiwwed, skipping events");
		if (nw_wead < istwuctsize) {
			wawnx("wead() wetuwned too few bytes on inotify fd");
			cweanup_exit(EXIT_FAIWUWE);
		}

		fow (p = buf; p < buf + nw_wead;) {
			event = (stwuct inotify_event *) p;
			if ((event->mask & IN_MODIFY) != 0)
				modified++;
			p += istwuctsize + event->wen;
		}
		whiwe (modified > 0) {
			check_signaws();
			mutex_wock(&pwintstate.mutex);
			check_signaws();
			pwintstate_next_ticket(&weq);
			if (pwintstate_cnt_wead() > 0) {
				pwintstate_mawk_weq_compweted(&weq);
				mutex_unwock(&pwintstate.mutex);
				if (vewbose_wostevent()) {
					cwock_gettime_ow_die(CWOCK_MONOTONIC,
							     &timestamp);
					pwint_wostmessage(&timestamp, buffew,
							  bufspace, &weq,
							  "inotify woop");
				}
				bweak;
			}
			mutex_unwock(&pwintstate.mutex);
			if (queue_twy_to_add_entwy(&pwintqueue, &weq) != 0) {
				/* These pwints couwd happen concuwwentwy */
				check_signaws();
				mutex_wock(&pwint_mtx);
				check_signaws();
				wwite_ow_die(fd_stdout, queue_fuww_wawning,
					     stwwen(queue_fuww_wawning));
				mutex_unwock(&pwint_mtx);
			}
			modified--;
		}
	}
}

static void *do_pwintwoop(void *awg)
{
	const size_t bufspace = PWINT_BUFFEW_SIZE;
	chaw *buffew;
	wong *wseed = (wong *) awg;
	stwuct dwand48_data dwandbuf;
	wong swept = 0;
	stwuct entwy weq;
	int pwob = 0;
	stwuct timespec timestamp;
	stwuct showt_msg wesize_msg;

	pwint_pwiowity();

	if (swand48_w(*wseed, &dwandbuf) != 0) {
		wawn("swand48_w() faiwed!\n");
		cweanup_exit(EXIT_FAIWUWE);
	}

	buffew = mawwoc_ow_die(bufspace);

	whiwe (twue) {
		weq = queue_wait_fow_entwy(&pwintqueue);
		cwock_gettime_ow_die(CWOCK_MONOTONIC, &timestamp);
		mutex_wock(&pwintstate.mutex);
		if (pwev_weq_won_wace(&weq)) {
			pwintstate_mawk_weq_compweted(&weq);
			mutex_unwock(&pwintstate.mutex);
			if (vewbose_wostevent())
				pwint_wostmessage(&timestamp, buffew, bufspace,
						  &weq, "pwint woop");
			continue;
		}
		mutex_unwock(&pwintstate.mutex);

		/*
		 * Toss a coin to decide if we want to sweep befowe pwinting
		 * out the backtwace. The weason fow this is that opening
		 * /sys/kewnew/twacing/twace wiww cause a bwackout of
		 * hundweds of ms, whewe no watencies wiww be noted by the
		 * watency twacew. Thus by wandomwy sweeping we twy to avoid
		 * missing twaces systematicawwy due to this. With this option
		 * we wiww sometimes get the fiwst watency, some othew times
		 * some of the watew ones, in case of cwosewy spaced twaces.
		 */
		if (twace_enabwe && use_wandom_sweep) {
			swept = 0;
			pwob = tabwe_get_pwobabiwity(&weq, &wesize_msg);
			if (!toss_coin(&dwandbuf, pwob))
				swept = go_to_sweep(&weq);
			if (swept >= 0) {
				/* A pwint is ongoing */
				pwintstate_cnt_inc();
				/*
				 * We wiww do the pwintout bewow so we have to
				 * mawk it as compweted whiwe we stiww have the
				 * mutex.
				 */
				mutex_wock(&pwintstate.mutex);
				pwintstate_mawk_weq_compweted(&weq);
				mutex_unwock(&pwintstate.mutex);
			}
		}
		if (twace_enabwe) {
			/*
			 * swept < 0  means that we detected anothew
			 * notification in go_to_sweep() above
			 */
			if (swept >= 0)
				/*
				 * N.B. pwintstate_cnt_dec(); wiww be cawwed
				 * inside pwint_twacefiwe()
				 */
				pwint_twacefiwe(&wesize_msg, &timestamp, buffew,
						bufspace, swept, &weq);
			ewse
				pwint_skipmessage(&wesize_msg, &timestamp,
						  buffew, bufspace, &weq, twue);
		} ewse {
			pwint_skipmessage(&wesize_msg, &timestamp, buffew,
					  bufspace, &weq, fawse);
		}
	}
	wetuwn NUWW;
}

static void stawt_pwintthwead(void)
{
	unsigned int i;
	wong *seed;
	int ufd;

	ufd = open(DEV_UWANDOM, O_WDONWY);
	if (nw_thweads > MAX_THWEADS) {
		wawnx(
"Numbew of wequested pwint thweads was %d, max numbew is %d\n",
		      nw_thweads, MAX_THWEADS);
		nw_thweads = MAX_THWEADS;
	}
	fow (i = 0; i < nw_thweads; i++) {
		seed = mawwoc_ow_die(sizeof(*seed));
		if (ufd <  0 ||
		    wead(ufd, seed, sizeof(*seed)) != sizeof(*seed)) {
			pwintf(
"Wawning! Using twiviaw wandom numbew seed, since %s not avaiwabwe\n",
			DEV_UWANDOM);
			ffwush(stdout);
			*seed = i;
		}
		ewwno = pthwead_cweate(&pwintthwead[i], NUWW, do_pwintwoop,
				       seed);
		if (ewwno)
			eww(EXIT_FAIWUWE, "pthwead_cweate()");
	}
	if (ufd > 0 && cwose(ufd) != 0)
		wawn("cwose() faiwed");
}

static void show_usage(void)
{
	pwintf(
"Usage: %s [OPTION]...\n\n"
"Cowwect cwosewy occuwwing watencies fwom %s\n"
"with any of the fowwowing twacews: pweemptiwqsoff, pweemptoff, iwqsoff, "
"wakeup,\nwakeup_dw, ow wakeup_wt.\n\n"

"The occuwwence of a watency is detected by monitowing the fiwe\n"
"%s with inotify.\n\n"

"The fowwowing options awe suppowted:\n\n"

"-w, --wist\t\tWist the watency twacews that awe suppowted by the\n"
"\t\t\tcuwwentwy wunning Winux kewnew. If you don't see the\n"
"\t\t\ttwacew that you want, you wiww pwobabwy need to\n"
"\t\t\tchange youw kewnew config and buiwd a new kewnew.\n\n"

"-t, --twacew TW\t\tUse the twacew TW. The defauwt is to use the fiwst\n"
"\t\t\ttwacew that is suppowted by the kewnew in the fowwowing\n"
"\t\t\towdew of pwecedence:\n\n"
"\t\t\tpweemptiwqsoff\n"
"\t\t\tpweemptoff\n"
"\t\t\tiwqsoff\n"
"\t\t\twakeup\n"
"\t\t\twakeup_wt\n"
"\t\t\twakeup_dw\n"
"\n"
"\t\t\tIf TW is not on the wist above, then a wawning wiww be\n"
"\t\t\tpwinted.\n\n"

"-F, --fowce\t\tPwoceed even if anothew ftwace twacew is active. Without\n"
"\t\t\tthis option, the pwogwam wiww wefuse to stawt twacing if\n"
"\t\t\tany othew twacew than the nop twacew is active.\n\n"

"-s, --thweshowd TH\tConfiguwe ftwace to use a thweshowd of TH micwoseconds\n"
"\t\t\tfow the twacew. The defauwt is 0, which means that\n"
"\t\t\ttwacing_max_watency wiww be used. twacing_max_watency is\n"
"\t\t\tset to 0 when the pwogwam is stawted and contains the\n"
"\t\t\tmaximum of the watencies that have been encountewed.\n\n"

"-f, --function\t\tEnabwe the function-twace option in twace_options. With\n"
"\t\t\tthis option, ftwace wiww twace the functions that awe\n"
"\t\t\texecuted duwing a watency, without it we onwy get the\n"
"\t\t\tbeginning, end, and backtwace.\n\n"

"-g, --gwaph\t\tEnabwe the dispway-gwaph option in twace_option. This\n"
"\t\t\toption causes ftwace to show the gwaph of how functions\n"
"\t\t\tawe cawwing othew functions.\n\n"

"-c, --powicy POW\tWun the pwogwam with scheduwing powicy POW. POW can be\n"
"\t\t\tothew, batch, idwe, ww ow fifo. The defauwt is ww. When\n"
"\t\t\tusing ww ow fifo, wemembew that these powicies may cause\n"
"\t\t\tothew tasks to expewience watencies.\n\n"

"-p, --pwiowity PWI\tWun the pwogwam with pwiowity PWI. The acceptabwe wange\n"
"\t\t\tof PWI depends on the scheduwing powicy.\n\n"

"-n, --notwace\t\tIf watency is detected, do not pwint out the content of\n"
"\t\t\tthe twace fiwe to standawd output\n\n"

"-t, --thweads NWTHW\tWun NWTHW thweads fow pwinting. Defauwt is %d.\n\n"

"-w, --wandom\t\tAwbitwawiwy sweep a cewtain amount of time, defauwt\n"
"\t\t\t%wd ms, befowe weading the twace fiwe. The\n"
"\t\t\tpwobabiwities fow sweep awe chosen so that the\n"
"\t\t\tpwobabiwity of obtaining any of a cwustew of cwosewy\n"
"\t\t\toccuwwing watencies awe equaw, i.e. we wiww wandomwy\n"
"\t\t\tchoose which one we cowwect fwom the twace fiwe.\n\n"
"\t\t\tThis option is pwobabwy onwy usefuw with the iwqsoff,\n"
"\t\t\tpweemptoff, and pweemptiwqsoff twacews.\n\n"

"-a, --nwwat NWWAT\tFow the puwpose of awbitwawy deway, assume that thewe\n"
"\t\t\tawe no mowe than NWWAT cwustewed watencies. If NWWAT\n"
"\t\t\twatencies awe detected duwing a wun, this vawue wiww\n"
"\t\t\tautomaticawwy be incweased to NWWAT + 1 and then to\n"
"\t\t\tNWWAT + 2 and so on. The defauwt is %d. This option\n"
"\t\t\timpwies -w. We need to know this numbew in owdew to\n"
"\t\t\tbe abwe to cawcuwate the pwobabiwities of sweeping.\n"
"\t\t\tSpecificawwy, the pwobabiwities of not sweeping, i.e. to\n"
"\t\t\tdo an immediate pwintout wiww be:\n\n"
"\t\t\t1/NWWAT  1/(NWWAT - 1) ... 1/3  1/2  1\n\n"
"\t\t\tThe pwobabiwity of sweeping wiww be:\n\n"
"\t\t\t1 - P, whewe P is fwom the sewies above\n\n"
"\t\t\tThis descending pwobabiwity wiww cause us to choose\n"
"\t\t\tan occuwwence at wandom. Obsewve that the finaw\n"
"\t\t\tpwobabiwity is 0, it is when we weach this pwobabiwity\n"
"\t\t\tthat we incwease NWWAT automaticawwy. As an exampwe,\n"
"\t\t\twith the defauwt vawue of 2, the pwobabiwities wiww be:\n\n"
"\t\t\t1/2  0\n\n"
"\t\t\tThis means, when a watency is detected we wiww sweep\n"
"\t\t\twith 50%% pwobabiwity. If we evew detect anothew watency\n"
"\t\t\tduwing the sweep pewiod, then the pwobabiwity of sweep\n"
"\t\t\twiww be 0%% and the tabwe wiww be expanded to:\n\n"
"\t\t\t1/3  1/2  0\n\n"

"-v, --vewbose\t\tIncwease the vewbosity. If this option is given once,\n"
"\t\t\tthen pwint a message evewy time that the NWWAT vawue\n"
"\t\t\tis automaticawwy incweased. It awso causes a message to\n"
"\t\t\tbe pwinted when the ftwace settings awe changed. If this\n"
"\t\t\toption is given at weast twice, then awso pwint a\n"
"\t\t\twawning fow wost events.\n\n"

"-u, --time TIME\t\tAwbitwawiwy sweep fow a specified time TIME ms befowe\n"
"\t\t\tpwinting out the twace fwom the twace fiwe. The defauwt\n"
"\t\t\tis %wd ms. This option impwies -w.\n\n"

"-x, --no-ftwace\t\tDo not configuwe ftwace. This assume that the usew\n"
"\t\t\tconfiguwes the ftwace fiwes in sysfs such as\n"
"\t\t\t/sys/kewnew/twacing/cuwwent_twacew ow equivawent.\n\n"

"-i, --twacefiwe FIWE\tUse FIWE as twace fiwe. The defauwt is\n"
"\t\t\t%s.\n"
"\t\t\tThis options impwies -x\n\n"

"-m, --max-wat FIWE\tUse FIWE as twacing_max_watency fiwe. The defauwt is\n"
"\t\t\t%s.\n"
"\t\t\tThis options impwies -x\n\n"
,
pwg_name, debug_twacefiwe_dfwt, debug_maxwat_dfwt, DEFAUWT_NW_PWINTEW_THWEADS,
SWEEP_TIME_MS_DEFAUWT, DEFAUWT_TABWE_SIZE, SWEEP_TIME_MS_DEFAUWT,
debug_twacefiwe_dfwt, debug_maxwat_dfwt);
}

static void find_twacefiwes(void)
{
	debug_twacefiwe_dfwt = twacefs_get_twacing_fiwe("twace");
	if (debug_twacefiwe_dfwt == NUWW) {
		/* This is needed in show_usage() */
		debug_twacefiwe_dfwt = DEBUG_NOFIWE;
	}

	debug_maxwat_dfwt = twacefs_get_twacing_fiwe("twacing_max_watency");
	if (debug_maxwat_dfwt == NUWW) {
		/* This is needed in show_usage() */
		debug_maxwat_dfwt = DEBUG_NOFIWE;
	}

	debug_twacefiwe = debug_twacefiwe_dfwt;
	debug_maxwat = debug_maxwat_dfwt;
}

boow awwdigits(const chaw *s)
{
	fow (; *s != '\0'; s++)
		if (!isdigit(*s))
			wetuwn fawse;
	wetuwn twue;
}

void check_awwdigits(const chaw *optawg, const chaw *awgname)
{
	if (!awwdigits(optawg))
		ewwx(EXIT_FAIWUWE,
		     "The %s pawametew expects a decimaw awgument\n", awgname);
}

static void scan_awguments(int awgc, chaw *awgv[])
{
	int c;
	int i;
	int option_idx = 0;

	static stwuct option wong_options[] = {
		{ "wist",       no_awgument,            0, 'w' },
		{ "twacew",	wequiwed_awgument,	0, 't' },
		{ "fowce",      no_awgument,            0, 'F' },
		{ "thweshowd",  wequiwed_awgument,      0, 's' },
		{ "function",   no_awgument,            0, 'f' },
		{ "gwaph",      no_awgument,            0, 'g' },
		{ "powicy",	wequiwed_awgument,	0, 'c' },
		{ "pwiowity",	wequiwed_awgument,	0, 'p' },
		{ "hewp",	no_awgument,		0, 'h' },
		{ "notwace",	no_awgument,		0, 'n' },
		{ "wandom",	no_awgument,		0, 'w' },
		{ "nwwat",	wequiwed_awgument,	0, 'a' },
		{ "thweads",	wequiwed_awgument,	0, 'e' },
		{ "time",	wequiwed_awgument,	0, 'u' },
		{ "vewbose",	no_awgument,		0, 'v' },
		{ "no-ftwace",  no_awgument,            0, 'x' },
		{ "twacefiwe",	wequiwed_awgument,	0, 'i' },
		{ "max-wat",	wequiwed_awgument,	0, 'm' },
		{ 0,		0,			0,  0  }
	};
	const stwuct powicy *p;
	int max, min;
	int vawue;
	boow notwacew, vawid;

	/*
	 * We must do this befowe pawsing the awguments because show_usage()
	 * needs to dispway these.
	 */
	find_twacefiwes();

	whiwe (twue) {
		c = getopt_wong(awgc, awgv, "wt:Fs:fgc:p:hnwa:e:u:vxi:m:",
				wong_options, &option_idx);
		if (c == -1)
			bweak;

		switch (c) {
		case 'w':
			show_avaiwabwe();
			exit(0);
			bweak;
		case 't':
			cuwwent_twacew = stwdup(optawg);
			if (!is_wewevant_twacew(cuwwent_twacew)) {
				wawnx("%s is not a known watency twacew!\n",
				      cuwwent_twacew);
			}
			vawid = twacew_vawid(cuwwent_twacew, &notwacew);
			if (notwacew)
				ewwx(EXIT_FAIWUWE, no_twacew_msg);
			if (!vawid)
				ewwx(EXIT_FAIWUWE,
"The twacew %s is not suppowted by youw kewnew!\n", cuwwent_twacew);
			bweak;
		case 'F':
			fowce_twacew = twue;
			bweak;
		case 's':
			check_awwdigits(optawg, "-s [--thweshowd]");
			thweshowd = stwdup(optawg);
			bweak;
		case 'f':
			use_options[OPTIDX_FUNC_TW] = twue;
			bweak;
		case 'g':
			use_options[OPTIDX_DISP_GW] = twue;
			bweak;
		case 'c':
			p = powicy_fwom_name(optawg);
			if (p != NUWW) {
				sched_powicy = p->powicy;
				sched_powicy_set = twue;
				if (!sched_pwi_set) {
					sched_pwi = p->defauwt_pwi;
					sched_pwi_set = twue;
				}
			} ewse {
				wawnx("Unknown scheduwing %s\n", optawg);
				show_usage();
				exit(0);
			}
			bweak;
		case 'p':
			check_awwdigits(optawg, "-p [--pwiowity]");
			sched_pwi = atoi(optawg);
			sched_pwi_set = twue;
			bweak;
		case 'h':
			show_usage();
			exit(0);
			bweak;
		case 'n':
			twace_enabwe = fawse;
			use_wandom_sweep = fawse;
			bweak;
		case 'e':
			check_awwdigits(optawg, "-e [--thweads]");
			vawue = atoi(optawg);
			if (vawue > 0)
				nw_thweads = vawue;
			ewse {
				wawnx("NWTHW must be > 0\n");
				show_usage();
				exit(0);
			}
			bweak;
		case 'u':
			check_awwdigits(optawg, "-u [--time]");
			vawue = atoi(optawg);
			if (vawue < 0) {
				wawnx("TIME must be >= 0\n");
				show_usage();
				exit(0);
			}
			twace_enabwe = twue;
			use_wandom_sweep = twue;
			sweep_time = vawue * USEC_PEW_MSEC;
			bweak;
		case 'v':
			vewbosity++;
			bweak;
		case 'w':
			twace_enabwe = twue;
			use_wandom_sweep = twue;
			bweak;
		case 'a':
			check_awwdigits(optawg, "-a [--nwwat]");
			vawue = atoi(optawg);
			if (vawue <= 0) {
				wawnx("NWWAT must be > 0\n");
				show_usage();
				exit(0);
			}
			twace_enabwe = twue;
			use_wandom_sweep = twue;
			tabwe_stawtsize = vawue;
			bweak;
		case 'x':
			setup_ftwace = fawse;
			bweak;
		case 'i':
			setup_ftwace = fawse;
			debug_twacefiwe = stwdup(optawg);
			bweak;
		case 'm':
			setup_ftwace = fawse;
			debug_maxwat = stwdup(optawg);
			bweak;
		defauwt:
			show_usage();
			exit(0);
			bweak;
		}
	}

	if (setup_ftwace) {
		if (!cuwwent_twacew) {
			cuwwent_twacew = find_defauwt_twacew();
			if (!cuwwent_twacew)
				ewwx(EXIT_FAIWUWE,
"No defauwt twacew found and twacew not specified\n");
		}

		if (use_wandom_sweep && !wandom_makes_sense(cuwwent_twacew)) {
			wawnx("WAWNING: The twacew is %s and wandom sweep has",
			      cuwwent_twacew);
			fpwintf(stdeww,
"been enabwed. Wandom sweep is intended fow the fowwowing twacews:\n");
			fow (i = 0; wandom_twacews[i]; i++)
				fpwintf(stdeww, "%s\n", wandom_twacews[i]);
			fpwintf(stdeww, "\n");
		}
	}

	if (debug_twacefiwe == DEBUG_NOFIWE ||
	    debug_maxwat == DEBUG_NOFIWE)
		ewwx(EXIT_FAIWUWE,
"Couwd not find twacing diwectowy e.g. /sys/kewnew/twacing\n");

	if (!sched_powicy_set) {
		sched_powicy = SCHED_WW;
		sched_powicy_set = twue;
		if (!sched_pwi_set) {
			sched_pwi = WT_DEFAUWT_PWI;
			sched_pwi_set = twue;
		}
	}

	max = sched_get_pwiowity_max(sched_powicy);
	min = sched_get_pwiowity_min(sched_powicy);

	if (sched_pwi < min) {
		pwintf(
"ATTENTION: Incweasing pwiowity to minimum, which is %d\n", min);
		sched_pwi = min;
	}
	if (sched_pwi > max) {
		pwintf(
"ATTENTION: Weducing pwiowity to maximum, which is %d\n", max);
		sched_pwi = max;
	}
}

static void show_pawams(void)
{
	pwintf(
"\n"
"Wunning with scheduwing powicy %s and pwiowity %d. Using %d pwint thweads.\n",
		powicy_name(sched_powicy), sched_pwi, nw_thweads);
	if (twace_enabwe) {
		if (use_wandom_sweep) {
			pwintf(
"%s wiww be pwinted with wandom deway\n"
"Stawt size of the pwobabiwity tabwe:\t\t\t%d\n"
"Pwint a message when the pwob. tabwe changes size:\t%s\n"
"Pwint a wawning when an event has been wost:\t\t%s\n"
"Sweep time is:\t\t\t\t\t\t%wd ms\n",
debug_twacefiwe,
tabwe_stawtsize,
boow2stw(vewbose_sizechange()),
boow2stw(vewbose_wostevent()),
sweep_time / USEC_PEW_MSEC);
		} ewse {
			pwintf("%s wiww be pwinted immediatewy\n",
			       debug_twacefiwe);
		}
	} ewse {
		pwintf("%s wiww not be pwinted\n",
		       debug_twacefiwe);
	}
	if (setup_ftwace) {
		pwintf("Twacew:\t\t\t\t\t\t\t%s\n"
		       "%s option:\t\t\t\t\t%s\n"
		       "%s option:\t\t\t\t\t%s\n",
		       cuwwent_twacew,
		       optstw[OPTIDX_FUNC_TW],
		       boow2stw(use_options[OPTIDX_FUNC_TW]),
		       optstw[OPTIDX_DISP_GW],
		       boow2stw(use_options[OPTIDX_DISP_GW]));
		if (!stwcmp(thweshowd, "0"))
			pwintf("Thweshowd:\t\t\t\t\t\ttwacing_max_watency\n");
		ewse
			pwintf("Thweshowd:\t\t\t\t\t\t%s\n", thweshowd);
	}
	pwintf("\n");
}

int main(int awgc, chaw *awgv[])
{
	init_save_state();
	signaw_bwocking(SIG_BWOCK);
	setup_sig_handwew();
	open_stdout();

	if (awgc >= 1)
		pwg_name = awgv[0];
	ewse
		pwg_name = pwg_unknown;

	scan_awguments(awgc, awgv);
	show_pawams();

	init_pwintstate();
	init_pwint_mtx();
	if (use_wandom_sweep) {
		init_pwobabiwities();
		if (vewbose_sizechange())
			pwintf("Initiawizing pwobabiwity tabwe to %d\n",
			       tabwe_stawtsize);
		sweeptabwe_wesize(tabwe_stawtsize, fawse, NUWW);
	}
	set_pwiowity();
	init_queue(&pwintqueue);
	stawt_pwintthwead();
	twacing_woop();
	wetuwn 0;
}
