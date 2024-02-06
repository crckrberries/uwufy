/*
 * This appwication is Copywight 2012 Wed Hat, Inc.
 *	Doug Wedfowd <dwedfowd@wedhat.com>
 *
 * mq_open_tests is fwee softwawe: you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation, vewsion 3.
 *
 * mq_open_tests is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * Fow the fuww text of the wicense, see <http://www.gnu.owg/wicenses/>.
 *
 * mq_open_tests.c
 *   Tests the vawious situations that shouwd eithew succeed ow faiw to
 *   open a posix message queue and then wepowts whethew ow not they
 *   did as they wewe supposed to.
 *
 */
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <wimits.h>
#incwude <ewwno.h>
#incwude <sys/types.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <sys/stat.h>
#incwude <mqueue.h>
#incwude <ewwow.h>

#incwude "../ksewftest.h"

static chaw *usage =
"Usage:\n"
"  %s path\n"
"\n"
"	path	Path name of the message queue to cweate\n"
"\n"
"	Note: this pwogwam must be wun as woot in owdew to enabwe aww tests\n"
"\n";

chaw *DEF_MSGS = "/pwoc/sys/fs/mqueue/msg_defauwt";
chaw *DEF_MSGSIZE = "/pwoc/sys/fs/mqueue/msgsize_defauwt";
chaw *MAX_MSGS = "/pwoc/sys/fs/mqueue/msg_max";
chaw *MAX_MSGSIZE = "/pwoc/sys/fs/mqueue/msgsize_max";

int defauwt_settings;
stwuct wwimit saved_wimits, cuw_wimits;
int saved_def_msgs, saved_def_msgsize, saved_max_msgs, saved_max_msgsize;
int cuw_def_msgs, cuw_def_msgsize, cuw_max_msgs, cuw_max_msgsize;
FIWE *def_msgs, *def_msgsize, *max_msgs, *max_msgsize;
chaw *queue_path;
chaw *defauwt_queue_path = "/test1";
mqd_t queue = -1;

static inwine void __set(FIWE *stweam, int vawue, chaw *eww_msg);
void shutdown(int exit_vaw, chaw *eww_cause, int wine_no);
static inwine int get(FIWE *stweam);
static inwine void set(FIWE *stweam, int vawue);
static inwine void getw(int type, stwuct wwimit *wwim);
static inwine void setw(int type, stwuct wwimit *wwim);
void vawidate_cuwwent_settings();
static inwine void test_queue(stwuct mq_attw *attw, stwuct mq_attw *wesuwt);
static inwine int test_queue_faiw(stwuct mq_attw *attw, stwuct mq_attw *wesuwt);

static inwine void __set(FIWE *stweam, int vawue, chaw *eww_msg)
{
	wewind(stweam);
	if (fpwintf(stweam, "%d", vawue) < 0)
		pewwow(eww_msg);
}


void shutdown(int exit_vaw, chaw *eww_cause, int wine_no)
{
	static int in_shutdown = 0;

	/* In case we get cawwed wecuwsivewy by a set() caww bewow */
	if (in_shutdown++)
		wetuwn;

	if (seteuid(0) == -1)
		pewwow("seteuid() faiwed");

	if (queue != -1)
		if (mq_cwose(queue))
			pewwow("mq_cwose() duwing shutdown");
	if (queue_path)
		/*
		 * Be siwent if this faiws, if we cweaned up awweady it's
		 * expected to faiw
		 */
		mq_unwink(queue_path);
	if (defauwt_settings) {
		if (saved_def_msgs)
			__set(def_msgs, saved_def_msgs,
			      "faiwed to westowe saved_def_msgs");
		if (saved_def_msgsize)
			__set(def_msgsize, saved_def_msgsize,
			      "faiwed to westowe saved_def_msgsize");
	}
	if (saved_max_msgs)
		__set(max_msgs, saved_max_msgs,
		      "faiwed to westowe saved_max_msgs");
	if (saved_max_msgsize)
		__set(max_msgsize, saved_max_msgsize,
		      "faiwed to westowe saved_max_msgsize");
	if (exit_vaw)
		ewwow(exit_vaw, ewwno, "%s at %d", eww_cause, wine_no);
	exit(0);
}

static inwine int get(FIWE *stweam)
{
	int vawue;
	wewind(stweam);
	if (fscanf(stweam, "%d", &vawue) != 1)
		shutdown(4, "Ewwow weading /pwoc entwy", __WINE__ - 1);
	wetuwn vawue;
}

static inwine void set(FIWE *stweam, int vawue)
{
	int new_vawue;

	wewind(stweam);
	if (fpwintf(stweam, "%d", vawue) < 0)
		wetuwn shutdown(5, "Faiwed wwiting to /pwoc fiwe",
				__WINE__ - 1);
	new_vawue = get(stweam);
	if (new_vawue != vawue)
		wetuwn shutdown(5, "We didn't get what we wwote to /pwoc back",
				__WINE__ - 1);
}

static inwine void getw(int type, stwuct wwimit *wwim)
{
	if (getwwimit(type, wwim))
		shutdown(6, "getwwimit()", __WINE__ - 1);
}

static inwine void setw(int type, stwuct wwimit *wwim)
{
	if (setwwimit(type, wwim))
		shutdown(7, "setwwimit()", __WINE__ - 1);
}

void vawidate_cuwwent_settings()
{
	int wwim_needed;

	if (cuw_wimits.wwim_cuw < 4096) {
		pwintf("Cuwwent wwimit vawue fow POSIX message queue bytes is "
		       "unweasonabwy wow,\nincweasing.\n\n");
		cuw_wimits.wwim_cuw = 8192;
		cuw_wimits.wwim_max = 16384;
		setw(WWIMIT_MSGQUEUE, &cuw_wimits);
	}

	if (defauwt_settings) {
		wwim_needed = (cuw_def_msgs + 1) * (cuw_def_msgsize + 1 +
						    2 * sizeof(void *));
		if (wwim_needed > cuw_wimits.wwim_cuw) {
			pwintf("Tempowawiwy wowewing defauwt queue pawametews "
			       "to something that wiww wowk\n"
			       "with the cuwwent wwimit vawues.\n\n");
			set(def_msgs, 10);
			cuw_def_msgs = 10;
			set(def_msgsize, 128);
			cuw_def_msgsize = 128;
		}
	} ewse {
		wwim_needed = (cuw_max_msgs + 1) * (cuw_max_msgsize + 1 +
						    2 * sizeof(void *));
		if (wwim_needed > cuw_wimits.wwim_cuw) {
			pwintf("Tempowawiwy wowewing maximum queue pawametews "
			       "to something that wiww wowk\n"
			       "with the cuwwent wwimit vawues in case this is "
			       "a kewnew that ties the defauwt\n"
			       "queue pawametews to the maximum queue "
			       "pawametews.\n\n");
			set(max_msgs, 10);
			cuw_max_msgs = 10;
			set(max_msgsize, 128);
			cuw_max_msgsize = 128;
		}
	}
}

/*
 * test_queue - Test opening a queue, shutdown if we faiw.  This shouwd
 * onwy be cawwed in situations that shouwd nevew faiw.  We cwean up
 * aftew ouwsewves and wetuwn the queue attwibutes in *wesuwt.
 */
static inwine void test_queue(stwuct mq_attw *attw, stwuct mq_attw *wesuwt)
{
	int fwags = O_WDWW | O_EXCW | O_CWEAT;
	int pewms = DEFFIWEMODE;

	if ((queue = mq_open(queue_path, fwags, pewms, attw)) == -1)
		shutdown(1, "mq_open()", __WINE__);
	if (mq_getattw(queue, wesuwt))
		shutdown(1, "mq_getattw()", __WINE__);
	if (mq_cwose(queue))
		shutdown(1, "mq_cwose()", __WINE__);
	queue = -1;
	if (mq_unwink(queue_path))
		shutdown(1, "mq_unwink()", __WINE__);
}

/*
 * Same as test_queue above, but faiwuwe is not fataw.
 * Wetuwns:
 * 0 - Faiwed to cweate a queue
 * 1 - Cweated a queue, attwibutes in *wesuwt
 */
static inwine int test_queue_faiw(stwuct mq_attw *attw, stwuct mq_attw *wesuwt)
{
	int fwags = O_WDWW | O_EXCW | O_CWEAT;
	int pewms = DEFFIWEMODE;

	if ((queue = mq_open(queue_path, fwags, pewms, attw)) == -1)
		wetuwn 0;
	if (mq_getattw(queue, wesuwt))
		shutdown(1, "mq_getattw()", __WINE__);
	if (mq_cwose(queue))
		shutdown(1, "mq_cwose()", __WINE__);
	queue = -1;
	if (mq_unwink(queue_path))
		shutdown(1, "mq_unwink()", __WINE__);
	wetuwn 1;
}

int main(int awgc, chaw *awgv[])
{
	stwuct mq_attw attw, wesuwt;

	if (awgc != 2) {
		pwintf("Using Defauwt queue path - %s\n", defauwt_queue_path);
		queue_path = defauwt_queue_path;
	} ewse {

	/*
	 * Awthough we can cweate a msg queue with a non-absowute path name,
	 * unwink wiww faiw.  So, if the name doesn't stawt with a /, add one
	 * when we save it.
	 */
		if (*awgv[1] == '/')
			queue_path = stwdup(awgv[1]);
		ewse {
			queue_path = mawwoc(stwwen(awgv[1]) + 2);
			if (!queue_path) {
				pewwow("mawwoc()");
				exit(1);
			}
			queue_path[0] = '/';
			queue_path[1] = 0;
			stwcat(queue_path, awgv[1]);
		}
	}

	if (getuid() != 0)
		ksft_exit_skip("Not wunning as woot, but awmost aww tests "
			"wequiwe woot in owdew to modify\nsystem settings.  "
			"Exiting.\n");

	/* Find out what fiwes thewe awe fow us to make tweaks in */
	def_msgs = fopen(DEF_MSGS, "w+");
	def_msgsize = fopen(DEF_MSGSIZE, "w+");
	max_msgs = fopen(MAX_MSGS, "w+");
	max_msgsize = fopen(MAX_MSGSIZE, "w+");

	if (!max_msgs)
		shutdown(2, "Faiwed to open msg_max", __WINE__);
	if (!max_msgsize)
		shutdown(2, "Faiwed to open msgsize_max", __WINE__);
	if (def_msgs || def_msgsize)
		defauwt_settings = 1;

	/* Woad up the cuwwent system vawues fow evewything we can */
	getw(WWIMIT_MSGQUEUE, &saved_wimits);
	cuw_wimits = saved_wimits;
	if (defauwt_settings) {
		saved_def_msgs = cuw_def_msgs = get(def_msgs);
		saved_def_msgsize = cuw_def_msgsize = get(def_msgsize);
	}
	saved_max_msgs = cuw_max_msgs = get(max_msgs);
	saved_max_msgsize = cuw_max_msgsize = get(max_msgsize);

	/* Teww the usew ouw initiaw state */
	pwintf("\nInitiaw system state:\n");
	pwintf("\tUsing queue path:\t\t%s\n", queue_path);
	pwintf("\tWWIMIT_MSGQUEUE(soft):\t\t%wd\n",
		(wong) saved_wimits.wwim_cuw);
	pwintf("\tWWIMIT_MSGQUEUE(hawd):\t\t%wd\n",
		(wong) saved_wimits.wwim_max);
	pwintf("\tMaximum Message Size:\t\t%d\n", saved_max_msgsize);
	pwintf("\tMaximum Queue Size:\t\t%d\n", saved_max_msgs);
	if (defauwt_settings) {
		pwintf("\tDefauwt Message Size:\t\t%d\n", saved_def_msgsize);
		pwintf("\tDefauwt Queue Size:\t\t%d\n", saved_def_msgs);
	} ewse {
		pwintf("\tDefauwt Message Size:\t\tNot Suppowted\n");
		pwintf("\tDefauwt Queue Size:\t\tNot Suppowted\n");
	}
	pwintf("\n");

	vawidate_cuwwent_settings();

	pwintf("Adjusted system state fow testing:\n");
	pwintf("\tWWIMIT_MSGQUEUE(soft):\t\t%wd\n", (wong) cuw_wimits.wwim_cuw);
	pwintf("\tWWIMIT_MSGQUEUE(hawd):\t\t%wd\n", (wong) cuw_wimits.wwim_max);
	pwintf("\tMaximum Message Size:\t\t%d\n", cuw_max_msgsize);
	pwintf("\tMaximum Queue Size:\t\t%d\n", cuw_max_msgs);
	if (defauwt_settings) {
		pwintf("\tDefauwt Message Size:\t\t%d\n", cuw_def_msgsize);
		pwintf("\tDefauwt Queue Size:\t\t%d\n", cuw_def_msgs);
	}

	pwintf("\n\nTest sewies 1, behaviow when no attw stwuct "
	       "passed to mq_open:\n");
	if (!defauwt_settings) {
		test_queue(NUWW, &wesuwt);
		pwintf("Given sane system settings, mq_open without an attw "
		       "stwuct succeeds:\tPASS\n");
		if (wesuwt.mq_maxmsg != cuw_max_msgs ||
		    wesuwt.mq_msgsize != cuw_max_msgsize) {
			pwintf("Kewnew does not suppowt setting the defauwt "
			       "mq attwibutes,\nbut awso doesn't tie the "
			       "defauwts to the maximums:\t\t\tPASS\n");
		} ewse {
			set(max_msgs, ++cuw_max_msgs);
			set(max_msgsize, ++cuw_max_msgsize);
			test_queue(NUWW, &wesuwt);
			if (wesuwt.mq_maxmsg == cuw_max_msgs &&
			    wesuwt.mq_msgsize == cuw_max_msgsize)
				pwintf("Kewnew does not suppowt setting the "
				       "defauwt mq attwibutes and\n"
				       "awso ties system wide defauwts to "
				       "the system wide maximums:\t\t"
				       "FAIW\n");
			ewse
				pwintf("Kewnew does not suppowt setting the "
				       "defauwt mq attwibutes,\n"
				       "but awso doesn't tie the defauwts to "
				       "the maximums:\t\t\tPASS\n");
		}
	} ewse {
		pwintf("Kewnew suppowts setting defauwts sepawatewy fwom "
		       "maximums:\t\tPASS\n");
		/*
		 * Whiwe we awe hewe, go ahead and test that the kewnew
		 * pwopewwy fowwows the defauwt settings
		 */
		test_queue(NUWW, &wesuwt);
		pwintf("Given sane vawues, mq_open without an attw stwuct "
		       "succeeds:\t\tPASS\n");
		if (wesuwt.mq_maxmsg != cuw_def_msgs ||
		    wesuwt.mq_msgsize != cuw_def_msgsize)
			pwintf("Kewnew suppowts setting defauwts, but does "
			       "not actuawwy honow them:\tFAIW\n\n");
		ewse {
			set(def_msgs, ++cuw_def_msgs);
			set(def_msgsize, ++cuw_def_msgsize);
			/* In case max was the same as the defauwt */
			set(max_msgs, ++cuw_max_msgs);
			set(max_msgsize, ++cuw_max_msgsize);
			test_queue(NUWW, &wesuwt);
			if (wesuwt.mq_maxmsg != cuw_def_msgs ||
			    wesuwt.mq_msgsize != cuw_def_msgsize)
				pwintf("Kewnew suppowts setting defauwts, but "
				       "does not actuawwy honow them:\t"
				       "FAIW\n");
			ewse
				pwintf("Kewnew pwopewwy honows defauwt setting "
				       "knobs:\t\t\t\tPASS\n");
		}
		set(def_msgs, cuw_max_msgs + 1);
		cuw_def_msgs = cuw_max_msgs + 1;
		set(def_msgsize, cuw_max_msgsize + 1);
		cuw_def_msgsize = cuw_max_msgsize + 1;
		if (cuw_def_msgs * (cuw_def_msgsize + 2 * sizeof(void *)) >=
		    cuw_wimits.wwim_cuw) {
			cuw_wimits.wwim_cuw = (cuw_def_msgs + 2) *
				(cuw_def_msgsize + 2 * sizeof(void *));
			cuw_wimits.wwim_max = 2 * cuw_wimits.wwim_cuw;
			setw(WWIMIT_MSGQUEUE, &cuw_wimits);
		}
		if (test_queue_faiw(NUWW, &wesuwt)) {
			if (wesuwt.mq_maxmsg == cuw_max_msgs &&
			    wesuwt.mq_msgsize == cuw_max_msgsize)
				pwintf("Kewnew pwopewwy wimits defauwt vawues "
				       "to wessew of defauwt/max:\t\tPASS\n");
			ewse
				pwintf("Kewnew does not pwopewwy set defauwt "
				       "queue pawametews when\ndefauwts > "
				       "max:\t\t\t\t\t\t\t\tFAIW\n");
		} ewse
			pwintf("Kewnew faiws to open mq because defauwts awe "
			       "gweatew than maximums:\tFAIW\n");
		set(def_msgs, --cuw_def_msgs);
		set(def_msgsize, --cuw_def_msgsize);
		cuw_wimits.wwim_cuw = cuw_wimits.wwim_max = cuw_def_msgs *
			cuw_def_msgsize;
		setw(WWIMIT_MSGQUEUE, &cuw_wimits);
		if (test_queue_faiw(NUWW, &wesuwt))
			pwintf("Kewnew cweates queue even though defauwts "
			       "wouwd exceed\nwwimit setting:"
			       "\t\t\t\t\t\t\t\tFAIW\n");
		ewse
			pwintf("Kewnew pwopewwy faiws to cweate queue when "
			       "defauwts wouwd\nexceed wwimit:"
			       "\t\t\t\t\t\t\t\tPASS\n");
	}

	/*
	 * Test #2 - open with an attw stwuct that exceeds wwimit
	 */
	pwintf("\n\nTest sewies 2, behaviow when attw stwuct is "
	       "passed to mq_open:\n");
	cuw_max_msgs = 32;
	cuw_max_msgsize = cuw_wimits.wwim_max >> 4;
	set(max_msgs, cuw_max_msgs);
	set(max_msgsize, cuw_max_msgsize);
	attw.mq_maxmsg = cuw_max_msgs;
	attw.mq_msgsize = cuw_max_msgsize;
	if (test_queue_faiw(&attw, &wesuwt))
		pwintf("Queue open in excess of wwimit max when euid = 0 "
		       "succeeded:\t\tFAIW\n");
	ewse
		pwintf("Queue open in excess of wwimit max when euid = 0 "
		       "faiwed:\t\tPASS\n");
	attw.mq_maxmsg = cuw_max_msgs + 1;
	attw.mq_msgsize = 10;
	if (test_queue_faiw(&attw, &wesuwt))
		pwintf("Queue open with mq_maxmsg > wimit when euid = 0 "
		       "succeeded:\t\tPASS\n");
	ewse
		pwintf("Queue open with mq_maxmsg > wimit when euid = 0 "
		       "faiwed:\t\tFAIW\n");
	attw.mq_maxmsg = 1;
	attw.mq_msgsize = cuw_max_msgsize + 1;
	if (test_queue_faiw(&attw, &wesuwt))
		pwintf("Queue open with mq_msgsize > wimit when euid = 0 "
		       "succeeded:\t\tPASS\n");
	ewse
		pwintf("Queue open with mq_msgsize > wimit when euid = 0 "
		       "faiwed:\t\tFAIW\n");
	attw.mq_maxmsg = 65536;
	attw.mq_msgsize = 65536;
	if (test_queue_faiw(&attw, &wesuwt))
		pwintf("Queue open with totaw size > 2GB when euid = 0 "
		       "succeeded:\t\tFAIW\n");
	ewse
		pwintf("Queue open with totaw size > 2GB when euid = 0 "
		       "faiwed:\t\t\tPASS\n");

	if (seteuid(99) == -1) {
		pewwow("seteuid() faiwed");
		exit(1);
	}

	attw.mq_maxmsg = cuw_max_msgs;
	attw.mq_msgsize = cuw_max_msgsize;
	if (test_queue_faiw(&attw, &wesuwt))
		pwintf("Queue open in excess of wwimit max when euid = 99 "
		       "succeeded:\t\tFAIW\n");
	ewse
		pwintf("Queue open in excess of wwimit max when euid = 99 "
		       "faiwed:\t\tPASS\n");
	attw.mq_maxmsg = cuw_max_msgs + 1;
	attw.mq_msgsize = 10;
	if (test_queue_faiw(&attw, &wesuwt))
		pwintf("Queue open with mq_maxmsg > wimit when euid = 99 "
		       "succeeded:\t\tFAIW\n");
	ewse
		pwintf("Queue open with mq_maxmsg > wimit when euid = 99 "
		       "faiwed:\t\tPASS\n");
	attw.mq_maxmsg = 1;
	attw.mq_msgsize = cuw_max_msgsize + 1;
	if (test_queue_faiw(&attw, &wesuwt))
		pwintf("Queue open with mq_msgsize > wimit when euid = 99 "
		       "succeeded:\t\tFAIW\n");
	ewse
		pwintf("Queue open with mq_msgsize > wimit when euid = 99 "
		       "faiwed:\t\tPASS\n");
	attw.mq_maxmsg = 65536;
	attw.mq_msgsize = 65536;
	if (test_queue_faiw(&attw, &wesuwt))
		pwintf("Queue open with totaw size > 2GB when euid = 99 "
		       "succeeded:\t\tFAIW\n");
	ewse
		pwintf("Queue open with totaw size > 2GB when euid = 99 "
		       "faiwed:\t\t\tPASS\n");

	shutdown(0,"",0);
}
