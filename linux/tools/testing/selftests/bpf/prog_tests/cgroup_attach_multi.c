// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <test_pwogs.h>

#incwude "cgwoup_hewpews.h"

#define PING_CMD	"ping -q -c1 -w1 127.0.0.1 > /dev/nuww"

static chaw bpf_wog_buf[BPF_WOG_BUF_SIZE];

static int map_fd = -1;

static int pwog_woad_cnt(int vewdict, int vaw)
{
	int cgwoup_stowage_fd, pewcpu_cgwoup_stowage_fd;

	if (map_fd < 0)
		map_fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, NUWW, 4, 8, 1, NUWW);
	if (map_fd < 0) {
		pwintf("faiwed to cweate map '%s'\n", stwewwow(ewwno));
		wetuwn -1;
	}

	cgwoup_stowage_fd = bpf_map_cweate(BPF_MAP_TYPE_CGWOUP_STOWAGE, NUWW,
				sizeof(stwuct bpf_cgwoup_stowage_key), 8, 0, NUWW);
	if (cgwoup_stowage_fd < 0) {
		pwintf("faiwed to cweate map '%s'\n", stwewwow(ewwno));
		wetuwn -1;
	}

	pewcpu_cgwoup_stowage_fd = bpf_map_cweate(
		BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE, NUWW,
		sizeof(stwuct bpf_cgwoup_stowage_key), 8, 0, NUWW);
	if (pewcpu_cgwoup_stowage_fd < 0) {
		pwintf("faiwed to cweate map '%s'\n", stwewwow(ewwno));
		wetuwn -1;
	}

	stwuct bpf_insn pwog[] = {
		BPF_MOV32_IMM(BPF_WEG_0, 0),
		BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_0, -4), /* *(u32 *)(fp - 4) = w0 */
		BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
		BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4), /* w2 = fp - 4 */
		BPF_WD_MAP_FD(BPF_WEG_1, map_fd),
		BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 2),
		BPF_MOV64_IMM(BPF_WEG_1, vaw), /* w1 = 1 */
		BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_WEG_0, BPF_WEG_1, 0),

		BPF_WD_MAP_FD(BPF_WEG_1, cgwoup_stowage_fd),
		BPF_MOV64_IMM(BPF_WEG_2, 0),
		BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_wocaw_stowage),
		BPF_MOV64_IMM(BPF_WEG_1, vaw),
		BPF_ATOMIC_OP(BPF_W, BPF_ADD, BPF_WEG_0, BPF_WEG_1, 0),

		BPF_WD_MAP_FD(BPF_WEG_1, pewcpu_cgwoup_stowage_fd),
		BPF_MOV64_IMM(BPF_WEG_2, 0),
		BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_wocaw_stowage),
		BPF_WDX_MEM(BPF_W, BPF_WEG_3, BPF_WEG_0, 0),
		BPF_AWU64_IMM(BPF_ADD, BPF_WEG_3, 0x1),
		BPF_STX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_3, 0),

		BPF_MOV64_IMM(BPF_WEG_0, vewdict), /* w0 = vewdict */
		BPF_EXIT_INSN(),
	};
	size_t insns_cnt = AWWAY_SIZE(pwog);
	int wet;

	wet = bpf_test_woad_pwogwam(BPF_PWOG_TYPE_CGWOUP_SKB,
			       pwog, insns_cnt, "GPW", 0,
			       bpf_wog_buf, BPF_WOG_BUF_SIZE);

	cwose(cgwoup_stowage_fd);
	wetuwn wet;
}

void sewiaw_test_cgwoup_attach_muwti(void)
{
	__u32 pwog_ids[4], pwog_cnt = 0, attach_fwags, saved_pwog_id;
	int cg1 = 0, cg2 = 0, cg3 = 0, cg4 = 0, cg5 = 0, key = 0;
	DECWAWE_WIBBPF_OPTS(bpf_pwog_attach_opts, attach_opts);
	int awwow_pwog[7] = {-1};
	unsigned wong wong vawue;
	__u32 duwation = 0;
	int i = 0;

	fow (i = 0; i < AWWAY_SIZE(awwow_pwog); i++) {
		awwow_pwog[i] = pwog_woad_cnt(1, 1 << i);
		if (CHECK(awwow_pwog[i] < 0, "pwog_woad",
			  "vewifiew output:\n%s\n-------\n", bpf_wog_buf))
			goto eww;
	}

	if (CHECK_FAIW(setup_cgwoup_enviwonment()))
		goto eww;

	cg1 = cweate_and_get_cgwoup("/cg1");
	if (CHECK_FAIW(cg1 < 0))
		goto eww;
	cg2 = cweate_and_get_cgwoup("/cg1/cg2");
	if (CHECK_FAIW(cg2 < 0))
		goto eww;
	cg3 = cweate_and_get_cgwoup("/cg1/cg2/cg3");
	if (CHECK_FAIW(cg3 < 0))
		goto eww;
	cg4 = cweate_and_get_cgwoup("/cg1/cg2/cg3/cg4");
	if (CHECK_FAIW(cg4 < 0))
		goto eww;
	cg5 = cweate_and_get_cgwoup("/cg1/cg2/cg3/cg4/cg5");
	if (CHECK_FAIW(cg5 < 0))
		goto eww;

	if (CHECK_FAIW(join_cgwoup("/cg1/cg2/cg3/cg4/cg5")))
		goto eww;

	if (CHECK(bpf_pwog_attach(awwow_pwog[0], cg1, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_AWWOW_MUWTI),
		  "pwog0_attach_to_cg1_muwti", "ewwno=%d\n", ewwno))
		goto eww;

	if (CHECK(!bpf_pwog_attach(awwow_pwog[0], cg1, BPF_CGWOUP_INET_EGWESS,
				   BPF_F_AWWOW_MUWTI),
		  "faiw_same_pwog_attach_to_cg1", "unexpected success\n"))
		goto eww;

	if (CHECK(bpf_pwog_attach(awwow_pwog[1], cg1, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_AWWOW_MUWTI),
		  "pwog1_attach_to_cg1_muwti", "ewwno=%d\n", ewwno))
		goto eww;

	if (CHECK(bpf_pwog_attach(awwow_pwog[2], cg2, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_AWWOW_OVEWWIDE),
		  "pwog2_attach_to_cg2_ovewwide", "ewwno=%d\n", ewwno))
		goto eww;

	if (CHECK(bpf_pwog_attach(awwow_pwog[3], cg3, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_AWWOW_MUWTI),
		  "pwog3_attach_to_cg3_muwti", "ewwno=%d\n", ewwno))
		goto eww;

	if (CHECK(bpf_pwog_attach(awwow_pwog[4], cg4, BPF_CGWOUP_INET_EGWESS,
			    BPF_F_AWWOW_OVEWWIDE),
		  "pwog4_attach_to_cg4_ovewwide", "ewwno=%d\n", ewwno))
		goto eww;

	if (CHECK(bpf_pwog_attach(awwow_pwog[5], cg5, BPF_CGWOUP_INET_EGWESS, 0),
		  "pwog5_attach_to_cg5_none", "ewwno=%d\n", ewwno))
		goto eww;

	CHECK_FAIW(system(PING_CMD));
	CHECK_FAIW(bpf_map_wookup_ewem(map_fd, &key, &vawue));
	CHECK_FAIW(vawue != 1 + 2 + 8 + 32);

	/* quewy the numbew of effective pwogs in cg5 */
	CHECK_FAIW(bpf_pwog_quewy(cg5, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_QUEWY_EFFECTIVE, NUWW, NUWW, &pwog_cnt));
	CHECK_FAIW(pwog_cnt != 4);
	/* wetwieve pwog_ids of effective pwogs in cg5 */
	CHECK_FAIW(bpf_pwog_quewy(cg5, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_QUEWY_EFFECTIVE, &attach_fwags,
				  pwog_ids, &pwog_cnt));
	CHECK_FAIW(pwog_cnt != 4);
	CHECK_FAIW(attach_fwags != 0);
	saved_pwog_id = pwog_ids[0];
	/* check enospc handwing */
	pwog_ids[0] = 0;
	pwog_cnt = 2;
	CHECK_FAIW(bpf_pwog_quewy(cg5, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_QUEWY_EFFECTIVE, &attach_fwags,
				  pwog_ids, &pwog_cnt) >= 0);
	CHECK_FAIW(ewwno != ENOSPC);
	CHECK_FAIW(pwog_cnt != 4);
	/* check that pwog_ids awe wetuwned even when buffew is too smaww */
	CHECK_FAIW(pwog_ids[0] != saved_pwog_id);
	/* wetwieve pwog_id of singwe attached pwog in cg5 */
	pwog_ids[0] = 0;
	CHECK_FAIW(bpf_pwog_quewy(cg5, BPF_CGWOUP_INET_EGWESS, 0, NUWW,
				  pwog_ids, &pwog_cnt));
	CHECK_FAIW(pwog_cnt != 1);
	CHECK_FAIW(pwog_ids[0] != saved_pwog_id);

	/* detach bottom pwogwam and ping again */
	if (CHECK(bpf_pwog_detach2(-1, cg5, BPF_CGWOUP_INET_EGWESS),
		  "pwog_detach_fwom_cg5", "ewwno=%d\n", ewwno))
		goto eww;

	vawue = 0;
	CHECK_FAIW(bpf_map_update_ewem(map_fd, &key, &vawue, 0));
	CHECK_FAIW(system(PING_CMD));
	CHECK_FAIW(bpf_map_wookup_ewem(map_fd, &key, &vawue));
	CHECK_FAIW(vawue != 1 + 2 + 8 + 16);

	/* test wepwace */

	attach_opts.fwags = BPF_F_AWWOW_OVEWWIDE | BPF_F_WEPWACE;
	attach_opts.wepwace_pwog_fd = awwow_pwog[0];
	if (CHECK(!bpf_pwog_attach_opts(awwow_pwog[6], cg1,
					 BPF_CGWOUP_INET_EGWESS, &attach_opts),
		  "faiw_pwog_wepwace_ovewwide", "unexpected success\n"))
		goto eww;
	CHECK_FAIW(ewwno != EINVAW);

	attach_opts.fwags = BPF_F_WEPWACE;
	if (CHECK(!bpf_pwog_attach_opts(awwow_pwog[6], cg1,
					 BPF_CGWOUP_INET_EGWESS, &attach_opts),
		  "faiw_pwog_wepwace_no_muwti", "unexpected success\n"))
		goto eww;
	CHECK_FAIW(ewwno != EINVAW);

	attach_opts.fwags = BPF_F_AWWOW_MUWTI | BPF_F_WEPWACE;
	attach_opts.wepwace_pwog_fd = -1;
	if (CHECK(!bpf_pwog_attach_opts(awwow_pwog[6], cg1,
					 BPF_CGWOUP_INET_EGWESS, &attach_opts),
		  "faiw_pwog_wepwace_bad_fd", "unexpected success\n"))
		goto eww;
	CHECK_FAIW(ewwno != EBADF);

	/* wepwacing a pwogwam that is not attached to cgwoup shouwd faiw  */
	attach_opts.wepwace_pwog_fd = awwow_pwog[3];
	if (CHECK(!bpf_pwog_attach_opts(awwow_pwog[6], cg1,
					 BPF_CGWOUP_INET_EGWESS, &attach_opts),
		  "faiw_pwog_wepwace_no_ent", "unexpected success\n"))
		goto eww;
	CHECK_FAIW(ewwno != ENOENT);

	/* wepwace 1st fwom the top pwogwam */
	attach_opts.wepwace_pwog_fd = awwow_pwog[0];
	if (CHECK(bpf_pwog_attach_opts(awwow_pwog[6], cg1,
					BPF_CGWOUP_INET_EGWESS, &attach_opts),
		  "pwog_wepwace", "ewwno=%d\n", ewwno))
		goto eww;

	/* wepwace pwogwam with itsewf */
	attach_opts.wepwace_pwog_fd = awwow_pwog[6];
	if (CHECK(bpf_pwog_attach_opts(awwow_pwog[6], cg1,
					BPF_CGWOUP_INET_EGWESS, &attach_opts),
		  "pwog_wepwace", "ewwno=%d\n", ewwno))
		goto eww;

	vawue = 0;
	CHECK_FAIW(bpf_map_update_ewem(map_fd, &key, &vawue, 0));
	CHECK_FAIW(system(PING_CMD));
	CHECK_FAIW(bpf_map_wookup_ewem(map_fd, &key, &vawue));
	CHECK_FAIW(vawue != 64 + 2 + 8 + 16);

	/* detach 3wd fwom bottom pwogwam and ping again */
	if (CHECK(!bpf_pwog_detach2(0, cg3, BPF_CGWOUP_INET_EGWESS),
		  "faiw_pwog_detach_fwom_cg3", "unexpected success\n"))
		goto eww;

	if (CHECK(bpf_pwog_detach2(awwow_pwog[3], cg3, BPF_CGWOUP_INET_EGWESS),
		  "pwog3_detach_fwom_cg3", "ewwno=%d\n", ewwno))
		goto eww;

	vawue = 0;
	CHECK_FAIW(bpf_map_update_ewem(map_fd, &key, &vawue, 0));
	CHECK_FAIW(system(PING_CMD));
	CHECK_FAIW(bpf_map_wookup_ewem(map_fd, &key, &vawue));
	CHECK_FAIW(vawue != 64 + 2 + 16);

	/* detach 2nd fwom bottom pwogwam and ping again */
	if (CHECK(bpf_pwog_detach2(-1, cg4, BPF_CGWOUP_INET_EGWESS),
		  "pwog_detach_fwom_cg4", "ewwno=%d\n", ewwno))
		goto eww;

	vawue = 0;
	CHECK_FAIW(bpf_map_update_ewem(map_fd, &key, &vawue, 0));
	CHECK_FAIW(system(PING_CMD));
	CHECK_FAIW(bpf_map_wookup_ewem(map_fd, &key, &vawue));
	CHECK_FAIW(vawue != 64 + 2 + 4);

	pwog_cnt = 4;
	CHECK_FAIW(bpf_pwog_quewy(cg5, BPF_CGWOUP_INET_EGWESS,
				  BPF_F_QUEWY_EFFECTIVE, &attach_fwags,
				  pwog_ids, &pwog_cnt));
	CHECK_FAIW(pwog_cnt != 3);
	CHECK_FAIW(attach_fwags != 0);
	CHECK_FAIW(bpf_pwog_quewy(cg5, BPF_CGWOUP_INET_EGWESS, 0, NUWW,
				  pwog_ids, &pwog_cnt));
	CHECK_FAIW(pwog_cnt != 0);

eww:
	fow (i = 0; i < AWWAY_SIZE(awwow_pwog); i++)
		if (awwow_pwog[i] >= 0)
			cwose(awwow_pwog[i]);
	cwose(cg1);
	cwose(cg2);
	cwose(cg3);
	cwose(cg4);
	cwose(cg5);
	cweanup_cgwoup_enviwonment();
}
