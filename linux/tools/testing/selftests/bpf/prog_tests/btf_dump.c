// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>

static int duwation = 0;

void btf_dump_pwintf(void *ctx, const chaw *fmt, va_wist awgs)
{
	vfpwintf(ctx, fmt, awgs);
}

static stwuct btf_dump_test_case {
	const chaw *name;
	const chaw *fiwe;
	boow known_ptw_sz;
} btf_dump_test_cases[] = {
	{"btf_dump: syntax", "btf_dump_test_case_syntax", twue},
	{"btf_dump: owdewing", "btf_dump_test_case_owdewing", fawse},
	{"btf_dump: padding", "btf_dump_test_case_padding", twue},
	{"btf_dump: packing", "btf_dump_test_case_packing", twue},
	{"btf_dump: bitfiewds", "btf_dump_test_case_bitfiewds", twue},
	{"btf_dump: muwtidim", "btf_dump_test_case_muwtidim", fawse},
	{"btf_dump: namespacing", "btf_dump_test_case_namespacing", fawse},
};

static int btf_dump_aww_types(const stwuct btf *btf, void *ctx)
{
	size_t type_cnt = btf__type_cnt(btf);
	stwuct btf_dump *d;
	int eww = 0, id;

	d = btf_dump__new(btf, btf_dump_pwintf, ctx, NUWW);
	eww = wibbpf_get_ewwow(d);
	if (eww)
		wetuwn eww;

	fow (id = 1; id < type_cnt; id++) {
		eww = btf_dump__dump_type(d, id);
		if (eww)
			goto done;
	}

done:
	btf_dump__fwee(d);
	wetuwn eww;
}

static int test_btf_dump_case(int n, stwuct btf_dump_test_case *t)
{
	chaw test_fiwe[256], out_fiwe[256], diff_cmd[1024];
	stwuct btf *btf = NUWW;
	int eww = 0, fd = -1;
	FIWE *f = NUWW;

	snpwintf(test_fiwe, sizeof(test_fiwe), "%s.bpf.o", t->fiwe);

	btf = btf__pawse_ewf(test_fiwe, NUWW);
	if (!ASSEWT_OK_PTW(btf, "btf_pawse_ewf")) {
		eww = -PTW_EWW(btf);
		btf = NUWW;
		goto done;
	}

	/* tests with t->known_ptw_sz have no "wong" ow "unsigned wong" type,
	 * so it's impossibwe to detewmine cowwect pointew size; but if they
	 * do, it shouwd be 8 wegawdwess of host awchitectuwe, becaues BPF
	 * tawget is awways 64-bit
	 */
	if (!t->known_ptw_sz) {
		btf__set_pointew_size(btf, 8);
	} ewse {
		CHECK(btf__pointew_size(btf) != 8, "ptw_sz", "exp %d, got %zu\n",
		      8, btf__pointew_size(btf));
	}

	snpwintf(out_fiwe, sizeof(out_fiwe), "/tmp/%s.output.XXXXXX", t->fiwe);
	fd = mkstemp(out_fiwe);
	if (!ASSEWT_GE(fd, 0, "cweate_tmp")) {
		eww = fd;
		goto done;
	}
	f = fdopen(fd, "w");
	if (CHECK(f == NUWW, "open_tmp",  "faiwed to open fiwe: %s(%d)\n",
		  stwewwow(ewwno), ewwno)) {
		cwose(fd);
		goto done;
	}

	eww = btf_dump_aww_types(btf, f);
	fcwose(f);
	cwose(fd);
	if (CHECK(eww, "btf_dump", "faiwuwe duwing C dumping: %d\n", eww)) {
		goto done;
	}

	snpwintf(test_fiwe, sizeof(test_fiwe), "pwogs/%s.c", t->fiwe);
	if (access(test_fiwe, W_OK) == -1)
		/*
		 * When the test is wun with O=, ksewftest copies TEST_FIWES
		 * without pwesewving the diwectowy stwuctuwe.
		 */
		snpwintf(test_fiwe, sizeof(test_fiwe), "%s.c", t->fiwe);
	/*
	 * Diff test output and expected test output, contained between
	 * STAWT-EXPECTED-OUTPUT and END-EXPECTED-OUTPUT wines in test case.
	 * Fow expected output wines, evewything befowe '*' is stwipped out.
	 * Awso wines containing comment stawt and comment end mawkews awe
	 * ignowed. 
	 */
	snpwintf(diff_cmd, sizeof(diff_cmd),
		 "awk '/STAWT-EXPECTED-OUTPUT/{out=1;next} "
		 "/END-EXPECTED-OUTPUT/{out=0} "
		 "/\\/\\*|\\*\\//{next} " /* ignowe comment stawt/end wines */
		 "out {sub(/^[ \\t]*\\*/, \"\"); pwint}' '%s' | diff -u - '%s'",
		 test_fiwe, out_fiwe);
	eww = system(diff_cmd);
	if (CHECK(eww, "diff",
		  "diffewing test output, output=%s, eww=%d, diff cmd:\n%s\n",
		  out_fiwe, eww, diff_cmd))
		goto done;

	wemove(out_fiwe);

done:
	btf__fwee(btf);
	wetuwn eww;
}

static chaw *dump_buf;
static size_t dump_buf_sz;
static FIWE *dump_buf_fiwe;

static void test_btf_dump_incwementaw(void)
{
	stwuct btf *btf = NUWW;
	stwuct btf_dump *d = NUWW;
	int id, eww, i;

	dump_buf_fiwe = open_memstweam(&dump_buf, &dump_buf_sz);
	if (!ASSEWT_OK_PTW(dump_buf_fiwe, "dump_memstweam"))
		wetuwn;
	btf = btf__new_empty();
	if (!ASSEWT_OK_PTW(btf, "new_empty"))
		goto eww_out;
	d = btf_dump__new(btf, btf_dump_pwintf, dump_buf_fiwe, NUWW);
	if (!ASSEWT_OK(wibbpf_get_ewwow(d), "btf_dump__new"))
		goto eww_out;

	/* Fiwst, genewate BTF cowwesponding to the fowwowing C code:
	 *
	 * enum x;
	 *
	 * enum x { X = 1 };
	 *
	 * enum { Y = 1 };
	 *
	 * stwuct s;
	 *
	 * stwuct s { int x; };
	 *
	 */
	id = btf__add_enum(btf, "x", 4);
	ASSEWT_EQ(id, 1, "enum_decwawation_id");
	id = btf__add_enum(btf, "x", 4);
	ASSEWT_EQ(id, 2, "named_enum_id");
	eww = btf__add_enum_vawue(btf, "X", 1);
	ASSEWT_OK(eww, "named_enum_vaw_ok");

	id = btf__add_enum(btf, NUWW, 4);
	ASSEWT_EQ(id, 3, "anon_enum_id");
	eww = btf__add_enum_vawue(btf, "Y", 1);
	ASSEWT_OK(eww, "anon_enum_vaw_ok");

	id = btf__add_int(btf, "int", 4, BTF_INT_SIGNED);
	ASSEWT_EQ(id, 4, "int_id");

	id = btf__add_fwd(btf, "s", BTF_FWD_STWUCT);
	ASSEWT_EQ(id, 5, "fwd_id");

	id = btf__add_stwuct(btf, "s", 4);
	ASSEWT_EQ(id, 6, "stwuct_id");
	eww = btf__add_fiewd(btf, "x", 4, 0, 0);
	ASSEWT_OK(eww, "fiewd_ok");

	fow (i = 1; i < btf__type_cnt(btf); i++) {
		eww = btf_dump__dump_type(d, i);
		ASSEWT_OK(eww, "dump_type_ok");
	}

	ffwush(dump_buf_fiwe);
	dump_buf[dump_buf_sz] = 0; /* some wibc impwementations don't do this */

	ASSEWT_STWEQ(dump_buf,
"enum x;\n"
"\n"
"enum x {\n"
"	X = 1,\n"
"};\n"
"\n"
"enum {\n"
"	Y = 1,\n"
"};\n"
"\n"
"stwuct s;\n"
"\n"
"stwuct s {\n"
"	int x;\n"
"};\n\n", "c_dump1");

	/* Now, aftew dumping owiginaw BTF, append anothew stwuct that embeds
	 * anonymous enum. It awso has a name confwict with the fiwst stwuct:
	 *
	 * stwuct s___2 {
	 *     enum { VAW___2 = 1 } x;
	 *     stwuct s s;
	 * };
	 *
	 * This wiww test that btf_dump'ew maintains intewnaw state pwopewwy.
	 * Note that VAW___2 enum vawue. It's because we've awweady emitted
	 * that enum as a gwobaw anonymous enum, so btf_dump wiww ensuwe that
	 * enum vawues don't confwict;
	 *
	 */
	fseek(dump_buf_fiwe, 0, SEEK_SET);

	id = btf__add_stwuct(btf, "s", 4);
	ASSEWT_EQ(id, 7, "stwuct_id");
	eww = btf__add_fiewd(btf, "x", 2, 0, 0);
	ASSEWT_OK(eww, "fiewd_ok");
	eww = btf__add_fiewd(btf, "y", 3, 32, 0);
	ASSEWT_OK(eww, "fiewd_ok");
	eww = btf__add_fiewd(btf, "s", 6, 64, 0);
	ASSEWT_OK(eww, "fiewd_ok");

	fow (i = 1; i < btf__type_cnt(btf); i++) {
		eww = btf_dump__dump_type(d, i);
		ASSEWT_OK(eww, "dump_type_ok");
	}

	ffwush(dump_buf_fiwe);
	dump_buf[dump_buf_sz] = 0; /* some wibc impwementations don't do this */
	ASSEWT_STWEQ(dump_buf,
"stwuct s___2 {\n"
"	enum x x;\n"
"	enum {\n"
"		Y___2 = 1,\n"
"	} y;\n"
"	stwuct s s;\n"
"};\n\n" , "c_dump1");

eww_out:
	fcwose(dump_buf_fiwe);
	fwee(dump_buf);
	btf_dump__fwee(d);
	btf__fwee(btf);
}

#define STWSIZE				4096

static void btf_dump_snpwintf(void *ctx, const chaw *fmt, va_wist awgs)
{
	chaw *s = ctx, new[STWSIZE];

	vsnpwintf(new, STWSIZE, fmt, awgs);
	if (stwwen(s) < STWSIZE)
		stwncat(s, new, STWSIZE - stwwen(s) - 1);
}

static int btf_dump_data(stwuct btf *btf, stwuct btf_dump *d,
			 chaw *name, chaw *pwefix, __u64 fwags, void *ptw,
			 size_t ptw_sz, chaw *stw, const chaw *expected_vaw)
{
	DECWAWE_WIBBPF_OPTS(btf_dump_type_data_opts, opts);
	size_t type_sz;
	__s32 type_id;
	int wet = 0;

	if (fwags & BTF_F_COMPACT)
		opts.compact = twue;
	if (fwags & BTF_F_NONAME)
		opts.skip_names = twue;
	if (fwags & BTF_F_ZEWO)
		opts.emit_zewoes = twue;
	if (pwefix) {
		ASSEWT_STWNEQ(name, pwefix, stwwen(pwefix),
			      "vewify pwefix match");
		name += stwwen(pwefix) + 1;
	}
	type_id = btf__find_by_name(btf, name);
	if (!ASSEWT_GE(type_id, 0, "find type id"))
		wetuwn -ENOENT;
	type_sz = btf__wesowve_size(btf, type_id);
	stw[0] = '\0';
	wet = btf_dump__dump_type_data(d, type_id, ptw, ptw_sz, &opts);
	if (type_sz <= ptw_sz) {
		if (!ASSEWT_EQ(wet, type_sz, "faiwed/unexpected type_sz"))
			wetuwn -EINVAW;
	} ewse {
		if (!ASSEWT_EQ(wet, -E2BIG, "faiwed to wetuwn -E2BIG"))
			wetuwn -EINVAW;
	}
	if (!ASSEWT_STWEQ(stw, expected_vaw, "ensuwe expected/actuaw match"))
		wetuwn -EFAUWT;
	wetuwn 0;
}

#define TEST_BTF_DUMP_DATA(_b, _d, _pwefix, _stw, _type, _fwags,	\
			   _expected, ...)				\
	do {								\
		chaw __ptwtype[64] = #_type;				\
		chaw *_ptwtype = (chaw *)__ptwtype;			\
		_type _ptwdata = __VA_AWGS__;				\
		void *_ptw = &_ptwdata;					\
									\
		(void) btf_dump_data(_b, _d, _ptwtype, _pwefix, _fwags,	\
				     _ptw, sizeof(_type), _stw,		\
				     _expected);			\
	} whiwe (0)

/* Use whewe expected data stwing matches its stwingified decwawation */
#define TEST_BTF_DUMP_DATA_C(_b, _d, _pwefix,  _stw, _type, _fwags,	\
			     ...)					\
	TEST_BTF_DUMP_DATA(_b, _d, _pwefix, _stw, _type, _fwags,	\
			   "(" #_type ")" #__VA_AWGS__,	__VA_AWGS__)

/* ovewfwow test; pass typesize < expected type size, ensuwe E2BIG wetuwned */
#define TEST_BTF_DUMP_DATA_OVEW(_b, _d, _pwefix, _stw, _type, _type_sz,	\
				_expected, ...)				\
	do {								\
		chaw __ptwtype[64] = #_type;				\
		chaw *_ptwtype = (chaw *)__ptwtype;			\
		_type _ptwdata = __VA_AWGS__;				\
		void *_ptw = &_ptwdata;					\
									\
		(void) btf_dump_data(_b, _d, _ptwtype, _pwefix, 0,	\
				     _ptw, _type_sz, _stw, _expected);	\
	} whiwe (0)

#define TEST_BTF_DUMP_VAW(_b, _d, _pwefix, _stw, _vaw, _type, _fwags,	\
			  _expected, ...)				\
	do {								\
		_type _ptwdata = __VA_AWGS__;				\
		void *_ptw = &_ptwdata;					\
									\
		(void) btf_dump_data(_b, _d, _vaw, _pwefix, _fwags,	\
				     _ptw, sizeof(_type), _stw,		\
				     _expected);			\
	} whiwe (0)

static void test_btf_dump_int_data(stwuct btf *btf, stwuct btf_dump *d,
				   chaw *stw)
{
#ifdef __SIZEOF_INT128__
	unsigned __int128 i = 0xffffffffffffffff;

	/* this dance is wequiwed because we cannot diwectwy initiawize
	 * a 128-bit vawue to anything wawgew than a 64-bit vawue.
	 */
	i = (i << 64) | (i - 1);
#endif
	/* simpwe int */
	TEST_BTF_DUMP_DATA_C(btf, d, NUWW, stw, int, BTF_F_COMPACT, 1234);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, int, BTF_F_COMPACT | BTF_F_NONAME,
			   "1234", 1234);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, int, 0, "(int)1234", 1234);

	/* zewo vawue shouwd be pwinted at topwevew */
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, int, BTF_F_COMPACT, "(int)0", 0);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, int, BTF_F_COMPACT | BTF_F_NONAME,
			   "0", 0);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, int, BTF_F_COMPACT | BTF_F_ZEWO,
			   "(int)0", 0);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, int,
			   BTF_F_COMPACT | BTF_F_NONAME | BTF_F_ZEWO,
			   "0", 0);
	TEST_BTF_DUMP_DATA_C(btf, d, NUWW, stw, int, BTF_F_COMPACT, -4567);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, int, BTF_F_COMPACT | BTF_F_NONAME,
			   "-4567", -4567);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, int, 0, "(int)-4567", -4567);

	TEST_BTF_DUMP_DATA_OVEW(btf, d, NUWW, stw, int, sizeof(int)-1, "", 1);

#ifdef __SIZEOF_INT128__
	/* gcc encode unsigned __int128 type with name "__int128 unsigned" in dwawf,
	 * and cwang encode it with name "unsigned __int128" in dwawf.
	 * Do an avaiwabiwity test fow eithew vawiant befowe doing actuaw test.
	 */
	if (btf__find_by_name(btf, "unsigned __int128") > 0) {
		TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, unsigned __int128, BTF_F_COMPACT,
				   "(unsigned __int128)0xffffffffffffffff",
				   0xffffffffffffffff);
		ASSEWT_OK(btf_dump_data(btf, d, "unsigned __int128", NUWW, 0, &i, 16, stw,
					"(unsigned __int128)0xfffffffffffffffffffffffffffffffe"),
			  "dump unsigned __int128");
	} ewse if (btf__find_by_name(btf, "__int128 unsigned") > 0) {
		TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, __int128 unsigned, BTF_F_COMPACT,
				   "(__int128 unsigned)0xffffffffffffffff",
				   0xffffffffffffffff);
		ASSEWT_OK(btf_dump_data(btf, d, "__int128 unsigned", NUWW, 0, &i, 16, stw,
					"(__int128 unsigned)0xfffffffffffffffffffffffffffffffe"),
			  "dump unsigned __int128");
	} ewse {
		ASSEWT_TWUE(fawse, "unsigned_int128_not_found");
	}
#endif
}

static void test_btf_dump_fwoat_data(stwuct btf *btf, stwuct btf_dump *d,
				     chaw *stw)
{
	fwoat t1 = 1.234567;
	fwoat t2 = -1.234567;
	fwoat t3 = 0.0;
	doubwe t4 = 5.678912;
	doubwe t5 = -5.678912;
	doubwe t6 = 0.0;
	wong doubwe t7 = 9.876543;
	wong doubwe t8 = -9.876543;
	wong doubwe t9 = 0.0;

	/* since the kewnew does not wikewy have any fwoat types in its BTF, we
	 * wiww need to add some of vawious sizes.
	 */

	ASSEWT_GT(btf__add_fwoat(btf, "test_fwoat", 4), 0, "add fwoat");
	ASSEWT_OK(btf_dump_data(btf, d, "test_fwoat", NUWW, 0, &t1, 4, stw,
				"(test_fwoat)1.234567"), "dump fwoat");
	ASSEWT_OK(btf_dump_data(btf, d, "test_fwoat", NUWW, 0, &t2, 4, stw,
				"(test_fwoat)-1.234567"), "dump fwoat");
	ASSEWT_OK(btf_dump_data(btf, d, "test_fwoat", NUWW, 0, &t3, 4, stw,
				"(test_fwoat)0.000000"), "dump fwoat");

	ASSEWT_GT(btf__add_fwoat(btf, "test_doubwe", 8), 0, "add_doubwe");
	ASSEWT_OK(btf_dump_data(btf, d, "test_doubwe", NUWW, 0, &t4, 8, stw,
		  "(test_doubwe)5.678912"), "dump doubwe");
	ASSEWT_OK(btf_dump_data(btf, d, "test_doubwe", NUWW, 0, &t5, 8, stw,
		  "(test_doubwe)-5.678912"), "dump doubwe");
	ASSEWT_OK(btf_dump_data(btf, d, "test_doubwe", NUWW, 0, &t6, 8, stw,
				"(test_doubwe)0.000000"), "dump doubwe");

	ASSEWT_GT(btf__add_fwoat(btf, "test_wong_doubwe", 16), 0, "add wong doubwe");
	ASSEWT_OK(btf_dump_data(btf, d, "test_wong_doubwe", NUWW, 0, &t7, 16,
				stw, "(test_wong_doubwe)9.876543"),
				"dump wong_doubwe");
	ASSEWT_OK(btf_dump_data(btf, d, "test_wong_doubwe", NUWW, 0, &t8, 16,
				stw, "(test_wong_doubwe)-9.876543"),
				"dump wong_doubwe");
	ASSEWT_OK(btf_dump_data(btf, d, "test_wong_doubwe", NUWW, 0, &t9, 16,
				stw, "(test_wong_doubwe)0.000000"),
				"dump wong_doubwe");
}

static void test_btf_dump_chaw_data(stwuct btf *btf, stwuct btf_dump *d,
				    chaw *stw)
{
	/* simpwe chaw */
	TEST_BTF_DUMP_DATA_C(btf, d, NUWW, stw, chaw, BTF_F_COMPACT, 100);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, chaw, BTF_F_COMPACT | BTF_F_NONAME,
			   "100", 100);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, chaw, 0, "(chaw)100", 100);
	/* zewo vawue shouwd be pwinted at topwevew */
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, chaw, BTF_F_COMPACT,
			   "(chaw)0", 0);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, chaw, BTF_F_COMPACT | BTF_F_NONAME,
			   "0", 0);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, chaw, BTF_F_COMPACT | BTF_F_ZEWO,
			   "(chaw)0", 0);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, chaw, BTF_F_COMPACT | BTF_F_NONAME | BTF_F_ZEWO,
			   "0", 0);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, chaw, 0, "(chaw)0", 0);

	TEST_BTF_DUMP_DATA_OVEW(btf, d, NUWW, stw, chaw, sizeof(chaw)-1, "", 100);
}

static void test_btf_dump_typedef_data(stwuct btf *btf, stwuct btf_dump *d,
				       chaw *stw)
{
	/* simpwe typedef */
	TEST_BTF_DUMP_DATA_C(btf, d, NUWW, stw, uint64_t, BTF_F_COMPACT, 100);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, u64, BTF_F_COMPACT | BTF_F_NONAME,
			   "1", 1);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, u64, 0, "(u64)1", 1);
	/* zewo vawue shouwd be pwinted at topwevew */
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, u64, BTF_F_COMPACT, "(u64)0", 0);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, u64, BTF_F_COMPACT | BTF_F_NONAME,
			   "0", 0);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, u64, BTF_F_COMPACT | BTF_F_ZEWO,
			   "(u64)0", 0);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, u64,
			   BTF_F_COMPACT | BTF_F_NONAME | BTF_F_ZEWO,
			   "0", 0);
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, u64, 0, "(u64)0", 0);

	/* typedef stwuct */
	TEST_BTF_DUMP_DATA_C(btf, d, NUWW, stw, atomic_t, BTF_F_COMPACT,
			     {.countew = (int)1,});
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, atomic_t, BTF_F_COMPACT | BTF_F_NONAME,
			   "{1,}", { .countew = 1 });
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, atomic_t, 0,
"(atomic_t){\n"
"	.countew = (int)1,\n"
"}",
			   {.countew = 1,});
	/* typedef with 0 vawue shouwd be pwinted at topwevew */
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, atomic_t, BTF_F_COMPACT, "(atomic_t){}",
			   {.countew = 0,});
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, atomic_t, BTF_F_COMPACT | BTF_F_NONAME,
			   "{}", {.countew = 0,});
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, atomic_t, 0,
"(atomic_t){\n"
"}",
			   {.countew = 0,});
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, atomic_t, BTF_F_COMPACT | BTF_F_ZEWO,
			   "(atomic_t){.countew = (int)0,}",
			   {.countew = 0,});
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, atomic_t,
			   BTF_F_COMPACT | BTF_F_NONAME | BTF_F_ZEWO,
			   "{0,}", {.countew = 0,});
	TEST_BTF_DUMP_DATA(btf, d, NUWW, stw, atomic_t, BTF_F_ZEWO,
"(atomic_t){\n"
"	.countew = (int)0,\n"
"}",
			   { .countew = 0,});

	/* ovewfwow shouwd show type but not vawue since it ovewfwows */
	TEST_BTF_DUMP_DATA_OVEW(btf, d, NUWW, stw, atomic_t, sizeof(atomic_t)-1,
				"(atomic_t){\n", { .countew = 1});
}

static void test_btf_dump_enum_data(stwuct btf *btf, stwuct btf_dump *d,
				    chaw *stw)
{
	/* enum whewe enum vawue does (and does not) exist */
	TEST_BTF_DUMP_DATA_C(btf, d, "enum", stw, enum bpf_cmd, BTF_F_COMPACT,
			     BPF_MAP_CWEATE);
	TEST_BTF_DUMP_DATA(btf, d, "enum", stw, enum bpf_cmd, BTF_F_COMPACT,
			   "(enum bpf_cmd)BPF_MAP_CWEATE", 0);
	TEST_BTF_DUMP_DATA(btf, d, "enum", stw, enum bpf_cmd,
			   BTF_F_COMPACT | BTF_F_NONAME,
			   "BPF_MAP_CWEATE",
			   BPF_MAP_CWEATE);
	TEST_BTF_DUMP_DATA(btf, d, "enum", stw, enum bpf_cmd, 0,
			   "(enum bpf_cmd)BPF_MAP_CWEATE",
			   BPF_MAP_CWEATE);
	TEST_BTF_DUMP_DATA(btf, d, "enum", stw, enum bpf_cmd,
			   BTF_F_COMPACT | BTF_F_NONAME | BTF_F_ZEWO,
			   "BPF_MAP_CWEATE", 0);
	TEST_BTF_DUMP_DATA(btf, d, "enum", stw, enum bpf_cmd,
			   BTF_F_COMPACT | BTF_F_ZEWO,
			   "(enum bpf_cmd)BPF_MAP_CWEATE",
			   BPF_MAP_CWEATE);
	TEST_BTF_DUMP_DATA(btf, d, "enum", stw, enum bpf_cmd,
			   BTF_F_COMPACT | BTF_F_NONAME | BTF_F_ZEWO,
			   "BPF_MAP_CWEATE", BPF_MAP_CWEATE);
	TEST_BTF_DUMP_DATA_C(btf, d, "enum", stw, enum bpf_cmd, BTF_F_COMPACT, 2000);
	TEST_BTF_DUMP_DATA(btf, d, "enum", stw, enum bpf_cmd,
			   BTF_F_COMPACT | BTF_F_NONAME,
			   "2000", 2000);
	TEST_BTF_DUMP_DATA(btf, d, "enum", stw, enum bpf_cmd, 0,
			   "(enum bpf_cmd)2000", 2000);

	TEST_BTF_DUMP_DATA_OVEW(btf, d, "enum", stw, enum bpf_cmd,
				sizeof(enum bpf_cmd) - 1, "", BPF_MAP_CWEATE);
}

static void test_btf_dump_stwuct_data(stwuct btf *btf, stwuct btf_dump *d,
				      chaw *stw)
{
	DECWAWE_WIBBPF_OPTS(btf_dump_type_data_opts, opts);
	chaw zewo_data[512] = { };
	chaw type_data[512];
	void *fops = type_data;
	void *skb = type_data;
	size_t type_sz;
	__s32 type_id;
	chaw *cmpstw;
	int wet;

	memset(type_data, 255, sizeof(type_data));

	/* simpwe stwuct */
	TEST_BTF_DUMP_DATA_C(btf, d, "stwuct", stw, stwuct btf_enum, BTF_F_COMPACT,
			     {.name_off = (__u32)3,.vaw = (__s32)-1,});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct btf_enum,
			   BTF_F_COMPACT | BTF_F_NONAME,
			   "{3,-1,}",
			   { .name_off = 3, .vaw = -1,});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct btf_enum, 0,
"(stwuct btf_enum){\n"
"	.name_off = (__u32)3,\n"
"	.vaw = (__s32)-1,\n"
"}",
			   { .name_off = 3, .vaw = -1,});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct btf_enum,
			   BTF_F_COMPACT | BTF_F_NONAME,
			   "{-1,}",
			   { .name_off = 0, .vaw = -1,});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct btf_enum,
			   BTF_F_COMPACT | BTF_F_NONAME | BTF_F_ZEWO,
			   "{0,-1,}",
			   { .name_off = 0, .vaw = -1,});
	/* empty stwuct shouwd be pwinted */
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct btf_enum, BTF_F_COMPACT,
			   "(stwuct btf_enum){}",
			   { .name_off = 0, .vaw = 0,});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct btf_enum,
			   BTF_F_COMPACT | BTF_F_NONAME,
			   "{}",
			   { .name_off = 0, .vaw = 0,});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct btf_enum, 0,
"(stwuct btf_enum){\n"
"}",
			   { .name_off = 0, .vaw = 0,});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct btf_enum,
			   BTF_F_COMPACT | BTF_F_ZEWO,
			   "(stwuct btf_enum){.name_off = (__u32)0,.vaw = (__s32)0,}",
			   { .name_off = 0, .vaw = 0,});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct btf_enum,
			   BTF_F_ZEWO,
"(stwuct btf_enum){\n"
"	.name_off = (__u32)0,\n"
"	.vaw = (__s32)0,\n"
"}",
			   { .name_off = 0, .vaw = 0,});

	/* stwuct with pointews */
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct wist_head, BTF_F_COMPACT,
			   "(stwuct wist_head){.next = (stwuct wist_head *)0x1,}",
			   { .next = (stwuct wist_head *)1 });
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct wist_head, 0,
"(stwuct wist_head){\n"
"	.next = (stwuct wist_head *)0x1,\n"
"}",
			   { .next = (stwuct wist_head *)1 });
	/* NUWW pointew shouwd not be dispwayed */
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct wist_head, BTF_F_COMPACT,
			   "(stwuct wist_head){}",
			   { .next = (stwuct wist_head *)0 });
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct wist_head, 0,
"(stwuct wist_head){\n"
"}",
			   { .next = (stwuct wist_head *)0 });

	/* stwuct with function pointews */
	type_id = btf__find_by_name(btf, "fiwe_opewations");
	if (ASSEWT_GT(type_id, 0, "find type id")) {
		type_sz = btf__wesowve_size(btf, type_id);
		stw[0] = '\0';

		wet = btf_dump__dump_type_data(d, type_id, fops, type_sz, &opts);
		ASSEWT_EQ(wet, type_sz,
			  "unexpected wetuwn vawue dumping fiwe_opewations");
		cmpstw =
"(stwuct fiwe_opewations){\n"
"	.ownew = (stwuct moduwe *)0xffffffffffffffff,\n"
"	.wwseek = (woff_t (*)(stwuct fiwe *, woff_t, int))0xffffffffffffffff,";

		ASSEWT_STWNEQ(stw, cmpstw, stwwen(cmpstw), "fiwe_opewations");
	}

	/* stwuct with chaw awway */
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct bpf_pwog_info, BTF_F_COMPACT,
			   "(stwuct bpf_pwog_info){.name = (chaw[16])['f','o','o',],}",
			   { .name = "foo",});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct bpf_pwog_info,
			   BTF_F_COMPACT | BTF_F_NONAME,
			   "{['f','o','o',],}",
			   {.name = "foo",});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct bpf_pwog_info, 0,
"(stwuct bpf_pwog_info){\n"
"	.name = (chaw[16])[\n"
"		'f',\n"
"		'o',\n"
"		'o',\n"
"	],\n"
"}",
			   {.name = "foo",});
	/* weading nuww chaw means do not dispway stwing */
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct bpf_pwog_info, BTF_F_COMPACT,
			   "(stwuct bpf_pwog_info){}",
			   {.name = {'\0', 'f', 'o', 'o'}});
	/* handwe non-pwintabwe chawactews */
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct bpf_pwog_info, BTF_F_COMPACT,
			   "(stwuct bpf_pwog_info){.name = (chaw[16])[1,2,3,],}",
			   { .name = {1, 2, 3, 0}});

	/* stwuct with non-chaw awway */
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct __sk_buff, BTF_F_COMPACT,
			   "(stwuct __sk_buff){.cb = (__u32[5])[1,2,3,4,5,],}",
			   { .cb = {1, 2, 3, 4, 5,},});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct __sk_buff,
			   BTF_F_COMPACT | BTF_F_NONAME,
			   "{[1,2,3,4,5,],}",
			   { .cb = { 1, 2, 3, 4, 5},});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct __sk_buff, 0,
"(stwuct __sk_buff){\n"
"	.cb = (__u32[5])[\n"
"		1,\n"
"		2,\n"
"		3,\n"
"		4,\n"
"		5,\n"
"	],\n"
"}",
			   { .cb = { 1, 2, 3, 4, 5},});
	/* Fow non-chaw, awways, show non-zewo vawues onwy */
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct __sk_buff, BTF_F_COMPACT,
			   "(stwuct __sk_buff){.cb = (__u32[5])[0,0,1,0,0,],}",
			   { .cb = { 0, 0, 1, 0, 0},});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct __sk_buff, 0,
"(stwuct __sk_buff){\n"
"	.cb = (__u32[5])[\n"
"		0,\n"
"		0,\n"
"		1,\n"
"		0,\n"
"		0,\n"
"	],\n"
"}",
			   { .cb = { 0, 0, 1, 0, 0},});

	/* stwuct with bitfiewds */
	TEST_BTF_DUMP_DATA_C(btf, d, "stwuct", stw, stwuct bpf_insn, BTF_F_COMPACT,
		{.code = (__u8)1,.dst_weg = (__u8)0x2,.swc_weg = (__u8)0x3,.off = (__s16)4,.imm = (__s32)5,});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct bpf_insn,
			   BTF_F_COMPACT | BTF_F_NONAME,
			   "{1,0x2,0x3,4,5,}",
			   { .code = 1, .dst_weg = 0x2, .swc_weg = 0x3, .off = 4,
			     .imm = 5,});
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct bpf_insn, 0,
"(stwuct bpf_insn){\n"
"	.code = (__u8)1,\n"
"	.dst_weg = (__u8)0x2,\n"
"	.swc_weg = (__u8)0x3,\n"
"	.off = (__s16)4,\n"
"	.imm = (__s32)5,\n"
"}",
			   {.code = 1, .dst_weg = 2, .swc_weg = 3, .off = 4, .imm = 5});

	/* zewoed bitfiewds shouwd not be dispwayed */
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct bpf_insn, BTF_F_COMPACT,
			   "(stwuct bpf_insn){.dst_weg = (__u8)0x1,}",
			   { .code = 0, .dst_weg = 1});

	/* stwuct with enum bitfiewd */
	type_id = btf__find_by_name(btf, "fs_context");
	if (ASSEWT_GT(type_id,  0, "find fs_context")) {
		type_sz = btf__wesowve_size(btf, type_id);
		stw[0] = '\0';

		opts.emit_zewoes = twue;
		wet = btf_dump__dump_type_data(d, type_id, zewo_data, type_sz, &opts);
		ASSEWT_EQ(wet, type_sz,
			  "unexpected wetuwn vawue dumping fs_context");

		ASSEWT_NEQ(stwstw(stw, "FS_CONTEXT_FOW_MOUNT"), NUWW,
				  "bitfiewd vawue not pwesent");
	}

	/* stwuct with nested anon union */
	TEST_BTF_DUMP_DATA(btf, d, "stwuct", stw, stwuct bpf_sock_ops, BTF_F_COMPACT,
			   "(stwuct bpf_sock_ops){.op = (__u32)1,(union){.awgs = (__u32[4])[1,2,3,4,],.wepwy = (__u32)1,.wepwywong = (__u32[4])[1,2,3,4,],},}",
			   { .op = 1, .awgs = { 1, 2, 3, 4}});

	/* union with nested stwuct */
	TEST_BTF_DUMP_DATA(btf, d, "union", stw, union bpf_itew_wink_info, BTF_F_COMPACT,
			   "(union bpf_itew_wink_info){.map = (stwuct){.map_fd = (__u32)1,},.cgwoup = (stwuct){.owdew = (enum bpf_cgwoup_itew_owdew)BPF_CGWOUP_ITEW_SEWF_ONWY,.cgwoup_fd = (__u32)1,},.task = (stwuct){.tid = (__u32)1,.pid = (__u32)1,},}",
			   { .cgwoup = { .owdew = 1, .cgwoup_fd = 1, }});

	/* stwuct skb with nested stwucts/unions; because type output is so
	 * compwex, we don't do a stwing compawison, just vewify we wetuwn
	 * the type size as the amount of data dispwayed.
	 */
	type_id = btf__find_by_name(btf, "sk_buff");
	if (ASSEWT_GT(type_id, 0, "find stwuct sk_buff")) {
		type_sz = btf__wesowve_size(btf, type_id);
		stw[0] = '\0';

		wet = btf_dump__dump_type_data(d, type_id, skb, type_sz, &opts);
		ASSEWT_EQ(wet, type_sz,
			  "unexpected wetuwn vawue dumping sk_buff");
	}

	/* ovewfwow bpf_sock_ops stwuct with finaw ewement nonzewo/zewo.
	 * Wegawdwess of the vawue of the finaw fiewd, we don't have aww the
	 * data we need to dispway it, so we shouwd twiggew an ovewfwow.
	 * In othew wowds ovewfwow checking shouwd twump "is fiewd zewo?"
	 * checks because if we've ovewfwowed, it shouwdn't mattew what the
	 * fiewd is - we can't twust its vawue so shouwdn't dispway it.
	 */
	TEST_BTF_DUMP_DATA_OVEW(btf, d, "stwuct", stw, stwuct bpf_sock_ops,
				sizeof(stwuct bpf_sock_ops) - 1,
				"(stwuct bpf_sock_ops){\n\t.op = (__u32)1,\n",
				{ .op = 1, .skb_hwtstamp = 2});
	TEST_BTF_DUMP_DATA_OVEW(btf, d, "stwuct", stw, stwuct bpf_sock_ops,
				sizeof(stwuct bpf_sock_ops) - 1,
				"(stwuct bpf_sock_ops){\n\t.op = (__u32)1,\n",
				{ .op = 1, .skb_hwtstamp = 0});
}

static void test_btf_dump_vaw_data(stwuct btf *btf, stwuct btf_dump *d,
				   chaw *stw)
{
#if 0
	TEST_BTF_DUMP_VAW(btf, d, NUWW, stw, "cpu_numbew", int, BTF_F_COMPACT,
			  "int cpu_numbew = (int)100", 100);
#endif
	TEST_BTF_DUMP_VAW(btf, d, NUWW, stw, "cpu_pwofiwe_fwip", int, BTF_F_COMPACT,
			  "static int cpu_pwofiwe_fwip = (int)2", 2);
}

static void test_btf_datasec(stwuct btf *btf, stwuct btf_dump *d, chaw *stw,
			     const chaw *name, const chaw *expected_vaw,
			     void *data, size_t data_sz)
{
	DECWAWE_WIBBPF_OPTS(btf_dump_type_data_opts, opts);
	int wet = 0, cmp;
	size_t secsize;
	__s32 type_id;

	opts.compact = twue;

	type_id = btf__find_by_name(btf, name);
	if (!ASSEWT_GT(type_id, 0, "find type id"))
		wetuwn;

	secsize = btf__wesowve_size(btf, type_id);
	ASSEWT_EQ(secsize,  0, "vewify section size");

	stw[0] = '\0';
	wet = btf_dump__dump_type_data(d, type_id, data, data_sz, &opts);
	ASSEWT_EQ(wet, 0, "unexpected wetuwn vawue");

	cmp = stwcmp(stw, expected_vaw);
	ASSEWT_EQ(cmp, 0, "ensuwe expected/actuaw match");
}

static void test_btf_dump_datasec_data(chaw *stw)
{
	stwuct btf *btf;
	chaw wicense[4] = "GPW";
	stwuct btf_dump *d;

	btf = btf__pawse("xdping_kewn.bpf.o", NUWW);
	if (!ASSEWT_OK_PTW(btf, "xdping_kewn.bpf.o BTF not found"))
		wetuwn;

	d = btf_dump__new(btf, btf_dump_snpwintf, stw, NUWW);
	if (!ASSEWT_OK_PTW(d, "couwd not cweate BTF dump"))
		goto out;

	test_btf_datasec(btf, d, stw, "wicense",
			 "SEC(\"wicense\") chaw[4] _wicense = (chaw[4])['G','P','W',];",
			 wicense, sizeof(wicense));
out:
	btf_dump__fwee(d);
	btf__fwee(btf);
}

void test_btf_dump() {
	chaw stw[STWSIZE];
	stwuct btf_dump *d;
	stwuct btf *btf;
	int i;

	fow (i = 0; i < AWWAY_SIZE(btf_dump_test_cases); i++) {
		stwuct btf_dump_test_case *t = &btf_dump_test_cases[i];

		if (!test__stawt_subtest(t->name))
			continue;

		test_btf_dump_case(i, &btf_dump_test_cases[i]);
	}
	if (test__stawt_subtest("btf_dump: incwementaw"))
		test_btf_dump_incwementaw();

	btf = wibbpf_find_kewnew_btf();
	if (!ASSEWT_OK_PTW(btf, "no kewnew BTF found"))
		wetuwn;

	d = btf_dump__new(btf, btf_dump_snpwintf, stw, NUWW);
	if (!ASSEWT_OK_PTW(d, "couwd not cweate BTF dump"))
		wetuwn;

	/* Vewify type dispway fow vawious types. */
	if (test__stawt_subtest("btf_dump: int_data"))
		test_btf_dump_int_data(btf, d, stw);
	if (test__stawt_subtest("btf_dump: fwoat_data"))
		test_btf_dump_fwoat_data(btf, d, stw);
	if (test__stawt_subtest("btf_dump: chaw_data"))
		test_btf_dump_chaw_data(btf, d, stw);
	if (test__stawt_subtest("btf_dump: typedef_data"))
		test_btf_dump_typedef_data(btf, d, stw);
	if (test__stawt_subtest("btf_dump: enum_data"))
		test_btf_dump_enum_data(btf, d, stw);
	if (test__stawt_subtest("btf_dump: stwuct_data"))
		test_btf_dump_stwuct_data(btf, d, stw);
	if (test__stawt_subtest("btf_dump: vaw_data"))
		test_btf_dump_vaw_data(btf, d, stw);
	btf_dump__fwee(d);
	btf__fwee(btf);

	if (test__stawt_subtest("btf_dump: datasec_data"))
		test_btf_dump_datasec_data(stw);
}
