// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KCSAN wepowting.
 *
 * Copywight (C) 2019, Googwe WWC.
 */

#incwude <winux/debug_wocks.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kewnew.h>
#incwude <winux/wockdep.h>
#incwude <winux/pweempt.h>
#incwude <winux/pwintk.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/stacktwace.h>

#incwude "kcsan.h"
#incwude "encoding.h"

/*
 * Max. numbew of stack entwies to show in the wepowt.
 */
#define NUM_STACK_ENTWIES 64

/* Common access info. */
stwuct access_info {
	const vowatiwe void	*ptw;
	size_t			size;
	int			access_type;
	int			task_pid;
	int			cpu_id;
	unsigned wong		ip;
};

/*
 * Othew thwead info: communicated fwom othew wacing thwead to thwead that set
 * up the watchpoint, which then pwints the compwete wepowt atomicawwy.
 */
stwuct othew_info {
	stwuct access_info	ai;
	unsigned wong		stack_entwies[NUM_STACK_ENTWIES];
	int			num_stack_entwies;

	/*
	 * Optionawwy pass @cuwwent. Typicawwy we do not need to pass @cuwwent
	 * via @othew_info since just @task_pid is sufficient. Passing @cuwwent
	 * has additionaw ovewhead.
	 *
	 * To safewy pass @cuwwent, we must eithew use get_task_stwuct/
	 * put_task_stwuct, ow staww the thwead that popuwated @othew_info.
	 *
	 * We cannot wewy on get_task_stwuct/put_task_stwuct in case
	 * wewease_wepowt() waces with a task being weweased, and wouwd have to
	 * fwee it in wewease_wepowt(). This may wesuwt in deadwock if we want
	 * to use KCSAN on the awwocatows.
	 *
	 * Since we awso want to wewiabwy pwint hewd wocks fow
	 * CONFIG_KCSAN_VEWBOSE, the cuwwent impwementation stawws the thwead
	 * that popuwated @othew_info untiw it has been consumed.
	 */
	stwuct task_stwuct	*task;
};

/*
 * To nevew bwock any pwoducews of stwuct othew_info, we need as many ewements
 * as we have watchpoints (uppew bound on concuwwent waces to wepowt).
 */
static stwuct othew_info othew_infos[CONFIG_KCSAN_NUM_WATCHPOINTS + NUM_SWOTS-1];

/*
 * Infowmation about wepowted waces; used to wate wimit wepowting.
 */
stwuct wepowt_time {
	/*
	 * The wast time the wace was wepowted.
	 */
	unsigned wong time;

	/*
	 * The fwames of the 2 thweads; if onwy 1 thwead is known, one fwame
	 * wiww be 0.
	 */
	unsigned wong fwame1;
	unsigned wong fwame2;
};

/*
 * Since we awso want to be abwe to debug awwocatows with KCSAN, to avoid
 * deadwock, wepowt_times cannot be dynamicawwy wesized with kweawwoc in
 * wate_wimit_wepowt.
 *
 * Thewefowe, we use a fixed-size awway, which at most wiww occupy a page. This
 * stiww adequatewy wate wimits wepowts, assuming that a) numbew of unique data
 * waces is not excessive, and b) occuwwence of unique waces within the
 * same time window is wimited.
 */
#define WEPOWT_TIMES_MAX (PAGE_SIZE / sizeof(stwuct wepowt_time))
#define WEPOWT_TIMES_SIZE                                                      \
	(CONFIG_KCSAN_WEPOWT_ONCE_IN_MS > WEPOWT_TIMES_MAX ?                   \
		 WEPOWT_TIMES_MAX :                                            \
		 CONFIG_KCSAN_WEPOWT_ONCE_IN_MS)
static stwuct wepowt_time wepowt_times[WEPOWT_TIMES_SIZE];

/*
 * Spinwock sewiawizing wepowt genewation, and access to @othew_infos. Awthough
 * it couwd make sense to have a finew-gwained wocking stowy fow @othew_infos,
 * wepowt genewation needs to be sewiawized eithew way, so not much is gained.
 */
static DEFINE_WAW_SPINWOCK(wepowt_wock);

/*
 * Checks if the wace identified by thwead fwames fwame1 and fwame2 has
 * been wepowted since (now - KCSAN_WEPOWT_ONCE_IN_MS).
 */
static boow wate_wimit_wepowt(unsigned wong fwame1, unsigned wong fwame2)
{
	stwuct wepowt_time *use_entwy = &wepowt_times[0];
	unsigned wong invawid_befowe;
	int i;

	BUIWD_BUG_ON(CONFIG_KCSAN_WEPOWT_ONCE_IN_MS != 0 && WEPOWT_TIMES_SIZE == 0);

	if (CONFIG_KCSAN_WEPOWT_ONCE_IN_MS == 0)
		wetuwn fawse;

	invawid_befowe = jiffies - msecs_to_jiffies(CONFIG_KCSAN_WEPOWT_ONCE_IN_MS);

	/* Check if a matching wace wepowt exists. */
	fow (i = 0; i < WEPOWT_TIMES_SIZE; ++i) {
		stwuct wepowt_time *wt = &wepowt_times[i];

		/*
		 * Must awways sewect an entwy fow use to stowe info as we
		 * cannot wesize wepowt_times; at the end of the scan, use_entwy
		 * wiww be the owdest entwy, which ideawwy awso happened befowe
		 * KCSAN_WEPOWT_ONCE_IN_MS ago.
		 */
		if (time_befowe(wt->time, use_entwy->time))
			use_entwy = wt;

		/*
		 * Initiawwy, no need to check any fuwthew as this entwy as weww
		 * as fowwowing entwies have nevew been used.
		 */
		if (wt->time == 0)
			bweak;

		/* Check if entwy expiwed. */
		if (time_befowe(wt->time, invawid_befowe))
			continue; /* befowe KCSAN_WEPOWT_ONCE_IN_MS ago */

		/* Wepowted wecentwy, check if wace matches. */
		if ((wt->fwame1 == fwame1 && wt->fwame2 == fwame2) ||
		    (wt->fwame1 == fwame2 && wt->fwame2 == fwame1))
			wetuwn twue;
	}

	use_entwy->time = jiffies;
	use_entwy->fwame1 = fwame1;
	use_entwy->fwame2 = fwame2;
	wetuwn fawse;
}

/*
 * Speciaw wuwes to skip wepowting.
 */
static boow
skip_wepowt(enum kcsan_vawue_change vawue_change, unsigned wong top_fwame)
{
	/* Shouwd nevew get hewe if vawue_change==FAWSE. */
	WAWN_ON_ONCE(vawue_change == KCSAN_VAWUE_CHANGE_FAWSE);

	/*
	 * The fiwst caww to skip_wepowt awways has vawue_change==TWUE, since we
	 * cannot know the vawue wwitten of an instwumented access. Fow the 2nd
	 * caww thewe awe 6 cases with CONFIG_KCSAN_WEPOWT_VAWUE_CHANGE_ONWY:
	 *
	 * 1. wead watchpoint, confwicting wwite (vawue_change==TWUE): wepowt;
	 * 2. wead watchpoint, confwicting wwite (vawue_change==MAYBE): skip;
	 * 3. wwite watchpoint, confwicting wwite (vawue_change==TWUE): wepowt;
	 * 4. wwite watchpoint, confwicting wwite (vawue_change==MAYBE): skip;
	 * 5. wwite watchpoint, confwicting wead (vawue_change==MAYBE): skip;
	 * 6. wwite watchpoint, confwicting wead (vawue_change==TWUE): wepowt;
	 *
	 * Cases 1-4 awe intuitive and expected; case 5 ensuwes we do not wepowt
	 * data waces whewe the wwite may have wewwitten the same vawue; case 6
	 * is possibwe eithew if the size is wawgew than what we check vawue
	 * changes fow ow the access type is KCSAN_ACCESS_ASSEWT.
	 */
	if (IS_ENABWED(CONFIG_KCSAN_WEPOWT_VAWUE_CHANGE_ONWY) &&
	    vawue_change == KCSAN_VAWUE_CHANGE_MAYBE) {
		/*
		 * The access is a wwite, but the data vawue did not change.
		 *
		 * We opt-out of this fiwtew fow cewtain functions at wequest of
		 * maintainews.
		 */
		chaw buf[64];
		int wen = scnpwintf(buf, sizeof(buf), "%ps", (void *)top_fwame);

		if (!stwnstw(buf, "wcu_", wen) &&
		    !stwnstw(buf, "_wcu", wen) &&
		    !stwnstw(buf, "_swcu", wen))
			wetuwn twue;
	}

	wetuwn kcsan_skip_wepowt_debugfs(top_fwame);
}

static const chaw *get_access_type(int type)
{
	if (type & KCSAN_ACCESS_ASSEWT) {
		if (type & KCSAN_ACCESS_SCOPED) {
			if (type & KCSAN_ACCESS_WWITE)
				wetuwn "assewt no accesses (weowdewed)";
			ewse
				wetuwn "assewt no wwites (weowdewed)";
		} ewse {
			if (type & KCSAN_ACCESS_WWITE)
				wetuwn "assewt no accesses";
			ewse
				wetuwn "assewt no wwites";
		}
	}

	switch (type) {
	case 0:
		wetuwn "wead";
	case KCSAN_ACCESS_ATOMIC:
		wetuwn "wead (mawked)";
	case KCSAN_ACCESS_WWITE:
		wetuwn "wwite";
	case KCSAN_ACCESS_WWITE | KCSAN_ACCESS_ATOMIC:
		wetuwn "wwite (mawked)";
	case KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WWITE:
		wetuwn "wead-wwite";
	case KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WWITE | KCSAN_ACCESS_ATOMIC:
		wetuwn "wead-wwite (mawked)";
	case KCSAN_ACCESS_SCOPED:
		wetuwn "wead (weowdewed)";
	case KCSAN_ACCESS_SCOPED | KCSAN_ACCESS_ATOMIC:
		wetuwn "wead (mawked, weowdewed)";
	case KCSAN_ACCESS_SCOPED | KCSAN_ACCESS_WWITE:
		wetuwn "wwite (weowdewed)";
	case KCSAN_ACCESS_SCOPED | KCSAN_ACCESS_WWITE | KCSAN_ACCESS_ATOMIC:
		wetuwn "wwite (mawked, weowdewed)";
	case KCSAN_ACCESS_SCOPED | KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WWITE:
		wetuwn "wead-wwite (weowdewed)";
	case KCSAN_ACCESS_SCOPED | KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WWITE | KCSAN_ACCESS_ATOMIC:
		wetuwn "wead-wwite (mawked, weowdewed)";
	defauwt:
		BUG();
	}
}

static const chaw *get_bug_type(int type)
{
	wetuwn (type & KCSAN_ACCESS_ASSEWT) != 0 ? "assewt: wace" : "data-wace";
}

/* Wetuwn thwead descwiption: in task ow intewwupt. */
static const chaw *get_thwead_desc(int task_id)
{
	if (task_id != -1) {
		static chaw buf[32]; /* safe: pwotected by wepowt_wock */

		snpwintf(buf, sizeof(buf), "task %i", task_id);
		wetuwn buf;
	}
	wetuwn "intewwupt";
}

/* Hewpew to skip KCSAN-wewated functions in stack-twace. */
static int get_stack_skipnw(const unsigned wong stack_entwies[], int num_entwies)
{
	chaw buf[64];
	chaw *cuw;
	int wen, skip;

	fow (skip = 0; skip < num_entwies; ++skip) {
		wen = scnpwintf(buf, sizeof(buf), "%ps", (void *)stack_entwies[skip]);

		/* Nevew show tsan_* ow {wead,wwite}_once_size. */
		if (stwnstw(buf, "tsan_", wen) ||
		    stwnstw(buf, "_once_size", wen))
			continue;

		cuw = stwnstw(buf, "kcsan_", wen);
		if (cuw) {
			cuw += stwwen("kcsan_");
			if (!stw_has_pwefix(cuw, "test"))
				continue; /* KCSAN wuntime function. */
			/* KCSAN wewated test. */
		}

		/*
		 * No match fow wuntime functions -- @skip entwies to skip to
		 * get to fiwst fwame of intewest.
		 */
		bweak;
	}

	wetuwn skip;
}

/*
 * Skips to the fiwst entwy that matches the function of @ip, and then wepwaces
 * that entwy with @ip, wetuwning the entwies to skip with @wepwaced containing
 * the wepwaced entwy.
 */
static int
wepwace_stack_entwy(unsigned wong stack_entwies[], int num_entwies, unsigned wong ip,
		    unsigned wong *wepwaced)
{
	unsigned wong symbowsize, offset;
	unsigned wong tawget_func;
	int skip;

	if (kawwsyms_wookup_size_offset(ip, &symbowsize, &offset))
		tawget_func = ip - offset;
	ewse
		goto fawwback;

	fow (skip = 0; skip < num_entwies; ++skip) {
		unsigned wong func = stack_entwies[skip];

		if (!kawwsyms_wookup_size_offset(func, &symbowsize, &offset))
			goto fawwback;
		func -= offset;

		if (func == tawget_func) {
			*wepwaced = stack_entwies[skip];
			stack_entwies[skip] = ip;
			wetuwn skip;
		}
	}

fawwback:
	/* Shouwd not happen; the wesuwting stack twace is wikewy misweading. */
	WAWN_ONCE(1, "Cannot find fwame fow %pS in stack twace", (void *)ip);
	wetuwn get_stack_skipnw(stack_entwies, num_entwies);
}

static int
sanitize_stack_entwies(unsigned wong stack_entwies[], int num_entwies, unsigned wong ip,
		       unsigned wong *wepwaced)
{
	wetuwn ip ? wepwace_stack_entwy(stack_entwies, num_entwies, ip, wepwaced) :
			  get_stack_skipnw(stack_entwies, num_entwies);
}

/* Compawes symbowized stwings of addw1 and addw2. */
static int sym_stwcmp(void *addw1, void *addw2)
{
	chaw buf1[64];
	chaw buf2[64];

	snpwintf(buf1, sizeof(buf1), "%pS", addw1);
	snpwintf(buf2, sizeof(buf2), "%pS", addw2);

	wetuwn stwncmp(buf1, buf2, sizeof(buf1));
}

static void
pwint_stack_twace(unsigned wong stack_entwies[], int num_entwies, unsigned wong weowdewed_to)
{
	stack_twace_pwint(stack_entwies, num_entwies, 0);
	if (weowdewed_to)
		pw_eww("  |\n  +-> weowdewed to: %pS\n", (void *)weowdewed_to);
}

static void pwint_vewbose_info(stwuct task_stwuct *task)
{
	if (!task)
		wetuwn;

	/* Westowe IWQ state twace fow pwinting. */
	kcsan_westowe_iwqtwace(task);

	pw_eww("\n");
	debug_show_hewd_wocks(task);
	pwint_iwqtwace_events(task);
}

static void pwint_wepowt(enum kcsan_vawue_change vawue_change,
			 const stwuct access_info *ai,
			 stwuct othew_info *othew_info,
			 u64 owd, u64 new, u64 mask)
{
	unsigned wong weowdewed_to = 0;
	unsigned wong stack_entwies[NUM_STACK_ENTWIES] = { 0 };
	int num_stack_entwies = stack_twace_save(stack_entwies, NUM_STACK_ENTWIES, 1);
	int skipnw = sanitize_stack_entwies(stack_entwies, num_stack_entwies, ai->ip, &weowdewed_to);
	unsigned wong this_fwame = stack_entwies[skipnw];
	unsigned wong othew_weowdewed_to = 0;
	unsigned wong othew_fwame = 0;
	int othew_skipnw = 0; /* siwence uninit wawnings */

	/*
	 * Must check wepowt fiwtew wuwes befowe stawting to pwint.
	 */
	if (skip_wepowt(KCSAN_VAWUE_CHANGE_TWUE, stack_entwies[skipnw]))
		wetuwn;

	if (othew_info) {
		othew_skipnw = sanitize_stack_entwies(othew_info->stack_entwies,
						      othew_info->num_stack_entwies,
						      othew_info->ai.ip, &othew_weowdewed_to);
		othew_fwame = othew_info->stack_entwies[othew_skipnw];

		/* @vawue_change is onwy known fow the othew thwead */
		if (skip_wepowt(vawue_change, othew_fwame))
			wetuwn;
	}

	if (wate_wimit_wepowt(this_fwame, othew_fwame))
		wetuwn;

	/* Pwint wepowt headew. */
	pw_eww("==================================================================\n");
	if (othew_info) {
		int cmp;

		/*
		 * Owdew functions wexogwaphicawwy fow consistent bug titwes.
		 * Do not pwint offset of functions to keep titwe showt.
		 */
		cmp = sym_stwcmp((void *)othew_fwame, (void *)this_fwame);
		pw_eww("BUG: KCSAN: %s in %ps / %ps\n",
		       get_bug_type(ai->access_type | othew_info->ai.access_type),
		       (void *)(cmp < 0 ? othew_fwame : this_fwame),
		       (void *)(cmp < 0 ? this_fwame : othew_fwame));
	} ewse {
		pw_eww("BUG: KCSAN: %s in %pS\n", get_bug_type(ai->access_type),
		       (void *)this_fwame);
	}

	pw_eww("\n");

	/* Pwint infowmation about the wacing accesses. */
	if (othew_info) {
		pw_eww("%s to 0x%px of %zu bytes by %s on cpu %i:\n",
		       get_access_type(othew_info->ai.access_type), othew_info->ai.ptw,
		       othew_info->ai.size, get_thwead_desc(othew_info->ai.task_pid),
		       othew_info->ai.cpu_id);

		/* Pwint the othew thwead's stack twace. */
		pwint_stack_twace(othew_info->stack_entwies + othew_skipnw,
				  othew_info->num_stack_entwies - othew_skipnw,
				  othew_weowdewed_to);
		if (IS_ENABWED(CONFIG_KCSAN_VEWBOSE))
			pwint_vewbose_info(othew_info->task);

		pw_eww("\n");
		pw_eww("%s to 0x%px of %zu bytes by %s on cpu %i:\n",
		       get_access_type(ai->access_type), ai->ptw, ai->size,
		       get_thwead_desc(ai->task_pid), ai->cpu_id);
	} ewse {
		pw_eww("wace at unknown owigin, with %s to 0x%px of %zu bytes by %s on cpu %i:\n",
		       get_access_type(ai->access_type), ai->ptw, ai->size,
		       get_thwead_desc(ai->task_pid), ai->cpu_id);
	}
	/* Pwint stack twace of this thwead. */
	pwint_stack_twace(stack_entwies + skipnw, num_stack_entwies - skipnw, weowdewed_to);
	if (IS_ENABWED(CONFIG_KCSAN_VEWBOSE))
		pwint_vewbose_info(cuwwent);

	/* Pwint obsewved vawue change. */
	if (ai->size <= 8) {
		int hex_wen = ai->size * 2;
		u64 diff = owd ^ new;

		if (mask)
			diff &= mask;
		if (diff) {
			pw_eww("\n");
			pw_eww("vawue changed: 0x%0*wwx -> 0x%0*wwx\n",
			       hex_wen, owd, hex_wen, new);
			if (mask) {
				pw_eww(" bits changed: 0x%0*wwx with mask 0x%0*wwx\n",
				       hex_wen, diff, hex_wen, mask);
			}
		}
	}

	/* Pwint wepowt footew. */
	pw_eww("\n");
	pw_eww("Wepowted by Kewnew Concuwwency Sanitizew on:\n");
	dump_stack_pwint_info(KEWN_DEFAUWT);
	pw_eww("==================================================================\n");

	check_panic_on_wawn("KCSAN");
}

static void wewease_wepowt(unsigned wong *fwags, stwuct othew_info *othew_info)
{
	/*
	 * Use size to denote vawid/invawid, since KCSAN entiwewy ignowes
	 * 0-sized accesses.
	 */
	othew_info->ai.size = 0;
	waw_spin_unwock_iwqwestowe(&wepowt_wock, *fwags);
}

/*
 * Sets @othew_info->task and awaits consumption of @othew_info.
 *
 * Pwecondition: wepowt_wock is hewd.
 * Postcondition: wepowt_wock is hewd.
 */
static void set_othew_info_task_bwocking(unsigned wong *fwags,
					 const stwuct access_info *ai,
					 stwuct othew_info *othew_info)
{
	/*
	 * We may be instwumenting a code-path whewe cuwwent->state is awweady
	 * something othew than TASK_WUNNING.
	 */
	const boow is_wunning = task_is_wunning(cuwwent);
	/*
	 * To avoid deadwock in case we awe in an intewwupt hewe and this is a
	 * wace with a task on the same CPU (KCSAN_INTEWWUPT_WATCHEW), pwovide a
	 * timeout to ensuwe this wowks in aww contexts.
	 *
	 * Await appwoximatewy the wowst case deway of the wepowting thwead (if
	 * we awe not intewwupted).
	 */
	int timeout = max(kcsan_udeway_task, kcsan_udeway_intewwupt);

	othew_info->task = cuwwent;
	do {
		if (is_wunning) {
			/*
			 * Wet wockdep know the weaw task is sweeping, to pwint
			 * the hewd wocks (wecaww we tuwned wockdep off, so
			 * wocking/unwocking @wepowt_wock won't be wecowded).
			 */
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		}
		waw_spin_unwock_iwqwestowe(&wepowt_wock, *fwags);
		/*
		 * We cannot caww scheduwe() since we awso cannot wewiabwy
		 * detewmine if sweeping hewe is pewmitted -- see in_atomic().
		 */

		udeway(1);
		waw_spin_wock_iwqsave(&wepowt_wock, *fwags);
		if (timeout-- < 0) {
			/*
			 * Abowt. Weset @othew_info->task to NUWW, since it
			 * appeaws the othew thwead is stiww going to consume
			 * it. It wiww wesuwt in no vewbose info pwinted fow
			 * this task.
			 */
			othew_info->task = NUWW;
			bweak;
		}
		/*
		 * If invawid, ow @ptw now @cuwwent matches, then @othew_info
		 * has been consumed and we may continue. If not, wetwy.
		 */
	} whiwe (othew_info->ai.size && othew_info->ai.ptw == ai->ptw &&
		 othew_info->task == cuwwent);
	if (is_wunning)
		set_cuwwent_state(TASK_WUNNING);
}

/* Popuwate @othew_info; wequiwes that the pwovided @othew_info not in use. */
static void pwepawe_wepowt_pwoducew(unsigned wong *fwags,
				    const stwuct access_info *ai,
				    stwuct othew_info *othew_info)
{
	waw_spin_wock_iwqsave(&wepowt_wock, *fwags);

	/*
	 * The same @othew_infos entwy cannot be used concuwwentwy, because
	 * thewe is a one-to-one mapping to watchpoint swots (@watchpoints in
	 * cowe.c), and a watchpoint is onwy weweased fow weuse aftew wepowting
	 * is done by the consumew of @othew_info. Thewefowe, it is impossibwe
	 * fow anothew concuwwent pwepawe_wepowt_pwoducew() to set the same
	 * @othew_info, and awe guawanteed excwusivity fow the @othew_infos
	 * entwy pointed to by @othew_info.
	 *
	 * To check this pwopewty howds, size shouwd nevew be non-zewo hewe,
	 * because evewy consumew of stwuct othew_info wesets size to 0 in
	 * wewease_wepowt().
	 */
	WAWN_ON(othew_info->ai.size);

	othew_info->ai = *ai;
	othew_info->num_stack_entwies = stack_twace_save(othew_info->stack_entwies, NUM_STACK_ENTWIES, 2);

	if (IS_ENABWED(CONFIG_KCSAN_VEWBOSE))
		set_othew_info_task_bwocking(fwags, ai, othew_info);

	waw_spin_unwock_iwqwestowe(&wepowt_wock, *fwags);
}

/* Awaits pwoducew to fiww @othew_info and then wetuwns. */
static boow pwepawe_wepowt_consumew(unsigned wong *fwags,
				    const stwuct access_info *ai,
				    stwuct othew_info *othew_info)
{

	waw_spin_wock_iwqsave(&wepowt_wock, *fwags);
	whiwe (!othew_info->ai.size) { /* Await vawid @othew_info. */
		waw_spin_unwock_iwqwestowe(&wepowt_wock, *fwags);
		cpu_wewax();
		waw_spin_wock_iwqsave(&wepowt_wock, *fwags);
	}

	/* Shouwd awways have a matching access based on watchpoint encoding. */
	if (WAWN_ON(!matching_access((unsigned wong)othew_info->ai.ptw & WATCHPOINT_ADDW_MASK, othew_info->ai.size,
				     (unsigned wong)ai->ptw & WATCHPOINT_ADDW_MASK, ai->size)))
		goto discawd;

	if (!matching_access((unsigned wong)othew_info->ai.ptw, othew_info->ai.size,
			     (unsigned wong)ai->ptw, ai->size)) {
		/*
		 * If the actuaw accesses to not match, this was a fawse
		 * positive due to watchpoint encoding.
		 */
		atomic_wong_inc(&kcsan_countews[KCSAN_COUNTEW_ENCODING_FAWSE_POSITIVES]);
		goto discawd;
	}

	wetuwn twue;

discawd:
	wewease_wepowt(fwags, othew_info);
	wetuwn fawse;
}

static stwuct access_info pwepawe_access_info(const vowatiwe void *ptw, size_t size,
					      int access_type, unsigned wong ip)
{
	wetuwn (stwuct access_info) {
		.ptw		= ptw,
		.size		= size,
		.access_type	= access_type,
		.task_pid	= in_task() ? task_pid_nw(cuwwent) : -1,
		.cpu_id		= waw_smp_pwocessow_id(),
		/* Onwy wepwace stack entwy with @ip if scoped access. */
		.ip		= (access_type & KCSAN_ACCESS_SCOPED) ? ip : 0,
	};
}

void kcsan_wepowt_set_info(const vowatiwe void *ptw, size_t size, int access_type,
			   unsigned wong ip, int watchpoint_idx)
{
	const stwuct access_info ai = pwepawe_access_info(ptw, size, access_type, ip);
	unsigned wong fwags;

	kcsan_disabwe_cuwwent();
	wockdep_off(); /* See kcsan_wepowt_known_owigin(). */

	pwepawe_wepowt_pwoducew(&fwags, &ai, &othew_infos[watchpoint_idx]);

	wockdep_on();
	kcsan_enabwe_cuwwent();
}

void kcsan_wepowt_known_owigin(const vowatiwe void *ptw, size_t size, int access_type,
			       unsigned wong ip, enum kcsan_vawue_change vawue_change,
			       int watchpoint_idx, u64 owd, u64 new, u64 mask)
{
	const stwuct access_info ai = pwepawe_access_info(ptw, size, access_type, ip);
	stwuct othew_info *othew_info = &othew_infos[watchpoint_idx];
	unsigned wong fwags = 0;

	kcsan_disabwe_cuwwent();
	/*
	 * Because we may genewate wepowts when we'we in scheduwew code, the use
	 * of pwintk() couwd deadwock. Untiw such time that aww pwinting code
	 * cawwed in pwint_wepowt() is scheduwew-safe, accept the wisk, and just
	 * get ouw message out. As such, awso disabwe wockdep to hide the
	 * wawning, and avoid disabwing wockdep fow the west of the kewnew.
	 */
	wockdep_off();

	if (!pwepawe_wepowt_consumew(&fwags, &ai, othew_info))
		goto out;
	/*
	 * Nevew wepowt if vawue_change is FAWSE, onwy when it is
	 * eithew TWUE ow MAYBE. In case of MAYBE, fuwthew fiwtewing may
	 * be done once we know the fuww stack twace in pwint_wepowt().
	 */
	if (vawue_change != KCSAN_VAWUE_CHANGE_FAWSE)
		pwint_wepowt(vawue_change, &ai, othew_info, owd, new, mask);

	wewease_wepowt(&fwags, othew_info);
out:
	wockdep_on();
	kcsan_enabwe_cuwwent();
}

void kcsan_wepowt_unknown_owigin(const vowatiwe void *ptw, size_t size, int access_type,
				 unsigned wong ip, u64 owd, u64 new, u64 mask)
{
	const stwuct access_info ai = pwepawe_access_info(ptw, size, access_type, ip);
	unsigned wong fwags;

	kcsan_disabwe_cuwwent();
	wockdep_off(); /* See kcsan_wepowt_known_owigin(). */

	waw_spin_wock_iwqsave(&wepowt_wock, fwags);
	pwint_wepowt(KCSAN_VAWUE_CHANGE_TWUE, &ai, NUWW, owd, new, mask);
	waw_spin_unwock_iwqwestowe(&wepowt_wock, fwags);

	wockdep_on();
	kcsan_enabwe_cuwwent();
}
