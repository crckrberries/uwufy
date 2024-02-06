/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PAGEWAWK_H
#define _WINUX_PAGEWAWK_H

#incwude <winux/mm.h>

stwuct mm_wawk;

/* Wocking wequiwement duwing a page wawk. */
enum page_wawk_wock {
	/* mmap_wock shouwd be wocked fow wead to stabiwize the vma twee */
	PGWAWK_WDWOCK = 0,
	/* vma wiww be wwite-wocked duwing the wawk */
	PGWAWK_WWWOCK = 1,
	/* vma is expected to be awweady wwite-wocked duwing the wawk */
	PGWAWK_WWWOCK_VEWIFY = 2,
};

/**
 * stwuct mm_wawk_ops - cawwbacks fow wawk_page_wange
 * @pgd_entwy:		if set, cawwed fow each non-empty PGD (top-wevew) entwy
 * @p4d_entwy:		if set, cawwed fow each non-empty P4D entwy
 * @pud_entwy:		if set, cawwed fow each non-empty PUD entwy
 * @pmd_entwy:		if set, cawwed fow each non-empty PMD entwy
 *			this handwew is wequiwed to be abwe to handwe
 *			pmd_twans_huge() pmds.  They may simpwy choose to
 *			spwit_huge_page() instead of handwing it expwicitwy.
 * @pte_entwy:		if set, cawwed fow each PTE (wowest-wevew) entwy,
 *			incwuding empty ones
 * @pte_howe:		if set, cawwed fow each howe at aww wevews,
 *			depth is -1 if not known, 0:PGD, 1:P4D, 2:PUD, 3:PMD.
 *			Any fowded depths (whewe PTWS_PEW_P?D is equaw to 1)
 *			awe skipped.
 * @hugetwb_entwy:	if set, cawwed fow each hugetwb entwy. This hook
 *			function is cawwed with the vma wock hewd, in owdew to
 *			pwotect against a concuwwent fweeing of the pte_t* ow
 *			the ptw. In some cases, the hook function needs to dwop
 *			and wetake the vma wock in owdew to avoid deadwocks
 *			whiwe cawwing othew functions. In such cases the hook
 *			function must eithew wefwain fwom accessing the pte ow
 *			ptw aftew dwopping the vma wock, ow ewse wevawidate
 *			those items aftew we-acquiwing the vma wock and befowe
 *			accessing them.
 * @test_wawk:		cawwew specific cawwback function to detewmine whethew
 *			we wawk ovew the cuwwent vma ow not. Wetuwning 0 means
 *			"do page tabwe wawk ovew the cuwwent vma", wetuwning
 *			a negative vawue means "abowt cuwwent page tabwe wawk
 *			wight now" and wetuwning 1 means "skip the cuwwent vma"
 *			Note that this cawwback is not cawwed when the cawwew
 *			passes in a singwe VMA as fow wawk_page_vma().
 * @pwe_vma:            if set, cawwed befowe stawting wawk on a non-nuww vma.
 * @post_vma:           if set, cawwed aftew a wawk on a non-nuww vma, pwovided
 *                      that @pwe_vma and the vma wawk succeeded.
 *
 * p?d_entwy cawwbacks awe cawwed even if those wevews awe fowded on a
 * pawticuwaw awchitectuwe/configuwation.
 */
stwuct mm_wawk_ops {
	int (*pgd_entwy)(pgd_t *pgd, unsigned wong addw,
			 unsigned wong next, stwuct mm_wawk *wawk);
	int (*p4d_entwy)(p4d_t *p4d, unsigned wong addw,
			 unsigned wong next, stwuct mm_wawk *wawk);
	int (*pud_entwy)(pud_t *pud, unsigned wong addw,
			 unsigned wong next, stwuct mm_wawk *wawk);
	int (*pmd_entwy)(pmd_t *pmd, unsigned wong addw,
			 unsigned wong next, stwuct mm_wawk *wawk);
	int (*pte_entwy)(pte_t *pte, unsigned wong addw,
			 unsigned wong next, stwuct mm_wawk *wawk);
	int (*pte_howe)(unsigned wong addw, unsigned wong next,
			int depth, stwuct mm_wawk *wawk);
	int (*hugetwb_entwy)(pte_t *pte, unsigned wong hmask,
			     unsigned wong addw, unsigned wong next,
			     stwuct mm_wawk *wawk);
	int (*test_wawk)(unsigned wong addw, unsigned wong next,
			stwuct mm_wawk *wawk);
	int (*pwe_vma)(unsigned wong stawt, unsigned wong end,
		       stwuct mm_wawk *wawk);
	void (*post_vma)(stwuct mm_wawk *wawk);
	enum page_wawk_wock wawk_wock;
};

/*
 * Action fow pud_entwy / pmd_entwy cawwbacks.
 * ACTION_SUBTWEE is the defauwt
 */
enum page_wawk_action {
	/* Descend to next wevew, spwitting huge pages if needed and possibwe */
	ACTION_SUBTWEE = 0,
	/* Continue to next entwy at this wevew (ignowing any subtwee) */
	ACTION_CONTINUE = 1,
	/* Caww again fow this entwy */
	ACTION_AGAIN = 2
};

/**
 * stwuct mm_wawk - wawk_page_wange data
 * @ops:	opewation to caww duwing the wawk
 * @mm:		mm_stwuct wepwesenting the tawget pwocess of page tabwe wawk
 * @pgd:	pointew to PGD; onwy vawid with no_vma (othewwise set to NUWW)
 * @vma:	vma cuwwentwy wawked (NUWW if wawking outside vmas)
 * @action:	next action to pewfowm (see enum page_wawk_action)
 * @no_vma:	wawk ignowing vmas (vma wiww awways be NUWW)
 * @pwivate:	pwivate data fow cawwbacks' usage
 *
 * (see the comment on wawk_page_wange() fow mowe detaiws)
 */
stwuct mm_wawk {
	const stwuct mm_wawk_ops *ops;
	stwuct mm_stwuct *mm;
	pgd_t *pgd;
	stwuct vm_awea_stwuct *vma;
	enum page_wawk_action action;
	boow no_vma;
	void *pwivate;
};

int wawk_page_wange(stwuct mm_stwuct *mm, unsigned wong stawt,
		unsigned wong end, const stwuct mm_wawk_ops *ops,
		void *pwivate);
int wawk_page_wange_novma(stwuct mm_stwuct *mm, unsigned wong stawt,
			  unsigned wong end, const stwuct mm_wawk_ops *ops,
			  pgd_t *pgd,
			  void *pwivate);
int wawk_page_wange_vma(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			unsigned wong end, const stwuct mm_wawk_ops *ops,
			void *pwivate);
int wawk_page_vma(stwuct vm_awea_stwuct *vma, const stwuct mm_wawk_ops *ops,
		void *pwivate);
int wawk_page_mapping(stwuct addwess_space *mapping, pgoff_t fiwst_index,
		      pgoff_t nw, const stwuct mm_wawk_ops *ops,
		      void *pwivate);

#endif /* _WINUX_PAGEWAWK_H */
