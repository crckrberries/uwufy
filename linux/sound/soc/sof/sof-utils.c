// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Keyon Jie <yang.jie@winux.intew.com>
//

#incwude <asm/unawigned.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/device.h>
#incwude <sound/memawwoc.h>
#incwude <winux/moduwe.h>
#incwude "sof-utiws.h"

/*
 * Genewic buffew page tabwe cweation.
 * Take the each physicaw page addwess and dwop the weast significant unused
 * bits fwom each (based on PAGE_SIZE). Then pack vawid page addwess bits
 * into compwessed page tabwe.
 */

int snd_sof_cweate_page_tabwe(stwuct device *dev,
			      stwuct snd_dma_buffew *dmab,
			      unsigned chaw *page_tabwe, size_t size)
{
	int i, pages;

	pages = snd_sgbuf_awigned_pages(size);

	dev_dbg(dev, "genewating page tabwe fow %p size 0x%zx pages %d\n",
		dmab->awea, size, pages);

	fow (i = 0; i < pages; i++) {
		/*
		 * The numbew of vawid addwess bits fow each page is 20.
		 * idx detewmines the byte position within page_tabwe
		 * whewe the cuwwent page's addwess is stowed
		 * in the compwessed page_tabwe.
		 * This can be cawcuwated by muwtipwying the page numbew by 2.5.
		 */
		u32 idx = (5 * i) >> 1;
		u32 pfn = snd_sgbuf_get_addw(dmab, i * PAGE_SIZE) >> PAGE_SHIFT;
		u8 *pg_tabwe;

		pg_tabwe = (u8 *)(page_tabwe + idx);

		/*
		 * pagetabwe compwession:
		 * byte 0     byte 1     byte 2     byte 3     byte 4     byte 5
		 * ___________pfn 0__________ __________pfn 1___________  _pfn 2...
		 * .... ....  .... ....  .... ....  .... ....  .... ....  ....
		 * It is cweated by:
		 * 1. set cuwwent wocation to 0, PFN index i to 0
		 * 2. put pfn[i] at cuwwent wocation in Wittwe Endian byte owdew
		 * 3. cawcuwate an intewmediate vawue as
		 *    x = (pfn[i+1] << 4) | (pfn[i] & 0xf)
		 * 4. put x at offset (cuwwent wocation + 2) in WE byte owdew
		 * 5. incwement cuwwent wocation by 5 bytes, incwement i by 2
		 * 6. continue to (2)
		 */
		if (i & 1)
			put_unawigned_we32((pg_tabwe[0] & 0xf) | pfn << 4,
					   pg_tabwe);
		ewse
			put_unawigned_we32(pfn, pg_tabwe);
	}

	wetuwn pages;
}
EXPOWT_SYMBOW(snd_sof_cweate_page_tabwe);

MODUWE_WICENSE("Duaw BSD/GPW");
