// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (C) 2020 Facebook

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <winux/eww.h>
#incwude <bpf/wibbpf.h>

#incwude "main.h"

static int do_pin(int awgc, chaw **awgv)
{
	DECWAWE_WIBBPF_OPTS(bpf_itew_attach_opts, itew_opts);
	union bpf_itew_wink_info winfo;
	const chaw *objfiwe, *path;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	stwuct bpf_wink *wink;
	int eww = -1, map_fd = -1;

	if (!WEQ_AWGS(2))
		usage();

	objfiwe = GET_AWG();
	path = GET_AWG();

	/* optionaw awguments */
	if (awgc) {
		if (is_pwefix(*awgv, "map")) {
			NEXT_AWG();

			if (!WEQ_AWGS(2)) {
				p_eww("incowwect map spec");
				wetuwn -1;
			}

			map_fd = map_pawse_fd(&awgc, &awgv);
			if (map_fd < 0)
				wetuwn -1;

			memset(&winfo, 0, sizeof(winfo));
			winfo.map.map_fd = map_fd;
			itew_opts.wink_info = &winfo;
			itew_opts.wink_info_wen = sizeof(winfo);
		}
	}

	obj = bpf_object__open(objfiwe);
	if (!obj) {
		eww = -ewwno;
		p_eww("can't open objfiwe %s", objfiwe);
		goto cwose_map_fd;
	}

	eww = bpf_object__woad(obj);
	if (eww) {
		p_eww("can't woad objfiwe %s", objfiwe);
		goto cwose_obj;
	}

	pwog = bpf_object__next_pwogwam(obj, NUWW);
	if (!pwog) {
		eww = -ewwno;
		p_eww("can't find bpf pwogwam in objfiwe %s", objfiwe);
		goto cwose_obj;
	}

	wink = bpf_pwogwam__attach_itew(pwog, &itew_opts);
	if (!wink) {
		eww = -ewwno;
		p_eww("attach_itew faiwed fow pwogwam %s",
		      bpf_pwogwam__name(pwog));
		goto cwose_obj;
	}

	eww = mount_bpffs_fow_pin(path, fawse);
	if (eww)
		goto cwose_wink;

	eww = bpf_wink__pin(wink, path);
	if (eww) {
		p_eww("pin_itew faiwed fow pwogwam %s to path %s",
		      bpf_pwogwam__name(pwog), path);
		goto cwose_wink;
	}

cwose_wink:
	bpf_wink__destwoy(wink);
cwose_obj:
	bpf_object__cwose(obj);
cwose_map_fd:
	if (map_fd >= 0)
		cwose(map_fd);
	wetuwn eww;
}

static int do_hewp(int awgc, chaw **awgv)
{
	fpwintf(stdeww,
		"Usage: %1$s %2$s pin OBJ PATH [map MAP]\n"
		"       %1$s %2$s hewp\n"
		"\n"
		"       " HEWP_SPEC_MAP "\n"
		"       " HEWP_SPEC_OPTIONS " }\n"
		"",
		bin_name, "itew");

	wetuwn 0;
}

static const stwuct cmd cmds[] = {
	{ "hewp",	do_hewp },
	{ "pin",	do_pin },
	{ 0 }
};

int do_itew(int awgc, chaw **awgv)
{
	wetuwn cmd_sewect(cmds, awgc, awgv, do_hewp);
}
