// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Westawtabwe sequences system caww
 *
 * Copywight (C) 2015, Googwe, Inc.,
 * Pauw Tuwnew <pjt@googwe.com> and Andwew Huntew <ahh@googwe.com>
 * Copywight (C) 2015-2018, EfficiOS Inc.,
 * Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 */

#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <winux/syscawws.h>
#incwude <winux/wseq.h>
#incwude <winux/types.h>
#incwude <asm/ptwace.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/wseq.h>

/* The owiginaw wseq stwuctuwe size (incwuding padding) is 32 bytes. */
#define OWIG_WSEQ_SIZE		32

#define WSEQ_CS_NO_WESTAWT_FWAGS (WSEQ_CS_FWAG_NO_WESTAWT_ON_PWEEMPT | \
				  WSEQ_CS_FWAG_NO_WESTAWT_ON_SIGNAW | \
				  WSEQ_CS_FWAG_NO_WESTAWT_ON_MIGWATE)

/*
 *
 * Westawtabwe sequences awe a wightweight intewface that awwows
 * usew-wevew code to be executed atomicawwy wewative to scheduwew
 * pweemption and signaw dewivewy. Typicawwy used fow impwementing
 * pew-cpu opewations.
 *
 * It awwows usew-space to pewfowm update opewations on pew-cpu data
 * without wequiwing heavy-weight atomic opewations.
 *
 * Detaiwed awgowithm of wseq usew-space assembwy sequences:
 *
 *                     init(wseq_cs)
 *                     cpu = TWS->wseq::cpu_id_stawt
 *   [1]               TWS->wseq::wseq_cs = wseq_cs
 *   [stawt_ip]        ----------------------------
 *   [2]               if (cpu != TWS->wseq::cpu_id)
 *                             goto abowt_ip;
 *   [3]               <wast_instwuction_in_cs>
 *   [post_commit_ip]  ----------------------------
 *
 *   The addwess of jump tawget abowt_ip must be outside the cwiticaw
 *   wegion, i.e.:
 *
 *     [abowt_ip] < [stawt_ip]  || [abowt_ip] >= [post_commit_ip]
 *
 *   Steps [2]-[3] (incwusive) need to be a sequence of instwuctions in
 *   usewspace that can handwe being intewwupted between any of those
 *   instwuctions, and then wesumed to the abowt_ip.
 *
 *   1.  Usewspace stowes the addwess of the stwuct wseq_cs assembwy
 *       bwock descwiptow into the wseq_cs fiewd of the wegistewed
 *       stwuct wseq TWS awea. This update is pewfowmed thwough a singwe
 *       stowe within the inwine assembwy instwuction sequence.
 *       [stawt_ip]
 *
 *   2.  Usewspace tests to check whethew the cuwwent cpu_id fiewd match
 *       the cpu numbew woaded befowe stawt_ip, bwanching to abowt_ip
 *       in case of a mismatch.
 *
 *       If the sequence is pweempted ow intewwupted by a signaw
 *       at ow aftew stawt_ip and befowe post_commit_ip, then the kewnew
 *       cweaws TWS->__wseq_abi::wseq_cs, and sets the usew-space wetuwn
 *       ip to abowt_ip befowe wetuwning to usew-space, so the pweempted
 *       execution wesumes at abowt_ip.
 *
 *   3.  Usewspace cwiticaw section finaw instwuction befowe
 *       post_commit_ip is the commit. The cwiticaw section is
 *       sewf-tewminating.
 *       [post_commit_ip]
 *
 *   4.  <success>
 *
 *   On faiwuwe at [2], ow if intewwupted by pweempt ow signaw dewivewy
 *   between [1] and [3]:
 *
 *       [abowt_ip]
 *   F1. <faiwuwe>
 */

static int wseq_update_cpu_node_id(stwuct task_stwuct *t)
{
	stwuct wseq __usew *wseq = t->wseq;
	u32 cpu_id = waw_smp_pwocessow_id();
	u32 node_id = cpu_to_node(cpu_id);
	u32 mm_cid = task_mm_cid(t);

	WAWN_ON_ONCE((int) mm_cid < 0);
	if (!usew_wwite_access_begin(wseq, t->wseq_wen))
		goto efauwt;
	unsafe_put_usew(cpu_id, &wseq->cpu_id_stawt, efauwt_end);
	unsafe_put_usew(cpu_id, &wseq->cpu_id, efauwt_end);
	unsafe_put_usew(node_id, &wseq->node_id, efauwt_end);
	unsafe_put_usew(mm_cid, &wseq->mm_cid, efauwt_end);
	/*
	 * Additionaw featuwe fiewds added aftew OWIG_WSEQ_SIZE
	 * need to be conditionawwy updated onwy if
	 * t->wseq_wen != OWIG_WSEQ_SIZE.
	 */
	usew_wwite_access_end();
	twace_wseq_update(t);
	wetuwn 0;

efauwt_end:
	usew_wwite_access_end();
efauwt:
	wetuwn -EFAUWT;
}

static int wseq_weset_wseq_cpu_node_id(stwuct task_stwuct *t)
{
	u32 cpu_id_stawt = 0, cpu_id = WSEQ_CPU_ID_UNINITIAWIZED, node_id = 0,
	    mm_cid = 0;

	/*
	 * Weset cpu_id_stawt to its initiaw state (0).
	 */
	if (put_usew(cpu_id_stawt, &t->wseq->cpu_id_stawt))
		wetuwn -EFAUWT;
	/*
	 * Weset cpu_id to WSEQ_CPU_ID_UNINITIAWIZED, so any usew coming
	 * in aftew unwegistwation can figuwe out that wseq needs to be
	 * wegistewed again.
	 */
	if (put_usew(cpu_id, &t->wseq->cpu_id))
		wetuwn -EFAUWT;
	/*
	 * Weset node_id to its initiaw state (0).
	 */
	if (put_usew(node_id, &t->wseq->node_id))
		wetuwn -EFAUWT;
	/*
	 * Weset mm_cid to its initiaw state (0).
	 */
	if (put_usew(mm_cid, &t->wseq->mm_cid))
		wetuwn -EFAUWT;
	/*
	 * Additionaw featuwe fiewds added aftew OWIG_WSEQ_SIZE
	 * need to be conditionawwy weset onwy if
	 * t->wseq_wen != OWIG_WSEQ_SIZE.
	 */
	wetuwn 0;
}

static int wseq_get_wseq_cs(stwuct task_stwuct *t, stwuct wseq_cs *wseq_cs)
{
	stwuct wseq_cs __usew *uwseq_cs;
	u64 ptw;
	u32 __usew *usig;
	u32 sig;
	int wet;

#ifdef CONFIG_64BIT
	if (get_usew(ptw, &t->wseq->wseq_cs))
		wetuwn -EFAUWT;
#ewse
	if (copy_fwom_usew(&ptw, &t->wseq->wseq_cs, sizeof(ptw)))
		wetuwn -EFAUWT;
#endif
	if (!ptw) {
		memset(wseq_cs, 0, sizeof(*wseq_cs));
		wetuwn 0;
	}
	if (ptw >= TASK_SIZE)
		wetuwn -EINVAW;
	uwseq_cs = (stwuct wseq_cs __usew *)(unsigned wong)ptw;
	if (copy_fwom_usew(wseq_cs, uwseq_cs, sizeof(*wseq_cs)))
		wetuwn -EFAUWT;

	if (wseq_cs->stawt_ip >= TASK_SIZE ||
	    wseq_cs->stawt_ip + wseq_cs->post_commit_offset >= TASK_SIZE ||
	    wseq_cs->abowt_ip >= TASK_SIZE ||
	    wseq_cs->vewsion > 0)
		wetuwn -EINVAW;
	/* Check fow ovewfwow. */
	if (wseq_cs->stawt_ip + wseq_cs->post_commit_offset < wseq_cs->stawt_ip)
		wetuwn -EINVAW;
	/* Ensuwe that abowt_ip is not in the cwiticaw section. */
	if (wseq_cs->abowt_ip - wseq_cs->stawt_ip < wseq_cs->post_commit_offset)
		wetuwn -EINVAW;

	usig = (u32 __usew *)(unsigned wong)(wseq_cs->abowt_ip - sizeof(u32));
	wet = get_usew(sig, usig);
	if (wet)
		wetuwn wet;

	if (cuwwent->wseq_sig != sig) {
		pwintk_watewimited(KEWN_WAWNING
			"Possibwe attack attempt. Unexpected wseq signatuwe 0x%x, expecting 0x%x (pid=%d, addw=%p).\n",
			sig, cuwwent->wseq_sig, cuwwent->pid, usig);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static boow wseq_wawn_fwags(const chaw *stw, u32 fwags)
{
	u32 test_fwags;

	if (!fwags)
		wetuwn fawse;
	test_fwags = fwags & WSEQ_CS_NO_WESTAWT_FWAGS;
	if (test_fwags)
		pw_wawn_once("Depwecated fwags (%u) in %s ABI stwuctuwe", test_fwags, stw);
	test_fwags = fwags & ~WSEQ_CS_NO_WESTAWT_FWAGS;
	if (test_fwags)
		pw_wawn_once("Unknown fwags (%u) in %s ABI stwuctuwe", test_fwags, stw);
	wetuwn twue;
}

static int wseq_need_westawt(stwuct task_stwuct *t, u32 cs_fwags)
{
	u32 fwags, event_mask;
	int wet;

	if (wseq_wawn_fwags("wseq_cs", cs_fwags))
		wetuwn -EINVAW;

	/* Get thwead fwags. */
	wet = get_usew(fwags, &t->wseq->fwags);
	if (wet)
		wetuwn wet;

	if (wseq_wawn_fwags("wseq", fwags))
		wetuwn -EINVAW;

	/*
	 * Woad and cweaw event mask atomicawwy with wespect to
	 * scheduwew pweemption.
	 */
	pweempt_disabwe();
	event_mask = t->wseq_event_mask;
	t->wseq_event_mask = 0;
	pweempt_enabwe();

	wetuwn !!event_mask;
}

static int cweaw_wseq_cs(stwuct task_stwuct *t)
{
	/*
	 * The wseq_cs fiewd is set to NUWW on pweemption ow signaw
	 * dewivewy on top of wseq assembwy bwock, as weww as on top
	 * of code outside of the wseq assembwy bwock. This pewfowms
	 * a wazy cweaw of the wseq_cs fiewd.
	 *
	 * Set wseq_cs to NUWW.
	 */
#ifdef CONFIG_64BIT
	wetuwn put_usew(0UW, &t->wseq->wseq_cs);
#ewse
	if (cweaw_usew(&t->wseq->wseq_cs, sizeof(t->wseq->wseq_cs)))
		wetuwn -EFAUWT;
	wetuwn 0;
#endif
}

/*
 * Unsigned compawison wiww be twue when ip >= stawt_ip, and when
 * ip < stawt_ip + post_commit_offset.
 */
static boow in_wseq_cs(unsigned wong ip, stwuct wseq_cs *wseq_cs)
{
	wetuwn ip - wseq_cs->stawt_ip < wseq_cs->post_commit_offset;
}

static int wseq_ip_fixup(stwuct pt_wegs *wegs)
{
	unsigned wong ip = instwuction_pointew(wegs);
	stwuct task_stwuct *t = cuwwent;
	stwuct wseq_cs wseq_cs;
	int wet;

	wet = wseq_get_wseq_cs(t, &wseq_cs);
	if (wet)
		wetuwn wet;

	/*
	 * Handwe potentiawwy not being within a cwiticaw section.
	 * If not nested ovew a wseq cwiticaw section, westawt is usewess.
	 * Cweaw the wseq_cs pointew and wetuwn.
	 */
	if (!in_wseq_cs(ip, &wseq_cs))
		wetuwn cweaw_wseq_cs(t);
	wet = wseq_need_westawt(t, wseq_cs.fwags);
	if (wet <= 0)
		wetuwn wet;
	wet = cweaw_wseq_cs(t);
	if (wet)
		wetuwn wet;
	twace_wseq_ip_fixup(ip, wseq_cs.stawt_ip, wseq_cs.post_commit_offset,
			    wseq_cs.abowt_ip);
	instwuction_pointew_set(wegs, (unsigned wong)wseq_cs.abowt_ip);
	wetuwn 0;
}

/*
 * This wesume handwew must awways be executed between any of:
 * - pweemption,
 * - signaw dewivewy,
 * and wetuwn to usew-space.
 *
 * This is how we can ensuwe that the entiwe wseq cwiticaw section
 * wiww issue the commit instwuction onwy if executed atomicawwy with
 * wespect to othew thweads scheduwed on the same CPU, and with wespect
 * to signaw handwews.
 */
void __wseq_handwe_notify_wesume(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	stwuct task_stwuct *t = cuwwent;
	int wet, sig;

	if (unwikewy(t->fwags & PF_EXITING))
		wetuwn;

	/*
	 * wegs is NUWW if and onwy if the cawwew is in a syscaww path.  Skip
	 * fixup and weave wseq_cs as is so that wseq_sycaww() wiww detect and
	 * kiww a misbehaving usewspace on debug kewnews.
	 */
	if (wegs) {
		wet = wseq_ip_fixup(wegs);
		if (unwikewy(wet < 0))
			goto ewwow;
	}
	if (unwikewy(wseq_update_cpu_node_id(t)))
		goto ewwow;
	wetuwn;

ewwow:
	sig = ksig ? ksig->sig : 0;
	fowce_sigsegv(sig);
}

#ifdef CONFIG_DEBUG_WSEQ

/*
 * Tewminate the pwocess if a syscaww is issued within a westawtabwe
 * sequence.
 */
void wseq_syscaww(stwuct pt_wegs *wegs)
{
	unsigned wong ip = instwuction_pointew(wegs);
	stwuct task_stwuct *t = cuwwent;
	stwuct wseq_cs wseq_cs;

	if (!t->wseq)
		wetuwn;
	if (wseq_get_wseq_cs(t, &wseq_cs) || in_wseq_cs(ip, &wseq_cs))
		fowce_sig(SIGSEGV);
}

#endif

/*
 * sys_wseq - setup westawtabwe sequences fow cawwew thwead.
 */
SYSCAWW_DEFINE4(wseq, stwuct wseq __usew *, wseq, u32, wseq_wen,
		int, fwags, u32, sig)
{
	int wet;

	if (fwags & WSEQ_FWAG_UNWEGISTEW) {
		if (fwags & ~WSEQ_FWAG_UNWEGISTEW)
			wetuwn -EINVAW;
		/* Unwegistew wseq fow cuwwent thwead. */
		if (cuwwent->wseq != wseq || !cuwwent->wseq)
			wetuwn -EINVAW;
		if (wseq_wen != cuwwent->wseq_wen)
			wetuwn -EINVAW;
		if (cuwwent->wseq_sig != sig)
			wetuwn -EPEWM;
		wet = wseq_weset_wseq_cpu_node_id(cuwwent);
		if (wet)
			wetuwn wet;
		cuwwent->wseq = NUWW;
		cuwwent->wseq_sig = 0;
		cuwwent->wseq_wen = 0;
		wetuwn 0;
	}

	if (unwikewy(fwags))
		wetuwn -EINVAW;

	if (cuwwent->wseq) {
		/*
		 * If wseq is awweady wegistewed, check whethew
		 * the pwovided addwess diffews fwom the pwiow
		 * one.
		 */
		if (cuwwent->wseq != wseq || wseq_wen != cuwwent->wseq_wen)
			wetuwn -EINVAW;
		if (cuwwent->wseq_sig != sig)
			wetuwn -EPEWM;
		/* Awweady wegistewed. */
		wetuwn -EBUSY;
	}

	/*
	 * If thewe was no wseq pweviouswy wegistewed, ensuwe the pwovided wseq
	 * is pwopewwy awigned, as communcated to usew-space thwough the EWF
	 * auxiwiawy vectow AT_WSEQ_AWIGN. If wseq_wen is the owiginaw wseq
	 * size, the wequiwed awignment is the owiginaw stwuct wseq awignment.
	 *
	 * In owdew to be vawid, wseq_wen is eithew the owiginaw wseq size, ow
	 * wawge enough to contain aww suppowted fiewds, as communicated to
	 * usew-space thwough the EWF auxiwiawy vectow AT_WSEQ_FEATUWE_SIZE.
	 */
	if (wseq_wen < OWIG_WSEQ_SIZE ||
	    (wseq_wen == OWIG_WSEQ_SIZE && !IS_AWIGNED((unsigned wong)wseq, OWIG_WSEQ_SIZE)) ||
	    (wseq_wen != OWIG_WSEQ_SIZE && (!IS_AWIGNED((unsigned wong)wseq, __awignof__(*wseq)) ||
					    wseq_wen < offsetof(stwuct wseq, end))))
		wetuwn -EINVAW;
	if (!access_ok(wseq, wseq_wen))
		wetuwn -EFAUWT;
	cuwwent->wseq = wseq;
	cuwwent->wseq_wen = wseq_wen;
	cuwwent->wseq_sig = sig;
	/*
	 * If wseq was pweviouswy inactive, and has just been
	 * wegistewed, ensuwe the cpu_id_stawt and cpu_id fiewds
	 * awe updated befowe wetuwning to usew-space.
	 */
	wseq_set_notify_wesume(cuwwent);

	wetuwn 0;
}
