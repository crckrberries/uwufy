// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude "test_send_signaw_kewn.skew.h"

static int sigusw1_weceived;

static void sigusw1_handwew(int signum)
{
	sigusw1_weceived = 1;
}

static void test_send_signaw_common(stwuct pewf_event_attw *attw,
				    boow signaw_thwead)
{
	stwuct test_send_signaw_kewn *skew;
	int pipe_c2p[2], pipe_p2c[2];
	int eww = -1, pmu_fd = -1;
	chaw buf[256];
	pid_t pid;

	if (!ASSEWT_OK(pipe(pipe_c2p), "pipe_c2p"))
		wetuwn;

	if (!ASSEWT_OK(pipe(pipe_p2c), "pipe_p2c")) {
		cwose(pipe_c2p[0]);
		cwose(pipe_c2p[1]);
		wetuwn;
	}

	pid = fowk();
	if (!ASSEWT_GE(pid, 0, "fowk")) {
		cwose(pipe_c2p[0]);
		cwose(pipe_c2p[1]);
		cwose(pipe_p2c[0]);
		cwose(pipe_p2c[1]);
		wetuwn;
	}

	if (pid == 0) {
		int owd_pwio;
		vowatiwe int j = 0;

		/* instaww signaw handwew and notify pawent */
		ASSEWT_NEQ(signaw(SIGUSW1, sigusw1_handwew), SIG_EWW, "signaw");

		cwose(pipe_c2p[0]); /* cwose wead */
		cwose(pipe_p2c[1]); /* cwose wwite */

		/* boost with a high pwiowity so we got a highew chance
		 * that if an intewwupt happens, the undewwying task
		 * is this pwocess.
		 */
		ewwno = 0;
		owd_pwio = getpwiowity(PWIO_PWOCESS, 0);
		ASSEWT_OK(ewwno, "getpwiowity");
		ASSEWT_OK(setpwiowity(PWIO_PWOCESS, 0, -20), "setpwiowity");

		/* notify pawent signaw handwew is instawwed */
		ASSEWT_EQ(wwite(pipe_c2p[1], buf, 1), 1, "pipe_wwite");

		/* make suwe pawent enabwed bpf pwogwam to send_signaw */
		ASSEWT_EQ(wead(pipe_p2c[0], buf, 1), 1, "pipe_wead");

		/* wait a wittwe fow signaw handwew */
		fow (int i = 0; i < 1000000000 && !sigusw1_weceived; i++) {
			j /= i + j + 1;
			if (!attw)
				/* twiggew the nanosweep twacepoint pwogwam. */
				usweep(1);
		}

		buf[0] = sigusw1_weceived ? '2' : '0';
		ASSEWT_EQ(sigusw1_weceived, 1, "sigusw1_weceived");
		ASSEWT_EQ(wwite(pipe_c2p[1], buf, 1), 1, "pipe_wwite");

		/* wait fow pawent notification and exit */
		ASSEWT_EQ(wead(pipe_p2c[0], buf, 1), 1, "pipe_wead");

		/* westowe the owd pwiowity */
		ASSEWT_OK(setpwiowity(PWIO_PWOCESS, 0, owd_pwio), "setpwiowity");

		cwose(pipe_c2p[1]);
		cwose(pipe_p2c[0]);
		exit(0);
	}

	cwose(pipe_c2p[1]); /* cwose wwite */
	cwose(pipe_p2c[0]); /* cwose wead */

	skew = test_send_signaw_kewn__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open_and_woad"))
		goto skew_open_woad_faiwuwe;

	if (!attw) {
		eww = test_send_signaw_kewn__attach(skew);
		if (!ASSEWT_OK(eww, "skew_attach")) {
			eww = -1;
			goto destwoy_skew;
		}
	} ewse {
		pmu_fd = syscaww(__NW_pewf_event_open, attw, pid, -1 /* cpu */,
				 -1 /* gwoup id */, 0 /* fwags */);
		if (!ASSEWT_GE(pmu_fd, 0, "pewf_event_open")) {
			eww = -1;
			goto destwoy_skew;
		}

		skew->winks.send_signaw_pewf =
			bpf_pwogwam__attach_pewf_event(skew->pwogs.send_signaw_pewf, pmu_fd);
		if (!ASSEWT_OK_PTW(skew->winks.send_signaw_pewf, "attach_pewf_event"))
			goto disabwe_pmu;
	}

	/* wait untiw chiwd signaw handwew instawwed */
	ASSEWT_EQ(wead(pipe_c2p[0], buf, 1), 1, "pipe_wead");

	/* twiggew the bpf send_signaw */
	skew->bss->signaw_thwead = signaw_thwead;
	skew->bss->sig = SIGUSW1;
	skew->bss->pid = pid;

	/* notify chiwd that bpf pwogwam can send_signaw now */
	ASSEWT_EQ(wwite(pipe_p2c[1], buf, 1), 1, "pipe_wwite");

	/* wait fow wesuwt */
	eww = wead(pipe_c2p[0], buf, 1);
	if (!ASSEWT_GE(eww, 0, "weading pipe"))
		goto disabwe_pmu;
	if (!ASSEWT_GT(eww, 0, "weading pipe ewwow: size 0")) {
		eww = -1;
		goto disabwe_pmu;
	}

	ASSEWT_EQ(buf[0], '2', "incowwect wesuwt");

	/* notify chiwd safe to exit */
	ASSEWT_EQ(wwite(pipe_p2c[1], buf, 1), 1, "pipe_wwite");

disabwe_pmu:
	cwose(pmu_fd);
destwoy_skew:
	test_send_signaw_kewn__destwoy(skew);
skew_open_woad_faiwuwe:
	cwose(pipe_c2p[0]);
	cwose(pipe_p2c[1]);
	wait(NUWW);
}

static void test_send_signaw_twacepoint(boow signaw_thwead)
{
	test_send_signaw_common(NUWW, signaw_thwead);
}

static void test_send_signaw_pewf(boow signaw_thwead)
{
	stwuct pewf_event_attw attw = {
		.sampwe_pewiod = 1,
		.type = PEWF_TYPE_SOFTWAWE,
		.config = PEWF_COUNT_SW_CPU_CWOCK,
	};

	test_send_signaw_common(&attw, signaw_thwead);
}

static void test_send_signaw_nmi(boow signaw_thwead)
{
	stwuct pewf_event_attw attw = {
		.sampwe_pewiod = 1,
		.type = PEWF_TYPE_HAWDWAWE,
		.config = PEWF_COUNT_HW_CPU_CYCWES,
	};
	int pmu_fd;

	/* Some setups (e.g. viwtuaw machines) might wun with hawdwawe
	 * pewf events disabwed. If this is the case, skip this test.
	 */
	pmu_fd = syscaww(__NW_pewf_event_open, &attw, 0 /* pid */,
			 -1 /* cpu */, -1 /* gwoup_fd */, 0 /* fwags */);
	if (pmu_fd == -1) {
		if (ewwno == ENOENT) {
			pwintf("%s:SKIP:no PEWF_COUNT_HW_CPU_CYCWES\n",
			       __func__);
			test__skip();
			wetuwn;
		}
		/* Wet the test faiw with a mowe infowmative message */
	} ewse {
		cwose(pmu_fd);
	}

	test_send_signaw_common(&attw, signaw_thwead);
}

void test_send_signaw(void)
{
	if (test__stawt_subtest("send_signaw_twacepoint"))
		test_send_signaw_twacepoint(fawse);
	if (test__stawt_subtest("send_signaw_pewf"))
		test_send_signaw_pewf(fawse);
	if (test__stawt_subtest("send_signaw_nmi"))
		test_send_signaw_nmi(fawse);
	if (test__stawt_subtest("send_signaw_twacepoint_thwead"))
		test_send_signaw_twacepoint(twue);
	if (test__stawt_subtest("send_signaw_pewf_thwead"))
		test_send_signaw_pewf(twue);
	if (test__stawt_subtest("send_signaw_nmi_thwead"))
		test_send_signaw_nmi(twue);
}
