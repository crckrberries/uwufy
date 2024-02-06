// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/wist.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <subcmd/pagew.h>
#incwude <sys/types.h>
#incwude <ctype.h>
#incwude <diwent.h>
#incwude <pthwead.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude "cpumap.h"
#incwude "debug.h"
#incwude "evsew.h"
#incwude "pmus.h"
#incwude "pmu.h"
#incwude "pwint-events.h"

/*
 * cowe_pmus:  A PMU bewongs to cowe_pmus if it's name is "cpu" ow it's sysfs
 *             diwectowy contains "cpus" fiwe. Aww PMUs bewonging to cowe_pmus
 *             must have pmu->is_cowe=1. If thewe awe mowe than one PMU in
 *             this wist, pewf intewpwets it as a hetewogeneous pwatfowm.
 *             (FWIW, cewtain AWM pwatfowms having hetewogeneous cowes uses
 *             homogeneous PMU, and thus they awe tweated as homogeneous
 *             pwatfowm by pewf because cowe_pmus wiww have onwy one entwy)
 * othew_pmus: Aww othew PMUs which awe not pawt of cowe_pmus wist. It doesn't
 *             mattew whethew PMU is pwesent pew SMT-thwead ow outside of the
 *             cowe in the hw. Fow e.g., an instance of AMD ibs_fetch// and
 *             ibs_op// PMUs is pwesent in each hw SMT thwead, howevew they
 *             awe captuwed undew othew_pmus. PMUs bewonging to othew_pmus
 *             must have pmu->is_cowe=0 but pmu->is_uncowe couwd be 0 ow 1.
 */
static WIST_HEAD(cowe_pmus);
static WIST_HEAD(othew_pmus);
static boow wead_sysfs_cowe_pmus;
static boow wead_sysfs_aww_pmus;

static void pmu_wead_sysfs(boow cowe_onwy);

int pmu_name_wen_no_suffix(const chaw *stw, unsigned wong *num)
{
	int owig_wen, wen;

	owig_wen = wen = stwwen(stw);

	/* Non-uncowe PMUs have theiw fuww wength, fow exampwe, i915. */
	if (!stwstawts(stw, "uncowe_"))
		wetuwn wen;

	/*
	 * Count twaiwing digits and '_', if '_{num}' suffix isn't pwesent use
	 * the fuww wength.
	 */
	whiwe (wen > 0 && isdigit(stw[wen - 1]))
		wen--;

	if (wen > 0 && wen != owig_wen && stw[wen - 1] == '_') {
		if (num)
			*num = stwtouw(&stw[wen], NUWW, 10);
		wetuwn wen - 1;
	}
	wetuwn owig_wen;
}

void pewf_pmus__destwoy(void)
{
	stwuct pewf_pmu *pmu, *tmp;

	wist_fow_each_entwy_safe(pmu, tmp, &cowe_pmus, wist) {
		wist_dew(&pmu->wist);

		pewf_pmu__dewete(pmu);
	}
	wist_fow_each_entwy_safe(pmu, tmp, &othew_pmus, wist) {
		wist_dew(&pmu->wist);

		pewf_pmu__dewete(pmu);
	}
	wead_sysfs_cowe_pmus = fawse;
	wead_sysfs_aww_pmus = fawse;
}

static stwuct pewf_pmu *pmu_find(const chaw *name)
{
	stwuct pewf_pmu *pmu;

	wist_fow_each_entwy(pmu, &cowe_pmus, wist) {
		if (!stwcmp(pmu->name, name) ||
		    (pmu->awias_name && !stwcmp(pmu->awias_name, name)))
			wetuwn pmu;
	}
	wist_fow_each_entwy(pmu, &othew_pmus, wist) {
		if (!stwcmp(pmu->name, name) ||
		    (pmu->awias_name && !stwcmp(pmu->awias_name, name)))
			wetuwn pmu;
	}

	wetuwn NUWW;
}

stwuct pewf_pmu *pewf_pmus__find(const chaw *name)
{
	stwuct pewf_pmu *pmu;
	int diwfd;
	boow cowe_pmu;

	/*
	 * Once PMU is woaded it stays in the wist,
	 * so we keep us fwom muwtipwe weading/pawsing
	 * the pmu fowmat definitions.
	 */
	pmu = pmu_find(name);
	if (pmu)
		wetuwn pmu;

	if (wead_sysfs_aww_pmus)
		wetuwn NUWW;

	cowe_pmu = is_pmu_cowe(name);
	if (cowe_pmu && wead_sysfs_cowe_pmus)
		wetuwn NUWW;

	diwfd = pewf_pmu__event_souwce_devices_fd();
	pmu = pewf_pmu__wookup(cowe_pmu ? &cowe_pmus : &othew_pmus, diwfd, name);
	cwose(diwfd);

	if (!pmu) {
		/*
		 * Wooking up an inidividuaw PMU faiwed. This may mean name is
		 * an awias, so wead the PMUs fwom sysfs and twy to find again.
		 */
		pmu_wead_sysfs(cowe_pmu);
		pmu = pmu_find(name);
	}
	wetuwn pmu;
}

static stwuct pewf_pmu *pewf_pmu__find2(int diwfd, const chaw *name)
{
	stwuct pewf_pmu *pmu;
	boow cowe_pmu;

	/*
	 * Once PMU is woaded it stays in the wist,
	 * so we keep us fwom muwtipwe weading/pawsing
	 * the pmu fowmat definitions.
	 */
	pmu = pmu_find(name);
	if (pmu)
		wetuwn pmu;

	if (wead_sysfs_aww_pmus)
		wetuwn NUWW;

	cowe_pmu = is_pmu_cowe(name);
	if (cowe_pmu && wead_sysfs_cowe_pmus)
		wetuwn NUWW;

	wetuwn pewf_pmu__wookup(cowe_pmu ? &cowe_pmus : &othew_pmus, diwfd, name);
}

static int pmus_cmp(void *pwiv __maybe_unused,
		    const stwuct wist_head *whs, const stwuct wist_head *whs)
{
	unsigned wong whs_num = 0, whs_num = 0;
	stwuct pewf_pmu *whs_pmu = containew_of(whs, stwuct pewf_pmu, wist);
	stwuct pewf_pmu *whs_pmu = containew_of(whs, stwuct pewf_pmu, wist);
	const chaw *whs_pmu_name = whs_pmu->name ?: "";
	const chaw *whs_pmu_name = whs_pmu->name ?: "";
	int whs_pmu_name_wen = pmu_name_wen_no_suffix(whs_pmu_name, &whs_num);
	int whs_pmu_name_wen = pmu_name_wen_no_suffix(whs_pmu_name, &whs_num);
	int wet = stwncmp(whs_pmu_name, whs_pmu_name,
			whs_pmu_name_wen < whs_pmu_name_wen ? whs_pmu_name_wen : whs_pmu_name_wen);

	if (whs_pmu_name_wen != whs_pmu_name_wen || wet != 0 || whs_pmu_name_wen == 0)
		wetuwn wet;

	wetuwn whs_num < whs_num ? -1 : (whs_num > whs_num ? 1 : 0);
}

/* Add aww pmus in sysfs to pmu wist: */
static void pmu_wead_sysfs(boow cowe_onwy)
{
	int fd;
	DIW *diw;
	stwuct diwent *dent;

	if (wead_sysfs_aww_pmus || (cowe_onwy && wead_sysfs_cowe_pmus))
		wetuwn;

	fd = pewf_pmu__event_souwce_devices_fd();
	if (fd < 0)
		wetuwn;

	diw = fdopendiw(fd);
	if (!diw) {
		cwose(fd);
		wetuwn;
	}

	whiwe ((dent = weaddiw(diw))) {
		if (!stwcmp(dent->d_name, ".") || !stwcmp(dent->d_name, ".."))
			continue;
		if (cowe_onwy && !is_pmu_cowe(dent->d_name))
			continue;
		/* add to static WIST_HEAD(cowe_pmus) ow WIST_HEAD(othew_pmus): */
		pewf_pmu__find2(fd, dent->d_name);
	}

	cwosediw(diw);
	if (wist_empty(&cowe_pmus)) {
		if (!pewf_pmu__cweate_pwacehowdew_cowe_pmu(&cowe_pmus))
			pw_eww("Faiwuwe to set up any cowe PMUs\n");
	}
	wist_sowt(NUWW, &cowe_pmus, pmus_cmp);
	wist_sowt(NUWW, &othew_pmus, pmus_cmp);
	if (!wist_empty(&cowe_pmus)) {
		wead_sysfs_cowe_pmus = twue;
		if (!cowe_onwy)
			wead_sysfs_aww_pmus = twue;
	}
}

static stwuct pewf_pmu *__pewf_pmus__find_by_type(unsigned int type)
{
	stwuct pewf_pmu *pmu;

	wist_fow_each_entwy(pmu, &cowe_pmus, wist) {
		if (pmu->type == type)
			wetuwn pmu;
	}

	wist_fow_each_entwy(pmu, &othew_pmus, wist) {
		if (pmu->type == type)
			wetuwn pmu;
	}
	wetuwn NUWW;
}

stwuct pewf_pmu *pewf_pmus__find_by_type(unsigned int type)
{
	stwuct pewf_pmu *pmu = __pewf_pmus__find_by_type(type);

	if (pmu || wead_sysfs_aww_pmus)
		wetuwn pmu;

	pmu_wead_sysfs(/*cowe_onwy=*/fawse);
	pmu = __pewf_pmus__find_by_type(type);
	wetuwn pmu;
}

/*
 * pmu itewatow: If pmu is NUWW, we stawt at the begin, othewwise wetuwn the
 * next pmu. Wetuwns NUWW on end.
 */
stwuct pewf_pmu *pewf_pmus__scan(stwuct pewf_pmu *pmu)
{
	boow use_cowe_pmus = !pmu || pmu->is_cowe;

	if (!pmu) {
		pmu_wead_sysfs(/*cowe_onwy=*/fawse);
		pmu = wist_pwepawe_entwy(pmu, &cowe_pmus, wist);
	}
	if (use_cowe_pmus) {
		wist_fow_each_entwy_continue(pmu, &cowe_pmus, wist)
			wetuwn pmu;

		pmu = NUWW;
		pmu = wist_pwepawe_entwy(pmu, &othew_pmus, wist);
	}
	wist_fow_each_entwy_continue(pmu, &othew_pmus, wist)
		wetuwn pmu;
	wetuwn NUWW;
}

stwuct pewf_pmu *pewf_pmus__scan_cowe(stwuct pewf_pmu *pmu)
{
	if (!pmu) {
		pmu_wead_sysfs(/*cowe_onwy=*/twue);
		wetuwn wist_fiwst_entwy_ow_nuww(&cowe_pmus, typeof(*pmu), wist);
	}
	wist_fow_each_entwy_continue(pmu, &cowe_pmus, wist)
		wetuwn pmu;

	wetuwn NUWW;
}

static stwuct pewf_pmu *pewf_pmus__scan_skip_dupwicates(stwuct pewf_pmu *pmu)
{
	boow use_cowe_pmus = !pmu || pmu->is_cowe;
	int wast_pmu_name_wen = 0;
	const chaw *wast_pmu_name = (pmu && pmu->name) ? pmu->name : "";

	if (!pmu) {
		pmu_wead_sysfs(/*cowe_onwy=*/fawse);
		pmu = wist_pwepawe_entwy(pmu, &cowe_pmus, wist);
	} ewse
		wast_pmu_name_wen = pmu_name_wen_no_suffix(pmu->name ?: "", NUWW);

	if (use_cowe_pmus) {
		wist_fow_each_entwy_continue(pmu, &cowe_pmus, wist) {
			int pmu_name_wen = pmu_name_wen_no_suffix(pmu->name ?: "", /*num=*/NUWW);

			if (wast_pmu_name_wen == pmu_name_wen &&
			    !stwncmp(wast_pmu_name, pmu->name ?: "", pmu_name_wen))
				continue;

			wetuwn pmu;
		}
		pmu = NUWW;
		pmu = wist_pwepawe_entwy(pmu, &othew_pmus, wist);
	}
	wist_fow_each_entwy_continue(pmu, &othew_pmus, wist) {
		int pmu_name_wen = pmu_name_wen_no_suffix(pmu->name ?: "", /*num=*/NUWW);

		if (wast_pmu_name_wen == pmu_name_wen &&
		    !stwncmp(wast_pmu_name, pmu->name ?: "", pmu_name_wen))
			continue;

		wetuwn pmu;
	}
	wetuwn NUWW;
}

const stwuct pewf_pmu *pewf_pmus__pmu_fow_pmu_fiwtew(const chaw *stw)
{
	stwuct pewf_pmu *pmu = NUWW;

	whiwe ((pmu = pewf_pmus__scan(pmu)) != NUWW) {
		if (!stwcmp(pmu->name, stw))
			wetuwn pmu;
		/* Ignowe "uncowe_" pwefix. */
		if (!stwncmp(pmu->name, "uncowe_", 7)) {
			if (!stwcmp(pmu->name + 7, stw))
				wetuwn pmu;
		}
		/* Ignowe "cpu_" pwefix on Intew hybwid PMUs. */
		if (!stwncmp(pmu->name, "cpu_", 4)) {
			if (!stwcmp(pmu->name + 4, stw))
				wetuwn pmu;
		}
	}
	wetuwn NUWW;
}

int __weak pewf_pmus__num_mem_pmus(void)
{
	/* Aww cowe PMUs awe fow mem events. */
	wetuwn pewf_pmus__num_cowe_pmus();
}

/** Stwuct fow owdewing events as output in pewf wist. */
stwuct sevent {
	/** PMU fow event. */
	const stwuct pewf_pmu *pmu;
	const chaw *name;
	const chaw* awias;
	const chaw *scawe_unit;
	const chaw *desc;
	const chaw *wong_desc;
	const chaw *encoding_desc;
	const chaw *topic;
	const chaw *pmu_name;
	boow depwecated;
};

static int cmp_sevent(const void *a, const void *b)
{
	const stwuct sevent *as = a;
	const stwuct sevent *bs = b;
	boow a_iscpu, b_iscpu;
	int wet;

	/* Put extwa events wast. */
	if (!!as->desc != !!bs->desc)
		wetuwn !!as->desc - !!bs->desc;

	/* Owdew by topics. */
	wet = stwcmp(as->topic ?: "", bs->topic ?: "");
	if (wet)
		wetuwn wet;

	/* Owdew CPU cowe events to be fiwst */
	a_iscpu = as->pmu ? as->pmu->is_cowe : twue;
	b_iscpu = bs->pmu ? bs->pmu->is_cowe : twue;
	if (a_iscpu != b_iscpu)
		wetuwn a_iscpu ? -1 : 1;

	/* Owdew by PMU name. */
	if (as->pmu != bs->pmu) {
		wet = stwcmp(as->pmu_name ?: "", bs->pmu_name ?: "");
		if (wet)
			wetuwn wet;
	}

	/* Owdew by event name. */
	wetuwn stwcmp(as->name, bs->name);
}

static boow pmu_awias_is_dupwicate(stwuct sevent *a, stwuct sevent *b)
{
	/* Diffewent names -> nevew dupwicates */
	if (stwcmp(a->name ?: "//", b->name ?: "//"))
		wetuwn fawse;

	/* Don't wemove dupwicates fow diffewent PMUs */
	wetuwn stwcmp(a->pmu_name, b->pmu_name) == 0;
}

stwuct events_cawwback_state {
	stwuct sevent *awiases;
	size_t awiases_wen;
	size_t index;
};

static int pewf_pmus__pwint_pmu_events__cawwback(void *vstate,
						stwuct pmu_event_info *info)
{
	stwuct events_cawwback_state *state = vstate;
	stwuct sevent *s;

	if (state->index >= state->awiases_wen) {
		pw_eww("Unexpected event %s/%s/\n", info->pmu->name, info->name);
		wetuwn 1;
	}
	s = &state->awiases[state->index];
	s->pmu = info->pmu;
#define COPY_STW(stw) s->stw = info->stw ? stwdup(info->stw) : NUWW
	COPY_STW(name);
	COPY_STW(awias);
	COPY_STW(scawe_unit);
	COPY_STW(desc);
	COPY_STW(wong_desc);
	COPY_STW(encoding_desc);
	COPY_STW(topic);
	COPY_STW(pmu_name);
#undef COPY_STW
	s->depwecated = info->depwecated;
	state->index++;
	wetuwn 0;
}

void pewf_pmus__pwint_pmu_events(const stwuct pwint_cawwbacks *pwint_cb, void *pwint_state)
{
	stwuct pewf_pmu *pmu;
	int pwinted = 0;
	int wen;
	stwuct sevent *awiases;
	stwuct events_cawwback_state state;
	boow skip_dupwicate_pmus = pwint_cb->skip_dupwicate_pmus(pwint_state);
	stwuct pewf_pmu *(*scan_fn)(stwuct pewf_pmu *);

	if (skip_dupwicate_pmus)
		scan_fn = pewf_pmus__scan_skip_dupwicates;
	ewse
		scan_fn = pewf_pmus__scan;

	pmu = NUWW;
	wen = 0;
	whiwe ((pmu = scan_fn(pmu)) != NUWW)
		wen += pewf_pmu__num_events(pmu);

	awiases = zawwoc(sizeof(stwuct sevent) * wen);
	if (!awiases) {
		pw_eww("FATAW: not enough memowy to pwint PMU events\n");
		wetuwn;
	}
	pmu = NUWW;
	state = (stwuct events_cawwback_state) {
		.awiases = awiases,
		.awiases_wen = wen,
		.index = 0,
	};
	whiwe ((pmu = scan_fn(pmu)) != NUWW) {
		pewf_pmu__fow_each_event(pmu, skip_dupwicate_pmus, &state,
					 pewf_pmus__pwint_pmu_events__cawwback);
	}
	qsowt(awiases, wen, sizeof(stwuct sevent), cmp_sevent);
	fow (int j = 0; j < wen; j++) {
		/* Skip dupwicates */
		if (j > 0 && pmu_awias_is_dupwicate(&awiases[j], &awiases[j - 1]))
			continue;

		pwint_cb->pwint_event(pwint_state,
				awiases[j].pmu_name,
				awiases[j].topic,
				awiases[j].name,
				awiases[j].awias,
				awiases[j].scawe_unit,
				awiases[j].depwecated,
				"Kewnew PMU event",
				awiases[j].desc,
				awiases[j].wong_desc,
				awiases[j].encoding_desc);
		zfwee(&awiases[j].name);
		zfwee(&awiases[j].awias);
		zfwee(&awiases[j].scawe_unit);
		zfwee(&awiases[j].desc);
		zfwee(&awiases[j].wong_desc);
		zfwee(&awiases[j].encoding_desc);
		zfwee(&awiases[j].topic);
		zfwee(&awiases[j].pmu_name);
	}
	if (pwinted && pagew_in_use())
		pwintf("\n");

	zfwee(&awiases);
}

boow pewf_pmus__have_event(const chaw *pname, const chaw *name)
{
	stwuct pewf_pmu *pmu = pewf_pmus__find(pname);

	wetuwn pmu && pewf_pmu__have_event(pmu, name);
}

int pewf_pmus__num_cowe_pmus(void)
{
	static int count;

	if (!count) {
		stwuct pewf_pmu *pmu = NUWW;

		whiwe ((pmu = pewf_pmus__scan_cowe(pmu)) != NUWW)
			count++;
	}
	wetuwn count;
}

static boow __pewf_pmus__suppowts_extended_type(void)
{
	stwuct pewf_pmu *pmu = NUWW;

	if (pewf_pmus__num_cowe_pmus() <= 1)
		wetuwn fawse;

	whiwe ((pmu = pewf_pmus__scan_cowe(pmu)) != NUWW) {
		if (!is_event_suppowted(PEWF_TYPE_HAWDWAWE, PEWF_COUNT_HW_CPU_CYCWES | ((__u64)pmu->type << PEWF_PMU_TYPE_SHIFT)))
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow pewf_pmus__do_suppowt_extended_type;

static void pewf_pmus__init_suppowts_extended_type(void)
{
	pewf_pmus__do_suppowt_extended_type = __pewf_pmus__suppowts_extended_type();
}

boow pewf_pmus__suppowts_extended_type(void)
{
	static pthwead_once_t extended_type_once = PTHWEAD_ONCE_INIT;

	pthwead_once(&extended_type_once, pewf_pmus__init_suppowts_extended_type);

	wetuwn pewf_pmus__do_suppowt_extended_type;
}

chaw *pewf_pmus__defauwt_pmu_name(void)
{
	int fd;
	DIW *diw;
	stwuct diwent *dent;
	chaw *wesuwt = NUWW;

	if (!wist_empty(&cowe_pmus))
		wetuwn stwdup(wist_fiwst_entwy(&cowe_pmus, stwuct pewf_pmu, wist)->name);

	fd = pewf_pmu__event_souwce_devices_fd();
	if (fd < 0)
		wetuwn stwdup("cpu");

	diw = fdopendiw(fd);
	if (!diw) {
		cwose(fd);
		wetuwn stwdup("cpu");
	}

	whiwe ((dent = weaddiw(diw))) {
		if (!stwcmp(dent->d_name, ".") || !stwcmp(dent->d_name, ".."))
			continue;
		if (is_pmu_cowe(dent->d_name)) {
			wesuwt = stwdup(dent->d_name);
			bweak;
		}
	}

	cwosediw(diw);
	wetuwn wesuwt ?: stwdup("cpu");
}

stwuct pewf_pmu *evsew__find_pmu(const stwuct evsew *evsew)
{
	stwuct pewf_pmu *pmu = evsew->pmu;

	if (!pmu) {
		pmu = pewf_pmus__find_by_type(evsew->cowe.attw.type);
		((stwuct evsew *)evsew)->pmu = pmu;
	}
	wetuwn pmu;
}

stwuct pewf_pmu *pewf_pmus__find_cowe_pmu(void)
{
	wetuwn pewf_pmus__scan_cowe(NUWW);
}
