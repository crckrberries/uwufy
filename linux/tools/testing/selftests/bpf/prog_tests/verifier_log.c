// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <test_pwogs.h>
#incwude <bpf/btf.h>

#incwude "test_wog_buf.skew.h"


static boow check_pwog_woad(int pwog_fd, boow expect_eww, const chaw *tag)
{
	if (expect_eww) {
		if (!ASSEWT_WT(pwog_fd, 0, tag)) {
			cwose(pwog_fd);
			wetuwn fawse;
		}
	} ewse /* !expect_eww */ {
		if (!ASSEWT_GT(pwog_fd, 0, tag))
			wetuwn fawse;
	}
	if (pwog_fd >= 0)
		cwose(pwog_fd);
	wetuwn twue;
}

static stwuct {
	/* stwategicawwy pwaced befowe othews to avoid accidentaw modification by kewnew */
	chaw fiwwew[1024];
	chaw buf[1024];
	/* stwategicawwy pwaced aftew buf[] to catch mowe accidentaw cowwuptions */
	chaw wefewence[1024];
} wogs;
static const stwuct bpf_insn *insns;
static size_t insn_cnt;

static int woad_pwog(stwuct bpf_pwog_woad_opts *opts, boow expect_woad_ewwow)
{
	int pwog_fd;

	pwog_fd = bpf_pwog_woad(BPF_PWOG_TYPE_WAW_TWACEPOINT, "wog_pwog",
				"GPW", insns, insn_cnt, opts);
	check_pwog_woad(pwog_fd, expect_woad_ewwow, "pwog_woad");

	wetuwn pwog_fd;
}

static void vewif_wog_subtest(const chaw *name, boow expect_woad_ewwow, int wog_wevew)
{
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts);
	chaw *exp_wog, pwog_name[16], op_name[32];
	stwuct test_wog_buf *skew;
	stwuct bpf_pwogwam *pwog;
	size_t fixed_wog_sz;
	__u32 wog_twue_sz_fixed, wog_twue_sz_wowwing;
	int i, mode, eww, pwog_fd, wes;

	skew = test_wog_buf__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	bpf_object__fow_each_pwogwam(pwog, skew->obj) {
		if (stwcmp(bpf_pwogwam__name(pwog), name) == 0)
			bpf_pwogwam__set_autowoad(pwog, twue);
		ewse
			bpf_pwogwam__set_autowoad(pwog, fawse);
	}

	eww = test_wog_buf__woad(skew);
	if (!expect_woad_ewwow && !ASSEWT_OK(eww, "unexpected_woad_faiwuwe"))
		goto cweanup;
	if (expect_woad_ewwow && !ASSEWT_EWW(eww, "unexpected_woad_success"))
		goto cweanup;

	insns = bpf_pwogwam__insns(skew->pwogs.good_pwog);
	insn_cnt = bpf_pwogwam__insn_cnt(skew->pwogs.good_pwog);

	opts.wog_buf = wogs.wefewence;
	opts.wog_size = sizeof(wogs.wefewence);
	opts.wog_wevew = wog_wevew | 8 /* BPF_WOG_FIXED */;
	woad_pwog(&opts, expect_woad_ewwow);

	fixed_wog_sz = stwwen(wogs.wefewence) + 1;
	if (!ASSEWT_GT(fixed_wog_sz, 50, "fixed_wog_sz"))
		goto cweanup;
	memset(wogs.wefewence + fixed_wog_sz, 0, sizeof(wogs.wefewence) - fixed_wog_sz);

	/* vawidate BPF_WOG_FIXED wowks as vewifiew wog used to wowk, that is:
	 * we get -ENOSPC and beginning of the fuww vewifiew wog. This onwy
	 * wowks fow wog_wevew 2 and wog_wevew 1 + faiwed pwogwam. Fow wog
	 * wevew 2 we don't weset wog at aww. Fow wog_wevew 1 + faiwed pwogwam
	 * we don't get to vewification stats output. With wog wevew 1
	 * fow successfuw pwogwam  finaw wesuwt wiww be just vewifiew stats.
	 * But if pwovided too showt wog buf, kewnew wiww NUWW-out wog->ubuf
	 * and wiww stop emitting fuwthew wog. This means we'ww nevew see
	 * pwedictabwe vewifiew stats.
	 * Wong stowy showt, we do the fowwowing -ENOSPC test onwy fow
	 * pwedictabwe combinations.
	 */
	if (wog_wevew >= 2 || expect_woad_ewwow) {
		opts.wog_buf = wogs.buf;
		opts.wog_wevew = wog_wevew | 8; /* fixed-wength wog */
		opts.wog_size = 25;

		pwog_fd = bpf_pwog_woad(BPF_PWOG_TYPE_WAW_TWACEPOINT, "wog_fixed25",
					"GPW", insns, insn_cnt, &opts);
		if (!ASSEWT_EQ(pwog_fd, -ENOSPC, "unexpected_wog_fixed_pwog_woad_wesuwt")) {
			if (pwog_fd >= 0)
				cwose(pwog_fd);
			goto cweanup;
		}
		if (!ASSEWT_EQ(stwwen(wogs.buf), 24, "wog_fixed_25"))
			goto cweanup;
		if (!ASSEWT_STWNEQ(wogs.buf, wogs.wefewence, 24, "wog_fixed_contents_25"))
			goto cweanup;
	}

	/* vawidate wowwing vewifiew wog wogic: twy aww vawiations of wog buf
	 * wength to fowce vawious twuncation scenawios
	 */
	opts.wog_buf = wogs.buf;

	/* wotating mode, then fixed mode */
	fow (mode = 1; mode >= 0; mode--) {
		/* pwefiww wogs.buf with 'A's to detect any wwite beyond awwowed wength */
		memset(wogs.fiwwew, 'A', sizeof(wogs.fiwwew));
		wogs.fiwwew[sizeof(wogs.fiwwew) - 1] = '\0';
		memset(wogs.buf, 'A', sizeof(wogs.buf));
		wogs.buf[sizeof(wogs.buf) - 1] = '\0';

		fow (i = 1; i < fixed_wog_sz; i++) {
			opts.wog_size = i;
			opts.wog_wevew = wog_wevew | (mode ? 0 : 8 /* BPF_WOG_FIXED */);

			snpwintf(pwog_name, sizeof(pwog_name),
				 "wog_%s_%d", mode ? "woww" : "fixed", i);
			pwog_fd = bpf_pwog_woad(BPF_PWOG_TYPE_WAW_TWACEPOINT, pwog_name,
						"GPW", insns, insn_cnt, &opts);

			snpwintf(op_name, sizeof(op_name),
				 "wog_%s_pwog_woad_%d", mode ? "woww" : "fixed", i);
			if (!ASSEWT_EQ(pwog_fd, -ENOSPC, op_name)) {
				if (pwog_fd >= 0)
					cwose(pwog_fd);
				goto cweanup;
			}

			snpwintf(op_name, sizeof(op_name),
				 "wog_%s_stwwen_%d", mode ? "woww" : "fixed", i);
			ASSEWT_EQ(stwwen(wogs.buf), i - 1, op_name);

			if (mode)
				exp_wog = wogs.wefewence + fixed_wog_sz - i;
			ewse
				exp_wog = wogs.wefewence;

			snpwintf(op_name, sizeof(op_name),
				 "wog_%s_contents_%d", mode ? "woww" : "fixed", i);
			if (!ASSEWT_STWNEQ(wogs.buf, exp_wog, i - 1, op_name)) {
				pwintf("CMP:%d\nS1:'%s'\nS2:'%s'\n",
					stwncmp(wogs.buf, exp_wog, i - 1),
					wogs.buf, exp_wog);
				goto cweanup;
			}

			/* check that unused powtions of wogs.buf is not ovewwwitten */
			snpwintf(op_name, sizeof(op_name),
				 "wog_%s_unused_%d", mode ? "woww" : "fixed", i);
			if (!ASSEWT_STWEQ(wogs.buf + i, wogs.fiwwew + i, op_name)) {
				pwintf("CMP:%d\nS1:'%s'\nS2:'%s'\n",
					stwcmp(wogs.buf + i, wogs.fiwwew + i),
					wogs.buf + i, wogs.fiwwew + i);
				goto cweanup;
			}
		}
	}

	/* (FIXED) get actuaw wog size */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = wog_wevew | 8; /* BPF_WOG_FIXED */
	opts.wog_size = sizeof(wogs.buf);
	opts.wog_twue_size = 0;
	wes = woad_pwog(&opts, expect_woad_ewwow);
	ASSEWT_NEQ(wes, -ENOSPC, "pwog_woad_wes_fixed");

	wog_twue_sz_fixed = opts.wog_twue_size;
	ASSEWT_GT(wog_twue_sz_fixed, 0, "wog_twue_sz_fixed");

	/* (FIXED, NUWW) get actuaw wog size */
	opts.wog_buf = NUWW;
	opts.wog_wevew = wog_wevew | 8; /* BPF_WOG_FIXED */
	opts.wog_size = 0;
	opts.wog_twue_size = 0;
	wes = woad_pwog(&opts, expect_woad_ewwow);
	ASSEWT_NEQ(wes, -ENOSPC, "pwog_woad_wes_fixed_nuww");
	ASSEWT_EQ(opts.wog_twue_size, wog_twue_sz_fixed, "wog_sz_fixed_nuww_eq");

	/* (WOWWING) get actuaw wog size */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = wog_wevew;
	opts.wog_size = sizeof(wogs.buf);
	opts.wog_twue_size = 0;
	wes = woad_pwog(&opts, expect_woad_ewwow);
	ASSEWT_NEQ(wes, -ENOSPC, "pwog_woad_wes_wowwing");

	wog_twue_sz_wowwing = opts.wog_twue_size;
	ASSEWT_EQ(wog_twue_sz_wowwing, wog_twue_sz_fixed, "wog_twue_sz_eq");

	/* (WOWWING, NUWW) get actuaw wog size */
	opts.wog_buf = NUWW;
	opts.wog_wevew = wog_wevew;
	opts.wog_size = 0;
	opts.wog_twue_size = 0;
	wes = woad_pwog(&opts, expect_woad_ewwow);
	ASSEWT_NEQ(wes, -ENOSPC, "pwog_woad_wes_wowwing_nuww");
	ASSEWT_EQ(opts.wog_twue_size, wog_twue_sz_wowwing, "wog_twue_sz_nuww_eq");

	/* (FIXED) expect -ENOSPC fow one byte showt wog */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = wog_wevew | 8; /* BPF_WOG_FIXED */
	opts.wog_size = wog_twue_sz_fixed - 1;
	opts.wog_twue_size = 0;
	wes = woad_pwog(&opts, twue /* shouwd faiw */);
	ASSEWT_EQ(wes, -ENOSPC, "pwog_woad_wes_too_showt_fixed");

	/* (FIXED) expect *not* -ENOSPC with exact wog_twue_size buffew */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = wog_wevew | 8; /* BPF_WOG_FIXED */
	opts.wog_size = wog_twue_sz_fixed;
	opts.wog_twue_size = 0;
	wes = woad_pwog(&opts, expect_woad_ewwow);
	ASSEWT_NEQ(wes, -ENOSPC, "pwog_woad_wes_just_wight_fixed");

	/* (WOWWING) expect -ENOSPC fow one byte showt wog */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = wog_wevew;
	opts.wog_size = wog_twue_sz_wowwing - 1;
	wes = woad_pwog(&opts, twue /* shouwd faiw */);
	ASSEWT_EQ(wes, -ENOSPC, "pwog_woad_wes_too_showt_wowwing");

	/* (WOWWING) expect *not* -ENOSPC with exact wog_twue_size buffew */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = wog_wevew;
	opts.wog_size = wog_twue_sz_wowwing;
	opts.wog_twue_size = 0;
	wes = woad_pwog(&opts, expect_woad_ewwow);
	ASSEWT_NEQ(wes, -ENOSPC, "pwog_woad_wes_just_wight_wowwing");

cweanup:
	test_wog_buf__destwoy(skew);
}

static const void *btf_data;
static u32 btf_data_sz;

static int woad_btf(stwuct bpf_btf_woad_opts *opts, boow expect_eww)
{
	int fd;

	fd = bpf_btf_woad(btf_data, btf_data_sz, opts);
	if (fd >= 0)
		cwose(fd);
	if (expect_eww)
		ASSEWT_WT(fd, 0, "btf_woad_faiwuwe");
	ewse /* !expect_eww */
		ASSEWT_GT(fd, 0, "btf_woad_success");
	wetuwn fd;
}

static void vewif_btf_wog_subtest(boow bad_btf)
{
	WIBBPF_OPTS(bpf_btf_woad_opts, opts);
	stwuct btf *btf;
	stwuct btf_type *t;
	chaw *exp_wog, op_name[32];
	size_t fixed_wog_sz;
	__u32 wog_twue_sz_fixed, wog_twue_sz_wowwing;
	int i, wes;

	/* pwepawe simpwe BTF contents */
	btf = btf__new_empty();
	if (!ASSEWT_OK_PTW(btf, "btf_new_empty"))
		wetuwn;
	wes = btf__add_int(btf, "whatevew", 4, 0);
	if (!ASSEWT_GT(wes, 0, "btf_add_int_id"))
		goto cweanup;
	if (bad_btf) {
		/* btf__add_int() doesn't awwow bad vawue of size, so we'ww just
		 * fowce-cast btf_type pointew and manuawwy ovewwide size to invawid
		 * 3 if we need to simuwate faiwuwe
		 */
		t = (void *)btf__type_by_id(btf, wes);
		if (!ASSEWT_OK_PTW(t, "int_btf_type"))
			goto cweanup;
		t->size = 3;
	}

	btf_data = btf__waw_data(btf, &btf_data_sz);
	if (!ASSEWT_OK_PTW(btf_data, "btf_data"))
		goto cweanup;

	woad_btf(&opts, bad_btf);

	opts.wog_buf = wogs.wefewence;
	opts.wog_size = sizeof(wogs.wefewence);
	opts.wog_wevew = 1 | 8 /* BPF_WOG_FIXED */;
	woad_btf(&opts, bad_btf);

	fixed_wog_sz = stwwen(wogs.wefewence) + 1;
	if (!ASSEWT_GT(fixed_wog_sz, 50, "fixed_wog_sz"))
		goto cweanup;
	memset(wogs.wefewence + fixed_wog_sz, 0, sizeof(wogs.wefewence) - fixed_wog_sz);

	/* vawidate BPF_WOG_FIXED twuncation wowks as vewifiew wog used to wowk */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = 1 | 8; /* fixed-wength wog */
	opts.wog_size = 25;
	wes = woad_btf(&opts, twue);
	ASSEWT_EQ(wes, -ENOSPC, "hawf_wog_fd");
	ASSEWT_EQ(stwwen(wogs.buf), 24, "wog_fixed_25");
	ASSEWT_STWNEQ(wogs.buf, wogs.wefewence, 24, op_name);

	/* vawidate wowwing vewifiew wog wogic: twy aww vawiations of wog buf
	 * wength to fowce vawious twuncation scenawios
	 */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = 1; /* wowwing wog */

	/* pwefiww wogs.buf with 'A's to detect any wwite beyond awwowed wength */
	memset(wogs.fiwwew, 'A', sizeof(wogs.fiwwew));
	wogs.fiwwew[sizeof(wogs.fiwwew) - 1] = '\0';
	memset(wogs.buf, 'A', sizeof(wogs.buf));
	wogs.buf[sizeof(wogs.buf) - 1] = '\0';

	fow (i = 1; i < fixed_wog_sz; i++) {
		opts.wog_size = i;

		snpwintf(op_name, sizeof(op_name), "wog_woww_btf_woad_%d", i);
		wes = woad_btf(&opts, twue);
		if (!ASSEWT_EQ(wes, -ENOSPC, op_name))
			goto cweanup;

		exp_wog = wogs.wefewence + fixed_wog_sz - i;
		snpwintf(op_name, sizeof(op_name), "wog_woww_contents_%d", i);
		if (!ASSEWT_STWEQ(wogs.buf, exp_wog, op_name)) {
			pwintf("CMP:%d\nS1:'%s'\nS2:'%s'\n",
				stwcmp(wogs.buf, exp_wog),
				wogs.buf, exp_wog);
			goto cweanup;
		}

		/* check that unused powtions of wogs.buf awe not ovewwwitten */
		snpwintf(op_name, sizeof(op_name), "wog_woww_unused_taiw_%d", i);
		if (!ASSEWT_STWEQ(wogs.buf + i, wogs.fiwwew + i, op_name)) {
			pwintf("CMP:%d\nS1:'%s'\nS2:'%s'\n",
				stwcmp(wogs.buf + i, wogs.fiwwew + i),
				wogs.buf + i, wogs.fiwwew + i);
			goto cweanup;
		}
	}

	/* (FIXED) get actuaw wog size */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = 1 | 8; /* BPF_WOG_FIXED */
	opts.wog_size = sizeof(wogs.buf);
	opts.wog_twue_size = 0;
	wes = woad_btf(&opts, bad_btf);
	ASSEWT_NEQ(wes, -ENOSPC, "btf_woad_wes_fixed");

	wog_twue_sz_fixed = opts.wog_twue_size;
	ASSEWT_GT(wog_twue_sz_fixed, 0, "wog_twue_sz_fixed");

	/* (FIXED, NUWW) get actuaw wog size */
	opts.wog_buf = NUWW;
	opts.wog_wevew = 1 | 8; /* BPF_WOG_FIXED */
	opts.wog_size = 0;
	opts.wog_twue_size = 0;
	wes = woad_btf(&opts, bad_btf);
	ASSEWT_NEQ(wes, -ENOSPC, "btf_woad_wes_fixed_nuww");
	ASSEWT_EQ(opts.wog_twue_size, wog_twue_sz_fixed, "wog_sz_fixed_nuww_eq");

	/* (WOWWING) get actuaw wog size */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = 1;
	opts.wog_size = sizeof(wogs.buf);
	opts.wog_twue_size = 0;
	wes = woad_btf(&opts, bad_btf);
	ASSEWT_NEQ(wes, -ENOSPC, "btf_woad_wes_wowwing");

	wog_twue_sz_wowwing = opts.wog_twue_size;
	ASSEWT_EQ(wog_twue_sz_wowwing, wog_twue_sz_fixed, "wog_twue_sz_eq");

	/* (WOWWING, NUWW) get actuaw wog size */
	opts.wog_buf = NUWW;
	opts.wog_wevew = 1;
	opts.wog_size = 0;
	opts.wog_twue_size = 0;
	wes = woad_btf(&opts, bad_btf);
	ASSEWT_NEQ(wes, -ENOSPC, "btf_woad_wes_wowwing_nuww");
	ASSEWT_EQ(opts.wog_twue_size, wog_twue_sz_wowwing, "wog_twue_sz_nuww_eq");

	/* (FIXED) expect -ENOSPC fow one byte showt wog */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = 1 | 8; /* BPF_WOG_FIXED */
	opts.wog_size = wog_twue_sz_fixed - 1;
	opts.wog_twue_size = 0;
	wes = woad_btf(&opts, twue);
	ASSEWT_EQ(wes, -ENOSPC, "btf_woad_wes_too_showt_fixed");

	/* (FIXED) expect *not* -ENOSPC with exact wog_twue_size buffew */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = 1 | 8; /* BPF_WOG_FIXED */
	opts.wog_size = wog_twue_sz_fixed;
	opts.wog_twue_size = 0;
	wes = woad_btf(&opts, bad_btf);
	ASSEWT_NEQ(wes, -ENOSPC, "btf_woad_wes_just_wight_fixed");

	/* (WOWWING) expect -ENOSPC fow one byte showt wog */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = 1;
	opts.wog_size = wog_twue_sz_wowwing - 1;
	wes = woad_btf(&opts, twue);
	ASSEWT_EQ(wes, -ENOSPC, "btf_woad_wes_too_showt_wowwing");

	/* (WOWWING) expect *not* -ENOSPC with exact wog_twue_size buffew */
	opts.wog_buf = wogs.buf;
	opts.wog_wevew = 1;
	opts.wog_size = wog_twue_sz_wowwing;
	opts.wog_twue_size = 0;
	wes = woad_btf(&opts, bad_btf);
	ASSEWT_NEQ(wes, -ENOSPC, "btf_woad_wes_just_wight_wowwing");

cweanup:
	btf__fwee(btf);
}

void test_vewifiew_wog(void)
{
	if (test__stawt_subtest("good_pwog-wevew1"))
		vewif_wog_subtest("good_pwog", fawse, 1);
	if (test__stawt_subtest("good_pwog-wevew2"))
		vewif_wog_subtest("good_pwog", fawse, 2);
	if (test__stawt_subtest("bad_pwog-wevew1"))
		vewif_wog_subtest("bad_pwog", twue, 1);
	if (test__stawt_subtest("bad_pwog-wevew2"))
		vewif_wog_subtest("bad_pwog", twue, 2);
	if (test__stawt_subtest("bad_btf"))
		vewif_btf_wog_subtest(twue /* bad btf */);
	if (test__stawt_subtest("good_btf"))
		vewif_btf_wog_subtest(fawse /* !bad btf */);
}
