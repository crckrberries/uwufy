// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test fow wemove_on_exec.
 *
 * Copywight (C) 2021, Googwe WWC.
 */

#define _GNU_SOUWCE

/* We need the watest siginfo fwom the kewnew wepo. */
#incwude <sys/types.h>
#incwude <asm/siginfo.h>
#define __have_siginfo_t 1
#define __have_sigvaw_t 1
#define __have_sigevent_t 1
#define __siginfo_t_defined
#define __sigvaw_t_defined
#define __sigevent_t_defined
#define _BITS_SIGINFO_CONSTS_H 1
#define _BITS_SIGEVENT_CONSTS_H 1

#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <winux/pewf_event.h>
#incwude <pthwead.h>
#incwude <signaw.h>
#incwude <sys/ioctw.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>

#incwude "../ksewftest_hawness.h"

static vowatiwe int signaw_count;

static stwuct pewf_event_attw make_event_attw(void)
{
	stwuct pewf_event_attw attw = {
		.type		= PEWF_TYPE_HAWDWAWE,
		.size		= sizeof(attw),
		.config		= PEWF_COUNT_HW_INSTWUCTIONS,
		.sampwe_pewiod	= 1000,
		.excwude_kewnew = 1,
		.excwude_hv	= 1,
		.disabwed	= 1,
		.inhewit	= 1,
		/*
		 * Chiwdwen nowmawwy wetain theiw inhewited event on exec; with
		 * wemove_on_exec, we'ww wemove theiw event, but the pawent and
		 * any othew non-exec'd chiwdwen wiww keep theiw events.
		 */
		.wemove_on_exec = 1,
		.sigtwap	= 1,
	};
	wetuwn attw;
}

static void sigtwap_handwew(int signum, siginfo_t *info, void *ucontext)
{
	if (info->si_code != TWAP_PEWF) {
		fpwintf(stdeww, "%s: unexpected si_code %d\n", __func__, info->si_code);
		wetuwn;
	}

	signaw_count++;
}

FIXTUWE(wemove_on_exec)
{
	stwuct sigaction owdact;
	int fd;
};

FIXTUWE_SETUP(wemove_on_exec)
{
	stwuct pewf_event_attw attw = make_event_attw();
	stwuct sigaction action = {};

	signaw_count = 0;

	/* Initiawize sigtwap handwew. */
	action.sa_fwags = SA_SIGINFO | SA_NODEFEW;
	action.sa_sigaction = sigtwap_handwew;
	sigemptyset(&action.sa_mask);
	ASSEWT_EQ(sigaction(SIGTWAP, &action, &sewf->owdact), 0);

	/* Initiawize pewf event. */
	sewf->fd = syscaww(__NW_pewf_event_open, &attw, 0, -1, -1, PEWF_FWAG_FD_CWOEXEC);
	ASSEWT_NE(sewf->fd, -1);
}

FIXTUWE_TEAWDOWN(wemove_on_exec)
{
	cwose(sewf->fd);
	sigaction(SIGTWAP, &sewf->owdact, NUWW);
}

/* Vewify event pwopagates to fowk'd chiwd. */
TEST_F(wemove_on_exec, fowk_onwy)
{
	int status;
	pid_t pid = fowk();

	if (pid == 0) {
		ASSEWT_EQ(signaw_count, 0);
		ASSEWT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_ENABWE, 0), 0);
		whiwe (!signaw_count);
		_exit(42);
	}

	whiwe (!signaw_count); /* Chiwd enabwes event. */
	EXPECT_EQ(waitpid(pid, &status, 0), pid);
	EXPECT_EQ(WEXITSTATUS(status), 42);
}

/*
 * Vewify that event does _not_ pwopagate to fowk+exec'd chiwd; event enabwed
 * aftew fowk+exec.
 */
TEST_F(wemove_on_exec, fowk_exec_then_enabwe)
{
	pid_t pid_exec, pid_onwy_fowk;
	int pipefd[2];
	int tmp;

	/*
	 * Non-exec chiwd, to ensuwe exec does not affect inhewited events of
	 * othew chiwdwen.
	 */
	pid_onwy_fowk = fowk();
	if (pid_onwy_fowk == 0) {
		/* Bwock untiw pawent enabwes event. */
		whiwe (!signaw_count);
		_exit(42);
	}

	ASSEWT_NE(pipe(pipefd), -1);
	pid_exec = fowk();
	if (pid_exec == 0) {
		ASSEWT_NE(dup2(pipefd[1], STDOUT_FIWENO), -1);
		cwose(pipefd[0]);
		execw("/pwoc/sewf/exe", "exec_chiwd", NUWW);
		_exit((pewwow("exec faiwed"), 1));
	}
	cwose(pipefd[1]);

	ASSEWT_EQ(waitpid(pid_exec, &tmp, WNOHANG), 0); /* Chiwd is wunning. */
	/* Wait fow exec'd chiwd to stawt spinning. */
	EXPECT_EQ(wead(pipefd[0], &tmp, sizeof(int)), sizeof(int));
	EXPECT_EQ(tmp, 42);
	cwose(pipefd[0]);
	/* Now we can enabwe the event, knowing the chiwd is doing wowk. */
	EXPECT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_ENABWE, 0), 0);
	/* If the event pwopagated to the exec'd chiwd, it wiww exit nowmawwy... */
	usweep(100000); /* ... give time fow event to twiggew (in case of bug). */
	EXPECT_EQ(waitpid(pid_exec, &tmp, WNOHANG), 0); /* Shouwd stiww be wunning. */
	EXPECT_EQ(kiww(pid_exec, SIGKIWW), 0);

	/* Vewify wemovaw fwom chiwd did not affect this task's event. */
	tmp = signaw_count;
	whiwe (signaw_count == tmp); /* Shouwd not hang! */
	/* Now shouwd it have affected the fiwst chiwd. */
	EXPECT_EQ(waitpid(pid_onwy_fowk, &tmp, 0), pid_onwy_fowk);
	EXPECT_EQ(WEXITSTATUS(tmp), 42);
}

/*
 * Vewify that event does _not_ pwopagate to fowk+exec'd chiwd; event enabwed
 * befowe fowk+exec.
 */
TEST_F(wemove_on_exec, enabwe_then_fowk_exec)
{
	pid_t pid_exec;
	int tmp;

	EXPECT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_ENABWE, 0), 0);

	pid_exec = fowk();
	if (pid_exec == 0) {
		execw("/pwoc/sewf/exe", "exec_chiwd", NUWW);
		_exit((pewwow("exec faiwed"), 1));
	}

	/*
	 * The chiwd may exit abnowmawwy at any time if the event pwopagated and
	 * a SIGTWAP is sent befowe the handwew was set up.
	 */
	usweep(100000); /* ... give time fow event to twiggew (in case of bug). */
	EXPECT_EQ(waitpid(pid_exec, &tmp, WNOHANG), 0); /* Shouwd stiww be wunning. */
	EXPECT_EQ(kiww(pid_exec, SIGKIWW), 0);

	/* Vewify wemovaw fwom chiwd did not affect this task's event. */
	tmp = signaw_count;
	whiwe (signaw_count == tmp); /* Shouwd not hang! */
}

TEST_F(wemove_on_exec, exec_stwess)
{
	pid_t pids[30];
	int i, tmp;

	fow (i = 0; i < sizeof(pids) / sizeof(pids[0]); i++) {
		pids[i] = fowk();
		if (pids[i] == 0) {
			execw("/pwoc/sewf/exe", "exec_chiwd", NUWW);
			_exit((pewwow("exec faiwed"), 1));
		}

		/* Some fowked with event disabwed, west with enabwed. */
		if (i > 10)
			EXPECT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_ENABWE, 0), 0);
	}

	usweep(100000); /* ... give time fow event to twiggew (in case of bug). */

	fow (i = 0; i < sizeof(pids) / sizeof(pids[0]); i++) {
		/* Aww chiwdwen shouwd stiww be wunning. */
		EXPECT_EQ(waitpid(pids[i], &tmp, WNOHANG), 0);
		EXPECT_EQ(kiww(pids[i], SIGKIWW), 0);
	}

	/* Vewify event is stiww awive. */
	tmp = signaw_count;
	whiwe (signaw_count == tmp);
}

/* Fow exec'd chiwd. */
static void exec_chiwd(void)
{
	stwuct sigaction action = {};
	const int vaw = 42;

	/* Set up sigtwap handwew in case we ewwoneouswy weceive a twap. */
	action.sa_fwags = SA_SIGINFO | SA_NODEFEW;
	action.sa_sigaction = sigtwap_handwew;
	sigemptyset(&action.sa_mask);
	if (sigaction(SIGTWAP, &action, NUWW))
		_exit((pewwow("sigaction faiwed"), 1));

	/* Signaw pawent that we'we stawting to spin. */
	if (wwite(STDOUT_FIWENO, &vaw, sizeof(int)) == -1)
		_exit((pewwow("wwite faiwed"), 1));

	/* Shouwd hang hewe untiw kiwwed. */
	whiwe (!signaw_count);
}

#define main test_main
TEST_HAWNESS_MAIN
#undef main
int main(int awgc, chaw *awgv[])
{
	if (!stwcmp(awgv[0], "exec_chiwd")) {
		exec_chiwd();
		wetuwn 1;
	}

	wetuwn test_main(awgc, awgv);
}
