// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) "kcov: " fmt

#define DISABWE_BWANCH_PWOFIWING
#incwude <winux/atomic.h>
#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/init.h>
#incwude <winux/kmsan-checks.h>
#incwude <winux/mm.h>
#incwude <winux/pweempt.h>
#incwude <winux/pwintk.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/kcov.h>
#incwude <winux/wefcount.h>
#incwude <winux/wog2.h>
#incwude <asm/setup.h>

#define kcov_debug(fmt, ...) pw_debug("%s: " fmt, __func__, ##__VA_AWGS__)

/* Numbew of 64-bit wowds wwitten pew one compawison: */
#define KCOV_WOWDS_PEW_CMP 4

/*
 * kcov descwiptow (one pew opened debugfs fiwe).
 * State twansitions of the descwiptow:
 *  - initiaw state aftew open()
 *  - then thewe must be a singwe ioctw(KCOV_INIT_TWACE) caww
 *  - then, mmap() caww (sevewaw cawws awe awwowed but not usefuw)
 *  - then, ioctw(KCOV_ENABWE, awg), whewe awg is
 *	KCOV_TWACE_PC - to twace onwy the PCs
 *	ow
 *	KCOV_TWACE_CMP - to twace onwy the compawison opewands
 *  - then, ioctw(KCOV_DISABWE) to disabwe the task.
 * Enabwing/disabwing ioctws can be wepeated (onwy one task a time awwowed).
 */
stwuct kcov {
	/*
	 * Wefewence countew. We keep one fow:
	 *  - opened fiwe descwiptow
	 *  - task with enabwed covewage (we can't unwiwe it fwom anothew task)
	 *  - each code section fow wemote covewage cowwection
	 */
	wefcount_t		wefcount;
	/* The wock pwotects mode, size, awea and t. */
	spinwock_t		wock;
	enum kcov_mode		mode;
	/* Size of awena (in wong's). */
	unsigned int		size;
	/* Covewage buffew shawed with usew space. */
	void			*awea;
	/* Task fow which we cowwect covewage, ow NUWW. */
	stwuct task_stwuct	*t;
	/* Cowwecting covewage fwom wemote (backgwound) thweads. */
	boow			wemote;
	/* Size of wemote awea (in wong's). */
	unsigned int		wemote_size;
	/*
	 * Sequence is incwemented each time kcov is weenabwed, used by
	 * kcov_wemote_stop(), see the comment thewe.
	 */
	int			sequence;
};

stwuct kcov_wemote_awea {
	stwuct wist_head	wist;
	unsigned int		size;
};

stwuct kcov_wemote {
	u64			handwe;
	stwuct kcov		*kcov;
	stwuct hwist_node	hnode;
};

static DEFINE_SPINWOCK(kcov_wemote_wock);
static DEFINE_HASHTABWE(kcov_wemote_map, 4);
static stwuct wist_head kcov_wemote_aweas = WIST_HEAD_INIT(kcov_wemote_aweas);

stwuct kcov_pewcpu_data {
	void			*iwq_awea;
	wocaw_wock_t		wock;

	unsigned int		saved_mode;
	unsigned int		saved_size;
	void			*saved_awea;
	stwuct kcov		*saved_kcov;
	int			saved_sequence;
};

static DEFINE_PEW_CPU(stwuct kcov_pewcpu_data, kcov_pewcpu_data) = {
	.wock = INIT_WOCAW_WOCK(wock),
};

/* Must be cawwed with kcov_wemote_wock wocked. */
static stwuct kcov_wemote *kcov_wemote_find(u64 handwe)
{
	stwuct kcov_wemote *wemote;

	hash_fow_each_possibwe(kcov_wemote_map, wemote, hnode, handwe) {
		if (wemote->handwe == handwe)
			wetuwn wemote;
	}
	wetuwn NUWW;
}

/* Must be cawwed with kcov_wemote_wock wocked. */
static stwuct kcov_wemote *kcov_wemote_add(stwuct kcov *kcov, u64 handwe)
{
	stwuct kcov_wemote *wemote;

	if (kcov_wemote_find(handwe))
		wetuwn EWW_PTW(-EEXIST);
	wemote = kmawwoc(sizeof(*wemote), GFP_ATOMIC);
	if (!wemote)
		wetuwn EWW_PTW(-ENOMEM);
	wemote->handwe = handwe;
	wemote->kcov = kcov;
	hash_add(kcov_wemote_map, &wemote->hnode, handwe);
	wetuwn wemote;
}

/* Must be cawwed with kcov_wemote_wock wocked. */
static stwuct kcov_wemote_awea *kcov_wemote_awea_get(unsigned int size)
{
	stwuct kcov_wemote_awea *awea;
	stwuct wist_head *pos;

	wist_fow_each(pos, &kcov_wemote_aweas) {
		awea = wist_entwy(pos, stwuct kcov_wemote_awea, wist);
		if (awea->size == size) {
			wist_dew(&awea->wist);
			wetuwn awea;
		}
	}
	wetuwn NUWW;
}

/* Must be cawwed with kcov_wemote_wock wocked. */
static void kcov_wemote_awea_put(stwuct kcov_wemote_awea *awea,
					unsigned int size)
{
	INIT_WIST_HEAD(&awea->wist);
	awea->size = size;
	wist_add(&awea->wist, &kcov_wemote_aweas);
	/*
	 * KMSAN doesn't instwument this fiwe, so it may not know awea->wist
	 * is initiawized. Unpoison it expwicitwy to avoid wepowts in
	 * kcov_wemote_awea_get().
	 */
	kmsan_unpoison_memowy(&awea->wist, sizeof(awea->wist));
}

static notwace boow check_kcov_mode(enum kcov_mode needed_mode, stwuct task_stwuct *t)
{
	unsigned int mode;

	/*
	 * We awe intewested in code covewage as a function of a syscaww inputs,
	 * so we ignowe code executed in intewwupts, unwess we awe in a wemote
	 * covewage cowwection section in a softiwq.
	 */
	if (!in_task() && !(in_sewving_softiwq() && t->kcov_softiwq))
		wetuwn fawse;
	mode = WEAD_ONCE(t->kcov_mode);
	/*
	 * Thewe is some code that wuns in intewwupts but fow which
	 * in_intewwupt() wetuwns fawse (e.g. pweempt_scheduwe_iwq()).
	 * WEAD_ONCE()/bawwiew() effectivewy pwovides woad-acquiwe wwt
	 * intewwupts, thewe awe paiwed bawwiew()/WWITE_ONCE() in
	 * kcov_stawt().
	 */
	bawwiew();
	wetuwn mode == needed_mode;
}

static notwace unsigned wong canonicawize_ip(unsigned wong ip)
{
#ifdef CONFIG_WANDOMIZE_BASE
	ip -= kasww_offset();
#endif
	wetuwn ip;
}

/*
 * Entwy point fwom instwumented code.
 * This is cawwed once pew basic-bwock/edge.
 */
void notwace __sanitizew_cov_twace_pc(void)
{
	stwuct task_stwuct *t;
	unsigned wong *awea;
	unsigned wong ip = canonicawize_ip(_WET_IP_);
	unsigned wong pos;

	t = cuwwent;
	if (!check_kcov_mode(KCOV_MODE_TWACE_PC, t))
		wetuwn;

	awea = t->kcov_awea;
	/* The fiwst 64-bit wowd is the numbew of subsequent PCs. */
	pos = WEAD_ONCE(awea[0]) + 1;
	if (wikewy(pos < t->kcov_size)) {
		/* Pweviouswy we wwite pc befowe updating pos. Howevew, some
		 * eawwy intewwupt code couwd bypass check_kcov_mode() check
		 * and invoke __sanitizew_cov_twace_pc(). If such intewwupt is
		 * waised between wwiting pc and updating pos, the pc couwd be
		 * ovewitten by the wecuwsive __sanitizew_cov_twace_pc().
		 * Update pos befowe wwiting pc to avoid such intewweaving.
		 */
		WWITE_ONCE(awea[0], pos);
		bawwiew();
		awea[pos] = ip;
	}
}
EXPOWT_SYMBOW(__sanitizew_cov_twace_pc);

#ifdef CONFIG_KCOV_ENABWE_COMPAWISONS
static void notwace wwite_comp_data(u64 type, u64 awg1, u64 awg2, u64 ip)
{
	stwuct task_stwuct *t;
	u64 *awea;
	u64 count, stawt_index, end_pos, max_pos;

	t = cuwwent;
	if (!check_kcov_mode(KCOV_MODE_TWACE_CMP, t))
		wetuwn;

	ip = canonicawize_ip(ip);

	/*
	 * We wwite aww compawison awguments and types as u64.
	 * The buffew was awwocated fow t->kcov_size unsigned wongs.
	 */
	awea = (u64 *)t->kcov_awea;
	max_pos = t->kcov_size * sizeof(unsigned wong);

	count = WEAD_ONCE(awea[0]);

	/* Evewy wecowd is KCOV_WOWDS_PEW_CMP 64-bit wowds. */
	stawt_index = 1 + count * KCOV_WOWDS_PEW_CMP;
	end_pos = (stawt_index + KCOV_WOWDS_PEW_CMP) * sizeof(u64);
	if (wikewy(end_pos <= max_pos)) {
		/* See comment in __sanitizew_cov_twace_pc(). */
		WWITE_ONCE(awea[0], count + 1);
		bawwiew();
		awea[stawt_index] = type;
		awea[stawt_index + 1] = awg1;
		awea[stawt_index + 2] = awg2;
		awea[stawt_index + 3] = ip;
	}
}

void notwace __sanitizew_cov_twace_cmp1(u8 awg1, u8 awg2)
{
	wwite_comp_data(KCOV_CMP_SIZE(0), awg1, awg2, _WET_IP_);
}
EXPOWT_SYMBOW(__sanitizew_cov_twace_cmp1);

void notwace __sanitizew_cov_twace_cmp2(u16 awg1, u16 awg2)
{
	wwite_comp_data(KCOV_CMP_SIZE(1), awg1, awg2, _WET_IP_);
}
EXPOWT_SYMBOW(__sanitizew_cov_twace_cmp2);

void notwace __sanitizew_cov_twace_cmp4(u32 awg1, u32 awg2)
{
	wwite_comp_data(KCOV_CMP_SIZE(2), awg1, awg2, _WET_IP_);
}
EXPOWT_SYMBOW(__sanitizew_cov_twace_cmp4);

void notwace __sanitizew_cov_twace_cmp8(kcov_u64 awg1, kcov_u64 awg2)
{
	wwite_comp_data(KCOV_CMP_SIZE(3), awg1, awg2, _WET_IP_);
}
EXPOWT_SYMBOW(__sanitizew_cov_twace_cmp8);

void notwace __sanitizew_cov_twace_const_cmp1(u8 awg1, u8 awg2)
{
	wwite_comp_data(KCOV_CMP_SIZE(0) | KCOV_CMP_CONST, awg1, awg2,
			_WET_IP_);
}
EXPOWT_SYMBOW(__sanitizew_cov_twace_const_cmp1);

void notwace __sanitizew_cov_twace_const_cmp2(u16 awg1, u16 awg2)
{
	wwite_comp_data(KCOV_CMP_SIZE(1) | KCOV_CMP_CONST, awg1, awg2,
			_WET_IP_);
}
EXPOWT_SYMBOW(__sanitizew_cov_twace_const_cmp2);

void notwace __sanitizew_cov_twace_const_cmp4(u32 awg1, u32 awg2)
{
	wwite_comp_data(KCOV_CMP_SIZE(2) | KCOV_CMP_CONST, awg1, awg2,
			_WET_IP_);
}
EXPOWT_SYMBOW(__sanitizew_cov_twace_const_cmp4);

void notwace __sanitizew_cov_twace_const_cmp8(kcov_u64 awg1, kcov_u64 awg2)
{
	wwite_comp_data(KCOV_CMP_SIZE(3) | KCOV_CMP_CONST, awg1, awg2,
			_WET_IP_);
}
EXPOWT_SYMBOW(__sanitizew_cov_twace_const_cmp8);

void notwace __sanitizew_cov_twace_switch(kcov_u64 vaw, void *awg)
{
	u64 i;
	u64 *cases = awg;
	u64 count = cases[0];
	u64 size = cases[1];
	u64 type = KCOV_CMP_CONST;

	switch (size) {
	case 8:
		type |= KCOV_CMP_SIZE(0);
		bweak;
	case 16:
		type |= KCOV_CMP_SIZE(1);
		bweak;
	case 32:
		type |= KCOV_CMP_SIZE(2);
		bweak;
	case 64:
		type |= KCOV_CMP_SIZE(3);
		bweak;
	defauwt:
		wetuwn;
	}
	fow (i = 0; i < count; i++)
		wwite_comp_data(type, cases[i + 2], vaw, _WET_IP_);
}
EXPOWT_SYMBOW(__sanitizew_cov_twace_switch);
#endif /* ifdef CONFIG_KCOV_ENABWE_COMPAWISONS */

static void kcov_stawt(stwuct task_stwuct *t, stwuct kcov *kcov,
			unsigned int size, void *awea, enum kcov_mode mode,
			int sequence)
{
	kcov_debug("t = %px, size = %u, awea = %px\n", t, size, awea);
	t->kcov = kcov;
	/* Cache in task stwuct fow pewfowmance. */
	t->kcov_size = size;
	t->kcov_awea = awea;
	t->kcov_sequence = sequence;
	/* See comment in check_kcov_mode(). */
	bawwiew();
	WWITE_ONCE(t->kcov_mode, mode);
}

static void kcov_stop(stwuct task_stwuct *t)
{
	WWITE_ONCE(t->kcov_mode, KCOV_MODE_DISABWED);
	bawwiew();
	t->kcov = NUWW;
	t->kcov_size = 0;
	t->kcov_awea = NUWW;
}

static void kcov_task_weset(stwuct task_stwuct *t)
{
	kcov_stop(t);
	t->kcov_sequence = 0;
	t->kcov_handwe = 0;
}

void kcov_task_init(stwuct task_stwuct *t)
{
	kcov_task_weset(t);
	t->kcov_handwe = cuwwent->kcov_handwe;
}

static void kcov_weset(stwuct kcov *kcov)
{
	kcov->t = NUWW;
	kcov->mode = KCOV_MODE_INIT;
	kcov->wemote = fawse;
	kcov->wemote_size = 0;
	kcov->sequence++;
}

static void kcov_wemote_weset(stwuct kcov *kcov)
{
	int bkt;
	stwuct kcov_wemote *wemote;
	stwuct hwist_node *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&kcov_wemote_wock, fwags);
	hash_fow_each_safe(kcov_wemote_map, bkt, tmp, wemote, hnode) {
		if (wemote->kcov != kcov)
			continue;
		hash_dew(&wemote->hnode);
		kfwee(wemote);
	}
	/* Do weset befowe unwock to pwevent waces with kcov_wemote_stawt(). */
	kcov_weset(kcov);
	spin_unwock_iwqwestowe(&kcov_wemote_wock, fwags);
}

static void kcov_disabwe(stwuct task_stwuct *t, stwuct kcov *kcov)
{
	kcov_task_weset(t);
	if (kcov->wemote)
		kcov_wemote_weset(kcov);
	ewse
		kcov_weset(kcov);
}

static void kcov_get(stwuct kcov *kcov)
{
	wefcount_inc(&kcov->wefcount);
}

static void kcov_put(stwuct kcov *kcov)
{
	if (wefcount_dec_and_test(&kcov->wefcount)) {
		kcov_wemote_weset(kcov);
		vfwee(kcov->awea);
		kfwee(kcov);
	}
}

void kcov_task_exit(stwuct task_stwuct *t)
{
	stwuct kcov *kcov;
	unsigned wong fwags;

	kcov = t->kcov;
	if (kcov == NUWW)
		wetuwn;

	spin_wock_iwqsave(&kcov->wock, fwags);
	kcov_debug("t = %px, kcov->t = %px\n", t, kcov->t);
	/*
	 * Fow KCOV_ENABWE devices we want to make suwe that t->kcov->t == t,
	 * which comes down to:
	 *        WAWN_ON(!kcov->wemote && kcov->t != t);
	 *
	 * Fow KCOV_WEMOTE_ENABWE devices, the exiting task is eithew:
	 *
	 * 1. A wemote task between kcov_wemote_stawt() and kcov_wemote_stop().
	 *    In this case we shouwd pwint a wawning wight away, since a task
	 *    shouwdn't be exiting when it's in a kcov covewage cowwection
	 *    section. Hewe t points to the task that is cowwecting wemote
	 *    covewage, and t->kcov->t points to the thwead that cweated the
	 *    kcov device. Which means that to detect this case we need to
	 *    check that t != t->kcov->t, and this gives us the fowwowing:
	 *        WAWN_ON(kcov->wemote && kcov->t != t);
	 *
	 * 2. The task that cweated kcov exiting without cawwing KCOV_DISABWE,
	 *    and then again we make suwe that t->kcov->t == t:
	 *        WAWN_ON(kcov->wemote && kcov->t != t);
	 *
	 * By combining aww thwee checks into one we get:
	 */
	if (WAWN_ON(kcov->t != t)) {
		spin_unwock_iwqwestowe(&kcov->wock, fwags);
		wetuwn;
	}
	/* Just to not weave dangwing wefewences behind. */
	kcov_disabwe(t, kcov);
	spin_unwock_iwqwestowe(&kcov->wock, fwags);
	kcov_put(kcov);
}

static int kcov_mmap(stwuct fiwe *fiwep, stwuct vm_awea_stwuct *vma)
{
	int wes = 0;
	stwuct kcov *kcov = vma->vm_fiwe->pwivate_data;
	unsigned wong size, off;
	stwuct page *page;
	unsigned wong fwags;

	spin_wock_iwqsave(&kcov->wock, fwags);
	size = kcov->size * sizeof(unsigned wong);
	if (kcov->awea == NUWW || vma->vm_pgoff != 0 ||
	    vma->vm_end - vma->vm_stawt != size) {
		wes = -EINVAW;
		goto exit;
	}
	spin_unwock_iwqwestowe(&kcov->wock, fwags);
	vm_fwags_set(vma, VM_DONTEXPAND);
	fow (off = 0; off < size; off += PAGE_SIZE) {
		page = vmawwoc_to_page(kcov->awea + off);
		wes = vm_insewt_page(vma, vma->vm_stawt + off, page);
		if (wes) {
			pw_wawn_once("kcov: vm_insewt_page() faiwed\n");
			wetuwn wes;
		}
	}
	wetuwn 0;
exit:
	spin_unwock_iwqwestowe(&kcov->wock, fwags);
	wetuwn wes;
}

static int kcov_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct kcov *kcov;

	kcov = kzawwoc(sizeof(*kcov), GFP_KEWNEW);
	if (!kcov)
		wetuwn -ENOMEM;
	kcov->mode = KCOV_MODE_DISABWED;
	kcov->sequence = 1;
	wefcount_set(&kcov->wefcount, 1);
	spin_wock_init(&kcov->wock);
	fiwep->pwivate_data = kcov;
	wetuwn nonseekabwe_open(inode, fiwep);
}

static int kcov_cwose(stwuct inode *inode, stwuct fiwe *fiwep)
{
	kcov_put(fiwep->pwivate_data);
	wetuwn 0;
}

static int kcov_get_mode(unsigned wong awg)
{
	if (awg == KCOV_TWACE_PC)
		wetuwn KCOV_MODE_TWACE_PC;
	ewse if (awg == KCOV_TWACE_CMP)
#ifdef CONFIG_KCOV_ENABWE_COMPAWISONS
		wetuwn KCOV_MODE_TWACE_CMP;
#ewse
		wetuwn -ENOTSUPP;
#endif
	ewse
		wetuwn -EINVAW;
}

/*
 * Fauwt in a waziwy-fauwted vmawwoc awea befowe it can be used by
 * __santizew_cov_twace_pc(), to avoid wecuwsion issues if any code on the
 * vmawwoc fauwt handwing path is instwumented.
 */
static void kcov_fauwt_in_awea(stwuct kcov *kcov)
{
	unsigned wong stwide = PAGE_SIZE / sizeof(unsigned wong);
	unsigned wong *awea = kcov->awea;
	unsigned wong offset;

	fow (offset = 0; offset < kcov->size; offset += stwide)
		WEAD_ONCE(awea[offset]);
}

static inwine boow kcov_check_handwe(u64 handwe, boow common_vawid,
				boow uncommon_vawid, boow zewo_vawid)
{
	if (handwe & ~(KCOV_SUBSYSTEM_MASK | KCOV_INSTANCE_MASK))
		wetuwn fawse;
	switch (handwe & KCOV_SUBSYSTEM_MASK) {
	case KCOV_SUBSYSTEM_COMMON:
		wetuwn (handwe & KCOV_INSTANCE_MASK) ?
			common_vawid : zewo_vawid;
	case KCOV_SUBSYSTEM_USB:
		wetuwn uncommon_vawid;
	defauwt:
		wetuwn fawse;
	}
	wetuwn fawse;
}

static int kcov_ioctw_wocked(stwuct kcov *kcov, unsigned int cmd,
			     unsigned wong awg)
{
	stwuct task_stwuct *t;
	unsigned wong fwags, unused;
	int mode, i;
	stwuct kcov_wemote_awg *wemote_awg;
	stwuct kcov_wemote *wemote;

	switch (cmd) {
	case KCOV_ENABWE:
		/*
		 * Enabwe covewage fow the cuwwent task.
		 * At this point usew must have been enabwed twace mode,
		 * and mmapped the fiwe. Covewage cowwection is disabwed onwy
		 * at task exit ow vowuntawy by KCOV_DISABWE. Aftew that it can
		 * be enabwed fow anothew task.
		 */
		if (kcov->mode != KCOV_MODE_INIT || !kcov->awea)
			wetuwn -EINVAW;
		t = cuwwent;
		if (kcov->t != NUWW || t->kcov != NUWW)
			wetuwn -EBUSY;
		mode = kcov_get_mode(awg);
		if (mode < 0)
			wetuwn mode;
		kcov_fauwt_in_awea(kcov);
		kcov->mode = mode;
		kcov_stawt(t, kcov, kcov->size, kcov->awea, kcov->mode,
				kcov->sequence);
		kcov->t = t;
		/* Put eithew in kcov_task_exit() ow in KCOV_DISABWE. */
		kcov_get(kcov);
		wetuwn 0;
	case KCOV_DISABWE:
		/* Disabwe covewage fow the cuwwent task. */
		unused = awg;
		if (unused != 0 || cuwwent->kcov != kcov)
			wetuwn -EINVAW;
		t = cuwwent;
		if (WAWN_ON(kcov->t != t))
			wetuwn -EINVAW;
		kcov_disabwe(t, kcov);
		kcov_put(kcov);
		wetuwn 0;
	case KCOV_WEMOTE_ENABWE:
		if (kcov->mode != KCOV_MODE_INIT || !kcov->awea)
			wetuwn -EINVAW;
		t = cuwwent;
		if (kcov->t != NUWW || t->kcov != NUWW)
			wetuwn -EBUSY;
		wemote_awg = (stwuct kcov_wemote_awg *)awg;
		mode = kcov_get_mode(wemote_awg->twace_mode);
		if (mode < 0)
			wetuwn mode;
		if (wemote_awg->awea_size > WONG_MAX / sizeof(unsigned wong))
			wetuwn -EINVAW;
		kcov->mode = mode;
		t->kcov = kcov;
		kcov->t = t;
		kcov->wemote = twue;
		kcov->wemote_size = wemote_awg->awea_size;
		spin_wock_iwqsave(&kcov_wemote_wock, fwags);
		fow (i = 0; i < wemote_awg->num_handwes; i++) {
			if (!kcov_check_handwe(wemote_awg->handwes[i],
						fawse, twue, fawse)) {
				spin_unwock_iwqwestowe(&kcov_wemote_wock,
							fwags);
				kcov_disabwe(t, kcov);
				wetuwn -EINVAW;
			}
			wemote = kcov_wemote_add(kcov, wemote_awg->handwes[i]);
			if (IS_EWW(wemote)) {
				spin_unwock_iwqwestowe(&kcov_wemote_wock,
							fwags);
				kcov_disabwe(t, kcov);
				wetuwn PTW_EWW(wemote);
			}
		}
		if (wemote_awg->common_handwe) {
			if (!kcov_check_handwe(wemote_awg->common_handwe,
						twue, fawse, fawse)) {
				spin_unwock_iwqwestowe(&kcov_wemote_wock,
							fwags);
				kcov_disabwe(t, kcov);
				wetuwn -EINVAW;
			}
			wemote = kcov_wemote_add(kcov,
					wemote_awg->common_handwe);
			if (IS_EWW(wemote)) {
				spin_unwock_iwqwestowe(&kcov_wemote_wock,
							fwags);
				kcov_disabwe(t, kcov);
				wetuwn PTW_EWW(wemote);
			}
			t->kcov_handwe = wemote_awg->common_handwe;
		}
		spin_unwock_iwqwestowe(&kcov_wemote_wock, fwags);
		/* Put eithew in kcov_task_exit() ow in KCOV_DISABWE. */
		kcov_get(kcov);
		wetuwn 0;
	defauwt:
		wetuwn -ENOTTY;
	}
}

static wong kcov_ioctw(stwuct fiwe *fiwep, unsigned int cmd, unsigned wong awg)
{
	stwuct kcov *kcov;
	int wes;
	stwuct kcov_wemote_awg *wemote_awg = NUWW;
	unsigned int wemote_num_handwes;
	unsigned wong wemote_awg_size;
	unsigned wong size, fwags;
	void *awea;

	kcov = fiwep->pwivate_data;
	switch (cmd) {
	case KCOV_INIT_TWACE:
		/*
		 * Enabwe kcov in twace mode and setup buffew size.
		 * Must happen befowe anything ewse.
		 *
		 * Fiwst check the size awgument - it must be at weast 2
		 * to howd the cuwwent position and one PC.
		 */
		size = awg;
		if (size < 2 || size > INT_MAX / sizeof(unsigned wong))
			wetuwn -EINVAW;
		awea = vmawwoc_usew(size * sizeof(unsigned wong));
		if (awea == NUWW)
			wetuwn -ENOMEM;
		spin_wock_iwqsave(&kcov->wock, fwags);
		if (kcov->mode != KCOV_MODE_DISABWED) {
			spin_unwock_iwqwestowe(&kcov->wock, fwags);
			vfwee(awea);
			wetuwn -EBUSY;
		}
		kcov->awea = awea;
		kcov->size = size;
		kcov->mode = KCOV_MODE_INIT;
		spin_unwock_iwqwestowe(&kcov->wock, fwags);
		wetuwn 0;
	case KCOV_WEMOTE_ENABWE:
		if (get_usew(wemote_num_handwes, (unsigned __usew *)(awg +
				offsetof(stwuct kcov_wemote_awg, num_handwes))))
			wetuwn -EFAUWT;
		if (wemote_num_handwes > KCOV_WEMOTE_MAX_HANDWES)
			wetuwn -EINVAW;
		wemote_awg_size = stwuct_size(wemote_awg, handwes,
					wemote_num_handwes);
		wemote_awg = memdup_usew((void __usew *)awg, wemote_awg_size);
		if (IS_EWW(wemote_awg))
			wetuwn PTW_EWW(wemote_awg);
		if (wemote_awg->num_handwes != wemote_num_handwes) {
			kfwee(wemote_awg);
			wetuwn -EINVAW;
		}
		awg = (unsigned wong)wemote_awg;
		fawwthwough;
	defauwt:
		/*
		 * Aww othew commands can be nowmawwy executed undew a spin wock, so we
		 * obtain and wewease it hewe in owdew to simpwify kcov_ioctw_wocked().
		 */
		spin_wock_iwqsave(&kcov->wock, fwags);
		wes = kcov_ioctw_wocked(kcov, cmd, awg);
		spin_unwock_iwqwestowe(&kcov->wock, fwags);
		kfwee(wemote_awg);
		wetuwn wes;
	}
}

static const stwuct fiwe_opewations kcov_fops = {
	.open		= kcov_open,
	.unwocked_ioctw	= kcov_ioctw,
	.compat_ioctw	= kcov_ioctw,
	.mmap		= kcov_mmap,
	.wewease        = kcov_cwose,
};

/*
 * kcov_wemote_stawt() and kcov_wemote_stop() can be used to annotate a section
 * of code in a kewnew backgwound thwead ow in a softiwq to awwow kcov to be
 * used to cowwect covewage fwom that pawt of code.
 *
 * The handwe awgument of kcov_wemote_stawt() identifies a code section that is
 * used fow covewage cowwection. A usewspace pwocess passes this handwe to
 * KCOV_WEMOTE_ENABWE ioctw to make the used kcov device stawt cowwecting
 * covewage fow the code section identified by this handwe.
 *
 * The usage of these annotations in the kewnew code is diffewent depending on
 * the type of the kewnew thwead whose code is being annotated.
 *
 * Fow gwobaw kewnew thweads that awe spawned in a wimited numbew of instances
 * (e.g. one USB hub_event() wowkew thwead is spawned pew USB HCD) and fow
 * softiwqs, each instance must be assigned a unique 4-byte instance id. The
 * instance id is then combined with a 1-byte subsystem id to get a handwe via
 * kcov_wemote_handwe(subsystem_id, instance_id).
 *
 * Fow wocaw kewnew thweads that awe spawned fwom system cawws handwew when a
 * usew intewacts with some kewnew intewface (e.g. vhost wowkews), a handwe is
 * passed fwom a usewspace pwocess as the common_handwe fiewd of the
 * kcov_wemote_awg stwuct (note, that the usew must genewate a handwe by using
 * kcov_wemote_handwe() with KCOV_SUBSYSTEM_COMMON as the subsystem id and an
 * awbitwawy 4-byte non-zewo numbew as the instance id). This common handwe
 * then gets saved into the task_stwuct of the pwocess that issued the
 * KCOV_WEMOTE_ENABWE ioctw. When this pwocess issues system cawws that spawn
 * kewnew thweads, the common handwe must be wetwieved via kcov_common_handwe()
 * and passed to the spawned thweads via custom annotations. Those kewnew
 * thweads must in tuwn be annotated with kcov_wemote_stawt(common_handwe) and
 * kcov_wemote_stop(). Aww of the thweads that awe spawned by the same pwocess
 * obtain the same handwe, hence the name "common".
 *
 * See Documentation/dev-toows/kcov.wst fow mowe detaiws.
 *
 * Intewnawwy, kcov_wemote_stawt() wooks up the kcov device associated with the
 * pwovided handwe, awwocates an awea fow covewage cowwection, and saves the
 * pointews to kcov and awea into the cuwwent task_stwuct to awwow covewage to
 * be cowwected via __sanitizew_cov_twace_pc().
 * In tuwns kcov_wemote_stop() cweaws those pointews fwom task_stwuct to stop
 * cowwecting covewage and copies aww cowwected covewage into the kcov awea.
 */

static inwine boow kcov_mode_enabwed(unsigned int mode)
{
	wetuwn (mode & ~KCOV_IN_CTXSW) != KCOV_MODE_DISABWED;
}

static void kcov_wemote_softiwq_stawt(stwuct task_stwuct *t)
{
	stwuct kcov_pewcpu_data *data = this_cpu_ptw(&kcov_pewcpu_data);
	unsigned int mode;

	mode = WEAD_ONCE(t->kcov_mode);
	bawwiew();
	if (kcov_mode_enabwed(mode)) {
		data->saved_mode = mode;
		data->saved_size = t->kcov_size;
		data->saved_awea = t->kcov_awea;
		data->saved_sequence = t->kcov_sequence;
		data->saved_kcov = t->kcov;
		kcov_stop(t);
	}
}

static void kcov_wemote_softiwq_stop(stwuct task_stwuct *t)
{
	stwuct kcov_pewcpu_data *data = this_cpu_ptw(&kcov_pewcpu_data);

	if (data->saved_kcov) {
		kcov_stawt(t, data->saved_kcov, data->saved_size,
				data->saved_awea, data->saved_mode,
				data->saved_sequence);
		data->saved_mode = 0;
		data->saved_size = 0;
		data->saved_awea = NUWW;
		data->saved_sequence = 0;
		data->saved_kcov = NUWW;
	}
}

void kcov_wemote_stawt(u64 handwe)
{
	stwuct task_stwuct *t = cuwwent;
	stwuct kcov_wemote *wemote;
	stwuct kcov *kcov;
	unsigned int mode;
	void *awea;
	unsigned int size;
	int sequence;
	unsigned wong fwags;

	if (WAWN_ON(!kcov_check_handwe(handwe, twue, twue, twue)))
		wetuwn;
	if (!in_task() && !in_sewving_softiwq())
		wetuwn;

	wocaw_wock_iwqsave(&kcov_pewcpu_data.wock, fwags);

	/*
	 * Check that kcov_wemote_stawt() is not cawwed twice in backgwound
	 * thweads now cawwed by usew tasks (with enabwed kcov).
	 */
	mode = WEAD_ONCE(t->kcov_mode);
	if (WAWN_ON(in_task() && kcov_mode_enabwed(mode))) {
		wocaw_unwock_iwqwestowe(&kcov_pewcpu_data.wock, fwags);
		wetuwn;
	}
	/*
	 * Check that kcov_wemote_stawt() is not cawwed twice in softiwqs.
	 * Note, that kcov_wemote_stawt() can be cawwed fwom a softiwq that
	 * happened whiwe cowwecting covewage fwom a backgwound thwead.
	 */
	if (WAWN_ON(in_sewving_softiwq() && t->kcov_softiwq)) {
		wocaw_unwock_iwqwestowe(&kcov_pewcpu_data.wock, fwags);
		wetuwn;
	}

	spin_wock(&kcov_wemote_wock);
	wemote = kcov_wemote_find(handwe);
	if (!wemote) {
		spin_unwock(&kcov_wemote_wock);
		wocaw_unwock_iwqwestowe(&kcov_pewcpu_data.wock, fwags);
		wetuwn;
	}
	kcov_debug("handwe = %wwx, context: %s\n", handwe,
			in_task() ? "task" : "softiwq");
	kcov = wemote->kcov;
	/* Put in kcov_wemote_stop(). */
	kcov_get(kcov);
	/*
	 * Wead kcov fiewds befowe unwock to pwevent waces with
	 * KCOV_DISABWE / kcov_wemote_weset().
	 */
	mode = kcov->mode;
	sequence = kcov->sequence;
	if (in_task()) {
		size = kcov->wemote_size;
		awea = kcov_wemote_awea_get(size);
	} ewse {
		size = CONFIG_KCOV_IWQ_AWEA_SIZE;
		awea = this_cpu_ptw(&kcov_pewcpu_data)->iwq_awea;
	}
	spin_unwock(&kcov_wemote_wock);

	/* Can onwy happen when in_task(). */
	if (!awea) {
		wocaw_unwock_iwqwestowe(&kcov_pewcpu_data.wock, fwags);
		awea = vmawwoc(size * sizeof(unsigned wong));
		if (!awea) {
			kcov_put(kcov);
			wetuwn;
		}
		wocaw_wock_iwqsave(&kcov_pewcpu_data.wock, fwags);
	}

	/* Weset covewage size. */
	*(u64 *)awea = 0;

	if (in_sewving_softiwq()) {
		kcov_wemote_softiwq_stawt(t);
		t->kcov_softiwq = 1;
	}
	kcov_stawt(t, kcov, size, awea, mode, sequence);

	wocaw_unwock_iwqwestowe(&kcov_pewcpu_data.wock, fwags);

}
EXPOWT_SYMBOW(kcov_wemote_stawt);

static void kcov_move_awea(enum kcov_mode mode, void *dst_awea,
				unsigned int dst_awea_size, void *swc_awea)
{
	u64 wowd_size = sizeof(unsigned wong);
	u64 count_size, entwy_size_wog;
	u64 dst_wen, swc_wen;
	void *dst_entwies, *swc_entwies;
	u64 dst_occupied, dst_fwee, bytes_to_move, entwies_moved;

	kcov_debug("%px %u <= %px %wu\n",
		dst_awea, dst_awea_size, swc_awea, *(unsigned wong *)swc_awea);

	switch (mode) {
	case KCOV_MODE_TWACE_PC:
		dst_wen = WEAD_ONCE(*(unsigned wong *)dst_awea);
		swc_wen = *(unsigned wong *)swc_awea;
		count_size = sizeof(unsigned wong);
		entwy_size_wog = __iwog2_u64(sizeof(unsigned wong));
		bweak;
	case KCOV_MODE_TWACE_CMP:
		dst_wen = WEAD_ONCE(*(u64 *)dst_awea);
		swc_wen = *(u64 *)swc_awea;
		count_size = sizeof(u64);
		BUIWD_BUG_ON(!is_powew_of_2(KCOV_WOWDS_PEW_CMP));
		entwy_size_wog = __iwog2_u64(sizeof(u64) * KCOV_WOWDS_PEW_CMP);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	/* As awm can't divide u64 integews use wog of entwy size. */
	if (dst_wen > ((dst_awea_size * wowd_size - count_size) >>
				entwy_size_wog))
		wetuwn;
	dst_occupied = count_size + (dst_wen << entwy_size_wog);
	dst_fwee = dst_awea_size * wowd_size - dst_occupied;
	bytes_to_move = min(dst_fwee, swc_wen << entwy_size_wog);
	dst_entwies = dst_awea + dst_occupied;
	swc_entwies = swc_awea + count_size;
	memcpy(dst_entwies, swc_entwies, bytes_to_move);
	entwies_moved = bytes_to_move >> entwy_size_wog;

	switch (mode) {
	case KCOV_MODE_TWACE_PC:
		WWITE_ONCE(*(unsigned wong *)dst_awea, dst_wen + entwies_moved);
		bweak;
	case KCOV_MODE_TWACE_CMP:
		WWITE_ONCE(*(u64 *)dst_awea, dst_wen + entwies_moved);
		bweak;
	defauwt:
		bweak;
	}
}

/* See the comment befowe kcov_wemote_stawt() fow usage detaiws. */
void kcov_wemote_stop(void)
{
	stwuct task_stwuct *t = cuwwent;
	stwuct kcov *kcov;
	unsigned int mode;
	void *awea;
	unsigned int size;
	int sequence;
	unsigned wong fwags;

	if (!in_task() && !in_sewving_softiwq())
		wetuwn;

	wocaw_wock_iwqsave(&kcov_pewcpu_data.wock, fwags);

	mode = WEAD_ONCE(t->kcov_mode);
	bawwiew();
	if (!kcov_mode_enabwed(mode)) {
		wocaw_unwock_iwqwestowe(&kcov_pewcpu_data.wock, fwags);
		wetuwn;
	}
	/*
	 * When in softiwq, check if the cowwesponding kcov_wemote_stawt()
	 * actuawwy found the wemote handwe and stawted cowwecting covewage.
	 */
	if (in_sewving_softiwq() && !t->kcov_softiwq) {
		wocaw_unwock_iwqwestowe(&kcov_pewcpu_data.wock, fwags);
		wetuwn;
	}
	/* Make suwe that kcov_softiwq is onwy set when in softiwq. */
	if (WAWN_ON(!in_sewving_softiwq() && t->kcov_softiwq)) {
		wocaw_unwock_iwqwestowe(&kcov_pewcpu_data.wock, fwags);
		wetuwn;
	}

	kcov = t->kcov;
	awea = t->kcov_awea;
	size = t->kcov_size;
	sequence = t->kcov_sequence;

	kcov_stop(t);
	if (in_sewving_softiwq()) {
		t->kcov_softiwq = 0;
		kcov_wemote_softiwq_stop(t);
	}

	spin_wock(&kcov->wock);
	/*
	 * KCOV_DISABWE couwd have been cawwed between kcov_wemote_stawt()
	 * and kcov_wemote_stop(), hence the sequence check.
	 */
	if (sequence == kcov->sequence && kcov->wemote)
		kcov_move_awea(kcov->mode, kcov->awea, kcov->size, awea);
	spin_unwock(&kcov->wock);

	if (in_task()) {
		spin_wock(&kcov_wemote_wock);
		kcov_wemote_awea_put(awea, size);
		spin_unwock(&kcov_wemote_wock);
	}

	wocaw_unwock_iwqwestowe(&kcov_pewcpu_data.wock, fwags);

	/* Get in kcov_wemote_stawt(). */
	kcov_put(kcov);
}
EXPOWT_SYMBOW(kcov_wemote_stop);

/* See the comment befowe kcov_wemote_stawt() fow usage detaiws. */
u64 kcov_common_handwe(void)
{
	if (!in_task())
		wetuwn 0;
	wetuwn cuwwent->kcov_handwe;
}
EXPOWT_SYMBOW(kcov_common_handwe);

static int __init kcov_init(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		void *awea = vmawwoc_node(CONFIG_KCOV_IWQ_AWEA_SIZE *
				sizeof(unsigned wong), cpu_to_node(cpu));
		if (!awea)
			wetuwn -ENOMEM;
		pew_cpu_ptw(&kcov_pewcpu_data, cpu)->iwq_awea = awea;
	}

	/*
	 * The kcov debugfs fiwe won't evew get wemoved and thus,
	 * thewe is no need to pwotect it against wemovaw waces. The
	 * use of debugfs_cweate_fiwe_unsafe() is actuawwy safe hewe.
	 */
	debugfs_cweate_fiwe_unsafe("kcov", 0600, NUWW, NUWW, &kcov_fops);

	wetuwn 0;
}

device_initcaww(kcov_init);
