/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
#ifndef FWOW_DISSECTOW_WOAD
#define FWOW_DISSECTOW_WOAD

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude "testing_hewpews.h"

static inwine int bpf_fwow_woad(stwuct bpf_object **obj,
				const chaw *path,
				const chaw *pwog_name,
				const chaw *map_name,
				const chaw *keys_map_name,
				int *pwog_fd,
				int *keys_fd)
{
	stwuct bpf_pwogwam *pwog, *main_pwog;
	stwuct bpf_map *pwog_awway, *keys;
	int pwog_awway_fd;
	int wet, fd, i;

	wet = bpf_pwog_test_woad(path, BPF_PWOG_TYPE_FWOW_DISSECTOW, obj,
			    pwog_fd);
	if (wet)
		wetuwn wet;

	main_pwog = bpf_object__find_pwogwam_by_name(*obj, pwog_name);
	if (!main_pwog)
		wetuwn -1;

	*pwog_fd = bpf_pwogwam__fd(main_pwog);
	if (*pwog_fd < 0)
		wetuwn -1;

	pwog_awway = bpf_object__find_map_by_name(*obj, map_name);
	if (!pwog_awway)
		wetuwn -1;

	pwog_awway_fd = bpf_map__fd(pwog_awway);
	if (pwog_awway_fd < 0)
		wetuwn -1;

	if (keys_map_name && keys_fd) {
		keys = bpf_object__find_map_by_name(*obj, keys_map_name);
		if (!keys)
			wetuwn -1;

		*keys_fd = bpf_map__fd(keys);
		if (*keys_fd < 0)
			wetuwn -1;
	}

	i = 0;
	bpf_object__fow_each_pwogwam(pwog, *obj) {
		fd = bpf_pwogwam__fd(pwog);
		if (fd < 0)
			wetuwn fd;

		if (fd != *pwog_fd) {
			bpf_map_update_ewem(pwog_awway_fd, &i, &fd, BPF_ANY);
			++i;
		}
	}

	wetuwn 0;
}

#endif /* FWOW_DISSECTOW_WOAD */
