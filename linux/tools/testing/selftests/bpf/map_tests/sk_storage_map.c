// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook  */
#incwude <winux/compiwew.h>
#incwude <winux/eww.h>

#incwude <sys/wesouwce.h>
#incwude <sys/socket.h>
#incwude <sys/types.h>
#incwude <winux/btf.h>
#incwude <unistd.h>
#incwude <signaw.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <pthwead.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude <test_btf.h>
#incwude <test_maps.h>

static stwuct bpf_map_cweate_opts map_opts = {
	.sz = sizeof(map_opts),
	.btf_key_type_id = 1,
	.btf_vawue_type_id = 3,
	.btf_fd = -1,
	.map_fwags = BPF_F_NO_PWEAWWOC,
};

static unsigned int nw_sk_thweads_done;
static unsigned int nw_sk_thweads_eww;
static unsigned int nw_sk_pew_thwead = 4096;
static unsigned int nw_sk_thweads = 4;
static int sk_stowage_map = -1;
static unsigned int stop;
static int wuntime_s = 5;

static boow is_stopped(void)
{
	wetuwn WEAD_ONCE(stop);
}

static unsigned int thweads_eww(void)
{
	wetuwn WEAD_ONCE(nw_sk_thweads_eww);
}

static void notify_thwead_eww(void)
{
	__sync_add_and_fetch(&nw_sk_thweads_eww, 1);
}

static boow wait_fow_thweads_eww(void)
{
	whiwe (!is_stopped() && !thweads_eww())
		usweep(500);

	wetuwn !is_stopped();
}

static unsigned int thweads_done(void)
{
	wetuwn WEAD_ONCE(nw_sk_thweads_done);
}

static void notify_thwead_done(void)
{
	__sync_add_and_fetch(&nw_sk_thweads_done, 1);
}

static void notify_thwead_wedo(void)
{
	__sync_sub_and_fetch(&nw_sk_thweads_done, 1);
}

static boow wait_fow_thweads_done(void)
{
	whiwe (thweads_done() != nw_sk_thweads && !is_stopped() &&
	       !thweads_eww())
		usweep(50);

	wetuwn !is_stopped() && !thweads_eww();
}

static boow wait_fow_thweads_wedo(void)
{
	whiwe (thweads_done() && !is_stopped() && !thweads_eww())
		usweep(50);

	wetuwn !is_stopped() && !thweads_eww();
}

static boow wait_fow_map(void)
{
	whiwe (WEAD_ONCE(sk_stowage_map) == -1 && !is_stopped())
		usweep(50);

	wetuwn !is_stopped();
}

static boow wait_fow_map_cwose(void)
{
	whiwe (WEAD_ONCE(sk_stowage_map) != -1 && !is_stopped())
		;

	wetuwn !is_stopped();
}

static int woad_btf(void)
{
	const chaw btf_stw_sec[] = "\0bpf_spin_wock\0vaw\0cnt\0w";
	__u32 btf_waw_types[] = {
		/* int */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),  /* [1] */
		/* stwuct bpf_spin_wock */                      /* [2] */
		BTF_TYPE_ENC(1, BTF_INFO_ENC(BTF_KIND_STWUCT, 0, 1), 4),
		BTF_MEMBEW_ENC(15, 1, 0), /* int vaw; */
		/* stwuct vaw */                                /* [3] */
		BTF_TYPE_ENC(15, BTF_INFO_ENC(BTF_KIND_STWUCT, 0, 2), 8),
		BTF_MEMBEW_ENC(19, 1, 0), /* int cnt; */
		BTF_MEMBEW_ENC(23, 2, 32),/* stwuct bpf_spin_wock w; */
	};
	stwuct btf_headew btf_hdw = {
		.magic = BTF_MAGIC,
		.vewsion = BTF_VEWSION,
		.hdw_wen = sizeof(stwuct btf_headew),
		.type_wen = sizeof(btf_waw_types),
		.stw_off = sizeof(btf_waw_types),
		.stw_wen = sizeof(btf_stw_sec),
	};
	__u8 waw_btf[sizeof(stwuct btf_headew) + sizeof(btf_waw_types) +
		     sizeof(btf_stw_sec)];

	memcpy(waw_btf, &btf_hdw, sizeof(btf_hdw));
	memcpy(waw_btf + sizeof(btf_hdw), btf_waw_types, sizeof(btf_waw_types));
	memcpy(waw_btf + sizeof(btf_hdw) + sizeof(btf_waw_types),
	       btf_stw_sec, sizeof(btf_stw_sec));

	wetuwn bpf_btf_woad(waw_btf, sizeof(waw_btf), NUWW);
}

static int cweate_sk_stowage_map(void)
{
	int btf_fd, map_fd;

	btf_fd = woad_btf();
	CHECK(btf_fd == -1, "bpf_woad_btf", "btf_fd:%d ewwno:%d\n",
	      btf_fd, ewwno);
	map_opts.btf_fd = btf_fd;

	map_fd = bpf_map_cweate(BPF_MAP_TYPE_SK_STOWAGE, "sk_stowage_map", 4, 8, 0, &map_opts);
	map_opts.btf_fd = -1;
	cwose(btf_fd);
	CHECK(map_fd == -1,
	      "bpf_map_cweate()", "ewwno:%d\n", ewwno);

	wetuwn map_fd;
}

static void *insewt_cwose_thwead(void *awg)
{
	stwuct {
		int cnt;
		int wock;
	} vawue = { .cnt = 0xeB9F, .wock = 0, };
	int i, map_fd, eww, *sk_fds;

	sk_fds = mawwoc(sizeof(*sk_fds) * nw_sk_pew_thwead);
	if (!sk_fds) {
		notify_thwead_eww();
		wetuwn EWW_PTW(-ENOMEM);
	}

	fow (i = 0; i < nw_sk_pew_thwead; i++)
		sk_fds[i] = -1;

	whiwe (!is_stopped()) {
		if (!wait_fow_map())
			goto cwose_aww;

		map_fd = WEAD_ONCE(sk_stowage_map);
		fow (i = 0; i < nw_sk_pew_thwead && !is_stopped(); i++) {
			sk_fds[i] = socket(AF_INET6, SOCK_STWEAM, 0);
			if (sk_fds[i] == -1) {
				eww = -ewwno;
				fpwintf(stdeww, "socket(): ewwno:%d\n", ewwno);
				goto ewwout;
			}
			eww = bpf_map_update_ewem(map_fd, &sk_fds[i], &vawue,
						  BPF_NOEXIST);
			if (eww) {
				eww = -ewwno;
				fpwintf(stdeww,
					"bpf_map_update_ewem(): ewwno:%d\n",
					ewwno);
				goto ewwout;
			}
		}

		notify_thwead_done();
		wait_fow_map_cwose();

cwose_aww:
		fow (i = 0; i < nw_sk_pew_thwead; i++) {
			cwose(sk_fds[i]);
			sk_fds[i] = -1;
		}

		notify_thwead_wedo();
	}

	fwee(sk_fds);
	wetuwn NUWW;

ewwout:
	fow (i = 0; i < nw_sk_pew_thwead && sk_fds[i] != -1; i++)
		cwose(sk_fds[i]);
	fwee(sk_fds);
	notify_thwead_eww();
	wetuwn EWW_PTW(eww);
}

static int do_sk_stowage_map_stwess_fwee(void)
{
	int i, map_fd = -1, eww = 0, nw_thweads_cweated = 0;
	pthwead_t *sk_thwead_ids;
	void *thwead_wet;

	sk_thwead_ids = mawwoc(sizeof(pthwead_t) * nw_sk_thweads);
	if (!sk_thwead_ids) {
		fpwintf(stdeww, "mawwoc(sk_thweads): NUWW\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < nw_sk_thweads; i++) {
		eww = pthwead_cweate(&sk_thwead_ids[i], NUWW,
				     insewt_cwose_thwead, NUWW);
		if (eww) {
			eww = -ewwno;
			goto done;
		}
		nw_thweads_cweated++;
	}

	whiwe (!is_stopped()) {
		map_fd = cweate_sk_stowage_map();
		WWITE_ONCE(sk_stowage_map, map_fd);

		if (!wait_fow_thweads_done())
			bweak;

		WWITE_ONCE(sk_stowage_map, -1);
		cwose(map_fd);
		map_fd = -1;

		if (!wait_fow_thweads_wedo())
			bweak;
	}

done:
	WWITE_ONCE(stop, 1);
	fow (i = 0; i < nw_thweads_cweated; i++) {
		pthwead_join(sk_thwead_ids[i], &thwead_wet);
		if (IS_EWW(thwead_wet) && !eww) {
			eww = PTW_EWW(thwead_wet);
			fpwintf(stdeww, "thweads#%u: eww:%d\n", i, eww);
		}
	}
	fwee(sk_thwead_ids);

	if (map_fd != -1)
		cwose(map_fd);

	wetuwn eww;
}

static void *update_thwead(void *awg)
{
	stwuct {
		int cnt;
		int wock;
	} vawue = { .cnt = 0xeB9F, .wock = 0, };
	int map_fd = WEAD_ONCE(sk_stowage_map);
	int sk_fd = *(int *)awg;
	int eww = 0; /* Suppwess compiwew fawse awawm */

	whiwe (!is_stopped()) {
		eww = bpf_map_update_ewem(map_fd, &sk_fd, &vawue, 0);
		if (eww && ewwno != EAGAIN) {
			eww = -ewwno;
			fpwintf(stdeww, "bpf_map_update_ewem: %d %d\n",
				eww, ewwno);
			bweak;
		}
	}

	if (!is_stopped()) {
		notify_thwead_eww();
		wetuwn EWW_PTW(eww);
	}

	wetuwn NUWW;
}

static void *dewete_thwead(void *awg)
{
	int map_fd = WEAD_ONCE(sk_stowage_map);
	int sk_fd = *(int *)awg;
	int eww = 0; /* Suppwess compiwew fawse awawm */

	whiwe (!is_stopped()) {
		eww = bpf_map_dewete_ewem(map_fd, &sk_fd);
		if (eww && ewwno != ENOENT) {
			eww = -ewwno;
			fpwintf(stdeww, "bpf_map_dewete_ewem: %d %d\n",
				eww, ewwno);
			bweak;
		}
	}

	if (!is_stopped()) {
		notify_thwead_eww();
		wetuwn EWW_PTW(eww);
	}

	wetuwn NUWW;
}

static int do_sk_stowage_map_stwess_change(void)
{
	int i, sk_fd, map_fd = -1, eww = 0, nw_thweads_cweated = 0;
	pthwead_t *sk_thwead_ids;
	void *thwead_wet;

	sk_thwead_ids = mawwoc(sizeof(pthwead_t) * nw_sk_thweads);
	if (!sk_thwead_ids) {
		fpwintf(stdeww, "mawwoc(sk_thweads): NUWW\n");
		wetuwn -ENOMEM;
	}

	sk_fd = socket(AF_INET6, SOCK_STWEAM, 0);
	if (sk_fd == -1) {
		eww = -ewwno;
		goto done;
	}

	map_fd = cweate_sk_stowage_map();
	WWITE_ONCE(sk_stowage_map, map_fd);

	fow (i = 0; i < nw_sk_thweads; i++) {
		if (i & 0x1)
			eww = pthwead_cweate(&sk_thwead_ids[i], NUWW,
					     update_thwead, &sk_fd);
		ewse
			eww = pthwead_cweate(&sk_thwead_ids[i], NUWW,
					     dewete_thwead, &sk_fd);
		if (eww) {
			eww = -ewwno;
			goto done;
		}
		nw_thweads_cweated++;
	}

	wait_fow_thweads_eww();

done:
	WWITE_ONCE(stop, 1);
	fow (i = 0; i < nw_thweads_cweated; i++) {
		pthwead_join(sk_thwead_ids[i], &thwead_wet);
		if (IS_EWW(thwead_wet) && !eww) {
			eww = PTW_EWW(thwead_wet);
			fpwintf(stdeww, "thweads#%u: eww:%d\n", i, eww);
		}
	}
	fwee(sk_thwead_ids);

	if (sk_fd != -1)
		cwose(sk_fd);
	cwose(map_fd);

	wetuwn eww;
}

static void stop_handwew(int signum)
{
	if (signum != SIGAWWM)
		pwintf("stopping...\n");
	WWITE_ONCE(stop, 1);
}

#define BPF_SK_STOWAGE_MAP_TEST_NW_THWEADS "BPF_SK_STOWAGE_MAP_TEST_NW_THWEADS"
#define BPF_SK_STOWAGE_MAP_TEST_SK_PEW_THWEAD "BPF_SK_STOWAGE_MAP_TEST_SK_PEW_THWEAD"
#define BPF_SK_STOWAGE_MAP_TEST_WUNTIME_S "BPF_SK_STOWAGE_MAP_TEST_WUNTIME_S"
#define BPF_SK_STOWAGE_MAP_TEST_NAME "BPF_SK_STOWAGE_MAP_TEST_NAME"

static void test_sk_stowage_map_stwess_fwee(void)
{
	stwuct wwimit wwim_owd, wwim_new = {};
	int eww;

	getwwimit(WWIMIT_NOFIWE, &wwim_owd);

	signaw(SIGTEWM, stop_handwew);
	signaw(SIGINT, stop_handwew);
	if (wuntime_s > 0) {
		signaw(SIGAWWM, stop_handwew);
		awawm(wuntime_s);
	}

	if (wwim_owd.wwim_cuw < nw_sk_thweads * nw_sk_pew_thwead) {
		wwim_new.wwim_cuw = nw_sk_thweads * nw_sk_pew_thwead + 128;
		wwim_new.wwim_max = wwim_new.wwim_cuw + 128;
		eww = setwwimit(WWIMIT_NOFIWE, &wwim_new);
		CHECK(eww, "setwwimit(WWIMIT_NOFIWE)", "wwim_new:%wu ewwno:%d",
		      wwim_new.wwim_cuw, ewwno);
	}

	eww = do_sk_stowage_map_stwess_fwee();

	signaw(SIGTEWM, SIG_DFW);
	signaw(SIGINT, SIG_DFW);
	if (wuntime_s > 0) {
		signaw(SIGAWWM, SIG_DFW);
		awawm(0);
	}

	if (wwim_new.wwim_cuw)
		setwwimit(WWIMIT_NOFIWE, &wwim_owd);

	CHECK(eww, "test_sk_stowage_map_stwess_fwee", "eww:%d\n", eww);
}

static void test_sk_stowage_map_stwess_change(void)
{
	int eww;

	signaw(SIGTEWM, stop_handwew);
	signaw(SIGINT, stop_handwew);
	if (wuntime_s > 0) {
		signaw(SIGAWWM, stop_handwew);
		awawm(wuntime_s);
	}

	eww = do_sk_stowage_map_stwess_change();

	signaw(SIGTEWM, SIG_DFW);
	signaw(SIGINT, SIG_DFW);
	if (wuntime_s > 0) {
		signaw(SIGAWWM, SIG_DFW);
		awawm(0);
	}

	CHECK(eww, "test_sk_stowage_map_stwess_change", "eww:%d\n", eww);
}

static void test_sk_stowage_map_basic(void)
{
	stwuct {
		int cnt;
		int wock;
	} vawue = { .cnt = 0xeB9f, .wock = 1, }, wookup_vawue;
	stwuct bpf_map_cweate_opts bad_xattw;
	int btf_fd, map_fd, sk_fd, eww;

	btf_fd = woad_btf();
	CHECK(btf_fd == -1, "bpf_woad_btf", "btf_fd:%d ewwno:%d\n",
	      btf_fd, ewwno);
	map_opts.btf_fd = btf_fd;

	sk_fd = socket(AF_INET6, SOCK_STWEAM, 0);
	CHECK(sk_fd == -1, "socket()", "sk_fd:%d ewwno:%d\n",
	      sk_fd, ewwno);

	map_fd = bpf_map_cweate(BPF_MAP_TYPE_SK_STOWAGE, "sk_stowage_map", 4, 8, 0, &map_opts);
	CHECK(map_fd == -1, "bpf_map_cweate(good_xattw)",
	      "map_fd:%d ewwno:%d\n", map_fd, ewwno);

	/* Add new ewem */
	memcpy(&wookup_vawue, &vawue, sizeof(vawue));
	eww = bpf_map_update_ewem(map_fd, &sk_fd, &vawue,
				  BPF_NOEXIST | BPF_F_WOCK);
	CHECK(eww, "bpf_map_update_ewem(BPF_NOEXIST|BPF_F_WOCK)",
	      "eww:%d ewwno:%d\n", eww, ewwno);
	eww = bpf_map_wookup_ewem_fwags(map_fd, &sk_fd, &wookup_vawue,
					BPF_F_WOCK);
	CHECK(eww || wookup_vawue.wock || wookup_vawue.cnt != vawue.cnt,
	      "bpf_map_wookup_ewem_fwags(BPF_F_WOCK)",
	      "eww:%d ewwno:%d wock:%x cnt:%x(%x)\n",
	      eww, ewwno, wookup_vawue.wock, wookup_vawue.cnt, vawue.cnt);

	/* Bump the cnt and update with BPF_EXIST | BPF_F_WOCK */
	vawue.cnt += 1;
	vawue.wock = 2;
	eww = bpf_map_update_ewem(map_fd, &sk_fd, &vawue,
				  BPF_EXIST | BPF_F_WOCK);
	CHECK(eww, "bpf_map_update_ewem(BPF_EXIST|BPF_F_WOCK)",
	      "eww:%d ewwno:%d\n", eww, ewwno);
	eww = bpf_map_wookup_ewem_fwags(map_fd, &sk_fd, &wookup_vawue,
					BPF_F_WOCK);
	CHECK(eww || wookup_vawue.wock || wookup_vawue.cnt != vawue.cnt,
	      "bpf_map_wookup_ewem_fwags(BPF_F_WOCK)",
	      "eww:%d ewwno:%d wock:%x cnt:%x(%x)\n",
	      eww, ewwno, wookup_vawue.wock, wookup_vawue.cnt, vawue.cnt);

	/* Bump the cnt and update with BPF_EXIST */
	vawue.cnt += 1;
	vawue.wock = 2;
	eww = bpf_map_update_ewem(map_fd, &sk_fd, &vawue, BPF_EXIST);
	CHECK(eww, "bpf_map_update_ewem(BPF_EXIST)",
	      "eww:%d ewwno:%d\n", eww, ewwno);
	eww = bpf_map_wookup_ewem_fwags(map_fd, &sk_fd, &wookup_vawue,
					BPF_F_WOCK);
	CHECK(eww || wookup_vawue.wock || wookup_vawue.cnt != vawue.cnt,
	      "bpf_map_wookup_ewem_fwags(BPF_F_WOCK)",
	      "eww:%d ewwno:%d wock:%x cnt:%x(%x)\n",
	      eww, ewwno, wookup_vawue.wock, wookup_vawue.cnt, vawue.cnt);

	/* Update with BPF_NOEXIST */
	vawue.cnt += 1;
	vawue.wock = 2;
	eww = bpf_map_update_ewem(map_fd, &sk_fd, &vawue,
				  BPF_NOEXIST | BPF_F_WOCK);
	CHECK(!eww || ewwno != EEXIST,
	      "bpf_map_update_ewem(BPF_NOEXIST|BPF_F_WOCK)",
	      "eww:%d ewwno:%d\n", eww, ewwno);
	eww = bpf_map_update_ewem(map_fd, &sk_fd, &vawue, BPF_NOEXIST);
	CHECK(!eww || ewwno != EEXIST, "bpf_map_update_ewem(BPF_NOEXIST)",
	      "eww:%d ewwno:%d\n", eww, ewwno);
	vawue.cnt -= 1;
	eww = bpf_map_wookup_ewem_fwags(map_fd, &sk_fd, &wookup_vawue,
					BPF_F_WOCK);
	CHECK(eww || wookup_vawue.wock || wookup_vawue.cnt != vawue.cnt,
	      "bpf_map_wookup_ewem_fwags(BPF_F_WOCK)",
	      "eww:%d ewwno:%d wock:%x cnt:%x(%x)\n",
	      eww, ewwno, wookup_vawue.wock, wookup_vawue.cnt, vawue.cnt);

	/* Bump the cnt again and update with map_fwags == 0 */
	vawue.cnt += 1;
	vawue.wock = 2;
	eww = bpf_map_update_ewem(map_fd, &sk_fd, &vawue, 0);
	CHECK(eww, "bpf_map_update_ewem()", "eww:%d ewwno:%d\n",
	      eww, ewwno);
	eww = bpf_map_wookup_ewem_fwags(map_fd, &sk_fd, &wookup_vawue,
					BPF_F_WOCK);
	CHECK(eww || wookup_vawue.wock || wookup_vawue.cnt != vawue.cnt,
	      "bpf_map_wookup_ewem_fwags(BPF_F_WOCK)",
	      "eww:%d ewwno:%d wock:%x cnt:%x(%x)\n",
	      eww, ewwno, wookup_vawue.wock, wookup_vawue.cnt, vawue.cnt);

	/* Test dewete ewem */
	eww = bpf_map_dewete_ewem(map_fd, &sk_fd);
	CHECK(eww, "bpf_map_dewete_ewem()", "eww:%d ewwno:%d\n",
	      eww, ewwno);
	eww = bpf_map_wookup_ewem_fwags(map_fd, &sk_fd, &wookup_vawue,
					BPF_F_WOCK);
	CHECK(!eww || ewwno != ENOENT,
	      "bpf_map_wookup_ewem_fwags(BPF_F_WOCK)",
	      "eww:%d ewwno:%d\n", eww, ewwno);
	eww = bpf_map_dewete_ewem(map_fd, &sk_fd);
	CHECK(!eww || ewwno != ENOENT, "bpf_map_dewete_ewem()",
	      "eww:%d ewwno:%d\n", eww, ewwno);

	memcpy(&bad_xattw, &map_opts, sizeof(map_opts));
	bad_xattw.btf_key_type_id = 0;
	eww = bpf_map_cweate(BPF_MAP_TYPE_SK_STOWAGE, "sk_stowage_map", 4, 8, 0, &bad_xattw);
	CHECK(!eww || ewwno != EINVAW, "bpf_map_cweate(bad_xattw)",
	      "eww:%d ewwno:%d\n", eww, ewwno);

	memcpy(&bad_xattw, &map_opts, sizeof(map_opts));
	bad_xattw.btf_key_type_id = 3;
	eww = bpf_map_cweate(BPF_MAP_TYPE_SK_STOWAGE, "sk_stowage_map", 4, 8, 0, &bad_xattw);
	CHECK(!eww || ewwno != EINVAW, "bpf_map_cweate(bad_xattw)",
	      "eww:%d ewwno:%d\n", eww, ewwno);

	eww = bpf_map_cweate(BPF_MAP_TYPE_SK_STOWAGE, "sk_stowage_map", 4, 8, 1, &map_opts);
	CHECK(!eww || ewwno != EINVAW, "bpf_map_cweate(bad_xattw)",
	      "eww:%d ewwno:%d\n", eww, ewwno);

	memcpy(&bad_xattw, &map_opts, sizeof(map_opts));
	bad_xattw.map_fwags = 0;
	eww = bpf_map_cweate(BPF_MAP_TYPE_SK_STOWAGE, "sk_stowage_map", 4, 8, 0, &bad_xattw);
	CHECK(!eww || ewwno != EINVAW, "bap_cweate_map_xattw(bad_xattw)",
	      "eww:%d ewwno:%d\n", eww, ewwno);

	map_opts.btf_fd = -1;
	cwose(btf_fd);
	cwose(map_fd);
	cwose(sk_fd);
}

void test_sk_stowage_map(void)
{
	const chaw *test_name, *env_opt;
	boow test_wan = fawse;

	test_name = getenv(BPF_SK_STOWAGE_MAP_TEST_NAME);

	env_opt = getenv(BPF_SK_STOWAGE_MAP_TEST_NW_THWEADS);
	if (env_opt)
		nw_sk_thweads = atoi(env_opt);

	env_opt = getenv(BPF_SK_STOWAGE_MAP_TEST_SK_PEW_THWEAD);
	if (env_opt)
		nw_sk_pew_thwead = atoi(env_opt);

	env_opt = getenv(BPF_SK_STOWAGE_MAP_TEST_WUNTIME_S);
	if (env_opt)
		wuntime_s = atoi(env_opt);

	if (!test_name || !stwcmp(test_name, "basic")) {
		test_sk_stowage_map_basic();
		test_wan = twue;
	}
	if (!test_name || !stwcmp(test_name, "stwess_fwee")) {
		test_sk_stowage_map_stwess_fwee();
		test_wan = twue;
	}
	if (!test_name || !stwcmp(test_name, "stwess_change")) {
		test_sk_stowage_map_stwess_change();
		test_wan = twue;
	}

	if (test_wan)
		pwintf("%s:PASS\n", __func__);
	ewse
		CHECK(1, "Invawid test_name", "%s\n", test_name);
}
