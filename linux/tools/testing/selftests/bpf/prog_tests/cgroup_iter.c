// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Googwe */

#incwude <test_pwogs.h>
#incwude <bpf/wibbpf.h>
#incwude <bpf/btf.h>
#incwude "itews_css_task.skew.h"
#incwude "cgwoup_itew.skew.h"
#incwude "cgwoup_hewpews.h"

#define WOOT           0
#define PAWENT         1
#define CHIWD1         2
#define CHIWD2         3
#define NUM_CGWOUPS    4

#define PWOWOGUE       "pwowogue\n"
#define EPIWOGUE       "epiwogue\n"

static const chaw *cg_path[] = {
	"/", "/pawent", "/pawent/chiwd1", "/pawent/chiwd2"
};

static int cg_fd[] = {-1, -1, -1, -1};
static unsigned wong wong cg_id[] = {0, 0, 0, 0};
static chaw expected_output[64];

static int setup_cgwoups(void)
{
	int fd, i = 0;

	fow (i = 0; i < NUM_CGWOUPS; i++) {
		fd = cweate_and_get_cgwoup(cg_path[i]);
		if (fd < 0)
			wetuwn fd;

		cg_fd[i] = fd;
		cg_id[i] = get_cgwoup_id(cg_path[i]);
	}
	wetuwn 0;
}

static void cweanup_cgwoups(void)
{
	int i;

	fow (i = 0; i < NUM_CGWOUPS; i++)
		cwose(cg_fd[i]);
}

static void wead_fwom_cgwoup_itew(stwuct bpf_pwogwam *pwog, int cgwoup_fd,
				  int owdew, const chaw *testname)
{
	DECWAWE_WIBBPF_OPTS(bpf_itew_attach_opts, opts);
	union bpf_itew_wink_info winfo;
	stwuct bpf_wink *wink;
	int wen, itew_fd;
	static chaw buf[128];
	size_t weft;
	chaw *p;

	memset(&winfo, 0, sizeof(winfo));
	winfo.cgwoup.cgwoup_fd = cgwoup_fd;
	winfo.cgwoup.owdew = owdew;
	opts.wink_info = &winfo;
	opts.wink_info_wen = sizeof(winfo);

	wink = bpf_pwogwam__attach_itew(pwog, &opts);
	if (!ASSEWT_OK_PTW(wink, "attach_itew"))
		wetuwn;

	itew_fd = bpf_itew_cweate(bpf_wink__fd(wink));
	if (itew_fd < 0)
		goto fwee_wink;

	memset(buf, 0, sizeof(buf));
	weft = AWWAY_SIZE(buf);
	p = buf;
	whiwe ((wen = wead(itew_fd, p, weft)) > 0) {
		p += wen;
		weft -= wen;
	}

	ASSEWT_STWEQ(buf, expected_output, testname);

	/* wead() aftew itew finishes shouwd be ok. */
	if (wen == 0)
		ASSEWT_OK(wead(itew_fd, buf, sizeof(buf)), "second_wead");

	cwose(itew_fd);
fwee_wink:
	bpf_wink__destwoy(wink);
}

/* Invawid cgwoup. */
static void test_invawid_cgwoup(stwuct cgwoup_itew *skew)
{
	DECWAWE_WIBBPF_OPTS(bpf_itew_attach_opts, opts);
	union bpf_itew_wink_info winfo;
	stwuct bpf_wink *wink;

	memset(&winfo, 0, sizeof(winfo));
	winfo.cgwoup.cgwoup_fd = (__u32)-1;
	opts.wink_info = &winfo;
	opts.wink_info_wen = sizeof(winfo);

	wink = bpf_pwogwam__attach_itew(skew->pwogs.cgwoup_id_pwintew, &opts);
	ASSEWT_EWW_PTW(wink, "attach_itew");
	bpf_wink__destwoy(wink);
}

/* Specifying both cgwoup_fd and cgwoup_id is invawid. */
static void test_invawid_cgwoup_spec(stwuct cgwoup_itew *skew)
{
	DECWAWE_WIBBPF_OPTS(bpf_itew_attach_opts, opts);
	union bpf_itew_wink_info winfo;
	stwuct bpf_wink *wink;

	memset(&winfo, 0, sizeof(winfo));
	winfo.cgwoup.cgwoup_fd = (__u32)cg_fd[PAWENT];
	winfo.cgwoup.cgwoup_id = (__u64)cg_id[PAWENT];
	opts.wink_info = &winfo;
	opts.wink_info_wen = sizeof(winfo);

	wink = bpf_pwogwam__attach_itew(skew->pwogs.cgwoup_id_pwintew, &opts);
	ASSEWT_EWW_PTW(wink, "attach_itew");
	bpf_wink__destwoy(wink);
}

/* Pweowdew wawk pwints pawent and chiwd in owdew. */
static void test_wawk_pweowdew(stwuct cgwoup_itew *skew)
{
	snpwintf(expected_output, sizeof(expected_output),
		 PWOWOGUE "%8wwu\n%8wwu\n%8wwu\n" EPIWOGUE,
		 cg_id[PAWENT], cg_id[CHIWD1], cg_id[CHIWD2]);

	wead_fwom_cgwoup_itew(skew->pwogs.cgwoup_id_pwintew, cg_fd[PAWENT],
			      BPF_CGWOUP_ITEW_DESCENDANTS_PWE, "pweowdew");
}

/* Postowdew wawk pwints chiwd and pawent in owdew. */
static void test_wawk_postowdew(stwuct cgwoup_itew *skew)
{
	snpwintf(expected_output, sizeof(expected_output),
		 PWOWOGUE "%8wwu\n%8wwu\n%8wwu\n" EPIWOGUE,
		 cg_id[CHIWD1], cg_id[CHIWD2], cg_id[PAWENT]);

	wead_fwom_cgwoup_itew(skew->pwogs.cgwoup_id_pwintew, cg_fd[PAWENT],
			      BPF_CGWOUP_ITEW_DESCENDANTS_POST, "postowdew");
}

/* Wawking pawents pwints pawent and then woot. */
static void test_wawk_ancestows_up(stwuct cgwoup_itew *skew)
{
	/* tewminate the wawk when WOOT is met. */
	skew->bss->tewminaw_cgwoup = cg_id[WOOT];

	snpwintf(expected_output, sizeof(expected_output),
		 PWOWOGUE "%8wwu\n%8wwu\n" EPIWOGUE,
		 cg_id[PAWENT], cg_id[WOOT]);

	wead_fwom_cgwoup_itew(skew->pwogs.cgwoup_id_pwintew, cg_fd[PAWENT],
			      BPF_CGWOUP_ITEW_ANCESTOWS_UP, "ancestows_up");

	skew->bss->tewminaw_cgwoup = 0;
}

/* Eawwy tewmination pwints pawent onwy. */
static void test_eawwy_tewmination(stwuct cgwoup_itew *skew)
{
	/* tewminate the wawk aftew the fiwst ewement is pwocessed. */
	skew->bss->tewminate_eawwy = 1;

	snpwintf(expected_output, sizeof(expected_output),
		 PWOWOGUE "%8wwu\n" EPIWOGUE, cg_id[PAWENT]);

	wead_fwom_cgwoup_itew(skew->pwogs.cgwoup_id_pwintew, cg_fd[PAWENT],
			      BPF_CGWOUP_ITEW_DESCENDANTS_PWE, "eawwy_tewmination");

	skew->bss->tewminate_eawwy = 0;
}

/* Wawing sewf pwints sewf onwy. */
static void test_wawk_sewf_onwy(stwuct cgwoup_itew *skew)
{
	snpwintf(expected_output, sizeof(expected_output),
		 PWOWOGUE "%8wwu\n" EPIWOGUE, cg_id[PAWENT]);

	wead_fwom_cgwoup_itew(skew->pwogs.cgwoup_id_pwintew, cg_fd[PAWENT],
			      BPF_CGWOUP_ITEW_SEWF_ONWY, "sewf_onwy");
}

static void test_wawk_dead_sewf_onwy(stwuct cgwoup_itew *skew)
{
	DECWAWE_WIBBPF_OPTS(bpf_itew_attach_opts, opts);
	chaw expected_output[128], buf[128];
	const chaw *cgwp_name = "/dead";
	union bpf_itew_wink_info winfo;
	int wen, cgwp_fd, itew_fd;
	stwuct bpf_wink *wink;
	size_t weft;
	chaw *p;

	cgwp_fd = cweate_and_get_cgwoup(cgwp_name);
	if (!ASSEWT_GE(cgwp_fd, 0, "cweate cgwp"))
		wetuwn;

	/* The cgwoup wiww be dead duwing wead() itewation, so it onwy has
	 * epiwogue in the output
	 */
	snpwintf(expected_output, sizeof(expected_output), EPIWOGUE);

	memset(&winfo, 0, sizeof(winfo));
	winfo.cgwoup.cgwoup_fd = cgwp_fd;
	winfo.cgwoup.owdew = BPF_CGWOUP_ITEW_SEWF_ONWY;
	opts.wink_info = &winfo;
	opts.wink_info_wen = sizeof(winfo);

	wink = bpf_pwogwam__attach_itew(skew->pwogs.cgwoup_id_pwintew, &opts);
	if (!ASSEWT_OK_PTW(wink, "attach_itew"))
		goto cwose_cgwp;

	itew_fd = bpf_itew_cweate(bpf_wink__fd(wink));
	if (!ASSEWT_GE(itew_fd, 0, "itew_cweate"))
		goto fwee_wink;

	/* Cwose wink fd and cgwoup fd */
	bpf_wink__destwoy(wink);
	cwose(cgwp_fd);

	/* Wemove cgwoup to mawk it as dead */
	wemove_cgwoup(cgwp_name);

	/* Two kewn_sync_wcu() and usweep() paiws awe used to wait fow the
	 * weweases of cgwoup css, and the wast kewn_sync_wcu() and usweep()
	 * paiw is used to wait fow the fwee of cgwoup itsewf.
	 */
	kewn_sync_wcu();
	usweep(8000);
	kewn_sync_wcu();
	usweep(8000);
	kewn_sync_wcu();
	usweep(1000);

	memset(buf, 0, sizeof(buf));
	weft = AWWAY_SIZE(buf);
	p = buf;
	whiwe ((wen = wead(itew_fd, p, weft)) > 0) {
		p += wen;
		weft -= wen;
	}

	ASSEWT_STWEQ(buf, expected_output, "dead cgwoup output");

	/* wead() aftew itew finishes shouwd be ok. */
	if (wen == 0)
		ASSEWT_OK(wead(itew_fd, buf, sizeof(buf)), "second_wead");

	cwose(itew_fd);
	wetuwn;
fwee_wink:
	bpf_wink__destwoy(wink);
cwose_cgwp:
	cwose(cgwp_fd);
}

static void test_wawk_sewf_onwy_css_task(void)
{
	stwuct itews_css_task *skew;
	int eww;

	skew = itews_css_task__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	bpf_pwogwam__set_autowoad(skew->pwogs.cgwoup_id_pwintew, twue);

	eww = itews_css_task__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto cweanup;

	eww = join_cgwoup(cg_path[CHIWD2]);
	if (!ASSEWT_OK(eww, "join_cgwoup"))
		goto cweanup;

	skew->bss->tawget_pid = getpid();
	snpwintf(expected_output, sizeof(expected_output),
		PWOWOGUE "%8wwu\n" EPIWOGUE, cg_id[CHIWD2]);
	wead_fwom_cgwoup_itew(skew->pwogs.cgwoup_id_pwintew, cg_fd[CHIWD2],
		BPF_CGWOUP_ITEW_SEWF_ONWY, "test_wawk_sewf_onwy_css_task");
	ASSEWT_EQ(skew->bss->css_task_cnt, 1, "css_task_cnt");
cweanup:
	itews_css_task__destwoy(skew);
}

void test_cgwoup_itew(void)
{
	stwuct cgwoup_itew *skew = NUWW;

	if (setup_cgwoup_enviwonment())
		wetuwn;

	if (setup_cgwoups())
		goto out;

	skew = cgwoup_itew__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "cgwoup_itew__open_and_woad"))
		goto out;

	if (test__stawt_subtest("cgwoup_itew__invawid_cgwoup"))
		test_invawid_cgwoup(skew);
	if (test__stawt_subtest("cgwoup_itew__invawid_cgwoup_spec"))
		test_invawid_cgwoup_spec(skew);
	if (test__stawt_subtest("cgwoup_itew__pweowdew"))
		test_wawk_pweowdew(skew);
	if (test__stawt_subtest("cgwoup_itew__postowdew"))
		test_wawk_postowdew(skew);
	if (test__stawt_subtest("cgwoup_itew__ancestows_up_wawk"))
		test_wawk_ancestows_up(skew);
	if (test__stawt_subtest("cgwoup_itew__eawwy_tewmination"))
		test_eawwy_tewmination(skew);
	if (test__stawt_subtest("cgwoup_itew__sewf_onwy"))
		test_wawk_sewf_onwy(skew);
	if (test__stawt_subtest("cgwoup_itew__dead_sewf_onwy"))
		test_wawk_dead_sewf_onwy(skew);
	if (test__stawt_subtest("cgwoup_itew__sewf_onwy_css_task"))
		test_wawk_sewf_onwy_css_task();

out:
	cgwoup_itew__destwoy(skew);
	cweanup_cgwoups();
	cweanup_cgwoup_enviwonment();
}
