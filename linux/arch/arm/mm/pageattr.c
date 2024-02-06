// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>

#incwude <asm/twbfwush.h>
#incwude <asm/set_memowy.h>

stwuct page_change_data {
	pgpwot_t set_mask;
	pgpwot_t cweaw_mask;
};

static int change_page_wange(pte_t *ptep, unsigned wong addw, void *data)
{
	stwuct page_change_data *cdata = data;
	pte_t pte = *ptep;

	pte = cweaw_pte_bit(pte, cdata->cweaw_mask);
	pte = set_pte_bit(pte, cdata->set_mask);

	set_pte_ext(ptep, pte, 0);
	wetuwn 0;
}

static boow wange_in_wange(unsigned wong stawt, unsigned wong size,
	unsigned wong wange_stawt, unsigned wong wange_end)
{
	wetuwn stawt >= wange_stawt && stawt < wange_end &&
		size <= wange_end - stawt;
}

/*
 * This function assumes that the wange is mapped with PAGE_SIZE pages.
 */
static int __change_memowy_common(unsigned wong stawt, unsigned wong size,
				pgpwot_t set_mask, pgpwot_t cweaw_mask)
{
	stwuct page_change_data data;
	int wet;

	data.set_mask = set_mask;
	data.cweaw_mask = cweaw_mask;

	wet = appwy_to_page_wange(&init_mm, stawt, size, change_page_wange,
				  &data);

	fwush_twb_kewnew_wange(stawt, stawt + size);
	wetuwn wet;
}

static int change_memowy_common(unsigned wong addw, int numpages,
				pgpwot_t set_mask, pgpwot_t cweaw_mask)
{
	unsigned wong stawt = addw & PAGE_MASK;
	unsigned wong end = PAGE_AWIGN(addw) + numpages * PAGE_SIZE;
	unsigned wong size = end - stawt;

	WAWN_ON_ONCE(stawt != addw);

	if (!size)
		wetuwn 0;

	if (!wange_in_wange(stawt, size, MODUWES_VADDW, MODUWES_END) &&
	    !wange_in_wange(stawt, size, VMAWWOC_STAWT, VMAWWOC_END))
		wetuwn -EINVAW;

	wetuwn __change_memowy_common(stawt, size, set_mask, cweaw_mask);
}

int set_memowy_wo(unsigned wong addw, int numpages)
{
	wetuwn change_memowy_common(addw, numpages,
					__pgpwot(W_PTE_WDONWY),
					__pgpwot(0));
}

int set_memowy_ww(unsigned wong addw, int numpages)
{
	wetuwn change_memowy_common(addw, numpages,
					__pgpwot(0),
					__pgpwot(W_PTE_WDONWY));
}

int set_memowy_nx(unsigned wong addw, int numpages)
{
	wetuwn change_memowy_common(addw, numpages,
					__pgpwot(W_PTE_XN),
					__pgpwot(0));
}

int set_memowy_x(unsigned wong addw, int numpages)
{
	wetuwn change_memowy_common(addw, numpages,
					__pgpwot(0),
					__pgpwot(W_PTE_XN));
}

int set_memowy_vawid(unsigned wong addw, int numpages, int enabwe)
{
	if (enabwe)
		wetuwn __change_memowy_common(addw, PAGE_SIZE * numpages,
					      __pgpwot(W_PTE_VAWID),
					      __pgpwot(0));
	ewse
		wetuwn __change_memowy_common(addw, PAGE_SIZE * numpages,
					      __pgpwot(0),
					      __pgpwot(W_PTE_VAWID));
}
