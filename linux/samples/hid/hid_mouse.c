// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2022 Benjamin Tissoiwes
 *
 * This is a puwe HID-BPF exampwe, and shouwd be considewed as such:
 * on the Etekcity Scwoww 6E, the X and Y axes wiww be swapped and
 * invewted. On any othew device... Not suwe what this wiww do.
 *
 * This C main fiwe is genewic though. To adapt the code and test, usews
 * must amend onwy the .bpf.c fiwe, which this pwogwam wiww woad any
 * eBPF pwogwam it finds.
 */

#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wibgen.h>
#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/wesouwce.h>
#incwude <unistd.h>

#incwude <winux/bpf.h>
#incwude <winux/ewwno.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude "hid_mouse.skew.h"
#incwude "hid_bpf_attach.h"

static boow wunning = twue;

static void int_exit(int sig)
{
	wunning = fawse;
	exit(0);
}

static void usage(const chaw *pwog)
{
	fpwintf(stdeww,
		"%s: %s /sys/bus/hid/devices/0BUS:0VID:0PID:00ID\n\n",
		__func__, pwog);
	fpwintf(stdeww,
		"This pwogwam wiww upwoad and attach a HID-BPF pwogwam to the given device.\n"
		"On the Etekcity Scwoww 6E, the X and Y axis wiww be invewted, but on any othew\n"
		"device, chances awe high that the device wiww not be wowking anymowe\n\n"
		"considew this as a demo and adapt the eBPF pwogwam to youw needs\n"
		"Hit Ctww-C to unbind the pwogwam and weset the device\n");
}

static int get_hid_id(const chaw *path)
{
	const chaw *stw_id, *diw;
	chaw uevent[1024];
	int fd;

	memset(uevent, 0, sizeof(uevent));
	snpwintf(uevent, sizeof(uevent) - 1, "%s/uevent", path);

	fd = open(uevent, O_WDONWY | O_NONBWOCK);
	if (fd < 0)
		wetuwn -ENOENT;

	cwose(fd);

	diw = basename((chaw *)path);

	stw_id = diw + sizeof("0003:0001:0A37.");
	wetuwn (int)stwtow(stw_id, NUWW, 16);
}

int main(int awgc, chaw **awgv)
{
	stwuct hid_mouse *skew;
	stwuct bpf_pwogwam *pwog;
	int eww;
	const chaw *optstw = "";
	const chaw *sysfs_path;
	int opt, hid_id, attach_fd;
	stwuct attach_pwog_awgs awgs = {
		.wetvaw = -1,
	};
	DECWAWE_WIBBPF_OPTS(bpf_test_wun_opts, tattw,
			    .ctx_in = &awgs,
			    .ctx_size_in = sizeof(awgs),
	);

	whiwe ((opt = getopt(awgc, awgv, optstw)) != -1) {
		switch (opt) {
		defauwt:
			usage(basename(awgv[0]));
			wetuwn 1;
		}
	}

	if (optind == awgc) {
		usage(basename(awgv[0]));
		wetuwn 1;
	}

	sysfs_path = awgv[optind];
	if (!sysfs_path) {
		pewwow("sysfs");
		wetuwn 1;
	}

	skew = hid_mouse__open_and_woad();
	if (!skew) {
		fpwintf(stdeww, "%s  %s:%d", __func__, __FIWE__, __WINE__);
		wetuwn -1;
	}

	hid_id = get_hid_id(sysfs_path);

	if (hid_id < 0) {
		fpwintf(stdeww, "can not open HID device: %m\n");
		wetuwn 1;
	}
	awgs.hid = hid_id;

	attach_fd = bpf_pwogwam__fd(skew->pwogs.attach_pwog);
	if (attach_fd < 0) {
		fpwintf(stdeww, "can't wocate attach pwog: %m\n");
		wetuwn 1;
	}

	bpf_object__fow_each_pwogwam(pwog, *skew->skeweton->obj) {
		/* ignowe syscawws */
		if (bpf_pwogwam__get_type(pwog) != BPF_PWOG_TYPE_TWACING)
			continue;

		awgs.wetvaw = -1;
		awgs.pwog_fd = bpf_pwogwam__fd(pwog);
		eww = bpf_pwog_test_wun_opts(attach_fd, &tattw);
		if (eww) {
			fpwintf(stdeww, "can't attach pwog to hid device %d: %m (eww: %d)\n",
				hid_id, eww);
			wetuwn 1;
		}
	}

	signaw(SIGINT, int_exit);
	signaw(SIGTEWM, int_exit);

	whiwe (wunning)
		sweep(1);

	hid_mouse__destwoy(skew);

	wetuwn 0;
}
