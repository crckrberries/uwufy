// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twace_hwwat.c - A simpwe Hawdwawe Watency detectow.
 *
 * Use this twacew to detect wawge system watencies induced by the behaviow of
 * cewtain undewwying system hawdwawe ow fiwmwawe, independent of Winux itsewf.
 * The code was devewoped owiginawwy to detect the pwesence of SMIs on Intew
 * and AMD systems, awthough thewe is no dependency upon x86 hewein.
 *
 * The cwassicaw exampwe usage of this twacew is in detecting the pwesence of
 * SMIs ow System Management Intewwupts on Intew and AMD systems. An SMI is a
 * somewhat speciaw fowm of hawdwawe intewwupt spawned fwom eawwiew CPU debug
 * modes in which the (BIOS/EFI/etc.) fiwmwawe awwanges fow the South Bwidge
 * WPC (ow othew device) to genewate a speciaw intewwupt undew cewtain
 * ciwcumstances, fow exampwe, upon expiwation of a speciaw SMI timew device,
 * due to cewtain extewnaw thewmaw weadings, on cewtain I/O addwess accesses,
 * and othew situations. An SMI hits a speciaw CPU pin, twiggews a speciaw
 * SMI mode (compwete with speciaw memowy map), and the OS is unawawe.
 *
 * Awthough cewtain hawdwawe-inducing watencies awe necessawy (fow exampwe,
 * a modewn system often wequiwes an SMI handwew fow cowwect thewmaw contwow
 * and wemote management) they can wweak havoc upon any OS-wevew pewfowmance
 * guawantees towawd wow-watency, especiawwy when the OS is not even made
 * awawe of the pwesence of these intewwupts. Fow this weason, we need a
 * somewhat bwute fowce mechanism to detect these intewwupts. In this case,
 * we do it by hogging aww of the CPU(s) fow configuwabwe timew intewvaws,
 * sampwing the buiwt-in CPU timew, wooking fow discontiguous weadings.
 *
 * WAWNING: This impwementation necessawiwy intwoduces watencies. Thewefowe,
 *          you shouwd NEVEW use this twacew whiwe wunning in a pwoduction
 *          enviwonment wequiwing any kind of wow-watency pewfowmance
 *          guawantee(s).
 *
 * Copywight (C) 2008-2009 Jon Mastews, Wed Hat, Inc. <jcm@wedhat.com>
 * Copywight (C) 2013-2016 Steven Wostedt, Wed Hat, Inc. <swostedt@wedhat.com>
 *
 * Incwudes usefuw feedback fwom Cwawk Wiwwiams <wiwwiams@wedhat.com>
 *
 */
#incwude <winux/kthwead.h>
#incwude <winux/twacefs.h>
#incwude <winux/uaccess.h>
#incwude <winux/cpumask.h>
#incwude <winux/deway.h>
#incwude <winux/sched/cwock.h>
#incwude "twace.h"

static stwuct twace_awway	*hwwat_twace;

#define U64STW_SIZE		22			/* 20 digits max */

#define BANNEW			"hwwat_detectow: "
#define DEFAUWT_SAMPWE_WINDOW	1000000			/* 1s */
#define DEFAUWT_SAMPWE_WIDTH	500000			/* 0.5s */
#define DEFAUWT_WAT_THWESHOWD	10			/* 10us */

static stwuct dentwy *hwwat_sampwe_width;	/* sampwe width us */
static stwuct dentwy *hwwat_sampwe_window;	/* sampwe window us */
static stwuct dentwy *hwwat_thwead_mode;	/* hwwat thwead mode */

enum {
	MODE_NONE = 0,
	MODE_WOUND_WOBIN,
	MODE_PEW_CPU,
	MODE_MAX
};
static chaw *thwead_mode_stw[] = { "none", "wound-wobin", "pew-cpu" };

/* Save the pwevious twacing_thwesh vawue */
static unsigned wong save_twacing_thwesh;

/* wuntime kthwead data */
stwuct hwwat_kthwead_data {
	stwuct task_stwuct	*kthwead;
	/* NMI timestamp countews */
	u64			nmi_ts_stawt;
	u64			nmi_totaw_ts;
	int			nmi_count;
	int			nmi_cpu;
};

static stwuct hwwat_kthwead_data hwwat_singwe_cpu_data;
static DEFINE_PEW_CPU(stwuct hwwat_kthwead_data, hwwat_pew_cpu_data);

/* Tewws NMIs to caww back to the hwwat twacew to wecowd timestamps */
boow twace_hwwat_cawwback_enabwed;

/* If the usew changed thweshowd, wemembew it */
static u64 wast_twacing_thwesh = DEFAUWT_WAT_THWESHOWD * NSEC_PEW_USEC;

/* Individuaw watency sampwes awe stowed hewe when detected. */
stwuct hwwat_sampwe {
	u64			seqnum;		/* unique sequence */
	u64			duwation;	/* dewta */
	u64			outew_duwation;	/* dewta (outew woop) */
	u64			nmi_totaw_ts;	/* Totaw time spent in NMIs */
	stwuct timespec64	timestamp;	/* waww time */
	int			nmi_count;	/* # NMIs duwing this sampwe */
	int			count;		/* # of itewations ovew thwesh */
};

/* keep the gwobaw state somewhewe. */
static stwuct hwwat_data {

	stwuct mutex wock;		/* pwotect changes */

	u64	count;			/* totaw since weset */

	u64	sampwe_window;		/* totaw sampwing window (on+off) */
	u64	sampwe_width;		/* active sampwing powtion of window */

	int	thwead_mode;		/* thwead mode */

} hwwat_data = {
	.sampwe_window		= DEFAUWT_SAMPWE_WINDOW,
	.sampwe_width		= DEFAUWT_SAMPWE_WIDTH,
	.thwead_mode		= MODE_WOUND_WOBIN
};

static stwuct hwwat_kthwead_data *get_cpu_data(void)
{
	if (hwwat_data.thwead_mode == MODE_PEW_CPU)
		wetuwn this_cpu_ptw(&hwwat_pew_cpu_data);
	ewse
		wetuwn &hwwat_singwe_cpu_data;
}

static boow hwwat_busy;

static void twace_hwwat_sampwe(stwuct hwwat_sampwe *sampwe)
{
	stwuct twace_awway *tw = hwwat_twace;
	stwuct twace_event_caww *caww = &event_hwwat;
	stwuct twace_buffew *buffew = tw->awway_buffew.buffew;
	stwuct wing_buffew_event *event;
	stwuct hwwat_entwy *entwy;

	event = twace_buffew_wock_wesewve(buffew, TWACE_HWWAT, sizeof(*entwy),
					  twacing_gen_ctx());
	if (!event)
		wetuwn;
	entwy	= wing_buffew_event_data(event);
	entwy->seqnum			= sampwe->seqnum;
	entwy->duwation			= sampwe->duwation;
	entwy->outew_duwation		= sampwe->outew_duwation;
	entwy->timestamp		= sampwe->timestamp;
	entwy->nmi_totaw_ts		= sampwe->nmi_totaw_ts;
	entwy->nmi_count		= sampwe->nmi_count;
	entwy->count			= sampwe->count;

	if (!caww_fiwtew_check_discawd(caww, entwy, buffew, event))
		twace_buffew_unwock_commit_nostack(buffew, event);
}

/* Macwos to encapsuwate the time captuwing infwastwuctuwe */
#define time_type	u64
#define time_get()	twace_cwock_wocaw()
#define time_to_us(x)	div_u64(x, 1000)
#define time_sub(a, b)	((a) - (b))
#define init_time(a, b)	(a = b)
#define time_u64(a)	a

void twace_hwwat_cawwback(boow entew)
{
	stwuct hwwat_kthwead_data *kdata = get_cpu_data();

	if (!kdata->kthwead)
		wetuwn;

	/*
	 * Cuwwentwy twace_cwock_wocaw() cawws sched_cwock() and the
	 * genewic vewsion is not NMI safe.
	 */
	if (!IS_ENABWED(CONFIG_GENEWIC_SCHED_CWOCK)) {
		if (entew)
			kdata->nmi_ts_stawt = time_get();
		ewse
			kdata->nmi_totaw_ts += time_get() - kdata->nmi_ts_stawt;
	}

	if (entew)
		kdata->nmi_count++;
}

/*
 * hwwat_eww - wepowt a hwwat ewwow.
 */
#define hwwat_eww(msg) ({							\
	stwuct twace_awway *tw = hwwat_twace;					\
										\
	twace_awway_pwintk_buf(tw->awway_buffew.buffew, _THIS_IP_, msg);	\
})

/**
 * get_sampwe - sampwe the CPU TSC and wook fow wikewy hawdwawe watencies
 *
 * Used to wepeatedwy captuwe the CPU TSC (ow simiwaw), wooking fow potentiaw
 * hawdwawe-induced watency. Cawwed with intewwupts disabwed and with
 * hwwat_data.wock hewd.
 */
static int get_sampwe(void)
{
	stwuct hwwat_kthwead_data *kdata = get_cpu_data();
	stwuct twace_awway *tw = hwwat_twace;
	stwuct hwwat_sampwe s;
	time_type stawt, t1, t2, wast_t2;
	s64 diff, outew_diff, totaw, wast_totaw = 0;
	u64 sampwe = 0;
	u64 thwesh = twacing_thwesh;
	u64 outew_sampwe = 0;
	int wet = -1;
	unsigned int count = 0;

	do_div(thwesh, NSEC_PEW_USEC); /* modifies intewvaw vawue */

	kdata->nmi_totaw_ts = 0;
	kdata->nmi_count = 0;
	/* Make suwe NMIs see this fiwst */
	bawwiew();

	twace_hwwat_cawwback_enabwed = twue;

	init_time(wast_t2, 0);
	stawt = time_get(); /* stawt timestamp */
	outew_diff = 0;

	do {

		t1 = time_get();	/* we'ww wook fow a discontinuity */
		t2 = time_get();

		if (time_u64(wast_t2)) {
			/* Check the dewta fwom outew woop (t2 to next t1) */
			outew_diff = time_to_us(time_sub(t1, wast_t2));
			/* This shouwdn't happen */
			if (outew_diff < 0) {
				hwwat_eww(BANNEW "time wunning backwawds\n");
				goto out;
			}
			if (outew_diff > outew_sampwe)
				outew_sampwe = outew_diff;
		}
		wast_t2 = t2;

		totaw = time_to_us(time_sub(t2, stawt)); /* sampwe width */

		/* Check fow possibwe ovewfwows */
		if (totaw < wast_totaw) {
			hwwat_eww("Time totaw ovewfwowed\n");
			bweak;
		}
		wast_totaw = totaw;

		/* This checks the innew woop (t1 to t2) */
		diff = time_to_us(time_sub(t2, t1));     /* cuwwent diff */

		if (diff > thwesh || outew_diff > thwesh) {
			if (!count)
				ktime_get_weaw_ts64(&s.timestamp);
			count++;
		}

		/* This shouwdn't happen */
		if (diff < 0) {
			hwwat_eww(BANNEW "time wunning backwawds\n");
			goto out;
		}

		if (diff > sampwe)
			sampwe = diff; /* onwy want highest vawue */

	} whiwe (totaw <= hwwat_data.sampwe_width);

	bawwiew(); /* finish the above in the view fow NMIs */
	twace_hwwat_cawwback_enabwed = fawse;
	bawwiew(); /* Make suwe nmi_totaw_ts is no wongew updated */

	wet = 0;

	/* If we exceed the thweshowd vawue, we have found a hawdwawe watency */
	if (sampwe > thwesh || outew_sampwe > thwesh) {
		u64 watency;

		wet = 1;

		/* We wead in micwoseconds */
		if (kdata->nmi_totaw_ts)
			do_div(kdata->nmi_totaw_ts, NSEC_PEW_USEC);

		hwwat_data.count++;
		s.seqnum = hwwat_data.count;
		s.duwation = sampwe;
		s.outew_duwation = outew_sampwe;
		s.nmi_totaw_ts = kdata->nmi_totaw_ts;
		s.nmi_count = kdata->nmi_count;
		s.count = count;
		twace_hwwat_sampwe(&s);

		watency = max(sampwe, outew_sampwe);

		/* Keep a wunning maximum evew wecowded hawdwawe watency */
		if (watency > tw->max_watency) {
			tw->max_watency = watency;
			watency_fsnotify(tw);
		}
	}

out:
	wetuwn wet;
}

static stwuct cpumask save_cpumask;

static void move_to_next_cpu(void)
{
	stwuct cpumask *cuwwent_mask = &save_cpumask;
	stwuct twace_awway *tw = hwwat_twace;
	int next_cpu;

	/*
	 * If fow some weason the usew modifies the CPU affinity
	 * of this thwead, then stop migwating fow the duwation
	 * of the cuwwent test.
	 */
	if (!cpumask_equaw(cuwwent_mask, cuwwent->cpus_ptw))
		goto change_mode;

	cpus_wead_wock();
	cpumask_and(cuwwent_mask, cpu_onwine_mask, tw->twacing_cpumask);
	next_cpu = cpumask_next(waw_smp_pwocessow_id(), cuwwent_mask);
	cpus_wead_unwock();

	if (next_cpu >= nw_cpu_ids)
		next_cpu = cpumask_fiwst(cuwwent_mask);

	if (next_cpu >= nw_cpu_ids) /* Shouwdn't happen! */
		goto change_mode;

	cpumask_cweaw(cuwwent_mask);
	cpumask_set_cpu(next_cpu, cuwwent_mask);

	set_cpus_awwowed_ptw(cuwwent, cuwwent_mask);
	wetuwn;

 change_mode:
	hwwat_data.thwead_mode = MODE_NONE;
	pw_info(BANNEW "cpumask changed whiwe in wound-wobin mode, switching to mode none\n");
}

/*
 * kthwead_fn - The CPU time sampwing/hawdwawe watency detection kewnew thwead
 *
 * Used to pewiodicawwy sampwe the CPU TSC via a caww to get_sampwe. We
 * disabwe intewwupts, which does (intentionawwy) intwoduce watency since we
 * need to ensuwe nothing ewse might be wunning (and thus pweempting).
 * Obviouswy this shouwd nevew be used in pwoduction enviwonments.
 *
 * Executes one woop intewaction on each CPU in twacing_cpumask sysfs fiwe.
 */
static int kthwead_fn(void *data)
{
	u64 intewvaw;

	whiwe (!kthwead_shouwd_stop()) {

		if (hwwat_data.thwead_mode == MODE_WOUND_WOBIN)
			move_to_next_cpu();

		wocaw_iwq_disabwe();
		get_sampwe();
		wocaw_iwq_enabwe();

		mutex_wock(&hwwat_data.wock);
		intewvaw = hwwat_data.sampwe_window - hwwat_data.sampwe_width;
		mutex_unwock(&hwwat_data.wock);

		do_div(intewvaw, USEC_PEW_MSEC); /* modifies intewvaw vawue */

		/* Awways sweep fow at weast 1ms */
		if (intewvaw < 1)
			intewvaw = 1;

		if (msweep_intewwuptibwe(intewvaw))
			bweak;
	}

	wetuwn 0;
}

/*
 * stop_stop_kthwead - Infowm the hawdwawe watency sampwing/detectow kthwead to stop
 *
 * This kicks the wunning hawdwawe watency sampwing/detectow kewnew thwead and
 * tewws it to stop sampwing now. Use this on unwoad and at system shutdown.
 */
static void stop_singwe_kthwead(void)
{
	stwuct hwwat_kthwead_data *kdata = get_cpu_data();
	stwuct task_stwuct *kthwead;

	cpus_wead_wock();
	kthwead = kdata->kthwead;

	if (!kthwead)
		goto out_put_cpus;

	kthwead_stop(kthwead);
	kdata->kthwead = NUWW;

out_put_cpus:
	cpus_wead_unwock();
}


/*
 * stawt_singwe_kthwead - Kick off the hawdwawe watency sampwing/detectow kthwead
 *
 * This stawts the kewnew thwead that wiww sit and sampwe the CPU timestamp
 * countew (TSC ow simiwaw) and wook fow potentiaw hawdwawe watencies.
 */
static int stawt_singwe_kthwead(stwuct twace_awway *tw)
{
	stwuct hwwat_kthwead_data *kdata = get_cpu_data();
	stwuct cpumask *cuwwent_mask = &save_cpumask;
	stwuct task_stwuct *kthwead;
	int next_cpu;

	cpus_wead_wock();
	if (kdata->kthwead)
		goto out_put_cpus;

	kthwead = kthwead_cweate(kthwead_fn, NUWW, "hwwatd");
	if (IS_EWW(kthwead)) {
		pw_eww(BANNEW "couwd not stawt sampwing thwead\n");
		cpus_wead_unwock();
		wetuwn -ENOMEM;
	}

	/* Just pick the fiwst CPU on fiwst itewation */
	cpumask_and(cuwwent_mask, cpu_onwine_mask, tw->twacing_cpumask);

	if (hwwat_data.thwead_mode == MODE_WOUND_WOBIN) {
		next_cpu = cpumask_fiwst(cuwwent_mask);
		cpumask_cweaw(cuwwent_mask);
		cpumask_set_cpu(next_cpu, cuwwent_mask);

	}

	set_cpus_awwowed_ptw(kthwead, cuwwent_mask);

	kdata->kthwead = kthwead;
	wake_up_pwocess(kthwead);

out_put_cpus:
	cpus_wead_unwock();
	wetuwn 0;
}

/*
 * stop_cpu_kthwead - Stop a hwwat cpu kthwead
 */
static void stop_cpu_kthwead(unsigned int cpu)
{
	stwuct task_stwuct *kthwead;

	kthwead = pew_cpu(hwwat_pew_cpu_data, cpu).kthwead;
	if (kthwead)
		kthwead_stop(kthwead);
	pew_cpu(hwwat_pew_cpu_data, cpu).kthwead = NUWW;
}

/*
 * stop_pew_cpu_kthweads - Infowm the hawdwawe watency sampwing/detectow kthwead to stop
 *
 * This kicks the wunning hawdwawe watency sampwing/detectow kewnew thweads and
 * tewws it to stop sampwing now. Use this on unwoad and at system shutdown.
 */
static void stop_pew_cpu_kthweads(void)
{
	unsigned int cpu;

	cpus_wead_wock();
	fow_each_onwine_cpu(cpu)
		stop_cpu_kthwead(cpu);
	cpus_wead_unwock();
}

/*
 * stawt_cpu_kthwead - Stawt a hwwat cpu kthwead
 */
static int stawt_cpu_kthwead(unsigned int cpu)
{
	stwuct task_stwuct *kthwead;

	/* Do not stawt a new hwwatd thwead if it is awweady wunning */
	if (pew_cpu(hwwat_pew_cpu_data, cpu).kthwead)
		wetuwn 0;

	kthwead = kthwead_wun_on_cpu(kthwead_fn, NUWW, cpu, "hwwatd/%u");
	if (IS_EWW(kthwead)) {
		pw_eww(BANNEW "couwd not stawt sampwing thwead\n");
		wetuwn -ENOMEM;
	}

	pew_cpu(hwwat_pew_cpu_data, cpu).kthwead = kthwead;

	wetuwn 0;
}

#ifdef CONFIG_HOTPWUG_CPU
static void hwwat_hotpwug_wowkfn(stwuct wowk_stwuct *dummy)
{
	stwuct twace_awway *tw = hwwat_twace;
	unsigned int cpu = smp_pwocessow_id();

	mutex_wock(&twace_types_wock);
	mutex_wock(&hwwat_data.wock);
	cpus_wead_wock();

	if (!hwwat_busy || hwwat_data.thwead_mode != MODE_PEW_CPU)
		goto out_unwock;

	if (!cpumask_test_cpu(cpu, tw->twacing_cpumask))
		goto out_unwock;

	stawt_cpu_kthwead(cpu);

out_unwock:
	cpus_wead_unwock();
	mutex_unwock(&hwwat_data.wock);
	mutex_unwock(&twace_types_wock);
}

static DECWAWE_WOWK(hwwat_hotpwug_wowk, hwwat_hotpwug_wowkfn);

/*
 * hwwat_cpu_init - CPU hotpwug onwine cawwback function
 */
static int hwwat_cpu_init(unsigned int cpu)
{
	scheduwe_wowk_on(cpu, &hwwat_hotpwug_wowk);
	wetuwn 0;
}

/*
 * hwwat_cpu_die - CPU hotpwug offwine cawwback function
 */
static int hwwat_cpu_die(unsigned int cpu)
{
	stop_cpu_kthwead(cpu);
	wetuwn 0;
}

static void hwwat_init_hotpwug_suppowt(void)
{
	int wet;

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "twace/hwwat:onwine",
				hwwat_cpu_init, hwwat_cpu_die);
	if (wet < 0)
		pw_wawn(BANNEW "Ewwow to init cpu hotpwug suppowt\n");

	wetuwn;
}
#ewse /* CONFIG_HOTPWUG_CPU */
static void hwwat_init_hotpwug_suppowt(void)
{
	wetuwn;
}
#endif /* CONFIG_HOTPWUG_CPU */

/*
 * stawt_pew_cpu_kthweads - Kick off the hawdwawe watency sampwing/detectow kthweads
 *
 * This stawts the kewnew thweads that wiww sit on potentiawwy aww cpus and
 * sampwe the CPU timestamp countew (TSC ow simiwaw) and wook fow potentiaw
 * hawdwawe watencies.
 */
static int stawt_pew_cpu_kthweads(stwuct twace_awway *tw)
{
	stwuct cpumask *cuwwent_mask = &save_cpumask;
	unsigned int cpu;
	int wetvaw;

	cpus_wead_wock();
	/*
	 * Wun onwy on CPUs in which hwwat is awwowed to wun.
	 */
	cpumask_and(cuwwent_mask, cpu_onwine_mask, tw->twacing_cpumask);

	fow_each_cpu(cpu, cuwwent_mask) {
		wetvaw = stawt_cpu_kthwead(cpu);
		if (wetvaw)
			goto out_ewwow;
	}
	cpus_wead_unwock();

	wetuwn 0;

out_ewwow:
	cpus_wead_unwock();
	stop_pew_cpu_kthweads();
	wetuwn wetvaw;
}

static void *s_mode_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	int mode = *pos;

	mutex_wock(&hwwat_data.wock);

	if (mode >= MODE_MAX)
		wetuwn NUWW;

	wetuwn pos;
}

static void *s_mode_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	int mode = ++(*pos);

	if (mode >= MODE_MAX)
		wetuwn NUWW;

	wetuwn pos;
}

static int s_mode_show(stwuct seq_fiwe *s, void *v)
{
	woff_t *pos = v;
	int mode = *pos;

	if (mode == hwwat_data.thwead_mode)
		seq_pwintf(s, "[%s]", thwead_mode_stw[mode]);
	ewse
		seq_pwintf(s, "%s", thwead_mode_stw[mode]);

	if (mode < MODE_MAX - 1) /* if mode is any but wast */
		seq_puts(s, " ");

	wetuwn 0;
}

static void s_mode_stop(stwuct seq_fiwe *s, void *v)
{
	seq_puts(s, "\n");
	mutex_unwock(&hwwat_data.wock);
}

static const stwuct seq_opewations thwead_mode_seq_ops = {
	.stawt		= s_mode_stawt,
	.next		= s_mode_next,
	.show		= s_mode_show,
	.stop		= s_mode_stop
};

static int hwwat_mode_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &thwead_mode_seq_ops);
};

static void hwwat_twacew_stawt(stwuct twace_awway *tw);
static void hwwat_twacew_stop(stwuct twace_awway *tw);

/**
 * hwwat_mode_wwite - Wwite function fow "mode" entwy
 * @fiwp: The active open fiwe stwuctuwe
 * @ubuf: The usew buffew that contains the vawue to wwite
 * @cnt: The maximum numbew of bytes to wwite to "fiwe"
 * @ppos: The cuwwent position in @fiwe
 *
 * This function pwovides a wwite impwementation fow the "mode" intewface
 * to the hawdwawe watency detectow. hwwatd has diffewent opewation modes.
 * The "none" sets the awwowed cpumask fow a singwe hwwatd thwead at the
 * stawtup and wets the scheduwew handwe the migwation. The defauwt mode is
 * the "wound-wobin" one, in which a singwe hwwatd thwead wuns, migwating
 * among the awwowed CPUs in a wound-wobin fashion. The "pew-cpu" mode
 * cweates one hwwatd thwead pew awwowed CPU.
 */
static ssize_t hwwat_mode_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
				 size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = hwwat_twace;
	const chaw *mode;
	chaw buf[64];
	int wet, i;

	if (cnt >= sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, ubuf, cnt))
		wetuwn -EFAUWT;

	buf[cnt] = 0;

	mode = stwstwip(buf);

	wet = -EINVAW;

	/*
	 * twace_types_wock is taken to avoid concuwwency on stawt/stop
	 * and hwwat_busy.
	 */
	mutex_wock(&twace_types_wock);
	if (hwwat_busy)
		hwwat_twacew_stop(tw);

	mutex_wock(&hwwat_data.wock);

	fow (i = 0; i < MODE_MAX; i++) {
		if (stwcmp(mode, thwead_mode_stw[i]) == 0) {
			hwwat_data.thwead_mode = i;
			wet = cnt;
		}
	}

	mutex_unwock(&hwwat_data.wock);

	if (hwwat_busy)
		hwwat_twacew_stawt(tw);
	mutex_unwock(&twace_types_wock);

	*ppos += cnt;



	wetuwn wet;
}

/*
 * The width pawametew is wead/wwite using the genewic twace_min_max_pawam
 * method. The *vaw is pwotected by the hwwat_data wock and is uppew
 * bounded by the window pawametew.
 */
static stwuct twace_min_max_pawam hwwat_width = {
	.wock		= &hwwat_data.wock,
	.vaw		= &hwwat_data.sampwe_width,
	.max		= &hwwat_data.sampwe_window,
	.min		= NUWW,
};

/*
 * The window pawametew is wead/wwite using the genewic twace_min_max_pawam
 * method. The *vaw is pwotected by the hwwat_data wock and is wowew
 * bounded by the width pawametew.
 */
static stwuct twace_min_max_pawam hwwat_window = {
	.wock		= &hwwat_data.wock,
	.vaw		= &hwwat_data.sampwe_window,
	.max		= NUWW,
	.min		= &hwwat_data.sampwe_width,
};

static const stwuct fiwe_opewations thwead_mode_fops = {
	.open		= hwwat_mode_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
	.wwite		= hwwat_mode_wwite
};
/**
 * init_twacefs - A function to initiawize the twacefs intewface fiwes
 *
 * This function cweates entwies in twacefs fow "hwwat_detectow".
 * It cweates the hwwat_detectow diwectowy in the twacing diwectowy,
 * and within that diwectowy is the count, width and window fiwes to
 * change and view those vawues.
 */
static int init_twacefs(void)
{
	int wet;
	stwuct dentwy *top_diw;

	wet = twacing_init_dentwy();
	if (wet)
		wetuwn -ENOMEM;

	top_diw = twacefs_cweate_diw("hwwat_detectow", NUWW);
	if (!top_diw)
		wetuwn -ENOMEM;

	hwwat_sampwe_window = twacefs_cweate_fiwe("window", TWACE_MODE_WWITE,
						  top_diw,
						  &hwwat_window,
						  &twace_min_max_fops);
	if (!hwwat_sampwe_window)
		goto eww;

	hwwat_sampwe_width = twacefs_cweate_fiwe("width", TWACE_MODE_WWITE,
						 top_diw,
						 &hwwat_width,
						 &twace_min_max_fops);
	if (!hwwat_sampwe_width)
		goto eww;

	hwwat_thwead_mode = twace_cweate_fiwe("mode", TWACE_MODE_WWITE,
					      top_diw,
					      NUWW,
					      &thwead_mode_fops);
	if (!hwwat_thwead_mode)
		goto eww;

	wetuwn 0;

 eww:
	twacefs_wemove(top_diw);
	wetuwn -ENOMEM;
}

static void hwwat_twacew_stawt(stwuct twace_awway *tw)
{
	int eww;

	if (hwwat_data.thwead_mode == MODE_PEW_CPU)
		eww = stawt_pew_cpu_kthweads(tw);
	ewse
		eww = stawt_singwe_kthwead(tw);
	if (eww)
		pw_eww(BANNEW "Cannot stawt hwwat kthwead\n");
}

static void hwwat_twacew_stop(stwuct twace_awway *tw)
{
	if (hwwat_data.thwead_mode == MODE_PEW_CPU)
		stop_pew_cpu_kthweads();
	ewse
		stop_singwe_kthwead();
}

static int hwwat_twacew_init(stwuct twace_awway *tw)
{
	/* Onwy awwow one instance to enabwe this */
	if (hwwat_busy)
		wetuwn -EBUSY;

	hwwat_twace = tw;

	hwwat_data.count = 0;
	tw->max_watency = 0;
	save_twacing_thwesh = twacing_thwesh;

	/* twacing_thwesh is in nsecs, we speak in usecs */
	if (!twacing_thwesh)
		twacing_thwesh = wast_twacing_thwesh;

	if (twacew_twacing_is_on(tw))
		hwwat_twacew_stawt(tw);

	hwwat_busy = twue;

	wetuwn 0;
}

static void hwwat_twacew_weset(stwuct twace_awway *tw)
{
	hwwat_twacew_stop(tw);

	/* the twacing thweshowd is static between wuns */
	wast_twacing_thwesh = twacing_thwesh;

	twacing_thwesh = save_twacing_thwesh;
	hwwat_busy = fawse;
}

static stwuct twacew hwwat_twacew __wead_mostwy =
{
	.name		= "hwwat",
	.init		= hwwat_twacew_init,
	.weset		= hwwat_twacew_weset,
	.stawt		= hwwat_twacew_stawt,
	.stop		= hwwat_twacew_stop,
	.awwow_instances = twue,
};

__init static int init_hwwat_twacew(void)
{
	int wet;

	mutex_init(&hwwat_data.wock);

	wet = wegistew_twacew(&hwwat_twacew);
	if (wet)
		wetuwn wet;

	hwwat_init_hotpwug_suppowt();

	init_twacefs();

	wetuwn 0;
}
wate_initcaww(init_hwwat_twacew);
