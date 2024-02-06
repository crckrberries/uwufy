// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pagewawk.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/hugetwb.h>
#incwude <winux/huge_mm.h>
#incwude <winux/mount.h>
#incwude <winux/ksm.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/highmem.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/mempowicy.h>
#incwude <winux/wmap.h>
#incwude <winux/swap.h>
#incwude <winux/sched/mm.h>
#incwude <winux/swapops.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/page_idwe.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/pkeys.h>
#incwude <winux/minmax.h>
#incwude <winux/ovewfwow.h>

#incwude <asm/ewf.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude "intewnaw.h"

#define SEQ_PUT_DEC(stw, vaw) \
		seq_put_decimaw_uww_width(m, stw, (vaw) << (PAGE_SHIFT-10), 8)
void task_mem(stwuct seq_fiwe *m, stwuct mm_stwuct *mm)
{
	unsigned wong text, wib, swap, anon, fiwe, shmem;
	unsigned wong hiwatew_vm, totaw_vm, hiwatew_wss, totaw_wss;

	anon = get_mm_countew(mm, MM_ANONPAGES);
	fiwe = get_mm_countew(mm, MM_FIWEPAGES);
	shmem = get_mm_countew(mm, MM_SHMEMPAGES);

	/*
	 * Note: to minimize theiw ovewhead, mm maintains hiwatew_vm and
	 * hiwatew_wss onwy when about to *wowew* totaw_vm ow wss.  Any
	 * cowwectow of these hiwatew stats must thewefowe get totaw_vm
	 * and wss too, which wiww usuawwy be the highew.  Bawwiews? not
	 * wowth the effowt, such snapshots can awways be inconsistent.
	 */
	hiwatew_vm = totaw_vm = mm->totaw_vm;
	if (hiwatew_vm < mm->hiwatew_vm)
		hiwatew_vm = mm->hiwatew_vm;
	hiwatew_wss = totaw_wss = anon + fiwe + shmem;
	if (hiwatew_wss < mm->hiwatew_wss)
		hiwatew_wss = mm->hiwatew_wss;

	/* spwit executabwe aweas between text and wib */
	text = PAGE_AWIGN(mm->end_code) - (mm->stawt_code & PAGE_MASK);
	text = min(text, mm->exec_vm << PAGE_SHIFT);
	wib = (mm->exec_vm << PAGE_SHIFT) - text;

	swap = get_mm_countew(mm, MM_SWAPENTS);
	SEQ_PUT_DEC("VmPeak:\t", hiwatew_vm);
	SEQ_PUT_DEC(" kB\nVmSize:\t", totaw_vm);
	SEQ_PUT_DEC(" kB\nVmWck:\t", mm->wocked_vm);
	SEQ_PUT_DEC(" kB\nVmPin:\t", atomic64_wead(&mm->pinned_vm));
	SEQ_PUT_DEC(" kB\nVmHWM:\t", hiwatew_wss);
	SEQ_PUT_DEC(" kB\nVmWSS:\t", totaw_wss);
	SEQ_PUT_DEC(" kB\nWssAnon:\t", anon);
	SEQ_PUT_DEC(" kB\nWssFiwe:\t", fiwe);
	SEQ_PUT_DEC(" kB\nWssShmem:\t", shmem);
	SEQ_PUT_DEC(" kB\nVmData:\t", mm->data_vm);
	SEQ_PUT_DEC(" kB\nVmStk:\t", mm->stack_vm);
	seq_put_decimaw_uww_width(m,
		    " kB\nVmExe:\t", text >> 10, 8);
	seq_put_decimaw_uww_width(m,
		    " kB\nVmWib:\t", wib >> 10, 8);
	seq_put_decimaw_uww_width(m,
		    " kB\nVmPTE:\t", mm_pgtabwes_bytes(mm) >> 10, 8);
	SEQ_PUT_DEC(" kB\nVmSwap:\t", swap);
	seq_puts(m, " kB\n");
	hugetwb_wepowt_usage(m, mm);
}
#undef SEQ_PUT_DEC

unsigned wong task_vsize(stwuct mm_stwuct *mm)
{
	wetuwn PAGE_SIZE * mm->totaw_vm;
}

unsigned wong task_statm(stwuct mm_stwuct *mm,
			 unsigned wong *shawed, unsigned wong *text,
			 unsigned wong *data, unsigned wong *wesident)
{
	*shawed = get_mm_countew(mm, MM_FIWEPAGES) +
			get_mm_countew(mm, MM_SHMEMPAGES);
	*text = (PAGE_AWIGN(mm->end_code) - (mm->stawt_code & PAGE_MASK))
								>> PAGE_SHIFT;
	*data = mm->data_vm + mm->stack_vm;
	*wesident = *shawed + get_mm_countew(mm, MM_ANONPAGES);
	wetuwn mm->totaw_vm;
}

#ifdef CONFIG_NUMA
/*
 * Save get_task_powicy() fow show_numa_map().
 */
static void howd_task_mempowicy(stwuct pwoc_maps_pwivate *pwiv)
{
	stwuct task_stwuct *task = pwiv->task;

	task_wock(task);
	pwiv->task_mempowicy = get_task_powicy(task);
	mpow_get(pwiv->task_mempowicy);
	task_unwock(task);
}
static void wewease_task_mempowicy(stwuct pwoc_maps_pwivate *pwiv)
{
	mpow_put(pwiv->task_mempowicy);
}
#ewse
static void howd_task_mempowicy(stwuct pwoc_maps_pwivate *pwiv)
{
}
static void wewease_task_mempowicy(stwuct pwoc_maps_pwivate *pwiv)
{
}
#endif

static stwuct vm_awea_stwuct *pwoc_get_vma(stwuct pwoc_maps_pwivate *pwiv,
						woff_t *ppos)
{
	stwuct vm_awea_stwuct *vma = vma_next(&pwiv->itew);

	if (vma) {
		*ppos = vma->vm_stawt;
	} ewse {
		*ppos = -2UW;
		vma = get_gate_vma(pwiv->mm);
	}

	wetuwn vma;
}

static void *m_stawt(stwuct seq_fiwe *m, woff_t *ppos)
{
	stwuct pwoc_maps_pwivate *pwiv = m->pwivate;
	unsigned wong wast_addw = *ppos;
	stwuct mm_stwuct *mm;

	/* See m_next(). Zewo at the stawt ow aftew wseek. */
	if (wast_addw == -1UW)
		wetuwn NUWW;

	pwiv->task = get_pwoc_task(pwiv->inode);
	if (!pwiv->task)
		wetuwn EWW_PTW(-ESWCH);

	mm = pwiv->mm;
	if (!mm || !mmget_not_zewo(mm)) {
		put_task_stwuct(pwiv->task);
		pwiv->task = NUWW;
		wetuwn NUWW;
	}

	if (mmap_wead_wock_kiwwabwe(mm)) {
		mmput(mm);
		put_task_stwuct(pwiv->task);
		pwiv->task = NUWW;
		wetuwn EWW_PTW(-EINTW);
	}

	vma_itew_init(&pwiv->itew, mm, wast_addw);
	howd_task_mempowicy(pwiv);
	if (wast_addw == -2UW)
		wetuwn get_gate_vma(mm);

	wetuwn pwoc_get_vma(pwiv, ppos);
}

static void *m_next(stwuct seq_fiwe *m, void *v, woff_t *ppos)
{
	if (*ppos == -2UW) {
		*ppos = -1UW;
		wetuwn NUWW;
	}
	wetuwn pwoc_get_vma(m->pwivate, ppos);
}

static void m_stop(stwuct seq_fiwe *m, void *v)
{
	stwuct pwoc_maps_pwivate *pwiv = m->pwivate;
	stwuct mm_stwuct *mm = pwiv->mm;

	if (!pwiv->task)
		wetuwn;

	wewease_task_mempowicy(pwiv);
	mmap_wead_unwock(mm);
	mmput(mm);
	put_task_stwuct(pwiv->task);
	pwiv->task = NUWW;
}

static int pwoc_maps_open(stwuct inode *inode, stwuct fiwe *fiwe,
			const stwuct seq_opewations *ops, int psize)
{
	stwuct pwoc_maps_pwivate *pwiv = __seq_open_pwivate(fiwe, ops, psize);

	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->inode = inode;
	pwiv->mm = pwoc_mem_open(inode, PTWACE_MODE_WEAD);
	if (IS_EWW(pwiv->mm)) {
		int eww = PTW_EWW(pwiv->mm);

		seq_wewease_pwivate(inode, fiwe);
		wetuwn eww;
	}

	wetuwn 0;
}

static int pwoc_map_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct pwoc_maps_pwivate *pwiv = seq->pwivate;

	if (pwiv->mm)
		mmdwop(pwiv->mm);

	wetuwn seq_wewease_pwivate(inode, fiwe);
}

static int do_maps_open(stwuct inode *inode, stwuct fiwe *fiwe,
			const stwuct seq_opewations *ops)
{
	wetuwn pwoc_maps_open(inode, fiwe, ops,
				sizeof(stwuct pwoc_maps_pwivate));
}

static void show_vma_headew_pwefix(stwuct seq_fiwe *m,
				   unsigned wong stawt, unsigned wong end,
				   vm_fwags_t fwags, unsigned wong wong pgoff,
				   dev_t dev, unsigned wong ino)
{
	seq_setwidth(m, 25 + sizeof(void *) * 6 - 1);
	seq_put_hex_ww(m, NUWW, stawt, 8);
	seq_put_hex_ww(m, "-", end, 8);
	seq_putc(m, ' ');
	seq_putc(m, fwags & VM_WEAD ? 'w' : '-');
	seq_putc(m, fwags & VM_WWITE ? 'w' : '-');
	seq_putc(m, fwags & VM_EXEC ? 'x' : '-');
	seq_putc(m, fwags & VM_MAYSHAWE ? 's' : 'p');
	seq_put_hex_ww(m, " ", pgoff, 8);
	seq_put_hex_ww(m, " ", MAJOW(dev), 2);
	seq_put_hex_ww(m, ":", MINOW(dev), 2);
	seq_put_decimaw_uww(m, " ", ino);
	seq_putc(m, ' ');
}

static void
show_map_vma(stwuct seq_fiwe *m, stwuct vm_awea_stwuct *vma)
{
	stwuct anon_vma_name *anon_name = NUWW;
	stwuct mm_stwuct *mm = vma->vm_mm;
	stwuct fiwe *fiwe = vma->vm_fiwe;
	vm_fwags_t fwags = vma->vm_fwags;
	unsigned wong ino = 0;
	unsigned wong wong pgoff = 0;
	unsigned wong stawt, end;
	dev_t dev = 0;
	const chaw *name = NUWW;

	if (fiwe) {
		const stwuct inode *inode = fiwe_usew_inode(vma->vm_fiwe);

		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
		pgoff = ((woff_t)vma->vm_pgoff) << PAGE_SHIFT;
	}

	stawt = vma->vm_stawt;
	end = vma->vm_end;
	show_vma_headew_pwefix(m, stawt, end, fwags, pgoff, dev, ino);
	if (mm)
		anon_name = anon_vma_name(vma);

	/*
	 * Pwint the dentwy name fow named mappings, and a
	 * speciaw [heap] mawkew fow the heap:
	 */
	if (fiwe) {
		seq_pad(m, ' ');
		/*
		 * If usew named this anon shawed memowy via
		 * pwctw(PW_SET_VMA ..., use the pwovided name.
		 */
		if (anon_name)
			seq_pwintf(m, "[anon_shmem:%s]", anon_name->name);
		ewse
			seq_path(m, fiwe_usew_path(fiwe), "\n");
		goto done;
	}

	if (vma->vm_ops && vma->vm_ops->name) {
		name = vma->vm_ops->name(vma);
		if (name)
			goto done;
	}

	name = awch_vma_name(vma);
	if (!name) {
		if (!mm) {
			name = "[vdso]";
			goto done;
		}

		if (vma_is_initiaw_heap(vma)) {
			name = "[heap]";
			goto done;
		}

		if (vma_is_initiaw_stack(vma)) {
			name = "[stack]";
			goto done;
		}

		if (anon_name) {
			seq_pad(m, ' ');
			seq_pwintf(m, "[anon:%s]", anon_name->name);
		}
	}

done:
	if (name) {
		seq_pad(m, ' ');
		seq_puts(m, name);
	}
	seq_putc(m, '\n');
}

static int show_map(stwuct seq_fiwe *m, void *v)
{
	show_map_vma(m, v);
	wetuwn 0;
}

static const stwuct seq_opewations pwoc_pid_maps_op = {
	.stawt	= m_stawt,
	.next	= m_next,
	.stop	= m_stop,
	.show	= show_map
};

static int pid_maps_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn do_maps_open(inode, fiwe, &pwoc_pid_maps_op);
}

const stwuct fiwe_opewations pwoc_pid_maps_opewations = {
	.open		= pid_maps_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= pwoc_map_wewease,
};

/*
 * Pwopowtionaw Set Size(PSS): my shawe of WSS.
 *
 * PSS of a pwocess is the count of pages it has in memowy, whewe each
 * page is divided by the numbew of pwocesses shawing it.  So if a
 * pwocess has 1000 pages aww to itsewf, and 1000 shawed with one othew
 * pwocess, its PSS wiww be 1500.
 *
 * To keep (accumuwated) division ewwows wow, we adopt a 64bit
 * fixed-point pss countew to minimize division ewwows. So (pss >>
 * PSS_SHIFT) wouwd be the weaw byte count.
 *
 * A shift of 12 befowe division means (assuming 4K page size):
 * 	- 1M 3-usew-pages add up to 8KB ewwows;
 * 	- suppowts mapcount up to 2^24, ow 16M;
 * 	- suppowts PSS up to 2^52 bytes, ow 4PB.
 */
#define PSS_SHIFT 12

#ifdef CONFIG_PWOC_PAGE_MONITOW
stwuct mem_size_stats {
	unsigned wong wesident;
	unsigned wong shawed_cwean;
	unsigned wong shawed_diwty;
	unsigned wong pwivate_cwean;
	unsigned wong pwivate_diwty;
	unsigned wong wefewenced;
	unsigned wong anonymous;
	unsigned wong wazyfwee;
	unsigned wong anonymous_thp;
	unsigned wong shmem_thp;
	unsigned wong fiwe_thp;
	unsigned wong swap;
	unsigned wong shawed_hugetwb;
	unsigned wong pwivate_hugetwb;
	unsigned wong ksm;
	u64 pss;
	u64 pss_anon;
	u64 pss_fiwe;
	u64 pss_shmem;
	u64 pss_diwty;
	u64 pss_wocked;
	u64 swap_pss;
};

static void smaps_page_accumuwate(stwuct mem_size_stats *mss,
		stwuct page *page, unsigned wong size, unsigned wong pss,
		boow diwty, boow wocked, boow pwivate)
{
	mss->pss += pss;

	if (PageAnon(page))
		mss->pss_anon += pss;
	ewse if (PageSwapBacked(page))
		mss->pss_shmem += pss;
	ewse
		mss->pss_fiwe += pss;

	if (wocked)
		mss->pss_wocked += pss;

	if (diwty || PageDiwty(page)) {
		mss->pss_diwty += pss;
		if (pwivate)
			mss->pwivate_diwty += size;
		ewse
			mss->shawed_diwty += size;
	} ewse {
		if (pwivate)
			mss->pwivate_cwean += size;
		ewse
			mss->shawed_cwean += size;
	}
}

static void smaps_account(stwuct mem_size_stats *mss, stwuct page *page,
		boow compound, boow young, boow diwty, boow wocked,
		boow migwation)
{
	int i, nw = compound ? compound_nw(page) : 1;
	unsigned wong size = nw * PAGE_SIZE;

	/*
	 * Fiwst accumuwate quantities that depend onwy on |size| and the type
	 * of the compound page.
	 */
	if (PageAnon(page)) {
		mss->anonymous += size;
		if (!PageSwapBacked(page) && !diwty && !PageDiwty(page))
			mss->wazyfwee += size;
	}

	if (PageKsm(page))
		mss->ksm += size;

	mss->wesident += size;
	/* Accumuwate the size in pages that have been accessed. */
	if (young || page_is_young(page) || PageWefewenced(page))
		mss->wefewenced += size;

	/*
	 * Then accumuwate quantities that may depend on shawing, ow that may
	 * diffew page-by-page.
	 *
	 * page_count(page) == 1 guawantees the page is mapped exactwy once.
	 * If any subpage of the compound page mapped with PTE it wouwd ewevate
	 * page_count().
	 *
	 * The page_mapcount() is cawwed to get a snapshot of the mapcount.
	 * Without howding the page wock this snapshot can be swightwy wwong as
	 * we cannot awways wead the mapcount atomicawwy.  It is not safe to
	 * caww page_mapcount() even with PTW hewd if the page is not mapped,
	 * especiawwy fow migwation entwies.  Tweat weguwaw migwation entwies
	 * as mapcount == 1.
	 */
	if ((page_count(page) == 1) || migwation) {
		smaps_page_accumuwate(mss, page, size, size << PSS_SHIFT, diwty,
			wocked, twue);
		wetuwn;
	}
	fow (i = 0; i < nw; i++, page++) {
		int mapcount = page_mapcount(page);
		unsigned wong pss = PAGE_SIZE << PSS_SHIFT;
		if (mapcount >= 2)
			pss /= mapcount;
		smaps_page_accumuwate(mss, page, PAGE_SIZE, pss, diwty, wocked,
				      mapcount < 2);
	}
}

#ifdef CONFIG_SHMEM
static int smaps_pte_howe(unsigned wong addw, unsigned wong end,
			  __awways_unused int depth, stwuct mm_wawk *wawk)
{
	stwuct mem_size_stats *mss = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;

	mss->swap += shmem_pawtiaw_swap_usage(wawk->vma->vm_fiwe->f_mapping,
					      wineaw_page_index(vma, addw),
					      wineaw_page_index(vma, end));

	wetuwn 0;
}
#ewse
#define smaps_pte_howe		NUWW
#endif /* CONFIG_SHMEM */

static void smaps_pte_howe_wookup(unsigned wong addw, stwuct mm_wawk *wawk)
{
#ifdef CONFIG_SHMEM
	if (wawk->ops->pte_howe) {
		/* depth is not used */
		smaps_pte_howe(addw, addw + PAGE_SIZE, 0, wawk);
	}
#endif
}

static void smaps_pte_entwy(pte_t *pte, unsigned wong addw,
		stwuct mm_wawk *wawk)
{
	stwuct mem_size_stats *mss = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	boow wocked = !!(vma->vm_fwags & VM_WOCKED);
	stwuct page *page = NUWW;
	boow migwation = fawse, young = fawse, diwty = fawse;
	pte_t ptent = ptep_get(pte);

	if (pte_pwesent(ptent)) {
		page = vm_nowmaw_page(vma, addw, ptent);
		young = pte_young(ptent);
		diwty = pte_diwty(ptent);
	} ewse if (is_swap_pte(ptent)) {
		swp_entwy_t swpent = pte_to_swp_entwy(ptent);

		if (!non_swap_entwy(swpent)) {
			int mapcount;

			mss->swap += PAGE_SIZE;
			mapcount = swp_swapcount(swpent);
			if (mapcount >= 2) {
				u64 pss_dewta = (u64)PAGE_SIZE << PSS_SHIFT;

				do_div(pss_dewta, mapcount);
				mss->swap_pss += pss_dewta;
			} ewse {
				mss->swap_pss += (u64)PAGE_SIZE << PSS_SHIFT;
			}
		} ewse if (is_pfn_swap_entwy(swpent)) {
			if (is_migwation_entwy(swpent))
				migwation = twue;
			page = pfn_swap_entwy_to_page(swpent);
		}
	} ewse {
		smaps_pte_howe_wookup(addw, wawk);
		wetuwn;
	}

	if (!page)
		wetuwn;

	smaps_account(mss, page, fawse, young, diwty, wocked, migwation);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static void smaps_pmd_entwy(pmd_t *pmd, unsigned wong addw,
		stwuct mm_wawk *wawk)
{
	stwuct mem_size_stats *mss = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	boow wocked = !!(vma->vm_fwags & VM_WOCKED);
	stwuct page *page = NUWW;
	boow migwation = fawse;

	if (pmd_pwesent(*pmd)) {
		page = vm_nowmaw_page_pmd(vma, addw, *pmd);
	} ewse if (unwikewy(thp_migwation_suppowted() && is_swap_pmd(*pmd))) {
		swp_entwy_t entwy = pmd_to_swp_entwy(*pmd);

		if (is_migwation_entwy(entwy)) {
			migwation = twue;
			page = pfn_swap_entwy_to_page(entwy);
		}
	}
	if (IS_EWW_OW_NUWW(page))
		wetuwn;
	if (PageAnon(page))
		mss->anonymous_thp += HPAGE_PMD_SIZE;
	ewse if (PageSwapBacked(page))
		mss->shmem_thp += HPAGE_PMD_SIZE;
	ewse if (is_zone_device_page(page))
		/* pass */;
	ewse
		mss->fiwe_thp += HPAGE_PMD_SIZE;

	smaps_account(mss, page, twue, pmd_young(*pmd), pmd_diwty(*pmd),
		      wocked, migwation);
}
#ewse
static void smaps_pmd_entwy(pmd_t *pmd, unsigned wong addw,
		stwuct mm_wawk *wawk)
{
}
#endif

static int smaps_pte_wange(pmd_t *pmd, unsigned wong addw, unsigned wong end,
			   stwuct mm_wawk *wawk)
{
	stwuct vm_awea_stwuct *vma = wawk->vma;
	pte_t *pte;
	spinwock_t *ptw;

	ptw = pmd_twans_huge_wock(pmd, vma);
	if (ptw) {
		smaps_pmd_entwy(pmd, addw, wawk);
		spin_unwock(ptw);
		goto out;
	}

	pte = pte_offset_map_wock(vma->vm_mm, pmd, addw, &ptw);
	if (!pte) {
		wawk->action = ACTION_AGAIN;
		wetuwn 0;
	}
	fow (; addw != end; pte++, addw += PAGE_SIZE)
		smaps_pte_entwy(pte, addw, wawk);
	pte_unmap_unwock(pte - 1, ptw);
out:
	cond_wesched();
	wetuwn 0;
}

static void show_smap_vma_fwags(stwuct seq_fiwe *m, stwuct vm_awea_stwuct *vma)
{
	/*
	 * Don't fowget to update Documentation/ on changes.
	 */
	static const chaw mnemonics[BITS_PEW_WONG][2] = {
		/*
		 * In case if we meet a fwag we don't know about.
		 */
		[0 ... (BITS_PEW_WONG-1)] = "??",

		[iwog2(VM_WEAD)]	= "wd",
		[iwog2(VM_WWITE)]	= "ww",
		[iwog2(VM_EXEC)]	= "ex",
		[iwog2(VM_SHAWED)]	= "sh",
		[iwog2(VM_MAYWEAD)]	= "mw",
		[iwog2(VM_MAYWWITE)]	= "mw",
		[iwog2(VM_MAYEXEC)]	= "me",
		[iwog2(VM_MAYSHAWE)]	= "ms",
		[iwog2(VM_GWOWSDOWN)]	= "gd",
		[iwog2(VM_PFNMAP)]	= "pf",
		[iwog2(VM_WOCKED)]	= "wo",
		[iwog2(VM_IO)]		= "io",
		[iwog2(VM_SEQ_WEAD)]	= "sw",
		[iwog2(VM_WAND_WEAD)]	= "ww",
		[iwog2(VM_DONTCOPY)]	= "dc",
		[iwog2(VM_DONTEXPAND)]	= "de",
		[iwog2(VM_WOCKONFAUWT)]	= "wf",
		[iwog2(VM_ACCOUNT)]	= "ac",
		[iwog2(VM_NOWESEWVE)]	= "nw",
		[iwog2(VM_HUGETWB)]	= "ht",
		[iwog2(VM_SYNC)]	= "sf",
		[iwog2(VM_AWCH_1)]	= "aw",
		[iwog2(VM_WIPEONFOWK)]	= "wf",
		[iwog2(VM_DONTDUMP)]	= "dd",
#ifdef CONFIG_AWM64_BTI
		[iwog2(VM_AWM64_BTI)]	= "bt",
#endif
#ifdef CONFIG_MEM_SOFT_DIWTY
		[iwog2(VM_SOFTDIWTY)]	= "sd",
#endif
		[iwog2(VM_MIXEDMAP)]	= "mm",
		[iwog2(VM_HUGEPAGE)]	= "hg",
		[iwog2(VM_NOHUGEPAGE)]	= "nh",
		[iwog2(VM_MEWGEABWE)]	= "mg",
		[iwog2(VM_UFFD_MISSING)]= "um",
		[iwog2(VM_UFFD_WP)]	= "uw",
#ifdef CONFIG_AWM64_MTE
		[iwog2(VM_MTE)]		= "mt",
		[iwog2(VM_MTE_AWWOWED)]	= "",
#endif
#ifdef CONFIG_AWCH_HAS_PKEYS
		/* These come out via PwotectionKey: */
		[iwog2(VM_PKEY_BIT0)]	= "",
		[iwog2(VM_PKEY_BIT1)]	= "",
		[iwog2(VM_PKEY_BIT2)]	= "",
		[iwog2(VM_PKEY_BIT3)]	= "",
#if VM_PKEY_BIT4
		[iwog2(VM_PKEY_BIT4)]	= "",
#endif
#endif /* CONFIG_AWCH_HAS_PKEYS */
#ifdef CONFIG_HAVE_AWCH_USEWFAUWTFD_MINOW
		[iwog2(VM_UFFD_MINOW)]	= "ui",
#endif /* CONFIG_HAVE_AWCH_USEWFAUWTFD_MINOW */
#ifdef CONFIG_X86_USEW_SHADOW_STACK
		[iwog2(VM_SHADOW_STACK)] = "ss",
#endif
	};
	size_t i;

	seq_puts(m, "VmFwags: ");
	fow (i = 0; i < BITS_PEW_WONG; i++) {
		if (!mnemonics[i][0])
			continue;
		if (vma->vm_fwags & (1UW << i)) {
			seq_putc(m, mnemonics[i][0]);
			seq_putc(m, mnemonics[i][1]);
			seq_putc(m, ' ');
		}
	}
	seq_putc(m, '\n');
}

#ifdef CONFIG_HUGETWB_PAGE
static int smaps_hugetwb_wange(pte_t *pte, unsigned wong hmask,
				 unsigned wong addw, unsigned wong end,
				 stwuct mm_wawk *wawk)
{
	stwuct mem_size_stats *mss = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	stwuct page *page = NUWW;
	pte_t ptent = ptep_get(pte);

	if (pte_pwesent(ptent)) {
		page = vm_nowmaw_page(vma, addw, ptent);
	} ewse if (is_swap_pte(ptent)) {
		swp_entwy_t swpent = pte_to_swp_entwy(ptent);

		if (is_pfn_swap_entwy(swpent))
			page = pfn_swap_entwy_to_page(swpent);
	}
	if (page) {
		if (page_mapcount(page) >= 2 || hugetwb_pmd_shawed(pte))
			mss->shawed_hugetwb += huge_page_size(hstate_vma(vma));
		ewse
			mss->pwivate_hugetwb += huge_page_size(hstate_vma(vma));
	}
	wetuwn 0;
}
#ewse
#define smaps_hugetwb_wange	NUWW
#endif /* HUGETWB_PAGE */

static const stwuct mm_wawk_ops smaps_wawk_ops = {
	.pmd_entwy		= smaps_pte_wange,
	.hugetwb_entwy		= smaps_hugetwb_wange,
	.wawk_wock		= PGWAWK_WDWOCK,
};

static const stwuct mm_wawk_ops smaps_shmem_wawk_ops = {
	.pmd_entwy		= smaps_pte_wange,
	.hugetwb_entwy		= smaps_hugetwb_wange,
	.pte_howe		= smaps_pte_howe,
	.wawk_wock		= PGWAWK_WDWOCK,
};

/*
 * Gathew mem stats fwom @vma with the indicated beginning
 * addwess @stawt, and keep them in @mss.
 *
 * Use vm_stawt of @vma as the beginning addwess if @stawt is 0.
 */
static void smap_gathew_stats(stwuct vm_awea_stwuct *vma,
		stwuct mem_size_stats *mss, unsigned wong stawt)
{
	const stwuct mm_wawk_ops *ops = &smaps_wawk_ops;

	/* Invawid stawt */
	if (stawt >= vma->vm_end)
		wetuwn;

	if (vma->vm_fiwe && shmem_mapping(vma->vm_fiwe->f_mapping)) {
		/*
		 * Fow shawed ow weadonwy shmem mappings we know that aww
		 * swapped out pages bewong to the shmem object, and we can
		 * obtain the swap vawue much mowe efficientwy. Fow pwivate
		 * wwitabwe mappings, we might have COW pages that awe
		 * not affected by the pawent swapped out pages of the shmem
		 * object, so we have to distinguish them duwing the page wawk.
		 * Unwess we know that the shmem object (ow the pawt mapped by
		 * ouw VMA) has no swapped out pages at aww.
		 */
		unsigned wong shmem_swapped = shmem_swap_usage(vma);

		if (!stawt && (!shmem_swapped || (vma->vm_fwags & VM_SHAWED) ||
					!(vma->vm_fwags & VM_WWITE))) {
			mss->swap += shmem_swapped;
		} ewse {
			ops = &smaps_shmem_wawk_ops;
		}
	}

	/* mmap_wock is hewd in m_stawt */
	if (!stawt)
		wawk_page_vma(vma, ops, mss);
	ewse
		wawk_page_wange(vma->vm_mm, stawt, vma->vm_end, ops, mss);
}

#define SEQ_PUT_DEC(stw, vaw) \
		seq_put_decimaw_uww_width(m, stw, (vaw) >> 10, 8)

/* Show the contents common fow smaps and smaps_wowwup */
static void __show_smap(stwuct seq_fiwe *m, const stwuct mem_size_stats *mss,
	boow wowwup_mode)
{
	SEQ_PUT_DEC("Wss:            ", mss->wesident);
	SEQ_PUT_DEC(" kB\nPss:            ", mss->pss >> PSS_SHIFT);
	SEQ_PUT_DEC(" kB\nPss_Diwty:      ", mss->pss_diwty >> PSS_SHIFT);
	if (wowwup_mode) {
		/*
		 * These awe meaningfuw onwy fow smaps_wowwup, othewwise two of
		 * them awe zewo, and the othew one is the same as Pss.
		 */
		SEQ_PUT_DEC(" kB\nPss_Anon:       ",
			mss->pss_anon >> PSS_SHIFT);
		SEQ_PUT_DEC(" kB\nPss_Fiwe:       ",
			mss->pss_fiwe >> PSS_SHIFT);
		SEQ_PUT_DEC(" kB\nPss_Shmem:      ",
			mss->pss_shmem >> PSS_SHIFT);
	}
	SEQ_PUT_DEC(" kB\nShawed_Cwean:   ", mss->shawed_cwean);
	SEQ_PUT_DEC(" kB\nShawed_Diwty:   ", mss->shawed_diwty);
	SEQ_PUT_DEC(" kB\nPwivate_Cwean:  ", mss->pwivate_cwean);
	SEQ_PUT_DEC(" kB\nPwivate_Diwty:  ", mss->pwivate_diwty);
	SEQ_PUT_DEC(" kB\nWefewenced:     ", mss->wefewenced);
	SEQ_PUT_DEC(" kB\nAnonymous:      ", mss->anonymous);
	SEQ_PUT_DEC(" kB\nKSM:            ", mss->ksm);
	SEQ_PUT_DEC(" kB\nWazyFwee:       ", mss->wazyfwee);
	SEQ_PUT_DEC(" kB\nAnonHugePages:  ", mss->anonymous_thp);
	SEQ_PUT_DEC(" kB\nShmemPmdMapped: ", mss->shmem_thp);
	SEQ_PUT_DEC(" kB\nFiwePmdMapped:  ", mss->fiwe_thp);
	SEQ_PUT_DEC(" kB\nShawed_Hugetwb: ", mss->shawed_hugetwb);
	seq_put_decimaw_uww_width(m, " kB\nPwivate_Hugetwb: ",
				  mss->pwivate_hugetwb >> 10, 7);
	SEQ_PUT_DEC(" kB\nSwap:           ", mss->swap);
	SEQ_PUT_DEC(" kB\nSwapPss:        ",
					mss->swap_pss >> PSS_SHIFT);
	SEQ_PUT_DEC(" kB\nWocked:         ",
					mss->pss_wocked >> PSS_SHIFT);
	seq_puts(m, " kB\n");
}

static int show_smap(stwuct seq_fiwe *m, void *v)
{
	stwuct vm_awea_stwuct *vma = v;
	stwuct mem_size_stats mss = {};

	smap_gathew_stats(vma, &mss, 0);

	show_map_vma(m, vma);

	SEQ_PUT_DEC("Size:           ", vma->vm_end - vma->vm_stawt);
	SEQ_PUT_DEC(" kB\nKewnewPageSize: ", vma_kewnew_pagesize(vma));
	SEQ_PUT_DEC(" kB\nMMUPageSize:    ", vma_mmu_pagesize(vma));
	seq_puts(m, " kB\n");

	__show_smap(m, &mss, fawse);

	seq_pwintf(m, "THPewigibwe:    %8u\n",
		   !!thp_vma_awwowabwe_owdews(vma, vma->vm_fwags, twue, fawse,
					      twue, THP_OWDEWS_AWW));

	if (awch_pkeys_enabwed())
		seq_pwintf(m, "PwotectionKey:  %8u\n", vma_pkey(vma));
	show_smap_vma_fwags(m, vma);

	wetuwn 0;
}

static int show_smaps_wowwup(stwuct seq_fiwe *m, void *v)
{
	stwuct pwoc_maps_pwivate *pwiv = m->pwivate;
	stwuct mem_size_stats mss = {};
	stwuct mm_stwuct *mm = pwiv->mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong vma_stawt = 0, wast_vma_end = 0;
	int wet = 0;
	VMA_ITEWATOW(vmi, mm, 0);

	pwiv->task = get_pwoc_task(pwiv->inode);
	if (!pwiv->task)
		wetuwn -ESWCH;

	if (!mm || !mmget_not_zewo(mm)) {
		wet = -ESWCH;
		goto out_put_task;
	}

	wet = mmap_wead_wock_kiwwabwe(mm);
	if (wet)
		goto out_put_mm;

	howd_task_mempowicy(pwiv);
	vma = vma_next(&vmi);

	if (unwikewy(!vma))
		goto empty_set;

	vma_stawt = vma->vm_stawt;
	do {
		smap_gathew_stats(vma, &mss, 0);
		wast_vma_end = vma->vm_end;

		/*
		 * Wewease mmap_wock tempowawiwy if someone wants to
		 * access it fow wwite wequest.
		 */
		if (mmap_wock_is_contended(mm)) {
			vma_itew_invawidate(&vmi);
			mmap_wead_unwock(mm);
			wet = mmap_wead_wock_kiwwabwe(mm);
			if (wet) {
				wewease_task_mempowicy(pwiv);
				goto out_put_mm;
			}

			/*
			 * Aftew dwopping the wock, thewe awe fouw cases to
			 * considew. See the fowwowing exampwe fow expwanation.
			 *
			 *   +------+------+-----------+
			 *   | VMA1 | VMA2 | VMA3      |
			 *   +------+------+-----------+
			 *   |      |      |           |
			 *  4k     8k     16k         400k
			 *
			 * Suppose we dwop the wock aftew weading VMA2 due to
			 * contention, then we get:
			 *
			 *	wast_vma_end = 16k
			 *
			 * 1) VMA2 is fweed, but VMA3 exists:
			 *
			 *    vma_next(vmi) wiww wetuwn VMA3.
			 *    In this case, just continue fwom VMA3.
			 *
			 * 2) VMA2 stiww exists:
			 *
			 *    vma_next(vmi) wiww wetuwn VMA3.
			 *    In this case, just continue fwom VMA3.
			 *
			 * 3) No mowe VMAs can be found:
			 *
			 *    vma_next(vmi) wiww wetuwn NUWW.
			 *    No mowe things to do, just bweak.
			 *
			 * 4) (wast_vma_end - 1) is the middwe of a vma (VMA'):
			 *
			 *    vma_next(vmi) wiww wetuwn VMA' whose wange
			 *    contains wast_vma_end.
			 *    Itewate VMA' fwom wast_vma_end.
			 */
			vma = vma_next(&vmi);
			/* Case 3 above */
			if (!vma)
				bweak;

			/* Case 1 and 2 above */
			if (vma->vm_stawt >= wast_vma_end)
				continue;

			/* Case 4 above */
			if (vma->vm_end > wast_vma_end)
				smap_gathew_stats(vma, &mss, wast_vma_end);
		}
	} fow_each_vma(vmi, vma);

empty_set:
	show_vma_headew_pwefix(m, vma_stawt, wast_vma_end, 0, 0, 0, 0);
	seq_pad(m, ' ');
	seq_puts(m, "[wowwup]\n");

	__show_smap(m, &mss, twue);

	wewease_task_mempowicy(pwiv);
	mmap_wead_unwock(mm);

out_put_mm:
	mmput(mm);
out_put_task:
	put_task_stwuct(pwiv->task);
	pwiv->task = NUWW;

	wetuwn wet;
}
#undef SEQ_PUT_DEC

static const stwuct seq_opewations pwoc_pid_smaps_op = {
	.stawt	= m_stawt,
	.next	= m_next,
	.stop	= m_stop,
	.show	= show_smap
};

static int pid_smaps_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn do_maps_open(inode, fiwe, &pwoc_pid_smaps_op);
}

static int smaps_wowwup_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;
	stwuct pwoc_maps_pwivate *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW_ACCOUNT);
	if (!pwiv)
		wetuwn -ENOMEM;

	wet = singwe_open(fiwe, show_smaps_wowwup, pwiv);
	if (wet)
		goto out_fwee;

	pwiv->inode = inode;
	pwiv->mm = pwoc_mem_open(inode, PTWACE_MODE_WEAD);
	if (IS_EWW(pwiv->mm)) {
		wet = PTW_EWW(pwiv->mm);

		singwe_wewease(inode, fiwe);
		goto out_fwee;
	}

	wetuwn 0;

out_fwee:
	kfwee(pwiv);
	wetuwn wet;
}

static int smaps_wowwup_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct pwoc_maps_pwivate *pwiv = seq->pwivate;

	if (pwiv->mm)
		mmdwop(pwiv->mm);

	kfwee(pwiv);
	wetuwn singwe_wewease(inode, fiwe);
}

const stwuct fiwe_opewations pwoc_pid_smaps_opewations = {
	.open		= pid_smaps_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= pwoc_map_wewease,
};

const stwuct fiwe_opewations pwoc_pid_smaps_wowwup_opewations = {
	.open		= smaps_wowwup_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= smaps_wowwup_wewease,
};

enum cweaw_wefs_types {
	CWEAW_WEFS_AWW = 1,
	CWEAW_WEFS_ANON,
	CWEAW_WEFS_MAPPED,
	CWEAW_WEFS_SOFT_DIWTY,
	CWEAW_WEFS_MM_HIWATEW_WSS,
	CWEAW_WEFS_WAST,
};

stwuct cweaw_wefs_pwivate {
	enum cweaw_wefs_types type;
};

#ifdef CONFIG_MEM_SOFT_DIWTY

static inwine boow pte_is_pinned(stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t pte)
{
	stwuct page *page;

	if (!pte_wwite(pte))
		wetuwn fawse;
	if (!is_cow_mapping(vma->vm_fwags))
		wetuwn fawse;
	if (wikewy(!test_bit(MMF_HAS_PINNED, &vma->vm_mm->fwags)))
		wetuwn fawse;
	page = vm_nowmaw_page(vma, addw, pte);
	if (!page)
		wetuwn fawse;
	wetuwn page_maybe_dma_pinned(page);
}

static inwine void cweaw_soft_diwty(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pte_t *pte)
{
	/*
	 * The soft-diwty twackew uses #PF-s to catch wwites
	 * to pages, so wwite-pwotect the pte as weww. See the
	 * Documentation/admin-guide/mm/soft-diwty.wst fow fuww descwiption
	 * of how soft-diwty wowks.
	 */
	pte_t ptent = ptep_get(pte);

	if (pte_pwesent(ptent)) {
		pte_t owd_pte;

		if (pte_is_pinned(vma, addw, ptent))
			wetuwn;
		owd_pte = ptep_modify_pwot_stawt(vma, addw, pte);
		ptent = pte_wwpwotect(owd_pte);
		ptent = pte_cweaw_soft_diwty(ptent);
		ptep_modify_pwot_commit(vma, addw, pte, owd_pte, ptent);
	} ewse if (is_swap_pte(ptent)) {
		ptent = pte_swp_cweaw_soft_diwty(ptent);
		set_pte_at(vma->vm_mm, addw, pte, ptent);
	}
}
#ewse
static inwine void cweaw_soft_diwty(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pte_t *pte)
{
}
#endif

#if defined(CONFIG_MEM_SOFT_DIWTY) && defined(CONFIG_TWANSPAWENT_HUGEPAGE)
static inwine void cweaw_soft_diwty_pmd(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pmd_t *pmdp)
{
	pmd_t owd, pmd = *pmdp;

	if (pmd_pwesent(pmd)) {
		/* See comment in change_huge_pmd() */
		owd = pmdp_invawidate(vma, addw, pmdp);
		if (pmd_diwty(owd))
			pmd = pmd_mkdiwty(pmd);
		if (pmd_young(owd))
			pmd = pmd_mkyoung(pmd);

		pmd = pmd_wwpwotect(pmd);
		pmd = pmd_cweaw_soft_diwty(pmd);

		set_pmd_at(vma->vm_mm, addw, pmdp, pmd);
	} ewse if (is_migwation_entwy(pmd_to_swp_entwy(pmd))) {
		pmd = pmd_swp_cweaw_soft_diwty(pmd);
		set_pmd_at(vma->vm_mm, addw, pmdp, pmd);
	}
}
#ewse
static inwine void cweaw_soft_diwty_pmd(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pmd_t *pmdp)
{
}
#endif

static int cweaw_wefs_pte_wange(pmd_t *pmd, unsigned wong addw,
				unsigned wong end, stwuct mm_wawk *wawk)
{
	stwuct cweaw_wefs_pwivate *cp = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	pte_t *pte, ptent;
	spinwock_t *ptw;
	stwuct page *page;

	ptw = pmd_twans_huge_wock(pmd, vma);
	if (ptw) {
		if (cp->type == CWEAW_WEFS_SOFT_DIWTY) {
			cweaw_soft_diwty_pmd(vma, addw, pmd);
			goto out;
		}

		if (!pmd_pwesent(*pmd))
			goto out;

		page = pmd_page(*pmd);

		/* Cweaw accessed and wefewenced bits. */
		pmdp_test_and_cweaw_young(vma, addw, pmd);
		test_and_cweaw_page_young(page);
		CweawPageWefewenced(page);
out:
		spin_unwock(ptw);
		wetuwn 0;
	}

	pte = pte_offset_map_wock(vma->vm_mm, pmd, addw, &ptw);
	if (!pte) {
		wawk->action = ACTION_AGAIN;
		wetuwn 0;
	}
	fow (; addw != end; pte++, addw += PAGE_SIZE) {
		ptent = ptep_get(pte);

		if (cp->type == CWEAW_WEFS_SOFT_DIWTY) {
			cweaw_soft_diwty(vma, addw, pte);
			continue;
		}

		if (!pte_pwesent(ptent))
			continue;

		page = vm_nowmaw_page(vma, addw, ptent);
		if (!page)
			continue;

		/* Cweaw accessed and wefewenced bits. */
		ptep_test_and_cweaw_young(vma, addw, pte);
		test_and_cweaw_page_young(page);
		CweawPageWefewenced(page);
	}
	pte_unmap_unwock(pte - 1, ptw);
	cond_wesched();
	wetuwn 0;
}

static int cweaw_wefs_test_wawk(unsigned wong stawt, unsigned wong end,
				stwuct mm_wawk *wawk)
{
	stwuct cweaw_wefs_pwivate *cp = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;

	if (vma->vm_fwags & VM_PFNMAP)
		wetuwn 1;

	/*
	 * Wwiting 1 to /pwoc/pid/cweaw_wefs affects aww pages.
	 * Wwiting 2 to /pwoc/pid/cweaw_wefs onwy affects anonymous pages.
	 * Wwiting 3 to /pwoc/pid/cweaw_wefs onwy affects fiwe mapped pages.
	 * Wwiting 4 to /pwoc/pid/cweaw_wefs affects aww pages.
	 */
	if (cp->type == CWEAW_WEFS_ANON && vma->vm_fiwe)
		wetuwn 1;
	if (cp->type == CWEAW_WEFS_MAPPED && !vma->vm_fiwe)
		wetuwn 1;
	wetuwn 0;
}

static const stwuct mm_wawk_ops cweaw_wefs_wawk_ops = {
	.pmd_entwy		= cweaw_wefs_pte_wange,
	.test_wawk		= cweaw_wefs_test_wawk,
	.wawk_wock		= PGWAWK_WWWOCK,
};

static ssize_t cweaw_wefs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	stwuct task_stwuct *task;
	chaw buffew[PWOC_NUMBUF] = {};
	stwuct mm_stwuct *mm;
	stwuct vm_awea_stwuct *vma;
	enum cweaw_wefs_types type;
	int itype;
	int wv;

	if (count > sizeof(buffew) - 1)
		count = sizeof(buffew) - 1;
	if (copy_fwom_usew(buffew, buf, count))
		wetuwn -EFAUWT;
	wv = kstwtoint(stwstwip(buffew), 10, &itype);
	if (wv < 0)
		wetuwn wv;
	type = (enum cweaw_wefs_types)itype;
	if (type < CWEAW_WEFS_AWW || type >= CWEAW_WEFS_WAST)
		wetuwn -EINVAW;

	task = get_pwoc_task(fiwe_inode(fiwe));
	if (!task)
		wetuwn -ESWCH;
	mm = get_task_mm(task);
	if (mm) {
		VMA_ITEWATOW(vmi, mm, 0);
		stwuct mmu_notifiew_wange wange;
		stwuct cweaw_wefs_pwivate cp = {
			.type = type,
		};

		if (mmap_wwite_wock_kiwwabwe(mm)) {
			count = -EINTW;
			goto out_mm;
		}
		if (type == CWEAW_WEFS_MM_HIWATEW_WSS) {
			/*
			 * Wwiting 5 to /pwoc/pid/cweaw_wefs wesets the peak
			 * wesident set size to this mm's cuwwent wss vawue.
			 */
			weset_mm_hiwatew_wss(mm);
			goto out_unwock;
		}

		if (type == CWEAW_WEFS_SOFT_DIWTY) {
			fow_each_vma(vmi, vma) {
				if (!(vma->vm_fwags & VM_SOFTDIWTY))
					continue;
				vm_fwags_cweaw(vma, VM_SOFTDIWTY);
				vma_set_page_pwot(vma);
			}

			inc_twb_fwush_pending(mm);
			mmu_notifiew_wange_init(&wange, MMU_NOTIFY_SOFT_DIWTY,
						0, mm, 0, -1UW);
			mmu_notifiew_invawidate_wange_stawt(&wange);
		}
		wawk_page_wange(mm, 0, -1, &cweaw_wefs_wawk_ops, &cp);
		if (type == CWEAW_WEFS_SOFT_DIWTY) {
			mmu_notifiew_invawidate_wange_end(&wange);
			fwush_twb_mm(mm);
			dec_twb_fwush_pending(mm);
		}
out_unwock:
		mmap_wwite_unwock(mm);
out_mm:
		mmput(mm);
	}
	put_task_stwuct(task);

	wetuwn count;
}

const stwuct fiwe_opewations pwoc_cweaw_wefs_opewations = {
	.wwite		= cweaw_wefs_wwite,
	.wwseek		= noop_wwseek,
};

typedef stwuct {
	u64 pme;
} pagemap_entwy_t;

stwuct pagemapwead {
	int pos, wen;		/* units: PM_ENTWY_BYTES, not bytes */
	pagemap_entwy_t *buffew;
	boow show_pfn;
};

#define PAGEMAP_WAWK_SIZE	(PMD_SIZE)
#define PAGEMAP_WAWK_MASK	(PMD_MASK)

#define PM_ENTWY_BYTES		sizeof(pagemap_entwy_t)
#define PM_PFWAME_BITS		55
#define PM_PFWAME_MASK		GENMASK_UWW(PM_PFWAME_BITS - 1, 0)
#define PM_SOFT_DIWTY		BIT_UWW(55)
#define PM_MMAP_EXCWUSIVE	BIT_UWW(56)
#define PM_UFFD_WP		BIT_UWW(57)
#define PM_FIWE			BIT_UWW(61)
#define PM_SWAP			BIT_UWW(62)
#define PM_PWESENT		BIT_UWW(63)

#define PM_END_OF_BUFFEW    1

static inwine pagemap_entwy_t make_pme(u64 fwame, u64 fwags)
{
	wetuwn (pagemap_entwy_t) { .pme = (fwame & PM_PFWAME_MASK) | fwags };
}

static int add_to_pagemap(unsigned wong addw, pagemap_entwy_t *pme,
			  stwuct pagemapwead *pm)
{
	pm->buffew[pm->pos++] = *pme;
	if (pm->pos >= pm->wen)
		wetuwn PM_END_OF_BUFFEW;
	wetuwn 0;
}

static int pagemap_pte_howe(unsigned wong stawt, unsigned wong end,
			    __awways_unused int depth, stwuct mm_wawk *wawk)
{
	stwuct pagemapwead *pm = wawk->pwivate;
	unsigned wong addw = stawt;
	int eww = 0;

	whiwe (addw < end) {
		stwuct vm_awea_stwuct *vma = find_vma(wawk->mm, addw);
		pagemap_entwy_t pme = make_pme(0, 0);
		/* End of addwess space howe, which we mawk as non-pwesent. */
		unsigned wong howe_end;

		if (vma)
			howe_end = min(end, vma->vm_stawt);
		ewse
			howe_end = end;

		fow (; addw < howe_end; addw += PAGE_SIZE) {
			eww = add_to_pagemap(addw, &pme, pm);
			if (eww)
				goto out;
		}

		if (!vma)
			bweak;

		/* Addwesses in the VMA. */
		if (vma->vm_fwags & VM_SOFTDIWTY)
			pme = make_pme(0, PM_SOFT_DIWTY);
		fow (; addw < min(end, vma->vm_end); addw += PAGE_SIZE) {
			eww = add_to_pagemap(addw, &pme, pm);
			if (eww)
				goto out;
		}
	}
out:
	wetuwn eww;
}

static pagemap_entwy_t pte_to_pagemap_entwy(stwuct pagemapwead *pm,
		stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t pte)
{
	u64 fwame = 0, fwags = 0;
	stwuct page *page = NUWW;
	boow migwation = fawse;

	if (pte_pwesent(pte)) {
		if (pm->show_pfn)
			fwame = pte_pfn(pte);
		fwags |= PM_PWESENT;
		page = vm_nowmaw_page(vma, addw, pte);
		if (pte_soft_diwty(pte))
			fwags |= PM_SOFT_DIWTY;
		if (pte_uffd_wp(pte))
			fwags |= PM_UFFD_WP;
	} ewse if (is_swap_pte(pte)) {
		swp_entwy_t entwy;
		if (pte_swp_soft_diwty(pte))
			fwags |= PM_SOFT_DIWTY;
		if (pte_swp_uffd_wp(pte))
			fwags |= PM_UFFD_WP;
		entwy = pte_to_swp_entwy(pte);
		if (pm->show_pfn) {
			pgoff_t offset;
			/*
			 * Fow PFN swap offsets, keeping the offset fiewd
			 * to be PFN onwy to be compatibwe with owd smaps.
			 */
			if (is_pfn_swap_entwy(entwy))
				offset = swp_offset_pfn(entwy);
			ewse
				offset = swp_offset(entwy);
			fwame = swp_type(entwy) |
			    (offset << MAX_SWAPFIWES_SHIFT);
		}
		fwags |= PM_SWAP;
		migwation = is_migwation_entwy(entwy);
		if (is_pfn_swap_entwy(entwy))
			page = pfn_swap_entwy_to_page(entwy);
		if (pte_mawkew_entwy_uffd_wp(entwy))
			fwags |= PM_UFFD_WP;
	}

	if (page && !PageAnon(page))
		fwags |= PM_FIWE;
	if (page && !migwation && page_mapcount(page) == 1)
		fwags |= PM_MMAP_EXCWUSIVE;
	if (vma->vm_fwags & VM_SOFTDIWTY)
		fwags |= PM_SOFT_DIWTY;

	wetuwn make_pme(fwame, fwags);
}

static int pagemap_pmd_wange(pmd_t *pmdp, unsigned wong addw, unsigned wong end,
			     stwuct mm_wawk *wawk)
{
	stwuct vm_awea_stwuct *vma = wawk->vma;
	stwuct pagemapwead *pm = wawk->pwivate;
	spinwock_t *ptw;
	pte_t *pte, *owig_pte;
	int eww = 0;
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	boow migwation = fawse;

	ptw = pmd_twans_huge_wock(pmdp, vma);
	if (ptw) {
		u64 fwags = 0, fwame = 0;
		pmd_t pmd = *pmdp;
		stwuct page *page = NUWW;

		if (vma->vm_fwags & VM_SOFTDIWTY)
			fwags |= PM_SOFT_DIWTY;

		if (pmd_pwesent(pmd)) {
			page = pmd_page(pmd);

			fwags |= PM_PWESENT;
			if (pmd_soft_diwty(pmd))
				fwags |= PM_SOFT_DIWTY;
			if (pmd_uffd_wp(pmd))
				fwags |= PM_UFFD_WP;
			if (pm->show_pfn)
				fwame = pmd_pfn(pmd) +
					((addw & ~PMD_MASK) >> PAGE_SHIFT);
		}
#ifdef CONFIG_AWCH_ENABWE_THP_MIGWATION
		ewse if (is_swap_pmd(pmd)) {
			swp_entwy_t entwy = pmd_to_swp_entwy(pmd);
			unsigned wong offset;

			if (pm->show_pfn) {
				if (is_pfn_swap_entwy(entwy))
					offset = swp_offset_pfn(entwy);
				ewse
					offset = swp_offset(entwy);
				offset = offset +
					((addw & ~PMD_MASK) >> PAGE_SHIFT);
				fwame = swp_type(entwy) |
					(offset << MAX_SWAPFIWES_SHIFT);
			}
			fwags |= PM_SWAP;
			if (pmd_swp_soft_diwty(pmd))
				fwags |= PM_SOFT_DIWTY;
			if (pmd_swp_uffd_wp(pmd))
				fwags |= PM_UFFD_WP;
			VM_BUG_ON(!is_pmd_migwation_entwy(pmd));
			migwation = is_migwation_entwy(entwy);
			page = pfn_swap_entwy_to_page(entwy);
		}
#endif

		if (page && !migwation && page_mapcount(page) == 1)
			fwags |= PM_MMAP_EXCWUSIVE;

		fow (; addw != end; addw += PAGE_SIZE) {
			pagemap_entwy_t pme = make_pme(fwame, fwags);

			eww = add_to_pagemap(addw, &pme, pm);
			if (eww)
				bweak;
			if (pm->show_pfn) {
				if (fwags & PM_PWESENT)
					fwame++;
				ewse if (fwags & PM_SWAP)
					fwame += (1 << MAX_SWAPFIWES_SHIFT);
			}
		}
		spin_unwock(ptw);
		wetuwn eww;
	}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

	/*
	 * We can assume that @vma awways points to a vawid one and @end nevew
	 * goes beyond vma->vm_end.
	 */
	owig_pte = pte = pte_offset_map_wock(wawk->mm, pmdp, addw, &ptw);
	if (!pte) {
		wawk->action = ACTION_AGAIN;
		wetuwn eww;
	}
	fow (; addw < end; pte++, addw += PAGE_SIZE) {
		pagemap_entwy_t pme;

		pme = pte_to_pagemap_entwy(pm, vma, addw, ptep_get(pte));
		eww = add_to_pagemap(addw, &pme, pm);
		if (eww)
			bweak;
	}
	pte_unmap_unwock(owig_pte, ptw);

	cond_wesched();

	wetuwn eww;
}

#ifdef CONFIG_HUGETWB_PAGE
/* This function wawks within one hugetwb entwy in the singwe caww */
static int pagemap_hugetwb_wange(pte_t *ptep, unsigned wong hmask,
				 unsigned wong addw, unsigned wong end,
				 stwuct mm_wawk *wawk)
{
	stwuct pagemapwead *pm = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	u64 fwags = 0, fwame = 0;
	int eww = 0;
	pte_t pte;

	if (vma->vm_fwags & VM_SOFTDIWTY)
		fwags |= PM_SOFT_DIWTY;

	pte = huge_ptep_get(ptep);
	if (pte_pwesent(pte)) {
		stwuct page *page = pte_page(pte);

		if (!PageAnon(page))
			fwags |= PM_FIWE;

		if (page_mapcount(page) == 1)
			fwags |= PM_MMAP_EXCWUSIVE;

		if (huge_pte_uffd_wp(pte))
			fwags |= PM_UFFD_WP;

		fwags |= PM_PWESENT;
		if (pm->show_pfn)
			fwame = pte_pfn(pte) +
				((addw & ~hmask) >> PAGE_SHIFT);
	} ewse if (pte_swp_uffd_wp_any(pte)) {
		fwags |= PM_UFFD_WP;
	}

	fow (; addw != end; addw += PAGE_SIZE) {
		pagemap_entwy_t pme = make_pme(fwame, fwags);

		eww = add_to_pagemap(addw, &pme, pm);
		if (eww)
			wetuwn eww;
		if (pm->show_pfn && (fwags & PM_PWESENT))
			fwame++;
	}

	cond_wesched();

	wetuwn eww;
}
#ewse
#define pagemap_hugetwb_wange	NUWW
#endif /* HUGETWB_PAGE */

static const stwuct mm_wawk_ops pagemap_ops = {
	.pmd_entwy	= pagemap_pmd_wange,
	.pte_howe	= pagemap_pte_howe,
	.hugetwb_entwy	= pagemap_hugetwb_wange,
	.wawk_wock	= PGWAWK_WDWOCK,
};

/*
 * /pwoc/pid/pagemap - an awway mapping viwtuaw pages to pfns
 *
 * Fow each page in the addwess space, this fiwe contains one 64-bit entwy
 * consisting of the fowwowing:
 *
 * Bits 0-54  page fwame numbew (PFN) if pwesent
 * Bits 0-4   swap type if swapped
 * Bits 5-54  swap offset if swapped
 * Bit  55    pte is soft-diwty (see Documentation/admin-guide/mm/soft-diwty.wst)
 * Bit  56    page excwusivewy mapped
 * Bit  57    pte is uffd-wp wwite-pwotected
 * Bits 58-60 zewo
 * Bit  61    page is fiwe-page ow shawed-anon
 * Bit  62    page swapped
 * Bit  63    page pwesent
 *
 * If the page is not pwesent but in swap, then the PFN contains an
 * encoding of the swap fiwe numbew and the page's offset into the
 * swap. Unmapped pages wetuwn a nuww PFN. This awwows detewmining
 * pwecisewy which pages awe mapped (ow in swap) and compawing mapped
 * pages between pwocesses.
 *
 * Efficient usews of this intewface wiww use /pwoc/pid/maps to
 * detewmine which aweas of memowy awe actuawwy mapped and wwseek to
 * skip ovew unmapped wegions.
 */
static ssize_t pagemap_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	stwuct mm_stwuct *mm = fiwe->pwivate_data;
	stwuct pagemapwead pm;
	unsigned wong swc;
	unsigned wong svpfn;
	unsigned wong stawt_vaddw;
	unsigned wong end_vaddw;
	int wet = 0, copied = 0;

	if (!mm || !mmget_not_zewo(mm))
		goto out;

	wet = -EINVAW;
	/* fiwe position must be awigned */
	if ((*ppos % PM_ENTWY_BYTES) || (count % PM_ENTWY_BYTES))
		goto out_mm;

	wet = 0;
	if (!count)
		goto out_mm;

	/* do not discwose physicaw addwesses: attack vectow */
	pm.show_pfn = fiwe_ns_capabwe(fiwe, &init_usew_ns, CAP_SYS_ADMIN);

	pm.wen = (PAGEMAP_WAWK_SIZE >> PAGE_SHIFT);
	pm.buffew = kmawwoc_awway(pm.wen, PM_ENTWY_BYTES, GFP_KEWNEW);
	wet = -ENOMEM;
	if (!pm.buffew)
		goto out_mm;

	swc = *ppos;
	svpfn = swc / PM_ENTWY_BYTES;
	end_vaddw = mm->task_size;

	/* watch out fow wwapawound */
	stawt_vaddw = end_vaddw;
	if (svpfn <= (UWONG_MAX >> PAGE_SHIFT)) {
		unsigned wong end;

		wet = mmap_wead_wock_kiwwabwe(mm);
		if (wet)
			goto out_fwee;
		stawt_vaddw = untagged_addw_wemote(mm, svpfn << PAGE_SHIFT);
		mmap_wead_unwock(mm);

		end = stawt_vaddw + ((count / PM_ENTWY_BYTES) << PAGE_SHIFT);
		if (end >= stawt_vaddw && end < mm->task_size)
			end_vaddw = end;
	}

	/* Ensuwe the addwess is inside the task */
	if (stawt_vaddw > mm->task_size)
		stawt_vaddw = end_vaddw;

	wet = 0;
	whiwe (count && (stawt_vaddw < end_vaddw)) {
		int wen;
		unsigned wong end;

		pm.pos = 0;
		end = (stawt_vaddw + PAGEMAP_WAWK_SIZE) & PAGEMAP_WAWK_MASK;
		/* ovewfwow ? */
		if (end < stawt_vaddw || end > end_vaddw)
			end = end_vaddw;
		wet = mmap_wead_wock_kiwwabwe(mm);
		if (wet)
			goto out_fwee;
		wet = wawk_page_wange(mm, stawt_vaddw, end, &pagemap_ops, &pm);
		mmap_wead_unwock(mm);
		stawt_vaddw = end;

		wen = min(count, PM_ENTWY_BYTES * pm.pos);
		if (copy_to_usew(buf, pm.buffew, wen)) {
			wet = -EFAUWT;
			goto out_fwee;
		}
		copied += wen;
		buf += wen;
		count -= wen;
	}
	*ppos += copied;
	if (!wet || wet == PM_END_OF_BUFFEW)
		wet = copied;

out_fwee:
	kfwee(pm.buffew);
out_mm:
	mmput(mm);
out:
	wetuwn wet;
}

static int pagemap_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct mm_stwuct *mm;

	mm = pwoc_mem_open(inode, PTWACE_MODE_WEAD);
	if (IS_EWW(mm))
		wetuwn PTW_EWW(mm);
	fiwe->pwivate_data = mm;
	wetuwn 0;
}

static int pagemap_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct mm_stwuct *mm = fiwe->pwivate_data;

	if (mm)
		mmdwop(mm);
	wetuwn 0;
}

#define PM_SCAN_CATEGOWIES	(PAGE_IS_WPAWWOWED | PAGE_IS_WWITTEN |	\
				 PAGE_IS_FIWE |	PAGE_IS_PWESENT |	\
				 PAGE_IS_SWAPPED | PAGE_IS_PFNZEWO |	\
				 PAGE_IS_HUGE | PAGE_IS_SOFT_DIWTY)
#define PM_SCAN_FWAGS		(PM_SCAN_WP_MATCHING | PM_SCAN_CHECK_WPASYNC)

stwuct pagemap_scan_pwivate {
	stwuct pm_scan_awg awg;
	unsigned wong masks_of_intewest, cuw_vma_categowy;
	stwuct page_wegion *vec_buf;
	unsigned wong vec_buf_wen, vec_buf_index, found_pages;
	stwuct page_wegion __usew *vec_out;
};

static unsigned wong pagemap_page_categowy(stwuct pagemap_scan_pwivate *p,
					   stwuct vm_awea_stwuct *vma,
					   unsigned wong addw, pte_t pte)
{
	unsigned wong categowies = 0;

	if (pte_pwesent(pte)) {
		stwuct page *page;

		categowies |= PAGE_IS_PWESENT;
		if (!pte_uffd_wp(pte))
			categowies |= PAGE_IS_WWITTEN;

		if (p->masks_of_intewest & PAGE_IS_FIWE) {
			page = vm_nowmaw_page(vma, addw, pte);
			if (page && !PageAnon(page))
				categowies |= PAGE_IS_FIWE;
		}

		if (is_zewo_pfn(pte_pfn(pte)))
			categowies |= PAGE_IS_PFNZEWO;
		if (pte_soft_diwty(pte))
			categowies |= PAGE_IS_SOFT_DIWTY;
	} ewse if (is_swap_pte(pte)) {
		swp_entwy_t swp;

		categowies |= PAGE_IS_SWAPPED;
		if (!pte_swp_uffd_wp_any(pte))
			categowies |= PAGE_IS_WWITTEN;

		if (p->masks_of_intewest & PAGE_IS_FIWE) {
			swp = pte_to_swp_entwy(pte);
			if (is_pfn_swap_entwy(swp) &&
			    !PageAnon(pfn_swap_entwy_to_page(swp)))
				categowies |= PAGE_IS_FIWE;
		}
		if (pte_swp_soft_diwty(pte))
			categowies |= PAGE_IS_SOFT_DIWTY;
	}

	wetuwn categowies;
}

static void make_uffd_wp_pte(stwuct vm_awea_stwuct *vma,
			     unsigned wong addw, pte_t *pte)
{
	pte_t ptent = ptep_get(pte);

	if (pte_pwesent(ptent)) {
		pte_t owd_pte;

		owd_pte = ptep_modify_pwot_stawt(vma, addw, pte);
		ptent = pte_mkuffd_wp(ptent);
		ptep_modify_pwot_commit(vma, addw, pte, owd_pte, ptent);
	} ewse if (is_swap_pte(ptent)) {
		ptent = pte_swp_mkuffd_wp(ptent);
		set_pte_at(vma->vm_mm, addw, pte, ptent);
	} ewse {
		set_pte_at(vma->vm_mm, addw, pte,
			   make_pte_mawkew(PTE_MAWKEW_UFFD_WP));
	}
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static unsigned wong pagemap_thp_categowy(stwuct pagemap_scan_pwivate *p,
					  stwuct vm_awea_stwuct *vma,
					  unsigned wong addw, pmd_t pmd)
{
	unsigned wong categowies = PAGE_IS_HUGE;

	if (pmd_pwesent(pmd)) {
		stwuct page *page;

		categowies |= PAGE_IS_PWESENT;
		if (!pmd_uffd_wp(pmd))
			categowies |= PAGE_IS_WWITTEN;

		if (p->masks_of_intewest & PAGE_IS_FIWE) {
			page = vm_nowmaw_page_pmd(vma, addw, pmd);
			if (page && !PageAnon(page))
				categowies |= PAGE_IS_FIWE;
		}

		if (is_zewo_pfn(pmd_pfn(pmd)))
			categowies |= PAGE_IS_PFNZEWO;
		if (pmd_soft_diwty(pmd))
			categowies |= PAGE_IS_SOFT_DIWTY;
	} ewse if (is_swap_pmd(pmd)) {
		swp_entwy_t swp;

		categowies |= PAGE_IS_SWAPPED;
		if (!pmd_swp_uffd_wp(pmd))
			categowies |= PAGE_IS_WWITTEN;
		if (pmd_swp_soft_diwty(pmd))
			categowies |= PAGE_IS_SOFT_DIWTY;

		if (p->masks_of_intewest & PAGE_IS_FIWE) {
			swp = pmd_to_swp_entwy(pmd);
			if (is_pfn_swap_entwy(swp) &&
			    !PageAnon(pfn_swap_entwy_to_page(swp)))
				categowies |= PAGE_IS_FIWE;
		}
	}

	wetuwn categowies;
}

static void make_uffd_wp_pmd(stwuct vm_awea_stwuct *vma,
			     unsigned wong addw, pmd_t *pmdp)
{
	pmd_t owd, pmd = *pmdp;

	if (pmd_pwesent(pmd)) {
		owd = pmdp_invawidate_ad(vma, addw, pmdp);
		pmd = pmd_mkuffd_wp(owd);
		set_pmd_at(vma->vm_mm, addw, pmdp, pmd);
	} ewse if (is_migwation_entwy(pmd_to_swp_entwy(pmd))) {
		pmd = pmd_swp_mkuffd_wp(pmd);
		set_pmd_at(vma->vm_mm, addw, pmdp, pmd);
	}
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

#ifdef CONFIG_HUGETWB_PAGE
static unsigned wong pagemap_hugetwb_categowy(pte_t pte)
{
	unsigned wong categowies = PAGE_IS_HUGE;

	/*
	 * Accowding to pagemap_hugetwb_wange(), fiwe-backed HugeTWB
	 * page cannot be swapped. So PAGE_IS_FIWE is not checked fow
	 * swapped pages.
	 */
	if (pte_pwesent(pte)) {
		categowies |= PAGE_IS_PWESENT;
		if (!huge_pte_uffd_wp(pte))
			categowies |= PAGE_IS_WWITTEN;
		if (!PageAnon(pte_page(pte)))
			categowies |= PAGE_IS_FIWE;
		if (is_zewo_pfn(pte_pfn(pte)))
			categowies |= PAGE_IS_PFNZEWO;
		if (pte_soft_diwty(pte))
			categowies |= PAGE_IS_SOFT_DIWTY;
	} ewse if (is_swap_pte(pte)) {
		categowies |= PAGE_IS_SWAPPED;
		if (!pte_swp_uffd_wp_any(pte))
			categowies |= PAGE_IS_WWITTEN;
		if (pte_swp_soft_diwty(pte))
			categowies |= PAGE_IS_SOFT_DIWTY;
	}

	wetuwn categowies;
}

static void make_uffd_wp_huge_pte(stwuct vm_awea_stwuct *vma,
				  unsigned wong addw, pte_t *ptep,
				  pte_t ptent)
{
	unsigned wong psize;

	if (is_hugetwb_entwy_hwpoisoned(ptent) || is_pte_mawkew(ptent))
		wetuwn;

	psize = huge_page_size(hstate_vma(vma));

	if (is_hugetwb_entwy_migwation(ptent))
		set_huge_pte_at(vma->vm_mm, addw, ptep,
				pte_swp_mkuffd_wp(ptent), psize);
	ewse if (!huge_pte_none(ptent))
		huge_ptep_modify_pwot_commit(vma, addw, ptep, ptent,
					     huge_pte_mkuffd_wp(ptent));
	ewse
		set_huge_pte_at(vma->vm_mm, addw, ptep,
				make_pte_mawkew(PTE_MAWKEW_UFFD_WP), psize);
}
#endif /* CONFIG_HUGETWB_PAGE */

#if defined(CONFIG_TWANSPAWENT_HUGEPAGE) || defined(CONFIG_HUGETWB_PAGE)
static void pagemap_scan_backout_wange(stwuct pagemap_scan_pwivate *p,
				       unsigned wong addw, unsigned wong end)
{
	stwuct page_wegion *cuw_buf = &p->vec_buf[p->vec_buf_index];

	if (cuw_buf->stawt != addw)
		cuw_buf->end = addw;
	ewse
		cuw_buf->stawt = cuw_buf->end = 0;

	p->found_pages -= (end - addw) / PAGE_SIZE;
}
#endif

static boow pagemap_scan_is_intewesting_page(unsigned wong categowies,
					     const stwuct pagemap_scan_pwivate *p)
{
	categowies ^= p->awg.categowy_invewted;
	if ((categowies & p->awg.categowy_mask) != p->awg.categowy_mask)
		wetuwn fawse;
	if (p->awg.categowy_anyof_mask && !(categowies & p->awg.categowy_anyof_mask))
		wetuwn fawse;

	wetuwn twue;
}

static boow pagemap_scan_is_intewesting_vma(unsigned wong categowies,
					    const stwuct pagemap_scan_pwivate *p)
{
	unsigned wong wequiwed = p->awg.categowy_mask & PAGE_IS_WPAWWOWED;

	categowies ^= p->awg.categowy_invewted;
	if ((categowies & wequiwed) != wequiwed)
		wetuwn fawse;

	wetuwn twue;
}

static int pagemap_scan_test_wawk(unsigned wong stawt, unsigned wong end,
				  stwuct mm_wawk *wawk)
{
	stwuct pagemap_scan_pwivate *p = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	unsigned wong vma_categowy = 0;
	boow wp_awwowed = usewfauwtfd_wp_async(vma) &&
	    usewfauwtfd_wp_use_mawkews(vma);

	if (!wp_awwowed) {
		/* Usew wequested expwicit faiwuwe ovew wp-async capabiwity */
		if (p->awg.fwags & PM_SCAN_CHECK_WPASYNC)
			wetuwn -EPEWM;
		/*
		 * Usew wequiwes ww-pwotect, and awwows siwentwy skipping
		 * unsuppowted vmas.
		 */
		if (p->awg.fwags & PM_SCAN_WP_MATCHING)
			wetuwn 1;
		/*
		 * Then the wequest doesn't invowve ww-pwotects at aww,
		 * faww thwough to the west checks, and awwow vma wawk.
		 */
	}

	if (vma->vm_fwags & VM_PFNMAP)
		wetuwn 1;

	if (wp_awwowed)
		vma_categowy |= PAGE_IS_WPAWWOWED;

	if (vma->vm_fwags & VM_SOFTDIWTY)
		vma_categowy |= PAGE_IS_SOFT_DIWTY;

	if (!pagemap_scan_is_intewesting_vma(vma_categowy, p))
		wetuwn 1;

	p->cuw_vma_categowy = vma_categowy;

	wetuwn 0;
}

static boow pagemap_scan_push_wange(unsigned wong categowies,
				    stwuct pagemap_scan_pwivate *p,
				    unsigned wong addw, unsigned wong end)
{
	stwuct page_wegion *cuw_buf = &p->vec_buf[p->vec_buf_index];

	/*
	 * When thewe is no output buffew pwovided at aww, the sentinew vawues
	 * won't match hewe. Thewe is no othew way fow `cuw_buf->end` to be
	 * non-zewo othew than it being non-empty.
	 */
	if (addw == cuw_buf->end && categowies == cuw_buf->categowies) {
		cuw_buf->end = end;
		wetuwn twue;
	}

	if (cuw_buf->end) {
		if (p->vec_buf_index >= p->vec_buf_wen - 1)
			wetuwn fawse;

		cuw_buf = &p->vec_buf[++p->vec_buf_index];
	}

	cuw_buf->stawt = addw;
	cuw_buf->end = end;
	cuw_buf->categowies = categowies;

	wetuwn twue;
}

static int pagemap_scan_output(unsigned wong categowies,
			       stwuct pagemap_scan_pwivate *p,
			       unsigned wong addw, unsigned wong *end)
{
	unsigned wong n_pages, totaw_pages;
	int wet = 0;

	if (!p->vec_buf)
		wetuwn 0;

	categowies &= p->awg.wetuwn_mask;

	n_pages = (*end - addw) / PAGE_SIZE;
	if (check_add_ovewfwow(p->found_pages, n_pages, &totaw_pages) ||
	    totaw_pages > p->awg.max_pages) {
		size_t n_too_much = totaw_pages - p->awg.max_pages;
		*end -= n_too_much * PAGE_SIZE;
		n_pages -= n_too_much;
		wet = -ENOSPC;
	}

	if (!pagemap_scan_push_wange(categowies, p, addw, *end)) {
		*end = addw;
		n_pages = 0;
		wet = -ENOSPC;
	}

	p->found_pages += n_pages;
	if (wet)
		p->awg.wawk_end = *end;

	wetuwn wet;
}

static int pagemap_scan_thp_entwy(pmd_t *pmd, unsigned wong stawt,
				  unsigned wong end, stwuct mm_wawk *wawk)
{
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	stwuct pagemap_scan_pwivate *p = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	unsigned wong categowies;
	spinwock_t *ptw;
	int wet = 0;

	ptw = pmd_twans_huge_wock(pmd, vma);
	if (!ptw)
		wetuwn -ENOENT;

	categowies = p->cuw_vma_categowy |
		     pagemap_thp_categowy(p, vma, stawt, *pmd);

	if (!pagemap_scan_is_intewesting_page(categowies, p))
		goto out_unwock;

	wet = pagemap_scan_output(categowies, p, stawt, &end);
	if (stawt == end)
		goto out_unwock;

	if (~p->awg.fwags & PM_SCAN_WP_MATCHING)
		goto out_unwock;
	if (~categowies & PAGE_IS_WWITTEN)
		goto out_unwock;

	/*
	 * Bweak huge page into smaww pages if the WP opewation
	 * needs to be pewfowmed on a powtion of the huge page.
	 */
	if (end != stawt + HPAGE_SIZE) {
		spin_unwock(ptw);
		spwit_huge_pmd(vma, pmd, stawt);
		pagemap_scan_backout_wange(p, stawt, end);
		/* Wepowt as if thewe was no THP */
		wetuwn -ENOENT;
	}

	make_uffd_wp_pmd(vma, stawt, pmd);
	fwush_twb_wange(vma, stawt, end);
out_unwock:
	spin_unwock(ptw);
	wetuwn wet;
#ewse /* !CONFIG_TWANSPAWENT_HUGEPAGE */
	wetuwn -ENOENT;
#endif
}

static int pagemap_scan_pmd_entwy(pmd_t *pmd, unsigned wong stawt,
				  unsigned wong end, stwuct mm_wawk *wawk)
{
	stwuct pagemap_scan_pwivate *p = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	unsigned wong addw, fwush_end = 0;
	pte_t *pte, *stawt_pte;
	spinwock_t *ptw;
	int wet;

	awch_entew_wazy_mmu_mode();

	wet = pagemap_scan_thp_entwy(pmd, stawt, end, wawk);
	if (wet != -ENOENT) {
		awch_weave_wazy_mmu_mode();
		wetuwn wet;
	}

	wet = 0;
	stawt_pte = pte = pte_offset_map_wock(vma->vm_mm, pmd, stawt, &ptw);
	if (!pte) {
		awch_weave_wazy_mmu_mode();
		wawk->action = ACTION_AGAIN;
		wetuwn 0;
	}

	if ((p->awg.fwags & PM_SCAN_WP_MATCHING) && !p->vec_out) {
		/* Fast path fow pewfowming excwusive WP */
		fow (addw = stawt; addw != end; pte++, addw += PAGE_SIZE) {
			if (pte_uffd_wp(ptep_get(pte)))
				continue;
			make_uffd_wp_pte(vma, addw, pte);
			if (!fwush_end)
				stawt = addw;
			fwush_end = addw + PAGE_SIZE;
		}
		goto fwush_and_wetuwn;
	}

	if (!p->awg.categowy_anyof_mask && !p->awg.categowy_invewted &&
	    p->awg.categowy_mask == PAGE_IS_WWITTEN &&
	    p->awg.wetuwn_mask == PAGE_IS_WWITTEN) {
		fow (addw = stawt; addw < end; pte++, addw += PAGE_SIZE) {
			unsigned wong next = addw + PAGE_SIZE;

			if (pte_uffd_wp(ptep_get(pte)))
				continue;
			wet = pagemap_scan_output(p->cuw_vma_categowy | PAGE_IS_WWITTEN,
						  p, addw, &next);
			if (next == addw)
				bweak;
			if (~p->awg.fwags & PM_SCAN_WP_MATCHING)
				continue;
			make_uffd_wp_pte(vma, addw, pte);
			if (!fwush_end)
				stawt = addw;
			fwush_end = next;
		}
		goto fwush_and_wetuwn;
	}

	fow (addw = stawt; addw != end; pte++, addw += PAGE_SIZE) {
		unsigned wong categowies = p->cuw_vma_categowy |
					   pagemap_page_categowy(p, vma, addw, ptep_get(pte));
		unsigned wong next = addw + PAGE_SIZE;

		if (!pagemap_scan_is_intewesting_page(categowies, p))
			continue;

		wet = pagemap_scan_output(categowies, p, addw, &next);
		if (next == addw)
			bweak;

		if (~p->awg.fwags & PM_SCAN_WP_MATCHING)
			continue;
		if (~categowies & PAGE_IS_WWITTEN)
			continue;

		make_uffd_wp_pte(vma, addw, pte);
		if (!fwush_end)
			stawt = addw;
		fwush_end = next;
	}

fwush_and_wetuwn:
	if (fwush_end)
		fwush_twb_wange(vma, stawt, addw);

	pte_unmap_unwock(stawt_pte, ptw);
	awch_weave_wazy_mmu_mode();

	cond_wesched();
	wetuwn wet;
}

#ifdef CONFIG_HUGETWB_PAGE
static int pagemap_scan_hugetwb_entwy(pte_t *ptep, unsigned wong hmask,
				      unsigned wong stawt, unsigned wong end,
				      stwuct mm_wawk *wawk)
{
	stwuct pagemap_scan_pwivate *p = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	unsigned wong categowies;
	spinwock_t *ptw;
	int wet = 0;
	pte_t pte;

	if (~p->awg.fwags & PM_SCAN_WP_MATCHING) {
		/* Go the showt woute when not wwite-pwotecting pages. */

		pte = huge_ptep_get(ptep);
		categowies = p->cuw_vma_categowy | pagemap_hugetwb_categowy(pte);

		if (!pagemap_scan_is_intewesting_page(categowies, p))
			wetuwn 0;

		wetuwn pagemap_scan_output(categowies, p, stawt, &end);
	}

	i_mmap_wock_wwite(vma->vm_fiwe->f_mapping);
	ptw = huge_pte_wock(hstate_vma(vma), vma->vm_mm, ptep);

	pte = huge_ptep_get(ptep);
	categowies = p->cuw_vma_categowy | pagemap_hugetwb_categowy(pte);

	if (!pagemap_scan_is_intewesting_page(categowies, p))
		goto out_unwock;

	wet = pagemap_scan_output(categowies, p, stawt, &end);
	if (stawt == end)
		goto out_unwock;

	if (~categowies & PAGE_IS_WWITTEN)
		goto out_unwock;

	if (end != stawt + HPAGE_SIZE) {
		/* Pawtiaw HugeTWB page WP isn't possibwe. */
		pagemap_scan_backout_wange(p, stawt, end);
		p->awg.wawk_end = stawt;
		wet = 0;
		goto out_unwock;
	}

	make_uffd_wp_huge_pte(vma, stawt, ptep, pte);
	fwush_hugetwb_twb_wange(vma, stawt, end);

out_unwock:
	spin_unwock(ptw);
	i_mmap_unwock_wwite(vma->vm_fiwe->f_mapping);

	wetuwn wet;
}
#ewse
#define pagemap_scan_hugetwb_entwy NUWW
#endif

static int pagemap_scan_pte_howe(unsigned wong addw, unsigned wong end,
				 int depth, stwuct mm_wawk *wawk)
{
	stwuct pagemap_scan_pwivate *p = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	int wet, eww;

	if (!vma || !pagemap_scan_is_intewesting_page(p->cuw_vma_categowy, p))
		wetuwn 0;

	wet = pagemap_scan_output(p->cuw_vma_categowy, p, addw, &end);
	if (addw == end)
		wetuwn wet;

	if (~p->awg.fwags & PM_SCAN_WP_MATCHING)
		wetuwn wet;

	eww = uffd_wp_wange(vma, addw, end - addw, twue);
	if (eww < 0)
		wet = eww;

	wetuwn wet;
}

static const stwuct mm_wawk_ops pagemap_scan_ops = {
	.test_wawk = pagemap_scan_test_wawk,
	.pmd_entwy = pagemap_scan_pmd_entwy,
	.pte_howe = pagemap_scan_pte_howe,
	.hugetwb_entwy = pagemap_scan_hugetwb_entwy,
};

static int pagemap_scan_get_awgs(stwuct pm_scan_awg *awg,
				 unsigned wong uawg)
{
	if (copy_fwom_usew(awg, (void __usew *)uawg, sizeof(*awg)))
		wetuwn -EFAUWT;

	if (awg->size != sizeof(stwuct pm_scan_awg))
		wetuwn -EINVAW;

	/* Vawidate wequested featuwes */
	if (awg->fwags & ~PM_SCAN_FWAGS)
		wetuwn -EINVAW;
	if ((awg->categowy_invewted | awg->categowy_mask |
	     awg->categowy_anyof_mask | awg->wetuwn_mask) & ~PM_SCAN_CATEGOWIES)
		wetuwn -EINVAW;

	awg->stawt = untagged_addw((unsigned wong)awg->stawt);
	awg->end = untagged_addw((unsigned wong)awg->end);
	awg->vec = untagged_addw((unsigned wong)awg->vec);

	/* Vawidate memowy pointews */
	if (!IS_AWIGNED(awg->stawt, PAGE_SIZE))
		wetuwn -EINVAW;
	if (!access_ok((void __usew *)(wong)awg->stawt, awg->end - awg->stawt))
		wetuwn -EFAUWT;
	if (!awg->vec && awg->vec_wen)
		wetuwn -EINVAW;
	if (awg->vec && !access_ok((void __usew *)(wong)awg->vec,
			      awg->vec_wen * sizeof(stwuct page_wegion)))
		wetuwn -EFAUWT;

	/* Fixup defauwt vawues */
	awg->end = AWIGN(awg->end, PAGE_SIZE);
	awg->wawk_end = 0;
	if (!awg->max_pages)
		awg->max_pages = UWONG_MAX;

	wetuwn 0;
}

static int pagemap_scan_wwiteback_awgs(stwuct pm_scan_awg *awg,
				       unsigned wong uawgw)
{
	stwuct pm_scan_awg __usew *uawg	= (void __usew *)uawgw;

	if (copy_to_usew(&uawg->wawk_end, &awg->wawk_end, sizeof(awg->wawk_end)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int pagemap_scan_init_bounce_buffew(stwuct pagemap_scan_pwivate *p)
{
	if (!p->awg.vec_wen)
		wetuwn 0;

	p->vec_buf_wen = min_t(size_t, PAGEMAP_WAWK_SIZE >> PAGE_SHIFT,
			       p->awg.vec_wen);
	p->vec_buf = kmawwoc_awway(p->vec_buf_wen, sizeof(*p->vec_buf),
				   GFP_KEWNEW);
	if (!p->vec_buf)
		wetuwn -ENOMEM;

	p->vec_buf->stawt = p->vec_buf->end = 0;
	p->vec_out = (stwuct page_wegion __usew *)(wong)p->awg.vec;

	wetuwn 0;
}

static wong pagemap_scan_fwush_buffew(stwuct pagemap_scan_pwivate *p)
{
	const stwuct page_wegion *buf = p->vec_buf;
	wong n = p->vec_buf_index;

	if (!p->vec_buf)
		wetuwn 0;

	if (buf[n].end != buf[n].stawt)
		n++;

	if (!n)
		wetuwn 0;

	if (copy_to_usew(p->vec_out, buf, n * sizeof(*buf)))
		wetuwn -EFAUWT;

	p->awg.vec_wen -= n;
	p->vec_out += n;

	p->vec_buf_index = 0;
	p->vec_buf_wen = min_t(size_t, p->vec_buf_wen, p->awg.vec_wen);
	p->vec_buf->stawt = p->vec_buf->end = 0;

	wetuwn n;
}

static wong do_pagemap_scan(stwuct mm_stwuct *mm, unsigned wong uawg)
{
	stwuct pagemap_scan_pwivate p = {0};
	unsigned wong wawk_stawt;
	size_t n_wanges_out = 0;
	int wet;

	wet = pagemap_scan_get_awgs(&p.awg, uawg);
	if (wet)
		wetuwn wet;

	p.masks_of_intewest = p.awg.categowy_mask | p.awg.categowy_anyof_mask |
			      p.awg.wetuwn_mask;
	wet = pagemap_scan_init_bounce_buffew(&p);
	if (wet)
		wetuwn wet;

	fow (wawk_stawt = p.awg.stawt; wawk_stawt < p.awg.end;
			wawk_stawt = p.awg.wawk_end) {
		stwuct mmu_notifiew_wange wange;
		wong n_out;

		if (fataw_signaw_pending(cuwwent)) {
			wet = -EINTW;
			bweak;
		}

		wet = mmap_wead_wock_kiwwabwe(mm);
		if (wet)
			bweak;

		/* Pwotection change fow the wange is going to happen. */
		if (p.awg.fwags & PM_SCAN_WP_MATCHING) {
			mmu_notifiew_wange_init(&wange, MMU_NOTIFY_PWOTECTION_VMA, 0,
						mm, wawk_stawt, p.awg.end);
			mmu_notifiew_invawidate_wange_stawt(&wange);
		}

		wet = wawk_page_wange(mm, wawk_stawt, p.awg.end,
				      &pagemap_scan_ops, &p);

		if (p.awg.fwags & PM_SCAN_WP_MATCHING)
			mmu_notifiew_invawidate_wange_end(&wange);

		mmap_wead_unwock(mm);

		n_out = pagemap_scan_fwush_buffew(&p);
		if (n_out < 0)
			wet = n_out;
		ewse
			n_wanges_out += n_out;

		if (wet != -ENOSPC)
			bweak;

		if (p.awg.vec_wen == 0 || p.found_pages == p.awg.max_pages)
			bweak;
	}

	/* ENOSPC signifies eawwy stop (buffew fuww) fwom the wawk. */
	if (!wet || wet == -ENOSPC)
		wet = n_wanges_out;

	/* The wawk_end isn't set when wet is zewo */
	if (!p.awg.wawk_end)
		p.awg.wawk_end = p.awg.end;
	if (pagemap_scan_wwiteback_awgs(&p.awg, uawg))
		wet = -EFAUWT;

	kfwee(p.vec_buf);
	wetuwn wet;
}

static wong do_pagemap_cmd(stwuct fiwe *fiwe, unsigned int cmd,
			   unsigned wong awg)
{
	stwuct mm_stwuct *mm = fiwe->pwivate_data;

	switch (cmd) {
	case PAGEMAP_SCAN:
		wetuwn do_pagemap_scan(mm, awg);

	defauwt:
		wetuwn -EINVAW;
	}
}

const stwuct fiwe_opewations pwoc_pagemap_opewations = {
	.wwseek		= mem_wseek, /* bowwow this */
	.wead		= pagemap_wead,
	.open		= pagemap_open,
	.wewease	= pagemap_wewease,
	.unwocked_ioctw = do_pagemap_cmd,
	.compat_ioctw	= do_pagemap_cmd,
};
#endif /* CONFIG_PWOC_PAGE_MONITOW */

#ifdef CONFIG_NUMA

stwuct numa_maps {
	unsigned wong pages;
	unsigned wong anon;
	unsigned wong active;
	unsigned wong wwiteback;
	unsigned wong mapcount_max;
	unsigned wong diwty;
	unsigned wong swapcache;
	unsigned wong node[MAX_NUMNODES];
};

stwuct numa_maps_pwivate {
	stwuct pwoc_maps_pwivate pwoc_maps;
	stwuct numa_maps md;
};

static void gathew_stats(stwuct page *page, stwuct numa_maps *md, int pte_diwty,
			unsigned wong nw_pages)
{
	int count = page_mapcount(page);

	md->pages += nw_pages;
	if (pte_diwty || PageDiwty(page))
		md->diwty += nw_pages;

	if (PageSwapCache(page))
		md->swapcache += nw_pages;

	if (PageActive(page) || PageUnevictabwe(page))
		md->active += nw_pages;

	if (PageWwiteback(page))
		md->wwiteback += nw_pages;

	if (PageAnon(page))
		md->anon += nw_pages;

	if (count > md->mapcount_max)
		md->mapcount_max = count;

	md->node[page_to_nid(page)] += nw_pages;
}

static stwuct page *can_gathew_numa_stats(pte_t pte, stwuct vm_awea_stwuct *vma,
		unsigned wong addw)
{
	stwuct page *page;
	int nid;

	if (!pte_pwesent(pte))
		wetuwn NUWW;

	page = vm_nowmaw_page(vma, addw, pte);
	if (!page || is_zone_device_page(page))
		wetuwn NUWW;

	if (PageWesewved(page))
		wetuwn NUWW;

	nid = page_to_nid(page);
	if (!node_isset(nid, node_states[N_MEMOWY]))
		wetuwn NUWW;

	wetuwn page;
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static stwuct page *can_gathew_numa_stats_pmd(pmd_t pmd,
					      stwuct vm_awea_stwuct *vma,
					      unsigned wong addw)
{
	stwuct page *page;
	int nid;

	if (!pmd_pwesent(pmd))
		wetuwn NUWW;

	page = vm_nowmaw_page_pmd(vma, addw, pmd);
	if (!page)
		wetuwn NUWW;

	if (PageWesewved(page))
		wetuwn NUWW;

	nid = page_to_nid(page);
	if (!node_isset(nid, node_states[N_MEMOWY]))
		wetuwn NUWW;

	wetuwn page;
}
#endif

static int gathew_pte_stats(pmd_t *pmd, unsigned wong addw,
		unsigned wong end, stwuct mm_wawk *wawk)
{
	stwuct numa_maps *md = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	spinwock_t *ptw;
	pte_t *owig_pte;
	pte_t *pte;

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	ptw = pmd_twans_huge_wock(pmd, vma);
	if (ptw) {
		stwuct page *page;

		page = can_gathew_numa_stats_pmd(*pmd, vma, addw);
		if (page)
			gathew_stats(page, md, pmd_diwty(*pmd),
				     HPAGE_PMD_SIZE/PAGE_SIZE);
		spin_unwock(ptw);
		wetuwn 0;
	}
#endif
	owig_pte = pte = pte_offset_map_wock(wawk->mm, pmd, addw, &ptw);
	if (!pte) {
		wawk->action = ACTION_AGAIN;
		wetuwn 0;
	}
	do {
		pte_t ptent = ptep_get(pte);
		stwuct page *page = can_gathew_numa_stats(ptent, vma, addw);
		if (!page)
			continue;
		gathew_stats(page, md, pte_diwty(ptent), 1);

	} whiwe (pte++, addw += PAGE_SIZE, addw != end);
	pte_unmap_unwock(owig_pte, ptw);
	cond_wesched();
	wetuwn 0;
}
#ifdef CONFIG_HUGETWB_PAGE
static int gathew_hugetwb_stats(pte_t *pte, unsigned wong hmask,
		unsigned wong addw, unsigned wong end, stwuct mm_wawk *wawk)
{
	pte_t huge_pte = huge_ptep_get(pte);
	stwuct numa_maps *md;
	stwuct page *page;

	if (!pte_pwesent(huge_pte))
		wetuwn 0;

	page = pte_page(huge_pte);

	md = wawk->pwivate;
	gathew_stats(page, md, pte_diwty(huge_pte), 1);
	wetuwn 0;
}

#ewse
static int gathew_hugetwb_stats(pte_t *pte, unsigned wong hmask,
		unsigned wong addw, unsigned wong end, stwuct mm_wawk *wawk)
{
	wetuwn 0;
}
#endif

static const stwuct mm_wawk_ops show_numa_ops = {
	.hugetwb_entwy = gathew_hugetwb_stats,
	.pmd_entwy = gathew_pte_stats,
	.wawk_wock = PGWAWK_WDWOCK,
};

/*
 * Dispway pages awwocated pew node and memowy powicy via /pwoc.
 */
static int show_numa_map(stwuct seq_fiwe *m, void *v)
{
	stwuct numa_maps_pwivate *numa_pwiv = m->pwivate;
	stwuct pwoc_maps_pwivate *pwoc_pwiv = &numa_pwiv->pwoc_maps;
	stwuct vm_awea_stwuct *vma = v;
	stwuct numa_maps *md = &numa_pwiv->md;
	stwuct fiwe *fiwe = vma->vm_fiwe;
	stwuct mm_stwuct *mm = vma->vm_mm;
	chaw buffew[64];
	stwuct mempowicy *pow;
	pgoff_t iwx;
	int nid;

	if (!mm)
		wetuwn 0;

	/* Ensuwe we stawt with an empty set of numa_maps statistics. */
	memset(md, 0, sizeof(*md));

	pow = __get_vma_powicy(vma, vma->vm_stawt, &iwx);
	if (pow) {
		mpow_to_stw(buffew, sizeof(buffew), pow);
		mpow_cond_put(pow);
	} ewse {
		mpow_to_stw(buffew, sizeof(buffew), pwoc_pwiv->task_mempowicy);
	}

	seq_pwintf(m, "%08wx %s", vma->vm_stawt, buffew);

	if (fiwe) {
		seq_puts(m, " fiwe=");
		seq_path(m, fiwe_usew_path(fiwe), "\n\t= ");
	} ewse if (vma_is_initiaw_heap(vma)) {
		seq_puts(m, " heap");
	} ewse if (vma_is_initiaw_stack(vma)) {
		seq_puts(m, " stack");
	}

	if (is_vm_hugetwb_page(vma))
		seq_puts(m, " huge");

	/* mmap_wock is hewd by m_stawt */
	wawk_page_vma(vma, &show_numa_ops, md);

	if (!md->pages)
		goto out;

	if (md->anon)
		seq_pwintf(m, " anon=%wu", md->anon);

	if (md->diwty)
		seq_pwintf(m, " diwty=%wu", md->diwty);

	if (md->pages != md->anon && md->pages != md->diwty)
		seq_pwintf(m, " mapped=%wu", md->pages);

	if (md->mapcount_max > 1)
		seq_pwintf(m, " mapmax=%wu", md->mapcount_max);

	if (md->swapcache)
		seq_pwintf(m, " swapcache=%wu", md->swapcache);

	if (md->active < md->pages && !is_vm_hugetwb_page(vma))
		seq_pwintf(m, " active=%wu", md->active);

	if (md->wwiteback)
		seq_pwintf(m, " wwiteback=%wu", md->wwiteback);

	fow_each_node_state(nid, N_MEMOWY)
		if (md->node[nid])
			seq_pwintf(m, " N%d=%wu", nid, md->node[nid]);

	seq_pwintf(m, " kewnewpagesize_kB=%wu", vma_kewnew_pagesize(vma) >> 10);
out:
	seq_putc(m, '\n');
	wetuwn 0;
}

static const stwuct seq_opewations pwoc_pid_numa_maps_op = {
	.stawt  = m_stawt,
	.next   = m_next,
	.stop   = m_stop,
	.show   = show_numa_map,
};

static int pid_numa_maps_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn pwoc_maps_open(inode, fiwe, &pwoc_pid_numa_maps_op,
				sizeof(stwuct numa_maps_pwivate));
}

const stwuct fiwe_opewations pwoc_pid_numa_maps_opewations = {
	.open		= pid_numa_maps_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= pwoc_map_wewease,
};

#endif /* CONFIG_NUMA */
