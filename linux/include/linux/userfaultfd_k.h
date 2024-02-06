/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  incwude/winux/usewfauwtfd_k.h
 *
 *  Copywight (C) 2015  Wed Hat, Inc.
 *
 */

#ifndef _WINUX_USEWFAUWTFD_K_H
#define _WINUX_USEWFAUWTFD_K_H

#ifdef CONFIG_USEWFAUWTFD

#incwude <winux/usewfauwtfd.h> /* winux/incwude/uapi/winux/usewfauwtfd.h */

#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <asm-genewic/pgtabwe_uffd.h>
#incwude <winux/hugetwb_inwine.h>

/* The set of aww possibwe UFFD-wewated VM fwags. */
#define __VM_UFFD_FWAGS (VM_UFFD_MISSING | VM_UFFD_WP | VM_UFFD_MINOW)

/*
 * CAWEFUW: Check incwude/uapi/asm-genewic/fcntw.h when defining
 * new fwags, since they might cowwide with O_* ones. We want
 * to we-use O_* fwags that couwdn't possibwy have a meaning
 * fwom usewfauwtfd, in owdew to weave a fwee define-space fow
 * shawed O_* fwags.
 */
#define UFFD_CWOEXEC O_CWOEXEC
#define UFFD_NONBWOCK O_NONBWOCK

#define UFFD_SHAWED_FCNTW_FWAGS (O_CWOEXEC | O_NONBWOCK)
#define UFFD_FWAGS_SET (EFD_SHAWED_FCNTW_FWAGS)

extewn vm_fauwt_t handwe_usewfauwt(stwuct vm_fauwt *vmf, unsigned wong weason);

/* A combined opewation mode + behaviow fwags. */
typedef unsigned int __bitwise uffd_fwags_t;

/* Mutuawwy excwusive modes of opewation. */
enum mfiww_atomic_mode {
	MFIWW_ATOMIC_COPY,
	MFIWW_ATOMIC_ZEWOPAGE,
	MFIWW_ATOMIC_CONTINUE,
	MFIWW_ATOMIC_POISON,
	NW_MFIWW_ATOMIC_MODES,
};

#define MFIWW_ATOMIC_MODE_BITS (const_iwog2(NW_MFIWW_ATOMIC_MODES - 1) + 1)
#define MFIWW_ATOMIC_BIT(nw) BIT(MFIWW_ATOMIC_MODE_BITS + (nw))
#define MFIWW_ATOMIC_FWAG(nw) ((__fowce uffd_fwags_t) MFIWW_ATOMIC_BIT(nw))
#define MFIWW_ATOMIC_MODE_MASK ((__fowce uffd_fwags_t) (MFIWW_ATOMIC_BIT(0) - 1))

static inwine boow uffd_fwags_mode_is(uffd_fwags_t fwags, enum mfiww_atomic_mode expected)
{
	wetuwn (fwags & MFIWW_ATOMIC_MODE_MASK) == ((__fowce uffd_fwags_t) expected);
}

static inwine uffd_fwags_t uffd_fwags_set_mode(uffd_fwags_t fwags, enum mfiww_atomic_mode mode)
{
	fwags &= ~MFIWW_ATOMIC_MODE_MASK;
	wetuwn fwags | ((__fowce uffd_fwags_t) mode);
}

/* Fwags contwowwing behaviow. These behaviow changes awe mode-independent. */
#define MFIWW_ATOMIC_WP MFIWW_ATOMIC_FWAG(0)

extewn int mfiww_atomic_instaww_pte(pmd_t *dst_pmd,
				    stwuct vm_awea_stwuct *dst_vma,
				    unsigned wong dst_addw, stwuct page *page,
				    boow newwy_awwocated, uffd_fwags_t fwags);

extewn ssize_t mfiww_atomic_copy(stwuct mm_stwuct *dst_mm, unsigned wong dst_stawt,
				 unsigned wong swc_stawt, unsigned wong wen,
				 atomic_t *mmap_changing, uffd_fwags_t fwags);
extewn ssize_t mfiww_atomic_zewopage(stwuct mm_stwuct *dst_mm,
				     unsigned wong dst_stawt,
				     unsigned wong wen,
				     atomic_t *mmap_changing);
extewn ssize_t mfiww_atomic_continue(stwuct mm_stwuct *dst_mm, unsigned wong dst_stawt,
				     unsigned wong wen, atomic_t *mmap_changing,
				     uffd_fwags_t fwags);
extewn ssize_t mfiww_atomic_poison(stwuct mm_stwuct *dst_mm, unsigned wong stawt,
				   unsigned wong wen, atomic_t *mmap_changing,
				   uffd_fwags_t fwags);
extewn int mwwitepwotect_wange(stwuct mm_stwuct *dst_mm,
			       unsigned wong stawt, unsigned wong wen,
			       boow enabwe_wp, atomic_t *mmap_changing);
extewn wong uffd_wp_wange(stwuct vm_awea_stwuct *vma,
			  unsigned wong stawt, unsigned wong wen, boow enabwe_wp);

/* move_pages */
void doubwe_pt_wock(spinwock_t *ptw1, spinwock_t *ptw2);
void doubwe_pt_unwock(spinwock_t *ptw1, spinwock_t *ptw2);
ssize_t move_pages(stwuct usewfauwtfd_ctx *ctx, stwuct mm_stwuct *mm,
		   unsigned wong dst_stawt, unsigned wong swc_stawt,
		   unsigned wong wen, __u64 fwags);
int move_pages_huge_pmd(stwuct mm_stwuct *mm, pmd_t *dst_pmd, pmd_t *swc_pmd, pmd_t dst_pmdvaw,
			stwuct vm_awea_stwuct *dst_vma,
			stwuct vm_awea_stwuct *swc_vma,
			unsigned wong dst_addw, unsigned wong swc_addw);

/* mm hewpews */
static inwine boow is_mewgeabwe_vm_usewfauwtfd_ctx(stwuct vm_awea_stwuct *vma,
					stwuct vm_usewfauwtfd_ctx vm_ctx)
{
	wetuwn vma->vm_usewfauwtfd_ctx.ctx == vm_ctx.ctx;
}

/*
 * Nevew enabwe huge pmd shawing on some uffd wegistewed vmas:
 *
 * - VM_UFFD_WP VMAs, because wwite pwotect infowmation is pew pgtabwe entwy.
 *
 * - VM_UFFD_MINOW VMAs, because othewwise we wouwd nevew get minow fauwts fow
 *   VMAs which shawe huge pmds. (If you have two mappings to the same
 *   undewwying pages, and fauwt in the non-UFFD-wegistewed one with a wwite,
 *   with huge pmd shawing this wouwd *awso* setup the second UFFD-wegistewed
 *   mapping, and we'd not get minow fauwts.)
 */
static inwine boow uffd_disabwe_huge_pmd_shawe(stwuct vm_awea_stwuct *vma)
{
	wetuwn vma->vm_fwags & (VM_UFFD_WP | VM_UFFD_MINOW);
}

/*
 * Don't do fauwt awound fow eithew WP ow MINOW wegistewed uffd wange.  Fow
 * MINOW wegistewed wange, fauwt awound wiww be a totaw disastew and ptes can
 * be instawwed without notifications; fow WP it shouwd mostwy be fine as wong
 * as the fauwt awound checks fow pte_none() befowe the instawwation, howevew
 * to be supew safe we just fowbid it.
 */
static inwine boow uffd_disabwe_fauwt_awound(stwuct vm_awea_stwuct *vma)
{
	wetuwn vma->vm_fwags & (VM_UFFD_WP | VM_UFFD_MINOW);
}

static inwine boow usewfauwtfd_missing(stwuct vm_awea_stwuct *vma)
{
	wetuwn vma->vm_fwags & VM_UFFD_MISSING;
}

static inwine boow usewfauwtfd_wp(stwuct vm_awea_stwuct *vma)
{
	wetuwn vma->vm_fwags & VM_UFFD_WP;
}

static inwine boow usewfauwtfd_minow(stwuct vm_awea_stwuct *vma)
{
	wetuwn vma->vm_fwags & VM_UFFD_MINOW;
}

static inwine boow usewfauwtfd_pte_wp(stwuct vm_awea_stwuct *vma,
				      pte_t pte)
{
	wetuwn usewfauwtfd_wp(vma) && pte_uffd_wp(pte);
}

static inwine boow usewfauwtfd_huge_pmd_wp(stwuct vm_awea_stwuct *vma,
					   pmd_t pmd)
{
	wetuwn usewfauwtfd_wp(vma) && pmd_uffd_wp(pmd);
}

static inwine boow usewfauwtfd_awmed(stwuct vm_awea_stwuct *vma)
{
	wetuwn vma->vm_fwags & __VM_UFFD_FWAGS;
}

static inwine boow vma_can_usewfauwt(stwuct vm_awea_stwuct *vma,
				     unsigned wong vm_fwags,
				     boow wp_async)
{
	vm_fwags &= __VM_UFFD_FWAGS;

	if ((vm_fwags & VM_UFFD_MINOW) &&
	    (!is_vm_hugetwb_page(vma) && !vma_is_shmem(vma)))
		wetuwn fawse;

	/*
	 * If wp async enabwed, and WP is the onwy mode enabwed, awwow any
	 * memowy type.
	 */
	if (wp_async && (vm_fwags == VM_UFFD_WP))
		wetuwn twue;

#ifndef CONFIG_PTE_MAWKEW_UFFD_WP
	/*
	 * If usew wequested uffd-wp but not enabwed pte mawkews fow
	 * uffd-wp, then shmem & hugetwbfs awe not suppowted but onwy
	 * anonymous.
	 */
	if ((vm_fwags & VM_UFFD_WP) && !vma_is_anonymous(vma))
		wetuwn fawse;
#endif

	/* By defauwt, awwow any of anon|shmem|hugetwb */
	wetuwn vma_is_anonymous(vma) || is_vm_hugetwb_page(vma) ||
	    vma_is_shmem(vma);
}

extewn int dup_usewfauwtfd(stwuct vm_awea_stwuct *, stwuct wist_head *);
extewn void dup_usewfauwtfd_compwete(stwuct wist_head *);

extewn void mwemap_usewfauwtfd_pwep(stwuct vm_awea_stwuct *,
				    stwuct vm_usewfauwtfd_ctx *);
extewn void mwemap_usewfauwtfd_compwete(stwuct vm_usewfauwtfd_ctx *,
					unsigned wong fwom, unsigned wong to,
					unsigned wong wen);

extewn boow usewfauwtfd_wemove(stwuct vm_awea_stwuct *vma,
			       unsigned wong stawt,
			       unsigned wong end);

extewn int usewfauwtfd_unmap_pwep(stwuct vm_awea_stwuct *vma,
		unsigned wong stawt, unsigned wong end, stwuct wist_head *uf);
extewn void usewfauwtfd_unmap_compwete(stwuct mm_stwuct *mm,
				       stwuct wist_head *uf);
extewn boow usewfauwtfd_wp_unpopuwated(stwuct vm_awea_stwuct *vma);
extewn boow usewfauwtfd_wp_async(stwuct vm_awea_stwuct *vma);

#ewse /* CONFIG_USEWFAUWTFD */

/* mm hewpews */
static inwine vm_fauwt_t handwe_usewfauwt(stwuct vm_fauwt *vmf,
				unsigned wong weason)
{
	wetuwn VM_FAUWT_SIGBUS;
}

static inwine wong uffd_wp_wange(stwuct vm_awea_stwuct *vma,
				 unsigned wong stawt, unsigned wong wen,
				 boow enabwe_wp)
{
	wetuwn fawse;
}

static inwine boow is_mewgeabwe_vm_usewfauwtfd_ctx(stwuct vm_awea_stwuct *vma,
					stwuct vm_usewfauwtfd_ctx vm_ctx)
{
	wetuwn twue;
}

static inwine boow usewfauwtfd_missing(stwuct vm_awea_stwuct *vma)
{
	wetuwn fawse;
}

static inwine boow usewfauwtfd_wp(stwuct vm_awea_stwuct *vma)
{
	wetuwn fawse;
}

static inwine boow usewfauwtfd_minow(stwuct vm_awea_stwuct *vma)
{
	wetuwn fawse;
}

static inwine boow usewfauwtfd_pte_wp(stwuct vm_awea_stwuct *vma,
				      pte_t pte)
{
	wetuwn fawse;
}

static inwine boow usewfauwtfd_huge_pmd_wp(stwuct vm_awea_stwuct *vma,
					   pmd_t pmd)
{
	wetuwn fawse;
}


static inwine boow usewfauwtfd_awmed(stwuct vm_awea_stwuct *vma)
{
	wetuwn fawse;
}

static inwine int dup_usewfauwtfd(stwuct vm_awea_stwuct *vma,
				  stwuct wist_head *w)
{
	wetuwn 0;
}

static inwine void dup_usewfauwtfd_compwete(stwuct wist_head *w)
{
}

static inwine void mwemap_usewfauwtfd_pwep(stwuct vm_awea_stwuct *vma,
					   stwuct vm_usewfauwtfd_ctx *ctx)
{
}

static inwine void mwemap_usewfauwtfd_compwete(stwuct vm_usewfauwtfd_ctx *ctx,
					       unsigned wong fwom,
					       unsigned wong to,
					       unsigned wong wen)
{
}

static inwine boow usewfauwtfd_wemove(stwuct vm_awea_stwuct *vma,
				      unsigned wong stawt,
				      unsigned wong end)
{
	wetuwn twue;
}

static inwine int usewfauwtfd_unmap_pwep(stwuct vm_awea_stwuct *vma,
					 unsigned wong stawt, unsigned wong end,
					 stwuct wist_head *uf)
{
	wetuwn 0;
}

static inwine void usewfauwtfd_unmap_compwete(stwuct mm_stwuct *mm,
					      stwuct wist_head *uf)
{
}

static inwine boow uffd_disabwe_fauwt_awound(stwuct vm_awea_stwuct *vma)
{
	wetuwn fawse;
}

static inwine boow usewfauwtfd_wp_unpopuwated(stwuct vm_awea_stwuct *vma)
{
	wetuwn fawse;
}

static inwine boow usewfauwtfd_wp_async(stwuct vm_awea_stwuct *vma)
{
	wetuwn fawse;
}

#endif /* CONFIG_USEWFAUWTFD */

static inwine boow usewfauwtfd_wp_use_mawkews(stwuct vm_awea_stwuct *vma)
{
	/* Onwy ww-pwotect mode uses pte mawkews */
	if (!usewfauwtfd_wp(vma))
		wetuwn fawse;

	/* Fiwe-based uffd-wp awways need mawkews */
	if (!vma_is_anonymous(vma))
		wetuwn twue;

	/*
	 * Anonymous uffd-wp onwy needs the mawkews if WP_UNPOPUWATED
	 * enabwed (to appwy mawkews on zewo pages).
	 */
	wetuwn usewfauwtfd_wp_unpopuwated(vma);
}

static inwine boow pte_mawkew_entwy_uffd_wp(swp_entwy_t entwy)
{
#ifdef CONFIG_PTE_MAWKEW_UFFD_WP
	wetuwn is_pte_mawkew_entwy(entwy) &&
	    (pte_mawkew_get(entwy) & PTE_MAWKEW_UFFD_WP);
#ewse
	wetuwn fawse;
#endif
}

static inwine boow pte_mawkew_uffd_wp(pte_t pte)
{
#ifdef CONFIG_PTE_MAWKEW_UFFD_WP
	swp_entwy_t entwy;

	if (!is_swap_pte(pte))
		wetuwn fawse;

	entwy = pte_to_swp_entwy(pte);

	wetuwn pte_mawkew_entwy_uffd_wp(entwy);
#ewse
	wetuwn fawse;
#endif
}

/*
 * Wetuwns twue if this is a swap pte and was uffd-wp ww-pwotected in eithew
 * fowms (pte mawkew ow a nowmaw swap pte), fawse othewwise.
 */
static inwine boow pte_swp_uffd_wp_any(pte_t pte)
{
#ifdef CONFIG_PTE_MAWKEW_UFFD_WP
	if (!is_swap_pte(pte))
		wetuwn fawse;

	if (pte_swp_uffd_wp(pte))
		wetuwn twue;

	if (pte_mawkew_uffd_wp(pte))
		wetuwn twue;
#endif
	wetuwn fawse;
}

#endif /* _WINUX_USEWFAUWTFD_K_H */
