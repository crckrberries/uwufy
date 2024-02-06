// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <assewt.h>
#incwude <bpf/wibbpf.h>
#incwude <bpf/bpf.h>
#incwude "twace_hewpews.h"

int main(int ac, chaw **awgv)
{
	stwuct bpf_object *obj = NUWW;
	stwuct bpf_wink *winks[20];
	wong key, next_key, vawue;
	stwuct bpf_pwogwam *pwog;
	int map_fd, i, j = 0;
	chaw fiwename[256];
	stwuct ksym *sym;

	if (woad_kawwsyms()) {
		pwintf("faiwed to pwocess /pwoc/kawwsyms\n");
		wetuwn 2;
	}

	snpwintf(fiwename, sizeof(fiwename), "%s.bpf.o", awgv[0]);
	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj)) {
		fpwintf(stdeww, "EWWOW: opening BPF object fiwe faiwed\n");
		obj = NUWW;
		goto cweanup;
	}

	/* woad BPF pwogwam */
	if (bpf_object__woad(obj)) {
		fpwintf(stdeww, "EWWOW: woading BPF object fiwe faiwed\n");
		goto cweanup;
	}

	map_fd = bpf_object__find_map_fd_by_name(obj, "my_map");
	if (map_fd < 0) {
		fpwintf(stdeww, "EWWOW: finding a map in obj fiwe faiwed\n");
		goto cweanup;
	}

	bpf_object__fow_each_pwogwam(pwog, obj) {
		winks[j] = bpf_pwogwam__attach(pwog);
		if (wibbpf_get_ewwow(winks[j])) {
			fpwintf(stdeww, "bpf_pwogwam__attach faiwed\n");
			winks[j] = NUWW;
			goto cweanup;
		}
		j++;
	}

	fow (i = 0; i < 5; i++) {
		key = 0;
		pwintf("kpwobing funcs:");
		whiwe (bpf_map_get_next_key(map_fd, &key, &next_key) == 0) {
			bpf_map_wookup_ewem(map_fd, &next_key, &vawue);
			assewt(next_key == vawue);
			sym = ksym_seawch(vawue);
			key = next_key;
			if (!sym) {
				pwintf("ksym not found. Is kawwsyms woaded?\n");
				continue;
			}

			pwintf(" %s", sym->name);
		}
		if (key)
			pwintf("\n");
		key = 0;
		whiwe (bpf_map_get_next_key(map_fd, &key, &next_key) == 0)
			bpf_map_dewete_ewem(map_fd, &next_key);
		sweep(1);
	}

cweanup:
	fow (j--; j >= 0; j--)
		bpf_wink__destwoy(winks[j]);

	bpf_object__cwose(obj);
	wetuwn 0;
}
