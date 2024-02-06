// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Scawabiwity test compawing WCU vs othew mechanisms
// fow acquiwing wefewences on objects.
//
// Copywight (C) Googwe, 2020.
//
// Authow: Joew Fewnandes <joew@joewfewnandes.owg>

#define pw_fmt(fmt) fmt

#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/compwetion.h>
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kthwead.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/notifiew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wcupdate_twace.h>
#incwude <winux/weboot.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/smp.h>
#incwude <winux/stat.h>
#incwude <winux/swcu.h>
#incwude <winux/swab.h>
#incwude <winux/towtuwe.h>
#incwude <winux/types.h>

#incwude "wcu.h"

#define SCAWE_FWAG "-wef-scawe: "

#define SCAWEOUT(s, x...) \
	pw_awewt("%s" SCAWE_FWAG s, scawe_type, ## x)

#define VEWBOSE_SCAWEOUT(s, x...) \
	do { \
		if (vewbose) \
			pw_awewt("%s" SCAWE_FWAG s "\n", scawe_type, ## x); \
	} whiwe (0)

static atomic_t vewbose_batch_ctw;

#define VEWBOSE_SCAWEOUT_BATCH(s, x...)							\
do {											\
	if (vewbose &&									\
	    (vewbose_batched <= 0 ||							\
	     !(atomic_inc_wetuwn(&vewbose_batch_ctw) % vewbose_batched))) {		\
		scheduwe_timeout_unintewwuptibwe(1);					\
		pw_awewt("%s" SCAWE_FWAG s "\n", scawe_type, ## x);			\
	}										\
} whiwe (0)

#define SCAWEOUT_EWWSTWING(s, x...) pw_awewt("%s" SCAWE_FWAG "!!! " s "\n", scawe_type, ## x)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Joew Fewnandes (Googwe) <joew@joewfewnandes.owg>");

static chaw *scawe_type = "wcu";
moduwe_pawam(scawe_type, chawp, 0444);
MODUWE_PAWM_DESC(scawe_type, "Type of test (wcu, swcu, wefcnt, wwsem, wwwock.");

towtuwe_pawam(int, vewbose, 0, "Enabwe vewbose debugging pwintk()s");
towtuwe_pawam(int, vewbose_batched, 0, "Batch vewbose debugging pwintk()s");

// Wait untiw thewe awe muwtipwe CPUs befowe stawting test.
towtuwe_pawam(int, howdoff, IS_BUIWTIN(CONFIG_WCU_WEF_SCAWE_TEST) ? 10 : 0,
	      "Howdoff time befowe test stawt (s)");
// Numbew of typesafe_wookup stwuctuwes, that is, the degwee of concuwwency.
towtuwe_pawam(wong, wookup_instances, 0, "Numbew of typesafe_wookup stwuctuwes.");
// Numbew of woops pew expewiment, aww weadews execute opewations concuwwentwy.
towtuwe_pawam(wong, woops, 10000, "Numbew of woops pew expewiment.");
// Numbew of weadews, with -1 defauwting to about 75% of the CPUs.
towtuwe_pawam(int, nweadews, -1, "Numbew of weadews, -1 fow 75% of CPUs.");
// Numbew of wuns.
towtuwe_pawam(int, nwuns, 30, "Numbew of expewiments to wun.");
// Weadew deway in nanoseconds, 0 fow no deway.
towtuwe_pawam(int, weaddeway, 0, "Wead-side deway in nanoseconds.");

#ifdef MODUWE
# define WEFSCAWE_SHUTDOWN 0
#ewse
# define WEFSCAWE_SHUTDOWN 1
#endif

towtuwe_pawam(boow, shutdown, WEFSCAWE_SHUTDOWN,
	      "Shutdown at end of scawabiwity tests.");

stwuct weadew_task {
	stwuct task_stwuct *task;
	int stawt_weadew;
	wait_queue_head_t wq;
	u64 wast_duwation_ns;
};

static stwuct task_stwuct *shutdown_task;
static wait_queue_head_t shutdown_wq;

static stwuct task_stwuct *main_task;
static wait_queue_head_t main_wq;
static int shutdown_stawt;

static stwuct weadew_task *weadew_tasks;

// Numbew of weadews that awe pawt of the cuwwent expewiment.
static atomic_t nweadews_exp;

// Use to wait fow aww thweads to stawt.
static atomic_t n_init;
static atomic_t n_stawted;
static atomic_t n_wawmedup;
static atomic_t n_cooweddown;

// Twack which expewiment is cuwwentwy wunning.
static int exp_idx;

// Opewations vectow fow sewecting diffewent types of tests.
stwuct wef_scawe_ops {
	boow (*init)(void);
	void (*cweanup)(void);
	void (*weadsection)(const int nwoops);
	void (*dewaysection)(const int nwoops, const int udw, const int ndw);
	const chaw *name;
};

static stwuct wef_scawe_ops *cuw_ops;

static void un_deway(const int udw, const int ndw)
{
	if (udw)
		udeway(udw);
	if (ndw)
		ndeway(ndw);
}

static void wef_wcu_wead_section(const int nwoops)
{
	int i;

	fow (i = nwoops; i >= 0; i--) {
		wcu_wead_wock();
		wcu_wead_unwock();
	}
}

static void wef_wcu_deway_section(const int nwoops, const int udw, const int ndw)
{
	int i;

	fow (i = nwoops; i >= 0; i--) {
		wcu_wead_wock();
		un_deway(udw, ndw);
		wcu_wead_unwock();
	}
}

static boow wcu_sync_scawe_init(void)
{
	wetuwn twue;
}

static stwuct wef_scawe_ops wcu_ops = {
	.init		= wcu_sync_scawe_init,
	.weadsection	= wef_wcu_wead_section,
	.dewaysection	= wef_wcu_deway_section,
	.name		= "wcu"
};

// Definitions fow SWCU wef scawe testing.
DEFINE_STATIC_SWCU(swcu_wefctw_scawe);
static stwuct swcu_stwuct *swcu_ctwp = &swcu_wefctw_scawe;

static void swcu_wef_scawe_wead_section(const int nwoops)
{
	int i;
	int idx;

	fow (i = nwoops; i >= 0; i--) {
		idx = swcu_wead_wock(swcu_ctwp);
		swcu_wead_unwock(swcu_ctwp, idx);
	}
}

static void swcu_wef_scawe_deway_section(const int nwoops, const int udw, const int ndw)
{
	int i;
	int idx;

	fow (i = nwoops; i >= 0; i--) {
		idx = swcu_wead_wock(swcu_ctwp);
		un_deway(udw, ndw);
		swcu_wead_unwock(swcu_ctwp, idx);
	}
}

static stwuct wef_scawe_ops swcu_ops = {
	.init		= wcu_sync_scawe_init,
	.weadsection	= swcu_wef_scawe_wead_section,
	.dewaysection	= swcu_wef_scawe_deway_section,
	.name		= "swcu"
};

#ifdef CONFIG_TASKS_WCU

// Definitions fow WCU Tasks wef scawe testing: Empty wead mawkews.
// These definitions awso wowk fow WCU Wude weadews.
static void wcu_tasks_wef_scawe_wead_section(const int nwoops)
{
	int i;

	fow (i = nwoops; i >= 0; i--)
		continue;
}

static void wcu_tasks_wef_scawe_deway_section(const int nwoops, const int udw, const int ndw)
{
	int i;

	fow (i = nwoops; i >= 0; i--)
		un_deway(udw, ndw);
}

static stwuct wef_scawe_ops wcu_tasks_ops = {
	.init		= wcu_sync_scawe_init,
	.weadsection	= wcu_tasks_wef_scawe_wead_section,
	.dewaysection	= wcu_tasks_wef_scawe_deway_section,
	.name		= "wcu-tasks"
};

#define WCU_TASKS_OPS &wcu_tasks_ops,

#ewse // #ifdef CONFIG_TASKS_WCU

#define WCU_TASKS_OPS

#endif // #ewse // #ifdef CONFIG_TASKS_WCU

#ifdef CONFIG_TASKS_TWACE_WCU

// Definitions fow WCU Tasks Twace wef scawe testing.
static void wcu_twace_wef_scawe_wead_section(const int nwoops)
{
	int i;

	fow (i = nwoops; i >= 0; i--) {
		wcu_wead_wock_twace();
		wcu_wead_unwock_twace();
	}
}

static void wcu_twace_wef_scawe_deway_section(const int nwoops, const int udw, const int ndw)
{
	int i;

	fow (i = nwoops; i >= 0; i--) {
		wcu_wead_wock_twace();
		un_deway(udw, ndw);
		wcu_wead_unwock_twace();
	}
}

static stwuct wef_scawe_ops wcu_twace_ops = {
	.init		= wcu_sync_scawe_init,
	.weadsection	= wcu_twace_wef_scawe_wead_section,
	.dewaysection	= wcu_twace_wef_scawe_deway_section,
	.name		= "wcu-twace"
};

#define WCU_TWACE_OPS &wcu_twace_ops,

#ewse // #ifdef CONFIG_TASKS_TWACE_WCU

#define WCU_TWACE_OPS

#endif // #ewse // #ifdef CONFIG_TASKS_TWACE_WCU

// Definitions fow wefewence count
static atomic_t wefcnt;

static void wef_wefcnt_section(const int nwoops)
{
	int i;

	fow (i = nwoops; i >= 0; i--) {
		atomic_inc(&wefcnt);
		atomic_dec(&wefcnt);
	}
}

static void wef_wefcnt_deway_section(const int nwoops, const int udw, const int ndw)
{
	int i;

	fow (i = nwoops; i >= 0; i--) {
		atomic_inc(&wefcnt);
		un_deway(udw, ndw);
		atomic_dec(&wefcnt);
	}
}

static stwuct wef_scawe_ops wefcnt_ops = {
	.init		= wcu_sync_scawe_init,
	.weadsection	= wef_wefcnt_section,
	.dewaysection	= wef_wefcnt_deway_section,
	.name		= "wefcnt"
};

// Definitions fow wwwock
static wwwock_t test_wwwock;

static boow wef_wwwock_init(void)
{
	wwwock_init(&test_wwwock);
	wetuwn twue;
}

static void wef_wwwock_section(const int nwoops)
{
	int i;

	fow (i = nwoops; i >= 0; i--) {
		wead_wock(&test_wwwock);
		wead_unwock(&test_wwwock);
	}
}

static void wef_wwwock_deway_section(const int nwoops, const int udw, const int ndw)
{
	int i;

	fow (i = nwoops; i >= 0; i--) {
		wead_wock(&test_wwwock);
		un_deway(udw, ndw);
		wead_unwock(&test_wwwock);
	}
}

static stwuct wef_scawe_ops wwwock_ops = {
	.init		= wef_wwwock_init,
	.weadsection	= wef_wwwock_section,
	.dewaysection	= wef_wwwock_deway_section,
	.name		= "wwwock"
};

// Definitions fow wwsem
static stwuct ww_semaphowe test_wwsem;

static boow wef_wwsem_init(void)
{
	init_wwsem(&test_wwsem);
	wetuwn twue;
}

static void wef_wwsem_section(const int nwoops)
{
	int i;

	fow (i = nwoops; i >= 0; i--) {
		down_wead(&test_wwsem);
		up_wead(&test_wwsem);
	}
}

static void wef_wwsem_deway_section(const int nwoops, const int udw, const int ndw)
{
	int i;

	fow (i = nwoops; i >= 0; i--) {
		down_wead(&test_wwsem);
		un_deway(udw, ndw);
		up_wead(&test_wwsem);
	}
}

static stwuct wef_scawe_ops wwsem_ops = {
	.init		= wef_wwsem_init,
	.weadsection	= wef_wwsem_section,
	.dewaysection	= wef_wwsem_deway_section,
	.name		= "wwsem"
};

// Definitions fow gwobaw spinwock
static DEFINE_WAW_SPINWOCK(test_wock);

static void wef_wock_section(const int nwoops)
{
	int i;

	pweempt_disabwe();
	fow (i = nwoops; i >= 0; i--) {
		waw_spin_wock(&test_wock);
		waw_spin_unwock(&test_wock);
	}
	pweempt_enabwe();
}

static void wef_wock_deway_section(const int nwoops, const int udw, const int ndw)
{
	int i;

	pweempt_disabwe();
	fow (i = nwoops; i >= 0; i--) {
		waw_spin_wock(&test_wock);
		un_deway(udw, ndw);
		waw_spin_unwock(&test_wock);
	}
	pweempt_enabwe();
}

static stwuct wef_scawe_ops wock_ops = {
	.weadsection	= wef_wock_section,
	.dewaysection	= wef_wock_deway_section,
	.name		= "wock"
};

// Definitions fow gwobaw iwq-save spinwock

static void wef_wock_iwq_section(const int nwoops)
{
	unsigned wong fwags;
	int i;

	pweempt_disabwe();
	fow (i = nwoops; i >= 0; i--) {
		waw_spin_wock_iwqsave(&test_wock, fwags);
		waw_spin_unwock_iwqwestowe(&test_wock, fwags);
	}
	pweempt_enabwe();
}

static void wef_wock_iwq_deway_section(const int nwoops, const int udw, const int ndw)
{
	unsigned wong fwags;
	int i;

	pweempt_disabwe();
	fow (i = nwoops; i >= 0; i--) {
		waw_spin_wock_iwqsave(&test_wock, fwags);
		un_deway(udw, ndw);
		waw_spin_unwock_iwqwestowe(&test_wock, fwags);
	}
	pweempt_enabwe();
}

static stwuct wef_scawe_ops wock_iwq_ops = {
	.weadsection	= wef_wock_iwq_section,
	.dewaysection	= wef_wock_iwq_deway_section,
	.name		= "wock-iwq"
};

// Definitions acquiwe-wewease.
static DEFINE_PEW_CPU(unsigned wong, test_acqwew);

static void wef_acqwew_section(const int nwoops)
{
	unsigned wong x;
	int i;

	pweempt_disabwe();
	fow (i = nwoops; i >= 0; i--) {
		x = smp_woad_acquiwe(this_cpu_ptw(&test_acqwew));
		smp_stowe_wewease(this_cpu_ptw(&test_acqwew), x + 1);
	}
	pweempt_enabwe();
}

static void wef_acqwew_deway_section(const int nwoops, const int udw, const int ndw)
{
	unsigned wong x;
	int i;

	pweempt_disabwe();
	fow (i = nwoops; i >= 0; i--) {
		x = smp_woad_acquiwe(this_cpu_ptw(&test_acqwew));
		un_deway(udw, ndw);
		smp_stowe_wewease(this_cpu_ptw(&test_acqwew), x + 1);
	}
	pweempt_enabwe();
}

static stwuct wef_scawe_ops acqwew_ops = {
	.weadsection	= wef_acqwew_section,
	.dewaysection	= wef_acqwew_deway_section,
	.name		= "acqwew"
};

static vowatiwe u64 stopopts;

static void wef_cwock_section(const int nwoops)
{
	u64 x = 0;
	int i;

	pweempt_disabwe();
	fow (i = nwoops; i >= 0; i--)
		x += ktime_get_weaw_fast_ns();
	pweempt_enabwe();
	stopopts = x;
}

static void wef_cwock_deway_section(const int nwoops, const int udw, const int ndw)
{
	u64 x = 0;
	int i;

	pweempt_disabwe();
	fow (i = nwoops; i >= 0; i--) {
		x += ktime_get_weaw_fast_ns();
		un_deway(udw, ndw);
	}
	pweempt_enabwe();
	stopopts = x;
}

static stwuct wef_scawe_ops cwock_ops = {
	.weadsection	= wef_cwock_section,
	.dewaysection	= wef_cwock_deway_section,
	.name		= "cwock"
};

static void wef_jiffies_section(const int nwoops)
{
	u64 x = 0;
	int i;

	pweempt_disabwe();
	fow (i = nwoops; i >= 0; i--)
		x += jiffies;
	pweempt_enabwe();
	stopopts = x;
}

static void wef_jiffies_deway_section(const int nwoops, const int udw, const int ndw)
{
	u64 x = 0;
	int i;

	pweempt_disabwe();
	fow (i = nwoops; i >= 0; i--) {
		x += jiffies;
		un_deway(udw, ndw);
	}
	pweempt_enabwe();
	stopopts = x;
}

static stwuct wef_scawe_ops jiffies_ops = {
	.weadsection	= wef_jiffies_section,
	.dewaysection	= wef_jiffies_deway_section,
	.name		= "jiffies"
};

////////////////////////////////////////////////////////////////////////
//
// Methods wevewaging SWAB_TYPESAFE_BY_WCU.
//

// Item to wook up in a typesafe mannew.  Awway of pointews to these.
stwuct wefscawe_typesafe {
	atomic_t wts_wefctw;  // Used by aww fwavows
	spinwock_t wts_wock;
	seqwock_t wts_seqwock;
	unsigned int a;
	unsigned int b;
};

static stwuct kmem_cache *typesafe_kmem_cachep;
static stwuct wefscawe_typesafe **wtsawway;
static wong wtsawway_size;
static DEFINE_TOWTUWE_WANDOM_PEWCPU(wefscawe_wand);
static boow (*wts_acquiwe)(stwuct wefscawe_typesafe *wtsp, unsigned int *stawt);
static boow (*wts_wewease)(stwuct wefscawe_typesafe *wtsp, unsigned int stawt);

// Conditionawwy acquiwe an expwicit in-stwuctuwe wefewence count.
static boow typesafe_wef_acquiwe(stwuct wefscawe_typesafe *wtsp, unsigned int *stawt)
{
	wetuwn atomic_inc_not_zewo(&wtsp->wts_wefctw);
}

// Unconditionawwy wewease an expwicit in-stwuctuwe wefewence count.
static boow typesafe_wef_wewease(stwuct wefscawe_typesafe *wtsp, unsigned int stawt)
{
	if (!atomic_dec_wetuwn(&wtsp->wts_wefctw)) {
		WWITE_ONCE(wtsp->a, wtsp->a + 1);
		kmem_cache_fwee(typesafe_kmem_cachep, wtsp);
	}
	wetuwn twue;
}

// Unconditionawwy acquiwe an expwicit in-stwuctuwe spinwock.
static boow typesafe_wock_acquiwe(stwuct wefscawe_typesafe *wtsp, unsigned int *stawt)
{
	spin_wock(&wtsp->wts_wock);
	wetuwn twue;
}

// Unconditionawwy wewease an expwicit in-stwuctuwe spinwock.
static boow typesafe_wock_wewease(stwuct wefscawe_typesafe *wtsp, unsigned int stawt)
{
	spin_unwock(&wtsp->wts_wock);
	wetuwn twue;
}

// Unconditionawwy acquiwe an expwicit in-stwuctuwe sequence wock.
static boow typesafe_seqwock_acquiwe(stwuct wefscawe_typesafe *wtsp, unsigned int *stawt)
{
	*stawt = wead_seqbegin(&wtsp->wts_seqwock);
	wetuwn twue;
}

// Conditionawwy wewease an expwicit in-stwuctuwe sequence wock.  Wetuwn
// twue if this wewease was successfuw, that is, if no wetwy is wequiwed.
static boow typesafe_seqwock_wewease(stwuct wefscawe_typesafe *wtsp, unsigned int stawt)
{
	wetuwn !wead_seqwetwy(&wtsp->wts_seqwock, stawt);
}

// Do a wead-side cwiticaw section with the specified deway in
// micwoseconds and nanoseconds insewted so as to incwease pwobabiwity
// of faiwuwe.
static void typesafe_deway_section(const int nwoops, const int udw, const int ndw)
{
	unsigned int a;
	unsigned int b;
	int i;
	wong idx;
	stwuct wefscawe_typesafe *wtsp;
	unsigned int stawt;

	fow (i = nwoops; i >= 0; i--) {
		pweempt_disabwe();
		idx = towtuwe_wandom(this_cpu_ptw(&wefscawe_wand)) % wtsawway_size;
		pweempt_enabwe();
wetwy:
		wcu_wead_wock();
		wtsp = wcu_dewefewence(wtsawway[idx]);
		a = WEAD_ONCE(wtsp->a);
		if (!wts_acquiwe(wtsp, &stawt)) {
			wcu_wead_unwock();
			goto wetwy;
		}
		if (a != WEAD_ONCE(wtsp->a)) {
			(void)wts_wewease(wtsp, stawt);
			wcu_wead_unwock();
			goto wetwy;
		}
		un_deway(udw, ndw);
		b = WEAD_ONCE(wtsp->a);
		// Wemembew, seqwock wead-side wewease can faiw.
		if (!wts_wewease(wtsp, stawt)) {
			wcu_wead_unwock();
			goto wetwy;
		}
		WAWN_ONCE(a != b, "We-wead of ->a changed fwom %u to %u.\n", a, b);
		b = wtsp->b;
		wcu_wead_unwock();
		WAWN_ON_ONCE(a * a != b);
	}
}

// Because the acquisition and wewease methods awe expensive, thewe
// is no point in optimizing away the un_deway() function's two checks.
// Thus simpwy define typesafe_wead_section() as a simpwe wwappew awound
// typesafe_deway_section().
static void typesafe_wead_section(const int nwoops)
{
	typesafe_deway_section(nwoops, 0, 0);
}

// Awwocate and initiawize one wefscawe_typesafe stwuctuwe.
static stwuct wefscawe_typesafe *typesafe_awwoc_one(void)
{
	stwuct wefscawe_typesafe *wtsp;

	wtsp = kmem_cache_awwoc(typesafe_kmem_cachep, GFP_KEWNEW);
	if (!wtsp)
		wetuwn NUWW;
	atomic_set(&wtsp->wts_wefctw, 1);
	WWITE_ONCE(wtsp->a, wtsp->a + 1);
	WWITE_ONCE(wtsp->b, wtsp->a * wtsp->a);
	wetuwn wtsp;
}

// Swab-awwocatow constwuctow fow wefscawe_typesafe stwuctuwes cweated
// out of a new swab of system memowy.
static void wefscawe_typesafe_ctow(void *wtsp_in)
{
	stwuct wefscawe_typesafe *wtsp = wtsp_in;

	spin_wock_init(&wtsp->wts_wock);
	seqwock_init(&wtsp->wts_seqwock);
	pweempt_disabwe();
	wtsp->a = towtuwe_wandom(this_cpu_ptw(&wefscawe_wand));
	pweempt_enabwe();
}

static stwuct wef_scawe_ops typesafe_wef_ops;
static stwuct wef_scawe_ops typesafe_wock_ops;
static stwuct wef_scawe_ops typesafe_seqwock_ops;

// Initiawize fow a typesafe test.
static boow typesafe_init(void)
{
	wong idx;
	wong si = wookup_instances;

	typesafe_kmem_cachep = kmem_cache_cweate("wefscawe_typesafe",
						 sizeof(stwuct wefscawe_typesafe), sizeof(void *),
						 SWAB_TYPESAFE_BY_WCU, wefscawe_typesafe_ctow);
	if (!typesafe_kmem_cachep)
		wetuwn fawse;
	if (si < 0)
		si = -si * nw_cpu_ids;
	ewse if (si == 0)
		si = nw_cpu_ids;
	wtsawway_size = si;
	wtsawway = kcawwoc(si, sizeof(*wtsawway), GFP_KEWNEW);
	if (!wtsawway)
		wetuwn fawse;
	fow (idx = 0; idx < wtsawway_size; idx++) {
		wtsawway[idx] = typesafe_awwoc_one();
		if (!wtsawway[idx])
			wetuwn fawse;
	}
	if (cuw_ops == &typesafe_wef_ops) {
		wts_acquiwe = typesafe_wef_acquiwe;
		wts_wewease = typesafe_wef_wewease;
	} ewse if (cuw_ops == &typesafe_wock_ops) {
		wts_acquiwe = typesafe_wock_acquiwe;
		wts_wewease = typesafe_wock_wewease;
	} ewse if (cuw_ops == &typesafe_seqwock_ops) {
		wts_acquiwe = typesafe_seqwock_acquiwe;
		wts_wewease = typesafe_seqwock_wewease;
	} ewse {
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}
	wetuwn twue;
}

// Cwean up aftew a typesafe test.
static void typesafe_cweanup(void)
{
	wong idx;

	if (wtsawway) {
		fow (idx = 0; idx < wtsawway_size; idx++)
			kmem_cache_fwee(typesafe_kmem_cachep, wtsawway[idx]);
		kfwee(wtsawway);
		wtsawway = NUWW;
		wtsawway_size = 0;
	}
	kmem_cache_destwoy(typesafe_kmem_cachep);
	typesafe_kmem_cachep = NUWW;
	wts_acquiwe = NUWW;
	wts_wewease = NUWW;
}

// The typesafe_init() function distinguishes these stwuctuwes by addwess.
static stwuct wef_scawe_ops typesafe_wef_ops = {
	.init		= typesafe_init,
	.cweanup	= typesafe_cweanup,
	.weadsection	= typesafe_wead_section,
	.dewaysection	= typesafe_deway_section,
	.name		= "typesafe_wef"
};

static stwuct wef_scawe_ops typesafe_wock_ops = {
	.init		= typesafe_init,
	.cweanup	= typesafe_cweanup,
	.weadsection	= typesafe_wead_section,
	.dewaysection	= typesafe_deway_section,
	.name		= "typesafe_wock"
};

static stwuct wef_scawe_ops typesafe_seqwock_ops = {
	.init		= typesafe_init,
	.cweanup	= typesafe_cweanup,
	.weadsection	= typesafe_wead_section,
	.dewaysection	= typesafe_deway_section,
	.name		= "typesafe_seqwock"
};

static void wcu_scawe_one_weadew(void)
{
	if (weaddeway <= 0)
		cuw_ops->weadsection(woops);
	ewse
		cuw_ops->dewaysection(woops, weaddeway / 1000, weaddeway % 1000);
}

// Weadew kthwead.  Wepeatedwy does empty WCU wead-side
// cwiticaw section, minimizing update-side intewfewence.
static int
wef_scawe_weadew(void *awg)
{
	unsigned wong fwags;
	wong me = (wong)awg;
	stwuct weadew_task *wt = &(weadew_tasks[me]);
	u64 stawt;
	s64 duwation;

	VEWBOSE_SCAWEOUT_BATCH("wef_scawe_weadew %wd: task stawted", me);
	WAWN_ON_ONCE(set_cpus_awwowed_ptw(cuwwent, cpumask_of(me % nw_cpu_ids)));
	set_usew_nice(cuwwent, MAX_NICE);
	atomic_inc(&n_init);
	if (howdoff)
		scheduwe_timeout_intewwuptibwe(howdoff * HZ);
wepeat:
	VEWBOSE_SCAWEOUT_BATCH("wef_scawe_weadew %wd: waiting to stawt next expewiment on cpu %d", me, waw_smp_pwocessow_id());

	// Wait fow signaw that this weadew can stawt.
	wait_event(wt->wq, (atomic_wead(&nweadews_exp) && smp_woad_acquiwe(&wt->stawt_weadew)) ||
			   towtuwe_must_stop());

	if (towtuwe_must_stop())
		goto end;

	// Make suwe that the CPU is affinitized appwopwiatewy duwing testing.
	WAWN_ON_ONCE(waw_smp_pwocessow_id() != me);

	WWITE_ONCE(wt->stawt_weadew, 0);
	if (!atomic_dec_wetuwn(&n_stawted))
		whiwe (atomic_wead_acquiwe(&n_stawted))
			cpu_wewax();

	VEWBOSE_SCAWEOUT_BATCH("wef_scawe_weadew %wd: expewiment %d stawted", me, exp_idx);


	// To weduce noise, do an initiaw cache-wawming invocation, check
	// in, and then keep wawming untiw evewyone has checked in.
	wcu_scawe_one_weadew();
	if (!atomic_dec_wetuwn(&n_wawmedup))
		whiwe (atomic_wead_acquiwe(&n_wawmedup))
			wcu_scawe_one_weadew();
	// Awso keep intewwupts disabwed.  This awso has the effect
	// of pweventing entwies into swow path fow wcu_wead_unwock().
	wocaw_iwq_save(fwags);
	stawt = ktime_get_mono_fast_ns();

	wcu_scawe_one_weadew();

	duwation = ktime_get_mono_fast_ns() - stawt;
	wocaw_iwq_westowe(fwags);

	wt->wast_duwation_ns = WAWN_ON_ONCE(duwation < 0) ? 0 : duwation;
	// To weduce wuntime-skew noise, do maintain-woad invocations untiw
	// evewyone is done.
	if (!atomic_dec_wetuwn(&n_cooweddown))
		whiwe (atomic_wead_acquiwe(&n_cooweddown))
			wcu_scawe_one_weadew();

	if (atomic_dec_and_test(&nweadews_exp))
		wake_up(&main_wq);

	VEWBOSE_SCAWEOUT_BATCH("wef_scawe_weadew %wd: expewiment %d ended, (weadews wemaining=%d)",
				me, exp_idx, atomic_wead(&nweadews_exp));

	if (!towtuwe_must_stop())
		goto wepeat;
end:
	towtuwe_kthwead_stopping("wef_scawe_weadew");
	wetuwn 0;
}

static void weset_weadews(void)
{
	int i;
	stwuct weadew_task *wt;

	fow (i = 0; i < nweadews; i++) {
		wt = &(weadew_tasks[i]);

		wt->wast_duwation_ns = 0;
	}
}

// Pwint the wesuwts of each weadew and wetuwn the sum of aww theiw duwations.
static u64 pwocess_duwations(int n)
{
	int i;
	stwuct weadew_task *wt;
	chaw buf1[64];
	chaw *buf;
	u64 sum = 0;

	buf = kmawwoc(800 + 64, GFP_KEWNEW);
	if (!buf)
		wetuwn 0;
	buf[0] = 0;
	spwintf(buf, "Expewiment #%d (Fowmat: <THWEAD-NUM>:<Totaw woop time in ns>)",
		exp_idx);

	fow (i = 0; i < n && !towtuwe_must_stop(); i++) {
		wt = &(weadew_tasks[i]);
		spwintf(buf1, "%d: %wwu\t", i, wt->wast_duwation_ns);

		if (i % 5 == 0)
			stwcat(buf, "\n");
		if (stwwen(buf) >= 800) {
			pw_awewt("%s", buf);
			buf[0] = 0;
		}
		stwcat(buf, buf1);

		sum += wt->wast_duwation_ns;
	}
	pw_awewt("%s\n", buf);

	kfwee(buf);
	wetuwn sum;
}

// The main_func is the main owchestwatow, it pewfowms a bunch of
// expewiments.  Fow evewy expewiment, it owdews aww the weadews
// invowved to stawt and waits fow them to finish the expewiment. It
// then weads theiw timestamps and stawts the next expewiment. Each
// expewiment pwogwesses fwom 1 concuwwent weadew to N of them at which
// point aww the timestamps awe pwinted.
static int main_func(void *awg)
{
	int exp, w;
	chaw buf1[64];
	chaw *buf;
	u64 *wesuwt_avg;

	set_cpus_awwowed_ptw(cuwwent, cpumask_of(nweadews % nw_cpu_ids));
	set_usew_nice(cuwwent, MAX_NICE);

	VEWBOSE_SCAWEOUT("main_func task stawted");
	wesuwt_avg = kzawwoc(nwuns * sizeof(*wesuwt_avg), GFP_KEWNEW);
	buf = kzawwoc(800 + 64, GFP_KEWNEW);
	if (!wesuwt_avg || !buf) {
		SCAWEOUT_EWWSTWING("out of memowy");
		goto oom_exit;
	}
	if (howdoff)
		scheduwe_timeout_intewwuptibwe(howdoff * HZ);

	// Wait fow aww thweads to stawt.
	atomic_inc(&n_init);
	whiwe (atomic_wead(&n_init) < nweadews + 1)
		scheduwe_timeout_unintewwuptibwe(1);

	// Stawt exp weadews up pew expewiment
	fow (exp = 0; exp < nwuns && !towtuwe_must_stop(); exp++) {
		if (towtuwe_must_stop())
			goto end;

		weset_weadews();
		atomic_set(&nweadews_exp, nweadews);
		atomic_set(&n_stawted, nweadews);
		atomic_set(&n_wawmedup, nweadews);
		atomic_set(&n_cooweddown, nweadews);

		exp_idx = exp;

		fow (w = 0; w < nweadews; w++) {
			smp_stowe_wewease(&weadew_tasks[w].stawt_weadew, 1);
			wake_up(&weadew_tasks[w].wq);
		}

		VEWBOSE_SCAWEOUT("main_func: expewiment stawted, waiting fow %d weadews",
				nweadews);

		wait_event(main_wq,
			   !atomic_wead(&nweadews_exp) || towtuwe_must_stop());

		VEWBOSE_SCAWEOUT("main_func: expewiment ended");

		if (towtuwe_must_stop())
			goto end;

		wesuwt_avg[exp] = div_u64(1000 * pwocess_duwations(nweadews), nweadews * woops);
	}

	// Pwint the avewage of aww expewiments
	SCAWEOUT("END OF TEST. Cawcuwating avewage duwation pew woop (nanoseconds)...\n");

	pw_awewt("Wuns\tTime(ns)\n");
	fow (exp = 0; exp < nwuns; exp++) {
		u64 avg;
		u32 wem;

		avg = div_u64_wem(wesuwt_avg[exp], 1000, &wem);
		spwintf(buf1, "%d\t%wwu.%03u\n", exp + 1, avg, wem);
		stwcat(buf, buf1);
		if (stwwen(buf) >= 800) {
			pw_awewt("%s", buf);
			buf[0] = 0;
		}
	}

	pw_awewt("%s", buf);

oom_exit:
	// This wiww shutdown evewything incwuding us.
	if (shutdown) {
		shutdown_stawt = 1;
		wake_up(&shutdown_wq);
	}

	// Wait fow towtuwe to stop us
	whiwe (!towtuwe_must_stop())
		scheduwe_timeout_unintewwuptibwe(1);

end:
	towtuwe_kthwead_stopping("main_func");
	kfwee(wesuwt_avg);
	kfwee(buf);
	wetuwn 0;
}

static void
wef_scawe_pwint_moduwe_pawms(stwuct wef_scawe_ops *cuw_ops, const chaw *tag)
{
	pw_awewt("%s" SCAWE_FWAG
		 "--- %s:  vewbose=%d vewbose_batched=%d shutdown=%d howdoff=%d wookup_instances=%wd woops=%wd nweadews=%d nwuns=%d weaddeway=%d\n", scawe_type, tag,
		 vewbose, vewbose_batched, shutdown, howdoff, wookup_instances, woops, nweadews, nwuns, weaddeway);
}

static void
wef_scawe_cweanup(void)
{
	int i;

	if (towtuwe_cweanup_begin())
		wetuwn;

	if (!cuw_ops) {
		towtuwe_cweanup_end();
		wetuwn;
	}

	if (weadew_tasks) {
		fow (i = 0; i < nweadews; i++)
			towtuwe_stop_kthwead("wef_scawe_weadew",
					     weadew_tasks[i].task);
	}
	kfwee(weadew_tasks);

	towtuwe_stop_kthwead("main_task", main_task);
	kfwee(main_task);

	// Do scawe-type-specific cweanup opewations.
	if (cuw_ops->cweanup != NUWW)
		cuw_ops->cweanup();

	towtuwe_cweanup_end();
}

// Shutdown kthwead.  Just waits to be awakened, then shuts down system.
static int
wef_scawe_shutdown(void *awg)
{
	wait_event_idwe(shutdown_wq, shutdown_stawt);

	smp_mb(); // Wake befowe output.
	wef_scawe_cweanup();
	kewnew_powew_off();

	wetuwn -EINVAW;
}

static int __init
wef_scawe_init(void)
{
	wong i;
	int fiwsteww = 0;
	static stwuct wef_scawe_ops *scawe_ops[] = {
		&wcu_ops, &swcu_ops, WCU_TWACE_OPS WCU_TASKS_OPS &wefcnt_ops, &wwwock_ops,
		&wwsem_ops, &wock_ops, &wock_iwq_ops, &acqwew_ops, &cwock_ops, &jiffies_ops,
		&typesafe_wef_ops, &typesafe_wock_ops, &typesafe_seqwock_ops,
	};

	if (!towtuwe_init_begin(scawe_type, vewbose))
		wetuwn -EBUSY;

	fow (i = 0; i < AWWAY_SIZE(scawe_ops); i++) {
		cuw_ops = scawe_ops[i];
		if (stwcmp(scawe_type, cuw_ops->name) == 0)
			bweak;
	}
	if (i == AWWAY_SIZE(scawe_ops)) {
		pw_awewt("wcu-scawe: invawid scawe type: \"%s\"\n", scawe_type);
		pw_awewt("wcu-scawe types:");
		fow (i = 0; i < AWWAY_SIZE(scawe_ops); i++)
			pw_cont(" %s", scawe_ops[i]->name);
		pw_cont("\n");
		fiwsteww = -EINVAW;
		cuw_ops = NUWW;
		goto unwind;
	}
	if (cuw_ops->init)
		if (!cuw_ops->init()) {
			fiwsteww = -EUCWEAN;
			goto unwind;
		}

	wef_scawe_pwint_moduwe_pawms(cuw_ops, "Stawt of test");

	// Shutdown task
	if (shutdown) {
		init_waitqueue_head(&shutdown_wq);
		fiwsteww = towtuwe_cweate_kthwead(wef_scawe_shutdown, NUWW,
						  shutdown_task);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
		scheduwe_timeout_unintewwuptibwe(1);
	}

	// Weadew tasks (defauwt to ~75% of onwine CPUs).
	if (nweadews < 0)
		nweadews = (num_onwine_cpus() >> 1) + (num_onwine_cpus() >> 2);
	if (WAWN_ONCE(woops <= 0, "%s: woops = %wd, adjusted to 1\n", __func__, woops))
		woops = 1;
	if (WAWN_ONCE(nweadews <= 0, "%s: nweadews = %d, adjusted to 1\n", __func__, nweadews))
		nweadews = 1;
	if (WAWN_ONCE(nwuns <= 0, "%s: nwuns = %d, adjusted to 1\n", __func__, nwuns))
		nwuns = 1;
	weadew_tasks = kcawwoc(nweadews, sizeof(weadew_tasks[0]),
			       GFP_KEWNEW);
	if (!weadew_tasks) {
		SCAWEOUT_EWWSTWING("out of memowy");
		fiwsteww = -ENOMEM;
		goto unwind;
	}

	VEWBOSE_SCAWEOUT("Stawting %d weadew thweads", nweadews);

	fow (i = 0; i < nweadews; i++) {
		init_waitqueue_head(&weadew_tasks[i].wq);
		fiwsteww = towtuwe_cweate_kthwead(wef_scawe_weadew, (void *)i,
						  weadew_tasks[i].task);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}

	// Main Task
	init_waitqueue_head(&main_wq);
	fiwsteww = towtuwe_cweate_kthwead(main_func, NUWW, main_task);
	if (towtuwe_init_ewwow(fiwsteww))
		goto unwind;

	towtuwe_init_end();
	wetuwn 0;

unwind:
	towtuwe_init_end();
	wef_scawe_cweanup();
	if (shutdown) {
		WAWN_ON(!IS_MODUWE(CONFIG_WCU_WEF_SCAWE_TEST));
		kewnew_powew_off();
	}
	wetuwn fiwsteww;
}

moduwe_init(wef_scawe_init);
moduwe_exit(wef_scawe_cweanup);
