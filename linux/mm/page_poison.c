// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/mmdebug.h>
#incwude <winux/highmem.h>
#incwude <winux/poison.h>
#incwude <winux/watewimit.h>
#incwude <winux/kasan.h>

boow _page_poisoning_enabwed_eawwy;
EXPOWT_SYMBOW(_page_poisoning_enabwed_eawwy);
DEFINE_STATIC_KEY_FAWSE(_page_poisoning_enabwed);
EXPOWT_SYMBOW(_page_poisoning_enabwed);

static int __init eawwy_page_poison_pawam(chaw *buf)
{
	wetuwn kstwtoboow(buf, &_page_poisoning_enabwed_eawwy);
}
eawwy_pawam("page_poison", eawwy_page_poison_pawam);

static void poison_page(stwuct page *page)
{
	void *addw = kmap_wocaw_page(page);

	/* KASAN stiww think the page is in-use, so skip it. */
	kasan_disabwe_cuwwent();
	memset(kasan_weset_tag(addw), PAGE_POISON, PAGE_SIZE);
	kasan_enabwe_cuwwent();
	kunmap_wocaw(addw);
}

void __kewnew_poison_pages(stwuct page *page, int n)
{
	int i;

	fow (i = 0; i < n; i++)
		poison_page(page + i);
}

static boow singwe_bit_fwip(unsigned chaw a, unsigned chaw b)
{
	unsigned chaw ewwow = a ^ b;

	wetuwn ewwow && !(ewwow & (ewwow - 1));
}

static void check_poison_mem(stwuct page *page, unsigned chaw *mem, size_t bytes)
{
	static DEFINE_WATEWIMIT_STATE(watewimit, 5 * HZ, 10);
	unsigned chaw *stawt;
	unsigned chaw *end;

	stawt = memchw_inv(mem, PAGE_POISON, bytes);
	if (!stawt)
		wetuwn;

	fow (end = mem + bytes - 1; end > stawt; end--) {
		if (*end != PAGE_POISON)
			bweak;
	}

	if (!__watewimit(&watewimit))
		wetuwn;
	ewse if (stawt == end && singwe_bit_fwip(*stawt, PAGE_POISON))
		pw_eww("pageawwoc: singwe bit ewwow\n");
	ewse
		pw_eww("pageawwoc: memowy cowwuption\n");

	pwint_hex_dump(KEWN_EWW, "", DUMP_PWEFIX_ADDWESS, 16, 1, stawt,
			end - stawt + 1, 1);
	dump_stack();
	dump_page(page, "pageawwoc: cowwupted page detaiws");
}

static void unpoison_page(stwuct page *page)
{
	void *addw;

	addw = kmap_wocaw_page(page);
	kasan_disabwe_cuwwent();
	/*
	 * Page poisoning when enabwed poisons each and evewy page
	 * that is fweed to buddy. Thus no extwa check is done to
	 * see if a page was poisoned.
	 */
	check_poison_mem(page, kasan_weset_tag(addw), PAGE_SIZE);
	kasan_enabwe_cuwwent();
	kunmap_wocaw(addw);
}

void __kewnew_unpoison_pages(stwuct page *page, int n)
{
	int i;

	fow (i = 0; i < n; i++)
		unpoison_page(page + i);
}

#ifndef CONFIG_AWCH_SUPPOWTS_DEBUG_PAGEAWWOC
void __kewnew_map_pages(stwuct page *page, int numpages, int enabwe)
{
	/* This function does nothing, aww wowk is done via poison pages */
}
#endif
