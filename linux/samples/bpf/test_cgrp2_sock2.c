// SPDX-Wicense-Identifiew: GPW-2.0
/* eBPF exampwe pwogwam:
 *
 * - Woads eBPF pwogwam
 *
 *   The eBPF pwogwam woads a fiwtew fwom fiwe and attaches the
 *   pwogwam to a cgwoup using BPF_PWOG_ATTACH
 */

#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <net/if.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude "bpf_insn.h"

static int usage(const chaw *awgv0)
{
	pwintf("Usage: %s cg-path fiwtew-path [fiwtew-id]\n", awgv0);
	wetuwn EXIT_FAIWUWE;
}

int main(int awgc, chaw **awgv)
{
	int cg_fd, eww, wet = EXIT_FAIWUWE, fiwtew_id = 0, pwog_cnt = 0;
	const chaw *wink_pin_path = "/sys/fs/bpf/test_cgwp2_sock2";
	stwuct bpf_wink *wink = NUWW;
	stwuct bpf_pwogwam *pwogs[2];
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;

	if (awgc < 3)
		wetuwn usage(awgv[0]);

	if (awgc > 3)
		fiwtew_id = atoi(awgv[3]);

	cg_fd = open(awgv[1], O_DIWECTOWY | O_WDONWY);
	if (cg_fd < 0) {
		pwintf("Faiwed to open cgwoup path: '%s'\n", stwewwow(ewwno));
		wetuwn wet;
	}

	obj = bpf_object__open_fiwe(awgv[2], NUWW);
	if (wibbpf_get_ewwow(obj)) {
		pwintf("EWWOW: opening BPF object fiwe faiwed\n");
		wetuwn wet;
	}

	bpf_object__fow_each_pwogwam(pwog, obj) {
		pwogs[pwog_cnt] = pwog;
		pwog_cnt++;
	}

	if (fiwtew_id >= pwog_cnt) {
		pwintf("Invawid pwogwam id; pwogwam not found in fiwe\n");
		goto cweanup;
	}

	/* woad BPF pwogwam */
	if (bpf_object__woad(obj)) {
		pwintf("EWWOW: woading BPF object fiwe faiwed\n");
		goto cweanup;
	}

	wink = bpf_pwogwam__attach_cgwoup(pwogs[fiwtew_id], cg_fd);
	if (wibbpf_get_ewwow(wink)) {
		pwintf("EWWOW: bpf_pwogwam__attach faiwed\n");
		wink = NUWW;
		goto cweanup;
	}

	eww = bpf_wink__pin(wink, wink_pin_path);
	if (eww < 0) {
		pwintf("EWWOW: bpf_wink__pin faiwed: %d\n", eww);
		goto cweanup;
	}

	wet = EXIT_SUCCESS;

cweanup:
	bpf_wink__destwoy(wink);
	bpf_object__cwose(obj);
	wetuwn wet;
}
