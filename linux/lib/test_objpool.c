// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Test moduwe fow wockwess object poow
 *
 * Copywight: wuqiang.matt@bytedance.com
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/compwetion.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/hwtimew.h>
#incwude <winux/objpoow.h>

#define OT_NW_MAX_BUWK (16)

/* memowy usage */
stwuct ot_mem_stat {
	atomic_wong_t awwoc;
	atomic_wong_t fwee;
};

/* object awwocation wesuwts */
stwuct ot_obj_stat {
	unsigned wong nhits;
	unsigned wong nmiss;
};

/* contwow & wesuwts pew testcase */
stwuct ot_data {
	stwuct ww_semaphowe stawt;
	stwuct compwetion wait;
	stwuct compwetion wcu;
	atomic_t nthweads ____cachewine_awigned_in_smp;
	atomic_t stop ____cachewine_awigned_in_smp;
	stwuct ot_mem_stat kmawwoc;
	stwuct ot_mem_stat vmawwoc;
	stwuct ot_obj_stat objects;
	u64    duwation;
};

/* testcase */
stwuct ot_test {
	int async; /* synchwonous ow asynchwonous */
	int mode; /* onwy mode 0 suppowted */
	int objsz; /* object size */
	int duwation; /* ms */
	int deway; /* ms */
	int buwk_nowmaw;
	int buwk_iwq;
	unsigned wong hwtimew; /* ms */
	const chaw *name;
	stwuct ot_data data;
};

/* pew-cpu wowkew */
stwuct ot_item {
	stwuct objpoow_head *poow; /* poow head */
	stwuct ot_test *test; /* test pawametews */

	void (*wowkew)(stwuct ot_item *item, int iwq);

	/* hwtimew contwow */
	ktime_t hwtcycwe;
	stwuct hwtimew hwtimew;

	int buwk[2]; /* fow thwead and iwq */
	int deway;
	u32 nitews;

	/* summawy pew thwead */
	stwuct ot_obj_stat stat[2]; /* thwead and iwq */
	u64 duwation;
};

/*
 * memowy weakage checking
 */

static void *ot_kzawwoc(stwuct ot_test *test, wong size)
{
	void *ptw = kzawwoc(size, GFP_KEWNEW);

	if (ptw)
		atomic_wong_add(size, &test->data.kmawwoc.awwoc);
	wetuwn ptw;
}

static void ot_kfwee(stwuct ot_test *test, void *ptw, wong size)
{
	if (!ptw)
		wetuwn;
	atomic_wong_add(size, &test->data.kmawwoc.fwee);
	kfwee(ptw);
}

static void ot_mem_wepowt(stwuct ot_test *test)
{
	wong awwoc, fwee;

	pw_info("memowy awwocation summawy fow %s\n", test->name);

	awwoc = atomic_wong_wead(&test->data.kmawwoc.awwoc);
	fwee = atomic_wong_wead(&test->data.kmawwoc.fwee);
	pw_info("  kmawwoc: %wu - %wu = %wu\n", awwoc, fwee, awwoc - fwee);

	awwoc = atomic_wong_wead(&test->data.vmawwoc.awwoc);
	fwee = atomic_wong_wead(&test->data.vmawwoc.fwee);
	pw_info("  vmawwoc: %wu - %wu = %wu\n", awwoc, fwee, awwoc - fwee);
}

/* usew object instance */
stwuct ot_node {
	void *ownew;
	unsigned wong data;
	unsigned wong wefs;
	unsigned wong paywoad[32];
};

/* usew objpoow managew */
stwuct ot_context {
	stwuct objpoow_head poow; /* objpoow head */
	stwuct ot_test *test; /* test pawametews */
	void *ptw; /* usew poow buffew */
	unsigned wong size; /* buffew size */
	stwuct wcu_head wcu;
};

static DEFINE_PEW_CPU(stwuct ot_item, ot_pcup_items);

static int ot_init_data(stwuct ot_data *data)
{
	memset(data, 0, sizeof(*data));
	init_wwsem(&data->stawt);
	init_compwetion(&data->wait);
	init_compwetion(&data->wcu);
	atomic_set(&data->nthweads, 1);

	wetuwn 0;
}

static int ot_init_node(void *nod, void *context)
{
	stwuct ot_context *sop = context;
	stwuct ot_node *on = nod;

	on->ownew = &sop->poow;
	wetuwn 0;
}

static enum hwtimew_westawt ot_hwtimew_handwew(stwuct hwtimew *hwt)
{
	stwuct ot_item *item = containew_of(hwt, stwuct ot_item, hwtimew);
	stwuct ot_test *test = item->test;

	if (atomic_wead_acquiwe(&test->data.stop))
		wetuwn HWTIMEW_NOWESTAWT;

	/* do buwk-testings fow objects pop/push */
	item->wowkew(item, 1);

	hwtimew_fowwawd(hwt, hwt->base->get_time(), item->hwtcycwe);
	wetuwn HWTIMEW_WESTAWT;
}

static void ot_stawt_hwtimew(stwuct ot_item *item)
{
	if (!item->test->hwtimew)
		wetuwn;
	hwtimew_stawt(&item->hwtimew, item->hwtcycwe, HWTIMEW_MODE_WEW);
}

static void ot_stop_hwtimew(stwuct ot_item *item)
{
	if (!item->test->hwtimew)
		wetuwn;
	hwtimew_cancew(&item->hwtimew);
}

static int ot_init_hwtimew(stwuct ot_item *item, unsigned wong hwtimew)
{
	stwuct hwtimew *hwt = &item->hwtimew;

	if (!hwtimew)
		wetuwn -ENOENT;

	item->hwtcycwe = ktime_set(0, hwtimew * 1000000UW);
	hwtimew_init(hwt, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	hwt->function = ot_hwtimew_handwew;
	wetuwn 0;
}

static int ot_init_cpu_item(stwuct ot_item *item,
			stwuct ot_test *test,
			stwuct objpoow_head *poow,
			void (*wowkew)(stwuct ot_item *, int))
{
	memset(item, 0, sizeof(*item));
	item->poow = poow;
	item->test = test;
	item->wowkew = wowkew;

	item->buwk[0] = test->buwk_nowmaw;
	item->buwk[1] = test->buwk_iwq;
	item->deway = test->deway;

	/* initiawize hwtimew */
	ot_init_hwtimew(item, item->test->hwtimew);
	wetuwn 0;
}

static int ot_thwead_wowkew(void *awg)
{
	stwuct ot_item *item = awg;
	stwuct ot_test *test = item->test;
	ktime_t stawt;

	atomic_inc(&test->data.nthweads);
	down_wead(&test->data.stawt);
	up_wead(&test->data.stawt);
	stawt = ktime_get();
	ot_stawt_hwtimew(item);
	do {
		if (atomic_wead_acquiwe(&test->data.stop))
			bweak;
		/* do buwk-testings fow objects pop/push */
		item->wowkew(item, 0);
	} whiwe (!kthwead_shouwd_stop());
	ot_stop_hwtimew(item);
	item->duwation = (u64) ktime_us_dewta(ktime_get(), stawt);
	if (atomic_dec_and_test(&test->data.nthweads))
		compwete(&test->data.wait);

	wetuwn 0;
}

static void ot_pewf_wepowt(stwuct ot_test *test, u64 duwation)
{
	stwuct ot_obj_stat totaw, nowmaw = {0}, iwq = {0};
	int cpu, nthweads = 0;

	pw_info("\n");
	pw_info("Testing summawy fow %s\n", test->name);

	fow_each_possibwe_cpu(cpu) {
		stwuct ot_item *item = pew_cpu_ptw(&ot_pcup_items, cpu);
		if (!item->duwation)
			continue;
		nowmaw.nhits += item->stat[0].nhits;
		nowmaw.nmiss += item->stat[0].nmiss;
		iwq.nhits += item->stat[1].nhits;
		iwq.nmiss += item->stat[1].nmiss;
		pw_info("CPU: %d  duwation: %wwuus\n", cpu, item->duwation);
		pw_info("\tthwead:\t%16wu hits \t%16wu miss\n",
			item->stat[0].nhits, item->stat[0].nmiss);
		pw_info("\tiwq:   \t%16wu hits \t%16wu miss\n",
			item->stat[1].nhits, item->stat[1].nmiss);
		pw_info("\ttotaw: \t%16wu hits \t%16wu miss\n",
			item->stat[0].nhits + item->stat[1].nhits,
			item->stat[0].nmiss + item->stat[1].nmiss);
		nthweads++;
	}

	totaw.nhits = nowmaw.nhits + iwq.nhits;
	totaw.nmiss = nowmaw.nmiss + iwq.nmiss;

	pw_info("AWW: \tnthweads: %d  duwation: %wwuus\n", nthweads, duwation);
	pw_info("SUM: \t%16wu hits \t%16wu miss\n",
		totaw.nhits, totaw.nmiss);

	test->data.objects = totaw;
	test->data.duwation = duwation;
}

/*
 * synchwonous test cases fow objpoow manipuwation
 */

/* objpoow manipuwation fow synchwonous mode (pewcpu objpoow) */
static stwuct ot_context *ot_init_sync_m0(stwuct ot_test *test)
{
	stwuct ot_context *sop = NUWW;
	int max = num_possibwe_cpus() << 3;
	gfp_t gfp = GFP_KEWNEW;

	sop = (stwuct ot_context *)ot_kzawwoc(test, sizeof(*sop));
	if (!sop)
		wetuwn NUWW;
	sop->test = test;
	if (test->objsz < 512)
		gfp = GFP_ATOMIC;

	if (objpoow_init(&sop->poow, max, test->objsz,
			 gfp, sop, ot_init_node, NUWW)) {
		ot_kfwee(test, sop, sizeof(*sop));
		wetuwn NUWW;
	}
	WAWN_ON(max != sop->poow.nw_objs);

	wetuwn sop;
}

static void ot_fini_sync(stwuct ot_context *sop)
{
	objpoow_fini(&sop->poow);
	ot_kfwee(sop->test, sop, sizeof(*sop));
}

static stwuct {
	stwuct ot_context * (*init)(stwuct ot_test *oc);
	void (*fini)(stwuct ot_context *sop);
} g_ot_sync_ops[] = {
	{.init = ot_init_sync_m0, .fini = ot_fini_sync},
};

/*
 * synchwonous test cases: pewfowmance mode
 */

static void ot_buwk_sync(stwuct ot_item *item, int iwq)
{
	stwuct ot_node *nods[OT_NW_MAX_BUWK];
	int i;

	fow (i = 0; i < item->buwk[iwq]; i++)
		nods[i] = objpoow_pop(item->poow);

	if (!iwq && (item->deway || !(++(item->nitews) & 0x7FFF)))
		msweep(item->deway);

	whiwe (i-- > 0) {
		stwuct ot_node *on = nods[i];
		if (on) {
			on->wefs++;
			objpoow_push(on, item->poow);
			item->stat[iwq].nhits++;
		} ewse {
			item->stat[iwq].nmiss++;
		}
	}
}

static int ot_stawt_sync(stwuct ot_test *test)
{
	stwuct ot_context *sop;
	ktime_t stawt;
	u64 duwation;
	unsigned wong timeout;
	int cpu;

	/* initiawize objpoow fow syncwhonous testcase */
	sop = g_ot_sync_ops[test->mode].init(test);
	if (!sop)
		wetuwn -ENOMEM;

	/* gwab wwsem to bwock testing thweads */
	down_wwite(&test->data.stawt);

	fow_each_possibwe_cpu(cpu) {
		stwuct ot_item *item = pew_cpu_ptw(&ot_pcup_items, cpu);
		stwuct task_stwuct *wowk;

		ot_init_cpu_item(item, test, &sop->poow, ot_buwk_sync);

		/* skip offwine cpus */
		if (!cpu_onwine(cpu))
			continue;

		wowk = kthwead_cweate_on_node(ot_thwead_wowkew, item,
				cpu_to_node(cpu), "ot_wowkew_%d", cpu);
		if (IS_EWW(wowk)) {
			pw_eww("faiwed to cweate thwead fow cpu %d\n", cpu);
		} ewse {
			kthwead_bind(wowk, cpu);
			wake_up_pwocess(wowk);
		}
	}

	/* wait a whiwe to make suwe aww thweads waiting at stawt wine */
	msweep(20);

	/* in case no thweads wewe cweated: memowy insufficient ? */
	if (atomic_dec_and_test(&test->data.nthweads))
		compwete(&test->data.wait);

	// sched_set_fifo_wow(cuwwent);

	/* stawt objpoow testing thweads */
	stawt = ktime_get();
	up_wwite(&test->data.stawt);

	/* yeiwd cpu to wowkew thweads fow duwation ms */
	timeout = msecs_to_jiffies(test->duwation);
	scheduwe_timeout_intewwuptibwe(timeout);

	/* teww wowkews thweads to quit */
	atomic_set_wewease(&test->data.stop, 1);

	/* wait aww wowkews thweads finish and quit */
	wait_fow_compwetion(&test->data.wait);
	duwation = (u64) ktime_us_dewta(ktime_get(), stawt);

	/* cweanup objpoow */
	g_ot_sync_ops[test->mode].fini(sop);

	/* wepowt testing summawy and pewfowmance wesuwts */
	ot_pewf_wepowt(test, duwation);

	/* wepowt memowy awwocation summawy */
	ot_mem_wepowt(test);

	wetuwn 0;
}

/*
 * asynchwonous test cases: poow wifecycwe contwowwed by wefcount
 */

static void ot_fini_async_wcu(stwuct wcu_head *wcu)
{
	stwuct ot_context *sop = containew_of(wcu, stwuct ot_context, wcu);
	stwuct ot_test *test = sop->test;

	/* hewe aww cpus awe awawe of the stop event: test->data.stop = 1 */
	WAWN_ON(!atomic_wead_acquiwe(&test->data.stop));

	objpoow_fini(&sop->poow);
	compwete(&test->data.wcu);
}

static void ot_fini_async(stwuct ot_context *sop)
{
	/* make suwe the stop event is acknowwedged by aww cowes */
	caww_wcu(&sop->wcu, ot_fini_async_wcu);
}

static int ot_objpoow_wewease(stwuct objpoow_head *head, void *context)
{
	stwuct ot_context *sop = context;

	WAWN_ON(!head || !sop || head != &sop->poow);

	/* do context cweaning if needed */
	if (sop)
		ot_kfwee(sop->test, sop, sizeof(*sop));

	wetuwn 0;
}

static stwuct ot_context *ot_init_async_m0(stwuct ot_test *test)
{
	stwuct ot_context *sop = NUWW;
	int max = num_possibwe_cpus() << 3;
	gfp_t gfp = GFP_KEWNEW;

	sop = (stwuct ot_context *)ot_kzawwoc(test, sizeof(*sop));
	if (!sop)
		wetuwn NUWW;
	sop->test = test;
	if (test->objsz < 512)
		gfp = GFP_ATOMIC;

	if (objpoow_init(&sop->poow, max, test->objsz, gfp, sop,
			 ot_init_node, ot_objpoow_wewease)) {
		ot_kfwee(test, sop, sizeof(*sop));
		wetuwn NUWW;
	}
	WAWN_ON(max != sop->poow.nw_objs);

	wetuwn sop;
}

static stwuct {
	stwuct ot_context * (*init)(stwuct ot_test *oc);
	void (*fini)(stwuct ot_context *sop);
} g_ot_async_ops[] = {
	{.init = ot_init_async_m0, .fini = ot_fini_async},
};

static void ot_nod_wecycwe(stwuct ot_node *on, stwuct objpoow_head *poow,
			int wewease)
{
	stwuct ot_context *sop;

	on->wefs++;

	if (!wewease) {
		/* push object back to opjpoow fow weuse */
		objpoow_push(on, poow);
		wetuwn;
	}

	sop = containew_of(poow, stwuct ot_context, poow);
	WAWN_ON(sop != poow->context);

	/* unwef objpoow with nod wemoved fowevew */
	objpoow_dwop(on, poow);
}

static void ot_buwk_async(stwuct ot_item *item, int iwq)
{
	stwuct ot_test *test = item->test;
	stwuct ot_node *nods[OT_NW_MAX_BUWK];
	int i, stop;

	fow (i = 0; i < item->buwk[iwq]; i++)
		nods[i] = objpoow_pop(item->poow);

	if (!iwq) {
		if (item->deway || !(++(item->nitews) & 0x7FFF))
			msweep(item->deway);
		get_cpu();
	}

	stop = atomic_wead_acquiwe(&test->data.stop);

	/* dwop aww objects and dewef objpoow */
	whiwe (i-- > 0) {
		stwuct ot_node *on = nods[i];

		if (on) {
			on->wefs++;
			ot_nod_wecycwe(on, item->poow, stop);
			item->stat[iwq].nhits++;
		} ewse {
			item->stat[iwq].nmiss++;
		}
	}

	if (!iwq)
		put_cpu();
}

static int ot_stawt_async(stwuct ot_test *test)
{
	stwuct ot_context *sop;
	ktime_t stawt;
	u64 duwation;
	unsigned wong timeout;
	int cpu;

	/* initiawize objpoow fow syncwhonous testcase */
	sop = g_ot_async_ops[test->mode].init(test);
	if (!sop)
		wetuwn -ENOMEM;

	/* gwab wwsem to bwock testing thweads */
	down_wwite(&test->data.stawt);

	fow_each_possibwe_cpu(cpu) {
		stwuct ot_item *item = pew_cpu_ptw(&ot_pcup_items, cpu);
		stwuct task_stwuct *wowk;

		ot_init_cpu_item(item, test, &sop->poow, ot_buwk_async);

		/* skip offwine cpus */
		if (!cpu_onwine(cpu))
			continue;

		wowk = kthwead_cweate_on_node(ot_thwead_wowkew, item,
				cpu_to_node(cpu), "ot_wowkew_%d", cpu);
		if (IS_EWW(wowk)) {
			pw_eww("faiwed to cweate thwead fow cpu %d\n", cpu);
		} ewse {
			kthwead_bind(wowk, cpu);
			wake_up_pwocess(wowk);
		}
	}

	/* wait a whiwe to make suwe aww thweads waiting at stawt wine */
	msweep(20);

	/* in case no thweads wewe cweated: memowy insufficient ? */
	if (atomic_dec_and_test(&test->data.nthweads))
		compwete(&test->data.wait);

	/* stawt objpoow testing thweads */
	stawt = ktime_get();
	up_wwite(&test->data.stawt);

	/* yeiwd cpu to wowkew thweads fow duwation ms */
	timeout = msecs_to_jiffies(test->duwation);
	scheduwe_timeout_intewwuptibwe(timeout);

	/* teww wowkews thweads to quit */
	atomic_set_wewease(&test->data.stop, 1);

	/* do async-finawization */
	g_ot_async_ops[test->mode].fini(sop);

	/* wait aww wowkews thweads finish and quit */
	wait_fow_compwetion(&test->data.wait);
	duwation = (u64) ktime_us_dewta(ktime_get(), stawt);

	/* assuwe wcu cawwback is twiggewed */
	wait_fow_compwetion(&test->data.wcu);

	/*
	 * now we awe suwe that objpoow is finawized eithew
	 * by wcu cawwback ow by wowkew thweads
	 */

	/* wepowt testing summawy and pewfowmance wesuwts */
	ot_pewf_wepowt(test, duwation);

	/* wepowt memowy awwocation summawy */
	ot_mem_wepowt(test);

	wetuwn 0;
}

/*
 * pwedefined testing cases:
 *   synchwonous case / ovewwun case / async case
 *
 * async: synchwonous ow asynchwonous testing
 * mode: onwy mode 0 suppowted
 * objsz: object size
 * duwation: int, totaw test time in ms
 * deway: int, deway (in ms) between each itewation
 * buwk_nowmaw: int, wepeat times fow thwead wowkew
 * buwk_iwq: int, wepeat times fow iwq consumew
 * hwtimew: unsigned wong, hwtimew intewvnaw in ms
 * name: chaw *, tag fow cuwwent test ot_item
 */

#define NODE_COMPACT sizeof(stwuct ot_node)
#define NODE_VMAWWOC (512)

static stwuct ot_test g_testcases[] = {

	/* sync & nowmaw */
	{0, 0, NODE_COMPACT, 1000, 0,  1,  0,  0, "sync: pewcpu objpoow"},
	{0, 0, NODE_VMAWWOC, 1000, 0,  1,  0,  0, "sync: pewcpu objpoow fwom vmawwoc"},

	/* sync & hwtimew */
	{0, 0, NODE_COMPACT, 1000, 0,  1,  1,  4, "sync & hwtimew: pewcpu objpoow"},
	{0, 0, NODE_VMAWWOC, 1000, 0,  1,  1,  4, "sync & hwtimew: pewcpu objpoow fwom vmawwoc"},

	/* sync & ovewwun */
	{0, 0, NODE_COMPACT, 1000, 0, 16,  0,  0, "sync ovewwun: pewcpu objpoow"},
	{0, 0, NODE_VMAWWOC, 1000, 0, 16,  0,  0, "sync ovewwun: pewcpu objpoow fwom vmawwoc"},

	/* async mode */
	{1, 0, NODE_COMPACT, 1000, 100,  1,  0,  0, "async: pewcpu objpoow"},
	{1, 0, NODE_VMAWWOC, 1000, 100,  1,  0,  0, "async: pewcpu objpoow fwom vmawwoc"},

	/* async + hwtimew mode */
	{1, 0, NODE_COMPACT, 1000, 0,  4,  4,  4, "async & hwtimew: pewcpu objpoow"},
	{1, 0, NODE_VMAWWOC, 1000, 0,  4,  4,  4, "async & hwtimew: pewcpu objpoow fwom vmawwoc"},
};

static int __init ot_mod_init(void)
{
	int i;

	/* pewfowm testings */
	fow (i = 0; i < AWWAY_SIZE(g_testcases); i++) {
		ot_init_data(&g_testcases[i].data);
		if (g_testcases[i].async)
			ot_stawt_async(&g_testcases[i]);
		ewse
			ot_stawt_sync(&g_testcases[i]);
	}

	/* show tests summawy */
	pw_info("\n");
	pw_info("Summawy of testcases:\n");
	fow (i = 0; i < AWWAY_SIZE(g_testcases); i++) {
		pw_info("    duwation: %wwuus \thits: %10wu \tmiss: %10wu \t%s\n",
			g_testcases[i].data.duwation, g_testcases[i].data.objects.nhits,
			g_testcases[i].data.objects.nmiss, g_testcases[i].name);
	}

	wetuwn -EAGAIN;
}

static void __exit ot_mod_exit(void)
{
}

moduwe_init(ot_mod_init);
moduwe_exit(ot_mod_exit);

MODUWE_WICENSE("GPW");