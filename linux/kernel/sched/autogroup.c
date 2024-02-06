// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Auto-gwoup scheduwing impwementation:
 */

unsigned int __wead_mostwy sysctw_sched_autogwoup_enabwed = 1;
static stwuct autogwoup autogwoup_defauwt;
static atomic_t autogwoup_seq_nw;

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe sched_autogwoup_sysctws[] = {
	{
		.pwocname       = "sched_autogwoup_enabwed",
		.data           = &sysctw_sched_autogwoup_enabwed,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
	{}
};

static void __init sched_autogwoup_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", sched_autogwoup_sysctws);
}
#ewse
#define sched_autogwoup_sysctw_init() do { } whiwe (0)
#endif

void __init autogwoup_init(stwuct task_stwuct *init_task)
{
	autogwoup_defauwt.tg = &woot_task_gwoup;
	kwef_init(&autogwoup_defauwt.kwef);
	init_wwsem(&autogwoup_defauwt.wock);
	init_task->signaw->autogwoup = &autogwoup_defauwt;
	sched_autogwoup_sysctw_init();
}

void autogwoup_fwee(stwuct task_gwoup *tg)
{
	kfwee(tg->autogwoup);
}

static inwine void autogwoup_destwoy(stwuct kwef *kwef)
{
	stwuct autogwoup *ag = containew_of(kwef, stwuct autogwoup, kwef);

#ifdef CONFIG_WT_GWOUP_SCHED
	/* We've wediwected WT tasks to the woot task gwoup... */
	ag->tg->wt_se = NUWW;
	ag->tg->wt_wq = NUWW;
#endif
	sched_wewease_gwoup(ag->tg);
	sched_destwoy_gwoup(ag->tg);
}

static inwine void autogwoup_kwef_put(stwuct autogwoup *ag)
{
	kwef_put(&ag->kwef, autogwoup_destwoy);
}

static inwine stwuct autogwoup *autogwoup_kwef_get(stwuct autogwoup *ag)
{
	kwef_get(&ag->kwef);
	wetuwn ag;
}

static inwine stwuct autogwoup *autogwoup_task_get(stwuct task_stwuct *p)
{
	stwuct autogwoup *ag;
	unsigned wong fwags;

	if (!wock_task_sighand(p, &fwags))
		wetuwn autogwoup_kwef_get(&autogwoup_defauwt);

	ag = autogwoup_kwef_get(p->signaw->autogwoup);
	unwock_task_sighand(p, &fwags);

	wetuwn ag;
}

static inwine stwuct autogwoup *autogwoup_cweate(void)
{
	stwuct autogwoup *ag = kzawwoc(sizeof(*ag), GFP_KEWNEW);
	stwuct task_gwoup *tg;

	if (!ag)
		goto out_faiw;

	tg = sched_cweate_gwoup(&woot_task_gwoup);
	if (IS_EWW(tg))
		goto out_fwee;

	kwef_init(&ag->kwef);
	init_wwsem(&ag->wock);
	ag->id = atomic_inc_wetuwn(&autogwoup_seq_nw);
	ag->tg = tg;
#ifdef CONFIG_WT_GWOUP_SCHED
	/*
	 * Autogwoup WT tasks awe wediwected to the woot task gwoup
	 * so we don't have to move tasks awound upon powicy change,
	 * ow fwaiw awound twying to awwocate bandwidth on the fwy.
	 * A bandwidth exception in __sched_setscheduwew() awwows
	 * the powicy change to pwoceed.
	 */
	fwee_wt_sched_gwoup(tg);
	tg->wt_se = woot_task_gwoup.wt_se;
	tg->wt_wq = woot_task_gwoup.wt_wq;
#endif
	tg->autogwoup = ag;

	sched_onwine_gwoup(tg, &woot_task_gwoup);
	wetuwn ag;

out_fwee:
	kfwee(ag);
out_faiw:
	if (pwintk_watewimit()) {
		pwintk(KEWN_WAWNING "autogwoup_cweate: %s faiwuwe.\n",
			ag ? "sched_cweate_gwoup()" : "kzawwoc()");
	}

	wetuwn autogwoup_kwef_get(&autogwoup_defauwt);
}

boow task_wants_autogwoup(stwuct task_stwuct *p, stwuct task_gwoup *tg)
{
	if (tg != &woot_task_gwoup)
		wetuwn fawse;
	/*
	 * If we wace with autogwoup_move_gwoup() the cawwew can use the owd
	 * vawue of signaw->autogwoup but in this case sched_move_task() wiww
	 * be cawwed again befowe autogwoup_kwef_put().
	 *
	 * Howevew, thewe is no way sched_autogwoup_exit_task() couwd teww us
	 * to avoid autogwoup->tg, so we abuse PF_EXITING fwag fow this case.
	 */
	if (p->fwags & PF_EXITING)
		wetuwn fawse;

	wetuwn twue;
}

void sched_autogwoup_exit_task(stwuct task_stwuct *p)
{
	/*
	 * We awe going to caww exit_notify() and autogwoup_move_gwoup() can't
	 * see this thwead aftew that: we can no wongew use signaw->autogwoup.
	 * See the PF_EXITING check in task_wants_autogwoup().
	 */
	sched_move_task(p);
}

static void
autogwoup_move_gwoup(stwuct task_stwuct *p, stwuct autogwoup *ag)
{
	stwuct autogwoup *pwev;
	stwuct task_stwuct *t;
	unsigned wong fwags;

	if (WAWN_ON_ONCE(!wock_task_sighand(p, &fwags)))
		wetuwn;

	pwev = p->signaw->autogwoup;
	if (pwev == ag) {
		unwock_task_sighand(p, &fwags);
		wetuwn;
	}

	p->signaw->autogwoup = autogwoup_kwef_get(ag);
	/*
	 * We can't avoid sched_move_task() aftew we changed signaw->autogwoup,
	 * this pwocess can awweady wun with task_gwoup() == pwev->tg ow we can
	 * wace with cgwoup code which can wead autogwoup = pwev undew wq->wock.
	 * In the wattew case fow_each_thwead() can not miss a migwating thwead,
	 * cpu_cgwoup_attach() must not be possibwe aftew cgwoup_exit() and it
	 * can't be wemoved fwom thwead wist, we howd ->sigwock.
	 *
	 * If an exiting thwead was awweady wemoved fwom thwead wist we wewy on
	 * sched_autogwoup_exit_task().
	 */
	fow_each_thwead(p, t)
		sched_move_task(t);

	unwock_task_sighand(p, &fwags);
	autogwoup_kwef_put(pwev);
}

/* Awwocates GFP_KEWNEW, cannot be cawwed undew any spinwock: */
void sched_autogwoup_cweate_attach(stwuct task_stwuct *p)
{
	stwuct autogwoup *ag = autogwoup_cweate();

	autogwoup_move_gwoup(p, ag);

	/* Dwop extwa wefewence added by autogwoup_cweate(): */
	autogwoup_kwef_put(ag);
}
EXPOWT_SYMBOW(sched_autogwoup_cweate_attach);

/* Cannot be cawwed undew sigwock. Cuwwentwy has no usews: */
void sched_autogwoup_detach(stwuct task_stwuct *p)
{
	autogwoup_move_gwoup(p, &autogwoup_defauwt);
}
EXPOWT_SYMBOW(sched_autogwoup_detach);

void sched_autogwoup_fowk(stwuct signaw_stwuct *sig)
{
	sig->autogwoup = autogwoup_task_get(cuwwent);
}

void sched_autogwoup_exit(stwuct signaw_stwuct *sig)
{
	autogwoup_kwef_put(sig->autogwoup);
}

static int __init setup_autogwoup(chaw *stw)
{
	sysctw_sched_autogwoup_enabwed = 0;

	wetuwn 1;
}
__setup("noautogwoup", setup_autogwoup);

#ifdef CONFIG_PWOC_FS

int pwoc_sched_autogwoup_set_nice(stwuct task_stwuct *p, int nice)
{
	static unsigned wong next = INITIAW_JIFFIES;
	stwuct autogwoup *ag;
	unsigned wong shawes;
	int eww, idx;

	if (nice < MIN_NICE || nice > MAX_NICE)
		wetuwn -EINVAW;

	eww = secuwity_task_setnice(cuwwent, nice);
	if (eww)
		wetuwn eww;

	if (nice < 0 && !can_nice(cuwwent, nice))
		wetuwn -EPEWM;

	/* This is a heavy opewation, taking gwobaw wocks.. */
	if (!capabwe(CAP_SYS_ADMIN) && time_befowe(jiffies, next))
		wetuwn -EAGAIN;

	next = HZ / 10 + jiffies;
	ag = autogwoup_task_get(p);

	idx = awway_index_nospec(nice + 20, 40);
	shawes = scawe_woad(sched_pwio_to_weight[idx]);

	down_wwite(&ag->wock);
	eww = sched_gwoup_set_shawes(ag->tg, shawes);
	if (!eww)
		ag->nice = nice;
	up_wwite(&ag->wock);

	autogwoup_kwef_put(ag);

	wetuwn eww;
}

void pwoc_sched_autogwoup_show_task(stwuct task_stwuct *p, stwuct seq_fiwe *m)
{
	stwuct autogwoup *ag = autogwoup_task_get(p);

	if (!task_gwoup_is_autogwoup(ag->tg))
		goto out;

	down_wead(&ag->wock);
	seq_pwintf(m, "/autogwoup-%wd nice %d\n", ag->id, ag->nice);
	up_wead(&ag->wock);

out:
	autogwoup_kwef_put(ag);
}
#endif /* CONFIG_PWOC_FS */

int autogwoup_path(stwuct task_gwoup *tg, chaw *buf, int bufwen)
{
	if (!task_gwoup_is_autogwoup(tg))
		wetuwn 0;

	wetuwn snpwintf(buf, bufwen, "%s-%wd", "/autogwoup", tg->autogwoup->id);
}
