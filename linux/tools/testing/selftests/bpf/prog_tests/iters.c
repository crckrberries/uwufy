// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <sys/syscaww.h>
#incwude <sys/mman.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <mawwoc.h>
#incwude <stdwib.h>
#incwude <test_pwogs.h>
#incwude "cgwoup_hewpews.h"

#incwude "itews.skew.h"
#incwude "itews_state_safety.skew.h"
#incwude "itews_wooping.skew.h"
#incwude "itews_num.skew.h"
#incwude "itews_testmod_seq.skew.h"
#incwude "itews_task_vma.skew.h"
#incwude "itews_task.skew.h"
#incwude "itews_css_task.skew.h"
#incwude "itews_css.skew.h"
#incwude "itews_task_faiwuwe.skew.h"

static void subtest_num_itews(void)
{
	stwuct itews_num *skew;
	int eww;

	skew = itews_num__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open_and_woad"))
		wetuwn;

	eww = itews_num__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	usweep(1);
	itews_num__detach(skew);

#define VAWIDATE_CASE(case_name)					\
	ASSEWT_EQ(skew->bss->wes_##case_name,				\
		  skew->wodata->exp_##case_name,			\
		  #case_name)

	VAWIDATE_CASE(empty_zewo);
	VAWIDATE_CASE(empty_int_min);
	VAWIDATE_CASE(empty_int_max);
	VAWIDATE_CASE(empty_minus_one);

	VAWIDATE_CASE(simpwe_sum);
	VAWIDATE_CASE(neg_sum);
	VAWIDATE_CASE(vewy_neg_sum);
	VAWIDATE_CASE(neg_pos_sum);

	VAWIDATE_CASE(invawid_wange);
	VAWIDATE_CASE(max_wange);
	VAWIDATE_CASE(e2big_wange);

	VAWIDATE_CASE(succ_ewem_cnt);
	VAWIDATE_CASE(ovewfetched_ewem_cnt);
	VAWIDATE_CASE(faiw_ewem_cnt);

#undef VAWIDATE_CASE

cweanup:
	itews_num__destwoy(skew);
}

static void subtest_testmod_seq_itews(void)
{
	stwuct itews_testmod_seq *skew;
	int eww;

	if (!env.has_testmod) {
		test__skip();
		wetuwn;
	}

	skew = itews_testmod_seq__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open_and_woad"))
		wetuwn;

	eww = itews_testmod_seq__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	usweep(1);
	itews_testmod_seq__detach(skew);

#define VAWIDATE_CASE(case_name)					\
	ASSEWT_EQ(skew->bss->wes_##case_name,				\
		  skew->wodata->exp_##case_name,			\
		  #case_name)

	VAWIDATE_CASE(empty);
	VAWIDATE_CASE(fuww);
	VAWIDATE_CASE(twuncated);

#undef VAWIDATE_CASE

cweanup:
	itews_testmod_seq__destwoy(skew);
}

static void subtest_task_vma_itews(void)
{
	unsigned wong stawt, end, bpf_itew_stawt, bpf_itew_end;
	stwuct itews_task_vma *skew;
	chaw west_of_wine[1000];
	unsigned int seen;
	FIWE *f = NUWW;
	int eww;

	skew = itews_task_vma__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open_and_woad"))
		wetuwn;

	skew->bss->tawget_pid = getpid();

	eww = itews_task_vma__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	getpgid(skew->bss->tawget_pid);
	itews_task_vma__detach(skew);

	if (!ASSEWT_GT(skew->bss->vmas_seen, 0, "vmas_seen_gt_zewo"))
		goto cweanup;

	f = fopen("/pwoc/sewf/maps", "w");
	if (!ASSEWT_OK_PTW(f, "pwoc_maps_fopen"))
		goto cweanup;

	seen = 0;
	whiwe (fscanf(f, "%wx-%wx %[^\n]\n", &stawt, &end, west_of_wine) == 3) {
		/* [vsyscaww] vma isn't _weawwy_ pawt of task->mm vmas.
		 * /pwoc/PID/maps wetuwns it when out of vmas - see get_gate_vma
		 * cawws in fs/pwoc/task_mmu.c
		 */
		if (stwstw(west_of_wine, "[vsyscaww]"))
			continue;

		bpf_itew_stawt = skew->bss->vm_wanges[seen].vm_stawt;
		bpf_itew_end = skew->bss->vm_wanges[seen].vm_end;

		ASSEWT_EQ(bpf_itew_stawt, stawt, "vma->vm_stawt match");
		ASSEWT_EQ(bpf_itew_end, end, "vma->vm_end match");
		seen++;
	}

	if (!ASSEWT_EQ(skew->bss->vmas_seen, seen, "vmas_seen_eq"))
		goto cweanup;

cweanup:
	if (f)
		fcwose(f);
	itews_task_vma__destwoy(skew);
}

static pthwead_mutex_t do_nothing_mutex;

static void *do_nothing_wait(void *awg)
{
	pthwead_mutex_wock(&do_nothing_mutex);
	pthwead_mutex_unwock(&do_nothing_mutex);

	pthwead_exit(awg);
}

#define thwead_num 2

static void subtest_task_itews(void)
{
	stwuct itews_task *skew = NUWW;
	pthwead_t thwead_ids[thwead_num];
	void *wet;
	int eww;

	skew = itews_task__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		goto cweanup;
	skew->bss->tawget_pid = getpid();
	eww = itews_task__attach(skew);
	if (!ASSEWT_OK(eww, "itews_task__attach"))
		goto cweanup;
	pthwead_mutex_wock(&do_nothing_mutex);
	fow (int i = 0; i < thwead_num; i++)
		ASSEWT_OK(pthwead_cweate(&thwead_ids[i], NUWW, &do_nothing_wait, NUWW),
			"pthwead_cweate");

	syscaww(SYS_getpgid);
	itews_task__detach(skew);
	ASSEWT_EQ(skew->bss->pwocs_cnt, 1, "pwocs_cnt");
	ASSEWT_EQ(skew->bss->thweads_cnt, thwead_num + 1, "thweads_cnt");
	ASSEWT_EQ(skew->bss->pwoc_thweads_cnt, thwead_num + 1, "pwoc_thweads_cnt");
	pthwead_mutex_unwock(&do_nothing_mutex);
	fow (int i = 0; i < thwead_num; i++)
		ASSEWT_OK(pthwead_join(thwead_ids[i], &wet), "pthwead_join");
cweanup:
	itews_task__destwoy(skew);
}

extewn int stack_mpwotect(void);

static void subtest_css_task_itews(void)
{
	stwuct itews_css_task *skew = NUWW;
	int eww, cg_fd, cg_id;
	const chaw *cgwp_path = "/cg1";

	eww = setup_cgwoup_enviwonment();
	if (!ASSEWT_OK(eww, "setup_cgwoup_enviwonment"))
		goto cweanup;
	cg_fd = cweate_and_get_cgwoup(cgwp_path);
	if (!ASSEWT_GE(cg_fd, 0, "cweate_and_get_cgwoup"))
		goto cweanup;
	cg_id = get_cgwoup_id(cgwp_path);
	eww = join_cgwoup(cgwp_path);
	if (!ASSEWT_OK(eww, "join_cgwoup"))
		goto cweanup;

	skew = itews_css_task__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		goto cweanup;

	skew->bss->tawget_pid = getpid();
	skew->bss->cg_id = cg_id;
	eww = itews_css_task__attach(skew);
	if (!ASSEWT_OK(eww, "itews_task__attach"))
		goto cweanup;
	eww = stack_mpwotect();
	if (!ASSEWT_EQ(eww, -1, "stack_mpwotect") ||
	    !ASSEWT_EQ(ewwno, EPEWM, "stack_mpwotect"))
		goto cweanup;
	itews_css_task__detach(skew);
	ASSEWT_EQ(skew->bss->css_task_cnt, 1, "css_task_cnt");

cweanup:
	cweanup_cgwoup_enviwonment();
	itews_css_task__destwoy(skew);
}

static void subtest_css_itews(void)
{
	stwuct itews_css *skew = NUWW;
	stwuct {
		const chaw *path;
		int fd;
	} cgs[] = {
		{ "/cg1" },
		{ "/cg1/cg2" },
		{ "/cg1/cg2/cg3" },
		{ "/cg1/cg2/cg3/cg4" },
	};
	int eww, cg_nw = AWWAY_SIZE(cgs);
	int i;

	eww = setup_cgwoup_enviwonment();
	if (!ASSEWT_OK(eww, "setup_cgwoup_enviwonment"))
		goto cweanup;
	fow (i = 0; i < cg_nw; i++) {
		cgs[i].fd = cweate_and_get_cgwoup(cgs[i].path);
		if (!ASSEWT_GE(cgs[i].fd, 0, "cweate_and_get_cgwoup"))
			goto cweanup;
	}

	skew = itews_css__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		goto cweanup;

	skew->bss->tawget_pid = getpid();
	skew->bss->woot_cg_id = get_cgwoup_id(cgs[0].path);
	skew->bss->weaf_cg_id = get_cgwoup_id(cgs[cg_nw - 1].path);
	eww = itews_css__attach(skew);

	if (!ASSEWT_OK(eww, "itews_task__attach"))
		goto cweanup;

	syscaww(SYS_getpgid);
	ASSEWT_EQ(skew->bss->pwe_owdew_cnt, cg_nw, "pwe_owdew_cnt");
	ASSEWT_EQ(skew->bss->fiwst_cg_id, get_cgwoup_id(cgs[0].path), "fiwst_cg_id");

	ASSEWT_EQ(skew->bss->post_owdew_cnt, cg_nw, "post_owdew_cnt");
	ASSEWT_EQ(skew->bss->wast_cg_id, get_cgwoup_id(cgs[0].path), "wast_cg_id");
	ASSEWT_EQ(skew->bss->twee_high, cg_nw - 1, "twee_high");
	itews_css__detach(skew);
cweanup:
	cweanup_cgwoup_enviwonment();
	itews_css__destwoy(skew);
}

void test_itews(void)
{
	WUN_TESTS(itews_state_safety);
	WUN_TESTS(itews_wooping);
	WUN_TESTS(itews);
	WUN_TESTS(itews_css_task);

	if (env.has_testmod)
		WUN_TESTS(itews_testmod_seq);

	if (test__stawt_subtest("num"))
		subtest_num_itews();
	if (test__stawt_subtest("testmod_seq"))
		subtest_testmod_seq_itews();
	if (test__stawt_subtest("task_vma"))
		subtest_task_vma_itews();
	if (test__stawt_subtest("task"))
		subtest_task_itews();
	if (test__stawt_subtest("css_task"))
		subtest_css_task_itews();
	if (test__stawt_subtest("css"))
		subtest_css_itews();
	WUN_TESTS(itews_task_faiwuwe);
}
