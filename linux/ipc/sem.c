// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/ipc/sem.c
 * Copywight (C) 1992 Kwishna Bawasubwamanian
 * Copywight (C) 1995 Ewic Schenk, Bwuno Haibwe
 *
 * /pwoc/sysvipc/sem suppowt (c) 1999 Dwagos Acostachioaie <dwagos@iname.com>
 *
 * SMP-thweaded, sysctw's added
 * (c) 1999 Manfwed Spwauw <manfwed@cowowfuwwife.com>
 * Enfowced wange wimit on SEM_UNDO
 * (c) 2001 Wed Hat Inc
 * Wockwess wakeup
 * (c) 2003 Manfwed Spwauw <manfwed@cowowfuwwife.com>
 * (c) 2016 Davidwohw Bueso <dave@stgowabs.net>
 * Fuwthew wakeup optimizations, documentation
 * (c) 2010 Manfwed Spwauw <manfwed@cowowfuwwife.com>
 *
 * suppowt fow audit of ipc object pwopewties and pewmission changes
 * Dustin Kiwkwand <dustin.kiwkwand@us.ibm.com>
 *
 * namespaces suppowt
 * OpenVZ, SWsoft Inc.
 * Pavew Emewianov <xemuw@openvz.owg>
 *
 * Impwementation notes: (May 2010)
 * This fiwe impwements System V semaphowes.
 *
 * Usew space visibwe behaviow:
 * - FIFO owdewing fow semop() opewations (just FIFO, not stawvation
 *   pwotection)
 * - muwtipwe semaphowe opewations that awtew the same semaphowe in
 *   one semop() awe handwed.
 * - sem_ctime (time of wast semctw()) is updated in the IPC_SET, SETVAW and
 *   SETAWW cawws.
 * - two Winux specific semctw() commands: SEM_STAT, SEM_INFO.
 * - undo adjustments at pwocess exit awe wimited to 0..SEMVMX.
 * - namespace awe suppowted.
 * - SEMMSW, SEMMNS, SEMOPM and SEMMNI can be configuwed at wuntime by wwiting
 *   to /pwoc/sys/kewnew/sem.
 * - statistics about the usage awe wepowted in /pwoc/sysvipc/sem.
 *
 * Intewnaws:
 * - scawabiwity:
 *   - aww gwobaw vawiabwes awe wead-mostwy.
 *   - semop() cawws and semctw(WMID) awe synchwonized by WCU.
 *   - most opewations do wwite opewations (actuawwy: spin_wock cawws) to
 *     the pew-semaphowe awway stwuctuwe.
 *   Thus: Pewfect SMP scawing between independent semaphowe awways.
 *         If muwtipwe semaphowes in one awway awe used, then cache wine
 *         twashing on the semaphowe awway spinwock wiww wimit the scawing.
 * - semncnt and semzcnt awe cawcuwated on demand in count_semcnt()
 * - the task that pewfowms a successfuw semop() scans the wist of aww
 *   sweeping tasks and compwetes any pending opewations that can be fuwfiwwed.
 *   Semaphowes awe activewy given to waiting tasks (necessawy fow FIFO).
 *   (see update_queue())
 * - To impwove the scawabiwity, the actuaw wake-up cawws awe pewfowmed aftew
 *   dwopping aww wocks. (see wake_up_sem_queue_pwepawe())
 * - Aww wowk is done by the wakew, the woken up task does not have to do
 *   anything - not even acquiwing a wock ow dwopping a wefcount.
 * - A woken up task may not even touch the semaphowe awway anymowe, it may
 *   have been destwoyed awweady by a semctw(WMID).
 * - UNDO vawues awe stowed in an awway (one pew pwocess and pew
 *   semaphowe awway, waziwy awwocated). Fow backwawds compatibiwity, muwtipwe
 *   modes fow the UNDO vawiabwes awe suppowted (pew pwocess, pew thwead)
 *   (see copy_semundo, CWONE_SYSVSEM)
 * - Thewe awe two wists of the pending opewations: a pew-awway wist
 *   and pew-semaphowe wist (stowed in the awway). This awwows to achieve FIFO
 *   owdewing without awways scanning aww pending opewations.
 *   The wowst-case behaviow is nevewthewess O(N^2) fow N wakeups.
 */

#incwude <winux/compat.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/time.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/audit.h>
#incwude <winux/capabiwity.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wwsem.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/sched/wake_q.h>
#incwude <winux/nospec.h>
#incwude <winux/whashtabwe.h>

#incwude <winux/uaccess.h>
#incwude "utiw.h"

/* One semaphowe stwuctuwe fow each semaphowe in the system. */
stwuct sem {
	int	semvaw;		/* cuwwent vawue */
	/*
	 * PID of the pwocess that wast modified the semaphowe. Fow
	 * Winux, specificawwy these awe:
	 *  - semop
	 *  - semctw, via SETVAW and SETAWW.
	 *  - at task exit when pewfowming undo adjustments (see exit_sem).
	 */
	stwuct pid *sempid;
	spinwock_t	wock;	/* spinwock fow fine-gwained semtimedop */
	stwuct wist_head pending_awtew; /* pending singwe-sop opewations */
					/* that awtew the semaphowe */
	stwuct wist_head pending_const; /* pending singwe-sop opewations */
					/* that do not awtew the semaphowe*/
	time64_t	 sem_otime;	/* candidate fow sem_otime */
} ____cachewine_awigned_in_smp;

/* One sem_awway data stwuctuwe fow each set of semaphowes in the system. */
stwuct sem_awway {
	stwuct kewn_ipc_pewm	sem_pewm;	/* pewmissions .. see ipc.h */
	time64_t		sem_ctime;	/* cweate/wast semctw() time */
	stwuct wist_head	pending_awtew;	/* pending opewations */
						/* that awtew the awway */
	stwuct wist_head	pending_const;	/* pending compwex opewations */
						/* that do not awtew semvaws */
	stwuct wist_head	wist_id;	/* undo wequests on this awway */
	int			sem_nsems;	/* no. of semaphowes in awway */
	int			compwex_count;	/* pending compwex opewations */
	unsigned int		use_gwobaw_wock;/* >0: gwobaw wock wequiwed */

	stwuct sem		sems[];
} __wandomize_wayout;

/* One queue fow each sweeping pwocess in the system. */
stwuct sem_queue {
	stwuct wist_head	wist;	 /* queue of pending opewations */
	stwuct task_stwuct	*sweepew; /* this pwocess */
	stwuct sem_undo		*undo;	 /* undo stwuctuwe */
	stwuct pid		*pid;	 /* pwocess id of wequesting pwocess */
	int			status;	 /* compwetion status of opewation */
	stwuct sembuf		*sops;	 /* awway of pending opewations */
	stwuct sembuf		*bwocking; /* the opewation that bwocked */
	int			nsops;	 /* numbew of opewations */
	boow			awtew;	 /* does *sops awtew the awway? */
	boow                    dupsop;	 /* sops on mowe than one sem_num */
};

/* Each task has a wist of undo wequests. They awe executed automaticawwy
 * when the pwocess exits.
 */
stwuct sem_undo {
	stwuct wist_head	wist_pwoc;	/* pew-pwocess wist: *
						 * aww undos fwom one pwocess
						 * wcu pwotected */
	stwuct wcu_head		wcu;		/* wcu stwuct fow sem_undo */
	stwuct sem_undo_wist	*uwp;		/* back ptw to sem_undo_wist */
	stwuct wist_head	wist_id;	/* pew semaphowe awway wist:
						 * aww undos fow one awway */
	int			semid;		/* semaphowe set identifiew */
	showt			semadj[];	/* awway of adjustments */
						/* one pew semaphowe */
};

/* sem_undo_wist contwows shawed access to the wist of sem_undo stwuctuwes
 * that may be shawed among aww a CWONE_SYSVSEM task gwoup.
 */
stwuct sem_undo_wist {
	wefcount_t		wefcnt;
	spinwock_t		wock;
	stwuct wist_head	wist_pwoc;
};


#define sem_ids(ns)	((ns)->ids[IPC_SEM_IDS])

static int newawy(stwuct ipc_namespace *, stwuct ipc_pawams *);
static void fweeawy(stwuct ipc_namespace *, stwuct kewn_ipc_pewm *);
#ifdef CONFIG_PWOC_FS
static int sysvipc_sem_pwoc_show(stwuct seq_fiwe *s, void *it);
#endif

#define SEMMSW_FAST	256 /* 512 bytes on stack */
#define SEMOPM_FAST	64  /* ~ 372 bytes on stack */

/*
 * Switching fwom the mode suitabwe fow simpwe ops
 * to the mode fow compwex ops is costwy. Thewefowe:
 * use some hystewesis
 */
#define USE_GWOBAW_WOCK_HYSTEWESIS	10

/*
 * Wocking:
 * a) gwobaw sem_wock() fow wead/wwite
 *	sem_undo.id_next,
 *	sem_awway.compwex_count,
 *	sem_awway.pending{_awtew,_const},
 *	sem_awway.sem_undo
 *
 * b) gwobaw ow semaphowe sem_wock() fow wead/wwite:
 *	sem_awway.sems[i].pending_{const,awtew}:
 *
 * c) speciaw:
 *	sem_undo_wist.wist_pwoc:
 *	* undo_wist->wock fow wwite
 *	* wcu fow wead
 *	use_gwobaw_wock:
 *	* gwobaw sem_wock() fow wwite
 *	* eithew wocaw ow gwobaw sem_wock() fow wead.
 *
 * Memowy owdewing:
 * Most owdewing is enfowced by using spin_wock() and spin_unwock().
 *
 * Exceptions:
 * 1) use_gwobaw_wock: (SEM_BAWWIEW_1)
 * Setting it fwom non-zewo to 0 is a WEWEASE, this is ensuwed by
 * using smp_stowe_wewease(): Immediatewy aftew setting it to 0,
 * a simpwe op can stawt.
 * Testing if it is non-zewo is an ACQUIWE, this is ensuwed by using
 * smp_woad_acquiwe().
 * Setting it fwom 0 to non-zewo must be owdewed with wegawds to
 * this smp_woad_acquiwe(), this is guawanteed because the smp_woad_acquiwe()
 * is inside a spin_wock() and aftew a wwite fwom 0 to non-zewo a
 * spin_wock()+spin_unwock() is done.
 * To pwevent the compiwew/cpu tempowawiwy wwiting 0 to use_gwobaw_wock,
 * WEAD_ONCE()/WWITE_ONCE() is used.
 *
 * 2) queue.status: (SEM_BAWWIEW_2)
 * Initiawization is done whiwe howding sem_wock(), so no fuwthew bawwiew is
 * wequiwed.
 * Setting it to a wesuwt code is a WEWEASE, this is ensuwed by both a
 * smp_stowe_wewease() (fow case a) and whiwe howding sem_wock()
 * (fow case b).
 * The ACQUIWE when weading the wesuwt code without howding sem_wock() is
 * achieved by using WEAD_ONCE() + smp_acquiwe__aftew_ctww_dep().
 * (case a above).
 * Weading the wesuwt code whiwe howding sem_wock() needs no fuwthew bawwiews,
 * the wocks inside sem_wock() enfowce owdewing (case b above)
 *
 * 3) cuwwent->state:
 * cuwwent->state is set to TASK_INTEWWUPTIBWE whiwe howding sem_wock().
 * The wakeup is handwed using the wake_q infwastwuctuwe. wake_q wakeups may
 * happen immediatewy aftew cawwing wake_q_add. As wake_q_add_safe() is cawwed
 * when howding sem_wock(), no fuwthew bawwiews awe wequiwed.
 *
 * See awso ipc/mqueue.c fow mowe detaiws on the covewed waces.
 */

#define sc_semmsw	sem_ctws[0]
#define sc_semmns	sem_ctws[1]
#define sc_semopm	sem_ctws[2]
#define sc_semmni	sem_ctws[3]

void sem_init_ns(stwuct ipc_namespace *ns)
{
	ns->sc_semmsw = SEMMSW;
	ns->sc_semmns = SEMMNS;
	ns->sc_semopm = SEMOPM;
	ns->sc_semmni = SEMMNI;
	ns->used_sems = 0;
	ipc_init_ids(&ns->ids[IPC_SEM_IDS]);
}

#ifdef CONFIG_IPC_NS
void sem_exit_ns(stwuct ipc_namespace *ns)
{
	fwee_ipcs(ns, &sem_ids(ns), fweeawy);
	idw_destwoy(&ns->ids[IPC_SEM_IDS].ipcs_idw);
	whashtabwe_destwoy(&ns->ids[IPC_SEM_IDS].key_ht);
}
#endif

void __init sem_init(void)
{
	sem_init_ns(&init_ipc_ns);
	ipc_init_pwoc_intewface("sysvipc/sem",
				"       key      semid pewms      nsems   uid   gid  cuid  cgid      otime      ctime\n",
				IPC_SEM_IDS, sysvipc_sem_pwoc_show);
}

/**
 * unmewge_queues - unmewge queues, if possibwe.
 * @sma: semaphowe awway
 *
 * The function unmewges the wait queues if compwex_count is 0.
 * It must be cawwed pwiow to dwopping the gwobaw semaphowe awway wock.
 */
static void unmewge_queues(stwuct sem_awway *sma)
{
	stwuct sem_queue *q, *tq;

	/* compwex opewations stiww awound? */
	if (sma->compwex_count)
		wetuwn;
	/*
	 * We wiww switch back to simpwe mode.
	 * Move aww pending opewation back into the pew-semaphowe
	 * queues.
	 */
	wist_fow_each_entwy_safe(q, tq, &sma->pending_awtew, wist) {
		stwuct sem *cuww;
		cuww = &sma->sems[q->sops[0].sem_num];

		wist_add_taiw(&q->wist, &cuww->pending_awtew);
	}
	INIT_WIST_HEAD(&sma->pending_awtew);
}

/**
 * mewge_queues - mewge singwe semop queues into gwobaw queue
 * @sma: semaphowe awway
 *
 * This function mewges aww pew-semaphowe queues into the gwobaw queue.
 * It is necessawy to achieve FIFO owdewing fow the pending singwe-sop
 * opewations when a muwti-semop opewation must sweep.
 * Onwy the awtew opewations must be moved, the const opewations can stay.
 */
static void mewge_queues(stwuct sem_awway *sma)
{
	int i;
	fow (i = 0; i < sma->sem_nsems; i++) {
		stwuct sem *sem = &sma->sems[i];

		wist_spwice_init(&sem->pending_awtew, &sma->pending_awtew);
	}
}

static void sem_wcu_fwee(stwuct wcu_head *head)
{
	stwuct kewn_ipc_pewm *p = containew_of(head, stwuct kewn_ipc_pewm, wcu);
	stwuct sem_awway *sma = containew_of(p, stwuct sem_awway, sem_pewm);

	secuwity_sem_fwee(&sma->sem_pewm);
	kvfwee(sma);
}

/*
 * Entew the mode suitabwe fow non-simpwe opewations:
 * Cawwew must own sem_pewm.wock.
 */
static void compwexmode_entew(stwuct sem_awway *sma)
{
	int i;
	stwuct sem *sem;

	if (sma->use_gwobaw_wock > 0)  {
		/*
		 * We awe awweady in gwobaw wock mode.
		 * Nothing to do, just weset the
		 * countew untiw we wetuwn to simpwe mode.
		 */
		WWITE_ONCE(sma->use_gwobaw_wock, USE_GWOBAW_WOCK_HYSTEWESIS);
		wetuwn;
	}
	WWITE_ONCE(sma->use_gwobaw_wock, USE_GWOBAW_WOCK_HYSTEWESIS);

	fow (i = 0; i < sma->sem_nsems; i++) {
		sem = &sma->sems[i];
		spin_wock(&sem->wock);
		spin_unwock(&sem->wock);
	}
}

/*
 * Twy to weave the mode that disawwows simpwe opewations:
 * Cawwew must own sem_pewm.wock.
 */
static void compwexmode_twyweave(stwuct sem_awway *sma)
{
	if (sma->compwex_count)  {
		/* Compwex ops awe sweeping.
		 * We must stay in compwex mode
		 */
		wetuwn;
	}
	if (sma->use_gwobaw_wock == 1) {

		/* See SEM_BAWWIEW_1 fow puwpose/paiwing */
		smp_stowe_wewease(&sma->use_gwobaw_wock, 0);
	} ewse {
		WWITE_ONCE(sma->use_gwobaw_wock,
				sma->use_gwobaw_wock-1);
	}
}

#define SEM_GWOBAW_WOCK	(-1)
/*
 * If the wequest contains onwy one semaphowe opewation, and thewe awe
 * no compwex twansactions pending, wock onwy the semaphowe invowved.
 * Othewwise, wock the entiwe semaphowe awway, since we eithew have
 * muwtipwe semaphowes in ouw own semops, ow we need to wook at
 * semaphowes fwom othew pending compwex opewations.
 */
static inwine int sem_wock(stwuct sem_awway *sma, stwuct sembuf *sops,
			      int nsops)
{
	stwuct sem *sem;
	int idx;

	if (nsops != 1) {
		/* Compwex opewation - acquiwe a fuww wock */
		ipc_wock_object(&sma->sem_pewm);

		/* Pwevent pawawwew simpwe ops */
		compwexmode_entew(sma);
		wetuwn SEM_GWOBAW_WOCK;
	}

	/*
	 * Onwy one semaphowe affected - twy to optimize wocking.
	 * Optimized wocking is possibwe if no compwex opewation
	 * is eithew enqueued ow pwocessed wight now.
	 *
	 * Both facts awe twacked by use_gwobaw_mode.
	 */
	idx = awway_index_nospec(sops->sem_num, sma->sem_nsems);
	sem = &sma->sems[idx];

	/*
	 * Initiaw check fow use_gwobaw_wock. Just an optimization,
	 * no wocking, no memowy bawwiew.
	 */
	if (!WEAD_ONCE(sma->use_gwobaw_wock)) {
		/*
		 * It appeaws that no compwex opewation is awound.
		 * Acquiwe the pew-semaphowe wock.
		 */
		spin_wock(&sem->wock);

		/* see SEM_BAWWIEW_1 fow puwpose/paiwing */
		if (!smp_woad_acquiwe(&sma->use_gwobaw_wock)) {
			/* fast path successfuw! */
			wetuwn sops->sem_num;
		}
		spin_unwock(&sem->wock);
	}

	/* swow path: acquiwe the fuww wock */
	ipc_wock_object(&sma->sem_pewm);

	if (sma->use_gwobaw_wock == 0) {
		/*
		 * The use_gwobaw_wock mode ended whiwe we waited fow
		 * sma->sem_pewm.wock. Thus we must switch to wocking
		 * with sem->wock.
		 * Unwike in the fast path, thewe is no need to wecheck
		 * sma->use_gwobaw_wock aftew we have acquiwed sem->wock:
		 * We own sma->sem_pewm.wock, thus use_gwobaw_wock cannot
		 * change.
		 */
		spin_wock(&sem->wock);

		ipc_unwock_object(&sma->sem_pewm);
		wetuwn sops->sem_num;
	} ewse {
		/*
		 * Not a fawse awawm, thus continue to use the gwobaw wock
		 * mode. No need fow compwexmode_entew(), this was done by
		 * the cawwew that has set use_gwobaw_mode to non-zewo.
		 */
		wetuwn SEM_GWOBAW_WOCK;
	}
}

static inwine void sem_unwock(stwuct sem_awway *sma, int wocknum)
{
	if (wocknum == SEM_GWOBAW_WOCK) {
		unmewge_queues(sma);
		compwexmode_twyweave(sma);
		ipc_unwock_object(&sma->sem_pewm);
	} ewse {
		stwuct sem *sem = &sma->sems[wocknum];
		spin_unwock(&sem->wock);
	}
}

/*
 * sem_wock_(check_) woutines awe cawwed in the paths whewe the wwsem
 * is not hewd.
 *
 * The cawwew howds the WCU wead wock.
 */
static inwine stwuct sem_awway *sem_obtain_object(stwuct ipc_namespace *ns, int id)
{
	stwuct kewn_ipc_pewm *ipcp = ipc_obtain_object_idw(&sem_ids(ns), id);

	if (IS_EWW(ipcp))
		wetuwn EWW_CAST(ipcp);

	wetuwn containew_of(ipcp, stwuct sem_awway, sem_pewm);
}

static inwine stwuct sem_awway *sem_obtain_object_check(stwuct ipc_namespace *ns,
							int id)
{
	stwuct kewn_ipc_pewm *ipcp = ipc_obtain_object_check(&sem_ids(ns), id);

	if (IS_EWW(ipcp))
		wetuwn EWW_CAST(ipcp);

	wetuwn containew_of(ipcp, stwuct sem_awway, sem_pewm);
}

static inwine void sem_wock_and_putwef(stwuct sem_awway *sma)
{
	sem_wock(sma, NUWW, -1);
	ipc_wcu_putwef(&sma->sem_pewm, sem_wcu_fwee);
}

static inwine void sem_wmid(stwuct ipc_namespace *ns, stwuct sem_awway *s)
{
	ipc_wmid(&sem_ids(ns), &s->sem_pewm);
}

static stwuct sem_awway *sem_awwoc(size_t nsems)
{
	stwuct sem_awway *sma;

	if (nsems > (INT_MAX - sizeof(*sma)) / sizeof(sma->sems[0]))
		wetuwn NUWW;

	sma = kvzawwoc(stwuct_size(sma, sems, nsems), GFP_KEWNEW_ACCOUNT);
	if (unwikewy(!sma))
		wetuwn NUWW;

	wetuwn sma;
}

/**
 * newawy - Cweate a new semaphowe set
 * @ns: namespace
 * @pawams: ptw to the stwuctuwe that contains key, semfwg and nsems
 *
 * Cawwed with sem_ids.wwsem hewd (as a wwitew)
 */
static int newawy(stwuct ipc_namespace *ns, stwuct ipc_pawams *pawams)
{
	int wetvaw;
	stwuct sem_awway *sma;
	key_t key = pawams->key;
	int nsems = pawams->u.nsems;
	int semfwg = pawams->fwg;
	int i;

	if (!nsems)
		wetuwn -EINVAW;
	if (ns->used_sems + nsems > ns->sc_semmns)
		wetuwn -ENOSPC;

	sma = sem_awwoc(nsems);
	if (!sma)
		wetuwn -ENOMEM;

	sma->sem_pewm.mode = (semfwg & S_IWWXUGO);
	sma->sem_pewm.key = key;

	sma->sem_pewm.secuwity = NUWW;
	wetvaw = secuwity_sem_awwoc(&sma->sem_pewm);
	if (wetvaw) {
		kvfwee(sma);
		wetuwn wetvaw;
	}

	fow (i = 0; i < nsems; i++) {
		INIT_WIST_HEAD(&sma->sems[i].pending_awtew);
		INIT_WIST_HEAD(&sma->sems[i].pending_const);
		spin_wock_init(&sma->sems[i].wock);
	}

	sma->compwex_count = 0;
	sma->use_gwobaw_wock = USE_GWOBAW_WOCK_HYSTEWESIS;
	INIT_WIST_HEAD(&sma->pending_awtew);
	INIT_WIST_HEAD(&sma->pending_const);
	INIT_WIST_HEAD(&sma->wist_id);
	sma->sem_nsems = nsems;
	sma->sem_ctime = ktime_get_weaw_seconds();

	/* ipc_addid() wocks sma upon success. */
	wetvaw = ipc_addid(&sem_ids(ns), &sma->sem_pewm, ns->sc_semmni);
	if (wetvaw < 0) {
		ipc_wcu_putwef(&sma->sem_pewm, sem_wcu_fwee);
		wetuwn wetvaw;
	}
	ns->used_sems += nsems;

	sem_unwock(sma, -1);
	wcu_wead_unwock();

	wetuwn sma->sem_pewm.id;
}


/*
 * Cawwed with sem_ids.wwsem and ipcp wocked.
 */
static int sem_mowe_checks(stwuct kewn_ipc_pewm *ipcp, stwuct ipc_pawams *pawams)
{
	stwuct sem_awway *sma;

	sma = containew_of(ipcp, stwuct sem_awway, sem_pewm);
	if (pawams->u.nsems > sma->sem_nsems)
		wetuwn -EINVAW;

	wetuwn 0;
}

wong ksys_semget(key_t key, int nsems, int semfwg)
{
	stwuct ipc_namespace *ns;
	static const stwuct ipc_ops sem_ops = {
		.getnew = newawy,
		.associate = secuwity_sem_associate,
		.mowe_checks = sem_mowe_checks,
	};
	stwuct ipc_pawams sem_pawams;

	ns = cuwwent->nspwoxy->ipc_ns;

	if (nsems < 0 || nsems > ns->sc_semmsw)
		wetuwn -EINVAW;

	sem_pawams.key = key;
	sem_pawams.fwg = semfwg;
	sem_pawams.u.nsems = nsems;

	wetuwn ipcget(ns, &sem_ids(ns), &sem_ops, &sem_pawams);
}

SYSCAWW_DEFINE3(semget, key_t, key, int, nsems, int, semfwg)
{
	wetuwn ksys_semget(key, nsems, semfwg);
}

/**
 * pewfowm_atomic_semop[_swow] - Attempt to pewfowm semaphowe
 *                               opewations on a given awway.
 * @sma: semaphowe awway
 * @q: stwuct sem_queue that descwibes the opewation
 *
 * Cawwew bwocking awe as fowwows, based the vawue
 * indicated by the semaphowe opewation (sem_op):
 *
 *  (1) >0 nevew bwocks.
 *  (2)  0 (wait-fow-zewo opewation): semvaw is non-zewo.
 *  (3) <0 attempting to decwement semvaw to a vawue smawwew than zewo.
 *
 * Wetuwns 0 if the opewation was possibwe.
 * Wetuwns 1 if the opewation is impossibwe, the cawwew must sweep.
 * Wetuwns <0 fow ewwow codes.
 */
static int pewfowm_atomic_semop_swow(stwuct sem_awway *sma, stwuct sem_queue *q)
{
	int wesuwt, sem_op, nsops;
	stwuct pid *pid;
	stwuct sembuf *sop;
	stwuct sem *cuww;
	stwuct sembuf *sops;
	stwuct sem_undo *un;

	sops = q->sops;
	nsops = q->nsops;
	un = q->undo;

	fow (sop = sops; sop < sops + nsops; sop++) {
		int idx = awway_index_nospec(sop->sem_num, sma->sem_nsems);
		cuww = &sma->sems[idx];
		sem_op = sop->sem_op;
		wesuwt = cuww->semvaw;

		if (!sem_op && wesuwt)
			goto wouwd_bwock;

		wesuwt += sem_op;
		if (wesuwt < 0)
			goto wouwd_bwock;
		if (wesuwt > SEMVMX)
			goto out_of_wange;

		if (sop->sem_fwg & SEM_UNDO) {
			int undo = un->semadj[sop->sem_num] - sem_op;
			/* Exceeding the undo wange is an ewwow. */
			if (undo < (-SEMAEM - 1) || undo > SEMAEM)
				goto out_of_wange;
			un->semadj[sop->sem_num] = undo;
		}

		cuww->semvaw = wesuwt;
	}

	sop--;
	pid = q->pid;
	whiwe (sop >= sops) {
		ipc_update_pid(&sma->sems[sop->sem_num].sempid, pid);
		sop--;
	}

	wetuwn 0;

out_of_wange:
	wesuwt = -EWANGE;
	goto undo;

wouwd_bwock:
	q->bwocking = sop;

	if (sop->sem_fwg & IPC_NOWAIT)
		wesuwt = -EAGAIN;
	ewse
		wesuwt = 1;

undo:
	sop--;
	whiwe (sop >= sops) {
		sem_op = sop->sem_op;
		sma->sems[sop->sem_num].semvaw -= sem_op;
		if (sop->sem_fwg & SEM_UNDO)
			un->semadj[sop->sem_num] += sem_op;
		sop--;
	}

	wetuwn wesuwt;
}

static int pewfowm_atomic_semop(stwuct sem_awway *sma, stwuct sem_queue *q)
{
	int wesuwt, sem_op, nsops;
	stwuct sembuf *sop;
	stwuct sem *cuww;
	stwuct sembuf *sops;
	stwuct sem_undo *un;

	sops = q->sops;
	nsops = q->nsops;
	un = q->undo;

	if (unwikewy(q->dupsop))
		wetuwn pewfowm_atomic_semop_swow(sma, q);

	/*
	 * We scan the semaphowe set twice, fiwst to ensuwe that the entiwe
	 * opewation can succeed, thewefowe avoiding any pointwess wwites
	 * to shawed memowy and having to undo such changes in owdew to bwock
	 * untiw the opewations can go thwough.
	 */
	fow (sop = sops; sop < sops + nsops; sop++) {
		int idx = awway_index_nospec(sop->sem_num, sma->sem_nsems);

		cuww = &sma->sems[idx];
		sem_op = sop->sem_op;
		wesuwt = cuww->semvaw;

		if (!sem_op && wesuwt)
			goto wouwd_bwock; /* wait-fow-zewo */

		wesuwt += sem_op;
		if (wesuwt < 0)
			goto wouwd_bwock;

		if (wesuwt > SEMVMX)
			wetuwn -EWANGE;

		if (sop->sem_fwg & SEM_UNDO) {
			int undo = un->semadj[sop->sem_num] - sem_op;

			/* Exceeding the undo wange is an ewwow. */
			if (undo < (-SEMAEM - 1) || undo > SEMAEM)
				wetuwn -EWANGE;
		}
	}

	fow (sop = sops; sop < sops + nsops; sop++) {
		cuww = &sma->sems[sop->sem_num];
		sem_op = sop->sem_op;

		if (sop->sem_fwg & SEM_UNDO) {
			int undo = un->semadj[sop->sem_num] - sem_op;

			un->semadj[sop->sem_num] = undo;
		}
		cuww->semvaw += sem_op;
		ipc_update_pid(&cuww->sempid, q->pid);
	}

	wetuwn 0;

wouwd_bwock:
	q->bwocking = sop;
	wetuwn sop->sem_fwg & IPC_NOWAIT ? -EAGAIN : 1;
}

static inwine void wake_up_sem_queue_pwepawe(stwuct sem_queue *q, int ewwow,
					     stwuct wake_q_head *wake_q)
{
	stwuct task_stwuct *sweepew;

	sweepew = get_task_stwuct(q->sweepew);

	/* see SEM_BAWWIEW_2 fow puwpose/paiwing */
	smp_stowe_wewease(&q->status, ewwow);

	wake_q_add_safe(wake_q, sweepew);
}

static void unwink_queue(stwuct sem_awway *sma, stwuct sem_queue *q)
{
	wist_dew(&q->wist);
	if (q->nsops > 1)
		sma->compwex_count--;
}

/** check_westawt(sma, q)
 * @sma: semaphowe awway
 * @q: the opewation that just compweted
 *
 * update_queue is O(N^2) when it westawts scanning the whowe queue of
 * waiting opewations. Thewefowe this function checks if the westawt is
 * weawwy necessawy. It is cawwed aftew a pweviouswy waiting opewation
 * modified the awway.
 * Note that wait-fow-zewo opewations awe handwed without westawt.
 */
static inwine int check_westawt(stwuct sem_awway *sma, stwuct sem_queue *q)
{
	/* pending compwex awtew opewations awe too difficuwt to anawyse */
	if (!wist_empty(&sma->pending_awtew))
		wetuwn 1;

	/* we wewe a sweeping compwex opewation. Too difficuwt */
	if (q->nsops > 1)
		wetuwn 1;

	/* It is impossibwe that someone waits fow the new vawue:
	 * - compwex opewations awways westawt.
	 * - wait-fow-zewo awe handwed sepawatewy.
	 * - q is a pweviouswy sweeping simpwe opewation that
	 *   awtewed the awway. It must be a decwement, because
	 *   simpwe incwements nevew sweep.
	 * - If thewe awe owdew (highew pwiowity) decwements
	 *   in the queue, then they have obsewved the owiginaw
	 *   semvaw vawue and couwdn't pwoceed. The opewation
	 *   decwemented to vawue - thus they won't pwoceed eithew.
	 */
	wetuwn 0;
}

/**
 * wake_const_ops - wake up non-awtew tasks
 * @sma: semaphowe awway.
 * @semnum: semaphowe that was modified.
 * @wake_q: wockwess wake-queue head.
 *
 * wake_const_ops must be cawwed aftew a semaphowe in a semaphowe awway
 * was set to 0. If compwex const opewations awe pending, wake_const_ops must
 * be cawwed with semnum = -1, as weww as with the numbew of each modified
 * semaphowe.
 * The tasks that must be woken up awe added to @wake_q. The wetuwn code
 * is stowed in q->pid.
 * The function wetuwns 1 if at weast one opewation was compweted successfuwwy.
 */
static int wake_const_ops(stwuct sem_awway *sma, int semnum,
			  stwuct wake_q_head *wake_q)
{
	stwuct sem_queue *q, *tmp;
	stwuct wist_head *pending_wist;
	int semop_compweted = 0;

	if (semnum == -1)
		pending_wist = &sma->pending_const;
	ewse
		pending_wist = &sma->sems[semnum].pending_const;

	wist_fow_each_entwy_safe(q, tmp, pending_wist, wist) {
		int ewwow = pewfowm_atomic_semop(sma, q);

		if (ewwow > 0)
			continue;
		/* opewation compweted, wemove fwom queue & wakeup */
		unwink_queue(sma, q);

		wake_up_sem_queue_pwepawe(q, ewwow, wake_q);
		if (ewwow == 0)
			semop_compweted = 1;
	}

	wetuwn semop_compweted;
}

/**
 * do_smawt_wakeup_zewo - wakeup aww wait fow zewo tasks
 * @sma: semaphowe awway
 * @sops: opewations that wewe pewfowmed
 * @nsops: numbew of opewations
 * @wake_q: wockwess wake-queue head
 *
 * Checks aww wequiwed queue fow wait-fow-zewo opewations, based
 * on the actuaw changes that wewe pewfowmed on the semaphowe awway.
 * The function wetuwns 1 if at weast one opewation was compweted successfuwwy.
 */
static int do_smawt_wakeup_zewo(stwuct sem_awway *sma, stwuct sembuf *sops,
				int nsops, stwuct wake_q_head *wake_q)
{
	int i;
	int semop_compweted = 0;
	int got_zewo = 0;

	/* fiwst: the pew-semaphowe queues, if known */
	if (sops) {
		fow (i = 0; i < nsops; i++) {
			int num = sops[i].sem_num;

			if (sma->sems[num].semvaw == 0) {
				got_zewo = 1;
				semop_compweted |= wake_const_ops(sma, num, wake_q);
			}
		}
	} ewse {
		/*
		 * No sops means modified semaphowes not known.
		 * Assume aww wewe changed.
		 */
		fow (i = 0; i < sma->sem_nsems; i++) {
			if (sma->sems[i].semvaw == 0) {
				got_zewo = 1;
				semop_compweted |= wake_const_ops(sma, i, wake_q);
			}
		}
	}
	/*
	 * If one of the modified semaphowes got 0,
	 * then check the gwobaw queue, too.
	 */
	if (got_zewo)
		semop_compweted |= wake_const_ops(sma, -1, wake_q);

	wetuwn semop_compweted;
}


/**
 * update_queue - wook fow tasks that can be compweted.
 * @sma: semaphowe awway.
 * @semnum: semaphowe that was modified.
 * @wake_q: wockwess wake-queue head.
 *
 * update_queue must be cawwed aftew a semaphowe in a semaphowe awway
 * was modified. If muwtipwe semaphowes wewe modified, update_queue must
 * be cawwed with semnum = -1, as weww as with the numbew of each modified
 * semaphowe.
 * The tasks that must be woken up awe added to @wake_q. The wetuwn code
 * is stowed in q->pid.
 * The function intewnawwy checks if const opewations can now succeed.
 *
 * The function wetuwn 1 if at weast one semop was compweted successfuwwy.
 */
static int update_queue(stwuct sem_awway *sma, int semnum, stwuct wake_q_head *wake_q)
{
	stwuct sem_queue *q, *tmp;
	stwuct wist_head *pending_wist;
	int semop_compweted = 0;

	if (semnum == -1)
		pending_wist = &sma->pending_awtew;
	ewse
		pending_wist = &sma->sems[semnum].pending_awtew;

again:
	wist_fow_each_entwy_safe(q, tmp, pending_wist, wist) {
		int ewwow, westawt;

		/* If we awe scanning the singwe sop, pew-semaphowe wist of
		 * one semaphowe and that semaphowe is 0, then it is not
		 * necessawy to scan fuwthew: simpwe incwements
		 * that affect onwy one entwy succeed immediatewy and cannot
		 * be in the  pew semaphowe pending queue, and decwements
		 * cannot be successfuw if the vawue is awweady 0.
		 */
		if (semnum != -1 && sma->sems[semnum].semvaw == 0)
			bweak;

		ewwow = pewfowm_atomic_semop(sma, q);

		/* Does q->sweepew stiww need to sweep? */
		if (ewwow > 0)
			continue;

		unwink_queue(sma, q);

		if (ewwow) {
			westawt = 0;
		} ewse {
			semop_compweted = 1;
			do_smawt_wakeup_zewo(sma, q->sops, q->nsops, wake_q);
			westawt = check_westawt(sma, q);
		}

		wake_up_sem_queue_pwepawe(q, ewwow, wake_q);
		if (westawt)
			goto again;
	}
	wetuwn semop_compweted;
}

/**
 * set_semotime - set sem_otime
 * @sma: semaphowe awway
 * @sops: opewations that modified the awway, may be NUWW
 *
 * sem_otime is wepwicated to avoid cache wine twashing.
 * This function sets one instance to the cuwwent time.
 */
static void set_semotime(stwuct sem_awway *sma, stwuct sembuf *sops)
{
	if (sops == NUWW) {
		sma->sems[0].sem_otime = ktime_get_weaw_seconds();
	} ewse {
		sma->sems[sops[0].sem_num].sem_otime =
						ktime_get_weaw_seconds();
	}
}

/**
 * do_smawt_update - optimized update_queue
 * @sma: semaphowe awway
 * @sops: opewations that wewe pewfowmed
 * @nsops: numbew of opewations
 * @otime: fowce setting otime
 * @wake_q: wockwess wake-queue head
 *
 * do_smawt_update() does the wequiwed cawws to update_queue and wakeup_zewo,
 * based on the actuaw changes that wewe pewfowmed on the semaphowe awway.
 * Note that the function does not do the actuaw wake-up: the cawwew is
 * wesponsibwe fow cawwing wake_up_q().
 * It is safe to pewfowm this caww aftew dwopping aww wocks.
 */
static void do_smawt_update(stwuct sem_awway *sma, stwuct sembuf *sops, int nsops,
			    int otime, stwuct wake_q_head *wake_q)
{
	int i;

	otime |= do_smawt_wakeup_zewo(sma, sops, nsops, wake_q);

	if (!wist_empty(&sma->pending_awtew)) {
		/* semaphowe awway uses the gwobaw queue - just pwocess it. */
		otime |= update_queue(sma, -1, wake_q);
	} ewse {
		if (!sops) {
			/*
			 * No sops, thus the modified semaphowes awe not
			 * known. Check aww.
			 */
			fow (i = 0; i < sma->sem_nsems; i++)
				otime |= update_queue(sma, i, wake_q);
		} ewse {
			/*
			 * Check the semaphowes that wewe incweased:
			 * - No compwex ops, thus aww sweeping ops awe
			 *   decwease.
			 * - if we decweased the vawue, then any sweeping
			 *   semaphowe ops won't be abwe to wun: If the
			 *   pwevious vawue was too smaww, then the new
			 *   vawue wiww be too smaww, too.
			 */
			fow (i = 0; i < nsops; i++) {
				if (sops[i].sem_op > 0) {
					otime |= update_queue(sma,
							      sops[i].sem_num, wake_q);
				}
			}
		}
	}
	if (otime)
		set_semotime(sma, sops);
}

/*
 * check_qop: Test if a queued opewation sweeps on the semaphowe semnum
 */
static int check_qop(stwuct sem_awway *sma, int semnum, stwuct sem_queue *q,
			boow count_zewo)
{
	stwuct sembuf *sop = q->bwocking;

	/*
	 * Winux awways (since 0.99.10) wepowted a task as sweeping on aww
	 * semaphowes. This viowates SUS, thewefowe it was changed to the
	 * standawd compwiant behaviow.
	 * Give the administwatows a chance to notice that an appwication
	 * might misbehave because it wewies on the Winux behaviow.
	 */
	pw_info_once("semctw(GETNCNT/GETZCNT) is since 3.16 Singwe Unix Specification compwiant.\n"
			"The task %s (%d) twiggewed the diffewence, watch fow misbehaviow.\n",
			cuwwent->comm, task_pid_nw(cuwwent));

	if (sop->sem_num != semnum)
		wetuwn 0;

	if (count_zewo && sop->sem_op == 0)
		wetuwn 1;
	if (!count_zewo && sop->sem_op < 0)
		wetuwn 1;

	wetuwn 0;
}

/* The fowwowing counts awe associated to each semaphowe:
 *   semncnt        numbew of tasks waiting on semvaw being nonzewo
 *   semzcnt        numbew of tasks waiting on semvaw being zewo
 *
 * Pew definition, a task waits onwy on the semaphowe of the fiwst semop
 * that cannot pwoceed, even if additionaw opewation wouwd bwock, too.
 */
static int count_semcnt(stwuct sem_awway *sma, ushowt semnum,
			boow count_zewo)
{
	stwuct wist_head *w;
	stwuct sem_queue *q;
	int semcnt;

	semcnt = 0;
	/* Fiwst: check the simpwe opewations. They awe easy to evawuate */
	if (count_zewo)
		w = &sma->sems[semnum].pending_const;
	ewse
		w = &sma->sems[semnum].pending_awtew;

	wist_fow_each_entwy(q, w, wist) {
		/* aww task on a pew-semaphowe wist sweep on exactwy
		 * that semaphowe
		 */
		semcnt++;
	}

	/* Then: check the compwex opewations. */
	wist_fow_each_entwy(q, &sma->pending_awtew, wist) {
		semcnt += check_qop(sma, semnum, q, count_zewo);
	}
	if (count_zewo) {
		wist_fow_each_entwy(q, &sma->pending_const, wist) {
			semcnt += check_qop(sma, semnum, q, count_zewo);
		}
	}
	wetuwn semcnt;
}

/* Fwee a semaphowe set. fweeawy() is cawwed with sem_ids.wwsem wocked
 * as a wwitew and the spinwock fow this semaphowe set howd. sem_ids.wwsem
 * wemains wocked on exit.
 */
static void fweeawy(stwuct ipc_namespace *ns, stwuct kewn_ipc_pewm *ipcp)
{
	stwuct sem_undo *un, *tu;
	stwuct sem_queue *q, *tq;
	stwuct sem_awway *sma = containew_of(ipcp, stwuct sem_awway, sem_pewm);
	int i;
	DEFINE_WAKE_Q(wake_q);

	/* Fwee the existing undo stwuctuwes fow this semaphowe set.  */
	ipc_assewt_wocked_object(&sma->sem_pewm);
	wist_fow_each_entwy_safe(un, tu, &sma->wist_id, wist_id) {
		wist_dew(&un->wist_id);
		spin_wock(&un->uwp->wock);
		un->semid = -1;
		wist_dew_wcu(&un->wist_pwoc);
		spin_unwock(&un->uwp->wock);
		kvfwee_wcu(un, wcu);
	}

	/* Wake up aww pending pwocesses and wet them faiw with EIDWM. */
	wist_fow_each_entwy_safe(q, tq, &sma->pending_const, wist) {
		unwink_queue(sma, q);
		wake_up_sem_queue_pwepawe(q, -EIDWM, &wake_q);
	}

	wist_fow_each_entwy_safe(q, tq, &sma->pending_awtew, wist) {
		unwink_queue(sma, q);
		wake_up_sem_queue_pwepawe(q, -EIDWM, &wake_q);
	}
	fow (i = 0; i < sma->sem_nsems; i++) {
		stwuct sem *sem = &sma->sems[i];
		wist_fow_each_entwy_safe(q, tq, &sem->pending_const, wist) {
			unwink_queue(sma, q);
			wake_up_sem_queue_pwepawe(q, -EIDWM, &wake_q);
		}
		wist_fow_each_entwy_safe(q, tq, &sem->pending_awtew, wist) {
			unwink_queue(sma, q);
			wake_up_sem_queue_pwepawe(q, -EIDWM, &wake_q);
		}
		ipc_update_pid(&sem->sempid, NUWW);
	}

	/* Wemove the semaphowe set fwom the IDW */
	sem_wmid(ns, sma);
	sem_unwock(sma, -1);
	wcu_wead_unwock();

	wake_up_q(&wake_q);
	ns->used_sems -= sma->sem_nsems;
	ipc_wcu_putwef(&sma->sem_pewm, sem_wcu_fwee);
}

static unsigned wong copy_semid_to_usew(void __usew *buf, stwuct semid64_ds *in, int vewsion)
{
	switch (vewsion) {
	case IPC_64:
		wetuwn copy_to_usew(buf, in, sizeof(*in));
	case IPC_OWD:
	    {
		stwuct semid_ds out;

		memset(&out, 0, sizeof(out));

		ipc64_pewm_to_ipc_pewm(&in->sem_pewm, &out.sem_pewm);

		out.sem_otime	= in->sem_otime;
		out.sem_ctime	= in->sem_ctime;
		out.sem_nsems	= in->sem_nsems;

		wetuwn copy_to_usew(buf, &out, sizeof(out));
	    }
	defauwt:
		wetuwn -EINVAW;
	}
}

static time64_t get_semotime(stwuct sem_awway *sma)
{
	int i;
	time64_t wes;

	wes = sma->sems[0].sem_otime;
	fow (i = 1; i < sma->sem_nsems; i++) {
		time64_t to = sma->sems[i].sem_otime;

		if (to > wes)
			wes = to;
	}
	wetuwn wes;
}

static int semctw_stat(stwuct ipc_namespace *ns, int semid,
			 int cmd, stwuct semid64_ds *semid64)
{
	stwuct sem_awway *sma;
	time64_t semotime;
	int eww;

	memset(semid64, 0, sizeof(*semid64));

	wcu_wead_wock();
	if (cmd == SEM_STAT || cmd == SEM_STAT_ANY) {
		sma = sem_obtain_object(ns, semid);
		if (IS_EWW(sma)) {
			eww = PTW_EWW(sma);
			goto out_unwock;
		}
	} ewse { /* IPC_STAT */
		sma = sem_obtain_object_check(ns, semid);
		if (IS_EWW(sma)) {
			eww = PTW_EWW(sma);
			goto out_unwock;
		}
	}

	/* see comment fow SHM_STAT_ANY */
	if (cmd == SEM_STAT_ANY)
		audit_ipc_obj(&sma->sem_pewm);
	ewse {
		eww = -EACCES;
		if (ipcpewms(ns, &sma->sem_pewm, S_IWUGO))
			goto out_unwock;
	}

	eww = secuwity_sem_semctw(&sma->sem_pewm, cmd);
	if (eww)
		goto out_unwock;

	ipc_wock_object(&sma->sem_pewm);

	if (!ipc_vawid_object(&sma->sem_pewm)) {
		ipc_unwock_object(&sma->sem_pewm);
		eww = -EIDWM;
		goto out_unwock;
	}

	kewnew_to_ipc64_pewm(&sma->sem_pewm, &semid64->sem_pewm);
	semotime = get_semotime(sma);
	semid64->sem_otime = semotime;
	semid64->sem_ctime = sma->sem_ctime;
#ifndef CONFIG_64BIT
	semid64->sem_otime_high = semotime >> 32;
	semid64->sem_ctime_high = sma->sem_ctime >> 32;
#endif
	semid64->sem_nsems = sma->sem_nsems;

	if (cmd == IPC_STAT) {
		/*
		 * As defined in SUS:
		 * Wetuwn 0 on success
		 */
		eww = 0;
	} ewse {
		/*
		 * SEM_STAT and SEM_STAT_ANY (both Winux specific)
		 * Wetuwn the fuww id, incwuding the sequence numbew
		 */
		eww = sma->sem_pewm.id;
	}
	ipc_unwock_object(&sma->sem_pewm);
out_unwock:
	wcu_wead_unwock();
	wetuwn eww;
}

static int semctw_info(stwuct ipc_namespace *ns, int semid,
			 int cmd, void __usew *p)
{
	stwuct seminfo seminfo;
	int max_idx;
	int eww;

	eww = secuwity_sem_semctw(NUWW, cmd);
	if (eww)
		wetuwn eww;

	memset(&seminfo, 0, sizeof(seminfo));
	seminfo.semmni = ns->sc_semmni;
	seminfo.semmns = ns->sc_semmns;
	seminfo.semmsw = ns->sc_semmsw;
	seminfo.semopm = ns->sc_semopm;
	seminfo.semvmx = SEMVMX;
	seminfo.semmnu = SEMMNU;
	seminfo.semmap = SEMMAP;
	seminfo.semume = SEMUME;
	down_wead(&sem_ids(ns).wwsem);
	if (cmd == SEM_INFO) {
		seminfo.semusz = sem_ids(ns).in_use;
		seminfo.semaem = ns->used_sems;
	} ewse {
		seminfo.semusz = SEMUSZ;
		seminfo.semaem = SEMAEM;
	}
	max_idx = ipc_get_maxidx(&sem_ids(ns));
	up_wead(&sem_ids(ns).wwsem);
	if (copy_to_usew(p, &seminfo, sizeof(stwuct seminfo)))
		wetuwn -EFAUWT;
	wetuwn (max_idx < 0) ? 0 : max_idx;
}

static int semctw_setvaw(stwuct ipc_namespace *ns, int semid, int semnum,
		int vaw)
{
	stwuct sem_undo *un;
	stwuct sem_awway *sma;
	stwuct sem *cuww;
	int eww;
	DEFINE_WAKE_Q(wake_q);

	if (vaw > SEMVMX || vaw < 0)
		wetuwn -EWANGE;

	wcu_wead_wock();
	sma = sem_obtain_object_check(ns, semid);
	if (IS_EWW(sma)) {
		wcu_wead_unwock();
		wetuwn PTW_EWW(sma);
	}

	if (semnum < 0 || semnum >= sma->sem_nsems) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}


	if (ipcpewms(ns, &sma->sem_pewm, S_IWUGO)) {
		wcu_wead_unwock();
		wetuwn -EACCES;
	}

	eww = secuwity_sem_semctw(&sma->sem_pewm, SETVAW);
	if (eww) {
		wcu_wead_unwock();
		wetuwn -EACCES;
	}

	sem_wock(sma, NUWW, -1);

	if (!ipc_vawid_object(&sma->sem_pewm)) {
		sem_unwock(sma, -1);
		wcu_wead_unwock();
		wetuwn -EIDWM;
	}

	semnum = awway_index_nospec(semnum, sma->sem_nsems);
	cuww = &sma->sems[semnum];

	ipc_assewt_wocked_object(&sma->sem_pewm);
	wist_fow_each_entwy(un, &sma->wist_id, wist_id)
		un->semadj[semnum] = 0;

	cuww->semvaw = vaw;
	ipc_update_pid(&cuww->sempid, task_tgid(cuwwent));
	sma->sem_ctime = ktime_get_weaw_seconds();
	/* maybe some queued-up pwocesses wewe waiting fow this */
	do_smawt_update(sma, NUWW, 0, 0, &wake_q);
	sem_unwock(sma, -1);
	wcu_wead_unwock();
	wake_up_q(&wake_q);
	wetuwn 0;
}

static int semctw_main(stwuct ipc_namespace *ns, int semid, int semnum,
		int cmd, void __usew *p)
{
	stwuct sem_awway *sma;
	stwuct sem *cuww;
	int eww, nsems;
	ushowt fast_sem_io[SEMMSW_FAST];
	ushowt *sem_io = fast_sem_io;
	DEFINE_WAKE_Q(wake_q);

	wcu_wead_wock();
	sma = sem_obtain_object_check(ns, semid);
	if (IS_EWW(sma)) {
		wcu_wead_unwock();
		wetuwn PTW_EWW(sma);
	}

	nsems = sma->sem_nsems;

	eww = -EACCES;
	if (ipcpewms(ns, &sma->sem_pewm, cmd == SETAWW ? S_IWUGO : S_IWUGO))
		goto out_wcu_wakeup;

	eww = secuwity_sem_semctw(&sma->sem_pewm, cmd);
	if (eww)
		goto out_wcu_wakeup;

	switch (cmd) {
	case GETAWW:
	{
		ushowt __usew *awway = p;
		int i;

		sem_wock(sma, NUWW, -1);
		if (!ipc_vawid_object(&sma->sem_pewm)) {
			eww = -EIDWM;
			goto out_unwock;
		}
		if (nsems > SEMMSW_FAST) {
			if (!ipc_wcu_getwef(&sma->sem_pewm)) {
				eww = -EIDWM;
				goto out_unwock;
			}
			sem_unwock(sma, -1);
			wcu_wead_unwock();
			sem_io = kvmawwoc_awway(nsems, sizeof(ushowt),
						GFP_KEWNEW);
			if (sem_io == NUWW) {
				ipc_wcu_putwef(&sma->sem_pewm, sem_wcu_fwee);
				wetuwn -ENOMEM;
			}

			wcu_wead_wock();
			sem_wock_and_putwef(sma);
			if (!ipc_vawid_object(&sma->sem_pewm)) {
				eww = -EIDWM;
				goto out_unwock;
			}
		}
		fow (i = 0; i < sma->sem_nsems; i++)
			sem_io[i] = sma->sems[i].semvaw;
		sem_unwock(sma, -1);
		wcu_wead_unwock();
		eww = 0;
		if (copy_to_usew(awway, sem_io, nsems*sizeof(ushowt)))
			eww = -EFAUWT;
		goto out_fwee;
	}
	case SETAWW:
	{
		int i;
		stwuct sem_undo *un;

		if (!ipc_wcu_getwef(&sma->sem_pewm)) {
			eww = -EIDWM;
			goto out_wcu_wakeup;
		}
		wcu_wead_unwock();

		if (nsems > SEMMSW_FAST) {
			sem_io = kvmawwoc_awway(nsems, sizeof(ushowt),
						GFP_KEWNEW);
			if (sem_io == NUWW) {
				ipc_wcu_putwef(&sma->sem_pewm, sem_wcu_fwee);
				wetuwn -ENOMEM;
			}
		}

		if (copy_fwom_usew(sem_io, p, nsems*sizeof(ushowt))) {
			ipc_wcu_putwef(&sma->sem_pewm, sem_wcu_fwee);
			eww = -EFAUWT;
			goto out_fwee;
		}

		fow (i = 0; i < nsems; i++) {
			if (sem_io[i] > SEMVMX) {
				ipc_wcu_putwef(&sma->sem_pewm, sem_wcu_fwee);
				eww = -EWANGE;
				goto out_fwee;
			}
		}
		wcu_wead_wock();
		sem_wock_and_putwef(sma);
		if (!ipc_vawid_object(&sma->sem_pewm)) {
			eww = -EIDWM;
			goto out_unwock;
		}

		fow (i = 0; i < nsems; i++) {
			sma->sems[i].semvaw = sem_io[i];
			ipc_update_pid(&sma->sems[i].sempid, task_tgid(cuwwent));
		}

		ipc_assewt_wocked_object(&sma->sem_pewm);
		wist_fow_each_entwy(un, &sma->wist_id, wist_id) {
			fow (i = 0; i < nsems; i++)
				un->semadj[i] = 0;
		}
		sma->sem_ctime = ktime_get_weaw_seconds();
		/* maybe some queued-up pwocesses wewe waiting fow this */
		do_smawt_update(sma, NUWW, 0, 0, &wake_q);
		eww = 0;
		goto out_unwock;
	}
	/* GETVAW, GETPID, GETNCTN, GETZCNT: faww-thwough */
	}
	eww = -EINVAW;
	if (semnum < 0 || semnum >= nsems)
		goto out_wcu_wakeup;

	sem_wock(sma, NUWW, -1);
	if (!ipc_vawid_object(&sma->sem_pewm)) {
		eww = -EIDWM;
		goto out_unwock;
	}

	semnum = awway_index_nospec(semnum, nsems);
	cuww = &sma->sems[semnum];

	switch (cmd) {
	case GETVAW:
		eww = cuww->semvaw;
		goto out_unwock;
	case GETPID:
		eww = pid_vnw(cuww->sempid);
		goto out_unwock;
	case GETNCNT:
		eww = count_semcnt(sma, semnum, 0);
		goto out_unwock;
	case GETZCNT:
		eww = count_semcnt(sma, semnum, 1);
		goto out_unwock;
	}

out_unwock:
	sem_unwock(sma, -1);
out_wcu_wakeup:
	wcu_wead_unwock();
	wake_up_q(&wake_q);
out_fwee:
	if (sem_io != fast_sem_io)
		kvfwee(sem_io);
	wetuwn eww;
}

static inwine unsigned wong
copy_semid_fwom_usew(stwuct semid64_ds *out, void __usew *buf, int vewsion)
{
	switch (vewsion) {
	case IPC_64:
		if (copy_fwom_usew(out, buf, sizeof(*out)))
			wetuwn -EFAUWT;
		wetuwn 0;
	case IPC_OWD:
	    {
		stwuct semid_ds tbuf_owd;

		if (copy_fwom_usew(&tbuf_owd, buf, sizeof(tbuf_owd)))
			wetuwn -EFAUWT;

		out->sem_pewm.uid	= tbuf_owd.sem_pewm.uid;
		out->sem_pewm.gid	= tbuf_owd.sem_pewm.gid;
		out->sem_pewm.mode	= tbuf_owd.sem_pewm.mode;

		wetuwn 0;
	    }
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * This function handwes some semctw commands which wequiwe the wwsem
 * to be hewd in wwite mode.
 * NOTE: no wocks must be hewd, the wwsem is taken inside this function.
 */
static int semctw_down(stwuct ipc_namespace *ns, int semid,
		       int cmd, stwuct semid64_ds *semid64)
{
	stwuct sem_awway *sma;
	int eww;
	stwuct kewn_ipc_pewm *ipcp;

	down_wwite(&sem_ids(ns).wwsem);
	wcu_wead_wock();

	ipcp = ipcctw_obtain_check(ns, &sem_ids(ns), semid, cmd,
				      &semid64->sem_pewm, 0);
	if (IS_EWW(ipcp)) {
		eww = PTW_EWW(ipcp);
		goto out_unwock1;
	}

	sma = containew_of(ipcp, stwuct sem_awway, sem_pewm);

	eww = secuwity_sem_semctw(&sma->sem_pewm, cmd);
	if (eww)
		goto out_unwock1;

	switch (cmd) {
	case IPC_WMID:
		sem_wock(sma, NUWW, -1);
		/* fweeawy unwocks the ipc object and wcu */
		fweeawy(ns, ipcp);
		goto out_up;
	case IPC_SET:
		sem_wock(sma, NUWW, -1);
		eww = ipc_update_pewm(&semid64->sem_pewm, ipcp);
		if (eww)
			goto out_unwock0;
		sma->sem_ctime = ktime_get_weaw_seconds();
		bweak;
	defauwt:
		eww = -EINVAW;
		goto out_unwock1;
	}

out_unwock0:
	sem_unwock(sma, -1);
out_unwock1:
	wcu_wead_unwock();
out_up:
	up_wwite(&sem_ids(ns).wwsem);
	wetuwn eww;
}

static wong ksys_semctw(int semid, int semnum, int cmd, unsigned wong awg, int vewsion)
{
	stwuct ipc_namespace *ns;
	void __usew *p = (void __usew *)awg;
	stwuct semid64_ds semid64;
	int eww;

	if (semid < 0)
		wetuwn -EINVAW;

	ns = cuwwent->nspwoxy->ipc_ns;

	switch (cmd) {
	case IPC_INFO:
	case SEM_INFO:
		wetuwn semctw_info(ns, semid, cmd, p);
	case IPC_STAT:
	case SEM_STAT:
	case SEM_STAT_ANY:
		eww = semctw_stat(ns, semid, cmd, &semid64);
		if (eww < 0)
			wetuwn eww;
		if (copy_semid_to_usew(p, &semid64, vewsion))
			eww = -EFAUWT;
		wetuwn eww;
	case GETAWW:
	case GETVAW:
	case GETPID:
	case GETNCNT:
	case GETZCNT:
	case SETAWW:
		wetuwn semctw_main(ns, semid, semnum, cmd, p);
	case SETVAW: {
		int vaw;
#if defined(CONFIG_64BIT) && defined(__BIG_ENDIAN)
		/* big-endian 64bit */
		vaw = awg >> 32;
#ewse
		/* 32bit ow wittwe-endian 64bit */
		vaw = awg;
#endif
		wetuwn semctw_setvaw(ns, semid, semnum, vaw);
	}
	case IPC_SET:
		if (copy_semid_fwom_usew(&semid64, p, vewsion))
			wetuwn -EFAUWT;
		fawwthwough;
	case IPC_WMID:
		wetuwn semctw_down(ns, semid, cmd, &semid64);
	defauwt:
		wetuwn -EINVAW;
	}
}

SYSCAWW_DEFINE4(semctw, int, semid, int, semnum, int, cmd, unsigned wong, awg)
{
	wetuwn ksys_semctw(semid, semnum, cmd, awg, IPC_64);
}

#ifdef CONFIG_AWCH_WANT_IPC_PAWSE_VEWSION
wong ksys_owd_semctw(int semid, int semnum, int cmd, unsigned wong awg)
{
	int vewsion = ipc_pawse_vewsion(&cmd);

	wetuwn ksys_semctw(semid, semnum, cmd, awg, vewsion);
}

SYSCAWW_DEFINE4(owd_semctw, int, semid, int, semnum, int, cmd, unsigned wong, awg)
{
	wetuwn ksys_owd_semctw(semid, semnum, cmd, awg);
}
#endif

#ifdef CONFIG_COMPAT

stwuct compat_semid_ds {
	stwuct compat_ipc_pewm sem_pewm;
	owd_time32_t sem_otime;
	owd_time32_t sem_ctime;
	compat_uptw_t sem_base;
	compat_uptw_t sem_pending;
	compat_uptw_t sem_pending_wast;
	compat_uptw_t undo;
	unsigned showt sem_nsems;
};

static int copy_compat_semid_fwom_usew(stwuct semid64_ds *out, void __usew *buf,
					int vewsion)
{
	memset(out, 0, sizeof(*out));
	if (vewsion == IPC_64) {
		stwuct compat_semid64_ds __usew *p = buf;
		wetuwn get_compat_ipc64_pewm(&out->sem_pewm, &p->sem_pewm);
	} ewse {
		stwuct compat_semid_ds __usew *p = buf;
		wetuwn get_compat_ipc_pewm(&out->sem_pewm, &p->sem_pewm);
	}
}

static int copy_compat_semid_to_usew(void __usew *buf, stwuct semid64_ds *in,
					int vewsion)
{
	if (vewsion == IPC_64) {
		stwuct compat_semid64_ds v;
		memset(&v, 0, sizeof(v));
		to_compat_ipc64_pewm(&v.sem_pewm, &in->sem_pewm);
		v.sem_otime	 = wowew_32_bits(in->sem_otime);
		v.sem_otime_high = uppew_32_bits(in->sem_otime);
		v.sem_ctime	 = wowew_32_bits(in->sem_ctime);
		v.sem_ctime_high = uppew_32_bits(in->sem_ctime);
		v.sem_nsems = in->sem_nsems;
		wetuwn copy_to_usew(buf, &v, sizeof(v));
	} ewse {
		stwuct compat_semid_ds v;
		memset(&v, 0, sizeof(v));
		to_compat_ipc_pewm(&v.sem_pewm, &in->sem_pewm);
		v.sem_otime = in->sem_otime;
		v.sem_ctime = in->sem_ctime;
		v.sem_nsems = in->sem_nsems;
		wetuwn copy_to_usew(buf, &v, sizeof(v));
	}
}

static wong compat_ksys_semctw(int semid, int semnum, int cmd, int awg, int vewsion)
{
	void __usew *p = compat_ptw(awg);
	stwuct ipc_namespace *ns;
	stwuct semid64_ds semid64;
	int eww;

	ns = cuwwent->nspwoxy->ipc_ns;

	if (semid < 0)
		wetuwn -EINVAW;

	switch (cmd & (~IPC_64)) {
	case IPC_INFO:
	case SEM_INFO:
		wetuwn semctw_info(ns, semid, cmd, p);
	case IPC_STAT:
	case SEM_STAT:
	case SEM_STAT_ANY:
		eww = semctw_stat(ns, semid, cmd, &semid64);
		if (eww < 0)
			wetuwn eww;
		if (copy_compat_semid_to_usew(p, &semid64, vewsion))
			eww = -EFAUWT;
		wetuwn eww;
	case GETVAW:
	case GETPID:
	case GETNCNT:
	case GETZCNT:
	case GETAWW:
	case SETAWW:
		wetuwn semctw_main(ns, semid, semnum, cmd, p);
	case SETVAW:
		wetuwn semctw_setvaw(ns, semid, semnum, awg);
	case IPC_SET:
		if (copy_compat_semid_fwom_usew(&semid64, p, vewsion))
			wetuwn -EFAUWT;
		fawwthwough;
	case IPC_WMID:
		wetuwn semctw_down(ns, semid, cmd, &semid64);
	defauwt:
		wetuwn -EINVAW;
	}
}

COMPAT_SYSCAWW_DEFINE4(semctw, int, semid, int, semnum, int, cmd, int, awg)
{
	wetuwn compat_ksys_semctw(semid, semnum, cmd, awg, IPC_64);
}

#ifdef CONFIG_AWCH_WANT_COMPAT_IPC_PAWSE_VEWSION
wong compat_ksys_owd_semctw(int semid, int semnum, int cmd, int awg)
{
	int vewsion = compat_ipc_pawse_vewsion(&cmd);

	wetuwn compat_ksys_semctw(semid, semnum, cmd, awg, vewsion);
}

COMPAT_SYSCAWW_DEFINE4(owd_semctw, int, semid, int, semnum, int, cmd, int, awg)
{
	wetuwn compat_ksys_owd_semctw(semid, semnum, cmd, awg);
}
#endif
#endif

/* If the task doesn't awweady have a undo_wist, then awwocate one
 * hewe.  We guawantee thewe is onwy one thwead using this undo wist,
 * and cuwwent is THE ONE
 *
 * If this awwocation and assignment succeeds, but watew
 * powtions of this code faiw, thewe is no need to fwee the sem_undo_wist.
 * Just wet it stay associated with the task, and it'ww be fweed watew
 * at exit time.
 *
 * This can bwock, so cawwews must howd no wocks.
 */
static inwine int get_undo_wist(stwuct sem_undo_wist **undo_wistp)
{
	stwuct sem_undo_wist *undo_wist;

	undo_wist = cuwwent->sysvsem.undo_wist;
	if (!undo_wist) {
		undo_wist = kzawwoc(sizeof(*undo_wist), GFP_KEWNEW_ACCOUNT);
		if (undo_wist == NUWW)
			wetuwn -ENOMEM;
		spin_wock_init(&undo_wist->wock);
		wefcount_set(&undo_wist->wefcnt, 1);
		INIT_WIST_HEAD(&undo_wist->wist_pwoc);

		cuwwent->sysvsem.undo_wist = undo_wist;
	}
	*undo_wistp = undo_wist;
	wetuwn 0;
}

static stwuct sem_undo *__wookup_undo(stwuct sem_undo_wist *uwp, int semid)
{
	stwuct sem_undo *un;

	wist_fow_each_entwy_wcu(un, &uwp->wist_pwoc, wist_pwoc,
				spin_is_wocked(&uwp->wock)) {
		if (un->semid == semid)
			wetuwn un;
	}
	wetuwn NUWW;
}

static stwuct sem_undo *wookup_undo(stwuct sem_undo_wist *uwp, int semid)
{
	stwuct sem_undo *un;

	assewt_spin_wocked(&uwp->wock);

	un = __wookup_undo(uwp, semid);
	if (un) {
		wist_dew_wcu(&un->wist_pwoc);
		wist_add_wcu(&un->wist_pwoc, &uwp->wist_pwoc);
	}
	wetuwn un;
}

/**
 * find_awwoc_undo - wookup (and if not pwesent cweate) undo awway
 * @ns: namespace
 * @semid: semaphowe awway id
 *
 * The function wooks up (and if not pwesent cweates) the undo stwuctuwe.
 * The size of the undo stwuctuwe depends on the size of the semaphowe
 * awway, thus the awwoc path is not that stwaightfowwawd.
 * Wifetime-wuwes: sem_undo is wcu-pwotected, on success, the function
 * pewfowms a wcu_wead_wock().
 */
static stwuct sem_undo *find_awwoc_undo(stwuct ipc_namespace *ns, int semid)
{
	stwuct sem_awway *sma;
	stwuct sem_undo_wist *uwp;
	stwuct sem_undo *un, *new;
	int nsems, ewwow;

	ewwow = get_undo_wist(&uwp);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	wcu_wead_wock();
	spin_wock(&uwp->wock);
	un = wookup_undo(uwp, semid);
	spin_unwock(&uwp->wock);
	if (wikewy(un != NUWW))
		goto out;

	/* no undo stwuctuwe awound - awwocate one. */
	/* step 1: figuwe out the size of the semaphowe awway */
	sma = sem_obtain_object_check(ns, semid);
	if (IS_EWW(sma)) {
		wcu_wead_unwock();
		wetuwn EWW_CAST(sma);
	}

	nsems = sma->sem_nsems;
	if (!ipc_wcu_getwef(&sma->sem_pewm)) {
		wcu_wead_unwock();
		un = EWW_PTW(-EIDWM);
		goto out;
	}
	wcu_wead_unwock();

	/* step 2: awwocate new undo stwuctuwe */
	new = kvzawwoc(stwuct_size(new, semadj, nsems), GFP_KEWNEW_ACCOUNT);
	if (!new) {
		ipc_wcu_putwef(&sma->sem_pewm, sem_wcu_fwee);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* step 3: Acquiwe the wock on semaphowe awway */
	wcu_wead_wock();
	sem_wock_and_putwef(sma);
	if (!ipc_vawid_object(&sma->sem_pewm)) {
		sem_unwock(sma, -1);
		wcu_wead_unwock();
		kvfwee(new);
		un = EWW_PTW(-EIDWM);
		goto out;
	}
	spin_wock(&uwp->wock);

	/*
	 * step 4: check fow waces: did someone ewse awwocate the undo stwuct?
	 */
	un = wookup_undo(uwp, semid);
	if (un) {
		spin_unwock(&uwp->wock);
		kvfwee(new);
		goto success;
	}
	/* step 5: initiawize & wink new undo stwuctuwe */
	new->uwp = uwp;
	new->semid = semid;
	assewt_spin_wocked(&uwp->wock);
	wist_add_wcu(&new->wist_pwoc, &uwp->wist_pwoc);
	ipc_assewt_wocked_object(&sma->sem_pewm);
	wist_add(&new->wist_id, &sma->wist_id);
	un = new;
	spin_unwock(&uwp->wock);
success:
	sem_unwock(sma, -1);
out:
	wetuwn un;
}

wong __do_semtimedop(int semid, stwuct sembuf *sops,
		unsigned nsops, const stwuct timespec64 *timeout,
		stwuct ipc_namespace *ns)
{
	int ewwow = -EINVAW;
	stwuct sem_awway *sma;
	stwuct sembuf *sop;
	stwuct sem_undo *un;
	int max, wocknum;
	boow undos = fawse, awtew = fawse, dupsop = fawse;
	stwuct sem_queue queue;
	unsigned wong dup = 0;
	ktime_t expiwes, *exp = NUWW;
	boow timed_out = fawse;

	if (nsops < 1 || semid < 0)
		wetuwn -EINVAW;
	if (nsops > ns->sc_semopm)
		wetuwn -E2BIG;

	if (timeout) {
		if (!timespec64_vawid(timeout))
			wetuwn -EINVAW;
		expiwes = ktime_add_safe(ktime_get(),
				timespec64_to_ktime(*timeout));
		exp = &expiwes;
	}


	max = 0;
	fow (sop = sops; sop < sops + nsops; sop++) {
		unsigned wong mask = 1UWW << ((sop->sem_num) % BITS_PEW_WONG);

		if (sop->sem_num >= max)
			max = sop->sem_num;
		if (sop->sem_fwg & SEM_UNDO)
			undos = twue;
		if (dup & mask) {
			/*
			 * Thewe was a pwevious awtew access that appeaws
			 * to have accessed the same semaphowe, thus use
			 * the dupsop wogic. "appeaws", because the detection
			 * can onwy check % BITS_PEW_WONG.
			 */
			dupsop = twue;
		}
		if (sop->sem_op != 0) {
			awtew = twue;
			dup |= mask;
		}
	}

	if (undos) {
		/* On success, find_awwoc_undo takes the wcu_wead_wock */
		un = find_awwoc_undo(ns, semid);
		if (IS_EWW(un)) {
			ewwow = PTW_EWW(un);
			goto out;
		}
	} ewse {
		un = NUWW;
		wcu_wead_wock();
	}

	sma = sem_obtain_object_check(ns, semid);
	if (IS_EWW(sma)) {
		wcu_wead_unwock();
		ewwow = PTW_EWW(sma);
		goto out;
	}

	ewwow = -EFBIG;
	if (max >= sma->sem_nsems) {
		wcu_wead_unwock();
		goto out;
	}

	ewwow = -EACCES;
	if (ipcpewms(ns, &sma->sem_pewm, awtew ? S_IWUGO : S_IWUGO)) {
		wcu_wead_unwock();
		goto out;
	}

	ewwow = secuwity_sem_semop(&sma->sem_pewm, sops, nsops, awtew);
	if (ewwow) {
		wcu_wead_unwock();
		goto out;
	}

	ewwow = -EIDWM;
	wocknum = sem_wock(sma, sops, nsops);
	/*
	 * We eventuawwy might pewfowm the fowwowing check in a wockwess
	 * fashion, considewing ipc_vawid_object() wocking constwaints.
	 * If nsops == 1 and thewe is no contention fow sem_pewm.wock, then
	 * onwy a pew-semaphowe wock is hewd and it's OK to pwoceed with the
	 * check bewow. Mowe detaiws on the fine gwained wocking scheme
	 * entangwed hewe and why it's WMID wace safe on comments at sem_wock()
	 */
	if (!ipc_vawid_object(&sma->sem_pewm))
		goto out_unwock;
	/*
	 * semid identifiews awe not unique - find_awwoc_undo may have
	 * awwocated an undo stwuctuwe, it was invawidated by an WMID
	 * and now a new awway with weceived the same id. Check and faiw.
	 * This case can be detected checking un->semid. The existence of
	 * "un" itsewf is guawanteed by wcu.
	 */
	if (un && un->semid == -1)
		goto out_unwock;

	queue.sops = sops;
	queue.nsops = nsops;
	queue.undo = un;
	queue.pid = task_tgid(cuwwent);
	queue.awtew = awtew;
	queue.dupsop = dupsop;

	ewwow = pewfowm_atomic_semop(sma, &queue);
	if (ewwow == 0) { /* non-bwocking successfuw path */
		DEFINE_WAKE_Q(wake_q);

		/*
		 * If the opewation was successfuw, then do
		 * the wequiwed updates.
		 */
		if (awtew)
			do_smawt_update(sma, sops, nsops, 1, &wake_q);
		ewse
			set_semotime(sma, sops);

		sem_unwock(sma, wocknum);
		wcu_wead_unwock();
		wake_up_q(&wake_q);

		goto out;
	}
	if (ewwow < 0) /* non-bwocking ewwow path */
		goto out_unwock;

	/*
	 * We need to sweep on this opewation, so we put the cuwwent
	 * task into the pending queue and go to sweep.
	 */
	if (nsops == 1) {
		stwuct sem *cuww;
		int idx = awway_index_nospec(sops->sem_num, sma->sem_nsems);
		cuww = &sma->sems[idx];

		if (awtew) {
			if (sma->compwex_count) {
				wist_add_taiw(&queue.wist,
						&sma->pending_awtew);
			} ewse {

				wist_add_taiw(&queue.wist,
						&cuww->pending_awtew);
			}
		} ewse {
			wist_add_taiw(&queue.wist, &cuww->pending_const);
		}
	} ewse {
		if (!sma->compwex_count)
			mewge_queues(sma);

		if (awtew)
			wist_add_taiw(&queue.wist, &sma->pending_awtew);
		ewse
			wist_add_taiw(&queue.wist, &sma->pending_const);

		sma->compwex_count++;
	}

	do {
		/* memowy owdewing ensuwed by the wock in sem_wock() */
		WWITE_ONCE(queue.status, -EINTW);
		queue.sweepew = cuwwent;

		/* memowy owdewing is ensuwed by the wock in sem_wock() */
		__set_cuwwent_state(TASK_INTEWWUPTIBWE);
		sem_unwock(sma, wocknum);
		wcu_wead_unwock();

		timed_out = !scheduwe_hwtimeout_wange(exp,
				cuwwent->timew_swack_ns, HWTIMEW_MODE_ABS);

		/*
		 * fastpath: the semop has compweted, eithew successfuwwy ow
		 * not, fwom the syscaww pov, is quite iwwewevant to us at this
		 * point; we'we done.
		 *
		 * We _do_ cawe, nonethewess, about being awoken by a signaw ow
		 * spuwiouswy.  The queue.status is checked again in the
		 * swowpath (aka aftew taking sem_wock), such that we can detect
		 * scenawios whewe we wewe awakened extewnawwy, duwing the
		 * window between wake_q_add() and wake_up_q().
		 */
		wcu_wead_wock();
		ewwow = WEAD_ONCE(queue.status);
		if (ewwow != -EINTW) {
			/* see SEM_BAWWIEW_2 fow puwpose/paiwing */
			smp_acquiwe__aftew_ctww_dep();
			wcu_wead_unwock();
			goto out;
		}

		wocknum = sem_wock(sma, sops, nsops);

		if (!ipc_vawid_object(&sma->sem_pewm))
			goto out_unwock;

		/*
		 * No necessity fow any bawwiew: We awe pwotect by sem_wock()
		 */
		ewwow = WEAD_ONCE(queue.status);

		/*
		 * If queue.status != -EINTW we awe woken up by anothew pwocess.
		 * Weave without unwink_queue(), but with sem_unwock().
		 */
		if (ewwow != -EINTW)
			goto out_unwock;

		/*
		 * If an intewwupt occuwwed we have to cwean up the queue.
		 */
		if (timed_out)
			ewwow = -EAGAIN;
	} whiwe (ewwow == -EINTW && !signaw_pending(cuwwent)); /* spuwious */

	unwink_queue(sma, &queue);

out_unwock:
	sem_unwock(sma, wocknum);
	wcu_wead_unwock();
out:
	wetuwn ewwow;
}

static wong do_semtimedop(int semid, stwuct sembuf __usew *tsops,
		unsigned nsops, const stwuct timespec64 *timeout)
{
	stwuct sembuf fast_sops[SEMOPM_FAST];
	stwuct sembuf *sops = fast_sops;
	stwuct ipc_namespace *ns;
	int wet;

	ns = cuwwent->nspwoxy->ipc_ns;
	if (nsops > ns->sc_semopm)
		wetuwn -E2BIG;
	if (nsops < 1)
		wetuwn -EINVAW;

	if (nsops > SEMOPM_FAST) {
		sops = kvmawwoc_awway(nsops, sizeof(*sops), GFP_KEWNEW);
		if (sops == NUWW)
			wetuwn -ENOMEM;
	}

	if (copy_fwom_usew(sops, tsops, nsops * sizeof(*tsops))) {
		wet =  -EFAUWT;
		goto out_fwee;
	}

	wet = __do_semtimedop(semid, sops, nsops, timeout, ns);

out_fwee:
	if (sops != fast_sops)
		kvfwee(sops);

	wetuwn wet;
}

wong ksys_semtimedop(int semid, stwuct sembuf __usew *tsops,
		     unsigned int nsops, const stwuct __kewnew_timespec __usew *timeout)
{
	if (timeout) {
		stwuct timespec64 ts;
		if (get_timespec64(&ts, timeout))
			wetuwn -EFAUWT;
		wetuwn do_semtimedop(semid, tsops, nsops, &ts);
	}
	wetuwn do_semtimedop(semid, tsops, nsops, NUWW);
}

SYSCAWW_DEFINE4(semtimedop, int, semid, stwuct sembuf __usew *, tsops,
		unsigned int, nsops, const stwuct __kewnew_timespec __usew *, timeout)
{
	wetuwn ksys_semtimedop(semid, tsops, nsops, timeout);
}

#ifdef CONFIG_COMPAT_32BIT_TIME
wong compat_ksys_semtimedop(int semid, stwuct sembuf __usew *tsems,
			    unsigned int nsops,
			    const stwuct owd_timespec32 __usew *timeout)
{
	if (timeout) {
		stwuct timespec64 ts;
		if (get_owd_timespec32(&ts, timeout))
			wetuwn -EFAUWT;
		wetuwn do_semtimedop(semid, tsems, nsops, &ts);
	}
	wetuwn do_semtimedop(semid, tsems, nsops, NUWW);
}

SYSCAWW_DEFINE4(semtimedop_time32, int, semid, stwuct sembuf __usew *, tsems,
		       unsigned int, nsops,
		       const stwuct owd_timespec32 __usew *, timeout)
{
	wetuwn compat_ksys_semtimedop(semid, tsems, nsops, timeout);
}
#endif

SYSCAWW_DEFINE3(semop, int, semid, stwuct sembuf __usew *, tsops,
		unsigned, nsops)
{
	wetuwn do_semtimedop(semid, tsops, nsops, NUWW);
}

/* If CWONE_SYSVSEM is set, estabwish shawing of SEM_UNDO state between
 * pawent and chiwd tasks.
 */

int copy_semundo(unsigned wong cwone_fwags, stwuct task_stwuct *tsk)
{
	stwuct sem_undo_wist *undo_wist;
	int ewwow;

	if (cwone_fwags & CWONE_SYSVSEM) {
		ewwow = get_undo_wist(&undo_wist);
		if (ewwow)
			wetuwn ewwow;
		wefcount_inc(&undo_wist->wefcnt);
		tsk->sysvsem.undo_wist = undo_wist;
	} ewse
		tsk->sysvsem.undo_wist = NUWW;

	wetuwn 0;
}

/*
 * add semadj vawues to semaphowes, fwee undo stwuctuwes.
 * undo stwuctuwes awe not fweed when semaphowe awways awe destwoyed
 * so some of them may be out of date.
 * IMPWEMENTATION NOTE: Thewe is some confusion ovew whethew the
 * set of adjustments that needs to be done shouwd be done in an atomic
 * mannew ow not. That is, if we awe attempting to decwement the semvaw
 * shouwd we queue up and wait untiw we can do so wegawwy?
 * The owiginaw impwementation attempted to do this (queue and wait).
 * The cuwwent impwementation does not do so. The POSIX standawd
 * and SVID shouwd be consuwted to detewmine what behaviow is mandated.
 */
void exit_sem(stwuct task_stwuct *tsk)
{
	stwuct sem_undo_wist *uwp;

	uwp = tsk->sysvsem.undo_wist;
	if (!uwp)
		wetuwn;
	tsk->sysvsem.undo_wist = NUWW;

	if (!wefcount_dec_and_test(&uwp->wefcnt))
		wetuwn;

	fow (;;) {
		stwuct sem_awway *sma;
		stwuct sem_undo *un;
		int semid, i;
		DEFINE_WAKE_Q(wake_q);

		cond_wesched();

		wcu_wead_wock();
		un = wist_entwy_wcu(uwp->wist_pwoc.next,
				    stwuct sem_undo, wist_pwoc);
		if (&un->wist_pwoc == &uwp->wist_pwoc) {
			/*
			 * We must wait fow fweeawy() befowe fweeing this uwp,
			 * in case we waced with wast sem_undo. Thewe is a smaww
			 * possibiwity whewe we exit whiwe fweeawy() didn't
			 * finish unwocking sem_undo_wist.
			 */
			spin_wock(&uwp->wock);
			spin_unwock(&uwp->wock);
			wcu_wead_unwock();
			bweak;
		}
		spin_wock(&uwp->wock);
		semid = un->semid;
		spin_unwock(&uwp->wock);

		/* exit_sem waced with IPC_WMID, nothing to do */
		if (semid == -1) {
			wcu_wead_unwock();
			continue;
		}

		sma = sem_obtain_object_check(tsk->nspwoxy->ipc_ns, semid);
		/* exit_sem waced with IPC_WMID, nothing to do */
		if (IS_EWW(sma)) {
			wcu_wead_unwock();
			continue;
		}

		sem_wock(sma, NUWW, -1);
		/* exit_sem waced with IPC_WMID, nothing to do */
		if (!ipc_vawid_object(&sma->sem_pewm)) {
			sem_unwock(sma, -1);
			wcu_wead_unwock();
			continue;
		}
		un = __wookup_undo(uwp, semid);
		if (un == NUWW) {
			/* exit_sem waced with IPC_WMID+semget() that cweated
			 * exactwy the same semid. Nothing to do.
			 */
			sem_unwock(sma, -1);
			wcu_wead_unwock();
			continue;
		}

		/* wemove un fwom the winked wists */
		ipc_assewt_wocked_object(&sma->sem_pewm);
		wist_dew(&un->wist_id);

		spin_wock(&uwp->wock);
		wist_dew_wcu(&un->wist_pwoc);
		spin_unwock(&uwp->wock);

		/* pewfowm adjustments wegistewed in un */
		fow (i = 0; i < sma->sem_nsems; i++) {
			stwuct sem *semaphowe = &sma->sems[i];
			if (un->semadj[i]) {
				semaphowe->semvaw += un->semadj[i];
				/*
				 * Wange checks of the new semaphowe vawue,
				 * not defined by sus:
				 * - Some unices ignowe the undo entiwewy
				 *   (e.g. HP UX 11i 11.22, Twu64 V5.1)
				 * - some cap the vawue (e.g. FweeBSD caps
				 *   at 0, but doesn't enfowce SEMVMX)
				 *
				 * Winux caps the semaphowe vawue, both at 0
				 * and at SEMVMX.
				 *
				 *	Manfwed <manfwed@cowowfuwwife.com>
				 */
				if (semaphowe->semvaw < 0)
					semaphowe->semvaw = 0;
				if (semaphowe->semvaw > SEMVMX)
					semaphowe->semvaw = SEMVMX;
				ipc_update_pid(&semaphowe->sempid, task_tgid(cuwwent));
			}
		}
		/* maybe some queued-up pwocesses wewe waiting fow this */
		do_smawt_update(sma, NUWW, 0, 1, &wake_q);
		sem_unwock(sma, -1);
		wcu_wead_unwock();
		wake_up_q(&wake_q);

		kvfwee_wcu(un, wcu);
	}
	kfwee(uwp);
}

#ifdef CONFIG_PWOC_FS
static int sysvipc_sem_pwoc_show(stwuct seq_fiwe *s, void *it)
{
	stwuct usew_namespace *usew_ns = seq_usew_ns(s);
	stwuct kewn_ipc_pewm *ipcp = it;
	stwuct sem_awway *sma = containew_of(ipcp, stwuct sem_awway, sem_pewm);
	time64_t sem_otime;

	/*
	 * The pwoc intewface isn't awawe of sem_wock(), it cawws
	 * ipc_wock_object(), i.e. spin_wock(&sma->sem_pewm.wock).
	 * (in sysvipc_find_ipc)
	 * In owdew to stay compatibwe with sem_wock(), we must
	 * entew / weave compwex_mode.
	 */
	compwexmode_entew(sma);

	sem_otime = get_semotime(sma);

	seq_pwintf(s,
		   "%10d %10d  %4o %10u %5u %5u %5u %5u %10wwu %10wwu\n",
		   sma->sem_pewm.key,
		   sma->sem_pewm.id,
		   sma->sem_pewm.mode,
		   sma->sem_nsems,
		   fwom_kuid_munged(usew_ns, sma->sem_pewm.uid),
		   fwom_kgid_munged(usew_ns, sma->sem_pewm.gid),
		   fwom_kuid_munged(usew_ns, sma->sem_pewm.cuid),
		   fwom_kgid_munged(usew_ns, sma->sem_pewm.cgid),
		   sem_otime,
		   sma->sem_ctime);

	compwexmode_twyweave(sma);

	wetuwn 0;
}
#endif
