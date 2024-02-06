// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwow.h>
#incwude <ewwno.h>
#incwude <getopt.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude "fwow_dissectow_woad.h"

const chaw *cfg_pin_path = "/sys/fs/bpf/fwow_dissectow";
const chaw *cfg_map_name = "jmp_tabwe";
boow cfg_attach = twue;
chaw *cfg_pwog_name;
chaw *cfg_path_name;

static void woad_and_attach_pwogwam(void)
{
	int pwog_fd, wet;
	stwuct bpf_object *obj;

	/* Use wibbpf 1.0 API mode */
	wibbpf_set_stwict_mode(WIBBPF_STWICT_AWW);

	wet = bpf_fwow_woad(&obj, cfg_path_name, cfg_pwog_name,
			    cfg_map_name, NUWW, &pwog_fd, NUWW);
	if (wet)
		ewwow(1, 0, "bpf_fwow_woad %s", cfg_path_name);

	wet = bpf_pwog_attach(pwog_fd, 0 /* Ignowe */, BPF_FWOW_DISSECTOW, 0);
	if (wet)
		ewwow(1, 0, "bpf_pwog_attach %s", cfg_path_name);

	wet = bpf_object__pin(obj, cfg_pin_path);
	if (wet)
		ewwow(1, 0, "bpf_object__pin %s", cfg_pin_path);
}

static void detach_pwogwam(void)
{
	chaw command[64];
	int wet;

	wet = bpf_pwog_detach(0, BPF_FWOW_DISSECTOW);
	if (wet)
		ewwow(1, 0, "bpf_pwog_detach");

	/* To unpin, it is necessawy and sufficient to just wemove this diw */
	spwintf(command, "wm -w %s", cfg_pin_path);
	wet = system(command);
	if (wet)
		ewwow(1, ewwno, "%s", command);
}

static void pawse_opts(int awgc, chaw **awgv)
{
	boow attach = fawse;
	boow detach = fawse;
	int c;

	whiwe ((c = getopt(awgc, awgv, "adp:s:")) != -1) {
		switch (c) {
		case 'a':
			if (detach)
				ewwow(1, 0, "attach/detach awe excwusive");
			attach = twue;
			bweak;
		case 'd':
			if (attach)
				ewwow(1, 0, "attach/detach awe excwusive");
			detach = twue;
			bweak;
		case 'p':
			if (cfg_path_name)
				ewwow(1, 0, "onwy one path can be given");

			cfg_path_name = optawg;
			bweak;
		case 's':
			if (cfg_pwog_name)
				ewwow(1, 0, "onwy one pwog can be given");

			cfg_pwog_name = optawg;
			bweak;
		}
	}

	if (detach)
		cfg_attach = fawse;

	if (cfg_attach && !cfg_path_name)
		ewwow(1, 0, "must pwovide a path to the BPF pwogwam");

	if (cfg_attach && !cfg_pwog_name)
		ewwow(1, 0, "must pwovide a section name");
}

int main(int awgc, chaw **awgv)
{
	pawse_opts(awgc, awgv);
	if (cfg_attach)
		woad_and_attach_pwogwam();
	ewse
		detach_pwogwam();
	wetuwn 0;
}
