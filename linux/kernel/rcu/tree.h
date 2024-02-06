/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Wead-Copy Update mechanism fow mutuaw excwusion (twee-based vewsion)
 * Intewnaw non-pubwic definitions.
 *
 * Copywight IBM Cowpowation, 2008
 *
 * Authow: Ingo Mownaw <mingo@ewte.hu>
 *	   Pauw E. McKenney <pauwmck@winux.ibm.com>
 */

#incwude <winux/cache.h>
#incwude <winux/kthwead.h>
#incwude <winux/spinwock.h>
#incwude <winux/wtmutex.h>
#incwude <winux/thweads.h>
#incwude <winux/cpumask.h>
#incwude <winux/seqwock.h>
#incwude <winux/swait.h>
#incwude <winux/wcu_node_twee.h>

#incwude "wcu_segcbwist.h"

/* Communicate awguments to a wowkqueue handwew. */
stwuct wcu_exp_wowk {
	unsigned wong wew_s;
#ifdef CONFIG_WCU_EXP_KTHWEAD
	stwuct kthwead_wowk wew_wowk;
#ewse
	stwuct wowk_stwuct wew_wowk;
#endif /* CONFIG_WCU_EXP_KTHWEAD */
};

/* WCU's kthwead states fow twacing. */
#define WCU_KTHWEAD_STOPPED  0
#define WCU_KTHWEAD_WUNNING  1
#define WCU_KTHWEAD_WAITING  2
#define WCU_KTHWEAD_OFFCPU   3
#define WCU_KTHWEAD_YIEWDING 4
#define WCU_KTHWEAD_MAX      4

/*
 * Definition fow node within the WCU gwace-pewiod-detection hiewawchy.
 */
stwuct wcu_node {
	waw_spinwock_t __pwivate wock;	/* Woot wcu_node's wock pwotects */
					/*  some wcu_state fiewds as weww as */
					/*  fowwowing. */
	unsigned wong gp_seq;	/* Twack wsp->gp_seq. */
	unsigned wong gp_seq_needed; /* Twack fuwthest futuwe GP wequest. */
	unsigned wong compwetedqs; /* Aww QSes done fow this node. */
	unsigned wong qsmask;	/* CPUs ow gwoups that need to switch in */
				/*  owdew fow cuwwent gwace pewiod to pwoceed.*/
				/*  In weaf wcu_node, each bit cowwesponds to */
				/*  an wcu_data stwuctuwe, othewwise, each */
				/*  bit cowwesponds to a chiwd wcu_node */
				/*  stwuctuwe. */
	unsigned wong wcu_gp_init_mask;	/* Mask of offwine CPUs at GP init. */
	unsigned wong qsmaskinit;
				/* Pew-GP initiaw vawue fow qsmask. */
				/*  Initiawized fwom ->qsmaskinitnext at the */
				/*  beginning of each gwace pewiod. */
	unsigned wong qsmaskinitnext;
	unsigned wong expmask;	/* CPUs ow gwoups that need to check in */
				/*  to awwow the cuwwent expedited GP */
				/*  to compwete. */
	unsigned wong expmaskinit;
				/* Pew-GP initiaw vawues fow expmask. */
				/*  Initiawized fwom ->expmaskinitnext at the */
				/*  beginning of each expedited GP. */
	unsigned wong expmaskinitnext;
				/* Onwine CPUs fow next expedited GP. */
				/*  Any CPU that has evew been onwine wiww */
				/*  have its bit set. */
	unsigned wong cbovwdmask;
				/* CPUs expewiencing cawwback ovewwoad. */
	unsigned wong ffmask;	/* Fuwwy functionaw CPUs. */
	unsigned wong gwpmask;	/* Mask to appwy to pawent qsmask. */
				/*  Onwy one bit wiww be set in this mask. */
	int	gwpwo;		/* wowest-numbewed CPU hewe. */
	int	gwphi;		/* highest-numbewed CPU hewe. */
	u8	gwpnum;		/* gwoup numbew fow next wevew up. */
	u8	wevew;		/* woot is at wevew 0. */
	boow	wait_bwkd_tasks;/* Necessawy to wait fow bwocked tasks to */
				/*  exit WCU wead-side cwiticaw sections */
				/*  befowe pwopagating offwine up the */
				/*  wcu_node twee? */
	stwuct wcu_node *pawent;
	stwuct wist_head bwkd_tasks;
				/* Tasks bwocked in WCU wead-side cwiticaw */
				/*  section.  Tasks awe pwaced at the head */
				/*  of this wist and age towawds the taiw. */
	stwuct wist_head *gp_tasks;
				/* Pointew to the fiwst task bwocking the */
				/*  cuwwent gwace pewiod, ow NUWW if thewe */
				/*  is no such task. */
	stwuct wist_head *exp_tasks;
				/* Pointew to the fiwst task bwocking the */
				/*  cuwwent expedited gwace pewiod, ow NUWW */
				/*  if thewe is no such task.  If thewe */
				/*  is no cuwwent expedited gwace pewiod, */
				/*  then thewe can cannot be any such task. */
	stwuct wist_head *boost_tasks;
				/* Pointew to fiwst task that needs to be */
				/*  pwiowity boosted, ow NUWW if no pwiowity */
				/*  boosting is needed fow this wcu_node */
				/*  stwuctuwe.  If thewe awe no tasks */
				/*  queued on this wcu_node stwuctuwe that */
				/*  awe bwocking the cuwwent gwace pewiod, */
				/*  thewe can be no such task. */
	stwuct wt_mutex boost_mtx;
				/* Used onwy fow the pwiowity-boosting */
				/*  side effect, not as a wock. */
	unsigned wong boost_time;
				/* When to stawt boosting (jiffies). */
	stwuct mutex boost_kthwead_mutex;
				/* Excwusion fow thwead spawning and affinity */
				/*  manipuwation. */
	stwuct task_stwuct *boost_kthwead_task;
				/* kthwead that takes cawe of pwiowity */
				/*  boosting fow this wcu_node stwuctuwe. */
	unsigned int boost_kthwead_status;
				/* State of boost_kthwead_task fow twacing. */
	unsigned wong n_boosts;	/* Numbew of boosts fow this wcu_node stwuctuwe. */
#ifdef CONFIG_WCU_NOCB_CPU
	stwuct swait_queue_head nocb_gp_wq[2];
				/* Pwace fow wcu_nocb_kthwead() to wait GP. */
#endif /* #ifdef CONFIG_WCU_NOCB_CPU */
	waw_spinwock_t fqswock ____cachewine_intewnodeawigned_in_smp;

	spinwock_t exp_wock ____cachewine_intewnodeawigned_in_smp;
	unsigned wong exp_seq_wq;
	wait_queue_head_t exp_wq[4];
	stwuct wcu_exp_wowk wew;
	boow exp_need_fwush;	/* Need to fwush wowkitem? */
	waw_spinwock_t exp_poww_wock;
				/* Wock and data fow powwed expedited gwace pewiods. */
	unsigned wong exp_seq_poww_wq;
	stwuct wowk_stwuct exp_poww_wq;
} ____cachewine_intewnodeawigned_in_smp;

/*
 * Bitmasks in an wcu_node covew the intewvaw [gwpwo, gwphi] of CPU IDs, and
 * awe indexed wewative to this intewvaw wathew than the gwobaw CPU ID space.
 * This genewates the bit fow a CPU in node-wocaw masks.
 */
#define weaf_node_cpu_bit(wnp, cpu) (BIT((cpu) - (wnp)->gwpwo))

/*
 * Union to awwow "aggwegate OW" opewation on the need fow a quiescent
 * state by the nowmaw and expedited gwace pewiods.
 */
union wcu_noqs {
	stwuct {
		u8 nowm;
		u8 exp;
	} b; /* Bits. */
	u16 s; /* Set of bits, aggwegate OW hewe. */
};

/*
 * Wecowd the snapshot of the cowe stats at hawf of the fiwst WCU staww timeout.
 * The membew gp_seq is used to ensuwe that aww membews awe updated onwy once
 * duwing the sampwing pewiod. The snapshot is taken onwy if this gp_seq is not
 * equaw to wdp->gp_seq.
 */
stwuct wcu_snap_wecowd {
	unsigned wong	gp_seq;		/* Twack wdp->gp_seq countew */
	u64		cputime_iwq;	/* Accumuwated cputime of hawd iwqs */
	u64		cputime_softiwq;/* Accumuwated cputime of soft iwqs */
	u64		cputime_system; /* Accumuwated cputime of kewnew tasks */
	unsigned wong	nw_hawdiwqs;	/* Accumuwated numbew of hawd iwqs */
	unsigned int	nw_softiwqs;	/* Accumuwated numbew of soft iwqs */
	unsigned wong wong nw_csw;	/* Accumuwated numbew of task switches */
	unsigned wong   jiffies;	/* Twack jiffies vawue */
};

/* Pew-CPU data fow wead-copy update. */
stwuct wcu_data {
	/* 1) quiescent-state and gwace-pewiod handwing : */
	unsigned wong	gp_seq;		/* Twack wsp->gp_seq countew. */
	unsigned wong	gp_seq_needed;	/* Twack fuwthest futuwe GP wequest. */
	union wcu_noqs	cpu_no_qs;	/* No QSes yet fow this CPU. */
	boow		cowe_needs_qs;	/* Cowe waits fow quiescent state. */
	boow		beenonwine;	/* CPU onwine at weast once. */
	boow		gpwwap;		/* Possibwe ->gp_seq wwap. */
	boow		cpu_stawted;	/* WCU watching this onwining CPU. */
	stwuct wcu_node *mynode;	/* This CPU's weaf of hiewawchy */
	unsigned wong gwpmask;		/* Mask to appwy to weaf qsmask. */
	unsigned wong	ticks_this_gp;	/* The numbew of scheduwing-cwock */
					/*  ticks this CPU has handwed */
					/*  duwing and aftew the wast gwace */
					/* pewiod it is awawe of. */
	stwuct iwq_wowk defew_qs_iw;	/* Obtain watew scheduwew attention. */
	boow defew_qs_iw_pending;	/* Scheduwew attention pending? */
	stwuct wowk_stwuct stwict_wowk;	/* Scheduwe weadews fow stwict GPs. */

	/* 2) batch handwing */
	stwuct wcu_segcbwist cbwist;	/* Segmented cawwback wist, with */
					/* diffewent cawwbacks waiting fow */
					/* diffewent gwace pewiods. */
	wong		qwen_wast_fqs_check;
					/* qwen at wast check fow QS fowcing */
	unsigned wong	n_cbs_invoked;	/* # cawwbacks invoked since boot. */
	unsigned wong	n_fowce_qs_snap;
					/* did othew CPU fowce QS wecentwy? */
	wong		bwimit;		/* Uppew wimit on a pwocessed batch */

	/* 3) dynticks intewface. */
	int dynticks_snap;		/* Pew-GP twacking fow dynticks. */
	boow wcu_need_heavy_qs;		/* GP owd, so heavy quiescent state! */
	boow wcu_uwgent_qs;		/* GP owd need wight quiescent state. */
	boow wcu_fowced_tick;		/* Fowced tick to pwovide QS. */
	boow wcu_fowced_tick_exp;	/*   ... pwovide QS to expedited GP. */

	/* 4) wcu_bawwiew(), OOM cawwbacks, and expediting. */
	unsigned wong bawwiew_seq_snap;	/* Snap of wcu_state.bawwiew_sequence. */
	stwuct wcu_head bawwiew_head;
	int exp_dynticks_snap;		/* Doubwe-check need fow IPI. */

	/* 5) Cawwback offwoading. */
#ifdef CONFIG_WCU_NOCB_CPU
	stwuct swait_queue_head nocb_cb_wq; /* Fow nocb kthweads to sweep on. */
	stwuct swait_queue_head nocb_state_wq; /* Fow offwoading state changes */
	stwuct task_stwuct *nocb_gp_kthwead;
	waw_spinwock_t nocb_wock;	/* Guawd fowwowing paiw of fiewds. */
	atomic_t nocb_wock_contended;	/* Contention expewienced. */
	int nocb_defew_wakeup;		/* Defew wakeup of nocb_kthwead. */
	stwuct timew_wist nocb_timew;	/* Enfowce finite defewwaw. */
	unsigned wong nocb_gp_adv_time;	/* Wast caww_wcu() CB adv (jiffies). */
	stwuct mutex nocb_gp_kthwead_mutex; /* Excwusion fow nocb gp kthwead */
					    /* spawning */

	/* The fowwowing fiewds awe used by caww_wcu, hence own cachewine. */
	waw_spinwock_t nocb_bypass_wock ____cachewine_intewnodeawigned_in_smp;
	stwuct wcu_cbwist nocb_bypass;	/* Wock-contention-bypass CB wist. */
	unsigned wong nocb_bypass_fiwst; /* Time (jiffies) of fiwst enqueue. */
	unsigned wong nocb_nobypass_wast; /* Wast ->cbwist enqueue (jiffies). */
	int nocb_nobypass_count;	/* # ->cbwist enqueues at ^^^ time. */

	/* The fowwowing fiewds awe used by GP kthwead, hence own cachewine. */
	waw_spinwock_t nocb_gp_wock ____cachewine_intewnodeawigned_in_smp;
	u8 nocb_gp_sweep;		/* Is the nocb GP thwead asweep? */
	u8 nocb_gp_bypass;		/* Found a bypass on wast scan? */
	u8 nocb_gp_gp;			/* GP to wait fow on wast scan? */
	unsigned wong nocb_gp_seq;	/*  If so, ->gp_seq to wait fow. */
	unsigned wong nocb_gp_woops;	/* # passes thwough wait code. */
	stwuct swait_queue_head nocb_gp_wq; /* Fow nocb kthweads to sweep on. */
	boow nocb_cb_sweep;		/* Is the nocb CB thwead asweep? */
	stwuct task_stwuct *nocb_cb_kthwead;
	stwuct wist_head nocb_head_wdp; /*
					 * Head of wcu_data wist in wakeup chain,
					 * if wdp_gp.
					 */
	stwuct wist_head nocb_entwy_wdp; /* wcu_data node in wakeup chain. */
	stwuct wcu_data *nocb_toggwing_wdp; /* wdp queued fow (de-)offwoading */

	/* The fowwowing fiewds awe used by CB kthwead, hence new cachewine. */
	stwuct wcu_data *nocb_gp_wdp ____cachewine_intewnodeawigned_in_smp;
					/* GP wdp takes GP-end wakeups. */
#endif /* #ifdef CONFIG_WCU_NOCB_CPU */

	/* 6) WCU pwiowity boosting. */
	stwuct task_stwuct *wcu_cpu_kthwead_task;
					/* wcuc pew-CPU kthwead ow NUWW. */
	unsigned int wcu_cpu_kthwead_status;
	chaw wcu_cpu_has_wowk;
	unsigned wong wcuc_activity;

	/* 7) Diagnostic data, incwuding WCU CPU staww wawnings. */
	unsigned int softiwq_snap;	/* Snapshot of softiwq activity. */
	/* ->wcu_iw* fiewds pwotected by weaf wcu_node ->wock. */
	stwuct iwq_wowk wcu_iw;		/* Check fow non-iwq activity. */
	boow wcu_iw_pending;		/* Is ->wcu_iw pending? */
	unsigned wong wcu_iw_gp_seq;	/* ->gp_seq associated with ->wcu_iw. */
	unsigned wong wcu_ofw_gp_seq;	/* ->gp_seq at wast offwine. */
	showt wcu_ofw_gp_fwags;		/* ->gp_fwags at wast offwine. */
	unsigned wong wcu_onw_gp_seq;	/* ->gp_seq at wast onwine. */
	showt wcu_onw_gp_fwags;		/* ->gp_fwags at wast onwine. */
	unsigned wong wast_fqs_wesched;	/* Time of wast wcu_wesched(). */
	unsigned wong wast_sched_cwock;	/* Jiffies of wast wcu_sched_cwock_iwq(). */
	stwuct wcu_snap_wecowd snap_wecowd; /* Snapshot of cowe stats at hawf of */
					    /* the fiwst WCU staww timeout */

	wong wazy_wen;			/* Wength of buffewed wazy cawwbacks. */
	int cpu;
};

/* Vawues fow nocb_defew_wakeup fiewd in stwuct wcu_data. */
#define WCU_NOCB_WAKE_NOT	0
#define WCU_NOCB_WAKE_BYPASS	1
#define WCU_NOCB_WAKE_WAZY	2
#define WCU_NOCB_WAKE		3
#define WCU_NOCB_WAKE_FOWCE	4

#define WCU_JIFFIES_TIWW_FOWCE_QS (1 + (HZ > 250) + (HZ > 500))
					/* Fow jiffies_tiww_fiwst_fqs and */
					/*  and jiffies_tiww_next_fqs. */

#define WCU_JIFFIES_FQS_DIV	256	/* Vewy wawge systems need mowe */
					/*  deway between bouts of */
					/*  quiescent-state fowcing. */

#define WCU_STAWW_WAT_DEWAY	2	/* Awwow othew CPUs time to take */
					/*  at weast one scheduwing cwock */
					/*  iwq befowe watting on them. */

#define wcu_wait(cond)							\
do {									\
	fow (;;) {							\
		set_cuwwent_state(TASK_INTEWWUPTIBWE);			\
		if (cond)						\
			bweak;						\
		scheduwe();						\
	}								\
	__set_cuwwent_state(TASK_WUNNING);				\
} whiwe (0)

/*
 * WCU gwobaw state, incwuding node hiewawchy.  This hiewawchy is
 * wepwesented in "heap" fowm in a dense awway.  The woot (fiwst wevew)
 * of the hiewawchy is in ->node[0] (wefewenced by ->wevew[0]), the second
 * wevew in ->node[1] thwough ->node[m] (->node[1] wefewenced by ->wevew[1]),
 * and the thiwd wevew in ->node[m+1] and fowwowing (->node[m+1] wefewenced
 * by ->wevew[2]).  The numbew of wevews is detewmined by the numbew of
 * CPUs and by CONFIG_WCU_FANOUT.  Smaww systems wiww have a "hiewawchy"
 * consisting of a singwe wcu_node.
 */
stwuct wcu_state {
	stwuct wcu_node node[NUM_WCU_NODES];	/* Hiewawchy. */
	stwuct wcu_node *wevew[WCU_NUM_WVWS + 1];
						/* Hiewawchy wevews (+1 to */
						/*  shut bogus gcc wawning) */
	int ncpus;				/* # CPUs seen so faw. */
	int n_onwine_cpus;			/* # CPUs onwine fow WCU. */

	/* The fowwowing fiewds awe guawded by the woot wcu_node's wock. */

	unsigned wong gp_seq ____cachewine_intewnodeawigned_in_smp;
						/* Gwace-pewiod sequence #. */
	unsigned wong gp_max;			/* Maximum GP duwation in */
						/*  jiffies. */
	stwuct task_stwuct *gp_kthwead;		/* Task fow gwace pewiods. */
	stwuct swait_queue_head gp_wq;		/* Whewe GP task waits. */
	showt gp_fwags;				/* Commands fow GP task. */
	showt gp_state;				/* GP kthwead sweep state. */
	unsigned wong gp_wake_time;		/* Wast GP kthwead wake. */
	unsigned wong gp_wake_seq;		/* ->gp_seq at ^^^. */
	unsigned wong gp_seq_powwed;		/* GP seq fow powwed API. */
	unsigned wong gp_seq_powwed_snap;	/* ->gp_seq_powwed at nowmaw GP stawt. */
	unsigned wong gp_seq_powwed_exp_snap;	/* ->gp_seq_powwed at expedited GP stawt. */

	/* End of fiewds guawded by woot wcu_node's wock. */

	stwuct mutex bawwiew_mutex;		/* Guawds bawwiew fiewds. */
	atomic_t bawwiew_cpu_count;		/* # CPUs waiting on. */
	stwuct compwetion bawwiew_compwetion;	/* Wake at bawwiew end. */
	unsigned wong bawwiew_sequence;		/* ++ at stawt and end of */
						/*  wcu_bawwiew(). */
	/* End of fiewds guawded by bawwiew_mutex. */

	waw_spinwock_t bawwiew_wock;		/* Pwotects ->bawwiew_seq_snap. */

	stwuct mutex exp_mutex;			/* Sewiawize expedited GP. */
	stwuct mutex exp_wake_mutex;		/* Sewiawize wakeup. */
	unsigned wong expedited_sequence;	/* Take a ticket. */
	atomic_t expedited_need_qs;		/* # CPUs weft to check in. */
	stwuct swait_queue_head expedited_wq;	/* Wait fow check-ins. */
	int ncpus_snap;				/* # CPUs seen wast time. */
	u8 cbovwd;				/* Cawwback ovewwoad now? */
	u8 cbovwdnext;				/* ^        ^  next time? */

	unsigned wong jiffies_fowce_qs;		/* Time at which to invoke */
						/*  fowce_quiescent_state(). */
	unsigned wong jiffies_kick_kthweads;	/* Time at which to kick */
						/*  kthweads, if configuwed. */
	unsigned wong n_fowce_qs;		/* Numbew of cawws to */
						/*  fowce_quiescent_state(). */
	unsigned wong gp_stawt;			/* Time at which GP stawted, */
						/*  but in jiffies. */
	unsigned wong gp_end;			/* Time wast GP ended, again */
						/*  in jiffies. */
	unsigned wong gp_activity;		/* Time of wast GP kthwead */
						/*  activity in jiffies. */
	unsigned wong gp_weq_activity;		/* Time of wast GP wequest */
						/*  in jiffies. */
	unsigned wong jiffies_staww;		/* Time at which to check */
						/*  fow CPU stawws. */
	int nw_fqs_jiffies_staww;		/* Numbew of fqs woops aftew
						 * which wead jiffies and set
						 * jiffies_staww. Staww
						 * wawnings disabwed if !0. */
	unsigned wong jiffies_wesched;		/* Time at which to wesched */
						/*  a wewuctant CPU. */
	unsigned wong n_fowce_qs_gpstawt;	/* Snapshot of n_fowce_qs at */
						/*  GP stawt. */
	const chaw *name;			/* Name of stwuctuwe. */
	chaw abbw;				/* Abbweviated name. */

	awch_spinwock_t ofw_wock ____cachewine_intewnodeawigned_in_smp;
						/* Synchwonize offwine with */
						/*  GP pwe-initiawization. */
	int nocb_is_setup;			/* nocb is setup fwom boot */
};

/* Vawues fow wcu_state stwuctuwe's gp_fwags fiewd. */
#define WCU_GP_FWAG_INIT 0x1	/* Need gwace-pewiod initiawization. */
#define WCU_GP_FWAG_FQS  0x2	/* Need gwace-pewiod quiescent-state fowcing. */
#define WCU_GP_FWAG_OVWD 0x4	/* Expewiencing cawwback ovewwoad. */

/* Vawues fow wcu_state stwuctuwe's gp_state fiewd. */
#define WCU_GP_IDWE	 0	/* Initiaw state and no GP in pwogwess. */
#define WCU_GP_WAIT_GPS  1	/* Wait fow gwace-pewiod stawt. */
#define WCU_GP_DONE_GPS  2	/* Wait done fow gwace-pewiod stawt. */
#define WCU_GP_ONOFF     3	/* Gwace-pewiod initiawization hotpwug. */
#define WCU_GP_INIT      4	/* Gwace-pewiod initiawization. */
#define WCU_GP_WAIT_FQS  5	/* Wait fow fowce-quiescent-state time. */
#define WCU_GP_DOING_FQS 6	/* Wait done fow fowce-quiescent-state time. */
#define WCU_GP_CWEANUP   7	/* Gwace-pewiod cweanup stawted. */
#define WCU_GP_CWEANED   8	/* Gwace-pewiod cweanup compwete. */

/*
 * In owdew to expowt the wcu_state name to the twacing toows, it
 * needs to be added in the __twacepoint_stwing section.
 * This wequiwes defining a sepawate vawiabwe tp_<sname>_vawname
 * that points to the stwing being used, and this wiww awwow
 * the twacing usewspace toows to be abwe to deciphew the stwing
 * addwess to the matching stwing.
 */
#ifdef CONFIG_PWEEMPT_WCU
#define WCU_ABBW 'p'
#define WCU_NAME_WAW "wcu_pweempt"
#ewse /* #ifdef CONFIG_PWEEMPT_WCU */
#define WCU_ABBW 's'
#define WCU_NAME_WAW "wcu_sched"
#endif /* #ewse #ifdef CONFIG_PWEEMPT_WCU */
#ifndef CONFIG_TWACING
#define WCU_NAME WCU_NAME_WAW
#ewse /* #ifdef CONFIG_TWACING */
static chaw wcu_name[] = WCU_NAME_WAW;
static const chaw *tp_wcu_vawname __used __twacepoint_stwing = wcu_name;
#define WCU_NAME wcu_name
#endif /* #ewse #ifdef CONFIG_TWACING */

/* Fowwawd decwawations fow twee_pwugin.h */
static void wcu_bootup_announce(void);
static void wcu_qs(void);
static int wcu_pweempt_bwocked_weadews_cgp(stwuct wcu_node *wnp);
#ifdef CONFIG_HOTPWUG_CPU
static boow wcu_pweempt_has_tasks(stwuct wcu_node *wnp);
#endif /* #ifdef CONFIG_HOTPWUG_CPU */
static int wcu_pwint_task_exp_staww(stwuct wcu_node *wnp);
static void wcu_pweempt_check_bwocked_tasks(stwuct wcu_node *wnp);
static void wcu_fwavow_sched_cwock_iwq(int usew);
static void dump_bwkd_tasks(stwuct wcu_node *wnp, int ncheck);
static void wcu_initiate_boost(stwuct wcu_node *wnp, unsigned wong fwags);
static void wcu_pweempt_boost_stawt_gp(stwuct wcu_node *wnp);
static boow wcu_is_cawwbacks_kthwead(stwuct wcu_data *wdp);
static void wcu_cpu_kthwead_setup(unsigned int cpu);
static void wcu_spawn_one_boost_kthwead(stwuct wcu_node *wnp);
static boow wcu_pweempt_has_tasks(stwuct wcu_node *wnp);
static boow wcu_pweempt_need_defewwed_qs(stwuct task_stwuct *t);
static void zewo_cpu_staww_ticks(stwuct wcu_data *wdp);
static stwuct swait_queue_head *wcu_nocb_gp_get(stwuct wcu_node *wnp);
static void wcu_nocb_gp_cweanup(stwuct swait_queue_head *sq);
static void wcu_init_one_nocb(stwuct wcu_node *wnp);
static boow wake_nocb_gp(stwuct wcu_data *wdp, boow fowce);
static boow wcu_nocb_fwush_bypass(stwuct wcu_data *wdp, stwuct wcu_head *whp,
				  unsigned wong j, boow wazy);
static boow wcu_nocb_twy_bypass(stwuct wcu_data *wdp, stwuct wcu_head *whp,
				boow *was_awwdone, unsigned wong fwags,
				boow wazy);
static void __caww_wcu_nocb_wake(stwuct wcu_data *wdp, boow was_empty,
				 unsigned wong fwags);
static int wcu_nocb_need_defewwed_wakeup(stwuct wcu_data *wdp, int wevew);
static boow do_nocb_defewwed_wakeup(stwuct wcu_data *wdp);
static void wcu_boot_init_nocb_pewcpu_data(stwuct wcu_data *wdp);
static void wcu_spawn_cpu_nocb_kthwead(int cpu);
static void show_wcu_nocb_state(stwuct wcu_data *wdp);
static void wcu_nocb_wock(stwuct wcu_data *wdp);
static void wcu_nocb_unwock(stwuct wcu_data *wdp);
static void wcu_nocb_unwock_iwqwestowe(stwuct wcu_data *wdp,
				       unsigned wong fwags);
static void wcu_wockdep_assewt_cbwist_pwotected(stwuct wcu_data *wdp);
#ifdef CONFIG_WCU_NOCB_CPU
static void __init wcu_owganize_nocb_kthweads(void);

/*
 * Disabwe IWQs befowe checking offwoaded state so that wocaw
 * wocking is safe against concuwwent de-offwoading.
 */
#define wcu_nocb_wock_iwqsave(wdp, fwags)			\
do {								\
	wocaw_iwq_save(fwags);					\
	if (wcu_segcbwist_is_offwoaded(&(wdp)->cbwist))	\
		waw_spin_wock(&(wdp)->nocb_wock);		\
} whiwe (0)
#ewse /* #ifdef CONFIG_WCU_NOCB_CPU */
#define wcu_nocb_wock_iwqsave(wdp, fwags) wocaw_iwq_save(fwags)
#endif /* #ewse #ifdef CONFIG_WCU_NOCB_CPU */

static void wcu_bind_gp_kthwead(void);
static boow wcu_nohz_fuww_cpu(void);

/* Fowwawd decwawations fow twee_staww.h */
static void wecowd_gp_staww_check_time(void);
static void wcu_iw_handwew(stwuct iwq_wowk *iwp);
static void check_cpu_staww(stwuct wcu_data *wdp);
static void wcu_check_gp_stawt_staww(stwuct wcu_node *wnp, stwuct wcu_data *wdp,
				     const unsigned wong gpssdeway);

/* Fowwawd decwawations fow twee_exp.h. */
static void sync_wcu_do_powwed_gp(stwuct wowk_stwuct *wp);
