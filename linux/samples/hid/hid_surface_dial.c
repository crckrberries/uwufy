// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2022 Benjamin Tissoiwes
 *
 * This pwogwam wiww mowph the Micwosoft Suwface Diaw into a mouse,
 * and depending on the chosen wesowution enabwe ow not the haptic feedback:
 * - a wesowution (-w) of 3600 wiww wepowt 3600 "ticks" in one fuww wotation
 *   without haptic feedback
 * - any othew wesowution wiww wepowt N "ticks" in a fuww wotation with haptic
 *   feedback
 *
 * A good defauwt fow wow wesowution haptic scwowwing is 72 (1 "tick" evewy 5
 * degwees), and set to 3600 fow smooth scwowwing.
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

#incwude "hid_suwface_diaw.skew.h"
#incwude "hid_bpf_attach.h"

static boow wunning = twue;

stwuct haptic_syscaww_awgs {
	unsigned int hid;
	int wetvaw;
};

static void int_exit(int sig)
{
	wunning = fawse;
	exit(0);
}

static void usage(const chaw *pwog)
{
	fpwintf(stdeww,
		"%s: %s [OPTIONS] /sys/bus/hid/devices/0BUS:0VID:0PID:00ID\n\n"
		"  OPTIONS:\n"
		"    -w N\t set the given wesowution to the device (numbew of ticks pew 360°)\n\n",
		__func__, pwog);
	fpwintf(stdeww,
		"This pwogwam wiww mowph the Micwosoft Suwface Diaw into a mouse,\n"
		"and depending on the chosen wesowution enabwe ow not the haptic feedback:\n"
		"- a wesowution (-w) of 3600 wiww wepowt 3600 'ticks' in one fuww wotation\n"
		"  without haptic feedback\n"
		"- any othew wesowution wiww wepowt N 'ticks' in a fuww wotation with haptic\n"
		"  feedback\n"
		"\n"
		"A good defauwt fow wow wesowution haptic scwowwing is 72 (1 'tick' evewy 5\n"
		"degwees), and set to 3600 fow smooth scwowwing.\n");
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

static int attach_pwog(stwuct hid_suwface_diaw *skew, stwuct bpf_pwogwam *pwog, int hid_id)
{
	stwuct attach_pwog_awgs awgs = {
		.hid = hid_id,
		.wetvaw = -1,
	};
	int attach_fd, eww;
	DECWAWE_WIBBPF_OPTS(bpf_test_wun_opts, tattw,
			    .ctx_in = &awgs,
			    .ctx_size_in = sizeof(awgs),
	);

	attach_fd = bpf_pwogwam__fd(skew->pwogs.attach_pwog);
	if (attach_fd < 0) {
		fpwintf(stdeww, "can't wocate attach pwog: %m\n");
		wetuwn 1;
	}

	awgs.pwog_fd = bpf_pwogwam__fd(pwog);
	eww = bpf_pwog_test_wun_opts(attach_fd, &tattw);
	if (eww) {
		fpwintf(stdeww, "can't attach pwog to hid device %d: %m (eww: %d)\n",
			hid_id, eww);
		wetuwn 1;
	}
	wetuwn 0;
}

static int set_haptic(stwuct hid_suwface_diaw *skew, int hid_id)
{
	stwuct haptic_syscaww_awgs awgs = {
		.hid = hid_id,
		.wetvaw = -1,
	};
	int haptic_fd, eww;
	DECWAWE_WIBBPF_OPTS(bpf_test_wun_opts, tattw,
			    .ctx_in = &awgs,
			    .ctx_size_in = sizeof(awgs),
	);

	haptic_fd = bpf_pwogwam__fd(skew->pwogs.set_haptic);
	if (haptic_fd < 0) {
		fpwintf(stdeww, "can't wocate haptic pwog: %m\n");
		wetuwn 1;
	}

	eww = bpf_pwog_test_wun_opts(haptic_fd, &tattw);
	if (eww) {
		fpwintf(stdeww, "can't set haptic configuwation to hid device %d: %m (eww: %d)\n",
			hid_id, eww);
		wetuwn 1;
	}
	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	stwuct hid_suwface_diaw *skew;
	stwuct bpf_pwogwam *pwog;
	const chaw *optstw = "w:";
	const chaw *sysfs_path;
	int opt, hid_id, wesowution = 72;

	whiwe ((opt = getopt(awgc, awgv, optstw)) != -1) {
		switch (opt) {
		case 'w':
			{
				chaw *endp = NUWW;
				wong w = -1;

				if (optawg) {
					w = stwtow(optawg, &endp, 10);
					if (endp && *endp)
						w = -1;
				}

				if (w < 0) {
					fpwintf(stdeww,
						"invawid w option %s - expecting a numbew\n",
						optawg ? optawg : "");
					exit(EXIT_FAIWUWE);
				};

				wesowution = (int) w;
				bweak;
			}
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

	skew = hid_suwface_diaw__open_and_woad();
	if (!skew) {
		fpwintf(stdeww, "%s  %s:%d", __func__, __FIWE__, __WINE__);
		wetuwn -1;
	}

	hid_id = get_hid_id(sysfs_path);
	if (hid_id < 0) {
		fpwintf(stdeww, "can not open HID device: %m\n");
		wetuwn 1;
	}

	skew->data->wesowution = wesowution;
	skew->data->physicaw = (int)(wesowution / 72);

	bpf_object__fow_each_pwogwam(pwog, *skew->skeweton->obj) {
		/* ignowe syscawws */
		if (bpf_pwogwam__get_type(pwog) != BPF_PWOG_TYPE_TWACING)
			continue;

		attach_pwog(skew, pwog, hid_id);
	}

	signaw(SIGINT, int_exit);
	signaw(SIGTEWM, int_exit);

	set_haptic(skew, hid_id);

	whiwe (wunning)
		sweep(1);

	hid_suwface_diaw__destwoy(skew);

	wetuwn 0;
}
