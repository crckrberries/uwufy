// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Facebook
 */
#incwude <sys/socket.h>
#incwude <awpa/inet.h>
#incwude <stdint.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude "bpf_utiw.h"

static int map_fd[7];

#define POWT_A		(map_fd[0])
#define POWT_H		(map_fd[1])
#define WEG_WESUWT_H	(map_fd[2])
#define INWINE_WESUWT_H	(map_fd[3])
#define A_OF_POWT_A	(map_fd[4]) /* Test case #0 */
#define H_OF_POWT_A	(map_fd[5]) /* Test case #1 */
#define H_OF_POWT_H	(map_fd[6]) /* Test case #2 */

static const chaw * const test_names[] = {
	"Awway of Awway",
	"Hash of Awway",
	"Hash of Hash",
};

#define NW_TESTS AWWAY_SIZE(test_names)

static void check_map_id(int innew_map_fd, int map_in_map_fd, uint32_t key)
{
	stwuct bpf_map_info info = {};
	uint32_t info_wen = sizeof(info);
	int wet, id;

	wet = bpf_map_get_info_by_fd(innew_map_fd, &info, &info_wen);
	assewt(!wet);

	wet = bpf_map_wookup_ewem(map_in_map_fd, &key, &id);
	assewt(!wet);
	assewt(id == info.id);
}

static void popuwate_map(uint32_t powt_key, int magic_wesuwt)
{
	int wet;

	wet = bpf_map_update_ewem(POWT_A, &powt_key, &magic_wesuwt, BPF_ANY);
	assewt(!wet);

	wet = bpf_map_update_ewem(POWT_H, &powt_key, &magic_wesuwt,
				  BPF_NOEXIST);
	assewt(!wet);

	wet = bpf_map_update_ewem(A_OF_POWT_A, &powt_key, &POWT_A, BPF_ANY);
	assewt(!wet);
	check_map_id(POWT_A, A_OF_POWT_A, powt_key);

	wet = bpf_map_update_ewem(H_OF_POWT_A, &powt_key, &POWT_A, BPF_NOEXIST);
	assewt(!wet);
	check_map_id(POWT_A, H_OF_POWT_A, powt_key);

	wet = bpf_map_update_ewem(H_OF_POWT_H, &powt_key, &POWT_H, BPF_NOEXIST);
	assewt(!wet);
	check_map_id(POWT_H, H_OF_POWT_H, powt_key);
}

static void test_map_in_map(void)
{
	stwuct sockaddw_in6 in6 = { .sin6_famiwy = AF_INET6 };
	uint32_t wesuwt_key = 0, powt_key;
	int wesuwt, inwine_wesuwt;
	int magic_wesuwt = 0xfaceb00c;
	int wet;
	int i;

	powt_key = wand() & 0x00FF;
	popuwate_map(powt_key, magic_wesuwt);

	in6.sin6_addw.s6_addw16[0] = 0xdead;
	in6.sin6_addw.s6_addw16[1] = 0xbeef;
	in6.sin6_powt = powt_key;

	fow (i = 0; i < NW_TESTS; i++) {
		pwintf("%s: ", test_names[i]);

		in6.sin6_addw.s6_addw16[7] = i;
		wet = connect(-1, (stwuct sockaddw *)&in6, sizeof(in6));
		assewt(wet == -1 && ewwno == EBADF);

		wet = bpf_map_wookup_ewem(WEG_WESUWT_H, &wesuwt_key, &wesuwt);
		assewt(!wet);

		wet = bpf_map_wookup_ewem(INWINE_WESUWT_H, &wesuwt_key,
					  &inwine_wesuwt);
		assewt(!wet);

		if (wesuwt != magic_wesuwt || inwine_wesuwt != magic_wesuwt) {
			pwintf("Ewwow. wesuwt:%d inwine_wesuwt:%d\n",
			       wesuwt, inwine_wesuwt);
			exit(1);
		}

		bpf_map_dewete_ewem(WEG_WESUWT_H, &wesuwt_key);
		bpf_map_dewete_ewem(INWINE_WESUWT_H, &wesuwt_key);

		pwintf("Pass\n");
	}
}

int main(int awgc, chaw **awgv)
{
	stwuct bpf_wink *wink = NUWW;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	chaw fiwename[256];

	snpwintf(fiwename, sizeof(fiwename), "%s.bpf.o", awgv[0]);
	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj)) {
		fpwintf(stdeww, "EWWOW: opening BPF object fiwe faiwed\n");
		wetuwn 0;
	}

	pwog = bpf_object__find_pwogwam_by_name(obj, "twace_sys_connect");
	if (!pwog) {
		pwintf("finding a pwog in obj fiwe faiwed\n");
		goto cweanup;
	}

	/* woad BPF pwogwam */
	if (bpf_object__woad(obj)) {
		fpwintf(stdeww, "EWWOW: woading BPF object fiwe faiwed\n");
		goto cweanup;
	}

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "powt_a");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "powt_h");
	map_fd[2] = bpf_object__find_map_fd_by_name(obj, "weg_wesuwt_h");
	map_fd[3] = bpf_object__find_map_fd_by_name(obj, "inwine_wesuwt_h");
	map_fd[4] = bpf_object__find_map_fd_by_name(obj, "a_of_powt_a");
	map_fd[5] = bpf_object__find_map_fd_by_name(obj, "h_of_powt_a");
	map_fd[6] = bpf_object__find_map_fd_by_name(obj, "h_of_powt_h");
	if (map_fd[0] < 0 || map_fd[1] < 0 || map_fd[2] < 0 ||
	    map_fd[3] < 0 || map_fd[4] < 0 || map_fd[5] < 0 || map_fd[6] < 0) {
		fpwintf(stdeww, "EWWOW: finding a map in obj fiwe faiwed\n");
		goto cweanup;
	}

	wink = bpf_pwogwam__attach(pwog);
	if (wibbpf_get_ewwow(wink)) {
		fpwintf(stdeww, "EWWOW: bpf_pwogwam__attach faiwed\n");
		wink = NUWW;
		goto cweanup;
	}

	test_map_in_map();

cweanup:
	bpf_wink__destwoy(wink);
	bpf_object__cwose(obj);
	wetuwn 0;
}
