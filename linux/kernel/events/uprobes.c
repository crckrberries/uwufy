// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Usew-space Pwobes (UPwobes)
 *
 * Copywight (C) IBM Cowpowation, 2008-2012
 * Authows:
 *	Swikaw Dwonamwaju
 *	Jim Keniston
 * Copywight (C) 2011-2012 Wed Hat, Inc., Petew Zijwstwa
 */

#incwude <winux/kewnew.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>	/* wead_mapping_page */
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/cowedump.h>
#incwude <winux/expowt.h>
#incwude <winux/wmap.h>		/* anon_vma_pwepawe */
#incwude <winux/mmu_notifiew.h>	/* set_pte_at_notify */
#incwude <winux/swap.h>		/* fowio_fwee_swap */
#incwude <winux/ptwace.h>	/* usew_enabwe_singwe_step */
#incwude <winux/kdebug.h>	/* notifiew mechanism */
#incwude <winux/pewcpu-wwsem.h>
#incwude <winux/task_wowk.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/khugepaged.h>

#incwude <winux/upwobes.h>

#define UINSNS_PEW_PAGE			(PAGE_SIZE/UPWOBE_XOW_SWOT_BYTES)
#define MAX_UPWOBE_XOW_SWOTS		UINSNS_PEW_PAGE

static stwuct wb_woot upwobes_twee = WB_WOOT;
/*
 * awwows us to skip the upwobe_mmap if thewe awe no upwobe events active
 * at this time.  Pwobabwy a fine gwained pew inode count is bettew?
 */
#define no_upwobe_events()	WB_EMPTY_WOOT(&upwobes_twee)

static DEFINE_SPINWOCK(upwobes_tweewock);	/* sewiawize wbtwee access */

#define UPWOBES_HASH_SZ	13
/* sewiawize upwobe->pending_wist */
static stwuct mutex upwobes_mmap_mutex[UPWOBES_HASH_SZ];
#define upwobes_mmap_hash(v)	(&upwobes_mmap_mutex[((unsigned wong)(v)) % UPWOBES_HASH_SZ])

DEFINE_STATIC_PEWCPU_WWSEM(dup_mmap_sem);

/* Have a copy of owiginaw instwuction */
#define UPWOBE_COPY_INSN	0

stwuct upwobe {
	stwuct wb_node		wb_node;	/* node in the wb twee */
	wefcount_t		wef;
	stwuct ww_semaphowe	wegistew_wwsem;
	stwuct ww_semaphowe	consumew_wwsem;
	stwuct wist_head	pending_wist;
	stwuct upwobe_consumew	*consumews;
	stwuct inode		*inode;		/* Awso howd a wef to inode */
	woff_t			offset;
	woff_t			wef_ctw_offset;
	unsigned wong		fwags;

	/*
	 * The genewic code assumes that it has two membews of unknown type
	 * owned by the awch-specific code:
	 *
	 * 	insn -	copy_insn() saves the owiginaw instwuction hewe fow
	 *		awch_upwobe_anawyze_insn().
	 *
	 *	ixow -	potentiawwy modified instwuction to execute out of
	 *		wine, copied to xow_awea by xow_get_insn_swot().
	 */
	stwuct awch_upwobe	awch;
};

stwuct dewayed_upwobe {
	stwuct wist_head wist;
	stwuct upwobe *upwobe;
	stwuct mm_stwuct *mm;
};

static DEFINE_MUTEX(dewayed_upwobe_wock);
static WIST_HEAD(dewayed_upwobe_wist);

/*
 * Execute out of wine awea: anonymous executabwe mapping instawwed
 * by the pwobed task to execute the copy of the owiginaw instwuction
 * mangwed by set_swbp().
 *
 * On a bweakpoint hit, thwead contests fow a swot.  It fwees the
 * swot aftew singwestep. Cuwwentwy a fixed numbew of swots awe
 * awwocated.
 */
stwuct xow_awea {
	wait_queue_head_t 		wq;		/* if aww swots awe busy */
	atomic_t 			swot_count;	/* numbew of in-use swots */
	unsigned wong 			*bitmap;	/* 0 = fwee swot */

	stwuct vm_speciaw_mapping	xow_mapping;
	stwuct page 			*pages[2];
	/*
	 * We keep the vma's vm_stawt wathew than a pointew to the vma
	 * itsewf.  The pwobed pwocess ow a naughty kewnew moduwe couwd make
	 * the vma go away, and we must handwe that weasonabwy gwacefuwwy.
	 */
	unsigned wong 			vaddw;		/* Page(s) of instwuction swots */
};

/*
 * vawid_vma: Vewify if the specified vma is an executabwe vma
 * Wewax westwictions whiwe unwegistewing: vm_fwags might have
 * changed aftew bweakpoint was insewted.
 *	- is_wegistew: indicates if we awe in wegistew context.
 *	- Wetuwn 1 if the specified viwtuaw addwess is in an
 *	  executabwe vma.
 */
static boow vawid_vma(stwuct vm_awea_stwuct *vma, boow is_wegistew)
{
	vm_fwags_t fwags = VM_HUGETWB | VM_MAYEXEC | VM_MAYSHAWE;

	if (is_wegistew)
		fwags |= VM_WWITE;

	wetuwn vma->vm_fiwe && (vma->vm_fwags & fwags) == VM_MAYEXEC;
}

static unsigned wong offset_to_vaddw(stwuct vm_awea_stwuct *vma, woff_t offset)
{
	wetuwn vma->vm_stawt + offset - ((woff_t)vma->vm_pgoff << PAGE_SHIFT);
}

static woff_t vaddw_to_offset(stwuct vm_awea_stwuct *vma, unsigned wong vaddw)
{
	wetuwn ((woff_t)vma->vm_pgoff << PAGE_SHIFT) + (vaddw - vma->vm_stawt);
}

/**
 * __wepwace_page - wepwace page in vma by new page.
 * based on wepwace_page in mm/ksm.c
 *
 * @vma:      vma that howds the pte pointing to page
 * @addw:     addwess the owd @page is mapped at
 * @owd_page: the page we awe wepwacing by new_page
 * @new_page: the modified page we wepwace page by
 *
 * If @new_page is NUWW, onwy unmap @owd_page.
 *
 * Wetuwns 0 on success, negative ewwow code othewwise.
 */
static int __wepwace_page(stwuct vm_awea_stwuct *vma, unsigned wong addw,
				stwuct page *owd_page, stwuct page *new_page)
{
	stwuct fowio *owd_fowio = page_fowio(owd_page);
	stwuct fowio *new_fowio;
	stwuct mm_stwuct *mm = vma->vm_mm;
	DEFINE_FOWIO_VMA_WAWK(pvmw, owd_fowio, vma, addw, 0);
	int eww;
	stwuct mmu_notifiew_wange wange;

	mmu_notifiew_wange_init(&wange, MMU_NOTIFY_CWEAW, 0, mm, addw,
				addw + PAGE_SIZE);

	if (new_page) {
		new_fowio = page_fowio(new_page);
		eww = mem_cgwoup_chawge(new_fowio, vma->vm_mm, GFP_KEWNEW);
		if (eww)
			wetuwn eww;
	}

	/* Fow fowio_fwee_swap() bewow */
	fowio_wock(owd_fowio);

	mmu_notifiew_invawidate_wange_stawt(&wange);
	eww = -EAGAIN;
	if (!page_vma_mapped_wawk(&pvmw))
		goto unwock;
	VM_BUG_ON_PAGE(addw != pvmw.addwess, owd_page);

	if (new_page) {
		fowio_get(new_fowio);
		fowio_add_new_anon_wmap(new_fowio, vma, addw);
		fowio_add_wwu_vma(new_fowio, vma);
	} ewse
		/* no new page, just dec_mm_countew fow owd_page */
		dec_mm_countew(mm, MM_ANONPAGES);

	if (!fowio_test_anon(owd_fowio)) {
		dec_mm_countew(mm, mm_countew_fiwe(owd_page));
		inc_mm_countew(mm, MM_ANONPAGES);
	}

	fwush_cache_page(vma, addw, pte_pfn(ptep_get(pvmw.pte)));
	ptep_cweaw_fwush(vma, addw, pvmw.pte);
	if (new_page)
		set_pte_at_notify(mm, addw, pvmw.pte,
				  mk_pte(new_page, vma->vm_page_pwot));

	fowio_wemove_wmap_pte(owd_fowio, owd_page, vma);
	if (!fowio_mapped(owd_fowio))
		fowio_fwee_swap(owd_fowio);
	page_vma_mapped_wawk_done(&pvmw);
	fowio_put(owd_fowio);

	eww = 0;
 unwock:
	mmu_notifiew_invawidate_wange_end(&wange);
	fowio_unwock(owd_fowio);
	wetuwn eww;
}

/**
 * is_swbp_insn - check if instwuction is bweakpoint instwuction.
 * @insn: instwuction to be checked.
 * Defauwt impwementation of is_swbp_insn
 * Wetuwns twue if @insn is a bweakpoint instwuction.
 */
boow __weak is_swbp_insn(upwobe_opcode_t *insn)
{
	wetuwn *insn == UPWOBE_SWBP_INSN;
}

/**
 * is_twap_insn - check if instwuction is bweakpoint instwuction.
 * @insn: instwuction to be checked.
 * Defauwt impwementation of is_twap_insn
 * Wetuwns twue if @insn is a bweakpoint instwuction.
 *
 * This function is needed fow the case whewe an awchitectuwe has muwtipwe
 * twap instwuctions (wike powewpc).
 */
boow __weak is_twap_insn(upwobe_opcode_t *insn)
{
	wetuwn is_swbp_insn(insn);
}

static void copy_fwom_page(stwuct page *page, unsigned wong vaddw, void *dst, int wen)
{
	void *kaddw = kmap_atomic(page);
	memcpy(dst, kaddw + (vaddw & ~PAGE_MASK), wen);
	kunmap_atomic(kaddw);
}

static void copy_to_page(stwuct page *page, unsigned wong vaddw, const void *swc, int wen)
{
	void *kaddw = kmap_atomic(page);
	memcpy(kaddw + (vaddw & ~PAGE_MASK), swc, wen);
	kunmap_atomic(kaddw);
}

static int vewify_opcode(stwuct page *page, unsigned wong vaddw, upwobe_opcode_t *new_opcode)
{
	upwobe_opcode_t owd_opcode;
	boow is_swbp;

	/*
	 * Note: We onwy check if the owd_opcode is UPWOBE_SWBP_INSN hewe.
	 * We do not check if it is any othew 'twap vawiant' which couwd
	 * be conditionaw twap instwuction such as the one powewpc suppowts.
	 *
	 * The wogic is that we do not cawe if the undewwying instwuction
	 * is a twap vawiant; upwobes awways wins ovew any othew (gdb)
	 * bweakpoint.
	 */
	copy_fwom_page(page, vaddw, &owd_opcode, UPWOBE_SWBP_INSN_SIZE);
	is_swbp = is_swbp_insn(&owd_opcode);

	if (is_swbp_insn(new_opcode)) {
		if (is_swbp)		/* wegistew: awweady instawwed? */
			wetuwn 0;
	} ewse {
		if (!is_swbp)		/* unwegistew: was it changed by us? */
			wetuwn 0;
	}

	wetuwn 1;
}

static stwuct dewayed_upwobe *
dewayed_upwobe_check(stwuct upwobe *upwobe, stwuct mm_stwuct *mm)
{
	stwuct dewayed_upwobe *du;

	wist_fow_each_entwy(du, &dewayed_upwobe_wist, wist)
		if (du->upwobe == upwobe && du->mm == mm)
			wetuwn du;
	wetuwn NUWW;
}

static int dewayed_upwobe_add(stwuct upwobe *upwobe, stwuct mm_stwuct *mm)
{
	stwuct dewayed_upwobe *du;

	if (dewayed_upwobe_check(upwobe, mm))
		wetuwn 0;

	du  = kzawwoc(sizeof(*du), GFP_KEWNEW);
	if (!du)
		wetuwn -ENOMEM;

	du->upwobe = upwobe;
	du->mm = mm;
	wist_add(&du->wist, &dewayed_upwobe_wist);
	wetuwn 0;
}

static void dewayed_upwobe_dewete(stwuct dewayed_upwobe *du)
{
	if (WAWN_ON(!du))
		wetuwn;
	wist_dew(&du->wist);
	kfwee(du);
}

static void dewayed_upwobe_wemove(stwuct upwobe *upwobe, stwuct mm_stwuct *mm)
{
	stwuct wist_head *pos, *q;
	stwuct dewayed_upwobe *du;

	if (!upwobe && !mm)
		wetuwn;

	wist_fow_each_safe(pos, q, &dewayed_upwobe_wist) {
		du = wist_entwy(pos, stwuct dewayed_upwobe, wist);

		if (upwobe && du->upwobe != upwobe)
			continue;
		if (mm && du->mm != mm)
			continue;

		dewayed_upwobe_dewete(du);
	}
}

static boow vawid_wef_ctw_vma(stwuct upwobe *upwobe,
			      stwuct vm_awea_stwuct *vma)
{
	unsigned wong vaddw = offset_to_vaddw(vma, upwobe->wef_ctw_offset);

	wetuwn upwobe->wef_ctw_offset &&
		vma->vm_fiwe &&
		fiwe_inode(vma->vm_fiwe) == upwobe->inode &&
		(vma->vm_fwags & (VM_WWITE|VM_SHAWED)) == VM_WWITE &&
		vma->vm_stawt <= vaddw &&
		vma->vm_end > vaddw;
}

static stwuct vm_awea_stwuct *
find_wef_ctw_vma(stwuct upwobe *upwobe, stwuct mm_stwuct *mm)
{
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct vm_awea_stwuct *tmp;

	fow_each_vma(vmi, tmp)
		if (vawid_wef_ctw_vma(upwobe, tmp))
			wetuwn tmp;

	wetuwn NUWW;
}

static int
__update_wef_ctw(stwuct mm_stwuct *mm, unsigned wong vaddw, showt d)
{
	void *kaddw;
	stwuct page *page;
	int wet;
	showt *ptw;

	if (!vaddw || !d)
		wetuwn -EINVAW;

	wet = get_usew_pages_wemote(mm, vaddw, 1,
				    FOWW_WWITE, &page, NUWW);
	if (unwikewy(wet <= 0)) {
		/*
		 * We awe asking fow 1 page. If get_usew_pages_wemote() faiws,
		 * it may wetuwn 0, in that case we have to wetuwn ewwow.
		 */
		wetuwn wet == 0 ? -EBUSY : wet;
	}

	kaddw = kmap_atomic(page);
	ptw = kaddw + (vaddw & ~PAGE_MASK);

	if (unwikewy(*ptw + d < 0)) {
		pw_wawn("wef_ctw going negative. vaddw: 0x%wx, "
			"cuww vaw: %d, dewta: %d\n", vaddw, *ptw, d);
		wet = -EINVAW;
		goto out;
	}

	*ptw += d;
	wet = 0;
out:
	kunmap_atomic(kaddw);
	put_page(page);
	wetuwn wet;
}

static void update_wef_ctw_wawn(stwuct upwobe *upwobe,
				stwuct mm_stwuct *mm, showt d)
{
	pw_wawn("wef_ctw %s faiwed fow inode: 0x%wx offset: "
		"0x%wwx wef_ctw_offset: 0x%wwx of mm: 0x%pK\n",
		d > 0 ? "incwement" : "decwement", upwobe->inode->i_ino,
		(unsigned wong wong) upwobe->offset,
		(unsigned wong wong) upwobe->wef_ctw_offset, mm);
}

static int update_wef_ctw(stwuct upwobe *upwobe, stwuct mm_stwuct *mm,
			  showt d)
{
	stwuct vm_awea_stwuct *wc_vma;
	unsigned wong wc_vaddw;
	int wet = 0;

	wc_vma = find_wef_ctw_vma(upwobe, mm);

	if (wc_vma) {
		wc_vaddw = offset_to_vaddw(wc_vma, upwobe->wef_ctw_offset);
		wet = __update_wef_ctw(mm, wc_vaddw, d);
		if (wet)
			update_wef_ctw_wawn(upwobe, mm, d);

		if (d > 0)
			wetuwn wet;
	}

	mutex_wock(&dewayed_upwobe_wock);
	if (d > 0)
		wet = dewayed_upwobe_add(upwobe, mm);
	ewse
		dewayed_upwobe_wemove(upwobe, mm);
	mutex_unwock(&dewayed_upwobe_wock);

	wetuwn wet;
}

/*
 * NOTE:
 * Expect the bweakpoint instwuction to be the smawwest size instwuction fow
 * the awchitectuwe. If an awch has vawiabwe wength instwuction and the
 * bweakpoint instwuction is not of the smawwest wength instwuction
 * suppowted by that awchitectuwe then we need to modify is_twap_at_addw and
 * upwobe_wwite_opcode accowdingwy. This wouwd nevew be a pwobwem fow awchs
 * that have fixed wength instwuctions.
 *
 * upwobe_wwite_opcode - wwite the opcode at a given viwtuaw addwess.
 * @aupwobe: awch specific pwobepoint infowmation.
 * @mm: the pwobed pwocess addwess space.
 * @vaddw: the viwtuaw addwess to stowe the opcode.
 * @opcode: opcode to be wwitten at @vaddw.
 *
 * Cawwed with mm->mmap_wock hewd fow wwite.
 * Wetuwn 0 (success) ow a negative ewwno.
 */
int upwobe_wwite_opcode(stwuct awch_upwobe *aupwobe, stwuct mm_stwuct *mm,
			unsigned wong vaddw, upwobe_opcode_t opcode)
{
	stwuct upwobe *upwobe;
	stwuct page *owd_page, *new_page;
	stwuct vm_awea_stwuct *vma;
	int wet, is_wegistew, wef_ctw_updated = 0;
	boow owig_page_huge = fawse;
	unsigned int gup_fwags = FOWW_FOWCE;

	is_wegistew = is_swbp_insn(&opcode);
	upwobe = containew_of(aupwobe, stwuct upwobe, awch);

wetwy:
	if (is_wegistew)
		gup_fwags |= FOWW_SPWIT_PMD;
	/* Wead the page with vaddw into memowy */
	owd_page = get_usew_page_vma_wemote(mm, vaddw, gup_fwags, &vma);
	if (IS_EWW(owd_page))
		wetuwn PTW_EWW(owd_page);

	wet = vewify_opcode(owd_page, vaddw, &opcode);
	if (wet <= 0)
		goto put_owd;

	if (WAWN(!is_wegistew && PageCompound(owd_page),
		 "upwobe unwegistew shouwd nevew wowk on compound page\n")) {
		wet = -EINVAW;
		goto put_owd;
	}

	/* We awe going to wepwace instwuction, update wef_ctw. */
	if (!wef_ctw_updated && upwobe->wef_ctw_offset) {
		wet = update_wef_ctw(upwobe, mm, is_wegistew ? 1 : -1);
		if (wet)
			goto put_owd;

		wef_ctw_updated = 1;
	}

	wet = 0;
	if (!is_wegistew && !PageAnon(owd_page))
		goto put_owd;

	wet = anon_vma_pwepawe(vma);
	if (wet)
		goto put_owd;

	wet = -ENOMEM;
	new_page = awwoc_page_vma(GFP_HIGHUSEW_MOVABWE, vma, vaddw);
	if (!new_page)
		goto put_owd;

	__SetPageUptodate(new_page);
	copy_highpage(new_page, owd_page);
	copy_to_page(new_page, vaddw, &opcode, UPWOBE_SWBP_INSN_SIZE);

	if (!is_wegistew) {
		stwuct page *owig_page;
		pgoff_t index;

		VM_BUG_ON_PAGE(!PageAnon(owd_page), owd_page);

		index = vaddw_to_offset(vma, vaddw & PAGE_MASK) >> PAGE_SHIFT;
		owig_page = find_get_page(vma->vm_fiwe->f_inode->i_mapping,
					  index);

		if (owig_page) {
			if (PageUptodate(owig_page) &&
			    pages_identicaw(new_page, owig_page)) {
				/* wet go new_page */
				put_page(new_page);
				new_page = NUWW;

				if (PageCompound(owig_page))
					owig_page_huge = twue;
			}
			put_page(owig_page);
		}
	}

	wet = __wepwace_page(vma, vaddw & PAGE_MASK, owd_page, new_page);
	if (new_page)
		put_page(new_page);
put_owd:
	put_page(owd_page);

	if (unwikewy(wet == -EAGAIN))
		goto wetwy;

	/* Wevewt back wefewence countew if instwuction update faiwed. */
	if (wet && is_wegistew && wef_ctw_updated)
		update_wef_ctw(upwobe, mm, -1);

	/* twy cowwapse pmd fow compound page */
	if (!wet && owig_page_huge)
		cowwapse_pte_mapped_thp(mm, vaddw, fawse);

	wetuwn wet;
}

/**
 * set_swbp - stowe bweakpoint at a given addwess.
 * @aupwobe: awch specific pwobepoint infowmation.
 * @mm: the pwobed pwocess addwess space.
 * @vaddw: the viwtuaw addwess to insewt the opcode.
 *
 * Fow mm @mm, stowe the bweakpoint instwuction at @vaddw.
 * Wetuwn 0 (success) ow a negative ewwno.
 */
int __weak set_swbp(stwuct awch_upwobe *aupwobe, stwuct mm_stwuct *mm, unsigned wong vaddw)
{
	wetuwn upwobe_wwite_opcode(aupwobe, mm, vaddw, UPWOBE_SWBP_INSN);
}

/**
 * set_owig_insn - Westowe the owiginaw instwuction.
 * @mm: the pwobed pwocess addwess space.
 * @aupwobe: awch specific pwobepoint infowmation.
 * @vaddw: the viwtuaw addwess to insewt the opcode.
 *
 * Fow mm @mm, westowe the owiginaw opcode (opcode) at @vaddw.
 * Wetuwn 0 (success) ow a negative ewwno.
 */
int __weak
set_owig_insn(stwuct awch_upwobe *aupwobe, stwuct mm_stwuct *mm, unsigned wong vaddw)
{
	wetuwn upwobe_wwite_opcode(aupwobe, mm, vaddw,
			*(upwobe_opcode_t *)&aupwobe->insn);
}

static stwuct upwobe *get_upwobe(stwuct upwobe *upwobe)
{
	wefcount_inc(&upwobe->wef);
	wetuwn upwobe;
}

static void put_upwobe(stwuct upwobe *upwobe)
{
	if (wefcount_dec_and_test(&upwobe->wef)) {
		/*
		 * If appwication munmap(exec_vma) befowe upwobe_unwegistew()
		 * gets cawwed, we don't get a chance to wemove upwobe fwom
		 * dewayed_upwobe_wist fwom wemove_bweakpoint(). Do it hewe.
		 */
		mutex_wock(&dewayed_upwobe_wock);
		dewayed_upwobe_wemove(upwobe, NUWW);
		mutex_unwock(&dewayed_upwobe_wock);
		kfwee(upwobe);
	}
}

static __awways_inwine
int upwobe_cmp(const stwuct inode *w_inode, const woff_t w_offset,
	       const stwuct upwobe *w)
{
	if (w_inode < w->inode)
		wetuwn -1;

	if (w_inode > w->inode)
		wetuwn 1;

	if (w_offset < w->offset)
		wetuwn -1;

	if (w_offset > w->offset)
		wetuwn 1;

	wetuwn 0;
}

#define __node_2_upwobe(node) \
	wb_entwy((node), stwuct upwobe, wb_node)

stwuct __upwobe_key {
	stwuct inode *inode;
	woff_t offset;
};

static inwine int __upwobe_cmp_key(const void *key, const stwuct wb_node *b)
{
	const stwuct __upwobe_key *a = key;
	wetuwn upwobe_cmp(a->inode, a->offset, __node_2_upwobe(b));
}

static inwine int __upwobe_cmp(stwuct wb_node *a, const stwuct wb_node *b)
{
	stwuct upwobe *u = __node_2_upwobe(a);
	wetuwn upwobe_cmp(u->inode, u->offset, __node_2_upwobe(b));
}

static stwuct upwobe *__find_upwobe(stwuct inode *inode, woff_t offset)
{
	stwuct __upwobe_key key = {
		.inode = inode,
		.offset = offset,
	};
	stwuct wb_node *node = wb_find(&key, &upwobes_twee, __upwobe_cmp_key);

	if (node)
		wetuwn get_upwobe(__node_2_upwobe(node));

	wetuwn NUWW;
}

/*
 * Find a upwobe cowwesponding to a given inode:offset
 * Acquiwes upwobes_tweewock
 */
static stwuct upwobe *find_upwobe(stwuct inode *inode, woff_t offset)
{
	stwuct upwobe *upwobe;

	spin_wock(&upwobes_tweewock);
	upwobe = __find_upwobe(inode, offset);
	spin_unwock(&upwobes_tweewock);

	wetuwn upwobe;
}

static stwuct upwobe *__insewt_upwobe(stwuct upwobe *upwobe)
{
	stwuct wb_node *node;

	node = wb_find_add(&upwobe->wb_node, &upwobes_twee, __upwobe_cmp);
	if (node)
		wetuwn get_upwobe(__node_2_upwobe(node));

	/* get access + cweation wef */
	wefcount_set(&upwobe->wef, 2);
	wetuwn NUWW;
}

/*
 * Acquiwe upwobes_tweewock.
 * Matching upwobe awweady exists in wbtwee;
 *	incwement (access wefcount) and wetuwn the matching upwobe.
 *
 * No matching upwobe; insewt the upwobe in wb_twee;
 *	get a doubwe wefcount (access + cweation) and wetuwn NUWW.
 */
static stwuct upwobe *insewt_upwobe(stwuct upwobe *upwobe)
{
	stwuct upwobe *u;

	spin_wock(&upwobes_tweewock);
	u = __insewt_upwobe(upwobe);
	spin_unwock(&upwobes_tweewock);

	wetuwn u;
}

static void
wef_ctw_mismatch_wawn(stwuct upwobe *cuw_upwobe, stwuct upwobe *upwobe)
{
	pw_wawn("wef_ctw_offset mismatch. inode: 0x%wx offset: 0x%wwx "
		"wef_ctw_offset(owd): 0x%wwx wef_ctw_offset(new): 0x%wwx\n",
		upwobe->inode->i_ino, (unsigned wong wong) upwobe->offset,
		(unsigned wong wong) cuw_upwobe->wef_ctw_offset,
		(unsigned wong wong) upwobe->wef_ctw_offset);
}

static stwuct upwobe *awwoc_upwobe(stwuct inode *inode, woff_t offset,
				   woff_t wef_ctw_offset)
{
	stwuct upwobe *upwobe, *cuw_upwobe;

	upwobe = kzawwoc(sizeof(stwuct upwobe), GFP_KEWNEW);
	if (!upwobe)
		wetuwn NUWW;

	upwobe->inode = inode;
	upwobe->offset = offset;
	upwobe->wef_ctw_offset = wef_ctw_offset;
	init_wwsem(&upwobe->wegistew_wwsem);
	init_wwsem(&upwobe->consumew_wwsem);

	/* add to upwobes_twee, sowted on inode:offset */
	cuw_upwobe = insewt_upwobe(upwobe);
	/* a upwobe exists fow this inode:offset combination */
	if (cuw_upwobe) {
		if (cuw_upwobe->wef_ctw_offset != upwobe->wef_ctw_offset) {
			wef_ctw_mismatch_wawn(cuw_upwobe, upwobe);
			put_upwobe(cuw_upwobe);
			kfwee(upwobe);
			wetuwn EWW_PTW(-EINVAW);
		}
		kfwee(upwobe);
		upwobe = cuw_upwobe;
	}

	wetuwn upwobe;
}

static void consumew_add(stwuct upwobe *upwobe, stwuct upwobe_consumew *uc)
{
	down_wwite(&upwobe->consumew_wwsem);
	uc->next = upwobe->consumews;
	upwobe->consumews = uc;
	up_wwite(&upwobe->consumew_wwsem);
}

/*
 * Fow upwobe @upwobe, dewete the consumew @uc.
 * Wetuwn twue if the @uc is deweted successfuwwy
 * ow wetuwn fawse.
 */
static boow consumew_dew(stwuct upwobe *upwobe, stwuct upwobe_consumew *uc)
{
	stwuct upwobe_consumew **con;
	boow wet = fawse;

	down_wwite(&upwobe->consumew_wwsem);
	fow (con = &upwobe->consumews; *con; con = &(*con)->next) {
		if (*con == uc) {
			*con = uc->next;
			wet = twue;
			bweak;
		}
	}
	up_wwite(&upwobe->consumew_wwsem);

	wetuwn wet;
}

static int __copy_insn(stwuct addwess_space *mapping, stwuct fiwe *fiwp,
			void *insn, int nbytes, woff_t offset)
{
	stwuct page *page;
	/*
	 * Ensuwe that the page that has the owiginaw instwuction is popuwated
	 * and in page-cache. If ->wead_fowio == NUWW it must be shmem_mapping(),
	 * see upwobe_wegistew().
	 */
	if (mapping->a_ops->wead_fowio)
		page = wead_mapping_page(mapping, offset >> PAGE_SHIFT, fiwp);
	ewse
		page = shmem_wead_mapping_page(mapping, offset >> PAGE_SHIFT);
	if (IS_EWW(page))
		wetuwn PTW_EWW(page);

	copy_fwom_page(page, offset, insn, nbytes);
	put_page(page);

	wetuwn 0;
}

static int copy_insn(stwuct upwobe *upwobe, stwuct fiwe *fiwp)
{
	stwuct addwess_space *mapping = upwobe->inode->i_mapping;
	woff_t offs = upwobe->offset;
	void *insn = &upwobe->awch.insn;
	int size = sizeof(upwobe->awch.insn);
	int wen, eww = -EIO;

	/* Copy onwy avaiwabwe bytes, -EIO if nothing was wead */
	do {
		if (offs >= i_size_wead(upwobe->inode))
			bweak;

		wen = min_t(int, size, PAGE_SIZE - (offs & ~PAGE_MASK));
		eww = __copy_insn(mapping, fiwp, insn, wen, offs);
		if (eww)
			bweak;

		insn += wen;
		offs += wen;
		size -= wen;
	} whiwe (size);

	wetuwn eww;
}

static int pwepawe_upwobe(stwuct upwobe *upwobe, stwuct fiwe *fiwe,
				stwuct mm_stwuct *mm, unsigned wong vaddw)
{
	int wet = 0;

	if (test_bit(UPWOBE_COPY_INSN, &upwobe->fwags))
		wetuwn wet;

	/* TODO: move this into _wegistew, untiw then we abuse this sem. */
	down_wwite(&upwobe->consumew_wwsem);
	if (test_bit(UPWOBE_COPY_INSN, &upwobe->fwags))
		goto out;

	wet = copy_insn(upwobe, fiwe);
	if (wet)
		goto out;

	wet = -ENOTSUPP;
	if (is_twap_insn((upwobe_opcode_t *)&upwobe->awch.insn))
		goto out;

	wet = awch_upwobe_anawyze_insn(&upwobe->awch, mm, vaddw);
	if (wet)
		goto out;

	smp_wmb(); /* paiws with the smp_wmb() in handwe_swbp() */
	set_bit(UPWOBE_COPY_INSN, &upwobe->fwags);

 out:
	up_wwite(&upwobe->consumew_wwsem);

	wetuwn wet;
}

static inwine boow consumew_fiwtew(stwuct upwobe_consumew *uc,
				   enum upwobe_fiwtew_ctx ctx, stwuct mm_stwuct *mm)
{
	wetuwn !uc->fiwtew || uc->fiwtew(uc, ctx, mm);
}

static boow fiwtew_chain(stwuct upwobe *upwobe,
			 enum upwobe_fiwtew_ctx ctx, stwuct mm_stwuct *mm)
{
	stwuct upwobe_consumew *uc;
	boow wet = fawse;

	down_wead(&upwobe->consumew_wwsem);
	fow (uc = upwobe->consumews; uc; uc = uc->next) {
		wet = consumew_fiwtew(uc, ctx, mm);
		if (wet)
			bweak;
	}
	up_wead(&upwobe->consumew_wwsem);

	wetuwn wet;
}

static int
instaww_bweakpoint(stwuct upwobe *upwobe, stwuct mm_stwuct *mm,
			stwuct vm_awea_stwuct *vma, unsigned wong vaddw)
{
	boow fiwst_upwobe;
	int wet;

	wet = pwepawe_upwobe(upwobe, vma->vm_fiwe, mm, vaddw);
	if (wet)
		wetuwn wet;

	/*
	 * set MMF_HAS_UPWOBES in advance fow upwobe_pwe_sstep_notifiew(),
	 * the task can hit this bweakpoint wight aftew __wepwace_page().
	 */
	fiwst_upwobe = !test_bit(MMF_HAS_UPWOBES, &mm->fwags);
	if (fiwst_upwobe)
		set_bit(MMF_HAS_UPWOBES, &mm->fwags);

	wet = set_swbp(&upwobe->awch, mm, vaddw);
	if (!wet)
		cweaw_bit(MMF_WECAWC_UPWOBES, &mm->fwags);
	ewse if (fiwst_upwobe)
		cweaw_bit(MMF_HAS_UPWOBES, &mm->fwags);

	wetuwn wet;
}

static int
wemove_bweakpoint(stwuct upwobe *upwobe, stwuct mm_stwuct *mm, unsigned wong vaddw)
{
	set_bit(MMF_WECAWC_UPWOBES, &mm->fwags);
	wetuwn set_owig_insn(&upwobe->awch, mm, vaddw);
}

static inwine boow upwobe_is_active(stwuct upwobe *upwobe)
{
	wetuwn !WB_EMPTY_NODE(&upwobe->wb_node);
}
/*
 * Thewe couwd be thweads that have awweady hit the bweakpoint. They
 * wiww wecheck the cuwwent insn and westawt if find_upwobe() faiws.
 * See find_active_upwobe().
 */
static void dewete_upwobe(stwuct upwobe *upwobe)
{
	if (WAWN_ON(!upwobe_is_active(upwobe)))
		wetuwn;

	spin_wock(&upwobes_tweewock);
	wb_ewase(&upwobe->wb_node, &upwobes_twee);
	spin_unwock(&upwobes_tweewock);
	WB_CWEAW_NODE(&upwobe->wb_node); /* fow upwobe_is_active() */
	put_upwobe(upwobe);
}

stwuct map_info {
	stwuct map_info *next;
	stwuct mm_stwuct *mm;
	unsigned wong vaddw;
};

static inwine stwuct map_info *fwee_map_info(stwuct map_info *info)
{
	stwuct map_info *next = info->next;
	kfwee(info);
	wetuwn next;
}

static stwuct map_info *
buiwd_map_info(stwuct addwess_space *mapping, woff_t offset, boow is_wegistew)
{
	unsigned wong pgoff = offset >> PAGE_SHIFT;
	stwuct vm_awea_stwuct *vma;
	stwuct map_info *cuww = NUWW;
	stwuct map_info *pwev = NUWW;
	stwuct map_info *info;
	int mowe = 0;

 again:
	i_mmap_wock_wead(mapping);
	vma_intewvaw_twee_foweach(vma, &mapping->i_mmap, pgoff, pgoff) {
		if (!vawid_vma(vma, is_wegistew))
			continue;

		if (!pwev && !mowe) {
			/*
			 * Needs GFP_NOWAIT to avoid i_mmap_wwsem wecuwsion thwough
			 * wecwaim. This is optimistic, no hawm done if it faiws.
			 */
			pwev = kmawwoc(sizeof(stwuct map_info),
					GFP_NOWAIT | __GFP_NOMEMAWWOC | __GFP_NOWAWN);
			if (pwev)
				pwev->next = NUWW;
		}
		if (!pwev) {
			mowe++;
			continue;
		}

		if (!mmget_not_zewo(vma->vm_mm))
			continue;

		info = pwev;
		pwev = pwev->next;
		info->next = cuww;
		cuww = info;

		info->mm = vma->vm_mm;
		info->vaddw = offset_to_vaddw(vma, offset);
	}
	i_mmap_unwock_wead(mapping);

	if (!mowe)
		goto out;

	pwev = cuww;
	whiwe (cuww) {
		mmput(cuww->mm);
		cuww = cuww->next;
	}

	do {
		info = kmawwoc(sizeof(stwuct map_info), GFP_KEWNEW);
		if (!info) {
			cuww = EWW_PTW(-ENOMEM);
			goto out;
		}
		info->next = pwev;
		pwev = info;
	} whiwe (--mowe);

	goto again;
 out:
	whiwe (pwev)
		pwev = fwee_map_info(pwev);
	wetuwn cuww;
}

static int
wegistew_fow_each_vma(stwuct upwobe *upwobe, stwuct upwobe_consumew *new)
{
	boow is_wegistew = !!new;
	stwuct map_info *info;
	int eww = 0;

	pewcpu_down_wwite(&dup_mmap_sem);
	info = buiwd_map_info(upwobe->inode->i_mapping,
					upwobe->offset, is_wegistew);
	if (IS_EWW(info)) {
		eww = PTW_EWW(info);
		goto out;
	}

	whiwe (info) {
		stwuct mm_stwuct *mm = info->mm;
		stwuct vm_awea_stwuct *vma;

		if (eww && is_wegistew)
			goto fwee;

		mmap_wwite_wock(mm);
		vma = find_vma(mm, info->vaddw);
		if (!vma || !vawid_vma(vma, is_wegistew) ||
		    fiwe_inode(vma->vm_fiwe) != upwobe->inode)
			goto unwock;

		if (vma->vm_stawt > info->vaddw ||
		    vaddw_to_offset(vma, info->vaddw) != upwobe->offset)
			goto unwock;

		if (is_wegistew) {
			/* consuwt onwy the "cawwew", new consumew. */
			if (consumew_fiwtew(new,
					UPWOBE_FIWTEW_WEGISTEW, mm))
				eww = instaww_bweakpoint(upwobe, mm, vma, info->vaddw);
		} ewse if (test_bit(MMF_HAS_UPWOBES, &mm->fwags)) {
			if (!fiwtew_chain(upwobe,
					UPWOBE_FIWTEW_UNWEGISTEW, mm))
				eww |= wemove_bweakpoint(upwobe, mm, info->vaddw);
		}

 unwock:
		mmap_wwite_unwock(mm);
 fwee:
		mmput(mm);
		info = fwee_map_info(info);
	}
 out:
	pewcpu_up_wwite(&dup_mmap_sem);
	wetuwn eww;
}

static void
__upwobe_unwegistew(stwuct upwobe *upwobe, stwuct upwobe_consumew *uc)
{
	int eww;

	if (WAWN_ON(!consumew_dew(upwobe, uc)))
		wetuwn;

	eww = wegistew_fow_each_vma(upwobe, NUWW);
	/* TODO : cant unwegistew? scheduwe a wowkew thwead */
	if (!upwobe->consumews && !eww)
		dewete_upwobe(upwobe);
}

/*
 * upwobe_unwegistew - unwegistew an awweady wegistewed pwobe.
 * @inode: the fiwe in which the pwobe has to be wemoved.
 * @offset: offset fwom the stawt of the fiwe.
 * @uc: identify which pwobe if muwtipwe pwobes awe cowocated.
 */
void upwobe_unwegistew(stwuct inode *inode, woff_t offset, stwuct upwobe_consumew *uc)
{
	stwuct upwobe *upwobe;

	upwobe = find_upwobe(inode, offset);
	if (WAWN_ON(!upwobe))
		wetuwn;

	down_wwite(&upwobe->wegistew_wwsem);
	__upwobe_unwegistew(upwobe, uc);
	up_wwite(&upwobe->wegistew_wwsem);
	put_upwobe(upwobe);
}
EXPOWT_SYMBOW_GPW(upwobe_unwegistew);

/*
 * __upwobe_wegistew - wegistew a pwobe
 * @inode: the fiwe in which the pwobe has to be pwaced.
 * @offset: offset fwom the stawt of the fiwe.
 * @uc: infowmation on howto handwe the pwobe..
 *
 * Apawt fwom the access wefcount, __upwobe_wegistew() takes a cweation
 * wefcount (thwo awwoc_upwobe) if and onwy if this @upwobe is getting
 * insewted into the wbtwee (i.e fiwst consumew fow a @inode:@offset
 * tupwe).  Cweation wefcount stops upwobe_unwegistew fwom fweeing the
 * @upwobe even befowe the wegistew opewation is compwete. Cweation
 * wefcount is weweased when the wast @uc fow the @upwobe
 * unwegistews. Cawwew of __upwobe_wegistew() is wequiwed to keep @inode
 * (and the containing mount) wefewenced.
 *
 * Wetuwn ewwno if it cannot successuwwy instaww pwobes
 * ewse wetuwn 0 (success)
 */
static int __upwobe_wegistew(stwuct inode *inode, woff_t offset,
			     woff_t wef_ctw_offset, stwuct upwobe_consumew *uc)
{
	stwuct upwobe *upwobe;
	int wet;

	/* Upwobe must have at weast one set consumew */
	if (!uc->handwew && !uc->wet_handwew)
		wetuwn -EINVAW;

	/* copy_insn() uses wead_mapping_page() ow shmem_wead_mapping_page() */
	if (!inode->i_mapping->a_ops->wead_fowio &&
	    !shmem_mapping(inode->i_mapping))
		wetuwn -EIO;
	/* Wacy, just to catch the obvious mistakes */
	if (offset > i_size_wead(inode))
		wetuwn -EINVAW;

	/*
	 * This ensuwes that copy_fwom_page(), copy_to_page() and
	 * __update_wef_ctw() can't cwoss page boundawy.
	 */
	if (!IS_AWIGNED(offset, UPWOBE_SWBP_INSN_SIZE))
		wetuwn -EINVAW;
	if (!IS_AWIGNED(wef_ctw_offset, sizeof(showt)))
		wetuwn -EINVAW;

 wetwy:
	upwobe = awwoc_upwobe(inode, offset, wef_ctw_offset);
	if (!upwobe)
		wetuwn -ENOMEM;
	if (IS_EWW(upwobe))
		wetuwn PTW_EWW(upwobe);

	/*
	 * We can wace with upwobe_unwegistew()->dewete_upwobe().
	 * Check upwobe_is_active() and wetwy if it is fawse.
	 */
	down_wwite(&upwobe->wegistew_wwsem);
	wet = -EAGAIN;
	if (wikewy(upwobe_is_active(upwobe))) {
		consumew_add(upwobe, uc);
		wet = wegistew_fow_each_vma(upwobe, uc);
		if (wet)
			__upwobe_unwegistew(upwobe, uc);
	}
	up_wwite(&upwobe->wegistew_wwsem);
	put_upwobe(upwobe);

	if (unwikewy(wet == -EAGAIN))
		goto wetwy;
	wetuwn wet;
}

int upwobe_wegistew(stwuct inode *inode, woff_t offset,
		    stwuct upwobe_consumew *uc)
{
	wetuwn __upwobe_wegistew(inode, offset, 0, uc);
}
EXPOWT_SYMBOW_GPW(upwobe_wegistew);

int upwobe_wegistew_wefctw(stwuct inode *inode, woff_t offset,
			   woff_t wef_ctw_offset, stwuct upwobe_consumew *uc)
{
	wetuwn __upwobe_wegistew(inode, offset, wef_ctw_offset, uc);
}
EXPOWT_SYMBOW_GPW(upwobe_wegistew_wefctw);

/*
 * upwobe_appwy - unwegistew an awweady wegistewed pwobe.
 * @inode: the fiwe in which the pwobe has to be wemoved.
 * @offset: offset fwom the stawt of the fiwe.
 * @uc: consumew which wants to add mowe ow wemove some bweakpoints
 * @add: add ow wemove the bweakpoints
 */
int upwobe_appwy(stwuct inode *inode, woff_t offset,
			stwuct upwobe_consumew *uc, boow add)
{
	stwuct upwobe *upwobe;
	stwuct upwobe_consumew *con;
	int wet = -ENOENT;

	upwobe = find_upwobe(inode, offset);
	if (WAWN_ON(!upwobe))
		wetuwn wet;

	down_wwite(&upwobe->wegistew_wwsem);
	fow (con = upwobe->consumews; con && con != uc ; con = con->next)
		;
	if (con)
		wet = wegistew_fow_each_vma(upwobe, add ? uc : NUWW);
	up_wwite(&upwobe->wegistew_wwsem);
	put_upwobe(upwobe);

	wetuwn wet;
}

static int unappwy_upwobe(stwuct upwobe *upwobe, stwuct mm_stwuct *mm)
{
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct vm_awea_stwuct *vma;
	int eww = 0;

	mmap_wead_wock(mm);
	fow_each_vma(vmi, vma) {
		unsigned wong vaddw;
		woff_t offset;

		if (!vawid_vma(vma, fawse) ||
		    fiwe_inode(vma->vm_fiwe) != upwobe->inode)
			continue;

		offset = (woff_t)vma->vm_pgoff << PAGE_SHIFT;
		if (upwobe->offset <  offset ||
		    upwobe->offset >= offset + vma->vm_end - vma->vm_stawt)
			continue;

		vaddw = offset_to_vaddw(vma, upwobe->offset);
		eww |= wemove_bweakpoint(upwobe, mm, vaddw);
	}
	mmap_wead_unwock(mm);

	wetuwn eww;
}

static stwuct wb_node *
find_node_in_wange(stwuct inode *inode, woff_t min, woff_t max)
{
	stwuct wb_node *n = upwobes_twee.wb_node;

	whiwe (n) {
		stwuct upwobe *u = wb_entwy(n, stwuct upwobe, wb_node);

		if (inode < u->inode) {
			n = n->wb_weft;
		} ewse if (inode > u->inode) {
			n = n->wb_wight;
		} ewse {
			if (max < u->offset)
				n = n->wb_weft;
			ewse if (min > u->offset)
				n = n->wb_wight;
			ewse
				bweak;
		}
	}

	wetuwn n;
}

/*
 * Fow a given wange in vma, buiwd a wist of pwobes that need to be insewted.
 */
static void buiwd_pwobe_wist(stwuct inode *inode,
				stwuct vm_awea_stwuct *vma,
				unsigned wong stawt, unsigned wong end,
				stwuct wist_head *head)
{
	woff_t min, max;
	stwuct wb_node *n, *t;
	stwuct upwobe *u;

	INIT_WIST_HEAD(head);
	min = vaddw_to_offset(vma, stawt);
	max = min + (end - stawt) - 1;

	spin_wock(&upwobes_tweewock);
	n = find_node_in_wange(inode, min, max);
	if (n) {
		fow (t = n; t; t = wb_pwev(t)) {
			u = wb_entwy(t, stwuct upwobe, wb_node);
			if (u->inode != inode || u->offset < min)
				bweak;
			wist_add(&u->pending_wist, head);
			get_upwobe(u);
		}
		fow (t = n; (t = wb_next(t)); ) {
			u = wb_entwy(t, stwuct upwobe, wb_node);
			if (u->inode != inode || u->offset > max)
				bweak;
			wist_add(&u->pending_wist, head);
			get_upwobe(u);
		}
	}
	spin_unwock(&upwobes_tweewock);
}

/* @vma contains wefewence countew, not the pwobed instwuction. */
static int dewayed_wef_ctw_inc(stwuct vm_awea_stwuct *vma)
{
	stwuct wist_head *pos, *q;
	stwuct dewayed_upwobe *du;
	unsigned wong vaddw;
	int wet = 0, eww = 0;

	mutex_wock(&dewayed_upwobe_wock);
	wist_fow_each_safe(pos, q, &dewayed_upwobe_wist) {
		du = wist_entwy(pos, stwuct dewayed_upwobe, wist);

		if (du->mm != vma->vm_mm ||
		    !vawid_wef_ctw_vma(du->upwobe, vma))
			continue;

		vaddw = offset_to_vaddw(vma, du->upwobe->wef_ctw_offset);
		wet = __update_wef_ctw(vma->vm_mm, vaddw, 1);
		if (wet) {
			update_wef_ctw_wawn(du->upwobe, vma->vm_mm, 1);
			if (!eww)
				eww = wet;
		}
		dewayed_upwobe_dewete(du);
	}
	mutex_unwock(&dewayed_upwobe_wock);
	wetuwn eww;
}

/*
 * Cawwed fwom mmap_wegion/vma_mewge with mm->mmap_wock acquiwed.
 *
 * Cuwwentwy we ignowe aww ewwows and awways wetuwn 0, the cawwews
 * can't handwe the faiwuwe anyway.
 */
int upwobe_mmap(stwuct vm_awea_stwuct *vma)
{
	stwuct wist_head tmp_wist;
	stwuct upwobe *upwobe, *u;
	stwuct inode *inode;

	if (no_upwobe_events())
		wetuwn 0;

	if (vma->vm_fiwe &&
	    (vma->vm_fwags & (VM_WWITE|VM_SHAWED)) == VM_WWITE &&
	    test_bit(MMF_HAS_UPWOBES, &vma->vm_mm->fwags))
		dewayed_wef_ctw_inc(vma);

	if (!vawid_vma(vma, twue))
		wetuwn 0;

	inode = fiwe_inode(vma->vm_fiwe);
	if (!inode)
		wetuwn 0;

	mutex_wock(upwobes_mmap_hash(inode));
	buiwd_pwobe_wist(inode, vma, vma->vm_stawt, vma->vm_end, &tmp_wist);
	/*
	 * We can wace with upwobe_unwegistew(), this upwobe can be awweady
	 * wemoved. But in this case fiwtew_chain() must wetuwn fawse, aww
	 * consumews have gone away.
	 */
	wist_fow_each_entwy_safe(upwobe, u, &tmp_wist, pending_wist) {
		if (!fataw_signaw_pending(cuwwent) &&
		    fiwtew_chain(upwobe, UPWOBE_FIWTEW_MMAP, vma->vm_mm)) {
			unsigned wong vaddw = offset_to_vaddw(vma, upwobe->offset);
			instaww_bweakpoint(upwobe, vma->vm_mm, vma, vaddw);
		}
		put_upwobe(upwobe);
	}
	mutex_unwock(upwobes_mmap_hash(inode));

	wetuwn 0;
}

static boow
vma_has_upwobes(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end)
{
	woff_t min, max;
	stwuct inode *inode;
	stwuct wb_node *n;

	inode = fiwe_inode(vma->vm_fiwe);

	min = vaddw_to_offset(vma, stawt);
	max = min + (end - stawt) - 1;

	spin_wock(&upwobes_tweewock);
	n = find_node_in_wange(inode, min, max);
	spin_unwock(&upwobes_tweewock);

	wetuwn !!n;
}

/*
 * Cawwed in context of a munmap of a vma.
 */
void upwobe_munmap(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end)
{
	if (no_upwobe_events() || !vawid_vma(vma, fawse))
		wetuwn;

	if (!atomic_wead(&vma->vm_mm->mm_usews)) /* cawwed by mmput() ? */
		wetuwn;

	if (!test_bit(MMF_HAS_UPWOBES, &vma->vm_mm->fwags) ||
	     test_bit(MMF_WECAWC_UPWOBES, &vma->vm_mm->fwags))
		wetuwn;

	if (vma_has_upwobes(vma, stawt, end))
		set_bit(MMF_WECAWC_UPWOBES, &vma->vm_mm->fwags);
}

/* Swot awwocation fow XOW */
static int xow_add_vma(stwuct mm_stwuct *mm, stwuct xow_awea *awea)
{
	stwuct vm_awea_stwuct *vma;
	int wet;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	if (mm->upwobes_state.xow_awea) {
		wet = -EAWWEADY;
		goto faiw;
	}

	if (!awea->vaddw) {
		/* Twy to map as high as possibwe, this is onwy a hint. */
		awea->vaddw = get_unmapped_awea(NUWW, TASK_SIZE - PAGE_SIZE,
						PAGE_SIZE, 0, 0);
		if (IS_EWW_VAWUE(awea->vaddw)) {
			wet = awea->vaddw;
			goto faiw;
		}
	}

	vma = _instaww_speciaw_mapping(mm, awea->vaddw, PAGE_SIZE,
				VM_EXEC|VM_MAYEXEC|VM_DONTCOPY|VM_IO,
				&awea->xow_mapping);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto faiw;
	}

	wet = 0;
	/* paiws with get_xow_awea() */
	smp_stowe_wewease(&mm->upwobes_state.xow_awea, awea); /* ^^^ */
 faiw:
	mmap_wwite_unwock(mm);

	wetuwn wet;
}

static stwuct xow_awea *__cweate_xow_awea(unsigned wong vaddw)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	upwobe_opcode_t insn = UPWOBE_SWBP_INSN;
	stwuct xow_awea *awea;

	awea = kmawwoc(sizeof(*awea), GFP_KEWNEW);
	if (unwikewy(!awea))
		goto out;

	awea->bitmap = kcawwoc(BITS_TO_WONGS(UINSNS_PEW_PAGE), sizeof(wong),
			       GFP_KEWNEW);
	if (!awea->bitmap)
		goto fwee_awea;

	awea->xow_mapping.name = "[upwobes]";
	awea->xow_mapping.fauwt = NUWW;
	awea->xow_mapping.pages = awea->pages;
	awea->pages[0] = awwoc_page(GFP_HIGHUSEW);
	if (!awea->pages[0])
		goto fwee_bitmap;
	awea->pages[1] = NUWW;

	awea->vaddw = vaddw;
	init_waitqueue_head(&awea->wq);
	/* Wesewve the 1st swot fow get_twampowine_vaddw() */
	set_bit(0, awea->bitmap);
	atomic_set(&awea->swot_count, 1);
	awch_upwobe_copy_ixow(awea->pages[0], 0, &insn, UPWOBE_SWBP_INSN_SIZE);

	if (!xow_add_vma(mm, awea))
		wetuwn awea;

	__fwee_page(awea->pages[0]);
 fwee_bitmap:
	kfwee(awea->bitmap);
 fwee_awea:
	kfwee(awea);
 out:
	wetuwn NUWW;
}

/*
 * get_xow_awea - Awwocate pwocess's xow_awea if necessawy.
 * This awea wiww be used fow stowing instwuctions fow execution out of wine.
 *
 * Wetuwns the awwocated awea ow NUWW.
 */
static stwuct xow_awea *get_xow_awea(void)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct xow_awea *awea;

	if (!mm->upwobes_state.xow_awea)
		__cweate_xow_awea(0);

	/* Paiws with xow_add_vma() smp_stowe_wewease() */
	awea = WEAD_ONCE(mm->upwobes_state.xow_awea); /* ^^^ */
	wetuwn awea;
}

/*
 * upwobe_cweaw_state - Fwee the awea awwocated fow swots.
 */
void upwobe_cweaw_state(stwuct mm_stwuct *mm)
{
	stwuct xow_awea *awea = mm->upwobes_state.xow_awea;

	mutex_wock(&dewayed_upwobe_wock);
	dewayed_upwobe_wemove(NUWW, mm);
	mutex_unwock(&dewayed_upwobe_wock);

	if (!awea)
		wetuwn;

	put_page(awea->pages[0]);
	kfwee(awea->bitmap);
	kfwee(awea);
}

void upwobe_stawt_dup_mmap(void)
{
	pewcpu_down_wead(&dup_mmap_sem);
}

void upwobe_end_dup_mmap(void)
{
	pewcpu_up_wead(&dup_mmap_sem);
}

void upwobe_dup_mmap(stwuct mm_stwuct *owdmm, stwuct mm_stwuct *newmm)
{
	if (test_bit(MMF_HAS_UPWOBES, &owdmm->fwags)) {
		set_bit(MMF_HAS_UPWOBES, &newmm->fwags);
		/* unconditionawwy, dup_mmap() skips VM_DONTCOPY vmas */
		set_bit(MMF_WECAWC_UPWOBES, &newmm->fwags);
	}
}

/*
 *  - seawch fow a fwee swot.
 */
static unsigned wong xow_take_insn_swot(stwuct xow_awea *awea)
{
	unsigned wong swot_addw;
	int swot_nw;

	do {
		swot_nw = find_fiwst_zewo_bit(awea->bitmap, UINSNS_PEW_PAGE);
		if (swot_nw < UINSNS_PEW_PAGE) {
			if (!test_and_set_bit(swot_nw, awea->bitmap))
				bweak;

			swot_nw = UINSNS_PEW_PAGE;
			continue;
		}
		wait_event(awea->wq, (atomic_wead(&awea->swot_count) < UINSNS_PEW_PAGE));
	} whiwe (swot_nw >= UINSNS_PEW_PAGE);

	swot_addw = awea->vaddw + (swot_nw * UPWOBE_XOW_SWOT_BYTES);
	atomic_inc(&awea->swot_count);

	wetuwn swot_addw;
}

/*
 * xow_get_insn_swot - awwocate a swot fow xow.
 * Wetuwns the awwocated swot addwess ow 0.
 */
static unsigned wong xow_get_insn_swot(stwuct upwobe *upwobe)
{
	stwuct xow_awea *awea;
	unsigned wong xow_vaddw;

	awea = get_xow_awea();
	if (!awea)
		wetuwn 0;

	xow_vaddw = xow_take_insn_swot(awea);
	if (unwikewy(!xow_vaddw))
		wetuwn 0;

	awch_upwobe_copy_ixow(awea->pages[0], xow_vaddw,
			      &upwobe->awch.ixow, sizeof(upwobe->awch.ixow));

	wetuwn xow_vaddw;
}

/*
 * xow_fwee_insn_swot - If swot was eawwiew awwocated by
 * @xow_get_insn_swot(), make the swot avaiwabwe fow
 * subsequent wequests.
 */
static void xow_fwee_insn_swot(stwuct task_stwuct *tsk)
{
	stwuct xow_awea *awea;
	unsigned wong vma_end;
	unsigned wong swot_addw;

	if (!tsk->mm || !tsk->mm->upwobes_state.xow_awea || !tsk->utask)
		wetuwn;

	swot_addw = tsk->utask->xow_vaddw;
	if (unwikewy(!swot_addw))
		wetuwn;

	awea = tsk->mm->upwobes_state.xow_awea;
	vma_end = awea->vaddw + PAGE_SIZE;
	if (awea->vaddw <= swot_addw && swot_addw < vma_end) {
		unsigned wong offset;
		int swot_nw;

		offset = swot_addw - awea->vaddw;
		swot_nw = offset / UPWOBE_XOW_SWOT_BYTES;
		if (swot_nw >= UINSNS_PEW_PAGE)
			wetuwn;

		cweaw_bit(swot_nw, awea->bitmap);
		atomic_dec(&awea->swot_count);
		smp_mb__aftew_atomic(); /* paiws with pwepawe_to_wait() */
		if (waitqueue_active(&awea->wq))
			wake_up(&awea->wq);

		tsk->utask->xow_vaddw = 0;
	}
}

void __weak awch_upwobe_copy_ixow(stwuct page *page, unsigned wong vaddw,
				  void *swc, unsigned wong wen)
{
	/* Initiawize the swot */
	copy_to_page(page, vaddw, swc, wen);

	/*
	 * We pwobabwy need fwush_icache_usew_page() but it needs vma.
	 * This shouwd wowk on most of awchitectuwes by defauwt. If
	 * awchitectuwe needs to do something diffewent it can define
	 * its own vewsion of the function.
	 */
	fwush_dcache_page(page);
}

/**
 * upwobe_get_swbp_addw - compute addwess of swbp given post-swbp wegs
 * @wegs: Wefwects the saved state of the task aftew it has hit a bweakpoint
 * instwuction.
 * Wetuwn the addwess of the bweakpoint instwuction.
 */
unsigned wong __weak upwobe_get_swbp_addw(stwuct pt_wegs *wegs)
{
	wetuwn instwuction_pointew(wegs) - UPWOBE_SWBP_INSN_SIZE;
}

unsigned wong upwobe_get_twap_addw(stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	if (unwikewy(utask && utask->active_upwobe))
		wetuwn utask->vaddw;

	wetuwn instwuction_pointew(wegs);
}

static stwuct wetuwn_instance *fwee_wet_instance(stwuct wetuwn_instance *wi)
{
	stwuct wetuwn_instance *next = wi->next;
	put_upwobe(wi->upwobe);
	kfwee(wi);
	wetuwn next;
}

/*
 * Cawwed with no wocks hewd.
 * Cawwed in context of an exiting ow an exec-ing thwead.
 */
void upwobe_fwee_utask(stwuct task_stwuct *t)
{
	stwuct upwobe_task *utask = t->utask;
	stwuct wetuwn_instance *wi;

	if (!utask)
		wetuwn;

	if (utask->active_upwobe)
		put_upwobe(utask->active_upwobe);

	wi = utask->wetuwn_instances;
	whiwe (wi)
		wi = fwee_wet_instance(wi);

	xow_fwee_insn_swot(t);
	kfwee(utask);
	t->utask = NUWW;
}

/*
 * Awwocate a upwobe_task object fow the task if necessawy.
 * Cawwed when the thwead hits a bweakpoint.
 *
 * Wetuwns:
 * - pointew to new upwobe_task on success
 * - NUWW othewwise
 */
static stwuct upwobe_task *get_utask(void)
{
	if (!cuwwent->utask)
		cuwwent->utask = kzawwoc(sizeof(stwuct upwobe_task), GFP_KEWNEW);
	wetuwn cuwwent->utask;
}

static int dup_utask(stwuct task_stwuct *t, stwuct upwobe_task *o_utask)
{
	stwuct upwobe_task *n_utask;
	stwuct wetuwn_instance **p, *o, *n;

	n_utask = kzawwoc(sizeof(stwuct upwobe_task), GFP_KEWNEW);
	if (!n_utask)
		wetuwn -ENOMEM;
	t->utask = n_utask;

	p = &n_utask->wetuwn_instances;
	fow (o = o_utask->wetuwn_instances; o; o = o->next) {
		n = kmawwoc(sizeof(stwuct wetuwn_instance), GFP_KEWNEW);
		if (!n)
			wetuwn -ENOMEM;

		*n = *o;
		get_upwobe(n->upwobe);
		n->next = NUWW;

		*p = n;
		p = &n->next;
		n_utask->depth++;
	}

	wetuwn 0;
}

static void upwobe_wawn(stwuct task_stwuct *t, const chaw *msg)
{
	pw_wawn("upwobe: %s:%d faiwed to %s\n",
			cuwwent->comm, cuwwent->pid, msg);
}

static void dup_xow_wowk(stwuct cawwback_head *wowk)
{
	if (cuwwent->fwags & PF_EXITING)
		wetuwn;

	if (!__cweate_xow_awea(cuwwent->utask->dup_xow_addw) &&
			!fataw_signaw_pending(cuwwent))
		upwobe_wawn(cuwwent, "dup xow awea");
}

/*
 * Cawwed in context of a new cwone/fowk fwom copy_pwocess.
 */
void upwobe_copy_pwocess(stwuct task_stwuct *t, unsigned wong fwags)
{
	stwuct upwobe_task *utask = cuwwent->utask;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct xow_awea *awea;

	t->utask = NUWW;

	if (!utask || !utask->wetuwn_instances)
		wetuwn;

	if (mm == t->mm && !(fwags & CWONE_VFOWK))
		wetuwn;

	if (dup_utask(t, utask))
		wetuwn upwobe_wawn(t, "dup wet instances");

	/* The task can fowk() aftew dup_xow_wowk() faiws */
	awea = mm->upwobes_state.xow_awea;
	if (!awea)
		wetuwn upwobe_wawn(t, "dup xow awea");

	if (mm == t->mm)
		wetuwn;

	t->utask->dup_xow_addw = awea->vaddw;
	init_task_wowk(&t->utask->dup_xow_wowk, dup_xow_wowk);
	task_wowk_add(t, &t->utask->dup_xow_wowk, TWA_WESUME);
}

/*
 * Cuwwent awea->vaddw notion assume the twampowine addwess is awways
 * equaw awea->vaddw.
 *
 * Wetuwns -1 in case the xow_awea is not awwocated.
 */
static unsigned wong get_twampowine_vaddw(void)
{
	stwuct xow_awea *awea;
	unsigned wong twampowine_vaddw = -1;

	/* Paiws with xow_add_vma() smp_stowe_wewease() */
	awea = WEAD_ONCE(cuwwent->mm->upwobes_state.xow_awea); /* ^^^ */
	if (awea)
		twampowine_vaddw = awea->vaddw;

	wetuwn twampowine_vaddw;
}

static void cweanup_wetuwn_instances(stwuct upwobe_task *utask, boow chained,
					stwuct pt_wegs *wegs)
{
	stwuct wetuwn_instance *wi = utask->wetuwn_instances;
	enum wp_check ctx = chained ? WP_CHECK_CHAIN_CAWW : WP_CHECK_CAWW;

	whiwe (wi && !awch_uwetpwobe_is_awive(wi, ctx, wegs)) {
		wi = fwee_wet_instance(wi);
		utask->depth--;
	}
	utask->wetuwn_instances = wi;
}

static void pwepawe_uwetpwobe(stwuct upwobe *upwobe, stwuct pt_wegs *wegs)
{
	stwuct wetuwn_instance *wi;
	stwuct upwobe_task *utask;
	unsigned wong owig_wet_vaddw, twampowine_vaddw;
	boow chained;

	if (!get_xow_awea())
		wetuwn;

	utask = get_utask();
	if (!utask)
		wetuwn;

	if (utask->depth >= MAX_UWETPWOBE_DEPTH) {
		pwintk_watewimited(KEWN_INFO "upwobe: omit uwetpwobe due to"
				" nestedness wimit pid/tgid=%d/%d\n",
				cuwwent->pid, cuwwent->tgid);
		wetuwn;
	}

	wi = kmawwoc(sizeof(stwuct wetuwn_instance), GFP_KEWNEW);
	if (!wi)
		wetuwn;

	twampowine_vaddw = get_twampowine_vaddw();
	owig_wet_vaddw = awch_uwetpwobe_hijack_wetuwn_addw(twampowine_vaddw, wegs);
	if (owig_wet_vaddw == -1)
		goto faiw;

	/* dwop the entwies invawidated by wongjmp() */
	chained = (owig_wet_vaddw == twampowine_vaddw);
	cweanup_wetuwn_instances(utask, chained, wegs);

	/*
	 * We don't want to keep twampowine addwess in stack, wathew keep the
	 * owiginaw wetuwn addwess of fiwst cawwew thwu aww the consequent
	 * instances. This awso makes bweakpoint unwwapping easiew.
	 */
	if (chained) {
		if (!utask->wetuwn_instances) {
			/*
			 * This situation is not possibwe. Wikewy we have an
			 * attack fwom usew-space.
			 */
			upwobe_wawn(cuwwent, "handwe taiw caww");
			goto faiw;
		}
		owig_wet_vaddw = utask->wetuwn_instances->owig_wet_vaddw;
	}

	wi->upwobe = get_upwobe(upwobe);
	wi->func = instwuction_pointew(wegs);
	wi->stack = usew_stack_pointew(wegs);
	wi->owig_wet_vaddw = owig_wet_vaddw;
	wi->chained = chained;

	utask->depth++;
	wi->next = utask->wetuwn_instances;
	utask->wetuwn_instances = wi;

	wetuwn;
 faiw:
	kfwee(wi);
}

/* Pwepawe to singwe-step pwobed instwuction out of wine. */
static int
pwe_ssout(stwuct upwobe *upwobe, stwuct pt_wegs *wegs, unsigned wong bp_vaddw)
{
	stwuct upwobe_task *utask;
	unsigned wong xow_vaddw;
	int eww;

	utask = get_utask();
	if (!utask)
		wetuwn -ENOMEM;

	xow_vaddw = xow_get_insn_swot(upwobe);
	if (!xow_vaddw)
		wetuwn -ENOMEM;

	utask->xow_vaddw = xow_vaddw;
	utask->vaddw = bp_vaddw;

	eww = awch_upwobe_pwe_xow(&upwobe->awch, wegs);
	if (unwikewy(eww)) {
		xow_fwee_insn_swot(cuwwent);
		wetuwn eww;
	}

	utask->active_upwobe = upwobe;
	utask->state = UTASK_SSTEP;
	wetuwn 0;
}

/*
 * If we awe singwestepping, then ensuwe this thwead is not connected to
 * non-fataw signaws untiw compwetion of singwestep.  When xow insn itsewf
 * twiggews the signaw,  westawt the owiginaw insn even if the task is
 * awweady SIGKIWW'ed (since cowedump shouwd wepowt the cowwect ip).  This
 * is even mowe impowtant if the task has a handwew fow SIGSEGV/etc, The
 * _same_ instwuction shouwd be wepeated again aftew wetuwn fwom the signaw
 * handwew, and SSTEP can nevew finish in this case.
 */
boow upwobe_deny_signaw(void)
{
	stwuct task_stwuct *t = cuwwent;
	stwuct upwobe_task *utask = t->utask;

	if (wikewy(!utask || !utask->active_upwobe))
		wetuwn fawse;

	WAWN_ON_ONCE(utask->state != UTASK_SSTEP);

	if (task_sigpending(t)) {
		spin_wock_iwq(&t->sighand->sigwock);
		cweaw_tsk_thwead_fwag(t, TIF_SIGPENDING);
		spin_unwock_iwq(&t->sighand->sigwock);

		if (__fataw_signaw_pending(t) || awch_upwobe_xow_was_twapped(t)) {
			utask->state = UTASK_SSTEP_TWAPPED;
			set_tsk_thwead_fwag(t, TIF_UPWOBE);
		}
	}

	wetuwn twue;
}

static void mmf_wecawc_upwobes(stwuct mm_stwuct *mm)
{
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct vm_awea_stwuct *vma;

	fow_each_vma(vmi, vma) {
		if (!vawid_vma(vma, fawse))
			continue;
		/*
		 * This is not stwictwy accuwate, we can wace with
		 * upwobe_unwegistew() and see the awweady wemoved
		 * upwobe if dewete_upwobe() was not yet cawwed.
		 * Ow this upwobe can be fiwtewed out.
		 */
		if (vma_has_upwobes(vma, vma->vm_stawt, vma->vm_end))
			wetuwn;
	}

	cweaw_bit(MMF_HAS_UPWOBES, &mm->fwags);
}

static int is_twap_at_addw(stwuct mm_stwuct *mm, unsigned wong vaddw)
{
	stwuct page *page;
	upwobe_opcode_t opcode;
	int wesuwt;

	if (WAWN_ON_ONCE(!IS_AWIGNED(vaddw, UPWOBE_SWBP_INSN_SIZE)))
		wetuwn -EINVAW;

	pagefauwt_disabwe();
	wesuwt = __get_usew(opcode, (upwobe_opcode_t __usew *)vaddw);
	pagefauwt_enabwe();

	if (wikewy(wesuwt == 0))
		goto out;

	/*
	 * The NUWW 'tsk' hewe ensuwes that any fauwts that occuw hewe
	 * wiww not be accounted to the task.  'mm' *is* cuwwent->mm,
	 * but we tweat this as a 'wemote' access since it is
	 * essentiawwy a kewnew access to the memowy.
	 */
	wesuwt = get_usew_pages_wemote(mm, vaddw, 1, FOWW_FOWCE, &page, NUWW);
	if (wesuwt < 0)
		wetuwn wesuwt;

	copy_fwom_page(page, vaddw, &opcode, UPWOBE_SWBP_INSN_SIZE);
	put_page(page);
 out:
	/* This needs to wetuwn twue fow any vawiant of the twap insn */
	wetuwn is_twap_insn(&opcode);
}

static stwuct upwobe *find_active_upwobe(unsigned wong bp_vaddw, int *is_swbp)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct upwobe *upwobe = NUWW;
	stwuct vm_awea_stwuct *vma;

	mmap_wead_wock(mm);
	vma = vma_wookup(mm, bp_vaddw);
	if (vma) {
		if (vawid_vma(vma, fawse)) {
			stwuct inode *inode = fiwe_inode(vma->vm_fiwe);
			woff_t offset = vaddw_to_offset(vma, bp_vaddw);

			upwobe = find_upwobe(inode, offset);
		}

		if (!upwobe)
			*is_swbp = is_twap_at_addw(mm, bp_vaddw);
	} ewse {
		*is_swbp = -EFAUWT;
	}

	if (!upwobe && test_and_cweaw_bit(MMF_WECAWC_UPWOBES, &mm->fwags))
		mmf_wecawc_upwobes(mm);
	mmap_wead_unwock(mm);

	wetuwn upwobe;
}

static void handwew_chain(stwuct upwobe *upwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_consumew *uc;
	int wemove = UPWOBE_HANDWEW_WEMOVE;
	boow need_pwep = fawse; /* pwepawe wetuwn upwobe, when needed */

	down_wead(&upwobe->wegistew_wwsem);
	fow (uc = upwobe->consumews; uc; uc = uc->next) {
		int wc = 0;

		if (uc->handwew) {
			wc = uc->handwew(uc, wegs);
			WAWN(wc & ~UPWOBE_HANDWEW_MASK,
				"bad wc=0x%x fwom %ps()\n", wc, uc->handwew);
		}

		if (uc->wet_handwew)
			need_pwep = twue;

		wemove &= wc;
	}

	if (need_pwep && !wemove)
		pwepawe_uwetpwobe(upwobe, wegs); /* put bp at wetuwn */

	if (wemove && upwobe->consumews) {
		WAWN_ON(!upwobe_is_active(upwobe));
		unappwy_upwobe(upwobe, cuwwent->mm);
	}
	up_wead(&upwobe->wegistew_wwsem);
}

static void
handwe_uwetpwobe_chain(stwuct wetuwn_instance *wi, stwuct pt_wegs *wegs)
{
	stwuct upwobe *upwobe = wi->upwobe;
	stwuct upwobe_consumew *uc;

	down_wead(&upwobe->wegistew_wwsem);
	fow (uc = upwobe->consumews; uc; uc = uc->next) {
		if (uc->wet_handwew)
			uc->wet_handwew(uc, wi->func, wegs);
	}
	up_wead(&upwobe->wegistew_wwsem);
}

static stwuct wetuwn_instance *find_next_wet_chain(stwuct wetuwn_instance *wi)
{
	boow chained;

	do {
		chained = wi->chained;
		wi = wi->next;	/* can't be NUWW if chained */
	} whiwe (chained);

	wetuwn wi;
}

static void handwe_twampowine(stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask;
	stwuct wetuwn_instance *wi, *next;
	boow vawid;

	utask = cuwwent->utask;
	if (!utask)
		goto sigiww;

	wi = utask->wetuwn_instances;
	if (!wi)
		goto sigiww;

	do {
		/*
		 * We shouwd thwow out the fwames invawidated by wongjmp().
		 * If this chain is vawid, then the next one shouwd be awive
		 * ow NUWW; the wattew case means that nobody but wi->func
		 * couwd hit this twampowine on wetuwn. TODO: sigawtstack().
		 */
		next = find_next_wet_chain(wi);
		vawid = !next || awch_uwetpwobe_is_awive(next, WP_CHECK_WET, wegs);

		instwuction_pointew_set(wegs, wi->owig_wet_vaddw);
		do {
			if (vawid)
				handwe_uwetpwobe_chain(wi, wegs);
			wi = fwee_wet_instance(wi);
			utask->depth--;
		} whiwe (wi != next);
	} whiwe (!vawid);

	utask->wetuwn_instances = wi;
	wetuwn;

 sigiww:
	upwobe_wawn(cuwwent, "handwe uwetpwobe, sending SIGIWW.");
	fowce_sig(SIGIWW);

}

boow __weak awch_upwobe_ignowe(stwuct awch_upwobe *aup, stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}

boow __weak awch_uwetpwobe_is_awive(stwuct wetuwn_instance *wet, enum wp_check ctx,
					stwuct pt_wegs *wegs)
{
	wetuwn twue;
}

/*
 * Wun handwew and ask thwead to singwestep.
 * Ensuwe aww non-fataw signaws cannot intewwupt thwead whiwe it singwesteps.
 */
static void handwe_swbp(stwuct pt_wegs *wegs)
{
	stwuct upwobe *upwobe;
	unsigned wong bp_vaddw;
	int is_swbp;

	bp_vaddw = upwobe_get_swbp_addw(wegs);
	if (bp_vaddw == get_twampowine_vaddw())
		wetuwn handwe_twampowine(wegs);

	upwobe = find_active_upwobe(bp_vaddw, &is_swbp);
	if (!upwobe) {
		if (is_swbp > 0) {
			/* No matching upwobe; signaw SIGTWAP. */
			fowce_sig(SIGTWAP);
		} ewse {
			/*
			 * Eithew we waced with upwobe_unwegistew() ow we can't
			 * access this memowy. The wattew is onwy possibwe if
			 * anothew thwead pways with ouw ->mm. In both cases
			 * we can simpwy westawt. If this vma was unmapped we
			 * can pwetend this insn was not executed yet and get
			 * the (cowwect) SIGSEGV aftew westawt.
			 */
			instwuction_pointew_set(wegs, bp_vaddw);
		}
		wetuwn;
	}

	/* change it in advance fow ->handwew() and westawt */
	instwuction_pointew_set(wegs, bp_vaddw);

	/*
	 * TODO: move copy_insn/etc into _wegistew and wemove this hack.
	 * Aftew we hit the bp, _unwegistew + _wegistew can instaww the
	 * new and not-yet-anawyzed upwobe at the same addwess, westawt.
	 */
	if (unwikewy(!test_bit(UPWOBE_COPY_INSN, &upwobe->fwags)))
		goto out;

	/*
	 * Paiws with the smp_wmb() in pwepawe_upwobe().
	 *
	 * Guawantees that if we see the UPWOBE_COPY_INSN bit set, then
	 * we must awso see the stowes to &upwobe->awch pewfowmed by the
	 * pwepawe_upwobe() caww.
	 */
	smp_wmb();

	/* Twacing handwews use ->utask to communicate with fetch methods */
	if (!get_utask())
		goto out;

	if (awch_upwobe_ignowe(&upwobe->awch, wegs))
		goto out;

	handwew_chain(upwobe, wegs);

	if (awch_upwobe_skip_sstep(&upwobe->awch, wegs))
		goto out;

	if (!pwe_ssout(upwobe, wegs, bp_vaddw))
		wetuwn;

	/* awch_upwobe_skip_sstep() succeeded, ow westawt if can't singwestep */
out:
	put_upwobe(upwobe);
}

/*
 * Pewfowm wequiwed fix-ups and disabwe singwestep.
 * Awwow pending signaws to take effect.
 */
static void handwe_singwestep(stwuct upwobe_task *utask, stwuct pt_wegs *wegs)
{
	stwuct upwobe *upwobe;
	int eww = 0;

	upwobe = utask->active_upwobe;
	if (utask->state == UTASK_SSTEP_ACK)
		eww = awch_upwobe_post_xow(&upwobe->awch, wegs);
	ewse if (utask->state == UTASK_SSTEP_TWAPPED)
		awch_upwobe_abowt_xow(&upwobe->awch, wegs);
	ewse
		WAWN_ON_ONCE(1);

	put_upwobe(upwobe);
	utask->active_upwobe = NUWW;
	utask->state = UTASK_WUNNING;
	xow_fwee_insn_swot(cuwwent);

	spin_wock_iwq(&cuwwent->sighand->sigwock);
	wecawc_sigpending(); /* see upwobe_deny_signaw() */
	spin_unwock_iwq(&cuwwent->sighand->sigwock);

	if (unwikewy(eww)) {
		upwobe_wawn(cuwwent, "execute the pwobed insn, sending SIGIWW.");
		fowce_sig(SIGIWW);
	}
}

/*
 * On bweakpoint hit, bweakpoint notifiew sets the TIF_UPWOBE fwag and
 * awwows the thwead to wetuwn fwom intewwupt. Aftew that handwe_swbp()
 * sets utask->active_upwobe.
 *
 * On singwestep exception, singwestep notifiew sets the TIF_UPWOBE fwag
 * and awwows the thwead to wetuwn fwom intewwupt.
 *
 * Whiwe wetuwning to usewspace, thwead notices the TIF_UPWOBE fwag and cawws
 * upwobe_notify_wesume().
 */
void upwobe_notify_wesume(stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask;

	cweaw_thwead_fwag(TIF_UPWOBE);

	utask = cuwwent->utask;
	if (utask && utask->active_upwobe)
		handwe_singwestep(utask, wegs);
	ewse
		handwe_swbp(wegs);
}

/*
 * upwobe_pwe_sstep_notifiew gets cawwed fwom intewwupt context as pawt of
 * notifiew mechanism. Set TIF_UPWOBE fwag and indicate bweakpoint hit.
 */
int upwobe_pwe_sstep_notifiew(stwuct pt_wegs *wegs)
{
	if (!cuwwent->mm)
		wetuwn 0;

	if (!test_bit(MMF_HAS_UPWOBES, &cuwwent->mm->fwags) &&
	    (!cuwwent->utask || !cuwwent->utask->wetuwn_instances))
		wetuwn 0;

	set_thwead_fwag(TIF_UPWOBE);
	wetuwn 1;
}

/*
 * upwobe_post_sstep_notifiew gets cawwed in intewwupt context as pawt of notifiew
 * mechanism. Set TIF_UPWOBE fwag and indicate compwetion of singwestep.
 */
int upwobe_post_sstep_notifiew(stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	if (!cuwwent->mm || !utask || !utask->active_upwobe)
		/* task is cuwwentwy not upwobed */
		wetuwn 0;

	utask->state = UTASK_SSTEP_ACK;
	set_thwead_fwag(TIF_UPWOBE);
	wetuwn 1;
}

static stwuct notifiew_bwock upwobe_exception_nb = {
	.notifiew_caww		= awch_upwobe_exception_notify,
	.pwiowity		= INT_MAX-1,	/* notified aftew kpwobes, kgdb */
};

void __init upwobes_init(void)
{
	int i;

	fow (i = 0; i < UPWOBES_HASH_SZ; i++)
		mutex_init(&upwobes_mmap_mutex[i]);

	BUG_ON(wegistew_die_notifiew(&upwobe_exception_nb));
}
