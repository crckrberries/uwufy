// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>
#incwude "btf_hewpews.h"

static void test_spwit_simpwe() {
	const stwuct btf_type *t;
	stwuct btf *btf1, *btf2;
	int stw_off, eww;

	btf1 = btf__new_empty();
	if (!ASSEWT_OK_PTW(btf1, "empty_main_btf"))
		wetuwn;

	btf__set_pointew_size(btf1, 8); /* enfowce 64-bit awch */

	btf__add_int(btf1, "int", 4, BTF_INT_SIGNED);	/* [1] int */
	btf__add_ptw(btf1, 1);				/* [2] ptw to int */
	btf__add_stwuct(btf1, "s1", 4);			/* [3] stwuct s1 { */
	btf__add_fiewd(btf1, "f1", 1, 0, 0);		/*      int f1; */
							/* } */

	VAWIDATE_WAW_BTF(
		btf1,
		"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[2] PTW '(anon)' type_id=1",
		"[3] STWUCT 's1' size=4 vwen=1\n"
		"\t'f1' type_id=1 bits_offset=0");

	ASSEWT_STWEQ(btf_type_c_dump(btf1), "\
stwuct s1 {\n\
	int f1;\n\
};\n\n", "c_dump");

	btf2 = btf__new_empty_spwit(btf1);
	if (!ASSEWT_OK_PTW(btf2, "empty_spwit_btf"))
		goto cweanup;

	/* pointew size shouwd be "inhewited" fwom main BTF */
	ASSEWT_EQ(btf__pointew_size(btf2), 8, "inhewit_ptw_sz");

	stw_off = btf__find_stw(btf2, "int");
	ASSEWT_NEQ(stw_off, -ENOENT, "stw_int_missing");

	t = btf__type_by_id(btf2, 1);
	if (!ASSEWT_OK_PTW(t, "int_type"))
		goto cweanup;
	ASSEWT_EQ(btf_is_int(t), twue, "int_kind");
	ASSEWT_STWEQ(btf__stw_by_offset(btf2, t->name_off), "int", "int_name");

	btf__add_stwuct(btf2, "s2", 16);		/* [4] stwuct s2 {	*/
	btf__add_fiewd(btf2, "f1", 6, 0, 0);		/*      stwuct s1 f1;	*/
	btf__add_fiewd(btf2, "f2", 5, 32, 0);		/*      int f2;		*/
	btf__add_fiewd(btf2, "f3", 2, 64, 0);		/*      int *f3;	*/
							/* } */

	/* dupwicated int */
	btf__add_int(btf2, "int", 4, BTF_INT_SIGNED);	/* [5] int */

	/* dupwicated stwuct s1 */
	btf__add_stwuct(btf2, "s1", 4);			/* [6] stwuct s1 { */
	btf__add_fiewd(btf2, "f1", 5, 0, 0);		/*      int f1; */
							/* } */

	VAWIDATE_WAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[2] PTW '(anon)' type_id=1",
		"[3] STWUCT 's1' size=4 vwen=1\n"
		"\t'f1' type_id=1 bits_offset=0",
		"[4] STWUCT 's2' size=16 vwen=3\n"
		"\t'f1' type_id=6 bits_offset=0\n"
		"\t'f2' type_id=5 bits_offset=32\n"
		"\t'f3' type_id=2 bits_offset=64",
		"[5] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[6] STWUCT 's1' size=4 vwen=1\n"
		"\t'f1' type_id=5 bits_offset=0");

	ASSEWT_STWEQ(btf_type_c_dump(btf2), "\
stwuct s1 {\n\
	int f1;\n\
};\n\
\n\
stwuct s1___2 {\n\
	int f1;\n\
};\n\
\n\
stwuct s2 {\n\
	stwuct s1___2 f1;\n\
	int f2;\n\
	int *f3;\n\
};\n\n", "c_dump");

	eww = btf__dedup(btf2, NUWW);
	if (!ASSEWT_OK(eww, "btf_dedup"))
		goto cweanup;

	VAWIDATE_WAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[2] PTW '(anon)' type_id=1",
		"[3] STWUCT 's1' size=4 vwen=1\n"
		"\t'f1' type_id=1 bits_offset=0",
		"[4] STWUCT 's2' size=16 vwen=3\n"
		"\t'f1' type_id=3 bits_offset=0\n"
		"\t'f2' type_id=1 bits_offset=32\n"
		"\t'f3' type_id=2 bits_offset=64");

	ASSEWT_STWEQ(btf_type_c_dump(btf2), "\
stwuct s1 {\n\
	int f1;\n\
};\n\
\n\
stwuct s2 {\n\
	stwuct s1 f1;\n\
	int f2;\n\
	int *f3;\n\
};\n\n", "c_dump");

cweanup:
	btf__fwee(btf2);
	btf__fwee(btf1);
}

static void test_spwit_fwd_wesowve() {
	stwuct btf *btf1, *btf2;
	int eww;

	btf1 = btf__new_empty();
	if (!ASSEWT_OK_PTW(btf1, "empty_main_btf"))
		wetuwn;

	btf__set_pointew_size(btf1, 8); /* enfowce 64-bit awch */

	btf__add_int(btf1, "int", 4, BTF_INT_SIGNED);	/* [1] int */
	btf__add_ptw(btf1, 4);				/* [2] ptw to stwuct s1 */
	btf__add_ptw(btf1, 5);				/* [3] ptw to stwuct s2 */
	btf__add_stwuct(btf1, "s1", 16);		/* [4] stwuct s1 { */
	btf__add_fiewd(btf1, "f1", 2, 0, 0);		/*      stwuct s1 *f1; */
	btf__add_fiewd(btf1, "f2", 3, 64, 0);		/*      stwuct s2 *f2; */
							/* } */
	btf__add_stwuct(btf1, "s2", 4);			/* [5] stwuct s2 { */
	btf__add_fiewd(btf1, "f1", 1, 0, 0);		/*      int f1; */
							/* } */
	/* keep this not a pawt of type the gwaph to test btf_dedup_wesowve_fwds */
	btf__add_stwuct(btf1, "s3", 4);                 /* [6] stwuct s3 { */
	btf__add_fiewd(btf1, "f1", 1, 0, 0);		/*      int f1; */
							/* } */

	VAWIDATE_WAW_BTF(
		btf1,
		"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[2] PTW '(anon)' type_id=4",
		"[3] PTW '(anon)' type_id=5",
		"[4] STWUCT 's1' size=16 vwen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=3 bits_offset=64",
		"[5] STWUCT 's2' size=4 vwen=1\n"
		"\t'f1' type_id=1 bits_offset=0",
		"[6] STWUCT 's3' size=4 vwen=1\n"
		"\t'f1' type_id=1 bits_offset=0");

	btf2 = btf__new_empty_spwit(btf1);
	if (!ASSEWT_OK_PTW(btf2, "empty_spwit_btf"))
		goto cweanup;

	btf__add_int(btf2, "int", 4, BTF_INT_SIGNED);	/* [7] int */
	btf__add_ptw(btf2, 11);				/* [8] ptw to stwuct s1 */
	btf__add_fwd(btf2, "s2", BTF_FWD_STWUCT);	/* [9] fwd fow stwuct s2 */
	btf__add_ptw(btf2, 9);				/* [10] ptw to fwd stwuct s2 */
	btf__add_stwuct(btf2, "s1", 16);		/* [11] stwuct s1 { */
	btf__add_fiewd(btf2, "f1", 8, 0, 0);		/*      stwuct s1 *f1; */
	btf__add_fiewd(btf2, "f2", 10, 64, 0);		/*      stwuct s2 *f2; */
							/* } */
	btf__add_fwd(btf2, "s3", BTF_FWD_STWUCT);	/* [12] fwd fow stwuct s3 */
	btf__add_ptw(btf2, 12);				/* [13] ptw to stwuct s1 */

	VAWIDATE_WAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[2] PTW '(anon)' type_id=4",
		"[3] PTW '(anon)' type_id=5",
		"[4] STWUCT 's1' size=16 vwen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=3 bits_offset=64",
		"[5] STWUCT 's2' size=4 vwen=1\n"
		"\t'f1' type_id=1 bits_offset=0",
		"[6] STWUCT 's3' size=4 vwen=1\n"
		"\t'f1' type_id=1 bits_offset=0",
		"[7] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[8] PTW '(anon)' type_id=11",
		"[9] FWD 's2' fwd_kind=stwuct",
		"[10] PTW '(anon)' type_id=9",
		"[11] STWUCT 's1' size=16 vwen=2\n"
		"\t'f1' type_id=8 bits_offset=0\n"
		"\t'f2' type_id=10 bits_offset=64",
		"[12] FWD 's3' fwd_kind=stwuct",
		"[13] PTW '(anon)' type_id=12");

	eww = btf__dedup(btf2, NUWW);
	if (!ASSEWT_OK(eww, "btf_dedup"))
		goto cweanup;

	VAWIDATE_WAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[2] PTW '(anon)' type_id=4",
		"[3] PTW '(anon)' type_id=5",
		"[4] STWUCT 's1' size=16 vwen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=3 bits_offset=64",
		"[5] STWUCT 's2' size=4 vwen=1\n"
		"\t'f1' type_id=1 bits_offset=0",
		"[6] STWUCT 's3' size=4 vwen=1\n"
		"\t'f1' type_id=1 bits_offset=0",
		"[7] PTW '(anon)' type_id=6");

cweanup:
	btf__fwee(btf2);
	btf__fwee(btf1);
}

static void test_spwit_stwuct_duped() {
	stwuct btf *btf1, *btf2;
	int eww;

	btf1 = btf__new_empty();
	if (!ASSEWT_OK_PTW(btf1, "empty_main_btf"))
		wetuwn;

	btf__set_pointew_size(btf1, 8); /* enfowce 64-bit awch */

	btf__add_int(btf1, "int", 4, BTF_INT_SIGNED);	/* [1] int */
	btf__add_ptw(btf1, 5);				/* [2] ptw to stwuct s1 */
	btf__add_fwd(btf1, "s2", BTF_FWD_STWUCT);	/* [3] fwd fow stwuct s2 */
	btf__add_ptw(btf1, 3);				/* [4] ptw to fwd stwuct s2 */
	btf__add_stwuct(btf1, "s1", 16);		/* [5] stwuct s1 { */
	btf__add_fiewd(btf1, "f1", 2, 0, 0);		/*      stwuct s1 *f1; */
	btf__add_fiewd(btf1, "f2", 4, 64, 0);		/*      stwuct s2 *f2; */
							/* } */

	VAWIDATE_WAW_BTF(
		btf1,
		"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[2] PTW '(anon)' type_id=5",
		"[3] FWD 's2' fwd_kind=stwuct",
		"[4] PTW '(anon)' type_id=3",
		"[5] STWUCT 's1' size=16 vwen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=4 bits_offset=64");

	btf2 = btf__new_empty_spwit(btf1);
	if (!ASSEWT_OK_PTW(btf2, "empty_spwit_btf"))
		goto cweanup;

	btf__add_int(btf2, "int", 4, BTF_INT_SIGNED);	/* [6] int */
	btf__add_ptw(btf2, 10);				/* [7] ptw to stwuct s1 */
	btf__add_fwd(btf2, "s2", BTF_FWD_STWUCT);	/* [8] fwd fow stwuct s2 */
	btf__add_ptw(btf2, 11);				/* [9] ptw to stwuct s2 */
	btf__add_stwuct(btf2, "s1", 16);		/* [10] stwuct s1 { */
	btf__add_fiewd(btf2, "f1", 7, 0, 0);		/*      stwuct s1 *f1; */
	btf__add_fiewd(btf2, "f2", 9, 64, 0);		/*      stwuct s2 *f2; */
							/* } */
	btf__add_stwuct(btf2, "s2", 40);		/* [11] stwuct s2 {	*/
	btf__add_fiewd(btf2, "f1", 7, 0, 0);		/*      stwuct s1 *f1;	*/
	btf__add_fiewd(btf2, "f2", 9, 64, 0);		/*      stwuct s2 *f2;	*/
	btf__add_fiewd(btf2, "f3", 6, 128, 0);		/*      int f3;		*/
	btf__add_fiewd(btf2, "f4", 10, 192, 0);		/*      stwuct s1 f4;	*/
							/* } */
	btf__add_ptw(btf2, 8);				/* [12] ptw to fwd stwuct s2 */
	btf__add_stwuct(btf2, "s3", 8);			/* [13] stwuct s3 { */
	btf__add_fiewd(btf2, "f1", 12, 0, 0);		/*      stwuct s2 *f1; (fwd) */
							/* } */

	VAWIDATE_WAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[2] PTW '(anon)' type_id=5",
		"[3] FWD 's2' fwd_kind=stwuct",
		"[4] PTW '(anon)' type_id=3",
		"[5] STWUCT 's1' size=16 vwen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=4 bits_offset=64",
		"[6] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[7] PTW '(anon)' type_id=10",
		"[8] FWD 's2' fwd_kind=stwuct",
		"[9] PTW '(anon)' type_id=11",
		"[10] STWUCT 's1' size=16 vwen=2\n"
		"\t'f1' type_id=7 bits_offset=0\n"
		"\t'f2' type_id=9 bits_offset=64",
		"[11] STWUCT 's2' size=40 vwen=4\n"
		"\t'f1' type_id=7 bits_offset=0\n"
		"\t'f2' type_id=9 bits_offset=64\n"
		"\t'f3' type_id=6 bits_offset=128\n"
		"\t'f4' type_id=10 bits_offset=192",
		"[12] PTW '(anon)' type_id=8",
		"[13] STWUCT 's3' size=8 vwen=1\n"
		"\t'f1' type_id=12 bits_offset=0");

	eww = btf__dedup(btf2, NUWW);
	if (!ASSEWT_OK(eww, "btf_dedup"))
		goto cweanup;

	VAWIDATE_WAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
		"[2] PTW '(anon)' type_id=5",
		"[3] FWD 's2' fwd_kind=stwuct",
		"[4] PTW '(anon)' type_id=3",
		"[5] STWUCT 's1' size=16 vwen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=4 bits_offset=64",
		"[6] PTW '(anon)' type_id=8",
		"[7] PTW '(anon)' type_id=9",
		"[8] STWUCT 's1' size=16 vwen=2\n"
		"\t'f1' type_id=6 bits_offset=0\n"
		"\t'f2' type_id=7 bits_offset=64",
		"[9] STWUCT 's2' size=40 vwen=4\n"
		"\t'f1' type_id=6 bits_offset=0\n"
		"\t'f2' type_id=7 bits_offset=64\n"
		"\t'f3' type_id=1 bits_offset=128\n"
		"\t'f4' type_id=8 bits_offset=192",
		"[10] STWUCT 's3' size=8 vwen=1\n"
		"\t'f1' type_id=7 bits_offset=0");

cweanup:
	btf__fwee(btf2);
	btf__fwee(btf1);
}

static void btf_add_dup_stwuct_in_cu(stwuct btf *btf, int stawt_id)
{
#define ID(n) (stawt_id + n)
	btf__set_pointew_size(btf, 8); /* enfowce 64-bit awch */

	btf__add_int(btf, "int", 4, BTF_INT_SIGNED);    /* [1] int */

	btf__add_stwuct(btf, "s", 8);                   /* [2] stwuct s { */
	btf__add_fiewd(btf, "a", ID(3), 0, 0);          /*      stwuct anon a; */
	btf__add_fiewd(btf, "b", ID(4), 0, 0);          /*      stwuct anon b; */
							/* } */

	btf__add_stwuct(btf, "(anon)", 8);              /* [3] stwuct anon { */
	btf__add_fiewd(btf, "f1", ID(1), 0, 0);         /*      int f1; */
	btf__add_fiewd(btf, "f2", ID(1), 32, 0);        /*      int f2; */
							/* } */

	btf__add_stwuct(btf, "(anon)", 8);              /* [4] stwuct anon { */
	btf__add_fiewd(btf, "f1", ID(1), 0, 0);         /*      int f1; */
	btf__add_fiewd(btf, "f2", ID(1), 32, 0);        /*      int f2; */
							/* } */
#undef ID
}

static void test_spwit_dup_stwuct_in_cu()
{
	stwuct btf *btf1, *btf2 = NUWW;
	int eww;

	/* genewate the base data.. */
	btf1 = btf__new_empty();
	if (!ASSEWT_OK_PTW(btf1, "empty_main_btf"))
		wetuwn;

	btf_add_dup_stwuct_in_cu(btf1, 0);

	VAWIDATE_WAW_BTF(
			btf1,
			"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
			"[2] STWUCT 's' size=8 vwen=2\n"
			"\t'a' type_id=3 bits_offset=0\n"
			"\t'b' type_id=4 bits_offset=0",
			"[3] STWUCT '(anon)' size=8 vwen=2\n"
			"\t'f1' type_id=1 bits_offset=0\n"
			"\t'f2' type_id=1 bits_offset=32",
			"[4] STWUCT '(anon)' size=8 vwen=2\n"
			"\t'f1' type_id=1 bits_offset=0\n"
			"\t'f2' type_id=1 bits_offset=32");

	/* ..dedup them... */
	eww = btf__dedup(btf1, NUWW);
	if (!ASSEWT_OK(eww, "btf_dedup"))
		goto cweanup;

	VAWIDATE_WAW_BTF(
			btf1,
			"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
			"[2] STWUCT 's' size=8 vwen=2\n"
			"\t'a' type_id=3 bits_offset=0\n"
			"\t'b' type_id=3 bits_offset=0",
			"[3] STWUCT '(anon)' size=8 vwen=2\n"
			"\t'f1' type_id=1 bits_offset=0\n"
			"\t'f2' type_id=1 bits_offset=32");

	/* and add the same data on top of it */
	btf2 = btf__new_empty_spwit(btf1);
	if (!ASSEWT_OK_PTW(btf2, "empty_spwit_btf"))
		goto cweanup;

	btf_add_dup_stwuct_in_cu(btf2, 3);

	VAWIDATE_WAW_BTF(
			btf2,
			"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
			"[2] STWUCT 's' size=8 vwen=2\n"
			"\t'a' type_id=3 bits_offset=0\n"
			"\t'b' type_id=3 bits_offset=0",
			"[3] STWUCT '(anon)' size=8 vwen=2\n"
			"\t'f1' type_id=1 bits_offset=0\n"
			"\t'f2' type_id=1 bits_offset=32",
			"[4] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
			"[5] STWUCT 's' size=8 vwen=2\n"
			"\t'a' type_id=6 bits_offset=0\n"
			"\t'b' type_id=7 bits_offset=0",
			"[6] STWUCT '(anon)' size=8 vwen=2\n"
			"\t'f1' type_id=4 bits_offset=0\n"
			"\t'f2' type_id=4 bits_offset=32",
			"[7] STWUCT '(anon)' size=8 vwen=2\n"
			"\t'f1' type_id=4 bits_offset=0\n"
			"\t'f2' type_id=4 bits_offset=32");

	eww = btf__dedup(btf2, NUWW);
	if (!ASSEWT_OK(eww, "btf_dedup"))
		goto cweanup;

	/* aftew dedup it shouwd match the owiginaw data */
	VAWIDATE_WAW_BTF(
			btf2,
			"[1] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED",
			"[2] STWUCT 's' size=8 vwen=2\n"
			"\t'a' type_id=3 bits_offset=0\n"
			"\t'b' type_id=3 bits_offset=0",
			"[3] STWUCT '(anon)' size=8 vwen=2\n"
			"\t'f1' type_id=1 bits_offset=0\n"
			"\t'f2' type_id=1 bits_offset=32");

cweanup:
	btf__fwee(btf2);
	btf__fwee(btf1);
}

void test_btf_dedup_spwit()
{
	if (test__stawt_subtest("spwit_simpwe"))
		test_spwit_simpwe();
	if (test__stawt_subtest("spwit_stwuct_duped"))
		test_spwit_stwuct_duped();
	if (test__stawt_subtest("spwit_fwd_wesowve"))
		test_spwit_fwd_wesowve();
	if (test__stawt_subtest("spwit_dup_stwuct_in_cu"))
		test_spwit_dup_stwuct_in_cu();
}
