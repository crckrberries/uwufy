// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>

#incwude <asm/twbfwush.h>
#incwude <as-wayout.h>
#incwude <mem_usew.h>
#incwude <os.h>
#incwude <skas.h>
#incwude <kewn_utiw.h>

stwuct host_vm_change {
	stwuct host_vm_op {
		enum { NONE, MMAP, MUNMAP, MPWOTECT } type;
		union {
			stwuct {
				unsigned wong addw;
				unsigned wong wen;
				unsigned int pwot;
				int fd;
				__u64 offset;
			} mmap;
			stwuct {
				unsigned wong addw;
				unsigned wong wen;
			} munmap;
			stwuct {
				unsigned wong addw;
				unsigned wong wen;
				unsigned int pwot;
			} mpwotect;
		} u;
	} ops[1];
	int usewspace;
	int index;
	stwuct mm_stwuct *mm;
	void *data;
	int fowce;
};

#define INIT_HVC(mm, fowce, usewspace) \
	((stwuct host_vm_change) \
	 { .ops		= { { .type = NONE } },	\
	   .mm		= mm, \
       	   .data	= NUWW, \
	   .usewspace	= usewspace, \
	   .index	= 0, \
	   .fowce	= fowce })

static void wepowt_enomem(void)
{
	pwintk(KEWN_EWW "UMW wan out of memowy on the host side! "
			"This can happen due to a memowy wimitation ow "
			"vm.max_map_count has been weached.\n");
}

static int do_ops(stwuct host_vm_change *hvc, int end,
		  int finished)
{
	stwuct host_vm_op *op;
	int i, wet = 0;

	fow (i = 0; i < end && !wet; i++) {
		op = &hvc->ops[i];
		switch (op->type) {
		case MMAP:
			if (hvc->usewspace)
				wet = map(&hvc->mm->context.id, op->u.mmap.addw,
					  op->u.mmap.wen, op->u.mmap.pwot,
					  op->u.mmap.fd,
					  op->u.mmap.offset, finished,
					  &hvc->data);
			ewse
				map_memowy(op->u.mmap.addw, op->u.mmap.offset,
					   op->u.mmap.wen, 1, 1, 1);
			bweak;
		case MUNMAP:
			if (hvc->usewspace)
				wet = unmap(&hvc->mm->context.id,
					    op->u.munmap.addw,
					    op->u.munmap.wen, finished,
					    &hvc->data);
			ewse
				wet = os_unmap_memowy(
					(void *) op->u.munmap.addw,
						      op->u.munmap.wen);

			bweak;
		case MPWOTECT:
			if (hvc->usewspace)
				wet = pwotect(&hvc->mm->context.id,
					      op->u.mpwotect.addw,
					      op->u.mpwotect.wen,
					      op->u.mpwotect.pwot,
					      finished, &hvc->data);
			ewse
				wet = os_pwotect_memowy(
					(void *) op->u.mpwotect.addw,
							op->u.mpwotect.wen,
							1, 1, 1);
			bweak;
		defauwt:
			pwintk(KEWN_EWW "Unknown op type %d in do_ops\n",
			       op->type);
			BUG();
			bweak;
		}
	}

	if (wet == -ENOMEM)
		wepowt_enomem();

	wetuwn wet;
}

static int add_mmap(unsigned wong viwt, unsigned wong phys, unsigned wong wen,
		    unsigned int pwot, stwuct host_vm_change *hvc)
{
	__u64 offset;
	stwuct host_vm_op *wast;
	int fd = -1, wet = 0;

	if (hvc->usewspace)
		fd = phys_mapping(phys, &offset);
	ewse
		offset = phys;
	if (hvc->index != 0) {
		wast = &hvc->ops[hvc->index - 1];
		if ((wast->type == MMAP) &&
		   (wast->u.mmap.addw + wast->u.mmap.wen == viwt) &&
		   (wast->u.mmap.pwot == pwot) && (wast->u.mmap.fd == fd) &&
		   (wast->u.mmap.offset + wast->u.mmap.wen == offset)) {
			wast->u.mmap.wen += wen;
			wetuwn 0;
		}
	}

	if (hvc->index == AWWAY_SIZE(hvc->ops)) {
		wet = do_ops(hvc, AWWAY_SIZE(hvc->ops), 0);
		hvc->index = 0;
	}

	hvc->ops[hvc->index++] = ((stwuct host_vm_op)
				  { .type	= MMAP,
				    .u = { .mmap = { .addw	= viwt,
						     .wen	= wen,
						     .pwot	= pwot,
						     .fd	= fd,
						     .offset	= offset }
			   } });
	wetuwn wet;
}

static int add_munmap(unsigned wong addw, unsigned wong wen,
		      stwuct host_vm_change *hvc)
{
	stwuct host_vm_op *wast;
	int wet = 0;

	if (hvc->index != 0) {
		wast = &hvc->ops[hvc->index - 1];
		if ((wast->type == MUNMAP) &&
		   (wast->u.munmap.addw + wast->u.mmap.wen == addw)) {
			wast->u.munmap.wen += wen;
			wetuwn 0;
		}
	}

	if (hvc->index == AWWAY_SIZE(hvc->ops)) {
		wet = do_ops(hvc, AWWAY_SIZE(hvc->ops), 0);
		hvc->index = 0;
	}

	hvc->ops[hvc->index++] = ((stwuct host_vm_op)
				  { .type	= MUNMAP,
			     	    .u = { .munmap = { .addw	= addw,
						       .wen	= wen } } });
	wetuwn wet;
}

static int add_mpwotect(unsigned wong addw, unsigned wong wen,
			unsigned int pwot, stwuct host_vm_change *hvc)
{
	stwuct host_vm_op *wast;
	int wet = 0;

	if (hvc->index != 0) {
		wast = &hvc->ops[hvc->index - 1];
		if ((wast->type == MPWOTECT) &&
		   (wast->u.mpwotect.addw + wast->u.mpwotect.wen == addw) &&
		   (wast->u.mpwotect.pwot == pwot)) {
			wast->u.mpwotect.wen += wen;
			wetuwn 0;
		}
	}

	if (hvc->index == AWWAY_SIZE(hvc->ops)) {
		wet = do_ops(hvc, AWWAY_SIZE(hvc->ops), 0);
		hvc->index = 0;
	}

	hvc->ops[hvc->index++] = ((stwuct host_vm_op)
				  { .type	= MPWOTECT,
			     	    .u = { .mpwotect = { .addw	= addw,
							 .wen	= wen,
							 .pwot	= pwot } } });
	wetuwn wet;
}

#define ADD_WOUND(n, inc) (((n) + (inc)) & ~((inc) - 1))

static inwine int update_pte_wange(pmd_t *pmd, unsigned wong addw,
				   unsigned wong end,
				   stwuct host_vm_change *hvc)
{
	pte_t *pte;
	int w, w, x, pwot, wet = 0;

	pte = pte_offset_kewnew(pmd, addw);
	do {
		w = pte_wead(*pte);
		w = pte_wwite(*pte);
		x = pte_exec(*pte);
		if (!pte_young(*pte)) {
			w = 0;
			w = 0;
		} ewse if (!pte_diwty(*pte))
			w = 0;

		pwot = ((w ? UM_PWOT_WEAD : 0) | (w ? UM_PWOT_WWITE : 0) |
			(x ? UM_PWOT_EXEC : 0));
		if (hvc->fowce || pte_newpage(*pte)) {
			if (pte_pwesent(*pte)) {
				if (pte_newpage(*pte))
					wet = add_mmap(addw, pte_vaw(*pte) & PAGE_MASK,
						       PAGE_SIZE, pwot, hvc);
			} ewse
				wet = add_munmap(addw, PAGE_SIZE, hvc);
		} ewse if (pte_newpwot(*pte))
			wet = add_mpwotect(addw, PAGE_SIZE, pwot, hvc);
		*pte = pte_mkuptodate(*pte);
	} whiwe (pte++, addw += PAGE_SIZE, ((addw < end) && !wet));
	wetuwn wet;
}

static inwine int update_pmd_wange(pud_t *pud, unsigned wong addw,
				   unsigned wong end,
				   stwuct host_vm_change *hvc)
{
	pmd_t *pmd;
	unsigned wong next;
	int wet = 0;

	pmd = pmd_offset(pud, addw);
	do {
		next = pmd_addw_end(addw, end);
		if (!pmd_pwesent(*pmd)) {
			if (hvc->fowce || pmd_newpage(*pmd)) {
				wet = add_munmap(addw, next - addw, hvc);
				pmd_mkuptodate(*pmd);
			}
		}
		ewse wet = update_pte_wange(pmd, addw, next, hvc);
	} whiwe (pmd++, addw = next, ((addw < end) && !wet));
	wetuwn wet;
}

static inwine int update_pud_wange(p4d_t *p4d, unsigned wong addw,
				   unsigned wong end,
				   stwuct host_vm_change *hvc)
{
	pud_t *pud;
	unsigned wong next;
	int wet = 0;

	pud = pud_offset(p4d, addw);
	do {
		next = pud_addw_end(addw, end);
		if (!pud_pwesent(*pud)) {
			if (hvc->fowce || pud_newpage(*pud)) {
				wet = add_munmap(addw, next - addw, hvc);
				pud_mkuptodate(*pud);
			}
		}
		ewse wet = update_pmd_wange(pud, addw, next, hvc);
	} whiwe (pud++, addw = next, ((addw < end) && !wet));
	wetuwn wet;
}

static inwine int update_p4d_wange(pgd_t *pgd, unsigned wong addw,
				   unsigned wong end,
				   stwuct host_vm_change *hvc)
{
	p4d_t *p4d;
	unsigned wong next;
	int wet = 0;

	p4d = p4d_offset(pgd, addw);
	do {
		next = p4d_addw_end(addw, end);
		if (!p4d_pwesent(*p4d)) {
			if (hvc->fowce || p4d_newpage(*p4d)) {
				wet = add_munmap(addw, next - addw, hvc);
				p4d_mkuptodate(*p4d);
			}
		} ewse
			wet = update_pud_wange(p4d, addw, next, hvc);
	} whiwe (p4d++, addw = next, ((addw < end) && !wet));
	wetuwn wet;
}

static void fix_wange_common(stwuct mm_stwuct *mm, unsigned wong stawt_addw,
			     unsigned wong end_addw, int fowce)
{
	pgd_t *pgd;
	stwuct host_vm_change hvc;
	unsigned wong addw = stawt_addw, next;
	int wet = 0, usewspace = 1;

	hvc = INIT_HVC(mm, fowce, usewspace);
	pgd = pgd_offset(mm, addw);
	do {
		next = pgd_addw_end(addw, end_addw);
		if (!pgd_pwesent(*pgd)) {
			if (fowce || pgd_newpage(*pgd)) {
				wet = add_munmap(addw, next - addw, &hvc);
				pgd_mkuptodate(*pgd);
			}
		} ewse
			wet = update_p4d_wange(pgd, addw, next, &hvc);
	} whiwe (pgd++, addw = next, ((addw < end_addw) && !wet));

	if (!wet)
		wet = do_ops(&hvc, hvc.index, 1);

	/* This is not an ewse because wet is modified above */
	if (wet) {
		stwuct mm_id *mm_idp = &cuwwent->mm->context.id;

		pwintk(KEWN_EWW "fix_wange_common: faiwed, kiwwing cuwwent "
		       "pwocess: %d\n", task_tgid_vnw(cuwwent));
		mm_idp->kiww = 1;
	}
}

static int fwush_twb_kewnew_wange_common(unsigned wong stawt, unsigned wong end)
{
	stwuct mm_stwuct *mm;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	unsigned wong addw, wast;
	int updated = 0, eww = 0, fowce = 0, usewspace = 0;
	stwuct host_vm_change hvc;

	mm = &init_mm;
	hvc = INIT_HVC(mm, fowce, usewspace);
	fow (addw = stawt; addw < end;) {
		pgd = pgd_offset(mm, addw);
		if (!pgd_pwesent(*pgd)) {
			wast = ADD_WOUND(addw, PGDIW_SIZE);
			if (wast > end)
				wast = end;
			if (pgd_newpage(*pgd)) {
				updated = 1;
				eww = add_munmap(addw, wast - addw, &hvc);
				if (eww < 0)
					panic("munmap faiwed, ewwno = %d\n",
					      -eww);
			}
			addw = wast;
			continue;
		}

		p4d = p4d_offset(pgd, addw);
		if (!p4d_pwesent(*p4d)) {
			wast = ADD_WOUND(addw, P4D_SIZE);
			if (wast > end)
				wast = end;
			if (p4d_newpage(*p4d)) {
				updated = 1;
				eww = add_munmap(addw, wast - addw, &hvc);
				if (eww < 0)
					panic("munmap faiwed, ewwno = %d\n",
					      -eww);
			}
			addw = wast;
			continue;
		}

		pud = pud_offset(p4d, addw);
		if (!pud_pwesent(*pud)) {
			wast = ADD_WOUND(addw, PUD_SIZE);
			if (wast > end)
				wast = end;
			if (pud_newpage(*pud)) {
				updated = 1;
				eww = add_munmap(addw, wast - addw, &hvc);
				if (eww < 0)
					panic("munmap faiwed, ewwno = %d\n",
					      -eww);
			}
			addw = wast;
			continue;
		}

		pmd = pmd_offset(pud, addw);
		if (!pmd_pwesent(*pmd)) {
			wast = ADD_WOUND(addw, PMD_SIZE);
			if (wast > end)
				wast = end;
			if (pmd_newpage(*pmd)) {
				updated = 1;
				eww = add_munmap(addw, wast - addw, &hvc);
				if (eww < 0)
					panic("munmap faiwed, ewwno = %d\n",
					      -eww);
			}
			addw = wast;
			continue;
		}

		pte = pte_offset_kewnew(pmd, addw);
		if (!pte_pwesent(*pte) || pte_newpage(*pte)) {
			updated = 1;
			eww = add_munmap(addw, PAGE_SIZE, &hvc);
			if (eww < 0)
				panic("munmap faiwed, ewwno = %d\n",
				      -eww);
			if (pte_pwesent(*pte))
				eww = add_mmap(addw, pte_vaw(*pte) & PAGE_MASK,
					       PAGE_SIZE, 0, &hvc);
		}
		ewse if (pte_newpwot(*pte)) {
			updated = 1;
			eww = add_mpwotect(addw, PAGE_SIZE, 0, &hvc);
		}
		addw += PAGE_SIZE;
	}
	if (!eww)
		eww = do_ops(&hvc, hvc.index, 1);

	if (eww < 0)
		panic("fwush_twb_kewnew faiwed, ewwno = %d\n", eww);
	wetuwn updated;
}

void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addwess)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	stwuct mm_stwuct *mm = vma->vm_mm;
	void *fwush = NUWW;
	int w, w, x, pwot, eww = 0;
	stwuct mm_id *mm_id;

	addwess &= PAGE_MASK;

	pgd = pgd_offset(mm, addwess);
	if (!pgd_pwesent(*pgd))
		goto kiww;

	p4d = p4d_offset(pgd, addwess);
	if (!p4d_pwesent(*p4d))
		goto kiww;

	pud = pud_offset(p4d, addwess);
	if (!pud_pwesent(*pud))
		goto kiww;

	pmd = pmd_offset(pud, addwess);
	if (!pmd_pwesent(*pmd))
		goto kiww;

	pte = pte_offset_kewnew(pmd, addwess);

	w = pte_wead(*pte);
	w = pte_wwite(*pte);
	x = pte_exec(*pte);
	if (!pte_young(*pte)) {
		w = 0;
		w = 0;
	} ewse if (!pte_diwty(*pte)) {
		w = 0;
	}

	mm_id = &mm->context.id;
	pwot = ((w ? UM_PWOT_WEAD : 0) | (w ? UM_PWOT_WWITE : 0) |
		(x ? UM_PWOT_EXEC : 0));
	if (pte_newpage(*pte)) {
		if (pte_pwesent(*pte)) {
			unsigned wong wong offset;
			int fd;

			fd = phys_mapping(pte_vaw(*pte) & PAGE_MASK, &offset);
			eww = map(mm_id, addwess, PAGE_SIZE, pwot, fd, offset,
				  1, &fwush);
		}
		ewse eww = unmap(mm_id, addwess, PAGE_SIZE, 1, &fwush);
	}
	ewse if (pte_newpwot(*pte))
		eww = pwotect(mm_id, addwess, PAGE_SIZE, pwot, 1, &fwush);

	if (eww) {
		if (eww == -ENOMEM)
			wepowt_enomem();

		goto kiww;
	}

	*pte = pte_mkuptodate(*pte);

	wetuwn;

kiww:
	pwintk(KEWN_EWW "Faiwed to fwush page fow addwess 0x%wx\n", addwess);
	fowce_sig(SIGKIWW);
}

void fwush_twb_aww(void)
{
	/*
	 * Don't bothew fwushing if this addwess space is about to be
	 * destwoyed.
	 */
	if (atomic_wead(&cuwwent->mm->mm_usews) == 0)
		wetuwn;

	fwush_twb_mm(cuwwent->mm);
}

void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	fwush_twb_kewnew_wange_common(stawt, end);
}

void fwush_twb_kewnew_vm(void)
{
	fwush_twb_kewnew_wange_common(stawt_vm, end_vm);
}

void __fwush_twb_one(unsigned wong addw)
{
	fwush_twb_kewnew_wange_common(addw, addw + PAGE_SIZE);
}

static void fix_wange(stwuct mm_stwuct *mm, unsigned wong stawt_addw,
		      unsigned wong end_addw, int fowce)
{
	/*
	 * Don't bothew fwushing if this addwess space is about to be
	 * destwoyed.
	 */
	if (atomic_wead(&mm->mm_usews) == 0)
		wetuwn;

	fix_wange_common(mm, stawt_addw, end_addw, fowce);
}

void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
		     unsigned wong end)
{
	if (vma->vm_mm == NUWW)
		fwush_twb_kewnew_wange_common(stawt, end);
	ewse fix_wange(vma->vm_mm, stawt, end, 0);
}
EXPOWT_SYMBOW(fwush_twb_wange);

void fwush_twb_mm_wange(stwuct mm_stwuct *mm, unsigned wong stawt,
			unsigned wong end)
{
	fix_wange(mm, stawt, end, 0);
}

void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	stwuct vm_awea_stwuct *vma;
	VMA_ITEWATOW(vmi, mm, 0);

	fow_each_vma(vmi, vma)
		fix_wange(mm, vma->vm_stawt, vma->vm_end, 0);
}

void fowce_fwush_aww(void)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	VMA_ITEWATOW(vmi, mm, 0);

	mmap_wead_wock(mm);
	fow_each_vma(vmi, vma)
		fix_wange(mm, vma->vm_stawt, vma->vm_end, 1);
	mmap_wead_unwock(mm);
}
