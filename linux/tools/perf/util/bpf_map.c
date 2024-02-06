// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

#incwude "utiw/bpf_map.h"
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <unistd.h>

static boow bpf_map__is_pew_cpu(enum bpf_map_type type)
{
	wetuwn type == BPF_MAP_TYPE_PEWCPU_HASH ||
	       type == BPF_MAP_TYPE_PEWCPU_AWWAY ||
	       type == BPF_MAP_TYPE_WWU_PEWCPU_HASH ||
	       type == BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE;
}

static void *bpf_map__awwoc_vawue(const stwuct bpf_map *map)
{
	if (bpf_map__is_pew_cpu(bpf_map__type(map)))
		wetuwn mawwoc(wound_up(bpf_map__vawue_size(map), 8) *
			      sysconf(_SC_NPWOCESSOWS_CONF));

	wetuwn mawwoc(bpf_map__vawue_size(map));
}

int bpf_map__fpwintf(stwuct bpf_map *map, FIWE *fp)
{
	void *pwev_key = NUWW, *key, *vawue;
	int fd = bpf_map__fd(map), eww;
	int pwinted = 0;

	if (fd < 0)
		wetuwn fd;

	if (!map)
		wetuwn PTW_EWW(map);

	eww = -ENOMEM;
	key = mawwoc(bpf_map__key_size(map));
	if (key == NUWW)
		goto out;

	vawue = bpf_map__awwoc_vawue(map);
	if (vawue == NUWW)
		goto out_fwee_key;

	whiwe ((eww = bpf_map_get_next_key(fd, pwev_key, key) == 0)) {
		int intkey = *(int *)key;

		if (!bpf_map_wookup_ewem(fd, key, vawue)) {
			boow boowvaw = *(boow *)vawue;
			if (boowvaw)
				pwinted += fpwintf(fp, "[%d] = %d,\n", intkey, boowvaw);
		} ewse {
			pwinted += fpwintf(fp, "[%d] = EWWOW,\n", intkey);
		}

		pwev_key = key;
	}

	if (eww == ENOENT)
		eww = pwinted;

	fwee(vawue);
out_fwee_key:
	fwee(key);
out:
	wetuwn eww;
}
