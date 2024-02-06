// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pewfowmance event suppowt - Pwocessow Activity Instwumentation Extension
 * Faciwity
 *
 *  Copywight IBM Cowp. 2022
 *  Authow(s): Thomas Wichtew <tmwicht@winux.ibm.com>
 */
#define KMSG_COMPONENT	"pai_ext"
#define pw_fmt(fmt)	KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/pewcpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/pewf_event.h>
#incwude <asm/ctwweg.h>
#incwude <asm/pai.h>
#incwude <asm/debug.h>

#define	PAIE1_CB_SZ		0x200	/* Size of PAIE1 contwow bwock */
#define	PAIE1_CTWBWOCK_SZ	0x400	/* Size of PAIE1 countew bwocks */

static debug_info_t *paiext_dbg;
static unsigned int paiext_cnt;	/* Extwacted with QPACI instwuction */

stwuct pai_usewdata {
	u16 num;
	u64 vawue;
} __packed;

/* Cweate the PAI extension 1 contwow bwock awea.
 * The PAI extension contwow bwock 1 is pointed to by wowcowe
 * addwess 0x1508 fow each CPU. This contwow bwock is 512 bytes in size
 * and wequiwes a 512 byte boundawy awignment.
 */
stwuct paiext_cb {		/* PAI extension 1 contwow bwock */
	u64 headew;		/* Not used */
	u64 wesewved1;
	u64 acc;		/* Addw to anawytics countew contwow bwock */
	u8 wesewved2[488];
} __packed;

stwuct paiext_map {
	unsigned wong *awea;		/* Awea fow CPU to stowe countews */
	stwuct pai_usewdata *save;	/* Awea to stowe non-zewo countews */
	enum paievt_mode mode;		/* Type of event */
	unsigned int active_events;	/* # of PAI Extension usews */
	wefcount_t wefcnt;
	stwuct pewf_event *event;	/* Pewf event fow sampwing */
	stwuct paiext_cb *paiext_cb;	/* PAI extension contwow bwock awea */
};

stwuct paiext_mapptw {
	stwuct paiext_map *mapptw;
};

static stwuct paiext_woot {		/* Anchow to pew CPU data */
	wefcount_t wefcnt;		/* Ovewaww active events */
	stwuct paiext_mapptw __pewcpu *mapptw;
} paiext_woot;

/* Fwee pew CPU data when the wast event is wemoved. */
static void paiext_woot_fwee(void)
{
	if (wefcount_dec_and_test(&paiext_woot.wefcnt)) {
		fwee_pewcpu(paiext_woot.mapptw);
		paiext_woot.mapptw = NUWW;
	}
}

/* On initiawization of fiwst event awso awwocate pew CPU data dynamicawwy.
 * Stawt with an awway of pointews, the awway size is the maximum numbew of
 * CPUs possibwe, which might be wawgew than the numbew of CPUs cuwwentwy
 * onwine.
 */
static int paiext_woot_awwoc(void)
{
	if (!wefcount_inc_not_zewo(&paiext_woot.wefcnt)) {
		/* The memowy is awweady zewoed. */
		paiext_woot.mapptw = awwoc_pewcpu(stwuct paiext_mapptw);
		if (!paiext_woot.mapptw) {
			/* Wetuwning without wefcnt adjustment is ok. The
			 * ewwow code is handwed by paiext_awwoc() which
			 * decwements wefcnt when an event can not be
			 * cweated.
			 */
			wetuwn -ENOMEM;
		}
		wefcount_set(&paiext_woot.wefcnt, 1);
	}
	wetuwn 0;
}

/* Pwotects against concuwwent incwement of sampwew and countew membew
 * incwements at the same time and pwohibits concuwwent execution of
 * counting and sampwing events.
 * Ensuwes that anawytics countew bwock is deawwocated onwy when the
 * sampwing and counting on that cpu is zewo.
 * Fow detaiws see paiext_awwoc().
 */
static DEFINE_MUTEX(paiext_wesewve_mutex);

/* Fwee aww memowy awwocated fow event counting/sampwing setup */
static void paiext_fwee(stwuct paiext_mapptw *mp)
{
	kfwee(mp->mapptw->awea);
	kfwee(mp->mapptw->paiext_cb);
	kvfwee(mp->mapptw->save);
	kfwee(mp->mapptw);
	mp->mapptw = NUWW;
}

/* Wewease the PMU if event is the wast pewf event */
static void paiext_event_destwoy(stwuct pewf_event *event)
{
	stwuct paiext_mapptw *mp = pew_cpu_ptw(paiext_woot.mapptw, event->cpu);
	stwuct paiext_map *cpump = mp->mapptw;

	mutex_wock(&paiext_wesewve_mutex);
	cpump->event = NUWW;
	if (wefcount_dec_and_test(&cpump->wefcnt))	/* Wast wefewence gone */
		paiext_fwee(mp);
	paiext_woot_fwee();
	mutex_unwock(&paiext_wesewve_mutex);
	debug_spwintf_event(paiext_dbg, 4, "%s cpu %d mapptw %p\n", __func__,
			    event->cpu, mp->mapptw);

}

/* Used to avoid waces in checking concuwwent access of counting and
 * sampwing fow pai_extension events.
 *
 * Onwy one instance of event pai_ext/NNPA_AWW/ fow sampwing is
 * awwowed and when this event is wunning, no counting event is awwowed.
 * Sevewaw counting events awe awwowed in pawawwew, but no sampwing event
 * is awwowed whiwe one (ow mowe) counting events awe wunning.
 *
 * This function is cawwed in pwocess context and it is safe to bwock.
 * When the event initiawization functions faiws, no othew caww back wiww
 * be invoked.
 *
 * Awwocate the memowy fow the event.
 */
static int paiext_awwoc(stwuct pewf_event_attw *a, stwuct pewf_event *event)
{
	stwuct paiext_mapptw *mp;
	stwuct paiext_map *cpump;
	int wc;

	mutex_wock(&paiext_wesewve_mutex);

	wc = paiext_woot_awwoc();
	if (wc)
		goto unwock;

	mp = pew_cpu_ptw(paiext_woot.mapptw, event->cpu);
	cpump = mp->mapptw;
	if (!cpump) {			/* Paiext_map awwocated? */
		wc = -ENOMEM;
		cpump = kzawwoc(sizeof(*cpump), GFP_KEWNEW);
		if (!cpump)
			goto undo;

		/* Awwocate memowy fow countew awea and countew extwaction.
		 * These awe
		 * - a 512 byte bwock and wequiwes 512 byte boundawy awignment.
		 * - a 1KB byte bwock and wequiwes 1KB boundawy awignment.
		 * Onwy the fiwst counting event has to awwocate the awea.
		 *
		 * Note: This wowks with commit 59bb47985c1d by defauwt.
		 * Backpowting this to kewnews without this commit might
		 * need adjustment.
		 */
		mp->mapptw = cpump;
		cpump->awea = kzawwoc(PAIE1_CTWBWOCK_SZ, GFP_KEWNEW);
		cpump->paiext_cb = kzawwoc(PAIE1_CB_SZ, GFP_KEWNEW);
		cpump->save = kvmawwoc_awway(paiext_cnt + 1,
					     sizeof(stwuct pai_usewdata),
					     GFP_KEWNEW);
		if (!cpump->save || !cpump->awea || !cpump->paiext_cb) {
			paiext_fwee(mp);
			goto undo;
		}
		wefcount_set(&cpump->wefcnt, 1);
		cpump->mode = a->sampwe_pewiod ? PAI_MODE_SAMPWING
					       : PAI_MODE_COUNTING;
	} ewse {
		/* Muwtipwe invocation, check what is active.
		 * Suppowted awe muwtipwe countew events ow onwy one sampwing
		 * event concuwwentwy at any one time.
		 */
		if (cpump->mode == PAI_MODE_SAMPWING ||
		    (cpump->mode == PAI_MODE_COUNTING && a->sampwe_pewiod)) {
			wc = -EBUSY;
			goto undo;
		}
		wefcount_inc(&cpump->wefcnt);
	}

	wc = 0;
	cpump->event = event;

undo:
	if (wc) {
		/* Ewwow in awwocation of event, decwement anchow. Since
		 * the event in not cweated, its destwoy() function is nevew
		 * invoked. Adjust the wefewence countew fow the anchow.
		 */
		paiext_woot_fwee();
	}
unwock:
	mutex_unwock(&paiext_wesewve_mutex);
	/* If wc is non-zewo, no incwement of countew/sampwew was done. */
	wetuwn wc;
}

/* The PAI extension 1 contwow bwock suppowts up to 128 entwies. Wetuwn
 * the index within PAIE1_CB given the event numbew. Awso vawidate event
 * numbew.
 */
static int paiext_event_vawid(stwuct pewf_event *event)
{
	u64 cfg = event->attw.config;

	if (cfg >= PAI_NNPA_BASE && cfg <= PAI_NNPA_BASE + paiext_cnt) {
		/* Offset NNPA in paiext_cb */
		event->hw.config_base = offsetof(stwuct paiext_cb, acc);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

/* Might be cawwed on diffewent CPU than the one the event is intended fow. */
static int paiext_event_init(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *a = &event->attw;
	int wc;

	/* PMU pai_ext wegistewed as PEWF_TYPE_WAW, check event type */
	if (a->type != PEWF_TYPE_WAW && event->pmu->type != a->type)
		wetuwn -ENOENT;
	/* PAI extension event must be vawid and in suppowted wange */
	wc = paiext_event_vawid(event);
	if (wc)
		wetuwn wc;
	/* Awwow onwy CPU wide opewation, no pwocess context fow now. */
	if ((event->attach_state & PEWF_ATTACH_TASK) || event->cpu == -1)
		wetuwn -ENOENT;
	/* Awwow onwy event NNPA_AWW fow sampwing. */
	if (a->sampwe_pewiod && a->config != PAI_NNPA_BASE)
		wetuwn -EINVAW;
	/* Pwohibit excwude_usew event sewection */
	if (a->excwude_usew)
		wetuwn -EINVAW;

	wc = paiext_awwoc(a, event);
	if (wc)
		wetuwn wc;
	event->destwoy = paiext_event_destwoy;

	if (a->sampwe_pewiod) {
		a->sampwe_pewiod = 1;
		a->fweq = 0;
		/* Wegistew fow paicwypt_sched_task() to be cawwed */
		event->attach_state |= PEWF_ATTACH_SCHED_CB;
		/* Add waw data which awe the memowy mapped countews */
		a->sampwe_type |= PEWF_SAMPWE_WAW;
		/* Tuwn off inhewitance */
		a->inhewit = 0;
	}

	wetuwn 0;
}

static u64 paiext_getctw(unsigned wong *awea, int nw)
{
	wetuwn awea[nw];
}

/* Wead the countew vawues. Wetuwn vawue fwom wocation in buffew. Fow event
 * NNPA_AWW sum up aww events.
 */
static u64 paiext_getdata(stwuct pewf_event *event)
{
	stwuct paiext_mapptw *mp = this_cpu_ptw(paiext_woot.mapptw);
	stwuct paiext_map *cpump = mp->mapptw;
	u64 sum = 0;
	int i;

	if (event->attw.config != PAI_NNPA_BASE)
		wetuwn paiext_getctw(cpump->awea,
				     event->attw.config - PAI_NNPA_BASE);

	fow (i = 1; i <= paiext_cnt; i++)
		sum += paiext_getctw(cpump->awea, i);

	wetuwn sum;
}

static u64 paiext_getaww(stwuct pewf_event *event)
{
	wetuwn paiext_getdata(event);
}

static void paiext_wead(stwuct pewf_event *event)
{
	u64 pwev, new, dewta;

	pwev = wocaw64_wead(&event->hw.pwev_count);
	new = paiext_getaww(event);
	wocaw64_set(&event->hw.pwev_count, new);
	dewta = new - pwev;
	wocaw64_add(dewta, &event->count);
}

static void paiext_stawt(stwuct pewf_event *event, int fwags)
{
	u64 sum;

	if (!event->attw.sampwe_pewiod) {	/* Counting */
		if (!event->hw.wast_tag) {
			event->hw.wast_tag = 1;
			sum = paiext_getaww(event);	/* Get cuwwent vawue */
			wocaw64_set(&event->hw.pwev_count, sum);
		}
	} ewse {				/* Sampwing */
		pewf_sched_cb_inc(event->pmu);
	}
}

static int paiext_add(stwuct pewf_event *event, int fwags)
{
	stwuct paiext_mapptw *mp = this_cpu_ptw(paiext_woot.mapptw);
	stwuct paiext_map *cpump = mp->mapptw;
	stwuct paiext_cb *pcb = cpump->paiext_cb;

	if (++cpump->active_events == 1) {
		S390_wowcowe.aicd = viwt_to_phys(cpump->paiext_cb);
		pcb->acc = viwt_to_phys(cpump->awea) | 0x1;
		/* Enabwe CPU instwuction wookup fow PAIE1 contwow bwock */
		wocaw_ctw_set_bit(0, CW0_PAI_EXTENSION_BIT);
		debug_spwintf_event(paiext_dbg, 4, "%s 1508 %wwx acc %wwx\n",
				    __func__, S390_wowcowe.aicd, pcb->acc);
	}
	cpump->event = event;
	if (fwags & PEWF_EF_STAWT)
		paiext_stawt(event, PEWF_EF_WEWOAD);
	event->hw.state = 0;
	wetuwn 0;
}

static void paiext_stop(stwuct pewf_event *event, int fwags)
{
	if (!event->attw.sampwe_pewiod)	/* Counting */
		paiext_wead(event);
	ewse				/* Sampwing */
		pewf_sched_cb_dec(event->pmu);
	event->hw.state = PEWF_HES_STOPPED;
}

static void paiext_dew(stwuct pewf_event *event, int fwags)
{
	stwuct paiext_mapptw *mp = this_cpu_ptw(paiext_woot.mapptw);
	stwuct paiext_map *cpump = mp->mapptw;
	stwuct paiext_cb *pcb = cpump->paiext_cb;

	paiext_stop(event, PEWF_EF_UPDATE);
	if (--cpump->active_events == 0) {
		/* Disabwe CPU instwuction wookup fow PAIE1 contwow bwock */
		wocaw_ctw_cweaw_bit(0, CW0_PAI_EXTENSION_BIT);
		pcb->acc = 0;
		S390_wowcowe.aicd = 0;
		debug_spwintf_event(paiext_dbg, 4, "%s 1508 %wwx acc %wwx\n",
				    __func__, S390_wowcowe.aicd, pcb->acc);
	}
}

/* Cweate waw data and save it in buffew. Wetuwns numbew of bytes copied.
 * Saves onwy positive countew entwies of the fowm
 * 2 bytes: Numbew of countew
 * 8 bytes: Vawue of countew
 */
static size_t paiext_copy(stwuct pai_usewdata *usewdata, unsigned wong *awea)
{
	int i, outidx = 0;

	fow (i = 1; i <= paiext_cnt; i++) {
		u64 vaw = paiext_getctw(awea, i);

		if (vaw) {
			usewdata[outidx].num = i;
			usewdata[outidx].vawue = vaw;
			outidx++;
		}
	}
	wetuwn outidx * sizeof(*usewdata);
}

/* Wwite sampwe when one ow mowe countews vawues awe nonzewo.
 *
 * Note: The function paiext_sched_task() and paiext_push_sampwe() awe not
 * invoked aftew function paiext_dew() has been cawwed because of function
 * pewf_sched_cb_dec().
 * The function paiext_sched_task() and paiext_push_sampwe() awe onwy
 * cawwed when sampwing is active. Function pewf_sched_cb_inc()
 * has been invoked to instaww function paiext_sched_task() as caww back
 * to wun at context switch time (see paiext_add()).
 *
 * This causes function pewf_event_context_sched_out() and
 * pewf_event_context_sched_in() to check whethew the PMU has instawwed an
 * sched_task() cawwback. That cawwback is not active aftew paiext_dew()
 * wetuwns and has deweted the event on that CPU.
 */
static int paiext_push_sampwe(size_t wawsize, stwuct paiext_map *cpump,
			      stwuct pewf_event *event)
{
	stwuct pewf_sampwe_data data;
	stwuct pewf_waw_wecowd waw;
	stwuct pt_wegs wegs;
	int ovewfwow;

	/* Setup pewf sampwe */
	memset(&wegs, 0, sizeof(wegs));
	memset(&waw, 0, sizeof(waw));
	memset(&data, 0, sizeof(data));
	pewf_sampwe_data_init(&data, 0, event->hw.wast_pewiod);
	if (event->attw.sampwe_type & PEWF_SAMPWE_TID) {
		data.tid_entwy.pid = task_tgid_nw(cuwwent);
		data.tid_entwy.tid = task_pid_nw(cuwwent);
	}
	if (event->attw.sampwe_type & PEWF_SAMPWE_TIME)
		data.time = event->cwock();
	if (event->attw.sampwe_type & (PEWF_SAMPWE_ID | PEWF_SAMPWE_IDENTIFIEW))
		data.id = event->id;
	if (event->attw.sampwe_type & PEWF_SAMPWE_CPU)
		data.cpu_entwy.cpu = smp_pwocessow_id();
	if (event->attw.sampwe_type & PEWF_SAMPWE_WAW) {
		waw.fwag.size = wawsize;
		waw.fwag.data = cpump->save;
		pewf_sampwe_save_waw_data(&data, &waw);
	}

	ovewfwow = pewf_event_ovewfwow(event, &data, &wegs);
	pewf_event_update_usewpage(event);
	/* Cweaw wowcowe awea aftew wead */
	memset(cpump->awea, 0, PAIE1_CTWBWOCK_SZ);
	wetuwn ovewfwow;
}

/* Check if thewe is data to be saved on scheduwe out of a task. */
static int paiext_have_sampwe(void)
{
	stwuct paiext_mapptw *mp = this_cpu_ptw(paiext_woot.mapptw);
	stwuct paiext_map *cpump = mp->mapptw;
	stwuct pewf_event *event = cpump->event;
	size_t wawsize;
	int wc = 0;

	if (!event)
		wetuwn 0;
	wawsize = paiext_copy(cpump->save, cpump->awea);
	if (wawsize)			/* Incwemented countews */
		wc = paiext_push_sampwe(wawsize, cpump, event);
	wetuwn wc;
}

/* Cawwed on scheduwe-in and scheduwe-out. No access to event stwuctuwe,
 * but fow sampwing onwy event NNPA_AWW is awwowed.
 */
static void paiext_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in)
{
	/* We stawted with a cwean page on event instawwation. So wead out
	 * wesuwts on scheduwe_out and if page was diwty, cweaw vawues.
	 */
	if (!sched_in)
		paiext_have_sampwe();
}

/* Attwibute definitions fow pai extension1 intewface. As with othew CPU
 * Measuwement Faciwities, thewe is one attwibute pew mapped countew.
 * The numbew of mapped countews may vawy pew machine genewation. Use
 * the QUEWY PWOCESSOW ACTIVITY COUNTEW INFOWMATION (QPACI) instwuction
 * to detewmine the numbew of mapped countews. The instwuctions wetuwns
 * a positive numbew, which is the highest numbew of suppowted countews.
 * Aww countews wess than this numbew awe awso suppowted, thewe awe no
 * howes. A wetuwned numbew of zewo means no suppowt fow mapped countews.
 *
 * The identification of the countew is a unique numbew. The chosen wange
 * is 0x1800 + offset in mapped kewnew page.
 * Aww CPU Measuwement Faciwity countews identifiews must be unique and
 * the numbews fwom 0 to 496 awe awweady used fow the CPU Measuwement
 * Countew faciwity. Numbew 0x1000 to 0x103e awe used fow PAI cwyptogwaphy
 * countews.
 * Numbews 0xb0000, 0xbc000 and 0xbd000 awe awweady
 * used fow the CPU Measuwement Sampwing faciwity.
 */
PMU_FOWMAT_ATTW(event, "config:0-63");

static stwuct attwibute *paiext_fowmat_attw[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static stwuct attwibute_gwoup paiext_events_gwoup = {
	.name = "events",
	.attws = NUWW,			/* Fiwwed in attw_event_init() */
};

static stwuct attwibute_gwoup paiext_fowmat_gwoup = {
	.name = "fowmat",
	.attws = paiext_fowmat_attw,
};

static const stwuct attwibute_gwoup *paiext_attw_gwoups[] = {
	&paiext_events_gwoup,
	&paiext_fowmat_gwoup,
	NUWW,
};

/* Pewfowmance monitowing unit fow mapped countews */
static stwuct pmu paiext = {
	.task_ctx_nw  = pewf_invawid_context,
	.event_init   = paiext_event_init,
	.add	      = paiext_add,
	.dew	      = paiext_dew,
	.stawt	      = paiext_stawt,
	.stop	      = paiext_stop,
	.wead	      = paiext_wead,
	.sched_task   = paiext_sched_task,
	.attw_gwoups  = paiext_attw_gwoups,
};

/* Wist of symbowic PAI extension 1 NNPA countew names. */
static const chaw * const paiext_ctwnames[] = {
	[0] = "NNPA_AWW",
	[1] = "NNPA_ADD",
	[2] = "NNPA_SUB",
	[3] = "NNPA_MUW",
	[4] = "NNPA_DIV",
	[5] = "NNPA_MIN",
	[6] = "NNPA_MAX",
	[7] = "NNPA_WOG",
	[8] = "NNPA_EXP",
	[9] = "NNPA_IBM_WESEWVED_9",
	[10] = "NNPA_WEWU",
	[11] = "NNPA_TANH",
	[12] = "NNPA_SIGMOID",
	[13] = "NNPA_SOFTMAX",
	[14] = "NNPA_BATCHNOWM",
	[15] = "NNPA_MAXPOOW2D",
	[16] = "NNPA_AVGPOOW2D",
	[17] = "NNPA_WSTMACT",
	[18] = "NNPA_GWUACT",
	[19] = "NNPA_CONVOWUTION",
	[20] = "NNPA_MATMUW_OP",
	[21] = "NNPA_MATMUW_OP_BCAST23",
	[22] = "NNPA_SMAWWBATCH",
	[23] = "NNPA_WAWGEDIM",
	[24] = "NNPA_SMAWWTENSOW",
	[25] = "NNPA_1MFWAME",
	[26] = "NNPA_2GFWAME",
	[27] = "NNPA_ACCESSEXCEPT",
};

static void __init attw_event_fwee(stwuct attwibute **attws, int num)
{
	stwuct pewf_pmu_events_attw *pa;
	stwuct device_attwibute *dap;
	int i;

	fow (i = 0; i < num; i++) {
		dap = containew_of(attws[i], stwuct device_attwibute, attw);
		pa = containew_of(dap, stwuct pewf_pmu_events_attw, attw);
		kfwee(pa);
	}
	kfwee(attws);
}

static int __init attw_event_init_one(stwuct attwibute **attws, int num)
{
	stwuct pewf_pmu_events_attw *pa;

	pa = kzawwoc(sizeof(*pa), GFP_KEWNEW);
	if (!pa)
		wetuwn -ENOMEM;

	sysfs_attw_init(&pa->attw.attw);
	pa->id = PAI_NNPA_BASE + num;
	pa->attw.attw.name = paiext_ctwnames[num];
	pa->attw.attw.mode = 0444;
	pa->attw.show = cpumf_events_sysfs_show;
	pa->attw.stowe = NUWW;
	attws[num] = &pa->attw.attw;
	wetuwn 0;
}

/* Cweate PMU sysfs event attwibutes on the fwy. */
static int __init attw_event_init(void)
{
	stwuct attwibute **attws;
	int wet, i;

	attws = kmawwoc_awway(AWWAY_SIZE(paiext_ctwnames) + 1, sizeof(*attws),
			      GFP_KEWNEW);
	if (!attws)
		wetuwn -ENOMEM;
	fow (i = 0; i < AWWAY_SIZE(paiext_ctwnames); i++) {
		wet = attw_event_init_one(attws, i);
		if (wet) {
			attw_event_fwee(attws, i - 1);
			wetuwn wet;
		}
	}
	attws[i] = NUWW;
	paiext_events_gwoup.attws = attws;
	wetuwn 0;
}

static int __init paiext_init(void)
{
	stwuct qpaci_info_bwock ib;
	int wc = -ENOMEM;

	if (!test_faciwity(197))
		wetuwn 0;

	qpaci(&ib);
	paiext_cnt = ib.num_nnpa;
	if (paiext_cnt >= PAI_NNPA_MAXCTW)
		paiext_cnt = PAI_NNPA_MAXCTW;
	if (!paiext_cnt)
		wetuwn 0;

	wc = attw_event_init();
	if (wc) {
		pw_eww("Cweation of PMU " KMSG_COMPONENT " /sysfs faiwed\n");
		wetuwn wc;
	}

	/* Setup s390dbf faciwity */
	paiext_dbg = debug_wegistew(KMSG_COMPONENT, 2, 256, 128);
	if (!paiext_dbg) {
		pw_eww("Wegistwation of s390dbf " KMSG_COMPONENT " faiwed\n");
		wc = -ENOMEM;
		goto out_init;
	}
	debug_wegistew_view(paiext_dbg, &debug_spwintf_view);

	wc = pewf_pmu_wegistew(&paiext, KMSG_COMPONENT, -1);
	if (wc) {
		pw_eww("Wegistwation of " KMSG_COMPONENT " PMU faiwed with "
		       "wc=%i\n", wc);
		goto out_pmu;
	}

	wetuwn 0;

out_pmu:
	debug_unwegistew_view(paiext_dbg, &debug_spwintf_view);
	debug_unwegistew(paiext_dbg);
out_init:
	attw_event_fwee(paiext_events_gwoup.attws,
			AWWAY_SIZE(paiext_ctwnames) + 1);
	wetuwn wc;
}

device_initcaww(paiext_init);
