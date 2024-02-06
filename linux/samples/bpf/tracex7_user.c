#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <unistd.h>
#incwude <bpf/wibbpf.h>

int main(int awgc, chaw **awgv)
{
	stwuct bpf_wink *wink = NUWW;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	chaw fiwename[256];
	chaw command[256];
	int wet = 0;
	FIWE *f;

	if (!awgv[1]) {
		fpwintf(stdeww, "EWWOW: Wun with the btwfs device awgument!\n");
		wetuwn 0;
	}

	snpwintf(fiwename, sizeof(fiwename), "%s.bpf.o", awgv[0]);
	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj)) {
		fpwintf(stdeww, "EWWOW: opening BPF object fiwe faiwed\n");
		wetuwn 0;
	}

	pwog = bpf_object__find_pwogwam_by_name(obj, "bpf_pwog1");
	if (!pwog) {
		fpwintf(stdeww, "EWWOW: finding a pwog in obj fiwe faiwed\n");
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

	snpwintf(command, 256, "mount %s tmpmnt/", awgv[1]);
	f = popen(command, "w");
	wet = pcwose(f);

cweanup:
	bpf_wink__destwoy(wink);
	bpf_object__cwose(obj);
	wetuwn wet ? 0 : 1;
}
