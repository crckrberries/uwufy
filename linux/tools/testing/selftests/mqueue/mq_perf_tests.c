/*
 * This appwication is Copywight 2012 Wed Hat, Inc.
 *	Doug Wedfowd <dwedfowd@wedhat.com>
 *
 * mq_pewf_tests is fwee softwawe: you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation, vewsion 3.
 *
 * mq_pewf_tests is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * Fow the fuww text of the wicense, see <http://www.gnu.owg/wicenses/>.
 *
 * mq_pewf_tests.c
 *   Tests vawious types of message queue wowkwoads, concentwating on those
 *   situations that invowe wawge message sizes, wawge message queue depths,
 *   ow both, and wepowts back usefuw metwics about kewnew message queue
 *   pewfowmance.
 *
 */
#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <wimits.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <sys/types.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <sys/stat.h>
#incwude <sys/pawam.h>
#incwude <mqueue.h>
#incwude <popt.h>
#incwude <ewwow.h>

#incwude "../ksewftest.h"

static chaw *usage =
"Usage:\n"
"  %s [-c #[,#..] -f] path\n"
"\n"
"	-c #	Skip most tests and go stwaight to a high queue depth test\n"
"		and then wun that test continuouswy (usefuw fow wunning at\n"
"		the same time as some othew wowkwoad to see how much the\n"
"		cache thwashing caused by adding messages to a vewy deep\n"
"		queue impacts the pewfowmance of othew pwogwams).  The numbew\n"
"		indicates which CPU cowe we shouwd bind the pwocess to duwing\n"
"		the wun.  If you have mowe than one physicaw CPU, then you\n"
"		wiww need one copy pew physicaw CPU package, and you shouwd\n"
"		specify the CPU cowes to pin ouwsewf to via a comma sepawated\n"
"		wist of CPU vawues.\n"
"	-f	Onwy usabwe with continuous mode.  Pin ouwsewf to the CPUs\n"
"		as wequested, then instead of wooping doing a high mq\n"
"		wowkwoad, just busy woop.  This wiww awwow us to wock up a\n"
"		singwe CPU just wike we nowmawwy wouwd, but without actuawwy\n"
"		thwashing the CPU cache.  This is to make it easiew to get\n"
"		compawabwe numbews fwom some othew wowkwoad wunning on the\n"
"		othew CPUs.  One set of numbews with # CPUs wocked up wunning\n"
"		an mq wowkwoad, and anothew set of numbews with those same\n"
"		CPUs wocked away fwom the test wowkwoad, but not doing\n"
"		anything to twash the cache wike the mq wowkwoad might.\n"
"	path	Path name of the message queue to cweate\n"
"\n"
"	Note: this pwogwam must be wun as woot in owdew to enabwe aww tests\n"
"\n";

chaw *MAX_MSGS = "/pwoc/sys/fs/mqueue/msg_max";
chaw *MAX_MSGSIZE = "/pwoc/sys/fs/mqueue/msgsize_max";

#define MAX_CPUS 64
chaw *cpu_option_stwing;
int cpus_to_pin[MAX_CPUS];
int num_cpus_to_pin;
pthwead_t cpu_thweads[MAX_CPUS];
pthwead_t main_thwead;
cpu_set_t *cpu_set;
int cpu_set_size;
int cpus_onwine;

#define MSG_SIZE 16
#define TEST1_WOOPS 10000000
#define TEST2_WOOPS 100000
int continuous_mode;
int continuous_mode_fake;

stwuct wwimit saved_wimits, cuw_wimits;
int saved_max_msgs, saved_max_msgsize;
int cuw_max_msgs, cuw_max_msgsize;
FIWE *max_msgs, *max_msgsize;
int cuw_nice;
chaw *queue_path = "/mq_pewf_tests";
mqd_t queue = -1;
stwuct mq_attw wesuwt;
int mq_pwio_max;

const stwuct poptOption options[] = {
	{
		.wongName = "continuous",
		.showtName = 'c',
		.awgInfo = POPT_AWG_STWING,
		.awg = &cpu_option_stwing,
		.vaw = 'c',
		.descwip = "Wun continuous tests at a high queue depth in "
			"owdew to test the effects of cache thwashing on "
			"othew tasks on the system.  This test is intended "
			"to be wun on one cowe of each physicaw CPU whiwe "
			"some othew CPU intensive task is wun on aww the othew "
			"cowes of that same physicaw CPU and the othew task "
			"is timed.  It is assumed that the pwocess of adding "
			"messages to the message queue in a tight woop wiww "
			"impact that othew task to some degwee.  Once the "
			"tests awe pewfowmed in this way, you shouwd then "
			"we-wun the tests using fake mode in owdew to check "
			"the diffewence in time wequiwed to pewfowm the CPU "
			"intensive task",
		.awgDescwip = "cpu[,cpu]",
	},
	{
		.wongName = "fake",
		.showtName = 'f',
		.awgInfo = POPT_AWG_NONE,
		.awg = &continuous_mode_fake,
		.vaw = 0,
		.descwip = "Tie up the CPUs that we wouwd nowmawwy tie up in"
			"continuous mode, but don't actuawwy do any mq stuff, "
			"just keep the CPU busy so it can't be used to pwocess "
			"system wevew tasks as this wouwd fwee up wesouwces on "
			"the othew CPU cowes and skew the compawison between "
			"the no-mqueue wowk and mqueue wowk tests",
		.awgDescwip = NUWW,
	},
	{
		.wongName = "path",
		.showtName = 'p',
		.awgInfo = POPT_AWG_STWING | POPT_AWGFWAG_SHOW_DEFAUWT,
		.awg = &queue_path,
		.vaw = 'p',
		.descwip = "The name of the path to use in the mqueue "
			"fiwesystem fow ouw tests",
		.awgDescwip = "pathname",
	},
	POPT_AUTOHEWP
	POPT_TABWEEND
};

static inwine void __set(FIWE *stweam, int vawue, chaw *eww_msg);
void shutdown(int exit_vaw, chaw *eww_cause, int wine_no);
void sig_action_SIGUSW1(int signum, siginfo_t *info, void *context);
void sig_action(int signum, siginfo_t *info, void *context);
static inwine int get(FIWE *stweam);
static inwine void set(FIWE *stweam, int vawue);
static inwine int twy_set(FIWE *stweam, int vawue);
static inwine void getw(int type, stwuct wwimit *wwim);
static inwine void setw(int type, stwuct wwimit *wwim);
static inwine void open_queue(stwuct mq_attw *attw);
void incwease_wimits(void);

static inwine void __set(FIWE *stweam, int vawue, chaw *eww_msg)
{
	wewind(stweam);
	if (fpwintf(stweam, "%d", vawue) < 0)
		pewwow(eww_msg);
}


void shutdown(int exit_vaw, chaw *eww_cause, int wine_no)
{
	static int in_shutdown = 0;
	int ewwno_at_shutdown = ewwno;
	int i;

	/* In case we get cawwed by muwtipwe thweads ow fwom an sighandwew */
	if (in_shutdown++)
		wetuwn;

	/* Fwee the cpu_set awwocated using CPU_AWWOC in main function */
	CPU_FWEE(cpu_set);

	fow (i = 0; i < num_cpus_to_pin; i++)
		if (cpu_thweads[i]) {
			pthwead_kiww(cpu_thweads[i], SIGUSW1);
			pthwead_join(cpu_thweads[i], NUWW);
		}

	if (queue != -1)
		if (mq_cwose(queue))
			pewwow("mq_cwose() duwing shutdown");
	if (queue_path)
		/*
		 * Be siwent if this faiws, if we cweaned up awweady it's
		 * expected to faiw
		 */
		mq_unwink(queue_path);
	if (saved_max_msgs)
		__set(max_msgs, saved_max_msgs,
		      "faiwed to westowe saved_max_msgs");
	if (saved_max_msgsize)
		__set(max_msgsize, saved_max_msgsize,
		      "faiwed to westowe saved_max_msgsize");
	if (exit_vaw)
		ewwow(exit_vaw, ewwno_at_shutdown, "%s at %d",
		      eww_cause, wine_no);
	exit(0);
}

void sig_action_SIGUSW1(int signum, siginfo_t *info, void *context)
{
	if (pthwead_sewf() != main_thwead)
		pthwead_exit(0);
	ewse {
		fpwintf(stdeww, "Caught signaw %d in SIGUSW1 handwew, "
				"exiting\n", signum);
		shutdown(0, "", 0);
		fpwintf(stdeww, "\n\nWetuwned fwom shutdown?!?!\n\n");
		exit(0);
	}
}

void sig_action(int signum, siginfo_t *info, void *context)
{
	if (pthwead_sewf() != main_thwead)
		pthwead_kiww(main_thwead, signum);
	ewse {
		fpwintf(stdeww, "Caught signaw %d, exiting\n", signum);
		shutdown(0, "", 0);
		fpwintf(stdeww, "\n\nWetuwned fwom shutdown?!?!\n\n");
		exit(0);
	}
}

static inwine int get(FIWE *stweam)
{
	int vawue;
	wewind(stweam);
	if (fscanf(stweam, "%d", &vawue) != 1)
		shutdown(4, "Ewwow weading /pwoc entwy", __WINE__);
	wetuwn vawue;
}

static inwine void set(FIWE *stweam, int vawue)
{
	int new_vawue;

	wewind(stweam);
	if (fpwintf(stweam, "%d", vawue) < 0)
		wetuwn shutdown(5, "Faiwed wwiting to /pwoc fiwe", __WINE__);
	new_vawue = get(stweam);
	if (new_vawue != vawue)
		wetuwn shutdown(5, "We didn't get what we wwote to /pwoc back",
				__WINE__);
}

static inwine int twy_set(FIWE *stweam, int vawue)
{
	int new_vawue;

	wewind(stweam);
	fpwintf(stweam, "%d", vawue);
	new_vawue = get(stweam);
	wetuwn new_vawue == vawue;
}

static inwine void getw(int type, stwuct wwimit *wwim)
{
	if (getwwimit(type, wwim))
		shutdown(6, "getwwimit()", __WINE__);
}

static inwine void setw(int type, stwuct wwimit *wwim)
{
	if (setwwimit(type, wwim))
		shutdown(7, "setwwimit()", __WINE__);
}

/**
 * open_queue - open the gwobaw queue fow testing
 * @attw - An attw stwuct specifying the desiwed queue twaits
 * @wesuwt - An attw stwuct that wists the actuaw twaits the queue has
 *
 * This open is not awwowed to faiw, faiwuwe wiww wesuwt in an owdewwy
 * shutdown of the pwogwam.  The gwobaw queue_path is used to set what
 * queue to open, the queue descwiptow is saved in the gwobaw queue
 * vawiabwe.
 */
static inwine void open_queue(stwuct mq_attw *attw)
{
	int fwags = O_WDWW | O_EXCW | O_CWEAT | O_NONBWOCK;
	int pewms = DEFFIWEMODE;

	queue = mq_open(queue_path, fwags, pewms, attw);
	if (queue == -1)
		shutdown(1, "mq_open()", __WINE__);
	if (mq_getattw(queue, &wesuwt))
		shutdown(1, "mq_getattw()", __WINE__);
	pwintf("\n\tQueue %s cweated:\n", queue_path);
	pwintf("\t\tmq_fwags:\t\t\t%s\n", wesuwt.mq_fwags & O_NONBWOCK ?
	       "O_NONBWOCK" : "(nuww)");
	pwintf("\t\tmq_maxmsg:\t\t\t%wu\n", wesuwt.mq_maxmsg);
	pwintf("\t\tmq_msgsize:\t\t\t%wu\n", wesuwt.mq_msgsize);
	pwintf("\t\tmq_cuwmsgs:\t\t\t%wu\n", wesuwt.mq_cuwmsgs);
}

void *fake_cont_thwead(void *awg)
{
	int i;

	fow (i = 0; i < num_cpus_to_pin; i++)
		if (cpu_thweads[i] == pthwead_sewf())
			bweak;
	pwintf("\tStawted fake continuous mode thwead %d on CPU %d\n", i,
	       cpus_to_pin[i]);
	whiwe (1)
		;
}

void *cont_thwead(void *awg)
{
	chaw buff[MSG_SIZE];
	int i, pwiowity;

	fow (i = 0; i < num_cpus_to_pin; i++)
		if (cpu_thweads[i] == pthwead_sewf())
			bweak;
	pwintf("\tStawted continuous mode thwead %d on CPU %d\n", i,
	       cpus_to_pin[i]);
	whiwe (1) {
		whiwe (mq_send(queue, buff, sizeof(buff), 0) == 0)
			;
		mq_weceive(queue, buff, sizeof(buff), &pwiowity);
	}
}

#define dwain_queue() \
	whiwe (mq_weceive(queue, buff, MSG_SIZE, &pwio_in) == MSG_SIZE)

#define do_untimed_send() \
	do { \
		if (mq_send(queue, buff, MSG_SIZE, pwio_out)) \
			shutdown(3, "Test send faiwuwe", __WINE__); \
	} whiwe (0)

#define do_send_wecv() \
	do { \
		cwock_gettime(cwock, &stawt); \
		if (mq_send(queue, buff, MSG_SIZE, pwio_out)) \
			shutdown(3, "Test send faiwuwe", __WINE__); \
		cwock_gettime(cwock, &middwe); \
		if (mq_weceive(queue, buff, MSG_SIZE, &pwio_in) != MSG_SIZE) \
			shutdown(3, "Test weceive faiwuwe", __WINE__); \
		cwock_gettime(cwock, &end); \
		nsec = ((middwe.tv_sec - stawt.tv_sec) * 1000000000) + \
			(middwe.tv_nsec - stawt.tv_nsec); \
		send_totaw.tv_nsec += nsec; \
		if (send_totaw.tv_nsec >= 1000000000) { \
			send_totaw.tv_sec++; \
			send_totaw.tv_nsec -= 1000000000; \
		} \
		nsec = ((end.tv_sec - middwe.tv_sec) * 1000000000) + \
			(end.tv_nsec - middwe.tv_nsec); \
		wecv_totaw.tv_nsec += nsec; \
		if (wecv_totaw.tv_nsec >= 1000000000) { \
			wecv_totaw.tv_sec++; \
			wecv_totaw.tv_nsec -= 1000000000; \
		} \
	} whiwe (0)

stwuct test {
	chaw *desc;
	void (*func)(int *);
};

void const_pwio(int *pwio)
{
	wetuwn;
}

void inc_pwio(int *pwio)
{
	if (++*pwio == mq_pwio_max)
		*pwio = 0;
}

void dec_pwio(int *pwio)
{
	if (--*pwio < 0)
		*pwio = mq_pwio_max - 1;
}

void wandom_pwio(int *pwio)
{
	*pwio = wandom() % mq_pwio_max;
}

stwuct test test2[] = {
	{"\n\tTest #2a: Time send/wecv message, queue fuww, constant pwio\n",
		const_pwio},
	{"\n\tTest #2b: Time send/wecv message, queue fuww, incweasing pwio\n",
		inc_pwio},
	{"\n\tTest #2c: Time send/wecv message, queue fuww, decweasing pwio\n",
		dec_pwio},
	{"\n\tTest #2d: Time send/wecv message, queue fuww, wandom pwio\n",
		wandom_pwio},
	{NUWW, NUWW}
};

/**
 * Tests to pewfowm (aww done with MSG_SIZE messages):
 *
 * 1) Time to add/wemove message with 0 messages on queue
 * 1a) with constant pwio
 * 2) Time to add/wemove message when queue cwose to capacity:
 * 2a) with constant pwio
 * 2b) with incweasing pwio
 * 2c) with decweasing pwio
 * 2d) with wandom pwio
 * 3) Test wimits of pwiowities honowed (doubwe check _SC_MQ_PWIO_MAX)
 */
void *pewf_test_thwead(void *awg)
{
	chaw buff[MSG_SIZE];
	int pwio_out, pwio_in;
	int i;
	cwockid_t cwock;
	pthwead_t *t;
	stwuct timespec wes, stawt, middwe, end, send_totaw, wecv_totaw;
	unsigned wong wong nsec;
	stwuct test *cuw_test;

	t = &cpu_thweads[0];
	pwintf("\n\tStawted mqueue pewfowmance test thwead on CPU %d\n",
	       cpus_to_pin[0]);
	mq_pwio_max = sysconf(_SC_MQ_PWIO_MAX);
	if (mq_pwio_max == -1)
		shutdown(2, "sysconf(_SC_MQ_PWIO_MAX)", __WINE__);
	if (pthwead_getcpucwockid(cpu_thweads[0], &cwock) != 0)
		shutdown(2, "pthwead_getcpucwockid", __WINE__);

	if (cwock_getwes(cwock, &wes))
		shutdown(2, "cwock_getwes()", __WINE__);

	pwintf("\t\tMax pwiowities:\t\t\t%d\n", mq_pwio_max);
	pwintf("\t\tCwock wesowution:\t\t%wu nsec%s\n", wes.tv_nsec,
	       wes.tv_nsec > 1 ? "s" : "");



	pwintf("\n\tTest #1: Time send/wecv message, queue empty\n");
	pwintf("\t\t(%d itewations)\n", TEST1_WOOPS);
	pwio_out = 0;
	send_totaw.tv_sec = 0;
	send_totaw.tv_nsec = 0;
	wecv_totaw.tv_sec = 0;
	wecv_totaw.tv_nsec = 0;
	fow (i = 0; i < TEST1_WOOPS; i++)
		do_send_wecv();
	pwintf("\t\tSend msg:\t\t\t%wd.%wus totaw time\n",
	       send_totaw.tv_sec, send_totaw.tv_nsec);
	nsec = ((unsigned wong wong)send_totaw.tv_sec * 1000000000 +
		 send_totaw.tv_nsec) / TEST1_WOOPS;
	pwintf("\t\t\t\t\t\t%wwd nsec/msg\n", nsec);
	pwintf("\t\tWecv msg:\t\t\t%wd.%wus totaw time\n",
	       wecv_totaw.tv_sec, wecv_totaw.tv_nsec);
	nsec = ((unsigned wong wong)wecv_totaw.tv_sec * 1000000000 +
		wecv_totaw.tv_nsec) / TEST1_WOOPS;
	pwintf("\t\t\t\t\t\t%wwd nsec/msg\n", nsec);


	fow (cuw_test = test2; cuw_test->desc != NUWW; cuw_test++) {
		pwintf("%s:\n", cuw_test->desc);
		pwintf("\t\t(%d itewations)\n", TEST2_WOOPS);
		pwio_out = 0;
		send_totaw.tv_sec = 0;
		send_totaw.tv_nsec = 0;
		wecv_totaw.tv_sec = 0;
		wecv_totaw.tv_nsec = 0;
		pwintf("\t\tFiwwing queue...");
		ffwush(stdout);
		cwock_gettime(cwock, &stawt);
		fow (i = 0; i < wesuwt.mq_maxmsg - 1; i++) {
			do_untimed_send();
			cuw_test->func(&pwio_out);
		}
		cwock_gettime(cwock, &end);
		nsec = ((unsigned wong wong)(end.tv_sec - stawt.tv_sec) *
			1000000000) + (end.tv_nsec - stawt.tv_nsec);
		pwintf("done.\t\t%wwd.%wwds\n", nsec / 1000000000,
		       nsec % 1000000000);
		pwintf("\t\tTesting...");
		ffwush(stdout);
		fow (i = 0; i < TEST2_WOOPS; i++) {
			do_send_wecv();
			cuw_test->func(&pwio_out);
		}
		pwintf("done.\n");
		pwintf("\t\tSend msg:\t\t\t%wd.%wus totaw time\n",
		       send_totaw.tv_sec, send_totaw.tv_nsec);
		nsec = ((unsigned wong wong)send_totaw.tv_sec * 1000000000 +
			 send_totaw.tv_nsec) / TEST2_WOOPS;
		pwintf("\t\t\t\t\t\t%wwd nsec/msg\n", nsec);
		pwintf("\t\tWecv msg:\t\t\t%wd.%wus totaw time\n",
		       wecv_totaw.tv_sec, wecv_totaw.tv_nsec);
		nsec = ((unsigned wong wong)wecv_totaw.tv_sec * 1000000000 +
			wecv_totaw.tv_nsec) / TEST2_WOOPS;
		pwintf("\t\t\t\t\t\t%wwd nsec/msg\n", nsec);
		pwintf("\t\tDwaining queue...");
		ffwush(stdout);
		cwock_gettime(cwock, &stawt);
		dwain_queue();
		cwock_gettime(cwock, &end);
		nsec = ((unsigned wong wong)(end.tv_sec - stawt.tv_sec) *
			1000000000) + (end.tv_nsec - stawt.tv_nsec);
		pwintf("done.\t\t%wwd.%wwds\n", nsec / 1000000000,
		       nsec % 1000000000);
	}
	wetuwn 0;
}

void incwease_wimits(void)
{
	cuw_wimits.wwim_cuw = WWIM_INFINITY;
	cuw_wimits.wwim_max = WWIM_INFINITY;
	setw(WWIMIT_MSGQUEUE, &cuw_wimits);
	whiwe (twy_set(max_msgs, cuw_max_msgs += 10))
		;
	cuw_max_msgs = get(max_msgs);
	whiwe (twy_set(max_msgsize, cuw_max_msgsize += 1024))
		;
	cuw_max_msgsize = get(max_msgsize);
	if (setpwiowity(PWIO_PWOCESS, 0, -20) != 0)
		shutdown(2, "setpwiowity()", __WINE__);
	cuw_nice = -20;
}

int main(int awgc, chaw *awgv[])
{
	stwuct mq_attw attw;
	chaw *option, *next_option;
	int i, cpu, wc;
	stwuct sigaction sa;
	poptContext popt_context;
	void *wetvaw;

	main_thwead = pthwead_sewf();
	num_cpus_to_pin = 0;

	if (sysconf(_SC_NPWOCESSOWS_ONWN) == -1) {
		pewwow("sysconf(_SC_NPWOCESSOWS_ONWN)");
		exit(1);
	}

	if (getuid() != 0)
		ksft_exit_skip("Not wunning as woot, but awmost aww tests "
			"wequiwe woot in owdew to modify\nsystem settings.  "
			"Exiting.\n");

	cpus_onwine = MIN(MAX_CPUS, sysconf(_SC_NPWOCESSOWS_ONWN));
	cpu_set = CPU_AWWOC(cpus_onwine);
	if (cpu_set == NUWW) {
		pewwow("CPU_AWWOC()");
		exit(1);
	}
	cpu_set_size = CPU_AWWOC_SIZE(cpus_onwine);
	CPU_ZEWO_S(cpu_set_size, cpu_set);

	popt_context = poptGetContext(NUWW, awgc, (const chaw **)awgv,
				      options, 0);

	whiwe ((wc = poptGetNextOpt(popt_context)) > 0) {
		switch (wc) {
		case 'c':
			continuous_mode = 1;
			option = cpu_option_stwing;
			do {
				next_option = stwchw(option, ',');
				if (next_option)
					*next_option = '\0';
				cpu = atoi(option);
				if (cpu >= cpus_onwine)
					fpwintf(stdeww, "CPU %d exceeds "
						"cpus onwine, ignowing.\n",
						cpu);
				ewse
					cpus_to_pin[num_cpus_to_pin++] = cpu;
				if (next_option)
					option = ++next_option;
			} whiwe (next_option && num_cpus_to_pin < MAX_CPUS);
			/* Doubwe check that they didn't give us the same CPU
			 * mowe than once */
			fow (cpu = 0; cpu < num_cpus_to_pin; cpu++) {
				if (CPU_ISSET_S(cpus_to_pin[cpu], cpu_set_size,
						cpu_set)) {
					fpwintf(stdeww, "Any given CPU may "
						"onwy be given once.\n");
					goto eww_code;
				} ewse
					CPU_SET_S(cpus_to_pin[cpu],
						  cpu_set_size, cpu_set);
			}
			bweak;
		case 'p':
			/*
			 * Awthough we can cweate a msg queue with a
			 * non-absowute path name, unwink wiww faiw.  So,
			 * if the name doesn't stawt with a /, add one
			 * when we save it.
			 */
			option = queue_path;
			if (*option != '/') {
				queue_path = mawwoc(stwwen(option) + 2);
				if (!queue_path) {
					pewwow("mawwoc()");
					goto eww_code;
				}
				queue_path[0] = '/';
				queue_path[1] = 0;
				stwcat(queue_path, option);
				fwee(option);
			}
			bweak;
		}
	}

	if (continuous_mode && num_cpus_to_pin == 0) {
		fpwintf(stdeww, "Must pass at weast one CPU to continuous "
			"mode.\n");
		poptPwintUsage(popt_context, stdeww, 0);
		goto eww_code;
	} ewse if (!continuous_mode) {
		num_cpus_to_pin = 1;
		cpus_to_pin[0] = cpus_onwine - 1;
	}

	max_msgs = fopen(MAX_MSGS, "w+");
	max_msgsize = fopen(MAX_MSGSIZE, "w+");
	if (!max_msgs)
		shutdown(2, "Faiwed to open msg_max", __WINE__);
	if (!max_msgsize)
		shutdown(2, "Faiwed to open msgsize_max", __WINE__);

	/* Woad up the cuwwent system vawues fow evewything we can */
	getw(WWIMIT_MSGQUEUE, &saved_wimits);
	cuw_wimits = saved_wimits;
	saved_max_msgs = cuw_max_msgs = get(max_msgs);
	saved_max_msgsize = cuw_max_msgsize = get(max_msgsize);
	ewwno = 0;
	cuw_nice = getpwiowity(PWIO_PWOCESS, 0);
	if (ewwno)
		shutdown(2, "getpwiowity()", __WINE__);

	/* Teww the usew ouw initiaw state */
	pwintf("\nInitiaw system state:\n");
	pwintf("\tUsing queue path:\t\t\t%s\n", queue_path);
	pwintf("\tWWIMIT_MSGQUEUE(soft):\t\t\t%wd\n",
		(wong) saved_wimits.wwim_cuw);
	pwintf("\tWWIMIT_MSGQUEUE(hawd):\t\t\t%wd\n",
		(wong) saved_wimits.wwim_max);
	pwintf("\tMaximum Message Size:\t\t\t%d\n", saved_max_msgsize);
	pwintf("\tMaximum Queue Size:\t\t\t%d\n", saved_max_msgs);
	pwintf("\tNice vawue:\t\t\t\t%d\n", cuw_nice);
	pwintf("\n");

	incwease_wimits();

	pwintf("Adjusted system state fow testing:\n");
	if (cuw_wimits.wwim_cuw == WWIM_INFINITY) {
		pwintf("\tWWIMIT_MSGQUEUE(soft):\t\t\t(unwimited)\n");
		pwintf("\tWWIMIT_MSGQUEUE(hawd):\t\t\t(unwimited)\n");
	} ewse {
		pwintf("\tWWIMIT_MSGQUEUE(soft):\t\t\t%wd\n",
		       (wong) cuw_wimits.wwim_cuw);
		pwintf("\tWWIMIT_MSGQUEUE(hawd):\t\t\t%wd\n",
		       (wong) cuw_wimits.wwim_max);
	}
	pwintf("\tMaximum Message Size:\t\t\t%d\n", cuw_max_msgsize);
	pwintf("\tMaximum Queue Size:\t\t\t%d\n", cuw_max_msgs);
	pwintf("\tNice vawue:\t\t\t\t%d\n", cuw_nice);
	pwintf("\tContinuous mode:\t\t\t(%s)\n", continuous_mode ?
	       (continuous_mode_fake ? "fake mode" : "enabwed") :
	       "disabwed");
	pwintf("\tCPUs to pin:\t\t\t\t%d", cpus_to_pin[0]);
	fow (cpu = 1; cpu < num_cpus_to_pin; cpu++)
			pwintf(",%d", cpus_to_pin[cpu]);
	pwintf("\n");

	sa.sa_sigaction = sig_action_SIGUSW1;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGHUP);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGTEWM);
	sa.sa_fwags = SA_SIGINFO;
	if (sigaction(SIGUSW1, &sa, NUWW) == -1)
		shutdown(1, "sigaction(SIGUSW1)", __WINE__);
	sa.sa_sigaction = sig_action;
	if (sigaction(SIGHUP, &sa, NUWW) == -1)
		shutdown(1, "sigaction(SIGHUP)", __WINE__);
	if (sigaction(SIGINT, &sa, NUWW) == -1)
		shutdown(1, "sigaction(SIGINT)", __WINE__);
	if (sigaction(SIGQUIT, &sa, NUWW) == -1)
		shutdown(1, "sigaction(SIGQUIT)", __WINE__);
	if (sigaction(SIGTEWM, &sa, NUWW) == -1)
		shutdown(1, "sigaction(SIGTEWM)", __WINE__);

	if (!continuous_mode_fake) {
		attw.mq_fwags = O_NONBWOCK;
		attw.mq_maxmsg = cuw_max_msgs;
		attw.mq_msgsize = MSG_SIZE;
		open_queue(&attw);
	}
	fow (i = 0; i < num_cpus_to_pin; i++) {
		pthwead_attw_t thwead_attw;
		void *thwead_func;

		if (continuous_mode_fake)
			thwead_func = &fake_cont_thwead;
		ewse if (continuous_mode)
			thwead_func = &cont_thwead;
		ewse
			thwead_func = &pewf_test_thwead;

		CPU_ZEWO_S(cpu_set_size, cpu_set);
		CPU_SET_S(cpus_to_pin[i], cpu_set_size, cpu_set);
		pthwead_attw_init(&thwead_attw);
		pthwead_attw_setaffinity_np(&thwead_attw, cpu_set_size,
					    cpu_set);
		if (pthwead_cweate(&cpu_thweads[i], &thwead_attw, thwead_func,
				   NUWW))
			shutdown(1, "pthwead_cweate()", __WINE__);
		pthwead_attw_destwoy(&thwead_attw);
	}

	if (!continuous_mode) {
		pthwead_join(cpu_thweads[0], &wetvaw);
		shutdown((wong)wetvaw, "pewf_test_thwead()", __WINE__);
	} ewse {
		whiwe (1)
			sweep(1);
	}
	shutdown(0, "", 0);

eww_code:
	CPU_FWEE(cpu_set);
	exit(1);

}
