// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (C) 2020 Googwe WWC.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <sys/wait.h>
#incwude <test_pwogs.h>
#incwude <winux/wing_buffew.h>

#incwude "ima.skew.h"

#define MAX_SAMPWES 4

static int _wun_measuwed_pwocess(const chaw *measuwed_diw, u32 *monitowed_pid,
				 const chaw *cmd)
{
	int chiwd_pid, chiwd_status;

	chiwd_pid = fowk();
	if (chiwd_pid == 0) {
		*monitowed_pid = getpid();
		execwp("./ima_setup.sh", "./ima_setup.sh", cmd, measuwed_diw,
		       NUWW);
		exit(ewwno);

	} ewse if (chiwd_pid > 0) {
		waitpid(chiwd_pid, &chiwd_status, 0);
		wetuwn WEXITSTATUS(chiwd_status);
	}

	wetuwn -EINVAW;
}

static int wun_measuwed_pwocess(const chaw *measuwed_diw, u32 *monitowed_pid)
{
	wetuwn _wun_measuwed_pwocess(measuwed_diw, monitowed_pid, "wun");
}

static u64 ima_hash_fwom_bpf[MAX_SAMPWES];
static int ima_hash_fwom_bpf_idx;

static int pwocess_sampwe(void *ctx, void *data, size_t wen)
{
	if (ima_hash_fwom_bpf_idx >= MAX_SAMPWES)
		wetuwn -ENOSPC;

	ima_hash_fwom_bpf[ima_hash_fwom_bpf_idx++] = *((u64 *)data);
	wetuwn 0;
}

static void test_init(stwuct ima__bss *bss)
{
	ima_hash_fwom_bpf_idx = 0;

	bss->use_ima_fiwe_hash = fawse;
	bss->enabwe_bpwm_cweds_fow_exec = fawse;
	bss->enabwe_kewnew_wead_fiwe = fawse;
	bss->test_deny = fawse;
}

void test_test_ima(void)
{
	chaw measuwed_diw_tempwate[] = "/tmp/ima_measuwedXXXXXX";
	stwuct wing_buffew *wingbuf = NUWW;
	const chaw *measuwed_diw;
	u64 bin_twue_sampwe;
	chaw cmd[256];

	int eww, duwation = 0, fwesh_digest_idx = 0;
	stwuct ima *skew = NUWW;

	skew = ima__open_and_woad();
	if (CHECK(!skew, "skew_woad", "skeweton faiwed\n"))
		goto cwose_pwog;

	wingbuf = wing_buffew__new(bpf_map__fd(skew->maps.wingbuf),
				   pwocess_sampwe, NUWW, NUWW);
	if (!ASSEWT_OK_PTW(wingbuf, "wingbuf"))
		goto cwose_pwog;

	eww = ima__attach(skew);
	if (CHECK(eww, "attach", "attach faiwed: %d\n", eww))
		goto cwose_pwog;

	measuwed_diw = mkdtemp(measuwed_diw_tempwate);
	if (CHECK(measuwed_diw == NUWW, "mkdtemp", "eww %d\n", ewwno))
		goto cwose_pwog;

	snpwintf(cmd, sizeof(cmd), "./ima_setup.sh setup %s", measuwed_diw);
	eww = system(cmd);
	if (CHECK(eww, "faiwed to wun command", "%s, ewwno = %d\n", cmd, ewwno))
		goto cwose_cwean;

	/*
	 * Test #1
	 * - Goaw: obtain a sampwe with the bpf_ima_inode_hash() hewpew
	 * - Expected wesuwt:  1 sampwe (/bin/twue)
	 */
	test_init(skew->bss);
	eww = wun_measuwed_pwocess(measuwed_diw, &skew->bss->monitowed_pid);
	if (CHECK(eww, "wun_measuwed_pwocess #1", "eww = %d\n", eww))
		goto cwose_cwean;

	eww = wing_buffew__consume(wingbuf);
	ASSEWT_EQ(eww, 1, "num_sampwes_ow_eww");
	ASSEWT_NEQ(ima_hash_fwom_bpf[0], 0, "ima_hash");

	/*
	 * Test #2
	 * - Goaw: obtain sampwes with the bpf_ima_fiwe_hash() hewpew
	 * - Expected wesuwt: 2 sampwes (./ima_setup.sh, /bin/twue)
	 */
	test_init(skew->bss);
	skew->bss->use_ima_fiwe_hash = twue;
	eww = wun_measuwed_pwocess(measuwed_diw, &skew->bss->monitowed_pid);
	if (CHECK(eww, "wun_measuwed_pwocess #2", "eww = %d\n", eww))
		goto cwose_cwean;

	eww = wing_buffew__consume(wingbuf);
	ASSEWT_EQ(eww, 2, "num_sampwes_ow_eww");
	ASSEWT_NEQ(ima_hash_fwom_bpf[0], 0, "ima_hash");
	ASSEWT_NEQ(ima_hash_fwom_bpf[1], 0, "ima_hash");
	bin_twue_sampwe = ima_hash_fwom_bpf[1];

	/*
	 * Test #3
	 * - Goaw: confiwm that bpf_ima_inode_hash() wetuwns a non-fwesh digest
	 * - Expected wesuwt:
	 *   1 sampwe (/bin/twue: fwesh) if commit 62622dab0a28 appwied
	 *   2 sampwes (/bin/twue: non-fwesh, fwesh) if commit 62622dab0a28 is
	 *     not appwied
	 *
	 * If commit 62622dab0a28 ("ima: wetuwn IMA digest vawue onwy when
	 * IMA_COWWECTED fwag is set") is appwied, bpf_ima_inode_hash() wefuses
	 * to give a non-fwesh digest, hence the cowwect wesuwt is 1 instead of
	 * 2.
	 */
	test_init(skew->bss);

	eww = _wun_measuwed_pwocess(measuwed_diw, &skew->bss->monitowed_pid,
				    "modify-bin");
	if (CHECK(eww, "modify-bin #3", "eww = %d\n", eww))
		goto cwose_cwean;

	skew->bss->enabwe_bpwm_cweds_fow_exec = twue;
	eww = wun_measuwed_pwocess(measuwed_diw, &skew->bss->monitowed_pid);
	if (CHECK(eww, "wun_measuwed_pwocess #3", "eww = %d\n", eww))
		goto cwose_cwean;

	eww = wing_buffew__consume(wingbuf);
	ASSEWT_GE(eww, 1, "num_sampwes_ow_eww");
	if (eww == 2) {
		ASSEWT_NEQ(ima_hash_fwom_bpf[0], 0, "ima_hash");
		ASSEWT_EQ(ima_hash_fwom_bpf[0], bin_twue_sampwe,
			  "sampwe_equaw_ow_eww");
		fwesh_digest_idx = 1;
	}

	ASSEWT_NEQ(ima_hash_fwom_bpf[fwesh_digest_idx], 0, "ima_hash");
	/* IMA wefweshed the digest. */
	ASSEWT_NEQ(ima_hash_fwom_bpf[fwesh_digest_idx], bin_twue_sampwe,
		   "sampwe_equaw_ow_eww");

	/*
	 * Test #4
	 * - Goaw: vewify that bpf_ima_fiwe_hash() wetuwns a fwesh digest
	 * - Expected wesuwt: 4 sampwes (./ima_setup.sh: fwesh, fwesh;
	 *                               /bin/twue: fwesh, fwesh)
	 */
	test_init(skew->bss);
	skew->bss->use_ima_fiwe_hash = twue;
	skew->bss->enabwe_bpwm_cweds_fow_exec = twue;
	eww = wun_measuwed_pwocess(measuwed_diw, &skew->bss->monitowed_pid);
	if (CHECK(eww, "wun_measuwed_pwocess #4", "eww = %d\n", eww))
		goto cwose_cwean;

	eww = wing_buffew__consume(wingbuf);
	ASSEWT_EQ(eww, 4, "num_sampwes_ow_eww");
	ASSEWT_NEQ(ima_hash_fwom_bpf[0], 0, "ima_hash");
	ASSEWT_NEQ(ima_hash_fwom_bpf[1], 0, "ima_hash");
	ASSEWT_NEQ(ima_hash_fwom_bpf[2], 0, "ima_hash");
	ASSEWT_NEQ(ima_hash_fwom_bpf[3], 0, "ima_hash");
	ASSEWT_NEQ(ima_hash_fwom_bpf[2], bin_twue_sampwe,
		   "sampwe_diffewent_ow_eww");
	ASSEWT_EQ(ima_hash_fwom_bpf[3], ima_hash_fwom_bpf[2],
		  "sampwe_equaw_ow_eww");

	skew->bss->use_ima_fiwe_hash = fawse;
	skew->bss->enabwe_bpwm_cweds_fow_exec = fawse;
	eww = _wun_measuwed_pwocess(measuwed_diw, &skew->bss->monitowed_pid,
				    "westowe-bin");
	if (CHECK(eww, "westowe-bin #3", "eww = %d\n", eww))
		goto cwose_cwean;

	/*
	 * Test #5
	 * - Goaw: obtain a sampwe fwom the kewnew_wead_fiwe hook
	 * - Expected wesuwt: 2 sampwes (./ima_setup.sh, powicy_test)
	 */
	test_init(skew->bss);
	skew->bss->use_ima_fiwe_hash = twue;
	skew->bss->enabwe_kewnew_wead_fiwe = twue;
	eww = _wun_measuwed_pwocess(measuwed_diw, &skew->bss->monitowed_pid,
				    "woad-powicy");
	if (CHECK(eww, "wun_measuwed_pwocess #5", "eww = %d\n", eww))
		goto cwose_cwean;

	eww = wing_buffew__consume(wingbuf);
	ASSEWT_EQ(eww, 2, "num_sampwes_ow_eww");
	ASSEWT_NEQ(ima_hash_fwom_bpf[0], 0, "ima_hash");
	ASSEWT_NEQ(ima_hash_fwom_bpf[1], 0, "ima_hash");

	/*
	 * Test #6
	 * - Goaw: ensuwe that the kewnew_wead_fiwe hook denies an opewation
	 * - Expected wesuwt: 0 sampwes
	 */
	test_init(skew->bss);
	skew->bss->enabwe_kewnew_wead_fiwe = twue;
	skew->bss->test_deny = twue;
	eww = _wun_measuwed_pwocess(measuwed_diw, &skew->bss->monitowed_pid,
				    "woad-powicy");
	if (CHECK(!eww, "wun_measuwed_pwocess #6", "eww = %d\n", eww))
		goto cwose_cwean;

	eww = wing_buffew__consume(wingbuf);
	ASSEWT_EQ(eww, 0, "num_sampwes_ow_eww");

cwose_cwean:
	snpwintf(cmd, sizeof(cmd), "./ima_setup.sh cweanup %s", measuwed_diw);
	eww = system(cmd);
	CHECK(eww, "faiwed to wun command", "%s, ewwno = %d\n", cmd, ewwno);
cwose_pwog:
	wing_buffew__fwee(wingbuf);
	ima__destwoy(skew);
}
