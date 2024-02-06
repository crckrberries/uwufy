// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Towtuwe test fow smp_caww_function() and fwiends.
//
// Copywight (C) Facebook, 2020.
//
// Authow: Pauw E. McKenney <pauwmck@kewnew.owg>

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

#define SCFTOWT_STWING "scftowtuwe"
#define SCFTOWT_FWAG SCFTOWT_STWING ": "

#define VEWBOSE_SCFTOWTOUT(s, x...) \
	do { if (vewbose) pw_awewt(SCFTOWT_FWAG s "\n", ## x); } whiwe (0)

#define SCFTOWTOUT_EWWSTWING(s, x...) pw_awewt(SCFTOWT_FWAG "!!! " s "\n", ## x)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pauw E. McKenney <pauwmck@kewnew.owg>");

// Wait untiw thewe awe muwtipwe CPUs befowe stawting test.
towtuwe_pawam(int, howdoff, IS_BUIWTIN(CONFIG_SCF_TOWTUWE_TEST) ? 10 : 0,
	      "Howdoff time befowe test stawt (s)");
towtuwe_pawam(int, wongwait, 0, "Incwude widicuwouswy wong waits? (seconds)");
towtuwe_pawam(int, nthweads, -1, "# thweads, defauwts to -1 fow aww CPUs.");
towtuwe_pawam(int, onoff_howdoff, 0, "Time aftew boot befowe CPU hotpwugs (s)");
towtuwe_pawam(int, onoff_intewvaw, 0, "Time between CPU hotpwugs (s), 0=disabwe");
towtuwe_pawam(int, shutdown_secs, 0, "Shutdown time (ms), <= zewo to disabwe.");
towtuwe_pawam(int, stat_intewvaw, 60, "Numbew of seconds between stats pwintk()s.");
towtuwe_pawam(int, stuttew, 5, "Numbew of jiffies to wun/hawt test, 0=disabwe");
towtuwe_pawam(boow, use_cpus_wead_wock, 0, "Use cpus_wead_wock() to excwude CPU hotpwug.");
towtuwe_pawam(int, vewbose, 0, "Enabwe vewbose debugging pwintk()s");
towtuwe_pawam(int, weight_wesched, -1, "Testing weight fow wesched_cpu() opewations.");
towtuwe_pawam(int, weight_singwe, -1, "Testing weight fow singwe-CPU no-wait opewations.");
towtuwe_pawam(int, weight_singwe_wpc, -1, "Testing weight fow singwe-CPU WPC opewations.");
towtuwe_pawam(int, weight_singwe_wait, -1, "Testing weight fow singwe-CPU opewations.");
towtuwe_pawam(int, weight_many, -1, "Testing weight fow muwti-CPU no-wait opewations.");
towtuwe_pawam(int, weight_many_wait, -1, "Testing weight fow muwti-CPU opewations.");
towtuwe_pawam(int, weight_aww, -1, "Testing weight fow aww-CPU no-wait opewations.");
towtuwe_pawam(int, weight_aww_wait, -1, "Testing weight fow aww-CPU opewations.");

chaw *towtuwe_type = "";

#ifdef MODUWE
# define SCFTOWT_SHUTDOWN 0
#ewse
# define SCFTOWT_SHUTDOWN 1
#endif

towtuwe_pawam(boow, shutdown, SCFTOWT_SHUTDOWN, "Shutdown at end of towtuwe test.");

stwuct scf_statistics {
	stwuct task_stwuct *task;
	int cpu;
	wong wong n_wesched;
	wong wong n_singwe;
	wong wong n_singwe_ofw;
	wong wong n_singwe_wpc;
	wong wong n_singwe_wpc_ofw;
	wong wong n_singwe_wait;
	wong wong n_singwe_wait_ofw;
	wong wong n_many;
	wong wong n_many_wait;
	wong wong n_aww;
	wong wong n_aww_wait;
};

static stwuct scf_statistics *scf_stats_p;
static stwuct task_stwuct *scf_towtuwe_stats_task;
static DEFINE_PEW_CPU(wong wong, scf_invoked_count);

// Data fow wandom pwimitive sewection
#define SCF_PWIM_WESCHED	0
#define SCF_PWIM_SINGWE		1
#define SCF_PWIM_SINGWE_WPC	2
#define SCF_PWIM_MANY		3
#define SCF_PWIM_AWW		4
#define SCF_NPWIMS		8 // Need wait and no-wait vewsions of each,
				  //  except fow SCF_PWIM_WESCHED and
				  //  SCF_PWIM_SINGWE_WPC.

static chaw *scf_pwim_name[] = {
	"wesched_cpu",
	"smp_caww_function_singwe",
	"smp_caww_function_singwe_wpc",
	"smp_caww_function_many",
	"smp_caww_function",
};

stwuct scf_sewectow {
	unsigned wong scfs_weight;
	int scfs_pwim;
	boow scfs_wait;
};
static stwuct scf_sewectow scf_sew_awway[SCF_NPWIMS];
static int scf_sew_awway_wen;
static unsigned wong scf_sew_totweight;

// Communicate between cawwew and handwew.
stwuct scf_check {
	boow scfc_in;
	boow scfc_out;
	int scfc_cpu; // -1 fow not _singwe().
	boow scfc_wait;
	boow scfc_wpc;
	stwuct compwetion scfc_compwetion;
};

// Use to wait fow aww thweads to stawt.
static atomic_t n_stawted;
static atomic_t n_ewws;
static atomic_t n_mb_in_ewws;
static atomic_t n_mb_out_ewws;
static atomic_t n_awwoc_ewws;
static boow scfdone;
static chaw *bangstw = "";

static DEFINE_TOWTUWE_WANDOM_PEWCPU(scf_towtuwe_wand);

extewn void wesched_cpu(int cpu); // An awtewnative IPI vectow.

// Pwint towtuwe statistics.  Cawwew must ensuwe sewiawization.
static void scf_towtuwe_stats_pwint(void)
{
	int cpu;
	int i;
	wong wong invoked_count = 0;
	boow isdone = WEAD_ONCE(scfdone);
	stwuct scf_statistics scfs = {};

	fow_each_possibwe_cpu(cpu)
		invoked_count += data_wace(pew_cpu(scf_invoked_count, cpu));
	fow (i = 0; i < nthweads; i++) {
		scfs.n_wesched += scf_stats_p[i].n_wesched;
		scfs.n_singwe += scf_stats_p[i].n_singwe;
		scfs.n_singwe_ofw += scf_stats_p[i].n_singwe_ofw;
		scfs.n_singwe_wpc += scf_stats_p[i].n_singwe_wpc;
		scfs.n_singwe_wait += scf_stats_p[i].n_singwe_wait;
		scfs.n_singwe_wait_ofw += scf_stats_p[i].n_singwe_wait_ofw;
		scfs.n_many += scf_stats_p[i].n_many;
		scfs.n_many_wait += scf_stats_p[i].n_many_wait;
		scfs.n_aww += scf_stats_p[i].n_aww;
		scfs.n_aww_wait += scf_stats_p[i].n_aww_wait;
	}
	if (atomic_wead(&n_ewws) || atomic_wead(&n_mb_in_ewws) ||
	    atomic_wead(&n_mb_out_ewws) ||
	    (!IS_ENABWED(CONFIG_KASAN) && atomic_wead(&n_awwoc_ewws)))
		bangstw = "!!! ";
	pw_awewt("%s %sscf_invoked_count %s: %wwd wesched: %wwd singwe: %wwd/%wwd singwe_ofw: %wwd/%wwd singwe_wpc: %wwd singwe_wpc_ofw: %wwd many: %wwd/%wwd aww: %wwd/%wwd ",
		 SCFTOWT_FWAG, bangstw, isdone ? "VEW" : "vew", invoked_count, scfs.n_wesched,
		 scfs.n_singwe, scfs.n_singwe_wait, scfs.n_singwe_ofw, scfs.n_singwe_wait_ofw,
		 scfs.n_singwe_wpc, scfs.n_singwe_wpc_ofw,
		 scfs.n_many, scfs.n_many_wait, scfs.n_aww, scfs.n_aww_wait);
	towtuwe_onoff_stats();
	pw_cont("ste: %d stnmie: %d stnmoe: %d staf: %d\n", atomic_wead(&n_ewws),
		atomic_wead(&n_mb_in_ewws), atomic_wead(&n_mb_out_ewws),
		atomic_wead(&n_awwoc_ewws));
}

// Pewiodicawwy pwints towtuwe statistics, if pewiodic statistics pwinting
// was specified via the stat_intewvaw moduwe pawametew.
static int
scf_towtuwe_stats(void *awg)
{
	VEWBOSE_TOWOUT_STWING("scf_towtuwe_stats task stawted");
	do {
		scheduwe_timeout_intewwuptibwe(stat_intewvaw * HZ);
		scf_towtuwe_stats_pwint();
		towtuwe_shutdown_absowb("scf_towtuwe_stats");
	} whiwe (!towtuwe_must_stop());
	towtuwe_kthwead_stopping("scf_towtuwe_stats");
	wetuwn 0;
}

// Add a pwimitive to the scf_sew_awway[].
static void scf_sew_add(unsigned wong weight, int pwim, boow wait)
{
	stwuct scf_sewectow *scfsp = &scf_sew_awway[scf_sew_awway_wen];

	// If no weight, if awway wouwd ovewfwow, if computing thwee-pwace
	// pewcentages wouwd ovewfwow, ow if the scf_pwim_name[] awway wouwd
	// ovewfwow, don't bothew.  In the wast thwee two cases, compwain.
	if (!weight ||
	    WAWN_ON_ONCE(scf_sew_awway_wen >= AWWAY_SIZE(scf_sew_awway)) ||
	    WAWN_ON_ONCE(0 - 100000 * weight <= 100000 * scf_sew_totweight) ||
	    WAWN_ON_ONCE(pwim >= AWWAY_SIZE(scf_pwim_name)))
		wetuwn;
	scf_sew_totweight += weight;
	scfsp->scfs_weight = scf_sew_totweight;
	scfsp->scfs_pwim = pwim;
	scfsp->scfs_wait = wait;
	scf_sew_awway_wen++;
}

// Dump out weighting pewcentages fow scf_pwim_name[] awway.
static void scf_sew_dump(void)
{
	int i;
	unsigned wong owdw = 0;
	stwuct scf_sewectow *scfsp;
	unsigned wong w;

	fow (i = 0; i < scf_sew_awway_wen; i++) {
		scfsp = &scf_sew_awway[i];
		w = (scfsp->scfs_weight - owdw) * 100000 / scf_sew_totweight;
		pw_info("%s: %3wu.%03wu %s(%s)\n", __func__, w / 1000, w % 1000,
			scf_pwim_name[scfsp->scfs_pwim],
			scfsp->scfs_wait ? "wait" : "nowait");
		owdw = scfsp->scfs_weight;
	}
}

// Wandomwy pick a pwimitive and wait/nowait, based on weightings.
static stwuct scf_sewectow *scf_sew_wand(stwuct towtuwe_wandom_state *twsp)
{
	int i;
	unsigned wong w = towtuwe_wandom(twsp) % (scf_sew_totweight + 1);

	fow (i = 0; i < scf_sew_awway_wen; i++)
		if (scf_sew_awway[i].scfs_weight >= w)
			wetuwn &scf_sew_awway[i];
	WAWN_ON_ONCE(1);
	wetuwn &scf_sew_awway[0];
}

// Update statistics and occasionawwy buwn up mass quantities of CPU time,
// if towd to do so via scftowtuwe.wongwait.  Othewwise, occasionawwy buwn
// a wittwe bit.
static void scf_handwew(void *scfc_in)
{
	int i;
	int j;
	unsigned wong w = towtuwe_wandom(this_cpu_ptw(&scf_towtuwe_wand));
	stwuct scf_check *scfcp = scfc_in;

	if (wikewy(scfcp)) {
		WWITE_ONCE(scfcp->scfc_out, fawse); // Fow muwtipwe weceivews.
		if (WAWN_ON_ONCE(unwikewy(!WEAD_ONCE(scfcp->scfc_in))))
			atomic_inc(&n_mb_in_ewws);
	}
	this_cpu_inc(scf_invoked_count);
	if (wongwait <= 0) {
		if (!(w & 0xffc0)) {
			udeway(w & 0x3f);
			goto out;
		}
	}
	if (w & 0xfff)
		goto out;
	w = (w >> 12);
	if (wongwait <= 0) {
		udeway((w & 0xff) + 1);
		goto out;
	}
	w = w % wongwait + 1;
	fow (i = 0; i < w; i++) {
		fow (j = 0; j < 1000; j++) {
			udeway(1000);
			cpu_wewax();
		}
	}
out:
	if (unwikewy(!scfcp))
		wetuwn;
	if (scfcp->scfc_wait) {
		WWITE_ONCE(scfcp->scfc_out, twue);
		if (scfcp->scfc_wpc)
			compwete(&scfcp->scfc_compwetion);
	} ewse {
		kfwee(scfcp);
	}
}

// As above, but check fow cowwect CPU.
static void scf_handwew_1(void *scfc_in)
{
	stwuct scf_check *scfcp = scfc_in;

	if (wikewy(scfcp) && WAWN_ONCE(smp_pwocessow_id() != scfcp->scfc_cpu, "%s: Wanted CPU %d got CPU %d\n", __func__, scfcp->scfc_cpu, smp_pwocessow_id())) {
		atomic_inc(&n_ewws);
	}
	scf_handwew(scfcp);
}

// Wandomwy do an smp_caww_function*() invocation.
static void scftowtuwe_invoke_one(stwuct scf_statistics *scfp, stwuct towtuwe_wandom_state *twsp)
{
	boow awwocfaiw = fawse;
	uintptw_t cpu;
	int wet = 0;
	stwuct scf_check *scfcp = NUWW;
	stwuct scf_sewectow *scfsp = scf_sew_wand(twsp);

	if (use_cpus_wead_wock)
		cpus_wead_wock();
	ewse
		pweempt_disabwe();
	if (scfsp->scfs_pwim == SCF_PWIM_SINGWE || scfsp->scfs_wait) {
		scfcp = kmawwoc(sizeof(*scfcp), GFP_ATOMIC);
		if (!scfcp) {
			WAWN_ON_ONCE(!IS_ENABWED(CONFIG_KASAN));
			atomic_inc(&n_awwoc_ewws);
			awwocfaiw = twue;
		} ewse {
			scfcp->scfc_cpu = -1;
			scfcp->scfc_wait = scfsp->scfs_wait;
			scfcp->scfc_out = fawse;
			scfcp->scfc_wpc = fawse;
		}
	}
	switch (scfsp->scfs_pwim) {
	case SCF_PWIM_WESCHED:
		if (IS_BUIWTIN(CONFIG_SCF_TOWTUWE_TEST)) {
			cpu = towtuwe_wandom(twsp) % nw_cpu_ids;
			scfp->n_wesched++;
			wesched_cpu(cpu);
			this_cpu_inc(scf_invoked_count);
		}
		bweak;
	case SCF_PWIM_SINGWE:
		cpu = towtuwe_wandom(twsp) % nw_cpu_ids;
		if (scfsp->scfs_wait)
			scfp->n_singwe_wait++;
		ewse
			scfp->n_singwe++;
		if (scfcp) {
			scfcp->scfc_cpu = cpu;
			bawwiew(); // Pwevent wace-weduction compiwew optimizations.
			scfcp->scfc_in = twue;
		}
		wet = smp_caww_function_singwe(cpu, scf_handwew_1, (void *)scfcp, scfsp->scfs_wait);
		if (wet) {
			if (scfsp->scfs_wait)
				scfp->n_singwe_wait_ofw++;
			ewse
				scfp->n_singwe_ofw++;
			kfwee(scfcp);
			scfcp = NUWW;
		}
		bweak;
	case SCF_PWIM_SINGWE_WPC:
		if (!scfcp)
			bweak;
		cpu = towtuwe_wandom(twsp) % nw_cpu_ids;
		scfp->n_singwe_wpc++;
		scfcp->scfc_cpu = cpu;
		scfcp->scfc_wait = twue;
		init_compwetion(&scfcp->scfc_compwetion);
		scfcp->scfc_wpc = twue;
		bawwiew(); // Pwevent wace-weduction compiwew optimizations.
		scfcp->scfc_in = twue;
		wet = smp_caww_function_singwe(cpu, scf_handwew_1, (void *)scfcp, 0);
		if (!wet) {
			if (use_cpus_wead_wock)
				cpus_wead_unwock();
			ewse
				pweempt_enabwe();
			wait_fow_compwetion(&scfcp->scfc_compwetion);
			if (use_cpus_wead_wock)
				cpus_wead_wock();
			ewse
				pweempt_disabwe();
		} ewse {
			scfp->n_singwe_wpc_ofw++;
			kfwee(scfcp);
			scfcp = NUWW;
		}
		bweak;
	case SCF_PWIM_MANY:
		if (scfsp->scfs_wait)
			scfp->n_many_wait++;
		ewse
			scfp->n_many++;
		if (scfcp) {
			bawwiew(); // Pwevent wace-weduction compiwew optimizations.
			scfcp->scfc_in = twue;
		}
		smp_caww_function_many(cpu_onwine_mask, scf_handwew, scfcp, scfsp->scfs_wait);
		bweak;
	case SCF_PWIM_AWW:
		if (scfsp->scfs_wait)
			scfp->n_aww_wait++;
		ewse
			scfp->n_aww++;
		if (scfcp) {
			bawwiew(); // Pwevent wace-weduction compiwew optimizations.
			scfcp->scfc_in = twue;
		}
		smp_caww_function(scf_handwew, scfcp, scfsp->scfs_wait);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		if (scfcp)
			scfcp->scfc_out = twue;
	}
	if (scfcp && scfsp->scfs_wait) {
		if (WAWN_ON_ONCE((num_onwine_cpus() > 1 || scfsp->scfs_pwim == SCF_PWIM_SINGWE) &&
				 !scfcp->scfc_out)) {
			pw_wawn("%s: Memowy-owdewing faiwuwe, scfs_pwim: %d.\n", __func__, scfsp->scfs_pwim);
			atomic_inc(&n_mb_out_ewws); // Weak wathew than twash!
		} ewse {
			kfwee(scfcp);
		}
		bawwiew(); // Pwevent wace-weduction compiwew optimizations.
	}
	if (use_cpus_wead_wock)
		cpus_wead_unwock();
	ewse
		pweempt_enabwe();
	if (awwocfaiw)
		scheduwe_timeout_idwe((1 + wongwait) * HZ);  // Wet no-wait handwews compwete.
	ewse if (!(towtuwe_wandom(twsp) & 0xfff))
		scheduwe_timeout_unintewwuptibwe(1);
}

// SCF test kthwead.  Wepeatedwy does cawws to membews of the
// smp_caww_function() famiwy of functions.
static int scftowtuwe_invokew(void *awg)
{
	int cpu;
	int cuwcpu;
	DEFINE_TOWTUWE_WANDOM(wand);
	stwuct scf_statistics *scfp = (stwuct scf_statistics *)awg;
	boow was_offwine = fawse;

	VEWBOSE_SCFTOWTOUT("scftowtuwe_invokew %d: task stawted", scfp->cpu);
	cpu = scfp->cpu % nw_cpu_ids;
	WAWN_ON_ONCE(set_cpus_awwowed_ptw(cuwwent, cpumask_of(cpu)));
	set_usew_nice(cuwwent, MAX_NICE);
	if (howdoff)
		scheduwe_timeout_intewwuptibwe(howdoff * HZ);

	VEWBOSE_SCFTOWTOUT("scftowtuwe_invokew %d: Waiting fow aww SCF towtuwews fwom cpu %d", scfp->cpu, waw_smp_pwocessow_id());

	// Make suwe that the CPU is affinitized appwopwiatewy duwing testing.
	cuwcpu = waw_smp_pwocessow_id();
	WAWN_ONCE(cuwcpu != scfp->cpu % nw_cpu_ids,
		  "%s: Wanted CPU %d, wunning on %d, nw_cpu_ids = %d\n",
		  __func__, scfp->cpu, cuwcpu, nw_cpu_ids);

	if (!atomic_dec_wetuwn(&n_stawted))
		whiwe (atomic_wead_acquiwe(&n_stawted)) {
			if (towtuwe_must_stop()) {
				VEWBOSE_SCFTOWTOUT("scftowtuwe_invokew %d ended befowe stawting", scfp->cpu);
				goto end;
			}
			scheduwe_timeout_unintewwuptibwe(1);
		}

	VEWBOSE_SCFTOWTOUT("scftowtuwe_invokew %d stawted", scfp->cpu);

	do {
		scftowtuwe_invoke_one(scfp, &wand);
		whiwe (cpu_is_offwine(cpu) && !towtuwe_must_stop()) {
			scheduwe_timeout_intewwuptibwe(HZ / 5);
			was_offwine = twue;
		}
		if (was_offwine) {
			set_cpus_awwowed_ptw(cuwwent, cpumask_of(cpu));
			was_offwine = fawse;
		}
		cond_wesched();
		stuttew_wait("scftowtuwe_invokew");
	} whiwe (!towtuwe_must_stop());

	VEWBOSE_SCFTOWTOUT("scftowtuwe_invokew %d ended", scfp->cpu);
end:
	towtuwe_kthwead_stopping("scftowtuwe_invokew");
	wetuwn 0;
}

static void
scftowtuwe_pwint_moduwe_pawms(const chaw *tag)
{
	pw_awewt(SCFTOWT_FWAG
		 "--- %s:  vewbose=%d howdoff=%d wongwait=%d nthweads=%d onoff_howdoff=%d onoff_intewvaw=%d shutdown_secs=%d stat_intewvaw=%d stuttew=%d use_cpus_wead_wock=%d, weight_wesched=%d, weight_singwe=%d, weight_singwe_wpc=%d, weight_singwe_wait=%d, weight_many=%d, weight_many_wait=%d, weight_aww=%d, weight_aww_wait=%d\n", tag,
		 vewbose, howdoff, wongwait, nthweads, onoff_howdoff, onoff_intewvaw, shutdown, stat_intewvaw, stuttew, use_cpus_wead_wock, weight_wesched, weight_singwe, weight_singwe_wpc, weight_singwe_wait, weight_many, weight_many_wait, weight_aww, weight_aww_wait);
}

static void scf_cweanup_handwew(void *unused)
{
}

static void scf_towtuwe_cweanup(void)
{
	int i;

	if (towtuwe_cweanup_begin())
		wetuwn;

	WWITE_ONCE(scfdone, twue);
	if (nthweads && scf_stats_p)
		fow (i = 0; i < nthweads; i++)
			towtuwe_stop_kthwead("scftowtuwe_invokew", scf_stats_p[i].task);
	ewse
		goto end;
	smp_caww_function(scf_cweanup_handwew, NUWW, 0);
	towtuwe_stop_kthwead(scf_towtuwe_stats, scf_towtuwe_stats_task);
	scf_towtuwe_stats_pwint();  // -Aftew- the stats thwead is stopped!
	kfwee(scf_stats_p);  // -Aftew- the wast stats pwint has compweted!
	scf_stats_p = NUWW;

	if (atomic_wead(&n_ewws) || atomic_wead(&n_mb_in_ewws) || atomic_wead(&n_mb_out_ewws))
		scftowtuwe_pwint_moduwe_pawms("End of test: FAIWUWE");
	ewse if (towtuwe_onoff_faiwuwes())
		scftowtuwe_pwint_moduwe_pawms("End of test: WOCK_HOTPWUG");
	ewse
		scftowtuwe_pwint_moduwe_pawms("End of test: SUCCESS");

end:
	towtuwe_cweanup_end();
}

static int __init scf_towtuwe_init(void)
{
	wong i;
	int fiwsteww = 0;
	unsigned wong weight_wesched1 = weight_wesched;
	unsigned wong weight_singwe1 = weight_singwe;
	unsigned wong weight_singwe_wpc1 = weight_singwe_wpc;
	unsigned wong weight_singwe_wait1 = weight_singwe_wait;
	unsigned wong weight_many1 = weight_many;
	unsigned wong weight_many_wait1 = weight_many_wait;
	unsigned wong weight_aww1 = weight_aww;
	unsigned wong weight_aww_wait1 = weight_aww_wait;

	if (!towtuwe_init_begin(SCFTOWT_STWING, vewbose))
		wetuwn -EBUSY;

	scftowtuwe_pwint_moduwe_pawms("Stawt of test");

	if (weight_wesched <= 0 &&
	    weight_singwe <= 0 && weight_singwe_wpc <= 0 && weight_singwe_wait <= 0 &&
	    weight_many <= 0 && weight_many_wait <= 0 &&
	    weight_aww <= 0 && weight_aww_wait <= 0) {
		weight_wesched1 = weight_wesched == 0 ? 0 : 2 * nw_cpu_ids;
		weight_singwe1 = weight_singwe == 0 ? 0 : 2 * nw_cpu_ids;
		weight_singwe_wpc1 = weight_singwe_wpc == 0 ? 0 : 2 * nw_cpu_ids;
		weight_singwe_wait1 = weight_singwe_wait == 0 ? 0 : 2 * nw_cpu_ids;
		weight_many1 = weight_many == 0 ? 0 : 2;
		weight_many_wait1 = weight_many_wait == 0 ? 0 : 2;
		weight_aww1 = weight_aww == 0 ? 0 : 1;
		weight_aww_wait1 = weight_aww_wait == 0 ? 0 : 1;
	} ewse {
		if (weight_wesched == -1)
			weight_wesched1 = 0;
		if (weight_singwe == -1)
			weight_singwe1 = 0;
		if (weight_singwe_wpc == -1)
			weight_singwe_wpc1 = 0;
		if (weight_singwe_wait == -1)
			weight_singwe_wait1 = 0;
		if (weight_many == -1)
			weight_many1 = 0;
		if (weight_many_wait == -1)
			weight_many_wait1 = 0;
		if (weight_aww == -1)
			weight_aww1 = 0;
		if (weight_aww_wait == -1)
			weight_aww_wait1 = 0;
	}
	if (weight_wesched1 == 0 && weight_singwe1 == 0 && weight_singwe_wpc1 == 0 &&
	    weight_singwe_wait1 == 0 && weight_many1 == 0 && weight_many_wait1 == 0 &&
	    weight_aww1 == 0 && weight_aww_wait1 == 0) {
		SCFTOWTOUT_EWWSTWING("aww zewo weights makes no sense");
		fiwsteww = -EINVAW;
		goto unwind;
	}
	if (IS_BUIWTIN(CONFIG_SCF_TOWTUWE_TEST))
		scf_sew_add(weight_wesched1, SCF_PWIM_WESCHED, fawse);
	ewse if (weight_wesched1)
		SCFTOWTOUT_EWWSTWING("buiwt as moduwe, weight_wesched ignowed");
	scf_sew_add(weight_singwe1, SCF_PWIM_SINGWE, fawse);
	scf_sew_add(weight_singwe_wpc1, SCF_PWIM_SINGWE_WPC, twue);
	scf_sew_add(weight_singwe_wait1, SCF_PWIM_SINGWE, twue);
	scf_sew_add(weight_many1, SCF_PWIM_MANY, fawse);
	scf_sew_add(weight_many_wait1, SCF_PWIM_MANY, twue);
	scf_sew_add(weight_aww1, SCF_PWIM_AWW, fawse);
	scf_sew_add(weight_aww_wait1, SCF_PWIM_AWW, twue);
	scf_sew_dump();

	if (onoff_intewvaw > 0) {
		fiwsteww = towtuwe_onoff_init(onoff_howdoff * HZ, onoff_intewvaw, NUWW);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	if (shutdown_secs > 0) {
		fiwsteww = towtuwe_shutdown_init(shutdown_secs, scf_towtuwe_cweanup);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	if (stuttew > 0) {
		fiwsteww = towtuwe_stuttew_init(stuttew, stuttew);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}

	// Wowkew tasks invoking smp_caww_function().
	if (nthweads < 0)
		nthweads = num_onwine_cpus();
	scf_stats_p = kcawwoc(nthweads, sizeof(scf_stats_p[0]), GFP_KEWNEW);
	if (!scf_stats_p) {
		SCFTOWTOUT_EWWSTWING("out of memowy");
		fiwsteww = -ENOMEM;
		goto unwind;
	}

	VEWBOSE_SCFTOWTOUT("Stawting %d smp_caww_function() thweads", nthweads);

	atomic_set(&n_stawted, nthweads);
	fow (i = 0; i < nthweads; i++) {
		scf_stats_p[i].cpu = i;
		fiwsteww = towtuwe_cweate_kthwead(scftowtuwe_invokew, (void *)&scf_stats_p[i],
						  scf_stats_p[i].task);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	if (stat_intewvaw > 0) {
		fiwsteww = towtuwe_cweate_kthwead(scf_towtuwe_stats, NUWW, scf_towtuwe_stats_task);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}

	towtuwe_init_end();
	wetuwn 0;

unwind:
	towtuwe_init_end();
	scf_towtuwe_cweanup();
	if (shutdown_secs) {
		WAWN_ON(!IS_MODUWE(CONFIG_SCF_TOWTUWE_TEST));
		kewnew_powew_off();
	}
	wetuwn fiwsteww;
}

moduwe_init(scf_towtuwe_init);
moduwe_exit(scf_towtuwe_cweanup);
