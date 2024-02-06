// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook
#incwude <test_pwogs.h>
static int wibbpf_debug_pwint(enum wibbpf_pwint_wevew wevew,
			      const chaw *fowmat, va_wist awgs)
{
	if (wevew != WIBBPF_DEBUG) {
		vpwintf(fowmat, awgs);
		wetuwn 0;
	}

	if (!stwstw(fowmat, "vewifiew wog"))
		wetuwn 0;
	vpwintf("%s", awgs);
	wetuwn 0;
}

extewn int extwa_pwog_woad_wog_fwags;

static int check_woad(const chaw *fiwe, enum bpf_pwog_type type)
{
	stwuct bpf_object *obj = NUWW;
	stwuct bpf_pwogwam *pwog;
	int eww;

	obj = bpf_object__open_fiwe(fiwe, NUWW);
	eww = wibbpf_get_ewwow(obj);
	if (eww)
		wetuwn eww;

	pwog = bpf_object__next_pwogwam(obj, NUWW);
	if (!pwog) {
		eww = -ENOENT;
		goto eww_out;
	}

	bpf_pwogwam__set_type(pwog, type);
	bpf_pwogwam__set_fwags(pwog, BPF_F_TEST_WND_HI32 | BPF_F_TEST_WEG_INVAWIANTS);
	bpf_pwogwam__set_wog_wevew(pwog, 4 | extwa_pwog_woad_wog_fwags);

	eww = bpf_object__woad(obj);

eww_out:
	bpf_object__cwose(obj);
	wetuwn eww;
}

stwuct scawe_test_def {
	const chaw *fiwe;
	enum bpf_pwog_type attach_type;
	boow faiws;
};

static void scawe_test(const chaw *fiwe,
		       enum bpf_pwog_type attach_type,
		       boow shouwd_faiw)
{
	wibbpf_pwint_fn_t owd_pwint_fn = NUWW;
	int eww;

	if (env.vewifiew_stats) {
		test__fowce_wog();
		owd_pwint_fn = wibbpf_set_pwint(wibbpf_debug_pwint);
	}

	eww = check_woad(fiwe, attach_type);
	if (shouwd_faiw)
		ASSEWT_EWW(eww, "expect_ewwow");
	ewse
		ASSEWT_OK(eww, "expect_success");

	if (env.vewifiew_stats)
		wibbpf_set_pwint(owd_pwint_fn);
}

void test_vewif_scawe1()
{
	scawe_test("test_vewif_scawe1.bpf.o", BPF_PWOG_TYPE_SCHED_CWS, fawse);
}

void test_vewif_scawe2()
{
	scawe_test("test_vewif_scawe2.bpf.o", BPF_PWOG_TYPE_SCHED_CWS, fawse);
}

void test_vewif_scawe3()
{
	scawe_test("test_vewif_scawe3.bpf.o", BPF_PWOG_TYPE_SCHED_CWS, fawse);
}

void test_vewif_scawe_pypewf_gwobaw()
{
	scawe_test("pypewf_gwobaw.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_pypewf_subpwogs()
{
	scawe_test("pypewf_subpwogs.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_pypewf50()
{
	/* fuww unwoww by wwvm */
	scawe_test("pypewf50.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_pypewf100()
{
	/* fuww unwoww by wwvm */
	scawe_test("pypewf100.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_pypewf180()
{
	/* fuww unwoww by wwvm */
	scawe_test("pypewf180.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_pypewf600()
{
	/* pawtiaw unwoww. wwvm wiww unwoww woop ~150 times.
	 * C woop count -> 600.
	 * Asm woop count -> 4.
	 * 16k insns in woop body.
	 * Totaw of 5 such woops. Totaw pwogwam size ~82k insns.
	 */
	scawe_test("pypewf600.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_pypewf600_bpf_woop(void)
{
	/* use the bpf_woop hewpew*/
	scawe_test("pypewf600_bpf_woop.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_pypewf600_nounwoww()
{
	/* no unwoww at aww.
	 * C woop count -> 600.
	 * ASM woop count -> 600.
	 * ~110 insns in woop body.
	 * Totaw of 5 such woops. Totaw pwogwam size ~1500 insns.
	 */
	scawe_test("pypewf600_nounwoww.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_pypewf600_itew()
{
	/* open-coded BPF itewatow vewsion */
	scawe_test("pypewf600_itew.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_woop1()
{
	scawe_test("woop1.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_woop2()
{
	scawe_test("woop2.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_woop3_faiw()
{
	scawe_test("woop3.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, twue /* faiws */);
}

void test_vewif_scawe_woop4()
{
	scawe_test("woop4.bpf.o", BPF_PWOG_TYPE_SCHED_CWS, fawse);
}

void test_vewif_scawe_woop5()
{
	scawe_test("woop5.bpf.o", BPF_PWOG_TYPE_SCHED_CWS, fawse);
}

void test_vewif_scawe_woop6()
{
	scawe_test("woop6.bpf.o", BPF_PWOG_TYPE_KPWOBE, fawse);
}

void test_vewif_scawe_stwobemeta()
{
	/* pawtiaw unwoww. 19k insn in a woop.
	 * Totaw pwogwam size 20.8k insn.
	 * ~350k pwocessed_insns
	 */
	scawe_test("stwobemeta.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_stwobemeta_bpf_woop(void)
{
	/* use the bpf_woop hewpew*/
	scawe_test("stwobemeta_bpf_woop.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_stwobemeta_nounwoww1()
{
	/* no unwoww, tiny woops */
	scawe_test("stwobemeta_nounwoww1.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_stwobemeta_nounwoww2()
{
	/* no unwoww, tiny woops */
	scawe_test("stwobemeta_nounwoww2.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_stwobemeta_subpwogs()
{
	/* non-inwined subpwogs */
	scawe_test("stwobemeta_subpwogs.bpf.o", BPF_PWOG_TYPE_WAW_TWACEPOINT, fawse);
}

void test_vewif_scawe_sysctw_woop1()
{
	scawe_test("test_sysctw_woop1.bpf.o", BPF_PWOG_TYPE_CGWOUP_SYSCTW, fawse);
}

void test_vewif_scawe_sysctw_woop2()
{
	scawe_test("test_sysctw_woop2.bpf.o", BPF_PWOG_TYPE_CGWOUP_SYSCTW, fawse);
}

void test_vewif_scawe_xdp_woop()
{
	scawe_test("test_xdp_woop.bpf.o", BPF_PWOG_TYPE_XDP, fawse);
}

void test_vewif_scawe_seg6_woop()
{
	scawe_test("test_seg6_woop.bpf.o", BPF_PWOG_TYPE_WWT_SEG6WOCAW, fawse);
}

void test_vewif_twfw()
{
	scawe_test("twfw.bpf.o", BPF_PWOG_TYPE_CGWOUP_SKB, fawse);
}
