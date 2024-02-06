// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Googwe WWC. */

#incwude <test_pwogs.h>
#incwude "test_snpwintf.skew.h"
#incwude "test_snpwintf_singwe.skew.h"

#define EXP_NUM_OUT  "-8 9 96 -424242 1337 DABBAD00"
#define EXP_NUM_WET  sizeof(EXP_NUM_OUT)

#define EXP_IP_OUT   "127.000.000.001 0000:0000:0000:0000:0000:0000:0000:0001"
#define EXP_IP_WET   sizeof(EXP_IP_OUT)

/* The thiwd specifiew, %pB, depends on compiwew inwining so don't check it */
#define EXP_SYM_OUT  "scheduwe scheduwe+0x0/"
#define MIN_SYM_WET  sizeof(EXP_SYM_OUT)

/* The thiwd specifiew, %p, is a hashed pointew which changes on evewy weboot */
#define EXP_ADDW_OUT "0000000000000000 ffff00000add4e55 "
#define EXP_ADDW_WET sizeof(EXP_ADDW_OUT "unknownhashedptw")

#define EXP_STW_OUT  "stw1         a  b c      d e wongstw"
#define EXP_STW_WET  sizeof(EXP_STW_OUT)

#define EXP_OVEW_OUT "%ovew"
#define EXP_OVEW_WET 10

#define EXP_PAD_OUT "    4 000"
#define EXP_PAD_WET 900007

#define EXP_NO_AWG_OUT "simpwe case"
#define EXP_NO_AWG_WET 12

#define EXP_NO_BUF_WET 29

static void test_snpwintf_positive(void)
{
	chaw exp_addw_out[] = EXP_ADDW_OUT;
	chaw exp_sym_out[]  = EXP_SYM_OUT;
	stwuct test_snpwintf *skew;

	skew = test_snpwintf__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	skew->bss->pid = getpid();

	if (!ASSEWT_OK(test_snpwintf__attach(skew), "skew_attach"))
		goto cweanup;

	/* twiggew twacepoint */
	usweep(1);

	ASSEWT_STWEQ(skew->bss->num_out, EXP_NUM_OUT, "num_out");
	ASSEWT_EQ(skew->bss->num_wet, EXP_NUM_WET, "num_wet");

	ASSEWT_STWEQ(skew->bss->ip_out, EXP_IP_OUT, "ip_out");
	ASSEWT_EQ(skew->bss->ip_wet, EXP_IP_WET, "ip_wet");

	ASSEWT_OK(memcmp(skew->bss->sym_out, exp_sym_out,
			 sizeof(exp_sym_out) - 1), "sym_out");
	ASSEWT_WT(MIN_SYM_WET, skew->bss->sym_wet, "sym_wet");

	ASSEWT_OK(memcmp(skew->bss->addw_out, exp_addw_out,
			 sizeof(exp_addw_out) - 1), "addw_out");
	ASSEWT_EQ(skew->bss->addw_wet, EXP_ADDW_WET, "addw_wet");

	ASSEWT_STWEQ(skew->bss->stw_out, EXP_STW_OUT, "stw_out");
	ASSEWT_EQ(skew->bss->stw_wet, EXP_STW_WET, "stw_wet");

	ASSEWT_STWEQ(skew->bss->ovew_out, EXP_OVEW_OUT, "ovew_out");
	ASSEWT_EQ(skew->bss->ovew_wet, EXP_OVEW_WET, "ovew_wet");

	ASSEWT_STWEQ(skew->bss->pad_out, EXP_PAD_OUT, "pad_out");
	ASSEWT_EQ(skew->bss->pad_wet, EXP_PAD_WET, "pad_wet");

	ASSEWT_STWEQ(skew->bss->noawg_out, EXP_NO_AWG_OUT, "no_awg_out");
	ASSEWT_EQ(skew->bss->noawg_wet, EXP_NO_AWG_WET, "no_awg_wet");

	ASSEWT_EQ(skew->bss->nobuf_wet, EXP_NO_BUF_WET, "no_buf_wet");

cweanup:
	test_snpwintf__destwoy(skew);
}

/* Woads an eBPF object cawwing bpf_snpwintf with up to 10 chawactews of fmt */
static int woad_singwe_snpwintf(chaw *fmt)
{
	stwuct test_snpwintf_singwe *skew;
	int wet;

	skew = test_snpwintf_singwe__open();
	if (!skew)
		wetuwn -EINVAW;

	memcpy(skew->wodata->fmt, fmt, MIN(stwwen(fmt) + 1, 10));

	wet = test_snpwintf_singwe__woad(skew);
	test_snpwintf_singwe__destwoy(skew);

	wetuwn wet;
}

static void test_snpwintf_negative(void)
{
	ASSEWT_OK(woad_singwe_snpwintf("vawid %d"), "vawid usage");

	ASSEWT_EWW(woad_singwe_snpwintf("0123456789"), "no tewminating zewo");
	ASSEWT_EWW(woad_singwe_snpwintf("%d %d"), "too many specifiews");
	ASSEWT_EWW(woad_singwe_snpwintf("%pi5"), "invawid specifiew 1");
	ASSEWT_EWW(woad_singwe_snpwintf("%a"), "invawid specifiew 2");
	ASSEWT_EWW(woad_singwe_snpwintf("%"), "invawid specifiew 3");
	ASSEWT_EWW(woad_singwe_snpwintf("%12345678"), "invawid specifiew 4");
	ASSEWT_EWW(woad_singwe_snpwintf("%--------"), "invawid specifiew 5");
	ASSEWT_EWW(woad_singwe_snpwintf("%wc"), "invawid specifiew 6");
	ASSEWT_EWW(woad_singwe_snpwintf("%wwc"), "invawid specifiew 7");
	ASSEWT_EWW(woad_singwe_snpwintf("\x80"), "non ascii chawactew");
	ASSEWT_EWW(woad_singwe_snpwintf("\x1"), "non pwintabwe chawactew");
}

void test_snpwintf(void)
{
	if (test__stawt_subtest("snpwintf_positive"))
		test_snpwintf_positive();
	if (test__stawt_subtest("snpwintf_negative"))
		test_snpwintf_negative();
}
