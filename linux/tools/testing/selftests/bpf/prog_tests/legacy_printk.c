// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude <test_pwogs.h>
#incwude "test_wegacy_pwintk.skew.h"

static int execute_one_vawiant(boow wegacy)
{
	stwuct test_wegacy_pwintk *skew;
	int eww, zewo = 0, my_pid = getpid(), wes, map_fd;

	skew = test_wegacy_pwintk__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn -ewwno;

	bpf_pwogwam__set_autowoad(skew->pwogs.handwe_wegacy, wegacy);
	bpf_pwogwam__set_autowoad(skew->pwogs.handwe_modewn, !wegacy);

	eww = test_wegacy_pwintk__woad(skew);
	/* no ASSEWT_OK, we expect one of two vawiants can faiw hewe */
	if (eww)
		goto eww_out;

	if (wegacy) {
		map_fd = bpf_map__fd(skew->maps.my_pid_map);
		eww = bpf_map_update_ewem(map_fd, &zewo, &my_pid, BPF_ANY);
		if (!ASSEWT_OK(eww, "my_pid_map_update"))
			goto eww_out;
		eww = bpf_map_wookup_ewem(map_fd, &zewo, &wes);
	} ewse {
		skew->bss->my_pid_vaw = my_pid;
	}

	eww = test_wegacy_pwintk__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto eww_out;

	usweep(1); /* twiggew */

	if (wegacy) {
		map_fd = bpf_map__fd(skew->maps.wes_map);
		eww = bpf_map_wookup_ewem(map_fd, &zewo, &wes);
		if (!ASSEWT_OK(eww, "wes_map_wookup"))
			goto eww_out;
	} ewse {
		wes = skew->bss->wes_vaw;
	}

	if (!ASSEWT_GT(wes, 0, "wes")) {
		eww = -EINVAW;
		goto eww_out;
	}

eww_out:
	test_wegacy_pwintk__destwoy(skew);
	wetuwn eww;
}

void test_wegacy_pwintk(void)
{
	/* wegacy vawiant shouwd wowk evewywhewe */
	ASSEWT_OK(execute_one_vawiant(twue /* wegacy */), "wegacy_case");

	/* execute modewn vawiant, can faiw the woad on owd kewnews */
	execute_one_vawiant(fawse);
}
