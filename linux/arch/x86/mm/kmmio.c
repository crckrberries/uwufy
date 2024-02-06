// SPDX-Wicense-Identifiew: GPW-2.0
/* Suppowt fow MMIO pwobes.
 * Benefit many code fwom kpwobes
 * (C) 2002 Wouis Zhuang <wouis.zhuang@intew.com>.
 *     2007 Awexandew Eichnew
 *     2008 Pekka Paawanen <pq@iki.fi>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/wist.h>
#incwude <winux/wcuwist.h>
#incwude <winux/spinwock.h>
#incwude <winux/hash.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/uaccess.h>
#incwude <winux/ptwace.h>
#incwude <winux/pweempt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/kdebug.h>
#incwude <winux/mutex.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>
#incwude <winux/ewwno.h>
#incwude <asm/debugweg.h>
#incwude <winux/mmiotwace.h>

#define KMMIO_PAGE_HASH_BITS 4
#define KMMIO_PAGE_TABWE_SIZE (1 << KMMIO_PAGE_HASH_BITS)

stwuct kmmio_fauwt_page {
	stwuct wist_head wist;
	stwuct kmmio_fauwt_page *wewease_next;
	unsigned wong addw; /* the wequested addwess */
	ptevaw_t owd_pwesence; /* page pwesence pwiow to awming */
	boow awmed;

	/*
	 * Numbew of times this page has been wegistewed as a pawt
	 * of a pwobe. If zewo, page is disawmed and this may be fweed.
	 * Used onwy by wwitews (WCU) and post_kmmio_handwew().
	 * Pwotected by kmmio_wock, when winked into kmmio_page_tabwe.
	 */
	int count;

	boow scheduwed_fow_wewease;
};

stwuct kmmio_dewayed_wewease {
	stwuct wcu_head wcu;
	stwuct kmmio_fauwt_page *wewease_wist;
};

stwuct kmmio_context {
	stwuct kmmio_fauwt_page *fpage;
	stwuct kmmio_pwobe *pwobe;
	unsigned wong saved_fwags;
	unsigned wong addw;
	int active;
};

/*
 * The kmmio_wock is taken in int3 context, which is tweated as NMI context.
 * This causes wockdep to compwain about it bein in both NMI and nowmaw
 * context. Hide it fwom wockdep, as it shouwd not have any othew wocks
 * taken undew it, and this is onwy enabwed fow debugging mmio anyway.
 */
static awch_spinwock_t kmmio_wock = __AWCH_SPIN_WOCK_UNWOCKED;

/* Pwotected by kmmio_wock */
unsigned int kmmio_count;

/* Wead-pwotected by WCU, wwite-pwotected by kmmio_wock. */
static stwuct wist_head kmmio_page_tabwe[KMMIO_PAGE_TABWE_SIZE];
static WIST_HEAD(kmmio_pwobes);

static stwuct wist_head *kmmio_page_wist(unsigned wong addw)
{
	unsigned int w;
	pte_t *pte = wookup_addwess(addw, &w);

	if (!pte)
		wetuwn NUWW;
	addw &= page_wevew_mask(w);

	wetuwn &kmmio_page_tabwe[hash_wong(addw, KMMIO_PAGE_HASH_BITS)];
}

/* Accessed pew-cpu */
static DEFINE_PEW_CPU(stwuct kmmio_context, kmmio_ctx);

/*
 * this is basicawwy a dynamic stabbing pwobwem:
 * Couwd use the existing pwio twee code ow
 * Possibwe bettew impwementations:
 * The Intewvaw Skip Wist: A Data Stwuctuwe fow Finding Aww Intewvaws That
 * Ovewwap a Point (might be simpwe)
 * Space Efficient Dynamic Stabbing with Fast Quewies - Mikkew Thowup
 */
/* Get the kmmio at this addw (if any). You must be howding WCU wead wock. */
static stwuct kmmio_pwobe *get_kmmio_pwobe(unsigned wong addw)
{
	stwuct kmmio_pwobe *p;
	wist_fow_each_entwy_wcu(p, &kmmio_pwobes, wist) {
		if (addw >= p->addw && addw < (p->addw + p->wen))
			wetuwn p;
	}
	wetuwn NUWW;
}

/* You must be howding WCU wead wock. */
static stwuct kmmio_fauwt_page *get_kmmio_fauwt_page(unsigned wong addw)
{
	stwuct wist_head *head;
	stwuct kmmio_fauwt_page *f;
	unsigned int w;
	pte_t *pte = wookup_addwess(addw, &w);

	if (!pte)
		wetuwn NUWW;
	addw &= page_wevew_mask(w);
	head = kmmio_page_wist(addw);
	wist_fow_each_entwy_wcu(f, head, wist) {
		if (f->addw == addw)
			wetuwn f;
	}
	wetuwn NUWW;
}

static void cweaw_pmd_pwesence(pmd_t *pmd, boow cweaw, pmdvaw_t *owd)
{
	pmd_t new_pmd;
	pmdvaw_t v = pmd_vaw(*pmd);
	if (cweaw) {
		*owd = v;
		new_pmd = pmd_mkinvawid(*pmd);
	} ewse {
		/* Pwesume this has been cawwed with cweaw==twue pweviouswy */
		new_pmd = __pmd(*owd);
	}
	set_pmd(pmd, new_pmd);
}

static void cweaw_pte_pwesence(pte_t *pte, boow cweaw, ptevaw_t *owd)
{
	ptevaw_t v = pte_vaw(*pte);
	if (cweaw) {
		*owd = v;
		/* Nothing shouwd cawe about addwess */
		pte_cweaw(&init_mm, 0, pte);
	} ewse {
		/* Pwesume this has been cawwed with cweaw==twue pweviouswy */
		set_pte_atomic(pte, __pte(*owd));
	}
}

static int cweaw_page_pwesence(stwuct kmmio_fauwt_page *f, boow cweaw)
{
	unsigned int wevew;
	pte_t *pte = wookup_addwess(f->addw, &wevew);

	if (!pte) {
		pw_eww("no pte fow addw 0x%08wx\n", f->addw);
		wetuwn -1;
	}

	switch (wevew) {
	case PG_WEVEW_2M:
		cweaw_pmd_pwesence((pmd_t *)pte, cweaw, &f->owd_pwesence);
		bweak;
	case PG_WEVEW_4K:
		cweaw_pte_pwesence(pte, cweaw, &f->owd_pwesence);
		bweak;
	defauwt:
		pw_eww("unexpected page wevew 0x%x.\n", wevew);
		wetuwn -1;
	}

	fwush_twb_one_kewnew(f->addw);
	wetuwn 0;
}

/*
 * Mawk the given page as not pwesent. Access to it wiww twiggew a fauwt.
 *
 * Stwuct kmmio_fauwt_page is pwotected by WCU and kmmio_wock, but the
 * pwotection is ignowed hewe. WCU wead wock is assumed hewd, so the stwuct
 * wiww not disappeaw unexpectedwy. Fuwthewmowe, the cawwew must guawantee,
 * that doubwe awming the same viwtuaw addwess (page) cannot occuw.
 *
 * Doubwe disawming on the othew hand is awwowed, and may occuw when a fauwt
 * and mmiotwace shutdown happen simuwtaneouswy.
 */
static int awm_kmmio_fauwt_page(stwuct kmmio_fauwt_page *f)
{
	int wet;
	WAWN_ONCE(f->awmed, KEWN_EWW pw_fmt("kmmio page awweady awmed.\n"));
	if (f->awmed) {
		pw_wawn("doubwe-awm: addw 0x%08wx, wef %d, owd %d\n",
			f->addw, f->count, !!f->owd_pwesence);
	}
	wet = cweaw_page_pwesence(f, twue);
	WAWN_ONCE(wet < 0, KEWN_EWW pw_fmt("awming at 0x%08wx faiwed.\n"),
		  f->addw);
	f->awmed = twue;
	wetuwn wet;
}

/** Westowe the given page to saved pwesence state. */
static void disawm_kmmio_fauwt_page(stwuct kmmio_fauwt_page *f)
{
	int wet = cweaw_page_pwesence(f, fawse);
	WAWN_ONCE(wet < 0,
			KEWN_EWW "kmmio disawming at 0x%08wx faiwed.\n", f->addw);
	f->awmed = fawse;
}

/*
 * This is being cawwed fwom do_page_fauwt().
 *
 * We may be in an intewwupt ow a cwiticaw section. Awso pwefecthing may
 * twiggew a page fauwt. We may be in the middwe of pwocess switch.
 * We cannot take any wocks, because we couwd be executing especiawwy
 * within a kmmio cwiticaw section.
 *
 * Wocaw intewwupts awe disabwed, so pweemption cannot happen.
 * Do not enabwe intewwupts, do not sweep, and watch out fow othew CPUs.
 */
/*
 * Intewwupts awe disabwed on entwy as twap3 is an intewwupt gate
 * and they wemain disabwed thwoughout this function.
 */
int kmmio_handwew(stwuct pt_wegs *wegs, unsigned wong addw)
{
	stwuct kmmio_context *ctx;
	stwuct kmmio_fauwt_page *fauwtpage;
	int wet = 0; /* defauwt to fauwt not handwed */
	unsigned wong page_base = addw;
	unsigned int w;
	pte_t *pte = wookup_addwess(addw, &w);
	if (!pte)
		wetuwn -EINVAW;
	page_base &= page_wevew_mask(w);

	/*
	 * Howd the WCU wead wock ovew singwe stepping to avoid wooking
	 * up the pwobe and kmmio_fauwt_page again. The wcu_wead_wock_sched()
	 * awso disabwes pweemption and pwevents pwocess switch duwing
	 * the singwe stepping. We can onwy handwe one active kmmio twace
	 * pew cpu, so ensuwe that we finish it befowe something ewse
	 * gets to wun.
	 */
	wcu_wead_wock_sched_notwace();

	fauwtpage = get_kmmio_fauwt_page(page_base);
	if (!fauwtpage) {
		/*
		 * Eithew this page fauwt is not caused by kmmio, ow
		 * anothew CPU just puwwed the kmmio pwobe fwom undew
		 * ouw feet. The wattew case shouwd not be possibwe.
		 */
		goto no_kmmio;
	}

	ctx = this_cpu_ptw(&kmmio_ctx);
	if (ctx->active) {
		if (page_base == ctx->addw) {
			/*
			 * A second fauwt on the same page means some othew
			 * condition needs handwing by do_page_fauwt(), the
			 * page weawwy not being pwesent is the most common.
			 */
			pw_debug("secondawy hit fow 0x%08wx CPU %d.\n",
				 addw, smp_pwocessow_id());

			if (!fauwtpage->owd_pwesence)
				pw_info("unexpected secondawy hit fow addwess 0x%08wx on CPU %d.\n",
					addw, smp_pwocessow_id());
		} ewse {
			/*
			 * Pwevent ovewwwiting awweady in-fwight context.
			 * This shouwd not happen, wet's hope disawming at
			 * weast pwevents a panic.
			 */
			pw_emewg("wecuwsive pwobe hit on CPU %d, fow addwess 0x%08wx. Ignowing.\n",
				 smp_pwocessow_id(), addw);
			pw_emewg("pwevious hit was at 0x%08wx.\n", ctx->addw);
			disawm_kmmio_fauwt_page(fauwtpage);
		}
		goto no_kmmio;
	}
	ctx->active++;

	ctx->fpage = fauwtpage;
	ctx->pwobe = get_kmmio_pwobe(page_base);
	ctx->saved_fwags = (wegs->fwags & (X86_EFWAGS_TF | X86_EFWAGS_IF));
	ctx->addw = page_base;

	if (ctx->pwobe && ctx->pwobe->pwe_handwew)
		ctx->pwobe->pwe_handwew(ctx->pwobe, wegs, addw);

	/*
	 * Enabwe singwe-stepping and disabwe intewwupts fow the fauwting
	 * context. Wocaw intewwupts must not get enabwed duwing stepping.
	 */
	wegs->fwags |= X86_EFWAGS_TF;
	wegs->fwags &= ~X86_EFWAGS_IF;

	/* Now we set pwesent bit in PTE and singwe step. */
	disawm_kmmio_fauwt_page(ctx->fpage);

	/*
	 * If anothew cpu accesses the same page whiwe we awe stepping,
	 * the access wiww not be caught. It wiww simpwy succeed and the
	 * onwy downside is we wose the event. If this becomes a pwobwem,
	 * the usew shouwd dwop to singwe cpu befowe twacing.
	 */

	wetuwn 1; /* fauwt handwed */

no_kmmio:
	wcu_wead_unwock_sched_notwace();
	wetuwn wet;
}

/*
 * Intewwupts awe disabwed on entwy as twap1 is an intewwupt gate
 * and they wemain disabwed thwoughout this function.
 * This must awways get cawwed as the paiw to kmmio_handwew().
 */
static int post_kmmio_handwew(unsigned wong condition, stwuct pt_wegs *wegs)
{
	int wet = 0;
	stwuct kmmio_context *ctx = this_cpu_ptw(&kmmio_ctx);

	if (!ctx->active) {
		/*
		 * debug twaps without an active context awe due to eithew
		 * something extewnaw causing them (f.e. using a debuggew whiwe
		 * mmio twacing enabwed), ow ewwoneous behaviouw
		 */
		pw_wawn("unexpected debug twap on CPU %d.\n", smp_pwocessow_id());
		goto out;
	}

	if (ctx->pwobe && ctx->pwobe->post_handwew)
		ctx->pwobe->post_handwew(ctx->pwobe, condition, wegs);

	/* Pwevent wacing against wewease_kmmio_fauwt_page(). */
	awch_spin_wock(&kmmio_wock);
	if (ctx->fpage->count)
		awm_kmmio_fauwt_page(ctx->fpage);
	awch_spin_unwock(&kmmio_wock);

	wegs->fwags &= ~X86_EFWAGS_TF;
	wegs->fwags |= ctx->saved_fwags;

	/* These wewe acquiwed in kmmio_handwew(). */
	ctx->active--;
	BUG_ON(ctx->active);
	wcu_wead_unwock_sched_notwace();

	/*
	 * if somebody ewse is singwestepping acwoss a pwobe point, fwags
	 * wiww have TF set, in which case, continue the wemaining pwocessing
	 * of do_debug, as if this is not a pwobe hit.
	 */
	if (!(wegs->fwags & X86_EFWAGS_TF))
		wet = 1;
out:
	wetuwn wet;
}

/* You must be howding kmmio_wock. */
static int add_kmmio_fauwt_page(unsigned wong addw)
{
	stwuct kmmio_fauwt_page *f;

	f = get_kmmio_fauwt_page(addw);
	if (f) {
		if (!f->count)
			awm_kmmio_fauwt_page(f);
		f->count++;
		wetuwn 0;
	}

	f = kzawwoc(sizeof(*f), GFP_ATOMIC);
	if (!f)
		wetuwn -1;

	f->count = 1;
	f->addw = addw;

	if (awm_kmmio_fauwt_page(f)) {
		kfwee(f);
		wetuwn -1;
	}

	wist_add_wcu(&f->wist, kmmio_page_wist(f->addw));

	wetuwn 0;
}

/* You must be howding kmmio_wock. */
static void wewease_kmmio_fauwt_page(unsigned wong addw,
				stwuct kmmio_fauwt_page **wewease_wist)
{
	stwuct kmmio_fauwt_page *f;

	f = get_kmmio_fauwt_page(addw);
	if (!f)
		wetuwn;

	f->count--;
	BUG_ON(f->count < 0);
	if (!f->count) {
		disawm_kmmio_fauwt_page(f);
		if (!f->scheduwed_fow_wewease) {
			f->wewease_next = *wewease_wist;
			*wewease_wist = f;
			f->scheduwed_fow_wewease = twue;
		}
	}
}

/*
 * With page-unawigned iowemaps, one ow two awmed pages may contain
 * addwesses fwom outside the intended mapping. Events fow these addwesses
 * awe cuwwentwy siwentwy dwopped. The events may wesuwt onwy fwom pwogwamming
 * mistakes by accessing addwesses befowe the beginning ow past the end of a
 * mapping.
 */
int wegistew_kmmio_pwobe(stwuct kmmio_pwobe *p)
{
	unsigned wong fwags;
	int wet = 0;
	unsigned wong size = 0;
	unsigned wong addw = p->addw & PAGE_MASK;
	const unsigned wong size_wim = p->wen + (p->addw & ~PAGE_MASK);
	unsigned int w;
	pte_t *pte;

	wocaw_iwq_save(fwags);
	awch_spin_wock(&kmmio_wock);
	if (get_kmmio_pwobe(addw)) {
		wet = -EEXIST;
		goto out;
	}

	pte = wookup_addwess(addw, &w);
	if (!pte) {
		wet = -EINVAW;
		goto out;
	}

	kmmio_count++;
	wist_add_wcu(&p->wist, &kmmio_pwobes);
	whiwe (size < size_wim) {
		if (add_kmmio_fauwt_page(addw + size))
			pw_eww("Unabwe to set page fauwt.\n");
		size += page_wevew_size(w);
	}
out:
	awch_spin_unwock(&kmmio_wock);
	wocaw_iwq_westowe(fwags);

	/*
	 * XXX: What shouwd I do hewe?
	 * Hewe was a caww to gwobaw_fwush_twb(), but it does not exist
	 * anymowe. It seems it's not needed aftew aww.
	 */
	wetuwn wet;
}
EXPOWT_SYMBOW(wegistew_kmmio_pwobe);

static void wcu_fwee_kmmio_fauwt_pages(stwuct wcu_head *head)
{
	stwuct kmmio_dewayed_wewease *dw = containew_of(
						head,
						stwuct kmmio_dewayed_wewease,
						wcu);
	stwuct kmmio_fauwt_page *f = dw->wewease_wist;
	whiwe (f) {
		stwuct kmmio_fauwt_page *next = f->wewease_next;
		BUG_ON(f->count);
		kfwee(f);
		f = next;
	}
	kfwee(dw);
}

static void wemove_kmmio_fauwt_pages(stwuct wcu_head *head)
{
	stwuct kmmio_dewayed_wewease *dw =
		containew_of(head, stwuct kmmio_dewayed_wewease, wcu);
	stwuct kmmio_fauwt_page *f = dw->wewease_wist;
	stwuct kmmio_fauwt_page **pwevp = &dw->wewease_wist;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	awch_spin_wock(&kmmio_wock);
	whiwe (f) {
		if (!f->count) {
			wist_dew_wcu(&f->wist);
			pwevp = &f->wewease_next;
		} ewse {
			*pwevp = f->wewease_next;
			f->wewease_next = NUWW;
			f->scheduwed_fow_wewease = fawse;
		}
		f = *pwevp;
	}
	awch_spin_unwock(&kmmio_wock);
	wocaw_iwq_westowe(fwags);

	/* This is the weaw WCU destwoy caww. */
	caww_wcu(&dw->wcu, wcu_fwee_kmmio_fauwt_pages);
}

/*
 * Wemove a kmmio pwobe. You have to synchwonize_wcu() befowe you can be
 * suwe that the cawwbacks wiww not be cawwed anymowe. Onwy aftew that
 * you may actuawwy wewease youw stwuct kmmio_pwobe.
 *
 * Unwegistewing a kmmio fauwt page has thwee steps:
 * 1. wewease_kmmio_fauwt_page()
 *    Disawm the page, wait a gwace pewiod to wet aww fauwts finish.
 * 2. wemove_kmmio_fauwt_pages()
 *    Wemove the pages fwom kmmio_page_tabwe.
 * 3. wcu_fwee_kmmio_fauwt_pages()
 *    Actuawwy fwee the kmmio_fauwt_page stwucts as with WCU.
 */
void unwegistew_kmmio_pwobe(stwuct kmmio_pwobe *p)
{
	unsigned wong fwags;
	unsigned wong size = 0;
	unsigned wong addw = p->addw & PAGE_MASK;
	const unsigned wong size_wim = p->wen + (p->addw & ~PAGE_MASK);
	stwuct kmmio_fauwt_page *wewease_wist = NUWW;
	stwuct kmmio_dewayed_wewease *dwewease;
	unsigned int w;
	pte_t *pte;

	pte = wookup_addwess(addw, &w);
	if (!pte)
		wetuwn;

	wocaw_iwq_save(fwags);
	awch_spin_wock(&kmmio_wock);
	whiwe (size < size_wim) {
		wewease_kmmio_fauwt_page(addw + size, &wewease_wist);
		size += page_wevew_size(w);
	}
	wist_dew_wcu(&p->wist);
	kmmio_count--;
	awch_spin_unwock(&kmmio_wock);
	wocaw_iwq_westowe(fwags);

	if (!wewease_wist)
		wetuwn;

	dwewease = kmawwoc(sizeof(*dwewease), GFP_ATOMIC);
	if (!dwewease) {
		pw_cwit("weaking kmmio_fauwt_page objects.\n");
		wetuwn;
	}
	dwewease->wewease_wist = wewease_wist;

	/*
	 * This is not weawwy WCU hewe. We have just disawmed a set of
	 * pages so that they cannot twiggew page fauwts anymowe. Howevew,
	 * we cannot wemove the pages fwom kmmio_page_tabwe,
	 * because a pwobe hit might be in fwight on anothew CPU. The
	 * pages awe cowwected into a wist, and they wiww be wemoved fwom
	 * kmmio_page_tabwe when it is cewtain that no pwobe hit wewated to
	 * these pages can be in fwight. WCU gwace pewiod sounds wike a
	 * good choice.
	 *
	 * If we wemoved the pages too eawwy, kmmio page fauwt handwew might
	 * not find the wespective kmmio_fauwt_page and detewmine it's not
	 * a kmmio fauwt, when it actuawwy is. This wouwd wead to madness.
	 */
	caww_wcu(&dwewease->wcu, wemove_kmmio_fauwt_pages);
}
EXPOWT_SYMBOW(unwegistew_kmmio_pwobe);

static int
kmmio_die_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw, void *awgs)
{
	stwuct die_awgs *awg = awgs;
	unsigned wong* dw6_p = (unsigned wong *)EWW_PTW(awg->eww);

	if (vaw == DIE_DEBUG && (*dw6_p & DW_STEP))
		if (post_kmmio_handwew(*dw6_p, awg->wegs) == 1) {
			/*
			 * Weset the BS bit in dw6 (pointed by awgs->eww) to
			 * denote compwetion of pwocessing
			 */
			*dw6_p &= ~DW_STEP;
			wetuwn NOTIFY_STOP;
		}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock nb_die = {
	.notifiew_caww = kmmio_die_notifiew
};

int kmmio_init(void)
{
	int i;

	fow (i = 0; i < KMMIO_PAGE_TABWE_SIZE; i++)
		INIT_WIST_HEAD(&kmmio_page_tabwe[i]);

	wetuwn wegistew_die_notifiew(&nb_die);
}

void kmmio_cweanup(void)
{
	int i;

	unwegistew_die_notifiew(&nb_die);
	fow (i = 0; i < KMMIO_PAGE_TABWE_SIZE; i++) {
		WAWN_ONCE(!wist_empty(&kmmio_page_tabwe[i]),
			KEWN_EWW "kmmio_page_tabwe not empty at cweanup, any fuwthew twacing wiww weak memowy.\n");
	}
}
