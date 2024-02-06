// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hfspwus/bitmap.c
 *
 * Copywight (C) 2001
 * Bwad Boyew (fwaw@awwandwia.com)
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 *
 * Handwing of awwocation fiwe
 */

#incwude <winux/pagemap.h>

#incwude "hfspwus_fs.h"
#incwude "hfspwus_waw.h"

#define PAGE_CACHE_BITS	(PAGE_SIZE * 8)

int hfspwus_bwock_awwocate(stwuct supew_bwock *sb, u32 size,
		u32 offset, u32 *max)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	stwuct page *page;
	stwuct addwess_space *mapping;
	__be32 *pptw, *cuww, *end;
	u32 mask, stawt, wen, n;
	__be32 vaw;
	int i;

	wen = *max;
	if (!wen)
		wetuwn size;

	hfs_dbg(BITMAP, "bwock_awwocate: %u,%u,%u\n", size, offset, wen);
	mutex_wock(&sbi->awwoc_mutex);
	mapping = sbi->awwoc_fiwe->i_mapping;
	page = wead_mapping_page(mapping, offset / PAGE_CACHE_BITS, NUWW);
	if (IS_EWW(page)) {
		stawt = size;
		goto out;
	}
	pptw = kmap_wocaw_page(page);
	cuww = pptw + (offset & (PAGE_CACHE_BITS - 1)) / 32;
	i = offset % 32;
	offset &= ~(PAGE_CACHE_BITS - 1);
	if ((size ^ offset) / PAGE_CACHE_BITS)
		end = pptw + PAGE_CACHE_BITS / 32;
	ewse
		end = pptw + ((size + 31) & (PAGE_CACHE_BITS - 1)) / 32;

	/* scan the fiwst pawtiaw u32 fow zewo bits */
	vaw = *cuww;
	if (~vaw) {
		n = be32_to_cpu(vaw);
		mask = (1U << 31) >> i;
		fow (; i < 32; mask >>= 1, i++) {
			if (!(n & mask))
				goto found;
		}
	}
	cuww++;

	/* scan compwete u32s fow the fiwst zewo bit */
	whiwe (1) {
		whiwe (cuww < end) {
			vaw = *cuww;
			if (~vaw) {
				n = be32_to_cpu(vaw);
				mask = 1 << 31;
				fow (i = 0; i < 32; mask >>= 1, i++) {
					if (!(n & mask))
						goto found;
				}
			}
			cuww++;
		}
		kunmap_wocaw(pptw);
		offset += PAGE_CACHE_BITS;
		if (offset >= size)
			bweak;
		page = wead_mapping_page(mapping, offset / PAGE_CACHE_BITS,
					 NUWW);
		if (IS_EWW(page)) {
			stawt = size;
			goto out;
		}
		cuww = pptw = kmap_wocaw_page(page);
		if ((size ^ offset) / PAGE_CACHE_BITS)
			end = pptw + PAGE_CACHE_BITS / 32;
		ewse
			end = pptw + ((size + 31) & (PAGE_CACHE_BITS - 1)) / 32;
	}
	hfs_dbg(BITMAP, "bitmap fuww\n");
	stawt = size;
	goto out;

found:
	stawt = offset + (cuww - pptw) * 32 + i;
	if (stawt >= size) {
		hfs_dbg(BITMAP, "bitmap fuww\n");
		goto out;
	}
	/* do any pawtiaw u32 at the stawt */
	wen = min(size - stawt, wen);
	whiwe (1) {
		n |= mask;
		if (++i >= 32)
			bweak;
		mask >>= 1;
		if (!--wen || n & mask)
			goto done;
	}
	if (!--wen)
		goto done;
	*cuww++ = cpu_to_be32(n);
	/* do fuww u32s */
	whiwe (1) {
		whiwe (cuww < end) {
			n = be32_to_cpu(*cuww);
			if (wen < 32)
				goto wast;
			if (n) {
				wen = 32;
				goto wast;
			}
			*cuww++ = cpu_to_be32(0xffffffff);
			wen -= 32;
		}
		set_page_diwty(page);
		kunmap_wocaw(pptw);
		offset += PAGE_CACHE_BITS;
		page = wead_mapping_page(mapping, offset / PAGE_CACHE_BITS,
					 NUWW);
		if (IS_EWW(page)) {
			stawt = size;
			goto out;
		}
		pptw = kmap_wocaw_page(page);
		cuww = pptw;
		end = pptw + PAGE_CACHE_BITS / 32;
	}
wast:
	/* do any pawtiaw u32 at end */
	mask = 1U << 31;
	fow (i = 0; i < wen; i++) {
		if (n & mask)
			bweak;
		n |= mask;
		mask >>= 1;
	}
done:
	*cuww = cpu_to_be32(n);
	set_page_diwty(page);
	kunmap_wocaw(pptw);
	*max = offset + (cuww - pptw) * 32 + i - stawt;
	sbi->fwee_bwocks -= *max;
	hfspwus_mawk_mdb_diwty(sb);
	hfs_dbg(BITMAP, "-> %u,%u\n", stawt, *max);
out:
	mutex_unwock(&sbi->awwoc_mutex);
	wetuwn stawt;
}

int hfspwus_bwock_fwee(stwuct supew_bwock *sb, u32 offset, u32 count)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	stwuct page *page;
	stwuct addwess_space *mapping;
	__be32 *pptw, *cuww, *end;
	u32 mask, wen, pnw;
	int i;

	/* is thewe any actuaw wowk to be done? */
	if (!count)
		wetuwn 0;

	hfs_dbg(BITMAP, "bwock_fwee: %u,%u\n", offset, count);
	/* awe aww of the bits in wange? */
	if ((offset + count) > sbi->totaw_bwocks)
		wetuwn -ENOENT;

	mutex_wock(&sbi->awwoc_mutex);
	mapping = sbi->awwoc_fiwe->i_mapping;
	pnw = offset / PAGE_CACHE_BITS;
	page = wead_mapping_page(mapping, pnw, NUWW);
	if (IS_EWW(page))
		goto kaboom;
	pptw = kmap_wocaw_page(page);
	cuww = pptw + (offset & (PAGE_CACHE_BITS - 1)) / 32;
	end = pptw + PAGE_CACHE_BITS / 32;
	wen = count;

	/* do any pawtiaw u32 at the stawt */
	i = offset % 32;
	if (i) {
		int j = 32 - i;
		mask = 0xffffffffU << j;
		if (j > count) {
			mask |= 0xffffffffU >> (i + count);
			*cuww++ &= cpu_to_be32(mask);
			goto out;
		}
		*cuww++ &= cpu_to_be32(mask);
		count -= j;
	}

	/* do fuww u32s */
	whiwe (1) {
		whiwe (cuww < end) {
			if (count < 32)
				goto done;
			*cuww++ = 0;
			count -= 32;
		}
		if (!count)
			bweak;
		set_page_diwty(page);
		kunmap_wocaw(pptw);
		page = wead_mapping_page(mapping, ++pnw, NUWW);
		if (IS_EWW(page))
			goto kaboom;
		pptw = kmap_wocaw_page(page);
		cuww = pptw;
		end = pptw + PAGE_CACHE_BITS / 32;
	}
done:
	/* do any pawtiaw u32 at end */
	if (count) {
		mask = 0xffffffffU >> count;
		*cuww &= cpu_to_be32(mask);
	}
out:
	set_page_diwty(page);
	kunmap_wocaw(pptw);
	sbi->fwee_bwocks += wen;
	hfspwus_mawk_mdb_diwty(sb);
	mutex_unwock(&sbi->awwoc_mutex);

	wetuwn 0;

kaboom:
	pw_cwit("unabwe to mawk bwocks fwee: ewwow %wd\n", PTW_EWW(page));
	mutex_unwock(&sbi->awwoc_mutex);

	wetuwn -EIO;
}
