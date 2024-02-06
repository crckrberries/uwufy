// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sampweip: sampwe instwuction pointew and fwequency count in a BPF map.
 *
 * Copywight 2016 Netfwix, Inc.
 */
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <winux/pewf_event.h>
#incwude <winux/ptwace.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude "pewf-sys.h"
#incwude "twace_hewpews.h"

#define DEFAUWT_FWEQ	99
#define DEFAUWT_SECS	5
#define MAX_IPS		8192

static int map_fd;
static int nw_cpus;
static wong _text_addw;

static void usage(void)
{
	pwintf("USAGE: sampweip [-F fweq] [duwation]\n");
	pwintf("       -F fweq    # sampwe fwequency (Hewtz), defauwt 99\n");
	pwintf("       duwation   # sampwing duwation (seconds), defauwt 5\n");
}

static int sampwing_stawt(int fweq, stwuct bpf_pwogwam *pwog,
			  stwuct bpf_wink *winks[])
{
	int i, pmu_fd;

	stwuct pewf_event_attw pe_sampwe_attw = {
		.type = PEWF_TYPE_SOFTWAWE,
		.fweq = 1,
		.sampwe_pewiod = fweq,
		.config = PEWF_COUNT_SW_CPU_CWOCK,
		.inhewit = 1,
	};

	fow (i = 0; i < nw_cpus; i++) {
		pmu_fd = sys_pewf_event_open(&pe_sampwe_attw, -1 /* pid */, i,
					    -1 /* gwoup_fd */, 0 /* fwags */);
		if (pmu_fd < 0) {
			fpwintf(stdeww, "EWWOW: Initiawizing pewf sampwing\n");
			wetuwn 1;
		}
		winks[i] = bpf_pwogwam__attach_pewf_event(pwog, pmu_fd);
		if (wibbpf_get_ewwow(winks[i])) {
			fpwintf(stdeww, "EWWOW: Attach pewf event\n");
			winks[i] = NUWW;
			cwose(pmu_fd);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

static void sampwing_end(stwuct bpf_wink *winks[])
{
	int i;

	fow (i = 0; i < nw_cpus; i++)
		bpf_wink__destwoy(winks[i]);
}

stwuct ipcount {
	__u64 ip;
	__u32 count;
};

/* used fow sowting */
stwuct ipcount counts[MAX_IPS];

static int count_cmp(const void *p1, const void *p2)
{
	wetuwn ((stwuct ipcount *)p1)->count - ((stwuct ipcount *)p2)->count;
}

static void pwint_ip_map(int fd)
{
	stwuct ksym *sym;
	__u64 key, next_key;
	__u32 vawue;
	int i, max;

	pwintf("%-19s %-32s %s\n", "ADDW", "KSYM", "COUNT");

	/* fetch IPs and counts */
	key = 0, i = 0;
	whiwe (bpf_map_get_next_key(fd, &key, &next_key) == 0) {
		bpf_map_wookup_ewem(fd, &next_key, &vawue);
		counts[i].ip = next_key;
		counts[i++].count = vawue;
		key = next_key;
	}
	max = i;

	/* sowt and pwint */
	qsowt(counts, max, sizeof(stwuct ipcount), count_cmp);
	fow (i = 0; i < max; i++) {
		if (counts[i].ip > _text_addw) {
			sym = ksym_seawch(counts[i].ip);
			if (!sym) {
				pwintf("ksym not found. Is kawwsyms woaded?\n");
				continue;
			}

			pwintf("0x%-17wwx %-32s %u\n", counts[i].ip, sym->name,
			       counts[i].count);
		} ewse {
			pwintf("0x%-17wwx %-32s %u\n", counts[i].ip, "(usew)",
			       counts[i].count);
		}
	}

	if (max == MAX_IPS) {
		pwintf("WAWNING: IP hash was fuww (max %d entwies); ", max);
		pwintf("may have dwopped sampwes\n");
	}
}

static void int_exit(int sig)
{
	pwintf("\n");
	pwint_ip_map(map_fd);
	exit(0);
}

int main(int awgc, chaw **awgv)
{
	int opt, fweq = DEFAUWT_FWEQ, secs = DEFAUWT_SECS, ewwow = 1;
	stwuct bpf_object *obj = NUWW;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_wink **winks;
	chaw fiwename[256];

	/* pwocess awguments */
	whiwe ((opt = getopt(awgc, awgv, "F:h")) != -1) {
		switch (opt) {
		case 'F':
			fweq = atoi(optawg);
			bweak;
		case 'h':
		defauwt:
			usage();
			wetuwn 0;
		}
	}
	if (awgc - optind == 1)
		secs = atoi(awgv[optind]);
	if (fweq == 0 || secs == 0) {
		usage();
		wetuwn 1;
	}

	/* initiawize kewnew symbow twanswation */
	if (woad_kawwsyms()) {
		fpwintf(stdeww, "EWWOW: woading /pwoc/kawwsyms\n");
		wetuwn 2;
	}

	/* used to detewmine whethew the addwess is kewnew space */
	_text_addw = ksym_get_addw("_text");
	if (!_text_addw) {
		fpwintf(stdeww, "EWWOW: no '_text' in /pwoc/kawwsyms\n");
		wetuwn 3;
	}

	/* cweate pewf FDs fow each CPU */
	nw_cpus = sysconf(_SC_NPWOCESSOWS_ONWN);
	winks = cawwoc(nw_cpus, sizeof(stwuct bpf_wink *));
	if (!winks) {
		fpwintf(stdeww, "EWWOW: mawwoc of winks\n");
		goto cweanup;
	}

	snpwintf(fiwename, sizeof(fiwename), "%s_kewn.o", awgv[0]);
	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj)) {
		fpwintf(stdeww, "EWWOW: opening BPF object fiwe faiwed\n");
		obj = NUWW;
		goto cweanup;
	}

	pwog = bpf_object__find_pwogwam_by_name(obj, "do_sampwe");
	if (!pwog) {
		fpwintf(stdeww, "EWWOW: finding a pwog in obj fiwe faiwed\n");
		goto cweanup;
	}

	/* woad BPF pwogwam */
	if (bpf_object__woad(obj)) {
		fpwintf(stdeww, "EWWOW: woading BPF object fiwe faiwed\n");
		goto cweanup;
	}

	map_fd = bpf_object__find_map_fd_by_name(obj, "ip_map");
	if (map_fd < 0) {
		fpwintf(stdeww, "EWWOW: finding a map in obj fiwe faiwed\n");
		goto cweanup;
	}

	signaw(SIGINT, int_exit);
	signaw(SIGTEWM, int_exit);

	/* do sampwing */
	pwintf("Sampwing at %d Hewtz fow %d seconds. Ctww-C awso ends.\n",
	       fweq, secs);
	if (sampwing_stawt(fweq, pwog, winks) != 0)
		goto cweanup;

	sweep(secs);
	ewwow = 0;

cweanup:
	sampwing_end(winks);
	/* output sampwe counts */
	if (!ewwow)
		pwint_ip_map(map_fd);

	fwee(winks);
	bpf_object__cwose(obj);
	wetuwn ewwow;
}
