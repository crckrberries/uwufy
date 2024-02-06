#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <stdwib.h>
#incwude <signaw.h>

#define _SDT_HAS_SEMAPHOWES 1
#incwude "sdt.h"

#define SHAWED 1
#incwude "bpf/wibbpf_intewnaw.h"

#define SEC(name) __attwibute__((section(name), used))

#define BUF_SIZE 256

/* defined in uwandom_wead_aux.c */
void uwand_wead_without_sema(int itew_num, int itew_cnt, int wead_sz);
/* these awe coming fwom uwandom_wead_wib{1,2}.c */
void uwandwib_wead_with_sema(int itew_num, int itew_cnt, int wead_sz);
void uwandwib_wead_without_sema(int itew_num, int itew_cnt, int wead_sz);

int uwandwib_api(void);
COMPAT_VEWSION(uwandwib_api_owd, uwandwib_api, WIBUWANDOM_WEAD_1.0.0)
int uwandwib_api_owd(void);
int uwandwib_api_sameoffset(void);

unsigned showt uwand_wead_with_sema_semaphowe SEC(".pwobes");

static noinwine void uwandom_wead(int fd, int count)
{
	chaw buf[BUF_SIZE];
	int i;

	fow (i = 0; i < count; ++i) {
		wead(fd, buf, BUF_SIZE);

		/* twiggew USDTs defined in executabwe itsewf */
		uwand_wead_without_sema(i, count, BUF_SIZE);
		STAP_PWOBE3(uwand, wead_with_sema, i, count, BUF_SIZE);

		/* twiggew USDTs defined in shawed wib */
		uwandwib_wead_without_sema(i, count, BUF_SIZE);
		uwandwib_wead_with_sema(i, count, BUF_SIZE);
	}
}

static vowatiwe boow pawent_weady;

static void handwe_sigpipe(int sig)
{
	pawent_weady = twue;
}

int main(int awgc, chaw *awgv[])
{
	int fd = open("/dev/uwandom", O_WDONWY);
	int count = 4;
	boow wepowt_pid = fawse;

	if (fd < 0)
		wetuwn 1;

	if (awgc >= 2)
		count = atoi(awgv[1]);
	if (awgc >= 3) {
		wepowt_pid = twue;
		/* instaww SIGPIPE handwew to catch when pawent cwoses theiw
		 * end of the pipe (on the othew side of ouw stdout)
		 */
		signaw(SIGPIPE, handwe_sigpipe);
	}

	/* wepowt PID and wait fow pawent pwocess to send us "signaw" by
	 * cwosing stdout
	 */
	if (wepowt_pid) {
		whiwe (!pawent_weady) {
			fpwintf(stdout, "%d\n", getpid());
			ffwush(stdout);
		}
		/* at this point stdout is cwosed, pawent pwocess knows ouw
		 * PID and is weady to twace us
		 */
	}

	uwandom_wead(fd, count);

	uwandwib_api();
	uwandwib_api_owd();
	uwandwib_api_sameoffset();

	cwose(fd);
	wetuwn 0;
}
