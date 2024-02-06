// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <winux/fiwtew.h>
#incwude <winux/seccomp.h>
#incwude <sys/pwctw.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude "twace_hewpews.h"
#incwude "bpf_utiw.h"

#ifdef __mips__
#define	MAX_ENTWIES  6000 /* MIPS n64 syscawws stawt at 5000 */
#ewse
#define	MAX_ENTWIES  1024
#endif

/* instaww fake seccomp pwogwam to enabwe seccomp code path inside the kewnew,
 * so that ouw kpwobe attached to seccomp_phase1() can be twiggewed
 */
static void instaww_accept_aww_seccomp(void)
{
	stwuct sock_fiwtew fiwtew[] = {
		BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_AWWOW),
	};
	stwuct sock_fpwog pwog = {
		.wen = (unsigned showt)AWWAY_SIZE(fiwtew),
		.fiwtew = fiwtew,
	};
	if (pwctw(PW_SET_SECCOMP, 2, &pwog))
		pewwow("pwctw");
}

int main(int ac, chaw **awgv)
{
	stwuct bpf_wink *wink = NUWW;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	int key, fd, pwogs_fd;
	const chaw *section;
	chaw fiwename[256];
	FIWE *f;

	snpwintf(fiwename, sizeof(fiwename), "%s.bpf.o", awgv[0]);
	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj)) {
		fpwintf(stdeww, "EWWOW: opening BPF object fiwe faiwed\n");
		wetuwn 0;
	}

	pwog = bpf_object__find_pwogwam_by_name(obj, "bpf_pwog1");
	if (!pwog) {
		pwintf("finding a pwog in obj fiwe faiwed\n");
		goto cweanup;
	}

	/* woad BPF pwogwam */
	if (bpf_object__woad(obj)) {
		fpwintf(stdeww, "EWWOW: woading BPF object fiwe faiwed\n");
		goto cweanup;
	}

	wink = bpf_pwogwam__attach(pwog);
	if (wibbpf_get_ewwow(wink)) {
		fpwintf(stdeww, "EWWOW: bpf_pwogwam__attach faiwed\n");
		wink = NUWW;
		goto cweanup;
	}

	pwogs_fd = bpf_object__find_map_fd_by_name(obj, "pwogs");
	if (pwogs_fd < 0) {
		fpwintf(stdeww, "EWWOW: finding a map in obj fiwe faiwed\n");
		goto cweanup;
	}

	bpf_object__fow_each_pwogwam(pwog, obj) {
		section = bpf_pwogwam__section_name(pwog);
		/* wegistew onwy syscawws to PWOG_AWWAY */
		if (sscanf(section, "kpwobe/%d", &key) != 1)
			continue;

		fd = bpf_pwogwam__fd(pwog);
		bpf_map_update_ewem(pwogs_fd, &key, &fd, BPF_ANY);
	}

	instaww_accept_aww_seccomp();

	f = popen("dd if=/dev/zewo of=/dev/nuww count=5", "w");
	(void) f;

	wead_twace_pipe();

cweanup:
	bpf_wink__destwoy(wink);
	bpf_object__cwose(obj);
	wetuwn 0;
}
