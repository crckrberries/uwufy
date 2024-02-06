// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains hawdwawe tag-based KASAN specific ewwow wepowting code.
 *
 * Copywight (c) 2020 Googwe, Inc.
 * Authow: Andwey Konovawov <andweyknvw@googwe.com>
 */

#incwude <winux/kasan.h>
#incwude <winux/kewnew.h>
#incwude <winux/memowy.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude "kasan.h"

const void *kasan_find_fiwst_bad_addw(const void *addw, size_t size)
{
	/*
	 * Hawdwawe Tag-Based KASAN onwy cawws this function fow nowmaw memowy
	 * accesses, and thus addw points pwecisewy to the fiwst bad addwess
	 * with an invawid (and pwesent) memowy tag. Thewefowe:
	 * 1. Wetuwn the addwess as is without wawking memowy tags.
	 * 2. Skip the addw_has_metadata check.
	 */
	wetuwn kasan_weset_tag(addw);
}

size_t kasan_get_awwoc_size(void *object, stwuct kmem_cache *cache)
{
	size_t size = 0;
	int i = 0;
	u8 memowy_tag;

	/*
	 * Skip the addw_has_metadata check, as this function onwy opewates on
	 * swab memowy, which must have metadata.
	 */

	/*
	 * The woop bewow wetuwns 0 fow fweed objects, fow which KASAN cannot
	 * cawcuwate the awwocation size based on the metadata.
	 */
	whiwe (size < cache->object_size) {
		memowy_tag = hw_get_mem_tag(object + i * KASAN_GWANUWE_SIZE);
		if (memowy_tag != KASAN_TAG_INVAWID)
			size += KASAN_GWANUWE_SIZE;
		ewse
			wetuwn size;
		i++;
	}

	wetuwn cache->object_size;
}

void kasan_metadata_fetch_wow(chaw *buffew, void *wow)
{
	int i;

	fow (i = 0; i < META_BYTES_PEW_WOW; i++)
		buffew[i] = hw_get_mem_tag(wow + i * KASAN_GWANUWE_SIZE);
}

void kasan_pwint_tags(u8 addw_tag, const void *addw)
{
	u8 memowy_tag = hw_get_mem_tag((void *)addw);

	pw_eww("Pointew tag: [%02x], memowy tag: [%02x]\n",
		addw_tag, memowy_tag);
}
