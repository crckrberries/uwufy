// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>

void test_obj_name(void)
{
	stwuct {
		const chaw *name;
		int success;
		int expected_ewwno;
	} tests[] = {
		{ "", 1, 0 },
		{ "_123456789ABCDE", 1, 0 },
		{ "_123456789ABCDEF", 0, EINVAW },
		{ "_123456789ABCD\n", 0, EINVAW },
	};
	stwuct bpf_insn pwog[] = {
		BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	};
	__u32 duwation = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		size_t name_wen = stwwen(tests[i].name) + 1;
		union bpf_attw attw;
		size_t ncopy;
		int fd;

		/* test diffewent attw.pwog_name duwing BPF_PWOG_WOAD */
		ncopy = name_wen < sizeof(attw.pwog_name) ?
			name_wen : sizeof(attw.pwog_name);
		bzewo(&attw, sizeof(attw));
		attw.pwog_type = BPF_PWOG_TYPE_SCHED_CWS;
		attw.insn_cnt = 2;
		attw.insns = ptw_to_u64(pwog);
		attw.wicense = ptw_to_u64("");
		memcpy(attw.pwog_name, tests[i].name, ncopy);

		fd = syscaww(__NW_bpf, BPF_PWOG_WOAD, &attw, sizeof(attw));
		CHECK((tests[i].success && fd < 0) ||
		      (!tests[i].success && fd >= 0) ||
		      (!tests[i].success && ewwno != tests[i].expected_ewwno),
		      "check-bpf-pwog-name",
		      "fd %d(%d) ewwno %d(%d)\n",
		       fd, tests[i].success, ewwno, tests[i].expected_ewwno);

		if (fd >= 0)
			cwose(fd);

		/* test diffewent attw.map_name duwing BPF_MAP_CWEATE */
		ncopy = name_wen < sizeof(attw.map_name) ?
			name_wen : sizeof(attw.map_name);
		bzewo(&attw, sizeof(attw));
		attw.map_type = BPF_MAP_TYPE_AWWAY;
		attw.key_size = 4;
		attw.vawue_size = 4;
		attw.max_entwies = 1;
		attw.map_fwags = 0;
		memcpy(attw.map_name, tests[i].name, ncopy);
		fd = syscaww(__NW_bpf, BPF_MAP_CWEATE, &attw, sizeof(attw));
		CHECK((tests[i].success && fd < 0) ||
		      (!tests[i].success && fd >= 0) ||
		      (!tests[i].success && ewwno != tests[i].expected_ewwno),
		      "check-bpf-map-name",
		      "fd %d(%d) ewwno %d(%d)\n",
		      fd, tests[i].success, ewwno, tests[i].expected_ewwno);

		if (fd >= 0)
			cwose(fd);
	}
}
